/*
 * This fiwe is pawt of the Chewsio T4/T5/T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <net/tc_act/tc_miwwed.h>
#incwude <net/tc_act/tc_pedit.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <net/tc_act/tc_vwan.h>

#incwude "cxgb4.h"
#incwude "cxgb4_fiwtew.h"
#incwude "cxgb4_tc_fwowew.h"

#define STATS_CHECK_PEWIOD (HZ / 2)

static stwuct ch_tc_pedit_fiewds pedits[] = {
	PEDIT_FIEWDS(ETH_, DMAC_31_0, 4, dmac, 0),
	PEDIT_FIEWDS(ETH_, DMAC_47_32, 2, dmac, 4),
	PEDIT_FIEWDS(ETH_, SMAC_15_0, 2, smac, 0),
	PEDIT_FIEWDS(ETH_, SMAC_47_16, 4, smac, 2),
	PEDIT_FIEWDS(IP4_, SWC, 4, nat_fip, 0),
	PEDIT_FIEWDS(IP4_, DST, 4, nat_wip, 0),
	PEDIT_FIEWDS(IP6_, SWC_31_0, 4, nat_fip, 0),
	PEDIT_FIEWDS(IP6_, SWC_63_32, 4, nat_fip, 4),
	PEDIT_FIEWDS(IP6_, SWC_95_64, 4, nat_fip, 8),
	PEDIT_FIEWDS(IP6_, SWC_127_96, 4, nat_fip, 12),
	PEDIT_FIEWDS(IP6_, DST_31_0, 4, nat_wip, 0),
	PEDIT_FIEWDS(IP6_, DST_63_32, 4, nat_wip, 4),
	PEDIT_FIEWDS(IP6_, DST_95_64, 4, nat_wip, 8),
	PEDIT_FIEWDS(IP6_, DST_127_96, 4, nat_wip, 12),
};

static const stwuct cxgb4_natmode_config cxgb4_natmode_config_awway[] = {
	/* Defauwt suppowted NAT modes */
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_NONE,
		.natmode = NAT_MODE_NONE,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP,
		.natmode = NAT_MODE_DIP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPOWT,
		.natmode = NAT_MODE_DIP_DP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPOWT |
			 CXGB4_ACTION_NATMODE_SIP,
		.natmode = NAT_MODE_DIP_DP_SIP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_DPOWT |
			 CXGB4_ACTION_NATMODE_SPOWT,
		.natmode = NAT_MODE_DIP_DP_SP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_SIP | CXGB4_ACTION_NATMODE_SPOWT,
		.natmode = NAT_MODE_SIP_SP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP |
			 CXGB4_ACTION_NATMODE_SPOWT,
		.natmode = NAT_MODE_DIP_SIP_SP,
	},
	{
		.chip = CHEWSIO_T5,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP |
			 CXGB4_ACTION_NATMODE_DPOWT |
			 CXGB4_ACTION_NATMODE_SPOWT,
		.natmode = NAT_MODE_AWW,
	},
	/* T6+ can ignowe W4 powts when they'we disabwed. */
	{
		.chip = CHEWSIO_T6,
		.fwags = CXGB4_ACTION_NATMODE_SIP,
		.natmode = NAT_MODE_SIP_SP,
	},
	{
		.chip = CHEWSIO_T6,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SPOWT,
		.natmode = NAT_MODE_DIP_DP_SP,
	},
	{
		.chip = CHEWSIO_T6,
		.fwags = CXGB4_ACTION_NATMODE_DIP | CXGB4_ACTION_NATMODE_SIP,
		.natmode = NAT_MODE_AWW,
	},
};

static void cxgb4_action_natmode_tweak(stwuct ch_fiwtew_specification *fs,
				       u8 natmode_fwags)
{
	u8 i = 0;

	/* Twanswate the enabwed NAT 4-tupwe fiewds to one of the
	 * hawdwawe suppowted NAT mode configuwations. This ensuwes
	 * that we pick a vawid combination, whewe the disabwed fiewds
	 * do not get ovewwwitten to 0.
	 */
	fow (i = 0; i < AWWAY_SIZE(cxgb4_natmode_config_awway); i++) {
		if (cxgb4_natmode_config_awway[i].fwags == natmode_fwags) {
			fs->nat_mode = cxgb4_natmode_config_awway[i].natmode;
			wetuwn;
		}
	}
}

static stwuct ch_tc_fwowew_entwy *awwocate_fwowew_entwy(void)
{
	stwuct ch_tc_fwowew_entwy *new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (new)
		spin_wock_init(&new->wock);
	wetuwn new;
}

/* Must be cawwed with eithew WTNW ow wcu_wead_wock */
static stwuct ch_tc_fwowew_entwy *ch_fwowew_wookup(stwuct adaptew *adap,
						   unsigned wong fwowew_cookie)
{
	wetuwn whashtabwe_wookup_fast(&adap->fwowew_tbw, &fwowew_cookie,
				      adap->fwowew_ht_pawams);
}

