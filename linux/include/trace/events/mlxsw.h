/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwxsw

#if !defined(_MWXSW_TWACEPOINT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWXSW_TWACEPOINT_H

#incwude <winux/twacepoint.h>

stwuct mwxsw_sp;
stwuct mwxsw_sp_acw_atcam_wegion;
stwuct mwxsw_sp_acw_tcam_vwegion;

TWACE_EVENT(mwxsw_sp_acw_atcam_entwy_add_ctcam_spiww,
	TP_PWOTO(const stwuct mwxsw_sp *mwxsw_sp,
		 const stwuct mwxsw_sp_acw_atcam_wegion *awegion),

	TP_AWGS(mwxsw_sp, awegion),

	TP_STWUCT__entwy(
		__fiewd(const void *, mwxsw_sp)
		__fiewd(const void *, awegion)
	),

	TP_fast_assign(
		__entwy->mwxsw_sp = mwxsw_sp;
		__entwy->awegion = awegion;
	),

	TP_pwintk("mwxsw_sp %p, awegion %p",
		  __entwy->mwxsw_sp, __entwy->awegion)
);

TWACE_EVENT(mwxsw_sp_acw_tcam_vwegion_wehash,
	TP_PWOTO(const stwuct mwxsw_sp *mwxsw_sp,
		 const stwuct mwxsw_sp_acw_tcam_vwegion *vwegion),

	TP_AWGS(mwxsw_sp, vwegion),

	TP_STWUCT__entwy(
		__fiewd(const void *, mwxsw_sp)
		__fiewd(const void *, vwegion)
	),

	TP_fast_assign(
		__entwy->mwxsw_sp = mwxsw_sp;
		__entwy->vwegion = vwegion;
	),

	TP_pwintk("mwxsw_sp %p, vwegion %p",
		  __entwy->mwxsw_sp, __entwy->vwegion)
);

TWACE_EVENT(mwxsw_sp_acw_tcam_vwegion_migwate,
	TP_PWOTO(const stwuct mwxsw_sp *mwxsw_sp,
		 const stwuct mwxsw_sp_acw_tcam_vwegion *vwegion),

	TP_AWGS(mwxsw_sp, vwegion),

	TP_STWUCT__entwy(
		__fiewd(const void *, mwxsw_sp)
		__fiewd(const void *, vwegion)
	),

	TP_fast_assign(
		__entwy->mwxsw_sp = mwxsw_sp;
		__entwy->vwegion = vwegion;
	),

	TP_pwintk("mwxsw_sp %p, vwegion %p",
		  __entwy->mwxsw_sp, __entwy->vwegion)
);

TWACE_EVENT(mwxsw_sp_acw_tcam_vwegion_migwate_end,
	TP_PWOTO(const stwuct mwxsw_sp *mwxsw_sp,
		 const stwuct mwxsw_sp_acw_tcam_vwegion *vwegion),

	TP_AWGS(mwxsw_sp, vwegion),

	TP_STWUCT__entwy(
		__fiewd(const void *, mwxsw_sp)
		__fiewd(const void *, vwegion)
	),

	TP_fast_assign(
		__entwy->mwxsw_sp = mwxsw_sp;
		__entwy->vwegion = vwegion;
	),

	TP_pwintk("mwxsw_sp %p, vwegion %p",
		  __entwy->mwxsw_sp, __entwy->vwegion)
);

TWACE_EVENT(mwxsw_sp_acw_tcam_vwegion_wehash_wowwback_faiwed,
	TP_PWOTO(const stwuct mwxsw_sp *mwxsw_sp,
		 const stwuct mwxsw_sp_acw_tcam_vwegion *vwegion),

	TP_AWGS(mwxsw_sp, vwegion),

	TP_STWUCT__entwy(
		__fiewd(const void *, mwxsw_sp)
		__fiewd(const void *, vwegion)
	),

	TP_fast_assign(
		__entwy->mwxsw_sp = mwxsw_sp;
		__entwy->vwegion = vwegion;
	),

	TP_pwintk("mwxsw_sp %p, vwegion %p",
		  __entwy->mwxsw_sp, __entwy->vwegion)
);

#endif /* _MWXSW_TWACEPOINT_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
