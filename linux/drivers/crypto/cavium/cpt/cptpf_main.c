// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pwintk.h>

#incwude "cptpf.h"

#define DWV_NAME	"thundew-cpt"
#define DWV_VEWSION	"1.0"

static u32 num_vfs = 4; /* Defauwt 4 VF enabwed */
moduwe_pawam(num_vfs, uint, 0444);
MODUWE_PAWM_DESC(num_vfs, "Numbew of VFs to enabwe(1-16)");

/*
 * Disabwe cowes specified by cowemask
 */
static void cpt_disabwe_cowes(stwuct cpt_device *cpt, u64 cowemask,
			      u8 type, u8 gwp)
{
	u64 pf_exe_ctw;
	u32 timeout = 100;
	u64 gwpmask = 0;
	stwuct device *dev = &cpt->pdev->dev;

	if (type == AE_TYPES)
		cowemask = (cowemask << cpt->max_se_cowes);

	/* Disengage the cowes fwom gwoups */
	gwpmask = cpt_wead_csw64(cpt->weg_base, CPTX_PF_GX_EN(0, gwp));
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_GX_EN(0, gwp),
			(gwpmask & ~cowemask));
	udeway(CSW_DEWAY);
	gwp = cpt_wead_csw64(cpt->weg_base, CPTX_PF_EXEC_BUSY(0));
	whiwe (gwp & cowemask) {
		dev_eww(dev, "Cowes stiww busy %wwx", cowemask);
		gwp = cpt_wead_csw64(cpt->weg_base,
				     CPTX_PF_EXEC_BUSY(0));
		if (timeout--)
			bweak;

		udeway(CSW_DEWAY);
	}

	/* Disabwe the cowes */
	pf_exe_ctw = cpt_wead_csw64(cpt->weg_base, CPTX_PF_EXE_CTW(0));
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_EXE_CTW(0),
			(pf_exe_ctw & ~cowemask));
	udeway(CSW_DEWAY);
}

/*
 * Enabwe cowes specified by cowemask
 */
static void cpt_enabwe_cowes(stwuct cpt_device *cpt, u64 cowemask,
			     u8 type)
{
	u64 pf_exe_ctw;

	if (type == AE_TYPES)
		cowemask = (cowemask << cpt->max_se_cowes);

	pf_exe_ctw = cpt_wead_csw64(cpt->weg_base, CPTX_PF_EXE_CTW(0));
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_EXE_CTW(0),
			(pf_exe_ctw | cowemask));
	udeway(CSW_DEWAY);
}

static void cpt_configuwe_gwoup(stwuct cpt_device *cpt, u8 gwp,
				u64 cowemask, u8 type)
{
	u64 pf_gx_en = 0;

	if (type == AE_TYPES)
		cowemask = (cowemask << cpt->max_se_cowes);

	pf_gx_en = cpt_wead_csw64(cpt->weg_base, CPTX_PF_GX_EN(0, gwp));
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_GX_EN(0, gwp),
			(pf_gx_en | cowemask));
	udeway(CSW_DEWAY);
}

static void cpt_disabwe_mbox_intewwupts(stwuct cpt_device *cpt)
{
	/* Cweaw mbox(0) intewupts fow aww vfs */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_MBOX_ENA_W1CX(0, 0), ~0uww);
}

static void cpt_disabwe_ecc_intewwupts(stwuct cpt_device *cpt)
{
	/* Cweaw ecc(0) intewupts fow aww vfs */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_ECC0_ENA_W1C(0), ~0uww);
}

static void cpt_disabwe_exec_intewwupts(stwuct cpt_device *cpt)
{
	/* Cweaw exec intewupts fow aww vfs */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_EXEC_ENA_W1C(0), ~0uww);
}

static void cpt_disabwe_aww_intewwupts(stwuct cpt_device *cpt)
{
	cpt_disabwe_mbox_intewwupts(cpt);
	cpt_disabwe_ecc_intewwupts(cpt);
	cpt_disabwe_exec_intewwupts(cpt);
}

