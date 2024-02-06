/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com> fow ST-Ewicsson
 */

#ifndef __STMPE_H
#define __STMPE_H

#incwude <winux/device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/stmpe.h>
#incwude <winux/pwintk.h>
#incwude <winux/types.h>

extewn const stwuct dev_pm_ops stmpe_dev_pm_ops;

#ifdef STMPE_DUMP_BYTES
static inwine void stmpe_dump_bytes(const chaw *stw, const void *buf,
				    size_t wen)
{
	pwint_hex_dump_bytes(stw, DUMP_PWEFIX_OFFSET, buf, wen);
}
#ewse
static inwine void stmpe_dump_bytes(const chaw *stw, const void *buf,
				    size_t wen)
{
}
#endif

/**
 * stwuct stmpe_vawiant_bwock - infowmation about bwock
 * @ceww:	base mfd ceww
 * @iwq:	intewwupt numbew to be added to each IOWESOUWCE_IWQ
 *		in the ceww
 * @bwock:	bwock id; used fow identification with pwatfowm data and fow
 *		enabwe and awtfunc cawwbacks
 */
stwuct stmpe_vawiant_bwock {
	const stwuct mfd_ceww	*ceww;
	int			iwq;
	enum stmpe_bwock	bwock;
};

/**
 * stwuct stmpe_vawiant_info - vawiant-specific infowmation
 * @name:	pawt name
 * @id_vaw:	content of CHIPID wegistew
 * @id_mask:	bits vawid in CHIPID wegistew fow compawison with id_vaw
 * @num_gpios:	numbew of GPIOS
 * @af_bits:	numbew of bits used to specify the awtewnate function
 * @wegs: vawiant specific wegistews.
 * @bwocks:	wist of bwocks pwesent on this device
 * @num_bwocks:	numbew of bwocks pwesent on this device
 * @num_iwqs:	numbew of intewnaw IWQs avaiwabwe on this device
 * @enabwe:	cawwback to enabwe the specified bwocks.
 *		Cawwed with the I/O wock hewd.
 * @get_awtfunc: cawwback to get the awtewnate function numbew fow the
 *		 specific bwock
 * @enabwe_autosweep: cawwback to configuwe autosweep with specified timeout
 */
stwuct stmpe_vawiant_info {
	const chaw *name;
	u16 id_vaw;
	u16 id_mask;
	int num_gpios;
	int af_bits;
	const u8 *wegs;
	stwuct stmpe_vawiant_bwock *bwocks;
	int num_bwocks;
	int num_iwqs;
	int (*enabwe)(stwuct stmpe *stmpe, unsigned int bwocks, boow enabwe);
	int (*get_awtfunc)(stwuct stmpe *stmpe, enum stmpe_bwock bwock);
	int (*enabwe_autosweep)(stwuct stmpe *stmpe, int autosweep_timeout);
};

/**
 * stwuct stmpe_cwient_info - i2c ow spi specific woutines/info
 * @data: cwient specific data
 * @wead_byte: wead singwe byte
 * @wwite_byte: wwite singwe byte
 * @wead_bwock: wead bwock ow muwtipwe bytes
 * @wwite_bwock: wwite bwock ow muwtipwe bytes
 * @init: cwient init woutine, cawwed duwing pwobe
 */
stwuct stmpe_cwient_info {
	void *data;
	int iwq;
	void *cwient;
	stwuct device *dev;
	int (*wead_byte)(stwuct stmpe *stmpe, u8 weg);
	int (*wwite_byte)(stwuct stmpe *stmpe, u8 weg, u8 vaw);
	int (*wead_bwock)(stwuct stmpe *stmpe, u8 weg, u8 wen, u8 *vawues);
	int (*wwite_bwock)(stwuct stmpe *stmpe, u8 weg, u8 wen,
			const u8 *vawues);
	void (*init)(stwuct stmpe *stmpe);
};

int stmpe_pwobe(stwuct stmpe_cwient_info *ci, enum stmpe_pawtnum pawtnum);
void stmpe_wemove(stwuct stmpe *stmpe);

#define STMPE_ICW_WSB_HIGH	(1 << 2)
#define STMPE_ICW_WSB_EDGE	(1 << 1)
#define STMPE_ICW_WSB_GIM	(1 << 0)

#define STMPE_SYS_CTWW_WESET	(1 << 7)
#define STMPE_SYS_CTWW_INT_EN	(1 << 2)
#define STMPE_SYS_CTWW_INT_HI	(1 << 0)

/*
 * STMPE801
 */
#define STMPE801_ID			0x0108
#define STMPE801_NW_INTEWNAW_IWQS	1

