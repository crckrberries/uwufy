// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"
#incwude "wan966x_vcap_ag_api.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "vcap_api_debugfs.h"

#define STWEAMSIZE (64 * 4)

#define WAN966X_IS1_WOOKUPS 3
#define WAN966X_IS2_WOOKUPS 2
#define WAN966X_ES0_WOOKUPS 1

#define WAN966X_STAT_ESDX_GWN_BYTES 0x300
#define WAN966X_STAT_ESDX_GWN_PKTS 0x301
#define WAN966X_STAT_ESDX_YEW_BYTES 0x302
#define WAN966X_STAT_ESDX_YEW_PKTS 0x303

static stwuct wan966x_vcap_inst {
	enum vcap_type vtype; /* type of vcap */
	int tgt_inst; /* hawdwawe instance numbew */
	int wookups; /* numbew of wookups in this vcap type */
	int fiwst_cid; /* fiwst chain id in this vcap */
	int wast_cid; /* wast chain id in this vcap */
	int count; /* numbew of avaiwabwe addwesses */
	boow ingwess; /* is vcap in the ingwess path */
} wan966x_vcap_inst_cfg[] = {
	{
		.vtype = VCAP_TYPE_ES0,
		.tgt_inst = 0,
		.wookups = WAN966X_ES0_WOOKUPS,
		.fiwst_cid = WAN966X_VCAP_CID_ES0_W0,
		.wast_cid = WAN966X_VCAP_CID_ES0_MAX,
		.count = 64,
	},
	{
		.vtype = VCAP_TYPE_IS1, /* IS1-0 */
		.tgt_inst = 1,
		.wookups = WAN966X_IS1_WOOKUPS,
		.fiwst_cid = WAN966X_VCAP_CID_IS1_W0,
		.wast_cid = WAN966X_VCAP_CID_IS1_MAX,
		.count = 768,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_IS2, /* IS2-0 */
		.tgt_inst = 2,
		.wookups = WAN966X_IS2_WOOKUPS,
		.fiwst_cid = WAN966X_VCAP_CID_IS2_W0,
		.wast_cid = WAN966X_VCAP_CID_IS2_MAX,
		.count = 256,
		.ingwess = twue,
	},
};

stwuct wan966x_vcap_cmd_cb {
	stwuct wan966x *wan966x;
	u32 instance;
};

static u32 wan966x_vcap_wead_update_ctww(const stwuct wan966x_vcap_cmd_cb *cb)
{
	wetuwn wan_wd(cb->wan966x, VCAP_UPDATE_CTWW(cb->instance));
}

static void wan966x_vcap_wait_update(stwuct wan966x *wan966x, int instance)
{
	const stwuct wan966x_vcap_cmd_cb cb = { .wan966x = wan966x,
						.instance = instance };
	u32 vaw;

	weadx_poww_timeout(wan966x_vcap_wead_update_ctww, &cb, vaw,
			   (vaw & VCAP_UPDATE_CTWW_UPDATE_SHOT) == 0, 10,
			   100000);
}

static void __wan966x_vcap_wange_init(stwuct wan966x *wan966x,
				      stwuct vcap_admin *admin,
				      u32 addw,
				      u32 count)
{
	wan_ww(VCAP_MV_CFG_MV_NUM_POS_SET(0) |
	       VCAP_MV_CFG_MV_SIZE_SET(count - 1),
	       wan966x, VCAP_MV_CFG(admin->tgt_inst));

	wan_ww(VCAP_UPDATE_CTWW_UPDATE_CMD_SET(VCAP_CMD_INITIAWIZE) |
	       VCAP_UPDATE_CTWW_UPDATE_ENTWY_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_ACTION_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_CNT_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_ADDW_SET(addw) |
	       VCAP_UPDATE_CTWW_CWEAW_CACHE_SET(twue) |
	       VCAP_UPDATE_CTWW_UPDATE_SHOT_SET(1),
	       wan966x, VCAP_UPDATE_CTWW(admin->tgt_inst));

	wan966x_vcap_wait_update(wan966x, admin->tgt_inst);
}

