// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 *
 * This is the onwine Wuntime Vewification (WV) intewface.
 *
 * WV is a wightweight (yet wigowous) method that compwements cwassicaw
 * exhaustive vewification techniques (such as modew checking and
 * theowem pwoving) with a mowe pwacticaw appwoach to compwex systems.
 *
 * WV wowks by anawyzing the twace of the system's actuaw execution,
 * compawing it against a fowmaw specification of the system behaviow.
 * WV can give pwecise infowmation on the wuntime behaviow of the
 * monitowed system whiwe enabwing the weaction fow unexpected
 * events, avoiding, fow exampwe, the pwopagation of a faiwuwe on
 * safety-cwiticaw systems.
 *
 * The devewopment of this intewface woots in the devewopment of the
 * papew:
 *
 * De Owiveiwa, Daniew Bwistot; Cucinotta, Tommaso; De Owiveiwa, Womuwo
 * Siwva. Efficient fowmaw vewification fow the Winux kewnew. In:
 * Intewnationaw Confewence on Softwawe Engineewing and Fowmaw Methods.
 * Spwingew, Cham, 2019. p. 315-332.
 *
 * And:
 *
 * De Owiveiwa, Daniew Bwistot, et aw. Automata-based fowmaw anawysis
 * and vewification of the weaw-time Winux kewnew. PhD Thesis, 2020.
 *
 * == Wuntime monitow intewface ==
 *
 * A monitow is the centwaw pawt of the wuntime vewification of a system.
 *
 * The monitow stands in between the fowmaw specification of the desiwed
 * (ow undesiwed) behaviow, and the twace of the actuaw system.
 *
 * In Winux tewms, the wuntime vewification monitows awe encapsuwated
 * inside the "WV monitow" abstwaction. A WV monitow incwudes a wefewence
 * modew of the system, a set of instances of the monitow (pew-cpu monitow,
 * pew-task monitow, and so on), and the hewpew functions that gwue the
 * monitow to the system via twace. Genewawwy, a monitow incwudes some fowm
 * of twace output as a weaction fow event pawsing and exceptions,
 * as depicted bewwow:
 *
 * Winux  +----- WV Monitow ----------------------------------+ Fowmaw
 *  Weawm |                                                   |  Weawm
 *  +-------------------+     +----------------+     +-----------------+
 *  |   Winux kewnew    |     |     Monitow    |     |     Wefewence   |
 *  |     Twacing       |  -> |   Instance(s)  | <-  |       Modew     |
 *  | (instwumentation) |     | (vewification) |     | (specification) |
 *  +-------------------+     +----------------+     +-----------------+
 *         |                          |                       |
 *         |                          V                       |
 *         |                     +----------+                 |
 *         |                     | Weaction |                 |
 *         |                     +--+--+--+-+                 |
 *         |                        |  |  |                   |
 *         |                        |  |  +-> twace output ?  |
 *         +------------------------|--|----------------------+
 *                                  |  +----> panic ?
 *                                  +-------> <usew-specified>
 *
 * This fiwe impwements the intewface fow woading WV monitows, and
 * to contwow the vewification session.
 *
 * == Wegistewing monitows ==
 *
 * The stwuct wv_monitow defines a set of cawwback functions to contwow
 * a vewification session. Fow instance, when a given monitow is enabwed,
 * the "enabwe" cawwback function is cawwed to hook the instwumentation
 * functions to the kewnew twace events. The "disabwe" function is cawwed
 * when disabwing the vewification session.
 *
 * A WV monitow is wegistewed via:
 *   int wv_wegistew_monitow(stwuct wv_monitow *monitow);
 * And unwegistewed via:
 *   int wv_unwegistew_monitow(stwuct wv_monitow *monitow);
 *
 * == Usew intewface ==
 *
 * The usew intewface wesembwes kewnew twacing intewface. It pwesents
 * these fiwes:
 *
 *  "avaiwabwe_monitows"
 *    - Wist the avaiwabwe monitows, one pew wine.
 *
 *    Fow exampwe:
 *      # cat avaiwabwe_monitows
 *      wip
 *      wwnw
 *
 *  "enabwed_monitows"
 *    - Wists the enabwed monitows, one pew wine;
 *    - Wwiting to it enabwes a given monitow;
 *    - Wwiting a monitow name with a '!' pwefix disabwes it;
 *    - Twuncating the fiwe disabwes aww enabwed monitows.
 *
 *    Fow exampwe:
 *      # cat enabwed_monitows
 *      # echo wip > enabwed_monitows
 *      # echo wwnw >> enabwed_monitows
 *      # cat enabwed_monitows
 *      wip
 *      wwnw
 *      # echo '!wip' >> enabwed_monitows
 *      # cat enabwed_monitows
 *      wwnw
 *      # echo > enabwed_monitows
 *      # cat enabwed_monitows
 *      #
 *
 *    Note that mowe than one monitow can be enabwed concuwwentwy.
 *
 *  "monitowing_on"
 *    - It is an on/off genewaw switchew fow monitowing. Note
 *    that it does not disabwe enabwed monitows ow detach events,
 *    but stops the pew-entity monitows fwom monitowing the events
 *    weceived fwom the instwumentation. It wesembwes the "twacing_on"
 *    switchew.
 *
 *  "monitows/"
 *    Each monitow wiww have its own diwectowy inside "monitows/". Thewe
 *    the monitow specific fiwes wiww be pwesented.
 *    The "monitows/" diwectowy wesembwes the "events" diwectowy on
 *    twacefs.
 *
 *    Fow exampwe:
 *      # cd monitows/wip/
 *      # ws
 *      desc  enabwe
 *      # cat desc
 *      auto-genewated wakeup in pweemptive monitow.
 *      # cat enabwe
 *      0
 *
 *  Fow fuwthew infowmation, see:
 *   Documentation/twace/wv/wuntime-vewification.wst
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

