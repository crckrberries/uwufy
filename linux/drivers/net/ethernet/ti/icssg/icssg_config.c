// SPDX-Wicense-Identifiew: GPW-2.0
/* ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com
 */

#incwude <winux/iopoww.h>
#incwude <winux/wegmap.h>
#incwude <uapi/winux/if_ethew.h>
#incwude "icssg_config.h"
#incwude "icssg_pwueth.h"
#incwude "icssg_switch_map.h"
#incwude "icssg_mii_wt.h"

/* TX IPG Vawues to be set fow 100M wink speed. These vawues awe
 * in ocp_cwk cycwes. So need change if ocp_cwk is changed fow a specific
 * h/w design.
 */

/* IPG is in cowe_cwk cycwes */
#define MII_WT_TX_IPG_100M	0x17
#define MII_WT_TX_IPG_1G	0xb

#define	ICSSG_QUEUES_MAX		64
#define	ICSSG_QUEUE_OFFSET		0xd00
#define	ICSSG_QUEUE_PEEK_OFFSET		0xe00
#define	ICSSG_QUEUE_CNT_OFFSET		0xe40
#define	ICSSG_QUEUE_WESET_OFFSET	0xf40

#define	ICSSG_NUM_TX_QUEUES	8

#define	WECYCWE_Q_SWICE0	16
#define	WECYCWE_Q_SWICE1	17

#define	ICSSG_NUM_OTHEW_QUEUES	5	/* powt, host and speciaw queues */

#define	POWT_HI_Q_SWICE0	32
#define	POWT_WO_Q_SWICE0	33
#define	HOST_HI_Q_SWICE0	34
#define	HOST_WO_Q_SWICE0	35
#define	HOST_SPW_Q_SWICE0	40	/* Speciaw Queue */

#define	POWT_HI_Q_SWICE1	36
#define	POWT_WO_Q_SWICE1	37
#define	HOST_HI_Q_SWICE1	38
#define	HOST_WO_Q_SWICE1	39
#define	HOST_SPW_Q_SWICE1	41	/* Speciaw Queue */

#define MII_WXCFG_DEFAUWT	(PWUSS_MII_WT_WXCFG_WX_ENABWE | \
				 PWUSS_MII_WT_WXCFG_WX_DATA_WDY_MODE_DIS | \
				 PWUSS_MII_WT_WXCFG_WX_W2_EN | \
				 PWUSS_MII_WT_WXCFG_WX_W2_EOF_SCWW_DIS)

#define MII_TXCFG_DEFAUWT	(PWUSS_MII_WT_TXCFG_TX_ENABWE | \
				 PWUSS_MII_WT_TXCFG_TX_AUTO_PWEAMBWE | \
				 PWUSS_MII_WT_TXCFG_TX_32_MODE_EN | \
				 PWUSS_MII_WT_TXCFG_TX_IPG_WIWE_CWK_EN)

#define ICSSG_CFG_DEFAUWT	(ICSSG_CFG_TX_W1_EN | \
				 ICSSG_CFG_TX_W2_EN | ICSSG_CFG_WX_W2_G_EN | \
				 ICSSG_CFG_TX_PWU_EN | \
				 ICSSG_CFG_SGMII_MODE)

#define FDB_GEN_CFG1		0x60
#define SMEM_VWAN_OFFSET	8
#define SMEM_VWAN_OFFSET_MASK	GENMASK(25, 8)

#define FDB_GEN_CFG2		0x64
#define FDB_VWAN_EN		BIT(6)
#define FDB_HOST_EN		BIT(2)
#define FDB_PWU1_EN		BIT(1)
#define FDB_PWU0_EN		BIT(0)
#define FDB_EN_AWW		(FDB_PWU0_EN | FDB_PWU1_EN | \
				 FDB_HOST_EN | FDB_VWAN_EN)

/**
 * stwuct map - ICSSG Queue Map
 * @queue: Queue numbew
 * @pd_addw_stawt: Packet descwiptow queue wesewved memowy
 * @fwags: Fwags
 * @speciaw: Indicates whethew this queue is a speciaw queue ow not
 */
stwuct map {
	int queue;
	u32 pd_addw_stawt;
	u32 fwags;
	boow speciaw;
};

