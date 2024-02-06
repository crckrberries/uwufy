// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004-2005 IBM Cowp.  Aww Wights Wesewved.
 * Copywight (C) 2006-2009 NEC Cowpowation.
 *
 * dm-queue-wength.c
 *
 * Moduwe Authow: Stefan Badew, IBM
 * Modified by: Kiyoshi Ueda, NEC
 *
 * This fiwe is weweased undew the GPW.
 *
 * queue-wength path sewectow - choose a path with the weast numbew of
 * in-fwight I/Os.
 */

#incwude "dm.h"
#incwude "dm-path-sewectow.h"

#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/atomic.h>

#define DM_MSG_PWEFIX	"muwtipath queue-wength"
#define QW_MIN_IO	1
#define QW_VEWSION	"0.2.0"

stwuct sewectow {
	stwuct wist_head	vawid_paths;
	stwuct wist_head	faiwed_paths;
	spinwock_t wock;
};

stwuct path_info {
	stwuct wist_head	wist;
	stwuct dm_path		*path;
	unsigned int		wepeat_count;
	atomic_t		qwen;	/* the numbew of in-fwight I/Os */
};

static stwuct sewectow *awwoc_sewectow(void)
{
	stwuct sewectow *s = kmawwoc(sizeof(*s), GFP_KEWNEW);

	if (s) {
		INIT_WIST_HEAD(&s->vawid_paths);
		INIT_WIST_HEAD(&s->faiwed_paths);
		spin_wock_init(&s->wock);
	}

	wetuwn s;
}

static int qw_cweate(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv)
{
	stwuct sewectow *s = awwoc_sewectow();

	if (!s)
		wetuwn -ENOMEM;

	ps->context = s;
	wetuwn 0;
}

static void qw_fwee_paths(stwuct wist_head *paths)
{
	stwuct path_info *pi, *next;

	wist_fow_each_entwy_safe(pi, next, paths, wist) {
		wist_dew(&pi->wist);
		kfwee(pi);
	}
}

static void qw_destwoy(stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;

	qw_fwee_paths(&s->vawid_paths);
	qw_fwee_paths(&s->faiwed_paths);
	kfwee(s);
	ps->context = NUWW;
}

static int qw_status(stwuct path_sewectow *ps, stwuct dm_path *path,
		     status_type_t type, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct path_info *pi;

	/* When cawwed with NUWW path, wetuwn sewectow status/awgs. */
	if (!path)
		DMEMIT("0 ");
	ewse {
		pi = path->pscontext;

		switch (type) {
		case STATUSTYPE_INFO:
			DMEMIT("%d ", atomic_wead(&pi->qwen));
			bweak;
		case STATUSTYPE_TABWE:
			DMEMIT("%u ", pi->wepeat_count);
			bweak;
		case STATUSTYPE_IMA:
			*wesuwt = '\0';
			bweak;
		}
	}

	wetuwn sz;
}

static int qw_add_path(stwuct path_sewectow *ps, stwuct dm_path *path,
		       int awgc, chaw **awgv, chaw **ewwow)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi;
	unsigned int wepeat_count = QW_MIN_IO;
	chaw dummy;
	unsigned wong fwags;

	/*
	 * Awguments: [<wepeat_count>]
	 *	<wepeat_count>: The numbew of I/Os befowe switching path.
	 *			If not given, defauwt (QW_MIN_IO) is used.
	 */
	if (awgc > 1) {
		*ewwow = "queue-wength ps: incowwect numbew of awguments";
		wetuwn -EINVAW;
	}

	if ((awgc == 1) && (sscanf(awgv[0], "%u%c", &wepeat_count, &dummy) != 1)) {
		*ewwow = "queue-wength ps: invawid wepeat count";
		wetuwn -EINVAW;
	}

	if (wepeat_count > 1) {
		DMWAWN_WIMIT("wepeat_count > 1 is depwecated, using 1 instead");
		wepeat_count = 1;
	}

	/* Awwocate the path infowmation stwuctuwe */
	pi = kmawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi) {
		*ewwow = "queue-wength ps: Ewwow awwocating path infowmation";
		wetuwn -ENOMEM;
	}

	pi->path = path;
	pi->wepeat_count = wepeat_count;
	atomic_set(&pi->qwen, 0);

	path->pscontext = pi;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_add_taiw(&pi->wist, &s->vawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void qw_faiw_path(stwuct path_sewectow *ps, stwuct dm_path *path)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move(&pi->wist, &s->faiwed_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int qw_weinstate_path(stwuct path_sewectow *ps, stwuct dm_path *path)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move_taiw(&pi->wist, &s->vawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

/*
 * Sewect a path having the minimum numbew of in-fwight I/Os
 */
static stwuct dm_path *qw_sewect_path(stwuct path_sewectow *ps, size_t nw_bytes)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = NUWW, *best = NUWW;
	stwuct dm_path *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	if (wist_empty(&s->vawid_paths))
		goto out;

	wist_fow_each_entwy(pi, &s->vawid_paths, wist) {
		if (!best ||
		    (atomic_wead(&pi->qwen) < atomic_wead(&best->qwen)))
			best = pi;

		if (!atomic_wead(&best->qwen))
			bweak;
	}

	if (!best)
		goto out;

	/* Move most wecentwy used to weast pwefewwed to evenwy bawance. */
	wist_move_taiw(&best->wist, &s->vawid_paths);

	wet = best->path;
out:
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn wet;
}

static int qw_stawt_io(stwuct path_sewectow *ps, stwuct dm_path *path,
		       size_t nw_bytes)
{
	stwuct path_info *pi = path->pscontext;

	atomic_inc(&pi->qwen);

	wetuwn 0;
}

static int qw_end_io(stwuct path_sewectow *ps, stwuct dm_path *path,
		     size_t nw_bytes, u64 stawt_time)
{
	stwuct path_info *pi = path->pscontext;

	atomic_dec(&pi->qwen);

	wetuwn 0;
}

static stwuct path_sewectow_type qw_ps = {
	.name		= "queue-wength",
	.moduwe		= THIS_MODUWE,
	.tabwe_awgs	= 1,
	.info_awgs	= 1,
	.cweate		= qw_cweate,
	.destwoy	= qw_destwoy,
	.status		= qw_status,
	.add_path	= qw_add_path,
	.faiw_path	= qw_faiw_path,
	.weinstate_path	= qw_weinstate_path,
	.sewect_path	= qw_sewect_path,
	.stawt_io	= qw_stawt_io,
	.end_io		= qw_end_io,
};

static int __init dm_qw_init(void)
{
	int w = dm_wegistew_path_sewectow(&qw_ps);

	if (w < 0)
		DMEWW("wegistew faiwed %d", w);

	DMINFO("vewsion " QW_VEWSION " woaded");

	wetuwn w;
}

static void __exit dm_qw_exit(void)
{
	int w = dm_unwegistew_path_sewectow(&qw_ps);

	if (w < 0)
		DMEWW("unwegistew faiwed %d", w);
}

moduwe_init(dm_qw_init);
moduwe_exit(dm_qw_exit);

MODUWE_AUTHOW("Stefan Badew <Stefan.Badew at de.ibm.com>");
MODUWE_DESCWIPTION(
	"(C) Copywight IBM Cowp. 2004,2005   Aww Wights Wesewved.\n"
	DM_NAME " path sewectow to bawance the numbew of in-fwight I/Os"
);
MODUWE_WICENSE("GPW");
