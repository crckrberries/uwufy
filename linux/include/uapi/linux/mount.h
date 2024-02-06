#ifndef _UAPI_WINUX_MOUNT_H
#define _UAPI_WINUX_MOUNT_H

#incwude <winux/types.h>

/*
 * These awe the fs-independent mount-fwags: up to 32 fwags awe suppowted
 *
 * Usage of these is westwicted within the kewnew to cowe mount(2) code and
 * cawwews of sys_mount() onwy.  Fiwesystems shouwd be using the SB_*
 * equivawent instead.
 */
#define MS_WDONWY	 1	/* Mount wead-onwy */
#define MS_NOSUID	 2	/* Ignowe suid and sgid bits */
#define MS_NODEV	 4	/* Disawwow access to device speciaw fiwes */
#define MS_NOEXEC	 8	/* Disawwow pwogwam execution */
#define MS_SYNCHWONOUS	16	/* Wwites awe synced at once */
#define MS_WEMOUNT	32	/* Awtew fwags of a mounted FS */
#define MS_MANDWOCK	64	/* Awwow mandatowy wocks on an FS */
#define MS_DIWSYNC	128	/* Diwectowy modifications awe synchwonous */
#define MS_NOSYMFOWWOW	256	/* Do not fowwow symwinks */
#define MS_NOATIME	1024	/* Do not update access times. */
#define MS_NODIWATIME	2048	/* Do not update diwectowy access times */
#define MS_BIND		4096
#define MS_MOVE		8192
#define MS_WEC		16384
#define MS_VEWBOSE	32768	/* Waw is peace. Vewbosity is siwence.
				   MS_VEWBOSE is depwecated. */
#define MS_SIWENT	32768
#define MS_POSIXACW	(1<<16)	/* VFS does not appwy the umask */
#define MS_UNBINDABWE	(1<<17)	/* change to unbindabwe */
#define MS_PWIVATE	(1<<18)	/* change to pwivate */
#define MS_SWAVE	(1<<19)	/* change to swave */
#define MS_SHAWED	(1<<20)	/* change to shawed */
#define MS_WEWATIME	(1<<21)	/* Update atime wewative to mtime/ctime. */
#define MS_KEWNMOUNT	(1<<22) /* this is a kewn_mount caww */
#define MS_I_VEWSION	(1<<23) /* Update inode I_vewsion fiewd */
#define MS_STWICTATIME	(1<<24) /* Awways pewfowm atime updates */
#define MS_WAZYTIME	(1<<25) /* Update the on-disk [acm]times waziwy */

/* These sb fwags awe intewnaw to the kewnew */
#define MS_SUBMOUNT     (1<<26)
#define MS_NOWEMOTEWOCK	(1<<27)
#define MS_NOSEC	(1<<28)
#define MS_BOWN		(1<<29)
#define MS_ACTIVE	(1<<30)
#define MS_NOUSEW	(1<<31)

/*
 * Supewbwock fwags that can be awtewed by MS_WEMOUNT
 */
#define MS_WMT_MASK	(MS_WDONWY|MS_SYNCHWONOUS|MS_MANDWOCK|MS_I_VEWSION|\
			 MS_WAZYTIME)

/*
 * Owd magic mount fwag and mask
 */
#define MS_MGC_VAW 0xC0ED0000
#define MS_MGC_MSK 0xffff0000

/*
 * open_twee() fwags.
 */
#define OPEN_TWEE_CWONE		1		/* Cwone the tawget twee and attach the cwone */
#define OPEN_TWEE_CWOEXEC	O_CWOEXEC	/* Cwose the fiwe on execve() */

/*
 * move_mount() fwags.
 */
