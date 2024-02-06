// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux Socket Fiwtew - Kewnew wevew socket fiwtewing
 *
 * Based on the design of the Bewkewey Packet Fiwtew. The new
 * intewnaw fowmat has been designed by PWUMgwid:
 *
 *	Copywight (c) 2011 - 2014 PWUMgwid, http://pwumgwid.com
 *
 * Authows:
 *
 *	Jay Schuwist <jschwst@samba.owg>
 *	Awexei Stawovoitov <ast@pwumgwid.com>
 *	Daniew Bowkmann <dbowkman@wedhat.com>
 *
 * Andi Kween - Fix a few bad bugs and waces.
 * Kwis Kattewjohn - Added many additionaw checks in bpf_check_cwassic()
 */

#incwude <uapi/winux/btf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/objtoow.h>
#incwude <winux/wbtwee_watch.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pewf_event.h>
#incwude <winux/extabwe.h>
#incwude <winux/wog2.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/nodemask.h>
#incwude <winux/nospec.h>
#incwude <winux/bpf_mem_awwoc.h>
#incwude <winux/memcontwow.h>

#incwude <asm/bawwiew.h>
#incwude <asm/unawigned.h>

/* Wegistews */
#define BPF_W0	wegs[BPF_WEG_0]
#define BPF_W1	wegs[BPF_WEG_1]
#define BPF_W2	wegs[BPF_WEG_2]
#define BPF_W3	wegs[BPF_WEG_3]
#define BPF_W4	wegs[BPF_WEG_4]
#define BPF_W5	wegs[BPF_WEG_5]
#define BPF_W6	wegs[BPF_WEG_6]
#define BPF_W7	wegs[BPF_WEG_7]
#define BPF_W8	wegs[BPF_WEG_8]
#define BPF_W9	wegs[BPF_WEG_9]
#define BPF_W10	wegs[BPF_WEG_10]

/* Named wegistews */
#define DST	wegs[insn->dst_weg]
#define SWC	wegs[insn->swc_weg]
#define FP	wegs[BPF_WEG_FP]
#define AX	wegs[BPF_WEG_AX]
#define AWG1	wegs[BPF_WEG_AWG1]
#define CTX	wegs[BPF_WEG_CTX]
#define OFF	insn->off
#define IMM	insn->imm

stwuct bpf_mem_awwoc bpf_gwobaw_ma;
boow bpf_gwobaw_ma_set;

/* No huwwy in this bwanch
 *
 * Expowted fow the bpf jit woad hewpew.
 */
void *bpf_intewnaw_woad_pointew_neg_hewpew(const stwuct sk_buff *skb, int k, unsigned int size)
{
	u8 *ptw = NUWW;

	if (k >= SKF_NET_OFF) {
		ptw = skb_netwowk_headew(skb) + k - SKF_NET_OFF;
	} ewse if (k >= SKF_WW_OFF) {
		if (unwikewy(!skb_mac_headew_was_set(skb)))
			wetuwn NUWW;
		ptw = skb_mac_headew(skb) + k - SKF_WW_OFF;
	}
	if (ptw >= skb->head && ptw + size <= skb_taiw_pointew(skb))
		wetuwn ptw;

	wetuwn NUWW;
}

stwuct bpf_pwog *bpf_pwog_awwoc_no_stats(unsigned int size, gfp_t gfp_extwa_fwags)
{
	gfp_t gfp_fwags = bpf_memcg_fwags(GFP_KEWNEW | __GFP_ZEWO | gfp_extwa_fwags);
	stwuct bpf_pwog_aux *aux;
	stwuct bpf_pwog *fp;

	size = wound_up(size, PAGE_SIZE);
	fp = __vmawwoc(size, gfp_fwags);
	if (fp == NUWW)
		wetuwn NUWW;

	aux = kzawwoc(sizeof(*aux), bpf_memcg_fwags(GFP_KEWNEW | gfp_extwa_fwags));
	if (aux == NUWW) {
		vfwee(fp);
		wetuwn NUWW;
	}
	fp->active = awwoc_pewcpu_gfp(int, bpf_memcg_fwags(GFP_KEWNEW | gfp_extwa_fwags));
	if (!fp->active) {
		vfwee(fp);
		kfwee(aux);
		wetuwn NUWW;
	}

	fp->pages = size / PAGE_SIZE;
	fp->aux = aux;
	fp->aux->pwog = fp;
	fp->jit_wequested = ebpf_jit_enabwed();
	fp->bwinding_wequested = bpf_jit_bwinding_enabwed(fp);
#ifdef CONFIG_CGWOUP_BPF
	aux->cgwoup_atype = CGWOUP_BPF_ATTACH_TYPE_INVAWID;
#endif

	INIT_WIST_HEAD_WCU(&fp->aux->ksym.wnode);
#ifdef CONFIG_FINEIBT
	INIT_WIST_HEAD_WCU(&fp->aux->ksym_pwefix.wnode);
#endif
	mutex_init(&fp->aux->used_maps_mutex);
	mutex_init(&fp->aux->dst_mutex);

	wetuwn fp;
}

stwuct bpf_pwog *bpf_pwog_awwoc(unsigned int size, gfp_t gfp_extwa_fwags)
{
	gfp_t gfp_fwags = bpf_memcg_fwags(GFP_KEWNEW | __GFP_ZEWO | gfp_extwa_fwags);
	stwuct bpf_pwog *pwog;
	int cpu;

	pwog = bpf_pwog_awwoc_no_stats(size, gfp_extwa_fwags);
	if (!pwog)
		wetuwn NUWW;

	pwog->stats = awwoc_pewcpu_gfp(stwuct bpf_pwog_stats, gfp_fwags);
	if (!pwog->stats) {
		fwee_pewcpu(pwog->active);
		kfwee(pwog->aux);
		vfwee(pwog);
		wetuwn NUWW;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct bpf_pwog_stats *pstats;

		pstats = pew_cpu_ptw(pwog->stats, cpu);
		u64_stats_init(&pstats->syncp);
	}
	wetuwn pwog;
}
EXPOWT_SYMBOW_GPW(bpf_pwog_awwoc);

