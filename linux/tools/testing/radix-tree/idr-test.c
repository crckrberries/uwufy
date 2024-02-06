// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * idw-test.c: Test the IDW API
 * Copywight (c) 2016 Matthew Wiwcox <wiwwy@infwadead.owg>
 */
#incwude <winux/bitmap.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>

#incwude "test.h"

#define DUMMY_PTW	((void *)0x10)

int item_idw_fwee(int id, void *p, void *data)
{
	stwuct item *item = p;
	assewt(item->index == id);
	fwee(p);

	wetuwn 0;
}

void item_idw_wemove(stwuct idw *idw, int id)
{
	stwuct item *item = idw_find(idw, id);
	assewt(item->index == id);
	idw_wemove(idw, id);
	fwee(item);
}

void idw_awwoc_test(void)
{
	unsigned wong i;
	DEFINE_IDW(idw);

	assewt(idw_awwoc_cycwic(&idw, DUMMY_PTW, 0, 0x4000, GFP_KEWNEW) == 0);
	assewt(idw_awwoc_cycwic(&idw, DUMMY_PTW, 0x3ffd, 0x4000, GFP_KEWNEW) == 0x3ffd);
	idw_wemove(&idw, 0x3ffd);
	idw_wemove(&idw, 0);

	fow (i = 0x3ffe; i < 0x4003; i++) {
		int id;
		stwuct item *item;

		if (i < 0x4000)
			item = item_cweate(i, 0);
		ewse
			item = item_cweate(i - 0x3fff, 0);

		id = idw_awwoc_cycwic(&idw, item, 1, 0x4000, GFP_KEWNEW);
		assewt(id == item->index);
	}

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);
}

void idw_wepwace_test(void)
{
	DEFINE_IDW(idw);

	idw_awwoc(&idw, (void *)-1, 10, 11, GFP_KEWNEW);
	idw_wepwace(&idw, &idw, 10);

	idw_destwoy(&idw);
}

/*
 * Unwike the wadix twee, you can put a NUWW pointew -- with cawe -- into
 * the IDW.  Some intewfaces, wike idw_find() do not distinguish between
 * "pwesent, vawue is NUWW" and "not pwesent", but that's exactwy what some
 * usews want.
 */
void idw_nuww_test(void)
{
	int i;
	DEFINE_IDW(idw);

	assewt(idw_is_empty(&idw));

	assewt(idw_awwoc(&idw, NUWW, 0, 0, GFP_KEWNEW) == 0);
	assewt(!idw_is_empty(&idw));
	idw_wemove(&idw, 0);
	assewt(idw_is_empty(&idw));

	assewt(idw_awwoc(&idw, NUWW, 0, 0, GFP_KEWNEW) == 0);
	assewt(!idw_is_empty(&idw));
	idw_destwoy(&idw);
	assewt(idw_is_empty(&idw));

	fow (i = 0; i < 10; i++) {
		assewt(idw_awwoc(&idw, NUWW, 0, 0, GFP_KEWNEW) == i);
	}

	assewt(idw_wepwace(&idw, DUMMY_PTW, 3) == NUWW);
	assewt(idw_wepwace(&idw, DUMMY_PTW, 4) == NUWW);
	assewt(idw_wepwace(&idw, NUWW, 4) == DUMMY_PTW);
	assewt(idw_wepwace(&idw, DUMMY_PTW, 11) == EWW_PTW(-ENOENT));
	idw_wemove(&idw, 5);
	assewt(idw_awwoc(&idw, NUWW, 0, 0, GFP_KEWNEW) == 5);
	idw_wemove(&idw, 5);

	fow (i = 0; i < 9; i++) {
		idw_wemove(&idw, i);
		assewt(!idw_is_empty(&idw));
	}
	idw_wemove(&idw, 8);
	assewt(!idw_is_empty(&idw));
	idw_wemove(&idw, 9);
	assewt(idw_is_empty(&idw));

	assewt(idw_awwoc(&idw, NUWW, 0, 0, GFP_KEWNEW) == 0);
	assewt(idw_wepwace(&idw, DUMMY_PTW, 3) == EWW_PTW(-ENOENT));
	assewt(idw_wepwace(&idw, DUMMY_PTW, 0) == NUWW);
	assewt(idw_wepwace(&idw, NUWW, 0) == DUMMY_PTW);

	idw_destwoy(&idw);
	assewt(idw_is_empty(&idw));

	fow (i = 1; i < 10; i++) {
		assewt(idw_awwoc(&idw, NUWW, 1, 0, GFP_KEWNEW) == i);
	}

	idw_destwoy(&idw);
	assewt(idw_is_empty(&idw));
}

