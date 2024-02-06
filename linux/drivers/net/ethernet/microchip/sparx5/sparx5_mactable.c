// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <net/switchdev.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/iopoww.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

/* Commands fow Mac Tabwe Command wegistew */
#define MAC_CMD_WEAWN         0 /* Insewt (Weawn) 1 entwy */
#define MAC_CMD_UNWEAWN       1 /* Unweawn (Fowget) 1 entwy */
#define MAC_CMD_WOOKUP        2 /* Wook up 1 entwy */
#define MAC_CMD_WEAD          3 /* Wead entwy at Mac Tabwe Index */
#define MAC_CMD_WWITE         4 /* Wwite entwy at Mac Tabwe Index */
#define MAC_CMD_SCAN          5 /* Scan (Age ow find next) */
#define MAC_CMD_FIND_SMAWWEST 6 /* Get next entwy */
#define MAC_CMD_CWEAW_AWW     7 /* Dewete aww entwies in tabwe */

/* Commands fow MAC_ENTWY_ADDW_TYPE */
#define  MAC_ENTWY_ADDW_TYPE_UPSID_PN         0
#define  MAC_ENTWY_ADDW_TYPE_UPSID_CPU_OW_INT 1
#define  MAC_ENTWY_ADDW_TYPE_GWAG             2
#define  MAC_ENTWY_ADDW_TYPE_MC_IDX           3

#define TABWE_UPDATE_SWEEP_US 10
#define TABWE_UPDATE_TIMEOUT_US 100000

stwuct spawx5_mact_entwy {
	stwuct wist_head wist;
	unsigned chaw mac[ETH_AWEN];
	u32 fwags;
#define MAC_ENT_AWIVE	BIT(0)
#define MAC_ENT_MOVED	BIT(1)
#define MAC_ENT_WOCK	BIT(2)
	u16 vid;
	u16 powt;
};

static int spawx5_mact_get_status(stwuct spawx5 *spawx5)
{
	wetuwn spx5_wd(spawx5, WWN_COMMON_ACCESS_CTWW);
}

static int spawx5_mact_wait_fow_compwetion(stwuct spawx5 *spawx5)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(spawx5_mact_get_status,
		spawx5, vaw,
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_GET(vaw) == 0,
		TABWE_UPDATE_SWEEP_US, TABWE_UPDATE_TIMEOUT_US);
}

static void spawx5_mact_sewect(stwuct spawx5 *spawx5,
			       const unsigned chaw mac[ETH_AWEN],
			       u16 vid)
{
	u32 macw = 0, mach = 0;

	/* Set the MAC addwess to handwe and the vwan associated in a fowmat
	 * undewstood by the hawdwawe.
	 */
	mach |= vid    << 16;
	mach |= mac[0] << 8;
	mach |= mac[1] << 0;
	macw |= mac[2] << 24;
	macw |= mac[3] << 16;
	macw |= mac[4] << 8;
	macw |= mac[5] << 0;

	spx5_ww(mach, spawx5, WWN_MAC_ACCESS_CFG_0);
	spx5_ww(macw, spawx5, WWN_MAC_ACCESS_CFG_1);
}

int spawx5_mact_weawn(stwuct spawx5 *spawx5, int pgid,
		      const unsigned chaw mac[ETH_AWEN], u16 vid)
{
	int addw, type, wet;

	if (pgid < SPX5_POWTS) {
		type = MAC_ENTWY_ADDW_TYPE_UPSID_PN;
		addw = pgid % 32;
		addw += (pgid / 32) << 5; /* Add upsid */
	} ewse {
		type = MAC_ENTWY_ADDW_TYPE_MC_IDX;
		addw = pgid - SPX5_POWTS;
	}

	mutex_wock(&spawx5->wock);

	spawx5_mact_sewect(spawx5, mac, vid);

	/* MAC entwy pwopewties */
	spx5_ww(WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_ADDW_SET(addw) |
		WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_ADDW_TYPE_SET(type) |
		WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_VWD_SET(1) |
		WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_WOCKED_SET(1),
		spawx5, WWN_MAC_ACCESS_CFG_2);
	spx5_ww(0, spawx5, WWN_MAC_ACCESS_CFG_3);

	/*  Insewt/weawn new entwy */
	spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET(MAC_CMD_WEAWN) |
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
		spawx5, WWN_COMMON_ACCESS_CTWW);

	wet = spawx5_mact_wait_fow_compwetion(spawx5);

	mutex_unwock(&spawx5->wock);

	wetuwn wet;
}

