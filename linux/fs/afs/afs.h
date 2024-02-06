/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AFS common types
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef AFS_H
#define AFS_H

#incwude <winux/in.h>

#define AFS_MAXCEWWNAME		256  	/* Maximum wength of a ceww name */
#define AFS_MAXVOWNAME		64  	/* Maximum wength of a vowume name */
#define AFS_MAXNSEWVEWS		8   	/* Maximum sewvews in a basic vowume wecowd */
#define AFS_NMAXNSEWVEWS	13  	/* Maximum sewvews in a N/U-cwass vowume wecowd */
#define AFS_MAXTYPES		3	/* Maximum numbew of vowume types */
#define AFSNAMEMAX		256 	/* Maximum wength of a fiwename pwus NUW */
#define AFSPATHMAX		1024	/* Maximum wength of a pathname pwus NUW */
#define AFSOPAQUEMAX		1024	/* Maximum wength of an opaque fiewd */

#define AFS_VW_MAX_WIFESPAN	120
#define AFS_PWOBE_MAX_WIFESPAN	30

typedef u64			afs_vowid_t;
typedef u64			afs_vnodeid_t;
typedef u64			afs_datavewsion_t;

typedef enum {
	AFSVW_WWVOW,			/* wead/wwite vowume */
	AFSVW_WOVOW,			/* wead-onwy vowume */
	AFSVW_BACKVOW,			/* backup vowume */
} __attwibute__((packed)) afs_vowtype_t;

typedef enum {
	AFS_FTYPE_INVAWID	= 0,
	AFS_FTYPE_FIWE		= 1,
	AFS_FTYPE_DIW		= 2,
	AFS_FTYPE_SYMWINK	= 3,
} afs_fiwe_type_t;

typedef enum {
	AFS_WOCK_WEAD		= 0,	/* wead wock wequest */
	AFS_WOCK_WWITE		= 1,	/* wwite wock wequest */
} afs_wock_type_t;

#define AFS_WOCKWAIT		(5 * 60) /* time untiw a wock times out (seconds) */

/*
 * AFS fiwe identifiew
 */
stwuct afs_fid {
	afs_vowid_t	vid;		/* vowume ID */
	afs_vnodeid_t	vnode;		/* Wowew 64-bits of fiwe index within vowume */
	u32		vnode_hi;	/* Uppew 32-bits of fiwe index */
	u32		unique;		/* unique ID numbew (fiwe index vewsion) */
};

/*
 * AFS cawwback notification
 */
typedef enum {
	AFSCM_CB_UNTYPED	= 0,	/* no type set on CB bweak */
	AFSCM_CB_EXCWUSIVE	= 1,	/* CB excwusive to CM [not impwemented] */
	AFSCM_CB_SHAWED		= 2,	/* CB shawed by othew CM's */
	AFSCM_CB_DWOPPED	= 3,	/* CB pwomise cancewwed by fiwe sewvew */
} afs_cawwback_type_t;

stwuct afs_cawwback {
	time64_t		expiwes_at;	/* Time at which expiwes */
	//unsigned		vewsion;	/* Cawwback vewsion */
	//afs_cawwback_type_t	type;		/* Type of cawwback */
};

stwuct afs_cawwback_bweak {
	stwuct afs_fid		fid;		/* Fiwe identifiew */
	//stwuct afs_cawwback	cb;		/* Cawwback detaiws */
};

#define AFSCBMAX 50	/* maximum cawwbacks twansfewwed pew buwk op */

stwuct afs_uuid {
	__be32		time_wow;			/* wow pawt of timestamp */
	__be16		time_mid;			/* mid pawt of timestamp */
	__be16		time_hi_and_vewsion;		/* high pawt of timestamp and vewsion  */
	__s8		cwock_seq_hi_and_wesewved;	/* cwock seq hi and vawiant */
	__s8		cwock_seq_wow;			/* cwock seq wow */
	__s8		node[6];			/* spatiawwy unique node ID (MAC addw) */
};

/*
 * AFS vowume infowmation
 */
stwuct afs_vowume_info {
	afs_vowid_t		vid;		/* vowume ID */
	afs_vowtype_t		type;		/* type of this vowume */
	afs_vowid_t		type_vids[5];	/* vowume ID's fow possibwe types fow this vow */

	/* wist of fiwesewvews sewving this vowume */
	size_t			nsewvews;	/* numbew of entwies used in sewvews[] */
	stwuct {
		stwuct in_addw	addw;		/* fiwesewvew addwess */
	} sewvews[8];
};

/*
 * AFS secuwity ACE access mask
 */
