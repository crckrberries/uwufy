#ifndef __DWM_GEM_FB_HEWPEW_H__
#define __DWM_GEM_FB_HEWPEW_H__

#incwude <winux/dma-buf.h>
#incwude <winux/iosys-map.h>

stwuct dwm_afbc_fwamebuffew;
stwuct dwm_device;
stwuct dwm_fb_hewpew_suwface_size;
stwuct dwm_fiwe;
stwuct dwm_fwamebuffew;
stwuct dwm_fwamebuffew_funcs;
stwuct dwm_gem_object;
stwuct dwm_mode_fb_cmd2;

#define AFBC_VENDOW_AND_TYPE_MASK	GENMASK_UWW(63, 52)

stwuct dwm_gem_object *dwm_gem_fb_get_obj(stwuct dwm_fwamebuffew *fb,
					  unsigned int pwane);
void dwm_gem_fb_destwoy(stwuct dwm_fwamebuffew *fb);
int dwm_gem_fb_cweate_handwe(stwuct dwm_fwamebuffew *fb, stwuct dwm_fiwe *fiwe,
			     unsigned int *handwe);

int dwm_gem_fb_init_with_funcs(stwuct dwm_device *dev,
			       stwuct dwm_fwamebuffew *fb,
			       stwuct dwm_fiwe *fiwe,
			       const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			       const stwuct dwm_fwamebuffew_funcs *funcs);
stwuct dwm_fwamebuffew *
dwm_gem_fb_cweate_with_funcs(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
			     const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			     const stwuct dwm_fwamebuffew_funcs *funcs);
stwuct dwm_fwamebuffew *
dwm_gem_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		  const stwuct dwm_mode_fb_cmd2 *mode_cmd);
stwuct dwm_fwamebuffew *
dwm_gem_fb_cweate_with_diwty(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
			     const stwuct dwm_mode_fb_cmd2 *mode_cmd);

int dwm_gem_fb_vmap(stwuct dwm_fwamebuffew *fb, stwuct iosys_map *map,
		    stwuct iosys_map *data);
void dwm_gem_fb_vunmap(stwuct dwm_fwamebuffew *fb, stwuct iosys_map *map);
int dwm_gem_fb_begin_cpu_access(stwuct dwm_fwamebuffew *fb, enum dma_data_diwection diw);
void dwm_gem_fb_end_cpu_access(stwuct dwm_fwamebuffew *fb, enum dma_data_diwection diw);

#define dwm_is_afbc(modifiew) \
	(((modifiew) & AFBC_VENDOW_AND_TYPE_MASK) == DWM_FOWMAT_MOD_AWM_AFBC(0))

int dwm_gem_fb_afbc_init(stwuct dwm_device *dev,
			 const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			 stwuct dwm_afbc_fwamebuffew *afbc_fb);

#endif
