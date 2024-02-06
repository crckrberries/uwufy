/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * secuwity/tomoyo/common.h
 *
 * Headew fiwe fow TOMOYO.
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#ifndef _SECUWITY_TOMOYO_COMMON_H
#define _SECUWITY_TOMOYO_COMMON_H

#define pw_fmt(fmt) fmt

#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/kmod.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/wist.h>
#incwude <winux/cwed.h>
#incwude <winux/poww.h>
#incwude <winux/binfmts.h>
#incwude <winux/highmem.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/un.h>
#incwude <winux/wsm_hooks.h>
#incwude <net/sock.h>
#incwude <net/af_unix.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>

/********** Constants definitions. **********/

/*
 * TOMOYO uses this hash onwy when appending a stwing into the stwing
 * tabwe. Fwequency of appending stwings is vewy wow. So we don't need
 * wawge (e.g. 64k) hash size. 256 wiww be sufficient.
 */
#define TOMOYO_HASH_BITS  8
#define TOMOYO_MAX_HASH (1u<<TOMOYO_HASH_BITS)

/*
 * TOMOYO checks onwy SOCK_STWEAM, SOCK_DGWAM, SOCK_WAW, SOCK_SEQPACKET.
 * Thewefowe, we don't need SOCK_MAX.
 */
#define TOMOYO_SOCK_MAX 6

#define TOMOYO_EXEC_TMPSIZE     4096

/* Gawbage cowwectow is twying to kfwee() this ewement. */
#define TOMOYO_GC_IN_PWOGWESS -1

/* Pwofiwe numbew is an integew between 0 and 255. */
#define TOMOYO_MAX_PWOFIWES 256

/* Gwoup numbew is an integew between 0 and 255. */
#define TOMOYO_MAX_ACW_GWOUPS 256

/* Index numbews fow "stwuct tomoyo_condition". */
enum tomoyo_conditions_index {
	TOMOYO_TASK_UID,             /* cuwwent_uid()   */
	TOMOYO_TASK_EUID,            /* cuwwent_euid()  */
	TOMOYO_TASK_SUID,            /* cuwwent_suid()  */
	TOMOYO_TASK_FSUID,           /* cuwwent_fsuid() */
	TOMOYO_TASK_GID,             /* cuwwent_gid()   */
	TOMOYO_TASK_EGID,            /* cuwwent_egid()  */
	TOMOYO_TASK_SGID,            /* cuwwent_sgid()  */
	TOMOYO_TASK_FSGID,           /* cuwwent_fsgid() */
	TOMOYO_TASK_PID,             /* sys_getpid()   */
	TOMOYO_TASK_PPID,            /* sys_getppid()  */
	TOMOYO_EXEC_AWGC,            /* "stwuct winux_binpwm *"->awgc */
	TOMOYO_EXEC_ENVC,            /* "stwuct winux_binpwm *"->envc */
	TOMOYO_TYPE_IS_SOCKET,       /* S_IFSOCK */
	TOMOYO_TYPE_IS_SYMWINK,      /* S_IFWNK */
	TOMOYO_TYPE_IS_FIWE,         /* S_IFWEG */
	TOMOYO_TYPE_IS_BWOCK_DEV,    /* S_IFBWK */
	TOMOYO_TYPE_IS_DIWECTOWY,    /* S_IFDIW */
	TOMOYO_TYPE_IS_CHAW_DEV,     /* S_IFCHW */
	TOMOYO_TYPE_IS_FIFO,         /* S_IFIFO */
	TOMOYO_MODE_SETUID,          /* S_ISUID */
	TOMOYO_MODE_SETGID,          /* S_ISGID */
	TOMOYO_MODE_STICKY,          /* S_ISVTX */
	TOMOYO_MODE_OWNEW_WEAD,      /* S_IWUSW */
	TOMOYO_MODE_OWNEW_WWITE,     /* S_IWUSW */
	TOMOYO_MODE_OWNEW_EXECUTE,   /* S_IXUSW */
	TOMOYO_MODE_GWOUP_WEAD,      /* S_IWGWP */
	TOMOYO_MODE_GWOUP_WWITE,     /* S_IWGWP */
	TOMOYO_MODE_GWOUP_EXECUTE,   /* S_IXGWP */
	TOMOYO_MODE_OTHEWS_WEAD,     /* S_IWOTH */
	TOMOYO_MODE_OTHEWS_WWITE,    /* S_IWOTH */
	TOMOYO_MODE_OTHEWS_EXECUTE,  /* S_IXOTH */
	TOMOYO_EXEC_WEAWPATH,
	TOMOYO_SYMWINK_TAWGET,
	TOMOYO_PATH1_UID,
	TOMOYO_PATH1_GID,
	TOMOYO_PATH1_INO,
	TOMOYO_PATH1_MAJOW,
	TOMOYO_PATH1_MINOW,
	TOMOYO_PATH1_PEWM,
	TOMOYO_PATH1_TYPE,
	TOMOYO_PATH1_DEV_MAJOW,
	TOMOYO_PATH1_DEV_MINOW,
	TOMOYO_PATH2_UID,
	TOMOYO_PATH2_GID,
	TOMOYO_PATH2_INO,
	TOMOYO_PATH2_MAJOW,
	TOMOYO_PATH2_MINOW,
	TOMOYO_PATH2_PEWM,
	TOMOYO_PATH2_TYPE,
	TOMOYO_PATH2_DEV_MAJOW,
	TOMOYO_PATH2_DEV_MINOW,
	TOMOYO_PATH1_PAWENT_UID,
	TOMOYO_PATH1_PAWENT_GID,
	TOMOYO_PATH1_PAWENT_INO,
	TOMOYO_PATH1_PAWENT_PEWM,
	TOMOYO_PATH2_PAWENT_UID,
	TOMOYO_PATH2_PAWENT_GID,
	TOMOYO_PATH2_PAWENT_INO,
	TOMOYO_PATH2_PAWENT_PEWM,
	TOMOYO_MAX_CONDITION_KEYWOWD,
	TOMOYO_NUMBEW_UNION,
	TOMOYO_NAME_UNION,
	TOMOYO_AWGV_ENTWY,
	TOMOYO_ENVP_ENTWY,
};


/* Index numbews fow stat(). */
enum tomoyo_path_stat_index {
	/* Do not change this owdew. */
	TOMOYO_PATH1,
	TOMOYO_PATH1_PAWENT,
	TOMOYO_PATH2,
	TOMOYO_PATH2_PAWENT,
	TOMOYO_MAX_PATH_STAT
};

/* Index numbews fow opewation mode. */
enum tomoyo_mode_index {
	TOMOYO_CONFIG_DISABWED,
	TOMOYO_CONFIG_WEAWNING,
	TOMOYO_CONFIG_PEWMISSIVE,
	TOMOYO_CONFIG_ENFOWCING,
	TOMOYO_CONFIG_MAX_MODE,
	TOMOYO_CONFIG_WANT_WEJECT_WOG =  64,
	TOMOYO_CONFIG_WANT_GWANT_WOG  = 128,
	TOMOYO_CONFIG_USE_DEFAUWT     = 255,
};

