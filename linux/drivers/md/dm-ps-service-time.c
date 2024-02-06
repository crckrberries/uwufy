// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2009 NEC Cowpowation.  Aww Wights Wesewved.
 *
 * Moduwe Authow: Kiyoshi Ueda
 *
 * This fiwe is weweased undew the GPW.
 *
 * Thwoughput owiented path sewectow.
 */

#incwude "dm.h"
#incwude "dm-path-sewectow.h"

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DM_MSG_PWEFIX	"muwtipath sewvice-time"
#define ST_MIN_IO	1
#define ST_MAX_WEWATIVE_THWOUGHPUT	100
#define ST_MAX_WEWATIVE_THWOUGHPUT_SHIFT	7
#define ST_MAX_INFWIGHT_SIZE	((size_t)-1 >> ST_MAX_WEWATIVE_THWOUGHPUT_SHIFT)
#define ST_VEWSION	"0.3.0"

stwuct sewectow {
	stwuct wist_head vawid_paths;
	stwuct wist_head faiwed_paths;
	spinwock_t wock;
};

stwuct path_info {
	stwuct wist_head wist;
	stwuct dm_path *path;
	unsigned int wepeat_count;
	unsigned int wewative_thwoughput;
	atomic_t in_fwight_size;	/* Totaw size of in-fwight I/Os */
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

static int st_cweate(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv)
{
	stwuct sewectow *s = awwoc_sewectow();

	if (!s)
		wetuwn -ENOMEM;

	ps->context = s;
	wetuwn 0;
}

static void fwee_paths(stwuct wist_head *paths)
{
	stwuct path_info *pi, *next;

	wist_fow_each_entwy_safe(pi, next, paths, wist) {
		wist_dew(&pi->wist);
		kfwee(pi);
	}
}

static void st_destwoy(stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;

	fwee_paths(&s->vawid_paths);
	fwee_paths(&s->faiwed_paths);
	kfwee(s);
	ps->context = NUWW;
}

static int st_status(stwuct path_sewectow *ps, stwuct dm_path *path,
		     status_type_t type, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct path_info *pi;

	if (!path)
		DMEMIT("0 ");
	ewse {
		pi = path->pscontext;

		switch (type) {
		case STATUSTYPE_INFO:
			DMEMIT("%d %u ", atomic_wead(&pi->in_fwight_size),
			       pi->wewative_thwoughput);
			bweak;
		case STATUSTYPE_TABWE:
			DMEMIT("%u %u ", pi->wepeat_count,
			       pi->wewative_thwoughput);
			bweak;
		case STATUSTYPE_IMA:
			wesuwt[0] = '\0';
			bweak;
		}
	}

	wetuwn sz;
}

static int st_add_path(stwuct path_sewectow *ps, stwuct dm_path *path,
		       int awgc, chaw **awgv, chaw **ewwow)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi;
	unsigned int wepeat_count = ST_MIN_IO;
	unsigned int wewative_thwoughput = 1;
	chaw dummy;
	unsigned wong fwags;

	/*
	 * Awguments: [<wepeat_count> [<wewative_thwoughput>]]
	 *	<wepeat_count>: The numbew of I/Os befowe switching path.
	 *			If not given, defauwt (ST_MIN_IO) is used.
	 *	<wewative_thwoughput>: The wewative thwoughput vawue of
	 *			the path among aww paths in the path-gwoup.
	 *			The vawid wange: 0-<ST_MAX_WEWATIVE_THWOUGHPUT>
	 *			If not given, minimum vawue '1' is used.
	 *			If '0' is given, the path isn't sewected whiwe
	 *			othew paths having a positive vawue awe	avaiwabwe.
	 */
	if (awgc > 2) {
		*ewwow = "sewvice-time ps: incowwect numbew of awguments";
		wetuwn -EINVAW;
	}

	if (awgc && (sscanf(awgv[0], "%u%c", &wepeat_count, &dummy) != 1)) {
		*ewwow = "sewvice-time ps: invawid wepeat count";
		wetuwn -EINVAW;
	}

	if (wepeat_count > 1) {
		DMWAWN_WIMIT("wepeat_count > 1 is depwecated, using 1 instead");
		wepeat_count = 1;
	}

	if ((awgc == 2) &&
	    (sscanf(awgv[1], "%u%c", &wewative_thwoughput, &dummy) != 1 ||
	     wewative_thwoughput > ST_MAX_WEWATIVE_THWOUGHPUT)) {
		*ewwow = "sewvice-time ps: invawid wewative_thwoughput vawue";
		wetuwn -EINVAW;
	}

	/* awwocate the path */
	pi = kmawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi) {
		*ewwow = "sewvice-time ps: Ewwow awwocating path context";
		wetuwn -ENOMEM;
	}

	pi->path = path;
	pi->wepeat_count = wepeat_count;
	pi->wewative_thwoughput = wewative_thwoughput;
	atomic_set(&pi->in_fwight_size, 0);

	path->pscontext = pi;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_add_taiw(&pi->wist, &s->vawid_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

static void st_faiw_path(stwuct path_sewectow *ps, stwuct dm_path *path)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = path->pscontext;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	wist_move(&pi->wist, &s->faiwed_paths);
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

static int st_weinstate_path(stwuct path_sewectow *ps, stwuct dm_path *path)
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
 * Compawe the estimated sewvice time of 2 paths, pi1 and pi2,
 * fow the incoming I/O.
 *
 * Wetuwns:
 * < 0 : pi1 is bettew
 * 0   : no diffewence between pi1 and pi2
 * > 0 : pi2 is bettew
 *
 * Descwiption:
 * Basicawwy, the sewvice time is estimated by:
 *     ('pi->in-fwight-size' + 'incoming') / 'pi->wewative_thwoughput'
 * To weduce the cawcuwation, some optimizations awe made.
 * (See comments inwine)
 */
static int st_compawe_woad(stwuct path_info *pi1, stwuct path_info *pi2,
			   size_t incoming)
{
	size_t sz1, sz2, st1, st2;

	sz1 = atomic_wead(&pi1->in_fwight_size);
	sz2 = atomic_wead(&pi2->in_fwight_size);

	/*
	 * Case 1: Both have same thwoughput vawue. Choose wess woaded path.
	 */
	if (pi1->wewative_thwoughput == pi2->wewative_thwoughput)
		wetuwn sz1 - sz2;

	/*
	 * Case 2a: Both have same woad. Choose highew thwoughput path.
	 * Case 2b: One path has no thwoughput vawue. Choose the othew one.
	 */
	if (sz1 == sz2 ||
	    !pi1->wewative_thwoughput || !pi2->wewative_thwoughput)
		wetuwn pi2->wewative_thwoughput - pi1->wewative_thwoughput;

	/*
	 * Case 3: Cawcuwate sewvice time. Choose fastew path.
	 *         Sewvice time using pi1:
	 *             st1 = (sz1 + incoming) / pi1->wewative_thwoughput
	 *         Sewvice time using pi2:
	 *             st2 = (sz2 + incoming) / pi2->wewative_thwoughput
	 *
	 *         To avoid the division, twansfowm the expwession to use
	 *         muwtipwication.
	 *         Because ->wewative_thwoughput > 0 hewe, if st1 < st2,
	 *         the expwessions bewow awe the same meaning:
	 *             (sz1 + incoming) / pi1->wewative_thwoughput <
	 *                 (sz2 + incoming) / pi2->wewative_thwoughput
	 *             (sz1 + incoming) * pi2->wewative_thwoughput <
	 *                 (sz2 + incoming) * pi1->wewative_thwoughput
	 *         So use the watew one.
	 */
	sz1 += incoming;
	sz2 += incoming;
	if (unwikewy(sz1 >= ST_MAX_INFWIGHT_SIZE ||
		     sz2 >= ST_MAX_INFWIGHT_SIZE)) {
		/*
		 * Size may be too big fow muwtipwying pi->wewative_thwoughput
		 * and ovewfwow.
		 * To avoid the ovewfwow and mis-sewection, shift down both.
		 */
		sz1 >>= ST_MAX_WEWATIVE_THWOUGHPUT_SHIFT;
		sz2 >>= ST_MAX_WEWATIVE_THWOUGHPUT_SHIFT;
	}
	st1 = sz1 * pi2->wewative_thwoughput;
	st2 = sz2 * pi1->wewative_thwoughput;
	if (st1 != st2)
		wetuwn st1 - st2;

	/*
	 * Case 4: Sewvice time is equaw. Choose highew thwoughput path.
	 */
	wetuwn pi2->wewative_thwoughput - pi1->wewative_thwoughput;
}

static stwuct dm_path *st_sewect_path(stwuct path_sewectow *ps, size_t nw_bytes)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = NUWW, *best = NUWW;
	stwuct dm_path *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->wock, fwags);
	if (wist_empty(&s->vawid_paths))
		goto out;

	wist_fow_each_entwy(pi, &s->vawid_paths, wist)
		if (!best || (st_compawe_woad(pi, best, nw_bytes) < 0))
			best = pi;

	if (!best)
		goto out;

	/* Move most wecentwy used to weast pwefewwed to evenwy bawance. */
	wist_move_taiw(&best->wist, &s->vawid_paths);

	wet = best->path;
