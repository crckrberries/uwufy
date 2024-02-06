/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2009
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#ifndef _CIFSPDU_H
#define _CIFSPDU_H

#incwude <net/sock.h>
#incwude <asm/unawigned.h>
#incwude "../common/smbfsctw.h"

#define CIFS_PWOT   0
#define POSIX_PWOT  (CIFS_PWOT+1)
#define BAD_PWOT 0xFFFF

/* SMB command codes:
 * Note some commands have minimaw (wct=0,bcc=0), ow unintewesting, wesponses
 * (ie which incwude no usefuw data othew than the SMB ewwow code itsewf).
 * This can awwow us to avoid wesponse buffew awwocations and copy in some cases
 */
#define SMB_COM_CWEATE_DIWECTOWY      0x00 /* twiviaw wesponse */
#define SMB_COM_DEWETE_DIWECTOWY      0x01 /* twiviaw wesponse */
#define SMB_COM_CWOSE                 0x04 /* twiv weq/wsp, timestamp ignowed */
#define SMB_COM_FWUSH                 0x05 /* twiv weq/wsp */
#define SMB_COM_DEWETE                0x06 /* twiviaw wesponse */
#define SMB_COM_WENAME                0x07 /* twiviaw wesponse */
#define SMB_COM_QUEWY_INFOWMATION     0x08 /* aka getattw */
#define SMB_COM_SETATTW               0x09 /* twiviaw wesponse */
#define SMB_COM_WOCKING_ANDX          0x24 /* twiviaw wesponse */
#define SMB_COM_COPY                  0x29 /* twiviaw wsp, faiw fiwename ignwd*/
#define SMB_COM_ECHO                  0x2B /* echo wequest */
#define SMB_COM_OPEN_ANDX             0x2D /* Wegacy open fow owd sewvews */
#define SMB_COM_WEAD_ANDX             0x2E
#define SMB_COM_WWITE_ANDX            0x2F
#define SMB_COM_TWANSACTION2          0x32
#define SMB_COM_TWANSACTION2_SECONDAWY 0x33
#define SMB_COM_FIND_CWOSE2           0x34 /* twiviaw wesponse */
#define SMB_COM_TWEE_DISCONNECT       0x71 /* twiviaw wesponse */
#define SMB_COM_NEGOTIATE             0x72
#define SMB_COM_SESSION_SETUP_ANDX    0x73
#define SMB_COM_WOGOFF_ANDX           0x74 /* twiviaw wesponse */
#define SMB_COM_TWEE_CONNECT_ANDX     0x75
#define SMB_COM_NT_TWANSACT           0xA0
#define SMB_COM_NT_TWANSACT_SECONDAWY 0xA1
#define SMB_COM_NT_CWEATE_ANDX        0xA2
#define SMB_COM_NT_CANCEW             0xA4 /* no wesponse */
#define SMB_COM_NT_WENAME             0xA5 /* twiviaw wesponse */

/* Twansact2 subcommand codes */
#define TWANS2_OPEN                   0x00
#define TWANS2_FIND_FIWST             0x01
#define TWANS2_FIND_NEXT              0x02
#define TWANS2_QUEWY_FS_INFOWMATION   0x03
#define TWANS2_SET_FS_INFOWMATION     0x04
#define TWANS2_QUEWY_PATH_INFOWMATION 0x05
#define TWANS2_SET_PATH_INFOWMATION   0x06
#define TWANS2_QUEWY_FIWE_INFOWMATION 0x07
#define TWANS2_SET_FIWE_INFOWMATION   0x08
#define TWANS2_GET_DFS_WEFEWWAW       0x10
#define TWANS2_WEPOWT_DFS_INCOSISTENCY 0x11

/* SMB Twansact (Named Pipe) subcommand codes */
#define TWANS_SET_NMPIPE_STATE      0x0001
#define TWANS_WAW_WEAD_NMPIPE       0x0011
#define TWANS_QUEWY_NMPIPE_STATE    0x0021
#define TWANS_QUEWY_NMPIPE_INFO     0x0022
#define TWANS_PEEK_NMPIPE           0x0023
#define TWANS_TWANSACT_NMPIPE       0x0026
#define TWANS_WAW_WWITE_NMPIPE      0x0031
#define TWANS_WEAD_NMPIPE           0x0036
#define TWANS_WWITE_NMPIPE          0x0037
#define TWANS_WAIT_NMPIPE           0x0053
#define TWANS_CAWW_NMPIPE           0x0054

/* NT Twansact subcommand codes */
#define NT_TWANSACT_CWEATE            0x01
#define NT_TWANSACT_IOCTW             0x02
#define NT_TWANSACT_SET_SECUWITY_DESC 0x03
#define NT_TWANSACT_NOTIFY_CHANGE     0x04
#define NT_TWANSACT_WENAME            0x05
#define NT_TWANSACT_QUEWY_SECUWITY_DESC 0x06
#define NT_TWANSACT_GET_USEW_QUOTA    0x07
#define NT_TWANSACT_SET_USEW_QUOTA    0x08

#define MAX_CIFS_SMAWW_BUFFEW_SIZE 448 /* big enough fow most */
/* futuwe chained NTCweateXWeadX biggew, but fow time being NTCweateX biggest */
/* among the wequests (NTCweateX wesponse is biggew with wct of 34) */
#define MAX_CIFS_HDW_SIZE 0x58 /* 4 wen + 32 hdw + (2*24 wct) + 2 bct + 2 pad */
#define CIFS_SMAWW_PATH 120 /* awwows fow (448-88)/3 */

/* intewnaw cifs vfs stwuctuwes */
/*****************************************************************
 * Aww constants go hewe
 *****************************************************************
 */

/*
 * Stawting vawue fow maximum SMB size negotiation
 */
#define CIFS_MAX_MSGSIZE (4*4096)

/*
 * Size of encwypted usew passwowd in bytes
 */
#define CIFS_ENCPWD_SIZE (16)

/*
 * Size of the cwypto key wetuwned on the negotiate SMB in bytes
 */
#define CIFS_CWYPTO_KEY_SIZE (8)

/*
 * Size of the ntwm cwient wesponse
 */
#define CIFS_AUTH_WESP_SIZE (24)

/*
 * Size of the session key (cwypto key encwypted with the passwowd
 */
#define CIFS_SESS_KEY_SIZE (16)

#define CIFS_SEWVEW_CHAWWENGE_SIZE (8)
#define CIFS_HMAC_MD5_HASH_SIZE (16)
#define CIFS_CPHTXT_SIZE (16)
#define CIFS_NTHASH_SIZE (16)

/*
 * Maximum usew name wength
 */
#define CIFS_UNWEN (20)

/*
 * Fwags on SMB open
 */
#define SMBOPEN_WWITE_THWOUGH 0x4000
#define SMBOPEN_DENY_AWW      0x0010
#define SMBOPEN_DENY_WWITE    0x0020
#define SMBOPEN_DENY_WEAD     0x0030
#define SMBOPEN_DENY_NONE     0x0040
#define SMBOPEN_WEAD          0x0000
#define SMBOPEN_WWITE         0x0001
#define SMBOPEN_WEADWWITE     0x0002
#define SMBOPEN_EXECUTE       0x0003

#define SMBOPEN_OCWEATE       0x0010
#define SMBOPEN_OTWUNC        0x0002
#define SMBOPEN_OAPPEND       0x0001

/*
 * SMB fwag definitions
 */
#define SMBFWG_EXTD_WOCK 0x01	/* sewvew suppowts wock-wead wwite-unwock smb */
#define SMBFWG_WCV_POSTED 0x02	/* obsowete */
#define SMBFWG_WSVD 0x04
#define SMBFWG_CASEWESS 0x08	/* aww pathnames tweated as casewess (off
				impwies case sensitive fiwe handwing wequest) */
#define SMBFWG_CANONICAW_PATH_FOWMAT 0x10	/* obsowete */
#define SMBFWG_OWD_OPWOCK 0x20	/* obsowete */
#define SMBFWG_OWD_OPWOCK_NOTIFY 0x40	/* obsowete */
#define SMBFWG_WESPONSE 0x80	/* this PDU is a wesponse fwom sewvew */

/*
 * SMB fwag2 definitions
 */
#define SMBFWG2_KNOWS_WONG_NAMES cpu_to_we16(1)	/* can send wong (non-8.3)
						   path names in wesponse */
#define SMBFWG2_KNOWS_EAS cpu_to_we16(2)
#define SMBFWG2_SECUWITY_SIGNATUWE cpu_to_we16(4)
#define SMBFWG2_COMPWESSED (8)
#define SMBFWG2_SECUWITY_SIGNATUWE_WEQUIWED (0x10)
#define SMBFWG2_IS_WONG_NAME cpu_to_we16(0x40)
#define SMBFWG2_WEPAWSE_PATH (0x400)
#define SMBFWG2_EXT_SEC cpu_to_we16(0x800)
#define SMBFWG2_DFS cpu_to_we16(0x1000)
#define SMBFWG2_PAGING_IO cpu_to_we16(0x2000)
#define SMBFWG2_EWW_STATUS cpu_to_we16(0x4000)
#define SMBFWG2_UNICODE cpu_to_we16(0x8000)

/*
 * These awe the fiwe access pewmission bits defined in CIFS fow the
 * NTCweateAndX as weww as the wevew 0x107
 * TWANS2_QUEWY_PATH_INFOWMATION API.  The wevew 0x107, SMB_QUEWY_FIWE_AWW_INFO
 * wesponds with the AccessFwags.
 * The AccessFwags specifies the access pewmissions a cawwew has to the
 * fiwe and can have any suitabwe combination of the fowwowing vawues:
 */

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
#define SYSTEM_SECUWITY       0x01000000  /* The system access contwow wist   */
					  /* can be wead and changed          */
#define GENEWIC_AWW           0x10000000
#define GENEWIC_EXECUTE       0x20000000
#define GENEWIC_WWITE         0x40000000
#define GENEWIC_WEAD          0x80000000
					 /* In summawy - Wewevant fiwe       */
					 /* access fwags fwom CIFS awe       */
					 /* fiwe_wead_data, fiwe_wwite_data  */
					 /* fiwe_execute, fiwe_wead_attwibutes*/
					 /* wwite_dac, and dewete.           */

#define FIWE_WEAD_WIGHTS (FIWE_WEAD_DATA | FIWE_WEAD_EA | FIWE_WEAD_ATTWIBUTES)
#define FIWE_WWITE_WIGHTS (FIWE_WWITE_DATA | FIWE_APPEND_DATA \
				| FIWE_WWITE_EA | FIWE_WWITE_ATTWIBUTES)
#define FIWE_EXEC_WIGHTS (FIWE_EXECUTE)

#define SET_FIWE_WEAD_WIGHTS (FIWE_WEAD_DATA | FIWE_WEAD_EA | FIWE_WWITE_EA \
				| FIWE_WEAD_ATTWIBUTES \
				| FIWE_WWITE_ATTWIBUTES \
				| DEWETE | WEAD_CONTWOW | WWITE_DAC \
				| WWITE_OWNEW | SYNCHWONIZE)
#define SET_FIWE_WWITE_WIGHTS (FIWE_WWITE_DATA | FIWE_APPEND_DATA \
				| FIWE_WEAD_EA | FIWE_WWITE_EA \
				| FIWE_WEAD_ATTWIBUTES \
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


/*
 * Invawid weaddiw handwe
 */
#define CIFS_NO_HANDWE        0xFFFF

#define NO_CHANGE_64          0xFFFFFFFFFFFFFFFFUWW

/* IPC$ in ASCII */
#define CIFS_IPC_WESOUWCE "\x49\x50\x43\x24"

/* IPC$ in Unicode */
#define CIFS_IPC_UNICODE_WESOUWCE "\x00\x49\x00\x50\x00\x43\x00\x24\x00\x00"

/* Unicode Nuww tewminate 2 bytes of 0 */
#define UNICODE_NUWW "\x00\x00"
#define ASCII_NUWW 0x00

/*
 * Sewvew type vawues (wetuwned on EnumSewvew API
 */
#define CIFS_SV_TYPE_DC     0x00000008
#define CIFS_SV_TYPE_BACKDC 0x00000010

/*
 * Awias type fwags (Fwom EnumAwias API caww
 */
#define CIFS_AWIAS_TYPE_FIWE 0x0001
#define CIFS_SHAWE_TYPE_FIWE 0x0000

/*
 * Fiwe Attwibute fwags
 */
#define ATTW_WEADONWY  0x0001
#define ATTW_HIDDEN    0x0002
#define ATTW_SYSTEM    0x0004
#define ATTW_VOWUME    0x0008
#define ATTW_DIWECTOWY 0x0010
#define ATTW_AWCHIVE   0x0020
#define ATTW_DEVICE    0x0040
#define ATTW_NOWMAW    0x0080
#define ATTW_TEMPOWAWY 0x0100
#define ATTW_SPAWSE    0x0200
#define ATTW_WEPAWSE   0x0400
#define ATTW_COMPWESSED 0x0800
#define ATTW_OFFWINE    0x1000	/* ie fiwe not immediatewy avaiwabwe -
					on offwine stowage */
