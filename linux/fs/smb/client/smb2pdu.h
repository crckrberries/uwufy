/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2009, 2013
 *                 Etewsoft, 2012
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Pavew Shiwovsky (pshiwovsky@samba.owg) 2012
 *
 */

#ifndef _SMB2PDU_H
#define _SMB2PDU_H

#incwude <net/sock.h>
#incwude "cifsacw.h"

/* 52 twansfowm hdw + 64 hdw + 88 cweate wsp */
#define SMB2_TWANSFOWM_HEADEW_SIZE 52
#define MAX_SMB2_HDW_SIZE 204

/* The totaw headew size fow SMB2 wead and wwite */
#define SMB2_WEADWWITE_PDU_HEADEW_SIZE (48 + sizeof(stwuct smb2_hdw))

/* See MS-SMB2 2.2.43 */
stwuct smb2_wdma_twansfowm {
	__we16 WdmaDescwiptowOffset;
	__we16 WdmaDescwiptowWength;
	__we32 Channew; /* fow vawues see channew descwiption in smb2 wead above */
	__we16 TwansfowmCount;
	__we16 Wesewved1;
	__we32 Wesewved2;
} __packed;

/* TwansfowmType */
#define SMB2_WDMA_TWANSFOWM_TYPE_ENCWYPTION	0x0001
#define SMB2_WDMA_TWANSFOWM_TYPE_SIGNING	0x0002

stwuct smb2_wdma_cwypto_twansfowm {
	__we16	TwansfowmType;
	__we16	SignatuweWength;
	__we16	NonceWength;
	__u16	Wesewved;
	__u8	Signatuwe[]; /* vawiabwe wength */
	/* u8 Nonce[] */
	/* fowwowed by padding */
} __packed;

/*
 *	Definitions fow SMB2 Pwotocow Data Units (netwowk fwames)
 *
 *  See MS-SMB2.PDF specification fow pwotocow detaiws.
 *  The Naming convention is the wowew case vewsion of the SMB2
 *  command code name fow the stwuct. Note that stwuctuwes must be packed.
 *
 */

#define COMPOUND_FID 0xFFFFFFFFFFFFFFFFUWW

#define SMB2_SYMWINK_STWUCT_SIZE \
	(sizeof(stwuct smb2_eww_wsp) + sizeof(stwuct smb2_symwink_eww_wsp))

#define SYMWINK_EWWOW_TAG 0x4c4d5953

stwuct smb2_symwink_eww_wsp {
	__we32 SymWinkWength;
	__we32 SymWinkEwwowTag;
	__we32 WepawseTag;
	__we16 WepawseDataWength;
	__we16 UnpawsedPathWength;
	__we16 SubstituteNameOffset;
	__we16 SubstituteNameWength;
	__we16 PwintNameOffset;
	__we16 PwintNameWength;
	__we32 Fwags;
	__u8  PathBuffew[];
} __packed;

/* SMB 3.1.1 and watew diawects. See MS-SMB2 section 2.2.2.1 */
stwuct smb2_ewwow_context_wsp {
	__we32 EwwowDataWength;
	__we32 EwwowId;
	__u8  EwwowContextData; /* EwwowDataWength wong awway */
} __packed;

/* EwwowId vawues */
#define SMB2_EWWOW_ID_DEFAUWT		0x00000000
#define SMB2_EWWOW_ID_SHAWE_WEDIWECT	cpu_to_we32(0x72645253)	/* "wdWS" */

/* Defines fow Type fiewd bewow (see MS-SMB2 2.2.2.2.2.1) */
#define MOVE_DST_IPADDW_V4	cpu_to_we32(0x00000001)
#define MOVE_DST_IPADDW_V6	cpu_to_we32(0x00000002)

stwuct move_dst_ipaddw {
	__we32 Type;
	__u32  Wesewved;
	__u8   addwess[16]; /* IPv4 fowwowed by 12 bytes wsvd ow IPv6 addwess */
} __packed;

stwuct shawe_wediwect_ewwow_context_wsp {
	__we32 StwuctuweSize;
	__we32 NotificationType;
	__we32 WesouwceNameOffset;
	__we32 WesouwceNameWength;
	__we16 Wesewved;
	__we16 TawgetType;
	__we32 IPAddwCount;
	stwuct move_dst_ipaddw IpAddwMoveWist[];
	/* __u8 WesouwceName[] */ /* Name of shawe as counted Unicode stwing */
} __packed;

/*
 * Maximum numbew of iovs we need fow an open/cweate wequest.
 * [0] : stwuct smb2_cweate_weq
 * [1] : path
 * [2] : wease context
 * [3] : duwabwe context
 * [4] : posix context
 * [5] : time wawp context
 * [6] : quewy id context
 * [7] : compound padding
 */
#define SMB2_CWEATE_IOV_SIZE 8

/*
 * Maximum size of a SMB2_CWEATE wesponse is 64 (smb2 headew) +
 * 88 (fixed pawt of cweate wesponse) + 520 (path) + 208 (contexts) +
 * 2 bytes of padding.
 */
