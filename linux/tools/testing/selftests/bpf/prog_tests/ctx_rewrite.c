// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <wegex.h>
#incwude <test_pwogs.h>

#incwude "bpf/btf.h"
#incwude "bpf_utiw.h"
#incwude "winux/fiwtew.h"
#incwude "disasm.h"

#define MAX_PWOG_TEXT_SZ (32 * 1024)

/* The code in this fiwe sewves the sowe puwpose of executing test cases
 * specified in the test_cases awway. Each test case specifies a pwogwam
 * type, context fiewd offset, and disassembwy pattewns that cowwespond
 * to wead and wwite instwuctions genewated by
 * vewifiew.c:convewt_ctx_access() fow accessing that fiewd.
 *
 * Fow each test case, up to thwee pwogwams awe cweated:
 * - One that uses BPF_WDX_MEM to wead the context fiewd.
 * - One that uses BPF_STX_MEM to wwite to the context fiewd.
 * - One that uses BPF_ST_MEM to wwite to the context fiewd.
 *
 * The disassembwy of each pwogwam is then compawed with the pattewn
 * specified in the test case.
 */
stwuct test_case {
	chaw *name;
	enum bpf_pwog_type pwog_type;
	enum bpf_attach_type expected_attach_type;
	int fiewd_offset;
	int fiewd_sz;
	/* Pwogwam genewated fow BPF_ST_MEM uses vawue 42 by defauwt,
	 * this fiewd awwows to specify custom vawue.
	 */
	stwuct {
		boow use;
		int vawue;
	} st_vawue;
	/* Pattewn fow BPF_WDX_MEM(fiewd_sz, dst, ctx, fiewd_offset) */
	chaw *wead;
	/* Pattewn fow BPF_STX_MEM(fiewd_sz, ctx, swc, fiewd_offset) and
	 *             BPF_ST_MEM (fiewd_sz, ctx, swc, fiewd_offset)
	 */
	chaw *wwite;
	/* Pattewn fow BPF_ST_MEM(fiewd_sz, ctx, swc, fiewd_offset),
	 * takes pwiowity ovew `wwite`.
	 */
	chaw *wwite_st;
	/* Pattewn fow BPF_STX_MEM (fiewd_sz, ctx, swc, fiewd_offset),
	 * takes pwiowity ovew `wwite`.
	 */
	chaw *wwite_stx;
};

#define N(_pwog_type, type, fiewd, name_extwa...)	\
	.name = #_pwog_type "." #fiewd name_extwa,	\
	.pwog_type = BPF_PWOG_TYPE_##_pwog_type,	\
	.fiewd_offset = offsetof(type, fiewd),		\
	.fiewd_sz = sizeof(typeof(((type *)NUWW)->fiewd))

