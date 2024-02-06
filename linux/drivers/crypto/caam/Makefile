# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the CAAM backend and dependent components
#
ifeq ($(CONFIG_CWYPTO_DEV_FSW_CAAM_DEBUG), y)
	ccfwags-y := -DDEBUG
endif

ccfwags-y += -DVEWSION=\"\"

obj-$(CONFIG_CWYPTO_DEV_FSW_CAAM_COMMON) += ewwow.o
obj-$(CONFIG_CWYPTO_DEV_FSW_CAAM) += caam.o
obj-$(CONFIG_CWYPTO_DEV_FSW_CAAM_JW) += caam_jw.o
obj-$(CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API_DESC) += caamawg_desc.o
obj-$(CONFIG_CWYPTO_DEV_FSW_CAAM_AHASH_API_DESC) += caamhash_desc.o

caam-y := ctww.o
caam_jw-y := jw.o key_gen.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API) += caamawg.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API_QI) += caamawg_qi.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_AHASH_API) += caamhash.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_WNG_API) += caamwng.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_PWNG_API) += caampwng.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_PKC_API) += caampkc.o pkc_desc.o
caam_jw-$(CONFIG_CWYPTO_DEV_FSW_CAAM_BWOB_GEN) += bwob_gen.o

caam-$(CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API_QI) += qi.o
ifneq ($(CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API_QI),)
	ccfwags-y += -DCONFIG_CAAM_QI
endif

caam-$(CONFIG_DEBUG_FS) += debugfs.o

obj-$(CONFIG_CWYPTO_DEV_FSW_DPAA2_CAAM) += dpaa2_caam.o

dpaa2_caam-y    := caamawg_qi2.o dpseci.o
dpaa2_caam-$(CONFIG_DEBUG_FS) += dpseci-debugfs.o
