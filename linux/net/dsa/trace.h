/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight 2022-2023 NXP
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM	dsa

#if !defined(_NET_DSA_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _NET_DSA_TWACE_H

#incwude <net/dsa.h>
#incwude <net/switchdev.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wefcount.h>
#incwude <winux/twacepoint.h>

/* Enough to fit "bwidge %s num %d" whewe num has 3 digits */
#define DSA_DB_BUFSIZ	(IFNAMSIZ + 16)

void dsa_db_pwint(const stwuct dsa_db *db, chaw buf[DSA_DB_BUFSIZ]);
const chaw *dsa_powt_kind(const stwuct dsa_powt *dp);

DECWAWE_EVENT_CWASS(dsa_powt_addw_op_hw,

	TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw, u16 vid,
		 const stwuct dsa_db *db, int eww),

	TP_AWGS(dp, addw, vid, db, eww),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->eww = eww;
	),

	TP_pwintk("%s %s powt %d addw %pM vid %u db \"%s\" eww %d",
		  __get_stw(dev), __get_stw(kind), __entwy->powt, __entwy->addw,
		  __entwy->vid, __entwy->db_buf, __entwy->eww)
);

/* Add unicast/muwticast addwess to hawdwawe, eithew on usew powts
 * (whewe no wefcounting is kept), ow on shawed powts when the entwy
 * is fiwst seen and its wefcount is 1.
 */
DEFINE_EVENT(dsa_powt_addw_op_hw, dsa_fdb_add_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db, int eww),
	     TP_AWGS(dp, addw, vid, db, eww));

DEFINE_EVENT(dsa_powt_addw_op_hw, dsa_mdb_add_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db, int eww),
	     TP_AWGS(dp, addw, vid, db, eww));

/* Dewete unicast/muwticast addwess fwom hawdwawe, eithew on usew powts ow
 * when the wefcount on shawed powts weaches 0
 */
DEFINE_EVENT(dsa_powt_addw_op_hw, dsa_fdb_dew_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db, int eww),
	     TP_AWGS(dp, addw, vid, db, eww));

DEFINE_EVENT(dsa_powt_addw_op_hw, dsa_mdb_dew_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db, int eww),
	     TP_AWGS(dp, addw, vid, db, eww));

DECWAWE_EVENT_CWASS(dsa_powt_addw_op_wefcount,

	TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw, u16 vid,
		 const stwuct dsa_db *db, const wefcount_t *wefcount),

	TP_AWGS(dp, addw, vid, db, wefcount),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->wefcount = wefcount_wead(wefcount);
	),

	TP_pwintk("%s %s powt %d addw %pM vid %u db \"%s\" wefcount %u",
		  __get_stw(dev), __get_stw(kind), __entwy->powt, __entwy->addw,
		  __entwy->vid, __entwy->db_buf, __entwy->wefcount)
);

/* Bump the wefcount of an existing unicast/muwticast addwess on shawed powts */
DEFINE_EVENT(dsa_powt_addw_op_wefcount, dsa_fdb_add_bump,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, addw, vid, db, wefcount));

DEFINE_EVENT(dsa_powt_addw_op_wefcount, dsa_mdb_add_bump,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, addw, vid, db, wefcount));

/* Dwop the wefcount of a muwticast addwess that we stiww keep on
 * shawed powts
 */
DEFINE_EVENT(dsa_powt_addw_op_wefcount, dsa_fdb_dew_dwop,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, addw, vid, db, wefcount));

DEFINE_EVENT(dsa_powt_addw_op_wefcount, dsa_mdb_dew_dwop,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, addw, vid, db, wefcount));

DECWAWE_EVENT_CWASS(dsa_powt_addw_dew_not_found,

	TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw, u16 vid,
		 const stwuct dsa_db *db),

	TP_AWGS(dp, addw, vid, db),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
	),

	TP_pwintk("%s %s powt %d addw %pM vid %u db \"%s\"",
		  __get_stw(dev), __get_stw(kind), __entwy->powt,
		  __entwy->addw, __entwy->vid, __entwy->db_buf)
);

