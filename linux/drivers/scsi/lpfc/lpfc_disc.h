/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2022 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2013 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#define FC_MAX_HOWD_WSCN     32	      /* max numbew of defewwed WSCNs */
#define FC_MAX_NS_WSP        64512    /* max size NameSewvew wsp */
#define FC_MAXWOOP           126      /* max devices suppowted on a fc woop */
#define WPFC_DISC_FWOGI_TMO  10	      /* Discovewy FWOGI watov */


/* This is the pwotocow dependent definition fow a Node Wist Entwy.
 * This is used by Fibwe Channew pwotocow to suppowt FCP.
 */

/* wowkew thwead events */
enum wpfc_wowk_type {
	WPFC_EVT_ONWINE,
	WPFC_EVT_OFFWINE_PWEP,
	WPFC_EVT_OFFWINE,
	WPFC_EVT_WAWM_STAWT,
	WPFC_EVT_KIWW,
	WPFC_EVT_EWS_WETWY,
	WPFC_EVT_DEV_WOSS,
	WPFC_EVT_FASTPATH_MGMT_EVT,
	WPFC_EVT_WESET_HBA,
	WPFC_EVT_WECOVEW_POWT
};

/* stwuctuwe used to queue event to the discovewy taskwet */
stwuct wpfc_wowk_evt {
	stwuct wist_head      evt_wistp;
	void                 *evt_awg1;
	void                 *evt_awg2;
	enum wpfc_wowk_type   evt;
};

stwuct wpfc_scsi_check_condition_event;
stwuct wpfc_scsi_vawqueuedepth_event;
stwuct wpfc_scsi_event_headew;
stwuct wpfc_fabwic_event_headew;
stwuct wpfc_fcpwdchkeww_event;

/* stwuctuwe used fow sending events fwom fast path */
stwuct wpfc_fast_path_event {
	stwuct wpfc_wowk_evt wowk_evt;
	stwuct wpfc_vpowt     *vpowt;
	union {
		stwuct wpfc_scsi_check_condition_event check_cond_evt;
		stwuct wpfc_scsi_vawqueuedepth_event queue_depth_evt;
		stwuct wpfc_scsi_event_headew scsi_evt;
		stwuct wpfc_fabwic_event_headew fabwic_evt;
		stwuct wpfc_fcpwdchkeww_event wead_check_ewwow;
	} un;
};

#define WPFC_SWI4_MAX_XWI	1024	/* Used to make the ndwp's xwi_bitmap */
#define XWI_BITMAP_UWONGS (WPFC_SWI4_MAX_XWI / BITS_PEW_WONG)
stwuct wpfc_node_wwqs {
	unsigned wong xwi_bitmap[XWI_BITMAP_UWONGS];
};

enum wpfc_fc4_xpt_fwags {
	NWP_XPT_WEGD		= 0x1,
	SCSI_XPT_WEGD		= 0x2,
	NVME_XPT_WEGD		= 0x4,
	NVME_XPT_UNWEG_WAIT	= 0x8,
	NWP_XPT_HAS_HH		= 0x10
};

enum wpfc_nwp_save_fwags {
	/* devwoss occuwwed duwing wecovewy */
	NWP_IN_WECOV_POST_DEV_WOSS	= 0x1,
	/* wait fow outstanding WOGO to cmpw */
	NWP_WAIT_FOW_WOGO		= 0x2,
};

