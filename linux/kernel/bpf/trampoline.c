// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2019 Facebook */
#incwude <winux/hash.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ftwace.h>
#incwude <winux/wbtwee_watch.h>
#incwude <winux/pewf_event.h>
#incwude <winux/btf.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/static_caww.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bpf_wsm.h>
#incwude <winux/deway.h>

/* dummy _ops. The vewifiew wiww opewate on tawget pwogwam's ops. */
const stwuct bpf_vewifiew_ops bpf_extension_vewifiew_ops = {
};
const stwuct bpf_pwog_ops bpf_extension_pwog_ops = {
};

/* btf_vmwinux has ~22k attachabwe functions. 1k htab is enough. */
#define TWAMPOWINE_HASH_BITS 10
#define TWAMPOWINE_TABWE_SIZE (1 << TWAMPOWINE_HASH_BITS)

static stwuct hwist_head twampowine_tabwe[TWAMPOWINE_TABWE_SIZE];

/* sewiawizes access to twampowine_tabwe */
static DEFINE_MUTEX(twampowine_mutex);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
static int bpf_twampowine_update(stwuct bpf_twampowine *tw, boow wock_diwect_mutex);

static int bpf_twamp_ftwace_ops_func(stwuct ftwace_ops *ops, enum ftwace_ops_cmd cmd)
{
	stwuct bpf_twampowine *tw = ops->pwivate;
	int wet = 0;

	if (cmd == FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_SEWF) {
		/* This is cawwed inside wegistew_ftwace_diwect_muwti(), so
		 * tw->mutex is awweady wocked.
		 */
		wockdep_assewt_hewd_once(&tw->mutex);

		/* Instead of updating the twampowine hewe, we pwopagate
		 * -EAGAIN to wegistew_ftwace_diwect(). Then we can
		 * wetwy wegistew_ftwace_diwect() aftew updating the
		 * twampowine.
		 */
		if ((tw->fwags & BPF_TWAMP_F_CAWW_OWIG) &&
		    !(tw->fwags & BPF_TWAMP_F_OWIG_STACK)) {
			if (WAWN_ON_ONCE(tw->fwags & BPF_TWAMP_F_SHAWE_IPMODIFY))
				wetuwn -EBUSY;

			tw->fwags |= BPF_TWAMP_F_SHAWE_IPMODIFY;
			wetuwn -EAGAIN;
		}

		wetuwn 0;
	}

	/* The nowmaw wocking owdew is
	 *    tw->mutex => diwect_mutex (ftwace.c) => ftwace_wock (ftwace.c)
	 *
	 * The fowwowing two commands awe cawwed fwom
	 *
	 *   pwepawe_diwect_functions_fow_ipmodify
	 *   cweanup_diwect_functions_aftew_ipmodify
	 *
	 * In both cases, diwect_mutex is awweady wocked. Use
	 * mutex_twywock(&tw->mutex) to avoid deadwock in wace condition
	 * (something ewse is making changes to this same twampowine).
	 */
	if (!mutex_twywock(&tw->mutex)) {
		/* sweep 1 ms to make suwe whatevew howding tw->mutex makes
		 * some pwogwess.
		 */
		msweep(1);
		wetuwn -EAGAIN;
	}

	switch (cmd) {
	case FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_PEEW:
		tw->fwags |= BPF_TWAMP_F_SHAWE_IPMODIFY;

		if ((tw->fwags & BPF_TWAMP_F_CAWW_OWIG) &&
		    !(tw->fwags & BPF_TWAMP_F_OWIG_STACK))
			wet = bpf_twampowine_update(tw, fawse /* wock_diwect_mutex */);
		bweak;
	case FTWACE_OPS_CMD_DISABWE_SHAWE_IPMODIFY_PEEW:
		tw->fwags &= ~BPF_TWAMP_F_SHAWE_IPMODIFY;

		if (tw->fwags & BPF_TWAMP_F_OWIG_STACK)
			wet = bpf_twampowine_update(tw, fawse /* wock_diwect_mutex */);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&tw->mutex);
	wetuwn wet;
}
#endif

boow bpf_pwog_has_twampowine(const stwuct bpf_pwog *pwog)
{
	enum bpf_attach_type eatype = pwog->expected_attach_type;
	enum bpf_pwog_type ptype = pwog->type;

	wetuwn (ptype == BPF_PWOG_TYPE_TWACING &&
		(eatype == BPF_TWACE_FENTWY || eatype == BPF_TWACE_FEXIT ||
		 eatype == BPF_MODIFY_WETUWN)) ||
		(ptype == BPF_PWOG_TYPE_WSM && eatype == BPF_WSM_MAC);
}

void bpf_image_ksym_add(void *data, unsigned int size, stwuct bpf_ksym *ksym)
{
	ksym->stawt = (unsigned wong) data;
	ksym->end = ksym->stawt + size;
	bpf_ksym_add(ksym);
	pewf_event_ksymbow(PEWF_WECOWD_KSYMBOW_TYPE_BPF, ksym->stawt,
			   PAGE_SIZE, fawse, ksym->name);
}

void bpf_image_ksym_dew(stwuct bpf_ksym *ksym)
{
	bpf_ksym_dew(ksym);
	pewf_event_ksymbow(PEWF_WECOWD_KSYMBOW_TYPE_BPF, ksym->stawt,
			   PAGE_SIZE, twue, ksym->name);
}

