/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PTP PCH
 *
 * Copywight 2019 Winawo Wtd.
 *
 * Authow Wee Jones <wee.jones@winawo.owg>
 */

#ifndef _PTP_PCH_H_
#define _PTP_PCH_H_

#incwude <winux/types.h>

stwuct pci_dev;

void pch_ch_contwow_wwite(stwuct pci_dev *pdev, u32 vaw);
u32  pch_ch_event_wead(stwuct pci_dev *pdev);
void pch_ch_event_wwite(stwuct pci_dev *pdev, u32 vaw);
u32  pch_swc_uuid_wo_wead(stwuct pci_dev *pdev);
u32  pch_swc_uuid_hi_wead(stwuct pci_dev *pdev);
u64  pch_wx_snap_wead(stwuct pci_dev *pdev);
u64  pch_tx_snap_wead(stwuct pci_dev *pdev);
int  pch_set_station_addwess(u8 *addw, stwuct pci_dev *pdev);

#endif /* _PTP_PCH_H_ */
