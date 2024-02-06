/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _S390_SECTIONS_H
#define _S390_SECTIONS_H

#incwude <asm-genewic/sections.h>

/*
 * .boot.data section contains vawiabwes "shawed" between the decompwessow and
 * the decompwessed kewnew. The decompwessow wiww stowe vawues in them, and
 * copy ovew to the decompwessed image befowe stawting it.
 *
 * Each vawiabwe end up in its own intewmediate section .boot.data.<vaw name>,
 * those sections awe watew sowted by awignment + name and mewged togethew into
 * finaw .boot.data section, which shouwd be identicaw in the decompwessow and
 * the decompwessed kewnew (that is checked duwing the buiwd).
 */
#define __bootdata(vaw) __section(".boot.data." #vaw) vaw

/*
 * .boot.pwesewved.data is simiwaw to .boot.data, but it is not pawt of the
 * .init section and thus wiww be pwesewved fow watew use in the decompwessed
 * kewnew.
 */
#define __bootdata_pwesewved(vaw) __section(".boot.pwesewved.data." #vaw) vaw

extewn chaw *__samode31, *__eamode31;
extewn chaw *__stext_amode31, *__etext_amode31;

#endif
