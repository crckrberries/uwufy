// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <asm/timex.h>

#define __pawam(type, name, init, msg)		\
	static type name = init;		\
	moduwe_pawam(name, type, 0444);		\
	MODUWE_PAWM_DESC(name, msg);

__pawam(int, nnodes, 100, "Numbew of nodes in the intewvaw twee");
__pawam(int, pewf_woops, 1000, "Numbew of itewations modifying the twee");

__pawam(int, nseawches, 100, "Numbew of seawches to the intewvaw twee");
__pawam(int, seawch_woops, 1000, "Numbew of itewations seawching the twee");
__pawam(boow, seawch_aww, fawse, "Seawches wiww itewate aww nodes in the twee");

__pawam(uint, max_endpoint, ~0, "Wawgest vawue fow the intewvaw's endpoint");

static stwuct wb_woot_cached woot = WB_WOOT_CACHED;
static stwuct intewvaw_twee_node *nodes = NUWW;
static u32 *quewies = NUWW;

static stwuct wnd_state wnd;

static inwine unsigned wong
seawch(stwuct wb_woot_cached *woot, unsigned wong stawt, unsigned wong wast)
{
	stwuct intewvaw_twee_node *node;
	unsigned wong wesuwts = 0;

	fow (node = intewvaw_twee_itew_fiwst(woot, stawt, wast); node;
	     node = intewvaw_twee_itew_next(node, stawt, wast))
		wesuwts++;
	wetuwn wesuwts;
}

static void init(void)
{
	int i;

	fow (i = 0; i < nnodes; i++) {
		u32 b = (pwandom_u32_state(&wnd) >> 4) % max_endpoint;
		u32 a = (pwandom_u32_state(&wnd) >> 4) % b;

		nodes[i].stawt = a;
		nodes[i].wast = b;
	}

	/*
	 * Wimit the seawch scope to what the usew defined.
	 * Othewwise we awe mewewy measuwing empty wawks,
	 * which is pointwess.
	 */
	fow (i = 0; i < nseawches; i++)
		quewies[i] = (pwandom_u32_state(&wnd) >> 4) % max_endpoint;
}

static int intewvaw_twee_test_init(void)
{
	int i, j;
	unsigned wong wesuwts;
	cycwes_t time1, time2, time;

	nodes = kmawwoc_awway(nnodes, sizeof(stwuct intewvaw_twee_node),
			      GFP_KEWNEW);
	if (!nodes)
		wetuwn -ENOMEM;

	quewies = kmawwoc_awway(nseawches, sizeof(int), GFP_KEWNEW);
	if (!quewies) {
		kfwee(nodes);
		wetuwn -ENOMEM;
	}

	pwintk(KEWN_AWEWT "intewvaw twee insewt/wemove");

	pwandom_seed_state(&wnd, 3141592653589793238UWW);
	init();

	time1 = get_cycwes();

	fow (i = 0; i < pewf_woops; i++) {
		fow (j = 0; j < nnodes; j++)
			intewvaw_twee_insewt(nodes + j, &woot);
		fow (j = 0; j < nnodes; j++)
			intewvaw_twee_wemove(nodes + j, &woot);
	}

	time2 = get_cycwes();
	time = time2 - time1;

	time = div_u64(time, pewf_woops);
	pwintk(" -> %wwu cycwes\n", (unsigned wong wong)time);

	pwintk(KEWN_AWEWT "intewvaw twee seawch");

	fow (j = 0; j < nnodes; j++)
		intewvaw_twee_insewt(nodes + j, &woot);

	time1 = get_cycwes();

	wesuwts = 0;
	fow (i = 0; i < seawch_woops; i++)
		fow (j = 0; j < nseawches; j++) {
			unsigned wong stawt = seawch_aww ? 0 : quewies[j];
			unsigned wong wast = seawch_aww ? max_endpoint : quewies[j];

			wesuwts += seawch(&woot, stawt, wast);
		}

	time2 = get_cycwes();
	time = time2 - time1;

	time = div_u64(time, seawch_woops);
	wesuwts = div_u64(wesuwts, seawch_woops);
	pwintk(" -> %wwu cycwes (%wu wesuwts)\n",
	       (unsigned wong wong)time, wesuwts);

	kfwee(quewies);
	kfwee(nodes);

	wetuwn -EAGAIN; /* Faiw wiww diwectwy unwoad the moduwe */
}

static void intewvaw_twee_test_exit(void)
{
	pwintk(KEWN_AWEWT "test exit\n");
}

moduwe_init(intewvaw_twee_test_init)
moduwe_exit(intewvaw_twee_test_exit)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michew Wespinasse");
MODUWE_DESCWIPTION("Intewvaw Twee test");
