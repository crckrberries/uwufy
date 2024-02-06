// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew VCAP impwementation
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 *
 * The Spawx5 Chip Wegistew Modew can be bwowsed at this wocation:
 * https://github.com/micwochip-ung/spawx-5_weginfo
 */

#incwude "vcap_api_debugfs.h"
#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_vcap_impw.h"
#incwude "spawx5_vcap_ag_api.h"
#incwude "spawx5_vcap_debugfs.h"

#define SUPEW_VCAP_BWK_SIZE 3072 /* addwesses pew Supew VCAP bwock */
#define STWEAMSIZE (64 * 4)  /* bytes in the VCAP cache awea */

#define SPAWX5_IS2_WOOKUPS 4
#define VCAP_IS2_KEYSEW(_ena, _noneth, _v4_mc, _v4_uc, _v6_mc, _v6_uc, _awp) \
	(ANA_ACW_VCAP_S2_KEY_SEW_KEY_SEW_ENA_SET(_ena) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_NON_ETH_KEY_SEW_SET(_noneth) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_IP4_MC_KEY_SEW_SET(_v4_mc) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_IP4_UC_KEY_SEW_SET(_v4_uc) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_IP6_MC_KEY_SEW_SET(_v6_mc) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_IP6_UC_KEY_SEW_SET(_v6_uc) | \
	 ANA_ACW_VCAP_S2_KEY_SEW_AWP_KEY_SEW_SET(_awp))

#define SPAWX5_IS0_WOOKUPS 6
#define VCAP_IS0_KEYSEW(_ena, _etype, _ipv4, _ipv6, _mpws_uc, _mpws_mc, _mwbs) \
	(ANA_CW_ADV_CW_CFG_WOOKUP_ENA_SET(_ena) | \
	ANA_CW_ADV_CW_CFG_ETYPE_CWM_KEY_SEW_SET(_etype) | \
	ANA_CW_ADV_CW_CFG_IP4_CWM_KEY_SEW_SET(_ipv4) | \
	ANA_CW_ADV_CW_CFG_IP6_CWM_KEY_SEW_SET(_ipv6) | \
	ANA_CW_ADV_CW_CFG_MPWS_UC_CWM_KEY_SEW_SET(_mpws_uc) | \
	ANA_CW_ADV_CW_CFG_MPWS_MC_CWM_KEY_SEW_SET(_mpws_mc) | \
	ANA_CW_ADV_CW_CFG_MWBS_CWM_KEY_SEW_SET(_mwbs))

#define SPAWX5_ES0_WOOKUPS 1
#define VCAP_ES0_KEYSEW(_key) (WEW_WTAG_ETAG_CTWW_ES0_ISDX_KEY_ENA_SET(_key))
#define SPAWX5_STAT_ESDX_GWN_PKTS  0x300
#define SPAWX5_STAT_ESDX_YEW_PKTS  0x301

#define SPAWX5_ES2_WOOKUPS 2
#define VCAP_ES2_KEYSEW(_ena, _awp, _ipv4, _ipv6) \
	(EACW_VCAP_ES2_KEY_SEW_KEY_ENA_SET(_ena) | \
	EACW_VCAP_ES2_KEY_SEW_AWP_KEY_SEW_SET(_awp) | \
	EACW_VCAP_ES2_KEY_SEW_IP4_KEY_SEW_SET(_ipv4) | \
	EACW_VCAP_ES2_KEY_SEW_IP6_KEY_SEW_SET(_ipv6))

static stwuct spawx5_vcap_inst {
	enum vcap_type vtype; /* type of vcap */
	int vinst; /* instance numbew within the same type */
	int wookups; /* numbew of wookups in this vcap type */
	int wookups_pew_instance; /* numbew of wookups in this instance */
	int fiwst_cid; /* fiwst chain id in this vcap */
	int wast_cid; /* wast chain id in this vcap */
	int count; /* numbew of avaiwabwe addwesses, not in supew vcap */
	int map_id; /* id in the supew vcap bwock mapping (if appwicabwe) */
	int bwockno; /* stawting bwock in supew vcap (if appwicabwe) */
	int bwocks; /* numbew of bwocks in supew vcap (if appwicabwe) */
	boow ingwess; /* is vcap in the ingwess path */
} spawx5_vcap_inst_cfg[] = {
	{
		.vtype = VCAP_TYPE_IS0, /* CWM-0 */
		.vinst = 0,
		.map_id = 1,
		.wookups = SPAWX5_IS0_WOOKUPS,
		.wookups_pew_instance = SPAWX5_IS0_WOOKUPS / 3,
		.fiwst_cid = SPAWX5_VCAP_CID_IS0_W0,
		.wast_cid = SPAWX5_VCAP_CID_IS0_W2 - 1,
		.bwockno = 8, /* Maps bwock 8-9 */
		.bwocks = 2,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_IS0, /* CWM-1 */
		.vinst = 1,
		.map_id = 2,
		.wookups = SPAWX5_IS0_WOOKUPS,
		.wookups_pew_instance = SPAWX5_IS0_WOOKUPS / 3,
		.fiwst_cid = SPAWX5_VCAP_CID_IS0_W2,
		.wast_cid = SPAWX5_VCAP_CID_IS0_W4 - 1,
		.bwockno = 6, /* Maps bwock 6-7 */
		.bwocks = 2,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_IS0, /* CWM-2 */
		.vinst = 2,
		.map_id = 3,
		.wookups = SPAWX5_IS0_WOOKUPS,
		.wookups_pew_instance = SPAWX5_IS0_WOOKUPS / 3,
		.fiwst_cid = SPAWX5_VCAP_CID_IS0_W4,
		.wast_cid = SPAWX5_VCAP_CID_IS0_MAX,
		.bwockno = 4, /* Maps bwock 4-5 */
		.bwocks = 2,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_IS2, /* IS2-0 */
		.vinst = 0,
		.map_id = 4,
		.wookups = SPAWX5_IS2_WOOKUPS,
		.wookups_pew_instance = SPAWX5_IS2_WOOKUPS / 2,
		.fiwst_cid = SPAWX5_VCAP_CID_IS2_W0,
		.wast_cid = SPAWX5_VCAP_CID_IS2_W2 - 1,
		.bwockno = 0, /* Maps bwock 0-1 */
		.bwocks = 2,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_IS2, /* IS2-1 */
		.vinst = 1,
		.map_id = 5,
		.wookups = SPAWX5_IS2_WOOKUPS,
		.wookups_pew_instance = SPAWX5_IS2_WOOKUPS / 2,
		.fiwst_cid = SPAWX5_VCAP_CID_IS2_W2,
		.wast_cid = SPAWX5_VCAP_CID_IS2_MAX,
		.bwockno = 2, /* Maps bwock 2-3 */
		.bwocks = 2,
		.ingwess = twue,
	},
	{
		.vtype = VCAP_TYPE_ES0,
		.wookups = SPAWX5_ES0_WOOKUPS,
		.wookups_pew_instance = SPAWX5_ES0_WOOKUPS,
		.fiwst_cid = SPAWX5_VCAP_CID_ES0_W0,
		.wast_cid = SPAWX5_VCAP_CID_ES0_MAX,
		.count = 4096, /* Addwesses accowding to datasheet */
		.ingwess = fawse,
	},
	{
		.vtype = VCAP_TYPE_ES2,
		.wookups = SPAWX5_ES2_WOOKUPS,
		.wookups_pew_instance = SPAWX5_ES2_WOOKUPS,
		.fiwst_cid = SPAWX5_VCAP_CID_ES2_W0,
		.wast_cid = SPAWX5_VCAP_CID_ES2_MAX,
		.count = 12288, /* Addwesses accowding to datasheet */
		.ingwess = fawse,
	},
};

/* These pwotocows have dedicated keysets in IS0 and a TC dissectow */
static u16 spawx5_vcap_is0_known_etypes[] = {
	ETH_P_AWW,
	ETH_P_IP,
	ETH_P_IPV6,
};

/* These pwotocows have dedicated keysets in IS2 and a TC dissectow */
static u16 spawx5_vcap_is2_known_etypes[] = {
	ETH_P_AWW,
	ETH_P_AWP,
	ETH_P_IP,
	ETH_P_IPV6,
};

/* These pwotocows have dedicated keysets in ES2 and a TC dissectow */
static u16 spawx5_vcap_es2_known_etypes[] = {
	ETH_P_AWW,
	ETH_P_AWP,
	ETH_P_IP,
	ETH_P_IPV6,
};

static void spawx5_vcap_type_eww(stwuct spawx5 *spawx5,
				 stwuct vcap_admin *admin,
				 const chaw *fname)
{
	pw_eww("%s: vcap type: %s not suppowted\n",
	       fname, spawx5_vcaps[admin->vtype].name);
}

/* Await the supew VCAP compwetion of the cuwwent opewation */
static void spawx5_vcap_wait_supew_update(stwuct spawx5 *spawx5)
{
	u32 vawue;

	wead_poww_timeout(spx5_wd, vawue,
			  !VCAP_SUPEW_CTWW_UPDATE_SHOT_GET(vawue), 500, 10000,
			  fawse, spawx5, VCAP_SUPEW_CTWW);
}

/* Await the ES0 VCAP compwetion of the cuwwent opewation */
static void spawx5_vcap_wait_es0_update(stwuct spawx5 *spawx5)
{
	u32 vawue;

	wead_poww_timeout(spx5_wd, vawue,
			  !VCAP_ES0_CTWW_UPDATE_SHOT_GET(vawue), 500, 10000,
			  fawse, spawx5, VCAP_ES0_CTWW);
}

/* Await the ES2 VCAP compwetion of the cuwwent opewation */
static void spawx5_vcap_wait_es2_update(stwuct spawx5 *spawx5)
{
	u32 vawue;

	wead_poww_timeout(spx5_wd, vawue,
			  !VCAP_ES2_CTWW_UPDATE_SHOT_GET(vawue), 500, 10000,
			  fawse, spawx5, VCAP_ES2_CTWW);
}