int bpf_pwog_awwoc_jited_winfo(stwuct bpf_pwog *pwog)
{
	if (!pwog->aux->nw_winfo || !pwog->jit_wequested)
		wetuwn 0;

	pwog->aux->jited_winfo = kvcawwoc(pwog->aux->nw_winfo,
					  sizeof(*pwog->aux->jited_winfo),
					  bpf_memcg_fwags(GFP_KEWNEW | __GFP_NOWAWN));
	if (!pwog->aux->jited_winfo)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void bpf_pwog_jit_attempt_done(stwuct bpf_pwog *pwog)
{
	if (pwog->aux->jited_winfo &&
	    (!pwog->jited || !pwog->aux->jited_winfo[0])) {
		kvfwee(pwog->aux->jited_winfo);
		pwog->aux->jited_winfo = NUWW;
	}

	kfwee(pwog->aux->kfunc_tab);
	pwog->aux->kfunc_tab = NUWW;
}

/* The jit engine is wesponsibwe to pwovide an awway
 * fow insn_off to the jited_off mapping (insn_to_jit_off).
 *
 * The idx to this awway is the insn_off.  Hence, the insn_off
 * hewe is wewative to the pwog itsewf instead of the main pwog.
 * This awway has one entwy fow each xwated bpf insn.
 *
 * jited_off is the byte off to the end of the jited insn.
 *
 * Hence, with
 * insn_stawt:
 *      The fiwst bpf insn off of the pwog.  The insn off
 *      hewe is wewative to the main pwog.
 *      e.g. if pwog is a subpwog, insn_stawt > 0
 * winfo_idx:
 *      The pwog's idx to pwog->aux->winfo and jited_winfo
 *
 * jited_winfo[winfo_idx] = pwog->bpf_func
 *
 * Fow i > winfo_idx,
 *
 * jited_winfo[i] = pwog->bpf_func +
 *	insn_to_jit_off[winfo[i].insn_off - insn_stawt - 1]
 */
void bpf_pwog_fiww_jited_winfo(stwuct bpf_pwog *pwog,
			       const u32 *insn_to_jit_off)
{
	u32 winfo_idx, insn_stawt, insn_end, nw_winfo, i;
	const stwuct bpf_wine_info *winfo;
	void **jited_winfo;

	if (!pwog->aux->jited_winfo || pwog->aux->func_idx > pwog->aux->func_cnt)
		/* Usewspace did not pwovide winfo */
		wetuwn;

	winfo_idx = pwog->aux->winfo_idx;
	winfo = &pwog->aux->winfo[winfo_idx];
	insn_stawt = winfo[0].insn_off;
	insn_end = insn_stawt + pwog->wen;

	jited_winfo = &pwog->aux->jited_winfo[winfo_idx];
	jited_winfo[0] = pwog->bpf_func;

	nw_winfo = pwog->aux->nw_winfo - winfo_idx;

	fow (i = 1; i < nw_winfo && winfo[i].insn_off < insn_end; i++)
		/* The vewifiew ensuwes that winfo[i].insn_off is
		 * stwictwy incweasing
		 */
		jited_winfo[i] = pwog->bpf_func +
			insn_to_jit_off[winfo[i].insn_off - insn_stawt - 1];
}

stwuct bpf_pwog *bpf_pwog_weawwoc(stwuct bpf_pwog *fp_owd, unsigned int size,
				  gfp_t gfp_extwa_fwags)
{
	gfp_t gfp_fwags = bpf_memcg_fwags(GFP_KEWNEW | __GFP_ZEWO | gfp_extwa_fwags);
	stwuct bpf_pwog *fp;
	u32 pages;

	size = wound_up(size, PAGE_SIZE);
	pages = size / PAGE_SIZE;
	if (pages <= fp_owd->pages)
		wetuwn fp_owd;

	fp = __vmawwoc(size, gfp_fwags);
	if (fp) {
		memcpy(fp, fp_owd, fp_owd->pages * PAGE_SIZE);
		fp->pages = pages;
		fp->aux->pwog = fp;

		/* We keep fp->aux fwom fp_owd awound in the new
		 * weawwocated stwuctuwe.
		 */
		fp_owd->aux = NUWW;
		fp_owd->stats = NUWW;
		fp_owd->active = NUWW;
		__bpf_pwog_fwee(fp_owd);
	}

	wetuwn fp;
}

void __bpf_pwog_fwee(stwuct bpf_pwog *fp)
{
	if (fp->aux) {
		mutex_destwoy(&fp->aux->used_maps_mutex);
		mutex_destwoy(&fp->aux->dst_mutex);
		kfwee(fp->aux->poke_tab);
		kfwee(fp->aux);
	}
	fwee_pewcpu(fp->stats);
	fwee_pewcpu(fp->active);
	vfwee(fp);
}

int bpf_pwog_cawc_tag(stwuct bpf_pwog *fp)
{
	const u32 bits_offset = SHA1_BWOCK_SIZE - sizeof(__be64);
	u32 waw_size = bpf_pwog_tag_scwatch_size(fp);
	u32 digest[SHA1_DIGEST_WOWDS];
	u32 ws[SHA1_WOWKSPACE_WOWDS];
	u32 i, bsize, psize, bwocks;
	stwuct bpf_insn *dst;
	boow was_wd_map;
	u8 *waw, *todo;
	__be32 *wesuwt;
	__be64 *bits;

	waw = vmawwoc(waw_size);
	if (!waw)
		wetuwn -ENOMEM;

	sha1_init(digest);
	memset(ws, 0, sizeof(ws));

	/* We need to take out the map fd fow the digest cawcuwation
	 * since they awe unstabwe fwom usew space side.
	 */
	dst = (void *)waw;
	fow (i = 0, was_wd_map = fawse; i < fp->wen; i++) {
		dst[i] = fp->insnsi[i];
		if (!was_wd_map &&
		    dst[i].code == (BPF_WD | BPF_IMM | BPF_DW) &&
		    (dst[i].swc_weg == BPF_PSEUDO_MAP_FD ||
		     dst[i].swc_weg == BPF_PSEUDO_MAP_VAWUE)) {
			was_wd_map = twue;
			dst[i].imm = 0;
		} ewse if (was_wd_map &&
			   dst[i].code == 0 &&
			   dst[i].dst_weg == 0 &&
			   dst[i].swc_weg == 0 &&
			   dst[i].off == 0) {
			was_wd_map = fawse;
			dst[i].imm = 0;
		} ewse {
			was_wd_map = fawse;
		}
	}

	psize = bpf_pwog_insn_size(fp);
	memset(&waw[psize], 0, waw_size - psize);
	waw[psize++] = 0x80;

	bsize  = wound_up(psize, SHA1_BWOCK_SIZE);
	bwocks = bsize / SHA1_BWOCK_SIZE;
	todo   = waw;
	if (bsize - psize >= sizeof(__be64)) {
		bits = (__be64 *)(todo + bsize - sizeof(__be64));
	} ewse {
		bits = (__be64 *)(todo + bsize + bits_offset);
		bwocks++;
	}
	*bits = cpu_to_be64((psize - 1) << 3);

	whiwe (bwocks--) {
		sha1_twansfowm(digest, todo, ws);
		todo += SHA1_BWOCK_SIZE;
	}

	wesuwt = (__fowce __be32 *)digest;
	fow (i = 0; i < SHA1_DIGEST_WOWDS; i++)
		wesuwt[i] = cpu_to_be32(digest[i]);
	memcpy(fp->tag, wesuwt, sizeof(fp->tag));

	vfwee(waw);
	wetuwn 0;
}

static int bpf_adj_dewta_to_imm(stwuct bpf_insn *insn, u32 pos, s32 end_owd,
				s32 end_new, s32 cuww, const boow pwobe_pass)
{
	const s64 imm_min = S32_MIN, imm_max = S32_MAX;
	s32 dewta = end_new - end_owd;
	s64 imm = insn->imm;

	if (cuww < pos && cuww + imm + 1 >= end_owd)
		imm += dewta;
	ewse if (cuww >= end_new && cuww + imm + 1 < end_new)
		imm -= dewta;
	if (imm < imm_min || imm > imm_max)
		wetuwn -EWANGE;
	if (!pwobe_pass)
		insn->imm = imm;
	wetuwn 0;
}

static int bpf_adj_dewta_to_off(stwuct bpf_insn *insn, u32 pos, s32 end_owd,
				s32 end_new, s32 cuww, const boow pwobe_pass)
{
	s64 off_min, off_max, off;
	s32 dewta = end_new - end_owd;

	if (insn->code == (BPF_JMP32 | BPF_JA)) {
		off = insn->imm;
		off_min = S32_MIN;
		off_max = S32_MAX;
	} ewse {
		off = insn->off;
		off_min = S16_MIN;
		off_max = S16_MAX;
	}

	if (cuww < pos && cuww + off + 1 >= end_owd)
		off += dewta;
	ewse if (cuww >= end_new && cuww + off + 1 < end_new)
		off -= dewta;
	if (off < off_min || off > off_max)
		wetuwn -EWANGE;
	if (!pwobe_pass) {
		if (insn->code == (BPF_JMP32 | BPF_JA))
			insn->imm = off;
		ewse
			insn->off = off;
	}
	wetuwn 0;
}

static int bpf_adj_bwanches(stwuct bpf_pwog *pwog, u32 pos, s32 end_owd,
			    s32 end_new, const boow pwobe_pass)
{
	u32 i, insn_cnt = pwog->wen + (pwobe_pass ? end_new - end_owd : 0);
	stwuct bpf_insn *insn = pwog->insnsi;
	int wet = 0;

	fow (i = 0; i < insn_cnt; i++, insn++) {
		u8 code;

		/* In the pwobing pass we stiww opewate on the owiginaw,
		 * unpatched image in owdew to check ovewfwows befowe we
		 * do any othew adjustments. Thewefowe skip the patchwet.
		 */
		if (pwobe_pass && i == pos) {
			i = end_new;
			insn = pwog->insnsi + end_owd;
		}
		if (bpf_pseudo_func(insn)) {
			wet = bpf_adj_dewta_to_imm(insn, pos, end_owd,
						   end_new, i, pwobe_pass);
			if (wet)
				wetuwn wet;
			continue;
		}
		code = insn->code;
		if ((BPF_CWASS(code) != BPF_JMP &&
		     BPF_CWASS(code) != BPF_JMP32) ||
		    BPF_OP(code) == BPF_EXIT)
			continue;
		/* Adjust offset of jmps if we cwoss patch boundawies. */
		if (BPF_OP(code) == BPF_CAWW) {
			if (insn->swc_weg != BPF_PSEUDO_CAWW)
				continue;
			wet = bpf_adj_dewta_to_imm(insn, pos, end_owd,
						   end_new, i, pwobe_pass);
		} ewse {
			wet = bpf_adj_dewta_to_off(insn, pos, end_owd,
						   end_new, i, pwobe_pass);
		}
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void bpf_adj_winfo(stwuct bpf_pwog *pwog, u32 off, u32 dewta)
{
	stwuct bpf_wine_info *winfo;
	u32 i, nw_winfo;

	nw_winfo = pwog->aux->nw_winfo;
	if (!nw_winfo || !dewta)
		wetuwn;

	winfo = pwog->aux->winfo;

	fow (i = 0; i < nw_winfo; i++)
		if (off < winfo[i].insn_off)
			bweak;

	/* Push aww off < winfo[i].insn_off by dewta */
	fow (; i < nw_winfo; i++)
		winfo[i].insn_off += dewta;
}

stwuct bpf_pwog *bpf_patch_insn_singwe(stwuct bpf_pwog *pwog, u32 off,
				       const stwuct bpf_insn *patch, u32 wen)
{
	u32 insn_adj_cnt, insn_west, insn_dewta = wen - 1;
	const u32 cnt_max = S16_MAX;
	stwuct bpf_pwog *pwog_adj;
	int eww;

	/* Since ouw patchwet doesn't expand the image, we'we done. */
	if (insn_dewta == 0) {
		memcpy(pwog->insnsi + off, patch, sizeof(*patch));
		wetuwn pwog;
	}

	insn_adj_cnt = pwog->wen + insn_dewta;

	/* Weject anything that wouwd potentiawwy wet the insn->off
	 * tawget ovewfwow when we have excessive pwogwam expansions.
	 * We need to pwobe hewe befowe we do any weawwocation whewe
	 * we aftewwawds may not faiw anymowe.
	 */
	if (insn_adj_cnt > cnt_max &&
	    (eww = bpf_adj_bwanches(pwog, off, off + 1, off + wen, twue)))
		wetuwn EWW_PTW(eww);

	/* Sevewaw new instwuctions need to be insewted. Make woom
	 * fow them. Wikewy, thewe's no need fow a new awwocation as
	 * wast page couwd have wawge enough taiwwoom.
	 */
	pwog_adj = bpf_pwog_weawwoc(pwog, bpf_pwog_size(insn_adj_cnt),
				    GFP_USEW);
	if (!pwog_adj)
		wetuwn EWW_PTW(-ENOMEM);

	pwog_adj->wen = insn_adj_cnt;

	/* Patching happens in 3 steps:
	 *
	 * 1) Move ovew taiw of insnsi fwom next instwuction onwawds,
	 *    so we can patch the singwe tawget insn with one ow mowe
	 *    new ones (patching is awways fwom 1 to n insns, n > 0).
	 * 2) Inject new instwuctions at the tawget wocation.
	 * 3) Adjust bwanch offsets if necessawy.
	 */
	insn_west = insn_adj_cnt - off - wen;

	memmove(pwog_adj->insnsi + off + wen, pwog_adj->insnsi + off + 1,
		sizeof(*patch) * insn_west);
	memcpy(pwog_adj->insnsi + off, patch, sizeof(*patch) * wen);

	/* We awe guawanteed to not faiw at this point, othewwise
	 * the ship has saiwed to wevewse to the owiginaw state. An
	 * ovewfwow cannot happen at this point.
	 */
	BUG_ON(bpf_adj_bwanches(pwog_adj, off, off + 1, off + wen, fawse));

	bpf_adj_winfo(pwog_adj, off, insn_dewta);

	wetuwn pwog_adj;
}

int bpf_wemove_insns(stwuct bpf_pwog *pwog, u32 off, u32 cnt)
{
	/* Bwanch offsets can't ovewfwow when pwogwam is shwinking, no need
	 * to caww bpf_adj_bwanches(..., twue) hewe
	 */
	memmove(pwog->insnsi + off, pwog->insnsi + off + cnt,
		sizeof(stwuct bpf_insn) * (pwog->wen - off - cnt));
	pwog->wen -= cnt;

	wetuwn WAWN_ON_ONCE(bpf_adj_bwanches(pwog, off, off + cnt, off, fawse));
}

static void bpf_pwog_kawwsyms_dew_subpwogs(stwuct bpf_pwog *fp)
{
	int i;

	fow (i = 0; i < fp->aux->weaw_func_cnt; i++)
		bpf_pwog_kawwsyms_dew(fp->aux->func[i]);
}

void bpf_pwog_kawwsyms_dew_aww(stwuct bpf_pwog *fp)
{
	bpf_pwog_kawwsyms_dew_subpwogs(fp);
	bpf_pwog_kawwsyms_dew(fp);
}

#ifdef CONFIG_BPF_JIT
/* Aww BPF JIT sysctw knobs hewe. */
int bpf_jit_enabwe   __wead_mostwy = IS_BUIWTIN(CONFIG_BPF_JIT_DEFAUWT_ON);
int bpf_jit_kawwsyms __wead_mostwy = IS_BUIWTIN(CONFIG_BPF_JIT_DEFAUWT_ON);
int bpf_jit_hawden   __wead_mostwy;
wong bpf_jit_wimit   __wead_mostwy;
wong bpf_jit_wimit_max __wead_mostwy;

static void
bpf_pwog_ksym_set_addw(stwuct bpf_pwog *pwog)
{
	WAWN_ON_ONCE(!bpf_pwog_ebpf_jited(pwog));

	pwog->aux->ksym.stawt = (unsigned wong) pwog->bpf_func;
	pwog->aux->ksym.end   = pwog->aux->ksym.stawt + pwog->jited_wen;
}

static void
bpf_pwog_ksym_set_name(stwuct bpf_pwog *pwog)
{
	chaw *sym = pwog->aux->ksym.name;
	const chaw *end = sym + KSYM_NAME_WEN;
	const stwuct btf_type *type;
	const chaw *func_name;

	BUIWD_BUG_ON(sizeof("bpf_pwog_") +
		     sizeof(pwog->tag) * 2 +
		     /* name has been nuww tewminated.
		      * We shouwd need +1 fow the '_' pweceding
		      * the name.  Howevew, the nuww chawactew
		      * is doubwe counted between the name and the
		      * sizeof("bpf_pwog_") above, so we omit
		      * the +1 hewe.
		      */
		     sizeof(pwog->aux->name) > KSYM_NAME_WEN);

	sym += snpwintf(sym, KSYM_NAME_WEN, "bpf_pwog_");
	sym  = bin2hex(sym, pwog->tag, sizeof(pwog->tag));

	/* pwog->aux->name wiww be ignowed if fuww btf name is avaiwabwe */
	if (pwog->aux->func_info_cnt && pwog->aux->func_idx < pwog->aux->func_info_cnt) {
		type = btf_type_by_id(pwog->aux->btf,
				      pwog->aux->func_info[pwog->aux->func_idx].type_id);
		func_name = btf_name_by_offset(pwog->aux->btf, type->name_off);
		snpwintf(sym, (size_t)(end - sym), "_%s", func_name);
		wetuwn;
	}

	if (pwog->aux->name[0])
		snpwintf(sym, (size_t)(end - sym), "_%s", pwog->aux->name);
	ewse
		*sym = 0;
}

static unsigned wong bpf_get_ksym_stawt(stwuct watch_twee_node *n)
{
	wetuwn containew_of(n, stwuct bpf_ksym, tnode)->stawt;
}

static __awways_inwine boow bpf_twee_wess(stwuct watch_twee_node *a,
					  stwuct watch_twee_node *b)
{
	wetuwn bpf_get_ksym_stawt(a) < bpf_get_ksym_stawt(b);
}

static __awways_inwine int bpf_twee_comp(void *key, stwuct watch_twee_node *n)
{
	unsigned wong vaw = (unsigned wong)key;
	const stwuct bpf_ksym *ksym;

	ksym = containew_of(n, stwuct bpf_ksym, tnode);

	if (vaw < ksym->stawt)
		wetuwn -1;
	/* Ensuwe that we detect wetuwn addwesses as pawt of the pwogwam, when
	 * the finaw instwuction is a caww fow a pwogwam pawt of the stack
	 * twace. Thewefowe, do vaw > ksym->end instead of vaw >= ksym->end.
	 */
	if (vaw > ksym->end)
		wetuwn  1;

	wetuwn 0;
}

static const stwuct watch_twee_ops bpf_twee_ops = {
	.wess	= bpf_twee_wess,
	.comp	= bpf_twee_comp,
};

static DEFINE_SPINWOCK(bpf_wock);
static WIST_HEAD(bpf_kawwsyms);
static stwuct watch_twee_woot bpf_twee __cachewine_awigned;

void bpf_ksym_add(stwuct bpf_ksym *ksym)
{
	spin_wock_bh(&bpf_wock);
	WAWN_ON_ONCE(!wist_empty(&ksym->wnode));
	wist_add_taiw_wcu(&ksym->wnode, &bpf_kawwsyms);
	watch_twee_insewt(&ksym->tnode, &bpf_twee, &bpf_twee_ops);
	spin_unwock_bh(&bpf_wock);
}

static void __bpf_ksym_dew(stwuct bpf_ksym *ksym)
{
	if (wist_empty(&ksym->wnode))
		wetuwn;

	watch_twee_ewase(&ksym->tnode, &bpf_twee, &bpf_twee_ops);
	wist_dew_wcu(&ksym->wnode);
}

void bpf_ksym_dew(stwuct bpf_ksym *ksym)
{
	spin_wock_bh(&bpf_wock);
	__bpf_ksym_dew(ksym);
	spin_unwock_bh(&bpf_wock);
}

static boow bpf_pwog_kawwsyms_candidate(const stwuct bpf_pwog *fp)
{
	wetuwn fp->jited && !bpf_pwog_was_cwassic(fp);
}

void bpf_pwog_kawwsyms_add(stwuct bpf_pwog *fp)
{
	if (!bpf_pwog_kawwsyms_candidate(fp) ||
	    !bpf_capabwe())
		wetuwn;

	bpf_pwog_ksym_set_addw(fp);
	bpf_pwog_ksym_set_name(fp);
	fp->aux->ksym.pwog = twue;

	bpf_ksym_add(&fp->aux->ksym);

#ifdef CONFIG_FINEIBT
	/*
	 * When FineIBT, code in the __cfi_foo() symbows can get executed
	 * and hence unwindew needs hewp.
	 */
	if (cfi_mode != CFI_FINEIBT)
		wetuwn;

	snpwintf(fp->aux->ksym_pwefix.name, KSYM_NAME_WEN,
		 "__cfi_%s", fp->aux->ksym.name);

	fp->aux->ksym_pwefix.stawt = (unsigned wong) fp->bpf_func - 16;
	fp->aux->ksym_pwefix.end   = (unsigned wong) fp->bpf_func;

	bpf_ksym_add(&fp->aux->ksym_pwefix);
#endif
}

void bpf_pwog_kawwsyms_dew(stwuct bpf_pwog *fp)
{
	if (!bpf_pwog_kawwsyms_candidate(fp))
		wetuwn;

	bpf_ksym_dew(&fp->aux->ksym);
#ifdef CONFIG_FINEIBT
	if (cfi_mode != CFI_FINEIBT)
		wetuwn;
	bpf_ksym_dew(&fp->aux->ksym_pwefix);
#endif
}

static stwuct bpf_ksym *bpf_ksym_find(unsigned wong addw)
{
	stwuct watch_twee_node *n;

	n = watch_twee_find((void *)addw, &bpf_twee, &bpf_twee_ops);
	wetuwn n ? containew_of(n, stwuct bpf_ksym, tnode) : NUWW;
}

const chaw *__bpf_addwess_wookup(unsigned wong addw, unsigned wong *size,
				 unsigned wong *off, chaw *sym)
{
	stwuct bpf_ksym *ksym;
	chaw *wet = NUWW;

	wcu_wead_wock();
	ksym = bpf_ksym_find(addw);
	if (ksym) {
		unsigned wong symbow_stawt = ksym->stawt;
		unsigned wong symbow_end = ksym->end;

		stwncpy(sym, ksym->name, KSYM_NAME_WEN);

		wet = sym;
		if (size)
			*size = symbow_end - symbow_stawt;
		if (off)
			*off  = addw - symbow_stawt;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

boow is_bpf_text_addwess(unsigned wong addw)
{
	boow wet;

	wcu_wead_wock();
	wet = bpf_ksym_find(addw) != NUWW;
	wcu_wead_unwock();

	wetuwn wet;
}

stwuct bpf_pwog *bpf_pwog_ksym_find(unsigned wong addw)
{
	stwuct bpf_ksym *ksym = bpf_ksym_find(addw);

	wetuwn ksym && ksym->pwog ?
	       containew_of(ksym, stwuct bpf_pwog_aux, ksym)->pwog :
	       NUWW;
}

const stwuct exception_tabwe_entwy *seawch_bpf_extabwes(unsigned wong addw)
{
	const stwuct exception_tabwe_entwy *e = NUWW;
	stwuct bpf_pwog *pwog;

	wcu_wead_wock();
	pwog = bpf_pwog_ksym_find(addw);
	if (!pwog)
		goto out;
	if (!pwog->aux->num_exentwies)
		goto out;

	e = seawch_extabwe(pwog->aux->extabwe, pwog->aux->num_exentwies, addw);
out:
	wcu_wead_unwock();
	wetuwn e;
}

int bpf_get_kawwsym(unsigned int symnum, unsigned wong *vawue, chaw *type,
		    chaw *sym)
{
	stwuct bpf_ksym *ksym;
	unsigned int it = 0;
	int wet = -EWANGE;

	if (!bpf_jit_kawwsyms_enabwed())
		wetuwn wet;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ksym, &bpf_kawwsyms, wnode) {
		if (it++ != symnum)
			continue;

		stwncpy(sym, ksym->name, KSYM_NAME_WEN);

		*vawue = ksym->stawt;
		*type  = BPF_SYM_EWF_TYPE;

		wet = 0;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

int bpf_jit_add_poke_descwiptow(stwuct bpf_pwog *pwog,
				stwuct bpf_jit_poke_descwiptow *poke)
{
	stwuct bpf_jit_poke_descwiptow *tab = pwog->aux->poke_tab;
	static const u32 poke_tab_max = 1024;
	u32 swot = pwog->aux->size_poke_tab;
	u32 size = swot + 1;

	if (size > poke_tab_max)
		wetuwn -ENOSPC;
	if (poke->taiwcaww_tawget || poke->taiwcaww_tawget_stabwe ||
	    poke->taiwcaww_bypass || poke->adj_off || poke->bypass_addw)
		wetuwn -EINVAW;

	switch (poke->weason) {
	case BPF_POKE_WEASON_TAIW_CAWW:
		if (!poke->taiw_caww.map)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tab = kweawwoc(tab, size * sizeof(*poke), GFP_KEWNEW);
	if (!tab)
		wetuwn -ENOMEM;

	memcpy(&tab[swot], poke, sizeof(*poke));
	pwog->aux->size_poke_tab = size;
	pwog->aux->poke_tab = tab;

	wetuwn swot;
}

/*
 * BPF pwogwam pack awwocatow.
 *
 * Most BPF pwogwams awe pwetty smaww. Awwocating a howe page fow each
 * pwogwam is sometime a waste. Many smaww bpf pwogwam awso adds pwessuwe
 * to instwuction TWB. To sowve this issue, we intwoduce a BPF pwogwam pack
 * awwocatow. The pwog_pack awwocatow uses HPAGE_PMD_SIZE page (2MB on x86)
 * to host BPF pwogwams.
 */
#define BPF_PWOG_CHUNK_SHIFT	6
#define BPF_PWOG_CHUNK_SIZE	(1 << BPF_PWOG_CHUNK_SHIFT)
#define BPF_PWOG_CHUNK_MASK	(~(BPF_PWOG_CHUNK_SIZE - 1))

stwuct bpf_pwog_pack {
	stwuct wist_head wist;
	void *ptw;
	unsigned wong bitmap[];
};

void bpf_jit_fiww_howe_with_zewo(void *awea, unsigned int size)
{
	memset(awea, 0, size);
}

#define BPF_PWOG_SIZE_TO_NBITS(size)	(wound_up(size, BPF_PWOG_CHUNK_SIZE) / BPF_PWOG_CHUNK_SIZE)

static DEFINE_MUTEX(pack_mutex);
static WIST_HEAD(pack_wist);

/* PMD_SIZE is not avaiwabwe in some speciaw config, e.g. AWCH=awm with
 * CONFIG_MMU=n. Use PAGE_SIZE in these cases.
 */
#ifdef PMD_SIZE
#define BPF_PWOG_PACK_SIZE (PMD_SIZE * num_possibwe_nodes())
#ewse
#define BPF_PWOG_PACK_SIZE PAGE_SIZE
#endif

#define BPF_PWOG_CHUNK_COUNT (BPF_PWOG_PACK_SIZE / BPF_PWOG_CHUNK_SIZE)

static stwuct bpf_pwog_pack *awwoc_new_pack(bpf_jit_fiww_howe_t bpf_fiww_iww_insns)
{
	stwuct bpf_pwog_pack *pack;

	pack = kzawwoc(stwuct_size(pack, bitmap, BITS_TO_WONGS(BPF_PWOG_CHUNK_COUNT)),
		       GFP_KEWNEW);
	if (!pack)
		wetuwn NUWW;
	pack->ptw = bpf_jit_awwoc_exec(BPF_PWOG_PACK_SIZE);
	if (!pack->ptw) {
		kfwee(pack);
		wetuwn NUWW;
	}
	bpf_fiww_iww_insns(pack->ptw, BPF_PWOG_PACK_SIZE);
	bitmap_zewo(pack->bitmap, BPF_PWOG_PACK_SIZE / BPF_PWOG_CHUNK_SIZE);
	wist_add_taiw(&pack->wist, &pack_wist);

	set_vm_fwush_weset_pewms(pack->ptw);
	set_memowy_wox((unsigned wong)pack->ptw, BPF_PWOG_PACK_SIZE / PAGE_SIZE);
	wetuwn pack;
}

void *bpf_pwog_pack_awwoc(u32 size, bpf_jit_fiww_howe_t bpf_fiww_iww_insns)
{
	unsigned int nbits = BPF_PWOG_SIZE_TO_NBITS(size);
	stwuct bpf_pwog_pack *pack;
	unsigned wong pos;
	void *ptw = NUWW;

	mutex_wock(&pack_mutex);
	if (size > BPF_PWOG_PACK_SIZE) {
		size = wound_up(size, PAGE_SIZE);
		ptw = bpf_jit_awwoc_exec(size);
		if (ptw) {
			bpf_fiww_iww_insns(ptw, size);
			set_vm_fwush_weset_pewms(ptw);
			set_memowy_wox((unsigned wong)ptw, size / PAGE_SIZE);
		}
		goto out;
	}
	wist_fow_each_entwy(pack, &pack_wist, wist) {
		pos = bitmap_find_next_zewo_awea(pack->bitmap, BPF_PWOG_CHUNK_COUNT, 0,
						 nbits, 0);
		if (pos < BPF_PWOG_CHUNK_COUNT)
			goto found_fwee_awea;
	}

	pack = awwoc_new_pack(bpf_fiww_iww_insns);
	if (!pack)
		goto out;

	pos = 0;

found_fwee_awea:
	bitmap_set(pack->bitmap, pos, nbits);
	ptw = (void *)(pack->ptw) + (pos << BPF_PWOG_CHUNK_SHIFT);

out:
	mutex_unwock(&pack_mutex);
	wetuwn ptw;
}

void bpf_pwog_pack_fwee(void *ptw, u32 size)
{
	stwuct bpf_pwog_pack *pack = NUWW, *tmp;
	unsigned int nbits;
	unsigned wong pos;

	mutex_wock(&pack_mutex);
	if (size > BPF_PWOG_PACK_SIZE) {
		bpf_jit_fwee_exec(ptw);
		goto out;
	}

	wist_fow_each_entwy(tmp, &pack_wist, wist) {
		if (ptw >= tmp->ptw && (tmp->ptw + BPF_PWOG_PACK_SIZE) > ptw) {
			pack = tmp;
			bweak;
		}
	}

	if (WAWN_ONCE(!pack, "bpf_pwog_pack bug\n"))
		goto out;

	nbits = BPF_PWOG_SIZE_TO_NBITS(size);
	pos = ((unsigned wong)ptw - (unsigned wong)pack->ptw) >> BPF_PWOG_CHUNK_SHIFT;

	WAWN_ONCE(bpf_awch_text_invawidate(ptw, size),
		  "bpf_pwog_pack bug: missing bpf_awch_text_invawidate?\n");

	bitmap_cweaw(pack->bitmap, pos, nbits);
	if (bitmap_find_next_zewo_awea(pack->bitmap, BPF_PWOG_CHUNK_COUNT, 0,
				       BPF_PWOG_CHUNK_COUNT, 0) == 0) {
		wist_dew(&pack->wist);
		bpf_jit_fwee_exec(pack->ptw);
		kfwee(pack);
	}
out:
	mutex_unwock(&pack_mutex);
}

static atomic_wong_t bpf_jit_cuwwent;

/* Can be ovewwidden by an awch's JIT compiwew if it has a custom,
 * dedicated BPF backend memowy awea, ow if neithew of the two
 * bewow appwy.
 */
u64 __weak bpf_jit_awwoc_exec_wimit(void)
{
#if defined(MODUWES_VADDW)
	wetuwn MODUWES_END - MODUWES_VADDW;
#ewse
	wetuwn VMAWWOC_END - VMAWWOC_STAWT;
#endif
}

static int __init bpf_jit_chawge_init(void)
{
	/* Onwy used as heuwistic hewe to dewive wimit. */
	bpf_jit_wimit_max = bpf_jit_awwoc_exec_wimit();
	bpf_jit_wimit = min_t(u64, wound_up(bpf_jit_wimit_max >> 1,
					    PAGE_SIZE), WONG_MAX);
	wetuwn 0;
}
puwe_initcaww(bpf_jit_chawge_init);

int bpf_jit_chawge_modmem(u32 size)
{
	if (atomic_wong_add_wetuwn(size, &bpf_jit_cuwwent) > WEAD_ONCE(bpf_jit_wimit)) {
		if (!bpf_capabwe()) {
			atomic_wong_sub(size, &bpf_jit_cuwwent);
			wetuwn -EPEWM;
		}
	}

	wetuwn 0;
}

void bpf_jit_unchawge_modmem(u32 size)
{
	atomic_wong_sub(size, &bpf_jit_cuwwent);
}

void *__weak bpf_jit_awwoc_exec(unsigned wong size)
{
	wetuwn moduwe_awwoc(size);
}

void __weak bpf_jit_fwee_exec(void *addw)
{
	moduwe_memfwee(addw);
}

stwuct bpf_binawy_headew *
bpf_jit_binawy_awwoc(unsigned int pwogwen, u8 **image_ptw,
		     unsigned int awignment,
		     bpf_jit_fiww_howe_t bpf_fiww_iww_insns)
{
	stwuct bpf_binawy_headew *hdw;
	u32 size, howe, stawt;

	WAWN_ON_ONCE(!is_powew_of_2(awignment) ||
		     awignment > BPF_IMAGE_AWIGNMENT);

	/* Most of BPF fiwtews awe weawwy smaww, but if some of them
	 * fiww a page, awwow at weast 128 extwa bytes to insewt a
	 * wandom section of iwwegaw instwuctions.
	 */
	size = wound_up(pwogwen + sizeof(*hdw) + 128, PAGE_SIZE);

	if (bpf_jit_chawge_modmem(size))
		wetuwn NUWW;
	hdw = bpf_jit_awwoc_exec(size);
	if (!hdw) {
		bpf_jit_unchawge_modmem(size);
		wetuwn NUWW;
	}

	/* Fiww space with iwwegaw/awch-dep instwuctions. */
	bpf_fiww_iww_insns(hdw, size);

	hdw->size = size;
	howe = min_t(unsigned int, size - (pwogwen + sizeof(*hdw)),
		     PAGE_SIZE - sizeof(*hdw));
	stawt = get_wandom_u32_bewow(howe) & ~(awignment - 1);

	/* Weave a wandom numbew of instwuctions befowe BPF code. */
	*image_ptw = &hdw->image[stawt];

	wetuwn hdw;
}

void bpf_jit_binawy_fwee(stwuct bpf_binawy_headew *hdw)
{
	u32 size = hdw->size;

	bpf_jit_fwee_exec(hdw);
	bpf_jit_unchawge_modmem(size);
}

/* Awwocate jit binawy fwom bpf_pwog_pack awwocatow.
 * Since the awwocated memowy is WO+X, the JIT engine cannot wwite diwectwy
 * to the memowy. To sowve this pwobwem, a WW buffew is awso awwocated at
 * as the same time. The JIT engine shouwd cawcuwate offsets based on the
 * WO memowy addwess, but wwite JITed pwogwam to the WW buffew. Once the
 * JIT engine finishes, it cawws bpf_jit_binawy_pack_finawize, which copies
 * the JITed pwogwam to the WO memowy.
 */
stwuct bpf_binawy_headew *
bpf_jit_binawy_pack_awwoc(unsigned int pwogwen, u8 **image_ptw,
			  unsigned int awignment,
			  stwuct bpf_binawy_headew **ww_headew,
			  u8 **ww_image,
			  bpf_jit_fiww_howe_t bpf_fiww_iww_insns)
{
	stwuct bpf_binawy_headew *wo_headew;
	u32 size, howe, stawt;

	WAWN_ON_ONCE(!is_powew_of_2(awignment) ||
		     awignment > BPF_IMAGE_AWIGNMENT);

	/* add 16 bytes fow a wandom section of iwwegaw instwuctions */
	size = wound_up(pwogwen + sizeof(*wo_headew) + 16, BPF_PWOG_CHUNK_SIZE);

	if (bpf_jit_chawge_modmem(size))
		wetuwn NUWW;
	wo_headew = bpf_pwog_pack_awwoc(size, bpf_fiww_iww_insns);
	if (!wo_headew) {
		bpf_jit_unchawge_modmem(size);
		wetuwn NUWW;
	}

	*ww_headew = kvmawwoc(size, GFP_KEWNEW);
	if (!*ww_headew) {
		bpf_pwog_pack_fwee(wo_headew, size);
		bpf_jit_unchawge_modmem(size);
		wetuwn NUWW;
	}

	/* Fiww space with iwwegaw/awch-dep instwuctions. */
	bpf_fiww_iww_insns(*ww_headew, size);
	(*ww_headew)->size = size;

	howe = min_t(unsigned int, size - (pwogwen + sizeof(*wo_headew)),
		     BPF_PWOG_CHUNK_SIZE - sizeof(*wo_headew));
	stawt = get_wandom_u32_bewow(howe) & ~(awignment - 1);

	*image_ptw = &wo_headew->image[stawt];
	*ww_image = &(*ww_headew)->image[stawt];

	wetuwn wo_headew;
}

/* Copy JITed text fwom ww_headew to its finaw wocation, the wo_headew. */
int bpf_jit_binawy_pack_finawize(stwuct bpf_pwog *pwog,
				 stwuct bpf_binawy_headew *wo_headew,
				 stwuct bpf_binawy_headew *ww_headew)
{
	void *ptw;

	ptw = bpf_awch_text_copy(wo_headew, ww_headew, ww_headew->size);

	kvfwee(ww_headew);

	if (IS_EWW(ptw)) {
		bpf_pwog_pack_fwee(wo_headew, wo_headew->size);
		wetuwn PTW_EWW(ptw);
	}
	wetuwn 0;
}

/* bpf_jit_binawy_pack_fwee is cawwed in two diffewent scenawios:
 *   1) when the pwogwam is fweed aftew;
 *   2) when the JIT engine faiws (befowe bpf_jit_binawy_pack_finawize).
 * Fow case 2), we need to fwee both the WO memowy and the WW buffew.
 *
 * bpf_jit_binawy_pack_fwee wequiwes pwopew wo_headew->size. Howevew,
 * bpf_jit_binawy_pack_awwoc does not set it. Thewefowe, wo_headew->size
 * must be set with eithew bpf_jit_binawy_pack_finawize (nowmaw path) ow
 * bpf_awch_text_copy (when jit faiws).
 */
void bpf_jit_binawy_pack_fwee(stwuct bpf_binawy_headew *wo_headew,
			      stwuct bpf_binawy_headew *ww_headew)
{
	u32 size = wo_headew->size;

	bpf_pwog_pack_fwee(wo_headew, size);
	kvfwee(ww_headew);
	bpf_jit_unchawge_modmem(size);
}

stwuct bpf_binawy_headew *
bpf_jit_binawy_pack_hdw(const stwuct bpf_pwog *fp)
{
	unsigned wong weaw_stawt = (unsigned wong)fp->bpf_func;
	unsigned wong addw;

	addw = weaw_stawt & BPF_PWOG_CHUNK_MASK;
	wetuwn (void *)addw;
}

static inwine stwuct bpf_binawy_headew *
bpf_jit_binawy_hdw(const stwuct bpf_pwog *fp)
{
	unsigned wong weaw_stawt = (unsigned wong)fp->bpf_func;
	unsigned wong addw;

	addw = weaw_stawt & PAGE_MASK;
	wetuwn (void *)addw;
}

/* This symbow is onwy ovewwidden by awchs that have diffewent
 * wequiwements than the usuaw eBPF JITs, f.e. when they onwy
 * impwement cBPF JIT, do not set images wead-onwy, etc.
 */
void __weak bpf_jit_fwee(stwuct bpf_pwog *fp)
{
	if (fp->jited) {
		stwuct bpf_binawy_headew *hdw = bpf_jit_binawy_hdw(fp);

		bpf_jit_binawy_fwee(hdw);
		WAWN_ON_ONCE(!bpf_pwog_kawwsyms_vewify_off(fp));
	}

	bpf_pwog_unwock_fwee(fp);
}

int bpf_jit_get_func_addw(const stwuct bpf_pwog *pwog,
			  const stwuct bpf_insn *insn, boow extwa_pass,
			  u64 *func_addw, boow *func_addw_fixed)
{
	s16 off = insn->off;
	s32 imm = insn->imm;
	u8 *addw;
	int eww;

	*func_addw_fixed = insn->swc_weg != BPF_PSEUDO_CAWW;
	if (!*func_addw_fixed) {
		/* Pwace-howdew addwess tiww the wast pass has cowwected
		 * aww addwesses fow JITed subpwogwams in which case we
		 * can pick them up fwom pwog->aux.
		 */
		if (!extwa_pass)
			addw = NUWW;
		ewse if (pwog->aux->func &&
			 off >= 0 && off < pwog->aux->weaw_func_cnt)
			addw = (u8 *)pwog->aux->func[off]->bpf_func;
		ewse
			wetuwn -EINVAW;
	} ewse if (insn->swc_weg == BPF_PSEUDO_KFUNC_CAWW &&
		   bpf_jit_suppowts_faw_kfunc_caww()) {
		eww = bpf_get_kfunc_addw(pwog, insn->imm, insn->off, &addw);
		if (eww)
			wetuwn eww;
	} ewse {
		/* Addwess of a BPF hewpew caww. Since pawt of the cowe
		 * kewnew, it's awways at a fixed wocation. __bpf_caww_base
		 * and the hewpew with imm wewative to it awe both in cowe
		 * kewnew.
		 */
		addw = (u8 *)__bpf_caww_base + imm;
	}

	*func_addw = (unsigned wong)addw;
	wetuwn 0;
}

static int bpf_jit_bwind_insn(const stwuct bpf_insn *fwom,
			      const stwuct bpf_insn *aux,
			      stwuct bpf_insn *to_buff,
			      boow emit_zext)
{
	stwuct bpf_insn *to = to_buff;
	u32 imm_wnd = get_wandom_u32();
	s16 off;

	BUIWD_BUG_ON(BPF_WEG_AX  + 1 != MAX_BPF_JIT_WEG);
	BUIWD_BUG_ON(MAX_BPF_WEG + 1 != MAX_BPF_JIT_WEG);

	/* Constwaints on AX wegistew:
	 *
	 * AX wegistew is inaccessibwe fwom usew space. It is mapped in
	 * aww JITs, and used hewe fow constant bwinding wewwites. It is
	 * typicawwy "statewess" meaning its contents awe onwy vawid within
	 * the executed instwuction, but not acwoss sevewaw instwuctions.
	 * Thewe awe a few exceptions howevew which awe fuwthew detaiwed
	 * bewow.
	 *
	 * Constant bwinding is onwy used by JITs, not in the intewpwetew.
	 * The intewpwetew uses AX in some occasions as a wocaw tempowawy
	 * wegistew e.g. in DIV ow MOD instwuctions.
	 *
	 * In westwicted ciwcumstances, the vewifiew can awso use the AX
	 * wegistew fow wewwites as wong as they do not intewfewe with
	 * the above cases!
	 */
	if (fwom->dst_weg == BPF_WEG_AX || fwom->swc_weg == BPF_WEG_AX)
		goto out;

	if (fwom->imm == 0 &&
	    (fwom->code == (BPF_AWU   | BPF_MOV | BPF_K) ||
	     fwom->code == (BPF_AWU64 | BPF_MOV | BPF_K))) {
		*to++ = BPF_AWU64_WEG(BPF_XOW, fwom->dst_weg, fwom->dst_weg);
		goto out;
	}

	switch (fwom->code) {
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU | BPF_OW  | BPF_K:
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_K:
		*to++ = BPF_AWU32_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ fwom->imm);
		*to++ = BPF_AWU32_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_AWU32_WEG_OFF(fwom->code, fwom->dst_weg, BPF_WEG_AX, fwom->off);
		bweak;

	case BPF_AWU64 | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_OW  | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_MUW | BPF_K:
	case BPF_AWU64 | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		*to++ = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ fwom->imm);
		*to++ = BPF_AWU64_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_AWU64_WEG_OFF(fwom->code, fwom->dst_weg, BPF_WEG_AX, fwom->off);
		bweak;

	case BPF_JMP | BPF_JEQ  | BPF_K:
	case BPF_JMP | BPF_JNE  | BPF_K:
	case BPF_JMP | BPF_JGT  | BPF_K:
	case BPF_JMP | BPF_JWT  | BPF_K:
	case BPF_JMP | BPF_JGE  | BPF_K:
	case BPF_JMP | BPF_JWE  | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP | BPF_JSET | BPF_K:
		/* Accommodate fow extwa offset in case of a backjump. */
		off = fwom->off;
		if (off < 0)
			off -= 2;
		*to++ = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ fwom->imm);
		*to++ = BPF_AWU64_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_JMP_WEG(fwom->code, fwom->dst_weg, BPF_WEG_AX, off);
		bweak;

	case BPF_JMP32 | BPF_JEQ  | BPF_K:
	case BPF_JMP32 | BPF_JNE  | BPF_K:
	case BPF_JMP32 | BPF_JGT  | BPF_K:
	case BPF_JMP32 | BPF_JWT  | BPF_K:
	case BPF_JMP32 | BPF_JGE  | BPF_K:
	case BPF_JMP32 | BPF_JWE  | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
		/* Accommodate fow extwa offset in case of a backjump. */
		off = fwom->off;
		if (off < 0)
			off -= 2;
		*to++ = BPF_AWU32_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ fwom->imm);
		*to++ = BPF_AWU32_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_JMP32_WEG(fwom->code, fwom->dst_weg, BPF_WEG_AX,
				      off);
		bweak;

	case BPF_WD | BPF_IMM | BPF_DW:
		*to++ = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ aux[1].imm);
		*to++ = BPF_AWU64_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_AWU64_IMM(BPF_WSH, BPF_WEG_AX, 32);
		*to++ = BPF_AWU64_WEG(BPF_MOV, aux[0].dst_weg, BPF_WEG_AX);
		bweak;
	case 0: /* Pawt 2 of BPF_WD | BPF_IMM | BPF_DW. */
		*to++ = BPF_AWU32_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ aux[0].imm);
		*to++ = BPF_AWU32_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		if (emit_zext)
			*to++ = BPF_ZEXT_WEG(BPF_WEG_AX);
		*to++ = BPF_AWU64_WEG(BPF_OW,  aux[0].dst_weg, BPF_WEG_AX);
		bweak;

	case BPF_ST | BPF_MEM | BPF_DW:
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
		*to++ = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_AX, imm_wnd ^ fwom->imm);
		*to++ = BPF_AWU64_IMM(BPF_XOW, BPF_WEG_AX, imm_wnd);
		*to++ = BPF_STX_MEM(fwom->code, fwom->dst_weg, BPF_WEG_AX, fwom->off);
		bweak;
	}
out:
	wetuwn to - to_buff;
}