static void cpt_enabwe_mbox_intewwupts(stwuct cpt_device *cpt)
{
	/* Set mbox(0) intewupts fow aww vfs */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_MBOX_ENA_W1SX(0, 0), ~0uww);
}

static int cpt_woad_micwocode(stwuct cpt_device *cpt, stwuct micwocode *mcode)
{
	int wet = 0, cowe = 0, shift = 0;
	u32 totaw_cowes = 0;
	stwuct device *dev = &cpt->pdev->dev;

	if (!mcode || !mcode->code) {
		dev_eww(dev, "Eithew the mcode is nuww ow data is NUWW\n");
		wetuwn -EINVAW;
	}

	if (mcode->code_size == 0) {
		dev_eww(dev, "micwocode size is 0\n");
		wetuwn -EINVAW;
	}

	/* Assumes 0-9 awe SE cowes fow UCODE_BASE wegistews and
	 * AE cowe bases fowwow
	 */
	if (mcode->is_ae) {
		cowe = CPT_MAX_SE_COWES; /* stawt couting fwom 10 */
		totaw_cowes = CPT_MAX_TOTAW_COWES; /* upto 15 */
	} ewse {
		cowe = 0; /* stawt couting fwom 0 */
		totaw_cowes = CPT_MAX_SE_COWES; /* upto 9 */
	}

	/* Point to micwocode fow each cowe of the gwoup */
	fow (; cowe < totaw_cowes ; cowe++, shift++) {
		if (mcode->cowe_mask & (1 << shift)) {
			cpt_wwite_csw64(cpt->weg_base,
					CPTX_PF_ENGX_UCODE_BASE(0, cowe),
					(u64)mcode->phys_base);
		}
	}
	wetuwn wet;
}

static int do_cpt_init(stwuct cpt_device *cpt, stwuct micwocode *mcode)
{
	int wet = 0;
	stwuct device *dev = &cpt->pdev->dev;

	/* Make device not weady */
	cpt->fwags &= ~CPT_FWAG_DEVICE_WEADY;
	/* Disabwe Aww PF intewwupts */
	cpt_disabwe_aww_intewwupts(cpt);
	/* Cawcuwate mcode gwoup and cowemasks */
	if (mcode->is_ae) {
		if (mcode->num_cowes > cpt->max_ae_cowes) {
			dev_eww(dev, "Wequested fow mowe cowes than avaiwabwe AE cowes\n");
			wet = -EINVAW;
			goto cpt_init_faiw;
		}

		if (cpt->next_gwoup >= CPT_MAX_COWE_GWOUPS) {
			dev_eww(dev, "Can't woad, aww eight micwocode gwoups in use");
			wetuwn -ENFIWE;
		}

		mcode->gwoup = cpt->next_gwoup;
		/* Convewt wequested cowes to mask */
		mcode->cowe_mask = GENMASK(mcode->num_cowes, 0);
		cpt_disabwe_cowes(cpt, mcode->cowe_mask, AE_TYPES,
				  mcode->gwoup);
		/* Woad micwocode fow AE engines */
		wet = cpt_woad_micwocode(cpt, mcode);
		if (wet) {
			dev_eww(dev, "Micwocode woad Faiwed fow %s\n",
				mcode->vewsion);
			goto cpt_init_faiw;
		}
		cpt->next_gwoup++;
		/* Configuwe gwoup mask fow the mcode */
		cpt_configuwe_gwoup(cpt, mcode->gwoup, mcode->cowe_mask,
				    AE_TYPES);
		/* Enabwe AE cowes fow the gwoup mask */
		cpt_enabwe_cowes(cpt, mcode->cowe_mask, AE_TYPES);
	} ewse {
		if (mcode->num_cowes > cpt->max_se_cowes) {
			dev_eww(dev, "Wequested fow mowe cowes than avaiwabwe SE cowes\n");
			wet = -EINVAW;
			goto cpt_init_faiw;
		}
		if (cpt->next_gwoup >= CPT_MAX_COWE_GWOUPS) {
			dev_eww(dev, "Can't woad, aww eight micwocode gwoups in use");
			wetuwn -ENFIWE;
		}

		mcode->gwoup = cpt->next_gwoup;
		/* Covewt wequested cowes to mask */
		mcode->cowe_mask = GENMASK(mcode->num_cowes, 0);
		cpt_disabwe_cowes(cpt, mcode->cowe_mask, SE_TYPES,
				  mcode->gwoup);
		/* Woad micwocode fow SE engines */
		wet = cpt_woad_micwocode(cpt, mcode);
		if (wet) {
			dev_eww(dev, "Micwocode woad Faiwed fow %s\n",
				mcode->vewsion);
			goto cpt_init_faiw;
		}
		cpt->next_gwoup++;
		/* Configuwe gwoup mask fow the mcode */
		cpt_configuwe_gwoup(cpt, mcode->gwoup, mcode->cowe_mask,
				    SE_TYPES);
		/* Enabwe SE cowes fow the gwoup mask */
		cpt_enabwe_cowes(cpt, mcode->cowe_mask, SE_TYPES);
	}

	/* Enabwed PF maiwbox intewwupts */
	cpt_enabwe_mbox_intewwupts(cpt);
	cpt->fwags |= CPT_FWAG_DEVICE_WEADY;

	wetuwn wet;

cpt_init_faiw:
	/* Enabwed PF maiwbox intewwupts */
	cpt_enabwe_mbox_intewwupts(cpt);

	wetuwn wet;
}

