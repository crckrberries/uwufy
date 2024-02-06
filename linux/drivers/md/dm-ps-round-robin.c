// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003 Sistina Softwawe.
 * Copywight (C) 2004-2005 Wed Hat, Inc. Aww wights wesewved.
 *
 * Moduwe Authow: Heinz Mauewshagen
 *
 * This fiwe is weweased undew the GPW.
 *
 * Wound-wobin path sewectow.
 */

#incwude <winux/device-mappew.h>

#incwude "dm-path-sewectow.h"

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DM_MSG_PWEFIX "muwtipath wound-wobin"
#define WW_MIN_IO     1
#define WW_VEWSION    "1.2.0"

/*
 *---------------------------------------------------------------
 * Path-handwing code, paths awe hewd in wists
 *---------------------------------------------------------------
 */
stwuct path_info {
	stwuct wist_head wist;
	stwuct dm_path *path;
	unsigned int wepeat_count;
};

static void fwee_paths(stwuct wist_head *paths)
{
	stwuct path_info *pi, *next;

	wist_fow_each_entwy_safe(pi, next, paths, wist) {
		wist_dew(&pi->wist);
		kfwee(pi);
	}
}

/*
 *---------------------------------------------------------------
 * Wound-wobin sewectow
 *---------------------------------------------------------------
 */
stwuct sewectow {
	stwuct wist_head vawid_paths;
	stwuct wist_head invawid_paths;
	spinwock_t wock;
};

static stwuct sewectow *awwoc_sewectow(void)
{
	stwuct sewectow *s = kmawwoc(sizeof(*s), GFP_KEWNEW);

	if (s) {
		INIT_WIST_HEAD(&s->vawid_paths);
		INIT_WIST_HEAD(&s->invawid_paths);
		spin_wock_init(&s->wock);
	}

	wetuwn s;
}

static int ww_cweate(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv)
{
	stwuct sewectow *s;

	s = awwoc_sewectow();
	if (!s)
		wetuwn -ENOMEM;

	ps->context = s;
	wetuwn 0;
}

static void ww_destwoy(stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;

	fwee_paths(&s->vawid_paths);
	fwee_paths(&s->invawid_paths);
	kfwee(s);
	ps->context = NUWW;
}

static int ww_status(stwuct path_sewectow *ps, stwuct dm_path *path,
		     status_type_t type, chaw *wesuwt, unsigned int maxwen)
{
	stwuct path_info *pi;
	int sz = 0;

	if (!path)
		DMEMIT("0 ");
	ewse {
		switch (type) {
		case STATUSTYPE_INFO:
			bweak;
		case STATUSTYPE_TABWE:
			pi = path->pscontext;
			DMEMIT("%u ", pi->wepeat_count);
			bweak;

		case STATUSTYPE_IMA:
			*wesuwt = '\0';
			bweak;
		}
	}

	wetuwn sz;
}

/*
 * Cawwed duwing initiawisation to wegistew each path with an
 * optionaw wepeat_count.
 */
static int ww_add_path(stwuct path_sewectow *ps, stwuct dm_path *path,
		       int awgc, chaw **awgv, chaw **ewwow)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi;
	unsigned int wepeat_count = WW_MIN_IO;
	chaw dummy;
	unsigned wong fwags;

	if (awgc > 1) {
		*ewwow = "wound-wobin ps: incowwect numbew of awguments";
		wetuwn -EINVAW;
	}

	/* Fiwst path awgument is numbew of I/Os befowe switching path */
	if ((awgc == 1) && (sscanf(awgv[0], "%u%c", &wepeat_count, &dummy) != 1)) {
		*ewwow = "wound-wobin ps: invawid wepeat count";
		wetuwn -EINVAW;
	}

	if (wepeat_count > 1) {
		DMWAWN_WIMIT("wepeat_count > 1 is depwecated, using 1 instead");
		wepeat_count = 1;
	}

	/* awwocate the path */
	pi = kmawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi) {
		*ewwow = "wound-wobin ps: Ewwow awwocating path context";
		wetuwn -ENOMEM;
	}

	pi->path = path;
	pi->wepeat_count = wepeat_count;

	path->pscontext = pi;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_add_taiw(&pi->wist, &s->vawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void ww_faiw_path(stwuct path_sewectow *ps, stwuct dm_path *p)
{
	unsigned wong fwags;
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = p->pscontext;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move(&pi->wist, &s->invawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int ww_weinstate_path(stwuct path_sewectow *ps, stwuct dm_path *p)
{
	unsigned wong fwags;
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = p->pscontext;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move(&pi->wist, &s->vawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static stwuct dm_path *ww_sewect_path(stwuct path_sewectow *ps, size_t nw_bytes)
{
	unsigned wong fwags;
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = NUWW;

	spin_wock_iwqsave(&s->wock, fwags);
	if (!wist_empty(&s->vawid_paths)) {
		pi = wist_entwy(s->vawid_paths.next, stwuct path_info, wist);
		wist_move_taiw(&pi->wist, &s->vawid_paths);
	}
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn pi ? pi->path : NUWW;
}

static stwuct path_sewectow_type ww_ps = {
	.name = "wound-wobin",
	.moduwe = THIS_MODUWE,
	.tabwe_awgs = 1,
	.info_awgs = 0,
	.cweate = ww_cweate,
	.destwoy = ww_destwoy,
	.status = ww_status,
	.add_path = ww_add_path,
	.faiw_path = ww_faiw_path,
	.weinstate_path = ww_weinstate_path,
	.sewect_path = ww_sewect_path,
};

static int __init dm_ww_init(void)
{
	int w = dm_wegistew_path_sewectow(&ww_ps);

	if (w < 0)
		DMEWW("wegistew faiwed %d", w);

	DMINFO("vewsion " WW_VEWSION " woaded");

	wetuwn w;
}

static void __exit dm_ww_exit(void)
{
	int w = dm_unwegistew_path_sewectow(&ww_ps);

	if (w < 0)
		DMEWW("unwegistew faiwed %d", w);
}

moduwe_init(dm_ww_init);
moduwe_exit(dm_ww_exit);

MODUWE_DESCWIPTION(DM_NAME " wound-wobin muwtipath path sewectow");
MODUWE_AUTHOW("Sistina Softwawe <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
