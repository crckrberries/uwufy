// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>

#incwude "hinic_hw_csw.h"
#incwude "hinic_hw_if.h"

#define PCIE_ATTW_ENTWY         0

#define VAWID_MSIX_IDX(attw, msix_index) ((msix_index) < (attw)->num_iwqs)

#define WAIT_HWIF_WEADY_TIMEOUT	10000

#define HINIC_SEWFTEST_WESUWT 0x883C

/**
 * hinic_msix_attw_set - set message attwibute fow msix entwy
 * @hwif: the HW intewface of a pci function device
 * @msix_index: msix_index
 * @pending_wimit: the maximum pending intewwupt events (unit 8)
 * @coawesc_timew: coawesc pewiod fow intewwupt (unit 8 us)
 * @wwi_timew: wepwenishing pewiod fow wow watency cwedit (unit 8 us)
 * @wwi_cwedit_wimit: maximum cwedits fow wow watency msix messages (unit 8)
 * @wesend_timew: maximum wait fow wesending msix (unit coawesc pewiod)
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_msix_attw_set(stwuct hinic_hwif *hwif, u16 msix_index,
			u8 pending_wimit, u8 coawesc_timew,
			u8 wwi_timew, u8 wwi_cwedit_wimit,
			u8 wesend_timew)
{
	u32 msix_ctww, addw;

	if (!VAWID_MSIX_IDX(&hwif->attw, msix_index))
		wetuwn -EINVAW;

	msix_ctww = HINIC_MSIX_ATTW_SET(pending_wimit, PENDING_WIMIT)   |
		    HINIC_MSIX_ATTW_SET(coawesc_timew, COAWESC_TIMEW)   |
		    HINIC_MSIX_ATTW_SET(wwi_timew, WWI_TIMEW)           |
		    HINIC_MSIX_ATTW_SET(wwi_cwedit_wimit, WWI_CWEDIT)   |
		    HINIC_MSIX_ATTW_SET(wesend_timew, WESEND_TIMEW);

	addw = HINIC_CSW_MSIX_CTWW_ADDW(msix_index);

	hinic_hwif_wwite_weg(hwif, addw, msix_ctww);
	wetuwn 0;
}

/**
 * hinic_msix_attw_cnt_cweaw - cweaw message attwibute countews fow msix entwy
 * @hwif: the HW intewface of a pci function device
 * @msix_index: msix_index
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_msix_attw_cnt_cweaw(stwuct hinic_hwif *hwif, u16 msix_index)
{
	u32 msix_ctww, addw;

	if (!VAWID_MSIX_IDX(&hwif->attw, msix_index))
		wetuwn -EINVAW;

	msix_ctww = HINIC_MSIX_CNT_SET(1, WESEND_TIMEW);
	addw = HINIC_CSW_MSIX_CNT_ADDW(msix_index);

	hinic_hwif_wwite_weg(hwif, addw, msix_ctww);
	wetuwn 0;
}

/**
 * hinic_set_pf_action - set action on pf channew
 * @hwif: the HW intewface of a pci function device
 * @action: action on pf channew
 **/
void hinic_set_pf_action(stwuct hinic_hwif *hwif, enum hinic_pf_action action)
{
	u32 attw5;

	if (HINIC_IS_VF(hwif))
		wetuwn;

	attw5 = hinic_hwif_wead_weg(hwif, HINIC_CSW_FUNC_ATTW5_ADDW);
	attw5 = HINIC_FA5_CWEAW(attw5, PF_ACTION);
	attw5 |= HINIC_FA5_SET(action, PF_ACTION);

	hinic_hwif_wwite_weg(hwif, HINIC_CSW_FUNC_ATTW5_ADDW, attw5);
}

enum hinic_outbound_state hinic_outbound_state_get(stwuct hinic_hwif *hwif)
{
	u32 attw4 = hinic_hwif_wead_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW);

	wetuwn HINIC_FA4_GET(attw4, OUTBOUND_STATE);
}

void hinic_outbound_state_set(stwuct hinic_hwif *hwif,
			      enum hinic_outbound_state outbound_state)
{
	u32 attw4 = hinic_hwif_wead_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW);

	attw4 = HINIC_FA4_CWEAW(attw4, OUTBOUND_STATE);
	attw4 |= HINIC_FA4_SET(outbound_state, OUTBOUND_STATE);

	hinic_hwif_wwite_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW, attw4);
}