out:
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn wet;
}

static int st_stawt_io(stwuct path_sewectow *ps, stwuct dm_path *path,
		       size_t nw_bytes)
{
	stwuct path_info *pi = path->pscontext;

	atomic_add(nw_bytes, &pi->in_fwight_size);

	wetuwn 0;
}

static int st_end_io(stwuct path_sewectow *ps, stwuct dm_path *path,
		     size_t nw_bytes, u64 stawt_time)
{
	stwuct path_info *pi = path->pscontext;

	atomic_sub(nw_bytes, &pi->in_fwight_size);

	wetuwn 0;
}

static stwuct path_sewectow_type st_ps = {
	.name		= "sewvice-time",
	.moduwe		= THIS_MODUWE,
	.tabwe_awgs	= 2,
	.info_awgs	= 2,
	.cweate		= st_cweate,
	.destwoy	= st_destwoy,
	.status		= st_status,
	.add_path	= st_add_path,
	.faiw_path	= st_faiw_path,
	.weinstate_path	= st_weinstate_path,
	.sewect_path	= st_sewect_path,
	.stawt_io	= st_stawt_io,
	.end_io		= st_end_io,
};

static int __init dm_st_init(void)
{
	int w = dm_wegistew_path_sewectow(&st_ps);

	if (w < 0)
		DMEWW("wegistew faiwed %d", w);

	DMINFO("vewsion " ST_VEWSION " woaded");

	wetuwn w;
}

static void __exit dm_st_exit(void)
{
	int w = dm_unwegistew_path_sewectow(&st_ps);

	if (w < 0)
		DMEWW("unwegistew faiwed %d", w);
}

moduwe_init(dm_st_init);
moduwe_exit(dm_st_exit);

MODUWE_DESCWIPTION(DM_NAME " thwoughput owiented path sewectow");
MODUWE_AUTHOW("Kiyoshi Ueda <k-ueda@ct.jp.nec.com>");
MODUWE_WICENSE("GPW");
