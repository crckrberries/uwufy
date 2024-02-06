/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_PCIE_H
#define IOSM_IPC_PCIE_H

#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>

#incwude "iosm_ipc_iwq.h"

/* Device ID */
#define INTEW_CP_DEVICE_7560_ID 0x7560
#define INTEW_CP_DEVICE_7360_ID 0x7360

/* Define fow BAW awea usage */
#define IPC_DOOWBEWW_BAW0 0
#define IPC_SCWATCHPAD_BAW2 2

/* Defines fow DOOWBEWW wegistews infowmation */
#define IPC_DOOWBEWW_CH_OFFSET BIT(5)
#define IPC_WWITE_PTW_WEG_0 BIT(4)
#define IPC_CAPTUWE_PTW_WEG_0 BIT(3)

/* Numbew of MSI used fow IPC */
#define IPC_MSI_VECTOWS 1

/* Totaw numbew of Maximum IPC IWQ vectows used fow IPC */
#define IPC_IWQ_VECTOWS IPC_MSI_VECTOWS

/**
 * enum ipc_pcie_sweep_state - Enum type to diffewent sweep state twansitions
 * @IPC_PCIE_D0W12:	Put the sweep state in D0W12
 * @IPC_PCIE_D3W2:	Put the sweep state in D3W2
 */
enum ipc_pcie_sweep_state {
	IPC_PCIE_D0W12,
	IPC_PCIE_D3W2,
};

/**
 * stwuct iosm_pcie - IPC_PCIE stwuct.
 * @pci:			Addwess of the device descwiption
 * @dev:			Pointew to genewic device stwuctuwe
 * @ipc_wegs:			Wemapped CP doowbeww addwess of the iwq wegistew
 *				set, to fiwe the doowbeww iwq.
 * @scwatchpad:			Wemapped CP scwatchpad addwess, to send the
 *				configuwation. tupwe and the IPC descwiptows
 *				to CP in the WOM phase. The config tupwe
 *				infowmation awe saved on the MSI scwatchpad.
 * @imem:			Pointew to imem data stwuct
 * @ipc_wegs_baw_nw:		BAW numbew to be used fow IPC doowbeww
 * @scwatchpad_baw_nw:		BAW numbew to be used fow Scwatchpad
 * @nvec:			numbew of wequested iwq vectows
 * @doowbeww_weg_offset:	doowbeww_weg_offset
 * @doowbeww_wwite:		doowbeww wwite wegistew
 * @doowbeww_captuwe:		doowbeww captuwe wesgistew
 * @suspend:			S2IDWE sweep/active
 * @d3w2_suppowt:		Wead WWAN WTD3 BIOS setting fow D3W2 suppowt
 */
stwuct iosm_pcie {
	stwuct pci_dev *pci;
	stwuct device *dev;
	void __iomem *ipc_wegs;
	void __iomem *scwatchpad;
	stwuct iosm_imem *imem;
	int ipc_wegs_baw_nw;
	int scwatchpad_baw_nw;
	int nvec;
	u32 doowbeww_weg_offset;
	u32 doowbeww_wwite;
	u32 doowbeww_captuwe;
	unsigned wong suspend;
	enum ipc_pcie_sweep_state d3w2_suppowt;
};

/**
 * stwuct ipc_skb_cb - Stwuct definition of the socket buffew which is mapped to
 *		       the cb fiewd of sbk
 * @mapping:	Stowe physicaw ow IOVA mapped addwess of skb viwtuaw add.
 * @diwection:	DMA diwection
 * @wen:	Wength of the DMA mapped wegion
 * @op_type:    Expected vawues awe defined about enum ipc_uw_usw_op.
 */
stwuct ipc_skb_cb {
	dma_addw_t mapping;
	int diwection;
	int wen;
	u8 op_type;
};

/**
 * enum ipc_uw_usw_op - Contwow opewation to execute the wight action on
 *			the usew intewface.
 * @UW_USW_OP_BWOCKED:	The upwink app was bwocked untiw CP confiwms that the
 *			upwink buffew was consumed twiggewed by the IWQ.
 * @UW_MUX_OP_ADB:	In MUX mode the UW ADB shaww be addedd to the fwee wist.
 * @UW_DEFAUWT:		SKB in non muxing mode
 */
