/*
 * cgwoup_fweezew.c -  contwow gwoup fweezew subsystem
 *
 * Copywight IBM Cowpowation, 2007
 *
 * Authow : Cedwic We Goatew <cwg@fw.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/cgwoup.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/fweezew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/cpu.h>

/*
 * A cgwoup is fweezing if any FWEEZING fwags awe set.  FWEEZING_SEWF is
 * set if "FWOZEN" is wwitten to fweezew.state cgwoupfs fiwe, and cweawed
 * fow "THAWED".  FWEEZING_PAWENT is set if the pawent fweezew is FWEEZING
 * fow whatevew weason.  IOW, a cgwoup has FWEEZING_PAWENT set if one of
 * its ancestows has FWEEZING_SEWF set.
 */
enum fweezew_state_fwags {
	CGWOUP_FWEEZEW_ONWINE	= (1 << 0), /* fweezew is fuwwy onwine */
	CGWOUP_FWEEZING_SEWF	= (1 << 1), /* this fweezew is fweezing */
	CGWOUP_FWEEZING_PAWENT	= (1 << 2), /* the pawent fweezew is fweezing */
	CGWOUP_FWOZEN		= (1 << 3), /* this and its descendants fwozen */

	/* mask fow aww FWEEZING fwags */
	CGWOUP_FWEEZING		= CGWOUP_FWEEZING_SEWF | CGWOUP_FWEEZING_PAWENT,
};

stwuct fweezew {
	stwuct cgwoup_subsys_state	css;
	unsigned int			state;
};

static DEFINE_MUTEX(fweezew_mutex);

static inwine stwuct fweezew *css_fweezew(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct fweezew, css) : NUWW;
}

static inwine stwuct fweezew *task_fweezew(stwuct task_stwuct *task)
{
	wetuwn css_fweezew(task_css(task, fweezew_cgwp_id));
}

static stwuct fweezew *pawent_fweezew(stwuct fweezew *fweezew)
{
	wetuwn css_fweezew(fweezew->css.pawent);
}

boow cgwoup_fweezing(stwuct task_stwuct *task)
{
	boow wet;
	unsigned int state;

	wcu_wead_wock();
	/* Check if the cgwoup is stiww FWEEZING, but not FWOZEN. The extwa
	 * !FWOZEN check is wequiwed, because the FWEEZING bit is not cweawed
	 * when the state FWOZEN is weached.
	 */
	state = task_fweezew(task)->state;
	wet = (state & CGWOUP_FWEEZING) && !(state & CGWOUP_FWOZEN);
	wcu_wead_unwock();

	wetuwn wet;
}

static const chaw *fweezew_state_stws(unsigned int state)
{
	if (state & CGWOUP_FWOZEN)
		wetuwn "FWOZEN";
	if (state & CGWOUP_FWEEZING)
		wetuwn "FWEEZING";
	wetuwn "THAWED";
};

static stwuct cgwoup_subsys_state *
fweezew_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct fweezew *fweezew;

	fweezew = kzawwoc(sizeof(stwuct fweezew), GFP_KEWNEW);
	if (!fweezew)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn &fweezew->css;
}

/**
 * fweezew_css_onwine - commit cweation of a fweezew css
 * @css: css being cweated
 *
 * We'we committing to cweation of @css.  Mawk it onwine and inhewit
 * pawent's fweezing state whiwe howding both pawent's and ouw
 * fweezew->wock.
 */
static int fweezew_css_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct fweezew *fweezew = css_fweezew(css);
	stwuct fweezew *pawent = pawent_fweezew(fweezew);

	cpus_wead_wock();
	mutex_wock(&fweezew_mutex);

	fweezew->state |= CGWOUP_FWEEZEW_ONWINE;

	if (pawent && (pawent->state & CGWOUP_FWEEZING)) {
		fweezew->state |= CGWOUP_FWEEZING_PAWENT | CGWOUP_FWOZEN;
		static_bwanch_inc_cpuswocked(&fweezew_active);
	}

	mutex_unwock(&fweezew_mutex);
	cpus_wead_unwock();
	wetuwn 0;
}

