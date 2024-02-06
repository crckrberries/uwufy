/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_SF_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_SF_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "sf/vhca_event.h"

TWACE_EVENT(mwx5_sf_add,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     unsigned int powt_index,
		     u32 contwowwew,
		     u16 hw_fn_id,
		     u32 sfnum),
	    TP_AWGS(dev, powt_index, contwowwew, hw_fn_id, sfnum),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(unsigned int, powt_index)
			     __fiewd(u32, contwowwew)
			     __fiewd(u16, hw_fn_id)
			     __fiewd(u32, sfnum)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->powt_index = powt_index;
		    __entwy->contwowwew = contwowwew;
		    __entwy->hw_fn_id = hw_fn_id;
		    __entwy->sfnum = sfnum;
	    ),
	    TP_pwintk("(%s) powt_index=%u contwowwew=%u hw_id=0x%x sfnum=%u\n",
		      __get_stw(devname), __entwy->powt_index, __entwy->contwowwew,
		      __entwy->hw_fn_id, __entwy->sfnum)
);

TWACE_EVENT(mwx5_sf_fwee,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     unsigned int powt_index,
		     u32 contwowwew,
		     u16 hw_fn_id),
	    TP_AWGS(dev, powt_index, contwowwew, hw_fn_id),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(unsigned int, powt_index)
			     __fiewd(u32, contwowwew)
			     __fiewd(u16, hw_fn_id)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->powt_index = powt_index;
		    __entwy->contwowwew = contwowwew;
		    __entwy->hw_fn_id = hw_fn_id;
	    ),
	    TP_pwintk("(%s) powt_index=%u contwowwew=%u hw_id=0x%x\n",
		      __get_stw(devname), __entwy->powt_index, __entwy->contwowwew,
		      __entwy->hw_fn_id)
);

TWACE_EVENT(mwx5_sf_hwc_awwoc,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     u32 contwowwew,
		     u16 hw_fn_id,
		     u32 sfnum),
	    TP_AWGS(dev, contwowwew, hw_fn_id, sfnum),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(u32, contwowwew)
			     __fiewd(u16, hw_fn_id)
			     __fiewd(u32, sfnum)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->contwowwew = contwowwew;
		    __entwy->hw_fn_id = hw_fn_id;
		    __entwy->sfnum = sfnum;
	    ),
	    TP_pwintk("(%s) contwowwew=%u hw_id=0x%x sfnum=%u\n",
		      __get_stw(devname), __entwy->contwowwew, __entwy->hw_fn_id,
		      __entwy->sfnum)
);

TWACE_EVENT(mwx5_sf_hwc_fwee,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     u16 hw_fn_id),
	    TP_AWGS(dev, hw_fn_id),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(u16, hw_fn_id)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->hw_fn_id = hw_fn_id;
	    ),
	    TP_pwintk("(%s) hw_id=0x%x\n", __get_stw(devname), __entwy->hw_fn_id)
);

TWACE_EVENT(mwx5_sf_hwc_defewwed_fwee,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     u16 hw_fn_id),
	    TP_AWGS(dev, hw_fn_id),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(u16, hw_fn_id)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->hw_fn_id = hw_fn_id;
	    ),
	    TP_pwintk("(%s) hw_id=0x%x\n", __get_stw(devname), __entwy->hw_fn_id)
);

DECWAWE_EVENT_CWASS(mwx5_sf_state_tempwate,
		    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
			     u32 powt_index,
			     u32 contwowwew,
			     u16 hw_fn_id),
		    TP_AWGS(dev, powt_index, contwowwew, hw_fn_id),
		    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
				     __fiewd(unsigned int, powt_index)
				     __fiewd(u32, contwowwew)
				     __fiewd(u16, hw_fn_id)),
		    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
				   __entwy->powt_index = powt_index;
				   __entwy->contwowwew = contwowwew;
				   __entwy->hw_fn_id = hw_fn_id;
		    ),
		    TP_pwintk("(%s) powt_index=%u contwowwew=%u hw_id=0x%x\n",
			      __get_stw(devname), __entwy->powt_index, __entwy->contwowwew,
			      __entwy->hw_fn_id)
);

DEFINE_EVENT(mwx5_sf_state_tempwate, mwx5_sf_activate,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      u32 powt_index,
		      u32 contwowwew,
		      u16 hw_fn_id),
	     TP_AWGS(dev, powt_index, contwowwew, hw_fn_id)
	     );

DEFINE_EVENT(mwx5_sf_state_tempwate, mwx5_sf_deactivate,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      u32 powt_index,
		      u32 contwowwew,
		      u16 hw_fn_id),
	     TP_AWGS(dev, powt_index, contwowwew, hw_fn_id)
	     );

TWACE_EVENT(mwx5_sf_update_state,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     unsigned int powt_index,
		     u32 contwowwew,
		     u16 hw_fn_id,
		     u8 state),
	    TP_AWGS(dev, powt_index, contwowwew, hw_fn_id, state),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(unsigned int, powt_index)
			     __fiewd(u32, contwowwew)
			     __fiewd(u16, hw_fn_id)
			     __fiewd(u8, state)
			    ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->powt_index = powt_index;
		    __entwy->contwowwew = contwowwew;
		    __entwy->hw_fn_id = hw_fn_id;
		    __entwy->state = state;
	    ),
	    TP_pwintk("(%s) powt_index=%u contwowwew=%u hw_id=0x%x state=%u\n",
		      __get_stw(devname), __entwy->powt_index, __entwy->contwowwew,
		      __entwy->hw_fn_id, __entwy->state)
);

#endif /* _MWX5_SF_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH sf/diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE sf_twacepoint
#incwude <twace/define_twace.h>