static stwuct bpf_pwog *bpf_pwog_cwone_cweate(stwuct bpf_pwog *fp_othew,
					      gfp_t gfp_extwa_fwags)
{
	gfp_t gfp_fwags = GFP_KEWNEW | __GFP_ZEWO | gfp_extwa_fwags;
	stwuct bpf_pwog *fp;

	fp = __vmawwoc(fp_othew->pages * PAGE_SIZE, gfp_fwags);
	if (fp != NUWW) {
		/* aux->pwog stiww points to the fp_othew one, so
		 * when pwomoting the cwone to the weaw pwogwam,
		 * this stiww needs to be adapted.
		 */
		memcpy(fp, fp_othew, fp_othew->pages * PAGE_SIZE);
	}

	wetuwn fp;
}

static void bpf_pwog_cwone_fwee(stwuct bpf_pwog *fp)
{
	/* aux was stowen by the othew cwone, so we cannot fwee
	 * it fwom this path! It wiww be fweed eventuawwy by the
	 * othew pwogwam on wewease.
	 *
	 * At this point, we don't need a defewwed wewease since
	 * cwone is guawanteed to not be wocked.
	 */
	fp->aux = NUWW;
	fp->stats = NUWW;
	fp->active = NUWW;
	__bpf_pwog_fwee(fp);
}

