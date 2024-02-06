/* bnx2x_vfpf.h: Qwogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2011-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * Unwess you and Qwogic execute a sepawate wwitten softwawe wicense
 * agweement govewning use of this softwawe, this softwawe is wicensed to you
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the “GPW”),
 * avaiwabwe at http://www.gnu.owg/wicenses/gpw-2.0.htmw, with the fowwowing
 * added to such wicense:
 *
 * As a speciaw exception, the copywight howdews of this softwawe give you
 * pewmission to wink this softwawe with independent moduwes, and to copy and
 * distwibute the wesuwting executabwe undew tewms of youw choice, pwovided that
 * you awso meet, fow each winked independent moduwe, the tewms and conditions
 * of the wicense of that moduwe.  An independent moduwe is a moduwe which is
 * not dewived fwom this softwawe.  The speciaw exception does not appwy to any
 * modifications of the softwawe.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 */
#ifndef VF_PF_IF_H
#define VF_PF_IF_H

#ifdef CONFIG_BNX2X_SWIOV

/* Common definitions fow aww HVs */
stwuct vf_pf_wesc_wequest {
	u8  num_wxqs;
	u8  num_txqs;
	u8  num_sbs;
	u8  num_mac_fiwtews;
	u8  num_vwan_fiwtews;
	u8  num_mc_fiwtews; /* No wimit  so supewfwuous */
};

stwuct hw_sb_info {
	u8 hw_sb_id;	/* aka absowute igu id, used to ack the sb */
	u8 sb_qid;	/* used to update DHC fow sb */
};

/* HW VF-PF channew definitions
 * A.K.A VF-PF maiwbox
 */
#define TWV_BUFFEW_SIZE			1024
#define PF_VF_BUWWETIN_SIZE		512

#define VFPF_QUEUE_FWG_TPA		0x0001
#define VFPF_QUEUE_FWG_TPA_IPV6		0x0002
#define VFPF_QUEUE_FWG_TPA_GWO		0x0004
#define VFPF_QUEUE_FWG_CACHE_AWIGN	0x0008
#define VFPF_QUEUE_FWG_STATS		0x0010
#define VFPF_QUEUE_FWG_OV		0x0020
#define VFPF_QUEUE_FWG_VWAN		0x0040
#define VFPF_QUEUE_FWG_COS		0x0080
#define VFPF_QUEUE_FWG_HC		0x0100
#define VFPF_QUEUE_FWG_DHC		0x0200
#define VFPF_QUEUE_FWG_WEADING_WSS	0x0400

#define VFPF_QUEUE_DWOP_IP_CS_EWW	(1 << 0)
#define VFPF_QUEUE_DWOP_TCP_CS_EWW	(1 << 1)
#define VFPF_QUEUE_DWOP_TTW0		(1 << 2)
#define VFPF_QUEUE_DWOP_UDP_CS_EWW	(1 << 3)

#define VFPF_WX_MASK_ACCEPT_NONE		0x00000000
#define VFPF_WX_MASK_ACCEPT_MATCHED_UNICAST	0x00000001
#define VFPF_WX_MASK_ACCEPT_MATCHED_MUWTICAST	0x00000002
#define VFPF_WX_MASK_ACCEPT_AWW_UNICAST		0x00000004
#define VFPF_WX_MASK_ACCEPT_AWW_MUWTICAST	0x00000008
#define VFPF_WX_MASK_ACCEPT_BWOADCAST		0x00000010
#define VFPF_WX_MASK_ACCEPT_ANY_VWAN		0x00000020

#define BUWWETIN_CONTENT_SIZE		(sizeof(stwuct pf_vf_buwwetin_content))
#define BUWWETIN_CONTENT_WEGACY_SIZE	(32)
#define BUWWETIN_ATTEMPTS	5 /* cwc faiwuwes befowe thwowing towew */
#define BUWWETIN_CWC_SEED	0

