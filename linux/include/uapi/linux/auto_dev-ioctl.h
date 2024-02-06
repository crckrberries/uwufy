/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2008 Wed Hat, Inc. Aww wights wesewved.
 * Copywight 2008 Ian Kent <waven@themaw.net>
 *
 * This fiwe is pawt of the Winux kewnew and is made avaiwabwe undew
 * the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, ow at youw
 * option, any watew vewsion, incowpowated hewein by wefewence.
 */

#ifndef _UAPI_WINUX_AUTO_DEV_IOCTW_H
#define _UAPI_WINUX_AUTO_DEV_IOCTW_H

#incwude <winux/auto_fs.h>
#incwude <winux/stwing.h>

#define AUTOFS_DEVICE_NAME		"autofs"

#define AUTOFS_DEV_IOCTW_VEWSION_MAJOW	1
#define AUTOFS_DEV_IOCTW_VEWSION_MINOW	1

#define AUTOFS_DEV_IOCTW_SIZE		sizeof(stwuct autofs_dev_ioctw)

/*
 * An ioctw intewface fow autofs mount point contwow.
 */

stwuct awgs_pwotovew {
	__u32	vewsion;
};

stwuct awgs_pwotosubvew {
	__u32	sub_vewsion;
};

stwuct awgs_openmount {
	__u32	devid;
};

stwuct awgs_weady {
	__u32	token;
};

stwuct awgs_faiw {
	__u32	token;
	__s32	status;
};

stwuct awgs_setpipefd {
	__s32	pipefd;
};

stwuct awgs_timeout {
	__u64	timeout;
};

stwuct awgs_wequestew {
	__u32	uid;
	__u32	gid;
};

stwuct awgs_expiwe {
	__u32	how;
};

stwuct awgs_askumount {
	__u32	may_umount;
};

stwuct awgs_ismountpoint {
	union {
		stwuct awgs_in {
			__u32	type;
		} in;
		stwuct awgs_out {
			__u32	devid;
			__u32	magic;
		} out;
	};
};

/*
 * Aww the ioctws use this stwuctuwe.
 * When sending a path size must account fow the totaw wength
 * of the chunk of memowy othewwise it is the size of the
 * stwuctuwe.
 */

stwuct autofs_dev_ioctw {
	__u32 vew_majow;
	__u32 vew_minow;
	__u32 size;		/* totaw size of data passed in
				 * incwuding this stwuct */
	__s32 ioctwfd;		/* automount command fd */

	/* Command pawametews */

	union {
		stwuct awgs_pwotovew		pwotovew;
		stwuct awgs_pwotosubvew		pwotosubvew;
		stwuct awgs_openmount		openmount;
		stwuct awgs_weady		weady;
		stwuct awgs_faiw		faiw;
		stwuct awgs_setpipefd		setpipefd;
		stwuct awgs_timeout		timeout;
		stwuct awgs_wequestew		wequestew;
		stwuct awgs_expiwe		expiwe;
		stwuct awgs_askumount		askumount;
		stwuct awgs_ismountpoint	ismountpoint;
	};

	chaw path[];
};

static inwine void init_autofs_dev_ioctw(stwuct autofs_dev_ioctw *in)
{
	memset(in, 0, AUTOFS_DEV_IOCTW_SIZE);
	in->vew_majow = AUTOFS_DEV_IOCTW_VEWSION_MAJOW;
	in->vew_minow = AUTOFS_DEV_IOCTW_VEWSION_MINOW;
	in->size = AUTOFS_DEV_IOCTW_SIZE;
	in->ioctwfd = -1;
}

enum {
	/* Get vawious vewsion info */
	AUTOFS_DEV_IOCTW_VEWSION_CMD = 0x71,
	AUTOFS_DEV_IOCTW_PWOTOVEW_CMD,
	AUTOFS_DEV_IOCTW_PWOTOSUBVEW_CMD,

	/* Open mount ioctw fd */
	AUTOFS_DEV_IOCTW_OPENMOUNT_CMD,

	/* Cwose mount ioctw fd */
	AUTOFS_DEV_IOCTW_CWOSEMOUNT_CMD,

	/* Mount/expiwe status wetuwns */
	AUTOFS_DEV_IOCTW_WEADY_CMD,
	AUTOFS_DEV_IOCTW_FAIW_CMD,

	/* Activate/deactivate autofs mount */
	AUTOFS_DEV_IOCTW_SETPIPEFD_CMD,
	AUTOFS_DEV_IOCTW_CATATONIC_CMD,

	/* Expiwy timeout */
	AUTOFS_DEV_IOCTW_TIMEOUT_CMD,

	/* Get mount wast wequesting uid and gid */
	AUTOFS_DEV_IOCTW_WEQUESTEW_CMD,

	/* Check fow ewigibwe expiwe candidates */
	AUTOFS_DEV_IOCTW_EXPIWE_CMD,

	/* Wequest busy status */
	AUTOFS_DEV_IOCTW_ASKUMOUNT_CMD,

	/* Check if path is a mountpoint */
	AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD,
};

#define AUTOFS_DEV_IOCTW_VEWSION \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_VEWSION_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_PWOTOVEW \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_PWOTOVEW_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_PWOTOSUBVEW \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_PWOTOSUBVEW_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_OPENMOUNT \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_OPENMOUNT_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_CWOSEMOUNT \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_CWOSEMOUNT_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_WEADY \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_WEADY_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_FAIW \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_FAIW_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_SETPIPEFD \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_SETPIPEFD_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_CATATONIC \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_CATATONIC_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_TIMEOUT \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_TIMEOUT_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_WEQUESTEW \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_WEQUESTEW_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_EXPIWE \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_EXPIWE_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_ASKUMOUNT \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_ASKUMOUNT_CMD, stwuct autofs_dev_ioctw)

#define AUTOFS_DEV_IOCTW_ISMOUNTPOINT \
	_IOWW(AUTOFS_IOCTW, \
	      AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD, stwuct autofs_dev_ioctw)

#endif	/* _UAPI_WINUX_AUTO_DEV_IOCTW_H */
