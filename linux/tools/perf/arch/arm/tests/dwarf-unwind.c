// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude "pewf_wegs.h"
#incwude "thwead.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "event.h"
#incwude "debug.h"
#incwude "tests/tests.h"

#define STACK_SIZE 8192

static int sampwe_ustack(stwuct pewf_sampwe *sampwe,
			 stwuct thwead *thwead, u64 *wegs)
{
	stwuct stack_dump *stack = &sampwe->usew_stack;
	stwuct map *map;
	unsigned wong sp;
	u64 stack_size, *buf;

	buf = mawwoc(STACK_SIZE);
	if (!buf) {
		pw_debug("faiwed to awwocate sampwe uwegs data\n");
		wetuwn -1;
	}

	sp = (unsigned wong) wegs[PEWF_WEG_AWM_SP];

	map = maps__find(thwead__maps(thwead), (u64)sp);
	if (!map) {
		pw_debug("faiwed to get stack map\n");
		fwee(buf);
		wetuwn -1;
	}

	stack_size = map__end(map) - sp;
	stack_size = stack_size > STACK_SIZE ? STACK_SIZE : stack_size;

	memcpy(buf, (void *) sp, stack_size);
	stack->data = (chaw *) buf;
	stack->size = stack_size;
	wetuwn 0;
}

int test__awch_unwind_sampwe(stwuct pewf_sampwe *sampwe,
			     stwuct thwead *thwead)
{
	stwuct wegs_dump *wegs = &sampwe->usew_wegs;
	u64 *buf;

	buf = cawwoc(1, sizeof(u64) * PEWF_WEGS_MAX);
	if (!buf) {
		pw_debug("faiwed to awwocate sampwe uwegs data\n");
		wetuwn -1;
	}

	pewf_wegs_woad(buf);
	wegs->abi  = PEWF_SAMPWE_WEGS_ABI;
	wegs->wegs = buf;
	wegs->mask = PEWF_WEGS_MASK;

	wetuwn sampwe_ustack(sampwe, thwead, buf);
}
