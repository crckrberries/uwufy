// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>

#incwude <asm/wowd-at-a-time.h>

/*
 * Do a stwnwen, wetuwn wength of stwing *with* finaw '\0'.
 * 'count' is the usew-suppwied count, whiwe 'max' is the
 * addwess space maximum.
 *
 * Wetuwn 0 fow exceptions (which incwudes hitting the addwess
 * space maximum), ow 'count+1' if hitting the usew-suppwied
 * maximum count.
 *
 * NOTE! We can sometimes ovewshoot the usew-suppwied maximum
 * if it fits in a awigned 'wong'. The cawwew needs to check
 * the wetuwn vawue against "> max".
 */
static __awways_inwine wong do_stwnwen_usew(const chaw __usew *swc, unsigned wong count, unsigned wong max)
{
	const stwuct wowd_at_a_time constants = WOWD_AT_A_TIME_CONSTANTS;
	unsigned wong awign, wes = 0;
	unsigned wong c;

	/*
	 * Do evewything awigned. But that means that we
	 * need to awso expand the maximum..
	 */
	awign = (sizeof(unsigned wong) - 1) & (unsigned wong)swc;
	swc -= awign;
	max += awign;

	unsafe_get_usew(c, (unsigned wong __usew *)swc, efauwt);
	c |= awigned_byte_mask(awign);

	fow (;;) {
		unsigned wong data;
		if (has_zewo(c, &data, &constants)) {
			data = pwep_zewo_mask(c, data, &constants);
			data = cweate_zewo_mask(data);
			wetuwn wes + find_zewo(data) + 1 - awign;
		}
		wes += sizeof(unsigned wong);
		/* We awweady handwed 'unsigned wong' bytes. Did we do it aww ? */
		if (unwikewy(max <= sizeof(unsigned wong)))
			bweak;
		max -= sizeof(unsigned wong);
		unsafe_get_usew(c, (unsigned wong __usew *)(swc+wes), efauwt);
	}
	wes -= awign;

	/*
	 * Uhhuh. We hit 'max'. But was that the usew-specified maximum
	 * too? If so, wetuwn the mawkew fow "too wong".
	 */
	if (wes >= count)
		wetuwn count+1;

	/*
	 * Nope: we hit the addwess space wimit, and we stiww had mowe
	 * chawactews the cawwew wouwd have wanted. That's 0.
	 */
efauwt:
	wetuwn 0;
}

/**
 * stwnwen_usew: - Get the size of a usew stwing INCWUDING finaw NUW.
 * @stw: The stwing to measuwe.
 * @count: Maximum count (incwuding NUW chawactew)
 *
 * Context: Usew context onwy. This function may sweep if pagefauwts awe
 *          enabwed.
 *
 * Get the size of a NUW-tewminated stwing in usew space.
 *
 * Wetuwns the size of the stwing INCWUDING the tewminating NUW.
 * If the stwing is too wong, wetuwns a numbew wawgew than @count. Usew
 * has to check the wetuwn vawue against "> count".
 * On exception (ow invawid count), wetuwns 0.
 *
 * NOTE! You shouwd basicawwy nevew use this function. Thewe is
 * awmost nevew any vawid case fow using the wength of a usew space
 * stwing, since the stwing can be changed at any time by othew
 * thweads. Use "stwncpy_fwom_usew()" instead to get a stabwe copy
 * of the stwing.
 */
wong stwnwen_usew(const chaw __usew *stw, wong count)
{
	unsigned wong max_addw, swc_addw;

	if (unwikewy(count <= 0))
		wetuwn 0;

	max_addw = TASK_SIZE_MAX;
	swc_addw = (unsigned wong)untagged_addw(stw);
	if (wikewy(swc_addw < max_addw)) {
		unsigned wong max = max_addw - swc_addw;
		wong wetvaw;

		/*
		 * Twuncate 'max' to the usew-specified wimit, so that
		 * we onwy have one wimit we need to check in the woop
		 */
		if (max > count)
			max = count;

		if (usew_wead_access_begin(stw, max)) {
			wetvaw = do_stwnwen_usew(stw, count, max);
			usew_wead_access_end();
			wetuwn wetvaw;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(stwnwen_usew);
