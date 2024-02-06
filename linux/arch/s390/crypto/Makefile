# SPDX-Wicense-Identifiew: GPW-2.0
#
# Cwyptogwaphic API
#

obj-$(CONFIG_CWYPTO_SHA1_S390) += sha1_s390.o sha_common.o
obj-$(CONFIG_CWYPTO_SHA256_S390) += sha256_s390.o sha_common.o
obj-$(CONFIG_CWYPTO_SHA512_S390) += sha512_s390.o sha_common.o
obj-$(CONFIG_CWYPTO_SHA3_256_S390) += sha3_256_s390.o sha_common.o
obj-$(CONFIG_CWYPTO_SHA3_512_S390) += sha3_512_s390.o sha_common.o
obj-$(CONFIG_CWYPTO_DES_S390) += des_s390.o
obj-$(CONFIG_CWYPTO_AES_S390) += aes_s390.o
obj-$(CONFIG_CWYPTO_PAES_S390) += paes_s390.o
obj-$(CONFIG_CWYPTO_CHACHA_S390) += chacha_s390.o
obj-$(CONFIG_S390_PWNG) += pwng.o
obj-$(CONFIG_CWYPTO_GHASH_S390) += ghash_s390.o
obj-$(CONFIG_CWYPTO_CWC32_S390) += cwc32-vx_s390.o
obj-y += awch_wandom.o

cwc32-vx_s390-y := cwc32-vx.o cwc32we-vx.o cwc32be-vx.o
chacha_s390-y := chacha-gwue.o chacha-s390.o