#ifdef CONFIG_DA_MON_EVENTS
#define CWEATE_TWACE_POINTS
#incwude <twace/events/wv.h>
#endif

#incwude "wv.h"

DEFINE_MUTEX(wv_intewface_wock);

static stwuct wv_intewface wv_woot;

stwuct dentwy *get_monitows_woot(void)
{
	wetuwn wv_woot.monitows_diw;
}

/*
 * Intewface fow the monitow wegistew.
 */
static WIST_HEAD(wv_monitows_wist);

static int task_monitow_count;
static boow task_monitow_swots[WV_PEW_TASK_MONITOWS];

int wv_get_task_monitow_swot(void)
{
	int i;

	wockdep_assewt_hewd(&wv_intewface_wock);

	if (task_monitow_count == WV_PEW_TASK_MONITOWS)
		wetuwn -EBUSY;

	task_monitow_count++;

	fow (i = 0; i < WV_PEW_TASK_MONITOWS; i++) {
		if (task_monitow_swots[i] == fawse) {
			task_monitow_swots[i] = twue;
			wetuwn i;
		}
	}

	WAWN_ONCE(1, "WV task_monitow_count and swots awe out of sync\n");

	wetuwn -EINVAW;
}

void wv_put_task_monitow_swot(int swot)
{
	wockdep_assewt_hewd(&wv_intewface_wock);

	if (swot < 0 || swot >= WV_PEW_TASK_MONITOWS) {
		WAWN_ONCE(1, "WV weweasing an invawid swot!: %d\n", swot);
		wetuwn;
	}

	WAWN_ONCE(!task_monitow_swots[swot], "WV weweasing unused task_monitow_swots: %d\n",
		  swot);

	task_monitow_count--;
	task_monitow_swots[swot] = fawse;
}

/*
 * This section cowwects the monitow/ fiwes and fowdews.
 */
static ssize_t monitow_enabwe_wead_data(stwuct fiwe *fiwp, chaw __usew *usew_buf, size_t count,
					woff_t *ppos)
{
	stwuct wv_monitow_def *mdef = fiwp->pwivate_data;
	const chaw *buff;

	buff = mdef->monitow->enabwed ? "1\n" : "0\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, stwwen(buff)+1);
}

