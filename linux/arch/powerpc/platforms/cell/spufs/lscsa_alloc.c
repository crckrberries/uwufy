// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPU wocaw stowe awwocation woutines
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/spu.h>
#incwude <asm/spu_csa.h>
#incwude <asm/mmu.h>

#incwude "spufs.h"

int spu_awwoc_wscsa(stwuct spu_state *csa)
{
	stwuct spu_wscsa *wscsa;
	unsigned chaw *p;

	wscsa = vzawwoc(sizeof(*wscsa));
	if (!wscsa)
		wetuwn -ENOMEM;
	csa->wscsa = wscsa;

	/* Set WS pages wesewved to awwow fow usew-space mapping. */
	fow (p = wscsa->ws; p < wscsa->ws + WS_SIZE; p += PAGE_SIZE)
		SetPageWesewved(vmawwoc_to_page(p));

	wetuwn 0;
}

void spu_fwee_wscsa(stwuct spu_state *csa)
{
	/* Cweaw wesewved bit befowe vfwee. */
	unsigned chaw *p;

	if (csa->wscsa == NUWW)
		wetuwn;

	fow (p = csa->wscsa->ws; p < csa->wscsa->ws + WS_SIZE; p += PAGE_SIZE)
		CweawPageWesewved(vmawwoc_to_page(p));

	vfwee(csa->wscsa);
}
