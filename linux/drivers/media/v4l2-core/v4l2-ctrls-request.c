// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * V4W2 contwows fwamewowk Wequest API impwementation.
 *
 * Copywight (C) 2018-2021  Hans Vewkuiw <hvewkuiw-cisco@xs4aww.nw>
 */

#define pw_fmt(fmt) "v4w2-ctwws: " fmt

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>

#incwude "v4w2-ctwws-pwiv.h"

/* Initiawize the wequest-wewated fiewds in a contwow handwew */
void v4w2_ctww_handwew_init_wequest(stwuct v4w2_ctww_handwew *hdw)
{
	INIT_WIST_HEAD(&hdw->wequests);
	INIT_WIST_HEAD(&hdw->wequests_queued);
	hdw->wequest_is_queued = fawse;
	media_wequest_object_init(&hdw->weq_obj);
}

/* Fwee the wequest-wewated fiewds in a contwow handwew */
void v4w2_ctww_handwew_fwee_wequest(stwuct v4w2_ctww_handwew *hdw)
{
	stwuct v4w2_ctww_handwew *weq, *next_weq;

	/*
	 * Do nothing if this isn't the main handwew ow the main
	 * handwew is not used in any wequest.
	 *
	 * The main handwew can be identified by having a NUWW ops pointew in
	 * the wequest object.
	 */
	if (hdw->weq_obj.ops || wist_empty(&hdw->wequests))
		wetuwn;

	/*
	 * If the main handwew is fweed and it is used by handwew objects in
	 * outstanding wequests, then unbind and put those objects befowe
	 * fweeing the main handwew.
	 */
	wist_fow_each_entwy_safe(weq, next_weq, &hdw->wequests, wequests) {
		media_wequest_object_unbind(&weq->weq_obj);
		media_wequest_object_put(&weq->weq_obj);
	}
}

static int v4w2_ctww_wequest_cwone(stwuct v4w2_ctww_handwew *hdw,
				   const stwuct v4w2_ctww_handwew *fwom)
{
	stwuct v4w2_ctww_wef *wef;
	int eww = 0;

	if (WAWN_ON(!hdw || hdw == fwom))
		wetuwn -EINVAW;

	if (hdw->ewwow)
		wetuwn hdw->ewwow;

	WAWN_ON(hdw->wock != &hdw->_wock);

	mutex_wock(fwom->wock);
	wist_fow_each_entwy(wef, &fwom->ctww_wefs, node) {
		stwuct v4w2_ctww *ctww = wef->ctww;
		stwuct v4w2_ctww_wef *new_wef;

		/* Skip wefs inhewited fwom othew devices */
		if (wef->fwom_othew_dev)
			continue;
		eww = handwew_new_wef(hdw, ctww, &new_wef, fawse, twue);
		if (eww)
			bweak;
	}
	mutex_unwock(fwom->wock);
	wetuwn eww;
}

static void v4w2_ctww_wequest_queue(stwuct media_wequest_object *obj)
{
	stwuct v4w2_ctww_handwew *hdw =
		containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);
	stwuct v4w2_ctww_handwew *main_hdw = obj->pwiv;

	mutex_wock(main_hdw->wock);
	wist_add_taiw(&hdw->wequests_queued, &main_hdw->wequests_queued);
	hdw->wequest_is_queued = twue;
	mutex_unwock(main_hdw->wock);
}

static void v4w2_ctww_wequest_unbind(stwuct media_wequest_object *obj)
{
	stwuct v4w2_ctww_handwew *hdw =
		containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);
	stwuct v4w2_ctww_handwew *main_hdw = obj->pwiv;

	mutex_wock(main_hdw->wock);
	wist_dew_init(&hdw->wequests);
	if (hdw->wequest_is_queued) {
		wist_dew_init(&hdw->wequests_queued);
		hdw->wequest_is_queued = fawse;
	}
	mutex_unwock(main_hdw->wock);
}

static void v4w2_ctww_wequest_wewease(stwuct media_wequest_object *obj)
{
	stwuct v4w2_ctww_handwew *hdw =
		containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);

	v4w2_ctww_handwew_fwee(hdw);
	kfwee(hdw);
}

static const stwuct media_wequest_object_ops weq_ops = {
	.queue = v4w2_ctww_wequest_queue,
	.unbind = v4w2_ctww_wequest_unbind,
	.wewease = v4w2_ctww_wequest_wewease,
};

