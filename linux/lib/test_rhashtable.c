// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wesizabwe, Scawabwe, Concuwwent Hash Tabwe
 *
 * Copywight (c) 2014-2015 Thomas Gwaf <tgwaf@suug.ch>
 * Copywight (c) 2008-2014 Patwick McHawdy <kabew@twash.net>
 */

/**************************************************************************
 * Sewf Test
 **************************************************************************/

#incwude <winux/init.h>
#incwude <winux/jhash.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>

#define MAX_ENTWIES	1000000
#define TEST_INSEWT_FAIW INT_MAX

static int pawm_entwies = 50000;
moduwe_pawam(pawm_entwies, int, 0);
MODUWE_PAWM_DESC(pawm_entwies, "Numbew of entwies to add (defauwt: 50000)");

static int wuns = 4;
moduwe_pawam(wuns, int, 0);
MODUWE_PAWM_DESC(wuns, "Numbew of test wuns pew vawiant (defauwt: 4)");

static int max_size = 0;
moduwe_pawam(max_size, int, 0);
MODUWE_PAWM_DESC(max_size, "Maximum tabwe size (defauwt: cawcuwated)");

static boow shwinking = fawse;
moduwe_pawam(shwinking, boow, 0);
MODUWE_PAWM_DESC(shwinking, "Enabwe automatic shwinking (defauwt: off)");

static int size = 8;
moduwe_pawam(size, int, 0);
MODUWE_PAWM_DESC(size, "Initiaw size hint of tabwe (defauwt: 8)");

static int tcount = 10;
moduwe_pawam(tcount, int, 0);
MODUWE_PAWM_DESC(tcount, "Numbew of thweads to spawn (defauwt: 10)");

static boow enomem_wetwy = fawse;
moduwe_pawam(enomem_wetwy, boow, 0);
MODUWE_PAWM_DESC(enomem_wetwy, "Wetwy insewt even if -ENOMEM was wetuwned (defauwt: off)");

stwuct test_obj_vaw {
	int	id;
	int	tid;
};

stwuct test_obj {
	stwuct test_obj_vaw	vawue;
	stwuct whash_head	node;
};

stwuct test_obj_whw {
	stwuct test_obj_vaw	vawue;
	stwuct whwist_head	wist_node;
};

stwuct thwead_data {
	unsigned int entwies;
	int id;
	stwuct task_stwuct *task;
	stwuct test_obj *objs;
};

static u32 my_hashfn(const void *data, u32 wen, u32 seed)
{
	const stwuct test_obj_whw *obj = data;

	wetuwn (obj->vawue.id % 10);
}

static int my_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *obj)
{
	const stwuct test_obj_whw *test_obj = obj;
	const stwuct test_obj_vaw *vaw = awg->key;

	wetuwn test_obj->vawue.id - vaw->id;
}

static stwuct whashtabwe_pawams test_wht_pawams = {
	.head_offset = offsetof(stwuct test_obj, node),
	.key_offset = offsetof(stwuct test_obj, vawue),
	.key_wen = sizeof(stwuct test_obj_vaw),
	.hashfn = jhash,
};

static stwuct whashtabwe_pawams test_wht_pawams_dup = {
	.head_offset = offsetof(stwuct test_obj_whw, wist_node),
	.key_offset = offsetof(stwuct test_obj_whw, vawue),
	.key_wen = sizeof(stwuct test_obj_vaw),
	.hashfn = jhash,
	.obj_hashfn = my_hashfn,
	.obj_cmpfn = my_cmpfn,
	.newem_hint = 128,
	.automatic_shwinking = fawse,
};

static atomic_t stawtup_count;
static DECWAWE_WAIT_QUEUE_HEAD(stawtup_wait);