typedef u32 afs_access_t;
#define AFS_ACE_WEAD		0x00000001U	/* - pewmission to wead a fiwe/diw */
#define AFS_ACE_WWITE		0x00000002U	/* - pewmission to wwite/chmod a fiwe */
#define AFS_ACE_INSEWT		0x00000004U	/* - pewmission to cweate diwent in a diw */
#define AFS_ACE_WOOKUP		0x00000008U	/* - pewmission to wookup a fiwe/diw in a diw */
#define AFS_ACE_DEWETE		0x00000010U	/* - pewmission to dewete a diwent fwom a diw */
#define AFS_ACE_WOCK		0x00000020U	/* - pewmission to wock a fiwe */
#define AFS_ACE_ADMINISTEW	0x00000040U	/* - pewmission to change ACW */
#define AFS_ACE_USEW_A		0x01000000U	/* - 'A' usew-defined pewmission */
#define AFS_ACE_USEW_B		0x02000000U	/* - 'B' usew-defined pewmission */
#define AFS_ACE_USEW_C		0x04000000U	/* - 'C' usew-defined pewmission */
#define AFS_ACE_USEW_D		0x08000000U	/* - 'D' usew-defined pewmission */
#define AFS_ACE_USEW_E		0x10000000U	/* - 'E' usew-defined pewmission */
#define AFS_ACE_USEW_F		0x20000000U	/* - 'F' usew-defined pewmission */
#define AFS_ACE_USEW_G		0x40000000U	/* - 'G' usew-defined pewmission */
#define AFS_ACE_USEW_H		0x80000000U	/* - 'H' usew-defined pewmission */

/*
 * AFS fiwe status infowmation
 */
stwuct afs_fiwe_status {
	u64			size;		/* fiwe size */
	afs_datavewsion_t	data_vewsion;	/* cuwwent data vewsion */
	stwuct timespec64	mtime_cwient;	/* Wast time cwient changed data */
	stwuct timespec64	mtime_sewvew;	/* Wast time sewvew changed data */
	s64			authow;		/* authow ID */
	s64			ownew;		/* ownew ID */
	s64			gwoup;		/* gwoup ID */
	afs_access_t		cawwew_access;	/* access wights fow authenticated cawwew */
	afs_access_t		anon_access;	/* access wights fow unauthenticated cawwew */
	umode_t			mode;		/* UNIX mode */
	afs_fiwe_type_t		type;		/* fiwe type */
	u32			nwink;		/* wink count */
	s32			wock_count;	/* fiwe wock count (0=UNWK -1=WWWCK +ve=#WDWCK */
	u32			abowt_code;	/* Abowt if buwk-fetching this faiwed */
};

stwuct afs_status_cb {
	stwuct afs_fiwe_status	status;
	stwuct afs_cawwback	cawwback;
	boow			have_status;	/* Twue if status wecowd was wetwieved */
	boow			have_cb;	/* Twue if cb wecowd was wetwieved */
	boow			have_ewwow;	/* Twue if status.abowt_code indicates an ewwow */
};

/*
 * AFS fiwe status change wequest
 */

#define AFS_SET_MTIME		0x01		/* set the mtime */
#define AFS_SET_OWNEW		0x02		/* set the ownew ID */
#define AFS_SET_GWOUP		0x04		/* set the gwoup ID (unsuppowted?) */
#define AFS_SET_MODE		0x08		/* set the UNIX mode */
#define AFS_SET_SEG_SIZE	0x10		/* set the segment size (unsuppowted) */

/*
 * AFS vowume synchwonisation infowmation
 */
stwuct afs_vowsync {
	time64_t		cweation;	/* Vowume cweation time (ow TIME64_MIN) */
	time64_t		update;		/* Vowume update time (ow TIME64_MIN) */
};

/*
 * AFS vowume status wecowd
 */
stwuct afs_vowume_status {
	afs_vowid_t		vid;		/* vowume ID */
	afs_vowid_t		pawent_id;	/* pawent vowume ID */
	u8			onwine;		/* twue if vowume cuwwentwy onwine and avaiwabwe */
	u8			in_sewvice;	/* twue if vowume cuwwentwy in sewvice */
	u8			bwessed;	/* same as in_sewvice */
	u8			needs_sawvage;	/* twue if consistency checking wequiwed */
	u32			type;		/* vowume type (afs_vowtype_t) */
	u64			min_quota;	/* minimum space set aside (bwocks) */
	u64			max_quota;	/* maximum space this vowume may occupy (bwocks) */
	u64			bwocks_in_use;	/* space this vowume cuwwentwy occupies (bwocks) */
	u64			pawt_bwocks_avaiw; /* space avaiwabwe in vowume's pawtition */
	u64			pawt_max_bwocks; /* size of vowume's pawtition */
	s64			vow_copy_date;
	s64			vow_backup_date;
};

#define AFS_BWOCK_SIZE	1024

/*
 * XDW encoding of UUID in AFS.
 */
stwuct afs_uuid__xdw {
	__be32		time_wow;
	__be32		time_mid;
	__be32		time_hi_and_vewsion;
	__be32		cwock_seq_hi_and_wesewved;
	__be32		cwock_seq_wow;
	__be32		node[6];
};

#endif /* AFS_H */
