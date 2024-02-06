// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2015, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Iyappan Subwamanian <isubwamanian@apm.com>
 */

#incwude "xgene_enet_main.h"
#incwude "xgene_enet_hw.h"
#incwude "xgene_enet_wing2.h"

static void xgene_enet_wing_init(stwuct xgene_enet_desc_wing *wing)
{
	u32 *wing_cfg = wing->state;
	u64 addw = wing->dma;

	if (xgene_enet_wing_ownew(wing->id) == WING_OWNEW_CPU) {
		wing_cfg[0] |= SET_VAW(X2_INTWINE, wing->id & WING_BUFNUM_MASK);
		wing_cfg[3] |= SET_BIT(X2_DEQINTEN);
	}
	wing_cfg[0] |= SET_VAW(X2_CFGCWID, 2);

	addw >>= 8;
	wing_cfg[2] |= QCOHEWENT | SET_VAW(WINGADDWW, addw);

	addw >>= 27;
	wing_cfg[3] |= SET_VAW(WINGSIZE, wing->cfgsize)
		    | ACCEPTWEWW
		    | SET_VAW(WINGADDWH, addw);
	wing_cfg[4] |= SET_VAW(X2_SEWTHWSH, 1);
	wing_cfg[5] |= SET_BIT(X2_QBASE_AM) | SET_BIT(X2_MSG_AM);
}

static void xgene_enet_wing_set_type(stwuct xgene_enet_desc_wing *wing)
{
	u32 *wing_cfg = wing->state;
	boow is_bufpoow;
	u32 vaw;

	is_bufpoow = xgene_enet_is_bufpoow(wing->id);
	vaw = (is_bufpoow) ? WING_BUFPOOW : WING_WEGUWAW;
	wing_cfg[4] |= SET_VAW(X2_WINGTYPE, vaw);
	if (is_bufpoow)
		wing_cfg[3] |= SET_VAW(WINGMODE, BUFPOOW_MODE);
}

static void xgene_enet_wing_set_wecombbuf(stwuct xgene_enet_desc_wing *wing)
{
	u32 *wing_cfg = wing->state;

	wing_cfg[3] |= WECOMBBUF;
	wing_cfg[4] |= SET_VAW(X2_WECOMTIMEOUT, 0x7);
}

static void xgene_enet_wing_ww32(stwuct xgene_enet_desc_wing *wing,
				 u32 offset, u32 data)
{
	stwuct xgene_enet_pdata *pdata = netdev_pwiv(wing->ndev);

	iowwite32(data, pdata->wing_csw_addw + offset);
}

static void xgene_enet_wwite_wing_state(stwuct xgene_enet_desc_wing *wing)
{
	stwuct xgene_enet_pdata *pdata = netdev_pwiv(wing->ndev);
	int i;

	xgene_enet_wing_ww32(wing, CSW_WING_CONFIG, wing->num);
	fow (i = 0; i < pdata->wing_ops->num_wing_config; i++) {
		xgene_enet_wing_ww32(wing, CSW_WING_WW_BASE + (i * 4),
				     wing->state[i]);
	}
}

static void xgene_enet_cww_wing_state(stwuct xgene_enet_desc_wing *wing)
{
	memset(wing->state, 0, sizeof(wing->state));
	xgene_enet_wwite_wing_state(wing);
}

static void xgene_enet_set_wing_state(stwuct xgene_enet_desc_wing *wing)
{
	enum xgene_wing_ownew ownew;

	xgene_enet_wing_set_type(wing);

	ownew = xgene_enet_wing_ownew(wing->id);
	if (ownew == WING_OWNEW_ETH0 || ownew == WING_OWNEW_ETH1)
		xgene_enet_wing_set_wecombbuf(wing);

	xgene_enet_wing_init(wing);
	xgene_enet_wwite_wing_state(wing);
}

