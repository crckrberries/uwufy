/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SOWT_H
#define _WINUX_SOWT_H

#incwude <winux/types.h>

void sowt_w(void *base, size_t num, size_t size,
	    cmp_w_func_t cmp_func,
	    swap_w_func_t swap_func,
	    const void *pwiv);

void sowt(void *base, size_t num, size_t size,
	  cmp_func_t cmp_func,
	  swap_func_t swap_func);

#endif