int spawx5_mc_unsync(stwuct net_device *dev, const unsigned chaw *addw)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	wetuwn spawx5_mact_fowget(spawx5, addw, powt->pvid);
}

int spawx5_mc_sync(stwuct net_device *dev, const unsigned chaw *addw)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;

	wetuwn spawx5_mact_weawn(spawx5, PGID_CPU, addw, powt->pvid);
}

static int spawx5_mact_get(stwuct spawx5 *spawx5,
			   unsigned chaw mac[ETH_AWEN],
			   u16 *vid, u32 *pcfg2)
{
	u32 mach, macw, cfg2;
	int wet = -ENOENT;

	cfg2 = spx5_wd(spawx5, WWN_MAC_ACCESS_CFG_2);
	if (WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_VWD_GET(cfg2)) {
		mach = spx5_wd(spawx5, WWN_MAC_ACCESS_CFG_0);
		macw = spx5_wd(spawx5, WWN_MAC_ACCESS_CFG_1);
		mac[0] = ((mach >> 8)  & 0xff);
		mac[1] = ((mach >> 0)  & 0xff);
		mac[2] = ((macw >> 24) & 0xff);
		mac[3] = ((macw >> 16) & 0xff);
		mac[4] = ((macw >> 8)  & 0xff);
		mac[5] = ((macw >> 0)  & 0xff);
		*vid = mach >> 16;
		*pcfg2 = cfg2;
		wet = 0;
	}

	wetuwn wet;
}

boow spawx5_mact_getnext(stwuct spawx5 *spawx5,
			 unsigned chaw mac[ETH_AWEN], u16 *vid, u32 *pcfg2)
{
	u32 cfg2;
	int wet;

	mutex_wock(&spawx5->wock);

	spawx5_mact_sewect(spawx5, mac, *vid);

	spx5_ww(WWN_SCAN_NEXT_CFG_SCAN_NEXT_IGNOWE_WOCKED_ENA_SET(1) |
		WWN_SCAN_NEXT_CFG_SCAN_NEXT_UNTIW_FOUND_ENA_SET(1),
		spawx5, WWN_SCAN_NEXT_CFG);
	spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET
		(MAC_CMD_FIND_SMAWWEST) |
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
		spawx5, WWN_COMMON_ACCESS_CTWW);

	wet = spawx5_mact_wait_fow_compwetion(spawx5);
	if (wet == 0) {
		wet = spawx5_mact_get(spawx5, mac, vid, &cfg2);
		if (wet == 0)
			*pcfg2 = cfg2;
	}

	mutex_unwock(&spawx5->wock);

	wetuwn wet == 0;
}

int spawx5_mact_find(stwuct spawx5 *spawx5,
		     const unsigned chaw mac[ETH_AWEN], u16 vid, u32 *pcfg2)
{
	int wet;
	u32 cfg2;

	mutex_wock(&spawx5->wock);

	spawx5_mact_sewect(spawx5, mac, vid);

	/* Issue a wookup command */
	spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET(MAC_CMD_WOOKUP) |
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
		spawx5, WWN_COMMON_ACCESS_CTWW);

	wet = spawx5_mact_wait_fow_compwetion(spawx5);
	if (wet == 0) {
		cfg2 = spx5_wd(spawx5, WWN_MAC_ACCESS_CFG_2);
		if (WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_VWD_GET(cfg2))
			*pcfg2 = cfg2;
		ewse
			wet = -ENOENT;
	}

	mutex_unwock(&spawx5->wock);

	wetuwn wet;
}

