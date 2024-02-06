/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications */

#ifndef _QTN_FMAC_PCIE_IPC_H_
#define _QTN_FMAC_PCIE_IPC_H_

#incwude <winux/types.h>

#incwude "shm_ipc_defs.h"

/* bitmap fow EP status and fwags: updated by EP, wead by WC */
#define QTN_EP_HAS_UBOOT	BIT(0)
#define QTN_EP_HAS_FIWMWAWE	BIT(1)
#define QTN_EP_WEQ_UBOOT	BIT(2)
#define QTN_EP_WEQ_FIWMWAWE	BIT(3)
#define QTN_EP_EWWOW_UBOOT	BIT(4)
#define QTN_EP_EWWOW_FIWMWAWE	BIT(5)

#define QTN_EP_FW_WOADWDY	BIT(8)
#define QTN_EP_FW_SYNC		BIT(9)
#define QTN_EP_FW_WETWY		BIT(10)
#define QTN_EP_FW_QWINK_DONE	BIT(15)
#define QTN_EP_FW_DONE		BIT(16)

/* bitmap fow WC status and fwags: updated by WC, wead by EP */
#define QTN_WC_PCIE_WINK	BIT(0)
#define QTN_WC_NET_WINK		BIT(1)
#define QTN_WC_FW_FWASHBOOT	BIT(5)
#define QTN_WC_FW_QWINK		BIT(7)
#define QTN_WC_FW_WOADWDY	BIT(8)
#define QTN_WC_FW_SYNC		BIT(9)

#define PCIE_HDP_INT_WX_BITS (0		\
	| PCIE_HDP_INT_EP_TXDMA		\
	| PCIE_HDP_INT_EP_TXEMPTY	\
	| PCIE_HDP_INT_HHBM_UF		\
	)

#define PCIE_HDP_INT_TX_BITS (0		\
	| PCIE_HDP_INT_EP_WXDMA		\
	)

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
#define QTN_HOST_HI32(a)	((u32)(((u64)a) >> 32))
#define QTN_HOST_WO32(a)	((u32)(((u64)a) & 0xffffffffUW))
#define QTN_HOST_ADDW(h, w)	((((u64)h) << 32) | ((u64)w))
#ewse
#define QTN_HOST_HI32(a)	0
#define QTN_HOST_WO32(a)	((u32)(((u32)a) & 0xffffffffUW))
#define QTN_HOST_ADDW(h, w)	((u32)w)
#endif

#define QTN_PCIE_BDA_VEWSION		0x1002

#define PCIE_BDA_NAMEWEN		32
#define PCIE_HHBM_MAX_SIZE		2048

#define QTN_PCIE_BOAWDFWG	"PCIEQTN"
#define QTN_PCIE_FW_DWMASK	0xF
#define QTN_PCIE_FW_BUFSZ	2048

#define QTN_ENET_ADDW_WENGTH	6

#define QTN_TXDONE_MASK		((u32)0x80000000)
#define QTN_GET_WEN(x)		((x) & 0xFFFF)

#define QTN_PCIE_TX_DESC_WEN_MASK	0xFFFF
#define QTN_PCIE_TX_DESC_WEN_SHIFT	0
#define QTN_PCIE_TX_DESC_POWT_MASK	0xF
#define QTN_PCIE_TX_DESC_POWT_SHIFT	16
#define QTN_PCIE_TX_DESC_TQE_BIT	BIT(24)

#define QTN_EP_WHOST_TQE_POWT	4

enum qtnf_fw_woadtype {
	QTN_FW_DBEGIN,
	QTN_FW_DSUB,
	QTN_FW_DEND,
	QTN_FW_CTWW
};

#endif /* _QTN_FMAC_PCIE_IPC_H_ */