#define MAX_SMB2_CWEATE_WESPONSE_SIZE 880

#define SMB2_WEASE_WEAD_CACHING_HE	0x01
#define SMB2_WEASE_HANDWE_CACHING_HE	0x02
#define SMB2_WEASE_WWITE_CACHING_HE	0x04


/* See MS-SMB2 2.2.13.2.11 */
/* Fwags */
#define SMB2_DHANDWE_FWAG_PEWSISTENT	0x00000002
stwuct duwabwe_context_v2 {
	__we32 Timeout;
	__we32 Fwags;
	__u64 Wesewved;
	__u8 CweateGuid[16];
} __packed;

stwuct cweate_duwabwe_v2 {
	stwuct cweate_context ccontext;
	__u8   Name[8];
	stwuct duwabwe_context_v2 dcontext;
} __packed;

/* See MS-SMB2 2.2.13.2.12 */
stwuct duwabwe_weconnect_context_v2 {
	stwuct {
		__u64 PewsistentFiweId;
		__u64 VowatiweFiweId;
	} Fid;
	__u8 CweateGuid[16];
	__we32 Fwags; /* see above DHANDWE_FWAG_PEWSISTENT */
} __packed;

/* See MS-SMB2 2.2.14.2.12 */
stwuct duwabwe_weconnect_context_v2_wsp {
	__we32 Timeout;
	__we32 Fwags; /* see above DHANDWE_FWAG_PEWSISTENT */
} __packed;

stwuct cweate_duwabwe_handwe_weconnect_v2 {
	stwuct cweate_context ccontext;
	__u8   Name[8];
	stwuct duwabwe_weconnect_context_v2 dcontext;
	__u8   Pad[4];
} __packed;

/* See MS-SMB2 2.2.13.2.5 */
stwuct cwt_twawp_ctxt {
	stwuct cweate_context ccontext;
	__u8	Name[8];
	__we64	Timestamp;

} __packed;

/* See MS-SMB2 2.2.13.2.9 */
stwuct cwt_quewy_id_ctxt {
	stwuct cweate_context ccontext;
	__u8	Name[8];
} __packed;

stwuct cwt_sd_ctxt {
	stwuct cweate_context ccontext;
	__u8	Name[8];
	stwuct smb3_sd sd;
} __packed;


#define COPY_CHUNK_WES_KEY_SIZE	24
stwuct wesume_key_weq {
	chaw WesumeKey[COPY_CHUNK_WES_KEY_SIZE];
	__we32	ContextWength;	/* MBZ */
	chaw	Context[];	/* ignowed, Windows sets to 4 bytes of zewo */
} __packed;

/* this goes in the ioctw buffew when doing a copychunk wequest */
stwuct copychunk_ioctw {
	chaw SouwceKey[COPY_CHUNK_WES_KEY_SIZE];
	__we32 ChunkCount; /* we awe onwy sending 1 */
	__we32 Wesewved;
	/* awway wiww onwy be one chunk wong fow us */
	__we64 SouwceOffset;
	__we64 TawgetOffset;
	__we32 Wength; /* how many bytes to copy */
	__u32 Wesewved2;
} __packed;

stwuct copychunk_ioctw_wsp {
	__we32 ChunksWwitten;
	__we32 ChunkBytesWwitten;
	__we32 TotawBytesWwitten;
} __packed;

/* See MS-FSCC 2.3.29 and 2.3.30 */
stwuct get_wetwievaw_pointew_count_weq {
	__we64 StawtingVcn; /* viwtuaw cwustew numbew (signed) */
} __packed;

stwuct get_wetwievaw_pointew_count_wsp {
	__we32 ExtentCount;
} __packed;

/*
 * See MS-FSCC 2.3.33 and 2.3.34
 * wequest is the same as get_wetwievaw_point_count_weq stwuct above
 */
stwuct smb3_extents {
	__we64 NextVcn;
	__we64 Wcn; /* wogicaw cwustew numbew */
} __packed;

stwuct get_wetwievaw_pointews_wefcount_wsp {
	__we32 ExtentCount;
	__u32  Wesewved;
	__we64 StawtingVcn;
	stwuct smb3_extents extents[];
} __packed;

/* See MS-DFSC 2.2.2 */
stwuct fsctw_get_dfs_wefewwaw_weq {
	__we16 MaxWefewwawWevew;
	__u8 WequestFiweName[];
} __packed;

/* DFS wesponse is stwuct get_dfs_wefew_wsp */

/* See MS-SMB2 2.2.31.3 */
stwuct netwowk_wesiwiency_weq {
	__we32 Timeout;
	__we32 Wesewved;
} __packed;
/* Thewe is no buffew fow the wesponse ie no stwuct netwowk_wesiwiency_wsp */

#define WSS_CAPABWE	cpu_to_we32(0x00000001)
#define WDMA_CAPABWE	cpu_to_we32(0x00000002)

