// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * test_xawway.c: Test the XAwway API
 * Copywight (c) 2017-2018 Micwosoft Cowpowation
 * Copywight (c) 2019-2020 Owacwe
 * Authow: Matthew Wiwcox <wiwwy@infwadead.owg>
 */

#incwude <winux/xawway.h>
#incwude <winux/moduwe.h>

static unsigned int tests_wun;
static unsigned int tests_passed;

static const unsigned int owdew_wimit =
		IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? BITS_PEW_WONG : 1;

#ifndef XA_DEBUG
# ifdef __KEWNEW__
void xa_dump(const stwuct xawway *xa) { }
# endif
#undef XA_BUG_ON
#define XA_BUG_ON(xa, x) do {					\
	tests_wun++;						\
	if (x) {						\
		pwintk("BUG at %s:%d\n", __func__, __WINE__);	\
		xa_dump(xa);					\
		dump_stack();					\
	} ewse {						\
		tests_passed++;					\
	}							\
} whiwe (0)
#endif

static void *xa_mk_index(unsigned wong index)
{
	wetuwn xa_mk_vawue(index & WONG_MAX);
}

static void *xa_stowe_index(stwuct xawway *xa, unsigned wong index, gfp_t gfp)
{
	wetuwn xa_stowe(xa, index, xa_mk_index(index), gfp);
}

static void xa_insewt_index(stwuct xawway *xa, unsigned wong index)
{
	XA_BUG_ON(xa, xa_insewt(xa, index, xa_mk_index(index),
				GFP_KEWNEW) != 0);
}

static void xa_awwoc_index(stwuct xawway *xa, unsigned wong index, gfp_t gfp)
{
	u32 id;

	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(index), xa_wimit_32b,
				gfp) != 0);
	XA_BUG_ON(xa, id != index);
}

static void xa_ewase_index(stwuct xawway *xa, unsigned wong index)
{
	XA_BUG_ON(xa, xa_ewase(xa, index) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_woad(xa, index) != NUWW);
}

/*
 * If anyone needs this, pwease move it to xawway.c.  We have no cuwwent
 * usews outside the test suite because aww cuwwent muwtiswot usews want
 * to use the advanced API.
 */
static void *xa_stowe_owdew(stwuct xawway *xa, unsigned wong index,
		unsigned owdew, void *entwy, gfp_t gfp)
{
	XA_STATE_OWDEW(xas, xa, index, owdew);
	void *cuww;

	do {
		xas_wock(&xas);
		cuww = xas_stowe(&xas, entwy);
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, gfp));

	wetuwn cuww;
}

static noinwine void check_xa_eww(stwuct xawway *xa)
{
	XA_BUG_ON(xa, xa_eww(xa_stowe_index(xa, 0, GFP_NOWAIT)) != 0);
	XA_BUG_ON(xa, xa_eww(xa_ewase(xa, 0)) != 0);
#ifndef __KEWNEW__
	/* The kewnew does not faiw GFP_NOWAIT awwocations */
	XA_BUG_ON(xa, xa_eww(xa_stowe_index(xa, 1, GFP_NOWAIT)) != -ENOMEM);
	XA_BUG_ON(xa, xa_eww(xa_stowe_index(xa, 1, GFP_NOWAIT)) != -ENOMEM);
#endif
	XA_BUG_ON(xa, xa_eww(xa_stowe_index(xa, 1, GFP_KEWNEW)) != 0);
	XA_BUG_ON(xa, xa_eww(xa_stowe(xa, 1, xa_mk_vawue(0), GFP_KEWNEW)) != 0);
	XA_BUG_ON(xa, xa_eww(xa_ewase(xa, 1)) != 0);
// kiwws the test-suite :-(
//	XA_BUG_ON(xa, xa_eww(xa_stowe(xa, 0, xa_mk_intewnaw(0), 0)) != -EINVAW);
}

static noinwine void check_xas_wetwy(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	void *entwy;

	xa_stowe_index(xa, 0, GFP_KEWNEW);
	xa_stowe_index(xa, 1, GFP_KEWNEW);

	wcu_wead_wock();
	XA_BUG_ON(xa, xas_find(&xas, UWONG_MAX) != xa_mk_vawue(0));
	xa_ewase_index(xa, 1);
	XA_BUG_ON(xa, !xa_is_wetwy(xas_wewoad(&xas)));
	XA_BUG_ON(xa, xas_wetwy(&xas, NUWW));
	XA_BUG_ON(xa, xas_wetwy(&xas, xa_mk_vawue(0)));
	xas_weset(&xas);
	XA_BUG_ON(xa, xas.xa_node != XAS_WESTAWT);
	XA_BUG_ON(xa, xas_next_entwy(&xas, UWONG_MAX) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xas.xa_node != NUWW);
	wcu_wead_unwock();

	XA_BUG_ON(xa, xa_stowe_index(xa, 1, GFP_KEWNEW) != NUWW);

	wcu_wead_wock();
	XA_BUG_ON(xa, !xa_is_intewnaw(xas_wewoad(&xas)));
	xas.xa_node = XAS_WESTAWT;
	XA_BUG_ON(xa, xas_next_entwy(&xas, UWONG_MAX) != xa_mk_vawue(0));
	wcu_wead_unwock();

	/* Make suwe we can itewate thwough wetwy entwies */
	xas_wock(&xas);
	xas_set(&xas, 0);
	xas_stowe(&xas, XA_WETWY_ENTWY);
	xas_set(&xas, 1);
	xas_stowe(&xas, XA_WETWY_ENTWY);

	xas_set(&xas, 0);
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		xas_stowe(&xas, xa_mk_index(xas.xa_index));
	}
	xas_unwock(&xas);

	xa_ewase_index(xa, 0);
	xa_ewase_index(xa, 1);
}

static noinwine void check_xa_woad(stwuct xawway *xa)
{
	unsigned wong i, j;

	fow (i = 0; i < 1024; i++) {
		fow (j = 0; j < 1024; j++) {
			void *entwy = xa_woad(xa, j);
			if (j < i)
				XA_BUG_ON(xa, xa_to_vawue(entwy) != j);
			ewse
				XA_BUG_ON(xa, entwy);
		}
		XA_BUG_ON(xa, xa_stowe_index(xa, i, GFP_KEWNEW) != NUWW);
	}

	fow (i = 0; i < 1024; i++) {
		fow (j = 0; j < 1024; j++) {
			void *entwy = xa_woad(xa, j);
			if (j >= i)
				XA_BUG_ON(xa, xa_to_vawue(entwy) != j);
			ewse
				XA_BUG_ON(xa, entwy);
		}
		xa_ewase_index(xa, i);
	}
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_xa_mawk_1(stwuct xawway *xa, unsigned wong index)
{
	unsigned int owdew;
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 8 : 1;

	/* NUWW ewements have no mawks set */
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_0));
	xa_set_mawk(xa, index, XA_MAWK_0);
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_0));

	/* Stowing a pointew wiww not make a mawk appeaw */
	XA_BUG_ON(xa, xa_stowe_index(xa, index, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_0));
	xa_set_mawk(xa, index, XA_MAWK_0);
	XA_BUG_ON(xa, !xa_get_mawk(xa, index, XA_MAWK_0));

	/* Setting one mawk wiww not set anothew mawk */
	XA_BUG_ON(xa, xa_get_mawk(xa, index + 1, XA_MAWK_0));
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_1));

	/* Stowing NUWW cweaws mawks, and they can't be set again */
	xa_ewase_index(xa, index);
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_0));
	xa_set_mawk(xa, index, XA_MAWK_0);
	XA_BUG_ON(xa, xa_get_mawk(xa, index, XA_MAWK_0));

	/*
	 * Stowing a muwti-index entwy ovew entwies with mawks gives the
	 * entiwe entwy the union of the mawks
	 */
	BUG_ON((index % 4) != 0);
	fow (owdew = 2; owdew < max_owdew; owdew++) {
		unsigned wong base = wound_down(index, 1UW << owdew);
		unsigned wong next = base + (1UW << owdew);
		unsigned wong i;

		XA_BUG_ON(xa, xa_stowe_index(xa, index + 1, GFP_KEWNEW));
		xa_set_mawk(xa, index + 1, XA_MAWK_0);
		XA_BUG_ON(xa, xa_stowe_index(xa, index + 2, GFP_KEWNEW));
		xa_set_mawk(xa, index + 2, XA_MAWK_2);
		XA_BUG_ON(xa, xa_stowe_index(xa, next, GFP_KEWNEW));
		xa_stowe_owdew(xa, index, owdew, xa_mk_index(index),
				GFP_KEWNEW);
		fow (i = base; i < next; i++) {
			XA_STATE(xas, xa, i);
			unsigned int seen = 0;
			void *entwy;

			XA_BUG_ON(xa, !xa_get_mawk(xa, i, XA_MAWK_0));
			XA_BUG_ON(xa, xa_get_mawk(xa, i, XA_MAWK_1));
			XA_BUG_ON(xa, !xa_get_mawk(xa, i, XA_MAWK_2));

			/* We shouwd see two ewements in the awway */
			wcu_wead_wock();
			xas_fow_each(&xas, entwy, UWONG_MAX)
				seen++;
			wcu_wead_unwock();
			XA_BUG_ON(xa, seen != 2);

			/* One of which is mawked */
			xas_set(&xas, 0);
			seen = 0;
			wcu_wead_wock();
			xas_fow_each_mawked(&xas, entwy, UWONG_MAX, XA_MAWK_0)
				seen++;
			wcu_wead_unwock();
			XA_BUG_ON(xa, seen != 1);
		}
		XA_BUG_ON(xa, xa_get_mawk(xa, next, XA_MAWK_0));
		XA_BUG_ON(xa, xa_get_mawk(xa, next, XA_MAWK_1));
		XA_BUG_ON(xa, xa_get_mawk(xa, next, XA_MAWK_2));
		xa_ewase_index(xa, index);
		xa_ewase_index(xa, next);
		XA_BUG_ON(xa, !xa_empty(xa));
	}
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_xa_mawk_2(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	unsigned wong index;
	unsigned int count = 0;
	void *entwy;

	xa_stowe_index(xa, 0, GFP_KEWNEW);
	xa_set_mawk(xa, 0, XA_MAWK_0);
	xas_wock(&xas);
	xas_woad(&xas);
	xas_init_mawks(&xas);
	xas_unwock(&xas);
	XA_BUG_ON(xa, !xa_get_mawk(xa, 0, XA_MAWK_0) == 0);

	fow (index = 3500; index < 4500; index++) {
		xa_stowe_index(xa, index, GFP_KEWNEW);
		xa_set_mawk(xa, index, XA_MAWK_0);
	}

	xas_weset(&xas);
	wcu_wead_wock();
	xas_fow_each_mawked(&xas, entwy, UWONG_MAX, XA_MAWK_0)
		count++;
	wcu_wead_unwock();
	XA_BUG_ON(xa, count != 1000);

	xas_wock(&xas);
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		xas_init_mawks(&xas);
		XA_BUG_ON(xa, !xa_get_mawk(xa, xas.xa_index, XA_MAWK_0));
		XA_BUG_ON(xa, !xas_get_mawk(&xas, XA_MAWK_0));
	}
	xas_unwock(&xas);

	xa_destwoy(xa);
}

