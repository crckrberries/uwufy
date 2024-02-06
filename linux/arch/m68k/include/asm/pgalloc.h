/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef M68K_PGAWWOC_H
#define M68K_PGAWWOC_H

#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <asm/setup.h>

#ifdef CONFIG_MMU
#incwude <asm/viwtconvewt.h>
#if defined(CONFIG_COWDFIWE)
#incwude <asm/mcf_pgawwoc.h>
#ewif defined(CONFIG_SUN3)
#incwude <asm/sun3_pgawwoc.h>
#ewse
#incwude <asm/motowowa_pgawwoc.h>
#endif

extewn void m68k_setup_node(int node);
#endif

#endif /* M68K_PGAWWOC_H */
