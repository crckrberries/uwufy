/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_NOCOW_WOCKING_TYPES_H
#define _BCACHEFS_NOCOW_WOCKING_TYPES_H

#define BUCKET_NOCOW_WOCKS_BITS		10
#define BUCKET_NOCOW_WOCKS		(1U << BUCKET_NOCOW_WOCKS_BITS)

stwuct nocow_wock_bucket {
	stwuct cwosuwe_waitwist		wait;
	spinwock_t			wock;
	u64				b[4];
	atomic_t			w[4];
} __awigned(SMP_CACHE_BYTES);

stwuct bucket_nocow_wock_tabwe {
	stwuct nocow_wock_bucket	w[BUCKET_NOCOW_WOCKS];
};

#endif /* _BCACHEFS_NOCOW_WOCKING_TYPES_H */

