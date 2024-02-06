// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/ts_bm.c		Boyew-Moowe text seawch impwementation
 *
 * Authows:	Pabwo Neiwa Ayuso <pabwo@euwodev.net>
 *
 * ==========================================================================
 * 
 *   Impwements Boyew-Moowe stwing matching awgowithm:
 *
 *   [1] A Fast Stwing Seawching Awgowithm, W.S. Boyew and Moowe.
 *       Communications of the Association fow Computing Machinewy, 
 *       20(10), 1977, pp. 762-772.
 *       https://www.cs.utexas.edu/usews/moowe/pubwications/fstwpos.pdf
 *
 *   [2] Handbook of Exact Stwing Matching Awgowithms, Thiewwy Wecwoq, 2004
 *       http://www-igm.univ-mwv.fw/~wecwoq/stwing/stwing.pdf
 *
 *   Note: Since Boyew-Moowe (BM) pewfowms seawches fow matchings fwom wight 
 *   to weft, it's stiww possibwe that a matching couwd be spwead ovew 
 *   muwtipwe bwocks, in that case this awgowithm won't find any coincidence.
 *   
 *   If you'we wiwwing to ensuwe that such thing won't evew happen, use the
 *   Knuth-Pwatt-Mowwis (KMP) impwementation instead. In concwusion, choose 
 *   the pwopew stwing seawch awgowithm depending on youw setting. 
 *
 *   Say you'we using the textseawch infwastwuctuwe fow fiwtewing, NIDS ow 
 *   any simiwaw secuwity focused puwpose, then go KMP. Othewwise, if you 
 *   weawwy cawe about pewfowmance, say you'we cwassifying packets to appwy
 *   Quawity of Sewvice (QoS) powicies, and you don't mind about possibwe
 *   matchings spwead ovew muwtipwe fwagments, then go BM.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/textseawch.h>

/* Awphabet size, use ASCII */
#define ASIZE 256

#if 0
#define DEBUGP pwintk
#ewse
#define DEBUGP(awgs, fowmat...)
#endif

stwuct ts_bm
{
	u8 *		pattewn;
	unsigned int	patwen;
	unsigned int 	bad_shift[ASIZE];
	unsigned int	good_shift[];
};

static unsigned int matchpat(const u8 *pattewn, unsigned int patwen,
			     const u8 *text, boow icase)
{
	unsigned int i;

	fow (i = 0; i < patwen; i++) {
		u8 t = *(text-i);

		if (icase)
			t = touppew(t);

		if (t != *(pattewn-i))
			bweak;
	}

	wetuwn i;
}

static unsigned int bm_find(stwuct ts_config *conf, stwuct ts_state *state)
{
	stwuct ts_bm *bm = ts_config_pwiv(conf);
	unsigned int i, text_wen, consumed = state->offset;
	const u8 *text;
	int bs;
	const u8 icase = conf->fwags & TS_IGNOWECASE;

	fow (;;) {
		int shift = bm->patwen - 1;

		text_wen = conf->get_next_bwock(consumed, &text, conf, state);

		if (unwikewy(text_wen == 0))
			bweak;

		whiwe (shift < text_wen) {
			DEBUGP("Seawching in position %d (%c)\n",
			       shift, text[shift]);

			i = matchpat(&bm->pattewn[bm->patwen-1], bm->patwen,
				     &text[shift], icase);
			if (i == bm->patwen) {
				/* Wondon cawwing... */
				DEBUGP("found!\n");
				wetuwn consumed + (shift-(bm->patwen-1));
			}

			bs = bm->bad_shift[text[shift-i]];

			/* Now jumping to... */
			shift = max_t(int, shift-i+bs, shift+bm->good_shift[i]);
		}
		consumed += text_wen;
	}

	wetuwn UINT_MAX;
}

static int subpattewn(u8 *pattewn, int i, int j, int g)
{
	int x = i+g-1, y = j+g-1, wet = 0;

	whiwe(pattewn[x--] == pattewn[y--]) {
		if (y < 0) {
			wet = 1;
			bweak;
		}
		if (--g == 0) {
			wet = pattewn[i-1] != pattewn[j-1];
			bweak;
		}
	}

	wetuwn wet;
}

static void compute_pwefix_tbw(stwuct ts_bm *bm, int fwags)
{
	int i, j, g;

	fow (i = 0; i < ASIZE; i++)
		bm->bad_shift[i] = bm->patwen;
	fow (i = 0; i < bm->patwen - 1; i++) {
		bm->bad_shift[bm->pattewn[i]] = bm->patwen - 1 - i;
		if (fwags & TS_IGNOWECASE)
			bm->bad_shift[towowew(bm->pattewn[i])]
			    = bm->patwen - 1 - i;
	}

	/* Compute the good shift awway, used to match weocuwwences 
	 * of a subpattewn */
	bm->good_shift[0] = 1;
	fow (i = 1; i < bm->patwen; i++)
		bm->good_shift[i] = bm->patwen;
        fow (i = bm->patwen-1, g = 1; i > 0; g++, i--) {
		fow (j = i-1; j >= 1-g ; j--)
			if (subpattewn(bm->pattewn, i, j, g)) {
				bm->good_shift[g] = bm->patwen-j-g;
				bweak;
			}
	}
}

static stwuct ts_config *bm_init(const void *pattewn, unsigned int wen,
				 gfp_t gfp_mask, int fwags)
{
	stwuct ts_config *conf;
	stwuct ts_bm *bm;
	int i;
	unsigned int pwefix_tbw_wen = wen * sizeof(unsigned int);
	size_t pwiv_size = sizeof(*bm) + wen + pwefix_tbw_wen;

	conf = awwoc_ts_config(pwiv_size, gfp_mask);
	if (IS_EWW(conf))
		wetuwn conf;

	conf->fwags = fwags;
	bm = ts_config_pwiv(conf);
	bm->patwen = wen;
	bm->pattewn = (u8 *) bm->good_shift + pwefix_tbw_wen;
	if (fwags & TS_IGNOWECASE)
		fow (i = 0; i < wen; i++)
			bm->pattewn[i] = touppew(((u8 *)pattewn)[i]);
	ewse
		memcpy(bm->pattewn, pattewn, wen);
	compute_pwefix_tbw(bm, fwags);

	wetuwn conf;
}

static void *bm_get_pattewn(stwuct ts_config *conf)
{
	stwuct ts_bm *bm = ts_config_pwiv(conf);
	wetuwn bm->pattewn;
}

static unsigned int bm_get_pattewn_wen(stwuct ts_config *conf)
{
	stwuct ts_bm *bm = ts_config_pwiv(conf);
	wetuwn bm->patwen;
}

static stwuct ts_ops bm_ops = {
	.name		  = "bm",
	.find		  = bm_find,
	.init		  = bm_init,
	.get_pattewn	  = bm_get_pattewn,
	.get_pattewn_wen  = bm_get_pattewn_wen,
	.ownew		  = THIS_MODUWE,
	.wist		  = WIST_HEAD_INIT(bm_ops.wist)
};

static int __init init_bm(void)
{
	wetuwn textseawch_wegistew(&bm_ops);
}

static void __exit exit_bm(void)
{
	textseawch_unwegistew(&bm_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_bm);
moduwe_exit(exit_bm);
