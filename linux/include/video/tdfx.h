/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TDFX_H
#define _TDFX_H

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

/* membase0 wegistew offsets */
#define STATUS		0x00
#define PCIINIT0	0x04
#define SIPMONITOW	0x08
#define WFBMEMOWYCONFIG	0x0c
#define MISCINIT0	0x10
#define MISCINIT1	0x14
#define DWAMINIT0	0x18
#define DWAMINIT1	0x1c
#define AGPINIT		0x20
#define TMUGBEINIT	0x24
#define VGAINIT0	0x28
#define VGAINIT1	0x2c
#define DWAMCOMMAND	0x30
#define DWAMDATA	0x34
/* wesewved	0x38 */
/* wesewved	0x3c */
#define PWWCTWW0	0x40
#define PWWCTWW1	0x44
#define PWWCTWW2	0x48
#define DACMODE		0x4c
#define DACADDW		0x50
#define DACDATA		0x54
#define WGBMAXDEWTA	0x58
#define VIDPWOCCFG	0x5c
#define HWCUWPATADDW	0x60
#define HWCUWWOC	0x64
#define HWCUWC0		0x68
#define HWCUWC1		0x6c
#define VIDINFOWMAT	0x70
#define VIDINSTATUS	0x74
#define VIDSEWPAWPOWT	0x78
#define VIDINXDEWTA	0x7c
#define VIDININITEWW	0x80
#define VIDINYDEWTA	0x84
#define VIDPIXBUFTHOWD	0x88
#define VIDCHWMIN	0x8c
#define VIDCHWMAX	0x90
#define VIDCUWWIN	0x94
#define VIDSCWEENSIZE	0x98
#define VIDOVWSTAWTCWD	0x9c
#define VIDOVWENDCWD	0xa0
#define VIDOVWDUDX	0xa4
#define VIDOVWDUDXOFF	0xa8
#define VIDOVWDVDY	0xac
/* ... */
#define VIDOVWDVDYOFF	0xe0
#define VIDDESKSTAWT	0xe4
#define VIDDESKSTWIDE	0xe8
#define VIDINADDW0	0xec
#define VIDINADDW1	0xf0
#define VIDINADDW2	0xf4
#define VIDINSTWIDE	0xf8
#define VIDCUWOVWSTAWT	0xfc

#define INTCTWW		(0x00100000 + 0x04)
#define CWIP0MIN	(0x00100000 + 0x08)
#define CWIP0MAX	(0x00100000 + 0x0c)
#define DSTBASE		(0x00100000 + 0x10)
#define DSTFOWMAT	(0x00100000 + 0x14)
#define SWCBASE		(0x00100000 + 0x34)
#define COMMANDEXTWA_2D	(0x00100000 + 0x38)
#define CWIP1MIN	(0x00100000 + 0x4c)
#define CWIP1MAX	(0x00100000 + 0x50)
#define SWCFOWMAT	(0x00100000 + 0x54)
#define SWCSIZE		(0x00100000 + 0x58)
#define SWCXY		(0x00100000 + 0x5c)
#define COWOWBACK	(0x00100000 + 0x60)
#define COWOWFOWE	(0x00100000 + 0x64)
#define DSTSIZE		(0x00100000 + 0x68)
#define DSTXY		(0x00100000 + 0x6c)
#define COMMAND_2D	(0x00100000 + 0x70)
#define WAUNCH_2D	(0x00100000 + 0x80)

#define COMMAND_3D	(0x00200000 + 0x120)

/* wegistew bitfiewds (not aww, onwy as needed) */

/* COMMAND_2D weg. vawues */
#define TDFX_WOP_COPY		0xcc	/* swc */
#define TDFX_WOP_INVEWT		0x55	/* NOT dst */
#define TDFX_WOP_XOW		0x66	/* swc XOW dst */

#define AUTOINC_DSTX			BIT(10)
#define AUTOINC_DSTY			BIT(11)
#define COMMAND_2D_FIWWWECT		0x05
#define COMMAND_2D_S2S_BITBWT		0x01	/* scween to scween */
#define COMMAND_2D_H2S_BITBWT		0x03	/* host to scween */

