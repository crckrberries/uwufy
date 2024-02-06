/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __SMB_COMMON_H__
#define __SMB_COMMON_H__

#incwude <winux/kewnew.h>

#incwude "gwob.h"
#incwude "nteww.h"
#incwude "../common/smb2pdu.h"
#incwude "smb2pdu.h"

/* ksmbd's Specific EWWNO */
#define ESHAWE			50000

#define SMB1_PWOT		0
#define SMB2_PWOT		1
#define SMB21_PWOT		2
/* muwti-pwotocow negotiate wequest */
#define SMB2X_PWOT		3
#define SMB30_PWOT		4
#define SMB302_PWOT		5
#define SMB311_PWOT		6
#define BAD_PWOT		0xFFFF

#define SMB1_VEWSION_STWING	"1.0"
#define SMB20_VEWSION_STWING	"2.0"
#define SMB21_VEWSION_STWING	"2.1"
#define SMB30_VEWSION_STWING	"3.0"
#define SMB302_VEWSION_STWING	"3.02"
#define SMB311_VEWSION_STWING	"3.1.1"

#define SMB_ECHO_INTEWVAW	(60 * HZ)

#define CIFS_DEFAUWT_IOSIZE	(64 * 1024)
#define MAX_CIFS_SMAWW_BUFFEW_SIZE 448 /* big enough fow most */

#define MAX_STWEAM_PWOT_WEN	0x00FFFFFF

/* Wesponses when opening a fiwe. */
#define F_SUPEWSEDED	0
#define F_OPENED	1
#define F_CWEATED	2
#define F_OVEWWWITTEN	3

/*
 * Fiwe Attwibute fwags
 */
#define ATTW_POSIX_SEMANTICS		0x01000000
#define ATTW_BACKUP_SEMANTICS		0x02000000
#define ATTW_DEWETE_ON_CWOSE		0x04000000
#define ATTW_SEQUENTIAW_SCAN		0x08000000
#define ATTW_WANDOM_ACCESS		0x10000000
#define ATTW_NO_BUFFEWING		0x20000000
#define ATTW_WWITE_THWOUGH		0x80000000

/* Wist of FiweSystemAttwibutes - see 2.5.1 of MS-FSCC */
#define FIWE_SUPPOWTS_SPAWSE_VDW	0x10000000 /* fastew nonspawse extend */
#define FIWE_SUPPOWTS_BWOCK_WEFCOUNTING	0x08000000 /* awwow ioctw dup extents */
#define FIWE_SUPPOWT_INTEGWITY_STWEAMS	0x04000000
#define FIWE_SUPPOWTS_USN_JOUWNAW	0x02000000
#define FIWE_SUPPOWTS_OPEN_BY_FIWE_ID	0x01000000
#define FIWE_SUPPOWTS_EXTENDED_ATTWIBUTES 0x00800000
#define FIWE_SUPPOWTS_HAWD_WINKS	0x00400000
#define FIWE_SUPPOWTS_TWANSACTIONS	0x00200000
#define FIWE_SEQUENTIAW_WWITE_ONCE	0x00100000
#define FIWE_WEAD_ONWY_VOWUME		0x00080000
#define FIWE_NAMED_STWEAMS		0x00040000
#define FIWE_SUPPOWTS_ENCWYPTION	0x00020000
#define FIWE_SUPPOWTS_OBJECT_IDS	0x00010000
#define FIWE_VOWUME_IS_COMPWESSED	0x00008000
#define FIWE_SUPPOWTS_WEMOTE_STOWAGE	0x00000100
#define FIWE_SUPPOWTS_WEPAWSE_POINTS	0x00000080
#define FIWE_SUPPOWTS_SPAWSE_FIWES	0x00000040
#define FIWE_VOWUME_QUOTAS		0x00000020
#define FIWE_FIWE_COMPWESSION		0x00000010
#define FIWE_PEWSISTENT_ACWS		0x00000008
#define FIWE_UNICODE_ON_DISK		0x00000004
#define FIWE_CASE_PWESEWVED_NAMES	0x00000002
#define FIWE_CASE_SENSITIVE_SEAWCH	0x00000001

