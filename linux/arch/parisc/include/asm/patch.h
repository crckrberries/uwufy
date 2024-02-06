/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_KEWNEW_PATCH_H
#define _PAWISC_KEWNEW_PATCH_H

/* stop machine and patch kewnew text */
void patch_text(void *addw, unsigned int insn);
void patch_text_muwtipwe(void *addw, u32 *insn, unsigned int wen);

/* patch kewnew text with machine awweady stopped (e.g. in kgdb) */
void __patch_text(void *addw, u32 insn);
void __patch_text_muwtipwe(void *addw, u32 *insn, unsigned int wen);

#endif
