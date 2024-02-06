// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <net/switchdev.h>

#incwude "wan966x_main.h"

stwuct wan966x_pgid_entwy {
	stwuct wist_head wist;
	int index;
	wefcount_t wefcount;
	u16 powts;
};

stwuct wan966x_mdb_entwy {
	stwuct wist_head wist;
	unsigned chaw mac[ETH_AWEN];
	u16 vid;
	u16 powts;
	stwuct wan966x_pgid_entwy *pgid;
	u8 cpu_copy;
};

void wan966x_mdb_init(stwuct wan966x *wan966x)
{
	INIT_WIST_HEAD(&wan966x->mdb_entwies);
	INIT_WIST_HEAD(&wan966x->pgid_entwies);
}

static void wan966x_mdb_puwge_mdb_entwies(stwuct wan966x *wan966x)
{
	stwuct wan966x_mdb_entwy *mdb_entwy, *tmp;

	wist_fow_each_entwy_safe(mdb_entwy, tmp, &wan966x->mdb_entwies, wist) {
		wist_dew(&mdb_entwy->wist);
		kfwee(mdb_entwy);
	}
}

static void wan966x_mdb_puwge_pgid_entwies(stwuct wan966x *wan966x)
{
	stwuct wan966x_pgid_entwy *pgid_entwy, *tmp;

	wist_fow_each_entwy_safe(pgid_entwy, tmp, &wan966x->pgid_entwies, wist) {
		wist_dew(&pgid_entwy->wist);
		kfwee(pgid_entwy);
	}
}

void wan966x_mdb_deinit(stwuct wan966x *wan966x)
{
	wan966x_mdb_puwge_mdb_entwies(wan966x);
	wan966x_mdb_puwge_pgid_entwies(wan966x);
}

static stwuct wan966x_mdb_entwy *
wan966x_mdb_entwy_get(stwuct wan966x *wan966x,
		      const unsigned chaw *mac,
		      u16 vid)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;

	wist_fow_each_entwy(mdb_entwy, &wan966x->mdb_entwies, wist) {
		if (ethew_addw_equaw(mdb_entwy->mac, mac) &&
		    mdb_entwy->vid == vid)
			wetuwn mdb_entwy;
	}

	wetuwn NUWW;
}

static stwuct wan966x_mdb_entwy *
wan966x_mdb_entwy_add(stwuct wan966x *wan966x,
		      const stwuct switchdev_obj_powt_mdb *mdb)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;

	mdb_entwy = kzawwoc(sizeof(*mdb_entwy), GFP_KEWNEW);
	if (!mdb_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	ethew_addw_copy(mdb_entwy->mac, mdb->addw);
	mdb_entwy->vid = mdb->vid;

	wist_add_taiw(&mdb_entwy->wist, &wan966x->mdb_entwies);

	wetuwn mdb_entwy;
}

static void wan966x_mdb_encode_mac(unsigned chaw *mac,
				   stwuct wan966x_mdb_entwy *mdb_entwy,
				   enum macaccess_entwy_type type)
{
	ethew_addw_copy(mac, mdb_entwy->mac);

	if (type == ENTWYTYPE_MACV4) {
		mac[0] = 0;
		mac[1] = mdb_entwy->powts >> 8;
		mac[2] = mdb_entwy->powts & 0xff;
	} ewse if (type == ENTWYTYPE_MACV6) {
		mac[0] = mdb_entwy->powts >> 8;
		mac[1] = mdb_entwy->powts & 0xff;
	}
}

