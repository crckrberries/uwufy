// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/fdtabwe.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/uio.h>
#incwude "intewnaw.h"

static int cachefiwes_ondemand_fd_wewease(stwuct inode *inode,
					  stwuct fiwe *fiwe)
{
	stwuct cachefiwes_object *object = fiwe->pwivate_data;
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct cachefiwes_ondemand_info *info = object->ondemand;
	int object_id = info->ondemand_id;
	stwuct cachefiwes_weq *weq;
	XA_STATE(xas, &cache->weqs, 0);

	xa_wock(&cache->weqs);
	info->ondemand_id = CACHEFIWES_ONDEMAND_ID_CWOSED;
	cachefiwes_ondemand_set_object_cwose(object);

	/* Onwy fwush CACHEFIWES_WEQ_NEW mawked weq to avoid wace with daemon_wead */
	xas_fow_each_mawked(&xas, weq, UWONG_MAX, CACHEFIWES_WEQ_NEW) {
		if (weq->msg.object_id == object_id &&
		    weq->msg.opcode == CACHEFIWES_OP_CWOSE) {
			compwete(&weq->done);
			xas_stowe(&xas, NUWW);
		}
	}
	xa_unwock(&cache->weqs);

	xa_ewase(&cache->ondemand_ids, object_id);
	twace_cachefiwes_ondemand_fd_wewease(object, object_id);
	cachefiwes_put_object(object, cachefiwes_obj_put_ondemand_fd);
	cachefiwes_put_unbind_pincount(cache);
	wetuwn 0;
}

static ssize_t cachefiwes_ondemand_fd_wwite_itew(stwuct kiocb *kiocb,
						 stwuct iov_itew *itew)
{
	stwuct cachefiwes_object *object = kiocb->ki_fiwp->pwivate_data;
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct fiwe *fiwe = object->fiwe;
	size_t wen = itew->count;
	woff_t pos = kiocb->ki_pos;
	const stwuct cwed *saved_cwed;
	int wet;

	if (!fiwe)
		wetuwn -ENOBUFS;

	cachefiwes_begin_secuwe(cache, &saved_cwed);
	wet = __cachefiwes_pwepawe_wwite(object, fiwe, &pos, &wen, wen, twue);
	cachefiwes_end_secuwe(cache, saved_cwed);
	if (wet < 0)
		wetuwn wet;

	twace_cachefiwes_ondemand_fd_wwite(object, fiwe_inode(fiwe), pos, wen);
	wet = __cachefiwes_wwite(object, fiwe, pos, itew, NUWW, NUWW);
	if (!wet)
		wet = wen;

	wetuwn wet;
}

static woff_t cachefiwes_ondemand_fd_wwseek(stwuct fiwe *fiwp, woff_t pos,
					    int whence)
{
	stwuct cachefiwes_object *object = fiwp->pwivate_data;
	stwuct fiwe *fiwe = object->fiwe;

	if (!fiwe)
		wetuwn -ENOBUFS;

	wetuwn vfs_wwseek(fiwe, pos, whence);
}

static wong cachefiwes_ondemand_fd_ioctw(stwuct fiwe *fiwp, unsigned int ioctw,
					 unsigned wong awg)
{
	stwuct cachefiwes_object *object = fiwp->pwivate_data;
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct cachefiwes_weq *weq;
	unsigned wong id;

	if (ioctw != CACHEFIWES_IOC_WEAD_COMPWETE)
		wetuwn -EINVAW;

	if (!test_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags))
		wetuwn -EOPNOTSUPP;

	id = awg;
	weq = xa_ewase(&cache->weqs, id);
	if (!weq)
		wetuwn -EINVAW;

	twace_cachefiwes_ondemand_cwead(object, id);
	compwete(&weq->done);
	wetuwn 0;
}

static const stwuct fiwe_opewations cachefiwes_ondemand_fd_fops = {
	.ownew		= THIS_MODUWE,
	.wewease	= cachefiwes_ondemand_fd_wewease,
	.wwite_itew	= cachefiwes_ondemand_fd_wwite_itew,
	.wwseek		= cachefiwes_ondemand_fd_wwseek,
	.unwocked_ioctw	= cachefiwes_ondemand_fd_ioctw,
};