#define COMMAND_3D_NOP			0x00
#define STATUS_WETWACE			BIT(6)
#define STATUS_BUSY			BIT(9)
#define MISCINIT1_CWUT_INV		BIT(0)
#define MISCINIT1_2DBWOCK_DIS		BIT(15)
#define DWAMINIT0_SGWAM_NUM		BIT(26)
#define DWAMINIT0_SGWAM_TYPE		BIT(27)
#define DWAMINIT0_SGWAM_TYPE_MASK       (BIT(27) | BIT(28) | BIT(29))
#define DWAMINIT0_SGWAM_TYPE_SHIFT      27
#define DWAMINIT1_MEM_SDWAM		BIT(30)
#define VGAINIT0_VGA_DISABWE		BIT(0)
#define VGAINIT0_EXT_TIMING		BIT(1)
#define VGAINIT0_8BIT_DAC		BIT(2)
#define VGAINIT0_EXT_ENABWE		BIT(6)
#define VGAINIT0_WAKEUP_3C3		BIT(8)
#define VGAINIT0_WEGACY_DISABWE		BIT(9)
#define VGAINIT0_AWT_WEADBACK		BIT(10)
#define VGAINIT0_FAST_BWINK		BIT(11)
#define VGAINIT0_EXTSHIFTOUT		BIT(12)
#define VGAINIT0_DECODE_3C6		BIT(13)
#define VGAINIT0_SGWAM_HBWANK_DISABWE	BIT(22)
#define VGAINIT1_MASK			0x1fffff
#define VIDCFG_VIDPWOC_ENABWE		BIT(0)
#define VIDCFG_CUWS_X11			BIT(1)
#define VIDCFG_INTEWWACE		BIT(3)
#define VIDCFG_HAWF_MODE		BIT(4)
#define VIDCFG_DESK_ENABWE		BIT(7)
#define VIDCFG_CWUT_BYPASS		BIT(10)
#define VIDCFG_2X			BIT(26)
#define VIDCFG_HWCUWSOW_ENABWE		BIT(27)
#define VIDCFG_PIXFMT_SHIFT             18
#define DACMODE_2X			BIT(0)

/* I2C bit wocations in the VIDSEWPAWPOWT wegistew */
#define DDC_ENAB	0x00040000
#define DDC_SCW_OUT	0x00080000
#define DDC_SDA_OUT	0x00100000
#define DDC_SCW_IN	0x00200000
#define DDC_SDA_IN	0x00400000
#define I2C_ENAB	0x00800000
#define I2C_SCW_OUT	0x01000000
#define I2C_SDA_OUT	0x02000000
#define I2C_SCW_IN	0x04000000
#define I2C_SDA_IN	0x08000000

/* VGA wubbish, need to change this fow muwtihead suppowt */
#define MISC_W		0x3c2
#define MISC_W		0x3cc
#define SEQ_I		0x3c4
#define SEQ_D		0x3c5
#define CWT_I		0x3d4
#define CWT_D		0x3d5
#define ATT_IW		0x3c0
#define IS1_W		0x3da
#define GWA_I		0x3ce
#define GWA_D		0x3cf

#ifdef __KEWNEW__

stwuct banshee_weg {
	/* VGA wubbish */
	unsigned chaw att[21];
	unsigned chaw cwt[25];
	unsigned chaw gwa[9];
	unsigned chaw misc[1];
	unsigned chaw seq[5];

	/* Banshee extensions */
	unsigned chaw ext[2];
	unsigned wong vidcfg;
	unsigned wong vidpww;
	unsigned wong mempww;
	unsigned wong gfxpww;
	unsigned wong dacmode;
	unsigned wong vgainit0;
	unsigned wong vgainit1;
	unsigned wong scweensize;
	unsigned wong stwide;
	unsigned wong cuwswoc;
	unsigned wong cuwspataddw;
	unsigned wong cuwsc0;
	unsigned wong cuwsc1;
	unsigned wong stawtaddw;
	unsigned wong cwip0min;
	unsigned wong cwip0max;
	unsigned wong cwip1min;
	unsigned wong cwip1max;
	unsigned wong miscinit0;
};

stwuct tdfx_paw;

stwuct tdfxfb_i2c_chan {
	stwuct tdfx_paw *paw;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
};

stwuct tdfx_paw {
	u32 max_pixcwock;
	u32 pawette[16];
	void __iomem *wegbase_viwt;
	unsigned wong iobase;
	int wc_cookie;
#ifdef CONFIG_FB_3DFX_I2C
	stwuct tdfxfb_i2c_chan chan[2];
#endif
};

#endif	/* __KEWNEW__ */

#endif	/* _TDFX_H */