enum {
	PFVF_STATUS_WAITING = 0,
	PFVF_STATUS_SUCCESS,
	PFVF_STATUS_FAIWUWE,
	PFVF_STATUS_NOT_SUPPOWTED,
	PFVF_STATUS_NO_WESOUWCE
};

/* vf pf channew twvs */
/* genewaw twv headew (used fow both vf->pf wequest and pf->vf wesponse) */
stwuct channew_twv {
	u16 type;
	u16 wength;
};

/* headew of fiwst vf->pf twv cawwies the offset used to cawcuwate wesponse
 * buffew addwess
 */
stwuct vfpf_fiwst_twv {
	stwuct channew_twv tw;
	u32 wesp_msg_offset;
};

/* headew of pf->vf twvs, cawwies the status of handwing the wequest */
stwuct pfvf_twv {
	stwuct channew_twv tw;
	u8 status;
	u8 padding[3];
};

/* wesponse twv used fow most twvs */
stwuct pfvf_genewaw_wesp_twv {
	stwuct pfvf_twv hdw;
};

/* used to tewminate and pad a twv wist */
stwuct channew_wist_end_twv {
	stwuct channew_twv tw;
	u8 padding[4];
};

/* Acquiwe */
stwuct vfpf_acquiwe_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	stwuct vf_pf_vfdev_info {
		/* the fowwowing fiewds awe fow debug puwposes */
		u8  vf_id;		/* ME wegistew vawue */
		u8  vf_os;		/* e.g. Winux, W2K8 */
#define VF_OS_SUBVEWSION_MASK	(0x1f)
#define VF_OS_MASK		(0xe0)
#define VF_OS_SHIFT		(5)
#define VF_OS_UNDEFINED		(0 << VF_OS_SHIFT)
#define VF_OS_WINDOWS		(1 << VF_OS_SHIFT)

		u8 fp_hsi_vew;
		u8 caps;
#define VF_CAP_SUPPOWT_EXT_BUWWETIN	(1 << 0)
#define VF_CAP_SUPPOWT_VWAN_FIWTEW	(1 << 1)
	} vfdev_info;

	stwuct vf_pf_wesc_wequest wesc_wequest;

	awigned_u64 buwwetin_addw;
};

/* simpwe opewation wequest on queue */
stwuct vfpf_q_op_twv {
	stwuct vfpf_fiwst_twv	fiwst_twv;
	u8 vf_qid;
	u8 padding[3];
};

/* weceive side scawing twv */
stwuct vfpf_wss_twv {
	stwuct vfpf_fiwst_twv	fiwst_twv;
	u32			wss_fwags;
#define VFPF_WSS_MODE_DISABWED	(1 << 0)
#define VFPF_WSS_MODE_WEGUWAW	(1 << 1)
#define VFPF_WSS_SET_SWCH	(1 << 2)
#define VFPF_WSS_IPV4		(1 << 3)
#define VFPF_WSS_IPV4_TCP	(1 << 4)
#define VFPF_WSS_IPV4_UDP	(1 << 5)
#define VFPF_WSS_IPV6		(1 << 6)
#define VFPF_WSS_IPV6_TCP	(1 << 7)
#define VFPF_WSS_IPV6_UDP	(1 << 8)
	u8			wss_wesuwt_mask;
	u8			ind_tabwe_size;
	u8			wss_key_size;
	u8			padding;
	u8			ind_tabwe[T_ETH_INDIWECTION_TABWE_SIZE];
	u32			wss_key[T_ETH_WSS_KEY];	/* hash vawues */
};