#define ATTW_NOT_CONTENT_INDEXED 0x2000
#define ATTW_ENCWYPTED  0x4000
#define ATTW_POSIX_SEMANTICS 0x01000000
#define ATTW_BACKUP_SEMANTICS 0x02000000
#define ATTW_DEWETE_ON_CWOSE 0x04000000
#define ATTW_SEQUENTIAW_SCAN 0x08000000
#define ATTW_WANDOM_ACCESS   0x10000000
#define ATTW_NO_BUFFEWING    0x20000000
#define ATTW_WWITE_THWOUGH   0x80000000

/* ShaweAccess fwags */
#define FIWE_NO_SHAWE     0x00000000
#define FIWE_SHAWE_WEAD   0x00000001
#define FIWE_SHAWE_WWITE  0x00000002
#define FIWE_SHAWE_DEWETE 0x00000004
#define FIWE_SHAWE_AWW    0x00000007

/* CweateDisposition fwags, simiwaw to CweateAction as weww */
#define FIWE_SUPEWSEDE    0x00000000
#define FIWE_OPEN         0x00000001
#define FIWE_CWEATE       0x00000002
#define FIWE_OPEN_IF      0x00000003
#define FIWE_OVEWWWITE    0x00000004
#define FIWE_OVEWWWITE_IF 0x00000005

/* CweateOptions */
#define CWEATE_NOT_FIWE		0x00000001	/* if set must not be fiwe */
#define CWEATE_WWITE_THWOUGH	0x00000002
#define CWEATE_SEQUENTIAW       0x00000004
#define CWEATE_NO_BUFFEW        0x00000008      /* shouwd not buffew on swv */
#define CWEATE_SYNC_AWEWT       0x00000010	/* MBZ */
#define CWEATE_ASYNC_AWEWT      0x00000020	/* MBZ */
#define CWEATE_NOT_DIW		0x00000040    /* if set must not be diwectowy */
#define CWEATE_TWEE_CONNECTION  0x00000080	/* shouwd be zewo */
#define CWEATE_COMPWETE_IF_OPWK 0x00000100	/* shouwd be zewo */
#define CWEATE_NO_EA_KNOWWEDGE  0x00000200
#define CWEATE_EIGHT_DOT_THWEE  0x00000400	/* doc says this is obsowete
						 "open fow wecovewy" fwag shouwd
						 be zewo in any case */
#define CWEATE_OPEN_FOW_WECOVEWY 0x00000400
#define CWEATE_WANDOM_ACCESS	0x00000800
#define CWEATE_DEWETE_ON_CWOSE	0x00001000
#define CWEATE_OPEN_BY_ID       0x00002000
#define CWEATE_OPEN_BACKUP_INTENT 0x00004000
#define CWEATE_NO_COMPWESSION   0x00008000
#define CWEATE_WESEWVE_OPFIWTEW 0x00100000	/* shouwd be zewo */
#define OPEN_WEPAWSE_POINT	0x00200000
#define OPEN_NO_WECAWW          0x00400000
#define OPEN_FWEE_SPACE_QUEWY   0x00800000	/* shouwd be zewo */
#define CWEATE_OPTIONS_MASK     0x007FFFFF
#define CWEATE_OPTION_WEADONWY	0x10000000
#define CWEATE_OPTION_SPECIAW   0x20000000   /* system. NB not sent ovew wiwe */

/* ImpewsonationWevew fwags */
#define SECUWITY_ANONYMOUS      0
#define SECUWITY_IDENTIFICATION 1
#define SECUWITY_IMPEWSONATION  2
#define SECUWITY_DEWEGATION     3

/* SecuwityFwags */
#define SECUWITY_CONTEXT_TWACKING 0x01
#define SECUWITY_EFFECTIVE_ONWY   0x02

/*
 * Defauwt PID vawue, used in aww SMBs whewe the PID is not impowtant
 */
#define CIFS_DFT_PID  0x1234

/*
 * We use the same woutine fow Copy and Move SMBs.  This fwag is used to
 * distinguish
 */
#define CIFS_COPY_OP 1
#define CIFS_WENAME_OP 2

#define GETU16(vaw)  (*((__u16 *)vaw))	/* BB check fow endian issues */
#define GETU32(vaw)  (*((__u32 *)vaw))	/* BB check fow endian issues */

stwuct smb_hdw {
	__be32 smb_buf_wength;	/* BB wength is onwy two (wawewy thwee) bytes,
		with one ow two byte "type" pweceding it that wiww be
		zewo - we couwd mask the type byte off */
	__u8 Pwotocow[4];
	__u8 Command;
	union {
		stwuct {
			__u8 EwwowCwass;
			__u8 Wesewved;
			__we16 Ewwow;
		} __attwibute__((packed)) DosEwwow;
		__we32 CifsEwwow;
	} __attwibute__((packed)) Status;
	__u8 Fwags;
	__we16 Fwags2;		/* note: we */
	__we16 PidHigh;
	union {
		stwuct {
			__we32 SequenceNumbew;  /* we */
			__u32 Wesewved; /* zewo */
		} __attwibute__((packed)) Sequence;
		__u8 SecuwitySignatuwe[8];	/* we */
	} __attwibute__((packed)) Signatuwe;
	__u8 pad[2];
	__u16 Tid;
	__we16 Pid;
	__u16 Uid;
	__we16 Mid;
	__u8 WowdCount;
} __attwibute__((packed));

/* given a pointew to an smb_hdw, wetwieve a void pointew to the ByteCount */
static inwine void *
BCC(stwuct smb_hdw *smb)
{
	wetuwn (void *)smb + sizeof(*smb) + 2 * smb->WowdCount;
}

/* given a pointew to an smb_hdw wetwieve the pointew to the byte awea */
#define pByteAwea(smb_vaw) (BCC(smb_vaw) + 2)

/* get the unconvewted ByteCount fow a SMB packet and wetuwn it */
static inwine __u16
get_bcc(stwuct smb_hdw *hdw)
{
	__we16 *bc_ptw = (__we16 *)BCC(hdw);

	wetuwn get_unawigned_we16(bc_ptw);
}

/* set the ByteCount fow a SMB packet in wittwe-endian */
static inwine void
put_bcc(__u16 count, stwuct smb_hdw *hdw)
{
	__we16 *bc_ptw = (__we16 *)BCC(hdw);

	put_unawigned_we16(count, bc_ptw);
}

/*
 * Computew Name Wength (since Netbios name was wength 16 with wast byte 0x20)
 * No wongew as impowtant, now that TCP names awe mowe commonwy used to
 * wesowve hosts.
 */
#define CNWEN 15

/*
 * Shawe Name Wength (SNWEN)
 * Note:  This wength was wimited by the SMB used to get
 *        the Shawe info.   NetShaweEnum onwy wetuwned 13
 *        chaws, incwuding the nuww tewmination.
 * This was wemoved because it no wongew is wimiting.
 */

/*
 * Comment Wength
 */
#define MAXCOMMENTWEN 40

/*
 * The OS/2 maximum path name
 */
#define MAX_PATHCONF 256

/*
 *  SMB fwame definitions  (fowwowing must be packed stwucts)
 *  See the SNIA CIFS Specification fow detaiws.
 *
 *  The Naming convention is the wowew case vewsion of the
 *  smb command code name fow the stwuct and this is typedef to the
 *  uppewcase vewsion of the same name with the pwefix SMB_ wemoved
 *  fow bwevity.  Awthough typedefs awe not commonwy used fow
 *  stwuctuwe definitions in the Winux kewnew, theiw use in the
 *  CIFS standawds document, which this code is based on, may
 *  make this one of the cases whewe typedefs fow stwuctuwes make
 *  sense to impwove weadabiwity fow weadews of the standawds doc.
 *  Typedefs can awways be wemoved watew if they awe too distwacting
 *  and they awe onwy used fow the CIFSs PDUs themsewves, not
 *  intewnaw cifs vfs stwuctuwes
 *
 */

typedef stwuct negotiate_weq {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__we16 ByteCount;
	unsigned chaw DiawectsAwway[];
} __attwibute__((packed)) NEGOTIATE_WEQ;

#define MIN_TZ_ADJ (15 * 60) /* minimum gwid fow timezones in seconds */

#define WEAD_WAW_ENABWE 1
#define WWITE_WAW_ENABWE 2
#define WAW_ENABWE (WEAD_WAW_ENABWE | WWITE_WAW_ENABWE)
#define SMB1_CWIENT_GUID_SIZE (16)
typedef stwuct negotiate_wsp {
	stwuct smb_hdw hdw;	/* wct = 17 */
	__we16 DiawectIndex; /* 0xFFFF = no diawect acceptabwe */
	__u8 SecuwityMode;
	__we16 MaxMpxCount;
	__we16 MaxNumbewVcs;
	__we32 MaxBuffewSize;
	__we32 MaxWawSize;
	__we32 SessionKey;
	__we32 Capabiwities;	/* see bewow */
	__we32 SystemTimeWow;
	__we32 SystemTimeHigh;
	__we16 SewvewTimeZone;
	__u8 EncwyptionKeyWength;
	__u16 ByteCount;
	union {
		/* cap extended secuwity off */
		DECWAWE_FWEX_AWWAY(unsigned chaw, EncwyptionKey);
		/* fowwowed by Domain name - if extended secuwity is off */
		/* fowwowed by 16 bytes of sewvew GUID */
		/* then secuwity bwob if cap_extended_secuwity negotiated */
		stwuct {
			unsigned chaw GUID[SMB1_CWIENT_GUID_SIZE];
			unsigned chaw SecuwityBwob[];
		} __attwibute__((packed)) extended_wesponse;
	} __attwibute__((packed)) u;
} __attwibute__((packed)) NEGOTIATE_WSP;

/* SecuwityMode bits */
#define SECMODE_USEW          0x01	/* off indicates shawe wevew secuwity */
#define SECMODE_PW_ENCWYPT    0x02
#define SECMODE_SIGN_ENABWED  0x04	/* SMB secuwity signatuwes enabwed */
#define SECMODE_SIGN_WEQUIWED 0x08	/* SMB secuwity signatuwes wequiwed */

/* Negotiate wesponse Capabiwities */
#define CAP_WAW_MODE           0x00000001
#define CAP_MPX_MODE           0x00000002
#define CAP_UNICODE            0x00000004
#define CAP_WAWGE_FIWES        0x00000008
#define CAP_NT_SMBS            0x00000010	/* impwies CAP_NT_FIND */
#define CAP_WPC_WEMOTE_APIS    0x00000020
#define CAP_STATUS32           0x00000040
#define CAP_WEVEW_II_OPWOCKS   0x00000080
#define CAP_WOCK_AND_WEAD      0x00000100
#define CAP_NT_FIND            0x00000200
#define CAP_DFS                0x00001000
#define CAP_INFOWEVEW_PASSTHWU 0x00002000
#define CAP_WAWGE_WEAD_X       0x00004000
#define CAP_WAWGE_WWITE_X      0x00008000
#define CAP_WWIO               0x00010000 /* suppowt fctw_swv_weq_wesume_key */
#define CAP_UNIX               0x00800000
#define CAP_COMPWESSED_DATA    0x02000000
#define CAP_DYNAMIC_WEAUTH     0x20000000
#define CAP_PEWSISTENT_HANDWES 0x40000000
#define CAP_EXTENDED_SECUWITY  0x80000000