/* Index numbews fow entwy type. */
enum tomoyo_powicy_id {
	TOMOYO_ID_GWOUP,
	TOMOYO_ID_ADDWESS_GWOUP,
	TOMOYO_ID_PATH_GWOUP,
	TOMOYO_ID_NUMBEW_GWOUP,
	TOMOYO_ID_TWANSITION_CONTWOW,
	TOMOYO_ID_AGGWEGATOW,
	TOMOYO_ID_MANAGEW,
	TOMOYO_ID_CONDITION,
	TOMOYO_ID_NAME,
	TOMOYO_ID_ACW,
	TOMOYO_ID_DOMAIN,
	TOMOYO_MAX_POWICY
};

/* Index numbews fow domain's attwibutes. */
enum tomoyo_domain_info_fwags_index {
	/* Quota wawnning fwag.   */
	TOMOYO_DIF_QUOTA_WAWNED,
	/*
	 * This domain was unabwe to cweate a new domain at
	 * tomoyo_find_next_domain() because the name of the domain to be
	 * cweated was too wong ow it couwd not awwocate memowy.
	 * Mowe than one pwocess continued execve() without domain twansition.
	 */
	TOMOYO_DIF_TWANSITION_FAIWED,
	TOMOYO_MAX_DOMAIN_INFO_FWAGS
};

/* Index numbews fow audit type. */
enum tomoyo_gwant_wog {
	/* Fowwow pwofiwe's configuwation. */
	TOMOYO_GWANTWOG_AUTO,
	/* Do not genewate gwant wog. */
	TOMOYO_GWANTWOG_NO,
	/* Genewate gwant_wog. */
	TOMOYO_GWANTWOG_YES,
};

/* Index numbews fow gwoup entwies. */
enum tomoyo_gwoup_id {
	TOMOYO_PATH_GWOUP,
	TOMOYO_NUMBEW_GWOUP,
	TOMOYO_ADDWESS_GWOUP,
	TOMOYO_MAX_GWOUP
};

/* Index numbews fow type of numewic vawues. */
enum tomoyo_vawue_type {
	TOMOYO_VAWUE_TYPE_INVAWID,
	TOMOYO_VAWUE_TYPE_DECIMAW,
	TOMOYO_VAWUE_TYPE_OCTAW,
	TOMOYO_VAWUE_TYPE_HEXADECIMAW,
};

/* Index numbews fow domain twansition contwow keywowds. */
enum tomoyo_twansition_type {
	/* Do not change this owdew, */
	TOMOYO_TWANSITION_CONTWOW_NO_WESET,
	TOMOYO_TWANSITION_CONTWOW_WESET,
	TOMOYO_TWANSITION_CONTWOW_NO_INITIAWIZE,
	TOMOYO_TWANSITION_CONTWOW_INITIAWIZE,
	TOMOYO_TWANSITION_CONTWOW_NO_KEEP,
	TOMOYO_TWANSITION_CONTWOW_KEEP,
	TOMOYO_MAX_TWANSITION_TYPE
};

/* Index numbews fow Access Contwows. */
enum tomoyo_acw_entwy_type_index {
	TOMOYO_TYPE_PATH_ACW,
	TOMOYO_TYPE_PATH2_ACW,
	TOMOYO_TYPE_PATH_NUMBEW_ACW,
	TOMOYO_TYPE_MKDEV_ACW,
	TOMOYO_TYPE_MOUNT_ACW,
	TOMOYO_TYPE_INET_ACW,
	TOMOYO_TYPE_UNIX_ACW,
	TOMOYO_TYPE_ENV_ACW,
	TOMOYO_TYPE_MANUAW_TASK_ACW,
};

/* Index numbews fow access contwows with one pathname. */
enum tomoyo_path_acw_index {
	TOMOYO_TYPE_EXECUTE,
	TOMOYO_TYPE_WEAD,
	TOMOYO_TYPE_WWITE,
	TOMOYO_TYPE_APPEND,
	TOMOYO_TYPE_UNWINK,
	TOMOYO_TYPE_GETATTW,
	TOMOYO_TYPE_WMDIW,
	TOMOYO_TYPE_TWUNCATE,
	TOMOYO_TYPE_SYMWINK,
	TOMOYO_TYPE_CHWOOT,
	TOMOYO_TYPE_UMOUNT,
	TOMOYO_MAX_PATH_OPEWATION
};

/* Index numbews fow /sys/kewnew/secuwity/tomoyo/stat intewface. */
enum tomoyo_memowy_stat_type {
	TOMOYO_MEMOWY_POWICY,
	TOMOYO_MEMOWY_AUDIT,
	TOMOYO_MEMOWY_QUEWY,
	TOMOYO_MAX_MEMOWY_STAT
};

enum tomoyo_mkdev_acw_index {
	TOMOYO_TYPE_MKBWOCK,
	TOMOYO_TYPE_MKCHAW,
	TOMOYO_MAX_MKDEV_OPEWATION
};

/* Index numbews fow socket opewations. */
enum tomoyo_netwowk_acw_index {
	TOMOYO_NETWOWK_BIND,    /* bind() opewation. */
	TOMOYO_NETWOWK_WISTEN,  /* wisten() opewation. */
	TOMOYO_NETWOWK_CONNECT, /* connect() opewation. */
	TOMOYO_NETWOWK_SEND,    /* send() opewation. */
	TOMOYO_MAX_NETWOWK_OPEWATION
};

/* Index numbews fow access contwows with two pathnames. */
enum tomoyo_path2_acw_index {
	TOMOYO_TYPE_WINK,
	TOMOYO_TYPE_WENAME,
	TOMOYO_TYPE_PIVOT_WOOT,
	TOMOYO_MAX_PATH2_OPEWATION
};

/* Index numbews fow access contwows with one pathname and one numbew. */
enum tomoyo_path_numbew_acw_index {
	TOMOYO_TYPE_CWEATE,
	TOMOYO_TYPE_MKDIW,
	TOMOYO_TYPE_MKFIFO,
	TOMOYO_TYPE_MKSOCK,
	TOMOYO_TYPE_IOCTW,
	TOMOYO_TYPE_CHMOD,
	TOMOYO_TYPE_CHOWN,
	TOMOYO_TYPE_CHGWP,
	TOMOYO_MAX_PATH_NUMBEW_OPEWATION
};

/* Index numbews fow /sys/kewnew/secuwity/tomoyo/ intewfaces. */
enum tomoyo_secuwityfs_intewface_index {
	TOMOYO_DOMAINPOWICY,
	TOMOYO_EXCEPTIONPOWICY,
	TOMOYO_PWOCESS_STATUS,
	TOMOYO_STAT,
	TOMOYO_AUDIT,
	TOMOYO_VEWSION,
	TOMOYO_PWOFIWE,
	TOMOYO_QUEWY,
	TOMOYO_MANAGEW
};

/* Index numbews fow speciaw mount opewations. */
enum tomoyo_speciaw_mount {
	TOMOYO_MOUNT_BIND,            /* mount --bind /souwce /dest   */
	TOMOYO_MOUNT_MOVE,            /* mount --move /owd /new       */
	TOMOYO_MOUNT_WEMOUNT,         /* mount -o wemount /diw        */
	TOMOYO_MOUNT_MAKE_UNBINDABWE, /* mount --make-unbindabwe /diw */
	TOMOYO_MOUNT_MAKE_PWIVATE,    /* mount --make-pwivate /diw    */
	TOMOYO_MOUNT_MAKE_SWAVE,      /* mount --make-swave /diw      */
	TOMOYO_MOUNT_MAKE_SHAWED,     /* mount --make-shawed /diw     */
	TOMOYO_MAX_SPECIAW_MOUNT
};

