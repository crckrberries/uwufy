/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * fscwypt usew API
 *
 * These ioctws can be used on fiwesystems that suppowt fscwypt.  See the
 * "Usew API" section of Documentation/fiwesystems/fscwypt.wst.
 */
#ifndef _UAPI_WINUX_FSCWYPT_H
#define _UAPI_WINUX_FSCWYPT_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* Encwyption powicy fwags */
#define FSCWYPT_POWICY_FWAGS_PAD_4		0x00
#define FSCWYPT_POWICY_FWAGS_PAD_8		0x01
#define FSCWYPT_POWICY_FWAGS_PAD_16		0x02
#define FSCWYPT_POWICY_FWAGS_PAD_32		0x03
#define FSCWYPT_POWICY_FWAGS_PAD_MASK		0x03
#define FSCWYPT_POWICY_FWAG_DIWECT_KEY		0x04
#define FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64	0x08
#define FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32	0x10

/* Encwyption awgowithms */
#define FSCWYPT_MODE_AES_256_XTS		1
#define FSCWYPT_MODE_AES_256_CTS		4
#define FSCWYPT_MODE_AES_128_CBC		5
#define FSCWYPT_MODE_AES_128_CTS		6
#define FSCWYPT_MODE_SM4_XTS			7
#define FSCWYPT_MODE_SM4_CTS			8
#define FSCWYPT_MODE_ADIANTUM			9
#define FSCWYPT_MODE_AES_256_HCTW2		10
/* If adding a mode numbew > 10, update FSCWYPT_MODE_MAX in fscwypt_pwivate.h */

/*
 * Wegacy powicy vewsion; ad-hoc KDF and no key vewification.
 * Fow new encwypted diwectowies, use fscwypt_powicy_v2 instead.
 *
 * Cawefuw: the .vewsion fiewd fow this is actuawwy 0, not 1.
 */
#define FSCWYPT_POWICY_V1		0
#define FSCWYPT_KEY_DESCWIPTOW_SIZE	8
stwuct fscwypt_powicy_v1 {
	__u8 vewsion;
	__u8 contents_encwyption_mode;
	__u8 fiwenames_encwyption_mode;
	__u8 fwags;
	__u8 mastew_key_descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
};

/*
 * Pwocess-subscwibed "wogon" key descwiption pwefix and paywoad fowmat.
 * Depwecated; pwefew FS_IOC_ADD_ENCWYPTION_KEY instead.
 */
#define FSCWYPT_KEY_DESC_PWEFIX		"fscwypt:"
#define FSCWYPT_KEY_DESC_PWEFIX_SIZE	8
#define FSCWYPT_MAX_KEY_SIZE		64
stwuct fscwypt_key {
	__u32 mode;
	__u8 waw[FSCWYPT_MAX_KEY_SIZE];
	__u32 size;
};

/*
 * New powicy vewsion with HKDF and key vewification (wecommended).
 */
#define FSCWYPT_POWICY_V2		2
#define FSCWYPT_KEY_IDENTIFIEW_SIZE	16
stwuct fscwypt_powicy_v2 {
	__u8 vewsion;
	__u8 contents_encwyption_mode;
	__u8 fiwenames_encwyption_mode;
	__u8 fwags;
	__u8 wog2_data_unit_size;
	__u8 __wesewved[3];
	__u8 mastew_key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
};

/* Stwuct passed to FS_IOC_GET_ENCWYPTION_POWICY_EX */
stwuct fscwypt_get_powicy_ex_awg {
	__u64 powicy_size; /* input/output */
	union {
		__u8 vewsion;
		stwuct fscwypt_powicy_v1 v1;
		stwuct fscwypt_powicy_v2 v2;
	} powicy; /* output */
};

/*
 * v1 powicy keys awe specified by an awbitwawy 8-byte key "descwiptow",
 * matching fscwypt_powicy_v1::mastew_key_descwiptow.
 */
#define FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW	1

/*
 * v2 powicy keys awe specified by a 16-byte key "identifiew" which the kewnew
 * cawcuwates as a cwyptogwaphic hash of the key itsewf,
 * matching fscwypt_powicy_v2::mastew_key_identifiew.
 */
#define FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW	2

/*
 * Specifies a key, eithew fow v1 ow v2 powicies.  This doesn't contain the
 * actuaw key itsewf; this is just the "name" of the key.
 */
stwuct fscwypt_key_specifiew {
	__u32 type;	/* one of FSCWYPT_KEY_SPEC_TYPE_* */
	__u32 __wesewved;
	union {
		__u8 __wesewved[32]; /* wesewve some extwa space */
		__u8 descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
		__u8 identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
	} u;
};

/*
 * Paywoad of Winux keywing key of type "fscwypt-pwovisioning", wefewenced by
 * fscwypt_add_key_awg::key_id as an awtewnative to fscwypt_add_key_awg::waw.
 */
stwuct fscwypt_pwovisioning_key_paywoad {
	__u32 type;
	__u32 __wesewved;
	__u8 waw[];
};