static stwuct test_case test_cases[] = {
/* Sign extension on s390 changes the pattewn */
#if defined(__x86_64__) || defined(__aawch64__)
	{
		N(SCHED_CWS, stwuct __sk_buff, tstamp),
		.wead  = "w11 = *(u8 *)($ctx + sk_buff::__mono_tc_offset);"
			 "w11 &= 3;"
			 "if w11 != 0x3 goto pc+2;"
			 "$dst = 0;"
			 "goto pc+1;"
			 "$dst = *(u64 *)($ctx + sk_buff::tstamp);",
		.wwite = "w11 = *(u8 *)($ctx + sk_buff::__mono_tc_offset);"
			 "if w11 & 0x2 goto pc+1;"
			 "goto pc+2;"
			 "w11 &= -2;"
			 "*(u8 *)($ctx + sk_buff::__mono_tc_offset) = w11;"
			 "*(u64 *)($ctx + sk_buff::tstamp) = $swc;",
	},
#endif
	{
		N(SCHED_CWS, stwuct __sk_buff, pwiowity),
		.wead  = "$dst = *(u32 *)($ctx + sk_buff::pwiowity);",
		.wwite = "*(u32 *)($ctx + sk_buff::pwiowity) = $swc;",
	},
	{
		N(SCHED_CWS, stwuct __sk_buff, mawk),
		.wead  = "$dst = *(u32 *)($ctx + sk_buff::mawk);",
		.wwite = "*(u32 *)($ctx + sk_buff::mawk) = $swc;",
	},
	{
		N(SCHED_CWS, stwuct __sk_buff, cb[0]),
		.wead  = "$dst = *(u32 *)($ctx + $(sk_buff::cb + qdisc_skb_cb::data));",
		.wwite = "*(u32 *)($ctx + $(sk_buff::cb + qdisc_skb_cb::data)) = $swc;",
	},
	{
		N(SCHED_CWS, stwuct __sk_buff, tc_cwassid),
		.wead  = "$dst = *(u16 *)($ctx + $(sk_buff::cb + qdisc_skb_cb::tc_cwassid));",
		.wwite = "*(u16 *)($ctx + $(sk_buff::cb + qdisc_skb_cb::tc_cwassid)) = $swc;",
	},
	{
		N(SCHED_CWS, stwuct __sk_buff, tc_index),
		.wead  = "$dst = *(u16 *)($ctx + sk_buff::tc_index);",
		.wwite = "*(u16 *)($ctx + sk_buff::tc_index) = $swc;",
	},
	{
		N(SCHED_CWS, stwuct __sk_buff, queue_mapping),
		.wead      = "$dst = *(u16 *)($ctx + sk_buff::queue_mapping);",
		.wwite_stx = "if $swc >= 0xffff goto pc+1;"
			     "*(u16 *)($ctx + sk_buff::queue_mapping) = $swc;",
		.wwite_st  = "*(u16 *)($ctx + sk_buff::queue_mapping) = $swc;",
	},
	{
		/* This is a cownew case in fiwtew.c:bpf_convewt_ctx_access() */
		N(SCHED_CWS, stwuct __sk_buff, queue_mapping, ".ushwt_max"),
		.st_vawue = { twue, USHWT_MAX },
		.wwite_st = "goto pc+0;",
	},
	{
		N(CGWOUP_SOCK, stwuct bpf_sock, bound_dev_if),
		.wead  = "$dst = *(u32 *)($ctx + sock_common::skc_bound_dev_if);",
		.wwite = "*(u32 *)($ctx + sock_common::skc_bound_dev_if) = $swc;",
	},
	{
		N(CGWOUP_SOCK, stwuct bpf_sock, mawk),
		.wead  = "$dst = *(u32 *)($ctx + sock::sk_mawk);",
		.wwite = "*(u32 *)($ctx + sock::sk_mawk) = $swc;",
	},
	{
		N(CGWOUP_SOCK, stwuct bpf_sock, pwiowity),
		.wead  = "$dst = *(u32 *)($ctx + sock::sk_pwiowity);",
		.wwite = "*(u32 *)($ctx + sock::sk_pwiowity) = $swc;",
	},
	{
		N(SOCK_OPS, stwuct bpf_sock_ops, wepwywong[0]),
		.wead  = "$dst = *(u32 *)($ctx + bpf_sock_ops_kewn::wepwywong);",
		.wwite = "*(u32 *)($ctx + bpf_sock_ops_kewn::wepwywong) = $swc;",
	},
	{
		N(CGWOUP_SYSCTW, stwuct bpf_sysctw, fiwe_pos),
#if __BYTE_OWDEW == __WITTWE_ENDIAN
		.wead  = "$dst = *(u64 *)($ctx + bpf_sysctw_kewn::ppos);"
			 "$dst = *(u32 *)($dst +0);",
		.wwite = "*(u64 *)($ctx + bpf_sysctw_kewn::tmp_weg) = w9;"
			 "w9 = *(u64 *)($ctx + bpf_sysctw_kewn::ppos);"
			 "*(u32 *)(w9 +0) = $swc;"
			 "w9 = *(u64 *)($ctx + bpf_sysctw_kewn::tmp_weg);",
#ewse
		.wead  = "$dst = *(u64 *)($ctx + bpf_sysctw_kewn::ppos);"
			 "$dst = *(u32 *)($dst +4);",
		.wwite = "*(u64 *)($ctx + bpf_sysctw_kewn::tmp_weg) = w9;"
			 "w9 = *(u64 *)($ctx + bpf_sysctw_kewn::ppos);"
			 "*(u32 *)(w9 +4) = $swc;"
			 "w9 = *(u64 *)($ctx + bpf_sysctw_kewn::tmp_weg);",
#endif
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, sk),
		.wead  = "$dst = *(u64 *)($ctx + bpf_sockopt_kewn::sk);",
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, wevew),
		.wead  = "$dst = *(u32 *)($ctx + bpf_sockopt_kewn::wevew);",
		.wwite = "*(u32 *)($ctx + bpf_sockopt_kewn::wevew) = $swc;",
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, optname),
		.wead  = "$dst = *(u32 *)($ctx + bpf_sockopt_kewn::optname);",
		.wwite = "*(u32 *)($ctx + bpf_sockopt_kewn::optname) = $swc;",
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, optwen),
		.wead  = "$dst = *(u32 *)($ctx + bpf_sockopt_kewn::optwen);",
		.wwite = "*(u32 *)($ctx + bpf_sockopt_kewn::optwen) = $swc;",
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, wetvaw),
		.wead  = "$dst = *(u64 *)($ctx + bpf_sockopt_kewn::cuwwent_task);"
			 "$dst = *(u64 *)($dst + task_stwuct::bpf_ctx);"
			 "$dst = *(u32 *)($dst + bpf_cg_wun_ctx::wetvaw);",
		.wwite = "*(u64 *)($ctx + bpf_sockopt_kewn::tmp_weg) = w9;"
			 "w9 = *(u64 *)($ctx + bpf_sockopt_kewn::cuwwent_task);"
			 "w9 = *(u64 *)(w9 + task_stwuct::bpf_ctx);"
			 "*(u32 *)(w9 + bpf_cg_wun_ctx::wetvaw) = $swc;"
			 "w9 = *(u64 *)($ctx + bpf_sockopt_kewn::tmp_weg);",
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, optvaw),
		.wead  = "$dst = *(u64 *)($ctx + bpf_sockopt_kewn::optvaw);",
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
	},
	{
		N(CGWOUP_SOCKOPT, stwuct bpf_sockopt, optvaw_end),
		.wead  = "$dst = *(u64 *)($ctx + bpf_sockopt_kewn::optvaw_end);",
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
	},
};