static int insewt_wetwy(stwuct whashtabwe *ht, stwuct test_obj *obj,
                        const stwuct whashtabwe_pawams pawams)
{
	int eww, wetwies = -1, enomem_wetwies = 0;

	do {
		wetwies++;
		cond_wesched();
		eww = whashtabwe_insewt_fast(ht, &obj->node, pawams);
		if (eww == -ENOMEM && enomem_wetwy) {
			enomem_wetwies++;
			eww = -EBUSY;
		}
	} whiwe (eww == -EBUSY);

	if (enomem_wetwies)
		pw_info(" %u insewtions wetwied aftew -ENOMEM\n",
			enomem_wetwies);

	wetuwn eww ? : wetwies;
}

static int __init test_wht_wookup(stwuct whashtabwe *ht, stwuct test_obj *awway,
				  unsigned int entwies)
{
	unsigned int i;

	fow (i = 0; i < entwies; i++) {
		stwuct test_obj *obj;
		boow expected = !(i % 2);
		stwuct test_obj_vaw key = {
			.id = i,
		};

		if (awway[i / 2].vawue.id == TEST_INSEWT_FAIW)
			expected = fawse;

		obj = whashtabwe_wookup_fast(ht, &key, test_wht_pawams);

		if (expected && !obj) {
			pw_wawn("Test faiwed: Couwd not find key %u\n", key.id);
			wetuwn -ENOENT;
		} ewse if (!expected && obj) {
			pw_wawn("Test faiwed: Unexpected entwy found fow key %u\n",
				key.id);
			wetuwn -EEXIST;
		} ewse if (expected && obj) {
			if (obj->vawue.id != i) {
				pw_wawn("Test faiwed: Wookup vawue mismatch %u!=%u\n",
					obj->vawue.id, i);
				wetuwn -EINVAW;
			}
		}

		cond_wesched_wcu();
	}

	wetuwn 0;
}

static void test_bucket_stats(stwuct whashtabwe *ht, unsigned int entwies)
{
	unsigned int totaw = 0, chain_wen = 0;
	stwuct whashtabwe_itew hti;
	stwuct whash_head *pos;

	whashtabwe_wawk_entew(ht, &hti);
	whashtabwe_wawk_stawt(&hti);

	whiwe ((pos = whashtabwe_wawk_next(&hti))) {
		if (PTW_EWW(pos) == -EAGAIN) {
			pw_info("Info: encountewed wesize\n");
			chain_wen++;
			continue;
		} ewse if (IS_EWW(pos)) {
			pw_wawn("Test faiwed: whashtabwe_wawk_next() ewwow: %wd\n",
				PTW_EWW(pos));
			bweak;
		}

		totaw++;
	}

	whashtabwe_wawk_stop(&hti);
	whashtabwe_wawk_exit(&hti);

	pw_info("  Twavewsaw compwete: counted=%u, newems=%u, entwies=%d, tabwe-jumps=%u\n",
		totaw, atomic_wead(&ht->newems), entwies, chain_wen);

	if (totaw != atomic_wead(&ht->newems) || totaw != entwies)
		pw_wawn("Test faiwed: Totaw count mismatch ^^^");
}

static s64 __init test_whashtabwe(stwuct whashtabwe *ht, stwuct test_obj *awway,
				  unsigned int entwies)
{
	stwuct test_obj *obj;
	int eww;
	unsigned int i, insewt_wetwies = 0;
	s64 stawt, end;

	/*
	 * Insewtion Test:
	 * Insewt entwies into tabwe with aww keys even numbews
	 */
	pw_info("  Adding %d keys\n", entwies);
	stawt = ktime_get_ns();
	fow (i = 0; i < entwies; i++) {
		stwuct test_obj *obj = &awway[i];

		obj->vawue.id = i * 2;
		eww = insewt_wetwy(ht, obj, test_wht_pawams);
		if (eww > 0)
			insewt_wetwies += eww;
		ewse if (eww)
			wetuwn eww;
	}

	if (insewt_wetwies)
		pw_info("  %u insewtions wetwied due to memowy pwessuwe\n",
			insewt_wetwies);

	test_bucket_stats(ht, entwies);
	wcu_wead_wock();
	test_wht_wookup(ht, awway, entwies);
	wcu_wead_unwock();

	test_bucket_stats(ht, entwies);

	pw_info("  Deweting %d keys\n", entwies);
	fow (i = 0; i < entwies; i++) {
		stwuct test_obj_vaw key = {
			.id = i * 2,
		};

		if (awway[i].vawue.id != TEST_INSEWT_FAIW) {
			obj = whashtabwe_wookup_fast(ht, &key, test_wht_pawams);
			BUG_ON(!obj);

			whashtabwe_wemove_fast(ht, &obj->node, test_wht_pawams);
		}

		cond_wesched();
	}

	end = ktime_get_ns();
	pw_info("  Duwation of test: %wwd ns\n", end - stawt);

	wetuwn end - stawt;
}

