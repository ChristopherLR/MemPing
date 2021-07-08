#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "timer_1.h"
#include <counter.h>

#define BUTTON 3
#define RED_LED 7
#define SECONDS_PER_DAY 86400
#define TICKS_PER_SECOND 61
#define DEBUG false

Counter counter = {0, 0, 0};
volatile unsigned char sys_tick = 0;

String LED_DISP1 = "Last taken:     ";

unsigned char UPDATE_DISP = 0;

volatile unsigned char button_tick = 0;
volatile unsigned char can_update_button = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void update_display();
void button_press();

void setup() {

  // PORTB = 0;
  // DDRB = 0;
  // PORTC = 0;
  // DDRC = 0;
  // PORTD = 0;
  // DDRD = 0;
  
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_press, FALLING);

  digitalWrite(RED_LED, LOW);
  if (DEBUG) Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(LED_DISP1);
  lcd.setCursor(0,1);
  lcd.print("0");
  
  if (DEBUG) Serial.print("DEBUG::ENABLED");
  configure_clock2();
  configure_clock1(15624); // 15624 ticks per second
  sei();//allow interrupts
}

ISR(TIMER2_COMPB_vect){
	TCNT2 = 0;
	sys_tick++;

	if(sys_tick >= TICKS_PER_SECOND) {
    sys_tick = 0;
  };
};

// Occurs every one second
ISR(TIMER1_COMPB_vect) {
  if (counter.hours > 18){
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
  }

  increment(&counter);
  UPDATE_DISP = 1;
  if (button_tick <= 0){
    button_tick++;
  }
  TCNT1 = 0;
}

void button_press(){
  if (button_tick){
    reset(&counter);
    button_tick = 0;
  }
}

void update_display(){
  lcd.setCursor(0,1);
  lcd.print(get_time(&counter)); 
}

void loop() {
  if (UPDATE_DISP) {
    update_display();
    UPDATE_DISP = 0;
  }
}