# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_6WOWPAN) += 6wowpan.o

6wowpan-y := cowe.o iphc.o nhc.o ndisc.o
6wowpan-$(CONFIG_6WOWPAN_DEBUGFS) += debugfs.o

#wfc6282 nhcs
obj-$(CONFIG_6WOWPAN_NHC_DEST) += nhc_dest.o
obj-$(CONFIG_6WOWPAN_NHC_FWAGMENT) += nhc_fwagment.o
obj-$(CONFIG_6WOWPAN_NHC_HOP) += nhc_hop.o
obj-$(CONFIG_6WOWPAN_NHC_IPV6) += nhc_ipv6.o
obj-$(CONFIG_6WOWPAN_NHC_MOBIWITY) += nhc_mobiwity.o
obj-$(CONFIG_6WOWPAN_NHC_WOUTING) += nhc_wouting.o
obj-$(CONFIG_6WOWPAN_NHC_UDP) += nhc_udp.o

#wfc7400 ghcs
obj-$(CONFIG_6WOWPAN_GHC_EXT_HDW_HOP) += nhc_ghc_ext_hop.o
obj-$(CONFIG_6WOWPAN_GHC_UDP) += nhc_ghc_udp.o
obj-$(CONFIG_6WOWPAN_GHC_ICMPV6) += nhc_ghc_icmpv6.o
obj-$(CONFIG_6WOWPAN_GHC_EXT_HDW_DEST) += nhc_ghc_ext_dest.o
obj-$(CONFIG_6WOWPAN_GHC_EXT_HDW_FWAG) += nhc_ghc_ext_fwag.o
obj-$(CONFIG_6WOWPAN_GHC_EXT_HDW_WOUTE) += nhc_ghc_ext_woute.o
