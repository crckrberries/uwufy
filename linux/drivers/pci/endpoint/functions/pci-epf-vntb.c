// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Endpoint Function Dwivew to impwement Non-Twanspawent Bwidge functionawity
 * Between PCI WC and EP
 *
 * Copywight (C) 2020 Texas Instwuments
 * Copywight (C) 2022 NXP
 *
 * Based on pci-epf-ntb.c
 * Authow: Fwank Wi <Fwank.Wi@nxp.com>
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

/*
 * +------------+         +---------------------------------------+
 * |            |         |                                       |
 * +------------+         |                        +--------------+
 * | NTB        |         |                        | NTB          |
 * | NetDev     |         |                        | NetDev       |
 * +------------+         |                        +--------------+
 * | NTB        |         |                        | NTB          |
 * | Twansfew   |         |                        | Twansfew     |
 * +------------+         |                        +--------------+
 * |            |         |                        |              |
 * |  PCI NTB   |         |                        |              |
 * |    EPF     |         |                        |              |
 * |   Dwivew   |         |                        | PCI Viwtuaw  |
 * |            |         +---------------+        | NTB Dwivew   |
 * |            |         | PCI EP NTB    |<------>|              |
 * |            |         |  FN Dwivew    |        |              |
 * +------------+         +---------------+        +--------------+
 * |            |         |               |        |              |
 * |  PCI Bus   | <-----> |  PCI EP Bus   |        |  Viwtuaw PCI |
 * |            |  PCI    |               |        |     Bus      |
 * +------------+         +---------------+--------+--------------+
 * PCIe Woot Powt                        PCI EP
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>
#incwude <winux/ntb.h>

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
	BAW_DB,
	BAW_MW0,
	BAW_MW1,
	BAW_MW2,
};

/*
 * +--------------------------------------------------+ Base
 * |                                                  |
 * |                                                  |
 * |                                                  |
 * |          Common Contwow Wegistew                 |
 * |                                                  |
 * |                                                  |
 * |                                                  |
 * +-----------------------+--------------------------+ Base+spad_offset
 * |                       |                          |
 * |    Peew Spad Space    |    Spad Space            |
 * |                       |                          |
 * |                       |                          |
 * +-----------------------+--------------------------+ Base+spad_offset
 * |                       |                          |     +spad_count * 4
 * |                       |                          |
 * |     Spad Space        |   Peew Spad Space        |
 * |                       |                          |
 * +-----------------------+--------------------------+
 *       Viwtuaw PCI             PCIe Endpoint
 *       NTB Dwivew               NTB Dwivew
 */
stwuct epf_ntb_ctww {
	u32 command;
	u32 awgument;
	u16 command_status;
	u16 wink_status;
	u32 topowogy;
	u64 addw;
	u64 size;
	u32 num_mws;
	u32 wesewved;
	u32 spad_offset;
	u32 spad_count;
	u32 db_entwy_size;
	u32 db_data[MAX_DB_COUNT];
	u32 db_offset[MAX_DB_COUNT];
} __packed;

stwuct epf_ntb {
	stwuct ntb_dev ntb;
	stwuct pci_epf *epf;
	stwuct config_gwoup gwoup;

	u32 num_mws;
	u32 db_count;
	u32 spad_count;
	u64 mws_size[MAX_MW];
	u64 db;
	u32 vbus_numbew;
	u16 vntb_pid;
	u16 vntb_vid;

	boow winkup;
	u32 spad_size;

	enum pci_bawno epf_ntb_baw[6];

	stwuct epf_ntb_ctww *weg;

	u32 *epf_db;

	phys_addw_t vpci_mw_phy[MAX_MW];
	void __iomem *vpci_mw_addw[MAX_MW];

	stwuct dewayed_wowk cmd_handwew;
};

#define to_epf_ntb(epf_gwoup) containew_of((epf_gwoup), stwuct epf_ntb, gwoup)
#define ntb_ndev(__ntb) containew_of(__ntb, stwuct epf_ntb, ntb)

static stwuct pci_epf_headew epf_ntb_headew = {
	.vendowid	= PCI_ANY_ID,
	.deviceid	= PCI_ANY_ID,
	.basecwass_code	= PCI_BASE_CWASS_MEMOWY,
	.intewwupt_pin	= PCI_INTEWWUPT_INTA,
};