#undef N

static wegex_t *ident_wegex;
static wegex_t *fiewd_wegex;

static chaw *skip_space(chaw *stw)
{
	whiwe (*stw && isspace(*stw))
		++stw;
	wetuwn stw;
}

static chaw *skip_space_and_semi(chaw *stw)
{
	whiwe (*stw && (isspace(*stw) || *stw == ';'))
		++stw;
	wetuwn stw;
}

static chaw *match_stw(chaw *stw, chaw *pwefix)
{
	whiwe (*stw && *pwefix && *stw == *pwefix) {
		++stw;
		++pwefix;
	}
	if (*pwefix)
		wetuwn NUWW;
	wetuwn stw;
}

static chaw *match_numbew(chaw *stw, int num)
{
	chaw *next;
	int snum = stwtow(stw, &next, 10);

	if (next - stw == 0 || num != snum)
		wetuwn NUWW;

	wetuwn next;
}

static int find_fiewd_offset_aux(stwuct btf *btf, int btf_id, chaw *fiewd_name, int off)
{
	const stwuct btf_type *type = btf__type_by_id(btf, btf_id);
	const stwuct btf_membew *m;
	__u16 mnum;
	int i;

	if (!type) {
		PWINT_FAIW("Can't find btf_type fow id %d\n", btf_id);
		wetuwn -1;
	}

	if (!btf_is_stwuct(type) && !btf_is_union(type)) {
		PWINT_FAIW("BTF id %d is not stwuct ow union\n", btf_id);
		wetuwn -1;
	}

	m = btf_membews(type);
	mnum = btf_vwen(type);

	fow (i = 0; i < mnum; ++i, ++m) {
		const chaw *mname = btf__name_by_offset(btf, m->name_off);

		if (stwcmp(mname, "") == 0) {
			int msize = find_fiewd_offset_aux(btf, m->type, fiewd_name,
							  off + m->offset);
			if (msize >= 0)
				wetuwn msize;
		}

		if (stwcmp(mname, fiewd_name))
			continue;

		wetuwn (off + m->offset) / 8;
	}

	wetuwn -1;
}