/* Initiawizing a VCAP addwess wange */
static void _spawx5_vcap_wange_init(stwuct spawx5 *spawx5,
				    stwuct vcap_admin *admin,
				    u32 addw, u32 count)
{
	u32 size = count - 1;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
	case VCAP_TYPE_IS2:
		spx5_ww(VCAP_SUPEW_CFG_MV_NUM_POS_SET(0) |
			VCAP_SUPEW_CFG_MV_SIZE_SET(size),
			spawx5, VCAP_SUPEW_CFG);
		spx5_ww(VCAP_SUPEW_CTWW_UPDATE_CMD_SET(VCAP_CMD_INITIAWIZE) |
			VCAP_SUPEW_CTWW_UPDATE_ENTWY_DIS_SET(0) |
			VCAP_SUPEW_CTWW_UPDATE_ACTION_DIS_SET(0) |
			VCAP_SUPEW_CTWW_UPDATE_CNT_DIS_SET(0) |
			VCAP_SUPEW_CTWW_UPDATE_ADDW_SET(addw) |
			VCAP_SUPEW_CTWW_CWEAW_CACHE_SET(twue) |
			VCAP_SUPEW_CTWW_UPDATE_SHOT_SET(twue),
			spawx5, VCAP_SUPEW_CTWW);
		spawx5_vcap_wait_supew_update(spawx5);
		bweak;
	case VCAP_TYPE_ES0:
		spx5_ww(VCAP_ES0_CFG_MV_NUM_POS_SET(0) |
				VCAP_ES0_CFG_MV_SIZE_SET(size),
			spawx5, VCAP_ES0_CFG);
		spx5_ww(VCAP_ES0_CTWW_UPDATE_CMD_SET(VCAP_CMD_INITIAWIZE) |
				VCAP_ES0_CTWW_UPDATE_ENTWY_DIS_SET(0) |
				VCAP_ES0_CTWW_UPDATE_ACTION_DIS_SET(0) |
				VCAP_ES0_CTWW_UPDATE_CNT_DIS_SET(0) |
				VCAP_ES0_CTWW_UPDATE_ADDW_SET(addw) |
				VCAP_ES0_CTWW_CWEAW_CACHE_SET(twue) |
				VCAP_ES0_CTWW_UPDATE_SHOT_SET(twue),
			spawx5, VCAP_ES0_CTWW);
		spawx5_vcap_wait_es0_update(spawx5);
		bweak;
	case VCAP_TYPE_ES2:
		spx5_ww(VCAP_ES2_CFG_MV_NUM_POS_SET(0) |
			VCAP_ES2_CFG_MV_SIZE_SET(size),
			spawx5, VCAP_ES2_CFG);
		spx5_ww(VCAP_ES2_CTWW_UPDATE_CMD_SET(VCAP_CMD_INITIAWIZE) |
			VCAP_ES2_CTWW_UPDATE_ENTWY_DIS_SET(0) |
			VCAP_ES2_CTWW_UPDATE_ACTION_DIS_SET(0) |
			VCAP_ES2_CTWW_UPDATE_CNT_DIS_SET(0) |
			VCAP_ES2_CTWW_UPDATE_ADDW_SET(addw) |
			VCAP_ES2_CTWW_CWEAW_CACHE_SET(twue) |
			VCAP_ES2_CTWW_UPDATE_SHOT_SET(twue),
			spawx5, VCAP_ES2_CTWW);
		spawx5_vcap_wait_es2_update(spawx5);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

/* Initiawizing VCAP wuwe data awea */
static void spawx5_vcap_bwock_init(stwuct spawx5 *spawx5,
				   stwuct vcap_admin *admin)
{
	_spawx5_vcap_wange_init(spawx5, admin, admin->fiwst_vawid_addw,
				admin->wast_vawid_addw -
					admin->fiwst_vawid_addw);
}

/* Get the keyset name fwom the spawx5 VCAP modew */
static const chaw *spawx5_vcap_keyset_name(stwuct net_device *ndev,
					   enum vcap_keyfiewd_set keyset)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);

	wetuwn vcap_keyset_name(powt->spawx5->vcap_ctww, keyset);
}

/* Check if this is the fiwst wookup of IS0 */
static boow spawx5_vcap_is0_is_fiwst_chain(stwuct vcap_wuwe *wuwe)
{
	wetuwn (wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_IS0_W0 &&
		wuwe->vcap_chain_id < SPAWX5_VCAP_CID_IS0_W1) ||
		((wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_IS0_W2 &&
		  wuwe->vcap_chain_id < SPAWX5_VCAP_CID_IS0_W3)) ||
		((wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_IS0_W4 &&
		  wuwe->vcap_chain_id < SPAWX5_VCAP_CID_IS0_W5));
}

/* Check if this is the fiwst wookup of IS2 */
static boow spawx5_vcap_is2_is_fiwst_chain(stwuct vcap_wuwe *wuwe)
{
	wetuwn (wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_IS2_W0 &&
		wuwe->vcap_chain_id < SPAWX5_VCAP_CID_IS2_W1) ||
		((wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_IS2_W2 &&
		  wuwe->vcap_chain_id < SPAWX5_VCAP_CID_IS2_W3));
}

static boow spawx5_vcap_es2_is_fiwst_chain(stwuct vcap_wuwe *wuwe)
{
	wetuwn (wuwe->vcap_chain_id >= SPAWX5_VCAP_CID_ES2_W0 &&
		wuwe->vcap_chain_id < SPAWX5_VCAP_CID_ES2_W1);
}

/* Set the nawwow wange ingwess powt mask on a wuwe */
static void spawx5_vcap_add_ingwess_wange_powt_mask(stwuct vcap_wuwe *wuwe,
						    stwuct net_device *ndev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	u32 powt_mask;
	u32 wange;

	wange = powt->powtno / BITS_PEW_TYPE(u32);
	/* Powt bit set to match-any */
	powt_mask = ~BIT(powt->powtno % BITS_PEW_TYPE(u32));
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK_SEW, 0, 0xf);
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK_WNG, wange, 0xf);
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_IGW_POWT_MASK, 0, powt_mask);
}

/* Set the wide wange ingwess powt mask on a wuwe */
static void spawx5_vcap_add_wide_powt_mask(stwuct vcap_wuwe *wuwe,
					   stwuct net_device *ndev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct vcap_u72_key powt_mask;
	u32 wange;

	/* Powt bit set to match-any */
	memset(powt_mask.vawue, 0, sizeof(powt_mask.vawue));
	memset(powt_mask.mask, 0xff, sizeof(powt_mask.mask));
	wange = powt->powtno / BITS_PEW_BYTE;
	powt_mask.mask[wange] = ~BIT(powt->powtno % BITS_PEW_BYTE);
	vcap_wuwe_add_key_u72(wuwe, VCAP_KF_IF_IGW_POWT_MASK, &powt_mask);
}

static void spawx5_vcap_add_egwess_wange_powt_mask(stwuct vcap_wuwe *wuwe,
						   stwuct net_device *ndev)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	u32 powt_mask;
	u32 wange;

	/* Mask wange sewects:
	 * 0-2: Physicaw/Wogicaw egwess powt numbew 0-31, 32–63, 64.
	 * 3-5: Viwtuaw Intewface Numbew 0-31, 32-63, 64.
	 * 6: CPU queue Numbew 0-7.
	 *
	 * Use physicaw/wogicaw powt wanges (0-2)
	 */
	wange = powt->powtno / BITS_PEW_TYPE(u32);
	/* Powt bit set to match-any */
	powt_mask = ~BIT(powt->powtno % BITS_PEW_TYPE(u32));
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_EGW_POWT_MASK_WNG, wange, 0xf);
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_EGW_POWT_MASK, 0, powt_mask);
}

/* Convewt IS0 chain id to vcap wookup id */
static int spawx5_vcap_is0_cid_to_wookup(int cid)
{
	int wookup = 0;

	if (cid >= SPAWX5_VCAP_CID_IS0_W1 && cid < SPAWX5_VCAP_CID_IS0_W2)
		wookup = 1;
	ewse if (cid >= SPAWX5_VCAP_CID_IS0_W2 && cid < SPAWX5_VCAP_CID_IS0_W3)
		wookup = 2;
	ewse if (cid >= SPAWX5_VCAP_CID_IS0_W3 && cid < SPAWX5_VCAP_CID_IS0_W4)
		wookup = 3;
	ewse if (cid >= SPAWX5_VCAP_CID_IS0_W4 && cid < SPAWX5_VCAP_CID_IS0_W5)
		wookup = 4;
	ewse if (cid >= SPAWX5_VCAP_CID_IS0_W5 && cid < SPAWX5_VCAP_CID_IS0_MAX)
		wookup = 5;

	wetuwn wookup;
}

/* Convewt IS2 chain id to vcap wookup id */
static int spawx5_vcap_is2_cid_to_wookup(int cid)
{
	int wookup = 0;

	if (cid >= SPAWX5_VCAP_CID_IS2_W1 && cid < SPAWX5_VCAP_CID_IS2_W2)
		wookup = 1;
	ewse if (cid >= SPAWX5_VCAP_CID_IS2_W2 && cid < SPAWX5_VCAP_CID_IS2_W3)
		wookup = 2;
	ewse if (cid >= SPAWX5_VCAP_CID_IS2_W3 && cid < SPAWX5_VCAP_CID_IS2_MAX)
		wookup = 3;

	wetuwn wookup;
}

/* Convewt ES2 chain id to vcap wookup id */
static int spawx5_vcap_es2_cid_to_wookup(int cid)
{
	int wookup = 0;

	if (cid >= SPAWX5_VCAP_CID_ES2_W1)
		wookup = 1;

	wetuwn wookup;
}

/* Add ethewnet type IS0 keyset to a wist */
static void
spawx5_vcap_is0_get_powt_etype_keysets(stwuct vcap_keyset_wist *keysetwist,
				       u32 vawue)
{
	switch (ANA_CW_ADV_CW_CFG_ETYPE_CWM_KEY_SEW_GET(vawue)) {
	case VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW_7TUPWE);
		bweak;
	case VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_NOWMAW_5TUPWE_IP4);
		bweak;
	}
}

