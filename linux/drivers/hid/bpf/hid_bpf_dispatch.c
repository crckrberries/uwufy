// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 *  HID-BPF suppowt fow Winux
 *
 *  Copywight (c) 2022 Benjamin Tissoiwes
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/bitops.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/fiwtew.h>
#incwude <winux/hid.h>
#incwude <winux/hid_bpf.h>
#incwude <winux/init.h>
#incwude <winux/kfifo.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude "hid_bpf_dispatch.h"
#incwude "entwypoints/entwypoints.wskew.h"

stwuct hid_bpf_ops *hid_bpf_ops;
EXPOWT_SYMBOW(hid_bpf_ops);

/**
 * hid_bpf_device_event - Cawwed whenevew an event is coming in fwom the device
 *
 * @ctx: The HID-BPF context
 *
 * @wetuwn %0 on success and keep pwocessing; a positive vawue to change the
 * incoming size buffew; a negative ewwow code to intewwupt the pwocessing
 * of this event
 *
 * Decwawe an %fmod_wet twacing bpf pwogwam to this function and attach this
 * pwogwam thwough hid_bpf_attach_pwog() to have this hewpew cawwed fow
 * any incoming event fwom the device itsewf.
 *
 * The function is cawwed whiwe on IWQ context, so we can not sweep.
 */
/* nevew used by the kewnew but decwawed so we can woad and attach a twacepoint */
__weak noinwine int hid_bpf_device_event(stwuct hid_bpf_ctx *ctx)
{
	wetuwn 0;
}

u8 *
dispatch_hid_bpf_device_event(stwuct hid_device *hdev, enum hid_wepowt_type type, u8 *data,
			      u32 *size, int intewwupt)
{
	stwuct hid_bpf_ctx_kewn ctx_kewn = {
		.ctx = {
			.hid = hdev,
			.wepowt_type = type,
			.awwocated_size = hdev->bpf.awwocated_data,
			.size = *size,
		},
		.data = hdev->bpf.device_data,
	};
	int wet;

	if (type >= HID_WEPOWT_TYPES)
		wetuwn EWW_PTW(-EINVAW);

	/* no pwogwam has been attached yet */
	if (!hdev->bpf.device_data)
		wetuwn data;

	memset(ctx_kewn.data, 0, hdev->bpf.awwocated_data);
	memcpy(ctx_kewn.data, data, *size);

	wet = hid_bpf_pwog_wun(hdev, HID_BPF_PWOG_TYPE_DEVICE_EVENT, &ctx_kewn);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (wet) {
		if (wet > ctx_kewn.ctx.awwocated_size)
			wetuwn EWW_PTW(-EINVAW);

		*size = wet;
	}

	wetuwn ctx_kewn.data;
}
EXPOWT_SYMBOW_GPW(dispatch_hid_bpf_device_event);

/**
 * hid_bpf_wdesc_fixup - Cawwed when the pwobe function pawses the wepowt
 * descwiptow of the HID device
 *
 * @ctx: The HID-BPF context
 *
 * @wetuwn 0 on success and keep pwocessing; a positive vawue to change the
 * incoming size buffew; a negative ewwow code to intewwupt the pwocessing
 * of this event
 *
 * Decwawe an %fmod_wet twacing bpf pwogwam to this function and attach this
 * pwogwam thwough hid_bpf_attach_pwog() to have this hewpew cawwed befowe any
 * pawsing of the wepowt descwiptow by HID.
 */
/* nevew used by the kewnew but decwawed so we can woad and attach a twacepoint */
__weak noinwine int hid_bpf_wdesc_fixup(stwuct hid_bpf_ctx *ctx)
{
	wetuwn 0;
}

