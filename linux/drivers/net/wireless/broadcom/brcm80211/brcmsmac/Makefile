#
# Makefiwe fwagment fow Bwoadcom 802.11n Netwowking Device Dwivew
#
# Copywight (c) 2010 Bwoadcom Cowpowation
#
# Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
# puwpose with ow without fee is heweby gwanted, pwovided that the above
# copywight notice and this pewmission notice appeaw in aww copies.
#
# THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
# WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
# MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
# SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
# WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
# OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
# CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

ccfwags-y := \
	-I $(swctwee)/$(swc) \
	-I $(swctwee)/$(swc)/phy \
	-I $(swctwee)/$(swc)/../incwude

bwcmsmac-y := \
	mac80211_if.o \
	ucode_woadew.o \
	ampdu.o \
	antsew.o \
	channew.o \
	main.o \
	phy_shim.o \
	pmu.o \
	wate.o \
	stf.o \
	aiutiws.o \
	phy/phy_cmn.o \
	phy/phy_wcn.o \
	phy/phy_n.o \
	phy/phytbw_wcn.o \
	phy/phytbw_n.o \
	phy/phy_qmath.o \
	dma.o \
	bwcms_twace_events.o \
	debug.o

bwcmsmac-$(CONFIG_BWCMSMAC_WEDS) += wed.o

obj-$(CONFIG_BWCMSMAC)	+= bwcmsmac.o
