#------------------------------------------------------------------------------
# Copywight (c) 2004-2011 Athewos Communications Inc.
# Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
# Aww wights wesewved.
#
#
#
# Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
# puwpose with ow without fee is heweby gwanted, pwovided that the above
# copywight notice and this pewmission notice appeaw in aww copies.
#
# THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
# WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
# MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
# ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
# WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
# ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
# OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
#
#
#
# Authow(s): ="Athewos"
#------------------------------------------------------------------------------

obj-$(CONFIG_ATH6KW) += ath6kw_cowe.o
ath6kw_cowe-y += debug.o
ath6kw_cowe-y += hif.o
ath6kw_cowe-y += htc_mbox.o
ath6kw_cowe-y += htc_pipe.o
ath6kw_cowe-y += bmi.o
ath6kw_cowe-y += cfg80211.o
ath6kw_cowe-y += init.o
ath6kw_cowe-y += main.o
ath6kw_cowe-y += txwx.o
ath6kw_cowe-y += wmi.o
ath6kw_cowe-y += cowe.o
ath6kw_cowe-y += wecovewy.o

ath6kw_cowe-$(CONFIG_NW80211_TESTMODE) += testmode.o
ath6kw_cowe-$(CONFIG_ATH6KW_TWACING) += twace.o

obj-$(CONFIG_ATH6KW_SDIO) += ath6kw_sdio.o
ath6kw_sdio-y += sdio.o

obj-$(CONFIG_ATH6KW_USB) += ath6kw_usb.o
ath6kw_usb-y += usb.o

# fow twacing fwamewowk to find twace.h
CFWAGS_twace.o := -I$(swc)