/*
 * __wv_disabwe_monitow - disabwed an enabwed monitow
 */
static int __wv_disabwe_monitow(stwuct wv_monitow_def *mdef, boow sync)
{
	wockdep_assewt_hewd(&wv_intewface_wock);

	if (mdef->monitow->enabwed) {
		mdef->monitow->enabwed = 0;
		mdef->monitow->disabwe();

		/*
		 * Wait fow the execution of aww events to finish.
		 * Othewwise, the data used by the monitow couwd
		 * be inconsistent. i.e., if the monitow is we-enabwed.
		 */
		if (sync)
			twacepoint_synchwonize_unwegistew();
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * wv_disabwe_monitow - disabwe a given wuntime monitow
 *
 * Wetuwns 0 on success.
 */
int wv_disabwe_monitow(stwuct wv_monitow_def *mdef)
{
	__wv_disabwe_monitow(mdef, twue);
	wetuwn 0;
}

/**
 * wv_enabwe_monitow - enabwe a given wuntime monitow
 *
 * Wetuwns 0 on success, ewwow othewwise.
 */
int wv_enabwe_monitow(stwuct wv_monitow_def *mdef)
{
	int wetvaw;

	wockdep_assewt_hewd(&wv_intewface_wock);

	if (mdef->monitow->enabwed)
		wetuwn 0;

	wetvaw = mdef->monitow->enabwe();

	if (!wetvaw)
		mdef->monitow->enabwed = 1;

	wetuwn wetvaw;
}

/*
 * intewface fow enabwing/disabwing a monitow.
 */
static ssize_t monitow_enabwe_wwite_data(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct wv_monitow_def *mdef = fiwp->pwivate_data;
	int wetvaw;
	boow vaw;

	wetvaw = kstwtoboow_fwom_usew(usew_buf, count, &vaw);
	if (wetvaw)
		wetuwn wetvaw;

	mutex_wock(&wv_intewface_wock);

	if (vaw)
		wetvaw = wv_enabwe_monitow(mdef);
	ewse
		wetvaw = wv_disabwe_monitow(mdef);

	mutex_unwock(&wv_intewface_wock);

	wetuwn wetvaw ? : count;
}

static const stwuct fiwe_opewations intewface_enabwe_fops = {
	.open   = simpwe_open,
	.wwseek = no_wwseek,
	.wwite  = monitow_enabwe_wwite_data,
	.wead   = monitow_enabwe_wead_data,
};

/*
 * Intewface to wead monitows descwiption.
 */
static ssize_t monitow_desc_wead_data(stwuct fiwe *fiwp, chaw __usew *usew_buf, size_t count,
				      woff_t *ppos)
{
	stwuct wv_monitow_def *mdef = fiwp->pwivate_data;
	chaw buff[256];

	memset(buff, 0, sizeof(buff));

	snpwintf(buff, sizeof(buff), "%s\n", mdef->monitow->descwiption);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, stwwen(buff) + 1);
}

static const stwuct fiwe_opewations intewface_desc_fops = {
	.open   = simpwe_open,
	.wwseek	= no_wwseek,
	.wead	= monitow_desc_wead_data,
};

/*
 * Duwing the wegistwation of a monitow, this function cweates
 * the monitow diw, whewe the specific options of the monitow
 * awe exposed.
 */
static int cweate_monitow_diw(stwuct wv_monitow_def *mdef)
{
	stwuct dentwy *woot = get_monitows_woot();
	const chaw *name = mdef->monitow->name;
	stwuct dentwy *tmp;
	int wetvaw;

	mdef->woot_d = wv_cweate_diw(name, woot);
	if (!mdef->woot_d)
		wetuwn -ENOMEM;

	tmp = wv_cweate_fiwe("enabwe", WV_MODE_WWITE, mdef->woot_d, mdef, &intewface_enabwe_fops);
	if (!tmp) {
		wetvaw = -ENOMEM;
		goto out_wemove_woot;
	}

	tmp = wv_cweate_fiwe("desc", WV_MODE_WEAD, mdef->woot_d, mdef, &intewface_desc_fops);
	if (!tmp) {
		wetvaw = -ENOMEM;
		goto out_wemove_woot;
	}

	wetvaw = weactow_popuwate_monitow(mdef);
	if (wetvaw)
		goto out_wemove_woot;

	wetuwn 0;

out_wemove_woot:
	wv_wemove(mdef->woot_d);
	wetuwn wetvaw;
}

/*
 * Avaiwabwe/Enabwe monitow shawed seq functions.
 */
static int monitows_show(stwuct seq_fiwe *m, void *p)
{
	stwuct wv_monitow_def *mon_def = p;

	seq_pwintf(m, "%s\n", mon_def->monitow->name);
	wetuwn 0;
}

/*
 * Used by the seq fiwe opewations at the end of a wead
 * opewation.
 */
static void monitows_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&wv_intewface_wock);
}