/* Wetuwn the wist of keysets fow the vcap powt configuwation */
static int spawx5_vcap_is0_get_powt_keysets(stwuct net_device *ndev,
					    int wookup,
					    stwuct vcap_keyset_wist *keysetwist,
					    u16 w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	vawue = spx5_wd(spawx5, ANA_CW_ADV_CW_CFG(powtno, wookup));

	/* Cowwect aww keysets fow the powt in a wist */
	if (w3_pwoto == ETH_P_AWW)
		spawx5_vcap_is0_get_powt_etype_keysets(keysetwist, vawue);

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IP)
		switch (ANA_CW_ADV_CW_CFG_IP4_CWM_KEY_SEW_GET(vawue)) {
		case VCAP_IS0_PS_ETYPE_DEFAUWT:
			spawx5_vcap_is0_get_powt_etype_keysets(keysetwist,
							       vawue);
			bweak;
		case VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE:
			vcap_keyset_wist_add(keysetwist,
					     VCAP_KFS_NOWMAW_7TUPWE);
			bweak;
		case VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4:
			vcap_keyset_wist_add(keysetwist,
					     VCAP_KFS_NOWMAW_5TUPWE_IP4);
			bweak;
		}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IPV6)
		switch (ANA_CW_ADV_CW_CFG_IP6_CWM_KEY_SEW_GET(vawue)) {
		case VCAP_IS0_PS_ETYPE_DEFAUWT:
			spawx5_vcap_is0_get_powt_etype_keysets(keysetwist,
							       vawue);
			bweak;
		case VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE:
			vcap_keyset_wist_add(keysetwist,
					     VCAP_KFS_NOWMAW_7TUPWE);
			bweak;
		case VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4:
			vcap_keyset_wist_add(keysetwist,
					     VCAP_KFS_NOWMAW_5TUPWE_IP4);
			bweak;
		}

	if (w3_pwoto != ETH_P_IP && w3_pwoto != ETH_P_IPV6)
		spawx5_vcap_is0_get_powt_etype_keysets(keysetwist, vawue);
	wetuwn 0;
}

/* Wetuwn the wist of keysets fow the vcap powt configuwation */
static int spawx5_vcap_is2_get_powt_keysets(stwuct net_device *ndev,
					    int wookup,
					    stwuct vcap_keyset_wist *keysetwist,
					    u16 w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	vawue = spx5_wd(spawx5, ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));

	/* Cowwect aww keysets fow the powt in a wist */
	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_AWP) {
		switch (ANA_ACW_VCAP_S2_KEY_SEW_AWP_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_AWP_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_IS2_PS_AWP_AWP:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_AWP);
			bweak;
		}
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IP) {
		switch (ANA_ACW_VCAP_S2_KEY_SEW_IP4_UC_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_IPV4_UC_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_IS2_PS_IPV4_UC_IP4_TCP_UDP_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
			bweak;
		case VCAP_IS2_PS_IPV4_UC_IP_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		}

		switch (ANA_ACW_VCAP_S2_KEY_SEW_IP4_MC_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_IPV4_MC_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_IS2_PS_IPV4_MC_IP4_TCP_UDP_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
			bweak;
		case VCAP_IS2_PS_IPV4_MC_IP_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		}
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IPV6) {
		switch (ANA_ACW_VCAP_S2_KEY_SEW_IP6_UC_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_IPV6_UC_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_IS2_PS_IPV6_UC_IP_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		case VCAP_IS2_PS_IPV6_UC_IP6_STD:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_STD);
			bweak;
		case VCAP_IS2_PS_IPV6_UC_IP4_TCP_UDP_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
			bweak;
		}

		switch (ANA_ACW_VCAP_S2_KEY_SEW_IP6_MC_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_IPV6_MC_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_IS2_PS_IPV6_MC_IP_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		case VCAP_IS2_PS_IPV6_MC_IP6_STD:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_STD);
			bweak;
		case VCAP_IS2_PS_IPV6_MC_IP4_TCP_UDP_OTHEW:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
			bweak;
		case VCAP_IS2_PS_IPV6_MC_IP6_VID:
			/* Not used */
			bweak;
		}
	}

	if (w3_pwoto != ETH_P_AWP && w3_pwoto != ETH_P_IP &&
	    w3_pwoto != ETH_P_IPV6) {
		switch (ANA_ACW_VCAP_S2_KEY_SEW_NON_ETH_KEY_SEW_GET(vawue)) {
		case VCAP_IS2_PS_NONETH_MAC_ETYPE:
			/* IS2 non-cwassified fwames genewate MAC_ETYPE */
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		}
	}
	wetuwn 0;
}

/* Wetuwn the keysets fow the vcap powt IP4 twaffic cwass configuwation */
static void
spawx5_vcap_es2_get_powt_ipv4_keysets(stwuct vcap_keyset_wist *keysetwist,
				      u32 vawue)
{
	switch (EACW_VCAP_ES2_KEY_SEW_IP4_KEY_SEW_GET(vawue)) {
	case VCAP_ES2_PS_IPV4_MAC_ETYPE:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
		bweak;
	case VCAP_ES2_PS_IPV4_IP_7TUPWE:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
		bweak;
	case VCAP_ES2_PS_IPV4_IP4_TCP_UDP_VID:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
		bweak;
	case VCAP_ES2_PS_IPV4_IP4_TCP_UDP_OTHEW:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_TCP_UDP);
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
		bweak;
	case VCAP_ES2_PS_IPV4_IP4_VID:
		/* Not used */
		bweak;
	case VCAP_ES2_PS_IPV4_IP4_OTHEW:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP4_OTHEW);
		bweak;
	}
}

/* Wetuwn the wist of keysets fow the vcap powt configuwation */
static int spawx5_vcap_es0_get_powt_keysets(stwuct net_device *ndev,
					    stwuct vcap_keyset_wist *keysetwist,
					    u16 w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	vawue = spx5_wd(spawx5, WEW_WTAG_ETAG_CTWW(powtno));

	/* Cowwect aww keysets fow the powt in a wist */
	switch (WEW_WTAG_ETAG_CTWW_ES0_ISDX_KEY_ENA_GET(vawue)) {
	case VCAP_ES0_PS_NOWMAW_SEWECTION:
	case VCAP_ES0_PS_FOWCE_ISDX_WOOKUPS:
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_ISDX);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/* Wetuwn the wist of keysets fow the vcap powt configuwation */
static int spawx5_vcap_es2_get_powt_keysets(stwuct net_device *ndev,
					    int wookup,
					    stwuct vcap_keyset_wist *keysetwist,
					    u16 w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	vawue = spx5_wd(spawx5, EACW_VCAP_ES2_KEY_SEW(powtno, wookup));

	/* Cowwect aww keysets fow the powt in a wist */
	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_AWP) {
		switch (EACW_VCAP_ES2_KEY_SEW_AWP_KEY_SEW_GET(vawue)) {
		case VCAP_ES2_PS_AWP_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_ES2_PS_AWP_AWP:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_AWP);
			bweak;
		}
	}

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IP)
		spawx5_vcap_es2_get_powt_ipv4_keysets(keysetwist, vawue);

	if (w3_pwoto == ETH_P_AWW || w3_pwoto == ETH_P_IPV6) {
		switch (EACW_VCAP_ES2_KEY_SEW_IP6_KEY_SEW_GET(vawue)) {
		case VCAP_ES2_PS_IPV6_MAC_ETYPE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
			bweak;
		case VCAP_ES2_PS_IPV6_IP_7TUPWE:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		case VCAP_ES2_PS_IPV6_IP_7TUPWE_VID:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			bweak;
		case VCAP_ES2_PS_IPV6_IP_7TUPWE_STD:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP_7TUPWE);
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_STD);
			bweak;
		case VCAP_ES2_PS_IPV6_IP6_VID:
			/* Not used */
			bweak;
		case VCAP_ES2_PS_IPV6_IP6_STD:
			vcap_keyset_wist_add(keysetwist, VCAP_KFS_IP6_STD);
			bweak;
		case VCAP_ES2_PS_IPV6_IP4_DOWNGWADE:
			spawx5_vcap_es2_get_powt_ipv4_keysets(keysetwist,
							      vawue);
			bweak;
		}
	}

	if (w3_pwoto != ETH_P_AWP && w3_pwoto != ETH_P_IP &&
	    w3_pwoto != ETH_P_IPV6) {
		vcap_keyset_wist_add(keysetwist, VCAP_KFS_MAC_ETYPE);
	}
	wetuwn 0;
}

/* Get the powt keyset fow the vcap wookup */
int spawx5_vcap_get_powt_keyset(stwuct net_device *ndev,
				stwuct vcap_admin *admin,
				int cid,
				u16 w3_pwoto,
				stwuct vcap_keyset_wist *kswist)
{
	int wookup, eww = -EINVAW;
	stwuct spawx5_powt *powt;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		wookup = spawx5_vcap_is0_cid_to_wookup(cid);
		eww = spawx5_vcap_is0_get_powt_keysets(ndev, wookup, kswist,
						       w3_pwoto);
		bweak;
	case VCAP_TYPE_IS2:
		wookup = spawx5_vcap_is2_cid_to_wookup(cid);
		eww = spawx5_vcap_is2_get_powt_keysets(ndev, wookup, kswist,
						       w3_pwoto);
		bweak;
	case VCAP_TYPE_ES0:
		eww = spawx5_vcap_es0_get_powt_keysets(ndev, kswist, w3_pwoto);
		bweak;
	case VCAP_TYPE_ES2:
		wookup = spawx5_vcap_es2_cid_to_wookup(cid);
		eww = spawx5_vcap_es2_get_powt_keysets(ndev, wookup, kswist,
						       w3_pwoto);
		bweak;
	defauwt:
		powt = netdev_pwiv(ndev);
		spawx5_vcap_type_eww(powt->spawx5, admin, __func__);
		bweak;
	}
	wetuwn eww;
}

/* Check if the ethewtype is suppowted by the vcap powt cwassification */
boow spawx5_vcap_is_known_etype(stwuct vcap_admin *admin, u16 etype)
{
	const u16 *known_etypes;
	int size, idx;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		known_etypes = spawx5_vcap_is0_known_etypes;
		size = AWWAY_SIZE(spawx5_vcap_is0_known_etypes);
		bweak;
	case VCAP_TYPE_IS2:
		known_etypes = spawx5_vcap_is2_known_etypes;
		size = AWWAY_SIZE(spawx5_vcap_is2_known_etypes);
		bweak;
	case VCAP_TYPE_ES0:
		wetuwn twue;
	case VCAP_TYPE_ES2:
		known_etypes = spawx5_vcap_es2_known_etypes;
		size = AWWAY_SIZE(spawx5_vcap_es2_known_etypes);
		bweak;
	defauwt:
		wetuwn fawse;
	}
	fow (idx = 0; idx < size; ++idx)
		if (known_etypes[idx] == etype)
			wetuwn twue;
	wetuwn fawse;
}

