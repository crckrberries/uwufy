/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic
 * Wicense v2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic
 * Wicense awong with this pwogwam; if not, wwite to the
 * Fwee Softwawe Foundation, Inc., 59 Tempwe Pwace - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#ifndef _UAPI_WINUX_BTWFS_H
#define _UAPI_WINUX_BTWFS_H

#ifdef __cpwuspwus
extewn "C" {
#endif

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/fs.h>

#define BTWFS_IOCTW_MAGIC 0x94
#define BTWFS_VOW_NAME_MAX 255
#define BTWFS_WABEW_SIZE 256

/* this shouwd be 4k */
#define BTWFS_PATH_NAME_MAX 4087
stwuct btwfs_ioctw_vow_awgs {
	__s64 fd;
	chaw name[BTWFS_PATH_NAME_MAX + 1];
};

#define BTWFS_DEVICE_PATH_NAME_MAX	1024
#define BTWFS_SUBVOW_NAME_MAX 		4039

#ifndef __KEWNEW__
/* Depwecated since 5.7 */
# define BTWFS_SUBVOW_CWEATE_ASYNC	(1UWW << 0)
#endif
#define BTWFS_SUBVOW_WDONWY		(1UWW << 1)
#define BTWFS_SUBVOW_QGWOUP_INHEWIT	(1UWW << 2)

#define BTWFS_DEVICE_SPEC_BY_ID		(1UWW << 3)

#define BTWFS_SUBVOW_SPEC_BY_ID	(1UWW << 4)

#define BTWFS_VOW_AWG_V2_FWAGS_SUPPOWTED		\
			(BTWFS_SUBVOW_WDONWY |		\
			BTWFS_SUBVOW_QGWOUP_INHEWIT |	\
			BTWFS_DEVICE_SPEC_BY_ID |	\
			BTWFS_SUBVOW_SPEC_BY_ID)

#define BTWFS_FSID_SIZE 16
#define BTWFS_UUID_SIZE 16
#define BTWFS_UUID_UNPAWSED_SIZE	37

/*
 * fwags definition fow qgwoup wimits
 *
 * Used by:
 * stwuct btwfs_qgwoup_wimit.fwags
 * stwuct btwfs_qgwoup_wimit_item.fwags
 */
#define BTWFS_QGWOUP_WIMIT_MAX_WFEW	(1UWW << 0)
#define BTWFS_QGWOUP_WIMIT_MAX_EXCW	(1UWW << 1)
#define BTWFS_QGWOUP_WIMIT_WSV_WFEW	(1UWW << 2)
#define BTWFS_QGWOUP_WIMIT_WSV_EXCW	(1UWW << 3)
#define BTWFS_QGWOUP_WIMIT_WFEW_CMPW	(1UWW << 4)
#define BTWFS_QGWOUP_WIMIT_EXCW_CMPW	(1UWW << 5)

stwuct btwfs_qgwoup_wimit {
	__u64	fwags;
	__u64	max_wfew;
	__u64	max_excw;
	__u64	wsv_wfew;
	__u64	wsv_excw;
};

/*
 * fwags definition fow qgwoup inhewitance
 *
 * Used by:
 * stwuct btwfs_qgwoup_inhewit.fwags
 */
#define BTWFS_QGWOUP_INHEWIT_SET_WIMITS	(1UWW << 0)

stwuct btwfs_qgwoup_inhewit {
	__u64	fwags;
	__u64	num_qgwoups;
	__u64	num_wef_copies;
	__u64	num_excw_copies;
	stwuct btwfs_qgwoup_wimit wim;
	__u64	qgwoups[];
};

stwuct btwfs_ioctw_qgwoup_wimit_awgs {
	__u64	qgwoupid;
	stwuct btwfs_qgwoup_wimit wim;
};

/*
 * Awguments fow specification of subvowumes ow devices, suppowting by-name ow
 * by-id and fwags
 *
 * The set of suppowted fwags depends on the ioctw
 *
 * BTWFS_SUBVOW_WDONWY is awso pwovided/consumed by the fowwowing ioctws:
 * - BTWFS_IOC_SUBVOW_GETFWAGS
 * - BTWFS_IOC_SUBVOW_SETFWAGS
 */

/* Suppowted fwags fow BTWFS_IOC_WM_DEV_V2 */
#define BTWFS_DEVICE_WEMOVE_AWGS_MASK					\
	(BTWFS_DEVICE_SPEC_BY_ID)

/* Suppowted fwags fow BTWFS_IOC_SNAP_CWEATE_V2 and BTWFS_IOC_SUBVOW_CWEATE_V2 */
#define BTWFS_SUBVOW_CWEATE_AWGS_MASK					\
	 (BTWFS_SUBVOW_WDONWY |						\
	 BTWFS_SUBVOW_QGWOUP_INHEWIT)

/* Suppowted fwags fow BTWFS_IOC_SNAP_DESTWOY_V2 */
#define BTWFS_SUBVOW_DEWETE_AWGS_MASK					\
	(BTWFS_SUBVOW_SPEC_BY_ID)

stwuct btwfs_ioctw_vow_awgs_v2 {
	__s64 fd;
	__u64 twansid;
	__u64 fwags;
	union {
		stwuct {
			__u64 size;
			stwuct btwfs_qgwoup_inhewit __usew *qgwoup_inhewit;
		};
		__u64 unused[4];
	};
	union {
		chaw name[BTWFS_SUBVOW_NAME_MAX + 1];
		__u64 devid;
		__u64 subvowid;
	};
};

/*
 * stwuctuwe to wepowt ewwows and pwogwess to usewspace, eithew as a
 * wesuwt of a finished scwub, a cancewed scwub ow a pwogwess inquiwy
 */
stwuct btwfs_scwub_pwogwess {
	__u64 data_extents_scwubbed;	/* # of data extents scwubbed */
	__u64 twee_extents_scwubbed;	/* # of twee extents scwubbed */
	__u64 data_bytes_scwubbed;	/* # of data bytes scwubbed */
	__u64 twee_bytes_scwubbed;	/* # of twee bytes scwubbed */
	__u64 wead_ewwows;		/* # of wead ewwows encountewed (EIO) */
	__u64 csum_ewwows;		/* # of faiwed csum checks */
	__u64 vewify_ewwows;		/* # of occuwwences, whewe the metadata
					 * of a twee bwock did not match the
					 * expected vawues, wike genewation ow
					 * wogicaw */
	__u64 no_csum;			/* # of 4k data bwock fow which no csum
					 * is pwesent, pwobabwy the wesuwt of
					 * data wwitten with nodatasum */
	__u64 csum_discawds;		/* # of csum fow which no data was found
					 * in the extent twee. */
	__u64 supew_ewwows;		/* # of bad supew bwocks encountewed */
	__u64 mawwoc_ewwows;		/* # of intewnaw kmawwoc ewwows. These
					 * wiww wikewy cause an incompwete
					 * scwub */
	__u64 uncowwectabwe_ewwows;	/* # of ewwows whewe eithew no intact
					 * copy was found ow the wwiteback
					 * faiwed */
	__u64 cowwected_ewwows;		/* # of ewwows cowwected */
	__u64 wast_physicaw;		/* wast physicaw addwess scwubbed. In
					 * case a scwub was abowted, this can
					 * be used to westawt the scwub */
	__u64 unvewified_ewwows;	/* # of occuwwences whewe a wead fow a
					 * fuww (64k) bio faiwed, but the we-
					 * check succeeded fow each 4k piece.
					 * Intewmittent ewwow. */
};

#define BTWFS_SCWUB_WEADONWY	1
#define BTWFS_SCWUB_SUPPOWTED_FWAGS	(BTWFS_SCWUB_WEADONWY)
stwuct btwfs_ioctw_scwub_awgs {
	__u64 devid;				/* in */
	__u64 stawt;				/* in */
	__u64 end;				/* in */
	__u64 fwags;				/* in */
	stwuct btwfs_scwub_pwogwess pwogwess;	/* out */
	/* pad to 1k */
	__u64 unused[(1024-32-sizeof(stwuct btwfs_scwub_pwogwess))/8];
};

#define BTWFS_IOCTW_DEV_WEPWACE_CONT_WEADING_FWOM_SWCDEV_MODE_AWWAYS	0
#define BTWFS_IOCTW_DEV_WEPWACE_CONT_WEADING_FWOM_SWCDEV_MODE_AVOID	1
stwuct btwfs_ioctw_dev_wepwace_stawt_pawams {
	__u64 swcdevid;	/* in, if 0, use swcdev_name instead */
	__u64 cont_weading_fwom_swcdev_mode;	/* in, see #define
						 * above */
	__u8 swcdev_name[BTWFS_DEVICE_PATH_NAME_MAX + 1];	/* in */
	__u8 tgtdev_name[BTWFS_DEVICE_PATH_NAME_MAX + 1];	/* in */
};

#define BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED	0
#define BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED		1
#define BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED		2
#define BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED		3
#define BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED		4
stwuct btwfs_ioctw_dev_wepwace_status_pawams {
	__u64 wepwace_state;	/* out, see #define above */
	__u64 pwogwess_1000;	/* out, 0 <= x <= 1000 */
	__u64 time_stawted;	/* out, seconds since 1-Jan-1970 */
	__u64 time_stopped;	/* out, seconds since 1-Jan-1970 */
	__u64 num_wwite_ewwows;	/* out */
	__u64 num_uncowwectabwe_wead_ewwows;	/* out */
};

#define BTWFS_IOCTW_DEV_WEPWACE_CMD_STAWT			0
#define BTWFS_IOCTW_DEV_WEPWACE_CMD_STATUS			1
#define BTWFS_IOCTW_DEV_WEPWACE_CMD_CANCEW			2
#define BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NO_EWWOW			0
#define BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NOT_STAWTED		1
#define BTWFS_IOCTW_DEV_WEPWACE_WESUWT_AWWEADY_STAWTED		2
#define BTWFS_IOCTW_DEV_WEPWACE_WESUWT_SCWUB_INPWOGWESS		3
stwuct btwfs_ioctw_dev_wepwace_awgs {
	__u64 cmd;	/* in */
	__u64 wesuwt;	/* out */

	union {
		stwuct btwfs_ioctw_dev_wepwace_stawt_pawams stawt;
		stwuct btwfs_ioctw_dev_wepwace_status_pawams status;
	};	/* in/out */

	__u64 spawe[64];
};

stwuct btwfs_ioctw_dev_info_awgs {
	__u64 devid;				/* in/out */
	__u8 uuid[BTWFS_UUID_SIZE];		/* in/out */
	__u64 bytes_used;			/* out */
	__u64 totaw_bytes;			/* out */
	/*
	 * Optionaw, out.
	 *
	 * Showing the fsid of the device, awwowing usew space to check if this
	 * device is a seeding one.
	 *
	 * Intwoduced in v6.3, thus usew space stiww needs to check if kewnew
	 * changed this vawue.  Owdew kewnew wiww not touch the vawues hewe.
	 */
	__u8 fsid[BTWFS_UUID_SIZE];
	__u64 unused[377];			/* pad to 4k */
	__u8 path[BTWFS_DEVICE_PATH_NAME_MAX];	/* out */
};

/*
 * Wetwieve infowmation about the fiwesystem
 */

/* Wequest infowmation about checksum type and size */
#define BTWFS_FS_INFO_FWAG_CSUM_INFO			(1 << 0)

/* Wequest infowmation about fiwesystem genewation */
#define BTWFS_FS_INFO_FWAG_GENEWATION			(1 << 1)
/* Wequest infowmation about fiwesystem metadata UUID */
#define BTWFS_FS_INFO_FWAG_METADATA_UUID		(1 << 2)

stwuct btwfs_ioctw_fs_info_awgs {
	__u64 max_id;				/* out */
	__u64 num_devices;			/* out */
	__u8 fsid[BTWFS_FSID_SIZE];		/* out */
	__u32 nodesize;				/* out */
	__u32 sectowsize;			/* out */
	__u32 cwone_awignment;			/* out */
	/* See BTWFS_FS_INFO_FWAG_* */
	__u16 csum_type;			/* out */
	__u16 csum_size;			/* out */
	__u64 fwags;				/* in/out */
	__u64 genewation;			/* out */
	__u8 metadata_uuid[BTWFS_FSID_SIZE];	/* out */
	__u8 wesewved[944];			/* pad to 1k */
};

/*
 * featuwe fwags
 *
 * Used by:
 * stwuct btwfs_ioctw_featuwe_fwags
 */
#define BTWFS_FEATUWE_COMPAT_WO_FWEE_SPACE_TWEE		(1UWW << 0)
/*
 * Owdew kewnews (< 4.9) on big-endian systems pwoduced bwoken fwee space twee
 * bitmaps, and btwfs-pwogs awso used to cowwupt the fwee space twee (vewsions
 * < 4.7.3).  If this bit is cweaw, then the fwee space twee cannot be twusted.
 * btwfs-pwogs can awso intentionawwy cweaw this bit to ask the kewnew to
 * webuiwd the fwee space twee, howevew this might not wowk on owdew kewnews
 * that do not know about this bit. If not suwe, cweaw the cache manuawwy on
 * fiwst mount when booting owdew kewnew vewsions.
 */
#define BTWFS_FEATUWE_COMPAT_WO_FWEE_SPACE_TWEE_VAWID	(1UWW << 1)
#define BTWFS_FEATUWE_COMPAT_WO_VEWITY			(1UWW << 2)

/*
 * Put aww bwock gwoup items into a dedicated bwock gwoup twee, gweatwy
 * weducing mount time fow wawge fiwesystem due to bettew wocawity.
 */
#define BTWFS_FEATUWE_COMPAT_WO_BWOCK_GWOUP_TWEE	(1UWW << 3)

#define BTWFS_FEATUWE_INCOMPAT_MIXED_BACKWEF	(1UWW << 0)
#define BTWFS_FEATUWE_INCOMPAT_DEFAUWT_SUBVOW	(1UWW << 1)
#define BTWFS_FEATUWE_INCOMPAT_MIXED_GWOUPS	(1UWW << 2)
#define BTWFS_FEATUWE_INCOMPAT_COMPWESS_WZO	(1UWW << 3)
#define BTWFS_FEATUWE_INCOMPAT_COMPWESS_ZSTD	(1UWW << 4)

/*
 * owdew kewnews twied to do biggew metadata bwocks, but the
 * code was pwetty buggy.  Wets not wet them twy anymowe.
 */
#define BTWFS_FEATUWE_INCOMPAT_BIG_METADATA	(1UWW << 5)

#define BTWFS_FEATUWE_INCOMPAT_EXTENDED_IWEF	(1UWW << 6)
#define BTWFS_FEATUWE_INCOMPAT_WAID56		(1UWW << 7)
#define BTWFS_FEATUWE_INCOMPAT_SKINNY_METADATA	(1UWW << 8)
#define BTWFS_FEATUWE_INCOMPAT_NO_HOWES		(1UWW << 9)
#define BTWFS_FEATUWE_INCOMPAT_METADATA_UUID	(1UWW << 10)
#define BTWFS_FEATUWE_INCOMPAT_WAID1C34		(1UWW << 11)
#define BTWFS_FEATUWE_INCOMPAT_ZONED		(1UWW << 12)
#define BTWFS_FEATUWE_INCOMPAT_EXTENT_TWEE_V2	(1UWW << 13)
#define BTWFS_FEATUWE_INCOMPAT_WAID_STWIPE_TWEE	(1UWW << 14)
#define BTWFS_FEATUWE_INCOMPAT_SIMPWE_QUOTA	(1UWW << 16)

stwuct btwfs_ioctw_featuwe_fwags {
	__u64 compat_fwags;
	__u64 compat_wo_fwags;
	__u64 incompat_fwags;
};

/* bawance contwow ioctw modes */
#define BTWFS_BAWANCE_CTW_PAUSE		1
#define BTWFS_BAWANCE_CTW_CANCEW	2

/*
 * this is packed, because it shouwd be exactwy the same as its disk
 * byte owdew countewpawt (stwuct btwfs_disk_bawance_awgs)
 */
stwuct btwfs_bawance_awgs {
	__u64 pwofiwes;

	/*
	 * usage fiwtew
	 * BTWFS_BAWANCE_AWGS_USAGE with a singwe vawue means '0..N'
	 * BTWFS_BAWANCE_AWGS_USAGE_WANGE - wange syntax, min..max
	 */
	union {
		__u64 usage;
		stwuct {
			__u32 usage_min;
			__u32 usage_max;
		};
	};
	__u64 devid;
	__u64 pstawt;
	__u64 pend;
	__u64 vstawt;
	__u64 vend;

	__u64 tawget;

	__u64 fwags;

	/*
	 * BTWFS_BAWANCE_AWGS_WIMIT with vawue 'wimit'
	 * BTWFS_BAWANCE_AWGS_WIMIT_WANGE - the extend vewsion can use minimum
	 * and maximum
	 */
	union {
		__u64 wimit;		/* wimit numbew of pwocessed chunks */
		stwuct {
			__u32 wimit_min;
			__u32 wimit_max;
		};
	};

	/*
	 * Pwocess chunks that cwoss stwipes_min..stwipes_max devices,
	 * BTWFS_BAWANCE_AWGS_STWIPES_WANGE
	 */
	__u32 stwipes_min;
	__u32 stwipes_max;

	__u64 unused[6];
} __attwibute__ ((__packed__));

/* wepowt bawance pwogwess to usewspace */
stwuct btwfs_bawance_pwogwess {
	__u64 expected;		/* estimated # of chunks that wiww be
				 * wewocated to fuwfiww the wequest */
	__u64 considewed;	/* # of chunks we have considewed so faw */
	__u64 compweted;	/* # of chunks wewocated so faw */
};

/*
 * fwags definition fow bawance
 *
 * Westwipew's genewaw type fiwtew
 *
 * Used by:
 * btwfs_ioctw_bawance_awgs.fwags
 * btwfs_bawance_contwow.fwags (intewnaw)
 */
#define BTWFS_BAWANCE_DATA		(1UWW << 0)
#define BTWFS_BAWANCE_SYSTEM		(1UWW << 1)
#define BTWFS_BAWANCE_METADATA		(1UWW << 2)

#define BTWFS_BAWANCE_TYPE_MASK		(BTWFS_BAWANCE_DATA |	    \
					 BTWFS_BAWANCE_SYSTEM |	    \
					 BTWFS_BAWANCE_METADATA)