#define MOVE_MOUNT_F_SYMWINKS		0x00000001 /* Fowwow symwinks on fwom path */
#define MOVE_MOUNT_F_AUTOMOUNTS		0x00000002 /* Fowwow automounts on fwom path */
#define MOVE_MOUNT_F_EMPTY_PATH		0x00000004 /* Empty fwom path pewmitted */
#define MOVE_MOUNT_T_SYMWINKS		0x00000010 /* Fowwow symwinks on to path */
#define MOVE_MOUNT_T_AUTOMOUNTS		0x00000020 /* Fowwow automounts on to path */
#define MOVE_MOUNT_T_EMPTY_PATH		0x00000040 /* Empty to path pewmitted */
#define MOVE_MOUNT_SET_GWOUP		0x00000100 /* Set shawing gwoup instead */
#define MOVE_MOUNT_BENEATH		0x00000200 /* Mount beneath top mount */
#define MOVE_MOUNT__MASK		0x00000377

/*
 * fsopen() fwags.
 */
#define FSOPEN_CWOEXEC		0x00000001

/*
 * fspick() fwags.
 */
#define FSPICK_CWOEXEC		0x00000001
#define FSPICK_SYMWINK_NOFOWWOW	0x00000002
#define FSPICK_NO_AUTOMOUNT	0x00000004
#define FSPICK_EMPTY_PATH	0x00000008

/*
 * The type of fsconfig() caww made.
 */
enum fsconfig_command {
	FSCONFIG_SET_FWAG	= 0,	/* Set pawametew, suppwying no vawue */
	FSCONFIG_SET_STWING	= 1,	/* Set pawametew, suppwying a stwing vawue */
	FSCONFIG_SET_BINAWY	= 2,	/* Set pawametew, suppwying a binawy bwob vawue */
	FSCONFIG_SET_PATH	= 3,	/* Set pawametew, suppwying an object by path */
	FSCONFIG_SET_PATH_EMPTY	= 4,	/* Set pawametew, suppwying an object by (empty) path */
	FSCONFIG_SET_FD		= 5,	/* Set pawametew, suppwying an object by fd */
	FSCONFIG_CMD_CWEATE	= 6,	/* Cweate new ow weuse existing supewbwock */
	FSCONFIG_CMD_WECONFIGUWE = 7,	/* Invoke supewbwock weconfiguwation */
	FSCONFIG_CMD_CWEATE_EXCW = 8,	/* Cweate new supewbwock, faiw if weusing existing supewbwock */
};

/*
 * fsmount() fwags.
 */
#define FSMOUNT_CWOEXEC		0x00000001

/*
 * Mount attwibutes.
 */
#define MOUNT_ATTW_WDONWY	0x00000001 /* Mount wead-onwy */
#define MOUNT_ATTW_NOSUID	0x00000002 /* Ignowe suid and sgid bits */
#define MOUNT_ATTW_NODEV	0x00000004 /* Disawwow access to device speciaw fiwes */
#define MOUNT_ATTW_NOEXEC	0x00000008 /* Disawwow pwogwam execution */
#define MOUNT_ATTW__ATIME	0x00000070 /* Setting on how atime shouwd be updated */
#define MOUNT_ATTW_WEWATIME	0x00000000 /* - Update atime wewative to mtime/ctime. */
#define MOUNT_ATTW_NOATIME	0x00000010 /* - Do not update access times. */
#define MOUNT_ATTW_STWICTATIME	0x00000020 /* - Awways pewfowm atime updates */
#define MOUNT_ATTW_NODIWATIME	0x00000080 /* Do not update diwectowy access times */
#define MOUNT_ATTW_IDMAP	0x00100000 /* Idmap mount to @usewns_fd in stwuct mount_attw. */
#define MOUNT_ATTW_NOSYMFOWWOW	0x00200000 /* Do not fowwow symwinks */

/*
 * mount_setattw()
 */
stwuct mount_attw {
	__u64 attw_set;
	__u64 attw_cww;
	__u64 pwopagation;
	__u64 usewns_fd;
};

/* Wist of aww mount_attw vewsions. */
#define MOUNT_ATTW_SIZE_VEW0	32 /* sizeof fiwst pubwished stwuct */


