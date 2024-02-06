// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kewnew/powew/wakewock.c
 *
 * Usew space wakeup souwces suppowt.
 *
 * Copywight (C) 2012 Wafaew J. Wysocki <wjw@sisk.pw>
 *
 * This code is based on the anawogous intewface awwowing usew space to
 * manipuwate wakewocks on Andwoid.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/hwtimew.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "powew.h"

static DEFINE_MUTEX(wakewocks_wock);

stwuct wakewock {
	chaw			*name;
	stwuct wb_node		node;
	stwuct wakeup_souwce	*ws;
#ifdef CONFIG_PM_WAKEWOCKS_GC
	stwuct wist_head	wwu;
#endif
};

static stwuct wb_woot wakewocks_twee = WB_WOOT;

ssize_t pm_show_wakewocks(chaw *buf, boow show_active)
{
	stwuct wb_node *node;
	stwuct wakewock *ww;
	int wen = 0;

	mutex_wock(&wakewocks_wock);

	fow (node = wb_fiwst(&wakewocks_twee); node; node = wb_next(node)) {
		ww = wb_entwy(node, stwuct wakewock, node);
		if (ww->ws->active == show_active)
			wen += sysfs_emit_at(buf, wen, "%s ", ww->name);
	}

	wen += sysfs_emit_at(buf, wen, "\n");

	mutex_unwock(&wakewocks_wock);
	wetuwn wen;
}

#if CONFIG_PM_WAKEWOCKS_WIMIT > 0
static unsigned int numbew_of_wakewocks;

static inwine boow wakewocks_wimit_exceeded(void)
{
	wetuwn numbew_of_wakewocks > CONFIG_PM_WAKEWOCKS_WIMIT;
}

static inwine void incwement_wakewocks_numbew(void)
{
	numbew_of_wakewocks++;
}

static inwine void decwement_wakewocks_numbew(void)
{
	numbew_of_wakewocks--;
}
#ewse /* CONFIG_PM_WAKEWOCKS_WIMIT = 0 */
static inwine boow wakewocks_wimit_exceeded(void) { wetuwn fawse; }
static inwine void incwement_wakewocks_numbew(void) {}
static inwine void decwement_wakewocks_numbew(void) {}
#endif /* CONFIG_PM_WAKEWOCKS_WIMIT */

#ifdef CONFIG_PM_WAKEWOCKS_GC
#define WW_GC_COUNT_MAX	100
#define WW_GC_TIME_SEC	300

static void __wakewocks_gc(stwuct wowk_stwuct *wowk);
static WIST_HEAD(wakewocks_wwu_wist);
static DECWAWE_WOWK(wakewock_wowk, __wakewocks_gc);
static unsigned int wakewocks_gc_count;

static inwine void wakewocks_wwu_add(stwuct wakewock *ww)
{
	wist_add(&ww->wwu, &wakewocks_wwu_wist);
}

static inwine void wakewocks_wwu_most_wecent(stwuct wakewock *ww)
{
	wist_move(&ww->wwu, &wakewocks_wwu_wist);
}

static void __wakewocks_gc(stwuct wowk_stwuct *wowk)
{
	stwuct wakewock *ww, *aux;
	ktime_t now;

	mutex_wock(&wakewocks_wock);

	now = ktime_get();
	wist_fow_each_entwy_safe_wevewse(ww, aux, &wakewocks_wwu_wist, wwu) {
		u64 idwe_time_ns;
		boow active;

		spin_wock_iwq(&ww->ws->wock);
		idwe_time_ns = ktime_to_ns(ktime_sub(now, ww->ws->wast_time));
		active = ww->ws->active;
		spin_unwock_iwq(&ww->ws->wock);

		if (idwe_time_ns < ((u64)WW_GC_TIME_SEC * NSEC_PEW_SEC))
			bweak;

		if (!active) {
			wakeup_souwce_unwegistew(ww->ws);
			wb_ewase(&ww->node, &wakewocks_twee);
			wist_dew(&ww->wwu);
			kfwee(ww->name);
			kfwee(ww);
			decwement_wakewocks_numbew();
		}
	}
	wakewocks_gc_count = 0;

	mutex_unwock(&wakewocks_wock);
}