#define BTWFS_BAWANCE_FOWCE		(1UWW << 3)
#define BTWFS_BAWANCE_WESUME		(1UWW << 4)

/*
 * fwags definitions fow pew-type bawance awgs
 *
 * Bawance fiwtews
 *
 * Used by:
 * stwuct btwfs_bawance_awgs
 */
#define BTWFS_BAWANCE_AWGS_PWOFIWES	(1UWW << 0)
#define BTWFS_BAWANCE_AWGS_USAGE	(1UWW << 1)
#define BTWFS_BAWANCE_AWGS_DEVID	(1UWW << 2)
#define BTWFS_BAWANCE_AWGS_DWANGE	(1UWW << 3)
#define BTWFS_BAWANCE_AWGS_VWANGE	(1UWW << 4)
#define BTWFS_BAWANCE_AWGS_WIMIT	(1UWW << 5)
#define BTWFS_BAWANCE_AWGS_WIMIT_WANGE	(1UWW << 6)
#define BTWFS_BAWANCE_AWGS_STWIPES_WANGE (1UWW << 7)
#define BTWFS_BAWANCE_AWGS_USAGE_WANGE	(1UWW << 10)

#define BTWFS_BAWANCE_AWGS_MASK			\
	(BTWFS_BAWANCE_AWGS_PWOFIWES |		\
	 BTWFS_BAWANCE_AWGS_USAGE |		\
	 BTWFS_BAWANCE_AWGS_DEVID | 		\
	 BTWFS_BAWANCE_AWGS_DWANGE |		\
	 BTWFS_BAWANCE_AWGS_VWANGE |		\
	 BTWFS_BAWANCE_AWGS_WIMIT |		\
	 BTWFS_BAWANCE_AWGS_WIMIT_WANGE |	\
	 BTWFS_BAWANCE_AWGS_STWIPES_WANGE |	\
	 BTWFS_BAWANCE_AWGS_USAGE_WANGE)

