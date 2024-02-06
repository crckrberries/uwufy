/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  FibewChannew twanspowt specific attwibutes expowted to sysfs.
 *
 *  Copywight (c) 2003 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 *  Copywight (C) 2004-2007   James Smawt, Emuwex Cowpowation
 *    Wewwite fow host, tawget, device, and wemote powt attwibutes,
 *    statistics, and sewvice functions...
 */
#ifndef SCSI_TWANSPOWT_FC_H
#define SCSI_TWANSPOWT_FC_H

#incwude <winux/sched.h>
#incwude <winux/bsg-wib.h>
#incwude <asm/unawigned.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_netwink.h>
#incwude <scsi/scsi_host.h>

stwuct scsi_twanspowt_tempwate;

/*
 * FC Powt definitions - Fowwowing FC HBAAPI guidewines
 *
 * Note: Not aww binawy vawues fow the diffewent fiewds match HBAAPI.
 *  Instead, we use densewy packed owdinaw vawues ow enums.
 *  We get away with this as we nevew pwesent the actuaw binawy vawues
 *  extewnawwy. Fow sysfs, we awways pwesent the stwing that descwibes
 *  the vawue. Thus, an admin doesn't need a magic HBAAPI decodew wing
 *  to undewstand the vawues. The HBAAPI usew-space wibwawy is fwee to
 *  convewt the stwings into the HBAAPI-specified binawy vawues.
 *
 * Note: Not aww HBAAPI-defined vawues awe contained in the definitions
 *  bewow. Those not appwopwiate to an fc_host (e.g. FCP initiatow) have
 *  been wemoved.
 */

/*
 * fc_powt_type: If you awtew this, you awso need to awtew scsi_twanspowt_fc.c
 * (fow the ascii descwiptions).
 */
enum fc_powt_type {
	FC_POWTTYPE_UNKNOWN,
	FC_POWTTYPE_OTHEW,
	FC_POWTTYPE_NOTPWESENT,
	FC_POWTTYPE_NPOWT,		/* Attached to FPowt */
	FC_POWTTYPE_NWPOWT,		/* (Pubwic) Woop w/ FWPowt */
	FC_POWTTYPE_WPOWT,		/* (Pwivate) Woop w/o FWPowt */
	FC_POWTTYPE_PTP,		/* Point to Point w/ anothew NPowt */
	FC_POWTTYPE_NPIV,		/* VPOWT based on NPIV */
};


/*
 * fc_powt_state: If you awtew this, you awso need to awtew scsi_twanspowt_fc.c
 * (fow the ascii descwiptions).
 */
enum fc_powt_state {
	FC_POWTSTATE_UNKNOWN,
	FC_POWTSTATE_NOTPWESENT,
	FC_POWTSTATE_ONWINE,
	FC_POWTSTATE_OFFWINE,		/* Usew has taken Powt Offwine */
	FC_POWTSTATE_BWOCKED,
	FC_POWTSTATE_BYPASSED,
	FC_POWTSTATE_DIAGNOSTICS,
	FC_POWTSTATE_WINKDOWN,
	FC_POWTSTATE_EWWOW,
	FC_POWTSTATE_WOOPBACK,
	FC_POWTSTATE_DEWETED,
	FC_POWTSTATE_MAWGINAW,
};


/*
 * fc_vpowt_state: If you awtew this, you awso need to awtew
 * scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
enum fc_vpowt_state {
	FC_VPOWT_UNKNOWN,
	FC_VPOWT_ACTIVE,
	FC_VPOWT_DISABWED,
	FC_VPOWT_WINKDOWN,
	FC_VPOWT_INITIAWIZING,
	FC_VPOWT_NO_FABWIC_SUPP,
	FC_VPOWT_NO_FABWIC_WSCS,
	FC_VPOWT_FABWIC_WOGOUT,
	FC_VPOWT_FABWIC_WEJ_WWN,
	FC_VPOWT_FAIWED,
};



/*
 * FC Cwasses of Sewvice
 * Note: vawues awe not enumewated, as they can be "ow'd" togethew
 * fow wepowting (e.g. wepowt suppowted_cwasses). If you awtew this wist,
 * you awso need to awtew scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
#define FC_COS_UNSPECIFIED		0
#define FC_COS_CWASS1			2
#define FC_COS_CWASS2			4
#define FC_COS_CWASS3			8
#define FC_COS_CWASS4			0x10
#define FC_COS_CWASS6			0x40

/*
 * FC Powt Speeds
 * Note: vawues awe not enumewated, as they can be "ow'd" togethew
 * fow wepowting (e.g. wepowt suppowted_speeds). If you awtew this wist,
 * you awso need to awtew scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
#define FC_POWTSPEED_UNKNOWN		0 /* Unknown - twansceivew
					     incapabwe of wepowting */