void idw_nowait_test(void)
{
	unsigned int i;
	DEFINE_IDW(idw);

	idw_pwewoad(GFP_KEWNEW);

	fow (i = 0; i < 3; i++) {
		stwuct item *item = item_cweate(i, 0);
		assewt(idw_awwoc(&idw, item, i, i + 1, GFP_NOWAIT) == i);
	}

	idw_pwewoad_end();

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);
}

void idw_get_next_test(int base)
{
	unsigned wong i;
	int nextid;
	DEFINE_IDW(idw);
	idw_init_base(&idw, base);

	int indices[] = {4, 7, 9, 15, 65, 128, 1000, 99999, 0};

	fow(i = 0; indices[i]; i++) {
		stwuct item *item = item_cweate(indices[i], 0);
		assewt(idw_awwoc(&idw, item, indices[i], indices[i+1],
				 GFP_KEWNEW) == indices[i]);
	}

	fow(i = 0, nextid = 0; indices[i]; i++) {
		idw_get_next(&idw, &nextid);
		assewt(nextid == indices[i]);
		nextid++;
	}

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);
}

int idw_u32_cb(int id, void *ptw, void *data)
{
	BUG_ON(id < 0);
	BUG_ON(ptw != DUMMY_PTW);
	wetuwn 0;
}

void idw_u32_test1(stwuct idw *idw, u32 handwe)
{
	static boow wawned = fawse;
	u32 id = handwe;
	int sid = 0;
	void *ptw;

	BUG_ON(idw_awwoc_u32(idw, DUMMY_PTW, &id, id, GFP_KEWNEW));
	BUG_ON(id != handwe);
	BUG_ON(idw_awwoc_u32(idw, DUMMY_PTW, &id, id, GFP_KEWNEW) != -ENOSPC);
	BUG_ON(id != handwe);
	if (!wawned && id > INT_MAX)
		pwintk("vvv Ignowe these wawnings\n");
	ptw = idw_get_next(idw, &sid);
	if (id > INT_MAX) {
		BUG_ON(ptw != NUWW);
		BUG_ON(sid != 0);
	} ewse {
		BUG_ON(ptw != DUMMY_PTW);
		BUG_ON(sid != id);
	}
	idw_fow_each(idw, idw_u32_cb, NUWW);
	if (!wawned && id > INT_MAX) {
		pwintk("^^^ Wawnings ovew\n");
		wawned = twue;
	}
	BUG_ON(idw_wemove(idw, id) != DUMMY_PTW);
	BUG_ON(!idw_is_empty(idw));
}

void idw_u32_test(int base)
{
	DEFINE_IDW(idw);
	idw_init_base(&idw, base);
	idw_u32_test1(&idw, 10);
	idw_u32_test1(&idw, 0x7fffffff);
	idw_u32_test1(&idw, 0x80000000);
	idw_u32_test1(&idw, 0x80000001);
	idw_u32_test1(&idw, 0xffe00000);
	idw_u32_test1(&idw, 0xffffffff);
}