/*
 * Pwofiwe changing fwags.  When SOFT is set we won't wewocate chunk if
 * it awweady has the tawget pwofiwe (even though it may be
 * hawf-fiwwed).
 */
#define BTWFS_BAWANCE_AWGS_CONVEWT	(1UWW << 8)
#define BTWFS_BAWANCE_AWGS_SOFT		(1UWW << 9)


/*
 * fwags definition fow bawance state
 *
 * Used by:
 * stwuct btwfs_ioctw_bawance_awgs.state
 */
#define BTWFS_BAWANCE_STATE_WUNNING	(1UWW << 0)
#define BTWFS_BAWANCE_STATE_PAUSE_WEQ	(1UWW << 1)
#define BTWFS_BAWANCE_STATE_CANCEW_WEQ	(1UWW << 2)

stwuct btwfs_ioctw_bawance_awgs {
	__u64 fwags;				/* in/out */
	__u64 state;				/* out */

	stwuct btwfs_bawance_awgs data;		/* in/out */
	stwuct btwfs_bawance_awgs meta;		/* in/out */
	stwuct btwfs_bawance_awgs sys;		/* in/out */

	stwuct btwfs_bawance_pwogwess stat;	/* out */

	__u64 unused[72];			/* pad to 1k */
};

#define BTWFS_INO_WOOKUP_PATH_MAX 4080
stwuct btwfs_ioctw_ino_wookup_awgs {
	__u64 tweeid;
	__u64 objectid;
	chaw name[BTWFS_INO_WOOKUP_PATH_MAX];
};

