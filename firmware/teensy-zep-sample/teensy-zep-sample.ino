
/**
 * Write one packet to the usb connection.
 * 
 * A packet has a header + a payload.
 * The header starts with its size max 255 and its type also an
 * eight bit entity. The size is the size of the total packet.
 * So the payload is the size of the packet - the size of the header.
 */
class SerialPackage {
  
  public:
    
    enum package_type {
      START,
      STOP,
      HEADER,
      SAMPLE,
      SCREEN_INTERRUPT,
      SOUND_SAMPLE
    };
    
    void send_start()
    {
      const int size = sizeof(uint8_t) + sizeof(uint8_t); 
      set_size(HDR_SZ);
      set_type(START);
      Serial.write(m_buffer, size);
    }
    
    void send_stop()
    {
      const int size = sizeof(uint8_t) + sizeof(uint8_t);
      set_type(STOP);
      set_size(size);
      Serial.write(m_buffer, size);      
    }

    void send_header(const char* header, size_t hdr_sz)
    {
      // limit size of header to 256 bytes hdr_sz is the length
      // the content, not the package header. HDR_SZ is the size
      // of the SerialPackage header.
      int size = HDR_SZ + hdr_sz < 256 ? HDR_SZ + hdr_sz : 256;
      
      set_type(HEADER);
      set_size(size);
      set_string(header, hdr_sz < 254 ? hdr_sz: 254 );
      
      Serial.write(m_buffer, size);
    }

    void send_sample(unsigned long t,
                     uint8_t w,
                     uint8_t b,
                     uint16_t photo,
                     uint16_t sound
                     )
    {
      const int size = HDR_SZ + sizeof(t) + sizeof(w) + sizeof(b) + 
                                sizeof(photo) + sizeof(sound);
      uint8_t* wrptr = m_buffer + HDR_SZ; // point right after the packet header.
      
      set_type(SAMPLE);
      set_size(size);

      // Copy all arguments to buffer.
      memcpy(wrptr, &t    , sizeof(t));     wrptr += sizeof(t);
      memcpy(wrptr, &w    , sizeof(w));     wrptr += sizeof(w);
      memcpy(wrptr, &b    , sizeof(b));     wrptr += sizeof(b);
      memcpy(wrptr, &photo, sizeof(photo)); wrptr += sizeof(photo);
      memcpy(wrptr, &sound, sizeof(sound)); wrptr += sizeof(sound);
    
      Serial.write(m_buffer, size);
    }

    void send_screen_interrupt(unsigned long t, uint8_t line_val)
    {
      const int size = HDR_SZ + sizeof(t) + sizeof(line_val);
      uint8_t* wrptr =  m_buffer + HDR_SZ;

      set_type(SCREEN_INTERRUPT);
      set_size(size);
      memcpy(wrptr, &t, sizeof(t));             wrptr += sizeof(t);
      memcpy(wrptr, &line_val, sizeof(uint8_t));wrptr += sizeof(uint8_t);

      Serial.write(m_buffer, size);
    }

    void send_sound_sample(uint32_t tbeg, uint32_t tend)
    {
      const int size = HDR_SZ + sizeof(tbeg) + sizeof(tend);
      uint8_t* wrptr = m_buffer + HDR_SZ; // Point right after the packet header.

      set_type(SOUND_SAMPLE);
      set_size(size);

      memcpy(wrptr, &tbeg, sizeof(tbeg)); wrptr += sizeof(tbeg);
      memcpy(wrptr, &tend, sizeof(tend)); wrptr += sizeof(tend);
      
      Serial.write(m_buffer, size);
    }
    
  private:

    const size_t HDR_SZ = 2;
  
    void set_string(const char* s, size_t hdr)
    {
      memcpy(m_buffer + 2, s, hdr < 254 ? hdr : 254);
    }
    
    void set_type(uint8_t pkg_type)
    {
      m_buffer[1] = pkg_type;
    }

    void set_size(uint8_t size)
    {
      m_buffer[0] = size;
    }

    uint8_t m_buffer[256];
};

class SoundTiming {

  public:
    SoundTiming() {
      reset();
    }
    
    void reset() {
      m_start = 0;
      m_end = 0;
    }

    /**
     * Register the time.
     * Each first time sample will set m_start and m_end.
     * Each subsequent sample will only set m_end, untill
     * reset is called.
     */
    void register_time(uint32_t t)
    {
      if (!m_start)
        m_start = t;
      m_end = t;
    }

    void get_times(uint32_t* pstart, uint32_t* pend) {
      *pstart = m_start;
      *pend = m_end;
    }

  private:
    
    uint32_t m_start; // First registered time.
    uint32_t m_end;   // Last registered time.
};


/**
 * Global variables
 */

const int LED_PIN           = 13; // led on teensy device
const int BLINK_PIN         = 12; // the led to blink

// Interrupt pins active low
const int ZEP_START_PIN     = 23; // Zep (BeexyBox X) will pull this pin low when experiment starts.
const int ZEP_SOUND_PIN     = 22; // Is set high when a sound sampling interval starts 
                                  // Is put high by BeexyBox or parallel port

// Input pins (Analog)
const int SENSOR_PHOTO_PIN  = 14; // Reads photo diode current converted to voltage.
const int SENSOR_SOUND_PIN  = 15; // Reads sound level.

// Input pins (Digital)
const int SCREEN_PIN        = 10; // Goes high or low in according to the screen.
const int SOUND_LEVEL_PIN   = 9;  // Is driven by the sound output of the audio lineout. 