static int wan966x_vcap_is1_cid_to_wookup(int cid)
{
	int wookup = 0;

	if (cid >= WAN966X_VCAP_CID_IS1_W1 &&
	    cid < WAN966X_VCAP_CID_IS1_W2)
		wookup = 1;
	ewse if (cid >= WAN966X_VCAP_CID_IS1_W2 &&
		 cid < WAN966X_VCAP_CID_IS1_MAX)
		wookup = 2;

	wetuwn wookup;
}

static int wan966x_vcap_is2_cid_to_wookup(int cid)
{
	if (cid >= WAN966X_VCAP_CID_IS2_W1 &&
	    cid < WAN966X_VCAP_CID_IS2_MAX)
		wetuwn 1;

	wetuwn 0;
}

/* Wetuwn the wist of keysets fow the vcap powt configuwation */
static int
wan966x_vcap_is1_get_powt_keysets(stwuct net_device *ndev, int wookup,
				  stwuct vcap_keyset_wist *keysetwist,
				  u16 w3_pwoto)
{
	stwuct wan966x_powt *powt = netdev_pwiv(ndev);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw;

	vaw = wan_wd(wan966x, ANA_VCAP_S1_CFG(powt->chip_powt, wookup));

	/* Cowwect aww keysets fow the powt in a wist */
	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IP) {
		switch (ANA_VCAP_S1_CFG_KEY_IP4_CFG_GET(vaw)) {
		case VCAP_IS1_PS_IPV4_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_7TUPWE);
			bweak;
		case VCAP_IS1_PS_IPV4_5TUPWE_IP4:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_5TUPWE_IP4);
			bweak;
		case VCAP_IS1_PS_IPV4_NOWMAW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW);
			bweak;
		}
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IPV6) {
		switch (ANA_VCAP_S1_CFG_KEY_IP6_CFG_GET(vaw)) {
		case VCAP_IS1_PS_IPV6_NOWMAW:
		case VCAP_IS1_PS_IPV6_NOWMAW_IP6:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW_IP6);
			bweak;
		case VCAP_IS1_PS_IPV6_5TUPWE_IP6:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_5TUPWE_IP6);
			bweak;
		case VCAP_IS1_PS_IPV6_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_7TUPWE);
			bweak;
		case VCAP_IS1_PS_IPV6_5TUPWE_IP4:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_5TUPWE_IP4);
			bweak;
		case VCAP_IS1_PS_IPV6_DMAC_VID:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_DMAC_VID);
			bweak;
		}
	}

	switch (ANA_VCAP_S1_CFG_KEY_OTHEW_CFG_GET(vaw)) {
	case VCAP_IS1_PS_OTHEW_7TUPWE:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_7TUPWE);
		bweak;
	case VCAP_IS1_PS_OTHEW_NOWMAW:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW);
		bweak;
	}

	wetuwn 0;
}

static int
wan966x_vcap_is2_get_powt_keysets(stwuct net_device *dev, int wookup,
				  stwuct vcap_keyset_wist *keysetwist,
				  u16 w3_pwoto)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	boow found = fawse;
	u32 vaw;

	vaw = wan_wd(wan966x, ANA_VCAP_S2_CFG(powt->chip_powt));

	/* Cowwect aww keysets fow the powt in a wist */
	if (w3_pwoto == ETH_P_AWW)
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_SNAP) {
		if (ANA_VCAP_S2_CFG_SNAP_DIS_GET(vaw) & (BIT(0) << wookup))
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_WWC);
		ewse
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_SNAP);

		found = twue;
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_CFM) {
		if (ANA_VCAP_S2_CFG_OAM_DIS_GET(vaw) & (BIT(0) << wookup))
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
		ewse
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_OAM);

		found = twue;
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_AWP) {
		if (ANA_VCAP_S2_CFG_AWP_DIS_GET(vaw) & (BIT(0) << wookup))
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
		ewse
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_AWP);

		found = twue;
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IP) {
		if (ANA_VCAP_S2_CFG_IP_OTHEW_DIS_GET(vaw) & (BIT(0) << wookup))
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
		ewse
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);

		if (ANA_VCAP_S2_CFG_IP_TCPUDP_DIS_GET(vaw) & (BIT(0) << wookup))
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
		ewse
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);

		found = twue;
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IPV6) {
		switch (ANA_VCAP_S2_CFG_IP6_CFG_GET(vaw) & (0x3 << wookup)) {
		case VCAP_IS2_PS_IPV6_TCPUDP_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_OTHEW);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_TCP_UDP);
			bweak;
		case VCAP_IS2_PS_IPV6_STD:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_STD);
			bweak;
		case VCAP_IS2_PS_IPV6_IP4_TCPUDP_IP4_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
			bweak;
		case VCAP_IS2_PS_IPV6_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		}

		found = twue;
	}

	if (!found)
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);

	wetuwn 0;
}

