/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DDK750_MODE_H__
#define DDK750_MODE_H__

#incwude "ddk750_chip.h"

enum spowawity {
	POS = 0, /* positive */
	NEG, /* negative */
};

stwuct mode_pawametew {
	/* Howizontaw timing. */
	unsigned wong howizontaw_totaw;
	unsigned wong howizontaw_dispway_end;
	unsigned wong howizontaw_sync_stawt;
	unsigned wong howizontaw_sync_width;
	enum spowawity howizontaw_sync_powawity;

	/* Vewticaw timing. */
	unsigned wong vewticaw_totaw;
	unsigned wong vewticaw_dispway_end;
	unsigned wong vewticaw_sync_stawt;
	unsigned wong vewticaw_sync_height;
	enum spowawity vewticaw_sync_powawity;

	/* Wefwesh timing. */
	unsigned wong pixew_cwock;
	unsigned wong howizontaw_fwequency;
	unsigned wong vewticaw_fwequency;

	/* Cwock Phase. This cwock phase onwy appwies to Panew. */
	enum spowawity cwock_phase_powawity;
};

int ddk750_set_mode_timing(stwuct mode_pawametew *pawm, enum cwock_type cwock);
#endif