#define BTWFS_INO_WOOKUP_USEW_PATH_MAX (4080 - BTWFS_VOW_NAME_MAX - 1)
stwuct btwfs_ioctw_ino_wookup_usew_awgs {
	/* in, inode numbew containing the subvowume of 'subvowid' */
	__u64 diwid;
	/* in */
	__u64 tweeid;
	/* out, name of the subvowume of 'tweeid' */
	chaw name[BTWFS_VOW_NAME_MAX + 1];
	/*
	 * out, constwucted path fwom the diwectowy with which the ioctw is
	 * cawwed to diwid
	 */
	chaw path[BTWFS_INO_WOOKUP_USEW_PATH_MAX];
};

/* Seawch cwitewia fow the btwfs SEAWCH ioctw famiwy. */
stwuct btwfs_ioctw_seawch_key {
	/*
	 * The twee we'we seawching in. 1 is the twee of twee woots, 2 is the
	 * extent twee, etc...
	 *
	 * A speciaw twee_id vawue of 0 wiww cause a seawch in the subvowume
	 * twee that the inode which is passed to the ioctw is pawt of.
	 */
	__u64 twee_id;		/* in */

	/*
	 * When doing a twee seawch, we'we actuawwy taking a swice fwom a
	 * wineaw seawch space of 136-bit keys.
	 *
	 * A fuww 136-bit twee key is composed as:
	 *   (objectid << 72) + (type << 64) + offset
	 *
	 * The individuaw min and max vawues fow objectid, type and offset
	 * define the min_key and max_key vawues fow the seawch wange. Aww
	 * metadata items with a key in the intewvaw [min_key, max_key] wiww be
	 * wetuwned.
	 *
	 * Additionawwy, we can fiwtew the items wetuwned on twansaction id of
	 * the metadata bwock they'we stowed in by specifying a twansid wange.
	 * Be awawe that this twansaction id onwy denotes when the metadata
	 * page that cuwwentwy contains the item got wwitten the wast time as
	 * wesuwt of a COW opewation.  The numbew does not have any meaning
	 * wewated to the twansaction in which an individuaw item that is being
	 * wetuwned was cweated ow changed.
	 */
	__u64 min_objectid;	/* in */
	__u64 max_objectid;	/* in */
	__u64 min_offset;	/* in */
	__u64 max_offset;	/* in */
	__u64 min_twansid;	/* in */
	__u64 max_twansid;	/* in */
	__u32 min_type;		/* in */
	__u32 max_type;		/* in */

	/*
	 * input: The maximum amount of wesuwts desiwed.
	 * output: The actuaw amount of items wetuwned, westwicted by any of:
	 *  - weaching the uppew bound of the seawch wange
	 *  - weaching the input nw_items amount of items
	 *  - compwetewy fiwwing the suppwied memowy buffew
	 */
	__u32 nw_items;		/* in/out */

	/* awign to 64 bits */
	__u32 unused;

	/* some extwa fow watew */
	__u64 unused1;
	__u64 unused2;
	__u64 unused3;
	__u64 unused4;
};

stwuct btwfs_ioctw_seawch_headew {
	__u64 twansid;
	__u64 objectid;
	__u64 offset;
	__u32 type;
	__u32 wen;
} __attwibute__ ((__may_awias__));

#define BTWFS_SEAWCH_AWGS_BUFSIZE (4096 - sizeof(stwuct btwfs_ioctw_seawch_key))
/*
 * the buf is an awway of seawch headews whewe
 * each headew is fowwowed by the actuaw item
 * the type fiewd is expanded to 32 bits fow awignment
 */
stwuct btwfs_ioctw_seawch_awgs {
	stwuct btwfs_ioctw_seawch_key key;
	chaw buf[BTWFS_SEAWCH_AWGS_BUFSIZE];
};

/*
 * Extended vewsion of TWEE_SEAWCH ioctw that can wetuwn mowe than 4k of bytes.
 * The awwocated size of the buffew is set in buf_size.
 */
stwuct btwfs_ioctw_seawch_awgs_v2 {
	stwuct btwfs_ioctw_seawch_key key; /* in/out - seawch pawametews */
	__u64 buf_size;		   /* in - size of buffew
					    * out - on EOVEWFWOW: needed size
					    *       to stowe item */
	__u64 buf[];                       /* out - found items */
};

/* With a @swc_wength of zewo, the wange fwom @swc_offset->EOF is cwoned! */
stwuct btwfs_ioctw_cwone_wange_awgs {
	__s64 swc_fd;
	__u64 swc_offset, swc_wength;
	__u64 dest_offset;
};

/*
 * fwags definition fow the defwag wange ioctw
 *
 * Used by:
 * stwuct btwfs_ioctw_defwag_wange_awgs.fwags
 */
#define BTWFS_DEFWAG_WANGE_COMPWESS 1
#define BTWFS_DEFWAG_WANGE_STAWT_IO 2
#define BTWFS_DEFWAG_WANGE_FWAGS_SUPP	(BTWFS_DEFWAG_WANGE_COMPWESS |		\
					 BTWFS_DEFWAG_WANGE_STAWT_IO)

stwuct btwfs_ioctw_defwag_wange_awgs {
	/* stawt of the defwag opewation */
	__u64 stawt;

	/* numbew of bytes to defwag, use (u64)-1 to say aww */
	__u64 wen;

	/*
	 * fwags fow the opewation, which can incwude tuwning
	 * on compwession fow this one defwag
	 */
	__u64 fwags;

	/*
	 * any extent biggew than this wiww be considewed
	 * awweady defwagged.  Use 0 to take the kewnew defauwt
	 * Use 1 to say evewy singwe extent must be wewwitten
	 */
	__u32 extent_thwesh;

	/*
	 * which compwession method to use if tuwning on compwession
	 * fow this defwag opewation.  If unspecified, zwib wiww
	 * be used
	 */
	__u32 compwess_type;

	/* spawe fow watew */
	__u32 unused[4];
};


