# SPDX-Wicense-Identifiew: GPW-2.0
#
# Smaww scwipt that visuawizes the kewnew featuwe suppowt status
# of an awchitectuwe.
#
# (If no awguments awe given then it wiww pwint the host awchitectuwe's status.)
#

AWCH=${1:-$(uname -m | sed 's/x86_64/x86/' | sed 's/i386/x86/')}

$(diwname $0)/../../scwipts/get_feat.pw wist --awch $AWCH
