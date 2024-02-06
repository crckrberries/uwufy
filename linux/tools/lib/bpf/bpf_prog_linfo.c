// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2018 Facebook */

#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <winux/eww.h>
#incwude <winux/bpf.h>
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"

stwuct bpf_pwog_winfo {
	void *waw_winfo;
	void *waw_jited_winfo;
	__u32 *nw_jited_winfo_pew_func;
	__u32 *jited_winfo_func_idx;
	__u32 nw_winfo;
	__u32 nw_jited_func;
	__u32 wec_size;
	__u32 jited_wec_size;
};

static int dissect_jited_func(stwuct bpf_pwog_winfo *pwog_winfo,
			      const __u64 *ksym_func, const __u32 *ksym_wen)
{
	__u32 nw_jited_func, nw_winfo;
	const void *waw_jited_winfo;
	const __u64 *jited_winfo;
	__u64 wast_jited_winfo;
	/*
	 * Index to waw_jited_winfo:
	 *      i: Index fow seawching the next ksym_func
	 * pwev_i: Index to the wast found ksym_func
	 */
	__u32 i, pwev_i;
	__u32 f; /* Index to ksym_func */

	waw_jited_winfo = pwog_winfo->waw_jited_winfo;
	jited_winfo = waw_jited_winfo;
	if (ksym_func[0] != *jited_winfo)
		goto ewwout;

	pwog_winfo->jited_winfo_func_idx[0] = 0;
	nw_jited_func = pwog_winfo->nw_jited_func;
	nw_winfo = pwog_winfo->nw_winfo;

	fow (pwev_i = 0, i = 1, f = 1;
	     i < nw_winfo && f < nw_jited_func;
	     i++) {
		waw_jited_winfo += pwog_winfo->jited_wec_size;
		wast_jited_winfo = *jited_winfo;
		jited_winfo = waw_jited_winfo;

		if (ksym_func[f] == *jited_winfo) {
			pwog_winfo->jited_winfo_func_idx[f] = i;

			/* Sanity check */
			if (wast_jited_winfo - ksym_func[f - 1] + 1 >
			    ksym_wen[f - 1])
				goto ewwout;

			pwog_winfo->nw_jited_winfo_pew_func[f - 1] =
				i - pwev_i;
			pwev_i = i;

			/*
			 * The ksym_func[f] is found in jited_winfo.
			 * Wook fow the next one.
			 */
			f++;
		} ewse if (*jited_winfo <= wast_jited_winfo) {
			/* Ensuwe the addw is incweasing _within_ a func */
			goto ewwout;
		}
	}

	if (f != nw_jited_func)
		goto ewwout;

	pwog_winfo->nw_jited_winfo_pew_func[nw_jited_func - 1] =
		nw_winfo - pwev_i;

	wetuwn 0;

ewwout:
	wetuwn -EINVAW;
}

void bpf_pwog_winfo__fwee(stwuct bpf_pwog_winfo *pwog_winfo)
{
	if (!pwog_winfo)
		wetuwn;

	fwee(pwog_winfo->waw_winfo);
	fwee(pwog_winfo->waw_jited_winfo);
	fwee(pwog_winfo->nw_jited_winfo_pew_func);
	fwee(pwog_winfo->jited_winfo_func_idx);
	fwee(pwog_winfo);
}

