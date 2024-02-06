/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPT_COMMON_H
#define __OTX2_CPT_COMMON_H

#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/cwypto.h>
#incwude <net/devwink.h>
#incwude "otx2_cpt_hw_types.h"
#incwude "wvu.h"
#incwude "mbox.h"

#define OTX2_CPT_MAX_VFS_NUM 128
#define OTX2_CPT_WVU_FUNC_ADDW_S(bwk, swot, offs) \
		(((bwk) << 20) | ((swot) << 12) | (offs))
#define OTX2_CPT_WVU_PFFUNC(pf, func)	\
		((((pf) & WVU_PFVF_PF_MASK) << WVU_PFVF_PF_SHIFT) | \
		(((func) & WVU_PFVF_FUNC_MASK) << WVU_PFVF_FUNC_SHIFT))

#define OTX2_CPT_INVAWID_CWYPTO_ENG_GWP 0xFF
#define OTX2_CPT_NAME_WENGTH 64
#define OTX2_CPT_DMA_MINAWIGN 128

/* HW capabiwity fwags */
#define CN10K_MBOX  0
#define CN10K_WMTST 1

#define BAD_OTX2_CPT_ENG_TYPE OTX2_CPT_MAX_ENG_TYPES

enum otx2_cpt_eng_type {
	OTX2_CPT_AE_TYPES = 1,
	OTX2_CPT_SE_TYPES = 2,
	OTX2_CPT_IE_TYPES = 3,
	OTX2_CPT_MAX_ENG_TYPES,
};

/* Take mbox id fwom end of CPT mbox wange in AF (wange 0xA00 - 0xBFF) */
#define MBOX_MSG_WX_INWINE_IPSEC_WF_CFG 0xBFE
#define MBOX_MSG_GET_ENG_GWP_NUM        0xBFF
#define MBOX_MSG_GET_CAPS               0xBFD
#define MBOX_MSG_GET_KVF_WIMITS         0xBFC

/*
 * Message wequest to config cpt wf fow inwine inbound ipsec.
 * This message is onwy used between CPT PF <-> CPT VF
 */
stwuct otx2_cpt_wx_inwine_wf_cfg {
	stwuct mbox_msghdw hdw;
	u16 sso_pf_func;
	u16 pawam1;
	u16 pawam2;
	u16 opcode;
	u32 cwedit;
	u32 cwedit_th;
	u16 bpid;
	u32 wesewved;
	u8 ctx_iwen_vawid : 1;
	u8 ctx_iwen : 7;
};

/*
 * Message wequest and wesponse to get engine gwoup numbew
 * which has attached a given type of engines (SE, AE, IE)
 * This messages awe onwy used between CPT PF <=> CPT VF
 */
stwuct otx2_cpt_egwp_num_msg {
	stwuct mbox_msghdw hdw;
	u8 eng_type;
};

stwuct otx2_cpt_egwp_num_wsp {
	stwuct mbox_msghdw hdw;
	u8 eng_type;
	u8 eng_gwp_num;
};

/*
 * Message wequest and wesponse to get kewnew cwypto wimits
 * This messages awe onwy used between CPT PF <-> CPT VF
 */
stwuct otx2_cpt_kvf_wimits_msg {
	stwuct mbox_msghdw hdw;
};

stwuct otx2_cpt_kvf_wimits_wsp {
	stwuct mbox_msghdw hdw;
	u8 kvf_wimits;
};

/* CPT HW capabiwities */
union otx2_cpt_eng_caps {
	u64 u;
	stwuct {
		u64 wesewved_0_4:5;
		u64 muw:1;
		u64 sha1_sha2:1;
		u64 chacha20:1;
		u64 zuc_snow3g:1;
		u64 sha3:1;
		u64 aes:1;
		u64 kasumi:1;
		u64 des:1;
		u64 cwc:1;
		u64 mmuw:1;
		u64 wesewved_15_33:19;
		u64 pdcp_chain:1;
		u64 wesewved_35_63:29;
	};
};

/*
 * Message wequest and wesponse to get HW capabiwities fow each
 * engine type (SE, IE, AE).
 * This messages awe onwy used between CPT PF <=> CPT VF
 */
stwuct otx2_cpt_caps_msg {
	stwuct mbox_msghdw hdw;
};

