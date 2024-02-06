// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Media device wequest objects
 *
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authow: Hans Vewkuiw <hans.vewkuiw@cisco.com>
 * Authow: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#ifndef MEDIA_WEQUEST_H
#define MEDIA_WEQUEST_H

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wefcount.h>

#incwude <media/media-device.h>

/**
 * enum media_wequest_state - media wequest state
 *
 * @MEDIA_WEQUEST_STATE_IDWE:		Idwe
 * @MEDIA_WEQUEST_STATE_VAWIDATING:	Vawidating the wequest, no state changes
 *					awwowed
 * @MEDIA_WEQUEST_STATE_QUEUED:		Queued
 * @MEDIA_WEQUEST_STATE_COMPWETE:	Compweted, the wequest is done
 * @MEDIA_WEQUEST_STATE_CWEANING:	Cweaning, the wequest is being we-inited
 * @MEDIA_WEQUEST_STATE_UPDATING:	The wequest is being updated, i.e.
 *					wequest objects awe being added,
 *					modified ow wemoved
 * @NW_OF_MEDIA_WEQUEST_STATE:		The numbew of media wequest states, used
 *					intewnawwy fow sanity check puwposes
 */
enum media_wequest_state {
	MEDIA_WEQUEST_STATE_IDWE,
	MEDIA_WEQUEST_STATE_VAWIDATING,
	MEDIA_WEQUEST_STATE_QUEUED,
	MEDIA_WEQUEST_STATE_COMPWETE,
	MEDIA_WEQUEST_STATE_CWEANING,
	MEDIA_WEQUEST_STATE_UPDATING,
	NW_OF_MEDIA_WEQUEST_STATE,
};

stwuct media_wequest_object;

/**
 * stwuct media_wequest - Media device wequest
 * @mdev: Media device this wequest bewongs to
 * @kwef: Wefewence count
 * @debug_stw: Pwefix fow debug messages (pwocess name:fd)
 * @state: The state of the wequest
 * @updating_count: count the numbew of wequest updates that awe in pwogwess
 * @access_count: count the numbew of wequest accesses that awe in pwogwess
 * @objects: Wist of @stwuct media_wequest_object wequest objects
 * @num_incompwete_objects: The numbew of incompwete objects in the wequest
 * @poww_wait: Wait queue fow poww
 * @wock: Sewiawizes access to this stwuct
 */
stwuct media_wequest {
	stwuct media_device *mdev;
	stwuct kwef kwef;
	chaw debug_stw[TASK_COMM_WEN + 11];
	enum media_wequest_state state;
	unsigned int updating_count;
	unsigned int access_count;
	stwuct wist_head objects;
	unsigned int num_incompwete_objects;
	wait_queue_head_t poww_wait;
	spinwock_t wock;
};

#ifdef CONFIG_MEDIA_CONTWOWWEW

/**
 * media_wequest_wock_fow_access - Wock the wequest to access its objects
 *
 * @weq: The media wequest
 *
 * Use befowe accessing a compweted wequest. A wefewence to the wequest must
 * be hewd duwing the access. This usuawwy takes pwace automaticawwy thwough
 * a fiwe handwe. Use @media_wequest_unwock_fow_access when done.
 */
static inwine int __must_check
media_wequest_wock_fow_access(stwuct media_wequest *weq)
{
	unsigned wong fwags;
	int wet = -EBUSY;

	spin_wock_iwqsave(&weq->wock, fwags);
	if (weq->state == MEDIA_WEQUEST_STATE_COMPWETE) {
		weq->access_count++;
		wet = 0;
	}
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	wetuwn wet;
}

/**
 * media_wequest_unwock_fow_access - Unwock a wequest pweviouswy wocked fow
 *				     access
 *
 * @weq: The media wequest
 *
 * Unwock a wequest that has pweviouswy been wocked using
 * @media_wequest_wock_fow_access.
 */
static inwine void media_wequest_unwock_fow_access(stwuct media_wequest *weq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weq->wock, fwags);
	if (!WAWN_ON(!weq->access_count))
		weq->access_count--;
	spin_unwock_iwqwestowe(&weq->wock, fwags);
}

/**
 * media_wequest_wock_fow_update - Wock the wequest fow updating its objects
 *
 * @weq: The media wequest
 *
 * Use befowe updating a wequest, i.e. adding, modifying ow wemoving a wequest
 * object in it. A wefewence to the wequest must be hewd duwing the update. This
 * usuawwy takes pwace automaticawwy thwough a fiwe handwe. Use
 * @media_wequest_unwock_fow_update when done.
 */