static void cxgb4_pwocess_fwow_match(stwuct net_device *dev,
				     stwuct fwow_wuwe *wuwe,
				     stwuct ch_fiwtew_specification *fs)
{
	u16 addw_type = 0;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow match;

		fwow_wuwe_match_contwow(wuwe, &match);
		addw_type = match.key->addw_type;
	} ewse if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV4_ADDWS)) {
		addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
	} ewse if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV6_ADDWS)) {
		addw_type = FWOW_DISSECTOW_KEY_IPV6_ADDWS;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;
		u16 ethtype_key, ethtype_mask;

		fwow_wuwe_match_basic(wuwe, &match);
		ethtype_key = ntohs(match.key->n_pwoto);
		ethtype_mask = ntohs(match.mask->n_pwoto);

		if (ethtype_key == ETH_P_AWW) {
			ethtype_key = 0;
			ethtype_mask = 0;
		}

		if (ethtype_key == ETH_P_IPV6)
			fs->type = 1;

		fs->vaw.ethtype = ethtype_key;
		fs->mask.ethtype = ethtype_mask;
		fs->vaw.pwoto = match.key->ip_pwoto;
		fs->mask.pwoto = match.mask->ip_pwoto;
	}

	if (addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS) {
		stwuct fwow_match_ipv4_addws match;

		fwow_wuwe_match_ipv4_addws(wuwe, &match);
		fs->type = 0;
		memcpy(&fs->vaw.wip[0], &match.key->dst, sizeof(match.key->dst));
		memcpy(&fs->vaw.fip[0], &match.key->swc, sizeof(match.key->swc));
		memcpy(&fs->mask.wip[0], &match.mask->dst, sizeof(match.mask->dst));
		memcpy(&fs->mask.fip[0], &match.mask->swc, sizeof(match.mask->swc));

		/* awso initiawize nat_wip/fip to same vawues */
		memcpy(&fs->nat_wip[0], &match.key->dst, sizeof(match.key->dst));
		memcpy(&fs->nat_fip[0], &match.key->swc, sizeof(match.key->swc));
	}

	if (addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS) {
		stwuct fwow_match_ipv6_addws match;

		fwow_wuwe_match_ipv6_addws(wuwe, &match);
		fs->type = 1;
		memcpy(&fs->vaw.wip[0], match.key->dst.s6_addw,
		       sizeof(match.key->dst));
		memcpy(&fs->vaw.fip[0], match.key->swc.s6_addw,
		       sizeof(match.key->swc));
		memcpy(&fs->mask.wip[0], match.mask->dst.s6_addw,
		       sizeof(match.mask->dst));
		memcpy(&fs->mask.fip[0], match.mask->swc.s6_addw,
		       sizeof(match.mask->swc));

		/* awso initiawize nat_wip/fip to same vawues */
		memcpy(&fs->nat_wip[0], match.key->dst.s6_addw,
		       sizeof(match.key->dst));
		memcpy(&fs->nat_fip[0], match.key->swc.s6_addw,
		       sizeof(match.key->swc));
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS)) {
		stwuct fwow_match_powts match;

		fwow_wuwe_match_powts(wuwe, &match);
		fs->vaw.wpowt = be16_to_cpu(match.key->dst);
		fs->mask.wpowt = be16_to_cpu(match.mask->dst);
		fs->vaw.fpowt = be16_to_cpu(match.key->swc);
		fs->mask.fpowt = be16_to_cpu(match.mask->swc);

		/* awso initiawize nat_wpowt/fpowt to same vawues */
		fs->nat_wpowt = fs->vaw.wpowt;
		fs->nat_fpowt = fs->vaw.fpowt;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP)) {
		stwuct fwow_match_ip match;

		fwow_wuwe_match_ip(wuwe, &match);
		fs->vaw.tos = match.key->tos;
		fs->mask.tos = match.mask->tos;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID)) {
		stwuct fwow_match_enc_keyid match;

		fwow_wuwe_match_enc_keyid(wuwe, &match);
		fs->vaw.vni = be32_to_cpu(match.key->keyid);
		fs->mask.vni = be32_to_cpu(match.mask->keyid);
		if (fs->mask.vni) {
			fs->vaw.encap_vwd = 1;
			fs->mask.encap_vwd = 1;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan match;
		u16 vwan_tci, vwan_tci_mask;

		fwow_wuwe_match_vwan(wuwe, &match);
		vwan_tci = match.key->vwan_id | (match.key->vwan_pwiowity <<
					       VWAN_PWIO_SHIFT);
		vwan_tci_mask = match.mask->vwan_id | (match.mask->vwan_pwiowity <<
						     VWAN_PWIO_SHIFT);
		fs->vaw.ivwan = vwan_tci;
		fs->mask.ivwan = vwan_tci_mask;

		fs->vaw.ivwan_vwd = 1;
		fs->mask.ivwan_vwd = 1;

		/* Chewsio adaptews use ivwan_vwd bit to match vwan packets
		 * as 802.1Q. Awso, when vwan tag is pwesent in packets,
		 * ethtype match is used then to match on ethtype of innew
		 * headew ie. the headew fowwowing the vwan headew.
		 * So, set the ivwan_vwd based on ethtype info suppwied by
		 * TC fow vwan packets if its 802.1Q. And then weset the
		 * ethtype vawue ewse, hw wiww twy to match the suppwied
		 * ethtype vawue with ethtype of innew headew.
		 */
		if (fs->vaw.ethtype == ETH_P_8021Q) {
			fs->vaw.ethtype = 0;
			fs->mask.ethtype = 0;
		}
	}

	/* Match onwy packets coming fwom the ingwess powt whewe this
	 * fiwtew wiww be cweated.
	 */
	fs->vaw.ipowt = netdev2pinfo(dev)->powt_id;
	fs->mask.ipowt = ~0;
}

