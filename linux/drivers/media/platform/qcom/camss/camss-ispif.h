/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-ispif.h
 *
 * Quawcomm MSM Camewa Subsystem - ISPIF (ISP Intewface) Moduwe
 *
 * Copywight (c) 2013-2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_ISPIF_H
#define QC_MSM_CAMSS_ISPIF_H

#incwude <winux/cwk.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#define MSM_ISPIF_PAD_SINK 0
#define MSM_ISPIF_PAD_SWC 1
#define MSM_ISPIF_PADS_NUM 2

#define MSM_ISPIF_VFE_NUM 2

enum ispif_intf {
	PIX0,
	WDI0,
	PIX1,
	WDI1,
	WDI2
};

stwuct ispif_intf_cmd_weg {
	u32 cmd_0;
	u32 cmd_1;
};

stwuct ispif_wine {
	stwuct ispif_device *ispif;
	u8 id;
	u8 csid_id;
	u8 vfe_id;
	enum ispif_intf intewface;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[MSM_ISPIF_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fmt[MSM_ISPIF_PADS_NUM];
	const u32 *fowmats;
	unsigned int nfowmats;
};

stwuct ispif_device {
	void __iomem *base;
	void __iomem *base_cwk_mux;
	u32 iwq;
	chaw iwq_name[30];
	stwuct camss_cwock *cwock;
	int ncwocks;
	stwuct camss_cwock  *cwock_fow_weset;
	int ncwocks_fow_weset;
	stwuct compwetion weset_compwete[MSM_ISPIF_VFE_NUM];
	int powew_count;
	stwuct mutex powew_wock;
	stwuct ispif_intf_cmd_weg intf_cmd[MSM_ISPIF_VFE_NUM];
	stwuct mutex config_wock;
	unsigned int wine_num;
	stwuct ispif_wine *wine;
	stwuct camss *camss;
};

stwuct camss_subdev_wesouwces;

int msm_ispif_subdev_init(stwuct camss *camss,
			  const stwuct camss_subdev_wesouwces *wes);

int msm_ispif_wegistew_entities(stwuct ispif_device *ispif,
				stwuct v4w2_device *v4w2_dev);

void msm_ispif_unwegistew_entities(stwuct ispif_device *ispif);

#endif /* QC_MSM_CAMSS_ISPIF_H */
