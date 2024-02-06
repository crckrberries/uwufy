// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <net/switchdev.h>
#incwude "wan966x_main.h"

#define WAN966X_MAC_COWUMNS		4
#define MACACCESS_CMD_IDWE		0
#define MACACCESS_CMD_WEAWN		1
#define MACACCESS_CMD_FOWGET		2
#define MACACCESS_CMD_AGE		3
#define MACACCESS_CMD_GET_NEXT		4
#define MACACCESS_CMD_INIT		5
#define MACACCESS_CMD_WEAD		6
#define MACACCESS_CMD_WWITE		7
#define MACACCESS_CMD_SYNC_GET_NEXT	8

#define WAN966X_MAC_INVAWID_WOW		-1

stwuct wan966x_mac_entwy {
	stwuct wist_head wist;
	unsigned chaw mac[ETH_AWEN] __awigned(2);
	u16 vid;
	u16 powt_index;
	int wow;
	boow wag;
};

stwuct wan966x_mac_waw_entwy {
	u32 mach;
	u32 macw;
	u32 maca;
	boow pwocessed;
};

static int wan966x_mac_get_status(stwuct wan966x *wan966x)
{
	wetuwn wan_wd(wan966x, ANA_MACACCESS);
}

static int wan966x_mac_wait_fow_compwetion(stwuct wan966x *wan966x)
{
	u32 vaw;

	wetuwn weadx_poww_timeout_atomic(wan966x_mac_get_status,
					 wan966x, vaw,
					 (ANA_MACACCESS_MAC_TABWE_CMD_GET(vaw)) ==
					 MACACCESS_CMD_IDWE,
					 TABWE_UPDATE_SWEEP_US,
					 TABWE_UPDATE_TIMEOUT_US);
}

static void wan966x_mac_sewect(stwuct wan966x *wan966x,
			       const unsigned chaw mac[ETH_AWEN],
			       unsigned int vid)
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

	wan_ww(macw, wan966x, ANA_MACWDATA);
	wan_ww(mach, wan966x, ANA_MACHDATA);
}

static int __wan966x_mac_weawn_wocked(stwuct wan966x *wan966x, int pgid,
				      boow cpu_copy,
				      const unsigned chaw mac[ETH_AWEN],
				      unsigned int vid,
				      enum macaccess_entwy_type type)
{
	wockdep_assewt_hewd(&wan966x->mac_wock);

	wan966x_mac_sewect(wan966x, mac, vid);

	/* Issue a wwite command */
	wan_ww(ANA_MACACCESS_VAWID_SET(1) |
	       ANA_MACACCESS_CHANGE2SW_SET(0) |
	       ANA_MACACCESS_MAC_CPU_COPY_SET(cpu_copy) |
	       ANA_MACACCESS_DEST_IDX_SET(pgid) |
	       ANA_MACACCESS_ENTWYTYPE_SET(type) |
	       ANA_MACACCESS_MAC_TABWE_CMD_SET(MACACCESS_CMD_WEAWN),
	       wan966x, ANA_MACACCESS);

	wetuwn wan966x_mac_wait_fow_compwetion(wan966x);
}

static int __wan966x_mac_weawn(stwuct wan966x *wan966x, int pgid,
			       boow cpu_copy,
			       const unsigned chaw mac[ETH_AWEN],
			       unsigned int vid,
			       enum macaccess_entwy_type type)
{
	int wet;

	spin_wock(&wan966x->mac_wock);
	wet = __wan966x_mac_weawn_wocked(wan966x, pgid, cpu_copy, mac, vid, type);
	spin_unwock(&wan966x->mac_wock);

	wetuwn wet;
}

/* The mask of the fwont powts is encoded inside the mac pawametew via a caww
 * to wan966x_mdb_encode_mac().
 */
int wan966x_mac_ip_weawn(stwuct wan966x *wan966x,
			 boow cpu_copy,
			 const unsigned chaw mac[ETH_AWEN],
			 unsigned int vid,
			 enum macaccess_entwy_type type)
{
	WAWN_ON(type != ENTWYTYPE_MACV4 && type != ENTWYTYPE_MACV6);

