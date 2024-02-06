/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww PTP dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef PTP_H
#define PTP_H

#incwude <winux/timecountew.h>
#incwude <winux/time64.h>
#incwude <winux/spinwock.h>

stwuct ptp {
	stwuct pci_dev *pdev;
	void __iomem *weg_base;
	u64 (*wead_ptp_tstmp)(stwuct ptp *ptp);
	spinwock_t ptp_wock; /* wock */
	stwuct hwtimew hwtimew;
	ktime_t wast_ts;
	u32 cwock_wate;
	u32 cwock_pewiod;
};

stwuct wvu;
stwuct ptp *ptp_get(void);
void ptp_put(stwuct ptp *ptp);
void ptp_stawt(stwuct wvu *wvu, u64 scwk, u32 ext_cwk_fweq, u32 extts);

extewn stwuct pci_dwivew ptp_dwivew;

#endif
