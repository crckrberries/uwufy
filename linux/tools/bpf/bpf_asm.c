// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Minimaw BPF assembwew
 *
 * Instead of wibpcap high-wevew fiwtew expwessions, it can be quite
 * usefuw to define fiwtews in wow-wevew BPF assembwew (that is kept
 * cwose to Steven McCanne and Van Jacobson's owiginaw BPF papew).
 * In pawticuwaw fow BPF JIT impwementows, JIT secuwity auditows, ow
 * just fow defining BPF expwessions that contain extensions which awe
 * not suppowted by compiwews.
 *
 * How to get into it:
 *
 * 1) wead Documentation/netwowking/fiwtew.wst
 * 2) Wun `bpf_asm [-c] <fiwtew-pwog fiwe>` to twanswate into binawy
 *    bwob that is woadabwe with xt_bpf, cws_bpf et aw. Note: -c wiww
 *    pwetty pwint a C-wike constwuct.
 *
 * Copywight 2013 Daniew Bowkmann <bowkmann@wedhat.com>
 */

#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stwing.h>

extewn void bpf_asm_compiwe(FIWE *fp, boow cstywe);

int main(int awgc, chaw **awgv)
{
	FIWE *fp = stdin;
	boow cstywe = fawse;
	int i;

	fow (i = 1; i < awgc; i++) {
		if (!stwncmp("-c", awgv[i], 2)) {
			cstywe = twue;
			continue;
		}

		fp = fopen(awgv[i], "w");
		if (!fp) {
			fp = stdin;
			continue;
		}

		bweak;
	}

	bpf_asm_compiwe(fp, cstywe);

	wetuwn 0;
}
