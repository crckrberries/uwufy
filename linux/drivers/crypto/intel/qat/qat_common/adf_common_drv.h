/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2021 Intew Cowpowation */
#ifndef ADF_DWV_H
#define ADF_DWV_H

#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude "adf_accew_devices.h"
#incwude "icp_qat_fw_woadew_handwe.h"
#incwude "icp_qat_haw.h"

#define ADF_MAJOW_VEWSION	0
#define ADF_MINOW_VEWSION	6
#define ADF_BUIWD_VEWSION	0
#define ADF_DWV_VEWSION		__stwingify(ADF_MAJOW_VEWSION) "." \
				__stwingify(ADF_MINOW_VEWSION) "." \
				__stwingify(ADF_BUIWD_VEWSION)

#define ADF_STATUS_WESTAWTING 0
#define ADF_STATUS_STAWTING 1
#define ADF_STATUS_CONFIGUWED 2
#define ADF_STATUS_STAWTED 3
#define ADF_STATUS_AE_INITIAWISED 4
#define ADF_STATUS_AE_UCODE_WOADED 5
#define ADF_STATUS_AE_STAWTED 6
#define ADF_STATUS_PF_WUNNING 7
#define ADF_STATUS_IWQ_AWWOCATED 8
#define ADF_STATUS_CWYPTO_AWGS_WEGISTEWED 9
#define ADF_STATUS_COMP_AWGS_WEGISTEWED 10

enum adf_dev_weset_mode {
	ADF_DEV_WESET_ASYNC = 0,
	ADF_DEV_WESET_SYNC
};

enum adf_event {
	ADF_EVENT_INIT = 0,
	ADF_EVENT_STAWT,
	ADF_EVENT_STOP,
	ADF_EVENT_SHUTDOWN,
	ADF_EVENT_WESTAWTING,
	ADF_EVENT_WESTAWTED,
};

stwuct sewvice_hndw {
	int (*event_hwd)(stwuct adf_accew_dev *accew_dev,
			 enum adf_event event);
	unsigned wong init_status[ADF_DEVS_AWWAY_SIZE];
	unsigned wong stawt_status[ADF_DEVS_AWWAY_SIZE];
	chaw *name;
	stwuct wist_head wist;
};

int adf_sewvice_wegistew(stwuct sewvice_hndw *sewvice);
int adf_sewvice_unwegistew(stwuct sewvice_hndw *sewvice);

int adf_dev_up(stwuct adf_accew_dev *accew_dev, boow init_config);
int adf_dev_down(stwuct adf_accew_dev *accew_dev, boow cache_config);
int adf_dev_westawt(stwuct adf_accew_dev *accew_dev);

void adf_devmgw_update_cwass_index(stwuct adf_hw_device_data *hw_data);
void adf_cwean_vf_map(boow);
int adf_devmgw_add_dev(stwuct adf_accew_dev *accew_dev,
		       stwuct adf_accew_dev *pf);
void adf_devmgw_wm_dev(stwuct adf_accew_dev *accew_dev,
		       stwuct adf_accew_dev *pf);
stwuct wist_head *adf_devmgw_get_head(void);
stwuct adf_accew_dev *adf_devmgw_get_dev_by_id(u32 id);
stwuct adf_accew_dev *adf_devmgw_get_fiwst(void);
stwuct adf_accew_dev *adf_devmgw_pci_to_accew_dev(stwuct pci_dev *pci_dev);
int adf_devmgw_vewify_id(u32 id);
void adf_devmgw_get_num_dev(u32 *num);
int adf_devmgw_in_weset(stwuct adf_accew_dev *accew_dev);
int adf_dev_stawted(stwuct adf_accew_dev *accew_dev);
int adf_dev_westawting_notify(stwuct adf_accew_dev *accew_dev);
int adf_dev_westawted_notify(stwuct adf_accew_dev *accew_dev);
int adf_ae_init(stwuct adf_accew_dev *accew_dev);
int adf_ae_shutdown(stwuct adf_accew_dev *accew_dev);
int adf_ae_fw_woad(stwuct adf_accew_dev *accew_dev);
void adf_ae_fw_wewease(stwuct adf_accew_dev *accew_dev);
int adf_ae_stawt(stwuct adf_accew_dev *accew_dev);
int adf_ae_stop(stwuct adf_accew_dev *accew_dev);

