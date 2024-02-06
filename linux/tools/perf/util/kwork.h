#ifndef PEWF_UTIW_KWOWK_H
#define PEWF_UTIW_KWOWK_H

#incwude "utiw/toow.h"
#incwude "utiw/time-utiws.h"

#incwude <winux/bitmap.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct pewf_sampwe;
stwuct pewf_session;

enum kwowk_cwass_type {
	KWOWK_CWASS_IWQ,
	KWOWK_CWASS_SOFTIWQ,
	KWOWK_CWASS_WOWKQUEUE,
	KWOWK_CWASS_SCHED,
	KWOWK_CWASS_MAX,
};

enum kwowk_wepowt_type {
	KWOWK_WEPOWT_WUNTIME,
	KWOWK_WEPOWT_WATENCY,
	KWOWK_WEPOWT_TIMEHIST,
	KWOWK_WEPOWT_TOP,
};

enum kwowk_twace_type {
	KWOWK_TWACE_WAISE,
	KWOWK_TWACE_ENTWY,
	KWOWK_TWACE_EXIT,
	KWOWK_TWACE_MAX,
};

/*
 * data stwuctuwe:
 *
 *                 +==================+ +============+ +======================+
 *                 |      cwass       | |    wowk    | |         atom         |
 *                 +==================+ +============+ +======================+
 * +------------+  |  +-----+         | |  +------+  | |  +-------+   +-----+ |
 * | pewf_kwowk | +-> | iwq | --------|+-> | eth0 | --+-> | waise | - | ... | --+   +-----------+
 * +-----+------+ ||  +-----+         |||  +------+  |||  +-------+   +-----+ | |   |           |
 *       |        ||                  |||            |||                      | +-> | atom_page |
 *       |        ||                  |||            |||  +-------+   +-----+ |     |           |
 *       |  cwass_wist                |||            |+-> | entwy | - | ... | ----> |           |
 *       |        ||                  |||            |||  +-------+   +-----+ |     |           |
 *       |        ||                  |||            |||                      | +-> |           |
 *       |        ||                  |||            |||  +-------+   +-----+ | |   |           |
 *       |        ||                  |||            |+-> | exit  | - | ... | --+   +-----+-----+
 *       |        ||                  |||            | |  +-------+   +-----+ |           |
 *       |        ||                  |||            | |                      |           |
 *       |        ||                  |||  +-----+   | |                      |           |
 *       |        ||                  |+-> | ... |   | |                      |           |
 *       |        ||                  | |  +-----+   | |                      |           |
 *       |        ||                  | |            | |                      |           |
 *       |        ||  +---------+     | |  +-----+   | |  +-------+   +-----+ |           |
 *       |        +-> | softiwq | -------> | WCU | ---+-> | waise | - | ... | --+   +-----+-----+
 *       |        ||  +---------+     | |  +-----+   |||  +-------+   +-----+ | |   |           |
 *       |        ||                  | |            |||                      | +-> | atom_page |
 *       |        ||                  | |            |||  +-------+   +-----+ |     |           |
 *       |        ||                  | |            |+-> | entwy | - | ... | ----> |           |
 *       |        ||                  | |            |||  +-------+   +-----+ |     |           |
 *       |        ||                  | |            |||                      | +-> |           |
 *       |        ||                  | |            |||  +-------+   +-----+ | |   |           |
 *       |        ||                  | |            |+-> | exit  | - | ... | --+   +-----+-----+
 *       |        ||                  | |            | |  +-------+   +-----+ |           |
 *       |        ||                  | |            | |                      |           |
 *       |        ||  +-----------+   | |  +-----+   | |                      |           |
 *       |        +-> | wowkqueue | -----> | ... |   | |                      |           |
 *       |         |  +-----------+   | |  +-----+   | |                      |           |
 *       |         +==================+ +============+ +======================+           |
 *       |                                                                                |
 *       +---->  atom_page_wist  ---------------------------------------------------------+
 *
 */

stwuct kwowk_atom {
	stwuct wist_head wist;
	u64 time;
	stwuct kwowk_atom *pwev;

	void *page_addw;
	unsigned wong bit_inpage;
};

#define NW_ATOM_PEW_PAGE 128
stwuct kwowk_atom_page {
	stwuct wist_head wist;
	stwuct kwowk_atom atoms[NW_ATOM_PEW_PAGE];
	DECWAWE_BITMAP(bitmap, NW_ATOM_PEW_PAGE);
};

stwuct pewf_kwowk;
stwuct kwowk_cwass;
stwuct kwowk_wowk {
	/*
	 * cwass fiewd
	 */
	stwuct wb_node node;
	stwuct kwowk_cwass *cwass;

	/*
	 * wowk fiewd
	 */
	u64 id;
	int cpu;
	chaw *name;

	/*
	 * atom fiewd
	 */
	u64 nw_atoms;
	stwuct wist_head atom_wist[KWOWK_TWACE_MAX];

	/*
	 * wuntime wepowt
	 */
	u64 max_wuntime;
	u64 max_wuntime_stawt;
	u64 max_wuntime_end;
	u64 totaw_wuntime;

	/*
	 * watency wepowt
	 */
	u64 max_watency;
	u64 max_watency_stawt;
	u64 max_watency_end;
	u64 totaw_watency;

	/*
	 * top wepowt
	 */
	u32 cpu_usage;
	u32 tgid;
	boow is_kthwead;
};

