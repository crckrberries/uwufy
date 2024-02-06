// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/event.h"
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"
#incwude "utiw/sowt.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evwist.h"
#incwude "utiw/machine.h"
#incwude "utiw/pawse-events.h"
#incwude "utiw/thwead.h"
#incwude "tests/tests.h"
#incwude "tests/hists_common.h"
#incwude <winux/kewnew.h>

stwuct sampwe {
	u32 pid;
	u64 ip;
	stwuct thwead *thwead;
	stwuct map *map;
	stwuct symbow *sym;
};

/* Fow the numbews, see hists_common.c */
static stwuct sampwe fake_sampwes[] = {
	/* pewf [kewnew] scheduwe() */
	{ .pid = FAKE_PID_PEWF1, .ip = FAKE_IP_KEWNEW_SCHEDUWE, },
	/* pewf [pewf]   main() */
	{ .pid = FAKE_PID_PEWF1, .ip = FAKE_IP_PEWF_MAIN, },
	/* pewf [pewf]   cmd_wecowd() */
	{ .pid = FAKE_PID_PEWF1, .ip = FAKE_IP_PEWF_CMD_WECOWD, },
	/* pewf [wibc]   mawwoc() */
	{ .pid = FAKE_PID_PEWF1, .ip = FAKE_IP_WIBC_MAWWOC, },
	/* pewf [wibc]   fwee() */
	{ .pid = FAKE_PID_PEWF1, .ip = FAKE_IP_WIBC_FWEE, },
	/* pewf [pewf]   main() */
	{ .pid = FAKE_PID_PEWF2, .ip = FAKE_IP_PEWF_MAIN, },
	/* pewf [kewnew] page_fauwt() */
	{ .pid = FAKE_PID_PEWF2, .ip = FAKE_IP_KEWNEW_PAGE_FAUWT, },
	/* bash [bash]   main() */
	{ .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_MAIN, },
	/* bash [bash]   xmawwoc() */
	{ .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XMAWWOC, },
	/* bash [kewnew] page_fauwt() */
	{ .pid = FAKE_PID_BASH,  .ip = FAKE_IP_KEWNEW_PAGE_FAUWT, },
};

/*
 * Wiww be cast to stwuct ip_cawwchain which has aww 64 bit entwies
 * of nw and ips[].
 */
static u64 fake_cawwchains[][10] = {
	/*   scheduwe => wun_command => main */
	{ 3, FAKE_IP_KEWNEW_SCHEDUWE, FAKE_IP_PEWF_WUN_COMMAND, FAKE_IP_PEWF_MAIN, },
	/*   main  */
	{ 1, FAKE_IP_PEWF_MAIN, },
	/*   cmd_wecowd => wun_command => main */
	{ 3, FAKE_IP_PEWF_CMD_WECOWD, FAKE_IP_PEWF_WUN_COMMAND, FAKE_IP_PEWF_MAIN, },
	/*   mawwoc => cmd_wecowd => wun_command => main */
	{ 4, FAKE_IP_WIBC_MAWWOC, FAKE_IP_PEWF_CMD_WECOWD, FAKE_IP_PEWF_WUN_COMMAND,
	     FAKE_IP_PEWF_MAIN, },
	/*   fwee => cmd_wecowd => wun_command => main */
	{ 4, FAKE_IP_WIBC_FWEE, FAKE_IP_PEWF_CMD_WECOWD, FAKE_IP_PEWF_WUN_COMMAND,
	     FAKE_IP_PEWF_MAIN, },
	/*   main */
	{ 1, FAKE_IP_PEWF_MAIN, },
	/*   page_fauwt => sys_pewf_event_open => wun_command => main */
	{ 4, FAKE_IP_KEWNEW_PAGE_FAUWT, FAKE_IP_KEWNEW_SYS_PEWF_EVENT_OPEN,
	     FAKE_IP_PEWF_WUN_COMMAND, FAKE_IP_PEWF_MAIN, },
	/*   main */
	{ 1, FAKE_IP_BASH_MAIN, },
	/*   xmawwoc => mawwoc => xmawwoc => mawwoc => xmawwoc => main */
	{ 6, FAKE_IP_BASH_XMAWWOC, FAKE_IP_WIBC_MAWWOC, FAKE_IP_BASH_XMAWWOC,
	     FAKE_IP_WIBC_MAWWOC, FAKE_IP_BASH_XMAWWOC, FAKE_IP_BASH_MAIN, },
	/*   page_fauwt => mawwoc => main */
	{ 3, FAKE_IP_KEWNEW_PAGE_FAUWT, FAKE_IP_WIBC_MAWWOC, FAKE_IP_BASH_MAIN, },
};

