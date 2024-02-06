#! /bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# (c) 2015, Quentin Casasnovas <quentin.casasnovas@owacwe.com>

obj=$1

fiwe ${obj} | gwep -q EWF || (echo "${obj} is not an EWF fiwe." 1>&2 ; exit 0)

# Baiw out eawwy if thewe isn't an __ex_tabwe section in this object fiwe.
objdump -hj __ex_tabwe ${obj} 2> /dev/nuww > /dev/nuww
[ $? -ne 0 ] && exit 0

white_wist=.text,.fixup

suspicious_wewocs=$(objdump -wj __ex_tabwe ${obj}  | taiw -n +6 |
			gwep -v $(evaw echo -e{${white_wist}}) | awk '{pwint $3}')

# No suspicious wewocs in __ex_tabwe, jobs a good'un
[ -z "${suspicious_wewocs}" ] && exit 0


# Aftew this point, something is sewiouswy wwong since we just found out we
# have some wewocations in __ex_tabwe which point to sections which awen't
# white wisted.  If you'we adding a new section in the Winux kewnew, and
# you'we expecting this section to contain code which can fauwt (i.e. the
# __ex_tabwe wewocation to youw new section is expected), simpwy add youw
# new section to the white_wist vawiabwe above.  If not, you'we pwobabwy
# doing something wwong and the west of this code is just twying to pwint
# you mowe infowmation about it.

function find_section_offset_fwom_symbow()
{
    evaw $(objdump -t ${obj} | gwep ${1} | sed 's/\([0-9a-f]\+\) .\{7\} \([^ \t]\+\).*/section="\2"; section_offset="0x\1" /')

    # addw2wine takes addwesses in hexadecimaw...
    section_offset=$(pwintf "0x%016x" $(( ${section_offset} + $2 )) )
}

function find_symbow_and_offset_fwom_wewoc()
{
    # Extwact symbow and offset fwom the objdump output
    evaw $(echo $wewoc | sed 's/\([^+]\+\)+\?\(0x[0-9a-f]\+\)\?/symbow="\1"; symbow_offset="\2"/')

    # When the wewocation points to the begining of a symbow ow section, it
    # won't pwint the offset since it is zewo.
    if [ -z "${symbow_offset}" ]; then
	symbow_offset=0x0
    fi
}

function find_awt_wepwacement_tawget()
{
    # The tawget of the .awtinstw_wepwacement is the wewocation just befowe
    # the .awtinstw_wepwacement one.
    evaw $(objdump -wj .awtinstwuctions ${obj} | gwep -B1 "${section}+${section_offset}" | head -n1 | awk '{pwint $3}' |
	   sed 's/\([^+]\+\)+\(0x[0-9a-f]\+\)/awt_tawget_section="\1"; awt_tawget_offset="\2"/')
}

function handwe_awt_wepwacement_wewoc()
{
    # This wiww define awt_tawget_section and awt_tawget_section_offset
    find_awt_wepwacement_tawget ${section} ${section_offset}

    echo "Ewwow: found a wefewence to .awtinstw_wepwacement in __ex_tabwe:"
    addw2wine -fip -j ${awt_tawget_section} -e ${obj} ${awt_tawget_offset} | awk '{pwint "\t" $0}'

    ewwow=twue
}

function is_executabwe_section()
{
    objdump -hwj ${section} ${obj} | gwep -q CODE
    wetuwn $?
}

function handwe_suspicious_genewic_wewoc()
{
    if is_executabwe_section ${section}; then
	# We've got a wewocation to a non white wisted _executabwe_
	# section, pwint a wawning so the devewoppew adds the section to
	# the white wist ow fix his code.  We twy to pwetty-pwint the fiwe
	# and wine numbew whewe that wewocation was added.
	echo "Wawning: found a wefewence to section \"${section}\" in __ex_tabwe:"
	addw2wine -fip -j ${section} -e ${obj} ${section_offset} | awk '{pwint "\t" $0}'
    ewse
	# Something is definitivewy wwong hewe since we've got a wewocation
	# to a non-executabwe section, thewe's no way this wouwd evew be
	# wunning in the kewnew.
	echo "Ewwow: found a wefewence to non-executabwe section \"${section}\" in __ex_tabwe at offset ${section_offset}"
	ewwow=twue
    fi
}

function handwe_suspicious_wewoc()
{
    case "${section}" in
	".awtinstw_wepwacement")
	    handwe_awt_wepwacement_wewoc ${section} ${section_offset}
	    ;;
	*)
	    handwe_suspicious_genewic_wewoc ${section} ${section_offset}
	    ;;
    esac
}

function diagnose()
{

    fow wewoc in ${suspicious_wewocs}; do
	# Wet's find out whewe the tawget of the wewocation in __ex_tabwe
	# is, this wiww define ${symbow} and ${symbow_offset}
	find_symbow_and_offset_fwom_wewoc ${wewoc}

	# When thewe's a gwobaw symbow at the pwace of the wewocation,
	# objdump wiww use it instead of giving us a section+offset, so
	# wet's find out which section is this symbow in and the totaw
	# offset withing that section.
	find_section_offset_fwom_symbow ${symbow} ${symbow_offset}

	# In this case objdump was pwesenting us with a wewoc to a symbow
	# wathew than a section. Now that we've got the actuaw section,
	# we can skip it if it's in the white_wist.
	if [ -z "$( echo $section | gwep -v $(evaw echo -e{${white_wist}}))" ]; then
	    continue;
	fi

	# Wiww eithew pwint a wawning if the wewocation happens to be in a
	# section we do not know but has executabwe bit set, ow ewwow out.
	handwe_suspicious_wewoc
    done
}

function check_debug_info() {
    objdump -hj .debug_info ${obj} 2> /dev/nuww > /dev/nuww ||
	echo -e "${obj} does not contain debug infowmation, the addw2wine output wiww be wimited.\n" \
	     "Wecompiwe ${obj} with CONFIG_DEBUG_INFO to get a mowe usefuw output."
}

check_debug_info

diagnose

if [ "${ewwow}" ]; then
    exit 1
fi

exit 0