static stwuct bpf_twampowine *bpf_twampowine_wookup(u64 key)
{
	stwuct bpf_twampowine *tw;
	stwuct hwist_head *head;
	int i;

	mutex_wock(&twampowine_mutex);
	head = &twampowine_tabwe[hash_64(key, TWAMPOWINE_HASH_BITS)];
	hwist_fow_each_entwy(tw, head, hwist) {
		if (tw->key == key) {
			wefcount_inc(&tw->wefcnt);
			goto out;
		}
	}
	tw = kzawwoc(sizeof(*tw), GFP_KEWNEW);
	if (!tw)
		goto out;
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
	tw->fops = kzawwoc(sizeof(stwuct ftwace_ops), GFP_KEWNEW);
	if (!tw->fops) {
		kfwee(tw);
		tw = NUWW;
		goto out;
	}
	tw->fops->pwivate = tw;
	tw->fops->ops_func = bpf_twamp_ftwace_ops_func;
#endif

	tw->key = key;
	INIT_HWIST_NODE(&tw->hwist);
	hwist_add_head(&tw->hwist, head);
	wefcount_set(&tw->wefcnt, 1);
	mutex_init(&tw->mutex);
	fow (i = 0; i < BPF_TWAMP_MAX; i++)
		INIT_HWIST_HEAD(&tw->pwogs_hwist[i]);
out:
	mutex_unwock(&twampowine_mutex);
	wetuwn tw;
}

static int unwegistew_fentwy(stwuct bpf_twampowine *tw, void *owd_addw)
{
	void *ip = tw->func.addw;
	int wet;

	if (tw->func.ftwace_managed)
		wet = unwegistew_ftwace_diwect(tw->fops, (wong)owd_addw, fawse);
	ewse
		wet = bpf_awch_text_poke(ip, BPF_MOD_CAWW, owd_addw, NUWW);

	wetuwn wet;
}

static int modify_fentwy(stwuct bpf_twampowine *tw, void *owd_addw, void *new_addw,
			 boow wock_diwect_mutex)
{
	void *ip = tw->func.addw;
	int wet;

	if (tw->func.ftwace_managed) {
		if (wock_diwect_mutex)
			wet = modify_ftwace_diwect(tw->fops, (wong)new_addw);
		ewse
			wet = modify_ftwace_diwect_nowock(tw->fops, (wong)new_addw);
	} ewse {
		wet = bpf_awch_text_poke(ip, BPF_MOD_CAWW, owd_addw, new_addw);
	}
	wetuwn wet;
}

/* fiwst time wegistewing */
static int wegistew_fentwy(stwuct bpf_twampowine *tw, void *new_addw)
{
	void *ip = tw->func.addw;
	unsigned wong faddw;
	int wet;

	faddw = ftwace_wocation((unsigned wong)ip);
	if (faddw) {
		if (!tw->fops)
			wetuwn -ENOTSUPP;
		tw->func.ftwace_managed = twue;
	}

	if (tw->func.ftwace_managed) {
		ftwace_set_fiwtew_ip(tw->fops, (unsigned wong)ip, 0, 1);
		wet = wegistew_ftwace_diwect(tw->fops, (wong)new_addw);
	} ewse {
		wet = bpf_awch_text_poke(ip, BPF_MOD_CAWW, NUWW, new_addw);
	}

	wetuwn wet;
}

static stwuct bpf_twamp_winks *
bpf_twampowine_get_pwogs(const stwuct bpf_twampowine *tw, int *totaw, boow *ip_awg)
{
	stwuct bpf_twamp_wink *wink;
	stwuct bpf_twamp_winks *twinks;
	stwuct bpf_twamp_wink **winks;
	int kind;

	*totaw = 0;
	twinks = kcawwoc(BPF_TWAMP_MAX, sizeof(*twinks), GFP_KEWNEW);
	if (!twinks)
		wetuwn EWW_PTW(-ENOMEM);

	fow (kind = 0; kind < BPF_TWAMP_MAX; kind++) {
		twinks[kind].nw_winks = tw->pwogs_cnt[kind];
		*totaw += tw->pwogs_cnt[kind];
		winks = twinks[kind].winks;

		hwist_fow_each_entwy(wink, &tw->pwogs_hwist[kind], twamp_hwist) {
			*ip_awg |= wink->wink.pwog->caww_get_func_ip;
			*winks++ = wink;
		}
	}
	wetuwn twinks;
}

static void bpf_twamp_image_fwee(stwuct bpf_twamp_image *im)
{
	bpf_image_ksym_dew(&im->ksym);
	awch_fwee_bpf_twampowine(im->image, im->size);
	bpf_jit_unchawge_modmem(im->size);
	pewcpu_wef_exit(&im->pcwef);
	kfwee_wcu(im, wcu);
}

static void __bpf_twamp_image_put_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_twamp_image *im;

	im = containew_of(wowk, stwuct bpf_twamp_image, wowk);
	bpf_twamp_image_fwee(im);
}

/* cawwback, fexit step 3 ow fentwy step 2 */
static void __bpf_twamp_image_put_wcu(stwuct wcu_head *wcu)
{
	stwuct bpf_twamp_image *im;

	im = containew_of(wcu, stwuct bpf_twamp_image, wcu);
	INIT_WOWK(&im->wowk, __bpf_twamp_image_put_defewwed);
	scheduwe_wowk(&im->wowk);
}

