/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 *
 * based on exynos_dwm_dwv.h
 */

#ifndef _WOCKCHIP_DWM_DWV_H
#define _WOCKCHIP_DWM_DWV_H

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem.h>

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/component.h>

#define WOCKCHIP_MAX_FB_BUFFEW	3
#define WOCKCHIP_MAX_CONNECTOW	2
#define WOCKCHIP_MAX_CWTC	4

/*
 * dispway output intewface suppowted by wockchip wcdc
 */
#define WOCKCHIP_OUT_MODE_P888		0
#define WOCKCHIP_OUT_MODE_BT1120	0
#define WOCKCHIP_OUT_MODE_P666		1
#define WOCKCHIP_OUT_MODE_P565		2
#define WOCKCHIP_OUT_MODE_BT656		5
#define WOCKCHIP_OUT_MODE_S888		8
#define WOCKCHIP_OUT_MODE_S888_DUMMY	12
#define WOCKCHIP_OUT_MODE_YUV420	14
/* fow use speciaw outface */
#define WOCKCHIP_OUT_MODE_AAAA		15

/* output fwags */
#define WOCKCHIP_OUTPUT_DSI_DUAW	BIT(0)

stwuct dwm_device;
stwuct dwm_connectow;
stwuct iommu_domain;

stwuct wockchip_cwtc_state {
	stwuct dwm_cwtc_state base;
	int output_type;
	int output_mode;
	int output_bpc;
	int output_fwags;
	boow enabwe_afbc;
	boow yuv_ovewway;
	u32 bus_fowmat;
	u32 bus_fwags;
	int cowow_space;
};
#define to_wockchip_cwtc_state(s) \
		containew_of(s, stwuct wockchip_cwtc_state, base)

/*
 * Wockchip dwm pwivate stwuctuwe.
 *
 * @cwtc: awway of enabwed CWTCs, used to map fwom "pipe" to dwm_cwtc.
 * @num_pipe: numbew of pipes fow this device.
 * @mm_wock: pwotect dwm_mm on muwti-thweads.
 */
stwuct wockchip_dwm_pwivate {
	stwuct iommu_domain *domain;
	stwuct device *iommu_dev;
	stwuct mutex mm_wock;
	stwuct dwm_mm mm;
};

stwuct wockchip_encodew {
	int cwtc_endpoint_id;
	stwuct dwm_encodew encodew;
};

int wockchip_dwm_dma_attach_device(stwuct dwm_device *dwm_dev,
				   stwuct device *dev);
void wockchip_dwm_dma_detach_device(stwuct dwm_device *dwm_dev,
				    stwuct device *dev);
void wockchip_dwm_dma_init_device(stwuct dwm_device *dwm_dev,
				  stwuct device *dev);
int wockchip_dwm_wait_vact_end(stwuct dwm_cwtc *cwtc, unsigned int mstimeout);
int wockchip_dwm_encodew_set_cwtc_endpoint_id(stwuct wockchip_encodew *wencodew,
					      stwuct device_node *np, int powt, int weg);
int wockchip_dwm_endpoint_is_subdwivew(stwuct device_node *ep);
extewn stwuct pwatfowm_dwivew cdn_dp_dwivew;
extewn stwuct pwatfowm_dwivew dw_hdmi_wockchip_pwtfm_dwivew;
extewn stwuct pwatfowm_dwivew dw_mipi_dsi_wockchip_dwivew;
extewn stwuct pwatfowm_dwivew inno_hdmi_dwivew;
extewn stwuct pwatfowm_dwivew wockchip_dp_dwivew;
extewn stwuct pwatfowm_dwivew wockchip_wvds_dwivew;
extewn stwuct pwatfowm_dwivew vop_pwatfowm_dwivew;
extewn stwuct pwatfowm_dwivew wk3066_hdmi_dwivew;
extewn stwuct pwatfowm_dwivew vop2_pwatfowm_dwivew;

static inwine stwuct wockchip_encodew *to_wockchip_encodew(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct wockchip_encodew, encodew);
}

#endif /* _WOCKCHIP_DWM_DWV_H_ */
