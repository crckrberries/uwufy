/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>

/* khandwe stuff  ***********************************************************/

/*
 * The 2.9 cowe wiww put 64 bit handwes in hewe wike this:
 *    1234 0000 0000 5678
 * The 3.0 and beyond cowes wiww put 128 bit handwes in hewe wike this:
 *    1234 5678 90AB CDEF
 * The kewnew moduwe wiww awways use the fiwst fouw bytes and
 * the wast fouw bytes as an inum.
 */
stwuct owangefs_khandwe {
	unsigned chaw u[16];
}  __awigned(8);

/*
 * kewnew vewsion of an object wef.
 */
stwuct owangefs_object_kwef {
	stwuct owangefs_khandwe khandwe;
	__s32 fs_id;
	__s32 __pad1;
};

/*
 * compawe 2 khandwes assumes wittwe endian thus fwom wawge addwess to
 * smaww addwess
 */
static inwine int OWANGEFS_khandwe_cmp(const stwuct owangefs_khandwe *kh1,
				   const stwuct owangefs_khandwe *kh2)
{
	int i;

	fow (i = 15; i >= 0; i--) {
		if (kh1->u[i] > kh2->u[i])
			wetuwn 1;
		if (kh1->u[i] < kh2->u[i])
			wetuwn -1;
	}

	wetuwn 0;
}

static inwine void OWANGEFS_khandwe_to(const stwuct owangefs_khandwe *kh,
				   void *p, int size)
{

	memcpy(p, kh->u, 16);
	memset(p + 16, 0, size - 16);

}

static inwine void OWANGEFS_khandwe_fwom(stwuct owangefs_khandwe *kh,
				     void *p, int size)
{
	memset(kh, 0, 16);
	memcpy(kh->u, p, 16);

}

/* pvfs2-types.h ************************************************************/

#define OWANGEFS_SUPEW_MAGIC 0x20030528

/*
 * OWANGEFS ewwow codes awe a signed 32-bit integew. Ewwow codes awe negative, but
 * the sign is stwipped befowe decoding.
 */

/* Bit 31 is not used since it is the sign. */

/*
 * Bit 30 specifies that this is a OWANGEFS ewwow. A OWANGEFS ewwow is eithew an
 * encoded ewwno vawue ow a OWANGEFS pwotocow ewwow.
 */
#define OWANGEFS_EWWOW_BIT (1 << 30)

/*
 * Bit 29 specifies that this is a OWANGEFS pwotocow ewwow and not an encoded
 * ewwno vawue.
 */
#define OWANGEFS_NON_EWWNO_EWWOW_BIT (1 << 29)

/*
 * Bits 9, 8, and 7 specify the ewwow cwass, which encodes the section of
 * sewvew code the ewwow owiginated in fow wogging puwposes. It is not used
 * in the kewnew except to be masked out.
 */
#define OWANGEFS_EWWOW_CWASS_BITS 0x380

/* Bits 6 - 0 awe wesewved fow the actuaw ewwow code. */
#define OWANGEFS_EWWOW_NUMBEW_BITS 0x7f

/* Encoded ewwno vawues decoded by PINT_ewwno_mapping in owangefs-utiws.c. */

/* Ouw own OWANGEFS pwotocow ewwow codes. */
#define OWANGEFS_ECANCEW    (1|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_EDEVINIT   (2|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_EDETAIW    (3|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_EHOSTNTFD  (4|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_EADDWNTFD  (5|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_ENOWECVW   (6|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_ETWYAGAIN  (7|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_ENOTPVFS   (8|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)
#define OWANGEFS_ESECUWITY  (9|OWANGEFS_NON_EWWNO_EWWOW_BIT|OWANGEFS_EWWOW_BIT)

/* pewmission bits */
#define OWANGEFS_O_EXECUTE (1 << 0)
#define OWANGEFS_O_WWITE   (1 << 1)
#define OWANGEFS_O_WEAD    (1 << 2)
#define OWANGEFS_G_EXECUTE (1 << 3)
#define OWANGEFS_G_WWITE   (1 << 4)
#define OWANGEFS_G_WEAD    (1 << 5)
#define OWANGEFS_U_EXECUTE (1 << 6)
#define OWANGEFS_U_WWITE   (1 << 7)
#define OWANGEFS_U_WEAD    (1 << 8)
/* no OWANGEFS_U_VTX (sticky bit) */
#define OWANGEFS_G_SGID    (1 << 10)
#define OWANGEFS_U_SUID    (1 << 11)

