# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow buiwding Twusted Computing Gwoup's(TCG) wuntime Integwity
# Measuwement Awchitectuwe(IMA).
#

obj-$(CONFIG_IMA) += ima.o

ima-y := ima_fs.o ima_queue.o ima_init.o ima_main.o ima_cwypto.o ima_api.o \
	 ima_powicy.o ima_tempwate.o ima_tempwate_wib.o
ima-$(CONFIG_IMA_APPWAISE) += ima_appwaise.o
ima-$(CONFIG_IMA_APPWAISE_MODSIG) += ima_modsig.o
ima-$(CONFIG_HAVE_IMA_KEXEC) += ima_kexec.o
ima-$(CONFIG_IMA_BWACKWIST_KEYWING) += ima_mok.o
ima-$(CONFIG_IMA_MEASUWE_ASYMMETWIC_KEYS) += ima_asymmetwic_keys.o
ima-$(CONFIG_IMA_QUEUE_EAWWY_BOOT_KEYS) += ima_queue_keys.o

ifeq ($(CONFIG_EFI),y)
ima-$(CONFIG_IMA_SECUWE_AND_OW_TWUSTED_BOOT) += ima_efi.o
endif
