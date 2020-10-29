/*
  Durability Test
  Author: Marisa Lim (marisa.lim@u.nus.edu)
  Evolution Innovation Lab
  National University of Singapore
*/

#include "SPI.h"                          // To communicate with SPI devices
// #include "TFT_eSPI.h"                     // Arduino IDE compatible graphics and fonts library
// #include "Free_Fonts.h"                   // Include the header file attached to this sketch
// #include "NUS.h"                          // NUS logo
#include <Wire.h>                         // This is needed for FT6206 
#include <Adafruit_FT6206.h>              // The FT6206 uses hardware I2C (SCL/SDA)

//Added by WLW on 26 FEB 2019 START from here
//for ADCs, I/O expenders and PWM controllers
#include <Adafruit_ADS1015.h>
#include <FaBoPWM_PCA9685.h>
#include <Adafruit_MCP23017.h>

#include <Mcp3208.h>
SPIClass spiADC(HSPI);

#define SPI_CS      15       // 2   // dummy
#define ADC_VREF    1200     // 1.2V Vref
#define ADC_CLK     4000000  // SPI clock 1.2MHz   20x60k
#define SPLS        100      // samples

#define ADC_CS_CTRL_1 15
#define ADC_CS_CTRL_2 4

#define SPDT_CTRL_1   25     //Single Pole Double Throw (SPDT) Switch
#define SPDT_CTRL_2   26

#define SPDT_IN1  digitalWrite (SPDT_CTRL_1, LOW); digitalWrite (SPDT_CTRL_2, LOW)
#define SPDT_IN2  digitalWrite (SPDT_CTRL_1, HIGH); digitalWrite (SPDT_CTRL_2, LOW)
#define SPDT_IN3  digitalWrite (SPDT_CTRL_1, LOW); digitalWrite (SPDT_CTRL_2, HIGH)
#define SPDT_IN4  digitalWrite (SPDT_CTRL_1, HIGH); digitalWrite (SPDT_CTRL_2, HIGH)


MCP3208 adc(ADC_VREF, SPI_CS, &spiADC);

uint16_t data[3][8][SPLS] = {0}; //there are 3x ADC chips and each with 7 single-ended channels

MCP3208::Channel ADC_CH[8] = {
  MCP3208::SINGLE_0,
  MCP3208::SINGLE_1,
  MCP3208::SINGLE_2,
  MCP3208::SINGLE_3,
  MCP3208::SINGLE_4,
  MCP3208::SINGLE_5,
  MCP3208::SINGLE_6,
  MCP3208::SINGLE_7
};


#define MUX_EN  33    //active LOW
#define MUX_IN  32

Adafruit_ADS1015 ads = Adafruit_ADS1015(0x49);     /* Use this for the 12-bit version */
Adafruit_ADS1015 ads2 = Adafruit_ADS1015(0x48);     /* Use this for the 12-bit version */
FaBoPWM TNTPWM;       //using I2C_TWO defined in modified ADS1015 Library
Adafruit_MCP23017 mcp;

//int16_t
int PRESSURE[11];
int value[10];
int VIN_SENSE; //11 elements array for holding PRESSURE readings

//Added by WLW on 26 FEB 2019 END at here
//TFT_eSPI tft = TFT_eSPI();                // Use LCD screen uses hardware SPI

Adafruit_FT6206 ctp = Adafruit_FT6206();

#define pump    1         // WLW - define I/O points
#define valve1  2
#define valve2  3
#define valve3  4
#define valve4  5
#define valve5  6
#define valve6  7
#define valve7  8
#define valve8  9
#define valve9  10
#define valve10 11
#define pressureSensor1  1
#define pressureSensor2  2
#define pressureSensor3  3
#define pressureSensor4  4
#define pressureSensor5  5
#define pressureSensor6  6
#define pressureSensor7  7
#define pressureSensor8  8
#define pressureSensor9  9
#define pressureSensor10 10
#define pressureSensor11 11


long seqTime;