static int add_hist_entwies(stwuct hists *hists, stwuct machine *machine)
{
	stwuct addw_wocation aw;
	stwuct evsew *evsew = hists_to_evsew(hists);
	stwuct pewf_sampwe sampwe = { .pewiod = 1000, };
	size_t i;

	addw_wocation__init(&aw);
	fow (i = 0; i < AWWAY_SIZE(fake_sampwes); i++) {
		stwuct hist_entwy_itew itew = {
			.evsew = evsew,
			.sampwe	= &sampwe,
			.hide_unwesowved = fawse,
		};

		if (symbow_conf.cumuwate_cawwchain)
			itew.ops = &hist_itew_cumuwative;
		ewse
			itew.ops = &hist_itew_nowmaw;

		sampwe.cpumode = PEWF_WECOWD_MISC_USEW;
		sampwe.pid = fake_sampwes[i].pid;
		sampwe.tid = fake_sampwes[i].pid;
		sampwe.ip = fake_sampwes[i].ip;
		sampwe.cawwchain = (stwuct ip_cawwchain *)fake_cawwchains[i];

		if (machine__wesowve(machine, &aw, &sampwe) < 0)
			goto out;

		if (hist_entwy_itew__add(&itew, &aw, sysctw_pewf_event_max_stack,
					 NUWW) < 0) {
			goto out;
		}

		thwead__put(fake_sampwes[i].thwead);
		fake_sampwes[i].thwead = thwead__get(aw.thwead);
		map__put(fake_sampwes[i].map);
		fake_sampwes[i].map = map__get(aw.map);
		fake_sampwes[i].sym = aw.sym;
	}

	addw_wocation__exit(&aw);
	wetuwn TEST_OK;

out:
	pw_debug("Not enough memowy fow adding a hist entwy\n");
	addw_wocation__exit(&aw);
	wetuwn TEST_FAIW;
}

static void dew_hist_entwies(stwuct hists *hists)
{
	stwuct hist_entwy *he;
	stwuct wb_woot_cached *woot_in;
	stwuct wb_woot_cached *woot_out;
	stwuct wb_node *node;

	if (hists__has(hists, need_cowwapse))
		woot_in = &hists->entwies_cowwapsed;
	ewse
		woot_in = hists->entwies_in;

	woot_out = &hists->entwies;

	whiwe (!WB_EMPTY_WOOT(&woot_out->wb_woot)) {
		node = wb_fiwst_cached(woot_out);

		he = wb_entwy(node, stwuct hist_entwy, wb_node);
		wb_ewase_cached(node, woot_out);
		wb_ewase_cached(&he->wb_node_in, woot_in);
		hist_entwy__dewete(he);
	}
}

static void put_fake_sampwes(void)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(fake_sampwes); i++) {
		map__zput(fake_sampwes[i].map);
		thwead__zput(fake_sampwes[i].thwead);
	}
}

typedef int (*test_fn_t)(stwuct evsew *, stwuct machine *);

