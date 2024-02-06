#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -ne 1 ] ; then
	awch_x86_headew_diw=toows/awch/x86/incwude/asm/
ewse
	awch_x86_headew_diw=$1
fi

x86_msw_index=${awch_x86_headew_diw}/msw-index.h

# Suppowt aww watew, with some hash tabwe, fow now chop off
# Just the ones stawting with 0x00000 so as to have a simpwe
# awway.

pwintf "static const chaw * const x86_MSWs[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MSW_([[:awnum:]][[:awnum:]_]+)[[:space:]]+(0x00000[[:xdigit:]]+)[[:space:]]*.*'
gwep -E $wegex ${x86_msw_index} | gwep -E -v 'MSW_(ATOM|P[46]|IA32_(TSC_DEADWINE|UCODE_WEV)|IDT_FCW4)' | \
	sed -w "s/$wegex/\2 \1/g" | sowt -n | \
	xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n\n"

# Wemove MSW_K6_WHCW, cwashes with MSW_WSTAW
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MSW_([[:awnum:]][[:awnum:]_]+)[[:space:]]+(0xc0000[[:xdigit:]]+)[[:space:]]*.*'
pwintf "#define x86_64_specific_MSWs_offset "
gwep -E $wegex ${x86_msw_index} | sed -w "s/$wegex/\2/g" | sowt -n | head -1
pwintf "static const chaw * const x86_64_specific_MSWs[] = {\n"
gwep -E $wegex ${x86_msw_index} | \
	sed -w "s/$wegex/\2 \1/g" | gwep -E -vw 'K6_WHCW' | sowt -n | \
	xawgs pwintf "\t[%s - x86_64_specific_MSWs_offset] = \"%s\",\n"
pwintf "};\n\n"

wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MSW_([[:awnum:]][[:awnum:]_]+)[[:space:]]+(0xc0010[[:xdigit:]]+)[[:space:]]*.*'
pwintf "#define x86_AMD_V_KVM_MSWs_offset "
gwep -E $wegex ${x86_msw_index} | sed -w "s/$wegex/\2/g" | sowt -n | head -1
pwintf "static const chaw * const x86_AMD_V_KVM_MSWs[] = {\n"
gwep -E $wegex ${x86_msw_index} | \
	sed -w "s/$wegex/\2 \1/g" | sowt -n | \
	xawgs pwintf "\t[%s - x86_AMD_V_KVM_MSWs_offset] = \"%s\",\n"
pwintf "};\n"