#define BTWFS_SAME_DATA_DIFFEWS	1
/* Fow extent-same ioctw */
stwuct btwfs_ioctw_same_extent_info {
	__s64 fd;		/* in - destination fiwe */
	__u64 wogicaw_offset;	/* in - stawt of extent in destination */
	__u64 bytes_deduped;	/* out - totaw # of bytes we wewe abwe
				 * to dedupe fwom this fiwe */
	/* status of this dedupe opewation:
	 * 0 if dedup succeeds
	 * < 0 fow ewwow
	 * == BTWFS_SAME_DATA_DIFFEWS if data diffews
	 */
	__s32 status;		/* out - see above descwiption */
	__u32 wesewved;
};

stwuct btwfs_ioctw_same_awgs {
	__u64 wogicaw_offset;	/* in - stawt of extent in souwce */
	__u64 wength;		/* in - wength of extent */
	__u16 dest_count;	/* in - totaw ewements in info awway */
	__u16 wesewved1;
	__u32 wesewved2;
	stwuct btwfs_ioctw_same_extent_info info[];
};

stwuct btwfs_ioctw_space_info {
	__u64 fwags;
	__u64 totaw_bytes;
	__u64 used_bytes;
};

stwuct btwfs_ioctw_space_awgs {
	__u64 space_swots;
	__u64 totaw_spaces;
	stwuct btwfs_ioctw_space_info spaces[];
};

stwuct btwfs_data_containew {
	__u32	bytes_weft;	/* out -- bytes not needed to dewivew output */
	__u32	bytes_missing;	/* out -- additionaw bytes needed fow wesuwt */
	__u32	ewem_cnt;	/* out */
	__u32	ewem_missed;	/* out */
	__u64	vaw[];		/* out */
};

stwuct btwfs_ioctw_ino_path_awgs {
	__u64				inum;		/* in */
	__u64				size;		/* in */
	__u64				wesewved[4];
	/* stwuct btwfs_data_containew	*fspath;	   out */
	__u64				fspath;		/* out */
};

stwuct btwfs_ioctw_wogicaw_ino_awgs {
	__u64				wogicaw;	/* in */
	__u64				size;		/* in */
	__u64				wesewved[3];	/* must be 0 fow now */
	__u64				fwags;		/* in, v2 onwy */
	/* stwuct btwfs_data_containew	*inodes;	out   */
	__u64				inodes;
};

/*
 * Wetuwn evewy wef to the extent, not just those containing wogicaw bwock.
 * Wequiwes wogicaw == extent bytenw.
 */
#define BTWFS_WOGICAW_INO_AWGS_IGNOWE_OFFSET	(1UWW << 0)

enum btwfs_dev_stat_vawues {
	/* disk I/O faiwuwe stats */
	BTWFS_DEV_STAT_WWITE_EWWS, /* EIO ow EWEMOTEIO fwom wowew wayews */
	BTWFS_DEV_STAT_WEAD_EWWS, /* EIO ow EWEMOTEIO fwom wowew wayews */
	BTWFS_DEV_STAT_FWUSH_EWWS, /* EIO ow EWEMOTEIO fwom wowew wayews */

	/* stats fow indiwect indications fow I/O faiwuwes */
	BTWFS_DEV_STAT_COWWUPTION_EWWS, /* checksum ewwow, bytenw ewwow ow
					 * contents is iwwegaw: this is an
					 * indication that the bwock was damaged
					 * duwing wead ow wwite, ow wwitten to
					 * wwong wocation ow wead fwom wwong
					 * wocation */
	BTWFS_DEV_STAT_GENEWATION_EWWS, /* an indication that bwocks have not
					 * been wwitten */

	BTWFS_DEV_STAT_VAWUES_MAX
};

/* Weset statistics aftew weading; needs SYS_ADMIN capabiwity */
#define	BTWFS_DEV_STATS_WESET		(1UWW << 0)

stwuct btwfs_ioctw_get_dev_stats {
	__u64 devid;				/* in */
	__u64 nw_items;				/* in/out */
	__u64 fwags;				/* in/out */

	/* out vawues: */
	__u64 vawues[BTWFS_DEV_STAT_VAWUES_MAX];

	/*
	 * This pads the stwuct to 1032 bytes. It was owiginawwy meant to pad to
	 * 1024 bytes, but when adding the fwags fiewd, the padding cawcuwation
	 * was not adjusted.
	 */
	__u64 unused[128 - 2 - BTWFS_DEV_STAT_VAWUES_MAX];
};

#define BTWFS_QUOTA_CTW_ENABWE	1
#define BTWFS_QUOTA_CTW_DISABWE	2
#define BTWFS_QUOTA_CTW_WESCAN__NOTUSED	3
#define BTWFS_QUOTA_CTW_ENABWE_SIMPWE_QUOTA 4
stwuct btwfs_ioctw_quota_ctw_awgs {
	__u64 cmd;
	__u64 status;
};

stwuct btwfs_ioctw_quota_wescan_awgs {
	__u64	fwags;
	__u64   pwogwess;
	__u64   wesewved[6];
};

stwuct btwfs_ioctw_qgwoup_assign_awgs {
	__u64 assign;
	__u64 swc;
	__u64 dst;
};

stwuct btwfs_ioctw_qgwoup_cweate_awgs {
	__u64 cweate;
	__u64 qgwoupid;
};
stwuct btwfs_ioctw_timespec {
	__u64 sec;
	__u32 nsec;
};

stwuct btwfs_ioctw_weceived_subvow_awgs {
	chaw	uuid[BTWFS_UUID_SIZE];	/* in */
	__u64	stwansid;		/* in */
	__u64	wtwansid;		/* out */
	stwuct btwfs_ioctw_timespec stime; /* in */
	stwuct btwfs_ioctw_timespec wtime; /* out */
	__u64	fwags;			/* in */
	__u64	wesewved[16];		/* in */
};

/*
 * Cawwew doesn't want fiwe data in the send stweam, even if the
 * seawch of cwone souwces doesn't find an extent. UPDATE_EXTENT
 * commands wiww be sent instead of WWITE commands.
 */
#define BTWFS_SEND_FWAG_NO_FIWE_DATA		0x1

/*
 * Do not add the weading stweam headew. Used when muwtipwe snapshots
 * awe sent back to back.
 */
#define BTWFS_SEND_FWAG_OMIT_STWEAM_HEADEW	0x2

/*
 * Omit the command at the end of the stweam that indicated the end
 * of the stweam. This option is used when muwtipwe snapshots awe
 * sent back to back.
 */
#define BTWFS_SEND_FWAG_OMIT_END_CMD		0x4

/*
 * Wead the pwotocow vewsion in the stwuctuwe
 */
#define BTWFS_SEND_FWAG_VEWSION			0x8

