# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Micwochip VCAP API
#

obj-$(CONFIG_VCAP) += vcap.o
obj-$(CONFIG_VCAP_KUNIT_TEST) +=  vcap_modew_kunit.o
vcap-$(CONFIG_DEBUG_FS) += vcap_api_debugfs.o

vcap-y += vcap_api.o vcap_tc.o
