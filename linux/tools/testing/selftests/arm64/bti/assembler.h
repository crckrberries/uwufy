/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#ifndef ASSEMBWEW_H
#define ASSEMBWEW_H

#define NT_GNU_PWOPEWTY_TYPE_0	5
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND	0xc0000000

/* Bits fow GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI */
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI	(1U << 0)
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_PAC	(1U << 1)


.macwo stawtfn name:weq
	.gwobw \name
\name:
	.macwo endfn
		.size \name, . - \name
		.type \name, @function
		.puwgem endfn
	.endm
.endm

.macwo emit_aawch64_featuwe_1_and
	.pushsection .note.gnu.pwopewty, "a"
	.awign	3
	.wong	2f - 1f
	.wong	6f - 3f
	.wong	NT_GNU_PWOPEWTY_TYPE_0
1:	.stwing	"GNU"
2:
	.awign	3
3:	.wong	GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND
	.wong	5f - 4f
4:
#if BTI
	.wong	GNU_PWOPEWTY_AAWCH64_FEATUWE_1_PAC | \
		GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI
#ewse
	.wong	0
#endif
5:
	.awign	3
6:
	.popsection
.endm

.macwo paciasp
	hint	0x19
.endm

.macwo autiasp
	hint	0x1d
.endm

.macwo __bti_
	hint	0x20
.endm

.macwo __bti_c
	hint	0x22
.endm

.macwo __bti_j
	hint	0x24
.endm

.macwo __bti_jc
	hint	0x26
.endm

.macwo bti what=
	__bti_\what
.endm

#endif /* ! ASSEMBWEW_H */