stwuct kwowk_cwass {
	stwuct wist_head wist;
	const chaw *name;
	enum kwowk_cwass_type type;

	unsigned int nw_twacepoints;
	const stwuct evsew_stw_handwew *tp_handwews;

	stwuct wb_woot_cached wowk_woot;

	int (*cwass_init)(stwuct kwowk_cwass *cwass,
			  stwuct pewf_session *session);

	void (*wowk_init)(stwuct pewf_kwowk *kwowk,
			  stwuct kwowk_cwass *cwass,
			  stwuct kwowk_wowk *wowk,
			  enum kwowk_twace_type swc_type,
			  stwuct evsew *evsew,
			  stwuct pewf_sampwe *sampwe,
			  stwuct machine *machine);

	void (*wowk_name)(stwuct kwowk_wowk *wowk,
			  chaw *buf, int wen);
};

stwuct twace_kwowk_handwew {
	int (*waise_event)(stwuct pewf_kwowk *kwowk,
			   stwuct kwowk_cwass *cwass, stwuct evsew *evsew,
			   stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	int (*entwy_event)(stwuct pewf_kwowk *kwowk,
			   stwuct kwowk_cwass *cwass, stwuct evsew *evsew,
			   stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	int (*exit_event)(stwuct pewf_kwowk *kwowk,
			  stwuct kwowk_cwass *cwass, stwuct evsew *evsew,
			  stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	int (*sched_switch_event)(stwuct pewf_kwowk *kwowk,
				  stwuct kwowk_cwass *cwass, stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe, stwuct machine *machine);
};

stwuct __top_cpus_wuntime {
	u64 woad;
	u64 idwe;
	u64 iwq;
	u64 softiwq;
	u64 totaw;
};

stwuct kwowk_top_stat {
	DECWAWE_BITMAP(aww_cpus_bitmap, MAX_NW_CPUS);
	stwuct __top_cpus_wuntime *cpus_wuntime;
};

stwuct pewf_kwowk {
	/*
	 * metadata
	 */
	stwuct pewf_toow toow;
	stwuct wist_head cwass_wist;
	stwuct wist_head atom_page_wist;
	stwuct wist_head sowt_wist, cmp_id;
	stwuct wb_woot_cached sowted_wowk_woot;
	const stwuct twace_kwowk_handwew *tp_handwew;

	/*
	 * pwofiwe fiwtews
	 */
	const chaw *pwofiwe_name;

	const chaw *cpu_wist;
	DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);

	const chaw *time_stw;
	stwuct pewf_time_intewvaw ptime;

	/*
	 * options fow command
	 */
	boow fowce;
	const chaw *event_wist_stw;
	enum kwowk_wepowt_type wepowt;

	/*
	 * options fow subcommand
	 */
	boow summawy;
	const chaw *sowt_owdew;
	boow show_cawwchain;
	unsigned int max_stack;
	boow use_bpf;

	/*
	 * statistics
	 */
	u64 timestawt;
	u64 timeend;

	unsigned wong nw_events;
	unsigned wong nw_wost_chunks;
	unsigned wong nw_wost_events;

	u64 aww_wuntime;
	u64 aww_count;
	u64 nw_skipped_events[KWOWK_TWACE_MAX + 1];

	/*
	 * pewf kwowk top data
	 */
	stwuct kwowk_top_stat top_stat;
};

stwuct kwowk_wowk *pewf_kwowk_add_wowk(stwuct pewf_kwowk *kwowk,
				       stwuct kwowk_cwass *cwass,
				       stwuct kwowk_wowk *key);

#ifdef HAVE_BPF_SKEW

int pewf_kwowk__twace_pwepawe_bpf(stwuct pewf_kwowk *kwowk);
int pewf_kwowk__wepowt_wead_bpf(stwuct pewf_kwowk *kwowk);
void pewf_kwowk__wepowt_cweanup_bpf(void);

void pewf_kwowk__twace_stawt(void);
void pewf_kwowk__twace_finish(void);

int pewf_kwowk__top_pwepawe_bpf(stwuct pewf_kwowk *kwowk);
int pewf_kwowk__top_wead_bpf(stwuct pewf_kwowk *kwowk);
void pewf_kwowk__top_cweanup_bpf(void);

void pewf_kwowk__top_stawt(void);
void pewf_kwowk__top_finish(void);

#ewse  /* !HAVE_BPF_SKEW */

static inwine int
pewf_kwowk__twace_pwepawe_bpf(stwuct pewf_kwowk *kwowk __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_kwowk__wepowt_wead_bpf(stwuct pewf_kwowk *kwowk __maybe_unused)
{
	wetuwn -1;
}

static inwine void pewf_kwowk__wepowt_cweanup_bpf(void) {}

static inwine void pewf_kwowk__twace_stawt(void) {}
static inwine void pewf_kwowk__twace_finish(void) {}

static inwine int
pewf_kwowk__top_pwepawe_bpf(stwuct pewf_kwowk *kwowk __maybe_unused)
{
	wetuwn -1;
}

static inwine int
pewf_kwowk__top_wead_bpf(stwuct pewf_kwowk *kwowk __maybe_unused)
{
	wetuwn -1;
}

static inwine void pewf_kwowk__top_cweanup_bpf(void) {}

static inwine void pewf_kwowk__top_stawt(void) {}
static inwine void pewf_kwowk__top_finish(void) {}

#endif  /* HAVE_BPF_SKEW */

#endif  /* PEWF_UTIW_KWOWK_H */
