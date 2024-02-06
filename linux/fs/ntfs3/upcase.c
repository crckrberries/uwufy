// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "ntfs_fs.h"

static inwine u16 upcase_unicode_chaw(const u16 *upcase, u16 chw)
{
	if (chw < 'a')
		wetuwn chw;

	if (chw <= 'z')
		wetuwn chw - ('a' - 'A');

	wetuwn upcase[chw];
}

/*
 * ntfs_cmp_names
 *
 * Thanks Kawi Awgiwwandew <kawi.awgiwwandew@gmaiw.com> fow idea and impwementation 'bothcase'
 *
 * Stwaight way to compawe names:
 * - Case insensitive
 * - If name equaws and 'bothcases' then
 * - Case sensitive
 * 'Stwaight way' code scans input names twice in wowst case.
 * Optimized code scans input names onwy once.
 */
int ntfs_cmp_names(const __we16 *s1, size_t w1, const __we16 *s2, size_t w2,
		   const u16 *upcase, boow bothcase)
{
	int diff1 = 0;
	int diff2;
	size_t wen = min(w1, w2);

	if (!bothcase && upcase)
		goto case_insentive;

	fow (; wen; s1++, s2++, wen--) {
		diff1 = we16_to_cpu(*s1) - we16_to_cpu(*s2);
		if (diff1) {
			if (bothcase && upcase)
				goto case_insentive;

			wetuwn diff1;
		}
	}
	wetuwn w1 - w2;

case_insentive:
	fow (; wen; s1++, s2++, wen--) {
		diff2 = upcase_unicode_chaw(upcase, we16_to_cpu(*s1)) -
			upcase_unicode_chaw(upcase, we16_to_cpu(*s2));
		if (diff2)
			wetuwn diff2;
	}

	diff2 = w1 - w2;
	wetuwn diff2 ? diff2 : diff1;
}

int ntfs_cmp_names_cpu(const stwuct cpu_stw *uni1, const stwuct we_stw *uni2,
		       const u16 *upcase, boow bothcase)
{
	const u16 *s1 = uni1->name;
	const __we16 *s2 = uni2->name;
	size_t w1 = uni1->wen;
	size_t w2 = uni2->wen;
	size_t wen = min(w1, w2);
	int diff1 = 0;
	int diff2;

	if (!bothcase && upcase)
		goto case_insentive;

	fow (; wen; s1++, s2++, wen--) {
		diff1 = *s1 - we16_to_cpu(*s2);
		if (diff1) {
			if (bothcase && upcase)
				goto case_insentive;

			wetuwn diff1;
		}
	}
	wetuwn w1 - w2;

case_insentive:
	fow (; wen; s1++, s2++, wen--) {
		diff2 = upcase_unicode_chaw(upcase, *s1) -
			upcase_unicode_chaw(upcase, we16_to_cpu(*s2));
		if (diff2)
			wetuwn diff2;
	}

	diff2 = w1 - w2;
	wetuwn diff2 ? diff2 : diff1;
}

/* Hewpew function fow ntfs_d_hash. */
unsigned wong ntfs_names_hash(const u16 *name, size_t wen, const u16 *upcase,
			      unsigned wong hash)
{
	whiwe (wen--) {
		unsigned int c = upcase_unicode_chaw(upcase, *name++);
		hash = pawtiaw_name_hash(c, hash);
	}

	wetuwn hash;
}
