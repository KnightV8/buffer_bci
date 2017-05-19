#define EEGO_SDK_BIND_STATIC // How to bind
#include <eemagine/sdk/factory.h> // SDK header
#include <eemagine/sdk/wrapper.cc> // Wrapper code to be compiled.
#include <iostream> // console io 

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
<<<<<<< HEAD
#include <sys/time.h>
=======
>>>>>>> 4cb5a13... eego2ft driver

#ifdef PLATFORM_WIN32
    // function Sleep in ms!
    #include <conio.h>
    #include <windows.h>
#else
    // function sleep in s!
    #include <unistd.h>
#endif

#include <OnlineDataManager.h>
#include <ConsoleInput.h>
#include <StringServer.h>

static int BUFFRATE=50; /* rate (Hz) at which samples are sent to the buffer */
<<<<<<< HEAD
static int BUFFERSUBSAMPLESIZE=1; /* number of buffer samples per amplifier sample */
<<<<<<< HEAD
=======
>>>>>>> 765db6e... eego support stuff
static int sampleRate=250;
=======
>>>>>>> 4cb5a13... eego2ft driver

#if defined(__WIN32__) || defined(__WIN64__)
 #define SIGALRM -1
 #if defined(NOBACKGROUNDSCAN)
    #include <wlanapi.h>
 #endif
#endif


<<<<<<< HEAD
bool running=true;
=======
amplifier* amp=null ; 
stream* eegStream=null; 
>>>>>>> 4cb5a13... eego2ft driver
int port=1972, ctrlPort=8000;
char hostname[256]="localhost";
StringServer ctrlServ;
ConsoleInput conIn;

<<<<<<< HEAD
using namespace eemagine::sdk;
amplifier* amp=NULL ; 
stream* eegStream=NULL; 


void shutdown(){
  running=false;
      #ifdef PLATFORM_WIN32
        Sleep(100);
      #else
        sleep(.1); 
      #endif  
   delete eegStream;
   delete amp;
}

=======
>>>>>>> 4cb5a13... eego2ft driver
void sig_handler(int32_t sig) 
{
  fprintf(stdout,"\nStop grabbing with signal %d\n",sig);
  shutdown();
  //raise(SIGALRM);  
  exit(sig);
}

void usage(){
  fprintf(stderr, "Usage: eego2ft <config-file> buffhost buffport ctrlport samprate buffrate \n");
  fprintf(stderr, "where:\n");
  fprintf(stderr, "\t <config-file> is a configureation file for the streaming\n");
  fprintf(stderr, "\t buffhost - address of the buffer host computer.       (%s)\n",hostname);
  fprintf(stderr, "\t Passing a minus (-) tells this application to spawn its own buffer server\n");
  fprintf(stderr, "\t buffport\t int port number                            (%d)\n",port);
  fprintf(stderr, "\t ctrlPort\t int port number of control interface for ODM (%d)\n",ctrlPort);
  fprintf(stderr, "\t samprate\t float sample rate to run the amp at        (%d)\n",sampleRate);
  fprintf(stderr, "\t buffrate\t is the frequency in Hz that data is sent to the buffer    (%d)\n",BUFFRATE);
  /*sig_handler(0);*/
}