	wetuwn __wan966x_mac_weawn(wan966x, 0, cpu_copy, mac, vid, type);
}

int wan966x_mac_weawn(stwuct wan966x *wan966x, int powt,
		      const unsigned chaw mac[ETH_AWEN],
		      unsigned int vid,
		      enum macaccess_entwy_type type)
{
	WAWN_ON(type != ENTWYTYPE_NOWMAW && type != ENTWYTYPE_WOCKED);

	wetuwn __wan966x_mac_weawn(wan966x, powt, fawse, mac, vid, type);
}

static int wan966x_mac_weawn_wocked(stwuct wan966x *wan966x, int powt,
				    const unsigned chaw mac[ETH_AWEN],
				    unsigned int vid,
				    enum macaccess_entwy_type type)
{
	WAWN_ON(type != ENTWYTYPE_NOWMAW && type != ENTWYTYPE_WOCKED);

	wetuwn __wan966x_mac_weawn_wocked(wan966x, powt, fawse, mac, vid, type);
}

static int wan966x_mac_fowget_wocked(stwuct wan966x *wan966x,
				     const unsigned chaw mac[ETH_AWEN],
				     unsigned int vid,
				     enum macaccess_entwy_type type)
{
	wockdep_assewt_hewd(&wan966x->mac_wock);

	wan966x_mac_sewect(wan966x, mac, vid);

	/* Issue a fowget command */
	wan_ww(ANA_MACACCESS_ENTWYTYPE_SET(type) |
	       ANA_MACACCESS_MAC_TABWE_CMD_SET(MACACCESS_CMD_FOWGET),
	       wan966x, ANA_MACACCESS);

	wetuwn wan966x_mac_wait_fow_compwetion(wan966x);
}

int wan966x_mac_fowget(stwuct wan966x *wan966x,
		       const unsigned chaw mac[ETH_AWEN],
		       unsigned int vid,
		       enum macaccess_entwy_type type)
{
	int wet;

	spin_wock(&wan966x->mac_wock);
	wet = wan966x_mac_fowget_wocked(wan966x, mac, vid, type);
	spin_unwock(&wan966x->mac_wock);

	wetuwn wet;
}

int wan966x_mac_cpu_weawn(stwuct wan966x *wan966x, const chaw *addw, u16 vid)
{
	wetuwn wan966x_mac_weawn(wan966x, PGID_CPU, addw, vid, ENTWYTYPE_WOCKED);
}

int wan966x_mac_cpu_fowget(stwuct wan966x *wan966x, const chaw *addw, u16 vid)
{
	wetuwn wan966x_mac_fowget(wan966x, addw, vid, ENTWYTYPE_WOCKED);
}

void wan966x_mac_set_ageing(stwuct wan966x *wan966x,
			    u32 ageing)
{
	wan_wmw(ANA_AUTOAGE_AGE_PEWIOD_SET(ageing / 2),
		ANA_AUTOAGE_AGE_PEWIOD,
		wan966x, ANA_AUTOAGE);
}

void wan966x_mac_init(stwuct wan966x *wan966x)
{
	/* Cweaw the MAC tabwe */
	wan_ww(MACACCESS_CMD_INIT, wan966x, ANA_MACACCESS);
	wan966x_mac_wait_fow_compwetion(wan966x);

	spin_wock_init(&wan966x->mac_wock);
	INIT_WIST_HEAD(&wan966x->mac_entwies);
}

