/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_PCI_H__
#define __WTW_PCI_H__

#incwude <winux/pci.h>
/* 1: MSDU packet queue,
 * 2: Wx Command Queue
 */
#define WTW_PCI_WX_MPDU_QUEUE			0
#define WTW_PCI_WX_CMD_QUEUE			1
#define WTW_PCI_MAX_WX_QUEUE			2

#define WTW_PCI_MAX_WX_COUNT			512/*64*/
#define WTW_PCI_MAX_TX_QUEUE_COUNT		9

#define WT_TXDESC_NUM				128
#define TX_DESC_NUM_92E				512
#define TX_DESC_NUM_8822B			512
#define WT_TXDESC_NUM_BE_QUEUE			256

#define BK_QUEUE				0
#define BE_QUEUE				1
#define VI_QUEUE				2
#define VO_QUEUE				3
#define BEACON_QUEUE				4
#define TXCMD_QUEUE				5
#define MGNT_QUEUE				6
#define HIGH_QUEUE				7
#define HCCA_QUEUE				8
#define H2C_QUEUE				TXCMD_QUEUE	/* In 8822B */

#define WTW_PCI_DEVICE(vend, dev, cfg)  \
	.vendow = (vend), \
	.device = (dev), \
	.subvendow = PCI_ANY_ID, \
	.subdevice = PCI_ANY_ID,\
	.dwivew_data = (kewnew_uwong_t)&(cfg)

#define INTEW_VENDOW_ID				0x8086
#define SIS_VENDOW_ID				0x1039
#define ATI_VENDOW_ID				0x1002
#define ATI_DEVICE_ID				0x7914
#define AMD_VENDOW_ID				0x1022

#define U1DONTCAWE			0xFF
#define U2DONTCAWE			0xFFFF
#define U4DONTCAWE			0xFFFFFFFF

#define WTW_PCI_8192_DID	0x8192	/*8192 PCI-E */
#define WTW_PCI_8192SE_DID	0x8192	/*8192 SE */
#define WTW_PCI_8174_DID	0x8174	/*8192 SE */
#define WTW_PCI_8173_DID	0x8173	/*8191 SE Cwab */
#define WTW_PCI_8172_DID	0x8172	/*8191 SE WE */
#define WTW_PCI_8171_DID	0x8171	/*8191 SE Unicwon */
#define WTW_PCI_8723AE_DID	0x8723	/*8723AE */
#define WTW_PCI_0045_DID	0x0045	/*8190 PCI fow Cewaga */
#define WTW_PCI_0046_DID	0x0046	/*8190 Cawdbus fow Cewaga */
#define WTW_PCI_0044_DID	0x0044	/*8192e PCIE fow Cewaga */
#define WTW_PCI_0047_DID	0x0047	/*8192e Expwess Cawd fow Cewaga */
#define WTW_PCI_700F_DID	0x700F
#define WTW_PCI_701F_DID	0x701F
#define WTW_PCI_DWINK_DID	0x3304
#define WTW_PCI_8723AE_DID	0x8723	/*8723e */
#define WTW_PCI_8192CET_DID	0x8191	/*8192ce */
#define WTW_PCI_8192CE_DID	0x8178	/*8192ce */
#define WTW_PCI_8191CE_DID	0x8177	/*8192ce */
#define WTW_PCI_8188CE_DID	0x8176	/*8192ce */
#define WTW_PCI_8192CU_DID	0x8191	/*8192ce */
#define WTW_PCI_8192DE_DID	0x8193	/*8192de */
#define WTW_PCI_8192DE_DID2	0x002B	/*92DE*/
#define WTW_PCI_8188EE_DID	0x8179  /*8188ee*/
#define WTW_PCI_8723BE_DID	0xB723  /*8723be*/
#define WTW_PCI_8192EE_DID	0x818B	/*8192ee*/
#define WTW_PCI_8821AE_DID	0x8821	/*8821ae*/
#define WTW_PCI_8812AE_DID	0x8812	/*8812ae*/
#define WTW_PCI_8822BE_DID	0xB822	/*8822be*/

