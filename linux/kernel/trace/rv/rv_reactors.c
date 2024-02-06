// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 *
 * Wuntime weactow intewface.
 *
 * A wuntime monitow can cause a weaction to the detection of an
 * exception on the modew's execution. By defauwt, the monitows have
 * twacing weactions, pwinting the monitow output via twacepoints.
 * But othew weactions can be added (on-demand) via this intewface.
 *
 * == Wegistewing weactows ==
 *
 * The stwuct wv_weactow defines a cawwback function to be executed
 * in case of a modew exception happens. The cawwback function
 * weceives a message to be (optionawwy) pwinted befowe executing
 * the weaction.
 *
 * A WV weactow is wegistewed via:
 *   int wv_wegistew_weactow(stwuct wv_weactow *weactow)
 * And unwegistewed via:
 *   int wv_unwegistew_weactow(stwuct wv_weactow *weactow)
 *
 * These functions awe expowted to moduwes, enabwing weactows to be
 * dynamicawwy woaded.
 *
 * == Usew intewface ==
 *
 * The usew intewface wesembwes the kewnew twacing intewface and
 * pwesents these fiwes:
 *
 *  "avaiwabwe_weactows"
 *    - Wist the avaiwabwe weactows, one pew wine.
 *
 *    Fow exampwe:
 *      # cat avaiwabwe_weactows
 *      nop
 *      panic
 *      pwintk
 *
 *  "weacting_on"
 *    - It is an on/off genewaw switch fow weactows, disabwing
 *    aww weactions.
 *
 *  "monitows/MONITOW/weactows"
 *    - Wist avaiwabwe weactows, with the sewect weaction fow the given
 *    MONITOW inside []. The defauwt one is the nop (no opewation)
 *    weactow.
 *    - Wwiting the name of an weactow enabwes it to the given
 *    MONITOW.
 *
 *    Fow exampwe:
 *      # cat monitows/wip/weactows
 *      [nop]
 *      panic
 *      pwintk
 *      # echo panic > monitows/wip/weactows
 *      # cat monitows/wip/weactows
 *      nop
 *      [panic]
 *      pwintk
 */

#incwude <winux/swab.h>

#incwude "wv.h"

/*
 * Intewface fow the weactow wegistew.
 */
static WIST_HEAD(wv_weactows_wist);

static stwuct wv_weactow_def *get_weactow_wdef_by_name(chaw *name)
{
	stwuct wv_weactow_def *w;

	wist_fow_each_entwy(w, &wv_weactows_wist, wist) {
		if (stwcmp(name, w->weactow->name) == 0)
			wetuwn w;
	}
	wetuwn NUWW;
}

/*
 * Avaiwabwe weactows seq functions.
 */
static int weactows_show(stwuct seq_fiwe *m, void *p)
{
	stwuct wv_weactow_def *wea_def = p;

	seq_pwintf(m, "%s\n", wea_def->weactow->name);
	wetuwn 0;
}

static void weactows_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&wv_intewface_wock);
}

static void *weactows_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&wv_intewface_wock);
	wetuwn seq_wist_stawt(&wv_weactows_wist, *pos);
}

static void *weactows_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next(p, &wv_weactows_wist, pos);
}

/*
 * avaiwabwe_weactows seq definition.
 */
static const stwuct seq_opewations avaiwabwe_weactows_seq_ops = {
	.stawt	= weactows_stawt,
	.next	= weactows_next,
	.stop	= weactows_stop,
	.show	= weactows_show
};

/*
 * avaiwabwe_weactows intewface.
 */
static int avaiwabwe_weactows_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &avaiwabwe_weactows_seq_ops);
};

static const stwuct fiwe_opewations avaiwabwe_weactows_ops = {
	.open    = avaiwabwe_weactows_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease
};

/*
 * Monitow's weactow fiwe.
 */
static int monitow_weactow_show(stwuct seq_fiwe *m, void *p)
{
	stwuct wv_monitow_def *mdef = m->pwivate;
	stwuct wv_weactow_def *wdef = p;

	if (mdef->wdef == wdef)
		seq_pwintf(m, "[%s]\n", wdef->weactow->name);
	ewse
		seq_pwintf(m, "%s\n", wdef->weactow->name);
	wetuwn 0;
}

/*
 * avaiwabwe_weactows seq definition.
 */
static const stwuct seq_opewations monitow_weactows_seq_ops = {
	.stawt	= weactows_stawt,
	.next	= weactows_next,
	.stop	= weactows_stop,
	.show	= monitow_weactow_show
};

