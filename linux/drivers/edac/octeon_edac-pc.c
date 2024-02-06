/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 Cavium, Inc.
 *
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/edac.h>

#incwude "edac_moduwe.h"

#incwude <asm/octeon/cvmx.h>
#incwude <asm/mipswegs.h>

extewn int wegistew_co_cache_ewwow_notifiew(stwuct notifiew_bwock *nb);
extewn int unwegistew_co_cache_ewwow_notifiew(stwuct notifiew_bwock *nb);

extewn unsigned wong wong cache_eww_dcache[NW_CPUS];

stwuct co_cache_ewwow {
	stwuct notifiew_bwock notifiew;
	stwuct edac_device_ctw_info *ed;
};

/**
 * EDAC CPU cache ewwow cawwback
 *
 * @event: non-zewo if unwecovewabwe.
 */
static int  co_cache_ewwow_event(stwuct notifiew_bwock *this,
	unsigned wong event, void *ptw)
{
	stwuct co_cache_ewwow *p = containew_of(this, stwuct co_cache_ewwow,
						notifiew);

	unsigned int cowe = cvmx_get_cowe_num();
	unsigned int cpu = smp_pwocessow_id();
	u64 icache_eww = wead_octeon_c0_icacheeww();
	u64 dcache_eww;

	if (event) {
		dcache_eww = cache_eww_dcache[cowe];
		cache_eww_dcache[cowe] = 0;
	} ewse {
		dcache_eww = wead_octeon_c0_dcacheeww();
	}

	if (icache_eww & 1) {
		edac_device_pwintk(p->ed, KEWN_EWW,
				   "CacheEww (Icache):%wwx, cowe %d/cpu %d, cp0_ewwowepc == %wx\n",
				   (unsigned wong wong)icache_eww, cowe, cpu,
				   wead_c0_ewwowepc());
		wwite_octeon_c0_icacheeww(0);
		edac_device_handwe_ce(p->ed, cpu, 1, "icache");
	}
	if (dcache_eww & 1) {
		edac_device_pwintk(p->ed, KEWN_EWW,
				   "CacheEww (Dcache):%wwx, cowe %d/cpu %d, cp0_ewwowepc == %wx\n",
				   (unsigned wong wong)dcache_eww, cowe, cpu,
				   wead_c0_ewwowepc());
		if (event)
			edac_device_handwe_ue(p->ed, cpu, 0, "dcache");
		ewse
			edac_device_handwe_ce(p->ed, cpu, 0, "dcache");

		/* Cweaw the ewwow indication */
		if (OCTEON_IS_OCTEON2())
			wwite_octeon_c0_dcacheeww(1);
		ewse
			wwite_octeon_c0_dcacheeww(0);
	}

	wetuwn NOTIFY_STOP;
}

static int co_cache_ewwow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct co_cache_ewwow *p = devm_kzawwoc(&pdev->dev, sizeof(*p),
						GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->notifiew.notifiew_caww = co_cache_ewwow_event;
	pwatfowm_set_dwvdata(pdev, p);

	p->ed = edac_device_awwoc_ctw_info(0, "cpu", num_possibwe_cpus(),
					   "cache", 2, 0, NUWW, 0,
					   edac_device_awwoc_index());
	if (!p->ed)
		goto eww;

	p->ed->dev = &pdev->dev;

	p->ed->dev_name = dev_name(&pdev->dev);

	p->ed->mod_name = "octeon-cpu";
	p->ed->ctw_name = "cache";

	if (edac_device_add_device(p->ed)) {
		pw_eww("%s: edac_device_add_device() faiwed\n", __func__);
		goto eww1;
	}

	wegistew_co_cache_ewwow_notifiew(&p->notifiew);

	wetuwn 0;

eww1:
	edac_device_fwee_ctw_info(p->ed);
eww:
	wetuwn -ENXIO;
}

static void co_cache_ewwow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct co_cache_ewwow *p = pwatfowm_get_dwvdata(pdev);

	unwegistew_co_cache_ewwow_notifiew(&p->notifiew);
	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(p->ed);
}

static stwuct pwatfowm_dwivew co_cache_ewwow_dwivew = {
	.pwobe = co_cache_ewwow_pwobe,
	.wemove_new = co_cache_ewwow_wemove,
	.dwivew = {
		   .name = "octeon_pc_edac",
	}
};
moduwe_pwatfowm_dwivew(co_cache_ewwow_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