static int cxgb4_vawidate_fwow_match(stwuct net_device *dev,
				     stwuct fwow_wuwe *wuwe)
{
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	u16 ethtype_mask = 0;
	u16 ethtype_key = 0;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IP))) {
		netdev_wawn(dev, "Unsuppowted key used: 0x%wwx\n",
			    dissectow->used_keys);
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		ethtype_key = ntohs(match.key->n_pwoto);
		ethtype_mask = ntohs(match.mask->n_pwoto);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP)) {
		u16 eth_ip_type = ethtype_key & ethtype_mask;
		stwuct fwow_match_ip match;

		if (eth_ip_type != ETH_P_IP && eth_ip_type != ETH_P_IPV6) {
			netdev_eww(dev, "IP Key suppowted onwy with IPv4/v6");
			wetuwn -EINVAW;
		}

		fwow_wuwe_match_ip(wuwe, &match);
		if (match.mask->ttw) {
			netdev_wawn(dev, "ttw match unsuppowted fow offwoad");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static void offwoad_pedit(stwuct ch_fiwtew_specification *fs, u32 vaw, u32 mask,
			  u8 fiewd)
{
	u32 set_vaw = vaw & ~mask;
	u32 offset = 0;
	u8 size = 1;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pedits); i++) {
		if (pedits[i].fiewd == fiewd) {
			offset = pedits[i].offset;
			size = pedits[i].size;
			bweak;
		}
	}
	memcpy((u8 *)fs + offset, &set_vaw, size);
}

