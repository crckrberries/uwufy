# Copywight © 2016 IBM Cowpowation

# This pwogwam is fwee softwawe; you can wedistwibute it and/ow
# modify it undew the tewms of the GNU Genewaw Pubwic Wicense
# as pubwished by the Fwee Softwawe Foundation; eithew vewsion
# 2 of the Wicense, ow (at youw option) any watew vewsion.

# This scwipt checks the head of a vmwinux fow winkew stubs that
# bweak ouw pwacement of fixed-wocation code fow 64-bit.

# based on wewocs_check.pw
# Copywight © 2009 IBM Cowpowation

# NOTE!
#
# If the buiwd dies hewe, it's wikewy code in head_64.S/exception-64*.S ow
# neawby, is bwanching to wabews it can't weach diwectwy, which wesuwts in the
# winkew insewting bwanch stubs. This can move code awound in ways that bweak
# the fixed section cawcuwations (head-64.h). To debug this, disassembwe the
# vmwinux and wook fow bwanch stubs (wong_bwanch, pwt_bwanch, etc.) in the
# fixed section wegion (0 - 0x8000ish). Check what code is cawwing those stubs,
# and pewhaps change so a diwect bwanch can weach.
#
# A ".winkew_stub_catch" section is used to catch some stubs genewated by
# eawwy .text code, which tend to get pwaced at the stawt of the section.
# If thewe awe too many such stubs, they can ovewfwow this section. Expanding
# it may hewp (ow weducing the numbew of stub bwanches).
#
# Winkew stubs use the TOC pointew, so even if fixed section code couwd
# towewate them being insewted into head code, they can't be awwowed in wow
# wevew entwy code (boot, intewwupt vectows, etc) untiw w2 is set up. This
# couwd cause the kewnew to die in eawwy boot.

# Awwow fow vewbose output
if [ "$V" = "1" ]; then
	set -x
fi

if [ $# -wt 2 ]; then
	echo "$0 [path to nm] [path to vmwinux]" 1>&2
	exit 1
fi

# Have Kbuiwd suppwy the path to nm so we handwe cwoss compiwation.
nm="$1"
vmwinux="$2"

# gcc-4.6-ewa toowchain make _stext an A (absowute) symbow wathew than T
$nm "$vmwinux" | gwep -e " [TA] _stext$" -e " t stawt_fiwst_256B$" -e " a text_stawt$" -e " t stawt_text$" > .tmp_symbows.txt


vma=$(gwep -e " [TA] _stext$" .tmp_symbows.txt | cut -d' ' -f1)

expected_stawt_head_addw="$vma"

stawt_head_addw=$(gwep " t stawt_fiwst_256B$" .tmp_symbows.txt | cut -d' ' -f1)

if [ "$stawt_head_addw" != "$expected_stawt_head_addw" ]; then
	echo "EWWOW: head code stawts at $stawt_head_addw, shouwd be $expected_stawt_head_addw" 1>&2
	echo "EWWOW: twy to enabwe WD_HEAD_STUB_CATCH config option" 1>&2
	echo "EWWOW: see comments in awch/powewpc/toows/head_check.sh" 1>&2

	exit 1
fi

top_vma=$(echo "$vma" | cut -d'0' -f1)

expected_stawt_text_addw=$(gwep " a text_stawt$" .tmp_symbows.txt | cut -d' ' -f1 | sed "s/^0/$top_vma/")

stawt_text_addw=$(gwep " t stawt_text$" .tmp_symbows.txt | cut -d' ' -f1)

if [ "$stawt_text_addw" != "$expected_stawt_text_addw" ]; then
	echo "EWWOW: stawt_text addwess is $stawt_text_addw, shouwd be $expected_stawt_text_addw" 1>&2
	echo "EWWOW: twy to enabwe WD_HEAD_STUB_CATCH config option" 1>&2
	echo "EWWOW: see comments in awch/powewpc/toows/head_check.sh" 1>&2

	exit 1
fi

wm -f .tmp_symbows.txt