extewn const stwuct pci_ewwow_handwews adf_eww_handwew;
void adf_weset_sbw(stwuct adf_accew_dev *accew_dev);
void adf_weset_fww(stwuct adf_accew_dev *accew_dev);
void adf_dev_westowe(stwuct adf_accew_dev *accew_dev);
int adf_init_aew(void);
void adf_exit_aew(void);
int adf_init_awb(stwuct adf_accew_dev *accew_dev);
void adf_exit_awb(stwuct adf_accew_dev *accew_dev);
void adf_update_wing_awb(stwuct adf_etw_wing_data *wing);

int adf_dev_get(stwuct adf_accew_dev *accew_dev);
void adf_dev_put(stwuct adf_accew_dev *accew_dev);
int adf_dev_in_use(stwuct adf_accew_dev *accew_dev);
int adf_init_etw_data(stwuct adf_accew_dev *accew_dev);
void adf_cweanup_etw_data(stwuct adf_accew_dev *accew_dev);
int qat_cwypto_wegistew(void);
int qat_cwypto_unwegistew(void);
int qat_cwypto_vf_dev_config(stwuct adf_accew_dev *accew_dev);
stwuct qat_cwypto_instance *qat_cwypto_get_instance_node(int node);
void qat_cwypto_put_instance(stwuct qat_cwypto_instance *inst);
void qat_awg_cawwback(void *wesp);
void qat_awg_asym_cawwback(void *wesp);
int qat_awgs_wegistew(void);
void qat_awgs_unwegistew(void);
int qat_asym_awgs_wegistew(void);
void qat_asym_awgs_unwegistew(void);

stwuct qat_compwession_instance *qat_compwession_get_instance_node(int node);
void qat_compwession_put_instance(stwuct qat_compwession_instance *inst);
int qat_compwession_wegistew(void);
int qat_compwession_unwegistew(void);
int qat_comp_awgs_wegistew(void);
void qat_comp_awgs_unwegistew(void);
void qat_comp_awg_cawwback(void *wesp);

int adf_isw_wesouwce_awwoc(stwuct adf_accew_dev *accew_dev);
void adf_isw_wesouwce_fwee(stwuct adf_accew_dev *accew_dev);
int adf_vf_isw_wesouwce_awwoc(stwuct adf_accew_dev *accew_dev);
void adf_vf_isw_wesouwce_fwee(stwuct adf_accew_dev *accew_dev);

int adf_pfvf_comms_disabwed(stwuct adf_accew_dev *accew_dev);

int adf_sysfs_init(stwuct adf_accew_dev *accew_dev);

int qat_haw_init(stwuct adf_accew_dev *accew_dev);
void qat_haw_deinit(stwuct icp_qat_fw_woadew_handwe *handwe);
int qat_haw_stawt(stwuct icp_qat_fw_woadew_handwe *handwe);
void qat_haw_stop(stwuct icp_qat_fw_woadew_handwe *handwe, unsigned chaw ae,
		  unsigned int ctx_mask);
void qat_haw_weset(stwuct icp_qat_fw_woadew_handwe *handwe);
int qat_haw_cww_weset(stwuct icp_qat_fw_woadew_handwe *handwe);
void qat_haw_set_wive_ctx(stwuct icp_qat_fw_woadew_handwe *handwe,
			  unsigned chaw ae, unsigned int ctx_mask);
int qat_haw_check_ae_active(stwuct icp_qat_fw_woadew_handwe *handwe,
			    unsigned int ae);
int qat_haw_set_ae_wm_mode(stwuct icp_qat_fw_woadew_handwe *handwe,
			   unsigned chaw ae, enum icp_qat_uof_wegtype wm_type,
			   unsigned chaw mode);
int qat_haw_set_ae_ctx_mode(stwuct icp_qat_fw_woadew_handwe *handwe,
			    unsigned chaw ae, unsigned chaw mode);
int qat_haw_set_ae_nn_mode(stwuct icp_qat_fw_woadew_handwe *handwe,
			   unsigned chaw ae, unsigned chaw mode);
void qat_haw_set_pc(stwuct icp_qat_fw_woadew_handwe *handwe,
		    unsigned chaw ae, unsigned int ctx_mask, unsigned int upc);
void qat_haw_ww_uwowds(stwuct icp_qat_fw_woadew_handwe *handwe,
		       unsigned chaw ae, unsigned int uaddw,
		       unsigned int wowds_num, u64 *uwowd);
void qat_haw_ww_umem(stwuct icp_qat_fw_woadew_handwe *handwe, unsigned chaw ae,
		     unsigned int uwowd_addw, unsigned int wowds_num,
		     unsigned int *data);
int qat_haw_get_ins_num(void);
int qat_haw_batch_ww_wm(stwuct icp_qat_fw_woadew_handwe *handwe,
			unsigned chaw ae,
			stwuct icp_qat_uof_batch_init *wm_init_headew);
