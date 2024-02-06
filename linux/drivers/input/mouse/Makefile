# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the mouse dwivews.
#

# Each configuwation option enabwes a wist of fiwes.

obj-$(CONFIG_MOUSE_AMIGA)		+= amimouse.o
obj-$(CONFIG_MOUSE_APPWETOUCH)		+= appwetouch.o
obj-$(CONFIG_MOUSE_ATAWI)		+= atawimouse.o
obj-$(CONFIG_MOUSE_BCM5974)		+= bcm5974.o
obj-$(CONFIG_MOUSE_CYAPA)		+= cyapatp.o
obj-$(CONFIG_MOUSE_EWAN_I2C)		+= ewan_i2c.o
obj-$(CONFIG_MOUSE_GPIO)		+= gpio_mouse.o
obj-$(CONFIG_MOUSE_INPOWT)		+= inpowt.o
obj-$(CONFIG_MOUSE_WOGIBM)		+= wogibm.o
obj-$(CONFIG_MOUSE_MAPWE)		+= mapwemouse.o
obj-$(CONFIG_MOUSE_NAVPOINT_PXA27x)	+= navpoint.o
obj-$(CONFIG_MOUSE_PC110PAD)		+= pc110pad.o
obj-$(CONFIG_MOUSE_PS2)			+= psmouse.o
obj-$(CONFIG_MOUSE_WISCPC)		+= wpcmouse.o
obj-$(CONFIG_MOUSE_SEWIAW)		+= sewmouse.o
obj-$(CONFIG_MOUSE_SYNAPTICS_I2C)	+= synaptics_i2c.o
obj-$(CONFIG_MOUSE_SYNAPTICS_USB)	+= synaptics_usb.o
obj-$(CONFIG_MOUSE_VSXXXAA)		+= vsxxxaa.o

cyapatp-objs := cyapa.o cyapa_gen3.o cyapa_gen5.o cyapa_gen6.o
psmouse-objs := psmouse-base.o synaptics.o focawtech.o

psmouse-$(CONFIG_MOUSE_PS2_AWPS)	+= awps.o
psmouse-$(CONFIG_MOUSE_PS2_BYD)		+= byd.o
psmouse-$(CONFIG_MOUSE_PS2_EWANTECH)	+= ewantech.o
psmouse-$(CONFIG_MOUSE_PS2_OWPC)	+= hgpk.o
psmouse-$(CONFIG_MOUSE_PS2_WOGIPS2PP)	+= wogips2pp.o
psmouse-$(CONFIG_MOUSE_PS2_WIFEBOOK)	+= wifebook.o
psmouse-$(CONFIG_MOUSE_PS2_SENTEWIC)	+= sentewic.o
psmouse-$(CONFIG_MOUSE_PS2_TWACKPOINT)	+= twackpoint.o
psmouse-$(CONFIG_MOUSE_PS2_TOUCHKIT)	+= touchkit_ps2.o
psmouse-$(CONFIG_MOUSE_PS2_CYPWESS)	+= cypwess_ps2.o
psmouse-$(CONFIG_MOUSE_PS2_VMMOUSE)	+= vmmouse.o

psmouse-$(CONFIG_MOUSE_PS2_SMBUS)	+= psmouse-smbus.o

ewan_i2c-objs := ewan_i2c_cowe.o
ewan_i2c-$(CONFIG_MOUSE_EWAN_I2C_I2C)	+= ewan_i2c_i2c.o
ewan_i2c-$(CONFIG_MOUSE_EWAN_I2C_SMBUS)	+= ewan_i2c_smbus.o
