#define timedelaykeypad 400 //thoi gian doi sang ki tu *
// Define LED pins for system status
#define LED_WAIT PIN_C2      // Waiting for password (Yellow)
#define LED_GRANTED PIN_C1   // Access granted (Green)
#define LED_DENIED PIN_C0    // Access denied (Red)
// Define motor driver control pins
#define MOTOR_IN1 PIN_C0     // Motor direction control
#define MOTOR_IN2 PIN_C1     // Motor direction control
#define MOTOR_ENA PIN_C2     // Motor enable
//Gram
#define testonoff 0 //test mode (0 cho tat, 1 cho bat)

UNSIGNED INT8 HANG,COT,MP,MPT;
CONST UNSIGNED CHAR MAQUETCOT[4]= {0xFE,0xFD,0xFB,0xF7};


void Motor_start() {
   output_low(pin_D6);
//!  output_high(MOTOR_ENA);       // Enable motor
//!  output_high(MOTOR_IN1);       // Set motor direction (adjust as needed)
//!  output_low(MOTOR_IN2);
}// Stop the motor
void Motor_stop() {
   output_high(pin_D6);
//!  output_low(MOTOR_ENA);        // Disable motor
//!  output_low(MOTOR_IN1);
//!  output_low(MOTOR_IN2);
}// Function to get key press from keypad (4x4 matrix)

UNSIGNED INT KEYPRESS(){
   MP=HANG=0XFF;
   FOR(COT=0;COT<4;COT++){
      OUTPUT_B(MAQUETCOT[COT]);
   IF       (!INPUT(PIN_B4)) {HANG=3; BREAK;}
   ELSE  IF (!INPUT(PIN_B5)) {HANG=2; BREAK;}
   ELSE  IF (!INPUT(PIN_B6)) {  HANG=1;BREAK;}
   ELSE  IF (!INPUT(PIN_B7)) {HANG=0; BREAK;}
   }
   IF (HANG!=0XFF) MP = (3-COT) + HANG*4;
   switch(mp){
      case 0: MP=13; break;
      case 1: MP=12; break;
      case 2: MP=11; break;
      case 3: MP=10; break;
      case 4: MP=15; break;
      case 5: MP=9; break;
      case 6: MP=6; break;
      case 7: MP=3; break;
      case 8: MP=0; break;
      case 9: MP=8; break;
      case 10: MP=5; break;
      case 11: MP=2; break;
      case 12: MP=14; break;
      case 13: MP=7; break;
      case 14: MP=4; break;
      case 15: MP=1; break;
      default: break;
   }
}
VOID KEY_4X4(){
   KEYPRESS();
   IF (MP!=0XFF) {
      DELAY_MS(10);
      KEYPRESS();
      IF(MP!=0XFF){
         MPT=MP; 
         WHILE(MP!=0XFF) {KEYPRESS();}
         MP=MPT;
      }
   }
}