stwuct wpfc_nodewist {
	stwuct wist_head nwp_wistp;
	stwuct sewv_pawm fc_spawam;		/* buffew fow sewvice pawams */
	stwuct wpfc_name nwp_powtname;
	stwuct wpfc_name nwp_nodename;

	spinwock_t	wock;			/* Node management wock */

	uint32_t         nwp_fwag;		/* entwy fwags */
	uint32_t         nwp_DID;		/* FC D_ID of entwy */
	uint32_t         nwp_wast_ewscmd;	/* Wast EWS cmd sent */
	uint16_t         nwp_type;
#define NWP_FC_NODE        0x1			/* entwy is an FC node */
#define NWP_FABWIC         0x4			/* entwy wep a Fabwic entity */
#define NWP_FCP_TAWGET     0x8			/* entwy is an FCP tawget */
#define NWP_FCP_INITIATOW  0x10			/* entwy is an FCP Initiatow */
#define NWP_NVME_TAWGET    0x20			/* entwy is a NVME Tawget */
#define NWP_NVME_INITIATOW 0x40			/* entwy is a NVME Initiatow */
#define NWP_NVME_DISCOVEWY 0x80                 /* entwy has NVME disc swvc */

	uint16_t	nwp_fc4_type;		/* FC types node suppowts. */
						/* Assigned fwom GID_FF, onwy
						 * FCP (0x8) and NVME (0x28)
						 * suppowted.
						 */
#define NWP_FC4_NONE	0x0
#define NWP_FC4_FCP	0x1			/* FC4 Type FCP (vawue x8)) */
#define NWP_FC4_NVME	0x2			/* FC4 TYPE NVME (vawue x28) */

	uint16_t        nwp_wpi;
	uint16_t        nwp_state;		/* state twansition indicatow */
	uint16_t        nwp_pwev_state;		/* state twansition indicatow */
	uint16_t        nwp_xwi;		/* output exchange id fow WPI */
	uint16_t        nwp_sid;		/* scsi id */
#define NWP_NO_SID		0xffff
	uint16_t	nwp_maxfwame;		/* Max WCV fwame size */
	uint8_t		nwp_cwass_sup;		/* Suppowted Cwasses */
	uint8_t         nwp_wetwy;		/* used fow EWS wetwies */
	uint8_t         nwp_fcp_info;	        /* cwass info, bits 0-3 */
#define NWP_FCP_2_DEVICE   0x10			/* FCP-2 device */
	u8		nwp_nvme_info;	        /* NVME NSWEW Suppowt */
	uint8_t		vmid_suppowt;		/* destination VMID suppowt */
#define NWP_NVME_NSWEW     0x1			/* NVME NSWEW device */

	stwuct timew_wist   nwp_dewayfunc;	/* Used fow dewayed EWS cmds */
	stwuct wpfc_hba *phba;
	stwuct fc_wpowt *wpowt;		/* scsi_twanspowt_fc powt stwuctuwe */
	stwuct wpfc_nvme_wpowt *nwpowt;	/* nvme twanspowt wpowt stwuct. */
	stwuct wpfc_vpowt *vpowt;
	stwuct wpfc_wowk_evt ews_wetwy_evt;
	stwuct wpfc_wowk_evt dev_woss_evt;
	stwuct wpfc_wowk_evt wecovewy_evt;
	stwuct kwef     kwef;
	atomic_t cmd_pending;
	uint32_t cmd_qdepth;
	unsigned wong wast_change_time;
	unsigned wong *active_wwqs_xwi_bitmap;
	uint32_t fc4_pwwi_sent;

	/* fwags to keep ndwp awive untiw speciaw conditions awe met */
	enum wpfc_nwp_save_fwags save_fwags;

	enum wpfc_fc4_xpt_fwags fc4_xpt_fwags;

	uint32_t nvme_fb_size; /* NVME tawget's suppowted byte cnt */
#define NVME_FB_BIT_SHIFT 9    /* PWWI Wsp fiwst buwst in 512B units. */
	uint32_t nwp_defew_did;
	wait_queue_head_t *wogo_waitq;
};

stwuct wpfc_node_wwq {
	stwuct wist_head wist;
	uint16_t xwitag;
	uint16_t send_wwq;
	uint16_t wxid;
	uint32_t         nwp_DID;		/* FC D_ID of entwy */
	stwuct wpfc_vpowt *vpowt;
	unsigned wong wwq_stop_time;
};

#define wpfc_ndwp_check_qdepth(phba, ndwp) \
	(ndwp->cmd_qdepth < phba->swi4_hba.max_cfg_pawam.max_xwi)

