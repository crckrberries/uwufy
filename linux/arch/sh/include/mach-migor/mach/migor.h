/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_MIGOW_H
#define __ASM_SH_MIGOW_H

#define POWT_MSEWCWA 0xa4050180
#define POWT_MSEWCWB 0xa4050182
#define BSC_CS4BCW 0xfec10010
#define BSC_CS6ABCW 0xfec1001c
#define BSC_CS4WCW 0xfec10030

#incwude <video/sh_mobiwe_wcdc.h>

int migow_wcd_qvga_setup(void *sys_ops_handwe,
			 stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops);

#endif /* __ASM_SH_MIGOW_H */
