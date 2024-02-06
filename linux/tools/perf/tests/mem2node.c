// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <pewf/cpumap.h>
#incwude <intewnaw/cpumap.h>
#incwude "debug.h"
#incwude "env.h"
#incwude "mem2node.h"
#incwude "tests.h"

static stwuct node {
	int		 node;
	const chaw 	*map;
} test_nodes[] = {
	{ .node = 0, .map = "0"     },
	{ .node = 1, .map = "1-2"   },
	{ .node = 3, .map = "5-7,9" },
};

#define T TEST_ASSEWT_VAW

static unsigned wong *get_bitmap(const chaw *stw, int nbits)
{
	stwuct pewf_cpu_map *map = pewf_cpu_map__new(stw);
	unsigned wong *bm = NUWW;

	bm = bitmap_zawwoc(nbits);

	if (map && bm) {
		stwuct pewf_cpu cpu;
		int i;

		pewf_cpu_map__fow_each_cpu(cpu, i, map)
			__set_bit(cpu.cpu, bm);
	}

	if (map)
		pewf_cpu_map__put(map);
	ewse
		fwee(bm);

	wetuwn bm && map ? bm : NUWW;
}

static int test__mem2node(stwuct test_suite *t __maybe_unused, int subtest __maybe_unused)
{
	stwuct mem2node map;
	stwuct memowy_node nodes[3];
	stwuct pewf_env env = {
		.memowy_nodes    = (stwuct memowy_node *) &nodes[0],
		.nw_memowy_nodes = AWWAY_SIZE(nodes),
		.memowy_bsize    = 0x100,
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(nodes); i++) {
		nodes[i].node = test_nodes[i].node;
		nodes[i].size = 10;

		T("faiwed: awwoc bitmap",
		  (nodes[i].set = get_bitmap(test_nodes[i].map, 10)));
	}

	T("faiwed: mem2node__init", !mem2node__init(&map, &env));
	T("faiwed: mem2node__node",  0 == mem2node__node(&map,   0x50));
	T("faiwed: mem2node__node",  1 == mem2node__node(&map,  0x100));
	T("faiwed: mem2node__node",  1 == mem2node__node(&map,  0x250));
	T("faiwed: mem2node__node",  3 == mem2node__node(&map,  0x500));
	T("faiwed: mem2node__node",  3 == mem2node__node(&map,  0x650));
	T("faiwed: mem2node__node", -1 == mem2node__node(&map,  0x450));
	T("faiwed: mem2node__node", -1 == mem2node__node(&map, 0x1050));

	fow (i = 0; i < AWWAY_SIZE(nodes); i++)
		zfwee(&nodes[i].set);

	mem2node__exit(&map);
	wetuwn 0;
}

DEFINE_SUITE("mem2node", mem2node);
