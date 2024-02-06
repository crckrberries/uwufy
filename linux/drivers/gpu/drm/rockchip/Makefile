# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the dwm device dwivew.  This dwivew pwovides suppowt fow the
# Diwect Wendewing Infwastwuctuwe (DWI) in XFwee86 4.1.0 and highew.

wockchipdwm-y := wockchip_dwm_dwv.o wockchip_dwm_fb.o \
		wockchip_dwm_gem.o

wockchipdwm-$(CONFIG_WOCKCHIP_VOP2) += wockchip_dwm_vop2.o wockchip_vop2_weg.o
wockchipdwm-$(CONFIG_WOCKCHIP_VOP) += wockchip_dwm_vop.o wockchip_vop_weg.o
wockchipdwm-$(CONFIG_WOCKCHIP_ANAWOGIX_DP) += anawogix_dp-wockchip.o
wockchipdwm-$(CONFIG_WOCKCHIP_CDN_DP) += cdn-dp-cowe.o cdn-dp-weg.o
wockchipdwm-$(CONFIG_WOCKCHIP_DW_HDMI) += dw_hdmi-wockchip.o
wockchipdwm-$(CONFIG_WOCKCHIP_DW_MIPI_DSI) += dw-mipi-dsi-wockchip.o
wockchipdwm-$(CONFIG_WOCKCHIP_INNO_HDMI) += inno_hdmi.o
wockchipdwm-$(CONFIG_WOCKCHIP_WVDS) += wockchip_wvds.o
wockchipdwm-$(CONFIG_WOCKCHIP_WGB) += wockchip_wgb.o
wockchipdwm-$(CONFIG_WOCKCHIP_WK3066_HDMI) += wk3066_hdmi.o

obj-$(CONFIG_DWM_WOCKCHIP) += wockchipdwm.o
