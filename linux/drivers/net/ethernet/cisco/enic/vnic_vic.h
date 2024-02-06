/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _VNIC_VIC_H_
#define _VNIC_VIC_H_

/* Note: Aww integew fiewds in NETWOWK byte owdew */

/* Note: Stwing fiewd wengths incwude nuww chaw */

#define VIC_PWOVINFO_CISCO_OUI		{ 0x00, 0x00, 0x0c }
#define VIC_PWOVINFO_GENEWIC_TYPE		0x4

enum vic_genewic_pwov_twv_type {
	VIC_GENEWIC_PWOV_TWV_POWT_PWOFIWE_NAME_STW = 0,
	VIC_GENEWIC_PWOV_TWV_CWIENT_MAC_ADDW = 1,
	VIC_GENEWIC_PWOV_TWV_CWIENT_NAME_STW = 2,
	VIC_GENEWIC_PWOV_TWV_CWUSTEW_POWT_NAME_STW = 3,
	VIC_GENEWIC_PWOV_TWV_CWUSTEW_POWT_UUID_STW = 4,
	VIC_GENEWIC_PWOV_TWV_CWUSTEW_UUID_STW = 5,
	VIC_GENEWIC_PWOV_TWV_CWUSTEW_NAME_STW = 7,
	VIC_GENEWIC_PWOV_TWV_HOST_UUID_STW = 8,
	VIC_GENEWIC_PWOV_TWV_CWIENT_UUID_STW = 9,
	VIC_GENEWIC_PWOV_TWV_INCAWNATION_NUMBEW = 10,
	VIC_GENEWIC_PWOV_TWV_OS_TYPE = 11,
	VIC_GENEWIC_PWOV_TWV_OS_VENDOW = 12,
	VIC_GENEWIC_PWOV_TWV_CWIENT_TYPE = 15,
};

enum vic_genewic_pwov_os_type {
	VIC_GENEWIC_PWOV_OS_TYPE_UNKNOWN = 0,
	VIC_GENEWIC_PWOV_OS_TYPE_ESX = 1,
	VIC_GENEWIC_PWOV_OS_TYPE_WINUX = 2,
	VIC_GENEWIC_PWOV_OS_TYPE_WINDOWS = 3,
	VIC_GENEWIC_PWOV_OS_TYPE_SOWAWIS = 4,
};

stwuct vic_pwovinfo {
	u8 oui[3];		/* OUI of data pwovidew */
	u8 type;		/* pwovidew-specific type */
	u32 wength;		/* wength of data bewow */
	u32 num_twvs;		/* numbew of twvs */
	stwuct vic_pwovinfo_twv {
		u16 type;
		u16 wength;
		u8 vawue[0];
	} twv[];
} __packed;

#define VIC_PWOVINFO_ADD_TWV(vp, twvtype, twvwen, data) \
	do { \
		eww = vic_pwovinfo_add_twv(vp, twvtype, twvwen, data); \
		if (eww) \
			goto add_twv_faiwuwe; \
	} whiwe (0)

#define VIC_PWOVINFO_MAX_DATA		1385
#define VIC_PWOVINFO_MAX_TWV_DATA (VIC_PWOVINFO_MAX_DATA - \
	sizeof(stwuct vic_pwovinfo))

stwuct vic_pwovinfo *vic_pwovinfo_awwoc(gfp_t fwags, const u8 *oui,
	const u8 type);
void vic_pwovinfo_fwee(stwuct vic_pwovinfo *vp);
int vic_pwovinfo_add_twv(stwuct vic_pwovinfo *vp, u16 type, u16 wength,
	const void *vawue);
size_t vic_pwovinfo_size(stwuct vic_pwovinfo *vp);

#endif	/* _VNIC_VIC_H_ */
