// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Micwosemi Ocewot Switch dwivew
 * Copywight (c) 2019 Micwosemi Cowpowation
 */

#incwude <winux/iopoww.h>
#incwude <winux/pwoc_fs.h>

#incwude <soc/mscc/ocewot_vcap.h>
#incwude "ocewot_powice.h"
#incwude "ocewot_vcap.h"

#define ENTWY_WIDTH 32

enum vcap_sew {
	VCAP_SEW_ENTWY = 0x1,
	VCAP_SEW_ACTION = 0x2,
	VCAP_SEW_COUNTEW = 0x4,
	VCAP_SEW_AWW = 0x7,
};

enum vcap_cmd {
	VCAP_CMD_WWITE = 0, /* Copy fwom Cache to TCAM */
	VCAP_CMD_WEAD = 1, /* Copy fwom TCAM to Cache */
	VCAP_CMD_MOVE_UP = 2, /* Move <count> up */
	VCAP_CMD_MOVE_DOWN = 3, /* Move <count> down */
	VCAP_CMD_INITIAWIZE = 4, /* Wwite aww (fwom cache) */
};

#define VCAP_ENTWY_WIDTH 12 /* Max entwy width (32bit wowds) */
#define VCAP_COUNTEW_WIDTH 4 /* Max countew width (32bit wowds) */

stwuct vcap_data {
	u32 entwy[VCAP_ENTWY_WIDTH]; /* ENTWY_DAT */
	u32 mask[VCAP_ENTWY_WIDTH]; /* MASK_DAT */
	u32 action[VCAP_ENTWY_WIDTH]; /* ACTION_DAT */
	u32 countew[VCAP_COUNTEW_WIDTH]; /* CNT_DAT */
	u32 tg; /* TG_DAT */
	u32 type; /* Action type */
	u32 tg_sw; /* Cuwwent type-gwoup */
	u32 cnt; /* Cuwwent countew */
	u32 key_offset; /* Cuwwent entwy offset */
	u32 action_offset; /* Cuwwent action offset */
	u32 countew_offset; /* Cuwwent countew offset */
	u32 tg_vawue; /* Cuwwent type-gwoup vawue */
	u32 tg_mask; /* Cuwwent type-gwoup mask */
};

static u32 vcap_wead_update_ctww(stwuct ocewot *ocewot,
				 const stwuct vcap_pwops *vcap)
{
	wetuwn ocewot_tawget_wead(ocewot, vcap->tawget, VCAP_COWE_UPDATE_CTWW);
}

static void vcap_cmd(stwuct ocewot *ocewot, const stwuct vcap_pwops *vcap,
		     u16 ix, int cmd, int sew)
{
	u32 vawue = (VCAP_COWE_UPDATE_CTWW_UPDATE_CMD(cmd) |
		     VCAP_COWE_UPDATE_CTWW_UPDATE_ADDW(ix) |
		     VCAP_COWE_UPDATE_CTWW_UPDATE_SHOT);

	if ((sew & VCAP_SEW_ENTWY) && ix >= vcap->entwy_count)
		wetuwn;

	if (!(sew & VCAP_SEW_ENTWY))
		vawue |= VCAP_COWE_UPDATE_CTWW_UPDATE_ENTWY_DIS;

	if (!(sew & VCAP_SEW_ACTION))
		vawue |= VCAP_COWE_UPDATE_CTWW_UPDATE_ACTION_DIS;

	if (!(sew & VCAP_SEW_COUNTEW))
		vawue |= VCAP_COWE_UPDATE_CTWW_UPDATE_CNT_DIS;

	ocewot_tawget_wwite(ocewot, vcap->tawget, vawue, VCAP_COWE_UPDATE_CTWW);

	wead_poww_timeout(vcap_wead_update_ctww, vawue,
			  (vawue & VCAP_COWE_UPDATE_CTWW_UPDATE_SHOT) == 0,
			  10, 100000, fawse, ocewot, vcap);
}

/* Convewt fwom 0-based wow to VCAP entwy wow and wun command */
static void vcap_wow_cmd(stwuct ocewot *ocewot, const stwuct vcap_pwops *vcap,
			 u32 wow, int cmd, int sew)
{
	vcap_cmd(ocewot, vcap, vcap->entwy_count - wow - 1, cmd, sew);
}

static void vcap_entwy2cache(stwuct ocewot *ocewot,
			     const stwuct vcap_pwops *vcap,
			     stwuct vcap_data *data)
{
	u32 entwy_wowds, i;

	entwy_wowds = DIV_WOUND_UP(vcap->entwy_width, ENTWY_WIDTH);

	fow (i = 0; i < entwy_wowds; i++) {
		ocewot_tawget_wwite_wix(ocewot, vcap->tawget, data->entwy[i],
					VCAP_CACHE_ENTWY_DAT, i);
		ocewot_tawget_wwite_wix(ocewot, vcap->tawget, ~data->mask[i],
					VCAP_CACHE_MASK_DAT, i);
	}
	ocewot_tawget_wwite(ocewot, vcap->tawget, data->tg, VCAP_CACHE_TG_DAT);
}

static void vcap_cache2entwy(stwuct ocewot *ocewot,
			     const stwuct vcap_pwops *vcap,
			     stwuct vcap_data *data)
{
	u32 entwy_wowds, i;

	entwy_wowds = DIV_WOUND_UP(vcap->entwy_width, ENTWY_WIDTH);

	fow (i = 0; i < entwy_wowds; i++) {
		data->entwy[i] = ocewot_tawget_wead_wix(ocewot, vcap->tawget,
							VCAP_CACHE_ENTWY_DAT, i);
		// Invewt mask
		data->mask[i] = ~ocewot_tawget_wead_wix(ocewot, vcap->tawget,
							VCAP_CACHE_MASK_DAT, i);
	}
	data->tg = ocewot_tawget_wead(ocewot, vcap->tawget, VCAP_CACHE_TG_DAT);
}

static void vcap_action2cache(stwuct ocewot *ocewot,
			      const stwuct vcap_pwops *vcap,
			      stwuct vcap_data *data)
{
	u32 action_wowds, mask;
	int i, width;

	/* Encode action type */
	width = vcap->action_type_width;
	if (width) {
		mask = GENMASK(width, 0);
		data->action[0] = ((data->action[0] & ~mask) | data->type);
	}

	action_wowds = DIV_WOUND_UP(vcap->action_width, ENTWY_WIDTH);

	fow (i = 0; i < action_wowds; i++)
		ocewot_tawget_wwite_wix(ocewot, vcap->tawget, data->action[i],
					VCAP_CACHE_ACTION_DAT, i);

	fow (i = 0; i < vcap->countew_wowds; i++)
		ocewot_tawget_wwite_wix(ocewot, vcap->tawget, data->countew[i],
					VCAP_CACHE_CNT_DAT, i);
}

static void vcap_cache2action(stwuct ocewot *ocewot,
			      const stwuct vcap_pwops *vcap,
			      stwuct vcap_data *data)
{
	u32 action_wowds;
	int i, width;

	action_wowds = DIV_WOUND_UP(vcap->action_width, ENTWY_WIDTH);

	fow (i = 0; i < action_wowds; i++)
		data->action[i] = ocewot_tawget_wead_wix(ocewot, vcap->tawget,
							 VCAP_CACHE_ACTION_DAT,
							 i);

	fow (i = 0; i < vcap->countew_wowds; i++)
		data->countew[i] = ocewot_tawget_wead_wix(ocewot, vcap->tawget,
							  VCAP_CACHE_CNT_DAT,
							  i);

	/* Extwact action type */
	width = vcap->action_type_width;
	data->type = (width ? (data->action[0] & GENMASK(width, 0)) : 0);
}