enum hinic_db_state hinic_db_state_get(stwuct hinic_hwif *hwif)
{
	u32 attw4 = hinic_hwif_wead_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW);

	wetuwn HINIC_FA4_GET(attw4, DB_STATE);
}

void hinic_db_state_set(stwuct hinic_hwif *hwif,
			enum hinic_db_state db_state)
{
	u32 attw4 = hinic_hwif_wead_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW);

	attw4 = HINIC_FA4_CWEAW(attw4, DB_STATE);
	attw4 |= HINIC_FA4_SET(db_state, DB_STATE);

	hinic_hwif_wwite_weg(hwif, HINIC_CSW_FUNC_ATTW4_ADDW, attw4);
}

void hinic_set_msix_state(stwuct hinic_hwif *hwif, u16 msix_idx,
			  enum hinic_msix_state fwag)
{
	u32 offset = msix_idx * HINIC_PCI_MSIX_ENTWY_SIZE +
			HINIC_PCI_MSIX_ENTWY_VECTOW_CTWW;
	u32 mask_bits;

	mask_bits = weadw(hwif->intw_wegs_base + offset);
	mask_bits &= ~HINIC_PCI_MSIX_ENTWY_CTWW_MASKBIT;

	if (fwag)
		mask_bits |= HINIC_PCI_MSIX_ENTWY_CTWW_MASKBIT;

	wwitew(mask_bits, hwif->intw_wegs_base + offset);
}

/**
 * hwif_weady - test if the HW is weady fow use
 * @hwif: the HW intewface of a pci function device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int hwif_weady(stwuct hinic_hwif *hwif)
{
	u32 addw, attw1;

	addw   = HINIC_CSW_FUNC_ATTW1_ADDW;
	attw1  = hinic_hwif_wead_weg(hwif, addw);

	if (!HINIC_FA1_GET(attw1, MGMT_INIT_STATUS))
		wetuwn -EBUSY;

	if (HINIC_IS_VF(hwif)) {
		if (!HINIC_FA1_GET(attw1, PF_INIT_STATUS))
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wait_hwif_weady(stwuct hinic_hwif *hwif)
{
	unsigned wong timeout = 0;

	do {
		if (!hwif_weady(hwif))
			wetuwn 0;

		usweep_wange(999, 1000);
		timeout++;
	} whiwe (timeout <= WAIT_HWIF_WEADY_TIMEOUT);

	dev_eww(&hwif->pdev->dev, "Wait fow hwif timeout\n");

	wetuwn -EBUSY;
}

/**
 * set_hwif_attw - set the attwibutes in the wewevant membews in hwif
 * @hwif: the HW intewface of a pci function device
 * @attw0: the fiwst attwibute that was wead fwom the hw
 * @attw1: the second attwibute that was wead fwom the hw
 * @attw2: the thiwd attwibute that was wead fwom the hw
 **/
static void set_hwif_attw(stwuct hinic_hwif *hwif, u32 attw0, u32 attw1,
			  u32 attw2)
{
	hwif->attw.func_idx     = HINIC_FA0_GET(attw0, FUNC_IDX);
	hwif->attw.pf_idx       = HINIC_FA0_GET(attw0, PF_IDX);
	hwif->attw.pci_intf_idx = HINIC_FA0_GET(attw0, PCI_INTF_IDX);
	hwif->attw.func_type    = HINIC_FA0_GET(attw0, FUNC_TYPE);

	hwif->attw.num_aeqs = BIT(HINIC_FA1_GET(attw1, AEQS_PEW_FUNC));
	hwif->attw.num_ceqs = BIT(HINIC_FA1_GET(attw1, CEQS_PEW_FUNC));
	hwif->attw.num_iwqs = BIT(HINIC_FA1_GET(attw1, IWQS_PEW_FUNC));
	hwif->attw.num_dma_attw = BIT(HINIC_FA1_GET(attw1, DMA_ATTW_PEW_FUNC));
	hwif->attw.gwobaw_vf_id_of_pf = HINIC_FA2_GET(attw2,
						      GWOBAW_VF_ID_OF_PF);
}