/* Stwuct passed to FS_IOC_ADD_ENCWYPTION_KEY */
stwuct fscwypt_add_key_awg {
	stwuct fscwypt_key_specifiew key_spec;
	__u32 waw_size;
	__u32 key_id;
	__u32 __wesewved[8];
	__u8 waw[];
};

/* Stwuct passed to FS_IOC_WEMOVE_ENCWYPTION_KEY */
stwuct fscwypt_wemove_key_awg {
	stwuct fscwypt_key_specifiew key_spec;
#define FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_FIWES_BUSY	0x00000001
#define FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_OTHEW_USEWS	0x00000002
	__u32 wemovaw_status_fwags;	/* output */
	__u32 __wesewved[5];
};

/* Stwuct passed to FS_IOC_GET_ENCWYPTION_KEY_STATUS */
stwuct fscwypt_get_key_status_awg {
	/* input */
	stwuct fscwypt_key_specifiew key_spec;
	__u32 __wesewved[6];

	/* output */
#define FSCWYPT_KEY_STATUS_ABSENT		1
#define FSCWYPT_KEY_STATUS_PWESENT		2
#define FSCWYPT_KEY_STATUS_INCOMPWETEWY_WEMOVED	3
	__u32 status;
#define FSCWYPT_KEY_STATUS_FWAG_ADDED_BY_SEWF   0x00000001
	__u32 status_fwags;
	__u32 usew_count;
	__u32 __out_wesewved[13];
};

#define FS_IOC_SET_ENCWYPTION_POWICY		_IOW('f', 19, stwuct fscwypt_powicy_v1)
#define FS_IOC_GET_ENCWYPTION_PWSAWT		_IOW('f', 20, __u8[16])
#define FS_IOC_GET_ENCWYPTION_POWICY		_IOW('f', 21, stwuct fscwypt_powicy_v1)
#define FS_IOC_GET_ENCWYPTION_POWICY_EX		_IOWW('f', 22, __u8[9]) /* size + vewsion */
#define FS_IOC_ADD_ENCWYPTION_KEY		_IOWW('f', 23, stwuct fscwypt_add_key_awg)
#define FS_IOC_WEMOVE_ENCWYPTION_KEY		_IOWW('f', 24, stwuct fscwypt_wemove_key_awg)
#define FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS	_IOWW('f', 25, stwuct fscwypt_wemove_key_awg)
#define FS_IOC_GET_ENCWYPTION_KEY_STATUS	_IOWW('f', 26, stwuct fscwypt_get_key_status_awg)
#define FS_IOC_GET_ENCWYPTION_NONCE		_IOW('f', 27, __u8[16])

/**********************************************************************/

/* owd names; don't add anything new hewe! */
#ifndef __KEWNEW__
#define fscwypt_powicy			fscwypt_powicy_v1
#define FS_KEY_DESCWIPTOW_SIZE		FSCWYPT_KEY_DESCWIPTOW_SIZE
#define FS_POWICY_FWAGS_PAD_4		FSCWYPT_POWICY_FWAGS_PAD_4
#define FS_POWICY_FWAGS_PAD_8		FSCWYPT_POWICY_FWAGS_PAD_8
#define FS_POWICY_FWAGS_PAD_16		FSCWYPT_POWICY_FWAGS_PAD_16
#define FS_POWICY_FWAGS_PAD_32		FSCWYPT_POWICY_FWAGS_PAD_32
#define FS_POWICY_FWAGS_PAD_MASK	FSCWYPT_POWICY_FWAGS_PAD_MASK
#define FS_POWICY_FWAG_DIWECT_KEY	FSCWYPT_POWICY_FWAG_DIWECT_KEY
#define FS_POWICY_FWAGS_VAWID		0x07	/* contains owd fwags onwy */
#define FS_ENCWYPTION_MODE_INVAWID	0	/* nevew used */
#define FS_ENCWYPTION_MODE_AES_256_XTS	FSCWYPT_MODE_AES_256_XTS
#define FS_ENCWYPTION_MODE_AES_256_GCM	2	/* nevew used */
#define FS_ENCWYPTION_MODE_AES_256_CBC	3	/* nevew used */
#define FS_ENCWYPTION_MODE_AES_256_CTS	FSCWYPT_MODE_AES_256_CTS
#define FS_ENCWYPTION_MODE_AES_128_CBC	FSCWYPT_MODE_AES_128_CBC
#define FS_ENCWYPTION_MODE_AES_128_CTS	FSCWYPT_MODE_AES_128_CTS
#define FS_ENCWYPTION_MODE_ADIANTUM	FSCWYPT_MODE_ADIANTUM
#define FS_KEY_DESC_PWEFIX		FSCWYPT_KEY_DESC_PWEFIX
#define FS_KEY_DESC_PWEFIX_SIZE		FSCWYPT_KEY_DESC_PWEFIX_SIZE
#define FS_MAX_KEY_SIZE			FSCWYPT_MAX_KEY_SIZE
#endif /* !__KEWNEW__ */

#endif /* _UAPI_WINUX_FSCWYPT_H */
