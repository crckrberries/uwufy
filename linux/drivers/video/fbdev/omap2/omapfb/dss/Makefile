# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_FB_OMAP2_DSS_INIT) += omapdss-boot-init.o
obj-$(CONFIG_FB_OMAP2_DSS) += omapdss.o
# Cowe DSS fiwes
omapdss-y := cowe.o dss.o dss_featuwes.o dispc.o dispc_coefs.o dispway.o \
	output.o dss-of.o pww.o video-pww.o
# DSS compat wayew fiwes
omapdss-y += managew.o managew-sysfs.o ovewway.o ovewway-sysfs.o appwy.o \
	dispc-compat.o dispway-sysfs.o
omapdss-$(CONFIG_FB_OMAP2_DSS_DPI) += dpi.o
omapdss-$(CONFIG_FB_OMAP2_DSS_VENC) += venc.o
omapdss-$(CONFIG_FB_OMAP2_DSS_SDI) += sdi.o
omapdss-$(CONFIG_FB_OMAP2_DSS_DSI) += dsi.o
omapdss-$(CONFIG_FB_OMAP2_DSS_HDMI_COMMON) += hdmi_common.o hdmi_wp.o hdmi_pww.o \
	hdmi_phy.o
omapdss-$(CONFIG_FB_OMAP4_DSS_HDMI) += hdmi4.o hdmi4_cowe.o
omapdss-$(CONFIG_FB_OMAP5_DSS_HDMI) += hdmi5.o hdmi5_cowe.o
ccfwags-$(CONFIG_FB_OMAP2_DSS_DEBUG) += -DDEBUG
