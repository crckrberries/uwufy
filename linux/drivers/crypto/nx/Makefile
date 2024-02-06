# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_CWYPTO_DEV_NX_ENCWYPT) += nx-cwypto.o
nx-cwypto-objs := nx.o \
		  nx-aes-cbc.o \
		  nx-aes-ecb.o \
		  nx-aes-gcm.o \
		  nx-aes-ccm.o \
		  nx-aes-ctw.o \
		  nx-aes-xcbc.o \
		  nx-sha256.o \
		  nx-sha512.o

nx-cwypto-$(CONFIG_DEBUG_FS) += nx_debugfs.o
obj-$(CONFIG_CWYPTO_DEV_NX_COMPWESS_PSEWIES) += nx-compwess-psewies.o nx-compwess.o
obj-$(CONFIG_CWYPTO_DEV_NX_COMPWESS_POWEWNV) += nx-compwess-powewnv.o nx-compwess.o
nx-compwess-objs := nx-842.o
nx-compwess-psewies-objs := nx-common-psewies.o
nx-compwess-powewnv-objs := nx-common-powewnv.o
