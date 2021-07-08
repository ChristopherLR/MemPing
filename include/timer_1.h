#include <avr/interrupt.h>
#include <avr/io.h>

void configure_clock1(const int freq){

  /* TIMSK1
   * Timer/Counter 1 Interrupt Mask Register
   * Bit 5: ICF1 - Input Capture Flag
   * Bit 2: OCF1B - Output Compare B Match
   * Bit 1: OCF1A -
   * bit 0: TOV1 - Overflow Flag
   */
  // enable timer compare interrupt
  TIMSK1 = (1 << OCF1B);

  /* TCCR1B - Timer 1 Control Reg B
   * [ICNC1][ICES1][-][WGM13][WGM12][CS12][CS11][CS10]
   * ICNC1 - Input Capture Noise Canceler
   * ICES1 - Input Capture Edge Select
   * WGM - Waveform Gen Mode - Setting PWM/Normal
   * CS - Clock Select - Pre-scaling */
  //TCCR1B = 0b00000000; /* Stopping the clock */

  /* TCCR1A - Timer 1 Control Reg A
   * [COM1A1][COM1A0][COM1B1][COM1B0][-][-][WGM11][WGM10]
   * COM1A - Compare Output mode channel A
   * COM1B - ** for A
   * WGM - Wave Gen Mode */

  TCCR1A = 0b00000000;

  /* To Set WGM = 0000 and Prescaler to 1024
   * TCCR1B = [00][-][00][101]
   * TCCR1C = [FOC1A][FOC1B][-][-][-][-][-][-]
   * FOC - Force Output Compare for A/B */
  TCCR1B = 0;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TCCR1C = (1 << FOC1B);  

  /* OCR1B - (OCR1BH & OCR1BL) - 16 Bit
   * Output Compare Register B
   * Bit 15-0: Output to compare to timer
   * 16,000,000/1024 = 15625 Ticks per sec */
  OCR1A = freq;

  /* TIFRx - Timer Interrupt Flag Registers
   * [-][-][-][-][-][OCFxB][OCFxA][TOVx]
   * OCFxB - Compare Match B
   * OCFxA - Compare Match A
   * TOVx - Timer Overflow flagc */
  //TIFR1 = 0b00000000;

  /* TCNT1 - (TCNT1H & TCNT1L) - 16 Bit
   * Timer/Counter 1
   * Bit 15-0: The value of the timer */
  TCNT1 = 0;
};

void configure_clock2(){
	TIMSK2 = 0b00000100; //Setting flag on compare b
	/* TCCR2B Timer/Counter Control Reg B
	 * [FOC2A][FOC2B][-][-][WGM22][CS22][CS21][CS20]
	 */
	TCCR2B = 0; // turning clock off

	/* TCCR2A Timer/Counter Control Reg A
	 * [COM2A1][COM2A0][COM2B1][COM2B0][-][-][WGM21][WGM20]
	 */
	TCCR2A = 0; // Setting waveform to normal op

	OCR2B = 255; // Setting max compare

	TIFR2 = 0b00000100; // ISR on compare match b

	/*
	 * (16,000,000/1024)/255 = 0.01632
	 * 1/0.01632 = 61 -> need 61 for 1 second
	 */
	TCCR2B = 0b00000111; // Setting prescaler to 1024

	TCNT2 = 0; // Setting clock to 0
}