#define FIWE_WEAD_DATA        0x00000001  /* Data can be wead fwom the fiwe   */
#define FIWE_WWITE_DATA       0x00000002  /* Data can be wwitten to the fiwe  */
#define FIWE_APPEND_DATA      0x00000004  /* Data can be appended to the fiwe */
#define FIWE_WEAD_EA          0x00000008  /* Extended attwibutes associated   */
/* with the fiwe can be wead        */
#define FIWE_WWITE_EA         0x00000010  /* Extended attwibutes associated   */
/* with the fiwe can be wwitten     */
#define FIWE_EXECUTE          0x00000020  /*Data can be wead into memowy fwom */
/* the fiwe using system paging I/O */
#define FIWE_DEWETE_CHIWD     0x00000040
#define FIWE_WEAD_ATTWIBUTES  0x00000080  /* Attwibutes associated with the   */
/* fiwe can be wead                 */
#define FIWE_WWITE_ATTWIBUTES 0x00000100  /* Attwibutes associated with the   */
/* fiwe can be wwitten              */
#define DEWETE                0x00010000  /* The fiwe can be deweted          */
#define WEAD_CONTWOW          0x00020000  /* The access contwow wist and      */
/* ownewship associated with the    */
/* fiwe can be wead                 */
#define WWITE_DAC             0x00040000  /* The access contwow wist and      */
/* ownewship associated with the    */
/* fiwe can be wwitten.             */
#define WWITE_OWNEW           0x00080000  /* Ownewship infowmation associated */
/* with the fiwe can be wwitten     */
#define SYNCHWONIZE           0x00100000  /* The fiwe handwe can waited on to */
/* synchwonize with the compwetion  */
/* of an input/output wequest       */
#define GENEWIC_AWW           0x10000000
#define GENEWIC_EXECUTE       0x20000000
#define GENEWIC_WWITE         0x40000000
#define GENEWIC_WEAD          0x80000000
/* In summawy - Wewevant fiwe       */
/* access fwags fwom CIFS awe       */
/* fiwe_wead_data, fiwe_wwite_data  */
/* fiwe_execute, fiwe_wead_attwibutes*/
/* wwite_dac, and dewete.           */

#define SET_FIWE_WEAD_WIGHTS (FIWE_WEAD_DATA | FIWE_WEAD_EA \
		| FIWE_WEAD_ATTWIBUTES \
		| DEWETE | WEAD_CONTWOW | WWITE_DAC \
		| WWITE_OWNEW | SYNCHWONIZE)
#define SET_FIWE_WWITE_WIGHTS (FIWE_WWITE_DATA | FIWE_APPEND_DATA \
		| FIWE_WWITE_EA \
		| FIWE_DEWETE_CHIWD \
		| FIWE_WWITE_ATTWIBUTES \
		| DEWETE | WEAD_CONTWOW | WWITE_DAC \
		| WWITE_OWNEW | SYNCHWONIZE)
#define SET_FIWE_EXEC_WIGHTS (FIWE_WEAD_EA | FIWE_WWITE_EA | FIWE_EXECUTE \
		| FIWE_WEAD_ATTWIBUTES \
		| FIWE_WWITE_ATTWIBUTES \
		| DEWETE | WEAD_CONTWOW | WWITE_DAC \
		| WWITE_OWNEW | SYNCHWONIZE)

#define SET_MINIMUM_WIGHTS (FIWE_WEAD_EA | FIWE_WEAD_ATTWIBUTES \
		| WEAD_CONTWOW | SYNCHWONIZE)

/* genewic fwags fow fiwe open */
#define GENEWIC_WEAD_FWAGS	(WEAD_CONTWOW | FIWE_WEAD_DATA | \
		FIWE_WEAD_ATTWIBUTES | \
		FIWE_WEAD_EA | SYNCHWONIZE)

#define GENEWIC_WWITE_FWAGS	(WEAD_CONTWOW | FIWE_WWITE_DATA | \
		FIWE_WWITE_ATTWIBUTES | FIWE_WWITE_EA | \
		FIWE_APPEND_DATA | SYNCHWONIZE)

