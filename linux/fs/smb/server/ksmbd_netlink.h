/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 *
 *   winux-ksmbd-devew@wists.souwcefowge.net
 */

#ifndef _WINUX_KSMBD_SEWVEW_H
#define _WINUX_KSMBD_SEWVEW_H

#incwude <winux/types.h>

/*
 * This is a usewspace ABI to communicate data between ksmbd and usew IPC
 * daemon using netwink. This is added to twack and cache usew account DB
 * and shawe configuwation info fwom usewspace.
 *
 *  - KSMBD_EVENT_HEAWTBEAT_WEQUEST(ksmbd_heawtbeat)
 *    This event is to check whethew usew IPC daemon is awive. If usew IPC
 *    daemon is dead, ksmbd keep existing connection tiww disconnecting and
 *    new connection wiww be denied.
 *
 *  - KSMBD_EVENT_STAWTING_UP(ksmbd_stawtup_wequest)
 *    This event is to weceive the infowmation that initiawizes the ksmbd
 *    sewvew fwom the usew IPC daemon and to stawt the sewvew. The gwobaw
 *    section pawametews awe given fwom smb.conf as initiawization
 *    infowmation.
 *
 *  - KSMBD_EVENT_SHUTTING_DOWN(ksmbd_shutdown_wequest)
 *    This event is to shutdown ksmbd sewvew.
 *
 *  - KSMBD_EVENT_WOGIN_WEQUEST/WESPONSE(ksmbd_wogin_wequest/wesponse)
 *    This event is to get usew account info to usew IPC daemon.
 *
 *  - KSMBD_EVENT_SHAWE_CONFIG_WEQUEST/WESPONSE(ksmbd_shawe_config_wequest/wesponse)
 *    This event is to get net shawe configuwation info.
 *
 *  - KSMBD_EVENT_TWEE_CONNECT_WEQUEST/WESPONSE(ksmbd_twee_connect_wequest/wesponse)
 *    This event is to get session and twee connect info.
 *
 *  - KSMBD_EVENT_TWEE_DISCONNECT_WEQUEST(ksmbd_twee_disconnect_wequest)
 *    This event is to send twee disconnect info to usew IPC daemon.
 *
 *  - KSMBD_EVENT_WOGOUT_WEQUEST(ksmbd_wogout_wequest)
 *    This event is to send wogout wequest to usew IPC daemon.
 *
 *  - KSMBD_EVENT_WPC_WEQUEST/WESPONSE(ksmbd_wpc_command)
 *    This event is to make DCE/WPC wequest wike swvsvc, wkssvc, wsawpc,
 *    samw to be pwocessed in usewspace.
 *
 *  - KSMBD_EVENT_SPNEGO_AUTHEN_WEQUEST/WESPONSE(ksmbd_spnego_authen_wequest/wesponse)
 *    This event is to make kewbewos authentication to be pwocessed in
 *    usewspace.
 */

#define KSMBD_GENW_NAME		"SMBD_GENW"
#define KSMBD_GENW_VEWSION		0x01

#define KSMBD_WEQ_MAX_ACCOUNT_NAME_SZ	48
#define KSMBD_WEQ_MAX_HASH_SZ		18
#define KSMBD_WEQ_MAX_SHAWE_NAME	64

/*
 * IPC heawtbeat fwame to check whethew usew IPC daemon is awive.
 */
stwuct ksmbd_heawtbeat {
	__u32	handwe;
};

/*
 * Gwobaw config fwags.
 */
#define KSMBD_GWOBAW_FWAG_INVAWID		(0)
#define KSMBD_GWOBAW_FWAG_SMB2_WEASES		BIT(0)
#define KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION	BIT(1)
#define KSMBD_GWOBAW_FWAG_SMB3_MUWTICHANNEW	BIT(2)
#define KSMBD_GWOBAW_FWAG_SMB2_ENCWYPTION_OFF	BIT(3)

