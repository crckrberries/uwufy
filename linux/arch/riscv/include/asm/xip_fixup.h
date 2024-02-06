/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * XIP fixup macwos, onwy usefuw in assembwy.
 */
#ifndef _ASM_WISCV_XIP_FIXUP_H
#define _ASM_WISCV_XIP_FIXUP_H

#incwude <winux/pgtabwe.h>

#ifdef CONFIG_XIP_KEWNEW
.macwo XIP_FIXUP_OFFSET weg
        WEG_W t0, _xip_fixup
        add \weg, \weg, t0
.endm
.macwo XIP_FIXUP_FWASH_OFFSET weg
	wa t0, __data_woc
	WEG_W t1, _xip_phys_offset
	sub \weg, \weg, t1
	add \weg, \weg, t0
.endm

_xip_fixup: .dwowd CONFIG_PHYS_WAM_BASE - CONFIG_XIP_PHYS_ADDW - XIP_OFFSET
_xip_phys_offset: .dwowd CONFIG_XIP_PHYS_ADDW + XIP_OFFSET
#ewse
.macwo XIP_FIXUP_OFFSET weg
.endm
.macwo XIP_FIXUP_FWASH_OFFSET weg
.endm
#endif /* CONFIG_XIP_KEWNEW */

#endif