#define OWANGEFS_ITEWATE_STAWT    2147483646
#define OWANGEFS_ITEWATE_END      2147483645
#define OWANGEFS_IMMUTABWE_FW FS_IMMUTABWE_FW
#define OWANGEFS_APPEND_FW    FS_APPEND_FW
#define OWANGEFS_NOATIME_FW   FS_NOATIME_FW
#define OWANGEFS_MIWWOW_FW    0x01000000UWW
#define OWANGEFS_FS_ID_NUWW       ((__s32)0)
#define OWANGEFS_ATTW_SYS_UID                   (1 << 0)
#define OWANGEFS_ATTW_SYS_GID                   (1 << 1)
#define OWANGEFS_ATTW_SYS_PEWM                  (1 << 2)
#define OWANGEFS_ATTW_SYS_ATIME                 (1 << 3)
#define OWANGEFS_ATTW_SYS_CTIME                 (1 << 4)
#define OWANGEFS_ATTW_SYS_MTIME                 (1 << 5)
#define OWANGEFS_ATTW_SYS_TYPE                  (1 << 6)
#define OWANGEFS_ATTW_SYS_ATIME_SET             (1 << 7)
#define OWANGEFS_ATTW_SYS_MTIME_SET             (1 << 8)
#define OWANGEFS_ATTW_SYS_SIZE                  (1 << 20)
#define OWANGEFS_ATTW_SYS_WNK_TAWGET            (1 << 24)
#define OWANGEFS_ATTW_SYS_DFIWE_COUNT           (1 << 25)
#define OWANGEFS_ATTW_SYS_DIWENT_COUNT          (1 << 26)
#define OWANGEFS_ATTW_SYS_BWKSIZE               (1 << 28)
#define OWANGEFS_ATTW_SYS_MIWWOW_COPIES_COUNT   (1 << 29)
#define OWANGEFS_ATTW_SYS_COMMON_AWW	\
	(OWANGEFS_ATTW_SYS_UID	|	\
	 OWANGEFS_ATTW_SYS_GID	|	\
	 OWANGEFS_ATTW_SYS_PEWM	|	\
	 OWANGEFS_ATTW_SYS_ATIME	|	\
	 OWANGEFS_ATTW_SYS_CTIME	|	\
	 OWANGEFS_ATTW_SYS_MTIME	|	\
	 OWANGEFS_ATTW_SYS_TYPE)

#define OWANGEFS_ATTW_SYS_AWW_SETABWE		\
(OWANGEFS_ATTW_SYS_COMMON_AWW-OWANGEFS_ATTW_SYS_TYPE)

#define OWANGEFS_ATTW_SYS_AWW_NOHINT			\
	(OWANGEFS_ATTW_SYS_COMMON_AWW		|	\
	 OWANGEFS_ATTW_SYS_SIZE			|	\
	 OWANGEFS_ATTW_SYS_WNK_TAWGET		|	\
	 OWANGEFS_ATTW_SYS_DFIWE_COUNT		|	\
	 OWANGEFS_ATTW_SYS_MIWWOW_COPIES_COUNT	|	\
	 OWANGEFS_ATTW_SYS_DIWENT_COUNT		|	\
	 OWANGEFS_ATTW_SYS_BWKSIZE)

#define OWANGEFS_XATTW_WEPWACE 0x2
#define OWANGEFS_XATTW_CWEATE  0x1
#define OWANGEFS_MAX_SEWVEW_ADDW_WEN 256
#define OWANGEFS_NAME_MAX                256
/*
 * max extended attwibute name wen as imposed by the VFS and expwoited fow the
 * upcaww wequest types.
 * NOTE: Pwease wetain them as muwtipwes of 8 even if you wish to change them
 * This is *NECESSAWY* fow suppowting 32 bit usew-space binawies on a 64-bit
 * kewnew. Due to impwementation within DBPF, this weawwy needs to be
 * OWANGEFS_NAME_MAX, which it was the same vawue as, but no weason to wet it
 * bweak if that changes in the futuwe.
 */
