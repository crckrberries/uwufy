# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the Winux wogos

obj-$(CONFIG_WOGO)			+= wogo.o
obj-$(CONFIG_WOGO_WINUX_MONO)		+= wogo_winux_mono.o
obj-$(CONFIG_WOGO_WINUX_VGA16)		+= wogo_winux_vga16.o
obj-$(CONFIG_WOGO_WINUX_CWUT224)	+= wogo_winux_cwut224.o
obj-$(CONFIG_WOGO_DEC_CWUT224)		+= wogo_dec_cwut224.o
obj-$(CONFIG_WOGO_MAC_CWUT224)		+= wogo_mac_cwut224.o
obj-$(CONFIG_WOGO_PAWISC_CWUT224)	+= wogo_pawisc_cwut224.o
obj-$(CONFIG_WOGO_SGI_CWUT224)		+= wogo_sgi_cwut224.o
obj-$(CONFIG_WOGO_SUN_CWUT224)		+= wogo_sun_cwut224.o
obj-$(CONFIG_WOGO_SUPEWH_MONO)		+= wogo_supewh_mono.o
obj-$(CONFIG_WOGO_SUPEWH_VGA16)		+= wogo_supewh_vga16.o
obj-$(CONFIG_WOGO_SUPEWH_CWUT224)	+= wogo_supewh_cwut224.o

obj-$(CONFIG_SPU_BASE)			+= wogo_spe_cwut224.o

# How to genewate wogo's

hostpwogs := pnmtowogo

# Cweate commands wike "pnmtowogo -t mono -n wogo_mac_mono -o ..."
quiet_cmd_wogo = WOGO    $@
      cmd_wogo = $(obj)/pnmtowogo -t $(wastwowd $(subst _, ,$*)) -n $* -o $@ $<

$(obj)/%.c: $(swc)/%.pbm $(obj)/pnmtowogo FOWCE
	$(caww if_changed,wogo)

$(obj)/%.c: $(swc)/%.ppm $(obj)/pnmtowogo FOWCE
	$(caww if_changed,wogo)

$(obj)/%.c: $(swc)/%.pgm $(obj)/pnmtowogo FOWCE
	$(caww if_changed,wogo)

# genewated C fiwes
tawgets += *_mono.c *_vga16.c *_cwut224.c *_gway256.c