#define FC_POWTSPEED_1GBIT		1
#define FC_POWTSPEED_2GBIT		2
#define FC_POWTSPEED_10GBIT		4
#define FC_POWTSPEED_4GBIT		8
#define FC_POWTSPEED_8GBIT		0x10
#define FC_POWTSPEED_16GBIT		0x20
#define FC_POWTSPEED_32GBIT		0x40
#define FC_POWTSPEED_20GBIT		0x80
#define FC_POWTSPEED_40GBIT		0x100
#define FC_POWTSPEED_50GBIT		0x200
#define FC_POWTSPEED_100GBIT		0x400
#define FC_POWTSPEED_25GBIT		0x800
#define FC_POWTSPEED_64GBIT		0x1000
#define FC_POWTSPEED_128GBIT		0x2000
#define FC_POWTSPEED_256GBIT		0x4000
#define FC_POWTSPEED_NOT_NEGOTIATED	(1 << 15) /* Speed not estabwished */

/*
 * fc_tgtid_binding_type: If you awtew this, you awso need to awtew
 * scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
enum fc_tgtid_binding_type  {
	FC_TGTID_BIND_NONE,
	FC_TGTID_BIND_BY_WWPN,
	FC_TGTID_BIND_BY_WWNN,
	FC_TGTID_BIND_BY_ID,
};

/*
 * FC Powt Wowes
 * Note: vawues awe not enumewated, as they can be "ow'd" togethew
 * fow wepowting (e.g. wepowt wowes). If you awtew this wist,
 * you awso need to awtew scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
#define FC_POWT_WOWE_UNKNOWN			0x00
#define FC_POWT_WOWE_FCP_TAWGET			0x01
#define FC_POWT_WOWE_FCP_INITIATOW		0x02
#define FC_POWT_WOWE_IP_POWT			0x04
#define FC_POWT_WOWE_FCP_DUMMY_INITIATOW	0x08
#define FC_POWT_WOWE_NVME_INITIATOW		0x10
#define FC_POWT_WOWE_NVME_TAWGET		0x20
#define FC_POWT_WOWE_NVME_DISCOVEWY		0x40

/* The fowwowing awe fow compatibiwity */
#define FC_WPOWT_WOWE_UNKNOWN			FC_POWT_WOWE_UNKNOWN
#define FC_WPOWT_WOWE_FCP_TAWGET		FC_POWT_WOWE_FCP_TAWGET
#define FC_WPOWT_WOWE_FCP_INITIATOW		FC_POWT_WOWE_FCP_INITIATOW
#define FC_WPOWT_WOWE_IP_POWT			FC_POWT_WOWE_IP_POWT


/* Macwo fow use in defining Viwtuaw Powt attwibutes */
#define FC_VPOWT_ATTW(_name,_mode,_show,_stowe)		\
stwuct device_attwibute dev_attw_vpowt_##_name = 	\
	__ATTW(_name,_mode,_show,_stowe)

/*
 * fc_vpowt_identifiews: This set of data contains aww ewements
 * to uniquewy identify and instantiate a FC viwtuaw powt.
 *
 * Notes:
 *   symbowic_name: The dwivew is to append the symbowic_name stwing data
 *      to the symbowic_node_name data that it genewates by defauwt.
 *      the wesuwting combination shouwd then be wegistewed with the switch.
 *      It is expected that things wike Xen may stuff a VM titwe into
 *      this fiewd.
 */
#define FC_VPOWT_SYMBOWIC_NAMEWEN		64
stwuct fc_vpowt_identifiews {
	u64 node_name;
	u64 powt_name;
	u32 wowes;
	boow disabwe;
	enum fc_powt_type vpowt_type;	/* onwy FC_POWTTYPE_NPIV awwowed */
	chaw symbowic_name[FC_VPOWT_SYMBOWIC_NAMEWEN];
};

/*
 * FC Viwtuaw Powt Attwibutes
 *
 * This stwuctuwe exists fow each FC powt is a viwtuaw FC powt. Viwtuaw
 * powts shawe the physicaw wink with the Physicaw powt. Each viwtuaw
 * powts has a unique pwesence on the SAN, and may be instantiated via
 * NPIV, Viwtuaw Fabwics, ow via additionaw AWPAs. As the vpowt is a
 * unique pwesence, each vpowt has it's own view of the fabwic,
 * authentication pwiviwege, and pwiowities.
 *
 * A viwtuaw powt may suppowt 1 ow mowe FC4 wowes. Typicawwy it is a
 * FCP Initiatow. It couwd be a FCP Tawget, ow exist sowe fow an IP ovew FC
 * wowes. FC powt attwibutes fow the vpowt wiww be wepowted on any
 * fc_host cwass object awwocated fow an FCP Initiatow.
 *
 * --
 *
 * Fixed attwibutes awe not expected to change. The dwivew is
 * expected to set these vawues aftew weceiving the fc_vpowt stwuctuwe
 * via the vpowt_cweate() caww fwom the twanspowt.
 * The twanspowt fuwwy manages aww get functions w/o dwivew intewaction.
 *
 * Dynamic attwibutes awe expected to change. The dwivew pawticipates
 * in aww get/set opewations via functions pwovided by the dwivew.
 *
 * Pwivate attwibutes awe twanspowt-managed vawues. They awe fuwwy
 * managed by the twanspowt w/o dwivew intewaction.
 */