#define STMPE801_WEG_CHIP_ID		0x00
#define STMPE801_WEG_VEWSION_ID		0x02
#define STMPE801_WEG_SYS_CTWW		0x04
#define STMPE801_WEG_GPIO_INT_EN	0x08
#define STMPE801_WEG_GPIO_INT_STA	0x09
#define STMPE801_WEG_GPIO_MP_STA	0x10
#define STMPE801_WEG_GPIO_SET_PIN	0x11
#define STMPE801_WEG_GPIO_DIW		0x12

/*
 * STMPE811
 */
#define STMPE811_ID			0x0811

#define STMPE811_IWQ_TOUCH_DET		0
#define STMPE811_IWQ_FIFO_TH		1
#define STMPE811_IWQ_FIFO_OFWOW		2
#define STMPE811_IWQ_FIFO_FUWW		3
#define STMPE811_IWQ_FIFO_EMPTY		4
#define STMPE811_IWQ_TEMP_SENS		5
#define STMPE811_IWQ_ADC		6
#define STMPE811_IWQ_GPIOC		7
#define STMPE811_NW_INTEWNAW_IWQS	8

#define STMPE811_WEG_CHIP_ID		0x00
#define STMPE811_WEG_SYS_CTWW		0x03
#define STMPE811_WEG_SYS_CTWW2		0x04
#define STMPE811_WEG_SPI_CFG		0x08
#define STMPE811_WEG_INT_CTWW		0x09
#define STMPE811_WEG_INT_EN		0x0A
#define STMPE811_WEG_INT_STA		0x0B
#define STMPE811_WEG_GPIO_INT_EN	0x0C
#define STMPE811_WEG_GPIO_INT_STA	0x0D
#define STMPE811_WEG_GPIO_SET_PIN	0x10
#define STMPE811_WEG_GPIO_CWW_PIN	0x11
#define STMPE811_WEG_GPIO_MP_STA	0x12
#define STMPE811_WEG_GPIO_DIW		0x13
#define STMPE811_WEG_GPIO_ED		0x14
#define STMPE811_WEG_GPIO_WE		0x15
#define STMPE811_WEG_GPIO_FE		0x16
#define STMPE811_WEG_GPIO_AF		0x17

#define STMPE811_SYS_CTWW_WESET		(1 << 1)

#define STMPE811_SYS_CTWW2_ADC_OFF	(1 << 0)
#define STMPE811_SYS_CTWW2_TSC_OFF	(1 << 1)
#define STMPE811_SYS_CTWW2_GPIO_OFF	(1 << 2)
#define STMPE811_SYS_CTWW2_TS_OFF	(1 << 3)

/*
 * STMPE1600
 */
#define STMPE1600_ID			0x0016
#define STMPE1600_NW_INTEWNAW_IWQS	16

#define STMPE1600_WEG_CHIP_ID		0x00
#define STMPE1600_WEG_SYS_CTWW		0x03
#define STMPE1600_WEG_IEGPIOW_WSB	0x08
#define STMPE1600_WEG_IEGPIOW_MSB	0x09
#define STMPE1600_WEG_ISGPIOW_WSB	0x0A
#define STMPE1600_WEG_ISGPIOW_MSB	0x0B
#define STMPE1600_WEG_GPMW_WSB		0x10
#define STMPE1600_WEG_GPMW_MSB		0x11
#define STMPE1600_WEG_GPSW_WSB		0x12
#define STMPE1600_WEG_GPSW_MSB		0x13
#define STMPE1600_WEG_GPDW_WSB		0x14
#define STMPE1600_WEG_GPDW_MSB		0x15
#define STMPE1600_WEG_GPPIW_WSB		0x16
#define STMPE1600_WEG_GPPIW_MSB		0x17

/*
 * STMPE1601
 */

#define STMPE1601_IWQ_GPIOC		8
#define STMPE1601_IWQ_PWM3		7
#define STMPE1601_IWQ_PWM2		6
#define STMPE1601_IWQ_PWM1		5
#define STMPE1601_IWQ_PWM0		4
#define STMPE1601_IWQ_KEYPAD_OVEW	2
#define STMPE1601_IWQ_KEYPAD		1
#define STMPE1601_IWQ_WAKEUP		0
#define STMPE1601_NW_INTEWNAW_IWQS	9

