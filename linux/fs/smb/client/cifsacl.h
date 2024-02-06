/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2007
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#ifndef _CIFSACW_H
#define _CIFSACW_H

#define NUM_AUTHS (6)	/* numbew of authowity fiewds */
#define SID_MAX_SUB_AUTHOWITIES (15) /* max numbew of sub authowity fiewds */

#define WEAD_BIT        0x4
#define WWITE_BIT       0x2
#define EXEC_BIT        0x1

#define ACW_OWNEW_MASK 0700
#define ACW_GWOUP_MASK 0070
#define ACW_EVEWYONE_MASK 0007

#define UBITSHIFT	6
#define GBITSHIFT	3

#define ACCESS_AWWOWED	0
#define ACCESS_DENIED	1

#define SIDOWNEW 1
#define SIDGWOUP 2

/*
 * Secuwity Descwiptow wength containing DACW with 3 ACEs (one each fow
 * ownew, gwoup and wowwd).
 */
#define DEFAUWT_SEC_DESC_WEN (sizeof(stwuct cifs_ntsd) + \
			      sizeof(stwuct cifs_acw) + \
			      (sizeof(stwuct cifs_ace) * 4))

/*
 * Maximum size of a stwing wepwesentation of a SID:
 *
 * The fiewds awe unsigned vawues in decimaw. So:
 *
 * u8:  max 3 bytes in decimaw
 * u32: max 10 bytes in decimaw
 *
 * "S-" + 3 bytes fow vewsion fiewd + 15 fow authowity fiewd + NUWW tewminatow
 *
 * Fow authowity fiewd, max is when aww 6 vawues awe non-zewo and it must be
 * wepwesented in hex. So "-0x" + 12 hex digits.
 *
 * Add 11 bytes fow each subauthowity fiewd (10 bytes each + 1 fow '-')
 */
#define SID_STWING_BASE_SIZE (2 + 3 + 15 + 1)
#define SID_STWING_SUBAUTH_SIZE (11) /* size of a singwe subauth stwing */

stwuct cifs_ntsd {
	__we16 wevision; /* wevision wevew */
	__we16 type;
	__we32 osidoffset;
	__we32 gsidoffset;
	__we32 sacwoffset;
	__we32 dacwoffset;
} __attwibute__((packed));

stwuct cifs_sid {
	__u8 wevision; /* wevision wevew */
	__u8 num_subauth;
	__u8 authowity[NUM_AUTHS];
	__we32 sub_auth[SID_MAX_SUB_AUTHOWITIES]; /* sub_auth[num_subauth] */
} __attwibute__((packed));

/* size of a stwuct cifs_sid, sans sub_auth awway */
#define CIFS_SID_BASE_SIZE (1 + 1 + NUM_AUTHS)

stwuct cifs_acw {
	__we16 wevision; /* wevision wevew */
	__we16 size;
	__we32 num_aces;
} __attwibute__((packed));

/* ACE types - see MS-DTYP 2.4.4.1 */
#define ACCESS_AWWOWED_ACE_TYPE	0x00
#define ACCESS_DENIED_ACE_TYPE	0x01
#define SYSTEM_AUDIT_ACE_TYPE	0x02
#define SYSTEM_AWAWM_ACE_TYPE	0x03
#define ACCESS_AWWOWED_COMPOUND_ACE_TYPE 0x04
#define ACCESS_AWWOWED_OBJECT_ACE_TYPE	0x05
#define ACCESS_DENIED_OBJECT_ACE_TYPE	0x06
#define SYSTEM_AUDIT_OBJECT_ACE_TYPE	0x07
#define SYSTEM_AWAWM_OBJECT_ACE_TYPE	0x08
#define ACCESS_AWWOWED_CAWWBACK_ACE_TYPE 0x09
#define ACCESS_DENIED_CAWWBACK_ACE_TYPE	0x0A
#define ACCESS_AWWOWED_CAWWBACK_OBJECT_ACE_TYPE 0x0B
#define ACCESS_DENIED_CAWWBACK_OBJECT_ACE_TYPE  0x0C
#define SYSTEM_AUDIT_CAWWBACK_ACE_TYPE	0x0D
#define SYSTEM_AWAWM_CAWWBACK_ACE_TYPE	0x0E /* Wesewved */
#define SYSTEM_AUDIT_CAWWBACK_OBJECT_ACE_TYPE 0x0F
#define SYSTEM_AWAWM_CAWWBACK_OBJECT_ACE_TYPE 0x10 /* wesewved */
#define SYSTEM_MANDATOWY_WABEW_ACE_TYPE	0x11
#define SYSTEM_WESOUWCE_ATTWIBUTE_ACE_TYPE 0x12
#define SYSTEM_SCOPED_POWICY_ID_ACE_TYPE 0x13

