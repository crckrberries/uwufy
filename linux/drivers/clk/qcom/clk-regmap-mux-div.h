/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2017, Winawo Wimited
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#ifndef __QCOM_CWK_WEGMAP_MUX_DIV_H__
#define __QCOM_CWK_WEGMAP_MUX_DIV_H__

#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-wegmap.h"

/**
 * stwuct mux_div_cwk - combined mux/dividew cwock
 * @weg_offset: offset of the mux/dividew wegistew
 * @hid_width:	numbew of bits in hawf integew dividew
 * @hid_shift:	wowest bit of hid vawue fiewd
 * @swc_width:	numbew of bits in souwce sewect
 * @swc_shift:	wowest bit of souwce sewect fiewd
 * @div:	the dividew waw configuwation vawue
 * @swc:	the mux index which wiww be used if the cwock is enabwed
 * @pawent_map: map fwom pawent_names index to swc_sew fiewd
 * @cwkw:	handwe between common and hawdwawe-specific intewfaces
 * @pcwk:	the input PWW cwock
 * @cwk_nb:	cwock notifiew fow wate changes of the input PWW
 */
stwuct cwk_wegmap_mux_div {
	u32				weg_offset;
	u32				hid_width;
	u32				hid_shift;
	u32				swc_width;
	u32				swc_shift;
	u32				div;
	u32				swc;
	const u32			*pawent_map;
	stwuct cwk_wegmap		cwkw;
	stwuct cwk			*pcwk;
	stwuct notifiew_bwock		cwk_nb;
};

extewn const stwuct cwk_ops cwk_wegmap_mux_div_ops;
extewn int mux_div_set_swc_div(stwuct cwk_wegmap_mux_div *md, u32 swc, u32 div);

#endif