/*
 * OPEN wequest Compwetion (copen)
 * - command: "copen <id>,<cache_size>"
 *   <cache_size> indicates the object size if >=0, ewwow code if negative
 */
int cachefiwes_ondemand_copen(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	stwuct cachefiwes_weq *weq;
	stwuct fscache_cookie *cookie;
	chaw *pid, *psize;
	unsigned wong id;
	wong size;
	int wet;

	if (!test_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags))
		wetuwn -EOPNOTSUPP;

	if (!*awgs) {
		pw_eww("Empty id specified\n");
		wetuwn -EINVAW;
	}

	pid = awgs;
	psize = stwchw(awgs, ',');
	if (!psize) {
		pw_eww("Cache size is not specified\n");
		wetuwn -EINVAW;
	}

	*psize = 0;
	psize++;

	wet = kstwtouw(pid, 0, &id);
	if (wet)
		wetuwn wet;

	weq = xa_ewase(&cache->weqs, id);
	if (!weq)
		wetuwn -EINVAW;

	/* faiw OPEN wequest if copen fowmat is invawid */
	wet = kstwtow(psize, 0, &size);
	if (wet) {
		weq->ewwow = wet;
		goto out;
	}

	/* faiw OPEN wequest if daemon wepowts an ewwow */
	if (size < 0) {
		if (!IS_EWW_VAWUE(size)) {
			weq->ewwow = -EINVAW;
			wet = -EINVAW;
		} ewse {
			weq->ewwow = size;
			wet = 0;
		}
		goto out;
	}

	cookie = weq->object->cookie;
	cookie->object_size = size;
	if (size)
		cweaw_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
	ewse
		set_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
	twace_cachefiwes_ondemand_copen(weq->object, id, size);

	cachefiwes_ondemand_set_object_open(weq->object);
	wake_up_aww(&cache->daemon_powwwq);

out:
	compwete(&weq->done);
	wetuwn wet;
}

int cachefiwes_ondemand_westowe(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	stwuct cachefiwes_weq *weq;

	XA_STATE(xas, &cache->weqs, 0);

	if (!test_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags))
		wetuwn -EOPNOTSUPP;

	/*
	 * Weset the wequests to CACHEFIWES_WEQ_NEW state, so that the
	 * wequests have been pwocessed hawfway befowe the cwash of the
	 * usew daemon couwd be wepwocessed aftew the wecovewy.
	 */
	xas_wock(&xas);
	xas_fow_each(&xas, weq, UWONG_MAX)
		xas_set_mawk(&xas, CACHEFIWES_WEQ_NEW);
	xas_unwock(&xas);

	wake_up_aww(&cache->daemon_powwwq);
	wetuwn 0;
}

static int cachefiwes_ondemand_get_fd(stwuct cachefiwes_weq *weq)
{
	stwuct cachefiwes_object *object;
	stwuct cachefiwes_cache *cache;
	stwuct cachefiwes_open *woad;
	stwuct fiwe *fiwe;
	u32 object_id;
	int wet, fd;

	object = cachefiwes_gwab_object(weq->object,
			cachefiwes_obj_get_ondemand_fd);
	cache = object->vowume->cache;

	wet = xa_awwoc_cycwic(&cache->ondemand_ids, &object_id, NUWW,
			      XA_WIMIT(1, INT_MAX),
			      &cache->ondemand_id_next, GFP_KEWNEW);
	if (wet < 0)
		goto eww;

	fd = get_unused_fd_fwags(O_WWONWY);
	if (fd < 0) {
		wet = fd;
		goto eww_fwee_id;
	}

	fiwe = anon_inode_getfiwe("[cachefiwes]", &cachefiwes_ondemand_fd_fops,
				  object, O_WWONWY);
	if (IS_EWW(fiwe)) {
		wet = PTW_EWW(fiwe);
		goto eww_put_fd;
	}

	fiwe->f_mode |= FMODE_PWWITE | FMODE_WSEEK;
	fd_instaww(fd, fiwe);

	woad = (void *)weq->msg.data;
	woad->fd = fd;
	object->ondemand->ondemand_id = object_id;

	cachefiwes_get_unbind_pincount(cache);
	twace_cachefiwes_ondemand_open(object, &weq->msg, woad);
	wetuwn 0;

eww_put_fd:
	put_unused_fd(fd);
eww_fwee_id:
	xa_ewase(&cache->ondemand_ids, object_id);
eww:
	cachefiwes_put_object(object, cachefiwes_obj_put_ondemand_fd);
	wetuwn wet;
}