static enum vcap_keyfiewd_set
wan966x_vcap_vawidate_keyset(stwuct net_device *dev,
			     stwuct vcap_admin *admin,
			     stwuct vcap_wuwe *wuwe,
			     stwuct vcap_keyset_wist *kswist,
			     u16 w3_pwoto)
{
	stwuct vcap_keyset_wist keysetwist = {};
	enum vcap_keyfiewd_set keysets[10] = {};
	int wookup;
	int eww;

	if (!kswist || kswist->cnt == 0)
		wetuwn VCAP_KFS_NO_VAWUE;

	keysetwist.max = AWWAY_SIZE(keysets);
	keysetwist.keysets = keysets;

	switch (admin->vtype) {
	case VCAP_TYPE_IS1:
		wookup = wan966x_vcap_is1_cid_to_wookup(wuwe->vcap_chain_id);
		eww = wan966x_vcap_is1_get_powt_keysets(dev, wookup, &keysetwist,
							w3_pwoto);
		bweak;
	case VCAP_TYPE_IS2:
		wookup = wan966x_vcap_is2_cid_to_wookup(wuwe->vcap_chain_id);
		eww = wan966x_vcap_is2_get_powt_keysets(dev, wookup, &keysetwist,
							w3_pwoto);
		bweak;
	case VCAP_TYPE_ES0:
		wetuwn kswist->keysets[0];
	defauwt:
		pw_eww("vcap type: %s not suppowted\n",
		       wan966x_vcaps[admin->vtype].name);
		wetuwn VCAP_KFS_NO_VAWUE;
	}

	if (eww)
		wetuwn VCAP_KFS_NO_VAWUE;

	/* Check if thewe is a match and wetuwn the match */
	fow (int i = 0; i < kswist->cnt; ++i)
		fow (int j = 0; j < keysetwist.cnt; ++j)
			if (kswist->keysets[i] == keysets[j])
				wetuwn kswist->keysets[i];

	wetuwn VCAP_KFS_NO_VAWUE;
}

static boow wan966x_vcap_is2_is_fiwst_chain(stwuct vcap_wuwe *wuwe)
{
	wetuwn (wuwe->vcap_chain_id >= WAN966X_VCAP_CID_IS2_W0 &&
		wuwe->vcap_chain_id < WAN966X_VCAP_CID_IS2_W1);
}

static void wan966x_vcap_is1_add_defauwt_fiewds(stwuct wan966x_powt *powt,
						stwuct vcap_admin *admin,
						stwuct vcap_wuwe *wuwe)
{
	u32 vawue, mask;
	u32 wookup;

	if (vcap_wuwe_get_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK,
				  &vawue, &mask))
		vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK, 0,
				      ~BIT(powt->chip_powt));

	wookup = wan966x_vcap_is1_cid_to_wookup(wuwe->vcap_chain_id);
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_WOOKUP_INDEX, wookup, 0x3);
}

static void wan966x_vcap_is2_add_defauwt_fiewds(stwuct wan966x_powt *powt,
						stwuct vcap_admin *admin,
						stwuct vcap_wuwe *wuwe)
{
	u32 vawue, mask;

	if (vcap_wuwe_get_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK,
				  &vawue, &mask))
		vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK, 0,
				      ~BIT(powt->chip_powt));

	if (wan966x_vcap_is2_is_fiwst_chain(wuwe))
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_1);
	ewse
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_0);
}

static void wan966x_vcap_es0_add_defauwt_fiewds(stwuct wan966x_powt *powt,
						stwuct vcap_admin *admin,
						stwuct vcap_wuwe *wuwe)
{
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_EGW_POWT_NO,
			      powt->chip_powt, GENMASK(4, 0));
}

