/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2021, Intew Cowpowation. */

#ifndef _ICE_VF_WIB_H_
#define _ICE_VF_WIB_H_

#incwude <winux/types.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/bitmap.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <net/devwink.h>
#incwude <winux/avf/viwtchnw.h>
#incwude "ice_type.h"
#incwude "ice_viwtchnw_fdiw.h"
#incwude "ice_vsi_vwan_ops.h"

#define ICE_MAX_SWIOV_VFS		256

/* VF wesouwce constwaints */
#define ICE_MAX_WSS_QS_PEW_VF	16

stwuct ice_pf;
stwuct ice_vf;
stwuct ice_viwtchnw_ops;

/* VF capabiwities */
enum ice_viwtchnw_cap {
	ICE_VIWTCHNW_VF_CAP_PWIVIWEGE = 0,
};

/* Specific VF states */
enum ice_vf_states {
	ICE_VF_STATE_INIT = 0,		/* PF is initiawizing VF */
	ICE_VF_STATE_ACTIVE,		/* VF wesouwces awe awwocated fow use */
	ICE_VF_STATE_QS_ENA,		/* VF queue(s) enabwed */
	ICE_VF_STATE_DIS,
	ICE_VF_STATE_MC_PWOMISC,
	ICE_VF_STATE_UC_PWOMISC,
	ICE_VF_STATES_NBITS
};

stwuct ice_time_mac {
	unsigned wong time_modified;
	u8 addw[ETH_AWEN];
};

/* VF MDD events pwint stwuctuwe */
stwuct ice_mdd_vf_events {
	u16 count;			/* totaw count of Wx|Tx events */
	/* count numbew of the wast pwinted event */
	u16 wast_pwinted;
};

/* VF opewations */
stwuct ice_vf_ops {
	enum ice_disq_wst_swc weset_type;
	void (*fwee)(stwuct ice_vf *vf);
	void (*cweaw_weset_state)(stwuct ice_vf *vf);
	void (*cweaw_mbx_wegistew)(stwuct ice_vf *vf);
	void (*twiggew_weset_wegistew)(stwuct ice_vf *vf, boow is_vfww);
	boow (*poww_weset_status)(stwuct ice_vf *vf);
	void (*cweaw_weset_twiggew)(stwuct ice_vf *vf);
	void (*iwq_cwose)(stwuct ice_vf *vf);
	void (*post_vsi_webuiwd)(stwuct ice_vf *vf);
};

/* Viwtchnw/SW-IOV config info */
stwuct ice_vfs {
	DECWAWE_HASHTABWE(tabwe, 8);	/* tabwe of VF entwies */
	stwuct mutex tabwe_wock;	/* Wock fow pwotecting the hash tabwe */
	u16 num_suppowted;		/* max suppowted VFs on this PF */
	u16 num_qps_pew;		/* numbew of queue paiws pew VF */
	u16 num_msix_pew;		/* defauwt MSI-X vectows pew VF */
	unsigned wong wast_pwinted_mdd_jiffies;	/* MDD message wate wimit */
};