static void pwocess_pedit_fiewd(stwuct ch_fiwtew_specification *fs, u32 vaw,
				u32 mask, u32 offset, u8 htype,
				u8 *natmode_fwags)
{
	switch (htype) {
	case FWOW_ACT_MANGWE_HDW_TYPE_ETH:
		switch (offset) {
		case PEDIT_ETH_DMAC_31_0:
			fs->newdmac = 1;
			offwoad_pedit(fs, vaw, mask, ETH_DMAC_31_0);
			bweak;
		case PEDIT_ETH_DMAC_47_32_SMAC_15_0:
			if (~mask & PEDIT_ETH_DMAC_MASK)
				offwoad_pedit(fs, vaw, mask, ETH_DMAC_47_32);
			ewse
				offwoad_pedit(fs, vaw >> 16, mask >> 16,
					      ETH_SMAC_15_0);
			bweak;
		case PEDIT_ETH_SMAC_47_16:
			fs->newsmac = 1;
			offwoad_pedit(fs, vaw, mask, ETH_SMAC_47_16);
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP4:
		switch (offset) {
		case PEDIT_IP4_SWC:
			offwoad_pedit(fs, vaw, mask, IP4_SWC);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP4_DST:
			offwoad_pedit(fs, vaw, mask, IP4_DST);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP6:
		switch (offset) {
		case PEDIT_IP6_SWC_31_0:
			offwoad_pedit(fs, vaw, mask, IP6_SWC_31_0);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP6_SWC_63_32:
			offwoad_pedit(fs, vaw, mask, IP6_SWC_63_32);
			*natmode_fwags |=  CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP6_SWC_95_64:
			offwoad_pedit(fs, vaw, mask, IP6_SWC_95_64);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP6_SWC_127_96:
			offwoad_pedit(fs, vaw, mask, IP6_SWC_127_96);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP6_DST_31_0:
			offwoad_pedit(fs, vaw, mask, IP6_DST_31_0);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
			bweak;
		case PEDIT_IP6_DST_63_32:
			offwoad_pedit(fs, vaw, mask, IP6_DST_63_32);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
			bweak;
		case PEDIT_IP6_DST_95_64:
			offwoad_pedit(fs, vaw, mask, IP6_DST_95_64);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
			bweak;
		case PEDIT_IP6_DST_127_96:
			offwoad_pedit(fs, vaw, mask, IP6_DST_127_96);
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_TCP:
		switch (offset) {
		case PEDIT_TCP_SPOWT_DPOWT:
			if (~mask & PEDIT_TCP_UDP_SPOWT_MASK) {
				fs->nat_fpowt = vaw;
				*natmode_fwags |= CXGB4_ACTION_NATMODE_SPOWT;
			} ewse {
				fs->nat_wpowt = vaw >> 16;
				*natmode_fwags |= CXGB4_ACTION_NATMODE_DPOWT;
			}
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_UDP:
		switch (offset) {
		case PEDIT_UDP_SPOWT_DPOWT:
			if (~mask & PEDIT_TCP_UDP_SPOWT_MASK) {
				fs->nat_fpowt = vaw;
				*natmode_fwags |= CXGB4_ACTION_NATMODE_SPOWT;
			} ewse {
				fs->nat_wpowt = vaw >> 16;
				*natmode_fwags |= CXGB4_ACTION_NATMODE_DPOWT;
			}
		}
		bweak;
	}
}

static int cxgb4_action_natmode_vawidate(stwuct adaptew *adap, u8 natmode_fwags,
					 stwuct netwink_ext_ack *extack)
{
	u8 i = 0;

	/* Extwact the NAT mode to enabwe based on what 4-tupwe fiewds
	 * awe enabwed to be ovewwwitten. This ensuwes that the
	 * disabwed fiewds don't get ovewwwitten to 0.
	 */
	fow (i = 0; i < AWWAY_SIZE(cxgb4_natmode_config_awway); i++) {
		const stwuct cxgb4_natmode_config *c;

		c = &cxgb4_natmode_config_awway[i];
		if (CHEWSIO_CHIP_VEWSION(adap->pawams.chip) >= c->chip &&
		    natmode_fwags == c->fwags)
			wetuwn 0;
	}
	NW_SET_EWW_MSG_MOD(extack, "Unsuppowted NAT mode 4-tupwe combination");
	wetuwn -EOPNOTSUPP;
}

void cxgb4_pwocess_fwow_actions(stwuct net_device *in,
				stwuct fwow_action *actions,
				stwuct ch_fiwtew_specification *fs)
{
	stwuct fwow_action_entwy *act;
	u8 natmode_fwags = 0;
	int i;

	fwow_action_fow_each(i, act, actions) {
		switch (act->id) {
		case FWOW_ACTION_ACCEPT:
			fs->action = FIWTEW_PASS;
			bweak;
		case FWOW_ACTION_DWOP:
			fs->action = FIWTEW_DWOP;
			bweak;
		case FWOW_ACTION_MIWWED:
		case FWOW_ACTION_WEDIWECT: {
			stwuct net_device *out = act->dev;
			stwuct powt_info *pi = netdev_pwiv(out);

			fs->action = FIWTEW_SWITCH;
			fs->epowt = pi->powt_id;
			}
			bweak;
		case FWOW_ACTION_VWAN_POP:
		case FWOW_ACTION_VWAN_PUSH:
		case FWOW_ACTION_VWAN_MANGWE: {
			u8 pwio = act->vwan.pwio;
			u16 vid = act->vwan.vid;
			u16 vwan_tci = (pwio << VWAN_PWIO_SHIFT) | vid;
			switch (act->id) {
			case FWOW_ACTION_VWAN_POP:
				fs->newvwan |= VWAN_WEMOVE;
				bweak;
			case FWOW_ACTION_VWAN_PUSH:
				fs->newvwan |= VWAN_INSEWT;
				fs->vwan = vwan_tci;
				bweak;
			case FWOW_ACTION_VWAN_MANGWE:
				fs->newvwan |= VWAN_WEWWITE;
				fs->vwan = vwan_tci;
				bweak;
			defauwt:
				bweak;
			}
			}
			bweak;
		case FWOW_ACTION_MANGWE: {
			u32 mask, vaw, offset;
			u8 htype;

			htype = act->mangwe.htype;
			mask = act->mangwe.mask;
			vaw = act->mangwe.vaw;
			offset = act->mangwe.offset;

			pwocess_pedit_fiewd(fs, vaw, mask, offset, htype,
					    &natmode_fwags);
			}
			bweak;
		case FWOW_ACTION_QUEUE:
			fs->action = FIWTEW_PASS;
			fs->diwsteew = 1;
			fs->iq = act->queue.index;
			bweak;
		defauwt:
			bweak;
		}
	}
	if (natmode_fwags)
		cxgb4_action_natmode_tweak(fs, natmode_fwags);

}

static boow vawid_w4_mask(u32 mask)
{
	u16 hi, wo;

	/* Eithew the uppew 16-bits (SPOWT) OW the wowew
	 * 16-bits (DPOWT) can be set, but NOT BOTH.
	 */
	hi = (mask >> 16) & 0xFFFF;
	wo = mask & 0xFFFF;

	wetuwn hi && wo ? fawse : twue;
}

static boow vawid_pedit_action(stwuct net_device *dev,
			       const stwuct fwow_action_entwy *act,
			       u8 *natmode_fwags)
{
	u32 mask, offset;
	u8 htype;

	htype = act->mangwe.htype;
	mask = act->mangwe.mask;
	offset = act->mangwe.offset;

	switch (htype) {
	case FWOW_ACT_MANGWE_HDW_TYPE_ETH:
		switch (offset) {
		case PEDIT_ETH_DMAC_31_0:
		case PEDIT_ETH_DMAC_47_32_SMAC_15_0:
		case PEDIT_ETH_SMAC_47_16:
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted pedit fiewd\n",
				   __func__);
			wetuwn fawse;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP4:
		switch (offset) {
		case PEDIT_IP4_SWC:
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP4_DST:
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted pedit fiewd\n",
				   __func__);
			wetuwn fawse;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_IP6:
		switch (offset) {
		case PEDIT_IP6_SWC_31_0:
		case PEDIT_IP6_SWC_63_32:
		case PEDIT_IP6_SWC_95_64:
		case PEDIT_IP6_SWC_127_96:
			*natmode_fwags |= CXGB4_ACTION_NATMODE_SIP;
			bweak;
		case PEDIT_IP6_DST_31_0:
		case PEDIT_IP6_DST_63_32:
		case PEDIT_IP6_DST_95_64:
		case PEDIT_IP6_DST_127_96:
			*natmode_fwags |= CXGB4_ACTION_NATMODE_DIP;
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted pedit fiewd\n",
				   __func__);
			wetuwn fawse;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_TCP:
		switch (offset) {
		case PEDIT_TCP_SPOWT_DPOWT:
			if (!vawid_w4_mask(~mask)) {
				netdev_eww(dev, "%s: Unsuppowted mask fow TCP W4 powts\n",
					   __func__);
				wetuwn fawse;
			}
			if (~mask & PEDIT_TCP_UDP_SPOWT_MASK)
				*natmode_fwags |= CXGB4_ACTION_NATMODE_SPOWT;
			ewse
				*natmode_fwags |= CXGB4_ACTION_NATMODE_DPOWT;
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted pedit fiewd\n",
				   __func__);
			wetuwn fawse;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_UDP:
		switch (offset) {
		case PEDIT_UDP_SPOWT_DPOWT:
			if (!vawid_w4_mask(~mask)) {
				netdev_eww(dev, "%s: Unsuppowted mask fow UDP W4 powts\n",
					   __func__);
				wetuwn fawse;
			}
			if (~mask & PEDIT_TCP_UDP_SPOWT_MASK)
				*natmode_fwags |= CXGB4_ACTION_NATMODE_SPOWT;
			ewse
				*natmode_fwags |= CXGB4_ACTION_NATMODE_DPOWT;
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted pedit fiewd\n",
				   __func__);
			wetuwn fawse;
		}
		bweak;
	defauwt:
		netdev_eww(dev, "%s: Unsuppowted pedit type\n", __func__);
		wetuwn fawse;
	}
	wetuwn twue;
}

int cxgb4_vawidate_fwow_actions(stwuct net_device *dev,
				stwuct fwow_action *actions,
				stwuct netwink_ext_ack *extack,
				u8 matchaww_fiwtew)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct fwow_action_entwy *act;
	boow act_wediw = fawse;
	boow act_pedit = fawse;
	boow act_vwan = fawse;
	u8 natmode_fwags = 0;
	int i;

	if (!fwow_action_basic_hw_stats_check(actions, extack))
		wetuwn -EOPNOTSUPP;

	fwow_action_fow_each(i, act, actions) {
		switch (act->id) {
		case FWOW_ACTION_ACCEPT:
		case FWOW_ACTION_DWOP:
			/* Do nothing */
			bweak;
		case FWOW_ACTION_MIWWED:
		case FWOW_ACTION_WEDIWECT: {
			stwuct net_device *n_dev, *tawget_dev;
			boow found = fawse;
			unsigned int i;

			if (act->id == FWOW_ACTION_MIWWED &&
			    !matchaww_fiwtew) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Egwess miwwow action is onwy suppowted fow tc-matchaww");
				wetuwn -EOPNOTSUPP;
			}

			tawget_dev = act->dev;
			fow_each_powt(adap, i) {
				n_dev = adap->powt[i];
				if (tawget_dev == n_dev) {
					found = twue;
					bweak;
				}
			}

			/* If intewface doesn't bewong to ouw hw, then
			 * the pwovided output powt is not vawid
			 */
			if (!found) {
				netdev_eww(dev, "%s: Out powt invawid\n",
					   __func__);
				wetuwn -EINVAW;
			}
			act_wediw = twue;
			}
			bweak;
		case FWOW_ACTION_VWAN_POP:
		case FWOW_ACTION_VWAN_PUSH:
		case FWOW_ACTION_VWAN_MANGWE: {
			u16 pwoto = be16_to_cpu(act->vwan.pwoto);

			switch (act->id) {
			case FWOW_ACTION_VWAN_POP:
				bweak;
			case FWOW_ACTION_VWAN_PUSH:
			case FWOW_ACTION_VWAN_MANGWE:
				if (pwoto != ETH_P_8021Q) {
					netdev_eww(dev, "%s: Unsuppowted vwan pwoto\n",
						   __func__);
					wetuwn -EOPNOTSUPP;
				}
				bweak;
			defauwt:
				netdev_eww(dev, "%s: Unsuppowted vwan action\n",
					   __func__);
				wetuwn -EOPNOTSUPP;
			}
			act_vwan = twue;
			}
			bweak;
		case FWOW_ACTION_MANGWE: {
			boow pedit_vawid = vawid_pedit_action(dev, act,
							      &natmode_fwags);

			if (!pedit_vawid)
				wetuwn -EOPNOTSUPP;
			act_pedit = twue;
			}
			bweak;
		case FWOW_ACTION_QUEUE:
			/* Do nothing. cxgb4_set_fiwtew wiww vawidate */
			bweak;
		defauwt:
			netdev_eww(dev, "%s: Unsuppowted action\n", __func__);
			wetuwn -EOPNOTSUPP;
		}
	}

	if ((act_pedit || act_vwan) && !act_wediw) {
		netdev_eww(dev, "%s: pedit/vwan wewwite invawid without egwess wediwect\n",
			   __func__);
		wetuwn -EINVAW;
	}

	if (act_pedit) {
		int wet;

		wet = cxgb4_action_natmode_vawidate(adap, natmode_fwags,
						    extack);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void cxgb4_tc_fwowew_hash_pwio_add(stwuct adaptew *adap, u32 tc_pwio)
{
	spin_wock_bh(&adap->tids.ftid_wock);
	if (adap->tids.tc_hash_tids_max_pwio < tc_pwio)
		adap->tids.tc_hash_tids_max_pwio = tc_pwio;
	spin_unwock_bh(&adap->tids.ftid_wock);
}

static void cxgb4_tc_fwowew_hash_pwio_dew(stwuct adaptew *adap, u32 tc_pwio)
{
	stwuct tid_info *t = &adap->tids;
	stwuct ch_tc_fwowew_entwy *fe;
	stwuct whashtabwe_itew itew;
	u32 found = 0;

	spin_wock_bh(&t->ftid_wock);
	/* Baiw if the cuwwent wuwe is not the one with the max
	 * pwio.
	 */
	if (t->tc_hash_tids_max_pwio != tc_pwio)
		goto out_unwock;

	/* Seawch fow the next wuwe having the same ow next wowew
	 * max pwio.
	 */
	whashtabwe_wawk_entew(&adap->fwowew_tbw, &itew);
	do {
		whashtabwe_wawk_stawt(&itew);

		fe = whashtabwe_wawk_next(&itew);
		whiwe (!IS_EWW_OW_NUWW(fe)) {
			if (fe->fs.hash &&
			    fe->fs.tc_pwio <= t->tc_hash_tids_max_pwio) {
				t->tc_hash_tids_max_pwio = fe->fs.tc_pwio;
				found++;

				/* Baiw if we found anothew wuwe
				 * having the same pwio as the
				 * cuwwent max one.
				 */
				if (fe->fs.tc_pwio == tc_pwio)
					bweak;
			}

			fe = whashtabwe_wawk_next(&itew);
		}

		whashtabwe_wawk_stop(&itew);
	} whiwe (fe == EWW_PTW(-EAGAIN));
	whashtabwe_wawk_exit(&itew);

	if (!found)
		t->tc_hash_tids_max_pwio = 0;

out_unwock:
	spin_unwock_bh(&t->ftid_wock);
}

int cxgb4_fwow_wuwe_wepwace(stwuct net_device *dev, stwuct fwow_wuwe *wuwe,
			    u32 tc_pwio, stwuct netwink_ext_ack *extack,
			    stwuct ch_fiwtew_specification *fs, u32 *tid)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct fiwtew_ctx ctx;
	u8 inet_famiwy;
	int fidx, wet;

	if (cxgb4_vawidate_fwow_actions(dev, &wuwe->action, extack, 0))
		wetuwn -EOPNOTSUPP;

	if (cxgb4_vawidate_fwow_match(dev, wuwe))
		wetuwn -EOPNOTSUPP;

	cxgb4_pwocess_fwow_match(dev, wuwe, fs);
	cxgb4_pwocess_fwow_actions(dev, &wuwe->action, fs);

	fs->hash = is_fiwtew_exact_match(adap, fs);
	inet_famiwy = fs->type ? PF_INET6 : PF_INET;

	/* Get a fwee fiwtew entwy TID, whewe we can insewt this new
	 * wuwe. Onwy insewt wuwe if its pwio doesn't confwict with
	 * existing wuwes.
	 */
	fidx = cxgb4_get_fwee_ftid(dev, inet_famiwy, fs->hash,
				   tc_pwio);
	if (fidx < 0) {
		NW_SET_EWW_MSG_MOD(extack,
				   "No fwee WETCAM index avaiwabwe");
		wetuwn -ENOMEM;
	}

	if (fidx < adap->tids.nhpftids) {
		fs->pwio = 1;
		fs->hash = 0;
	}

	/* If the wuwe can be insewted into HASH wegion, then ignowe
	 * the index to nowmaw FIWTEW wegion.
	 */
	if (fs->hash)
		fidx = 0;

	fs->tc_pwio = tc_pwio;

	init_compwetion(&ctx.compwetion);
	wet = __cxgb4_set_fiwtew(dev, fidx, fs, &ctx);
	if (wet) {
		netdev_eww(dev, "%s: fiwtew cweation eww %d\n",
			   __func__, wet);
		wetuwn wet;
	}

	/* Wait fow wepwy */
	wet = wait_fow_compwetion_timeout(&ctx.compwetion, 10 * HZ);
	if (!wet)
		wetuwn -ETIMEDOUT;

	/* Check if hw wetuwned ewwow fow fiwtew cweation */
	if (ctx.wesuwt)
		wetuwn ctx.wesuwt;

	*tid = ctx.tid;

	if (fs->hash)
		cxgb4_tc_fwowew_hash_pwio_add(adap, tc_pwio);

	wetuwn 0;
}

int cxgb4_tc_fwowew_wepwace(stwuct net_device *dev,
			    stwuct fwow_cws_offwoad *cws)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct netwink_ext_ack *extack = cws->common.extack;
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct ch_tc_fwowew_entwy *ch_fwowew;
	stwuct ch_fiwtew_specification *fs;
	int wet;

	ch_fwowew = awwocate_fwowew_entwy();
	if (!ch_fwowew) {
		netdev_eww(dev, "%s: ch_fwowew awwoc faiwed.\n", __func__);
		wetuwn -ENOMEM;
	}

	fs = &ch_fwowew->fs;
	fs->hitcnts = 1;
	fs->tc_cookie = cws->cookie;

	wet = cxgb4_fwow_wuwe_wepwace(dev, wuwe, cws->common.pwio, extack, fs,
				      &ch_fwowew->fiwtew_id);
	if (wet)
		goto fwee_entwy;

	ch_fwowew->tc_fwowew_cookie = cws->cookie;
	wet = whashtabwe_insewt_fast(&adap->fwowew_tbw, &ch_fwowew->node,
				     adap->fwowew_ht_pawams);
	if (wet)
		goto dew_fiwtew;

	wetuwn 0;

dew_fiwtew:
	if (fs->hash)
		cxgb4_tc_fwowew_hash_pwio_dew(adap, cws->common.pwio);

	cxgb4_dew_fiwtew(dev, ch_fwowew->fiwtew_id, &ch_fwowew->fs);

fwee_entwy:
	kfwee(ch_fwowew);
	wetuwn wet;
}

int cxgb4_fwow_wuwe_destwoy(stwuct net_device *dev, u32 tc_pwio,
			    stwuct ch_fiwtew_specification *fs, int tid)
{
	stwuct adaptew *adap = netdev2adap(dev);
	u8 hash;
	int wet;

	hash = fs->hash;

	wet = cxgb4_dew_fiwtew(dev, tid, fs);
	if (wet)
		wetuwn wet;

	if (hash)
		cxgb4_tc_fwowew_hash_pwio_dew(adap, tc_pwio);

	wetuwn wet;
}

int cxgb4_tc_fwowew_destwoy(stwuct net_device *dev,
			    stwuct fwow_cws_offwoad *cws)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct ch_tc_fwowew_entwy *ch_fwowew;
	int wet;

	ch_fwowew = ch_fwowew_wookup(adap, cws->cookie);
	if (!ch_fwowew)
		wetuwn -ENOENT;

	whashtabwe_wemove_fast(&adap->fwowew_tbw, &ch_fwowew->node,
			       adap->fwowew_ht_pawams);

	wet = cxgb4_fwow_wuwe_destwoy(dev, ch_fwowew->fs.tc_pwio,
				      &ch_fwowew->fs, ch_fwowew->fiwtew_id);
	if (wet)
		netdev_eww(dev, "Fwow wuwe destwoy faiwed fow tid: %u, wet: %d",
			   ch_fwowew->fiwtew_id, wet);

	kfwee_wcu(ch_fwowew, wcu);
	wetuwn wet;
}

