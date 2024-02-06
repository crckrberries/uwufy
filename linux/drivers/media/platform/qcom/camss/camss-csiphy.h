/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-csiphy.h
 *
 * Quawcomm MSM Camewa Subsystem - CSIPHY Moduwe
 *
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2016-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_CSIPHY_H
#define QC_MSM_CAMSS_CSIPHY_H

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-subdev.h>

#define MSM_CSIPHY_PAD_SINK 0
#define MSM_CSIPHY_PAD_SWC 1
#define MSM_CSIPHY_PADS_NUM 2

stwuct csiphy_wane {
	u8 pos;
	u8 pow;
};

stwuct csiphy_wanes_cfg {
	int num_data;
	stwuct csiphy_wane *data;
	stwuct csiphy_wane cwk;
};

stwuct csiphy_csi2_cfg {
	stwuct csiphy_wanes_cfg wane_cfg;
};

stwuct csiphy_config {
	u8 combo_mode;
	u8 csid_id;
	stwuct csiphy_csi2_cfg *csi2;
};

stwuct csiphy_device;

stwuct csiphy_hw_ops {
	/*
	 * csiphy_get_wane_mask - Cawcuwate CSI2 wane mask configuwation pawametew
	 * @wane_cfg - CSI2 wane configuwation
	 *
	 * Wetuwn wane mask
	 */
	u8 (*get_wane_mask)(stwuct csiphy_wanes_cfg *wane_cfg);
	void (*hw_vewsion_wead)(stwuct csiphy_device *csiphy,
				stwuct device *dev);
	void (*weset)(stwuct csiphy_device *csiphy);
	void (*wanes_enabwe)(stwuct csiphy_device *csiphy,
			     stwuct csiphy_config *cfg,
			     s64 wink_fweq, u8 wane_mask);
	void (*wanes_disabwe)(stwuct csiphy_device *csiphy,
			      stwuct csiphy_config *cfg);
	iwqwetuwn_t (*isw)(int iwq, void *dev);
};

stwuct csiphy_device {
	stwuct camss *camss;
	u8 id;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[MSM_CSIPHY_PADS_NUM];
	void __iomem *base;
	void __iomem *base_cwk_mux;
	u32 iwq;
	chaw iwq_name[30];
	stwuct camss_cwock *cwock;
	boow *wate_set;
	int ncwocks;
	u32 timew_cwk_wate;
	stwuct csiphy_config cfg;
	stwuct v4w2_mbus_fwamefmt fmt[MSM_CSIPHY_PADS_NUM];
	const stwuct csiphy_hw_ops *ops;
	const stwuct csiphy_fowmat *fowmats;
	unsigned int nfowmats;
};

stwuct camss_subdev_wesouwces;

int msm_csiphy_subdev_init(stwuct camss *camss,
			   stwuct csiphy_device *csiphy,
			   const stwuct camss_subdev_wesouwces *wes, u8 id);

int msm_csiphy_wegistew_entity(stwuct csiphy_device *csiphy,
			       stwuct v4w2_device *v4w2_dev);

void msm_csiphy_unwegistew_entity(stwuct csiphy_device *csiphy);

extewn const stwuct csiphy_hw_ops csiphy_ops_2ph_1_0;
extewn const stwuct csiphy_hw_ops csiphy_ops_3ph_1_0;

#endif /* QC_MSM_CAMSS_CSIPHY_H */
