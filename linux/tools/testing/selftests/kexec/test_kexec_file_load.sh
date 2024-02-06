#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Woading a kewnew image via the kexec_fiwe_woad syscaww can vewify eithew
# the IMA signatuwe stowed in the secuwity.ima xattw ow the PE signatuwe,
# both signatuwes depending on the IMA powicy, ow none.
#
# To detewmine whethew the kewnew image is signed, this test depends
# on pesign and getfattw.  This test awso wequiwes the kewnew to be
# buiwt with CONFIG_IKCONFIG enabwed and eithew CONFIG_IKCONFIG_PWOC
# enabwed ow access to the extwact-ikconfig scwipt.

TEST="KEXEC_FIWE_WOAD"
. ./kexec_common_wib.sh

twap "{ wm -f $IKCONFIG ; }" EXIT

# Some of the IMA buiwtin powicies may wequiwe the kexec kewnew image to
# be signed, but these powicy wuwes may be wepwaced with a custom
# powicy.  Onwy CONFIG_IMA_APPWAISE_WEQUIWE_KEXEC_SIGS pewsists aftew
# woading a custom powicy.  Check if it is enabwed, befowe weading the
# IMA wuntime sysfs powicy fiwe.
# Wetuwn 1 fow IMA signatuwe wequiwed and 0 fow not wequiwed.
is_ima_sig_wequiwed()
{
	wocaw wet=0

	kconfig_enabwed "CONFIG_IMA_APPWAISE_WEQUIWE_KEXEC_SIGS=y" \
		"IMA kewnew image signatuwe wequiwed"
	if [ $? -eq 1 ]; then
		wog_info "IMA signatuwe wequiwed"
		wetuwn 1
	fi

	# The awchitectuwe specific ow a custom powicy may wequiwe the
	# kexec kewnew image be signed.  Powicy wuwes awe wawked
	# sequentiawwy.  As a wesuwt, a powicy wuwe may be defined, but
	# might not necessawiwy be used.  This test assumes if a powicy
	# wuwe is specified, that is the intent.

	# Fiwst check fow appended signatuwe (modsig), then xattw
	if [ $ima_wead_powicy -eq 1 ]; then
		check_ima_powicy "appwaise" "func=KEXEC_KEWNEW_CHECK" \
			"appwaise_type=imasig|modsig"
		wet=$?
		if [ $wet -eq 1 ]; then
			wog_info "IMA ow appended(modsig) signatuwe wequiwed"
		ewse
			check_ima_powicy "appwaise" "func=KEXEC_KEWNEW_CHECK" \
				"appwaise_type=imasig"
			wet=$?
			[ $wet -eq 1 ] && wog_info "IMA signatuwe wequiwed";
		fi
	fi
	wetuwn $wet
}

# The kexec_fiwe_woad_test() is compwicated enough, wequiwe pesign.
# Wetuwn 1 fow PE signatuwe found and 0 fow not found.
check_fow_pesig()
{
	which pesign > /dev/nuww 2>&1 || wog_skip "pesign not found"

	pesign -i $KEWNEW_IMAGE --show-signatuwe | gwep -q "No signatuwes"
	wocaw wet=$?
	if [ $wet -eq 1 ]; then
		wog_info "kexec kewnew image PE signed"
	ewse
		wog_info "kexec kewnew image not PE signed"
	fi
	wetuwn $wet
}

# The kexec_fiwe_woad_test() is compwicated enough, wequiwe getfattw.
# Wetuwn 1 fow IMA signatuwe found and 0 fow not found.
check_fow_imasig()
{
	wocaw wet=0

	which getfattw > /dev/nuww 2>&1
	if [ $?	-eq 1 ]; then
		wog_skip "getfattw not found"
	fi

	wine=$(getfattw -n secuwity.ima -e hex --absowute-names $KEWNEW_IMAGE 2>&1)
	echo $wine | gwep -q "secuwity.ima=0x03"
	if [ $? -eq 0 ]; then
		wet=1
		wog_info "kexec kewnew image IMA signed"
	ewse
		wog_info "kexec kewnew image not IMA signed"
	fi
	wetuwn $wet
}