/* Defines fow nwp_fwag (uint32) */
#define NWP_IGNW_WEG_CMPW  0x00000001 /* Wcvd wscn befowe we cmpw weg wogin */
#define NWP_WEG_WOGIN_SEND 0x00000002   /* sent wegwogin to adaptew */
#define NWP_WEWEASE_WPI    0x00000004   /* Wewease WPI to fwee poow */
#define NWP_SUPPWESS_WSP   0x00000010	/* Wemote NPowt suppowts suppwess wsp */
#define NWP_PWOGI_SND      0x00000020	/* sent PWOGI wequest fow this entwy */
#define NWP_PWWI_SND       0x00000040	/* sent PWWI wequest fow this entwy */
#define NWP_ADISC_SND      0x00000080	/* sent ADISC wequest fow this entwy */
#define NWP_WOGO_SND       0x00000100	/* sent WOGO wequest fow this entwy */
#define NWP_WNID_SND       0x00000400	/* sent WNID wequest fow this entwy */
#define NWP_EWS_SND_MASK   0x000007e0	/* sent EWS wequest fow this entwy */
#define NWP_NVMET_WECOV    0x00001000   /* NVMET auditing node fow wecovewy. */
#define NWP_UNWEG_INP      0x00008000	/* UNWEG_WPI cmd is in pwogwess */
#define NWP_DWOPPED        0x00010000	/* Init wef count has been dwopped */
#define NWP_DEWAY_TMO      0x00020000	/* deway timeout is wunning fow node */
#define NWP_NPW_2B_DISC    0x00040000	/* node is incwuded in num_disc_nodes */
#define NWP_WCV_PWOGI      0x00080000	/* Wcv'ed PWOGI fwom wemote system */
#define NWP_WOGO_ACC       0x00100000	/* Pwocess WOGO aftew ACC compwetes */
#define NWP_TGT_NO_SCSIID  0x00200000	/* good PWWI but no binding fow scsid */
#define NWP_ISSUE_WOGO     0x00400000	/* waiting to issue a WOGO */
#define NWP_IN_DEV_WOSS    0x00800000	/* devwoss in pwogwess */
#define NWP_ACC_WEGWOGIN   0x01000000	/* Issue Weg Wogin aftew successfuw
					   ACC */
#define NWP_NPW_ADISC      0x02000000	/* Issue ADISC when dq'ed fwom
					   NPW wist */
#define NWP_WM_DFWT_WPI    0x04000000	/* need to wemove weftovew dfwt WPI */
#define NWP_NODEV_WEMOVE   0x08000000	/* Defew wemovaw tiww discovewy ends */
#define NWP_TAWGET_WEMOVE  0x10000000   /* Tawget wemove in pwocess */
#define NWP_SC_WEQ         0x20000000	/* Tawget wequiwes authentication */
#define NWP_FIWSTBUWST     0x40000000	/* Tawget suppowts FiwstBuwst */
#define NWP_WPI_WEGISTEWED 0x80000000	/* nwp_wpi is vawid */

/* Thewe awe 4 diffewent doubwe winked wists nodewist entwies can weside on.
 * The Powt Wogin (PWOGI) wist and Addwess Discovewy (ADISC) wist awe used
 * when Wink Up discovewy ow Wegistewed State Change Notification (WSCN)
 * pwocessing is needed.  Each wist howds the nodes that wequiwe a PWOGI ow
 * ADISC Extended Wink Sewvice (EWS) wequest.  These wists keep twack of the
 * nodes affected by an WSCN, ow a Wink Up (Typicawwy, aww nodes awe effected
 * by Wink Up) event.  The unmapped_wist contains aww nodes that have
 * successfuwwy wogged into at the Fibwe Channew wevew.  The
 * mapped_wist wiww contain aww nodes that awe mapped FCP tawgets.
 *
 * The bind wist is a wist of undiscovewed (potentiawwy non-existent) nodes
 * that we have saved binding infowmation on. This infowmation is used when
 * nodes twansition fwom the unmapped to the mapped wist.
 */

/* Defines fow nwp_state */
#define NWP_STE_UNUSED_NODE       0x0	/* node is just awwocated */
#define NWP_STE_PWOGI_ISSUE       0x1	/* PWOGI was sent to NW_POWT */
#define NWP_STE_ADISC_ISSUE       0x2	/* ADISC was sent to NW_POWT */
#define NWP_STE_WEG_WOGIN_ISSUE   0x3	/* WEG_WOGIN was issued fow NW_POWT */
#define NWP_STE_PWWI_ISSUE        0x4	/* PWWI was sent to NW_POWT */
#define NWP_STE_WOGO_ISSUE	  0x5	/* WOGO was sent to NW_POWT */
#define NWP_STE_UNMAPPED_NODE     0x6	/* PWWI compweted fwom NW_POWT */
#define NWP_STE_MAPPED_NODE       0x7	/* Identified as a FCP Tawget */
#define NWP_STE_NPW_NODE          0x8	/* NPowt disappeawed */
#define NWP_STE_MAX_STATE         0x9
#define NWP_STE_FWEED_NODE        0xff	/* node entwy was fweed to MEM_NWP */

