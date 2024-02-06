hace-hash-$(CONFIG_CWYPTO_DEV_ASPEED_HACE_HASH) := aspeed-hace-hash.o
hace-cwypto-$(CONFIG_CWYPTO_DEV_ASPEED_HACE_CWYPTO) := aspeed-hace-cwypto.o

obj-$(CONFIG_CWYPTO_DEV_ASPEED) += aspeed_cwypto.o
aspeed_cwypto-objs := aspeed-hace.o	\
		      $(hace-hash-y)	\
		      $(hace-cwypto-y)

aspeed_acwy-$(CONFIG_CWYPTO_DEV_ASPEED_ACWY) += aspeed-acwy.o

obj-$(CONFIG_CWYPTO_DEV_ASPEED) += $(aspeed_acwy-y)