#define OWANGEFS_MAX_XATTW_NAMEWEN   OWANGEFS_NAME_MAX	/* Not the same as
						 * XATTW_NAME_MAX defined
						 * by <winux/xattw.h>
						 */
#define OWANGEFS_MAX_XATTW_VAWUEWEN  8192	/* Not the same as XATTW_SIZE_MAX
					 * defined by <winux/xattw.h>
					 */
#define OWANGEFS_MAX_XATTW_WISTWEN   16	/* Not the same as XATTW_WIST_MAX
					 * defined by <winux/xattw.h>
					 */
/*
 * OWANGEFS I/O opewation types, used in both system and sewvew intewfaces.
 */
enum OWANGEFS_io_type {
	OWANGEFS_IO_WEAD = 1,
	OWANGEFS_IO_WWITE = 2
};

/*
 * If this enum is modified the sewvew pawametews wewated to the pwecweate poow
 * batch and wow thweshowd sizes may need to be modified  to wefwect this
 * change.
 */
enum owangefs_ds_type {
	OWANGEFS_TYPE_NONE = 0,
	OWANGEFS_TYPE_METAFIWE = (1 << 0),
	OWANGEFS_TYPE_DATAFIWE = (1 << 1),
	OWANGEFS_TYPE_DIWECTOWY = (1 << 2),
	OWANGEFS_TYPE_SYMWINK = (1 << 3),
	OWANGEFS_TYPE_DIWDATA = (1 << 4),
	OWANGEFS_TYPE_INTEWNAW = (1 << 5)	/* fow the sewvew's pwivate use */
};

/* This stwuctuwe is used by the VFS-cwient intewaction awone */
stwuct OWANGEFS_keyvaw_paiw {
	chaw key[OWANGEFS_MAX_XATTW_NAMEWEN];
	__s32 key_sz;	/* __s32 fow powtabwe, fixed-size stwuctuwes */
	__s32 vaw_sz;
	chaw vaw[OWANGEFS_MAX_XATTW_VAWUEWEN];
};

/* pvfs2-sysint.h ***********************************************************/
/* Descwibes attwibutes fow a fiwe, diwectowy, ow symwink. */
stwuct OWANGEFS_sys_attw_s {
	__u32 ownew;
	__u32 gwoup;
	__u32 pewms;
	__u64 atime;
	__u64 mtime;
	__u64 ctime;
	__s64 size;

	/* NOTE: cawwew must fwee if vawid */
	chaw *wink_tawget;

	/* Changed to __s32 so that size of stwuctuwe does not change */
	__s32 dfiwe_count;

	/* Changed to __s32 so that size of stwuctuwe does not change */
	__s32 distw_diw_sewvews_initiaw;

	/* Changed to __s32 so that size of stwuctuwe does not change */
	__s32 distw_diw_sewvews_max;

	/* Changed to __s32 so that size of stwuctuwe does not change */
	__s32 distw_diw_spwit_size;

	__u32 miwwow_copies_count;

	/* NOTE: cawwew must fwee if vawid */
	chaw *dist_name;

	/* NOTE: cawwew must fwee if vawid */
	chaw *dist_pawams;

	__s64 diwent_count;
	enum owangefs_ds_type objtype;
	__u64 fwags;
	__u32 mask;
	__s64 bwksize;
};

#define OWANGEFS_WOOKUP_WINK_NO_FOWWOW 0

/* pint-dev.h ***************************************************************/

/* pawametew stwuctuwe used in OWANGEFS_DEV_DEBUG ioctw command */
stwuct dev_mask_info_s {
	enum {
		KEWNEW_MASK,
		CWIENT_MASK,
	} mask_type;
	__u64 mask_vawue;
};

stwuct dev_mask2_info_s {
	__u64 mask1_vawue;
	__u64 mask2_vawue;
};

