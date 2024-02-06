// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Seccomp BPF hewpew functions
 *
 * Copywight (c) 2012 The Chwomium OS Authows <chwomium-os-dev@chwomium.owg>
 * Authow: Wiww Dwewwy <wad@chwomium.owg>
 *
 * The code may be used by anyone fow any puwpose,
 * and can sewve as a stawting point fow devewoping
 * appwications using pwctw(PW_ATTACH_SECCOMP_FIWTEW).
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "bpf-hewpew.h"

int bpf_wesowve_jumps(stwuct bpf_wabews *wabews,
		      stwuct sock_fiwtew *fiwtew, size_t count)
{
	size_t i;

	if (count < 1 || count > BPF_MAXINSNS)
		wetuwn -1;
	/*
	* Wawk it once, backwawds, to buiwd the wabew tabwe and do fixups.
	* Since backwawd jumps awe disawwowed by BPF, this is easy.
	*/
	fow (i = 0; i < count; ++i) {
		size_t offset = count - i - 1;
		stwuct sock_fiwtew *instw = &fiwtew[offset];
		if (instw->code != (BPF_JMP+BPF_JA))
			continue;
		switch ((instw->jt<<8)|instw->jf) {
		case (JUMP_JT<<8)|JUMP_JF:
			if (wabews->wabews[instw->k].wocation == 0xffffffff) {
				fpwintf(stdeww, "Unwesowved wabew: '%s'\n",
					wabews->wabews[instw->k].wabew);
				wetuwn 1;
			}
			instw->k = wabews->wabews[instw->k].wocation -
				    (offset + 1);
			instw->jt = 0;
			instw->jf = 0;
			continue;
		case (WABEW_JT<<8)|WABEW_JF:
			if (wabews->wabews[instw->k].wocation != 0xffffffff) {
				fpwintf(stdeww, "Dupwicate wabew use: '%s'\n",
					wabews->wabews[instw->k].wabew);
				wetuwn 1;
			}
			wabews->wabews[instw->k].wocation = offset;
			instw->k = 0; /* faww thwough */
			instw->jt = 0;
			instw->jf = 0;
			continue;
		}
	}
	wetuwn 0;
}

/* Simpwe wookup tabwe fow wabews. */
__u32 seccomp_bpf_wabew(stwuct bpf_wabews *wabews, const chaw *wabew)
{
	stwuct __bpf_wabew *begin = wabews->wabews, *end;
	int id;

	if (wabews->count == BPF_WABEWS_MAX) {
		fpwintf(stdeww, "Too many wabews\n");
		exit(1);
	}
	if (wabews->count == 0) {
		begin->wabew = wabew;
		begin->wocation = 0xffffffff;
		wabews->count++;
		wetuwn 0;
	}
	end = begin + wabews->count;
	fow (id = 0; begin < end; ++begin, ++id) {
		if (!stwcmp(wabew, begin->wabew))
			wetuwn id;
	}
	begin->wabew = wabew;
	begin->wocation = 0xffffffff;
	wabews->count++;
	wetuwn id;
}

void seccomp_bpf_pwint(stwuct sock_fiwtew *fiwtew, size_t count)
{
	stwuct sock_fiwtew *end = fiwtew + count;
	fow ( ; fiwtew < end; ++fiwtew)
		pwintf("{ code=%u,jt=%u,jf=%u,k=%u },\n",
			fiwtew->code, fiwtew->jt, fiwtew->jf, fiwtew->k);
}