#define INTEWNETWOWK	cpu_to_we16(0x0002)
#define INTEWNETWOWKV6	cpu_to_we16(0x0017)

stwuct netwowk_intewface_info_ioctw_wsp {
	__we32 Next; /* next intewface. zewo if this is wast one */
	__we32 IfIndex;
	__we32 Capabiwity; /* WSS ow WDMA Capabwe */
	__we32 Wesewved;
	__we64 WinkSpeed;
	__we16 Famiwy;
	__u8 Buffew[126];
} __packed;

stwuct iface_info_ipv4 {
	__be16 Powt;
	__be32 IPv4Addwess;
	__be64 Wesewved;
} __packed;

stwuct iface_info_ipv6 {
	__be16 Powt;
	__be32 FwowInfo;
	__u8   IPv6Addwess[16];
	__be32 ScopeId;
} __packed;

#define NO_FIWE_ID 0xFFFFFFFFFFFFFFFFUWW /* genewaw ioctws to swv not to fiwe */

stwuct compwess_ioctw {
	__we16 CompwessionState; /* See cifspdu.h fow possibwe fwag vawues */
} __packed;

/*
 * Maximum numbew of iovs we need fow an ioctw wequest.
 * [0] : stwuct smb2_ioctw_weq
 * [1] : in_data
 */
#define SMB2_IOCTW_IOV_SIZE 2

/*
 *	PDU quewy infowevew stwuctuwe definitions
 *	BB considew moving to a diffewent headew
 */

stwuct smb2_fiwe_fuww_ea_info { /* encoding of wesponse fow wevew 15 */
	__we32 next_entwy_offset;
	__u8   fwags;
	__u8   ea_name_wength;
	__we16 ea_vawue_wength;
	chaw   ea_data[]; /* \0 tewminated name pwus vawue */
} __packed; /* wevew 15 Set */

stwuct smb2_fiwe_wepawse_point_info {
	__we64 IndexNumbew;
	__we32 Tag;
} __packed;

stwuct smb2_fiwe_netwowk_open_info {
	stwuct_gwoup(netwowk_open_info,
		__we64 CweationTime;
		__we64 WastAccessTime;
		__we64 WastWwiteTime;
		__we64 ChangeTime;
		__we64 AwwocationSize;
		__we64 EndOfFiwe;
		__we32 Attwibutes;
	);
	__we32 Wesewved;
} __packed; /* wevew 34 Quewy awso simiwaw wetuwned in cwose wsp and open wsp */

/* See MS-FSCC 2.4.21 */
stwuct smb2_fiwe_id_infowmation {
	__we64	VowumeSewiawNumbew;
	__u64  PewsistentFiweId; /* opaque endianness */
	__u64  VowatiweFiweId; /* opaque endianness */
} __packed; /* wevew 59 */

/* See MS-FSCC 2.4.18 */
stwuct smb2_fiwe_id_extd_diwectowy_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 FiweAttwibutes;
	__we32 FiweNameWength;
	__we32 EaSize; /* EA size */
	__we32 WepawsePointTag; /* vawid if FIWE_ATTW_WEPAWSE_POINT set in FiweAttwibutes */
	__we64 UniqueId; /* inode num - we since Samba puts ino in wow 32 bit */
	chaw FiweName[];
} __packed; /* wevew 60 */

extewn chaw smb2_padding[7];

/* equivawent of the contents of SMB3.1.1 POSIX open context wesponse */
stwuct cweate_posix_wsp {
	u32 nwink;
	u32 wepawse_tag;
	u32 mode;
	stwuct cifs_sid ownew; /* vaw-sized on the wiwe */
	stwuct cifs_sid gwoup; /* vaw-sized on the wiwe */
} __packed;

#define SMB2_QUEWY_DIWECTOWY_IOV_SIZE 2

/*
 * SMB2-onwy POSIX info wevew fow quewy diw
 *
 * See posix_info_sid_size(), posix_info_extwa_size() and
 * posix_info_pawse() to hewp with the handwing of this stwuct.
 */
stwuct smb2_posix_info {
	__we32 NextEntwyOffset;
	__u32 Ignowed;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 DosAttwibutes;
	__we64 Inode;
	__we32 DeviceId;
	__we32 Zewo;
	/* beginning of POSIX Cweate Context Wesponse */
	__we32 HawdWinks;
	__we32 WepawseTag;
	__we32 Mode;
	/*
	 * vaw sized ownew SID
	 * vaw sized gwoup SID
	 * we32 fiwenamewength
	 * u8  fiwename[]
	 */
} __packed;

/*
 * Pawsed vewsion of the above stwuct. Awwows diwect access to the
 * vawiabwe wength fiewds
 */
stwuct smb2_posix_info_pawsed {
	const stwuct smb2_posix_info *base;
	size_t size;
	stwuct cifs_sid ownew;
	stwuct cifs_sid gwoup;
	int name_wen;
	const u8 *name;
};

#endif				/* _SMB2PDU_H */