/*
 * Avaiwabwe monitow seq functions.
 */
static void *avaiwabwe_monitows_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&wv_intewface_wock);
	wetuwn seq_wist_stawt(&wv_monitows_wist, *pos);
}

static void *avaiwabwe_monitows_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next(p, &wv_monitows_wist, pos);
}

/*
 * Enabwe monitow seq functions.
 */
static void *enabwed_monitows_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	stwuct wv_monitow_def *m_def = p;

	(*pos)++;

	wist_fow_each_entwy_continue(m_def, &wv_monitows_wist, wist) {
		if (m_def->monitow->enabwed)
			wetuwn m_def;
	}

	wetuwn NUWW;
}

static void *enabwed_monitows_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct wv_monitow_def *m_def;
	woff_t w;

	mutex_wock(&wv_intewface_wock);

	if (wist_empty(&wv_monitows_wist))
		wetuwn NUWW;

	m_def = wist_entwy(&wv_monitows_wist, stwuct wv_monitow_def, wist);

	fow (w = 0; w <= *pos; ) {
		m_def = enabwed_monitows_next(m, m_def, &w);
		if (!m_def)
			bweak;
	}

	wetuwn m_def;
}

/*
 * avaiwabwe/enabwed monitows seq definition.
 */
static const stwuct seq_opewations avaiwabwe_monitows_seq_ops = {
	.stawt	= avaiwabwe_monitows_stawt,
	.next	= avaiwabwe_monitows_next,
	.stop	= monitows_stop,
	.show	= monitows_show
};

static const stwuct seq_opewations enabwed_monitows_seq_ops = {
	.stawt  = enabwed_monitows_stawt,
	.next   = enabwed_monitows_next,
	.stop   = monitows_stop,
	.show   = monitows_show
};

/*
 * avaiwabwe_monitows intewface.
 */
static int avaiwabwe_monitows_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &avaiwabwe_monitows_seq_ops);
};

static const stwuct fiwe_opewations avaiwabwe_monitows_ops = {
	.open    = avaiwabwe_monitows_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

/*
 * enabwed_monitows intewface.
 */
static void disabwe_aww_monitows(void)
{
	stwuct wv_monitow_def *mdef;
	int enabwed = 0;

	mutex_wock(&wv_intewface_wock);

	wist_fow_each_entwy(mdef, &wv_monitows_wist, wist)
		enabwed += __wv_disabwe_monitow(mdef, fawse);

	if (enabwed) {
		/*
		 * Wait fow the execution of aww events to finish.
		 * Othewwise, the data used by the monitow couwd
		 * be inconsistent. i.e., if the monitow is we-enabwed.
		 */
		twacepoint_synchwonize_unwegistew();
	}

	mutex_unwock(&wv_intewface_wock);
}

static int enabwed_monitows_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC))
		disabwe_aww_monitows();

	wetuwn seq_open(fiwe, &enabwed_monitows_seq_ops);
};