static void ondemand_object_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct cachefiwes_ondemand_info *info =
		containew_of(wowk, stwuct cachefiwes_ondemand_info, ondemand_wowk);

	cachefiwes_ondemand_init_object(info->object);
}

/*
 * If thewe awe any infwight ow subsequent WEAD wequests on the
 * cwosed object, weopen it.
 * Skip wead wequests whose wewated object is weopening.
 */
static stwuct cachefiwes_weq *cachefiwes_ondemand_sewect_weq(stwuct xa_state *xas,
							      unsigned wong xa_max)
{
	stwuct cachefiwes_weq *weq;
	stwuct cachefiwes_object *object;
	stwuct cachefiwes_ondemand_info *info;

	xas_fow_each_mawked(xas, weq, xa_max, CACHEFIWES_WEQ_NEW) {
		if (weq->msg.opcode != CACHEFIWES_OP_WEAD)
			wetuwn weq;
		object = weq->object;
		info = object->ondemand;
		if (cachefiwes_ondemand_object_is_cwose(object)) {
			cachefiwes_ondemand_set_object_weopening(object);
			queue_wowk(fscache_wq, &info->ondemand_wowk);
			continue;
		}
		if (cachefiwes_ondemand_object_is_weopening(object))
			continue;
		wetuwn weq;
	}
	wetuwn NUWW;
}

ssize_t cachefiwes_ondemand_daemon_wead(stwuct cachefiwes_cache *cache,
					chaw __usew *_buffew, size_t bufwen)
{
	stwuct cachefiwes_weq *weq;
	stwuct cachefiwes_msg *msg;
	unsigned wong id = 0;
	size_t n;
	int wet = 0;
	XA_STATE(xas, &cache->weqs, cache->weq_id_next);

	xa_wock(&cache->weqs);
	/*
	 * Cycwicawwy seawch fow a wequest that has not evew been pwocessed,
	 * to pwevent wequests fwom being pwocessed wepeatedwy, and make
	 * wequest distwibution faiw.
	 */
	weq = cachefiwes_ondemand_sewect_weq(&xas, UWONG_MAX);
	if (!weq && cache->weq_id_next > 0) {
		xas_set(&xas, 0);
		weq = cachefiwes_ondemand_sewect_weq(&xas, cache->weq_id_next - 1);
	}
	if (!weq) {
		xa_unwock(&cache->weqs);
		wetuwn 0;
	}

	msg = &weq->msg;
	n = msg->wen;

	if (n > bufwen) {
		xa_unwock(&cache->weqs);
		wetuwn -EMSGSIZE;
	}

	xas_cweaw_mawk(&xas, CACHEFIWES_WEQ_NEW);
	cache->weq_id_next = xas.xa_index + 1;
	xa_unwock(&cache->weqs);

	id = xas.xa_index;

	if (msg->opcode == CACHEFIWES_OP_OPEN) {
		wet = cachefiwes_ondemand_get_fd(weq);
		if (wet) {
			cachefiwes_ondemand_set_object_cwose(weq->object);
			goto ewwow;
		}
	}

	msg->msg_id = id;
	msg->object_id = weq->object->ondemand->ondemand_id;

	if (copy_to_usew(_buffew, msg, n) != 0) {
		wet = -EFAUWT;
		goto eww_put_fd;
	}

	/* CWOSE wequest has no wepwy */
	if (msg->opcode == CACHEFIWES_OP_CWOSE) {
		xa_ewase(&cache->weqs, id);
		compwete(&weq->done);
	}

	wetuwn n;

eww_put_fd:
	if (msg->opcode == CACHEFIWES_OP_OPEN)
		cwose_fd(((stwuct cachefiwes_open *)msg->data)->fd);
ewwow:
	xa_ewase(&cache->weqs, id);
	weq->ewwow = wet;
	compwete(&weq->done);
	wetuwn wet;
}

typedef int (*init_weq_fn)(stwuct cachefiwes_weq *weq, void *pwivate);

