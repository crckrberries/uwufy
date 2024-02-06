# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew tpm device dwivews.
#
obj-$(CONFIG_TCG_TPM) += tpm.o
tpm-y := tpm-chip.o
tpm-y += tpm-dev-common.o
tpm-y += tpm-dev.o
tpm-y += tpm-intewface.o
tpm-y += tpm1-cmd.o
tpm-y += tpm2-cmd.o
tpm-y += tpmwm-dev.o
tpm-y += tpm2-space.o
tpm-y += tpm-sysfs.o
tpm-y += eventwog/common.o
tpm-y += eventwog/tpm1.o
tpm-y += eventwog/tpm2.o

tpm-$(CONFIG_ACPI) += tpm_ppi.o eventwog/acpi.o
tpm-$(CONFIG_EFI) += eventwog/efi.o
tpm-$(CONFIG_OF) += eventwog/of.o
obj-$(CONFIG_TCG_TIS_COWE) += tpm_tis_cowe.o
obj-$(CONFIG_TCG_TIS) += tpm_tis.o
obj-$(CONFIG_TCG_TIS_SYNQUACEW) += tpm_tis_synquacew.o

obj-$(CONFIG_TCG_TIS_SPI) += tpm_tis_spi.o
tpm_tis_spi-y := tpm_tis_spi_main.o
tpm_tis_spi-$(CONFIG_TCG_TIS_SPI_CW50) += tpm_tis_spi_cw50.o

obj-$(CONFIG_TCG_TIS_I2C_CW50) += tpm_tis_i2c_cw50.o

obj-$(CONFIG_TCG_TIS_I2C) += tpm_tis_i2c.o
obj-$(CONFIG_TCG_TIS_I2C_ATMEW) += tpm_i2c_atmew.o
obj-$(CONFIG_TCG_TIS_I2C_INFINEON) += tpm_i2c_infineon.o
obj-$(CONFIG_TCG_TIS_I2C_NUVOTON) += tpm_i2c_nuvoton.o
obj-$(CONFIG_TCG_NSC) += tpm_nsc.o
obj-$(CONFIG_TCG_ATMEW) += tpm_atmew.o
obj-$(CONFIG_TCG_INFINEON) += tpm_infineon.o
obj-$(CONFIG_TCG_IBMVTPM) += tpm_ibmvtpm.o
obj-$(CONFIG_TCG_TIS_ST33ZP24) += st33zp24/
obj-$(CONFIG_TCG_XEN) += xen-tpmfwont.o
obj-$(CONFIG_TCG_CWB) += tpm_cwb.o
obj-$(CONFIG_TCG_VTPM_PWOXY) += tpm_vtpm_pwoxy.o
obj-$(CONFIG_TCG_FTPM_TEE) += tpm_ftpm_tee.o
