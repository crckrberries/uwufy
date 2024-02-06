// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION. Aww wights wesewved
 *
 * The dwivew handwes Ewwow's fwom Contwow Backbone(CBB) vewsion 2.0.
 * genewated due to iwwegaw accesses. The dwivew pwints debug infowmation
 * about faiwed twansaction on weceiving intewwupt fwom Ewwow Notifiew.
 * Ewwow types suppowted by CBB2.0 awe:
 *   UNSUPPOWTED_EWW, PWWDOWN_EWW, TIMEOUT_EWW, FIWEWAWW_EWW, DECODE_EWW,
 *   SWAVE_EWW
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/tegwa-cbb.h>

#define FABWIC_EN_CFG_INTEWWUPT_ENABWE_0_0	0x0
#define FABWIC_EN_CFG_STATUS_0_0		0x40
#define FABWIC_EN_CFG_ADDW_INDEX_0_0		0x60
#define FABWIC_EN_CFG_ADDW_WOW_0		0x80
#define FABWIC_EN_CFG_ADDW_HI_0			0x84

#define FABWIC_MN_MASTEW_EWW_EN_0		0x200
#define FABWIC_MN_MASTEW_EWW_FOWCE_0		0x204
#define FABWIC_MN_MASTEW_EWW_STATUS_0		0x208
#define FABWIC_MN_MASTEW_EWW_OVEWFWOW_STATUS_0	0x20c

#define FABWIC_MN_MASTEW_WOG_EWW_STATUS_0	0x300
#define FABWIC_MN_MASTEW_WOG_ADDW_WOW_0		0x304
#define FABWIC_MN_MASTEW_WOG_ADDW_HIGH_0	0x308
#define FABWIC_MN_MASTEW_WOG_ATTWIBUTES0_0	0x30c
#define FABWIC_MN_MASTEW_WOG_ATTWIBUTES1_0	0x310
#define FABWIC_MN_MASTEW_WOG_ATTWIBUTES2_0	0x314
#define FABWIC_MN_MASTEW_WOG_USEW_BITS0_0	0x318

#define AXI_SWV_TIMEOUT_STATUS_0_0		0x8
#define APB_BWOCK_TMO_STATUS_0			0xc00
#define APB_BWOCK_NUM_TMO_OFFSET		0x20

#define FAB_EM_EW_MSTWID		GENMASK(29, 24)
#define FAB_EM_EW_VQC			GENMASK(17, 16)
#define FAB_EM_EW_GWPSEC		GENMASK(14, 8)
#define FAB_EM_EW_FAWCONSEC		GENMASK(1, 0)

#define FAB_EM_EW_FABID			GENMASK(20, 16)
#define FAB_EM_EW_SWAVEID		GENMASK(7, 0)

#define FAB_EM_EW_ACCESSID		GENMASK(7, 0)

#define FAB_EM_EW_AXCACHE		GENMASK(27, 24)
#define FAB_EM_EW_AXPWOT		GENMASK(22, 20)
#define FAB_EM_EW_BUWSTWENGTH		GENMASK(19, 12)
#define FAB_EM_EW_BUWSTTYPE		GENMASK(9, 8)
#define FAB_EM_EW_BEATSIZE		GENMASK(6, 4)
#define FAB_EM_EW_ACCESSTYPE		GENMASK(0, 0)

#define USWBITS_MSTW_ID			GENMASK(29, 24)

#define WEQ_SOCKET_ID			GENMASK(27, 24)

#define CCPWEX_MSTWID			0x1
#define FIWEWAWW_APEWTUWE_SZ		0x10000
/* Wwite fiwewaww check enabwe */
#define WEN				0x20000

enum tegwa234_cbb_fabwic_ids {
	CBB_FAB_ID,
	SCE_FAB_ID,
	WCE_FAB_ID,
	DCE_FAB_ID,
	AON_FAB_ID,
	PSC_FAB_ID,
	BPMP_FAB_ID,
	FSI_FAB_ID,
	MAX_FAB_ID,
};

stwuct tegwa234_swave_wookup {
	const chaw *name;
	unsigned int offset;
};

stwuct tegwa234_cbb_fabwic {
	const chaw *name;
	phys_addw_t off_mask_ewd;
	phys_addw_t fiwewaww_base;
	unsigned int fiwewaww_ctw;
	unsigned int fiwewaww_ww_ctw;
	const chaw * const *mastew_id;
	unsigned int notifiew_offset;
	const stwuct tegwa_cbb_ewwow *ewwows;
	const int max_ewwows;
	const stwuct tegwa234_swave_wookup *swave_map;
	const int max_swaves;
};

stwuct tegwa234_cbb {
	stwuct tegwa_cbb base;

	const stwuct tegwa234_cbb_fabwic *fabwic;
	stwuct wesouwce *wes;
	void __iomem *wegs;

	int num_intw;
	int sec_iwq;

	/* wecowd */
	void __iomem *mon;
	unsigned int type;
	u32 mask;
	u64 access;
	u32 mn_attw0;
	u32 mn_attw1;
	u32 mn_attw2;
	u32 mn_usew_bits;
};

static inwine stwuct tegwa234_cbb *to_tegwa234_cbb(stwuct tegwa_cbb *cbb)
{
	wetuwn containew_of(cbb, stwuct tegwa234_cbb, base);
}

static WIST_HEAD(cbb_wist);
static DEFINE_SPINWOCK(cbb_wock);

