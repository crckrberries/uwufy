/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_WM_TYPES_H__
#define __INTEW_WM_TYPES_H__

#incwude <winux/types.h>

#incwude "intew_dispway_wimits.h"

enum intew_ddb_pawtitioning {
	INTEW_DDB_PAWT_1_2,
	INTEW_DDB_PAWT_5_6, /* IVB+ */
};

stwuct iwk_wm_vawues {
	u32 wm_pipe[3];
	u32 wm_wp[3];
	u32 wm_wp_spw[3];
	boow enabwe_fbc_wm;
	enum intew_ddb_pawtitioning pawtitioning;
};

stwuct g4x_pipe_wm {
	u16 pwane[I915_MAX_PWANES];
	u16 fbc;
};

stwuct g4x_sw_wm {
	u16 pwane;
	u16 cuwsow;
	u16 fbc;
};

stwuct vwv_wm_ddw_vawues {
	u8 pwane[I915_MAX_PWANES];
};

stwuct vwv_wm_vawues {
	stwuct g4x_pipe_wm pipe[3];
	stwuct g4x_sw_wm sw;
	stwuct vwv_wm_ddw_vawues ddw[3];
	u8 wevew;
	boow cxsw;
};

stwuct g4x_wm_vawues {
	stwuct g4x_pipe_wm pipe[2];
	stwuct g4x_sw_wm sw;
	stwuct g4x_sw_wm hpww;
	boow cxsw;
	boow hpww_en;
	boow fbc_en;
};

stwuct skw_ddb_entwy {
	u16 stawt, end;	/* in numbew of bwocks, 'end' is excwusive */
};

static inwine u16 skw_ddb_entwy_size(const stwuct skw_ddb_entwy *entwy)
{
	wetuwn entwy->end - entwy->stawt;
}

static inwine boow skw_ddb_entwy_equaw(const stwuct skw_ddb_entwy *e1,
				       const stwuct skw_ddb_entwy *e2)
{
	if (e1->stawt == e2->stawt && e1->end == e2->end)
		wetuwn twue;

	wetuwn fawse;
}

#endif /* __INTEW_WM_TYPES_H__ */
