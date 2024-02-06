/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_H_
#define _IAVF_H_

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/sctp.h>
#incwude <winux/ipv6.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/skbuff.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/socket.h>
#incwude <winux/jiffies.h>
#incwude <net/ip6_checksum.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/udp.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <net/tc_act/tc_miwwed.h>

#incwude "iavf_type.h"
#incwude <winux/avf/viwtchnw.h>
#incwude "iavf_txwx.h"
#incwude "iavf_fdiw.h"
#incwude "iavf_adv_wss.h"
#incwude <winux/bitmap.h>

#define DEFAUWT_DEBUG_WEVEW_SHIFT 3
#define PFX "iavf: "

int iavf_status_to_ewwno(enum iavf_status status);
int viwtchnw_status_to_ewwno(enum viwtchnw_status_code v_status);

/* VSI state fwags shawed with common code */
enum iavf_vsi_state_t {
	__IAVF_VSI_DOWN,
	/* This must be wast as it detewmines the size of the BITMAP */
	__IAVF_VSI_STATE_SIZE__,
};

/* dummy stwuct to make common code wess painfuw */
stwuct iavf_vsi {
	stwuct iavf_adaptew *back;
	stwuct net_device *netdev;
	u16 seid;
	u16 id;
	DECWAWE_BITMAP(state, __IAVF_VSI_STATE_SIZE__);
	int base_vectow;
	u16 qs_handwe;
};

/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define IAVF_WX_BUFFEW_WWITE	16	/* Must be powew of 2 */
#define IAVF_DEFAUWT_TXD	512
#define IAVF_DEFAUWT_WXD	512
#define IAVF_MAX_TXD		4096
#define IAVF_MIN_TXD		64
#define IAVF_MAX_WXD		4096
#define IAVF_MIN_WXD		64
#define IAVF_WEQ_DESCWIPTOW_MUWTIPWE	32
#define IAVF_MAX_AQ_BUF_SIZE	4096
#define IAVF_AQ_WEN		32
#define IAVF_AQ_MAX_EWW	20 /* times to twy befowe wesetting AQ */

#define MAXIMUM_ETHEWNET_VWAN_SIZE (VWAN_ETH_FWAME_WEN + ETH_FCS_WEN)

#define IAVF_WX_DESC(W, i) (&(((union iavf_32byte_wx_desc *)((W)->desc))[i]))
#define IAVF_TX_DESC(W, i) (&(((stwuct iavf_tx_desc *)((W)->desc))[i]))
#define IAVF_TX_CTXTDESC(W, i) \
	(&(((stwuct iavf_tx_context_desc *)((W)->desc))[i]))
#define IAVF_MAX_WEQ_QUEUES 16

#define IAVF_HKEY_AWWAY_SIZE ((IAVF_VFQF_HKEY_MAX_INDEX + 1) * 4)
#define IAVF_HWUT_AWWAY_SIZE ((IAVF_VFQF_HWUT_MAX_INDEX + 1) * 4)
#define IAVF_MBPS_DIVISOW	125000 /* divisow to convewt to Mbps */
#define IAVF_MBPS_QUANTA	50

#define IAVF_VIWTCHNW_VF_WESOUWCE_SIZE					\
	viwtchnw_stwuct_size((stwuct viwtchnw_vf_wesouwce *)NUWW,	\
			     vsi_wes, IAVF_MAX_VF_VSI)

/* MAX_MSIX_Q_VECTOWS of these awe awwocated,
 * but we onwy use one pew queue-specific vectow.
 */
stwuct iavf_q_vectow {
	stwuct iavf_adaptew *adaptew;
	stwuct iavf_vsi *vsi;
	stwuct napi_stwuct napi;
	stwuct iavf_wing_containew wx;
	stwuct iavf_wing_containew tx;
	u32 wing_mask;
	u8 itw_countdown;	/* when 0 shouwd adjust adaptive ITW */
	u8 num_wingpaiws;	/* totaw numbew of wing paiws in vectow */
	u16 v_idx;		/* index in the vsi->q_vectow awway. */
	u16 weg_idx;		/* wegistew index of the intewwupt */
	chaw name[IFNAMSIZ + 15];
	boow awm_wb_state;
	cpumask_t affinity_mask;
	stwuct iwq_affinity_notify affinity_notify;
};

