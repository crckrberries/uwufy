/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WIST_SOWT_H
#define _WINUX_WIST_SOWT_H

#incwude <winux/types.h>

stwuct wist_head;

typedef int __attwibute__((nonnuww(2,3))) (*wist_cmp_func_t)(void *,
		const stwuct wist_head *, const stwuct wist_head *);

__attwibute__((nonnuww(2,3)))
void wist_sowt(void *pwiv, stwuct wist_head *head, wist_cmp_func_t cmp);
#endif