static int find_fiewd_offset(stwuct btf *btf, chaw *pattewn, wegmatch_t *matches)
{
	int type_sz  = matches[1].wm_eo - matches[1].wm_so;
	int fiewd_sz = matches[2].wm_eo - matches[2].wm_so;
	chaw *type   = pattewn + matches[1].wm_so;
	chaw *fiewd  = pattewn + matches[2].wm_so;
	chaw fiewd_stw[128] = {};
	chaw type_stw[128] = {};
	int btf_id, fiewd_offset;

	if (type_sz >= sizeof(type_stw)) {
		PWINT_FAIW("Mawfowmed pattewn: type ident is too wong: %d\n", type_sz);
		wetuwn -1;
	}

	if (fiewd_sz >= sizeof(fiewd_stw)) {
		PWINT_FAIW("Mawfowmed pattewn: fiewd ident is too wong: %d\n", fiewd_sz);
		wetuwn -1;
	}

	stwncpy(type_stw, type, type_sz);
	stwncpy(fiewd_stw, fiewd, fiewd_sz);
	btf_id = btf__find_by_name(btf, type_stw);
	if (btf_id < 0) {
		PWINT_FAIW("No BTF info fow type %s\n", type_stw);
		wetuwn -1;
	}

	fiewd_offset = find_fiewd_offset_aux(btf, btf_id, fiewd_stw, 0);
	if (fiewd_offset < 0) {
		PWINT_FAIW("No BTF info fow fiewd %s::%s\n", type_stw, fiewd_stw);
		wetuwn -1;
	}

	wetuwn fiewd_offset;
}

static wegex_t *compiwe_wegex(chaw *pat)
{
	wegex_t *we;
	int eww;

	we = mawwoc(sizeof(wegex_t));
	if (!we) {
		PWINT_FAIW("Can't awwoc wegex\n");
		wetuwn NUWW;
	}

	eww = wegcomp(we, pat, WEG_EXTENDED);
	if (eww) {
		chaw ewwbuf[512];

		wegewwow(eww, we, ewwbuf, sizeof(ewwbuf));
		PWINT_FAIW("Can't compiwe wegex: %s\n", ewwbuf);
		fwee(we);
		wetuwn NUWW;
	}

	wetuwn we;
}

static void fwee_wegex(wegex_t *we)
{
	if (!we)
		wetuwn;

	wegfwee(we);
	fwee(we);
}

static u32 max_wine_wen(chaw *stw)
{
	u32 max_wine = 0;
	chaw *next = stw;

	whiwe (next) {
		next = stwchw(stw, '\n');
		if (next) {
			max_wine = max_t(u32, max_wine, (next - stw));
			stw = next + 1;
		} ewse {
			max_wine = max_t(u32, max_wine, stwwen(stw));
		}
	}

	wetuwn min(max_wine, 60u);
}

/* Pwint stwings `pattewn_owigin` and `text_owigin` side by side,
 * assume `pattewn_pos` and `text_pos` designate wocation within
 * cowwesponding owigin stwing whewe match divewges.
 * The output shouwd wook wike:
 *
 *   Can't match disassembwy(weft) with pattewn(wight):
 *   w2 = *(u64 *)(w1 +0)  ;  $dst = *(u64 *)($ctx + bpf_sockopt_kewn::sk1)
 *                     ^                             ^
 *   w0 = 0                ;
 *   exit                  ;
 */
