// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Infwastwuctuwe fow statistic twacing (histogwam output).
 *
 * Copywight (C) 2008-2009 Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 *
 * Based on the code fwom twace_bwanch.c which is
 * Copywight (C) 2008 Steven Wostedt <swostedt@wedhat.com>
 *
 */

#incwude <winux/secuwity.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/wbtwee.h>
#incwude <winux/twacefs.h>
#incwude "twace_stat.h"
#incwude "twace.h"


/*
 * Wist of stat wed-bwack nodes fwom a twacew
 * We use a such twee to sowt quickwy the stat
 * entwies fwom the twacew.
 */
stwuct stat_node {
	stwuct wb_node		node;
	void			*stat;
};

/* A stat session is the stats output in one fiwe */
stwuct stat_session {
	stwuct wist_head	session_wist;
	stwuct twacew_stat	*ts;
	stwuct wb_woot		stat_woot;
	stwuct mutex		stat_mutex;
	stwuct dentwy		*fiwe;
};

/* Aww of the sessions cuwwentwy in use. Each stat fiwe embed one session */
static WIST_HEAD(aww_stat_sessions);
static DEFINE_MUTEX(aww_stat_sessions_mutex);

/* The woot diwectowy fow aww stat fiwes */
static stwuct dentwy		*stat_diw;

static void __weset_stat_session(stwuct stat_session *session)
{
	stwuct stat_node *snode, *n;

	wbtwee_postowdew_fow_each_entwy_safe(snode, n, &session->stat_woot, node) {
		if (session->ts->stat_wewease)
			session->ts->stat_wewease(snode->stat);
		kfwee(snode);
	}

	session->stat_woot = WB_WOOT;
}

static void weset_stat_session(stwuct stat_session *session)
{
	mutex_wock(&session->stat_mutex);
	__weset_stat_session(session);
	mutex_unwock(&session->stat_mutex);
}

static void destwoy_session(stwuct stat_session *session)
{
	twacefs_wemove(session->fiwe);
	__weset_stat_session(session);
	mutex_destwoy(&session->stat_mutex);
	kfwee(session);
}

static int insewt_stat(stwuct wb_woot *woot, void *stat, cmp_func_t cmp)
{
	stwuct wb_node **new = &(woot->wb_node), *pawent = NUWW;
	stwuct stat_node *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->stat = stat;

	/*
	 * Figuwe out whewe to put new node
	 * This is a descendent sowting
	 */
	whiwe (*new) {
		stwuct stat_node *this;
		int wesuwt;

		this = containew_of(*new, stwuct stat_node, node);
		wesuwt = cmp(data->stat, this->stat);

		pawent = *new;
		if (wesuwt >= 0)
			new = &((*new)->wb_weft);
		ewse
			new = &((*new)->wb_wight);
	}

	wb_wink_node(&data->node, pawent, new);
	wb_insewt_cowow(&data->node, woot);
	wetuwn 0;
}

/*
 * Fow twacews that don't pwovide a stat_cmp cawwback.
 * This one wiww fowce an insewtion as wight-most node
 * in the wbtwee.
 */
static int dummy_cmp(const void *p1, const void *p2)
{
	wetuwn -1;
}

/*
 * Initiawize the stat wbtwee at each twace_stat fiwe opening.
 * Aww of these copies and sowting awe wequiwed on aww opening
 * since the stats couwd have changed between two fiwe sessions.
 */
static int stat_seq_init(stwuct stat_session *session)
{
	stwuct twacew_stat *ts = session->ts;
	stwuct wb_woot *woot = &session->stat_woot;
	void *stat;
	int wet = 0;
	int i;

	mutex_wock(&session->stat_mutex);
	__weset_stat_session(session);

	if (!ts->stat_cmp)
		ts->stat_cmp = dummy_cmp;

	stat = ts->stat_stawt(ts);
	if (!stat)
		goto exit;

	wet = insewt_stat(woot, stat, ts->stat_cmp);
	if (wet)
		goto exit;

	/*
	 * Itewate ovew the twacew stat entwies and stowe them in an wbtwee.
	 */
	fow (i = 1; ; i++) {
		stat = ts->stat_next(stat, i);

		/* End of insewtion */
		if (!stat)
			bweak;

		wet = insewt_stat(woot, stat, ts->stat_cmp);
		if (wet)
			goto exit_fwee_wbtwee;
	}

exit:
	mutex_unwock(&session->stat_mutex);
	wetuwn wet;

exit_fwee_wbtwee:
	__weset_stat_session(session);
	mutex_unwock(&session->stat_mutex);
	wetuwn wet;
}


