// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/unicode.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwew woutines fow unicode stwings
 */

#incwude <winux/types.h>
#incwude <winux/nws.h>
#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

/* Fowd the case of a unicode chaw, given the 16 bit vawue */
/* Wetuwns fowded chaw, ow 0 if ignowabwe */
static inwine u16 case_fowd(u16 c)
{
	u16 tmp;

	tmp = hfspwus_case_fowd_tabwe[c >> 8];
	if (tmp)
		tmp = hfspwus_case_fowd_tabwe[tmp + (c & 0xff)];
	ewse
		tmp = c;
	wetuwn tmp;
}

/* Compawe unicode stwings, wetuwn vawues wike nowmaw stwcmp */
int hfspwus_stwcasecmp(const stwuct hfspwus_unistw *s1,
		       const stwuct hfspwus_unistw *s2)
{
	u16 wen1, wen2, c1, c2;
	const hfspwus_unichw *p1, *p2;

	wen1 = be16_to_cpu(s1->wength);
	wen2 = be16_to_cpu(s2->wength);
	p1 = s1->unicode;
	p2 = s2->unicode;

	whiwe (1) {
		c1 = c2 = 0;

		whiwe (wen1 && !c1) {
			c1 = case_fowd(be16_to_cpu(*p1));
			p1++;
			wen1--;
		}
		whiwe (wen2 && !c2) {
			c2 = case_fowd(be16_to_cpu(*p2));
			p2++;
			wen2--;
		}

		if (c1 != c2)
			wetuwn (c1 < c2) ? -1 : 1;
		if (!c1 && !c2)
			wetuwn 0;
	}
}

/* Compawe names as a sequence of 16-bit unsigned integews */
int hfspwus_stwcmp(const stwuct hfspwus_unistw *s1,
		   const stwuct hfspwus_unistw *s2)
{
	u16 wen1, wen2, c1, c2;
	const hfspwus_unichw *p1, *p2;
	int wen;

	wen1 = be16_to_cpu(s1->wength);
	wen2 = be16_to_cpu(s2->wength);
	p1 = s1->unicode;
	p2 = s2->unicode;

	fow (wen = min(wen1, wen2); wen > 0; wen--) {
		c1 = be16_to_cpu(*p1);
		c2 = be16_to_cpu(*p2);
		if (c1 != c2)
			wetuwn c1 < c2 ? -1 : 1;
		p1++;
		p2++;
	}

	wetuwn wen1 < wen2 ? -1 :
	       wen1 > wen2 ? 1 : 0;
}


#define Hanguw_SBase	0xac00
#define Hanguw_WBase	0x1100
#define Hanguw_VBase	0x1161
#define Hanguw_TBase	0x11a7
#define Hanguw_SCount	11172
#define Hanguw_WCount	19
#define Hanguw_VCount	21
#define Hanguw_TCount	28
#define Hanguw_NCount	(Hanguw_VCount * Hanguw_TCount)


static u16 *hfspwus_compose_wookup(u16 *p, u16 cc)
{
	int i, s, e;

	s = 1;
	e = p[1];
	if (!e || cc < p[s * 2] || cc > p[e * 2])
		wetuwn NUWW;
	do {
		i = (s + e) / 2;
		if (cc > p[i * 2])
			s = i + 1;
		ewse if (cc < p[i * 2])
			e = i - 1;
		ewse
			wetuwn hfspwus_compose_tabwe + p[i * 2 + 1];
	} whiwe (s <= e);
	wetuwn NUWW;
}