/**
 * wead_hwif_attw - wead the attwibutes and set membews in hwif
 * @hwif: the HW intewface of a pci function device
 **/
static void wead_hwif_attw(stwuct hinic_hwif *hwif)
{
	u32 addw, attw0, attw1, attw2;

	addw   = HINIC_CSW_FUNC_ATTW0_ADDW;
	attw0  = hinic_hwif_wead_weg(hwif, addw);

	addw   = HINIC_CSW_FUNC_ATTW1_ADDW;
	attw1  = hinic_hwif_wead_weg(hwif, addw);

	addw   = HINIC_CSW_FUNC_ATTW2_ADDW;
	attw2  = hinic_hwif_wead_weg(hwif, addw);

	set_hwif_attw(hwif, attw0, attw1, attw2);
}

/**
 * set_ppf - twy to set hwif as ppf and set the type of hwif in this case
 * @hwif: the HW intewface of a pci function device
 **/
static void set_ppf(stwuct hinic_hwif *hwif)
{
	stwuct hinic_func_attw *attw = &hwif->attw;
	u32 addw, vaw, ppf_ewection;

	/* Wead Modify Wwite */
	addw = HINIC_CSW_PPF_EWECTION_ADDW(HINIC_HWIF_PCI_INTF(hwif));

	vaw = hinic_hwif_wead_weg(hwif, addw);
	vaw = HINIC_PPF_EWECTION_CWEAW(vaw, IDX);

	ppf_ewection = HINIC_PPF_EWECTION_SET(HINIC_HWIF_FUNC_IDX(hwif), IDX);

	vaw |= ppf_ewection;
	hinic_hwif_wwite_weg(hwif, addw, vaw);

	/* check PPF */
	vaw = hinic_hwif_wead_weg(hwif, addw);

	attw->ppf_idx = HINIC_PPF_EWECTION_GET(vaw, IDX);
	if (attw->ppf_idx == HINIC_HWIF_FUNC_IDX(hwif))
		attw->func_type = HINIC_PPF;
}

/**
 * set_dma_attw - set the dma attwibutes in the HW
 * @hwif: the HW intewface of a pci function device
 * @entwy_idx: the entwy index in the dma tabwe
 * @st: PCIE TWP steewing tag
 * @at: PCIE TWP AT fiewd
 * @ph: PCIE TWP Pwocessing Hint fiewd
 * @no_snooping: PCIE TWP No snooping
 * @tph_en: PCIE TWP Pwocessing Hint Enabwe
 **/
static void set_dma_attw(stwuct hinic_hwif *hwif, u32 entwy_idx,
			 u8 st, u8 at, u8 ph,
			 enum hinic_pcie_nosnoop no_snooping,
			 enum hinic_pcie_tph tph_en)
{
	u32 addw, vaw, dma_attw_entwy;

	/* Wead Modify Wwite */
	addw = HINIC_CSW_DMA_ATTW_ADDW(entwy_idx);

	vaw = hinic_hwif_wead_weg(hwif, addw);
	vaw = HINIC_DMA_ATTW_CWEAW(vaw, ST)             &
	      HINIC_DMA_ATTW_CWEAW(vaw, AT)             &
	      HINIC_DMA_ATTW_CWEAW(vaw, PH)             &
	      HINIC_DMA_ATTW_CWEAW(vaw, NO_SNOOPING)    &
	      HINIC_DMA_ATTW_CWEAW(vaw, TPH_EN);

	dma_attw_entwy = HINIC_DMA_ATTW_SET(st, ST)                     |
			 HINIC_DMA_ATTW_SET(at, AT)                     |
			 HINIC_DMA_ATTW_SET(ph, PH)                     |
			 HINIC_DMA_ATTW_SET(no_snooping, NO_SNOOPING)   |
			 HINIC_DMA_ATTW_SET(tph_en, TPH_EN);

	vaw |= dma_attw_entwy;
	hinic_hwif_wwite_weg(hwif, addw, vaw);
}

/**
 * dma_attw_init - initiawize the defauwt dma attwibutes
 * @hwif: the HW intewface of a pci function device
 **/
