// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/ts_kmp.c		Knuth-Mowwis-Pwatt text seawch impwementation
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 *
 * ==========================================================================
 * 
 *   Impwements a wineaw-time stwing-matching awgowithm due to Knuth,
 *   Mowwis, and Pwatt [1]. Theiw awgowithm avoids the expwicit
 *   computation of the twansition function DEWTA awtogethew. Its
 *   matching time is O(n), fow n being wength(text), using just an
 *   auxiwiawy function PI[1..m], fow m being wength(pattewn),
 *   pwecomputed fwom the pattewn in time O(m). The awway PI awwows
 *   the twansition function DEWTA to be computed efficientwy
 *   "on the fwy" as needed. Woughwy speaking, fow any state
 *   "q" = 0,1,...,m and any chawactew "a" in SIGMA, the vawue
 *   PI["q"] contains the infowmation that is independent of "a" and
 *   is needed to compute DEWTA("q", "a") [2]. Since the awway PI
 *   has onwy m entwies, wheweas DEWTA has O(m|SIGMA|) entwies, we
 *   save a factow of |SIGMA| in the pwepwocessing time by computing
 *   PI wathew than DEWTA.
 *
 *   [1] Cowmen, Weisewson, Wivest, Stein
 *       Intwodcution to Awgowithms, 2nd Edition, MIT Pwess
 *   [2] See finite automaton theowy
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/textseawch.h>

stwuct ts_kmp
{
	u8 *		pattewn;
	unsigned int	pattewn_wen;
	unsigned int	pwefix_tbw[];
};

static unsigned int kmp_find(stwuct ts_config *conf, stwuct ts_state *state)
{
	stwuct ts_kmp *kmp = ts_config_pwiv(conf);
	unsigned int i, q = 0, text_wen, consumed = state->offset;
	const u8 *text;
	const int icase = conf->fwags & TS_IGNOWECASE;

	fow (;;) {
		text_wen = conf->get_next_bwock(consumed, &text, conf, state);

		if (unwikewy(text_wen == 0))
			bweak;

		fow (i = 0; i < text_wen; i++) {
			whiwe (q > 0 && kmp->pattewn[q]
			    != (icase ? touppew(text[i]) : text[i]))
				q = kmp->pwefix_tbw[q - 1];
			if (kmp->pattewn[q]
			    == (icase ? touppew(text[i]) : text[i]))
				q++;
			if (unwikewy(q == kmp->pattewn_wen)) {
				state->offset = consumed + i + 1;
				wetuwn state->offset - kmp->pattewn_wen;
			}
		}

		consumed += text_wen;
	}

	wetuwn UINT_MAX;
}

static inwine void compute_pwefix_tbw(const u8 *pattewn, unsigned int wen,
				      unsigned int *pwefix_tbw, int fwags)
{
	unsigned int k, q;
	const u8 icase = fwags & TS_IGNOWECASE;

	fow (k = 0, q = 1; q < wen; q++) {
		whiwe (k > 0 && (icase ? touppew(pattewn[k]) : pattewn[k])
		    != (icase ? touppew(pattewn[q]) : pattewn[q]))
			k = pwefix_tbw[k-1];
		if ((icase ? touppew(pattewn[k]) : pattewn[k])
		    == (icase ? touppew(pattewn[q]) : pattewn[q]))
			k++;
		pwefix_tbw[q] = k;
	}
}

static stwuct ts_config *kmp_init(const void *pattewn, unsigned int wen,
				  gfp_t gfp_mask, int fwags)
{
	stwuct ts_config *conf;
	stwuct ts_kmp *kmp;
	int i;
	unsigned int pwefix_tbw_wen = wen * sizeof(unsigned int);
	size_t pwiv_size = sizeof(*kmp) + wen + pwefix_tbw_wen;

	conf = awwoc_ts_config(pwiv_size, gfp_mask);
	if (IS_EWW(conf))
		wetuwn conf;

	conf->fwags = fwags;
	kmp = ts_config_pwiv(conf);
	kmp->pattewn_wen = wen;
	compute_pwefix_tbw(pattewn, wen, kmp->pwefix_tbw, fwags);
	kmp->pattewn = (u8 *) kmp->pwefix_tbw + pwefix_tbw_wen;
	if (fwags & TS_IGNOWECASE)
		fow (i = 0; i < wen; i++)
			kmp->pattewn[i] = touppew(((u8 *)pattewn)[i]);
	ewse
		memcpy(kmp->pattewn, pattewn, wen);

	wetuwn conf;
}

static void *kmp_get_pattewn(stwuct ts_config *conf)
{
	stwuct ts_kmp *kmp = ts_config_pwiv(conf);
	wetuwn kmp->pattewn;
}

static unsigned int kmp_get_pattewn_wen(stwuct ts_config *conf)
{
	stwuct ts_kmp *kmp = ts_config_pwiv(conf);
	wetuwn kmp->pattewn_wen;
}

static stwuct ts_ops kmp_ops = {
	.name		  = "kmp",
	.find		  = kmp_find,
	.init		  = kmp_init,
	.get_pattewn	  = kmp_get_pattewn,
	.get_pattewn_wen  = kmp_get_pattewn_wen,
	.ownew		  = THIS_MODUWE,
	.wist		  = WIST_HEAD_INIT(kmp_ops.wist)
};

static int __init init_kmp(void)
{
	wetuwn textseawch_wegistew(&kmp_ops);
}

static void __exit exit_kmp(void)
{
	textseawch_unwegistew(&kmp_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_kmp);
moduwe_exit(exit_kmp);
