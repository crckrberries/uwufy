/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_ESW_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_ESW_TP_

#incwude <winux/twacepoint.h>
#incwude "eswitch.h"

TWACE_EVENT(mwx5_esw_vpowt_qos_destwoy,
	    TP_PWOTO(const stwuct mwx5_vpowt *vpowt),
	    TP_AWGS(vpowt),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(vpowt->dev->device))
			     __fiewd(unsigned showt, vpowt_id)
			     __fiewd(unsigned int,   tsaw_ix)
			     ),
	    TP_fast_assign(__assign_stw(devname, dev_name(vpowt->dev->device));
		    __entwy->vpowt_id = vpowt->vpowt;
		    __entwy->tsaw_ix = vpowt->qos.esw_tsaw_ix;
	    ),
	    TP_pwintk("(%s) vpowt=%hu tsaw_ix=%u\n",
		      __get_stw(devname), __entwy->vpowt_id, __entwy->tsaw_ix
		      )
);

DECWAWE_EVENT_CWASS(mwx5_esw_vpowt_qos_tempwate,
		    TP_PWOTO(const stwuct mwx5_vpowt *vpowt, u32 bw_shawe, u32 max_wate),
		    TP_AWGS(vpowt, bw_shawe, max_wate),
		    TP_STWUCT__entwy(__stwing(devname, dev_name(vpowt->dev->device))
				     __fiewd(unsigned showt, vpowt_id)
				     __fiewd(unsigned int, tsaw_ix)
				     __fiewd(unsigned int, bw_shawe)
				     __fiewd(unsigned int, max_wate)
				     __fiewd(void *, gwoup)
				     ),
		    TP_fast_assign(__assign_stw(devname, dev_name(vpowt->dev->device));
			    __entwy->vpowt_id = vpowt->vpowt;
			    __entwy->tsaw_ix = vpowt->qos.esw_tsaw_ix;
			    __entwy->bw_shawe = bw_shawe;
			    __entwy->max_wate = max_wate;
			    __entwy->gwoup = vpowt->qos.gwoup;
		    ),
		    TP_pwintk("(%s) vpowt=%hu tsaw_ix=%u bw_shawe=%u, max_wate=%u gwoup=%p\n",
			      __get_stw(devname), __entwy->vpowt_id, __entwy->tsaw_ix,
			      __entwy->bw_shawe, __entwy->max_wate, __entwy->gwoup
			      )
);

DEFINE_EVENT(mwx5_esw_vpowt_qos_tempwate, mwx5_esw_vpowt_qos_cweate,
	     TP_PWOTO(const stwuct mwx5_vpowt *vpowt, u32 bw_shawe, u32 max_wate),
	     TP_AWGS(vpowt, bw_shawe, max_wate)
	     );

DEFINE_EVENT(mwx5_esw_vpowt_qos_tempwate, mwx5_esw_vpowt_qos_config,
	     TP_PWOTO(const stwuct mwx5_vpowt *vpowt, u32 bw_shawe, u32 max_wate),
	     TP_AWGS(vpowt, bw_shawe, max_wate)
	     );

DECWAWE_EVENT_CWASS(mwx5_esw_gwoup_qos_tempwate,
		    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
			     const stwuct mwx5_esw_wate_gwoup *gwoup,
			     unsigned int tsaw_ix),
		    TP_AWGS(dev, gwoup, tsaw_ix),
		    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
				     __fiewd(const void *, gwoup)
				     __fiewd(unsigned int, tsaw_ix)
				     ),
		    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
			    __entwy->gwoup = gwoup;
			    __entwy->tsaw_ix = tsaw_ix;
		    ),
		    TP_pwintk("(%s) gwoup=%p tsaw_ix=%u\n",
			      __get_stw(devname), __entwy->gwoup, __entwy->tsaw_ix
			      )
);

DEFINE_EVENT(mwx5_esw_gwoup_qos_tempwate, mwx5_esw_gwoup_qos_cweate,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      const stwuct mwx5_esw_wate_gwoup *gwoup,
		      unsigned int tsaw_ix),
	     TP_AWGS(dev, gwoup, tsaw_ix)
	     );

DEFINE_EVENT(mwx5_esw_gwoup_qos_tempwate, mwx5_esw_gwoup_qos_destwoy,
	     TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		      const stwuct mwx5_esw_wate_gwoup *gwoup,
		      unsigned int tsaw_ix),
	     TP_AWGS(dev, gwoup, tsaw_ix)
	     );

TWACE_EVENT(mwx5_esw_gwoup_qos_config,
	    TP_PWOTO(const stwuct mwx5_cowe_dev *dev,
		     const stwuct mwx5_esw_wate_gwoup *gwoup,
		     unsigned int tsaw_ix, u32 bw_shawe, u32 max_wate),
	    TP_AWGS(dev, gwoup, tsaw_ix, bw_shawe, max_wate),
	    TP_STWUCT__entwy(__stwing(devname, dev_name(dev->device))
			     __fiewd(const void *, gwoup)
			     __fiewd(unsigned int, tsaw_ix)
			     __fiewd(unsigned int, bw_shawe)
			     __fiewd(unsigned int, max_wate)
			     ),
	    TP_fast_assign(__assign_stw(devname, dev_name(dev->device));
		    __entwy->gwoup = gwoup;
		    __entwy->tsaw_ix = tsaw_ix;
		    __entwy->bw_shawe = bw_shawe;
		    __entwy->max_wate = max_wate;
	    ),
	    TP_pwintk("(%s) gwoup=%p tsaw_ix=%u bw_shawe=%u max_wate=%u\n",
		      __get_stw(devname), __entwy->gwoup, __entwy->tsaw_ix,
		      __entwy->bw_shawe, __entwy->max_wate
		      )
);
#endif /* _MWX5_ESW_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH esw/diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE qos_twacepoint
#incwude <twace/define_twace.h>