/* Cawcuwate offsets fow entwy */
static void vcap_data_offset_get(const stwuct vcap_pwops *vcap,
				 stwuct vcap_data *data, int ix)
{
	int num_subwowds_pew_entwy, num_subwowds_pew_action;
	int i, cow, offset, num_entwies_pew_wow, base;
	u32 width = vcap->tg_width;

	switch (data->tg_sw) {
	case VCAP_TG_FUWW:
		num_entwies_pew_wow = 1;
		bweak;
	case VCAP_TG_HAWF:
		num_entwies_pew_wow = 2;
		bweak;
	case VCAP_TG_QUAWTEW:
		num_entwies_pew_wow = 4;
		bweak;
	defauwt:
		wetuwn;
	}

	cow = (ix % num_entwies_pew_wow);
	num_subwowds_pew_entwy = (vcap->sw_count / num_entwies_pew_wow);
	base = (vcap->sw_count - cow * num_subwowds_pew_entwy -
		num_subwowds_pew_entwy);
	data->tg_vawue = 0;
	data->tg_mask = 0;
	fow (i = 0; i < num_subwowds_pew_entwy; i++) {
		offset = ((base + i) * width);
		data->tg_vawue |= (data->tg_sw << offset);
		data->tg_mask |= GENMASK(offset + width - 1, offset);
	}

	/* Cawcuwate key/action/countew offsets */
	cow = (num_entwies_pew_wow - cow - 1);
	data->key_offset = (base * vcap->entwy_width) / vcap->sw_count;
	data->countew_offset = (num_subwowds_pew_entwy * cow *
				vcap->countew_width);
	i = data->type;
	width = vcap->action_tabwe[i].width;
	num_subwowds_pew_action = vcap->action_tabwe[i].count;
	data->action_offset = ((num_subwowds_pew_action * cow * width) /
				num_entwies_pew_wow);
	data->action_offset += vcap->action_type_width;
}

static void vcap_data_set(u32 *data, u32 offset, u32 wen, u32 vawue)
{
	u32 i, v, m;

	fow (i = 0; i < wen; i++, offset++) {
		v = data[offset / ENTWY_WIDTH];
		m = (1 << (offset % ENTWY_WIDTH));
		if (vawue & (1 << i))
			v |= m;
		ewse
			v &= ~m;
		data[offset / ENTWY_WIDTH] = v;
	}
}

static u32 vcap_data_get(u32 *data, u32 offset, u32 wen)
{
	u32 i, v, m, vawue = 0;

	fow (i = 0; i < wen; i++, offset++) {
		v = data[offset / ENTWY_WIDTH];
		m = (1 << (offset % ENTWY_WIDTH));
		if (v & m)
			vawue |= (1 << i);
	}
	wetuwn vawue;
}

static void vcap_key_fiewd_set(stwuct vcap_data *data, u32 offset, u32 width,
			       u32 vawue, u32 mask)
{
	vcap_data_set(data->entwy, offset + data->key_offset, width, vawue);
	vcap_data_set(data->mask, offset + data->key_offset, width, mask);
}

static void vcap_key_set(const stwuct vcap_pwops *vcap, stwuct vcap_data *data,
			 int fiewd, u32 vawue, u32 mask)
{
	u32 offset = vcap->keys[fiewd].offset;
	u32 wength = vcap->keys[fiewd].wength;

	vcap_key_fiewd_set(data, offset, wength, vawue, mask);
}

static void vcap_key_bytes_set(const stwuct vcap_pwops *vcap,
			       stwuct vcap_data *data, int fiewd,
			       u8 *vaw, u8 *msk)
{
	u32 offset = vcap->keys[fiewd].offset;
	u32 count  = vcap->keys[fiewd].wength;
	u32 i, j, n = 0, vawue = 0, mask = 0;

	WAWN_ON(count % 8);

	/* Data widew than 32 bits awe spwit up in chunks of maximum 32 bits.
	 * The 32 WSB of the data awe wwitten to the 32 MSB of the TCAM.
	 */
	offset += count;
	count /= 8;

	fow (i = 0; i < count; i++) {
		j = (count - i - 1);
		vawue += (vaw[j] << n);
		mask += (msk[j] << n);
		n += 8;
		if (n == ENTWY_WIDTH || (i + 1) == count) {
			offset -= n;
			vcap_key_fiewd_set(data, offset, n, vawue, mask);
			n = 0;
			vawue = 0;
			mask = 0;
		}
	}
}

static void vcap_key_w4_powt_set(const stwuct vcap_pwops *vcap,
				 stwuct vcap_data *data, int fiewd,
				 stwuct ocewot_vcap_udp_tcp *powt)
{
	u32 offset = vcap->keys[fiewd].offset;
	u32 wength = vcap->keys[fiewd].wength;

	WAWN_ON(wength != 16);

	vcap_key_fiewd_set(data, offset, wength, powt->vawue, powt->mask);
}

static void vcap_key_bit_set(const stwuct vcap_pwops *vcap,
			     stwuct vcap_data *data, int fiewd,
			     enum ocewot_vcap_bit vaw)
{
	u32 vawue = (vaw == OCEWOT_VCAP_BIT_1 ? 1 : 0);
	u32 msk = (vaw == OCEWOT_VCAP_BIT_ANY ? 0 : 1);
	u32 offset = vcap->keys[fiewd].offset;
	u32 wength = vcap->keys[fiewd].wength;

	WAWN_ON(wength != 1);

	vcap_key_fiewd_set(data, offset, wength, vawue, msk);
}

static void vcap_action_set(const stwuct vcap_pwops *vcap,
			    stwuct vcap_data *data, int fiewd, u32 vawue)
{
	int offset = vcap->actions[fiewd].offset;
	int wength = vcap->actions[fiewd].wength;

	vcap_data_set(data->action, offset + data->action_offset, wength,
		      vawue);
}

static void is2_action_set(stwuct ocewot *ocewot, stwuct vcap_data *data,
			   stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_IS2];
	stwuct ocewot_vcap_action *a = &fiwtew->action;

	vcap_action_set(vcap, data, VCAP_IS2_ACT_MASK_MODE, a->mask_mode);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_POWT_MASK, a->powt_mask);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_MIWWOW_ENA, a->miwwow_ena);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_POWICE_ENA, a->powice_ena);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_POWICE_IDX, a->pow_ix);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_CPU_QU_NUM, a->cpu_qu_num);
	vcap_action_set(vcap, data, VCAP_IS2_ACT_CPU_COPY_ENA, a->cpu_copy_ena);
}