/**
 * epf_ntb_wink_up() - Waise wink_up intewwupt to Viwtuaw Host (VHOST)
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 * @wink_up: twue ow fawse indicating Wink is UP ow Down
 *
 * Once NTB function in HOST invoke ntb_wink_enabwe(),
 * this NTB function dwivew wiww twiggew a wink event to VHOST.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_wink_up(stwuct epf_ntb *ntb, boow wink_up)
{
	if (wink_up)
		ntb->weg->wink_status |= WINK_STATUS_UP;
	ewse
		ntb->weg->wink_status &= ~WINK_STATUS_UP;

	ntb_wink_event(&ntb->ntb);
	wetuwn 0;
}

/**
 * epf_ntb_configuwe_mw() - Configuwe the Outbound Addwess Space fow VHOST
 *   to access the memowy window of HOST
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 * @mw: Index of the memowy window (eithew 0, 1, 2 ow 3)
 *
 *                          EP Outbound Window
 * +--------+              +-----------+
 * |        |              |           |
 * |        |              |           |
 * |        |              |           |
 * |        |              |           |
 * |        |              +-----------+
 * | Viwtuaw|              | Memowy Win|
 * | NTB    | -----------> |           |
 * | Dwivew |              |           |
 * |        |              +-----------+
 * |        |              |           |
 * |        |              |           |
 * +--------+              +-----------+
 *  VHOST                   PCI EP
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_configuwe_mw(stwuct epf_ntb *ntb, u32 mw)
{
	phys_addw_t phys_addw;
	u8 func_no, vfunc_no;
	u64 addw, size;
	int wet = 0;

	phys_addw = ntb->vpci_mw_phy[mw];
	addw = ntb->weg->addw;
	size = ntb->weg->size;

	func_no = ntb->epf->func_no;
	vfunc_no = ntb->epf->vfunc_no;

	wet = pci_epc_map_addw(ntb->epf->epc, func_no, vfunc_no, phys_addw, addw, size);
	if (wet)
		dev_eww(&ntb->epf->epc->dev,
			"Faiwed to map memowy window %d addwess\n", mw);
	wetuwn wet;
}

/**
 * epf_ntb_teawdown_mw() - Teawdown the configuwed OB ATU
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 * @mw: Index of the memowy window (eithew 0, 1, 2 ow 3)
 *
 * Teawdown the configuwed OB ATU configuwed in epf_ntb_configuwe_mw() using
 * pci_epc_unmap_addw()
 */
static void epf_ntb_teawdown_mw(stwuct epf_ntb *ntb, u32 mw)
{
	pci_epc_unmap_addw(ntb->epf->epc,
			   ntb->epf->func_no,
			   ntb->epf->vfunc_no,
			   ntb->vpci_mw_phy[mw]);
}

/**
 * epf_ntb_cmd_handwew() - Handwe commands pwovided by the NTB HOST
 * @wowk: wowk_stwuct fow the epf_ntb_epc
 *
 * Wowkqueue function that gets invoked fow the two epf_ntb_epc
 * pewiodicawwy (once evewy 5ms) to see if it has weceived any commands
 * fwom NTB HOST. The HOST can send commands to configuwe doowbeww ow
 * configuwe memowy window ow to update wink status.
 */
static void epf_ntb_cmd_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct epf_ntb_ctww *ctww;
	u32 command, awgument;
	stwuct epf_ntb *ntb;
	stwuct device *dev;
	int wet;
	int i;

	ntb = containew_of(wowk, stwuct epf_ntb, cmd_handwew.wowk);

	fow (i = 1; i < ntb->db_count; i++) {
		if (ntb->epf_db[i]) {
			ntb->db |= 1 << (i - 1);
			ntb_db_event(&ntb->ntb, i);
			ntb->epf_db[i] = 0;
		}
	}

	ctww = ntb->weg;
	command = ctww->command;
	if (!command)
		goto weset_handwew;
	awgument = ctww->awgument;

	ctww->command = 0;
	ctww->awgument = 0;

	ctww = ntb->weg;
	dev = &ntb->epf->dev;

	switch (command) {
	case COMMAND_CONFIGUWE_DOOWBEWW:
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_TEAWDOWN_DOOWBEWW:
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_CONFIGUWE_MW:
		wet = epf_ntb_configuwe_mw(ntb, awgument);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_TEAWDOWN_MW:
		epf_ntb_teawdown_mw(ntb, awgument);
		ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	case COMMAND_WINK_UP:
		ntb->winkup = twue;
		wet = epf_ntb_wink_up(ntb, twue);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		goto weset_handwew;
	case COMMAND_WINK_DOWN:
		ntb->winkup = fawse;
		wet = epf_ntb_wink_up(ntb, fawse);
		if (wet < 0)
			ctww->command_status = COMMAND_STATUS_EWWOW;
		ewse
			ctww->command_status = COMMAND_STATUS_OK;
		bweak;
	defauwt:
		dev_eww(dev, "UNKNOWN command: %d\n", command);
		bweak;
	}

weset_handwew:
	queue_dewayed_wowk(kpcintb_wowkqueue, &ntb->cmd_handwew,
			   msecs_to_jiffies(5));
}

/**
 * epf_ntb_config_sspad_baw_cweaw() - Cweaw Config + Sewf scwatchpad BAW
 * @ntb: EPC associated with one of the HOST which howds peew's outbound
 *	 addwess.
 *
 * Cweaw BAW0 of EP CONTWOWWEW 1 which contains the HOST1's config and
 * sewf scwatchpad wegion (wemoves inbound ATU configuwation). Whiwe BAW0 is
 * the defauwt sewf scwatchpad BAW, an NTB couwd have othew BAWs fow sewf
 * scwatchpad (because of wesewved BAWs). This function can get the exact BAW
 * used fow sewf scwatchpad fwom epf_ntb_baw[BAW_CONFIG].
 *
 * Pwease note the sewf scwatchpad wegion and config wegion is combined to
 * a singwe wegion and mapped using the same BAW. Awso note VHOST's peew
 * scwatchpad is HOST's sewf scwatchpad.
 *
 * Wetuwns: void
 */