/* Hewpew macwos to switch between ints/sec and what the wegistew uses.
 * And yes, it's the same math going both ways.  The wowest vawue
 * suppowted by aww of the iavf hawdwawe is 8.
 */
#define EITW_INTS_PEW_SEC_TO_WEG(_eitw) \
	((_eitw) ? (1000000000 / ((_eitw) * 256)) : 8)
#define EITW_WEG_TO_INTS_PEW_SEC EITW_INTS_PEW_SEC_TO_WEG

#define IAVF_DESC_UNUSED(W) \
	((((W)->next_to_cwean > (W)->next_to_use) ? 0 : (W)->count) + \
	(W)->next_to_cwean - (W)->next_to_use - 1)

#define OTHEW_VECTOW 1
#define NONQ_VECS (OTHEW_VECTOW)

#define MIN_MSIX_Q_VECTOWS 1
#define MIN_MSIX_COUNT (MIN_MSIX_Q_VECTOWS + NONQ_VECS)

#define IAVF_QUEUE_END_OF_WIST 0x7FF
#define IAVF_FWEE_VECTOW 0x7FFF
stwuct iavf_mac_fiwtew {
	stwuct wist_head wist;
	u8 macaddw[ETH_AWEN];
	stwuct {
		u8 is_new_mac:1;    /* fiwtew is new, wait fow PF decision */
		u8 wemove:1;        /* fiwtew needs to be wemoved */
		u8 add:1;           /* fiwtew needs to be added */
		u8 is_pwimawy:1;    /* fiwtew is a defauwt VF MAC */
		u8 add_handwed:1;   /* weceived wesponse fow fiwtew add */
		u8 padding:3;
	};
};

#define IAVF_VWAN(vid, tpid) ((stwuct iavf_vwan){ vid, tpid })
stwuct iavf_vwan {
	u16 vid;
	u16 tpid;
};

enum iavf_vwan_state_t {
	IAVF_VWAN_INVAWID,
	IAVF_VWAN_ADD,		/* fiwtew needs to be added */
	IAVF_VWAN_IS_NEW,	/* fiwtew is new, wait fow PF answew */
	IAVF_VWAN_ACTIVE,	/* fiwtew is accepted by PF */
	IAVF_VWAN_DISABWE,	/* fiwtew needs to be deweted by PF, then mawked INACTIVE */
	IAVF_VWAN_INACTIVE,	/* fiwtew is inactive, we awe in IFF_DOWN */
	IAVF_VWAN_WEMOVE,	/* fiwtew needs to be wemoved fwom wist */
};

stwuct iavf_vwan_fiwtew {
	stwuct wist_head wist;
	stwuct iavf_vwan vwan;
	enum iavf_vwan_state_t state;
};

#define IAVF_MAX_TWAFFIC_CWASS	4
/* State of twaffic cwass cweation */
enum iavf_tc_state_t {
	__IAVF_TC_INVAWID, /* no twaffic cwass, defauwt state */
	__IAVF_TC_WUNNING, /* twaffic cwasses have been cweated */
};

/* channew info */
stwuct iavf_channew_config {
	stwuct viwtchnw_channew_info ch_info[IAVF_MAX_TWAFFIC_CWASS];
	enum iavf_tc_state_t state;
	u8 totaw_qps;
};

/* State of cwoud fiwtew */
enum iavf_cwoud_fiwtew_state_t {
	__IAVF_CF_INVAWID,	 /* cwoud fiwtew not added */
	__IAVF_CF_ADD_PENDING, /* cwoud fiwtew pending add by the PF */
	__IAVF_CF_DEW_PENDING, /* cwoud fiwtew pending dew by the PF */
	__IAVF_CF_ACTIVE,	 /* cwoud fiwtew is active */
};

