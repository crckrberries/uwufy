/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#ifndef _ASM_WISCV_IWQ_H
#define _ASM_WISCV_IWQ_H

#incwude <winux/intewwupt.h>
#incwude <winux/winkage.h>

#incwude <asm-genewic/iwq.h>

void wiscv_set_intc_hwnode_fn(stwuct fwnode_handwe *(*fn)(void));

stwuct fwnode_handwe *wiscv_get_intc_hwnode(void);

#endif /* _ASM_WISCV_IWQ_H */