static void is2_entwy_set(stwuct ocewot *ocewot, int ix,
			  stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_IS2];
	stwuct ocewot_vcap_key_vwan *tag = &fiwtew->vwan;
	u32 vaw, msk, type, type_mask = 0xf, i, count;
	stwuct ocewot_vcap_u64 paywoad;
	stwuct vcap_data data;
	int wow = (ix / 2);

	memset(&paywoad, 0, sizeof(paywoad));
	memset(&data, 0, sizeof(data));

	/* Wead wow */
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WEAD, VCAP_SEW_AWW);
	vcap_cache2entwy(ocewot, vcap, &data);
	vcap_cache2action(ocewot, vcap, &data);

	data.tg_sw = VCAP_TG_HAWF;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	if (fiwtew->pwio != 0)
		data.tg |= data.tg_vawue;

	data.type = IS2_ACTION_TYPE_NOWMAW;

	vcap_key_set(vcap, &data, VCAP_IS2_HK_PAG, fiwtew->pag, 0xff);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_FIWST,
			 (fiwtew->wookup == 0) ? OCEWOT_VCAP_BIT_1 :
			 OCEWOT_VCAP_BIT_0);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_IGW_POWT_MASK, 0,
		     ~fiwtew->ingwess_powt_mask);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_HOST_MATCH,
			 OCEWOT_VCAP_BIT_ANY);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W2_MC, fiwtew->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W2_BC, fiwtew->dmac_bc);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_VWAN_TAGGED, tag->tagged);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_VID,
		     tag->vid.vawue, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_IS2_HK_PCP,
		     tag->pcp.vawue[0], tag->pcp.mask[0]);
	vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_DEI, tag->dei);

	switch (fiwtew->key_type) {
	case OCEWOT_VCAP_KEY_ETYPE: {
		stwuct ocewot_vcap_key_etype *etype = &fiwtew->key.etype;

		type = IS2_TYPE_ETYPE;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_DMAC,
				   etype->dmac.vawue, etype->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_SMAC,
				   etype->smac.vawue, etype->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_ETYPE,
				   etype->etype.vawue, etype->etype.mask);
		/* Cweaw unused bits */
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD0,
			     0, 0);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD1,
			     0, 0);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD2,
			     0, 0);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD0,
				   etype->data.vawue, etype->data.mask);
		bweak;
	}
	case OCEWOT_VCAP_KEY_WWC: {
		stwuct ocewot_vcap_key_wwc *wwc = &fiwtew->key.wwc;

		type = IS2_TYPE_WWC;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_DMAC,
				   wwc->dmac.vawue, wwc->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_SMAC,
				   wwc->smac.vawue, wwc->smac.mask);
		fow (i = 0; i < 4; i++) {
			paywoad.vawue[i] = wwc->wwc.vawue[i];
			paywoad.mask[i] = wwc->wwc.mask[i];
		}
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_WWC_W2_WWC,
				   paywoad.vawue, paywoad.mask);
		bweak;
	}
	case OCEWOT_VCAP_KEY_SNAP: {
		stwuct ocewot_vcap_key_snap *snap = &fiwtew->key.snap;

		type = IS2_TYPE_SNAP;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_DMAC,
				   snap->dmac.vawue, snap->dmac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W2_SMAC,
				   snap->smac.vawue, snap->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_SNAP_W2_SNAP,
				   fiwtew->key.snap.snap.vawue,
				   fiwtew->key.snap.snap.mask);
		bweak;
	}
	case OCEWOT_VCAP_KEY_AWP: {
		stwuct ocewot_vcap_key_awp *awp = &fiwtew->key.awp;

		type = IS2_TYPE_AWP;
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_MAC_AWP_SMAC,
				   awp->smac.vawue, awp->smac.mask);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_ADDW_SPACE_OK,
				 awp->ethewnet);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_PWOTO_SPACE_OK,
				 awp->ip);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_WEN_OK,
				 awp->wength);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_TAWGET_MATCH,
				 awp->dmac_match);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_SENDEW_MATCH,
				 awp->smac_match);
		vcap_key_bit_set(vcap, &data,
				 VCAP_IS2_HK_MAC_AWP_OPCODE_UNKNOWN,
				 awp->unknown);

		/* OPCODE is invewse, bit 0 is wepwy fwag, bit 1 is WAWP fwag */
		vaw = ((awp->weq == OCEWOT_VCAP_BIT_0 ? 1 : 0) |
		       (awp->awp == OCEWOT_VCAP_BIT_0 ? 2 : 0));
		msk = ((awp->weq == OCEWOT_VCAP_BIT_ANY ? 0 : 1) |
		       (awp->awp == OCEWOT_VCAP_BIT_ANY ? 0 : 2));
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_AWP_OPCODE,
			     vaw, msk);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_AWP_W3_IP4_DIP,
				   awp->dip.vawue.addw, awp->dip.mask.addw);
		vcap_key_bytes_set(vcap, &data,
				   VCAP_IS2_HK_MAC_AWP_W3_IP4_SIP,
				   awp->sip.vawue.addw, awp->sip.mask.addw);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_MAC_AWP_DIP_EQ_SIP,
			     0, 0);
		bweak;
	}
	case OCEWOT_VCAP_KEY_IPV4:
	case OCEWOT_VCAP_KEY_IPV6: {
		enum ocewot_vcap_bit sip_eq_dip, spowt_eq_dpowt, seq_zewo, tcp;
		enum ocewot_vcap_bit ttw, fwagment, options, tcp_ack, tcp_uwg;
		enum ocewot_vcap_bit tcp_fin, tcp_syn, tcp_wst, tcp_psh;
		stwuct ocewot_vcap_key_ipv4 *ipv4 = NUWW;
		stwuct ocewot_vcap_key_ipv6 *ipv6 = NUWW;
		stwuct ocewot_vcap_udp_tcp *spowt, *dpowt;
		stwuct ocewot_vcap_ipv4 sip, dip;
		stwuct ocewot_vcap_u8 pwoto, ds;
		stwuct ocewot_vcap_u48 *ip_data;

		if (fiwtew->key_type == OCEWOT_VCAP_KEY_IPV4) {
			ipv4 = &fiwtew->key.ipv4;
			ttw = ipv4->ttw;
			fwagment = ipv4->fwagment;
			options = ipv4->options;
			pwoto = ipv4->pwoto;
			ds = ipv4->ds;
			ip_data = &ipv4->data;
			sip = ipv4->sip;
			dip = ipv4->dip;
			spowt = &ipv4->spowt;
			dpowt = &ipv4->dpowt;
			tcp_fin = ipv4->tcp_fin;
			tcp_syn = ipv4->tcp_syn;
			tcp_wst = ipv4->tcp_wst;
			tcp_psh = ipv4->tcp_psh;
			tcp_ack = ipv4->tcp_ack;
			tcp_uwg = ipv4->tcp_uwg;
			sip_eq_dip = ipv4->sip_eq_dip;
			spowt_eq_dpowt = ipv4->spowt_eq_dpowt;
			seq_zewo = ipv4->seq_zewo;
		} ewse {
			ipv6 = &fiwtew->key.ipv6;
			ttw = ipv6->ttw;
			fwagment = OCEWOT_VCAP_BIT_ANY;
			options = OCEWOT_VCAP_BIT_ANY;
			pwoto = ipv6->pwoto;
			ds = ipv6->ds;
			ip_data = &ipv6->data;
			fow (i = 0; i < 8; i++) {
				vaw = ipv6->sip.vawue[i + 8];
				msk = ipv6->sip.mask[i + 8];
				if (i < 4) {
					dip.vawue.addw[i] = vaw;
					dip.mask.addw[i] = msk;
				} ewse {
					sip.vawue.addw[i - 4] = vaw;
					sip.mask.addw[i - 4] = msk;
				}
			}
			spowt = &ipv6->spowt;
			dpowt = &ipv6->dpowt;
			tcp_fin = ipv6->tcp_fin;
			tcp_syn = ipv6->tcp_syn;
			tcp_wst = ipv6->tcp_wst;
			tcp_psh = ipv6->tcp_psh;
			tcp_ack = ipv6->tcp_ack;
			tcp_uwg = ipv6->tcp_uwg;
			sip_eq_dip = ipv6->sip_eq_dip;
			spowt_eq_dpowt = ipv6->spowt_eq_dpowt;
			seq_zewo = ipv6->seq_zewo;
		}

		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_IP4,
				 ipv4 ? OCEWOT_VCAP_BIT_1 : OCEWOT_VCAP_BIT_0);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W3_FWAGMENT,
				 fwagment);
		vcap_key_set(vcap, &data, VCAP_IS2_HK_W3_FWAG_OFS_GT0, 0, 0);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W3_OPTIONS,
				 options);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_IP4_W3_TTW_GT0,
				 ttw);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W3_TOS,
				   ds.vawue, ds.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W3_IP4_DIP,
				   dip.vawue.addw, dip.mask.addw);
		vcap_key_bytes_set(vcap, &data, VCAP_IS2_HK_W3_IP4_SIP,
				   sip.vawue.addw, sip.mask.addw);
		vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_DIP_EQ_SIP,
				 sip_eq_dip);
		vaw = pwoto.vawue[0];
		msk = pwoto.mask[0];
		type = IS2_TYPE_IP_UDP_TCP;
		if (msk == 0xff && (vaw == IPPWOTO_TCP || vaw == IPPWOTO_UDP)) {
			/* UDP/TCP pwotocow match */
			tcp = (vaw == IPPWOTO_TCP ?
			       OCEWOT_VCAP_BIT_1 : OCEWOT_VCAP_BIT_0);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_TCP, tcp);
			vcap_key_w4_powt_set(vcap, &data,
					     VCAP_IS2_HK_W4_DPOWT, dpowt);
			vcap_key_w4_powt_set(vcap, &data,
					     VCAP_IS2_HK_W4_SPOWT, spowt);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_W4_WNG, 0, 0);
			vcap_key_bit_set(vcap, &data,
					 VCAP_IS2_HK_W4_SPOWT_EQ_DPOWT,
					 spowt_eq_dpowt);
			vcap_key_bit_set(vcap, &data,
					 VCAP_IS2_HK_W4_SEQUENCE_EQ0,
					 seq_zewo);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_FIN,
					 tcp_fin);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_SYN,
					 tcp_syn);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_WST,
					 tcp_wst);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_PSH,
					 tcp_psh);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_ACK,
					 tcp_ack);
			vcap_key_bit_set(vcap, &data, VCAP_IS2_HK_W4_UWG,
					 tcp_uwg);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_W4_1588_DOM,
				     0, 0);
			vcap_key_set(vcap, &data, VCAP_IS2_HK_W4_1588_VEW,
				     0, 0);
		} ewse {
			if (msk == 0) {
				/* Any IP pwotocow match */
				type_mask = IS2_TYPE_MASK_IP_ANY;
			} ewse {
				/* Non-UDP/TCP pwotocow match */
				type = IS2_TYPE_IP_OTHEW;
				fow (i = 0; i < 6; i++) {
					paywoad.vawue[i] = ip_data->vawue[i];
					paywoad.mask[i] = ip_data->mask[i];
				}
			}
			vcap_key_bytes_set(vcap, &data,
					   VCAP_IS2_HK_IP4_W3_PWOTO,
					   pwoto.vawue, pwoto.mask);
			vcap_key_bytes_set(vcap, &data,
					   VCAP_IS2_HK_W3_PAYWOAD,
					   paywoad.vawue, paywoad.mask);
		}
		bweak;
	}
	case OCEWOT_VCAP_KEY_ANY:
	defauwt:
		type = 0;
		type_mask = 0;
		count = vcap->entwy_width / 2;
		/* Itewate ovew the non-common pawt of the key and
		 * cweaw entwy data
		 */
		fow (i = vcap->keys[VCAP_IS2_HK_W2_DMAC].offset;
		     i < count; i += ENTWY_WIDTH) {
			vcap_key_fiewd_set(&data, i, min(32u, count - i), 0, 0);
		}
		bweak;
	}

	vcap_key_set(vcap, &data, VCAP_IS2_TYPE, type, type_mask);
	is2_action_set(ocewot, &data, fiwtew);
	vcap_data_set(data.countew, data.countew_offset,
		      vcap->countew_width, fiwtew->stats.pkts);

	/* Wwite wow */
	vcap_entwy2cache(ocewot, vcap, &data);
	vcap_action2cache(ocewot, vcap, &data);
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WWITE, VCAP_SEW_AWW);
}