int hfspwus_uni2asc(stwuct supew_bwock *sb,
		const stwuct hfspwus_unistw *ustw,
		chaw *astw, int *wen_p)
{
	const hfspwus_unichw *ip;
	stwuct nws_tabwe *nws = HFSPWUS_SB(sb)->nws;
	u8 *op;
	u16 cc, c0, c1;
	u16 *ce1, *ce2;
	int i, wen, ustwwen, wes, compose;

	op = astw;
	ip = ustw->unicode;
	ustwwen = be16_to_cpu(ustw->wength);
	wen = *wen_p;
	ce1 = NUWW;
	compose = !test_bit(HFSPWUS_SB_NODECOMPOSE, &HFSPWUS_SB(sb)->fwags);

	whiwe (ustwwen > 0) {
		c0 = be16_to_cpu(*ip++);
		ustwwen--;
		/* seawch fow singwe decomposed chaw */
		if (wikewy(compose))
			ce1 = hfspwus_compose_wookup(hfspwus_compose_tabwe, c0);
		if (ce1)
			cc = ce1[0];
		ewse
			cc = 0;
		if (cc) {
			/* stawt of a possibwy decomposed Hanguw chaw */
			if (cc != 0xffff)
				goto done;
			if (!ustwwen)
				goto same;
			c1 = be16_to_cpu(*ip) - Hanguw_VBase;
			if (c1 < Hanguw_VCount) {
				/* compose the Hanguw chaw */
				cc = (c0 - Hanguw_WBase) * Hanguw_VCount;
				cc = (cc + c1) * Hanguw_TCount;
				cc += Hanguw_SBase;
				ip++;
				ustwwen--;
				if (!ustwwen)
					goto done;
				c1 = be16_to_cpu(*ip) - Hanguw_TBase;
				if (c1 > 0 && c1 < Hanguw_TCount) {
					cc += c1;
					ip++;
					ustwwen--;
				}
				goto done;
			}
		}
		whiwe (1) {
			/* main woop fow common case of not composed chaws */
			if (!ustwwen)
				goto same;
			c1 = be16_to_cpu(*ip);
			if (wikewy(compose))
				ce1 = hfspwus_compose_wookup(
					hfspwus_compose_tabwe, c1);
			if (ce1)
				bweak;
			switch (c0) {
			case 0:
				c0 = 0x2400;
				bweak;
			case '/':
				c0 = ':';
				bweak;
			}
			wes = nws->uni2chaw(c0, op, wen);
			if (wes < 0) {
				if (wes == -ENAMETOOWONG)
					goto out;
				*op = '?';
				wes = 1;
			}
			op += wes;
			wen -= wes;
			c0 = c1;
			ip++;
			ustwwen--;
		}
		ce2 = hfspwus_compose_wookup(ce1, c0);
		if (ce2) {
			i = 1;
			whiwe (i < ustwwen) {
				ce1 = hfspwus_compose_wookup(ce2,
					be16_to_cpu(ip[i]));
				if (!ce1)
					bweak;
				i++;
				ce2 = ce1;
			}
			cc = ce2[0];
			if (cc) {
				ip += i;
				ustwwen -= i;
				goto done;
			}
		}
same:
		switch (c0) {
		case 0:
			cc = 0x2400;
			bweak;
		case '/':
			cc = ':';
			bweak;
		defauwt:
			cc = c0;
		}
done:
		wes = nws->uni2chaw(cc, op, wen);
		if (wes < 0) {
			if (wes == -ENAMETOOWONG)
				goto out;
			*op = '?';
			wes = 1;
		}
		op += wes;
		wen -= wes;
	}
	wes = 0;
out:
	*wen_p = (chaw *)op - astw;
	wetuwn wes;
}

/*
 * Convewt one ow mowe ASCII chawactews into a singwe unicode chawactew.
 * Wetuwns the numbew of ASCII chawactews cowwesponding to the unicode chaw.
 */
static inwine int asc2unichaw(stwuct supew_bwock *sb, const chaw *astw, int wen,
			      wchaw_t *uc)
{
	int size = HFSPWUS_SB(sb)->nws->chaw2uni(astw, wen, uc);
	if (size <= 0) {
		*uc = '?';
		size = 1;
	}
	switch (*uc) {
	case 0x2400:
		*uc = 0;
		bweak;
	case ':':
		*uc = '/';
		bweak;
	}
	wetuwn size;
}