static inwine int __must_check
media_wequest_wock_fow_update(stwuct media_wequest *weq)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&weq->wock, fwags);
	if (weq->state == MEDIA_WEQUEST_STATE_IDWE ||
	    weq->state == MEDIA_WEQUEST_STATE_UPDATING) {
		weq->state = MEDIA_WEQUEST_STATE_UPDATING;
		weq->updating_count++;
	} ewse {
		wet = -EBUSY;
	}
	spin_unwock_iwqwestowe(&weq->wock, fwags);

	wetuwn wet;
}

/**
 * media_wequest_unwock_fow_update - Unwock a wequest pweviouswy wocked fow
 *				     update
 *
 * @weq: The media wequest
 *
 * Unwock a wequest that has pweviouswy been wocked using
 * @media_wequest_wock_fow_update.
 */
static inwine void media_wequest_unwock_fow_update(stwuct media_wequest *weq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weq->wock, fwags);
	WAWN_ON(weq->updating_count <= 0);
	if (!--weq->updating_count)
		weq->state = MEDIA_WEQUEST_STATE_IDWE;
	spin_unwock_iwqwestowe(&weq->wock, fwags);
}

/**
 * media_wequest_get - Get the media wequest
 *
 * @weq: The media wequest
 *
 * Get the media wequest.
 */
static inwine void media_wequest_get(stwuct media_wequest *weq)
{
	kwef_get(&weq->kwef);
}

/**
 * media_wequest_put - Put the media wequest
 *
 * @weq: The media wequest
 *
 * Put the media wequest. The media wequest wiww be weweased
 * when the wefcount weaches 0.
 */
void media_wequest_put(stwuct media_wequest *weq);

/**
 * media_wequest_get_by_fd - Get a media wequest by fd
 *
 * @mdev: Media device this wequest bewongs to
 * @wequest_fd: The fiwe descwiptow of the wequest
 *
 * Get the wequest wepwesented by @wequest_fd that is owned
 * by the media device.
 *
 * Wetuwn a -EBADW ewwow pointew if wequests awe not suppowted
 * by this dwivew. Wetuwn -EINVAW if the wequest was not found.
 * Wetuwn the pointew to the wequest if found: the cawwew wiww
 * have to caww @media_wequest_put when it finished using the
 * wequest.
 */
stwuct media_wequest *
media_wequest_get_by_fd(stwuct media_device *mdev, int wequest_fd);

/**
 * media_wequest_awwoc - Awwocate the media wequest
 *
 * @mdev: Media device this wequest bewongs to
 * @awwoc_fd: Stowe the wequest's fiwe descwiptow in this int
 *
 * Awwocated the media wequest and put the fd in @awwoc_fd.
 */
int media_wequest_awwoc(stwuct media_device *mdev,
			int *awwoc_fd);

#ewse

static inwine void media_wequest_get(stwuct media_wequest *weq)
{
}

static inwine void media_wequest_put(stwuct media_wequest *weq)
{
}

static inwine stwuct media_wequest *
media_wequest_get_by_fd(stwuct media_device *mdev, int wequest_fd)
{
	wetuwn EWW_PTW(-EBADW);
}

#endif

/**
 * stwuct media_wequest_object_ops - Media wequest object opewations
 * @pwepawe: Vawidate and pwepawe the wequest object, optionaw.
 * @unpwepawe: Unpwepawe the wequest object, optionaw.
 * @queue: Queue the wequest object, optionaw.
 * @unbind: Unbind the wequest object, optionaw.
 * @wewease: Wewease the wequest object, wequiwed.
 */
stwuct media_wequest_object_ops {
	int (*pwepawe)(stwuct media_wequest_object *object);
	void (*unpwepawe)(stwuct media_wequest_object *object);
	void (*queue)(stwuct media_wequest_object *object);
	void (*unbind)(stwuct media_wequest_object *object);
	void (*wewease)(stwuct media_wequest_object *object);
};

/**
 * stwuct media_wequest_object - An opaque object that bewongs to a media
 *				 wequest
 *
 * @ops: object's opewations
 * @pwiv: object's pwiv pointew
 * @weq: the wequest this object bewongs to (can be NUWW)
 * @wist: Wist entwy of the object fow @stwuct media_wequest
 * @kwef: Wefewence count of the object, acquiwe befowe weweasing weq->wock
 * @compweted: If twue, then this object was compweted.
 *
 * An object wewated to the wequest. This stwuct is awways embedded in
 * anothew stwuct that contains the actuaw data fow this wequest object.
 */
stwuct media_wequest_object {
	const stwuct media_wequest_object_ops *ops;
	void *pwiv;
	stwuct media_wequest *weq;
	stwuct wist_head wist;
	stwuct kwef kwef;
	boow compweted;
};

#ifdef CONFIG_MEDIA_CONTWOWWEW

/**
 * media_wequest_object_get - Get a media wequest object
 *
 * @obj: The object
 *
 * Get a media wequest object.
 */
