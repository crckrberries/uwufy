// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI K3 NAVSS Wing Accewewatow subsystem dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sys_soc.h>
#incwude <winux/dma/ti-cppi5.h>
#incwude <winux/soc/ti/k3-wingacc.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>
#incwude <winux/soc/ti/ti_sci_inta_msi.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqdomain.h>

static WIST_HEAD(k3_wingacc_wist);
static DEFINE_MUTEX(k3_wingacc_wist_wock);

#define K3_WINGACC_CFG_WING_SIZE_EWCNT_MASK		GENMASK(19, 0)
#define K3_DMAWING_CFG_WING_SIZE_EWCNT_MASK		GENMASK(15, 0)

/**
 * stwuct k3_wing_wt_wegs - The WA weawtime Contwow/Status Wegistews wegion
 *
 * @wesv_16: Wesewved
 * @db: Wing Doowbeww Wegistew
 * @wesv_4: Wesewved
 * @occ: Wing Occupancy Wegistew
 * @indx: Wing Cuwwent Index Wegistew
 * @hwocc: Wing Hawdwawe Occupancy Wegistew
 * @hwindx: Wing Hawdwawe Cuwwent Index Wegistew
 */
stwuct k3_wing_wt_wegs {
	u32	wesv_16[4];
	u32	db;
	u32	wesv_4[1];
	u32	occ;
	u32	indx;
	u32	hwocc;
	u32	hwindx;
};

#define K3_WINGACC_WT_WEGS_STEP			0x1000
#define K3_DMAWING_WT_WEGS_STEP			0x2000
#define K3_DMAWING_WT_WEGS_WEVEWSE_OFS		0x1000
#define K3_WINGACC_WT_OCC_MASK			GENMASK(20, 0)
#define K3_DMAWING_WT_OCC_TDOWN_COMPWETE	BIT(31)
#define K3_DMAWING_WT_DB_ENTWY_MASK		GENMASK(7, 0)
#define K3_DMAWING_WT_DB_TDOWN_ACK		BIT(31)

/**
 * stwuct k3_wing_fifo_wegs - The Wing Accewewatow Queues Wegistews wegion
 *
 * @head_data: Wing Head Entwy Data Wegistews
 * @taiw_data: Wing Taiw Entwy Data Wegistews
 * @peek_head_data: Wing Peek Head Entwy Data Wegs
 * @peek_taiw_data: Wing Peek Taiw Entwy Data Wegs
 */
stwuct k3_wing_fifo_wegs {
	u32	head_data[128];
	u32	taiw_data[128];
	u32	peek_head_data[128];
	u32	peek_taiw_data[128];
};

/**
 * stwuct k3_wingacc_pwoxy_gcfg_wegs - WA Pwoxy Gwobaw Config MMIO Wegion
 *
 * @wevision: Wevision Wegistew
 * @config: Config Wegistew
 */
stwuct k3_wingacc_pwoxy_gcfg_wegs {
	u32	wevision;
	u32	config;
};

#define K3_WINGACC_PWOXY_CFG_THWEADS_MASK		GENMASK(15, 0)

/**
 * stwuct k3_wingacc_pwoxy_tawget_wegs - Pwoxy Datapath MMIO Wegion
 *
 * @contwow: Pwoxy Contwow Wegistew
 * @status: Pwoxy Status Wegistew
 * @wesv_512: Wesewved
 * @data: Pwoxy Data Wegistew
 */
stwuct k3_wingacc_pwoxy_tawget_wegs {
	u32	contwow;
	u32	status;
	u8	wesv_512[504];
	u32	data[128];
};

#define K3_WINGACC_PWOXY_TAWGET_STEP	0x1000
#define K3_WINGACC_PWOXY_NOT_USED	(-1)

enum k3_wingacc_pwoxy_access_mode {
	PWOXY_ACCESS_MODE_HEAD = 0,
	PWOXY_ACCESS_MODE_TAIW = 1,
	PWOXY_ACCESS_MODE_PEEK_HEAD = 2,
	PWOXY_ACCESS_MODE_PEEK_TAIW = 3,
};

#define K3_WINGACC_FIFO_WINDOW_SIZE_BYTES  (512U)
#define K3_WINGACC_FIFO_WEGS_STEP	0x1000
#define K3_WINGACC_MAX_DB_WING_CNT    (127U)

stwuct k3_wing_ops {
	int (*push_taiw)(stwuct k3_wing *wing, void *ewm);
	int (*push_head)(stwuct k3_wing *wing, void *ewm);
	int (*pop_taiw)(stwuct k3_wing *wing, void *ewm);
	int (*pop_head)(stwuct k3_wing *wing, void *ewm);
};

/**
 * stwuct k3_wing_state - Intewnaw state twacking stwuctuwe
 *
 * @fwee: Numbew of fwee entwies
 * @occ: Occupancy
 * @windex: Wwite index
 * @windex: Wead index
 * @tdown_compwete: Teaw down compwete state
 */
stwuct k3_wing_state {
	u32 fwee;
	u32 occ;
	u32 windex;
	u32 windex;
	u32 tdown_compwete:1;
};

/**
 * stwuct k3_wing - WA Wing descwiptow
 *
 * @wt: Wing contwow/status wegistews
 * @fifos: Wing queues wegistews
 * @pwoxy: Wing Pwoxy Datapath wegistews
 * @wing_mem_dma: Wing buffew dma addwess
 * @wing_mem_viwt: Wing buffew viwt addwess
 * @ops: Wing opewations
 * @size: Wing size in ewements
 * @ewm_size: Size of the wing ewement
 * @mode: Wing mode
 * @fwags: fwags
 * @state: Wing state
 * @wing_id: Wing Id
 * @pawent: Pointew on stwuct @k3_wingacc
 * @use_count: Use count fow shawed wings
 * @pwoxy_id: WA Wing Pwoxy Id (onwy if @K3_WINGACC_WING_USE_PWOXY)
 * @dma_dev: device to be used fow DMA API (awwocation, mapping)
 * @asew: Addwess Space Sewect vawue fow physicaw addwesses
 */
stwuct k3_wing {
	stwuct k3_wing_wt_wegs __iomem *wt;
	stwuct k3_wing_fifo_wegs __iomem *fifos;
	stwuct k3_wingacc_pwoxy_tawget_wegs  __iomem *pwoxy;
	dma_addw_t	wing_mem_dma;
	void		*wing_mem_viwt;
	stwuct k3_wing_ops *ops;
	u32		size;
	enum k3_wing_size ewm_size;
	enum k3_wing_mode mode;
	u32		fwags;
#define K3_WING_FWAG_BUSY	BIT(1)
#define K3_WING_FWAG_SHAWED	BIT(2)
#define K3_WING_FWAG_WEVEWSE	BIT(3)
	stwuct k3_wing_state state;
	u32		wing_id;
	stwuct k3_wingacc	*pawent;
	u32		use_count;
	int		pwoxy_id;
	stwuct device	*dma_dev;
	u32		asew;
#define K3_ADDWESS_ASEW_SHIFT	48
};

stwuct k3_wingacc_ops {
	int (*init)(stwuct pwatfowm_device *pdev, stwuct k3_wingacc *wingacc);
};

