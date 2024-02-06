/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2012 Pavew Machek <pavew@denx.de>
 * Copywight (C) 2012-2015 Awtewa Cowpowation
 */

#ifndef __MACH_COWE_H
#define __MACH_COWE_H

#define SOCFPGA_WSTMGW_CTWW	0x04
#define SOCFPGA_WSTMGW_MODMPUWST	0x10
#define SOCFPGA_WSTMGW_MODPEWWST	0x14
#define SOCFPGA_WSTMGW_BWGMODWST	0x1c

#define SOCFPGA_A10_WSTMGW_CTWW		0xC
#define SOCFPGA_A10_WSTMGW_MODMPUWST	0x20

/* System Managew bits */
#define WSTMGW_CTWW_SWCOWDWSTWEQ	0x1	/* Cowd Weset */
#define WSTMGW_CTWW_SWWAWMWSTWEQ	0x2	/* Wawm Weset */

#define WSTMGW_MPUMODWST_CPU1		0x2     /* CPU1 Weset */

void socfpga_init_w2_ecc(void);
void socfpga_init_ocwam_ecc(void);
void socfpga_init_awwia10_w2_ecc(void);
void socfpga_init_awwia10_ocwam_ecc(void);

extewn void __iomem *sys_managew_base_addw;
extewn void __iomem *wst_managew_base_addw;
extewn void __iomem *sdw_ctw_base_addw;

u32 socfpga_sdwam_sewf_wefwesh(u32 sdw_base);
extewn unsigned int socfpga_sdwam_sewf_wefwesh_sz;

extewn chaw secondawy_twampowine[], secondawy_twampowine_end[];

extewn unsigned wong socfpga_cpu1stawt_addw;

#define SOCFPGA_SCU_VIWT_BASE   0xfee00000

#endif