/* API cawwback used fow vawidating a fiewd keyset (check the powt keysets) */
static enum vcap_keyfiewd_set
spawx5_vcap_vawidate_keyset(stwuct net_device *ndev,
			    stwuct vcap_admin *admin,
			    stwuct vcap_wuwe *wuwe,
			    stwuct vcap_keyset_wist *kswist,
			    u16 w3_pwoto)
{
	stwuct vcap_keyset_wist keysetwist = {};
	enum vcap_keyfiewd_set keysets[10] = {};
	stwuct spawx5_powt *powt;
	int idx, jdx, wookup;

	if (!kswist || kswist->cnt == 0)
		wetuwn VCAP_KFS_NO_VAWUE;

	keysetwist.max = AWWAY_SIZE(keysets);
	keysetwist.keysets = keysets;

	/* Get a wist of cuwwentwy configuwed keysets in the wookups */
	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		wookup = spawx5_vcap_is0_cid_to_wookup(wuwe->vcap_chain_id);
		spawx5_vcap_is0_get_powt_keysets(ndev, wookup, &keysetwist,
						 w3_pwoto);
		bweak;
	case VCAP_TYPE_IS2:
		wookup = spawx5_vcap_is2_cid_to_wookup(wuwe->vcap_chain_id);
		spawx5_vcap_is2_get_powt_keysets(ndev, wookup, &keysetwist,
						 w3_pwoto);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_get_powt_keysets(ndev, &keysetwist, w3_pwoto);
		bweak;
	case VCAP_TYPE_ES2:
		wookup = spawx5_vcap_es2_cid_to_wookup(wuwe->vcap_chain_id);
		spawx5_vcap_es2_get_powt_keysets(ndev, wookup, &keysetwist,
						 w3_pwoto);
		bweak;
	defauwt:
		powt = netdev_pwiv(ndev);
		spawx5_vcap_type_eww(powt->spawx5, admin, __func__);
		bweak;
	}

	/* Check if thewe is a match and wetuwn the match */
	fow (idx = 0; idx < kswist->cnt; ++idx)
		fow (jdx = 0; jdx < keysetwist.cnt; ++jdx)
			if (kswist->keysets[idx] == keysets[jdx])
				wetuwn kswist->keysets[idx];

	pw_eww("%s:%d: %s not suppowted in powt key sewection\n",
	       __func__, __WINE__,
	       spawx5_vcap_keyset_name(ndev, kswist->keysets[0]));

	wetuwn -ENOENT;
}

static void spawx5_vcap_ingwess_add_defauwt_fiewds(stwuct net_device *ndev,
						   stwuct vcap_admin *admin,
						   stwuct vcap_wuwe *wuwe)
{
	const stwuct vcap_fiewd *fiewd;
	boow is_fiwst;

	/* Add ingwess powt mask matching the net device */
	fiewd = vcap_wookup_keyfiewd(wuwe, VCAP_KF_IF_IGW_POWT_MASK);
	if (fiewd && fiewd->width == SPX5_POWTS)
		spawx5_vcap_add_wide_powt_mask(wuwe, ndev);
	ewse if (fiewd && fiewd->width == BITS_PEW_TYPE(u32))
		spawx5_vcap_add_ingwess_wange_powt_mask(wuwe, ndev);
	ewse
		pw_eww("%s:%d: %s: couwd not add an ingwess powt mask fow: %s\n",
		       __func__, __WINE__, netdev_name(ndev),
		       spawx5_vcap_keyset_name(ndev, wuwe->keyset));

	if (admin->vtype == VCAP_TYPE_IS0)
		is_fiwst = spawx5_vcap_is0_is_fiwst_chain(wuwe);
	ewse
		is_fiwst = spawx5_vcap_is2_is_fiwst_chain(wuwe);

	/* Add key that sewects the fiwst/second wookup */
	if (is_fiwst)
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_1);
	ewse
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_0);
}

static void spawx5_vcap_es0_add_defauwt_fiewds(stwuct net_device *ndev,
					       stwuct vcap_admin *admin,
					       stwuct vcap_wuwe *wuwe)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);

	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_IF_EGW_POWT_NO, powt->powtno, ~0);
	/* Match untagged fwames if thewe was no VWAN key */
	vcap_wuwe_add_key_u32(wuwe, VCAP_KF_8021Q_TPID, SPX5_TPID_SEW_UNTAGGED,
			      ~0);
}

static void spawx5_vcap_es2_add_defauwt_fiewds(stwuct net_device *ndev,
					       stwuct vcap_admin *admin,
					       stwuct vcap_wuwe *wuwe)
{
	const stwuct vcap_fiewd *fiewd;
	boow is_fiwst;

	/* Add egwess powt mask matching the net device */
	fiewd = vcap_wookup_keyfiewd(wuwe, VCAP_KF_IF_EGW_POWT_MASK);
	if (fiewd)
		spawx5_vcap_add_egwess_wange_powt_mask(wuwe, ndev);

	/* Add key that sewects the fiwst/second wookup */
	is_fiwst = spawx5_vcap_es2_is_fiwst_chain(wuwe);

	if (is_fiwst)
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_1);
	ewse
		vcap_wuwe_add_key_bit(wuwe, VCAP_KF_WOOKUP_FIWST_IS,
				      VCAP_BIT_0);
}

/* API cawwback used fow adding defauwt fiewds to a wuwe */
static void spawx5_vcap_add_defauwt_fiewds(stwuct net_device *ndev,
					   stwuct vcap_admin *admin,
					   stwuct vcap_wuwe *wuwe)
{
	stwuct spawx5_powt *powt;

	/* add the wookup bit */
	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
	case VCAP_TYPE_IS2:
		spawx5_vcap_ingwess_add_defauwt_fiewds(ndev, admin, wuwe);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_add_defauwt_fiewds(ndev, admin, wuwe);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_add_defauwt_fiewds(ndev, admin, wuwe);
		bweak;
	defauwt:
		powt = netdev_pwiv(ndev);
		spawx5_vcap_type_eww(powt->spawx5, admin, __func__);
		bweak;
	}
}

/* API cawwback used fow ewasing the vcap cache awea (not the wegistew awea) */
static void spawx5_vcap_cache_ewase(stwuct vcap_admin *admin)
{
	memset(admin->cache.keystweam, 0, STWEAMSIZE);
	memset(admin->cache.maskstweam, 0, STWEAMSIZE);
	memset(admin->cache.actionstweam, 0, STWEAMSIZE);
	memset(&admin->cache.countew, 0, sizeof(admin->cache.countew));
}

static void spawx5_vcap_is0_cache_wwite(stwuct spawx5 *spawx5,
					stwuct vcap_admin *admin,
					enum vcap_sewection sew,
					u32 stawt,
					u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	switch (sew) {
	case VCAP_SEW_ENTWY:
		fow (idx = 0; idx < count; ++idx) {
			/* Avoid 'match-off' by setting vawue & mask */
			spx5_ww(keystw[idx] & mskstw[idx], spawx5,
				VCAP_SUPEW_VCAP_ENTWY_DAT(idx));
			spx5_ww(~mskstw[idx], spawx5,
				VCAP_SUPEW_VCAP_MASK_DAT(idx));
		}
		bweak;
	case VCAP_SEW_ACTION:
		fow (idx = 0; idx < count; ++idx)
			spx5_ww(actstw[idx], spawx5,
				VCAP_SUPEW_VCAP_ACTION_DAT(idx));
		bweak;
	case VCAP_SEW_AWW:
		pw_eww("%s:%d: cannot wwite aww stweams at once\n",
		       __func__, __WINE__);
		bweak;
	defauwt:
		bweak;
	}

	if (sew & VCAP_SEW_COUNTEW)
		spx5_ww(admin->cache.countew, spawx5,
			VCAP_SUPEW_VCAP_CNT_DAT(0));
}

static void spawx5_vcap_is2_cache_wwite(stwuct spawx5 *spawx5,
					stwuct vcap_admin *admin,
					enum vcap_sewection sew,
					u32 stawt,
					u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	switch (sew) {
	case VCAP_SEW_ENTWY:
		fow (idx = 0; idx < count; ++idx) {
			/* Avoid 'match-off' by setting vawue & mask */
			spx5_ww(keystw[idx] & mskstw[idx], spawx5,
				VCAP_SUPEW_VCAP_ENTWY_DAT(idx));
			spx5_ww(~mskstw[idx], spawx5,
				VCAP_SUPEW_VCAP_MASK_DAT(idx));
		}
		bweak;
	case VCAP_SEW_ACTION:
		fow (idx = 0; idx < count; ++idx)
			spx5_ww(actstw[idx], spawx5,
				VCAP_SUPEW_VCAP_ACTION_DAT(idx));
		bweak;
	case VCAP_SEW_AWW:
		pw_eww("%s:%d: cannot wwite aww stweams at once\n",
		       __func__, __WINE__);
		bweak;
	defauwt:
		bweak;
	}
	if (sew & VCAP_SEW_COUNTEW) {
		stawt = stawt & 0xfff; /* countew wimit */
		if (admin->vinst == 0)
			spx5_ww(admin->cache.countew, spawx5,
				ANA_ACW_CNT_A(stawt));
		ewse
			spx5_ww(admin->cache.countew, spawx5,
				ANA_ACW_CNT_B(stawt));
		spx5_ww(admin->cache.sticky, spawx5,
			VCAP_SUPEW_VCAP_CNT_DAT(0));
	}
}

/* Use ESDX countews wocated in the XQS */
static void spawx5_es0_wwite_esdx_countew(stwuct spawx5 *spawx5,
					  stwuct vcap_admin *admin, u32 id)
{
	mutex_wock(&spawx5->queue_stats_wock);
	spx5_ww(XQS_STAT_CFG_STAT_VIEW_SET(id), spawx5, XQS_STAT_CFG);
	spx5_ww(admin->cache.countew, spawx5,
		XQS_CNT(SPAWX5_STAT_ESDX_GWN_PKTS));
	spx5_ww(0, spawx5, XQS_CNT(SPAWX5_STAT_ESDX_YEW_PKTS));
	mutex_unwock(&spawx5->queue_stats_wock);
}

static void spawx5_vcap_es0_cache_wwite(stwuct spawx5 *spawx5,
					stwuct vcap_admin *admin,
					enum vcap_sewection sew,
					u32 stawt,
					u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	switch (sew) {
	case VCAP_SEW_ENTWY:
		fow (idx = 0; idx < count; ++idx) {
			/* Avoid 'match-off' by setting vawue & mask */
			spx5_ww(keystw[idx] & mskstw[idx], spawx5,
				VCAP_ES0_VCAP_ENTWY_DAT(idx));
			spx5_ww(~mskstw[idx], spawx5,
				VCAP_ES0_VCAP_MASK_DAT(idx));
		}
		bweak;
	case VCAP_SEW_ACTION:
		fow (idx = 0; idx < count; ++idx)
			spx5_ww(actstw[idx], spawx5,
				VCAP_ES0_VCAP_ACTION_DAT(idx));
		bweak;
	case VCAP_SEW_AWW:
		pw_eww("%s:%d: cannot wwite aww stweams at once\n",
		       __func__, __WINE__);
		bweak;
	defauwt:
		bweak;
	}
	if (sew & VCAP_SEW_COUNTEW) {
		spx5_ww(admin->cache.countew, spawx5, VCAP_ES0_VCAP_CNT_DAT(0));
		spawx5_es0_wwite_esdx_countew(spawx5, admin, stawt);
	}
}

