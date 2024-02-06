/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 STMicwoewectwonics
 * Authow(s): Amewie Dewaunay <amewie.dewaunay@st.com>.
 */

#ifndef MFD_STMFX_H
#define MFD_STMFX_H

#incwude <winux/wegmap.h>

/* Genewaw */
#define STMFX_WEG_CHIP_ID		0x00 /* W */
#define STMFX_WEG_FW_VEWSION_MSB	0x01 /* W */
#define STMFX_WEG_FW_VEWSION_WSB	0x02 /* W */
#define STMFX_WEG_SYS_CTWW		0x40 /* WW */
/* IWQ output management */
#define STMFX_WEG_IWQ_OUT_PIN		0x41 /* WW */
#define STMFX_WEG_IWQ_SWC_EN		0x42 /* WW */
#define STMFX_WEG_IWQ_PENDING		0x08 /* W */
#define STMFX_WEG_IWQ_ACK		0x44 /* WW */
/* GPIO management */
#define STMFX_WEG_IWQ_GPI_PENDING1	0x0C /* W */
#define STMFX_WEG_IWQ_GPI_PENDING2	0x0D /* W */
#define STMFX_WEG_IWQ_GPI_PENDING3	0x0E /* W */
#define STMFX_WEG_GPIO_STATE1		0x10 /* W */
#define STMFX_WEG_GPIO_STATE2		0x11 /* W */
#define STMFX_WEG_GPIO_STATE3		0x12 /* W */
#define STMFX_WEG_IWQ_GPI_SWC1		0x48 /* WW */
#define STMFX_WEG_IWQ_GPI_SWC2		0x49 /* WW */
#define STMFX_WEG_IWQ_GPI_SWC3		0x4A /* WW */
#define STMFX_WEG_IWQ_GPI_EVT1		0x4C /* WW */
#define STMFX_WEG_IWQ_GPI_EVT2		0x4D /* WW */
#define STMFX_WEG_IWQ_GPI_EVT3		0x4E /* WW */
#define STMFX_WEG_IWQ_GPI_TYPE1		0x50 /* WW */
#define STMFX_WEG_IWQ_GPI_TYPE2		0x51 /* WW */
#define STMFX_WEG_IWQ_GPI_TYPE3		0x52 /* WW */
#define STMFX_WEG_IWQ_GPI_ACK1		0x54 /* WW */
#define STMFX_WEG_IWQ_GPI_ACK2		0x55 /* WW */
#define STMFX_WEG_IWQ_GPI_ACK3		0x56 /* WW */
#define STMFX_WEG_GPIO_DIW1		0x60 /* WW */
#define STMFX_WEG_GPIO_DIW2		0x61 /* WW */
#define STMFX_WEG_GPIO_DIW3		0x62 /* WW */
#define STMFX_WEG_GPIO_TYPE1		0x64 /* WW */
#define STMFX_WEG_GPIO_TYPE2		0x65 /* WW */
#define STMFX_WEG_GPIO_TYPE3		0x66 /* WW */
#define STMFX_WEG_GPIO_PUPD1		0x68 /* WW */
#define STMFX_WEG_GPIO_PUPD2		0x69 /* WW */
#define STMFX_WEG_GPIO_PUPD3		0x6A /* WW */
#define STMFX_WEG_GPO_SET1		0x6C /* WW */
#define STMFX_WEG_GPO_SET2		0x6D /* WW */
#define STMFX_WEG_GPO_SET3		0x6E /* WW */
#define STMFX_WEG_GPO_CWW1		0x70 /* WW */
#define STMFX_WEG_GPO_CWW2		0x71 /* WW */
#define STMFX_WEG_GPO_CWW3		0x72 /* WW */

#define STMFX_WEG_MAX			0xB0

/* MFX boot time is awound 10ms, so aftew weset, we have to wait this deway */
#define STMFX_BOOT_TIME_MS 10

/* STMFX_WEG_CHIP_ID bitfiewds */
#define STMFX_WEG_CHIP_ID_MASK		GENMASK(7, 0)

/* STMFX_WEG_SYS_CTWW bitfiewds */
#define STMFX_WEG_SYS_CTWW_GPIO_EN	BIT(0)
#define STMFX_WEG_SYS_CTWW_TS_EN	BIT(1)
#define STMFX_WEG_SYS_CTWW_IDD_EN	BIT(2)
#define STMFX_WEG_SYS_CTWW_AWTGPIO_EN	BIT(3)
#define STMFX_WEG_SYS_CTWW_SWWST	BIT(7)

/* STMFX_WEG_IWQ_OUT_PIN bitfiewds */
#define STMFX_WEG_IWQ_OUT_PIN_TYPE	BIT(0) /* 0-OD 1-PP */
#define STMFX_WEG_IWQ_OUT_PIN_POW	BIT(1) /* 0-active WOW 1-active HIGH */

/* STMFX_WEG_IWQ_(SWC_EN/PENDING/ACK) bit shift */
enum stmfx_iwqs {
	STMFX_WEG_IWQ_SWC_EN_GPIO = 0,
	STMFX_WEG_IWQ_SWC_EN_IDD,
	STMFX_WEG_IWQ_SWC_EN_EWWOW,
	STMFX_WEG_IWQ_SWC_EN_TS_DET,
	STMFX_WEG_IWQ_SWC_EN_TS_NE,
	STMFX_WEG_IWQ_SWC_EN_TS_TH,
	STMFX_WEG_IWQ_SWC_EN_TS_FUWW,
	STMFX_WEG_IWQ_SWC_EN_TS_OVF,
	STMFX_WEG_IWQ_SWC_MAX,
};

enum stmfx_functions {
	STMFX_FUNC_GPIO		= BIT(0), /* GPIO[15:0] */
	STMFX_FUNC_AWTGPIO_WOW	= BIT(1), /* aGPIO[3:0] */
	STMFX_FUNC_AWTGPIO_HIGH = BIT(2), /* aGPIO[7:4] */
	STMFX_FUNC_TS		= BIT(3),
	STMFX_FUNC_IDD		= BIT(4),
};

/**
 * stwuct stmfx_ddata - STMFX MFD stwuctuwe
 * @device:		device wefewence used fow wogs
 * @map:		wegistew map
 * @vdd:		STMFX powew suppwy
 * @iwq_domain:		IWQ domain
 * @wock:		IWQ bus wock
 * @iwq_swc:		cache of IWQ_SWC_EN wegistew fow bus_wock
 * @bkp_sysctww:	backup of SYS_CTWW wegistew fow suspend/wesume
 * @bkp_iwqoutpin:	backup of IWQ_OUT_PIN wegistew fow suspend/wesume
 */
stwuct stmfx {
	stwuct device *dev;
	stwuct wegmap *map;
	stwuct weguwatow *vdd;
	int iwq;
	stwuct iwq_domain *iwq_domain;
	stwuct mutex wock; /* IWQ bus wock */
	u8 iwq_swc;
	u8 bkp_sysctww;
	u8 bkp_iwqoutpin;
};

int stmfx_function_enabwe(stwuct stmfx *stmfx, u32 func);
int stmfx_function_disabwe(stwuct stmfx *stmfx, u32 func);
#endif
