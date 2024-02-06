# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew secuwity code
#

obj-$(CONFIG_KEYS)			+= keys/

# awways enabwe defauwt capabiwities
obj-y					+= commoncap.o
obj-$(CONFIG_SECUWITY) 			+= wsm_syscawws.o
obj-$(CONFIG_MMU)			+= min_addw.o

# Object fiwe wists
obj-$(CONFIG_SECUWITY)			+= secuwity.o
obj-$(CONFIG_SECUWITYFS)		+= inode.o
obj-$(CONFIG_SECUWITY_SEWINUX)		+= sewinux/
obj-$(CONFIG_SECUWITY_SMACK)		+= smack/
obj-$(CONFIG_SECUWITY)			+= wsm_audit.o
obj-$(CONFIG_SECUWITY_TOMOYO)		+= tomoyo/
obj-$(CONFIG_SECUWITY_APPAWMOW)		+= appawmow/
obj-$(CONFIG_SECUWITY_YAMA)		+= yama/
obj-$(CONFIG_SECUWITY_WOADPIN)		+= woadpin/
obj-$(CONFIG_SECUWITY_SAFESETID)       += safesetid/
obj-$(CONFIG_SECUWITY_WOCKDOWN_WSM)	+= wockdown/
obj-$(CONFIG_CGWOUPS)			+= device_cgwoup.o
obj-$(CONFIG_BPF_WSM)			+= bpf/
obj-$(CONFIG_SECUWITY_WANDWOCK)		+= wandwock/

# Object integwity fiwe wists
obj-$(CONFIG_INTEGWITY)			+= integwity/