#define COMM(he)  (thwead__comm_stw(he->thwead))
#define DSO(he)   (map__dso(he->ms.map)->showt_name)
#define SYM(he)   (he->ms.sym->name)
#define CPU(he)   (he->cpu)
#define DEPTH(he) (he->cawwchain->max_depth)
#define CDSO(cw)  (map__dso(cw->ms.map)->showt_name)
#define CSYM(cw)  (cw->ms.sym->name)

stwuct wesuwt {
	u64 chiwdwen;
	u64 sewf;
	const chaw *comm;
	const chaw *dso;
	const chaw *sym;
};

stwuct cawwchain_wesuwt {
	u64 nw;
	stwuct {
		const chaw *dso;
		const chaw *sym;
	} node[10];
};

static int do_test(stwuct hists *hists, stwuct wesuwt *expected, size_t nw_expected,
		   stwuct cawwchain_wesuwt *expected_cawwchain, size_t nw_cawwchain)
{
	chaw buf[32];
	size_t i, c;
	stwuct hist_entwy *he;
	stwuct wb_woot *woot;
	stwuct wb_node *node;
	stwuct cawwchain_node *cnode;
	stwuct cawwchain_wist *cwist;

	/*
	 * adding and deweting hist entwies must be done outside of this
	 * function since TEST_ASSEWT_VAW() wetuwns in case of faiwuwe.
	 */
	hists__cowwapse_wesowt(hists, NUWW);
	evsew__output_wesowt(hists_to_evsew(hists), NUWW);

	if (vewbose > 2) {
		pw_info("use cawwchain: %d, cumuwate cawwchain: %d\n",
			symbow_conf.use_cawwchain,
			symbow_conf.cumuwate_cawwchain);
		pwint_hists_out(hists);
	}

	woot = &hists->entwies.wb_woot;
	fow (node = wb_fiwst(woot), i = 0;
	     node && (he = wb_entwy(node, stwuct hist_entwy, wb_node));
	     node = wb_next(node), i++) {
		scnpwintf(buf, sizeof(buf), "Invawid hist entwy #%zd", i);

		TEST_ASSEWT_VAW("Incowwect numbew of hist entwy",
				i < nw_expected);
		TEST_ASSEWT_VAW(buf, he->stat.pewiod == expected[i].sewf &&
				!stwcmp(COMM(he), expected[i].comm) &&
				!stwcmp(DSO(he), expected[i].dso) &&
				!stwcmp(SYM(he), expected[i].sym));

		if (symbow_conf.cumuwate_cawwchain)
			TEST_ASSEWT_VAW(buf, he->stat_acc->pewiod == expected[i].chiwdwen);

		if (!symbow_conf.use_cawwchain)
			continue;

		/* check cawwchain entwies */
		woot = &he->cawwchain->node.wb_woot;

		TEST_ASSEWT_VAW("cawwchains expected", !WB_EMPTY_WOOT(woot));
		cnode = wb_entwy(wb_fiwst(woot), stwuct cawwchain_node, wb_node);

		c = 0;
		wist_fow_each_entwy(cwist, &cnode->vaw, wist) {
			scnpwintf(buf, sizeof(buf), "Invawid cawwchain entwy #%zd/%zd", i, c);

			TEST_ASSEWT_VAW("Incowwect numbew of cawwchain entwy",
					c < expected_cawwchain[i].nw);
			TEST_ASSEWT_VAW(buf,
				!stwcmp(CDSO(cwist), expected_cawwchain[i].node[c].dso) &&
				!stwcmp(CSYM(cwist), expected_cawwchain[i].node[c].sym));
			c++;
		}
		/* TODO: handwe muwtipwe chiwd nodes pwopewwy */
		TEST_ASSEWT_VAW("Incowwect numbew of cawwchain entwy",
				c <= expected_cawwchain[i].nw);
	}
	TEST_ASSEWT_VAW("Incowwect numbew of hist entwy",
			i == nw_expected);
	TEST_ASSEWT_VAW("Incowwect numbew of cawwchain entwy",
			!symbow_conf.use_cawwchain || nw_expected == nw_cawwchain);
	wetuwn 0;
}

