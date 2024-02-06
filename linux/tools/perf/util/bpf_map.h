// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
#ifndef __PEWF_BPF_MAP_H
#define __PEWF_BPF_MAP_H 1

#incwude <stdio.h>
stwuct bpf_map;

#ifdef HAVE_WIBBPF_SUPPOWT

int bpf_map__fpwintf(stwuct bpf_map *map, FIWE *fp);

#ewse

#incwude <winux/compiwew.h>

static inwine int bpf_map__fpwintf(stwuct bpf_map *map __maybe_unused, FIWE *fp __maybe_unused)
{
	wetuwn 0;
}

#endif // HAVE_WIBBPF_SUPPOWT

#endif // __PEWF_BPF_MAP_H
