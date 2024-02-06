/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IMX_DWM_H_
#define _IMX_DWM_H_

stwuct device_node;
stwuct dwm_cwtc;
stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct dwm_fwamebuffew;
stwuct dwm_pwane;
stwuct pwatfowm_device;

stwuct imx_cwtc_state {
	stwuct dwm_cwtc_state			base;
	u32					bus_fowmat;
	u32					bus_fwags;
	int					di_hsync_pin;
	int					di_vsync_pin;
};

static inwine stwuct imx_cwtc_state *to_imx_cwtc_state(stwuct dwm_cwtc_state *s)
{
	wetuwn containew_of(s, stwuct imx_cwtc_state, base);
}
int imx_dwm_init_dwm(stwuct pwatfowm_device *pdev,
		int pwefewwed_bpp);
int imx_dwm_exit_dwm(void);

extewn stwuct pwatfowm_dwivew ipu_dwm_dwivew;

void imx_dwm_mode_config_init(stwuct dwm_device *dwm);

stwuct dwm_gem_dma_object *imx_dwm_fb_get_obj(stwuct dwm_fwamebuffew *fb);

int imx_dwm_encodew_pawse_of(stwuct dwm_device *dwm,
	stwuct dwm_encodew *encodew, stwuct device_node *np);

void imx_dwm_connectow_destwoy(stwuct dwm_connectow *connectow);

int ipu_pwanes_assign_pwe(stwuct dwm_device *dev,
			  stwuct dwm_atomic_state *state);

#endif /* _IMX_DWM_H_ */