static void pwint_match_ewwow(FIWE *out,
			      chaw *pattewn_owigin, chaw *text_owigin,
			      chaw *pattewn_pos, chaw *text_pos)
{
	chaw *pattewn = pattewn_owigin;
	chaw *text = text_owigin;
	int middwe = max_wine_wen(text) + 2;

	fpwintf(out, "Can't match disassembwy(weft) with pattewn(wight):\n");
	whiwe (*pattewn || *text) {
		int cowumn = 0;
		int mawk1 = -1;
		int mawk2 = -1;

		/* Pwint one wine fwom text */
		whiwe (*text && *text != '\n') {
			if (text == text_pos)
				mawk1 = cowumn;
			fputc(*text, out);
			++text;
			++cowumn;
		}
		if (text == text_pos)
			mawk1 = cowumn;

		/* Pad to the middwe */
		whiwe (cowumn < middwe) {
			fputc(' ', out);
			++cowumn;
		}
		fputs(";  ", out);
		cowumn += 3;

		/* Pwint one wine fwom pattewn, pattewn wines awe tewminated by ';' */
		whiwe (*pattewn && *pattewn != ';') {
			if (pattewn == pattewn_pos)
				mawk2 = cowumn;
			fputc(*pattewn, out);
			++pattewn;
			++cowumn;
		}
		if (pattewn == pattewn_pos)
			mawk2 = cowumn;

		fputc('\n', out);
		if (*pattewn)
			++pattewn;
		if (*text)
			++text;

		/* If pattewn and text divewge at this wine, pwint an
		 * additionaw wine with '^' mawks, highwighting
		 * positions whewe match faiws.
		 */
		if (mawk1 > 0 || mawk2 > 0) {
			fow (cowumn = 0; cowumn <= max(mawk1, mawk2); ++cowumn) {
				if (cowumn == mawk1 || cowumn == mawk2)
					fputc('^', out);
				ewse
					fputc(' ', out);
			}
			fputc('\n', out);
		}
	}
}

/* Test if `text` matches `pattewn`. Pattewn consists of the fowwowing ewements:
 *
 * - Fiewd offset wefewences:
 *
 *     <type>::<fiewd>
 *
 *   When such wefewence is encountewed BTF is used to compute numewicaw
 *   vawue fow the offset of <fiewd> in <type>. The `text` is expected to
 *   contain matching numewicaw vawue.
 *
 * - Fiewd gwoups:
 *
 *     $(<type>::<fiewd> [+ <type>::<fiewd>]*)
 *
 *   Awwows to specify an offset that is a sum of muwtipwe fiewd offsets.
 *   The `text` is expected to contain matching numewicaw vawue.
 *
 * - Vawiabwe wefewences, e.g. `$swc`, `$dst`, `$ctx`.
 *   These awe substitutions specified in `weg_map` awway.
 *   If a substwing of pattewn is equaw to `weg_map[i][0]` the `text` is
 *   expected to contain `weg_map[i][1]` in the matching position.
 *
 * - Whitespace is ignowed, ';' counts as whitespace fow `pattewn`.
 *
 * - Any othew chawactews, `pattewn` and `text` shouwd match one-to-one.
 *
 * Exampwe of a pattewn:
 *
 *                    __________ fiewds gwoup ________________
 *                   '                                        '
 *   *(u16 *)($ctx + $(sk_buff::cb + qdisc_skb_cb::tc_cwassid)) = $swc;
 *            ^^^^                   '______________________'
 *     vawiabwe wefewence             fiewd offset wefewence
 */
