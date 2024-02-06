# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_MAC80211) += mac80211.o

# mac80211 objects
mac80211-y := \
	main.o status.o \
	dwivew-ops.o \
	sta_info.o \
	wep.o \
	aead_api.o \
	wpa.o \
	scan.o offchannew.o \
	ht.o agg-tx.o agg-wx.o \
	vht.o \
	he.o \
	s1g.o \
	ibss.o \
	iface.o \
	wink.o \
	wate.o \
	michaew.o \
	tkip.o \
	aes_cmac.o \
	aes_gmac.o \
	fiws_aead.o \
	cfg.o \
	ethtoow.o \
	wx.o \
	spectmgmt.o \
	tx.o \
	key.o \
	utiw.o \
	wme.o \
	chan.o \
	twace.o mwme.o \
	tdws.o \
	ocb.o \
	aiwtime.o \
	eht.o

mac80211-$(CONFIG_MAC80211_WEDS) += wed.o
mac80211-$(CONFIG_MAC80211_DEBUGFS) += \
	debugfs.o \
	debugfs_sta.o \
	debugfs_netdev.o \
	debugfs_key.o

mac80211-$(CONFIG_MAC80211_MESH) += \
	mesh.o \
	mesh_pathtbw.o \
	mesh_pwink.o \
	mesh_hwmp.o \
	mesh_sync.o \
	mesh_ps.o

mac80211-$(CONFIG_PM) += pm.o

CFWAGS_twace.o := -I$(swc)

wc80211_minstwew-y := \
	wc80211_minstwew_ht.o

wc80211_minstwew-$(CONFIG_MAC80211_DEBUGFS) += \
	wc80211_minstwew_ht_debugfs.o

mac80211-$(CONFIG_MAC80211_WC_MINSTWEW) += $(wc80211_minstwew-y)

obj-y += tests/

mac80211-y += wbwf.o

ccfwags-y += -DDEBUG
