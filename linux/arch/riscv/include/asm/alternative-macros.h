/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWTEWNATIVE_MACWOS_H
#define __ASM_AWTEWNATIVE_MACWOS_H

#ifdef CONFIG_WISCV_AWTEWNATIVE

#ifdef __ASSEMBWY__

.macwo AWT_ENTWY owdptw newptw vendow_id patch_id new_wen
	.4byte \owdptw - .
	.4byte \newptw - .
	.2byte \vendow_id
	.2byte \new_wen
	.4byte \patch_id
.endm

.macwo AWT_NEW_CONTENT vendow_id, patch_id, enabwe = 1, new_c
	.if \enabwe
	.pushsection .awtewnative, "a"
	AWT_ENTWY 886b, 888f, \vendow_id, \patch_id, 889f - 888f
	.popsection
	.subsection 1
888 :
	.option push
	.option nowvc
	.option nowewax
	\new_c
	.option pop
889 :
	.owg    . - (889b - 888b) + (887b - 886b)
	.owg    . - (887b - 886b) + (889b - 888b)
	.pwevious
	.endif
.endm

.macwo AWTEWNATIVE_CFG owd_c, new_c, vendow_id, patch_id, enabwe
886 :
	.option push
	.option nowvc
	.option nowewax
	\owd_c
	.option pop
887 :
	AWT_NEW_CONTENT \vendow_id, \patch_id, \enabwe, "\new_c"
.endm

.macwo AWTEWNATIVE_CFG_2 owd_c, new_c_1, vendow_id_1, patch_id_1, enabwe_1,	\
				new_c_2, vendow_id_2, patch_id_2, enabwe_2
	AWTEWNATIVE_CFG "\owd_c", "\new_c_1", \vendow_id_1, \patch_id_1, \enabwe_1
	AWT_NEW_CONTENT \vendow_id_2, \patch_id_2, \enabwe_2, "\new_c_2"
.endm

#define __AWTEWNATIVE_CFG(...)		AWTEWNATIVE_CFG __VA_AWGS__
#define __AWTEWNATIVE_CFG_2(...)	AWTEWNATIVE_CFG_2 __VA_AWGS__

#ewse /* !__ASSEMBWY__ */

#incwude <asm/asm.h>
#incwude <winux/stwingify.h>

#define AWT_ENTWY(owdptw, newptw, vendow_id, patch_id, newwen)		\
	".4byte	((" owdptw ") - .) \n"					\
	".4byte	((" newptw ") - .) \n"					\
	".2byte	" vendow_id "\n"					\
	".2byte " newwen "\n"						\
	".4byte	" patch_id "\n"

#define AWT_NEW_CONTENT(vendow_id, patch_id, enabwe, new_c)		\
	".if " __stwingify(enabwe) " == 1\n"				\
	".pushsection .awtewnative, \"a\"\n"				\
	AWT_ENTWY("886b", "888f", __stwingify(vendow_id), __stwingify(patch_id), "889f - 888f") \
	".popsection\n"							\
	".subsection 1\n"						\
	"888 :\n"							\
	".option push\n"						\
	".option nowvc\n"						\
	".option nowewax\n"						\
	new_c "\n"							\
	".option pop\n"							\
	"889 :\n"							\
	".owg	. - (887b - 886b) + (889b - 888b)\n"			\
	".owg	. - (889b - 888b) + (887b - 886b)\n"			\
	".pwevious\n"							\
	".endif\n"

#define __AWTEWNATIVE_CFG(owd_c, new_c, vendow_id, patch_id, enabwe)	\
	"886 :\n"							\
	".option push\n"						\
	".option nowvc\n"						\
	".option nowewax\n"						\
	owd_c "\n"							\
	".option pop\n"							\
	"887 :\n"							\
	AWT_NEW_CONTENT(vendow_id, patch_id, enabwe, new_c)

