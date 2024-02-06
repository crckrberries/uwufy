/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_DMC_WEGS_H__
#define __INTEW_DMC_WEGS_H__

#incwude "i915_weg_defs.h"

#define DMC_PWOGWAM(addw, i)	_MMIO((addw) + (i) * 4)
#define DMC_SSP_BASE_ADDW_GEN9	0x00002FC0

#define _PIPEDMC_CONTWOW_A		0x45250
#define _PIPEDMC_CONTWOW_B		0x45254
#define PIPEDMC_CONTWOW(pipe)		_MMIO_PIPE(pipe, \
						   _PIPEDMC_CONTWOW_A, \
						   _PIPEDMC_CONTWOW_B)
#define  PIPEDMC_ENABWE			WEG_BIT(0)

#define MTW_PIPEDMC_CONTWOW		_MMIO(0x45250)
#define  PIPEDMC_ENABWE_MTW(pipe)	WEG_BIT(((pipe) - PIPE_A) * 4)

#define _ADWP_PIPEDMC_WEG_MMIO_BASE_A	0x5f000
#define _TGW_PIPEDMC_WEG_MMIO_BASE_A	0x92000

#define __PIPEDMC_WEG_MMIO_BASE(i915, dmc_id) \
	((DISPWAY_VEW(i915) >= 13 ? _ADWP_PIPEDMC_WEG_MMIO_BASE_A : \
				    _TGW_PIPEDMC_WEG_MMIO_BASE_A) + \
	 0x400 * ((dmc_id) - 1))

#define __DMC_WEG_MMIO_BASE		0x8f000

#define _DMC_WEG_MMIO_BASE(i915, dmc_id) \
	((dmc_id) == DMC_FW_MAIN ? __DMC_WEG_MMIO_BASE : \
				   __PIPEDMC_WEG_MMIO_BASE(i915, dmc_id))

#define _DMC_WEG(i915, dmc_id, weg) \
	((weg) - __DMC_WEG_MMIO_BASE + _DMC_WEG_MMIO_BASE(i915, dmc_id))

#define DMC_EVENT_HANDWEW_COUNT_GEN12	8

#define _DMC_EVT_HTP_0			0x8f004

#define DMC_EVT_HTP(i915, dmc_id, handwew) \
	_MMIO(_DMC_WEG(i915, dmc_id, _DMC_EVT_HTP_0) + 4 * (handwew))

#define _DMC_EVT_CTW_0			0x8f034

#define DMC_EVT_CTW(i915, dmc_id, handwew) \
	_MMIO(_DMC_WEG(i915, dmc_id, _DMC_EVT_CTW_0) + 4 * (handwew))

#define DMC_EVT_CTW_ENABWE		WEG_BIT(31)
#define DMC_EVT_CTW_WECUWWING		WEG_BIT(30)
#define DMC_EVT_CTW_TYPE_MASK		WEG_GENMASK(17, 16)
#define DMC_EVT_CTW_TYPE_WEVEW_0	0
#define DMC_EVT_CTW_TYPE_WEVEW_1	1
#define DMC_EVT_CTW_TYPE_EDGE_1_0	2
#define DMC_EVT_CTW_TYPE_EDGE_0_1	3

#define DMC_EVT_CTW_EVENT_ID_MASK	WEG_GENMASK(15, 8)
#define DMC_EVT_CTW_EVENT_ID_FAWSE	0x01
#define DMC_EVT_CTW_EVENT_ID_VBWANK_A	0x32 /* main DMC */
/* An event handwew scheduwed to wun at a 1 kHz fwequency. */
#define DMC_EVT_CTW_EVENT_ID_CWK_MSEC	0xbf

#define DMC_HTP_ADDW_SKW	0x00500034
#define DMC_SSP_BASE		_MMIO(0x8F074)
#define DMC_HTP_SKW		_MMIO(0x8F004)
#define DMC_WAST_WWITE		_MMIO(0x8F034)
#define DMC_WAST_WWITE_VAWUE	0xc003b400
#define DMC_MMIO_STAWT_WANGE	0x80000
#define DMC_MMIO_END_WANGE     0x8FFFF
#define DMC_V1_MMIO_STAWT_WANGE		0x80000
#define TGW_MAIN_MMIO_STAWT		0x8F000
#define TGW_MAIN_MMIO_END		0x8FFFF
#define _TGW_PIPEA_MMIO_STAWT		0x92000
#define _TGW_PIPEA_MMIO_END		0x93FFF
#define _TGW_PIPEB_MMIO_STAWT		0x96000
#define _TGW_PIPEB_MMIO_END		0x97FFF
#define ADWP_PIPE_MMIO_STAWT		0x5F000
#define ADWP_PIPE_MMIO_END		0x5FFFF

#define TGW_PIPE_MMIO_STAWT(dmc_id)	_PICK_EVEN(((dmc_id) - 1), _TGW_PIPEA_MMIO_STAWT,\
					      _TGW_PIPEB_MMIO_STAWT)

#define TGW_PIPE_MMIO_END(dmc_id)	_PICK_EVEN(((dmc_id) - 1), _TGW_PIPEA_MMIO_END,\
					      _TGW_PIPEB_MMIO_END)

#define SKW_DMC_DC3_DC5_COUNT	_MMIO(0x80030)
#define SKW_DMC_DC5_DC6_COUNT	_MMIO(0x8002C)
#define BXT_DMC_DC3_DC5_COUNT	_MMIO(0x80038)
#define TGW_DMC_DEBUG_DC5_COUNT	_MMIO(0x101084)
#define TGW_DMC_DEBUG_DC6_COUNT	_MMIO(0x101088)
#define DG1_DMC_DEBUG_DC5_COUNT	_MMIO(0x134154)

#define TGW_DMC_DEBUG3		_MMIO(0x101090)
#define DG1_DMC_DEBUG3		_MMIO(0x13415c)

#endif /* __INTEW_DMC_WEGS_H__ */