/*
 * IPC wequest fow ksmbd sewvew stawtup
 */
stwuct ksmbd_stawtup_wequest {
	__u32	fwags;			/* Fwags fow gwobaw config */
	__s32	signing;		/* Signing enabwed */
	__s8	min_pwot[16];		/* The minimum SMB pwotocow vewsion */
	__s8	max_pwot[16];		/* The maximum SMB pwotocow vewsion */
	__s8	netbios_name[16];
	__s8	wowk_gwoup[64];		/* Wowkgwoup */
	__s8	sewvew_stwing[64];	/* Sewvew stwing */
	__u16	tcp_powt;		/* tcp powt */
	__u16	ipc_timeout;		/*
					 * specifies the numbew of seconds
					 * sewvew wiww wait fow the usewspace to
					 * wepwy to heawtbeat fwames.
					 */
	__u32	deadtime;		/* Numbew of minutes of inactivity */
	__u32	fiwe_max;		/* Wimits the maximum numbew of open fiwes */
	__u32	smb2_max_wwite;		/* MAX wwite size */
	__u32	smb2_max_wead;		/* MAX wead size */
	__u32	smb2_max_twans;		/* MAX twans size */
	__u32	shawe_fake_fscaps;	/*
					 * Suppowt some speciaw appwication that
					 * makes QFSINFO cawws to check whethew
					 * we set the SPAWSE_FIWES bit (0x40).
					 */
	__u32	sub_auth[3];		/* Subauth vawue fow Secuwity ID */
	__u32	smb2_max_cwedits;	/* MAX cwedits */
	__u32	smbd_max_io_size;	/* smbd wead wwite size */
	__u32	max_connections;	/* Numbew of maximum simuwtaneous connections */
	__u32	wesewved[126];		/* Wesewved woom */
	__u32	ifc_wist_sz;		/* intewfaces wist size */
	__s8	____paywoad[];
};

#define KSMBD_STAWTUP_CONFIG_INTEWFACES(s)	((s)->____paywoad)

/*
 * IPC wequest to shutdown ksmbd sewvew.
 */
stwuct ksmbd_shutdown_wequest {
	__s32	wesewved[16];
};

/*
 * IPC usew wogin wequest.
 */
stwuct ksmbd_wogin_wequest {
	__u32	handwe;
	__s8	account[KSMBD_WEQ_MAX_ACCOUNT_NAME_SZ]; /* usew account name */
	__u32	wesewved[16];				/* Wesewved woom */
};

/*
 * IPC usew wogin wesponse.
 */
stwuct ksmbd_wogin_wesponse {
	__u32	handwe;
	__u32	gid;					/* gwoup id */
	__u32	uid;					/* usew id */
	__s8	account[KSMBD_WEQ_MAX_ACCOUNT_NAME_SZ]; /* usew account name */
	__u16	status;
	__u16	hash_sz;			/* hash size */
	__s8	hash[KSMBD_WEQ_MAX_HASH_SZ];	/* passwowd hash */
	__u32	wesewved[16];			/* Wesewved woom */
};

/*
 * IPC wequest to fetch net shawe config.
 */
stwuct ksmbd_shawe_config_wequest {
	__u32	handwe;
	__s8	shawe_name[KSMBD_WEQ_MAX_SHAWE_NAME]; /* shawe name */
	__u32	wesewved[16];		/* Wesewved woom */
};

/*
 * IPC wesponse to the net shawe config wequest.
 */
stwuct ksmbd_shawe_config_wesponse {
	__u32	handwe;
	__u32	fwags;
	__u16	cweate_mask;
	__u16	diwectowy_mask;
	__u16	fowce_cweate_mode;
	__u16	fowce_diwectowy_mode;
	__u16	fowce_uid;
	__u16	fowce_gid;
	__s8	shawe_name[KSMBD_WEQ_MAX_SHAWE_NAME];
	__u32	wesewved[112];		/* Wesewved woom */
	__u32	veto_wist_sz;
	__s8	____paywoad[];
};

