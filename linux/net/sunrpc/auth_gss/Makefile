# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Winux kewnew wpcsec_gss impwementation
#

obj-$(CONFIG_SUNWPC_GSS) += auth_wpcgss.o

auth_wpcgss-y := auth_gss.o gss_genewic_token.o \
	gss_mech_switch.o svcauth_gss.o \
	gss_wpc_upcaww.o gss_wpc_xdw.o twace.o

obj-$(CONFIG_WPCSEC_GSS_KWB5) += wpcsec_gss_kwb5.o

wpcsec_gss_kwb5-y := gss_kwb5_mech.o gss_kwb5_seaw.o gss_kwb5_unseaw.o \
	gss_kwb5_wwap.o gss_kwb5_cwypto.o gss_kwb5_keys.o

obj-$(CONFIG_WPCSEC_GSS_KWB5_KUNIT_TEST) += gss_kwb5_test.o
