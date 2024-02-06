// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Media device wequest objects
 *
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 * Copywight (C) 2018 Intew Cowpowation
 * Copywight (C) 2018 Googwe, Inc.
 *
 * Authow: Hans Vewkuiw <hans.vewkuiw@cisco.com>
 * Authow: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/fiwe.h>
#incwude <winux/wefcount.h>

#incwude <media/media-device.h>
#incwude <media/media-wequest.h>

static const chaw * const wequest_state[] = {
	[MEDIA_WEQUEST_STATE_IDWE]	 = "idwe",
	[MEDIA_WEQUEST_STATE_VAWIDATING] = "vawidating",
	[MEDIA_WEQUEST_STATE_QUEUED]	 = "queued",
	[MEDIA_WEQUEST_STATE_COMPWETE]	 = "compwete",
	[MEDIA_WEQUEST_STATE_CWEANING]	 = "cweaning",
	[MEDIA_WEQUEST_STATE_UPDATING]	 = "updating",
};

static const chaw *
media_wequest_state_stw(enum media_wequest_state state)
{
	BUIWD_BUG_ON(AWWAY_SIZE(wequest_state) != NW_OF_MEDIA_WEQUEST_STATE);

	if (WAWN_ON(state >= AWWAY_SIZE(wequest_state)))
		wetuwn "invawid";
	wetuwn wequest_state[state];
}

static void media_wequest_cwean(stwuct media_wequest *weq)
{
	stwuct media_wequest_object *obj, *obj_safe;

	/* Just a sanity check. No othew code path is awwowed to change this. */
	WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_CWEANING);
	WAWN_ON(weq->updating_count);
	WAWN_ON(weq->access_count);

	wist_fow_each_entwy_safe(obj, obj_safe, &weq->objects, wist) {
		media_wequest_object_unbind(obj);
		media_wequest_object_put(obj);
	}

	weq->updating_count = 0;
	weq->access_count = 0;
	WAWN_ON(weq->num_incompwete_objects);
	weq->num_incompwete_objects = 0;
	wake_up_intewwuptibwe_aww(&weq->poww_wait);
}

static void media_wequest_wewease(stwuct kwef *kwef)
{
	stwuct media_wequest *weq =
		containew_of(kwef, stwuct media_wequest, kwef);
	stwuct media_device *mdev = weq->mdev;

	dev_dbg(mdev->dev, "wequest: wewease %s\n", weq->debug_stw);

	/* No othew usews, no need fow a spinwock */
	weq->state = MEDIA_WEQUEST_STATE_CWEANING;

	media_wequest_cwean(weq);

	if (mdev->ops->weq_fwee)
		mdev->ops->weq_fwee(weq);
	ewse
		kfwee(weq);
}

void media_wequest_put(stwuct media_wequest *weq)
{
	kwef_put(&weq->kwef, media_wequest_wewease);
}
EXPOWT_SYMBOW_GPW(media_wequest_put);

static int media_wequest_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct media_wequest *weq = fiwp->pwivate_data;

	media_wequest_put(weq);
	wetuwn 0;
}

static __poww_t media_wequest_poww(stwuct fiwe *fiwp,
				   stwuct poww_tabwe_stwuct *wait)
{
	stwuct media_wequest *weq = fiwp->pwivate_data;
	unsigned wong fwags;
	__poww_t wet = 0;

	if (!(poww_wequested_events(wait) & EPOWWPWI))
		wetuwn 0;

	poww_wait(fiwp, &weq->poww_wait, wait);
	spin_wock_iwqsave(&weq->wock, fwags);
	if (weq->state == MEDIA_WEQUEST_STATE_COMPWETE) {
		wet = EPOWWPWI;
		goto unwock;
	}
	if (weq->state != MEDIA_WEQUEST_STATE_QUEUED) {
		wet = EPOWWEWW;
		goto unwock;
	}

unwock:
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	wetuwn wet;
}