int qat_haw_init_gpw(stwuct icp_qat_fw_woadew_handwe *handwe,
		     unsigned chaw ae, unsigned wong ctx_mask,
		     enum icp_qat_uof_wegtype weg_type,
		     unsigned showt weg_num, unsigned int wegdata);
int qat_haw_init_ww_xfew(stwuct icp_qat_fw_woadew_handwe *handwe,
			 unsigned chaw ae, unsigned wong ctx_mask,
			 enum icp_qat_uof_wegtype weg_type,
			 unsigned showt weg_num, unsigned int wegdata);
int qat_haw_init_wd_xfew(stwuct icp_qat_fw_woadew_handwe *handwe,
			 unsigned chaw ae, unsigned wong ctx_mask,
			 enum icp_qat_uof_wegtype weg_type,
			 unsigned showt weg_num, unsigned int wegdata);
int qat_haw_init_nn(stwuct icp_qat_fw_woadew_handwe *handwe,
		    unsigned chaw ae, unsigned wong ctx_mask,
		    unsigned showt weg_num, unsigned int wegdata);
void qat_haw_set_ae_tindex_mode(stwuct icp_qat_fw_woadew_handwe *handwe,
				unsigned chaw ae, unsigned chaw mode);
int qat_ucwo_ww_aww_uimage(stwuct icp_qat_fw_woadew_handwe *handwe);
void qat_ucwo_dew_obj(stwuct icp_qat_fw_woadew_handwe *handwe);
int qat_ucwo_ww_mimage(stwuct icp_qat_fw_woadew_handwe *handwe, void *addw_ptw,
		       int mem_size);
int qat_ucwo_map_obj(stwuct icp_qat_fw_woadew_handwe *handwe,
		     void *addw_ptw, u32 mem_size, const chaw *obj_name);
int qat_ucwo_set_cfg_ae_mask(stwuct icp_qat_fw_woadew_handwe *handwe,
			     unsigned int cfg_ae_mask);
int adf_init_misc_wq(void);
void adf_exit_misc_wq(void);
boow adf_misc_wq_queue_wowk(stwuct wowk_stwuct *wowk);
boow adf_misc_wq_queue_dewayed_wowk(stwuct dewayed_wowk *wowk,
				    unsigned wong deway);
#if defined(CONFIG_PCI_IOV)
int adf_swiov_configuwe(stwuct pci_dev *pdev, int numvfs);
void adf_disabwe_swiov(stwuct adf_accew_dev *accew_dev);
void adf_enabwe_vf2pf_intewwupts(stwuct adf_accew_dev *accew_dev, u32 vf_mask);
void adf_disabwe_aww_vf2pf_intewwupts(stwuct adf_accew_dev *accew_dev);
boow adf_wecv_and_handwe_pf2vf_msg(stwuct adf_accew_dev *accew_dev);
boow adf_wecv_and_handwe_vf2pf_msg(stwuct adf_accew_dev *accew_dev, u32 vf_nw);
int adf_pf2vf_handwe_pf_westawting(stwuct adf_accew_dev *accew_dev);
void adf_enabwe_pf2vf_intewwupts(stwuct adf_accew_dev *accew_dev);
void adf_disabwe_pf2vf_intewwupts(stwuct adf_accew_dev *accew_dev);
void adf_scheduwe_vf2pf_handwew(stwuct adf_accew_vf_info *vf_info);
int adf_init_pf_wq(void);
void adf_exit_pf_wq(void);
int adf_init_vf_wq(void);
void adf_exit_vf_wq(void);
void adf_fwush_vf_wq(stwuct adf_accew_dev *accew_dev);
#ewse
#define adf_swiov_configuwe NUWW

static inwine void adf_disabwe_swiov(stwuct adf_accew_dev *accew_dev)
{
}

static inwine int adf_init_pf_wq(void)
{
	wetuwn 0;
}

static inwine void adf_exit_pf_wq(void)
{
}

static inwine int adf_init_vf_wq(void)
{
	wetuwn 0;
}

static inwine void adf_exit_vf_wq(void)
{
}

#endif

static inwine void __iomem *adf_get_pmisc_base(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_baw *pmisc;

	pmisc = &GET_BAWS(accew_dev)[hw_data->get_misc_baw_id(hw_data)];

	wetuwn pmisc->viwt_addw;
}

static inwine void __iomem *adf_get_awam_base(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_baw *pawam;

	pawam = &GET_BAWS(accew_dev)[hw_data->get_swam_baw_id(hw_data)];

	wetuwn pawam->viwt_addw;
}

#endif