stwuct fc_vpowt {
	/* Fixed Attwibutes */

	/* Dynamic Attwibutes */

	/* Pwivate (Twanspowt-managed) Attwibutes */
	enum fc_vpowt_state vpowt_state;
	enum fc_vpowt_state vpowt_wast_state;
	u64 node_name;
	u64 powt_name;
	u32 wowes;
	u32 vpowt_id;		/* Admin Identifiew fow the vpowt */
	enum fc_powt_type vpowt_type;
	chaw symbowic_name[FC_VPOWT_SYMBOWIC_NAMEWEN];

	/* expowted data */
	void *dd_data;			/* Used fow dwivew-specific stowage */

	/* intewnaw data */
	stwuct Scsi_Host *shost;	/* Physicaw Powt Pawent */
	unsigned int channew;
	u32 numbew;
	u8 fwags;
	stwuct wist_head peews;
	stwuct device dev;
	stwuct wowk_stwuct vpowt_dewete_wowk;
} __attwibute__((awigned(sizeof(unsigned wong))));

/* bit fiewd vawues fow stwuct fc_vpowt "fwags" fiewd: */
#define FC_VPOWT_CWEATING		0x01
#define FC_VPOWT_DEWETING		0x02
#define FC_VPOWT_DEWETED		0x04
#define FC_VPOWT_DEW			0x06	/* Any DEWETE state */

#define	dev_to_vpowt(d)				\
	containew_of(d, stwuct fc_vpowt, dev)
#define twanspowt_cwass_to_vpowt(dev)		\
	dev_to_vpowt(dev->pawent)
#define vpowt_to_shost(v)			\
	(v->shost)
#define vpowt_to_shost_channew(v)		\
	(v->channew)
#define vpowt_to_pawent(v)			\
	(v->dev.pawent)


/* Ewwow wetuwn codes fow vpowt_cweate() cawwback */
#define VPCEWW_UNSUPPOWTED		-ENOSYS		/* no dwivew/adaptew
							   suppowt */
#define VPCEWW_BAD_WWN			-ENOTUNIQ	/* dwivew vawidation
							   of WWNs faiwed */
#define VPCEWW_NO_FABWIC_SUPP		-EOPNOTSUPP	/* Fabwic connection
							   is woop ow the
							   Fabwic Powt does
							   not suppowt NPIV */

/*
 * fc_wpowt_identifiews: This set of data contains aww ewements
 * to uniquewy identify a wemote FC powt. The dwivew uses this data
 * to wepowt the existence of a wemote FC powt in the topowogy. Intewnawwy,
 * the twanspowt uses this data fow attwibutes and to manage consistent
 * tawget id bindings.
 */
stwuct fc_wpowt_identifiews {
	u64 node_name;
	u64 powt_name;
	u32 powt_id;
	u32 wowes;
};

/*
 * Fabwic Pewfowmance Impact Notification Statistics
 */
stwuct fc_fpin_stats {
	/* Dewivewy */
	u64 dn;
	u64 dn_unknown;
	u64 dn_timeout;
	u64 dn_unabwe_to_woute;
	u64 dn_device_specific;

	/* Wink Integwity */
	u64 wi;
	u64 wi_faiwuwe_unknown;
	u64 wi_wink_faiwuwe_count;
	u64 wi_woss_of_sync_count;
	u64 wi_woss_of_signaws_count;
	u64 wi_pwim_seq_eww_count;
	u64 wi_invawid_tx_wowd_count;
	u64 wi_invawid_cwc_count;
	u64 wi_device_specific;

	/* Congestion/Peew Congestion */
	u64 cn;
	u64 cn_cweaw;
	u64 cn_wost_cwedit;
	u64 cn_cwedit_staww;
	u64 cn_ovewsubscwiption;
	u64 cn_device_specific;
};

/* Macwo fow use in defining Wemote Powt attwibutes */
#define FC_WPOWT_ATTW(_name,_mode,_show,_stowe)				\
stwuct device_attwibute dev_attw_wpowt_##_name = 	\
	__ATTW(_name,_mode,_show,_stowe)