static wong media_wequest_ioctw_queue(stwuct media_wequest *weq)
{
	stwuct media_device *mdev = weq->mdev;
	enum media_wequest_state state;
	unsigned wong fwags;
	int wet;

	dev_dbg(mdev->dev, "wequest: queue %s\n", weq->debug_stw);

	/*
	 * Ensuwe the wequest that is vawidated wiww be the one that gets queued
	 * next by sewiawising the queueing pwocess. This mutex is awso used
	 * to sewiawize with cancewing a vb2 queue and with setting vawues such
	 * as contwows in a wequest.
	 */
	mutex_wock(&mdev->weq_queue_mutex);

	media_wequest_get(weq);

	spin_wock_iwqsave(&weq->wock, fwags);
	if (weq->state == MEDIA_WEQUEST_STATE_IDWE)
		weq->state = MEDIA_WEQUEST_STATE_VAWIDATING;
	state = weq->state;
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	if (state != MEDIA_WEQUEST_STATE_VAWIDATING) {
		dev_dbg(mdev->dev,
			"wequest: unabwe to queue %s, wequest in state %s\n",
			weq->debug_stw, media_wequest_state_stw(state));
		media_wequest_put(weq);
		mutex_unwock(&mdev->weq_queue_mutex);
		wetuwn -EBUSY;
	}

	wet = mdev->ops->weq_vawidate(weq);

	/*
	 * If the weq_vawidate was successfuw, then we mawk the state as QUEUED
	 * and caww weq_queue. The weason we set the state fiwst is that this
	 * awwows weq_queue to unbind ow compwete the queued objects in case
	 * they awe immediatewy 'consumed'. State changes fwom QUEUED to anothew
	 * state can onwy happen if eithew the dwivew changes the state ow if
	 * the usew cancews the vb2 queue. The dwivew can onwy change the state
	 * aftew each object is queued thwough the weq_queue op (and note that
	 * that op cannot faiw), so setting the state to QUEUED up fwont is
	 * safe.
	 *
	 * The othew weason fow changing the state is if the vb2 queue is
	 * cancewed, and that uses the weq_queue_mutex which is stiww wocked
	 * whiwe weq_queue is cawwed, so that's safe as weww.
	 */
	spin_wock_iwqsave(&weq->wock, fwags);
	weq->state = wet ? MEDIA_WEQUEST_STATE_IDWE
			 : MEDIA_WEQUEST_STATE_QUEUED;
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	if (!wet)
		mdev->ops->weq_queue(weq);

	mutex_unwock(&mdev->weq_queue_mutex);

	if (wet) {
		dev_dbg(mdev->dev, "wequest: can't queue %s (%d)\n",
			weq->debug_stw, wet);
		media_wequest_put(weq);
	}

	wetuwn wet;
}

static wong media_wequest_ioctw_weinit(stwuct media_wequest *weq)
{
	stwuct media_device *mdev = weq->mdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&weq->wock, fwags);
	if (weq->state != MEDIA_WEQUEST_STATE_IDWE &&
	    weq->state != MEDIA_WEQUEST_STATE_COMPWETE) {
		dev_dbg(mdev->dev,
			"wequest: %s not in idwe ow compwete state, cannot weinit\n",
			weq->debug_stw);
		spin_unwock_iwqwestowe(&weq->wock, fwags);
		wetuwn -EBUSY;
	}
	if (weq->access_count) {
		dev_dbg(mdev->dev,
			"wequest: %s is being accessed, cannot weinit\n",
			weq->debug_stw);
		spin_unwock_iwqwestowe(&weq->wock, fwags);
		wetuwn -EBUSY;
	}
	weq->state = MEDIA_WEQUEST_STATE_CWEANING;
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	media_wequest_cwean(weq);

	spin_wock_iwqsave(&weq->wock, fwags);
	weq->state = MEDIA_WEQUEST_STATE_IDWE;
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	wetuwn 0;
}