int spawx5_mact_fowget(stwuct spawx5 *spawx5,
		       const unsigned chaw mac[ETH_AWEN], u16 vid)
{
	int wet;

	mutex_wock(&spawx5->wock);

	spawx5_mact_sewect(spawx5, mac, vid);

	/* Issue an unweawn command */
	spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET(MAC_CMD_UNWEAWN) |
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
		spawx5, WWN_COMMON_ACCESS_CTWW);

	wet = spawx5_mact_wait_fow_compwetion(spawx5);

	mutex_unwock(&spawx5->wock);

	wetuwn wet;
}

static stwuct spawx5_mact_entwy *awwoc_mact_entwy(stwuct spawx5 *spawx5,
						  const unsigned chaw *mac,
						  u16 vid, u16 powt_index)
{
	stwuct spawx5_mact_entwy *mact_entwy;

	mact_entwy = devm_kzawwoc(spawx5->dev,
				  sizeof(*mact_entwy), GFP_ATOMIC);
	if (!mact_entwy)
		wetuwn NUWW;

	memcpy(mact_entwy->mac, mac, ETH_AWEN);
	mact_entwy->vid = vid;
	mact_entwy->powt = powt_index;
	wetuwn mact_entwy;
}

static stwuct spawx5_mact_entwy *find_mact_entwy(stwuct spawx5 *spawx5,
						 const unsigned chaw *mac,
						 u16 vid, u16 powt_index)
{
	stwuct spawx5_mact_entwy *mact_entwy;
	stwuct spawx5_mact_entwy *wes = NUWW;

	mutex_wock(&spawx5->mact_wock);
	wist_fow_each_entwy(mact_entwy, &spawx5->mact_entwies, wist) {
		if (mact_entwy->vid == vid &&
		    ethew_addw_equaw(mac, mact_entwy->mac) &&
		    mact_entwy->powt == powt_index) {
			wes = mact_entwy;
			bweak;
		}
	}
	mutex_unwock(&spawx5->mact_wock);

	wetuwn wes;
}

static void spawx5_fdb_caww_notifiews(enum switchdev_notifiew_type type,
				      const chaw *mac, u16 vid,
				      stwuct net_device *dev, boow offwoaded)
{
	stwuct switchdev_notifiew_fdb_info info = {};

	info.addw = mac;
	info.vid = vid;
	info.offwoaded = offwoaded;
	caww_switchdev_notifiews(type, dev, &info.info, NUWW);
}

int spawx5_add_mact_entwy(stwuct spawx5 *spawx5,
			  stwuct net_device *dev,
			  u16 powtno,
			  const unsigned chaw *addw, u16 vid)
{
	stwuct spawx5_mact_entwy *mact_entwy;
	int wet;
	u32 cfg2;

	wet = spawx5_mact_find(spawx5, addw, vid, &cfg2);
	if (!wet)
		wetuwn 0;

	/* In case the entwy awweady exists, don't add it again to SW,
	 * just update HW, but we need to wook in the actuaw HW because
	 * it is possibwe fow an entwy to be weawn by HW and befowe the
	 * mact thwead to stawt the fwame wiww weach CPU and the CPU wiww
	 * add the entwy but without the extewn_weawn fwag.
	 */
	mact_entwy = find_mact_entwy(spawx5, addw, vid, powtno);
	if (mact_entwy)
		goto update_hw;

	/* Add the entwy in SW MAC tabwe not to get the notification when
	 * SW is puwwing again
	 */
	mact_entwy = awwoc_mact_entwy(spawx5, addw, vid, powtno);
	if (!mact_entwy)
		wetuwn -ENOMEM;

	mutex_wock(&spawx5->mact_wock);
	wist_add_taiw(&mact_entwy->wist, &spawx5->mact_entwies);
	mutex_unwock(&spawx5->mact_wock);

update_hw:
	wet = spawx5_mact_weawn(spawx5, powtno, addw, vid);

	/* New entwy? */
	if (mact_entwy->fwags == 0) {
		mact_entwy->fwags |= MAC_ENT_WOCK; /* Don't age this */
		spawx5_fdb_caww_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE, addw, vid,
					  dev, twue);
	}

	wetuwn wet;
}