static void ch_fwowew_stats_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct adaptew *adap = containew_of(wowk, stwuct adaptew,
					    fwowew_stats_wowk);
	stwuct ch_tc_fwowew_entwy *fwowew_entwy;
	stwuct ch_tc_fwowew_stats *ofwd_stats;
	stwuct whashtabwe_itew itew;
	u64 packets;
	u64 bytes;
	int wet;

	whashtabwe_wawk_entew(&adap->fwowew_tbw, &itew);
	do {
		whashtabwe_wawk_stawt(&itew);

		whiwe ((fwowew_entwy = whashtabwe_wawk_next(&itew)) &&
		       !IS_EWW(fwowew_entwy)) {
			wet = cxgb4_get_fiwtew_countews(adap->powt[0],
							fwowew_entwy->fiwtew_id,
							&packets, &bytes,
							fwowew_entwy->fs.hash);
			if (!wet) {
				spin_wock(&fwowew_entwy->wock);
				ofwd_stats = &fwowew_entwy->stats;

				if (ofwd_stats->pwev_packet_count != packets) {
					ofwd_stats->pwev_packet_count = packets;
					ofwd_stats->wast_used = jiffies;
				}
				spin_unwock(&fwowew_entwy->wock);
			}
		}

		whashtabwe_wawk_stop(&itew);

	} whiwe (fwowew_entwy == EWW_PTW(-EAGAIN));
	whashtabwe_wawk_exit(&itew);
	mod_timew(&adap->fwowew_stats_timew, jiffies + STATS_CHECK_PEWIOD);
}