/* Attempt to dewete a unicast/muwticast addwess on shawed powts fow which
 * the dewete opewation was cawwed mowe times than the addition
 */
DEFINE_EVENT(dsa_powt_addw_dew_not_found, dsa_fdb_dew_not_found,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db),
	     TP_AWGS(dp, addw, vid, db));

DEFINE_EVENT(dsa_powt_addw_dew_not_found, dsa_mdb_dew_not_found,
	     TP_PWOTO(const stwuct dsa_powt *dp, const unsigned chaw *addw,
		      u16 vid, const stwuct dsa_db *db),
	     TP_AWGS(dp, addw, vid, db));

TWACE_EVENT(dsa_wag_fdb_add_hw,

	TP_PWOTO(const stwuct net_device *wag_dev, const unsigned chaw *addw,
		 u16 vid, const stwuct dsa_db *db, int eww),

	TP_AWGS(wag_dev, addw, vid, db, eww),

	TP_STWUCT__entwy(
		__stwing(dev, wag_dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__assign_stw(dev, wag_dev->name);
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->eww = eww;
	),

	TP_pwintk("%s addw %pM vid %u db \"%s\" eww %d",
		  __get_stw(dev), __entwy->addw, __entwy->vid,
		  __entwy->db_buf, __entwy->eww)
);

TWACE_EVENT(dsa_wag_fdb_add_bump,

	TP_PWOTO(const stwuct net_device *wag_dev, const unsigned chaw *addw,
		 u16 vid, const stwuct dsa_db *db, const wefcount_t *wefcount),

	TP_AWGS(wag_dev, addw, vid, db, wefcount),

	TP_STWUCT__entwy(
		__stwing(dev, wag_dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__assign_stw(dev, wag_dev->name);
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->wefcount = wefcount_wead(wefcount);
	),

	TP_pwintk("%s addw %pM vid %u db \"%s\" wefcount %u",
		  __get_stw(dev), __entwy->addw, __entwy->vid,
		  __entwy->db_buf, __entwy->wefcount)
);

TWACE_EVENT(dsa_wag_fdb_dew_hw,

	TP_PWOTO(const stwuct net_device *wag_dev, const unsigned chaw *addw,
		 u16 vid, const stwuct dsa_db *db, int eww),

	TP_AWGS(wag_dev, addw, vid, db, eww),

	TP_STWUCT__entwy(
		__stwing(dev, wag_dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__assign_stw(dev, wag_dev->name);
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->eww = eww;
	),

	TP_pwintk("%s addw %pM vid %u db \"%s\" eww %d",
		  __get_stw(dev), __entwy->addw, __entwy->vid,
		  __entwy->db_buf, __entwy->eww)
);

TWACE_EVENT(dsa_wag_fdb_dew_dwop,

	TP_PWOTO(const stwuct net_device *wag_dev, const unsigned chaw *addw,
		 u16 vid, const stwuct dsa_db *db, const wefcount_t *wefcount),

	TP_AWGS(wag_dev, addw, vid, db, wefcount),

	TP_STWUCT__entwy(
		__stwing(dev, wag_dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__assign_stw(dev, wag_dev->name);
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
		__entwy->wefcount = wefcount_wead(wefcount);
	),

	TP_pwintk("%s addw %pM vid %u db \"%s\" wefcount %u",
		  __get_stw(dev), __entwy->addw, __entwy->vid,
		  __entwy->db_buf, __entwy->wefcount)
);

TWACE_EVENT(dsa_wag_fdb_dew_not_found,

	TP_PWOTO(const stwuct net_device *wag_dev, const unsigned chaw *addw,
		 u16 vid, const stwuct dsa_db *db),

	TP_AWGS(wag_dev, addw, vid, db),

	TP_STWUCT__entwy(
		__stwing(dev, wag_dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__awway(chaw, db_buf, DSA_DB_BUFSIZ)
	),

	TP_fast_assign(
		__assign_stw(dev, wag_dev->name);
		ethew_addw_copy(__entwy->addw, addw);
		__entwy->vid = vid;
		dsa_db_pwint(db, __entwy->db_buf);
	),

	TP_pwintk("%s addw %pM vid %u db \"%s\"",
		  __get_stw(dev), __entwy->addw, __entwy->vid, __entwy->db_buf)
);

DECWAWE_EVENT_CWASS(dsa_vwan_op_hw,

	TP_PWOTO(const stwuct dsa_powt *dp,
		 const stwuct switchdev_obj_powt_vwan *vwan, int eww),

	TP_AWGS(dp, vwan, eww),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__fiewd(u16, vid)
		__fiewd(u16, fwags)
		__fiewd(boow, changed)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		__entwy->vid = vwan->vid;
		__entwy->fwags = vwan->fwags;
		__entwy->changed = vwan->changed;
		__entwy->eww = eww;
	),

	TP_pwintk("%s %s powt %d vid %u%s%s%s",
		  __get_stw(dev), __get_stw(kind), __entwy->powt, __entwy->vid,
		  __entwy->fwags & BWIDGE_VWAN_INFO_PVID ? " pvid" : "",
		  __entwy->fwags & BWIDGE_VWAN_INFO_UNTAGGED ? " untagged" : "",
		  __entwy->changed ? " (changed)" : "")
);

DEFINE_EVENT(dsa_vwan_op_hw, dsa_vwan_add_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan, int eww),
	     TP_AWGS(dp, vwan, eww));

DEFINE_EVENT(dsa_vwan_op_hw, dsa_vwan_dew_hw,
	     TP_PWOTO(const stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan, int eww),
	     TP_AWGS(dp, vwan, eww));

DECWAWE_EVENT_CWASS(dsa_vwan_op_wefcount,

	TP_PWOTO(const stwuct dsa_powt *dp,
		 const stwuct switchdev_obj_powt_vwan *vwan,
		 const wefcount_t *wefcount),

	TP_AWGS(dp, vwan, wefcount),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__fiewd(u16, vid)
		__fiewd(u16, fwags)
		__fiewd(boow, changed)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		__entwy->vid = vwan->vid;
		__entwy->fwags = vwan->fwags;
		__entwy->changed = vwan->changed;
		__entwy->wefcount = wefcount_wead(wefcount);
	),

	TP_pwintk("%s %s powt %d vid %u%s%s%s wefcount %u",
		  __get_stw(dev), __get_stw(kind), __entwy->powt, __entwy->vid,
		  __entwy->fwags & BWIDGE_VWAN_INFO_PVID ? " pvid" : "",
		  __entwy->fwags & BWIDGE_VWAN_INFO_UNTAGGED ? " untagged" : "",
		  __entwy->changed ? " (changed)" : "", __entwy->wefcount)
);

DEFINE_EVENT(dsa_vwan_op_wefcount, dsa_vwan_add_bump,
	     TP_PWOTO(const stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, vwan, wefcount));

DEFINE_EVENT(dsa_vwan_op_wefcount, dsa_vwan_dew_dwop,
	     TP_PWOTO(const stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan,
		      const wefcount_t *wefcount),
	     TP_AWGS(dp, vwan, wefcount));

TWACE_EVENT(dsa_vwan_dew_not_found,

	TP_PWOTO(const stwuct dsa_powt *dp,
		 const stwuct switchdev_obj_powt_vwan *vwan),

	TP_AWGS(dp, vwan),

	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dp->ds->dev))
		__stwing(kind, dsa_powt_kind(dp))
		__fiewd(int, powt)
		__fiewd(u16, vid)
	),

	TP_fast_assign(
		__assign_stw(dev, dev_name(dp->ds->dev));
		__assign_stw(kind, dsa_powt_kind(dp));
		__entwy->powt = dp->index;
		__entwy->vid = vwan->vid;
	),

	TP_pwintk("%s %s powt %d vid %u",
		  __get_stw(dev), __get_stw(kind), __entwy->powt, __entwy->vid)
);

#endif /* _NET_DSA_TWACE_H */

/* We don't want to use incwude/twace/events */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	twace
/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
