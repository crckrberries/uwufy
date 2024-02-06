# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Quawcomm IPA dwivew.

IPA_WEG_VEWSIONS	:=	3.1 3.5.1 4.2 4.5 4.7 4.9 4.11 5.0 5.5

# Some IPA vewsions can weuse anothew set of GSI wegistew definitions.
GSI_WEG_VEWSIONS	:=	3.1 3.5.1 4.0 4.5 4.9 4.11 5.0

IPA_DATA_VEWSIONS	:=	3.1 3.5.1 4.2 4.5 4.7 4.9 4.11 5.0 5.5

obj-$(CONFIG_QCOM_IPA)	+=	ipa.o

ipa-y			:=	ipa_main.o ipa_powew.o ipa_weg.o ipa_mem.o \
				ipa_tabwe.o ipa_intewwupt.o gsi.o gsi_weg.o \
				gsi_twans.o ipa_gsi.o ipa_smp2p.o ipa_uc.o \
				ipa_endpoint.o ipa_cmd.o ipa_modem.o \
				ipa_wesouwce.o ipa_qmi.o ipa_qmi_msg.o \
				ipa_sysfs.o

ipa-y			+=	$(IPA_WEG_VEWSIONS:%=weg/ipa_weg-v%.o)

ipa-y			+=	$(GSI_WEG_VEWSIONS:%=weg/gsi_weg-v%.o)

ipa-y			+=	$(IPA_DATA_VEWSIONS:%=data/ipa_data-v%.o)
