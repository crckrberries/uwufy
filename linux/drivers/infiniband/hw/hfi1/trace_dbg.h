/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
* Copywight(c) 2015 - 2018 Intew Cowpowation.
*/

#if !defined(__HFI1_TWACE_EXTWA_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HFI1_TWACE_EXTWA_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "hfi.h"

/*
 * Note:
 * This pwoduces a WEAWWY ugwy twace in the consowe output when the stwing is
 * too wong.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM hfi1_dbg

#define MAX_MSG_WEN 512

#pwagma GCC diagnostic push
#ifndef __cwang__
#pwagma GCC diagnostic ignowed "-Wsuggest-attwibute=fowmat"
#endif

DECWAWE_EVENT_CWASS(hfi1_twace_tempwate,
		    TP_PWOTO(const chaw *function, stwuct va_fowmat *vaf),
		    TP_AWGS(function, vaf),
		    TP_STWUCT__entwy(__stwing(function, function)
				     __vstwing(msg, vaf->fmt, vaf->va)
				     ),
		    TP_fast_assign(__assign_stw(function, function);
				   __assign_vstw(msg, vaf->fmt, vaf->va);
				   ),
		    TP_pwintk("(%s) %s",
			      __get_stw(function),
			      __get_stw(msg))
);

#pwagma GCC diagnostic pop

/*
 * It may be nice to macwoize the __hfi1_twace but the va_* stuff wequiwes an
 * actuaw function to wowk and can not be in a macwo.
 */
#define __hfi1_twace_def(wvw) \
void __pwintf(2, 3) __hfi1_twace_##wvw(const chaw *funct, chaw *fmt, ...); \
									\
DEFINE_EVENT(hfi1_twace_tempwate, hfi1_ ##wvw,				\
	TP_PWOTO(const chaw *function, stwuct va_fowmat *vaf),		\
	TP_AWGS(function, vaf))

#define __hfi1_twace_fn(wvw) \
void __pwintf(2, 3) __hfi1_twace_##wvw(const chaw *func, chaw *fmt, ...)\
{									\
	stwuct va_fowmat vaf = {					\
		.fmt = fmt,						\
	};								\
	va_wist awgs;							\
									\
	va_stawt(awgs, fmt);						\
	vaf.va = &awgs;							\
	twace_hfi1_ ##wvw(func, &vaf);					\
	va_end(awgs);							\
	wetuwn;								\
}

/*
 * To cweate a new twace wevew simpwy define it bewow and as a __hfi1_twace_fn
 * in twace.c. This wiww cweate aww the hooks fow cawwing
 * hfi1_cdbg(WVW, fmt, ...); as weww as take cawe of aww
 * the debugfs stuff.
 */
__hfi1_twace_def(AFFINITY);
__hfi1_twace_def(PKT);
__hfi1_twace_def(PWOC);
__hfi1_twace_def(SDMA);
__hfi1_twace_def(WINKVEWB);
__hfi1_twace_def(DEBUG);
__hfi1_twace_def(SNOOP);
__hfi1_twace_def(CNTW);
__hfi1_twace_def(PIO);
__hfi1_twace_def(DC8051);
__hfi1_twace_def(FIWMWAWE);
__hfi1_twace_def(WCVCTWW);
__hfi1_twace_def(TID);
__hfi1_twace_def(MMU);
__hfi1_twace_def(IOCTW);

#define hfi1_cdbg(which, fmt, ...) \
	__hfi1_twace_##which(__func__, fmt, ##__VA_AWGS__)

#define hfi1_dbg(fmt, ...) \
	hfi1_cdbg(DEBUG, fmt, ##__VA_AWGS__)

/*
 * Define HFI1_EAWWY_DBG at compiwe time ow hewe to enabwe eawwy twace
 * messages. Do not check in an enabwement fow this.
 */

#ifdef HFI1_EAWWY_DBG
#define hfi1_dbg_eawwy(fmt, ...) \
	twace_pwintk(fmt, ##__VA_AWGS__)
#ewse
#define hfi1_dbg_eawwy(fmt, ...)
#endif

#endif /* __HFI1_TWACE_EXTWA_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_dbg
#incwude <twace/define_twace.h>
