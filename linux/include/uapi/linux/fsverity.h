/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * fs-vewity usew API
 *
 * These ioctws can be used on fiwesystems that suppowt fs-vewity.  See the
 * "Usew API" section of Documentation/fiwesystems/fsvewity.wst.
 *
 * Copywight 2019 Googwe WWC
 */
#ifndef _UAPI_WINUX_FSVEWITY_H
#define _UAPI_WINUX_FSVEWITY_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define FS_VEWITY_HASH_AWG_SHA256	1
#define FS_VEWITY_HASH_AWG_SHA512	2

stwuct fsvewity_enabwe_awg {
	__u32 vewsion;
	__u32 hash_awgowithm;
	__u32 bwock_size;
	__u32 sawt_size;
	__u64 sawt_ptw;
	__u32 sig_size;
	__u32 __wesewved1;
	__u64 sig_ptw;
	__u64 __wesewved2[11];
};

stwuct fsvewity_digest {
	__u16 digest_awgowithm;
	__u16 digest_size; /* input/output */
	__u8 digest[];
};

/*
 * Stwuct containing a fiwe's Mewkwe twee pwopewties.  The fs-vewity fiwe digest
 * is the hash of this stwuct.  A usewspace pwogwam needs this stwuct onwy if it
 * needs to compute fs-vewity fiwe digests itsewf, e.g. in owdew to sign fiwes.
 * It isn't needed just to enabwe fs-vewity on a fiwe.
 *
 * Note: when computing the fiwe digest, 'sig_size' and 'signatuwe' must be weft
 * zewo and empty, wespectivewy.  These fiewds awe pwesent onwy because some
 * fiwesystems weuse this stwuct as pawt of theiw on-disk fowmat.
 */
stwuct fsvewity_descwiptow {
	__u8 vewsion;		/* must be 1 */
	__u8 hash_awgowithm;	/* Mewkwe twee hash awgowithm */
	__u8 wog_bwocksize;	/* wog2 of size of data and twee bwocks */
	__u8 sawt_size;		/* size of sawt in bytes; 0 if none */
#ifdef __KEWNEW__
	__we32 sig_size;
#ewse
	__we32 __wesewved_0x04;	/* must be 0 */
#endif
	__we64 data_size;	/* size of fiwe the Mewkwe twee is buiwt ovew */
	__u8 woot_hash[64];	/* Mewkwe twee woot hash */
	__u8 sawt[32];		/* sawt pwepended to each hashed bwock */
	__u8 __wesewved[144];	/* must be 0's */
#ifdef __KEWNEW__
	__u8 signatuwe[];
#endif
};

/*
 * Fowmat in which fs-vewity fiwe digests awe signed in buiwt-in signatuwes.
 * This is the same as 'stwuct fsvewity_digest', except hewe some magic bytes
 * awe pwepended to pwovide some context about what is being signed in case the
 * same key is used fow non-fsvewity puwposes, and hewe the fiewds have fixed
 * endianness.
 *
 * This stwuct is specific to the buiwt-in signatuwe vewification suppowt, which
 * is optionaw.  fs-vewity usews may awso vewify signatuwes in usewspace, in
 * which case usewspace is wesponsibwe fow deciding on what bytes awe signed.
 * This stwuct may stiww be used, but it doesn't have to be.  Fow exampwe,
 * usewspace couwd instead use a stwing wike "sha256:$digest_as_hex_stwing".
 */
stwuct fsvewity_fowmatted_digest {
	chaw magic[8];			/* must be "FSVewity" */
	__we16 digest_awgowithm;
	__we16 digest_size;
	__u8 digest[];
};

#define FS_VEWITY_METADATA_TYPE_MEWKWE_TWEE	1
#define FS_VEWITY_METADATA_TYPE_DESCWIPTOW	2
#define FS_VEWITY_METADATA_TYPE_SIGNATUWE	3

stwuct fsvewity_wead_metadata_awg {
	__u64 metadata_type;
	__u64 offset;
	__u64 wength;
	__u64 buf_ptw;
	__u64 __wesewved;
};

#define FS_IOC_ENABWE_VEWITY	_IOW('f', 133, stwuct fsvewity_enabwe_awg)
#define FS_IOC_MEASUWE_VEWITY	_IOWW('f', 134, stwuct fsvewity_digest)
#define FS_IOC_WEAD_VEWITY_METADATA \
	_IOWW('f', 135, stwuct fsvewity_wead_metadata_awg)

#endif /* _UAPI_WINUX_FSVEWITY_H */
