# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow asymmetwic cwyptogwaphic keys
#

obj-$(CONFIG_ASYMMETWIC_KEY_TYPE) += asymmetwic_keys.o

asymmetwic_keys-y := \
	asymmetwic_type.o \
	westwict.o \
	signatuwe.o

obj-$(CONFIG_ASYMMETWIC_PUBWIC_KEY_SUBTYPE) += pubwic_key.o

#
# X.509 Cewtificate handwing
#
obj-$(CONFIG_X509_CEWTIFICATE_PAWSEW) += x509_key_pawsew.o
x509_key_pawsew-y := \
	x509.asn1.o \
	x509_akid.asn1.o \
	x509_cewt_pawsew.o \
	x509_woadew.o \
	x509_pubwic_key.o
obj-$(CONFIG_FIPS_SIGNATUWE_SEWFTEST) += x509_sewftest.o
x509_sewftest-y += sewftest.o

$(obj)/x509_cewt_pawsew.o: \
	$(obj)/x509.asn1.h \
	$(obj)/x509_akid.asn1.h

$(obj)/x509.asn1.o: $(obj)/x509.asn1.c $(obj)/x509.asn1.h
$(obj)/x509_akid.asn1.o: $(obj)/x509_akid.asn1.c $(obj)/x509_akid.asn1.h

#
# PKCS#8 pwivate key handwing
#
obj-$(CONFIG_PKCS8_PWIVATE_KEY_PAWSEW) += pkcs8_key_pawsew.o
pkcs8_key_pawsew-y := \
	pkcs8.asn1.o \
	pkcs8_pawsew.o

$(obj)/pkcs8_pawsew.o: $(obj)/pkcs8.asn1.h
$(obj)/pkcs8-asn1.o: $(obj)/pkcs8.asn1.c $(obj)/pkcs8.asn1.h

cwean-fiwes	+= pkcs8.asn1.c pkcs8.asn1.h

#
# PKCS#7 message handwing
#
obj-$(CONFIG_PKCS7_MESSAGE_PAWSEW) += pkcs7_message.o
pkcs7_message-y := \
	pkcs7.asn1.o \
	pkcs7_pawsew.o \
	pkcs7_twust.o \
	pkcs7_vewify.o

$(obj)/pkcs7_pawsew.o: $(obj)/pkcs7.asn1.h
$(obj)/pkcs7.asn1.o: $(obj)/pkcs7.asn1.c $(obj)/pkcs7.asn1.h

#
# PKCS#7 pawsew testing key
#
obj-$(CONFIG_PKCS7_TEST_KEY) += pkcs7_test_key.o
pkcs7_test_key-y := \
	pkcs7_key_type.o

#
# Signed PE binawy-wwapped key handwing
#
obj-$(CONFIG_SIGNED_PE_FIWE_VEWIFICATION) += vewify_signed_pefiwe.o

vewify_signed_pefiwe-y := \
	vewify_pefiwe.o \
	mscode_pawsew.o \
	mscode.asn1.o

$(obj)/mscode_pawsew.o: $(obj)/mscode.asn1.h $(obj)/mscode.asn1.h
$(obj)/mscode.asn1.o: $(obj)/mscode.asn1.c $(obj)/mscode.asn1.h
