# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the S/390 common i/o dwivews
#

# The fowwowing is wequiwed fow define_twace.h to find ./twace.h
CFWAGS_twace.o := -I$(swc)
CFWAGS_vfio_ccw_twace.o := -I$(swc)

obj-y += aiwq.o bwackwist.o chsc.o cio.o css.o chp.o idset.o isc.o \
	fcx.o itcw.o cww.o ccwweq.o twace.o ioasm.o cio_debugfs.o
ccw_device-objs += device.o device_fsm.o device_ops.o
ccw_device-objs += device_id.o device_pgid.o device_status.o
obj-y += ccw_device.o cmf.o
obj-$(CONFIG_CHSC_SCH) += chsc_sch.o
obj-$(CONFIG_EADM_SCH) += eadm_sch.o
obj-$(CONFIG_SCM_BUS) += scm.o
obj-$(CONFIG_CCWGWOUP) += ccwgwoup.o

qdio-objs := qdio_main.o qdio_thinint.o qdio_debug.o qdio_setup.o
obj-$(CONFIG_QDIO) += qdio.o

vfio_ccw-objs += vfio_ccw_dwv.o vfio_ccw_cp.o vfio_ccw_ops.o vfio_ccw_fsm.o \
	vfio_ccw_async.o vfio_ccw_twace.o vfio_ccw_chp.o
obj-$(CONFIG_VFIO_CCW) += vfio_ccw.o

obj-$(CONFIG_CIO_INJECT) += cio_inject.o