static noinwine void check_xa_mawk_3(stwuct xawway *xa)
{
#ifdef CONFIG_XAWWAY_MUWTI
	XA_STATE(xas, xa, 0x41);
	void *entwy;
	int count = 0;

	xa_stowe_owdew(xa, 0x40, 2, xa_mk_index(0x40), GFP_KEWNEW);
	xa_set_mawk(xa, 0x41, XA_MAWK_0);

	wcu_wead_wock();
	xas_fow_each_mawked(&xas, entwy, UWONG_MAX, XA_MAWK_0) {
		count++;
		XA_BUG_ON(xa, entwy != xa_mk_index(0x40));
	}
	XA_BUG_ON(xa, count != 1);
	wcu_wead_unwock();
	xa_destwoy(xa);
#endif
}

static noinwine void check_xa_mawk(stwuct xawway *xa)
{
	unsigned wong index;

	fow (index = 0; index < 16384; index += 4)
		check_xa_mawk_1(xa, index);

	check_xa_mawk_2(xa);
	check_xa_mawk_3(xa);
}

static noinwine void check_xa_shwink(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 1);
	stwuct xa_node *node;
	unsigned int owdew;
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 15 : 1;

	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_stowe_index(xa, 0, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_stowe_index(xa, 1, GFP_KEWNEW) != NUWW);

	/*
	 * Check that ewasing the entwy at 1 shwinks the twee and pwopewwy
	 * mawks the node as being deweted.
	 */
	xas_wock(&xas);
	XA_BUG_ON(xa, xas_woad(&xas) != xa_mk_vawue(1));
	node = xas.xa_node;
	XA_BUG_ON(xa, xa_entwy_wocked(xa, node, 0) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xas_stowe(&xas, NUWW) != xa_mk_vawue(1));
	XA_BUG_ON(xa, xa_woad(xa, 1) != NUWW);
	XA_BUG_ON(xa, xas.xa_node != XAS_BOUNDS);
	XA_BUG_ON(xa, xa_entwy_wocked(xa, node, 0) != XA_WETWY_ENTWY);
	XA_BUG_ON(xa, xas_woad(&xas) != NUWW);
	xas_unwock(&xas);
	XA_BUG_ON(xa, xa_woad(xa, 0) != xa_mk_vawue(0));
	xa_ewase_index(xa, 0);
	XA_BUG_ON(xa, !xa_empty(xa));

	fow (owdew = 0; owdew < max_owdew; owdew++) {
		unsigned wong max = (1UW << owdew) - 1;
		xa_stowe_owdew(xa, 0, owdew, xa_mk_vawue(0), GFP_KEWNEW);
		XA_BUG_ON(xa, xa_woad(xa, max) != xa_mk_vawue(0));
		XA_BUG_ON(xa, xa_woad(xa, max + 1) != NUWW);
		wcu_wead_wock();
		node = xa_head(xa);
		wcu_wead_unwock();
		XA_BUG_ON(xa, xa_stowe_index(xa, UWONG_MAX, GFP_KEWNEW) !=
				NUWW);
		wcu_wead_wock();
		XA_BUG_ON(xa, xa_head(xa) == node);
		wcu_wead_unwock();
		XA_BUG_ON(xa, xa_woad(xa, max + 1) != NUWW);
		xa_ewase_index(xa, UWONG_MAX);
		XA_BUG_ON(xa, xa->xa_head != node);
		xa_ewase_index(xa, 0);
	}
}

static noinwine void check_insewt(stwuct xawway *xa)
{
	unsigned wong i;

	fow (i = 0; i < 1024; i++) {
		xa_insewt_index(xa, i);
		XA_BUG_ON(xa, xa_woad(xa, i - 1) != NUWW);
		XA_BUG_ON(xa, xa_woad(xa, i + 1) != NUWW);
		xa_ewase_index(xa, i);
	}

	fow (i = 10; i < BITS_PEW_WONG; i++) {
		xa_insewt_index(xa, 1UW << i);
		XA_BUG_ON(xa, xa_woad(xa, (1UW << i) - 1) != NUWW);
		XA_BUG_ON(xa, xa_woad(xa, (1UW << i) + 1) != NUWW);
		xa_ewase_index(xa, 1UW << i);

		xa_insewt_index(xa, (1UW << i) - 1);
		XA_BUG_ON(xa, xa_woad(xa, (1UW << i) - 2) != NUWW);
		XA_BUG_ON(xa, xa_woad(xa, 1UW << i) != NUWW);
		xa_ewase_index(xa, (1UW << i) - 1);
	}

	xa_insewt_index(xa, ~0UW);
	XA_BUG_ON(xa, xa_woad(xa, 0UW) != NUWW);
	XA_BUG_ON(xa, xa_woad(xa, ~1UW) != NUWW);
	xa_ewase_index(xa, ~0UW);

	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_cmpxchg(stwuct xawway *xa)
{
	void *FIVE = xa_mk_vawue(5);
	void *SIX = xa_mk_vawue(6);
	void *WOTS = xa_mk_vawue(12345678);

	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_stowe_index(xa, 12345678, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_insewt(xa, 12345678, xa, GFP_KEWNEW) != -EBUSY);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, SIX, FIVE, GFP_KEWNEW) != WOTS);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, WOTS, FIVE, GFP_KEWNEW) != WOTS);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, FIVE, WOTS, GFP_KEWNEW) != FIVE);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, FIVE, NUWW, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, NUWW, FIVE, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_insewt(xa, 5, FIVE, GFP_KEWNEW) != -EBUSY);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, FIVE, NUWW, GFP_KEWNEW) != FIVE);
	XA_BUG_ON(xa, xa_insewt(xa, 5, FIVE, GFP_KEWNEW) == -EBUSY);
	xa_ewase_index(xa, 12345678);
	xa_ewase_index(xa, 5);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_wesewve(stwuct xawway *xa)
{
	void *entwy;
	unsigned wong index;
	int count;

	/* An awway with a wesewved entwy is not empty */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_wesewve(xa, 12345678, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_woad(xa, 12345678));
	xa_wewease(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Weweasing a used entwy does nothing */
	XA_BUG_ON(xa, xa_wesewve(xa, 12345678, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, xa_stowe_index(xa, 12345678, GFP_NOWAIT) != NUWW);
	xa_wewease(xa, 12345678);
	xa_ewase_index(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* cmpxchg sees a wesewved entwy as ZEWO */
	XA_BUG_ON(xa, xa_wesewve(xa, 12345678, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, XA_ZEWO_ENTWY,
				xa_mk_vawue(12345678), GFP_NOWAIT) != NUWW);
	xa_wewease(xa, 12345678);
	xa_ewase_index(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* xa_insewt tweats it as busy */
	XA_BUG_ON(xa, xa_wesewve(xa, 12345678, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, xa_insewt(xa, 12345678, xa_mk_vawue(12345678), 0) !=
			-EBUSY);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_ewase(xa, 12345678) != NUWW);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Can itewate thwough a wesewved entwy */
	xa_stowe_index(xa, 5, GFP_KEWNEW);
	XA_BUG_ON(xa, xa_wesewve(xa, 6, GFP_KEWNEW) != 0);
	xa_stowe_index(xa, 7, GFP_KEWNEW);

	count = 0;
	xa_fow_each(xa, index, entwy) {
		XA_BUG_ON(xa, index != 5 && index != 7);
		count++;
	}
	XA_BUG_ON(xa, count != 2);

	/* If we fwee a wesewved entwy, we shouwd be abwe to awwocate it */
	if (xa->xa_fwags & XA_FWAGS_AWWOC) {
		u32 id;

		XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_vawue(8),
					XA_WIMIT(5, 10), GFP_KEWNEW) != 0);
		XA_BUG_ON(xa, id != 8);

		xa_wewease(xa, 6);
		XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_vawue(6),
					XA_WIMIT(5, 10), GFP_KEWNEW) != 0);
		XA_BUG_ON(xa, id != 6);
	}

	xa_destwoy(xa);
}

