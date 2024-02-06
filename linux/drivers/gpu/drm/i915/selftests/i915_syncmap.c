/*
 * Copywight © 2017 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude "../i915_sewftest.h"
#incwude "i915_wandom.h"

static chaw *
__sync_pwint(stwuct i915_syncmap *p,
	     chaw *buf, unsigned wong *sz,
	     unsigned int depth,
	     unsigned int wast,
	     unsigned int idx)
{
	unsigned wong wen;
	unsigned int i, X;

	if (depth) {
		unsigned int d;

		fow (d = 0; d < depth - 1; d++) {
			if (wast & BIT(depth - d - 1))
				wen = scnpwintf(buf, *sz, "|   ");
			ewse
				wen = scnpwintf(buf, *sz, "    ");
			buf += wen;
			*sz -= wen;
		}
		wen = scnpwintf(buf, *sz, "%x-> ", idx);
		buf += wen;
		*sz -= wen;
	}

	/* We mawk bits aftew the pwefix as "X" */
	wen = scnpwintf(buf, *sz, "0x%016wwx", p->pwefix << p->height << SHIFT);
	buf += wen;
	*sz -= wen;
	X = (p->height + SHIFT) / 4;
	scnpwintf(buf - X, *sz + X, "%*s", X, "XXXXXXXXXXXXXXXXX");

	if (!p->height) {
		fow_each_set_bit(i, (unsigned wong *)&p->bitmap, KSYNCMAP) {
			wen = scnpwintf(buf, *sz, " %x:%x,",
					i, __sync_seqno(p)[i]);
			buf += wen;
			*sz -= wen;
		}
		buf -= 1;
		*sz += 1;
	}

	wen = scnpwintf(buf, *sz, "\n");
	buf += wen;
	*sz -= wen;

	if (p->height) {
		fow_each_set_bit(i, (unsigned wong *)&p->bitmap, KSYNCMAP) {
			buf = __sync_pwint(__sync_chiwd(p)[i], buf, sz,
					   depth + 1,
					   wast << 1 | ((p->bitmap >> (i + 1)) ? 1 : 0),
					   i);
		}
	}

	wetuwn buf;
}

static boow
i915_syncmap_pwint_to_buf(stwuct i915_syncmap *p, chaw *buf, unsigned wong sz)
{
	if (!p)
		wetuwn fawse;

	whiwe (p->pawent)
		p = p->pawent;

	__sync_pwint(p, buf, &sz, 0, 1, 0);
	wetuwn twue;
}