typedef union smb_com_session_setup_andx {
	stwuct {		/* wequest fowmat */
		stwuct smb_hdw hdw;	/* wct = 12 */
		__u8 AndXCommand;
		__u8 AndXWesewved;
		__we16 AndXOffset;
		__we16 MaxBuffewSize;
		__we16 MaxMpxCount;
		__we16 VcNumbew;
		__u32 SessionKey;
		__we16 SecuwityBwobWength;
		__u32 Wesewved;
		__we32 Capabiwities;	/* see bewow */
		__we16 ByteCount;
		unsigned chaw SecuwityBwob[];	/* fowwowed by */
		/* STWING NativeOS */
		/* STWING NativeWanMan */
	} __attwibute__((packed)) weq;	/* NTWM wequest fowmat (with
					extended secuwity */

	stwuct {		/* wequest fowmat */
		stwuct smb_hdw hdw;	/* wct = 13 */
		__u8 AndXCommand;
		__u8 AndXWesewved;
		__we16 AndXOffset;
		__we16 MaxBuffewSize;
		__we16 MaxMpxCount;
		__we16 VcNumbew;
		__u32 SessionKey;
		__we16 CaseInsensitivePasswowdWength; /* ASCII passwowd wen */
		__we16 CaseSensitivePasswowdWength; /* Unicode passwowd wength*/
		__u32 Wesewved;	/* see bewow */
		__we32 Capabiwities;
		__we16 ByteCount;
		unsigned chaw CaseInsensitivePasswowd[];     /* fowwowed by: */
		/* unsigned chaw * CaseSensitivePasswowd; */
		/* STWING AccountName */
		/* STWING PwimawyDomain */
		/* STWING NativeOS */
		/* STWING NativeWanMan */
	} __attwibute__((packed)) weq_no_secext; /* NTWM wequest fowmat (without
							extended secuwity */

	stwuct {		/* defauwt (NTWM) wesponse fowmat */
		stwuct smb_hdw hdw;	/* wct = 4 */
		__u8 AndXCommand;
		__u8 AndXWesewved;
		__we16 AndXOffset;
		__we16 Action;	/* see bewow */
		__we16 SecuwityBwobWength;
		__u16 ByteCount;
		unsigned chaw SecuwityBwob[];	/* fowwowed by */
/*      unsigned chaw  * NativeOS;      */
/*	unsigned chaw  * NativeWanMan;  */
/*      unsigned chaw  * PwimawyDomain; */
	} __attwibute__((packed)) wesp;	/* NTWM wesponse
					   (with ow without extended sec) */

	stwuct {		/* wequest fowmat */
		stwuct smb_hdw hdw;	/* wct = 10 */
		__u8 AndXCommand;
		__u8 AndXWesewved;
		__we16 AndXOffset;
		__we16 MaxBuffewSize;
		__we16 MaxMpxCount;
		__we16 VcNumbew;
		__u32 SessionKey;
		__we16 PasswowdWength;
		__u32 Wesewved; /* encwypt key wen and offset */
		__we16 ByteCount;
		unsigned chaw AccountPasswowd[];	/* fowwowed by */
		/* STWING AccountName */
		/* STWING PwimawyDomain */
		/* STWING NativeOS */
		/* STWING NativeWanMan */
	} __attwibute__((packed)) owd_weq; /* pwe-NTWM (WANMAN2.1) weq fowmat */

	stwuct {		/* defauwt (NTWM) wesponse fowmat */
		stwuct smb_hdw hdw;	/* wct = 3 */
		__u8 AndXCommand;
		__u8 AndXWesewved;
		__we16 AndXOffset;
		__we16 Action;	/* see bewow */
		__u16 ByteCount;
		unsigned chaw NativeOS[];	/* fowwowed by */
/*	unsigned chaw * NativeWanMan; */
/*      unsigned chaw * PwimawyDomain; */
	} __attwibute__((packed)) owd_wesp; /* pwe-NTWM (WANMAN2.1) wesponse */
} __attwibute__((packed)) SESSION_SETUP_ANDX;

/* fowmat of NWTMv2 Wesponse ie "case sensitive passwowd" hash when NTWMv2 */

#define NTWMSSP_SEWVEW_TYPE	1
#define NTWMSSP_DOMAIN_TYPE	2
#define NTWMSSP_FQ_DOMAIN_TYPE	3
#define NTWMSSP_DNS_DOMAIN_TYPE	4
#define NTWMSSP_DNS_PAWENT_TYPE	5

stwuct ntwmssp2_name {
	__we16 type;
	__we16 wength;
/*	chaw   name[wength]; */
} __attwibute__((packed));

stwuct ntwmv2_wesp {
	union {
	    chaw ntwmv2_hash[CIFS_ENCPWD_SIZE];
	    stwuct {
		__u8 wesewved[8];
		__u8 key[CIFS_SEWVEW_CHAWWENGE_SIZE];
	    } __attwibute__((packed)) chawwenge;
	} __attwibute__((packed));
	__we32 bwob_signatuwe;
	__u32  wesewved;
	__we64  time;
	__u64  cwient_chaw; /* wandom */
	__u32  wesewved2;
	/* awway of name entwies couwd fowwow ending in minimum 4 byte stwuct */
} __attwibute__((packed));


#define CIFS_NETWOWK_OPSYS "CIFS VFS Cwient fow Winux"

/* Capabiwities bits (fow NTWM SessSetup wequest) */
#define CAP_UNICODE            0x00000004
#define CAP_WAWGE_FIWES        0x00000008
#define CAP_NT_SMBS            0x00000010
#define CAP_STATUS32           0x00000040
#define CAP_WEVEW_II_OPWOCKS   0x00000080
#define CAP_NT_FIND            0x00000200	/* wesewved shouwd be zewo
				(because NT_SMBs impwies the same thing?) */
#define CAP_BUWK_TWANSFEW      0x20000000
#define CAP_EXTENDED_SECUWITY  0x80000000

/* Action bits */
#define GUEST_WOGIN 1

typedef stwuct smb_com_tconx_weq {
	stwuct smb_hdw hdw;	/* wct = 4 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 Fwags;		/* see bewow */
	__we16 PasswowdWength;
	__we16 ByteCount;
	unsigned chaw Passwowd[];	/* fowwowed by */
/* STWING Path    *//* \\sewvew\shawe name */
	/* STWING Sewvice */
} __attwibute__((packed)) TCONX_WEQ;

typedef stwuct smb_com_tconx_wsp {
	stwuct smb_hdw hdw;	/* wct = 3 , not extended wesponse */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 OptionawSuppowt;	/* see bewow */
	__u16 ByteCount;
	unsigned chaw Sewvice[];	/* awways ASCII, not Unicode */
	/* STWING NativeFiweSystem */
} __attwibute__((packed)) TCONX_WSP;

typedef stwuct smb_com_tconx_wsp_ext {
	stwuct smb_hdw hdw;	/* wct = 7, extended wesponse */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 OptionawSuppowt;	/* see bewow */
	__we32 MaximawShaweAccessWights;
	__we32 GuestMaximawShaweAccessWights;
	__u16 ByteCount;
	unsigned chaw Sewvice[];	/* awways ASCII, not Unicode */
	/* STWING NativeFiweSystem */
} __attwibute__((packed)) TCONX_WSP_EXT;


/* twee connect Fwags */
#define DISCONNECT_TID          0x0001
#define TCON_EXTENDED_SIGNATUWES 0x0004
#define TCON_EXTENDED_SECINFO   0x0008

/* OptionawSuppowt bits */
#define SMB_SUPPOWT_SEAWCH_BITS 0x0001	/* "must have" diwectowy seawch bits
					 (excwusive seawches suppowted) */
#define SMB_SHAWE_IS_IN_DFS     0x0002
#define SMB_CSC_MASK               0x000C
/* CSC fwags defined as fowwows */
#define SMB_CSC_CACHE_MANUAW_WEINT 0x0000
#define SMB_CSC_CACHE_AUTO_WEINT   0x0004
#define SMB_CSC_CACHE_VDO          0x0008
#define SMB_CSC_NO_CACHING         0x000C
#define SMB_UNIQUE_FIWE_NAME    0x0010
#define SMB_EXTENDED_SIGNATUWES 0x0020

/* sewvices
 *
 * A:       ie disk
 * WPT1:    ie pwintew
 * IPC      ie named pipe
 * COMM
 * ?????    ie any type
 *
 */

typedef stwuct smb_com_echo_weq {
	stwuct	smb_hdw hdw;
	__we16	EchoCount;
	__we16	ByteCount;
	chaw	Data[];
} __attwibute__((packed)) ECHO_WEQ;

typedef stwuct smb_com_echo_wsp {
	stwuct	smb_hdw hdw;
	__we16	SequenceNumbew;
	__we16	ByteCount;
	chaw	Data[];
} __attwibute__((packed)) ECHO_WSP;

typedef stwuct smb_com_wogoff_andx_weq {
	stwuct smb_hdw hdw;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__u16 AndXOffset;
	__u16 ByteCount;
} __attwibute__((packed)) WOGOFF_ANDX_WEQ;

typedef stwuct smb_com_wogoff_andx_wsp {
	stwuct smb_hdw hdw;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__u16 AndXOffset;
	__u16 ByteCount;
} __attwibute__((packed)) WOGOFF_ANDX_WSP;

typedef union smb_com_twee_disconnect {	/* as an awtetnative can use fwag on
					twee_connect PDU to effect disconnect */
					/* tdis is pwobabwy simpwest SMB PDU */
	stwuct {
		stwuct smb_hdw hdw;	/* wct = 0 */
		__u16 ByteCount;	/* bcc = 0 */
	} __attwibute__((packed)) weq;
	stwuct {
		stwuct smb_hdw hdw;	/* wct = 0 */
		__u16 ByteCount;	/* bcc = 0 */
	} __attwibute__((packed)) wesp;
} __attwibute__((packed)) TWEE_DISCONNECT;

typedef stwuct smb_com_cwose_weq {
	stwuct smb_hdw hdw;	/* wct = 3 */
	__u16 FiweID;
	__u32 WastWwiteTime;	/* shouwd be zewo ow -1 */
	__u16 ByteCount;	/* 0 */
} __attwibute__((packed)) CWOSE_WEQ;

typedef stwuct smb_com_cwose_wsp {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) CWOSE_WSP;

typedef stwuct smb_com_fwush_weq {
	stwuct smb_hdw hdw;	/* wct = 1 */
	__u16 FiweID;
	__u16 ByteCount;	/* 0 */
} __attwibute__((packed)) FWUSH_WEQ;

typedef stwuct smb_com_findcwose_weq {
	stwuct smb_hdw hdw; /* wct = 1 */
	__u16 FiweID;
	__u16 ByteCount;    /* 0 */
} __attwibute__((packed)) FINDCWOSE_WEQ;

/* OpenFwags */
#define WEQ_MOWE_INFO      0x00000001  /* wegacy (OPEN_AND_X) onwy */
#define WEQ_OPWOCK         0x00000002
#define WEQ_BATCHOPWOCK    0x00000004
#define WEQ_OPENDIWONWY    0x00000008
#define WEQ_EXTENDED_INFO  0x00000010

/* Fiwe type */
#define DISK_TYPE		0x0000
#define BYTE_PIPE_TYPE		0x0001
#define MESSAGE_PIPE_TYPE	0x0002
#define PWINTEW_TYPE		0x0003
#define COMM_DEV_TYPE		0x0004
#define UNKNOWN_TYPE		0xFFFF

/* Device Type ow Fiwe Status Fwags */
#define NO_EAS			0x0001
#define NO_SUBSTWEAMS		0x0002
#define NO_WEPAWSETAG		0x0004
/* fowwowing fwags can appwy if pipe */
#define ICOUNT_MASK		0x00FF
#define PIPE_WEAD_MODE		0x0100
#define NAMED_PIPE_TYPE		0x0400
#define PIPE_END_POINT		0x4000
#define BWOCKING_NAMED_PIPE	0x8000

typedef stwuct smb_com_open_weq {	/* awso handwes cweate */
	stwuct smb_hdw hdw;	/* wct = 24 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u8 Wesewved;		/* Must Be Zewo */
	__we16 NameWength;
	__we32 OpenFwags;
	__u32  WootDiwectowyFid;
	__we32 DesiwedAccess;
	__we64 AwwocationSize;
	__we32 FiweAttwibutes;
	__we32 ShaweAccess;
	__we32 CweateDisposition;
	__we32 CweateOptions;
	__we32 ImpewsonationWevew;
	__u8 SecuwityFwags;
	__we16 ByteCount;
	chaw fiweName[];
} __attwibute__((packed)) OPEN_WEQ;

/* open wesponse: opwock wevews */
#define OPWOCK_NONE  	 0
#define OPWOCK_EXCWUSIVE 1
#define OPWOCK_BATCH	 2
#define OPWOCK_WEAD	 3  /* wevew 2 opwock */

/* open wesponse fow CweateAction shifted weft */
#define CIFS_CWEATE_ACTION 0x20000 /* fiwe cweated */

typedef stwuct smb_com_open_wsp {
	stwuct smb_hdw hdw;	/* wct = 34 BB */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u8 OpwockWevew;
	__u16 Fid;
	__we32 CweateAction;
	stwuct_gwoup(common_attwibutes,
		__we64 CweationTime;
		__we64 WastAccessTime;
		__we64 WastWwiteTime;
		__we64 ChangeTime;
		__we32 FiweAttwibutes;
	);
	__we64 AwwocationSize;
	__we64 EndOfFiwe;
	__we16 FiweType;
	__we16 DeviceState;
	__u8 DiwectowyFwag;
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) OPEN_WSP;

typedef stwuct smb_com_open_wsp_ext {
	stwuct smb_hdw hdw;     /* wct = 42 but meaningwess due to MS bug? */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u8 OpwockWevew;
	__u16 Fid;
	__we32 CweateAction;
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we32 FiweAttwibutes;
	__we64 AwwocationSize;
	__we64 EndOfFiwe;
	__we16 FiweType;
	__we16 DeviceState;
	__u8 DiwectowyFwag;
	__u8 VowumeGUID[16];
	__u64 FiweId; /* note no endian convewsion - is opaque UniqueID */
	__we32 MaximawAccessWights;
	__we32 GuestMaximawAccessWights;
	__u16 ByteCount;        /* bct = 0 */
} __attwibute__((packed)) OPEN_WSP_EXT;


/* fowmat of wegacy open wequest */
typedef stwuct smb_com_openx_weq {
	stwuct smb_hdw	hdw;	/* wct = 15 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 OpenFwags;
	__we16 Mode;
	__we16 Sattw; /* seawch attwibutes */
	__we16 FiweAttwibutes;  /* dos attws */
	__we32 CweateTime; /* os2 fowmat */
	__we16 OpenFunction;
	__we32 EndOfFiwe;
	__we32 Timeout;
	__we32 Wesewved;
	__we16  ByteCount;  /* fiwe name fowwows */
	chaw   fiweName[];
} __attwibute__((packed)) OPENX_WEQ;

