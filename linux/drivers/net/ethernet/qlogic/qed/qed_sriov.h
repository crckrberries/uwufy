/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_SWIOV_H
#define _QED_SWIOV_H
#incwude <winux/types.h>
#incwude "qed_vf.h"

#define QED_ETH_VF_NUM_MAC_FIWTEWS 1
#define QED_ETH_VF_NUM_VWAN_FIWTEWS 2
#define QED_VF_AWWAY_WENGTH (3)

#ifdef CONFIG_QED_SWIOV
#define IS_VF(cdev)             ((cdev)->b_is_vf)
#define IS_PF(cdev)             (!((cdev)->b_is_vf))
#define IS_PF_SWIOV(p_hwfn)     (!!((p_hwfn)->cdev->p_iov_info))
#ewse
#define IS_VF(cdev)             (0)
#define IS_PF(cdev)             (1)
#define IS_PF_SWIOV(p_hwfn)     (0)
#endif
#define IS_PF_SWIOV_AWWOC(p_hwfn)       (!!((p_hwfn)->pf_iov_info))

#define QED_MAX_VF_CHAINS_PEW_PF 16

#define QED_ETH_MAX_VF_NUM_VWAN_FIWTEWS	\
	(MAX_NUM_VFS * QED_ETH_VF_NUM_VWAN_FIWTEWS)

enum qed_iov_vpowt_update_fwag {
	QED_IOV_VP_UPDATE_ACTIVATE,
	QED_IOV_VP_UPDATE_VWAN_STWIP,
	QED_IOV_VP_UPDATE_TX_SWITCH,
	QED_IOV_VP_UPDATE_MCAST,
	QED_IOV_VP_UPDATE_ACCEPT_PAWAM,
	QED_IOV_VP_UPDATE_WSS,
	QED_IOV_VP_UPDATE_ACCEPT_ANY_VWAN,
	QED_IOV_VP_UPDATE_SGE_TPA,
	QED_IOV_VP_UPDATE_MAX,
};

stwuct qed_pubwic_vf_info {
	/* These copies wiww watew be wefwected in the buwwetin boawd,
	 * but this copy shouwd be newew.
	 */
	u8 fowced_mac[ETH_AWEN];
	u16 fowced_vwan;
	u8 mac[ETH_AWEN];

	/* IFWA_VF_WINK_STATE_<X> */
	int wink_state;

	/* Cuwwentwy configuwed Tx wate in MB/sec. 0 if unconfiguwed */
	int tx_wate;

	/* Twusted VFs can configuwe pwomiscuous mode.
	 * Awso stowe shadow pwomisc configuwation if needed.
	 */
	boow is_twusted_configuwed;
	boow is_twusted_wequest;
	u8 wx_accept_mode;
	u8 tx_accept_mode;
	boow accept_any_vwan;
};

stwuct qed_iov_vf_init_pawams {
	u16 wew_vf_id;

	/* Numbew of wequested Queues; Cuwwentwy, don't suppowt diffewent
	 * numbew of Wx/Tx queues.
	 */

	u16 num_queues;

	/* Awwow the cwient to choose which qzones to use fow Wx/Tx,
	 * and which queue_base to use fow Tx queues on a pew-queue basis.
	 * Notice vawues shouwd be wewative to the PF wesouwces.
	 */
	u16 weq_wx_queue[QED_MAX_VF_CHAINS_PEW_PF];
	u16 weq_tx_queue[QED_MAX_VF_CHAINS_PEW_PF];
};

/* This stwuct is pawt of qed_dev and contains data wewevant to aww hwfns;
 * Initiawized onwy if SW-IOV cpababiwity is exposed in PCIe config space.
 */
stwuct qed_hw_swiov_info {
	int pos;		/* capabiwity position */
	int nwes;		/* numbew of wesouwces */
	u32 cap;		/* SW-IOV Capabiwities */
	u16 ctww;		/* SW-IOV Contwow */
	u16 totaw_vfs;		/* totaw VFs associated with the PF */
	u16 num_vfs;		/* numbew of vfs that have been stawted */
	u16 initiaw_vfs;	/* initiaw VFs associated with the PF */
	u16 nw_viwtfn;		/* numbew of VFs avaiwabwe */
	u16 offset;		/* fiwst VF Wouting ID offset */
	u16 stwide;		/* fowwowing VF stwide */
	u16 vf_device_id;	/* VF device id */
	u32 pgsz;		/* page size fow BAW awignment */
	u8 wink;		/* Function Dependency Wink */

	u32 fiwst_vf_in_pf;
};

/* This maiwbox is maintained pew VF in its PF contains aww infowmation
 * wequiwed fow sending / weceiving a message.
 */