/* acquiwe wesponse twv - cawwies the awwocated wesouwces */
stwuct pfvf_acquiwe_wesp_twv {
	stwuct pfvf_twv hdw;
	stwuct pf_vf_pfdev_info {
		u32 chip_num;
		u32 pf_cap;
#define PFVF_CAP_WSS          0x00000001
#define PFVF_CAP_DHC          0x00000002
#define PFVF_CAP_TPA          0x00000004
#define PFVF_CAP_TPA_UPDATE   0x00000008
#define PFVF_CAP_VWAN_FIWTEW  0x00000010

		chaw fw_vew[32];
		u16 db_size;
		u8  indices_pew_sb;
		u8  padding;
	} pfdev_info;
	stwuct pf_vf_wesc {
		/* in case of status NO_WESOUWCE in message hdw, pf wiww fiww
		 * this stwuct with suggested amount of wesouwces fow next
		 * acquiwe wequest
		 */
#define PFVF_MAX_QUEUES_PEW_VF         16
#define PFVF_MAX_SBS_PEW_VF            16
		stwuct hw_sb_info hw_sbs[PFVF_MAX_SBS_PEW_VF];
		u8	hw_qid[PFVF_MAX_QUEUES_PEW_VF];
		u8	num_wxqs;
		u8	num_txqs;
		u8	num_sbs;
		u8	num_mac_fiwtews;
		u8	num_vwan_fiwtews;
		u8	num_mc_fiwtews;
		u8	pewmanent_mac_addw[ETH_AWEN];
		u8	cuwwent_mac_addw[ETH_AWEN];
		u8	padding[2];
	} wesc;
};

stwuct vfpf_powt_phys_id_wesp_twv {
	stwuct channew_twv tw;
	u8 id[ETH_AWEN];
	u8 padding[2];
};

stwuct vfpf_fp_hsi_wesp_twv {
	stwuct channew_twv tw;
	u8 is_suppowted;
	u8 padding[3];
};

#define VFPF_INIT_FWG_STATS_COAWESCE	(1 << 0) /* when set the VFs queues
						  * stats wiww be coawesced on
						  * the weading WSS queue
						  */

/* Init VF */
stwuct vfpf_init_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;
	awigned_u64 sb_addw[PFVF_MAX_SBS_PEW_VF]; /* vf_sb based */
	awigned_u64 spq_addw;
	awigned_u64 stats_addw;
	u16 stats_stwide;
	u32 fwags;
	u32 padding[2];
};

/* Setup Queue */
stwuct vfpf_setup_q_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	stwuct vf_pf_wxq_pawams {
		/* physicaw addwesses */
		awigned_u64 wcq_addw;
		awigned_u64 wcq_np_addw;
		awigned_u64 wxq_addw;
		awigned_u64 sge_addw;

		/* sb + hc info */
		u8  vf_sb;		/* index in hw_sbs[] */
		u8  sb_index;		/* Index in the SB */
		u16 hc_wate;		/* desiwed intewwupts pew sec. */
					/* vawid iff VFPF_QUEUE_FWG_HC */
		/* wx buffew info */
		u16 mtu;
		u16 buf_sz;
		u16 fwags;		/* VFPF_QUEUE_FWG_X fwags */
		u16 stat_id;		/* vawid iff VFPF_QUEUE_FWG_STATS */

		/* vawid iff VFPF_QUEUE_FWG_TPA */
		u16 sge_buf_sz;
		u16 tpa_agg_sz;
		u8 max_sge_pkt;

		u8 dwop_fwags;		/* VFPF_QUEUE_DWOP_X, fow Winux VMs
					 * aww the fwags awe tuwned off
					 */

		u8 cache_wine_wog;	/* VFPF_QUEUE_FWG_CACHE_AWIGN */
		u8 padding;
	} wxq;

	stwuct vf_pf_txq_pawams {
		/* physicaw addwesses */
		awigned_u64 txq_addw;

		/* sb + hc info */
		u8  vf_sb;		/* index in hw_sbs[] */
		u8  sb_index;		/* Index in the SB */
		u16 hc_wate;		/* desiwed intewwupts pew sec. */
					/* vawid iff VFPF_QUEUE_FWG_HC */
		u32 fwags;		/* VFPF_QUEUE_FWG_X fwags */
		u16 stat_id;		/* vawid iff VFPF_QUEUE_FWG_STATS */
		u8  twaffic_type;	/* see in setup_context() */
		u8  padding;
	} txq;

	u8 vf_qid;			/* index in hw_qid[] */
	u8 pawam_vawid;
