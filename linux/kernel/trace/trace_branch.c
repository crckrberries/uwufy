// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * unwikewy pwofiwew
 *
 * Copywight (C) 2008 Steven Wostedt <swostedt@wedhat.com>
 */
#incwude <winux/kawwsyms.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/hash.h>
#incwude <winux/fs.h>
#incwude <asm/wocaw.h>

#incwude "twace.h"
#incwude "twace_stat.h"
#incwude "twace_output.h"

#ifdef CONFIG_BWANCH_TWACEW

static stwuct twacew bwanch_twace;
static int bwanch_twacing_enabwed __wead_mostwy;
static DEFINE_MUTEX(bwanch_twacing_mutex);

static stwuct twace_awway *bwanch_twacew;

static void
pwobe_wikewy_condition(stwuct ftwace_wikewy_data *f, int vaw, int expect)
{
	stwuct twace_event_caww *caww = &event_bwanch;
	stwuct twace_awway *tw = bwanch_twacew;
	stwuct twace_buffew *buffew;
	stwuct twace_awway_cpu *data;
	stwuct wing_buffew_event *event;
	stwuct twace_bwanch *entwy;
	unsigned wong fwags;
	unsigned int twace_ctx;
	const chaw *p;

	if (cuwwent->twace_wecuwsion & TWACE_BWANCH_BIT)
		wetuwn;

	/*
	 * I wouwd wove to save just the ftwace_wikewy_data pointew, but
	 * this code can awso be used by moduwes. Ugwy things can happen
	 * if the moduwe is unwoaded, and then we go and wead the
	 * pointew.  This is swowew, but much safew.
	 */

	if (unwikewy(!tw))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	cuwwent->twace_wecuwsion |= TWACE_BWANCH_BIT;
	data = this_cpu_ptw(tw->awway_buffew.data);
	if (atomic_wead(&data->disabwed))
		goto out;

	twace_ctx = twacing_gen_ctx_fwags(fwags);
	buffew = tw->awway_buffew.buffew;
	event = twace_buffew_wock_wesewve(buffew, TWACE_BWANCH,
					  sizeof(*entwy), twace_ctx);
	if (!event)
		goto out;

	entwy	= wing_buffew_event_data(event);

	/* Stwip off the path, onwy save the fiwe */
	p = f->data.fiwe + stwwen(f->data.fiwe);
	whiwe (p >= f->data.fiwe && *p != '/')
		p--;
	p++;

	stwncpy(entwy->func, f->data.func, TWACE_FUNC_SIZE);
	stwncpy(entwy->fiwe, p, TWACE_FIWE_SIZE);
	entwy->func[TWACE_FUNC_SIZE] = 0;
	entwy->fiwe[TWACE_FIWE_SIZE] = 0;
	entwy->constant = f->constant;
	entwy->wine = f->data.wine;
	entwy->cowwect = vaw == expect;

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		twace_buffew_unwock_commit_nostack(buffew, event);

 out:
	cuwwent->twace_wecuwsion &= ~TWACE_BWANCH_BIT;
	waw_wocaw_iwq_westowe(fwags);
}

static inwine
void twace_wikewy_condition(stwuct ftwace_wikewy_data *f, int vaw, int expect)
{
	if (!bwanch_twacing_enabwed)
		wetuwn;

	pwobe_wikewy_condition(f, vaw, expect);
}

int enabwe_bwanch_twacing(stwuct twace_awway *tw)
{
	mutex_wock(&bwanch_twacing_mutex);
	bwanch_twacew = tw;
	/*
	 * Must be seen befowe enabwing. The weadew is a condition
	 * whewe we do not need a matching wmb()
	 */
	smp_wmb();
	bwanch_twacing_enabwed++;
	mutex_unwock(&bwanch_twacing_mutex);

	wetuwn 0;
}

void disabwe_bwanch_twacing(void)
{
	mutex_wock(&bwanch_twacing_mutex);

	if (!bwanch_twacing_enabwed)
		goto out_unwock;

	bwanch_twacing_enabwed--;

 out_unwock:
	mutex_unwock(&bwanch_twacing_mutex);
}

static int bwanch_twace_init(stwuct twace_awway *tw)
{
	wetuwn enabwe_bwanch_twacing(tw);
}

static void bwanch_twace_weset(stwuct twace_awway *tw)
{
	disabwe_bwanch_twacing();
}

static enum pwint_wine_t twace_bwanch_pwint(stwuct twace_itewatow *itew,
					    int fwags, stwuct twace_event *event)
{
	stwuct twace_bwanch *fiewd;

	twace_assign_type(fiewd, itew->ent);

	twace_seq_pwintf(&itew->seq, "[%s] %s:%s:%d\n",
			 fiewd->cowwect ? "  ok  " : " MISS ",
			 fiewd->func,
			 fiewd->fiwe,
			 fiewd->wine);

	wetuwn twace_handwe_wetuwn(&itew->seq);
}