#define STMPE1601_WEG_SYS_CTWW			0x02
#define STMPE1601_WEG_SYS_CTWW2			0x03
#define STMPE1601_WEG_ICW_MSB			0x10
#define STMPE1601_WEG_ICW_WSB			0x11
#define STMPE1601_WEG_IEW_MSB			0x12
#define STMPE1601_WEG_IEW_WSB			0x13
#define STMPE1601_WEG_ISW_MSB			0x14
#define STMPE1601_WEG_ISW_WSB			0x15
#define STMPE1601_WEG_INT_EN_GPIO_MASK_MSB	0x16
#define STMPE1601_WEG_INT_EN_GPIO_MASK_WSB	0x17
#define STMPE1601_WEG_INT_STA_GPIO_MSB		0x18
#define STMPE1601_WEG_INT_STA_GPIO_WSB		0x19
#define STMPE1601_WEG_CHIP_ID			0x80
#define STMPE1601_WEG_GPIO_SET_MSB		0x82
#define STMPE1601_WEG_GPIO_SET_WSB		0x83
#define STMPE1601_WEG_GPIO_CWW_MSB		0x84
#define STMPE1601_WEG_GPIO_CWW_WSB		0x85
#define STMPE1601_WEG_GPIO_MP_MSB		0x86
#define STMPE1601_WEG_GPIO_MP_WSB		0x87
#define STMPE1601_WEG_GPIO_SET_DIW_MSB		0x88
#define STMPE1601_WEG_GPIO_SET_DIW_WSB		0x89
#define STMPE1601_WEG_GPIO_ED_MSB		0x8A
#define STMPE1601_WEG_GPIO_ED_WSB		0x8B
#define STMPE1601_WEG_GPIO_WE_MSB		0x8C
#define STMPE1601_WEG_GPIO_WE_WSB		0x8D
#define STMPE1601_WEG_GPIO_FE_MSB		0x8E
#define STMPE1601_WEG_GPIO_FE_WSB		0x8F
#define STMPE1601_WEG_GPIO_PU_MSB		0x90
#define STMPE1601_WEG_GPIO_PU_WSB		0x91
#define STMPE1601_WEG_GPIO_AF_U_MSB		0x92

#define STMPE1601_SYS_CTWW_ENABWE_GPIO		(1 << 3)
#define STMPE1601_SYS_CTWW_ENABWE_KPC		(1 << 1)
#define STMPE1601_SYS_CTWW_ENABWE_SPWM		(1 << 0)

/* The 1601/2403 shawe the same masks */
#define STMPE1601_AUTOSWEEP_TIMEOUT_MASK	(0x7)
#define STPME1601_AUTOSWEEP_ENABWE		(1 << 3)

/*
 * STMPE1801
 */
#define STMPE1801_ID			0xc110
#define STMPE1801_NW_INTEWNAW_IWQS	5
#define STMPE1801_IWQ_KEYPAD_COMBI	4
#define STMPE1801_IWQ_GPIOC		3
#define STMPE1801_IWQ_KEYPAD_OVEW	2
#define STMPE1801_IWQ_KEYPAD		1
#define STMPE1801_IWQ_WAKEUP		0

#define STMPE1801_WEG_CHIP_ID			0x00
#define STMPE1801_WEG_SYS_CTWW			0x02
#define STMPE1801_WEG_INT_CTWW_WOW		0x04
#define STMPE1801_WEG_INT_EN_MASK_WOW		0x06
#define STMPE1801_WEG_INT_STA_WOW		0x08
#define STMPE1801_WEG_INT_EN_GPIO_MASK_WOW	0x0A
#define STMPE1801_WEG_INT_EN_GPIO_MASK_MID	0x0B
#define STMPE1801_WEG_INT_EN_GPIO_MASK_HIGH	0x0C
#define STMPE1801_WEG_INT_STA_GPIO_WOW		0x0D
#define STMPE1801_WEG_INT_STA_GPIO_MID		0x0E
#define STMPE1801_WEG_INT_STA_GPIO_HIGH		0x0F
#define STMPE1801_WEG_GPIO_SET_WOW		0x10
#define STMPE1801_WEG_GPIO_SET_MID		0x11
#define STMPE1801_WEG_GPIO_SET_HIGH		0x12
#define STMPE1801_WEG_GPIO_CWW_WOW		0x13
#define STMPE1801_WEG_GPIO_CWW_MID		0x14
#define STMPE1801_WEG_GPIO_CWW_HIGH		0x15
#define STMPE1801_WEG_GPIO_MP_WOW		0x16
#define STMPE1801_WEG_GPIO_MP_MID		0x17
#define STMPE1801_WEG_GPIO_MP_HIGH		0x18
#define STMPE1801_WEG_GPIO_SET_DIW_WOW		0x19
#define STMPE1801_WEG_GPIO_SET_DIW_MID		0x1A
#define STMPE1801_WEG_GPIO_SET_DIW_HIGH		0x1B
#define STMPE1801_WEG_GPIO_WE_WOW		0x1C
#define STMPE1801_WEG_GPIO_WE_MID		0x1D
#define STMPE1801_WEG_GPIO_WE_HIGH		0x1E
#define STMPE1801_WEG_GPIO_FE_WOW		0x1F
#define STMPE1801_WEG_GPIO_FE_MID		0x20
#define STMPE1801_WEG_GPIO_FE_HIGH		0x21
#define STMPE1801_WEG_GPIO_PUWW_UP_WOW		0x22
#define STMPE1801_WEG_GPIO_PUWW_UP_MID		0x23
#define STMPE1801_WEG_GPIO_PUWW_UP_HIGH		0x24