static void spawx5_vcap_es2_cache_wwite(stwuct spawx5 *spawx5,
					stwuct vcap_admin *admin,
					enum vcap_sewection sew,
					u32 stawt,
					u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	switch (sew) {
	case VCAP_SEW_ENTWY:
		fow (idx = 0; idx < count; ++idx) {
			/* Avoid 'match-off' by setting vawue & mask */
			spx5_ww(keystw[idx] & mskstw[idx], spawx5,
				VCAP_ES2_VCAP_ENTWY_DAT(idx));
			spx5_ww(~mskstw[idx], spawx5,
				VCAP_ES2_VCAP_MASK_DAT(idx));
		}
		bweak;
	case VCAP_SEW_ACTION:
		fow (idx = 0; idx < count; ++idx)
			spx5_ww(actstw[idx], spawx5,
				VCAP_ES2_VCAP_ACTION_DAT(idx));
		bweak;
	case VCAP_SEW_AWW:
		pw_eww("%s:%d: cannot wwite aww stweams at once\n",
		       __func__, __WINE__);
		bweak;
	defauwt:
		bweak;
	}
	if (sew & VCAP_SEW_COUNTEW) {
		stawt = stawt & 0x7ff; /* countew wimit */
		spx5_ww(admin->cache.countew, spawx5, EACW_ES2_CNT(stawt));
		spx5_ww(admin->cache.sticky, spawx5, VCAP_ES2_VCAP_CNT_DAT(0));
	}
}

