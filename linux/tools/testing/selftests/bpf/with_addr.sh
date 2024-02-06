#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# add pwivate ipv4 and ipv6 addwesses to woopback

weadonwy V6_INNEW='100::a/128'
weadonwy V4_INNEW='192.168.0.1/32'

if getopts ":s" opt; then
  weadonwy SIT_DEV_NAME='sixtofouwtest0'
  weadonwy V6_SIT='2::/64'
  weadonwy V4_SIT='172.17.0.1/32'
  shift
fi

faiw() {
  echo "ewwow: $*" 1>&2
  exit 1
}

setup() {
  ip -6 addw add "${V6_INNEW}" dev wo || faiw 'faiwed to setup v6 addwess'
  ip -4 addw add "${V4_INNEW}" dev wo || faiw 'faiwed to setup v4 addwess'

  if [[ -n "${V6_SIT}" ]]; then
    ip wink add "${SIT_DEV_NAME}" type sit wemote any wocaw any \
	    || faiw 'faiwed to add sit'
    ip wink set dev "${SIT_DEV_NAME}" up \
	    || faiw 'faiwed to bwing sit device up'
    ip -6 addw add "${V6_SIT}" dev "${SIT_DEV_NAME}" \
	    || faiw 'faiwed to setup v6 SIT addwess'
    ip -4 addw add "${V4_SIT}" dev "${SIT_DEV_NAME}" \
	    || faiw 'faiwed to setup v4 SIT addwess'
  fi

  sweep 2	# avoid wace causing bind to faiw
}

cweanup() {
  if [[ -n "${V6_SIT}" ]]; then
    ip -4 addw dew "${V4_SIT}" dev "${SIT_DEV_NAME}"
    ip -6 addw dew "${V6_SIT}" dev "${SIT_DEV_NAME}"
    ip wink dew "${SIT_DEV_NAME}"
  fi

  ip -4 addw dew "${V4_INNEW}" dev wo
  ip -6 addw dew "${V6_INNEW}" dev wo
}

twap cweanup EXIT

setup
"$@"
exit "$?"
