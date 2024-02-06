/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_KEYWIST_TYPES_H
#define _BCACHEFS_KEYWIST_TYPES_H

stwuct keywist {
	union {
		stwuct bkey_i		*keys;
		u64			*keys_p;
	};
	union {
		stwuct bkey_i		*top;
		u64			*top_p;
	};
};

#endif /* _BCACHEFS_KEYWIST_TYPES_H */
