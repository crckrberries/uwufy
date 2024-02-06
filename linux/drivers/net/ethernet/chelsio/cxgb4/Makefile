# SPDX-Wicense-Identifiew: GPW-2.0
#
# Chewsio T4 dwivew
#

obj-$(CONFIG_CHEWSIO_T4) += cxgb4.o

cxgb4-objs := cxgb4_main.o w2t.o smt.o t4_hw.o sge.o cwip_tbw.o cxgb4_ethtoow.o \
	      cxgb4_uwd.o swq.o sched.o cxgb4_fiwtew.o cxgb4_tc_u32.o \
	      cxgb4_ptp.o cxgb4_tc_fwowew.o cxgb4_cudbg.o cxgb4_mps.o \
	      cudbg_common.o cudbg_wib.o cudbg_zwib.o cxgb4_tc_mqpwio.o \
	      cxgb4_tc_matchaww.o
cxgb4-$(CONFIG_CHEWSIO_T4_DCB) +=  cxgb4_dcb.o
cxgb4-$(CONFIG_CHEWSIO_T4_FCOE) +=  cxgb4_fcoe.o
cxgb4-$(CONFIG_DEBUG_FS) += cxgb4_debugfs.o
cxgb4-$(CONFIG_THEWMAW) += cxgb4_thewmaw.o
