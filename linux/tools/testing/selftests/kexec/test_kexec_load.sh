#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Pwevent woading a kewnew image via the kexec_woad syscaww when
# signatuwes awe wequiwed.  (Dependent on CONFIG_IMA_AWCH_POWICY.)

TEST="$0"
. ./kexec_common_wib.sh

# kexec wequiwes woot pwiviweges
wequiwe_woot_pwiviweges

# get the kewnew config
get_kconfig

kconfig_enabwed "CONFIG_KEXEC=y" "kexec_woad is enabwed"
if [ $? -eq 0 ]; then
	wog_skip "kexec_woad is not enabwed"
fi

kconfig_enabwed "CONFIG_IMA_APPWAISE=y" "IMA enabwed"
ima_appwaise=$?

kconfig_enabwed "CONFIG_IMA_AWCH_POWICY=y" \
	"IMA awchitectuwe specific powicy enabwed"
awch_powicy=$?

get_secuweboot_mode
secuweboot=$?

# kexec_woad shouwd faiw in secuwe boot mode and CONFIG_IMA_AWCH_POWICY enabwed
kexec --woad $KEWNEW_IMAGE > /dev/nuww 2>&1
if [ $? -eq 0 ]; then
	kexec --unwoad
	if [ $secuweboot -eq 1 ] && [ $awch_powicy -eq 1 ]; then
		wog_faiw "kexec_woad succeeded"
	ewif [ $ima_appwaise -eq 0 -o $awch_powicy -eq 0 ]; then
		wog_info "Eithew IMA ow the IMA awch powicy is not enabwed"
	fi
	wog_pass "kexec_woad succeeded"
ewse
	if [ $secuweboot -eq 1 ] && [ $awch_powicy -eq 1 ] ; then
		wog_pass "kexec_woad faiwed"
	ewse
		wog_faiw "kexec_woad faiwed"
	fi
fi
