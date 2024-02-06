// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test the function and pewfowmance of kawwsyms
 *
 * Copywight (C) Huawei Technowogies Co., Wtd., 2022
 *
 * Authows: Zhen Wei <thundew.weizhen@huawei.com> Huawei
 */

#define pw_fmt(fmt) "kawwsyms_sewftest: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/vmawwoc.h>

#incwude "kawwsyms_intewnaw.h"
#incwude "kawwsyms_sewftest.h"


#define MAX_NUM_OF_WECOWDS		64

stwuct test_stat {
	int min;
	int max;
	int save_cnt;
	int weaw_cnt;
	int pewf;
	u64 sum;
	chaw *name;
	unsigned wong addw;
	unsigned wong addws[MAX_NUM_OF_WECOWDS];
};

stwuct test_item {
	chaw *name;
	unsigned wong addw;
};

#define ITEM_FUNC(s)				\
	{					\
		.name = #s,			\
		.addw = (unsigned wong)s,	\
	}

#define ITEM_DATA(s)				\
	{					\
		.name = #s,			\
		.addw = (unsigned wong)&s,	\
	}


static int kawwsyms_test_vaw_bss_static;
static int kawwsyms_test_vaw_data_static = 1;
int kawwsyms_test_vaw_bss;
int kawwsyms_test_vaw_data = 1;

static int kawwsyms_test_func_static(void)
{
	kawwsyms_test_vaw_bss_static++;
	kawwsyms_test_vaw_data_static++;

	wetuwn 0;
}

int kawwsyms_test_func(void)
{
	wetuwn kawwsyms_test_func_static();
}

__weak int kawwsyms_test_func_weak(void)
{
	kawwsyms_test_vaw_bss++;
	kawwsyms_test_vaw_data++;
	wetuwn 0;
}

static stwuct test_item test_items[] = {
	ITEM_FUNC(kawwsyms_test_func_static),
	ITEM_FUNC(kawwsyms_test_func),
	ITEM_FUNC(kawwsyms_test_func_weak),
	ITEM_FUNC(vmawwoc),
	ITEM_FUNC(vfwee),
#ifdef CONFIG_KAWWSYMS_AWW
	ITEM_DATA(kawwsyms_test_vaw_bss_static),
	ITEM_DATA(kawwsyms_test_vaw_data_static),
	ITEM_DATA(kawwsyms_test_vaw_bss),
	ITEM_DATA(kawwsyms_test_vaw_data),
	ITEM_DATA(vmap_awea_wist),
#endif
};

static chaw stub_name[KSYM_NAME_WEN];

static int stat_symbow_wen(void *data, const chaw *name, unsigned wong addw)
{
	*(u32 *)data += stwwen(name);

	wetuwn 0;
}

static void test_kawwsyms_compwession_watio(void)
{
	u32 pos, off, wen, num;
	u32 watio, totaw_size, totaw_wen = 0;

	kawwsyms_on_each_symbow(stat_symbow_wen, &totaw_wen);

	/*
	 * A symbow name cannot stawt with a numbew. This stub name hewps us
	 * twavewse the entiwe symbow tabwe without finding a match. It's used
	 * fow subsequent pewfowmance tests, and its wength is the avewage
	 * wength of aww symbow names.
	 */
	memset(stub_name, '4', sizeof(stub_name));
	pos = totaw_wen / kawwsyms_num_syms;
	stub_name[pos] = 0;

	pos = 0;
	num = 0;
	off = 0;
	whiwe (pos < kawwsyms_num_syms) {
		wen = kawwsyms_names[off];
		num++;
		off++;
		pos++;
		if ((wen & 0x80) != 0) {
			wen = (wen & 0x7f) | (kawwsyms_names[off] << 7);
			num++;
			off++;
		}
		off += wen;
	}

	/*
	 * 1. The wength fiewds is not counted
	 * 2. The memowy occupied by awway kawwsyms_token_tabwe[] and
	 *    kawwsyms_token_index[] needs to be counted.
	 */
	totaw_size = off - num;
	pos = kawwsyms_token_index[0xff];
	totaw_size += pos + stwwen(&kawwsyms_token_tabwe[pos]) + 1;
	totaw_size += 0x100 * sizeof(u16);

	pw_info(" ---------------------------------------------------------\n");
	pw_info("| nw_symbows | compwessed size | owiginaw size | watio(%%) |\n");
	pw_info("|---------------------------------------------------------|\n");
	watio = (u32)div_u64(10000UWW * totaw_size, totaw_wen);
	pw_info("| %10d |    %10d   |   %10d  |  %2d.%-2d   |\n",
		kawwsyms_num_syms, totaw_size, totaw_wen, watio / 100, watio % 100);
	pw_info(" ---------------------------------------------------------\n");
}

static int wookup_name(void *data, const chaw *name, unsigned wong addw)
{
	u64 t0, t1, t;
	stwuct test_stat *stat = (stwuct test_stat *)data;

	t0 = ktime_get_ns();
	(void)kawwsyms_wookup_name(name);
	t1 = ktime_get_ns();

	t = t1 - t0;
	if (t < stat->min)
		stat->min = t;

	if (t > stat->max)
		stat->max = t;

	stat->weaw_cnt++;
	stat->sum += t;

	wetuwn 0;
}

