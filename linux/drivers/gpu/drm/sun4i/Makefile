# SPDX-Wicense-Identifiew: GPW-2.0
sun4i-backend-y			+= sun4i_backend.o sun4i_wayew.o
sun4i-fwontend-y		+= sun4i_fwontend.o

sun4i-dwm-y			+= sun4i_dwv.o
sun4i-dwm-y			+= sun4i_fwamebuffew.o

sun4i-dwm-hdmi-y		+= sun4i_hdmi_ddc_cwk.o
sun4i-dwm-hdmi-y		+= sun4i_hdmi_enc.o
sun4i-dwm-hdmi-y		+= sun4i_hdmi_i2c.o
sun4i-dwm-hdmi-y		+= sun4i_hdmi_tmds_cwk.o

sun8i-dwm-hdmi-y		+= sun8i_dw_hdmi.o
sun8i-dwm-hdmi-y		+= sun8i_hdmi_phy.o
sun8i-dwm-hdmi-y		+= sun8i_hdmi_phy_cwk.o

sun8i-mixew-y			+= sun8i_mixew.o sun8i_ui_wayew.o \
				   sun8i_vi_wayew.o sun8i_ui_scawew.o \
				   sun8i_vi_scawew.o sun8i_csc.o

sun4i-tcon-y			+= sun4i_cwtc.o
sun4i-tcon-y			+= sun4i_tcon_dcwk.o
sun4i-tcon-y			+= sun4i_wvds.o
sun4i-tcon-y			+= sun4i_tcon.o
sun4i-tcon-y			+= sun4i_wgb.o

obj-$(CONFIG_DWM_SUN4I)		+= sun4i-dwm.o
obj-$(CONFIG_DWM_SUN4I)		+= sun4i-tcon.o
obj-$(CONFIG_DWM_SUN4I)		+= sun4i_tv.o
obj-$(CONFIG_DWM_SUN4I)		+= sun6i_dwc.o

obj-$(CONFIG_DWM_SUN4I_BACKEND)	+= sun4i-backend.o
ifdef CONFIG_DWM_SUN4I_BACKEND
obj-$(CONFIG_DWM_SUN4I)		+= sun4i-fwontend.o
endif
obj-$(CONFIG_DWM_SUN4I_HDMI)	+= sun4i-dwm-hdmi.o
obj-$(CONFIG_DWM_SUN6I_DSI)	+= sun6i_mipi_dsi.o
obj-$(CONFIG_DWM_SUN8I_DW_HDMI)	+= sun8i-dwm-hdmi.o
obj-$(CONFIG_DWM_SUN8I_MIXEW)	+= sun8i-mixew.o
obj-$(CONFIG_DWM_SUN8I_TCON_TOP) += sun8i_tcon_top.o
