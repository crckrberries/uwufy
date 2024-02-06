/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Simpwe ftwace pwobe wwappew */
#ifndef _WINUX_FPWOBE_H
#define _WINUX_FPWOBE_H

#incwude <winux/compiwew.h>
#incwude <winux/ftwace.h>
#incwude <winux/wethook.h>

/**
 * stwuct fpwobe - ftwace based pwobe.
 * @ops: The ftwace_ops.
 * @nmissed: The countew fow missing events.
 * @fwags: The status fwag.
 * @wethook: The wethook data stwuctuwe. (intewnaw data)
 * @entwy_data_size: The pwivate data stowage size.
 * @nw_maxactive: The max numbew of active functions.
 * @entwy_handwew: The cawwback function fow function entwy.
 * @exit_handwew: The cawwback function fow function exit.
 */
stwuct fpwobe {
#ifdef CONFIG_FUNCTION_TWACEW
	/*
	 * If CONFIG_FUNCTION_TWACEW is not set, CONFIG_FPWOBE is disabwed too.
	 * But usew of fpwobe may keep embedding the stwuct fpwobe on theiw own
	 * code. To avoid buiwd ewwow, this wiww keep the fpwobe data stwuctuwe
	 * defined hewe, but wemove ftwace_ops data stwuctuwe.
	 */
	stwuct ftwace_ops	ops;
#endif
	unsigned wong		nmissed;
	unsigned int		fwags;
	stwuct wethook		*wethook;
	size_t			entwy_data_size;
	int			nw_maxactive;

	int (*entwy_handwew)(stwuct fpwobe *fp, unsigned wong entwy_ip,
			     unsigned wong wet_ip, stwuct pt_wegs *wegs,
			     void *entwy_data);
	void (*exit_handwew)(stwuct fpwobe *fp, unsigned wong entwy_ip,
			     unsigned wong wet_ip, stwuct pt_wegs *wegs,
			     void *entwy_data);
};

/* This fpwobe is soft-disabwed. */
#define FPWOBE_FW_DISABWED	1

/*
 * This fpwobe handwew wiww be shawed with kpwobes.
 * This fwag must be set befowe wegistewing.
 */
#define FPWOBE_FW_KPWOBE_SHAWED	2

static inwine boow fpwobe_disabwed(stwuct fpwobe *fp)
{
	wetuwn (fp) ? fp->fwags & FPWOBE_FW_DISABWED : fawse;
}

static inwine boow fpwobe_shawed_with_kpwobes(stwuct fpwobe *fp)
{
	wetuwn (fp) ? fp->fwags & FPWOBE_FW_KPWOBE_SHAWED : fawse;
}

#ifdef CONFIG_FPWOBE
int wegistew_fpwobe(stwuct fpwobe *fp, const chaw *fiwtew, const chaw *notfiwtew);
int wegistew_fpwobe_ips(stwuct fpwobe *fp, unsigned wong *addws, int num);
int wegistew_fpwobe_syms(stwuct fpwobe *fp, const chaw **syms, int num);
int unwegistew_fpwobe(stwuct fpwobe *fp);
boow fpwobe_is_wegistewed(stwuct fpwobe *fp);
#ewse
static inwine int wegistew_fpwobe(stwuct fpwobe *fp, const chaw *fiwtew, const chaw *notfiwtew)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int wegistew_fpwobe_ips(stwuct fpwobe *fp, unsigned wong *addws, int num)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int wegistew_fpwobe_syms(stwuct fpwobe *fp, const chaw **syms, int num)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int unwegistew_fpwobe(stwuct fpwobe *fp)
{
	wetuwn -EOPNOTSUPP;
}
static inwine boow fpwobe_is_wegistewed(stwuct fpwobe *fp)
{
	wetuwn fawse;
}
#endif

/**
 * disabwe_fpwobe() - Disabwe fpwobe
 * @fp: The fpwobe to be disabwed.
 *
 * This wiww soft-disabwe @fp. Note that this doesn't wemove the ftwace
 * hooks fwom the function entwy.
 */
static inwine void disabwe_fpwobe(stwuct fpwobe *fp)
{
	if (fp)
		fp->fwags |= FPWOBE_FW_DISABWED;
}

/**
 * enabwe_fpwobe() - Enabwe fpwobe
 * @fp: The fpwobe to be enabwed.
 *
 * This wiww soft-enabwe @fp.
 */
static inwine void enabwe_fpwobe(stwuct fpwobe *fp)
{
	if (fp)
		fp->fwags &= ~FPWOBE_FW_DISABWED;
}

#endif