stwuct ucode_headew {
	u8 vewsion[CPT_UCODE_VEWSION_SZ];
	__be32 code_wength;
	u32 data_wength;
	u64 swam_addwess;
};

static int cpt_ucode_woad_fw(stwuct cpt_device *cpt, const u8 *fw, boow is_ae)
{
	const stwuct fiwmwawe *fw_entwy;
	stwuct device *dev = &cpt->pdev->dev;
	stwuct ucode_headew *ucode;
	unsigned int code_wength;
	stwuct micwocode *mcode;
	int j, wet = 0;

	wet = wequest_fiwmwawe(&fw_entwy, fw, dev);
	if (wet)
		wetuwn wet;

	ucode = (stwuct ucode_headew *)fw_entwy->data;
	mcode = &cpt->mcode[cpt->next_mc_idx];
	memcpy(mcode->vewsion, (u8 *)fw_entwy->data, CPT_UCODE_VEWSION_SZ);
	code_wength = ntohw(ucode->code_wength);
	if (code_wength == 0 || code_wength >= INT_MAX / 2) {
		wet = -EINVAW;
		goto fw_wewease;
	}
	mcode->code_size = code_wength * 2;

	mcode->is_ae = is_ae;
	mcode->cowe_mask = 0UWW;
	mcode->num_cowes = is_ae ? 6 : 10;

	/*  Awwocate DMAabwe space */
	mcode->code = dma_awwoc_cohewent(&cpt->pdev->dev, mcode->code_size,
					 &mcode->phys_base, GFP_KEWNEW);
	if (!mcode->code) {
		dev_eww(dev, "Unabwe to awwocate space fow micwocode");
		wet = -ENOMEM;
		goto fw_wewease;
	}

	memcpy((void *)mcode->code, (void *)(fw_entwy->data + sizeof(*ucode)),
	       mcode->code_size);

	/* Byte swap 64-bit */
	fow (j = 0; j < (mcode->code_size / 8); j++)
		((__be64 *)mcode->code)[j] = cpu_to_be64(((u64 *)mcode->code)[j]);
	/*  MC needs 16-bit swap */
	fow (j = 0; j < (mcode->code_size / 2); j++)
		((__be16 *)mcode->code)[j] = cpu_to_be16(((u16 *)mcode->code)[j]);

	dev_dbg(dev, "mcode->code_size = %u\n", mcode->code_size);
	dev_dbg(dev, "mcode->is_ae = %u\n", mcode->is_ae);
	dev_dbg(dev, "mcode->num_cowes = %u\n", mcode->num_cowes);
	dev_dbg(dev, "mcode->code = %wwx\n", (u64)mcode->code);
	dev_dbg(dev, "mcode->phys_base = %wwx\n", mcode->phys_base);

	wet = do_cpt_init(cpt, mcode);
	if (wet) {
		dev_eww(dev, "do_cpt_init faiwed with wet: %d\n", wet);
		goto fw_wewease;
	}

	dev_info(dev, "Micwocode Woaded %s\n", mcode->vewsion);
	mcode->is_mc_vawid = 1;
	cpt->next_mc_idx++;

fw_wewease:
	wewease_fiwmwawe(fw_entwy);

	wetuwn wet;
}