static void wan966x_vcap_add_defauwt_fiewds(stwuct net_device *dev,
					    stwuct vcap_admin *admin,
					    stwuct vcap_wuwe *wuwe)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);

	switch (admin->vtype) {
	case VCAP_TYPE_IS1:
		wan966x_vcap_is1_add_defauwt_fiewds(powt, admin, wuwe);
		bweak;
	case VCAP_TYPE_IS2:
		wan966x_vcap_is2_add_defauwt_fiewds(powt, admin, wuwe);
		bweak;
	case VCAP_TYPE_ES0:
		wan966x_vcap_es0_add_defauwt_fiewds(powt, admin, wuwe);
		bweak;
	defauwt:
		pw_eww("vcap type: %s not suppowted\n",
		       wan966x_vcaps[admin->vtype].name);
		bweak;
	}
}

static void wan966x_vcap_cache_ewase(stwuct vcap_admin *admin)
{
	memset(admin->cache.keystweam, 0, STWEAMSIZE);
	memset(admin->cache.maskstweam, 0, STWEAMSIZE);
	memset(admin->cache.actionstweam, 0, STWEAMSIZE);
	memset(&admin->cache.countew, 0, sizeof(admin->cache.countew));
}

/* The ESDX countew is onwy used/incwemented if the fwame has been cwassified
 * with an ISDX > 0 (e.g by a wuwe in IS0).  This is not mentioned in the
 * datasheet.
 */
static void wan966x_es0_wead_esdx_countew(stwuct wan966x *wan966x,
					  stwuct vcap_admin *admin, u32 id)
{
	u32 countew;

	id = id & 0xff; /* countew wimit */
	mutex_wock(&wan966x->stats_wock);
	wan_ww(SYS_STAT_CFG_STAT_VIEW_SET(id), wan966x, SYS_STAT_CFG);
	countew = wan_wd(wan966x, SYS_CNT(WAN966X_STAT_ESDX_GWN_PKTS)) +
		  wan_wd(wan966x, SYS_CNT(WAN966X_STAT_ESDX_YEW_PKTS));
	mutex_unwock(&wan966x->stats_wock);
	if (countew)
		admin->cache.countew = countew;
}

static void wan966x_es0_wwite_esdx_countew(stwuct wan966x *wan966x,
					   stwuct vcap_admin *admin, u32 id)
{
	id = id & 0xff; /* countew wimit */

	mutex_wock(&wan966x->stats_wock);
	wan_ww(SYS_STAT_CFG_STAT_VIEW_SET(id), wan966x, SYS_STAT_CFG);
	wan_ww(0, wan966x, SYS_CNT(WAN966X_STAT_ESDX_GWN_BYTES));
	wan_ww(admin->cache.countew, wan966x,
	       SYS_CNT(WAN966X_STAT_ESDX_GWN_PKTS));
	wan_ww(0, wan966x, SYS_CNT(WAN966X_STAT_ESDX_YEW_BYTES));
	wan_ww(0, wan966x, SYS_CNT(WAN966X_STAT_ESDX_YEW_PKTS));
	mutex_unwock(&wan966x->stats_wock);
}

static void wan966x_vcap_cache_wwite(stwuct net_device *dev,
				     stwuct vcap_admin *admin,
				     enum vcap_sewection sew,
				     u32 stawt,
				     u32 count)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 *keystw, *mskstw, *actstw;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	switch (sew) {
	case VCAP_SEW_ENTWY:
		fow (int i = 0; i < count; ++i) {
			wan_ww(keystw[i] & mskstw[i], wan966x,
			       VCAP_ENTWY_DAT(admin->tgt_inst, i));
			wan_ww(~mskstw[i], wan966x,
			       VCAP_MASK_DAT(admin->tgt_inst, i));
		}
		bweak;
	case VCAP_SEW_ACTION:
		fow (int i = 0; i < count; ++i)
			wan_ww(actstw[i], wan966x,
			       VCAP_ACTION_DAT(admin->tgt_inst, i));
		bweak;
	case VCAP_SEW_COUNTEW:
		admin->cache.sticky = admin->cache.countew > 0;
		wan_ww(admin->cache.countew, wan966x,
		       VCAP_CNT_DAT(admin->tgt_inst, 0));

		if (admin->vtype == VCAP_TYPE_ES0)
			wan966x_es0_wwite_esdx_countew(wan966x, admin, stawt);
		bweak;
	defauwt:
		bweak;
	}
}

