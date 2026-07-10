#include <stdint.h>

#define SYSCTL_BASE 0x400FE000

#define GPIO_PORTA_APB_BASE 0x40004000
#define GPIOA_APB_GPIOAFSEL (*((volatile uint32_t *) (GPIO_PORTA_APB_BASE + 0x420)))
#define GPIOA_APB_GPIOODR (*((volatile uint32_t *) (GPIO_PORTA_APB_BASE + 0x50C)))
#define GPIOA_APB_GPIOPCTL (*((volatile uint32_t *) (GPIO_PORTA_APB_BASE + 0x52C)))
#define GPIODIR_OFFSET 0x0400
#define GPIODEN_OFFSET 0x051C

#define RCGCGPIO (*((volatile uint32_t *) (SYSCTL_BASE + 0x608)))
#define RCGCI2C (*((volatile uint32_t *) (SYSCTL_BASE + 0x620)))

#define I2C0_BASE 0x40020000
#define I2C1_BASE 0x40021000
#define I2C2_BASE 0x40022000
#define I2C3_BASE 0x40023000

#define I2CMCR_OFFSET 0x020
#define I2CMTPR_OFFSET 0x00C
#define I2CMDR_OFFSET 0x008
#define I2CMCS_OFFSET 0x004

void init_i2c1(void) {
    // Enable Clock for I2C1
    RCGCI2C |= 2;

    // Enable Clock for GPIO for Pins PA6 & PA7
    RCGCGPIO |= 1;
    // Setup Pin7 for Outputs (GPIODIR)
    (*((volatile uint32_t *) (GPIO_PORTA_APB_BASE + GPIODIR_OFFSET))) |= (3 << 6);          // Set bit [7]
    // Digital Enable Pin6 & Pin7 (GPIODEN)
    (*((volatile uint32_t *) (GPIO_PORTA_APB_BASE + GPIODEN_OFFSET))) |= (3 << 6);
    // Set Alternate Function for Pins PA6 & PA7 (GPIOAFSEL)
    GPIOA_APB_GPIOAFSEL |= (3 << 6);
    // Configure Pins PA6 & PA7 for I2C (GPIOPCTL)
    GPIOA_APB_GPIOPCTL |= (3 << 24);
    GPIOA_APB_GPIOPCTL |= (3 << 28);

    // Configure Pins PA7 for Open Drain SDA (GPIOODR)
    GPIOA_APB_GPIOODR |= (1 << 7);


    // Enable Master Configuration for I2C1 (I2CMCR)
    (*((volatile uint32_t *) (I2C1_BASE + I2CMCR_OFFSET))) |= (0x10);
    // Set the I2C Clock Speed (I2CMTPR)
    (*((volatile uint32_t *) (I2C1_BASE + I2CMTPR_OFFSET))) = 0x0; // Set to 100Kbps
}

void send_i2c1(void) {
    // Set Master Slave Address to 1010 111_ I2CMSA
    (*((volatile uint32_t *) (I2C1_BASE + 0x000))) |= (0x76);
    // Clear Bit 0 to Transmit
    (*((volatile uint32_t *) (I2C1_BASE + 0x000))) &= ~(0x01);

    // Place Data Byte into I2CMDR
    (*((volatile uint32_t *) (I2C1_BASE + I2CMDR_OFFSET))) |= (0x59);
    // Initiate Single Byte Transmit with 0x07
    (*((volatile uint32_t *) (I2C1_BASE + I2CMCS_OFFSET))) = (0x09);

    // Check transmission completion
    while ((*((volatile uint32_t *) (I2C1_BASE + I2CMCS_OFFSET))) & 0x40) { ; }

    int error = (*((volatile uint32_t *) (I2C1_BASE + I2CMCS_OFFSET))) & 0x02;
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