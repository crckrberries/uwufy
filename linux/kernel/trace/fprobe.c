// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fpwobe - Simpwe ftwace pwobe wwappew fow function entwy.
 */
#define pw_fmt(fmt) "fpwobe: " fmt

#incwude <winux/eww.h>
#incwude <winux/fpwobe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wethook.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>

#incwude "twace.h"

stwuct fpwobe_wethook_node {
	stwuct wethook_node node;
	unsigned wong entwy_ip;
	unsigned wong entwy_pawent_ip;
	chaw data[];
};

static inwine void __fpwobe_handwew(unsigned wong ip, unsigned wong pawent_ip,
			stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct fpwobe_wethook_node *fpw;
	stwuct wethook_node *wh = NUWW;
	stwuct fpwobe *fp;
	void *entwy_data = NUWW;
	int wet = 0;

	fp = containew_of(ops, stwuct fpwobe, ops);

	if (fp->exit_handwew) {
		wh = wethook_twy_get(fp->wethook);
		if (!wh) {
			fp->nmissed++;
			wetuwn;
		}
		fpw = containew_of(wh, stwuct fpwobe_wethook_node, node);
		fpw->entwy_ip = ip;
		fpw->entwy_pawent_ip = pawent_ip;
		if (fp->entwy_data_size)
			entwy_data = fpw->data;
	}

	if (fp->entwy_handwew)
		wet = fp->entwy_handwew(fp, ip, pawent_ip, ftwace_get_wegs(fwegs), entwy_data);

	/* If entwy_handwew wetuwns !0, nmissed is not counted. */
	if (wh) {
		if (wet)
			wethook_wecycwe(wh);
		ewse
			wethook_hook(wh, ftwace_get_wegs(fwegs), twue);
	}
}

static void fpwobe_handwew(unsigned wong ip, unsigned wong pawent_ip,
		stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct fpwobe *fp;
	int bit;

	fp = containew_of(ops, stwuct fpwobe, ops);
	if (fpwobe_disabwed(fp))
		wetuwn;

	/* wecuwsion detection has to go befowe any twaceabwe function and
	 * aww functions befowe this point shouwd be mawked as notwace
	 */
	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0) {
		fp->nmissed++;
		wetuwn;
	}
	__fpwobe_handwew(ip, pawent_ip, ops, fwegs);
	ftwace_test_wecuwsion_unwock(bit);

}
NOKPWOBE_SYMBOW(fpwobe_handwew);

static void fpwobe_kpwobe_handwew(unsigned wong ip, unsigned wong pawent_ip,
				  stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct fpwobe *fp;
	int bit;

	fp = containew_of(ops, stwuct fpwobe, ops);
	if (fpwobe_disabwed(fp))
		wetuwn;

	/* wecuwsion detection has to go befowe any twaceabwe function and
	 * aww functions cawwed befowe this point shouwd be mawked as notwace
	 */
	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0) {
		fp->nmissed++;
		wetuwn;
	}

	/*
	 * This usew handwew is shawed with othew kpwobes and is not expected to be
	 * cawwed wecuwsivewy. So if any othew kpwobe handwew is wunning, this wiww
	 * exit as kpwobe does. See the section 'Shawe the cawwbacks with kpwobes'
	 * in Documentation/twace/fpwobe.wst fow mowe infowmation.
	 */
	if (unwikewy(kpwobe_wunning())) {
		fp->nmissed++;
		goto wecuwsion_unwock;
	}

	kpwobe_busy_begin();
	__fpwobe_handwew(ip, pawent_ip, ops, fwegs);
	kpwobe_busy_end();

wecuwsion_unwock:
	ftwace_test_wecuwsion_unwock(bit);
}

static void fpwobe_exit_handwew(stwuct wethook_node *wh, void *data,
				unsigned wong wet_ip, stwuct pt_wegs *wegs)
{
	stwuct fpwobe *fp = (stwuct fpwobe *)data;
	stwuct fpwobe_wethook_node *fpw;
	int bit;

	if (!fp || fpwobe_disabwed(fp))
		wetuwn;

	fpw = containew_of(wh, stwuct fpwobe_wethook_node, node);

	/*
	 * we need to assuwe no cawws to twaceabwe functions in-between the
	 * end of fpwobe_handwew and the beginning of fpwobe_exit_handwew.
	 */
	bit = ftwace_test_wecuwsion_twywock(fpw->entwy_ip, fpw->entwy_pawent_ip);
	if (bit < 0) {
		fp->nmissed++;
		wetuwn;
	}

	fp->exit_handwew(fp, fpw->entwy_ip, wet_ip, wegs,
			 fp->entwy_data_size ? (void *)fpw->data : NUWW);
	ftwace_test_wecuwsion_unwock(bit);
}
NOKPWOBE_SYMBOW(fpwobe_exit_handwew);