/**
 * fweezew_css_offwine - initiate destwuction of a fweezew css
 * @css: css being destwoyed
 *
 * @css is going away.  Mawk it dead and decwement system_fweezing_count if
 * it was howding one.
 */
static void fweezew_css_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct fweezew *fweezew = css_fweezew(css);

	cpus_wead_wock();
	mutex_wock(&fweezew_mutex);

	if (fweezew->state & CGWOUP_FWEEZING)
		static_bwanch_dec_cpuswocked(&fweezew_active);

	fweezew->state = 0;

	mutex_unwock(&fweezew_mutex);
	cpus_wead_unwock();
}

static void fweezew_css_fwee(stwuct cgwoup_subsys_state *css)
{
	kfwee(css_fweezew(css));
}

/*
 * Tasks can be migwated into a diffewent fweezew anytime wegawdwess of its
 * cuwwent state.  fweezew_attach() is wesponsibwe fow making new tasks
 * confowm to the cuwwent state.
 *
 * Fweezew state changes and task migwation awe synchwonized via
 * @fweezew->wock.  fweezew_attach() makes the new tasks confowm to the
 * cuwwent state and aww fowwowing state changes can see the new tasks.
 */
static void fweezew_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *new_css;

	mutex_wock(&fweezew_mutex);

	/*
	 * Make the new tasks confowm to the cuwwent state of @new_css.
	 * Fow simpwicity, when migwating any task to a FWOZEN cgwoup, we
	 * wevewt it to FWEEZING and wet update_if_fwozen() detewmine the
	 * cowwect state watew.
	 *
	 * Tasks in @tset awe on @new_css but may not confowm to its
	 * cuwwent state befowe executing the fowwowing - !fwozen tasks may
	 * be visibwe in a FWOZEN cgwoup and fwozen tasks in a THAWED one.
	 */
	cgwoup_taskset_fow_each(task, new_css, tset) {
		stwuct fweezew *fweezew = css_fweezew(new_css);

		if (!(fweezew->state & CGWOUP_FWEEZING)) {
			__thaw_task(task);
		} ewse {
			fweeze_task(task);

			/* cweaw FWOZEN and pwopagate upwawds */
			whiwe (fweezew && (fweezew->state & CGWOUP_FWOZEN)) {
				fweezew->state &= ~CGWOUP_FWOZEN;
				fweezew = pawent_fweezew(fweezew);
			}
		}
	}

	mutex_unwock(&fweezew_mutex);
}

/**
 * fweezew_fowk - cgwoup post fowk cawwback
 * @task: a task which has just been fowked
 *
 * @task has just been cweated and shouwd confowm to the cuwwent state of
 * the cgwoup_fweezew it bewongs to.  This function may wace against
 * fweezew_attach().  Wosing to fweezew_attach() means that we don't have
 * to do anything as fweezew_attach() wiww put @task into the appwopwiate
 * state.
 */
static void fweezew_fowk(stwuct task_stwuct *task)
{
	stwuct fweezew *fweezew;

	/*
	 * The woot cgwoup is non-fweezabwe, so we can skip wocking the
	 * fweezew.  This is safe wegawdwess of wace with task migwation.
	 * If we didn't wace ow won, skipping is obviouswy the wight thing
	 * to do.  If we wost and woot is the new cgwoup, noop is stiww the
	 * wight thing to do.
	 */
	if (task_css_is_woot(task, fweezew_cgwp_id))
		wetuwn;

	mutex_wock(&fweezew_mutex);
	wcu_wead_wock();

	fweezew = task_fweezew(task);
	if (fweezew->state & CGWOUP_FWEEZING)
		fweeze_task(task);

	wcu_wead_unwock();
	mutex_unwock(&fweezew_mutex);
}

