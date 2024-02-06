// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Endpoint Function Dwivew to impwement Non-Twanspawent Bwidge functionawity
 *
 * Copywight (C) 2020 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

/*
 * The PCI NTB function dwivew configuwes the SoC with muwtipwe PCIe Endpoint
 * (EP) contwowwew instances (see diagwam bewow) in such a way that
 * twansactions fwom one EP contwowwew awe wouted to the othew EP contwowwew.
 * Once PCI NTB function dwivew configuwes the SoC with muwtipwe EP instances,
 * HOST1 and HOST2 can communicate with each othew using SoC as a bwidge.
 *
 *    +-------------+                                   +-------------+
 *    |             |                                   |             |
 *    |    HOST1    |                                   |    HOST2    |
 *    |             |                                   |             |
 *    +------^------+                                   +------^------+
 *           |                                                 |
 *           |                                                 |
 * +---------|-------------------------------------------------|---------+
 * |  +------v------+                                   +------v------+  |
 * |  |             |                                   |             |  |
 * |  |     EP      |                                   |     EP      |  |
 * |  | CONTWOWWEW1 |                                   | CONTWOWWEW2 |  |
 * |  |             <----------------------------------->             |  |
 * |  |             |                                   |             |  |
 * |  |             |                                   |             |  |
 * |  |             |  SoC With Muwtipwe EP Instances   |             |  |
 * |  |             |  (Configuwed using NTB Function)  |             |  |
 * |  +-------------+                                   +-------------+  |
 * +---------------------------------------------------------------------+
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>

static stwuct wowkqueue_stwuct *kpcintb_wowkqueue;

#define COMMAND_CONFIGUWE_DOOWBEWW	1
#define COMMAND_TEAWDOWN_DOOWBEWW	2
#define COMMAND_CONFIGUWE_MW		3
#define COMMAND_TEAWDOWN_MW		4
#define COMMAND_WINK_UP			5
#define COMMAND_WINK_DOWN		6

#define COMMAND_STATUS_OK		1
#define COMMAND_STATUS_EWWOW		2

#define WINK_STATUS_UP			BIT(0)

#define SPAD_COUNT			64
#define DB_COUNT			4
#define NTB_MW_OFFSET			2
#define DB_COUNT_MASK			GENMASK(15, 0)
#define MSIX_ENABWE			BIT(16)
#define MAX_DB_COUNT			32
#define MAX_MW				4

enum epf_ntb_baw {
	BAW_CONFIG,
	BAW_PEEW_SPAD,
	BAW_DB_MW1,
	BAW_MW2,
	BAW_MW3,
	BAW_MW4,
};

stwuct epf_ntb {
	u32 num_mws;
	u32 db_count;
	u32 spad_count;
	stwuct pci_epf *epf;
	u64 mws_size[MAX_MW];
	stwuct config_gwoup gwoup;
	stwuct epf_ntb_epc *epc[2];
};

#define to_epf_ntb(epf_gwoup) containew_of((epf_gwoup), stwuct epf_ntb, gwoup)

stwuct epf_ntb_epc {
	u8 func_no;
	u8 vfunc_no;
	boow winkup;
	boow is_msix;
	int msix_baw;
	u32 spad_size;
	stwuct pci_epc *epc;
	stwuct epf_ntb *epf_ntb;
	void __iomem *mw_addw[6];
	size_t msix_tabwe_offset;
	stwuct epf_ntb_ctww *weg;
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno epf_ntb_baw[6];
	stwuct dewayed_wowk cmd_handwew;
	enum pci_epc_intewface_type type;
	const stwuct pci_epc_featuwes *epc_featuwes;
};

stwuct epf_ntb_ctww {
	u32	command;
	u32	awgument;
	u16	command_status;
	u16	wink_status;
	u32	topowogy;
	u64	addw;
	u64	size;
	u32	num_mws;
	u32	mw1_offset;
	u32	spad_offset;
	u32	spad_count;
	u32	db_entwy_size;
	u32	db_data[MAX_DB_COUNT];
	u32	db_offset[MAX_DB_COUNT];
} __packed;

static stwuct pci_epf_headew epf_ntb_headew = {
	.vendowid	= PCI_ANY_ID,
	.deviceid	= PCI_ANY_ID,
	.basecwass_code	= PCI_BASE_CWASS_MEMOWY,
	.intewwupt_pin	= PCI_INTEWWUPT_INTA,
};

/**
 * epf_ntb_wink_up() - Waise wink_up intewwupt to both the hosts
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @wink_up: twue ow fawse indicating Wink is UP ow Down
 *
 * Once NTB function in HOST1 and the NTB function in HOST2 invoke
 * ntb_wink_enabwe(), this NTB function dwivew wiww twiggew a wink event to
 * the NTB cwient in both the hosts.
 */
static int epf_ntb_wink_up(stwuct epf_ntb *ntb, boow wink_up)
{
	enum pci_epc_intewface_type type;
	stwuct epf_ntb_epc *ntb_epc;
	stwuct epf_ntb_ctww *ctww;
	unsigned int iwq_type;
	stwuct pci_epc *epc;
	u8 func_no, vfunc_no;
	boow is_msix;
	int wet;

	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++) {
		ntb_epc = ntb->epc[type];
		epc = ntb_epc->epc;
		func_no = ntb_epc->func_no;
		vfunc_no = ntb_epc->vfunc_no;
		is_msix = ntb_epc->is_msix;
		ctww = ntb_epc->weg;
		if (wink_up)
			ctww->wink_status |= WINK_STATUS_UP;
		ewse
			ctww->wink_status &= ~WINK_STATUS_UP;
		iwq_type = is_msix ? PCI_IWQ_MSIX : PCI_IWQ_MSI;
		wet = pci_epc_waise_iwq(epc, func_no, vfunc_no, iwq_type, 1);
		if (wet) {
			dev_eww(&epc->dev,
				"%s intf: Faiwed to waise Wink Up IWQ\n",
				pci_epc_intewface_stwing(type));
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * epf_ntb_configuwe_mw() - Configuwe the Outbound Addwess Space fow one host
 *   to access the memowy window of othew host
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 * @mw: Index of the memowy window (eithew 0, 1, 2 ow 3)
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAW0      |    |     |   Doowbeww 1   +-----------> MSI|X ADDWESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAW1      |    |     |   Doowbeww 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAW2      |          |   Doowbeww 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDWESS 2 |
 * |       BAW3      |    |     |   Doowbeww 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAW4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDWESS 3||
 * |       BAW5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTWOWWEW 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDWESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTWOWWEW 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 * This function pewfowms stage (B) in the above diagwam (see MW1) i.e., map OB
 * addwess space of memowy window to PCI addwess space.
 *
 * This opewation wequiwes 3 pawametews
 *  1) Addwess in the outbound addwess space
 *  2) Addwess in the PCI Addwess space
 *  3) Size of the addwess wegion to be mapped
 *
 * The addwess in the outbound addwess space (fow MW1, MW2, MW3 and MW4) is
 * stowed in epf_baw cowwesponding to BAW_DB_MW1 fow MW1 and BAW_MW2, BAW_MW3
 * BAW_MW4 fow west of the BAWs of epf_ntb_epc that is connected to HOST1. This
 * is popuwated in epf_ntb_awwoc_peew_mem() in this dwivew.
 *
 * The addwess and size of the PCI addwess wegion that has to be mapped wouwd
 * be pwovided by HOST2 in ctww->addw and ctww->size of epf_ntb_epc that is
 * connected to HOST2.
 *
 * Pwease note Memowy window1 (MW1) and Doowbeww wegistews togethew wiww be
 * mapped to a singwe BAW (BAW2) above fow 32-bit BAWs. The exact BAW that's
 * used fow Memowy window (MW) can be obtained fwom epf_ntb_baw[BAW_DB_MW1],
 * epf_ntb_baw[BAW_MW2], epf_ntb_baw[BAW_MW2], epf_ntb_baw[BAW_MW2].
 */
static int epf_ntb_configuwe_mw(stwuct epf_ntb *ntb,
				enum pci_epc_intewface_type type, u32 mw)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *peew_epf_baw;
	enum pci_bawno peew_bawno;
	stwuct epf_ntb_ctww *ctww;
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	u64 addw, size;
	int wet = 0;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[mw + NTB_MW_OFFSET];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];

	phys_addw = peew_epf_baw->phys_addw;
	ctww = ntb_epc->weg;
	addw = ctww->addw;
	size = ctww->size;
	if (mw + NTB_MW_OFFSET == BAW_DB_MW1)
		phys_addw += ctww->mw1_offset;

	if (size > ntb->mws_size[mw]) {
		dev_eww(&epc->dev,
			"%s intf: MW: %d Weq Sz:%wwxx > Suppowted Sz:%wwx\n",
			pci_epc_intewface_stwing(type), mw, size,
			ntb->mws_size[mw]);
		wet = -EINVAW;
		goto eww_invawid_size;
	}

	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	wet = pci_epc_map_addw(epc, func_no, vfunc_no, phys_addw, addw, size);
	if (wet)
		dev_eww(&epc->dev,
			"%s intf: Faiwed to map memowy window %d addwess\n",
			pci_epc_intewface_stwing(type), mw);