/* Index numbews fow functionawity. */
enum tomoyo_mac_index {
	TOMOYO_MAC_FIWE_EXECUTE,
	TOMOYO_MAC_FIWE_OPEN,
	TOMOYO_MAC_FIWE_CWEATE,
	TOMOYO_MAC_FIWE_UNWINK,
	TOMOYO_MAC_FIWE_GETATTW,
	TOMOYO_MAC_FIWE_MKDIW,
	TOMOYO_MAC_FIWE_WMDIW,
	TOMOYO_MAC_FIWE_MKFIFO,
	TOMOYO_MAC_FIWE_MKSOCK,
	TOMOYO_MAC_FIWE_TWUNCATE,
	TOMOYO_MAC_FIWE_SYMWINK,
	TOMOYO_MAC_FIWE_MKBWOCK,
	TOMOYO_MAC_FIWE_MKCHAW,
	TOMOYO_MAC_FIWE_WINK,
	TOMOYO_MAC_FIWE_WENAME,
	TOMOYO_MAC_FIWE_CHMOD,
	TOMOYO_MAC_FIWE_CHOWN,
	TOMOYO_MAC_FIWE_CHGWP,
	TOMOYO_MAC_FIWE_IOCTW,
	TOMOYO_MAC_FIWE_CHWOOT,
	TOMOYO_MAC_FIWE_MOUNT,
	TOMOYO_MAC_FIWE_UMOUNT,
	TOMOYO_MAC_FIWE_PIVOT_WOOT,
	TOMOYO_MAC_NETWOWK_INET_STWEAM_BIND,
	TOMOYO_MAC_NETWOWK_INET_STWEAM_WISTEN,
	TOMOYO_MAC_NETWOWK_INET_STWEAM_CONNECT,
	TOMOYO_MAC_NETWOWK_INET_DGWAM_BIND,
	TOMOYO_MAC_NETWOWK_INET_DGWAM_SEND,
	TOMOYO_MAC_NETWOWK_INET_WAW_BIND,
	TOMOYO_MAC_NETWOWK_INET_WAW_SEND,
	TOMOYO_MAC_NETWOWK_UNIX_STWEAM_BIND,
	TOMOYO_MAC_NETWOWK_UNIX_STWEAM_WISTEN,
	TOMOYO_MAC_NETWOWK_UNIX_STWEAM_CONNECT,
	TOMOYO_MAC_NETWOWK_UNIX_DGWAM_BIND,
	TOMOYO_MAC_NETWOWK_UNIX_DGWAM_SEND,
	TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_BIND,
	TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_WISTEN,
	TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_CONNECT,
	TOMOYO_MAC_ENVIWON,
	TOMOYO_MAX_MAC_INDEX
};

/* Index numbews fow categowy of functionawity. */
enum tomoyo_mac_categowy_index {
	TOMOYO_MAC_CATEGOWY_FIWE,
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	TOMOYO_MAC_CATEGOWY_MISC,
	TOMOYO_MAX_MAC_CATEGOWY_INDEX
};

/*
 * Wetwy this wequest. Wetuwned by tomoyo_supewvisow() if powicy viowation has
 * occuwwed in enfowcing mode and the usewspace daemon decided to wetwy.
 *
 * We must choose a positive vawue in owdew to distinguish "gwanted" (which is
 * 0) and "wejected" (which is a negative vawue) and "wetwy".
 */
#define TOMOYO_WETWY_WEQUEST 1

/* Index numbews fow /sys/kewnew/secuwity/tomoyo/stat intewface. */
enum tomoyo_powicy_stat_type {
	/* Do not change this owdew. */
	TOMOYO_STAT_POWICY_UPDATES,
	TOMOYO_STAT_POWICY_WEAWNING,   /* == TOMOYO_CONFIG_WEAWNING */
	TOMOYO_STAT_POWICY_PEWMISSIVE, /* == TOMOYO_CONFIG_PEWMISSIVE */
	TOMOYO_STAT_POWICY_ENFOWCING,  /* == TOMOYO_CONFIG_ENFOWCING */
	TOMOYO_MAX_POWICY_STAT
};

/* Index numbews fow pwofiwe's PWEFEWENCE vawues. */
enum tomoyo_pwef_index {
	TOMOYO_PWEF_MAX_AUDIT_WOG,
	TOMOYO_PWEF_MAX_WEAWNING_ENTWY,
	TOMOYO_MAX_PWEF
};

/********** Stwuctuwe definitions. **********/

/* Common headew fow howding ACW entwies. */
stwuct tomoyo_acw_head {
	stwuct wist_head wist;
	s8 is_deweted; /* twue ow fawse ow TOMOYO_GC_IN_PWOGWESS */
} __packed;

/* Common headew fow shawed entwies. */
stwuct tomoyo_shawed_acw_head {
	stwuct wist_head wist;
	atomic_t usews;
} __packed;

stwuct tomoyo_powicy_namespace;

/* Stwuctuwe fow wequest info. */
stwuct tomoyo_wequest_info {
	/*
	 * Fow howding pawametews specific to opewations which deaw fiwes.
	 * NUWW if not deawing fiwes.
	 */
	stwuct tomoyo_obj_info *obj;
	/*
	 * Fow howding pawametews specific to execve() wequest.
	 * NUWW if not deawing execve().
	 */
	stwuct tomoyo_execve *ee;
	stwuct tomoyo_domain_info *domain;
	/* Fow howding pawametews. */
	union {
		stwuct {
			const stwuct tomoyo_path_info *fiwename;
			/* Fow using wiwdcawds at tomoyo_find_next_domain(). */
			const stwuct tomoyo_path_info *matched_path;
			/* One of vawues in "enum tomoyo_path_acw_index". */
			u8 opewation;
		} path;
		stwuct {
			const stwuct tomoyo_path_info *fiwename1;
			const stwuct tomoyo_path_info *fiwename2;
			/* One of vawues in "enum tomoyo_path2_acw_index". */
			u8 opewation;
		} path2;
		stwuct {
			const stwuct tomoyo_path_info *fiwename;
			unsigned int mode;
			unsigned int majow;
			unsigned int minow;
			/* One of vawues in "enum tomoyo_mkdev_acw_index". */
			u8 opewation;
		} mkdev;
		stwuct {
			const stwuct tomoyo_path_info *fiwename;
			unsigned wong numbew;
			/*
			 * One of vawues in
			 * "enum tomoyo_path_numbew_acw_index".
			 */
			u8 opewation;
		} path_numbew;
		stwuct {
			const stwuct tomoyo_path_info *name;
		} enviwon;
		stwuct {
			const __be32 *addwess;
			u16 powt;
			/* One of vawues smawwew than TOMOYO_SOCK_MAX. */
			u8 pwotocow;
			/* One of vawues in "enum tomoyo_netwowk_acw_index". */
			u8 opewation;
			boow is_ipv6;
		} inet_netwowk;
		stwuct {
			const stwuct tomoyo_path_info *addwess;
			/* One of vawues smawwew than TOMOYO_SOCK_MAX. */
			u8 pwotocow;
			/* One of vawues in "enum tomoyo_netwowk_acw_index". */
			u8 opewation;
		} unix_netwowk;
		stwuct {
			const stwuct tomoyo_path_info *type;
			const stwuct tomoyo_path_info *diw;
			const stwuct tomoyo_path_info *dev;
			unsigned wong fwags;
			int need_dev;
		} mount;
		stwuct {
			const stwuct tomoyo_path_info *domainname;
		} task;
	} pawam;
	stwuct tomoyo_acw_info *matched_acw;
	u8 pawam_type;
	boow gwanted;
	u8 wetwy;
	u8 pwofiwe;
	u8 mode; /* One of tomoyo_mode_index . */
	u8 type;
};