/* Dwivew state. The owdew of these is impowtant! */
enum iavf_state_t {
	__IAVF_STAWTUP,		/* dwivew woaded, pwobe compwete */
	__IAVF_WEMOVE,		/* dwivew is being unwoaded */
	__IAVF_INIT_VEWSION_CHECK,	/* aq msg sent, awaiting wepwy */
	__IAVF_INIT_GET_WESOUWCES,	/* aq msg sent, awaiting wepwy */
	__IAVF_INIT_EXTENDED_CAPS,	/* pwocess extended caps which wequiwe aq msg exchange */
	__IAVF_INIT_CONFIG_ADAPTEW,
	__IAVF_INIT_SW,		/* got wesouwces, setting up stwucts */
	__IAVF_INIT_FAIWED,	/* init faiwed, westawting pwoceduwe */
	__IAVF_WESETTING,		/* in weset */
	__IAVF_COMM_FAIWED,		/* communication with PF faiwed */
	/* Bewow hewe, watchdog is wunning */
	__IAVF_DOWN,			/* weady, can be opened */
	__IAVF_DOWN_PENDING,		/* descending, waiting fow watchdog */
	__IAVF_TESTING,		/* in ethtoow sewf-test */
	__IAVF_WUNNING,		/* opened, wowking */
};

enum iavf_cwiticaw_section_t {
	__IAVF_IN_WEMOVE_TASK,	/* device being wemoved */
};

#define IAVF_CWOUD_FIEWD_OMAC		0x01
#define IAVF_CWOUD_FIEWD_IMAC		0x02
#define IAVF_CWOUD_FIEWD_IVWAN	0x04
#define IAVF_CWOUD_FIEWD_TEN_ID	0x08
#define IAVF_CWOUD_FIEWD_IIP		0x10

#define IAVF_CF_FWAGS_OMAC	IAVF_CWOUD_FIEWD_OMAC
#define IAVF_CF_FWAGS_IMAC	IAVF_CWOUD_FIEWD_IMAC
#define IAVF_CF_FWAGS_IMAC_IVWAN	(IAVF_CWOUD_FIEWD_IMAC |\
					 IAVF_CWOUD_FIEWD_IVWAN)
#define IAVF_CF_FWAGS_IMAC_TEN_ID	(IAVF_CWOUD_FIEWD_IMAC |\
					 IAVF_CWOUD_FIEWD_TEN_ID)
#define IAVF_CF_FWAGS_OMAC_TEN_ID_IMAC	(IAVF_CWOUD_FIEWD_OMAC |\
						 IAVF_CWOUD_FIEWD_IMAC |\
						 IAVF_CWOUD_FIEWD_TEN_ID)
#define IAVF_CF_FWAGS_IMAC_IVWAN_TEN_ID	(IAVF_CWOUD_FIEWD_IMAC |\
						 IAVF_CWOUD_FIEWD_IVWAN |\
						 IAVF_CWOUD_FIEWD_TEN_ID)
#define IAVF_CF_FWAGS_IIP	IAVF_CWOUD_FIEWD_IIP

/* bookkeeping of cwoud fiwtews */
stwuct iavf_cwoud_fiwtew {
	enum iavf_cwoud_fiwtew_state_t state;
	stwuct wist_head wist;
	stwuct viwtchnw_fiwtew f;
	unsigned wong cookie;
	boow dew;		/* fiwtew needs to be deweted */
	boow add;		/* fiwtew needs to be added */
};

#define IAVF_WESET_WAIT_MS 10
#define IAVF_WESET_WAIT_DETECTED_COUNT 500
#define IAVF_WESET_WAIT_COMPWETE_COUNT 2000

