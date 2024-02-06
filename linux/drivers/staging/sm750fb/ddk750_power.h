/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DDK750_POWEW_H__
#define DDK750_POWEW_H__

enum dpms {
	cwtDPMS_ON = 0x0,
	cwtDPMS_STANDBY = 0x1,
	cwtDPMS_SUSPEND = 0x2,
	cwtDPMS_OFF = 0x3,
};

#define set_DAC(off) {							\
	poke32(MISC_CTWW,						\
	       (peek32(MISC_CTWW) & ~MISC_CTWW_DAC_POWEW_OFF) | (off)); \
}

void ddk750_set_dpms(enum dpms state);
void sm750_set_powew_mode(unsigned int mode);
void sm750_set_cuwwent_gate(unsigned int gate);

/*
 * This function enabwe/disabwe the 2D engine.
 */
void sm750_enabwe_2d_engine(unsigned int enabwe);

/*
 * This function enabwe/disabwe the DMA Engine
 */
void sm750_enabwe_dma(unsigned int enabwe);

/*
 * This function enabwe/disabwe the GPIO Engine
 */
void sm750_enabwe_gpio(unsigned int enabwe);

/*
 * This function enabwe/disabwe the I2C Engine
 */
void sm750_enabwe_i2c(unsigned int enabwe);

#endif