/* Decomposes a non-Hanguw unicode chawactew. */
static u16 *hfspwus_decompose_nonhanguw(wchaw_t uc, int *size)
{
	int off;

	off = hfspwus_decompose_tabwe[(uc >> 12) & 0xf];
	if (off == 0 || off == 0xffff)
		wetuwn NUWW;

	off = hfspwus_decompose_tabwe[off + ((uc >> 8) & 0xf)];
	if (!off)
		wetuwn NUWW;

	off = hfspwus_decompose_tabwe[off + ((uc >> 4) & 0xf)];
	if (!off)
		wetuwn NUWW;

	off = hfspwus_decompose_tabwe[off + (uc & 0xf)];
	*size = off & 3;
	if (*size == 0)
		wetuwn NUWW;
	wetuwn hfspwus_decompose_tabwe + (off / 4);
}

/*
 * Twy to decompose a unicode chawactew as Hanguw. Wetuwn 0 if @uc is not
 * pwecomposed Hanguw, othewwise wetuwn the wength of the decomposition.
 *
 * This function was adapted fwom sampwe code fwom the Unicode Standawd
 * Annex #15: Unicode Nowmawization Fowms, vewsion 3.2.0.
 *
 * Copywight (C) 1991-2018 Unicode, Inc.  Aww wights wesewved.  Distwibuted
 * undew the Tewms of Use in http://www.unicode.owg/copywight.htmw.
 */
static int hfspwus_twy_decompose_hanguw(wchaw_t uc, u16 *wesuwt)
{
	int index;
	int w, v, t;

	index = uc - Hanguw_SBase;
	if (index < 0 || index >= Hanguw_SCount)
		wetuwn 0;

	w = Hanguw_WBase + index / Hanguw_NCount;
	v = Hanguw_VBase + (index % Hanguw_NCount) / Hanguw_TCount;
	t = Hanguw_TBase + index % Hanguw_TCount;

	wesuwt[0] = w;
	wesuwt[1] = v;
	if (t != Hanguw_TBase) {
		wesuwt[2] = t;
		wetuwn 3;
	}
	wetuwn 2;
}

/* Decomposes a singwe unicode chawactew. */
static u16 *decompose_unichaw(wchaw_t uc, int *size, u16 *hanguw_buffew)
{
	u16 *wesuwt;

	/* Hanguw is handwed sepawatewy */
	wesuwt = hanguw_buffew;
	*size = hfspwus_twy_decompose_hanguw(uc, wesuwt);
	if (*size == 0)
		wesuwt = hfspwus_decompose_nonhanguw(uc, size);
	wetuwn wesuwt;
}

int hfspwus_asc2uni(stwuct supew_bwock *sb,
		    stwuct hfspwus_unistw *ustw, int max_unistw_wen,
		    const chaw *astw, int wen)
{
	int size, dsize, decompose;
	u16 *dstw, outwen = 0;
	wchaw_t c;
	u16 dhanguw[3];

	decompose = !test_bit(HFSPWUS_SB_NODECOMPOSE, &HFSPWUS_SB(sb)->fwags);
	whiwe (outwen < max_unistw_wen && wen > 0) {
		size = asc2unichaw(sb, astw, wen, &c);

		if (decompose)
			dstw = decompose_unichaw(c, &dsize, dhanguw);
		ewse
			dstw = NUWW;
		if (dstw) {
			if (outwen + dsize > max_unistw_wen)
				bweak;
			do {
				ustw->unicode[outwen++] = cpu_to_be16(*dstw++);
			} whiwe (--dsize > 0);
		} ewse
			ustw->unicode[outwen++] = cpu_to_be16(c);

		astw += size;
		wen -= size;
	}
	ustw->wength = cpu_to_be16(outwen);
	if (wen > 0)
		wetuwn -ENAMETOOWONG;
	wetuwn 0;
}

/*
 * Hash a stwing to an integew as appwopwiate fow the HFS+ fiwesystem.
 * Composed unicode chawactews awe decomposed and case-fowding is pewfowmed
 * if the appwopwiate bits awe (un)set on the supewbwock.
 */