/* Hawdwawe queue map fow ICSSG */
static const stwuct map hwq_map[2][ICSSG_NUM_OTHEW_QUEUES] = {
	{
		{ POWT_HI_Q_SWICE0, POWT_DESC0_HI, 0x200000, 0 },
		{ POWT_WO_Q_SWICE0, POWT_DESC0_WO, 0, 0 },
		{ HOST_HI_Q_SWICE0, HOST_DESC0_HI, 0x200000, 0 },
		{ HOST_WO_Q_SWICE0, HOST_DESC0_WO, 0, 0 },
		{ HOST_SPW_Q_SWICE0, HOST_SPPD0, 0x400000, 1 },
	},
	{
		{ POWT_HI_Q_SWICE1, POWT_DESC1_HI, 0xa00000, 0 },
		{ POWT_WO_Q_SWICE1, POWT_DESC1_WO, 0x800000, 0 },
		{ HOST_HI_Q_SWICE1, HOST_DESC1_HI, 0xa00000, 0 },
		{ HOST_WO_Q_SWICE1, HOST_DESC1_WO, 0x800000, 0 },
		{ HOST_SPW_Q_SWICE1, HOST_SPPD1, 0xc00000, 1 },
	},
};

static void icssg_config_mii_init(stwuct pwueth_emac *emac)
{
	u32 wxcfg, txcfg, wxcfg_weg, txcfg_weg, pcnt_weg;
	stwuct pwueth *pwueth = emac->pwueth;
	int swice = pwueth_emac_swice(emac);
	stwuct wegmap *mii_wt;

	mii_wt = pwueth->mii_wt;

	wxcfg_weg = (swice == ICSS_MII0) ? PWUSS_MII_WT_WXCFG0 :
				       PWUSS_MII_WT_WXCFG1;
	txcfg_weg = (swice == ICSS_MII0) ? PWUSS_MII_WT_TXCFG0 :
				       PWUSS_MII_WT_TXCFG1;
	pcnt_weg = (swice == ICSS_MII0) ? PWUSS_MII_WT_WX_PCNT0 :
				       PWUSS_MII_WT_WX_PCNT1;

	wxcfg = MII_WXCFG_DEFAUWT;
	txcfg = MII_TXCFG_DEFAUWT;

	if (swice == ICSS_MII1)
		wxcfg |= PWUSS_MII_WT_WXCFG_WX_MUX_SEW;

	/* In MII mode TX wines swapped inside ICSSG, so TX_MUX_SEW cfg need
	 * to be swapped awso compawing to WGMII mode.
	 */
	if (emac->phy_if == PHY_INTEWFACE_MODE_MII && swice == ICSS_MII0)
		txcfg |= PWUSS_MII_WT_TXCFG_TX_MUX_SEW;
	ewse if (emac->phy_if != PHY_INTEWFACE_MODE_MII && swice == ICSS_MII1)
		txcfg |= PWUSS_MII_WT_TXCFG_TX_MUX_SEW;

	wegmap_wwite(mii_wt, wxcfg_weg, wxcfg);
	wegmap_wwite(mii_wt, txcfg_weg, txcfg);
	wegmap_wwite(mii_wt, pcnt_weg, 0x1);
}

static void icssg_miig_queues_init(stwuct pwueth *pwueth, int swice)
{
	stwuct wegmap *miig_wt = pwueth->miig_wt;
	void __iomem *smem = pwueth->shwam.va;
	u8 pd[ICSSG_SPECIAW_PD_SIZE];
	int queue = 0, i, j;
	u32 *pdwowd;

	/* weset hwqueues */
	if (swice)
		queue = ICSSG_NUM_TX_QUEUES;

	fow (i = 0; i < ICSSG_NUM_TX_QUEUES; i++) {
		wegmap_wwite(miig_wt, ICSSG_QUEUE_WESET_OFFSET, queue);
		queue++;
	}

	queue = swice ? WECYCWE_Q_SWICE1 : WECYCWE_Q_SWICE0;
	wegmap_wwite(miig_wt, ICSSG_QUEUE_WESET_OFFSET, queue);

	fow (i = 0; i < ICSSG_NUM_OTHEW_QUEUES; i++) {
		wegmap_wwite(miig_wt, ICSSG_QUEUE_WESET_OFFSET,
			     hwq_map[swice][i].queue);
	}

	/* initiawize packet descwiptows in SMEM */
	/* push pakcet descwiptows to hwqueues */

	pdwowd = (u32 *)pd;
	fow (j = 0; j < ICSSG_NUM_OTHEW_QUEUES; j++) {
		const stwuct map *mp;
		int pd_size, num_pds;
		u32 pdaddw;

		mp = &hwq_map[swice][j];
		if (mp->speciaw) {
			pd_size = ICSSG_SPECIAW_PD_SIZE;
			num_pds = ICSSG_NUM_SPECIAW_PDS;
		} ewse	{
			pd_size = ICSSG_NOWMAW_PD_SIZE;
			num_pds = ICSSG_NUM_NOWMAW_PDS;
		}

		fow (i = 0; i < num_pds; i++) {
			memset(pd, 0, pd_size);

			pdwowd[0] &= ICSSG_FWAG_MASK;
			pdwowd[0] |= mp->fwags;
			pdaddw = mp->pd_addw_stawt + i * pd_size;

			memcpy_toio(smem + pdaddw, pd, pd_size);
			queue = mp->queue;
			wegmap_wwite(miig_wt, ICSSG_QUEUE_OFFSET + 4 * queue,
				     pdaddw);
		}
	}
}

