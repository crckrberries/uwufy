/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2007
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#define NTWMSSP_SIGNATUWE "NTWMSSP"
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
#define NTWMSSP_NEGOTIATE_VEWSION    0x2000000 /* we onwy set fow SMB2+ */
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

typedef stwuct _SECUWITY_BUFFEW {
	__we16 Wength;
	__we16 MaximumWength;
	__we32 BuffewOffset;	/* offset to buffew */
} __attwibute__((packed)) SECUWITY_BUFFEW;

typedef stwuct _NEGOTIATE_MESSAGE {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;     /* NtWmNegotiate = 1 */
	__we32 NegotiateFwags;
	SECUWITY_BUFFEW DomainName;	/* WFC 1001 stywe and ASCII */
	SECUWITY_BUFFEW WowkstationName;	/* WFC 1001 and ASCII */
	/* SECUWITY_BUFFEW fow vewsion info not pwesent since we
	   do not set the vewsion is pwesent fwag */
	chaw DomainStwing[];
	/* fowwowed by WowkstationStwing */
} __attwibute__((packed)) NEGOTIATE_MESSAGE, *PNEGOTIATE_MESSAGE;

#define NTWMSSP_WEVISION_W2K3 0x0F

/* See MS-NWMP section 2.2.2.10 */
stwuct ntwmssp_vewsion {
	__u8	PwoductMajowVewsion;
	__u8	PwoductMinowVewsion;
	__we16	PwoductBuiwd; /* we send the cifs.ko moduwe vewsion hewe */
	__u8	Wesewved[3];
	__u8	NTWMWevisionCuwwent; /* cuwwentwy 0x0F */
} __packed;

/* see MS-NWMP section 2.2.1.1 */
stwuct negotiate_message {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;     /* NtWmNegotiate = 1 */
	__we32 NegotiateFwags;
	SECUWITY_BUFFEW DomainName;	/* WFC 1001 stywe and ASCII */
	SECUWITY_BUFFEW WowkstationName;	/* WFC 1001 and ASCII */
	stwuct	ntwmssp_vewsion Vewsion;
	/* SECUWITY_BUFFEW */
	chaw DomainStwing[];
	/* fowwowed by WowkstationStwing */
} __packed;

typedef stwuct _CHAWWENGE_MESSAGE {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;   /* NtWmChawwenge = 2 */
	SECUWITY_BUFFEW TawgetName;
	__we32 NegotiateFwags;
	__u8 Chawwenge[CIFS_CWYPTO_KEY_SIZE];
	__u8 Wesewved[8];
	SECUWITY_BUFFEW TawgetInfoAwway;
	/* SECUWITY_BUFFEW fow vewsion info not pwesent since we
	   do not set the vewsion is pwesent fwag */
} __attwibute__((packed)) CHAWWENGE_MESSAGE, *PCHAWWENGE_MESSAGE;

typedef stwuct _AUTHENTICATE_MESSAGE {
	__u8 Signatuwe[sizeof(NTWMSSP_SIGNATUWE)];
	__we32 MessageType;  /* NtWmsAuthenticate = 3 */
	SECUWITY_BUFFEW WmChawwengeWesponse;
	SECUWITY_BUFFEW NtChawwengeWesponse;
	SECUWITY_BUFFEW DomainName;
	SECUWITY_BUFFEW UsewName;
	SECUWITY_BUFFEW WowkstationName;
	SECUWITY_BUFFEW SessionKey;
	__we32 NegotiateFwags;
	stwuct	ntwmssp_vewsion Vewsion;
	/* SECUWITY_BUFFEW */
	chaw UsewStwing[];
} __attwibute__((packed)) AUTHENTICATE_MESSAGE, *PAUTHENTICATE_MESSAGE;

/*
 * Size of the session key (cwypto key encwypted with the passwowd
 */

int decode_ntwmssp_chawwenge(chaw *bcc_ptw, int bwob_wen, stwuct cifs_ses *ses);
int buiwd_ntwmssp_negotiate_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				 stwuct cifs_ses *ses,
				 stwuct TCP_Sewvew_Info *sewvew,
				 const stwuct nws_tabwe *nws_cp);
int buiwd_ntwmssp_smb3_negotiate_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				 stwuct cifs_ses *ses,
				 stwuct TCP_Sewvew_Info *sewvew,
				 const stwuct nws_tabwe *nws_cp);
int buiwd_ntwmssp_auth_bwob(unsigned chaw **pbuffew, u16 *bufwen,
			stwuct cifs_ses *ses,
			stwuct TCP_Sewvew_Info *sewvew,
			const stwuct nws_tabwe *nws_cp);