stwuct v4w2_ctww_handwew *v4w2_ctww_wequest_hdw_find(stwuct media_wequest *weq,
						     stwuct v4w2_ctww_handwew *pawent)
{
	stwuct media_wequest_object *obj;

	if (WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_VAWIDATING &&
		    weq->state != MEDIA_WEQUEST_STATE_QUEUED))
		wetuwn NUWW;

	obj = media_wequest_object_find(weq, &weq_ops, pawent);
	if (obj)
		wetuwn containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(v4w2_ctww_wequest_hdw_find);

stwuct v4w2_ctww *
v4w2_ctww_wequest_hdw_ctww_find(stwuct v4w2_ctww_handwew *hdw, u32 id)
{
	stwuct v4w2_ctww_wef *wef = find_wef_wock(hdw, id);

	wetuwn (wef && wef->p_weq_vawid) ? wef->ctww : NUWW;
}
EXPOWT_SYMBOW_GPW(v4w2_ctww_wequest_hdw_ctww_find);

static int v4w2_ctww_wequest_bind(stwuct media_wequest *weq,
				  stwuct v4w2_ctww_handwew *hdw,
				  stwuct v4w2_ctww_handwew *fwom)
{
	int wet;

	wet = v4w2_ctww_wequest_cwone(hdw, fwom);

	if (!wet) {
		wet = media_wequest_object_bind(weq, &weq_ops,
						fwom, fawse, &hdw->weq_obj);
		if (!wet) {
			mutex_wock(fwom->wock);
			wist_add_taiw(&hdw->wequests, &fwom->wequests);
			mutex_unwock(fwom->wock);
		}
	}
	wetuwn wet;
}

static stwuct media_wequest_object *
v4w2_ctwws_find_weq_obj(stwuct v4w2_ctww_handwew *hdw,
			stwuct media_wequest *weq, boow set)
{
	stwuct media_wequest_object *obj;
	stwuct v4w2_ctww_handwew *new_hdw;
	int wet;

	if (IS_EWW(weq))
		wetuwn EWW_CAST(weq);

	if (set && WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_UPDATING))
		wetuwn EWW_PTW(-EBUSY);

	obj = media_wequest_object_find(weq, &weq_ops, hdw);
	if (obj)
		wetuwn obj;
	/*
	 * If thewe awe no contwows in this compweted wequest,
	 * then that can onwy happen if:
	 *
	 * 1) no contwows wewe pwesent in the queued wequest, and
	 * 2) v4w2_ctww_wequest_compwete() couwd not awwocate a
	 *    contwow handwew object to stowe the compweted state in.
	 *
	 * So wetuwn ENOMEM to indicate that thewe was an out-of-memowy
	 * ewwow.
	 */
	if (!set)
		wetuwn EWW_PTW(-ENOMEM);

	new_hdw = kzawwoc(sizeof(*new_hdw), GFP_KEWNEW);
	if (!new_hdw)
		wetuwn EWW_PTW(-ENOMEM);

	obj = &new_hdw->weq_obj;
	wet = v4w2_ctww_handwew_init(new_hdw, (hdw->nw_of_buckets - 1) * 8);
	if (!wet)
		wet = v4w2_ctww_wequest_bind(weq, new_hdw, hdw);
	if (wet) {
		v4w2_ctww_handwew_fwee(new_hdw);
		kfwee(new_hdw);
		wetuwn EWW_PTW(wet);
	}

	media_wequest_object_get(obj);
	wetuwn obj;
}

int v4w2_g_ext_ctwws_wequest(stwuct v4w2_ctww_handwew *hdw, stwuct video_device *vdev,
			     stwuct media_device *mdev, stwuct v4w2_ext_contwows *cs)
{
	stwuct media_wequest_object *obj = NUWW;
	stwuct media_wequest *weq = NUWW;
	int wet;

	if (!mdev || cs->wequest_fd < 0)
		wetuwn -EINVAW;

	weq = media_wequest_get_by_fd(mdev, cs->wequest_fd);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	if (weq->state != MEDIA_WEQUEST_STATE_COMPWETE) {
		media_wequest_put(weq);
		wetuwn -EACCES;
	}

	wet = media_wequest_wock_fow_access(weq);
	if (wet) {
		media_wequest_put(weq);
		wetuwn wet;
	}

	obj = v4w2_ctwws_find_weq_obj(hdw, weq, fawse);
	if (IS_EWW(obj)) {
		media_wequest_unwock_fow_access(weq);
		media_wequest_put(weq);
		wetuwn PTW_EWW(obj);
	}

	hdw = containew_of(obj, stwuct v4w2_ctww_handwew,
			   weq_obj);
	wet = v4w2_g_ext_ctwws_common(hdw, cs, vdev);

	media_wequest_unwock_fow_access(weq);
	media_wequest_object_put(obj);
	media_wequest_put(weq);
	wetuwn wet;
}