int input = 0;
int old_input = 0;
float val = 0;
unsigned int startT = 0;
int now = 0;
int period = 6000; // 6 seconds
int program_start_T;
int count = 0;

void setup() //-------------------------------------------------------------------------------------------------------------------------------------------------------
{
  program_start_T = millis();

  pinMode (ADC_CS_CTRL_1, OUTPUT);
  pinMode (ADC_CS_CTRL_2, OUTPUT);
  pinMode (SPDT_CTRL_1, OUTPUT);
  pinMode (SPDT_CTRL_2, OUTPUT);

  //Added by WLW on 26 FEB 2019 START from here
  //for MUX ic control, ADC and I/O expenders
  pinMode(MUX_EN, OUTPUT);
  pinMode(MUX_IN, OUTPUT);

  SPDT_IN1;
  // initialize SPI interface for MCP3208
  adc.Chip_ID = 1;
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  spiADC.begin(14, 12, 13, 15);
  spiADC.beginTransaction(settings);

  ads.begin();

  if (TNTPWM.begin()) {
    TNTPWM.init(0); //set all PWM channels duty cycle to be zero [0% -50% -100%] map to [0-2048-4095]
  }

  mcp.begin();      // use default address
  mcp.pinMode(1, OUTPUT);
  //Added by WLW on 26 FEB 2019 END at here

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  Serial.begin(115200);

}

void loop(void) //----------------------------------------------------------------------------------------------------------------------------------------------------
{
  String ipw;
  while(Serial.available()) {
    char c = Serial.read();
    ipw += c;
    if(ipw == "start") cyclic_valve(); // only start cyclic counts when Python starts
    if(ipw == "reset") reset();
  }
  ipw = "";
//  delay(1);
}

// Functions ----------------------------------------------------------------------------------------------------------------------------------------------------

void reset() {
  Serial.print("reset");
  count = 0;
}

void read_while_rest(int setTime) { // function to call read
  startT = millis();
  while (millis() - startT < setTime) { // while time of 3 seconds isn't up
    ADC_READING(); // read pressure value
  }
}

void cyclic_valve() {
  for (int i = 0; i < 5000; i++) {
    TNTPWM.set_channel_value(1, 4095); // valve on
    read_while_rest(period / 2); // 3 seconds - 3000 ms
    TNTPWM.set_channel_value(1, 0); // valve off
    read_while_rest(period / 2); // 3 seconds - 3000 ms
    count += 1; // counting cycles
  }
}

//added by WLW on 25 FEB 2019 for ADC readings
void ADC_READING() {
  now = millis() - program_start_T;
  Serial.print(count); // print the cycle number
  Serial.print(","); 
  
  digitalWrite(MUX_EN, LOW);
  digitalWrite(MUX_IN, LOW);
  PRESSURE[0] = ads.readADC_SingleEnded(0);
  PRESSURE[2] = ads.readADC_SingleEnded(1);
  PRESSURE[4] = ads.readADC_SingleEnded(2);
  PRESSURE[6] = ads.readADC_SingleEnded(3);
  PRESSURE[8] = ads2.readADC_SingleEnded(0);
  PRESSURE[10] = ads2.readADC_SingleEnded(1);
  digitalWrite(MUX_IN, HIGH);
  PRESSURE[1] = ads.readADC_SingleEnded(0);
  PRESSURE[3] = ads.readADC_SingleEnded(1);
  PRESSURE[5] = ads.readADC_SingleEnded(2);
  PRESSURE[7] = ads.readADC_SingleEnded(3);
  PRESSURE[9] = ads2.readADC_SingleEnded(0);
  VIN_SENSE = ads2.readADC_SingleEnded(1);

  // produce calibrated values
  if ((PRESSURE[2] <= 263) && (PRESSURE[2] > 0)) { // only using one valve now
    val = 0;
  }
  else if (PRESSURE[2] > 263) {
    val = 0.3774 * PRESSURE[2] - 100.12; 
  }
  Serial.print(val); // print the calibrated pressure value
  Serial.print("\n"); // new line
  
}