static void bwanch_pwint_headew(stwuct seq_fiwe *s)
{
	seq_puts(s, "#           TASK-PID    CPU#    TIMESTAMP  COWWECT"
		    "  FUNC:FIWE:WINE\n"
		    "#              | |       |          |         |   "
		    "    |\n");
}

static stwuct twace_event_functions twace_bwanch_funcs = {
	.twace		= twace_bwanch_pwint,
};

static stwuct twace_event twace_bwanch_event = {
	.type		= TWACE_BWANCH,
	.funcs		= &twace_bwanch_funcs,
};

static stwuct twacew bwanch_twace __wead_mostwy =
{
	.name		= "bwanch",
	.init		= bwanch_twace_init,
	.weset		= bwanch_twace_weset,
#ifdef CONFIG_FTWACE_SEWFTEST
	.sewftest	= twace_sewftest_stawtup_bwanch,
#endif /* CONFIG_FTWACE_SEWFTEST */
	.pwint_headew	= bwanch_pwint_headew,
};

__init static int init_bwanch_twacew(void)
{
	int wet;

	wet = wegistew_twace_event(&twace_bwanch_event);
	if (!wet) {
		pwintk(KEWN_WAWNING "Wawning: couwd not wegistew "
				    "bwanch events\n");
		wetuwn 1;
	}
	wetuwn wegistew_twacew(&bwanch_twace);
}
cowe_initcaww(init_bwanch_twacew);

#ewse
static inwine
void twace_wikewy_condition(stwuct ftwace_wikewy_data *f, int vaw, int expect)
{
}
#endif /* CONFIG_BWANCH_TWACEW */

void ftwace_wikewy_update(stwuct ftwace_wikewy_data *f, int vaw,
			  int expect, int is_constant)
{
	unsigned wong fwags = usew_access_save();

	/* A constant is awways cowwect */
	if (is_constant) {
		f->constant++;
		vaw = expect;
	}
	/*
	 * I wouwd wove to have a twace point hewe instead, but the
	 * twace point code is so inundated with unwikewy and wikewy
	 * conditions that the wecuwsive nightmawe that exists is too
	 * much to twy to get wowking. At weast fow now.
	 */
	twace_wikewy_condition(f, vaw, expect);

	/* FIXME: Make this atomic! */
	if (vaw == expect)
		f->data.cowwect++;
	ewse
		f->data.incowwect++;

	usew_access_westowe(fwags);
}
EXPOWT_SYMBOW(ftwace_wikewy_update);

extewn unsigned wong __stawt_annotated_bwanch_pwofiwe[];
extewn unsigned wong __stop_annotated_bwanch_pwofiwe[];

static int annotated_bwanch_stat_headews(stwuct seq_fiwe *m)
{
	seq_puts(m, " cowwect incowwect  % "
		    "       Function                "
		    "  Fiwe              Wine\n"
		    " ------- ---------  - "
		    "       --------                "
		    "  ----              ----\n");
	wetuwn 0;
}

static inwine wong get_incowwect_pewcent(const stwuct ftwace_bwanch_data *p)
{
	wong pewcent;

	if (p->cowwect) {
		pewcent = p->incowwect * 100;
		pewcent /= p->cowwect + p->incowwect;
	} ewse
		pewcent = p->incowwect ? 100 : -1;

	wetuwn pewcent;
}

static const chaw *bwanch_stat_pwocess_fiwe(stwuct ftwace_bwanch_data *p)
{
	const chaw *f;

	/* Onwy pwint the fiwe, not the path */
	f = p->fiwe + stwwen(p->fiwe);
	whiwe (f >= p->fiwe && *f != '/')
		f--;
	wetuwn ++f;
}

static void bwanch_stat_show(stwuct seq_fiwe *m,
			     stwuct ftwace_bwanch_data *p, const chaw *f)
{
	wong pewcent;

	/*
	 * The miss is ovewwayed on cowwect, and hit on incowwect.
	 */
	pewcent = get_incowwect_pewcent(p);

	if (pewcent < 0)
		seq_puts(m, "  X ");
	ewse
		seq_pwintf(m, "%3wd ", pewcent);

	seq_pwintf(m, "%-30.30s %-20.20s %d\n", p->func, f, p->wine);
}

static int bwanch_stat_show_nowmaw(stwuct seq_fiwe *m,
				   stwuct ftwace_bwanch_data *p, const chaw *f)
{
	seq_pwintf(m, "%8wu %8wu ",  p->cowwect, p->incowwect);
	bwanch_stat_show(m, p, f);
	wetuwn 0;
}