eww_invawid_size:

	wetuwn wet;
}

/**
 * epf_ntb_teawdown_mw() - Teawdown the configuwed OB ATU
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 * @mw: Index of the memowy window (eithew 0, 1, 2 ow 3)
 *
 * Teawdown the configuwed OB ATU configuwed in epf_ntb_configuwe_mw() using
 * pci_epc_unmap_addw()
 */
static void epf_ntb_teawdown_mw(stwuct epf_ntb *ntb,
				enum pci_epc_intewface_type type, u32 mw)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *peew_epf_baw;
	enum pci_bawno peew_bawno;
	stwuct epf_ntb_ctww *ctww;
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[mw + NTB_MW_OFFSET];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];

	phys_addw = peew_epf_baw->phys_addw;
	ctww = ntb_epc->weg;
	if (mw + NTB_MW_OFFSET == BAW_DB_MW1)
		phys_addw += ctww->mw1_offset;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	pci_epc_unmap_addw(epc, func_no, vfunc_no, phys_addw);
}

/**
 * epf_ntb_configuwe_msi() - Map OB addwess space to MSI addwess
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 * @db_count: Numbew of doowbeww intewwupts to map
 *
 *+-----------------+    +----->+----------------+-----------+-----------------+
 *|       BAW0      |    |      |   Doowbeww 1   +---+------->   MSI ADDWESS   |
 *+-----------------+    |      +----------------+   |       +-----------------+
 *|       BAW1      |    |      |   Doowbeww 2   +---+       |                 |
 *+-----------------+----+      +----------------+   |       |                 |
 *|       BAW2      |           |   Doowbeww 3   +---+       |                 |
 *+-----------------+----+      +----------------+   |       |                 |
 *|       BAW3      |    |      |   Doowbeww 4   +---+       |                 |
 *+-----------------+    |      |----------------+           |                 |
 *|       BAW4      |    |      |                |           |                 |
 *+-----------------+    |      |      MW1       |           |                 |
 *|       BAW5      |    |      |                |           |                 |
 *+-----------------+    +----->-----------------+           |                 |
 *  EP CONTWOWWEW 1             |                |           |                 |
 *                              |                |           |                 |
 *                              +----------------+           +-----------------+
 *                     (A)       EP CONTWOWWEW 2             |                 |
 *                                 (OB SPACE)                |                 |
 *                                                           |      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 *
 * This function pewfowms stage (B) in the above diagwam (see Doowbeww 1,
 * Doowbeww 2, Doowbeww 3, Doowbeww 4) i.e map OB addwess space cowwesponding to
 * doowbeww to MSI addwess in PCI addwess space.
 *
 * This opewation wequiwes 3 pawametews
 *  1) Addwess wesewved fow doowbeww in the outbound addwess space
 *  2) MSI-X addwess in the PCIe Addwess space
 *  3) Numbew of MSI-X intewwupts that has to be configuwed
 *
 * The addwess in the outbound addwess space (fow the Doowbeww) is stowed in
 * epf_baw cowwesponding to BAW_DB_MW1 of epf_ntb_epc that is connected to
 * HOST1. This is popuwated in epf_ntb_awwoc_peew_mem() in this dwivew awong
 * with addwess fow MW1.
 *
 * pci_epc_map_msi_iwq() takes the MSI addwess fwom MSI capabiwity wegistew
 * and maps the OB addwess (obtained in epf_ntb_awwoc_peew_mem()) to the MSI
 * addwess.
 *
 * epf_ntb_configuwe_msi() awso stowes the MSI data to waise each intewwupt
 * in db_data of the peew's contwow wegion. This hewps the peew to waise
 * doowbeww of the othew host by wwiting db_data to the BAW cowwesponding to
 * BAW_DB_MW1.
 */
static int epf_ntb_configuwe_msi(stwuct epf_ntb *ntb,
				 enum pci_epc_intewface_type type, u16 db_count)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	u32 db_entwy_size, db_data, db_offset;
	stwuct pci_epf_baw *peew_epf_baw;
	stwuct epf_ntb_ctww *peew_ctww;
	enum pci_bawno peew_bawno;
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	int wet, i;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[BAW_DB_MW1];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];
	peew_ctww = peew_ntb_epc->weg;
	db_entwy_size = peew_ctww->db_entwy_size;

	phys_addw = peew_epf_baw->phys_addw;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	wet = pci_epc_map_msi_iwq(epc, func_no, vfunc_no, phys_addw, db_count,
				  db_entwy_size, &db_data, &db_offset);
	if (wet) {
		dev_eww(&epc->dev, "%s intf: Faiwed to map MSI IWQ\n",
			pci_epc_intewface_stwing(type));
		wetuwn wet;
	}

	fow (i = 0; i < db_count; i++) {
		peew_ctww->db_data[i] = db_data | i;
		peew_ctww->db_offset[i] = db_offset;
	}

	wetuwn 0;
}

/**
 * epf_ntb_configuwe_msix() - Map OB addwess space to MSI-X addwess
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 * @db_count: Numbew of doowbeww intewwupts to map
 *
 *+-----------------+    +----->+----------------+-----------+-----------------+
 *|       BAW0      |    |      |   Doowbeww 1   +-----------> MSI-X ADDWESS 1 |
 *+-----------------+    |      +----------------+           +-----------------+
 *|       BAW1      |    |      |   Doowbeww 2   +---------+ |                 |
 *+-----------------+----+      +----------------+         | |                 |
 *|       BAW2      |           |   Doowbeww 3   +-------+ | +-----------------+
 *+-----------------+----+      +----------------+       | +-> MSI-X ADDWESS 2 |
 *|       BAW3      |    |      |   Doowbeww 4   +-----+ |   +-----------------+
 *+-----------------+    |      |----------------+     | |   |                 |
 *|       BAW4      |    |      |                |     | |   +-----------------+
 *+-----------------+    |      |      MW1       +     | +-->+ MSI-X ADDWESS 3||
 *|       BAW5      |    |      |                |     |     +-----------------+
 *+-----------------+    +----->-----------------+     |     |                 |
 *  EP CONTWOWWEW 1             |                |     |     +-----------------+
 *                              |                |     +---->+ MSI-X ADDWESS 4 |
 *                              +----------------+           +-----------------+
 *                     (A)       EP CONTWOWWEW 2             |                 |
 *                                 (OB SPACE)                |                 |
 *                                                           |      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 * This function pewfowms stage (B) in the above diagwam (see Doowbeww 1,
 * Doowbeww 2, Doowbeww 3, Doowbeww 4) i.e map OB addwess space cowwesponding to
 * doowbeww to MSI-X addwess in PCI addwess space.
 *
 * This opewation wequiwes 3 pawametews
 *  1) Addwess wesewved fow doowbeww in the outbound addwess space
 *  2) MSI-X addwess in the PCIe Addwess space
 *  3) Numbew of MSI-X intewwupts that has to be configuwed
 *
 * The addwess in the outbound addwess space (fow the Doowbeww) is stowed in
 * epf_baw cowwesponding to BAW_DB_MW1 of epf_ntb_epc that is connected to
 * HOST1. This is popuwated in epf_ntb_awwoc_peew_mem() in this dwivew awong
 * with addwess fow MW1.
 *
 * The MSI-X addwess is in the MSI-X tabwe of EP CONTWOWWEW 2 and
 * the count of doowbeww is in ctww->awgument of epf_ntb_epc that is connected
 * to HOST2. MSI-X tabwe is stowed memowy mapped to ntb_epc->msix_baw and the
 * offset is in ntb_epc->msix_tabwe_offset. Fwom this epf_ntb_configuwe_msix()
 * gets the MSI-X addwess and data.
 *
 * epf_ntb_configuwe_msix() awso stowes the MSI-X data to waise each intewwupt
 * in db_data of the peew's contwow wegion. This hewps the peew to waise
 * doowbeww of the othew host by wwiting db_data to the BAW cowwesponding to
 * BAW_DB_MW1.
 */
static int epf_ntb_configuwe_msix(stwuct epf_ntb *ntb,
				  enum pci_epc_intewface_type type,
				  u16 db_count)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *peew_epf_baw, *epf_baw;
	stwuct pci_epf_msix_tbw *msix_tbw;
	stwuct epf_ntb_ctww *peew_ctww;
	u32 db_entwy_size, msg_data;
	enum pci_bawno peew_bawno;
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	size_t awign;
	u64 msg_addw;
	int wet, i;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	epf_baw = &ntb_epc->epf_baw[ntb_epc->msix_baw];
	msix_tbw = epf_baw->addw + ntb_epc->msix_tabwe_offset;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[BAW_DB_MW1];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];
	phys_addw = peew_epf_baw->phys_addw;
	peew_ctww = peew_ntb_epc->weg;
	epc_featuwes = ntb_epc->epc_featuwes;
	awign = epc_featuwes->awign;

	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	db_entwy_size = peew_ctww->db_entwy_size;

	fow (i = 0; i < db_count; i++) {
		msg_addw = AWIGN_DOWN(msix_tbw[i].msg_addw, awign);
		msg_data = msix_tbw[i].msg_data;
		wet = pci_epc_map_addw(epc, func_no, vfunc_no, phys_addw, msg_addw,
				       db_entwy_size);
		if (wet) {
			dev_eww(&epc->dev,
				"%s intf: Faiwed to configuwe MSI-X IWQ\n",
				pci_epc_intewface_stwing(type));
			wetuwn wet;
		}
		phys_addw = phys_addw + db_entwy_size;
		peew_ctww->db_data[i] = msg_data;
		peew_ctww->db_offset[i] = msix_tbw[i].msg_addw & (awign - 1);
	}
	ntb_epc->is_msix = twue;

	wetuwn 0;
}

