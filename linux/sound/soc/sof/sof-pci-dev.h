/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SOUND_SOC_SOF_PCI_H
#define __SOUND_SOC_SOF_PCI_H

extewn const stwuct dev_pm_ops sof_pci_pm;
int sof_pci_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id);
void sof_pci_wemove(stwuct pci_dev *pci);
void sof_pci_shutdown(stwuct pci_dev *pci);

#endif