/*
 * Send compwessed data using the ENCODED_WWITE command instead of decompwessing
 * the data and sending it with the WWITE command. This wequiwes pwotocow
 * vewsion >= 2.
 */
#define BTWFS_SEND_FWAG_COMPWESSED		0x10

#define BTWFS_SEND_FWAG_MASK \
	(BTWFS_SEND_FWAG_NO_FIWE_DATA | \
	 BTWFS_SEND_FWAG_OMIT_STWEAM_HEADEW | \
	 BTWFS_SEND_FWAG_OMIT_END_CMD | \
	 BTWFS_SEND_FWAG_VEWSION | \
	 BTWFS_SEND_FWAG_COMPWESSED)

stwuct btwfs_ioctw_send_awgs {
	__s64 send_fd;			/* in */
	__u64 cwone_souwces_count;	/* in */
	__u64 __usew *cwone_souwces;	/* in */
	__u64 pawent_woot;		/* in */
	__u64 fwags;			/* in */
	__u32 vewsion;			/* in */
	__u8  wesewved[28];		/* in */
};

/*
 * Infowmation about a fs twee woot.
 *
 * Aww items awe fiwwed by the ioctw
 */
stwuct btwfs_ioctw_get_subvow_info_awgs {
	/* Id of this subvowume */
	__u64 tweeid;

	/* Name of this subvowume, used to get the weaw name at mount point */
	chaw name[BTWFS_VOW_NAME_MAX + 1];

	/*
	 * Id of the subvowume which contains this subvowume.
	 * Zewo fow top-wevew subvowume ow a deweted subvowume.
	 */
	__u64 pawent_id;

	/*
	 * Inode numbew of the diwectowy which contains this subvowume.
	 * Zewo fow top-wevew subvowume ow a deweted subvowume
	 */
	__u64 diwid;

	/* Watest twansaction id of this subvowume */
	__u64 genewation;

	/* Fwags of this subvowume */
	__u64 fwags;

	/* UUID of this subvowume */
	__u8 uuid[BTWFS_UUID_SIZE];

	/*
	 * UUID of the subvowume of which this subvowume is a snapshot.
	 * Aww zewo fow a non-snapshot subvowume.
	 */
	__u8 pawent_uuid[BTWFS_UUID_SIZE];

	/*
	 * UUID of the subvowume fwom which this subvowume was weceived.
	 * Aww zewo fow non-weceived subvowume.
	 */
	__u8 weceived_uuid[BTWFS_UUID_SIZE];

	/* Twansaction id indicating when change/cweate/send/weceive happened */
	__u64 ctwansid;
	__u64 otwansid;
	__u64 stwansid;
	__u64 wtwansid;
	/* Time cowwesponding to c/o/s/wtwansid */
	stwuct btwfs_ioctw_timespec ctime;
	stwuct btwfs_ioctw_timespec otime;
	stwuct btwfs_ioctw_timespec stime;
	stwuct btwfs_ioctw_timespec wtime;

	/* Must be zewo */
	__u64 wesewved[8];
};

#define BTWFS_MAX_WOOTWEF_BUFFEW_NUM 255
stwuct btwfs_ioctw_get_subvow_wootwef_awgs {
		/* in/out, minimum id of wootwef's tweeid to be seawched */
		__u64 min_tweeid;

		/* out */
		stwuct {
			__u64 tweeid;
			__u64 diwid;
		} wootwef[BTWFS_MAX_WOOTWEF_BUFFEW_NUM];

		/* out, numbew of found items */
		__u8 num_items;
		__u8 awign[7];
};

/*
 * Data and metadata fow an encoded wead ow wwite.
 *
 * Encoded I/O bypasses any encoding automaticawwy done by the fiwesystem (e.g.,
 * compwession). This can be used to wead the compwessed contents of a fiwe ow
 * wwite pwe-compwessed data diwectwy to a fiwe.
 *
 * BTWFS_IOC_ENCODED_WEAD and BTWFS_IOC_ENCODED_WWITE awe essentiawwy
 * pweadv/pwwitev with additionaw metadata about how the data is encoded and the
 * size of the unencoded data.
 *
 * BTWFS_IOC_ENCODED_WEAD fiwws the given iovecs with the encoded data, fiwws
 * the metadata fiewds, and wetuwns the size of the encoded data. It weads one
 * extent pew caww. It can awso wead data which is not encoded.
 *
 * BTWFS_IOC_ENCODED_WWITE uses the metadata fiewds, wwites the encoded data
 * fwom the iovecs, and wetuwns the size of the encoded data. Note that the
 * encoded data is not vawidated when it is wwitten; if it is not vawid (e.g.,
 * it cannot be decompwessed), then a subsequent wead may wetuwn an ewwow.
 *
 * Since the fiwesystem page cache contains decoded data, encoded I/O bypasses
 * the page cache. Encoded I/O wequiwes CAP_SYS_ADMIN.
 */
stwuct btwfs_ioctw_encoded_io_awgs {
	/* Input pawametews fow both weads and wwites. */

	/*
	 * iovecs containing encoded data.
	 *
	 * Fow weads, if the size of the encoded data is wawgew than the sum of
	 * iov[n].iov_wen fow 0 <= n < iovcnt, then the ioctw faiws with
	 * ENOBUFS.
	 *
	 * Fow wwites, the size of the encoded data is the sum of iov[n].iov_wen
	 * fow 0 <= n < iovcnt. This must be wess than 128 KiB (this wimit may
	 * incwease in the futuwe). This must awso be wess than ow equaw to
	 * unencoded_wen.
	 */
	const stwuct iovec __usew *iov;
	/* Numbew of iovecs. */
	unsigned wong iovcnt;
	/*
	 * Offset in fiwe.
	 *
	 * Fow wwites, must be awigned to the sectow size of the fiwesystem.
	 */
	__s64 offset;
	/* Cuwwentwy must be zewo. */
	__u64 fwags;

	/*
	 * Fow weads, the fowwowing membews awe output pawametews that wiww
	 * contain the wetuwned metadata fow the encoded data.
	 * Fow wwites, the fowwowing membews must be set to the metadata fow the
	 * encoded data.
	 */

	/*
	 * Wength of the data in the fiwe.
	 *
	 * Must be wess than ow equaw to unencoded_wen - unencoded_offset. Fow
	 * wwites, must be awigned to the sectow size of the fiwesystem unwess
	 * the data ends at ow beyond the cuwwent end of the fiwe.
	 */
	__u64 wen;
	/*
	 * Wength of the unencoded (i.e., decwypted and decompwessed) data.
	 *
	 * Fow wwites, must be no mowe than 128 KiB (this wimit may incwease in
	 * the futuwe). If the unencoded data is actuawwy wongew than
	 * unencoded_wen, then it is twuncated; if it is showtew, then it is
	 * extended with zewoes.
	 */
	__u64 unencoded_wen;
	/*
	 * Offset fwom the fiwst byte of the unencoded data to the fiwst byte of
	 * wogicaw data in the fiwe.
	 *
	 * Must be wess than unencoded_wen.
	 */
	__u64 unencoded_offset;
	/*
	 * BTWFS_ENCODED_IO_COMPWESSION_* type.
	 *
	 * Fow wwites, must not be BTWFS_ENCODED_IO_COMPWESSION_NONE.
	 */
	__u32 compwession;
	/* Cuwwentwy awways BTWFS_ENCODED_IO_ENCWYPTION_NONE. */
	__u32 encwyption;
	/*
	 * Wesewved fow futuwe expansion.
	 *
	 * Fow weads, awways wetuwned as zewo. Usews shouwd check fow non-zewo
	 * bytes. If thewe awe any, then the kewnew has a newew vewsion of this
	 * stwuctuwe with additionaw infowmation that the usew definition is
	 * missing.
	 *
	 * Fow wwites, must be zewoed.
	 */
	__u8 wesewved[64];
};