/**
 * epf_ntb_configuwe_db() - Configuwe the Outbound Addwess Space fow one host
 *   to wing the doowbeww of othew host
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 * @db_count: Count of the numbew of doowbewws that has to be configuwed
 * @msix: Indicates whethew MSI-X ow MSI shouwd be used
 *
 * Invokes epf_ntb_configuwe_msix() ow epf_ntb_configuwe_msi() wequiwed fow
 * one HOST to wing the doowbeww of othew HOST.
 */
static int epf_ntb_configuwe_db(stwuct epf_ntb *ntb,
				enum pci_epc_intewface_type type,
				u16 db_count, boow msix)
{
	stwuct epf_ntb_epc *ntb_epc;
	stwuct pci_epc *epc;
	int wet;

	if (db_count > MAX_DB_COUNT)
		wetuwn -EINVAW;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	if (msix)
		wet = epf_ntb_configuwe_msix(ntb, type, db_count);
	ewse
		wet = epf_ntb_configuwe_msi(ntb, type, db_count);

	if (wet)
		dev_eww(&epc->dev, "%s intf: Faiwed to configuwe DB\n",
			pci_epc_intewface_stwing(type));

	wetuwn wet;
}

/**
 * epf_ntb_teawdown_db() - Unmap addwess in OB addwess space to MSI/MSI-X
 *   addwess
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Invoke pci_epc_unmap_addw() to unmap OB addwess to MSI/MSI-X addwess.
 */
static void
epf_ntb_teawdown_db(stwuct epf_ntb *ntb, enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *peew_epf_baw;
	enum pci_bawno peew_bawno;
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;

	ntb_epc = ntb->epc[type];
	epc = ntb_epc->epc;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[BAW_DB_MW1];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];
	phys_addw = peew_epf_baw->phys_addw;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	pci_epc_unmap_addw(epc, func_no, vfunc_no, phys_addw);
}

/**
 * epf_ntb_cmd_handwew() - Handwe commands pwovided by the NTB Host
 * @wowk: wowk_stwuct fow the two epf_ntb_epc (PWIMAWY and SECONDAWY)
 *
 * Wowkqueue function that gets invoked fow the two epf_ntb_epc
 * pewiodicawwy (once evewy 5ms) to see if it has weceived any commands
 * fwom NTB host. The host can send commands to configuwe doowbeww ow
 * configuwe memowy window ow to update wink status.
 */
static void epf_ntb_cmd_handwew(stwuct wowk_stwuct *wowk)
{
	enum pci_epc_intewface_type type;
	stwuct epf_ntb_epc *ntb_epc;
	stwuct epf_ntb_ctww *ctww;
	u32 command, awgument;
	stwuct epf_ntb *ntb;
	stwuct device *dev;
	u16 db_count;
	boow is_msix;
	int wet;

	ntb_epc = containew_of(wowk, stwuct epf_ntb_epc, cmd_handwew.wowk);
	ctww = ntb_epc->weg;
	command = ctww->command;
	if (!command)
		goto weset_handwew;
	awgument = ctww->awgument;

	ctww->command = 0;
	ctww->awgument = 0;

	ctww = ntb_epc->weg;
	type = ntb_epc->type;
	ntb = ntb_epc->epf_ntb;
	dev = &ntb->epf->dev;

	switch (command) {
	case COMMAND_CONFIGUWE_DOOWBEWW:
		db_count = awgument & DB_COUNT_MASK;
		is_msix = awgument & MSIX_ENABWE;
		wet = epf_ntb_configuwe_db(ntb, type, db_count, is_msix);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_TEAWDOWN_DOOWBEWW:
		epf_ntb_teawdown_db(ntb, type);
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_CONFIGUWE_MW:
		wet = epf_ntb_configuwe_mw(ntb, type, awgument);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_TEAWDOWN_MW:
		epf_ntb_teawdown_mw(ntb, type, awgument);
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_WINK_UP:
		ntb_epc->winkup = twue;
		if (ntb->epc[PWIMAWY_INTEWFACE]->winkup &&
		    ntb->epc[SECONDAWY_INTEWFACE]->winkup) {
			wet = epf_ntb_wink_up(ntb, twue);
			if (wet < 0)
				ctww->command_status = COMMAND_STATUS_EWWOW;
			ewse
				ctww->command_status = COMMAND_STATUS_OK;
			goto weset_handwew;
		}
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_WINK_DOWN:
		ntb_epc->winkup = fawse;
		wet = epf_ntb_wink_up(ntb, fawse);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	defauwt:
		dev_eww(dev, "%s intf UNKNOWN command: %d\n",
			pci_epc_intewface_stwing(type), command);
		bweak;
	}

weset_handwew:
	queue_dewayed_wowk(kpcintb_wowkqueue, &ntb_epc->cmd_handwew,
			   msecs_to_jiffies(5));
}

/**
 * epf_ntb_peew_spad_baw_cweaw() - Cweaw Peew Scwatchpad BAW
 * @ntb_epc: EPC associated with one of the HOST which howds peew's outbound
 *	     addwess.
 *
 *+-----------------+------->+------------------+        +-----------------+
 *|       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 *+-----------------+----+   +------------------+<-------+-----------------+
 *|       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 *+-----------------+    +-->+------------------+<-------+-----------------+
 *|       BAW2      |            Wocaw Memowy            |       BAW2      |
 *+-----------------+                                    +-----------------+
 *|       BAW3      |                                    |       BAW3      |
 *+-----------------+                                    +-----------------+
 *|       BAW4      |                                    |       BAW4      |
 *+-----------------+                                    +-----------------+
 *|       BAW5      |                                    |       BAW5      |
 *+-----------------+                                    +-----------------+
 *  EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Cweaw BAW1 of EP CONTWOWWEW 2 which contains the HOST2's peew scwatchpad
 * wegion. Whiwe BAW1 is the defauwt peew scwatchpad BAW, an NTB couwd have
 * othew BAWs fow peew scwatchpad (because of 64-bit BAWs ow wesewved BAWs).
 * This function can get the exact BAW used fow peew scwatchpad fwom
 * epf_ntb_baw[BAW_PEEW_SPAD].
 *
 * Since HOST2's peew scwatchpad is awso HOST1's sewf scwatchpad, this function
 * gets the addwess of peew scwatchpad fwom
 * peew_ntb_epc->epf_ntb_baw[BAW_CONFIG].
 */
static void epf_ntb_peew_spad_baw_cweaw(stwuct epf_ntb_epc *ntb_epc)
{
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	bawno = ntb_epc->epf_ntb_baw[BAW_PEEW_SPAD];
	epf_baw = &ntb_epc->epf_baw[bawno];
	pci_epc_cweaw_baw(epc, func_no, vfunc_no, epf_baw);
}

/**
 * epf_ntb_peew_spad_baw_set() - Set peew scwatchpad BAW
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 *+-----------------+------->+------------------+        +-----------------+
 *|       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 *+-----------------+----+   +------------------+<-------+-----------------+
 *|       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 *+-----------------+    +-->+------------------+<-------+-----------------+
 *|       BAW2      |            Wocaw Memowy            |       BAW2      |
 *+-----------------+                                    +-----------------+
 *|       BAW3      |                                    |       BAW3      |
 *+-----------------+                                    +-----------------+
 *|       BAW4      |                                    |       BAW4      |
 *+-----------------+                                    +-----------------+
 *|       BAW5      |                                    |       BAW5      |
 *+-----------------+                                    +-----------------+
 *  EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Set BAW1 of EP CONTWOWWEW 2 which contains the HOST2's peew scwatchpad
 * wegion. Whiwe BAW1 is the defauwt peew scwatchpad BAW, an NTB couwd have
 * othew BAWs fow peew scwatchpad (because of 64-bit BAWs ow wesewved BAWs).
 * This function can get the exact BAW used fow peew scwatchpad fwom
 * epf_ntb_baw[BAW_PEEW_SPAD].
 *
 * Since HOST2's peew scwatchpad is awso HOST1's sewf scwatchpad, this function
 * gets the addwess of peew scwatchpad fwom
 * peew_ntb_epc->epf_ntb_baw[BAW_CONFIG].
 */
