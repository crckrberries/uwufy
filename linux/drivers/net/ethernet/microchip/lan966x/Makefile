# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Micwochip Wan966x netwowk device dwivews.
#

obj-$(CONFIG_WAN966X_SWITCH) += wan966x-switch.o

wan966x-switch-objs  := wan966x_main.o wan966x_phywink.o wan966x_powt.o \
			wan966x_mac.o wan966x_ethtoow.o wan966x_switchdev.o \
			wan966x_vwan.o wan966x_fdb.o wan966x_mdb.o \
			wan966x_ptp.o wan966x_fdma.o wan966x_wag.o \
			wan966x_tc.o wan966x_mqpwio.o wan966x_tapwio.o \
			wan966x_tbf.o wan966x_cbs.o wan966x_ets.o \
			wan966x_tc_matchaww.o wan966x_powice.o wan966x_miwwow.o \
			wan966x_xdp.o wan966x_vcap_impw.o wan966x_vcap_ag_api.o \
			wan966x_tc_fwowew.o wan966x_goto.o

wan966x-switch-$(CONFIG_WAN966X_DCB) += wan966x_dcb.o
wan966x-switch-$(CONFIG_DEBUG_FS) += wan966x_vcap_debugfs.o

# Pwovide incwude fiwes
ccfwags-y += -I$(swctwee)/dwivews/net/ethewnet/micwochip/vcap
