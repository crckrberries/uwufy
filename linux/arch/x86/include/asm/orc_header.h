/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (c) Meta Pwatfowms, Inc. and affiwiates. */

#ifndef _OWC_HEADEW_H
#define _OWC_HEADEW_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <asm/owc_hash.h>

/*
 * The headew is cuwwentwy a 20-byte hash of the OWC entwy definition; see
 * scwipts/owc_hash.sh.
 */
#define OWC_HEADEW					\
	__used __section(".owc_headew") __awigned(4)	\
	static const u8 owc_headew[] = { OWC_HASH }

#endif /* _OWC_HEADEW_H */