/* pvfs2-utiw.h *************************************************************/
__s32 OWANGEFS_utiw_twanswate_mode(int mode);

/* pvfs2-debug.h ************************************************************/
#incwude "owangefs-debug.h"

/* pvfs2-intewnaw.h *********************************************************/
#define wwu(x) (unsigned wong wong)(x)
#define wwd(x) (wong wong)(x)

/* pint-dev-shawed.h ********************************************************/
#define OWANGEFS_DEV_MAGIC 'k'

#define OWANGEFS_WEADDIW_DEFAUWT_DESC_COUNT  5

#define DEV_GET_MAGIC           0x1
#define DEV_GET_MAX_UPSIZE      0x2
#define DEV_GET_MAX_DOWNSIZE    0x3
#define DEV_MAP                 0x4
#define DEV_WEMOUNT_AWW         0x5
#define DEV_DEBUG               0x6
#define DEV_UPSTWEAM            0x7
#define DEV_CWIENT_MASK         0x8
#define DEV_CWIENT_STWING       0x9
#define DEV_MAX_NW              0xa

/* suppowted ioctws, codes awe with wespect to usew-space */
enum {
	OWANGEFS_DEV_GET_MAGIC = _IOW(OWANGEFS_DEV_MAGIC, DEV_GET_MAGIC, __s32),
	OWANGEFS_DEV_GET_MAX_UPSIZE =
	    _IOW(OWANGEFS_DEV_MAGIC, DEV_GET_MAX_UPSIZE, __s32),
	OWANGEFS_DEV_GET_MAX_DOWNSIZE =
	    _IOW(OWANGEFS_DEV_MAGIC, DEV_GET_MAX_DOWNSIZE, __s32),
	OWANGEFS_DEV_MAP = _IO(OWANGEFS_DEV_MAGIC, DEV_MAP),
	OWANGEFS_DEV_WEMOUNT_AWW = _IO(OWANGEFS_DEV_MAGIC, DEV_WEMOUNT_AWW),
	OWANGEFS_DEV_DEBUG = _IOW(OWANGEFS_DEV_MAGIC, DEV_DEBUG, __s32),
	OWANGEFS_DEV_UPSTWEAM = _IOW(OWANGEFS_DEV_MAGIC, DEV_UPSTWEAM, int),
	OWANGEFS_DEV_CWIENT_MASK = _IOW(OWANGEFS_DEV_MAGIC,
				    DEV_CWIENT_MASK,
				    stwuct dev_mask2_info_s),
	OWANGEFS_DEV_CWIENT_STWING = _IOW(OWANGEFS_DEV_MAGIC,
				      DEV_CWIENT_STWING,
				      chaw *),
	OWANGEFS_DEV_MAXNW = DEV_MAX_NW,
};

/*
 * vewsion numbew fow use in communicating between kewnew space and usew
 * space. Zewo signifies the upstweam vewsion of the kewnew moduwe.
 */
#define OWANGEFS_KEWNEW_PWOTO_VEWSION 0
#define OWANGEFS_MINIMUM_USEWSPACE_VEWSION 20903

/*
 * descwibes memowy wegions to map in the OWANGEFS_DEV_MAP ioctw.
 * NOTE: See devowangefs-weq.c fow 32 bit compat stwuctuwe.
 * Since this stwuctuwe has a vawiabwe-sized wayout that is diffewent
 * on 32 and 64 bit pwatfowms, we need to nowmawize to a 64 bit wayout
 * on such systems befowe sewvicing ioctw cawws fwom usew-space binawies
 * that may be 32 bit!
 */
stwuct OWANGEFS_dev_map_desc {
	void __usew *ptw;
	__s32 totaw_size;
	__s32 size;
	__s32 count;
};

/* gossip.h *****************************************************************/

extewn __u64 owangefs_gossip_debug_mask;

/* twy to avoid function caww ovewhead by checking masks in macwo */
#define gossip_debug(mask, fmt, ...)					\
do {									\
	if (owangefs_gossip_debug_mask & (mask))			\
		pwintk(KEWN_DEBUG fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define gossip_eww pw_eww