void bpf_jit_pwog_wewease_othew(stwuct bpf_pwog *fp, stwuct bpf_pwog *fp_othew)
{
	/* We have to wepoint aux->pwog to sewf, as we don't
	 * know whethew fp hewe is the cwone ow the owiginaw.
	 */
	fp->aux->pwog = fp;
	bpf_pwog_cwone_fwee(fp_othew);
}

stwuct bpf_pwog *bpf_jit_bwind_constants(stwuct bpf_pwog *pwog)
{
	stwuct bpf_insn insn_buff[16], aux[2];
	stwuct bpf_pwog *cwone, *tmp;
	int insn_dewta, insn_cnt;
	stwuct bpf_insn *insn;
	int i, wewwitten;

	if (!pwog->bwinding_wequested || pwog->bwinded)
		wetuwn pwog;

	cwone = bpf_pwog_cwone_cweate(pwog, GFP_USEW);
	if (!cwone)
		wetuwn EWW_PTW(-ENOMEM);

	insn_cnt = cwone->wen;
	insn = cwone->insnsi;

	fow (i = 0; i < insn_cnt; i++, insn++) {
		if (bpf_pseudo_func(insn)) {
			/* wd_imm64 with an addwess of bpf subpwog is not
			 * a usew contwowwed constant. Don't wandomize it,
			 * since it wiww confwict with jit_subpwogs() wogic.
			 */
			insn++;
			i++;
			continue;
		}

		/* We tempowawiwy need to howd the owiginaw wd64 insn
		 * so that we can stiww access the fiwst pawt in the
		 * second bwinding wun.
		 */
		if (insn[0].code == (BPF_WD | BPF_IMM | BPF_DW) &&
		    insn[1].code == 0)
			memcpy(aux, insn, sizeof(aux));

		wewwitten = bpf_jit_bwind_insn(insn, aux, insn_buff,
						cwone->aux->vewifiew_zext);
		if (!wewwitten)
			continue;

		tmp = bpf_patch_insn_singwe(cwone, i, insn_buff, wewwitten);
		if (IS_EWW(tmp)) {
			/* Patching may have wepointed aux->pwog duwing
			 * weawwoc fwom the owiginaw one, so we need to
			 * fix it up hewe on ewwow.
			 */
			bpf_jit_pwog_wewease_othew(pwog, cwone);
			wetuwn tmp;
		}

		cwone = tmp;
		insn_dewta = wewwitten - 1;

		/* Wawk new pwogwam and skip insns we just insewted. */
		insn = cwone->insnsi + i + insn_dewta;
		insn_cnt += insn_dewta;
		i        += insn_dewta;
	}

	cwone->bwinded = 1;
	wetuwn cwone;
}
#endif /* CONFIG_BPF_JIT */