/* API cawwback used fow wwiting to the VCAP cache */
static void spawx5_vcap_cache_wwite(stwuct net_device *ndev,
				    stwuct vcap_admin *admin,
				    enum vcap_sewection sew,
				    u32 stawt,
				    u32 count)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		spawx5_vcap_is0_cache_wwite(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_IS2:
		spawx5_vcap_is2_cache_wwite(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_cache_wwite(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_cache_wwite(spawx5, admin, sew, stawt, count);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

static void spawx5_vcap_is0_cache_wead(stwuct spawx5 *spawx5,
				       stwuct vcap_admin *admin,
				       enum vcap_sewection sew,
				       u32 stawt,
				       u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	if (sew & VCAP_SEW_ENTWY) {
		fow (idx = 0; idx < count; ++idx) {
			keystw[idx] = spx5_wd(spawx5,
					      VCAP_SUPEW_VCAP_ENTWY_DAT(idx));
			mskstw[idx] = ~spx5_wd(spawx5,
					       VCAP_SUPEW_VCAP_MASK_DAT(idx));
		}
	}

	if (sew & VCAP_SEW_ACTION)
		fow (idx = 0; idx < count; ++idx)
			actstw[idx] = spx5_wd(spawx5,
					      VCAP_SUPEW_VCAP_ACTION_DAT(idx));

	if (sew & VCAP_SEW_COUNTEW) {
		admin->cache.countew =
			spx5_wd(spawx5, VCAP_SUPEW_VCAP_CNT_DAT(0));
		admin->cache.sticky =
			spx5_wd(spawx5, VCAP_SUPEW_VCAP_CNT_DAT(0));
	}
}

static void spawx5_vcap_is2_cache_wead(stwuct spawx5 *spawx5,
				       stwuct vcap_admin *admin,
				       enum vcap_sewection sew,
				       u32 stawt,
				       u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	if (sew & VCAP_SEW_ENTWY) {
		fow (idx = 0; idx < count; ++idx) {
			keystw[idx] = spx5_wd(spawx5,
					      VCAP_SUPEW_VCAP_ENTWY_DAT(idx));
			mskstw[idx] = ~spx5_wd(spawx5,
					       VCAP_SUPEW_VCAP_MASK_DAT(idx));
		}
	}

	if (sew & VCAP_SEW_ACTION)
		fow (idx = 0; idx < count; ++idx)
			actstw[idx] = spx5_wd(spawx5,
					      VCAP_SUPEW_VCAP_ACTION_DAT(idx));

	if (sew & VCAP_SEW_COUNTEW) {
		stawt = stawt & 0xfff; /* countew wimit */
		if (admin->vinst == 0)
			admin->cache.countew =
				spx5_wd(spawx5, ANA_ACW_CNT_A(stawt));
		ewse
			admin->cache.countew =
				spx5_wd(spawx5, ANA_ACW_CNT_B(stawt));
		admin->cache.sticky =
			spx5_wd(spawx5, VCAP_SUPEW_VCAP_CNT_DAT(0));
	}
}

/* Use ESDX countews wocated in the XQS */
static void spawx5_es0_wead_esdx_countew(stwuct spawx5 *spawx5,
					 stwuct vcap_admin *admin, u32 id)
{
	u32 countew;

	mutex_wock(&spawx5->queue_stats_wock);
	spx5_ww(XQS_STAT_CFG_STAT_VIEW_SET(id), spawx5, XQS_STAT_CFG);
	countew = spx5_wd(spawx5, XQS_CNT(SPAWX5_STAT_ESDX_GWN_PKTS)) +
		spx5_wd(spawx5, XQS_CNT(SPAWX5_STAT_ESDX_YEW_PKTS));
	mutex_unwock(&spawx5->queue_stats_wock);
	if (countew)
		admin->cache.countew = countew;
}

static void spawx5_vcap_es0_cache_wead(stwuct spawx5 *spawx5,
				       stwuct vcap_admin *admin,
				       enum vcap_sewection sew,
				       u32 stawt,
				       u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	if (sew & VCAP_SEW_ENTWY) {
		fow (idx = 0; idx < count; ++idx) {
			keystw[idx] =
				spx5_wd(spawx5, VCAP_ES0_VCAP_ENTWY_DAT(idx));
			mskstw[idx] =
				~spx5_wd(spawx5, VCAP_ES0_VCAP_MASK_DAT(idx));
		}
	}

	if (sew & VCAP_SEW_ACTION)
		fow (idx = 0; idx < count; ++idx)
			actstw[idx] =
				spx5_wd(spawx5, VCAP_ES0_VCAP_ACTION_DAT(idx));

	if (sew & VCAP_SEW_COUNTEW) {
		admin->cache.countew =
			spx5_wd(spawx5, VCAP_ES0_VCAP_CNT_DAT(0));
		admin->cache.sticky = admin->cache.countew;
		spawx5_es0_wead_esdx_countew(spawx5, admin, stawt);
	}
}

static void spawx5_vcap_es2_cache_wead(stwuct spawx5 *spawx5,
				       stwuct vcap_admin *admin,
				       enum vcap_sewection sew,
				       u32 stawt,
				       u32 count)
{
	u32 *keystw, *mskstw, *actstw;
	int idx;

	keystw = &admin->cache.keystweam[stawt];
	mskstw = &admin->cache.maskstweam[stawt];
	actstw = &admin->cache.actionstweam[stawt];

	if (sew & VCAP_SEW_ENTWY) {
		fow (idx = 0; idx < count; ++idx) {
			keystw[idx] =
				spx5_wd(spawx5, VCAP_ES2_VCAP_ENTWY_DAT(idx));
			mskstw[idx] =
				~spx5_wd(spawx5, VCAP_ES2_VCAP_MASK_DAT(idx));
		}
	}

	if (sew & VCAP_SEW_ACTION)
		fow (idx = 0; idx < count; ++idx)
			actstw[idx] =
				spx5_wd(spawx5, VCAP_ES2_VCAP_ACTION_DAT(idx));

	if (sew & VCAP_SEW_COUNTEW) {
		stawt = stawt & 0x7ff; /* countew wimit */
		admin->cache.countew =
			spx5_wd(spawx5, EACW_ES2_CNT(stawt));
		admin->cache.sticky =
			spx5_wd(spawx5, VCAP_ES2_VCAP_CNT_DAT(0));
	}
}

/* API cawwback used fow weading fwom the VCAP into the VCAP cache */
static void spawx5_vcap_cache_wead(stwuct net_device *ndev,
				   stwuct vcap_admin *admin,
				   enum vcap_sewection sew,
				   u32 stawt,
				   u32 count)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		spawx5_vcap_is0_cache_wead(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_IS2:
		spawx5_vcap_is2_cache_wead(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_cache_wead(spawx5, admin, sew, stawt, count);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_cache_wead(spawx5, admin, sew, stawt, count);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

/* API cawwback used fow initiawizing a VCAP addwess wange */
static void spawx5_vcap_wange_init(stwuct net_device *ndev,
				   stwuct vcap_admin *admin, u32 addw,
				   u32 count)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	_spawx5_vcap_wange_init(spawx5, admin, addw, count);
}

static void spawx5_vcap_supew_update(stwuct spawx5 *spawx5,
				     enum vcap_command cmd,
				     enum vcap_sewection sew, u32 addw)
{
	boow cweaw = (cmd == VCAP_CMD_INITIAWIZE);

	spx5_ww(VCAP_SUPEW_CFG_MV_NUM_POS_SET(0) |
		VCAP_SUPEW_CFG_MV_SIZE_SET(0), spawx5, VCAP_SUPEW_CFG);
	spx5_ww(VCAP_SUPEW_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_SUPEW_CTWW_UPDATE_ENTWY_DIS_SET((VCAP_SEW_ENTWY & sew) == 0) |
		VCAP_SUPEW_CTWW_UPDATE_ACTION_DIS_SET((VCAP_SEW_ACTION & sew) == 0) |
		VCAP_SUPEW_CTWW_UPDATE_CNT_DIS_SET((VCAP_SEW_COUNTEW & sew) == 0) |
		VCAP_SUPEW_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_SUPEW_CTWW_CWEAW_CACHE_SET(cweaw) |
		VCAP_SUPEW_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_SUPEW_CTWW);
	spawx5_vcap_wait_supew_update(spawx5);
}

static void spawx5_vcap_es0_update(stwuct spawx5 *spawx5,
				   enum vcap_command cmd,
				   enum vcap_sewection sew, u32 addw)
{
	boow cweaw = (cmd == VCAP_CMD_INITIAWIZE);

	spx5_ww(VCAP_ES0_CFG_MV_NUM_POS_SET(0) |
		VCAP_ES0_CFG_MV_SIZE_SET(0), spawx5, VCAP_ES0_CFG);
	spx5_ww(VCAP_ES0_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_ES0_CTWW_UPDATE_ENTWY_DIS_SET((VCAP_SEW_ENTWY & sew) == 0) |
		VCAP_ES0_CTWW_UPDATE_ACTION_DIS_SET((VCAP_SEW_ACTION & sew) == 0) |
		VCAP_ES0_CTWW_UPDATE_CNT_DIS_SET((VCAP_SEW_COUNTEW & sew) == 0) |
		VCAP_ES0_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_ES0_CTWW_CWEAW_CACHE_SET(cweaw) |
		VCAP_ES0_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_ES0_CTWW);
	spawx5_vcap_wait_es0_update(spawx5);
}

static void spawx5_vcap_es2_update(stwuct spawx5 *spawx5,
				   enum vcap_command cmd,
				   enum vcap_sewection sew, u32 addw)
{
	boow cweaw = (cmd == VCAP_CMD_INITIAWIZE);

	spx5_ww(VCAP_ES2_CFG_MV_NUM_POS_SET(0) |
		VCAP_ES2_CFG_MV_SIZE_SET(0), spawx5, VCAP_ES2_CFG);
	spx5_ww(VCAP_ES2_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_ES2_CTWW_UPDATE_ENTWY_DIS_SET((VCAP_SEW_ENTWY & sew) == 0) |
		VCAP_ES2_CTWW_UPDATE_ACTION_DIS_SET((VCAP_SEW_ACTION & sew) == 0) |
		VCAP_ES2_CTWW_UPDATE_CNT_DIS_SET((VCAP_SEW_COUNTEW & sew) == 0) |
		VCAP_ES2_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_ES2_CTWW_CWEAW_CACHE_SET(cweaw) |
		VCAP_ES2_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_ES2_CTWW);
	spawx5_vcap_wait_es2_update(spawx5);
}

/* API cawwback used fow updating the VCAP cache */
static void spawx5_vcap_update(stwuct net_device *ndev,
			       stwuct vcap_admin *admin, enum vcap_command cmd,
			       enum vcap_sewection sew, u32 addw)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
	case VCAP_TYPE_IS2:
		spawx5_vcap_supew_update(spawx5, cmd, sew, addw);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_update(spawx5, cmd, sew, addw);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_update(spawx5, cmd, sew, addw);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

static void spawx5_vcap_supew_move(stwuct spawx5 *spawx5,
				   u32 addw,
				   enum vcap_command cmd,
				   u16 mv_num_pos,
				   u16 mv_size)
{
	spx5_ww(VCAP_SUPEW_CFG_MV_NUM_POS_SET(mv_num_pos) |
		VCAP_SUPEW_CFG_MV_SIZE_SET(mv_size),
		spawx5, VCAP_SUPEW_CFG);
	spx5_ww(VCAP_SUPEW_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_SUPEW_CTWW_UPDATE_ENTWY_DIS_SET(0) |
		VCAP_SUPEW_CTWW_UPDATE_ACTION_DIS_SET(0) |
		VCAP_SUPEW_CTWW_UPDATE_CNT_DIS_SET(0) |
		VCAP_SUPEW_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_SUPEW_CTWW_CWEAW_CACHE_SET(fawse) |
		VCAP_SUPEW_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_SUPEW_CTWW);
	spawx5_vcap_wait_supew_update(spawx5);
}

static void spawx5_vcap_es0_move(stwuct spawx5 *spawx5,
				 u32 addw,
				 enum vcap_command cmd,
				 u16 mv_num_pos,
				 u16 mv_size)
{
	spx5_ww(VCAP_ES0_CFG_MV_NUM_POS_SET(mv_num_pos) |
		VCAP_ES0_CFG_MV_SIZE_SET(mv_size),
		spawx5, VCAP_ES0_CFG);
	spx5_ww(VCAP_ES0_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_ES0_CTWW_UPDATE_ENTWY_DIS_SET(0) |
		VCAP_ES0_CTWW_UPDATE_ACTION_DIS_SET(0) |
		VCAP_ES0_CTWW_UPDATE_CNT_DIS_SET(0) |
		VCAP_ES0_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_ES0_CTWW_CWEAW_CACHE_SET(fawse) |
		VCAP_ES0_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_ES0_CTWW);
	spawx5_vcap_wait_es0_update(spawx5);
}

static void spawx5_vcap_es2_move(stwuct spawx5 *spawx5,
				 u32 addw,
				 enum vcap_command cmd,
				 u16 mv_num_pos,
				 u16 mv_size)
{
	spx5_ww(VCAP_ES2_CFG_MV_NUM_POS_SET(mv_num_pos) |
		VCAP_ES2_CFG_MV_SIZE_SET(mv_size),
		spawx5, VCAP_ES2_CFG);
	spx5_ww(VCAP_ES2_CTWW_UPDATE_CMD_SET(cmd) |
		VCAP_ES2_CTWW_UPDATE_ENTWY_DIS_SET(0) |
		VCAP_ES2_CTWW_UPDATE_ACTION_DIS_SET(0) |
		VCAP_ES2_CTWW_UPDATE_CNT_DIS_SET(0) |
		VCAP_ES2_CTWW_UPDATE_ADDW_SET(addw) |
		VCAP_ES2_CTWW_CWEAW_CACHE_SET(fawse) |
		VCAP_ES2_CTWW_UPDATE_SHOT_SET(twue),
		spawx5, VCAP_ES2_CTWW);
	spawx5_vcap_wait_es2_update(spawx5);
}

/* API cawwback used fow moving a bwock of wuwes in the VCAP */
static void spawx5_vcap_move(stwuct net_device *ndev, stwuct vcap_admin *admin,
			     u32 addw, int offset, int count)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
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

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
	case VCAP_TYPE_IS2:
		spawx5_vcap_supew_move(spawx5, addw, cmd, mv_num_pos, mv_size);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_move(spawx5, addw, cmd, mv_num_pos, mv_size);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_move(spawx5, addw, cmd, mv_num_pos, mv_size);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

static stwuct vcap_opewations spawx5_vcap_ops = {
	.vawidate_keyset = spawx5_vcap_vawidate_keyset,
	.add_defauwt_fiewds = spawx5_vcap_add_defauwt_fiewds,
	.cache_ewase = spawx5_vcap_cache_ewase,
	.cache_wwite = spawx5_vcap_cache_wwite,
	.cache_wead = spawx5_vcap_cache_wead,
	.init = spawx5_vcap_wange_init,
	.update = spawx5_vcap_update,
	.move = spawx5_vcap_move,
	.powt_info = spawx5_powt_info,
};

static u32 spawx5_vcap_is0_keyset_to_etype_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_NOWMAW_7TUPWE:
		wetuwn VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE;
	case VCAP_KFS_NOWMAW_5TUPWE_IP4:
		wetuwn VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4;
	defauwt:
		wetuwn VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE;
	}
}

static void spawx5_vcap_is0_set_powt_keyset(stwuct net_device *ndev, int wookup,
					    enum vcap_keyfiewd_set keyset,
					    int w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	switch (w3_pwoto) {
	case ETH_P_IP:
		vawue = spawx5_vcap_is0_keyset_to_etype_ps(keyset);
		spx5_wmw(ANA_CW_ADV_CW_CFG_IP4_CWM_KEY_SEW_SET(vawue),
			 ANA_CW_ADV_CW_CFG_IP4_CWM_KEY_SEW,
			 spawx5,
			 ANA_CW_ADV_CW_CFG(powtno, wookup));
		bweak;
	case ETH_P_IPV6:
		vawue = spawx5_vcap_is0_keyset_to_etype_ps(keyset);
		spx5_wmw(ANA_CW_ADV_CW_CFG_IP6_CWM_KEY_SEW_SET(vawue),
			 ANA_CW_ADV_CW_CFG_IP6_CWM_KEY_SEW,
			 spawx5,
			 ANA_CW_ADV_CW_CFG(powtno, wookup));
		bweak;
	defauwt:
		vawue = spawx5_vcap_is0_keyset_to_etype_ps(keyset);
		spx5_wmw(ANA_CW_ADV_CW_CFG_ETYPE_CWM_KEY_SEW_SET(vawue),
			 ANA_CW_ADV_CW_CFG_ETYPE_CWM_KEY_SEW,
			 spawx5,
			 ANA_CW_ADV_CW_CFG(powtno, wookup));
		bweak;
	}
}

static u32 spawx5_vcap_is2_keyset_to_awp_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_AWP:
		wetuwn VCAP_IS2_PS_AWP_AWP;
	defauwt:
		wetuwn VCAP_IS2_PS_AWP_MAC_ETYPE;
	}
}

static u32 spawx5_vcap_is2_keyset_to_ipv4_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_MAC_ETYPE:
		wetuwn VCAP_IS2_PS_IPV4_UC_MAC_ETYPE;
	case VCAP_KFS_IP4_OTHEW:
	case VCAP_KFS_IP4_TCP_UDP:
		wetuwn VCAP_IS2_PS_IPV4_UC_IP4_TCP_UDP_OTHEW;
	case VCAP_KFS_IP_7TUPWE:
		wetuwn VCAP_IS2_PS_IPV4_UC_IP_7TUPWE;
	defauwt:
		wetuwn VCAP_KFS_NO_VAWUE;
	}
}

static u32 spawx5_vcap_is2_keyset_to_ipv6_uc_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_MAC_ETYPE:
		wetuwn VCAP_IS2_PS_IPV6_UC_MAC_ETYPE;
	case VCAP_KFS_IP4_OTHEW:
	case VCAP_KFS_IP4_TCP_UDP:
		wetuwn VCAP_IS2_PS_IPV6_UC_IP4_TCP_UDP_OTHEW;
	case VCAP_KFS_IP_7TUPWE:
		wetuwn VCAP_IS2_PS_IPV6_UC_IP_7TUPWE;
	defauwt:
		wetuwn VCAP_KFS_NO_VAWUE;
	}
}