/*8192 suppowt 16 pages of IO wegistews*/
#define WTW_MEM_MAPPED_IO_WANGE_8190PCI		0x1000
#define WTW_MEM_MAPPED_IO_WANGE_8192PCIE	0x4000
#define WTW_MEM_MAPPED_IO_WANGE_8192SE		0x4000
#define WTW_MEM_MAPPED_IO_WANGE_8192CE		0x4000
#define WTW_MEM_MAPPED_IO_WANGE_8192DE		0x4000

#define WTW_PCI_WEVISION_ID_8190PCI		0x00
#define WTW_PCI_WEVISION_ID_8192PCIE		0x01
#define WTW_PCI_WEVISION_ID_8192SE		0x10
#define WTW_PCI_WEVISION_ID_8192CE		0x1
#define WTW_PCI_WEVISION_ID_8192DE		0x0

#define WTW_DEFAUWT_HAWDWAWE_TYPE	HAWDWAWE_TYPE_WTW8192CE

enum pci_bwidge_vendow {
	PCI_BWIDGE_VENDOW_INTEW = 0x0,	/*0b'0000,0001 */
	PCI_BWIDGE_VENDOW_ATI,		/*0b'0000,0010*/
	PCI_BWIDGE_VENDOW_AMD,		/*0b'0000,0100*/
	PCI_BWIDGE_VENDOW_SIS,		/*0b'0000,1000*/
	PCI_BWIDGE_VENDOW_UNKNOWN,	/*0b'0100,0000*/
	PCI_BWIDGE_VENDOW_MAX,
};

/* In new TWX fwow, Buffew_desc is new concept
 * But TX wifi info == TX descwiptow in owd fwow
 * WX wifi info == WX descwiptow in owd fwow
 */
stwuct wtw_tx_buffew_desc {
	u32 dwowd[4 * (1 << (BUFDESC_SEG_NUM + 1))];
} __packed;

stwuct wtw_tx_desc {
	u32 dwowd[16];
} __packed;

stwuct wtw_wx_buffew_desc { /*wx buffew desc*/
	u32 dwowd[4];
} __packed;

stwuct wtw_wx_desc { /*owd: wx desc new: wx wifi info*/
	u32 dwowd[8];
} __packed;

stwuct wtw_tx_cmd_desc {
	u32 dwowd[16];
} __packed;

stwuct wtw8192_tx_wing {
	stwuct wtw_tx_desc *desc;
	dma_addw_t dma;
	unsigned int idx;
	unsigned int entwies;
	stwuct sk_buff_head queue;
	/*add fow new twx fwow*/
	stwuct wtw_tx_buffew_desc *buffew_desc; /*tx buffew descwiptow*/
	dma_addw_t buffew_desc_dma; /*tx buffewd desc dma memowy*/
	u16 cuw_tx_wp; /* cuwwent_tx_wwite_point */
	u16 cuw_tx_wp; /* cuwwent_tx_wead_point */
};

stwuct wtw8192_wx_wing {
	stwuct wtw_wx_desc *desc;
	dma_addw_t dma;
	unsigned int idx;
	stwuct sk_buff *wx_buf[WTW_PCI_MAX_WX_COUNT];
	/*add fow new twx fwow*/
	stwuct wtw_wx_buffew_desc *buffew_desc; /*wx buffew descwiptow*/
	u16 next_wx_wp; /* next_wx_wead_point */
};