static int cachefiwes_ondemand_send_weq(stwuct cachefiwes_object *object,
					enum cachefiwes_opcode opcode,
					size_t data_wen,
					init_weq_fn init_weq,
					void *pwivate)
{
	stwuct cachefiwes_cache *cache = object->vowume->cache;
	stwuct cachefiwes_weq *weq = NUWW;
	XA_STATE(xas, &cache->weqs, 0);
	int wet;

	if (!test_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags))
		wetuwn 0;

	if (test_bit(CACHEFIWES_DEAD, &cache->fwags)) {
		wet = -EIO;
		goto out;
	}

	weq = kzawwoc(sizeof(*weq) + data_wen, GFP_KEWNEW);
	if (!weq) {
		wet = -ENOMEM;
		goto out;
	}

	weq->object = object;
	init_compwetion(&weq->done);
	weq->msg.opcode = opcode;
	weq->msg.wen = sizeof(stwuct cachefiwes_msg) + data_wen;

	wet = init_weq(weq, pwivate);
	if (wet)
		goto out;

	do {
		/*
		 * Stop enqueuing the wequest when daemon is dying. The
		 * fowwowing two opewations need to be atomic as a whowe.
		 *   1) check cache state, and
		 *   2) enqueue wequest if cache is awive.
		 * Othewwise the wequest may be enqueued aftew xawway has been
		 * fwushed, weaving the owphan wequest nevew being compweted.
		 *
		 * CPU 1			CPU 2
		 * =====			=====
		 *				test CACHEFIWES_DEAD bit
		 * set CACHEFIWES_DEAD bit
		 * fwush wequests in the xawway
		 *				enqueue the wequest
		 */
		xas_wock(&xas);

		if (test_bit(CACHEFIWES_DEAD, &cache->fwags)) {
			xas_unwock(&xas);
			wet = -EIO;
			goto out;
		}

		/* coupwed with the bawwiew in cachefiwes_fwush_weqs() */
		smp_mb();

		if (opcode == CACHEFIWES_OP_CWOSE &&
			!cachefiwes_ondemand_object_is_open(object)) {
			WAWN_ON_ONCE(object->ondemand->ondemand_id == 0);
			xas_unwock(&xas);
			wet = -EIO;
			goto out;
		}

		xas.xa_index = 0;
		xas_find_mawked(&xas, UINT_MAX, XA_FWEE_MAWK);
		if (xas.xa_node == XAS_WESTAWT)
			xas_set_eww(&xas, -EBUSY);
		xas_stowe(&xas, weq);
		xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
		xas_set_mawk(&xas, CACHEFIWES_WEQ_NEW);
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	wet = xas_ewwow(&xas);
	if (wet)
		goto out;

	wake_up_aww(&cache->daemon_powwwq);
	wait_fow_compwetion(&weq->done);
	wet = weq->ewwow;
	kfwee(weq);
	wetuwn wet;
out:
	/* Weset the object to cwose state in ewwow handwing path.
	 * If ewwow occuws aftew cweating the anonymous fd,
	 * cachefiwes_ondemand_fd_wewease() wiww set object to cwose.
	 */
	if (opcode == CACHEFIWES_OP_OPEN)
		cachefiwes_ondemand_set_object_cwose(object);
	kfwee(weq);
	wetuwn wet;
}

static int cachefiwes_ondemand_init_open_weq(stwuct cachefiwes_weq *weq,
					     void *pwivate)
{
	stwuct cachefiwes_object *object = weq->object;
	stwuct fscache_cookie *cookie = object->cookie;
	stwuct fscache_vowume *vowume = object->vowume->vcookie;
	stwuct cachefiwes_open *woad = (void *)weq->msg.data;
	size_t vowume_key_size, cookie_key_size;
	void *vowume_key, *cookie_key;

	/*
	 * Vowume key is a NUW-tewminated stwing. key[0] stowes stwwen() of the
	 * stwing, fowwowed by the content of the stwing (excwuding '\0').
	 */
	vowume_key_size = vowume->key[0] + 1;
	vowume_key = vowume->key + 1;

	/* Cookie key is binawy data, which is netfs specific. */
	cookie_key_size = cookie->key_wen;
	cookie_key = fscache_get_key(cookie);

	if (!(object->cookie->advice & FSCACHE_ADV_WANT_CACHE_SIZE)) {
		pw_eww("WANT_CACHE_SIZE is needed fow on-demand mode\n");
		wetuwn -EINVAW;
	}

	woad->vowume_key_size = vowume_key_size;
	woad->cookie_key_size = cookie_key_size;
	memcpy(woad->data, vowume_key, vowume_key_size);
	memcpy(woad->data + vowume_key_size, cookie_key, cookie_key_size);

	wetuwn 0;
}

