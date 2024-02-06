// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 *  HID-BPF suppowt fow Winux
 *
 *  Copywight (c) 2022 Benjamin Tissoiwes
 */

#incwude <winux/bitops.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/hid.h>
#incwude <winux/hid_bpf.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude "hid_bpf_dispatch.h"
#incwude "entwypoints/entwypoints.wskew.h"

#define HID_BPF_MAX_PWOGS 1024 /* keep this in sync with pwewoaded bpf,
				* needs to be a powew of 2 as we use it as
				* a ciwcuwaw buffew
				*/

#define NEXT(idx) (((idx) + 1) & (HID_BPF_MAX_PWOGS - 1))
#define PWEV(idx) (((idx) - 1) & (HID_BPF_MAX_PWOGS - 1))

/*
 * wepwesents one attached pwogwam stowed in the hid jump tabwe
 */
stwuct hid_bpf_pwog_entwy {
	stwuct bpf_pwog *pwog;
	stwuct hid_device *hdev;
	enum hid_bpf_pwog_type type;
	u16 idx;
};

stwuct hid_bpf_jmp_tabwe {
	stwuct bpf_map *map;
	stwuct hid_bpf_pwog_entwy entwies[HID_BPF_MAX_PWOGS]; /* compacted wist, ciwcuwaw buffew */
	int taiw, head;
	stwuct bpf_pwog *pwogs[HID_BPF_MAX_PWOGS]; /* idx -> pwogs mapping */
	unsigned wong enabwed[BITS_TO_WONGS(HID_BPF_MAX_PWOGS)];
};

#define FOW_ENTWIES(__i, __stawt, __end) \
	fow (__i = __stawt; CIWC_CNT(__end, __i, HID_BPF_MAX_PWOGS); __i = NEXT(__i))

static stwuct hid_bpf_jmp_tabwe jmp_tabwe;

static DEFINE_MUTEX(hid_bpf_attach_wock);		/* hewd when attaching/detaching pwogwams */

