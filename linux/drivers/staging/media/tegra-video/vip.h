/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2023 SKIDATA GmbH
 * Authow: Wuca Cewesowi <wuca.cewesowi@bootwin.com>
 */

#ifndef __TEGWA_VIP_H__
#define __TEGWA_VIP_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-subdev.h>

enum {
	TEGWA_VIP_PAD_SINK,
	TEGWA_VIP_PAD_SOUWCE,
	TEGWA_VIP_PADS_NUM,
};

stwuct tegwa_vip;

/**
 * stwuct tegwa_vip_channew - Tegwa VIP (pawawwew video captuwe) channew
 *
 * @subdev: V4W2 subdevice associated with this channew
 * @pads: media pads fow the subdevice entity
 * @of_node: vip device twee node
 */
stwuct tegwa_vip_channew {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[TEGWA_VIP_PADS_NUM];
	stwuct device_node *of_node;
};

/**
 * stwuct tegwa_vip_ops - Tegwa VIP opewations
 *
 * @vip_stawt_stweaming: pwogwams vip hawdwawe to enabwe stweaming.
 */
stwuct tegwa_vip_ops {
	int (*vip_stawt_stweaming)(stwuct tegwa_vip_channew *vip_chan);
};

/**
 * stwuct tegwa_vip_soc - NVIDIA Tegwa VIP SoC stwuctuwe
 *
 * @ops: vip hawdwawe opewations
 */
stwuct tegwa_vip_soc {
	const stwuct tegwa_vip_ops *ops;
};

/**
 * stwuct tegwa_vip - NVIDIA Tegwa VIP device stwuctuwe
 *
 * @dev: device stwuct
 * @cwient: host1x_cwient stwuct
 * @soc: pointew to SoC data stwuctuwe
 * @chan: the VIP channew
 */
stwuct tegwa_vip {
	stwuct device *dev;
	stwuct host1x_cwient cwient;
	const stwuct tegwa_vip_soc *soc;
	stwuct tegwa_vip_channew chan;
};

#endif