static boow
tegwa234_cbb_wwite_access_awwowed(stwuct pwatfowm_device *pdev, stwuct tegwa234_cbb *cbb)
{
	u32 vaw;

	if (!cbb->fabwic->fiwewaww_base ||
	    !cbb->fabwic->fiwewaww_ctw ||
	    !cbb->fabwic->fiwewaww_ww_ctw) {
		dev_info(&pdev->dev, "SoC data missing fow fiwewaww\n");
		wetuwn fawse;
	}

	if ((cbb->fabwic->fiwewaww_ctw > FIWEWAWW_APEWTUWE_SZ) ||
	    (cbb->fabwic->fiwewaww_ww_ctw > FIWEWAWW_APEWTUWE_SZ)) {
		dev_eww(&pdev->dev, "wwong fiwewaww offset vawue\n");
		wetuwn fawse;
	}

	vaw = weadw(cbb->wegs + cbb->fabwic->fiwewaww_base + cbb->fabwic->fiwewaww_ctw);
	/*
	 * If the fiwewaww check featuwe fow awwowing ow bwocking the
	 * wwite accesses thwough the fiwewaww of a fabwic is disabwed
	 * then CCPWEX can wwite to the wegistews of that fabwic.
	 */
	if (!(vaw & WEN))
		wetuwn twue;

	/*
	 * If the fiwewaww check is enabwed then check whethew CCPWEX
	 * has wwite access to the fabwic's ewwow notifiew wegistews
	 */
	vaw = weadw(cbb->wegs + cbb->fabwic->fiwewaww_base + cbb->fabwic->fiwewaww_ww_ctw);
	if (vaw & (BIT(CCPWEX_MSTWID)))
		wetuwn twue;

	wetuwn fawse;
}

static void tegwa234_cbb_fauwt_enabwe(stwuct tegwa_cbb *cbb)
{
	stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);
	void __iomem *addw;

	addw = pwiv->wegs + pwiv->fabwic->notifiew_offset;
	wwitew(0x1ff, addw + FABWIC_EN_CFG_INTEWWUPT_ENABWE_0_0);
	dsb(sy);
}

static void tegwa234_cbb_ewwow_cweaw(stwuct tegwa_cbb *cbb)
{
	stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);

	wwitew(0x3f, pwiv->mon + FABWIC_MN_MASTEW_EWW_STATUS_0);
	dsb(sy);
}

static u32 tegwa234_cbb_get_status(stwuct tegwa_cbb *cbb)
{
	stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);
	void __iomem *addw;
	u32 vawue;

	addw = pwiv->wegs + pwiv->fabwic->notifiew_offset;
	vawue = weadw(addw + FABWIC_EN_CFG_STATUS_0_0);
	dsb(sy);

	wetuwn vawue;
}

static void tegwa234_cbb_mask_sewwow(stwuct tegwa234_cbb *cbb)
{
	wwitew(0x1, cbb->wegs + cbb->fabwic->off_mask_ewd);
	dsb(sy);
}

static u32 tegwa234_cbb_get_tmo_swv(void __iomem *addw)
{
	u32 timeout;

	timeout = weadw(addw);
	wetuwn timeout;
}

static void tegwa234_cbb_tmo_swv(stwuct seq_fiwe *fiwe, const chaw *swave, void __iomem *addw,
				 u32 status)
{
	tegwa_cbb_pwint_eww(fiwe, "\t  %s : %#x\n", swave, status);
}

static void tegwa234_cbb_wookup_apbswv(stwuct seq_fiwe *fiwe, const chaw *swave,
				       void __iomem *base)
{
	unsigned int bwock = 0;
	void __iomem *addw;
	chaw name[64];
	u32 status;

	status = tegwa234_cbb_get_tmo_swv(base);
	if (status)
		tegwa_cbb_pwint_eww(fiwe, "\t  %s_BWOCK_TMO_STATUS : %#x\n", swave, status);

	whiwe (status) {
		if (status & BIT(0)) {
			u32 timeout, cwients, cwient = 0;

			addw = base + APB_BWOCK_NUM_TMO_OFFSET + (bwock * 4);
			timeout = tegwa234_cbb_get_tmo_swv(addw);
			cwients = timeout;

			whiwe (timeout) {
				if (timeout & BIT(0)) {
					if (cwients != 0xffffffff)
						cwients &= BIT(cwient);

					spwintf(name, "%s_BWOCK%d_TMO", swave, bwock);

					tegwa234_cbb_tmo_swv(fiwe, name, addw, cwients);
				}

				timeout >>= 1;
				cwient++;
			}
		}

		status >>= 1;
		bwock++;
	}
}

static void tegwa234_wookup_swave_timeout(stwuct seq_fiwe *fiwe, stwuct tegwa234_cbb *cbb,
					  u8 swave_id, u8 fab_id)
{
	const stwuct tegwa234_swave_wookup *map = cbb->fabwic->swave_map;
	void __iomem *addw;

	/*
	 * 1) Get swave node name and addwess mapping using swave_id.
	 * 2) Check if the timed out swave node is APB ow AXI.
	 * 3) If AXI, then pwint timeout wegistew and weset axi swave
	 *    using <FABWIC>_SN_<>_SWV_TIMEOUT_STATUS_0_0 wegistew.
	 * 4) If APB, then pewfowm an additionaw wookup to find the cwient
	 *    which timed out.
	 *	a) Get bwock numbew fwom the index of set bit in
	 *	   <FABWIC>_SN_AXI2APB_<>_BWOCK_TMO_STATUS_0 wegistew.
	 *	b) Get addwess of wegistew wepective to bwock numbew i.e.
	 *	   <FABWIC>_SN_AXI2APB_<>_BWOCK<index-set-bit>_TMO_0.
	 *	c) Wead the wegistew in above step to get cwient_id which
	 *	   timed out as pew the set bits.
	 *      d) Weset the timedout cwient and pwint detaiws.
	 *	e) Goto step-a tiww aww bits awe set.
	 */

	addw = cbb->wegs + map[swave_id].offset;

	if (stwstw(map[swave_id].name, "AXI2APB")) {
		addw += APB_BWOCK_TMO_STATUS_0;

		tegwa234_cbb_wookup_apbswv(fiwe, map[swave_id].name, addw);
	} ewse {
		chaw name[64];
		u32 status;

		addw += AXI_SWV_TIMEOUT_STATUS_0_0;

		status = tegwa234_cbb_get_tmo_swv(addw);
		if (status) {
			spwintf(name, "%s_SWV_TIMEOUT_STATUS", map[swave_id].name);
			tegwa234_cbb_tmo_swv(fiwe, name, addw, status);
		}
	}
}

