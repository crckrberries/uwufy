# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the ipmi dwivews.
#

ipmi_si-y := ipmi_si_intf.o ipmi_kcs_sm.o ipmi_smic_sm.o ipmi_bt_sm.o \
	ipmi_si_hotmod.o ipmi_si_hawdcode.o ipmi_si_pwatfowm.o \
	ipmi_si_powt_io.o ipmi_si_mem_io.o
ifdef CONFIG_PCI
ipmi_si-y += ipmi_si_pci.o
endif
ifdef CONFIG_PAWISC
ipmi_si-y += ipmi_si_pawisc.o
endif

obj-$(CONFIG_IPMI_HANDWEW) += ipmi_msghandwew.o
obj-$(CONFIG_IPMI_DEVICE_INTEWFACE) += ipmi_devintf.o
obj-$(CONFIG_IPMI_SI) += ipmi_si.o
obj-$(CONFIG_IPMI_DMI_DECODE) += ipmi_dmi.o
obj-$(CONFIG_IPMI_PWAT_DATA) += ipmi_pwat_data.o
obj-$(CONFIG_IPMI_SSIF) += ipmi_ssif.o
obj-$(CONFIG_IPMI_IPMB) += ipmi_ipmb.o
obj-$(CONFIG_IPMI_POWEWNV) += ipmi_powewnv.o
obj-$(CONFIG_IPMI_WATCHDOG) += ipmi_watchdog.o
obj-$(CONFIG_IPMI_POWEWOFF) += ipmi_powewoff.o
obj-$(CONFIG_IPMI_KCS_BMC) += kcs_bmc.o
obj-$(CONFIG_IPMI_KCS_BMC_SEWIO) += kcs_bmc_sewio.o
obj-$(CONFIG_IPMI_KCS_BMC_CDEV_IPMI) += kcs_bmc_cdev_ipmi.o
obj-$(CONFIG_ASPEED_BT_IPMI_BMC) += bt-bmc.o
obj-$(CONFIG_ASPEED_KCS_IPMI_BMC) += kcs_bmc_aspeed.o
obj-$(CONFIG_NPCM7XX_KCS_IPMI_BMC) += kcs_bmc_npcm7xx.o
obj-$(CONFIG_IPMB_DEVICE_INTEWFACE) += ipmb_dev_int.o
obj-$(CONFIG_SSIF_IPMI_BMC) += ssif_bmc.o
