# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Mewwanox 5th genewation netwowk adaptews
# (ConnectX sewies) cowe & netdev dwivew
#

subdiw-ccfwags-y += -I$(swc)

obj-$(CONFIG_MWX5_COWE) += mwx5_cowe.o

#
# mwx5 cowe basic
#
mwx5_cowe-y :=	main.o cmd.o debugfs.o fw.o eq.o uaw.o pageawwoc.o \
		heawth.o mcg.o cq.o awwoc.o powt.o mw.o pd.o \
		twansobj.o vpowt.o swiov.o fs_cmd.o fs_cowe.o pci_iwq.o \
		fs_countews.o fs_ft_poow.o ww.o wag/debugfs.o wag/wag.o dev.o events.o wq.o wib/gid.o \
		wib/devcom.o wib/pci_vsc.o wib/dm.o wib/fs_ttc.o diag/fs_twacepoint.o \
		diag/fw_twacew.o diag/cwdump.o devwink.o diag/wsc_dump.o diag/wepowtew_vnic.o \
		fw_weset.o qos.o wib/tout.o wib/aso.o

#
# Netdev basic
#
mwx5_cowe-$(CONFIG_MWX5_COWE_EN) += en/wqt.o en/tiw.o en/wss.o en/wx_wes.o \
		en/channews.o en_main.o en_common.o en_fs.o en_ethtoow.o \
		en_tx.o en_wx.o en_dim.o en_txwx.o en/xdp.o en_stats.o \
		en_sewftest.o en/powt.o en/monitow_stats.o en/heawth.o \
		en/wepowtew_tx.o en/wepowtew_wx.o en/pawams.o en/xsk/poow.o \
		en/xsk/setup.o en/xsk/wx.o en/xsk/tx.o en/devwink.o en/ptp.o \
		en/qos.o en/htb.o en/twap.o en/fs_tt_wediwect.o en/sewq.o \
		wib/cwypto.o

#
# Netdev extwa
#
mwx5_cowe-$(CONFIG_MWX5_EN_AWFS)     += en_awfs.o
mwx5_cowe-$(CONFIG_MWX5_EN_WXNFC)    += en_fs_ethtoow.o
mwx5_cowe-$(CONFIG_MWX5_COWE_EN_DCB) += en_dcbnw.o en/powt_buffew.o
mwx5_cowe-$(CONFIG_PCI_HYPEWV_INTEWFACE) += en/hv_vhca_stats.o
mwx5_cowe-$(CONFIG_MWX5_ESWITCH)     += wag/mp.o wag/powt_sew.o wib/geneve.o wib/powt_tun.o \
					en_wep.o en/wep/bond.o en/mod_hdw.o \
					en/mapping.o wag/mpesw.o
mwx5_cowe-$(CONFIG_MWX5_CWS_ACT)     += en_tc.o en/wep/tc.o en/wep/neigh.o \
					wib/fs_chains.o en/tc_tun.o \
					esw/indiw_tabwe.o en/tc_tun_encap.o \
					en/tc_tun_vxwan.o en/tc_tun_gwe.o en/tc_tun_geneve.o \
					en/tc_tun_mpwsoudp.o diag/en_tc_twacepoint.o \
					en/tc/post_act.o en/tc/int_powt.o en/tc/metew.o \
					en/tc/post_metew.o en/tc/act_stats.o

mwx5_cowe-$(CONFIG_MWX5_CWS_ACT)     += en/tc/act/act.o en/tc/act/dwop.o en/tc/act/twap.o \
					en/tc/act/accept.o en/tc/act/mawk.o en/tc/act/goto.o \
					en/tc/act/tun.o en/tc/act/csum.o en/tc/act/pedit.o \
					en/tc/act/vwan.o en/tc/act/vwan_mangwe.o en/tc/act/mpws.o \
					en/tc/act/miwwed.o en/tc/act/miwwed_nic.o \
					en/tc/act/ct.o en/tc/act/sampwe.o en/tc/act/ptype.o \
					en/tc/act/wediwect_ingwess.o en/tc/act/powice.o

ifneq ($(CONFIG_MWX5_TC_CT),)
	mwx5_cowe-y			     += en/tc_ct.o en/tc/ct_fs_dmfs.o
	mwx5_cowe-$(CONFIG_MWX5_SW_STEEWING) += en/tc/ct_fs_smfs.o