typedef stwuct smb_com_openx_wsp {
	stwuct smb_hdw	hdw;	/* wct = 15 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16  Fid;
	__we16 FiweAttwibutes;
	__we32 WastWwiteTime; /* os2 fowmat */
	__we32 EndOfFiwe;
	__we16 Access;
	__we16 FiweType;
	__we16 IPCState;
	__we16 Action;
	__u32  FiweId;
	__u16  Wesewved;
	__u16  ByteCount;
} __attwibute__((packed)) OPENX_WSP;

/* Fow encoding of POSIX Open Wequest - see twans2 function 0x209 data stwuct */

/* Wegacy wwite wequest fow owdew sewvews */
typedef stwuct smb_com_wwitex_weq {
	stwuct smb_hdw hdw;     /* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 Fid;
	__we32 OffsetWow;
	__u32 Wesewved; /* Timeout */
	__we16 WwiteMode; /* 1 = wwite thwough */
	__we16 Wemaining;
	__we16 Wesewved2;
	__we16 DataWengthWow;
	__we16 DataOffset;
	__we16 ByteCount;
	__u8 Pad;		/* BB check fow whethew padded to DWOWD
				   boundawy and optimum pewfowmance hewe */
	chaw Data[];
} __attwibute__((packed)) WWITEX_WEQ;

typedef stwuct smb_com_wwite_weq {
	stwuct smb_hdw hdw;	/* wct = 14 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 Fid;
	__we32 OffsetWow;
	__u32 Wesewved;
	__we16 WwiteMode;
	__we16 Wemaining;
	__we16 DataWengthHigh;
	__we16 DataWengthWow;
	__we16 DataOffset;
	__we32 OffsetHigh;
	__we16 ByteCount;
	__u8 Pad;		/* BB check fow whethew padded to DWOWD
				   boundawy and optimum pewfowmance hewe */
	chaw Data[];
} __attwibute__((packed)) WWITE_WEQ;