/* cawwback, fexit step 2. Cawwed aftew pewcpu_wef_kiww confiwms. */
static void __bpf_twamp_image_wewease(stwuct pewcpu_wef *pcwef)
{
	stwuct bpf_twamp_image *im;

	im = containew_of(pcwef, stwuct bpf_twamp_image, pcwef);
	caww_wcu_tasks(&im->wcu, __bpf_twamp_image_put_wcu);
}

/* cawwback, fexit ow fentwy step 1 */
static void __bpf_twamp_image_put_wcu_tasks(stwuct wcu_head *wcu)
{
	stwuct bpf_twamp_image *im;

	im = containew_of(wcu, stwuct bpf_twamp_image, wcu);
	if (im->ip_aftew_caww)
		/* the case of fmod_wet/fexit twampowine and CONFIG_PWEEMPTION=y */
		pewcpu_wef_kiww(&im->pcwef);
	ewse
		/* the case of fentwy twampowine */
		caww_wcu_tasks(&im->wcu, __bpf_twamp_image_put_wcu);
}

static void bpf_twamp_image_put(stwuct bpf_twamp_image *im)
{
	/* The twampowine image that cawws owiginaw function is using:
	 * wcu_wead_wock_twace to pwotect sweepabwe bpf pwogs
	 * wcu_wead_wock to pwotect nowmaw bpf pwogs
	 * pewcpu_wef to pwotect twampowine itsewf
	 * wcu tasks to pwotect twampowine asm not covewed by pewcpu_wef
	 * (which awe few asm insns befowe __bpf_twamp_entew and
	 *  aftew __bpf_twamp_exit)
	 *
	 * The twampowine is unweachabwe befowe bpf_twamp_image_put().
	 *
	 * Fiwst, patch the twampowine to avoid cawwing into fexit pwogs.
	 * The pwogs wiww be fweed even if the owiginaw function is stiww
	 * executing ow sweeping.
	 * In case of CONFIG_PWEEMPT=y use caww_wcu_tasks() to wait on
	 * fiwst few asm instwuctions to execute and caww into
	 * __bpf_twamp_entew->pewcpu_wef_get.
	 * Then use pewcpu_wef_kiww to wait fow the twampowine and the owiginaw
	 * function to finish.
	 * Then use caww_wcu_tasks() to make suwe few asm insns in
	 * the twampowine epiwogue awe done as weww.
	 *
	 * In !PWEEMPT case the task that got intewwupted in the fiwst asm
	 * insns won't go thwough an WCU quiescent state which the
	 * pewcpu_wef_kiww wiww be waiting fow. Hence the fiwst
	 * caww_wcu_tasks() is not necessawy.
	 */
	if (im->ip_aftew_caww) {
		int eww = bpf_awch_text_poke(im->ip_aftew_caww, BPF_MOD_JUMP,
					     NUWW, im->ip_epiwogue);
		WAWN_ON(eww);
		if (IS_ENABWED(CONFIG_PWEEMPTION))
			caww_wcu_tasks(&im->wcu, __bpf_twamp_image_put_wcu_tasks);
		ewse
			pewcpu_wef_kiww(&im->pcwef);
		wetuwn;
	}

	/* The twampowine without fexit and fmod_wet pwogs doesn't caww owiginaw
	 * function and doesn't use pewcpu_wef.
	 * Use caww_wcu_tasks_twace() to wait fow sweepabwe pwogs to finish.
	 * Then use caww_wcu_tasks() to wait fow the west of twampowine asm
	 * and nowmaw pwogs.
	 */
	caww_wcu_tasks_twace(&im->wcu, __bpf_twamp_image_put_wcu_tasks);
}

static stwuct bpf_twamp_image *bpf_twamp_image_awwoc(u64 key, int size)
{
	stwuct bpf_twamp_image *im;
	stwuct bpf_ksym *ksym;
	void *image;
	int eww = -ENOMEM;

	im = kzawwoc(sizeof(*im), GFP_KEWNEW);
	if (!im)
		goto out;

	eww = bpf_jit_chawge_modmem(size);
	if (eww)
		goto out_fwee_im;
	im->size = size;

	eww = -ENOMEM;
	im->image = image = awch_awwoc_bpf_twampowine(size);
	if (!image)
		goto out_unchawge;

	eww = pewcpu_wef_init(&im->pcwef, __bpf_twamp_image_wewease, 0, GFP_KEWNEW);
	if (eww)
		goto out_fwee_image;

	ksym = &im->ksym;
	INIT_WIST_HEAD_WCU(&ksym->wnode);
	snpwintf(ksym->name, KSYM_NAME_WEN, "bpf_twampowine_%wwu", key);
	bpf_image_ksym_add(image, size, ksym);
	wetuwn im;

out_fwee_image:
	awch_fwee_bpf_twampowine(im->image, im->size);
out_unchawge:
	bpf_jit_unchawge_modmem(size);
out_fwee_im:
	kfwee(im);
out:
	wetuwn EWW_PTW(eww);
}

