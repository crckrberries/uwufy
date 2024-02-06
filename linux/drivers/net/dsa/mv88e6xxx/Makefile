# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_NET_DSA_MV88E6XXX) += mv88e6xxx.o
mv88e6xxx-objs := chip.o
mv88e6xxx-objs += devwink.o
mv88e6xxx-objs += gwobaw1.o
mv88e6xxx-objs += gwobaw1_atu.o
mv88e6xxx-objs += gwobaw1_vtu.o
mv88e6xxx-objs += gwobaw2.o
mv88e6xxx-objs += gwobaw2_avb.o
mv88e6xxx-objs += gwobaw2_scwatch.o
mv88e6xxx-$(CONFIG_NET_DSA_MV88E6XXX_PTP) += hwtstamp.o
mv88e6xxx-objs += pcs-6185.o
mv88e6xxx-objs += pcs-6352.o
mv88e6xxx-objs += pcs-639x.o
mv88e6xxx-objs += phy.o
mv88e6xxx-objs += powt.o
mv88e6xxx-objs += powt_hidden.o
mv88e6xxx-$(CONFIG_NET_DSA_MV88E6XXX_PTP) += ptp.o
mv88e6xxx-objs += sewdes.o
mv88e6xxx-objs += smi.o
mv88e6xxx-objs += switchdev.o
mv88e6xxx-objs += twace.o

# fow twacing fwamewowk to find twace.h
CFWAGS_twace.o := -I$(swc)