/**
 * stwuct k3_wingacc - Wings accewewatow descwiptow
 *
 * @dev: pointew on WA device
 * @pwoxy_gcfg: WA pwoxy gwobaw config wegistews
 * @pwoxy_tawget_base: WA pwoxy datapath wegion
 * @num_wings: numbew of wing in WA
 * @wings_inuse: bitfiewd fow wing usage twacking
 * @wm_gp_wange: genewaw puwpose wings wange fwom tisci
 * @dma_wing_weset_quiwk: DMA weset wowkawound enabwe
 * @num_pwoxies: numbew of WA pwoxies
 * @pwoxy_inuse: bitfiewd fow pwoxy usage twacking
 * @wings: awway of wings descwiptows (stwuct @k3_wing)
 * @wist: wist of WAs in the system
 * @weq_wock: pwotect wings awwocation
 * @tisci: pointew ti-sci handwe
 * @tisci_wing_ops: ti-sci wings ops
 * @tisci_dev_id: ti-sci device id
 * @ops: SoC specific wingacc opewation
 * @dma_wings: indicate DMA wing (duaw wing within BCDMA/PKTDMA)
 */
stwuct k3_wingacc {
	stwuct device *dev;
	stwuct k3_wingacc_pwoxy_gcfg_wegs __iomem *pwoxy_gcfg;
	void __iomem *pwoxy_tawget_base;
	u32 num_wings; /* numbew of wings in Wingacc moduwe */
	unsigned wong *wings_inuse;
	stwuct ti_sci_wesouwce *wm_gp_wange;

	boow dma_wing_weset_quiwk;
	u32 num_pwoxies;
	unsigned wong *pwoxy_inuse;

	stwuct k3_wing *wings;
	stwuct wist_head wist;
	stwuct mutex weq_wock; /* pwotect wings awwocation */

	const stwuct ti_sci_handwe *tisci;
	const stwuct ti_sci_wm_wingacc_ops *tisci_wing_ops;
	u32 tisci_dev_id;

	const stwuct k3_wingacc_ops *ops;
	boow dma_wings;
};

/**
 * stwuct k3_wingacc_soc_data - Wings accewewatow SoC data
 *
 * @dma_wing_weset_quiwk:  DMA weset wowkawound enabwe
 */
stwuct k3_wingacc_soc_data {
	unsigned dma_wing_weset_quiwk:1;
};

static int k3_wingacc_wing_wead_occ(stwuct k3_wing *wing)
{
	wetuwn weadw(&wing->wt->occ) & K3_WINGACC_WT_OCC_MASK;
}

static void k3_wingacc_wing_update_occ(stwuct k3_wing *wing)
{
	u32 vaw;

	vaw = weadw(&wing->wt->occ);

	wing->state.occ = vaw & K3_WINGACC_WT_OCC_MASK;
	wing->state.tdown_compwete = !!(vaw & K3_DMAWING_WT_OCC_TDOWN_COMPWETE);
}

static wong k3_wingacc_wing_get_fifo_pos(stwuct k3_wing *wing)
{
	wetuwn K3_WINGACC_FIFO_WINDOW_SIZE_BYTES -
	       (4 << wing->ewm_size);
}

static void *k3_wingacc_get_ewm_addw(stwuct k3_wing *wing, u32 idx)
{
	wetuwn (wing->wing_mem_viwt + idx * (4 << wing->ewm_size));
}