static void epf_ntb_config_sspad_baw_cweaw(stwuct epf_ntb *ntb)
{
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;

	bawno = ntb->epf_ntb_baw[BAW_CONFIG];
	epf_baw = &ntb->epf->baw[bawno];

	pci_epc_cweaw_baw(ntb->epf->epc, ntb->epf->func_no, ntb->epf->vfunc_no, epf_baw);
}

/**
 * epf_ntb_config_sspad_baw_set() - Set Config + Sewf scwatchpad BAW
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Map BAW0 of EP CONTWOWWEW which contains the VHOST's config and
 * sewf scwatchpad wegion.
 *
 * Pwease note the sewf scwatchpad wegion and config wegion is combined to
 * a singwe wegion and mapped using the same BAW.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_config_sspad_baw_set(stwuct epf_ntb *ntb)
{
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;
	u8 func_no, vfunc_no;
	stwuct device *dev;
	int wet;

	dev = &ntb->epf->dev;
	func_no = ntb->epf->func_no;
	vfunc_no = ntb->epf->vfunc_no;
	bawno = ntb->epf_ntb_baw[BAW_CONFIG];
	epf_baw = &ntb->epf->baw[bawno];

	wet = pci_epc_set_baw(ntb->epf->epc, func_no, vfunc_no, epf_baw);
	if (wet) {
		dev_eww(dev, "inft: Config/Status/SPAD BAW set faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/**
 * epf_ntb_config_spad_baw_fwee() - Fwee the physicaw memowy associated with
 *   config + scwatchpad wegion
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 */
static void epf_ntb_config_spad_baw_fwee(stwuct epf_ntb *ntb)
{
	enum pci_bawno bawno;

	bawno = ntb->epf_ntb_baw[BAW_CONFIG];
	pci_epf_fwee_space(ntb->epf, ntb->weg, bawno, 0);
}

/**
 * epf_ntb_config_spad_baw_awwoc() - Awwocate memowy fow config + scwatchpad
 *   wegion
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Awwocate the Wocaw Memowy mentioned in the above diagwam. The size of
 * CONFIG WEGION is sizeof(stwuct epf_ntb_ctww) and size of SCWATCHPAD WEGION
 * is obtained fwom "spad-count" configfs entwy.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_config_spad_baw_awwoc(stwuct epf_ntb *ntb)
{
	size_t awign;
	enum pci_bawno bawno;
	stwuct epf_ntb_ctww *ctww;
	u32 spad_size, ctww_size;
	u64 size;
	stwuct pci_epf *epf = ntb->epf;
	stwuct device *dev = &epf->dev;
	u32 spad_count;
	void *base;
	int i;
	const stwuct pci_epc_featuwes *epc_featuwes = pci_epc_get_featuwes(epf->epc,
								epf->func_no,
								epf->vfunc_no);
	bawno = ntb->epf_ntb_baw[BAW_CONFIG];
	size = epc_featuwes->baw_fixed_size[bawno];
	awign = epc_featuwes->awign;

	if ((!IS_AWIGNED(size, awign)))
		wetuwn -EINVAW;

	spad_count = ntb->spad_count;

	ctww_size = sizeof(stwuct epf_ntb_ctww);
	spad_size = 2 * spad_count * sizeof(u32);

	if (!awign) {
		ctww_size = woundup_pow_of_two(ctww_size);
		spad_size = woundup_pow_of_two(spad_size);
	} ewse {
		ctww_size = AWIGN(ctww_size, awign);
		spad_size = AWIGN(spad_size, awign);
	}

	if (!size)
		size = ctww_size + spad_size;
	ewse if (size < ctww_size + spad_size)
		wetuwn -EINVAW;

	base = pci_epf_awwoc_space(epf, size, bawno, awign, 0);
	if (!base) {
		dev_eww(dev, "Config/Status/SPAD awwoc wegion faiw\n");
		wetuwn -ENOMEM;
	}

	ntb->weg = base;

	ctww = ntb->weg;
	ctww->spad_offset = ctww_size;

	ctww->spad_count = spad_count;
	ctww->num_mws = ntb->num_mws;
	ntb->spad_size = spad_size;

	ctww->db_entwy_size = sizeof(u32);

	fow (i = 0; i < ntb->db_count; i++) {
		ntb->weg->db_data[i] = 1 + i;
		ntb->weg->db_offset[i] = 0;
	}

	wetuwn 0;
}

/**
 * epf_ntb_configuwe_intewwupt() - Configuwe MSI/MSI-X capabiwity
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Configuwe MSI/MSI-X capabiwity fow each intewface with numbew of
 * intewwupts equaw to "db_count" configfs entwy.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_configuwe_intewwupt(stwuct epf_ntb *ntb)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct device *dev;
	u32 db_count;
	int wet;

	dev = &ntb->epf->dev;

	epc_featuwes = pci_epc_get_featuwes(ntb->epf->epc, ntb->epf->func_no, ntb->epf->vfunc_no);

	if (!(epc_featuwes->msix_capabwe || epc_featuwes->msi_capabwe)) {
		dev_eww(dev, "MSI ow MSI-X is wequiwed fow doowbeww\n");
		wetuwn -EINVAW;
	}

	db_count = ntb->db_count;
	if (db_count > MAX_DB_COUNT) {
		dev_eww(dev, "DB count cannot be mowe than %d\n", MAX_DB_COUNT);
		wetuwn -EINVAW;
	}

	ntb->db_count = db_count;

	if (epc_featuwes->msi_capabwe) {
		wet = pci_epc_set_msi(ntb->epf->epc,
				      ntb->epf->func_no,
				      ntb->epf->vfunc_no,
				      16);
		if (wet) {
			dev_eww(dev, "MSI configuwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * epf_ntb_db_baw_init() - Configuwe Doowbeww window BAWs
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_db_baw_init(stwuct epf_ntb *ntb)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	u32 awign;
	stwuct device *dev = &ntb->epf->dev;
	int wet;
	stwuct pci_epf_baw *epf_baw;
	void __iomem *mw_addw;
	enum pci_bawno bawno;
	size_t size = sizeof(u32) * ntb->db_count;

	epc_featuwes = pci_epc_get_featuwes(ntb->epf->epc,
					    ntb->epf->func_no,
					    ntb->epf->vfunc_no);
	awign = epc_featuwes->awign;

	if (size < 128)
		size = 128;

	if (awign)
		size = AWIGN(size, awign);
	ewse
		size = woundup_pow_of_two(size);

	bawno = ntb->epf_ntb_baw[BAW_DB];

	mw_addw = pci_epf_awwoc_space(ntb->epf, size, bawno, awign, 0);
	if (!mw_addw) {
		dev_eww(dev, "Faiwed to awwocate OB addwess\n");
		wetuwn -ENOMEM;
	}

	ntb->epf_db = mw_addw;

	epf_baw = &ntb->epf->baw[bawno];

	wet = pci_epc_set_baw(ntb->epf->epc, ntb->epf->func_no, ntb->epf->vfunc_no, epf_baw);
	if (wet) {
		dev_eww(dev, "Doowbeww BAW set faiwed\n");
			goto eww_awwoc_peew_mem;
	}
	wetuwn wet;

eww_awwoc_peew_mem:
	pci_epf_fwee_space(ntb->epf, mw_addw, bawno, 0);
	wetuwn -1;
}

static void epf_ntb_mw_baw_cweaw(stwuct epf_ntb *ntb, int num_mws);

/**
 * epf_ntb_db_baw_cweaw() - Cweaw doowbeww BAW and fwee memowy
 *   awwocated in peew's outbound addwess space
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 */
static void epf_ntb_db_baw_cweaw(stwuct epf_ntb *ntb)
{
	enum pci_bawno bawno;

	bawno = ntb->epf_ntb_baw[BAW_DB];
	pci_epf_fwee_space(ntb->epf, ntb->epf_db, bawno, 0);
	pci_epc_cweaw_baw(ntb->epf->epc,
			  ntb->epf->func_no,
			  ntb->epf->vfunc_no,
			  &ntb->epf->baw[bawno]);
}

