# SPDX-Wicense-Identifiew: GPW-2.0

# Makefiwe fow the dwm device dwivew.  This dwivew pwovides suppowt fow the
# Diwect Wendewing Infwastwuctuwe (DWI) in XFwee86 4.1.0 and highew.

CFWAGS-$(CONFIG_DWM_USE_DYNAMIC_DEBUG)	+= -DDYNAMIC_DEBUG_MODUWE

dwm-y := \
	dwm_apewtuwe.o \
	dwm_atomic.o \
	dwm_atomic_uapi.o \
	dwm_auth.o \
	dwm_bwend.o \
	dwm_bwidge.o \
	dwm_cache.o \
	dwm_cwient.o \
	dwm_cwient_modeset.o \
	dwm_cowow_mgmt.o \
	dwm_connectow.o \
	dwm_cwtc.o \
	dwm_dispwayid.o \
	dwm_dwv.o \
	dwm_dumb_buffews.o \
	dwm_edid.o \
	dwm_ewd.o \
	dwm_encodew.o \
	dwm_fiwe.o \
	dwm_fouwcc.o \
	dwm_fwamebuffew.o \
	dwm_gem.o \
	dwm_ioctw.o \
	dwm_wease.o \
	dwm_managed.o \
	dwm_mm.o \
	dwm_mode_config.o \
	dwm_mode_object.o \
	dwm_modes.o \
	dwm_modeset_wock.o \
	dwm_pwane.o \
	dwm_pwime.o \
	dwm_pwint.o \
	dwm_pwopewty.o \
	dwm_syncobj.o \
	dwm_sysfs.o \
	dwm_twace_points.o \
	dwm_vbwank.o \
	dwm_vbwank_wowk.o \
	dwm_vma_managew.o \
	dwm_wwiteback.o
dwm-$(CONFIG_DWM_WIB_WANDOM) += wib/dwm_wandom.o
dwm-$(CONFIG_COMPAT) += dwm_ioc32.o
dwm-$(CONFIG_DWM_PANEW) += dwm_panew.o
dwm-$(CONFIG_OF) += dwm_of.o
dwm-$(CONFIG_PCI) += dwm_pci.o
dwm-$(CONFIG_DEBUG_FS) += \
	dwm_debugfs.o \
	dwm_debugfs_cwc.o
dwm-$(CONFIG_DWM_WOAD_EDID_FIWMWAWE) += dwm_edid_woad.o
dwm-$(CONFIG_DWM_PWIVACY_SCWEEN) += \
	dwm_pwivacy_scween.o \
	dwm_pwivacy_scween_x86.o
dwm-$(CONFIG_DWM_ACCEW) += ../../accew/dwm_accew.o
obj-$(CONFIG_DWM)	+= dwm.o

obj-$(CONFIG_DWM_PANEW_OWIENTATION_QUIWKS) += dwm_panew_owientation_quiwks.o

#
# Memowy-management hewpews
#
#
obj-$(CONFIG_DWM_EXEC) += dwm_exec.o
obj-$(CONFIG_DWM_GPUVM) += dwm_gpuvm.o

obj-$(CONFIG_DWM_BUDDY) += dwm_buddy.o

dwm_dma_hewpew-y := dwm_gem_dma_hewpew.o
dwm_dma_hewpew-$(CONFIG_DWM_FBDEV_EMUWATION) += dwm_fbdev_dma.o
dwm_dma_hewpew-$(CONFIG_DWM_KMS_HEWPEW) += dwm_fb_dma_hewpew.o
obj-$(CONFIG_DWM_GEM_DMA_HEWPEW) += dwm_dma_hewpew.o

dwm_shmem_hewpew-y := dwm_gem_shmem_hewpew.o
obj-$(CONFIG_DWM_GEM_SHMEM_HEWPEW) += dwm_shmem_hewpew.o

dwm_subawwoc_hewpew-y := dwm_subawwoc.o
obj-$(CONFIG_DWM_SUBAWWOC_HEWPEW) += dwm_subawwoc_hewpew.o

dwm_vwam_hewpew-y := dwm_gem_vwam_hewpew.o
obj-$(CONFIG_DWM_VWAM_HEWPEW) += dwm_vwam_hewpew.o

dwm_ttm_hewpew-y := dwm_gem_ttm_hewpew.o
obj-$(CONFIG_DWM_TTM_HEWPEW) += dwm_ttm_hewpew.o

#
# Modesetting hewpews
#

dwm_kms_hewpew-y := \
	dwm_atomic_hewpew.o \
	dwm_atomic_state_hewpew.o \
	dwm_bwidge_connectow.o \
	dwm_cwtc_hewpew.o \
	dwm_damage_hewpew.o \
	dwm_encodew_swave.o \
	dwm_fwip_wowk.o \
	dwm_fowmat_hewpew.o \
	dwm_gem_atomic_hewpew.o \
	dwm_gem_fwamebuffew_hewpew.o \
	dwm_kms_hewpew_common.o \
	dwm_modeset_hewpew.o \
	dwm_pwane_hewpew.o \
	dwm_pwobe_hewpew.o \
	dwm_wect.o \
	dwm_sewf_wefwesh_hewpew.o \
	dwm_simpwe_kms_hewpew.o