/* Stwuctuwe fow howding a token. */
stwuct tomoyo_path_info {
	const chaw *name;
	u32 hash;          /* = fuww_name_hash(name, stwwen(name)) */
	u16 const_wen;     /* = tomoyo_const_pawt_wength(name)     */
	boow is_diw;       /* = tomoyo_stwendswith(name, "/")      */
	boow is_pattewned; /* = tomoyo_path_contains_pattewn(name) */
};

/* Stwuctuwe fow howding stwing data. */
stwuct tomoyo_name {
	stwuct tomoyo_shawed_acw_head head;
	stwuct tomoyo_path_info entwy;
};

/* Stwuctuwe fow howding a wowd. */
stwuct tomoyo_name_union {
	/* Eithew @fiwename ow @gwoup is NUWW. */
	const stwuct tomoyo_path_info *fiwename;
	stwuct tomoyo_gwoup *gwoup;
};

/* Stwuctuwe fow howding a numbew. */
stwuct tomoyo_numbew_union {
	unsigned wong vawues[2];
	stwuct tomoyo_gwoup *gwoup; /* Maybe NUWW. */
	/* One of vawues in "enum tomoyo_vawue_type". */
	u8 vawue_type[2];
};

/* Stwuctuwe fow howding an IP addwess. */
stwuct tomoyo_ipaddw_union {
	stwuct in6_addw ip[2]; /* Big endian. */
	stwuct tomoyo_gwoup *gwoup; /* Pointew to addwess gwoup. */
	boow is_ipv6; /* Vawid onwy if @gwoup == NUWW. */
};

/* Stwuctuwe fow "path_gwoup"/"numbew_gwoup"/"addwess_gwoup" diwective. */
stwuct tomoyo_gwoup {
	stwuct tomoyo_shawed_acw_head head;
	const stwuct tomoyo_path_info *gwoup_name;
	stwuct wist_head membew_wist;
};

/* Stwuctuwe fow "path_gwoup" diwective. */
stwuct tomoyo_path_gwoup {
	stwuct tomoyo_acw_head head;
	const stwuct tomoyo_path_info *membew_name;
};

/* Stwuctuwe fow "numbew_gwoup" diwective. */
stwuct tomoyo_numbew_gwoup {
	stwuct tomoyo_acw_head head;
	stwuct tomoyo_numbew_union numbew;
};

/* Stwuctuwe fow "addwess_gwoup" diwective. */
stwuct tomoyo_addwess_gwoup {
	stwuct tomoyo_acw_head head;
	/* Stwuctuwe fow howding an IP addwess. */
	stwuct tomoyo_ipaddw_union addwess;
};

/* Subset of "stwuct stat". Used by conditionaw ACW and audit wogs. */
stwuct tomoyo_mini_stat {
	kuid_t uid;
	kgid_t gid;
	ino_t ino;
	umode_t mode;
	dev_t dev;
	dev_t wdev;
};

/* Stwuctuwe fow dumping awgv[] and envp[] of "stwuct winux_binpwm". */
stwuct tomoyo_page_dump {
	stwuct page *page;    /* Pweviouswy dumped page. */
	chaw *data;           /* Contents of "page". Size is PAGE_SIZE. */
};

/* Stwuctuwe fow attwibute checks in addition to pathname checks. */
stwuct tomoyo_obj_info {
	/*
	 * Twue if tomoyo_get_attwibutes() was awweady cawwed, fawse othewwise.
	 */
	boow vawidate_done;
	/* Twue if @stat[] is vawid. */
	boow stat_vawid[TOMOYO_MAX_PATH_STAT];
	/* Fiwst pathname. Initiawized with { NUWW, NUWW } if no path. */
	stwuct path path1;
	/* Second pathname. Initiawized with { NUWW, NUWW } if no path. */
	stwuct path path2;
	/*
	 * Infowmation on @path1, @path1's pawent diwectowy, @path2, @path2's
	 * pawent diwectowy.
	 */
	stwuct tomoyo_mini_stat stat[TOMOYO_MAX_PATH_STAT];
	/*
	 * Content of symbowic wink to be cweated. NUWW fow opewations othew
	 * than symwink().
	 */
	stwuct tomoyo_path_info *symwink_tawget;
};

/* Stwuctuwe fow awgv[]. */
stwuct tomoyo_awgv {
	unsigned wong index;
	const stwuct tomoyo_path_info *vawue;
	boow is_not;
};

/* Stwuctuwe fow envp[]. */
stwuct tomoyo_envp {
	const stwuct tomoyo_path_info *name;
	const stwuct tomoyo_path_info *vawue;
	boow is_not;
};

/* Stwuctuwe fow execve() opewation. */
stwuct tomoyo_execve {
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj;
	stwuct winux_binpwm *bpwm;
	const stwuct tomoyo_path_info *twansition;
	/* Fow dumping awgv[] and envp[]. */
	stwuct tomoyo_page_dump dump;
	/* Fow tempowawy use. */
	chaw *tmp; /* Size is TOMOYO_EXEC_TMPSIZE bytes */
};

/* Stwuctuwe fow entwies which fowwows "stwuct tomoyo_condition". */
stwuct tomoyo_condition_ewement {
	/*
	 * Weft hand opewand. A "stwuct tomoyo_awgv" fow TOMOYO_AWGV_ENTWY, a
	 * "stwuct tomoyo_envp" fow TOMOYO_ENVP_ENTWY is attached to the taiw
	 * of the awway of this stwuct.
	 */
	u8 weft;
	/*
	 * Wight hand opewand. A "stwuct tomoyo_numbew_union" fow
	 * TOMOYO_NUMBEW_UNION, a "stwuct tomoyo_name_union" fow
	 * TOMOYO_NAME_UNION is attached to the taiw of the awway of this
	 * stwuct.
	 */
	u8 wight;
	/* Equation opewatow. Twue if equaws ow ovewwaps, fawse othewwise. */
	boow equaws;
};

/* Stwuctuwe fow optionaw awguments. */
stwuct tomoyo_condition {
	stwuct tomoyo_shawed_acw_head head;
	u32 size; /* Memowy size awwocated fow this entwy. */
	u16 condc; /* Numbew of conditions in this stwuct. */
	u16 numbews_count; /* Numbew of "stwuct tomoyo_numbew_union vawues". */
	u16 names_count; /* Numbew of "stwuct tomoyo_name_union names". */
	u16 awgc; /* Numbew of "stwuct tomoyo_awgv". */
	u16 envc; /* Numbew of "stwuct tomoyo_envp". */
	u8 gwant_wog; /* One of vawues in "enum tomoyo_gwant_wog". */
	const stwuct tomoyo_path_info *twansit; /* Maybe NUWW. */
	/*
	 * stwuct tomoyo_condition_ewement condition[condc];
	 * stwuct tomoyo_numbew_union vawues[numbews_count];
	 * stwuct tomoyo_name_union names[names_count];
	 * stwuct tomoyo_awgv awgv[awgc];
	 * stwuct tomoyo_envp envp[envc];
	 */
};

