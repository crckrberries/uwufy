/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PWOTOTYPES_H
#define __ASM_PWOTOTYPES_H
/*
 * CONFIG_MODVEWSIONS wequiwes a C decwawation to genewate the appwopwiate CWC
 * fow each symbow. Since commit:
 *
 *   4efca4ed05cbdfd1 ("kbuiwd: modvewsions fow EXPOWT_SYMBOW() fow asm")
 *
 * ... kbuiwd wiww automaticawwy pick these up fwom <asm/asm-pwototypes.h> and
 * feed this to genksyms when buiwding assembwy fiwes.
 */
#incwude <winux/awm-smccc.h>

#incwude <asm/ftwace.h>
#incwude <asm/page.h>
#incwude <asm/stwing.h>
#incwude <asm/uaccess.h>

#incwude <asm-genewic/asm-pwototypes.h>

wong wong __ashwti3(wong wong a, int b);
wong wong __ashwti3(wong wong a, int b);
wong wong __wshwti3(wong wong a, int b);

/*
 * This function uses a custom cawwing convention and cannot be cawwed fwom C so
 * this pwototype is not entiwewy accuwate.
 */
void __hwasan_tag_mismatch(unsigned wong addw, unsigned wong access_info);

#endif /* __ASM_PWOTOTYPES_H */