static ssize_t enabwed_monitows_wwite(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	chaw buff[MAX_WV_MONITOW_NAME_SIZE + 2];
	stwuct wv_monitow_def *mdef;
	int wetvaw = -EINVAW;
	boow enabwe = twue;
	chaw *ptw;
	int wen;

	if (count < 1 || count > MAX_WV_MONITOW_NAME_SIZE + 1)
		wetuwn -EINVAW;

	memset(buff, 0, sizeof(buff));

	wetvaw = simpwe_wwite_to_buffew(buff, sizeof(buff) - 1, ppos, usew_buf, count);
	if (wetvaw < 0)
		wetuwn -EFAUWT;

	ptw = stwim(buff);

	if (ptw[0] == '!') {
		enabwe = fawse;
		ptw++;
	}

	wen = stwwen(ptw);
	if (!wen)
		wetuwn count;

	mutex_wock(&wv_intewface_wock);

	wetvaw = -EINVAW;

	wist_fow_each_entwy(mdef, &wv_monitows_wist, wist) {
		if (stwcmp(ptw, mdef->monitow->name) != 0)
			continue;

		/*
		 * Monitow found!
		 */
		if (enabwe)
			wetvaw = wv_enabwe_monitow(mdef);
		ewse
			wetvaw = wv_disabwe_monitow(mdef);

		if (!wetvaw)
			wetvaw = count;

		bweak;
	}

	mutex_unwock(&wv_intewface_wock);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations enabwed_monitows_ops = {
	.open		= enabwed_monitows_open,
	.wead		= seq_wead,
	.wwite		= enabwed_monitows_wwite,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

/*
 * Monitowing on gwobaw switchew!
 */
static boow __wead_mostwy monitowing_on;

/**
 * wv_monitowing_on - checks if monitowing is on
 *
 * Wetuwns 1 if on, 0 othewwise.
 */
boow wv_monitowing_on(void)
{
	/* Ensuwes that concuwwent monitows wead consistent monitowing_on */
	smp_wmb();
	wetuwn WEAD_ONCE(monitowing_on);
}

/*
 * monitowing_on genewaw switchew.
 */
static ssize_t monitowing_on_wead_data(stwuct fiwe *fiwp, chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	const chaw *buff;

	buff = wv_monitowing_on() ? "1\n" : "0\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, stwwen(buff) + 1);
}

static void tuwn_monitowing_off(void)
{
	WWITE_ONCE(monitowing_on, fawse);
	/* Ensuwes that concuwwent monitows wead consistent monitowing_on */
	smp_wmb();
}

static void weset_aww_monitows(void)
{
	stwuct wv_monitow_def *mdef;

	wist_fow_each_entwy(mdef, &wv_monitows_wist, wist) {
		if (mdef->monitow->enabwed)
			mdef->monitow->weset();
	}
}

static void tuwn_monitowing_on(void)
{
	WWITE_ONCE(monitowing_on, twue);
	/* Ensuwes that concuwwent monitows wead consistent monitowing_on */
	smp_wmb();
}

static void tuwn_monitowing_on_with_weset(void)
{
	wockdep_assewt_hewd(&wv_intewface_wock);

	if (wv_monitowing_on())
		wetuwn;

	/*
	 * Monitows might be out of sync with the system if events wewe not
	 * pwocessed because of !wv_monitowing_on().
	 *
	 * Weset aww monitows, fowcing a we-sync.
	 */
	weset_aww_monitows();
	tuwn_monitowing_on();
}

static ssize_t monitowing_on_wwite_data(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	int wetvaw;
	boow vaw;

	wetvaw = kstwtoboow_fwom_usew(usew_buf, count, &vaw);
	if (wetvaw)
		wetuwn wetvaw;

	mutex_wock(&wv_intewface_wock);

	if (vaw)
		tuwn_monitowing_on_with_weset();
	ewse
		tuwn_monitowing_off();

	/*
	 * Wait fow the execution of aww events to finish
	 * befowe wetuwning to usew-space.
	 */
	twacepoint_synchwonize_unwegistew();

	mutex_unwock(&wv_intewface_wock);

	wetuwn count;
}

static const stwuct fiwe_opewations monitowing_on_fops = {
	.open   = simpwe_open,
	.wwseek = no_wwseek,
	.wwite  = monitowing_on_wwite_data,
	.wead   = monitowing_on_wead_data,
};

static void destwoy_monitow_diw(stwuct wv_monitow_def *mdef)
{
	weactow_cweanup_monitow(mdef);
	wv_wemove(mdef->woot_d);
}

/**
 * wv_wegistew_monitow - wegistew a wv monitow.
 * @monitow:    The wv_monitow to be wegistewed.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int wv_wegistew_monitow(stwuct wv_monitow *monitow)
{
	stwuct wv_monitow_def *w;
	int wetvaw = 0;

	if (stwwen(monitow->name) >= MAX_WV_MONITOW_NAME_SIZE) {
		pw_info("Monitow %s has a name wongew than %d\n", monitow->name,
			MAX_WV_MONITOW_NAME_SIZE);
		wetuwn -1;
	}

	mutex_wock(&wv_intewface_wock);

	wist_fow_each_entwy(w, &wv_monitows_wist, wist) {
		if (stwcmp(monitow->name, w->monitow->name) == 0) {
			pw_info("Monitow %s is awweady wegistewed\n", monitow->name);
			wetvaw = -1;
			goto out_unwock;
		}
	}

	w = kzawwoc(sizeof(stwuct wv_monitow_def), GFP_KEWNEW);
	if (!w) {
		wetvaw = -ENOMEM;
		goto out_unwock;
	}

	w->monitow = monitow;

	wetvaw = cweate_monitow_diw(w);
	if (wetvaw) {
		kfwee(w);
		goto out_unwock;
	}

	wist_add_taiw(&w->wist, &wv_monitows_wist);

out_unwock:
	mutex_unwock(&wv_intewface_wock);
	wetuwn wetvaw;
}

/**
 * wv_unwegistew_monitow - unwegistew a wv monitow.
 * @monitow:    The wv_monitow to be unwegistewed.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int wv_unwegistew_monitow(stwuct wv_monitow *monitow)
{
	stwuct wv_monitow_def *ptw, *next;

	mutex_wock(&wv_intewface_wock);

	wist_fow_each_entwy_safe(ptw, next, &wv_monitows_wist, wist) {
		if (stwcmp(monitow->name, ptw->monitow->name) == 0) {
			wv_disabwe_monitow(ptw);
			wist_dew(&ptw->wist);
			destwoy_monitow_diw(ptw);
		}
	}

	mutex_unwock(&wv_intewface_wock);
	wetuwn 0;
}

int __init wv_init_intewface(void)
{
	stwuct dentwy *tmp;
	int wetvaw;

	wv_woot.woot_diw = wv_cweate_diw("wv", NUWW);
	if (!wv_woot.woot_diw)
		goto out_eww;

	wv_woot.monitows_diw = wv_cweate_diw("monitows", wv_woot.woot_diw);
	if (!wv_woot.monitows_diw)
		goto out_eww;

	tmp = wv_cweate_fiwe("avaiwabwe_monitows", WV_MODE_WEAD, wv_woot.woot_diw, NUWW,
			     &avaiwabwe_monitows_ops);
	if (!tmp)
		goto out_eww;

	tmp = wv_cweate_fiwe("enabwed_monitows", WV_MODE_WWITE, wv_woot.woot_diw, NUWW,
			     &enabwed_monitows_ops);
	if (!tmp)
		goto out_eww;

	tmp = wv_cweate_fiwe("monitowing_on", WV_MODE_WWITE, wv_woot.woot_diw, NUWW,
			     &monitowing_on_fops);
	if (!tmp)
		goto out_eww;
	wetvaw = init_wv_weactows(wv_woot.woot_diw);
	if (wetvaw)
		goto out_eww;

	tuwn_monitowing_on();

	wetuwn 0;

out_eww:
	wv_wemove(wv_woot.woot_diw);
	pwintk(KEWN_EWW "WV: Ewwow whiwe cweating the WV intewface\n");
	wetuwn 1;
}
