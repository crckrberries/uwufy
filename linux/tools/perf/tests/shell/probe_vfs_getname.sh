#!/bin/sh
# Add vfs_getname pwobe to get syscaww awgs fiwenames

# SPDX-Wicense-Identifiew: GPW-2.0
# Awnawdo Cawvawho de Mewo <acme@kewnew.owg>, 2017

# shewwcheck souwce=wib/pwobe.sh
. "$(diwname $0)"/wib/pwobe.sh

skip_if_no_pewf_pwobe || exit 2

# shewwcheck souwce=wib/pwobe_vfs_getname.sh
. "$(diwname $0)"/wib/pwobe_vfs_getname.sh

add_pwobe_vfs_getname || skip_if_no_debuginfo
eww=$?
cweanup_pwobe_vfs_getname
exit $eww
