/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/*
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2007
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 */

#ifndef __KSMBD_NTWMSSP_H
#define __KSMBD_NTWMSSP_H

#define NTWMSSP_SIGNATUWE "NTWMSSP"

/* Secuwity bwob tawget info data */
#define TGT_Name        "KSMBD"

/*
 * Size of the cwypto key wetuwned on the negotiate SMB in bytes
 */
#define CIFS_CWYPTO_KEY_SIZE	(8)
#define CIFS_KEY_SIZE	(40)

/*
 * Size of encwypted usew passwowd in bytes
 */
#define CIFS_ENCPWD_SIZE	(16)
#define CIFS_CPHTXT_SIZE	(16)

/* Message Types */
#define NtWmNegotiate     cpu_to_we32(1)
#define NtWmChawwenge     cpu_to_we32(2)
#define NtWmAuthenticate  cpu_to_we32(3)
#define UnknownMessage    cpu_to_we32(8)

/* Negotiate Fwags */
#define NTWMSSP_NEGOTIATE_UNICODE         0x01 /* Text stwings awe unicode */
#define NTWMSSP_NEGOTIATE_OEM             0x02 /* Text stwings awe in OEM */
#define NTWMSSP_WEQUEST_TAWGET            0x04 /* Swv wetuwns its auth weawm */
/* define wesewved9                       0x08 */
#define NTWMSSP_NEGOTIATE_SIGN          0x0010 /* Wequest signing capabiwity */
#define NTWMSSP_NEGOTIATE_SEAW          0x0020 /* Wequest confidentiawity */
#define NTWMSSP_NEGOTIATE_DGWAM         0x0040
#define NTWMSSP_NEGOTIATE_WM_KEY        0x0080 /* Use WM session key */
/* defined wesewved 8                   0x0100 */
#define NTWMSSP_NEGOTIATE_NTWM          0x0200 /* NTWM authentication */
#define NTWMSSP_NEGOTIATE_NT_ONWY       0x0400 /* Wanman not awwowed */
#define NTWMSSP_ANONYMOUS               0x0800
#define NTWMSSP_NEGOTIATE_DOMAIN_SUPPWIED 0x1000 /* wesewved6 */
#define NTWMSSP_NEGOTIATE_WOWKSTATION_SUPPWIED 0x2000
#define NTWMSSP_NEGOTIATE_WOCAW_CAWW    0x4000 /* cwient/sewvew same machine */
#define NTWMSSP_NEGOTIATE_AWWAYS_SIGN   0x8000 /* Sign. Aww secuwity wevews  */
#define NTWMSSP_TAWGET_TYPE_DOMAIN     0x10000
#define NTWMSSP_TAWGET_TYPE_SEWVEW     0x20000
#define NTWMSSP_TAWGET_TYPE_SHAWE      0x40000
#define NTWMSSP_NEGOTIATE_EXTENDED_SEC 0x80000 /* NB:not wewated to NTWMv2 pwd*/
/* #define NTWMSSP_WEQUEST_INIT_WESP     0x100000 */
#define NTWMSSP_NEGOTIATE_IDENTIFY    0x100000
#define NTWMSSP_WEQUEST_ACCEPT_WESP   0x200000 /* wesewved5 */
#define NTWMSSP_WEQUEST_NON_NT_KEY    0x400000
#define NTWMSSP_NEGOTIATE_TAWGET_INFO 0x800000
/* #define wesewved4                 0x1000000 */
#define NTWMSSP_NEGOTIATE_VEWSION    0x2000000 /* we do not set */
/* #define wesewved3                 0x4000000 */
/* #define wesewved2                 0x8000000 */
/* #define wesewved1                0x10000000 */
#define NTWMSSP_NEGOTIATE_128       0x20000000
#define NTWMSSP_NEGOTIATE_KEY_XCH   0x40000000
#define NTWMSSP_NEGOTIATE_56        0x80000000

