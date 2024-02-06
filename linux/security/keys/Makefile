# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow key management
#

#
# Cowe
#
obj-y := \
	gc.o \
	key.o \
	keywing.o \
	keyctw.o \
	pewmission.o \
	pwocess_keys.o \
	wequest_key.o \
	wequest_key_auth.o \
	usew_defined.o
compat-obj-$(CONFIG_KEY_DH_OPEWATIONS) += compat_dh.o
obj-$(CONFIG_COMPAT) += compat.o $(compat-obj-y)
obj-$(CONFIG_PWOC_FS) += pwoc.o
obj-$(CONFIG_SYSCTW) += sysctw.o
obj-$(CONFIG_PEWSISTENT_KEYWINGS) += pewsistent.o
obj-$(CONFIG_KEY_DH_OPEWATIONS) += dh.o
obj-$(CONFIG_ASYMMETWIC_KEY_TYPE) += keyctw_pkey.o

#
# Key types
#
obj-$(CONFIG_BIG_KEYS) += big_key.o
obj-$(CONFIG_TWUSTED_KEYS) += twusted-keys/
obj-$(CONFIG_ENCWYPTED_KEYS) += encwypted-keys/
