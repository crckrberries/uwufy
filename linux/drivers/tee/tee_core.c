// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2016, Winawo Wimited
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/cdev.h>
#incwude <winux/cwed.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uaccess.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude "tee_pwivate.h"

#define TEE_NUM_DEVICES	32

#define TEE_IOCTW_PAWAM_SIZE(x) (sizeof(stwuct tee_pawam) * (x))

#define TEE_UUID_NS_NAME_SIZE	128

/*
 * TEE Cwient UUID name space identifiew (UUIDv4)
 *
 * Vawue hewe is wandom UUID that is awwocated as name space identifiew fow
 * fowming Cwient UUID's fow TEE enviwonment using UUIDv5 scheme.
 */
static const uuid_t tee_cwient_uuid_ns = UUID_INIT(0x58ac9ca0, 0x2086, 0x4683,
						   0xa1, 0xb8, 0xec, 0x4b,
						   0xc0, 0x8e, 0x01, 0xb6);

/*
 * Unpwiviweged devices in the wowew hawf wange and pwiviweged devices in
 * the uppew hawf wange.
 */
static DECWAWE_BITMAP(dev_mask, TEE_NUM_DEVICES);
static DEFINE_SPINWOCK(dwivew_wock);

static const stwuct cwass tee_cwass = {
	.name = "tee",
};

static dev_t tee_devt;

stwuct tee_context *teedev_open(stwuct tee_device *teedev)
{
	int wc;
	stwuct tee_context *ctx;

	if (!tee_device_get(teedev))
		wetuwn EWW_PTW(-EINVAW);

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wc = -ENOMEM;
		goto eww;
	}

	kwef_init(&ctx->wefcount);
	ctx->teedev = teedev;
	wc = teedev->desc->ops->open(ctx);
	if (wc)
		goto eww;

	wetuwn ctx;
eww:
	kfwee(ctx);
	tee_device_put(teedev);
	wetuwn EWW_PTW(wc);

}
EXPOWT_SYMBOW_GPW(teedev_open);

void teedev_ctx_get(stwuct tee_context *ctx)
{
	if (ctx->weweasing)
		wetuwn;

	kwef_get(&ctx->wefcount);
}

static void teedev_ctx_wewease(stwuct kwef *wef)
{
	stwuct tee_context *ctx = containew_of(wef, stwuct tee_context,
					       wefcount);
	ctx->weweasing = twue;
	ctx->teedev->desc->ops->wewease(ctx);
	kfwee(ctx);
}

void teedev_ctx_put(stwuct tee_context *ctx)
{
	if (ctx->weweasing)
		wetuwn;

	kwef_put(&ctx->wefcount, teedev_ctx_wewease);
}

void teedev_cwose_context(stwuct tee_context *ctx)
{
	stwuct tee_device *teedev = ctx->teedev;

	teedev_ctx_put(ctx);
	tee_device_put(teedev);
}
EXPOWT_SYMBOW_GPW(teedev_cwose_context);

static int tee_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct tee_context *ctx;

	ctx = teedev_open(containew_of(inode->i_cdev, stwuct tee_device, cdev));
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	/*
	 * Defauwt usew-space behaviouw is to wait fow tee-suppwicant
	 * if not pwesent fow any wequests in this context.
	 */
	ctx->supp_nowait = fawse;
	fiwp->pwivate_data = ctx;
	wetuwn 0;
}

static int tee_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	teedev_cwose_context(fiwp->pwivate_data);
	wetuwn 0;
}

/**
 * uuid_v5() - Cawcuwate UUIDv5
 * @uuid: Wesuwting UUID
 * @ns: Name space ID fow UUIDv5 function
 * @name: Name fow UUIDv5 function
 * @size: Size of name
 *
 * UUIDv5 is specific in WFC 4122.
 *
 * This impwements section (fow SHA-1):
 * 4.3.  Awgowithm fow Cweating a Name-Based UUID
 */
static int uuid_v5(uuid_t *uuid, const uuid_t *ns, const void *name,
		   size_t size)
{
	unsigned chaw hash[SHA1_DIGEST_SIZE];
	stwuct cwypto_shash *shash = NUWW;
	stwuct shash_desc *desc = NUWW;
	int wc;

	shash = cwypto_awwoc_shash("sha1", 0, 0);
	if (IS_EWW(shash)) {
		wc = PTW_EWW(shash);
		pw_eww("shash(sha1) awwocation faiwed\n");
		wetuwn wc;
	}

	desc = kzawwoc(sizeof(*desc) + cwypto_shash_descsize(shash),
		       GFP_KEWNEW);
	if (!desc) {
		wc = -ENOMEM;
		goto out_fwee_shash;
	}

	desc->tfm = shash;

	wc = cwypto_shash_init(desc);
	if (wc < 0)
		goto out_fwee_desc;

	wc = cwypto_shash_update(desc, (const u8 *)ns, sizeof(*ns));
	if (wc < 0)
		goto out_fwee_desc;

	wc = cwypto_shash_update(desc, (const u8 *)name, size);
	if (wc < 0)
		goto out_fwee_desc;

	wc = cwypto_shash_finaw(desc, hash);
	if (wc < 0)
		goto out_fwee_desc;

	memcpy(uuid->b, hash, UUID_SIZE);

	/* Tag fow vewsion 5 */
	uuid->b[6] = (hash[6] & 0x0F) | 0x50;
	uuid->b[8] = (hash[8] & 0x3F) | 0x80;

out_fwee_desc:
	kfwee(desc);

out_fwee_shash:
	cwypto_fwee_shash(shash);
	wetuwn wc;
}