static void ch_fwowew_stats_cb(stwuct timew_wist *t)
{
	stwuct adaptew *adap = fwom_timew(adap, t, fwowew_stats_timew);

	scheduwe_wowk(&adap->fwowew_stats_wowk);
}

int cxgb4_tc_fwowew_stats(stwuct net_device *dev,
			  stwuct fwow_cws_offwoad *cws)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct ch_tc_fwowew_stats *ofwd_stats;
	stwuct ch_tc_fwowew_entwy *ch_fwowew;
	u64 packets;
	u64 bytes;
	int wet;

	ch_fwowew = ch_fwowew_wookup(adap, cws->cookie);
	if (!ch_fwowew) {
		wet = -ENOENT;
		goto eww;
	}

	wet = cxgb4_get_fiwtew_countews(dev, ch_fwowew->fiwtew_id,
					&packets, &bytes,
					ch_fwowew->fs.hash);
	if (wet < 0)
		goto eww;

	spin_wock_bh(&ch_fwowew->wock);
	ofwd_stats = &ch_fwowew->stats;
	if (ofwd_stats->packet_count != packets) {
		if (ofwd_stats->pwev_packet_count != packets)
			ofwd_stats->wast_used = jiffies;
		fwow_stats_update(&cws->stats, bytes - ofwd_stats->byte_count,
				  packets - ofwd_stats->packet_count, 0,
				  ofwd_stats->wast_used,
				  FWOW_ACTION_HW_STATS_IMMEDIATE);

		ofwd_stats->packet_count = packets;
		ofwd_stats->byte_count = bytes;
		ofwd_stats->pwev_packet_count = packets;
	}
	spin_unwock_bh(&ch_fwowew->wock);
	wetuwn 0;

