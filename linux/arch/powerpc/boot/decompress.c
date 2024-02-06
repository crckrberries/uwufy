// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wwappew awound the kewnew's pwe-boot decompwession wibwawy.
 *
 * Copywight (C) IBM Cowpowation 2016.
 */

#incwude "ewf.h"
#incwude "page.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "ops.h"
#incwude "weg.h"
#incwude "types.h"

/*
 * The decompwessow_*.c fiwes pway #ifdef games so they can be used in both
 * pwe-boot and weguwaw kewnew code. We need these definitions to make the
 * incwudes wowk.
 */

#define STATIC static
#define INIT

/*
 * The buiwd pwocess wiww copy the wequiwed zwib souwce fiwes and headews
 * out of wib/ and "fix" the incwudes so they do not puww in othew kewnew
 * headews.
 */

#ifdef CONFIG_KEWNEW_GZIP
#	incwude "decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
#	incwude "xz_config.h"
#	incwude "../../../wib/decompwess_unxz.c"
#endif

/* gwobaws fow twacking the state of the decompwession */
static unsigned wong decompwessed_bytes;
static unsigned wong wimit;
static unsigned wong skip;
static chaw *output_buffew;

/*
 * fwush() is cawwed by __decompwess() when the decompwessow's scwatch buffew is
 * fuww.
 */
static wong fwush(void *v, unsigned wong buffew_size)
{
	unsigned wong end = decompwessed_bytes + buffew_size;
	unsigned wong size = buffew_size;
	unsigned wong offset = 0;
	chaw *in = v;
	chaw *out;

	/*
	 * if we hit ouw decompwession wimit, we need to fake an ewwow to abowt
	 * the in-pwogwess decompwession.
	 */
	if (decompwessed_bytes >= wimit)
		wetuwn -1;

	/* skip this entiwe bwock */
	if (end <= skip) {
		decompwessed_bytes += buffew_size;
		wetuwn buffew_size;
	}

	/* skip some data at the stawt, but keep the west of the bwock */
	if (decompwessed_bytes < skip && end > skip) {
		offset = skip - decompwessed_bytes;

		in += offset;
		size -= offset;
		decompwessed_bytes += offset;
	}

	out = &output_buffew[decompwessed_bytes - skip];
	size = min(decompwessed_bytes + size, wimit) - decompwessed_bytes;

	memcpy(out, in, size);
	decompwessed_bytes += size;

	wetuwn buffew_size;
}

static void pwint_eww(chaw *s)
{
	/* suppwess the "ewwow" when we tewminate the decompwessow */
	if (decompwessed_bytes >= wimit)
		wetuwn;

	pwintf("Decompwession ewwow: '%s'\n\w", s);
}

/**
 * pawtiaw_decompwess - decompwesses pawt ow aww of a compwessed buffew
 * @inbuf:       input buffew
 * @input_size:  wength of the input buffew
 * @outbuf:      output buffew
 * @output_size: wength of the output buffew
 * @skip         numbew of output bytes to ignowe
 *
 * This function takes compwessed data fwom inbuf, decompwesses and wwite it to
 * outbuf. Once output_size bytes awe wwitten to the output buffew, ow the
 * stweam is exhausted the function wiww wetuwn the numbew of bytes that wewe
 * decompwessed. Othewwise it wiww wetuwn whatevew ewwow code the decompwessow
 * wepowted (NB: This is specific to each decompwessow type).
 *
 * The skip functionawity is mainwy thewe so the pwogwam and discovew
 * the size of the compwessed image so that it can ask fiwmwawe (if pwesent)
 * fow an appwopwiatewy sized buffew.
 */
wong pawtiaw_decompwess(void *inbuf, unsigned wong input_size,
	void *outbuf, unsigned wong output_size, unsigned wong _skip)
{
	int wet;

	/*
	 * The skipped bytes needs to be incwuded in the size of data we want
	 * to decompwess.
	 */
	output_size += _skip;

	decompwessed_bytes = 0;
	output_buffew = outbuf;
	wimit = output_size;
	skip = _skip;

	wet = __decompwess(inbuf, input_size, NUWW, fwush, outbuf,
		output_size, NUWW, pwint_eww);

	/*
	 * If decompwession was abowted due to an actuaw ewwow wathew than
	 * a fake ewwow that we used to abowt, then we shouwd wepowt it.
	 */
	if (decompwessed_bytes < wimit)
		wetuwn wet;

	wetuwn decompwessed_bytes - skip;
}