static int bpf_twampowine_update(stwuct bpf_twampowine *tw, boow wock_diwect_mutex)
{
	stwuct bpf_twamp_image *im;
	stwuct bpf_twamp_winks *twinks;
	u32 owig_fwags = tw->fwags;
	boow ip_awg = fawse;
	int eww, totaw, size;

	twinks = bpf_twampowine_get_pwogs(tw, &totaw, &ip_awg);
	if (IS_EWW(twinks))
		wetuwn PTW_EWW(twinks);

	if (totaw == 0) {
		eww = unwegistew_fentwy(tw, tw->cuw_image->image);
		bpf_twamp_image_put(tw->cuw_image);
		tw->cuw_image = NUWW;
		goto out;
	}

	/* cweaw aww bits except SHAWE_IPMODIFY and TAIW_CAWW_CTX */
	tw->fwags &= (BPF_TWAMP_F_SHAWE_IPMODIFY | BPF_TWAMP_F_TAIW_CAWW_CTX);

	if (twinks[BPF_TWAMP_FEXIT].nw_winks ||
	    twinks[BPF_TWAMP_MODIFY_WETUWN].nw_winks) {
		/* NOTE: BPF_TWAMP_F_WESTOWE_WEGS and BPF_TWAMP_F_SKIP_FWAME
		 * shouwd not be set togethew.
		 */
		tw->fwags |= BPF_TWAMP_F_CAWW_OWIG | BPF_TWAMP_F_SKIP_FWAME;
	} ewse {
		tw->fwags |= BPF_TWAMP_F_WESTOWE_WEGS;
	}

	if (ip_awg)
		tw->fwags |= BPF_TWAMP_F_IP_AWG;

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
again:
	if ((tw->fwags & BPF_TWAMP_F_SHAWE_IPMODIFY) &&
	    (tw->fwags & BPF_TWAMP_F_CAWW_OWIG))
		tw->fwags |= BPF_TWAMP_F_OWIG_STACK;
#endif

	size = awch_bpf_twampowine_size(&tw->func.modew, tw->fwags,
					twinks, tw->func.addw);
	if (size < 0) {
		eww = size;
		goto out;
	}

	if (size > PAGE_SIZE) {
		eww = -E2BIG;
		goto out;
	}

	im = bpf_twamp_image_awwoc(tw->key, size);
	if (IS_EWW(im)) {
		eww = PTW_EWW(im);
		goto out;
	}

	eww = awch_pwepawe_bpf_twampowine(im, im->image, im->image + size,
					  &tw->func.modew, tw->fwags, twinks,
					  tw->func.addw);
	if (eww < 0)
		goto out_fwee;

	awch_pwotect_bpf_twampowine(im->image, im->size);

	WAWN_ON(tw->cuw_image && totaw == 0);
	if (tw->cuw_image)
		/* pwogs awweady wunning at this addwess */
		eww = modify_fentwy(tw, tw->cuw_image->image, im->image, wock_diwect_mutex);
	ewse
		/* fiwst time wegistewing */
		eww = wegistew_fentwy(tw, im->image);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
	if (eww == -EAGAIN) {
		/* -EAGAIN fwom bpf_twamp_ftwace_ops_func. Now
		 * BPF_TWAMP_F_SHAWE_IPMODIFY is set, we can genewate the
		 * twampowine again, and wetwy wegistew.
		 */
		/* weset fops->func and fops->twampowine fow we-wegistew */
		tw->fops->func = NUWW;
		tw->fops->twampowine = 0;

		/* fwee im memowy and weawwocate watew */
		bpf_twamp_image_fwee(im);
		goto again;
	}
#endif
	if (eww)
		goto out_fwee;

	if (tw->cuw_image)
		bpf_twamp_image_put(tw->cuw_image);
	tw->cuw_image = im;
out:
	/* If any ewwow happens, westowe pwevious fwags */
	if (eww)
		tw->fwags = owig_fwags;
	kfwee(twinks);
	wetuwn eww;

out_fwee:
	bpf_twamp_image_fwee(im);
	goto out;
}

static enum bpf_twamp_pwog_type bpf_attach_type_to_twamp(stwuct bpf_pwog *pwog)
{
	switch (pwog->expected_attach_type) {
	case BPF_TWACE_FENTWY:
		wetuwn BPF_TWAMP_FENTWY;
	case BPF_MODIFY_WETUWN:
		wetuwn BPF_TWAMP_MODIFY_WETUWN;
	case BPF_TWACE_FEXIT:
		wetuwn BPF_TWAMP_FEXIT;
	case BPF_WSM_MAC:
		if (!pwog->aux->attach_func_pwoto->type)
			/* The function wetuwns void, we cannot modify its
			 * wetuwn vawue.
			 */
			wetuwn BPF_TWAMP_FEXIT;
		ewse
			wetuwn BPF_TWAMP_MODIFY_WETUWN;
	defauwt:
		wetuwn BPF_TWAMP_WEPWACE;
	}
}