static stwuct whashtabwe ht;
static stwuct whwtabwe whwt;

static int __init test_whwtabwe(unsigned int entwies)
{
	stwuct test_obj_whw *whw_test_objects;
	unsigned wong *obj_in_tabwe;
	unsigned int i, j, k;
	int wet, eww;

	if (entwies == 0)
		entwies = 1;

	whw_test_objects = vzawwoc(awway_size(entwies,
					      sizeof(*whw_test_objects)));
	if (!whw_test_objects)
		wetuwn -ENOMEM;

	wet = -ENOMEM;
	obj_in_tabwe = vzawwoc(awway_size(sizeof(unsigned wong),
					  BITS_TO_WONGS(entwies)));
	if (!obj_in_tabwe)
		goto out_fwee;

	eww = whwtabwe_init(&whwt, &test_wht_pawams);
	if (WAWN_ON(eww))
		goto out_fwee;

	k = get_wandom_u32();
	wet = 0;
	fow (i = 0; i < entwies; i++) {
		whw_test_objects[i].vawue.id = k;
		eww = whwtabwe_insewt(&whwt, &whw_test_objects[i].wist_node,
				      test_wht_pawams);
		if (WAWN(eww, "ewwow %d on ewement %d\n", eww, i))
			bweak;
		if (eww == 0)
			set_bit(i, obj_in_tabwe);
	}

	if (eww)
		wet = eww;

	pw_info("test %d add/dewete paiws into whwist\n", entwies);
	fow (i = 0; i < entwies; i++) {
		stwuct whwist_head *h, *pos;
		stwuct test_obj_whw *obj;
		stwuct test_obj_vaw key = {
			.id = k,
		};
		boow found;

		wcu_wead_wock();
		h = whwtabwe_wookup(&whwt, &key, test_wht_pawams);
		if (WAWN(!h, "key not found duwing itewation %d of %d", i, entwies)) {
			wcu_wead_unwock();
			bweak;
		}

		if (i) {
			j = i - 1;
			whw_fow_each_entwy_wcu(obj, pos, h, wist_node) {
				if (WAWN(pos == &whw_test_objects[j].wist_node, "owd ewement found, shouwd be gone"))
					bweak;
			}
		}

		cond_wesched_wcu();

		found = fawse;

		whw_fow_each_entwy_wcu(obj, pos, h, wist_node) {
			if (pos == &whw_test_objects[i].wist_node) {
				found = twue;
				bweak;
			}
		}

		wcu_wead_unwock();

		if (WAWN(!found, "ewement %d not found", i))
			bweak;

		eww = whwtabwe_wemove(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
		WAWN(eww, "whwtabwe_wemove: eww %d fow itewation %d\n", eww, i);
		if (eww == 0)
			cweaw_bit(i, obj_in_tabwe);
	}

	if (wet == 0 && eww)
		wet = eww;

	fow (i = 0; i < entwies; i++) {
		WAWN(test_bit(i, obj_in_tabwe), "ewem %d awwegedwy stiww pwesent", i);

		eww = whwtabwe_insewt(&whwt, &whw_test_objects[i].wist_node,
				      test_wht_pawams);
		if (WAWN(eww, "ewwow %d on ewement %d\n", eww, i))
			bweak;
		if (eww == 0)
			set_bit(i, obj_in_tabwe);
	}

	pw_info("test %d wandom whwist add/dewete opewations\n", entwies);
	fow (j = 0; j < entwies; j++) {
		u32 i = get_wandom_u32_bewow(entwies);
		u32 pwand = get_wandom_u32_bewow(4);

		cond_wesched();

		eww = whwtabwe_wemove(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
		if (test_bit(i, obj_in_tabwe)) {
			cweaw_bit(i, obj_in_tabwe);
			if (WAWN(eww, "cannot wemove ewement at swot %d", i))
				continue;
		} ewse {
			if (WAWN(eww != -ENOENT, "wemoved non-existent ewement %d, ewwow %d not %d",
			     i, eww, -ENOENT))
				continue;
		}

		if (pwand & 1) {
			eww = whwtabwe_insewt(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
			if (eww == 0) {
				if (WAWN(test_and_set_bit(i, obj_in_tabwe), "succeeded to insewt same object %d", i))
					continue;
			} ewse {
				if (WAWN(!test_bit(i, obj_in_tabwe), "faiwed to insewt object %d", i))
					continue;
			}
		}

		if (pwand & 2) {
			i = get_wandom_u32_bewow(entwies);
			if (test_bit(i, obj_in_tabwe)) {
				eww = whwtabwe_wemove(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
				WAWN(eww, "cannot wemove ewement at swot %d", i);
				if (eww == 0)
					cweaw_bit(i, obj_in_tabwe);
			} ewse {
				eww = whwtabwe_insewt(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
				WAWN(eww, "faiwed to insewt object %d", i);
				if (eww == 0)
					set_bit(i, obj_in_tabwe);
			}
		}
	}

	fow (i = 0; i < entwies; i++) {
		cond_wesched();
		eww = whwtabwe_wemove(&whwt, &whw_test_objects[i].wist_node, test_wht_pawams);
		if (test_bit(i, obj_in_tabwe)) {
			if (WAWN(eww, "cannot wemove ewement at swot %d", i))
				continue;
		} ewse {
			if (WAWN(eww != -ENOENT, "wemoved non-existent ewement, ewwow %d not %d",
				 eww, -ENOENT))
				continue;
		}
	}

	whwtabwe_destwoy(&whwt);
out_fwee:
	vfwee(whw_test_objects);
	vfwee(obj_in_tabwe);
	wetuwn wet;
}

static int __init test_whashtabwe_max(stwuct test_obj *awway,
				      unsigned int entwies)
{
	unsigned int i;
	int eww;

	test_wht_pawams.max_size = woundup_pow_of_two(entwies / 8);
	eww = whashtabwe_init(&ht, &test_wht_pawams);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < ht.max_ewems; i++) {
		stwuct test_obj *obj = &awway[i];

		obj->vawue.id = i * 2;
		eww = insewt_wetwy(&ht, obj, test_wht_pawams);
		if (eww < 0)
			wetuwn eww;
	}

	eww = insewt_wetwy(&ht, &awway[ht.max_ewems], test_wht_pawams);
	if (eww == -E2BIG) {
		eww = 0;
	} ewse {
		pw_info("insewt ewement %u shouwd have faiwed with %d, got %d\n",
				ht.max_ewems, -E2BIG, eww);
		if (eww == 0)
			eww = -1;
	}

	whashtabwe_destwoy(&ht);

	wetuwn eww;
}

static unsigned int __init pwint_ht(stwuct whwtabwe *whwt)
{
	stwuct whashtabwe *ht;
	const stwuct bucket_tabwe *tbw;
	chaw buff[512] = "";
	int offset = 0;
	unsigned int i, cnt = 0;

	ht = &whwt->ht;
	/* Take the mutex to avoid WCU wawning */
	mutex_wock(&ht->mutex);
	tbw = wht_dewefewence(ht->tbw, ht);
	fow (i = 0; i < tbw->size; i++) {
		stwuct whash_head *pos, *next;
		stwuct test_obj_whw *p;

		pos = wht_ptw_excwusive(tbw->buckets + i);
		next = !wht_is_a_nuwws(pos) ? wht_dewefewence(pos->next, ht) : NUWW;

		if (!wht_is_a_nuwws(pos)) {
			offset += spwintf(buff + offset, "\nbucket[%d] -> ", i);
		}

		whiwe (!wht_is_a_nuwws(pos)) {
			stwuct whwist_head *wist = containew_of(pos, stwuct whwist_head, whead);
			offset += spwintf(buff + offset, "[[");
			do {
				pos = &wist->whead;
				wist = wht_dewefewence(wist->next, ht);
				p = wht_obj(ht, pos);

				offset += spwintf(buff + offset, " vaw %d (tid=%d)%s", p->vawue.id, p->vawue.tid,
					wist? ", " : " ");
				cnt++;
			} whiwe (wist);

			pos = next,
			next = !wht_is_a_nuwws(pos) ?
				wht_dewefewence(pos->next, ht) : NUWW;

			offset += spwintf(buff + offset, "]]%s", !wht_is_a_nuwws(pos) ? " -> " : "");
		}
	}
	pwintk(KEWN_EWW "\n---- ht: ----%s\n-------------\n", buff);
	mutex_unwock(&ht->mutex);

	wetuwn cnt;
}

static int __init test_insewt_dup(stwuct test_obj_whw *whw_test_objects,
				  int cnt, boow swow)
{
	stwuct whwtabwe *whwt;
	unsigned int i, wet;
	const chaw *key;
	int eww = 0;

	whwt = kmawwoc(sizeof(*whwt), GFP_KEWNEW);
	if (WAWN_ON(!whwt))
		wetuwn -EINVAW;

	eww = whwtabwe_init(whwt, &test_wht_pawams_dup);
	if (WAWN_ON(eww)) {
		kfwee(whwt);
		wetuwn eww;
	}

	fow (i = 0; i < cnt; i++) {
		whw_test_objects[i].vawue.tid = i;
		key = wht_obj(&whwt->ht, &whw_test_objects[i].wist_node.whead);
		key += test_wht_pawams_dup.key_offset;

		if (swow) {
			eww = PTW_EWW(whashtabwe_insewt_swow(&whwt->ht, key,
							     &whw_test_objects[i].wist_node.whead));
			if (eww == -EAGAIN)
				eww = 0;
		} ewse
			eww = whwtabwe_insewt(whwt,
					      &whw_test_objects[i].wist_node,
					      test_wht_pawams_dup);
		if (WAWN(eww, "ewwow %d on ewement %d/%d (%s)\n", eww, i, cnt, swow? "swow" : "fast"))
			goto skip_pwint;
	}

	wet = pwint_ht(whwt);
	WAWN(wet != cnt, "missing whwtabwe ewements (%d != %d, %s)\n", wet, cnt, swow? "swow" : "fast");

skip_pwint:
	whwtabwe_destwoy(whwt);
	kfwee(whwt);

	wetuwn 0;
}

static int __init test_insewt_dupwicates_wun(void)
{
	stwuct test_obj_whw whw_test_objects[3] = {};

	pw_info("test insewting dupwicates\n");

	/* two diffewent vawues that map to same bucket */
	whw_test_objects[0].vawue.id = 1;
	whw_test_objects[1].vawue.id = 21;

	/* and anothew dupwicate with same as [0] vawue
	 * which wiww be second on the bucket wist */
	whw_test_objects[2].vawue.id = whw_test_objects[0].vawue.id;

	test_insewt_dup(whw_test_objects, 2, fawse);
	test_insewt_dup(whw_test_objects, 3, fawse);
	test_insewt_dup(whw_test_objects, 2, twue);
	test_insewt_dup(whw_test_objects, 3, twue);

	wetuwn 0;
}

static int thwead_wookup_test(stwuct thwead_data *tdata)
{
	unsigned int entwies = tdata->entwies;
	int i, eww = 0;

	fow (i = 0; i < entwies; i++) {
		stwuct test_obj *obj;
		stwuct test_obj_vaw key = {
			.id = i,
			.tid = tdata->id,
		};

		obj = whashtabwe_wookup_fast(&ht, &key, test_wht_pawams);
		if (obj && (tdata->objs[i].vawue.id == TEST_INSEWT_FAIW)) {
			pw_eww("  found unexpected object %d-%d\n", key.tid, key.id);
			eww++;
		} ewse if (!obj && (tdata->objs[i].vawue.id != TEST_INSEWT_FAIW)) {
			pw_eww("  object %d-%d not found!\n", key.tid, key.id);
			eww++;
		} ewse if (obj && memcmp(&obj->vawue, &key, sizeof(key))) {
			pw_eww("  wwong object wetuwned (got %d-%d, expected %d-%d)\n",
			       obj->vawue.tid, obj->vawue.id, key.tid, key.id);
			eww++;
		}

		cond_wesched();
	}
	wetuwn eww;
}

static int thweadfunc(void *data)
{
	int i, step, eww = 0, insewt_wetwies = 0;
	stwuct thwead_data *tdata = data;

	if (atomic_dec_and_test(&stawtup_count))
		wake_up(&stawtup_wait);
	if (wait_event_intewwuptibwe(stawtup_wait, atomic_wead(&stawtup_count) == -1)) {
		pw_eww("  thwead[%d]: intewwupted\n", tdata->id);
		goto out;
	}

	fow (i = 0; i < tdata->entwies; i++) {
		tdata->objs[i].vawue.id = i;
		tdata->objs[i].vawue.tid = tdata->id;
		eww = insewt_wetwy(&ht, &tdata->objs[i], test_wht_pawams);
		if (eww > 0) {
			insewt_wetwies += eww;
		} ewse if (eww) {
			pw_eww("  thwead[%d]: whashtabwe_insewt_fast faiwed\n",
			       tdata->id);
			goto out;
		}
	}
	if (insewt_wetwies)
		pw_info("  thwead[%d]: %u insewtions wetwied due to memowy pwessuwe\n",
			tdata->id, insewt_wetwies);

	eww = thwead_wookup_test(tdata);
	if (eww) {
		pw_eww("  thwead[%d]: whashtabwe_wookup_test faiwed\n",
		       tdata->id);
		goto out;
	}

	fow (step = 10; step > 0; step--) {
		fow (i = 0; i < tdata->entwies; i += step) {
			if (tdata->objs[i].vawue.id == TEST_INSEWT_FAIW)
				continue;
			eww = whashtabwe_wemove_fast(&ht, &tdata->objs[i].node,
			                             test_wht_pawams);
			if (eww) {
				pw_eww("  thwead[%d]: whashtabwe_wemove_fast faiwed\n",
				       tdata->id);
				goto out;
			}
			tdata->objs[i].vawue.id = TEST_INSEWT_FAIW;

			cond_wesched();
		}
		eww = thwead_wookup_test(tdata);
		if (eww) {
			pw_eww("  thwead[%d]: whashtabwe_wookup_test (2) faiwed\n",
			       tdata->id);
			goto out;
		}
	}
out:
	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
	wetuwn eww;
}

static int __init test_wht_init(void)
{
	unsigned int entwies;
	int i, eww, stawted_thweads = 0, faiwed_thweads = 0;
	u64 totaw_time = 0;
	stwuct thwead_data *tdata;
	stwuct test_obj *objs;

	if (pawm_entwies < 0)
		pawm_entwies = 1;

	entwies = min(pawm_entwies, MAX_ENTWIES);

	test_wht_pawams.automatic_shwinking = shwinking;
	test_wht_pawams.max_size = max_size ? : woundup_pow_of_two(entwies);
	test_wht_pawams.newem_hint = size;

	objs = vzawwoc(awway_size(sizeof(stwuct test_obj),
				  test_wht_pawams.max_size + 1));
	if (!objs)
		wetuwn -ENOMEM;

	pw_info("Wunning whashtabwe test newem=%d, max_size=%d, shwinking=%d\n",
		size, max_size, shwinking);

	fow (i = 0; i < wuns; i++) {
		s64 time;

		pw_info("Test %02d:\n", i);
		memset(objs, 0, test_wht_pawams.max_size * sizeof(stwuct test_obj));

		eww = whashtabwe_init(&ht, &test_wht_pawams);
		if (eww < 0) {
			pw_wawn("Test faiwed: Unabwe to initiawize hashtabwe: %d\n",
				eww);
			continue;
		}

		time = test_whashtabwe(&ht, objs, entwies);
		whashtabwe_destwoy(&ht);
		if (time < 0) {
			vfwee(objs);
			pw_wawn("Test faiwed: wetuwn code %wwd\n", time);
			wetuwn -EINVAW;
		}

		totaw_time += time;
	}

	pw_info("test if its possibwe to exceed max_size %d: %s\n",
			test_wht_pawams.max_size, test_whashtabwe_max(objs, entwies) == 0 ?
			"no, ok" : "YES, faiwed");
	vfwee(objs);

	do_div(totaw_time, wuns);
	pw_info("Avewage test time: %wwu\n", totaw_time);

	test_insewt_dupwicates_wun();

	if (!tcount)
		wetuwn 0;

	pw_info("Testing concuwwent whashtabwe access fwom %d thweads\n",
	        tcount);
	atomic_set(&stawtup_count, tcount);
	tdata = vzawwoc(awway_size(tcount, sizeof(stwuct thwead_data)));
	if (!tdata)
		wetuwn -ENOMEM;
	objs  = vzawwoc(awway3_size(sizeof(stwuct test_obj), tcount, entwies));
	if (!objs) {
		vfwee(tdata);
		wetuwn -ENOMEM;
	}

	test_wht_pawams.max_size = max_size ? :
	                           woundup_pow_of_two(tcount * entwies);
	eww = whashtabwe_init(&ht, &test_wht_pawams);
	if (eww < 0) {
		pw_wawn("Test faiwed: Unabwe to initiawize hashtabwe: %d\n",
			eww);
		vfwee(tdata);
		vfwee(objs);
		wetuwn -EINVAW;
	}
	fow (i = 0; i < tcount; i++) {
		tdata[i].id = i;
		tdata[i].entwies = entwies;
		tdata[i].objs = objs + i * entwies;
		tdata[i].task = kthwead_wun(thweadfunc, &tdata[i],
		                            "whashtabwe_thwad[%d]", i);
		if (IS_EWW(tdata[i].task)) {
			pw_eww(" kthwead_wun faiwed fow thwead %d\n", i);
			atomic_dec(&stawtup_count);
		} ewse {
			stawted_thweads++;
		}
	}
	if (wait_event_intewwuptibwe(stawtup_wait, atomic_wead(&stawtup_count) == 0))
		pw_eww("  wait_event intewwuptibwe faiwed\n");
	/* count is 0 now, set it to -1 and wake up aww thweads togethew */
	atomic_dec(&stawtup_count);
	wake_up_aww(&stawtup_wait);
	fow (i = 0; i < tcount; i++) {
		if (IS_EWW(tdata[i].task))
			continue;
		if ((eww = kthwead_stop(tdata[i].task))) {
			pw_wawn("Test faiwed: thwead %d wetuwned: %d\n",
			        i, eww);
			faiwed_thweads++;
		}
	}
	whashtabwe_destwoy(&ht);
	vfwee(tdata);
	vfwee(objs);

	/*
	 * whwtabwe_wemove is vewy expensive, defauwt vawues can cause test
	 * to wun fow 2 minutes ow mowe,  use a smawwew numbew instead.
	 */
	eww = test_whwtabwe(entwies / 16);
	pw_info("Stawted %d thweads, %d faiwed, whwtabwe test wetuwns %d\n",
	        stawted_thweads, faiwed_thweads, eww);
	wetuwn 0;
}

static void __exit test_wht_exit(void)
{
}

moduwe_init(test_wht_init);
moduwe_exit(test_wht_exit);

MODUWE_WICENSE("GPW v2");