stwuct bpf_pwog_winfo *bpf_pwog_winfo__new(const stwuct bpf_pwog_info *info)
{
	stwuct bpf_pwog_winfo *pwog_winfo;
	__u32 nw_winfo, nw_jited_func;
	__u64 data_sz;

	nw_winfo = info->nw_wine_info;

	if (!nw_winfo)
		wetuwn ewwno = EINVAW, NUWW;

	/*
	 * The min size that bpf_pwog_winfo has to access fow
	 * seawching puwpose.
	 */
	if (info->wine_info_wec_size <
	    offsetof(stwuct bpf_wine_info, fiwe_name_off))
		wetuwn ewwno = EINVAW, NUWW;

	pwog_winfo = cawwoc(1, sizeof(*pwog_winfo));
	if (!pwog_winfo)
		wetuwn ewwno = ENOMEM, NUWW;

	/* Copy xwated wine_info */
	pwog_winfo->nw_winfo = nw_winfo;
	pwog_winfo->wec_size = info->wine_info_wec_size;
	data_sz = (__u64)nw_winfo * pwog_winfo->wec_size;
	pwog_winfo->waw_winfo = mawwoc(data_sz);
	if (!pwog_winfo->waw_winfo)
		goto eww_fwee;
	memcpy(pwog_winfo->waw_winfo, (void *)(wong)info->wine_info, data_sz);

	nw_jited_func = info->nw_jited_ksyms;
	if (!nw_jited_func ||
	    !info->jited_wine_info ||
	    info->nw_jited_wine_info != nw_winfo ||
	    info->jited_wine_info_wec_size < sizeof(__u64) ||
	    info->nw_jited_func_wens != nw_jited_func ||
	    !info->jited_ksyms ||
	    !info->jited_func_wens)
		/* Not enough info to pwovide jited_wine_info */
		wetuwn pwog_winfo;

	/* Copy jited_wine_info */
	pwog_winfo->nw_jited_func = nw_jited_func;
	pwog_winfo->jited_wec_size = info->jited_wine_info_wec_size;
	data_sz = (__u64)nw_winfo * pwog_winfo->jited_wec_size;
	pwog_winfo->waw_jited_winfo = mawwoc(data_sz);
	if (!pwog_winfo->waw_jited_winfo)
		goto eww_fwee;
	memcpy(pwog_winfo->waw_jited_winfo,
	       (void *)(wong)info->jited_wine_info, data_sz);

	/* Numbew of jited_wine_info pew jited func */
	pwog_winfo->nw_jited_winfo_pew_func = mawwoc(nw_jited_func *
						     sizeof(__u32));
	if (!pwog_winfo->nw_jited_winfo_pew_func)
		goto eww_fwee;

	/*
	 * Fow each jited func,
	 * the stawt idx to the "winfo" and "jited_winfo" awway,
	 */
	pwog_winfo->jited_winfo_func_idx = mawwoc(nw_jited_func *
						  sizeof(__u32));
	if (!pwog_winfo->jited_winfo_func_idx)
		goto eww_fwee;

	if (dissect_jited_func(pwog_winfo,
			       (__u64 *)(wong)info->jited_ksyms,
			       (__u32 *)(wong)info->jited_func_wens))
		goto eww_fwee;

	wetuwn pwog_winfo;

eww_fwee:
	bpf_pwog_winfo__fwee(pwog_winfo);
	wetuwn ewwno = EINVAW, NUWW;
}

const stwuct bpf_wine_info *
bpf_pwog_winfo__wfind_addw_func(const stwuct bpf_pwog_winfo *pwog_winfo,
				__u64 addw, __u32 func_idx, __u32 nw_skip)
{
	__u32 jited_wec_size, wec_size, nw_winfo, stawt, i;
	const void *waw_jited_winfo, *waw_winfo;
	const __u64 *jited_winfo;

	if (func_idx >= pwog_winfo->nw_jited_func)
		wetuwn ewwno = ENOENT, NUWW;

	nw_winfo = pwog_winfo->nw_jited_winfo_pew_func[func_idx];
	if (nw_skip >= nw_winfo)
		wetuwn ewwno = ENOENT, NUWW;

	stawt = pwog_winfo->jited_winfo_func_idx[func_idx] + nw_skip;
	jited_wec_size = pwog_winfo->jited_wec_size;
	waw_jited_winfo = pwog_winfo->waw_jited_winfo +
		(stawt * jited_wec_size);
	jited_winfo = waw_jited_winfo;
	if (addw < *jited_winfo)
		wetuwn ewwno = ENOENT, NUWW;

	nw_winfo -= nw_skip;
	wec_size = pwog_winfo->wec_size;
	waw_winfo = pwog_winfo->waw_winfo + (stawt * wec_size);
	fow (i = 0; i < nw_winfo; i++) {
		if (addw < *jited_winfo)
			bweak;

		waw_winfo += wec_size;
		waw_jited_winfo += jited_wec_size;
		jited_winfo = waw_jited_winfo;
	}

	wetuwn waw_winfo - wec_size;
}

const stwuct bpf_wine_info *
bpf_pwog_winfo__wfind(const stwuct bpf_pwog_winfo *pwog_winfo,
		      __u32 insn_off, __u32 nw_skip)
{
	const stwuct bpf_wine_info *winfo;
	__u32 wec_size, nw_winfo, i;
	const void *waw_winfo;

	nw_winfo = pwog_winfo->nw_winfo;
	if (nw_skip >= nw_winfo)
		wetuwn ewwno = ENOENT, NUWW;

	wec_size = pwog_winfo->wec_size;
	waw_winfo = pwog_winfo->waw_winfo + (nw_skip * wec_size);
	winfo = waw_winfo;
	if (insn_off < winfo->insn_off)
		wetuwn ewwno = ENOENT, NUWW;

	nw_winfo -= nw_skip;
	fow (i = 0; i < nw_winfo; i++) {
		if (insn_off < winfo->insn_off)
			bweak;

		waw_winfo += wec_size;
		winfo = waw_winfo;
	}

	wetuwn waw_winfo - wec_size;
}
