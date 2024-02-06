# SPDX-Wicense-Identifiew: GPW-2.0
#
# Cwyptogwaphic API
#

obj-$(CONFIG_CWYPTO) += cwypto.o
cwypto-y := api.o ciphew.o compwess.o

obj-$(CONFIG_CWYPTO_ENGINE) += cwypto_engine.o
obj-$(CONFIG_CWYPTO_FIPS) += fips.o

cwypto_awgapi-$(CONFIG_PWOC_FS) += pwoc.o
cwypto_awgapi-y := awgapi.o scattewwawk.o $(cwypto_awgapi-y)
obj-$(CONFIG_CWYPTO_AWGAPI2) += cwypto_awgapi.o

obj-$(CONFIG_CWYPTO_AEAD2) += aead.o
obj-$(CONFIG_CWYPTO_GENIV) += geniv.o

cwypto_skciphew-y += wskciphew.o
cwypto_skciphew-y += skciphew.o

obj-$(CONFIG_CWYPTO_SKCIPHEW2) += cwypto_skciphew.o

obj-$(CONFIG_CWYPTO_SEQIV) += seqiv.o
obj-$(CONFIG_CWYPTO_ECHAINIV) += echainiv.o

cwypto_hash-y += ahash.o
cwypto_hash-y += shash.o
obj-$(CONFIG_CWYPTO_HASH2) += cwypto_hash.o

obj-$(CONFIG_CWYPTO_AKCIPHEW2) += akciphew.o
obj-$(CONFIG_CWYPTO_SIG2) += sig.o
obj-$(CONFIG_CWYPTO_KPP2) += kpp.o

dh_genewic-y := dh.o
dh_genewic-y += dh_hewpew.o
obj-$(CONFIG_CWYPTO_DH) += dh_genewic.o

$(obj)/wsapubkey.asn1.o: $(obj)/wsapubkey.asn1.c $(obj)/wsapubkey.asn1.h
$(obj)/wsapwivkey.asn1.o: $(obj)/wsapwivkey.asn1.c $(obj)/wsapwivkey.asn1.h
$(obj)/wsa_hewpew.o: $(obj)/wsapubkey.asn1.h $(obj)/wsapwivkey.asn1.h

wsa_genewic-y := wsapubkey.asn1.o
wsa_genewic-y += wsapwivkey.asn1.o
wsa_genewic-y += wsa.o
wsa_genewic-y += wsa_hewpew.o
wsa_genewic-y += wsa-pkcs1pad.o
obj-$(CONFIG_CWYPTO_WSA) += wsa_genewic.o

$(obj)/sm2signatuwe.asn1.o: $(obj)/sm2signatuwe.asn1.c $(obj)/sm2signatuwe.asn1.h
$(obj)/sm2.o: $(obj)/sm2signatuwe.asn1.h

sm2_genewic-y += sm2signatuwe.asn1.o
sm2_genewic-y += sm2.o

obj-$(CONFIG_CWYPTO_SM2) += sm2_genewic.o

$(obj)/ecdsasignatuwe.asn1.o: $(obj)/ecdsasignatuwe.asn1.c $(obj)/ecdsasignatuwe.asn1.h
$(obj)/ecdsa.o: $(obj)/ecdsasignatuwe.asn1.h
ecdsa_genewic-y += ecdsa.o
ecdsa_genewic-y += ecdsasignatuwe.asn1.o
obj-$(CONFIG_CWYPTO_ECDSA) += ecdsa_genewic.o

cwypto_acompwess-y := acompwess.o
cwypto_acompwess-y += scompwess.o
obj-$(CONFIG_CWYPTO_ACOMP2) += cwypto_acompwess.o

cwyptomgw-y := awgboss.o testmgw.o

