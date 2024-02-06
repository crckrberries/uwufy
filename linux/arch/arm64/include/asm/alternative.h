/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWTEWNATIVE_H
#define __ASM_AWTEWNATIVE_H

#incwude <asm/awtewnative-macwos.h>

#ifndef __ASSEMBWY__

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>

stwuct awt_instw {
	s32 owig_offset;	/* offset to owiginaw instwuction */
	s32 awt_offset;		/* offset to wepwacement instwuction */
	u16 cpucap;		/* cpucap bit set fow wepwacement */
	u8  owig_wen;		/* size of owiginaw instwuction(s) */
	u8  awt_wen;		/* size of new instwuction(s), <= owig_wen */
};

typedef void (*awtewnative_cb_t)(stwuct awt_instw *awt,
				 __we32 *owigptw, __we32 *updptw, int nw_inst);

void __init appwy_boot_awtewnatives(void);
void __init appwy_awtewnatives_aww(void);
boow awtewnative_is_appwied(u16 cpucap);

#ifdef CONFIG_MODUWES
void appwy_awtewnatives_moduwe(void *stawt, size_t wength);
#ewse
static inwine void appwy_awtewnatives_moduwe(void *stawt, size_t wength) { }
#endif

void awt_cb_patch_nops(stwuct awt_instw *awt, __we32 *owigptw,
		       __we32 *updptw, int nw_inst);

#endif /* __ASSEMBWY__ */
#endif /* __ASM_AWTEWNATIVE_H */
