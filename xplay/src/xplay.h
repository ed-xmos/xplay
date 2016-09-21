

#include <sndfile.h>
#include <thread>
#include <mutex>
#include <condition_variable>

typedef enum playmode{PLAYMODE_TONE, PLAYMODE_FILE, PLAYMODE_SILENCE} playmode_t;

class OutputChan
{
    public:
        OutputChan();
        virtual ~OutputChan() {};
        virtual int getNextSample(void) = 0;
};


class InputChan 
{
    public:
        InputChan();
        virtual ~InputChan() {};
        virtual void consumeSample(int sample) = 0;
};


class SampleTransform {
 public:
  virtual int transform(int) = 0;
};


class XPlay 
{
	public:
  		XPlay(unsigned sampleRate, OutputChan *oc);
  		~XPlay();
  		int run(unsigned delay_ms);
  		unsigned GetSampleRate();
        unsigned GetNumChansOut();
        unsigned GetNumChansIn();
  		OutputChan* outChans; // Should be private
  		InputChan* inChans;

	private:
  		unsigned sampleRate;
  		unsigned numIn;
  		unsigned numOut;
        unsigned playmode;
  		//bool loopback;
  		//bool useWDM;
};


/* OutChans */

class FileOutputChan : public OutputChan 
{
    public:
        FileOutputChan(char * filename);
        ~FileOutputChan();
        int getNextSample(void);

    private:
        std::thread *fileThread;
        unsigned count;
        unsigned bufSize;
        int *buf;
 
            
};

class SineOutputChan : public OutputChan 
{
    public:
        SineOutputChan(unsigned sampleRate, unsigned freq);
        int getNextSample(void);
    private:
        unsigned sampleRate;
        unsigned freq;
        int count;
        int period;
        int initialDelayCount;
        int *table;
};





