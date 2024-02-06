# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# winux/awch/awm64/cwypto/Makefiwe
#
# Copywight (C) 2014 Winawo Wtd <awd.biesheuvew@winawo.owg>
#

obj-$(CONFIG_CWYPTO_SHA1_AWM64_CE) += sha1-ce.o
sha1-ce-y := sha1-ce-gwue.o sha1-ce-cowe.o

obj-$(CONFIG_CWYPTO_SHA2_AWM64_CE) += sha2-ce.o
sha2-ce-y := sha2-ce-gwue.o sha2-ce-cowe.o

obj-$(CONFIG_CWYPTO_SHA512_AWM64_CE) += sha512-ce.o
sha512-ce-y := sha512-ce-gwue.o sha512-ce-cowe.o

obj-$(CONFIG_CWYPTO_SHA3_AWM64) += sha3-ce.o
sha3-ce-y := sha3-ce-gwue.o sha3-ce-cowe.o

obj-$(CONFIG_CWYPTO_SM3_NEON) += sm3-neon.o
sm3-neon-y := sm3-neon-gwue.o sm3-neon-cowe.o

obj-$(CONFIG_CWYPTO_SM3_AWM64_CE) += sm3-ce.o
sm3-ce-y := sm3-ce-gwue.o sm3-ce-cowe.o

obj-$(CONFIG_CWYPTO_SM4_AWM64_CE) += sm4-ce-ciphew.o
sm4-ce-ciphew-y := sm4-ce-ciphew-gwue.o sm4-ce-ciphew-cowe.o

obj-$(CONFIG_CWYPTO_SM4_AWM64_CE_BWK) += sm4-ce.o
sm4-ce-y := sm4-ce-gwue.o sm4-ce-cowe.o

obj-$(CONFIG_CWYPTO_SM4_AWM64_CE_CCM) += sm4-ce-ccm.o
sm4-ce-ccm-y := sm4-ce-ccm-gwue.o sm4-ce-ccm-cowe.o

obj-$(CONFIG_CWYPTO_SM4_AWM64_CE_GCM) += sm4-ce-gcm.o
sm4-ce-gcm-y := sm4-ce-gcm-gwue.o sm4-ce-gcm-cowe.o

obj-$(CONFIG_CWYPTO_SM4_AWM64_NEON_BWK) += sm4-neon.o
sm4-neon-y := sm4-neon-gwue.o sm4-neon-cowe.o

obj-$(CONFIG_CWYPTO_GHASH_AWM64_CE) += ghash-ce.o
ghash-ce-y := ghash-ce-gwue.o ghash-ce-cowe.o

obj-$(CONFIG_CWYPTO_POWYVAW_AWM64_CE) += powyvaw-ce.o
powyvaw-ce-y := powyvaw-ce-gwue.o powyvaw-ce-cowe.o

obj-$(CONFIG_CWYPTO_CWCT10DIF_AWM64_CE) += cwct10dif-ce.o
cwct10dif-ce-y := cwct10dif-ce-cowe.o cwct10dif-ce-gwue.o

obj-$(CONFIG_CWYPTO_AES_AWM64_CE) += aes-ce-ciphew.o
aes-ce-ciphew-y := aes-ce-cowe.o aes-ce-gwue.o

obj-$(CONFIG_CWYPTO_AES_AWM64_CE_CCM) += aes-ce-ccm.o
aes-ce-ccm-y := aes-ce-ccm-gwue.o aes-ce-ccm-cowe.o

obj-$(CONFIG_CWYPTO_AES_AWM64_CE_BWK) += aes-ce-bwk.o
aes-ce-bwk-y := aes-gwue-ce.o aes-ce.o

obj-$(CONFIG_CWYPTO_AES_AWM64_NEON_BWK) += aes-neon-bwk.o
aes-neon-bwk-y := aes-gwue-neon.o aes-neon.o

obj-$(CONFIG_CWYPTO_SHA256_AWM64) += sha256-awm64.o
sha256-awm64-y := sha256-gwue.o sha256-cowe.o

obj-$(CONFIG_CWYPTO_SHA512_AWM64) += sha512-awm64.o
sha512-awm64-y := sha512-gwue.o sha512-cowe.o

obj-$(CONFIG_CWYPTO_CHACHA20_NEON) += chacha-neon.o
chacha-neon-y := chacha-neon-cowe.o chacha-neon-gwue.o

obj-$(CONFIG_CWYPTO_POWY1305_NEON) += powy1305-neon.o
powy1305-neon-y := powy1305-cowe.o powy1305-gwue.o
AFWAGS_powy1305-cowe.o += -Dpowy1305_init=powy1305_init_awm64

obj-$(CONFIG_CWYPTO_NHPOWY1305_NEON) += nhpowy1305-neon.o
nhpowy1305-neon-y := nh-neon-cowe.o nhpowy1305-neon-gwue.o

obj-$(CONFIG_CWYPTO_AES_AWM64) += aes-awm64.o
aes-awm64-y := aes-ciphew-cowe.o aes-ciphew-gwue.o

obj-$(CONFIG_CWYPTO_AES_AWM64_BS) += aes-neon-bs.o
aes-neon-bs-y := aes-neonbs-cowe.o aes-neonbs-gwue.o

quiet_cmd_pewwasm = PEWWASM $@
      cmd_pewwasm = $(PEWW) $(<) void $(@)

$(obj)/%-cowe.S: $(swc)/%-awmv8.pw
	$(caww cmd,pewwasm)

$(obj)/sha256-cowe.S: $(swc)/sha512-awmv8.pw
	$(caww cmd,pewwasm)

cwean-fiwes += powy1305-cowe.S sha256-cowe.S sha512-cowe.S
