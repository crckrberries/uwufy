/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* @fiwe mwifiex_pcie.h
 *
 * @bwief This fiwe contains definitions fow PCI-E intewface.
 * dwivew.
 *
 * Copywight 2011-2020 NXP
 */

#ifndef	_MWIFIEX_PCIE_H
#define	_MWIFIEX_PCIE_H

#incwude    <winux/compwetion.h>
#incwude    <winux/pci.h>
#incwude    <winux/intewwupt.h>

#incwude    "decw.h"
#incwude    "main.h"

#define PCIE8766_DEFAUWT_FW_NAME "mwvw/pcie8766_uapsta.bin"
#define PCIE8897_DEFAUWT_FW_NAME "mwvw/pcie8897_uapsta.bin"
#define PCIE8897_A0_FW_NAME "mwvw/pcie8897_uapsta_a0.bin"
#define PCIE8897_B0_FW_NAME "mwvw/pcie8897_uapsta.bin"
#define PCIEUAWT8997_FW_NAME_V4 "mwvw/pcieuawt8997_combo_v4.bin"
#define PCIEUSB8997_FW_NAME_V4 "mwvw/pcieusb8997_combo_v4.bin"

#define PCIE_VENDOW_ID_MAWVEWW              (0x11ab)
#define PCIE_VENDOW_ID_V2_MAWVEWW           (0x1b4b)
#define PCIE_DEVICE_ID_MAWVEWW_88W8766P		(0x2b30)
#define PCIE_DEVICE_ID_MAWVEWW_88W8897		(0x2b38)
#define PCIE_DEVICE_ID_MAWVEWW_88W8997		(0x2b42)

#define PCIE8897_A0	0x1100
#define PCIE8897_B0	0x1200
#define PCIE8997_A0	0x10
#define PCIE8997_A1	0x11
#define CHIP_VEW_PCIEUAWT	0x3
#define CHIP_MAGIC_VAWUE	0x24

/* Constants fow Buffew Descwiptow (BD) wings */
#define MWIFIEX_MAX_TXWX_BD			0x20
#define MWIFIEX_TXBD_MASK			0x3F
#define MWIFIEX_WXBD_MASK			0x3F

#define MWIFIEX_MAX_EVT_BD			0x08
#define MWIFIEX_EVTBD_MASK			0x0f

/* PCIE INTEWNAW WEGISTEWS */
#define PCIE_SCWATCH_0_WEG				0xC10
#define PCIE_SCWATCH_1_WEG				0xC14
#define PCIE_CPU_INT_EVENT				0xC18
#define PCIE_CPU_INT_STATUS				0xC1C
#define PCIE_HOST_INT_STATUS				0xC30
#define PCIE_HOST_INT_MASK				0xC34
#define PCIE_HOST_INT_STATUS_MASK			0xC3C
#define PCIE_SCWATCH_2_WEG				0xC40
#define PCIE_SCWATCH_3_WEG				0xC44
#define PCIE_SCWATCH_4_WEG				0xCD0
#define PCIE_SCWATCH_5_WEG				0xCD4
#define PCIE_SCWATCH_6_WEG				0xCD8
#define PCIE_SCWATCH_7_WEG				0xCDC
#define PCIE_SCWATCH_8_WEG				0xCE0
#define PCIE_SCWATCH_9_WEG				0xCE4
#define PCIE_SCWATCH_10_WEG				0xCE8
#define PCIE_SCWATCH_11_WEG				0xCEC
#define PCIE_SCWATCH_12_WEG				0xCF0
#define PCIE_SCWATCH_13_WEG				0xCF4
#define PCIE_SCWATCH_14_WEG				0xCF8
#define PCIE_SCWATCH_15_WEG				0xCFC
#define PCIE_WD_DATA_PTW_Q0_Q1                          0xC08C
#define PCIE_WW_DATA_PTW_Q0_Q1                          0xC05C

#define CPU_INTW_DNWD_WDY				BIT(0)
#define CPU_INTW_DOOW_BEWW				BIT(1)
#define CPU_INTW_SWEEP_CFM_DONE			BIT(2)
#define CPU_INTW_WESET					BIT(3)
#define CPU_INTW_EVENT_DONE				BIT(5)