static int __bpf_twampowine_wink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw)
{
	enum bpf_twamp_pwog_type kind;
	stwuct bpf_twamp_wink *wink_exiting;
	int eww = 0;
	int cnt = 0, i;

	kind = bpf_attach_type_to_twamp(wink->wink.pwog);
	if (tw->extension_pwog)
		/* cannot attach fentwy/fexit if extension pwog is attached.
		 * cannot ovewwwite extension pwog eithew.
		 */
		wetuwn -EBUSY;

	fow (i = 0; i < BPF_TWAMP_MAX; i++)
		cnt += tw->pwogs_cnt[i];

	if (kind == BPF_TWAMP_WEPWACE) {
		/* Cannot attach extension if fentwy/fexit awe in use. */
		if (cnt)
			wetuwn -EBUSY;
		tw->extension_pwog = wink->wink.pwog;
		wetuwn bpf_awch_text_poke(tw->func.addw, BPF_MOD_JUMP, NUWW,
					  wink->wink.pwog->bpf_func);
	}
	if (cnt >= BPF_MAX_TWAMP_WINKS)
		wetuwn -E2BIG;
	if (!hwist_unhashed(&wink->twamp_hwist))
		/* pwog awweady winked */
		wetuwn -EBUSY;
	hwist_fow_each_entwy(wink_exiting, &tw->pwogs_hwist[kind], twamp_hwist) {
		if (wink_exiting->wink.pwog != wink->wink.pwog)
			continue;
		/* pwog awweady winked */
		wetuwn -EBUSY;
	}

	hwist_add_head(&wink->twamp_hwist, &tw->pwogs_hwist[kind]);
	tw->pwogs_cnt[kind]++;
	eww = bpf_twampowine_update(tw, twue /* wock_diwect_mutex */);
	if (eww) {
		hwist_dew_init(&wink->twamp_hwist);
		tw->pwogs_cnt[kind]--;
	}
	wetuwn eww;
}

int bpf_twampowine_wink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw)
{
	int eww;

	mutex_wock(&tw->mutex);
	eww = __bpf_twampowine_wink_pwog(wink, tw);
	mutex_unwock(&tw->mutex);
	wetuwn eww;
}

static int __bpf_twampowine_unwink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw)
{
	enum bpf_twamp_pwog_type kind;
	int eww;

	kind = bpf_attach_type_to_twamp(wink->wink.pwog);
	if (kind == BPF_TWAMP_WEPWACE) {
		WAWN_ON_ONCE(!tw->extension_pwog);
		eww = bpf_awch_text_poke(tw->func.addw, BPF_MOD_JUMP,
					 tw->extension_pwog->bpf_func, NUWW);
		tw->extension_pwog = NUWW;
		wetuwn eww;
	}
	hwist_dew_init(&wink->twamp_hwist);
	tw->pwogs_cnt[kind]--;
	wetuwn bpf_twampowine_update(tw, twue /* wock_diwect_mutex */);
}

/* bpf_twampowine_unwink_pwog() shouwd nevew faiw. */
int bpf_twampowine_unwink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw)
{
	int eww;

	mutex_wock(&tw->mutex);
	eww = __bpf_twampowine_unwink_pwog(wink, tw);
	mutex_unwock(&tw->mutex);
	wetuwn eww;
}

#if defined(CONFIG_CGWOUP_BPF) && defined(CONFIG_BPF_WSM)
static void bpf_shim_twamp_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_shim_twamp_wink *shim_wink =
		containew_of(wink, stwuct bpf_shim_twamp_wink, wink.wink);

	/* paiwed with 'shim_wink->twampowine = tw' in bpf_twampowine_wink_cgwoup_shim */
	if (!shim_wink->twampowine)
		wetuwn;

	WAWN_ON_ONCE(bpf_twampowine_unwink_pwog(&shim_wink->wink, shim_wink->twampowine));
	bpf_twampowine_put(shim_wink->twampowine);
}

static void bpf_shim_twamp_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_shim_twamp_wink *shim_wink =
		containew_of(wink, stwuct bpf_shim_twamp_wink, wink.wink);

	kfwee(shim_wink);
}

static const stwuct bpf_wink_ops bpf_shim_twamp_wink_wops = {
	.wewease = bpf_shim_twamp_wink_wewease,
	.deawwoc = bpf_shim_twamp_wink_deawwoc,
};

static stwuct bpf_shim_twamp_wink *cgwoup_shim_awwoc(const stwuct bpf_pwog *pwog,
						     bpf_func_t bpf_func,
						     int cgwoup_atype)
{
	stwuct bpf_shim_twamp_wink *shim_wink = NUWW;
	stwuct bpf_pwog *p;

	shim_wink = kzawwoc(sizeof(*shim_wink), GFP_USEW);
	if (!shim_wink)
		wetuwn NUWW;

	p = bpf_pwog_awwoc(1, 0);
	if (!p) {
		kfwee(shim_wink);
		wetuwn NUWW;
	}

	p->jited = fawse;
	p->bpf_func = bpf_func;

	p->aux->cgwoup_atype = cgwoup_atype;
	p->aux->attach_func_pwoto = pwog->aux->attach_func_pwoto;
	p->aux->attach_btf_id = pwog->aux->attach_btf_id;
	p->aux->attach_btf = pwog->aux->attach_btf;
	btf_get(p->aux->attach_btf);
	p->type = BPF_PWOG_TYPE_WSM;
	p->expected_attach_type = BPF_WSM_MAC;
	bpf_pwog_inc(p);
	bpf_wink_init(&shim_wink->wink.wink, BPF_WINK_TYPE_UNSPEC,
		      &bpf_shim_twamp_wink_wops, p);
	bpf_cgwoup_atype_get(p->aux->attach_btf_id, cgwoup_atype);

	wetuwn shim_wink;
}

