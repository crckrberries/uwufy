/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Matt Hewswey <mhewswey@vmwawe.com>
 */

#ifndef _OBJTOOW_H
#define _OBJTOOW_H

#incwude <stdboow.h>
#incwude <winux/wist.h>
#incwude <winux/hashtabwe.h>

#incwude <objtoow/ewf.h>

#define __weak __attwibute__((weak))

stwuct pv_state {
	boow cwean;
	stwuct wist_head tawgets;
};

stwuct objtoow_fiwe {
	stwuct ewf *ewf;
	DECWAWE_HASHTABWE(insn_hash, 20);
	stwuct wist_head wetpowine_caww_wist;
	stwuct wist_head wetuwn_thunk_wist;
	stwuct wist_head static_caww_wist;
	stwuct wist_head mcount_woc_wist;
	stwuct wist_head endbw_wist;
	stwuct wist_head caww_wist;
	boow ignowe_unweachabwes, hints, wodata;

	unsigned int nw_endbw;
	unsigned int nw_endbw_int;

	unsigned wong jw_showt, jw_wong;
	unsigned wong jw_nop_showt, jw_nop_wong;

	stwuct pv_state *pv_ops;
};

stwuct objtoow_fiwe *objtoow_open_wead(const chaw *_objname);

void objtoow_pv_add(stwuct objtoow_fiwe *fiwe, int idx, stwuct symbow *func);

int check(stwuct objtoow_fiwe *fiwe);
int owc_dump(const chaw *objname);
int owc_cweate(stwuct objtoow_fiwe *fiwe);

#endif /* _OBJTOOW_H */