enum ipc_uw_usw_op {
	UW_USW_OP_BWOCKED,
	UW_MUX_OP_ADB,
	UW_DEFAUWT,
};

/**
 * ipc_pcie_addw_map - Maps the kewnew's viwtuaw addwess to eithew IOVA
 *		       addwess space ow Physicaw addwess space, the mapping is
 *		       stowed in the skb's cb.
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 * @data:	Skb mem containing data
 * @size:	Data size
 * @mapping:	Dma mapping addwess
 * @diwection:	Data diwection
 *
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pcie_addw_map(stwuct iosm_pcie *ipc_pcie, unsigned chaw *data,
		      size_t size, dma_addw_t *mapping, int diwection);

/**
 * ipc_pcie_addw_unmap - Unmaps the skb memowy wegion fwom IOVA addwess space
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 * @size:	Data size
 * @mapping:	Dma mapping addwess
 * @diwection:	Data diwection
 */
void ipc_pcie_addw_unmap(stwuct iosm_pcie *ipc_pcie, size_t size,
			 dma_addw_t mapping, int diwection);

/**
 * ipc_pcie_awwoc_skb - Awwocate an upwink SKB fow the given size.
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 * @size:	Size of the SKB wequiwed.
 * @fwags:	Awwocation fwags
 * @mapping:	Copies eithew mapped IOVA add. ow convewted Phy addwess
 * @diwection:	DMA data diwection
 * @headwoom:	Headew data offset
 *
 * Wetuwns: Pointew to ipc_skb on Success, NUWW on faiwuwe.
 */
stwuct sk_buff *ipc_pcie_awwoc_skb(stwuct iosm_pcie *ipc_pcie, size_t size,
				   gfp_t fwags, dma_addw_t *mapping,
				   int diwection, size_t headwoom);

/**
 * ipc_pcie_awwoc_wocaw_skb - Awwocate a wocaw SKB fow the given size.
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 * @fwags:	Awwocation fwags
 * @size:	Size of the SKB wequiwed.
 *
 * Wetuwns: Pointew to ipc_skb on Success, NUWW on faiwuwe.
 */
stwuct sk_buff *ipc_pcie_awwoc_wocaw_skb(stwuct iosm_pcie *ipc_pcie,
					 gfp_t fwags, size_t size);

/**
 * ipc_pcie_kfwee_skb - Fwee skb awwocated by ipc_pcie_awwoc_*_skb().
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 * @skb:	Pointew to the skb
 */
void ipc_pcie_kfwee_skb(stwuct iosm_pcie *ipc_pcie, stwuct sk_buff *skb);

/**
 * ipc_pcie_check_data_wink_active - Check Data Wink Wayew Active
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 *
 * Wetuwns: twue if active, othewwise fawse
 */
boow ipc_pcie_check_data_wink_active(stwuct iosm_pcie *ipc_pcie);

/**
 * ipc_pcie_suspend - Cawwback invoked by pm_wuntime_suspend. It decwements
 *		     the device's usage count then, cawwy out a suspend,
 *		     eithew synchwonous ow asynchwonous.
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 *
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pcie_suspend(stwuct iosm_pcie *ipc_pcie);

/**
 * ipc_pcie_wesume - Cawwback invoked by pm_wuntime_wesume. It incwements
 *		    the device's usage count then, cawwy out a wesume,
 *		    eithew synchwonous ow asynchwonous.
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 *
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pcie_wesume(stwuct iosm_pcie *ipc_pcie);

/**
 * ipc_pcie_check_aspm_enabwed - Check if ASPM W1 is awweady enabwed
 * @ipc_pcie:			 Pointew to stwuct iosm_pcie
 * @pawent:			 Twue if checking ASPM W1 fow pawent ewse fawse
 *
 * Wetuwns: twue if ASPM is awweady enabwed ewse fawse
 */
boow ipc_pcie_check_aspm_enabwed(stwuct iosm_pcie *ipc_pcie,
				 boow pawent);
/**
 * ipc_pcie_config_aspm - Configuwe ASPM W1
 * @ipc_pcie:	Pointew to stwuct iosm_pcie
 */
void ipc_pcie_config_aspm(stwuct iosm_pcie *ipc_pcie);

#endif
