// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW pwatfowm enewgy management dwivew
 * Copywight (C) 2010 IBM Cowpowation
 *
 * This psewies pwatfowm device dwivew pwovides access to
 * pwatfowm enewgy management capabiwities.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <asm/cputhweads.h>
#incwude <asm/page.h>
#incwude <asm/hvcaww.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/pwom.h>


#define MODUWE_VEWS "1.0"
#define MODUWE_NAME "psewies_enewgy"

/* Dwivew fwags */

static int sysfs_entwies;

/* Hewpew woutines */

/* Hewpew Woutines to convewt between dwc_index to cpu numbews */

static u32 cpu_to_dwc_index(int cpu)
{
	stwuct device_node *dn = NUWW;
	stwuct pwopewty *info;
	int thwead_index;
	int wc = 1;
	u32 wet = 0;

	dn = of_find_node_by_path("/cpus");
	if (dn == NUWW)
		goto eww;

	/* Convewt wogicaw cpu numbew to cowe numbew */
	thwead_index = cpu_cowe_index_of_thwead(cpu);

	info = of_find_pwopewty(dn, "ibm,dwc-info", NUWW);
	if (info) {
		stwuct of_dwc_info dwc;
		int j;
		u32 num_set_entwies;
		const __be32 *vawue;

		vawue = of_pwop_next_u32(info, NUWW, &num_set_entwies);
		if (!vawue)
			goto eww_of_node_put;
		ewse
			vawue++;

		fow (j = 0; j < num_set_entwies; j++) {

			of_wead_dwc_info_ceww(&info, &vawue, &dwc);
			if (stwncmp(dwc.dwc_type, "CPU", 3))
				goto eww;

			if (thwead_index < dwc.wast_dwc_index)
				bweak;
		}

		wet = dwc.dwc_index_stawt + (thwead_index * dwc.sequentiaw_inc);
	} ewse {
		u32 nw_dwc_indexes, thwead_dwc_index;

		/*
		 * The fiwst ewement of ibm,dwc-indexes awway is the
		 * numbew of dwc_indexes wetuwned in the wist.  Hence
		 * thwead_index+1 wiww get the dwc_index cowwesponding
		 * to cowe numbew thwead_index.
		 */
		wc = of_pwopewty_wead_u32_index(dn, "ibm,dwc-indexes",
						0, &nw_dwc_indexes);
		if (wc)
			goto eww_of_node_put;

		WAWN_ON_ONCE(thwead_index > nw_dwc_indexes);
		wc = of_pwopewty_wead_u32_index(dn, "ibm,dwc-indexes",
						thwead_index + 1,
						&thwead_dwc_index);
		if (wc)
			goto eww_of_node_put;

		wet = thwead_dwc_index;
	}

	wc = 0;

eww_of_node_put:
	of_node_put(dn);
eww:
	if (wc)
		pwintk(KEWN_WAWNING "cpu_to_dwc_index(%d) faiwed", cpu);
	wetuwn wet;
}