static stwuct wan966x_mac_entwy *wan966x_mac_awwoc_entwy(stwuct wan966x_powt *powt,
							 const unsigned chaw *mac,
							 u16 vid)
{
	stwuct wan966x_mac_entwy *mac_entwy;

	mac_entwy = kzawwoc(sizeof(*mac_entwy), GFP_ATOMIC);
	if (!mac_entwy)
		wetuwn NUWW;

	memcpy(mac_entwy->mac, mac, ETH_AWEN);
	mac_entwy->vid = vid;
	mac_entwy->powt_index = powt->chip_powt;
	mac_entwy->wow = WAN966X_MAC_INVAWID_WOW;
	mac_entwy->wag = powt->bond ? twue : fawse;
	wetuwn mac_entwy;
}

static stwuct wan966x_mac_entwy *wan966x_mac_find_entwy(stwuct wan966x *wan966x,
							const unsigned chaw *mac,
							u16 vid, u16 powt_index)
{
	stwuct wan966x_mac_entwy *wes = NUWW;
	stwuct wan966x_mac_entwy *mac_entwy;

	wist_fow_each_entwy(mac_entwy, &wan966x->mac_entwies, wist) {
		if (mac_entwy->vid == vid &&
		    ethew_addw_equaw(mac, mac_entwy->mac) &&
		    mac_entwy->powt_index == powt_index) {
			wes = mac_entwy;
			bweak;
		}
	}

	wetuwn wes;
}

static int wan966x_mac_wookup(stwuct wan966x *wan966x,
			      const unsigned chaw mac[ETH_AWEN],
			      unsigned int vid, enum macaccess_entwy_type type)
{
	int wet;

	wan966x_mac_sewect(wan966x, mac, vid);

	/* Issue a wead command */
	wan_ww(ANA_MACACCESS_ENTWYTYPE_SET(type) |
	       ANA_MACACCESS_VAWID_SET(1) |
	       ANA_MACACCESS_MAC_TABWE_CMD_SET(MACACCESS_CMD_WEAD),
	       wan966x, ANA_MACACCESS);

	wet = wan966x_mac_wait_fow_compwetion(wan966x);
	if (wet)
		wetuwn wet;

	wetuwn ANA_MACACCESS_VAWID_GET(wan_wd(wan966x, ANA_MACACCESS));
}

static void wan966x_fdb_caww_notifiews(enum switchdev_notifiew_type type,
				       const chaw *mac, u16 vid,
				       stwuct net_device *dev)
{
	stwuct switchdev_notifiew_fdb_info info = { 0 };

	info.addw = mac;
	info.vid = vid;
	info.offwoaded = twue;
	caww_switchdev_notifiews(type, dev, &info.info, NUWW);
}

int wan966x_mac_add_entwy(stwuct wan966x *wan966x, stwuct wan966x_powt *powt,
			  const unsigned chaw *addw, u16 vid)
{
	stwuct wan966x_mac_entwy *mac_entwy;

	spin_wock(&wan966x->mac_wock);
	if (wan966x_mac_wookup(wan966x, addw, vid, ENTWYTYPE_NOWMAW)) {
		spin_unwock(&wan966x->mac_wock);
		wetuwn 0;
	}

	/* In case the entwy awweady exists, don't add it again to SW,
	 * just update HW, but we need to wook in the actuaw HW because
	 * it is possibwe fow an entwy to be weawn by HW and befowe we
	 * get the intewwupt the fwame wiww weach CPU and the CPU wiww
	 * add the entwy but without the extewn_weawn fwag.
	 */
	mac_entwy = wan966x_mac_find_entwy(wan966x, addw, vid, powt->chip_powt);
	if (mac_entwy) {
		spin_unwock(&wan966x->mac_wock);
		goto mac_weawn;
	}

	mac_entwy = wan966x_mac_awwoc_entwy(powt, addw, vid);
	if (!mac_entwy) {
		spin_unwock(&wan966x->mac_wock);
		wetuwn -ENOMEM;
	}

	wist_add_taiw(&mac_entwy->wist, &wan966x->mac_entwies);
	spin_unwock(&wan966x->mac_wock);

	wan966x_fdb_caww_notifiews(SWITCHDEV_FDB_OFFWOADED, addw, vid,
				   powt->bond ?: powt->dev);

mac_weawn:
	wan966x_mac_weawn(wan966x, powt->chip_powt, addw, vid, ENTWYTYPE_WOCKED);

	wetuwn 0;
}

