/*
 * I2C_Driver.h
 *
 *  Created on: Jul 10, 2026
 *      Author: Kenny
 */

#ifndef EEPROM_DRIVER_I2C_DRIVER_H_
#define EEPROM_DRIVER_I2C_DRIVER_H_

#include <stdint.h>

// System Addresses
#define SYSCTL_BASE 0x400FE000
#define RCGCGPIO (*((volatile uint32_t *) (SYSCTL_BASE + 0x608)))
#define RCGCI2C (*((volatile uint32_t *) (SYSCTL_BASE + 0x620)))

// GPIO Base Addresses
#define GPIO_PORTA_APB_BASE 0x40004000
#define GPIO_PORTB_APB_BASE 0x40005000
#define GPIO_PORTC_APB_BASE 0x40006000
#define GPIO_PORTD_APB_BASE 0x40007000
#define GPIO_PORTE_APB_BASE 0x40024000
#define GPIO_PORTF_APB_BASE 0x40025000

// GPIO Offsets
#define GPIOAFSEL_OFFSET 0x420
#define GPIOODR_OFFSET 0x50C
#define GPIOPCTL_OFFSET 0x52C
#define GPIODIR_OFFSET 0x400
#define GPIODEN_OFFSET 0x51C

// I2C Base Addresses
#define I2C0_BASE 0x40020000
#define I2C1_BASE 0x40021000
#define I2C2_BASE 0x40022000
#define I2C3_BASE 0x40023000

// I2C Offsets
#define I2CMCR_OFFSET 0x020
#define I2CMTPR_OFFSET 0x00C
#define I2CMDR_OFFSET 0x008
#define I2CMCS_OFFSET 0x004

// Realistically we can optimize by only using SDA bit to calculate SCL bit
// this would slow startup time by a tiny bit, but saves memory
// However, I didn't really need to optimize and depending on compiling
// padding might not even optimize this instance.
typedef struct {
    uint32_t i2cBase;
    uint32_t gpioBase;
    uint8_t sclk;
    uint8_t sdata;
} I2C_Config;

// Create I2C Config structs for the user to pass into initialization function

const I2C_Config i2c0_config = {
    .i2cBase = I2C0_BASE,
    .gpioBase = GPIO_PORTB_APB_BASE,
    .sclk = (1 << 2),
    .sdata = (1 << 3),
};

const I2C_Config i2c1_config = {
    .i2cBase = I2C1_BASE,
    .gpioBase = GPIO_PORTA_APB_BASE,
    .sclk = (1 << 6),
    .sdata = (1 << 7),
};

const I2C_Config i2c2_config = {
    .i2cBase = I2C2_BASE,
    .gpioBase = GPIO_PORTE_APB_BASE,
    .sclk = (1 << 4),
    .sdata = (1 << 5),
};

const I2C_Config i2c3_config = {
    .i2cBase = I2C3_BASE,
    .gpioBase = GPIO_PORTD_APB_BASE,
    .sclk = (1 << 0),
    .sdata = (1 << 1),
};

void init_i2c(I2C_Config config); // Maybe add Clock Speed
uint32 send_i2c(I2C_Config config, uint8_t slave, uint8_t data); // Returns 0 done, other if error
// uint32 send_multiple(I2C_Config config, uint8_t slave, uint8_t *data, int length);

#endif