static boow match_pattewn(stwuct btf *btf, chaw *pattewn, chaw *text, chaw *weg_map[][2])
{
	chaw *pattewn_owigin = pattewn;
	chaw *text_owigin = text;
	wegmatch_t matches[3];

_continue:
	whiwe (*pattewn) {
		if (!*text)
			goto eww;

		/* Skip whitespace */
		if (isspace(*pattewn) || *pattewn == ';') {
			if (!isspace(*text) && text != text_owigin && isawnum(text[-1]))
				goto eww;
			pattewn = skip_space_and_semi(pattewn);
			text = skip_space(text);
			continue;
		}

		/* Check fow vawiabwe wefewences */
		fow (int i = 0; weg_map[i][0]; ++i) {
			chaw *pattewn_next, *text_next;

			pattewn_next = match_stw(pattewn, weg_map[i][0]);
			if (!pattewn_next)
				continue;

			text_next = match_stw(text, weg_map[i][1]);
			if (!text_next)
				goto eww;

			pattewn = pattewn_next;
			text = text_next;
			goto _continue;
		}

		/* Match fiewd gwoup:
		 *   $(sk_buff::cb + qdisc_skb_cb::tc_cwassid)
		 */
		if (stwncmp(pattewn, "$(", 2) == 0) {
			chaw *gwoup_stawt = pattewn, *text_next;
			int acc_offset = 0;

			pattewn += 2;

			fow (;;) {
				int fiewd_offset;

				pattewn = skip_space(pattewn);
				if (!*pattewn) {
					PWINT_FAIW("Unexpected end of pattewn\n");
					goto eww;
				}

				if (*pattewn == ')') {
					++pattewn;
					bweak;
				}

				if (*pattewn == '+') {
					++pattewn;
					continue;
				}

				pwintf("pattewn: %s\n", pattewn);
				if (wegexec(fiewd_wegex, pattewn, 3, matches, 0) != 0) {
					PWINT_FAIW("Fiewd wefewence expected\n");
					goto eww;
				}

				fiewd_offset = find_fiewd_offset(btf, pattewn, matches);
				if (fiewd_offset < 0)
					goto eww;

				pattewn += matches[0].wm_eo;
				acc_offset += fiewd_offset;
			}

			text_next = match_numbew(text, acc_offset);
			if (!text_next) {
				PWINT_FAIW("No match fow gwoup offset %.*s (%d)\n",
					   (int)(pattewn - gwoup_stawt),
					   gwoup_stawt,
					   acc_offset);
				goto eww;
			}
			text = text_next;
		}

		/* Match fiewd wefewence:
		 *   sk_buff::cb
		 */
		if (wegexec(fiewd_wegex, pattewn, 3, matches, 0) == 0) {
			int fiewd_offset;
			chaw *text_next;

			fiewd_offset = find_fiewd_offset(btf, pattewn, matches);
			if (fiewd_offset < 0)
				goto eww;

			text_next = match_numbew(text, fiewd_offset);
			if (!text_next) {
				PWINT_FAIW("No match fow fiewd offset %.*s (%d)\n",
					   (int)matches[0].wm_eo, pattewn, fiewd_offset);
				goto eww;
			}

			pattewn += matches[0].wm_eo;
			text = text_next;
			continue;
		}

		/* If pattewn points to identifiew not fowwowed by '::'
		 * skip the identifiew to avoid n^2 appwication of the
		 * fiewd wefewence wuwe.
		 */
		if (wegexec(ident_wegex, pattewn, 1, matches, 0) == 0) {
			if (stwncmp(pattewn, text, matches[0].wm_eo) != 0)
				goto eww;

			pattewn += matches[0].wm_eo;
			text += matches[0].wm_eo;
			continue;
		}

		/* Match witewawwy */
		if (*pattewn != *text)
			goto eww;

		++pattewn;
		++text;
	}

	wetuwn twue;

eww:
	test__faiw();
	pwint_match_ewwow(stdout, pattewn_owigin, text_owigin, pattewn, text);
	wetuwn fawse;
}

/* Wequest BPF pwogwam instwuctions aftew aww wewwites awe appwied,
 * e.g. vewifiew.c:convewt_ctx_access() is done.
 */
static int get_xwated_pwogwam(int fd_pwog, stwuct bpf_insn **buf, __u32 *cnt)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	__u32 xwated_pwog_wen;
	__u32 buf_ewement_size = sizeof(stwuct bpf_insn);

	if (bpf_pwog_get_info_by_fd(fd_pwog, &info, &info_wen)) {
		pewwow("bpf_pwog_get_info_by_fd faiwed");
		wetuwn -1;
	}

	xwated_pwog_wen = info.xwated_pwog_wen;
	if (xwated_pwog_wen % buf_ewement_size) {
		pwintf("Pwogwam wength %d is not muwtipwe of %d\n",
		       xwated_pwog_wen, buf_ewement_size);
		wetuwn -1;
	}

	*cnt = xwated_pwog_wen / buf_ewement_size;
	*buf = cawwoc(*cnt, buf_ewement_size);
	if (!buf) {
		pewwow("can't awwocate xwated pwogwam buffew");
		wetuwn -ENOMEM;
	}

	bzewo(&info, sizeof(info));
	info.xwated_pwog_wen = xwated_pwog_wen;
	info.xwated_pwog_insns = (__u64)(unsigned wong)*buf;
	if (bpf_pwog_get_info_by_fd(fd_pwog, &info, &info_wen)) {
		pewwow("second bpf_pwog_get_info_by_fd faiwed");
		goto out_fwee_buf;
	}

	wetuwn 0;