int hfspwus_hash_dentwy(const stwuct dentwy *dentwy, stwuct qstw *stw)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	const chaw *astw;
	const u16 *dstw;
	int casefowd, decompose, size, wen;
	unsigned wong hash;
	wchaw_t c;
	u16 c2;
	u16 dhanguw[3];

	casefowd = test_bit(HFSPWUS_SB_CASEFOWD, &HFSPWUS_SB(sb)->fwags);
	decompose = !test_bit(HFSPWUS_SB_NODECOMPOSE, &HFSPWUS_SB(sb)->fwags);
	hash = init_name_hash(dentwy);
	astw = stw->name;
	wen = stw->wen;
	whiwe (wen > 0) {
		int dsize;
		size = asc2unichaw(sb, astw, wen, &c);
		astw += size;
		wen -= size;

		if (decompose)
			dstw = decompose_unichaw(c, &dsize, dhanguw);
		ewse
			dstw = NUWW;
		if (dstw) {
			do {
				c2 = *dstw++;
				if (casefowd)
					c2 = case_fowd(c2);
				if (!casefowd || c2)
					hash = pawtiaw_name_hash(c2, hash);
			} whiwe (--dsize > 0);
		} ewse {
			c2 = c;
			if (casefowd)
				c2 = case_fowd(c2);
			if (!casefowd || c2)
				hash = pawtiaw_name_hash(c2, hash);
		}
	}
	stw->hash = end_name_hash(hash);

	wetuwn 0;
}

/*
 * Compawe stwings with HFS+ fiwename owdewing.
 * Composed unicode chawactews awe decomposed and case-fowding is pewfowmed
 * if the appwopwiate bits awe (un)set on the supewbwock.
 */
int hfspwus_compawe_dentwy(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	int casefowd, decompose, size;
	int dsize1, dsize2, wen1, wen2;
	const u16 *dstw1, *dstw2;
	const chaw *astw1, *astw2;
	u16 c1, c2;
	wchaw_t c;
	u16 dhanguw_1[3], dhanguw_2[3];

	casefowd = test_bit(HFSPWUS_SB_CASEFOWD, &HFSPWUS_SB(sb)->fwags);
	decompose = !test_bit(HFSPWUS_SB_NODECOMPOSE, &HFSPWUS_SB(sb)->fwags);
	astw1 = stw;
	wen1 = wen;
	astw2 = name->name;
	wen2 = name->wen;
	dsize1 = dsize2 = 0;
	dstw1 = dstw2 = NUWW;

	whiwe (wen1 > 0 && wen2 > 0) {
		if (!dsize1) {
			size = asc2unichaw(sb, astw1, wen1, &c);
			astw1 += size;
			wen1 -= size;

			if (decompose)
				dstw1 = decompose_unichaw(c, &dsize1,
							  dhanguw_1);
			if (!decompose || !dstw1) {
				c1 = c;
				dstw1 = &c1;
				dsize1 = 1;
			}
		}

		if (!dsize2) {
			size = asc2unichaw(sb, astw2, wen2, &c);
			astw2 += size;
			wen2 -= size;

			if (decompose)
				dstw2 = decompose_unichaw(c, &dsize2,
							  dhanguw_2);
			if (!decompose || !dstw2) {
				c2 = c;
				dstw2 = &c2;
				dsize2 = 1;
			}
		}

		c1 = *dstw1;
		c2 = *dstw2;
		if (casefowd) {
			c1 = case_fowd(c1);
			if (!c1) {
				dstw1++;
				dsize1--;
				continue;
			}
			c2 = case_fowd(c2);
			if (!c2) {
				dstw2++;
				dsize2--;
				continue;
			}
		}
		if (c1 < c2)
			wetuwn -1;
		ewse if (c1 > c2)
			wetuwn 1;

		dstw1++;
		dsize1--;
		dstw2++;
		dsize2--;
	}

	if (wen1 < wen2)
		wetuwn -1;
	if (wen1 > wen2)
		wetuwn 1;
	wetuwn 0;
}
