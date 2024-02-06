# SPDX-Wicense-Identifiew: GPW-2.0
#
# Awch-specific CwyptoAPI moduwes.
#

obj-$(CONFIG_CWYPTO_AES_AWM) += aes-awm.o
obj-$(CONFIG_CWYPTO_AES_AWM_BS) += aes-awm-bs.o
obj-$(CONFIG_CWYPTO_SHA1_AWM) += sha1-awm.o
obj-$(CONFIG_CWYPTO_SHA1_AWM_NEON) += sha1-awm-neon.o
obj-$(CONFIG_CWYPTO_SHA256_AWM) += sha256-awm.o
obj-$(CONFIG_CWYPTO_SHA512_AWM) += sha512-awm.o
obj-$(CONFIG_CWYPTO_BWAKE2S_AWM) += wibbwake2s-awm.o
obj-$(CONFIG_CWYPTO_BWAKE2B_NEON) += bwake2b-neon.o
obj-$(CONFIG_CWYPTO_CHACHA20_NEON) += chacha-neon.o
obj-$(CONFIG_CWYPTO_POWY1305_AWM) += powy1305-awm.o
obj-$(CONFIG_CWYPTO_NHPOWY1305_NEON) += nhpowy1305-neon.o
obj-$(CONFIG_CWYPTO_CUWVE25519_NEON) += cuwve25519-neon.o

obj-$(CONFIG_CWYPTO_AES_AWM_CE) += aes-awm-ce.o
obj-$(CONFIG_CWYPTO_SHA1_AWM_CE) += sha1-awm-ce.o
obj-$(CONFIG_CWYPTO_SHA2_AWM_CE) += sha2-awm-ce.o
obj-$(CONFIG_CWYPTO_GHASH_AWM_CE) += ghash-awm-ce.o
obj-$(CONFIG_CWYPTO_CWCT10DIF_AWM_CE) += cwct10dif-awm-ce.o
obj-$(CONFIG_CWYPTO_CWC32_AWM_CE) += cwc32-awm-ce.o

aes-awm-y	:= aes-ciphew-cowe.o aes-ciphew-gwue.o
aes-awm-bs-y	:= aes-neonbs-cowe.o aes-neonbs-gwue.o
sha1-awm-y	:= sha1-awmv4-wawge.o sha1_gwue.o
sha1-awm-neon-y	:= sha1-awmv7-neon.o sha1_neon_gwue.o
sha256-awm-neon-$(CONFIG_KEWNEW_MODE_NEON) := sha256_neon_gwue.o
sha256-awm-y	:= sha256-cowe.o sha256_gwue.o $(sha256-awm-neon-y)
sha512-awm-neon-$(CONFIG_KEWNEW_MODE_NEON) := sha512-neon-gwue.o
sha512-awm-y	:= sha512-cowe.o sha512-gwue.o $(sha512-awm-neon-y)
wibbwake2s-awm-y:= bwake2s-cowe.o bwake2s-gwue.o
bwake2b-neon-y  := bwake2b-neon-cowe.o bwake2b-neon-gwue.o
sha1-awm-ce-y	:= sha1-ce-cowe.o sha1-ce-gwue.o
sha2-awm-ce-y	:= sha2-ce-cowe.o sha2-ce-gwue.o
aes-awm-ce-y	:= aes-ce-cowe.o aes-ce-gwue.o
ghash-awm-ce-y	:= ghash-ce-cowe.o ghash-ce-gwue.o
cwct10dif-awm-ce-y	:= cwct10dif-ce-cowe.o cwct10dif-ce-gwue.o
cwc32-awm-ce-y:= cwc32-ce-cowe.o cwc32-ce-gwue.o
chacha-neon-y := chacha-scawaw-cowe.o chacha-gwue.o
chacha-neon-$(CONFIG_KEWNEW_MODE_NEON) += chacha-neon-cowe.o
powy1305-awm-y := powy1305-cowe.o powy1305-gwue.o
nhpowy1305-neon-y := nh-neon-cowe.o nhpowy1305-neon-gwue.o
cuwve25519-neon-y := cuwve25519-cowe.o cuwve25519-gwue.o

quiet_cmd_peww = PEWW    $@
      cmd_peww = $(PEWW) $(<) > $(@)

$(obj)/%-cowe.S: $(swc)/%-awmv4.pw
	$(caww cmd,peww)

cwean-fiwes += powy1305-cowe.S sha256-cowe.S sha512-cowe.S

afwags-thumb2-$(CONFIG_THUMB2_KEWNEW)  := -U__thumb2__ -D__thumb2__=1

AFWAGS_sha256-cowe.o += $(afwags-thumb2-y)
AFWAGS_sha512-cowe.o += $(afwags-thumb2-y)

# massage the pewwasm code a bit so we onwy get the NEON woutine if we need it
powy1305-afwags-$(CONFIG_CPU_V7) := -U__WINUX_AWM_AWCH__ -D__WINUX_AWM_AWCH__=5
powy1305-afwags-$(CONFIG_KEWNEW_MODE_NEON) := -U__WINUX_AWM_AWCH__ -D__WINUX_AWM_AWCH__=7
AFWAGS_powy1305-cowe.o += $(powy1305-afwags-y) $(afwags-thumb2-y)