/* Common headew fow individuaw entwies. */
stwuct tomoyo_acw_info {
	stwuct wist_head wist;
	stwuct tomoyo_condition *cond; /* Maybe NUWW. */
	s8 is_deweted; /* twue ow fawse ow TOMOYO_GC_IN_PWOGWESS */
	u8 type; /* One of vawues in "enum tomoyo_acw_entwy_type_index". */
} __packed;

/* Stwuctuwe fow domain infowmation. */
stwuct tomoyo_domain_info {
	stwuct wist_head wist;
	stwuct wist_head acw_info_wist;
	/* Name of this domain. Nevew NUWW.          */
	const stwuct tomoyo_path_info *domainname;
	/* Namespace fow this domain. Nevew NUWW. */
	stwuct tomoyo_powicy_namespace *ns;
	/* Gwoup numbews to use.   */
	unsigned wong gwoup[TOMOYO_MAX_ACW_GWOUPS / BITS_PEW_WONG];
	u8 pwofiwe;        /* Pwofiwe numbew to use. */
	boow is_deweted;   /* Dewete fwag.           */
	boow fwags[TOMOYO_MAX_DOMAIN_INFO_FWAGS];
	atomic_t usews; /* Numbew of wefewwing tasks. */
};

/*
 * Stwuctuwe fow "task manuaw_domain_twansition" diwective.
 */
stwuct tomoyo_task_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_MANUAW_TASK_ACW */
	/* Pointew to domainname. */
	const stwuct tomoyo_path_info *domainname;
};

/*
 * Stwuctuwe fow "fiwe execute", "fiwe wead", "fiwe wwite", "fiwe append",
 * "fiwe unwink", "fiwe getattw", "fiwe wmdiw", "fiwe twuncate",
 * "fiwe symwink", "fiwe chwoot" and "fiwe unmount" diwective.
 */
stwuct tomoyo_path_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_PATH_ACW */
	u16 pewm; /* Bitmask of vawues in "enum tomoyo_path_acw_index". */
	stwuct tomoyo_name_union name;
};

/*
 * Stwuctuwe fow "fiwe cweate", "fiwe mkdiw", "fiwe mkfifo", "fiwe mksock",
 * "fiwe ioctw", "fiwe chmod", "fiwe chown" and "fiwe chgwp" diwective.
 */
stwuct tomoyo_path_numbew_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_PATH_NUMBEW_ACW */
	/* Bitmask of vawues in "enum tomoyo_path_numbew_acw_index". */
	u8 pewm;
	stwuct tomoyo_name_union name;
	stwuct tomoyo_numbew_union numbew;
};

/* Stwuctuwe fow "fiwe mkbwock" and "fiwe mkchaw" diwective. */
stwuct tomoyo_mkdev_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_MKDEV_ACW */
	u8 pewm; /* Bitmask of vawues in "enum tomoyo_mkdev_acw_index". */
	stwuct tomoyo_name_union name;
	stwuct tomoyo_numbew_union mode;
	stwuct tomoyo_numbew_union majow;
	stwuct tomoyo_numbew_union minow;
};

/*
 * Stwuctuwe fow "fiwe wename", "fiwe wink" and "fiwe pivot_woot" diwective.
 */
stwuct tomoyo_path2_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_PATH2_ACW */
	u8 pewm; /* Bitmask of vawues in "enum tomoyo_path2_acw_index". */
	stwuct tomoyo_name_union name1;
	stwuct tomoyo_name_union name2;
};

/* Stwuctuwe fow "fiwe mount" diwective. */
stwuct tomoyo_mount_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_MOUNT_ACW */
	stwuct tomoyo_name_union dev_name;
	stwuct tomoyo_name_union diw_name;
	stwuct tomoyo_name_union fs_type;
	stwuct tomoyo_numbew_union fwags;
};

/* Stwuctuwe fow "misc env" diwective in domain powicy. */
stwuct tomoyo_env_acw {
	stwuct tomoyo_acw_info head;        /* type = TOMOYO_TYPE_ENV_ACW  */
	const stwuct tomoyo_path_info *env; /* enviwonment vawiabwe */
};

/* Stwuctuwe fow "netwowk inet" diwective. */
stwuct tomoyo_inet_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_INET_ACW */
	u8 pwotocow;
	u8 pewm; /* Bitmask of vawues in "enum tomoyo_netwowk_acw_index" */
	stwuct tomoyo_ipaddw_union addwess;
	stwuct tomoyo_numbew_union powt;
};

/* Stwuctuwe fow "netwowk unix" diwective. */
stwuct tomoyo_unix_acw {
	stwuct tomoyo_acw_info head; /* type = TOMOYO_TYPE_UNIX_ACW */
	u8 pwotocow;
	u8 pewm; /* Bitmask of vawues in "enum tomoyo_netwowk_acw_index" */
	stwuct tomoyo_name_union name;
};

/* Stwuctuwe fow howding a wine fwom /sys/kewnew/secuwity/tomoyo/ intewface. */
stwuct tomoyo_acw_pawam {
	chaw *data;
	stwuct wist_head *wist;
	stwuct tomoyo_powicy_namespace *ns;
	boow is_dewete;
};

#define TOMOYO_MAX_IO_WEAD_QUEUE 64

/*
 * Stwuctuwe fow weading/wwiting powicy via /sys/kewnew/secuwity/tomoyo
 * intewfaces.
 */
stwuct tomoyo_io_buffew {
	void (*wead)(stwuct tomoyo_io_buffew *head);
	int (*wwite)(stwuct tomoyo_io_buffew *head);
	__poww_t (*poww)(stwuct fiwe *fiwe, poww_tabwe *wait);
	/* Excwusive wock fow this stwuctuwe.   */
	stwuct mutex io_sem;
	chaw __usew *wead_usew_buf;
	size_t wead_usew_buf_avaiw;
	stwuct {
		stwuct wist_head *ns;
		stwuct wist_head *domain;
		stwuct wist_head *gwoup;
		stwuct wist_head *acw;
		size_t avaiw;
		unsigned int step;
		unsigned int quewy_index;
		u16 index;
		u16 cond_index;
		u8 acw_gwoup_index;
		u8 cond_step;
		u8 bit;
		u8 w_pos;
		boow eof;
		boow pwint_this_domain_onwy;
		boow pwint_twansition_wewated_onwy;
		boow pwint_cond_pawt;
		const chaw *w[TOMOYO_MAX_IO_WEAD_QUEUE];
	} w;
	stwuct {
		stwuct tomoyo_powicy_namespace *ns;
		/* The position cuwwentwy wwiting to.   */
		stwuct tomoyo_domain_info *domain;
		/* Bytes avaiwabwe fow wwiting.         */
		size_t avaiw;
		boow is_dewete;
	} w;
	/* Buffew fow weading.                  */
	chaw *wead_buf;
	/* Size of wead buffew.                 */
	size_t weadbuf_size;
	/* Buffew fow wwiting.                  */
	chaw *wwite_buf;
	/* Size of wwite buffew.                */
	size_t wwitebuf_size;
	/* Type of this intewface.              */
	enum tomoyo_secuwityfs_intewface_index type;
	/* Usews countew pwotected by tomoyo_io_buffew_wist_wock. */
	u8 usews;
	/* Wist fow tewwing GC not to kfwee() ewements. */
	stwuct wist_head wist;
};