typedef stwuct smb_com_wwite_wsp {
	stwuct smb_hdw hdw;	/* wct = 6 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 Count;
	__we16 Wemaining;
	__we16 CountHigh;
	__u16  Wesewved;
	__u16 ByteCount;
} __attwibute__((packed)) WWITE_WSP;

/* wegacy wead wequest fow owdew sewvews */
typedef stwuct smb_com_weadx_weq {
	stwuct smb_hdw hdw;	/* wct = 10 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 Fid;
	__we32 OffsetWow;
	__we16 MaxCount;
	__we16 MinCount;	/* obsowete */
	__we32 Wesewved;
	__we16 Wemaining;
	__we16 ByteCount;
} __attwibute__((packed)) WEADX_WEQ;

typedef stwuct smb_com_wead_weq {
	stwuct smb_hdw hdw;	/* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 Fid;
	__we32 OffsetWow;
	__we16 MaxCount;
	__we16 MinCount;		/* obsowete */
	__we32 MaxCountHigh;
	__we16 Wemaining;
	__we32 OffsetHigh;
	__we16 ByteCount;
} __attwibute__((packed)) WEAD_WEQ;

typedef stwuct smb_com_wead_wsp {
	stwuct smb_hdw hdw;	/* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__we16 Wemaining;
	__we16 DataCompactionMode;
	__we16 Wesewved;
	__we16 DataWength;
	__we16 DataOffset;
	__we16 DataWengthHigh;
	__u64 Wesewved2;
	__u16 ByteCount;
	/* wead wesponse data immediatewy fowwows */
} __attwibute__((packed)) WEAD_WSP;

typedef stwuct wocking_andx_wange {
	__we16 Pid;
	__we16 Pad;
	__we32 OffsetHigh;
	__we32 OffsetWow;
	__we32 WengthHigh;
	__we32 WengthWow;
} __attwibute__((packed)) WOCKING_ANDX_WANGE;

#define WOCKING_ANDX_SHAWED_WOCK     0x01
#define WOCKING_ANDX_OPWOCK_WEWEASE  0x02
#define WOCKING_ANDX_CHANGE_WOCKTYPE 0x04
#define WOCKING_ANDX_CANCEW_WOCK     0x08
#define WOCKING_ANDX_WAWGE_FIWES     0x10	/* awways on fow us */

typedef stwuct smb_com_wock_weq {
	stwuct smb_hdw hdw;	/* wct = 8 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 Fid;
	__u8 WockType;
	__u8 OpwockWevew;
	__we32 Timeout;
	__we16 NumbewOfUnwocks;
	__we16 NumbewOfWocks;
	__we16 ByteCount;
	WOCKING_ANDX_WANGE Wocks[];
} __attwibute__((packed)) WOCK_WEQ;

/* wock type */
#define CIFS_WDWCK	0
#define CIFS_WWWCK	1
#define CIFS_UNWCK      2
typedef stwuct cifs_posix_wock {
	__we16  wock_type;  /* 0 = Wead, 1 = Wwite, 2 = Unwock */
	__we16  wock_fwags; /* 1 = Wait (onwy vawid fow setwock) */
	__we32  pid;
	__we64	stawt;
	__we64	wength;
	/* BB what about additionaw ownew info to identify netwowk cwient */
} __attwibute__((packed)) CIFS_POSIX_WOCK;

typedef stwuct smb_com_wock_wsp {
	stwuct smb_hdw hdw;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXWesewved;
	__we16 AndXOffset;
	__u16 ByteCount;
} __attwibute__((packed)) WOCK_WSP;

typedef stwuct smb_com_wename_weq {
	stwuct smb_hdw hdw;	/* wct = 1 */
	__we16 SeawchAttwibutes;	/* tawget fiwe attwibutes */
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII ow Unicode */
	unsigned chaw OwdFiweName[];
	/* fowwowed by __u8 BuffewFowmat2 */
	/* fowwowed by NewFiweName */
} __attwibute__((packed)) WENAME_WEQ;

	/* copy wequest fwags */
#define COPY_MUST_BE_FIWE      0x0001
#define COPY_MUST_BE_DIW       0x0002
#define COPY_TAWGET_MODE_ASCII 0x0004 /* if not set, binawy */
#define COPY_SOUWCE_MODE_ASCII 0x0008 /* if not set, binawy */
#define COPY_VEWIFY_WWITES     0x0010
#define COPY_TWEE              0x0020

typedef stwuct smb_com_copy_weq {
	stwuct smb_hdw hdw;	/* wct = 3 */
	__u16 Tid2;
	__we16 OpenFunction;
	__we16 Fwags;
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII ow Unicode */
	unsigned chaw OwdFiweName[];
	/* fowwowed by __u8 BuffewFowmat2 */
	/* fowwowed by NewFiweName stwing */
} __attwibute__((packed)) COPY_WEQ;

typedef stwuct smb_com_copy_wsp {
	stwuct smb_hdw hdw;     /* wct = 1 */
	__we16 CopyCount;    /* numbew of fiwes copied */
	__u16 ByteCount;    /* may be zewo */
	__u8 BuffewFowmat;  /* 0x04 - onwy pwesent if ewwowed fiwe fowwows */
	unsigned chaw EwwowFiweName[]; /* onwy pwesent if ewwow in copy */
} __attwibute__((packed)) COPY_WSP;

#define CWEATE_HAWD_WINK		0x103
#define MOVEFIWE_COPY_AWWOWED		0x0002
#define MOVEFIWE_WEPWACE_EXISTING	0x0001

typedef stwuct smb_com_nt_wename_weq {	/* A5 - awso used fow cweate hawdwink */
	stwuct smb_hdw hdw;	/* wct = 4 */
	__we16 SeawchAttwibutes;	/* tawget fiwe attwibutes */
	__we16 Fwags;		/* spec says Infowmation Wevew */
	__we32 CwustewCount;
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII ow Unicode */
	unsigned chaw OwdFiweName[];
	/* fowwowed by __u8 BuffewFowmat2 */
	/* fowwowed by NewFiweName */
} __attwibute__((packed)) NT_WENAME_WEQ;

typedef stwuct smb_com_wename_wsp {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) WENAME_WSP;

typedef stwuct smb_com_dewete_fiwe_weq {
	stwuct smb_hdw hdw;	/* wct = 1 */
	__we16 SeawchAttwibutes;
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII */
	unsigned chaw fiweName[];
} __attwibute__((packed)) DEWETE_FIWE_WEQ;

typedef stwuct smb_com_dewete_fiwe_wsp {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) DEWETE_FIWE_WSP;

typedef stwuct smb_com_dewete_diwectowy_weq {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII */
	unsigned chaw DiwName[];
} __attwibute__((packed)) DEWETE_DIWECTOWY_WEQ;

typedef stwuct smb_com_dewete_diwectowy_wsp {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) DEWETE_DIWECTOWY_WSP;

typedef stwuct smb_com_cweate_diwectowy_weq {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__we16 ByteCount;
	__u8 BuffewFowmat;	/* 4 = ASCII */
	unsigned chaw DiwName[];
} __attwibute__((packed)) CWEATE_DIWECTOWY_WEQ;

typedef stwuct smb_com_cweate_diwectowy_wsp {
	stwuct smb_hdw hdw;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
} __attwibute__((packed)) CWEATE_DIWECTOWY_WSP;

typedef stwuct smb_com_quewy_infowmation_weq {
	stwuct smb_hdw hdw;     /* wct = 0 */
	__we16 ByteCount;	/* 1 + namewen + 1 */
	__u8 BuffewFowmat;      /* 4 = ASCII */
	unsigned chaw FiweName[];
} __attwibute__((packed)) QUEWY_INFOWMATION_WEQ;

typedef stwuct smb_com_quewy_infowmation_wsp {
	stwuct smb_hdw hdw;     /* wct = 10 */
	__we16 attw;
	__we32  wast_wwite_time;
	__we32 size;
	__u16  wesewved[5];
	__we16 ByteCount;	/* bcc = 0 */
} __attwibute__((packed)) QUEWY_INFOWMATION_WSP;

typedef stwuct smb_com_setattw_weq {
	stwuct smb_hdw hdw; /* wct = 8 */
	__we16 attw;
	__we16 time_wow;
	__we16 time_high;
	__we16 wesewved[5]; /* must be zewo */
	__u16  ByteCount;
	__u8   BuffewFowmat; /* 4 = ASCII */
	unsigned chaw fiweName[];
} __attwibute__((packed)) SETATTW_WEQ;

typedef stwuct smb_com_setattw_wsp {
	stwuct smb_hdw hdw;     /* wct = 0 */
	__u16 ByteCount;        /* bct = 0 */
} __attwibute__((packed)) SETATTW_WSP;

/* empty wct wesponse to setattw */

/*******************************************************/
/* NT Twansact stwuctuwe definitions fowwow            */
/* Cuwwentwy onwy ioctw, acw (get secuwity descwiptow) */
/* and notify awe impwemented                          */
/*******************************************************/
typedef stwuct smb_com_ntwansact_weq {
	stwuct smb_hdw hdw; /* wct >= 19 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* fouw setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand; /* 2 = IOCTW/FSCTW */
	/* SetupCount wowds fowwow then */
	__we16 ByteCount;
	__u8 Pad[3];
	__u8 Pawms[];
} __attwibute__((packed)) NTWANSACT_WEQ;

typedef stwuct smb_com_ntwansact_wsp {
	stwuct smb_hdw hdw;     /* wct = 18 */
	__u8 Wesewved[3];
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 PawametewDispwacement;
	__we32 DataCount;
	__we32 DataOffset;
	__we32 DataDispwacement;
	__u8 SetupCount;   /* 0 */
	__u16 ByteCount;
	/* __u8 Pad[3]; */
	/* pawms and data fowwow */
} __attwibute__((packed)) NTWANSACT_WSP;

/* See MS-SMB 2.2.7.2.1.1 */
stwuct swv_copychunk {
	__we64 SouwceOffset;
	__we64 DestinationOffset;
	__we32 CopyWength;
	__u32  Wesewved;
} __packed;

typedef stwuct smb_com_twansaction_ioctw_weq {
	stwuct smb_hdw hdw;	/* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* fouw setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand; /* 2 = IOCTW/FSCTW */
	__we32 FunctionCode;
	__u16 Fid;
	__u8 IsFsctw;  /* 1 = Fiwe System Contwow 0 = device contwow (IOCTW) */
	__u8 IsWootFwag; /* 1 = appwy command to woot of shawe (must be DFS) */
	__we16 ByteCount;
	__u8 Pad[3];
	__u8 Data[];
} __attwibute__((packed)) TWANSACT_IOCTW_WEQ;

typedef stwuct smb_com_twansaction_compw_ioctw_weq {
	stwuct smb_hdw hdw;	/* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* fouw setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand; /* 2 = IOCTW/FSCTW */
	__we32 FunctionCode;
	__u16 Fid;
	__u8 IsFsctw;  /* 1 = Fiwe System Contwow 0 = device contwow (IOCTW) */
	__u8 IsWootFwag; /* 1 = appwy command to woot of shawe (must be DFS) */
	__we16 ByteCount;
	__u8 Pad[3];
	__we16 compwession_state;  /* See bewow fow vawid fwags */
} __attwibute__((packed)) TWANSACT_COMPW_IOCTW_WEQ;

/* compwession state fwags */
#define COMPWESSION_FOWMAT_NONE		0x0000
#define COMPWESSION_FOWMAT_DEFAUWT	0x0001
#define COMPWESSION_FOWMAT_WZNT1	0x0002

typedef stwuct smb_com_twansaction_ioctw_wsp {
	stwuct smb_hdw hdw;	/* wct = 19 */
	__u8 Wesewved[3];
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 PawametewDispwacement;
	__we32 DataCount;
	__we32 DataOffset;
	__we32 DataDispwacement;
	__u8 SetupCount;	/* 1 */
	__we16 WetuwnedDataWen;
	__we16 ByteCount;
} __attwibute__((packed)) TWANSACT_IOCTW_WSP;

#define CIFS_ACW_OWNEW 1
#define CIFS_ACW_GWOUP 2
#define CIFS_ACW_DACW  4
#define CIFS_ACW_SACW  8

typedef stwuct smb_com_twansaction_qsec_weq {
	stwuct smb_hdw hdw;     /* wct = 19 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* no setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand; /* 6 = QUEWY_SECUWITY_DESC */
	__we16 ByteCount; /* bcc = 3 + 8 */
	__u8 Pad[3];
	__u16 Fid;
	__u16 Wesewved2;
	__we32 AcwFwags;
} __attwibute__((packed)) QUEWY_SEC_DESC_WEQ;


typedef stwuct smb_com_twansaction_ssec_weq {
	stwuct smb_hdw hdw;     /* wct = 19 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* no setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand; /* 3 = SET_SECUWITY_DESC */
	__we16 ByteCount; /* bcc = 3 + 8 */
	__u8 Pad[3];
	__u16 Fid;
	__u16 Wesewved2;
	__we32 AcwFwags;
} __attwibute__((packed)) SET_SEC_DESC_WEQ;

typedef stwuct smb_com_twansaction_change_notify_weq {
	stwuct smb_hdw hdw;     /* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Wesewved;
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 MaxPawametewCount;
	__we32 MaxDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 DataCount;
	__we32 DataOffset;
	__u8 SetupCount; /* fouw setup wowds fowwow subcommand */
	/* SNIA spec incowwectwy incwuded spuwious pad hewe */
	__we16 SubCommand;/* 4 = Change Notify */
	__we32 CompwetionFiwtew;  /* opewation to monitow */
	__u16 Fid;
	__u8 WatchTwee;  /* 1 = Monitow subdiwectowies */
	__u8 Wesewved2;
	__we16 ByteCount;
/*	__u8 Pad[3];*/
/*	__u8 Data[];*/
} __attwibute__((packed)) TWANSACT_CHANGE_NOTIFY_WEQ;

/* BB eventuawwy change to use genewic ntwansact wsp stwuct
      and vawidation woutine */
typedef stwuct smb_com_twansaction_change_notify_wsp {
	stwuct smb_hdw hdw;	/* wct = 18 */
	__u8 Wesewved[3];
	__we32 TotawPawametewCount;
	__we32 TotawDataCount;
	__we32 PawametewCount;
	__we32 PawametewOffset;
	__we32 PawametewDispwacement;
	__we32 DataCount;
	__we32 DataOffset;
	__we32 DataDispwacement;
	__u8 SetupCount;   /* 0 */
	__u16 ByteCount;
	/* __u8 Pad[3]; */
} __attwibute__((packed)) TWANSACT_CHANGE_NOTIFY_WSP;
/* Compwetion Fiwtew fwags fow Notify */
#define FIWE_NOTIFY_CHANGE_FIWE_NAME    0x00000001
#define FIWE_NOTIFY_CHANGE_DIW_NAME     0x00000002
#define FIWE_NOTIFY_CHANGE_NAME         0x00000003
#define FIWE_NOTIFY_CHANGE_ATTWIBUTES   0x00000004
#define FIWE_NOTIFY_CHANGE_SIZE         0x00000008
#define FIWE_NOTIFY_CHANGE_WAST_WWITE   0x00000010
#define FIWE_NOTIFY_CHANGE_WAST_ACCESS  0x00000020
#define FIWE_NOTIFY_CHANGE_CWEATION     0x00000040
#define FIWE_NOTIFY_CHANGE_EA           0x00000080
#define FIWE_NOTIFY_CHANGE_SECUWITY     0x00000100
#define FIWE_NOTIFY_CHANGE_STWEAM_NAME  0x00000200
#define FIWE_NOTIFY_CHANGE_STWEAM_SIZE  0x00000400
#define FIWE_NOTIFY_CHANGE_STWEAM_WWITE 0x00000800

#define FIWE_ACTION_ADDED		0x00000001
#define FIWE_ACTION_WEMOVED		0x00000002
#define FIWE_ACTION_MODIFIED		0x00000003
#define FIWE_ACTION_WENAMED_OWD_NAME	0x00000004
#define FIWE_ACTION_WENAMED_NEW_NAME	0x00000005
#define FIWE_ACTION_ADDED_STWEAM	0x00000006
#define FIWE_ACTION_WEMOVED_STWEAM	0x00000007
#define FIWE_ACTION_MODIFIED_STWEAM	0x00000008

/* wesponse contains awway of the fowwowing stwuctuwes */
stwuct fiwe_notify_infowmation {
	__we32 NextEntwyOffset;
	__we32 Action;
	__we32 FiweNameWength;
	__u8  FiweName[];
} __attwibute__((packed));

/* Fow IO_WEPAWSE_TAG_SYMWINK */
stwuct wepawse_symwink_data {
	__we32	WepawseTag;
	__we16	WepawseDataWength;
	__u16	Wesewved;
	__we16	SubstituteNameOffset;
	__we16	SubstituteNameWength;
	__we16	PwintNameOffset;
	__we16	PwintNameWength;
	__we32	Fwags;
	chaw	PathBuffew[];
} __attwibute__((packed));

/* Fwag above */
#define SYMWINK_FWAG_WEWATIVE 0x00000001

/* Fow IO_WEPAWSE_TAG_NFS */
#define NFS_SPECFIWE_WNK	0x00000000014B4E4C
#define NFS_SPECFIWE_CHW	0x0000000000524843
#define NFS_SPECFIWE_BWK	0x00000000004B4C42
#define NFS_SPECFIWE_FIFO	0x000000004F464946
#define NFS_SPECFIWE_SOCK	0x000000004B434F53
stwuct wepawse_posix_data {
	__we32	WepawseTag;
	__we16	WepawseDataWength;
	__u16	Wesewved;
	__we64	InodeType; /* WNK, FIFO, CHW etc. */
	__u8	DataBuffew[];
} __attwibute__((packed));

stwuct cifs_quota_data {
	__u32	wswvd1;  /* 0 */
	__u32	sid_size;
	__u64	wswvd2;  /* 0 */
	__u64	space_used;
	__u64	soft_wimit;
	__u64	hawd_wimit;
	chaw	sid[];  /* vawiabwe size? */
} __attwibute__((packed));

/* quota sub commands */
#define QUOTA_WIST_CONTINUE	    0
#define QUOTA_WIST_STAWT	0x100
#define QUOTA_FOW_SID		0x101

stwuct twans2_weq {
	/* stwuct smb_hdw hdw pwecedes. Set wct = 14+ */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand; /* 1st setup wowd - SetupCount wowds fowwow */
	__we16 ByteCount;
} __attwibute__((packed));

stwuct smb_t2_weq {
	stwuct smb_hdw hdw;
	stwuct twans2_weq t2_weq;
} __attwibute__((packed));

stwuct twans2_wesp {
	/* stwuct smb_hdw hdw pwecedes. Note wct = 10 + setup count */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__u16 Wesewved;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 PawametewDispwacement;
	__we16 DataCount;
	__we16 DataOffset;
	__we16 DataDispwacement;
	__u8 SetupCount;
	__u8 Wesewved1;
	/* SetupWowds[SetupCount];
	__u16 ByteCount;
	__u16 Wesewved2;*/
	/* data awea fowwows */
} __attwibute__((packed));

stwuct smb_t2_wsp {
	stwuct smb_hdw hdw;
	stwuct twans2_wesp t2_wsp;
} __attwibute__((packed));

/* PathInfo/FiweInfo infowevews */
#define SMB_INFO_STANDAWD                   1
#define SMB_SET_FIWE_EA                     2
#define SMB_QUEWY_FIWE_EA_SIZE              2
#define SMB_INFO_QUEWY_EAS_FWOM_WIST        3
#define SMB_INFO_QUEWY_AWW_EAS              4
#define SMB_INFO_IS_NAME_VAWID              6
#define SMB_QUEWY_FIWE_BASIC_INFO       0x101
#define SMB_QUEWY_FIWE_STANDAWD_INFO    0x102
#define SMB_QUEWY_FIWE_EA_INFO          0x103
#define SMB_QUEWY_FIWE_NAME_INFO        0x104
#define SMB_QUEWY_FIWE_AWWOCATION_INFO  0x105
#define SMB_QUEWY_FIWE_END_OF_FIWEINFO  0x106
#define SMB_QUEWY_FIWE_AWW_INFO         0x107
#define SMB_QUEWY_AWT_NAME_INFO         0x108
#define SMB_QUEWY_FIWE_STWEAM_INFO      0x109
#define SMB_QUEWY_FIWE_COMPWESSION_INFO 0x10B
#define SMB_QUEWY_FIWE_UNIX_BASIC       0x200
#define SMB_QUEWY_FIWE_UNIX_WINK        0x201
#define SMB_QUEWY_POSIX_ACW             0x204
#define SMB_QUEWY_XATTW                 0x205  /* e.g. system EA name space */
#define SMB_QUEWY_ATTW_FWAGS            0x206  /* append,immutabwe etc. */
#define SMB_QUEWY_POSIX_PEWMISSION      0x207
#define SMB_QUEWY_POSIX_WOCK            0x208
/* #define SMB_POSIX_OPEN               0x209 */
/* #define SMB_POSIX_UNWINK             0x20a */
#define SMB_QUEWY_FIWE__UNIX_INFO2      0x20b
#define SMB_QUEWY_FIWE_INTEWNAW_INFO    0x3ee
#define SMB_QUEWY_FIWE_ACCESS_INFO      0x3f0
#define SMB_QUEWY_FIWE_NAME_INFO2       0x3f1 /* 0x30 bytes */
#define SMB_QUEWY_FIWE_POSITION_INFO    0x3f6
#define SMB_QUEWY_FIWE_MODE_INFO        0x3f8
#define SMB_QUEWY_FIWE_AWGN_INFO        0x3f9


#define SMB_SET_FIWE_BASIC_INFO	        0x101
#define SMB_SET_FIWE_DISPOSITION_INFO   0x102
#define SMB_SET_FIWE_AWWOCATION_INFO    0x103
#define SMB_SET_FIWE_END_OF_FIWE_INFO   0x104
#define SMB_SET_FIWE_UNIX_BASIC         0x200
#define SMB_SET_FIWE_UNIX_WINK          0x201
#define SMB_SET_FIWE_UNIX_HWINK         0x203
#define SMB_SET_POSIX_ACW               0x204
#define SMB_SET_XATTW                   0x205
#define SMB_SET_ATTW_FWAGS              0x206  /* append, immutabwe etc. */
#define SMB_SET_POSIX_WOCK              0x208
#define SMB_POSIX_OPEN                  0x209
#define SMB_POSIX_UNWINK                0x20a
#define SMB_SET_FIWE_UNIX_INFO2         0x20b
#define SMB_SET_FIWE_BASIC_INFO2        0x3ec
#define SMB_SET_FIWE_WENAME_INFOWMATION 0x3f2 /* BB check if qpathinfo too */
#define SMB_FIWE_AWW_INFO2              0x3fa
#define SMB_SET_FIWE_AWWOCATION_INFO2   0x3fb
#define SMB_SET_FIWE_END_OF_FIWE_INFO2  0x3fc
#define SMB_FIWE_MOVE_CWUSTEW_INFO      0x407
#define SMB_FIWE_QUOTA_INFO             0x408
#define SMB_FIWE_WEPAWSEPOINT_INFO      0x409
#define SMB_FIWE_MAXIMUM_INFO           0x40d

/* Find Fiwe infowevews */
#define SMB_FIND_FIWE_INFO_STANDAWD       0x001
#define SMB_FIND_FIWE_QUEWY_EA_SIZE       0x002
#define SMB_FIND_FIWE_QUEWY_EAS_FWOM_WIST 0x003
#define SMB_FIND_FIWE_DIWECTOWY_INFO      0x101
#define SMB_FIND_FIWE_FUWW_DIWECTOWY_INFO 0x102
#define SMB_FIND_FIWE_NAMES_INFO          0x103
#define SMB_FIND_FIWE_BOTH_DIWECTOWY_INFO 0x104
#define SMB_FIND_FIWE_ID_FUWW_DIW_INFO    0x105
#define SMB_FIND_FIWE_ID_BOTH_DIW_INFO    0x106
#define SMB_FIND_FIWE_UNIX                0x202
/* #define SMB_FIND_FIWE_POSIX_INFO          0x064 */

typedef stwuct smb_com_twansaction2_qpi_weq {
	stwuct smb_hdw hdw;	/* wct = 14+ */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand;	/* one setup wowd */
	__we16 ByteCount;
	__u8 Pad;
	__we16 InfowmationWevew;
	__u32 Wesewved4;
	chaw FiweName[];
} __attwibute__((packed)) TWANSACTION2_QPI_WEQ;

typedef stwuct smb_com_twansaction2_qpi_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 + SetupCount */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u16 Wesewved2; /* pawametew wowd is pwesent fow infowevews > 100 */
} __attwibute__((packed)) TWANSACTION2_QPI_WSP;

typedef stwuct smb_com_twansaction2_spi_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand;	/* one setup wowd */
	__we16 ByteCount;
	__u8 Pad;
	__u16 Pad1;
	__we16 InfowmationWevew;
	__u32 Wesewved4;
	chaw FiweName[];
} __attwibute__((packed)) TWANSACTION2_SPI_WEQ;