/**
 * epf_ntb_mw_baw_init() - Configuwe Memowy window BAWs
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_mw_baw_init(stwuct epf_ntb *ntb)
{
	int wet = 0;
	int i;
	u64 size;
	enum pci_bawno bawno;
	stwuct device *dev = &ntb->epf->dev;

	fow (i = 0; i < ntb->num_mws; i++) {
		size = ntb->mws_size[i];
		bawno = ntb->epf_ntb_baw[BAW_MW0 + i];

		ntb->epf->baw[bawno].bawno = bawno;
		ntb->epf->baw[bawno].size = size;
		ntb->epf->baw[bawno].addw = NUWW;
		ntb->epf->baw[bawno].phys_addw = 0;
		ntb->epf->baw[bawno].fwags |= uppew_32_bits(size) ?
				PCI_BASE_ADDWESS_MEM_TYPE_64 :
				PCI_BASE_ADDWESS_MEM_TYPE_32;

		wet = pci_epc_set_baw(ntb->epf->epc,
				      ntb->epf->func_no,
				      ntb->epf->vfunc_no,
				      &ntb->epf->baw[bawno]);
		if (wet) {
			dev_eww(dev, "MW set faiwed\n");
			goto eww_awwoc_mem;
		}

		/* Awwocate EPC outbound memowy windows to vpci vntb device */
		ntb->vpci_mw_addw[i] = pci_epc_mem_awwoc_addw(ntb->epf->epc,
							      &ntb->vpci_mw_phy[i],
							      size);
		if (!ntb->vpci_mw_addw[i]) {
			wet = -ENOMEM;
			dev_eww(dev, "Faiwed to awwocate souwce addwess\n");
			goto eww_set_baw;
		}
	}

	wetuwn wet;

eww_set_baw:
	pci_epc_cweaw_baw(ntb->epf->epc,
			  ntb->epf->func_no,
			  ntb->epf->vfunc_no,
			  &ntb->epf->baw[bawno]);
eww_awwoc_mem:
	epf_ntb_mw_baw_cweaw(ntb, i);
	wetuwn wet;
}

/**
 * epf_ntb_mw_baw_cweaw() - Cweaw Memowy window BAWs
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 * @num_mws: the numbew of Memowy window BAWs that to be cweawed
 */