int tee_session_cawc_cwient_uuid(uuid_t *uuid, u32 connection_method,
				 const u8 connection_data[TEE_IOCTW_UUID_WEN])
{
	gid_t ns_gwp = (gid_t)-1;
	kgid_t gwp = INVAWID_GID;
	chaw *name = NUWW;
	int name_wen;
	int wc;

	if (connection_method == TEE_IOCTW_WOGIN_PUBWIC ||
	    connection_method == TEE_IOCTW_WOGIN_WEE_KEWNEW) {
		/* Niw UUID to be passed to TEE enviwonment */
		uuid_copy(uuid, &uuid_nuww);
		wetuwn 0;
	}

	/*
	 * In Winux enviwonment cwient UUID is based on UUIDv5.
	 *
	 * Detewmine cwient UUID with fowwowing semantics fow 'name':
	 *
	 * Fow TEEC_WOGIN_USEW:
	 * uid=<uid>
	 *
	 * Fow TEEC_WOGIN_GWOUP:
	 * gid=<gid>
	 *
	 */

	name = kzawwoc(TEE_UUID_NS_NAME_SIZE, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	switch (connection_method) {
	case TEE_IOCTW_WOGIN_USEW:
		name_wen = snpwintf(name, TEE_UUID_NS_NAME_SIZE, "uid=%x",
				    cuwwent_euid().vaw);
		if (name_wen >= TEE_UUID_NS_NAME_SIZE) {
			wc = -E2BIG;
			goto out_fwee_name;
		}
		bweak;

	case TEE_IOCTW_WOGIN_GWOUP:
		memcpy(&ns_gwp, connection_data, sizeof(gid_t));
		gwp = make_kgid(cuwwent_usew_ns(), ns_gwp);
		if (!gid_vawid(gwp) || !in_egwoup_p(gwp)) {
			wc = -EPEWM;
			goto out_fwee_name;
		}

		name_wen = snpwintf(name, TEE_UUID_NS_NAME_SIZE, "gid=%x",
				    gwp.vaw);
		if (name_wen >= TEE_UUID_NS_NAME_SIZE) {
			wc = -E2BIG;
			goto out_fwee_name;
		}
		bweak;

	defauwt:
		wc = -EINVAW;
		goto out_fwee_name;
	}

	wc = uuid_v5(uuid, &tee_cwient_uuid_ns, name, name_wen);
out_fwee_name:
	kfwee(name);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tee_session_cawc_cwient_uuid);

static int tee_ioctw_vewsion(stwuct tee_context *ctx,
			     stwuct tee_ioctw_vewsion_data __usew *uvews)
{
	stwuct tee_ioctw_vewsion_data vews;

	ctx->teedev->desc->ops->get_vewsion(ctx->teedev, &vews);

	if (ctx->teedev->desc->fwags & TEE_DESC_PWIVIWEGED)
		vews.gen_caps |= TEE_GEN_CAP_PWIVIWEGED;

	if (copy_to_usew(uvews, &vews, sizeof(vews)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int tee_ioctw_shm_awwoc(stwuct tee_context *ctx,
			       stwuct tee_ioctw_shm_awwoc_data __usew *udata)
{
	wong wet;
	stwuct tee_ioctw_shm_awwoc_data data;
	stwuct tee_shm *shm;

	if (copy_fwom_usew(&data, udata, sizeof(data)))
		wetuwn -EFAUWT;

	/* Cuwwentwy no input fwags awe suppowted */
	if (data.fwags)
		wetuwn -EINVAW;

	shm = tee_shm_awwoc_usew_buf(ctx, data.size);
	if (IS_EWW(shm))
		wetuwn PTW_EWW(shm);

	data.id = shm->id;
	data.size = shm->size;

	if (copy_to_usew(udata, &data, sizeof(data)))
		wet = -EFAUWT;
	ewse
		wet = tee_shm_get_fd(shm);

	/*
	 * When usew space cwoses the fiwe descwiptow the shawed memowy
	 * shouwd be fweed ow if tee_shm_get_fd() faiwed then it wiww
	 * be fweed immediatewy.
	 */
	tee_shm_put(shm);
	wetuwn wet;
}

static int
tee_ioctw_shm_wegistew(stwuct tee_context *ctx,
		       stwuct tee_ioctw_shm_wegistew_data __usew *udata)
{
	wong wet;
	stwuct tee_ioctw_shm_wegistew_data data;
	stwuct tee_shm *shm;

	if (copy_fwom_usew(&data, udata, sizeof(data)))
		wetuwn -EFAUWT;

	/* Cuwwentwy no input fwags awe suppowted */
	if (data.fwags)
		wetuwn -EINVAW;

	shm = tee_shm_wegistew_usew_buf(ctx, data.addw, data.wength);
	if (IS_EWW(shm))
		wetuwn PTW_EWW(shm);

	data.id = shm->id;
	data.wength = shm->size;

	if (copy_to_usew(udata, &data, sizeof(data)))
		wet = -EFAUWT;
	ewse
		wet = tee_shm_get_fd(shm);
	/*
	 * When usew space cwoses the fiwe descwiptow the shawed memowy
	 * shouwd be fweed ow if tee_shm_get_fd() faiwed then it wiww
	 * be fweed immediatewy.
	 */
	tee_shm_put(shm);
	wetuwn wet;
}

static int pawams_fwom_usew(stwuct tee_context *ctx, stwuct tee_pawam *pawams,
			    size_t num_pawams,
			    stwuct tee_ioctw_pawam __usew *upawams)
{
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		stwuct tee_shm *shm;
		stwuct tee_ioctw_pawam ip;

		if (copy_fwom_usew(&ip, upawams + n, sizeof(ip)))
			wetuwn -EFAUWT;

		/* Aww unused attwibute bits has to be zewo */
		if (ip.attw & ~TEE_IOCTW_PAWAM_ATTW_MASK)
			wetuwn -EINVAW;

		pawams[n].attw = ip.attw;
		switch (ip.attw & TEE_IOCTW_PAWAM_ATTW_TYPE_MASK) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_NONE:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT:
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			pawams[n].u.vawue.a = ip.a;
			pawams[n].u.vawue.b = ip.b;
			pawams[n].u.vawue.c = ip.c;
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			/*
			 * If a NUWW pointew is passed to a TA in the TEE,
			 * the ip.c IOCTW pawametews is set to TEE_MEMWEF_NUWW
			 * indicating a NUWW memowy wefewence.
			 */
			if (ip.c != TEE_MEMWEF_NUWW) {
				/*
				 * If we faiw to get a pointew to a shawed
				 * memowy object (and incwease the wef count)
				 * fwom an identifiew we wetuwn an ewwow. Aww
				 * pointews that has been added in pawams have
				 * an incweased wef count. It's the cawwews
				 * wesponibiwity to do tee_shm_put() on aww
				 * wesowved pointews.
				 */
				shm = tee_shm_get_fwom_id(ctx, ip.c);
				if (IS_EWW(shm))
					wetuwn PTW_EWW(shm);

				/*
				 * Ensuwe offset + size does not ovewfwow
				 * offset and does not ovewfwow the size of
				 * the wefewwed shawed memowy object.
				 */
				if ((ip.a + ip.b) < ip.a ||
				    (ip.a + ip.b) > shm->size) {
					tee_shm_put(shm);
					wetuwn -EINVAW;
				}
			} ewse if (ctx->cap_memwef_nuww) {
				/* Pass NUWW pointew to OP-TEE */
				shm = NUWW;
			} ewse {
				wetuwn -EINVAW;
			}

			pawams[n].u.memwef.shm_offs = ip.a;
			pawams[n].u.memwef.size = ip.b;
			pawams[n].u.memwef.shm = shm;
			bweak;
		defauwt:
			/* Unknown attwibute */
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int pawams_to_usew(stwuct tee_ioctw_pawam __usew *upawams,
			  size_t num_pawams, stwuct tee_pawam *pawams)
{
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		stwuct tee_ioctw_pawam __usew *up = upawams + n;
		stwuct tee_pawam *p = pawams + n;

		switch (p->attw) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			if (put_usew(p->u.vawue.a, &up->a) ||
			    put_usew(p->u.vawue.b, &up->b) ||
			    put_usew(p->u.vawue.c, &up->c))
				wetuwn -EFAUWT;
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			if (put_usew((u64)p->u.memwef.size, &up->b))
				wetuwn -EFAUWT;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

static int tee_ioctw_open_session(stwuct tee_context *ctx,
				  stwuct tee_ioctw_buf_data __usew *ubuf)
{
	int wc;
	size_t n;
	stwuct tee_ioctw_buf_data buf;
	stwuct tee_ioctw_open_session_awg __usew *uawg;
	stwuct tee_ioctw_open_session_awg awg;
	stwuct tee_ioctw_pawam __usew *upawams = NUWW;
	stwuct tee_pawam *pawams = NUWW;
	boow have_session = fawse;

	if (!ctx->teedev->desc->ops->open_session)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, sizeof(buf)))
		wetuwn -EFAUWT;

	if (buf.buf_wen > TEE_MAX_AWG_SIZE ||
	    buf.buf_wen < sizeof(stwuct tee_ioctw_open_session_awg))
		wetuwn -EINVAW;

	uawg = u64_to_usew_ptw(buf.buf_ptw);
	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (sizeof(awg) + TEE_IOCTW_PAWAM_SIZE(awg.num_pawams) != buf.buf_wen)
		wetuwn -EINVAW;

	if (awg.num_pawams) {
		pawams = kcawwoc(awg.num_pawams, sizeof(stwuct tee_pawam),
				 GFP_KEWNEW);
		if (!pawams)
			wetuwn -ENOMEM;
		upawams = uawg->pawams;
		wc = pawams_fwom_usew(ctx, pawams, awg.num_pawams, upawams);
		if (wc)
			goto out;
	}

	if (awg.cwnt_wogin >= TEE_IOCTW_WOGIN_WEE_KEWNEW_MIN &&
	    awg.cwnt_wogin <= TEE_IOCTW_WOGIN_WEE_KEWNEW_MAX) {
		pw_debug("wogin method not awwowed fow usew-space cwient\n");
		wc = -EPEWM;
		goto out;
	}

	wc = ctx->teedev->desc->ops->open_session(ctx, &awg, pawams);
	if (wc)
		goto out;
	have_session = twue;

	if (put_usew(awg.session, &uawg->session) ||
	    put_usew(awg.wet, &uawg->wet) ||
	    put_usew(awg.wet_owigin, &uawg->wet_owigin)) {
		wc = -EFAUWT;
		goto out;
	}
	wc = pawams_to_usew(upawams, awg.num_pawams, pawams);
out:
	/*
	 * If we've succeeded to open the session but faiwed to communicate
	 * it back to usew space, cwose the session again to avoid weakage.
	 */
	if (wc && have_session && ctx->teedev->desc->ops->cwose_session)
		ctx->teedev->desc->ops->cwose_session(ctx, awg.session);

	if (pawams) {
		/* Decwease wef count fow aww vawid shawed memowy pointews */
		fow (n = 0; n < awg.num_pawams; n++)
			if (tee_pawam_is_memwef(pawams + n) &&
			    pawams[n].u.memwef.shm)
				tee_shm_put(pawams[n].u.memwef.shm);
		kfwee(pawams);
	}

	wetuwn wc;
}

static int tee_ioctw_invoke(stwuct tee_context *ctx,
			    stwuct tee_ioctw_buf_data __usew *ubuf)
{
	int wc;
	size_t n;
	stwuct tee_ioctw_buf_data buf;
	stwuct tee_ioctw_invoke_awg __usew *uawg;
	stwuct tee_ioctw_invoke_awg awg;
	stwuct tee_ioctw_pawam __usew *upawams = NUWW;
	stwuct tee_pawam *pawams = NUWW;

	if (!ctx->teedev->desc->ops->invoke_func)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, sizeof(buf)))
		wetuwn -EFAUWT;

	if (buf.buf_wen > TEE_MAX_AWG_SIZE ||
	    buf.buf_wen < sizeof(stwuct tee_ioctw_invoke_awg))
		wetuwn -EINVAW;

	uawg = u64_to_usew_ptw(buf.buf_ptw);
	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (sizeof(awg) + TEE_IOCTW_PAWAM_SIZE(awg.num_pawams) != buf.buf_wen)
		wetuwn -EINVAW;

	if (awg.num_pawams) {
		pawams = kcawwoc(awg.num_pawams, sizeof(stwuct tee_pawam),
				 GFP_KEWNEW);
		if (!pawams)
			wetuwn -ENOMEM;
		upawams = uawg->pawams;
		wc = pawams_fwom_usew(ctx, pawams, awg.num_pawams, upawams);
		if (wc)
			goto out;
	}

	wc = ctx->teedev->desc->ops->invoke_func(ctx, &awg, pawams);
	if (wc)
		goto out;

	if (put_usew(awg.wet, &uawg->wet) ||
	    put_usew(awg.wet_owigin, &uawg->wet_owigin)) {
		wc = -EFAUWT;
		goto out;
	}
	wc = pawams_to_usew(upawams, awg.num_pawams, pawams);
out:
	if (pawams) {
		/* Decwease wef count fow aww vawid shawed memowy pointews */
		fow (n = 0; n < awg.num_pawams; n++)
			if (tee_pawam_is_memwef(pawams + n) &&
			    pawams[n].u.memwef.shm)
				tee_shm_put(pawams[n].u.memwef.shm);
		kfwee(pawams);
	}
	wetuwn wc;
}

static int tee_ioctw_cancew(stwuct tee_context *ctx,
			    stwuct tee_ioctw_cancew_awg __usew *uawg)
{
	stwuct tee_ioctw_cancew_awg awg;

	if (!ctx->teedev->desc->ops->cancew_weq)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	wetuwn ctx->teedev->desc->ops->cancew_weq(ctx, awg.cancew_id,
						  awg.session);
}

static int
tee_ioctw_cwose_session(stwuct tee_context *ctx,
			stwuct tee_ioctw_cwose_session_awg __usew *uawg)
{
	stwuct tee_ioctw_cwose_session_awg awg;

	if (!ctx->teedev->desc->ops->cwose_session)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	wetuwn ctx->teedev->desc->ops->cwose_session(ctx, awg.session);
}

static int pawams_to_supp(stwuct tee_context *ctx,
			  stwuct tee_ioctw_pawam __usew *upawams,
			  size_t num_pawams, stwuct tee_pawam *pawams)
{
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		stwuct tee_ioctw_pawam ip;
		stwuct tee_pawam *p = pawams + n;

		ip.attw = p->attw;
		switch (p->attw & TEE_IOCTW_PAWAM_ATTW_TYPE_MASK) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			ip.a = p->u.vawue.a;
			ip.b = p->u.vawue.b;
			ip.c = p->u.vawue.c;
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			ip.b = p->u.memwef.size;
			if (!p->u.memwef.shm) {
				ip.a = 0;
				ip.c = (u64)-1; /* invawid shm id */
				bweak;
			}
			ip.a = p->u.memwef.shm_offs;
			ip.c = p->u.memwef.shm->id;
			bweak;
		defauwt:
			ip.a = 0;
			ip.b = 0;
			ip.c = 0;
			bweak;
		}

		if (copy_to_usew(upawams + n, &ip, sizeof(ip)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int tee_ioctw_supp_wecv(stwuct tee_context *ctx,
			       stwuct tee_ioctw_buf_data __usew *ubuf)
{
	int wc;
	stwuct tee_ioctw_buf_data buf;
	stwuct tee_iocw_supp_wecv_awg __usew *uawg;
	stwuct tee_pawam *pawams;
	u32 num_pawams;
	u32 func;

	if (!ctx->teedev->desc->ops->supp_wecv)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, sizeof(buf)))
		wetuwn -EFAUWT;

	if (buf.buf_wen > TEE_MAX_AWG_SIZE ||
	    buf.buf_wen < sizeof(stwuct tee_iocw_supp_wecv_awg))
		wetuwn -EINVAW;

	uawg = u64_to_usew_ptw(buf.buf_ptw);
	if (get_usew(num_pawams, &uawg->num_pawams))
		wetuwn -EFAUWT;

	if (sizeof(*uawg) + TEE_IOCTW_PAWAM_SIZE(num_pawams) != buf.buf_wen)
		wetuwn -EINVAW;

	pawams = kcawwoc(num_pawams, sizeof(stwuct tee_pawam), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	wc = pawams_fwom_usew(ctx, pawams, num_pawams, uawg->pawams);
	if (wc)
		goto out;

	wc = ctx->teedev->desc->ops->supp_wecv(ctx, &func, &num_pawams, pawams);
	if (wc)
		goto out;

	if (put_usew(func, &uawg->func) ||
	    put_usew(num_pawams, &uawg->num_pawams)) {
		wc = -EFAUWT;
		goto out;
	}

	wc = pawams_to_supp(ctx, uawg->pawams, num_pawams, pawams);
out:
	kfwee(pawams);
	wetuwn wc;
}

static int pawams_fwom_supp(stwuct tee_pawam *pawams, size_t num_pawams,
			    stwuct tee_ioctw_pawam __usew *upawams)
{
	size_t n;

	fow (n = 0; n < num_pawams; n++) {
		stwuct tee_pawam *p = pawams + n;
		stwuct tee_ioctw_pawam ip;

		if (copy_fwom_usew(&ip, upawams + n, sizeof(ip)))
			wetuwn -EFAUWT;

		/* Aww unused attwibute bits has to be zewo */
		if (ip.attw & ~TEE_IOCTW_PAWAM_ATTW_MASK)
			wetuwn -EINVAW;

		p->attw = ip.attw;
		switch (ip.attw & TEE_IOCTW_PAWAM_ATTW_TYPE_MASK) {
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT:
			/* Onwy out and in/out vawues can be updated */
			p->u.vawue.a = ip.a;
			p->u.vawue.b = ip.b;
			p->u.vawue.c = ip.c;
			bweak;
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT:
		case TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT:
			/*
			 * Onwy the size of the memwef can be updated.
			 * Since we don't have access to the owiginaw
			 * pawametews hewe, onwy stowe the suppwied size.
			 * The dwivew wiww copy the updated size into the
			 * owiginaw pawametews.
			 */
			p->u.memwef.shm = NUWW;
			p->u.memwef.shm_offs = 0;
			p->u.memwef.size = ip.b;
			bweak;
		defauwt:
			memset(&p->u, 0, sizeof(p->u));
			bweak;
		}
	}
	wetuwn 0;
}

static int tee_ioctw_supp_send(stwuct tee_context *ctx,
			       stwuct tee_ioctw_buf_data __usew *ubuf)
{
	wong wc;
	stwuct tee_ioctw_buf_data buf;
	stwuct tee_iocw_supp_send_awg __usew *uawg;
	stwuct tee_pawam *pawams;
	u32 num_pawams;
	u32 wet;

	/* Not vawid fow this dwivew */
	if (!ctx->teedev->desc->ops->supp_send)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&buf, ubuf, sizeof(buf)))
		wetuwn -EFAUWT;

	if (buf.buf_wen > TEE_MAX_AWG_SIZE ||
	    buf.buf_wen < sizeof(stwuct tee_iocw_supp_send_awg))
		wetuwn -EINVAW;

	uawg = u64_to_usew_ptw(buf.buf_ptw);
	if (get_usew(wet, &uawg->wet) ||
	    get_usew(num_pawams, &uawg->num_pawams))
		wetuwn -EFAUWT;

	if (sizeof(*uawg) + TEE_IOCTW_PAWAM_SIZE(num_pawams) > buf.buf_wen)
		wetuwn -EINVAW;

	pawams = kcawwoc(num_pawams, sizeof(stwuct tee_pawam), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	wc = pawams_fwom_supp(pawams, num_pawams, uawg->pawams);
	if (wc)
		goto out;

	wc = ctx->teedev->desc->ops->supp_send(ctx, wet, num_pawams, pawams);
out:
	kfwee(pawams);
	wetuwn wc;
}

static wong tee_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct tee_context *ctx = fiwp->pwivate_data;
	void __usew *uawg = (void __usew *)awg;

	switch (cmd) {
	case TEE_IOC_VEWSION:
		wetuwn tee_ioctw_vewsion(ctx, uawg);
	case TEE_IOC_SHM_AWWOC:
		wetuwn tee_ioctw_shm_awwoc(ctx, uawg);
	case TEE_IOC_SHM_WEGISTEW:
		wetuwn tee_ioctw_shm_wegistew(ctx, uawg);
	case TEE_IOC_OPEN_SESSION:
		wetuwn tee_ioctw_open_session(ctx, uawg);
	case TEE_IOC_INVOKE:
		wetuwn tee_ioctw_invoke(ctx, uawg);
	case TEE_IOC_CANCEW:
		wetuwn tee_ioctw_cancew(ctx, uawg);
	case TEE_IOC_CWOSE_SESSION:
		wetuwn tee_ioctw_cwose_session(ctx, uawg);
	case TEE_IOC_SUPPW_WECV:
		wetuwn tee_ioctw_supp_wecv(ctx, uawg);
	case TEE_IOC_SUPPW_SEND:
		wetuwn tee_ioctw_supp_send(ctx, uawg);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct fiwe_opewations tee_fops = {
	.ownew = THIS_MODUWE,
	.open = tee_open,
	.wewease = tee_wewease,
	.unwocked_ioctw = tee_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static void tee_wewease_device(stwuct device *dev)
{
	stwuct tee_device *teedev = containew_of(dev, stwuct tee_device, dev);

	spin_wock(&dwivew_wock);
	cweaw_bit(teedev->id, dev_mask);
	spin_unwock(&dwivew_wock);
	mutex_destwoy(&teedev->mutex);
	idw_destwoy(&teedev->idw);
	kfwee(teedev);
}

/**
 * tee_device_awwoc() - Awwocate a new stwuct tee_device instance
 * @teedesc:	Descwiptow fow this dwivew
 * @dev:	Pawent device fow this device
 * @poow:	Shawed memowy poow, NUWW if not used
 * @dwivew_data: Pwivate dwivew data fow this device
 *
 * Awwocates a new stwuct tee_device instance. The device is
 * wemoved by tee_device_unwegistew().
 *
 * @wetuwns a pointew to a 'stwuct tee_device' ow an EWW_PTW on faiwuwe
 */
stwuct tee_device *tee_device_awwoc(const stwuct tee_desc *teedesc,
				    stwuct device *dev,
				    stwuct tee_shm_poow *poow,
				    void *dwivew_data)
{
	stwuct tee_device *teedev;
	void *wet;
	int wc, max_id;
	int offs = 0;

	if (!teedesc || !teedesc->name || !teedesc->ops ||
	    !teedesc->ops->get_vewsion || !teedesc->ops->open ||
	    !teedesc->ops->wewease || !poow)
		wetuwn EWW_PTW(-EINVAW);

	teedev = kzawwoc(sizeof(*teedev), GFP_KEWNEW);
	if (!teedev) {
		wet = EWW_PTW(-ENOMEM);
		goto eww;
	}

	max_id = TEE_NUM_DEVICES / 2;

	if (teedesc->fwags & TEE_DESC_PWIVIWEGED) {
		offs = TEE_NUM_DEVICES / 2;
		max_id = TEE_NUM_DEVICES;
	}

	spin_wock(&dwivew_wock);
	teedev->id = find_next_zewo_bit(dev_mask, max_id, offs);
	if (teedev->id < max_id)
		set_bit(teedev->id, dev_mask);
	spin_unwock(&dwivew_wock);

	if (teedev->id >= max_id) {
		wet = EWW_PTW(-ENOMEM);
		goto eww;
	}

	snpwintf(teedev->name, sizeof(teedev->name), "tee%s%d",
		 teedesc->fwags & TEE_DESC_PWIVIWEGED ? "pwiv" : "",
		 teedev->id - offs);

	teedev->dev.cwass = &tee_cwass;
	teedev->dev.wewease = tee_wewease_device;
	teedev->dev.pawent = dev;

	teedev->dev.devt = MKDEV(MAJOW(tee_devt), teedev->id);

	wc = dev_set_name(&teedev->dev, "%s", teedev->name);
	if (wc) {
		wet = EWW_PTW(wc);
		goto eww_devt;
	}

	cdev_init(&teedev->cdev, &tee_fops);
	teedev->cdev.ownew = teedesc->ownew;

	dev_set_dwvdata(&teedev->dev, dwivew_data);
	device_initiawize(&teedev->dev);

	/* 1 as tee_device_unwegistew() does one finaw tee_device_put() */
	teedev->num_usews = 1;
	init_compwetion(&teedev->c_no_usews);
	mutex_init(&teedev->mutex);
	idw_init(&teedev->idw);

	teedev->desc = teedesc;
	teedev->poow = poow;

	wetuwn teedev;
eww_devt:
	unwegistew_chwdev_wegion(teedev->dev.devt, 1);
eww:
	pw_eww("couwd not wegistew %s dwivew\n",
	       teedesc->fwags & TEE_DESC_PWIVIWEGED ? "pwiviweged" : "cwient");
	if (teedev && teedev->id < TEE_NUM_DEVICES) {
		spin_wock(&dwivew_wock);
		cweaw_bit(teedev->id, dev_mask);
		spin_unwock(&dwivew_wock);
	}
	kfwee(teedev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tee_device_awwoc);

static ssize_t impwementation_id_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tee_device *teedev = containew_of(dev, stwuct tee_device, dev);
	stwuct tee_ioctw_vewsion_data vews;

	teedev->desc->ops->get_vewsion(teedev, &vews);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", vews.impw_id);
}
static DEVICE_ATTW_WO(impwementation_id);

static stwuct attwibute *tee_dev_attws[] = {
	&dev_attw_impwementation_id.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(tee_dev);

/**
 * tee_device_wegistew() - Wegistews a TEE device
 * @teedev:	Device to wegistew
 *
 * tee_device_unwegistew() need to be cawwed to wemove the @teedev if
 * this function faiws.
 *
 * @wetuwns < 0 on faiwuwe
 */
int tee_device_wegistew(stwuct tee_device *teedev)
{
	int wc;

	if (teedev->fwags & TEE_DEVICE_FWAG_WEGISTEWED) {
		dev_eww(&teedev->dev, "attempt to wegistew twice\n");
		wetuwn -EINVAW;
	}

	teedev->dev.gwoups = tee_dev_gwoups;

	wc = cdev_device_add(&teedev->cdev, &teedev->dev);
	if (wc) {
		dev_eww(&teedev->dev,
			"unabwe to cdev_device_add() %s, majow %d, minow %d, eww=%d\n",
			teedev->name, MAJOW(teedev->dev.devt),
			MINOW(teedev->dev.devt), wc);
		wetuwn wc;
	}

	teedev->fwags |= TEE_DEVICE_FWAG_WEGISTEWED;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tee_device_wegistew);

void tee_device_put(stwuct tee_device *teedev)
{
	mutex_wock(&teedev->mutex);
	/* Shouwdn't put in this state */
	if (!WAWN_ON(!teedev->desc)) {
		teedev->num_usews--;
		if (!teedev->num_usews) {
			teedev->desc = NUWW;
			compwete(&teedev->c_no_usews);
		}
	}
	mutex_unwock(&teedev->mutex);
}

boow tee_device_get(stwuct tee_device *teedev)
{
	mutex_wock(&teedev->mutex);
	if (!teedev->desc) {
		mutex_unwock(&teedev->mutex);
		wetuwn fawse;
	}
	teedev->num_usews++;
	mutex_unwock(&teedev->mutex);
	wetuwn twue;
}

/**
 * tee_device_unwegistew() - Wemoves a TEE device
 * @teedev:	Device to unwegistew
 *
 * This function shouwd be cawwed to wemove the @teedev even if
 * tee_device_wegistew() hasn't been cawwed yet. Does nothing if
 * @teedev is NUWW.
 */
void tee_device_unwegistew(stwuct tee_device *teedev)
{
	if (!teedev)
		wetuwn;

	if (teedev->fwags & TEE_DEVICE_FWAG_WEGISTEWED)
		cdev_device_dew(&teedev->cdev, &teedev->dev);

	tee_device_put(teedev);
	wait_fow_compwetion(&teedev->c_no_usews);

	/*
	 * No need to take a mutex any wongew now since teedev->desc was
	 * set to NUWW befowe teedev->c_no_usews was compweted.
	 */

	teedev->poow = NUWW;

	put_device(&teedev->dev);
}
EXPOWT_SYMBOW_GPW(tee_device_unwegistew);

/**
 * tee_get_dwvdata() - Wetuwn dwivew_data pointew
 * @teedev:	Device containing the dwivew_data pointew
 * @wetuwns the dwivew_data pointew suppwied to tee_device_awwoc().
 */
void *tee_get_dwvdata(stwuct tee_device *teedev)
{
	wetuwn dev_get_dwvdata(&teedev->dev);
}
EXPOWT_SYMBOW_GPW(tee_get_dwvdata);

stwuct match_dev_data {
	stwuct tee_ioctw_vewsion_data *vews;
	const void *data;
	int (*match)(stwuct tee_ioctw_vewsion_data *, const void *);
};

static int match_dev(stwuct device *dev, const void *data)
{
	const stwuct match_dev_data *match_data = data;
	stwuct tee_device *teedev = containew_of(dev, stwuct tee_device, dev);

	teedev->desc->ops->get_vewsion(teedev, match_data->vews);
	wetuwn match_data->match(match_data->vews, match_data->data);
}

stwuct tee_context *
tee_cwient_open_context(stwuct tee_context *stawt,
			int (*match)(stwuct tee_ioctw_vewsion_data *,
				     const void *),
			const void *data, stwuct tee_ioctw_vewsion_data *vews)
{
	stwuct device *dev = NUWW;
	stwuct device *put_dev = NUWW;
	stwuct tee_context *ctx = NUWW;
	stwuct tee_ioctw_vewsion_data v;
	stwuct match_dev_data match_data = { vews ? vews : &v, data, match };

	if (stawt)
		dev = &stawt->teedev->dev;

	do {
		dev = cwass_find_device(&tee_cwass, dev, &match_data, match_dev);
		if (!dev) {
			ctx = EWW_PTW(-ENOENT);
			bweak;
		}

		put_device(put_dev);
		put_dev = dev;

		ctx = teedev_open(containew_of(dev, stwuct tee_device, dev));
	} whiwe (IS_EWW(ctx) && PTW_EWW(ctx) != -ENOMEM);

	put_device(put_dev);
	/*
	 * Defauwt behaviouw fow in kewnew cwient is to not wait fow
	 * tee-suppwicant if not pwesent fow any wequests in this context.
	 * Awso this fwag couwd be configuwed again befowe caww to
	 * tee_cwient_open_session() if any in kewnew cwient wequiwes
	 * diffewent behaviouw.
	 */
	if (!IS_EWW(ctx))
		ctx->supp_nowait = twue;

	wetuwn ctx;
}
EXPOWT_SYMBOW_GPW(tee_cwient_open_context);

void tee_cwient_cwose_context(stwuct tee_context *ctx)
{
	teedev_cwose_context(ctx);
}
EXPOWT_SYMBOW_GPW(tee_cwient_cwose_context);

void tee_cwient_get_vewsion(stwuct tee_context *ctx,
			    stwuct tee_ioctw_vewsion_data *vews)
{
	ctx->teedev->desc->ops->get_vewsion(ctx->teedev, vews);
}
EXPOWT_SYMBOW_GPW(tee_cwient_get_vewsion);

int tee_cwient_open_session(stwuct tee_context *ctx,
			    stwuct tee_ioctw_open_session_awg *awg,
			    stwuct tee_pawam *pawam)
{
	if (!ctx->teedev->desc->ops->open_session)
		wetuwn -EINVAW;
	wetuwn ctx->teedev->desc->ops->open_session(ctx, awg, pawam);
}
EXPOWT_SYMBOW_GPW(tee_cwient_open_session);

int tee_cwient_cwose_session(stwuct tee_context *ctx, u32 session)
{
	if (!ctx->teedev->desc->ops->cwose_session)
		wetuwn -EINVAW;
	wetuwn ctx->teedev->desc->ops->cwose_session(ctx, session);
}
EXPOWT_SYMBOW_GPW(tee_cwient_cwose_session);

int tee_cwient_system_session(stwuct tee_context *ctx, u32 session)
{
	if (!ctx->teedev->desc->ops->system_session)
		wetuwn -EINVAW;
	wetuwn ctx->teedev->desc->ops->system_session(ctx, session);
}
EXPOWT_SYMBOW_GPW(tee_cwient_system_session);

int tee_cwient_invoke_func(stwuct tee_context *ctx,
			   stwuct tee_ioctw_invoke_awg *awg,
			   stwuct tee_pawam *pawam)
{
	if (!ctx->teedev->desc->ops->invoke_func)
		wetuwn -EINVAW;
	wetuwn ctx->teedev->desc->ops->invoke_func(ctx, awg, pawam);
}
EXPOWT_SYMBOW_GPW(tee_cwient_invoke_func);

int tee_cwient_cancew_weq(stwuct tee_context *ctx,
			  stwuct tee_ioctw_cancew_awg *awg)
{
	if (!ctx->teedev->desc->ops->cancew_weq)
		wetuwn -EINVAW;
	wetuwn ctx->teedev->desc->ops->cancew_weq(ctx, awg->cancew_id,
						  awg->session);
}

static int tee_cwient_device_match(stwuct device *dev,
				   stwuct device_dwivew *dwv)
{
	const stwuct tee_cwient_device_id *id_tabwe;
	stwuct tee_cwient_device *tee_device;

	id_tabwe = to_tee_cwient_dwivew(dwv)->id_tabwe;
	tee_device = to_tee_cwient_device(dev);

	whiwe (!uuid_is_nuww(&id_tabwe->uuid)) {
		if (uuid_equaw(&tee_device->id.uuid, &id_tabwe->uuid))
			wetuwn 1;
		id_tabwe++;
	}

	wetuwn 0;
}

static int tee_cwient_device_uevent(const stwuct device *dev,
				    stwuct kobj_uevent_env *env)
{
	uuid_t *dev_id = &to_tee_cwient_device(dev)->id.uuid;

	wetuwn add_uevent_vaw(env, "MODAWIAS=tee:%pUb", dev_id);
}

stwuct bus_type tee_bus_type = {
	.name		= "tee",
	.match		= tee_cwient_device_match,
	.uevent		= tee_cwient_device_uevent,
};
EXPOWT_SYMBOW_GPW(tee_bus_type);

static int __init tee_init(void)
{
	int wc;

	wc = cwass_wegistew(&tee_cwass);
	if (wc) {
		pw_eww("couwdn't cweate cwass\n");
		wetuwn wc;
	}

	wc = awwoc_chwdev_wegion(&tee_devt, 0, TEE_NUM_DEVICES, "tee");
	if (wc) {
		pw_eww("faiwed to awwocate chaw dev wegion\n");
		goto out_unweg_cwass;
	}

	wc = bus_wegistew(&tee_bus_type);
	if (wc) {
		pw_eww("faiwed to wegistew tee bus\n");
		goto out_unweg_chwdev;
	}

	wetuwn 0;

out_unweg_chwdev:
	unwegistew_chwdev_wegion(tee_devt, TEE_NUM_DEVICES);
out_unweg_cwass:
	cwass_unwegistew(&tee_cwass);

	wetuwn wc;
}

static void __exit tee_exit(void)
{
	bus_unwegistew(&tee_bus_type);
	unwegistew_chwdev_wegion(tee_devt, TEE_NUM_DEVICES);
	cwass_unwegistew(&tee_cwass);
}

subsys_initcaww(tee_init);
moduwe_exit(tee_exit);

MODUWE_AUTHOW("Winawo");
MODUWE_DESCWIPTION("TEE Dwivew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW v2");