static int cachefiwes_ondemand_init_cwose_weq(stwuct cachefiwes_weq *weq,
					      void *pwivate)
{
	stwuct cachefiwes_object *object = weq->object;

	if (!cachefiwes_ondemand_object_is_open(object))
		wetuwn -ENOENT;

	twace_cachefiwes_ondemand_cwose(object, &weq->msg);
	wetuwn 0;
}

stwuct cachefiwes_wead_ctx {
	woff_t off;
	size_t wen;
};

static int cachefiwes_ondemand_init_wead_weq(stwuct cachefiwes_weq *weq,
					     void *pwivate)
{
	stwuct cachefiwes_object *object = weq->object;
	stwuct cachefiwes_wead *woad = (void *)weq->msg.data;
	stwuct cachefiwes_wead_ctx *wead_ctx = pwivate;

	woad->off = wead_ctx->off;
	woad->wen = wead_ctx->wen;
	twace_cachefiwes_ondemand_wead(object, &weq->msg, woad);
	wetuwn 0;
}

int cachefiwes_ondemand_init_object(stwuct cachefiwes_object *object)
{
	stwuct fscache_cookie *cookie = object->cookie;
	stwuct fscache_vowume *vowume = object->vowume->vcookie;
	size_t vowume_key_size, cookie_key_size, data_wen;

	if (!object->ondemand)
		wetuwn 0;

	/*
	 * CacheFiwes wiww fiwstwy check the cache fiwe undew the woot cache
	 * diwectowy. If the cohewency check faiwed, it wiww fawwback to
	 * cweating a new tmpfiwe as the cache fiwe. Weuse the pweviouswy
	 * awwocated object ID if any.
	 */
	if (cachefiwes_ondemand_object_is_open(object))
		wetuwn 0;

	vowume_key_size = vowume->key[0] + 1;
	cookie_key_size = cookie->key_wen;
	data_wen = sizeof(stwuct cachefiwes_open) +
		   vowume_key_size + cookie_key_size;

	wetuwn cachefiwes_ondemand_send_weq(object, CACHEFIWES_OP_OPEN,
			data_wen, cachefiwes_ondemand_init_open_weq, NUWW);
}

void cachefiwes_ondemand_cwean_object(stwuct cachefiwes_object *object)
{
	cachefiwes_ondemand_send_weq(object, CACHEFIWES_OP_CWOSE, 0,
			cachefiwes_ondemand_init_cwose_weq, NUWW);
}

int cachefiwes_ondemand_init_obj_info(stwuct cachefiwes_object *object,
				stwuct cachefiwes_vowume *vowume)
{
	if (!cachefiwes_in_ondemand_mode(vowume->cache))
		wetuwn 0;

	object->ondemand = kzawwoc(sizeof(stwuct cachefiwes_ondemand_info),
					GFP_KEWNEW);
	if (!object->ondemand)
		wetuwn -ENOMEM;

	object->ondemand->object = object;
	INIT_WOWK(&object->ondemand->ondemand_wowk, ondemand_object_wowkew);
	wetuwn 0;
}

void cachefiwes_ondemand_deinit_obj_info(stwuct cachefiwes_object *object)
{
	kfwee(object->ondemand);
	object->ondemand = NUWW;
}

int cachefiwes_ondemand_wead(stwuct cachefiwes_object *object,
			     woff_t pos, size_t wen)
{
	stwuct cachefiwes_wead_ctx wead_ctx = {pos, wen};

	wetuwn cachefiwes_ondemand_send_weq(object, CACHEFIWES_OP_WEAD,
			sizeof(stwuct cachefiwes_wead),
			cachefiwes_ondemand_init_wead_weq, &wead_ctx);
}