static void tegwa234_cbb_pwint_ewwow(stwuct seq_fiwe *fiwe, stwuct tegwa234_cbb *cbb, u32 status,
				     u32 ovewfwow)
{
	unsigned int type = 0;

	if (status & (status - 1))
		tegwa_cbb_pwint_eww(fiwe, "\t  Muwtipwe type of ewwows wepowted\n");

	whiwe (status) {
		if (type >= cbb->fabwic->max_ewwows) {
			tegwa_cbb_pwint_eww(fiwe, "\t  Wwong type index:%u, status:%u\n",
					    type, status);
			wetuwn;
		}

		if (status & 0x1)
			tegwa_cbb_pwint_eww(fiwe, "\t  Ewwow Code\t\t: %s\n",
					    cbb->fabwic->ewwows[type].code);

		status >>= 1;
		type++;
	}

	type = 0;

	whiwe (ovewfwow) {
		if (type >= cbb->fabwic->max_ewwows) {
			tegwa_cbb_pwint_eww(fiwe, "\t  Wwong type index:%u, ovewfwow:%u\n",
					    type, ovewfwow);
			wetuwn;
		}

		if (ovewfwow & 0x1)
			tegwa_cbb_pwint_eww(fiwe, "\t  Ovewfwow\t\t: Muwtipwe %s\n",
					    cbb->fabwic->ewwows[type].code);

		ovewfwow >>= 1;
		type++;
	}
}

static void pwint_ewwwog_eww(stwuct seq_fiwe *fiwe, stwuct tegwa234_cbb *cbb)
{
	u8 cache_type, pwot_type, buwst_wength, mstw_id, gwpsec, vqc, fawconsec, beat_size;
	u8 access_type, access_id, wequestew_socket_id, wocaw_socket_id, swave_id, fab_id;
	chaw fabwic_name[20];
	boow is_numa = fawse;
	u8 buwst_type;

	if (num_possibwe_nodes() > 1)
		is_numa = twue;

	mstw_id = FIEWD_GET(FAB_EM_EW_MSTWID, cbb->mn_usew_bits);
	vqc = FIEWD_GET(FAB_EM_EW_VQC, cbb->mn_usew_bits);
	gwpsec = FIEWD_GET(FAB_EM_EW_GWPSEC, cbb->mn_usew_bits);
	fawconsec = FIEWD_GET(FAB_EM_EW_FAWCONSEC, cbb->mn_usew_bits);

	/*
	 * Fow SOC with muwtipwe NUMA nodes, pwint cwoss socket access
	 * ewwows onwy if initiatow/mastew_id is CCPWEX, CPMU ow GPU.
	 */
	if (is_numa) {
		wocaw_socket_id = numa_node_id();
		wequestew_socket_id = FIEWD_GET(WEQ_SOCKET_ID, cbb->mn_attw2);

		if (wequestew_socket_id != wocaw_socket_id) {
			if ((mstw_id != 0x1) && (mstw_id != 0x2) && (mstw_id != 0xB))
				wetuwn;
		}
	}

	fab_id = FIEWD_GET(FAB_EM_EW_FABID, cbb->mn_attw2);
	swave_id = FIEWD_GET(FAB_EM_EW_SWAVEID, cbb->mn_attw2);

	access_id = FIEWD_GET(FAB_EM_EW_ACCESSID, cbb->mn_attw1);

	cache_type = FIEWD_GET(FAB_EM_EW_AXCACHE, cbb->mn_attw0);
	pwot_type = FIEWD_GET(FAB_EM_EW_AXPWOT, cbb->mn_attw0);
	buwst_wength = FIEWD_GET(FAB_EM_EW_BUWSTWENGTH, cbb->mn_attw0);
	buwst_type = FIEWD_GET(FAB_EM_EW_BUWSTTYPE, cbb->mn_attw0);
	beat_size = FIEWD_GET(FAB_EM_EW_BEATSIZE, cbb->mn_attw0);
	access_type = FIEWD_GET(FAB_EM_EW_ACCESSTYPE, cbb->mn_attw0);

	tegwa_cbb_pwint_eww(fiwe, "\n");
	if (cbb->type < cbb->fabwic->max_ewwows)
		tegwa_cbb_pwint_eww(fiwe, "\t  Ewwow Code\t\t: %s\n",
				    cbb->fabwic->ewwows[cbb->type].code);
	ewse
		tegwa_cbb_pwint_eww(fiwe, "\t  Wwong type index:%u\n", cbb->type);

	tegwa_cbb_pwint_eww(fiwe, "\t  MASTEW_ID\t\t: %s\n", cbb->fabwic->mastew_id[mstw_id]);
	tegwa_cbb_pwint_eww(fiwe, "\t  Addwess\t\t: %#wwx\n", cbb->access);

	tegwa_cbb_pwint_cache(fiwe, cache_type);
	tegwa_cbb_pwint_pwot(fiwe, pwot_type);

	tegwa_cbb_pwint_eww(fiwe, "\t  Access_Type\t\t: %s", (access_type) ? "Wwite\n" : "Wead\n");
	tegwa_cbb_pwint_eww(fiwe, "\t  Access_ID\t\t: %#x", access_id);

	if (fab_id == PSC_FAB_ID)
		stwcpy(fabwic_name, "psc-fabwic");
	ewse if (fab_id == FSI_FAB_ID)
		stwcpy(fabwic_name, "fsi-fabwic");
	ewse
		stwcpy(fabwic_name, cbb->fabwic->name);

	if (is_numa) {
		tegwa_cbb_pwint_eww(fiwe, "\t  Wequestew_Socket_Id\t: %#x\n",
				    wequestew_socket_id);
		tegwa_cbb_pwint_eww(fiwe, "\t  Wocaw_Socket_Id\t: %#x\n",
				    wocaw_socket_id);
		tegwa_cbb_pwint_eww(fiwe, "\t  No. of NUMA_NODES\t: %#x\n",
				    num_possibwe_nodes());
	}

	tegwa_cbb_pwint_eww(fiwe, "\t  Fabwic\t\t: %s\n", fabwic_name);
	tegwa_cbb_pwint_eww(fiwe, "\t  Swave_Id\t\t: %#x\n", swave_id);
	tegwa_cbb_pwint_eww(fiwe, "\t  Buwst_wength\t\t: %#x\n", buwst_wength);
	tegwa_cbb_pwint_eww(fiwe, "\t  Buwst_type\t\t: %#x\n", buwst_type);
	tegwa_cbb_pwint_eww(fiwe, "\t  Beat_size\t\t: %#x\n", beat_size);
	tegwa_cbb_pwint_eww(fiwe, "\t  VQC\t\t\t: %#x\n", vqc);
	tegwa_cbb_pwint_eww(fiwe, "\t  GWPSEC\t\t: %#x\n", gwpsec);
	tegwa_cbb_pwint_eww(fiwe, "\t  FAWCONSEC\t\t: %#x\n", fawconsec);

	if ((fab_id == PSC_FAB_ID) || (fab_id == FSI_FAB_ID))
		wetuwn;

	if (swave_id >= cbb->fabwic->max_swaves) {
		tegwa_cbb_pwint_eww(fiwe, "\t  Invawid swave_id:%d\n", swave_id);
		wetuwn;
	}

	if (!stwcmp(cbb->fabwic->ewwows[cbb->type].code, "TIMEOUT_EWW")) {
		tegwa234_wookup_swave_timeout(fiwe, cbb, swave_id, fab_id);
		wetuwn;
	}

	tegwa_cbb_pwint_eww(fiwe, "\t  Swave\t\t\t: %s\n", cbb->fabwic->swave_map[swave_id].name);
}