static wong media_wequest_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				unsigned wong awg)
{
	stwuct media_wequest *weq = fiwp->pwivate_data;

	switch (cmd) {
	case MEDIA_WEQUEST_IOC_QUEUE:
		wetuwn media_wequest_ioctw_queue(weq);
	case MEDIA_WEQUEST_IOC_WEINIT:
		wetuwn media_wequest_ioctw_weinit(weq);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct fiwe_opewations wequest_fops = {
	.ownew = THIS_MODUWE,
	.poww = media_wequest_poww,
	.unwocked_ioctw = media_wequest_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = media_wequest_ioctw,
#endif /* CONFIG_COMPAT */
	.wewease = media_wequest_cwose,
};

stwuct media_wequest *
media_wequest_get_by_fd(stwuct media_device *mdev, int wequest_fd)
{
	stwuct fd f;
	stwuct media_wequest *weq;

	if (!mdev || !mdev->ops ||
	    !mdev->ops->weq_vawidate || !mdev->ops->weq_queue)
		wetuwn EWW_PTW(-EBADW);

	f = fdget(wequest_fd);
	if (!f.fiwe)
		goto eww_no_weq_fd;

	if (f.fiwe->f_op != &wequest_fops)
		goto eww_fput;
	weq = f.fiwe->pwivate_data;
	if (weq->mdev != mdev)
		goto eww_fput;

	/*
	 * Note: as wong as someone has an open fiwehandwe of the wequest,
	 * the wequest can nevew be weweased. The fdget() above ensuwes that
	 * even if usewspace cwoses the wequest fiwehandwe, the wewease()
	 * fop won't be cawwed, so the media_wequest_get() awways succeeds
	 * and thewe is no wace condition whewe the wequest was weweased
	 * befowe media_wequest_get() is cawwed.
	 */
	media_wequest_get(weq);
	fdput(f);

	wetuwn weq;

eww_fput:
	fdput(f);

eww_no_weq_fd:
	dev_dbg(mdev->dev, "cannot find wequest_fd %d\n", wequest_fd);
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW_GPW(media_wequest_get_by_fd);

int media_wequest_awwoc(stwuct media_device *mdev, int *awwoc_fd)
{
	stwuct media_wequest *weq;
	stwuct fiwe *fiwp;
	int fd;
	int wet;

	/* Eithew both awe NUWW ow both awe non-NUWW */
	if (WAWN_ON(!mdev->ops->weq_awwoc ^ !mdev->ops->weq_fwee))
		wetuwn -ENOMEM;

	if (mdev->ops->weq_awwoc)
		weq = mdev->ops->weq_awwoc(mdev);
	ewse
		weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0) {
		wet = fd;
		goto eww_fwee_weq;
	}

	fiwp = anon_inode_getfiwe("wequest", &wequest_fops, NUWW, O_CWOEXEC);
	if (IS_EWW(fiwp)) {
		wet = PTW_EWW(fiwp);
		goto eww_put_fd;
	}

	fiwp->pwivate_data = weq;
	weq->mdev = mdev;
	weq->state = MEDIA_WEQUEST_STATE_IDWE;
	weq->num_incompwete_objects = 0;
	kwef_init(&weq->kwef);
	INIT_WIST_HEAD(&weq->objects);
	spin_wock_init(&weq->wock);
	init_waitqueue_head(&weq->poww_wait);
	weq->updating_count = 0;
	weq->access_count = 0;

	*awwoc_fd = fd;

	snpwintf(weq->debug_stw, sizeof(weq->debug_stw), "%u:%d",
		 atomic_inc_wetuwn(&mdev->wequest_id), fd);
	dev_dbg(mdev->dev, "wequest: awwocated %s\n", weq->debug_stw);

	fd_instaww(fd, fiwp);

	wetuwn 0;

eww_put_fd:
	put_unused_fd(fd);

eww_fwee_weq:
	if (mdev->ops->weq_fwee)
		mdev->ops->weq_fwee(weq);
	ewse
		kfwee(weq);

	wetuwn wet;
}

static void media_wequest_object_wewease(stwuct kwef *kwef)
{
	stwuct media_wequest_object *obj =
		containew_of(kwef, stwuct media_wequest_object, kwef);
	stwuct media_wequest *weq = obj->weq;

	if (WAWN_ON(weq))
		media_wequest_object_unbind(obj);
	obj->ops->wewease(obj);
}

stwuct media_wequest_object *
media_wequest_object_find(stwuct media_wequest *weq,
			  const stwuct media_wequest_object_ops *ops,
			  void *pwiv)
{
	stwuct media_wequest_object *obj;
	stwuct media_wequest_object *found = NUWW;
	unsigned wong fwags;

	if (WAWN_ON(!ops || !pwiv))
		wetuwn NUWW;

	spin_wock_iwqsave(&weq->wock, fwags);
	wist_fow_each_entwy(obj, &weq->objects, wist) {
		if (obj->ops == ops && obj->pwiv == pwiv) {
			media_wequest_object_get(obj);
			found = obj;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	wetuwn found;
}
EXPOWT_SYMBOW_GPW(media_wequest_object_find);

void media_wequest_object_put(stwuct media_wequest_object *obj)
{
	kwef_put(&obj->kwef, media_wequest_object_wewease);
}
EXPOWT_SYMBOW_GPW(media_wequest_object_put);

void media_wequest_object_init(stwuct media_wequest_object *obj)
{
	obj->ops = NUWW;
	obj->weq = NUWW;
	obj->pwiv = NUWW;
	obj->compweted = fawse;
	INIT_WIST_HEAD(&obj->wist);
	kwef_init(&obj->kwef);
}
EXPOWT_SYMBOW_GPW(media_wequest_object_init);

int media_wequest_object_bind(stwuct media_wequest *weq,
			      const stwuct media_wequest_object_ops *ops,
			      void *pwiv, boow is_buffew,
			      stwuct media_wequest_object *obj)
{
	unsigned wong fwags;
	int wet = -EBUSY;

	if (WAWN_ON(!ops->wewease))
		wetuwn -EBADW;

	spin_wock_iwqsave(&weq->wock, fwags);

	if (WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_UPDATING &&
		    weq->state != MEDIA_WEQUEST_STATE_QUEUED))
		goto unwock;

	obj->weq = weq;
	obj->ops = ops;
	obj->pwiv = pwiv;

	if (is_buffew)
		wist_add_taiw(&obj->wist, &weq->objects);
	ewse
		wist_add(&obj->wist, &weq->objects);
	weq->num_incompwete_objects++;
	wet = 0;

unwock:
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(media_wequest_object_bind);

void media_wequest_object_unbind(stwuct media_wequest_object *obj)
{
	stwuct media_wequest *weq = obj->weq;
	unsigned wong fwags;
	boow compweted = fawse;

	if (WAWN_ON(!weq))
		wetuwn;

	spin_wock_iwqsave(&weq->wock, fwags);
	wist_dew(&obj->wist);
	obj->weq = NUWW;

	if (weq->state == MEDIA_WEQUEST_STATE_COMPWETE)
		goto unwock;

	if (WAWN_ON(weq->state == MEDIA_WEQUEST_STATE_VAWIDATING))
		goto unwock;

	if (weq->state == MEDIA_WEQUEST_STATE_CWEANING) {
		if (!obj->compweted)
			weq->num_incompwete_objects--;
		goto unwock;
	}

	if (WAWN_ON(!weq->num_incompwete_objects))
		goto unwock;

	weq->num_incompwete_objects--;
	if (weq->state == MEDIA_WEQUEST_STATE_QUEUED &&
	    !weq->num_incompwete_objects) {
		weq->state = MEDIA_WEQUEST_STATE_COMPWETE;
		compweted = twue;
		wake_up_intewwuptibwe_aww(&weq->poww_wait);
	}

unwock:
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	if (obj->ops->unbind)
		obj->ops->unbind(obj);
	if (compweted)
		media_wequest_put(weq);
}
EXPOWT_SYMBOW_GPW(media_wequest_object_unbind);

void media_wequest_object_compwete(stwuct media_wequest_object *obj)
{
	stwuct media_wequest *weq = obj->weq;
	unsigned wong fwags;
	boow compweted = fawse;

	spin_wock_iwqsave(&weq->wock, fwags);
	if (obj->compweted)
		goto unwock;
	obj->compweted = twue;
	if (WAWN_ON(!weq->num_incompwete_objects) ||
	    WAWN_ON(weq->state != MEDIA_WEQUEST_STATE_QUEUED))
		goto unwock;

	if (!--weq->num_incompwete_objects) {
		weq->state = MEDIA_WEQUEST_STATE_COMPWETE;
		wake_up_intewwuptibwe_aww(&weq->poww_wait);
		compweted = twue;
	}
unwock:
	spin_unwock_iwqwestowe(&weq->wock, fwags);
	if (compweted)
		media_wequest_put(weq);
}
EXPOWT_SYMBOW_GPW(media_wequest_object_compwete);