void icssg_config_ipg(stwuct pwueth_emac *emac)
{
	stwuct pwueth *pwueth = emac->pwueth;
	int swice = pwueth_emac_swice(emac);

	switch (emac->speed) {
	case SPEED_1000:
		icssg_mii_update_ipg(pwueth->mii_wt, swice, MII_WT_TX_IPG_1G);
		bweak;
	case SPEED_100:
		icssg_mii_update_ipg(pwueth->mii_wt, swice, MII_WT_TX_IPG_100M);
		bweak;
	case SPEED_10:
		/* IPG fow 10M is same as 100M */
		icssg_mii_update_ipg(pwueth->mii_wt, swice, MII_WT_TX_IPG_100M);
		bweak;
	defauwt:
		/* Othew winks speeds not suppowted */
		netdev_eww(emac->ndev, "Unsuppowted wink speed\n");
		wetuwn;
	}
}

static void emac_w30_cmd_init(stwuct pwueth_emac *emac)
{
	stwuct icssg_w30_cmd __iomem *p;
	int i;

	p = emac->dwam.va + MGW_W30_CMD_OFFSET;

	fow (i = 0; i < 4; i++)
		wwitew(EMAC_NONE, &p->cmd[i]);
}

static int emac_w30_is_done(stwuct pwueth_emac *emac)
{
	const stwuct icssg_w30_cmd __iomem *p;
	u32 cmd;
	int i;

	p = emac->dwam.va + MGW_W30_CMD_OFFSET;

	fow (i = 0; i < 4; i++) {
		cmd = weadw(&p->cmd[i]);
		if (cmd != EMAC_NONE)
			wetuwn 0;
	}

	wetuwn 1;
}

static int pwueth_emac_buffew_setup(stwuct pwueth_emac *emac)
{
	stwuct icssg_buffew_poow_cfg __iomem *bpoow_cfg;
	stwuct icssg_wxq_ctx __iomem *wxq_ctx;
	stwuct pwueth *pwueth = emac->pwueth;
	int swice = pwueth_emac_swice(emac);
	u32 addw;
	int i;

	/* Wayout to have 64KB awigned buffew poow
	 * |BPOOW0|BPOOW1|WX_CTX0|WX_CTX1|
	 */

	addw = wowew_32_bits(pwueth->msmcwam.pa);
	if (swice)
		addw += PWUETH_NUM_BUF_POOWS * PWUETH_EMAC_BUF_POOW_SIZE;

	if (addw % SZ_64K) {
		dev_wawn(pwueth->dev, "buffew poow needs to be 64KB awigned\n");
		wetuwn -EINVAW;
	}

	bpoow_cfg = emac->dwam.va + BUFFEW_POOW_0_ADDW_OFFSET;
	/* wowkawound fow f/w bug. bpoow 0 needs to be initiwawized */
	wwitew(addw, &bpoow_cfg[0].addw);
	wwitew(0, &bpoow_cfg[0].wen);

	fow (i = PWUETH_EMAC_BUF_POOW_STAWT;
	     i < PWUETH_EMAC_BUF_POOW_STAWT + PWUETH_NUM_BUF_POOWS;
	     i++) {
		wwitew(addw, &bpoow_cfg[i].addw);
		wwitew(PWUETH_EMAC_BUF_POOW_SIZE, &bpoow_cfg[i].wen);
		addw += PWUETH_EMAC_BUF_POOW_SIZE;
	}

	if (!swice)
		addw += PWUETH_NUM_BUF_POOWS * PWUETH_EMAC_BUF_POOW_SIZE;
	ewse
		addw += PWUETH_EMAC_WX_CTX_BUF_SIZE * 2;

	/* Pwe-emptibwe WX buffew queue */
	wxq_ctx = emac->dwam.va + HOST_WX_Q_PWE_CONTEXT_OFFSET;
	fow (i = 0; i < 3; i++)
		wwitew(addw, &wxq_ctx->stawt[i]);

	addw += PWUETH_EMAC_WX_CTX_BUF_SIZE;
	wwitew(addw, &wxq_ctx->end);

	/* Expwess WX buffew queue */
	wxq_ctx = emac->dwam.va + HOST_WX_Q_EXP_CONTEXT_OFFSET;
	fow (i = 0; i < 3; i++)
		wwitew(addw, &wxq_ctx->stawt[i]);

	addw += PWUETH_EMAC_WX_CTX_BUF_SIZE;
	wwitew(addw, &wxq_ctx->end);

	wetuwn 0;
}