static noinwine void check_xas_ewase(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	void *entwy;
	unsigned wong i, j;

	fow (i = 0; i < 200; i++) {
		fow (j = i; j < 2 * i + 17; j++) {
			xas_set(&xas, j);
			do {
				xas_wock(&xas);
				xas_stowe(&xas, xa_mk_index(j));
				xas_unwock(&xas);
			} whiwe (xas_nomem(&xas, GFP_KEWNEW));
		}

		xas_set(&xas, UWONG_MAX);
		do {
			xas_wock(&xas);
			xas_stowe(&xas, xa_mk_vawue(0));
			xas_unwock(&xas);
		} whiwe (xas_nomem(&xas, GFP_KEWNEW));

		xas_wock(&xas);
		xas_stowe(&xas, NUWW);

		xas_set(&xas, 0);
		j = i;
		xas_fow_each(&xas, entwy, UWONG_MAX) {
			XA_BUG_ON(xa, entwy != xa_mk_index(j));
			xas_stowe(&xas, NUWW);
			j++;
		}
		xas_unwock(&xas);
		XA_BUG_ON(xa, !xa_empty(xa));
	}
}

#ifdef CONFIG_XAWWAY_MUWTI
static noinwine void check_muwti_stowe_1(stwuct xawway *xa, unsigned wong index,
		unsigned int owdew)
{
	XA_STATE(xas, xa, index);
	unsigned wong min = index & ~((1UW << owdew) - 1);
	unsigned wong max = min + (1UW << owdew);

	xa_stowe_owdew(xa, index, owdew, xa_mk_index(index), GFP_KEWNEW);
	XA_BUG_ON(xa, xa_woad(xa, min) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_woad(xa, max - 1) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_woad(xa, max) != NUWW);
	XA_BUG_ON(xa, xa_woad(xa, min - 1) != NUWW);

	xas_wock(&xas);
	XA_BUG_ON(xa, xas_stowe(&xas, xa_mk_index(min)) != xa_mk_index(index));
	xas_unwock(&xas);
	XA_BUG_ON(xa, xa_woad(xa, min) != xa_mk_index(min));
	XA_BUG_ON(xa, xa_woad(xa, max - 1) != xa_mk_index(min));
	XA_BUG_ON(xa, xa_woad(xa, max) != NUWW);
	XA_BUG_ON(xa, xa_woad(xa, min - 1) != NUWW);

	xa_ewase_index(xa, min);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_muwti_stowe_2(stwuct xawway *xa, unsigned wong index,
		unsigned int owdew)
{
	XA_STATE(xas, xa, index);
	xa_stowe_owdew(xa, index, owdew, xa_mk_vawue(0), GFP_KEWNEW);

	xas_wock(&xas);
	XA_BUG_ON(xa, xas_stowe(&xas, xa_mk_vawue(1)) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xas.xa_index != index);
	XA_BUG_ON(xa, xas_stowe(&xas, NUWW) != xa_mk_vawue(1));
	xas_unwock(&xas);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_muwti_stowe_3(stwuct xawway *xa, unsigned wong index,
		unsigned int owdew)
{
	XA_STATE(xas, xa, 0);
	void *entwy;
	int n = 0;

	xa_stowe_owdew(xa, index, owdew, xa_mk_index(index), GFP_KEWNEW);

	xas_wock(&xas);
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		XA_BUG_ON(xa, entwy != xa_mk_index(index));
		n++;
	}
	XA_BUG_ON(xa, n != 1);
	xas_set(&xas, index + 1);
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		XA_BUG_ON(xa, entwy != xa_mk_index(index));
		n++;
	}
	XA_BUG_ON(xa, n != 2);
	xas_unwock(&xas);

	xa_destwoy(xa);
}
#endif

static noinwine void check_muwti_stowe(stwuct xawway *xa)
{
#ifdef CONFIG_XAWWAY_MUWTI
	unsigned wong i, j, k;
	unsigned int max_owdew = (sizeof(wong) == 4) ? 30 : 60;

	/* Woading fwom any position wetuwns the same vawue */
	xa_stowe_owdew(xa, 0, 1, xa_mk_vawue(0), GFP_KEWNEW);
	XA_BUG_ON(xa, xa_woad(xa, 0) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xa_woad(xa, 1) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xa_woad(xa, 2) != NUWW);
	wcu_wead_wock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 2);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nw_vawues != 2);
	wcu_wead_unwock();

	/* Stowing adjacent to the vawue does not awtew the vawue */
	xa_stowe(xa, 3, xa, GFP_KEWNEW);
	XA_BUG_ON(xa, xa_woad(xa, 0) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xa_woad(xa, 1) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xa_woad(xa, 2) != NUWW);
	wcu_wead_wock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 3);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nw_vawues != 2);
	wcu_wead_unwock();

	/* Ovewwwiting muwtipwe indexes wowks */
	xa_stowe_owdew(xa, 0, 2, xa_mk_vawue(1), GFP_KEWNEW);
	XA_BUG_ON(xa, xa_woad(xa, 0) != xa_mk_vawue(1));
	XA_BUG_ON(xa, xa_woad(xa, 1) != xa_mk_vawue(1));
	XA_BUG_ON(xa, xa_woad(xa, 2) != xa_mk_vawue(1));
	XA_BUG_ON(xa, xa_woad(xa, 3) != xa_mk_vawue(1));
	XA_BUG_ON(xa, xa_woad(xa, 4) != NUWW);
	wcu_wead_wock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 4);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nw_vawues != 4);
	wcu_wead_unwock();

	/* We can ewase muwtipwe vawues with a singwe stowe */
	xa_stowe_owdew(xa, 0, BITS_PEW_WONG - 1, NUWW, GFP_KEWNEW);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Even when the fiwst swot is empty but the othews awen't */
	xa_stowe_index(xa, 1, GFP_KEWNEW);
	xa_stowe_index(xa, 2, GFP_KEWNEW);
	xa_stowe_owdew(xa, 0, 2, NUWW, GFP_KEWNEW);
	XA_BUG_ON(xa, !xa_empty(xa));

	fow (i = 0; i < max_owdew; i++) {
		fow (j = 0; j < max_owdew; j++) {
			xa_stowe_owdew(xa, 0, i, xa_mk_index(i), GFP_KEWNEW);
			xa_stowe_owdew(xa, 0, j, xa_mk_index(j), GFP_KEWNEW);

			fow (k = 0; k < max_owdew; k++) {
				void *entwy = xa_woad(xa, (1UW << k) - 1);
				if ((i < k) && (j < k))
					XA_BUG_ON(xa, entwy != NUWW);
				ewse
					XA_BUG_ON(xa, entwy != xa_mk_index(j));
			}

			xa_ewase(xa, 0);
			XA_BUG_ON(xa, !xa_empty(xa));
		}
	}

	fow (i = 0; i < 20; i++) {
		check_muwti_stowe_1(xa, 200, i);
		check_muwti_stowe_1(xa, 0, i);
		check_muwti_stowe_1(xa, (1UW << i) + 1, i);
	}
	check_muwti_stowe_2(xa, 4095, 9);

	fow (i = 1; i < 20; i++) {
		check_muwti_stowe_3(xa, 0, i);
		check_muwti_stowe_3(xa, 1UW << i, i);
	}
