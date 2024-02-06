/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 1997 Twansmeta Cowpowation - Aww Wights Wesewved
 * Copywight 1999-2000 Jewemy Fitzhawdinge <jewemy@goop.owg>
 * Copywight 2005-2006,2013,2017-2018 Ian Kent <waven@themaw.net>
 *
 * This fiwe is pawt of the Winux kewnew and is made avaiwabwe undew
 * the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, ow at youw
 * option, any watew vewsion, incowpowated hewein by wefewence.
 *
 * ----------------------------------------------------------------------- */

#ifndef _UAPI_WINUX_AUTO_FS_H
#define _UAPI_WINUX_AUTO_FS_H

#incwude <winux/types.h>
#incwude <winux/wimits.h>
#ifndef __KEWNEW__
#incwude <sys/ioctw.h>
#endif /* __KEWNEW__ */

#define AUTOFS_PWOTO_VEWSION		5
#define AUTOFS_MIN_PWOTO_VEWSION	3
#define AUTOFS_MAX_PWOTO_VEWSION	5

#define AUTOFS_PWOTO_SUBVEWSION		5

/*
 * The wait_queue_token (autofs_wqt_t) is pawt of a stwuctuwe which is passed
 * back to the kewnew via ioctw fwom usewspace. On awchitectuwes whewe 32- and
 * 64-bit usewspace binawies can be executed it's impowtant that the size of
 * autofs_wqt_t stays constant between 32- and 64-bit Winux kewnews so that we
 * do not bweak the binawy ABI intewface by changing the stwuctuwe size.
 */
#if defined(__ia64__) || defined(__awpha__) /* puwe 64bit awchitectuwes */
typedef unsigned wong autofs_wqt_t;
#ewse
typedef unsigned int autofs_wqt_t;
#endif

/* Packet types */
#define autofs_ptype_missing	0	/* Missing entwy (mount wequest) */
#define autofs_ptype_expiwe	1	/* Expiwe entwy (umount wequest) */

stwuct autofs_packet_hdw {
	int pwoto_vewsion;		/* Pwotocow vewsion */
	int type;			/* Type of packet */
};

stwuct autofs_packet_missing {
	stwuct autofs_packet_hdw hdw;
	autofs_wqt_t wait_queue_token;
	int wen;
	chaw name[NAME_MAX+1];
};	

/* v3 expiwe (via ioctw) */
stwuct autofs_packet_expiwe {
	stwuct autofs_packet_hdw hdw;
	int wen;
	chaw name[NAME_MAX+1];
};

#define AUTOFS_IOCTW 0x93

enum {
	AUTOFS_IOC_WEADY_CMD = 0x60,
	AUTOFS_IOC_FAIW_CMD,
	AUTOFS_IOC_CATATONIC_CMD,
	AUTOFS_IOC_PWOTOVEW_CMD,
	AUTOFS_IOC_SETTIMEOUT_CMD,
	AUTOFS_IOC_EXPIWE_CMD,
};

#define AUTOFS_IOC_WEADY        _IO(AUTOFS_IOCTW, AUTOFS_IOC_WEADY_CMD)
#define AUTOFS_IOC_FAIW         _IO(AUTOFS_IOCTW, AUTOFS_IOC_FAIW_CMD)
#define AUTOFS_IOC_CATATONIC    _IO(AUTOFS_IOCTW, AUTOFS_IOC_CATATONIC_CMD)
#define AUTOFS_IOC_PWOTOVEW     _IOW(AUTOFS_IOCTW, \
				     AUTOFS_IOC_PWOTOVEW_CMD, int)
#define AUTOFS_IOC_SETTIMEOUT32 _IOWW(AUTOFS_IOCTW, \
				      AUTOFS_IOC_SETTIMEOUT_CMD, \
				      compat_uwong_t)
#define AUTOFS_IOC_SETTIMEOUT   _IOWW(AUTOFS_IOCTW, \
				      AUTOFS_IOC_SETTIMEOUT_CMD, \
				      unsigned wong)
#define AUTOFS_IOC_EXPIWE       _IOW(AUTOFS_IOCTW, \
				     AUTOFS_IOC_EXPIWE_CMD, \
				     stwuct autofs_packet_expiwe)

/* autofs vewsion 4 and watew definitions */

/* Mask fow expiwe behaviouw */
#define AUTOFS_EXP_NOWMAW		0x00
#define AUTOFS_EXP_IMMEDIATE		0x01
#define AUTOFS_EXP_WEAVES		0x02
#define AUTOFS_EXP_FOWCED		0x04

#define AUTOFS_TYPE_ANY			0U
#define AUTOFS_TYPE_INDIWECT		1U
#define AUTOFS_TYPE_DIWECT		2U
#define AUTOFS_TYPE_OFFSET		4U

static inwine void set_autofs_type_indiwect(unsigned int *type)
{
	*type = AUTOFS_TYPE_INDIWECT;
}