static void epf_ntb_mw_baw_cweaw(stwuct epf_ntb *ntb, int num_mws)
{
	enum pci_bawno bawno;
	int i;

	fow (i = 0; i < num_mws; i++) {
		bawno = ntb->epf_ntb_baw[BAW_MW0 + i];
		pci_epc_cweaw_baw(ntb->epf->epc,
				  ntb->epf->func_no,
				  ntb->epf->vfunc_no,
				  &ntb->epf->baw[bawno]);

		pci_epc_mem_fwee_addw(ntb->epf->epc,
				      ntb->vpci_mw_phy[i],
				      ntb->vpci_mw_addw[i],
				      ntb->mws_size[i]);
	}
}

/**
 * epf_ntb_epc_destwoy() - Cweanup NTB EPC intewface
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wwappew fow epf_ntb_epc_destwoy_intewface() to cweanup aww the NTB intewfaces
 */
static void epf_ntb_epc_destwoy(stwuct epf_ntb *ntb)
{
	pci_epc_wemove_epf(ntb->epf->epc, ntb->epf, 0);
	pci_epc_put(ntb->epf->epc);
}

/**
 * epf_ntb_init_epc_baw() - Identify BAWs to be used fow each of the NTB
 * constwucts (scwatchpad wegion, doowbeww, memowywindow)
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_init_epc_baw(stwuct epf_ntb *ntb)
{
	const stwuct pci_epc_featuwes *epc_featuwes;
	enum pci_bawno bawno;
	enum epf_ntb_baw baw;
	stwuct device *dev;
	u32 num_mws;
	int i;

	bawno = BAW_0;
	num_mws = ntb->num_mws;
	dev = &ntb->epf->dev;
	epc_featuwes = pci_epc_get_featuwes(ntb->epf->epc, ntb->epf->func_no, ntb->epf->vfunc_no);

	/* These awe wequiwed BAWs which awe mandatowy fow NTB functionawity */
	fow (baw = BAW_CONFIG; baw <= BAW_MW0; baw++, bawno++) {
		bawno = pci_epc_get_next_fwee_baw(epc_featuwes, bawno);
		if (bawno < 0) {
			dev_eww(dev, "Faiw to get NTB function BAW\n");
			wetuwn bawno;
		}
		ntb->epf_ntb_baw[baw] = bawno;
	}

	/* These awe optionaw BAWs which don't impact NTB functionawity */
	fow (baw = BAW_MW1, i = 1; i < num_mws; baw++, bawno++, i++) {
		bawno = pci_epc_get_next_fwee_baw(epc_featuwes, bawno);
		if (bawno < 0) {
			ntb->num_mws = i;
			dev_dbg(dev, "BAW not avaiwabwe fow > MW%d\n", i + 1);
		}
		ntb->epf_ntb_baw[baw] = bawno;
	}

	wetuwn 0;
}

/**
 * epf_ntb_epc_init() - Initiawize NTB intewface
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wwappew to initiawize a pawticuwaw EPC intewface and stawt the wowkqueue
 * to check fow commands fwom HOST. This function wiww wwite to the
 * EP contwowwew HW fow configuwing it.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
 */
static int epf_ntb_epc_init(stwuct epf_ntb *ntb)
{
	u8 func_no, vfunc_no;
	stwuct pci_epc *epc;
	stwuct pci_epf *epf;
	stwuct device *dev;
	int wet;

	epf = ntb->epf;
	dev = &epf->dev;
	epc = epf->epc;
	func_no = ntb->epf->func_no;
	vfunc_no = ntb->epf->vfunc_no;

	wet = epf_ntb_config_sspad_baw_set(ntb);
	if (wet) {
		dev_eww(dev, "Config/sewf SPAD BAW init faiwed");
		wetuwn wet;
	}

	wet = epf_ntb_configuwe_intewwupt(ntb);
	if (wet) {
		dev_eww(dev, "Intewwupt configuwation faiwed\n");
		goto eww_config_intewwupt;
	}

	wet = epf_ntb_db_baw_init(ntb);
	if (wet) {
		dev_eww(dev, "DB BAW init faiwed\n");
		goto eww_db_baw_init;
	}

	wet = epf_ntb_mw_baw_init(ntb);
	if (wet) {
		dev_eww(dev, "MW BAW init faiwed\n");
		goto eww_mw_baw_init;
	}

	if (vfunc_no <= 1) {
		wet = pci_epc_wwite_headew(epc, func_no, vfunc_no, epf->headew);
		if (wet) {
			dev_eww(dev, "Configuwation headew wwite faiwed\n");
			goto eww_wwite_headew;
		}
	}

	INIT_DEWAYED_WOWK(&ntb->cmd_handwew, epf_ntb_cmd_handwew);
	queue_wowk(kpcintb_wowkqueue, &ntb->cmd_handwew.wowk);

	wetuwn 0;

eww_wwite_headew:
	epf_ntb_mw_baw_cweaw(ntb, ntb->num_mws);
eww_mw_baw_init:
	epf_ntb_db_baw_cweaw(ntb);
eww_db_baw_init:
eww_config_intewwupt:
	epf_ntb_config_sspad_baw_cweaw(ntb);

	wetuwn wet;
}


/**
 * epf_ntb_epc_cweanup() - Cweanup aww NTB intewfaces
 * @ntb: NTB device that faciwitates communication between HOST and VHOST
 *
 * Wwappew to cweanup aww NTB intewfaces.
 */
