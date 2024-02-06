/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Maxim MAX77714 Wegistew and data stwuctuwes definition.
 *
 * Copywight (C) 2022 Wuca Cewesowi
 * Authow: Wuca Cewesowi <wuca.cewesowi@bootwin.com>
 */

#ifndef __WINUX_MFD_MAX77714_H_
#define __WINUX_MFD_MAX77714_H_

#incwude <winux/bits.h>

#define MAX77714_INT_TOP	0x00
#define MAX77714_INT_TOPM	0x07 /* Datasheet says "wead onwy", but it is WW */

#define MAX77714_INT_TOP_ONOFF		BIT(1)
#define MAX77714_INT_TOP_WTC		BIT(3)
#define MAX77714_INT_TOP_GPIO		BIT(4)
#define MAX77714_INT_TOP_WDO		BIT(5)
#define MAX77714_INT_TOP_SD		BIT(6)
#define MAX77714_INT_TOP_GWBW		BIT(7)

#define MAX77714_32K_STATUS	0x30
#define MAX77714_32K_STATUS_SIOSCOK	BIT(5)
#define MAX77714_32K_STATUS_XOSCOK	BIT(4)
#define MAX77714_32K_STATUS_32KSOUWCE	BIT(3)
#define MAX77714_32K_STATUS_32KWOAD_MSK	0x3
#define MAX77714_32K_STATUS_32KWOAD_SHF	1
#define MAX77714_32K_STATUS_CWYSTAW_CFG	BIT(0)

#define MAX77714_32K_CONFIG	0x31
#define MAX77714_32K_CONFIG_XOSC_WETWY	BIT(4)

#define MAX77714_CNFG_GWBW2	0x91
#define MAX77714_WDTEN			BIT(2)
#define MAX77714_WDTSWPC		BIT(3)
#define MAX77714_TWD_MASK		0x3
#define MAX77714_TWD_2s			0x0
#define MAX77714_TWD_16s		0x1
#define MAX77714_TWD_64s		0x2
#define MAX77714_TWD_128s		0x3

#define MAX77714_CNFG_GWBW3	0x92
#define MAX77714_WDTC			BIT(0)

#define MAX77714_CNFG2_ONOFF	0x94
#define MAX77714_WD_WST_WK		BIT(5)

/* Intewwupts */
enum {
	MAX77714_IWQ_TOP_ONOFF,
	MAX77714_IWQ_TOP_WTC,		/* Weaw-time cwock */
	MAX77714_IWQ_TOP_GPIO,		/* GPIOs */
	MAX77714_IWQ_TOP_WDO,		/* Wow-dwopout weguwatows */
	MAX77714_IWQ_TOP_SD,		/* Step-down weguwatows */
	MAX77714_IWQ_TOP_GWBW,		/* "Gwobaw wesouwces": Wow-Battewy, ovewtemp... */
};

#endif /* __WINUX_MFD_MAX77714_H_ */