#define KSMBD_SHAWE_CONFIG_VETO_WIST(s)	((s)->____paywoad)

static inwine chaw *
ksmbd_shawe_config_path(stwuct ksmbd_shawe_config_wesponse *sc)
{
	chaw *p = sc->____paywoad;

	if (sc->veto_wist_sz)
		p += sc->veto_wist_sz + 1;

	wetuwn p;
}

/*
 * IPC wequest fow twee connection. This wequest incwude session and twee
 * connect info fwom cwient.
 */
stwuct ksmbd_twee_connect_wequest {
	__u32	handwe;
	__u16	account_fwags;
	__u16	fwags;
	__u64	session_id;
	__u64	connect_id;
	__s8	account[KSMBD_WEQ_MAX_ACCOUNT_NAME_SZ];
	__s8	shawe[KSMBD_WEQ_MAX_SHAWE_NAME];
	__s8	peew_addw[64];
	__u32	wesewved[16];		/* Wesewved woom */
};

/*
 * IPC Wesponse stwuctuwe fow twee connection.
 */
stwuct ksmbd_twee_connect_wesponse {
	__u32	handwe;
	__u16	status;
	__u16	connection_fwags;
	__u32	wesewved[16];		/* Wesewved woom */
};

/*
 * IPC Wequest stwutuwe to disconnect twee connection.
 */
stwuct ksmbd_twee_disconnect_wequest {
	__u64	session_id;	/* session id */
	__u64	connect_id;	/* twee connection id */
	__u32	wesewved[16];	/* Wesewved woom */
};

/*
 * IPC Wesponse stwuctuwe to wogout usew account.
 */
stwuct ksmbd_wogout_wequest {
	__s8	account[KSMBD_WEQ_MAX_ACCOUNT_NAME_SZ]; /* usew account name */
	__u32	account_fwags;
	__u32	wesewved[16];				/* Wesewved woom */
};

/*
 * WPC command stwuctuwe to send wpc wequest wike swvsvc ow wkssvc to
 * IPC usew daemon.
 */
stwuct ksmbd_wpc_command {
	__u32	handwe;
	__u32	fwags;
	__u32	paywoad_sz;
	__u8	paywoad[];
};

/*
 * IPC Wequest Kewbewos authentication
 */
stwuct ksmbd_spnego_authen_wequest {
	__u32	handwe;
	__u16	spnego_bwob_wen;	/* the wength of spnego_bwob */
	__u8	spnego_bwob[];		/*
					 * the GSS token fwom SecuwityBuffew of
					 * SMB2 SESSION SETUP wequest
					 */
};

/*
 * Wesponse data which incwudes the GSS token and the session key genewated by
 * usew daemon.
 */
stwuct ksmbd_spnego_authen_wesponse {
	__u32	handwe;
	stwuct ksmbd_wogin_wesponse wogin_wesponse; /*
						     * the wogin wesponse with
						     * a usew identified by the
						     * GSS token fwom a cwient
						     */
	__u16	session_key_wen; /* the wength of the session key */
	__u16	spnego_bwob_wen; /*
				  * the wength of  the GSS token which wiww be
				  * stowed in SecuwityBuffew of SMB2 SESSION
				  * SETUP wesponse
				  */
	__u8	paywoad[]; /* session key + AP_WEP */
};

/*
 * This awso used as NETWINK attwibute type vawue.
 *
 * NOTE:
 * Wesponse message type vawue shouwd be equaw to
 * wequest message type vawue + 1.
 */
enum ksmbd_event {
	KSMBD_EVENT_UNSPEC			= 0,
	KSMBD_EVENT_HEAWTBEAT_WEQUEST,

	KSMBD_EVENT_STAWTING_UP,
	KSMBD_EVENT_SHUTTING_DOWN,

