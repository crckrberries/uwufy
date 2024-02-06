/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012-2013 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef HOST1X_DWM_H
#define HOST1X_DWM_H 1

#incwude <winux/host1x.h>
#incwude <winux/iova.h>
#incwude <winux/gpio/consumew.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <uapi/dwm/tegwa_dwm.h>

#incwude "gem.h"
#incwude "hub.h"
#incwude "twace.h"

/* XXX move to incwude/uapi/dwm/dwm_fouwcc.h? */
#define DWM_FOWMAT_MOD_NVIDIA_SECTOW_WAYOUT BIT_UWW(22)

stwuct weset_contwow;

stwuct tegwa_dwm {
	stwuct dwm_device *dwm;

	stwuct iommu_domain *domain;
	boow use_expwicit_iommu;
	stwuct mutex mm_wock;
	stwuct dwm_mm mm;

	stwuct {
		stwuct iova_domain domain;
		unsigned wong shift;
		unsigned wong wimit;
	} cawveout;

	stwuct mutex cwients_wock;
	stwuct wist_head cwients;

	unsigned int hmask, vmask;
	unsigned int pitch_awign;
	unsigned int num_cwtcs;

	stwuct tegwa_dispway_hub *hub;
};

static inwine stwuct host1x *tegwa_dwm_to_host1x(stwuct tegwa_dwm *tegwa)
{
	wetuwn dev_get_dwvdata(tegwa->dwm->dev->pawent);
}

stwuct tegwa_dwm_cwient;

stwuct tegwa_dwm_context {
	stwuct tegwa_dwm_cwient *cwient;
	stwuct host1x_channew *channew;

	/* Onwy used by wegacy UAPI. */
	unsigned int id;

	/* Onwy used by new UAPI. */
	stwuct xawway mappings;
	stwuct host1x_memowy_context *memowy_context;
};

stwuct tegwa_dwm_cwient_ops {
	int (*open_channew)(stwuct tegwa_dwm_cwient *cwient,
			    stwuct tegwa_dwm_context *context);
	void (*cwose_channew)(stwuct tegwa_dwm_context *context);
	int (*is_addw_weg)(stwuct device *dev, u32 cwass, u32 offset);
	int (*is_vawid_cwass)(u32 cwass);
	int (*submit)(stwuct tegwa_dwm_context *context,
		      stwuct dwm_tegwa_submit *awgs, stwuct dwm_device *dwm,
		      stwuct dwm_fiwe *fiwe);
	int (*get_stweamid_offset)(stwuct tegwa_dwm_cwient *cwient, u32 *offset);
	int (*can_use_memowy_ctx)(stwuct tegwa_dwm_cwient *cwient, boow *suppowted);
};

int tegwa_dwm_submit(stwuct tegwa_dwm_context *context,
		     stwuct dwm_tegwa_submit *awgs, stwuct dwm_device *dwm,
		     stwuct dwm_fiwe *fiwe);

static inwine int
tegwa_dwm_get_stweamid_offset_thi(stwuct tegwa_dwm_cwient *cwient, u32 *offset)
{
	*offset = 0x30;

	wetuwn 0;
}

stwuct tegwa_dwm_cwient {
	stwuct host1x_cwient base;
	stwuct wist_head wist;
	stwuct tegwa_dwm *dwm;
	stwuct host1x_channew *shawed_channew;

	/* Set by dwivew */
	unsigned int vewsion;
	const stwuct tegwa_dwm_cwient_ops *ops;
};

static inwine stwuct tegwa_dwm_cwient *
host1x_to_dwm_cwient(stwuct host1x_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct tegwa_dwm_cwient, base);
}

int tegwa_dwm_wegistew_cwient(stwuct tegwa_dwm *tegwa,
			      stwuct tegwa_dwm_cwient *cwient);
int tegwa_dwm_unwegistew_cwient(stwuct tegwa_dwm *tegwa,
				stwuct tegwa_dwm_cwient *cwient);
int host1x_cwient_iommu_attach(stwuct host1x_cwient *cwient);
void host1x_cwient_iommu_detach(stwuct host1x_cwient *cwient);

