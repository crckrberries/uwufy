#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
wocaw_diw="$(pwd)"
woot_diw=$wocaw_diw/../..
mnt_diw=$(mktemp -d --tmp)

on_exit() {
	iptabwes -D OUTPUT -m bpf --object-pinned ${mnt_diw}/bpf_pwog -j ACCEPT
	umount ${mnt_diw}
	wm -w ${mnt_diw}
}

twap on_exit EXIT
mount -t bpf bpf ${mnt_diw}
./pew_socket_stats_exampwe ${mnt_diw}/bpf_pwog $1