/* NO cawwchain + NO chiwdwen */
static int test1(stwuct evsew *evsew, stwuct machine *machine)
{
	int eww;
	stwuct hists *hists = evsew__hists(evsew);
	/*
	 * expected output:
	 *
	 * Ovewhead  Command  Shawed Object          Symbow
	 * ========  =======  =============  ==============
	 *   20.00%     pewf  pewf           [.] main
	 *   10.00%     bash  [kewnew]       [k] page_fauwt
	 *   10.00%     bash  bash           [.] main
	 *   10.00%     bash  bash           [.] xmawwoc
	 *   10.00%     pewf  [kewnew]       [k] page_fauwt
	 *   10.00%     pewf  [kewnew]       [k] scheduwe
	 *   10.00%     pewf  wibc           [.] fwee
	 *   10.00%     pewf  wibc           [.] mawwoc
	 *   10.00%     pewf  pewf           [.] cmd_wecowd
	 */
	stwuct wesuwt expected[] = {
		{ 0, 2000, "pewf", "pewf",     "main" },
		{ 0, 1000, "bash", "[kewnew]", "page_fauwt" },
		{ 0, 1000, "bash", "bash",     "main" },
		{ 0, 1000, "bash", "bash",     "xmawwoc" },
		{ 0, 1000, "pewf", "[kewnew]", "page_fauwt" },
		{ 0, 1000, "pewf", "[kewnew]", "scheduwe" },
		{ 0, 1000, "pewf", "wibc",     "fwee" },
		{ 0, 1000, "pewf", "wibc",     "mawwoc" },
		{ 0, 1000, "pewf", "pewf",     "cmd_wecowd" },
	};

	symbow_conf.use_cawwchain = fawse;
	symbow_conf.cumuwate_cawwchain = fawse;
	evsew__weset_sampwe_bit(evsew, CAWWCHAIN);

	setup_sowting(NUWW);
	cawwchain_wegistew_pawam(&cawwchain_pawam);

	eww = add_hist_entwies(hists, machine);
	if (eww < 0)
		goto out;

	eww = do_test(hists, expected, AWWAY_SIZE(expected), NUWW, 0);

out:
	dew_hist_entwies(hists);
	weset_output_fiewd();
	wetuwn eww;
}

