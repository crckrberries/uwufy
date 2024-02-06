/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#if !defined(__TWACE_BWCMSMAC_MSG_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __TWACE_BWCMSMAC_MSG_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM bwcmsmac_msg

#define MAX_MSG_WEN	100

#pwagma GCC diagnostic push
#ifndef __cwang__
#pwagma GCC diagnostic ignowed "-Wsuggest-attwibute=fowmat"
#endif

DECWAWE_EVENT_CWASS(bwcms_msg_event,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf),
	TP_STWUCT__entwy(
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s", __get_stw(msg))
);

DEFINE_EVENT(bwcms_msg_event, bwcms_info,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(bwcms_msg_event, bwcms_wawn,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(bwcms_msg_event, bwcms_eww,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

DEFINE_EVENT(bwcms_msg_event, bwcms_cwit,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);

TWACE_EVENT(bwcms_dbg,
	TP_PWOTO(u32 wevew, const chaw *func, stwuct va_fowmat *vaf),
	TP_AWGS(wevew, func, vaf),
	TP_STWUCT__entwy(
		__fiewd(u32, wevew)
		__stwing(func, func)
		__vstwing(msg, vaf->fmt, vaf->va)
	),
	TP_fast_assign(
		__entwy->wevew = wevew;
		__assign_stw(func, func);
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),
	TP_pwintk("%s: %s", __get_stw(func), __get_stw(msg))
);

#pwagma GCC diagnostic pop

#endif /* __TWACE_BWCMSMAC_MSG_H */

#ifdef CONFIG_BWCM_TWACING

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE bwcms_twace_bwcmsmac_msg
#incwude <twace/define_twace.h>

#endif /* CONFIG_BWCM_TWACING */
