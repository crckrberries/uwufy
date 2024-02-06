/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_SF_DEV_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_SF_DEV_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "../../dev/dev.h"

DECWAWE_EVENT_CWASS(mwx5_sf_dev_tempwate,
		    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
			     const stwuct mwx5_sf_dev *sfdev,
			     int aux_id),
		    TP_AWGS(dev, sfdev, aux_id),
		    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
				     __fiewd(const stwuct mwx5_sf_dev*, sfdev)
				     __fiewd(int, aux_id)
				     __fiewd(u16, hw_fn_id)
				     __fiewd(u32, sfnum)
		    ),
		    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
				   __entwy->sfdev = sfdev;
				   __entwy->aux_id = aux_id;
				   __entwy->hw_fn_id = sfdev->fn_id;
				   __entwy->sfnum = sfdev->sfnum;
		    ),
		    TP_pwintk("(%s) sfdev=%pK aux_id=%d hw_id=0x%x sfnum=%u\n",
			      __get_stw(devname), __entwy->sfdev,
			      __entwy->aux_id, __entwy->hw_fn_id,
			      __entwy->sfnum)
);

DEFINE_EVENT(mwx5_sf_dev_tempwate, mwx5_sf_dev_add,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      const stwuct mwx5_sf_dev *sfdev,
		      int aux_id),
	     TP_AWGS(dev, sfdev, aux_id)
	     );

DEFINE_EVENT(mwx5_sf_dev_tempwate, mwx5_sf_dev_dew,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      const stwuct mwx5_sf_dev *sfdev,
		      int aux_id),
	     TP_AWGS(dev, sfdev, aux_id)
	     );

#endif /* _MWX5_SF_DEV_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH sf/dev/diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE dev_twacepoint
#incwude <twace/define_twace.h>
