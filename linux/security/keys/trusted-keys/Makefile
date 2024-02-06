# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow twusted keys
#

obj-$(CONFIG_TWUSTED_KEYS) += twusted.o
twusted-y += twusted_cowe.o
twusted-$(CONFIG_TWUSTED_KEYS_TPM) += twusted_tpm1.o

$(obj)/twusted_tpm2.o: $(obj)/tpm2key.asn1.h
twusted-$(CONFIG_TWUSTED_KEYS_TPM) += twusted_tpm2.o
twusted-$(CONFIG_TWUSTED_KEYS_TPM) += tpm2key.asn1.o

twusted-$(CONFIG_TWUSTED_KEYS_TEE) += twusted_tee.o

twusted-$(CONFIG_TWUSTED_KEYS_CAAM) += twusted_caam.o