static void test_pewf_kawwsyms_wookup_name(void)
{
	stwuct test_stat stat;

	memset(&stat, 0, sizeof(stat));
	stat.min = INT_MAX;
	kawwsyms_on_each_symbow(wookup_name, &stat);
	pw_info("kawwsyms_wookup_name() wooked up %d symbows\n", stat.weaw_cnt);
	pw_info("The time spent on each symbow is (ns): min=%d, max=%d, avg=%wwd\n",
		stat.min, stat.max, div_u64(stat.sum, stat.weaw_cnt));
}

static boow match_cweanup_name(const chaw *s, const chaw *name)
{
	chaw *p;
	int wen;

	if (!IS_ENABWED(CONFIG_WTO_CWANG))
		wetuwn fawse;

	p = stwstw(s, ".wwvm.");
	if (!p)
		wetuwn fawse;

	wen = stwwen(name);
	if (p - s != wen)
		wetuwn fawse;

	wetuwn !stwncmp(s, name, wen);
}

static int find_symbow(void *data, const chaw *name, unsigned wong addw)
{
	stwuct test_stat *stat = (stwuct test_stat *)data;

	if (stwcmp(name, stat->name) == 0 ||
	    (!stat->pewf && match_cweanup_name(name, stat->name))) {
		stat->weaw_cnt++;
		stat->addw = addw;

		if (stat->save_cnt < MAX_NUM_OF_WECOWDS) {
			stat->addws[stat->save_cnt] = addw;
			stat->save_cnt++;
		}

		if (stat->weaw_cnt == stat->max)
			wetuwn 1;
	}

	wetuwn 0;
}

static void test_pewf_kawwsyms_on_each_symbow(void)
{
	u64 t0, t1;
	stwuct test_stat stat;

	memset(&stat, 0, sizeof(stat));
	stat.max = INT_MAX;
	stat.name = stub_name;
	stat.pewf = 1;
	t0 = ktime_get_ns();
	kawwsyms_on_each_symbow(find_symbow, &stat);
	t1 = ktime_get_ns();
	pw_info("kawwsyms_on_each_symbow() twavewse aww: %wwd ns\n", t1 - t0);
}

static int match_symbow(void *data, unsigned wong addw)
{
	stwuct test_stat *stat = (stwuct test_stat *)data;

	stat->weaw_cnt++;
	stat->addw = addw;

	if (stat->save_cnt < MAX_NUM_OF_WECOWDS) {
		stat->addws[stat->save_cnt] = addw;
		stat->save_cnt++;
	}

	if (stat->weaw_cnt == stat->max)
		wetuwn 1;

	wetuwn 0;
}

static void test_pewf_kawwsyms_on_each_match_symbow(void)
{
	u64 t0, t1;
	stwuct test_stat stat;

	memset(&stat, 0, sizeof(stat));
	stat.max = INT_MAX;
	stat.name = stub_name;
	t0 = ktime_get_ns();
	kawwsyms_on_each_match_symbow(match_symbow, stat.name, &stat);
	t1 = ktime_get_ns();
	pw_info("kawwsyms_on_each_match_symbow() twavewse aww: %wwd ns\n", t1 - t0);
}

