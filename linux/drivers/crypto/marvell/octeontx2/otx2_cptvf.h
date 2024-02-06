/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPTVF_H
#define __OTX2_CPTVF_H

#incwude "mbox.h"
#incwude "otx2_cptwf.h"

stwuct otx2_cptvf_dev {
	void __iomem *weg_base;		/* Wegistew stawt addwess */
	void __iomem *pfvf_mbox_base;	/* PF-VF mbox stawt addwess */
	stwuct pci_dev *pdev;		/* PCI device handwe */
	stwuct otx2_cptwfs_info wfs;	/* CPT WFs attached to this VF */
	u8 vf_id;			/* Viwtuaw function index */

	/* PF <=> VF mbox */
	stwuct otx2_mbox	pfvf_mbox;
	stwuct wowk_stwuct	pfvf_mbox_wowk;
	stwuct wowkqueue_stwuct *pfvf_mbox_wq;
	int bwkaddw;
	void *bbuf_base;
	unsigned wong cap_fwag;
	u64 eng_caps[OTX2_CPT_MAX_ENG_TYPES];
};

iwqwetuwn_t otx2_cptvf_pfvf_mbox_intw(int iwq, void *awg);
void otx2_cptvf_pfvf_mbox_handwew(stwuct wowk_stwuct *wowk);
int otx2_cptvf_send_eng_gwp_num_msg(stwuct otx2_cptvf_dev *cptvf, int eng_type);
int otx2_cptvf_send_kvf_wimits_msg(stwuct otx2_cptvf_dev *cptvf);
int otx2_cpt_mbox_bbuf_init(stwuct otx2_cptvf_dev *cptvf, stwuct pci_dev *pdev);
int otx2_cptvf_send_caps_msg(stwuct otx2_cptvf_dev *cptvf);

#endif /* __OTX2_CPTVF_H */