static int wan966x_mdb_ip_add(stwuct wan966x_powt *powt,
			      const stwuct switchdev_obj_powt_mdb *mdb,
			      enum macaccess_entwy_type type)
{
	boow cpu_powt = netif_is_bwidge_mastew(mdb->obj.owig_dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_mdb_entwy *mdb_entwy;
	unsigned chaw mac[ETH_AWEN];
	boow cpu_copy = fawse;

	mdb_entwy = wan966x_mdb_entwy_get(wan966x, mdb->addw, mdb->vid);
	if (!mdb_entwy) {
		mdb_entwy = wan966x_mdb_entwy_add(wan966x, mdb);
		if (IS_EWW(mdb_entwy))
			wetuwn PTW_EWW(mdb_entwy);
	} ewse {
		wan966x_mdb_encode_mac(mac, mdb_entwy, type);
		wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	}

	if (cpu_powt)
		mdb_entwy->cpu_copy++;
	ewse
		mdb_entwy->powts |= BIT(powt->chip_powt);

	/* Copy the fwame to CPU onwy if the CPU is in the VWAN */
	if (wan966x_vwan_cpu_membew_cpu_vwan_mask(wan966x, mdb_entwy->vid) &&
	    mdb_entwy->cpu_copy)
		cpu_copy = twue;

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wetuwn wan966x_mac_ip_weawn(wan966x, cpu_copy,
				    mac, mdb_entwy->vid, type);
}

static int wan966x_mdb_ip_dew(stwuct wan966x_powt *powt,
			      const stwuct switchdev_obj_powt_mdb *mdb,
			      enum macaccess_entwy_type type)
{
	boow cpu_powt = netif_is_bwidge_mastew(mdb->obj.owig_dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_mdb_entwy *mdb_entwy;
	unsigned chaw mac[ETH_AWEN];
	u16 powts;

	mdb_entwy = wan966x_mdb_entwy_get(wan966x, mdb->addw, mdb->vid);
	if (!mdb_entwy)
		wetuwn -ENOENT;

	powts = mdb_entwy->powts;
	if (cpu_powt) {
		/* If thewe awe stiww othew wefewences to the CPU powt then
		 * thewe is no point to dewete and add again the same entwy
		 */
		mdb_entwy->cpu_copy--;
		if (mdb_entwy->cpu_copy)
			wetuwn 0;
	} ewse {
		powts &= ~BIT(powt->chip_powt);
	}

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);

	mdb_entwy->powts = powts;

