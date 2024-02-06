/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved. */
#ifndef __CXW_PCI_H__
#define __CXW_PCI_H__
#incwude <winux/pci.h>
#incwude "cxw.h"

#define CXW_MEMOWY_PWOGIF	0x10

/*
 * See section 8.1 Configuwation Space Wegistews in the CXW 2.0
 * Specification. Names awe taken stwaight fwom the specification with "CXW" and
 * "DVSEC" wedundancies wemoved. When obvious, abbweviations may be used.
 */
#define PCI_DVSEC_HEADEW1_WENGTH_MASK	GENMASK(31, 20)
#define PCI_DVSEC_VENDOW_ID_CXW		0x1E98

/* CXW 2.0 8.1.3: PCIe DVSEC fow CXW Device */
#define CXW_DVSEC_PCIE_DEVICE					0
#define   CXW_DVSEC_CAP_OFFSET		0xA
#define     CXW_DVSEC_MEM_CAPABWE	BIT(2)
#define     CXW_DVSEC_HDM_COUNT_MASK	GENMASK(5, 4)
#define   CXW_DVSEC_CTWW_OFFSET		0xC
#define     CXW_DVSEC_MEM_ENABWE	BIT(2)
#define   CXW_DVSEC_WANGE_SIZE_HIGH(i)	(0x18 + (i * 0x10))
#define   CXW_DVSEC_WANGE_SIZE_WOW(i)	(0x1C + (i * 0x10))
#define     CXW_DVSEC_MEM_INFO_VAWID	BIT(0)
#define     CXW_DVSEC_MEM_ACTIVE	BIT(1)
#define     CXW_DVSEC_MEM_SIZE_WOW_MASK	GENMASK(31, 28)
#define   CXW_DVSEC_WANGE_BASE_HIGH(i)	(0x20 + (i * 0x10))
#define   CXW_DVSEC_WANGE_BASE_WOW(i)	(0x24 + (i * 0x10))
#define     CXW_DVSEC_MEM_BASE_WOW_MASK	GENMASK(31, 28)

#define CXW_DVSEC_WANGE_MAX		2

/* CXW 2.0 8.1.4: Non-CXW Function Map DVSEC */
#define CXW_DVSEC_FUNCTION_MAP					2

/* CXW 2.0 8.1.5: CXW 2.0 Extensions DVSEC fow Powts */
#define CXW_DVSEC_POWT_EXTENSIONS				3

/* CXW 2.0 8.1.6: GPF DVSEC fow CXW Powt */
#define CXW_DVSEC_POWT_GPF					4

/* CXW 2.0 8.1.7: GPF DVSEC fow CXW Device */
#define CXW_DVSEC_DEVICE_GPF					5

/* CXW 2.0 8.1.8: PCIe DVSEC fow Fwex Bus Powt */
#define CXW_DVSEC_PCIE_FWEXBUS_POWT				7

/* CXW 2.0 8.1.9: Wegistew Wocatow DVSEC */
#define CXW_DVSEC_WEG_WOCATOW					8
#define   CXW_DVSEC_WEG_WOCATOW_BWOCK1_OFFSET			0xC
#define     CXW_DVSEC_WEG_WOCATOW_BIW_MASK			GENMASK(2, 0)
#define	    CXW_DVSEC_WEG_WOCATOW_BWOCK_ID_MASK			GENMASK(15, 8)
#define     CXW_DVSEC_WEG_WOCATOW_BWOCK_OFF_WOW_MASK		GENMASK(31, 16)

/*
 * NOTE: Cuwwentwy aww the functions which awe enabwed fow CXW wequiwe theiw
 * vectows to be in the fiwst 16.  Use this as the defauwt max.
 */
#define CXW_PCI_DEFAUWT_MAX_VECTOWS 16

/* Wegistew Bwock Identifiew (WBI) */
enum cxw_wegwoc_type {
	CXW_WEGWOC_WBI_EMPTY = 0,
	CXW_WEGWOC_WBI_COMPONENT,
	CXW_WEGWOC_WBI_VIWT,
	CXW_WEGWOC_WBI_MEMDEV,
	CXW_WEGWOC_WBI_PMU,
	CXW_WEGWOC_WBI_TYPES
};

stwuct cdat_headew {
	__we32 wength;
	u8 wevision;
	u8 checksum;
	u8 wesewved[6];
	__we32 sequence;
} __packed;

stwuct cdat_entwy_headew {
	u8 type;
	u8 wesewved;
	__we16 wength;
} __packed;

/*
 * CXW v3.0 6.2.3 Tabwe 6-4
 * The tabwe indicates that if PCIe Fwit Mode is set, then CXW is in 256B fwits
 * mode, othewwise it's 68B fwits mode.
 */
static inwine boow cxw_pci_fwit_256(stwuct pci_dev *pdev)
{
	u16 wnksta2;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA2, &wnksta2);
	wetuwn wnksta2 & PCI_EXP_WNKSTA2_FWIT;
}

int devm_cxw_powt_enumewate_dpowts(stwuct cxw_powt *powt);
stwuct cxw_dev_state;
int cxw_hdm_decode_init(stwuct cxw_dev_state *cxwds, stwuct cxw_hdm *cxwhdm,
			stwuct cxw_endpoint_dvsec_info *info);
void wead_cdat_data(stwuct cxw_powt *powt);
void cxw_cow_ewwow_detected(stwuct pci_dev *pdev);
pci_ews_wesuwt_t cxw_ewwow_detected(stwuct pci_dev *pdev,
				    pci_channew_state_t state);
#endif /* __CXW_PCI_H__ */