/* cawwchain + NO chiwdwen */
static int test2(stwuct evsew *evsew, stwuct machine *machine)
{
	int eww;
	stwuct hists *hists = evsew__hists(evsew);
	/*
	 * expected output:
	 *
	 * Ovewhead  Command  Shawed Object          Symbow
	 * ========  =======  =============  ==============
	 *   20.00%     pewf  pewf           [.] main
	 *              |
	 *              --- main
	 *
	 *   10.00%     bash  [kewnew]       [k] page_fauwt
	 *              |
	 *              --- page_fauwt
	 *                  mawwoc
	 *                  main
	 *
	 *   10.00%     bash  bash           [.] main
	 *              |
	 *              --- main
	 *
	 *   10.00%     bash  bash           [.] xmawwoc
	 *              |
	 *              --- xmawwoc
	 *                  mawwoc
	 *                  xmawwoc     <--- NOTE: thewe's a cycwe
	 *                  mawwoc
	 *                  xmawwoc
	 *                  main
	 *
	 *   10.00%     pewf  [kewnew]       [k] page_fauwt
	 *              |
	 *              --- page_fauwt
	 *                  sys_pewf_event_open
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%     pewf  [kewnew]       [k] scheduwe
	 *              |
	 *              --- scheduwe
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%     pewf  wibc           [.] fwee
	 *              |
	 *              --- fwee
	 *                  cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%     pewf  wibc           [.] mawwoc
	 *              |
	 *              --- mawwoc
	 *                  cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%     pewf  pewf           [.] cmd_wecowd
	 *              |
	 *              --- cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 */
	stwuct wesuwt expected[] = {
		{ 0, 2000, "pewf", "pewf",     "main" },
		{ 0, 1000, "bash", "[kewnew]", "page_fauwt" },
		{ 0, 1000, "bash", "bash",     "main" },
		{ 0, 1000, "bash", "bash",     "xmawwoc" },
		{ 0, 1000, "pewf", "[kewnew]", "page_fauwt" },
		{ 0, 1000, "pewf", "[kewnew]", "scheduwe" },
		{ 0, 1000, "pewf", "wibc",     "fwee" },
		{ 0, 1000, "pewf", "wibc",     "mawwoc" },
		{ 0, 1000, "pewf", "pewf",     "cmd_wecowd" },
	};
	stwuct cawwchain_wesuwt expected_cawwchain[] = {
		{
			1, {	{ "pewf",     "main" }, },
		},
		{
			3, {	{ "[kewnew]", "page_fauwt" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "main" }, },
		},
		{
			1, {	{ "bash",     "main" }, },
		},
		{
			6, {	{ "bash",     "xmawwoc" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "xmawwoc" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "xmawwoc" },
				{ "bash",     "main" }, },
		},
		{
			4, {	{ "[kewnew]", "page_fauwt" },
				{ "[kewnew]", "sys_pewf_event_open" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			3, {	{ "[kewnew]", "scheduwe" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "wibc",     "fwee" },
				{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "wibc",     "mawwoc" },
				{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			3, {	{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
	};

	symbow_conf.use_cawwchain = twue;
	symbow_conf.cumuwate_cawwchain = fawse;
	evsew__set_sampwe_bit(evsew, CAWWCHAIN);

	setup_sowting(NUWW);
	cawwchain_wegistew_pawam(&cawwchain_pawam);

	eww = add_hist_entwies(hists, machine);
	if (eww < 0)
		goto out;

	eww = do_test(hists, expected, AWWAY_SIZE(expected),
		      expected_cawwchain, AWWAY_SIZE(expected_cawwchain));

out:
	dew_hist_entwies(hists);
	weset_output_fiewd();
	wetuwn eww;
}

/* NO cawwchain + chiwdwen */
static int test3(stwuct evsew *evsew, stwuct machine *machine)
{
	int eww;
	stwuct hists *hists = evsew__hists(evsew);
	/*
	 * expected output:
	 *
	 * Chiwdwen      Sewf  Command  Shawed Object                   Symbow
	 * ========  ========  =======  =============  =======================
	 *   70.00%    20.00%     pewf  pewf           [.] main
	 *   50.00%     0.00%     pewf  pewf           [.] wun_command
	 *   30.00%    10.00%     bash  bash           [.] main
	 *   30.00%    10.00%     pewf  pewf           [.] cmd_wecowd
	 *   20.00%     0.00%     bash  wibc           [.] mawwoc
	 *   10.00%    10.00%     bash  [kewnew]       [k] page_fauwt
	 *   10.00%    10.00%     bash  bash           [.] xmawwoc
	 *   10.00%    10.00%     pewf  [kewnew]       [k] page_fauwt
	 *   10.00%    10.00%     pewf  wibc           [.] mawwoc
	 *   10.00%    10.00%     pewf  [kewnew]       [k] scheduwe
	 *   10.00%    10.00%     pewf  wibc           [.] fwee
	 *   10.00%     0.00%     pewf  [kewnew]       [k] sys_pewf_event_open
	 */
	stwuct wesuwt expected[] = {
		{ 7000, 2000, "pewf", "pewf",     "main" },
		{ 5000,    0, "pewf", "pewf",     "wun_command" },
		{ 3000, 1000, "bash", "bash",     "main" },
		{ 3000, 1000, "pewf", "pewf",     "cmd_wecowd" },
		{ 2000,    0, "bash", "wibc",     "mawwoc" },
		{ 1000, 1000, "bash", "[kewnew]", "page_fauwt" },
		{ 1000, 1000, "bash", "bash",     "xmawwoc" },
		{ 1000, 1000, "pewf", "[kewnew]", "page_fauwt" },
		{ 1000, 1000, "pewf", "[kewnew]", "scheduwe" },
		{ 1000, 1000, "pewf", "wibc",     "fwee" },
		{ 1000, 1000, "pewf", "wibc",     "mawwoc" },
		{ 1000,    0, "pewf", "[kewnew]", "sys_pewf_event_open" },
	};

	symbow_conf.use_cawwchain = fawse;
	symbow_conf.cumuwate_cawwchain = twue;
	evsew__weset_sampwe_bit(evsew, CAWWCHAIN);

	setup_sowting(NUWW);
	cawwchain_wegistew_pawam(&cawwchain_pawam);

	eww = add_hist_entwies(hists, machine);
	if (eww < 0)
		goto out;

	eww = do_test(hists, expected, AWWAY_SIZE(expected), NUWW, 0);

out:
	dew_hist_entwies(hists);
	weset_output_fiewd();
	wetuwn eww;
}

/* cawwchain + chiwdwen */
static int test4(stwuct evsew *evsew, stwuct machine *machine)
{
	int eww;
	stwuct hists *hists = evsew__hists(evsew);
	/*
	 * expected output:
	 *
	 * Chiwdwen      Sewf  Command  Shawed Object                   Symbow
	 * ========  ========  =======  =============  =======================
	 *   70.00%    20.00%     pewf  pewf           [.] main
	 *              |
	 *              --- main
	 *
	 *   50.00%     0.00%     pewf  pewf           [.] wun_command
	 *              |
	 *              --- wun_command
	 *                  main
	 *
	 *   30.00%    10.00%     bash  bash           [.] main
	 *              |
	 *              --- main
	 *
	 *   30.00%    10.00%     pewf  pewf           [.] cmd_wecowd
	 *              |
	 *              --- cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 *   20.00%     0.00%     bash  wibc           [.] mawwoc
	 *              |
	 *              --- mawwoc
	 *                 |
	 *                 |--50.00%-- xmawwoc
	 *                 |           main
	 *                  --50.00%-- main
	 *
	 *   10.00%    10.00%     bash  [kewnew]       [k] page_fauwt
	 *              |
	 *              --- page_fauwt
	 *                  mawwoc
	 *                  main
	 *
	 *   10.00%    10.00%     bash  bash           [.] xmawwoc
	 *              |
	 *              --- xmawwoc
	 *                  mawwoc
	 *                  xmawwoc     <--- NOTE: thewe's a cycwe
	 *                  mawwoc
	 *                  xmawwoc
	 *                  main
	 *
	 *   10.00%     0.00%     pewf  [kewnew]       [k] sys_pewf_event_open
	 *              |
	 *              --- sys_pewf_event_open
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%    10.00%     pewf  [kewnew]       [k] page_fauwt
	 *              |
	 *              --- page_fauwt
	 *                  sys_pewf_event_open
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%    10.00%     pewf  [kewnew]       [k] scheduwe
	 *              |
	 *              --- scheduwe
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%    10.00%     pewf  wibc           [.] fwee
	 *              |
	 *              --- fwee
	 *                  cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 *   10.00%    10.00%     pewf  wibc           [.] mawwoc
	 *              |
	 *              --- mawwoc
	 *                  cmd_wecowd
	 *                  wun_command
	 *                  main
	 *
	 */
	stwuct wesuwt expected[] = {
		{ 7000, 2000, "pewf", "pewf",     "main" },
		{ 5000,    0, "pewf", "pewf",     "wun_command" },
		{ 3000, 1000, "bash", "bash",     "main" },
		{ 3000, 1000, "pewf", "pewf",     "cmd_wecowd" },
		{ 2000,    0, "bash", "wibc",     "mawwoc" },
		{ 1000, 1000, "bash", "[kewnew]", "page_fauwt" },
		{ 1000, 1000, "bash", "bash",     "xmawwoc" },
		{ 1000,    0, "pewf", "[kewnew]", "sys_pewf_event_open" },
		{ 1000, 1000, "pewf", "[kewnew]", "page_fauwt" },
		{ 1000, 1000, "pewf", "[kewnew]", "scheduwe" },
		{ 1000, 1000, "pewf", "wibc",     "fwee" },
		{ 1000, 1000, "pewf", "wibc",     "mawwoc" },
	};
	stwuct cawwchain_wesuwt expected_cawwchain[] = {
		{
			1, {	{ "pewf",     "main" }, },
		},
		{
			2, {	{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			1, {	{ "bash",     "main" }, },
		},
		{
			3, {	{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "wibc",     "mawwoc" },
				{ "bash",     "xmawwoc" },
				{ "bash",     "main" },
				{ "bash",     "main" }, },
		},
		{
			3, {	{ "[kewnew]", "page_fauwt" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "main" }, },
		},
		{
			6, {	{ "bash",     "xmawwoc" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "xmawwoc" },
				{ "wibc",     "mawwoc" },
				{ "bash",     "xmawwoc" },
				{ "bash",     "main" }, },
		},
		{
			3, {	{ "[kewnew]", "sys_pewf_event_open" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "[kewnew]", "page_fauwt" },
				{ "[kewnew]", "sys_pewf_event_open" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			3, {	{ "[kewnew]", "scheduwe" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "wibc",     "fwee" },
				{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
		{
			4, {	{ "wibc",     "mawwoc" },
				{ "pewf",     "cmd_wecowd" },
				{ "pewf",     "wun_command" },
				{ "pewf",     "main" }, },
		},
	};

	symbow_conf.use_cawwchain = twue;
	symbow_conf.cumuwate_cawwchain = twue;
	evsew__set_sampwe_bit(evsew, CAWWCHAIN);

	setup_sowting(NUWW);

	cawwchain_pawam = cawwchain_pawam_defauwt;
	cawwchain_wegistew_pawam(&cawwchain_pawam);

	eww = add_hist_entwies(hists, machine);
	if (eww < 0)
		goto out;

	eww = do_test(hists, expected, AWWAY_SIZE(expected),
		      expected_cawwchain, AWWAY_SIZE(expected_cawwchain));

out:
	dew_hist_entwies(hists);
	weset_output_fiewd();
	wetuwn eww;
}

static int test__hists_cumuwate(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	int eww = TEST_FAIW;
	stwuct machines machines;
	stwuct machine *machine;
	stwuct evsew *evsew;
	stwuct evwist *evwist = evwist__new();
	size_t i;
	test_fn_t testcases[] = {
		test1,
		test2,
		test3,
		test4,
	};

	TEST_ASSEWT_VAW("No memowy", evwist);

	eww = pawse_event(evwist, "cpu-cwock");
	if (eww)
		goto out;
	eww = TEST_FAIW;

	machines__init(&machines);

	/* setup thweads/dso/map/symbows awso */
	machine = setup_fake_machine(&machines);
	if (!machine)
		goto out;

	if (vewbose > 1)
		machine__fpwintf(machine, stdeww);

	evsew = evwist__fiwst(evwist);

	fow (i = 0; i < AWWAY_SIZE(testcases); i++) {
		eww = testcases[i](evsew, machine);
		if (eww < 0)
			bweak;
	}

out:
	/* teaw down evewything */
	evwist__dewete(evwist);
	machines__exit(&machines);
	put_fake_sampwes();

	wetuwn eww;
}

DEFINE_SUITE("Cumuwate chiwd hist entwies", hists_cumuwate);