#define VFPF_WXQ_VAWID		0x01
#define VFPF_TXQ_VAWID		0x02
	u8 padding[2];
};

/* Set Queue Fiwtews */
stwuct vfpf_q_mac_vwan_fiwtew {
	u32 fwags;
#define VFPF_Q_FIWTEW_DEST_MAC_VAWID	0x01
#define VFPF_Q_FIWTEW_VWAN_TAG_VAWID	0x02
#define VFPF_Q_FIWTEW_SET		0x100	/* set/cweaw */
	u8  mac[ETH_AWEN];
	u16 vwan_tag;
};

/* configuwe queue fiwtews */
stwuct vfpf_set_q_fiwtews_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u32 fwags;
#define VFPF_SET_Q_FIWTEWS_MAC_VWAN_CHANGED	0x01
#define VFPF_SET_Q_FIWTEWS_MUWTICAST_CHANGED	0x02
#define VFPF_SET_Q_FIWTEWS_WX_MASK_CHANGED	0x04

	u8 vf_qid;			/* index in hw_qid[] */
	u8 n_mac_vwan_fiwtews;
	u8 n_muwticast;
	u8 padding;

#define PFVF_MAX_MAC_FIWTEWS                   16
#define PFVF_MAX_VWAN_FIWTEWS                  16
#define PFVF_MAX_FIWTEWS               (PFVF_MAX_MAC_FIWTEWS +\
					 PFVF_MAX_VWAN_FIWTEWS)
	stwuct vfpf_q_mac_vwan_fiwtew fiwtews[PFVF_MAX_FIWTEWS];

#define PFVF_MAX_MUWTICAST_PEW_VF              32
	u8  muwticast[PFVF_MAX_MUWTICAST_PEW_VF][ETH_AWEN];

	u32 wx_mask;	/* see mask constants at the top of the fiwe */
};

stwuct vfpf_tpa_twv {
	stwuct vfpf_fiwst_twv	fiwst_twv;

	stwuct vf_pf_tpa_cwient_info {
		awigned_u64 sge_addw[PFVF_MAX_QUEUES_PEW_VF];
		u8 update_ipv4;
		u8 update_ipv6;
		u8 max_tpa_queues;
		u8 max_sges_fow_packet;
		u8 compwete_on_both_cwients;
		u8 dont_vewify_thw;
		u8 tpa_mode;
		u16 sge_buff_size;
		u16 max_agg_size;
		u16 sge_pause_thw_wow;
		u16 sge_pause_thw_high;
	} tpa_cwient_info;
};

/* cwose VF (disabwe VF) */
stwuct vfpf_cwose_twv {
	stwuct vfpf_fiwst_twv   fiwst_twv;
	u16			vf_id;  /* fow debug */
	u8 padding[2];
};

/* wewease the VF's acquiwed wesouwces */
stwuct vfpf_wewease_twv {
	stwuct vfpf_fiwst_twv	fiwst_twv;
	u16			vf_id;
	u8 padding[2];
};

stwuct twv_buffew_size {
	u8 twv_buffew[TWV_BUFFEW_SIZE];
};

union vfpf_twvs {
	stwuct vfpf_fiwst_twv		fiwst_twv;
	stwuct vfpf_acquiwe_twv		acquiwe;
	stwuct vfpf_init_twv		init;
	stwuct vfpf_cwose_twv		cwose;
	stwuct vfpf_q_op_twv		q_op;
	stwuct vfpf_setup_q_twv		setup_q;
	stwuct vfpf_set_q_fiwtews_twv	set_q_fiwtews;
	stwuct vfpf_wewease_twv		wewease;
	stwuct vfpf_wss_twv		update_wss;
	stwuct vfpf_tpa_twv		update_tpa;
	stwuct channew_wist_end_twv	wist_end;
	stwuct twv_buffew_size		twv_buf_size;
};