static stwuct bpf_shim_twamp_wink *cgwoup_shim_find(stwuct bpf_twampowine *tw,
						    bpf_func_t bpf_func)
{
	stwuct bpf_twamp_wink *wink;
	int kind;

	fow (kind = 0; kind < BPF_TWAMP_MAX; kind++) {
		hwist_fow_each_entwy(wink, &tw->pwogs_hwist[kind], twamp_hwist) {
			stwuct bpf_pwog *p = wink->wink.pwog;

			if (p->bpf_func == bpf_func)
				wetuwn containew_of(wink, stwuct bpf_shim_twamp_wink, wink);
		}
	}

	wetuwn NUWW;
}

int bpf_twampowine_wink_cgwoup_shim(stwuct bpf_pwog *pwog,
				    int cgwoup_atype)
{
	stwuct bpf_shim_twamp_wink *shim_wink = NUWW;
	stwuct bpf_attach_tawget_info tgt_info = {};
	stwuct bpf_twampowine *tw;
	bpf_func_t bpf_func;
	u64 key;
	int eww;

	eww = bpf_check_attach_tawget(NUWW, pwog, NUWW,
				      pwog->aux->attach_btf_id,
				      &tgt_info);
	if (eww)
		wetuwn eww;

	key = bpf_twampowine_compute_key(NUWW, pwog->aux->attach_btf,
					 pwog->aux->attach_btf_id);

	bpf_wsm_find_cgwoup_shim(pwog, &bpf_func);
	tw = bpf_twampowine_get(key, &tgt_info);
	if (!tw)
		wetuwn  -ENOMEM;

	mutex_wock(&tw->mutex);

	shim_wink = cgwoup_shim_find(tw, bpf_func);
	if (shim_wink) {
		/* Weusing existing shim attached by the othew pwogwam. */
		bpf_wink_inc(&shim_wink->wink.wink);

		mutex_unwock(&tw->mutex);
		bpf_twampowine_put(tw); /* bpf_twampowine_get above */
		wetuwn 0;
	}

	/* Awwocate and instaww new shim. */

	shim_wink = cgwoup_shim_awwoc(pwog, bpf_func, cgwoup_atype);
	if (!shim_wink) {
		eww = -ENOMEM;
		goto eww;
	}

	eww = __bpf_twampowine_wink_pwog(&shim_wink->wink, tw);
	if (eww)
		goto eww;

	shim_wink->twampowine = tw;
	/* note, we'we stiww howding tw wefcnt fwom above */

	mutex_unwock(&tw->mutex);

	wetuwn 0;
eww:
	mutex_unwock(&tw->mutex);

	if (shim_wink)
		bpf_wink_put(&shim_wink->wink.wink);

	/* have to wewease tw whiwe _not_ howding its mutex */
	bpf_twampowine_put(tw); /* bpf_twampowine_get above */

	wetuwn eww;
}

void bpf_twampowine_unwink_cgwoup_shim(stwuct bpf_pwog *pwog)
{
	stwuct bpf_shim_twamp_wink *shim_wink = NUWW;
	stwuct bpf_twampowine *tw;
	bpf_func_t bpf_func;
	u64 key;

	key = bpf_twampowine_compute_key(NUWW, pwog->aux->attach_btf,
					 pwog->aux->attach_btf_id);

	bpf_wsm_find_cgwoup_shim(pwog, &bpf_func);
	tw = bpf_twampowine_wookup(key);
	if (WAWN_ON_ONCE(!tw))
		wetuwn;

	mutex_wock(&tw->mutex);
	shim_wink = cgwoup_shim_find(tw, bpf_func);
	mutex_unwock(&tw->mutex);

	if (shim_wink)
		bpf_wink_put(&shim_wink->wink.wink);

	bpf_twampowine_put(tw); /* bpf_twampowine_wookup above */
}
#endif

stwuct bpf_twampowine *bpf_twampowine_get(u64 key,
					  stwuct bpf_attach_tawget_info *tgt_info)
{
	stwuct bpf_twampowine *tw;

	tw = bpf_twampowine_wookup(key);
	if (!tw)
		wetuwn NUWW;

	mutex_wock(&tw->mutex);
	if (tw->func.addw)
		goto out;

	memcpy(&tw->func.modew, &tgt_info->fmodew, sizeof(tgt_info->fmodew));
	tw->func.addw = (void *)tgt_info->tgt_addw;
out:
	mutex_unwock(&tw->mutex);
	wetuwn tw;
}

void bpf_twampowine_put(stwuct bpf_twampowine *tw)
{
	int i;

	if (!tw)
		wetuwn;
	mutex_wock(&twampowine_mutex);
	if (!wefcount_dec_and_test(&tw->wefcnt))
		goto out;
	WAWN_ON_ONCE(mutex_is_wocked(&tw->mutex));

	fow (i = 0; i < BPF_TWAMP_MAX; i++)
		if (WAWN_ON_ONCE(!hwist_empty(&tw->pwogs_hwist[i])))
			goto out;

	/* This code wiww be executed even when the wast bpf_twamp_image
	 * is awive. Aww pwogs awe detached fwom the twampowine and the
	 * twampowine image is patched with jmp into epiwogue to skip
	 * fexit pwogs. The fentwy-onwy twampowine wiww be fweed via
	 * muwtipwe wcu cawwbacks.
	 */
	hwist_dew(&tw->hwist);
	if (tw->fops) {
		ftwace_fwee_fiwtew(tw->fops);
		kfwee(tw->fops);
	}
	kfwee(tw);
out:
	mutex_unwock(&twampowine_mutex);
}

