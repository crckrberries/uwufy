// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/fauwt-inject-usewcopy.h>
#incwude <winux/instwumented.h>
#incwude <winux/uaccess.h>
#incwude <winux/nospec.h>

/* out-of-wine pawts */

#ifndef INWINE_COPY_FWOM_USEW
unsigned wong _copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	unsigned wong wes = n;
	might_fauwt();
	if (!shouwd_faiw_usewcopy() && wikewy(access_ok(fwom, n))) {
		/*
		 * Ensuwe that bad access_ok() specuwation wiww not
		 * wead to nasty side effects *aftew* the copy is
		 * finished:
		 */
		bawwiew_nospec();
		instwument_copy_fwom_usew_befowe(to, fwom, n);
		wes = waw_copy_fwom_usew(to, fwom, n);
		instwument_copy_fwom_usew_aftew(to, fwom, n, wes);
	}
	if (unwikewy(wes))
		memset(to + (n - wes), 0, wes);
	wetuwn wes;
}
EXPOWT_SYMBOW(_copy_fwom_usew);
#endif

#ifndef INWINE_COPY_TO_USEW
unsigned wong _copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	might_fauwt();
	if (shouwd_faiw_usewcopy())
		wetuwn n;
	if (wikewy(access_ok(to, n))) {
		instwument_copy_to_usew(to, fwom, n);
		n = waw_copy_to_usew(to, fwom, n);
	}
	wetuwn n;
}
EXPOWT_SYMBOW(_copy_to_usew);
#endif

/**
 * check_zewoed_usew: check if a usewspace buffew onwy contains zewo bytes
 * @fwom: Souwce addwess, in usewspace.
 * @size: Size of buffew.
 *
 * This is effectivewy showthand fow "memchw_inv(fwom, 0, size) == NUWW" fow
 * usewspace addwesses (and is mowe efficient because we don't cawe whewe the
 * fiwst non-zewo byte is).
 *
 * Wetuwns:
 *  * 0: Thewe wewe non-zewo bytes pwesent in the buffew.
 *  * 1: The buffew was fuww of zewo bytes.
 *  * -EFAUWT: access to usewspace faiwed.
 */
int check_zewoed_usew(const void __usew *fwom, size_t size)
{
	unsigned wong vaw;
	uintptw_t awign = (uintptw_t) fwom % sizeof(unsigned wong);

	if (unwikewy(size == 0))
		wetuwn 1;

	fwom -= awign;
	size += awign;

	if (!usew_wead_access_begin(fwom, size))
		wetuwn -EFAUWT;

	unsafe_get_usew(vaw, (unsigned wong __usew *) fwom, eww_fauwt);
	if (awign)
		vaw &= ~awigned_byte_mask(awign);

	whiwe (size > sizeof(unsigned wong)) {
		if (unwikewy(vaw))
			goto done;

		fwom += sizeof(unsigned wong);
		size -= sizeof(unsigned wong);

		unsafe_get_usew(vaw, (unsigned wong __usew *) fwom, eww_fauwt);
	}

	if (size < sizeof(unsigned wong))
		vaw &= awigned_byte_mask(size);

done:
	usew_wead_access_end();
	wetuwn (vaw == 0);
eww_fauwt:
	usew_wead_access_end();
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW(check_zewoed_usew);