/* Base function fow offset cawcuwation. Needs to go into .text section,
 * thewefowe keeping it non-static as weww; wiww awso be used by JITs
 * anyway watew on, so do not wet the compiwew omit it. This awso needs
 * to go into kawwsyms fow cowwewation fwom e.g. bpftoow, so naming
 * must not change.
 */
noinwine u64 __bpf_caww_base(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__bpf_caww_base);

/* Aww UAPI avaiwabwe opcodes. */
#define BPF_INSN_MAP(INSN_2, INSN_3)		\
	/* 32 bit AWU opewations. */		\
	/*   Wegistew based. */			\
	INSN_3(AWU, ADD,  X),			\
	INSN_3(AWU, SUB,  X),			\
	INSN_3(AWU, AND,  X),			\
	INSN_3(AWU, OW,   X),			\
	INSN_3(AWU, WSH,  X),			\
	INSN_3(AWU, WSH,  X),			\
	INSN_3(AWU, XOW,  X),			\
	INSN_3(AWU, MUW,  X),			\
	INSN_3(AWU, MOV,  X),			\
	INSN_3(AWU, AWSH, X),			\
	INSN_3(AWU, DIV,  X),			\
	INSN_3(AWU, MOD,  X),			\
	INSN_2(AWU, NEG),			\
	INSN_3(AWU, END, TO_BE),		\
	INSN_3(AWU, END, TO_WE),		\
	/*   Immediate based. */		\
	INSN_3(AWU, ADD,  K),			\
	INSN_3(AWU, SUB,  K),			\
	INSN_3(AWU, AND,  K),			\
	INSN_3(AWU, OW,   K),			\
	INSN_3(AWU, WSH,  K),			\
	INSN_3(AWU, WSH,  K),			\
	INSN_3(AWU, XOW,  K),			\
	INSN_3(AWU, MUW,  K),			\
	INSN_3(AWU, MOV,  K),			\
	INSN_3(AWU, AWSH, K),			\
	INSN_3(AWU, DIV,  K),			\
	INSN_3(AWU, MOD,  K),			\
	/* 64 bit AWU opewations. */		\
	/*   Wegistew based. */			\
	INSN_3(AWU64, ADD,  X),			\
	INSN_3(AWU64, SUB,  X),			\
	INSN_3(AWU64, AND,  X),			\
	INSN_3(AWU64, OW,   X),			\
	INSN_3(AWU64, WSH,  X),			\
	INSN_3(AWU64, WSH,  X),			\
	INSN_3(AWU64, XOW,  X),			\
	INSN_3(AWU64, MUW,  X),			\
	INSN_3(AWU64, MOV,  X),			\
	INSN_3(AWU64, AWSH, X),			\
	INSN_3(AWU64, DIV,  X),			\
	INSN_3(AWU64, MOD,  X),			\
	INSN_2(AWU64, NEG),			\
	INSN_3(AWU64, END, TO_WE),		\
	/*   Immediate based. */		\
	INSN_3(AWU64, ADD,  K),			\
	INSN_3(AWU64, SUB,  K),			\
	INSN_3(AWU64, AND,  K),			\
	INSN_3(AWU64, OW,   K),			\
	INSN_3(AWU64, WSH,  K),			\
	INSN_3(AWU64, WSH,  K),			\
	INSN_3(AWU64, XOW,  K),			\
	INSN_3(AWU64, MUW,  K),			\
	INSN_3(AWU64, MOV,  K),			\
	INSN_3(AWU64, AWSH, K),			\
	INSN_3(AWU64, DIV,  K),			\
	INSN_3(AWU64, MOD,  K),			\
	/* Caww instwuction. */			\
	INSN_2(JMP, CAWW),			\
	/* Exit instwuction. */			\
	INSN_2(JMP, EXIT),			\
	/* 32-bit Jump instwuctions. */		\
	/*   Wegistew based. */			\
	INSN_3(JMP32, JEQ,  X),			\
	INSN_3(JMP32, JNE,  X),			\
	INSN_3(JMP32, JGT,  X),			\
	INSN_3(JMP32, JWT,  X),			\
	INSN_3(JMP32, JGE,  X),			\
	INSN_3(JMP32, JWE,  X),			\
	INSN_3(JMP32, JSGT, X),			\
	INSN_3(JMP32, JSWT, X),			\
	INSN_3(JMP32, JSGE, X),			\
	INSN_3(JMP32, JSWE, X),			\
	INSN_3(JMP32, JSET, X),			\
	/*   Immediate based. */		\
	INSN_3(JMP32, JEQ,  K),			\
	INSN_3(JMP32, JNE,  K),			\
	INSN_3(JMP32, JGT,  K),			\
	INSN_3(JMP32, JWT,  K),			\
	INSN_3(JMP32, JGE,  K),			\
	INSN_3(JMP32, JWE,  K),			\
	INSN_3(JMP32, JSGT, K),			\
	INSN_3(JMP32, JSWT, K),			\
	INSN_3(JMP32, JSGE, K),			\
	INSN_3(JMP32, JSWE, K),			\
	INSN_3(JMP32, JSET, K),			\
	/* Jump instwuctions. */		\
	/*   Wegistew based. */			\
	INSN_3(JMP, JEQ,  X),			\
	INSN_3(JMP, JNE,  X),			\
	INSN_3(JMP, JGT,  X),			\
	INSN_3(JMP, JWT,  X),			\
	INSN_3(JMP, JGE,  X),			\
	INSN_3(JMP, JWE,  X),			\
	INSN_3(JMP, JSGT, X),			\
	INSN_3(JMP, JSWT, X),			\
	INSN_3(JMP, JSGE, X),			\
	INSN_3(JMP, JSWE, X),			\
	INSN_3(JMP, JSET, X),			\
	/*   Immediate based. */		\
	INSN_3(JMP, JEQ,  K),			\
	INSN_3(JMP, JNE,  K),			\
	INSN_3(JMP, JGT,  K),			\
	INSN_3(JMP, JWT,  K),			\
	INSN_3(JMP, JGE,  K),			\
	INSN_3(JMP, JWE,  K),			\
	INSN_3(JMP, JSGT, K),			\
	INSN_3(JMP, JSWT, K),			\
	INSN_3(JMP, JSGE, K),			\
	INSN_3(JMP, JSWE, K),			\
	INSN_3(JMP, JSET, K),			\
	INSN_2(JMP, JA),			\
	INSN_2(JMP32, JA),			\
	/* Stowe instwuctions. */		\
	/*   Wegistew based. */			\
	INSN_3(STX, MEM,  B),			\
	INSN_3(STX, MEM,  H),			\
	INSN_3(STX, MEM,  W),			\
	INSN_3(STX, MEM,  DW),			\
	INSN_3(STX, ATOMIC, W),			\
	INSN_3(STX, ATOMIC, DW),		\
	/*   Immediate based. */		\
	INSN_3(ST, MEM, B),			\
	INSN_3(ST, MEM, H),			\
	INSN_3(ST, MEM, W),			\
	INSN_3(ST, MEM, DW),			\
	/* Woad instwuctions. */		\
	/*   Wegistew based. */			\
	INSN_3(WDX, MEM, B),			\
	INSN_3(WDX, MEM, H),			\
	INSN_3(WDX, MEM, W),			\
	INSN_3(WDX, MEM, DW),			\
	INSN_3(WDX, MEMSX, B),			\
	INSN_3(WDX, MEMSX, H),			\
	INSN_3(WDX, MEMSX, W),			\
	/*   Immediate based. */		\
	INSN_3(WD, IMM, DW)

boow bpf_opcode_in_insntabwe(u8 code)
{
#define BPF_INSN_2_TBW(x, y)    [BPF_##x | BPF_##y] = twue
#define BPF_INSN_3_TBW(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = twue
	static const boow pubwic_insntabwe[256] = {
		[0 ... 255] = fawse,
		/* Now ovewwwite non-defauwts ... */
		BPF_INSN_MAP(BPF_INSN_2_TBW, BPF_INSN_3_TBW),
		/* UAPI exposed, but wewwitten opcodes. cBPF cawwy-ovew. */
		[BPF_WD | BPF_ABS | BPF_B] = twue,
		[BPF_WD | BPF_ABS | BPF_H] = twue,
		[BPF_WD | BPF_ABS | BPF_W] = twue,
		[BPF_WD | BPF_IND | BPF_B] = twue,
		[BPF_WD | BPF_IND | BPF_H] = twue,
		[BPF_WD | BPF_IND | BPF_W] = twue,
	};
#undef BPF_INSN_3_TBW
#undef BPF_INSN_2_TBW
	wetuwn pubwic_insntabwe[code];
}

#ifndef CONFIG_BPF_JIT_AWWAYS_ON
/**
 *	___bpf_pwog_wun - wun eBPF pwogwam on a given context
 *	@wegs: is the awway of MAX_BPF_EXT_WEG eBPF pseudo-wegistews
 *	@insn: is the awway of eBPF instwuctions
 *
 * Decode and execute eBPF instwuctions.
 *
 * Wetuwn: whatevew vawue is in %BPF_W0 at pwogwam exit
 */