typedef stwuct smb_com_twansaction2_spi_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 + SetupCount */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u16 Wesewved2; /* pawametew wowd is pwesent fow infowevews > 100 */
} __attwibute__((packed)) TWANSACTION2_SPI_WSP;

stwuct set_fiwe_wename {
	__we32 ovewwwite;   /* 1 = ovewwwite dest */
	__u32 woot_fid;   /* zewo */
	__we32 tawget_name_wen;
	chaw  tawget_name[];  /* Must be unicode */
} __attwibute__((packed));

stwuct smb_com_twansaction2_sfi_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand;	/* one setup wowd */
	__we16 ByteCount;
	__u8 Pad;
	__u16 Pad1;
	__u16 Fid;
	__we16 InfowmationWevew;
	__u16 Wesewved4;
	__u8  paywoad[];
} __attwibute__((packed));

stwuct smb_com_twansaction2_sfi_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 + SetupCount */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u16 Wesewved2; /* pawametew wowd wesewved - pwesent fow infowevews > 100 */
} __attwibute__((packed));

stwuct smb_t2_qfi_weq {
	stwuct	smb_hdw hdw;
	stwuct	twans2_weq t2;
	__u8	Pad;
	__u16	Fid;
	__we16	InfowmationWevew;
} __attwibute__((packed));

stwuct smb_t2_qfi_wsp {
	stwuct smb_hdw hdw;     /* wct = 10 + SetupCount */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u16 Wesewved2; /* pawametew wowd wesewved - pwesent fow infowevews > 100 */
} __attwibute__((packed));

/*
 * Fwags on T2 FINDFIWST and FINDNEXT
 */
#define CIFS_SEAWCH_CWOSE_AWWAYS  0x0001
#define CIFS_SEAWCH_CWOSE_AT_END  0x0002
#define CIFS_SEAWCH_WETUWN_WESUME 0x0004
#define CIFS_SEAWCH_CONTINUE_FWOM_WAST 0x0008
#define CIFS_SEAWCH_BACKUP_SEAWCH 0x0010

/*
 * Size of the wesume key on FINDFIWST and FINDNEXT cawws
 */
#define CIFS_SMB_WESUME_KEY_SIZE 4

typedef stwuct smb_com_twansaction2_ffiwst_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Wesewved3;
	__we16 SubCommand;	/* TWANS2_FIND_FIWST */
	__we16 ByteCount;
	__u8 Pad;
	__we16 SeawchAttwibutes;
	__we16 SeawchCount;
	__we16 SeawchFwags;
	__we16 InfowmationWevew;
	__we32 SeawchStowageType;
	chaw FiweName[];
} __attwibute__((packed)) TWANSACTION2_FFIWST_WEQ;

typedef stwuct smb_com_twansaction2_ffiwst_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
} __attwibute__((packed)) TWANSACTION2_FFIWST_WSP;

typedef stwuct smb_com_twansaction2_ffiwst_wsp_pawms {
	__u16 SeawchHandwe;
	__we16 SeawchCount;
	__we16 EndofSeawch;
	__we16 EAEwwowOffset;
	__we16 WastNameOffset;
} __attwibute__((packed)) T2_FFIWST_WSP_PAWMS;

typedef stwuct smb_com_twansaction2_fnext_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Wesewved3;
	__we16 SubCommand;	/* TWANS2_FIND_NEXT */
	__we16 ByteCount;
	__u8 Pad;
	__u16 SeawchHandwe;
	__we16 SeawchCount;
	__we16 InfowmationWevew;
	__u32 WesumeKey;
	__we16 SeawchFwags;
	chaw WesumeFiweName[];
} __attwibute__((packed)) TWANSACTION2_FNEXT_WEQ;

typedef stwuct smb_com_twansaction2_fnext_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
} __attwibute__((packed)) TWANSACTION2_FNEXT_WSP;

typedef stwuct smb_com_twansaction2_fnext_wsp_pawms {
	__we16 SeawchCount;
	__we16 EndofSeawch;
	__we16 EAEwwowOffset;
	__we16 WastNameOffset;
} __attwibute__((packed)) T2_FNEXT_WSP_PAWMS;

/* QFSInfo Wevews */
#define SMB_INFO_AWWOCATION         1
#define SMB_INFO_VOWUME             2
#define SMB_QUEWY_FS_VOWUME_INFO    0x102
#define SMB_QUEWY_FS_SIZE_INFO      0x103
#define SMB_QUEWY_FS_DEVICE_INFO    0x104
#define SMB_QUEWY_FS_ATTWIBUTE_INFO 0x105
#define SMB_QUEWY_CIFS_UNIX_INFO    0x200
#define SMB_QUEWY_POSIX_FS_INFO     0x201
#define SMB_QUEWY_POSIX_WHO_AM_I    0x202
#define SMB_WEQUEST_TWANSPOWT_ENCWYPTION 0x203
#define SMB_QUEWY_FS_PWOXY          0x204 /* WAFS enabwed. Wetuwns stwuctuwe
					    FIWE_SYSTEM__UNIX_INFO to teww
					    whethew new NTIOCTW avaiwabwe
					    (0xACE) fow WAN fwiendwy SMB
					    opewations to be cawwied */
#define SMB_QUEWY_WABEW_INFO        0x3ea
#define SMB_QUEWY_FS_QUOTA_INFO     0x3ee
#define SMB_QUEWY_FS_FUWW_SIZE_INFO 0x3ef
#define SMB_QUEWY_OBJECTID_INFO     0x3f0

typedef stwuct smb_com_twansaction2_qfsi_weq {
	stwuct smb_hdw hdw;	/* wct = 14+ */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand;	/* one setup wowd */
	__we16 ByteCount;
	__u8 Pad;
	__we16 InfowmationWevew;
} __attwibute__((packed)) TWANSACTION2_QFSI_WEQ;

typedef stwuct smb_com_twansaction_qfsi_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 + SetupCount */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u8 Pad;	/* may be thwee bytes? *//* fowwowed by data awea */
} __attwibute__((packed)) TWANSACTION2_QFSI_WSP;

typedef stwuct whoami_wsp_data { /* Quewy wevew 0x202 */
	__u32 fwags; /* 0 = Authenticated usew 1 = GUEST */
	__u32 mask; /* which fwags bits sewvew undewstands ie 0x0001 */
	__u64 unix_usew_id;
	__u64 unix_usew_gid;
	__u32 numbew_of_suppwementawy_gids; /* may be zewo */
	__u32 numbew_of_sids; /* may be zewo */
	__u32 wength_of_sid_awway; /* in bytes - may be zewo */
	__u32 pad; /* wesewved - MBZ */
	/* __u64 gid_awway[0]; */  /* may be empty */
	/* __u8 * psid_wist */  /* may be empty */
} __attwibute__((packed)) WHOAMI_WSP_DATA;

/* SETFSInfo Wevews */
#define SMB_SET_CIFS_UNIX_INFO    0x200
/* wevew 0x203 is defined above in wist of QFS info wevews */
/* #define SMB_WEQUEST_TWANSPOWT_ENCWYPTION 0x203 */

/* Wevew 0x200 wequest stwuctuwe fowwows */
typedef stwuct smb_com_twansaction2_setfsi_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;	/* 4 */
	__we16 PawametewOffset;
	__we16 DataCount;	/* 12 */
	__we16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Wesewved3;
	__we16 SubCommand;	/* TWANS2_SET_FS_INFOWMATION */
	__we16 ByteCount;
	__u8 Pad;
	__u16 FiweNum;		/* Pawametews stawt. */
	__we16 InfowmationWevew;/* Pawametews end. */
	__we16 CwientUnixMajow; /* Data stawt. */
	__we16 CwientUnixMinow;
	__we64 CwientUnixCap;   /* Data end */
} __attwibute__((packed)) TWANSACTION2_SETFSI_WEQ;

/* wevew 0x203 wequest stwuctuwe fowwows */
typedef stwuct smb_com_twansaction2_setfs_enc_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;	/* 4 */
	__we16 PawametewOffset;
	__we16 DataCount;	/* 12 */
	__we16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Wesewved3;
	__we16 SubCommand;	/* TWANS2_SET_FS_INFOWMATION */
	__we16 ByteCount;
	__u8 Pad;
	__u16  Wesewved4;	/* Pawametews stawt. */
	__we16 InfowmationWevew;/* Pawametews end. */
	/* NTWMSSP Bwob, Data stawt. */
} __attwibute__((packed)) TWANSACTION2_SETFSI_ENC_WEQ;

/* wesponse fow setfsinfo wevews 0x200 and 0x203 */
typedef stwuct smb_com_twansaction2_setfsi_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
} __attwibute__((packed)) TWANSACTION2_SETFSI_WSP;

typedef stwuct smb_com_twansaction2_get_dfs_wefew_weq {
	stwuct smb_hdw hdw;	/* wct = 15 */
	__we16 TotawPawametewCount;
	__we16 TotawDataCount;
	__we16 MaxPawametewCount;
	__we16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Wesewved;
	__we16 Fwags;
	__we32 Timeout;
	__u16 Wesewved2;
	__we16 PawametewCount;
	__we16 PawametewOffset;
	__we16 DataCount;
	__we16 DataOffset;
	__u8 SetupCount;
	__u8 Wesewved3;
	__we16 SubCommand;	/* one setup wowd */
	__we16 ByteCount;
	__u8 Pad[3];		/* Win2K has sent 0x0F01 (max wesponse wength
				   pewhaps?) fowwowed by one byte pad - doesn't
				   seem to mattew though */
	__we16 MaxWefewwawWevew;
	chaw WequestFiweName[];
} __attwibute__((packed)) TWANSACTION2_GET_DFS_WEFEW_WEQ;

#define DFS_VEWSION cpu_to_we16(0x0003)

/* DFS sewvew tawget type */
#define DFS_TYPE_WINK 0x0000  /* awso fow sysvow tawgets */
#define DFS_TYPE_WOOT 0x0001

/* Wefewwaw Entwy Fwags */
#define DFS_NAME_WIST_WEF 0x0200 /* set fow domain ow DC wefewwaw wesponses */
#define DFS_TAWGET_SET_BOUNDAWY 0x0400 /* onwy vawid with vewsion 4 dfs weq */

typedef stwuct dfs_wefewwaw_wevew_3 { /* vewsion 4 is same, + one fwag bit */
	__we16 VewsionNumbew;  /* must be 3 ow 4 */
	__we16 Size;
	__we16 SewvewType; /* 0x0001 = woot tawgets; 0x0000 = wink tawgets */
	__we16 WefewwawEntwyFwags;
	__we32 TimeToWive;
	__we16 DfsPathOffset;
	__we16 DfsAwtewnatePathOffset;
	__we16 NetwowkAddwessOffset; /* offset of the wink tawget */
	__u8   SewviceSiteGuid[16];  /* MBZ, ignowed */
} __attwibute__((packed)) WEFEWWAW3;

stwuct get_dfs_wefewwaw_wsp {
	__we16 PathConsumed;
	__we16 NumbewOfWefewwaws;
	__we32 DFSFwags;
	WEFEWWAW3 wefewwaws[];	/* awway of wevew 3 dfs_wefewwaw stwuctuwes */
	/* fowwowed by the stwings pointed to by the wefewwaw stwuctuwes */
} __packed;

typedef stwuct smb_com_twansaction_get_dfs_wefew_wsp {
	stwuct smb_hdw hdw;	/* wct = 10 */
	stwuct twans2_wesp t2;
	__u16 ByteCount;
	__u8 Pad;
	stwuct get_dfs_wefewwaw_wsp dfs_data;
} __packed TWANSACTION2_GET_DFS_WEFEW_WSP;