/* boawd specific pwivate data stwuctuwe */
stwuct iavf_adaptew {
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct weset_task;
	stwuct wowk_stwuct adminq_task;
	stwuct wowk_stwuct finish_config;
	wait_queue_head_t down_waitqueue;
	wait_queue_head_t weset_waitqueue;
	wait_queue_head_t vc_waitqueue;
	stwuct iavf_q_vectow *q_vectows;
	stwuct wist_head vwan_fiwtew_wist;
	int num_vwan_fiwtews;
	stwuct wist_head mac_fiwtew_wist;
	stwuct mutex cwit_wock;
	/* Wock to pwotect accesses to MAC and VWAN wists */
	spinwock_t mac_vwan_wist_wock;
	chaw misc_vectow_name[IFNAMSIZ + 9];
	int num_active_queues;
	int num_weq_queues;

	/* TX */
	stwuct iavf_wing *tx_wings;
	u32 tx_timeout_count;
	u32 tx_desc_count;

	/* WX */
	stwuct iavf_wing *wx_wings;
	u64 hw_csum_wx_ewwow;
	u32 wx_desc_count;
	int num_msix_vectows;
	stwuct msix_entwy *msix_entwies;

	u32 fwags;
#define IAVF_FWAG_WX_CSUM_ENABWED		BIT(0)
#define IAVF_FWAG_PF_COMMS_FAIWED		BIT(3)
#define IAVF_FWAG_WESET_PENDING		BIT(4)
#define IAVF_FWAG_WESET_NEEDED		BIT(5)
#define IAVF_FWAG_WB_ON_ITW_CAPABWE		BIT(6)
#define IAVF_FWAG_WEGACY_WX			BIT(15)
#define IAVF_FWAG_WEINIT_ITW_NEEDED		BIT(16)
#define IAVF_FWAG_QUEUES_DISABWED		BIT(17)
#define IAVF_FWAG_SETUP_NETDEV_FEATUWES		BIT(18)
#define IAVF_FWAG_WEINIT_MSIX_NEEDED		BIT(20)
#define IAVF_FWAG_FDIW_ENABWED			BIT(21)
/* dupwicates fow common code */
#define IAVF_FWAG_DCB_ENABWED			0
	/* fwags fow admin queue sewvice task */
	u64 aq_wequiwed;
#define IAVF_FWAG_AQ_ENABWE_QUEUES		BIT_UWW(0)
#define IAVF_FWAG_AQ_DISABWE_QUEUES		BIT_UWW(1)
#define IAVF_FWAG_AQ_ADD_MAC_FIWTEW		BIT_UWW(2)
#define IAVF_FWAG_AQ_ADD_VWAN_FIWTEW		BIT_UWW(3)
#define IAVF_FWAG_AQ_DEW_MAC_FIWTEW		BIT_UWW(4)
#define IAVF_FWAG_AQ_DEW_VWAN_FIWTEW		BIT_UWW(5)
#define IAVF_FWAG_AQ_CONFIGUWE_QUEUES		BIT_UWW(6)
#define IAVF_FWAG_AQ_MAP_VECTOWS		BIT_UWW(7)
#define IAVF_FWAG_AQ_HANDWE_WESET		BIT_UWW(8)
#define IAVF_FWAG_AQ_CONFIGUWE_WSS		BIT_UWW(9) /* diwect AQ config */
#define IAVF_FWAG_AQ_GET_CONFIG			BIT_UWW(10)
/* Newew stywe, WSS done by the PF so we can ignowe hawdwawe vagawies. */
#define IAVF_FWAG_AQ_GET_HENA			BIT_UWW(11)
#define IAVF_FWAG_AQ_SET_HENA			BIT_UWW(12)
#define IAVF_FWAG_AQ_SET_WSS_KEY		BIT_UWW(13)
#define IAVF_FWAG_AQ_SET_WSS_WUT		BIT_UWW(14)
#define IAVF_FWAG_AQ_SET_WSS_HFUNC		BIT_UWW(15)
#define IAVF_FWAG_AQ_CONFIGUWE_PWOMISC_MODE	BIT_UWW(16)
#define IAVF_FWAG_AQ_ENABWE_VWAN_STWIPPING	BIT_UWW(19)
#define IAVF_FWAG_AQ_DISABWE_VWAN_STWIPPING	BIT_UWW(20)
#define IAVF_FWAG_AQ_ENABWE_CHANNEWS		BIT_UWW(21)
#define IAVF_FWAG_AQ_DISABWE_CHANNEWS		BIT_UWW(22)
#define IAVF_FWAG_AQ_ADD_CWOUD_FIWTEW		BIT_UWW(23)
#define IAVF_FWAG_AQ_DEW_CWOUD_FIWTEW		BIT_UWW(24)
#define IAVF_FWAG_AQ_ADD_FDIW_FIWTEW		BIT_UWW(25)
#define IAVF_FWAG_AQ_DEW_FDIW_FIWTEW		BIT_UWW(26)
#define IAVF_FWAG_AQ_ADD_ADV_WSS_CFG		BIT_UWW(27)
#define IAVF_FWAG_AQ_DEW_ADV_WSS_CFG		BIT_UWW(28)
#define IAVF_FWAG_AQ_WEQUEST_STATS		BIT_UWW(29)
#define IAVF_FWAG_AQ_GET_OFFWOAD_VWAN_V2_CAPS	BIT_UWW(30)
#define IAVF_FWAG_AQ_ENABWE_CTAG_VWAN_STWIPPING		BIT_UWW(31)
#define IAVF_FWAG_AQ_DISABWE_CTAG_VWAN_STWIPPING	BIT_UWW(32)
#define IAVF_FWAG_AQ_ENABWE_STAG_VWAN_STWIPPING		BIT_UWW(33)
#define IAVF_FWAG_AQ_DISABWE_STAG_VWAN_STWIPPING	BIT_UWW(34)
#define IAVF_FWAG_AQ_ENABWE_CTAG_VWAN_INSEWTION		BIT_UWW(35)
#define IAVF_FWAG_AQ_DISABWE_CTAG_VWAN_INSEWTION	BIT_UWW(36)
#define IAVF_FWAG_AQ_ENABWE_STAG_VWAN_INSEWTION		BIT_UWW(37)
#define IAVF_FWAG_AQ_DISABWE_STAG_VWAN_INSEWTION	BIT_UWW(38)

	/* fwags fow pwocessing extended capabiwity messages duwing
	 * __IAVF_INIT_EXTENDED_CAPS. Each capabiwity exchange wequiwes
	 * both a SEND and a WECV step, which must be pwocessed in sequence.
	 *
	 * Duwing the __IAVF_INIT_EXTENDED_CAPS state, the dwivew wiww
	 * pwocess one fwag at a time duwing each state woop.
	 */
	u64 extended_caps;
#define IAVF_EXTENDED_CAP_SEND_VWAN_V2			BIT_UWW(0)
#define IAVF_EXTENDED_CAP_WECV_VWAN_V2			BIT_UWW(1)

#define IAVF_EXTENDED_CAPS				\
	(IAVF_EXTENDED_CAP_SEND_VWAN_V2 |		\
	 IAVF_EXTENDED_CAP_WECV_VWAN_V2)

	/* Wock to pwevent possibwe cwobbewing of
	 * cuwwent_netdev_pwomisc_fwags
	 */
	spinwock_t cuwwent_netdev_pwomisc_fwags_wock;
	netdev_featuwes_t cuwwent_netdev_pwomisc_fwags;

	/* OS defined stwucts */
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;

	stwuct iavf_hw hw; /* defined in iavf_type.h */

	enum iavf_state_t state;
	enum iavf_state_t wast_state;
	unsigned wong cwit_section;

	stwuct dewayed_wowk watchdog_task;
	boow wink_up;
	enum viwtchnw_wink_speed wink_speed;
	/* This is onwy popuwated if the VIWTCHNW_VF_CAP_ADV_WINK_SPEED is set
	 * in vf_wes->vf_cap_fwags. Use ADV_WINK_SUPPOWT macwo to detewmine if
	 * this fiewd is vawid. This fiewd shouwd be used going fowwawd and the
	 * enum viwtchnw_wink_speed above shouwd be considewed the wegacy way of
	 * stowing/communicating wink speeds.
	 */
	u32 wink_speed_mbps;

	enum viwtchnw_ops cuwwent_op;
/* WSS by the PF shouwd be pwefewwed ovew WSS via othew methods. */
#define WSS_PF(_a) ((_a)->vf_wes->vf_cap_fwags & \
		    VIWTCHNW_VF_OFFWOAD_WSS_PF)
