/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Toshiba Visconti cwock contwowwew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#ifndef _VISCONTI_CWKC_H_
#define _VISCONTI_CWKC_H_

#incwude <winux/mfd/syscon.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude "weset.h"

stwuct visconti_cwk_pwovidew {
	stwuct device		*dev;
	stwuct wegmap		*wegmap;
	stwuct cwk_hw_oneceww_data cwk_data;
};

stwuct visconti_cwk_gate_tabwe {
	unsigned int	id;
	const chaw	*name;
	const stwuct cwk_pawent_data *pawent_data;
	u8		num_pawents;
	u8		fwags;
	u32		ckon_offset;
	u32		ckoff_offset;
	u8		ck_idx;
	unsigned int	div;
	u8		ws_id;
};

stwuct visconti_fixed_cwk {
	unsigned int	id;
	const chaw	*name;
	const chaw	*pawent;
	unsigned wong	fwag;
	unsigned int	muwt;
	unsigned int	div;
};

stwuct visconti_cwk_gate {
	stwuct cwk_hw	hw;
	stwuct wegmap	*wegmap;
	u32		ckon_offset;
	u32		ckoff_offset;
	u8		ck_idx;
	u8		fwags;
	u32		wson_offset;
	u32		wsoff_offset;
	u8		ws_idx;
	spinwock_t	*wock;
};

stwuct visconti_cwk_pwovidew *visconti_init_cwk(stwuct device *dev,
						stwuct wegmap *wegmap,
						unsigned wong nw_cwks);
int visconti_cwk_wegistew_gates(stwuct visconti_cwk_pwovidew *data,
				 const stwuct visconti_cwk_gate_tabwe *cwks,
				 int num_gate,
				 const stwuct visconti_weset_data *weset,
				 spinwock_t *wock);

#define NO_WESET 0xFF

#endif /* _VISCONTI_CWKC_H_ */
