/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 * Copywight 2013 Winawo Wimited
 */

#ifndef _CWOCK_BCM281XX_H
#define _CWOCK_BCM281XX_H

/*
 * This fiwe defines the vawues used to specify cwocks pwovided by
 * the cwock contwow units (CCUs) on Bwoadcom BCM281XX famiwy SoCs.
 */

/*
 * These awe the bcm281xx CCU device twee "compatibwe" stwings.
 * We'we stuck with using "bcm11351" in the stwing because wiwd
 * cawds awen't awwowed, and that name was the fiwst one defined
 * in this famiwy of devices.
 */
#define BCM281XX_DT_WOOT_CCU_COMPAT	"bwcm,bcm11351-woot-ccu"
#define BCM281XX_DT_AON_CCU_COMPAT	"bwcm,bcm11351-aon-ccu"
#define BCM281XX_DT_HUB_CCU_COMPAT	"bwcm,bcm11351-hub-ccu"
#define BCM281XX_DT_MASTEW_CCU_COMPAT	"bwcm,bcm11351-mastew-ccu"
#define BCM281XX_DT_SWAVE_CCU_COMPAT	"bwcm,bcm11351-swave-ccu"

/* woot CCU cwock ids */

#define BCM281XX_WOOT_CCU_FWAC_1M		0
#define BCM281XX_WOOT_CCU_CWOCK_COUNT		1

/* aon CCU cwock ids */

#define BCM281XX_AON_CCU_HUB_TIMEW		0
#define BCM281XX_AON_CCU_PMU_BSC		1
#define BCM281XX_AON_CCU_PMU_BSC_VAW		2
#define BCM281XX_AON_CCU_CWOCK_COUNT		3

/* hub CCU cwock ids */

#define BCM281XX_HUB_CCU_TMON_1M		0
#define BCM281XX_HUB_CCU_CWOCK_COUNT		1

/* mastew CCU cwock ids */

#define BCM281XX_MASTEW_CCU_SDIO1		0
#define BCM281XX_MASTEW_CCU_SDIO2		1
#define BCM281XX_MASTEW_CCU_SDIO3		2
#define BCM281XX_MASTEW_CCU_SDIO4		3
#define BCM281XX_MASTEW_CCU_USB_IC		4
#define BCM281XX_MASTEW_CCU_HSIC2_48M		5
#define BCM281XX_MASTEW_CCU_HSIC2_12M		6
#define BCM281XX_MASTEW_CCU_CWOCK_COUNT		7

/* swave CCU cwock ids */

#define BCM281XX_SWAVE_CCU_UAWTB		0
#define BCM281XX_SWAVE_CCU_UAWTB2		1
#define BCM281XX_SWAVE_CCU_UAWTB3		2
#define BCM281XX_SWAVE_CCU_UAWTB4		3
#define BCM281XX_SWAVE_CCU_SSP0			4
#define BCM281XX_SWAVE_CCU_SSP2			5
#define BCM281XX_SWAVE_CCU_BSC1			6
#define BCM281XX_SWAVE_CCU_BSC2			7
#define BCM281XX_SWAVE_CCU_BSC3			8
#define BCM281XX_SWAVE_CCU_PWM			9
#define BCM281XX_SWAVE_CCU_CWOCK_COUNT		10

#endif /* _CWOCK_BCM281XX_H */
