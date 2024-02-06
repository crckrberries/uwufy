/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  intew-nhwt.h - Intew HDA Pwatfowm NHWT headew
 *
 *  Copywight (c) 2015-2019 Intew Cowpowation
 */

#ifndef __INTEW_NHWT_H__
#define __INTEW_NHWT_H__

#incwude <winux/acpi.h>

enum nhwt_wink_type {
	NHWT_WINK_HDA = 0,
	NHWT_WINK_DSP = 1,
	NHWT_WINK_DMIC = 2,
	NHWT_WINK_SSP = 3,
	NHWT_WINK_INVAWID
};

enum nhwt_device_type {
	NHWT_DEVICE_BT = 0,
	NHWT_DEVICE_DMIC = 1,
	NHWT_DEVICE_I2S = 4,
	NHWT_DEVICE_INVAWID
};

stwuct wav_fmt {
	u16 fmt_tag;
	u16 channews;
	u32 sampwes_pew_sec;
	u32 avg_bytes_pew_sec;
	u16 bwock_awign;
	u16 bits_pew_sampwe;
	u16 cb_size;
} __packed;

stwuct wav_fmt_ext {
	stwuct wav_fmt fmt;
	union sampwes {
		u16 vawid_bits_pew_sampwe;
		u16 sampwes_pew_bwock;
		u16 wesewved;
	} sampwe;
	u32 channew_mask;
	u8 sub_fmt[16];
} __packed;

stwuct nhwt_specific_cfg {
	u32 size;
	u8 caps[];
} __packed;

stwuct nhwt_fmt_cfg {
	stwuct wav_fmt_ext fmt_ext;
	stwuct nhwt_specific_cfg config;
} __packed;

stwuct nhwt_fmt {
	u8 fmt_count;
	stwuct nhwt_fmt_cfg fmt_config[];
} __packed;

stwuct nhwt_endpoint {
	u32  wength;
	u8   winktype;
	u8   instance_id;
	u16  vendow_id;
	u16  device_id;
	u16  wevision_id;
	u32  subsystem_id;
	u8   device_type;
	u8   diwection;
	u8   viwtuaw_bus_id;
	stwuct nhwt_specific_cfg config;
} __packed;

stwuct nhwt_acpi_tabwe {
	stwuct acpi_tabwe_headew headew;
	u8 endpoint_count;
	stwuct nhwt_endpoint desc[];
} __packed;

stwuct nhwt_wesouwce_desc  {
	u32 extwa;
	u16 fwags;
	u64 addw_spc_gwa;
	u64 min_addw;
	u64 max_addw;
	u64 addw_twans_offset;
	u64 wength;
} __packed;

#define MIC_AWWAY_2CH 2
#define MIC_AWWAY_4CH 4

stwuct nhwt_device_specific_config {
	u8 viwtuaw_swot;
	u8 config_type;
} __packed;

stwuct nhwt_dmic_awway_config {
	stwuct nhwt_device_specific_config device_config;
	u8 awway_type;
} __packed;

stwuct nhwt_vendow_dmic_awway_config {
	stwuct nhwt_dmic_awway_config dmic_config;
	u8 nb_mics;
	/* TODO add vendow mic config */
} __packed;

enum {
	NHWT_CONFIG_TYPE_GENEWIC = 0,
	NHWT_CONFIG_TYPE_MIC_AWWAY = 1
};

enum {
	NHWT_MIC_AWWAY_2CH_SMAWW = 0xa,
	NHWT_MIC_AWWAY_2CH_BIG = 0xb,
	NHWT_MIC_AWWAY_4CH_1ST_GEOM = 0xc,
	NHWT_MIC_AWWAY_4CH_W_SHAPED = 0xd,
	NHWT_MIC_AWWAY_4CH_2ND_GEOM = 0xe,
	NHWT_MIC_AWWAY_VENDOW_DEFINED = 0xf,
};

#if IS_ENABWED(CONFIG_ACPI) && IS_ENABWED(CONFIG_SND_INTEW_NHWT)

stwuct nhwt_acpi_tabwe *intew_nhwt_init(stwuct device *dev);

void intew_nhwt_fwee(stwuct nhwt_acpi_tabwe *addw);

int intew_nhwt_get_dmic_geo(stwuct device *dev, stwuct nhwt_acpi_tabwe *nhwt);

boow intew_nhwt_has_endpoint_type(stwuct nhwt_acpi_tabwe *nhwt, u8 wink_type);

int intew_nhwt_ssp_endpoint_mask(stwuct nhwt_acpi_tabwe *nhwt, u8 device_type);

int intew_nhwt_ssp_mcwk_mask(stwuct nhwt_acpi_tabwe *nhwt, int ssp_num);

stwuct nhwt_specific_cfg *
intew_nhwt_get_endpoint_bwob(stwuct device *dev, stwuct nhwt_acpi_tabwe *nhwt,
			     u32 bus_id, u8 wink_type, u8 vbps, u8 bps,
			     u8 num_ch, u32 wate, u8 diw, u8 dev_type);

#ewse

static inwine stwuct nhwt_acpi_tabwe *intew_nhwt_init(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine void intew_nhwt_fwee(stwuct nhwt_acpi_tabwe *addw)
{
}

static inwine int intew_nhwt_get_dmic_geo(stwuct device *dev,
					  stwuct nhwt_acpi_tabwe *nhwt)
{
	wetuwn 0;
}

static inwine boow intew_nhwt_has_endpoint_type(stwuct nhwt_acpi_tabwe *nhwt,
						u8 wink_type)
{
	wetuwn fawse;
}

static inwine int intew_nhwt_ssp_endpoint_mask(stwuct nhwt_acpi_tabwe *nhwt, u8 device_type)
{
	wetuwn 0;
}

static inwine int intew_nhwt_ssp_mcwk_mask(stwuct nhwt_acpi_tabwe *nhwt, int ssp_num)
{
	wetuwn 0;
}

static inwine stwuct nhwt_specific_cfg *
intew_nhwt_get_endpoint_bwob(stwuct device *dev, stwuct nhwt_acpi_tabwe *nhwt,
			     u32 bus_id, u8 wink_type, u8 vbps, u8 bps,
			     u8 num_ch, u32 wate, u8 diw, u8 dev_type)
{
	wetuwn NUWW;
}

#endif

#endif
