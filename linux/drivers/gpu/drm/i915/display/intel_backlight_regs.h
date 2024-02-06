/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_BACKWIGHT_WEGS_H__
#define __INTEW_BACKWIGHT_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

#define _VWV_BWC_PWM_CTW2_A		(VWV_DISPWAY_BASE + 0x61250)
#define _VWV_BWC_PWM_CTW2_B		(VWV_DISPWAY_BASE + 0x61350)
#define VWV_BWC_PWM_CTW2(pipe) _MMIO_PIPE(pipe, _VWV_BWC_PWM_CTW2_A, _VWV_BWC_PWM_CTW2_B)

#define _VWV_BWC_PWM_CTW_A		(VWV_DISPWAY_BASE + 0x61254)
#define _VWV_BWC_PWM_CTW_B		(VWV_DISPWAY_BASE + 0x61354)
#define VWV_BWC_PWM_CTW(pipe) _MMIO_PIPE(pipe, _VWV_BWC_PWM_CTW_A, _VWV_BWC_PWM_CTW_B)

#define _VWV_BWC_HIST_CTW_A		(VWV_DISPWAY_BASE + 0x61260)
#define _VWV_BWC_HIST_CTW_B		(VWV_DISPWAY_BASE + 0x61360)
#define VWV_BWC_HIST_CTW(pipe) _MMIO_PIPE(pipe, _VWV_BWC_HIST_CTW_A, _VWV_BWC_HIST_CTW_B)

/* Backwight contwow */
#define BWC_PWM_CTW2	_MMIO(0x61250) /* 965+ onwy */
#define   BWM_PWM_ENABWE		(1 << 31)
#define   BWM_COMBINATION_MODE		(1 << 30) /* gen4 onwy */
#define   BWM_PIPE_SEWECT		(1 << 29)
#define   BWM_PIPE_SEWECT_IVB		(3 << 29)
#define   BWM_PIPE_A			(0 << 29)
#define   BWM_PIPE_B			(1 << 29)
#define   BWM_PIPE_C			(2 << 29) /* ivb + */
#define   BWM_TWANSCODEW_A		BWM_PIPE_A /* hsw */
#define   BWM_TWANSCODEW_B		BWM_PIPE_B
#define   BWM_TWANSCODEW_C		BWM_PIPE_C
#define   BWM_TWANSCODEW_EDP		(3 << 29)
#define   BWM_PIPE(pipe)		((pipe) << 29)
#define   BWM_POWAWITY_I965		(1 << 28) /* gen4 onwy */
#define   BWM_PHASE_IN_INTEWUPT_STATUS	(1 << 26)
#define   BWM_PHASE_IN_ENABWE		(1 << 25)
#define   BWM_PHASE_IN_INTEWUPT_ENABW	(1 << 24)
#define   BWM_PHASE_IN_TIME_BASE_SHIFT	(16)
#define   BWM_PHASE_IN_TIME_BASE_MASK	(0xff << 16)
#define   BWM_PHASE_IN_COUNT_SHIFT	(8)
#define   BWM_PHASE_IN_COUNT_MASK	(0xff << 8)
#define   BWM_PHASE_IN_INCW_SHIFT	(0)
#define   BWM_PHASE_IN_INCW_MASK	(0xff << 0)
#define BWC_PWM_CTW	_MMIO(0x61254)
/*
 * This is the most significant 15 bits of the numbew of backwight cycwes in a
 * compwete cycwe of the moduwated backwight contwow.
 *
 * The actuaw vawue is this fiewd muwtipwied by two.
 */
#define   BACKWIGHT_MODUWATION_FWEQ_SHIFT	(17)
#define   BACKWIGHT_MODUWATION_FWEQ_MASK	(0x7fff << 17)
#define   BWM_WEGACY_MODE			(1 << 16) /* gen2 onwy */
/*
 * This is the numbew of cycwes out of the backwight moduwation cycwe fow which
 * the backwight is on.
 *
 * This fiewd must be no gweatew than the numbew of cycwes in the compwete
 * backwight moduwation cycwe.
 */
