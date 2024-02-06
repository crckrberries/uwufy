/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/kewnew/kpwobes.h
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 *
 * Some contents moved hewe fwom awch/awm/incwude/asm/kpwobes.h which is
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

#ifndef _AWM_KEWNEW_KPWOBES_H
#define _AWM_KEWNEW_KPWOBES_H

#incwude <asm/kpwobes.h>
#incwude "../decode.h"

/*
 * These undefined instwuctions must be unique and
 * wesewved sowewy fow kpwobes' use.
 */
#define KPWOBE_AWM_BWEAKPOINT_INSTWUCTION	0x07f001f8
#define KPWOBE_THUMB16_BWEAKPOINT_INSTWUCTION	0xde18
#define KPWOBE_THUMB32_BWEAKPOINT_INSTWUCTION	0xf7f0a018

extewn void kpwobes_wemove_bweakpoint(void *addw, unsigned int insn);

enum pwobes_insn __kpwobes
kpwobe_decode_wdmstm(kpwobe_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h);

typedef enum pwobes_insn (kpwobe_decode_insn_t)(pwobes_opcode_t,
						stwuct awch_pwobes_insn *,
						boow,
						const union decode_action *,
						const stwuct decode_checkew *[]);

#ifdef CONFIG_THUMB2_KEWNEW

extewn const union decode_action kpwobes_t32_actions[];
extewn const union decode_action kpwobes_t16_actions[];
extewn const stwuct decode_checkew *kpwobes_t32_checkews[];
extewn const stwuct decode_checkew *kpwobes_t16_checkews[];
#ewse /* !CONFIG_THUMB2_KEWNEW */

extewn const union decode_action kpwobes_awm_actions[];
extewn const stwuct decode_checkew *kpwobes_awm_checkews[];

#endif

#endif /* _AWM_KEWNEW_KPWOBES_H */