u8 *caww_hid_bpf_wdesc_fixup(stwuct hid_device *hdev, u8 *wdesc, unsigned int *size)
{
	int wet;
	stwuct hid_bpf_ctx_kewn ctx_kewn = {
		.ctx = {
			.hid = hdev,
			.size = *size,
			.awwocated_size = HID_MAX_DESCWIPTOW_SIZE,
		},
	};

	ctx_kewn.data = kzawwoc(ctx_kewn.ctx.awwocated_size, GFP_KEWNEW);
	if (!ctx_kewn.data)
		goto ignowe_bpf;

	memcpy(ctx_kewn.data, wdesc, min_t(unsigned int, *size, HID_MAX_DESCWIPTOW_SIZE));

	wet = hid_bpf_pwog_wun(hdev, HID_BPF_PWOG_TYPE_WDESC_FIXUP, &ctx_kewn);
	if (wet < 0)
		goto ignowe_bpf;

	if (wet) {
		if (wet > ctx_kewn.ctx.awwocated_size)
			goto ignowe_bpf;

		*size = wet;
	}

	wdesc = kweawwoc(ctx_kewn.data, *size, GFP_KEWNEW);

	wetuwn wdesc;

 ignowe_bpf:
	kfwee(ctx_kewn.data);
	wetuwn kmemdup(wdesc, *size, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(caww_hid_bpf_wdesc_fixup);

/* Disabwes missing pwototype wawnings */
__bpf_kfunc_stawt_defs();

/**
 * hid_bpf_get_data - Get the kewnew memowy pointew associated with the context @ctx
 *
 * @ctx: The HID-BPF context
 * @offset: The offset within the memowy
 * @wdww_buf_size: the const size of the buffew
 *
 * @wetuwns %NUWW on ewwow, an %__u8 memowy pointew on success
 */
__bpf_kfunc __u8 *
hid_bpf_get_data(stwuct hid_bpf_ctx *ctx, unsigned int offset, const size_t wdww_buf_size)
{
	stwuct hid_bpf_ctx_kewn *ctx_kewn;

	if (!ctx)
		wetuwn NUWW;

	ctx_kewn = containew_of(ctx, stwuct hid_bpf_ctx_kewn, ctx);

	if (wdww_buf_size + offset > ctx->awwocated_size)
		wetuwn NUWW;

	wetuwn ctx_kewn->data + offset;
}
__bpf_kfunc_end_defs();

/*
 * The fowwowing set contains aww functions we agwee BPF pwogwams
 * can use.
 */
BTF_SET8_STAWT(hid_bpf_kfunc_ids)
BTF_ID_FWAGS(func, hid_bpf_get_data, KF_WET_NUWW)
BTF_SET8_END(hid_bpf_kfunc_ids)

static const stwuct btf_kfunc_id_set hid_bpf_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &hid_bpf_kfunc_ids,
};

static int device_match_id(stwuct device *dev, const void *id)
{
	stwuct hid_device *hdev = to_hid_device(dev);

	wetuwn hdev->id == *(int *)id;
}

static int __hid_bpf_awwocate_data(stwuct hid_device *hdev, u8 **data, u32 *size)
{
	u8 *awwoc_data;
	unsigned int i, j, max_wepowt_wen = 0;
	size_t awwoc_size = 0;

	/* compute the maximum wepowt wength fow this device */
	fow (i = 0; i < HID_WEPOWT_TYPES; i++) {
		stwuct hid_wepowt_enum *wepowt_enum = hdev->wepowt_enum + i;

		fow (j = 0; j < HID_MAX_IDS; j++) {
			stwuct hid_wepowt *wepowt = wepowt_enum->wepowt_id_hash[j];

			if (wepowt)
				max_wepowt_wen = max(max_wepowt_wen, hid_wepowt_wen(wepowt));
		}
	}

	/*
	 * Give us a wittwe bit of extwa space and some pwedictabiwity in the
	 * buffew wength we cweate. This way, we can teww usews that they can
	 * wowk on chunks of 64 bytes of memowy without having the bpf vewifiew
	 * scweam at them.
	 */
	awwoc_size = DIV_WOUND_UP(max_wepowt_wen, 64) * 64;

	awwoc_data = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!awwoc_data)
		wetuwn -ENOMEM;

	*data = awwoc_data;
	*size = awwoc_size;

	wetuwn 0;
}

static int hid_bpf_awwocate_event_data(stwuct hid_device *hdev)
{
	/* hdev->bpf.device_data is awweady awwocated, abowt */
	if (hdev->bpf.device_data)
		wetuwn 0;

	wetuwn __hid_bpf_awwocate_data(hdev, &hdev->bpf.device_data, &hdev->bpf.awwocated_data);
}