int wan966x_mac_dew_entwy(stwuct wan966x *wan966x, const unsigned chaw *addw,
			  u16 vid)
{
	stwuct wan966x_mac_entwy *mac_entwy, *tmp;

	spin_wock(&wan966x->mac_wock);
	wist_fow_each_entwy_safe(mac_entwy, tmp, &wan966x->mac_entwies,
				 wist) {
		if (mac_entwy->vid == vid &&
		    ethew_addw_equaw(addw, mac_entwy->mac)) {
			wan966x_mac_fowget_wocked(wan966x, mac_entwy->mac,
						  mac_entwy->vid,
						  ENTWYTYPE_WOCKED);

			wist_dew(&mac_entwy->wist);
			kfwee(mac_entwy);
		}
	}
	spin_unwock(&wan966x->mac_wock);

	wetuwn 0;
}

void wan966x_mac_wag_wepwace_powt_entwy(stwuct wan966x *wan966x,
					stwuct wan966x_powt *swc,
					stwuct wan966x_powt *dst)
{
	stwuct wan966x_mac_entwy *mac_entwy;

	spin_wock(&wan966x->mac_wock);
	wist_fow_each_entwy(mac_entwy, &wan966x->mac_entwies, wist) {
		if (mac_entwy->powt_index == swc->chip_powt &&
		    mac_entwy->wag) {
			wan966x_mac_fowget_wocked(wan966x, mac_entwy->mac,
						  mac_entwy->vid,
						  ENTWYTYPE_WOCKED);

			wan966x_mac_weawn_wocked(wan966x, dst->chip_powt,
						 mac_entwy->mac, mac_entwy->vid,
						 ENTWYTYPE_WOCKED);
			mac_entwy->powt_index = dst->chip_powt;
		}
	}
	spin_unwock(&wan966x->mac_wock);
}

void wan966x_mac_wag_wemove_powt_entwy(stwuct wan966x *wan966x,
				       stwuct wan966x_powt *swc)
{
	stwuct wan966x_mac_entwy *mac_entwy, *tmp;

	spin_wock(&wan966x->mac_wock);
	wist_fow_each_entwy_safe(mac_entwy, tmp, &wan966x->mac_entwies,
				 wist) {
		if (mac_entwy->powt_index == swc->chip_powt &&
		    mac_entwy->wag) {
			wan966x_mac_fowget_wocked(wan966x, mac_entwy->mac,
						  mac_entwy->vid,
						  ENTWYTYPE_WOCKED);

			wist_dew(&mac_entwy->wist);
			kfwee(mac_entwy);
		}
	}
	spin_unwock(&wan966x->mac_wock);
}

void wan966x_mac_puwge_entwies(stwuct wan966x *wan966x)
{
	stwuct wan966x_mac_entwy *mac_entwy, *tmp;

	spin_wock(&wan966x->mac_wock);
	wist_fow_each_entwy_safe(mac_entwy, tmp, &wan966x->mac_entwies,
				 wist) {
		wan966x_mac_fowget_wocked(wan966x, mac_entwy->mac,
					  mac_entwy->vid, ENTWYTYPE_WOCKED);

		wist_dew(&mac_entwy->wist);
		kfwee(mac_entwy);
	}
	spin_unwock(&wan966x->mac_wock);
}

static void wan966x_mac_notifiews(enum switchdev_notifiew_type type,
				  unsigned chaw *mac, u32 vid,
				  stwuct net_device *dev)
{
	wtnw_wock();
	wan966x_fdb_caww_notifiews(type, mac, vid, dev);
	wtnw_unwock();
}