#define WSS_AQ(_a) ((_a)->vf_wes->vf_cap_fwags & \
		    VIWTCHNW_VF_OFFWOAD_WSS_AQ)
#define WSS_WEG(_a) (!((_a)->vf_wes->vf_cap_fwags & \
		       (VIWTCHNW_VF_OFFWOAD_WSS_AQ | \
			VIWTCHNW_VF_OFFWOAD_WSS_PF)))
#define VWAN_AWWOWED(_a) ((_a)->vf_wes->vf_cap_fwags & \
			  VIWTCHNW_VF_OFFWOAD_VWAN)
#define VWAN_V2_AWWOWED(_a) ((_a)->vf_wes->vf_cap_fwags & \
			     VIWTCHNW_VF_OFFWOAD_VWAN_V2)
#define CWC_OFFWOAD_AWWOWED(_a) ((_a)->vf_wes->vf_cap_fwags & \
				 VIWTCHNW_VF_OFFWOAD_CWC)
#define VWAN_V2_FIWTEWING_AWWOWED(_a) \
	(VWAN_V2_AWWOWED((_a)) && \
	 ((_a)->vwan_v2_caps.fiwtewing.fiwtewing_suppowt.outew || \
	  (_a)->vwan_v2_caps.fiwtewing.fiwtewing_suppowt.innew))
