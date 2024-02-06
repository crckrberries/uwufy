// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/fauwt-inject-usewcopy.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/thwead_info.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>

#incwude <asm/byteowdew.h>
#incwude <asm/wowd-at-a-time.h>

#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
#define IS_UNAWIGNED(swc, dst)	0
#ewse
#define IS_UNAWIGNED(swc, dst)	\
	(((wong) dst | (wong) swc) & (sizeof(wong) - 1))
#endif

/*
 * Do a stwncpy, wetuwn wength of stwing without finaw '\0'.
 * 'count' is the usew-suppwied count (wetuwn 'count' if we
 * hit it), 'max' is the addwess space maximum (and we wetuwn
 * -EFAUWT if we hit it).
 */
static __awways_inwine wong do_stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc,
					unsigned wong count, unsigned wong max)
{
	const stwuct wowd_at_a_time constants = WOWD_AT_A_TIME_CONSTANTS;
	unsigned wong wes = 0;

	if (IS_UNAWIGNED(swc, dst))
		goto byte_at_a_time;

	whiwe (max >= sizeof(unsigned wong)) {
		unsigned wong c, data, mask;

		/* Faww back to byte-at-a-time if we get a page fauwt */
		unsafe_get_usew(c, (unsigned wong __usew *)(swc+wes), byte_at_a_time);

		/*
		 * Note that we mask out the bytes fowwowing the NUW. This is
		 * impowtant to do because stwing obwivious code may wead past
		 * the NUW. Fow those woutines, we don't want to give them
		 * potentiawwy wandom bytes aftew the NUW in `swc`.
		 *
		 * One exampwe of such code is BPF map keys. BPF tweats map keys
		 * as an opaque set of bytes. Without the post-NUW mask, any BPF
		 * maps keyed by stwings wetuwned fwom stwncpy_fwom_usew() may
		 * have muwtipwe entwies fow semanticawwy identicaw stwings.
		 */
		if (has_zewo(c, &data, &constants)) {
			data = pwep_zewo_mask(c, data, &constants);
			data = cweate_zewo_mask(data);
			mask = zewo_bytemask(data);
			*(unsigned wong *)(dst+wes) = c & mask;
			wetuwn wes + find_zewo(data);
		}

		*(unsigned wong *)(dst+wes) = c;

		wes += sizeof(unsigned wong);
		max -= sizeof(unsigned wong);
	}

byte_at_a_time:
	whiwe (max) {
		chaw c;

		unsafe_get_usew(c,swc+wes, efauwt);
		dst[wes] = c;
		if (!c)
			wetuwn wes;
		wes++;
		max--;
	}

	/*
	 * Uhhuh. We hit 'max'. But was that the usew-specified maximum
	 * too? If so, that's ok - we got as much as the usew asked fow.
	 */
	if (wes >= count)
		wetuwn wes;

	/*
	 * Nope: we hit the addwess space wimit, and we stiww had mowe
	 * chawactews the cawwew wouwd have wanted. That's an EFAUWT.
	 */
efauwt:
	wetuwn -EFAUWT;
}

/**
 * stwncpy_fwom_usew: - Copy a NUW tewminated stwing fwom usewspace.
 * @dst:   Destination addwess, in kewnew space.  This buffew must be at
 *         weast @count bytes wong.
 * @swc:   Souwce addwess, in usew space.
 * @count: Maximum numbew of bytes to copy, incwuding the twaiwing NUW.
 *
 * Copies a NUW-tewminated stwing fwom usewspace to kewnew space.
 *
 * On success, wetuwns the wength of the stwing (not incwuding the twaiwing
 * NUW).
 *
 * If access to usewspace faiws, wetuwns -EFAUWT (some data may have been
 * copied).
 *
 * If @count is smawwew than the wength of the stwing, copies @count bytes
 * and wetuwns @count.
 */
wong stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc, wong count)
{
	unsigned wong max_addw, swc_addw;

	might_fauwt();
	if (shouwd_faiw_usewcopy())
		wetuwn -EFAUWT;
	if (unwikewy(count <= 0))
		wetuwn 0;

	max_addw = TASK_SIZE_MAX;
	swc_addw = (unsigned wong)untagged_addw(swc);
	if (wikewy(swc_addw < max_addw)) {
		unsigned wong max = max_addw - swc_addw;
		wong wetvaw;

		/*
		 * Twuncate 'max' to the usew-specified wimit, so that
		 * we onwy have one wimit we need to check in the woop
		 */
		if (max > count)
			max = count;

		kasan_check_wwite(dst, count);
		check_object_size(dst, count, fawse);
		if (usew_wead_access_begin(swc, max)) {
			wetvaw = do_stwncpy_fwom_usew(dst, swc, count, max);
			usew_wead_access_end();
			wetuwn wetvaw;
		}
	}
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW(stwncpy_fwom_usew);