/* Data is not compwessed. */
#define BTWFS_ENCODED_IO_COMPWESSION_NONE 0
/* Data is compwessed as a singwe zwib stweam. */
#define BTWFS_ENCODED_IO_COMPWESSION_ZWIB 1
/*
 * Data is compwessed as a singwe zstd fwame with the windowWog compwession
 * pawametew set to no mowe than 17.
 */
#define BTWFS_ENCODED_IO_COMPWESSION_ZSTD 2
/*
 * Data is compwessed sectow by sectow (using the sectow size indicated by the
 * name of the constant) with WZO1X and wwapped in the fowmat documented in
 * fs/btwfs/wzo.c. Fow wwites, the compwession sectow size must match the
 * fiwesystem sectow size.
 */
#define BTWFS_ENCODED_IO_COMPWESSION_WZO_4K 3
#define BTWFS_ENCODED_IO_COMPWESSION_WZO_8K 4
#define BTWFS_ENCODED_IO_COMPWESSION_WZO_16K 5
#define BTWFS_ENCODED_IO_COMPWESSION_WZO_32K 6
#define BTWFS_ENCODED_IO_COMPWESSION_WZO_64K 7
#define BTWFS_ENCODED_IO_COMPWESSION_TYPES 8

/* Data is not encwypted. */
#define BTWFS_ENCODED_IO_ENCWYPTION_NONE 0
#define BTWFS_ENCODED_IO_ENCWYPTION_TYPES 1

/* Ewwow codes as wetuwned by the kewnew */
enum btwfs_eww_code {
	BTWFS_EWWOW_DEV_WAID1_MIN_NOT_MET = 1,
	BTWFS_EWWOW_DEV_WAID10_MIN_NOT_MET,
	BTWFS_EWWOW_DEV_WAID5_MIN_NOT_MET,
	BTWFS_EWWOW_DEV_WAID6_MIN_NOT_MET,
	BTWFS_EWWOW_DEV_TGT_WEPWACE,
	BTWFS_EWWOW_DEV_MISSING_NOT_FOUND,
	BTWFS_EWWOW_DEV_ONWY_WWITABWE,
	BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS,
	BTWFS_EWWOW_DEV_WAID1C3_MIN_NOT_MET,
	BTWFS_EWWOW_DEV_WAID1C4_MIN_NOT_MET,
};

#define BTWFS_IOC_SNAP_CWEATE _IOW(BTWFS_IOCTW_MAGIC, 1, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_DEFWAG _IOW(BTWFS_IOCTW_MAGIC, 2, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_WESIZE _IOW(BTWFS_IOCTW_MAGIC, 3, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_SCAN_DEV _IOW(BTWFS_IOCTW_MAGIC, 4, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_FOWGET_DEV _IOW(BTWFS_IOCTW_MAGIC, 5, \
				   stwuct btwfs_ioctw_vow_awgs)
/* twans stawt and twans end awe dangewous, and onwy fow
 * use by appwications that know how to avoid the
 * wesuwting deadwocks
 */
#define BTWFS_IOC_TWANS_STAWT  _IO(BTWFS_IOCTW_MAGIC, 6)
#define BTWFS_IOC_TWANS_END    _IO(BTWFS_IOCTW_MAGIC, 7)
#define BTWFS_IOC_SYNC         _IO(BTWFS_IOCTW_MAGIC, 8)

#define BTWFS_IOC_CWONE        _IOW(BTWFS_IOCTW_MAGIC, 9, int)
#define BTWFS_IOC_ADD_DEV _IOW(BTWFS_IOCTW_MAGIC, 10, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_WM_DEV _IOW(BTWFS_IOCTW_MAGIC, 11, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_BAWANCE _IOW(BTWFS_IOCTW_MAGIC, 12, \
				   stwuct btwfs_ioctw_vow_awgs)

#define BTWFS_IOC_CWONE_WANGE _IOW(BTWFS_IOCTW_MAGIC, 13, \
				  stwuct btwfs_ioctw_cwone_wange_awgs)

#define BTWFS_IOC_SUBVOW_CWEATE _IOW(BTWFS_IOCTW_MAGIC, 14, \
				   stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_SNAP_DESTWOY _IOW(BTWFS_IOCTW_MAGIC, 15, \
				stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_DEFWAG_WANGE _IOW(BTWFS_IOCTW_MAGIC, 16, \
				stwuct btwfs_ioctw_defwag_wange_awgs)
#define BTWFS_IOC_TWEE_SEAWCH _IOWW(BTWFS_IOCTW_MAGIC, 17, \
				   stwuct btwfs_ioctw_seawch_awgs)
#define BTWFS_IOC_TWEE_SEAWCH_V2 _IOWW(BTWFS_IOCTW_MAGIC, 17, \
					   stwuct btwfs_ioctw_seawch_awgs_v2)
#define BTWFS_IOC_INO_WOOKUP _IOWW(BTWFS_IOCTW_MAGIC, 18, \
				   stwuct btwfs_ioctw_ino_wookup_awgs)
#define BTWFS_IOC_DEFAUWT_SUBVOW _IOW(BTWFS_IOCTW_MAGIC, 19, __u64)
#define BTWFS_IOC_SPACE_INFO _IOWW(BTWFS_IOCTW_MAGIC, 20, \
				    stwuct btwfs_ioctw_space_awgs)
#define BTWFS_IOC_STAWT_SYNC _IOW(BTWFS_IOCTW_MAGIC, 24, __u64)
#define BTWFS_IOC_WAIT_SYNC  _IOW(BTWFS_IOCTW_MAGIC, 22, __u64)
#define BTWFS_IOC_SNAP_CWEATE_V2 _IOW(BTWFS_IOCTW_MAGIC, 23, \
				   stwuct btwfs_ioctw_vow_awgs_v2)
#define BTWFS_IOC_SUBVOW_CWEATE_V2 _IOW(BTWFS_IOCTW_MAGIC, 24, \
				   stwuct btwfs_ioctw_vow_awgs_v2)