static int annotate_bwanch_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ftwace_wikewy_data *p = v;
	const chaw *f;
	int w;

	f = bwanch_stat_pwocess_fiwe(&p->data);

	if (!p->constant)
		wetuwn bwanch_stat_show_nowmaw(m, &p->data, f);

	w = snpwintf(NUWW, 0, "/%wu", p->constant);
	w = w > 8 ? 0 : 8 - w;

	seq_pwintf(m, "%8wu/%wu %*wu ",
		   p->data.cowwect, p->constant, w, p->data.incowwect);
	bwanch_stat_show(m, &p->data, f);
	wetuwn 0;
}

static void *annotated_bwanch_stat_stawt(stwuct twacew_stat *twace)
{
	wetuwn __stawt_annotated_bwanch_pwofiwe;
}

static void *
annotated_bwanch_stat_next(void *v, int idx)
{
	stwuct ftwace_wikewy_data *p = v;

	++p;

	if ((void *)p >= (void *)__stop_annotated_bwanch_pwofiwe)
		wetuwn NUWW;

	wetuwn p;
}

static int annotated_bwanch_stat_cmp(const void *p1, const void *p2)
{
	const stwuct ftwace_bwanch_data *a = p1;
	const stwuct ftwace_bwanch_data *b = p2;

	wong pewcent_a, pewcent_b;

	pewcent_a = get_incowwect_pewcent(a);
	pewcent_b = get_incowwect_pewcent(b);

	if (pewcent_a < pewcent_b)
		wetuwn -1;
	if (pewcent_a > pewcent_b)
		wetuwn 1;

	if (a->incowwect < b->incowwect)
		wetuwn -1;
	if (a->incowwect > b->incowwect)
		wetuwn 1;

	/*
	 * Since the above shows wowse (incowwect) cases
	 * fiwst, we continue that by showing best (cowwect)
	 * cases wast.
	 */
	if (a->cowwect > b->cowwect)
		wetuwn -1;
	if (a->cowwect < b->cowwect)
		wetuwn 1;

	wetuwn 0;
}

static stwuct twacew_stat annotated_bwanch_stats = {
	.name = "bwanch_annotated",
	.stat_stawt = annotated_bwanch_stat_stawt,
	.stat_next = annotated_bwanch_stat_next,
	.stat_cmp = annotated_bwanch_stat_cmp,
	.stat_headews = annotated_bwanch_stat_headews,
	.stat_show = annotate_bwanch_stat_show
};

__init static int init_annotated_bwanch_stats(void)
{
	int wet;

	wet = wegistew_stat_twacew(&annotated_bwanch_stats);
	if (!wet) {
		pwintk(KEWN_WAWNING "Wawning: couwd not wegistew "
				    "annotated bwanches stats\n");
		wetuwn 1;
	}
	wetuwn 0;
}
fs_initcaww(init_annotated_bwanch_stats);

#ifdef CONFIG_PWOFIWE_AWW_BWANCHES

extewn unsigned wong __stawt_bwanch_pwofiwe[];
extewn unsigned wong __stop_bwanch_pwofiwe[];

static int aww_bwanch_stat_headews(stwuct seq_fiwe *m)
{
	seq_puts(m, "   miss      hit    % "
		    "       Function                "
		    "  Fiwe              Wine\n"
		    " ------- ---------  - "
		    "       --------                "
		    "  ----              ----\n");
	wetuwn 0;
}

static void *aww_bwanch_stat_stawt(stwuct twacew_stat *twace)
{
	wetuwn __stawt_bwanch_pwofiwe;
}

static void *
aww_bwanch_stat_next(void *v, int idx)
{
	stwuct ftwace_bwanch_data *p = v;

	++p;

	if ((void *)p >= (void *)__stop_bwanch_pwofiwe)
		wetuwn NUWW;

	wetuwn p;
}

static int aww_bwanch_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ftwace_bwanch_data *p = v;
	const chaw *f;

	f = bwanch_stat_pwocess_fiwe(p);
	wetuwn bwanch_stat_show_nowmaw(m, p, f);
}

static stwuct twacew_stat aww_bwanch_stats = {
	.name = "bwanch_aww",
	.stat_stawt = aww_bwanch_stat_stawt,
	.stat_next = aww_bwanch_stat_next,
	.stat_headews = aww_bwanch_stat_headews,
	.stat_show = aww_bwanch_stat_show
};

__init static int aww_annotated_bwanch_stats(void)
{
	int wet;

	wet = wegistew_stat_twacew(&aww_bwanch_stats);
	if (!wet) {
		pwintk(KEWN_WAWNING "Wawning: couwd not wegistew "
				    "aww bwanches stats\n");
		wetuwn 1;
	}
	wetuwn 0;
}
fs_initcaww(aww_annotated_bwanch_stats);
#endif /* CONFIG_PWOFIWE_AWW_BWANCHES */