static int epf_ntb_peew_spad_baw_set(stwuct epf_ntb *ntb,
				     enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *peew_epf_baw, *epf_baw;
	enum pci_bawno peew_bawno, bawno;
	u32 peew_spad_offset;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	stwuct device *dev;
	int wet;

	dev = &ntb->epf->dev;

	peew_ntb_epc = ntb->epc[!type];
	peew_bawno = peew_ntb_epc->epf_ntb_baw[BAW_CONFIG];
	peew_epf_baw = &peew_ntb_epc->epf_baw[peew_bawno];

	ntb_epc = ntb->epc[type];
	bawno = ntb_epc->epf_ntb_baw[BAW_PEEW_SPAD];
	epf_baw = &ntb_epc->epf_baw[bawno];
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	epc = ntb_epc->epc;

	peew_spad_offset = peew_ntb_epc->weg->spad_offset;
	epf_baw->phys_addw = peew_epf_baw->phys_addw + peew_spad_offset;
	epf_baw->size = peew_ntb_epc->spad_size;
	epf_baw->bawno = bawno;
	epf_baw->fwags = PCI_BASE_ADDWESS_MEM_TYPE_32;

	wet = pci_epc_set_baw(epc, func_no, vfunc_no, epf_baw);
	if (wet) {
		dev_eww(dev, "%s intf: peew SPAD BAW set faiwed\n",
			pci_epc_intewface_stwing(type));
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * epf_ntb_config_sspad_baw_cweaw() - Cweaw Config + Sewf scwatchpad BAW
 * @ntb_epc: EPC associated with one of the HOST which howds peew's outbound
 *	     addwess.
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAW2      |            Wocaw Memowy            |       BAW2      |
 * +-----------------+                                    +-----------------+
 * |       BAW3      |                                    |       BAW3      |
 * +-----------------+                                    +-----------------+
 * |       BAW4      |                                    |       BAW4      |
 * +-----------------+                                    +-----------------+
 * |       BAW5      |                                    |       BAW5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Cweaw BAW0 of EP CONTWOWWEW 1 which contains the HOST1's config and
 * sewf scwatchpad wegion (wemoves inbound ATU configuwation). Whiwe BAW0 is
 * the defauwt sewf scwatchpad BAW, an NTB couwd have othew BAWs fow sewf
 * scwatchpad (because of wesewved BAWs). This function can get the exact BAW
 * used fow sewf scwatchpad fwom epf_ntb_baw[BAW_CONFIG].
 *
 * Pwease note the sewf scwatchpad wegion and config wegion is combined to
 * a singwe wegion and mapped using the same BAW. Awso note HOST2's peew
 * scwatchpad is HOST1's sewf scwatchpad.
 */
static void epf_ntb_config_sspad_baw_cweaw(stwuct epf_ntb_epc *ntb_epc)
{
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	bawno = ntb_epc->epf_ntb_baw[BAW_CONFIG];
	epf_baw = &ntb_epc->epf_baw[bawno];
	pci_epc_cweaw_baw(epc, func_no, vfunc_no, epf_baw);
}

/**
 * epf_ntb_config_sspad_baw_set() - Set Config + Sewf scwatchpad BAW
 * @ntb_epc: EPC associated with one of the HOST which howds peew's outbound
 *	     addwess.
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAW2      |            Wocaw Memowy            |       BAW2      |
 * +-----------------+                                    +-----------------+
 * |       BAW3      |                                    |       BAW3      |
 * +-----------------+                                    +-----------------+
 * |       BAW4      |                                    |       BAW4      |
 * +-----------------+                                    +-----------------+
 * |       BAW5      |                                    |       BAW5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Map BAW0 of EP CONTWOWWEW 1 which contains the HOST1's config and
 * sewf scwatchpad wegion. Whiwe BAW0 is the defauwt sewf scwatchpad BAW, an
 * NTB couwd have othew BAWs fow sewf scwatchpad (because of wesewved BAWs).
 * This function can get the exact BAW used fow sewf scwatchpad fwom
 * epf_ntb_baw[BAW_CONFIG].
 *
 * Pwease note the sewf scwatchpad wegion and config wegion is combined to
 * a singwe wegion and mapped using the same BAW. Awso note HOST2's peew
 * scwatchpad is HOST1's sewf scwatchpad.
 */
static int epf_ntb_config_sspad_baw_set(stwuct epf_ntb_epc *ntb_epc)
{
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct epf_ntb *ntb;
	stwuct pci_epc *epc;
	stwuct device *dev;
	int wet;

	ntb = ntb_epc->epf_ntb;
	dev = &ntb->epf->dev;

	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	bawno = ntb_epc->epf_ntb_baw[BAW_CONFIG];
	epf_baw = &ntb_epc->epf_baw[bawno];

	wet = pci_epc_set_baw(epc, func_no, vfunc_no, epf_baw);
	if (wet) {
		dev_eww(dev, "%s inft: Config/Status/SPAD BAW set faiwed\n",
			pci_epc_intewface_stwing(ntb_epc->type));
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * epf_ntb_config_spad_baw_fwee() - Fwee the physicaw memowy associated with
 *   config + scwatchpad wegion
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAW2      |            Wocaw Memowy            |       BAW2      |
 * +-----------------+                                    +-----------------+
 * |       BAW3      |                                    |       BAW3      |
 * +-----------------+                                    +-----------------+
 * |       BAW4      |                                    |       BAW4      |
 * +-----------------+                                    +-----------------+
 * |       BAW5      |                                    |       BAW5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Fwee the Wocaw Memowy mentioned in the above diagwam. Aftew invoking this
 * function, any of config + sewf scwatchpad wegion of HOST1 ow peew scwatchpad
 * wegion of HOST2 shouwd not be accessed.
 */
static void epf_ntb_config_spad_baw_fwee(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;
	stwuct epf_ntb_epc *ntb_epc;
	enum pci_bawno bawno;
	stwuct pci_epf *epf;

	epf = ntb->epf;
	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++) {
		ntb_epc = ntb->epc[type];
		bawno = ntb_epc->epf_ntb_baw[BAW_CONFIG];
		if (ntb_epc->weg)
			pci_epf_fwee_space(epf, ntb_epc->weg, bawno, type);
	}
}

/**
 * epf_ntb_config_spad_baw_awwoc() - Awwocate memowy fow config + scwatchpad
 *   wegion
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * +-----------------+------->+------------------+        +-----------------+
 * |       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 * +-----------------+----+   +------------------+<-------+-----------------+
 * |       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 * +-----------------+    +-->+------------------+<-------+-----------------+
 * |       BAW2      |            Wocaw Memowy            |       BAW2      |
 * +-----------------+                                    +-----------------+
 * |       BAW3      |                                    |       BAW3      |
 * +-----------------+                                    +-----------------+
 * |       BAW4      |                                    |       BAW4      |
 * +-----------------+                                    +-----------------+
 * |       BAW5      |                                    |       BAW5      |
 * +-----------------+                                    +-----------------+
 *   EP CONTWOWWEW 1                                        EP CONTWOWWEW 2
 *
 * Awwocate the Wocaw Memowy mentioned in the above diagwam. The size of
 * CONFIG WEGION is sizeof(stwuct epf_ntb_ctww) and size of SCWATCHPAD WEGION
 * is obtained fwom "spad-count" configfs entwy.
 *
 * The size of both config wegion and scwatchpad wegion has to be awigned,
 * since the scwatchpad wegion wiww awso be mapped as PEEW SCWATCHPAD of
 * othew host using a sepawate BAW.
 */
static int epf_ntb_config_spad_baw_awwoc(stwuct epf_ntb *ntb,
					 enum pci_epc_intewface_type type)
{
	const stwuct pci_epc_featuwes *peew_epc_featuwes, *epc_featuwes;
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	size_t msix_tabwe_size, pba_size, awign;
	enum pci_bawno peew_bawno, bawno;
	stwuct epf_ntb_ctww *ctww;
	u32 spad_size, ctww_size;
	u64 size, peew_size;
	stwuct pci_epf *epf;
	stwuct device *dev;
	boow msix_capabwe;
	u32 spad_count;
	void *base;

	epf = ntb->epf;
	dev = &epf->dev;
	ntb_epc = ntb->epc[type];

	epc_featuwes = ntb_epc->epc_featuwes;
	bawno = ntb_epc->epf_ntb_baw[BAW_CONFIG];
	size = epc_featuwes->baw_fixed_size[bawno];
	awign = epc_featuwes->awign;

	peew_ntb_epc = ntb->epc[!type];
	peew_epc_featuwes = peew_ntb_epc->epc_featuwes;
	peew_bawno = ntb_epc->epf_ntb_baw[BAW_PEEW_SPAD];
	peew_size = peew_epc_featuwes->baw_fixed_size[peew_bawno];

	/* Check if epc_featuwes is popuwated incowwectwy */
	if ((!IS_AWIGNED(size, awign)))
		wetuwn -EINVAW;

	spad_count = ntb->spad_count;

	ctww_size = sizeof(stwuct epf_ntb_ctww);
	spad_size = spad_count * 4;

	msix_capabwe = epc_featuwes->msix_capabwe;
	if (msix_capabwe) {
		msix_tabwe_size = PCI_MSIX_ENTWY_SIZE * ntb->db_count;
		ctww_size = AWIGN(ctww_size, 8);
		ntb_epc->msix_tabwe_offset = ctww_size;
		ntb_epc->msix_baw = bawno;
		/* Awign to QWOWD ow 8 Bytes */
		pba_size = AWIGN(DIV_WOUND_UP(ntb->db_count, 8), 8);
		ctww_size = ctww_size + msix_tabwe_size + pba_size;
	}

	if (!awign) {
		ctww_size = woundup_pow_of_two(ctww_size);
		spad_size = woundup_pow_of_two(spad_size);
	} ewse {
		ctww_size = AWIGN(ctww_size, awign);
		spad_size = AWIGN(spad_size, awign);
	}

	if (peew_size) {
		if (peew_size < spad_size)
			spad_count = peew_size / 4;
		spad_size = peew_size;
	}

	/*
	 * In owdew to make suwe SPAD offset is awigned to its size,
	 * expand contwow wegion size to the size of SPAD if SPAD size
	 * is gweatew than contwow wegion size.
	 */
	if (spad_size > ctww_size)
		ctww_size = spad_size;

	if (!size)
		size = ctww_size + spad_size;
	ewse if (size < ctww_size + spad_size)
		wetuwn -EINVAW;

	base = pci_epf_awwoc_space(epf, size, bawno, awign, type);
	if (!base) {
		dev_eww(dev, "%s intf: Config/Status/SPAD awwoc wegion faiw\n",
			pci_epc_intewface_stwing(type));
		wetuwn -ENOMEM;
	}

	ntb_epc->weg = base;

	ctww = ntb_epc->weg;
	ctww->spad_offset = ctww_size;
	ctww->spad_count = spad_count;
	ctww->num_mws = ntb->num_mws;
	ctww->db_entwy_size = awign ? awign : 4;
	ntb_epc->spad_size = spad_size;

	wetuwn 0;
}

/**
 * epf_ntb_config_spad_baw_awwoc_intewface() - Awwocate memowy fow config +
 *   scwatchpad wegion fow each of PWIMAWY and SECONDAWY intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Wwappew fow epf_ntb_config_spad_baw_awwoc() which awwocates memowy fow
 * config + scwatchpad wegion fow a specific intewface
 */
static int epf_ntb_config_spad_baw_awwoc_intewface(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;
	stwuct device *dev;
	int wet;

	dev = &ntb->epf->dev;

	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++) {
		wet = epf_ntb_config_spad_baw_awwoc(ntb, type);
		if (wet) {
			dev_eww(dev, "%s intf: Config/SPAD BAW awwoc faiwed\n",
				pci_epc_intewface_stwing(type));
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * epf_ntb_fwee_peew_mem() - Fwee memowy awwocated in peews outbound addwess
 *   space
 * @ntb_epc: EPC associated with one of the HOST which howds peews outbound
 *   addwess wegions
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAW0      |    |     |   Doowbeww 1   +-----------> MSI|X ADDWESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAW1      |    |     |   Doowbeww 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAW2      |          |   Doowbeww 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDWESS 2 |
 * |       BAW3      |    |     |   Doowbeww 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAW4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDWESS 3||
 * |       BAW5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTWOWWEW 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDWESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTWOWWEW 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 * Fwee memowy awwocated in EP CONTWOWWEW 2 (OB SPACE) in the above diagwam.
 * It'ww fwee Doowbeww 1, Doowbeww 2, Doowbeww 3, Doowbeww 4, MW1 (and MW2, MW3,
 * MW4).
 */
static void epf_ntb_fwee_peew_mem(stwuct epf_ntb_epc *ntb_epc)
{
	stwuct pci_epf_baw *epf_baw;
	void __iomem *mw_addw;
	phys_addw_t phys_addw;
	enum epf_ntb_baw baw;
	enum pci_bawno bawno;
	stwuct pci_epc *epc;
	size_t size;

	epc = ntb_epc->epc;

	fow (baw = BAW_DB_MW1; baw < BAW_MW4; baw++) {
		bawno = ntb_epc->epf_ntb_baw[baw];
		mw_addw = ntb_epc->mw_addw[bawno];
		epf_baw = &ntb_epc->epf_baw[bawno];
		phys_addw = epf_baw->phys_addw;
		size = epf_baw->size;
		if (mw_addw) {
			pci_epc_mem_fwee_addw(epc, phys_addw, mw_addw, size);
			ntb_epc->mw_addw[bawno] = NUWW;
		}
	}
}

/**
 * epf_ntb_db_mw_baw_cweaw() - Cweaw doowbeww and memowy BAW
 * @ntb_epc: EPC associated with one of the HOST which howds peew's outbound
 *   addwess
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAW0      |    |     |   Doowbeww 1   +-----------> MSI|X ADDWESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAW1      |    |     |   Doowbeww 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAW2      |          |   Doowbeww 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDWESS 2 |
 * |       BAW3      |    |     |   Doowbeww 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAW4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDWESS 3||
 * |       BAW5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTWOWWEW 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDWESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTWOWWEW 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 * Cweaw doowbeww and memowy BAWs (wemove inbound ATU configuwation). In the above
 * diagwam it cweaws BAW2 TO BAW5 of EP CONTWOWWEW 1 (Doowbeww BAW, MW1 BAW, MW2
 * BAW, MW3 BAW and MW4 BAW).
 */
static void epf_ntb_db_mw_baw_cweaw(stwuct epf_ntb_epc *ntb_epc)
{
	stwuct pci_epf_baw *epf_baw;
	enum epf_ntb_baw baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;

	epc = ntb_epc->epc;

	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	fow (baw = BAW_DB_MW1; baw < BAW_MW4; baw++) {
		bawno = ntb_epc->epf_ntb_baw[baw];
		epf_baw = &ntb_epc->epf_baw[bawno];
		pci_epc_cweaw_baw(epc, func_no, vfunc_no, epf_baw);
	}
}

/**
 * epf_ntb_db_mw_baw_cweanup() - Cweaw doowbeww/memowy BAW and fwee memowy
 *   awwocated in peews outbound addwess space
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Wwappew fow epf_ntb_db_mw_baw_cweaw() to cweaw HOST1's BAW and
 * epf_ntb_fwee_peew_mem() which fwees up HOST2 outbound memowy.
 */
static void epf_ntb_db_mw_baw_cweanup(stwuct epf_ntb *ntb,
				      enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;

	ntb_epc = ntb->epc[type];
	peew_ntb_epc = ntb->epc[!type];

	epf_ntb_db_mw_baw_cweaw(ntb_epc);
	epf_ntb_fwee_peew_mem(peew_ntb_epc);
}

/**
 * epf_ntb_configuwe_intewwupt() - Configuwe MSI/MSI-X capabiwity
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Configuwe MSI/MSI-X capabiwity fow each intewface with numbew of
 * intewwupts equaw to "db_count" configfs entwy.
 */
static int epf_ntb_configuwe_intewwupt(stwuct epf_ntb *ntb,
				       enum pci_epc_intewface_type type)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	boow msix_capabwe, msi_capabwe;
	stwuct epf_ntb_epc *ntb_epc;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	stwuct device *dev;
	u32 db_count;
	int wet;

	ntb_epc = ntb->epc[type];
	dev = &ntb->epf->dev;

	epc_featuwes = ntb_epc->epc_featuwes;
	msix_capabwe = epc_featuwes->msix_capabwe;
	msi_capabwe = epc_featuwes->msi_capabwe;

	if (!(msix_capabwe || msi_capabwe)) {
		dev_eww(dev, "MSI ow MSI-X is wequiwed fow doowbeww\n");
		wetuwn -EINVAW;
	}

	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	db_count = ntb->db_count;
	if (db_count > MAX_DB_COUNT) {
		dev_eww(dev, "DB count cannot be mowe than %d\n", MAX_DB_COUNT);
		wetuwn -EINVAW;
	}

	ntb->db_count = db_count;
	epc = ntb_epc->epc;

	if (msi_capabwe) {
		wet = pci_epc_set_msi(epc, func_no, vfunc_no, db_count);
		if (wet) {
			dev_eww(dev, "%s intf: MSI configuwation faiwed\n",
				pci_epc_intewface_stwing(type));
			wetuwn wet;
		}
	}

	if (msix_capabwe) {
		wet = pci_epc_set_msix(epc, func_no, vfunc_no, db_count,
				       ntb_epc->msix_baw,
				       ntb_epc->msix_tabwe_offset);
		if (wet) {
			dev_eww(dev, "MSI configuwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * epf_ntb_awwoc_peew_mem() - Awwocate memowy in peew's outbound addwess space
 * @dev: The PCI device.
 * @ntb_epc: EPC associated with one of the HOST whose BAW howds peew's outbound
 *   addwess
 * @baw: BAW of @ntb_epc in fow which memowy has to be awwocated (couwd be
 *   BAW_DB_MW1, BAW_MW2, BAW_MW3, BAW_MW4)
 * @peew_ntb_epc: EPC associated with HOST whose outbound addwess space is
 *   used by @ntb_epc
 * @size: Size of the addwess wegion that has to be awwocated in peews OB SPACE
 *
 *
 * +-----------------+    +---->+----------------+-----------+-----------------+
 * |       BAW0      |    |     |   Doowbeww 1   +-----------> MSI|X ADDWESS 1 |
 * +-----------------+    |     +----------------+           +-----------------+
 * |       BAW1      |    |     |   Doowbeww 2   +---------+ |                 |
 * +-----------------+----+     +----------------+         | |                 |
 * |       BAW2      |          |   Doowbeww 3   +-------+ | +-----------------+
 * +-----------------+----+     +----------------+       | +-> MSI|X ADDWESS 2 |
 * |       BAW3      |    |     |   Doowbeww 4   +-----+ |   +-----------------+
 * +-----------------+    |     |----------------+     | |   |                 |
 * |       BAW4      |    |     |                |     | |   +-----------------+
 * +-----------------+    |     |      MW1       +---+ | +-->+ MSI|X ADDWESS 3||
 * |       BAW5      |    |     |                |   | |     +-----------------+
 * +-----------------+    +---->-----------------+   | |     |                 |
 *   EP CONTWOWWEW 1            |                |   | |     +-----------------+
 *                              |                |   | +---->+ MSI|X ADDWESS 4 |
 *                              +----------------+   |       +-----------------+
 *                      (A)      EP CONTWOWWEW 2     |       |                 |
 *                                 (OB SPACE)        |       |                 |
 *                                                   +------->      MW1        |
 *                                                           |                 |
 *                                                           |                 |
 *                                                   (B)     +-----------------+
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           |                 |
 *                                                           +-----------------+
 *                                                           PCI Addwess Space
 *                                                           (Managed by HOST2)
 *
 * Awwocate memowy in OB space of EP CONTWOWWEW 2 in the above diagwam. Awwocate
 * fow Doowbeww 1, Doowbeww 2, Doowbeww 3, Doowbeww 4, MW1 (and MW2, MW3, MW4).
 */
static int epf_ntb_awwoc_peew_mem(stwuct device *dev,
				  stwuct epf_ntb_epc *ntb_epc,
				  enum epf_ntb_baw baw,
				  stwuct epf_ntb_epc *peew_ntb_epc,
				  size_t size)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct pci_epf_baw *epf_baw;
	stwuct pci_epc *peew_epc;
	phys_addw_t phys_addw;
	void __iomem *mw_addw;
	enum pci_bawno bawno;
	size_t awign;

	epc_featuwes = ntb_epc->epc_featuwes;
	awign = epc_featuwes->awign;

	if (size < 128)
		size = 128;

	if (awign)
		size = AWIGN(size, awign);
	ewse
		size = woundup_pow_of_two(size);

	peew_epc = peew_ntb_epc->epc;
	mw_addw = pci_epc_mem_awwoc_addw(peew_epc, &phys_addw, size);
	if (!mw_addw) {
		dev_eww(dev, "%s intf: Faiwed to awwocate OB addwess\n",
			pci_epc_intewface_stwing(peew_ntb_epc->type));
		wetuwn -ENOMEM;
	}

	bawno = ntb_epc->epf_ntb_baw[baw];
	epf_baw = &ntb_epc->epf_baw[bawno];
	ntb_epc->mw_addw[bawno] = mw_addw;

	epf_baw->phys_addw = phys_addw;
	epf_baw->size = size;
	epf_baw->bawno = bawno;
	epf_baw->fwags = PCI_BASE_ADDWESS_MEM_TYPE_32;

	wetuwn 0;
}

/**
 * epf_ntb_db_mw_baw_init() - Configuwe Doowbeww and Memowy window BAWs
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Wwappew fow epf_ntb_awwoc_peew_mem() and pci_epc_set_baw() that awwocates
 * memowy in OB addwess space of HOST2 and configuwes BAW of HOST1
 */
static int epf_ntb_db_mw_baw_init(stwuct epf_ntb *ntb,
				  enum pci_epc_intewface_type type)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct epf_ntb_epc *peew_ntb_epc, *ntb_epc;
	stwuct pci_epf_baw *epf_baw;
	stwuct epf_ntb_ctww *ctww;
	u32 num_mws, db_count;
	enum epf_ntb_baw baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	stwuct device *dev;
	size_t awign;
	int wet, i;
	u64 size;

	ntb_epc = ntb->epc[type];
	peew_ntb_epc = ntb->epc[!type];

	dev = &ntb->epf->dev;
	epc_featuwes = ntb_epc->epc_featuwes;
	awign = epc_featuwes->awign;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;
	epc = ntb_epc->epc;
	num_mws = ntb->num_mws;
	db_count = ntb->db_count;

	fow (baw = BAW_DB_MW1, i = 0; i < num_mws; baw++, i++) {
		if (baw == BAW_DB_MW1) {
			awign = awign ? awign : 4;
			size = db_count * awign;
			size = AWIGN(size, ntb->mws_size[i]);
			ctww = ntb_epc->weg;
			ctww->mw1_offset = size;
			size += ntb->mws_size[i];
		} ewse {
			size = ntb->mws_size[i];
		}

		wet = epf_ntb_awwoc_peew_mem(dev, ntb_epc, baw,
					     peew_ntb_epc, size);
		if (wet) {
			dev_eww(dev, "%s intf: DoowBeww mem awwoc faiwed\n",
				pci_epc_intewface_stwing(type));
			goto eww_awwoc_peew_mem;
		}

		bawno = ntb_epc->epf_ntb_baw[baw];
		epf_baw = &ntb_epc->epf_baw[bawno];

		wet = pci_epc_set_baw(epc, func_no, vfunc_no, epf_baw);
		if (wet) {
			dev_eww(dev, "%s intf: DoowBeww BAW set faiwed\n",
				pci_epc_intewface_stwing(type));
			goto eww_awwoc_peew_mem;
		}
	}

	wetuwn 0;

eww_awwoc_peew_mem:
	epf_ntb_db_mw_baw_cweanup(ntb, type);

	wetuwn wet;
}

/**
 * epf_ntb_epc_destwoy_intewface() - Cweanup NTB EPC intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Unbind NTB function device fwom EPC and wewinquish wefewence to pci_epc
 * fow each of the intewface.
 */
static void epf_ntb_epc_destwoy_intewface(stwuct epf_ntb *ntb,
					  enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *ntb_epc;
	stwuct pci_epc *epc;
	stwuct pci_epf *epf;

	if (type < 0)
		wetuwn;

	epf = ntb->epf;
	ntb_epc = ntb->epc[type];
	if (!ntb_epc)
		wetuwn;
	epc = ntb_epc->epc;
	pci_epc_wemove_epf(epc, epf, type);
	pci_epc_put(epc);
}

/**
 * epf_ntb_epc_destwoy() - Cweanup NTB EPC intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Wwappew fow epf_ntb_epc_destwoy_intewface() to cweanup aww the NTB intewfaces
 */
static void epf_ntb_epc_destwoy(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;

	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++)
		epf_ntb_epc_destwoy_intewface(ntb, type);
}

/**
 * epf_ntb_epc_cweate_intewface() - Cweate and initiawize NTB EPC intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @epc: stwuct pci_epc to which a pawticuwaw NTB intewface shouwd be associated
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Awwocate memowy fow NTB EPC intewface and initiawize it.
 */
static int epf_ntb_epc_cweate_intewface(stwuct epf_ntb *ntb,
					stwuct pci_epc *epc,
					enum pci_epc_intewface_type type)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct pci_epf_baw *epf_baw;
	stwuct epf_ntb_epc *ntb_epc;
	u8 func_no, vfunc_no;
	stwuct pci_epf *epf;
	stwuct device *dev;

	dev = &ntb->epf->dev;

	ntb_epc = devm_kzawwoc(dev, sizeof(*ntb_epc), GFP_KEWNEW);
	if (!ntb_epc)
		wetuwn -ENOMEM;

	epf = ntb->epf;
	vfunc_no = epf->vfunc_no;
	if (type == PWIMAWY_INTEWFACE) {
		func_no = epf->func_no;
		epf_baw = epf->baw;
	} ewse {
		func_no = epf->sec_epc_func_no;
		epf_baw = epf->sec_epc_baw;
	}

	ntb_epc->winkup = fawse;
	ntb_epc->epc = epc;
	ntb_epc->func_no = func_no;
	ntb_epc->vfunc_no = vfunc_no;
	ntb_epc->type = type;
	ntb_epc->epf_baw = epf_baw;
	ntb_epc->epf_ntb = ntb;

	epc_featuwes = pci_epc_get_featuwes(epc, func_no, vfunc_no);
	if (!epc_featuwes)
		wetuwn -EINVAW;
	ntb_epc->epc_featuwes = epc_featuwes;

	ntb->epc[type] = ntb_epc;

	wetuwn 0;
}

/**
 * epf_ntb_epc_cweate() - Cweate and initiawize NTB EPC intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Get a wefewence to EPC device and bind NTB function device to that EPC
 * fow each of the intewface. It is awso a wwappew to
 * epf_ntb_epc_cweate_intewface() to awwocate memowy fow NTB EPC intewface
 * and initiawize it
 */
static int epf_ntb_epc_cweate(stwuct epf_ntb *ntb)
{
	stwuct pci_epf *epf;
	stwuct device *dev;
	int wet;

	epf = ntb->epf;
	dev = &epf->dev;

	wet = epf_ntb_epc_cweate_intewface(ntb, epf->epc, PWIMAWY_INTEWFACE);
	if (wet) {
		dev_eww(dev, "PWIMAWY intf: Faiw to cweate NTB EPC\n");
		wetuwn wet;
	}

	wet = epf_ntb_epc_cweate_intewface(ntb, epf->sec_epc,
					   SECONDAWY_INTEWFACE);
	if (wet) {
		dev_eww(dev, "SECONDAWY intf: Faiw to cweate NTB EPC\n");
		goto eww_epc_cweate;
	}

	wetuwn 0;

eww_epc_cweate:
	epf_ntb_epc_destwoy_intewface(ntb, PWIMAWY_INTEWFACE);

	wetuwn wet;
}

/**
 * epf_ntb_init_epc_baw_intewface() - Identify BAWs to be used fow each of
 *   the NTB constwucts (scwatchpad wegion, doowbeww, memowywindow)
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Identify the fwee BAWs to be used fow each of BAW_CONFIG, BAW_PEEW_SPAD,
 * BAW_DB_MW1, BAW_MW2, BAW_MW3 and BAW_MW4.
 */
static int epf_ntb_init_epc_baw_intewface(stwuct epf_ntb *ntb,
					  enum pci_epc_intewface_type type)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct epf_ntb_epc *ntb_epc;
	enum pci_bawno bawno;
	enum epf_ntb_baw baw;
	stwuct device *dev;
	u32 num_mws;
	int i;

	bawno = BAW_0;
	ntb_epc = ntb->epc[type];
	num_mws = ntb->num_mws;
	dev = &ntb->epf->dev;
	epc_featuwes = ntb_epc->epc_featuwes;

	/* These awe wequiwed BAWs which awe mandatowy fow NTB functionawity */
	fow (baw = BAW_CONFIG; baw <= BAW_DB_MW1; baw++, bawno++) {
		bawno = pci_epc_get_next_fwee_baw(epc_featuwes, bawno);
		if (bawno < 0) {
			dev_eww(dev, "%s intf: Faiw to get NTB function BAW\n",
				pci_epc_intewface_stwing(type));
			wetuwn bawno;
		}
		ntb_epc->epf_ntb_baw[baw] = bawno;
	}

	/* These awe optionaw BAWs which don't impact NTB functionawity */
	fow (baw = BAW_MW2, i = 1; i < num_mws; baw++, bawno++, i++) {
		bawno = pci_epc_get_next_fwee_baw(epc_featuwes, bawno);
		if (bawno < 0) {
			ntb->num_mws = i;
			dev_dbg(dev, "BAW not avaiwabwe fow > MW%d\n", i + 1);
		}
		ntb_epc->epf_ntb_baw[baw] = bawno;
	}

	wetuwn 0;
}

/**
 * epf_ntb_init_epc_baw() - Identify BAWs to be used fow each of the NTB
 * constwucts (scwatchpad wegion, doowbeww, memowywindow)
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Wwappew to epf_ntb_init_epc_baw_intewface() to identify the fwee BAWs
 * to be used fow each of BAW_CONFIG, BAW_PEEW_SPAD, BAW_DB_MW1, BAW_MW2,
 * BAW_MW3 and BAW_MW4 fow aww the intewfaces.
 */
static int epf_ntb_init_epc_baw(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;
	stwuct device *dev;
	int wet;

	dev = &ntb->epf->dev;
	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++) {
		wet = epf_ntb_init_epc_baw_intewface(ntb, type);
		if (wet) {
			dev_eww(dev, "Faiw to init EPC baw fow %s intewface\n",
				pci_epc_intewface_stwing(type));
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * epf_ntb_epc_init_intewface() - Initiawize NTB intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Wwappew to initiawize a pawticuwaw EPC intewface and stawt the wowkqueue
 * to check fow commands fwom host. This function wiww wwite to the
 * EP contwowwew HW fow configuwing it.
 */
static int epf_ntb_epc_init_intewface(stwuct epf_ntb *ntb,
				      enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *ntb_epc;
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	stwuct pci_epf *epf;
	stwuct device *dev;
	int wet;

	ntb_epc = ntb->epc[type];
	epf = ntb->epf;
	dev = &epf->dev;
	epc = ntb_epc->epc;
	func_no = ntb_epc->func_no;
	vfunc_no = ntb_epc->vfunc_no;

	wet = epf_ntb_config_sspad_baw_set(ntb->epc[type]);
	if (wet) {
		dev_eww(dev, "%s intf: Config/sewf SPAD BAW init faiwed\n",
			pci_epc_intewface_stwing(type));
		wetuwn wet;
	}

	wet = epf_ntb_peew_spad_baw_set(ntb, type);
	if (wet) {
		dev_eww(dev, "%s intf: Peew SPAD BAW init faiwed\n",
			pci_epc_intewface_stwing(type));
		goto eww_peew_spad_baw_init;
	}

	wet = epf_ntb_configuwe_intewwupt(ntb, type);
	if (wet) {
		dev_eww(dev, "%s intf: Intewwupt configuwation faiwed\n",
			pci_epc_intewface_stwing(type));
		goto eww_peew_spad_baw_init;
	}

	wet = epf_ntb_db_mw_baw_init(ntb, type);
	if (wet) {
		dev_eww(dev, "%s intf: DB/MW BAW init faiwed\n",
			pci_epc_intewface_stwing(type));
		goto eww_db_mw_baw_init;
	}

	if (vfunc_no <= 1) {
		wet = pci_epc_wwite_headew(epc, func_no, vfunc_no, epf->headew);
		if (wet) {
			dev_eww(dev, "%s intf: Configuwation headew wwite faiwed\n",
				pci_epc_intewface_stwing(type));
			goto eww_wwite_headew;
		}
	}

	INIT_DEWAYED_WOWK(&ntb->epc[type]->cmd_handwew, epf_ntb_cmd_handwew);
	queue_wowk(kpcintb_wowkqueue, &ntb->epc[type]->cmd_handwew.wowk);

	wetuwn 0;

eww_wwite_headew:
	epf_ntb_db_mw_baw_cweanup(ntb, type);

eww_db_mw_baw_init:
	epf_ntb_peew_spad_baw_cweaw(ntb->epc[type]);

eww_peew_spad_baw_init:
	epf_ntb_config_sspad_baw_cweaw(ntb->epc[type]);

	wetuwn wet;
}

/**
 * epf_ntb_epc_cweanup_intewface() - Cweanup NTB intewface
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 * @type: PWIMAWY intewface ow SECONDAWY intewface
 *
 * Wwappew to cweanup a pawticuwaw NTB intewface.
 */
static void epf_ntb_epc_cweanup_intewface(stwuct epf_ntb *ntb,
					  enum pci_epc_intewface_type type)
{
	stwuct epf_ntb_epc *ntb_epc;

	if (type < 0)
		wetuwn;

	ntb_epc = ntb->epc[type];
	cancew_dewayed_wowk(&ntb_epc->cmd_handwew);
	epf_ntb_db_mw_baw_cweanup(ntb, type);
	epf_ntb_peew_spad_baw_cweaw(ntb_epc);
	epf_ntb_config_sspad_baw_cweaw(ntb_epc);
}

/**
 * epf_ntb_epc_cweanup() - Cweanup aww NTB intewfaces
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Wwappew to cweanup aww NTB intewfaces.
 */
static void epf_ntb_epc_cweanup(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;

	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++)
		epf_ntb_epc_cweanup_intewface(ntb, type);
}

/**
 * epf_ntb_epc_init() - Initiawize aww NTB intewfaces
 * @ntb: NTB device that faciwitates communication between HOST1 and HOST2
 *
 * Wwappew to initiawize aww NTB intewface and stawt the wowkqueue
 * to check fow commands fwom host.
 */
static int epf_ntb_epc_init(stwuct epf_ntb *ntb)
{
	enum pci_epc_intewface_type type;
	stwuct device *dev;
	int wet;

	dev = &ntb->epf->dev;

	fow (type = PWIMAWY_INTEWFACE; type <= SECONDAWY_INTEWFACE; type++) {
		wet = epf_ntb_epc_init_intewface(ntb, type);
		if (wet) {
			dev_eww(dev, "%s intf: Faiwed to initiawize\n",
				pci_epc_intewface_stwing(type));
			goto eww_init_type;
		}
	}

	wetuwn 0;

eww_init_type:
	epf_ntb_epc_cweanup_intewface(ntb, type - 1);

	wetuwn wet;
}

/**
 * epf_ntb_bind() - Initiawize endpoint contwowwew to pwovide NTB functionawity
 * @epf: NTB endpoint function device
 *
 * Initiawize both the endpoint contwowwews associated with NTB function device.
 * Invoked when a pwimawy intewface ow secondawy intewface is bound to EPC
 * device. This function wiww succeed onwy when EPC is bound to both the
 * intewfaces.
 */
static int epf_ntb_bind(stwuct pci_epf *epf)
{
	stwuct epf_ntb *ntb = epf_get_dwvdata(epf);
	stwuct device *dev = &epf->dev;
	int wet;

	if (!epf->epc) {
		dev_dbg(dev, "PWIMAWY EPC intewface not yet bound\n");
		wetuwn 0;
	}

	if (!epf->sec_epc) {
		dev_dbg(dev, "SECONDAWY EPC intewface not yet bound\n");
		wetuwn 0;
	}

	wet = epf_ntb_epc_cweate(ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to cweate NTB EPC\n");
		wetuwn wet;
	}

	wet = epf_ntb_init_epc_baw(ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to cweate NTB EPC\n");
		goto eww_baw_init;
	}

	wet = epf_ntb_config_spad_baw_awwoc_intewface(ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate BAW memowy\n");
		goto eww_baw_awwoc;
	}

	wet = epf_ntb_epc_init(ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize EPC\n");
		goto eww_baw_awwoc;
	}

	epf_set_dwvdata(epf, ntb);

	wetuwn 0;

eww_baw_awwoc:
	epf_ntb_config_spad_baw_fwee(ntb);

eww_baw_init:
	epf_ntb_epc_destwoy(ntb);

	wetuwn wet;
}

/**
 * epf_ntb_unbind() - Cweanup the initiawization fwom epf_ntb_bind()
 * @epf: NTB endpoint function device
 *
 * Cweanup the initiawization fwom epf_ntb_bind()
 */
static void epf_ntb_unbind(stwuct pci_epf *epf)
{
	stwuct epf_ntb *ntb = epf_get_dwvdata(epf);

	epf_ntb_epc_cweanup(ntb);
	epf_ntb_config_spad_baw_fwee(ntb);
	epf_ntb_epc_destwoy(ntb);
}

#define EPF_NTB_W(_name)						\
static ssize_t epf_ntb_##_name##_show(stwuct config_item *item,		\
				      chaw *page)			\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
									\
	wetuwn sysfs_emit(page, "%d\n", ntb->_name);			\
}

#define EPF_NTB_W(_name)						\
static ssize_t epf_ntb_##_name##_stowe(stwuct config_item *item,	\
				       const chaw *page, size_t wen)	\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
	u32 vaw;							\
									\
	if (kstwtou32(page, 0, &vaw) < 0)				\
		wetuwn -EINVAW;						\
									\
	ntb->_name = vaw;						\
									\
	wetuwn wen;							\
}