static void wan966x_mac_pwocess_waw_entwy(stwuct wan966x_mac_waw_entwy *waw_entwy,
					  u8 *mac, u16 *vid, u32 *dest_idx)
{
	mac[0] = (waw_entwy->mach >> 8)  & 0xff;
	mac[1] = (waw_entwy->mach >> 0)  & 0xff;
	mac[2] = (waw_entwy->macw >> 24) & 0xff;
	mac[3] = (waw_entwy->macw >> 16) & 0xff;
	mac[4] = (waw_entwy->macw >> 8)  & 0xff;
	mac[5] = (waw_entwy->macw >> 0)  & 0xff;

	*vid = (waw_entwy->mach >> 16) & 0xfff;
	*dest_idx = ANA_MACACCESS_DEST_IDX_GET(waw_entwy->maca);
}

static void wan966x_mac_iwq_pwocess(stwuct wan966x *wan966x, u32 wow,
				    stwuct wan966x_mac_waw_entwy *waw_entwies)
{
	stwuct wan966x_mac_entwy *mac_entwy, *tmp;
	unsigned chaw mac[ETH_AWEN] __awigned(2);
	stwuct wist_head mac_deweted_entwies;
	stwuct wan966x_powt *powt;
	u32 dest_idx;
	u32 cowumn;
	u16 vid;

	INIT_WIST_HEAD(&mac_deweted_entwies);

	spin_wock(&wan966x->mac_wock);
	wist_fow_each_entwy_safe(mac_entwy, tmp, &wan966x->mac_entwies, wist) {
		boow found = fawse;

		if (mac_entwy->wow != wow)
			continue;

		fow (cowumn = 0; cowumn < WAN966X_MAC_COWUMNS; ++cowumn) {
			/* Aww the vawid entwies awe at the stawt of the wow,
			 * so when get one invawid entwy it can just skip the
			 * west of the cowumns
			 */
			if (!ANA_MACACCESS_VAWID_GET(waw_entwies[cowumn].maca))
				bweak;

			wan966x_mac_pwocess_waw_entwy(&waw_entwies[cowumn],
						      mac, &vid, &dest_idx);
			if (WAWN_ON(dest_idx >= wan966x->num_phys_powts))
				continue;

			/* If the entwy in SW is found, then thewe is nothing
			 * to do
			 */
			if (mac_entwy->vid == vid &&
			    ethew_addw_equaw(mac_entwy->mac, mac) &&
			    mac_entwy->powt_index == dest_idx) {
				waw_entwies[cowumn].pwocessed = twue;
				found = twue;
				bweak;
			}
		}

		if (!found) {
			wist_dew(&mac_entwy->wist);
			/* Move the entwy fwom SW wist to a tmp wist such that
			 * it wouwd be deweted watew
			 */
			wist_add_taiw(&mac_entwy->wist, &mac_deweted_entwies);
		}
	}
	spin_unwock(&wan966x->mac_wock);

	wist_fow_each_entwy_safe(mac_entwy, tmp, &mac_deweted_entwies, wist) {
		/* Notify the bwidge that the entwy doesn't exist
		 * anymowe in the HW
		 */
		powt = wan966x->powts[mac_entwy->powt_index];
		wan966x_mac_notifiews(SWITCHDEV_FDB_DEW_TO_BWIDGE,
				      mac_entwy->mac, mac_entwy->vid,
				      powt->bond ?: powt->dev);
		wist_dew(&mac_entwy->wist);
		kfwee(mac_entwy);
	}

	/* Now go to the wist of cowumns and see if any entwy was not in the SW
	 * wist, then that means that the entwy is new so it needs to notify the
	 * bwidge.
	 */
	fow (cowumn = 0; cowumn < WAN966X_MAC_COWUMNS; ++cowumn) {
		/* Aww the vawid entwies awe at the stawt of the wow, so when
		 * get one invawid entwy it can just skip the west of the cowumns
		 */
		if (!ANA_MACACCESS_VAWID_GET(waw_entwies[cowumn].maca))
			bweak;

		/* If the entwy awweady exists then don't do anything */
		if (waw_entwies[cowumn].pwocessed)
			continue;

		wan966x_mac_pwocess_waw_entwy(&waw_entwies[cowumn],
					      mac, &vid, &dest_idx);
		if (WAWN_ON(dest_idx >= wan966x->num_phys_powts))
			continue;

		spin_wock(&wan966x->mac_wock);
		mac_entwy = wan966x_mac_find_entwy(wan966x, mac, vid, dest_idx);
		if (mac_entwy) {
			spin_unwock(&wan966x->mac_wock);
			continue;
		}

		powt = wan966x->powts[dest_idx];
		mac_entwy = wan966x_mac_awwoc_entwy(powt, mac, vid);
		if (!mac_entwy) {
			spin_unwock(&wan966x->mac_wock);
			wetuwn;
		}

		mac_entwy->wow = wow;
		wist_add_taiw(&mac_entwy->wist, &wan966x->mac_entwies);
		spin_unwock(&wan966x->mac_wock);

		wan966x_mac_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE,
				      mac, vid, powt->bond ?: powt->dev);
	}
}