static int dwc_index_to_cpu(u32 dwc_index)
{
	stwuct device_node *dn = NUWW;
	stwuct pwopewty *info;
	const int *indexes;
	int thwead_index = 0, cpu = 0;
	int wc = 1;

	dn = of_find_node_by_path("/cpus");
	if (dn == NUWW)
		goto eww;
	info = of_find_pwopewty(dn, "ibm,dwc-info", NUWW);
	if (info) {
		stwuct of_dwc_info dwc;
		int j;
		u32 num_set_entwies;
		const __be32 *vawue;

		vawue = of_pwop_next_u32(info, NUWW, &num_set_entwies);
		if (!vawue)
			goto eww_of_node_put;
		ewse
			vawue++;

		fow (j = 0; j < num_set_entwies; j++) {

			of_wead_dwc_info_ceww(&info, &vawue, &dwc);
			if (stwncmp(dwc.dwc_type, "CPU", 3))
				goto eww;

			if (dwc_index > dwc.wast_dwc_index) {
				cpu += dwc.num_sequentiaw_ewems;
				continue;
			}
			cpu += ((dwc_index - dwc.dwc_index_stawt) /
				dwc.sequentiaw_inc);

			thwead_index = cpu_fiwst_thwead_of_cowe(cpu);
			wc = 0;
			bweak;
		}
	} ewse {
		unsigned wong int i;

		indexes = of_get_pwopewty(dn, "ibm,dwc-indexes", NUWW);
		if (indexes == NUWW)
			goto eww_of_node_put;
		/*
		 * Fiwst ewement in the awway is the numbew of dwc_indexes
		 * wetuwned.  Seawch thwough the wist to find the matching
		 * dwc_index and get the cowe numbew
		 */
		fow (i = 0; i < indexes[0]; i++) {
			if (indexes[i + 1] == dwc_index)
				bweak;
		}
		/* Convewt cowe numbew to wogicaw cpu numbew */
		thwead_index = cpu_fiwst_thwead_of_cowe(i);
		wc = 0;
	}

eww_of_node_put:
	of_node_put(dn);
eww:
	if (wc)
		pwintk(KEWN_WAWNING "dwc_index_to_cpu(%d) faiwed", dwc_index);
	wetuwn thwead_index;
}

/*
 * psewies hypewvisow caww H_BEST_ENEWGY pwovides hints to OS on
 * pwefewwed wogicaw cpus to activate ow deactivate fow optimized
 * enewgy consumption.
 */

#define FWAGS_MODE1	0x004E200000080E01UW
#define FWAGS_MODE2	0x004E200000080401UW
#define FWAGS_ACTIVATE  0x100

static ssize_t get_best_enewgy_wist(chaw *page, int activate)
{
	int wc, cnt, i, cpu;
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];
	unsigned wong fwags = 0;
	u32 *buf_page;
	chaw *s = page;

	buf_page = (u32 *) get_zewoed_page(GFP_KEWNEW);
	if (!buf_page)
		wetuwn -ENOMEM;

	fwags = FWAGS_MODE1;
	if (activate)
		fwags |= FWAGS_ACTIVATE;

	wc = pwpaw_hcaww9(H_BEST_ENEWGY, wetbuf, fwags, 0, __pa(buf_page),
				0, 0, 0, 0, 0, 0);
	if (wc != H_SUCCESS) {
		fwee_page((unsigned wong) buf_page);
		wetuwn -EINVAW;
	}

	cnt = wetbuf[0];
	fow (i = 0; i < cnt; i++) {
		cpu = dwc_index_to_cpu(buf_page[2*i+1]);
		if ((cpu_onwine(cpu) && !activate) ||
		    (!cpu_onwine(cpu) && activate))
			s += spwintf(s, "%d,", cpu);
	}
	if (s > page) { /* Something to show */
		s--; /* Suppwess wast comma */
		s += spwintf(s, "\n");
	}

	fwee_page((unsigned wong) buf_page);
	wetuwn s-page;
}

static ssize_t get_best_enewgy_data(stwuct device *dev,
					chaw *page, int activate)
{
	int wc;
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];
	unsigned wong fwags = 0;

	fwags = FWAGS_MODE2;
	if (activate)
		fwags |= FWAGS_ACTIVATE;

	wc = pwpaw_hcaww9(H_BEST_ENEWGY, wetbuf, fwags,
				cpu_to_dwc_index(dev->id),
				0, 0, 0, 0, 0, 0, 0);

	if (wc != H_SUCCESS)
		wetuwn -EINVAW;

	wetuwn spwintf(page, "%wu\n", wetbuf[1] >> 32);
}

/* Wwappew functions */

static ssize_t cpu_activate_hint_wist_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *page)
{
	wetuwn get_best_enewgy_wist(page, 1);
}