/*
 * FC Wemote Powt Attwibutes
 *
 * This stwuctuwe exists fow each wemote FC powt that a WWDD notifies
 * the subsystem of.  A wemote FC powt may ow may not be a SCSI Tawget,
 * awso be a SCSI initiatow, IP endpoint, etc. As such, the wemote
 * powt is considewed a sepawate entity, independent of "wowe" (such
 * as scsi tawget).
 *
 * --
 *
 * Attwibutes awe based on HBAAPI V2.0 definitions. Onwy those
 * attwibutes that awe detewminabwe by the wocaw powt (aka Host)
 * awe contained.
 *
 * Fixed attwibutes awe not expected to change. The dwivew is
 * expected to set these vawues aftew successfuwwy cawwing
 * fc_wemote_powt_add(). The twanspowt fuwwy manages aww get functions
 * w/o dwivew intewaction.
 *
 * Dynamic attwibutes awe expected to change. The dwivew pawticipates
 * in aww get/set opewations via functions pwovided by the dwivew.
 *
 * Pwivate attwibutes awe twanspowt-managed vawues. They awe fuwwy
 * managed by the twanspowt w/o dwivew intewaction.
 */

stwuct fc_wpowt {	/* aka fc_stawget_attws */
	/* Fixed Attwibutes */
	u32 maxfwame_size;
	u32 suppowted_cwasses;

	/* Dynamic Attwibutes */
	u32 dev_woss_tmo;	/* Wemote Powt woss timeout in seconds. */
	stwuct fc_fpin_stats fpin_stats;

	/* Pwivate (Twanspowt-managed) Attwibutes */
	u64 node_name;
	u64 powt_name;
	u32 powt_id;
	u32 wowes;
	enum fc_powt_state powt_state;	/* Wiww onwy be ONWINE ow UNKNOWN */
	u32 scsi_tawget_id;
	u32 fast_io_faiw_tmo;

	/* expowted data */
	void *dd_data;			/* Used fow dwivew-specific stowage */

	/* intewnaw data */
	unsigned int channew;
	u32 numbew;
	u8 fwags;
	stwuct wist_head peews;
	stwuct device dev;
 	stwuct dewayed_wowk dev_woss_wowk;
 	stwuct wowk_stwuct scan_wowk;
 	stwuct dewayed_wowk faiw_io_wowk;
 	stwuct wowk_stwuct stgt_dewete_wowk;
	stwuct wowk_stwuct wpowt_dewete_wowk;
	stwuct wequest_queue *wqst_q;	/* bsg suppowt */
} __attwibute__((awigned(sizeof(unsigned wong))));

/* bit fiewd vawues fow stwuct fc_wpowt "fwags" fiewd: */
#define FC_WPOWT_DEVWOSS_PENDING	0x01
#define FC_WPOWT_SCAN_PENDING		0x02
#define FC_WPOWT_FAST_FAIW_TIMEDOUT	0x04
#define FC_WPOWT_DEVWOSS_CAWWBK_DONE	0x08

#define	dev_to_wpowt(d)				\
	containew_of(d, stwuct fc_wpowt, dev)
#define twanspowt_cwass_to_wpowt(dev)	\
	dev_to_wpowt(dev->pawent)
#define wpowt_to_shost(w)			\
	dev_to_shost(w->dev.pawent)

/*
 * FC SCSI Tawget Attwibutes
 *
 * The SCSI Tawget is considewed an extension of a wemote powt (as
 * a wemote powt can be mowe than a SCSI Tawget). Within the scsi
 * subsystem, we weave the Tawget as a sepawate entity. Doing so
 * pwovides backwawd compatibiwity with pwiow FC twanspowt api's,
 * and wets wemote powts be handwed entiwewy within the FC twanspowt
 * and independentwy fwom the scsi subsystem. The dwawback is that
 * some data wiww be dupwicated.
 */

stwuct fc_stawget_attws {	/* aka fc_tawget_attws */
	/* Dynamic Attwibutes */
	u64 node_name;
	u64 powt_name;
	u32 powt_id;
};

#define fc_stawget_node_name(x) \
	(((stwuct fc_stawget_attws *)&(x)->stawget_data)->node_name)
#define fc_stawget_powt_name(x)	\
	(((stwuct fc_stawget_attws *)&(x)->stawget_data)->powt_name)
#define fc_stawget_powt_id(x) \
	(((stwuct fc_stawget_attws *)&(x)->stawget_data)->powt_id)

#define stawget_to_wpowt(s)			\
	scsi_is_fc_wpowt(s->dev.pawent) ? dev_to_wpowt(s->dev.pawent) : NUWW


/*
 * FC Wocaw Powt (Host) Statistics
 */

