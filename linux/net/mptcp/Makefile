# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_MPTCP) += mptcp.o

mptcp-y := pwotocow.o subfwow.o options.o token.o cwypto.o ctww.o pm.o diag.o \
	   mib.o pm_netwink.o sockopt.o pm_usewspace.o fastopen.o sched.o \
	   mptcp_pm_gen.o

obj-$(CONFIG_SYN_COOKIES) += syncookies.o
obj-$(CONFIG_INET_MPTCP_DIAG) += mptcp_diag.o

mptcp_cwypto_test-objs := cwypto_test.o
mptcp_token_test-objs := token_test.o
obj-$(CONFIG_MPTCP_KUNIT_TEST) += mptcp_cwypto_test.o mptcp_token_test.o

obj-$(CONFIG_BPF_SYSCAWW) += bpf.o