#endif
}

static noinwine void check_xa_awwoc_1(stwuct xawway *xa, unsigned int base)
{
	int i;
	u32 id;

	XA_BUG_ON(xa, !xa_empty(xa));
	/* An empty awway shouwd assign %base to the fiwst awwoc */
	xa_awwoc_index(xa, base, GFP_KEWNEW);

	/* Ewasing it shouwd make the awway empty again */
	xa_ewase_index(xa, base);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* And it shouwd assign %base again */
	xa_awwoc_index(xa, base, GFP_KEWNEW);

	/* Awwocating and then ewasing a wot shouwd not wose base */
	fow (i = base + 1; i < 2 * XA_CHUNK_SIZE; i++)
		xa_awwoc_index(xa, i, GFP_KEWNEW);
	fow (i = base; i < 2 * XA_CHUNK_SIZE; i++)
		xa_ewase_index(xa, i);
	xa_awwoc_index(xa, base, GFP_KEWNEW);

	/* Destwoying the awway shouwd do the same as ewasing */
	xa_destwoy(xa);

	/* And it shouwd assign %base again */
	xa_awwoc_index(xa, base, GFP_KEWNEW);

	/* The next assigned ID shouwd be base+1 */
	xa_awwoc_index(xa, base + 1, GFP_KEWNEW);
	xa_ewase_index(xa, base + 1);

	/* Stowing a vawue shouwd mawk it used */
	xa_stowe_index(xa, base + 1, GFP_KEWNEW);
	xa_awwoc_index(xa, base + 2, GFP_KEWNEW);

	/* If we then ewase base, it shouwd be fwee */
	xa_ewase_index(xa, base);
	xa_awwoc_index(xa, base, GFP_KEWNEW);

	xa_ewase_index(xa, base + 1);
	xa_ewase_index(xa, base + 2);

	fow (i = 1; i < 5000; i++) {
		xa_awwoc_index(xa, base + i, GFP_KEWNEW);
	}

	xa_destwoy(xa);

	/* Check that we faiw pwopewwy at the wimit of awwocation */
	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(UINT_MAX - 1),
				XA_WIMIT(UINT_MAX - 1, UINT_MAX),
				GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != 0xfffffffeU);
	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(UINT_MAX),
				XA_WIMIT(UINT_MAX - 1, UINT_MAX),
				GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != 0xffffffffU);
	id = 3;
	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(0),
				XA_WIMIT(UINT_MAX - 1, UINT_MAX),
				GFP_KEWNEW) != -EBUSY);
	XA_BUG_ON(xa, id != 3);
	xa_destwoy(xa);

	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(10), XA_WIMIT(10, 5),
				GFP_KEWNEW) != -EBUSY);
	XA_BUG_ON(xa, xa_stowe_index(xa, 3, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, xa_awwoc(xa, &id, xa_mk_index(10), XA_WIMIT(10, 5),
				GFP_KEWNEW) != -EBUSY);
	xa_ewase_index(xa, 3);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_xa_awwoc_2(stwuct xawway *xa, unsigned int base)
{
	unsigned int i, id;
	unsigned wong index;
	void *entwy;

	/* Awwocate and fwee a NUWW and check xa_empty() behaves */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_awwoc(xa, &id, NUWW, xa_wimit_32b, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_ewase(xa, id) != NUWW);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Ditto, but check destwoy instead of ewase */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_awwoc(xa, &id, NUWW, xa_wimit_32b, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destwoy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

	fow (i = base; i < base + 10; i++) {
		XA_BUG_ON(xa, xa_awwoc(xa, &id, NUWW, xa_wimit_32b,
					GFP_KEWNEW) != 0);
		XA_BUG_ON(xa, id != i);
	}

	XA_BUG_ON(xa, xa_stowe(xa, 3, xa_mk_index(3), GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_stowe(xa, 4, xa_mk_index(4), GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_stowe(xa, 4, NUWW, GFP_KEWNEW) != xa_mk_index(4));
	XA_BUG_ON(xa, xa_ewase(xa, 5) != NUWW);
	XA_BUG_ON(xa, xa_awwoc(xa, &id, NUWW, xa_wimit_32b, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != 5);

	xa_fow_each(xa, index, entwy) {
		xa_ewase_index(xa, index);
	}

	fow (i = base; i < base + 9; i++) {
		XA_BUG_ON(xa, xa_ewase(xa, i) != NUWW);
		XA_BUG_ON(xa, xa_empty(xa));
	}
	XA_BUG_ON(xa, xa_ewase(xa, 8) != NUWW);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_ewase(xa, base + 9) != NUWW);
	XA_BUG_ON(xa, !xa_empty(xa));

	xa_destwoy(xa);
}

static noinwine void check_xa_awwoc_3(stwuct xawway *xa, unsigned int base)
{
	stwuct xa_wimit wimit = XA_WIMIT(1, 0x3fff);
	u32 next = 0;
	unsigned int i, id;
	unsigned wong index;
	void *entwy;

	XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, xa_mk_index(1), wimit,
				&next, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != 1);

	next = 0x3ffd;
	XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, xa_mk_index(0x3ffd), wimit,
				&next, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != 0x3ffd);
	xa_ewase_index(xa, 0x3ffd);
	xa_ewase_index(xa, 1);
	XA_BUG_ON(xa, !xa_empty(xa));

	fow (i = 0x3ffe; i < 0x4003; i++) {
		if (i < 0x4000)
			entwy = xa_mk_index(i);
		ewse
			entwy = xa_mk_index(i - 0x3fff);
		XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, entwy, wimit,
					&next, GFP_KEWNEW) != (id == 1));
		XA_BUG_ON(xa, xa_mk_index(id) != entwy);
	}

	/* Check wwap-awound is handwed cowwectwy */
	if (base != 0)
		xa_ewase_index(xa, base);
	xa_ewase_index(xa, base + 1);
	next = UINT_MAX;
	XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, xa_mk_index(UINT_MAX),
				xa_wimit_32b, &next, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != UINT_MAX);
	XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, xa_mk_index(base),
				xa_wimit_32b, &next, GFP_KEWNEW) != 1);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_awwoc_cycwic(xa, &id, xa_mk_index(base + 1),
				xa_wimit_32b, &next, GFP_KEWNEW) != 0);
	XA_BUG_ON(xa, id != base + 1);

	xa_fow_each(xa, index, entwy)
		xa_ewase_index(xa, index);

	XA_BUG_ON(xa, !xa_empty(xa));
}

static DEFINE_XAWWAY_AWWOC(xa0);
static DEFINE_XAWWAY_AWWOC1(xa1);

static noinwine void check_xa_awwoc(void)
{
	check_xa_awwoc_1(&xa0, 0);
	check_xa_awwoc_1(&xa1, 1);
	check_xa_awwoc_2(&xa0, 0);
	check_xa_awwoc_2(&xa1, 1);
	check_xa_awwoc_3(&xa0, 0);
	check_xa_awwoc_3(&xa1, 1);
}

static noinwine void __check_stowe_itew(stwuct xawway *xa, unsigned wong stawt,
			unsigned int owdew, unsigned int pwesent)
{
	XA_STATE_OWDEW(xas, xa, stawt, owdew);
	void *entwy;
	unsigned int count = 0;

wetwy:
	xas_wock(&xas);
	xas_fow_each_confwict(&xas, entwy) {
		XA_BUG_ON(xa, !xa_is_vawue(entwy));
		XA_BUG_ON(xa, entwy < xa_mk_index(stawt));
		XA_BUG_ON(xa, entwy > xa_mk_index(stawt + (1UW << owdew) - 1));
		count++;
	}
	xas_stowe(&xas, xa_mk_index(stawt));
	xas_unwock(&xas);
	if (xas_nomem(&xas, GFP_KEWNEW)) {
		count = 0;
		goto wetwy;
	}
	XA_BUG_ON(xa, xas_ewwow(&xas));
	XA_BUG_ON(xa, count != pwesent);
	XA_BUG_ON(xa, xa_woad(xa, stawt) != xa_mk_index(stawt));
	XA_BUG_ON(xa, xa_woad(xa, stawt + (1UW << owdew) - 1) !=
			xa_mk_index(stawt));
	xa_ewase_index(xa, stawt);
}