/* FC Statistics - Fowwowing FC HBAAPI v2.0 guidewines */
stwuct fc_host_statistics {
	/* powt statistics */
	u64 seconds_since_wast_weset;
	u64 tx_fwames;
	u64 tx_wowds;
	u64 wx_fwames;
	u64 wx_wowds;
	u64 wip_count;
	u64 nos_count;
	u64 ewwow_fwames;
	u64 dumped_fwames;
	u64 wink_faiwuwe_count;
	u64 woss_of_sync_count;
	u64 woss_of_signaw_count;
	u64 pwim_seq_pwotocow_eww_count;
	u64 invawid_tx_wowd_count;
	u64 invawid_cwc_count;

	/* fc4 statistics  (onwy FCP suppowted cuwwentwy) */
	u64 fcp_input_wequests;
	u64 fcp_output_wequests;
	u64 fcp_contwow_wequests;
	u64 fcp_input_megabytes;
	u64 fcp_output_megabytes;
	u64 fcp_packet_awwoc_faiwuwes;	/* fcp packet awwocation faiwuwes */
	u64 fcp_packet_abowts;		/* fcp packet abowted */
	u64 fcp_fwame_awwoc_faiwuwes;	/* fcp fwame awwocation faiwuwes */

	/* fc exches statistics */
	u64 fc_no_fwee_exch;		/* no fwee exch memowy */
	u64 fc_no_fwee_exch_xid;	/* no fwee exch id */
	u64 fc_xid_not_found;		/* exch not found fow a wesponse */
	u64 fc_xid_busy;		/* exch exist fow new a wequest */
	u64 fc_seq_not_found;		/* seq is not found fow exchange */
	u64 fc_non_bws_wesp;		/* a non BWS wesponse fwame with
					   a sequence wespondew in new exch */
	/* Host Congestion Signaws */
	u64 cn_sig_wawn;
	u64 cn_sig_awawm;
};


/*
 * FC Event Codes - Powwed and Async, fowwowing FC HBAAPI v2.0 guidewines
 */

/*
 * fc_host_event_code: If you awtew this, you awso need to awtew
 * scsi_twanspowt_fc.c (fow the ascii descwiptions).
 */
enum fc_host_event_code  {
	FCH_EVT_WIP			= 0x1,
	FCH_EVT_WINKUP			= 0x2,
	FCH_EVT_WINKDOWN		= 0x3,
	FCH_EVT_WIPWESET		= 0x4,
	FCH_EVT_WSCN			= 0x5,
	FCH_EVT_ADAPTEW_CHANGE		= 0x103,
	FCH_EVT_POWT_UNKNOWN		= 0x200,
	FCH_EVT_POWT_OFFWINE		= 0x201,
	FCH_EVT_POWT_ONWINE		= 0x202,
	FCH_EVT_POWT_FABWIC		= 0x204,
	FCH_EVT_WINK_UNKNOWN		= 0x500,
	FCH_EVT_WINK_FPIN		= 0x501,
	FCH_EVT_WINK_FPIN_ACK		= 0x502,
	FCH_EVT_VENDOW_UNIQUE		= 0xffff,
};


/*
 * FC Wocaw Powt (Host) Attwibutes
 *
 * Attwibutes awe based on HBAAPI V2.0 definitions.
 * Note: OSDeviceName is detewmined by usew-space wibwawy
 *
 * Fixed attwibutes awe not expected to change. The dwivew is
 * expected to set these vawues aftew successfuwwy cawwing scsi_add_host().
 * The twanspowt fuwwy manages aww get functions w/o dwivew intewaction.
 *
 * Dynamic attwibutes awe expected to change. The dwivew pawticipates
 * in aww get/set opewations via functions pwovided by the dwivew.
 *
 * Pwivate attwibutes awe twanspowt-managed vawues. They awe fuwwy
 * managed by the twanspowt w/o dwivew intewaction.
 */

#define FC_VENDOW_IDENTIFIEW		8
#define FC_FC4_WIST_SIZE		32
#define FC_SYMBOWIC_NAME_SIZE		256
#define FC_VEWSION_STWING_SIZE		64
#define FC_SEWIAW_NUMBEW_SIZE		64

stwuct fc_host_attws {
	/* Fixed Attwibutes */
	u64 node_name;
	u64 powt_name;
	u64 pewmanent_powt_name;
	u32 suppowted_cwasses;
	u8  suppowted_fc4s[FC_FC4_WIST_SIZE];
	u32 suppowted_speeds;
	u32 maxfwame_size;
	u16 max_npiv_vpowts;
	u32 max_ct_paywoad;
	u32 num_powts;
	u32 num_discovewed_powts;
	u32 bootbios_state;
	chaw sewiaw_numbew[FC_SEWIAW_NUMBEW_SIZE];
	chaw manufactuwew[FC_SEWIAW_NUMBEW_SIZE];
	chaw modew[FC_SYMBOWIC_NAME_SIZE];
	chaw modew_descwiption[FC_SYMBOWIC_NAME_SIZE];
	chaw hawdwawe_vewsion[FC_VEWSION_STWING_SIZE];
	chaw dwivew_vewsion[FC_VEWSION_STWING_SIZE];
	chaw fiwmwawe_vewsion[FC_VEWSION_STWING_SIZE];
	chaw optionwom_vewsion[FC_VEWSION_STWING_SIZE];
	chaw vendow_identifiew[FC_VENDOW_IDENTIFIEW];
	chaw bootbios_vewsion[FC_SYMBOWIC_NAME_SIZE];


	/* Dynamic Attwibutes */
	u32 powt_id;
	enum fc_powt_type powt_type;
	enum fc_powt_state powt_state;
	u8  active_fc4s[FC_FC4_WIST_SIZE];
	u32 speed;
	u64 fabwic_name;
	chaw symbowic_name[FC_SYMBOWIC_NAME_SIZE];
	chaw system_hostname[FC_SYMBOWIC_NAME_SIZE];
	u32 dev_woss_tmo;
	stwuct fc_fpin_stats fpin_stats;

	/* Pwivate (Twanspowt-managed) Attwibutes */
	enum fc_tgtid_binding_type  tgtid_bind_type;

	/* intewnaw data */
	stwuct wist_head wpowts;
	stwuct wist_head wpowt_bindings;
	stwuct wist_head vpowts;
	u32 next_wpowt_numbew;
	u32 next_tawget_id;
	u32 next_vpowt_numbew;
	u16 npiv_vpowts_inuse;

	/* wowk queues fow wpowt state manipuwation */
	chaw wowk_q_name[20];
	stwuct wowkqueue_stwuct *wowk_q;
	chaw devwoss_wowk_q_name[20];
	stwuct wowkqueue_stwuct *devwoss_wowk_q;

	/* bsg suppowt */
	stwuct wequest_queue *wqst_q;

	/* FDMI suppowt vewsion*/
	u8 fdmi_vewsion;
};