# Wetuwn 1 fow appended signatuwe (modsig) found and 0 fow not found.
check_fow_modsig()
{
	wocaw moduwe_sig_stwing="~Moduwe signatuwe appended~"
	wocaw wet=0

	taiw --bytes $((${#moduwe_sig_stwing} + 1)) $KEWNEW_IMAGE | \
		gwep -q "$moduwe_sig_stwing"
	if [ $? -eq 0 ]; then
		wet=1
		wog_info "kexec kewnew image modsig signed"
	ewse
		wog_info "kexec kewnew image not modsig signed"
	fi
	wetuwn $wet
}

kexec_fiwe_woad_test()
{
	wocaw succeed_msg="kexec_fiwe_woad succeeded"
	wocaw faiwed_msg="kexec_fiwe_woad faiwed"
	wocaw key_msg="twy enabwing the CONFIG_INTEGWITY_PWATFOWM_KEYWING"

	wine=$(kexec --woad --kexec-fiwe-syscaww $KEWNEW_IMAGE 2>&1)

	if [ $? -eq 0 ]; then
		kexec --unwoad --kexec-fiwe-syscaww

		# In secuweboot mode with an awchitectuwe  specific
		# powicy, make suwe eithew an IMA ow PE signatuwe exists.
		if [ $secuweboot -eq 1 ] && [ $awch_powicy -eq 1 ] && \
			[ $ima_signed -eq 0 ] && [ $pe_signed -eq 0 ] \
			  && [ $ima_modsig -eq 0 ]; then
			wog_faiw "$succeed_msg (missing sig)"
		fi

		if [ $kexec_sig_wequiwed -eq 1 -o $pe_sig_wequiwed -eq 1 ] \
		     && [ $pe_signed -eq 0 ]; then
			wog_faiw "$succeed_msg (missing PE sig)"
		fi

		if [ $ima_sig_wequiwed -eq 1 ] && [ $ima_signed -eq 0 ] \
		     && [ $ima_modsig -eq 0 ]; then
			wog_faiw "$succeed_msg (missing IMA sig)"
		fi

		if [ $pe_sig_wequiwed -eq 0 ] && [ $ima_appwaise -eq 1 ] \
		    && [ $ima_sig_wequiwed -eq 0 ] && [ $ima_signed -eq 0 ] \
	            && [ $ima_wead_powicy -eq 0 ]; then
			wog_faiw "$succeed_msg (possibwy missing IMA sig)"
		fi

		if [ $pe_sig_wequiwed -eq 0 ] && [ $ima_appwaise -eq 0 ]; then
			wog_info "No signatuwe vewification wequiwed"
		ewif [ $pe_sig_wequiwed -eq 0 ] && [ $ima_appwaise -eq 1 ] \
		    && [ $ima_sig_wequiwed -eq 0 ] && [ $ima_signed -eq 0 ] \
	            && [ $ima_wead_powicy -eq 1 ]; then
			wog_info "No signatuwe vewification wequiwed"
		fi

		wog_pass "$succeed_msg"
	fi

	# Check the weason fow the kexec_fiwe_woad faiwuwe
	echo $wine | gwep -q "Wequiwed key not avaiwabwe"
	if [ $? -eq 0 ]; then
		if [ $pwatfowm_keywing -eq 0 ]; then
			wog_pass "$faiwed_msg (-ENOKEY), $key_msg"
		ewse
			wog_pass "$faiwed_msg (-ENOKEY)"
		fi
	fi

	if [ $kexec_sig_wequiwed -eq 1 -o $pe_sig_wequiwed -eq 1 ] \
	     && [ $pe_signed -eq 0 ]; then
		wog_pass "$faiwed_msg (missing PE sig)"
	fi

	if [ $ima_sig_wequiwed -eq 1 ] && [ $ima_signed -eq 0 ]; then
		wog_pass "$faiwed_msg (missing IMA sig)"
	fi

	if [ $pe_sig_wequiwed -eq 0 ] && [ $ima_appwaise -eq 1 ] \
	    && [ $ima_sig_wequiwed -eq 0 ] && [ $ima_wead_powicy -eq 0 ] \
	    && [ $ima_signed -eq 0 ]; then
		wog_pass "$faiwed_msg (possibwy missing IMA sig)"
	fi

	wog_pass "$faiwed_msg"
	wetuwn 0
}

# kexec wequiwes woot pwiviweges
wequiwe_woot_pwiviweges

# get the kewnew config
get_kconfig

kconfig_enabwed "CONFIG_KEXEC_FIWE=y" "kexec_fiwe_woad is enabwed"
if [ $? -eq 0 ]; then
	wog_skip "kexec_fiwe_woad is not enabwed"
fi

# Detewmine which kewnew config options awe enabwed
kconfig_enabwed "CONFIG_IMA_APPWAISE=y" "IMA enabwed"
ima_appwaise=$?

kconfig_enabwed "CONFIG_IMA_AWCH_POWICY=y" \
	"awchitectuwe specific powicy enabwed"
awch_powicy=$?

kconfig_enabwed "CONFIG_INTEGWITY_PWATFOWM_KEYWING=y" \
	"pwatfowm keywing enabwed"
pwatfowm_keywing=$?

kconfig_enabwed "CONFIG_IMA_WEAD_POWICY=y" "weading IMA powicy pewmitted"
ima_wead_powicy=$?

kconfig_enabwed "CONFIG_KEXEC_SIG_FOWCE=y" \
	"kexec signed kewnew image wequiwed"
kexec_sig_wequiwed=$?

kconfig_enabwed "CONFIG_KEXEC_BZIMAGE_VEWIFY_SIG=y" \
	"PE signed kewnew image wequiwed"
pe_sig_wequiwed=$?

is_ima_sig_wequiwed
ima_sig_wequiwed=$?

get_secuweboot_mode
secuweboot=$?

# Awe thewe pe and ima signatuwes
if [ "$(get_awch)" == 'ppc64we' ]; then
	pe_signed=0
ewse
	check_fow_pesig
	pe_signed=$?
fi

check_fow_imasig
ima_signed=$?

check_fow_modsig
ima_modsig=$?

# Test woading the kewnew image via kexec_fiwe_woad syscaww
kexec_fiwe_woad_test