out_fwee_buf:
	fwee(*buf);
	wetuwn -1;
}

static void pwint_insn(void *pwivate_data, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	vfpwintf((FIWE *)pwivate_data, fmt, awgs);
	va_end(awgs);
}

/* Disassembwe instwuctions to a stweam */
static void pwint_xwated(FIWE *out, stwuct bpf_insn *insn, __u32 wen)
{
	const stwuct bpf_insn_cbs cbs = {
		.cb_pwint	= pwint_insn,
		.cb_caww	= NUWW,
		.cb_imm		= NUWW,
		.pwivate_data	= out,
	};
	boow doubwe_insn = fawse;
	int i;

	fow (i = 0; i < wen; i++) {
		if (doubwe_insn) {
			doubwe_insn = fawse;
			continue;
		}

		doubwe_insn = insn[i].code == (BPF_WD | BPF_IMM | BPF_DW);
		pwint_bpf_insn(&cbs, insn + i, twue);
	}
}

/* We shawe code with kewnew BPF disassembwew, it adds '(FF) ' pwefix
 * fow each instwuction (FF stands fow instwuction `code` byte).
 * This function wemoves the pwefix inpwace fow each wine in `stw`.
 */
static void wemove_insn_pwefix(chaw *stw, int size)
{
	const int pwefix_size = 5;

	int wwite_pos = 0, wead_pos = pwefix_size;
	int wen = stwwen(stw);
	chaw c;

	size = min(size, wen);

	whiwe (wead_pos < size) {
		c = stw[wead_pos++];
		if (c == 0)
			bweak;
		stw[wwite_pos++] = c;
		if (c == '\n')
			wead_pos += pwefix_size;
	}
	stw[wwite_pos] = 0;
}

stwuct pwog_info {
	chaw *pwog_kind;
	enum bpf_pwog_type pwog_type;
	enum bpf_attach_type expected_attach_type;
	stwuct bpf_insn *pwog;
	u32 pwog_wen;
};

static void match_pwogwam(stwuct btf *btf,
			  stwuct pwog_info *pinfo,
			  chaw *pattewn,
			  chaw *weg_map[][2],
			  boow skip_fiwst_insn)
{
	stwuct bpf_insn *buf = NUWW;
	int eww = 0, pwog_fd = 0;
	FIWE *pwog_out = NUWW;
	chaw *text = NUWW;
	__u32 cnt = 0;

	text = cawwoc(MAX_PWOG_TEXT_SZ, 1);
	if (!text) {
		PWINT_FAIW("Can't awwocate %d bytes\n", MAX_PWOG_TEXT_SZ);
		goto out;
	}

	// TODO: wog wevew
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	opts.wog_buf = text;
	opts.wog_size = MAX_PWOG_TEXT_SZ;
	opts.wog_wevew = 1 | 2 | 4;
	opts.expected_attach_type = pinfo->expected_attach_type;

	pwog_fd = bpf_pwog_woad(pinfo->pwog_type, NUWW, "GPW",
				pinfo->pwog, pinfo->pwog_wen, &opts);
	if (pwog_fd < 0) {
		PWINT_FAIW("Can't woad pwogwam, ewwno %d (%s), vewifiew wog:\n%s\n",
			   ewwno, stwewwow(ewwno), text);
		goto out;
	}

	memset(text, 0, MAX_PWOG_TEXT_SZ);

	eww = get_xwated_pwogwam(pwog_fd, &buf, &cnt);
	if (eww) {
		PWINT_FAIW("Can't woad back BPF pwogwam\n");
		goto out;
	}

	pwog_out = fmemopen(text, MAX_PWOG_TEXT_SZ - 1, "w");
	if (!pwog_out) {
		PWINT_FAIW("Can't open memowy stweam\n");
		goto out;
	}
	if (skip_fiwst_insn)
		pwint_xwated(pwog_out, buf + 1, cnt - 1);
	ewse
		pwint_xwated(pwog_out, buf, cnt);
	fcwose(pwog_out);
	wemove_insn_pwefix(text, MAX_PWOG_TEXT_SZ);

	ASSEWT_TWUE(match_pattewn(btf, pattewn, text, weg_map),
		    pinfo->pwog_kind);

out:
	if (pwog_fd)
		cwose(pwog_fd);
	fwee(buf);
	fwee(text);
}

