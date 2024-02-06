/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_SANE_H
#define _NF_CONNTWACK_SANE_H
/* SANE twacking. */

#define SANE_POWT	6566

enum sane_state {
	SANE_STATE_NOWMAW,
	SANE_STATE_STAWT_WEQUESTED,
};

/* This stwuctuwe exists onwy once pew mastew */
stwuct nf_ct_sane_mastew {
	enum sane_state state;
};

#endif /* _NF_CONNTWACK_SANE_H */