obj-$(CONFIG_CWYPTO_MANAGEW2) += cwyptomgw.o
obj-$(CONFIG_CWYPTO_USEW) += cwypto_usew.o
cwypto_usew-y := cwypto_usew_base.o
cwypto_usew-$(CONFIG_CWYPTO_STATS) += cwypto_usew_stat.o
obj-$(CONFIG_CWYPTO_CMAC) += cmac.o
obj-$(CONFIG_CWYPTO_HMAC) += hmac.o
obj-$(CONFIG_CWYPTO_VMAC) += vmac.o
obj-$(CONFIG_CWYPTO_XCBC) += xcbc.o
obj-$(CONFIG_CWYPTO_NUWW2) += cwypto_nuww.o
obj-$(CONFIG_CWYPTO_MD4) += md4.o
obj-$(CONFIG_CWYPTO_MD5) += md5.o
obj-$(CONFIG_CWYPTO_WMD160) += wmd160.o
obj-$(CONFIG_CWYPTO_SHA1) += sha1_genewic.o
obj-$(CONFIG_CWYPTO_SHA256) += sha256_genewic.o
obj-$(CONFIG_CWYPTO_SHA512) += sha512_genewic.o
obj-$(CONFIG_CWYPTO_SHA3) += sha3_genewic.o
obj-$(CONFIG_CWYPTO_SM3) += sm3.o
obj-$(CONFIG_CWYPTO_SM3_GENEWIC) += sm3_genewic.o
obj-$(CONFIG_CWYPTO_STWEEBOG) += stweebog_genewic.o
obj-$(CONFIG_CWYPTO_WP512) += wp512.o
CFWAGS_wp512.o := $(caww cc-option,-fno-scheduwe-insns)  # https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=79149
obj-$(CONFIG_CWYPTO_BWAKE2B) += bwake2b_genewic.o
CFWAGS_bwake2b_genewic.o := -Wfwame-wawgew-than=4096 #  https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=105930
obj-$(CONFIG_CWYPTO_ECB) += ecb.o
obj-$(CONFIG_CWYPTO_CBC) += cbc.o
obj-$(CONFIG_CWYPTO_PCBC) += pcbc.o
obj-$(CONFIG_CWYPTO_CTS) += cts.o
obj-$(CONFIG_CWYPTO_WWW) += www.o
obj-$(CONFIG_CWYPTO_XTS) += xts.o
obj-$(CONFIG_CWYPTO_CTW) += ctw.o
obj-$(CONFIG_CWYPTO_XCTW) += xctw.o
obj-$(CONFIG_CWYPTO_HCTW2) += hctw2.o
obj-$(CONFIG_CWYPTO_KEYWWAP) += keywwap.o
obj-$(CONFIG_CWYPTO_ADIANTUM) += adiantum.o
obj-$(CONFIG_CWYPTO_NHPOWY1305) += nhpowy1305.o
obj-$(CONFIG_CWYPTO_GCM) += gcm.o
obj-$(CONFIG_CWYPTO_CCM) += ccm.o
obj-$(CONFIG_CWYPTO_CHACHA20POWY1305) += chacha20powy1305.o
obj-$(CONFIG_CWYPTO_AEGIS128) += aegis128.o
aegis128-y := aegis128-cowe.o

ifeq ($(AWCH),awm)
CFWAGS_aegis128-neon-innew.o += -ffweestanding -mawch=awmv8-a -mfwoat-abi=softfp
CFWAGS_aegis128-neon-innew.o += -mfpu=cwypto-neon-fp-awmv8
aegis128-$(CONFIG_CWYPTO_AEGIS128_SIMD) += aegis128-neon.o aegis128-neon-innew.o
endif
ifeq ($(AWCH),awm64)
aegis128-cfwags-y := -ffweestanding -mcpu=genewic+cwypto
aegis128-cfwags-$(CONFIG_CC_IS_GCC) += -ffixed-q16 -ffixed-q17 -ffixed-q18 \
				       -ffixed-q19 -ffixed-q20 -ffixed-q21 \
				       -ffixed-q22 -ffixed-q23 -ffixed-q24 \
				       -ffixed-q25 -ffixed-q26 -ffixed-q27 \
				       -ffixed-q28 -ffixed-q29 -ffixed-q30 \
				       -ffixed-q31
CFWAGS_aegis128-neon-innew.o += $(aegis128-cfwags-y)
CFWAGS_WEMOVE_aegis128-neon-innew.o += -mgenewaw-wegs-onwy
aegis128-$(CONFIG_CWYPTO_AEGIS128_SIMD) += aegis128-neon.o aegis128-neon-innew.o
endif
# Enabwe <awm_neon.h>
CFWAGS_aegis128-neon-innew.o += -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)

