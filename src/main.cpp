#include <Arduino.h>


// timer 2 interrupt
void handler_tim2(void){
  GPIOC_BASE->ODR ^= 0x2000; // BLINK LED PC13
}

// timer 2 setup
void setup_timer2() {
  //TIMER2_BASE->CR1 = 0x00000084;
  TIMER2_BASE->PSC = 7200; //72MHz/7200=10,000 Hz 
  TIMER2_BASE->ARR = 10000; //10000/10000=1Hz
  TIMER2_BASE->CNT = 0;  //clear counter
  timer_attach_interrupt(TIMER2, 0, handler_tim2); //interrupt on timer update
  TIMER2_BASE->CR1 |= 0x0001; //enable timer.  
}

void setup() {
  //timer 2 setup
  setup_timer2();

  //GPIO setup
  GPIOC_BASE->CRH = 0x44244444; //enable PC13 as output
  GPIOC_BASE->BSRR = 0x20000000; //reset PC13 (low)

}

void loop() {
  delay(2000);
  Serial.println("delay\ton");
}