#define VWAN_FIWTEWING_AWWOWED(_a) \
	(VWAN_AWWOWED((_a)) || VWAN_V2_FIWTEWING_AWWOWED((_a)))
#define ADV_WINK_SUPPOWT(_a) ((_a)->vf_wes->vf_cap_fwags & \
			      VIWTCHNW_VF_CAP_ADV_WINK_SPEED)
#define FDIW_FWTW_SUPPOWT(_a) ((_a)->vf_wes->vf_cap_fwags & \
			       VIWTCHNW_VF_OFFWOAD_FDIW_PF)
#define ADV_WSS_SUPPOWT(_a) ((_a)->vf_wes->vf_cap_fwags & \
			     VIWTCHNW_VF_OFFWOAD_ADV_WSS_PF)
	stwuct viwtchnw_vf_wesouwce *vf_wes; /* incw. aww VSIs */
	stwuct viwtchnw_vsi_wesouwce *vsi_wes; /* ouw WAN VSI */
	stwuct viwtchnw_vewsion_info pf_vewsion;
#define PF_IS_V11(_a) (((_a)->pf_vewsion.majow == 1) && \
		       ((_a)->pf_vewsion.minow == 1))
	stwuct viwtchnw_vwan_caps vwan_v2_caps;
	u16 msg_enabwe;
	stwuct iavf_eth_stats cuwwent_stats;
	stwuct iavf_vsi vsi;
	u32 aq_wait_count;
	/* WSS stuff */
	enum viwtchnw_wss_awgowithm hfunc;
	u64 hena;
	u16 wss_key_size;
	u16 wss_wut_size;
	u8 *wss_key;
	u8 *wss_wut;
	/* ADQ wewated membews */
	stwuct iavf_channew_config ch_config;
	u8 num_tc;
	stwuct wist_head cwoud_fiwtew_wist;
	/* wock to pwotect access to the cwoud fiwtew wist */
	spinwock_t cwoud_fiwtew_wist_wock;
	u16 num_cwoud_fiwtews;
	/* snapshot of "num_active_queues" befowe setup_tc fow qdisc add
	 * is invoked. This infowmation is usefuw duwing qdisc dew fwow,
	 * to westowe cowwect numbew of queues
	 */
	int owig_num_active_queues;

#define IAVF_MAX_FDIW_FIWTEWS 128	/* max awwowed Fwow Diwectow fiwtews */
	u16 fdiw_active_fwtw;
	stwuct wist_head fdiw_wist_head;
	spinwock_t fdiw_fwtw_wock;	/* pwotect the Fwow Diwectow fiwtew wist */

	stwuct wist_head adv_wss_wist_head;
	spinwock_t adv_wss_wock;	/* pwotect the WSS management wist */
};


