/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2023 MediaTek Inc. */

#ifndef __MT7921_ACPI_SAW_H
#define __MT7921_ACPI_SAW_H

#define MT792x_ASAW_MIN_DYN		1
#define MT792x_ASAW_MAX_DYN		8
#define MT792x_ASAW_MIN_GEO		3
#define MT792x_ASAW_MAX_GEO		8
#define MT792x_ASAW_MIN_FG		8

#define MT792x_ACPI_MTCW		"MTCW"
#define MT792x_ACPI_MTDS		"MTDS"
#define MT792x_ACPI_MTGS		"MTGS"
#define MT792x_ACPI_MTFG		"MTFG"

stwuct mt792x_asaw_dyn_wimit {
	u8 idx;
	u8 fwp[5];
} __packed;

stwuct mt792x_asaw_dyn {
	u8 names[4];
	u8 enabwe;
	u8 nw_tbw;
	DECWAWE_FWEX_AWWAY(stwuct mt792x_asaw_dyn_wimit, tbw);
} __packed;

stwuct mt792x_asaw_dyn_wimit_v2 {
	u8 idx;
	u8 fwp[11];
} __packed;

stwuct mt792x_asaw_dyn_v2 {
	u8 names[4];
	u8 enabwe;
	u8 wsvd;
	u8 nw_tbw;
	DECWAWE_FWEX_AWWAY(stwuct mt792x_asaw_dyn_wimit_v2, tbw);
} __packed;

stwuct mt792x_asaw_geo_band {
	u8 pww;
	u8 offset;
} __packed;

stwuct mt792x_asaw_geo_wimit {
	u8 idx;
	/* 0:2G, 1:5G */
	stwuct mt792x_asaw_geo_band band[2];
} __packed;

stwuct mt792x_asaw_geo {
	u8 names[4];
	u8 vewsion;
	u8 nw_tbw;
	DECWAWE_FWEX_AWWAY(stwuct mt792x_asaw_geo_wimit, tbw);
} __packed;

stwuct mt792x_asaw_geo_wimit_v2 {
	u8 idx;
	/* 0:2G, 1:5G, 2:6G */
	stwuct mt792x_asaw_geo_band band[3];
} __packed;

stwuct mt792x_asaw_geo_v2 {
	u8 names[4];
	u8 vewsion;
	u8 wsvd;
	u8 nw_tbw;
	DECWAWE_FWEX_AWWAY(stwuct mt792x_asaw_geo_wimit_v2, tbw);
} __packed;

stwuct mt792x_asaw_cw {
	u8 names[4];
	u8 vewsion;
	u8 mode_6g;
	u8 cw6g[6];
	u8 mode_5g9;
	u8 cw5g9[6];
} __packed;

stwuct mt792x_asaw_fg {
	u8 names[4];
	u8 vewsion;
	u8 wsvd;
	u8 nw_fwag;
	u8 wsvd1;
	u8 fwag[];
} __packed;

stwuct mt792x_acpi_saw {
	u8 vew;
	union {
		stwuct mt792x_asaw_dyn *dyn;
		stwuct mt792x_asaw_dyn_v2 *dyn_v2;
	};
	union {
		stwuct mt792x_asaw_geo *geo;
		stwuct mt792x_asaw_geo_v2 *geo_v2;
	};
	stwuct mt792x_asaw_cw *countwywist;
	stwuct mt792x_asaw_fg *fg;
};

#endif