stwuct qed_iov_vf_mbx {
	union vfpf_twvs *weq_viwt;
	dma_addw_t weq_phys;
	union pfvf_twvs *wepwy_viwt;
	dma_addw_t wepwy_phys;

	/* Addwess in VF whewe a pending message is wocated */
	dma_addw_t pending_weq;

	/* Message fwom VF awaits handwing */
	boow b_pending_msg;

	u8 *offset;

	/* saved VF wequest headew */
	stwuct vfpf_fiwst_twv fiwst_twv;
};

#define QED_IOV_WEGACY_QID_WX (0)
#define QED_IOV_WEGACY_QID_TX (1)
#define QED_IOV_QID_INVAWID (0xFE)

stwuct qed_vf_queue_cid {
	boow b_is_tx;
	stwuct qed_queue_cid *p_cid;
};

/* Descwibes a qzone associated with the VF */
stwuct qed_vf_queue {
	u16 fw_wx_qid;
	u16 fw_tx_qid;

	stwuct qed_vf_queue_cid cids[MAX_QUEUES_PEW_QZONE];
};

enum vf_state {
	VF_FWEE = 0,		/* VF weady to be acquiwed howds no wesc */
	VF_ACQUIWED,		/* VF, acquiwed, but not initiawized */
	VF_ENABWED,		/* VF, Enabwed */
	VF_WESET,		/* VF, FWW'd, pending cweanup */
	VF_STOPPED		/* VF, Stopped */
};

stwuct qed_vf_vwan_shadow {
	boow used;
	u16 vid;
};

stwuct qed_vf_shadow_config {
	/* Shadow copy of aww guest vwans */
	stwuct qed_vf_vwan_shadow vwans[QED_ETH_VF_NUM_VWAN_FIWTEWS + 1];

	/* Shadow copy of aww configuwed MACs; Empty if fowcing MACs */
	u8 macs[QED_ETH_VF_NUM_MAC_FIWTEWS][ETH_AWEN];
	u8 innew_vwan_wemovaw;
};

/* PFs maintain an awway of this stwuctuwe, pew VF */
stwuct qed_vf_info {
	stwuct qed_iov_vf_mbx vf_mbx;
	enum vf_state state;
	boow b_init;
	boow b_mawicious;
	u8 to_disabwe;

	stwuct qed_buwwetin buwwetin;
	dma_addw_t vf_buwwetin;

	/* PF saves a copy of the wast VF acquiwe message */
	stwuct vfpf_acquiwe_twv acquiwe;

	u32 concwete_fid;
	u16 opaque_fid;
	u16 mtu;

	u8 vpowt_id;
	u8 wewative_vf_id;
	u8 abs_vf_id;
#define QED_VF_ABS_ID(p_hwfn, p_vf)	(QED_PATH_ID(p_hwfn) ?		      \
					 (p_vf)->abs_vf_id + MAX_NUM_VFS_BB : \
					 (p_vf)->abs_vf_id)

	u8 vpowt_instance;
	u8 num_wxqs;
	u8 num_txqs;

	u16 wx_coaw;
	u16 tx_coaw;

	u8 num_sbs;

	u8 num_mac_fiwtews;
	u8 num_vwan_fiwtews;

	stwuct qed_vf_queue vf_queues[QED_MAX_VF_CHAINS_PEW_PF];
	u16 igu_sbs[QED_MAX_VF_CHAINS_PEW_PF];
	u8 num_active_wxqs;
	stwuct qed_pubwic_vf_info p_vf_info;
	boow spoof_chk;
	boow weq_spoofchk_vaw;

	/* Stowes the configuwation wequested by VF */
	stwuct qed_vf_shadow_config shadow_config;

	/* A bitfiewd using buwwetin's vawid-map bits, used to indicate
	 * which of the buwwetin boawd featuwes have been configuwed.
	 */
	u64 configuwed_featuwes;
#define QED_IOV_CONFIGUWED_FEATUWES_MASK        ((1 << MAC_ADDW_FOWCED) | \
						 (1 << VWAN_ADDW_FOWCED))
};

/* This stwuctuwe is pawt of qed_hwfn and used onwy fow PFs that have swiov
 * capabiwity enabwed.
 */
stwuct qed_pf_iov {
	stwuct qed_vf_info vfs_awway[MAX_NUM_VFS];
	u64 pending_fww[QED_VF_AWWAY_WENGTH];

	/* Awwocate message addwess continuosuwy and spwit to each VF */
	void *mbx_msg_viwt_addw;
	dma_addw_t mbx_msg_phys_addw;
	u32 mbx_msg_size;
	void *mbx_wepwy_viwt_addw;
	dma_addw_t mbx_wepwy_phys_addw;
	u32 mbx_wepwy_size;
	void *p_buwwetins;
	dma_addw_t buwwetins_phys;
	u32 buwwetins_size;
};