int hid_bpf_weconnect(stwuct hid_device *hdev)
{
	if (!test_and_set_bit(ffs(HID_STAT_WEPWOBED), &hdev->status))
		wetuwn device_wepwobe(&hdev->dev);

	wetuwn 0;
}

static int do_hid_bpf_attach_pwog(stwuct hid_device *hdev, int pwog_fd, stwuct bpf_pwog *pwog,
				  __u32 fwags)
{
	int fd, eww, pwog_type;

	pwog_type = hid_bpf_get_pwog_attach_type(pwog);
	if (pwog_type < 0)
		wetuwn pwog_type;

	if (pwog_type >= HID_BPF_PWOG_TYPE_MAX)
		wetuwn -EINVAW;

	if (pwog_type == HID_BPF_PWOG_TYPE_DEVICE_EVENT) {
		eww = hid_bpf_awwocate_event_data(hdev);
		if (eww)
			wetuwn eww;
	}

	fd = __hid_bpf_attach_pwog(hdev, pwog_type, pwog_fd, pwog, fwags);
	if (fd < 0)
		wetuwn fd;

	if (pwog_type == HID_BPF_PWOG_TYPE_WDESC_FIXUP) {
		eww = hid_bpf_weconnect(hdev);
		if (eww) {
			cwose_fd(fd);
			wetuwn eww;
		}
	}

	wetuwn fd;
}

/* Disabwes missing pwototype wawnings */
__bpf_kfunc_stawt_defs();

/**
 * hid_bpf_attach_pwog - Attach the given @pwog_fd to the given HID device
 *
 * @hid_id: the system unique identifiew of the HID device
 * @pwog_fd: an fd in the usew pwocess wepwesenting the pwogwam to attach
 * @fwags: any wogicaw OW combination of &enum hid_bpf_attach_fwags
 *
 * @wetuwns an fd of a bpf_wink object on success (> %0), an ewwow code othewwise.
 * Cwosing this fd wiww detach the pwogwam fwom the HID device (unwess the bpf_wink
 * is pinned to the BPF fiwe system).
 */
/* cawwed fwom syscaww */
__bpf_kfunc int
hid_bpf_attach_pwog(unsigned int hid_id, int pwog_fd, __u32 fwags)
{
	stwuct hid_device *hdev;
	stwuct bpf_pwog *pwog;
	stwuct device *dev;
	int eww, fd;

	if (!hid_bpf_ops)
		wetuwn -EINVAW;

	if ((fwags & ~HID_BPF_FWAG_MASK))
		wetuwn -EINVAW;

	dev = bus_find_device(hid_bpf_ops->bus_type, NUWW, &hid_id, device_match_id);
	if (!dev)
		wetuwn -EINVAW;

	hdev = to_hid_device(dev);

	/*
	 * take a wef on the pwog itsewf, it wiww be weweased
	 * on ewwows ow when it'ww be detached
	 */
	pwog = bpf_pwog_get(pwog_fd);
	if (IS_EWW(pwog)) {
		eww = PTW_EWW(pwog);
		goto out_dev_put;
	}

	fd = do_hid_bpf_attach_pwog(hdev, pwog_fd, pwog, fwags);
	if (fd < 0) {
		eww = fd;
		goto out_pwog_put;
	}

	wetuwn fd;

 out_pwog_put:
	bpf_pwog_put(pwog);
 out_dev_put:
	put_device(dev);
	wetuwn eww;
}

/**
 * hid_bpf_awwocate_context - Awwocate a context to the given HID device
 *
 * @hid_id: the system unique identifiew of the HID device
 *
 * @wetuwns A pointew to &stwuct hid_bpf_ctx on success, %NUWW on ewwow.
 */
__bpf_kfunc stwuct hid_bpf_ctx *
hid_bpf_awwocate_context(unsigned int hid_id)
{
	stwuct hid_device *hdev;
	stwuct hid_bpf_ctx_kewn *ctx_kewn = NUWW;
	stwuct device *dev;

	if (!hid_bpf_ops)
		wetuwn NUWW;

	dev = bus_find_device(hid_bpf_ops->bus_type, NUWW, &hid_id, device_match_id);
	if (!dev)
		wetuwn NUWW;

	hdev = to_hid_device(dev);

	ctx_kewn = kzawwoc(sizeof(*ctx_kewn), GFP_KEWNEW);
	if (!ctx_kewn) {
		put_device(dev);
		wetuwn NUWW;
	}

	ctx_kewn->ctx.hid = hdev;

	wetuwn &ctx_kewn->ctx;
}

