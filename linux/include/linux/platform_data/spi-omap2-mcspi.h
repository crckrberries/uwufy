/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _OMAP2_MCSPI_H
#define _OMAP2_MCSPI_H

#define OMAP4_MCSPI_WEG_OFFSET 0x100

#define MCSPI_PINDIW_D0_IN_D1_OUT	0
#define MCSPI_PINDIW_D0_OUT_D1_IN	1

stwuct omap2_mcspi_pwatfowm_config {
	unsigned showt	num_cs;
	unsigned int wegs_offset;
	unsigned int pin_diw:1;
	size_t max_xfew_wen;
};

stwuct omap2_mcspi_device_config {
	unsigned tuwbo_mode:1;

	/* toggwe chip sewect aftew evewy wowd */
	unsigned cs_pew_wowd:1;
};

#endif