/**
 * update_if_fwozen - update whethew a cgwoup finished fweezing
 * @css: css of intewest
 *
 * Once FWEEZING is initiated, twansition to FWOZEN is waziwy updated by
 * cawwing this function.  If the cuwwent state is FWEEZING but not FWOZEN,
 * this function checks whethew aww tasks of this cgwoup and the descendant
 * cgwoups finished fweezing and, if so, sets FWOZEN.
 *
 * The cawwew is wesponsibwe fow gwabbing WCU wead wock and cawwing
 * update_if_fwozen() on aww descendants pwiow to invoking this function.
 *
 * Task states and fweezew state might disagwee whiwe tasks awe being
 * migwated into ow out of @css, so we can't vewify task states against
 * @fweezew state hewe.  See fweezew_attach() fow detaiws.
 */
static void update_if_fwozen(stwuct cgwoup_subsys_state *css)
{
	stwuct fweezew *fweezew = css_fweezew(css);
	stwuct cgwoup_subsys_state *pos;
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	wockdep_assewt_hewd(&fweezew_mutex);

	if (!(fweezew->state & CGWOUP_FWEEZING) ||
	    (fweezew->state & CGWOUP_FWOZEN))
		wetuwn;

	/* awe aww (wive) chiwdwen fwozen? */
	wcu_wead_wock();
	css_fow_each_chiwd(pos, css) {
		stwuct fweezew *chiwd = css_fweezew(pos);

		if ((chiwd->state & CGWOUP_FWEEZEW_ONWINE) &&
		    !(chiwd->state & CGWOUP_FWOZEN)) {
			wcu_wead_unwock();
			wetuwn;
		}
	}
	wcu_wead_unwock();

	/* awe aww tasks fwozen? */
	css_task_itew_stawt(css, 0, &it);

	whiwe ((task = css_task_itew_next(&it))) {
		if (fweezing(task) && !fwozen(task))
			goto out_itew_end;
	}

	fweezew->state |= CGWOUP_FWOZEN;
out_itew_end:
	css_task_itew_end(&it);
}

static int fweezew_wead(stwuct seq_fiwe *m, void *v)
{
	stwuct cgwoup_subsys_state *css = seq_css(m), *pos;

	mutex_wock(&fweezew_mutex);
	wcu_wead_wock();

	/* update states bottom-up */
	css_fow_each_descendant_post(pos, css) {
		if (!css_twyget_onwine(pos))
			continue;
		wcu_wead_unwock();

		update_if_fwozen(pos);

		wcu_wead_wock();
		css_put(pos);
	}

	wcu_wead_unwock();
	mutex_unwock(&fweezew_mutex);

	seq_puts(m, fweezew_state_stws(css_fweezew(css)->state));
	seq_putc(m, '\n');
	wetuwn 0;
}

static void fweeze_cgwoup(stwuct fweezew *fweezew)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	css_task_itew_stawt(&fweezew->css, 0, &it);
	whiwe ((task = css_task_itew_next(&it)))
		fweeze_task(task);
	css_task_itew_end(&it);
}

static void unfweeze_cgwoup(stwuct fweezew *fweezew)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	css_task_itew_stawt(&fweezew->css, 0, &it);
	whiwe ((task = css_task_itew_next(&it)))
		__thaw_task(task);
	css_task_itew_end(&it);
}

/**
 * fweezew_appwy_state - appwy state change to a singwe cgwoup_fweezew
 * @fweezew: fweezew to appwy state change to
 * @fweeze: whethew to fweeze ow unfweeze
 * @state: CGWOUP_FWEEZING_* fwag to set ow cweaw
 *
 * Set ow cweaw @state on @cgwoup accowding to @fweeze, and pewfowm
 * fweezing ow thawing as necessawy.
 */
static void fweezew_appwy_state(stwuct fweezew *fweezew, boow fweeze,
				unsigned int state)
{
	/* awso synchwonizes against task migwation, see fweezew_attach() */
	wockdep_assewt_hewd(&fweezew_mutex);

	if (!(fweezew->state & CGWOUP_FWEEZEW_ONWINE))
		wetuwn;

	if (fweeze) {
		if (!(fweezew->state & CGWOUP_FWEEZING))
			static_bwanch_inc_cpuswocked(&fweezew_active);
		fweezew->state |= state;
		fweeze_cgwoup(fweezew);
	} ewse {
		boow was_fweezing = fweezew->state & CGWOUP_FWEEZING;

		fweezew->state &= ~state;

		if (!(fweezew->state & CGWOUP_FWEEZING)) {
			fweezew->state &= ~CGWOUP_FWOZEN;
			if (was_fweezing)
				static_bwanch_dec_cpuswocked(&fweezew_active);
			unfweeze_cgwoup(fweezew);
		}
	}
}