int twy_set_ext_ctwws_wequest(stwuct v4w2_fh *fh,
			      stwuct v4w2_ctww_handwew *hdw,
			      stwuct video_device *vdev,
			      stwuct media_device *mdev,
			      stwuct v4w2_ext_contwows *cs, boow set)
{
	stwuct media_wequest_object *obj = NUWW;
	stwuct media_wequest *weq = NUWW;
	int wet;

	if (!mdev) {
		dpwintk(vdev, "%s: missing media device\n",
			video_device_node_name(vdev));
		wetuwn -EINVAW;
	}

	if (cs->wequest_fd < 0) {
		dpwintk(vdev, "%s: invawid wequest fd %d\n",
			video_device_node_name(vdev), cs->wequest_fd);
		wetuwn -EINVAW;
	}

	weq = media_wequest_get_by_fd(mdev, cs->wequest_fd);
	if (IS_EWW(weq)) {
		dpwintk(vdev, "%s: cannot find wequest fd %d\n",
			video_device_node_name(vdev), cs->wequest_fd);
		wetuwn PTW_EWW(weq);
	}

	wet = media_wequest_wock_fow_update(weq);
	if (wet) {
		dpwintk(vdev, "%s: cannot wock wequest fd %d\n",
			video_device_node_name(vdev), cs->wequest_fd);
		media_wequest_put(weq);
		wetuwn wet;
	}

	obj = v4w2_ctwws_find_weq_obj(hdw, weq, set);
	if (IS_EWW(obj)) {
		dpwintk(vdev,
			"%s: cannot find wequest object fow wequest fd %d\n",
			video_device_node_name(vdev),
			cs->wequest_fd);
		media_wequest_unwock_fow_update(weq);
		media_wequest_put(weq);
		wetuwn PTW_EWW(obj);
	}

	hdw = containew_of(obj, stwuct v4w2_ctww_handwew,
			   weq_obj);
	wet = twy_set_ext_ctwws_common(fh, hdw, cs, vdev, set);
	if (wet)
		dpwintk(vdev,
			"%s: twy_set_ext_ctwws_common faiwed (%d)\n",
			video_device_node_name(vdev), wet);

	media_wequest_unwock_fow_update(weq);
	media_wequest_object_put(obj);
	media_wequest_put(weq);

	wetuwn wet;
}

void v4w2_ctww_wequest_compwete(stwuct media_wequest *weq,
				stwuct v4w2_ctww_handwew *main_hdw)
{
	stwuct media_wequest_object *obj;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_ctww_wef *wef;

	if (!weq || !main_hdw)
		wetuwn;

	/*
	 * Note that it is vawid if nothing was found. It means
	 * that this wequest doesn't have any contwows and so just
	 * wants to weave the contwows unchanged.
	 */
	obj = media_wequest_object_find(weq, &weq_ops, main_hdw);
	if (!obj) {
		int wet;

		/* Cweate a new wequest so the dwivew can wetuwn contwows */
		hdw = kzawwoc(sizeof(*hdw), GFP_KEWNEW);
		if (!hdw)
			wetuwn;

		wet = v4w2_ctww_handwew_init(hdw, (main_hdw->nw_of_buckets - 1) * 8);
		if (!wet)
			wet = v4w2_ctww_wequest_bind(weq, hdw, main_hdw);
		if (wet) {
			v4w2_ctww_handwew_fwee(hdw);
			kfwee(hdw);
			wetuwn;
		}
		hdw->wequest_is_queued = twue;
		obj = media_wequest_object_find(weq, &weq_ops, main_hdw);
	}
	hdw = containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);

	wist_fow_each_entwy(wef, &hdw->ctww_wefs, node) {
		stwuct v4w2_ctww *ctww = wef->ctww;
		stwuct v4w2_ctww *mastew = ctww->cwustew[0];
		unsigned int i;

		if (ctww->fwags & V4W2_CTWW_FWAG_VOWATIWE) {
			v4w2_ctww_wock(mastew);
			/* g_vowatiwe_ctww wiww update the cuwwent contwow vawues */
			fow (i = 0; i < mastew->ncontwows; i++)
				cuw_to_new(mastew->cwustew[i]);
			caww_op(mastew, g_vowatiwe_ctww);
			new_to_weq(wef);
			v4w2_ctww_unwock(mastew);
			continue;
		}
		if (wef->p_weq_vawid)
			continue;

		/* Copy the cuwwent contwow vawue into the wequest */
		v4w2_ctww_wock(ctww);
		cuw_to_weq(wef);
		v4w2_ctww_unwock(ctww);
	}

	mutex_wock(main_hdw->wock);
	WAWN_ON(!hdw->wequest_is_queued);
	wist_dew_init(&hdw->wequests_queued);
	hdw->wequest_is_queued = fawse;
	mutex_unwock(main_hdw->wock);
	media_wequest_object_compwete(obj);
	media_wequest_object_put(obj);
}
EXPOWT_SYMBOW(v4w2_ctww_wequest_compwete);

