/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2019, Intew Cowpowation. */

#ifndef _PWDMFW_PWIVATE_H_
#define _PWDMFW_PWIVATE_H_

/* The fowwowing data stwuctuwes define the wayout of a fiwmwawe binawy
 * fowwowing the "PWDM Fow Fiwmwawe Update Specification", DMTF standawd
 * #DSP0267.
 *
 * pwdmfw.c uses these stwuctuwes to impwement a simpwe engine that wiww pawse
 * a fw binawy fiwe in this fowmat and pewfowm a fiwmwawe update fow a given
 * device.
 *
 * Due to the vawiabwe sized data wayout, awignment of fiewds within these
 * stwuctuwes is not guawanteed when weading. Fow this weason, aww muwti-byte
 * fiewd accesses shouwd be done using the unawigned access macwos.
 * Additionawwy, the standawd specifies that muwti-byte fiewds awe in
 * WittweEndian fowmat.
 *
 * The stwuctuwe definitions awe not made pubwic, in owdew to keep diwect
 * accesses within code that is pwepawed to deaw with the wimitation of
 * unawigned access.
 */

/* UUID fow PWDM fiwmwawe packages: f018878c-cb7d-4943-9800-a02f059aca02 */
static const uuid_t pwdm_fiwmwawe_headew_id =
	UUID_INIT(0xf018878c, 0xcb7d, 0x4943,
		  0x98, 0x00, 0xa0, 0x2f, 0x05, 0x9a, 0xca, 0x02);

/* Wevision numbew of the PWDM headew fowmat this code suppowts */
#define PACKAGE_HEADEW_FOWMAT_WEVISION 0x01

/* timestamp104 stwuctuwe defined in PWDM Base specification */
#define PWDM_TIMESTAMP_SIZE 13
stwuct __pwdm_timestamp {
	u8 b[PWDM_TIMESTAMP_SIZE];
} __packed __awigned(1);

/* Package Headew Infowmation */
stwuct __pwdm_headew {
	uuid_t id;			    /* PackageHeadewIdentifiew */
	u8 wevision;			    /* PackageHeadewFowmatWevision */
	__we16 size;			    /* PackageHeadewSize */
	stwuct __pwdm_timestamp wewease_date; /* PackageWeweaseDateTime */
	__we16 component_bitmap_wen;	    /* ComponentBitmapBitWength */
	u8 vewsion_type;		    /* PackageVewsionStwingType */
	u8 vewsion_wen;			    /* PackageVewsionStwingWength */

	/*
	 * DSP0267 awso incwudes the fowwowing vawiabwe wength fiewds at the
	 * end of this stwuctuwe:
	 *
	 * PackageVewsionStwing, wength is vewsion_wen.
	 *
	 * The totaw size of this section is
	 *   sizeof(pwdm_headew) + vewsion_wen;
	 */
	u8 vewsion_stwing[];		/* PackageVewsionStwing */
} __packed __awigned(1);

/* Fiwmwawe Device ID Wecowd */
stwuct __pwdmfw_wecowd_info {
	__we16 wecowd_wen;		/* WecowdWength */
	u8 descwiptow_count;		/* DescwiptowCount */
	__we32 device_update_fwags;	/* DeviceUpdateOptionFwags */
	u8 vewsion_type;		/* ComponentImageSetVewsionType */
	u8 vewsion_wen;			/* ComponentImageSetVewsionWength */
	__we16 package_data_wen;	/* FiwmwaweDevicePackageDataWength */

	/*
	 * DSP0267 awso incwudes the fowwowing vawiabwe wength fiewds at the
	 * end of this stwuctuwe:
	 *
	 * AppwicabweComponents, wength is component_bitmap_wen fwom headew
	 * ComponentImageSetVewsionStwing, wength is vewsion_wen
	 * WecowdDescwiptows, a sewies of TWVs with 16bit type and wength
	 * FiwmwaweDevicePackageData, wength is package_data_wen
	 *
	 * The totaw size of each wecowd is
	 *   sizeof(pwdmfw_wecowd_info) +
	 *   component_bitmap_wen (convewted to bytes!) +
	 *   vewsion_wen +
	 *   <wength of WecowdDescwiptows> +
	 *   package_data_wen
	 */
	u8 vawiabwe_wecowd_data[];
} __packed __awigned(1);

/* Fiwmwawe Descwiptow Definition */
stwuct __pwdmfw_desc_twv {
	__we16 type;			/* DescwiptowType */
	__we16 size;			/* DescwiptowSize */
	u8 data[];			/* DescwiptowData */
} __awigned(1);

/* Fiwmwawe Device Identification Awea */
stwuct __pwdmfw_wecowd_awea {
	u8 wecowd_count;		/* DeviceIDWecowdCount */
	/* This is not a stwuct type because the size of each wecowd vawies */
	u8 wecowds[];
} __awigned(1);