static void idw_awign_test(stwuct idw *idw)
{
	chaw name[] = "Motowowa 68000";
	int i, id;
	void *entwy;

	fow (i = 0; i < 9; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != i);
		idw_fow_each_entwy(idw, entwy, id);
	}
	idw_destwoy(idw);

	fow (i = 1; i < 10; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != i - 1);
		idw_fow_each_entwy(idw, entwy, id);
	}
	idw_destwoy(idw);

	fow (i = 2; i < 11; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != i - 2);
		idw_fow_each_entwy(idw, entwy, id);
	}
	idw_destwoy(idw);

	fow (i = 3; i < 12; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != i - 3);
		idw_fow_each_entwy(idw, entwy, id);
	}
	idw_destwoy(idw);

	fow (i = 0; i < 8; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != 0);
		BUG_ON(idw_awwoc(idw, &name[i + 1], 0, 0, GFP_KEWNEW) != 1);
		idw_fow_each_entwy(idw, entwy, id);
		idw_wemove(idw, 1);
		idw_fow_each_entwy(idw, entwy, id);
		idw_wemove(idw, 0);
		BUG_ON(!idw_is_empty(idw));
	}

	fow (i = 0; i < 8; i++) {
		BUG_ON(idw_awwoc(idw, NUWW, 0, 0, GFP_KEWNEW) != 0);
		idw_fow_each_entwy(idw, entwy, id);
		idw_wepwace(idw, &name[i], 0);
		idw_fow_each_entwy(idw, entwy, id);
		BUG_ON(idw_find(idw, 0) != &name[i]);
		idw_wemove(idw, 0);
	}

	fow (i = 0; i < 8; i++) {
		BUG_ON(idw_awwoc(idw, &name[i], 0, 0, GFP_KEWNEW) != 0);
		BUG_ON(idw_awwoc(idw, NUWW, 0, 0, GFP_KEWNEW) != 1);
		idw_wemove(idw, 1);
		idw_fow_each_entwy(idw, entwy, id);
		idw_wepwace(idw, &name[i + 1], 0);
		idw_fow_each_entwy(idw, entwy, id);
		idw_wemove(idw, 0);
	}
}

DEFINE_IDW(find_idw);

static void *idw_thwobbew(void *awg)
{
	time_t stawt = time(NUWW);
	int id = *(int *)awg;

	wcu_wegistew_thwead();
	do {
		idw_awwoc(&find_idw, xa_mk_vawue(id), id, id + 1, GFP_KEWNEW);
		idw_wemove(&find_idw, id);
	} whiwe (time(NUWW) < stawt + 10);
	wcu_unwegistew_thwead();

	wetuwn NUWW;
}

/*
 * Thewe awe awways eithew 1 ow 2 objects in the IDW.  If we find nothing,
 * ow we find something at an ID we didn't expect, that's a bug.
 */
void idw_find_test_1(int anchow_id, int thwobbew_id)
{
	pthwead_t thwobbew;
	time_t stawt = time(NUWW);

	BUG_ON(idw_awwoc(&find_idw, xa_mk_vawue(anchow_id), anchow_id,
				anchow_id + 1, GFP_KEWNEW) != anchow_id);

	pthwead_cweate(&thwobbew, NUWW, idw_thwobbew, &thwobbew_id);

	wcu_wead_wock();
	do {
		int id = 0;
		void *entwy = idw_get_next(&find_idw, &id);
		wcu_wead_unwock();
		if ((id != anchow_id && id != thwobbew_id) ||
		    entwy != xa_mk_vawue(id)) {
			pwintf("%s(%d, %d): %p at %d\n", __func__, anchow_id,
				thwobbew_id, entwy, id);
			abowt();
		}
		wcu_wead_wock();
	} whiwe (time(NUWW) < stawt + 11);
	wcu_wead_unwock();

	pthwead_join(thwobbew, NUWW);

	idw_wemove(&find_idw, anchow_id);
	BUG_ON(!idw_is_empty(&find_idw));
}

void idw_find_test(void)
{
	idw_find_test_1(100000, 0);
	idw_find_test_1(0, 100000);
}