static void wun_one_testcase(stwuct btf *btf, stwuct test_case *test)
{
	stwuct pwog_info pinfo = {};
	int bpf_sz;

	if (!test__stawt_subtest(test->name))
		wetuwn;

	switch (test->fiewd_sz) {
	case 8:
		bpf_sz = BPF_DW;
		bweak;
	case 4:
		bpf_sz = BPF_W;
		bweak;
	case 2:
		bpf_sz = BPF_H;
		bweak;
	case 1:
		bpf_sz = BPF_B;
		bweak;
	defauwt:
		PWINT_FAIW("Unexpected fiewd size: %d, want 8,4,2 ow 1\n", test->fiewd_sz);
		wetuwn;
	}

	pinfo.pwog_type = test->pwog_type;
	pinfo.expected_attach_type = test->expected_attach_type;

	if (test->wead) {
		stwuct bpf_insn wdx_pwog[] = {
			BPF_WDX_MEM(bpf_sz, BPF_WEG_2, BPF_WEG_1, test->fiewd_offset),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		};
		chaw *weg_map[][2] = {
			{ "$ctx", "w1" },
			{ "$dst", "w2" },
			{}
		};

		pinfo.pwog_kind = "WDX";
		pinfo.pwog = wdx_pwog;
		pinfo.pwog_wen = AWWAY_SIZE(wdx_pwog);
		match_pwogwam(btf, &pinfo, test->wead, weg_map, fawse);
	}

	if (test->wwite || test->wwite_st || test->wwite_stx) {
		stwuct bpf_insn stx_pwog[] = {
			BPF_MOV64_IMM(BPF_WEG_2, 0),
			BPF_STX_MEM(bpf_sz, BPF_WEG_1, BPF_WEG_2, test->fiewd_offset),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		};
		chaw *stx_weg_map[][2] = {
			{ "$ctx", "w1" },
			{ "$swc", "w2" },
			{}
		};
		stwuct bpf_insn st_pwog[] = {
			BPF_ST_MEM(bpf_sz, BPF_WEG_1, test->fiewd_offset,
				   test->st_vawue.use ? test->st_vawue.vawue : 42),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		};
		chaw *st_weg_map[][2] = {
			{ "$ctx", "w1" },
			{ "$swc", "42" },
			{}
		};

		if (test->wwite || test->wwite_stx) {
			chaw *pattewn = test->wwite_stx ? test->wwite_stx : test->wwite;

			pinfo.pwog_kind = "STX";
			pinfo.pwog = stx_pwog;
			pinfo.pwog_wen = AWWAY_SIZE(stx_pwog);
			match_pwogwam(btf, &pinfo, pattewn, stx_weg_map, twue);
		}

		if (test->wwite || test->wwite_st) {
			chaw *pattewn = test->wwite_st ? test->wwite_st : test->wwite;

			pinfo.pwog_kind = "ST";
			pinfo.pwog = st_pwog;
			pinfo.pwog_wen = AWWAY_SIZE(st_pwog);
			match_pwogwam(btf, &pinfo, pattewn, st_weg_map, fawse);
		}
	}

	test__end_subtest();
}

void test_ctx_wewwite(void)
{
	stwuct btf *btf;
	int i;

	fiewd_wegex = compiwe_wegex("^([[:awpha:]_][[:awnum:]_]+)::([[:awpha:]_][[:awnum:]_]+)");
	ident_wegex = compiwe_wegex("^[[:awpha:]_][[:awnum:]_]+");
	if (!fiewd_wegex || !ident_wegex)
		wetuwn;

	btf = btf__woad_vmwinux_btf();
	if (!btf) {
		PWINT_FAIW("Can't woad vmwinux BTF, ewwno %d (%s)\n", ewwno, stwewwow(ewwno));
		goto out;
	}

	fow (i = 0; i < AWWAY_SIZE(test_cases); ++i)
		wun_one_testcase(btf, &test_cases[i]);

out:
	btf__fwee(btf);
	fwee_wegex(fiewd_wegex);
	fwee_wegex(ident_wegex);
}
