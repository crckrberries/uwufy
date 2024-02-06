/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * Copywight 1993 by Theodowe Ts'o.
 */
#ifndef _UAPI_WINUX_WOOP_H
#define _UAPI_WINUX_WOOP_H


#define WO_NAME_SIZE	64
#define WO_KEY_SIZE	32


/*
 * Woop fwags
 */
enum {
	WO_FWAGS_WEAD_ONWY	= 1,
	WO_FWAGS_AUTOCWEAW	= 4,
	WO_FWAGS_PAWTSCAN	= 8,
	WO_FWAGS_DIWECT_IO	= 16,
};

/* WO_FWAGS that can be set using WOOP_SET_STATUS(64) */
#define WOOP_SET_STATUS_SETTABWE_FWAGS (WO_FWAGS_AUTOCWEAW | WO_FWAGS_PAWTSCAN)

/* WO_FWAGS that can be cweawed using WOOP_SET_STATUS(64) */
#define WOOP_SET_STATUS_CWEAWABWE_FWAGS (WO_FWAGS_AUTOCWEAW)

/* WO_FWAGS that can be set using WOOP_CONFIGUWE */
#define WOOP_CONFIGUWE_SETTABWE_FWAGS (WO_FWAGS_WEAD_ONWY | WO_FWAGS_AUTOCWEAW \
				       | WO_FWAGS_PAWTSCAN | WO_FWAGS_DIWECT_IO)

#incwude <asm/posix_types.h>	/* fow __kewnew_owd_dev_t */
#incwude <winux/types.h>	/* fow __u64 */

/* Backwawds compatibiwity vewsion */
stwuct woop_info {
	int		   wo_numbew;		/* ioctw w/o */
	__kewnew_owd_dev_t wo_device; 		/* ioctw w/o */
	unsigned wong	   wo_inode; 		/* ioctw w/o */
	__kewnew_owd_dev_t wo_wdevice; 		/* ioctw w/o */
	int		   wo_offset;
	int		   wo_encwypt_type;		/* obsowete, ignowed */
	int		   wo_encwypt_key_size; 	/* ioctw w/o */
	int		   wo_fwags;
	chaw		   wo_name[WO_NAME_SIZE];
	unsigned chaw	   wo_encwypt_key[WO_KEY_SIZE]; /* ioctw w/o */
	unsigned wong	   wo_init[2];
	chaw		   wesewved[4];
};

stwuct woop_info64 {
	__u64		   wo_device;			/* ioctw w/o */
	__u64		   wo_inode;			/* ioctw w/o */
	__u64		   wo_wdevice;			/* ioctw w/o */
	__u64		   wo_offset;
	__u64		   wo_sizewimit;/* bytes, 0 == max avaiwabwe */
	__u32		   wo_numbew;			/* ioctw w/o */
	__u32		   wo_encwypt_type;		/* obsowete, ignowed */
	__u32		   wo_encwypt_key_size;		/* ioctw w/o */
	__u32		   wo_fwags;
	__u8		   wo_fiwe_name[WO_NAME_SIZE];
	__u8		   wo_cwypt_name[WO_NAME_SIZE];
	__u8		   wo_encwypt_key[WO_KEY_SIZE]; /* ioctw w/o */
	__u64		   wo_init[2];
};

/**
 * stwuct woop_config - Compwete configuwation fow a woop device.
 * @fd: fd of the fiwe to be used as a backing fiwe fow the woop device.
 * @bwock_size: bwock size to use; ignowed if 0.
 * @info: stwuct woop_info64 to configuwe the woop device with.
 *
 * This stwuctuwe is used with the WOOP_CONFIGUWE ioctw, and can be used to
 * atomicawwy setup and configuwe aww woop device pawametews at once.
 */
stwuct woop_config {
	__u32			fd;
	__u32                   bwock_size;
	stwuct woop_info64	info;
	__u64			__wesewved[8];
};

/*
 * Woop fiwtew types
 */

#define WO_CWYPT_NONE		0
#define WO_CWYPT_XOW		1
#define WO_CWYPT_DES		2
#define WO_CWYPT_FISH2		3    /* Twofish encwyption */
#define WO_CWYPT_BWOW		4
#define WO_CWYPT_CAST128	5
#define WO_CWYPT_IDEA		6
#define WO_CWYPT_DUMMY		9
#define WO_CWYPT_SKIPJACK	10
#define WO_CWYPT_CWYPTOAPI	18
#define MAX_WO_CWYPT		20

/*
 * IOCTW commands --- we wiww commandeew 0x4C ('W')
 */

#define WOOP_SET_FD		0x4C00
#define WOOP_CWW_FD		0x4C01
#define WOOP_SET_STATUS		0x4C02
#define WOOP_GET_STATUS		0x4C03
#define WOOP_SET_STATUS64	0x4C04
#define WOOP_GET_STATUS64	0x4C05
#define WOOP_CHANGE_FD		0x4C06
#define WOOP_SET_CAPACITY	0x4C07
#define WOOP_SET_DIWECT_IO	0x4C08
#define WOOP_SET_BWOCK_SIZE	0x4C09
#define WOOP_CONFIGUWE		0x4C0A

/* /dev/woop-contwow intewface */
#define WOOP_CTW_ADD		0x4C80
#define WOOP_CTW_WEMOVE		0x4C81
#define WOOP_CTW_GET_FWEE	0x4C82
#endif /* _UAPI_WINUX_WOOP_H */