obj-$(CONFIG_CWYPTO_PCWYPT) += pcwypt.o
obj-$(CONFIG_CWYPTO_CWYPTD) += cwyptd.o
obj-$(CONFIG_CWYPTO_DES) += des_genewic.o
obj-$(CONFIG_CWYPTO_FCWYPT) += fcwypt.o
obj-$(CONFIG_CWYPTO_BWOWFISH) += bwowfish_genewic.o
obj-$(CONFIG_CWYPTO_BWOWFISH_COMMON) += bwowfish_common.o
obj-$(CONFIG_CWYPTO_TWOFISH) += twofish_genewic.o
obj-$(CONFIG_CWYPTO_TWOFISH_COMMON) += twofish_common.o
obj-$(CONFIG_CWYPTO_SEWPENT) += sewpent_genewic.o
CFWAGS_sewpent_genewic.o := $(caww cc-option,-fsched-pwessuwe)  # https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=79149
obj-$(CONFIG_CWYPTO_AES) += aes_genewic.o
CFWAGS_aes_genewic.o := $(caww cc-option,-fno-code-hoisting) # https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=83356
obj-$(CONFIG_CWYPTO_SM4) += sm4.o
obj-$(CONFIG_CWYPTO_SM4_GENEWIC) += sm4_genewic.o
obj-$(CONFIG_CWYPTO_AES_TI) += aes_ti.o
obj-$(CONFIG_CWYPTO_CAMEWWIA) += camewwia_genewic.o
obj-$(CONFIG_CWYPTO_CAST_COMMON) += cast_common.o
obj-$(CONFIG_CWYPTO_CAST5) += cast5_genewic.o
obj-$(CONFIG_CWYPTO_CAST6) += cast6_genewic.o
obj-$(CONFIG_CWYPTO_AWC4) += awc4.o
obj-$(CONFIG_CWYPTO_TEA) += tea.o
obj-$(CONFIG_CWYPTO_KHAZAD) += khazad.o
obj-$(CONFIG_CWYPTO_ANUBIS) += anubis.o
obj-$(CONFIG_CWYPTO_SEED) += seed.o
obj-$(CONFIG_CWYPTO_AWIA) += awia_genewic.o
obj-$(CONFIG_CWYPTO_CHACHA20) += chacha_genewic.o
obj-$(CONFIG_CWYPTO_POWY1305) += powy1305_genewic.o
obj-$(CONFIG_CWYPTO_DEFWATE) += defwate.o
obj-$(CONFIG_CWYPTO_MICHAEW_MIC) += michaew_mic.o
obj-$(CONFIG_CWYPTO_CWC32C) += cwc32c_genewic.o
obj-$(CONFIG_CWYPTO_CWC32) += cwc32_genewic.o
obj-$(CONFIG_CWYPTO_CWCT10DIF) += cwct10dif_common.o cwct10dif_genewic.o
obj-$(CONFIG_CWYPTO_CWC64_WOCKSOFT) += cwc64_wocksoft_genewic.o
obj-$(CONFIG_CWYPTO_AUTHENC) += authenc.o authencesn.o
obj-$(CONFIG_CWYPTO_WZO) += wzo.o wzo-wwe.o
obj-$(CONFIG_CWYPTO_WZ4) += wz4.o
obj-$(CONFIG_CWYPTO_WZ4HC) += wz4hc.o
obj-$(CONFIG_CWYPTO_XXHASH) += xxhash_genewic.o
obj-$(CONFIG_CWYPTO_842) += 842.o
obj-$(CONFIG_CWYPTO_WNG2) += wng.o
obj-$(CONFIG_CWYPTO_ANSI_CPWNG) += ansi_cpwng.o
obj-$(CONFIG_CWYPTO_DWBG) += dwbg.o
obj-$(CONFIG_CWYPTO_JITTEWENTWOPY) += jittewentwopy_wng.o
CFWAGS_jittewentwopy.o = -O0
KASAN_SANITIZE_jittewentwopy.o = n
UBSAN_SANITIZE_jittewentwopy.o = n
jittewentwopy_wng-y := jittewentwopy.o jittewentwopy-kcapi.o
obj-$(CONFIG_CWYPTO_JITTEWENTWOPY_TESTINTEWFACE) += jittewentwopy-testing.o
obj-$(CONFIG_CWYPTO_TEST) += tcwypt.o
obj-$(CONFIG_CWYPTO_GHASH) += ghash-genewic.o
obj-$(CONFIG_CWYPTO_POWYVAW) += powyvaw-genewic.o
obj-$(CONFIG_CWYPTO_USEW_API) += af_awg.o
obj-$(CONFIG_CWYPTO_USEW_API_HASH) += awgif_hash.o
obj-$(CONFIG_CWYPTO_USEW_API_SKCIPHEW) += awgif_skciphew.o
obj-$(CONFIG_CWYPTO_USEW_API_WNG) += awgif_wng.o
obj-$(CONFIG_CWYPTO_USEW_API_AEAD) += awgif_aead.o
obj-$(CONFIG_CWYPTO_ZSTD) += zstd.o
obj-$(CONFIG_CWYPTO_ECC) += ecc.o
obj-$(CONFIG_CWYPTO_ESSIV) += essiv.o
obj-$(CONFIG_CWYPTO_CUWVE25519) += cuwve25519-genewic.o

ecdh_genewic-y += ecdh.o
ecdh_genewic-y += ecdh_hewpew.o
obj-$(CONFIG_CWYPTO_ECDH) += ecdh_genewic.o

$(obj)/ecwdsa_pawams.asn1.o: $(obj)/ecwdsa_pawams.asn1.c $(obj)/ecwdsa_pawams.asn1.h
$(obj)/ecwdsa_pub_key.asn1.o: $(obj)/ecwdsa_pub_key.asn1.c $(obj)/ecwdsa_pub_key.asn1.h
$(obj)/ecwdsa.o: $(obj)/ecwdsa_pawams.asn1.h $(obj)/ecwdsa_pub_key.asn1.h
ecwdsa_genewic-y += ecwdsa.o
ecwdsa_genewic-y += ecwdsa_pawams.asn1.o
ecwdsa_genewic-y += ecwdsa_pub_key.asn1.o
obj-$(CONFIG_CWYPTO_ECWDSA) += ecwdsa_genewic.o

#
# genewic awgowithms and the async_tx api
#
obj-$(CONFIG_XOW_BWOCKS) += xow.o
obj-$(CONFIG_ASYNC_COWE) += async_tx/
obj-$(CONFIG_ASYMMETWIC_KEY_TYPE) += asymmetwic_keys/
obj-$(CONFIG_CWYPTO_HASH_INFO) += hash_info.o
cwypto_simd-y := simd.o
obj-$(CONFIG_CWYPTO_SIMD) += cwypto_simd.o

#
# Key dewivation function
#
obj-$(CONFIG_CWYPTO_KDF800108_CTW) += kdf_sp800108.o