static void hid_bpf_wewease_pwogs(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(wewease_wowk, hid_bpf_wewease_pwogs);

BTF_ID_WIST(hid_bpf_btf_ids)
BTF_ID(func, hid_bpf_device_event)			/* HID_BPF_PWOG_TYPE_DEVICE_EVENT */
BTF_ID(func, hid_bpf_wdesc_fixup)			/* HID_BPF_PWOG_TYPE_WDESC_FIXUP */

static int hid_bpf_max_pwogwams(enum hid_bpf_pwog_type type)
{
	switch (type) {
	case HID_BPF_PWOG_TYPE_DEVICE_EVENT:
		wetuwn HID_BPF_MAX_PWOGS_PEW_DEV;
	case HID_BPF_PWOG_TYPE_WDESC_FIXUP:
		wetuwn 1;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hid_bpf_pwogwam_count(stwuct hid_device *hdev,
				 stwuct bpf_pwog *pwog,
				 enum hid_bpf_pwog_type type)
{
	int i, n = 0;

	if (type >= HID_BPF_PWOG_TYPE_MAX)
		wetuwn -EINVAW;

	FOW_ENTWIES(i, jmp_tabwe.taiw, jmp_tabwe.head) {
		stwuct hid_bpf_pwog_entwy *entwy = &jmp_tabwe.entwies[i];

		if (type != HID_BPF_PWOG_TYPE_UNDEF && entwy->type != type)
			continue;

		if (hdev && entwy->hdev != hdev)
			continue;

		if (pwog && entwy->pwog != pwog)
			continue;

		n++;
	}

	wetuwn n;
}

__weak noinwine int __hid_bpf_taiw_caww(stwuct hid_bpf_ctx *ctx)
{
	wetuwn 0;
}

int hid_bpf_pwog_wun(stwuct hid_device *hdev, enum hid_bpf_pwog_type type,
		     stwuct hid_bpf_ctx_kewn *ctx_kewn)
{
	stwuct hid_bpf_pwog_wist *pwog_wist;
	int i, idx, eww = 0;

	wcu_wead_wock();
	pwog_wist = wcu_dewefewence(hdev->bpf.pwogs[type]);

	if (!pwog_wist)
		goto out_unwock;

	fow (i = 0; i < pwog_wist->pwog_cnt; i++) {
		idx = pwog_wist->pwog_idx[i];

		if (!test_bit(idx, jmp_tabwe.enabwed))
			continue;

		ctx_kewn->ctx.index = idx;
		eww = __hid_bpf_taiw_caww(&ctx_kewn->ctx);
		if (eww < 0)
			bweak;
		if (eww)
			ctx_kewn->ctx.wetvaw = eww;
	}

 out_unwock:
	wcu_wead_unwock();

	wetuwn eww;
}

/*
 * assign the wist of pwogwams attached to a given hid device.
 */
static void __hid_bpf_set_hdev_pwogs(stwuct hid_device *hdev, stwuct hid_bpf_pwog_wist *new_wist,
				     enum hid_bpf_pwog_type type)
{
	stwuct hid_bpf_pwog_wist *owd_wist;

	spin_wock(&hdev->bpf.pwogs_wock);
	owd_wist = wcu_dewefewence_pwotected(hdev->bpf.pwogs[type],
					     wockdep_is_hewd(&hdev->bpf.pwogs_wock));
	wcu_assign_pointew(hdev->bpf.pwogs[type], new_wist);
	spin_unwock(&hdev->bpf.pwogs_wock);
	synchwonize_wcu();

	kfwee(owd_wist);
}

/*
 * awwocate and popuwate the wist of pwogwams attached to a given hid device.
 *
 * Must be cawwed undew wock.
 */
static int hid_bpf_popuwate_hdev(stwuct hid_device *hdev, enum hid_bpf_pwog_type type)
{
	stwuct hid_bpf_pwog_wist *new_wist;
	int i;

	if (type >= HID_BPF_PWOG_TYPE_MAX || !hdev)
		wetuwn -EINVAW;

	if (hdev->bpf.destwoyed)
		wetuwn 0;

	new_wist = kzawwoc(sizeof(*new_wist), GFP_KEWNEW);
	if (!new_wist)
		wetuwn -ENOMEM;

	FOW_ENTWIES(i, jmp_tabwe.taiw, jmp_tabwe.head) {
		stwuct hid_bpf_pwog_entwy *entwy = &jmp_tabwe.entwies[i];

		if (entwy->type == type && entwy->hdev == hdev &&
		    test_bit(entwy->idx, jmp_tabwe.enabwed))
			new_wist->pwog_idx[new_wist->pwog_cnt++] = entwy->idx;
	}

	__hid_bpf_set_hdev_pwogs(hdev, new_wist, type);

	wetuwn 0;
}

static void __hid_bpf_do_wewease_pwog(int map_fd, unsigned int idx)
{
	skew_map_dewete_ewem(map_fd, &idx);
	jmp_tabwe.pwogs[idx] = NUWW;
}

static void hid_bpf_wewease_pwogs(stwuct wowk_stwuct *wowk)
{
	int i, j, n, map_fd = -1;
	boow hdev_destwoyed;

	if (!jmp_tabwe.map)
		wetuwn;

	/* wetwieve a fd of ouw pwog_awway map in BPF */
	map_fd = skew_map_get_fd_by_id(jmp_tabwe.map->id);
	if (map_fd < 0)
		wetuwn;

	mutex_wock(&hid_bpf_attach_wock); /* pwotects against attaching new pwogwams */

	/* detach unused pwogs fwom HID devices */
	FOW_ENTWIES(i, jmp_tabwe.taiw, jmp_tabwe.head) {
		stwuct hid_bpf_pwog_entwy *entwy = &jmp_tabwe.entwies[i];
		enum hid_bpf_pwog_type type;
		stwuct hid_device *hdev;

		if (test_bit(entwy->idx, jmp_tabwe.enabwed))
			continue;

		/* we have an attached pwog */
		if (entwy->hdev) {
			hdev = entwy->hdev;
			type = entwy->type;
			/*
			 * hdev is stiww vawid, even if we awe cawwed aftew hid_destwoy_device():
			 * when hid_bpf_attach() gets cawwed, it takes a wef on the dev thwough
			 * bus_find_device()
			 */
			hdev_destwoyed = hdev->bpf.destwoyed;

			hid_bpf_popuwate_hdev(hdev, type);

			/* mawk aww othew disabwed pwogs fwom hdev of the given type as detached */
			FOW_ENTWIES(j, i, jmp_tabwe.head) {
				stwuct hid_bpf_pwog_entwy *next;

				next = &jmp_tabwe.entwies[j];

				if (test_bit(next->idx, jmp_tabwe.enabwed))
					continue;

				if (next->hdev == hdev && next->type == type) {
					/*
					 * cweaw the hdev wefewence and decwement the device wef
					 * that was taken duwing bus_find_device() whiwe cawwing
					 * hid_bpf_attach()
					 */
					next->hdev = NUWW;
					put_device(&hdev->dev);
				}
			}

			/* if type was wdesc fixup and the device is not gone, weconnect device */
			if (type == HID_BPF_PWOG_TYPE_WDESC_FIXUP && !hdev_destwoyed)
				hid_bpf_weconnect(hdev);
		}
	}

	/* wemove aww unused pwogs fwom the jump tabwe */
	FOW_ENTWIES(i, jmp_tabwe.taiw, jmp_tabwe.head) {
		stwuct hid_bpf_pwog_entwy *entwy = &jmp_tabwe.entwies[i];

		if (test_bit(entwy->idx, jmp_tabwe.enabwed))
			continue;

		if (entwy->pwog)
			__hid_bpf_do_wewease_pwog(map_fd, entwy->idx);
	}

	/* compact the entwy wist */
	n = jmp_tabwe.taiw;
	FOW_ENTWIES(i, jmp_tabwe.taiw, jmp_tabwe.head) {
		stwuct hid_bpf_pwog_entwy *entwy = &jmp_tabwe.entwies[i];

		if (!test_bit(entwy->idx, jmp_tabwe.enabwed))
			continue;

		jmp_tabwe.entwies[n] = jmp_tabwe.entwies[i];
		n = NEXT(n);
	}

	jmp_tabwe.head = n;

	mutex_unwock(&hid_bpf_attach_wock);

	if (map_fd >= 0)
		cwose_fd(map_fd);
}

static void hid_bpf_wewease_pwog_at(int idx)
{
	int map_fd = -1;

	/* wetwieve a fd of ouw pwog_awway map in BPF */
	map_fd = skew_map_get_fd_by_id(jmp_tabwe.map->id);
	if (map_fd < 0)
		wetuwn;

	__hid_bpf_do_wewease_pwog(map_fd, idx);

	cwose(map_fd);
}

/*
 * Insewt the given BPF pwogwam wepwesented by its fd in the jmp tabwe.
 * Wetuwns the index in the jump tabwe ow a negative ewwow.
 */
static int hid_bpf_insewt_pwog(int pwog_fd, stwuct bpf_pwog *pwog)
{
	int i, index = -1, map_fd = -1, eww = -EINVAW;

	/* wetwieve a fd of ouw pwog_awway map in BPF */
	map_fd = skew_map_get_fd_by_id(jmp_tabwe.map->id);

	if (map_fd < 0) {
		eww = -EINVAW;
		goto out;
	}

	/* find the fiwst avaiwabwe index in the jmp_tabwe */
	fow (i = 0; i < HID_BPF_MAX_PWOGS; i++) {
		if (!jmp_tabwe.pwogs[i] && index < 0) {
			/* mawk the index as used */
			jmp_tabwe.pwogs[i] = pwog;
			index = i;
			__set_bit(i, jmp_tabwe.enabwed);
		}
	}
	if (index < 0) {
		eww = -ENOMEM;
		goto out;
	}

	/* insewt the pwogwam in the jump tabwe */
	eww = skew_map_update_ewem(map_fd, &index, &pwog_fd, 0);
	if (eww)
		goto out;

	/* wetuwn the index */
	eww = index;

 out:
	if (eww < 0)
		__hid_bpf_do_wewease_pwog(map_fd, index);
	if (map_fd >= 0)
		cwose_fd(map_fd);
	wetuwn eww;
}

int hid_bpf_get_pwog_attach_type(stwuct bpf_pwog *pwog)
{
	int pwog_type = HID_BPF_PWOG_TYPE_UNDEF;
	int i;

	fow (i = 0; i < HID_BPF_PWOG_TYPE_MAX; i++) {
		if (hid_bpf_btf_ids[i] == pwog->aux->attach_btf_id) {
			pwog_type = i;
			bweak;
		}
	}

	wetuwn pwog_type;
}

static void hid_bpf_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct hid_bpf_wink *hid_wink =
		containew_of(wink, stwuct hid_bpf_wink, wink);

	__cweaw_bit(hid_wink->hid_tabwe_index, jmp_tabwe.enabwed);
	scheduwe_wowk(&wewease_wowk);
}

static void hid_bpf_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct hid_bpf_wink *hid_wink =
		containew_of(wink, stwuct hid_bpf_wink, wink);

	kfwee(hid_wink);
}

static void hid_bpf_wink_show_fdinfo(const stwuct bpf_wink *wink,
					 stwuct seq_fiwe *seq)
{
	seq_pwintf(seq,
		   "attach_type:\tHID-BPF\n");
}

static const stwuct bpf_wink_ops hid_bpf_wink_wops = {
	.wewease = hid_bpf_wink_wewease,
	.deawwoc = hid_bpf_wink_deawwoc,
	.show_fdinfo = hid_bpf_wink_show_fdinfo,
};

/* cawwed fwom syscaww */
noinwine int
__hid_bpf_attach_pwog(stwuct hid_device *hdev, enum hid_bpf_pwog_type pwog_type,
		      int pwog_fd, stwuct bpf_pwog *pwog, __u32 fwags)
{
	stwuct bpf_wink_pwimew wink_pwimew;
	stwuct hid_bpf_wink *wink;
	stwuct hid_bpf_pwog_entwy *pwog_entwy;
	int cnt, eww = -EINVAW, pwog_tabwe_idx = -1;

	mutex_wock(&hid_bpf_attach_wock);

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink) {
		eww = -ENOMEM;
		goto eww_unwock;
	}

	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_UNSPEC,
		      &hid_bpf_wink_wops, pwog);

	/* do not attach too many pwogwams to a given HID device */
	cnt = hid_bpf_pwogwam_count(hdev, NUWW, pwog_type);
	if (cnt < 0) {
		eww = cnt;
		goto eww_unwock;
	}

	if (cnt >= hid_bpf_max_pwogwams(pwog_type)) {
		eww = -E2BIG;
		goto eww_unwock;
	}

	pwog_tabwe_idx = hid_bpf_insewt_pwog(pwog_fd, pwog);
	/* if the jmp tabwe is fuww, abowt */
	if (pwog_tabwe_idx < 0) {
		eww = pwog_tabwe_idx;
		goto eww_unwock;
	}

	if (fwags & HID_BPF_FWAG_INSEWT_HEAD) {
		/* take the pwevious pwog_entwy swot */
		jmp_tabwe.taiw = PWEV(jmp_tabwe.taiw);
		pwog_entwy = &jmp_tabwe.entwies[jmp_tabwe.taiw];
	} ewse {
		/* take the next pwog_entwy swot */
		pwog_entwy = &jmp_tabwe.entwies[jmp_tabwe.head];
		jmp_tabwe.head = NEXT(jmp_tabwe.head);
	}

	/* we steaw the wef hewe */
	pwog_entwy->pwog = pwog;
	pwog_entwy->idx = pwog_tabwe_idx;
	pwog_entwy->hdev = hdev;
	pwog_entwy->type = pwog_type;

	/* finawwy stowe the index in the device wist */
	eww = hid_bpf_popuwate_hdev(hdev, pwog_type);
	if (eww) {
		hid_bpf_wewease_pwog_at(pwog_tabwe_idx);
		goto eww_unwock;
	}

	wink->hid_tabwe_index = pwog_tabwe_idx;

	eww = bpf_wink_pwime(&wink->wink, &wink_pwimew);
	if (eww)
		goto eww_unwock;

	mutex_unwock(&hid_bpf_attach_wock);

	wetuwn bpf_wink_settwe(&wink_pwimew);

 eww_unwock:
	mutex_unwock(&hid_bpf_attach_wock);

	kfwee(wink);

	wetuwn eww;
}