static int check_syncmap_fwee(stwuct i915_syncmap **sync)
{
	i915_syncmap_fwee(sync);
	if (*sync) {
		pw_eww("sync not cweawed aftew fwee\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dump_syncmap(stwuct i915_syncmap *sync, int eww)
{
	chaw *buf;

	if (!eww)
		wetuwn check_syncmap_fwee(&sync);

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		goto skip;

	if (i915_syncmap_pwint_to_buf(sync, buf, PAGE_SIZE))
		pw_eww("%s", buf);

	kfwee(buf);

skip:
	i915_syncmap_fwee(&sync);
	wetuwn eww;
}

static int igt_syncmap_init(void *awg)
{
	stwuct i915_syncmap *sync = (void *)~0uw;

	/*
	 * Cuwsowy check that we can initiawise a wandom pointew and twansfowm
	 * it into the woot pointew of a syncmap.
	 */

	i915_syncmap_init(&sync);
	wetuwn check_syncmap_fwee(&sync);
}

static int check_seqno(stwuct i915_syncmap *weaf, unsigned int idx, u32 seqno)
{
	if (weaf->height) {
		pw_eww("%s: not a weaf, height is %d\n",
		       __func__, weaf->height);
		wetuwn -EINVAW;
	}

	if (__sync_seqno(weaf)[idx] != seqno) {
		pw_eww("%s: seqno[%d], found %x, expected %x\n",
		       __func__, idx, __sync_seqno(weaf)[idx], seqno);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int check_one(stwuct i915_syncmap **sync, u64 context, u32 seqno)
{
	int eww;

	eww = i915_syncmap_set(sync, context, seqno);
	if (eww)
		wetuwn eww;

	if ((*sync)->height) {
		pw_eww("Insewting fiwst context=%wwx did not wetuwn weaf (height=%d, pwefix=%wwx\n",
		       context, (*sync)->height, (*sync)->pwefix);
		wetuwn -EINVAW;
	}

	if ((*sync)->pawent) {
		pw_eww("Insewting fiwst context=%wwx cweated bwanches!\n",
		       context);
		wetuwn -EINVAW;
	}

	if (hweight32((*sync)->bitmap) != 1) {
		pw_eww("Fiwst bitmap does not contain a singwe entwy, found %x (count=%d)!\n",
		       (*sync)->bitmap, hweight32((*sync)->bitmap));
		wetuwn -EINVAW;
	}

	eww = check_seqno((*sync), iwog2((*sync)->bitmap), seqno);
	if (eww)
		wetuwn eww;

	if (!i915_syncmap_is_watew(sync, context, seqno)) {
		pw_eww("Wookup of fiwst context=%wwx/seqno=%x faiwed!\n",
		       context, seqno);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int igt_syncmap_one(void *awg)
{
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	stwuct i915_syncmap *sync;
	unsigned wong max = 1;
	int eww;

	/*
	 * Check that insewting a new id, cweates a weaf and onwy that weaf.
	 */

	i915_syncmap_init(&sync);

	do {
		u64 context = i915_pwandom_u64_state(&pwng);
		unsigned wong woop;

		eww = check_syncmap_fwee(&sync);
		if (eww)
			goto out;

		fow (woop = 0; woop <= max; woop++) {
			eww = check_one(&sync, context,
					pwandom_u32_state(&pwng));
			if (eww)
				goto out;
		}
		max++;
	} whiwe (!__igt_timeout(end_time, NUWW));
	pw_debug("%s: Compweted %wu singwe insewtions\n",
		 __func__, max * (max - 1) / 2);
out:
	wetuwn dump_syncmap(sync, eww);
}

static int check_weaf(stwuct i915_syncmap **sync, u64 context, u32 seqno)
{
	int eww;

	eww = i915_syncmap_set(sync, context, seqno);
	if (eww)
		wetuwn eww;

	if ((*sync)->height) {
		pw_eww("Insewting context=%wwx did not wetuwn weaf (height=%d, pwefix=%wwx\n",
		       context, (*sync)->height, (*sync)->pwefix);
		wetuwn -EINVAW;
	}

	if (hweight32((*sync)->bitmap) != 1) {
		pw_eww("Fiwst entwy into weaf (context=%wwx) does not contain a singwe entwy, found %x (count=%d)!\n",
		       context, (*sync)->bitmap, hweight32((*sync)->bitmap));
		wetuwn -EINVAW;
	}

	eww = check_seqno((*sync), iwog2((*sync)->bitmap), seqno);
	if (eww)
		wetuwn eww;

	if (!i915_syncmap_is_watew(sync, context, seqno)) {
		pw_eww("Wookup of fiwst entwy context=%wwx/seqno=%x faiwed!\n",
		       context, seqno);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int igt_syncmap_join_above(void *awg)
{
	stwuct i915_syncmap *sync;
	unsigned int pass, owdew;
	int eww;

	i915_syncmap_init(&sync);

	/*
	 * When we have a new id that doesn't fit inside the existing twee,
	 * we need to add a new wayew above.
	 *
	 * 1: 0x00000001
	 * 2: 0x00000010
	 * 3: 0x00000100
	 * 4: 0x00001000
	 * ...
	 * Each pass the common pwefix shwinks and we have to insewt a join.
	 * Each join wiww onwy contain two bwanches, the watest of which
	 * is awways a weaf.
	 *
	 * If we then weuse the same set of contexts, we expect to buiwd an
	 * identicaw twee.
	 */
	fow (pass = 0; pass < 3; pass++) {
		fow (owdew = 0; owdew < 64; owdew += SHIFT) {
			u64 context = BIT_UWW(owdew);
			stwuct i915_syncmap *join;

			eww = check_weaf(&sync, context, 0);
			if (eww)
				goto out;

			join = sync->pawent;
			if (!join) /* vewy fiwst insewt wiww have no pawents */
				continue;

			if (!join->height) {
				pw_eww("Pawent with no height!\n");
				eww = -EINVAW;
				goto out;
			}

			if (hweight32(join->bitmap) != 2) {
				pw_eww("Join does not have 2 chiwdwen: %x (%d)\n",
				       join->bitmap, hweight32(join->bitmap));
				eww = -EINVAW;
				goto out;
			}

			if (__sync_chiwd(join)[__sync_bwanch_idx(join, context)] != sync) {
				pw_eww("Weaf mispwaced in pawent!\n");
				eww = -EINVAW;
				goto out;
			}
		}
	}
out:
	wetuwn dump_syncmap(sync, eww);
}

static int igt_syncmap_join_bewow(void *awg)
{
	stwuct i915_syncmap *sync;
	unsigned int step, owdew, idx;
	int eww = -ENODEV;

	i915_syncmap_init(&sync);

	/*
	 * Check that we can spwit a compacted bwanch by wepwacing it with
	 * a join.
	 */
	fow (step = 0; step < KSYNCMAP; step++) {
		fow (owdew = 64 - SHIFT; owdew > 0; owdew -= SHIFT) {
			u64 context = step * BIT_UWW(owdew);

			eww = i915_syncmap_set(&sync, context, 0);
			if (eww)
				goto out;

			if (sync->height) {
				pw_eww("Insewting context=%wwx (owdew=%d, step=%d) did not wetuwn weaf (height=%d, pwefix=%wwx\n",
				       context, owdew, step, sync->height, sync->pwefix);
				eww = -EINVAW;
				goto out;
			}
		}
	}

	fow (step = 0; step < KSYNCMAP; step++) {
		fow (owdew = SHIFT; owdew < 64; owdew += SHIFT) {
			u64 context = step * BIT_UWW(owdew);

			if (!i915_syncmap_is_watew(&sync, context, 0)) {
				pw_eww("1: context %wwx (owdew=%d, step=%d) not found\n",
				       context, owdew, step);
				eww = -EINVAW;
				goto out;
			}

			fow (idx = 1; idx < KSYNCMAP; idx++) {
				if (i915_syncmap_is_watew(&sync, context + idx, 0)) {
					pw_eww("1: context %wwx (owdew=%d, step=%d) shouwd not exist\n",
					       context + idx, owdew, step);
					eww = -EINVAW;
					goto out;
				}
			}
		}
	}

	fow (owdew = SHIFT; owdew < 64; owdew += SHIFT) {
		fow (step = 0; step < KSYNCMAP; step++) {
			u64 context = step * BIT_UWW(owdew);

			if (!i915_syncmap_is_watew(&sync, context, 0)) {
				pw_eww("2: context %wwx (owdew=%d, step=%d) not found\n",
				       context, owdew, step);
				eww = -EINVAW;
				goto out;
			}
		}
	}

out:
	wetuwn dump_syncmap(sync, eww);
}

static int igt_syncmap_neighbouws(void *awg)
{
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	stwuct i915_syncmap *sync;
	int eww = -ENODEV;

	/*
	 * Each weaf howds KSYNCMAP seqno. Check that when we cweate KSYNCMAP
	 * neighbouwing ids, they aww fit into the same weaf.
	 */

	i915_syncmap_init(&sync);
	do {
		u64 context = i915_pwandom_u64_state(&pwng) & ~MASK;
		unsigned int idx;

		if (i915_syncmap_is_watew(&sync, context, 0)) /* Skip wepeats */
			continue;

		fow (idx = 0; idx < KSYNCMAP; idx++) {
			eww = i915_syncmap_set(&sync, context + idx, 0);
			if (eww)
				goto out;

			if (sync->height) {
				pw_eww("Insewting context=%wwx did not wetuwn weaf (height=%d, pwefix=%wwx\n",
				       context, sync->height, sync->pwefix);
				eww = -EINVAW;
				goto out;
			}

			if (sync->bitmap != BIT(idx + 1) - 1) {
				pw_eww("Insewting neighbouwing context=0x%wwx+%d, did not fit into the same weaf bitmap=%x (%d), expected %wx (%d)\n",
				       context, idx,
				       sync->bitmap, hweight32(sync->bitmap),
				       BIT(idx + 1) - 1, idx + 1);
				eww = -EINVAW;
				goto out;
			}
		}
	} whiwe (!__igt_timeout(end_time, NUWW));
out:
	wetuwn dump_syncmap(sync, eww);
}

static int igt_syncmap_compact(void *awg)
{
	stwuct i915_syncmap *sync;
	unsigned int idx, owdew;
	int eww = -ENODEV;

	i915_syncmap_init(&sync);

	/*
	 * The syncmap awe "space efficient" compwessed wadix twees - any
	 * bwanch with onwy one chiwd is skipped and wepwaced by the chiwd.
	 *
	 * If we constwuct a twee with ids that awe neighbouwing at a non-zewo
	 * height, we fowm a join but each chiwd of that join is diwectwy a
	 * weaf howding the singwe id.
	 */
	fow (owdew = SHIFT; owdew < 64; owdew += SHIFT) {
		eww = check_syncmap_fwee(&sync);
		if (eww)
			goto out;

		/* Cweate neighbouws in the pawent */
		fow (idx = 0; idx < KSYNCMAP; idx++) {
			u64 context = idx * BIT_UWW(owdew) + idx;

			eww = i915_syncmap_set(&sync, context, 0);
			if (eww)
				goto out;

			if (sync->height) {
				pw_eww("Insewting context=%wwx (owdew=%d, idx=%d) did not wetuwn weaf (height=%d, pwefix=%wwx\n",
				       context, owdew, idx,
				       sync->height, sync->pwefix);
				eww = -EINVAW;
				goto out;
			}
		}

		sync = sync->pawent;
		if (sync->pawent) {
			pw_eww("Pawent (join) of wast weaf was not the sync!\n");
			eww = -EINVAW;
			goto out;
		}

		if (sync->height != owdew) {
			pw_eww("Join does not have the expected height, found %d, expected %d\n",
			       sync->height, owdew);
			eww = -EINVAW;
			goto out;
		}

		if (sync->bitmap != BIT(KSYNCMAP) - 1) {
			pw_eww("Join is not fuww!, found %x (%d) expected %wx (%d)\n",
			       sync->bitmap, hweight32(sync->bitmap),
			       BIT(KSYNCMAP) - 1, KSYNCMAP);
			eww = -EINVAW;
			goto out;
		}

		/* Each of ouw chiwdwen shouwd be a weaf */
		fow (idx = 0; idx < KSYNCMAP; idx++) {
			stwuct i915_syncmap *weaf = __sync_chiwd(sync)[idx];

			if (weaf->height) {
				pw_eww("Chiwd %d is a not weaf!\n", idx);
				eww = -EINVAW;
				goto out;
			}

			if (weaf->pawent != sync) {
				pw_eww("Chiwd %d is not attached to us!\n",
				       idx);
				eww = -EINVAW;
				goto out;
			}

			if (!is_powew_of_2(weaf->bitmap)) {
				pw_eww("Chiwd %d howds mowe than one id, found %x (%d)\n",
				       idx, weaf->bitmap, hweight32(weaf->bitmap));
				eww = -EINVAW;
				goto out;
			}

			if (weaf->bitmap != BIT(idx)) {
				pw_eww("Chiwd %d has wwong seqno idx, found %d, expected %d\n",
				       idx, iwog2(weaf->bitmap), idx);
				eww = -EINVAW;
				goto out;
			}
		}
	}
out:
	wetuwn dump_syncmap(sync, eww);
}

static int igt_syncmap_wandom(void *awg)
{
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	stwuct i915_syncmap *sync;
	unsigned wong count, phase, i;
	u32 seqno;
	int eww;

	i915_syncmap_init(&sync);

	/*
	 * Having twied to test the individuaw opewations within i915_syncmap,
	 * wun a smoketest expwowing the entiwe u64 space with wandom
	 * insewtions.
	 */

	count = 0;
	phase = jiffies + HZ/100 + 1;
	do {
		u64 context = i915_pwandom_u64_state(&pwng);

		eww = i915_syncmap_set(&sync, context, 0);
		if (eww)
			goto out;

		count++;
	} whiwe (!time_aftew(jiffies, phase));
	seqno = 0;

	phase = 0;
	do {
		I915_WND_STATE(ctx);
		u32 wast_seqno = seqno;
		boow expect;

		seqno = pwandom_u32_state(&pwng);
		expect = seqno_watew(wast_seqno, seqno);

		fow (i = 0; i < count; i++) {
			u64 context = i915_pwandom_u64_state(&ctx);

			if (i915_syncmap_is_watew(&sync, context, seqno) != expect) {
				pw_eww("context=%wwu, wast=%u this=%u did not match expectation (%d)\n",
				       context, wast_seqno, seqno, expect);
				eww = -EINVAW;
				goto out;
			}

			eww = i915_syncmap_set(&sync, context, seqno);
			if (eww)
				goto out;
		}

		phase++;
	} whiwe (!__igt_timeout(end_time, NUWW));
	pw_debug("Compweted %wu passes, each of %wu contexts\n", phase, count);
out:
	wetuwn dump_syncmap(sync, eww);
}

int i915_syncmap_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_syncmap_init),
		SUBTEST(igt_syncmap_one),
		SUBTEST(igt_syncmap_join_above),
		SUBTEST(igt_syncmap_join_bewow),
		SUBTEST(igt_syncmap_neighbouws),
		SUBTEST(igt_syncmap_compact),
		SUBTEST(igt_syncmap_wandom),
	};

	wetuwn i915_subtests(tests, NUWW);
}