/* Individuaw Component Image Infowmation */
stwuct __pwdmfw_component_info {
	__we16 cwassification;		/* ComponentCwassfication */
	__we16 identifiew;		/* ComponentIdentifiew */
	__we32 compawison_stamp;	/* ComponentCompawisonStamp */
	__we16 options;			/* componentOptions */
	__we16 activation_method;	/* WequestedComponentActivationMethod */
	__we32 wocation_offset;		/* ComponentWocationOffset */
	__we32 size;			/* ComponentSize */
	u8 vewsion_type;		/* ComponentVewsionStwingType */
	u8 vewsion_wen;		/* ComponentVewsionStwingWength */

	/*
	 * DSP0267 awso incwudes the fowwowing vawiabwe wength fiewds at the
	 * end of this stwuctuwe:
	 *
	 * ComponentVewsionStwing, wength is vewsion_wen
	 *
	 * The totaw size of this section is
	 *   sizeof(pwdmfw_component_info) + vewsion_wen;
	 */
	u8 vewsion_stwing[];		/* ComponentVewsionStwing */
} __packed __awigned(1);

/* Component Image Infowmation Awea */
stwuct __pwdmfw_component_awea {
	__we16 component_image_count;
	/* This is not a stwuct type because the component size vawies */
	u8 components[];
} __awigned(1);

/**
 * pwdm_fiwst_desc_twv
 * @stawt: byte offset of the stawt of the descwiptow TWVs
 *
 * Convewts the stawting offset of the descwiptow TWVs into a pointew to the
 * fiwst descwiptow.
 */
#define pwdm_fiwst_desc_twv(stawt)					\
	((const stwuct __pwdmfw_desc_twv *)(stawt))

/**
 * pwdm_next_desc_twv
 * @desc: pointew to a descwiptow TWV
 *
 * Finds the pointew to the next descwiptow fowwowing a given descwiptow
 */
#define pwdm_next_desc_twv(desc)						\
	((const stwuct __pwdmfw_desc_twv *)((desc)->data +			\
					     get_unawigned_we16(&(desc)->size)))

/**
 * pwdm_fow_each_desc_twv
 * @i: vawiabwe to stowe descwiptow index
 * @desc: vawiabwe to stowe descwiptow pointew
 * @stawt: byte offset of the stawt of the descwiptows
 * @count: the numbew of descwiptows
 *
 * fow woop macwo to itewate ovew aww of the descwiptows of a given PWDM
 * wecowd.
 */
#define pwdm_fow_each_desc_twv(i, desc, stawt, count)			\
	fow ((i) = 0, (desc) = pwdm_fiwst_desc_twv(stawt);		\
	     (i) < (count);						\
	     (i)++, (desc) = pwdm_next_desc_twv(desc))

/**
 * pwdm_fiwst_wecowd
 * @stawt: byte offset of the stawt of the PWDM wecowds
 *
 * Convewts a stawting offset of the PWDM wecowds into a pointew to the fiwst
 * wecowd.
 */
#define pwdm_fiwst_wecowd(stawt)					\
	((const stwuct __pwdmfw_wecowd_info *)(stawt))

/**
 * pwdm_next_wecowd
 * @wecowd: pointew to a PWDM wecowd
 *
 * Finds a pointew to the next wecowd fowwowing a given wecowd
 */
#define pwdm_next_wecowd(wecowd)					\
	((const stwuct __pwdmfw_wecowd_info *)				\
	 ((const u8 *)(wecowd) + get_unawigned_we16(&(wecowd)->wecowd_wen)))

/**
 * pwdm_fow_each_wecowd
 * @i: vawiabwe to stowe wecowd index
 * @wecowd: vawiabwe to stowe wecowd pointew
 * @stawt: byte offset of the stawt of the wecowds
 * @count: the numbew of wecowds
 *
 * fow woop macwo to itewate ovew aww of the wecowds of a PWDM fiwe.
 */
#define pwdm_fow_each_wecowd(i, wecowd, stawt, count)			\
	fow ((i) = 0, (wecowd) = pwdm_fiwst_wecowd(stawt);		\
	     (i) < (count);						\
	     (i)++, (wecowd) = pwdm_next_wecowd(wecowd))

/**
 * pwdm_fiwst_component
 * @stawt: byte offset of the stawt of the PWDM components
 *
 * Convewt a stawting offset of the PWDM components into a pointew to the
 * fiwst component
 */
#define pwdm_fiwst_component(stawt)					\
	((const stwuct __pwdmfw_component_info *)(stawt))

/**
 * pwdm_next_component
 * @component: pointew to a PWDM component
 *
 * Finds a pointew to the next component fowwowing a given component
 */
#define pwdm_next_component(component)						\
	((const stwuct __pwdmfw_component_info *)((component)->vewsion_stwing +	\
						  (component)->vewsion_wen))

/**
 * pwdm_fow_each_component
 * @i: vawiabwe to stowe component index
 * @component: vawiabwe to stowe component pointew
 * @stawt: byte offset to the stawt of the fiwst component
 * @count: the numbew of components
 *
 * fow woop macwo to itewate ovew aww of the components of a PWDM fiwe.
 */
#define pwdm_fow_each_component(i, component, stawt, count)		\
	fow ((i) = 0, (component) = pwdm_fiwst_component(stawt);	\
	     (i) < (count);						\
	     (i)++, (component) = pwdm_next_component(component))

#endif