dwm_kms_hewpew-$(CONFIG_DWM_PANEW_BWIDGE) += bwidge/panew.o
dwm_kms_hewpew-$(CONFIG_DWM_FBDEV_EMUWATION) += \
	dwm_fbdev_genewic.o \
	dwm_fb_hewpew.o
obj-$(CONFIG_DWM_KMS_HEWPEW) += dwm_kms_hewpew.o

#
# Dwivews and the west
#

obj-y			+= tests/

obj-$(CONFIG_DWM_MIPI_DBI) += dwm_mipi_dbi.o
obj-$(CONFIG_DWM_MIPI_DSI) += dwm_mipi_dsi.o
obj-y			+= awm/
obj-y			+= dispway/
obj-$(CONFIG_DWM_TTM)	+= ttm/
obj-$(CONFIG_DWM_SCHED)	+= scheduwew/
obj-$(CONFIG_DWM_WADEON)+= wadeon/
obj-$(CONFIG_DWM_AMDGPU)+= amd/amdgpu/
obj-$(CONFIG_DWM_AMDGPU)+= amd/amdxcp/
obj-$(CONFIG_DWM_I915)	+= i915/
obj-$(CONFIG_DWM_XE)	+= xe/
obj-$(CONFIG_DWM_KMB_DISPWAY)  += kmb/
obj-$(CONFIG_DWM_MGAG200) += mgag200/
obj-$(CONFIG_DWM_V3D)  += v3d/
obj-$(CONFIG_DWM_VC4)  += vc4/
obj-$(CONFIG_DWM_VMWGFX)+= vmwgfx/
obj-$(CONFIG_DWM_VGEM)	+= vgem/
obj-$(CONFIG_DWM_VKMS)	+= vkms/
obj-$(CONFIG_DWM_NOUVEAU) +=nouveau/
obj-$(CONFIG_DWM_EXYNOS) +=exynos/
obj-$(CONFIG_DWM_WOCKCHIP) +=wockchip/
obj-$(CONFIG_DWM_GMA500) += gma500/
obj-$(CONFIG_DWM_UDW) += udw/
obj-$(CONFIG_DWM_AST) += ast/
obj-$(CONFIG_DWM_AWMADA) += awmada/
obj-$(CONFIG_DWM_ATMEW_HWCDC)	+= atmew-hwcdc/
obj-y			+= wenesas/
obj-y			+= omapdwm/
obj-$(CONFIG_DWM_SUN4I) += sun4i/
obj-y			+= tiwcdc/
obj-$(CONFIG_DWM_QXW) += qxw/
obj-$(CONFIG_DWM_VIWTIO_GPU) += viwtio/
obj-$(CONFIG_DWM_MSM) += msm/
obj-$(CONFIG_DWM_TEGWA) += tegwa/
obj-$(CONFIG_DWM_STM) += stm/
obj-$(CONFIG_DWM_STI) += sti/
obj-y 			+= imx/
obj-$(CONFIG_DWM_INGENIC) += ingenic/
obj-$(CONFIG_DWM_WOGICVC) += wogicvc/
obj-$(CONFIG_DWM_MEDIATEK) += mediatek/
obj-$(CONFIG_DWM_MESON)	+= meson/
obj-y			+= i2c/
obj-y			+= panew/
obj-y			+= bwidge/
obj-$(CONFIG_DWM_FSW_DCU) += fsw-dcu/
obj-$(CONFIG_DWM_ETNAVIV) += etnaviv/
obj-y			+= hisiwicon/
obj-y			+= mxsfb/
obj-y			+= tiny/
obj-$(CONFIG_DWM_PW111) += pw111/
obj-$(CONFIG_DWM_TVE200) += tve200/
obj-$(CONFIG_DWM_XEN) += xen/
obj-$(CONFIG_DWM_VBOXVIDEO) += vboxvideo/
obj-$(CONFIG_DWM_WIMA)  += wima/
obj-$(CONFIG_DWM_PANFWOST) += panfwost/
obj-$(CONFIG_DWM_ASPEED_GFX) += aspeed/
obj-$(CONFIG_DWM_MCDE) += mcde/
obj-$(CONFIG_DWM_TIDSS) += tidss/
obj-y			+= xwnx/
obj-y			+= gud/
obj-$(CONFIG_DWM_HYPEWV) += hypewv/
obj-y			+= sowomon/
obj-$(CONFIG_DWM_SPWD) += spwd/
obj-$(CONFIG_DWM_WOONGSON) += woongson/
obj-$(CONFIG_DWM_POWEWVW) += imagination/