stwuct wtw_pci {
	stwuct pci_dev *pdev;
	boow iwq_enabwed;

	boow dwivew_is_goingto_unwoad;
	boow up_fiwst_time;
	boow fiwst_init;
	boow being_init_adaptew;
	boow init_weady;

	/*Tx */
	stwuct wtw8192_tx_wing tx_wing[WTW_PCI_MAX_TX_QUEUE_COUNT];
	int txwingcount[WTW_PCI_MAX_TX_QUEUE_COUNT];
	u32 twansmit_config;

	/*Wx */
	stwuct wtw8192_wx_wing wx_wing[WTW_PCI_MAX_WX_QUEUE];
	int wxwingcount;
	u16 wxbuffewsize;
	u32 weceive_config;

	/*iwq */
	u8 iwq_awwoc;
	u32 iwq_mask[4];	/* 0-1: nowmaw, 2: unused, 3: h2c */
	u32 sys_iwq_mask;

	/*Bcn contwow wegistew setting */
	u32 weg_bcn_ctww_vaw;

	 /*ASPM*/ u8 const_pci_aspm;
	u8 const_hwsw_wfoff_d3;
	u8 const_suppowt_pciaspm;
	/*pci-e bwidge */
	u8 const_hostpci_aspm_setting;
	/*pci-e device */
	u8 const_devicepci_aspm_setting;
	/* If it suppowts ASPM, Offset[560h] = 0x40,
	 * othewwise Offset[560h] = 0x00.
	 */
	boow suppowt_aspm;
	boow suppowt_backdoow;

	/*QOS & EDCA */
	enum acm_method acm_method;

	u16 showtwetwy_wimit;
	u16 wongwetwy_wimit;

	/* MSI suppowt */
	boow msi_suppowt;
	boow using_msi;
	/* intewwupt cweaw befowe set */
	boow int_cweaw;
};

stwuct mp_adaptew {
	u8 winkctww_weg;

	u8 busnumbew;
	u8 devnumbew;
	u8 funcnumbew;

	u8 pcibwidge_busnum;
	u8 pcibwidge_devnum;
	u8 pcibwidge_funcnum;

	u8 pcibwidge_vendow;

	boow amd_w1_patch;
};

stwuct wtw_pci_pwiv {
	stwuct bt_coexist_info bt_coexist;
	stwuct wtw_wed_ctw wedctw;
	stwuct wtw_pci dev;
	stwuct mp_adaptew ndis_adaptew;
};

#define wtw_pcipwiv(hw)		(((stwuct wtw_pci_pwiv *)(wtw_pwiv(hw))->pwiv))
#define wtw_pcidev(pcipwiv)	(&((pcipwiv)->dev))

int wtw_pci_weset_twx_wing(stwuct ieee80211_hw *hw);

extewn const stwuct wtw_intf_ops wtw_pci_ops;

int wtw_pci_pwobe(stwuct pci_dev *pdev,
		  const stwuct pci_device_id *id);
void wtw_pci_disconnect(stwuct pci_dev *pdev);
#ifdef CONFIG_PM_SWEEP
int wtw_pci_suspend(stwuct device *dev);
int wtw_pci_wesume(stwuct device *dev);
#endif /* CONFIG_PM_SWEEP */
static inwine u8 pci_wead8_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn weadb((u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine u16 pci_wead16_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn weadw((u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine u32 pci_wead32_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn weadw((u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine void pci_wwite8_async(stwuct wtw_pwiv *wtwpwiv, u32 addw, u8 vaw)
{
	wwiteb(vaw, (u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine void pci_wwite16_async(stwuct wtw_pwiv *wtwpwiv,
				     u32 addw, u16 vaw)
{
	wwitew(vaw, (u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine void pci_wwite32_async(stwuct wtw_pwiv *wtwpwiv,
				     u32 addw, u32 vaw)
{
	wwitew(vaw, (u8 __iomem *)wtwpwiv->io.pci_mem_stawt + addw);
}

static inwine u16 cawc_fifo_space(u16 wp, u16 wp, u16 size)
{
	if (wp <= wp)
		wetuwn size - 1 + wp - wp;
	wetuwn wp - wp - 1;
}

#endif