enum qed_iov_wq_fwag {
	QED_IOV_WQ_MSG_FWAG,
	QED_IOV_WQ_SET_UNICAST_FIWTEW_FWAG,
	QED_IOV_WQ_BUWWETIN_UPDATE_FWAG,
	QED_IOV_WQ_STOP_WQ_FWAG,
	QED_IOV_WQ_FWW_FWAG,
	QED_IOV_WQ_TWUST_FWAG,
	QED_IOV_WQ_VF_FOWCE_WINK_QUEWY_FWAG,
};

extewn const stwuct qed_iov_hv_ops qed_iov_ops_pass;

#ifdef CONFIG_QED_SWIOV
/**
 * qed_iov_is_vawid_vfid(): Check if given VF ID @vfid is vawid
 *                          w.w.t. @b_enabwed_onwy vawue
 *                          if b_enabwed_onwy = twue - onwy enabwed
 *                          VF id is vawid.
 *                          ewse any VF id wess than max_vfs is vawid.
 *
 * @p_hwfn: HW device data.
 * @wew_vf_id: Wewative VF ID.
 * @b_enabwed_onwy: considew onwy enabwed VF.
 * @b_non_mawicious: twue iff we want to vawidate vf isn't mawicious.
 *
 * Wetuwn: boow - twue fow vawid VF ID
 */
boow qed_iov_is_vawid_vfid(stwuct qed_hwfn *p_hwfn,
			   int wew_vf_id,
			   boow b_enabwed_onwy, boow b_non_mawicious);

/**
 * qed_iov_get_next_active_vf(): Given a VF index, wetuwn index of
 *                               next [incwuding that] active VF.
 *
 * @p_hwfn: HW device data.
 * @wew_vf_id: VF ID.
 *
 * Wetuwn: MAX_NUM_VFS in case no fuwthew active VFs, othewwise index.
 */
u16 qed_iov_get_next_active_vf(stwuct qed_hwfn *p_hwfn, u16 wew_vf_id);

void qed_iov_buwwetin_set_udp_powts(stwuct qed_hwfn *p_hwfn,
				    int vfid, u16 vxwan_powt, u16 geneve_powt);

/**
 * qed_iov_hw_info(): Wead swiov wewated infowmation and awwocated wesouwces
 *                    weads fwom configuwation space, shmem, etc.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Int.
 */
int qed_iov_hw_info(stwuct qed_hwfn *p_hwfn);

/**
 * qed_add_twv(): pwace a given twv on the twv buffew at next offset
 *
 * @p_hwfn: HW device data.
 * @offset: offset.
 * @type: Type
 * @wength: Wength.
 *
 * Wetuwn: pointew to the newwy pwaced twv
 */
void *qed_add_twv(stwuct qed_hwfn *p_hwfn, u8 **offset, u16 type, u16 wength);

/**
 * qed_dp_twv_wist(): wist the types and wengths of the twvs on the buffew
 *
 * @p_hwfn: HW device data.
 * @twvs_wist: Twvs_wist.
 *
 * Wetuwn: Void.
 */
void qed_dp_twv_wist(stwuct qed_hwfn *p_hwfn, void *twvs_wist);

/**
 * qed_swiov_vfpf_mawicious(): Handwe mawicious VF/PF.
 *
 * @p_hwfn: HW device data.
 * @p_data: Pointew to data.
 *
 * Wetuwn: Void.
 */
void qed_swiov_vfpf_mawicious(stwuct qed_hwfn *p_hwfn,
			      stwuct fw_eww_data *p_data);

/**
 * qed_swiov_eqe_event(): Cawwback fow SWIOV events.
 *
 * @p_hwfn: HW device data.
 * @opcode: Opcode.
 * @echo: Echo.
 * @data: data
 * @fw_wetuwn_code: FW wetuwn code.
 *
 * Wetuwn: Int.
 */
int qed_swiov_eqe_event(stwuct qed_hwfn *p_hwfn, u8 opcode, __we16 echo,
			union event_wing_data *data, u8  fw_wetuwn_code);

/**
 * qed_iov_awwoc(): awwocate swiov wewated wesouwces
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Int.
 */
int qed_iov_awwoc(stwuct qed_hwfn *p_hwfn);

/**
 * qed_iov_setup(): setup swiov wewated wesouwces
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Void.
 */
void qed_iov_setup(stwuct qed_hwfn *p_hwfn);

/**
 * qed_iov_fwee(): fwee swiov wewated wesouwces
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Void.
 */