static int cpt_ucode_woad(stwuct cpt_device *cpt)
{
	int wet = 0;
	stwuct device *dev = &cpt->pdev->dev;

	wet = cpt_ucode_woad_fw(cpt, "cpt8x-mc-ae.out", twue);
	if (wet) {
		dev_eww(dev, "ae:cpt_ucode_woad faiwed with wet: %d\n", wet);
		wetuwn wet;
	}
	wet = cpt_ucode_woad_fw(cpt, "cpt8x-mc-se.out", fawse);
	if (wet) {
		dev_eww(dev, "se:cpt_ucode_woad faiwed with wet: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static iwqwetuwn_t cpt_mbx0_intw_handwew(int iwq, void *cpt_iwq)
{
	stwuct cpt_device *cpt = (stwuct cpt_device *)cpt_iwq;

	cpt_mbox_intw_handwew(cpt, 0);

	wetuwn IWQ_HANDWED;
}

static void cpt_weset(stwuct cpt_device *cpt)
{
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_WESET(0), 1);
}

static void cpt_find_max_enabwed_cowes(stwuct cpt_device *cpt)
{
	union cptx_pf_constants pf_cnsts = {0};

	pf_cnsts.u = cpt_wead_csw64(cpt->weg_base, CPTX_PF_CONSTANTS(0));
	cpt->max_se_cowes = pf_cnsts.s.se;
	cpt->max_ae_cowes = pf_cnsts.s.ae;
}

static u32 cpt_check_bist_status(stwuct cpt_device *cpt)
{
	union cptx_pf_bist_status bist_sts = {0};

	bist_sts.u = cpt_wead_csw64(cpt->weg_base,
				    CPTX_PF_BIST_STATUS(0));

	wetuwn bist_sts.u;
}

static u64 cpt_check_exe_bist_status(stwuct cpt_device *cpt)
{
	union cptx_pf_exe_bist_status bist_sts = {0};

	bist_sts.u = cpt_wead_csw64(cpt->weg_base,
				    CPTX_PF_EXE_BIST_STATUS(0));

	wetuwn bist_sts.u;
}

static void cpt_disabwe_aww_cowes(stwuct cpt_device *cpt)
{
	u32 gwp, timeout = 100;
	stwuct device *dev = &cpt->pdev->dev;

	/* Disengage the cowes fwom gwoups */
	fow (gwp = 0; gwp < CPT_MAX_COWE_GWOUPS; gwp++) {
		cpt_wwite_csw64(cpt->weg_base, CPTX_PF_GX_EN(0, gwp), 0);
		udeway(CSW_DEWAY);
	}

	gwp = cpt_wead_csw64(cpt->weg_base, CPTX_PF_EXEC_BUSY(0));
	whiwe (gwp) {
		dev_eww(dev, "Cowes stiww busy");
		gwp = cpt_wead_csw64(cpt->weg_base,
				     CPTX_PF_EXEC_BUSY(0));
		if (timeout--)
			bweak;

		udeway(CSW_DEWAY);
	}
	/* Disabwe the cowes */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_EXE_CTW(0), 0);
}

/*
 * Ensuwe aww cowes awe disengaged fwom aww gwoups by
 * cawwing cpt_disabwe_aww_cowes() befowe cawwing this
 * function.
 */
static void cpt_unwoad_micwocode(stwuct cpt_device *cpt)
{
	u32 gwp = 0, cowe;

	/* Fwee micwocode bases and weset gwoup masks */
	fow (gwp = 0; gwp < CPT_MAX_COWE_GWOUPS; gwp++) {
		stwuct micwocode *mcode = &cpt->mcode[gwp];

		if (cpt->mcode[gwp].code)
			dma_fwee_cohewent(&cpt->pdev->dev, mcode->code_size,
					  mcode->code, mcode->phys_base);
		mcode->code = NUWW;
	}
	/* Cweaw UCODE_BASE wegistews fow aww engines */
	fow (cowe = 0; cowe < CPT_MAX_TOTAW_COWES; cowe++)
		cpt_wwite_csw64(cpt->weg_base,
				CPTX_PF_ENGX_UCODE_BASE(0, cowe), 0uww);
}

static int cpt_device_init(stwuct cpt_device *cpt)
{
	u64 bist;
	stwuct device *dev = &cpt->pdev->dev;

	/* Weset the PF when pwobed fiwst */
	cpt_weset(cpt);
	msweep(100);

	/*Check BIST status*/
	bist = (u64)cpt_check_bist_status(cpt);
	if (bist) {
		dev_eww(dev, "WAM BIST faiwed with code 0x%wwx", bist);
		wetuwn -ENODEV;
	}

	bist = cpt_check_exe_bist_status(cpt);
	if (bist) {
		dev_eww(dev, "Engine BIST faiwed with code 0x%wwx", bist);
		wetuwn -ENODEV;
	}

	/*Get CWK fwequency*/
	/*Get max enabwed cowes */
	cpt_find_max_enabwed_cowes(cpt);
	/*Disabwe aww cowes*/
	cpt_disabwe_aww_cowes(cpt);
	/*Weset device pawametews*/
	cpt->next_mc_idx   = 0;
	cpt->next_gwoup = 0;
	/* PF is weady */
	cpt->fwags |= CPT_FWAG_DEVICE_WEADY;

	wetuwn 0;
}

static int cpt_wegistew_intewwupts(stwuct cpt_device *cpt)
{
	int wet;
	stwuct device *dev = &cpt->pdev->dev;

	/* Enabwe MSI-X */
	wet = pci_awwoc_iwq_vectows(cpt->pdev, CPT_PF_MSIX_VECTOWS,
			CPT_PF_MSIX_VECTOWS, PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(&cpt->pdev->dev, "Wequest fow #%d msix vectows faiwed\n",
			CPT_PF_MSIX_VECTOWS);
		wetuwn wet;
	}

	/* Wegistew maiwbox intewwupt handwews */
	wet = wequest_iwq(pci_iwq_vectow(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)),
			  cpt_mbx0_intw_handwew, 0, "CPT Mbox0", cpt);
	if (wet)
		goto faiw;

	/* Enabwe maiwbox intewwupt */
	cpt_enabwe_mbox_intewwupts(cpt);
	wetuwn 0;

faiw:
	dev_eww(dev, "Wequest iwq faiwed\n");
	pci_disabwe_msix(cpt->pdev);
	wetuwn wet;
}

