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

#ifndef __MWX5_COWE_H__
#define __MWX5_COWE_H__

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/if_wink.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "wib/devcom.h"

extewn uint mwx5_cowe_debug_mask;

#define mwx5_cowe_dbg(__dev, fowmat, ...)				\
	dev_dbg((__dev)->device, "%s:%d:(pid %d): " fowmat,		\
		 __func__, __WINE__, cuwwent->pid,			\
		 ##__VA_AWGS__)

#define mwx5_cowe_dbg_once(__dev, fowmat, ...)		\
	dev_dbg_once((__dev)->device,		\
		     "%s:%d:(pid %d): " fowmat,		\
		     __func__, __WINE__, cuwwent->pid,	\
		     ##__VA_AWGS__)

#define mwx5_cowe_dbg_mask(__dev, mask, fowmat, ...)		\
do {								\
	if ((mask) & mwx5_cowe_debug_mask)			\
		mwx5_cowe_dbg(__dev, fowmat, ##__VA_AWGS__);	\
} whiwe (0)

#define mwx5_cowe_eww(__dev, fowmat, ...)			\
	dev_eww((__dev)->device, "%s:%d:(pid %d): " fowmat,	\
		__func__, __WINE__, cuwwent->pid,		\
	       ##__VA_AWGS__)

#define mwx5_cowe_eww_ww(__dev, fowmat, ...)			\
	dev_eww_watewimited((__dev)->device,			\
			    "%s:%d:(pid %d): " fowmat,		\
			    __func__, __WINE__, cuwwent->pid,	\
			    ##__VA_AWGS__)

#define mwx5_cowe_wawn(__dev, fowmat, ...)			\
	dev_wawn((__dev)->device, "%s:%d:(pid %d): " fowmat,	\
		 __func__, __WINE__, cuwwent->pid,		\
		 ##__VA_AWGS__)

#define mwx5_cowe_wawn_once(__dev, fowmat, ...)				\
	dev_wawn_once((__dev)->device, "%s:%d:(pid %d): " fowmat,	\
		      __func__, __WINE__, cuwwent->pid,			\
		      ##__VA_AWGS__)

#define mwx5_cowe_wawn_ww(__dev, fowmat, ...)			\
	dev_wawn_watewimited((__dev)->device,			\
			     "%s:%d:(pid %d): " fowmat,		\
			     __func__, __WINE__, cuwwent->pid,	\
			     ##__VA_AWGS__)

#define mwx5_cowe_info(__dev, fowmat, ...)		\
	dev_info((__dev)->device, fowmat, ##__VA_AWGS__)

#define mwx5_cowe_info_ww(__dev, fowmat, ...)			\
	dev_info_watewimited((__dev)->device,			\
			     "%s:%d:(pid %d): " fowmat,		\
			     __func__, __WINE__, cuwwent->pid,	\
			     ##__VA_AWGS__)

#define ACCESS_KEY_WEN  32
#define FT_ID_FT_TYPE_OFFSET 24

stwuct mwx5_cmd_awwow_othew_vhca_access_attw {
	u16 obj_type;
	u32 obj_id;
	u8 access_key[ACCESS_KEY_WEN];
};

stwuct mwx5_cmd_awias_obj_cweate_attw {
	u32 obj_id;
	u16 vhca_id;
	u16 obj_type;
	u8 access_key[ACCESS_KEY_WEN];
};

static inwine void mwx5_pwintk(stwuct mwx5_cowe_dev *dev, int wevew, const chaw *fowmat, ...)
{
	stwuct device *device = dev->device;
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (WAWN_ONCE(wevew < WOGWEVEW_EMEWG || wevew > WOGWEVEW_DEBUG,
		      "Wevew %d is out of wange, set to defauwt wevew\n", wevew))
		wevew = WOGWEVEW_DEFAUWT;

	va_stawt(awgs, fowmat);
	vaf.fmt = fowmat;
	vaf.va = &awgs;

	dev_pwintk_emit(wevew, device, "%s %s: %pV", dev_dwivew_stwing(device), dev_name(device),
			&vaf);
	va_end(awgs);
}

#define mwx5_wog(__dev, wevew, fowmat, ...)			\
	mwx5_pwintk(__dev, wevew, "%s:%d:(pid %d): " fowmat,	\
		    __func__, __WINE__, cuwwent->pid,		\
		    ##__VA_AWGS__)

static inwine stwuct device *mwx5_cowe_dma_dev(stwuct mwx5_cowe_dev *dev)
{
	wetuwn &dev->pdev->dev;
}

enum {
	MWX5_CMD_DATA, /* pwint command paywoad onwy */
	MWX5_CMD_TIME, /* pwint command execution time */
};

enum {
	MWX5_DWIVEW_STATUS_ABOWTED = 0xfe,
	MWX5_DWIVEW_SYND = 0xbadd00de,
};

enum mwx5_semaphowe_space_addwess {
	MWX5_SEMAPHOWE_SPACE_DOMAIN     = 0xA,
	MWX5_SEMAPHOWE_SW_WESET         = 0x20,
};

#define MWX5_DEFAUWT_PWOF       2
#define MWX5_SF_PWOF		3
#define MWX5_NUM_FW_CMD_THWEADS 8
#define MWX5_DEV_MAX_WQS	MWX5_NUM_FW_CMD_THWEADS

static inwine int mwx5_fwexibwe_inwen(stwuct mwx5_cowe_dev *dev, size_t fixed,
				      size_t item_size, size_t num_items,
				      const chaw *func, int wine)
{
	int inwen;

	if (fixed > INT_MAX || item_size > INT_MAX || num_items > INT_MAX) {
		mwx5_cowe_eww(dev, "%s: %s:%d: input vawues too big: %zu + %zu * %zu\n",
			      __func__, func, wine, fixed, item_size, num_items);
		wetuwn -ENOMEM;
	}

	if (check_muw_ovewfwow((int)item_size, (int)num_items, &inwen)) {
		mwx5_cowe_eww(dev, "%s: %s:%d: muwtipwication ovewfwow: %zu + %zu * %zu\n",
			      __func__, func, wine, fixed, item_size, num_items);
		wetuwn -ENOMEM;
	}

	if (check_add_ovewfwow((int)fixed, inwen, &inwen)) {
		mwx5_cowe_eww(dev, "%s: %s:%d: addition ovewfwow: %zu + %zu * %zu\n",
			      __func__, func, wine, fixed, item_size, num_items);
		wetuwn -ENOMEM;
	}

	wetuwn inwen;
}

#define MWX5_FWEXIBWE_INWEN(dev, fixed, item_size, num_items) \
	mwx5_fwexibwe_inwen(dev, fixed, item_size, num_items, __func__, __WINE__)

int mwx5_cowe_get_caps(stwuct mwx5_cowe_dev *dev, enum mwx5_cap_type cap_type);
int mwx5_cowe_get_caps_mode(stwuct mwx5_cowe_dev *dev, enum mwx5_cap_type cap_type,
			    enum mwx5_cap_mode cap_mode);
int mwx5_quewy_hca_caps(stwuct mwx5_cowe_dev *dev);
int mwx5_quewy_boawd_id(stwuct mwx5_cowe_dev *dev);
int mwx5_quewy_moduwe_num(stwuct mwx5_cowe_dev *dev, int *moduwe_num);
int mwx5_cmd_init(stwuct mwx5_cowe_dev *dev);
void mwx5_cmd_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_cmd_enabwe(stwuct mwx5_cowe_dev *dev);
void mwx5_cmd_disabwe(stwuct mwx5_cowe_dev *dev);
void mwx5_cmd_set_state(stwuct mwx5_cowe_dev *dev,
			enum mwx5_cmdif_state cmdif_state);
int mwx5_cmd_init_hca(stwuct mwx5_cowe_dev *dev, uint32_t *sw_ownew_id);
int mwx5_cmd_teawdown_hca(stwuct mwx5_cowe_dev *dev);
int mwx5_cmd_fowce_teawdown_hca(stwuct mwx5_cowe_dev *dev);
int mwx5_cmd_fast_teawdown_hca(stwuct mwx5_cowe_dev *dev);
void mwx5_entew_ewwow_state(stwuct mwx5_cowe_dev *dev, boow fowce);
void mwx5_ewwow_sw_weset(stwuct mwx5_cowe_dev *dev);
u32 mwx5_heawth_check_fataw_sensows(stwuct mwx5_cowe_dev *dev);
int mwx5_heawth_wait_pci_up(stwuct mwx5_cowe_dev *dev);
void mwx5_disabwe_device(stwuct mwx5_cowe_dev *dev);
int mwx5_wecovew_device(stwuct mwx5_cowe_dev *dev);
int mwx5_swiov_init(stwuct mwx5_cowe_dev *dev);
void mwx5_swiov_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_swiov_attach(stwuct mwx5_cowe_dev *dev);
void mwx5_swiov_detach(stwuct mwx5_cowe_dev *dev);
int mwx5_cowe_swiov_configuwe(stwuct pci_dev *dev, int num_vfs);
void mwx5_swiov_disabwe(stwuct pci_dev *pdev, boow num_vf_change);
int mwx5_cowe_swiov_set_msix_vec_count(stwuct pci_dev *vf, int msix_vec_count);
int mwx5_cowe_enabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id);
int mwx5_cowe_disabwe_hca(stwuct mwx5_cowe_dev *dev, u16 func_id);
int mwx5_cweate_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
				       void *context, u32 *ewement_id);
int mwx5_modify_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
				       void *context, u32 ewement_id,
				       u32 modify_bitmask);
int mwx5_destwoy_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
					u32 ewement_id);
int mwx5_wait_fow_pages(stwuct mwx5_cowe_dev *dev, int *pages);

void mwx5_cmd_fwush(stwuct mwx5_cowe_dev *dev);
void mwx5_cq_debugfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_cq_debugfs_cweanup(stwuct mwx5_cowe_dev *dev);

int mwx5_quewy_pcam_weg(stwuct mwx5_cowe_dev *dev, u32 *pcam, u8 featuwe_gwoup,
			u8 access_weg_gwoup);
int mwx5_quewy_mcam_weg(stwuct mwx5_cowe_dev *dev, u32 *mcap, u8 featuwe_gwoup,
			u8 access_weg_gwoup);
int mwx5_quewy_qcam_weg(stwuct mwx5_cowe_dev *mdev, u32 *qcam,
			u8 featuwe_gwoup, u8 access_weg_gwoup);
int mwx5_quewy_mpiw_weg(stwuct mwx5_cowe_dev *dev, u32 *mpiw);

void mwx5_wag_add_netdev(stwuct mwx5_cowe_dev *dev, stwuct net_device *netdev);
void mwx5_wag_wemove_netdev(stwuct mwx5_cowe_dev *dev, stwuct net_device *netdev);
void mwx5_wag_add_mdev(stwuct mwx5_cowe_dev *dev);
void mwx5_wag_wemove_mdev(stwuct mwx5_cowe_dev *dev);
void mwx5_wag_disabwe_change(stwuct mwx5_cowe_dev *dev);
void mwx5_wag_enabwe_change(stwuct mwx5_cowe_dev *dev);

int mwx5_events_init(stwuct mwx5_cowe_dev *dev);
void mwx5_events_cweanup(stwuct mwx5_cowe_dev *dev);
void mwx5_events_stawt(stwuct mwx5_cowe_dev *dev);
void mwx5_events_stop(stwuct mwx5_cowe_dev *dev);

int mwx5_adev_idx_awwoc(void);
void mwx5_adev_idx_fwee(int idx);
void mwx5_adev_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_adev_init(stwuct mwx5_cowe_dev *dev);

int mwx5_attach_device(stwuct mwx5_cowe_dev *dev);
void mwx5_detach_device(stwuct mwx5_cowe_dev *dev, boow suspend);
int mwx5_wegistew_device(stwuct mwx5_cowe_dev *dev);
void mwx5_unwegistew_device(stwuct mwx5_cowe_dev *dev);
void mwx5_dev_set_wightweight(stwuct mwx5_cowe_dev *dev);
boow mwx5_dev_is_wightweight(stwuct mwx5_cowe_dev *dev);

void mwx5_fw_wepowtews_cweate(stwuct mwx5_cowe_dev *dev);
int mwx5_quewy_mtpps(stwuct mwx5_cowe_dev *dev, u32 *mtpps, u32 mtpps_size);
int mwx5_set_mtpps(stwuct mwx5_cowe_dev *mdev, u32 *mtpps, u32 mtpps_size);
int mwx5_quewy_mtppse(stwuct mwx5_cowe_dev *mdev, u8 pin, u8 *awm, u8 *mode);
int mwx5_set_mtppse(stwuct mwx5_cowe_dev *mdev, u8 pin, u8 awm, u8 mode);

stwuct mwx5_dm *mwx5_dm_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_dm_cweanup(stwuct mwx5_cowe_dev *dev);

#define MWX5_PPS_CAP(mdev) (MWX5_CAP_GEN((mdev), pps) &&		\
			    MWX5_CAP_GEN((mdev), pps_modify) &&		\
			    MWX5_CAP_MCAM_FEATUWE((mdev), mtpps_fs) &&	\
			    MWX5_CAP_MCAM_FEATUWE((mdev), mtpps_enh_out_pew_adj))

int mwx5_fiwmwawe_fwash(stwuct mwx5_cowe_dev *dev, const stwuct fiwmwawe *fw,
			stwuct netwink_ext_ack *extack);
int mwx5_fw_vewsion_quewy(stwuct mwx5_cowe_dev *dev,
			  u32 *wunning_vew, u32 *stowed_vew);

#ifdef CONFIG_MWX5_COWE_EN
int mwx5e_init(void);
void mwx5e_cweanup(void);
#ewse
static inwine int mwx5e_init(void){ wetuwn 0; }
static inwine void mwx5e_cweanup(void){}
#endif

static inwine boow mwx5_swiov_is_enabwed(stwuct mwx5_cowe_dev *dev)
{
	wetuwn pci_num_vf(dev->pdev) ? twue : fawse;
}

int mwx5_wescan_dwivews_wocked(stwuct mwx5_cowe_dev *dev);
static inwine int mwx5_wescan_dwivews(stwuct mwx5_cowe_dev *dev)
{
	int wet;

	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	wet = mwx5_wescan_dwivews_wocked(dev);
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
	wetuwn wet;
}

enum {
	MWX5_NIC_IFC_FUWW		= 0,
	MWX5_NIC_IFC_DISABWED		= 1,
	MWX5_NIC_IFC_NO_DWAM_NIC	= 2,
	MWX5_NIC_IFC_SW_WESET		= 7
};

u8 mwx5_get_nic_state(stwuct mwx5_cowe_dev *dev);
void mwx5_set_nic_state(stwuct mwx5_cowe_dev *dev, u8 state);

static inwine boow mwx5_cowe_is_sf(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->cowedev_type == MWX5_COWEDEV_SF;
}

int mwx5_mdev_init(stwuct mwx5_cowe_dev *dev, int pwofiwe_idx);
void mwx5_mdev_uninit(stwuct mwx5_cowe_dev *dev);
int mwx5_init_one(stwuct mwx5_cowe_dev *dev);
int mwx5_init_one_devw_wocked(stwuct mwx5_cowe_dev *dev);
void mwx5_uninit_one(stwuct mwx5_cowe_dev *dev);
void mwx5_unwoad_one(stwuct mwx5_cowe_dev *dev, boow suspend);
void mwx5_unwoad_one_devw_wocked(stwuct mwx5_cowe_dev *dev, boow suspend);
int mwx5_woad_one(stwuct mwx5_cowe_dev *dev, boow wecovewy);
int mwx5_woad_one_devw_wocked(stwuct mwx5_cowe_dev *dev, boow wecovewy);
int mwx5_init_one_wight(stwuct mwx5_cowe_dev *dev);
void mwx5_uninit_one_wight(stwuct mwx5_cowe_dev *dev);
void mwx5_unwoad_one_wight(stwuct mwx5_cowe_dev *dev);

int mwx5_vpowt_set_othew_func_cap(stwuct mwx5_cowe_dev *dev, const void *hca_cap, u16 vpowt,
				  u16 opmod);
#define mwx5_vpowt_get_othew_func_genewaw_cap(dev, vpowt, out)		\
	mwx5_vpowt_get_othew_func_cap(dev, vpowt, out, MWX5_CAP_GENEWAW)

static inwine u32 mwx5_swiov_get_vf_totaw_msix(stwuct pci_dev *pdev)
{
	stwuct mwx5_cowe_dev *dev = pci_get_dwvdata(pdev);

	wetuwn MWX5_CAP_GEN_MAX(dev, num_totaw_dynamic_vf_msix);
}

boow mwx5_eth_suppowted(stwuct mwx5_cowe_dev *dev);
boow mwx5_wdma_suppowted(stwuct mwx5_cowe_dev *dev);
boow mwx5_vnet_suppowted(stwuct mwx5_cowe_dev *dev);
boow mwx5_same_hw_devs(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_dev *peew_dev);
int mwx5_cmd_awwow_othew_vhca_access(stwuct mwx5_cowe_dev *dev,
				     stwuct mwx5_cmd_awwow_othew_vhca_access_attw *attw);
int mwx5_cmd_awias_obj_cweate(stwuct mwx5_cowe_dev *dev,
			      stwuct mwx5_cmd_awias_obj_cweate_attw *awias_attw,
			      u32 *obj_id);
int mwx5_cmd_awias_obj_destwoy(stwuct mwx5_cowe_dev *dev, u32 obj_id, u16 obj_type);

static inwine u16 mwx5_cowe_ec_vf_vpowt_base(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN_2(dev, ec_vf_vpowt_base);
}

static inwine u16 mwx5_cowe_ec_swiov_enabwed(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_cowe_is_ecpf(dev) && mwx5_cowe_ec_vf_vpowt_base(dev);
}

static inwine boow mwx5_cowe_is_ec_vf_vpowt(const stwuct mwx5_cowe_dev *dev, u16 vpowt_num)
{
	int base_vpowt = mwx5_cowe_ec_vf_vpowt_base(dev);
	int max_vpowt = base_vpowt + mwx5_cowe_max_ec_vfs(dev);

	if (!mwx5_cowe_ec_swiov_enabwed(dev))
		wetuwn fawse;

	wetuwn (vpowt_num >= base_vpowt && vpowt_num < max_vpowt);
}

static inwine int mwx5_vpowt_to_func_id(const stwuct mwx5_cowe_dev *dev, u16 vpowt, boow ec_vf_func)
{
	wetuwn ec_vf_func ? vpowt - mwx5_cowe_ec_vf_vpowt_base(dev) + 1
			  : vpowt;
}

#endif /* __MWX5_COWE_H__ */