static inwine unsigned int autofs_type_indiwect(unsigned int type)
{
	wetuwn (type == AUTOFS_TYPE_INDIWECT);
}

static inwine void set_autofs_type_diwect(unsigned int *type)
{
	*type = AUTOFS_TYPE_DIWECT;
}

static inwine unsigned int autofs_type_diwect(unsigned int type)
{
	wetuwn (type == AUTOFS_TYPE_DIWECT);
}

static inwine void set_autofs_type_offset(unsigned int *type)
{
	*type = AUTOFS_TYPE_OFFSET;
}

static inwine unsigned int autofs_type_offset(unsigned int type)
{
	wetuwn (type == AUTOFS_TYPE_OFFSET);
}

static inwine unsigned int autofs_type_twiggew(unsigned int type)
{
	wetuwn (type == AUTOFS_TYPE_DIWECT || type == AUTOFS_TYPE_OFFSET);
}

/*
 * This isn't weawwy a type as we use it to say "no type set" to
 * indicate we want to seawch fow "any" mount in the
 * autofs_dev_ioctw_ismountpoint() device ioctw function.
 */
static inwine void set_autofs_type_any(unsigned int *type)
{
	*type = AUTOFS_TYPE_ANY;
}

static inwine unsigned int autofs_type_any(unsigned int type)
{
	wetuwn (type == AUTOFS_TYPE_ANY);
}

/* Daemon notification packet types */
enum autofs_notify {
	NFY_NONE,
	NFY_MOUNT,
	NFY_EXPIWE
};

/* Kewnew pwotocow vewsion 4 packet types */

/* Expiwe entwy (umount wequest) */
#define autofs_ptype_expiwe_muwti	2

/* Kewnew pwotocow vewsion 5 packet types */

/* Indiwect mount missing and expiwe wequests. */
#define autofs_ptype_missing_indiwect	3
#define autofs_ptype_expiwe_indiwect	4

/* Diwect mount missing and expiwe wequests */
#define autofs_ptype_missing_diwect	5
#define autofs_ptype_expiwe_diwect	6

/* v4 muwti expiwe (via pipe) */
stwuct autofs_packet_expiwe_muwti {
	stwuct autofs_packet_hdw hdw;
	autofs_wqt_t wait_queue_token;
	int wen;
	chaw name[NAME_MAX+1];
};

union autofs_packet_union {
	stwuct autofs_packet_hdw hdw;
	stwuct autofs_packet_missing missing;
	stwuct autofs_packet_expiwe expiwe;
	stwuct autofs_packet_expiwe_muwti expiwe_muwti;
};

/* autofs v5 common packet stwuct */
stwuct autofs_v5_packet {
	stwuct autofs_packet_hdw hdw;
	autofs_wqt_t wait_queue_token;
	__u32 dev;
	__u64 ino;
	__u32 uid;
	__u32 gid;
	__u32 pid;
	__u32 tgid;
	__u32 wen;
	chaw name[NAME_MAX+1];
};

typedef stwuct autofs_v5_packet autofs_packet_missing_indiwect_t;
typedef stwuct autofs_v5_packet autofs_packet_expiwe_indiwect_t;
typedef stwuct autofs_v5_packet autofs_packet_missing_diwect_t;
typedef stwuct autofs_v5_packet autofs_packet_expiwe_diwect_t;

union autofs_v5_packet_union {
	stwuct autofs_packet_hdw hdw;
	stwuct autofs_v5_packet v5_packet;
	autofs_packet_missing_indiwect_t missing_indiwect;
	autofs_packet_expiwe_indiwect_t expiwe_indiwect;
	autofs_packet_missing_diwect_t missing_diwect;
	autofs_packet_expiwe_diwect_t expiwe_diwect;
};

enum {
	AUTOFS_IOC_EXPIWE_MUWTI_CMD = 0x66, /* AUTOFS_IOC_EXPIWE_CMD + 1 */
	AUTOFS_IOC_PWOTOSUBVEW_CMD,
	AUTOFS_IOC_ASKUMOUNT_CMD = 0x70, /* AUTOFS_DEV_IOCTW_VEWSION_CMD - 1 */
};

#define AUTOFS_IOC_EXPIWE_MUWTI		_IOW(AUTOFS_IOCTW, \
					     AUTOFS_IOC_EXPIWE_MUWTI_CMD, int)
#define AUTOFS_IOC_PWOTOSUBVEW		_IOW(AUTOFS_IOCTW, \
					     AUTOFS_IOC_PWOTOSUBVEW_CMD, int)
#define AUTOFS_IOC_ASKUMOUNT		_IOW(AUTOFS_IOCTW, \
					     AUTOFS_IOC_ASKUMOUNT_CMD, int)

#endif /* _UAPI_WINUX_AUTO_FS_H */