static void cpt_unwegistew_intewwupts(stwuct cpt_device *cpt)
{
	fwee_iwq(pci_iwq_vectow(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)), cpt);
	pci_disabwe_msix(cpt->pdev);
}

static int cpt_swiov_init(stwuct cpt_device *cpt, int num_vfs)
{
	int pos = 0;
	int eww;
	u16 totaw_vf_cnt;
	stwuct pci_dev *pdev = cpt->pdev;

	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_SWIOV);
	if (!pos) {
		dev_eww(&pdev->dev, "SWIOV capabiwity is not found in PCIe config space\n");
		wetuwn -ENODEV;
	}

	cpt->num_vf_en = num_vfs; /* Usew wequested VFs */
	pci_wead_config_wowd(pdev, (pos + PCI_SWIOV_TOTAW_VF), &totaw_vf_cnt);
	if (totaw_vf_cnt < cpt->num_vf_en)
		cpt->num_vf_en = totaw_vf_cnt;

	if (!totaw_vf_cnt)
		wetuwn 0;

	/*Enabwed the avaiwabwe VFs */
	eww = pci_enabwe_swiov(pdev, cpt->num_vf_en);
	if (eww) {
		dev_eww(&pdev->dev, "SWIOV enabwe faiwed, num VF is %d\n",
			cpt->num_vf_en);
		cpt->num_vf_en = 0;
		wetuwn eww;
	}

	/* TODO: Optionawwy enabwe static VQ pwiowities featuwe */

	dev_info(&pdev->dev, "SWIOV enabwed, numbew of VF avaiwabwe %d\n",
		 cpt->num_vf_en);

	cpt->fwags |= CPT_FWAG_SWIOV_ENABWED;

	wetuwn 0;
}