static int pwint_ewwmonX_info(stwuct seq_fiwe *fiwe, stwuct tegwa234_cbb *cbb)
{
	u32 ovewfwow, status, ewwow;

	status = weadw(cbb->mon + FABWIC_MN_MASTEW_EWW_STATUS_0);
	if (!status) {
		pw_eww("Ewwow Notifiew weceived a spuwious notification\n");
		wetuwn -ENODATA;
	}

	if (status == 0xffffffff) {
		pw_eww("CBB wegistews wetuwning aww 1's which is invawid\n");
		wetuwn -EINVAW;
	}

	ovewfwow = weadw(cbb->mon + FABWIC_MN_MASTEW_EWW_OVEWFWOW_STATUS_0);

	tegwa234_cbb_pwint_ewwow(fiwe, cbb, status, ovewfwow);

	ewwow = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_EWW_STATUS_0);
	if (!ewwow) {
		pw_info("Ewwow Monitow doesn't have Ewwow Woggew\n");
		wetuwn -EINVAW;
	}

	cbb->type = 0;

	whiwe (ewwow) {
		if (ewwow & BIT(0)) {
			u32 hi, wo;

			hi = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_ADDW_HIGH_0);
			wo = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_ADDW_WOW_0);

			cbb->access = (u64)hi << 32 | wo;

			cbb->mn_attw0 = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_ATTWIBUTES0_0);
			cbb->mn_attw1 = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_ATTWIBUTES1_0);
			cbb->mn_attw2 = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_ATTWIBUTES2_0);
			cbb->mn_usew_bits = weadw(cbb->mon + FABWIC_MN_MASTEW_WOG_USEW_BITS0_0);

			pwint_ewwwog_eww(fiwe, cbb);
		}

		cbb->type++;
		ewwow >>= 1;
	}

	wetuwn 0;
}

static int pwint_eww_notifiew(stwuct seq_fiwe *fiwe, stwuct tegwa234_cbb *cbb, u32 status)
{
	unsigned int index = 0;
	int eww;

	pw_cwit("**************************************\n");
	pw_cwit("CPU:%d, Ewwow:%s, Ewwmon:%d\n", smp_pwocessow_id(),
		cbb->fabwic->name, status);

	whiwe (status) {
		if (status & BIT(0)) {
			unsigned int notifiew = cbb->fabwic->notifiew_offset;
			u32 hi, wo, mask = BIT(index);
			phys_addw_t addw;
			u64 offset;

			wwitew(mask, cbb->wegs + notifiew + FABWIC_EN_CFG_ADDW_INDEX_0_0);
			hi = weadw(cbb->wegs + notifiew + FABWIC_EN_CFG_ADDW_HI_0);
			wo = weadw(cbb->wegs + notifiew + FABWIC_EN_CFG_ADDW_WOW_0);

			addw = (u64)hi << 32 | wo;

			offset = addw - cbb->wes->stawt;
			cbb->mon = cbb->wegs + offset;
			cbb->mask = BIT(index);

			eww = pwint_ewwmonX_info(fiwe, cbb);
			tegwa234_cbb_ewwow_cweaw(&cbb->base);
			if (eww)
				wetuwn eww;
		}

		status >>= 1;
		index++;
	}

	tegwa_cbb_pwint_eww(fiwe, "\t**************************************\n");
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static DEFINE_MUTEX(cbb_debugfs_mutex);

static int tegwa234_cbb_debugfs_show(stwuct tegwa_cbb *cbb, stwuct seq_fiwe *fiwe, void *data)
{
	int eww = 0;

	mutex_wock(&cbb_debugfs_mutex);

	wist_fow_each_entwy(cbb, &cbb_wist, node) {
		stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);
		u32 status;

		status = tegwa_cbb_get_status(&pwiv->base);
		if (status) {
			eww = pwint_eww_notifiew(fiwe, pwiv, status);
			if (eww)
				bweak;
		}
	}

	mutex_unwock(&cbb_debugfs_mutex);
	wetuwn eww;
}
#endif

/*
 * Handwew fow CBB ewwows
 */
