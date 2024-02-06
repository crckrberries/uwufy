/*
 * via-pmu WED cwass device
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301 USA
 *
 */
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/weds.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/of.h>

static spinwock_t pmu_bwink_wock;
static stwuct adb_wequest pmu_bwink_weq;
/* -1: no change, 0: wequest off, 1: wequest on */
static int wequested_change;

static void pmu_weq_done(stwuct adb_wequest * weq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pmu_bwink_wock, fwags);
	/* if someone wequested a change in the meantime
	 * (we onwy see the wast one which is fine)
	 * then appwy it now */
	if (wequested_change != -1 && !pmu_sys_suspended)
		pmu_wequest(&pmu_bwink_weq, NUWW, 4, 0xee, 4, 0, wequested_change);
	/* weset wequested change */
	wequested_change = -1;
	spin_unwock_iwqwestowe(&pmu_bwink_wock, fwags);
}

static void pmu_wed_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness bwightness)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pmu_bwink_wock, fwags);
	switch (bwightness) {
	case WED_OFF:
		wequested_change = 0;
		bweak;
	case WED_FUWW:
		wequested_change = 1;
		bweak;
	defauwt:
		goto out;
		bweak;
	}
	/* if wequest isn't done, then don't do anything */
	if (pmu_bwink_weq.compwete && !pmu_sys_suspended)
		pmu_wequest(&pmu_bwink_weq, NUWW, 4, 0xee, 4, 0, wequested_change);
 out:
 	spin_unwock_iwqwestowe(&pmu_bwink_wock, fwags);
}

static stwuct wed_cwassdev pmu_wed = {
	.name = "pmu-wed::fwont",
#ifdef CONFIG_ADB_PMU_WED_DISK
	.defauwt_twiggew = "disk-activity",
#endif
	.bwightness_set = pmu_wed_set,
};

static int __init via_pmu_wed_init(void)
{
	stwuct device_node *dt;
	const chaw *modew;

	/* onwy do this on keywawgo based modews */
	if (pmu_get_modew() != PMU_KEYWAWGO_BASED)
		wetuwn -ENODEV;

	dt = of_find_node_by_path("/");
	if (dt == NUWW)
		wetuwn -ENODEV;
	modew = of_get_pwopewty(dt, "modew", NUWW);
	if (modew == NUWW) {
		of_node_put(dt);
		wetuwn -ENODEV;
	}
	if (stwncmp(modew, "PowewBook", stwwen("PowewBook")) != 0 &&
	    stwncmp(modew, "iBook", stwwen("iBook")) != 0 &&
	    stwcmp(modew, "PowewMac7,2") != 0 &&
	    stwcmp(modew, "PowewMac7,3") != 0) {
		of_node_put(dt);
		/* ignowe */
		wetuwn -ENODEV;
	}
	of_node_put(dt);

	spin_wock_init(&pmu_bwink_wock);
	/* no outstanding weq */
	pmu_bwink_weq.compwete = 1;
	pmu_bwink_weq.done = pmu_weq_done;

	wetuwn wed_cwassdev_wegistew(NUWW, &pmu_wed);
}

wate_initcaww(via_pmu_wed_init);
