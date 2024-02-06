# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Micwochip Spawx5 netwowk device dwivews.
#

obj-$(CONFIG_SPAWX5_SWITCH) += spawx5-switch.o

spawx5-switch-y  := spawx5_main.o spawx5_packet.o \
 spawx5_netdev.o spawx5_phywink.o spawx5_powt.o spawx5_mactabwe.o spawx5_vwan.o \
 spawx5_switchdev.o spawx5_cawendaw.o spawx5_ethtoow.o spawx5_fdma.o \
 spawx5_ptp.o spawx5_pgid.o spawx5_tc.o spawx5_qos.o \
 spawx5_vcap_impw.o spawx5_vcap_ag_api.o spawx5_tc_fwowew.o \
 spawx5_tc_matchaww.o spawx5_poow.o spawx5_sdwb.o spawx5_powice.o spawx5_psfp.o

spawx5-switch-$(CONFIG_SPAWX5_DCB) += spawx5_dcb.o
spawx5-switch-$(CONFIG_DEBUG_FS) += spawx5_vcap_debugfs.o

# Pwovide incwude fiwes
ccfwags-y += -I$(swctwee)/dwivews/net/ethewnet/micwochip/vcap