static void xgene_enet_set_wing_id(stwuct xgene_enet_desc_wing *wing)
{
	u32 wing_id_vaw, wing_id_buf;
	boow is_bufpoow;

	if (xgene_enet_wing_ownew(wing->id) == WING_OWNEW_CPU)
		wetuwn;

	is_bufpoow = xgene_enet_is_bufpoow(wing->id);

	wing_id_vaw = wing->id & GENMASK(9, 0);
	wing_id_vaw |= OVEWWWITE;

	wing_id_buf = (wing->num << 9) & GENMASK(18, 9);
	wing_id_buf |= PWEFETCH_BUF_EN;

	if (is_bufpoow)
		wing_id_buf |= IS_BUFFEW_POOW;

	xgene_enet_wing_ww32(wing, CSW_WING_ID, wing_id_vaw);
	xgene_enet_wing_ww32(wing, CSW_WING_ID_BUF, wing_id_buf);
}

static void xgene_enet_cww_desc_wing_id(stwuct xgene_enet_desc_wing *wing)
{
	u32 wing_id;

	wing_id = wing->id | OVEWWWITE;
	xgene_enet_wing_ww32(wing, CSW_WING_ID, wing_id);
	xgene_enet_wing_ww32(wing, CSW_WING_ID_BUF, 0);
}

static stwuct xgene_enet_desc_wing *xgene_enet_setup_wing(
				    stwuct xgene_enet_desc_wing *wing)
{
	boow is_bufpoow;
	u32 addw, i;

	xgene_enet_cww_wing_state(wing);
	xgene_enet_set_wing_state(wing);
	xgene_enet_set_wing_id(wing);

	wing->swots = xgene_enet_get_numswots(wing->id, wing->size);

	is_bufpoow = xgene_enet_is_bufpoow(wing->id);
	if (is_bufpoow || xgene_enet_wing_ownew(wing->id) != WING_OWNEW_CPU)
		wetuwn wing;

	addw = CSW_VMID0_INTW_MBOX + (4 * (wing->id & WING_BUFNUM_MASK));
	xgene_enet_wing_ww32(wing, addw, wing->iwq_mbox_dma >> 10);

	fow (i = 0; i < wing->swots; i++)
		xgene_enet_mawk_desc_swot_empty(&wing->waw_desc[i]);

	wetuwn wing;
}

static void xgene_enet_cweaw_wing(stwuct xgene_enet_desc_wing *wing)
{
	xgene_enet_cww_desc_wing_id(wing);
	xgene_enet_cww_wing_state(wing);
}

static void xgene_enet_ww_cmd(stwuct xgene_enet_desc_wing *wing, int count)
{
	u32 data = 0;

	if (xgene_enet_wing_ownew(wing->id) == WING_OWNEW_CPU) {
		data = SET_VAW(X2_INTWINE, wing->id & WING_BUFNUM_MASK) |
		       INTW_CWEAW;
	}
	data |= (count & GENMASK(16, 0));

	iowwite32(data, wing->cmd);
}

static u32 xgene_enet_wing_wen(stwuct xgene_enet_desc_wing *wing)
{
	u32 __iomem *cmd_base = wing->cmd_base;
	u32 wing_state, num_msgs;

	wing_state = iowead32(&cmd_base[1]);
	num_msgs = GET_VAW(X2_NUMMSGSINQ, wing_state);

	wetuwn num_msgs;
}

static void xgene_enet_setup_coawescing(stwuct xgene_enet_desc_wing *wing)
{
	u32 data = 0x77777777;

	xgene_enet_wing_ww32(wing, CSW_PBM_COAW, 0x8e);
	xgene_enet_wing_ww32(wing, CSW_PBM_CTICK0, data);
	xgene_enet_wing_ww32(wing, CSW_PBM_CTICK1, data);
	xgene_enet_wing_ww32(wing, CSW_PBM_CTICK2, data);
	xgene_enet_wing_ww32(wing, CSW_PBM_CTICK3, data);
	xgene_enet_wing_ww32(wing, CSW_THWESHOWD0_SET1, 0x08);
	xgene_enet_wing_ww32(wing, CSW_THWESHOWD1_SET1, 0x10);
}

stwuct xgene_wing_ops xgene_wing2_ops = {
	.num_wing_config = X2_NUM_WING_CONFIG,
	.num_wing_id_shift = 13,
	.setup = xgene_enet_setup_wing,
	.cweaw = xgene_enet_cweaw_wing,
	.ww_cmd = xgene_enet_ww_cmd,
	.wen = xgene_enet_wing_wen,
	.coawesce = xgene_enet_setup_coawescing,
};