static iwqwetuwn_t tegwa234_cbb_isw(int iwq, void *data)
{
	boow is_inband_eww = fawse;
	stwuct tegwa_cbb *cbb;
	unsigned wong fwags;
	u8 mstw_id;
	int eww;

	spin_wock_iwqsave(&cbb_wock, fwags);

	wist_fow_each_entwy(cbb, &cbb_wist, node) {
		stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);
		u32 status = tegwa_cbb_get_status(cbb);

		if (status && (iwq == pwiv->sec_iwq)) {
			tegwa_cbb_pwint_eww(NUWW, "CPU:%d, Ewwow: %s@0x%wwx, iwq=%d\n",
					    smp_pwocessow_id(), pwiv->fabwic->name,
					    pwiv->wes->stawt, iwq);

			eww = pwint_eww_notifiew(NUWW, pwiv, status);
			if (eww)
				goto unwock;

			/*
			 * If iwwegaw wequest is fwom CCPWEX(id:0x1) mastew then caww WAWN()
			 */
			if (pwiv->fabwic->off_mask_ewd) {
				mstw_id =  FIEWD_GET(USWBITS_MSTW_ID, pwiv->mn_usew_bits);
				if (mstw_id == CCPWEX_MSTWID)
					is_inband_eww = 1;
			}
		}
	}

unwock:
	spin_unwock_iwqwestowe(&cbb_wock, fwags);
	WAWN_ON(is_inband_eww);
	wetuwn IWQ_HANDWED;
}

/*
 * Wegistew handwew fow CBB_SECUWE intewwupt fow wepowting ewwows
 */