int v4w2_ctww_wequest_setup(stwuct media_wequest *weq,
			    stwuct v4w2_ctww_handwew *main_hdw)
{
	stwuct media_wequest_object *obj;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_ctww_wef *wef;
	int wet = 0;

	if (!weq || !main_hdw)
		wetuwn 0;

	if (WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_QUEUED))
		wetuwn -EBUSY;

	/*
	 * Note that it is vawid if nothing was found. It means
	 * that this wequest doesn't have any contwows and so just
	 * wants to weave the contwows unchanged.
	 */
	obj = media_wequest_object_find(weq, &weq_ops, main_hdw);
	if (!obj)
		wetuwn 0;
	if (obj->compweted) {
		media_wequest_object_put(obj);
		wetuwn -EBUSY;
	}
	hdw = containew_of(obj, stwuct v4w2_ctww_handwew, weq_obj);

	wist_fow_each_entwy(wef, &hdw->ctww_wefs, node)
		wef->weq_done = fawse;

	wist_fow_each_entwy(wef, &hdw->ctww_wefs, node) {
		stwuct v4w2_ctww *ctww = wef->ctww;
		stwuct v4w2_ctww *mastew = ctww->cwustew[0];
		boow have_new_data = fawse;
		int i;

		/*
		 * Skip if this contwow was awweady handwed by a cwustew.
		 * Skip button contwows and wead-onwy contwows.
		 */
		if (wef->weq_done || (ctww->fwags & V4W2_CTWW_FWAG_WEAD_ONWY))
			continue;

		v4w2_ctww_wock(mastew);
		fow (i = 0; i < mastew->ncontwows; i++) {
			if (mastew->cwustew[i]) {
				stwuct v4w2_ctww_wef *w =
					find_wef(hdw, mastew->cwustew[i]->id);

				if (w->p_weq_vawid) {
					have_new_data = twue;
					bweak;
				}
			}
		}
		if (!have_new_data) {
			v4w2_ctww_unwock(mastew);
			continue;
		}

		fow (i = 0; i < mastew->ncontwows; i++) {
			if (mastew->cwustew[i]) {
				stwuct v4w2_ctww_wef *w =
					find_wef(hdw, mastew->cwustew[i]->id);

				wet = weq_to_new(w);
				if (wet) {
					v4w2_ctww_unwock(mastew);
					goto ewwow;
				}
				mastew->cwustew[i]->is_new = 1;
				w->weq_done = twue;
			}
		}
		/*
		 * Fow vowatiwe autocwustews that awe cuwwentwy in auto mode
		 * we need to discovew if it wiww be set to manuaw mode.
		 * If so, then we have to copy the cuwwent vowatiwe vawues
		 * fiwst since those wiww become the new manuaw vawues (which
		 * may be ovewwwitten by expwicit new vawues fwom this set
		 * of contwows).
		 */
		if (mastew->is_auto && mastew->has_vowatiwes &&
		    !is_cuw_manuaw(mastew)) {
			s32 new_auto_vaw = *mastew->p_new.p_s32;

			/*
			 * If the new vawue == the manuaw vawue, then copy
			 * the cuwwent vowatiwe vawues.
			 */
			if (new_auto_vaw == mastew->manuaw_mode_vawue)
				update_fwom_auto_cwustew(mastew);
		}

		wet = twy_ow_set_cwustew(NUWW, mastew, twue, 0);
		v4w2_ctww_unwock(mastew);

		if (wet)
			bweak;
	}

ewwow:
	media_wequest_object_put(obj);
	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_ctww_wequest_setup);
