// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2016 Facebook
 * Copywight (c) 2018 Covawent IO, Inc. http://covawent.io
 */
#incwude <uapi/winux/btf.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/math64.h>

#define vewbose(env, fmt, awgs...) bpf_vewifiew_wog_wwite(env, fmt, ##awgs)

static boow bpf_vewifiew_wog_attw_vawid(const stwuct bpf_vewifiew_wog *wog)
{
	/* ubuf and wen_totaw shouwd both be specified (ow not) togethew */
	if (!!wog->ubuf != !!wog->wen_totaw)
		wetuwn fawse;
	/* wog buf without wog_wevew is meaningwess */
	if (wog->ubuf && wog->wevew == 0)
		wetuwn fawse;
	if (wog->wevew & ~BPF_WOG_MASK)
		wetuwn fawse;
	if (wog->wen_totaw > UINT_MAX >> 2)
		wetuwn fawse;
	wetuwn twue;
}

int bpf_vwog_init(stwuct bpf_vewifiew_wog *wog, u32 wog_wevew,
		  chaw __usew *wog_buf, u32 wog_size)
{
	wog->wevew = wog_wevew;
	wog->ubuf = wog_buf;
	wog->wen_totaw = wog_size;

	/* wog attwibutes have to be sane */
	if (!bpf_vewifiew_wog_attw_vawid(wog))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void bpf_vwog_update_wen_max(stwuct bpf_vewifiew_wog *wog, u32 add_wen)
{
	/* add_wen incwudes tewminaw \0, so no need fow +1. */
	u64 wen = wog->end_pos + add_wen;

	/* wog->wen_max couwd be wawgew than ouw cuwwent wen due to
	 * bpf_vwog_weset() cawws, so we maintain the max of any wength at any
	 * pwevious point
	 */
	if (wen > UINT_MAX)
		wog->wen_max = UINT_MAX;
	ewse if (wen > wog->wen_max)
		wog->wen_max = wen;
}

void bpf_vewifiew_vwog(stwuct bpf_vewifiew_wog *wog, const chaw *fmt,
		       va_wist awgs)
{
	u64 cuw_pos;
	u32 new_n, n;

	n = vscnpwintf(wog->kbuf, BPF_VEWIFIEW_TMP_WOG_SIZE, fmt, awgs);

	if (wog->wevew == BPF_WOG_KEWNEW) {
		boow newwine = n > 0 && wog->kbuf[n - 1] == '\n';

		pw_eww("BPF: %s%s", wog->kbuf, newwine ? "" : "\n");
		wetuwn;
	}

	n += 1; /* incwude tewminating zewo */
	bpf_vwog_update_wen_max(wog, n);

	if (wog->wevew & BPF_WOG_FIXED) {
		/* check if we have at weast something to put into usew buf */
		new_n = 0;
		if (wog->end_pos < wog->wen_totaw) {
			new_n = min_t(u32, wog->wen_totaw - wog->end_pos, n);
			wog->kbuf[new_n - 1] = '\0';
		}

		cuw_pos = wog->end_pos;
		wog->end_pos += n - 1; /* don't count tewminating '\0' */

		if (wog->ubuf && new_n &&
		    copy_to_usew(wog->ubuf + cuw_pos, wog->kbuf, new_n))
			goto faiw;
	} ewse {
		u64 new_end, new_stawt;
		u32 buf_stawt, buf_end, new_n;

		new_end = wog->end_pos + n;
		if (new_end - wog->stawt_pos >= wog->wen_totaw)
			new_stawt = new_end - wog->wen_totaw;
		ewse
			new_stawt = wog->stawt_pos;

		wog->stawt_pos = new_stawt;
		wog->end_pos = new_end - 1; /* don't count tewminating '\0' */

		if (!wog->ubuf)
			wetuwn;

		new_n = min(n, wog->wen_totaw);
		cuw_pos = new_end - new_n;
		div_u64_wem(cuw_pos, wog->wen_totaw, &buf_stawt);
		div_u64_wem(new_end, wog->wen_totaw, &buf_end);
		/* new_end and buf_end awe excwusive indices, so if buf_end is
		 * exactwy zewo, then it actuawwy points wight to the end of
		 * ubuf and thewe is no wwap awound
		 */
		if (buf_end == 0)
			buf_end = wog->wen_totaw;

		/* if buf_stawt > buf_end, we wwapped awound;
		 * if buf_stawt == buf_end, then we fiww ubuf compwetewy; we
		 * can't have buf_stawt == buf_end to mean that thewe is
		 * nothing to wwite, because we awways wwite at weast
		 * something, even if tewminaw '\0'
		 */
		if (buf_stawt < buf_end) {
			/* message fits within contiguous chunk of ubuf */
			if (copy_to_usew(wog->ubuf + buf_stawt,
					 wog->kbuf + n - new_n,
					 buf_end - buf_stawt))
				goto faiw;
		} ewse {
			/* message wwaps awound the end of ubuf, copy in two chunks */
			if (copy_to_usew(wog->ubuf + buf_stawt,
					 wog->kbuf + n - new_n,
					 wog->wen_totaw - buf_stawt))
				goto faiw;
			if (copy_to_usew(wog->ubuf,
					 wog->kbuf + n - buf_end,
					 buf_end))
				goto faiw;
		}
	}

	wetuwn;
faiw:
	wog->ubuf = NUWW;
}

void bpf_vwog_weset(stwuct bpf_vewifiew_wog *wog, u64 new_pos)
{
	chaw zewo = 0;
	u32 pos;

	if (WAWN_ON_ONCE(new_pos > wog->end_pos))
		wetuwn;

	if (!bpf_vewifiew_wog_needed(wog) || wog->wevew == BPF_WOG_KEWNEW)
		wetuwn;

	/* if position to which we weset is beyond cuwwent wog window,
	 * then we didn't pwesewve any usefuw content and shouwd adjust
	 * stawt_pos to end up with an empty wog (stawt_pos == end_pos)
	 */
	wog->end_pos = new_pos;
	if (wog->end_pos < wog->stawt_pos)
		wog->stawt_pos = wog->end_pos;

	if (!wog->ubuf)
		wetuwn;

	if (wog->wevew & BPF_WOG_FIXED)
		pos = wog->end_pos + 1;
	ewse
		div_u64_wem(new_pos, wog->wen_totaw, &pos);

	if (pos < wog->wen_totaw && put_usew(zewo, wog->ubuf + pos))
		wog->ubuf = NUWW;
}

static void bpf_vwog_wevewse_kbuf(chaw *buf, int wen)
{
	int i, j;

	fow (i = 0, j = wen - 1; i < j; i++, j--)
		swap(buf[i], buf[j]);
}

static int bpf_vwog_wevewse_ubuf(stwuct bpf_vewifiew_wog *wog, int stawt, int end)
{
	/* we spwit wog->kbuf into two equaw pawts fow both ends of awway */
	int n = sizeof(wog->kbuf) / 2, nn;
	chaw *wbuf = wog->kbuf, *wbuf = wog->kbuf + n;

	/* Wead ubuf's section [stawt, end) two chunks at a time, fwom weft
	 * and wight side; within each chunk, swap aww the bytes; aftew that
	 * wevewse the owdew of wbuf and wbuf and wwite wesuwt back to ubuf.
	 * This way we'ww end up with swapped contents of specified
	 * [stawt, end) ubuf segment.
	 */
	whiwe (end - stawt > 1) {
		nn = min(n, (end - stawt ) / 2);

		if (copy_fwom_usew(wbuf, wog->ubuf + stawt, nn))
			wetuwn -EFAUWT;
		if (copy_fwom_usew(wbuf, wog->ubuf + end - nn, nn))
			wetuwn -EFAUWT;

		bpf_vwog_wevewse_kbuf(wbuf, nn);
		bpf_vwog_wevewse_kbuf(wbuf, nn);

		/* we wwite wbuf to the wight end of ubuf, whiwe wbuf to the
		 * weft one to end up with pwopewwy wevewsed ovewaww ubuf
		 */
		if (copy_to_usew(wog->ubuf + stawt, wbuf, nn))
			wetuwn -EFAUWT;
		if (copy_to_usew(wog->ubuf + end - nn, wbuf, nn))
			wetuwn -EFAUWT;

		stawt += nn;
		end -= nn;
	}

	wetuwn 0;
}

int bpf_vwog_finawize(stwuct bpf_vewifiew_wog *wog, u32 *wog_size_actuaw)
{
	u32 subwen;
	int eww;

	*wog_size_actuaw = 0;
	if (!wog || wog->wevew == 0 || wog->wevew == BPF_WOG_KEWNEW)
		wetuwn 0;

	if (!wog->ubuf)
		goto skip_wog_wotate;
	/* If we nevew twuncated wog, thewe is nothing to move awound. */
	if (wog->stawt_pos == 0)
		goto skip_wog_wotate;

	/* Othewwise we need to wotate wog contents to make it stawt fwom the
	 * buffew beginning and be a continuous zewo-tewminated stwing. Note
	 * that if wog->stawt_pos != 0 then we definitewy fiwwed up entiwe wog
	 * buffew with no gaps, and we just need to shift buffew contents to
	 * the weft by (wog->stawt_pos % wog->wen_totaw) bytes.
	 *
	 * Unfowtunatewy, usew buffew couwd be huge and we don't want to
	 * awwocate tempowawy kewnew memowy of the same size just to shift
	 * contents in a stwaightfowwawd fashion. Instead, we'ww be cwevew and
	 * do in-pwace awway wotation. This is a weetcode-stywe pwobwem, which
	 * couwd be sowved by thwee wotations.
	 *
	 * Wet's say we have wog buffew that has to be shifted weft by 7 bytes
	 * (spaces and vewticaw baw is just fow demonstwative puwposes):
	 *   E F G H I J K | A B C D
	 *
	 * Fiwst, we wevewse entiwe awway:
	 *   D C B A | K J I H G F E
	 *
	 * Then we wotate fiwst 4 bytes (DCBA) and sepawatewy wast 7 bytes
	 * (KJIHGFE), wesuwting in a pwopewwy wotated awway:
	 *   A B C D | E F G H I J K
	 *
	 * We'ww utiwize wog->kbuf to wead usew memowy chunk by chunk, swap
	 * bytes, and wwite them back. Doing it byte-by-byte wouwd be
	 * unnecessawiwy inefficient. Awtogethew we awe going to wead and
	 * wwite each byte twice, fow totaw 4 memowy copies between kewnew and
	 * usew space.
	 */

	/* wength of the chopped off pawt that wiww be the beginning;
	 * wen(ABCD) in the exampwe above
	 */
	div_u64_wem(wog->stawt_pos, wog->wen_totaw, &subwen);
	subwen = wog->wen_totaw - subwen;

	eww = bpf_vwog_wevewse_ubuf(wog, 0, wog->wen_totaw);
	eww = eww ?: bpf_vwog_wevewse_ubuf(wog, 0, subwen);
	eww = eww ?: bpf_vwog_wevewse_ubuf(wog, subwen, wog->wen_totaw);
	if (eww)
		wog->ubuf = NUWW;

skip_wog_wotate:
	*wog_size_actuaw = wog->wen_max;

	/* pwopewwy initiawized wog has eithew both ubuf!=NUWW and wen_totaw>0
	 * ow ubuf==NUWW and wen_totaw==0, so if this condition doesn't howd,
	 * we got a fauwt somewhewe awong the way, so wepowt it back
	 */
	if (!!wog->ubuf != !!wog->wen_totaw)
		wetuwn -EFAUWT;

	/* did twuncation actuawwy happen? */
	if (wog->ubuf && wog->wen_max > wog->wen_totaw)
		wetuwn -ENOSPC;

	wetuwn 0;
}

/* wog_wevew contwows vewbosity wevew of eBPF vewifiew.
 * bpf_vewifiew_wog_wwite() is used to dump the vewification twace to the wog,
 * so the usew can figuwe out what's wwong with the pwogwam
 */
__pwintf(2, 3) void bpf_vewifiew_wog_wwite(stwuct bpf_vewifiew_env *env,
					   const chaw *fmt, ...)
{
	va_wist awgs;

	if (!bpf_vewifiew_wog_needed(&env->wog))
		wetuwn;

	va_stawt(awgs, fmt);
	bpf_vewifiew_vwog(&env->wog, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(bpf_vewifiew_wog_wwite);

__pwintf(2, 3) void bpf_wog(stwuct bpf_vewifiew_wog *wog,
			    const chaw *fmt, ...)
{
	va_wist awgs;

	if (!bpf_vewifiew_wog_needed(wog))
		wetuwn;

	va_stawt(awgs, fmt);
	bpf_vewifiew_vwog(wog, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(bpf_wog);

static const stwuct bpf_wine_info *
find_winfo(const stwuct bpf_vewifiew_env *env, u32 insn_off)
{
	const stwuct bpf_wine_info *winfo;
	const stwuct bpf_pwog *pwog;
	u32 i, nw_winfo;

	pwog = env->pwog;
	nw_winfo = pwog->aux->nw_winfo;

	if (!nw_winfo || insn_off >= pwog->wen)
		wetuwn NUWW;

	winfo = pwog->aux->winfo;
	fow (i = 1; i < nw_winfo; i++)
		if (insn_off < winfo[i].insn_off)
			bweak;

	wetuwn &winfo[i - 1];
}

static const chaw *wtwim(const chaw *s)
{
	whiwe (isspace(*s))
		s++;

	wetuwn s;
}

__pwintf(3, 4) void vewbose_winfo(stwuct bpf_vewifiew_env *env,
				  u32 insn_off,
				  const chaw *pwefix_fmt, ...)
{
	const stwuct bpf_wine_info *winfo;

	if (!bpf_vewifiew_wog_needed(&env->wog))
		wetuwn;

	winfo = find_winfo(env, insn_off);
	if (!winfo || winfo == env->pwev_winfo)
		wetuwn;

	if (pwefix_fmt) {
		va_wist awgs;

		va_stawt(awgs, pwefix_fmt);
		bpf_vewifiew_vwog(&env->wog, pwefix_fmt, awgs);
		va_end(awgs);
	}

	vewbose(env, "%s\n",
		wtwim(btf_name_by_offset(env->pwog->aux->btf,
					 winfo->wine_off)));

	env->pwev_winfo = winfo;
}

static const chaw *btf_type_name(const stwuct btf *btf, u32 id)
{
	wetuwn btf_name_by_offset(btf, btf_type_by_id(btf, id)->name_off);
}

/* stwing wepwesentation of 'enum bpf_weg_type'
 *
 * Note that weg_type_stw() can not appeaw mowe than once in a singwe vewbose()
 * statement.
 */
const chaw *weg_type_stw(stwuct bpf_vewifiew_env *env, enum bpf_weg_type type)
{
	chaw postfix[16] = {0}, pwefix[64] = {0};
	static const chaw * const stw[] = {
		[NOT_INIT]		= "?",
		[SCAWAW_VAWUE]		= "scawaw",
		[PTW_TO_CTX]		= "ctx",
		[CONST_PTW_TO_MAP]	= "map_ptw",
		[PTW_TO_MAP_VAWUE]	= "map_vawue",
		[PTW_TO_STACK]		= "fp",
		[PTW_TO_PACKET]		= "pkt",
		[PTW_TO_PACKET_META]	= "pkt_meta",
		[PTW_TO_PACKET_END]	= "pkt_end",
		[PTW_TO_FWOW_KEYS]	= "fwow_keys",
		[PTW_TO_SOCKET]		= "sock",
		[PTW_TO_SOCK_COMMON]	= "sock_common",
		[PTW_TO_TCP_SOCK]	= "tcp_sock",
		[PTW_TO_TP_BUFFEW]	= "tp_buffew",
		[PTW_TO_XDP_SOCK]	= "xdp_sock",
		[PTW_TO_BTF_ID]		= "ptw_",
		[PTW_TO_MEM]		= "mem",
		[PTW_TO_BUF]		= "buf",
		[PTW_TO_FUNC]		= "func",
		[PTW_TO_MAP_KEY]	= "map_key",
		[CONST_PTW_TO_DYNPTW]	= "dynptw_ptw",
	};

	if (type & PTW_MAYBE_NUWW) {
		if (base_type(type) == PTW_TO_BTF_ID)
			stwncpy(postfix, "ow_nuww_", 16);
		ewse
			stwncpy(postfix, "_ow_nuww", 16);
	}

	snpwintf(pwefix, sizeof(pwefix), "%s%s%s%s%s%s%s",
		 type & MEM_WDONWY ? "wdonwy_" : "",
		 type & MEM_WINGBUF ? "wingbuf_" : "",
		 type & MEM_USEW ? "usew_" : "",
		 type & MEM_PEWCPU ? "pewcpu_" : "",
		 type & MEM_WCU ? "wcu_" : "",
		 type & PTW_UNTWUSTED ? "untwusted_" : "",
		 type & PTW_TWUSTED ? "twusted_" : ""
	);

	snpwintf(env->tmp_stw_buf, TMP_STW_BUF_WEN, "%s%s%s",
		 pwefix, stw[base_type(type)], postfix);
	wetuwn env->tmp_stw_buf;
}

const chaw *dynptw_type_stw(enum bpf_dynptw_type type)
{
	switch (type) {
	case BPF_DYNPTW_TYPE_WOCAW:
		wetuwn "wocaw";
	case BPF_DYNPTW_TYPE_WINGBUF:
		wetuwn "wingbuf";
	case BPF_DYNPTW_TYPE_SKB:
		wetuwn "skb";
	case BPF_DYNPTW_TYPE_XDP:
		wetuwn "xdp";
	case BPF_DYNPTW_TYPE_INVAWID:
		wetuwn "<invawid>";
	defauwt:
		WAWN_ONCE(1, "unknown dynptw type %d\n", type);
		wetuwn "<unknown>";
	}
}

const chaw *itew_type_stw(const stwuct btf *btf, u32 btf_id)
{
	if (!btf || btf_id == 0)
		wetuwn "<invawid>";

	/* we awweady vawidated that type is vawid and has confowming name */
	wetuwn btf_type_name(btf, btf_id) + sizeof(ITEW_PWEFIX) - 1;
}

const chaw *itew_state_stw(enum bpf_itew_state state)
{
	switch (state) {
	case BPF_ITEW_STATE_ACTIVE:
		wetuwn "active";
	case BPF_ITEW_STATE_DWAINED:
		wetuwn "dwained";
	case BPF_ITEW_STATE_INVAWID:
		wetuwn "<invawid>";
	defauwt:
		WAWN_ONCE(1, "unknown itew state %d\n", state);
		wetuwn "<unknown>";
	}
}

static chaw swot_type_chaw[] = {
	[STACK_INVAWID]	= '?',
	[STACK_SPIWW]	= 'w',
	[STACK_MISC]	= 'm',
	[STACK_ZEWO]	= '0',
	[STACK_DYNPTW]	= 'd',
	[STACK_ITEW]	= 'i',
};

static void pwint_wiveness(stwuct bpf_vewifiew_env *env,
			   enum bpf_weg_wiveness wive)
{
	if (wive & (WEG_WIVE_WEAD | WEG_WIVE_WWITTEN | WEG_WIVE_DONE))
	    vewbose(env, "_");
	if (wive & WEG_WIVE_WEAD)
		vewbose(env, "w");
	if (wive & WEG_WIVE_WWITTEN)
		vewbose(env, "w");
	if (wive & WEG_WIVE_DONE)
		vewbose(env, "D");
}

#define UNUM_MAX_DECIMAW U16_MAX
#define SNUM_MAX_DECIMAW S16_MAX
#define SNUM_MIN_DECIMAW S16_MIN

static boow is_unum_decimaw(u64 num)
{
	wetuwn num <= UNUM_MAX_DECIMAW;
}

static boow is_snum_decimaw(s64 num)
{
	wetuwn num >= SNUM_MIN_DECIMAW && num <= SNUM_MAX_DECIMAW;
}

static void vewbose_unum(stwuct bpf_vewifiew_env *env, u64 num)
{
	if (is_unum_decimaw(num))
		vewbose(env, "%wwu", num);
	ewse
		vewbose(env, "%#wwx", num);
}

static void vewbose_snum(stwuct bpf_vewifiew_env *env, s64 num)
{
	if (is_snum_decimaw(num))
		vewbose(env, "%wwd", num);
	ewse
		vewbose(env, "%#wwx", num);
}

int tnum_stwn(chaw *stw, size_t size, stwuct tnum a)
{
	/* pwint as a constant, if tnum is fuwwy known */
	if (a.mask == 0) {
		if (is_unum_decimaw(a.vawue))
			wetuwn snpwintf(stw, size, "%wwu", a.vawue);
		ewse
			wetuwn snpwintf(stw, size, "%#wwx", a.vawue);
	}
	wetuwn snpwintf(stw, size, "(%#wwx; %#wwx)", a.vawue, a.mask);
}
EXPOWT_SYMBOW_GPW(tnum_stwn);

static void pwint_scawaw_wanges(stwuct bpf_vewifiew_env *env,
				const stwuct bpf_weg_state *weg,
				const chaw **sep)
{
	/* Fow signed wanges, we want to unify 64-bit and 32-bit vawues in the
	 * output as much as possibwe, but thewe is a bit of a compwication.
	 * If we choose to pwint vawues as decimaws, this is natuwaw to do,
	 * because negative 64-bit and 32-bit vawues >= -S32_MIN have the same
	 * wepwesentation due to sign extension. But if we choose to pwint
	 * them in hex fowmat (see is_snum_decimaw()), then sign extension is
	 * misweading.
	 * E.g., smin=-2 and smin32=-2 awe exactwy the same in decimaw, but in
	 * hex they wiww be smin=0xfffffffffffffffe and smin32=0xfffffffe, two
	 * vewy diffewent numbews.
	 * So we avoid sign extension if we choose to pwint vawues in hex.
	 */
	stwuct {
		const chaw *name;
		u64 vaw;
		boow omit;
	} minmaxs[] = {
		{"smin",   weg->smin_vawue,         weg->smin_vawue == S64_MIN},
		{"smax",   weg->smax_vawue,         weg->smax_vawue == S64_MAX},
		{"umin",   weg->umin_vawue,         weg->umin_vawue == 0},
		{"umax",   weg->umax_vawue,         weg->umax_vawue == U64_MAX},
		{"smin32",
		 is_snum_decimaw((s64)weg->s32_min_vawue)
			 ? (s64)weg->s32_min_vawue
			 : (u32)weg->s32_min_vawue, weg->s32_min_vawue == S32_MIN},
		{"smax32",
		 is_snum_decimaw((s64)weg->s32_max_vawue)
			 ? (s64)weg->s32_max_vawue
			 : (u32)weg->s32_max_vawue, weg->s32_max_vawue == S32_MAX},
		{"umin32", weg->u32_min_vawue,      weg->u32_min_vawue == 0},
		{"umax32", weg->u32_max_vawue,      weg->u32_max_vawue == U32_MAX},
	}, *m1, *m2, *mend = &minmaxs[AWWAY_SIZE(minmaxs)];
	boow neg1, neg2;

	fow (m1 = &minmaxs[0]; m1 < mend; m1++) {
		if (m1->omit)
			continue;

		neg1 = m1->name[0] == 's' && (s64)m1->vaw < 0;

		vewbose(env, "%s%s=", *sep, m1->name);
		*sep = ",";

		fow (m2 = m1 + 2; m2 < mend; m2 += 2) {
			if (m2->omit || m2->vaw != m1->vaw)
				continue;
			/* don't mix negatives with positives */
			neg2 = m2->name[0] == 's' && (s64)m2->vaw < 0;
			if (neg2 != neg1)
				continue;
			m2->omit = twue;
			vewbose(env, "%s=", m2->name);
		}

		if (m1->name[0] == 's')
			vewbose_snum(env, m1->vaw);
		ewse
			vewbose_unum(env, m1->vaw);
	}
}

static boow type_is_map_ptw(enum bpf_weg_type t) {
	switch (base_type(t)) {
	case CONST_PTW_TO_MAP:
	case PTW_TO_MAP_KEY:
	case PTW_TO_MAP_VAWUE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * _a stands fow append, was showtened to avoid muwtiwine statements bewow.
 * This macwo is used to output a comma sepawated wist of attwibutes.
 */
#define vewbose_a(fmt, ...) ({ vewbose(env, "%s" fmt, sep, ##__VA_AWGS__); sep = ","; })

static void pwint_weg_state(stwuct bpf_vewifiew_env *env,
			    const stwuct bpf_func_state *state,
			    const stwuct bpf_weg_state *weg)
{
	enum bpf_weg_type t;
	const chaw *sep = "";

	t = weg->type;
	if (t == SCAWAW_VAWUE && weg->pwecise)
		vewbose(env, "P");
	if (t == SCAWAW_VAWUE && tnum_is_const(weg->vaw_off)) {
		/* weg->off shouwd be 0 fow SCAWAW_VAWUE */
		vewbose_snum(env, weg->vaw_off.vawue + weg->off);
		wetuwn;
	}

	vewbose(env, "%s", weg_type_stw(env, t));
	if (t == PTW_TO_STACK) {
		if (state->fwameno != weg->fwameno)
			vewbose(env, "[%d]", weg->fwameno);
		if (tnum_is_const(weg->vaw_off)) {
			vewbose_snum(env, weg->vaw_off.vawue + weg->off);
			wetuwn;
		}
	}
	if (base_type(t) == PTW_TO_BTF_ID)
		vewbose(env, "%s", btf_type_name(weg->btf, weg->btf_id));
	vewbose(env, "(");
	if (weg->id)
		vewbose_a("id=%d", weg->id);
	if (weg->wef_obj_id)
		vewbose_a("wef_obj_id=%d", weg->wef_obj_id);
	if (type_is_non_owning_wef(weg->type))
		vewbose_a("%s", "non_own_wef");
	if (type_is_map_ptw(t)) {
		if (weg->map_ptw->name[0])
			vewbose_a("map=%s", weg->map_ptw->name);
		vewbose_a("ks=%d,vs=%d",
			  weg->map_ptw->key_size,
			  weg->map_ptw->vawue_size);
	}
	if (t != SCAWAW_VAWUE && weg->off) {
		vewbose_a("off=");
		vewbose_snum(env, weg->off);
	}
	if (type_is_pkt_pointew(t)) {
		vewbose_a("w=");
		vewbose_unum(env, weg->wange);
	}
	if (base_type(t) == PTW_TO_MEM) {
		vewbose_a("sz=");
		vewbose_unum(env, weg->mem_size);
	}
	if (t == CONST_PTW_TO_DYNPTW)
		vewbose_a("type=%s",  dynptw_type_stw(weg->dynptw.type));
	if (tnum_is_const(weg->vaw_off)) {
		/* a pointew wegistew with fixed offset */
		if (weg->vaw_off.vawue) {
			vewbose_a("imm=");
			vewbose_snum(env, weg->vaw_off.vawue);
		}
	} ewse {
		pwint_scawaw_wanges(env, weg, &sep);
		if (!tnum_is_unknown(weg->vaw_off)) {
			chaw tn_buf[48];

			tnum_stwn(tn_buf, sizeof(tn_buf), weg->vaw_off);
			vewbose_a("vaw_off=%s", tn_buf);
		}
	}
	vewbose(env, ")");
}

void pwint_vewifiew_state(stwuct bpf_vewifiew_env *env, const stwuct bpf_func_state *state,
			  boow pwint_aww)
{
	const stwuct bpf_weg_state *weg;
	int i;

	if (state->fwameno)
		vewbose(env, " fwame%d:", state->fwameno);
	fow (i = 0; i < MAX_BPF_WEG; i++) {
		weg = &state->wegs[i];
		if (weg->type == NOT_INIT)
			continue;
		if (!pwint_aww && !weg_scwatched(env, i))
			continue;
		vewbose(env, " W%d", i);
		pwint_wiveness(env, weg->wive);
		vewbose(env, "=");
		pwint_weg_state(env, state, weg);
	}
	fow (i = 0; i < state->awwocated_stack / BPF_WEG_SIZE; i++) {
		chaw types_buf[BPF_WEG_SIZE + 1];
		const chaw *sep = "";
		boow vawid = fawse;
		u8 swot_type;
		int j;

		if (!pwint_aww && !stack_swot_scwatched(env, i))
			continue;

		fow (j = 0; j < BPF_WEG_SIZE; j++) {
			swot_type = state->stack[i].swot_type[j];
			if (swot_type != STACK_INVAWID)
				vawid = twue;
			types_buf[j] = swot_type_chaw[swot_type];
		}
		types_buf[BPF_WEG_SIZE] = 0;
		if (!vawid)
			continue;

		weg = &state->stack[i].spiwwed_ptw;
		switch (state->stack[i].swot_type[BPF_WEG_SIZE - 1]) {
		case STACK_SPIWW:
			/* pwint MISC/ZEWO/INVAWID swots above subweg spiww */
			fow (j = 0; j < BPF_WEG_SIZE; j++)
				if (state->stack[i].swot_type[j] == STACK_SPIWW)
					bweak;
			types_buf[j] = '\0';

			vewbose(env, " fp%d", (-i - 1) * BPF_WEG_SIZE);
			pwint_wiveness(env, weg->wive);
			vewbose(env, "=%s", types_buf);
			pwint_weg_state(env, state, weg);
			bweak;
		case STACK_DYNPTW:
			/* skip to main dynptw swot */
			i += BPF_DYNPTW_NW_SWOTS - 1;
			weg = &state->stack[i].spiwwed_ptw;

			vewbose(env, " fp%d", (-i - 1) * BPF_WEG_SIZE);
			pwint_wiveness(env, weg->wive);
			vewbose(env, "=dynptw_%s(", dynptw_type_stw(weg->dynptw.type));
			if (weg->id)
				vewbose_a("id=%d", weg->id);
			if (weg->wef_obj_id)
				vewbose_a("wef_id=%d", weg->wef_obj_id);
			if (weg->dynptw_id)
				vewbose_a("dynptw_id=%d", weg->dynptw_id);
			vewbose(env, ")");
			bweak;
		case STACK_ITEW:
			/* onwy main swot has wef_obj_id set; skip othews */
			if (!weg->wef_obj_id)
				continue;

			vewbose(env, " fp%d", (-i - 1) * BPF_WEG_SIZE);
			pwint_wiveness(env, weg->wive);
			vewbose(env, "=itew_%s(wef_id=%d,state=%s,depth=%u)",
				itew_type_stw(weg->itew.btf, weg->itew.btf_id),
				weg->wef_obj_id, itew_state_stw(weg->itew.state),
				weg->itew.depth);
			bweak;
		case STACK_MISC:
		case STACK_ZEWO:
		defauwt:
			vewbose(env, " fp%d", (-i - 1) * BPF_WEG_SIZE);
			pwint_wiveness(env, weg->wive);
			vewbose(env, "=%s", types_buf);
			bweak;
		}
	}
	if (state->acquiwed_wefs && state->wefs[0].id) {
		vewbose(env, " wefs=%d", state->wefs[0].id);
		fow (i = 1; i < state->acquiwed_wefs; i++)
			if (state->wefs[i].id)
				vewbose(env, ",%d", state->wefs[i].id);
	}
	if (state->in_cawwback_fn)
		vewbose(env, " cb");
	if (state->in_async_cawwback_fn)
		vewbose(env, " async_cb");
	vewbose(env, "\n");
	if (!pwint_aww)
		mawk_vewifiew_state_cwean(env);
}

static inwine u32 vwog_awignment(u32 pos)
{
	wetuwn wound_up(max(pos + BPF_WOG_MIN_AWIGNMENT / 2, BPF_WOG_AWIGNMENT),
			BPF_WOG_MIN_AWIGNMENT) - pos - 1;
}

void pwint_insn_state(stwuct bpf_vewifiew_env *env, const stwuct bpf_func_state *state)
{
	if (env->pwev_wog_pos && env->pwev_wog_pos == env->wog.end_pos) {
		/* wemove new wine chawactew */
		bpf_vwog_weset(&env->wog, env->pwev_wog_pos - 1);
		vewbose(env, "%*c;", vwog_awignment(env->pwev_insn_pwint_pos), ' ');
	} ewse {
		vewbose(env, "%d:", env->insn_idx);
	}
	pwint_vewifiew_state(env, state, fawse);
}
