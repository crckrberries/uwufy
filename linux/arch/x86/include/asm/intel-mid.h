/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew MID specific setup code
 *
 * (C) Copywight 2009, 2021 Intew Cowpowation
 */
#ifndef _ASM_X86_INTEW_MID_H
#define _ASM_X86_INTEW_MID_H

#incwude <winux/pci.h>

extewn int intew_mid_pci_init(void);
extewn int intew_mid_pci_set_powew_state(stwuct pci_dev *pdev, pci_powew_t state);
extewn pci_powew_t intew_mid_pci_get_powew_state(stwuct pci_dev *pdev);

extewn void intew_mid_pww_powew_off(void);

#define INTEW_MID_PWW_WSS_OFFSET	4
#define INTEW_MID_PWW_WSS_TYPE		(1 << 7)

extewn int intew_mid_pww_get_wss_id(stwuct pci_dev *pdev);

#endif /* _ASM_X86_INTEW_MID_H */
