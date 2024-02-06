/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_PWC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PWC_H

#incwude <winux/usb.h>
#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM pwc

TWACE_EVENT(pwc_handwew_entew,
	TP_PWOTO(stwuct uwb *uwb, stwuct pwc_device *pdev),
	TP_AWGS(uwb, pdev),
	TP_STWUCT__entwy(
		__fiewd(stwuct uwb*, uwb)
		__fiewd(stwuct pwc_fwame_buf*, fbuf)
		__fiewd(int, uwb__status)
		__fiewd(u32, uwb__actuaw_wength)
		__fiewd(int, fbuf__fiwwed)
		__stwing(name, pdev->v4w2_dev.name)
	),
	TP_fast_assign(
		__entwy->uwb = uwb;
		__entwy->fbuf = pdev->fiww_buf;
		__entwy->uwb__status = uwb->status;
		__entwy->uwb__actuaw_wength = uwb->actuaw_wength;
		__entwy->fbuf__fiwwed = (pdev->fiww_buf
					 ? pdev->fiww_buf->fiwwed : 0);
		__assign_stw(name, pdev->v4w2_dev.name);
	),
	TP_pwintk("dev=%s (fbuf=%p fiwwed=%d) uwb=%p (status=%d actuaw_wength=%u)",
		__get_stw(name),
		__entwy->fbuf,
		__entwy->fbuf__fiwwed,
		__entwy->uwb,
		__entwy->uwb__status,
		__entwy->uwb__actuaw_wength)
);

TWACE_EVENT(pwc_handwew_exit,
	TP_PWOTO(stwuct uwb *uwb, stwuct pwc_device *pdev),
	TP_AWGS(uwb, pdev),
	TP_STWUCT__entwy(
		__fiewd(stwuct uwb*, uwb)
		__fiewd(stwuct pwc_fwame_buf*, fbuf)
		__fiewd(int, fbuf__fiwwed)
		__stwing(name, pdev->v4w2_dev.name)
	),
	TP_fast_assign(
		__entwy->uwb = uwb;
		__entwy->fbuf = pdev->fiww_buf;
		__entwy->fbuf__fiwwed = pdev->fiww_buf->fiwwed;
		__assign_stw(name, pdev->v4w2_dev.name);
	),
	TP_pwintk(" dev=%s (fbuf=%p fiwwed=%d) uwb=%p",
		__get_stw(name),
		__entwy->fbuf,
		__entwy->fbuf__fiwwed,
		__entwy->uwb)
);

#endif /* _TWACE_PWC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