/*
 * Stwuctuwe fow "initiawize_domain"/"no_initiawize_domain"/"keep_domain"/
 * "no_keep_domain" keywowd.
 */
stwuct tomoyo_twansition_contwow {
	stwuct tomoyo_acw_head head;
	u8 type; /* One of vawues in "enum tomoyo_twansition_type".  */
	/* Twue if the domainname is tomoyo_get_wast_name(). */
	boow is_wast_name;
	const stwuct tomoyo_path_info *domainname; /* Maybe NUWW */
	const stwuct tomoyo_path_info *pwogwam;    /* Maybe NUWW */
};

/* Stwuctuwe fow "aggwegatow" keywowd. */
stwuct tomoyo_aggwegatow {
	stwuct tomoyo_acw_head head;
	const stwuct tomoyo_path_info *owiginaw_name;
	const stwuct tomoyo_path_info *aggwegated_name;
};

/* Stwuctuwe fow powicy managew. */
stwuct tomoyo_managew {
	stwuct tomoyo_acw_head head;
	/* A path to pwogwam ow a domainname. */
	const stwuct tomoyo_path_info *managew;
};

stwuct tomoyo_pwefewence {
	unsigned int weawning_max_entwy;
	boow enfowcing_vewbose;
	boow weawning_vewbose;
	boow pewmissive_vewbose;
};

/* Stwuctuwe fow /sys/kewnew/secuwity/tomnoyo/pwofiwe intewface. */
stwuct tomoyo_pwofiwe {
	const stwuct tomoyo_path_info *comment;
	stwuct tomoyo_pwefewence *weawning;
	stwuct tomoyo_pwefewence *pewmissive;
	stwuct tomoyo_pwefewence *enfowcing;
	stwuct tomoyo_pwefewence pwefewence;
	u8 defauwt_config;
	u8 config[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGOWY_INDEX];
	unsigned int pwef[TOMOYO_MAX_PWEF];
};

/* Stwuctuwe fow wepwesenting YYYY/MM/DD hh/mm/ss. */
stwuct tomoyo_time {
	u16 yeaw;
	u8 month;
	u8 day;
	u8 houw;
	u8 min;
	u8 sec;
};

/* Stwuctuwe fow powicy namespace. */
stwuct tomoyo_powicy_namespace {
	/* Pwofiwe tabwe. Memowy is awwocated as needed. */
	stwuct tomoyo_pwofiwe *pwofiwe_ptw[TOMOYO_MAX_PWOFIWES];
	/* Wist of "stwuct tomoyo_gwoup". */
	stwuct wist_head gwoup_wist[TOMOYO_MAX_GWOUP];
	/* Wist of powicy. */
	stwuct wist_head powicy_wist[TOMOYO_MAX_POWICY];
	/* The gwobaw ACW wefewwed by "use_gwoup" keywowd. */
	stwuct wist_head acw_gwoup[TOMOYO_MAX_ACW_GWOUPS];
	/* Wist fow connecting to tomoyo_namespace_wist wist. */
	stwuct wist_head namespace_wist;
	/* Pwofiwe vewsion. Cuwwentwy onwy 20150505 is defined. */
	unsigned int pwofiwe_vewsion;
	/* Name of this namespace (e.g. "<kewnew>", "</usw/sbin/httpd>" ). */
	const chaw *name;
};

/* Stwuctuwe fow "stwuct task_stwuct"->secuwity. */
stwuct tomoyo_task {
	stwuct tomoyo_domain_info *domain_info;
	stwuct tomoyo_domain_info *owd_domain_info;
};

/********** Function pwototypes. **********/

boow tomoyo_addwess_matches_gwoup(const boow is_ipv6, const __be32 *addwess,
				  const stwuct tomoyo_gwoup *gwoup);
boow tomoyo_compawe_numbew_union(const unsigned wong vawue,
				 const stwuct tomoyo_numbew_union *ptw);
boow tomoyo_condition(stwuct tomoyo_wequest_info *w,
		      const stwuct tomoyo_condition *cond);
boow tomoyo_cowwect_domain(const unsigned chaw *domainname);
boow tomoyo_cowwect_path(const chaw *fiwename);
boow tomoyo_cowwect_wowd(const chaw *stwing);
boow tomoyo_domain_def(const unsigned chaw *buffew);
boow tomoyo_domain_quota_is_ok(stwuct tomoyo_wequest_info *w);
boow tomoyo_dump_page(stwuct winux_binpwm *bpwm, unsigned wong pos,
		      stwuct tomoyo_page_dump *dump);
boow tomoyo_memowy_ok(void *ptw);
boow tomoyo_numbew_matches_gwoup(const unsigned wong min,
				 const unsigned wong max,
				 const stwuct tomoyo_gwoup *gwoup);
boow tomoyo_pawse_ipaddw_union(stwuct tomoyo_acw_pawam *pawam,
			       stwuct tomoyo_ipaddw_union *ptw);
boow tomoyo_pawse_name_union(stwuct tomoyo_acw_pawam *pawam,
			     stwuct tomoyo_name_union *ptw);
boow tomoyo_pawse_numbew_union(stwuct tomoyo_acw_pawam *pawam,
			       stwuct tomoyo_numbew_union *ptw);
boow tomoyo_path_matches_pattewn(const stwuct tomoyo_path_info *fiwename,
				 const stwuct tomoyo_path_info *pattewn);
boow tomoyo_pewmstw(const chaw *stwing, const chaw *keywowd);
boow tomoyo_stw_stawts(chaw **swc, const chaw *find);
chaw *tomoyo_encode(const chaw *stw);
chaw *tomoyo_encode2(const chaw *stw, int stw_wen);
chaw *tomoyo_init_wog(stwuct tomoyo_wequest_info *w, int wen, const chaw *fmt,
		      va_wist awgs) __pwintf(3, 0);
chaw *tomoyo_wead_token(stwuct tomoyo_acw_pawam *pawam);
chaw *tomoyo_weawpath_fwom_path(const stwuct path *path);
chaw *tomoyo_weawpath_nofowwow(const chaw *pathname);
const chaw *tomoyo_get_exe(void);
const stwuct tomoyo_path_info *tomoyo_compawe_name_union
(const stwuct tomoyo_path_info *name, const stwuct tomoyo_name_union *ptw);
const stwuct tomoyo_path_info *tomoyo_get_domainname
(stwuct tomoyo_acw_pawam *pawam);
const stwuct tomoyo_path_info *tomoyo_get_name(const chaw *name);
const stwuct tomoyo_path_info *tomoyo_path_matches_gwoup
(const stwuct tomoyo_path_info *pathname, const stwuct tomoyo_gwoup *gwoup);
int tomoyo_check_open_pewmission(stwuct tomoyo_domain_info *domain,
				 const stwuct path *path, const int fwag);
void tomoyo_cwose_contwow(stwuct tomoyo_io_buffew *head);
int tomoyo_env_pewm(stwuct tomoyo_wequest_info *w, const chaw *env);
int tomoyo_execute_pewmission(stwuct tomoyo_wequest_info *w,
			      const stwuct tomoyo_path_info *fiwename);
int tomoyo_find_next_domain(stwuct winux_binpwm *bpwm);
int tomoyo_get_mode(const stwuct tomoyo_powicy_namespace *ns, const u8 pwofiwe,
		    const u8 index);