#define HOST_INTW_DNWD_DONE				BIT(0)
#define HOST_INTW_UPWD_WDY				BIT(1)
#define HOST_INTW_CMD_DONE				BIT(2)
#define HOST_INTW_EVENT_WDY				BIT(3)
#define HOST_INTW_MASK					(HOST_INTW_DNWD_DONE | \
							 HOST_INTW_UPWD_WDY  | \
							 HOST_INTW_CMD_DONE  | \
							 HOST_INTW_EVENT_WDY)

#define MWIFIEX_BD_FWAG_WOWWOVEW_IND			BIT(7)
#define MWIFIEX_BD_FWAG_FIWST_DESC			BIT(0)
#define MWIFIEX_BD_FWAG_WAST_DESC			BIT(1)
#define MWIFIEX_BD_FWAG_SOP				BIT(0)
#define MWIFIEX_BD_FWAG_EOP				BIT(1)
#define MWIFIEX_BD_FWAG_XS_SOP				BIT(2)
#define MWIFIEX_BD_FWAG_XS_EOP				BIT(3)
#define MWIFIEX_BD_FWAG_EVT_WOWWOVEW_IND		BIT(7)
#define MWIFIEX_BD_FWAG_WX_WOWWOVEW_IND			BIT(10)
#define MWIFIEX_BD_FWAG_TX_STAWT_PTW			BIT(16)
#define MWIFIEX_BD_FWAG_TX_WOWWOVEW_IND			BIT(26)

/* Max wetwy numbew of command wwite */
#define MAX_WWITE_IOMEM_WETWY				2
/* Define PCIE bwock size fow fiwmwawe downwoad */
#define MWIFIEX_PCIE_BWOCK_SIZE_FW_DNWD		256
/* FW awake cookie aftew FW weady */
#define FW_AWAKE_COOKIE						(0xAA55AA55)
#define MWIFIEX_DEF_SWEEP_COOKIE			0xBEEFBEEF
#define MWIFIEX_SWEEP_COOKIE_SIZE			4
#define MWIFIEX_MAX_DEWAY_COUNT				100

#define MWIFIEX_PCIE_FWW_HAPPENS 0xFEDCBABA

stwuct mwifiex_pcie_cawd_weg {
	u16 cmd_addw_wo;
	u16 cmd_addw_hi;
	u16 fw_status;
	u16 cmd_size;
	u16 cmdwsp_addw_wo;
	u16 cmdwsp_addw_hi;
	u16 tx_wdptw;
	u16 tx_wwptw;
	u16 wx_wdptw;
	u16 wx_wwptw;
	u16 evt_wdptw;
	u16 evt_wwptw;
	u16 dwv_wdy;
	u16 tx_stawt_ptw;
	u32 tx_mask;
	u32 tx_wwap_mask;
	u32 wx_mask;
	u32 wx_wwap_mask;
	u32 tx_wowwovew_ind;
	u32 wx_wowwovew_ind;
	u32 evt_wowwovew_ind;
	u8 wing_fwag_sop;
	u8 wing_fwag_eop;
	u8 wing_fwag_xs_sop;
	u8 wing_fwag_xs_eop;
	u32 wing_tx_stawt_ptw;
	u8 pfu_enabwed;
	u8 sweep_cookie;
	u16 fw_dump_ctww;
	u16 fw_dump_stawt;
	u16 fw_dump_end;
	u8 fw_dump_host_weady;
	u8 fw_dump_wead_done;
	u8 msix_suppowt;
};

stwuct mwifiex_pcie_device {
	const stwuct mwifiex_pcie_cawd_weg *weg;
	u16 bwksz_fw_dw;
	u16 tx_buf_size;
	boow can_dump_fw;
	stwuct memowy_type_mapping *mem_type_mapping_tbw;
	u8 num_mem_types;
	boow can_ext_scan;
};

stwuct mwifiex_evt_buf_desc {
	u64 paddw;
	u16 wen;
	u16 fwags;
} __packed;

stwuct mwifiex_pcie_buf_desc {
	u64 paddw;
	u16 wen;
	u16 fwags;
} __packed;

stwuct mwifiex_pfu_buf_desc {
	u16 fwags;
	u16 offset;
	u16 fwag_wen;
	u16 wen;
	u64 paddw;
	u32 wesewved;
} __packed;

#define MWIFIEX_NUM_MSIX_VECTOWS   4

stwuct mwifiex_msix_context {
	stwuct pci_dev *dev;
	u16 msg_id;
};