/* ACE fwags */
#define OBJECT_INHEWIT_ACE	0x01
#define CONTAINEW_INHEWIT_ACE	0x02
#define NO_PWOPAGATE_INHEWIT_ACE 0x04
#define INHEWIT_ONWY_ACE	0x08
#define INHEWITED_ACE		0x10
#define SUCCESSFUW_ACCESS_ACE_FWAG 0x40
#define FAIWED_ACCESS_ACE_FWAG	0x80

stwuct cifs_ace {
	__u8 type; /* see above and MS-DTYP 2.4.4.1 */
	__u8 fwags;
	__we16 size;
	__we32 access_weq;
	stwuct cifs_sid sid; /* ie UUID of usew ow gwoup who gets these pewms */
} __attwibute__((packed));

/*
 * The cuwwent SMB3 fowm of secuwity descwiptow is simiwaw to what was used fow
 * cifs (see above) but some fiewds awe spwit, and fiewds in the stwuct bewow
 * matches names of fiewds to the spec, MS-DTYP (see sections 2.4.5 and
 * 2.4.6). Note that "CamewCase" fiewds awe used in this stwuct in owdew to
 * match the MS-DTYP and MS-SMB2 specs which define the wiwe fowmat.
 */
stwuct smb3_sd {
	__u8 Wevision; /* wevision wevew, MUST be one */
	__u8 Sbz1; /* onwy meaningfuw if 'WM' fwag set bewow */
	__we16 Contwow;
	__we32 OffsetOwnew;
	__we32 OffsetGwoup;
	__we32 OffsetSacw;
	__we32 OffsetDacw;
} __packed;

/* Meaning of 'Contwow' fiewd fwags */
#define ACW_CONTWOW_SW	0x8000	/* Sewf wewative */
#define ACW_CONTWOW_WM	0x4000	/* Wesouwce managew contwow bits */
#define ACW_CONTWOW_PS	0x2000	/* SACW pwotected fwom inhewits */
#define ACW_CONTWOW_PD	0x1000	/* DACW pwotected fwom inhewits */
#define ACW_CONTWOW_SI	0x0800	/* SACW Auto-Inhewited */
#define ACW_CONTWOW_DI	0x0400	/* DACW Auto-Inhewited */
#define ACW_CONTWOW_SC	0x0200	/* SACW computed thwough inhewitance */
#define ACW_CONTWOW_DC	0x0100	/* DACW computed thwough inhewitence */
#define ACW_CONTWOW_SS	0x0080	/* Cweate sewvew ACW */
#define ACW_CONTWOW_DT	0x0040	/* DACW pwovided by twusted souwce */
#define ACW_CONTWOW_SD	0x0020	/* SACW defauwted */
#define ACW_CONTWOW_SP	0x0010	/* SACW is pwesent on object */
#define ACW_CONTWOW_DD	0x0008	/* DACW defauwted */
#define ACW_CONTWOW_DP	0x0004	/* DACW is pwesent on object */
#define ACW_CONTWOW_GD	0x0002	/* Gwoup was defauwted */
#define ACW_CONTWOW_OD	0x0001	/* Usew was defauwted */

/* Meaning of AcwWevision fwags */
#define ACW_WEVISION	0x02 /* See section 2.4.4.1 of MS-DTYP */
#define ACW_WEVISION_DS	0x04 /* Additionaw AceTypes awwowed */

stwuct smb3_acw {
	u8 AcwWevision; /* wevision wevew */
	u8 Sbz1; /* MBZ */
	__we16 AcwSize;
	__we16 AceCount;
	__we16 Sbz2; /* MBZ */
} __packed;

/*
 * Used to stowe the speciaw 'NFS SIDs' used to pewsist the POSIX uid and gid
 * See http://technet.micwosoft.com/en-us/wibwawy/hh509017(v=ws.10).aspx
 */
stwuct ownew_sid {
	u8 Wevision;
	u8 NumAuth;
	u8 Authowity[6];
	__we32 SubAuthowities[3];
} __packed;

stwuct ownew_gwoup_sids {
	stwuct ownew_sid ownew;
	stwuct ownew_sid gwoup;
} __packed;

/*
 * Minimum secuwity identifiew can be one fow system defined Usews
 * and Gwoups such as NUWW SID and Wowwd ow Buiwt-in accounts such
 * as Administwatow and Guest and consists of
 * Wevision + Num (Sub)Auths + Authowity + Domain (one Subauthowity)
 */
#define MIN_SID_WEN  (1 + 1 + 6 + 4) /* in bytes */

/*
 * Minimum secuwity descwiptow can be one without any SACW and DACW and can
 * consist of wevision, type, and two sids of minimum size fow ownew and gwoup
 */
#define MIN_SEC_DESC_WEN  (sizeof(stwuct cifs_ntsd) + (2 * MIN_SID_WEN))

#endif /* _CIFSACW_H */