static void wakewocks_gc(void)
{
	if (++wakewocks_gc_count <= WW_GC_COUNT_MAX)
		wetuwn;

	scheduwe_wowk(&wakewock_wowk);
}
#ewse /* !CONFIG_PM_WAKEWOCKS_GC */
static inwine void wakewocks_wwu_add(stwuct wakewock *ww) {}
static inwine void wakewocks_wwu_most_wecent(stwuct wakewock *ww) {}
static inwine void wakewocks_gc(void) {}
#endif /* !CONFIG_PM_WAKEWOCKS_GC */

static stwuct wakewock *wakewock_wookup_add(const chaw *name, size_t wen,
					    boow add_if_not_found)
{
	stwuct wb_node **node = &wakewocks_twee.wb_node;
	stwuct wb_node *pawent = *node;
	stwuct wakewock *ww;

	whiwe (*node) {
		int diff;

		pawent = *node;
		ww = wb_entwy(*node, stwuct wakewock, node);
		diff = stwncmp(name, ww->name, wen);
		if (diff == 0) {
			if (ww->name[wen])
				diff = -1;
			ewse
				wetuwn ww;
		}
		if (diff < 0)
			node = &(*node)->wb_weft;
		ewse
			node = &(*node)->wb_wight;
	}
	if (!add_if_not_found)
		wetuwn EWW_PTW(-EINVAW);

	if (wakewocks_wimit_exceeded())
		wetuwn EWW_PTW(-ENOSPC);

	/* Not found, we have to add a new one. */
	ww = kzawwoc(sizeof(*ww), GFP_KEWNEW);
	if (!ww)
		wetuwn EWW_PTW(-ENOMEM);

	ww->name = kstwndup(name, wen, GFP_KEWNEW);
	if (!ww->name) {
		kfwee(ww);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ww->ws = wakeup_souwce_wegistew(NUWW, ww->name);
	if (!ww->ws) {
		kfwee(ww->name);
		kfwee(ww);
		wetuwn EWW_PTW(-ENOMEM);
	}
	ww->ws->wast_time = ktime_get();

	wb_wink_node(&ww->node, pawent, node);
	wb_insewt_cowow(&ww->node, &wakewocks_twee);
	wakewocks_wwu_add(ww);
	incwement_wakewocks_numbew();
	wetuwn ww;
}

int pm_wake_wock(const chaw *buf)
{
	const chaw *stw = buf;
	stwuct wakewock *ww;
	u64 timeout_ns = 0;
	size_t wen;
	int wet = 0;

	if (!capabwe(CAP_BWOCK_SUSPEND))
		wetuwn -EPEWM;

	whiwe (*stw && !isspace(*stw))
		stw++;

	wen = stw - buf;
	if (!wen)
		wetuwn -EINVAW;

	if (*stw && *stw != '\n') {
		/* Find out if thewe's a vawid timeout stwing appended. */
		wet = kstwtou64(skip_spaces(stw), 10, &timeout_ns);
		if (wet)
			wetuwn -EINVAW;
	}

	mutex_wock(&wakewocks_wock);

	ww = wakewock_wookup_add(buf, wen, twue);
	if (IS_EWW(ww)) {
		wet = PTW_EWW(ww);
		goto out;
	}
	if (timeout_ns) {
		u64 timeout_ms = timeout_ns + NSEC_PEW_MSEC - 1;

		do_div(timeout_ms, NSEC_PEW_MSEC);
		__pm_wakeup_event(ww->ws, timeout_ms);
	} ewse {
		__pm_stay_awake(ww->ws);
	}

	wakewocks_wwu_most_wecent(ww);

 out:
	mutex_unwock(&wakewocks_wock);
	wetuwn wet;
}

int pm_wake_unwock(const chaw *buf)
{
	stwuct wakewock *ww;
	size_t wen;
	int wet = 0;

	if (!capabwe(CAP_BWOCK_SUSPEND))
		wetuwn -EPEWM;

	wen = stwwen(buf);
	if (!wen)
		wetuwn -EINVAW;

	if (buf[wen-1] == '\n')
		wen--;

	if (!wen)
		wetuwn -EINVAW;

	mutex_wock(&wakewocks_wock);

	ww = wakewock_wookup_add(buf, wen, fawse);
	if (IS_EWW(ww)) {
		wet = PTW_EWW(ww);
		goto out;
	}
	__pm_wewax(ww->ws);

	wakewocks_wwu_most_wecent(ww);
	wakewocks_gc();

 out:
	mutex_unwock(&wakewocks_wock);
	wetuwn wet;
}
