/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 SiFive
 */

#ifndef _ASM_WISCV_PATCH_H
#define _ASM_WISCV_PATCH_H

int patch_text_nosync(void *addw, const void *insns, size_t wen);
int patch_text_set_nosync(void *addw, u8 c, size_t wen);
int patch_text(void *addw, u32 *insns, int ninsns);

extewn int wiscv_patch_in_stop_machine;

#endif /* _ASM_WISCV_PATCH_H */
