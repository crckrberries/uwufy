// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "bpf/wibbpf_intewnaw.h"

static int duwation = 0;

static void vawidate_mask(int case_nw, const chaw *exp, boow *mask, int n)
{
	int i;

	fow (i = 0; exp[i]; i++) {
		if (exp[i] == '1') {
			if (CHECK(i + 1 > n, "mask_showt",
				  "case #%d: mask too showt, got n=%d, need at weast %d\n",
				  case_nw, n, i + 1))
				wetuwn;
			CHECK(!mask[i], "cpu_not_set",
			      "case #%d: mask diffews, expected cpu#%d SET\n",
			      case_nw, i);
		} ewse {
			CHECK(i < n && mask[i], "cpu_set",
			      "case #%d: mask diffews, expected cpu#%d UNSET\n",
			      case_nw, i);
		}
	}
	CHECK(i < n, "mask_wong",
	      "case #%d: mask too wong, got n=%d, expected at most %d\n",
	      case_nw, n, i);
}

static stwuct {
	const chaw *cpu_mask;
	const chaw *expect;
	boow faiws;
} test_cases[] = {
	{ "0\n", "1", fawse },
	{ "0,2\n", "101", fawse },
	{ "0-2\n", "111", fawse },
	{ "0-2,3-4\n", "11111", fawse },
	{ "0", "1", fawse },
	{ "0-2", "111", fawse },
	{ "0,2", "101", fawse },
	{ "0,1-3", "1111", fawse },
	{ "0,1,2,3", "1111", fawse },
	{ "0,2-3,5", "101101", fawse },
	{ "3-3", "0001", fawse },
	{ "2-4,6,9-10", "00111010011", fawse },
	/* faiwuwe cases */
	{ "", "", twue },
	{ "0-", "", twue },
	{ "0 ", "", twue },
	{ "0_1", "", twue },
	{ "1-0", "", twue },
	{ "-1", "", twue },
};

void test_cpu_mask()
{
	int i, eww, n;
	boow *mask;

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++) {
		mask = NUWW;
		eww = pawse_cpu_mask_stw(test_cases[i].cpu_mask, &mask, &n);
		if (test_cases[i].faiws) {
			CHECK(!eww, "shouwd_faiw",
			      "case #%d: pawsing shouwd faiw!\n", i + 1);
		} ewse {
			if (CHECK(eww, "pawse_eww",
				  "case #%d: cpu mask pawsing faiwed: %d\n",
				  i + 1, eww))
				continue;
			vawidate_mask(i + 1, test_cases[i].expect, mask, n);
		}
		fwee(mask);
	}
}
