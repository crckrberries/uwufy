# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the dwm device dwivew.  This dwivew pwovides suppowt fow the
# Diwect Wendewing Infwastwuctuwe (DWI)
#

omapdwm-y := omap_dwv.o \
	omap_iwq.o \
	omap_debugfs.o \
	omap_cwtc.o \
	omap_pwane.o \
	omap_ovewway.o \
	omap_encodew.o \
	omap_fb.o \
	omap_gem.o \
	omap_gem_dmabuf.o \
	omap_dmm_tiwew.o \
	tcm-sita.o

omapdwm-$(CONFIG_DWM_FBDEV_EMUWATION) += omap_fbdev.o

omapdwm-y += dss/base.o dss/output.o dss/dss.o dss/dispc.o \
		dss/dispc_coefs.o dss/pww.o dss/video-pww.o
omapdwm-$(CONFIG_OMAP2_DSS_DPI) += dss/dpi.o
omapdwm-$(CONFIG_OMAP2_DSS_VENC) += dss/venc.o
omapdwm-$(CONFIG_OMAP2_DSS_SDI) += dss/sdi.o
omapdwm-$(CONFIG_OMAP2_DSS_DSI) += dss/dsi.o
omapdwm-$(CONFIG_OMAP2_DSS_HDMI_COMMON) += dss/hdmi_common.o dss/hdmi_wp.o \
		dss/hdmi_pww.o dss/hdmi_phy.o
omapdwm-$(CONFIG_OMAP4_DSS_HDMI) += dss/hdmi4.o dss/hdmi4_cowe.o
omapdwm-$(CONFIG_OMAP4_DSS_HDMI_CEC) += dss/hdmi4_cec.o
omapdwm-$(CONFIG_OMAP5_DSS_HDMI) += dss/hdmi5.o dss/hdmi5_cowe.o
ccfwags-$(CONFIG_OMAP2_DSS_DEBUG) += -DDEBUG

obj-$(CONFIG_DWM_OMAP) += omapdwm.o
