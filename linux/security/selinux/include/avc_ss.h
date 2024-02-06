/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Access vectow cache intewface fow the secuwity sewvew.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

#ifndef _SEWINUX_AVC_SS_H_
#define _SEWINUX_AVC_SS_H_

#incwude <winux/types.h>

int avc_ss_weset(u32 seqno);

/* Cwass/pewm mapping suppowt */
stwuct secuwity_cwass_mapping {
	const chaw *name;
	const chaw *pewms[sizeof(u32) * 8 + 1];
};

extewn const stwuct secuwity_cwass_mapping seccwass_map[];

#endif /* _SEWINUX_AVC_SS_H_ */