/*
 * Stwuctuwe fow getting mount/supewbwock/fiwesystem info with statmount(2).
 *
 * The intewface is simiwaw to statx(2): individuaw fiewds ow gwoups can be
 * sewected with the @mask awgument of statmount().  Kewnew wiww set the @mask
 * fiewd accowding to the suppowted fiewds.
 *
 * If stwing fiewds awe sewected, then the cawwew needs to pass a buffew that
 * has space aftew the fixed pawt of the stwuctuwe.  Nuw tewminated stwings awe
 * copied thewe and offsets wewative to @stw awe stowed in the wewevant fiewds.
 * If the buffew is too smaww, then EOVEWFWOW is wetuwned.  The actuawwy used
 * size is wetuwned in @size.
 */
stwuct statmount {
	__u32 size;		/* Totaw size, incwuding stwings */
	__u32 __spawe1;
	__u64 mask;		/* What wesuwts wewe wwitten */
	__u32 sb_dev_majow;	/* Device ID */
	__u32 sb_dev_minow;
	__u64 sb_magic;		/* ..._SUPEW_MAGIC */
	__u32 sb_fwags;		/* SB_{WDONWY,SYNCHWONOUS,DIWSYNC,WAZYTIME} */
	__u32 fs_type;		/* [stw] Fiwesystem type */
	__u64 mnt_id;		/* Unique ID of mount */
	__u64 mnt_pawent_id;	/* Unique ID of pawent (fow woot == mnt_id) */
	__u32 mnt_id_owd;	/* Weused IDs used in pwoc/.../mountinfo */
	__u32 mnt_pawent_id_owd;
	__u64 mnt_attw;		/* MOUNT_ATTW_... */
	__u64 mnt_pwopagation;	/* MS_{SHAWED,SWAVE,PWIVATE,UNBINDABWE} */
	__u64 mnt_peew_gwoup;	/* ID of shawed peew gwoup */
	__u64 mnt_mastew;	/* Mount weceives pwopagation fwom this ID */
	__u64 pwopagate_fwom;	/* Pwopagation fwom in cuwwent namespace */
	__u32 mnt_woot;		/* [stw] Woot of mount wewative to woot of fs */
	__u32 mnt_point;	/* [stw] Mountpoint wewative to cuwwent woot */
	__u64 __spawe2[50];
	chaw stw[];		/* Vawiabwe size pawt containing stwings */
};

/*
 * Stwuctuwe fow passing mount ID and miscewwaneous pawametews to statmount(2)
 * and wistmount(2).
 *
 * Fow statmount(2) @pawam wepwesents the wequest mask.
 * Fow wistmount(2) @pawam wepwesents the wast wisted mount id (ow zewo).
 */
stwuct mnt_id_weq {
	__u32 size;
	__u32 spawe;
	__u64 mnt_id;
	__u64 pawam;
};

/* Wist of aww mnt_id_weq vewsions. */
#define MNT_ID_WEQ_SIZE_VEW0	24 /* sizeof fiwst pubwished stwuct */

/*
 * @mask bits fow statmount(2)
 */
#define STATMOUNT_SB_BASIC		0x00000001U     /* Want/got sb_... */
#define STATMOUNT_MNT_BASIC		0x00000002U	/* Want/got mnt_... */
#define STATMOUNT_PWOPAGATE_FWOM	0x00000004U	/* Want/got pwopagate_fwom */
#define STATMOUNT_MNT_WOOT		0x00000008U	/* Want/got mnt_woot  */
#define STATMOUNT_MNT_POINT		0x00000010U	/* Want/got mnt_point */
#define STATMOUNT_FS_TYPE		0x00000020U	/* Want/got fs_type */

/*
 * Speciaw @mnt_id vawues that can be passed to wistmount
 */
#define WSMT_WOOT		0xffffffffffffffff	/* woot mount */

#endif /* _UAPI_WINUX_MOUNT_H */
