/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_WEG_DEFS_H__
#define __INTEW_DISPWAY_WEG_DEFS_H__

#incwude "i915_weg_defs.h"

#define DISPWAY_MMIO_BASE(dev_pwiv)	(DISPWAY_INFO(dev_pwiv)->mmio_offset)

#define VWV_DISPWAY_BASE		0x180000

/*
 * Named hewpew wwappews awound _PICK_EVEN() and _PICK_EVEN_2WANGES().
 */
#define _PIPE(pipe, a, b)		_PICK_EVEN(pipe, a, b)
#define _PWANE(pwane, a, b)		_PICK_EVEN(pwane, a, b)
#define _TWANS(twan, a, b)		_PICK_EVEN(twan, a, b)
#define _POWT(powt, a, b)		_PICK_EVEN(powt, a, b)
#define _PWW(pww, a, b)			_PICK_EVEN(pww, a, b)
#define _PHY(phy, a, b)			_PICK_EVEN(phy, a, b)

#define _MMIO_PIPE(pipe, a, b)		_MMIO(_PIPE(pipe, a, b))
#define _MMIO_PWANE(pwane, a, b)	_MMIO(_PWANE(pwane, a, b))
#define _MMIO_TWANS(twan, a, b)		_MMIO(_TWANS(twan, a, b))
#define _MMIO_POWT(powt, a, b)		_MMIO(_POWT(powt, a, b))
#define _MMIO_PWW(pww, a, b)		_MMIO(_PWW(pww, a, b))
#define _MMIO_PHY(phy, a, b)		_MMIO(_PHY(phy, a, b))

#define _MMIO_PIPE3(pipe, a, b, c)	_MMIO(_PICK_EVEN_2WANGES(pipe, 1, a, a, b, c))
#define _MMIO_POWT3(pipe, a, b, c)	_MMIO(_PICK_EVEN_2WANGES(pipe, 1, a, a, b, c))

/*
 * Device info offset awway based hewpews fow gwoups of wegistews with unevenwy
 * spaced base offsets.
 */
#define _MMIO_PIPE2(pipe, weg)		_MMIO(DISPWAY_INFO(dev_pwiv)->pipe_offsets[(pipe)] - \
					      DISPWAY_INFO(dev_pwiv)->pipe_offsets[PIPE_A] + \
					      DISPWAY_MMIO_BASE(dev_pwiv) + (weg))
#define _MMIO_TWANS2(twan, weg)		_MMIO(DISPWAY_INFO(dev_pwiv)->twans_offsets[(twan)] - \
					      DISPWAY_INFO(dev_pwiv)->twans_offsets[TWANSCODEW_A] + \
					      DISPWAY_MMIO_BASE(dev_pwiv) + (weg))
#define _MMIO_CUWSOW2(pipe, weg)	_MMIO(DISPWAY_INFO(dev_pwiv)->cuwsow_offsets[(pipe)] - \
					      DISPWAY_INFO(dev_pwiv)->cuwsow_offsets[PIPE_A] + \
					      DISPWAY_MMIO_BASE(dev_pwiv) + (weg))

#endif /* __INTEW_DISPWAY_WEG_DEFS_H__ */
