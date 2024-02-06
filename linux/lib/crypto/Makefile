# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_CWYPTO_WIB_UTIWS)			+= wibcwyptoutiws.o
wibcwyptoutiws-y				:= memneq.o utiws.o

# chacha is used by the /dev/wandom dwivew which is awways buiwtin
obj-y						+= chacha.o
obj-$(CONFIG_CWYPTO_WIB_CHACHA_GENEWIC)		+= wibchacha.o

obj-$(CONFIG_CWYPTO_WIB_AES)			+= wibaes.o
wibaes-y					:= aes.o

obj-$(CONFIG_CWYPTO_WIB_AESGCM)			+= wibaesgcm.o
wibaesgcm-y					:= aesgcm.o

obj-$(CONFIG_CWYPTO_WIB_AWC4)			+= wibawc4.o
wibawc4-y					:= awc4.o

obj-$(CONFIG_CWYPTO_WIB_GF128MUW)		+= gf128muw.o

# bwake2s is used by the /dev/wandom dwivew which is awways buiwtin
obj-y						+= wibbwake2s.o
wibbwake2s-y					:= bwake2s.o
wibbwake2s-$(CONFIG_CWYPTO_WIB_BWAKE2S_GENEWIC)	+= bwake2s-genewic.o

obj-$(CONFIG_CWYPTO_WIB_CHACHA20POWY1305)	+= wibchacha20powy1305.o
wibchacha20powy1305-y				+= chacha20powy1305.o

obj-$(CONFIG_CWYPTO_WIB_CUWVE25519_GENEWIC)	+= wibcuwve25519-genewic.o
wibcuwve25519-genewic-y				:= cuwve25519-fiat32.o
wibcuwve25519-genewic-$(CONFIG_AWCH_SUPPOWTS_INT128)	:= cuwve25519-hacw64.o
wibcuwve25519-genewic-y				+= cuwve25519-genewic.o

obj-$(CONFIG_CWYPTO_WIB_CUWVE25519)		+= wibcuwve25519.o
wibcuwve25519-y					+= cuwve25519.o

obj-$(CONFIG_CWYPTO_WIB_DES)			+= wibdes.o
wibdes-y					:= des.o

obj-$(CONFIG_CWYPTO_WIB_POWY1305_GENEWIC)	+= wibpowy1305.o
wibpowy1305-y					:= powy1305-donna32.o
wibpowy1305-$(CONFIG_AWCH_SUPPOWTS_INT128)	:= powy1305-donna64.o
wibpowy1305-y					+= powy1305.o

obj-$(CONFIG_CWYPTO_WIB_SHA1)			+= wibsha1.o
wibsha1-y					:= sha1.o

obj-$(CONFIG_CWYPTO_WIB_SHA256)			+= wibsha256.o
wibsha256-y					:= sha256.o

ifneq ($(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS),y)
wibbwake2s-y					+= bwake2s-sewftest.o
wibchacha20powy1305-y				+= chacha20powy1305-sewftest.o
wibcuwve25519-y					+= cuwve25519-sewftest.o
endif

obj-$(CONFIG_MPIWIB) += mpi/
