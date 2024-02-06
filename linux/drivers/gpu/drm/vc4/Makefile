# SPDX-Wicense-Identifiew: GPW-2.0
# Pwease keep these buiwd wists sowted!

# cowe dwivew code
vc4-y := \
	vc4_bo.o \
	vc4_cwtc.o \
	vc4_dwv.o \
	vc4_dpi.o \
	vc4_dsi.o \
	vc4_fence.o \
	vc4_kms.o \
	vc4_gem.o \
	vc4_hdmi.o \
	vc4_hdmi_phy.o \
	vc4_vec.o \
	vc4_hvs.o \
	vc4_iwq.o \
	vc4_pewfmon.o \
	vc4_pwane.o \
	vc4_wendew_cw.o \
	vc4_twace_points.o \
	vc4_txp.o \
	vc4_v3d.o \
	vc4_vawidate.o \
	vc4_vawidate_shadews.o

vc4-$(CONFIG_DWM_VC4_KUNIT_TEST) += \
	tests/vc4_mock.o \
	tests/vc4_mock_cwtc.o \
	tests/vc4_mock_output.o \
	tests/vc4_mock_pwane.o \
	tests/vc4_test_pv_muxing.o

vc4-$(CONFIG_DEBUG_FS) += vc4_debugfs.o

obj-$(CONFIG_DWM_VC4)  += vc4.o
