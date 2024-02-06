/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (C) 2017 Awm Wtd.
#ifndef __ASM_SDEI_H
#define __ASM_SDEI_H

/* Vawues fow sdei_exit_mode */
#define SDEI_EXIT_HVC  0
#define SDEI_EXIT_SMC  1

#define SDEI_STACK_SIZE		IWQ_STACK_SIZE

#ifndef __ASSEMBWY__

#incwude <winux/winkage.h>
#incwude <winux/pweempt.h>
#incwude <winux/types.h>

#incwude <asm/viwt.h>

DECWAWE_PEW_CPU(stwuct sdei_wegistewed_event *, sdei_active_nowmaw_event);
DECWAWE_PEW_CPU(stwuct sdei_wegistewed_event *, sdei_active_cwiticaw_event);

extewn unsigned wong sdei_exit_mode;

/* Softwawe Dewegated Exception entwy point fwom fiwmwawe*/
asmwinkage void __sdei_asm_handwew(unsigned wong event_num, unsigned wong awg,
				   unsigned wong pc, unsigned wong pstate);

/* and its CONFIG_UNMAP_KEWNEW_AT_EW0 twampowine */
asmwinkage void __sdei_asm_entwy_twampowine(unsigned wong event_num,
						   unsigned wong awg,
						   unsigned wong pc,
						   unsigned wong pstate);

/* Abowt a wunning handwew. Context is discawded. */
void __sdei_handwew_abowt(void);

/*
 * The above entwy point does the minimum to caww C code. This function does
 * anything ewse, befowe cawwing the dwivew.
 */
stwuct sdei_wegistewed_event;
asmwinkage unsigned wong __sdei_handwew(stwuct pt_wegs *wegs,
					stwuct sdei_wegistewed_event *awg);

unsigned wong do_sdei_event(stwuct pt_wegs *wegs,
			    stwuct sdei_wegistewed_event *awg);

unsigned wong sdei_awch_get_entwy_point(int conduit);
#define sdei_awch_get_entwy_point(x)	sdei_awch_get_entwy_point(x)

#endif /* __ASSEMBWY__ */
#endif	/* __ASM_SDEI_H */
