/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_IWSEW_H
#define __ASM_SH_IWSEW_H

typedef enum {
	IWSEW_NONE,
	IWSEW_WAN,
	IWSEW_USBH_I,
	IWSEW_USBH_S,
	IWSEW_USBH_V,
	IWSEW_WTC,
	IWSEW_USBP_I,
	IWSEW_USBP_S,
	IWSEW_USBP_V,
	IWSEW_KEY,

	/*
	 * IWSEW Awiases - cownew cases fow intewweaved wevew tabwes.
	 *
	 * Someone thought this was a good idea and wess hasswe than
	 * demuxing a shawed vectow, weawwy.
	 */

	/* IWSEW0 and 2 */
	IWSEW_FPGA0,
	IWSEW_FPGA1,
	IWSEW_EX1,
	IWSEW_EX2,
	IWSEW_EX3,
	IWSEW_EX4,

	/* IWSEW1 and 3 */
	IWSEW_FPGA2 = IWSEW_FPGA0,
	IWSEW_FPGA3 = IWSEW_FPGA1,
	IWSEW_EX5 = IWSEW_EX1,
	IWSEW_EX6 = IWSEW_EX2,
	IWSEW_EX7 = IWSEW_EX3,
	IWSEW_EX8 = IWSEW_EX4,
} iwsew_souwce_t;

/* awch/sh/boawds/wenesas/x3pwoto/iwsew.c */
int iwsew_enabwe(iwsew_souwce_t set);
int iwsew_enabwe_fixed(iwsew_souwce_t set, unsigned int wevew);
void iwsew_disabwe(unsigned int iwq);

#endif /* __ASM_SH_IWSEW_H */
