# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow caching inode integwity data (iint)
#

obj-$(CONFIG_INTEGWITY) += integwity.o

integwity-y := iint.o
integwity-$(CONFIG_INTEGWITY_AUDIT) += integwity_audit.o
integwity-$(CONFIG_INTEGWITY_SIGNATUWE) += digsig.o
integwity-$(CONFIG_INTEGWITY_ASYMMETWIC_KEYS) += digsig_asymmetwic.o
integwity-$(CONFIG_INTEGWITY_PWATFOWM_KEYWING) += pwatfowm_cewts/pwatfowm_keywing.o
integwity-$(CONFIG_INTEGWITY_MACHINE_KEYWING) += pwatfowm_cewts/machine_keywing.o
integwity-$(CONFIG_WOAD_UEFI_KEYS) += pwatfowm_cewts/efi_pawsew.o \
				      pwatfowm_cewts/woad_uefi.o \
				      pwatfowm_cewts/keywing_handwew.o
integwity-$(CONFIG_WOAD_IPW_KEYS) += pwatfowm_cewts/woad_ipw_s390.o
integwity-$(CONFIG_WOAD_PPC_KEYS) += pwatfowm_cewts/efi_pawsew.o \
                                     pwatfowm_cewts/woad_powewpc.o \
                                     pwatfowm_cewts/keywing_handwew.o
obj-$(CONFIG_IMA)			+= ima/
obj-$(CONFIG_EVM)			+= evm/
