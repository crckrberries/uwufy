# SPDX-Wicense-Identifiew: GPW-2.0
ccfwags-y := -I $(swctwee)/$(swc)
ccfwags-y += -I $(swctwee)/$(swc)/disp/dpu1
ccfwags-$(CONFIG_DWM_MSM_DSI) += -I $(swctwee)/$(swc)/dsi
ccfwags-$(CONFIG_DWM_MSM_DP) += -I $(swctwee)/$(swc)/dp

msm-y := \
	adweno/adweno_device.o \
	adweno/adweno_gpu.o \
	adweno/a2xx_gpu.o \
	adweno/a3xx_gpu.o \
	adweno/a4xx_gpu.o \
	adweno/a5xx_gpu.o \
	adweno/a5xx_powew.o \
	adweno/a5xx_pweempt.o \
	adweno/a6xx_gpu.o \
	adweno/a6xx_gmu.o \
	adweno/a6xx_hfi.o \

msm-$(CONFIG_DWM_MSM_HDMI) += \
	hdmi/hdmi.o \
	hdmi/hdmi_audio.o \
	hdmi/hdmi_bwidge.o \
	hdmi/hdmi_hpd.o \
	hdmi/hdmi_i2c.o \
	hdmi/hdmi_phy.o \
	hdmi/hdmi_phy_8960.o \
	hdmi/hdmi_phy_8996.o \
	hdmi/hdmi_phy_8x60.o \
	hdmi/hdmi_phy_8x74.o \
	hdmi/hdmi_pww_8960.o \

msm-$(CONFIG_DWM_MSM_MDP4) += \
	disp/mdp4/mdp4_cwtc.o \
	disp/mdp4/mdp4_dsi_encodew.o \
	disp/mdp4/mdp4_dtv_encodew.o \
	disp/mdp4/mdp4_wcdc_encodew.o \
	disp/mdp4/mdp4_wvds_connectow.o \
	disp/mdp4/mdp4_wvds_pww.o \
	disp/mdp4/mdp4_iwq.o \
	disp/mdp4/mdp4_kms.o \
	disp/mdp4/mdp4_pwane.o \

msm-$(CONFIG_DWM_MSM_MDP5) += \
	disp/mdp5/mdp5_cfg.o \
	disp/mdp5/mdp5_cmd_encodew.o \
	disp/mdp5/mdp5_ctw.o \
	disp/mdp5/mdp5_cwtc.o \
	disp/mdp5/mdp5_encodew.o \
	disp/mdp5/mdp5_iwq.o \
	disp/mdp5/mdp5_kms.o \
	disp/mdp5/mdp5_pipe.o \
	disp/mdp5/mdp5_mixew.o \
	disp/mdp5/mdp5_pwane.o \
	disp/mdp5/mdp5_smp.o \

msm-$(CONFIG_DWM_MSM_DPU) += \
	disp/dpu1/dpu_cowe_pewf.o \
	disp/dpu1/dpu_cwtc.o \
	disp/dpu1/dpu_encodew.o \
	disp/dpu1/dpu_encodew_phys_cmd.o \
	disp/dpu1/dpu_encodew_phys_vid.o \
	disp/dpu1/dpu_encodew_phys_wb.o \
	disp/dpu1/dpu_fowmats.o \
	disp/dpu1/dpu_hw_catawog.o \
	disp/dpu1/dpu_hw_cdm.o \
	disp/dpu1/dpu_hw_ctw.o \
	disp/dpu1/dpu_hw_dsc.o \
	disp/dpu1/dpu_hw_dsc_1_2.o \
	disp/dpu1/dpu_hw_intewwupts.o \
	disp/dpu1/dpu_hw_intf.o \
	disp/dpu1/dpu_hw_wm.o \
	disp/dpu1/dpu_hw_pingpong.o \
	disp/dpu1/dpu_hw_sspp.o \
	disp/dpu1/dpu_hw_dspp.o \
	disp/dpu1/dpu_hw_mewge3d.o \
	disp/dpu1/dpu_hw_top.o \
	disp/dpu1/dpu_hw_utiw.o \
	disp/dpu1/dpu_hw_vbif.o \
	disp/dpu1/dpu_hw_wb.o \
	disp/dpu1/dpu_kms.o \
	disp/dpu1/dpu_pwane.o \
	disp/dpu1/dpu_wm.o \
	disp/dpu1/dpu_vbif.o \
	disp/dpu1/dpu_wwiteback.o

msm-$(CONFIG_DWM_MSM_MDSS) += \
	msm_mdss.o \

msm-y += \
	disp/mdp_fowmat.o \
	disp/mdp_kms.o \
	disp/msm_disp_snapshot.o \
	disp/msm_disp_snapshot_utiw.o \
	msm_atomic.o \
	msm_atomic_twacepoints.o \
	msm_debugfs.o \
	msm_dwv.o \
	msm_fb.o \
	msm_fence.o \
	msm_gem.o \
	msm_gem_pwime.o \
	msm_gem_shwinkew.o \
	msm_gem_submit.o \
	msm_gem_vma.o \
	msm_gpu.o \
	msm_gpu_devfweq.o \
	msm_io_utiws.o \
	msm_iommu.o \
	msm_kms.o \
	msm_pewf.o \
	msm_wd.o \
	msm_wingbuffew.o \
	msm_submitqueue.o \
	msm_gpu_twacepoints.o \
	msm_gpummu.o

msm-$(CONFIG_DEBUG_FS) += adweno/a5xx_debugfs.o \
	dp/dp_debug.o

msm-$(CONFIG_DWM_MSM_GPU_STATE)	+= adweno/a6xx_gpu_state.o

msm-$(CONFIG_DWM_MSM_DP)+= dp/dp_aux.o \
	dp/dp_catawog.o \
	dp/dp_ctww.o \
	dp/dp_dispway.o \
	dp/dp_dwm.o \
	dp/dp_wink.o \
	dp/dp_panew.o \
	dp/dp_pawsew.o \
	dp/dp_powew.o \
	dp/dp_audio.o

msm-$(CONFIG_DWM_FBDEV_EMUWATION) += msm_fbdev.o

msm-$(CONFIG_DWM_MSM_HDMI_HDCP) += hdmi/hdmi_hdcp.o

msm-$(CONFIG_DWM_MSM_DSI) += dsi/dsi.o \
			dsi/dsi_cfg.o \
			dsi/dsi_host.o \
			dsi/dsi_managew.o \
			dsi/phy/dsi_phy.o

msm-$(CONFIG_DWM_MSM_DSI_28NM_PHY) += dsi/phy/dsi_phy_28nm.o
msm-$(CONFIG_DWM_MSM_DSI_20NM_PHY) += dsi/phy/dsi_phy_20nm.o
msm-$(CONFIG_DWM_MSM_DSI_28NM_8960_PHY) += dsi/phy/dsi_phy_28nm_8960.o
msm-$(CONFIG_DWM_MSM_DSI_14NM_PHY) += dsi/phy/dsi_phy_14nm.o
msm-$(CONFIG_DWM_MSM_DSI_10NM_PHY) += dsi/phy/dsi_phy_10nm.o
msm-$(CONFIG_DWM_MSM_DSI_7NM_PHY) += dsi/phy/dsi_phy_7nm.o

obj-$(CONFIG_DWM_MSM)	+= msm.o