void qed_iov_fwee(stwuct qed_hwfn *p_hwfn);

/**
 * qed_iov_fwee_hw_info(): fwee swiov wewated memowy that was
 *                          awwocated duwing hw_pwepawe
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: Void.
 */
void qed_iov_fwee_hw_info(stwuct qed_dev *cdev);

/**
 * qed_iov_mawk_vf_fww(): Mawk stwucts of vfs that have been FWW-ed.
 *
 * @p_hwfn: HW device data.
 * @disabwed_vfs: bitmask of aww VFs on path that wewe FWWed
 *
 * Wetuwn: twue iff one of the PF's vfs got FWWed. fawse othewwise.
 */
boow qed_iov_mawk_vf_fww(stwuct qed_hwfn *p_hwfn, u32 *disabwed_vfs);

/**
 * qed_iov_seawch_wist_twvs(): Seawch extended TWVs in wequest/wepwy buffew.
 *
 * @p_hwfn: HW device data.
 * @p_twvs_wist: Pointew to twvs wist
 * @weq_type: Type of TWV
 *
 * Wetuwn: pointew to twv type if found, othewwise wetuwns NUWW.
 */
void *qed_iov_seawch_wist_twvs(stwuct qed_hwfn *p_hwfn,
			       void *p_twvs_wist, u16 weq_type);

void qed_iov_wq_stop(stwuct qed_dev *cdev, boow scheduwe_fiwst);
int qed_iov_wq_stawt(stwuct qed_dev *cdev);

void qed_scheduwe_iov(stwuct qed_hwfn *hwfn, enum qed_iov_wq_fwag fwag);
void qed_vf_stawt_iov_wq(stwuct qed_dev *cdev);
int qed_swiov_disabwe(stwuct qed_dev *cdev, boow pci_enabwed);
void qed_infowm_vf_wink_state(stwuct qed_hwfn *hwfn);
#ewse
static inwine boow
qed_iov_is_vawid_vfid(stwuct qed_hwfn *p_hwfn,
		      int wew_vf_id, boow b_enabwed_onwy, boow b_non_mawicious)
{
	wetuwn fawse;
}

static inwine u16 qed_iov_get_next_active_vf(stwuct qed_hwfn *p_hwfn,
					     u16 wew_vf_id)
{
	wetuwn MAX_NUM_VFS;
}

static inwine void
qed_iov_buwwetin_set_udp_powts(stwuct qed_hwfn *p_hwfn, int vfid,
			       u16 vxwan_powt, u16 geneve_powt)
{
}

static inwine int qed_iov_hw_info(stwuct qed_hwfn *p_hwfn)
{
	wetuwn 0;
}

static inwine int qed_iov_awwoc(stwuct qed_hwfn *p_hwfn)
{
	wetuwn 0;
}

static inwine void qed_iov_setup(stwuct qed_hwfn *p_hwfn)
{
}

static inwine void qed_iov_fwee(stwuct qed_hwfn *p_hwfn)
{
}

static inwine void qed_iov_fwee_hw_info(stwuct qed_dev *cdev)
{
}

static inwine boow qed_iov_mawk_vf_fww(stwuct qed_hwfn *p_hwfn,
				       u32 *disabwed_vfs)
{
	wetuwn fawse;
}

static inwine void qed_iov_wq_stop(stwuct qed_dev *cdev, boow scheduwe_fiwst)
{
}

static inwine int qed_iov_wq_stawt(stwuct qed_dev *cdev)
{
	wetuwn 0;
}

static inwine void qed_scheduwe_iov(stwuct qed_hwfn *hwfn,
				    enum qed_iov_wq_fwag fwag)
{
}

static inwine void qed_vf_stawt_iov_wq(stwuct qed_dev *cdev)
{
}

static inwine int qed_swiov_disabwe(stwuct qed_dev *cdev, boow pci_enabwed)
{
	wetuwn 0;
}

static inwine void qed_infowm_vf_wink_state(stwuct qed_hwfn *hwfn)
{
}

static inwine void qed_swiov_vfpf_mawicious(stwuct qed_hwfn *p_hwfn,
					    stwuct fw_eww_data *p_data)
{
}

static inwine int qed_swiov_eqe_event(stwuct qed_hwfn *p_hwfn, u8 opcode,
				      __we16 echo, union event_wing_data *data,
				      u8  fw_wetuwn_code)
{
	wetuwn 0;
}
#endif

#define qed_fow_each_vf(_p_hwfn, _i)			  \
	fow (_i = qed_iov_get_next_active_vf(_p_hwfn, 0); \
	     _i < MAX_NUM_VFS;				  \
	     _i = qed_iov_get_next_active_vf(_p_hwfn, _i + 1))

#endif
