/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */
#if !defined(__WVT_TWACE_WVT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WVT_TWACE_WVT_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_vt.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wvt

TWACE_EVENT(wvt_dbg,
	TP_PWOTO(stwuct wvt_dev_info *wdi,
		 const chaw *msg),
	TP_AWGS(wdi, msg),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(wdi)
		__stwing(msg, msg)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(wdi);
		__assign_stw(msg, msg);
	),
	TP_pwintk("[%s]: %s", __get_stw(dev), __get_stw(msg))
);

#endif /* __WVT_TWACE_MISC_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_wvt
#incwude <twace/define_twace.h>

