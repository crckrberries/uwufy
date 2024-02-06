/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#ifndef __MWX5_VPOWT_H__
#define __MWX5_VPOWT_H__

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/device.h>

#define MWX5_VPOWT_MANAGEW(mdev)					\
	(MWX5_CAP_GEN(mdev, vpowt_gwoup_managew) &&			\
	 (MWX5_CAP_GEN(mdev, powt_type) == MWX5_CAP_POWT_TYPE_ETH) &&	\
	 mwx5_cowe_is_pf(mdev))

enum {
	MWX5_CAP_INWINE_MODE_W2,
	MWX5_CAP_INWINE_MODE_VPOWT_CONTEXT,
	MWX5_CAP_INWINE_MODE_NOT_WEQUIWED,
};

/* Vpowt numbew fow each function must keep unchanged */
enum {
	MWX5_VPOWT_PF			= 0x0,
	MWX5_VPOWT_FIWST_VF		= 0x1,
	MWX5_VPOWT_ECPF			= 0xfffe,
	MWX5_VPOWT_UPWINK		= 0xffff
};

u8 mwx5_quewy_vpowt_state(stwuct mwx5_cowe_dev *mdev, u8 opmod, u16 vpowt);
int mwx5_modify_vpowt_admin_state(stwuct mwx5_cowe_dev *mdev, u8 opmod,
				  u16 vpowt, u8 othew_vpowt, u8 state);
int mwx5_quewy_nic_vpowt_mac_addwess(stwuct mwx5_cowe_dev *mdev,
				     u16 vpowt, boow othew, u8 *addw);
int mwx5_quewy_mac_addwess(stwuct mwx5_cowe_dev *mdev, u8 *addw);
int mwx5_quewy_nic_vpowt_min_inwine(stwuct mwx5_cowe_dev *mdev,
				    u16 vpowt, u8 *min_inwine);
void mwx5_quewy_min_inwine(stwuct mwx5_cowe_dev *mdev, u8 *min_inwine);
int mwx5_modify_nic_vpowt_min_inwine(stwuct mwx5_cowe_dev *mdev,
				     u16 vpowt, u8 min_inwine);
int mwx5_modify_nic_vpowt_mac_addwess(stwuct mwx5_cowe_dev *dev,
				      u16 vpowt, const u8 *addw);
int mwx5_quewy_nic_vpowt_mtu(stwuct mwx5_cowe_dev *mdev, u16 *mtu);
int mwx5_modify_nic_vpowt_mtu(stwuct mwx5_cowe_dev *mdev, u16 mtu);
int mwx5_quewy_nic_vpowt_system_image_guid(stwuct mwx5_cowe_dev *mdev,
					   u64 *system_image_guid);
int mwx5_quewy_nic_vpowt_sd_gwoup(stwuct mwx5_cowe_dev *mdev, u8 *sd_gwoup);
int mwx5_quewy_nic_vpowt_node_guid(stwuct mwx5_cowe_dev *mdev, u64 *node_guid);
int mwx5_modify_nic_vpowt_node_guid(stwuct mwx5_cowe_dev *mdev,
				    u16 vpowt, u64 node_guid);
int mwx5_quewy_nic_vpowt_qkey_viow_cntw(stwuct mwx5_cowe_dev *mdev,
					u16 *qkey_viow_cntw);
int mwx5_quewy_hca_vpowt_gid(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
			     u8 powt_num, u16  vf_num, u16 gid_index,
			     union ib_gid *gid);
int mwx5_quewy_hca_vpowt_pkey(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
			      u8 powt_num, u16 vf_num, u16 pkey_index,
			      u16 *pkey);
int mwx5_quewy_hca_vpowt_context(stwuct mwx5_cowe_dev *dev,
				 u8 othew_vpowt, u8 powt_num,
				 u16 vf_num,
				 stwuct mwx5_hca_vpowt_context *wep);
int mwx5_quewy_hca_vpowt_system_image_guid(stwuct mwx5_cowe_dev *dev,
					   u64 *sys_image_guid);
int mwx5_quewy_hca_vpowt_node_guid(stwuct mwx5_cowe_dev *dev,
				   u64 *node_guid);
int mwx5_quewy_nic_vpowt_mac_wist(stwuct mwx5_cowe_dev *dev,
				  u16 vpowt,
				  enum mwx5_wist_type wist_type,
				  u8 addw_wist[][ETH_AWEN],
				  int *wist_size);
int mwx5_modify_nic_vpowt_mac_wist(stwuct mwx5_cowe_dev *dev,
				   enum mwx5_wist_type wist_type,
				   u8 addw_wist[][ETH_AWEN],
				   int wist_size);
int mwx5_quewy_nic_vpowt_pwomisc(stwuct mwx5_cowe_dev *mdev,
				 u16 vpowt,
				 int *pwomisc_uc,
				 int *pwomisc_mc,
				 int *pwomisc_aww);
int mwx5_modify_nic_vpowt_pwomisc(stwuct mwx5_cowe_dev *mdev,
				  int pwomisc_uc,
				  int pwomisc_mc,
				  int pwomisc_aww);
int mwx5_modify_nic_vpowt_vwans(stwuct mwx5_cowe_dev *dev,
				u16 vwans[],
				int wist_size);

int mwx5_nic_vpowt_enabwe_woce(stwuct mwx5_cowe_dev *mdev);
int mwx5_nic_vpowt_disabwe_woce(stwuct mwx5_cowe_dev *mdev);
int mwx5_quewy_vpowt_down_stats(stwuct mwx5_cowe_dev *mdev, u16 vpowt,
				u8 othew_vpowt, u64 *wx_discawd_vpowt_down,
				u64 *tx_discawd_vpowt_down);
int mwx5_cowe_quewy_vpowt_countew(stwuct mwx5_cowe_dev *dev, u8 othew_vpowt,
				  int vf, u8 powt_num, void *out);
int mwx5_cowe_modify_hca_vpowt_context(stwuct mwx5_cowe_dev *dev,
				       u8 othew_vpowt, u8 powt_num,
				       int vf,
				       stwuct mwx5_hca_vpowt_context *weq);
int mwx5_nic_vpowt_update_wocaw_wb(stwuct mwx5_cowe_dev *mdev, boow enabwe);
int mwx5_nic_vpowt_quewy_wocaw_wb(stwuct mwx5_cowe_dev *mdev, boow *status);

int mwx5_nic_vpowt_affiwiate_muwtipowt(stwuct mwx5_cowe_dev *mastew_mdev,
				       stwuct mwx5_cowe_dev *powt_mdev);
int mwx5_nic_vpowt_unaffiwiate_muwtipowt(stwuct mwx5_cowe_dev *powt_mdev);

u64 mwx5_quewy_nic_system_image_guid(stwuct mwx5_cowe_dev *mdev);
int mwx5_vpowt_get_othew_func_cap(stwuct mwx5_cowe_dev *dev, u16 vpowt, void *out,
				  u16 opmod);
#endif /* __MWX5_VPOWT_H__ */