void acquisition(const char *configFile, unsigned int sampleRate) {
  int nsamp=0, nblk=0;
   int packetInterval_ms = 1000./BUFFRATE;
   long int elapsedusec=0, printtime=0;
   struct timeval starttime, curtime;
   if( packetInterval_ms<1 ) { packetInterval_ms = 10; }

<<<<<<< HEAD
   int nChannels = amp->getChannelList().size();
   OnlineDataManager<double, double> ODM(0, nChannels, (float) sampleRate);
	
   if( !strcmp(configFile, "-") ) {
     if (ODM.configureFromFile(configFile) != 0) {
       fprintf(stderr, "Configuration %s file is invalid\n", configFile);
       return;
     } else {
       printf("Streaming %i out of %i channels\n", ODM.getSignalConfiguration().getStreamingSelection().getSize(), nChannels);
     }
=======
   nChannels = amp.getChannelList().size();
   OnlineDataManager<double, double> ODM(0, nChannels, (float) sampleRate);
	
   if( !strcmp(configFile, "-") ) {
	if (ODM.configureFromFile(configFile) != 0) {
		fprintf(stderr, "Configuration %s file is invalid\n", configFile);
		return;
	} else {
		printf("Streaming %i out of %i channels\n", ODM.getSignalConfiguration().getStreamingSelection().getSize(), TOTAL_CHANNELS);
	}
>>>>>>> 4cb5a13... eego2ft driver
   }
	if (!strcmp(hostname, "-")) {
		if (!ODM.useOwnServer(port)) {
			fprintf(stderr, "Could not spawn buffer server on port %d.\n",port);
			return;
		}
	} else {
		if (!ODM.connectToServer(hostname, port)) {
			fprintf(stderr, "Could not connect to buffer server at %s:%d.\n",hostname, port);
			return;
		}
	}
	
	ODM.enableStreaming();
	
	printf("Starting to transfer data - press [Escape] to quit\n");

<<<<<<< HEAD
	while (running) {
=======
	while (1) {
>>>>>>> 4cb5a13... eego2ft driver
		if (conIn.checkKey() && conIn.getKey()==27) break;	
		ctrlServ.checkRequests(ODM);
	
      buffer buf = eegStream->getData(); // Retrieve data from stream std::cout << "Samples read: "
		unsigned int nSamplesTaken=buf.getSampleCount();
		if (nSamplesTaken != 0) {
			double* dest = ODM.provideBlock(nSamplesTaken); 
<<<<<<< HEAD
			for (int i=0;i<nChannels;i++) {					
				for (unsigned int j=0;j<nSamplesTaken;j++) {
              dest[i + j*nChannels] = buf.getSample(i,j);
=======
			for (int i=0;i<TOTAL_CHANNELS;i++) {					
				for (unsigned int j=0;j<nSamplesTaken;j++) {
              dest[i + j*TOTAL_CHANNELS] = buf.getSample(i,j);
>>>>>>> 4cb5a13... eego2ft driver
				}
			}
			if (!ODM.handleBlock()) break;
		}

      // progress logging
      nsamp += nSamplesTaken;
      nblk += 1;
      gettimeofday(&curtime,NULL);
      elapsedusec=(curtime.tv_usec + 1000000 * curtime.tv_sec) - (starttime.tv_usec + 1000000 * starttime.tv_sec);
      if ( elapsedusec / 1000000 >= printtime ) {
        fprintf(stderr,"%d %d %d %f (blk,samp,event,sec)\r",nblk,nsamp,0,elapsedusec/1000000.0);
        printtime+=10;
      }
      // TODO: sleep taking account of the delay in sending etc?
      #ifdef PLATFORM_WIN32
        Sleep(packetInterval_ms);
      #else
<<<<<<< HEAD
        sleep(packetInterval_ms/1000.0f); 
=======
        sleep(packetInterval_ms./1000.0f); 
>>>>>>> 4cb5a13... eego2ft driver
      #endif
	}
}

<<<<<<< HEAD
int main(int argc, char **argv) {
	//const unsigned short composerPort	= 1726;
	
	if (argc<2) {
     usage();
     return 1;
	}
	if (argc>2) {
     strncpy(hostname, argv[2], sizeof(hostname));
	}	
	if (argc>3) {
		port = atoi(argv[3]);
	}	
	if (argc>4) {
		ctrlPort = atoi(argv[4]);
	}
	if (argc>5 ){
     sampleRate = atoi(argv[5]);
   }
	if (argc>6 ){
     BUFFRATE = atoi(argv[5]);
   }
=======


int main(int argc, char **argv) {
	//const unsigned short composerPort	= 1726;
	unsigned int samplingRate = 0;
	
	if (argc<2) {
     usage();
		return 1;
	}
	
	if (argc>2) {
		strncpy(hostname, argv[2], sizeof(hostname));
	} else {
		strcpy(hostname, "localhost");
	}
	
	if (argc>3) {
		port = atoi(argv[3]);
	} else {
		port = 1972;
	}	

	if (argc>4) {
		ctrlPort = atoi(argv[4]);
	} else {
		ctrlPort = 8000;
	}	
>>>>>>> 4cb5a13... eego2ft driver
	
	if (!ctrlServ.startListening(ctrlPort)) {
		fprintf(stderr, "Cannot listen on port %d for configuration commands\n", ctrlPort);
		return 1;
	}
	
<<<<<<< HEAD
  factory fact;
  amp = fact.getAmplifier(); // Get an amplifier
  eegStream = amp->OpenEegStream(sampleRate); // The sampling rate is the only argument needed
	
	if (eegStream != 0 && sampleRate!=0) {
		acquisition(argv[1], sampleRate);
	}
	
=======
  using namespace eemagine::sdk;
  factory fact;
  amp = fact.getAmplifier(); // Get an amplifier
  eegStream = amp->OpenEegStream(samplingRate); // The sampling rate is the only argument needed
	
	if (eegStream != 0 && samplingRate!=0) {
		acquisition(argv[1], samplingRate);
	}
	
   delete eegStream;
   delete amp;

>>>>>>> 4cb5a13... eego2ft driver
	return 0;
}  