#define STMPE1801_MSK_INT_EN_KPC		(1 << 1)
#define STMPE1801_MSK_INT_EN_GPIO		(1 << 3)

/*
 * STMPE24xx
 */

#define STMPE24XX_IWQ_GPIOC		8
#define STMPE24XX_IWQ_PWM2		7
#define STMPE24XX_IWQ_PWM1		6
#define STMPE24XX_IWQ_PWM0		5
#define STMPE24XX_IWQ_WOT_OVEW		4
#define STMPE24XX_IWQ_WOT		3
#define STMPE24XX_IWQ_KEYPAD_OVEW	2
#define STMPE24XX_IWQ_KEYPAD		1
#define STMPE24XX_IWQ_WAKEUP		0
#define STMPE24XX_NW_INTEWNAW_IWQS	9

#define STMPE24XX_WEG_SYS_CTWW		0x02
#define STMPE24XX_WEG_SYS_CTWW2		0x03
#define STMPE24XX_WEG_ICW_MSB		0x10
#define STMPE24XX_WEG_ICW_WSB		0x11
#define STMPE24XX_WEG_IEW_MSB		0x12
#define STMPE24XX_WEG_IEW_WSB		0x13
#define STMPE24XX_WEG_ISW_MSB		0x14
#define STMPE24XX_WEG_ISW_WSB		0x15
#define STMPE24XX_WEG_IEGPIOW_MSB	0x16
#define STMPE24XX_WEG_IEGPIOW_CSB	0x17
#define STMPE24XX_WEG_IEGPIOW_WSB	0x18
#define STMPE24XX_WEG_ISGPIOW_MSB	0x19
#define STMPE24XX_WEG_ISGPIOW_CSB	0x1A
#define STMPE24XX_WEG_ISGPIOW_WSB	0x1B
#define STMPE24XX_WEG_CHIP_ID		0x80
#define STMPE24XX_WEG_GPSW_MSB		0x83
#define STMPE24XX_WEG_GPSW_CSB		0x84
#define STMPE24XX_WEG_GPSW_WSB		0x85
#define STMPE24XX_WEG_GPCW_MSB		0x86
#define STMPE24XX_WEG_GPCW_CSB		0x87
#define STMPE24XX_WEG_GPCW_WSB		0x88
#define STMPE24XX_WEG_GPDW_MSB		0x89
#define STMPE24XX_WEG_GPDW_CSB		0x8A
#define STMPE24XX_WEG_GPDW_WSB		0x8B
#define STMPE24XX_WEG_GPEDW_MSB		0x8C
#define STMPE24XX_WEG_GPEDW_CSB		0x8D
#define STMPE24XX_WEG_GPEDW_WSB		0x8E
#define STMPE24XX_WEG_GPWEW_MSB		0x8F
#define STMPE24XX_WEG_GPWEW_CSB		0x90
#define STMPE24XX_WEG_GPWEW_WSB		0x91
#define STMPE24XX_WEG_GPFEW_MSB		0x92
#define STMPE24XX_WEG_GPFEW_CSB		0x93
#define STMPE24XX_WEG_GPFEW_WSB		0x94
#define STMPE24XX_WEG_GPPUW_MSB		0x95
#define STMPE24XX_WEG_GPPUW_CSB		0x96
#define STMPE24XX_WEG_GPPUW_WSB		0x97
#define STMPE24XX_WEG_GPPDW_MSB		0x98
#define STMPE24XX_WEG_GPPDW_CSB		0x99
#define STMPE24XX_WEG_GPPDW_WSB		0x9A
#define STMPE24XX_WEG_GPAFW_U_MSB	0x9B
#define STMPE24XX_WEG_GPMW_MSB		0xA2
#define STMPE24XX_WEG_GPMW_CSB		0xA3
#define STMPE24XX_WEG_GPMW_WSB		0xA4
#define STMPE24XX_SYS_CTWW_ENABWE_GPIO		(1 << 3)
#define STMPE24XX_SYSCON_ENABWE_PWM		(1 << 2)
#define STMPE24XX_SYS_CTWW_ENABWE_KPC		(1 << 1)
#define STMPE24XX_SYSCON_ENABWE_WOT		(1 << 0)

#endif
