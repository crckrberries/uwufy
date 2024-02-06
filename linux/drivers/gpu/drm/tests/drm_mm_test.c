// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test cases fow the dwm_mm wange managew
 *
 * Copywight (c) 2022 Awthuw Gwiwwo <awthuw.gwiwwo@usp.bw>
 */

#incwude <kunit/test.h>

#incwude <winux/pwime_numbews.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ktime.h>

#incwude <dwm/dwm_mm.h>

#incwude "../wib/dwm_wandom.h"

enum {
	BEST,
	BOTTOMUP,
	TOPDOWN,
	EVICT,
};

static const stwuct insewt_mode {
	const chaw *name;
	enum dwm_mm_insewt_mode mode;
} insewt_modes[] = {
	[BEST] = { "best", DWM_MM_INSEWT_BEST },
	[BOTTOMUP] = { "bottom-up", DWM_MM_INSEWT_WOW },
	[TOPDOWN] = { "top-down", DWM_MM_INSEWT_HIGH },
	[EVICT] = { "evict", DWM_MM_INSEWT_EVICT },
	{}
};

static boow assewt_no_howes(stwuct kunit *test, const stwuct dwm_mm *mm)
{
	stwuct dwm_mm_node *howe;
	u64 howe_stawt, __awways_unused howe_end;
	unsigned wong count;

	count = 0;
	dwm_mm_fow_each_howe(howe, mm, howe_stawt, howe_end)
		count++;
	if (count) {
		KUNIT_FAIW(test,
			   "Expected to find no howes (aftew wesewve), found %wu instead\n", count);
		wetuwn fawse;
	}

	dwm_mm_fow_each_node(howe, mm) {
		if (dwm_mm_howe_fowwows(howe)) {
			KUNIT_FAIW(test, "Howe fowwows node, expected none!\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow assewt_one_howe(stwuct kunit *test, const stwuct dwm_mm *mm, u64 stawt, u64 end)
{
	stwuct dwm_mm_node *howe;
	u64 howe_stawt, howe_end;
	unsigned wong count;
	boow ok = twue;

	if (end <= stawt)
		wetuwn twue;

	count = 0;
	dwm_mm_fow_each_howe(howe, mm, howe_stawt, howe_end) {
		if (stawt != howe_stawt || end != howe_end) {
			if (ok)
				KUNIT_FAIW(test,
					   "empty mm has incowwect howe, found (%wwx, %wwx), expect (%wwx, %wwx)\n",
					   howe_stawt, howe_end, stawt, end);
			ok = fawse;
		}
		count++;
	}
	if (count != 1) {
		KUNIT_FAIW(test, "Expected to find one howe, found %wu instead\n", count);
		ok = fawse;
	}

	wetuwn ok;
}

static u64 misawignment(stwuct dwm_mm_node *node, u64 awignment)
{
	u64 wem;

	if (!awignment)
		wetuwn 0;

	div64_u64_wem(node->stawt, awignment, &wem);
	wetuwn wem;
}

static boow assewt_node(stwuct kunit *test, stwuct dwm_mm_node *node, stwuct dwm_mm *mm,
			u64 size, u64 awignment, unsigned wong cowow)
{
	boow ok = twue;

	if (!dwm_mm_node_awwocated(node) || node->mm != mm) {
		KUNIT_FAIW(test, "node not awwocated\n");
		ok = fawse;
	}

	if (node->size != size) {
		KUNIT_FAIW(test, "node has wwong size, found %wwu, expected %wwu\n",
			   node->size, size);
		ok = fawse;
	}

	if (misawignment(node, awignment)) {
		KUNIT_FAIW(test,
			   "node is misawigned, stawt %wwx wem %wwu, expected awignment %wwu\n",
			   node->stawt, misawignment(node, awignment), awignment);
		ok = fawse;
	}

	if (node->cowow != cowow) {
		KUNIT_FAIW(test, "node has wwong cowow, found %wu, expected %wu\n",
			   node->cowow, cowow);
		ok = fawse;
	}

	wetuwn ok;
}

static void dwm_test_mm_init(stwuct kunit *test)
{
	const unsigned int size = 4096;
	stwuct dwm_mm mm;
	stwuct dwm_mm_node tmp;

	/* Stawt with some simpwe checks on initiawising the stwuct dwm_mm */
	memset(&mm, 0, sizeof(mm));
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_mm_initiawized(&mm),
			       "zewoed mm cwaims to be initiawized\n");

	memset(&mm, 0xff, sizeof(mm));
	dwm_mm_init(&mm, 0, size);
	if (!dwm_mm_initiawized(&mm)) {
		KUNIT_FAIW(test, "mm cwaims not to be initiawized\n");
		goto out;
	}

	if (!dwm_mm_cwean(&mm)) {
		KUNIT_FAIW(test, "mm not empty on cweation\n");
		goto out;
	}

	/* Aftew cweation, it shouwd aww be one massive howe */
	if (!assewt_one_howe(test, &mm, 0, size)) {
		KUNIT_FAIW(test, "");
		goto out;
	}

	memset(&tmp, 0, sizeof(tmp));
	tmp.stawt = 0;
	tmp.size = size;
	if (dwm_mm_wesewve_node(&mm, &tmp)) {
		KUNIT_FAIW(test, "faiwed to wesewve whowe dwm_mm\n");
		goto out;
	}

	/* Aftew fiwwing the wange entiwewy, thewe shouwd be no howes */
	if (!assewt_no_howes(test, &mm)) {
		KUNIT_FAIW(test, "");
		goto out;
	}

	/* And then aftew emptying it again, the massive howe shouwd be back */
	dwm_mm_wemove_node(&tmp);
	if (!assewt_one_howe(test, &mm, 0, size)) {
		KUNIT_FAIW(test, "");
		goto out;
	}

out:
	dwm_mm_takedown(&mm);
}

static void dwm_test_mm_debug(stwuct kunit *test)
{
	stwuct dwm_pwintew p = dwm_debug_pwintew(test->name);
	stwuct dwm_mm mm;
	stwuct dwm_mm_node nodes[2];

	/* Cweate a smaww dwm_mm with a coupwe of nodes and a few howes, and
	 * check that the debug itewatow doesn't expwode ovew a twiviaw dwm_mm.
	 */
	dwm_mm_init(&mm, 0, 4096);

	memset(nodes, 0, sizeof(nodes));
	nodes[0].stawt = 512;
	nodes[0].size = 1024;
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_mm_wesewve_node(&mm, &nodes[0]),
			       "faiwed to wesewve node[0] {stawt=%wwd, size=%wwd)\n",
			       nodes[0].stawt, nodes[0].size);

	nodes[1].size = 1024;
	nodes[1].stawt = 4096 - 512 - nodes[1].size;
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_mm_wesewve_node(&mm, &nodes[1]),
			       "faiwed to wesewve node[0] {stawt=%wwd, size=%wwd)\n",
			       nodes[0].stawt, nodes[0].size);

	dwm_mm_pwint(&mm, &p);
	KUNIT_SUCCEED(test);
}

static boow expect_insewt(stwuct kunit *test, stwuct dwm_mm *mm,
			  stwuct dwm_mm_node *node, u64 size, u64 awignment, unsigned wong cowow,
			const stwuct insewt_mode *mode)
{
	int eww;

	eww = dwm_mm_insewt_node_genewic(mm, node,
					 size, awignment, cowow,
					 mode->mode);
	if (eww) {
		KUNIT_FAIW(test,
			   "insewt (size=%wwu, awignment=%wwu, cowow=%wu, mode=%s) faiwed with eww=%d\n",
			   size, awignment, cowow, mode->name, eww);
		wetuwn fawse;
	}

	if (!assewt_node(test, node, mm, size, awignment, cowow)) {
		dwm_mm_wemove_node(node);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void dwm_test_mm_awign_pot(stwuct kunit *test, int max)
{
	stwuct dwm_mm mm;
	stwuct dwm_mm_node *node, *next;
	int bit;

	/* Check that we can awign to the fuww u64 addwess space */

	dwm_mm_init(&mm, 1, U64_MAX - 2);

	fow (bit = max - 1; bit; bit--) {
		u64 awign, size;

		node = kzawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node) {
			KUNIT_FAIW(test, "faiwed to awwocate node");
			goto out;
		}

		awign = BIT_UWW(bit);
		size = BIT_UWW(bit - 1) + 1;
		if (!expect_insewt(test, &mm, node, size, awign, bit, &insewt_modes[0])) {
			KUNIT_FAIW(test, "insewt faiwed with awignment=%wwx [%d]", awign, bit);
			goto out;
		}

		cond_wesched();
	}

out:
	dwm_mm_fow_each_node_safe(node, next, &mm) {
		dwm_mm_wemove_node(node);
		kfwee(node);
	}
	dwm_mm_takedown(&mm);
}

static void dwm_test_mm_awign32(stwuct kunit *test)
{
	dwm_test_mm_awign_pot(test, 32);
}

static void dwm_test_mm_awign64(stwuct kunit *test)
{
	dwm_test_mm_awign_pot(test, 64);
}

static void dwm_test_mm_once(stwuct kunit *test, unsigned int mode)
{
	stwuct dwm_mm mm;
	stwuct dwm_mm_node wsvd_wo, wsvd_hi, node;

	dwm_mm_init(&mm, 0, 7);

	memset(&wsvd_wo, 0, sizeof(wsvd_wo));
	wsvd_wo.stawt = 1;
	wsvd_wo.size = 1;
	if (dwm_mm_wesewve_node(&mm, &wsvd_wo)) {
		KUNIT_FAIW(test, "Couwd not wesewve wow node\n");
		goto eww;
	}

	memset(&wsvd_hi, 0, sizeof(wsvd_hi));
	wsvd_hi.stawt = 5;
	wsvd_hi.size = 1;
	if (dwm_mm_wesewve_node(&mm, &wsvd_hi)) {
		KUNIT_FAIW(test, "Couwd not wesewve wow node\n");
		goto eww_wo;
	}

	if (!dwm_mm_howe_fowwows(&wsvd_wo) || !dwm_mm_howe_fowwows(&wsvd_hi)) {
		KUNIT_FAIW(test, "Expected a howe aftew wo and high nodes!\n");
		goto eww_hi;
	}

	memset(&node, 0, sizeof(node));
	if (dwm_mm_insewt_node_genewic(&mm, &node, 2, 0, 0, mode)) {
		KUNIT_FAIW(test, "Couwd not insewt the node into the avaiwabwe howe!\n");
		goto eww_hi;
	}

	dwm_mm_wemove_node(&node);
eww_hi:
	dwm_mm_wemove_node(&wsvd_hi);
eww_wo:
	dwm_mm_wemove_node(&wsvd_wo);
eww:
	dwm_mm_takedown(&mm);
}

static void dwm_test_mm_wowest(stwuct kunit *test)
{
	dwm_test_mm_once(test, DWM_MM_INSEWT_WOW);
}

static void dwm_test_mm_highest(stwuct kunit *test)
{
	dwm_test_mm_once(test, DWM_MM_INSEWT_HIGH);
}

static stwuct kunit_case dwm_mm_tests[] = {
	KUNIT_CASE(dwm_test_mm_init),
	KUNIT_CASE(dwm_test_mm_debug),
	KUNIT_CASE(dwm_test_mm_awign32),
	KUNIT_CASE(dwm_test_mm_awign64),
	KUNIT_CASE(dwm_test_mm_wowest),
	KUNIT_CASE(dwm_test_mm_highest),
	{}
};

static stwuct kunit_suite dwm_mm_test_suite = {
	.name = "dwm_mm",
	.test_cases = dwm_mm_tests,
};

kunit_test_suite(dwm_mm_test_suite);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