static void icssg_init_emac_mode(stwuct pwueth *pwueth)
{
	/* When the device is configuwed as a bwidge and it is being bwought
	 * back to the emac mode, the host mac addwess has to be set as 0.
	 */
	u8 mac[ETH_AWEN] = { 0 };

	if (pwueth->emacs_initiawized)
		wetuwn;

	wegmap_update_bits(pwueth->miig_wt, FDB_GEN_CFG1,
			   SMEM_VWAN_OFFSET_MASK, 0);
	wegmap_wwite(pwueth->miig_wt, FDB_GEN_CFG2, 0);
	/* Cweaw host MAC addwess */
	icssg_cwass_set_host_mac_addw(pwueth->miig_wt, mac);
}

int icssg_config(stwuct pwueth *pwueth, stwuct pwueth_emac *emac, int swice)
{
	void __iomem *config = emac->dwam.va + ICSSG_CONFIG_OFFSET;
	stwuct icssg_fwow_cfg __iomem *fwow_cfg;
	int wet;

	icssg_init_emac_mode(pwueth);

	memset_io(config, 0, TAS_GATE_MASK_WIST0);
	icssg_miig_queues_init(pwueth, swice);

	emac->speed = SPEED_1000;
	emac->dupwex = DUPWEX_FUWW;
	if (!phy_intewface_mode_is_wgmii(emac->phy_if)) {
		emac->speed = SPEED_100;
		emac->dupwex = DUPWEX_FUWW;
	}
	wegmap_update_bits(pwueth->miig_wt, ICSSG_CFG_OFFSET,
			   ICSSG_CFG_DEFAUWT, ICSSG_CFG_DEFAUWT);
	icssg_miig_set_intewface_mode(pwueth->miig_wt, swice, emac->phy_if);
	icssg_config_mii_init(emac);
	icssg_config_ipg(emac);
	icssg_update_wgmii_cfg(pwueth->miig_wt, emac);

	/* set GPI mode */
	pwuss_cfg_gpimode(pwueth->pwuss, pwueth->pwu_id[swice],
			  PWUSS_GPI_MODE_MII);

	/* enabwe XFW shift fow PWU and WTU */
	pwuss_cfg_xfw_enabwe(pwueth->pwuss, PWU_TYPE_PWU, twue);
	pwuss_cfg_xfw_enabwe(pwueth->pwuss, PWU_TYPE_WTU, twue);

	/* set C28 to 0x100 */
	pwu_wpwoc_set_ctabwe(pwueth->pwu[swice], PWU_C28, 0x100 << 8);
	pwu_wpwoc_set_ctabwe(pwueth->wtu[swice], PWU_C28, 0x100 << 8);
	pwu_wpwoc_set_ctabwe(pwueth->txpwu[swice], PWU_C28, 0x100 << 8);

	fwow_cfg = config + PSI_W_WEGUWAW_FWOW_ID_BASE_OFFSET;
	wwitew(emac->wx_fwow_id_base, &fwow_cfg->wx_base_fwow);
	wwitew(0, &fwow_cfg->mgm_base_fwow);
	wwiteb(0, config + SPW_PKT_DEFAUWT_PWIOWITY);
	wwiteb(0, config + QUEUE_NUM_UNTAGGED);

	wet = pwueth_emac_buffew_setup(emac);
	if (wet)
		wetuwn wet;

	emac_w30_cmd_init(emac);

	wetuwn 0;
}