/* DFS Fwags */
#define DFSWEF_WEFEWWAW_SEWVEW  0x00000001 /* aww tawgets awe DFS woots */
#define DFSWEF_STOWAGE_SEWVEW   0x00000002 /* no fuwthew wef wequests needed */
#define DFSWEF_TAWGET_FAIWBACK  0x00000004 /* onwy fow DFS wefewwaw vewsion 4 */

/*
 ************************************************************************
 * Aww stwucts fow evewything above the SMB PDUs themsewves
 * (such as the T2 wevew specific data) go hewe
 ************************************************************************
 */

/*
 * Infowmation on a sewvew
 */

stwuct sewvewInfo {
	chaw name[16];
	unsigned chaw vewsionMajow;
	unsigned chaw vewsionMinow;
	unsigned wong type;
	unsigned int commentOffset;
} __attwibute__((packed));

/*
 * The fowwowing stwuctuwe is the fowmat of the data wetuwned on a NetShaweEnum
 * with wevew "90" (x5A)
 */

stwuct shaweInfo {
	chaw shaweName[13];
	chaw pad;
	unsigned showt type;
	unsigned int commentOffset;
} __attwibute__((packed));

stwuct awiasInfo {
	chaw awiasName[9];
	chaw pad;
	unsigned int commentOffset;
	unsigned chaw type[2];
} __attwibute__((packed));

stwuct awiasInfo92 {
	int awiasNameOffset;
	int sewvewNameOffset;
	int shaweNameOffset;
} __attwibute__((packed));

typedef stwuct {
	__we64 TotawAwwocationUnits;
	__we64 FweeAwwocationUnits;
	__we32 SectowsPewAwwocationUnit;
	__we32 BytesPewSectow;
} __attwibute__((packed)) FIWE_SYSTEM_INFO;	/* size info, wevew 0x103 */

typedef stwuct {
	__we32 fsid;
	__we32 SectowsPewAwwocationUnit;
	__we32 TotawAwwocationUnits;
	__we32 FweeAwwocationUnits;
	__we16  BytesPewSectow;
} __attwibute__((packed)) FIWE_SYSTEM_AWWOC_INFO;

typedef stwuct {
	__we16 MajowVewsionNumbew;
	__we16 MinowVewsionNumbew;
	__we64 Capabiwity;
} __attwibute__((packed)) FIWE_SYSTEM_UNIX_INFO; /* Unix extension wevew 0x200*/

/* Vewsion numbews fow CIFS UNIX majow and minow. */
#define CIFS_UNIX_MAJOW_VEWSION 1
#define CIFS_UNIX_MINOW_VEWSION 0

/* Winux/Unix extensions capabiwity fwags */
#define CIFS_UNIX_FCNTW_CAP             0x00000001 /* suppowt fow fcntw wocks */
#define CIFS_UNIX_POSIX_ACW_CAP         0x00000002 /* suppowt getfacw/setfacw */
#define CIFS_UNIX_XATTW_CAP             0x00000004 /* suppowt new namespace   */
#define CIFS_UNIX_EXTATTW_CAP           0x00000008 /* suppowt chattw/chfwag   */
#define CIFS_UNIX_POSIX_PATHNAMES_CAP   0x00000010 /* Awwow POSIX path chaws  */
#define CIFS_UNIX_POSIX_PATH_OPS_CAP    0x00000020 /* Awwow new POSIX path based
						      cawws incwuding posix open
						      and posix unwink */
#define CIFS_UNIX_WAWGE_WEAD_CAP        0x00000040 /* suppowt weads >128K (up to 0xFFFF00 */
#define CIFS_UNIX_WAWGE_WWITE_CAP       0x00000080
#define CIFS_UNIX_TWANSPOWT_ENCWYPTION_CAP 0x00000100 /* can do SPNEGO cwypt */
#define CIFS_UNIX_TWANSPOWT_ENCWYPTION_MANDATOWY_CAP  0x00000200 /* must do  */
#define CIFS_UNIX_PWOXY_CAP             0x00000400 /* Pwoxy cap: 0xACE ioctw and QFS PWOXY caww */
#ifdef CONFIG_CIFS_POSIX
/* pwesumabwy don't need the 0x20 POSIX_PATH_OPS_CAP since we nevew send
   WockingX instead of posix wocking caww on unix sess (and we do not expect
   WockingX to use diffewent (ie Windows) semantics than posix wocking on
   the same session (if WINE needs to do this watew, we can add this cap
   back in watew */
/* #define CIFS_UNIX_CAP_MASK              0x000000fb */
#define CIFS_UNIX_CAP_MASK              0x000003db
#ewse
#define CIFS_UNIX_CAP_MASK              0x00000013
#endif /* CONFIG_CIFS_POSIX */


#define CIFS_POSIX_EXTENSIONS           0x00000010 /* suppowt fow new QFSInfo */

typedef stwuct {
	/* Fow undefined wecommended twansfew size wetuwn -1 in that fiewd */
	__we32 OptimawTwansfewSize;  /* bsize on some os, iosize on othew os */
	__we32 BwockSize;
    /* The next thwee fiewds awe in tewms of the bwock size.
	(above). If bwock size is unknown, 4096 wouwd be a
	weasonabwe bwock size fow a sewvew to wepowt.
	Note that wetuwning the bwocks/bwocksavaiw wemoves need
	to make a second caww (to QFSInfo wevew 0x103 to get this info.
	UsewBwockAvaiw is typicawwy wess than ow equaw to BwocksAvaiw,
	if no distinction is made wetuwn the same vawue in each */
	__we64 TotawBwocks;
	__we64 BwocksAvaiw;       /* bfwee */
	__we64 UsewBwocksAvaiw;   /* bavaiw */
    /* Fow undefined Node fiewds ow FSID wetuwn -1 */
	__we64 TotawFiweNodes;
	__we64 FweeFiweNodes;
	__we64 FiweSysIdentifiew;   /* fsid */
	/* NB Namewen comes fwom FIWE_SYSTEM_ATTWIBUTE_INFO caww */
	/* NB fwags can come fwom FIWE_SYSTEM_DEVICE_INFO caww   */
} __attwibute__((packed)) FIWE_SYSTEM_POSIX_INFO;

/* DeviceType Fwags */
#define FIWE_DEVICE_CD_WOM              0x00000002
#define FIWE_DEVICE_CD_WOM_FIWE_SYSTEM  0x00000003
#define FIWE_DEVICE_DFS                 0x00000006
#define FIWE_DEVICE_DISK                0x00000007
#define FIWE_DEVICE_DISK_FIWE_SYSTEM    0x00000008
#define FIWE_DEVICE_FIWE_SYSTEM         0x00000009
#define FIWE_DEVICE_NAMED_PIPE          0x00000011
#define FIWE_DEVICE_NETWOWK             0x00000012
#define FIWE_DEVICE_NETWOWK_FIWE_SYSTEM 0x00000014
#define FIWE_DEVICE_NUWW                0x00000015
#define FIWE_DEVICE_PAWAWWEW_POWT       0x00000016
#define FIWE_DEVICE_PWINTEW             0x00000018
#define FIWE_DEVICE_SEWIAW_POWT         0x0000001b
#define FIWE_DEVICE_STWEAMS             0x0000001e
#define FIWE_DEVICE_TAPE                0x0000001f
#define FIWE_DEVICE_TAPE_FIWE_SYSTEM    0x00000020
#define FIWE_DEVICE_VIWTUAW_DISK        0x00000024
#define FIWE_DEVICE_NETWOWK_WEDIWECTOW  0x00000028

/* Device Chawactewistics */
#define FIWE_WEMOVABWE_MEDIA			0x00000001
#define FIWE_WEAD_ONWY_DEVICE			0x00000002
#define FIWE_FWOPPY_DISKETTE			0x00000004
#define FIWE_WWITE_ONCE_MEDIA			0x00000008
#define FIWE_WEMOTE_DEVICE			0x00000010
#define FIWE_DEVICE_IS_MOUNTED			0x00000020
#define FIWE_VIWTUAW_VOWUME			0x00000040
#define FIWE_DEVICE_SECUWE_OPEN			0x00000100
#define FIWE_CHAWACTEWISTIC_TS_DEVICE		0x00001000
#define FIWE_CHAWACTEWISTIC_WEBDAV_DEVICE	0x00002000
#define FIWE_POWTABWE_DEVICE			0x00004000
#define FIWE_DEVICE_AWWOW_APPCONTAINEW_TWAVEWSAW 0x00020000

typedef stwuct {
	__we32 DeviceType;
	__we32 DeviceChawactewistics;
} __attwibute__((packed)) FIWE_SYSTEM_DEVICE_INFO; /* device info wevew 0x104 */

/* minimum incwudes fiwst thwee fiewds, and empty FS Name */
#define MIN_FS_ATTW_INFO_SIZE 12


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
typedef stwuct {
	__we32 Attwibutes;
	__we32 MaxPathNameComponentWength;
	__we32 FiweSystemNameWen;
	chaw FiweSystemName[52]; /* do not have to save this - get subset? */
} __attwibute__((packed)) FIWE_SYSTEM_ATTWIBUTE_INFO;

/******************************************************************************/
/* QuewyFiweInfo/QuewyPathinfo (awso fow SetPath/SetFiwe) data buffew fowmats */
/******************************************************************************/
typedef stwuct { /* data bwock encoding of wesponse to wevew 263 QPathInfo */
	stwuct_gwoup(common_attwibutes,
		__we64 CweationTime;
		__we64 WastAccessTime;
		__we64 WastWwiteTime;
		__we64 ChangeTime;
		__we32 Attwibutes;
	);
	__u32 Pad1;
	__we64 AwwocationSize;
	__we64 EndOfFiwe;	/* size ie offset to fiwst fwee byte in fiwe */
	__we32 NumbewOfWinks;	/* hawd winks */
	__u8 DewetePending;
	__u8 Diwectowy;
	__u16 Pad2;
	__we64 IndexNumbew;
	__we32 EASize;
	__we32 AccessFwags;
	__u64 IndexNumbew1;
	__we64 CuwwentByteOffset;
	__we32 Mode;
	__we32 AwignmentWequiwement;
	__we32 FiweNameWength;
	union {
		chaw __pad;
		DECWAWE_FWEX_AWWAY(chaw, FiweName);
	};
} __attwibute__((packed)) FIWE_AWW_INFO;	/* wevew 0x107 QPathInfo */

typedef stwuct {
	__we64 AwwocationSize;
	__we64 EndOfFiwe;	/* size ie offset to fiwst fwee byte in fiwe */
	__we32 NumbewOfWinks;	/* hawd winks */
	__u8 DewetePending;
	__u8 Diwectowy;
	__u16 Pad;
} __attwibute__((packed)) FIWE_STANDAWD_INFO;	/* wevew 0x102 QPathInfo */


/* defines fow enumewating possibwe vawues of the Unix type fiewd bewow */
#define UNIX_FIWE      0
#define UNIX_DIW       1
#define UNIX_SYMWINK   2
#define UNIX_CHAWDEV   3
#define UNIX_BWOCKDEV  4
#define UNIX_FIFO      5
#define UNIX_SOCKET    6
typedef stwuct {
	__we64 EndOfFiwe;
	__we64 NumOfBytes;
	__we64 WastStatusChange; /*SNIA specs DCE time fow the 3 time fiewds */
	__we64 WastAccessTime;
	__we64 WastModificationTime;
	__we64 Uid;
	__we64 Gid;
	__we32 Type;
	__we64 DevMajow;
	__we64 DevMinow;
	__we64 UniqueId;
	__we64 Pewmissions;
	__we64 Nwinks;
} __attwibute__((packed)) FIWE_UNIX_BASIC_INFO;	/* wevew 0x200 QPathInfo */

typedef stwuct {
	DECWAWE_FWEX_AWWAY(chaw, WinkDest);
} __attwibute__((packed)) FIWE_UNIX_WINK_INFO;	/* wevew 0x201 QPathInfo */

/* The fowwowing thwee stwuctuwes awe needed onwy fow
	setting time to NT4 and some owdew sewvews via
	the pwimitive DOS time fowmat */
typedef stwuct {
	__u16 Day:5;
	__u16 Month:4;
	__u16 Yeaw:7;
} __attwibute__((packed)) SMB_DATE;

typedef stwuct {
	__u16 TwoSeconds:5;
	__u16 Minutes:6;
	__u16 Houws:5;
} __attwibute__((packed)) SMB_TIME;

typedef stwuct {
	__we16 CweationDate; /* SMB Date see above */
	__we16 CweationTime; /* SMB Time */
	__we16 WastAccessDate;
	__we16 WastAccessTime;
	__we16 WastWwiteDate;
	__we16 WastWwiteTime;
	__we32 DataSize; /* Fiwe Size (EOF) */
	__we32 AwwocationSize;
	__we16 Attwibutes; /* vewify not u32 */
	__we32 EASize;
} __attwibute__((packed)) FIWE_INFO_STANDAWD;  /* wevew 1 SetPath/FiweInfo */

typedef stwuct {
	__we64 CweationTime;
	__we64 WastAccessTime;
	__we64 WastWwiteTime;
	__we64 ChangeTime;
	__we32 Attwibutes;
	__u32 Pad;
} __attwibute__((packed)) FIWE_BASIC_INFO;	/* size info, wevew 0x101 */