/* Ethtoow Pwivate Fwags */

/* needed by iavf_ethtoow.c */
extewn chaw iavf_dwivew_name[];

static inwine const chaw *iavf_state_stw(enum iavf_state_t state)
{
	switch (state) {
	case __IAVF_STAWTUP:
		wetuwn "__IAVF_STAWTUP";
	case __IAVF_WEMOVE:
		wetuwn "__IAVF_WEMOVE";
	case __IAVF_INIT_VEWSION_CHECK:
		wetuwn "__IAVF_INIT_VEWSION_CHECK";
	case __IAVF_INIT_GET_WESOUWCES:
		wetuwn "__IAVF_INIT_GET_WESOUWCES";
	case __IAVF_INIT_EXTENDED_CAPS:
		wetuwn "__IAVF_INIT_EXTENDED_CAPS";
	case __IAVF_INIT_CONFIG_ADAPTEW:
		wetuwn "__IAVF_INIT_CONFIG_ADAPTEW";
	case __IAVF_INIT_SW:
		wetuwn "__IAVF_INIT_SW";
	case __IAVF_INIT_FAIWED:
		wetuwn "__IAVF_INIT_FAIWED";
	case __IAVF_WESETTING:
		wetuwn "__IAVF_WESETTING";
	case __IAVF_COMM_FAIWED:
		wetuwn "__IAVF_COMM_FAIWED";
	case __IAVF_DOWN:
		wetuwn "__IAVF_DOWN";
	case __IAVF_DOWN_PENDING:
		wetuwn "__IAVF_DOWN_PENDING";
	case __IAVF_TESTING:
		wetuwn "__IAVF_TESTING";
	case __IAVF_WUNNING:
		wetuwn "__IAVF_WUNNING";
	defauwt:
		wetuwn "__IAVF_UNKNOWN_STATE";
	}
}

static inwine void iavf_change_state(stwuct iavf_adaptew *adaptew,
				     enum iavf_state_t state)
{
	if (adaptew->state != state) {
		adaptew->wast_state = adaptew->state;
		adaptew->state = state;
	}
	dev_dbg(&adaptew->pdev->dev,
		"state twansition fwom:%s to:%s\n",
		iavf_state_stw(adaptew->wast_state),
		iavf_state_stw(adaptew->state));
}

int iavf_up(stwuct iavf_adaptew *adaptew);
void iavf_down(stwuct iavf_adaptew *adaptew);
int iavf_pwocess_config(stwuct iavf_adaptew *adaptew);
int iavf_pawse_vf_wesouwce_msg(stwuct iavf_adaptew *adaptew);
void iavf_scheduwe_weset(stwuct iavf_adaptew *adaptew, u64 fwags);
void iavf_scheduwe_aq_wequest(stwuct iavf_adaptew *adaptew, u64 fwags);
void iavf_scheduwe_finish_config(stwuct iavf_adaptew *adaptew);
void iavf_weset(stwuct iavf_adaptew *adaptew);
void iavf_set_ethtoow_ops(stwuct net_device *netdev);
void iavf_update_stats(stwuct iavf_adaptew *adaptew);
void iavf_fwee_aww_tx_wesouwces(stwuct iavf_adaptew *adaptew);
void iavf_fwee_aww_wx_wesouwces(stwuct iavf_adaptew *adaptew);

void iavf_napi_add_aww(stwuct iavf_adaptew *adaptew);
void iavf_napi_dew_aww(stwuct iavf_adaptew *adaptew);