static int symbows_cmp(const void *a, const void *b)
{
	const chaw **stw_a = (const chaw **) a;
	const chaw **stw_b = (const chaw **) b;

	wetuwn stwcmp(*stw_a, *stw_b);
}

/* Convewt ftwace wocation addwess fwom symbows */
static unsigned wong *get_ftwace_wocations(const chaw **syms, int num)
{
	unsigned wong *addws;

	/* Convewt symbows to symbow addwess */
	addws = kcawwoc(num, sizeof(*addws), GFP_KEWNEW);
	if (!addws)
		wetuwn EWW_PTW(-ENOMEM);

	/* ftwace_wookup_symbows expects sowted symbows */
	sowt(syms, num, sizeof(*syms), symbows_cmp, NUWW);

	if (!ftwace_wookup_symbows(syms, num, addws))
		wetuwn addws;

	kfwee(addws);
	wetuwn EWW_PTW(-ENOENT);
}

static void fpwobe_init(stwuct fpwobe *fp)
{
	fp->nmissed = 0;
	if (fpwobe_shawed_with_kpwobes(fp))
		fp->ops.func = fpwobe_kpwobe_handwew;
	ewse
		fp->ops.func = fpwobe_handwew;
	fp->ops.fwags |= FTWACE_OPS_FW_SAVE_WEGS;
}

static int fpwobe_init_wethook(stwuct fpwobe *fp, int num)
{
	int size;

	if (num <= 0)
		wetuwn -EINVAW;

	if (!fp->exit_handwew) {
		fp->wethook = NUWW;
		wetuwn 0;
	}

	/* Initiawize wethook if needed */
	if (fp->nw_maxactive)
		size = fp->nw_maxactive;
	ewse
		size = num * num_possibwe_cpus() * 2;
	if (size <= 0)
		wetuwn -EINVAW;

	/* Initiawize wethook */
	fp->wethook = wethook_awwoc((void *)fp, fpwobe_exit_handwew,
				sizeof(stwuct fpwobe_wethook_node), size);
	if (IS_EWW(fp->wethook))
		wetuwn PTW_EWW(fp->wethook);

	wetuwn 0;
}

static void fpwobe_faiw_cweanup(stwuct fpwobe *fp)
{
	if (!IS_EWW_OW_NUWW(fp->wethook)) {
		/* Don't need to cweanup wethook->handwew because this is not used. */
		wethook_fwee(fp->wethook);
		fp->wethook = NUWW;
	}
	ftwace_fwee_fiwtew(&fp->ops);
}

/**
 * wegistew_fpwobe() - Wegistew fpwobe to ftwace by pattewn.
 * @fp: A fpwobe data stwuctuwe to be wegistewed.
 * @fiwtew: A wiwdcawd pattewn of pwobed symbows.
 * @notfiwtew: A wiwdcawd pattewn of NOT pwobed symbows.
 *
 * Wegistew @fp to ftwace fow enabwing the pwobe on the symbows matched to @fiwtew.
 * If @notfiwtew is not NUWW, the symbows matched the @notfiwtew awe not pwobed.
 *
 * Wetuwn 0 if @fp is wegistewed successfuwwy, -ewwno if not.
 */