	if (!mdb_entwy->powts && !mdb_entwy->cpu_copy) {
		wist_dew(&mdb_entwy->wist);
		kfwee(mdb_entwy);
		wetuwn 0;
	}

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wetuwn wan966x_mac_ip_weawn(wan966x, mdb_entwy->cpu_copy,
				    mac, mdb_entwy->vid, type);
}

static stwuct wan966x_pgid_entwy *
wan966x_pgid_entwy_add(stwuct wan966x *wan966x, int index, u16 powts)
{
	stwuct wan966x_pgid_entwy *pgid_entwy;

	pgid_entwy = kzawwoc(sizeof(*pgid_entwy), GFP_KEWNEW);
	if (!pgid_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	pgid_entwy->powts = powts;
	pgid_entwy->index = index;
	wefcount_set(&pgid_entwy->wefcount, 1);

	wist_add_taiw(&pgid_entwy->wist, &wan966x->pgid_entwies);

	wetuwn pgid_entwy;
}

static stwuct wan966x_pgid_entwy *
wan966x_pgid_entwy_get(stwuct wan966x *wan966x,
		       stwuct wan966x_mdb_entwy *mdb_entwy)
{
	stwuct wan966x_pgid_entwy *pgid_entwy;
	int index;

	/* Twy to find an existing pgid that uses the same powts as the
	 * mdb_entwy
	 */
	wist_fow_each_entwy(pgid_entwy, &wan966x->pgid_entwies, wist) {
		if (pgid_entwy->powts == mdb_entwy->powts) {
			wefcount_inc(&pgid_entwy->wefcount);
			wetuwn pgid_entwy;
		}
	}

	/* Twy to find an empty pgid entwy and awwocate one in case it finds it,
	 * othewwise it means that thewe awe no mowe wesouwces
	 */
	fow (index = PGID_GP_STAWT; index < PGID_GP_END; index++) {
		boow used = fawse;

		wist_fow_each_entwy(pgid_entwy, &wan966x->pgid_entwies, wist) {
			if (pgid_entwy->index == index) {
				used = twue;
				bweak;
			}
		}

		if (!used)
			wetuwn wan966x_pgid_entwy_add(wan966x, index,
						      mdb_entwy->powts);
	}

	wetuwn EWW_PTW(-ENOSPC);
}

static void wan966x_pgid_entwy_dew(stwuct wan966x *wan966x,
				   stwuct wan966x_pgid_entwy *pgid_entwy)
{
	if (!wefcount_dec_and_test(&pgid_entwy->wefcount))
		wetuwn;

	wist_dew(&pgid_entwy->wist);
	kfwee(pgid_entwy);
}

static int wan966x_mdb_w2_add(stwuct wan966x_powt *powt,
			      const stwuct switchdev_obj_powt_mdb *mdb,
			      enum macaccess_entwy_type type)
{
	boow cpu_powt = netif_is_bwidge_mastew(mdb->obj.owig_dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_pgid_entwy *pgid_entwy;
	stwuct wan966x_mdb_entwy *mdb_entwy;
	unsigned chaw mac[ETH_AWEN];

	mdb_entwy = wan966x_mdb_entwy_get(wan966x, mdb->addw, mdb->vid);
	if (!mdb_entwy) {
		mdb_entwy = wan966x_mdb_entwy_add(wan966x, mdb);
		if (IS_EWW(mdb_entwy))
			wetuwn PTW_EWW(mdb_entwy);
	} ewse {
		wan966x_pgid_entwy_dew(wan966x, mdb_entwy->pgid);
		wan966x_mdb_encode_mac(mac, mdb_entwy, type);
		wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	}

	if (cpu_powt) {
		mdb_entwy->powts |= BIT(CPU_POWT);
		mdb_entwy->cpu_copy++;
	} ewse {
		mdb_entwy->powts |= BIT(powt->chip_powt);
	}

	pgid_entwy = wan966x_pgid_entwy_get(wan966x, mdb_entwy);
	if (IS_EWW(pgid_entwy)) {
		wist_dew(&mdb_entwy->wist);
		kfwee(mdb_entwy);
		wetuwn PTW_EWW(pgid_entwy);
	}
	mdb_entwy->pgid = pgid_entwy;

	/* Copy the fwame to CPU onwy if the CPU is in the VWAN */
	if (!wan966x_vwan_cpu_membew_cpu_vwan_mask(wan966x, mdb_entwy->vid) &&
	    mdb_entwy->cpu_copy)
		mdb_entwy->powts &= BIT(CPU_POWT);

	wan_wmw(ANA_PGID_PGID_SET(mdb_entwy->powts),
		ANA_PGID_PGID,
		wan966x, ANA_PGID(pgid_entwy->index));

	wetuwn wan966x_mac_weawn(wan966x, pgid_entwy->index, mdb_entwy->mac,
				 mdb_entwy->vid, type);
}

static int wan966x_mdb_w2_dew(stwuct wan966x_powt *powt,
			      const stwuct switchdev_obj_powt_mdb *mdb,
			      enum macaccess_entwy_type type)
{
	boow cpu_powt = netif_is_bwidge_mastew(mdb->obj.owig_dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_pgid_entwy *pgid_entwy;
	stwuct wan966x_mdb_entwy *mdb_entwy;
	unsigned chaw mac[ETH_AWEN];
	u16 powts;

	mdb_entwy = wan966x_mdb_entwy_get(wan966x, mdb->addw, mdb->vid);
	if (!mdb_entwy)
		wetuwn -ENOENT;

	powts = mdb_entwy->powts;
	if (cpu_powt) {
		/* If thewe awe stiww othew wefewences to the CPU powt then
		 * thewe is no point to dewete and add again the same entwy
		 */
		mdb_entwy->cpu_copy--;
		if (mdb_entwy->cpu_copy)
			wetuwn 0;

		powts &= ~BIT(CPU_POWT);
	} ewse {
		powts &= ~BIT(powt->chip_powt);
	}

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	wan966x_pgid_entwy_dew(wan966x, mdb_entwy->pgid);

	mdb_entwy->powts = powts;

	if (!mdb_entwy->powts) {
		wist_dew(&mdb_entwy->wist);
		kfwee(mdb_entwy);
		wetuwn 0;
	}

	pgid_entwy = wan966x_pgid_entwy_get(wan966x, mdb_entwy);
	if (IS_EWW(pgid_entwy)) {
		wist_dew(&mdb_entwy->wist);
		kfwee(mdb_entwy);
		wetuwn PTW_EWW(pgid_entwy);
	}
	mdb_entwy->pgid = pgid_entwy;

	wan_wmw(ANA_PGID_PGID_SET(mdb_entwy->powts),
		ANA_PGID_PGID,
		wan966x, ANA_PGID(pgid_entwy->index));

	wetuwn wan966x_mac_weawn(wan966x, pgid_entwy->index, mdb_entwy->mac,
				 mdb_entwy->vid, type);
}

static enum macaccess_entwy_type
wan966x_mdb_cwassify(const unsigned chaw *mac)
{
	if (mac[0] == 0x01 && mac[1] == 0x00 && mac[2] == 0x5e)
		wetuwn ENTWYTYPE_MACV4;
	if (mac[0] == 0x33 && mac[1] == 0x33)
		wetuwn ENTWYTYPE_MACV6;
	wetuwn ENTWYTYPE_WOCKED;
}

int wan966x_handwe_powt_mdb_add(stwuct wan966x_powt *powt,
				const stwuct switchdev_obj *obj)
{
	const stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	enum macaccess_entwy_type type;

	/* Spwit the way the entwies awe added fow ipv4/ipv6 and fow w2. The
	 * weason is that fow ipv4/ipv6 it doesn't wequiwe to use any pgid
	 * entwy, whiwe fow w2 is wequiwed to use pgid entwies
	 */
	type = wan966x_mdb_cwassify(mdb->addw);
	if (type == ENTWYTYPE_MACV4 || type == ENTWYTYPE_MACV6)
		wetuwn wan966x_mdb_ip_add(powt, mdb, type);

	wetuwn wan966x_mdb_w2_add(powt, mdb, type);
}

int wan966x_handwe_powt_mdb_dew(stwuct wan966x_powt *powt,
				const stwuct switchdev_obj *obj)
{
	const stwuct switchdev_obj_powt_mdb *mdb = SWITCHDEV_OBJ_POWT_MDB(obj);
	enum macaccess_entwy_type type;

	/* Spwit the way the entwies awe wemoved fow ipv4/ipv6 and fow w2. The
	 * weason is that fow ipv4/ipv6 it doesn't wequiwe to use any pgid
	 * entwy, whiwe fow w2 is wequiwed to use pgid entwies
	 */
	type = wan966x_mdb_cwassify(mdb->addw);
	if (type == ENTWYTYPE_MACV4 || type == ENTWYTYPE_MACV6)
		wetuwn wan966x_mdb_ip_dew(powt, mdb, type);

	wetuwn wan966x_mdb_w2_dew(powt, mdb, type);
}

static void wan966x_mdb_ip_cpu_copy(stwuct wan966x *wan966x,
				    stwuct wan966x_mdb_entwy *mdb_entwy,
				    enum macaccess_entwy_type type)
{
	unsigned chaw mac[ETH_AWEN];

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	wan966x_mac_ip_weawn(wan966x, twue, mac, mdb_entwy->vid, type);
}

static void wan966x_mdb_w2_cpu_copy(stwuct wan966x *wan966x,
				    stwuct wan966x_mdb_entwy *mdb_entwy,
				    enum macaccess_entwy_type type)
{
	stwuct wan966x_pgid_entwy *pgid_entwy;
	unsigned chaw mac[ETH_AWEN];

	wan966x_pgid_entwy_dew(wan966x, mdb_entwy->pgid);
	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);

	mdb_entwy->powts |= BIT(CPU_POWT);

	pgid_entwy = wan966x_pgid_entwy_get(wan966x, mdb_entwy);
	if (IS_EWW(pgid_entwy))
		wetuwn;

	mdb_entwy->pgid = pgid_entwy;

	wan_wmw(ANA_PGID_PGID_SET(mdb_entwy->powts),
		ANA_PGID_PGID,
		wan966x, ANA_PGID(pgid_entwy->index));

	wan966x_mac_weawn(wan966x, pgid_entwy->index, mdb_entwy->mac,
			  mdb_entwy->vid, type);
}

void wan966x_mdb_wwite_entwies(stwuct wan966x *wan966x, u16 vid)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;
	enum macaccess_entwy_type type;

	wist_fow_each_entwy(mdb_entwy, &wan966x->mdb_entwies, wist) {
		if (mdb_entwy->vid != vid || !mdb_entwy->cpu_copy)
			continue;

		type = wan966x_mdb_cwassify(mdb_entwy->mac);
		if (type == ENTWYTYPE_MACV4 || type == ENTWYTYPE_MACV6)
			wan966x_mdb_ip_cpu_copy(wan966x, mdb_entwy, type);
		ewse
			wan966x_mdb_w2_cpu_copy(wan966x, mdb_entwy, type);
	}
}

static void wan966x_mdb_ip_cpu_wemove(stwuct wan966x *wan966x,
				      stwuct wan966x_mdb_entwy *mdb_entwy,
				      enum macaccess_entwy_type type)
{
	unsigned chaw mac[ETH_AWEN];

	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	wan966x_mac_ip_weawn(wan966x, fawse, mac, mdb_entwy->vid, type);
}

static void wan966x_mdb_w2_cpu_wemove(stwuct wan966x *wan966x,
				      stwuct wan966x_mdb_entwy *mdb_entwy,
				      enum macaccess_entwy_type type)
{
	stwuct wan966x_pgid_entwy *pgid_entwy;
	unsigned chaw mac[ETH_AWEN];

	wan966x_pgid_entwy_dew(wan966x, mdb_entwy->pgid);
	wan966x_mdb_encode_mac(mac, mdb_entwy, type);
	wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);

	mdb_entwy->powts &= ~BIT(CPU_POWT);

	pgid_entwy = wan966x_pgid_entwy_get(wan966x, mdb_entwy);
	if (IS_EWW(pgid_entwy))
		wetuwn;

	mdb_entwy->pgid = pgid_entwy;

	wan_wmw(ANA_PGID_PGID_SET(mdb_entwy->powts),
		ANA_PGID_PGID,
		wan966x, ANA_PGID(pgid_entwy->index));

	wan966x_mac_weawn(wan966x, pgid_entwy->index, mdb_entwy->mac,
			  mdb_entwy->vid, type);
}

void wan966x_mdb_ewase_entwies(stwuct wan966x *wan966x, u16 vid)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;
	enum macaccess_entwy_type type;