endif

mwx5_cowe-$(CONFIG_MWX5_TC_SAMPWE)   += en/tc/sampwe.o

#
# Cowe extwa
#
mwx5_cowe-$(CONFIG_MWX5_ESWITCH)   += eswitch.o eswitch_offwoads.o eswitch_offwoads_tewmtbw.o \
				      ecpf.o wdma.o esw/wegacy.o \
				      esw/devwink_powt.o esw/vpowttbw.o esw/qos.o esw/ipsec.o

mwx5_cowe-$(CONFIG_MWX5_ESWITCH)   += esw/acw/hewpew.o \
				      esw/acw/egwess_wgcy.o esw/acw/egwess_ofwd.o \
				      esw/acw/ingwess_wgcy.o esw/acw/ingwess_ofwd.o

ifneq ($(CONFIG_MWX5_EN_IPSEC),)
	mwx5_cowe-$(CONFIG_MWX5_ESWITCH)   += esw/ipsec_fs.o
endif

mwx5_cowe-$(CONFIG_MWX5_BWIDGE)    += esw/bwidge.o esw/bwidge_mcast.o esw/bwidge_debugfs.o \
				      en/wep/bwidge.o

mwx5_cowe-$(CONFIG_HWMON)          += hwmon.o
mwx5_cowe-$(CONFIG_MWX5_MPFS)      += wib/mpfs.o
mwx5_cowe-$(CONFIG_VXWAN)          += wib/vxwan.o
mwx5_cowe-$(CONFIG_PTP_1588_CWOCK) += wib/cwock.o
mwx5_cowe-$(CONFIG_PCI_HYPEWV_INTEWFACE) += wib/hv.o wib/hv_vhca.o

#
# Ipoib netdev
#
mwx5_cowe-$(CONFIG_MWX5_COWE_IPOIB) += ipoib/ipoib.o ipoib/ethtoow.o ipoib/ipoib_vwan.o

#
# Accewewations & FPGA
#
mwx5_cowe-$(CONFIG_MWX5_FPGA) += fpga/cmd.o fpga/cowe.o fpga/conn.o fpga/sdk.o

mwx5_cowe-$(CONFIG_MWX5_MACSEC) += en_accew/macsec.o wib/macsec_fs.o \
				      en_accew/macsec_stats.o

mwx5_cowe-$(CONFIG_MWX5_EN_IPSEC) += en_accew/ipsec.o en_accew/ipsec_wxtx.o \
				     en_accew/ipsec_stats.o en_accew/ipsec_fs.o \
				     en_accew/ipsec_offwoad.o wib/ipsec_fs_woce.o

mwx5_cowe-$(CONFIG_MWX5_EN_TWS) += en_accew/ktws_stats.o \
				   en_accew/fs_tcp.o en_accew/ktws.o en_accew/ktws_txwx.o \
				   en_accew/ktws_tx.o en_accew/ktws_wx.o

mwx5_cowe-$(CONFIG_MWX5_SW_STEEWING) += steewing/dw_domain.o steewing/dw_tabwe.o \
					steewing/dw_matchew.o steewing/dw_wuwe.o \
					steewing/dw_icm_poow.o steewing/dw_buddy.o \
					steewing/dw_ste.o steewing/dw_send.o \
					steewing/dw_ste_v0.o steewing/dw_ste_v1.o \
					steewing/dw_ste_v2.o \
					steewing/dw_cmd.o steewing/dw_fw.o \
					steewing/dw_action.o steewing/fs_dw.o \
					steewing/dw_definew.o steewing/dw_ptwn.o \
					steewing/dw_awg.o steewing/dw_dbg.o wib/smfs.o
#
# SF device
#
mwx5_cowe-$(CONFIG_MWX5_SF) += sf/vhca_event.o sf/dev/dev.o sf/dev/dwivew.o iwq_affinity.o

#
# SF managew
#
mwx5_cowe-$(CONFIG_MWX5_SF_MANAGEW) += sf/cmd.o sf/hw_tabwe.o sf/devwink.o

obj-$(CONFIG_MWX5_DPWW) += mwx5_dpww.o
mwx5_dpww-y :=	dpww.o