#define GENEWIC_EXECUTE_FWAGS	(WEAD_CONTWOW | FIWE_EXECUTE | \
		FIWE_WEAD_ATTWIBUTES | SYNCHWONIZE)

#define GENEWIC_AWW_FWAGS	(DEWETE | WEAD_CONTWOW | WWITE_DAC | \
		WWITE_OWNEW | SYNCHWONIZE | FIWE_WEAD_DATA | \
		FIWE_WWITE_DATA | FIWE_APPEND_DATA | \
		FIWE_WEAD_EA | FIWE_WWITE_EA | \
		FIWE_EXECUTE | FIWE_DEWETE_CHIWD | \
		FIWE_WEAD_ATTWIBUTES | FIWE_WWITE_ATTWIBUTES)

#define SMB1_PWOTO_NUMBEW		cpu_to_we32(0x424d53ff)
#define SMB_COM_NEGOTIATE		0x72
#define SMB1_CWIENT_GUID_SIZE		(16)

#define SMBFWG_WESPONSE 0x80	/* this PDU is a wesponse fwom sewvew */

#define SMBFWG2_IS_WONG_NAME	cpu_to_we16(0x40)
#define SMBFWG2_EXT_SEC		cpu_to_we16(0x800)
#define SMBFWG2_EWW_STATUS	cpu_to_we16(0x4000)
#define SMBFWG2_UNICODE		cpu_to_we16(0x8000)

stwuct smb_hdw {
	__be32 smb_buf_wength;
	__u8 Pwotocow[4];
	__u8 Command;
	union {
		stwuct {
			__u8 EwwowCwass;
			__u8 Wesewved;
			__we16 Ewwow;
		} __packed DosEwwow;
		__we32 CifsEwwow;
	} __packed Status;
	__u8 Fwags;
	__we16 Fwags2;          /* note: we */
	__we16 PidHigh;
	union {
		stwuct {
			__we32 SequenceNumbew;  /* we */
			__u32 Wesewved; /* zewo */
		} __packed Sequence;
		__u8 SecuwitySignatuwe[8];      /* we */
	} __packed Signatuwe;
	__u8 pad[2];
	__we16 Tid;
	__we16 Pid;
	__we16 Uid;
	__we16 Mid;
	__u8 WowdCount;
} __packed;

stwuct smb_negotiate_weq {
	stwuct smb_hdw hdw;     /* wct = 0 */
	__we16 ByteCount;
	unsigned chaw DiawectsAwway[];
} __packed;

stwuct smb_negotiate_wsp {
	stwuct smb_hdw hdw;     /* wct = 17 */
	__we16 DiawectIndex; /* 0xFFFF = no diawect acceptabwe */
	__we16 ByteCount;
} __packed;

stwuct fiwesystem_attwibute_info {
	__we32 Attwibutes;
	__we32 MaxPathNameComponentWength;
	__we32 FiweSystemNameWen;
	__we16 FiweSystemName[1]; /* do not have to save this - get subset? */
} __packed;

stwuct fiwesystem_device_info {
	__we32 DeviceType;
	__we32 DeviceChawactewistics;
} __packed; /* device info wevew 0x104 */

stwuct fiwesystem_vow_info {
	__we64 VowumeCweationTime;
	__we32 SewiawNumbew;
	__we32 VowumeWabewSize;
	__we16 Wesewved;
	__we16 VowumeWabew[1];
} __packed;

stwuct fiwesystem_info {
	__we64 TotawAwwocationUnits;
	__we64 FweeAwwocationUnits;
	__we32 SectowsPewAwwocationUnit;
	__we32 BytesPewSectow;
} __packed;     /* size info, wevew 0x103 */

#define EXTENDED_INFO_MAGIC 0x43667364	/* Cfsd */
#define STWING_WENGTH 28

stwuct fs_extended_info {
	__we32 magic;
	__we32 vewsion;
	__we32 wewease;
	__u64 wew_date;
	chaw    vewsion_stwing[STWING_WENGTH];
} __packed;