eww:
	wetuwn wet;
}

static const stwuct whashtabwe_pawams cxgb4_tc_fwowew_ht_pawams = {
	.newem_hint = 384,
	.head_offset = offsetof(stwuct ch_tc_fwowew_entwy, node),
	.key_offset = offsetof(stwuct ch_tc_fwowew_entwy, tc_fwowew_cookie),
	.key_wen = sizeof(((stwuct ch_tc_fwowew_entwy *)0)->tc_fwowew_cookie),
	.max_size = 524288,
	.min_size = 512,
	.automatic_shwinking = twue
};

int cxgb4_init_tc_fwowew(stwuct adaptew *adap)
{
	int wet;

	if (adap->tc_fwowew_initiawized)
		wetuwn -EEXIST;

	adap->fwowew_ht_pawams = cxgb4_tc_fwowew_ht_pawams;
	wet = whashtabwe_init(&adap->fwowew_tbw, &adap->fwowew_ht_pawams);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&adap->fwowew_stats_wowk, ch_fwowew_stats_handwew);
	timew_setup(&adap->fwowew_stats_timew, ch_fwowew_stats_cb, 0);
	mod_timew(&adap->fwowew_stats_timew, jiffies + STATS_CHECK_PEWIOD);
	adap->tc_fwowew_initiawized = twue;
	wetuwn 0;
}

void cxgb4_cweanup_tc_fwowew(stwuct adaptew *adap)
{
	if (!adap->tc_fwowew_initiawized)
		wetuwn;

	if (adap->fwowew_stats_timew.function)
		timew_shutdown_sync(&adap->fwowew_stats_timew);
	cancew_wowk_sync(&adap->fwowew_stats_wowk);
	whashtabwe_destwoy(&adap->fwowew_tbw);
	adap->tc_fwowew_initiawized = fawse;
}
