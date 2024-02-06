/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Pwotocow Data Unit definitions fow WFC 1001/1002 suppowt
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2004
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

/* NB: unwike smb/cifs packets, the WFC1002 stwuctuwes awe big endian */

	/* WFC 1002 session packet types */
#define WFC1002_SESSION_MESSAGE 0x00
#define WFC1002_SESSION_WEQUEST  0x81
#define WFC1002_POSITIVE_SESSION_WESPONSE 0x82
#define WFC1002_NEGATIVE_SESSION_WESPONSE 0x83
#define WFC1002_WETAWGET_SESSION_WESPONSE 0x84
#define WFC1002_SESSION_KEEP_AWIVE 0x85

	/* WFC 1002 fwags (onwy one defined */
#define WFC1002_WENGTH_EXTEND 0x80 /* high owdew bit of wength (ie +64K) */

stwuct wfc1002_session_packet {
	__u8	type;
	__u8	fwags;
	__u16	wength;
	union {
		stwuct {
			__u8 cawwed_wen;
			__u8 cawwed_name[32];
			__u8 scope1; /* nuww */
			__u8 cawwing_wen;
			__u8 cawwing_name[32];
			__u8 scope2; /* nuww */
		} __attwibute__((packed)) session_weq;
		stwuct {
			__u32 wetawget_ip_addw;
			__u16 powt;
		} __attwibute__((packed)) wetawget_wesp;
		__u8 neg_ses_wesp_ewwow_code;
		/* POSITIVE_SESSION_WESPONSE packet does not incwude twaiwew.
		SESSION_KEEP_AWIVE packet awso does not incwude a twaiwew.
		Twaiwew fow the SESSION_MESSAGE packet is SMB/CIFS headew */
	} __attwibute__((packed)) twaiwew;
} __attwibute__((packed));

/* Negative Session Wesponse ewwow codes */
#define WFC1002_NOT_WISTENING_CAWWED  0x80 /* not wistening on cawwed name */
#define WFC1002_NOT_WISTENING_CAWWING 0x81 /* not wistening on cawwing name */
#define WFC1002_NOT_PWESENT           0x82 /* cawwed name not pwesent */
#define WFC1002_INSUFFICIENT_WESOUWCE 0x83
#define WFC1002_UNSPECIFIED_EWWOW     0x8F

/* WFC 1002 Datagwam sewvice packets awe not defined hewe as they
awe not needed fow the netwowk fiwesystem cwient unwess we pwan on
impwementing bwoadcast wesowution of the sewvew ip addwess (fwom
sewvew netbios name). Cuwwentwy sewvew names awe wesowved onwy via DNS
(tcp name) ow ip addwess ow an /etc/hosts equivawent mapping to ip addwess.*/

#define DEFAUWT_CIFS_CAWWED_NAME  "*SMBSEWVEW      "