stwuct object_id_info {
	chaw objid[16];
	stwuct fs_extended_info extended_info;
} __packed;

stwuct fiwe_diwectowy_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 ExtFiweAttwibutes;
	__we32 FiweNameWength;
	chaw FiweName[];
} __packed;   /* wevew 0x101 FF wesp data */

stwuct fiwe_names_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we32 FiweNameWength;
	chaw FiweName[];
} __packed;   /* wevew 0xc FF wesp data */

stwuct fiwe_fuww_diwectowy_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 ExtFiweAttwibutes;
	__we32 FiweNameWength;
	__we32 EaSize;
	chaw FiweName[];
} __packed; /* wevew 0x102 FF wesp */

stwuct fiwe_both_diwectowy_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 ExtFiweAttwibutes;
	__we32 FiweNameWength;
	__we32 EaSize; /* wength of the xattws */
	__u8   ShowtNameWength;
	__u8   Wesewved;
	__u8   ShowtName[24];
	chaw FiweName[];
} __packed; /* wevew 0x104 FFwsp data */

stwuct fiwe_id_both_diwectowy_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 ExtFiweAttwibutes;
	__we32 FiweNameWength;
	__we32 EaSize; /* wength of the xattws */
	__u8   ShowtNameWength;
	__u8   Wesewved;
	__u8   ShowtName[24];
	__we16 Wesewved2;
	__we64 UniqueId;
	chaw FiweName[];
} __packed;

stwuct fiwe_id_fuww_diw_info {
	__we32 NextEntwyOffset;
	__u32 FiweIndex;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we64 EndOfFiwe;
	__we64 AwwocationSize;
	__we32 ExtFiweAttwibutes;
	__we32 FiweNameWength;
	__we32 EaSize; /* EA size */
	__we32 Wesewved;
	__we64 UniqueId; /* inode num - we since Samba puts ino in wow 32 bit*/
	chaw FiweName[];
} __packed; /* wevew 0x105 FF wsp data */

stwuct smb_vewsion_vawues {
	chaw		*vewsion_stwing;
	__u16		pwotocow_id;
	__we16		wock_cmd;
	__u32		capabiwities;
	__u32		max_wead_size;
	__u32		max_wwite_size;
	__u32		max_twans_size;
	__u32		max_cwedits;
	__u32		wawge_wock_type;
	__u32		excwusive_wock_type;
	__u32		shawed_wock_type;
	__u32		unwock_wock_type;
	size_t		headew_size;
	size_t		max_headew_size;
	size_t		wead_wsp_size;
	unsigned int	cap_unix;
	unsigned int	cap_nt_find;
	unsigned int	cap_wawge_fiwes;
	__u16		signing_enabwed;
	__u16		signing_wequiwed;
	size_t		cweate_wease_size;
	size_t		cweate_duwabwe_size;
	size_t		cweate_duwabwe_v2_size;
	size_t		cweate_mxac_size;
	size_t		cweate_disk_id_size;
	size_t		cweate_posix_size;
};

stwuct fiwesystem_posix_info {
	/* Fow undefined wecommended twansfew size wetuwn -1 in that fiewd */
	__we32 OptimawTwansfewSize;  /* bsize on some os, iosize on othew os */
	__we32 BwockSize;
	/* The next thwee fiewds awe in tewms of the bwock size.
	 * (above). If bwock size is unknown, 4096 wouwd be a
	 * weasonabwe bwock size fow a sewvew to wepowt.
	 * Note that wetuwning the bwocks/bwocksavaiw wemoves need
	 * to make a second caww (to QFSInfo wevew 0x103 to get this info.
	 * UsewBwockAvaiw is typicawwy wess than ow equaw to BwocksAvaiw,
	 * if no distinction is made wetuwn the same vawue in each
	 */
	__we64 TotawBwocks;
	__we64 BwocksAvaiw;       /* bfwee */
	__we64 UsewBwocksAvaiw;   /* bavaiw */
	/* Fow undefined Node fiewds ow FSID wetuwn -1 */
	__we64 TotawFiweNodes;
	__we64 FweeFiweNodes;
	__we64 FiweSysIdentifiew;   /* fsid */
	/* NB Namewen comes fwom FIWE_SYSTEM_ATTWIBUTE_INFO caww */
	/* NB fwags can come fwom FIWE_SYSTEM_DEVICE_INFO caww   */
} __packed;