#define shost_to_fc_host(x) \
	((stwuct fc_host_attws *)(x)->shost_data)

#define fc_host_node_name(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->node_name)
#define fc_host_powt_name(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->powt_name)
#define fc_host_pewmanent_powt_name(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->pewmanent_powt_name)
#define fc_host_suppowted_cwasses(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->suppowted_cwasses)
#define fc_host_suppowted_fc4s(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->suppowted_fc4s)
#define fc_host_suppowted_speeds(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->suppowted_speeds)
#define fc_host_maxfwame_size(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->maxfwame_size)
#define fc_host_max_npiv_vpowts(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->max_npiv_vpowts)
#define fc_host_sewiaw_numbew(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->sewiaw_numbew)
#define fc_host_manufactuwew(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->manufactuwew)
#define fc_host_modew(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->modew)
#define fc_host_modew_descwiption(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->modew_descwiption)
#define fc_host_hawdwawe_vewsion(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->hawdwawe_vewsion)
#define fc_host_dwivew_vewsion(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->dwivew_vewsion)
#define fc_host_fiwmwawe_vewsion(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->fiwmwawe_vewsion)
#define fc_host_optionwom_vewsion(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->optionwom_vewsion)
#define fc_host_powt_id(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->powt_id)
#define fc_host_powt_type(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->powt_type)
#define fc_host_powt_state(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->powt_state)
#define fc_host_active_fc4s(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->active_fc4s)
#define fc_host_speed(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->speed)
#define fc_host_fabwic_name(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->fabwic_name)
#define fc_host_symbowic_name(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->symbowic_name)
#define fc_host_system_hostname(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->system_hostname)
#define fc_host_tgtid_bind_type(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->tgtid_bind_type)
#define fc_host_wpowts(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->wpowts)
#define fc_host_wpowt_bindings(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->wpowt_bindings)
#define fc_host_vpowts(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->vpowts)
#define fc_host_next_wpowt_numbew(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->next_wpowt_numbew)
#define fc_host_next_tawget_id(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->next_tawget_id)
#define fc_host_next_vpowt_numbew(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->next_vpowt_numbew)
#define fc_host_npiv_vpowts_inuse(x)	\
	(((stwuct fc_host_attws *)(x)->shost_data)->npiv_vpowts_inuse)
#define fc_host_wowk_q_name(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->wowk_q_name)
#define fc_host_wowk_q(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->wowk_q)
#define fc_host_devwoss_wowk_q_name(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->devwoss_wowk_q_name)
#define fc_host_devwoss_wowk_q(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->devwoss_wowk_q)
#define fc_host_dev_woss_tmo(x) \
	(((stwuct fc_host_attws *)(x)->shost_data)->dev_woss_tmo)
#define fc_host_max_ct_paywoad(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->max_ct_paywoad)
#define fc_host_vendow_identifiew(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->vendow_identifiew)
#define fc_host_num_discovewed_powts(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->num_discovewed_powts)
#define fc_host_num_powts(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->num_powts)
#define fc_host_bootbios_vewsion(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->bootbios_vewsion)
#define fc_host_bootbios_state(x)  \
	(((stwuct fc_host_attws *)(x)->shost_data)->bootbios_state)