//Sample every 100 micro seconds/10th of a millisecond.
#define SAMPLE_PERIOD 100

// set when a interrupt occures from ISR functions.
volatile int start_interrupt      = 0; // whether the program is taking samples.
volatile int sample_interrupt     = 0; // Is set when we should take a sample.
volatile int screen_interrupt     = 0; // occurs on a flank of the output of the photo
                                       // transistor circuit.
volatile int zep_sound_interrupt  = 0; // Is set on a flank before(rising) or after (falling) the 
                                       // sound has been presented.
volatile int sound_level_interrupt= 0; // is set on a flank of the teensy.

int led_val   = LOW;  // digital level of the led on teensy.

int8_t experiment_line  = HIGH;   // When pulled low the experiment is started.

bool started = false;             // Is set when the Zep tells it is ready to start.

IntervalTimer timer;
unsigned long zero_time;

SerialPackage package;
SoundTiming   sound_timer;

/***
 * Interrupt routines 
 */
void start_line_isr(void) {
  start_interrupt = 1;
}

void sample_interrupt_isr(void) {
  sample_interrupt = 1;
}

void screen_interrupt_isr() {
  screen_interrupt = 1;
}

void sound_level_isr() {
  // is set on flanks of the sound stimulus.
  sound_level_interrupt = 1;
}

void zep_sound_interrupt_isr() {
  // is set high just before zep starts an auditory stimulus.
  zep_sound_interrupt = 1;
}

/**
 * General functions
 */

 /**
  * Prepares the Teensy for a session. And send a start
  * message to the teensy-sample program.
  */
void start_measure_handler() // Starts the experiment
{
  // write the teensy led pin down in case it was on.
  zero_time = micros();
  const char* header = "time\twhite\tblack\tphoto\tsound";

  Serial.begin(9600); // Teensy always uses fullspeed usb speed.
  Serial.flush();     // Remove as much junk as possible.

  // Send start
  package.send_start();
  
  // We send the header without terminating 0 byte.
  package.send_header(header, strlen(header));

  timer.begin(sample_interrupt_isr, SAMPLE_PERIOD);

  digitalWrite(LED_PIN, LOW);
  started = true;
}

/**
 * Stops the session and send a stop signal to 
 */
void stop_measure_handler() //  And stop it
{
  started = false;
  timer.end();
  package.send_stop();
  Serial.flush();
  Serial.end();
  digitalWrite(BLINK_PIN, LOW);
}

void start_handler()
{
  int val = digitalRead(ZEP_START_PIN);
  if (val == HIGH)
    start_measure_handler();
  else
    stop_measure_handler();
}

void take_sample()
{
  unsigned t        = micros() - zero_time;
  int white         = 0;//digitalRead(ZEP_WHITE_PIN);
  int black         = 0;//digitalRead(ZEP_BLACK_PIN);
  int photo_value   = analogRead(SENSOR_PHOTO_PIN);
  int sound_value   = analogRead(SENSOR_SOUND_PIN);

  package.send_sample(t, white, black, photo_value, sound_value);
}

void screen_interrupt_handler()
{
  unsigned t      = micros() - zero_time;
  uint8_t lineval = digitalRead(SCREEN_PIN);

  package.send_screen_interrupt(t, lineval);
}

void zep_sound_interrupt_handler()
{
  // We start a new sound timing measurement, thus reset the sound timings.
  int value = digitalRead(ZEP_SOUND_PIN);
  if (value == HIGH) {
    sound_timer.reset();
  }
  else {
    uint32_t soundstart, soundend;
    sound_timer.get_times(&soundstart, &soundend);
    package.send_sound_sample(soundstart, soundend);
  }
}

void sound_level_interrupt_handler()
{
  uint32_t t = micros() - zero_time;
  sound_timer.register_time(t);
}

void setup()
{
  pinMode(LED_PIN,    OUTPUT);
  pinMode(BLINK_PIN,  OUTPUT);
  
  pinMode(ZEP_START_PIN,    INPUT);
  pinMode(SCREEN_PIN,       INPUT_PULLUP);
  pinMode(ZEP_SOUND_PIN,    INPUT);
  pinMode(SOUND_LEVEL_PIN,  INPUT_PULLUP);
  
  attachInterrupt(ZEP_START_PIN,    start_line_isr,           CHANGE);
  attachInterrupt(SCREEN_PIN,       screen_interrupt_isr,     CHANGE);
  attachInterrupt(ZEP_SOUND_PIN,    zep_sound_interrupt_isr,  CHANGE);
  attachInterrupt(SOUND_LEVEL_PIN,  sound_level_isr,          CHANGE);
}

void loop()
{
  if (start_interrupt) {
    start_interrupt = 0;
    start_handler();
  }

  if (sample_interrupt) {
    sample_interrupt = 0;
    if(started) {
      take_sample();
    }
  }

  if (screen_interrupt) {
    screen_interrupt = 0;
    if(started) {
      screen_interrupt_handler();
    }
  }

  if (zep_sound_interrupt) {
    zep_sound_interrupt = 0;
    if(started) {
      zep_sound_interrupt_handler(); 
    }
  }

  if (sound_level_interrupt) {
    sound_level_interrupt = 0;
    if (started)
      sound_level_interrupt_handler();
  }
    
  if(!started) { // only blink in standby.
    // blink status led
    long t = millis();
    if ((t/250) % 2)
      digitalWrite(LED_PIN, HIGH);
    else
      digitalWrite(LED_PIN, LOW);
  }
  
}