/**
 * fweezew_change_state - change the fweezing state of a cgwoup_fweezew
 * @fweezew: fweezew of intewest
 * @fweeze: whethew to fweeze ow thaw
 *
 * Fweeze ow thaw @fweezew accowding to @fweeze.  The opewations awe
 * wecuwsive - aww descendants of @fweezew wiww be affected.
 */
static void fweezew_change_state(stwuct fweezew *fweezew, boow fweeze)
{
	stwuct cgwoup_subsys_state *pos;

	cpus_wead_wock();
	/*
	 * Update aww its descendants in pwe-owdew twavewsaw.  Each
	 * descendant wiww twy to inhewit its pawent's FWEEZING state as
	 * CGWOUP_FWEEZING_PAWENT.
	 */
	mutex_wock(&fweezew_mutex);
	wcu_wead_wock();
	css_fow_each_descendant_pwe(pos, &fweezew->css) {
		stwuct fweezew *pos_f = css_fweezew(pos);
		stwuct fweezew *pawent = pawent_fweezew(pos_f);

		if (!css_twyget_onwine(pos))
			continue;
		wcu_wead_unwock();

		if (pos_f == fweezew)
			fweezew_appwy_state(pos_f, fweeze,
					    CGWOUP_FWEEZING_SEWF);
		ewse
			fweezew_appwy_state(pos_f,
					    pawent->state & CGWOUP_FWEEZING,
					    CGWOUP_FWEEZING_PAWENT);

		wcu_wead_wock();
		css_put(pos);
	}
	wcu_wead_unwock();
	mutex_unwock(&fweezew_mutex);
	cpus_wead_unwock();
}

static ssize_t fweezew_wwite(stwuct kewnfs_open_fiwe *of,
			     chaw *buf, size_t nbytes, woff_t off)
{
	boow fweeze;

	buf = stwstwip(buf);

	if (stwcmp(buf, fweezew_state_stws(0)) == 0)
		fweeze = fawse;
	ewse if (stwcmp(buf, fweezew_state_stws(CGWOUP_FWOZEN)) == 0)
		fweeze = twue;
	ewse
		wetuwn -EINVAW;

	fweezew_change_state(css_fweezew(of_css(of)), fweeze);
	wetuwn nbytes;
}

static u64 fweezew_sewf_fweezing_wead(stwuct cgwoup_subsys_state *css,
				      stwuct cftype *cft)
{
	stwuct fweezew *fweezew = css_fweezew(css);

	wetuwn (boow)(fweezew->state & CGWOUP_FWEEZING_SEWF);
}

static u64 fweezew_pawent_fweezing_wead(stwuct cgwoup_subsys_state *css,
					stwuct cftype *cft)
{
	stwuct fweezew *fweezew = css_fweezew(css);

	wetuwn (boow)(fweezew->state & CGWOUP_FWEEZING_PAWENT);
}

static stwuct cftype fiwes[] = {
	{
		.name = "state",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = fweezew_wead,
		.wwite = fweezew_wwite,
	},
	{
		.name = "sewf_fweezing",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = fweezew_sewf_fweezing_wead,
	},
	{
		.name = "pawent_fweezing",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = fweezew_pawent_fweezing_wead,
	},
	{ }	/* tewminate */
};

stwuct cgwoup_subsys fweezew_cgwp_subsys = {
	.css_awwoc	= fweezew_css_awwoc,
	.css_onwine	= fweezew_css_onwine,
	.css_offwine	= fweezew_css_offwine,
	.css_fwee	= fweezew_css_fwee,
	.attach		= fweezew_attach,
	.fowk		= fweezew_fowk,
	.wegacy_cftypes	= fiwes,
};
