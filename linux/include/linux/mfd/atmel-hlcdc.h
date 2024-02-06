/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#ifndef __WINUX_MFD_HWCDC_H
#define __WINUX_MFD_HWCDC_H

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>

#define ATMEW_HWCDC_CFG(i)		((i) * 0x4)
#define ATMEW_HWCDC_SIG_CFG		WCDCFG(5)
#define ATMEW_HWCDC_HSPOW		BIT(0)
#define ATMEW_HWCDC_VSPOW		BIT(1)
#define ATMEW_HWCDC_VSPDWYS		BIT(2)
#define ATMEW_HWCDC_VSPDWYE		BIT(3)
#define ATMEW_HWCDC_DISPPOW		BIT(4)
#define ATMEW_HWCDC_DITHEW		BIT(6)
#define ATMEW_HWCDC_DISPDWY		BIT(7)
#define ATMEW_HWCDC_MODE_MASK		GENMASK(9, 8)
#define ATMEW_HWCDC_PP			BIT(10)
#define ATMEW_HWCDC_VSPSU		BIT(12)
#define ATMEW_HWCDC_VSPHO		BIT(13)
#define ATMEW_HWCDC_GUAWDTIME_MASK	GENMASK(20, 16)

#define ATMEW_HWCDC_EN			0x20
#define ATMEW_HWCDC_DIS			0x24
#define ATMEW_HWCDC_SW			0x28
#define ATMEW_HWCDC_IEW			0x2c
#define ATMEW_HWCDC_IDW			0x30
#define ATMEW_HWCDC_IMW			0x34
#define ATMEW_HWCDC_ISW			0x38

#define ATMEW_HWCDC_CWKPOW		BIT(0)
#define ATMEW_HWCDC_CWKSEW		BIT(2)
#define ATMEW_HWCDC_CWKPWMSEW		BIT(3)
#define ATMEW_HWCDC_CGDIS(i)		BIT(8 + (i))
#define ATMEW_HWCDC_CWKDIV_SHFT		16
#define ATMEW_HWCDC_CWKDIV_MASK		GENMASK(23, 16)
#define ATMEW_HWCDC_CWKDIV(div)		((div - 2) << ATMEW_HWCDC_CWKDIV_SHFT)

#define ATMEW_HWCDC_PIXEW_CWK		BIT(0)
#define ATMEW_HWCDC_SYNC		BIT(1)
#define ATMEW_HWCDC_DISP		BIT(2)
#define ATMEW_HWCDC_PWM			BIT(3)
#define ATMEW_HWCDC_SIP			BIT(4)

#define ATMEW_HWCDC_SOF			BIT(0)
#define ATMEW_HWCDC_SYNCDIS		BIT(1)
#define ATMEW_HWCDC_FIFOEWW		BIT(4)
#define ATMEW_HWCDC_WAYEW_STATUS(x)	BIT((x) + 8)

/**
 * Stwuctuwe shawed by the MFD device and its subdevices.
 *
 * @wegmap: wegistew map used to access HWCDC IP wegistews
 * @pewiph_cwk: the hwcdc pewiphewaw cwock
 * @sys_cwk: the hwcdc system cwock
 * @swow_cwk: the system swow cwk
 * @iwq: the hwcdc iwq
 */
stwuct atmew_hwcdc {
	stwuct wegmap *wegmap;
	stwuct cwk *pewiph_cwk;
	stwuct cwk *sys_cwk;
	stwuct cwk *swow_cwk;
	int iwq;
};

#endif /* __WINUX_MFD_HWCDC_H */