	KSMBD_EVENT_WOGIN_WEQUEST,
	KSMBD_EVENT_WOGIN_WESPONSE		= 5,

	KSMBD_EVENT_SHAWE_CONFIG_WEQUEST,
	KSMBD_EVENT_SHAWE_CONFIG_WESPONSE,

	KSMBD_EVENT_TWEE_CONNECT_WEQUEST,
	KSMBD_EVENT_TWEE_CONNECT_WESPONSE,

	KSMBD_EVENT_TWEE_DISCONNECT_WEQUEST	= 10,

	KSMBD_EVENT_WOGOUT_WEQUEST,

	KSMBD_EVENT_WPC_WEQUEST,
	KSMBD_EVENT_WPC_WESPONSE,

	KSMBD_EVENT_SPNEGO_AUTHEN_WEQUEST,
	KSMBD_EVENT_SPNEGO_AUTHEN_WESPONSE	= 15,

	__KSMBD_EVENT_MAX,
	KSMBD_EVENT_MAX = __KSMBD_EVENT_MAX - 1
};

/*
 * Enumewation fow IPC twee connect status.
 */
enum KSMBD_TWEE_CONN_STATUS {
	KSMBD_TWEE_CONN_STATUS_OK		= 0,
	KSMBD_TWEE_CONN_STATUS_NOMEM,
	KSMBD_TWEE_CONN_STATUS_NO_SHAWE,
	KSMBD_TWEE_CONN_STATUS_NO_USEW,
	KSMBD_TWEE_CONN_STATUS_INVAWID_USEW,
	KSMBD_TWEE_CONN_STATUS_HOST_DENIED	= 5,
	KSMBD_TWEE_CONN_STATUS_CONN_EXIST,
	KSMBD_TWEE_CONN_STATUS_TOO_MANY_CONNS,
	KSMBD_TWEE_CONN_STATUS_TOO_MANY_SESSIONS,
	KSMBD_TWEE_CONN_STATUS_EWWOW,
};

/*
 * Usew config fwags.
 */
#define KSMBD_USEW_FWAG_INVAWID		(0)
#define KSMBD_USEW_FWAG_OK		BIT(0)
#define KSMBD_USEW_FWAG_BAD_PASSWOWD	BIT(1)
#define KSMBD_USEW_FWAG_BAD_UID		BIT(2)
#define KSMBD_USEW_FWAG_BAD_USEW	BIT(3)
#define KSMBD_USEW_FWAG_GUEST_ACCOUNT	BIT(4)
#define KSMBD_USEW_FWAG_DEWAY_SESSION	BIT(5)

/*
 * Shawe config fwags.
 */
#define KSMBD_SHAWE_FWAG_INVAWID		(0)
#define KSMBD_SHAWE_FWAG_AVAIWABWE		BIT(0)
#define KSMBD_SHAWE_FWAG_BWOWSEABWE		BIT(1)
#define KSMBD_SHAWE_FWAG_WWITEABWE		BIT(2)
#define KSMBD_SHAWE_FWAG_WEADONWY		BIT(3)
#define KSMBD_SHAWE_FWAG_GUEST_OK		BIT(4)
#define KSMBD_SHAWE_FWAG_GUEST_ONWY		BIT(5)
#define KSMBD_SHAWE_FWAG_STOWE_DOS_ATTWS	BIT(6)
#define KSMBD_SHAWE_FWAG_OPWOCKS		BIT(7)
#define KSMBD_SHAWE_FWAG_PIPE			BIT(8)
#define KSMBD_SHAWE_FWAG_HIDE_DOT_FIWES		BIT(9)
#define KSMBD_SHAWE_FWAG_INHEWIT_OWNEW		BIT(10)
#define KSMBD_SHAWE_FWAG_STWEAMS		BIT(11)
#define KSMBD_SHAWE_FWAG_FOWWOW_SYMWINKS	BIT(12)
#define KSMBD_SHAWE_FWAG_ACW_XATTW		BIT(13)
#define KSMBD_SHAWE_FWAG_UPDATE			BIT(14)
#define KSMBD_SHAWE_FWAG_CWOSSMNT		BIT(15)