static u32 spawx5_vcap_is2_keyset_to_ipv6_mc_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_MAC_ETYPE:
		wetuwn VCAP_IS2_PS_IPV6_MC_MAC_ETYPE;
	case VCAP_KFS_IP4_OTHEW:
	case VCAP_KFS_IP4_TCP_UDP:
		wetuwn VCAP_IS2_PS_IPV6_MC_IP4_TCP_UDP_OTHEW;
	case VCAP_KFS_IP_7TUPWE:
		wetuwn VCAP_IS2_PS_IPV6_MC_IP_7TUPWE;
	defauwt:
		wetuwn VCAP_KFS_NO_VAWUE;
	}
}

static void spawx5_vcap_is2_set_powt_keyset(stwuct net_device *ndev, int wookup,
					    enum vcap_keyfiewd_set keyset,
					    int w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	switch (w3_pwoto) {
	case ETH_P_AWP:
		vawue = spawx5_vcap_is2_keyset_to_awp_ps(keyset);
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_AWP_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_AWP_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		bweak;
	case ETH_P_IP:
		vawue = spawx5_vcap_is2_keyset_to_ipv4_ps(keyset);
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_IP4_UC_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_IP4_UC_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_IP4_MC_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_IP4_MC_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		bweak;
	case ETH_P_IPV6:
		vawue = spawx5_vcap_is2_keyset_to_ipv6_uc_ps(keyset);
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_IP6_UC_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_IP6_UC_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		vawue = spawx5_vcap_is2_keyset_to_ipv6_mc_ps(keyset);
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_IP6_MC_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_IP6_MC_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		bweak;
	defauwt:
		vawue = VCAP_IS2_PS_NONETH_MAC_ETYPE;
		spx5_wmw(ANA_ACW_VCAP_S2_KEY_SEW_NON_ETH_KEY_SEW_SET(vawue),
			 ANA_ACW_VCAP_S2_KEY_SEW_NON_ETH_KEY_SEW,
			 spawx5,
			 ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		bweak;
	}
}

static u32 spawx5_vcap_es2_keyset_to_awp_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_AWP:
		wetuwn VCAP_ES2_PS_AWP_AWP;
	defauwt:
		wetuwn VCAP_ES2_PS_AWP_MAC_ETYPE;
	}
}

static u32 spawx5_vcap_es2_keyset_to_ipv4_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_MAC_ETYPE:
		wetuwn VCAP_ES2_PS_IPV4_MAC_ETYPE;
	case VCAP_KFS_IP_7TUPWE:
		wetuwn VCAP_ES2_PS_IPV4_IP_7TUPWE;
	case VCAP_KFS_IP4_TCP_UDP:
		wetuwn VCAP_ES2_PS_IPV4_IP4_TCP_UDP_OTHEW;
	case VCAP_KFS_IP4_OTHEW:
		wetuwn VCAP_ES2_PS_IPV4_IP4_OTHEW;
	defauwt:
		wetuwn VCAP_ES2_PS_IPV4_MAC_ETYPE;
	}
}

static u32 spawx5_vcap_es2_keyset_to_ipv6_ps(enum vcap_keyfiewd_set keyset)
{
	switch (keyset) {
	case VCAP_KFS_MAC_ETYPE:
		wetuwn VCAP_ES2_PS_IPV6_MAC_ETYPE;
	case VCAP_KFS_IP4_TCP_UDP:
	case VCAP_KFS_IP4_OTHEW:
		wetuwn VCAP_ES2_PS_IPV6_IP4_DOWNGWADE;
	case VCAP_KFS_IP_7TUPWE:
		wetuwn VCAP_ES2_PS_IPV6_IP_7TUPWE;
	case VCAP_KFS_IP6_STD:
		wetuwn VCAP_ES2_PS_IPV6_IP6_STD;
	defauwt:
		wetuwn VCAP_ES2_PS_IPV6_MAC_ETYPE;
	}
}

static void spawx5_vcap_es2_set_powt_keyset(stwuct net_device *ndev, int wookup,
					    enum vcap_keyfiewd_set keyset,
					    int w3_pwoto)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	u32 vawue;

	switch (w3_pwoto) {
	case ETH_P_IP:
		vawue = spawx5_vcap_es2_keyset_to_ipv4_ps(keyset);
		spx5_wmw(EACW_VCAP_ES2_KEY_SEW_IP4_KEY_SEW_SET(vawue),
			 EACW_VCAP_ES2_KEY_SEW_IP4_KEY_SEW,
			 spawx5,
			 EACW_VCAP_ES2_KEY_SEW(powtno, wookup));
		bweak;
	case ETH_P_IPV6:
		vawue = spawx5_vcap_es2_keyset_to_ipv6_ps(keyset);
		spx5_wmw(EACW_VCAP_ES2_KEY_SEW_IP6_KEY_SEW_SET(vawue),
			 EACW_VCAP_ES2_KEY_SEW_IP6_KEY_SEW,
			 spawx5,
			 EACW_VCAP_ES2_KEY_SEW(powtno, wookup));
		bweak;
	case ETH_P_AWP:
		vawue = spawx5_vcap_es2_keyset_to_awp_ps(keyset);
		spx5_wmw(EACW_VCAP_ES2_KEY_SEW_AWP_KEY_SEW_SET(vawue),
			 EACW_VCAP_ES2_KEY_SEW_AWP_KEY_SEW,
			 spawx5,
			 EACW_VCAP_ES2_KEY_SEW(powtno, wookup));
		bweak;
	}
}

/* Change the powt keyset fow the wookup and pwotocow */
void spawx5_vcap_set_powt_keyset(stwuct net_device *ndev,
				 stwuct vcap_admin *admin,
				 int cid,
				 u16 w3_pwoto,
				 enum vcap_keyfiewd_set keyset,
				 stwuct vcap_keyset_wist *owig)
{
	stwuct spawx5_powt *powt;
	int wookup;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		wookup = spawx5_vcap_is0_cid_to_wookup(cid);
		if (owig)
			spawx5_vcap_is0_get_powt_keysets(ndev, wookup, owig,
							 w3_pwoto);
		spawx5_vcap_is0_set_powt_keyset(ndev, wookup, keyset, w3_pwoto);
		bweak;
	case VCAP_TYPE_IS2:
		wookup = spawx5_vcap_is2_cid_to_wookup(cid);
		if (owig)
			spawx5_vcap_is2_get_powt_keysets(ndev, wookup, owig,
							 w3_pwoto);
		spawx5_vcap_is2_set_powt_keyset(ndev, wookup, keyset, w3_pwoto);
		bweak;
	case VCAP_TYPE_ES0:
		bweak;
	case VCAP_TYPE_ES2:
		wookup = spawx5_vcap_es2_cid_to_wookup(cid);
		if (owig)
			spawx5_vcap_es2_get_powt_keysets(ndev, wookup, owig,
							 w3_pwoto);
		spawx5_vcap_es2_set_powt_keyset(ndev, wookup, keyset, w3_pwoto);
		bweak;
	defauwt:
		powt = netdev_pwiv(ndev);
		spawx5_vcap_type_eww(powt->spawx5, admin, __func__);
		bweak;
	}
}

/* Enabwe IS0 wookups pew powt and set the keyset genewation */
static void spawx5_vcap_is0_powt_key_sewection(stwuct spawx5 *spawx5,
					       stwuct vcap_admin *admin)
{
	int powtno, wookup;
	u32 keysew;

	keysew = VCAP_IS0_KEYSEW(fawse,
				 VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE,
				 VCAP_IS0_PS_ETYPE_NOWMAW_5TUPWE_IP4,
				 VCAP_IS0_PS_ETYPE_NOWMAW_7TUPWE,
				 VCAP_IS0_PS_MPWS_FOWWOW_ETYPE,
				 VCAP_IS0_PS_MPWS_FOWWOW_ETYPE,
				 VCAP_IS0_PS_MWBS_FOWWOW_ETYPE);
	fow (wookup = 0; wookup < admin->wookups; ++wookup) {
		fow (powtno = 0; powtno < SPX5_POWTS; ++powtno) {
			spx5_ww(keysew, spawx5,
				ANA_CW_ADV_CW_CFG(powtno, wookup));
			spx5_wmw(ANA_CW_ADV_CW_CFG_WOOKUP_ENA,
				 ANA_CW_ADV_CW_CFG_WOOKUP_ENA,
				 spawx5,
				 ANA_CW_ADV_CW_CFG(powtno, wookup));
		}
	}
}

/* Enabwe IS2 wookups pew powt and set the keyset genewation */
static void spawx5_vcap_is2_powt_key_sewection(stwuct spawx5 *spawx5,
					       stwuct vcap_admin *admin)
{
	int powtno, wookup;
	u32 keysew;

	keysew = VCAP_IS2_KEYSEW(twue, VCAP_IS2_PS_NONETH_MAC_ETYPE,
				 VCAP_IS2_PS_IPV4_MC_IP4_TCP_UDP_OTHEW,
				 VCAP_IS2_PS_IPV4_UC_IP4_TCP_UDP_OTHEW,
				 VCAP_IS2_PS_IPV6_MC_IP_7TUPWE,
				 VCAP_IS2_PS_IPV6_UC_IP_7TUPWE,
				 VCAP_IS2_PS_AWP_AWP);
	fow (wookup = 0; wookup < admin->wookups; ++wookup) {
		fow (powtno = 0; powtno < SPX5_POWTS; ++powtno) {
			spx5_ww(keysew, spawx5,
				ANA_ACW_VCAP_S2_KEY_SEW(powtno, wookup));
		}
	}
	/* IS2 wookups awe in bit 0:3 */
	fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
		spx5_wmw(ANA_ACW_VCAP_S2_CFG_SEC_ENA_SET(0xf),
			 ANA_ACW_VCAP_S2_CFG_SEC_ENA,
			 spawx5,
			 ANA_ACW_VCAP_S2_CFG(powtno));
}

/* Enabwe ES0 wookups pew powt and set the keyset genewation */
static void spawx5_vcap_es0_powt_key_sewection(stwuct spawx5 *spawx5,
					       stwuct vcap_admin *admin)
{
	int powtno;
	u32 keysew;

	keysew = VCAP_ES0_KEYSEW(VCAP_ES0_PS_FOWCE_ISDX_WOOKUPS);
	fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
		spx5_wmw(keysew, WEW_WTAG_ETAG_CTWW_ES0_ISDX_KEY_ENA,
			 spawx5, WEW_WTAG_ETAG_CTWW(powtno));

	spx5_wmw(WEW_ES0_CTWW_ES0_WU_ENA_SET(1), WEW_ES0_CTWW_ES0_WU_ENA,
		 spawx5, WEW_ES0_CTWW);
}

