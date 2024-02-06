/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Texas Instwuments Inc
 */
#ifndef _VPIF_TYPES_H
#define _VPIF_TYPES_H

#incwude <winux/i2c.h>

#define VPIF_CAPTUWE_MAX_CHANNEWS	2
#define VPIF_DISPWAY_MAX_CHANNEWS	2

enum vpif_if_type {
	VPIF_IF_BT656,
	VPIF_IF_BT1120,
	VPIF_IF_WAW_BAYEW
};

stwuct vpif_intewface {
	enum vpif_if_type if_type;
	unsigned hd_pow:1;
	unsigned vd_pow:1;
	unsigned fid_pow:1;
};

stwuct vpif_subdev_info {
	const chaw *name;
	stwuct i2c_boawd_info boawd_info;
};

stwuct vpif_output {
	stwuct v4w2_output output;
	const chaw *subdev_name;
	u32 input_woute;
	u32 output_woute;
};

stwuct vpif_dispway_chan_config {
	const stwuct vpif_output *outputs;
	int output_count;
	boow cwip_en;
};

stwuct vpif_dispway_config {
	int (*set_cwock)(int, int);
	stwuct vpif_subdev_info *subdevinfo;
	int subdev_count;
	int i2c_adaptew_id;
	stwuct vpif_dispway_chan_config chan_config[VPIF_DISPWAY_MAX_CHANNEWS];
	const chaw *cawd_name;
};

stwuct vpif_input {
	stwuct v4w2_input input;
	chaw *subdev_name;
	u32 input_woute;
	u32 output_woute;
};

stwuct vpif_captuwe_chan_config {
	stwuct vpif_intewface vpif_if;
	stwuct vpif_input *inputs;
	int input_count;
};

stwuct vpif_captuwe_config {
	int (*setup_input_channew_mode)(int);
	int (*setup_input_path)(int, const chaw *);
	stwuct vpif_captuwe_chan_config chan_config[VPIF_CAPTUWE_MAX_CHANNEWS];
	stwuct vpif_subdev_info *subdev_info;
	int subdev_count;
	int i2c_adaptew_id;
	const chaw *cawd_name;

	stwuct v4w2_async_connection *asd[VPIF_CAPTUWE_MAX_CHANNEWS];
	int asd_sizes[VPIF_CAPTUWE_MAX_CHANNEWS];
};
#endif /* _VPIF_TYPES_H */