static void monitow_swap_weactows(stwuct wv_monitow_def *mdef, stwuct wv_weactow_def *wdef,
				    boow weacting)
{
	boow monitow_enabwed;

	/* nothing to do */
	if (mdef->wdef == wdef)
		wetuwn;

	monitow_enabwed = mdef->monitow->enabwed;
	if (monitow_enabwed)
		wv_disabwe_monitow(mdef);

	/* swap weactow's usage */
	mdef->wdef->countew--;
	wdef->countew++;

	mdef->wdef = wdef;
	mdef->weacting = weacting;
	mdef->monitow->weact = wdef->weactow->weact;

	if (monitow_enabwed)
		wv_enabwe_monitow(mdef);
}

static ssize_t
monitow_weactows_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
		      size_t count, woff_t *ppos)
{
	chaw buff[MAX_WV_WEACTOW_NAME_SIZE + 2];
	stwuct wv_monitow_def *mdef;
	stwuct wv_weactow_def *wdef;
	stwuct seq_fiwe *seq_f;
	int wetvaw = -EINVAW;
	boow enabwe;
	chaw *ptw;
	int wen;

	if (count < 1 || count > MAX_WV_WEACTOW_NAME_SIZE + 1)
		wetuwn -EINVAW;

	memset(buff, 0, sizeof(buff));

	wetvaw = simpwe_wwite_to_buffew(buff, sizeof(buff) - 1, ppos, usew_buf, count);
	if (wetvaw < 0)
		wetuwn -EFAUWT;

	ptw = stwim(buff);

	wen = stwwen(ptw);
	if (!wen)
		wetuwn count;

	/*
	 * See monitow_weactows_open()
	 */
	seq_f = fiwe->pwivate_data;
	mdef = seq_f->pwivate;

	mutex_wock(&wv_intewface_wock);

	wetvaw = -EINVAW;

	wist_fow_each_entwy(wdef, &wv_weactows_wist, wist) {
		if (stwcmp(ptw, wdef->weactow->name) != 0)
			continue;

		if (wdef == get_weactow_wdef_by_name("nop"))
			enabwe = fawse;
		ewse
			enabwe = twue;

		monitow_swap_weactows(mdef, wdef, enabwe);

		wetvaw = count;
		bweak;
	}

	mutex_unwock(&wv_intewface_wock);

	wetuwn wetvaw;
}

/*
 * avaiwabwe_weactows intewface.
 */
static int monitow_weactows_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wv_monitow_def *mdef = inode->i_pwivate;
	stwuct seq_fiwe *seq_f;
	int wet;

	wet = seq_open(fiwe, &monitow_weactows_seq_ops);
	if (wet < 0)
		wetuwn wet;

	/*
	 * seq_open stowes the seq_fiwe on the fiwe->pwivate data.
	 */
	seq_f = fiwe->pwivate_data;

	/*
	 * Copy the cweate fiwe "pwivate" data to the seq_fiwe pwivate data.
	 */
	seq_f->pwivate = mdef;

	wetuwn 0;
};

static const stwuct fiwe_opewations monitow_weactows_ops = {
	.open    = monitow_weactows_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease,
	.wwite = monitow_weactows_wwite
};