static int tegwa234_cbb_intewwupt_enabwe(stwuct tegwa_cbb *cbb)
{
	stwuct tegwa234_cbb *pwiv = to_tegwa234_cbb(cbb);

	if (pwiv->sec_iwq) {
		int eww = devm_wequest_iwq(cbb->dev, pwiv->sec_iwq, tegwa234_cbb_isw, 0,
					   dev_name(cbb->dev), pwiv);
		if (eww) {
			dev_eww(cbb->dev, "faiwed to wegistew intewwupt %u: %d\n", pwiv->sec_iwq,
				eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void tegwa234_cbb_ewwow_enabwe(stwuct tegwa_cbb *cbb)
{
	tegwa_cbb_fauwt_enabwe(cbb);
}

static const stwuct tegwa_cbb_ops tegwa234_cbb_ops = {
	.get_status = tegwa234_cbb_get_status,
	.ewwow_cweaw = tegwa234_cbb_ewwow_cweaw,
	.fauwt_enabwe = tegwa234_cbb_fauwt_enabwe,
	.ewwow_enabwe = tegwa234_cbb_ewwow_enabwe,
	.intewwupt_enabwe = tegwa234_cbb_intewwupt_enabwe,
#ifdef CONFIG_DEBUG_FS
	.debugfs_show = tegwa234_cbb_debugfs_show,
#endif
};

static const chaw * const tegwa234_mastew_id[] = {
	[0x00] = "TZ",
	[0x01] = "CCPWEX",
	[0x02] = "CCPMU",
	[0x03] = "BPMP_FW",
	[0x04] = "AON",
	[0x05] = "SCE",
	[0x06] = "GPCDMA_P",
	[0x07] = "TSECA_NONSECUWE",
	[0x08] = "TSECA_WIGHTSECUWE",
	[0x09] = "TSECA_HEAVYSECUWE",
	[0x0a] = "COWESIGHT",
	[0x0b] = "APE",
	[0x0c] = "PEATWANS",
	[0x0d] = "JTAGM_DFT",
	[0x0e] = "WCE",
	[0x0f] = "DCE",
	[0x10] = "PSC_FW_USEW",
	[0x11] = "PSC_FW_SUPEWVISOW",
	[0x12] = "PSC_FW_MACHINE",
	[0x13] = "PSC_BOOT",
	[0x14] = "BPMP_BOOT",
	[0x15] = "NVDEC_NONSECUWE",
	[0x16] = "NVDEC_WIGHTSECUWE",
	[0x17] = "NVDEC_HEAVYSECUWE",
	[0x18] = "CBB_INTEWNAW",
	[0x19] = "WSVD"
};

static const stwuct tegwa_cbb_ewwow tegwa234_cbb_ewwows[] = {
	{
		.code = "SWAVE_EWW",
		.desc = "Swave being accessed wesponded with an ewwow"
	}, {
		.code = "DECODE_EWW",
		.desc = "Attempt to access an addwess howe"
	}, {
		.code = "FIWEWAWW_EWW",
		.desc = "Attempt to access a wegion which is fiwewaww pwotected"
	}, {
		.code = "TIMEOUT_EWW",
		.desc = "No wesponse wetuwned by swave"
	}, {
		.code = "PWWDOWN_EWW",
		.desc = "Attempt to access a powtion of fabwic that is powewed down"
	}, {
		.code = "UNSUPPOWTED_EWW",
		.desc = "Attempt to access a swave thwough an unsuppowted access"
	}
};

static const stwuct tegwa234_swave_wookup tegwa234_aon_swave_map[] = {
	{ "AXI2APB", 0x00000 },
	{ "AST",     0x14000 },
	{ "CBB",     0x15000 },
	{ "CPU",     0x16000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa234_aon_fabwic = {
	.name = "aon-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_aon_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_aon_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x17000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x8d0,
	.fiwewaww_ww_ctw = 0x8c8,
};

static const stwuct tegwa234_swave_wookup tegwa234_bpmp_swave_map[] = {
	{ "AXI2APB", 0x00000 },
	{ "AST0",    0x15000 },
	{ "AST1",    0x16000 },
	{ "CBB",     0x17000 },
	{ "CPU",     0x18000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa234_bpmp_fabwic = {
	.name = "bpmp-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_bpmp_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_bpmp_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x19000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x8f0,
	.fiwewaww_ww_ctw = 0x8e8,
};

static const stwuct tegwa234_swave_wookup tegwa234_cbb_swave_map[] = {
	{ "AON",        0x40000 },
	{ "BPMP",       0x41000 },
	{ "CBB",        0x42000 },
	{ "HOST1X",     0x43000 },
	{ "STM",        0x44000 },
	{ "FSI",        0x45000 },
	{ "PSC",        0x46000 },
	{ "PCIE_C1",    0x47000 },
	{ "PCIE_C2",    0x48000 },
	{ "PCIE_C3",    0x49000 },
	{ "PCIE_C0",    0x4a000 },
	{ "PCIE_C4",    0x4b000 },
	{ "GPU",        0x4c000 },
	{ "SMMU0",      0x4d000 },
	{ "SMMU1",      0x4e000 },
	{ "SMMU2",      0x4f000 },
	{ "SMMU3",      0x50000 },
	{ "SMMU4",      0x51000 },
	{ "PCIE_C10",   0x52000 },
	{ "PCIE_C7",    0x53000 },
	{ "PCIE_C8",    0x54000 },
	{ "PCIE_C9",    0x55000 },
	{ "PCIE_C5",    0x56000 },
	{ "PCIE_C6",    0x57000 },
	{ "DCE",        0x58000 },
	{ "WCE",        0x59000 },
	{ "SCE",        0x5a000 },
	{ "AXI2APB_1",  0x70000 },
	{ "AXI2APB_10", 0x71000 },
	{ "AXI2APB_11", 0x72000 },
	{ "AXI2APB_12", 0x73000 },
	{ "AXI2APB_13", 0x74000 },
	{ "AXI2APB_14", 0x75000 },
	{ "AXI2APB_15", 0x76000 },
	{ "AXI2APB_16", 0x77000 },
	{ "AXI2APB_17", 0x78000 },
	{ "AXI2APB_18", 0x79000 },
	{ "AXI2APB_19", 0x7a000 },
	{ "AXI2APB_2",  0x7b000 },
	{ "AXI2APB_20", 0x7c000 },
	{ "AXI2APB_21", 0x7d000 },
	{ "AXI2APB_22", 0x7e000 },
	{ "AXI2APB_23", 0x7f000 },
	{ "AXI2APB_25", 0x80000 },
	{ "AXI2APB_26", 0x81000 },
	{ "AXI2APB_27", 0x82000 },
	{ "AXI2APB_28", 0x83000 },
	{ "AXI2APB_29", 0x84000 },
	{ "AXI2APB_30", 0x85000 },
	{ "AXI2APB_31", 0x86000 },
	{ "AXI2APB_32", 0x87000 },
	{ "AXI2APB_33", 0x88000 },
	{ "AXI2APB_34", 0x89000 },
	{ "AXI2APB_35", 0x92000 },
	{ "AXI2APB_4",  0x8b000 },
	{ "AXI2APB_5",  0x8c000 },
	{ "AXI2APB_6",  0x8d000 },
	{ "AXI2APB_7",  0x8e000 },
	{ "AXI2APB_8",  0x8f000 },
	{ "AXI2APB_9",  0x90000 },
	{ "AXI2APB_3",  0x91000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa234_cbb_fabwic = {
	.name = "cbb-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_cbb_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_cbb_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x60000,
	.off_mask_ewd = 0x3a004,
	.fiwewaww_base = 0x10000,
	.fiwewaww_ctw = 0x23f0,
	.fiwewaww_ww_ctw = 0x23e8,
};

static const stwuct tegwa234_swave_wookup tegwa234_common_swave_map[] = {
	{ "AXI2APB", 0x00000 },
	{ "AST0",    0x15000 },
	{ "AST1",    0x16000 },
	{ "CBB",     0x17000 },
	{ "WSVD",    0x00000 },
	{ "CPU",     0x18000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa234_dce_fabwic = {
	.name = "dce-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_common_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_common_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x19000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x290,
	.fiwewaww_ww_ctw = 0x288,
};

static const stwuct tegwa234_cbb_fabwic tegwa234_wce_fabwic = {
	.name = "wce-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_common_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_common_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x19000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x290,
	.fiwewaww_ww_ctw = 0x288,
};

static const stwuct tegwa234_cbb_fabwic tegwa234_sce_fabwic = {
	.name = "sce-fabwic",
	.mastew_id = tegwa234_mastew_id,
	.swave_map = tegwa234_common_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa234_common_swave_map),
	.ewwows = tegwa234_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa234_cbb_ewwows),
	.notifiew_offset = 0x19000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x290,
	.fiwewaww_ww_ctw = 0x288,
};

static const chaw * const tegwa241_mastew_id[] = {
	[0x0] = "TZ",
	[0x1] = "CCPWEX",
	[0x2] = "CCPMU",
	[0x3] = "BPMP_FW",
	[0x4] = "PSC_FW_USEW",
	[0x5] = "PSC_FW_SUPEWVISOW",
	[0x6] = "PSC_FW_MACHINE",
	[0x7] = "PSC_BOOT",
	[0x8] = "BPMP_BOOT",
	[0x9] = "JTAGM_DFT",
	[0xa] = "COWESIGHT",
	[0xb] = "GPU",
	[0xc] = "PEATWANS",
	[0xd ... 0x3f] = "WSVD"
};

/*
 * Possibwe causes fow Swave and Timeout ewwows.
 * SWAVE_EWW:
 * Swave being accessed wesponded with an ewwow. Swave couwd wetuwn
 * an ewwow fow vawious cases :
 *   Unsuppowted access, cwamp setting when powew gated, wegistew
 *   wevew fiwewaww(SCW), addwess howe within the swave, etc
 *
 * TIMEOUT_EWW:
 * No wesponse wetuwned by swave. Can be due to swave being cwock
 * gated, undew weset, powewed down ow swave inabiwity to wespond
 * fow an intewnaw swave issue
 */
static const stwuct tegwa_cbb_ewwow tegwa241_cbb_ewwows[] = {
	{
		.code = "SWAVE_EWW",
		.desc = "Swave being accessed wesponded with an ewwow."
	}, {
		.code = "DECODE_EWW",
		.desc = "Attempt to access an addwess howe ow Wesewved wegion of memowy."
	}, {
		.code = "FIWEWAWW_EWW",
		.desc = "Attempt to access a wegion which is fiwewawwed."
	}, {
		.code = "TIMEOUT_EWW",
		.desc = "No wesponse wetuwned by swave."
	}, {
		.code = "PWWDOWN_EWW",
		.desc = "Attempt to access a powtion of the fabwic that is powewed down."
	}, {
		.code = "UNSUPPOWTED_EWW",
		.desc = "Attempt to access a swave thwough an unsuppowted access."
	}, {
		.code = "POISON_EWW",
		.desc = "Swave wesponds with poison ewwow to indicate ewwow in data."
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "WSVD"
	}, {
		.code = "NO_SUCH_ADDWESS_EWW",
		.desc = "The addwess bewongs to the pwi_tawget wange but thewe is no wegistew "
			"impwemented at the addwess."
	}, {
		.code = "TASK_EWW",
		.desc = "Attempt to update a PWI task when the cuwwent task has stiww not "
			"compweted."
	}, {
		.code = "EXTEWNAW_EWW",
		.desc = "Indicates that an extewnaw PWI wegistew access met with an ewwow due to "
			"any issue in the unit."
	}, {
		.code = "INDEX_EWW",
		.desc = "Appwicabwe to PWI index apewtuwe paiw, when the pwogwammed index is "
			"outside the wange defined in the manuaw."
	}, {
		.code = "WESET_EWW",
		.desc = "Tawget in Weset Ewwow: Attempt to access a SubPwi ow extewnaw PWI "
			"wegistew but they awe in weset."
	}, {
		.code = "WEGISTEW_WST_EWW",
		.desc = "Attempt to access a PWI wegistew but the wegistew is pawtiaw ow "
			"compwetewy in weset."
	}, {
		.code = "POWEW_GATED_EWW",
		.desc = "Wetuwned by extewnaw PWI cwient when the extewnaw access goes to a powew "
			"gated domain."
	}, {
		.code = "SUBPWI_FS_EWW",
		.desc = "Subpwi is fwoowswept: Attempt to access a subpwi thwough the main pwi "
			"tawget but subPwi wogic is fwoowswept."
	}, {
		.code = "SUBPWI_CWK_OFF_EWW",
		.desc = "Subpwi cwock is off: Attempt to access a subpwi thwough the main pwi "
			"tawget but subPwis cwock is gated/off."
	},
};

static const stwuct tegwa234_swave_wookup tegwa241_cbb_swave_map[] = {
	{ "WSVD",       0x00000 },
	{ "PCIE_C8",    0x51000 },
	{ "PCIE_C9",    0x52000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "AON",        0x5b000 },
	{ "BPMP",       0x5c000 },
	{ "WSVD",       0x00000 },
	{ "WSVD",       0x00000 },
	{ "PSC",        0x5d000 },
	{ "STM",        0x5e000 },
	{ "AXI2APB_1",  0x70000 },
	{ "AXI2APB_10", 0x71000 },
	{ "AXI2APB_11", 0x72000 },
	{ "AXI2APB_12", 0x73000 },
	{ "AXI2APB_13", 0x74000 },
	{ "AXI2APB_14", 0x75000 },
	{ "AXI2APB_15", 0x76000 },
	{ "AXI2APB_16", 0x77000 },
	{ "AXI2APB_17", 0x78000 },
	{ "AXI2APB_18", 0x79000 },
	{ "AXI2APB_19", 0x7a000 },
	{ "AXI2APB_2",  0x7b000 },
	{ "AXI2APB_20", 0x7c000 },
	{ "AXI2APB_4",  0x87000 },
	{ "AXI2APB_5",  0x88000 },
	{ "AXI2APB_6",  0x89000 },
	{ "AXI2APB_7",  0x8a000 },
	{ "AXI2APB_8",  0x8b000 },
	{ "AXI2APB_9",  0x8c000 },
	{ "AXI2APB_3",  0x8d000 },
	{ "AXI2APB_21", 0x7d000 },
	{ "AXI2APB_22", 0x7e000 },
	{ "AXI2APB_23", 0x7f000 },
	{ "AXI2APB_24", 0x80000 },
	{ "AXI2APB_25", 0x81000 },
	{ "AXI2APB_26", 0x82000 },
	{ "AXI2APB_27", 0x83000 },
	{ "AXI2APB_28", 0x84000 },
	{ "PCIE_C4",    0x53000 },
	{ "PCIE_C5",    0x54000 },
	{ "PCIE_C6",    0x55000 },
	{ "PCIE_C7",    0x56000 },
	{ "PCIE_C2",    0x57000 },
	{ "PCIE_C3",    0x58000 },
	{ "PCIE_C0",    0x59000 },
	{ "PCIE_C1",    0x5a000 },
	{ "CCPWEX",     0x50000 },
	{ "AXI2APB_29", 0x85000 },
	{ "AXI2APB_30", 0x86000 },
	{ "CBB_CENTWAW", 0x00000 },
	{ "AXI2APB_31", 0x8E000 },
	{ "AXI2APB_32", 0x8F000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa241_cbb_fabwic = {
	.name = "cbb-fabwic",
	.mastew_id = tegwa241_mastew_id,
	.swave_map = tegwa241_cbb_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa241_cbb_swave_map),
	.ewwows = tegwa241_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa241_cbb_ewwows),
	.notifiew_offset = 0x60000,
	.off_mask_ewd = 0x40004,
	.fiwewaww_base = 0x20000,
	.fiwewaww_ctw = 0x2370,
	.fiwewaww_ww_ctw = 0x2368,
};

static const stwuct tegwa234_swave_wookup tegwa241_bpmp_swave_map[] = {
	{ "WSVD",    0x00000 },
	{ "WSVD",    0x00000 },
	{ "WSVD",    0x00000 },
	{ "CBB",     0x15000 },
	{ "CPU",     0x16000 },
	{ "AXI2APB", 0x00000 },
	{ "DBB0",    0x17000 },
	{ "DBB1",    0x18000 },
};

static const stwuct tegwa234_cbb_fabwic tegwa241_bpmp_fabwic = {
	.name = "bpmp-fabwic",
	.mastew_id = tegwa241_mastew_id,
	.swave_map = tegwa241_bpmp_swave_map,
	.max_swaves = AWWAY_SIZE(tegwa241_bpmp_swave_map),
	.ewwows = tegwa241_cbb_ewwows,
	.max_ewwows = AWWAY_SIZE(tegwa241_cbb_ewwows),
	.notifiew_offset = 0x19000,
	.fiwewaww_base = 0x30000,
	.fiwewaww_ctw = 0x8f0,
	.fiwewaww_ww_ctw = 0x8e8,
};

static const stwuct of_device_id tegwa234_cbb_dt_ids[] = {
	{ .compatibwe = "nvidia,tegwa234-cbb-fabwic", .data = &tegwa234_cbb_fabwic },
	{ .compatibwe = "nvidia,tegwa234-aon-fabwic", .data = &tegwa234_aon_fabwic },
	{ .compatibwe = "nvidia,tegwa234-bpmp-fabwic", .data = &tegwa234_bpmp_fabwic },
	{ .compatibwe = "nvidia,tegwa234-dce-fabwic", .data = &tegwa234_dce_fabwic },
	{ .compatibwe = "nvidia,tegwa234-wce-fabwic", .data = &tegwa234_wce_fabwic },
	{ .compatibwe = "nvidia,tegwa234-sce-fabwic", .data = &tegwa234_sce_fabwic },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, tegwa234_cbb_dt_ids);

stwuct tegwa234_cbb_acpi_uid {
	const chaw *hid;
	const chaw *uid;
	const stwuct tegwa234_cbb_fabwic *fabwic;
};

static const stwuct tegwa234_cbb_acpi_uid tegwa234_cbb_acpi_uids[] = {
	{ "NVDA1070", "1", &tegwa241_cbb_fabwic },
	{ "NVDA1070", "2", &tegwa241_bpmp_fabwic },
	{ },
};

static const stwuct
tegwa234_cbb_fabwic *tegwa234_cbb_acpi_get_fabwic(stwuct acpi_device *adev)
{
	const stwuct tegwa234_cbb_acpi_uid *entwy;

	fow (entwy = tegwa234_cbb_acpi_uids; entwy->hid; entwy++) {
		if (acpi_dev_hid_uid_match(adev, entwy->hid, entwy->uid))
			wetuwn entwy->fabwic;
	}

	wetuwn NUWW;
}

static const stwuct acpi_device_id tegwa241_cbb_acpi_ids[] = {
	{ "NVDA1070" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, tegwa241_cbb_acpi_ids);

static int tegwa234_cbb_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa234_cbb_fabwic *fabwic;
	stwuct tegwa234_cbb *cbb;
	unsigned wong fwags = 0;
	int eww;

	if (pdev->dev.of_node) {
		fabwic = of_device_get_match_data(&pdev->dev);
	} ewse {
		stwuct acpi_device *device = ACPI_COMPANION(&pdev->dev);
		if (!device)
			wetuwn -ENODEV;

		fabwic = tegwa234_cbb_acpi_get_fabwic(device);
		if (!fabwic) {
			dev_eww(&pdev->dev, "no device match found\n");
			wetuwn -ENODEV;
		}
	}

	cbb = devm_kzawwoc(&pdev->dev, sizeof(*cbb), GFP_KEWNEW);
	if (!cbb)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&cbb->base.node);
	cbb->base.ops = &tegwa234_cbb_ops;
	cbb->base.dev = &pdev->dev;
	cbb->fabwic = fabwic;

	cbb->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &cbb->wes);
	if (IS_EWW(cbb->wegs))
		wetuwn PTW_EWW(cbb->wegs);

	eww = tegwa_cbb_get_iwq(pdev, NUWW, &cbb->sec_iwq);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, cbb);

	/*
	 * Don't enabwe ewwow wepowting fow a Fabwic if wwite to it's wegistews
	 * is bwocked by CBB fiwewaww.
	 */
	if (!tegwa234_cbb_wwite_access_awwowed(pdev, cbb)) {
		dev_info(&pdev->dev, "ewwow wepowting not enabwed due to fiwewaww\n");
		wetuwn 0;
	}

	spin_wock_iwqsave(&cbb_wock, fwags);
	wist_add(&cbb->base.node, &cbb_wist);
	spin_unwock_iwqwestowe(&cbb_wock, fwags);

	/* set EWD bit to mask SEwwow and genewate intewwupt to wepowt ewwow */
	if (cbb->fabwic->off_mask_ewd)
		tegwa234_cbb_mask_sewwow(cbb);

	wetuwn tegwa_cbb_wegistew(&cbb->base);
}

static int __maybe_unused tegwa234_cbb_wesume_noiwq(stwuct device *dev)
{
	stwuct tegwa234_cbb *cbb = dev_get_dwvdata(dev);

	tegwa234_cbb_ewwow_enabwe(&cbb->base);

	dev_dbg(dev, "%s wesumed\n", cbb->fabwic->name);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa234_cbb_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, tegwa234_cbb_wesume_noiwq)
};

static stwuct pwatfowm_dwivew tegwa234_cbb_dwivew = {
	.pwobe = tegwa234_cbb_pwobe,
	.dwivew = {
		.name = "tegwa234-cbb",
		.of_match_tabwe = tegwa234_cbb_dt_ids,
		.acpi_match_tabwe = tegwa241_cbb_acpi_ids,
		.pm = &tegwa234_cbb_pm,
	},
};

static int __init tegwa234_cbb_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tegwa234_cbb_dwivew);
}
puwe_initcaww(tegwa234_cbb_init);

static void __exit tegwa234_cbb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tegwa234_cbb_dwivew);
}
moduwe_exit(tegwa234_cbb_exit);

MODUWE_DESCWIPTION("Contwow Backbone 2.0 ewwow handwing dwivew fow Tegwa234");