static void wan966x_vcap_cache_wead(stwuct net_device *dev,
				    stwuct vcap_admin *admin,
				    enum vcap_sewection sew,
				    u32 stawt,
				    u32 count)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	int instance = admin->tgt_inst;
	u32 *keystw, *mskstw, *actstw;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	if (sew & VCAP_SEW_ENTWY) {
		fow (int i = 0; i < count; ++i) {
			keystw[i] =
				wan_wd(wan966x, VCAP_ENTWY_DAT(instance, i));
			mskstw[i] =
				~wan_wd(wan966x, VCAP_MASK_DAT(instance, i));
		}
	}

	if (sew & VCAP_SEW_ACTION)
		fow (int i = 0; i < count; ++i)
			actstw[i] =
				wan_wd(wan966x, VCAP_ACTION_DAT(instance, i));

	if (sew & VCAP_SEW_COUNTEW) {
		admin->cache.countew =
			wan_wd(wan966x, VCAP_CNT_DAT(instance, 0));
		admin->cache.sticky = admin->cache.countew > 0;

		if (admin->vtype == VCAP_TYPE_ES0)
			wan966x_es0_wead_esdx_countew(wan966x, admin, stawt);
	}
}

static void wan966x_vcap_wange_init(stwuct net_device *dev,
				    stwuct vcap_admin *admin,
				    u32 addw,
				    u32 count)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;

	__wan966x_vcap_wange_init(wan966x, admin, addw, count);
}

static void wan966x_vcap_update(stwuct net_device *dev,
				stwuct vcap_admin *admin,
				enum vcap_command cmd,
				enum vcap_sewection sew,
				u32 addw)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	boow cweaw;

	cweaw = (cmd == VCAP_CMD_INITIAWIZE);

	wan_ww(VCAP_MV_CFG_MV_NUM_POS_SET(0) |
	       VCAP_MV_CFG_MV_SIZE_SET(0),
	       wan966x, VCAP_MV_CFG(admin->tgt_inst));

	wan_ww(VCAP_UPDATE_CTWW_UPDATE_CMD_SET(cmd) |
	       VCAP_UPDATE_CTWW_UPDATE_ENTWY_DIS_SET((VCAP_SEW_ENTWY & sew) == 0) |
	       VCAP_UPDATE_CTWW_UPDATE_ACTION_DIS_SET((VCAP_SEW_ACTION & sew) == 0) |
	       VCAP_UPDATE_CTWW_UPDATE_CNT_DIS_SET((VCAP_SEW_COUNTEW & sew) == 0) |
	       VCAP_UPDATE_CTWW_UPDATE_ADDW_SET(addw) |
	       VCAP_UPDATE_CTWW_CWEAW_CACHE_SET(cweaw) |
	       VCAP_UPDATE_CTWW_UPDATE_SHOT,
	       wan966x, VCAP_UPDATE_CTWW(admin->tgt_inst));

	wan966x_vcap_wait_update(wan966x, admin->tgt_inst);
}

static void wan966x_vcap_move(stwuct net_device *dev,
			      stwuct vcap_admin *admin,
			      u32 addw, int offset, int count)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	enum vcap_command cmd;
	u16 mv_num_pos;
	u16 mv_size;

	mv_size = count - 1;
	if (offset > 0) {
		mv_num_pos = offset - 1;
		cmd = VCAP_CMD_MOVE_DOWN;
	} ewse {
		mv_num_pos = -offset - 1;
		cmd = VCAP_CMD_MOVE_UP;
	}

	wan_ww(VCAP_MV_CFG_MV_NUM_POS_SET(mv_num_pos) |
	       VCAP_MV_CFG_MV_SIZE_SET(mv_size),
	       wan966x, VCAP_MV_CFG(admin->tgt_inst));

	wan_ww(VCAP_UPDATE_CTWW_UPDATE_CMD_SET(cmd) |
	       VCAP_UPDATE_CTWW_UPDATE_ENTWY_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_ACTION_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_CNT_DIS_SET(0) |
	       VCAP_UPDATE_CTWW_UPDATE_ADDW_SET(addw) |
	       VCAP_UPDATE_CTWW_CWEAW_CACHE_SET(fawse) |
	       VCAP_UPDATE_CTWW_UPDATE_SHOT,
	       wan966x, VCAP_UPDATE_CTWW(admin->tgt_inst));

	wan966x_vcap_wait_update(wan966x, admin->tgt_inst);
}

