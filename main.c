#include <stdint.h>

void init_i2c1(void) {
    // Enable GPIO Clock for Port D
    (*((volatile uint32_t *) (0x400FE608))) |= (0x08);
    // Enable I2C Clock for Module 3
    (*((volatile uint32_t *) (0x400FE620))) |= (0x08);

    // Enable Pins 0 & 1 on Port D
    (*((volatile uint32_t *) (0x4000751C))) |= (0x03);
    // Enable Pins to Alternate Function
    (*((volatile uint32_t *) (0x40007420))) |= (0x03);
    // Allow GPIO Port Control to I2C Function
    (*((volatile uint32_t *) (0x4000752C))) |= (0x33);
    // Enable Open Drain for Pin 1 for SDA Function
    (*((volatile uint32_t *) (0x4000750C))) |= (0x02);
    // Enable I2C3 Master Function
    (*((volatile uint32_t *) (0x40023020))) |= (0x10);
    // Set Frequency of I2C
    (*((volatile uint32_t *) (0x4002300C))) = (0x07);
}

void send_i2c1(void) {
    // MSA set to 0x57 shifted 1 to transmit
    (*((volatile uint32_t *) (0x40023000))) = (0x57 << 1);
    // MDR set to 0x59 for Y
    (*((volatile uint32_t *) (0x40023008))) = (0x59);
    // MCS set to 0x07 for STOP, START, RUN
    (*((volatile uint32_t *) (0x40023004))) = (0x07);
    // Poll busy bit on I2C
    while ((*((volatile uint32_t *) (0x40023004))) & 1) { ; }
    // Check Error with Debug
    int error = (*((volatile uint32_t *) (0x40023004)));
}


int main(void)
{
    init_i2c1();

    while (1) {
        send_i2c1();
        int i;
        for (i=0; i<100000; i++) {
            ;
        }
    }

	return 0;
}