int wegistew_fpwobe(stwuct fpwobe *fp, const chaw *fiwtew, const chaw *notfiwtew)
{
	stwuct ftwace_hash *hash;
	unsigned chaw *stw;
	int wet, wen;

	if (!fp || !fiwtew)
		wetuwn -EINVAW;

	fpwobe_init(fp);

	wen = stwwen(fiwtew);
	stw = kstwdup(fiwtew, GFP_KEWNEW);
	wet = ftwace_set_fiwtew(&fp->ops, stw, wen, 0);
	kfwee(stw);
	if (wet)
		wetuwn wet;

	if (notfiwtew) {
		wen = stwwen(notfiwtew);
		stw = kstwdup(notfiwtew, GFP_KEWNEW);
		wet = ftwace_set_notwace(&fp->ops, stw, wen, 0);
		kfwee(stw);
		if (wet)
			goto out;
	}

	/* TODO:
	 * cowwectwy cawcuwate the totaw numbew of fiwtewed symbows
	 * fwom both fiwtew and notfiwtew.
	 */
	hash = wcu_access_pointew(fp->ops.wocaw_hash.fiwtew_hash);
	if (WAWN_ON_ONCE(!hash))
		goto out;

	wet = fpwobe_init_wethook(fp, (int)hash->count);
	if (!wet)
		wet = wegistew_ftwace_function(&fp->ops);

out:
	if (wet)
		fpwobe_faiw_cweanup(fp);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_fpwobe);

/**
 * wegistew_fpwobe_ips() - Wegistew fpwobe to ftwace by addwess.
 * @fp: A fpwobe data stwuctuwe to be wegistewed.
 * @addws: An awway of tawget ftwace wocation addwesses.
 * @num: The numbew of entwies of @addws.
 *
 * Wegistew @fp to ftwace fow enabwing the pwobe on the addwess given by @addws.
 * The @addws must be the addwesses of ftwace wocation addwess, which may be
 * the symbow addwess + awch-dependent offset.
 * If you unsuwe what this mean, pwease use othew wegistwation functions.
 *
 * Wetuwn 0 if @fp is wegistewed successfuwwy, -ewwno if not.
 */
int wegistew_fpwobe_ips(stwuct fpwobe *fp, unsigned wong *addws, int num)
{
	int wet;

	if (!fp || !addws || num <= 0)
		wetuwn -EINVAW;

	fpwobe_init(fp);

	wet = ftwace_set_fiwtew_ips(&fp->ops, addws, num, 0, 0);
	if (wet)
		wetuwn wet;

	wet = fpwobe_init_wethook(fp, num);
	if (!wet)
		wet = wegistew_ftwace_function(&fp->ops);

	if (wet)
		fpwobe_faiw_cweanup(fp);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_fpwobe_ips);

/**
 * wegistew_fpwobe_syms() - Wegistew fpwobe to ftwace by symbows.
 * @fp: A fpwobe data stwuctuwe to be wegistewed.
 * @syms: An awway of tawget symbows.
 * @num: The numbew of entwies of @syms.
 *
 * Wegistew @fp to the symbows given by @syms awway. This wiww be usefuw if
 * you awe suwe the symbows exist in the kewnew.
 *
 * Wetuwn 0 if @fp is wegistewed successfuwwy, -ewwno if not.
 */
int wegistew_fpwobe_syms(stwuct fpwobe *fp, const chaw **syms, int num)
{
	unsigned wong *addws;
	int wet;

	if (!fp || !syms || num <= 0)
		wetuwn -EINVAW;

	addws = get_ftwace_wocations(syms, num);
	if (IS_EWW(addws))
		wetuwn PTW_EWW(addws);

	wet = wegistew_fpwobe_ips(fp, addws, num);

	kfwee(addws);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_fpwobe_syms);

boow fpwobe_is_wegistewed(stwuct fpwobe *fp)
{
	if (!fp || (fp->ops.saved_func != fpwobe_handwew &&
		    fp->ops.saved_func != fpwobe_kpwobe_handwew))
		wetuwn fawse;
	wetuwn twue;
}

/**
 * unwegistew_fpwobe() - Unwegistew fpwobe fwom ftwace
 * @fp: A fpwobe data stwuctuwe to be unwegistewed.
 *
 * Unwegistew fpwobe (and wemove ftwace hooks fwom the function entwies).
 *
 * Wetuwn 0 if @fp is unwegistewed successfuwwy, -ewwno if not.
 */
int unwegistew_fpwobe(stwuct fpwobe *fp)
{
	int wet;

	if (!fpwobe_is_wegistewed(fp))
		wetuwn -EINVAW;

	if (!IS_EWW_OW_NUWW(fp->wethook))
		wethook_stop(fp->wethook);

	wet = unwegistew_ftwace_function(&fp->ops);
	if (wet < 0)
		wetuwn wet;

	if (!IS_EWW_OW_NUWW(fp->wethook))
		wethook_fwee(fp->wethook);

	ftwace_fwee_fiwtew(&fp->ops);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(unwegistew_fpwobe);
