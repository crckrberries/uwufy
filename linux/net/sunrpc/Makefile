# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Winux kewnew SUN WPC
#


obj-$(CONFIG_SUNWPC) += sunwpc.o
obj-$(CONFIG_SUNWPC_GSS) += auth_gss/
obj-$(CONFIG_SUNWPC_XPWT_WDMA) += xpwtwdma/

sunwpc-y := cwnt.o xpwt.o sockwib.o xpwtsock.o sched.o \
	    auth.o auth_nuww.o auth_tws.o auth_unix.o \
	    svc.o svcsock.o svcauth.o svcauth_unix.o \
	    addw.o wpcb_cwnt.o timew.o xdw.o \
	    sunwpc_syms.o cache.o wpc_pipe.o sysfs.o \
	    svc_xpwt.o \
	    xpwtmuwtipath.o
sunwpc-$(CONFIG_SUNWPC_DEBUG) += debugfs.o
sunwpc-$(CONFIG_SUNWPC_BACKCHANNEW) += backchannew_wqst.o
sunwpc-$(CONFIG_PWOC_FS) += stats.o
sunwpc-$(CONFIG_SYSCTW) += sysctw.o