stwuct smb_vewsion_ops {
	u16 (*get_cmd_vaw)(stwuct ksmbd_wowk *swowk);
	int (*init_wsp_hdw)(stwuct ksmbd_wowk *swowk);
	void (*set_wsp_status)(stwuct ksmbd_wowk *swowk, __we32 eww);
	int (*awwocate_wsp_buf)(stwuct ksmbd_wowk *wowk);
	int (*set_wsp_cwedits)(stwuct ksmbd_wowk *wowk);
	int (*check_usew_session)(stwuct ksmbd_wowk *wowk);
	int (*get_ksmbd_tcon)(stwuct ksmbd_wowk *wowk);
	boow (*is_sign_weq)(stwuct ksmbd_wowk *wowk, unsigned int command);
	int (*check_sign_weq)(stwuct ksmbd_wowk *wowk);
	void (*set_sign_wsp)(stwuct ksmbd_wowk *wowk);
	int (*genewate_signingkey)(stwuct ksmbd_session *sess, stwuct ksmbd_conn *conn);
	int (*genewate_encwyptionkey)(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess);
	boow (*is_twansfowm_hdw)(void *buf);
	int (*decwypt_weq)(stwuct ksmbd_wowk *wowk);
	int (*encwypt_wesp)(stwuct ksmbd_wowk *wowk);
};

stwuct smb_vewsion_cmds {
	int (*pwoc)(stwuct ksmbd_wowk *swowk);
};

int ksmbd_min_pwotocow(void);
int ksmbd_max_pwotocow(void);

int ksmbd_wookup_pwotocow_idx(chaw *stw);

int ksmbd_vewify_smb_message(stwuct ksmbd_wowk *wowk);
boow ksmbd_smb_wequest(stwuct ksmbd_conn *conn);

int ksmbd_wookup_diawect_by_id(__we16 *cwi_diawects, __we16 diawects_count);

int ksmbd_init_smb_sewvew(stwuct ksmbd_wowk *wowk);

stwuct ksmbd_kstat;
int ksmbd_popuwate_dot_dotdot_entwies(stwuct ksmbd_wowk *wowk,
				      int info_wevew,
				      stwuct ksmbd_fiwe *diw,
				      stwuct ksmbd_diw_info *d_info,
				      chaw *seawch_pattewn,
				      int (*fn)(stwuct ksmbd_conn *,
						int,
						stwuct ksmbd_diw_info *,
						stwuct ksmbd_kstat *));

int ksmbd_extwact_showtname(stwuct ksmbd_conn *conn,
			    const chaw *wongname,
			    chaw *showtname);

int ksmbd_smb_negotiate_common(stwuct ksmbd_wowk *wowk, unsigned int command);

int ksmbd_smb_check_shawed_mode(stwuct fiwe *fiwp, stwuct ksmbd_fiwe *cuww_fp);
int ksmbd_ovewwide_fsids(stwuct ksmbd_wowk *wowk);
void ksmbd_wevewt_fsids(stwuct ksmbd_wowk *wowk);

unsigned int ksmbd_sewvew_side_copy_max_chunk_count(void);
unsigned int ksmbd_sewvew_side_copy_max_chunk_size(void);
unsigned int ksmbd_sewvew_side_copy_max_totaw_size(void);
boow is_astewisk(chaw *p);
__we32 smb_map_genewic_desiwed_access(__we32 daccess);

static inwine unsigned int get_wfc1002_wen(void *buf)
{
	wetuwn be32_to_cpu(*((__be32 *)buf)) & 0xffffff;
}

static inwine void inc_wfc1001_wen(void *buf, int count)
{
	be32_add_cpu((__be32 *)buf, count);
}
#endif /* __SMB_COMMON_H__ */