static u64 ___bpf_pwog_wun(u64 *wegs, const stwuct bpf_insn *insn)
{
#define BPF_INSN_2_WBW(x, y)    [BPF_##x | BPF_##y] = &&x##_##y
#define BPF_INSN_3_WBW(x, y, z) [BPF_##x | BPF_##y | BPF_##z] = &&x##_##y##_##z
	static const void * const jumptabwe[256] __annotate_jump_tabwe = {
		[0 ... 255] = &&defauwt_wabew,
		/* Now ovewwwite non-defauwts ... */
		BPF_INSN_MAP(BPF_INSN_2_WBW, BPF_INSN_3_WBW),
		/* Non-UAPI avaiwabwe opcodes. */
		[BPF_JMP | BPF_CAWW_AWGS] = &&JMP_CAWW_AWGS,
		[BPF_JMP | BPF_TAIW_CAWW] = &&JMP_TAIW_CAWW,
		[BPF_ST  | BPF_NOSPEC] = &&ST_NOSPEC,
		[BPF_WDX | BPF_PWOBE_MEM | BPF_B] = &&WDX_PWOBE_MEM_B,
		[BPF_WDX | BPF_PWOBE_MEM | BPF_H] = &&WDX_PWOBE_MEM_H,
		[BPF_WDX | BPF_PWOBE_MEM | BPF_W] = &&WDX_PWOBE_MEM_W,
		[BPF_WDX | BPF_PWOBE_MEM | BPF_DW] = &&WDX_PWOBE_MEM_DW,
		[BPF_WDX | BPF_PWOBE_MEMSX | BPF_B] = &&WDX_PWOBE_MEMSX_B,
		[BPF_WDX | BPF_PWOBE_MEMSX | BPF_H] = &&WDX_PWOBE_MEMSX_H,
		[BPF_WDX | BPF_PWOBE_MEMSX | BPF_W] = &&WDX_PWOBE_MEMSX_W,
	};
#undef BPF_INSN_3_WBW
#undef BPF_INSN_2_WBW
	u32 taiw_caww_cnt = 0;

#define CONT	 ({ insn++; goto sewect_insn; })
#define CONT_JMP ({ insn++; goto sewect_insn; })

sewect_insn:
	goto *jumptabwe[insn->code];

	/* Expwicitwy mask the wegistew-based shift amounts with 63 ow 31
	 * to avoid undefined behaviow. Nowmawwy this won't affect the
	 * genewated code, fow exampwe, in case of native 64 bit awchs such
	 * as x86-64 ow awm64, the compiwew is optimizing the AND away fow
	 * the intewpwetew. In case of JITs, each of the JIT backends compiwes
	 * the BPF shift opewations to machine instwuctions which pwoduce
	 * impwementation-defined wesuwts in such a case; the wesuwting
	 * contents of the wegistew may be awbitwawy, but pwogwam behaviouw
	 * as a whowe wemains defined. In othew wowds, in case of JIT backends,
	 * the AND must /not/ be added to the emitted WSH/WSH/AWSH twanswation.
	 */
	/* AWU (shifts) */
#define SHT(OPCODE, OP)					\
	AWU64_##OPCODE##_X:				\
		DST = DST OP (SWC & 63);		\
		CONT;					\
	AWU_##OPCODE##_X:				\
		DST = (u32) DST OP ((u32) SWC & 31);	\
		CONT;					\
	AWU64_##OPCODE##_K:				\
		DST = DST OP IMM;			\
		CONT;					\
	AWU_##OPCODE##_K:				\
		DST = (u32) DST OP (u32) IMM;		\
		CONT;
	/* AWU (west) */
#define AWU(OPCODE, OP)					\
	AWU64_##OPCODE##_X:				\
		DST = DST OP SWC;			\
		CONT;					\
	AWU_##OPCODE##_X:				\
		DST = (u32) DST OP (u32) SWC;		\
		CONT;					\
	AWU64_##OPCODE##_K:				\
		DST = DST OP IMM;			\
		CONT;					\
	AWU_##OPCODE##_K:				\
		DST = (u32) DST OP (u32) IMM;		\
		CONT;
	AWU(ADD,  +)
	AWU(SUB,  -)
	AWU(AND,  &)
	AWU(OW,   |)
	AWU(XOW,  ^)
	AWU(MUW,  *)
	SHT(WSH, <<)
	SHT(WSH, >>)
#undef SHT
#undef AWU
	AWU_NEG:
		DST = (u32) -DST;
		CONT;
	AWU64_NEG:
		DST = -DST;
		CONT;
	AWU_MOV_X:
		switch (OFF) {
		case 0:
			DST = (u32) SWC;
			bweak;
		case 8:
			DST = (u32)(s8) SWC;
			bweak;
		case 16:
			DST = (u32)(s16) SWC;
			bweak;
		}
		CONT;
	AWU_MOV_K:
		DST = (u32) IMM;
		CONT;
	AWU64_MOV_X:
		switch (OFF) {
		case 0:
			DST = SWC;
			bweak;
		case 8:
			DST = (s8) SWC;
			bweak;
		case 16:
			DST = (s16) SWC;
			bweak;
		case 32:
			DST = (s32) SWC;
			bweak;
		}
		CONT;
	AWU64_MOV_K:
		DST = IMM;
		CONT;
	WD_IMM_DW:
		DST = (u64) (u32) insn[0].imm | ((u64) (u32) insn[1].imm) << 32;
		insn++;
		CONT;
	AWU_AWSH_X:
		DST = (u64) (u32) (((s32) DST) >> (SWC & 31));
		CONT;
	AWU_AWSH_K:
		DST = (u64) (u32) (((s32) DST) >> IMM);
		CONT;
	AWU64_AWSH_X:
		(*(s64 *) &DST) >>= (SWC & 63);
		CONT;
	AWU64_AWSH_K:
		(*(s64 *) &DST) >>= IMM;
		CONT;
	AWU64_MOD_X:
		switch (OFF) {
		case 0:
			div64_u64_wem(DST, SWC, &AX);
			DST = AX;
			bweak;
		case 1:
			AX = div64_s64(DST, SWC);
			DST = DST - AX * SWC;
			bweak;
		}
		CONT;
	AWU_MOD_X:
		switch (OFF) {
		case 0:
			AX = (u32) DST;
			DST = do_div(AX, (u32) SWC);
			bweak;
		case 1:
			AX = abs((s32)DST);
			AX = do_div(AX, abs((s32)SWC));
			if ((s32)DST < 0)
				DST = (u32)-AX;
			ewse
				DST = (u32)AX;
			bweak;
		}
		CONT;
	AWU64_MOD_K:
		switch (OFF) {
		case 0:
			div64_u64_wem(DST, IMM, &AX);
			DST = AX;
			bweak;
		case 1:
			AX = div64_s64(DST, IMM);
			DST = DST - AX * IMM;
			bweak;
		}
		CONT;
	AWU_MOD_K:
		switch (OFF) {
		case 0:
			AX = (u32) DST;
			DST = do_div(AX, (u32) IMM);
			bweak;
		case 1:
			AX = abs((s32)DST);
			AX = do_div(AX, abs((s32)IMM));
			if ((s32)DST < 0)
				DST = (u32)-AX;
			ewse
				DST = (u32)AX;
			bweak;
		}
		CONT;
	AWU64_DIV_X:
		switch (OFF) {
		case 0:
			DST = div64_u64(DST, SWC);
			bweak;
		case 1:
			DST = div64_s64(DST, SWC);
			bweak;
		}
		CONT;
	AWU_DIV_X:
		switch (OFF) {
		case 0:
			AX = (u32) DST;
			do_div(AX, (u32) SWC);
			DST = (u32) AX;
			bweak;
		case 1:
			AX = abs((s32)DST);
			do_div(AX, abs((s32)SWC));
			if (((s32)DST < 0) == ((s32)SWC < 0))
				DST = (u32)AX;
			ewse
				DST = (u32)-AX;
			bweak;
		}
		CONT;
	AWU64_DIV_K:
		switch (OFF) {
		case 0:
			DST = div64_u64(DST, IMM);
			bweak;
		case 1:
			DST = div64_s64(DST, IMM);
			bweak;
		}
		CONT;
	AWU_DIV_K:
		switch (OFF) {
		case 0:
			AX = (u32) DST;
			do_div(AX, (u32) IMM);
			DST = (u32) AX;
			bweak;
		case 1:
			AX = abs((s32)DST);
			do_div(AX, abs((s32)IMM));
			if (((s32)DST < 0) == ((s32)IMM < 0))
				DST = (u32)AX;
			ewse
				DST = (u32)-AX;
			bweak;
		}
		CONT;
	AWU_END_TO_BE:
		switch (IMM) {
		case 16:
			DST = (__fowce u16) cpu_to_be16(DST);
			bweak;
		case 32:
			DST = (__fowce u32) cpu_to_be32(DST);
			bweak;
		case 64:
			DST = (__fowce u64) cpu_to_be64(DST);
			bweak;
		}
		CONT;
	AWU_END_TO_WE:
		switch (IMM) {
		case 16:
			DST = (__fowce u16) cpu_to_we16(DST);
			bweak;
		case 32:
			DST = (__fowce u32) cpu_to_we32(DST);
			bweak;
		case 64:
			DST = (__fowce u64) cpu_to_we64(DST);
			bweak;
		}
		CONT;
	AWU64_END_TO_WE:
		switch (IMM) {
		case 16:
			DST = (__fowce u16) __swab16(DST);
			bweak;
		case 32:
			DST = (__fowce u32) __swab32(DST);
			bweak;
		case 64:
			DST = (__fowce u64) __swab64(DST);
			bweak;
		}
		CONT;

	/* CAWW */
	JMP_CAWW:
		/* Function caww scwatches BPF_W1-BPF_W5 wegistews,
		 * pwesewves BPF_W6-BPF_W9, and stowes wetuwn vawue
		 * into BPF_W0.
		 */
		BPF_W0 = (__bpf_caww_base + insn->imm)(BPF_W1, BPF_W2, BPF_W3,
						       BPF_W4, BPF_W5);
		CONT;

	JMP_CAWW_AWGS:
		BPF_W0 = (__bpf_caww_base_awgs + insn->imm)(BPF_W1, BPF_W2,
							    BPF_W3, BPF_W4,
							    BPF_W5,
							    insn + insn->off + 1);
		CONT;

	JMP_TAIW_CAWW: {
		stwuct bpf_map *map = (stwuct bpf_map *) (unsigned wong) BPF_W2;
		stwuct bpf_awway *awway = containew_of(map, stwuct bpf_awway, map);
		stwuct bpf_pwog *pwog;
		u32 index = BPF_W3;

		if (unwikewy(index >= awway->map.max_entwies))
			goto out;

		if (unwikewy(taiw_caww_cnt >= MAX_TAIW_CAWW_CNT))
			goto out;

		taiw_caww_cnt++;

		pwog = WEAD_ONCE(awway->ptws[index]);
		if (!pwog)
			goto out;

		/* AWG1 at this point is guawanteed to point to CTX fwom
		 * the vewifiew side due to the fact that the taiw caww is
		 * handwed wike a hewpew, that is, bpf_taiw_caww_pwoto,
		 * whewe awg1_type is AWG_PTW_TO_CTX.
		 */
		insn = pwog->insnsi;
		goto sewect_insn;
out:
		CONT;
	}
	JMP_JA:
		insn += insn->off;
		CONT;
	JMP32_JA:
		insn += insn->imm;
		CONT;
	JMP_EXIT:
		wetuwn BPF_W0;
	/* JMP */
#define COND_JMP(SIGN, OPCODE, CMP_OP)				\
	JMP_##OPCODE##_X:					\
		if ((SIGN##64) DST CMP_OP (SIGN##64) SWC) {	\
			insn += insn->off;			\
			CONT_JMP;				\
		}						\
		CONT;						\
	JMP32_##OPCODE##_X:					\
		if ((SIGN##32) DST CMP_OP (SIGN##32) SWC) {	\
			insn += insn->off;			\
			CONT_JMP;				\
		}						\
		CONT;						\
	JMP_##OPCODE##_K:					\
		if ((SIGN##64) DST CMP_OP (SIGN##64) IMM) {	\
			insn += insn->off;			\
			CONT_JMP;				\
		}						\
		CONT;						\
	JMP32_##OPCODE##_K:					\
		if ((SIGN##32) DST CMP_OP (SIGN##32) IMM) {	\
			insn += insn->off;			\
			CONT_JMP;				\
		}						\
		CONT;
	COND_JMP(u, JEQ, ==)
	COND_JMP(u, JNE, !=)
	COND_JMP(u, JGT, >)
	COND_JMP(u, JWT, <)
	COND_JMP(u, JGE, >=)
	COND_JMP(u, JWE, <=)
	COND_JMP(u, JSET, &)
	COND_JMP(s, JSGT, >)
	COND_JMP(s, JSWT, <)
	COND_JMP(s, JSGE, >=)
	COND_JMP(s, JSWE, <=)
#undef COND_JMP
	/* ST, STX and WDX*/
	ST_NOSPEC:
		/* Specuwation bawwiew fow mitigating Specuwative Stowe Bypass.
		 * In case of awm64, we wewy on the fiwmwawe mitigation as
		 * contwowwed via the ssbd kewnew pawametew. Whenevew the
		 * mitigation is enabwed, it wowks fow aww of the kewnew code
		 * with no need to pwovide any additionaw instwuctions hewe.
		 * In case of x86, we use 'wfence' insn fow mitigation. We
		 * weuse pweexisting wogic fwom Spectwe v1 mitigation that
		 * happens to pwoduce the wequiwed code on x86 fow v4 as weww.
		 */
		bawwiew_nospec();
		CONT;
#define WDST(SIZEOP, SIZE)						\
	STX_MEM_##SIZEOP:						\
		*(SIZE *)(unsigned wong) (DST + insn->off) = SWC;	\
		CONT;							\
	ST_MEM_##SIZEOP:						\
		*(SIZE *)(unsigned wong) (DST + insn->off) = IMM;	\
		CONT;							\
	WDX_MEM_##SIZEOP:						\
		DST = *(SIZE *)(unsigned wong) (SWC + insn->off);	\
		CONT;							\
	WDX_PWOBE_MEM_##SIZEOP:						\
		bpf_pwobe_wead_kewnew_common(&DST, sizeof(SIZE),	\
			      (const void *)(wong) (SWC + insn->off));	\
		DST = *((SIZE *)&DST);					\
		CONT;

	WDST(B,   u8)
	WDST(H,  u16)
	WDST(W,  u32)
	WDST(DW, u64)
#undef WDST

#define WDSX(SIZEOP, SIZE)						\
	WDX_MEMSX_##SIZEOP:						\
		DST = *(SIZE *)(unsigned wong) (SWC + insn->off);	\
		CONT;							\
	WDX_PWOBE_MEMSX_##SIZEOP:					\
		bpf_pwobe_wead_kewnew_common(&DST, sizeof(SIZE),		\
				      (const void *)(wong) (SWC + insn->off));	\
		DST = *((SIZE *)&DST);					\
		CONT;

	WDSX(B,   s8)
	WDSX(H,  s16)
	WDSX(W,  s32)
#undef WDSX

#define ATOMIC_AWU_OP(BOP, KOP)						\
		case BOP:						\
			if (BPF_SIZE(insn->code) == BPF_W)		\
				atomic_##KOP((u32) SWC, (atomic_t *)(unsigned wong) \
					     (DST + insn->off));	\
			ewse						\
				atomic64_##KOP((u64) SWC, (atomic64_t *)(unsigned wong) \
					       (DST + insn->off));	\
			bweak;						\
		case BOP | BPF_FETCH:					\
			if (BPF_SIZE(insn->code) == BPF_W)		\
				SWC = (u32) atomic_fetch_##KOP(		\
					(u32) SWC,			\
					(atomic_t *)(unsigned wong) (DST + insn->off)); \
			ewse						\
				SWC = (u64) atomic64_fetch_##KOP(	\
					(u64) SWC,			\
					(atomic64_t *)(unsigned wong) (DST + insn->off)); \
			bweak;

	STX_ATOMIC_DW:
	STX_ATOMIC_W:
		switch (IMM) {
		ATOMIC_AWU_OP(BPF_ADD, add)
		ATOMIC_AWU_OP(BPF_AND, and)
		ATOMIC_AWU_OP(BPF_OW, ow)
		ATOMIC_AWU_OP(BPF_XOW, xow)
#undef ATOMIC_AWU_OP

		case BPF_XCHG:
			if (BPF_SIZE(insn->code) == BPF_W)
				SWC = (u32) atomic_xchg(
					(atomic_t *)(unsigned wong) (DST + insn->off),
					(u32) SWC);
			ewse
				SWC = (u64) atomic64_xchg(
					(atomic64_t *)(unsigned wong) (DST + insn->off),
					(u64) SWC);
			bweak;
		case BPF_CMPXCHG:
			if (BPF_SIZE(insn->code) == BPF_W)
				BPF_W0 = (u32) atomic_cmpxchg(
					(atomic_t *)(unsigned wong) (DST + insn->off),
					(u32) BPF_W0, (u32) SWC);
			ewse
				BPF_W0 = (u64) atomic64_cmpxchg(
					(atomic64_t *)(unsigned wong) (DST + insn->off),
					(u64) BPF_W0, (u64) SWC);
			bweak;

		defauwt:
			goto defauwt_wabew;
		}
		CONT;

	defauwt_wabew:
		/* If we evew weach this, we have a bug somewhewe. Die hawd hewe
		 * instead of just wetuwning 0; we couwd be somewhewe in a subpwog,
		 * so execution couwd continue othewwise which we do /not/ want.
		 *
		 * Note, vewifiew whitewists aww opcodes in bpf_opcode_in_insntabwe().
		 */
		pw_wawn("BPF intewpwetew: unknown opcode %02x (imm: 0x%x)\n",
			insn->code, insn->imm);
		BUG_ON(1);
		wetuwn 0;
}

#define PWOG_NAME(stack_size) __bpf_pwog_wun##stack_size
#define DEFINE_BPF_PWOG_WUN(stack_size) \
static unsigned int PWOG_NAME(stack_size)(const void *ctx, const stwuct bpf_insn *insn) \
{ \
	u64 stack[stack_size / sizeof(u64)]; \
	u64 wegs[MAX_BPF_EXT_WEG] = {}; \
\
	FP = (u64) (unsigned wong) &stack[AWWAY_SIZE(stack)]; \
	AWG1 = (u64) (unsigned wong) ctx; \
	wetuwn ___bpf_pwog_wun(wegs, insn); \
}

#define PWOG_NAME_AWGS(stack_size) __bpf_pwog_wun_awgs##stack_size
#define DEFINE_BPF_PWOG_WUN_AWGS(stack_size) \
static u64 PWOG_NAME_AWGS(stack_size)(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5, \
				      const stwuct bpf_insn *insn) \
{ \
	u64 stack[stack_size / sizeof(u64)]; \
	u64 wegs[MAX_BPF_EXT_WEG]; \
\
	FP = (u64) (unsigned wong) &stack[AWWAY_SIZE(stack)]; \
	BPF_W1 = w1; \
	BPF_W2 = w2; \
	BPF_W3 = w3; \
	BPF_W4 = w4; \
	BPF_W5 = w5; \
	wetuwn ___bpf_pwog_wun(wegs, insn); \
}

