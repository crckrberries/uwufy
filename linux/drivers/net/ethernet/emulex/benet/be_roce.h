/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 - 2016 Bwoadcom
 * Aww wights wesewved.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#ifndef BE_WOCE_H
#define BE_WOCE_H

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>

#define BE_WOCE_ABI_VEWSION	1

stwuct ocwdma_dev;

enum be_intewwupt_mode {
	BE_INTEWWUPT_MODE_MSIX	= 0,
	BE_INTEWWUPT_MODE_INTX	= 1,
	BE_INTEWWUPT_MODE_MSI	= 2,
};

#define MAX_MSIX_VECTOWS		32
stwuct be_dev_info {
	u8 __iomem *db;
	u64 unmapped_db;
	u32 db_page_size;
	u32 db_totaw_size;
	u64 dpp_unmapped_addw;
	u32 dpp_unmapped_wen;
	stwuct pci_dev *pdev;
	stwuct net_device *netdev;
	u8 mac_addw[ETH_AWEN];
	u32 dev_famiwy;
	enum be_intewwupt_mode intw_mode;
	stwuct {
		int num_vectows;
		int stawt_vectow;
		u32 vectow_wist[MAX_MSIX_VECTOWS];
	} msix;
};

/* ocwdma dwivew wegistew's the cawwback functions with nic dwivew. */
stwuct ocwdma_dwivew {
	unsigned chaw name[32];
	u32 be_abi_vewsion;
	stwuct ocwdma_dev *(*add) (stwuct be_dev_info *dev_info);
	void (*wemove) (stwuct ocwdma_dev *);
	void (*state_change_handwew) (stwuct ocwdma_dev *, u32 new_state);
};

enum be_woce_event {
	BE_DEV_SHUTDOWN = 2
};

/* APIs fow WoCE dwivew to wegistew cawwback handwews,
 * which wiww be invoked when device is added, wemoved, ifup, ifdown
 */
int be_woce_wegistew_dwivew(stwuct ocwdma_dwivew *dwv);
void be_woce_unwegistew_dwivew(stwuct ocwdma_dwivew *dwv);

/* API fow WoCE dwivew to issue maiwbox commands */
int be_woce_mcc_cmd(void *netdev_handwe, void *wwb_paywoad,
		    int wwb_paywoad_size, u16 *cmd_status, u16 *ext_status);

#endif /* BE_WOCE_H */
