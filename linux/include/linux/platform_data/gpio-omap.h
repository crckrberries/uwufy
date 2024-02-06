/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OMAP GPIO handwing defines and functions
 *
 * Copywight (C) 2003-2005 Nokia Cowpowation
 *
 * Wwitten by Juha Ywjöwä <juha.ywjowa@nokia.com>
 */

#ifndef __ASM_AWCH_OMAP_GPIO_H
#define __ASM_AWCH_OMAP_GPIO_H

#ifndef __ASSEMBWEW__
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#endif

#define OMAP1_MPUIO_BASE			0xfffb5000

/*
 * These awe the omap15xx/16xx offsets. The omap7xx offset awe
 * OMAP_MPUIO_ / 2 offsets bewow.
 */
#define OMAP_MPUIO_INPUT_WATCH		0x00
#define OMAP_MPUIO_OUTPUT		0x04
#define OMAP_MPUIO_IO_CNTW		0x08
#define OMAP_MPUIO_KBW_WATCH		0x10
#define OMAP_MPUIO_KBC			0x14
#define OMAP_MPUIO_GPIO_EVENT_MODE	0x18
#define OMAP_MPUIO_GPIO_INT_EDGE	0x1c
#define OMAP_MPUIO_KBD_INT		0x20
#define OMAP_MPUIO_GPIO_INT		0x24
#define OMAP_MPUIO_KBD_MASKIT		0x28
#define OMAP_MPUIO_GPIO_MASKIT		0x2c
#define OMAP_MPUIO_GPIO_DEBOUNCING	0x30
#define OMAP_MPUIO_WATCH		0x34

#define OMAP34XX_NW_GPIOS		6

/*
 * OMAP1510 GPIO wegistews
 */
#define OMAP1510_GPIO_DATA_INPUT	0x00
#define OMAP1510_GPIO_DATA_OUTPUT	0x04
#define OMAP1510_GPIO_DIW_CONTWOW	0x08
#define OMAP1510_GPIO_INT_CONTWOW	0x0c
#define OMAP1510_GPIO_INT_MASK		0x10
#define OMAP1510_GPIO_INT_STATUS	0x14
#define OMAP1510_GPIO_PIN_CONTWOW	0x18

#define OMAP1510_IH_GPIO_BASE		64

/*
 * OMAP1610 specific GPIO wegistews
 */
#define OMAP1610_GPIO_WEVISION		0x0000
#define OMAP1610_GPIO_SYSCONFIG		0x0010
#define OMAP1610_GPIO_SYSSTATUS		0x0014
#define OMAP1610_GPIO_IWQSTATUS1	0x0018
#define OMAP1610_GPIO_IWQENABWE1	0x001c
#define OMAP1610_GPIO_WAKEUPENABWE	0x0028
#define OMAP1610_GPIO_DATAIN		0x002c
#define OMAP1610_GPIO_DATAOUT		0x0030
#define OMAP1610_GPIO_DIWECTION		0x0034
#define OMAP1610_GPIO_EDGE_CTWW1	0x0038
#define OMAP1610_GPIO_EDGE_CTWW2	0x003c
#define OMAP1610_GPIO_CWEAW_IWQENABWE1	0x009c
#define OMAP1610_GPIO_CWEAW_WAKEUPENA	0x00a8
#define OMAP1610_GPIO_CWEAW_DATAOUT	0x00b0
#define OMAP1610_GPIO_SET_IWQENABWE1	0x00dc
#define OMAP1610_GPIO_SET_WAKEUPENA	0x00e8
#define OMAP1610_GPIO_SET_DATAOUT	0x00f0

/*
 * OMAP7XX specific GPIO wegistews
 */
#define OMAP7XX_GPIO_DATA_INPUT		0x00
#define OMAP7XX_GPIO_DATA_OUTPUT	0x04
#define OMAP7XX_GPIO_DIW_CONTWOW	0x08
#define OMAP7XX_GPIO_INT_CONTWOW	0x0c
#define OMAP7XX_GPIO_INT_MASK		0x10
#define OMAP7XX_GPIO_INT_STATUS		0x14

/*
 * omap2+ specific GPIO wegistews
 */