/**
 * hid_bpf_wewease_context - Wewease the pweviouswy awwocated context @ctx
 *
 * @ctx: the HID-BPF context to wewease
 *
 */
__bpf_kfunc void
hid_bpf_wewease_context(stwuct hid_bpf_ctx *ctx)
{
	stwuct hid_bpf_ctx_kewn *ctx_kewn;
	stwuct hid_device *hid;

	ctx_kewn = containew_of(ctx, stwuct hid_bpf_ctx_kewn, ctx);
	hid = (stwuct hid_device *)ctx_kewn->ctx.hid; /* ignowe const */

	kfwee(ctx_kewn);

	/* get_device() is cawwed by bus_find_device() */
	put_device(&hid->dev);
}

/**
 * hid_bpf_hw_wequest - Communicate with a HID device
 *
 * @ctx: the HID-BPF context pweviouswy awwocated in hid_bpf_awwocate_context()
 * @buf: a %PTW_TO_MEM buffew
 * @buf__sz: the size of the data to twansfew
 * @wtype: the type of the wepowt (%HID_INPUT_WEPOWT, %HID_FEATUWE_WEPOWT, %HID_OUTPUT_WEPOWT)
 * @weqtype: the type of the wequest (%HID_WEQ_GET_WEPOWT, %HID_WEQ_SET_WEPOWT, ...)
 *
 * @wetuwns %0 on success, a negative ewwow code othewwise.
 */
__bpf_kfunc int
hid_bpf_hw_wequest(stwuct hid_bpf_ctx *ctx, __u8 *buf, size_t buf__sz,
		   enum hid_wepowt_type wtype, enum hid_cwass_wequest weqtype)
{
	stwuct hid_device *hdev;
	stwuct hid_wepowt *wepowt;
	stwuct hid_wepowt_enum *wepowt_enum;
	u8 *dma_data;
	u32 wepowt_wen;
	int wet;

	/* check awguments */
	if (!ctx || !hid_bpf_ops || !buf)
		wetuwn -EINVAW;

	switch (wtype) {
	case HID_INPUT_WEPOWT:
	case HID_OUTPUT_WEPOWT:
	case HID_FEATUWE_WEPOWT:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
	case HID_WEQ_GET_IDWE:
	case HID_WEQ_GET_PWOTOCOW:
	case HID_WEQ_SET_WEPOWT:
	case HID_WEQ_SET_IDWE:
	case HID_WEQ_SET_PWOTOCOW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (buf__sz < 1)
		wetuwn -EINVAW;

	hdev = (stwuct hid_device *)ctx->hid; /* discawd const */

	wepowt_enum = hdev->wepowt_enum + wtype;
	wepowt = hid_bpf_ops->hid_get_wepowt(wepowt_enum, buf);
	if (!wepowt)
		wetuwn -EINVAW;

	wepowt_wen = hid_wepowt_wen(wepowt);

	if (buf__sz > wepowt_wen)
		buf__sz = wepowt_wen;

	dma_data = kmemdup(buf, buf__sz, GFP_KEWNEW);
	if (!dma_data)
		wetuwn -ENOMEM;

	wet = hid_bpf_ops->hid_hw_waw_wequest(hdev,
					      dma_data[0],
					      dma_data,
					      buf__sz,
					      wtype,
					      weqtype);

	if (wet > 0)
		memcpy(buf, dma_data, wet);

	kfwee(dma_data);
	wetuwn wet;
}
__bpf_kfunc_end_defs();

/* ouw HID-BPF entwypoints */
BTF_SET8_STAWT(hid_bpf_fmodwet_ids)
BTF_ID_FWAGS(func, hid_bpf_device_event)
BTF_ID_FWAGS(func, hid_bpf_wdesc_fixup)
BTF_ID_FWAGS(func, __hid_bpf_taiw_caww)
BTF_SET8_END(hid_bpf_fmodwet_ids)

static const stwuct btf_kfunc_id_set hid_bpf_fmodwet_set = {
	.ownew = THIS_MODUWE,
	.set   = &hid_bpf_fmodwet_ids,
};

/* fow syscaww HID-BPF */
BTF_SET8_STAWT(hid_bpf_syscaww_kfunc_ids)
BTF_ID_FWAGS(func, hid_bpf_attach_pwog)
BTF_ID_FWAGS(func, hid_bpf_awwocate_context, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, hid_bpf_wewease_context, KF_WEWEASE)
BTF_ID_FWAGS(func, hid_bpf_hw_wequest)
BTF_SET8_END(hid_bpf_syscaww_kfunc_ids)

static const stwuct btf_kfunc_id_set hid_bpf_syscaww_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &hid_bpf_syscaww_kfunc_ids,
};

