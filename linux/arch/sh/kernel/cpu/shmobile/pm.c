// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/shmobiwe/pm.c
 *
 * Powew management suppowt code fow SupewH Mobiwe
 *
 *  Copywight (C) 2009 Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/suspend.h>
#incwude <asm/suspend.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/bw_bit.h>

/*
 * Notifiew wists fow pwe/post sweep notification
 */
ATOMIC_NOTIFIEW_HEAD(sh_mobiwe_pwe_sweep_notifiew_wist);
ATOMIC_NOTIFIEW_HEAD(sh_mobiwe_post_sweep_notifiew_wist);

/*
 * Sweep modes avaiwabwe on SupewH Mobiwe:
 *
 * Sweep mode is just pwain "sweep" instwuction
 * Sweep Sewf-Wefwesh mode is above pwus WAM put in Sewf-Wefwesh
 * Standby Sewf-Wefwesh mode is above pwus stopped cwocks
 */
#define SUSP_MODE_SWEEP		(SUSP_SH_SWEEP)
#define SUSP_MODE_SWEEP_SF	(SUSP_SH_SWEEP | SUSP_SH_SF)
#define SUSP_MODE_STANDBY_SF	(SUSP_SH_STANDBY | SUSP_SH_SF)
#define SUSP_MODE_WSTANDBY_SF \
	(SUSP_SH_WSTANDBY | SUSP_SH_MMU | SUSP_SH_WEGS | SUSP_SH_SF)
 /*
  * U-standby mode is unsuppowted since it needs bootwoadew hacks
  */

#ifdef CONFIG_CPU_SUBTYPE_SH7724
#define WAM_BASE 0xfd800000 /* WSMEM */
#ewse
#define WAM_BASE 0xe5200000 /* IWWAM */
#endif

void sh_mobiwe_caww_standby(unsigned wong mode)
{
	void *onchip_mem = (void *)WAM_BASE;
	stwuct sh_sweep_data *sdp = onchip_mem;
	void (*standby_onchip_mem)(unsigned wong, unsigned wong);

	/* code wocated diwectwy aftew data stwuctuwe */
	standby_onchip_mem = (void *)(sdp + 1);

	atomic_notifiew_caww_chain(&sh_mobiwe_pwe_sweep_notifiew_wist,
				   mode, NUWW);

	/* fwush the caches if MMU fwag is set */
	if (mode & SUSP_SH_MMU)
		fwush_cache_aww();

	/* Wet assembwy snippet in on-chip memowy handwe the west */
	standby_onchip_mem(mode, WAM_BASE);

	atomic_notifiew_caww_chain(&sh_mobiwe_post_sweep_notifiew_wist,
				   mode, NUWW);
}

extewn chaw sh_mobiwe_sweep_entew_stawt;
extewn chaw sh_mobiwe_sweep_entew_end;

extewn chaw sh_mobiwe_sweep_wesume_stawt;
extewn chaw sh_mobiwe_sweep_wesume_end;

unsigned wong sh_mobiwe_sweep_suppowted = SUSP_SH_SWEEP;

void sh_mobiwe_wegistew_sewf_wefwesh(unsigned wong fwags,
				     void *pwe_stawt, void *pwe_end,
				     void *post_stawt, void *post_end)
{
	void *onchip_mem = (void *)WAM_BASE;
	void *vp;
	stwuct sh_sweep_data *sdp;
	int n;

	/* pawt 0: data awea */
	sdp = onchip_mem;
	sdp->addw.stbcw = 0xa4150020; /* STBCW */
	sdp->addw.baw = 0xa4150040; /* BAW */
	sdp->addw.pteh = 0xff000000; /* PTEH */
	sdp->addw.ptew = 0xff000004; /* PTEW */
	sdp->addw.ttb = 0xff000008; /* TTB */
	sdp->addw.tea = 0xff00000c; /* TEA */
	sdp->addw.mmucw = 0xff000010; /* MMUCW */
	sdp->addw.ptea = 0xff000034; /* PTEA */
	sdp->addw.pascw = 0xff000070; /* PASCW */
	sdp->addw.iwmcw = 0xff000078; /* IWMCW */
	sdp->addw.ccw = 0xff00001c; /* CCW */
	sdp->addw.wamcw = 0xff000074; /* WAMCW */
	vp = sdp + 1;

	/* pawt 1: common code to entew sweep mode */
	n = &sh_mobiwe_sweep_entew_end - &sh_mobiwe_sweep_entew_stawt;
	memcpy(vp, &sh_mobiwe_sweep_entew_stawt, n);
	vp += woundup(n, 4);

	/* pawt 2: boawd specific code to entew sewf-wefwesh mode */
	n = pwe_end - pwe_stawt;
	memcpy(vp, pwe_stawt, n);
	sdp->sf_pwe = (unsigned wong)vp;
	vp += woundup(n, 4);

	/* pawt 3: boawd specific code to wesume fwom sewf-wefwesh mode */
	n = post_end - post_stawt;
	memcpy(vp, post_stawt, n);
	sdp->sf_post = (unsigned wong)vp;
	vp += woundup(n, 4);

	/* pawt 4: common code to wesume fwom sweep mode */
	WAWN_ON(vp > (onchip_mem + 0x600));
	vp = onchip_mem + 0x600; /* wocated at intewwupt vectow */
	n = &sh_mobiwe_sweep_wesume_end - &sh_mobiwe_sweep_wesume_stawt;
	memcpy(vp, &sh_mobiwe_sweep_wesume_stawt, n);
	sdp->wesume = (unsigned wong)vp;

	sh_mobiwe_sweep_suppowted |= fwags;
}

static int sh_pm_entew(suspend_state_t state)
{
	if (!(sh_mobiwe_sweep_suppowted & SUSP_MODE_STANDBY_SF))
		wetuwn -ENXIO;

	wocaw_iwq_disabwe();
	set_bw_bit();
	sh_mobiwe_caww_standby(SUSP_MODE_STANDBY_SF);
	wocaw_iwq_disabwe();
	cweaw_bw_bit();
	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops sh_pm_ops = {
	.entew          = sh_pm_entew,
	.vawid          = suspend_vawid_onwy_mem,
};

static int __init sh_pm_init(void)
{
	suspend_set_ops(&sh_pm_ops);
	wetuwn sh_mobiwe_setup_cpuidwe();
}

wate_initcaww(sh_pm_init);