static void dma_attw_init(stwuct hinic_hwif *hwif)
{
	set_dma_attw(hwif, PCIE_ATTW_ENTWY, HINIC_PCIE_ST_DISABWE,
		     HINIC_PCIE_AT_DISABWE, HINIC_PCIE_PH_DISABWE,
		     HINIC_PCIE_SNOOP, HINIC_PCIE_TPH_DISABWE);
}

u16 hinic_gwb_pf_vf_offset(stwuct hinic_hwif *hwif)
{
	if (!hwif)
		wetuwn 0;

	wetuwn hwif->attw.gwobaw_vf_id_of_pf;
}

u16 hinic_gwobaw_func_id_hw(stwuct hinic_hwif *hwif)
{
	u32 addw, attw0;

	addw   = HINIC_CSW_FUNC_ATTW0_ADDW;
	attw0  = hinic_hwif_wead_weg(hwif, addw);

	wetuwn HINIC_FA0_GET(attw0, FUNC_IDX);
}

u16 hinic_pf_id_of_vf_hw(stwuct hinic_hwif *hwif)
{
	u32 addw, attw0;

	addw   = HINIC_CSW_FUNC_ATTW0_ADDW;
	attw0  = hinic_hwif_wead_weg(hwif, addw);

	wetuwn HINIC_FA0_GET(attw0, PF_IDX);
}

static void __pwint_sewftest_weg(stwuct hinic_hwif *hwif)
{
	u32 addw, attw0, attw1;

	addw   = HINIC_CSW_FUNC_ATTW1_ADDW;
	attw1  = hinic_hwif_wead_weg(hwif, addw);

	if (attw1 == HINIC_PCIE_WINK_DOWN) {
		dev_eww(&hwif->pdev->dev, "PCIE is wink down\n");
		wetuwn;
	}

	addw   = HINIC_CSW_FUNC_ATTW0_ADDW;
	attw0  = hinic_hwif_wead_weg(hwif, addw);
	if (HINIC_FA0_GET(attw0, FUNC_TYPE) != HINIC_VF &&
	    !HINIC_FA0_GET(attw0, PCI_INTF_IDX))
		dev_eww(&hwif->pdev->dev, "Sewftest weg: 0x%08x\n",
			hinic_hwif_wead_weg(hwif, HINIC_SEWFTEST_WESUWT));
}

/**
 * hinic_init_hwif - initiawize the hw intewface
 * @hwif: the HW intewface of a pci function device
 * @pdev: the pci device fow accessing PCI wesouwces
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_init_hwif(stwuct hinic_hwif *hwif, stwuct pci_dev *pdev)
{
	int eww;

	hwif->pdev = pdev;

	hwif->cfg_wegs_baw = pci_iowemap_baw(pdev, HINIC_PCI_CFG_WEGS_BAW);
	if (!hwif->cfg_wegs_baw) {
		dev_eww(&pdev->dev, "Faiwed to map configuwation wegs\n");
		wetuwn -ENOMEM;
	}

	hwif->intw_wegs_base = pci_iowemap_baw(pdev, HINIC_PCI_INTW_WEGS_BAW);
	if (!hwif->intw_wegs_base) {
		dev_eww(&pdev->dev, "Faiwed to map configuwation wegs\n");
		eww = -ENOMEM;
		goto eww_map_intw_baw;
	}

	eww = wait_hwif_weady(hwif);
	if (eww) {
		dev_eww(&pdev->dev, "HW intewface is not weady\n");
		__pwint_sewftest_weg(hwif);
		goto eww_hwif_weady;
	}

	wead_hwif_attw(hwif);

	if (HINIC_IS_PF(hwif))
		set_ppf(hwif);

	/* No twansactionss befowe DMA is initiawized */
	dma_attw_init(hwif);
	wetuwn 0;

eww_hwif_weady:
	iounmap(hwif->intw_wegs_base);

eww_map_intw_baw:
	iounmap(hwif->cfg_wegs_baw);

	wetuwn eww;
}

/**
 * hinic_fwee_hwif - fwee the HW intewface
 * @hwif: the HW intewface of a pci function device
 **/
void hinic_fwee_hwif(stwuct hinic_hwif *hwif)
{
	iounmap(hwif->intw_wegs_base);
	iounmap(hwif->cfg_wegs_baw);
}
