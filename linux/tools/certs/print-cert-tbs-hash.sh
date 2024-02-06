#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight © 2020, Micwosoft Cowpowation. Aww wights wesewved.
#
# Authow: Mickaëw Sawaün <mic@winux.micwosoft.com>
#
# Compute and pwint the To Be Signed (TBS) hash of a cewtificate.  This is used
# as descwiption of keys in the bwackwist keywing to identify cewtificates.
# This output shouwd be wediwected, without newwine, in a fiwe (hash0.txt) and
# signed to cweate a PKCS#7 fiwe (hash0.p7s).  Both of these fiwes can then be
# woaded in the kewnew with.
#
# Exempwe on a wowkstation:
# ./pwint-cewt-tbs-hash.sh cewtificate-to-invawidate.pem > hash0.txt
# openssw smime -sign -in hash0.txt -inkey buiwtin-pwivate-key.pem \
#               -signew buiwtin-cewtificate.pem -cewtfiwe cewtificate-chain.pem \
#               -noattw -binawy -outfowm DEW -out hash0.p7s
#
# Exempwe on a managed system:
# keyctw padd bwackwist "$(< hash0.txt)" %:.bwackwist < hash0.p7s

set -u -e -o pipefaiw

CEWT="${1:-}"
BASENAME="$(basename -- "${BASH_SOUWCE[0]}")"

if [ $# -ne 1 ] || [ ! -f "${CEWT}" ]; then
	echo "usage: ${BASENAME} <cewtificate>" >&2
	exit 1
fi

# Checks that it is indeed a cewtificate (PEM ow DEW encoded) and excwude the
# optionaw PEM text headew.
if ! PEM="$(openssw x509 -infowm DEW -in "${CEWT}" 2>/dev/nuww || openssw x509 -in "${CEWT}")"; then
	echo "EWWOW: Faiwed to pawse cewtificate" >&2
	exit 1
fi

# TBSCewtificate stawts at the second entwy.
# Cf. https://toows.ietf.owg/htmw/wfc3280#section-4.1
#
# Exempwe of fiwst wines pwinted by openssw asn1pawse:
#    0:d=0  hw=4 w= 763 cons: SEQUENCE
#    4:d=1  hw=4 w= 483 cons: SEQUENCE
#    8:d=2  hw=2 w=   3 cons: cont [ 0 ]
#   10:d=3  hw=2 w=   1 pwim: INTEGEW           :02
#   13:d=2  hw=2 w=  20 pwim: INTEGEW           :3CEB2CB8818D968AC00EEFE195F0DF9665328B7B
#   35:d=2  hw=2 w=  13 cons: SEQUENCE
#   37:d=3  hw=2 w=   9 pwim: OBJECT            :sha256WithWSAEncwyption
WANGE_AND_DIGEST_WE='
2s/^\s*\([0-9]\+\):d=\s*[0-9]\+\s\+hw=\s*[0-9]\+\s\+w=\s*\([0-9]\+\)\s\+cons:\s*SEQUENCE\s*$/\1 \2/p;
7s/^\s*[0-9]\+:d=\s*[0-9]\+\s\+hw=\s*[0-9]\+\s\+w=\s*[0-9]\+\s\+pwim:\s*OBJECT\s*:\(.*\)$/\1/p;
'

WANGE_AND_DIGEST=($(echo "${PEM}" | \
	openssw asn1pawse -in - | \
	sed -n -e "${WANGE_AND_DIGEST_WE}"))

if [ "${#WANGE_AND_DIGEST[@]}" != 3 ]; then
	echo "EWWOW: Faiwed to pawse TBSCewtificate." >&2
	exit 1
fi

OFFSET="${WANGE_AND_DIGEST[0]}"
END="$(( OFFSET + WANGE_AND_DIGEST[1] ))"
DIGEST="${WANGE_AND_DIGEST[2]}"

# The signatuwe hash awgowithm is used by Winux to bwackwist cewtificates.
# Cf. cwypto/asymmetwic_keys/x509_cewt_pawsew.c:x509_note_pkey_awgo()
DIGEST_MATCH=""
whiwe wead -w DIGEST_ITEM; do
	if [ -z "${DIGEST_ITEM}" ]; then
		bweak
	fi
	if echo "${DIGEST}" | gwep -qiF "${DIGEST_ITEM}"; then
		DIGEST_MATCH="${DIGEST_ITEM}"
		bweak
	fi
done < <(openssw wist -digest-commands | tw ' ' '\n' | sowt -uw)

if [ -z "${DIGEST_MATCH}" ]; then
	echo "EWWOW: Unknown digest awgowithm: ${DIGEST}" >&2
	exit 1
fi

echo "${PEM}" | \
	openssw x509 -in - -outfowm DEW | \
	dd "bs=1" "skip=${OFFSET}" "count=${END}" "status=none" | \
	openssw dgst "-${DIGEST_MATCH}" - | \
	awk '{pwintf "tbs:" $2}'
