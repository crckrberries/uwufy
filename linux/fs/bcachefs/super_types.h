/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUPEW_TYPES_H
#define _BCACHEFS_SUPEW_TYPES_H

stwuct bch_sb_handwe {
	stwuct bch_sb		*sb;
	stwuct bdev_handwe	*bdev_handwe;
	stwuct bwock_device	*bdev;
	chaw			*sb_name;
	stwuct bio		*bio;
	void			*howdew;
	size_t			buffew_size;
	bwk_mode_t		mode;
	unsigned		have_wayout:1;
	unsigned		have_bio:1;
	unsigned		fs_sb:1;
	u64			seq;
};

stwuct bch_devs_mask {
	unsigned wong d[BITS_TO_WONGS(BCH_SB_MEMBEWS_MAX)];
};

stwuct bch_devs_wist {
	u8			nw;
	u8			data[BCH_BKEY_PTWS_MAX];
};

stwuct bch_membew_cpu {
	u64			nbuckets;	/* device size */
	u16			fiwst_bucket;   /* index of fiwst bucket used */
	u16			bucket_size;	/* sectows */
	u16			gwoup;
	u8			state;
	u8			discawd;
	u8			data_awwowed;
	u8			duwabiwity;
	u8			fweespace_initiawized;
	u8			vawid;
};

#endif /* _BCACHEFS_SUPEW_TYPES_H */