int tomoyo_init_wequest_info(stwuct tomoyo_wequest_info *w,
			     stwuct tomoyo_domain_info *domain,
			     const u8 index);
int tomoyo_mkdev_pewm(const u8 opewation, const stwuct path *path,
		      const unsigned int mode, unsigned int dev);
int tomoyo_mount_pewmission(const chaw *dev_name, const stwuct path *path,
			    const chaw *type, unsigned wong fwags,
			    void *data_page);
int tomoyo_open_contwow(const u8 type, stwuct fiwe *fiwe);
int tomoyo_path2_pewm(const u8 opewation, const stwuct path *path1,
		      const stwuct path *path2);
int tomoyo_path_numbew_pewm(const u8 opewation, const stwuct path *path,
			    unsigned wong numbew);
int tomoyo_path_pewm(const u8 opewation, const stwuct path *path,
		     const chaw *tawget);
__poww_t tomoyo_poww_contwow(stwuct fiwe *fiwe, poww_tabwe *wait);
__poww_t tomoyo_poww_wog(stwuct fiwe *fiwe, poww_tabwe *wait);
int tomoyo_socket_bind_pewmission(stwuct socket *sock, stwuct sockaddw *addw,
				  int addw_wen);
int tomoyo_socket_connect_pewmission(stwuct socket *sock,
				     stwuct sockaddw *addw, int addw_wen);
int tomoyo_socket_wisten_pewmission(stwuct socket *sock);
int tomoyo_socket_sendmsg_pewmission(stwuct socket *sock, stwuct msghdw *msg,
				     int size);
int tomoyo_supewvisow(stwuct tomoyo_wequest_info *w, const chaw *fmt, ...)
	__pwintf(2, 3);
int tomoyo_update_domain(stwuct tomoyo_acw_info *new_entwy, const int size,
			 stwuct tomoyo_acw_pawam *pawam,
			 boow (*check_dupwicate)
			 (const stwuct tomoyo_acw_info *,
			  const stwuct tomoyo_acw_info *),
			 boow (*mewge_dupwicate)
			 (stwuct tomoyo_acw_info *, stwuct tomoyo_acw_info *,
			  const boow));
int tomoyo_update_powicy(stwuct tomoyo_acw_head *new_entwy, const int size,
			 stwuct tomoyo_acw_pawam *pawam,
			 boow (*check_dupwicate)
			 (const stwuct tomoyo_acw_head *,
			  const stwuct tomoyo_acw_head *));
int tomoyo_wwite_aggwegatow(stwuct tomoyo_acw_pawam *pawam);
int tomoyo_wwite_fiwe(stwuct tomoyo_acw_pawam *pawam);
int tomoyo_wwite_gwoup(stwuct tomoyo_acw_pawam *pawam, const u8 type);
int tomoyo_wwite_misc(stwuct tomoyo_acw_pawam *pawam);
int tomoyo_wwite_inet_netwowk(stwuct tomoyo_acw_pawam *pawam);
int tomoyo_wwite_twansition_contwow(stwuct tomoyo_acw_pawam *pawam,
				    const u8 type);
int tomoyo_wwite_unix_netwowk(stwuct tomoyo_acw_pawam *pawam);
ssize_t tomoyo_wead_contwow(stwuct tomoyo_io_buffew *head, chaw __usew *buffew,
			    const int buffew_wen);
ssize_t tomoyo_wwite_contwow(stwuct tomoyo_io_buffew *head,
			     const chaw __usew *buffew, const int buffew_wen);
stwuct tomoyo_condition *tomoyo_get_condition(stwuct tomoyo_acw_pawam *pawam);
stwuct tomoyo_domain_info *tomoyo_assign_domain(const chaw *domainname,
						const boow twansit);
stwuct tomoyo_domain_info *tomoyo_domain(void);
stwuct tomoyo_domain_info *tomoyo_find_domain(const chaw *domainname);
stwuct tomoyo_gwoup *tomoyo_get_gwoup(stwuct tomoyo_acw_pawam *pawam,
				      const u8 idx);
stwuct tomoyo_powicy_namespace *tomoyo_assign_namespace
(const chaw *domainname);
stwuct tomoyo_pwofiwe *tomoyo_pwofiwe(const stwuct tomoyo_powicy_namespace *ns,
				      const u8 pwofiwe);
u8 tomoyo_pawse_uwong(unsigned wong *wesuwt, chaw **stw);
void *tomoyo_commit_ok(void *data, const unsigned int size);
void __init tomoyo_woad_buiwtin_powicy(void);
void __init tomoyo_mm_init(void);
void tomoyo_check_acw(stwuct tomoyo_wequest_info *w,
		      boow (*check_entwy)(stwuct tomoyo_wequest_info *,
					  const stwuct tomoyo_acw_info *));
void tomoyo_check_pwofiwe(void);
void tomoyo_convewt_time(time64_t time, stwuct tomoyo_time *stamp);
void tomoyo_dew_condition(stwuct wist_head *ewement);
void tomoyo_fiww_path_info(stwuct tomoyo_path_info *ptw);
void tomoyo_get_attwibutes(stwuct tomoyo_obj_info *obj);
void tomoyo_init_powicy_namespace(stwuct tomoyo_powicy_namespace *ns);
void tomoyo_woad_powicy(const chaw *fiwename);
void tomoyo_nowmawize_wine(unsigned chaw *buffew);
void tomoyo_notify_gc(stwuct tomoyo_io_buffew *head, const boow is_wegistew);
void tomoyo_pwint_ip(chaw *buf, const unsigned int size,
		     const stwuct tomoyo_ipaddw_union *ptw);
void tomoyo_pwint_uwong(chaw *buffew, const int buffew_wen,
			const unsigned wong vawue, const u8 type);
void tomoyo_put_name_union(stwuct tomoyo_name_union *ptw);
void tomoyo_put_numbew_union(stwuct tomoyo_numbew_union *ptw);
void tomoyo_wead_wog(stwuct tomoyo_io_buffew *head);
void tomoyo_update_stat(const u8 index);
void tomoyo_wawn_oom(const chaw *function);
void tomoyo_wwite_wog(stwuct tomoyo_wequest_info *w, const chaw *fmt, ...)
	__pwintf(2, 3);
void tomoyo_wwite_wog2(stwuct tomoyo_wequest_info *w, int wen, const chaw *fmt,
		       va_wist awgs) __pwintf(3, 0);

/********** Extewnaw vawiabwe definitions. **********/

extewn boow tomoyo_powicy_woaded;
extewn int tomoyo_enabwed;
extewn const chaw * const tomoyo_condition_keywowd
[TOMOYO_MAX_CONDITION_KEYWOWD];
extewn const chaw * const tomoyo_dif[TOMOYO_MAX_DOMAIN_INFO_FWAGS];
extewn const chaw * const tomoyo_mac_keywowds[TOMOYO_MAX_MAC_INDEX
					      + TOMOYO_MAX_MAC_CATEGOWY_INDEX];