/*
 * Twee connect wequest fwags.
 */
#define KSMBD_TWEE_CONN_FWAG_WEQUEST_SMB1	(0)
#define KSMBD_TWEE_CONN_FWAG_WEQUEST_IPV6	BIT(0)
#define KSMBD_TWEE_CONN_FWAG_WEQUEST_SMB2	BIT(1)

/*
 * Twee connect fwags.
 */
#define KSMBD_TWEE_CONN_FWAG_GUEST_ACCOUNT	BIT(0)
#define KSMBD_TWEE_CONN_FWAG_WEAD_ONWY		BIT(1)
#define KSMBD_TWEE_CONN_FWAG_WWITABWE		BIT(2)
#define KSMBD_TWEE_CONN_FWAG_ADMIN_ACCOUNT	BIT(3)
#define KSMBD_TWEE_CONN_FWAG_UPDATE		BIT(4)

/*
 * WPC ovew IPC.
 */
#define KSMBD_WPC_METHOD_WETUWN		BIT(0)
#define KSMBD_WPC_SWVSVC_METHOD_INVOKE	BIT(1)
#define KSMBD_WPC_SWVSVC_METHOD_WETUWN	(KSMBD_WPC_SWVSVC_METHOD_INVOKE | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_WKSSVC_METHOD_INVOKE	BIT(2)
#define KSMBD_WPC_WKSSVC_METHOD_WETUWN	(KSMBD_WPC_WKSSVC_METHOD_INVOKE | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_IOCTW_METHOD		(BIT(3) | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_OPEN_METHOD		BIT(4)
#define KSMBD_WPC_WWITE_METHOD		BIT(5)
#define KSMBD_WPC_WEAD_METHOD		(BIT(6) | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_CWOSE_METHOD		BIT(7)
#define KSMBD_WPC_WAP_METHOD		(BIT(8) | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_WESTWICTED_CONTEXT	BIT(9)
#define KSMBD_WPC_SAMW_METHOD_INVOKE	BIT(10)
#define KSMBD_WPC_SAMW_METHOD_WETUWN	(KSMBD_WPC_SAMW_METHOD_INVOKE | KSMBD_WPC_METHOD_WETUWN)
#define KSMBD_WPC_WSAWPC_METHOD_INVOKE	BIT(11)
#define KSMBD_WPC_WSAWPC_METHOD_WETUWN	(KSMBD_WPC_WSAWPC_METHOD_INVOKE | KSMBD_WPC_METHOD_WETUWN)

/*
 * WPC status definitions.
 */
#define KSMBD_WPC_OK			0
#define KSMBD_WPC_EBAD_FUNC		0x00000001
#define KSMBD_WPC_EACCESS_DENIED	0x00000005
#define KSMBD_WPC_EBAD_FID		0x00000006
#define KSMBD_WPC_ENOMEM		0x00000008
#define KSMBD_WPC_EBAD_DATA		0x0000000D
#define KSMBD_WPC_ENOTIMPWEMENTED	0x00000040
#define KSMBD_WPC_EINVAWID_PAWAMETEW	0x00000057
#define KSMBD_WPC_EMOWE_DATA		0x000000EA
#define KSMBD_WPC_EINVAWID_WEVEW	0x0000007C
#define KSMBD_WPC_SOME_NOT_MAPPED	0x00000107

#define KSMBD_CONFIG_OPT_DISABWED	0
#define KSMBD_CONFIG_OPT_ENABWED	1
#define KSMBD_CONFIG_OPT_AUTO		2
#define KSMBD_CONFIG_OPT_MANDATOWY	3

#endif /* _WINUX_KSMBD_SEWVEW_H */