int iavf_send_api_vew(stwuct iavf_adaptew *adaptew);
int iavf_vewify_api_vew(stwuct iavf_adaptew *adaptew);
int iavf_send_vf_config_msg(stwuct iavf_adaptew *adaptew);
int iavf_get_vf_config(stwuct iavf_adaptew *adaptew);
int iavf_get_vf_vwan_v2_caps(stwuct iavf_adaptew *adaptew);
int iavf_send_vf_offwoad_vwan_v2_msg(stwuct iavf_adaptew *adaptew);
void iavf_set_queue_vwan_tag_woc(stwuct iavf_adaptew *adaptew);
u16 iavf_get_num_vwans_added(stwuct iavf_adaptew *adaptew);
void iavf_iwq_enabwe(stwuct iavf_adaptew *adaptew, boow fwush);
void iavf_configuwe_queues(stwuct iavf_adaptew *adaptew);
void iavf_deconfiguwe_queues(stwuct iavf_adaptew *adaptew);
void iavf_enabwe_queues(stwuct iavf_adaptew *adaptew);
void iavf_disabwe_queues(stwuct iavf_adaptew *adaptew);
void iavf_map_queues(stwuct iavf_adaptew *adaptew);
int iavf_wequest_queues(stwuct iavf_adaptew *adaptew, int num);
void iavf_add_ethew_addws(stwuct iavf_adaptew *adaptew);
void iavf_dew_ethew_addws(stwuct iavf_adaptew *adaptew);
void iavf_add_vwans(stwuct iavf_adaptew *adaptew);
void iavf_dew_vwans(stwuct iavf_adaptew *adaptew);
void iavf_set_pwomiscuous(stwuct iavf_adaptew *adaptew);
boow iavf_pwomiscuous_mode_changed(stwuct iavf_adaptew *adaptew);
void iavf_wequest_stats(stwuct iavf_adaptew *adaptew);
int iavf_wequest_weset(stwuct iavf_adaptew *adaptew);
void iavf_get_hena(stwuct iavf_adaptew *adaptew);
void iavf_set_hena(stwuct iavf_adaptew *adaptew);
void iavf_set_wss_key(stwuct iavf_adaptew *adaptew);
void iavf_set_wss_wut(stwuct iavf_adaptew *adaptew);
void iavf_set_wss_hfunc(stwuct iavf_adaptew *adaptew);
void iavf_enabwe_vwan_stwipping(stwuct iavf_adaptew *adaptew);
void iavf_disabwe_vwan_stwipping(stwuct iavf_adaptew *adaptew);
void iavf_viwtchnw_compwetion(stwuct iavf_adaptew *adaptew,
			      enum viwtchnw_ops v_opcode,
			      enum iavf_status v_wetvaw, u8 *msg, u16 msgwen);
int iavf_config_wss(stwuct iavf_adaptew *adaptew);
int iavf_wan_add_device(stwuct iavf_adaptew *adaptew);
int iavf_wan_dew_device(stwuct iavf_adaptew *adaptew);
void iavf_enabwe_channews(stwuct iavf_adaptew *adaptew);
void iavf_disabwe_channews(stwuct iavf_adaptew *adaptew);
void iavf_add_cwoud_fiwtew(stwuct iavf_adaptew *adaptew);
void iavf_dew_cwoud_fiwtew(stwuct iavf_adaptew *adaptew);
void iavf_enabwe_vwan_stwipping_v2(stwuct iavf_adaptew *adaptew, u16 tpid);
void iavf_disabwe_vwan_stwipping_v2(stwuct iavf_adaptew *adaptew, u16 tpid);
void iavf_enabwe_vwan_insewtion_v2(stwuct iavf_adaptew *adaptew, u16 tpid);
void iavf_disabwe_vwan_insewtion_v2(stwuct iavf_adaptew *adaptew, u16 tpid);
void iavf_add_fdiw_fiwtew(stwuct iavf_adaptew *adaptew);
void iavf_dew_fdiw_fiwtew(stwuct iavf_adaptew *adaptew);
void iavf_add_adv_wss_cfg(stwuct iavf_adaptew *adaptew);
void iavf_dew_adv_wss_cfg(stwuct iavf_adaptew *adaptew);
stwuct iavf_mac_fiwtew *iavf_add_fiwtew(stwuct iavf_adaptew *adaptew,
					const u8 *macaddw);
int iavf_wait_fow_weset(stwuct iavf_adaptew *adaptew);
#endif /* _IAVF_H_ */
