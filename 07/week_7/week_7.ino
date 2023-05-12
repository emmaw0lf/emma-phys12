#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32)
#define TFT_CS         14
#define TFT_RST        15
#define TFT_DC         32

#elif defined(ESP8266)
#define TFT_CS         4
#define TFT_RST        16
#define TFT_DC         5

#else

#define TFT_CS        10
#define TFT_RST        9
#define TFT_DC         8
#endif

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
int red = ST77XX_RED;
int blue = ST77XX_BLUE;

class Background
{
  public:
    int bgColor;
    void screen(int color) {
      tft.fillScreen(color);
    }
    Background(int);
}
;

Background::Background(int backgroundColor): bgColor(backgroundColor) {

}



long result;   //variable for the result of the tx_rx measurement.
int analog_pin = A3;
int tx_pin = 4;

Background bg = Background(red);

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  pinMode(tx_pin, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  tft.init(135, 240);

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

}

void loop() {
  result = tx_rx();
  Serial.println(result);
  if (result > 2700 && result < 12000) {
    bg.bgColor = red;
    bg.screen(bg.bgColor);

  } else {
    bg.bgColor = blue;
    bg.screen(bg.bgColor);
  }
}


long tx_rx() {        // Function to execute rx_tx algorithm and return a value
  // that depends on coupling of two electrodes.
  // Value returned is a long integer.
  int read_high;
  int read_low;
  int diff;
  long int sum;
  int N_samples = 100;    // Number of samples to take.  Larger number slows it down, but reduces scatter.

  sum = 0;

  for (int i = 0; i < N_samples; i++) {
    digitalWrite(tx_pin, HIGH);             // Step the voltage high on conductor 1.
    read_high = analogRead(analog_pin);     // Measure response of conductor 2.
    delayMicroseconds(100);                 // Delay to reach steady state.
    digitalWrite(tx_pin, LOW);              // Step the voltage to zero on conductor 1.
    read_low = analogRead(analog_pin);      // Measure response of conductor 2.
    diff = read_high - read_low;            // desired answer is the difference between high and low.
    sum += diff;                            // Sums up N_samples of these measurements.


  }

  return sum;

}