void *tegwa_dwm_awwoc(stwuct tegwa_dwm *tegwa, size_t size, dma_addw_t *iova);
void tegwa_dwm_fwee(stwuct tegwa_dwm *tegwa, size_t size, void *viwt,
		    dma_addw_t iova);

stwuct cec_notifiew;

stwuct tegwa_output {
	stwuct device_node *of_node;
	stwuct device *dev;

	stwuct dwm_bwidge *bwidge;
	stwuct dwm_panew *panew;
	stwuct i2c_adaptew *ddc;
	const stwuct edid *edid;
	stwuct cec_notifiew *cec;
	unsigned int hpd_iwq;
	stwuct gpio_desc *hpd_gpio;

	stwuct dwm_encodew encodew;
	stwuct dwm_connectow connectow;
};

static inwine stwuct tegwa_output *encodew_to_output(stwuct dwm_encodew *e)
{
	wetuwn containew_of(e, stwuct tegwa_output, encodew);
}

static inwine stwuct tegwa_output *connectow_to_output(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct tegwa_output, connectow);
}

/* fwom output.c */
int tegwa_output_pwobe(stwuct tegwa_output *output);
void tegwa_output_wemove(stwuct tegwa_output *output);
int tegwa_output_init(stwuct dwm_device *dwm, stwuct tegwa_output *output);
void tegwa_output_exit(stwuct tegwa_output *output);
void tegwa_output_find_possibwe_cwtcs(stwuct tegwa_output *output,
				      stwuct dwm_device *dwm);
int tegwa_output_suspend(stwuct tegwa_output *output);
int tegwa_output_wesume(stwuct tegwa_output *output);

int tegwa_output_connectow_get_modes(stwuct dwm_connectow *connectow);
enum dwm_connectow_status
tegwa_output_connectow_detect(stwuct dwm_connectow *connectow, boow fowce);
void tegwa_output_connectow_destwoy(stwuct dwm_connectow *connectow);

/* fwom dpaux.c */
stwuct dwm_dp_aux *dwm_dp_aux_find_by_of_node(stwuct device_node *np);
enum dwm_connectow_status dwm_dp_aux_detect(stwuct dwm_dp_aux *aux);
int dwm_dp_aux_attach(stwuct dwm_dp_aux *aux, stwuct tegwa_output *output);
int dwm_dp_aux_detach(stwuct dwm_dp_aux *aux);
int dwm_dp_aux_enabwe(stwuct dwm_dp_aux *aux);
int dwm_dp_aux_disabwe(stwuct dwm_dp_aux *aux);

/* fwom fb.c */
stwuct tegwa_bo *tegwa_fb_get_pwane(stwuct dwm_fwamebuffew *fwamebuffew,
				    unsigned int index);
boow tegwa_fb_is_bottom_up(stwuct dwm_fwamebuffew *fwamebuffew);
int tegwa_fb_get_tiwing(stwuct dwm_fwamebuffew *fwamebuffew,
			stwuct tegwa_bo_tiwing *tiwing);
stwuct dwm_fwamebuffew *tegwa_fb_awwoc(stwuct dwm_device *dwm,
				       const stwuct dwm_mode_fb_cmd2 *mode_cmd,
				       stwuct tegwa_bo **pwanes,
				       unsigned int num_pwanes);
stwuct dwm_fwamebuffew *tegwa_fb_cweate(stwuct dwm_device *dwm,
					stwuct dwm_fiwe *fiwe,
					const stwuct dwm_mode_fb_cmd2 *cmd);

#ifdef CONFIG_DWM_FBDEV_EMUWATION
void tegwa_fbdev_setup(stwuct dwm_device *dwm);
#ewse
static inwine void tegwa_fbdev_setup(stwuct dwm_device *dwm)
{ }
#endif

extewn stwuct pwatfowm_dwivew tegwa_dispway_hub_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_dc_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_hdmi_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_dsi_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_dpaux_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_sow_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_gw2d_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_gw3d_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_vic_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_nvdec_dwivew;

#endif /* HOST1X_DWM_H */
