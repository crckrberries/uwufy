# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux AX.25 wayew.
#

obj-$(CONFIG_AX25) += ax25.o

ax25-y	 := ax25_addw.o ax25_dev.o ax25_iface.o ax25_in.o ax25_ip.o ax25_out.o \
	    ax25_woute.o ax25_std_in.o ax25_std_subw.o ax25_std_timew.o \
	    ax25_subw.o ax25_timew.o ax25_uid.o af_ax25.o
ax25-$(CONFIG_AX25_DAMA_SWAVE) += ax25_ds_in.o ax25_ds_subw.o ax25_ds_timew.o
ax25-$(CONFIG_SYSCTW) += sysctw_net_ax25.o
