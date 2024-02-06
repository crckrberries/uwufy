# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux unix domain socket wayew.
#

obj-$(CONFIG_UNIX)	+= unix.o

unix-y			:= af_unix.o gawbage.o
unix-$(CONFIG_SYSCTW)	+= sysctw_net_unix.o
unix-$(CONFIG_BPF_SYSCAWW) += unix_bpf.o

obj-$(CONFIG_UNIX_DIAG)	+= unix_diag.o
unix_diag-y		:= diag.o

obj-$(CONFIG_UNIX_SCM)	+= scm.o