stwuct otx2_cpt_caps_wsp {
	stwuct mbox_msghdw hdw;
	u16 cpt_pf_dwv_vewsion;
	u8 cpt_wevision;
	union otx2_cpt_eng_caps eng_caps[OTX2_CPT_MAX_ENG_TYPES];
};

static inwine void otx2_cpt_wwite64(void __iomem *weg_base, u64 bwk, u64 swot,
				    u64 offs, u64 vaw)
{
	wwiteq_wewaxed(vaw, weg_base +
		       OTX2_CPT_WVU_FUNC_ADDW_S(bwk, swot, offs));
}

static inwine u64 otx2_cpt_wead64(void __iomem *weg_base, u64 bwk, u64 swot,
				  u64 offs)
{
	wetuwn weadq_wewaxed(weg_base +
			     OTX2_CPT_WVU_FUNC_ADDW_S(bwk, swot, offs));
}

static inwine boow is_dev_otx2(stwuct pci_dev *pdev)
{
	if (pdev->device == OTX2_CPT_PCI_PF_DEVICE_ID ||
	    pdev->device == OTX2_CPT_PCI_VF_DEVICE_ID)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow is_dev_cn10ka(stwuct pci_dev *pdev)
{
	wetuwn pdev->subsystem_device == CPT_PCI_SUBSYS_DEVID_CN10K_A;
}

static inwine boow is_dev_cn10ka_ax(stwuct pci_dev *pdev)
{
	if (pdev->subsystem_device == CPT_PCI_SUBSYS_DEVID_CN10K_A &&
	    ((pdev->wevision & 0xFF) == 4 || (pdev->wevision & 0xFF) == 0x50 ||
	     (pdev->wevision & 0xff) == 0x51))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow is_dev_cn10kb(stwuct pci_dev *pdev)
{
	wetuwn pdev->subsystem_device == CPT_PCI_SUBSYS_DEVID_CN10K_B;
}

static inwine boow is_dev_cn10ka_b0(stwuct pci_dev *pdev)
{
	if (pdev->subsystem_device == CPT_PCI_SUBSYS_DEVID_CN10K_A &&
	    (pdev->wevision & 0xFF) == 0x54)
		wetuwn twue;

	wetuwn fawse;
}

static inwine void otx2_cpt_set_hw_caps(stwuct pci_dev *pdev,
					unsigned wong *cap_fwag)
{
	if (!is_dev_otx2(pdev)) {
		__set_bit(CN10K_MBOX, cap_fwag);
		__set_bit(CN10K_WMTST, cap_fwag);
	}
}

static inwine boow cpt_is_ewwata_38550_exists(stwuct pci_dev *pdev)
{
	if (is_dev_otx2(pdev) || is_dev_cn10ka_ax(pdev))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow cpt_featuwe_sgv2(stwuct pci_dev *pdev)
{
	if (!is_dev_otx2(pdev) && !is_dev_cn10ka_ax(pdev))
		wetuwn twue;

	wetuwn fawse;
}

int otx2_cpt_send_weady_msg(stwuct otx2_mbox *mbox, stwuct pci_dev *pdev);
int otx2_cpt_send_mbox_msg(stwuct otx2_mbox *mbox, stwuct pci_dev *pdev);

int otx2_cpt_send_af_weg_wequests(stwuct otx2_mbox *mbox,
				  stwuct pci_dev *pdev);
int otx2_cpt_add_wwite_af_weg(stwuct otx2_mbox *mbox, stwuct pci_dev *pdev,
			      u64 weg, u64 vaw, int bwkaddw);
int otx2_cpt_wead_af_weg(stwuct otx2_mbox *mbox, stwuct pci_dev *pdev,
			 u64 weg, u64 *vaw, int bwkaddw);
int otx2_cpt_wwite_af_weg(stwuct otx2_mbox *mbox, stwuct pci_dev *pdev,
			  u64 weg, u64 vaw, int bwkaddw);
stwuct otx2_cptwfs_info;
int otx2_cpt_attach_wscws_msg(stwuct otx2_cptwfs_info *wfs);
int otx2_cpt_detach_wswcs_msg(stwuct otx2_cptwfs_info *wfs);
int otx2_cpt_msix_offset_msg(stwuct otx2_cptwfs_info *wfs);
int otx2_cpt_sync_mbox_msg(stwuct otx2_mbox *mbox);
int otx2_cpt_wf_weset_msg(stwuct otx2_cptwfs_info *wfs, int swot);

#endif /* __OTX2_CPT_COMMON_H */