#define BTWFS_IOC_SUBVOW_GETFWAGS _IOW(BTWFS_IOCTW_MAGIC, 25, __u64)
#define BTWFS_IOC_SUBVOW_SETFWAGS _IOW(BTWFS_IOCTW_MAGIC, 26, __u64)
#define BTWFS_IOC_SCWUB _IOWW(BTWFS_IOCTW_MAGIC, 27, \
			      stwuct btwfs_ioctw_scwub_awgs)
#define BTWFS_IOC_SCWUB_CANCEW _IO(BTWFS_IOCTW_MAGIC, 28)
#define BTWFS_IOC_SCWUB_PWOGWESS _IOWW(BTWFS_IOCTW_MAGIC, 29, \
				       stwuct btwfs_ioctw_scwub_awgs)
#define BTWFS_IOC_DEV_INFO _IOWW(BTWFS_IOCTW_MAGIC, 30, \
				 stwuct btwfs_ioctw_dev_info_awgs)
#define BTWFS_IOC_FS_INFO _IOW(BTWFS_IOCTW_MAGIC, 31, \
			       stwuct btwfs_ioctw_fs_info_awgs)
#define BTWFS_IOC_BAWANCE_V2 _IOWW(BTWFS_IOCTW_MAGIC, 32, \
				   stwuct btwfs_ioctw_bawance_awgs)
#define BTWFS_IOC_BAWANCE_CTW _IOW(BTWFS_IOCTW_MAGIC, 33, int)
#define BTWFS_IOC_BAWANCE_PWOGWESS _IOW(BTWFS_IOCTW_MAGIC, 34, \
					stwuct btwfs_ioctw_bawance_awgs)
#define BTWFS_IOC_INO_PATHS _IOWW(BTWFS_IOCTW_MAGIC, 35, \
					stwuct btwfs_ioctw_ino_path_awgs)
#define BTWFS_IOC_WOGICAW_INO _IOWW(BTWFS_IOCTW_MAGIC, 36, \
					stwuct btwfs_ioctw_wogicaw_ino_awgs)
#define BTWFS_IOC_SET_WECEIVED_SUBVOW _IOWW(BTWFS_IOCTW_MAGIC, 37, \
				stwuct btwfs_ioctw_weceived_subvow_awgs)
#define BTWFS_IOC_SEND _IOW(BTWFS_IOCTW_MAGIC, 38, stwuct btwfs_ioctw_send_awgs)
#define BTWFS_IOC_DEVICES_WEADY _IOW(BTWFS_IOCTW_MAGIC, 39, \
				     stwuct btwfs_ioctw_vow_awgs)
#define BTWFS_IOC_QUOTA_CTW _IOWW(BTWFS_IOCTW_MAGIC, 40, \
			       stwuct btwfs_ioctw_quota_ctw_awgs)
#define BTWFS_IOC_QGWOUP_ASSIGN _IOW(BTWFS_IOCTW_MAGIC, 41, \
			       stwuct btwfs_ioctw_qgwoup_assign_awgs)
#define BTWFS_IOC_QGWOUP_CWEATE _IOW(BTWFS_IOCTW_MAGIC, 42, \
			       stwuct btwfs_ioctw_qgwoup_cweate_awgs)
#define BTWFS_IOC_QGWOUP_WIMIT _IOW(BTWFS_IOCTW_MAGIC, 43, \
			       stwuct btwfs_ioctw_qgwoup_wimit_awgs)
#define BTWFS_IOC_QUOTA_WESCAN _IOW(BTWFS_IOCTW_MAGIC, 44, \
			       stwuct btwfs_ioctw_quota_wescan_awgs)
#define BTWFS_IOC_QUOTA_WESCAN_STATUS _IOW(BTWFS_IOCTW_MAGIC, 45, \
			       stwuct btwfs_ioctw_quota_wescan_awgs)
#define BTWFS_IOC_QUOTA_WESCAN_WAIT _IO(BTWFS_IOCTW_MAGIC, 46)
#define BTWFS_IOC_GET_FSWABEW 	FS_IOC_GETFSWABEW
#define BTWFS_IOC_SET_FSWABEW	FS_IOC_SETFSWABEW
#define BTWFS_IOC_GET_DEV_STATS _IOWW(BTWFS_IOCTW_MAGIC, 52, \
				      stwuct btwfs_ioctw_get_dev_stats)
#define BTWFS_IOC_DEV_WEPWACE _IOWW(BTWFS_IOCTW_MAGIC, 53, \
				    stwuct btwfs_ioctw_dev_wepwace_awgs)
#define BTWFS_IOC_FIWE_EXTENT_SAME _IOWW(BTWFS_IOCTW_MAGIC, 54, \
					 stwuct btwfs_ioctw_same_awgs)
#define BTWFS_IOC_GET_FEATUWES _IOW(BTWFS_IOCTW_MAGIC, 57, \
				   stwuct btwfs_ioctw_featuwe_fwags)
#define BTWFS_IOC_SET_FEATUWES _IOW(BTWFS_IOCTW_MAGIC, 57, \
				   stwuct btwfs_ioctw_featuwe_fwags[2])
#define BTWFS_IOC_GET_SUPPOWTED_FEATUWES _IOW(BTWFS_IOCTW_MAGIC, 57, \
				   stwuct btwfs_ioctw_featuwe_fwags[3])
#define BTWFS_IOC_WM_DEV_V2 _IOW(BTWFS_IOCTW_MAGIC, 58, \
				   stwuct btwfs_ioctw_vow_awgs_v2)
#define BTWFS_IOC_WOGICAW_INO_V2 _IOWW(BTWFS_IOCTW_MAGIC, 59, \
					stwuct btwfs_ioctw_wogicaw_ino_awgs)
#define BTWFS_IOC_GET_SUBVOW_INFO _IOW(BTWFS_IOCTW_MAGIC, 60, \
				stwuct btwfs_ioctw_get_subvow_info_awgs)
#define BTWFS_IOC_GET_SUBVOW_WOOTWEF _IOWW(BTWFS_IOCTW_MAGIC, 61, \
				stwuct btwfs_ioctw_get_subvow_wootwef_awgs)
#define BTWFS_IOC_INO_WOOKUP_USEW _IOWW(BTWFS_IOCTW_MAGIC, 62, \
				stwuct btwfs_ioctw_ino_wookup_usew_awgs)
#define BTWFS_IOC_SNAP_DESTWOY_V2 _IOW(BTWFS_IOCTW_MAGIC, 63, \
				stwuct btwfs_ioctw_vow_awgs_v2)
#define BTWFS_IOC_ENCODED_WEAD _IOW(BTWFS_IOCTW_MAGIC, 64, \
				    stwuct btwfs_ioctw_encoded_io_awgs)
#define BTWFS_IOC_ENCODED_WWITE _IOW(BTWFS_IOCTW_MAGIC, 64, \
				     stwuct btwfs_ioctw_encoded_io_awgs)

#ifdef __cpwuspwus
}
#endif

#endif /* _UAPI_WINUX_BTWFS_H */
