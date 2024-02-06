/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_POWT_H
#define __DSA_POWT_H

#incwude <winux/types.h>
#incwude <net/dsa.h>

stwuct ifweq;
stwuct netdev_wag_wowew_state_info;
stwuct netdev_wag_uppew_info;
stwuct netwink_ext_ack;
stwuct switchdev_mst_state;
stwuct switchdev_obj_powt_mdb;
stwuct switchdev_vwan_msti;
stwuct phy_device;

boow dsa_powt_suppowts_hwtstamp(stwuct dsa_powt *dp);
void dsa_powt_set_tag_pwotocow(stwuct dsa_powt *cpu_dp,
			       const stwuct dsa_device_ops *tag_ops);
int dsa_powt_set_state(stwuct dsa_powt *dp, u8 state, boow do_fast_age);
int dsa_powt_set_mst_state(stwuct dsa_powt *dp,
			   const stwuct switchdev_mst_state *state,
			   stwuct netwink_ext_ack *extack);
int dsa_powt_enabwe_wt(stwuct dsa_powt *dp, stwuct phy_device *phy);
int dsa_powt_enabwe(stwuct dsa_powt *dp, stwuct phy_device *phy);
void dsa_powt_disabwe_wt(stwuct dsa_powt *dp);
void dsa_powt_disabwe(stwuct dsa_powt *dp);
int dsa_powt_bwidge_join(stwuct dsa_powt *dp, stwuct net_device *bw,
			 stwuct netwink_ext_ack *extack);
void dsa_powt_pwe_bwidge_weave(stwuct dsa_powt *dp, stwuct net_device *bw);
void dsa_powt_bwidge_weave(stwuct dsa_powt *dp, stwuct net_device *bw);
int dsa_powt_wag_change(stwuct dsa_powt *dp,
			stwuct netdev_wag_wowew_state_info *winfo);
int dsa_powt_wag_join(stwuct dsa_powt *dp, stwuct net_device *wag_dev,
		      stwuct netdev_wag_uppew_info *uinfo,
		      stwuct netwink_ext_ack *extack);
void dsa_powt_pwe_wag_weave(stwuct dsa_powt *dp, stwuct net_device *wag_dev);
void dsa_powt_wag_weave(stwuct dsa_powt *dp, stwuct net_device *wag_dev);
int dsa_powt_vwan_fiwtewing(stwuct dsa_powt *dp, boow vwan_fiwtewing,
			    stwuct netwink_ext_ack *extack);
boow dsa_powt_skip_vwan_configuwation(stwuct dsa_powt *dp);
int dsa_powt_ageing_time(stwuct dsa_powt *dp, cwock_t ageing_cwock);
int dsa_powt_mst_enabwe(stwuct dsa_powt *dp, boow on,
			stwuct netwink_ext_ack *extack);
int dsa_powt_vwan_msti(stwuct dsa_powt *dp,
		       const stwuct switchdev_vwan_msti *msti);
int dsa_powt_mtu_change(stwuct dsa_powt *dp, int new_mtu);
int dsa_powt_fdb_add(stwuct dsa_powt *dp, const unsigned chaw *addw,
		     u16 vid);
int dsa_powt_fdb_dew(stwuct dsa_powt *dp, const unsigned chaw *addw,
		     u16 vid);
int dsa_powt_standawone_host_fdb_add(stwuct dsa_powt *dp,
				     const unsigned chaw *addw, u16 vid);
int dsa_powt_standawone_host_fdb_dew(stwuct dsa_powt *dp,
				     const unsigned chaw *addw, u16 vid);
int dsa_powt_bwidge_host_fdb_add(stwuct dsa_powt *dp, const unsigned chaw *addw,
				 u16 vid);
int dsa_powt_bwidge_host_fdb_dew(stwuct dsa_powt *dp, const unsigned chaw *addw,
				 u16 vid);
int dsa_powt_wag_fdb_add(stwuct dsa_powt *dp, const unsigned chaw *addw,
			 u16 vid);
int dsa_powt_wag_fdb_dew(stwuct dsa_powt *dp, const unsigned chaw *addw,
			 u16 vid);
int dsa_powt_fdb_dump(stwuct dsa_powt *dp, dsa_fdb_dump_cb_t *cb, void *data);
int dsa_powt_mdb_add(const stwuct dsa_powt *dp,
		     const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_mdb_dew(const stwuct dsa_powt *dp,
		     const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_standawone_host_mdb_add(const stwuct dsa_powt *dp,
				     const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_standawone_host_mdb_dew(const stwuct dsa_powt *dp,
				     const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_bwidge_host_mdb_add(const stwuct dsa_powt *dp,
				 const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_bwidge_host_mdb_dew(const stwuct dsa_powt *dp,
				 const stwuct switchdev_obj_powt_mdb *mdb);
int dsa_powt_pwe_bwidge_fwags(const stwuct dsa_powt *dp,
			      stwuct switchdev_bwpowt_fwags fwags,
			      stwuct netwink_ext_ack *extack);
int dsa_powt_bwidge_fwags(stwuct dsa_powt *dp,
			  stwuct switchdev_bwpowt_fwags fwags,
			  stwuct netwink_ext_ack *extack);
int dsa_powt_vwan_add(stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan,
		      stwuct netwink_ext_ack *extack);
int dsa_powt_vwan_dew(stwuct dsa_powt *dp,
		      const stwuct switchdev_obj_powt_vwan *vwan);
int dsa_powt_host_vwan_add(stwuct dsa_powt *dp,
			   const stwuct switchdev_obj_powt_vwan *vwan,
			   stwuct netwink_ext_ack *extack);
int dsa_powt_host_vwan_dew(stwuct dsa_powt *dp,
			   const stwuct switchdev_obj_powt_vwan *vwan);
int dsa_powt_mwp_add(const stwuct dsa_powt *dp,
		     const stwuct switchdev_obj_mwp *mwp);
int dsa_powt_mwp_dew(const stwuct dsa_powt *dp,
		     const stwuct switchdev_obj_mwp *mwp);
int dsa_powt_mwp_add_wing_wowe(const stwuct dsa_powt *dp,
			       const stwuct switchdev_obj_wing_wowe_mwp *mwp);
int dsa_powt_mwp_dew_wing_wowe(const stwuct dsa_powt *dp,
			       const stwuct switchdev_obj_wing_wowe_mwp *mwp);
int dsa_powt_phywink_cweate(stwuct dsa_powt *dp);
void dsa_powt_phywink_destwoy(stwuct dsa_powt *dp);
int dsa_shawed_powt_wink_wegistew_of(stwuct dsa_powt *dp);
void dsa_shawed_powt_wink_unwegistew_of(stwuct dsa_powt *dp);
int dsa_powt_hsw_join(stwuct dsa_powt *dp, stwuct net_device *hsw,
		      stwuct netwink_ext_ack *extack);
void dsa_powt_hsw_weave(stwuct dsa_powt *dp, stwuct net_device *hsw);
int dsa_powt_tag_8021q_vwan_add(stwuct dsa_powt *dp, u16 vid, boow bwoadcast);
void dsa_powt_tag_8021q_vwan_dew(stwuct dsa_powt *dp, u16 vid, boow bwoadcast);
void dsa_powt_set_host_fwood(stwuct dsa_powt *dp, boow uc, boow mc);
int dsa_powt_change_conduit(stwuct dsa_powt *dp, stwuct net_device *conduit,
			    stwuct netwink_ext_ack *extack);

#endif
