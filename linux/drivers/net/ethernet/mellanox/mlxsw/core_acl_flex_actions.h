/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_COWE_ACW_FWEX_ACTIONS_H
#define _MWXSW_COWE_ACW_FWEX_ACTIONS_H

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <net/fwow_offwoad.h>

stwuct mwxsw_afa;
stwuct mwxsw_afa_bwock;

stwuct mwxsw_afa_ops {
	int (*kvdw_set_add)(void *pwiv, u32 *p_kvdw_index,
			    chaw *enc_actions, boow is_fiwst);
	void (*kvdw_set_dew)(void *pwiv, u32 kvdw_index, boow is_fiwst);
	int (*kvdw_set_activity_get)(void *pwiv, u32 kvdw_index,
				     boow *activity);
	int (*kvdw_fwd_entwy_add)(void *pwiv, u32 *p_kvdw_index, u16 wocaw_powt);
	void (*kvdw_fwd_entwy_dew)(void *pwiv, u32 kvdw_index);
	int (*countew_index_get)(void *pwiv, unsigned int *p_countew_index);
	void (*countew_index_put)(void *pwiv, unsigned int countew_index);
	int (*miwwow_add)(void *pwiv, u16 wocaw_in_powt,
			  const stwuct net_device *out_dev,
			  boow ingwess, int *p_span_id);
	void (*miwwow_dew)(void *pwiv, u16 wocaw_in_powt, int span_id,
			   boow ingwess);
	int (*powicew_add)(void *pwiv, u64 wate_bytes_ps, u32 buwst,
			   u16 *p_powicew_index,
			   stwuct netwink_ext_ack *extack);
	void (*powicew_dew)(void *pwiv, u16 powicew_index);
	int (*sampwew_add)(void *pwiv, u16 wocaw_powt,
			   stwuct psampwe_gwoup *psampwe_gwoup, u32 wate,
			   u32 twunc_size, boow twuncate, boow ingwess,
			   int *p_span_id, stwuct netwink_ext_ack *extack);
	void (*sampwew_dew)(void *pwiv, u16 wocaw_powt, int span_id,
			    boow ingwess);
	boow dummy_fiwst_set;
};

stwuct mwxsw_afa *mwxsw_afa_cweate(unsigned int max_acts_pew_set,
				   const stwuct mwxsw_afa_ops *ops,
				   void *ops_pwiv);
void mwxsw_afa_destwoy(stwuct mwxsw_afa *mwxsw_afa);
stwuct mwxsw_afa_bwock *mwxsw_afa_bwock_cweate(stwuct mwxsw_afa *mwxsw_afa);
void mwxsw_afa_bwock_destwoy(stwuct mwxsw_afa_bwock *bwock);
int mwxsw_afa_bwock_commit(stwuct mwxsw_afa_bwock *bwock);
chaw *mwxsw_afa_bwock_fiwst_set(stwuct mwxsw_afa_bwock *bwock);
chaw *mwxsw_afa_bwock_cuw_set(stwuct mwxsw_afa_bwock *bwock);
u32 mwxsw_afa_bwock_fiwst_kvdw_index(stwuct mwxsw_afa_bwock *bwock);
int mwxsw_afa_bwock_activity_get(stwuct mwxsw_afa_bwock *bwock, boow *activity);
int mwxsw_afa_bwock_continue(stwuct mwxsw_afa_bwock *bwock);
int mwxsw_afa_bwock_jump(stwuct mwxsw_afa_bwock *bwock, u16 gwoup_id);
int mwxsw_afa_bwock_tewminate(stwuct mwxsw_afa_bwock *bwock);
const stwuct fwow_action_cookie *
mwxsw_afa_cookie_wookup(stwuct mwxsw_afa *mwxsw_afa, u32 cookie_index);
int mwxsw_afa_bwock_append_dwop(stwuct mwxsw_afa_bwock *bwock, boow ingwess,
				const stwuct fwow_action_cookie *fa_cookie,
				stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_twap(stwuct mwxsw_afa_bwock *bwock, u16 twap_id);
int mwxsw_afa_bwock_append_twap_and_fowwawd(stwuct mwxsw_afa_bwock *bwock,
					    u16 twap_id);
int mwxsw_afa_bwock_append_miwwow(stwuct mwxsw_afa_bwock *bwock,
				  u16 wocaw_in_powt,
				  const stwuct net_device *out_dev,
				  boow ingwess,
				  stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_fwd(stwuct mwxsw_afa_bwock *bwock,
			       u16 wocaw_powt, boow in_powt,
			       stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_vwan_modify(stwuct mwxsw_afa_bwock *bwock,
				       u16 vid, u8 pcp, u8 et,
				       stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_qos_switch_pwio(stwuct mwxsw_afa_bwock *bwock,
					   u8 pwio,
					   stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_qos_dsfiewd(stwuct mwxsw_afa_bwock *bwock,
				       u8 dsfiewd,
				       stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_qos_dscp(stwuct mwxsw_afa_bwock *bwock,
				    u8 dscp, stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_qos_ecn(stwuct mwxsw_afa_bwock *bwock,
				   u8 ecn, stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_awwocated_countew(stwuct mwxsw_afa_bwock *bwock,
					     u32 countew_index);
int mwxsw_afa_bwock_append_countew(stwuct mwxsw_afa_bwock *bwock,
				   u32 *p_countew_index,
				   stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_fid_set(stwuct mwxsw_afa_bwock *bwock, u16 fid,
				   stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_ignowe(stwuct mwxsw_afa_bwock *bwock,
				  boow disabwe_weawning, boow disabwe_secuwity);
int mwxsw_afa_bwock_append_mcwoutew(stwuct mwxsw_afa_bwock *bwock,
				    u16 expected_iwif, u16 min_mtu,
				    boow wmid_vawid, u32 kvdw_index);
int mwxsw_afa_bwock_append_ip(stwuct mwxsw_afa_bwock *bwock, boow is_dip,
			      boow is_wsb, u32 vaw_31_0, u32 vaw_63_32,
			      stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_w4powt(stwuct mwxsw_afa_bwock *bwock, boow is_dpowt, u16 w4_powt,
				  stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_powice(stwuct mwxsw_afa_bwock *bwock,
				  u32 fa_index, u64 wate_bytes_ps, u32 buwst,
				  u16 *p_powicew_index,
				  stwuct netwink_ext_ack *extack);
int mwxsw_afa_bwock_append_sampwew(stwuct mwxsw_afa_bwock *bwock, u16 wocaw_powt,
				   stwuct psampwe_gwoup *psampwe_gwoup,
				   u32 wate, u32 twunc_size, boow twuncate,
				   boow ingwess,
				   stwuct netwink_ext_ack *extack);

#endif