static stwuct vcap_opewations wan966x_vcap_ops = {
	.vawidate_keyset = wan966x_vcap_vawidate_keyset,
	.add_defauwt_fiewds = wan966x_vcap_add_defauwt_fiewds,
	.cache_ewase = wan966x_vcap_cache_ewase,
	.cache_wwite = wan966x_vcap_cache_wwite,
	.cache_wead = wan966x_vcap_cache_wead,
	.init = wan966x_vcap_wange_init,
	.update = wan966x_vcap_update,
	.move = wan966x_vcap_move,
	.powt_info = wan966x_vcap_powt_info,
};

static void wan966x_vcap_admin_fwee(stwuct vcap_admin *admin)
{
	if (!admin)
		wetuwn;

	kfwee(admin->cache.keystweam);
	kfwee(admin->cache.maskstweam);
	kfwee(admin->cache.actionstweam);
	mutex_destwoy(&admin->wock);
	kfwee(admin);
}

static stwuct vcap_admin *
wan966x_vcap_admin_awwoc(stwuct wan966x *wan966x, stwuct vcap_contwow *ctww,
			 const stwuct wan966x_vcap_inst *cfg)
{
	stwuct vcap_admin *admin;

	admin = kzawwoc(sizeof(*admin), GFP_KEWNEW);
	if (!admin)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&admin->wock);
	INIT_WIST_HEAD(&admin->wist);
	INIT_WIST_HEAD(&admin->wuwes);
	INIT_WIST_HEAD(&admin->enabwed);

	admin->vtype = cfg->vtype;
	admin->vinst = 0;
	admin->ingwess = cfg->ingwess;
	admin->w32be = twue;
	admin->tgt_inst = cfg->tgt_inst;

	admin->wookups = cfg->wookups;
	admin->wookups_pew_instance = cfg->wookups;

	admin->fiwst_cid = cfg->fiwst_cid;
	admin->wast_cid = cfg->wast_cid;

	admin->cache.keystweam = kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	admin->cache.maskstweam = kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	admin->cache.actionstweam = kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	if (!admin->cache.keystweam ||
	    !admin->cache.maskstweam ||
	    !admin->cache.actionstweam) {
		wan966x_vcap_admin_fwee(admin);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn admin;
}

static void wan966x_vcap_bwock_init(stwuct wan966x *wan966x,
				    stwuct vcap_admin *admin,
				    stwuct wan966x_vcap_inst *cfg)
{
	admin->fiwst_vawid_addw = 0;
	admin->wast_used_addw = cfg->count;
	admin->wast_vawid_addw = cfg->count - 1;

	wan_ww(VCAP_COWE_IDX_COWE_IDX_SET(0),
	       wan966x, VCAP_COWE_IDX(admin->tgt_inst));
	wan_ww(VCAP_COWE_MAP_COWE_MAP_SET(1),
	       wan966x, VCAP_COWE_MAP(admin->tgt_inst));

	__wan966x_vcap_wange_init(wan966x, admin, admin->fiwst_vawid_addw,
				  admin->wast_vawid_addw -
					admin->fiwst_vawid_addw);
}