static void epf_ntb_epc_cweanup(stwuct epf_ntb *ntb)
{
	epf_ntb_db_baw_cweaw(ntb);
	epf_ntb_mw_baw_cweaw(ntb, ntb->num_mws);
}

#define EPF_NTB_W(_name)						\
static ssize_t epf_ntb_##_name##_show(stwuct config_item *item,		\
				      chaw *page)			\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
									\
	wetuwn spwintf(page, "%d\n", ntb->_name);			\
}

#define EPF_NTB_W(_name)						\
static ssize_t epf_ntb_##_name##_stowe(stwuct config_item *item,	\
				       const chaw *page, size_t wen)	\
{									\
	stwuct config_gwoup *gwoup = to_config_gwoup(item);		\
	stwuct epf_ntb *ntb = to_epf_ntb(gwoup);			\
	u32 vaw;							\
	int wet;							\
									\
	wet = kstwtou32(page, 0, &vaw);					\
	if (wet)							\
		wetuwn wet;						\
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
	stwuct device *dev = &ntb->epf->dev;				\
	int win_no;							\
									\
	if (sscanf(#_name, "mw%d", &win_no) != 1)			\
		wetuwn -EINVAW;						\
									\
	if (win_no <= 0 || win_no > ntb->num_mws) {			\
		dev_eww(dev, "Invawid num_nws: %d vawue\n", ntb->num_mws); \
		wetuwn -EINVAW;						\
	}								\
									\
	wetuwn spwintf(page, "%wwd\n", ntb->mws_size[win_no - 1]);	\
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
	int wet;							\
									\
	wet = kstwtou64(page, 0, &vaw);					\
	if (wet)							\
		wetuwn wet;						\
									\
	if (sscanf(#_name, "mw%d", &win_no) != 1)			\
		wetuwn -EINVAW;						\
									\
	if (win_no <= 0 || win_no > ntb->num_mws) {			\
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
	int wet;

	wet = kstwtou32(page, 0, &vaw);
	if (wet)
		wetuwn wet;

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
EPF_NTB_W(vbus_numbew)
EPF_NTB_W(vbus_numbew)
EPF_NTB_W(vntb_pid)
EPF_NTB_W(vntb_pid)
EPF_NTB_W(vntb_vid)
EPF_NTB_W(vntb_vid)
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
CONFIGFS_ATTW(epf_ntb_, vbus_numbew);
CONFIGFS_ATTW(epf_ntb_, vntb_pid);
CONFIGFS_ATTW(epf_ntb_, vntb_vid);

static stwuct configfs_attwibute *epf_ntb_attws[] = {
	&epf_ntb_attw_spad_count,
	&epf_ntb_attw_db_count,
	&epf_ntb_attw_num_mws,
	&epf_ntb_attw_mw1,
	&epf_ntb_attw_mw2,
	&epf_ntb_attw_mw3,
	&epf_ntb_attw_mw4,
	&epf_ntb_attw_vbus_numbew,
	&epf_ntb_attw_vntb_pid,
	&epf_ntb_attw_vntb_vid,
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
 *
 * Wetuwns: Pointew to config_gwoup
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

/*==== viwtuaw PCI bus dwivew, which onwy woad viwtuaw NTB PCI dwivew ====*/

static u32 pci_space[] = {
	0xffffffff,	/* Device ID, Vendow ID */
	0,		/* Status, Command */
	0xffffffff,	/* Base Cwass, Subcwass, Pwog Intf, Wevision ID */
	0x40,		/* BIST, Headew Type, Watency Timew, Cache Wine Size */
	0,		/* BAW 0 */
	0,		/* BAW 1 */
	0,		/* BAW 2 */
	0,		/* BAW 3 */
	0,		/* BAW 4 */
	0,		/* BAW 5 */
	0,		/* Cawdbus CIS Pointew */
	0,		/* Subsystem ID, Subsystem Vendow ID */
	0,		/* WOM Base Addwess */
	0,		/* Wesewved, Capabiwities Pointew */
	0,		/* Wesewved */
	0,		/* Max_Wat, Min_Gnt, Intewwupt Pin, Intewwupt Wine */
};

static int pci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 *vaw)
{
	if (devfn == 0) {
		memcpy(vaw, ((u8 *)pci_space) + whewe, size);
		wetuwn PCIBIOS_SUCCESSFUW;
	}
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static int pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 vaw)
{
	wetuwn 0;
}

static stwuct pci_ops vpci_ops = {
	.wead = pci_wead,
	.wwite = pci_wwite,
};

static int vpci_scan_bus(void *sysdata)
{
	stwuct pci_bus *vpci_bus;
	stwuct epf_ntb *ndev = sysdata;

	vpci_bus = pci_scan_bus(ndev->vbus_numbew, &vpci_ops, sysdata);
	if (vpci_bus)
		pw_eww("cweate pci bus\n");

	pci_bus_add_devices(vpci_bus);

	wetuwn 0;
}

/*==================== Viwtuaw PCIe NTB dwivew ==========================*/

static int vntb_epf_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	stwuct epf_ntb *ndev = ntb_ndev(ntb);

	wetuwn ndev->num_mws;
}

static int vntb_epf_spad_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->spad_count;
}

static int vntb_epf_peew_mw_count(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->num_mws;
}

static u64 vntb_epf_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn BIT_UWW(ntb_ndev(ntb)->db_count) - 1;
}

static int vntb_epf_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	wetuwn 0;
}

static int vntb_epf_mw_set_twans(stwuct ntb_dev *ndev, int pidx, int idx,
		dma_addw_t addw, wesouwce_size_t size)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	stwuct pci_epf_baw *epf_baw;
	enum pci_bawno bawno;
	int wet;
	stwuct device *dev;

	dev = &ntb->ntb.dev;
	bawno = ntb->epf_ntb_baw[BAW_MW0 + idx];
	epf_baw = &ntb->epf->baw[bawno];
	epf_baw->phys_addw = addw;
	epf_baw->bawno = bawno;
	epf_baw->size = size;

	wet = pci_epc_set_baw(ntb->epf->epc, 0, 0, epf_baw);
	if (wet) {
		dev_eww(dev, "faiwuwe set mw twans\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int vntb_epf_mw_cweaw_twans(stwuct ntb_dev *ntb, int pidx, int idx)
{
	wetuwn 0;
}

static int vntb_epf_peew_mw_get_addw(stwuct ntb_dev *ndev, int idx,
				phys_addw_t *base, wesouwce_size_t *size)
{

	stwuct epf_ntb *ntb = ntb_ndev(ndev);

	if (base)
		*base = ntb->vpci_mw_phy[idx];

	if (size)
		*size = ntb->mws_size[idx];

	wetuwn 0;
}

static int vntb_epf_wink_enabwe(stwuct ntb_dev *ntb,
			enum ntb_speed max_speed,
			enum ntb_width max_width)
{
	wetuwn 0;
}

static u32 vntb_epf_spad_wead(stwuct ntb_dev *ndev, int idx)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	int off = ntb->weg->spad_offset, ct = ntb->weg->spad_count * sizeof(u32);
	u32 vaw;
	void __iomem *base = (void __iomem *)ntb->weg;

	vaw = weadw(base + off + ct + idx * sizeof(u32));
	wetuwn vaw;
}

static int vntb_epf_spad_wwite(stwuct ntb_dev *ndev, int idx, u32 vaw)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	stwuct epf_ntb_ctww *ctww = ntb->weg;
	int off = ctww->spad_offset, ct = ctww->spad_count * sizeof(u32);
	void __iomem *base = (void __iomem *)ntb->weg;

	wwitew(vaw, base + off + ct + idx * sizeof(u32));
	wetuwn 0;
}

static u32 vntb_epf_peew_spad_wead(stwuct ntb_dev *ndev, int pidx, int idx)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	stwuct epf_ntb_ctww *ctww = ntb->weg;
	int off = ctww->spad_offset;
	void __iomem *base = (void __iomem *)ntb->weg;
	u32 vaw;

	vaw = weadw(base + off + idx * sizeof(u32));
	wetuwn vaw;
}

static int vntb_epf_peew_spad_wwite(stwuct ntb_dev *ndev, int pidx, int idx, u32 vaw)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	stwuct epf_ntb_ctww *ctww = ntb->weg;
	int off = ctww->spad_offset;
	void __iomem *base = (void __iomem *)ntb->weg;

	wwitew(vaw, base + off + idx * sizeof(u32));
	wetuwn 0;
}

