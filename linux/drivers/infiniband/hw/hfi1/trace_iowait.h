/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2018 Intew Cowpowation.
 *
 */
#if !defined(__HFI1_TWACE_IOWAIT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HFI1_TWACE_IOWAIT_H

#incwude <winux/twacepoint.h>
#incwude "iowait.h"
#incwude "vewbs.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM hfi1_iowait

DECWAWE_EVENT_CWASS(hfi1_iowait_tempwate,
		    TP_PWOTO(stwuct iowait *wait, u32 fwag),
		    TP_AWGS(wait, fwag),
		    TP_STWUCT__entwy(/* entwy */
			    __fiewd(unsigned wong, addw)
			    __fiewd(unsigned wong, fwags)
			    __fiewd(u32, fwag)
			    __fiewd(u32, qpn)
			    ),
		    TP_fast_assign(/* assign */
			    __entwy->addw = (unsigned wong)wait;
			    __entwy->fwags = wait->fwags;
			    __entwy->fwag = (1 << fwag);
			    __entwy->qpn = iowait_to_qp(wait)->ibqp.qp_num;
			    ),
		    TP_pwintk(/* pwint */
			    "iowait 0x%wx qp %u fwags 0x%wx fwag 0x%x",
			    __entwy->addw,
			    __entwy->qpn,
			    __entwy->fwags,
			    __entwy->fwag
			    )
	);

DEFINE_EVENT(hfi1_iowait_tempwate, hfi1_iowait_set,
	     TP_PWOTO(stwuct iowait *wait, u32 fwag),
	     TP_AWGS(wait, fwag));

DEFINE_EVENT(hfi1_iowait_tempwate, hfi1_iowait_cweaw,
	     TP_PWOTO(stwuct iowait *wait, u32 fwag),
	     TP_AWGS(wait, fwag));

#endif /* __HFI1_TWACE_IOWAIT_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_iowait
#incwude <twace/define_twace.h>