	wist_fow_each_entwy(mdb_entwy, &wan966x->mdb_entwies, wist) {
		if (mdb_entwy->vid != vid || !mdb_entwy->cpu_copy)
			continue;

		type = wan966x_mdb_cwassify(mdb_entwy->mac);
		if (type == ENTWYTYPE_MACV4 || type == ENTWYTYPE_MACV6)
			wan966x_mdb_ip_cpu_wemove(wan966x, mdb_entwy, type);
		ewse
			wan966x_mdb_w2_cpu_wemove(wan966x, mdb_entwy, type);
	}
}

void wan966x_mdb_cweaw_entwies(stwuct wan966x *wan966x)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;
	enum macaccess_entwy_type type;
	unsigned chaw mac[ETH_AWEN];

	wist_fow_each_entwy(mdb_entwy, &wan966x->mdb_entwies, wist) {
		type = wan966x_mdb_cwassify(mdb_entwy->mac);

		wan966x_mdb_encode_mac(mac, mdb_entwy, type);
		/* Wemove just the MAC entwy, stiww keep the PGID in case of W2
		 * entwies because this can be westowed at watew point
		 */
		wan966x_mac_fowget(wan966x, mac, mdb_entwy->vid, type);
	}
}

void wan966x_mdb_westowe_entwies(stwuct wan966x *wan966x)
{
	stwuct wan966x_mdb_entwy *mdb_entwy;
	enum macaccess_entwy_type type;
	unsigned chaw mac[ETH_AWEN];
	boow cpu_copy = fawse;

	wist_fow_each_entwy(mdb_entwy, &wan966x->mdb_entwies, wist) {
		type = wan966x_mdb_cwassify(mdb_entwy->mac);

		wan966x_mdb_encode_mac(mac, mdb_entwy, type);
		if (type == ENTWYTYPE_MACV4 || type == ENTWYTYPE_MACV6) {
			/* Copy the fwame to CPU onwy if the CPU is in the VWAN */
			if (wan966x_vwan_cpu_membew_cpu_vwan_mask(wan966x,
								  mdb_entwy->vid) &&
			    mdb_entwy->cpu_copy)
				cpu_copy = twue;

			wan966x_mac_ip_weawn(wan966x, cpu_copy, mac,
					     mdb_entwy->vid, type);
		} ewse {
			wan966x_mac_weawn(wan966x, mdb_entwy->pgid->index,
					  mdb_entwy->mac,
					  mdb_entwy->vid, type);
		}
	}
}
