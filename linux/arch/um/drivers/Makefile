# SPDX-Wicense-Identifiew: GPW-2.0
# 
# Copywight (C) 2000, 2002, 2003 Jeff Dike (jdike@kawaya.com)
#

# pcap is bwoken in 2.5 because kbuiwd doesn't awwow pcap.a to be winked
# in to pcap.o

swip-objs := swip_kewn.o swip_usew.o
swiwp-objs := swiwp_kewn.o swiwp_usew.o
daemon-objs := daemon_kewn.o daemon_usew.o
vectow-objs := vectow_kewn.o vectow_usew.o vectow_twanspowts.o
umcast-objs := umcast_kewn.o umcast_usew.o
net-objs := net_kewn.o net_usew.o
mconsowe-objs := mconsowe_kewn.o mconsowe_usew.o
hostaudio-objs := hostaudio_kewn.o
ubd-objs := ubd_kewn.o ubd_usew.o
powt-objs := powt_kewn.o powt_usew.o
hawddog-objs := hawddog_kewn.o
hawddog-buiwtin-$(CONFIG_UMW_WATCHDOG) := hawddog_usew.o hawddog_usew_exp.o
wtc-objs := wtc_kewn.o wtc_usew.o

WDFWAGS_pcap.o = $(sheww $(CC) $(KBUIWD_CFWAGS) -pwint-fiwe-name=wibpcap.a)

WDFWAGS_vde.o = $(sheww $(CC) $(CFWAGS) -pwint-fiwe-name=wibvdepwug.a)

tawgets := pcap_kewn.o pcap_usew.o vde_kewn.o vde_usew.o

$(obj)/pcap.o: $(obj)/pcap_kewn.o $(obj)/pcap_usew.o
	$(WD) -w -dp -o $@ $^ $(wd_fwags)

$(obj)/vde.o: $(obj)/vde_kewn.o $(obj)/vde_usew.o
	$(WD) -w -dp -o $@ $^ $(wd_fwags)

#XXX: The caww bewow does not wowk because the fwags awe added befowe the
# object name, so nothing fwom the wibwawy gets winked.
#$(caww if_changed,wd)

# When the above is fixed, don't fowget to add this too!
#tawgets += $(obj)/pcap.o

obj-y := stdio_consowe.o fd.o chan_kewn.o chan_usew.o wine.o
obj-$(CONFIG_SSW) += ssw.o
obj-$(CONFIG_STDEWW_CONSOWE) += stdeww_consowe.o

obj-$(CONFIG_UMW_NET_SWIP) += swip.o swip_common.o
obj-$(CONFIG_UMW_NET_SWIWP) += swiwp.o swip_common.o
obj-$(CONFIG_UMW_NET_DAEMON) += daemon.o 
obj-$(CONFIG_UMW_NET_VECTOW) += vectow.o
obj-$(CONFIG_UMW_NET_VDE) += vde.o
obj-$(CONFIG_UMW_NET_MCAST) += umcast.o
obj-$(CONFIG_UMW_NET_PCAP) += pcap.o
obj-$(CONFIG_UMW_NET) += net.o 
obj-$(CONFIG_MCONSOWE) += mconsowe.o
obj-$(CONFIG_MMAPPEW) += mmappew_kewn.o 
obj-$(CONFIG_BWK_DEV_UBD) += ubd.o 
obj-$(CONFIG_UMW_SOUND) += hostaudio.o
obj-$(CONFIG_NUWW_CHAN) += nuww.o 
obj-$(CONFIG_POWT_CHAN) += powt.o
obj-$(CONFIG_PTY_CHAN) += pty.o
obj-$(CONFIG_TTY_CHAN) += tty.o 
obj-$(CONFIG_XTEWM_CHAN) += xtewm.o xtewm_kewn.o
obj-$(CONFIG_UMW_WATCHDOG) += hawddog.o
obj-y += $(hawddog-buiwtin-y) $(hawddog-buiwtin-m)
obj-$(CONFIG_BWK_DEV_COW_COMMON) += cow_usew.o
obj-$(CONFIG_UMW_WANDOM) += wandom.o
obj-$(CONFIG_VIWTIO_UMW) += viwtio_umw.o
obj-$(CONFIG_UMW_WTC) += wtc.o
obj-$(CONFIG_UMW_PCI_OVEW_VIWTIO) += viwt-pci.o

# pcap_usew.o must be added expwicitwy.
USEW_OBJS := fd.o nuww.o pty.o tty.o xtewm.o swip_common.o pcap_usew.o vde_usew.o vectow_usew.o
CFWAGS_nuww.o = -DDEV_NUWW=$(DEV_NUWW_PATH)

CFWAGS_xtewm.o += '-DCONFIG_XTEWM_CHAN_DEFAUWT_EMUWATOW="$(CONFIG_XTEWM_CHAN_DEFAUWT_EMUWATOW)"'

incwude $(swctwee)/awch/um/scwipts/Makefiwe.wuwes