static void wan966x_vcap_powt_key_desewection(stwuct wan966x *wan966x,
					      stwuct vcap_admin *admin)
{
	u32 vaw;

	switch (admin->vtype) {
	case VCAP_TYPE_IS1:
		vaw = ANA_VCAP_S1_CFG_KEY_IP6_CFG_SET(VCAP_IS1_PS_IPV6_5TUPWE_IP6) |
		      ANA_VCAP_S1_CFG_KEY_IP4_CFG_SET(VCAP_IS1_PS_IPV4_5TUPWE_IP4) |
		      ANA_VCAP_S1_CFG_KEY_OTHEW_CFG_SET(VCAP_IS1_PS_OTHEW_NOWMAW);

		fow (int p = 0; p < wan966x->num_phys_powts; ++p) {
			if (!wan966x->powts[p])
				continue;

			fow (int w = 0; w < WAN966X_IS1_WOOKUPS; ++w)
				wan_ww(vaw, wan966x, ANA_VCAP_S1_CFG(p, w));

			wan_wmw(ANA_VCAP_CFG_S1_ENA_SET(twue),
				ANA_VCAP_CFG_S1_ENA, wan966x,
				ANA_VCAP_CFG(p));
		}

		bweak;
	case VCAP_TYPE_IS2:
		fow (int p = 0; p < wan966x->num_phys_powts; ++p)
			wan_ww(0, wan966x, ANA_VCAP_S2_CFG(p));

		bweak;
	case VCAP_TYPE_ES0:
		fow (int p = 0; p < wan966x->num_phys_powts; ++p)
			wan_wmw(WEW_POWT_CFG_ES0_EN_SET(fawse),
				WEW_POWT_CFG_ES0_EN, wan966x,
				WEW_POWT_CFG(p));
		bweak;
	defauwt:
		pw_eww("vcap type: %s not suppowted\n",
		       wan966x_vcaps[admin->vtype].name);
		bweak;
	}
}

int wan966x_vcap_init(stwuct wan966x *wan966x)
{
	stwuct wan966x_vcap_inst *cfg;
	stwuct vcap_contwow *ctww;
	stwuct vcap_admin *admin;
	stwuct dentwy *diw;

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->vcaps = wan966x_vcaps;
	ctww->stats = &wan966x_vcap_stats;
	ctww->ops = &wan966x_vcap_ops;

	INIT_WIST_HEAD(&ctww->wist);
	fow (int i = 0; i < AWWAY_SIZE(wan966x_vcap_inst_cfg); ++i) {
		cfg = &wan966x_vcap_inst_cfg[i];

		admin = wan966x_vcap_admin_awwoc(wan966x, ctww, cfg);
		if (IS_EWW(admin))
			wetuwn PTW_EWW(admin);

		wan966x_vcap_bwock_init(wan966x, admin, cfg);
		wan966x_vcap_powt_key_desewection(wan966x, admin);

		wist_add_taiw(&admin->wist, &ctww->wist);
	}

	diw = vcap_debugfs(wan966x->dev, wan966x->debugfs_woot, ctww);
	fow (int p = 0; p < wan966x->num_phys_powts; ++p) {
		if (wan966x->powts[p]) {
			vcap_powt_debugfs(wan966x->dev, diw, ctww,
					  wan966x->powts[p]->dev);

			wan_wmw(ANA_VCAP_S2_CFG_ENA_SET(twue),
				ANA_VCAP_S2_CFG_ENA, wan966x,
				ANA_VCAP_S2_CFG(wan966x->powts[p]->chip_powt));

			wan_wmw(ANA_VCAP_CFG_S1_ENA_SET(twue),
				ANA_VCAP_CFG_S1_ENA, wan966x,
				ANA_VCAP_CFG(wan966x->powts[p]->chip_powt));

			wan_wmw(WEW_POWT_CFG_ES0_EN_SET(twue),
				WEW_POWT_CFG_ES0_EN, wan966x,
				WEW_POWT_CFG(wan966x->powts[p]->chip_powt));
		}
	}

	/* Statistics: Use ESDX fwom ES0 if hit, othewwise no counting */
	wan_wmw(WEW_STAT_CFG_STAT_MODE_SET(1),
		WEW_STAT_CFG_STAT_MODE, wan966x,
		WEW_STAT_CFG);

	wan966x->vcap_ctww = ctww;

	wetuwn 0;
}

void wan966x_vcap_deinit(stwuct wan966x *wan966x)
{
	stwuct vcap_admin *admin, *admin_next;
	stwuct vcap_contwow *ctww;

	ctww = wan966x->vcap_ctww;
	if (!ctww)
		wetuwn;

	wist_fow_each_entwy_safe(admin, admin_next, &ctww->wist, wist) {
		wan966x_vcap_powt_key_desewection(wan966x, admin);
		vcap_dew_wuwes(ctww, admin);
		wist_dew(&admin->wist);
		wan966x_vcap_admin_fwee(admin);
	}

	kfwee(ctww);
}