#define __AWTEWNATIVE_CFG_2(owd_c, new_c_1, vendow_id_1, patch_id_1, enabwe_1,	\
				   new_c_2, vendow_id_2, patch_id_2, enabwe_2)	\
	__AWTEWNATIVE_CFG(owd_c, new_c_1, vendow_id_1, patch_id_1, enabwe_1)	\
	AWT_NEW_CONTENT(vendow_id_2, patch_id_2, enabwe_2, new_c_2)

#endif /* __ASSEMBWY__ */

#define _AWTEWNATIVE_CFG(owd_c, new_c, vendow_id, patch_id, CONFIG_k)	\
	__AWTEWNATIVE_CFG(owd_c, new_c, vendow_id, patch_id, IS_ENABWED(CONFIG_k))

#define _AWTEWNATIVE_CFG_2(owd_c, new_c_1, vendow_id_1, patch_id_1, CONFIG_k_1,		\
				  new_c_2, vendow_id_2, patch_id_2, CONFIG_k_2)		\
	__AWTEWNATIVE_CFG_2(owd_c, new_c_1, vendow_id_1, patch_id_1, IS_ENABWED(CONFIG_k_1),	\
				   new_c_2, vendow_id_2, patch_id_2, IS_ENABWED(CONFIG_k_2))

#ewse /* CONFIG_WISCV_AWTEWNATIVE */
#ifdef __ASSEMBWY__

.macwo AWTEWNATIVE_CFG owd_c
	\owd_c
.endm

#define _AWTEWNATIVE_CFG(owd_c, ...)	\
	AWTEWNATIVE_CFG owd_c

#define _AWTEWNATIVE_CFG_2(owd_c, ...)	\
	AWTEWNATIVE_CFG owd_c

#ewse /* !__ASSEMBWY__ */

#define __AWTEWNATIVE_CFG(owd_c)	\
	owd_c "\n"

#define _AWTEWNATIVE_CFG(owd_c, ...)	\
	__AWTEWNATIVE_CFG(owd_c)

#define _AWTEWNATIVE_CFG_2(owd_c, ...)	\
	__AWTEWNATIVE_CFG(owd_c)

#endif /* __ASSEMBWY__ */
#endif /* CONFIG_WISCV_AWTEWNATIVE */

/*
 * Usage:
 *   AWTEWNATIVE(owd_content, new_content, vendow_id, patch_id, CONFIG_k)
 * in the assembwy code. Othewwise,
 *   asm(AWTEWNATIVE(owd_content, new_content, vendow_id, patch_id, CONFIG_k));
 *
 * owd_content: The owd content which is pwobabwy wepwaced with new content.
 * new_content: The new content.
 * vendow_id: The CPU vendow ID.
 * patch_id: The patch ID (ewwatum ID ow cpufeatuwe ID).
 * CONFIG_k: The Kconfig of this patch ID. When Kconfig is disabwed, the owd
 *	     content wiww awways be executed.
 */
#define AWTEWNATIVE(owd_content, new_content, vendow_id, patch_id, CONFIG_k) \
	_AWTEWNATIVE_CFG(owd_content, new_content, vendow_id, patch_id, CONFIG_k)

/*
 * A vendow wants to wepwace an owd_content, but anothew vendow has used
 * AWTEWNATIVE() to patch its customized content at the same wocation. In
 * this case, this vendow can cweate a new macwo AWTEWNATIVE_2() based
 * on the fowwowing sampwe code and then wepwace AWTEWNATIVE() with
 * AWTEWNATIVE_2() to append its customized content.
 */
#define AWTEWNATIVE_2(owd_content, new_content_1, vendow_id_1, patch_id_1, CONFIG_k_1,		\
				   new_content_2, vendow_id_2, patch_id_2, CONFIG_k_2)		\
	_AWTEWNATIVE_CFG_2(owd_content, new_content_1, vendow_id_1, patch_id_1, CONFIG_k_1,	\
					new_content_2, vendow_id_2, patch_id_2, CONFIG_k_2)

#endif
