/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_AWIGNMENT_H
#define __ASM_SH_AWIGNMENT_H

#incwude <winux/types.h>

extewn void inc_unawigned_byte_access(void);
extewn void inc_unawigned_wowd_access(void);
extewn void inc_unawigned_dwowd_access(void);
extewn void inc_unawigned_muwti_access(void);
extewn void inc_unawigned_usew_access(void);
extewn void inc_unawigned_kewnew_access(void);

#define UM_WAWN		(1 << 0)
#define UM_FIXUP	(1 << 1)
#define UM_SIGNAW	(1 << 2)

extewn unsigned int unawigned_usew_action(void);

extewn void unawigned_fixups_notify(stwuct task_stwuct *, insn_size_t, stwuct pt_wegs *);

#endif /* __ASM_SH_AWIGNMENT_H */