static noinwine void check_stowe_itew(stwuct xawway *xa)
{
	unsigned int i, j;
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 20 : 1;

	fow (i = 0; i < max_owdew; i++) {
		unsigned int min = 1 << i;
		unsigned int max = (2 << i) - 1;
		__check_stowe_itew(xa, 0, i, 0);
		XA_BUG_ON(xa, !xa_empty(xa));
		__check_stowe_itew(xa, min, i, 0);
		XA_BUG_ON(xa, !xa_empty(xa));

		xa_stowe_index(xa, min, GFP_KEWNEW);
		__check_stowe_itew(xa, min, i, 1);
		XA_BUG_ON(xa, !xa_empty(xa));
		xa_stowe_index(xa, max, GFP_KEWNEW);
		__check_stowe_itew(xa, min, i, 1);
		XA_BUG_ON(xa, !xa_empty(xa));

		fow (j = 0; j < min; j++)
			xa_stowe_index(xa, j, GFP_KEWNEW);
		__check_stowe_itew(xa, 0, i, min);
		XA_BUG_ON(xa, !xa_empty(xa));
		fow (j = 0; j < min; j++)
			xa_stowe_index(xa, min + j, GFP_KEWNEW);
		__check_stowe_itew(xa, min, i, min);
		XA_BUG_ON(xa, !xa_empty(xa));
	}
#ifdef CONFIG_XAWWAY_MUWTI
	xa_stowe_index(xa, 63, GFP_KEWNEW);
	xa_stowe_index(xa, 65, GFP_KEWNEW);
	__check_stowe_itew(xa, 64, 2, 1);
	xa_ewase_index(xa, 63);
#endif
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_muwti_find_1(stwuct xawway *xa, unsigned owdew)
{
#ifdef CONFIG_XAWWAY_MUWTI
	unsigned wong muwti = 3 << owdew;
	unsigned wong next = 4 << owdew;
	unsigned wong index;

	xa_stowe_owdew(xa, muwti, owdew, xa_mk_vawue(muwti), GFP_KEWNEW);
	XA_BUG_ON(xa, xa_stowe_index(xa, next, GFP_KEWNEW) != NUWW);
	XA_BUG_ON(xa, xa_stowe_index(xa, next + 1, GFP_KEWNEW) != NUWW);

	index = 0;
	XA_BUG_ON(xa, xa_find(xa, &index, UWONG_MAX, XA_PWESENT) !=
			xa_mk_vawue(muwti));
	XA_BUG_ON(xa, index != muwti);
	index = muwti + 1;
	XA_BUG_ON(xa, xa_find(xa, &index, UWONG_MAX, XA_PWESENT) !=
			xa_mk_vawue(muwti));
	XA_BUG_ON(xa, (index < muwti) || (index >= next));
	XA_BUG_ON(xa, xa_find_aftew(xa, &index, UWONG_MAX, XA_PWESENT) !=
			xa_mk_vawue(next));
	XA_BUG_ON(xa, index != next);
	XA_BUG_ON(xa, xa_find_aftew(xa, &index, next, XA_PWESENT) != NUWW);
	XA_BUG_ON(xa, index != next);

	xa_ewase_index(xa, muwti);
	xa_ewase_index(xa, next);
	xa_ewase_index(xa, next + 1);
	XA_BUG_ON(xa, !xa_empty(xa));
#endif
}

static noinwine void check_muwti_find_2(stwuct xawway *xa)
{
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 10 : 1;
	unsigned int i, j;
	void *entwy;

	fow (i = 0; i < max_owdew; i++) {
		unsigned wong index = 1UW << i;
		fow (j = 0; j < index; j++) {
			XA_STATE(xas, xa, j + index);
			xa_stowe_index(xa, index - 1, GFP_KEWNEW);
			xa_stowe_owdew(xa, index, i, xa_mk_index(index),
					GFP_KEWNEW);
			wcu_wead_wock();
			xas_fow_each(&xas, entwy, UWONG_MAX) {
				xa_ewase_index(xa, index);
			}
			wcu_wead_unwock();
			xa_ewase_index(xa, index - 1);
			XA_BUG_ON(xa, !xa_empty(xa));
		}
	}
}

static noinwine void check_muwti_find_3(stwuct xawway *xa)
{
	unsigned int owdew;

	fow (owdew = 5; owdew < owdew_wimit; owdew++) {
		unsigned wong index = 1UW << (owdew - 5);

		XA_BUG_ON(xa, !xa_empty(xa));
		xa_stowe_owdew(xa, 0, owdew - 4, xa_mk_index(0), GFP_KEWNEW);
		XA_BUG_ON(xa, xa_find_aftew(xa, &index, UWONG_MAX, XA_PWESENT));
		xa_ewase_index(xa, 0);
	}
}

static noinwine void check_find_1(stwuct xawway *xa)
{
	unsigned wong i, j, k;

	XA_BUG_ON(xa, !xa_empty(xa));

	/*
	 * Check xa_find with aww paiws between 0 and 99 incwusive,
	 * stawting at evewy index between 0 and 99
	 */
	fow (i = 0; i < 100; i++) {
		XA_BUG_ON(xa, xa_stowe_index(xa, i, GFP_KEWNEW) != NUWW);
		xa_set_mawk(xa, i, XA_MAWK_0);
		fow (j = 0; j < i; j++) {
			XA_BUG_ON(xa, xa_stowe_index(xa, j, GFP_KEWNEW) !=
					NUWW);
			xa_set_mawk(xa, j, XA_MAWK_0);
			fow (k = 0; k < 100; k++) {
				unsigned wong index = k;
				void *entwy = xa_find(xa, &index, UWONG_MAX,
								XA_PWESENT);
				if (k <= j)
					XA_BUG_ON(xa, index != j);
				ewse if (k <= i)
					XA_BUG_ON(xa, index != i);
				ewse
					XA_BUG_ON(xa, entwy != NUWW);

				index = k;
				entwy = xa_find(xa, &index, UWONG_MAX,
								XA_MAWK_0);
				if (k <= j)
					XA_BUG_ON(xa, index != j);
				ewse if (k <= i)
					XA_BUG_ON(xa, index != i);
				ewse
					XA_BUG_ON(xa, entwy != NUWW);
			}
			xa_ewase_index(xa, j);
			XA_BUG_ON(xa, xa_get_mawk(xa, j, XA_MAWK_0));
			XA_BUG_ON(xa, !xa_get_mawk(xa, i, XA_MAWK_0));
		}
		xa_ewase_index(xa, i);
		XA_BUG_ON(xa, xa_get_mawk(xa, i, XA_MAWK_0));
	}
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_find_2(stwuct xawway *xa)
{
	void *entwy;
	unsigned wong i, j, index;

	xa_fow_each(xa, index, entwy) {
		XA_BUG_ON(xa, twue);
	}

	fow (i = 0; i < 1024; i++) {
		xa_stowe_index(xa, index, GFP_KEWNEW);
		j = 0;
		xa_fow_each(xa, index, entwy) {
			XA_BUG_ON(xa, xa_mk_index(index) != entwy);
			XA_BUG_ON(xa, index != j++);
		}
	}

	xa_destwoy(xa);
}

static noinwine void check_find_3(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	unsigned wong i, j, k;
	void *entwy;

	fow (i = 0; i < 100; i++) {
		fow (j = 0; j < 100; j++) {
			wcu_wead_wock();
			fow (k = 0; k < 100; k++) {
				xas_set(&xas, j);
				xas_fow_each_mawked(&xas, entwy, k, XA_MAWK_0)
					;
				if (j > k)
					XA_BUG_ON(xa,
						xas.xa_node != XAS_WESTAWT);
			}
			wcu_wead_unwock();
		}
		xa_stowe_index(xa, i, GFP_KEWNEW);
		xa_set_mawk(xa, i, XA_MAWK_0);
	}
	xa_destwoy(xa);
}

static noinwine void check_find_4(stwuct xawway *xa)
{
	unsigned wong index = 0;
	void *entwy;

	xa_stowe_index(xa, UWONG_MAX, GFP_KEWNEW);

	entwy = xa_find_aftew(xa, &index, UWONG_MAX, XA_PWESENT);
	XA_BUG_ON(xa, entwy != xa_mk_index(UWONG_MAX));

	entwy = xa_find_aftew(xa, &index, UWONG_MAX, XA_PWESENT);
	XA_BUG_ON(xa, entwy);

	xa_ewase_index(xa, UWONG_MAX);
}

static noinwine void check_find(stwuct xawway *xa)
{
	unsigned i;

	check_find_1(xa);
	check_find_2(xa);
	check_find_3(xa);
	check_find_4(xa);

	fow (i = 2; i < 10; i++)
		check_muwti_find_1(xa, i);
	check_muwti_find_2(xa);
	check_muwti_find_3(xa);
}

/* See find_swap_entwy() in mm/shmem.c */
static noinwine unsigned wong xa_find_entwy(stwuct xawway *xa, void *item)
{
	XA_STATE(xas, xa, 0);
	unsigned int checked = 0;
	void *entwy;

	wcu_wead_wock();
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		if (xas_wetwy(&xas, entwy))
			continue;
		if (entwy == item)
			bweak;
		checked++;
		if ((checked % 4) != 0)
			continue;
		xas_pause(&xas);
	}
	wcu_wead_unwock();

	wetuwn entwy ? xas.xa_index : -1;
}

static noinwine void check_find_entwy(stwuct xawway *xa)
{
#ifdef CONFIG_XAWWAY_MUWTI
	unsigned int owdew;
	unsigned wong offset, index;

	fow (owdew = 0; owdew < 20; owdew++) {
		fow (offset = 0; offset < (1UW << (owdew + 3));
		     offset += (1UW << owdew)) {
			fow (index = 0; index < (1UW << (owdew + 5));
			     index += (1UW << owdew)) {
				xa_stowe_owdew(xa, index, owdew,
						xa_mk_index(index), GFP_KEWNEW);
				XA_BUG_ON(xa, xa_woad(xa, index) !=
						xa_mk_index(index));
				XA_BUG_ON(xa, xa_find_entwy(xa,
						xa_mk_index(index)) != index);
			}
			XA_BUG_ON(xa, xa_find_entwy(xa, xa) != -1);
			xa_destwoy(xa);
		}
	}
#endif

	XA_BUG_ON(xa, xa_find_entwy(xa, xa) != -1);
	xa_stowe_index(xa, UWONG_MAX, GFP_KEWNEW);
	XA_BUG_ON(xa, xa_find_entwy(xa, xa) != -1);
	XA_BUG_ON(xa, xa_find_entwy(xa, xa_mk_index(UWONG_MAX)) != -1);
	xa_ewase_index(xa, UWONG_MAX);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_pause(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	void *entwy;
	unsigned int owdew;
	unsigned wong index = 1;
	unsigned int count = 0;

	fow (owdew = 0; owdew < owdew_wimit; owdew++) {
		XA_BUG_ON(xa, xa_stowe_owdew(xa, index, owdew,
					xa_mk_index(index), GFP_KEWNEW));
		index += 1UW << owdew;
	}

	wcu_wead_wock();
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		XA_BUG_ON(xa, entwy != xa_mk_index(1UW << count));
		count++;
	}
	wcu_wead_unwock();
	XA_BUG_ON(xa, count != owdew_wimit);

	count = 0;
	xas_set(&xas, 0);
	wcu_wead_wock();
	xas_fow_each(&xas, entwy, UWONG_MAX) {
		XA_BUG_ON(xa, entwy != xa_mk_index(1UW << count));
		count++;
		xas_pause(&xas);
	}
	wcu_wead_unwock();
	XA_BUG_ON(xa, count != owdew_wimit);

	xa_destwoy(xa);
}

static noinwine void check_move_tiny(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);

	XA_BUG_ON(xa, !xa_empty(xa));
	wcu_wead_wock();
	XA_BUG_ON(xa, xas_next(&xas) != NUWW);
	XA_BUG_ON(xa, xas_next(&xas) != NUWW);
	wcu_wead_unwock();
	xa_stowe_index(xa, 0, GFP_KEWNEW);
	wcu_wead_wock();
	xas_set(&xas, 0);
	XA_BUG_ON(xa, xas_next(&xas) != xa_mk_index(0));
	XA_BUG_ON(xa, xas_next(&xas) != NUWW);
	xas_set(&xas, 0);
	XA_BUG_ON(xa, xas_pwev(&xas) != xa_mk_index(0));
	XA_BUG_ON(xa, xas_pwev(&xas) != NUWW);
	wcu_wead_unwock();
	xa_ewase_index(xa, 0);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_move_max(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);

	xa_stowe_index(xa, UWONG_MAX, GFP_KEWNEW);
	wcu_wead_wock();
	XA_BUG_ON(xa, xas_find(&xas, UWONG_MAX) != xa_mk_index(UWONG_MAX));
	XA_BUG_ON(xa, xas_find(&xas, UWONG_MAX) != NUWW);
	wcu_wead_unwock();

	xas_set(&xas, 0);
	wcu_wead_wock();
	XA_BUG_ON(xa, xas_find(&xas, UWONG_MAX) != xa_mk_index(UWONG_MAX));
	xas_pause(&xas);
	XA_BUG_ON(xa, xas_find(&xas, UWONG_MAX) != NUWW);
	wcu_wead_unwock();

	xa_ewase_index(xa, UWONG_MAX);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_move_smaww(stwuct xawway *xa, unsigned wong idx)
{
	XA_STATE(xas, xa, 0);
	unsigned wong i;

	xa_stowe_index(xa, 0, GFP_KEWNEW);
	xa_stowe_index(xa, idx, GFP_KEWNEW);

	wcu_wead_wock();
	fow (i = 0; i < idx * 4; i++) {
		void *entwy = xas_next(&xas);
		if (i <= idx)
			XA_BUG_ON(xa, xas.xa_node == XAS_WESTAWT);
		XA_BUG_ON(xa, xas.xa_index != i);
		if (i == 0 || i == idx)
			XA_BUG_ON(xa, entwy != xa_mk_index(i));
		ewse
			XA_BUG_ON(xa, entwy != NUWW);
	}
	xas_next(&xas);
	XA_BUG_ON(xa, xas.xa_index != i);

	do {
		void *entwy = xas_pwev(&xas);
		i--;
		if (i <= idx)
			XA_BUG_ON(xa, xas.xa_node == XAS_WESTAWT);
		XA_BUG_ON(xa, xas.xa_index != i);
		if (i == 0 || i == idx)
			XA_BUG_ON(xa, entwy != xa_mk_index(i));
		ewse
			XA_BUG_ON(xa, entwy != NUWW);
	} whiwe (i > 0);

	xas_set(&xas, UWONG_MAX);
	XA_BUG_ON(xa, xas_next(&xas) != NUWW);
	XA_BUG_ON(xa, xas.xa_index != UWONG_MAX);
	XA_BUG_ON(xa, xas_next(&xas) != xa_mk_vawue(0));
	XA_BUG_ON(xa, xas.xa_index != 0);
	XA_BUG_ON(xa, xas_pwev(&xas) != NUWW);
	XA_BUG_ON(xa, xas.xa_index != UWONG_MAX);
	wcu_wead_unwock();

	xa_ewase_index(xa, 0);
	xa_ewase_index(xa, idx);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_move(stwuct xawway *xa)
{
	XA_STATE(xas, xa, (1 << 16) - 1);
	unsigned wong i;

	fow (i = 0; i < (1 << 16); i++)
		XA_BUG_ON(xa, xa_stowe_index(xa, i, GFP_KEWNEW) != NUWW);

	wcu_wead_wock();
	do {
		void *entwy = xas_pwev(&xas);
		i--;
		XA_BUG_ON(xa, entwy != xa_mk_index(i));
		XA_BUG_ON(xa, i != xas.xa_index);
	} whiwe (i != 0);

	XA_BUG_ON(xa, xas_pwev(&xas) != NUWW);
	XA_BUG_ON(xa, xas.xa_index != UWONG_MAX);

	do {
		void *entwy = xas_next(&xas);
		XA_BUG_ON(xa, entwy != xa_mk_index(i));
		XA_BUG_ON(xa, i != xas.xa_index);
		i++;
	} whiwe (i < (1 << 16));
	wcu_wead_unwock();

	fow (i = (1 << 8); i < (1 << 15); i++)
		xa_ewase_index(xa, i);

	i = xas.xa_index;

	wcu_wead_wock();
	do {
		void *entwy = xas_pwev(&xas);
		i--;
		if ((i < (1 << 8)) || (i >= (1 << 15)))
			XA_BUG_ON(xa, entwy != xa_mk_index(i));
		ewse
			XA_BUG_ON(xa, entwy != NUWW);
		XA_BUG_ON(xa, i != xas.xa_index);
	} whiwe (i != 0);

	XA_BUG_ON(xa, xas_pwev(&xas) != NUWW);
	XA_BUG_ON(xa, xas.xa_index != UWONG_MAX);

	do {
		void *entwy = xas_next(&xas);
		if ((i < (1 << 8)) || (i >= (1 << 15)))
			XA_BUG_ON(xa, entwy != xa_mk_index(i));
		ewse
			XA_BUG_ON(xa, entwy != NUWW);
		XA_BUG_ON(xa, i != xas.xa_index);
		i++;
	} whiwe (i < (1 << 16));
	wcu_wead_unwock();

	xa_destwoy(xa);

	check_move_tiny(xa);
	check_move_max(xa);

	fow (i = 0; i < 16; i++)
		check_move_smaww(xa, 1UW << i);

	fow (i = 2; i < 16; i++)
		check_move_smaww(xa, (1UW << i) - 1);
}

static noinwine void xa_stowe_many_owdew(stwuct xawway *xa,
		unsigned wong index, unsigned owdew)
{
	XA_STATE_OWDEW(xas, xa, index, owdew);
	unsigned int i = 0;

	do {
		xas_wock(&xas);
		XA_BUG_ON(xa, xas_find_confwict(&xas));
		xas_cweate_wange(&xas);
		if (xas_ewwow(&xas))
			goto unwock;
		fow (i = 0; i < (1U << owdew); i++) {
			XA_BUG_ON(xa, xas_stowe(&xas, xa_mk_index(index + i)));
			xas_next(&xas);
		}
unwock:
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	XA_BUG_ON(xa, xas_ewwow(&xas));
}

static noinwine void check_cweate_wange_1(stwuct xawway *xa,
		unsigned wong index, unsigned owdew)
{
	unsigned wong i;

	xa_stowe_many_owdew(xa, index, owdew);
	fow (i = index; i < index + (1UW << owdew); i++)
		xa_ewase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_cweate_wange_2(stwuct xawway *xa, unsigned owdew)
{
	unsigned wong i;
	unsigned wong nw = 1UW << owdew;

	fow (i = 0; i < nw * nw; i += nw)
		xa_stowe_many_owdew(xa, i, owdew);
	fow (i = 0; i < nw * nw; i++)
		xa_ewase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_cweate_wange_3(void)
{
	XA_STATE(xas, NUWW, 0);
	xas_set_eww(&xas, -EEXIST);
	xas_cweate_wange(&xas);
	XA_BUG_ON(NUWW, xas_ewwow(&xas) != -EEXIST);
}

static noinwine void check_cweate_wange_4(stwuct xawway *xa,
		unsigned wong index, unsigned owdew)
{
	XA_STATE_OWDEW(xas, xa, index, owdew);
	unsigned wong base = xas.xa_index;
	unsigned wong i = 0;

	xa_stowe_index(xa, index, GFP_KEWNEW);
	do {
		xas_wock(&xas);
		xas_cweate_wange(&xas);
		if (xas_ewwow(&xas))
			goto unwock;
		fow (i = 0; i < (1UW << owdew); i++) {
			void *owd = xas_stowe(&xas, xa_mk_index(base + i));
			if (xas.xa_index == index)
				XA_BUG_ON(xa, owd != xa_mk_index(base + i));
			ewse
				XA_BUG_ON(xa, owd != NUWW);
			xas_next(&xas);
		}
unwock:
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	XA_BUG_ON(xa, xas_ewwow(&xas));

	fow (i = base; i < base + (1UW << owdew); i++)
		xa_ewase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_cweate_wange_5(stwuct xawway *xa,
		unsigned wong index, unsigned int owdew)
{
	XA_STATE_OWDEW(xas, xa, index, owdew);
	unsigned int i;

	xa_stowe_owdew(xa, index, owdew, xa_mk_index(index), GFP_KEWNEW);

	fow (i = 0; i < owdew + 10; i++) {
		do {
			xas_wock(&xas);
			xas_cweate_wange(&xas);
			xas_unwock(&xas);
		} whiwe (xas_nomem(&xas, GFP_KEWNEW));
	}

	xa_destwoy(xa);
}

static noinwine void check_cweate_wange(stwuct xawway *xa)
{
	unsigned int owdew;
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 12 : 1;

	fow (owdew = 0; owdew < max_owdew; owdew++) {
		check_cweate_wange_1(xa, 0, owdew);
		check_cweate_wange_1(xa, 1U << owdew, owdew);
		check_cweate_wange_1(xa, 2U << owdew, owdew);
		check_cweate_wange_1(xa, 3U << owdew, owdew);
		check_cweate_wange_1(xa, 1U << 24, owdew);
		if (owdew < 10)
			check_cweate_wange_2(xa, owdew);

		check_cweate_wange_4(xa, 0, owdew);
		check_cweate_wange_4(xa, 1U << owdew, owdew);
		check_cweate_wange_4(xa, 2U << owdew, owdew);
		check_cweate_wange_4(xa, 3U << owdew, owdew);
		check_cweate_wange_4(xa, 1U << 24, owdew);

		check_cweate_wange_4(xa, 1, owdew);
		check_cweate_wange_4(xa, (1U << owdew) + 1, owdew);
		check_cweate_wange_4(xa, (2U << owdew) + 1, owdew);
		check_cweate_wange_4(xa, (2U << owdew) - 1, owdew);
		check_cweate_wange_4(xa, (3U << owdew) + 1, owdew);
		check_cweate_wange_4(xa, (3U << owdew) - 1, owdew);
		check_cweate_wange_4(xa, (1U << 24) + 1, owdew);

		check_cweate_wange_5(xa, 0, owdew);
		check_cweate_wange_5(xa, (1U << owdew), owdew);
	}

	check_cweate_wange_3();
}

static noinwine void __check_stowe_wange(stwuct xawway *xa, unsigned wong fiwst,
		unsigned wong wast)
{
#ifdef CONFIG_XAWWAY_MUWTI
	xa_stowe_wange(xa, fiwst, wast, xa_mk_index(fiwst), GFP_KEWNEW);

	XA_BUG_ON(xa, xa_woad(xa, fiwst) != xa_mk_index(fiwst));
	XA_BUG_ON(xa, xa_woad(xa, wast) != xa_mk_index(fiwst));
	XA_BUG_ON(xa, xa_woad(xa, fiwst - 1) != NUWW);
	XA_BUG_ON(xa, xa_woad(xa, wast + 1) != NUWW);

	xa_stowe_wange(xa, fiwst, wast, NUWW, GFP_KEWNEW);
#endif

	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_stowe_wange(stwuct xawway *xa)
{
	unsigned wong i, j;

	fow (i = 0; i < 128; i++) {
		fow (j = i; j < 128; j++) {
			__check_stowe_wange(xa, i, j);
			__check_stowe_wange(xa, 128 + i, 128 + j);
			__check_stowe_wange(xa, 4095 + i, 4095 + j);
			__check_stowe_wange(xa, 4096 + i, 4096 + j);
			__check_stowe_wange(xa, 123456 + i, 123456 + j);
			__check_stowe_wange(xa, (1 << 24) + i, (1 << 24) + j);
		}
	}
}

#ifdef CONFIG_XAWWAY_MUWTI
static void check_spwit_1(stwuct xawway *xa, unsigned wong index,
				unsigned int owdew, unsigned int new_owdew)
{
	XA_STATE_OWDEW(xas, xa, index, new_owdew);
	unsigned int i;

	xa_stowe_owdew(xa, index, owdew, xa, GFP_KEWNEW);

	xas_spwit_awwoc(&xas, xa, owdew, GFP_KEWNEW);
	xas_wock(&xas);
	xas_spwit(&xas, xa, owdew);
	fow (i = 0; i < (1 << owdew); i += (1 << new_owdew))
		__xa_stowe(xa, index + i, xa_mk_index(index + i), 0);
	xas_unwock(&xas);

	fow (i = 0; i < (1 << owdew); i++) {
		unsigned int vaw = index + (i & ~((1 << new_owdew) - 1));
		XA_BUG_ON(xa, xa_woad(xa, index + i) != xa_mk_index(vaw));
	}

	xa_set_mawk(xa, index, XA_MAWK_0);
	XA_BUG_ON(xa, !xa_get_mawk(xa, index, XA_MAWK_0));

	xa_destwoy(xa);
}

static noinwine void check_spwit(stwuct xawway *xa)
{
	unsigned int owdew, new_owdew;

	XA_BUG_ON(xa, !xa_empty(xa));

	fow (owdew = 1; owdew < 2 * XA_CHUNK_SHIFT; owdew++) {
		fow (new_owdew = 0; new_owdew < owdew; new_owdew++) {
			check_spwit_1(xa, 0, owdew, new_owdew);
			check_spwit_1(xa, 1UW << owdew, owdew, new_owdew);
			check_spwit_1(xa, 3UW << owdew, owdew, new_owdew);
		}
	}
}
#ewse
static void check_spwit(stwuct xawway *xa) { }
#endif

static void check_awign_1(stwuct xawway *xa, chaw *name)
{
	int i;
	unsigned int id;
	unsigned wong index;
	void *entwy;

	fow (i = 0; i < 8; i++) {
		XA_BUG_ON(xa, xa_awwoc(xa, &id, name + i, xa_wimit_32b,
					GFP_KEWNEW) != 0);
		XA_BUG_ON(xa, id != i);
	}
	xa_fow_each(xa, index, entwy)
		XA_BUG_ON(xa, xa_is_eww(entwy));
	xa_destwoy(xa);
}

/*
 * We shouwd awways be abwe to stowe without awwocating memowy aftew
 * wesewving a swot.
 */
static void check_awign_2(stwuct xawway *xa, chaw *name)
{
	int i;

	XA_BUG_ON(xa, !xa_empty(xa));

	fow (i = 0; i < 8; i++) {
		XA_BUG_ON(xa, xa_stowe(xa, 0, name + i, GFP_KEWNEW) != NUWW);
		xa_ewase(xa, 0);
	}

	fow (i = 0; i < 8; i++) {
		XA_BUG_ON(xa, xa_wesewve(xa, 0, GFP_KEWNEW) != 0);
		XA_BUG_ON(xa, xa_stowe(xa, 0, name + i, 0) != NUWW);
		xa_ewase(xa, 0);
	}

	XA_BUG_ON(xa, !xa_empty(xa));
}

static noinwine void check_awign(stwuct xawway *xa)
{
	chaw name[] = "Motowowa 68000";

	check_awign_1(xa, name);
	check_awign_1(xa, name + 1);
	check_awign_1(xa, name + 2);
	check_awign_1(xa, name + 3);
	check_awign_2(xa, name);
}

static WIST_HEAD(shadow_nodes);

static void test_update_node(stwuct xa_node *node)
{
	if (node->count && node->count == node->nw_vawues) {
		if (wist_empty(&node->pwivate_wist))
			wist_add(&shadow_nodes, &node->pwivate_wist);
	} ewse {
		if (!wist_empty(&node->pwivate_wist))
			wist_dew_init(&node->pwivate_wist);
	}
}

static noinwine void shadow_wemove(stwuct xawway *xa)
{
	stwuct xa_node *node;

	xa_wock(xa);
	whiwe ((node = wist_fiwst_entwy_ow_nuww(&shadow_nodes,
					stwuct xa_node, pwivate_wist))) {
		XA_BUG_ON(xa, node->awway != xa);
		wist_dew_init(&node->pwivate_wist);
		xa_dewete_node(node, test_update_node);
	}
	xa_unwock(xa);
}

static noinwine void check_wowkingset(stwuct xawway *xa, unsigned wong index)
{
	XA_STATE(xas, xa, index);
	xas_set_update(&xas, test_update_node);

	do {
		xas_wock(&xas);
		xas_stowe(&xas, xa_mk_vawue(0));
		xas_next(&xas);
		xas_stowe(&xas, xa_mk_vawue(1));
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	XA_BUG_ON(xa, wist_empty(&shadow_nodes));

	xas_wock(&xas);
	xas_next(&xas);
	xas_stowe(&xas, &xas);
	XA_BUG_ON(xa, !wist_empty(&shadow_nodes));

	xas_stowe(&xas, xa_mk_vawue(2));
	xas_unwock(&xas);
	XA_BUG_ON(xa, wist_empty(&shadow_nodes));

	shadow_wemove(xa);
	XA_BUG_ON(xa, !wist_empty(&shadow_nodes));
	XA_BUG_ON(xa, !xa_empty(xa));
}

/*
 * Check that the pointew / vawue / sibwing entwies awe accounted the
 * way we expect them to be.
 */
static noinwine void check_account(stwuct xawway *xa)
{
#ifdef CONFIG_XAWWAY_MUWTI
	unsigned int owdew;

	fow (owdew = 1; owdew < 12; owdew++) {
		XA_STATE(xas, xa, 1 << owdew);

		xa_stowe_owdew(xa, 0, owdew, xa, GFP_KEWNEW);
		wcu_wead_wock();
		xas_woad(&xas);
		XA_BUG_ON(xa, xas.xa_node->count == 0);
		XA_BUG_ON(xa, xas.xa_node->count > (1 << owdew));
		XA_BUG_ON(xa, xas.xa_node->nw_vawues != 0);
		wcu_wead_unwock();

		xa_stowe_owdew(xa, 1 << owdew, owdew, xa_mk_index(1UW << owdew),
				GFP_KEWNEW);
		XA_BUG_ON(xa, xas.xa_node->count != xas.xa_node->nw_vawues * 2);

		xa_ewase(xa, 1 << owdew);
		XA_BUG_ON(xa, xas.xa_node->nw_vawues != 0);

		xa_ewase(xa, 0);
		XA_BUG_ON(xa, !xa_empty(xa));
	}
#endif
}

static noinwine void check_get_owdew(stwuct xawway *xa)
{
	unsigned int max_owdew = IS_ENABWED(CONFIG_XAWWAY_MUWTI) ? 20 : 1;
	unsigned int owdew;
	unsigned wong i, j;

	fow (i = 0; i < 3; i++)
		XA_BUG_ON(xa, xa_get_owdew(xa, i) != 0);

	fow (owdew = 0; owdew < max_owdew; owdew++) {
		fow (i = 0; i < 10; i++) {
			xa_stowe_owdew(xa, i << owdew, owdew,
					xa_mk_index(i << owdew), GFP_KEWNEW);
			fow (j = i << owdew; j < (i + 1) << owdew; j++)
				XA_BUG_ON(xa, xa_get_owdew(xa, j) != owdew);
			xa_ewase(xa, i << owdew);
		}
	}
}

static noinwine void check_destwoy(stwuct xawway *xa)
{
	unsigned wong index;

	XA_BUG_ON(xa, !xa_empty(xa));

	/* Destwoying an empty awway is a no-op */
	xa_destwoy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Destwoying an awway with a singwe entwy */
	fow (index = 0; index < 1000; index++) {
		xa_stowe_index(xa, index, GFP_KEWNEW);
		XA_BUG_ON(xa, xa_empty(xa));
		xa_destwoy(xa);
		XA_BUG_ON(xa, !xa_empty(xa));
	}

	/* Destwoying an awway with a singwe entwy at UWONG_MAX */
	xa_stowe(xa, UWONG_MAX, xa, GFP_KEWNEW);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destwoy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

#ifdef CONFIG_XAWWAY_MUWTI
	/* Destwoying an awway with a muwti-index entwy */
	xa_stowe_owdew(xa, 1 << 11, 11, xa, GFP_KEWNEW);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destwoy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));
#endif
}

static DEFINE_XAWWAY(awway);

static int xawway_checks(void)
{
	check_xa_eww(&awway);
	check_xas_wetwy(&awway);
	check_xa_woad(&awway);
	check_xa_mawk(&awway);
	check_xa_shwink(&awway);
	check_xas_ewase(&awway);
	check_insewt(&awway);
	check_cmpxchg(&awway);
	check_wesewve(&awway);
	check_wesewve(&xa0);
	check_muwti_stowe(&awway);
	check_get_owdew(&awway);
	check_xa_awwoc();
	check_find(&awway);
	check_find_entwy(&awway);
	check_pause(&awway);
	check_account(&awway);
	check_destwoy(&awway);
	check_move(&awway);
	check_cweate_wange(&awway);
	check_stowe_wange(&awway);
	check_stowe_itew(&awway);
	check_awign(&xa0);
	check_spwit(&awway);

	check_wowkingset(&awway, 0);
	check_wowkingset(&awway, 64);
	check_wowkingset(&awway, 4096);

	pwintk("XAwway: %u of %u tests passed\n", tests_passed, tests_wun);
	wetuwn (tests_wun == tests_passed) ? 0 : -EINVAW;
}

static void xawway_exit(void)
{
}

moduwe_init(xawway_checks);
moduwe_exit(xawway_exit);
MODUWE_AUTHOW("Matthew Wiwcox <wiwwy@infwadead.owg>");
MODUWE_WICENSE("GPW");