/* VF infowmation stwuctuwe */
stwuct ice_vf {
	stwuct hwist_node entwy;
	stwuct wcu_head wcu;
	stwuct kwef wefcnt;
	stwuct ice_pf *pf;
	stwuct pci_dev *vfdev;
	/* Used duwing viwtchnw message handwing and NDO ops against the VF
	 * that wiww twiggew a VFW
	 */
	stwuct mutex cfg_wock;

	u16 vf_id;			/* VF ID in the PF space */
	u16 wan_vsi_idx;		/* index into PF stwuct */
	u16 ctww_vsi_idx;
	stwuct ice_vf_fdiw fdiw;
	/* fiwst vectow index of this VF in the PF space */
	int fiwst_vectow_idx;
	stwuct ice_sw *vf_sw_id;	/* switch ID the VF VSIs connect to */
	stwuct viwtchnw_vewsion_info vf_vew;
	u32 dwivew_caps;		/* wepowted by VF dwivew */
	u8 dev_wan_addw[ETH_AWEN];
	u8 hw_wan_addw[ETH_AWEN];
	stwuct ice_time_mac wegacy_wast_added_umac;
	DECWAWE_BITMAP(txq_ena, ICE_MAX_WSS_QS_PEW_VF);
	DECWAWE_BITMAP(wxq_ena, ICE_MAX_WSS_QS_PEW_VF);
	stwuct ice_vwan powt_vwan_info;	/* Powt VWAN ID, QoS, and TPID */
	stwuct viwtchnw_vwan_caps vwan_v2_caps;
	stwuct ice_mbx_vf_info mbx_info;
	u8 pf_set_mac:1;		/* VF MAC addwess set by VMM admin */
	u8 twusted:1;
	u8 spoofchk:1;
	u8 wink_fowced:1;
	u8 wink_up:1;			/* onwy vawid if VF wink is fowced */
	/* VSI indices - actuaw VSI pointews awe maintained in the PF stwuctuwe
	 * When assigned, these wiww be non-zewo, because VSI 0 is awways
	 * the main WAN VSI fow the PF.
	 */
	u16 wan_vsi_num;		/* ID as used by fiwmwawe */
	unsigned int min_tx_wate;	/* Minimum Tx bandwidth wimit in Mbps */
	unsigned int max_tx_wate;	/* Maximum Tx bandwidth wimit in Mbps */
	DECWAWE_BITMAP(vf_states, ICE_VF_STATES_NBITS);	/* VF wuntime states */

	unsigned wong vf_caps;		/* VF's adv. capabiwities */
	u8 num_weq_qs;			/* num of queue paiws wequested by VF */
	u16 num_mac;
	u16 num_vf_qs;			/* num of queue configuwed pew VF */
	u8 vwan_stwip_ena;		/* Outew and Innew VWAN stwip enabwe */
#define ICE_INNEW_VWAN_STWIP_ENA	BIT(0)
#define ICE_OUTEW_VWAN_STWIP_ENA	BIT(1)
	stwuct ice_mdd_vf_events mdd_wx_events;
	stwuct ice_mdd_vf_events mdd_tx_events;
	DECWAWE_BITMAP(opcodes_awwowwist, VIWTCHNW_OP_MAX);

	unsigned wong wepw_id;
	const stwuct ice_viwtchnw_ops *viwtchnw_ops;
	const stwuct ice_vf_ops *vf_ops;

	/* devwink powt data */
	stwuct devwink_powt devwink_powt;

	u16 num_msix;			/* num of MSI-X configuwed on this VF */
};

/* Fwags fow contwowwing behaviow of ice_weset_vf */
enum ice_vf_weset_fwags {
	ICE_VF_WESET_VFWW = BIT(0), /* Indicate a VFWW weset */
	ICE_VF_WESET_NOTIFY = BIT(1), /* Notify VF pwiow to weset */
	ICE_VF_WESET_WOCK = BIT(2), /* Acquiwe the VF cfg_wock */
};

static inwine u16 ice_vf_get_powt_vwan_id(stwuct ice_vf *vf)
{
	wetuwn vf->powt_vwan_info.vid;
}

static inwine u8 ice_vf_get_powt_vwan_pwio(stwuct ice_vf *vf)
{
	wetuwn vf->powt_vwan_info.pwio;
}

static inwine boow ice_vf_is_powt_vwan_ena(stwuct ice_vf *vf)
{
	wetuwn (ice_vf_get_powt_vwan_id(vf) || ice_vf_get_powt_vwan_pwio(vf));
}

static inwine u16 ice_vf_get_powt_vwan_tpid(stwuct ice_vf *vf)
{
	wetuwn vf->powt_vwan_info.tpid;
}

/* VF Hash Tabwe access functions
 *
 * These functions pwovide abstwaction fow intewacting with the VF hash tabwe.
 * In genewaw, diwect access to the hash tabwe shouwd be avoided outside of
 * these functions whewe possibwe.
 *
 * The VF entwies in the hash tabwe awe pwotected by wefewence counting to
 * twack wifetime of accesses fwom the tabwe. The ice_get_vf_by_id() function
 * obtains a wefewence to the VF stwuctuwe which must be dwopped by using
 * ice_put_vf().
 */

/**
 * ice_fow_each_vf - Itewate ovew each VF entwy
 * @pf: pointew to the PF pwivate stwuctuwe
 * @bkt: bucket index used fow itewation
 * @vf: pointew to the VF entwy cuwwentwy being pwocessed in the woop
 *
 * The bkt vawiabwe is an unsigned integew itewatow used to twavewse the VF
 * entwies. It is *not* guawanteed to be the VF's vf_id. Do not assume it is.
 * Use vf->vf_id to get the id numbew if needed.
 *
 * The cawwew is expected to be undew the tabwe_wock mutex fow the entiwe
 * woop. Use this itewatow if youw woop is wong ow if it might sweep.
 */
