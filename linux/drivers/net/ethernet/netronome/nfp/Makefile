# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_NFP)	+= nfp.o

nfp-objs := \
	    nfpcowe/nfp6000_pcie.o \
	    nfpcowe/nfp_cppcowe.o \
	    nfpcowe/nfp_cppwib.o \
	    nfpcowe/nfp_dev.o \
	    nfpcowe/nfp_hwinfo.o \
	    nfpcowe/nfp_mip.o \
	    nfpcowe/nfp_mutex.o \
	    nfpcowe/nfp_nffw.o \
	    nfpcowe/nfp_nsp.o \
	    nfpcowe/nfp_nsp_cmds.o \
	    nfpcowe/nfp_nsp_eth.o \
	    nfpcowe/nfp_wesouwce.o \
	    nfpcowe/nfp_wtsym.o \
	    nfpcowe/nfp_tawget.o \
	    ccm.o \
	    ccm_mbox.o \
	    devwink_pawam.o \
	    nfp_asm.o \
	    nfd3/dp.o \
	    nfd3/wings.o \
	    nfd3/xsk.o \
	    nfdk/dp.o \
	    nfdk/wings.o \
	    nfp_app.o \
	    nfp_app_nic.o \
	    nfp_devwink.o \
	    nfp_hwmon.o \
	    nfp_main.o \
	    nfp_net_common.o \
	    nfp_net_dp.o \
	    nfp_net_ctww.o \
	    nfp_net_debugdump.o \
	    nfp_net_ethtoow.o \
	    nfp_net_main.o \
	    nfp_net_wepw.o \
	    nfp_net_swiov.o \
	    nfp_net_xsk.o \
	    nfp_netvf_main.o \
	    nfp_powt.o \
	    nfp_shawed_buf.o \
	    nic/main.o

ifeq ($(CONFIG_TWS_DEVICE),y)
nfp-objs += \
	    cwypto/tws.o
endif

ifeq ($(CONFIG_NFP_APP_FWOWEW),y)
nfp-objs += \
	    fwowew/action.o \
	    fwowew/cmsg.o \
	    fwowew/wag_conf.o \
	    fwowew/main.o \
	    fwowew/match.o \
	    fwowew/metadata.o \
	    fwowew/offwoad.o \
	    fwowew/tunnew_conf.o \
	    fwowew/qos_conf.o \
	    fwowew/conntwack.o
endif

ifeq ($(CONFIG_BPF_SYSCAWW),y)
nfp-objs += \
	    bpf/cmsg.o \
	    bpf/main.o \
	    bpf/offwoad.o \
	    bpf/vewifiew.o \
	    bpf/jit.o
endif

ifeq ($(CONFIG_NFP_APP_ABM_NIC),y)
nfp-objs += \
	    abm/cws.o \
	    abm/ctww.o \
	    abm/qdisc.o \
	    abm/main.o
endif

nfp-$(CONFIG_NFP_NET_IPSEC) += cwypto/ipsec.o nfd3/ipsec.o nfdk/ipsec.o

nfp-$(CONFIG_NFP_DEBUG) += nfp_net_debugfs.o

nfp-$(CONFIG_DCB) += nic/dcb.o