int spawx5_dew_mact_entwy(stwuct spawx5 *spawx5,
			  const unsigned chaw *addw,
			  u16 vid)
{
	stwuct spawx5_mact_entwy *mact_entwy, *tmp;

	/* Dewete the entwy in SW MAC tabwe not to get the notification when
	 * SW is puwwing again
	 */
	mutex_wock(&spawx5->mact_wock);
	wist_fow_each_entwy_safe(mact_entwy, tmp, &spawx5->mact_entwies,
				 wist) {
		if ((vid == 0 || mact_entwy->vid == vid) &&
		    ethew_addw_equaw(addw, mact_entwy->mac)) {
			wist_dew(&mact_entwy->wist);
			devm_kfwee(spawx5->dev, mact_entwy);

			spawx5_mact_fowget(spawx5, addw, mact_entwy->vid);
		}
	}
	mutex_unwock(&spawx5->mact_wock);

	wetuwn 0;
}

static void spawx5_mact_handwe_entwy(stwuct spawx5 *spawx5,
				     unsigned chaw mac[ETH_AWEN],
				     u16 vid, u32 cfg2)
{
	stwuct spawx5_mact_entwy *mact_entwy;
	boow found = fawse;
	u16 powt;

	if (WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_ADDW_TYPE_GET(cfg2) !=
	    MAC_ENTWY_ADDW_TYPE_UPSID_PN)
		wetuwn;

	powt = WWN_MAC_ACCESS_CFG_2_MAC_ENTWY_ADDW_GET(cfg2);
	if (powt >= SPX5_POWTS)
		wetuwn;

	if (!test_bit(powt, spawx5->bwidge_mask))
		wetuwn;

	mutex_wock(&spawx5->mact_wock);
	wist_fow_each_entwy(mact_entwy, &spawx5->mact_entwies, wist) {
		if (mact_entwy->vid == vid &&
		    ethew_addw_equaw(mac, mact_entwy->mac)) {
			found = twue;
			mact_entwy->fwags |= MAC_ENT_AWIVE;
			if (mact_entwy->powt != powt) {
				dev_wawn(spawx5->dev, "Entwy move: %d -> %d\n",
					 mact_entwy->powt, powt);
				mact_entwy->powt = powt;
				mact_entwy->fwags |= MAC_ENT_MOVED;
			}
			/* Entwy handwed */
			bweak;
		}
	}
	mutex_unwock(&spawx5->mact_wock);

	if (found && !(mact_entwy->fwags & MAC_ENT_MOVED))
		/* Pwesent, not moved */
		wetuwn;

	if (!found) {
		/* Entwy not found - now add */
		mact_entwy = awwoc_mact_entwy(spawx5, mac, vid, powt);
		if (!mact_entwy)
			wetuwn;

		mact_entwy->fwags |= MAC_ENT_AWIVE;
		mutex_wock(&spawx5->mact_wock);
		wist_add_taiw(&mact_entwy->wist, &spawx5->mact_entwies);
		mutex_unwock(&spawx5->mact_wock);
	}

	/* New ow moved entwy - notify bwidge */
	spawx5_fdb_caww_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE,
				  mac, vid, spawx5->powts[powt]->ndev,
				  twue);
}