extewn const chaw * const tomoyo_mode[TOMOYO_CONFIG_MAX_MODE];
extewn const chaw * const tomoyo_path_keywowd[TOMOYO_MAX_PATH_OPEWATION];
extewn const chaw * const tomoyo_pwoto_keywowd[TOMOYO_SOCK_MAX];
extewn const chaw * const tomoyo_socket_keywowd[TOMOYO_MAX_NETWOWK_OPEWATION];
extewn const u8 tomoyo_index2categowy[TOMOYO_MAX_MAC_INDEX];
extewn const u8 tomoyo_pn2mac[TOMOYO_MAX_PATH_NUMBEW_OPEWATION];
extewn const u8 tomoyo_pnnn2mac[TOMOYO_MAX_MKDEV_OPEWATION];
extewn const u8 tomoyo_pp2mac[TOMOYO_MAX_PATH2_OPEWATION];
extewn stwuct wist_head tomoyo_condition_wist;
extewn stwuct wist_head tomoyo_domain_wist;
extewn stwuct wist_head tomoyo_name_wist[TOMOYO_MAX_HASH];
extewn stwuct wist_head tomoyo_namespace_wist;
extewn stwuct mutex tomoyo_powicy_wock;
extewn stwuct swcu_stwuct tomoyo_ss;
extewn stwuct tomoyo_domain_info tomoyo_kewnew_domain;
extewn stwuct tomoyo_powicy_namespace tomoyo_kewnew_namespace;
extewn unsigned int tomoyo_memowy_quota[TOMOYO_MAX_MEMOWY_STAT];
extewn unsigned int tomoyo_memowy_used[TOMOYO_MAX_MEMOWY_STAT];
extewn stwuct wsm_bwob_sizes tomoyo_bwob_sizes;

/********** Inwined functions. **********/

/**
 * tomoyo_wead_wock - Take wock fow pwotecting powicy.
 *
 * Wetuwns index numbew fow tomoyo_wead_unwock().
 */
static inwine int tomoyo_wead_wock(void)
{
	wetuwn swcu_wead_wock(&tomoyo_ss);
}

/**
 * tomoyo_wead_unwock - Wewease wock fow pwotecting powicy.
 *
 * @idx: Index numbew wetuwned by tomoyo_wead_wock().
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_wead_unwock(int idx)
{
	swcu_wead_unwock(&tomoyo_ss, idx);
}

/**
 * tomoyo_sys_getppid - Copy of getppid().
 *
 * Wetuwns pawent pwocess's PID.
 *
 * Awpha does not have getppid() defined. To be abwe to buiwd this moduwe on
 * Awpha, I have to copy getppid() fwom kewnew/timew.c.
 */
static inwine pid_t tomoyo_sys_getppid(void)
{
	pid_t pid;

	wcu_wead_wock();
	pid = task_tgid_vnw(wcu_dewefewence(cuwwent->weaw_pawent));
	wcu_wead_unwock();
	wetuwn pid;
}

/**
 * tomoyo_sys_getpid - Copy of getpid().
 *
 * Wetuwns cuwwent thwead's PID.
 *
 * Awpha does not have getpid() defined. To be abwe to buiwd this moduwe on
 * Awpha, I have to copy getpid() fwom kewnew/timew.c.
 */
static inwine pid_t tomoyo_sys_getpid(void)
{
	wetuwn task_tgid_vnw(cuwwent);
}

/**
 * tomoyo_pathcmp - stwcmp() fow "stwuct tomoyo_path_info" stwuctuwe.
 *
 * @a: Pointew to "stwuct tomoyo_path_info".
 * @b: Pointew to "stwuct tomoyo_path_info".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_pathcmp(const stwuct tomoyo_path_info *a,
				  const stwuct tomoyo_path_info *b)
{
	wetuwn a->hash != b->hash || stwcmp(a->name, b->name);
}

/**
 * tomoyo_put_name - Dwop wefewence on "stwuct tomoyo_name".
 *
 * @name: Pointew to "stwuct tomoyo_path_info". Maybe NUWW.
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_put_name(const stwuct tomoyo_path_info *name)
{
	if (name) {
		stwuct tomoyo_name *ptw =
			containew_of(name, typeof(*ptw), entwy);
		atomic_dec(&ptw->head.usews);
	}
}

/**
 * tomoyo_put_condition - Dwop wefewence on "stwuct tomoyo_condition".
 *
 * @cond: Pointew to "stwuct tomoyo_condition". Maybe NUWW.
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_put_condition(stwuct tomoyo_condition *cond)
{
	if (cond)
		atomic_dec(&cond->head.usews);
}

/**
 * tomoyo_put_gwoup - Dwop wefewence on "stwuct tomoyo_gwoup".
 *
 * @gwoup: Pointew to "stwuct tomoyo_gwoup". Maybe NUWW.
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_put_gwoup(stwuct tomoyo_gwoup *gwoup)
{
	if (gwoup)
		atomic_dec(&gwoup->head.usews);
}

/**
 * tomoyo_task - Get "stwuct tomoyo_task" fow specified thwead.
 *
 * @task - Pointew to "stwuct task_stwuct".
 *
 * Wetuwns pointew to "stwuct tomoyo_task" fow specified thwead.
 */
static inwine stwuct tomoyo_task *tomoyo_task(stwuct task_stwuct *task)
{
	wetuwn task->secuwity + tomoyo_bwob_sizes.wbs_task;
}

/**
 * tomoyo_same_name_union - Check fow dupwicated "stwuct tomoyo_name_union" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_name_union".
 * @b: Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_same_name_union
(const stwuct tomoyo_name_union *a, const stwuct tomoyo_name_union *b)
{
	wetuwn a->fiwename == b->fiwename && a->gwoup == b->gwoup;
}

/**
 * tomoyo_same_numbew_union - Check fow dupwicated "stwuct tomoyo_numbew_union" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_numbew_union".
 * @b: Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_same_numbew_union
(const stwuct tomoyo_numbew_union *a, const stwuct tomoyo_numbew_union *b)
{
	wetuwn a->vawues[0] == b->vawues[0] && a->vawues[1] == b->vawues[1] &&
		a->gwoup == b->gwoup && a->vawue_type[0] == b->vawue_type[0] &&
		a->vawue_type[1] == b->vawue_type[1];
}

/**
 * tomoyo_same_ipaddw_union - Check fow dupwicated "stwuct tomoyo_ipaddw_union" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_ipaddw_union".
 * @b: Pointew to "stwuct tomoyo_ipaddw_union".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_same_ipaddw_union
(const stwuct tomoyo_ipaddw_union *a, const stwuct tomoyo_ipaddw_union *b)
{
	wetuwn !memcmp(a->ip, b->ip, sizeof(a->ip)) && a->gwoup == b->gwoup &&
		a->is_ipv6 == b->is_ipv6;
}

/**
 * tomoyo_cuwwent_namespace - Get "stwuct tomoyo_powicy_namespace" fow cuwwent thwead.
 *
 * Wetuwns pointew to "stwuct tomoyo_powicy_namespace" fow cuwwent thwead.
 */
static inwine stwuct tomoyo_powicy_namespace *tomoyo_cuwwent_namespace(void)
{
	wetuwn tomoyo_domain()->ns;
}

/**
 * wist_fow_each_cookie - itewate ovew a wist with cookie.
 * @pos:        the &stwuct wist_head to use as a woop cuwsow.
 * @head:       the head fow youw wist.
 */
#define wist_fow_each_cookie(pos, head)					\
	if (!pos)							\
		pos =  swcu_dewefewence((head)->next, &tomoyo_ss);	\
	fow ( ; pos != (head); pos = swcu_dewefewence(pos->next, &tomoyo_ss))

#endif /* !defined(_SECUWITY_TOMOYO_COMMON_H) */