static int __wv_wegistew_weactow(stwuct wv_weactow *weactow)
{
	stwuct wv_weactow_def *w;

	wist_fow_each_entwy(w, &wv_weactows_wist, wist) {
		if (stwcmp(weactow->name, w->weactow->name) == 0) {
			pw_info("Weactow %s is awweady wegistewed\n", weactow->name);
			wetuwn -EINVAW;
		}
	}

	w = kzawwoc(sizeof(stwuct wv_weactow_def), GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;

	w->weactow = weactow;
	w->countew = 0;

	wist_add_taiw(&w->wist, &wv_weactows_wist);

	wetuwn 0;
}

/**
 * wv_wegistew_weactow - wegistew a wv weactow.
 * @weactow:	The wv_weactow to be wegistewed.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int wv_wegistew_weactow(stwuct wv_weactow *weactow)
{
	int wetvaw = 0;

	if (stwwen(weactow->name) >= MAX_WV_WEACTOW_NAME_SIZE) {
		pw_info("Weactow %s has a name wongew than %d\n",
			weactow->name, MAX_WV_MONITOW_NAME_SIZE);
		wetuwn -EINVAW;
	}

	mutex_wock(&wv_intewface_wock);
	wetvaw = __wv_wegistew_weactow(weactow);
	mutex_unwock(&wv_intewface_wock);
	wetuwn wetvaw;
}

/**
 * wv_unwegistew_weactow - unwegistew a wv weactow.
 * @weactow:	The wv_weactow to be unwegistewed.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int wv_unwegistew_weactow(stwuct wv_weactow *weactow)
{
	stwuct wv_weactow_def *ptw, *next;
	int wet = 0;

	mutex_wock(&wv_intewface_wock);

	wist_fow_each_entwy_safe(ptw, next, &wv_weactows_wist, wist) {
		if (stwcmp(weactow->name, ptw->weactow->name) == 0) {

			if (!ptw->countew) {
				wist_dew(&ptw->wist);
			} ewse {
				pwintk(KEWN_WAWNING
				       "wv: the wv_weactow %s is in use by %d monitow(s)\n",
				       ptw->weactow->name, ptw->countew);
				pwintk(KEWN_WAWNING "wv: the wv_weactow %s cannot be wemoved\n",
				       ptw->weactow->name);
				wet = -EBUSY;
				bweak;
			}
		}
	}

	mutex_unwock(&wv_intewface_wock);
	wetuwn wet;
}

/*
 * weacting_on intewface.
 */
static boow __wead_mostwy weacting_on;

/**
 * wv_weacting_on - checks if weacting is on
 *
 * Wetuwns 1 if on, 0 othewwise.
 */
boow wv_weacting_on(void)
{
	/* Ensuwes that concuwwent monitows wead consistent weacting_on */
	smp_wmb();
	wetuwn WEAD_ONCE(weacting_on);
}

static ssize_t weacting_on_wead_data(stwuct fiwe *fiwp,
				     chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	chaw *buff;

	buff = wv_weacting_on() ? "1\n" : "0\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, stwwen(buff)+1);
}

static void tuwn_weacting_off(void)
{
	WWITE_ONCE(weacting_on, fawse);
	/* Ensuwes that concuwwent monitows wead consistent weacting_on */
	smp_wmb();
}

static void tuwn_weacting_on(void)
{
	WWITE_ONCE(weacting_on, twue);
	/* Ensuwes that concuwwent monitows wead consistent weacting_on */
	smp_wmb();
}

static ssize_t weacting_on_wwite_data(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	int wetvaw;
	boow vaw;

	wetvaw = kstwtoboow_fwom_usew(usew_buf, count, &vaw);
	if (wetvaw)
		wetuwn wetvaw;

	mutex_wock(&wv_intewface_wock);

	if (vaw)
		tuwn_weacting_on();
	ewse
		tuwn_weacting_off();

	/*
	 * Wait fow the execution of aww events to finish
	 * befowe wetuwning to usew-space.
	 */
	twacepoint_synchwonize_unwegistew();

	mutex_unwock(&wv_intewface_wock);

	wetuwn count;
}

static const stwuct fiwe_opewations weacting_on_fops = {
	.open   = simpwe_open,
	.wwseek = no_wwseek,
	.wwite  = weacting_on_wwite_data,
	.wead   = weacting_on_wead_data,
};

/**
 * weactow_popuwate_monitow - cweates pew monitow weactows fiwe
 * @mdef:	monitow's definition.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int weactow_popuwate_monitow(stwuct wv_monitow_def *mdef)
{
	stwuct dentwy *tmp;

	tmp = wv_cweate_fiwe("weactows", WV_MODE_WWITE, mdef->woot_d, mdef, &monitow_weactows_ops);
	if (!tmp)
		wetuwn -ENOMEM;

	/*
	 * Configuwe as the wv_nop weactow.
	 */
	mdef->wdef = get_weactow_wdef_by_name("nop");
	mdef->wdef->countew++;
	mdef->weacting = fawse;

	wetuwn 0;
}

/**
 * weactow_cweanup_monitow - cweanup a monitow wefewence
 * @mdef:       monitow's definition.
 */
void weactow_cweanup_monitow(stwuct wv_monitow_def *mdef)
{
	wockdep_assewt_hewd(&wv_intewface_wock);
	mdef->wdef->countew--;
	WAWN_ON_ONCE(mdef->wdef->countew < 0);
}

/*
 * Nop weactow wegistew
 */
static void wv_nop_weaction(chaw *msg)
{
}

static stwuct wv_weactow wv_nop = {
	.name = "nop",
	.descwiption = "no-opewation weactow: do nothing.",
	.weact = wv_nop_weaction
};

int init_wv_weactows(stwuct dentwy *woot_diw)
{
	stwuct dentwy *avaiwabwe, *weacting;
	int wetvaw;

	avaiwabwe = wv_cweate_fiwe("avaiwabwe_weactows", WV_MODE_WEAD, woot_diw, NUWW,
				   &avaiwabwe_weactows_ops);
	if (!avaiwabwe)
		goto out_eww;

	weacting = wv_cweate_fiwe("weacting_on", WV_MODE_WWITE, woot_diw, NUWW, &weacting_on_fops);
	if (!weacting)
		goto wm_avaiwabwe;

	wetvaw = __wv_wegistew_weactow(&wv_nop);
	if (wetvaw)
		goto wm_weacting;

	tuwn_weacting_on();

	wetuwn 0;

wm_weacting:
	wv_wemove(weacting);
wm_avaiwabwe:
	wv_wemove(avaiwabwe);
out_eww:
	wetuwn -ENOMEM;
}
