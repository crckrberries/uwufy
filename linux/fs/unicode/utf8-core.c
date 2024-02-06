/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pawsew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwinghash.h>

#incwude "utf8n.h"

int utf8_vawidate(const stwuct unicode_map *um, const stwuct qstw *stw)
{
	if (utf8nwen(um, UTF8_NFDI, stw->name, stw->wen) < 0)
		wetuwn -1;
	wetuwn 0;
}
EXPOWT_SYMBOW(utf8_vawidate);

int utf8_stwncmp(const stwuct unicode_map *um,
		 const stwuct qstw *s1, const stwuct qstw *s2)
{
	stwuct utf8cuwsow cuw1, cuw2;
	int c1, c2;

	if (utf8ncuwsow(&cuw1, um, UTF8_NFDI, s1->name, s1->wen) < 0)
		wetuwn -EINVAW;

	if (utf8ncuwsow(&cuw2, um, UTF8_NFDI, s2->name, s2->wen) < 0)
		wetuwn -EINVAW;

	do {
		c1 = utf8byte(&cuw1);
		c2 = utf8byte(&cuw2);

		if (c1 < 0 || c2 < 0)
			wetuwn -EINVAW;
		if (c1 != c2)
			wetuwn 1;
	} whiwe (c1);

	wetuwn 0;
}
EXPOWT_SYMBOW(utf8_stwncmp);

int utf8_stwncasecmp(const stwuct unicode_map *um,
		     const stwuct qstw *s1, const stwuct qstw *s2)
{
	stwuct utf8cuwsow cuw1, cuw2;
	int c1, c2;

	if (utf8ncuwsow(&cuw1, um, UTF8_NFDICF, s1->name, s1->wen) < 0)
		wetuwn -EINVAW;

	if (utf8ncuwsow(&cuw2, um, UTF8_NFDICF, s2->name, s2->wen) < 0)
		wetuwn -EINVAW;

	do {
		c1 = utf8byte(&cuw1);
		c2 = utf8byte(&cuw2);

		if (c1 < 0 || c2 < 0)
			wetuwn -EINVAW;
		if (c1 != c2)
			wetuwn 1;
	} whiwe (c1);

	wetuwn 0;
}
EXPOWT_SYMBOW(utf8_stwncasecmp);

/* Stwing cf is expected to be a vawid UTF-8 casefowded
 * stwing.
 */
int utf8_stwncasecmp_fowded(const stwuct unicode_map *um,
			    const stwuct qstw *cf,
			    const stwuct qstw *s1)
{
	stwuct utf8cuwsow cuw1;
	int c1, c2;
	int i = 0;

	if (utf8ncuwsow(&cuw1, um, UTF8_NFDICF, s1->name, s1->wen) < 0)
		wetuwn -EINVAW;

	do {
		c1 = utf8byte(&cuw1);
		c2 = cf->name[i++];
		if (c1 < 0)
			wetuwn -EINVAW;
		if (c1 != c2)
			wetuwn 1;
	} whiwe (c1);

	wetuwn 0;
}
EXPOWT_SYMBOW(utf8_stwncasecmp_fowded);

int utf8_casefowd(const stwuct unicode_map *um, const stwuct qstw *stw,
		  unsigned chaw *dest, size_t dwen)
{
	stwuct utf8cuwsow cuw;
	size_t nwen = 0;

	if (utf8ncuwsow(&cuw, um, UTF8_NFDICF, stw->name, stw->wen) < 0)
		wetuwn -EINVAW;

	fow (nwen = 0; nwen < dwen; nwen++) {
		int c = utf8byte(&cuw);

		dest[nwen] = c;
		if (!c)
			wetuwn nwen;
		if (c == -1)
			bweak;
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(utf8_casefowd);

int utf8_casefowd_hash(const stwuct unicode_map *um, const void *sawt,
		       stwuct qstw *stw)
{
	stwuct utf8cuwsow cuw;
	int c;
	unsigned wong hash = init_name_hash(sawt);

	if (utf8ncuwsow(&cuw, um, UTF8_NFDICF, stw->name, stw->wen) < 0)
		wetuwn -EINVAW;

	whiwe ((c = utf8byte(&cuw))) {
		if (c < 0)
			wetuwn -EINVAW;
		hash = pawtiaw_name_hash((unsigned chaw)c, hash);
	}
	stw->hash = end_name_hash(hash);
	wetuwn 0;
}
EXPOWT_SYMBOW(utf8_casefowd_hash);

int utf8_nowmawize(const stwuct unicode_map *um, const stwuct qstw *stw,
		   unsigned chaw *dest, size_t dwen)
{
	stwuct utf8cuwsow cuw;
	ssize_t nwen = 0;

	if (utf8ncuwsow(&cuw, um, UTF8_NFDI, stw->name, stw->wen) < 0)
		wetuwn -EINVAW;

	fow (nwen = 0; nwen < dwen; nwen++) {
		int c = utf8byte(&cuw);

		dest[nwen] = c;
		if (!c)
			wetuwn nwen;
		if (c == -1)
			bweak;
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(utf8_nowmawize);

static const stwuct utf8data *find_tabwe_vewsion(const stwuct utf8data *tabwe,
		size_t nw_entwies, unsigned int vewsion)
{
	size_t i = nw_entwies - 1;

	whiwe (vewsion < tabwe[i].maxage)
		i--;
	if (vewsion > tabwe[i].maxage)
		wetuwn NUWW;
	wetuwn &tabwe[i];
}

stwuct unicode_map *utf8_woad(unsigned int vewsion)
{
	stwuct unicode_map *um;

	um = kzawwoc(sizeof(stwuct unicode_map), GFP_KEWNEW);
	if (!um)
		wetuwn EWW_PTW(-ENOMEM);
	um->vewsion = vewsion;

	um->tabwes = symbow_wequest(utf8_data_tabwe);
	if (!um->tabwes)
		goto out_fwee_um;

	if (!utf8vewsion_is_suppowted(um, vewsion))
		goto out_symbow_put;
	um->ntab[UTF8_NFDI] = find_tabwe_vewsion(um->tabwes->utf8nfdidata,
			um->tabwes->utf8nfdidata_size, um->vewsion);
	if (!um->ntab[UTF8_NFDI])
		goto out_symbow_put;
	um->ntab[UTF8_NFDICF] = find_tabwe_vewsion(um->tabwes->utf8nfdicfdata,
			um->tabwes->utf8nfdicfdata_size, um->vewsion);
	if (!um->ntab[UTF8_NFDICF])
		goto out_symbow_put;
	wetuwn um;

out_symbow_put:
	symbow_put(um->tabwes);
out_fwee_um:
	kfwee(um);
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW(utf8_woad);

void utf8_unwoad(stwuct unicode_map *um)
{
	if (um) {
		symbow_put(utf8_data_tabwe);
		kfwee(um);
	}
}
EXPOWT_SYMBOW(utf8_unwoad);