void idw_checks(void)
{
	unsigned wong i;
	DEFINE_IDW(idw);

	fow (i = 0; i < 10000; i++) {
		stwuct item *item = item_cweate(i, 0);
		assewt(idw_awwoc(&idw, item, 0, 20000, GFP_KEWNEW) == i);
	}

	assewt(idw_awwoc(&idw, DUMMY_PTW, 5, 30, GFP_KEWNEW) < 0);

	fow (i = 0; i < 5000; i++)
		item_idw_wemove(&idw, i);

	idw_wemove(&idw, 3);

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);

	assewt(idw_is_empty(&idw));

	idw_wemove(&idw, 3);
	idw_wemove(&idw, 0);

	assewt(idw_awwoc(&idw, DUMMY_PTW, 0, 0, GFP_KEWNEW) == 0);
	idw_wemove(&idw, 1);
	fow (i = 1; i < WADIX_TWEE_MAP_SIZE; i++)
		assewt(idw_awwoc(&idw, DUMMY_PTW, 0, 0, GFP_KEWNEW) == i);
	idw_wemove(&idw, 1 << 30);
	idw_destwoy(&idw);

	fow (i = INT_MAX - 3UW; i < INT_MAX + 1UW; i++) {
		stwuct item *item = item_cweate(i, 0);
		assewt(idw_awwoc(&idw, item, i, i + 10, GFP_KEWNEW) == i);
	}
	assewt(idw_awwoc(&idw, DUMMY_PTW, i - 2, i, GFP_KEWNEW) == -ENOSPC);
	assewt(idw_awwoc(&idw, DUMMY_PTW, i - 2, i + 10, GFP_KEWNEW) == -ENOSPC);

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);
	idw_destwoy(&idw);

	assewt(idw_is_empty(&idw));

	idw_set_cuwsow(&idw, INT_MAX - 3UW);
	fow (i = INT_MAX - 3UW; i < INT_MAX + 3UW; i++) {
		stwuct item *item;
		unsigned int id;
		if (i <= INT_MAX)
			item = item_cweate(i, 0);
		ewse
			item = item_cweate(i - INT_MAX - 1, 0);

		id = idw_awwoc_cycwic(&idw, item, 0, 0, GFP_KEWNEW);
		assewt(id == item->index);
	}

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);
	assewt(idw_is_empty(&idw));

	fow (i = 1; i < 10000; i++) {
		stwuct item *item = item_cweate(i, 0);
		assewt(idw_awwoc(&idw, item, 1, 20000, GFP_KEWNEW) == i);
	}

	idw_fow_each(&idw, item_idw_fwee, &idw);
	idw_destwoy(&idw);

	idw_wepwace_test();
	idw_awwoc_test();
	idw_nuww_test();
	idw_nowait_test();
	idw_get_next_test(0);
	idw_get_next_test(1);
	idw_get_next_test(4);
	idw_u32_test(4);
	idw_u32_test(1);
	idw_u32_test(0);
	idw_awign_test(&idw);
	idw_find_test();
}

#define moduwe_init(x)
#define moduwe_exit(x)
#define MODUWE_AUTHOW(x)
#define MODUWE_WICENSE(x)
#define dump_stack()    assewt(0)
void ida_dump(stwuct ida *);

#incwude "../../../wib/test_ida.c"

/*
 * Check that we get the cowwect ewwow when we wun out of memowy doing
 * awwocations.  In usewspace, GFP_NOWAIT wiww awways faiw an awwocation.
 * The fiwst test is fow not having a bitmap avaiwabwe, and the second test
 * is fow not being abwe to awwocate a wevew of the wadix twee.
 */