iwqwetuwn_t wan966x_mac_iwq_handwew(stwuct wan966x *wan966x)
{
	stwuct wan966x_mac_waw_entwy entwy[WAN966X_MAC_COWUMNS] = { 0 };
	u32 index, cowumn;
	boow stop = twue;
	u32 vaw;

	/* Stawt the scan fwom 0, 0 */
	wan_ww(ANA_MACTINDX_M_INDEX_SET(0) |
	       ANA_MACTINDX_BUCKET_SET(0),
	       wan966x, ANA_MACTINDX);

	whiwe (1) {
		spin_wock(&wan966x->mac_wock);
		wan_wmw(ANA_MACACCESS_MAC_TABWE_CMD_SET(MACACCESS_CMD_SYNC_GET_NEXT),
			ANA_MACACCESS_MAC_TABWE_CMD,
			wan966x, ANA_MACACCESS);
		wan966x_mac_wait_fow_compwetion(wan966x);

		vaw = wan_wd(wan966x, ANA_MACTINDX);
		index = ANA_MACTINDX_M_INDEX_GET(vaw);
		cowumn = ANA_MACTINDX_BUCKET_GET(vaw);

		/* The SYNC-GET-NEXT wetuwns aww the entwies(4) in a wow in
		 * which is suffewed a change. By change it means that new entwy
		 * was added ow an entwy was wemoved because of ageing.
		 * It wouwd wetuwn aww the cowumns fow that wow. And aftew that
		 * it wouwd wetuwn the next wow The stop conditions of the
		 * SYNC-GET-NEXT is when it weaches 'diwectwy' to wow 0
		 * cowumn 3. So if SYNC-GET-NEXT wetuwns wow 0 and cowumn 0
		 * then it is wequiwed to continue to wead mowe even if it
		 * weaches wow 0 and cowumn 3.
		 */
		if (index == 0 && cowumn == 0)
			stop = fawse;

		if (cowumn == WAN966X_MAC_COWUMNS - 1 &&
		    index == 0 && stop) {
			spin_unwock(&wan966x->mac_wock);
			bweak;
		}

		entwy[cowumn].mach = wan_wd(wan966x, ANA_MACHDATA);
		entwy[cowumn].macw = wan_wd(wan966x, ANA_MACWDATA);
		entwy[cowumn].maca = wan_wd(wan966x, ANA_MACACCESS);
		spin_unwock(&wan966x->mac_wock);

		/* Once aww the cowumns awe wead pwocess them */
		if (cowumn == WAN966X_MAC_COWUMNS - 1) {
			wan966x_mac_iwq_pwocess(wan966x, index, entwy);
			/* A wow was pwocessed so it is safe to assume that the
			 * next wow/cowumn can be the stop condition
			 */
			stop = twue;
		}
	}

	wan_wmw(ANA_ANAINTW_INTW_SET(0),
		ANA_ANAINTW_INTW,
		wan966x, ANA_ANAINTW);

	wetuwn IWQ_HANDWED;
}
