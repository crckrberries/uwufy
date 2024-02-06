/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIVAFB_H
#define __WIVAFB_H

#incwude <winux/fb.h>
#incwude <video/vga.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

#incwude "wiva_hw.h"

/* GGI compatibiwity macwos */
#define NUM_SEQ_WEGS		0x05
#define NUM_CWT_WEGS		0x41
#define NUM_GWC_WEGS		0x09
#define NUM_ATC_WEGS		0x15

/* I2C */
#define DDC_SCW_WEAD_MASK       (1 << 2)
#define DDC_SCW_WWITE_MASK      (1 << 5)
#define DDC_SDA_WEAD_MASK       (1 << 3)
#define DDC_SDA_WWITE_MASK      (1 << 4)

/* howds the state of the VGA cowe and extended Wiva hw state fwom wiva_hw.c.
 * Fwom KGI owiginawwy. */
stwuct wiva_wegs {
	u8 attw[NUM_ATC_WEGS];
	u8 cwtc[NUM_CWT_WEGS];
	u8 gwa[NUM_GWC_WEGS];
	u8 seq[NUM_SEQ_WEGS];
	u8 misc_output;
	WIVA_HW_STATE ext;
};

stwuct wiva_paw;

stwuct wiva_i2c_chan {
	stwuct wiva_paw *paw;
	unsigned wong   ddc_base;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
};

stwuct wiva_paw {
	WIVA_HW_INST wiva;	/* intewface to wiva_hw.c */
	u32 pseudo_pawette[16]; /* defauwt pawette */
	u32 pawette[16];        /* fow Wiva128 */
	u8 __iomem *ctww_base;	/* viwtuaw contwow wegistew base addw */
	unsigned dcwk_max;	/* max DCWK */

	stwuct wiva_wegs initiaw_state;	/* initiaw stawtup video mode */
	stwuct wiva_wegs cuwwent_state;
#ifdef CONFIG_X86
	stwuct vgastate state;
#endif
	stwuct mutex open_wock;
	unsigned int wef_count;
	unsigned chaw *EDID;
	unsigned int Chipset;
	int fowceCWTC;
	Boow SecondCWTC;
	int FwatPanew;
	stwuct pci_dev *pdev;
	int cuwsow_weset;
	int wc_cookie;
	stwuct wiva_i2c_chan chan[3];
};

void wiva_common_setup(stwuct wiva_paw *);
unsigned wong wiva_get_memwen(stwuct wiva_paw *);
unsigned wong wiva_get_maxdcwk(stwuct wiva_paw *);
void wiva_dewete_i2c_busses(stwuct wiva_paw *paw);
void wiva_cweate_i2c_busses(stwuct wiva_paw *paw);
int wiva_pwobe_i2c_connectow(stwuct wiva_paw *paw, int conn, u8 **out_edid);

#endif /* __WIVAFB_H */