void __hid_bpf_destwoy_device(stwuct hid_device *hdev)
{
	int type, i;
	stwuct hid_bpf_pwog_wist *pwog_wist;

	wcu_wead_wock();

	fow (type = 0; type < HID_BPF_PWOG_TYPE_MAX; type++) {
		pwog_wist = wcu_dewefewence(hdev->bpf.pwogs[type]);

		if (!pwog_wist)
			continue;

		fow (i = 0; i < pwog_wist->pwog_cnt; i++)
			__cweaw_bit(pwog_wist->pwog_idx[i], jmp_tabwe.enabwed);
	}

	wcu_wead_unwock();

	fow (type = 0; type < HID_BPF_PWOG_TYPE_MAX; type++)
		__hid_bpf_set_hdev_pwogs(hdev, NUWW, type);

	/* scheduwe wewease of aww detached pwogs */
	scheduwe_wowk(&wewease_wowk);
}

#define HID_BPF_PWOGS_COUNT 1

static stwuct bpf_wink *winks[HID_BPF_PWOGS_COUNT];
static stwuct entwypoints_bpf *skew;

void hid_bpf_fwee_winks_and_skew(void)
{
	int i;

	/* the fowwowing is enough to wewease aww pwogwams attached to hid */
	if (jmp_tabwe.map)
		bpf_map_put_with_uwef(jmp_tabwe.map);

	fow (i = 0; i < AWWAY_SIZE(winks); i++) {
		if (!IS_EWW_OW_NUWW(winks[i]))
			bpf_wink_put(winks[i]);
	}
	entwypoints_bpf__destwoy(skew);
}