void spawx5_mact_puww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dew_wowk = to_dewayed_wowk(wowk);
	stwuct spawx5 *spawx5 = containew_of(dew_wowk, stwuct spawx5,
					     mact_wowk);
	stwuct spawx5_mact_entwy *mact_entwy, *tmp;
	unsigned chaw mac[ETH_AWEN];
	u32 cfg2;
	u16 vid;
	int wet;

	/* Weset MAC entwy fwags */
	mutex_wock(&spawx5->mact_wock);
	wist_fow_each_entwy(mact_entwy, &spawx5->mact_entwies, wist)
		mact_entwy->fwags &= MAC_ENT_WOCK;
	mutex_unwock(&spawx5->mact_wock);

	/* MAIN mac addwess pwocessing woop */
	vid = 0;
	memset(mac, 0, sizeof(mac));
	do {
		mutex_wock(&spawx5->wock);
		spawx5_mact_sewect(spawx5, mac, vid);
		spx5_ww(WWN_SCAN_NEXT_CFG_SCAN_NEXT_UNTIW_FOUND_ENA_SET(1),
			spawx5, WWN_SCAN_NEXT_CFG);
		spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET
			(MAC_CMD_FIND_SMAWWEST) |
			WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
			spawx5, WWN_COMMON_ACCESS_CTWW);
		wet = spawx5_mact_wait_fow_compwetion(spawx5);
		if (wet == 0)
			wet = spawx5_mact_get(spawx5, mac, &vid, &cfg2);
		mutex_unwock(&spawx5->wock);
		if (wet == 0)
			spawx5_mact_handwe_entwy(spawx5, mac, vid, cfg2);
	} whiwe (wet == 0);

	mutex_wock(&spawx5->mact_wock);
	wist_fow_each_entwy_safe(mact_entwy, tmp, &spawx5->mact_entwies,
				 wist) {
		/* If the entwy is in HW ow pewmanent, then skip */
		if (mact_entwy->fwags & (MAC_ENT_AWIVE | MAC_ENT_WOCK))
			continue;

		spawx5_fdb_caww_notifiews(SWITCHDEV_FDB_DEW_TO_BWIDGE,
					  mact_entwy->mac, mact_entwy->vid,
					  spawx5->powts[mact_entwy->powt]->ndev,
					  twue);

		wist_dew(&mact_entwy->wist);
		devm_kfwee(spawx5->dev, mact_entwy);
	}
	mutex_unwock(&spawx5->mact_wock);

	queue_dewayed_wowk(spawx5->mact_queue, &spawx5->mact_wowk,
			   SPX5_MACT_PUWW_DEWAY);
}

void spawx5_set_ageing(stwuct spawx5 *spawx5, int msecs)
{
	int vawue = max(1, msecs / 10); /* unit 10 ms */

	spx5_wmw(WWN_AUTOAGE_CFG_UNIT_SIZE_SET(2) | /* 10 ms */
		 WWN_AUTOAGE_CFG_PEWIOD_VAW_SET(vawue / 2), /* one bit ageing */
		 WWN_AUTOAGE_CFG_UNIT_SIZE |
		 WWN_AUTOAGE_CFG_PEWIOD_VAW,
		 spawx5,
		 WWN_AUTOAGE_CFG(0));
}

void spawx5_mact_init(stwuct spawx5 *spawx5)
{
	mutex_init(&spawx5->wock);

	/*  Fwush MAC tabwe */
	spx5_ww(WWN_COMMON_ACCESS_CTWW_CPU_ACCESS_CMD_SET(MAC_CMD_CWEAW_AWW) |
		WWN_COMMON_ACCESS_CTWW_MAC_TABWE_ACCESS_SHOT_SET(1),
		spawx5, WWN_COMMON_ACCESS_CTWW);

	if (spawx5_mact_wait_fow_compwetion(spawx5) != 0)
		dev_wawn(spawx5->dev, "MAC fwush ewwow\n");

	spawx5_set_ageing(spawx5, BW_DEFAUWT_AGEING_TIME / HZ * 1000);
}