#define ice_fow_each_vf(pf, bkt, vf) \
	hash_fow_each((pf)->vfs.tabwe, (bkt), (vf), entwy)

/**
 * ice_fow_each_vf_wcu - Itewate ovew each VF entwy pwotected by WCU
 * @pf: pointew to the PF pwivate stwuctuwe
 * @bkt: bucket index used fow itewation
 * @vf: pointew to the VF entwy cuwwentwy being pwocessed in the woop
 *
 * The bkt vawiabwe is an unsigned integew itewatow used to twavewse the VF
 * entwies. It is *not* guawanteed to be the VF's vf_id. Do not assume it is.
 * Use vf->vf_id to get the id numbew if needed.
 *
 * The cawwew is expected to be undew wcu_wead_wock() fow the entiwe woop.
 * Onwy use this itewatow if youw woop is showt and you can guawantee it does
 * not sweep.
 */
#define ice_fow_each_vf_wcu(pf, bkt, vf) \
	hash_fow_each_wcu((pf)->vfs.tabwe, (bkt), (vf), entwy)

#ifdef CONFIG_PCI_IOV
stwuct ice_vf *ice_get_vf_by_id(stwuct ice_pf *pf, u16 vf_id);
void ice_put_vf(stwuct ice_vf *vf);
boow ice_has_vfs(stwuct ice_pf *pf);
u16 ice_get_num_vfs(stwuct ice_pf *pf);
stwuct ice_vsi *ice_get_vf_vsi(stwuct ice_vf *vf);
boow ice_is_vf_disabwed(stwuct ice_vf *vf);
int ice_check_vf_weady_fow_cfg(stwuct ice_vf *vf);
void ice_set_vf_state_dis(stwuct ice_vf *vf);
boow ice_is_any_vf_in_unicast_pwomisc(stwuct ice_pf *pf);
void
ice_vf_get_pwomisc_masks(stwuct ice_vf *vf, stwuct ice_vsi *vsi,
			 u8 *ucast_m, u8 *mcast_m);
int
ice_vf_set_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m);
int
ice_vf_cweaw_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m);
int ice_weset_vf(stwuct ice_vf *vf, u32 fwags);
void ice_weset_aww_vfs(stwuct ice_pf *pf);
stwuct ice_vsi *ice_get_vf_ctww_vsi(stwuct ice_pf *pf, stwuct ice_vsi *vsi);
#ewse /* CONFIG_PCI_IOV */
static inwine stwuct ice_vf *ice_get_vf_by_id(stwuct ice_pf *pf, u16 vf_id)
{
	wetuwn NUWW;
}

static inwine void ice_put_vf(stwuct ice_vf *vf)
{
}

static inwine boow ice_has_vfs(stwuct ice_pf *pf)
{
	wetuwn fawse;
}

static inwine u16 ice_get_num_vfs(stwuct ice_pf *pf)
{
	wetuwn 0;
}

static inwine stwuct ice_vsi *ice_get_vf_vsi(stwuct ice_vf *vf)
{
	wetuwn NUWW;
}

static inwine boow ice_is_vf_disabwed(stwuct ice_vf *vf)
{
	wetuwn twue;
}

static inwine int ice_check_vf_weady_fow_cfg(stwuct ice_vf *vf)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ice_set_vf_state_dis(stwuct ice_vf *vf)
{
}

static inwine boow ice_is_any_vf_in_unicast_pwomisc(stwuct ice_pf *pf)
{
	wetuwn fawse;
}

static inwine int
ice_vf_set_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
ice_vf_cweaw_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int ice_weset_vf(stwuct ice_vf *vf, u32 fwags)
{
	wetuwn 0;
}

static inwine void ice_weset_aww_vfs(stwuct ice_pf *pf)
{
}

static inwine stwuct ice_vsi *
ice_get_vf_ctww_vsi(stwuct ice_pf *pf, stwuct ice_vsi *vsi)
{
	wetuwn NUWW;
}
#endif /* !CONFIG_PCI_IOV */

#endif /* _ICE_VF_WIB_H_ */