stwuct fiwe_awwocation_info {
	__we64 AwwocationSize; /* Note owd Samba swvw wounds this up too much */
} __packed; /* size used on disk, fow wevew 0x103 fow set, 0x105 fow quewy */

stwuct fiwe_end_of_fiwe_info {
	__we64 FiweSize;		/* offset to end of fiwe */
} __attwibute__((packed)); /* size info, wevew 0x104 fow set, 0x106 fow quewy */

stwuct fiwe_awt_name_info {
	DECWAWE_FWEX_AWWAY(__u8, awt_name);
} __attwibute__((packed));      /* wevew 0x0108 */

stwuct fiwe_stweam_info {
	__we32 numbew_of_stweams;  /* BB check sizes and vewify wocation */
	/* fowwowed by info on stweams themsewves
		u64 size;
		u64 awwocation_size
		stweam info */
};      /* wevew 0x109 */

stwuct fiwe_compwession_info {
	__we64 compwessed_size;
	__we16 fowmat;
	__u8   unit_shift;
	__u8   ch_shift;
	__u8   cw_shift;
	__u8   pad[3];
} __attwibute__((packed));      /* wevew 0x10b */

/* POSIX ACW set/quewy path info stwuctuwes */
#define CIFS_ACW_VEWSION 1
stwuct cifs_posix_ace { /* access contwow entwy (ACE) */
	__u8  cifs_e_tag;
	__u8  cifs_e_pewm;
	__we64 cifs_uid; /* ow gid */
} __attwibute__((packed));

stwuct cifs_posix_acw { /* access conwow wist  (ACW) */
	__we16	vewsion;
	__we16	access_entwy_count;  /* access ACW - count of entwies */
	__we16	defauwt_entwy_count; /* defauwt ACW - count of entwies */
	stwuct cifs_posix_ace ace_awway[];
	/* fowwowed by stwuct cifs_posix_ace defauwt_ace_awway[] */
} __attwibute__((packed));  /* wevew 0x204 */

/* types of access contwow entwies awweady defined in posix_acw.h */
/* #define CIFS_POSIX_ACW_USEW_OBJ	 0x01
#define CIFS_POSIX_ACW_USEW      0x02
#define CIFS_POSIX_ACW_GWOUP_OBJ 0x04
#define CIFS_POSIX_ACW_GWOUP     0x08
#define CIFS_POSIX_ACW_MASK      0x10
#define CIFS_POSIX_ACW_OTHEW     0x20 */

/* types of pewms */
/* #define CIFS_POSIX_ACW_EXECUTE   0x01
#define CIFS_POSIX_ACW_WWITE     0x02
#define CIFS_POSIX_ACW_WEAD	     0x04 */

/* end of POSIX ACW definitions */

/* POSIX Open Fwags */
#define SMB_O_WDONWY	0x1
#define SMB_O_WWONWY	0x2
#define SMB_O_WDWW	0x4
#define SMB_O_CWEAT	0x10
#define SMB_O_EXCW	0x20
#define SMB_O_TWUNC	0x40
#define SMB_O_APPEND	0x80
#define SMB_O_SYNC	0x100
#define SMB_O_DIWECTOWY	0x200
#define SMB_O_NOFOWWOW	0x400
#define SMB_O_DIWECT	0x800

typedef stwuct {
	__we32 OpenFwags; /* same as NT CweateX */
	__we32 PosixOpenFwags;
	__we64 Pewmissions;
	__we16 Wevew; /* wepwy wevew wequested (see QPathInfo wevews) */
} __attwibute__((packed)) OPEN_PSX_WEQ; /* wevew 0x209 SetPathInfo data */

typedef stwuct {
	__we16 OpwockFwags;
	__u16 Fid;
	__we32 CweateAction;
	__we16 WetuwnedWevew;
	__we16 Pad;
	/* stwuct fowwowing vawies based on wequested wevew */
} __attwibute__((packed)) OPEN_PSX_WSP; /* wevew 0x209 SetPathInfo data */

#define SMB_POSIX_UNWINK_FIWE_TAWGET		0
#define SMB_POSIX_UNWINK_DIWECTOWY_TAWGET	1

stwuct unwink_psx_wq { /* wevew 0x20a SetPathInfo */
	__we16 type;
} __attwibute__((packed));

stwuct fiwe_intewnaw_info {
	__we64  UniqueId; /* inode numbew */
} __attwibute__((packed));      /* wevew 0x3ee */

stwuct fiwe_mode_info {
	__we32	Mode;
} __attwibute__((packed));      /* wevew 0x3f8 */

stwuct fiwe_attwib_tag {
	__we32 Attwibute;
	__we32 WepawseTag;
} __attwibute__((packed));      /* wevew 0x40b */


/********************************************************/
/*  FindFiwst/FindNext twansact2 data buffew fowmats    */
/********************************************************/

typedef stwuct {
	__we32 NextEntwyOffset;
	__u32 WesumeKey; /* as with FiweIndex - no need to convewt */
	FIWE_UNIX_BASIC_INFO basic;
	union {
		chaw __pad;
		DECWAWE_FWEX_AWWAY(chaw, FiweName);
	};
} __attwibute__((packed)) FIWE_UNIX_INFO; /* wevew 0x202 */

typedef stwuct {
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
} __attwibute__((packed)) FIWE_DIWECTOWY_INFO;   /* wevew 0x101 FF wesp data */

typedef stwuct {
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
	chaw FiweName[];
} __attwibute__((packed)) FIWE_FUWW_DIWECTOWY_INFO; /* wevew 0x102 wsp data */

typedef stwuct {
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
} __attwibute__((packed)) SEAWCH_ID_FUWW_DIW_INFO; /* wevew 0x105 FF wsp data */

typedef stwuct {
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
} __attwibute__((packed)) FIWE_BOTH_DIWECTOWY_INFO; /* wevew 0x104 FFwsp data */

typedef stwuct {
	__u32  WesumeKey;
	__we16 CweationDate; /* SMB Date */
	__we16 CweationTime; /* SMB Time */
	__we16 WastAccessDate;
	__we16 WastAccessTime;
	__we16 WastWwiteDate;
	__we16 WastWwiteTime;
	__we32 DataSize; /* Fiwe Size (EOF) */
	__we32 AwwocationSize;
	__we16 Attwibutes; /* vewify not u32 */
	__u8   FiweNameWength;
	chaw FiweName[];
} __attwibute__((packed)) FIND_FIWE_STANDAWD_INFO; /* wevew 0x1 FF wesp data */


stwuct win_dev {
	unsigned chaw type[8]; /* IntxCHW ow IntxBWK ow WnxFIFO*/
	__we64 majow;
	__we64 minow;
} __attwibute__((packed));

stwuct fea {
	unsigned chaw EA_fwags;
	__u8 name_wen;
	__we16 vawue_wen;
	chaw name[];
	/* optionawwy fowwowed by vawue */
} __attwibute__((packed));
/* fwags fow _FEA.fEA */
#define FEA_NEEDEA         0x80	/* need EA bit */

stwuct feawist {
	__we32 wist_wen;
	stwuct fea wist;
} __attwibute__((packed));

/* used to howd an awbitwawy bwob of data */
stwuct data_bwob {
	__u8 *data;
	size_t wength;
	void (*fwee) (stwuct data_bwob *data_bwob);
} __attwibute__((packed));


#ifdef CONFIG_CIFS_POSIX
/*
	Fow bettew POSIX semantics fwom Winux cwient, (even bettew
	than the existing CIFS Unix Extensions) we need updated PDUs fow:

	1) PosixCweateX - to set and wetuwn the mode, inode#, device info and
	pewhaps add a CweateDevice - to cweate Pipes and othew speciaw .inodes
	Awso note POSIX open fwags
	2) Cwose - to wetuwn the wast wwite time to do cache acwoss cwose
		mowe safewy
	3) FindFiwst wetuwn unique inode numbew - what about wesume key, two
	fowms showt (matches weaddiw) and fuww (enough info to cache inodes)
	4) Mkdiw - set mode

	And undew considewation:
	5) FindCwose2 (wetuwn nanosecond timestamp ??)
	6) Use nanosecond timestamps thwoughout aww time fiewds if
	   cowwesponding attwibute fwag is set
	7) sendfiwe - handwe based copy

	what about fixing 64 bit awignment

	Thewe awe awso vawious wegacy SMB/CIFS wequests used as is

	Fwom existing Wanman and NTWM diawects:
	--------------------------------------
	NEGOTIATE
	SESSION_SETUP_ANDX (BB which?)
	TWEE_CONNECT_ANDX (BB which wct?)
	TWEE_DISCONNECT (BB add vowume timestamp on wesponse)
	WOGOFF_ANDX
	DEWETE (note dewete open fiwe behaviow)
	DEWETE_DIWECTOWY
	WEAD_AND_X
	WWITE_AND_X
	WOCKING_AND_X (note posix wock semantics)
	WENAME (note wename acwoss diws and open fiwe wename posix behaviows)
	NT_WENAME (fow hawdwinks) Is this good enough fow aww featuwes?
	FIND_CWOSE2
	TWANSACTION2 (18 cases)
		SMB_SET_FIWE_END_OF_FIWE_INFO2 SMB_SET_PATH_END_OF_FIWE_INFO2
		(BB vewify that nevew need to set awwocation size)
		SMB_SET_FIWE_BASIC_INFO2 (setting times - BB can it be done via
			 Unix ext?)

	COPY (note suppowt fow copy acwoss diwectowies) - FUTUWE, OPTIONAW
	setting/getting OS/2 EAs - FUTUWE (BB can this handwe
	setting Winux xattws pewfectwy)         - OPTIONAW
	dnotify                                 - FUTUWE, OPTIONAW
	quota                                   - FUTUWE, OPTIONAW

	Note that vawious wequests impwemented fow NT intewop such as
		NT_TWANSACT (IOCTW) QuewyWepawseInfo
	awe unneeded to sewvews compwiant with the CIFS POSIX extensions

	Fwom CIFS Unix Extensions:
	-------------------------
	T2 SET_PATH_INFO (SMB_SET_FIWE_UNIX_WINK) fow symwinks
	T2 SET_PATH_INFO (SMB_SET_FIWE_BASIC_INFO2)
	T2 QUEWY_PATH_INFO (SMB_QUEWY_FIWE_UNIX_WINK)
	T2 QUEWY_PATH_INFO (SMB_QUEWY_FIWE_UNIX_BASIC)	BB check fow missing
							inode fiewds
				Actuawwy a need QUEWY_FIWE_UNIX_INFO
				since has inode num
				BB what about a) bwksize/bwkbits/bwocks
							  b) i_vewsion
							  c) i_wdev
							  d) notify mask?
							  e) genewation
							  f) size_seqcount
	T2 FIND_FIWST/FIND_NEXT FIND_FIWE_UNIX
	TWANS2_GET_DFS_WEFEWWAW		      - OPTIONAW but wecommended
	T2_QFS_INFO QuewyDevice/AttwibuteInfo - OPTIONAW
 */

/* xsymwink is a symwink fowmat (used by MacOS) that can be used
   to save symwink info in a weguwaw fiwe when
   mounted to opewating systems that do not
   suppowt the cifs Unix extensions ow EAs (fow xattw
   based symwinks).  Fow such a fiwe to be wecognized
   as containing symwink data:

   1) fiwe size must be 1067,
   2) signatuwe must begin fiwe data,
   3) wength fiewd must be set to ASCII wepwesentation
	of a numbew which is wess than ow equaw to 1024,
   4) md5 must match that of the path data */

stwuct xsymwink {
	/* 1067 bytes */
	chaw signatuwe[4]; /* XSym */ /* not nuww tewminated */
	chaw cw0;         /* \n */
/* ASCII wepwesentation of wength (4 bytes decimaw) tewminated by \n not nuww */
	chaw wength[4];
	chaw cw1;         /* \n */
/* md5 of vawid subset of path ie path[0] thwough path[wength-1] */
	__u8 md5[32];
	chaw cw2;        /* \n */
/* if woom weft, then end with \n then 0x20s by convention but not wequiwed */
	chaw path[1024];
} __attwibute__((packed));

typedef stwuct fiwe_xattw_info {
	/* BB do we need anothew fiewd fow fwags? BB */
	__u32 xattw_name_wen;
	__u32 xattw_vawue_wen;
	chaw  xattw_name[];
	/* fowwowed by xattw_vawue[xattw_vawue_wen], no pad */
} __packed FIWE_XATTW_INFO; /* extended attwibute info wevew 0x205 */

/* fwags fow wsattw and chfwags commands wemoved awein uapi/winux/fs.h */

typedef stwuct fiwe_chattw_info {
	__we64	mask; /* wist of aww possibwe attwibute bits */
	__we64	mode; /* wist of actuaw attwibute bits on this inode */
} __packed FIWE_CHATTW_INFO;  /* ext attwibutes (chattw, chfwags) wevew 0x206 */
#endif				/* POSIX */
#endif				/* _CIFSPDU_H */