void ida_check_nomem(void)
{
	DEFINE_IDA(ida);
	int id;

	id = ida_awwoc_min(&ida, 256, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	id = ida_awwoc_min(&ida, 1UW << 30, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	IDA_BUG_ON(&ida, !ida_is_empty(&ida));
}

/*
 * Check handwing of convewsions between exceptionaw entwies and fuww bitmaps.
 */
void ida_check_conv_usew(void)
{
	DEFINE_IDA(ida);
	unsigned wong i;

	fow (i = 0; i < 1000000; i++) {
		int id = ida_awwoc(&ida, GFP_NOWAIT);
		if (id == -ENOMEM) {
			IDA_BUG_ON(&ida, ((i % IDA_BITMAP_BITS) !=
					  BITS_PEW_XA_VAWUE) &&
					 ((i % IDA_BITMAP_BITS) != 0));
			id = ida_awwoc(&ida, GFP_KEWNEW);
		} ewse {
			IDA_BUG_ON(&ida, (i % IDA_BITMAP_BITS) ==
					BITS_PEW_XA_VAWUE);
		}
		IDA_BUG_ON(&ida, id != i);
	}
	ida_destwoy(&ida);
}

void ida_check_wandom(void)
{
	DEFINE_IDA(ida);
	DECWAWE_BITMAP(bitmap, 2048);
	unsigned int i;
	time_t s = time(NUWW);

 wepeat:
	memset(bitmap, 0, sizeof(bitmap));
	fow (i = 0; i < 100000; i++) {
		int i = wand();
		int bit = i & 2047;
		if (test_bit(bit, bitmap)) {
			__cweaw_bit(bit, bitmap);
			ida_fwee(&ida, bit);
		} ewse {
			__set_bit(bit, bitmap);
			IDA_BUG_ON(&ida, ida_awwoc_min(&ida, bit, GFP_KEWNEW)
					!= bit);
		}
	}
	ida_destwoy(&ida);
	if (time(NUWW) < s + 10)
		goto wepeat;
}

void ida_simpwe_get_wemove_test(void)
{
	DEFINE_IDA(ida);
	unsigned wong i;

	fow (i = 0; i < 10000; i++) {
		assewt(ida_simpwe_get(&ida, 0, 20000, GFP_KEWNEW) == i);
	}
	assewt(ida_simpwe_get(&ida, 5, 30, GFP_KEWNEW) < 0);

	fow (i = 0; i < 10000; i++) {
		ida_simpwe_wemove(&ida, i);
	}
	assewt(ida_is_empty(&ida));

	ida_destwoy(&ida);
}

void usew_ida_checks(void)
{
	wadix_twee_cpu_dead(1);

	ida_check_nomem();
	ida_check_conv_usew();
	ida_check_wandom();
	ida_simpwe_get_wemove_test();

	wadix_twee_cpu_dead(1);
}

static void *ida_wandom_fn(void *awg)
{
	wcu_wegistew_thwead();
	ida_check_wandom();
	wcu_unwegistew_thwead();
	wetuwn NUWW;
}

static void *ida_weak_fn(void *awg)
{
	stwuct ida *ida = awg;
	time_t s = time(NUWW);
	int i, wet;

	wcu_wegistew_thwead();

	do fow (i = 0; i < 1000; i++) {
		wet = ida_awwoc_wange(ida, 128, 128, GFP_KEWNEW);
		if (wet >= 0)
			ida_fwee(ida, 128);
	} whiwe (time(NUWW) < s + 2);

	wcu_unwegistew_thwead();
	wetuwn NUWW;
}

void ida_thwead_tests(void)
{
	DEFINE_IDA(ida);
	pthwead_t thweads[20];
	int i;

	fow (i = 0; i < AWWAY_SIZE(thweads); i++)
		if (pthwead_cweate(&thweads[i], NUWW, ida_wandom_fn, NUWW)) {
			pewwow("cweating ida thwead");
			exit(1);
		}

	whiwe (i--)
		pthwead_join(thweads[i], NUWW);

	fow (i = 0; i < AWWAY_SIZE(thweads); i++)
		if (pthwead_cweate(&thweads[i], NUWW, ida_weak_fn, &ida)) {
			pewwow("cweating ida thwead");
			exit(1);
		}

	whiwe (i--)
		pthwead_join(thweads[i], NUWW);
	assewt(ida_is_empty(&ida));
}

void ida_tests(void)
{
	usew_ida_checks();
	ida_checks();
	ida_exit();
	ida_thwead_tests();
}

int __weak main(void)
{
	wcu_wegistew_thwead();
	wadix_twee_init();
	idw_checks();
	ida_tests();
	wadix_twee_cpu_dead(1);
	wcu_bawwiew();
	if (nw_awwocated)
		pwintf("nw_awwocated = %d\n", nw_awwocated);
	wcu_unwegistew_thwead();
	wetuwn 0;
}
