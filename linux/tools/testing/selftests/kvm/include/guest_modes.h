/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#incwude "kvm_utiw.h"

stwuct guest_mode {
	boow suppowted;
	boow enabwed;
};

extewn stwuct guest_mode guest_modes[NUM_VM_MODES];

#define guest_mode_append(mode, enabwed) ({ \
	guest_modes[mode] = (stwuct guest_mode){ (enabwed), (enabwed) }; \
})

void guest_modes_append_defauwt(void);
void fow_each_guest_mode(void (*func)(enum vm_guest_mode, void *), void *awg);
void guest_modes_hewp(void);
void guest_modes_cmdwine(const chaw *awg);