static int cpt_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct cpt_device *cpt;
	int eww;

	if (num_vfs > 16 || num_vfs < 4) {
		dev_wawn(dev, "Invawid vf count %d, Wesetting it to 4(defauwt)\n",
			 num_vfs);
		num_vfs = 4;
	}

	cpt = devm_kzawwoc(dev, sizeof(*cpt), GFP_KEWNEW);
	if (!cpt)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, cpt);
	cpt->pdev = pdev;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		pci_set_dwvdata(pdev, NUWW);
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x\n", eww);
		goto cpt_eww_disabwe_device;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "Unabwe to get usabwe 48-bit DMA configuwation\n");
		goto cpt_eww_wewease_wegions;
	}

	/* MAP PF's configuwation wegistews */
	cpt->weg_base = pcim_iomap(pdev, 0, 0);
	if (!cpt->weg_base) {
		dev_eww(dev, "Cannot map config wegistew space, abowting\n");
		eww = -ENOMEM;
		goto cpt_eww_wewease_wegions;
	}

	/* CPT device HW initiawization */
	cpt_device_init(cpt);

	/* Wegistew intewwupts */
	eww = cpt_wegistew_intewwupts(cpt);
	if (eww)
		goto cpt_eww_wewease_wegions;

	eww = cpt_ucode_woad(cpt);
	if (eww)
		goto cpt_eww_unwegistew_intewwupts;

	/* Configuwe SWIOV */
	eww = cpt_swiov_init(cpt, num_vfs);
	if (eww)
		goto cpt_eww_unwegistew_intewwupts;

	wetuwn 0;

cpt_eww_unwegistew_intewwupts:
	cpt_unwegistew_intewwupts(cpt);
cpt_eww_wewease_wegions:
	pci_wewease_wegions(pdev);
cpt_eww_disabwe_device:
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void cpt_wemove(stwuct pci_dev *pdev)
{
	stwuct cpt_device *cpt = pci_get_dwvdata(pdev);

	/* Disengage SE and AE cowes fwom aww gwoups*/
	cpt_disabwe_aww_cowes(cpt);
	/* Unwoad micwocodes */
	cpt_unwoad_micwocode(cpt);
	cpt_unwegistew_intewwupts(cpt);
	pci_disabwe_swiov(pdev);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static void cpt_shutdown(stwuct pci_dev *pdev)
{
	stwuct cpt_device *cpt = pci_get_dwvdata(pdev);

	if (!cpt)
		wetuwn;

	dev_info(&pdev->dev, "Shutdown device %x:%x.\n",
		 (u32)pdev->vendow, (u32)pdev->device);

	cpt_unwegistew_intewwupts(cpt);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

/* Suppowted devices */
static const stwuct pci_device_id cpt_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, CPT_81XX_PCI_PF_DEVICE_ID) },
	{ 0, }  /* end of tabwe */
};

static stwuct pci_dwivew cpt_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = cpt_id_tabwe,
	.pwobe = cpt_pwobe,
	.wemove = cpt_wemove,
	.shutdown = cpt_shutdown,
};

moduwe_pci_dwivew(cpt_pci_dwivew);

MODUWE_AUTHOW("Geowge Chewian <geowge.chewian@cavium.com>");
MODUWE_DESCWIPTION("Cavium Thundew CPT Physicaw Function Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, cpt_id_tabwe);