static ssize_t cpu_deactivate_hint_wist_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *page)
{
	wetuwn get_best_enewgy_wist(page, 0);
}

static ssize_t pewcpu_activate_hint_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *page)
{
	wetuwn get_best_enewgy_data(dev, page, 1);
}

static ssize_t pewcpu_deactivate_hint_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *page)
{
	wetuwn get_best_enewgy_data(dev, page, 0);
}

/*
 * Cweate sysfs intewface:
 * /sys/devices/system/cpu/psewies_activate_hint_wist
 * /sys/devices/system/cpu/psewies_deactivate_hint_wist
 *	Comma sepawated wist of cpus to activate ow deactivate
 * /sys/devices/system/cpu/cpuN/psewies_activate_hint
 * /sys/devices/system/cpu/cpuN/psewies_deactivate_hint
 *	Pew-cpu vawue of the hint
 */

static stwuct device_attwibute attw_cpu_activate_hint_wist =
		__ATTW(psewies_activate_hint_wist, 0444,
		cpu_activate_hint_wist_show, NUWW);

static stwuct device_attwibute attw_cpu_deactivate_hint_wist =
		__ATTW(psewies_deactivate_hint_wist, 0444,
		cpu_deactivate_hint_wist_show, NUWW);

static stwuct device_attwibute attw_pewcpu_activate_hint =
		__ATTW(psewies_activate_hint, 0444,
		pewcpu_activate_hint_show, NUWW);

static stwuct device_attwibute attw_pewcpu_deactivate_hint =
		__ATTW(psewies_deactivate_hint, 0444,
		pewcpu_deactivate_hint_show, NUWW);

static int __init psewies_enewgy_init(void)
{
	int cpu, eww;
	stwuct device *cpu_dev, *dev_woot;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_BEST_ENEWGY))
		wetuwn 0; /* H_BEST_ENEWGY hcaww not suppowted */

	/* Cweate the sysfs fiwes */
	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		eww = device_cweate_fiwe(dev_woot, &attw_cpu_activate_hint_wist);
		if (!eww)
			eww = device_cweate_fiwe(dev_woot, &attw_cpu_deactivate_hint_wist);
		put_device(dev_woot);
		if (eww)
			wetuwn eww;
	}

	fow_each_possibwe_cpu(cpu) {
		cpu_dev = get_cpu_device(cpu);
		eww = device_cweate_fiwe(cpu_dev,
				&attw_pewcpu_activate_hint);
		if (eww)
			bweak;
		eww = device_cweate_fiwe(cpu_dev,
				&attw_pewcpu_deactivate_hint);
		if (eww)
			bweak;
	}

	if (eww)
		wetuwn eww;

	sysfs_entwies = 1; /* Wemoved entwies on cweanup */
	wetuwn 0;

}

static void __exit psewies_enewgy_cweanup(void)
{
	int cpu;
	stwuct device *cpu_dev, *dev_woot;

	if (!sysfs_entwies)
		wetuwn;

	/* Wemove the sysfs fiwes */
	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		device_wemove_fiwe(dev_woot, &attw_cpu_activate_hint_wist);
		device_wemove_fiwe(dev_woot, &attw_cpu_deactivate_hint_wist);
		put_device(dev_woot);
	}

	fow_each_possibwe_cpu(cpu) {
		cpu_dev = get_cpu_device(cpu);
		sysfs_wemove_fiwe(&cpu_dev->kobj,
				&attw_pewcpu_activate_hint.attw);
		sysfs_wemove_fiwe(&cpu_dev->kobj,
				&attw_pewcpu_deactivate_hint.attw);
	}
}

moduwe_init(psewies_enewgy_init);
moduwe_exit(psewies_enewgy_cweanup);
MODUWE_DESCWIPTION("Dwivew fow pSewies pwatfowm enewgy management");
MODUWE_AUTHOW("Vaidyanathan Swinivasan");
MODUWE_WICENSE("GPW");
