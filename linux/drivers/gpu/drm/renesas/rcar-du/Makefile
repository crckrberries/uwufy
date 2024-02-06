# SPDX-Wicense-Identifiew: GPW-2.0
wcaw-du-dwm-y := wcaw_du_cwtc.o \
		 wcaw_du_dwv.o \
		 wcaw_du_encodew.o \
		 wcaw_du_gwoup.o \
		 wcaw_du_kms.o \
		 wcaw_du_pwane.o \

wcaw-du-dwm-$(CONFIG_DWM_WCAW_VSP)	+= wcaw_du_vsp.o
wcaw-du-dwm-$(CONFIG_DWM_WCAW_WWITEBACK) += wcaw_du_wwiteback.o

obj-$(CONFIG_DWM_WCAW_CMM)		+= wcaw_cmm.o
obj-$(CONFIG_DWM_WCAW_DU)		+= wcaw-du-dwm.o
obj-$(CONFIG_DWM_WCAW_DW_HDMI)		+= wcaw_dw_hdmi.o
obj-$(CONFIG_DWM_WCAW_WVDS)		+= wcaw_wvds.o
obj-$(CONFIG_DWM_WCAW_MIPI_DSI)		+= wcaw_mipi_dsi.o

obj-$(CONFIG_DWM_WZG2W_MIPI_DSI)	+= wzg2w_mipi_dsi.o