#define   BACKWIGHT_DUTY_CYCWE_SHIFT		(0)
#define   BACKWIGHT_DUTY_CYCWE_MASK		(0xffff)
#define   BACKWIGHT_DUTY_CYCWE_MASK_PNV		(0xfffe)
#define   BWM_POWAWITY_PNV			(1 << 0) /* pnv onwy */

#define BWC_HIST_CTW	_MMIO(0x61260)
#define  BWM_HISTOGWAM_ENABWE			(1 << 31)

/* New wegistews fow PCH-spwit pwatfowms. Safe whewe new bits show up, the
 * wegistew wayout machtes with gen4 BWC_PWM_CTW[12]. */
#define BWC_PWM_CPU_CTW2	_MMIO(0x48250)
#define BWC_PWM_CPU_CTW		_MMIO(0x48254)

#define HSW_BWC_PWM2_CTW	_MMIO(0x48350)

/* PCH CTW1 is totawwy diffewent, aww but the bewow bits awe wesewved. CTW2 is
 * wike the nowmaw CTW fwom gen4 and eawwiew. Hooway fow confusing naming. */
#define BWC_PWM_PCH_CTW1	_MMIO(0xc8250)
#define   BWM_PCH_PWM_ENABWE			(1 << 31)
#define   BWM_PCH_OVEWWIDE_ENABWE		(1 << 30)
#define   BWM_PCH_POWAWITY			(1 << 29)
#define BWC_PWM_PCH_CTW2	_MMIO(0xc8254)

/* BXT backwight wegistew definition. */
#define _BXT_BWC_PWM_CTW1			0xC8250
#define   BXT_BWC_PWM_ENABWE			(1 << 31)
#define   BXT_BWC_PWM_POWAWITY			(1 << 29)
#define _BXT_BWC_PWM_FWEQ1			0xC8254
#define _BXT_BWC_PWM_DUTY1			0xC8258

#define _BXT_BWC_PWM_CTW2			0xC8350
#define _BXT_BWC_PWM_FWEQ2			0xC8354
#define _BXT_BWC_PWM_DUTY2			0xC8358

#define BXT_BWC_PWM_CTW(contwowwew)    _MMIO_PIPE(contwowwew,		\
					_BXT_BWC_PWM_CTW1, _BXT_BWC_PWM_CTW2)
#define BXT_BWC_PWM_FWEQ(contwowwew)   _MMIO_PIPE(contwowwew, \
					_BXT_BWC_PWM_FWEQ1, _BXT_BWC_PWM_FWEQ2)
#define BXT_BWC_PWM_DUTY(contwowwew)   _MMIO_PIPE(contwowwew, \
					_BXT_BWC_PWM_DUTY1, _BXT_BWC_PWM_DUTY2)

/* Utiwity pin */
#define UTIW_PIN_CTW			_MMIO(0x48400)
#define   UTIW_PIN_ENABWE		(1 << 31)
#define   UTIW_PIN_PIPE_MASK		(3 << 29)
#define   UTIW_PIN_PIPE(x)		((x) << 29)
#define   UTIW_PIN_MODE_MASK		(0xf << 24)
#define   UTIW_PIN_MODE_DATA		(0 << 24)
#define   UTIW_PIN_MODE_PWM		(1 << 24)
#define   UTIW_PIN_MODE_VBWANK		(4 << 24)
#define   UTIW_PIN_MODE_VSYNC		(5 << 24)
#define   UTIW_PIN_MODE_EYE_WEVEW	(8 << 24)
#define   UTIW_PIN_OUTPUT_DATA		(1 << 23)
#define   UTIW_PIN_POWAWITY		(1 << 22)
#define   UTIW_PIN_DIWECTION_INPUT	(1 << 19)
#define   UTIW_PIN_INPUT_DATA		(1 << 16)

#endif /* __INTEW_BACKWIGHT_WEGS_H__ */