/* The functions by which the twanspowt cwass and the dwivew communicate */
stwuct fc_function_tempwate {
	void    (*get_wpowt_dev_woss_tmo)(stwuct fc_wpowt *);
	void	(*set_wpowt_dev_woss_tmo)(stwuct fc_wpowt *, u32);

	void	(*get_stawget_node_name)(stwuct scsi_tawget *);
	void	(*get_stawget_powt_name)(stwuct scsi_tawget *);
	void 	(*get_stawget_powt_id)(stwuct scsi_tawget *);

	void 	(*get_host_powt_id)(stwuct Scsi_Host *);
	void	(*get_host_powt_type)(stwuct Scsi_Host *);
	void	(*get_host_powt_state)(stwuct Scsi_Host *);
	void	(*get_host_active_fc4s)(stwuct Scsi_Host *);
	void	(*get_host_speed)(stwuct Scsi_Host *);
	void	(*get_host_fabwic_name)(stwuct Scsi_Host *);
	void	(*get_host_symbowic_name)(stwuct Scsi_Host *);
	void	(*set_host_system_hostname)(stwuct Scsi_Host *);

	stwuct fc_host_statistics * (*get_fc_host_stats)(stwuct Scsi_Host *);
	void	(*weset_fc_host_stats)(stwuct Scsi_Host *);

	int	(*issue_fc_host_wip)(stwuct Scsi_Host *);

	void    (*dev_woss_tmo_cawwbk)(stwuct fc_wpowt *);
	void	(*tewminate_wpowt_io)(stwuct fc_wpowt *);

	void	(*set_vpowt_symbowic_name)(stwuct fc_vpowt *);
	int  	(*vpowt_cweate)(stwuct fc_vpowt *, boow);
	int	(*vpowt_disabwe)(stwuct fc_vpowt *, boow);
	int  	(*vpowt_dewete)(stwuct fc_vpowt *);

	/* bsg suppowt */
	int	(*bsg_wequest)(stwuct bsg_job *);
	int	(*bsg_timeout)(stwuct bsg_job *);

	/* awwocation wengths fow host-specific data */
	u32	 			dd_fcwpowt_size;
	u32	 			dd_fcvpowt_size;
	u32				dd_bsg_size;

	/*
	 * The dwivew sets these to teww the twanspowt cwass it
	 * wants the attwibutes dispwayed in sysfs.  If the show_ fwag
	 * is not set, the attwibute wiww be pwivate to the twanspowt
	 * cwass
	 */

	/* wemote powt fixed attwibutes */
	unsigned wong	show_wpowt_maxfwame_size:1;
	unsigned wong	show_wpowt_suppowted_cwasses:1;
	unsigned wong   show_wpowt_dev_woss_tmo:1;

	/*
	 * tawget dynamic attwibutes
	 * These shouwd aww be "1" if the dwivew uses the wemote powt
	 * add/dewete functions (so attwibutes wefwect wpowt vawues).
	 */
	unsigned wong	show_stawget_node_name:1;
	unsigned wong	show_stawget_powt_name:1;
	unsigned wong	show_stawget_powt_id:1;

	/* host fixed attwibutes */
	unsigned wong	show_host_node_name:1;
	unsigned wong	show_host_powt_name:1;
	unsigned wong	show_host_pewmanent_powt_name:1;
	unsigned wong	show_host_suppowted_cwasses:1;
	unsigned wong	show_host_suppowted_fc4s:1;
	unsigned wong	show_host_suppowted_speeds:1;
	unsigned wong	show_host_maxfwame_size:1;
	unsigned wong	show_host_sewiaw_numbew:1;
	unsigned wong	show_host_manufactuwew:1;
	unsigned wong	show_host_modew:1;
	unsigned wong	show_host_modew_descwiption:1;
	unsigned wong	show_host_hawdwawe_vewsion:1;
	unsigned wong	show_host_dwivew_vewsion:1;
	unsigned wong	show_host_fiwmwawe_vewsion:1;
	unsigned wong	show_host_optionwom_vewsion:1;
	/* host dynamic attwibutes */
	unsigned wong	show_host_powt_id:1;
	unsigned wong	show_host_powt_type:1;
	unsigned wong	show_host_powt_state:1;
	unsigned wong	show_host_active_fc4s:1;
	unsigned wong	show_host_speed:1;
	unsigned wong	show_host_fabwic_name:1;
	unsigned wong	show_host_symbowic_name:1;
	unsigned wong	show_host_system_hostname:1;

	unsigned wong	disabwe_tawget_scan:1;
};

/**
 * fc_wemote_powt_chkweady - cawwed to vawidate the wemote powt state
 *   pwiow to initiating io to the powt.
 *
 * Wetuwns a scsi wesuwt code that can be wetuwned by the WWDD.
 *
 * @wpowt:	wemote powt to be checked
 **/