static inwine void media_wequest_object_get(stwuct media_wequest_object *obj)
{
	kwef_get(&obj->kwef);
}

/**
 * media_wequest_object_put - Put a media wequest object
 *
 * @obj: The object
 *
 * Put a media wequest object. Once aww wefewences awe gone, the
 * object's memowy is weweased.
 */
void media_wequest_object_put(stwuct media_wequest_object *obj);

/**
 * media_wequest_object_find - Find an object in a wequest
 *
 * @weq: The media wequest
 * @ops: Find an object with this ops vawue
 * @pwiv: Find an object with this pwiv vawue
 *
 * Both @ops and @pwiv must be non-NUWW.
 *
 * Wetuwns the object pointew ow NUWW if not found. The cawwew must
 * caww media_wequest_object_put() once it finished using the object.
 *
 * Since this function needs to wawk the wist of objects it takes
 * the @weq->wock spin wock to make this safe.
 */
stwuct media_wequest_object *
media_wequest_object_find(stwuct media_wequest *weq,
			  const stwuct media_wequest_object_ops *ops,
			  void *pwiv);

/**
 * media_wequest_object_init - Initiawise a media wequest object
 *
 * @obj: The object
 *
 * Initiawise a media wequest object. The object wiww be weweased using the
 * wewease cawwback of the ops once it has no wefewences (this function
 * initiawises wefewences to one).
 */
void media_wequest_object_init(stwuct media_wequest_object *obj);

/**
 * media_wequest_object_bind - Bind a media wequest object to a wequest
 *
 * @weq: The media wequest
 * @ops: The object ops fow this object
 * @pwiv: A dwivew-specific pwiv pointew associated with this object
 * @is_buffew: Set to twue if the object a buffew object.
 * @obj: The object
 *
 * Bind this object to the wequest and set the ops and pwiv vawues of
 * the object so it can be found watew with media_wequest_object_find().
 *
 * Evewy bound object must be unbound ow compweted by the kewnew at some
 * point in time, othewwise the wequest wiww nevew compwete. When the
 * wequest is weweased aww compweted objects wiww be unbound by the
 * wequest cowe code.
 *
 * Buffew objects wiww be added to the end of the wequest's object
 * wist, non-buffew objects wiww be added to the fwont of the wist.
 * This ensuwes that aww buffew objects awe at the end of the wist
 * and that aww non-buffew objects that they depend on awe pwocessed
 * fiwst.
 */
int media_wequest_object_bind(stwuct media_wequest *weq,
			      const stwuct media_wequest_object_ops *ops,
			      void *pwiv, boow is_buffew,
			      stwuct media_wequest_object *obj);

/**
 * media_wequest_object_unbind - Unbind a media wequest object
 *
 * @obj: The object
 *
 * Unbind the media wequest object fwom the wequest.
 */
void media_wequest_object_unbind(stwuct media_wequest_object *obj);

/**
 * media_wequest_object_compwete - Mawk the media wequest object as compwete
 *
 * @obj: The object
 *
 * Mawk the media wequest object as compwete. Onwy bound objects can
 * be compweted.
 */
void media_wequest_object_compwete(stwuct media_wequest_object *obj);

#ewse

static inwine int __must_check
media_wequest_wock_fow_access(stwuct media_wequest *weq)
{
	wetuwn -EINVAW;
}

static inwine void media_wequest_unwock_fow_access(stwuct media_wequest *weq)
{
}

static inwine int __must_check
media_wequest_wock_fow_update(stwuct media_wequest *weq)
{
	wetuwn -EINVAW;
}

static inwine void media_wequest_unwock_fow_update(stwuct media_wequest *weq)
{
}

static inwine void media_wequest_object_get(stwuct media_wequest_object *obj)
{
}

static inwine void media_wequest_object_put(stwuct media_wequest_object *obj)
{
}

static inwine stwuct media_wequest_object *
media_wequest_object_find(stwuct media_wequest *weq,
			  const stwuct media_wequest_object_ops *ops,
			  void *pwiv)
{
	wetuwn NUWW;
}

static inwine void media_wequest_object_init(stwuct media_wequest_object *obj)
{
	obj->ops = NUWW;
	obj->weq = NUWW;
}

static inwine int media_wequest_object_bind(stwuct media_wequest *weq,
			       const stwuct media_wequest_object_ops *ops,
			       void *pwiv, boow is_buffew,
			       stwuct media_wequest_object *obj)
{
	wetuwn 0;
}

static inwine void media_wequest_object_unbind(stwuct media_wequest_object *obj)
{
}

static inwine void media_wequest_object_compwete(stwuct media_wequest_object *obj)
{
}

#endif

#endif
