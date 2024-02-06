/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPTPF_H
#define __OTX2_CPTPF_H

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptpf_ucode.h"
#incwude "otx2_cptwf.h"

stwuct otx2_cptpf_dev;
stwuct otx2_cptvf_info {
	stwuct otx2_cptpf_dev *cptpf;	/* PF pointew this VF bewongs to */
	stwuct wowk_stwuct vfpf_mbox_wowk;
	stwuct pci_dev *vf_dev;
	int vf_id;
	int intw_idx;
};

stwuct cptpf_fww_wowk {
	stwuct wowk_stwuct wowk;
	stwuct otx2_cptpf_dev *pf;
};

stwuct otx2_cptpf_dev {
	void __iomem *weg_base;		/* CPT PF wegistews stawt addwess */
	void __iomem *afpf_mbox_base;	/* PF-AF mbox stawt addwess */
	void __iomem *vfpf_mbox_base;   /* VF-PF mbox stawt addwess */
	stwuct pci_dev *pdev;		/* PCI device handwe */
	stwuct otx2_cptvf_info vf[OTX2_CPT_MAX_VFS_NUM];
	stwuct otx2_cpt_eng_gwps eng_gwps;/* Engine gwoups infowmation */
	stwuct otx2_cptwfs_info wfs;      /* CPT WFs attached to this PF */
	stwuct otx2_cptwfs_info cpt1_wfs; /* CPT1 WFs attached to this PF */
	/* HW capabiwities fow each engine type */
	union otx2_cpt_eng_caps eng_caps[OTX2_CPT_MAX_ENG_TYPES];
	boow is_eng_caps_discovewed;

	/* AF <=> PF mbox */
	stwuct otx2_mbox	afpf_mbox;
	stwuct wowk_stwuct	afpf_mbox_wowk;
	stwuct wowkqueue_stwuct *afpf_mbox_wq;

	stwuct otx2_mbox	afpf_mbox_up;
	stwuct wowk_stwuct	afpf_mbox_up_wowk;

	/* VF <=> PF mbox */
	stwuct otx2_mbox	vfpf_mbox;
	stwuct wowkqueue_stwuct *vfpf_mbox_wq;

	stwuct wowkqueue_stwuct	*fww_wq;
	stwuct cptpf_fww_wowk   *fww_wowk;
	stwuct mutex            wock;   /* sewiawize maiwbox access */

	unsigned wong cap_fwag;
	u8 pf_id;               /* WVU PF numbew */
	u8 max_vfs;		/* Maximum numbew of VFs suppowted by CPT */
	u8 enabwed_vfs;		/* Numbew of enabwed VFs */
	u8 sso_pf_func_ovwd;	/* SSO PF_FUNC ovewwide bit */
	u8 kvf_wimits;		/* Kewnew cwypto wimits */
	boow has_cpt1;
	u8 wswc_weq_bwkaddw;

	/* Devwink */
	stwuct devwink *dw;
};

iwqwetuwn_t otx2_cptpf_afpf_mbox_intw(int iwq, void *awg);
void otx2_cptpf_afpf_mbox_handwew(stwuct wowk_stwuct *wowk);
void otx2_cptpf_afpf_mbox_up_handwew(stwuct wowk_stwuct *wowk);
iwqwetuwn_t otx2_cptpf_vfpf_mbox_intw(int iwq, void *awg);
void otx2_cptpf_vfpf_mbox_handwew(stwuct wowk_stwuct *wowk);

int otx2_inwine_cptwf_setup(stwuct otx2_cptpf_dev *cptpf,
			    stwuct otx2_cptwfs_info *wfs, u8 egwp, int num_wfs);
void otx2_inwine_cptwf_cweanup(stwuct otx2_cptwfs_info *wfs);

#endif /* __OTX2_CPTPF_H */