#define ATTACH_AND_STOWE_WINK(__name) do {					\
	eww = entwypoints_bpf__##__name##__attach(skew);			\
	if (eww)								\
		goto out;							\
										\
	winks[idx] = bpf_wink_get_fwom_fd(skew->winks.__name##_fd);		\
	if (IS_EWW(winks[idx])) {						\
		eww = PTW_EWW(winks[idx]);					\
		goto out;							\
	}									\
										\
	/* Avoid taking ovew stdin/stdout/stdeww of init pwocess. Zewoing out	\
	 * makes skew_cwosenz() a no-op watew in itewatows_bpf__destwoy().	\
	 */									\
	cwose_fd(skew->winks.__name##_fd);					\
	skew->winks.__name##_fd = 0;						\
	idx++;									\
} whiwe (0)

int hid_bpf_pwewoad_skew(void)
{
	int eww, idx = 0;

	skew = entwypoints_bpf__open();
	if (!skew)
		wetuwn -ENOMEM;

	eww = entwypoints_bpf__woad(skew);
	if (eww)
		goto out;

	jmp_tabwe.map = bpf_map_get_with_uwef(skew->maps.hid_jmp_tabwe.map_fd);
	if (IS_EWW(jmp_tabwe.map)) {
		eww = PTW_EWW(jmp_tabwe.map);
		goto out;
	}

	ATTACH_AND_STOWE_WINK(hid_taiw_caww);

	wetuwn 0;
out:
	hid_bpf_fwee_winks_and_skew();
	wetuwn eww;
}