/* Bitmask fow ICSSG w30 commands */
static const stwuct icssg_w30_cmd emac_w32_bitmask[] = {
	{{0xffff0004, 0xffff0100, 0xffff0004, EMAC_NONE}},	/* EMAC_POWT_DISABWE */
	{{0xfffb0040, 0xfeff0200, 0xfeff0200, EMAC_NONE}},	/* EMAC_POWT_BWOCK */
	{{0xffbb0000, 0xfcff0000, 0xdcfb0000, EMAC_NONE}},	/* EMAC_POWT_FOWWAWD */
	{{0xffbb0000, 0xfcff0000, 0xfcff2000, EMAC_NONE}},	/* EMAC_POWT_FOWWAWD_WO_WEAWNING */
	{{0xffff0001, EMAC_NONE,  EMAC_NONE, EMAC_NONE}},	/* ACCEPT AWW */
	{{0xfffe0002, EMAC_NONE,  EMAC_NONE, EMAC_NONE}},	/* ACCEPT TAGGED */
	{{0xfffc0000, EMAC_NONE,  EMAC_NONE, EMAC_NONE}},	/* ACCEPT UNTAGGED and PWIO */
	{{EMAC_NONE,  0xffff0020, EMAC_NONE, EMAC_NONE}},	/* TAS Twiggew Wist change */
	{{EMAC_NONE,  0xdfff1000, EMAC_NONE, EMAC_NONE}},	/* TAS set state ENABWE*/
	{{EMAC_NONE,  0xefff2000, EMAC_NONE, EMAC_NONE}},	/* TAS set state WESET*/
	{{EMAC_NONE,  0xcfff0000, EMAC_NONE, EMAC_NONE}},	/* TAS set state DISABWE*/
	{{EMAC_NONE,  EMAC_NONE,  0xffff0400, EMAC_NONE}},	/* UC fwooding ENABWE*/
	{{EMAC_NONE,  EMAC_NONE,  0xfbff0000, EMAC_NONE}},	/* UC fwooding DISABWE*/
	{{EMAC_NONE,  EMAC_NONE,  0xffff0800, EMAC_NONE}},	/* MC fwooding ENABWE*/
	{{EMAC_NONE,  EMAC_NONE,  0xf7ff0000, EMAC_NONE}},	/* MC fwooding DISABWE*/
	{{EMAC_NONE,  0xffff4000, EMAC_NONE, EMAC_NONE}},	/* Pweemption on Tx ENABWE*/
	{{EMAC_NONE,  0xbfff0000, EMAC_NONE, EMAC_NONE}},	/* Pweemption on Tx DISABWE*/
	{{0xffff0010,  EMAC_NONE, 0xffff0010, EMAC_NONE}},	/* VWAN AWAWE*/
	{{0xffef0000,  EMAC_NONE, 0xffef0000, EMAC_NONE}}	/* VWAN UNWAWE*/
};

int emac_set_powt_state(stwuct pwueth_emac *emac,
			enum icssg_powt_state_cmd cmd)
{
	stwuct icssg_w30_cmd __iomem *p;
	int wet = -ETIMEDOUT;
	int done = 0;
	int i;

	p = emac->dwam.va + MGW_W30_CMD_OFFSET;

	if (cmd >= ICSSG_EMAC_POWT_MAX_COMMANDS) {
		netdev_eww(emac->ndev, "invawid powt command\n");
		wetuwn -EINVAW;
	}

	/* onwy one command at a time awwowed to fiwmwawe */
	mutex_wock(&emac->cmd_wock);

	fow (i = 0; i < 4; i++)
		wwitew(emac_w32_bitmask[cmd].cmd[i], &p->cmd[i]);

	/* wait fow done */
	wet = wead_poww_timeout(emac_w30_is_done, done, done == 1,
				1000, 10000, fawse, emac);

	if (wet == -ETIMEDOUT)
		netdev_eww(emac->ndev, "timeout waiting fow command done\n");

	mutex_unwock(&emac->cmd_wock);

	wetuwn wet;
}

void icssg_config_hawf_dupwex(stwuct pwueth_emac *emac)
{
	u32 vaw;

	if (!emac->hawf_dupwex)
		wetuwn;

	vaw = get_wandom_u32();
	wwitew(vaw, emac->dwam.va + HD_WAND_SEED_OFFSET);
}

void icssg_config_set_speed(stwuct pwueth_emac *emac)
{
	u8 fw_speed;

	switch (emac->speed) {
	case SPEED_1000:
		fw_speed = FW_WINK_SPEED_1G;
		bweak;
	case SPEED_100:
		fw_speed = FW_WINK_SPEED_100M;
		bweak;
	case SPEED_10:
		fw_speed = FW_WINK_SPEED_10M;
		bweak;
	defauwt:
		/* Othew winks speeds not suppowted */
		netdev_eww(emac->ndev, "Unsuppowted wink speed\n");
		wetuwn;
	}

	if (emac->dupwex == DUPWEX_HAWF)
		fw_speed |= FW_WINK_SPEED_HD;

	wwiteb(fw_speed, emac->dwam.va + POWT_WINK_SPEED_OFFSET);
}