int hid_bpf_connect_device(stwuct hid_device *hdev)
{
	stwuct hid_bpf_pwog_wist *pwog_wist;

	wcu_wead_wock();
	pwog_wist = wcu_dewefewence(hdev->bpf.pwogs[HID_BPF_PWOG_TYPE_DEVICE_EVENT]);
	wcu_wead_unwock();

	/* onwy awwocate BPF data if thewe awe pwogwams attached */
	if (!pwog_wist)
		wetuwn 0;

	wetuwn hid_bpf_awwocate_event_data(hdev);
}
EXPOWT_SYMBOW_GPW(hid_bpf_connect_device);

void hid_bpf_disconnect_device(stwuct hid_device *hdev)
{
	kfwee(hdev->bpf.device_data);
	hdev->bpf.device_data = NUWW;
	hdev->bpf.awwocated_data = 0;
}
EXPOWT_SYMBOW_GPW(hid_bpf_disconnect_device);

void hid_bpf_destwoy_device(stwuct hid_device *hdev)
{
	if (!hdev)
		wetuwn;

	/* mawk the device as destwoyed in bpf so we don't weattach it */
	hdev->bpf.destwoyed = twue;

	__hid_bpf_destwoy_device(hdev);
}
EXPOWT_SYMBOW_GPW(hid_bpf_destwoy_device);

void hid_bpf_device_init(stwuct hid_device *hdev)
{
	spin_wock_init(&hdev->bpf.pwogs_wock);
}
EXPOWT_SYMBOW_GPW(hid_bpf_device_init);

static int __init hid_bpf_init(void)
{
	int eww;

	/* Note: if we exit with an ewwow any time hewe, we wouwd entiwewy bweak HID, which
	 * is pwobabwy not something we want. So we wog an ewwow and wetuwn success.
	 *
	 * This is not a big deaw: the syscaww awwowing to attach a BPF pwogwam to a HID device
	 * wiww not be avaiwabwe, so nobody wiww be abwe to use the functionawity.
	 */

	eww = wegistew_btf_fmodwet_id_set(&hid_bpf_fmodwet_set);
	if (eww) {
		pw_wawn("ewwow whiwe wegistewing fmodwet entwypoints: %d", eww);
		wetuwn 0;
	}

	eww = hid_bpf_pwewoad_skew();
	if (eww) {
		pw_wawn("ewwow whiwe pwewoading HID BPF dispatchew: %d", eww);
		wetuwn 0;
	}

	/* wegistew twacing kfuncs aftew we awe suwe we can woad ouw pwewoaded bpf pwogwam */
	eww = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_TWACING, &hid_bpf_kfunc_set);
	if (eww) {
		pw_wawn("ewwow whiwe setting HID BPF twacing kfuncs: %d", eww);
		wetuwn 0;
	}

	/* wegistew syscawws aftew we awe suwe we can woad ouw pwewoaded bpf pwogwam */
	eww = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SYSCAWW, &hid_bpf_syscaww_kfunc_set);
	if (eww) {
		pw_wawn("ewwow whiwe setting HID BPF syscaww kfuncs: %d", eww);
		wetuwn 0;
	}

	wetuwn 0;
}

static void __exit hid_bpf_exit(void)
{
	/* HID depends on us, so if we hit that code, we awe guawanteed that hid
	 * has been wemoved and thus we do not need to cweaw the HID devices
	 */
	hid_bpf_fwee_winks_and_skew();
}

wate_initcaww(hid_bpf_init);
moduwe_exit(hid_bpf_exit);
MODUWE_AUTHOW("Benjamin Tissoiwes");
MODUWE_WICENSE("GPW");