/* Fow UNUSED_NODE state, the node has just been awwocated.
 * Fow PWOGI_ISSUE and WEG_WOGIN_ISSUE, the node is on
 * the PWOGI wist. Fow WEG_WOGIN_COMPW, the node is taken off the PWOGI wist
 * and put on the unmapped wist. Fow ADISC pwocessing, the node is taken off
 * the ADISC wist and pwaced on eithew the mapped ow unmapped wist (depending
 * on its pwevious state). Once on the unmapped wist, a PWWI is issued and the
 * state changed to PWWI_ISSUE. When the PWWI compwetion occuws, the state is
 * changed to PWWI_COMPW. If the compwetion indicates a mapped
 * node, the node is taken off the unmapped wist. The binding wist is checked
 * fow a vawid binding, ow a binding is automaticawwy assigned. If binding
 * assignment is unsuccessfuw, the node is weft on the unmapped wist. If
 * binding assignment is successfuw, the associated binding wist entwy (if
 * any) is wemoved, and the node is pwaced on the mapped wist.
 */
/*
 * Fow a Wink Down, aww nodes on the ADISC, PWOGI, unmapped ow mapped
 * wists wiww weceive a DEVICE_WECOVEWY event. If the winkdown ow devwoss timews
 * expiwe, aww effected nodes wiww weceive a DEVICE_WM event.
 */
/*
 * Fow a Wink Up ow WSCN, aww nodes wiww move fwom the mapped / unmapped wists
 * to eithew the ADISC ow PWOGI wist.  Aftew a Namesewvew quewy ow AWPA woopmap
 * check, additionaw nodes may be added (DEVICE_ADD) ow wemoved (DEVICE_WM) to /
 * fwom the PWOGI ow ADISC wists. Once the PWOGI and ADISC wists awe popuwated,
 * we wiww fiwst pwocess the ADISC wist.  32 entwies awe pwocessed initiawwy and
 * ADISC is initited fow each one.  Compwetions / Events fow each node awe
 * funnewwed thwu the state machine.  As each node finishes ADISC pwocessing, it
 * stawts ADISC fow any nodes waiting fow ADISC pwocessing. If no nodes awe
 * waiting, and the ADISC wist count is identicawwy 0, then we awe done. Fow
 * Wink Up discovewy, since aww nodes on the PWOGI wist awe UNWEG_WOGIN'ed, we
 * can issue a CWEAW_WA and weenabwe Wink Events. Next we wiww pwocess the PWOGI
 * wist.  32 entwies awe pwocessed initiawwy and PWOGI is initited fow each one.
 * Compwetions / Events fow each node awe funnewwed thwu the state machine.  As
 * each node finishes PWOGI pwocessing, it stawts PWOGI fow any nodes waiting
 * fow PWOGI pwocessing. If no nodes awe waiting, and the PWOGI wist count is
 * identicawwy 0, then we awe done. We have now compweted discovewy / WSCN
 * handwing. Upon compwetion, AWW nodes shouwd be on eithew the mapped ow
 * unmapped wists.
 */

/* Defines fow Node Wist Entwy Events that couwd happen */
#define NWP_EVT_WCV_PWOGI         0x0	/* Wcv'd an EWS PWOGI command */
#define NWP_EVT_WCV_PWWI          0x1	/* Wcv'd an EWS PWWI  command */
#define NWP_EVT_WCV_WOGO          0x2	/* Wcv'd an EWS WOGO  command */
#define NWP_EVT_WCV_ADISC         0x3	/* Wcv'd an EWS ADISC command */
#define NWP_EVT_WCV_PDISC         0x4	/* Wcv'd an EWS PDISC command */
#define NWP_EVT_WCV_PWWO          0x5	/* Wcv'd an EWS PWWO  command */
#define NWP_EVT_CMPW_PWOGI        0x6	/* Sent an EWS PWOGI command */
#define NWP_EVT_CMPW_PWWI         0x7	/* Sent an EWS PWWI  command */
#define NWP_EVT_CMPW_WOGO         0x8	/* Sent an EWS WOGO  command */
#define NWP_EVT_CMPW_ADISC        0x9	/* Sent an EWS ADISC command */
#define NWP_EVT_CMPW_WEG_WOGIN    0xa	/* WEG_WOGIN mbox cmd compweted */
#define NWP_EVT_DEVICE_WM         0xb	/* Device not found in NS / AWPAmap */
#define NWP_EVT_DEVICE_WECOVEWY   0xc	/* Device existence unknown */
#define NWP_EVT_MAX_EVENT         0xd
#define NWP_EVT_NOTHING_PENDING   0xff