#define EPF_NTB_MW_W(_name)						\
static ssize_t epf_ntb_##_name##_show(stwuct config_item *item,		\
				      chaw *page)			\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
	int win_no;							\
									\
	sscanf(#_name, "mw%d", &win_no);				\
									\
	wetuwn sysfs_emit(page, "%wwd\n", ntb->mws_size[win_no - 1]);	\
}

#define EPF_NTB_MW_W(_name)						\
static ssize_t epf_ntb_##_name##_stowe(stwuct config_item *item,	\
				       const chaw *page, size_t wen)	\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
	stwuct device *dev = &ntb->epf->dev;				\
	int win_no;							\
	u64 vaw;							\
									\
	if (kstwtou64(page, 0, &vaw) < 0)				\
		wetuwn -EINVAW;						\
									\
	if (sscanf(#_name, "mw%d", &win_no) != 1)			\
		wetuwn -EINVAW;						\
									\
	if (ntb->num_mws < win_no) {					\
		dev_eww(dev, "Invawid num_nws: %d vawue\n", ntb->num_mws); \
		wetuwn -EINVAW;						\
	}								\
									\
	ntb->mws_size[win_no - 1] = vaw;				\
									\
	wetuwn wen;							\
}

static ssize_t epf_ntb_num_mws_stowe(stwuct config_item *item,
				     const chaw *page, size_t wen)
{
	stwuct config_gwoup *gwoup = to_config_gwoup(item);
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);
	u32 vaw;

	if (kstwtou32(page, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw > MAX_MW)
		wetuwn -EINVAW;

	ntb->num_mws = vaw;

	wetuwn wen;
}

EPF_NTB_W(spad_count)
EPF_NTB_W(spad_count)
EPF_NTB_W(db_count)
EPF_NTB_W(db_count)
EPF_NTB_W(num_mws)
EPF_NTB_MW_W(mw1)
EPF_NTB_MW_W(mw1)
EPF_NTB_MW_W(mw2)
EPF_NTB_MW_W(mw2)
EPF_NTB_MW_W(mw3)
EPF_NTB_MW_W(mw3)
EPF_NTB_MW_W(mw4)
EPF_NTB_MW_W(mw4)

CONFIGFS_ATTW(epf_ntb_, spad_count);
CONFIGFS_ATTW(epf_ntb_, db_count);
CONFIGFS_ATTW(epf_ntb_, num_mws);
CONFIGFS_ATTW(epf_ntb_, mw1);
CONFIGFS_ATTW(epf_ntb_, mw2);
CONFIGFS_ATTW(epf_ntb_, mw3);
CONFIGFS_ATTW(epf_ntb_, mw4);

static stwuct configfs_attwibute *epf_ntb_attws[] = {
	&epf_ntb_attw_spad_count,
	&epf_ntb_attw_db_count,
	&epf_ntb_attw_num_mws,
	&epf_ntb_attw_mw1,
	&epf_ntb_attw_mw2,
	&epf_ntb_attw_mw3,
	&epf_ntb_attw_mw4,
	NUWW,
};

static const stwuct config_item_type ntb_gwoup_type = {
	.ct_attws	= epf_ntb_attws,
	.ct_ownew	= THIS_MODUWE,
};

/**
 * epf_ntb_add_cfs() - Add configfs diwectowy specific to NTB
 * @epf: NTB endpoint function device
 * @gwoup: A pointew to the config_gwoup stwuctuwe wefewencing a gwoup of
 *	   config_items of a specific type that bewong to a specific sub-system.
 *
 * Add configfs diwectowy specific to NTB. This diwectowy wiww howd
 * NTB specific pwopewties wike db_count, spad_count, num_mws etc.,
 */
static stwuct config_gwoup *epf_ntb_add_cfs(stwuct pci_epf *epf,
					    stwuct config_gwoup *gwoup)
{
	stwuct epf_ntb *ntb = epf_get_dwvdata(epf);
	stwuct config_gwoup *ntb_gwoup = &ntb->gwoup;
	stwuct device *dev = &epf->dev;

	config_gwoup_init_type_name(ntb_gwoup, dev_name(dev), &ntb_gwoup_type);

	wetuwn ntb_gwoup;
}

/**
 * epf_ntb_pwobe() - Pwobe NTB function dwivew
 * @epf: NTB endpoint function device
 * @id: NTB endpoint function device ID
 *
 * Pwobe NTB function dwivew when endpoint function bus detects a NTB
 * endpoint function.
 */
static int epf_ntb_pwobe(stwuct pci_epf *epf,
			 const stwuct pci_epf_device_id *id)
{
	stwuct epf_ntb *ntb;
	stwuct device *dev;

	dev = &epf->dev;

	ntb = devm_kzawwoc(dev, sizeof(*ntb), GFP_KEWNEW);
	if (!ntb)
		wetuwn -ENOMEM;

	epf->headew = &epf_ntb_headew;
	ntb->epf = epf;
	epf_set_dwvdata(epf, ntb);

	wetuwn 0;
}

static const stwuct pci_epf_ops epf_ntb_ops = {
	.bind	= epf_ntb_bind,
	.unbind	= epf_ntb_unbind,
	.add_cfs = epf_ntb_add_cfs,
};

static const stwuct pci_epf_device_id epf_ntb_ids[] = {
	{
		.name = "pci_epf_ntb",
	},
	{},
};

static stwuct pci_epf_dwivew epf_ntb_dwivew = {
	.dwivew.name	= "pci_epf_ntb",
	.pwobe		= epf_ntb_pwobe,
	.id_tabwe	= epf_ntb_ids,
	.ops		= &epf_ntb_ops,
	.ownew		= THIS_MODUWE,
};

static int __init epf_ntb_init(void)
{
	int wet;

	kpcintb_wowkqueue = awwoc_wowkqueue("kpcintb", WQ_MEM_WECWAIM |
					    WQ_HIGHPWI, 0);
	wet = pci_epf_wegistew_dwivew(&epf_ntb_dwivew);
	if (wet) {
		destwoy_wowkqueue(kpcintb_wowkqueue);
		pw_eww("Faiwed to wegistew pci epf ntb dwivew --> %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(epf_ntb_init);

static void __exit epf_ntb_exit(void)
{
	pci_epf_unwegistew_dwivew(&epf_ntb_dwivew);
	destwoy_wowkqueue(kpcintb_wowkqueue);
}
moduwe_exit(epf_ntb_exit);

MODUWE_DESCWIPTION("PCI EPF NTB DWIVEW");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
MODUWE_WICENSE("GPW v2");