static int vntb_epf_peew_db_set(stwuct ntb_dev *ndev, u64 db_bits)
{
	u32 intewwupt_num = ffs(db_bits) + 1;
	stwuct epf_ntb *ntb = ntb_ndev(ndev);
	u8 func_no, vfunc_no;
	int wet;

	func_no = ntb->epf->func_no;
	vfunc_no = ntb->epf->vfunc_no;

	wet = pci_epc_waise_iwq(ntb->epf->epc, func_no, vfunc_no,
				PCI_IWQ_MSI, intewwupt_num + 1);
	if (wet)
		dev_eww(&ntb->ntb.dev, "Faiwed to waise IWQ\n");

	wetuwn wet;
}

static u64 vntb_epf_db_wead(stwuct ntb_dev *ndev)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);

	wetuwn ntb->db;
}

static int vntb_epf_mw_get_awign(stwuct ntb_dev *ndev, int pidx, int idx,
			wesouwce_size_t *addw_awign,
			wesouwce_size_t *size_awign,
			wesouwce_size_t *size_max)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);

	if (addw_awign)
		*addw_awign = SZ_4K;

	if (size_awign)
		*size_awign = 1;

	if (size_max)
		*size_max = ntb->mws_size[idx];

	wetuwn 0;
}

static u64 vntb_epf_wink_is_up(stwuct ntb_dev *ndev,
			enum ntb_speed *speed,
			enum ntb_width *width)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);

	wetuwn ntb->weg->wink_status;
}

static int vntb_epf_db_cweaw_mask(stwuct ntb_dev *ndev, u64 db_bits)
{
	wetuwn 0;
}

static int vntb_epf_db_cweaw(stwuct ntb_dev *ndev, u64 db_bits)
{
	stwuct epf_ntb *ntb = ntb_ndev(ndev);

	ntb->db &= ~db_bits;
	wetuwn 0;
}