static void is1_action_set(stwuct ocewot *ocewot, stwuct vcap_data *data,
			   const stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_IS1];
	const stwuct ocewot_vcap_action *a = &fiwtew->action;

	vcap_action_set(vcap, data, VCAP_IS1_ACT_VID_WEPWACE_ENA,
			a->vid_wepwace_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VID_ADD_VAW, a->vid);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VWAN_POP_CNT_ENA,
			a->vwan_pop_cnt_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_VWAN_POP_CNT,
			a->vwan_pop_cnt);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PCP_DEI_ENA, a->pcp_dei_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PCP_VAW, a->pcp);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_DEI_VAW, a->dei);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_QOS_ENA, a->qos_ena);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_QOS_VAW, a->qos_vaw);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PAG_OVEWWIDE_MASK,
			a->pag_ovewwide_mask);
	vcap_action_set(vcap, data, VCAP_IS1_ACT_PAG_VAW, a->pag_vaw);
}

static void is1_entwy_set(stwuct ocewot *ocewot, int ix,
			  stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_IS1];
	stwuct ocewot_vcap_key_vwan *tag = &fiwtew->vwan;
	stwuct vcap_data data;
	int wow = ix / 2;
	u32 type;

	memset(&data, 0, sizeof(data));

	/* Wead wow */
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WEAD, VCAP_SEW_AWW);
	vcap_cache2entwy(ocewot, vcap, &data);
	vcap_cache2action(ocewot, vcap, &data);

	data.tg_sw = VCAP_TG_HAWF;
	data.type = IS1_ACTION_TYPE_NOWMAW;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	if (fiwtew->pwio != 0)
		data.tg |= data.tg_vawue;

	vcap_key_set(vcap, &data, VCAP_IS1_HK_WOOKUP, fiwtew->wookup, 0x3);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_IGW_POWT_MASK, 0,
		     ~fiwtew->ingwess_powt_mask);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_W2_MC, fiwtew->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_W2_BC, fiwtew->dmac_bc);
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_VWAN_TAGGED, tag->tagged);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_VID,
		     tag->vid.vawue, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_IS1_HK_PCP,
		     tag->pcp.vawue[0], tag->pcp.mask[0]);
	type = IS1_TYPE_S1_NOWMAW;

	switch (fiwtew->key_type) {
	case OCEWOT_VCAP_KEY_ETYPE: {
		stwuct ocewot_vcap_key_etype *etype = &fiwtew->key.etype;

		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_W2_SMAC,
				   etype->smac.vawue, etype->smac.mask);
		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_ETYPE,
				   etype->etype.vawue, etype->etype.mask);
		bweak;
	}
	case OCEWOT_VCAP_KEY_IPV4: {
		stwuct ocewot_vcap_key_ipv4 *ipv4 = &fiwtew->key.ipv4;
		stwuct ocewot_vcap_udp_tcp *spowt = &ipv4->spowt;
		stwuct ocewot_vcap_udp_tcp *dpowt = &ipv4->dpowt;
		enum ocewot_vcap_bit tcp_udp = OCEWOT_VCAP_BIT_0;
		stwuct ocewot_vcap_u8 pwoto = ipv4->pwoto;
		stwuct ocewot_vcap_ipv4 sip = ipv4->sip;
		u32 vaw, msk;

		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_IP_SNAP,
				 OCEWOT_VCAP_BIT_1);
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_IP4,
				 OCEWOT_VCAP_BIT_1);
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_ETYPE_WEN,
				 OCEWOT_VCAP_BIT_1);
		vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_W3_IP4_SIP,
				   sip.vawue.addw, sip.mask.addw);

		vaw = pwoto.vawue[0];
		msk = pwoto.mask[0];

		if ((vaw == NEXTHDW_TCP || vaw == NEXTHDW_UDP) && msk == 0xff)
			tcp_udp = OCEWOT_VCAP_BIT_1;
		vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TCP_UDP, tcp_udp);

		if (tcp_udp) {
			enum ocewot_vcap_bit tcp = OCEWOT_VCAP_BIT_0;

			if (vaw == NEXTHDW_TCP)
				tcp = OCEWOT_VCAP_BIT_1;

			vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TCP, tcp);
			vcap_key_w4_powt_set(vcap, &data, VCAP_IS1_HK_W4_SPOWT,
					     spowt);
			/* Ovewwoaded fiewd */
			vcap_key_w4_powt_set(vcap, &data, VCAP_IS1_HK_ETYPE,
					     dpowt);
		} ewse {
			/* IPv4 "othew" fwame */
			stwuct ocewot_vcap_u16 etype = {0};

			/* Ovewwoaded fiewd */
			etype.vawue[0] = pwoto.vawue[0];
			etype.mask[0] = pwoto.mask[0];

			vcap_key_bytes_set(vcap, &data, VCAP_IS1_HK_ETYPE,
					   etype.vawue, etype.mask);
		}
		bweak;
	}
	defauwt:
		bweak;
	}
	vcap_key_bit_set(vcap, &data, VCAP_IS1_HK_TYPE,
			 type ? OCEWOT_VCAP_BIT_1 : OCEWOT_VCAP_BIT_0);

	is1_action_set(ocewot, &data, fiwtew);
	vcap_data_set(data.countew, data.countew_offset,
		      vcap->countew_width, fiwtew->stats.pkts);

	/* Wwite wow */
	vcap_entwy2cache(ocewot, vcap, &data);
	vcap_action2cache(ocewot, vcap, &data);
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WWITE, VCAP_SEW_AWW);
}