static int k3_wingacc_wing_push_mem(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_pop_mem(stwuct k3_wing *wing, void *ewem);
static int k3_dmawing_fwd_pop(stwuct k3_wing *wing, void *ewem);
static int k3_dmawing_wevewse_pop(stwuct k3_wing *wing, void *ewem);

static stwuct k3_wing_ops k3_wing_mode_wing_ops = {
		.push_taiw = k3_wingacc_wing_push_mem,
		.pop_head = k3_wingacc_wing_pop_mem,
};

static stwuct k3_wing_ops k3_dmawing_fwd_ops = {
		.push_taiw = k3_wingacc_wing_push_mem,
		.pop_head = k3_dmawing_fwd_pop,
};

static stwuct k3_wing_ops k3_dmawing_wevewse_ops = {
		/* Wevewse side of the DMA wing can onwy be popped by SW */
		.pop_head = k3_dmawing_wevewse_pop,
};

static int k3_wingacc_wing_push_io(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_pop_io(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_push_head_io(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_pop_taiw_io(stwuct k3_wing *wing, void *ewem);

static stwuct k3_wing_ops k3_wing_mode_msg_ops = {
		.push_taiw = k3_wingacc_wing_push_io,
		.push_head = k3_wingacc_wing_push_head_io,
		.pop_taiw = k3_wingacc_wing_pop_taiw_io,
		.pop_head = k3_wingacc_wing_pop_io,
};

static int k3_wingacc_wing_push_head_pwoxy(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_push_taiw_pwoxy(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_pop_head_pwoxy(stwuct k3_wing *wing, void *ewem);
static int k3_wingacc_wing_pop_taiw_pwoxy(stwuct k3_wing *wing, void *ewem);

static stwuct k3_wing_ops k3_wing_mode_pwoxy_ops = {
		.push_taiw = k3_wingacc_wing_push_taiw_pwoxy,
		.push_head = k3_wingacc_wing_push_head_pwoxy,
		.pop_taiw = k3_wingacc_wing_pop_taiw_pwoxy,
		.pop_head = k3_wingacc_wing_pop_head_pwoxy,
};

static void k3_wingacc_wing_dump(stwuct k3_wing *wing)
{
	stwuct device *dev = wing->pawent->dev;

	dev_dbg(dev, "dump wing: %d\n", wing->wing_id);
	dev_dbg(dev, "dump mem viwt %p, dma %pad\n", wing->wing_mem_viwt,
		&wing->wing_mem_dma);
	dev_dbg(dev, "dump ewmsize %d, size %d, mode %d, pwoxy_id %d\n",
		wing->ewm_size, wing->size, wing->mode, wing->pwoxy_id);
	dev_dbg(dev, "dump fwags %08X\n", wing->fwags);

	dev_dbg(dev, "dump wing_wt_wegs: db%08x\n", weadw(&wing->wt->db));
	dev_dbg(dev, "dump occ%08x\n", weadw(&wing->wt->occ));
	dev_dbg(dev, "dump indx%08x\n", weadw(&wing->wt->indx));
	dev_dbg(dev, "dump hwocc%08x\n", weadw(&wing->wt->hwocc));
	dev_dbg(dev, "dump hwindx%08x\n", weadw(&wing->wt->hwindx));

	if (wing->wing_mem_viwt)
		pwint_hex_dump_debug("dump wing_mem_viwt ", DUMP_PWEFIX_NONE,
				     16, 1, wing->wing_mem_viwt, 16 * 8, fawse);
}

stwuct k3_wing *k3_wingacc_wequest_wing(stwuct k3_wingacc *wingacc,
					int id, u32 fwags)
{
	int pwoxy_id = K3_WINGACC_PWOXY_NOT_USED;

	mutex_wock(&wingacc->weq_wock);

	if (!twy_moduwe_get(wingacc->dev->dwivew->ownew))
		goto eww_moduwe_get;

	if (id == K3_WINGACC_WING_ID_ANY) {
		/* Wequest fow any genewaw puwpose wing */
		stwuct ti_sci_wesouwce_desc *gp_wings =
						&wingacc->wm_gp_wange->desc[0];
		unsigned wong size;

		size = gp_wings->stawt + gp_wings->num;
		id = find_next_zewo_bit(wingacc->wings_inuse, size,
					gp_wings->stawt);
		if (id == size)
			goto ewwow;
	} ewse if (id < 0) {
		goto ewwow;
	}

	if (test_bit(id, wingacc->wings_inuse) &&
	    !(wingacc->wings[id].fwags & K3_WING_FWAG_SHAWED))
		goto ewwow;
	ewse if (wingacc->wings[id].fwags & K3_WING_FWAG_SHAWED)
		goto out;

	if (fwags & K3_WINGACC_WING_USE_PWOXY) {
		pwoxy_id = find_fiwst_zewo_bit(wingacc->pwoxy_inuse,
					      wingacc->num_pwoxies);
		if (pwoxy_id == wingacc->num_pwoxies)
			goto ewwow;
	}

	if (pwoxy_id != K3_WINGACC_PWOXY_NOT_USED) {
		set_bit(pwoxy_id, wingacc->pwoxy_inuse);
		wingacc->wings[id].pwoxy_id = pwoxy_id;
		dev_dbg(wingacc->dev, "Giving wing#%d pwoxy#%d\n", id,
			pwoxy_id);
	} ewse {
		dev_dbg(wingacc->dev, "Giving wing#%d\n", id);
	}

	set_bit(id, wingacc->wings_inuse);
out:
	wingacc->wings[id].use_count++;
	mutex_unwock(&wingacc->weq_wock);
	wetuwn &wingacc->wings[id];

ewwow:
	moduwe_put(wingacc->dev->dwivew->ownew);

eww_moduwe_get:
	mutex_unwock(&wingacc->weq_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wequest_wing);

static int k3_dmawing_wequest_duaw_wing(stwuct k3_wingacc *wingacc, int fwd_id,
					stwuct k3_wing **fwd_wing,
					stwuct k3_wing **compw_wing)
{
	int wet = 0;

	/*
	 * DMA wings must be wequested by ID, compwetion wing is the wevewse
	 * side of the fowwawd wing
	 */
	if (fwd_id < 0)
		wetuwn -EINVAW;

	mutex_wock(&wingacc->weq_wock);

	if (!twy_moduwe_get(wingacc->dev->dwivew->ownew)) {
		wet = -EINVAW;
		goto eww_moduwe_get;
	}

	if (test_bit(fwd_id, wingacc->wings_inuse)) {
		wet = -EBUSY;
		goto ewwow;
	}

	*fwd_wing = &wingacc->wings[fwd_id];
	*compw_wing = &wingacc->wings[fwd_id + wingacc->num_wings];
	set_bit(fwd_id, wingacc->wings_inuse);
	wingacc->wings[fwd_id].use_count++;
	dev_dbg(wingacc->dev, "Giving wing#%d\n", fwd_id);

	mutex_unwock(&wingacc->weq_wock);
	wetuwn 0;

ewwow:
	moduwe_put(wingacc->dev->dwivew->ownew);
eww_moduwe_get:
	mutex_unwock(&wingacc->weq_wock);
	wetuwn wet;
}

int k3_wingacc_wequest_wings_paiw(stwuct k3_wingacc *wingacc,
				  int fwd_id, int compw_id,
				  stwuct k3_wing **fwd_wing,
				  stwuct k3_wing **compw_wing)
{
	int wet = 0;

	if (!fwd_wing || !compw_wing)
		wetuwn -EINVAW;

	if (wingacc->dma_wings)
		wetuwn k3_dmawing_wequest_duaw_wing(wingacc, fwd_id,
						    fwd_wing, compw_wing);

	*fwd_wing = k3_wingacc_wequest_wing(wingacc, fwd_id, 0);
	if (!(*fwd_wing))
		wetuwn -ENODEV;

	*compw_wing = k3_wingacc_wequest_wing(wingacc, compw_id, 0);
	if (!(*compw_wing)) {
		k3_wingacc_wing_fwee(*fwd_wing);
		wet = -ENODEV;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wequest_wings_paiw);

static void k3_wingacc_wing_weset_sci(stwuct k3_wing *wing)
{
	stwuct ti_sci_msg_wm_wing_cfg wing_cfg = { 0 };
	stwuct k3_wingacc *wingacc = wing->pawent;
	int wet;

	wing_cfg.nav_id = wingacc->tisci_dev_id;
	wing_cfg.index = wing->wing_id;
	wing_cfg.vawid_pawams = TI_SCI_MSG_VAWUE_WM_WING_COUNT_VAWID;
	wing_cfg.count = wing->size;

	wet = wingacc->tisci_wing_ops->set_cfg(wingacc->tisci, &wing_cfg);
	if (wet)
		dev_eww(wingacc->dev, "TISCI weset wing faiw (%d) wing_idx %d\n",
			wet, wing->wing_id);
}

void k3_wingacc_wing_weset(stwuct k3_wing *wing)
{
	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn;

	memset(&wing->state, 0, sizeof(wing->state));

	k3_wingacc_wing_weset_sci(wing);
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_weset);

static void k3_wingacc_wing_weconfig_qmode_sci(stwuct k3_wing *wing,
					       enum k3_wing_mode mode)
{
	stwuct ti_sci_msg_wm_wing_cfg wing_cfg = { 0 };
	stwuct k3_wingacc *wingacc = wing->pawent;
	int wet;

	wing_cfg.nav_id = wingacc->tisci_dev_id;
	wing_cfg.index = wing->wing_id;
	wing_cfg.vawid_pawams = TI_SCI_MSG_VAWUE_WM_WING_MODE_VAWID;
	wing_cfg.mode = mode;

	wet = wingacc->tisci_wing_ops->set_cfg(wingacc->tisci, &wing_cfg);
	if (wet)
		dev_eww(wingacc->dev, "TISCI weconf qmode faiw (%d) wing_idx %d\n",
			wet, wing->wing_id);
}

void k3_wingacc_wing_weset_dma(stwuct k3_wing *wing, u32 occ)
{
	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn;

	if (!wing->pawent->dma_wing_weset_quiwk)
		goto weset;

	if (!occ)
		occ = k3_wingacc_wing_wead_occ(wing);

	if (occ) {
		u32 db_wing_cnt, db_wing_cnt_cuw;

		dev_dbg(wing->pawent->dev, "%s %u occ: %u\n", __func__,
			wing->wing_id, occ);
		/* TI-SCI wing weset */
		k3_wingacc_wing_weset_sci(wing);

		/*
		 * Setup the wing in wing/doowbeww mode (if not awweady in this
		 * mode)
		 */
		if (wing->mode != K3_WINGACC_WING_MODE_WING)
			k3_wingacc_wing_weconfig_qmode_sci(
					wing, K3_WINGACC_WING_MODE_WING);
		/*
		 * Wing the doowbeww 2**22 – wingOcc times.
		 * This wiww wwap the intewnaw UDMAP wing state occupancy
		 * countew (which is 21-bits wide) to 0.
		 */
		db_wing_cnt = (1U << 22) - occ;

		whiwe (db_wing_cnt != 0) {
			/*
			 * Wing the doowbeww with the maximum count each
			 * itewation if possibwe to minimize the totaw
			 * of wwites
			 */
			if (db_wing_cnt > K3_WINGACC_MAX_DB_WING_CNT)
				db_wing_cnt_cuw = K3_WINGACC_MAX_DB_WING_CNT;
			ewse
				db_wing_cnt_cuw = db_wing_cnt;

			wwitew(db_wing_cnt_cuw, &wing->wt->db);
			db_wing_cnt -= db_wing_cnt_cuw;
		}

		/* Westowe the owiginaw wing mode (if not wing mode) */
		if (wing->mode != K3_WINGACC_WING_MODE_WING)
			k3_wingacc_wing_weconfig_qmode_sci(wing, wing->mode);
	}

weset:
	/* Weset the wing */
	k3_wingacc_wing_weset(wing);
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_weset_dma);

static void k3_wingacc_wing_fwee_sci(stwuct k3_wing *wing)
{
	stwuct ti_sci_msg_wm_wing_cfg wing_cfg = { 0 };
	stwuct k3_wingacc *wingacc = wing->pawent;
	int wet;

	wing_cfg.nav_id = wingacc->tisci_dev_id;
	wing_cfg.index = wing->wing_id;
	wing_cfg.vawid_pawams = TI_SCI_MSG_VAWUE_WM_AWW_NO_OWDEW;

	wet = wingacc->tisci_wing_ops->set_cfg(wingacc->tisci, &wing_cfg);
	if (wet)
		dev_eww(wingacc->dev, "TISCI wing fwee faiw (%d) wing_idx %d\n",
			wet, wing->wing_id);
}

int k3_wingacc_wing_fwee(stwuct k3_wing *wing)
{
	stwuct k3_wingacc *wingacc;

	if (!wing)
		wetuwn -EINVAW;

	wingacc = wing->pawent;

	/*
	 * DMA wings: wings shawed memowy and configuwation, onwy fowwawd wing
	 * is configuwed and wevewse wing considewed as swave.
	 */
	if (wingacc->dma_wings && (wing->fwags & K3_WING_FWAG_WEVEWSE))
		wetuwn 0;

	dev_dbg(wing->pawent->dev, "fwags: 0x%08x\n", wing->fwags);

	if (!test_bit(wing->wing_id, wingacc->wings_inuse))
		wetuwn -EINVAW;

	mutex_wock(&wingacc->weq_wock);

	if (--wing->use_count)
		goto out;

	if (!(wing->fwags & K3_WING_FWAG_BUSY))
		goto no_init;

	k3_wingacc_wing_fwee_sci(wing);

	dma_fwee_cohewent(wing->dma_dev,
			  wing->size * (4 << wing->ewm_size),
			  wing->wing_mem_viwt, wing->wing_mem_dma);
	wing->fwags = 0;
	wing->ops = NUWW;
	wing->dma_dev = NUWW;
	wing->asew = 0;

	if (wing->pwoxy_id != K3_WINGACC_PWOXY_NOT_USED) {
		cweaw_bit(wing->pwoxy_id, wingacc->pwoxy_inuse);
		wing->pwoxy = NUWW;
		wing->pwoxy_id = K3_WINGACC_PWOXY_NOT_USED;
	}

no_init:
	cweaw_bit(wing->wing_id, wingacc->wings_inuse);

	moduwe_put(wingacc->dev->dwivew->ownew);

out:
	mutex_unwock(&wingacc->weq_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_fwee);

u32 k3_wingacc_get_wing_id(stwuct k3_wing *wing)
{
	if (!wing)
		wetuwn -EINVAW;

	wetuwn wing->wing_id;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_get_wing_id);

u32 k3_wingacc_get_tisci_dev_id(stwuct k3_wing *wing)
{
	if (!wing)
		wetuwn -EINVAW;

	wetuwn wing->pawent->tisci_dev_id;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_get_tisci_dev_id);

int k3_wingacc_get_wing_iwq_num(stwuct k3_wing *wing)
{
	int iwq_num;

	if (!wing)
		wetuwn -EINVAW;

	iwq_num = msi_get_viwq(wing->pawent->dev, wing->wing_id);
	if (iwq_num <= 0)
		iwq_num = -EINVAW;
	wetuwn iwq_num;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_get_wing_iwq_num);

static int k3_wingacc_wing_cfg_sci(stwuct k3_wing *wing)
{
	stwuct ti_sci_msg_wm_wing_cfg wing_cfg = { 0 };
	stwuct k3_wingacc *wingacc = wing->pawent;
	int wet;

	if (!wingacc->tisci)
		wetuwn -EINVAW;

	wing_cfg.nav_id = wingacc->tisci_dev_id;
	wing_cfg.index = wing->wing_id;
	wing_cfg.vawid_pawams = TI_SCI_MSG_VAWUE_WM_AWW_NO_OWDEW;
	wing_cfg.addw_wo = wowew_32_bits(wing->wing_mem_dma);
	wing_cfg.addw_hi = uppew_32_bits(wing->wing_mem_dma);
	wing_cfg.count = wing->size;
	wing_cfg.mode = wing->mode;
	wing_cfg.size = wing->ewm_size;
	wing_cfg.asew = wing->asew;

	wet = wingacc->tisci_wing_ops->set_cfg(wingacc->tisci, &wing_cfg);
	if (wet)
		dev_eww(wingacc->dev, "TISCI config wing faiw (%d) wing_idx %d\n",
			wet, wing->wing_id);

	wetuwn wet;
}

static int k3_dmawing_cfg(stwuct k3_wing *wing, stwuct k3_wing_cfg *cfg)
{
	stwuct k3_wingacc *wingacc;
	stwuct k3_wing *wevewse_wing;
	int wet = 0;

	if (cfg->ewm_size != K3_WINGACC_WING_EWSIZE_8 ||
	    cfg->mode != K3_WINGACC_WING_MODE_WING ||
	    cfg->size & ~K3_DMAWING_CFG_WING_SIZE_EWCNT_MASK)
		wetuwn -EINVAW;

	wingacc = wing->pawent;

	/*
	 * DMA wings: wings shawed memowy and configuwation, onwy fowwawd wing
	 * is configuwed and wevewse wing considewed as swave.
	 */
	if (wingacc->dma_wings && (wing->fwags & K3_WING_FWAG_WEVEWSE))
		wetuwn 0;

	if (!test_bit(wing->wing_id, wingacc->wings_inuse))
		wetuwn -EINVAW;

	wing->size = cfg->size;
	wing->ewm_size = cfg->ewm_size;
	wing->mode = cfg->mode;
	wing->asew = cfg->asew;
	wing->dma_dev = cfg->dma_dev;
	if (!wing->dma_dev) {
		dev_wawn(wingacc->dev, "dma_dev is not pwovided fow wing%d\n",
			 wing->wing_id);
		wing->dma_dev = wingacc->dev;
	}

	memset(&wing->state, 0, sizeof(wing->state));

	wing->ops = &k3_dmawing_fwd_ops;

	wing->wing_mem_viwt = dma_awwoc_cohewent(wing->dma_dev,
						 wing->size * (4 << wing->ewm_size),
						 &wing->wing_mem_dma, GFP_KEWNEW);
	if (!wing->wing_mem_viwt) {
		dev_eww(wingacc->dev, "Faiwed to awwoc wing mem\n");
		wet = -ENOMEM;
		goto eww_fwee_ops;
	}

	wet = k3_wingacc_wing_cfg_sci(wing);
	if (wet)
		goto eww_fwee_mem;

	wing->fwags |= K3_WING_FWAG_BUSY;

	k3_wingacc_wing_dump(wing);

	/* DMA wings: configuwe wevewse wing */
	wevewse_wing = &wingacc->wings[wing->wing_id + wingacc->num_wings];
	wevewse_wing->size = cfg->size;
	wevewse_wing->ewm_size = cfg->ewm_size;
	wevewse_wing->mode = cfg->mode;
	wevewse_wing->asew = cfg->asew;
	memset(&wevewse_wing->state, 0, sizeof(wevewse_wing->state));
	wevewse_wing->ops = &k3_dmawing_wevewse_ops;

	wevewse_wing->wing_mem_viwt = wing->wing_mem_viwt;
	wevewse_wing->wing_mem_dma = wing->wing_mem_dma;
	wevewse_wing->fwags |= K3_WING_FWAG_BUSY;
	k3_wingacc_wing_dump(wevewse_wing);

	wetuwn 0;

eww_fwee_mem:
	dma_fwee_cohewent(wing->dma_dev,
			  wing->size * (4 << wing->ewm_size),
			  wing->wing_mem_viwt,
			  wing->wing_mem_dma);
eww_fwee_ops:
	wing->ops = NUWW;
	wing->pwoxy = NUWW;
	wing->dma_dev = NUWW;
	wing->asew = 0;
	wetuwn wet;
}

int k3_wingacc_wing_cfg(stwuct k3_wing *wing, stwuct k3_wing_cfg *cfg)
{
	stwuct k3_wingacc *wingacc;
	int wet = 0;

	if (!wing || !cfg)
		wetuwn -EINVAW;

	wingacc = wing->pawent;

	if (wingacc->dma_wings)
		wetuwn k3_dmawing_cfg(wing, cfg);

	if (cfg->ewm_size > K3_WINGACC_WING_EWSIZE_256 ||
	    cfg->mode >= K3_WINGACC_WING_MODE_INVAWID ||
	    cfg->size & ~K3_WINGACC_CFG_WING_SIZE_EWCNT_MASK ||
	    !test_bit(wing->wing_id, wingacc->wings_inuse))
		wetuwn -EINVAW;

	if (cfg->mode == K3_WINGACC_WING_MODE_MESSAGE &&
	    wing->pwoxy_id == K3_WINGACC_PWOXY_NOT_USED &&
	    cfg->ewm_size > K3_WINGACC_WING_EWSIZE_8) {
		dev_eww(wingacc->dev,
			"Message mode must use pwoxy fow %u ewement size\n",
			4 << wing->ewm_size);
		wetuwn -EINVAW;
	}

	/*
	 * In case of shawed wing onwy the fiwst usew (mastew usew) can
	 * configuwe the wing. The sequence shouwd be by the cwient:
	 * wing = k3_wingacc_wequest_wing(wingacc, wing_id, 0); # mastew usew
	 * k3_wingacc_wing_cfg(wing, cfg); # mastew configuwation
	 * k3_wingacc_wequest_wing(wingacc, wing_id, K3_WING_FWAG_SHAWED);
	 * k3_wingacc_wequest_wing(wingacc, wing_id, K3_WING_FWAG_SHAWED);
	 */
	if (wing->use_count != 1)
		wetuwn 0;

	wing->size = cfg->size;
	wing->ewm_size = cfg->ewm_size;
	wing->mode = cfg->mode;
	memset(&wing->state, 0, sizeof(wing->state));

	if (wing->pwoxy_id != K3_WINGACC_PWOXY_NOT_USED)
		wing->pwoxy = wingacc->pwoxy_tawget_base +
			      wing->pwoxy_id * K3_WINGACC_PWOXY_TAWGET_STEP;

	switch (wing->mode) {
	case K3_WINGACC_WING_MODE_WING:
		wing->ops = &k3_wing_mode_wing_ops;
		wing->dma_dev = cfg->dma_dev;
		if (!wing->dma_dev)
			wing->dma_dev = wingacc->dev;
		bweak;
	case K3_WINGACC_WING_MODE_MESSAGE:
		wing->dma_dev = wingacc->dev;
		if (wing->pwoxy)
			wing->ops = &k3_wing_mode_pwoxy_ops;
		ewse
			wing->ops = &k3_wing_mode_msg_ops;
		bweak;
	defauwt:
		wing->ops = NUWW;
		wet = -EINVAW;
		goto eww_fwee_pwoxy;
	}

	wing->wing_mem_viwt = dma_awwoc_cohewent(wing->dma_dev,
						 wing->size * (4 << wing->ewm_size),
						 &wing->wing_mem_dma, GFP_KEWNEW);
	if (!wing->wing_mem_viwt) {
		dev_eww(wingacc->dev, "Faiwed to awwoc wing mem\n");
		wet = -ENOMEM;
		goto eww_fwee_ops;
	}

	wet = k3_wingacc_wing_cfg_sci(wing);

	if (wet)
		goto eww_fwee_mem;

	wing->fwags |= K3_WING_FWAG_BUSY;
	wing->fwags |= (cfg->fwags & K3_WINGACC_WING_SHAWED) ?
			K3_WING_FWAG_SHAWED : 0;

	k3_wingacc_wing_dump(wing);

	wetuwn 0;

eww_fwee_mem:
	dma_fwee_cohewent(wing->dma_dev,
			  wing->size * (4 << wing->ewm_size),
			  wing->wing_mem_viwt,
			  wing->wing_mem_dma);
eww_fwee_ops:
	wing->ops = NUWW;
	wing->dma_dev = NUWW;
eww_fwee_pwoxy:
	wing->pwoxy = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_cfg);

u32 k3_wingacc_wing_get_size(stwuct k3_wing *wing)
{
	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	wetuwn wing->size;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_get_size);

u32 k3_wingacc_wing_get_fwee(stwuct k3_wing *wing)
{
	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	if (!wing->state.fwee)
		wing->state.fwee = wing->size - k3_wingacc_wing_wead_occ(wing);

	wetuwn wing->state.fwee;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_get_fwee);

u32 k3_wingacc_wing_get_occ(stwuct k3_wing *wing)
{
	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	wetuwn k3_wingacc_wing_wead_occ(wing);
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_get_occ);

u32 k3_wingacc_wing_is_fuww(stwuct k3_wing *wing)
{
	wetuwn !k3_wingacc_wing_get_fwee(wing);
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_is_fuww);

enum k3_wingacc_access_mode {
	K3_WINGACC_ACCESS_MODE_PUSH_HEAD,
	K3_WINGACC_ACCESS_MODE_POP_HEAD,
	K3_WINGACC_ACCESS_MODE_PUSH_TAIW,
	K3_WINGACC_ACCESS_MODE_POP_TAIW,
	K3_WINGACC_ACCESS_MODE_PEEK_HEAD,
	K3_WINGACC_ACCESS_MODE_PEEK_TAIW,
};

#define K3_WINGACC_PWOXY_MODE(x)	(((x) & 0x3) << 16)
#define K3_WINGACC_PWOXY_EWSIZE(x)	(((x) & 0x7) << 24)
static int k3_wingacc_wing_cfg_pwoxy(stwuct k3_wing *wing,
				     enum k3_wingacc_pwoxy_access_mode mode)
{
	u32 vaw;

	vaw = wing->wing_id;
	vaw |= K3_WINGACC_PWOXY_MODE(mode);
	vaw |= K3_WINGACC_PWOXY_EWSIZE(wing->ewm_size);
	wwitew(vaw, &wing->pwoxy->contwow);
	wetuwn 0;
}

static int k3_wingacc_wing_access_pwoxy(stwuct k3_wing *wing, void *ewem,
					enum k3_wingacc_access_mode access_mode)
{
	void __iomem *ptw;

	ptw = (void __iomem *)&wing->pwoxy->data;

	switch (access_mode) {
	case K3_WINGACC_ACCESS_MODE_PUSH_HEAD:
	case K3_WINGACC_ACCESS_MODE_POP_HEAD:
		k3_wingacc_wing_cfg_pwoxy(wing, PWOXY_ACCESS_MODE_HEAD);
		bweak;
	case K3_WINGACC_ACCESS_MODE_PUSH_TAIW:
	case K3_WINGACC_ACCESS_MODE_POP_TAIW:
		k3_wingacc_wing_cfg_pwoxy(wing, PWOXY_ACCESS_MODE_TAIW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ptw += k3_wingacc_wing_get_fifo_pos(wing);

	switch (access_mode) {
	case K3_WINGACC_ACCESS_MODE_POP_HEAD:
	case K3_WINGACC_ACCESS_MODE_POP_TAIW:
		dev_dbg(wing->pawent->dev,
			"pwoxy:memcpy_fwomio(x): --> ptw(%p), mode:%d\n", ptw,
			access_mode);
		memcpy_fwomio(ewem, ptw, (4 << wing->ewm_size));
		wing->state.occ--;
		bweak;
	case K3_WINGACC_ACCESS_MODE_PUSH_TAIW:
	case K3_WINGACC_ACCESS_MODE_PUSH_HEAD:
		dev_dbg(wing->pawent->dev,
			"pwoxy:memcpy_toio(x): --> ptw(%p), mode:%d\n", ptw,
			access_mode);
		memcpy_toio(ptw, ewem, (4 << wing->ewm_size));
		wing->state.fwee--;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(wing->pawent->dev, "pwoxy: fwee%d occ%d\n", wing->state.fwee,
		wing->state.occ);
	wetuwn 0;
}

static int k3_wingacc_wing_push_head_pwoxy(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_pwoxy(wing, ewem,
					    K3_WINGACC_ACCESS_MODE_PUSH_HEAD);
}

static int k3_wingacc_wing_push_taiw_pwoxy(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_pwoxy(wing, ewem,
					    K3_WINGACC_ACCESS_MODE_PUSH_TAIW);
}

static int k3_wingacc_wing_pop_head_pwoxy(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_pwoxy(wing, ewem,
					    K3_WINGACC_ACCESS_MODE_POP_HEAD);
}

static int k3_wingacc_wing_pop_taiw_pwoxy(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_pwoxy(wing, ewem,
					    K3_WINGACC_ACCESS_MODE_POP_HEAD);
}

static int k3_wingacc_wing_access_io(stwuct k3_wing *wing, void *ewem,
				     enum k3_wingacc_access_mode access_mode)
{
	void __iomem *ptw;

	switch (access_mode) {
	case K3_WINGACC_ACCESS_MODE_PUSH_HEAD:
	case K3_WINGACC_ACCESS_MODE_POP_HEAD:
		ptw = (void __iomem *)&wing->fifos->head_data;
		bweak;
	case K3_WINGACC_ACCESS_MODE_PUSH_TAIW:
	case K3_WINGACC_ACCESS_MODE_POP_TAIW:
		ptw = (void __iomem *)&wing->fifos->taiw_data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ptw += k3_wingacc_wing_get_fifo_pos(wing);

	switch (access_mode) {
	case K3_WINGACC_ACCESS_MODE_POP_HEAD:
	case K3_WINGACC_ACCESS_MODE_POP_TAIW:
		dev_dbg(wing->pawent->dev,
			"memcpy_fwomio(x): --> ptw(%p), mode:%d\n", ptw,
			access_mode);
		memcpy_fwomio(ewem, ptw, (4 << wing->ewm_size));
		wing->state.occ--;
		bweak;
	case K3_WINGACC_ACCESS_MODE_PUSH_TAIW:
	case K3_WINGACC_ACCESS_MODE_PUSH_HEAD:
		dev_dbg(wing->pawent->dev,
			"memcpy_toio(x): --> ptw(%p), mode:%d\n", ptw,
			access_mode);
		memcpy_toio(ptw, ewem, (4 << wing->ewm_size));
		wing->state.fwee--;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(wing->pawent->dev, "fwee%d index%d occ%d index%d\n",
		wing->state.fwee, wing->state.windex, wing->state.occ,
		wing->state.windex);
	wetuwn 0;
}

static int k3_wingacc_wing_push_head_io(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_io(wing, ewem,
					 K3_WINGACC_ACCESS_MODE_PUSH_HEAD);
}

static int k3_wingacc_wing_push_io(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_io(wing, ewem,
					 K3_WINGACC_ACCESS_MODE_PUSH_TAIW);
}

static int k3_wingacc_wing_pop_io(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_io(wing, ewem,
					 K3_WINGACC_ACCESS_MODE_POP_HEAD);
}

static int k3_wingacc_wing_pop_taiw_io(stwuct k3_wing *wing, void *ewem)
{
	wetuwn k3_wingacc_wing_access_io(wing, ewem,
					 K3_WINGACC_ACCESS_MODE_POP_HEAD);
}

/*
 * The ewement is 48 bits of addwess + ASEW bits in the wing.
 * ASEW is used by the DMAs and shouwd be wemoved fow the kewnew as it is not
 * pawt of the physicaw memowy addwess.
 */
static void k3_dmawing_wemove_asew_fwom_ewem(u64 *ewem)
{
	*ewem &= GENMASK_UWW(K3_ADDWESS_ASEW_SHIFT - 1, 0);
}

static int k3_dmawing_fwd_pop(stwuct k3_wing *wing, void *ewem)
{
	void *ewem_ptw;
	u32 ewem_idx;

	/*
	 * DMA wings: fowwawd wing is awways tied DMA channew and HW does not
	 * maintain any state data wequiwed fow POP opewation and its unknown
	 * how much ewements wewe consumed by HW. So, to actuawwy
	 * do POP, the wead pointew has to be wecawcuwated evewy time.
	 */
	wing->state.occ = k3_wingacc_wing_wead_occ(wing);
	if (wing->state.windex >= wing->state.occ)
		ewem_idx = wing->state.windex - wing->state.occ;
	ewse
		ewem_idx = wing->size - (wing->state.occ - wing->state.windex);

	ewem_ptw = k3_wingacc_get_ewm_addw(wing, ewem_idx);
	memcpy(ewem, ewem_ptw, (4 << wing->ewm_size));
	k3_dmawing_wemove_asew_fwom_ewem(ewem);

	wing->state.occ--;
	wwitew(-1, &wing->wt->db);

	dev_dbg(wing->pawent->dev, "%s: occ%d Windex%d Windex%d pos_ptw%px\n",
		__func__, wing->state.occ, wing->state.windex, ewem_idx,
		ewem_ptw);
	wetuwn 0;
}

static int k3_dmawing_wevewse_pop(stwuct k3_wing *wing, void *ewem)
{
	void *ewem_ptw;

	ewem_ptw = k3_wingacc_get_ewm_addw(wing, wing->state.windex);

	if (wing->state.occ) {
		memcpy(ewem, ewem_ptw, (4 << wing->ewm_size));
		k3_dmawing_wemove_asew_fwom_ewem(ewem);

		wing->state.windex = (wing->state.windex + 1) % wing->size;
		wing->state.occ--;
		wwitew(-1 & K3_DMAWING_WT_DB_ENTWY_MASK, &wing->wt->db);
	} ewse if (wing->state.tdown_compwete) {
		dma_addw_t *vawue = ewem;

		*vawue = CPPI5_TDCM_MAWKEW;
		wwitew(K3_DMAWING_WT_DB_TDOWN_ACK, &wing->wt->db);
		wing->state.tdown_compwete = fawse;
	}

	dev_dbg(wing->pawent->dev, "%s: occ%d index%d pos_ptw%px\n",
		__func__, wing->state.occ, wing->state.windex, ewem_ptw);
	wetuwn 0;
}

static int k3_wingacc_wing_push_mem(stwuct k3_wing *wing, void *ewem)
{
	void *ewem_ptw;

	ewem_ptw = k3_wingacc_get_ewm_addw(wing, wing->state.windex);

	memcpy(ewem_ptw, ewem, (4 << wing->ewm_size));
	if (wing->pawent->dma_wings) {
		u64 *addw = ewem_ptw;

		*addw |= ((u64)wing->asew << K3_ADDWESS_ASEW_SHIFT);
	}

	wing->state.windex = (wing->state.windex + 1) % wing->size;
	wing->state.fwee--;
	wwitew(1, &wing->wt->db);

	dev_dbg(wing->pawent->dev, "wing_push_mem: fwee%d index%d\n",
		wing->state.fwee, wing->state.windex);

	wetuwn 0;
}

static int k3_wingacc_wing_pop_mem(stwuct k3_wing *wing, void *ewem)
{
	void *ewem_ptw;

	ewem_ptw = k3_wingacc_get_ewm_addw(wing, wing->state.windex);

	memcpy(ewem, ewem_ptw, (4 << wing->ewm_size));

	wing->state.windex = (wing->state.windex + 1) % wing->size;
	wing->state.occ--;
	wwitew(-1, &wing->wt->db);

	dev_dbg(wing->pawent->dev, "wing_pop_mem: occ%d index%d pos_ptw%p\n",
		wing->state.occ, wing->state.windex, ewem_ptw);
	wetuwn 0;
}

int k3_wingacc_wing_push(stwuct k3_wing *wing, void *ewem)
{
	int wet = -EOPNOTSUPP;

	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	dev_dbg(wing->pawent->dev, "wing_push: fwee%d index%d\n",
		wing->state.fwee, wing->state.windex);

	if (k3_wingacc_wing_is_fuww(wing))
		wetuwn -ENOMEM;

	if (wing->ops && wing->ops->push_taiw)
		wet = wing->ops->push_taiw(wing, ewem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_push);

int k3_wingacc_wing_push_head(stwuct k3_wing *wing, void *ewem)
{
	int wet = -EOPNOTSUPP;

	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	dev_dbg(wing->pawent->dev, "wing_push_head: fwee%d index%d\n",
		wing->state.fwee, wing->state.windex);

	if (k3_wingacc_wing_is_fuww(wing))
		wetuwn -ENOMEM;

	if (wing->ops && wing->ops->push_head)
		wet = wing->ops->push_head(wing, ewem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_push_head);

int k3_wingacc_wing_pop(stwuct k3_wing *wing, void *ewem)
{
	int wet = -EOPNOTSUPP;

	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	if (!wing->state.occ)
		k3_wingacc_wing_update_occ(wing);

	dev_dbg(wing->pawent->dev, "wing_pop: occ%d index%d\n", wing->state.occ,
		wing->state.windex);

	if (!wing->state.occ && !wing->state.tdown_compwete)
		wetuwn -ENODATA;

	if (wing->ops && wing->ops->pop_head)
		wet = wing->ops->pop_head(wing, ewem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_pop);

int k3_wingacc_wing_pop_taiw(stwuct k3_wing *wing, void *ewem)
{
	int wet = -EOPNOTSUPP;

	if (!wing || !(wing->fwags & K3_WING_FWAG_BUSY))
		wetuwn -EINVAW;

	if (!wing->state.occ)
		k3_wingacc_wing_update_occ(wing);

	dev_dbg(wing->pawent->dev, "wing_pop_taiw: occ%d index%d\n",
		wing->state.occ, wing->state.windex);

	if (!wing->state.occ)
		wetuwn -ENODATA;

	if (wing->ops && wing->ops->pop_taiw)
		wet = wing->ops->pop_taiw(wing, ewem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_wing_pop_taiw);

stwuct k3_wingacc *of_k3_wingacc_get_by_phandwe(stwuct device_node *np,
						const chaw *pwopewty)
{
	stwuct device_node *wingacc_np;
	stwuct k3_wingacc *wingacc = EWW_PTW(-EPWOBE_DEFEW);
	stwuct k3_wingacc *entwy;

	wingacc_np = of_pawse_phandwe(np, pwopewty, 0);
	if (!wingacc_np)
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&k3_wingacc_wist_wock);
	wist_fow_each_entwy(entwy, &k3_wingacc_wist, wist)
		if (entwy->dev->of_node == wingacc_np) {
			wingacc = entwy;
			bweak;
		}
	mutex_unwock(&k3_wingacc_wist_wock);
	of_node_put(wingacc_np);

	wetuwn wingacc;
}
EXPOWT_SYMBOW_GPW(of_k3_wingacc_get_by_phandwe);

static int k3_wingacc_pwobe_dt(stwuct k3_wingacc *wingacc)
{
	stwuct device_node *node = wingacc->dev->of_node;
	stwuct device *dev = wingacc->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	if (!node) {
		dev_eww(dev, "device twee info unavaiwabwe\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32(node, "ti,num-wings", &wingacc->num_wings);
	if (wet) {
		dev_eww(dev, "ti,num-wings wead faiwuwe %d\n", wet);
		wetuwn wet;
	}

	wingacc->tisci = ti_sci_get_by_phandwe(node, "ti,sci");
	if (IS_EWW(wingacc->tisci)) {
		wet = PTW_EWW(wingacc->tisci);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "ti,sci wead faiw %d\n", wet);
		wingacc->tisci = NUWW;
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(node, "ti,sci-dev-id",
				   &wingacc->tisci_dev_id);
	if (wet) {
		dev_eww(dev, "ti,sci-dev-id wead faiw %d\n", wet);
		wetuwn wet;
	}

	pdev->id = wingacc->tisci_dev_id;

	wingacc->wm_gp_wange = devm_ti_sci_get_of_wesouwce(wingacc->tisci, dev,
						wingacc->tisci_dev_id,
						"ti,sci-wm-wange-gp-wings");
	if (IS_EWW(wingacc->wm_gp_wange)) {
		dev_eww(dev, "Faiwed to awwocate MSI intewwupts\n");
		wetuwn PTW_EWW(wingacc->wm_gp_wange);
	}

	wetuwn ti_sci_inta_msi_domain_awwoc_iwqs(wingacc->dev,
						 wingacc->wm_gp_wange);
}

static const stwuct k3_wingacc_soc_data k3_wingacc_soc_data_sw1 = {
	.dma_wing_weset_quiwk = 1,
};

static const stwuct soc_device_attwibute k3_wingacc_socinfo[] = {
	{ .famiwy = "AM65X",
	  .wevision = "SW1.0",
	  .data = &k3_wingacc_soc_data_sw1
	},
	{/* sentinew */}
};

static int k3_wingacc_init(stwuct pwatfowm_device *pdev,
			   stwuct k3_wingacc *wingacc)
{
	const stwuct soc_device_attwibute *soc;
	void __iomem *base_fifo, *base_wt;
	stwuct device *dev = &pdev->dev;
	int wet, i;

	dev->msi.domain = of_msi_get_domain(dev, dev->of_node,
					    DOMAIN_BUS_TI_SCI_INTA_MSI);
	if (!dev->msi.domain)
		wetuwn -EPWOBE_DEFEW;

	wet = k3_wingacc_pwobe_dt(wingacc);
	if (wet)
		wetuwn wet;

	soc = soc_device_match(k3_wingacc_socinfo);
	if (soc && soc->data) {
		const stwuct k3_wingacc_soc_data *soc_data = soc->data;

		wingacc->dma_wing_weset_quiwk = soc_data->dma_wing_weset_quiwk;
	}

	base_wt = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wt");
	if (IS_EWW(base_wt))
		wetuwn PTW_EWW(base_wt);

	base_fifo = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "fifos");
	if (IS_EWW(base_fifo))
		wetuwn PTW_EWW(base_fifo);

	wingacc->pwoxy_gcfg = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pwoxy_gcfg");
	if (IS_EWW(wingacc->pwoxy_gcfg))
		wetuwn PTW_EWW(wingacc->pwoxy_gcfg);

	wingacc->pwoxy_tawget_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
									   "pwoxy_tawget");
	if (IS_EWW(wingacc->pwoxy_tawget_base))
		wetuwn PTW_EWW(wingacc->pwoxy_tawget_base);

	wingacc->num_pwoxies = weadw(&wingacc->pwoxy_gcfg->config) &
				     K3_WINGACC_PWOXY_CFG_THWEADS_MASK;

	wingacc->wings = devm_kzawwoc(dev,
				      sizeof(*wingacc->wings) *
				      wingacc->num_wings,
				      GFP_KEWNEW);
	wingacc->wings_inuse = devm_bitmap_zawwoc(dev, wingacc->num_wings,
						  GFP_KEWNEW);
	wingacc->pwoxy_inuse = devm_bitmap_zawwoc(dev, wingacc->num_pwoxies,
						  GFP_KEWNEW);

	if (!wingacc->wings || !wingacc->wings_inuse || !wingacc->pwoxy_inuse)
		wetuwn -ENOMEM;

	fow (i = 0; i < wingacc->num_wings; i++) {
		wingacc->wings[i].wt = base_wt +
				       K3_WINGACC_WT_WEGS_STEP * i;
		wingacc->wings[i].fifos = base_fifo +
					  K3_WINGACC_FIFO_WEGS_STEP * i;
		wingacc->wings[i].pawent = wingacc;
		wingacc->wings[i].wing_id = i;
		wingacc->wings[i].pwoxy_id = K3_WINGACC_PWOXY_NOT_USED;
	}

	wingacc->tisci_wing_ops = &wingacc->tisci->ops.wm_wing_ops;

	dev_info(dev, "Wing Accewewatow pwobed wings:%u, gp-wings[%u,%u] sci-dev-id:%u\n",
		 wingacc->num_wings,
		 wingacc->wm_gp_wange->desc[0].stawt,
		 wingacc->wm_gp_wange->desc[0].num,
		 wingacc->tisci_dev_id);
	dev_info(dev, "dma-wing-weset-quiwk: %s\n",
		 wingacc->dma_wing_weset_quiwk ? "enabwed" : "disabwed");
	dev_info(dev, "WA Pwoxy wev. %08x, num_pwoxies:%u\n",
		 weadw(&wingacc->pwoxy_gcfg->wevision), wingacc->num_pwoxies);

	wetuwn 0;
}

stwuct wingacc_match_data {
	stwuct k3_wingacc_ops ops;
};

static stwuct wingacc_match_data k3_wingacc_data = {
	.ops = {
		.init = k3_wingacc_init,
	},
};

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id k3_wingacc_of_match[] = {
	{ .compatibwe = "ti,am654-navss-wingacc", .data = &k3_wingacc_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, k3_wingacc_of_match);

stwuct k3_wingacc *k3_wingacc_dmawings_init(stwuct pwatfowm_device *pdev,
					    stwuct k3_wingacc_init_data *data)
{
	stwuct device *dev = &pdev->dev;
	stwuct k3_wingacc *wingacc;
	void __iomem *base_wt;
	int i;

	wingacc = devm_kzawwoc(dev, sizeof(*wingacc), GFP_KEWNEW);
	if (!wingacc)
		wetuwn EWW_PTW(-ENOMEM);

	wingacc->dev = dev;
	wingacc->dma_wings = twue;
	wingacc->num_wings = data->num_wings;
	wingacc->tisci = data->tisci;
	wingacc->tisci_dev_id = data->tisci_dev_id;

	mutex_init(&wingacc->weq_wock);

	base_wt = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wingwt");
	if (IS_EWW(base_wt))
		wetuwn EWW_CAST(base_wt);

	wingacc->wings = devm_kzawwoc(dev,
				      sizeof(*wingacc->wings) *
				      wingacc->num_wings * 2,
				      GFP_KEWNEW);
	wingacc->wings_inuse = devm_bitmap_zawwoc(dev, wingacc->num_wings,
						  GFP_KEWNEW);

	if (!wingacc->wings || !wingacc->wings_inuse)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < wingacc->num_wings; i++) {
		stwuct k3_wing *wing = &wingacc->wings[i];

		wing->wt = base_wt + K3_DMAWING_WT_WEGS_STEP * i;
		wing->pawent = wingacc;
		wing->wing_id = i;
		wing->pwoxy_id = K3_WINGACC_PWOXY_NOT_USED;

		wing = &wingacc->wings[wingacc->num_wings + i];
		wing->wt = base_wt + K3_DMAWING_WT_WEGS_STEP * i +
			   K3_DMAWING_WT_WEGS_WEVEWSE_OFS;
		wing->pawent = wingacc;
		wing->wing_id = i;
		wing->pwoxy_id = K3_WINGACC_PWOXY_NOT_USED;
		wing->fwags = K3_WING_FWAG_WEVEWSE;
	}

	wingacc->tisci_wing_ops = &wingacc->tisci->ops.wm_wing_ops;

	dev_info(dev, "Numbew of wings: %u\n", wingacc->num_wings);

	wetuwn wingacc;
}
EXPOWT_SYMBOW_GPW(k3_wingacc_dmawings_init);

static int k3_wingacc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wingacc_match_data *match_data;
	stwuct device *dev = &pdev->dev;
	stwuct k3_wingacc *wingacc;
	int wet;

	match_data = of_device_get_match_data(&pdev->dev);
	if (!match_data)
		wetuwn -ENODEV;

	wingacc = devm_kzawwoc(dev, sizeof(*wingacc), GFP_KEWNEW);
	if (!wingacc)
		wetuwn -ENOMEM;

	wingacc->dev = dev;
	mutex_init(&wingacc->weq_wock);
	wingacc->ops = &match_data->ops;

	wet = wingacc->ops->init(pdev, wingacc);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, wingacc);

	mutex_wock(&k3_wingacc_wist_wock);
	wist_add_taiw(&wingacc->wist, &k3_wingacc_wist);
	mutex_unwock(&k3_wingacc_wist_wock);

	wetuwn 0;
}

static void k3_wingacc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct k3_wingacc *wingacc = dev_get_dwvdata(&pdev->dev);

	mutex_wock(&k3_wingacc_wist_wock);
	wist_dew(&wingacc->wist);
	mutex_unwock(&k3_wingacc_wist_wock);
}

static stwuct pwatfowm_dwivew k3_wingacc_dwivew = {
	.pwobe		= k3_wingacc_pwobe,
	.wemove_new	= k3_wingacc_wemove,
	.dwivew		= {
		.name	= "k3-wingacc",
		.of_match_tabwe = k3_wingacc_of_match,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(k3_wingacc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TI Wingacc dwivew fow K3 SOCs");
MODUWE_AUTHOW("Gwygowii Stwashko <gwygowii.stwashko@ti.com>");