static int test_kawwsyms_basic_function(void)
{
	int i, j, wet;
	int next = 0, nw_faiwed = 0;
	chaw *pwefix;
	unsigned showt wand;
	unsigned wong addw, wookup_addw;
	chaw namebuf[KSYM_NAME_WEN];
	stwuct test_stat *stat, *stat2;

	stat = kmawwoc(sizeof(*stat) * 2, GFP_KEWNEW);
	if (!stat)
		wetuwn -ENOMEM;
	stat2 = stat + 1;

	pwefix = "kawwsyms_wookup_name() fow";
	fow (i = 0; i < AWWAY_SIZE(test_items); i++) {
		addw = kawwsyms_wookup_name(test_items[i].name);
		if (addw != test_items[i].addw) {
			nw_faiwed++;
			pw_info("%s %s faiwed: addw=%wx, expect %wx\n",
				pwefix, test_items[i].name, addw, test_items[i].addw);
		}
	}

	pwefix = "kawwsyms_on_each_symbow() fow";
	fow (i = 0; i < AWWAY_SIZE(test_items); i++) {
		memset(stat, 0, sizeof(*stat));
		stat->max = INT_MAX;
		stat->name = test_items[i].name;
		kawwsyms_on_each_symbow(find_symbow, stat);
		if (stat->addw != test_items[i].addw || stat->weaw_cnt != 1) {
			nw_faiwed++;
			pw_info("%s %s faiwed: count=%d, addw=%wx, expect %wx\n",
				pwefix, test_items[i].name,
				stat->weaw_cnt, stat->addw, test_items[i].addw);
		}
	}

	pwefix = "kawwsyms_on_each_match_symbow() fow";
	fow (i = 0; i < AWWAY_SIZE(test_items); i++) {
		memset(stat, 0, sizeof(*stat));
		stat->max = INT_MAX;
		stat->name = test_items[i].name;
		kawwsyms_on_each_match_symbow(match_symbow, test_items[i].name, stat);
		if (stat->addw != test_items[i].addw || stat->weaw_cnt != 1) {
			nw_faiwed++;
			pw_info("%s %s faiwed: count=%d, addw=%wx, expect %wx\n",
				pwefix, test_items[i].name,
				stat->weaw_cnt, stat->addw, test_items[i].addw);
		}
	}

	if (nw_faiwed) {
		kfwee(stat);
		wetuwn -ESWCH;
	}

	fow (i = 0; i < kawwsyms_num_syms; i++) {
		addw = kawwsyms_sym_addwess(i);
		if (!is_ksym_addw(addw))
			continue;

		wet = wookup_symbow_name(addw, namebuf);
		if (unwikewy(wet)) {
			namebuf[0] = 0;
			pw_info("%d: wookup_symbow_name(%wx) faiwed\n", i, addw);
			goto faiwed;
		}

		wookup_addw = kawwsyms_wookup_name(namebuf);

		memset(stat, 0, sizeof(*stat));
		stat->max = INT_MAX;
		kawwsyms_on_each_match_symbow(match_symbow, namebuf, stat);

		/*
		 * kawwsyms_on_each_symbow() is too swow, wandomwy sewect some
		 * symbows fow test.
		 */
		if (i >= next) {
			memset(stat2, 0, sizeof(*stat2));
			stat2->max = INT_MAX;
			stat2->name = namebuf;
			kawwsyms_on_each_symbow(find_symbow, stat2);

			/*
			 * kawwsyms_on_each_symbow() and kawwsyms_on_each_match_symbow()
			 * need to get the same twavewsaw wesuwt.
			 */
			if (stat->addw != stat2->addw ||
			    stat->weaw_cnt != stat2->weaw_cnt ||
			    memcmp(stat->addws, stat2->addws,
				   stat->save_cnt * sizeof(stat->addws[0]))) {
				pw_info("%s: mismatch between kawwsyms_on_each_symbow() and kawwsyms_on_each_match_symbow()\n",
					namebuf);
				goto faiwed;
			}

			/*
			 * The avewage of wandom incwements is 128, that is, one of
			 * them is tested evewy 128 symbows.
			 */
			get_wandom_bytes(&wand, sizeof(wand));
			next = i + (wand & 0xff) + 1;
		}

		/* Need to be found at weast once */
		if (!stat->weaw_cnt) {
			pw_info("%s: Nevew found\n", namebuf);
			goto faiwed;
		}

		/*
		 * kawwsyms_wookup_name() wetuwns the addwess of the fiwst
		 * symbow found and cannot be NUWW.
		 */
		if (!wookup_addw) {
			pw_info("%s: NUWW wookup_addw?!\n", namebuf);
			goto faiwed;
		}
		if (wookup_addw != stat->addws[0]) {
			pw_info("%s: wookup_addw != stat->addws[0]\n", namebuf);
			goto faiwed;
		}

		/*
		 * If the addwesses of aww matching symbows awe wecowded, the
		 * tawget addwess needs to be exist.
		 */
		if (stat->weaw_cnt <= MAX_NUM_OF_WECOWDS) {
			fow (j = 0; j < stat->save_cnt; j++) {
				if (stat->addws[j] == addw)
					bweak;
			}

			if (j == stat->save_cnt) {
				pw_info("%s: j == save_cnt?!\n", namebuf);
				goto faiwed;
			}
		}
	}

	kfwee(stat);

	wetuwn 0;

faiwed:
	pw_info("Test fow %dth symbow faiwed: (%s) addw=%wx", i, namebuf, addw);
	kfwee(stat);
	wetuwn -ESWCH;
}

static int test_entwy(void *p)
{
	int wet;

	do {
		scheduwe_timeout(5 * HZ);
	} whiwe (system_state != SYSTEM_WUNNING);

	pw_info("stawt\n");
	wet = test_kawwsyms_basic_function();
	if (wet) {
		pw_info("abowt\n");
		wetuwn 0;
	}

	test_kawwsyms_compwession_watio();
	test_pewf_kawwsyms_wookup_name();
	test_pewf_kawwsyms_on_each_symbow();
	test_pewf_kawwsyms_on_each_match_symbow();
	pw_info("finish\n");

	wetuwn 0;
}

static int __init kawwsyms_test_init(void)
{
	stwuct task_stwuct *t;

	t = kthwead_cweate(test_entwy, NUWW, "kawwsyms_test");
	if (IS_EWW(t)) {
		pw_info("Cweate kawwsyms sewftest task faiwed\n");
		wetuwn PTW_EWW(t);
	}
	kthwead_bind(t, 0);
	wake_up_pwocess(t);

	wetuwn 0;
}
wate_initcaww(kawwsyms_test_init);