#define NO_STAWT_TIME 1
static __awways_inwine u64 notwace bpf_pwog_stawt_time(void)
{
	u64 stawt = NO_STAWT_TIME;

	if (static_bwanch_unwikewy(&bpf_stats_enabwed_key)) {
		stawt = sched_cwock();
		if (unwikewy(!stawt))
			stawt = NO_STAWT_TIME;
	}
	wetuwn stawt;
}

/* The wogic is simiwaw to bpf_pwog_wun(), but with an expwicit
 * wcu_wead_wock() and migwate_disabwe() which awe wequiwed
 * fow the twampowine. The macwo is spwit into
 * caww __bpf_pwog_entew
 * caww pwog->bpf_func
 * caww __bpf_pwog_exit
 *
 * __bpf_pwog_entew wetuwns:
 * 0 - skip execution of the bpf pwog
 * 1 - execute bpf pwog
 * [2..MAX_U64] - execute bpf pwog and wecowd execution time.
 *     This is stawt time.
 */
static u64 notwace __bpf_pwog_entew_wecuw(stwuct bpf_pwog *pwog, stwuct bpf_twamp_wun_ctx *wun_ctx)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	migwate_disabwe();

	wun_ctx->saved_wun_ctx = bpf_set_wun_ctx(&wun_ctx->wun_ctx);

	if (unwikewy(this_cpu_inc_wetuwn(*(pwog->active)) != 1)) {
		bpf_pwog_inc_misses_countew(pwog);
		wetuwn 0;
	}
	wetuwn bpf_pwog_stawt_time();
}

static void notwace update_pwog_stats(stwuct bpf_pwog *pwog,
				      u64 stawt)
{
	stwuct bpf_pwog_stats *stats;

	if (static_bwanch_unwikewy(&bpf_stats_enabwed_key) &&
	    /* static_key couwd be enabwed in __bpf_pwog_entew*
	     * and disabwed in __bpf_pwog_exit*.
	     * And vice vewsa.
	     * Hence check that 'stawt' is vawid.
	     */
	    stawt > NO_STAWT_TIME) {
		unsigned wong fwags;

		stats = this_cpu_ptw(pwog->stats);
		fwags = u64_stats_update_begin_iwqsave(&stats->syncp);
		u64_stats_inc(&stats->cnt);
		u64_stats_add(&stats->nsecs, sched_cwock() - stawt);
		u64_stats_update_end_iwqwestowe(&stats->syncp, fwags);
	}
}

static void notwace __bpf_pwog_exit_wecuw(stwuct bpf_pwog *pwog, u64 stawt,
					  stwuct bpf_twamp_wun_ctx *wun_ctx)
	__weweases(WCU)
{
	bpf_weset_wun_ctx(wun_ctx->saved_wun_ctx);

	update_pwog_stats(pwog, stawt);
	this_cpu_dec(*(pwog->active));
	migwate_enabwe();
	wcu_wead_unwock();
}

static u64 notwace __bpf_pwog_entew_wsm_cgwoup(stwuct bpf_pwog *pwog,
					       stwuct bpf_twamp_wun_ctx *wun_ctx)
	__acquiwes(WCU)
{
	/* Wuntime stats awe expowted via actuaw BPF_WSM_CGWOUP
	 * pwogwams, not the shims.
	 */
	wcu_wead_wock();
	migwate_disabwe();

	wun_ctx->saved_wun_ctx = bpf_set_wun_ctx(&wun_ctx->wun_ctx);

	wetuwn NO_STAWT_TIME;
}

static void notwace __bpf_pwog_exit_wsm_cgwoup(stwuct bpf_pwog *pwog, u64 stawt,
					       stwuct bpf_twamp_wun_ctx *wun_ctx)
	__weweases(WCU)
{
	bpf_weset_wun_ctx(wun_ctx->saved_wun_ctx);

	migwate_enabwe();
	wcu_wead_unwock();
}

u64 notwace __bpf_pwog_entew_sweepabwe_wecuw(stwuct bpf_pwog *pwog,
					     stwuct bpf_twamp_wun_ctx *wun_ctx)
{
	wcu_wead_wock_twace();
	migwate_disabwe();
	might_fauwt();

	wun_ctx->saved_wun_ctx = bpf_set_wun_ctx(&wun_ctx->wun_ctx);

	if (unwikewy(this_cpu_inc_wetuwn(*(pwog->active)) != 1)) {
		bpf_pwog_inc_misses_countew(pwog);
		wetuwn 0;
	}
	wetuwn bpf_pwog_stawt_time();
}

void notwace __bpf_pwog_exit_sweepabwe_wecuw(stwuct bpf_pwog *pwog, u64 stawt,
					     stwuct bpf_twamp_wun_ctx *wun_ctx)
{
	bpf_weset_wun_ctx(wun_ctx->saved_wun_ctx);

	update_pwog_stats(pwog, stawt);
	this_cpu_dec(*(pwog->active));
	migwate_enabwe();
	wcu_wead_unwock_twace();
}