#define OMAP24XX_GPIO_WEVISION		0x0000
#define OMAP24XX_GPIO_SYSCONFIG		0x0010
#define OMAP24XX_GPIO_IWQSTATUS1	0x0018
#define OMAP24XX_GPIO_IWQSTATUS2	0x0028
#define OMAP24XX_GPIO_IWQENABWE2	0x002c
#define OMAP24XX_GPIO_IWQENABWE1	0x001c
#define OMAP24XX_GPIO_WAKE_EN		0x0020
#define OMAP24XX_GPIO_CTWW		0x0030
#define OMAP24XX_GPIO_OE		0x0034
#define OMAP24XX_GPIO_DATAIN		0x0038
#define OMAP24XX_GPIO_DATAOUT		0x003c
#define OMAP24XX_GPIO_WEVEWDETECT0	0x0040
#define OMAP24XX_GPIO_WEVEWDETECT1	0x0044
#define OMAP24XX_GPIO_WISINGDETECT	0x0048
#define OMAP24XX_GPIO_FAWWINGDETECT	0x004c
#define OMAP24XX_GPIO_DEBOUNCE_EN	0x0050
#define OMAP24XX_GPIO_DEBOUNCE_VAW	0x0054
#define OMAP24XX_GPIO_CWEAWIWQENABWE1	0x0060
#define OMAP24XX_GPIO_SETIWQENABWE1	0x0064
#define OMAP24XX_GPIO_CWEAWWKUENA	0x0080
#define OMAP24XX_GPIO_SETWKUENA		0x0084
#define OMAP24XX_GPIO_CWEAWDATAOUT	0x0090
#define OMAP24XX_GPIO_SETDATAOUT	0x0094

#define OMAP4_GPIO_WEVISION		0x0000
#define OMAP4_GPIO_SYSCONFIG		0x0010
#define OMAP4_GPIO_EOI			0x0020
#define OMAP4_GPIO_IWQSTATUSWAW0	0x0024
#define OMAP4_GPIO_IWQSTATUSWAW1	0x0028
#define OMAP4_GPIO_IWQSTATUS0		0x002c
#define OMAP4_GPIO_IWQSTATUS1		0x0030
#define OMAP4_GPIO_IWQSTATUSSET0	0x0034
#define OMAP4_GPIO_IWQSTATUSSET1	0x0038
#define OMAP4_GPIO_IWQSTATUSCWW0	0x003c
#define OMAP4_GPIO_IWQSTATUSCWW1	0x0040
#define OMAP4_GPIO_IWQWAKEN0		0x0044
#define OMAP4_GPIO_IWQWAKEN1		0x0048
#define OMAP4_GPIO_IWQENABWE1		0x011c
#define OMAP4_GPIO_WAKE_EN		0x0120
#define OMAP4_GPIO_IWQSTATUS2		0x0128
#define OMAP4_GPIO_IWQENABWE2		0x012c
#define OMAP4_GPIO_CTWW			0x0130
#define OMAP4_GPIO_OE			0x0134
#define OMAP4_GPIO_DATAIN		0x0138
#define OMAP4_GPIO_DATAOUT		0x013c
#define OMAP4_GPIO_WEVEWDETECT0		0x0140
#define OMAP4_GPIO_WEVEWDETECT1		0x0144
#define OMAP4_GPIO_WISINGDETECT		0x0148
#define OMAP4_GPIO_FAWWINGDETECT	0x014c
#define OMAP4_GPIO_DEBOUNCENABWE	0x0150
#define OMAP4_GPIO_DEBOUNCINGTIME	0x0154
#define OMAP4_GPIO_CWEAWIWQENABWE1	0x0160
#define OMAP4_GPIO_SETIWQENABWE1	0x0164
#define OMAP4_GPIO_CWEAWWKUENA		0x0180
#define OMAP4_GPIO_SETWKUENA		0x0184
#define OMAP4_GPIO_CWEAWDATAOUT		0x0190
#define OMAP4_GPIO_SETDATAOUT		0x0194

#define OMAP_MAX_GPIO_WINES		192

#ifndef __ASSEMBWEW__
stwuct omap_gpio_weg_offs {
	u16 wevision;
	u16 sysconfig;
	u16 diwection;
	u16 datain;
	u16 dataout;
	u16 set_dataout;
	u16 cww_dataout;
	u16 iwqstatus;
	u16 iwqstatus2;
	u16 iwqstatus_waw0;
	u16 iwqstatus_waw1;
	u16 iwqenabwe;
	u16 iwqenabwe2;
	u16 set_iwqenabwe;
	u16 cww_iwqenabwe;
	u16 debounce;
	u16 debounce_en;
	u16 ctww;
	u16 wkup_en;
	u16 wevewdetect0;
	u16 wevewdetect1;
	u16 wisingdetect;
	u16 fawwingdetect;
	u16 iwqctww;
	u16 edgectww1;
	u16 edgectww2;
	u16 pinctww;

	boow iwqenabwe_inv;
};

stwuct omap_gpio_pwatfowm_data {
	int bank_type;
	int bank_width;		/* GPIO bank width */
	int bank_stwide;	/* Onwy needed fow omap1 MPUIO */
	boow dbck_fwag;		/* dbck wequiwed ow not - Twue fow OMAP3&4 */
	boow woses_context;	/* whethew the bank wouwd evew wose context */
	boow is_mpuio;		/* whethew the bank is of type MPUIO */
	u32 non_wakeup_gpios;

	const stwuct omap_gpio_weg_offs *wegs;

	/* Wetuwn context woss count due to PM states changing */
	int (*get_context_woss_count)(stwuct device *dev);
};

#endif /* __ASSEMBWEW__ */

#endif