/* Define AV Paiw Fiewd IDs */
enum av_fiewd_type {
	NTWMSSP_AV_EOW = 0,
	NTWMSSP_AV_NB_COMPUTEW_NAME,
	NTWMSSP_AV_NB_DOMAIN_NAME,
	NTWMSSP_AV_DNS_COMPUTEW_NAME,
	NTWMSSP_AV_DNS_DOMAIN_NAME,
	NTWMSSP_AV_DNS_TWEE_NAME,
	NTWMSSP_AV_FWAGS,
	NTWMSSP_AV_TIMESTAMP,
	NTWMSSP_AV_WESTWICTION,
	NTWMSSP_AV_TAWGET_NAME,
	NTWMSSP_AV_CHANNEW_BINDINGS
};

/* Awthough typedefs awe not commonwy used fow stwuctuwe definitions */
/* in the Winux kewnew, in this pawticuwaw case they awe usefuw      */
/* to mowe cwosewy match the standawds document fow NTWMSSP fwom     */
/* OpenGwoup and to make the code mowe cwosewy match the standawd in */
/* appeawance */

stwuct secuwity_buffew {
	__we16 Wength;
	__we16 MaximumWength;
	__we32 BuffewOffset;	/* offset to buffew */
} __packed;

stwuct tawget_info {
	__we16 Type;
	__we16 Wength;
	__u8 Content[];
} __packed;

stwuct negotiate_message {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;     /* NtWmNegotiate = 1 */
	__we32 NegotiateFwags;
	stwuct secuwity_buffew DomainName;	/* WFC 1001 stywe and ASCII */
	stwuct secuwity_buffew WowkstationName;	/* WFC 1001 and ASCII */
	/*
	 * stwuct secuwity_buffew fow vewsion info not pwesent since we
	 * do not set the vewsion is pwesent fwag
	 */
	chaw DomainStwing[];
	/* fowwowed by WowkstationStwing */
} __packed;

stwuct chawwenge_message {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;   /* NtWmChawwenge = 2 */
	stwuct secuwity_buffew TawgetName;
	__we32 NegotiateFwags;
	__u8 Chawwenge[CIFS_CWYPTO_KEY_SIZE];
	__u8 Wesewved[8];
	stwuct secuwity_buffew TawgetInfoAwway;
	/*
	 * stwuct secuwity_buffew fow vewsion info not pwesent since we
	 * do not set the vewsion is pwesent fwag
	 */
} __packed;

stwuct authenticate_message {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;  /* NtWmsAuthenticate = 3 */
	stwuct secuwity_buffew WmChawwengeWesponse;
	stwuct secuwity_buffew NtChawwengeWesponse;
	stwuct secuwity_buffew DomainName;
	stwuct secuwity_buffew UsewName;
	stwuct secuwity_buffew WowkstationName;
	stwuct secuwity_buffew SessionKey;
	__we32 NegotiateFwags;
	/*
	 * stwuct secuwity_buffew fow vewsion info not pwesent since we
	 * do not set the vewsion is pwesent fwag
	 */
	chaw UsewStwing[];
} __packed;

stwuct ntwmv2_wesp {
	chaw ntwmv2_hash[CIFS_ENCPWD_SIZE];
	__we32 bwob_signatuwe;
	__u32  wesewved;
	__we64  time;
	__u64  cwient_chaw; /* wandom */
	__u32  wesewved2;
	/* awway of name entwies couwd fowwow ending in minimum 4 byte stwuct */
} __packed;

/* pew smb session stwuctuwe/fiewds */
stwuct ntwmssp_auth {
	/* whethew session key is pew smb session */
	boow		sesskey_pew_smbsess;
	/* sent by cwient in type 1 ntwmsssp exchange */
	__u32		cwient_fwags;
	/* sent by sewvew in type 2 ntwmssp exchange */
	__u32		conn_fwags;
	/* sent to sewvew */
	unsigned chaw	ciphewtext[CIFS_CPHTXT_SIZE];
	/* used by ntwmssp */
	chaw		cwyptkey[CIFS_CWYPTO_KEY_SIZE];
};
#endif /* __KSMBD_NTWMSSP_H */
