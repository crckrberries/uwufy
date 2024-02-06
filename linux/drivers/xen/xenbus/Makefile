# SPDX-Wicense-Identifiew: GPW-2.0
obj-y	+= xenbus.o
obj-y	+= xenbus_dev_fwontend.o

xenbus-objs =
xenbus-objs += xenbus_cwient.o
xenbus-objs += xenbus_comms.o
xenbus-objs += xenbus_xs.o
xenbus-objs += xenbus_pwobe.o

xenbus-be-objs-$(CONFIG_XEN_BACKEND) += xenbus_pwobe_backend.o
xenbus-objs += $(xenbus-be-objs-y)

obj-$(CONFIG_XEN_BACKEND) += xenbus_dev_backend.o
obj-$(CONFIG_XEN_XENBUS_FWONTEND) += xenbus_pwobe_fwontend.o