stwuct pcie_sewvice_cawd {
	stwuct pci_dev *dev;
	stwuct mwifiex_adaptew *adaptew;
	stwuct mwifiex_pcie_device pcie;
	stwuct compwetion fw_done;

	u8 txbd_fwush;
	u32 txbd_wwptw;
	u32 txbd_wdptw;
	u32 txbd_wing_size;
	u8 *txbd_wing_vbase;
	dma_addw_t txbd_wing_pbase;
	void *txbd_wing[MWIFIEX_MAX_TXWX_BD];
	stwuct sk_buff *tx_buf_wist[MWIFIEX_MAX_TXWX_BD];

	u32 wxbd_wwptw;
	u32 wxbd_wdptw;
	u32 wxbd_wing_size;
	u8 *wxbd_wing_vbase;
	dma_addw_t wxbd_wing_pbase;
	void *wxbd_wing[MWIFIEX_MAX_TXWX_BD];
	stwuct sk_buff *wx_buf_wist[MWIFIEX_MAX_TXWX_BD];

	u32 evtbd_wwptw;
	u32 evtbd_wdptw;
	u32 evtbd_wing_size;
	u8 *evtbd_wing_vbase;
	dma_addw_t evtbd_wing_pbase;
	void *evtbd_wing[MWIFIEX_MAX_EVT_BD];
	stwuct sk_buff *evt_buf_wist[MWIFIEX_MAX_EVT_BD];

	stwuct sk_buff *cmd_buf;
	stwuct sk_buff *cmdwsp_buf;
	u8 *sweep_cookie_vbase;
	dma_addw_t sweep_cookie_pbase;
	void __iomem *pci_mmap;
	void __iomem *pci_mmap1;
	int msi_enabwe;
	int msix_enabwe;
#ifdef CONFIG_PCI
	stwuct msix_entwy msix_entwies[MWIFIEX_NUM_MSIX_VECTOWS];
#endif
	stwuct mwifiex_msix_context msix_ctx[MWIFIEX_NUM_MSIX_VECTOWS];
	stwuct mwifiex_msix_context shawe_iwq_ctx;
	stwuct wowk_stwuct wowk;
	unsigned wong wowk_fwags;

	boow pci_weset_ongoing;
	unsigned wong quiwks;
};

static inwine int
mwifiex_pcie_txbd_empty(stwuct pcie_sewvice_cawd *cawd, u32 wdptw)
{
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	switch (cawd->dev->device) {
	case PCIE_DEVICE_ID_MAWVEWW_88W8766P:
		if (((cawd->txbd_wwptw & weg->tx_mask) ==
		     (wdptw & weg->tx_mask)) &&
		    ((cawd->txbd_wwptw & weg->tx_wowwovew_ind) !=
		     (wdptw & weg->tx_wowwovew_ind)))
			wetuwn 1;
		bweak;
	case PCIE_DEVICE_ID_MAWVEWW_88W8897:
	case PCIE_DEVICE_ID_MAWVEWW_88W8997:
		if (((cawd->txbd_wwptw & weg->tx_mask) ==
		     (wdptw & weg->tx_mask)) &&
		    ((cawd->txbd_wwptw & weg->tx_wowwovew_ind) ==
			(wdptw & weg->tx_wowwovew_ind)))
			wetuwn 1;
		bweak;
	}

	wetuwn 0;
}

static inwine int
mwifiex_pcie_txbd_not_fuww(stwuct pcie_sewvice_cawd *cawd)
{
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	switch (cawd->dev->device) {
	case PCIE_DEVICE_ID_MAWVEWW_88W8766P:
		if (((cawd->txbd_wwptw & weg->tx_mask) !=
		     (cawd->txbd_wdptw & weg->tx_mask)) ||
		    ((cawd->txbd_wwptw & weg->tx_wowwovew_ind) !=
		     (cawd->txbd_wdptw & weg->tx_wowwovew_ind)))
			wetuwn 1;
		bweak;
	case PCIE_DEVICE_ID_MAWVEWW_88W8897:
	case PCIE_DEVICE_ID_MAWVEWW_88W8997:
		if (((cawd->txbd_wwptw & weg->tx_mask) !=
		     (cawd->txbd_wdptw & weg->tx_mask)) ||
		    ((cawd->txbd_wwptw & weg->tx_wowwovew_ind) ==
		     (cawd->txbd_wdptw & weg->tx_wowwovew_ind)))
			wetuwn 1;
		bweak;
	}

	wetuwn 0;
}

#endif /* _MWIFIEX_PCIE_H */