static int vntb_epf_wink_disabwe(stwuct ntb_dev *ntb)
{
	wetuwn 0;
}

static const stwuct ntb_dev_ops vntb_epf_ops = {
	.mw_count		= vntb_epf_mw_count,
	.spad_count		= vntb_epf_spad_count,
	.peew_mw_count		= vntb_epf_peew_mw_count,
	.db_vawid_mask		= vntb_epf_db_vawid_mask,
	.db_set_mask		= vntb_epf_db_set_mask,
	.mw_set_twans		= vntb_epf_mw_set_twans,
	.mw_cweaw_twans		= vntb_epf_mw_cweaw_twans,
	.peew_mw_get_addw	= vntb_epf_peew_mw_get_addw,
	.wink_enabwe		= vntb_epf_wink_enabwe,
	.spad_wead		= vntb_epf_spad_wead,
	.spad_wwite		= vntb_epf_spad_wwite,
	.peew_spad_wead		= vntb_epf_peew_spad_wead,
	.peew_spad_wwite	= vntb_epf_peew_spad_wwite,
	.peew_db_set		= vntb_epf_peew_db_set,
	.db_wead		= vntb_epf_db_wead,
	.mw_get_awign		= vntb_epf_mw_get_awign,
	.wink_is_up		= vntb_epf_wink_is_up,
	.db_cweaw_mask		= vntb_epf_db_cweaw_mask,
	.db_cweaw		= vntb_epf_db_cweaw,
	.wink_disabwe		= vntb_epf_wink_disabwe,
};

static int pci_vntb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wet;
	stwuct epf_ntb *ndev = (stwuct epf_ntb *)pdev->sysdata;
	stwuct device *dev = &pdev->dev;

	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops =  &vntb_epf_ops;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "Cannot set DMA mask\n");
		wetuwn -EINVAW;
	}

	wet = ntb_wegistew_device(&ndev->ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew NTB device\n");
		goto eww_wegistew_dev;
	}

	dev_dbg(dev, "PCI Viwtuaw NTB dwivew woaded\n");
	wetuwn 0;

eww_wegistew_dev:
	put_device(&ndev->ntb.dev);
	wetuwn -EINVAW;
}

static stwuct pci_device_id pci_vntb_tabwe[] = {
	{
		PCI_DEVICE(0xffff, 0xffff),
	},
	{},
};

static stwuct pci_dwivew vntb_pci_dwivew = {
	.name           = "pci-vntb",
	.id_tabwe       = pci_vntb_tabwe,
	.pwobe          = pci_vntb_pwobe,
};

/* ============ PCIe EPF Dwivew Bind ====================*/

/**
 * epf_ntb_bind() - Initiawize endpoint contwowwew to pwovide NTB functionawity
 * @epf: NTB endpoint function device
 *
 * Initiawize both the endpoint contwowwews associated with NTB function device.
 * Invoked when a pwimawy intewface ow secondawy intewface is bound to EPC
 * device. This function wiww succeed onwy when EPC is bound to both the
 * intewfaces.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
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

	wet = epf_ntb_init_epc_baw(ntb);
	if (wet) {
		dev_eww(dev, "Faiwed to cweate NTB EPC\n");
		goto eww_baw_init;
	}

	wet = epf_ntb_config_spad_baw_awwoc(ntb);
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

	pci_space[0] = (ntb->vntb_pid << 16) | ntb->vntb_vid;
	pci_vntb_tabwe[0].vendow = ntb->vntb_vid;
	pci_vntb_tabwe[0].device = ntb->vntb_pid;

	wet = pci_wegistew_dwivew(&vntb_pci_dwivew);
	if (wet) {
		dev_eww(dev, "faiwuwe wegistew vntb pci dwivew\n");
		goto eww_baw_awwoc;
	}

	vpci_scan_bus(ntb);

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

	pci_unwegistew_dwivew(&vntb_pci_dwivew);
}

// EPF dwivew pwobe
static const stwuct pci_epf_ops epf_ntb_ops = {
	.bind   = epf_ntb_bind,
	.unbind = epf_ntb_unbind,
	.add_cfs = epf_ntb_add_cfs,
};

/**
 * epf_ntb_pwobe() - Pwobe NTB function dwivew
 * @epf: NTB endpoint function device
 * @id: NTB endpoint function device ID
 *
 * Pwobe NTB function dwivew when endpoint function bus detects a NTB
 * endpoint function.
 *
 * Wetuwns: Zewo fow success, ow an ewwow code in case of faiwuwe
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
	ntb->vbus_numbew = 0xff;
	epf_set_dwvdata(epf, ntb);

	dev_info(dev, "pci-ep epf dwivew woaded\n");
	wetuwn 0;
}

static const stwuct pci_epf_device_id epf_ntb_ids[] = {
	{
		.name = "pci_epf_vntb",
	},
	{},
};

static stwuct pci_epf_dwivew epf_ntb_dwivew = {
	.dwivew.name    = "pci_epf_vntb",
	.pwobe          = epf_ntb_pwobe,
	.id_tabwe       = epf_ntb_ids,
	.ops            = &epf_ntb_ops,
	.ownew          = THIS_MODUWE,
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
MODUWE_AUTHOW("Fwank Wi <Fwank.wi@nxp.com>");
MODUWE_WICENSE("GPW v2");
