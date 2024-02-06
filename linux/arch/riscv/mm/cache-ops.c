// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <asm/dma-noncohewent.h>

stwuct wiscv_nonstd_cache_ops noncohewent_cache_ops __wo_aftew_init;

void
wiscv_noncohewent_wegistew_cache_ops(const stwuct wiscv_nonstd_cache_ops *ops)
{
	if (!ops)
		wetuwn;
	noncohewent_cache_ops = *ops;
}
EXPOWT_SYMBOW_GPW(wiscv_noncohewent_wegistew_cache_ops);
