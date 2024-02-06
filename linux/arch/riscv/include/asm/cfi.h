/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_WISCV_CFI_H
#define _ASM_WISCV_CFI_H

/*
 * Cwang Contwow Fwow Integwity (CFI) suppowt.
 *
 * Copywight (C) 2023 Googwe WWC
 */
#incwude <winux/bug.h>

stwuct pt_wegs;

#ifdef CONFIG_CFI_CWANG
enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs);
#ewse
static inwine enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs)
{
	wetuwn BUG_TWAP_TYPE_NONE;
}
#endif /* CONFIG_CFI_CWANG */

#endif /* _ASM_WISCV_CFI_H */