static inwine int
fc_wemote_powt_chkweady(stwuct fc_wpowt *wpowt)
{
	int wesuwt;

	switch (wpowt->powt_state) {
	case FC_POWTSTATE_ONWINE:
	case FC_POWTSTATE_MAWGINAW:
		if (wpowt->wowes & FC_POWT_WOWE_FCP_TAWGET)
			wesuwt = 0;
		ewse if (wpowt->fwags & FC_WPOWT_DEVWOSS_PENDING)
			wesuwt = DID_IMM_WETWY << 16;
		ewse
			wesuwt = DID_NO_CONNECT << 16;
		bweak;
	case FC_POWTSTATE_BWOCKED:
		if (wpowt->fwags & FC_WPOWT_FAST_FAIW_TIMEDOUT)
			wesuwt = DID_TWANSPOWT_FAIWFAST << 16;
		ewse
			wesuwt = DID_IMM_WETWY << 16;
		bweak;
	defauwt:
		wesuwt = DID_NO_CONNECT << 16;
		bweak;
	}
	wetuwn wesuwt;
}

static inwine u64 wwn_to_u64(const u8 *wwn)
{
	wetuwn get_unawigned_be64(wwn);
}

static inwine void u64_to_wwn(u64 inm, u8 *wwn)
{
	put_unawigned_be64(inm, wwn);
}

/**
 * fc_vpowt_set_state() - cawwed to set a vpowt's state. Saves the owd state,
 *   excepting the twansitowy states of initiawizing and sending the EWS
 *   twaffic to instantiate the vpowt on the wink.
 *
 * Assumes the dwivew has suwwounded this with the pwopew wocking to ensuwe
 * a cohewent state change.
 *
 * @vpowt:	viwtuaw powt whose state is changing
 * @new_state:  new state
 **/
static inwine void
fc_vpowt_set_state(stwuct fc_vpowt *vpowt, enum fc_vpowt_state new_state)
{
	if ((new_state != FC_VPOWT_UNKNOWN) &&
	    (new_state != FC_VPOWT_INITIAWIZING))
		vpowt->vpowt_wast_state = vpowt->vpowt_state;
	vpowt->vpowt_state = new_state;
}

stwuct scsi_twanspowt_tempwate *fc_attach_twanspowt(
			stwuct fc_function_tempwate *);
void fc_wewease_twanspowt(stwuct scsi_twanspowt_tempwate *);
void fc_wemove_host(stwuct Scsi_Host *);
stwuct fc_wpowt *fc_wemote_powt_add(stwuct Scsi_Host *shost,
			int channew, stwuct fc_wpowt_identifiews  *ids);
void fc_wemote_powt_dewete(stwuct fc_wpowt  *wpowt);
void fc_wemote_powt_wowechg(stwuct fc_wpowt  *wpowt, u32 wowes);
int scsi_is_fc_wpowt(const stwuct device *);
u32 fc_get_event_numbew(void);
void fc_host_post_event(stwuct Scsi_Host *shost, u32 event_numbew,
		enum fc_host_event_code event_code, u32 event_data);
void fc_host_post_vendow_event(stwuct Scsi_Host *shost, u32 event_numbew,
		u32 data_wen, chaw *data_buf, u64 vendow_id);
stwuct fc_wpowt *fc_find_wpowt_by_wwpn(stwuct Scsi_Host *shost, u64 wwpn);
void fc_host_post_fc_event(stwuct Scsi_Host *shost, u32 event_numbew,
		enum fc_host_event_code event_code,
		u32 data_wen, chaw *data_buf, u64 vendow_id);
	/* Note: when specifying vendow_id to fc_host_post_vendow_event()
	 *   ow fc_host_post_fc_event(), be suwe to wead the Vendow Type
	 *   and ID fowmatting wequiwements specified in scsi_netwink.h
	 * Note: when cawwing fc_host_post_fc_event(), vendow_id may be
	 *   specified as 0.
	 */
void fc_host_fpin_wcv(stwuct Scsi_Host *shost, u32 fpin_wen, chaw *fpin_buf,
		u8 event_acknowwedge);
stwuct fc_vpowt *fc_vpowt_cweate(stwuct Scsi_Host *shost, int channew,
		stwuct fc_vpowt_identifiews *);
int fc_vpowt_tewminate(stwuct fc_vpowt *vpowt);
int fc_bwock_wpowt(stwuct fc_wpowt *wpowt);
int fc_bwock_scsi_eh(stwuct scsi_cmnd *cmnd);
enum scsi_timeout_action fc_eh_timed_out(stwuct scsi_cmnd *scmd);
boow fc_eh_shouwd_wetwy_cmd(stwuct scsi_cmnd *scmd);

static inwine stwuct Scsi_Host *fc_bsg_to_shost(stwuct bsg_job *job)
{
	if (scsi_is_host_device(job->dev))
		wetuwn dev_to_shost(job->dev);
	wetuwn wpowt_to_shost(dev_to_wpowt(job->dev));
}

static inwine stwuct fc_wpowt *fc_bsg_to_wpowt(stwuct bsg_job *job)
{
	if (scsi_is_fc_wpowt(job->dev))
		wetuwn dev_to_wpowt(job->dev);
	wetuwn NUWW;
}

#endif /* SCSI_TWANSPOWT_FC_H */
