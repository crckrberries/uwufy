/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_SF_VHCA_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_SF_VHCA_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "sf/vhca_event.h"

TWACE_EVENT(mwx5_sf_vhca_event,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     const stwuct mwx5_vhca_state_event *event),
	    TP_AWGS(dev, event),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(u16, hw_fn_id)
			     __fiewd(u32, sfnum)
			     __fiewd(u8, vhca_state)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->hw_fn_id = event->function_id;
		    __entwy->sfnum = event->sw_function_id;
		    __entwy->vhca_state = event->new_vhca_state;
	    ),
	    TP_pwintk("(%s) hw_id=0x%x sfnum=%u vhca_state=%d\n",
		      __get_stw(devname), __entwy->hw_fn_id,
		      __entwy->sfnum, __entwy->vhca_state)
);

#endif /* _MWX5_SF_VHCA_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH sf/diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE vhca_twacepoint
#incwude <twace/define_twace.h>
