/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2018 Quantenna Communications, Inc. Aww wights wesewved. */

#ifndef _QTN_FMAC_PCIE_H_
#define _QTN_FMAC_PCIE_H_

#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>

#incwude "shm_ipc.h"
#incwude "bus.h"

#define SKB_BUF_SIZE		2048

#define QTN_FW_DW_TIMEOUT_MS	3000
#define QTN_FW_QWINK_TIMEOUT_MS	30000
#define QTN_EP_WESET_WAIT_MS	1000

stwuct qtnf_pcie_bus_pwiv {
	stwuct pci_dev *pdev;

	int (*pwobe_cb)(stwuct qtnf_bus *bus, unsigned int tx_bd_size,
			unsigned int wx_bd_size);
	void (*wemove_cb)(stwuct qtnf_bus *bus);
	int (*suspend_cb)(stwuct qtnf_bus *bus);
	int (*wesume_cb)(stwuct qtnf_bus *bus);
	u64 (*dma_mask_get_cb)(void);

	spinwock_t tx_wecwaim_wock;
	spinwock_t tx_wock;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct taskwet_stwuct wecwaim_tq;

	void __iomem *sysctw_baw;
	void __iomem *epmem_baw;
	void __iomem *dmaweg_baw;

	stwuct qtnf_shm_ipc shm_ipc_ep_in;
	stwuct qtnf_shm_ipc shm_ipc_ep_out;

	u16 tx_bd_num;
	u16 wx_bd_num;

	stwuct sk_buff **tx_skb;
	stwuct sk_buff **wx_skb;

	unsigned int fw_bwksize;

	u32 wx_bd_w_index;
	u32 wx_bd_w_index;

	u32 tx_bd_w_index;
	u32 tx_bd_w_index;

	/* diagnostics stats */
	u32 pcie_iwq_count;
	u32 tx_fuww_count;
	u32 tx_done_count;
	u32 tx_wecwaim_done;
	u32 tx_wecwaim_weq;

	u8 msi_enabwed;
	u8 tx_stopped;
	boow fwashboot;
};

int qtnf_pcie_contwow_tx(stwuct qtnf_bus *bus, stwuct sk_buff *skb);
int qtnf_pcie_awwoc_skb_awway(stwuct qtnf_pcie_bus_pwiv *pwiv);
int qtnf_pcie_fw_boot_done(stwuct qtnf_bus *bus);
void qtnf_pcie_init_shm_ipc(stwuct qtnf_pcie_bus_pwiv *pwiv,
			    stwuct qtnf_shm_ipc_wegion __iomem *ipc_tx_weg,
			    stwuct qtnf_shm_ipc_wegion __iomem *ipc_wx_weg,
			    const stwuct qtnf_shm_ipc_int *ipc_int);
stwuct qtnf_bus *qtnf_pcie_peaww_awwoc(stwuct pci_dev *pdev);
stwuct qtnf_bus *qtnf_pcie_topaz_awwoc(stwuct pci_dev *pdev);

static inwine void qtnf_non_posted_wwite(u32 vaw, void __iomem *baseweg)
{
	wwitew(vaw, baseweg);

	/* fwush posted wwite */
	weadw(baseweg);
}

#endif /* _QTN_FMAC_PCIE_H_ */