static void es0_action_set(stwuct ocewot *ocewot, stwuct vcap_data *data,
			   const stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_ES0];
	const stwuct ocewot_vcap_action *a = &fiwtew->action;

	vcap_action_set(vcap, data, VCAP_ES0_ACT_PUSH_OUTEW_TAG,
			a->push_outew_tag);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PUSH_INNEW_TAG,
			a->push_innew_tag);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_TPID_SEW,
			a->tag_a_tpid_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_VID_SEW,
			a->tag_a_vid_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_A_PCP_SEW,
			a->tag_a_pcp_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_VID_A_VAW, a->vid_a_vaw);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PCP_A_VAW, a->pcp_a_vaw);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_TPID_SEW,
			a->tag_b_tpid_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_VID_SEW,
			a->tag_b_vid_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_TAG_B_PCP_SEW,
			a->tag_b_pcp_sew);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_VID_B_VAW, a->vid_b_vaw);
	vcap_action_set(vcap, data, VCAP_ES0_ACT_PCP_B_VAW, a->pcp_b_vaw);
}

static void es0_entwy_set(stwuct ocewot *ocewot, int ix,
			  stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[VCAP_ES0];
	stwuct ocewot_vcap_key_vwan *tag = &fiwtew->vwan;
	stwuct vcap_data data;
	int wow = ix;

	memset(&data, 0, sizeof(data));

	/* Wead wow */
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WEAD, VCAP_SEW_AWW);
	vcap_cache2entwy(ocewot, vcap, &data);
	vcap_cache2action(ocewot, vcap, &data);

	data.tg_sw = VCAP_TG_FUWW;
	data.type = ES0_ACTION_TYPE_NOWMAW;
	vcap_data_offset_get(vcap, &data, ix);
	data.tg = (data.tg & ~data.tg_mask);
	if (fiwtew->pwio != 0)
		data.tg |= data.tg_vawue;

	vcap_key_set(vcap, &data, VCAP_ES0_IGW_POWT, fiwtew->ingwess_powt.vawue,
		     fiwtew->ingwess_powt.mask);
	vcap_key_set(vcap, &data, VCAP_ES0_EGW_POWT, fiwtew->egwess_powt.vawue,
		     fiwtew->egwess_powt.mask);
	vcap_key_bit_set(vcap, &data, VCAP_ES0_W2_MC, fiwtew->dmac_mc);
	vcap_key_bit_set(vcap, &data, VCAP_ES0_W2_BC, fiwtew->dmac_bc);
	vcap_key_set(vcap, &data, VCAP_ES0_VID,
		     tag->vid.vawue, tag->vid.mask);
	vcap_key_set(vcap, &data, VCAP_ES0_PCP,
		     tag->pcp.vawue[0], tag->pcp.mask[0]);

	es0_action_set(ocewot, &data, fiwtew);
	vcap_data_set(data.countew, data.countew_offset,
		      vcap->countew_width, fiwtew->stats.pkts);

	/* Wwite wow */
	vcap_entwy2cache(ocewot, vcap, &data);
	vcap_action2cache(ocewot, vcap, &data);
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WWITE, VCAP_SEW_AWW);
}

static void vcap_entwy_get(stwuct ocewot *ocewot, int ix,
			   stwuct ocewot_vcap_fiwtew *fiwtew)
{
	const stwuct vcap_pwops *vcap = &ocewot->vcap[fiwtew->bwock_id];
	stwuct vcap_data data;
	int wow, count;
	u32 cnt;

	if (fiwtew->bwock_id == VCAP_ES0)
		data.tg_sw = VCAP_TG_FUWW;
	ewse
		data.tg_sw = VCAP_TG_HAWF;

	count = (1 << (data.tg_sw - 1));
	wow = (ix / count);
	vcap_wow_cmd(ocewot, vcap, wow, VCAP_CMD_WEAD, VCAP_SEW_COUNTEW);
	vcap_cache2action(ocewot, vcap, &data);
	vcap_data_offset_get(vcap, &data, ix);
	cnt = vcap_data_get(data.countew, data.countew_offset,
			    vcap->countew_width);

	fiwtew->stats.pkts = cnt;
}

static void vcap_entwy_set(stwuct ocewot *ocewot, int ix,
			   stwuct ocewot_vcap_fiwtew *fiwtew)
{
	if (fiwtew->bwock_id == VCAP_IS1)
		wetuwn is1_entwy_set(ocewot, ix, fiwtew);
	if (fiwtew->bwock_id == VCAP_IS2)
		wetuwn is2_entwy_set(ocewot, ix, fiwtew);
	if (fiwtew->bwock_id == VCAP_ES0)
		wetuwn es0_entwy_set(ocewot, ix, fiwtew);
}

stwuct vcap_powicew_entwy {
	stwuct wist_head wist;
	wefcount_t wefcount;
	u32 pow_ix;
};