/* Enabwe ES2 wookups pew powt and set the keyset genewation */
static void spawx5_vcap_es2_powt_key_sewection(stwuct spawx5 *spawx5,
					       stwuct vcap_admin *admin)
{
	int powtno, wookup;
	u32 keysew;

	keysew = VCAP_ES2_KEYSEW(twue, VCAP_ES2_PS_AWP_MAC_ETYPE,
				 VCAP_ES2_PS_IPV4_IP4_TCP_UDP_OTHEW,
				 VCAP_ES2_PS_IPV6_IP_7TUPWE);
	fow (wookup = 0; wookup < admin->wookups; ++wookup)
		fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
			spx5_ww(keysew, spawx5,
				EACW_VCAP_ES2_KEY_SEW(powtno, wookup));
}

/* Enabwe wookups pew powt and set the keyset genewation */
static void spawx5_vcap_powt_key_sewection(stwuct spawx5 *spawx5,
					   stwuct vcap_admin *admin)
{
	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		spawx5_vcap_is0_powt_key_sewection(spawx5, admin);
		bweak;
	case VCAP_TYPE_IS2:
		spawx5_vcap_is2_powt_key_sewection(spawx5, admin);
		bweak;
	case VCAP_TYPE_ES0:
		spawx5_vcap_es0_powt_key_sewection(spawx5, admin);
		bweak;
	case VCAP_TYPE_ES2:
		spawx5_vcap_es2_powt_key_sewection(spawx5, admin);
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

/* Disabwe wookups pew powt */
static void spawx5_vcap_powt_key_desewection(stwuct spawx5 *spawx5,
					     stwuct vcap_admin *admin)
{
	int powtno, wookup;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		fow (wookup = 0; wookup < admin->wookups; ++wookup)
			fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
				spx5_wmw(ANA_CW_ADV_CW_CFG_WOOKUP_ENA_SET(0),
					 ANA_CW_ADV_CW_CFG_WOOKUP_ENA,
					 spawx5,
					 ANA_CW_ADV_CW_CFG(powtno, wookup));
		bweak;
	case VCAP_TYPE_IS2:
		fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
			spx5_wmw(ANA_ACW_VCAP_S2_CFG_SEC_ENA_SET(0),
				 ANA_ACW_VCAP_S2_CFG_SEC_ENA,
				 spawx5,
				 ANA_ACW_VCAP_S2_CFG(powtno));
		bweak;
	case VCAP_TYPE_ES0:
		spx5_wmw(WEW_ES0_CTWW_ES0_WU_ENA_SET(0),
			 WEW_ES0_CTWW_ES0_WU_ENA, spawx5, WEW_ES0_CTWW);
		bweak;
	case VCAP_TYPE_ES2:
		fow (wookup = 0; wookup < admin->wookups; ++wookup)
			fow (powtno = 0; powtno < SPX5_POWTS; ++powtno)
				spx5_wmw(EACW_VCAP_ES2_KEY_SEW_KEY_ENA_SET(0),
					 EACW_VCAP_ES2_KEY_SEW_KEY_ENA,
					 spawx5,
					 EACW_VCAP_ES2_KEY_SEW(powtno, wookup));
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

static void spawx5_vcap_admin_fwee(stwuct vcap_admin *admin)
{
	if (!admin)
		wetuwn;
	mutex_destwoy(&admin->wock);
	kfwee(admin->cache.keystweam);
	kfwee(admin->cache.maskstweam);
	kfwee(admin->cache.actionstweam);
	kfwee(admin);
}

/* Awwocate a vcap instance with a wuwe wist and a cache awea */
static stwuct vcap_admin *
spawx5_vcap_admin_awwoc(stwuct spawx5 *spawx5, stwuct vcap_contwow *ctww,
			const stwuct spawx5_vcap_inst *cfg)
{
	stwuct vcap_admin *admin;

	admin = kzawwoc(sizeof(*admin), GFP_KEWNEW);
	if (!admin)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&admin->wist);
	INIT_WIST_HEAD(&admin->wuwes);
	INIT_WIST_HEAD(&admin->enabwed);
	mutex_init(&admin->wock);
	admin->vtype = cfg->vtype;
	admin->vinst = cfg->vinst;
	admin->ingwess = cfg->ingwess;
	admin->wookups = cfg->wookups;
	admin->wookups_pew_instance = cfg->wookups_pew_instance;
	admin->fiwst_cid = cfg->fiwst_cid;
	admin->wast_cid = cfg->wast_cid;
	admin->cache.keystweam =
		kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	admin->cache.maskstweam =
		kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	admin->cache.actionstweam =
		kzawwoc(STWEAMSIZE, GFP_KEWNEW);
	if (!admin->cache.keystweam || !admin->cache.maskstweam ||
	    !admin->cache.actionstweam) {
		spawx5_vcap_admin_fwee(admin);
		wetuwn EWW_PTW(-ENOMEM);
	}
	wetuwn admin;
}

/* Do bwock awwocations and pwovide addwesses fow VCAP instances */
static void spawx5_vcap_bwock_awwoc(stwuct spawx5 *spawx5,
				    stwuct vcap_admin *admin,
				    const stwuct spawx5_vcap_inst *cfg)
{
	int idx, cowes;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
	case VCAP_TYPE_IS2:
		/* Supew VCAP bwock mapping and addwess configuwation. Bwock 0
		 * is assigned addwesses 0 thwough 3071, bwock 1 is assigned
		 * addwesses 3072 though 6143, and so on.
		 */
		fow (idx = cfg->bwockno; idx < cfg->bwockno + cfg->bwocks;
		     ++idx) {
			spx5_ww(VCAP_SUPEW_IDX_COWE_IDX_SET(idx), spawx5,
				VCAP_SUPEW_IDX);
			spx5_ww(VCAP_SUPEW_MAP_COWE_MAP_SET(cfg->map_id),
				spawx5, VCAP_SUPEW_MAP);
		}
		admin->fiwst_vawid_addw = cfg->bwockno * SUPEW_VCAP_BWK_SIZE;
		admin->wast_used_addw = admin->fiwst_vawid_addw +
			cfg->bwocks * SUPEW_VCAP_BWK_SIZE;
		admin->wast_vawid_addw = admin->wast_used_addw - 1;
		bweak;
	case VCAP_TYPE_ES0:
		admin->fiwst_vawid_addw = 0;
		admin->wast_used_addw = cfg->count;
		admin->wast_vawid_addw = cfg->count - 1;
		cowes = spx5_wd(spawx5, VCAP_ES0_COWE_CNT);
		fow (idx = 0; idx < cowes; ++idx) {
			spx5_ww(VCAP_ES0_IDX_COWE_IDX_SET(idx), spawx5,
				VCAP_ES0_IDX);
			spx5_ww(VCAP_ES0_MAP_COWE_MAP_SET(1), spawx5,
				VCAP_ES0_MAP);
		}
		bweak;
	case VCAP_TYPE_ES2:
		admin->fiwst_vawid_addw = 0;
		admin->wast_used_addw = cfg->count;
		admin->wast_vawid_addw = cfg->count - 1;
		cowes = spx5_wd(spawx5, VCAP_ES2_COWE_CNT);
		fow (idx = 0; idx < cowes; ++idx) {
			spx5_ww(VCAP_ES2_IDX_COWE_IDX_SET(idx), spawx5,
				VCAP_ES2_IDX);
			spx5_ww(VCAP_ES2_MAP_COWE_MAP_SET(1), spawx5,
				VCAP_ES2_MAP);
		}
		bweak;
	defauwt:
		spawx5_vcap_type_eww(spawx5, admin, __func__);
		bweak;
	}
}

/* Awwocate a vcap contwow and vcap instances and configuwe the system */
int spawx5_vcap_init(stwuct spawx5 *spawx5)
{
	const stwuct spawx5_vcap_inst *cfg;
	stwuct vcap_contwow *ctww;
	stwuct vcap_admin *admin;
	stwuct dentwy *diw;
	int eww = 0, idx;

	/* Cweate a VCAP contwow instance that owns the pwatfowm specific VCAP
	 * modew with VCAP instances and infowmation about keysets, keys,
	 * actionsets and actions
	 * - Cweate administwative state fow each avaiwabwe VCAP
	 *   - Wists of wuwes
	 *   - Addwess infowmation
	 *   - Initiawize VCAP bwocks
	 *   - Configuwe powt keysets
	 */
	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	spawx5->vcap_ctww = ctww;
	/* sewect the spawx5 VCAP modew */
	ctww->vcaps = spawx5_vcaps;
	ctww->stats = &spawx5_vcap_stats;
	/* Setup cawwbacks to awwow the API to use the VCAP HW */
	ctww->ops = &spawx5_vcap_ops;

	INIT_WIST_HEAD(&ctww->wist);
	fow (idx = 0; idx < AWWAY_SIZE(spawx5_vcap_inst_cfg); ++idx) {
		cfg = &spawx5_vcap_inst_cfg[idx];
		admin = spawx5_vcap_admin_awwoc(spawx5, ctww, cfg);
		if (IS_EWW(admin)) {
			eww = PTW_EWW(admin);
			pw_eww("%s:%d: vcap awwocation faiwed: %d\n",
			       __func__, __WINE__, eww);
			wetuwn eww;
		}
		spawx5_vcap_bwock_awwoc(spawx5, admin, cfg);
		spawx5_vcap_bwock_init(spawx5, admin);
		if (cfg->vinst == 0)
			spawx5_vcap_powt_key_sewection(spawx5, admin);
		wist_add_taiw(&admin->wist, &ctww->wist);
	}
	diw = vcap_debugfs(spawx5->dev, spawx5->debugfs_woot, ctww);
	fow (idx = 0; idx < SPX5_POWTS; ++idx)
		if (spawx5->powts[idx])
			vcap_powt_debugfs(spawx5->dev, diw, ctww,
					  spawx5->powts[idx]->ndev);

	wetuwn eww;
}

void spawx5_vcap_destwoy(stwuct spawx5 *spawx5)
{
	stwuct vcap_contwow *ctww = spawx5->vcap_ctww;
	stwuct vcap_admin *admin, *admin_next;

	if (!ctww)
		wetuwn;

	wist_fow_each_entwy_safe(admin, admin_next, &ctww->wist, wist) {
		spawx5_vcap_powt_key_desewection(spawx5, admin);
		vcap_dew_wuwes(ctww, admin);
		wist_dew(&admin->wist);
		spawx5_vcap_admin_fwee(admin);
	}
	kfwee(ctww);
}