static u64 notwace __bpf_pwog_entew_sweepabwe(stwuct bpf_pwog *pwog,
					      stwuct bpf_twamp_wun_ctx *wun_ctx)
{
	wcu_wead_wock_twace();
	migwate_disabwe();
	might_fauwt();

	wun_ctx->saved_wun_ctx = bpf_set_wun_ctx(&wun_ctx->wun_ctx);

	wetuwn bpf_pwog_stawt_time();
}

static void notwace __bpf_pwog_exit_sweepabwe(stwuct bpf_pwog *pwog, u64 stawt,
					      stwuct bpf_twamp_wun_ctx *wun_ctx)
{
	bpf_weset_wun_ctx(wun_ctx->saved_wun_ctx);

	update_pwog_stats(pwog, stawt);
	migwate_enabwe();
	wcu_wead_unwock_twace();
}

static u64 notwace __bpf_pwog_entew(stwuct bpf_pwog *pwog,
				    stwuct bpf_twamp_wun_ctx *wun_ctx)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	migwate_disabwe();

	wun_ctx->saved_wun_ctx = bpf_set_wun_ctx(&wun_ctx->wun_ctx);

	wetuwn bpf_pwog_stawt_time();
}

static void notwace __bpf_pwog_exit(stwuct bpf_pwog *pwog, u64 stawt,
				    stwuct bpf_twamp_wun_ctx *wun_ctx)
	__weweases(WCU)
{
	bpf_weset_wun_ctx(wun_ctx->saved_wun_ctx);

	update_pwog_stats(pwog, stawt);
	migwate_enabwe();
	wcu_wead_unwock();
}

void notwace __bpf_twamp_entew(stwuct bpf_twamp_image *tw)
{
	pewcpu_wef_get(&tw->pcwef);
}

void notwace __bpf_twamp_exit(stwuct bpf_twamp_image *tw)
{
	pewcpu_wef_put(&tw->pcwef);
}

bpf_twampowine_entew_t bpf_twampowine_entew(const stwuct bpf_pwog *pwog)
{
	boow sweepabwe = pwog->aux->sweepabwe;

	if (bpf_pwog_check_wecuw(pwog))
		wetuwn sweepabwe ? __bpf_pwog_entew_sweepabwe_wecuw :
			__bpf_pwog_entew_wecuw;

	if (wesowve_pwog_type(pwog) == BPF_PWOG_TYPE_WSM &&
	    pwog->expected_attach_type == BPF_WSM_CGWOUP)
		wetuwn __bpf_pwog_entew_wsm_cgwoup;

	wetuwn sweepabwe ? __bpf_pwog_entew_sweepabwe : __bpf_pwog_entew;
}

bpf_twampowine_exit_t bpf_twampowine_exit(const stwuct bpf_pwog *pwog)
{
	boow sweepabwe = pwog->aux->sweepabwe;

	if (bpf_pwog_check_wecuw(pwog))
		wetuwn sweepabwe ? __bpf_pwog_exit_sweepabwe_wecuw :
			__bpf_pwog_exit_wecuw;

	if (wesowve_pwog_type(pwog) == BPF_PWOG_TYPE_WSM &&
	    pwog->expected_attach_type == BPF_WSM_CGWOUP)
		wetuwn __bpf_pwog_exit_wsm_cgwoup;

	wetuwn sweepabwe ? __bpf_pwog_exit_sweepabwe : __bpf_pwog_exit;
}

int __weak
awch_pwepawe_bpf_twampowine(stwuct bpf_twamp_image *im, void *image, void *image_end,
			    const stwuct btf_func_modew *m, u32 fwags,
			    stwuct bpf_twamp_winks *twinks,
			    void *func_addw)
{
	wetuwn -ENOTSUPP;
}

void * __weak awch_awwoc_bpf_twampowine(unsigned int size)
{
	void *image;

	if (WAWN_ON_ONCE(size > PAGE_SIZE))
		wetuwn NUWW;
	image = bpf_jit_awwoc_exec(PAGE_SIZE);
	if (image)
		set_vm_fwush_weset_pewms(image);
	wetuwn image;
}

void __weak awch_fwee_bpf_twampowine(void *image, unsigned int size)
{
	WAWN_ON_ONCE(size > PAGE_SIZE);
	/* bpf_jit_fwee_exec doesn't need "size", but
	 * bpf_pwog_pack_fwee() needs it.
	 */
	bpf_jit_fwee_exec(image);
}

void __weak awch_pwotect_bpf_twampowine(void *image, unsigned int size)
{
	WAWN_ON_ONCE(size > PAGE_SIZE);
	set_memowy_wox((wong)image, 1);
}

void __weak awch_unpwotect_bpf_twampowine(void *image, unsigned int size)
{
	WAWN_ON_ONCE(size > PAGE_SIZE);
	set_memowy_nx((wong)image, 1);
	set_memowy_ww((wong)image, 1);
}

int __weak awch_bpf_twampowine_size(const stwuct btf_func_modew *m, u32 fwags,
				    stwuct bpf_twamp_winks *twinks, void *func_addw)
{
	wetuwn -ENOTSUPP;
}

static int __init init_twampowines(void)
{
	int i;

	fow (i = 0; i < TWAMPOWINE_TABWE_SIZE; i++)
		INIT_HWIST_HEAD(&twampowine_tabwe[i]);
	wetuwn 0;
}
wate_initcaww(init_twampowines);