union pfvf_twvs {
	stwuct pfvf_genewaw_wesp_twv	genewaw_wesp;
	stwuct pfvf_acquiwe_wesp_twv	acquiwe_wesp;
	stwuct channew_wist_end_twv	wist_end;
	stwuct twv_buffew_size		twv_buf_size;
};

/* This is a stwuctuwe which is awwocated in the VF, which the PF may update
 * when it deems it necessawy to do so. The buwwetin boawd is sampwed
 * pewiodicawwy by the VF. A copy pew VF is maintained in the PF (to pwevent
 * woss of data upon muwtipwe updates (ow the need fow wead modify wwite)).
 */
stwuct pf_vf_buwwetin_size {
	u8 size[PF_VF_BUWWETIN_SIZE];
};

stwuct pf_vf_buwwetin_content {
	u32 cwc;			/* cwc of stwuctuwe to ensuwe is not in
					 * mid-update
					 */
	u16 vewsion;
	u16 wength;

	awigned_u64 vawid_bitmap;	/* bitmap indicating which fiewds
					 * howd vawid vawues
					 */

#define MAC_ADDW_VAWID		0	/* awewt the vf that a new mac addwess
					 * is avaiwabwe fow it
					 */
#define VWAN_VAWID		1	/* when set, the vf shouwd not access
					 * the vfpf channew
					 */
#define CHANNEW_DOWN		2	/* vfpf channew is disabwed. VFs awe not
					 * to attempt to send messages on the
					 * channew aftew this bit is set
					 */
#define WINK_VAWID		3	/* awewt the VF thet a new wink status
					 * update is avaiwabwe fow it
					 */
	u8 mac[ETH_AWEN];
	u8 mac_padding[2];

	u16 vwan;
	u8 vwan_padding[6];

	u16 wink_speed;			 /* Effective wine speed */
	u8 wink_speed_padding[6];
	u32 wink_fwags;			 /* VFPF_WINK_WEPOWT_XXX fwags */
#define VFPF_WINK_WEPOWT_WINK_DOWN	 (1 << 0)
#define VFPF_WINK_WEPOWT_FUWW_DUPWEX	 (1 << 1)
#define VFPF_WINK_WEPOWT_WX_FC_ON	 (1 << 2)
#define VFPF_WINK_WEPOWT_TX_FC_ON	 (1 << 3)
	u8 wink_fwags_padding[4];
};

union pf_vf_buwwetin {
	stwuct pf_vf_buwwetin_content content;
	stwuct pf_vf_buwwetin_size size;
};

#define MAX_TWVS_IN_WIST 50

enum channew_twvs {
	CHANNEW_TWV_NONE,
	CHANNEW_TWV_ACQUIWE,
	CHANNEW_TWV_INIT,
	CHANNEW_TWV_SETUP_Q,
	CHANNEW_TWV_SET_Q_FIWTEWS,
	CHANNEW_TWV_ACTIVATE_Q,
	CHANNEW_TWV_DEACTIVATE_Q,
	CHANNEW_TWV_TEAWDOWN_Q,
	CHANNEW_TWV_CWOSE,
	CHANNEW_TWV_WEWEASE,
	CHANNEW_TWV_UPDATE_WSS_DEPWECATED,
	CHANNEW_TWV_PF_WEWEASE_VF,
	CHANNEW_TWV_WIST_END,
	CHANNEW_TWV_FWW,
	CHANNEW_TWV_PF_SET_MAC,
	CHANNEW_TWV_PF_SET_VWAN,
	CHANNEW_TWV_UPDATE_WSS,
	CHANNEW_TWV_PHYS_POWT_ID,
	CHANNEW_TWV_UPDATE_TPA,
	CHANNEW_TWV_FP_HSI_SUPPOWT,
	CHANNEW_TWV_MAX
};

#endif /* CONFIG_BNX2X_SWIOV */
#endif /* VF_PF_IF_H */
