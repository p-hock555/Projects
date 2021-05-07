//ISR Global variables
extern volatile unsigned char changed;  // Flag for state change
extern volatile unsigned char count; //keep the low count threshold in an int
extern volatile unsigned char new_state, old_state;
extern volatile unsigned char a, b;

void initialize_ISR(void);