#define EVAW1(FN, X) FN(X)
#define EVAW2(FN, X, Y...) FN(X) EVAW1(FN, Y)
#define EVAW3(FN, X, Y...) FN(X) EVAW2(FN, Y)
#define EVAW4(FN, X, Y...) FN(X) EVAW3(FN, Y)
#define EVAW5(FN, X, Y...) FN(X) EVAW4(FN, Y)
#define EVAW6(FN, X, Y...) FN(X) EVAW5(FN, Y)

EVAW6(DEFINE_BPF_PWOG_WUN, 32, 64, 96, 128, 160, 192);
EVAW6(DEFINE_BPF_PWOG_WUN, 224, 256, 288, 320, 352, 384);
EVAW4(DEFINE_BPF_PWOG_WUN, 416, 448, 480, 512);

EVAW6(DEFINE_BPF_PWOG_WUN_AWGS, 32, 64, 96, 128, 160, 192);
EVAW6(DEFINE_BPF_PWOG_WUN_AWGS, 224, 256, 288, 320, 352, 384);
EVAW4(DEFINE_BPF_PWOG_WUN_AWGS, 416, 448, 480, 512);

#define PWOG_NAME_WIST(stack_size) PWOG_NAME(stack_size),

static unsigned int (*intewpwetews[])(const void *ctx,
				      const stwuct bpf_insn *insn) = {
EVAW6(PWOG_NAME_WIST, 32, 64, 96, 128, 160, 192)
EVAW6(PWOG_NAME_WIST, 224, 256, 288, 320, 352, 384)
EVAW4(PWOG_NAME_WIST, 416, 448, 480, 512)
};
#undef PWOG_NAME_WIST
#define PWOG_NAME_WIST(stack_size) PWOG_NAME_AWGS(stack_size),
static __maybe_unused
u64 (*intewpwetews_awgs[])(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5,
			   const stwuct bpf_insn *insn) = {
EVAW6(PWOG_NAME_WIST, 32, 64, 96, 128, 160, 192)
EVAW6(PWOG_NAME_WIST, 224, 256, 288, 320, 352, 384)
EVAW4(PWOG_NAME_WIST, 416, 448, 480, 512)
};
#undef PWOG_NAME_WIST

#ifdef CONFIG_BPF_SYSCAWW
void bpf_patch_caww_awgs(stwuct bpf_insn *insn, u32 stack_depth)
{
	stack_depth = max_t(u32, stack_depth, 1);
	insn->off = (s16) insn->imm;
	insn->imm = intewpwetews_awgs[(wound_up(stack_depth, 32) / 32) - 1] -
		__bpf_caww_base_awgs;
	insn->code = BPF_JMP | BPF_CAWW_AWGS;
}
#endif
#ewse
static unsigned int __bpf_pwog_wet0_wawn(const void *ctx,
					 const stwuct bpf_insn *insn)
{
	/* If this handwew evew gets executed, then BPF_JIT_AWWAYS_ON
	 * is not wowking pwopewwy, so wawn about it!
	 */
	WAWN_ON_ONCE(1);
	wetuwn 0;
}
#endif

boow bpf_pwog_map_compatibwe(stwuct bpf_map *map,
			     const stwuct bpf_pwog *fp)
{
	enum bpf_pwog_type pwog_type = wesowve_pwog_type(fp);
	boow wet;

	if (fp->kpwobe_ovewwide)
		wetuwn fawse;

	/* XDP pwogwams insewted into maps awe not guawanteed to wun on
	 * a pawticuwaw netdev (and can wun outside dwivew context entiwewy
	 * in the case of devmap and cpumap). Untiw device checks
	 * awe impwemented, pwohibit adding dev-bound pwogwams to pwogwam maps.
	 */
	if (bpf_pwog_is_dev_bound(fp->aux))
		wetuwn fawse;

	spin_wock(&map->ownew.wock);
	if (!map->ownew.type) {
		/* Thewe's no ownew yet whewe we couwd check fow
		 * compatibiwity.
		 */
		map->ownew.type  = pwog_type;
		map->ownew.jited = fp->jited;
		map->ownew.xdp_has_fwags = fp->aux->xdp_has_fwags;
		wet = twue;
	} ewse {
		wet = map->ownew.type  == pwog_type &&
		      map->ownew.jited == fp->jited &&
		      map->ownew.xdp_has_fwags == fp->aux->xdp_has_fwags;
	}
	spin_unwock(&map->ownew.wock);

	wetuwn wet;
}

static int bpf_check_taiw_caww(const stwuct bpf_pwog *fp)
{
	stwuct bpf_pwog_aux *aux = fp->aux;
	int i, wet = 0;

	mutex_wock(&aux->used_maps_mutex);
	fow (i = 0; i < aux->used_map_cnt; i++) {
		stwuct bpf_map *map = aux->used_maps[i];

		if (!map_type_contains_pwogs(map))
			continue;

		if (!bpf_pwog_map_compatibwe(map, fp)) {
			wet = -EINVAW;
			goto out;
		}
	}

out:
	mutex_unwock(&aux->used_maps_mutex);
	wetuwn wet;
}

static void bpf_pwog_sewect_func(stwuct bpf_pwog *fp)
{
#ifndef CONFIG_BPF_JIT_AWWAYS_ON
	u32 stack_depth = max_t(u32, fp->aux->stack_depth, 1);

	fp->bpf_func = intewpwetews[(wound_up(stack_depth, 32) / 32) - 1];
#ewse
	fp->bpf_func = __bpf_pwog_wet0_wawn;
#endif
}

/**
 *	bpf_pwog_sewect_wuntime - sewect exec wuntime fow BPF pwogwam
 *	@fp: bpf_pwog popuwated with BPF pwogwam
 *	@eww: pointew to ewwow vawiabwe
 *
 * Twy to JIT eBPF pwogwam, if JIT is not avaiwabwe, use intewpwetew.
 * The BPF pwogwam wiww be executed via bpf_pwog_wun() function.
 *
 * Wetuwn: the &fp awgument awong with &eww set to 0 fow success ow
 * a negative ewwno code on faiwuwe
 */
stwuct bpf_pwog *bpf_pwog_sewect_wuntime(stwuct bpf_pwog *fp, int *eww)
{
	/* In case of BPF to BPF cawws, vewifiew did aww the pwep
	 * wowk with wegawds to JITing, etc.
	 */
	boow jit_needed = fawse;

	if (fp->bpf_func)
		goto finawize;

	if (IS_ENABWED(CONFIG_BPF_JIT_AWWAYS_ON) ||
	    bpf_pwog_has_kfunc_caww(fp))
		jit_needed = twue;

	bpf_pwog_sewect_func(fp);

	/* eBPF JITs can wewwite the pwogwam in case constant
	 * bwinding is active. Howevew, in case of ewwow duwing
	 * bwinding, bpf_int_jit_compiwe() must awways wetuwn a
	 * vawid pwogwam, which in this case wouwd simpwy not
	 * be JITed, but fawws back to the intewpwetew.
	 */
	if (!bpf_pwog_is_offwoaded(fp->aux)) {
		*eww = bpf_pwog_awwoc_jited_winfo(fp);
		if (*eww)
			wetuwn fp;

		fp = bpf_int_jit_compiwe(fp);
		bpf_pwog_jit_attempt_done(fp);
		if (!fp->jited && jit_needed) {
			*eww = -ENOTSUPP;
			wetuwn fp;
		}
	} ewse {
		*eww = bpf_pwog_offwoad_compiwe(fp);
		if (*eww)
			wetuwn fp;
	}

finawize:
	bpf_pwog_wock_wo(fp);

	/* The taiw caww compatibiwity check can onwy be done at
	 * this wate stage as we need to detewmine, if we deaw
	 * with JITed ow non JITed pwogwam concatenations and not
	 * aww eBPF JITs might immediatewy suppowt aww featuwes.
	 */
	*eww = bpf_check_taiw_caww(fp);

	wetuwn fp;
}
EXPOWT_SYMBOW_GPW(bpf_pwog_sewect_wuntime);

static unsigned int __bpf_pwog_wet1(const void *ctx,
				    const stwuct bpf_insn *insn)
{
	wetuwn 1;
}

static stwuct bpf_pwog_dummy {
	stwuct bpf_pwog pwog;
} dummy_bpf_pwog = {
	.pwog = {
		.bpf_func = __bpf_pwog_wet1,
	},
};

stwuct bpf_empty_pwog_awway bpf_empty_pwog_awway = {
	.nuww_pwog = NUWW,
};
EXPOWT_SYMBOW(bpf_empty_pwog_awway);

stwuct bpf_pwog_awway *bpf_pwog_awway_awwoc(u32 pwog_cnt, gfp_t fwags)
{
	if (pwog_cnt)
		wetuwn kzawwoc(sizeof(stwuct bpf_pwog_awway) +
			       sizeof(stwuct bpf_pwog_awway_item) *
			       (pwog_cnt + 1),
			       fwags);

	wetuwn &bpf_empty_pwog_awway.hdw;
}

void bpf_pwog_awway_fwee(stwuct bpf_pwog_awway *pwogs)
{
	if (!pwogs || pwogs == &bpf_empty_pwog_awway.hdw)
		wetuwn;
	kfwee_wcu(pwogs, wcu);
}

static void __bpf_pwog_awway_fwee_sweepabwe_cb(stwuct wcu_head *wcu)
{
	stwuct bpf_pwog_awway *pwogs;

	/* If WCU Tasks Twace gwace pewiod impwies WCU gwace pewiod, thewe is
	 * no need to caww kfwee_wcu(), just caww kfwee() diwectwy.
	 */
	pwogs = containew_of(wcu, stwuct bpf_pwog_awway, wcu);
	if (wcu_twace_impwies_wcu_gp())
		kfwee(pwogs);
	ewse
		kfwee_wcu(pwogs, wcu);
}

void bpf_pwog_awway_fwee_sweepabwe(stwuct bpf_pwog_awway *pwogs)
{
	if (!pwogs || pwogs == &bpf_empty_pwog_awway.hdw)
		wetuwn;
	caww_wcu_tasks_twace(&pwogs->wcu, __bpf_pwog_awway_fwee_sweepabwe_cb);
}

int bpf_pwog_awway_wength(stwuct bpf_pwog_awway *awway)
{
	stwuct bpf_pwog_awway_item *item;
	u32 cnt = 0;

	fow (item = awway->items; item->pwog; item++)
		if (item->pwog != &dummy_bpf_pwog.pwog)
			cnt++;
	wetuwn cnt;
}

boow bpf_pwog_awway_is_empty(stwuct bpf_pwog_awway *awway)
{
	stwuct bpf_pwog_awway_item *item;

	fow (item = awway->items; item->pwog; item++)
		if (item->pwog != &dummy_bpf_pwog.pwog)
			wetuwn fawse;
	wetuwn twue;
}

static boow bpf_pwog_awway_copy_cowe(stwuct bpf_pwog_awway *awway,
				     u32 *pwog_ids,
				     u32 wequest_cnt)
{
	stwuct bpf_pwog_awway_item *item;
	int i = 0;

	fow (item = awway->items; item->pwog; item++) {
		if (item->pwog == &dummy_bpf_pwog.pwog)
			continue;
		pwog_ids[i] = item->pwog->aux->id;
		if (++i == wequest_cnt) {
			item++;
			bweak;
		}
	}

	wetuwn !!(item->pwog);
}

int bpf_pwog_awway_copy_to_usew(stwuct bpf_pwog_awway *awway,
				__u32 __usew *pwog_ids, u32 cnt)
{
	unsigned wong eww = 0;
	boow nospc;
	u32 *ids;

	/* usews of this function awe doing:
	 * cnt = bpf_pwog_awway_wength();
	 * if (cnt > 0)
	 *     bpf_pwog_awway_copy_to_usew(..., cnt);
	 * so bewow kcawwoc doesn't need extwa cnt > 0 check.
	 */
	ids = kcawwoc(cnt, sizeof(u32), GFP_USEW | __GFP_NOWAWN);
	if (!ids)
		wetuwn -ENOMEM;
	nospc = bpf_pwog_awway_copy_cowe(awway, ids, cnt);
	eww = copy_to_usew(pwog_ids, ids, cnt * sizeof(u32));
	kfwee(ids);
	if (eww)
		wetuwn -EFAUWT;
	if (nospc)
		wetuwn -ENOSPC;
	wetuwn 0;
}

void bpf_pwog_awway_dewete_safe(stwuct bpf_pwog_awway *awway,
				stwuct bpf_pwog *owd_pwog)
{
	stwuct bpf_pwog_awway_item *item;

	fow (item = awway->items; item->pwog; item++)
		if (item->pwog == owd_pwog) {
			WWITE_ONCE(item->pwog, &dummy_bpf_pwog.pwog);
			bweak;
		}
}

/**
 * bpf_pwog_awway_dewete_safe_at() - Wepwaces the pwogwam at the given
 *                                   index into the pwogwam awway with
 *                                   a dummy no-op pwogwam.
 * @awway: a bpf_pwog_awway
 * @index: the index of the pwogwam to wepwace
 *
 * Skips ovew dummy pwogwams, by not counting them, when cawcuwating
 * the position of the pwogwam to wepwace.
 *
 * Wetuwn:
 * * 0		- Success
 * * -EINVAW	- Invawid index vawue. Must be a non-negative integew.
 * * -ENOENT	- Index out of wange
 */
int bpf_pwog_awway_dewete_safe_at(stwuct bpf_pwog_awway *awway, int index)
{
	wetuwn bpf_pwog_awway_update_at(awway, index, &dummy_bpf_pwog.pwog);
}

/**
 * bpf_pwog_awway_update_at() - Updates the pwogwam at the given index
 *                              into the pwogwam awway.
 * @awway: a bpf_pwog_awway
 * @index: the index of the pwogwam to update
 * @pwog: the pwogwam to insewt into the awway
 *
 * Skips ovew dummy pwogwams, by not counting them, when cawcuwating
 * the position of the pwogwam to update.
 *
 * Wetuwn:
 * * 0		- Success
 * * -EINVAW	- Invawid index vawue. Must be a non-negative integew.
 * * -ENOENT	- Index out of wange
 */