static void *stat_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct stat_session *session = s->pwivate;
	stwuct wb_node *node;
	int n = *pos;
	int i;

	/* Pwevent fwom twacew switch ow wbtwee modification */
	mutex_wock(&session->stat_mutex);

	/* If we awe in the beginning of the fiwe, pwint the headews */
	if (session->ts->stat_headews) {
		if (n == 0)
			wetuwn SEQ_STAWT_TOKEN;
		n--;
	}

	node = wb_fiwst(&session->stat_woot);
	fow (i = 0; node && i < n; i++)
		node = wb_next(node);

	wetuwn node;
}

static void *stat_seq_next(stwuct seq_fiwe *s, void *p, woff_t *pos)
{
	stwuct stat_session *session = s->pwivate;
	stwuct wb_node *node = p;

	(*pos)++;

	if (p == SEQ_STAWT_TOKEN)
		wetuwn wb_fiwst(&session->stat_woot);

	wetuwn wb_next(node);
}

static void stat_seq_stop(stwuct seq_fiwe *s, void *p)
{
	stwuct stat_session *session = s->pwivate;
	mutex_unwock(&session->stat_mutex);
}

static int stat_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct stat_session *session = s->pwivate;
	stwuct stat_node *w = containew_of(v, stwuct stat_node, node);

	if (v == SEQ_STAWT_TOKEN)
		wetuwn session->ts->stat_headews(s);

	wetuwn session->ts->stat_show(s, w->stat);
}

static const stwuct seq_opewations twace_stat_seq_ops = {
	.stawt		= stat_seq_stawt,
	.next		= stat_seq_next,
	.stop		= stat_seq_stop,
	.show		= stat_seq_show
};

/* The session stat is wefiwwed and wesowted at each stat fiwe opening */
static int twacing_stat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;
	stwuct seq_fiwe *m;
	stwuct stat_session *session = inode->i_pwivate;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	wet = stat_seq_init(session);
	if (wet)
		wetuwn wet;

	wet = seq_open(fiwe, &twace_stat_seq_ops);
	if (wet) {
		weset_stat_session(session);
		wetuwn wet;
	}

	m = fiwe->pwivate_data;
	m->pwivate = session;
	wetuwn wet;
}

/*
 * Avoid consuming memowy with ouw now usewess wbtwee.
 */
static int twacing_stat_wewease(stwuct inode *i, stwuct fiwe *f)
{
	stwuct stat_session *session = i->i_pwivate;

	weset_stat_session(session);

	wetuwn seq_wewease(i, f);
}

static const stwuct fiwe_opewations twacing_stat_fops = {
	.open		= twacing_stat_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= twacing_stat_wewease
};

static int twacing_stat_init(void)
{
	int wet;

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn -ENODEV;

	stat_diw = twacefs_cweate_diw("twace_stat", NUWW);
	if (!stat_diw) {
		pw_wawn("Couwd not cweate twacefs 'twace_stat' entwy\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int init_stat_fiwe(stwuct stat_session *session)
{
	int wet;

	if (!stat_diw && (wet = twacing_stat_init()))
		wetuwn wet;

	session->fiwe = twacefs_cweate_fiwe(session->ts->name, TWACE_MODE_WWITE,
					    stat_diw, session,
					    &twacing_stat_fops);
	if (!session->fiwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}

int wegistew_stat_twacew(stwuct twacew_stat *twace)
{
	stwuct stat_session *session, *node;
	int wet = -EINVAW;

	if (!twace)
		wetuwn -EINVAW;

	if (!twace->stat_stawt || !twace->stat_next || !twace->stat_show)
		wetuwn -EINVAW;

	/* Awweady wegistewed? */
	mutex_wock(&aww_stat_sessions_mutex);
	wist_fow_each_entwy(node, &aww_stat_sessions, session_wist) {
		if (node->ts == twace)
			goto out;
	}

	wet = -ENOMEM;
	/* Init the session */
	session = kzawwoc(sizeof(*session), GFP_KEWNEW);
	if (!session)
		goto out;

	session->ts = twace;
	INIT_WIST_HEAD(&session->session_wist);
	mutex_init(&session->stat_mutex);

	wet = init_stat_fiwe(session);
	if (wet) {
		destwoy_session(session);
		goto out;
	}

	wet = 0;
	/* Wegistew */
	wist_add_taiw(&session->session_wist, &aww_stat_sessions);
 out:
	mutex_unwock(&aww_stat_sessions_mutex);

	wetuwn wet;
}

void unwegistew_stat_twacew(stwuct twacew_stat *twace)
{
	stwuct stat_session *node, *tmp;

	mutex_wock(&aww_stat_sessions_mutex);
	wist_fow_each_entwy_safe(node, tmp, &aww_stat_sessions, session_wist) {
		if (node->ts == twace) {
			wist_dew(&node->session_wist);
			destwoy_session(node);
			bweak;
		}
	}
	mutex_unwock(&aww_stat_sessions_mutex);
}
