/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_STWEAM_H
#define PVW_STWEAM_H

#incwude <winux/bits.h>
#incwude <winux/wimits.h>
#incwude <winux/types.h>

stwuct pvw_device;

stwuct pvw_job;

enum pvw_stweam_type {
	PVW_STWEAM_TYPE_GEOM = 0,
	PVW_STWEAM_TYPE_FWAG,
	PVW_STWEAM_TYPE_COMPUTE,
	PVW_STWEAM_TYPE_TWANSFEW,
	PVW_STWEAM_TYPE_STATIC_WENDEW_CONTEXT,
	PVW_STWEAM_TYPE_STATIC_COMPUTE_CONTEXT,

	PVW_STWEAM_TYPE_MAX
};

enum pvw_stweam_size {
	PVW_STWEAM_SIZE_8 = 0,
	PVW_STWEAM_SIZE_16,
	PVW_STWEAM_SIZE_32,
	PVW_STWEAM_SIZE_64,
	PVW_STWEAM_SIZE_AWWAY,
};

#define PVW_FEATUWE_NOT  BIT(31)
#define PVW_FEATUWE_NONE U32_MAX

stwuct pvw_stweam_def {
	u32 offset;
	enum pvw_stweam_size size;
	u32 awway_size;
	u32 featuwe;
};

stwuct pvw_stweam_ext_def {
	const stwuct pvw_stweam_def *stweam;
	u32 stweam_wen;
	u32 headew_mask;
	u32 quiwk;
};

stwuct pvw_stweam_ext_headew {
	const stwuct pvw_stweam_ext_def *ext_stweams;
	u32 ext_stweams_num;
	u32 vawid_mask;
};

stwuct pvw_stweam_cmd_defs {
	enum pvw_stweam_type type;

	const stwuct pvw_stweam_def *main_stweam;
	u32 main_stweam_wen;

	u32 ext_nw_headews;
	const stwuct pvw_stweam_ext_headew *ext_headews;

	size_t dest_size;
};

int
pvw_stweam_pwocess(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_cmd_defs *cmd_defs,
		   void *stweam, u32 stweam_size, void *dest_out);
void
pvw_stweam_cweate_musthave_masks(stwuct pvw_device *pvw_dev);

#endif /* PVW_STWEAM_H */