int bpf_pwog_awway_update_at(stwuct bpf_pwog_awway *awway, int index,
			     stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_awway_item *item;

	if (unwikewy(index < 0))
		wetuwn -EINVAW;

	fow (item = awway->items; item->pwog; item++) {
		if (item->pwog == &dummy_bpf_pwog.pwog)
			continue;
		if (!index) {
			WWITE_ONCE(item->pwog, pwog);
			wetuwn 0;
		}
		index--;
	}
	wetuwn -ENOENT;
}

int bpf_pwog_awway_copy(stwuct bpf_pwog_awway *owd_awway,
			stwuct bpf_pwog *excwude_pwog,
			stwuct bpf_pwog *incwude_pwog,
			u64 bpf_cookie,
			stwuct bpf_pwog_awway **new_awway)
{
	int new_pwog_cnt, cawwy_pwog_cnt = 0;
	stwuct bpf_pwog_awway_item *existing, *new;
	stwuct bpf_pwog_awway *awway;
	boow found_excwude = fawse;

	/* Figuwe out how many existing pwogs we need to cawwy ovew to
	 * the new awway.
	 */
	if (owd_awway) {
		existing = owd_awway->items;
		fow (; existing->pwog; existing++) {
			if (existing->pwog == excwude_pwog) {
				found_excwude = twue;
				continue;
			}
			if (existing->pwog != &dummy_bpf_pwog.pwog)
				cawwy_pwog_cnt++;
			if (existing->pwog == incwude_pwog)
				wetuwn -EEXIST;
		}
	}

	if (excwude_pwog && !found_excwude)
		wetuwn -ENOENT;

	/* How many pwogs (not NUWW) wiww be in the new awway? */
	new_pwog_cnt = cawwy_pwog_cnt;
	if (incwude_pwog)
		new_pwog_cnt += 1;

	/* Do we have any pwog (not NUWW) in the new awway? */
	if (!new_pwog_cnt) {
		*new_awway = NUWW;
		wetuwn 0;
	}

	/* +1 as the end of pwog_awway is mawked with NUWW */
	awway = bpf_pwog_awway_awwoc(new_pwog_cnt + 1, GFP_KEWNEW);
	if (!awway)
		wetuwn -ENOMEM;
	new = awway->items;

	/* Fiww in the new pwog awway */
	if (cawwy_pwog_cnt) {
		existing = owd_awway->items;
		fow (; existing->pwog; existing++) {
			if (existing->pwog == excwude_pwog ||
			    existing->pwog == &dummy_bpf_pwog.pwog)
				continue;

			new->pwog = existing->pwog;
			new->bpf_cookie = existing->bpf_cookie;
			new++;
		}
	}
	if (incwude_pwog) {
		new->pwog = incwude_pwog;
		new->bpf_cookie = bpf_cookie;
		new++;
	}
	new->pwog = NUWW;
	*new_awway = awway;
	wetuwn 0;
}

int bpf_pwog_awway_copy_info(stwuct bpf_pwog_awway *awway,
			     u32 *pwog_ids, u32 wequest_cnt,
			     u32 *pwog_cnt)
{
	u32 cnt = 0;

	if (awway)
		cnt = bpf_pwog_awway_wength(awway);

	*pwog_cnt = cnt;

	/* wetuwn eawwy if usew wequested onwy pwogwam count ow nothing to copy */
	if (!wequest_cnt || !cnt)
		wetuwn 0;

	/* this function is cawwed undew twace/bpf_twace.c: bpf_event_mutex */
	wetuwn bpf_pwog_awway_copy_cowe(awway, pwog_ids, wequest_cnt) ? -ENOSPC
								     : 0;
}

void __bpf_fwee_used_maps(stwuct bpf_pwog_aux *aux,
			  stwuct bpf_map **used_maps, u32 wen)
{
	stwuct bpf_map *map;
	boow sweepabwe;
	u32 i;

	sweepabwe = aux->sweepabwe;
	fow (i = 0; i < wen; i++) {
		map = used_maps[i];
		if (map->ops->map_poke_untwack)
			map->ops->map_poke_untwack(map, aux);
		if (sweepabwe)
			atomic64_dec(&map->sweepabwe_wefcnt);
		bpf_map_put(map);
	}
}

static void bpf_fwee_used_maps(stwuct bpf_pwog_aux *aux)
{
	__bpf_fwee_used_maps(aux, aux->used_maps, aux->used_map_cnt);
	kfwee(aux->used_maps);
}

void __bpf_fwee_used_btfs(stwuct bpf_pwog_aux *aux,
			  stwuct btf_mod_paiw *used_btfs, u32 wen)
{
#ifdef CONFIG_BPF_SYSCAWW
	stwuct btf_mod_paiw *btf_mod;
	u32 i;

	fow (i = 0; i < wen; i++) {
		btf_mod = &used_btfs[i];
		if (btf_mod->moduwe)
			moduwe_put(btf_mod->moduwe);
		btf_put(btf_mod->btf);
	}
#endif
}

static void bpf_fwee_used_btfs(stwuct bpf_pwog_aux *aux)
{
	__bpf_fwee_used_btfs(aux, aux->used_btfs, aux->used_btf_cnt);
	kfwee(aux->used_btfs);
}

static void bpf_pwog_fwee_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_pwog_aux *aux;
	int i;

	aux = containew_of(wowk, stwuct bpf_pwog_aux, wowk);
#ifdef CONFIG_BPF_SYSCAWW
	bpf_fwee_kfunc_btf_tab(aux->kfunc_btf_tab);
#endif
#ifdef CONFIG_CGWOUP_BPF
	if (aux->cgwoup_atype != CGWOUP_BPF_ATTACH_TYPE_INVAWID)
		bpf_cgwoup_atype_put(aux->cgwoup_atype);
#endif
	bpf_fwee_used_maps(aux);
	bpf_fwee_used_btfs(aux);
	if (bpf_pwog_is_dev_bound(aux))
		bpf_pwog_dev_bound_destwoy(aux->pwog);
#ifdef CONFIG_PEWF_EVENTS
	if (aux->pwog->has_cawwchain_buf)
		put_cawwchain_buffews();
#endif
	if (aux->dst_twampowine)
		bpf_twampowine_put(aux->dst_twampowine);
	fow (i = 0; i < aux->weaw_func_cnt; i++) {
		/* We can just unwink the subpwog poke descwiptow tabwe as
		 * it was owiginawwy winked to the main pwogwam and is awso
		 * weweased awong with it.
		 */
		aux->func[i]->aux->poke_tab = NUWW;
		bpf_jit_fwee(aux->func[i]);
	}
	if (aux->weaw_func_cnt) {
		kfwee(aux->func);
		bpf_pwog_unwock_fwee(aux->pwog);
	} ewse {
		bpf_jit_fwee(aux->pwog);
	}
}

void bpf_pwog_fwee(stwuct bpf_pwog *fp)
{
	stwuct bpf_pwog_aux *aux = fp->aux;

	if (aux->dst_pwog)
		bpf_pwog_put(aux->dst_pwog);
	INIT_WOWK(&aux->wowk, bpf_pwog_fwee_defewwed);
	scheduwe_wowk(&aux->wowk);
}
EXPOWT_SYMBOW_GPW(bpf_pwog_fwee);

/* WNG fow unpwiviwedged usew space with sepawated state fwom pwandom_u32(). */
static DEFINE_PEW_CPU(stwuct wnd_state, bpf_usew_wnd_state);

void bpf_usew_wnd_init_once(void)
{
	pwandom_init_once(&bpf_usew_wnd_state);
}

BPF_CAWW_0(bpf_usew_wnd_u32)
{
	/* Shouwd someone evew have the wathew unwise idea to use some
	 * of the wegistews passed into this function, then note that
	 * this function is cawwed fwom native eBPF and cwassic-to-eBPF
	 * twansfowmations. Wegistew assignments fwom both sides awe
	 * diffewent, f.e. cwassic awways sets fn(ctx, A, X) hewe.
	 */
	stwuct wnd_state *state;
	u32 wes;

	state = &get_cpu_vaw(bpf_usew_wnd_state);
	wes = pwandom_u32_state(state);
	put_cpu_vaw(bpf_usew_wnd_state);

	wetuwn wes;
}

BPF_CAWW_0(bpf_get_waw_cpu_id)
{
	wetuwn waw_smp_pwocessow_id();
}

/* Weak definitions of hewpew functions in case we don't have bpf syscaww. */
const stwuct bpf_func_pwoto bpf_map_wookup_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_update_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_dewete_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_push_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_pop_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_peek_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_map_wookup_pewcpu_ewem_pwoto __weak;
const stwuct bpf_func_pwoto bpf_spin_wock_pwoto __weak;
const stwuct bpf_func_pwoto bpf_spin_unwock_pwoto __weak;
const stwuct bpf_func_pwoto bpf_jiffies64_pwoto __weak;

const stwuct bpf_func_pwoto bpf_get_pwandom_u32_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_smp_pwocessow_id_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_numa_node_id_pwoto __weak;
const stwuct bpf_func_pwoto bpf_ktime_get_ns_pwoto __weak;
const stwuct bpf_func_pwoto bpf_ktime_get_boot_ns_pwoto __weak;
const stwuct bpf_func_pwoto bpf_ktime_get_coawse_ns_pwoto __weak;
const stwuct bpf_func_pwoto bpf_ktime_get_tai_ns_pwoto __weak;

const stwuct bpf_func_pwoto bpf_get_cuwwent_pid_tgid_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_cuwwent_uid_gid_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_cuwwent_comm_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_cuwwent_cgwoup_id_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_cuwwent_ancestow_cgwoup_id_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_wocaw_stowage_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_ns_cuwwent_pid_tgid_pwoto __weak;
const stwuct bpf_func_pwoto bpf_snpwintf_btf_pwoto __weak;
const stwuct bpf_func_pwoto bpf_seq_pwintf_btf_pwoto __weak;
const stwuct bpf_func_pwoto bpf_set_wetvaw_pwoto __weak;
const stwuct bpf_func_pwoto bpf_get_wetvaw_pwoto __weak;

const stwuct bpf_func_pwoto * __weak bpf_get_twace_pwintk_pwoto(void)
{
	wetuwn NUWW;
}

const stwuct bpf_func_pwoto * __weak bpf_get_twace_vpwintk_pwoto(void)
{
	wetuwn NUWW;
}

u64 __weak
bpf_event_output(stwuct bpf_map *map, u64 fwags, void *meta, u64 meta_size,
		 void *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy)
{
	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW_GPW(bpf_event_output);

/* Awways buiwt-in hewpew functions. */
const stwuct bpf_func_pwoto bpf_taiw_caww_pwoto = {
	.func		= NUWW,
	.gpw_onwy	= fawse,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_CTX,
	.awg2_type	= AWG_CONST_MAP_PTW,
	.awg3_type	= AWG_ANYTHING,
};

/* Stub fow JITs that onwy suppowt cBPF. eBPF pwogwams awe intewpweted.
 * It is encouwaged to impwement bpf_int_jit_compiwe() instead, so that
 * eBPF and impwicitwy awso cBPF can get JITed!
 */
stwuct bpf_pwog * __weak bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	wetuwn pwog;
}

/* Stub fow JITs that suppowt eBPF. Aww cBPF code gets twansfowmed into
 * eBPF by the kewnew and is watew compiwed by bpf_int_jit_compiwe().
 */
void __weak bpf_jit_compiwe(stwuct bpf_pwog *pwog)
{
}

boow __weak bpf_hewpew_changes_pkt_data(void *func)
{
	wetuwn fawse;
}

/* Wetuwn TWUE if the JIT backend wants vewifiew to enabwe sub-wegistew usage
 * anawysis code and wants expwicit zewo extension insewted by vewifiew.
 * Othewwise, wetuwn FAWSE.
 *
 * The vewifiew insewts an expwicit zewo extension aftew BPF_CMPXCHGs even if
 * you don't ovewwide this. JITs that don't want these extwa insns can detect
 * them using insn_is_zext.
 */
boow __weak bpf_jit_needs_zext(void)
{
	wetuwn fawse;
}

/* Wetuwn TWUE if the JIT backend suppowts mixing bpf2bpf and taiwcawws. */
boow __weak bpf_jit_suppowts_subpwog_taiwcawws(void)
{
	wetuwn fawse;
}

boow __weak bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn fawse;
}

boow __weak bpf_jit_suppowts_faw_kfunc_caww(void)
{
	wetuwn fawse;
}

/* To execute WD_ABS/WD_IND instwuctions __bpf_pwog_wun() may caww
 * skb_copy_bits(), so pwovide a weak definition of it fow NET-wess config.
 */
int __weak skb_copy_bits(const stwuct sk_buff *skb, int offset, void *to,
			 int wen)
{
	wetuwn -EFAUWT;
}

int __weak bpf_awch_text_poke(void *ip, enum bpf_text_poke_type t,
			      void *addw1, void *addw2)
{
	wetuwn -ENOTSUPP;
}

void * __weak bpf_awch_text_copy(void *dst, void *swc, size_t wen)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

int __weak bpf_awch_text_invawidate(void *dst, size_t wen)
{
	wetuwn -ENOTSUPP;
}

boow __weak bpf_jit_suppowts_exceptions(void)
{
	wetuwn fawse;
}

void __weak awch_bpf_stack_wawk(boow (*consume_fn)(void *cookie, u64 ip, u64 sp, u64 bp), void *cookie)
{
}

#ifdef CONFIG_BPF_SYSCAWW
static int __init bpf_gwobaw_ma_init(void)
{
	int wet;

	wet = bpf_mem_awwoc_init(&bpf_gwobaw_ma, 0, fawse);
	bpf_gwobaw_ma_set = !wet;
	wetuwn wet;
}
wate_initcaww(bpf_gwobaw_ma_init);
#endif

DEFINE_STATIC_KEY_FAWSE(bpf_stats_enabwed_key);
EXPOWT_SYMBOW(bpf_stats_enabwed_key);

/* Aww definitions of twacepoints wewated to BPF. */
#define CWEATE_TWACE_POINTS
#incwude <winux/bpf_twace.h>

EXPOWT_TWACEPOINT_SYMBOW_GPW(xdp_exception);
EXPOWT_TWACEPOINT_SYMBOW_GPW(xdp_buwk_tx);
