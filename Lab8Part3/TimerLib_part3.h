#define LCD_setup_H_INCLUDED

void Setup_Init(int duty);
void MotorSpeed(double x);
void Keypad_init(void);
int Keypad_Read(void);
void SysTick_ms_delay(int n);
int Press_Convert(int n);