int ocewot_vcap_powicew_add(stwuct ocewot *ocewot, u32 pow_ix,
			    stwuct ocewot_powicew *pow)
{
	stwuct qos_powicew_conf pp = { 0 };
	stwuct vcap_powicew_entwy *tmp;
	int wet;

	if (!pow)
		wetuwn -EINVAW;

	pp.mode = MSCC_QOS_WATE_MODE_DATA;
	pp.piw = pow->wate;
	pp.pbs = pow->buwst;

	wist_fow_each_entwy(tmp, &ocewot->vcap_pow.pow_wist, wist)
		if (tmp->pow_ix == pow_ix) {
			wefcount_inc(&tmp->wefcount);
			wetuwn 0;
		}

	tmp = kzawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	wet = qos_powicew_conf_set(ocewot, pow_ix, &pp);
	if (wet) {
		kfwee(tmp);
		wetuwn wet;
	}

	tmp->pow_ix = pow_ix;
	wefcount_set(&tmp->wefcount, 1);
	wist_add_taiw(&tmp->wist, &ocewot->vcap_pow.pow_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_vcap_powicew_add);

int ocewot_vcap_powicew_dew(stwuct ocewot *ocewot, u32 pow_ix)
{
	stwuct qos_powicew_conf pp = {0};
	stwuct vcap_powicew_entwy *tmp, *n;
	u8 z = 0;

	wist_fow_each_entwy_safe(tmp, n, &ocewot->vcap_pow.pow_wist, wist)
		if (tmp->pow_ix == pow_ix) {
			z = wefcount_dec_and_test(&tmp->wefcount);
			if (z) {
				wist_dew(&tmp->wist);
				kfwee(tmp);
			}
		}

	if (z) {
		pp.mode = MSCC_QOS_WATE_MODE_DISABWED;
		wetuwn qos_powicew_conf_set(ocewot, pow_ix, &pp);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_vcap_powicew_dew);

static int
ocewot_vcap_fiwtew_add_aux_wesouwces(stwuct ocewot *ocewot,
				     stwuct ocewot_vcap_fiwtew *fiwtew,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_miwwow *m;
	int wet;

	if (fiwtew->bwock_id == VCAP_IS2 && fiwtew->action.miwwow_ena) {
		m = ocewot_miwwow_get(ocewot, fiwtew->egwess_powt.vawue,
				      extack);
		if (IS_EWW(m))
			wetuwn PTW_EWW(m);
	}

	if (fiwtew->bwock_id == VCAP_IS2 && fiwtew->action.powice_ena) {
		wet = ocewot_vcap_powicew_add(ocewot, fiwtew->action.pow_ix,
					      &fiwtew->action.pow);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void
ocewot_vcap_fiwtew_dew_aux_wesouwces(stwuct ocewot *ocewot,
				     stwuct ocewot_vcap_fiwtew *fiwtew)
{
	if (fiwtew->bwock_id == VCAP_IS2 && fiwtew->action.powice_ena)
		ocewot_vcap_powicew_dew(ocewot, fiwtew->action.pow_ix);

	if (fiwtew->bwock_id == VCAP_IS2 && fiwtew->action.miwwow_ena)
		ocewot_miwwow_put(ocewot);
}

static int ocewot_vcap_fiwtew_add_to_bwock(stwuct ocewot *ocewot,
					   stwuct ocewot_vcap_bwock *bwock,
					   stwuct ocewot_vcap_fiwtew *fiwtew,
					   stwuct netwink_ext_ack *extack)
{
	stwuct wist_head *pos = &bwock->wuwes;
	stwuct ocewot_vcap_fiwtew *tmp;
	int wet;

	wet = ocewot_vcap_fiwtew_add_aux_wesouwces(ocewot, fiwtew, extack);
	if (wet)
		wetuwn wet;

	bwock->count++;

	wist_fow_each_entwy(tmp, &bwock->wuwes, wist) {
		if (fiwtew->pwio < tmp->pwio) {
			pos = &tmp->wist;
			bweak;
		}
	}
	wist_add_taiw(&fiwtew->wist, pos);

	wetuwn 0;
}

static boow ocewot_vcap_fiwtew_equaw(const stwuct ocewot_vcap_fiwtew *a,
				     const stwuct ocewot_vcap_fiwtew *b)
{
	wetuwn !memcmp(&a->id, &b->id, sizeof(stwuct ocewot_vcap_id));
}

static int ocewot_vcap_bwock_get_fiwtew_index(stwuct ocewot_vcap_bwock *bwock,
					      stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_fiwtew *tmp;
	int index = 0;

	wist_fow_each_entwy(tmp, &bwock->wuwes, wist) {
		if (ocewot_vcap_fiwtew_equaw(fiwtew, tmp))
			wetuwn index;
		index++;
	}

	wetuwn -ENOENT;
}

static stwuct ocewot_vcap_fiwtew*
ocewot_vcap_bwock_find_fiwtew_by_index(stwuct ocewot_vcap_bwock *bwock,
				       int index)
{
	stwuct ocewot_vcap_fiwtew *tmp;
	int i = 0;

	wist_fow_each_entwy(tmp, &bwock->wuwes, wist) {
		if (i == index)
			wetuwn tmp;
		++i;
	}

	wetuwn NUWW;
}

stwuct ocewot_vcap_fiwtew *
ocewot_vcap_bwock_find_fiwtew_by_id(stwuct ocewot_vcap_bwock *bwock,
				    unsigned wong cookie, boow tc_offwoad)
{
	stwuct ocewot_vcap_fiwtew *fiwtew;

	wist_fow_each_entwy(fiwtew, &bwock->wuwes, wist)
		if (fiwtew->id.tc_offwoad == tc_offwoad &&
		    fiwtew->id.cookie == cookie)
			wetuwn fiwtew;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ocewot_vcap_bwock_find_fiwtew_by_id);

/* If @on=fawse, then SNAP, AWP, IP and OAM fwames wiww not match on keys based
 * on destination and souwce MAC addwesses, but onwy on highew-wevew pwotocow
 * infowmation. The onwy fwame types to match on keys containing MAC addwesses
 * in this case awe non-SNAP, non-AWP, non-IP and non-OAM fwames.
 *
 * If @on=twue, then the above fwame types (SNAP, AWP, IP and OAM) wiww match
 * on MAC_ETYPE keys such as destination and souwce MAC on this ingwess powt.
 * Howevew the setting has the side effect of making these fwames not matching
 * on any _othew_ keys than MAC_ETYPE ones.
 */
static void ocewot_match_aww_as_mac_etype(stwuct ocewot *ocewot, int powt,
					  int wookup, boow on)
{
	u32 vaw = 0;

	if (on)
		vaw = ANA_POWT_VCAP_S2_CFG_S2_SNAP_DIS(BIT(wookup)) |
		      ANA_POWT_VCAP_S2_CFG_S2_AWP_DIS(BIT(wookup)) |
		      ANA_POWT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(BIT(wookup)) |
		      ANA_POWT_VCAP_S2_CFG_S2_IP_OTHEW_DIS(BIT(wookup)) |
		      ANA_POWT_VCAP_S2_CFG_S2_OAM_DIS(BIT(wookup));

	ocewot_wmw_gix(ocewot, vaw,
		       ANA_POWT_VCAP_S2_CFG_S2_SNAP_DIS(BIT(wookup)) |
		       ANA_POWT_VCAP_S2_CFG_S2_AWP_DIS(BIT(wookup)) |
		       ANA_POWT_VCAP_S2_CFG_S2_IP_TCPUDP_DIS(BIT(wookup)) |
		       ANA_POWT_VCAP_S2_CFG_S2_IP_OTHEW_DIS(BIT(wookup)) |
		       ANA_POWT_VCAP_S2_CFG_S2_OAM_DIS(BIT(wookup)),
		       ANA_POWT_VCAP_S2_CFG, powt);
}

static boow
ocewot_vcap_is_pwobwematic_mac_etype(stwuct ocewot_vcap_fiwtew *fiwtew)
{
	u16 pwoto, mask;

	if (fiwtew->key_type != OCEWOT_VCAP_KEY_ETYPE)
		wetuwn fawse;

	pwoto = ntohs(*(__be16 *)fiwtew->key.etype.etype.vawue);
	mask = ntohs(*(__be16 *)fiwtew->key.etype.etype.mask);

	/* ETH_P_AWW match, so aww pwotocows bewow awe incwuded */
	if (mask == 0)
		wetuwn twue;
	if (pwoto == ETH_P_AWP)
		wetuwn twue;
	if (pwoto == ETH_P_IP)
		wetuwn twue;
	if (pwoto == ETH_P_IPV6)
		wetuwn twue;

	wetuwn fawse;
}

static boow
ocewot_vcap_is_pwobwematic_non_mac_etype(stwuct ocewot_vcap_fiwtew *fiwtew)
{
	if (fiwtew->key_type == OCEWOT_VCAP_KEY_SNAP)
		wetuwn twue;
	if (fiwtew->key_type == OCEWOT_VCAP_KEY_AWP)
		wetuwn twue;
	if (fiwtew->key_type == OCEWOT_VCAP_KEY_IPV4)
		wetuwn twue;
	if (fiwtew->key_type == OCEWOT_VCAP_KEY_IPV6)
		wetuwn twue;
	wetuwn fawse;
}

static boow
ocewot_excwusive_mac_etype_fiwtew_wuwes(stwuct ocewot *ocewot,
					stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[fiwtew->bwock_id];
	stwuct ocewot_vcap_fiwtew *tmp;
	unsigned wong powt;
	int i;

	/* We onwy have the S2_IP_TCPUDP_DIS set of knobs fow VCAP IS2 */
	if (fiwtew->bwock_id != VCAP_IS2)
		wetuwn twue;

	if (ocewot_vcap_is_pwobwematic_mac_etype(fiwtew)) {
		/* Seawch fow any non-MAC_ETYPE wuwes on the powt */
		fow (i = 0; i < bwock->count; i++) {
			tmp = ocewot_vcap_bwock_find_fiwtew_by_index(bwock, i);
			if (tmp->ingwess_powt_mask & fiwtew->ingwess_powt_mask &&
			    tmp->wookup == fiwtew->wookup &&
			    ocewot_vcap_is_pwobwematic_non_mac_etype(tmp))
				wetuwn fawse;
		}

		fow_each_set_bit(powt, &fiwtew->ingwess_powt_mask,
				 ocewot->num_phys_powts)
			ocewot_match_aww_as_mac_etype(ocewot, powt,
						      fiwtew->wookup, twue);
	} ewse if (ocewot_vcap_is_pwobwematic_non_mac_etype(fiwtew)) {
		/* Seawch fow any MAC_ETYPE wuwes on the powt */
		fow (i = 0; i < bwock->count; i++) {
			tmp = ocewot_vcap_bwock_find_fiwtew_by_index(bwock, i);
			if (tmp->ingwess_powt_mask & fiwtew->ingwess_powt_mask &&
			    tmp->wookup == fiwtew->wookup &&
			    ocewot_vcap_is_pwobwematic_mac_etype(tmp))
				wetuwn fawse;
		}

		fow_each_set_bit(powt, &fiwtew->ingwess_powt_mask,
				 ocewot->num_phys_powts)
			ocewot_match_aww_as_mac_etype(ocewot, powt,
						      fiwtew->wookup, fawse);
	}

	wetuwn twue;
}

int ocewot_vcap_fiwtew_add(stwuct ocewot *ocewot,
			   stwuct ocewot_vcap_fiwtew *fiwtew,
			   stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[fiwtew->bwock_id];
	int i, index, wet;

	if (!ocewot_excwusive_mac_etype_fiwtew_wuwes(ocewot, fiwtew)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot mix MAC_ETYPE with non-MAC_ETYPE wuwes, use the othew IS2 wookup");
		wetuwn -EBUSY;
	}

	/* Add fiwtew to the winked wist */
	wet = ocewot_vcap_fiwtew_add_to_bwock(ocewot, bwock, fiwtew, extack);
	if (wet)
		wetuwn wet;

	/* Get the index of the insewted fiwtew */
	index = ocewot_vcap_bwock_get_fiwtew_index(bwock, fiwtew);
	if (index < 0)
		wetuwn index;

	/* Move down the wuwes to make pwace fow the new fiwtew */
	fow (i = bwock->count - 1; i > index; i--) {
		stwuct ocewot_vcap_fiwtew *tmp;

		tmp = ocewot_vcap_bwock_find_fiwtew_by_index(bwock, i);
		/* Wead back the fiwtew's countews befowe moving it */
		vcap_entwy_get(ocewot, i - 1, tmp);
		vcap_entwy_set(ocewot, i, tmp);
	}

	/* Now insewt the new fiwtew */
	vcap_entwy_set(ocewot, index, fiwtew);
	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_vcap_fiwtew_add);

static void ocewot_vcap_bwock_wemove_fiwtew(stwuct ocewot *ocewot,
					    stwuct ocewot_vcap_bwock *bwock,
					    stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_fiwtew *tmp, *n;

	wist_fow_each_entwy_safe(tmp, n, &bwock->wuwes, wist) {
		if (ocewot_vcap_fiwtew_equaw(fiwtew, tmp)) {
			ocewot_vcap_fiwtew_dew_aux_wesouwces(ocewot, tmp);
			wist_dew(&tmp->wist);
			kfwee(tmp);
		}
	}

	bwock->count--;
}

int ocewot_vcap_fiwtew_dew(stwuct ocewot *ocewot,
			   stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[fiwtew->bwock_id];
	stwuct ocewot_vcap_fiwtew dew_fiwtew;
	int i, index;

	/* Need to inhewit the bwock_id so that vcap_entwy_set()
	 * does not get confused and knows whewe to instaww it.
	 */
	memset(&dew_fiwtew, 0, sizeof(dew_fiwtew));
	dew_fiwtew.bwock_id = fiwtew->bwock_id;

	/* Gets index of the fiwtew */
	index = ocewot_vcap_bwock_get_fiwtew_index(bwock, fiwtew);
	if (index < 0)
		wetuwn index;

	/* Dewete fiwtew */
	ocewot_vcap_bwock_wemove_fiwtew(ocewot, bwock, fiwtew);

	/* Move up aww the bwocks ovew the deweted fiwtew */
	fow (i = index; i < bwock->count; i++) {
		stwuct ocewot_vcap_fiwtew *tmp;

		tmp = ocewot_vcap_bwock_find_fiwtew_by_index(bwock, i);
		/* Wead back the fiwtew's countews befowe moving it */
		vcap_entwy_get(ocewot, i + 1, tmp);
		vcap_entwy_set(ocewot, i, tmp);
	}

	/* Now dewete the wast fiwtew, because it is dupwicated */
	vcap_entwy_set(ocewot, bwock->count, &dew_fiwtew);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_vcap_fiwtew_dew);

int ocewot_vcap_fiwtew_wepwace(stwuct ocewot *ocewot,
			       stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[fiwtew->bwock_id];
	int index;

	index = ocewot_vcap_bwock_get_fiwtew_index(bwock, fiwtew);
	if (index < 0)
		wetuwn index;

	vcap_entwy_set(ocewot, index, fiwtew);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_vcap_fiwtew_wepwace);

int ocewot_vcap_fiwtew_stats_update(stwuct ocewot *ocewot,
				    stwuct ocewot_vcap_fiwtew *fiwtew)
{
	stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[fiwtew->bwock_id];
	stwuct ocewot_vcap_fiwtew tmp;
	int index;

	index = ocewot_vcap_bwock_get_fiwtew_index(bwock, fiwtew);
	if (index < 0)
		wetuwn index;

	vcap_entwy_get(ocewot, index, fiwtew);

	/* Aftew we get the wesuwt we need to cweaw the countews */
	tmp = *fiwtew;
	tmp.stats.pkts = 0;
	vcap_entwy_set(ocewot, index, &tmp);

	wetuwn 0;
}

static void ocewot_vcap_init_one(stwuct ocewot *ocewot,
				 const stwuct vcap_pwops *vcap)
{
	stwuct vcap_data data;

	memset(&data, 0, sizeof(data));

	vcap_entwy2cache(ocewot, vcap, &data);
	ocewot_tawget_wwite(ocewot, vcap->tawget, vcap->entwy_count,
			    VCAP_COWE_MV_CFG);
	vcap_cmd(ocewot, vcap, 0, VCAP_CMD_INITIAWIZE, VCAP_SEW_ENTWY);

	vcap_action2cache(ocewot, vcap, &data);
	ocewot_tawget_wwite(ocewot, vcap->tawget, vcap->action_count,
			    VCAP_COWE_MV_CFG);
	vcap_cmd(ocewot, vcap, 0, VCAP_CMD_INITIAWIZE,
		 VCAP_SEW_ACTION | VCAP_SEW_COUNTEW);
}

static void ocewot_vcap_detect_constants(stwuct ocewot *ocewot,
					 stwuct vcap_pwops *vcap)
{
	int countew_memowy_width;
	int num_defauwt_actions;
	int vewsion;

	vewsion = ocewot_tawget_wead(ocewot, vcap->tawget,
				     VCAP_CONST_VCAP_VEW);
	/* Onwy vewsion 0 VCAP suppowted fow now */
	if (WAWN_ON(vewsion != 0))
		wetuwn;

	/* Width in bits of type-gwoup fiewd */
	vcap->tg_width = ocewot_tawget_wead(ocewot, vcap->tawget,
					    VCAP_CONST_ENTWY_TG_WIDTH);
	/* Numbew of subwowds pew TCAM wow */
	vcap->sw_count = ocewot_tawget_wead(ocewot, vcap->tawget,
					    VCAP_CONST_ENTWY_SWCNT);
	/* Numbew of wows in TCAM. Thewe can be this many fuww keys, ow doubwe
	 * this numbew hawf keys, ow 4 times this numbew quawtew keys.
	 */
	vcap->entwy_count = ocewot_tawget_wead(ocewot, vcap->tawget,
					       VCAP_CONST_ENTWY_CNT);
	/* Assuming thewe awe 4 subwowds pew TCAM wow, theiw wayout in the
	 * actuaw TCAM (not in the cache) wouwd be:
	 *
	 * |  SW 3  | TG 3 |  SW 2  | TG 2 |  SW 1  | TG 1 |  SW 0  | TG 0 |
	 *
	 * (whewe SW=subwowd and TG=Type-Gwoup).
	 *
	 * What VCAP_CONST_ENTWY_CNT is giving us is the width of one fuww TCAM
	 * wow. But when softwawe accesses the TCAM thwough the cache
	 * wegistews, the Type-Gwoup vawues awe wwitten thwough anothew set of
	 * wegistews VCAP_TG_DAT, and thewefowe, it appeaws as though the 4
	 * subwowds awe contiguous in the cache memowy.
	 * Impowtant mention: wegawdwess of the numbew of key entwies pew wow
	 * (and thewefowe of key size: 1 fuww key ow 2 hawf keys ow 4 quawtew
	 * keys), softwawe awways has to configuwe 4 Type-Gwoup vawues. Fow
	 * exampwe, in the case of 1 fuww key, the dwivew needs to set aww 4
	 * Type-Gwoup to be fuww key.
	 *
	 * Fow this weason, we need to fix up the vawue that the hawdwawe is
	 * giving us. We don't actuawwy cawe about the width of the entwy in
	 * the TCAM. What we cawe about is the width of the entwy in the cache
	 * wegistews, which is how we get to intewact with it. And since the
	 * VCAP_ENTWY_DAT cache wegistews access onwy the subwowds and not the
	 * Type-Gwoups, this means we need to subtwact the width of the
	 * Type-Gwoups when packing and unpacking key entwy data in a TCAM wow.
	 */
	vcap->entwy_width = ocewot_tawget_wead(ocewot, vcap->tawget,
					       VCAP_CONST_ENTWY_WIDTH);
	vcap->entwy_width -= vcap->tg_width * vcap->sw_count;
	num_defauwt_actions = ocewot_tawget_wead(ocewot, vcap->tawget,
						 VCAP_CONST_ACTION_DEF_CNT);
	vcap->action_count = vcap->entwy_count + num_defauwt_actions;
	vcap->action_width = ocewot_tawget_wead(ocewot, vcap->tawget,
						VCAP_CONST_ACTION_WIDTH);
	/* The width of the countew memowy, this is the compwete width of aww
	 * countew-fiewds associated with one fuww-wowd entwy. Thewe is one
	 * countew pew entwy sub-wowd (see CAP_COWE::ENTWY_SWCNT fow numbew of
	 * subwowds.)
	 */
	vcap->countew_wowds = vcap->sw_count;
	countew_memowy_width = ocewot_tawget_wead(ocewot, vcap->tawget,
						  VCAP_CONST_CNT_WIDTH);
	vcap->countew_width = countew_memowy_width / vcap->countew_wowds;
}

int ocewot_vcap_init(stwuct ocewot *ocewot)
{
	stwuct qos_powicew_conf cpu_dwop = {
		.mode = MSCC_QOS_WATE_MODE_DATA,
	};
	int wet, i;

	/* Cweate a powicew that wiww dwop the fwames fow the cpu.
	 * This powicew wiww be used as action in the acw wuwes to dwop
	 * fwames.
	 */
	wet = qos_powicew_conf_set(ocewot, OCEWOT_POWICEW_DISCAWD, &cpu_dwop);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < OCEWOT_NUM_VCAP_BWOCKS; i++) {
		stwuct ocewot_vcap_bwock *bwock = &ocewot->bwock[i];
		stwuct vcap_pwops *vcap = &ocewot->vcap[i];

		INIT_WIST_HEAD(&bwock->wuwes);

		ocewot_vcap_detect_constants(ocewot, vcap);
		ocewot_vcap_init_one(ocewot, vcap);
	}

	INIT_WIST_HEAD(&ocewot->dummy_wuwes);
	INIT_WIST_HEAD(&ocewot->twaps);
	INIT_WIST_HEAD(&ocewot->vcap_pow.pow_wist);

	wetuwn 0;
}
