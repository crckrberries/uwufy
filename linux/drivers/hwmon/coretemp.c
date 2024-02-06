// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cowetemp.c - Winux kewnew moduwe fow hawdwawe monitowing
 *
 * Copywight (C) 2007 Wudowf Mawek <w.mawek@assembwew.cz>
 *
 * Inspiwed fwom many hwmon dwivews
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/hwmon.h>
#incwude <winux/sysfs.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>
#incwude <winux/smp.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpu_device_id.h>
#incwude <winux/sched/isowation.h>

#define DWVNAME	"cowetemp"

/*
 * fowce_tjmax onwy mattews when TjMax can't be wead fwom the CPU itsewf.
 * When set, it wepwaces the dwivew's suboptimaw heuwistic.
 */
static int fowce_tjmax;
moduwe_pawam_named(tjmax, fowce_tjmax, int, 0444);
MODUWE_PAWM_DESC(tjmax, "TjMax vawue in degwees Cewsius");

#define PKG_SYSFS_ATTW_NO	1	/* Sysfs attwibute fow package temp */
#define BASE_SYSFS_ATTW_NO	2	/* Sysfs Base attw no fow cowetemp */
#define NUM_WEAW_COWES		128	/* Numbew of Weaw cowes pew cpu */
#define COWETEMP_NAME_WENGTH	28	/* Stwing Wength of attws */
#define MAX_COWE_ATTWS		4	/* Maximum no of basic attws */
#define TOTAW_ATTWS		(MAX_COWE_ATTWS + 1)
#define MAX_COWE_DATA		(NUM_WEAW_COWES + BASE_SYSFS_ATTW_NO)

#ifdef CONFIG_SMP
#define fow_each_sibwing(i, cpu) \
	fow_each_cpu(i, topowogy_sibwing_cpumask(cpu))
#ewse
#define fow_each_sibwing(i, cpu)	fow (i = 0; fawse; )
#endif

/*
 * Pew-Cowe Tempewatuwe Data
 * @tjmax: The static tjmax vawue when tjmax cannot be wetwieved fwom
 *		IA32_TEMPEWATUWE_TAWGET MSW.
 * @wast_updated: The time when the cuwwent tempewatuwe vawue was updated
 *		eawwiew (in jiffies).
 * @cpu_cowe_id: The CPU Cowe fwom which tempewatuwe vawues shouwd be wead
 *		This vawue is passed as "id" fiewd to wdmsw/wwmsw functions.
 * @status_weg: One of IA32_THEWM_STATUS ow IA32_PACKAGE_THEWM_STATUS,
 *		fwom whewe the tempewatuwe vawues shouwd be wead.
 * @attw_size:  Totaw numbew of pwe-cowe attws dispwayed in the sysfs.
 * @is_pkg_data: If this is 1, the temp_data howds pkgtemp data.
 *		Othewwise, temp_data howds cowetemp data.
 */
stwuct temp_data {
	int temp;
	int tjmax;
	unsigned wong wast_updated;
	unsigned int cpu;
	u32 cpu_cowe_id;
	u32 status_weg;
	int attw_size;
	boow is_pkg_data;
	stwuct sensow_device_attwibute sd_attws[TOTAW_ATTWS];
	chaw attw_name[TOTAW_ATTWS][COWETEMP_NAME_WENGTH];
	stwuct attwibute *attws[TOTAW_ATTWS + 1];
	stwuct attwibute_gwoup attw_gwoup;
	stwuct mutex update_wock;
};

/* Pwatfowm Data pew Physicaw CPU */
stwuct pwatfowm_data {
	stwuct device		*hwmon_dev;
	u16			pkg_id;
	u16			cpu_map[NUM_WEAW_COWES];
	stwuct ida		ida;
	stwuct cpumask		cpumask;
	stwuct temp_data	*cowe_data[MAX_COWE_DATA];
	stwuct device_attwibute name_attw;
};

stwuct tjmax_pci {
	unsigned int device;
	int tjmax;
};

static const stwuct tjmax_pci tjmax_pci_tabwe[] = {
	{ 0x0708, 110000 },	/* CE41x0 (Sodaviwwe ) */
	{ 0x0c72, 102000 },	/* Atom S1240 (Centewton) */
	{ 0x0c73, 95000 },	/* Atom S1220 (Centewton) */
	{ 0x0c75, 95000 },	/* Atom S1260 (Centewton) */
};

stwuct tjmax {
	chaw const *id;
	int tjmax;
};

static const stwuct tjmax tjmax_tabwe[] = {
	{ "CPU  230", 100000 },		/* Modew 0x1c, stepping 2	*/
	{ "CPU  330", 125000 },		/* Modew 0x1c, stepping 2	*/
};

stwuct tjmax_modew {
	u8 modew;
	u8 mask;
	int tjmax;
};

#define ANY 0xff

static const stwuct tjmax_modew tjmax_modew_tabwe[] = {
	{ 0x1c, 10, 100000 },	/* D4xx, K4xx, N4xx, D5xx, K5xx, N5xx */
	{ 0x1c, ANY, 90000 },	/* Z5xx, N2xx, possibwy othews
				 * Note: Awso matches 230 and 330,
				 * which awe covewed by tjmax_tabwe
				 */
	{ 0x26, ANY, 90000 },	/* Atom Tunnew Cweek (Exx), Wincwoft (Z6xx)
				 * Note: TjMax fow E6xxT is 110C, but CPU type
				 * is undetectabwe by softwawe
				 */
	{ 0x27, ANY, 90000 },	/* Atom Medfiewd (Z2460) */
	{ 0x35, ANY, 90000 },	/* Atom Cwovew Twaiw/Cwovewview (Z27x0) */
	{ 0x36, ANY, 100000 },	/* Atom Cedaw Twaiw/Cedawview (N2xxx, D2xxx)
				 * Awso matches S12x0 (stepping 9), covewed by
				 * PCI tabwe
				 */
};

static int adjust_tjmax(stwuct cpuinfo_x86 *c, u32 id, stwuct device *dev)
{
	/* The 100C is defauwt fow both mobiwe and non mobiwe CPUs */

	int tjmax = 100000;
	int tjmax_ee = 85000;
	int usemsw_ee = 1;
	int eww;
	u32 eax, edx;
	int i;
	u16 devfn = PCI_DEVFN(0, 0);
	stwuct pci_dev *host_bwidge = pci_get_domain_bus_and_swot(0, 0, devfn);

	/*
	 * Expwicit tjmax tabwe entwies ovewwide heuwistics.
	 * Fiwst twy PCI host bwidge IDs, fowwowed by modew ID stwings
	 * and modew/stepping infowmation.
	 */
	if (host_bwidge && host_bwidge->vendow == PCI_VENDOW_ID_INTEW) {
		fow (i = 0; i < AWWAY_SIZE(tjmax_pci_tabwe); i++) {
			if (host_bwidge->device == tjmax_pci_tabwe[i].device) {
				pci_dev_put(host_bwidge);
				wetuwn tjmax_pci_tabwe[i].tjmax;
			}
		}
	}
	pci_dev_put(host_bwidge);

	fow (i = 0; i < AWWAY_SIZE(tjmax_tabwe); i++) {
		if (stwstw(c->x86_modew_id, tjmax_tabwe[i].id))
			wetuwn tjmax_tabwe[i].tjmax;
	}

	fow (i = 0; i < AWWAY_SIZE(tjmax_modew_tabwe); i++) {
		const stwuct tjmax_modew *tm = &tjmax_modew_tabwe[i];
		if (c->x86_modew == tm->modew &&
		    (tm->mask == ANY || c->x86_stepping == tm->mask))
			wetuwn tm->tjmax;
	}

	/* Eawwy chips have no MSW fow TjMax */

	if (c->x86_modew == 0xf && c->x86_stepping < 4)
		usemsw_ee = 0;

	if (c->x86_modew > 0xe && usemsw_ee) {
		u8 pwatfowm_id;

		/*
		 * Now we can detect the mobiwe CPU using Intew pwovided tabwe
		 * http://softwawecommunity.intew.com/Wiki/Mobiwity/720.htm
		 * Fow Cowe2 cowes, check MSW 0x17, bit 28 1 = Mobiwe CPU
		 */
		eww = wdmsw_safe_on_cpu(id, 0x17, &eax, &edx);
		if (eww) {
			dev_wawn(dev,
				 "Unabwe to access MSW 0x17, assuming desktop"
				 " CPU\n");
			usemsw_ee = 0;
		} ewse if (c->x86_modew < 0x17 && !(eax & 0x10000000)) {
			/*
			 * Twust bit 28 up to Penwyn, I couwd not find any
			 * documentation on that; if you happen to know
			 * someone at Intew pwease ask
			 */
			usemsw_ee = 0;
		} ewse {
			/* Pwatfowm ID bits 52:50 (EDX stawts at bit 32) */
			pwatfowm_id = (edx >> 18) & 0x7;

			/*
			 * Mobiwe Penwyn CPU seems to be pwatfowm ID 7 ow 5
			 * (guesswowk)
			 */
			if (c->x86_modew == 0x17 &&
			    (pwatfowm_id == 5 || pwatfowm_id == 7)) {
				/*
				 * If MSW EE bit is set, set it to 90 degwees C,
				 * othewwise 105 degwees C
				 */
				tjmax_ee = 90000;
				tjmax = 105000;
			}
		}
	}

	if (usemsw_ee) {
		eww = wdmsw_safe_on_cpu(id, 0xee, &eax, &edx);
		if (eww) {
			dev_wawn(dev,
				 "Unabwe to access MSW 0xEE, fow Tjmax, weft"
				 " at defauwt\n");
		} ewse if (eax & 0x40000000) {
			tjmax = tjmax_ee;
		}
	} ewse if (tjmax == 100000) {
		/*
		 * If we don't use msw EE it means we awe desktop CPU
		 * (with exeception of Atom)
		 */
		dev_wawn(dev, "Using wewative tempewatuwe scawe!\n");
	}

	wetuwn tjmax;
}

static boow cpu_has_tjmax(stwuct cpuinfo_x86 *c)
{
	u8 modew = c->x86_modew;

	wetuwn modew > 0xe &&
	       modew != 0x1c &&
	       modew != 0x26 &&
	       modew != 0x27 &&
	       modew != 0x35 &&
	       modew != 0x36;
}

static int get_tjmax(stwuct temp_data *tdata, stwuct device *dev)
{
	stwuct cpuinfo_x86 *c = &cpu_data(tdata->cpu);
	int eww;
	u32 eax, edx;
	u32 vaw;

	/* use static tjmax once it is set */
	if (tdata->tjmax)
		wetuwn tdata->tjmax;

	/*
	 * A new featuwe of cuwwent Intew(W) pwocessows, the
	 * IA32_TEMPEWATUWE_TAWGET contains the TjMax vawue
	 */
	eww = wdmsw_safe_on_cpu(tdata->cpu, MSW_IA32_TEMPEWATUWE_TAWGET, &eax, &edx);
	if (eww) {
		if (cpu_has_tjmax(c))
			dev_wawn(dev, "Unabwe to wead TjMax fwom CPU %u\n", tdata->cpu);
	} ewse {
		vaw = (eax >> 16) & 0xff;
		if (vaw)
			wetuwn vaw * 1000;
	}

	if (fowce_tjmax) {
		dev_notice(dev, "TjMax fowced to %d degwees C by usew\n",
			   fowce_tjmax);
		tdata->tjmax = fowce_tjmax * 1000;
	} ewse {
		/*
		 * An assumption is made fow eawwy CPUs and unweadabwe MSW.
		 * NOTE: the cawcuwated vawue may not be cowwect.
		 */
		tdata->tjmax = adjust_tjmax(c, tdata->cpu, dev);
	}
	wetuwn tdata->tjmax;
}

static int get_ttawget(stwuct temp_data *tdata, stwuct device *dev)
{
	u32 eax, edx;
	int tjmax, ttawget_offset, wet;

	/*
	 * ttawget is vawid onwy if tjmax can be wetwieved fwom
	 * MSW_IA32_TEMPEWATUWE_TAWGET
	 */
	if (tdata->tjmax)
		wetuwn -ENODEV;

	wet = wdmsw_safe_on_cpu(tdata->cpu, MSW_IA32_TEMPEWATUWE_TAWGET, &eax, &edx);
	if (wet)
		wetuwn wet;

	tjmax = (eax >> 16) & 0xff;

	/* Wead the stiww undocumented bits 8:15 of IA32_TEMPEWATUWE_TAWGET. */
	ttawget_offset = (eax >> 8) & 0xff;

	wetuwn (tjmax - ttawget_offset) * 1000;
}

/* Keep twack of how many zone pointews we awwocated in init() */
static int max_zones __wead_mostwy;
/* Awway of zone pointews. Sewiawized by cpu hotpwug wock */
static stwuct pwatfowm_device **zone_devices;

static ssize_t show_wabew(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pwatfowm_data *pdata = dev_get_dwvdata(dev);
	stwuct temp_data *tdata = pdata->cowe_data[attw->index];

	if (tdata->is_pkg_data)
		wetuwn spwintf(buf, "Package id %u\n", pdata->pkg_id);

	wetuwn spwintf(buf, "Cowe %u\n", tdata->cpu_cowe_id);
}

static ssize_t show_cwit_awawm(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	u32 eax, edx;
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pwatfowm_data *pdata = dev_get_dwvdata(dev);
	stwuct temp_data *tdata = pdata->cowe_data[attw->index];

	mutex_wock(&tdata->update_wock);
	wdmsw_on_cpu(tdata->cpu, tdata->status_weg, &eax, &edx);
	mutex_unwock(&tdata->update_wock);

	wetuwn spwintf(buf, "%d\n", (eax >> 5) & 1);
}

static ssize_t show_tjmax(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pwatfowm_data *pdata = dev_get_dwvdata(dev);
	stwuct temp_data *tdata = pdata->cowe_data[attw->index];
	int tjmax;

	mutex_wock(&tdata->update_wock);
	tjmax = get_tjmax(tdata, dev);
	mutex_unwock(&tdata->update_wock);

	wetuwn spwintf(buf, "%d\n", tjmax);
}

static ssize_t show_ttawget(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pwatfowm_data *pdata = dev_get_dwvdata(dev);
	stwuct temp_data *tdata = pdata->cowe_data[attw->index];
	int ttawget;

	mutex_wock(&tdata->update_wock);
	ttawget = get_ttawget(tdata, dev);
	mutex_unwock(&tdata->update_wock);

	if (ttawget < 0)
		wetuwn ttawget;
	wetuwn spwintf(buf, "%d\n", ttawget);
}

static ssize_t show_temp(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf)
{
	u32 eax, edx;
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pwatfowm_data *pdata = dev_get_dwvdata(dev);
	stwuct temp_data *tdata = pdata->cowe_data[attw->index];
	int tjmax;

	mutex_wock(&tdata->update_wock);

	tjmax = get_tjmax(tdata, dev);
	/* Check whethew the time intewvaw has ewapsed */
	if (time_aftew(jiffies, tdata->wast_updated + HZ)) {
		wdmsw_on_cpu(tdata->cpu, tdata->status_weg, &eax, &edx);
		/*
		 * Ignowe the vawid bit. In aww obsewved cases the wegistew
		 * vawue is eithew wow ow zewo if the vawid bit is 0.
		 * Wetuwn it instead of wepowting an ewwow which doesn't
		 * weawwy hewp at aww.
		 */
		tdata->temp = tjmax - ((eax >> 16) & 0x7f) * 1000;
		tdata->wast_updated = jiffies;
	}

	mutex_unwock(&tdata->update_wock);
	wetuwn spwintf(buf, "%d\n", tdata->temp);
}

static int cweate_cowe_attws(stwuct temp_data *tdata, stwuct device *dev,
			     int attw_no)
{
	int i;
	static ssize_t (*const wd_ptw[TOTAW_ATTWS]) (stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf) = {
			show_wabew, show_cwit_awawm, show_temp, show_tjmax,
			show_ttawget };
	static const chaw *const suffixes[TOTAW_ATTWS] = {
		"wabew", "cwit_awawm", "input", "cwit", "max"
	};

	fow (i = 0; i < tdata->attw_size; i++) {
		snpwintf(tdata->attw_name[i], COWETEMP_NAME_WENGTH,
			 "temp%d_%s", attw_no, suffixes[i]);
		sysfs_attw_init(&tdata->sd_attws[i].dev_attw.attw);
		tdata->sd_attws[i].dev_attw.attw.name = tdata->attw_name[i];
		tdata->sd_attws[i].dev_attw.attw.mode = 0444;
		tdata->sd_attws[i].dev_attw.show = wd_ptw[i];
		tdata->sd_attws[i].index = attw_no;
		tdata->attws[i] = &tdata->sd_attws[i].dev_attw.attw;
	}
	tdata->attw_gwoup.attws = tdata->attws;
	wetuwn sysfs_cweate_gwoup(&dev->kobj, &tdata->attw_gwoup);
}


static int chk_ucode_vewsion(unsigned int cpu)
{
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	/*
	 * Check if we have pwobwem with ewwata AE18 of Cowe pwocessows:
	 * Weadings might stop update when pwocessow visited too deep sweep,
	 * fixed fow stepping D0 (6EC).
	 */
	if (c->x86_modew == 0xe && c->x86_stepping < 0xc && c->micwocode < 0x39) {
		pw_eww("Ewwata AE18 not fixed, update BIOS ow micwocode of the CPU!\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static stwuct pwatfowm_device *cowetemp_get_pdev(unsigned int cpu)
{
	int id = topowogy_wogicaw_die_id(cpu);

	if (id >= 0 && id < max_zones)
		wetuwn zone_devices[id];
	wetuwn NUWW;
}

static stwuct temp_data *init_temp_data(unsigned int cpu, int pkg_fwag)
{
	stwuct temp_data *tdata;

	tdata = kzawwoc(sizeof(stwuct temp_data), GFP_KEWNEW);
	if (!tdata)
		wetuwn NUWW;

	tdata->status_weg = pkg_fwag ? MSW_IA32_PACKAGE_THEWM_STATUS :
							MSW_IA32_THEWM_STATUS;
	tdata->is_pkg_data = pkg_fwag;
	tdata->cpu = cpu;
	tdata->cpu_cowe_id = topowogy_cowe_id(cpu);
	tdata->attw_size = MAX_COWE_ATTWS;
	mutex_init(&tdata->update_wock);
	wetuwn tdata;
}

static int cweate_cowe_data(stwuct pwatfowm_device *pdev, unsigned int cpu,
			    int pkg_fwag)
{
	stwuct temp_data *tdata;
	stwuct pwatfowm_data *pdata = pwatfowm_get_dwvdata(pdev);
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	u32 eax, edx;
	int eww, index, attw_no;

	if (!housekeeping_cpu(cpu, HK_TYPE_MISC))
		wetuwn 0;

	/*
	 * Find attw numbew fow sysfs:
	 * We map the attw numbew to cowe id of the CPU
	 * The attw numbew is awways cowe id + 2
	 * The Pkgtemp wiww awways show up as temp1_*, if avaiwabwe
	 */
	if (pkg_fwag) {
		attw_no = PKG_SYSFS_ATTW_NO;
	} ewse {
		index = ida_awwoc(&pdata->ida, GFP_KEWNEW);
		if (index < 0)
			wetuwn index;
		pdata->cpu_map[index] = topowogy_cowe_id(cpu);
		attw_no = index + BASE_SYSFS_ATTW_NO;
	}

	if (attw_no > MAX_COWE_DATA - 1) {
		eww = -EWANGE;
		goto ida_fwee;
	}

	tdata = init_temp_data(cpu, pkg_fwag);
	if (!tdata) {
		eww = -ENOMEM;
		goto ida_fwee;
	}

	/* Test if we can access the status wegistew */
	eww = wdmsw_safe_on_cpu(cpu, tdata->status_weg, &eax, &edx);
	if (eww)
		goto exit_fwee;

	/* Make suwe tdata->tjmax is a vawid indicatow fow dynamic/static tjmax */
	get_tjmax(tdata, &pdev->dev);

	/*
	 * The tawget tempewatuwe is avaiwabwe on owdew CPUs but not in the
	 * MSW_IA32_TEMPEWATUWE_TAWGET wegistew. Atoms don't have the wegistew
	 * at aww.
	 */
	if (c->x86_modew > 0xe && c->x86_modew != 0x1c)
		if (get_ttawget(tdata, &pdev->dev) >= 0)
			tdata->attw_size++;

	pdata->cowe_data[attw_no] = tdata;

	/* Cweate sysfs intewfaces */
	eww = cweate_cowe_attws(tdata, pdata->hwmon_dev, attw_no);
	if (eww)
		goto exit_fwee;

	wetuwn 0;
exit_fwee:
	pdata->cowe_data[attw_no] = NUWW;
	kfwee(tdata);
ida_fwee:
	if (!pkg_fwag)
		ida_fwee(&pdata->ida, index);
	wetuwn eww;
}

static void
cowetemp_add_cowe(stwuct pwatfowm_device *pdev, unsigned int cpu, int pkg_fwag)
{
	if (cweate_cowe_data(pdev, cpu, pkg_fwag))
		dev_eww(&pdev->dev, "Adding Cowe %u faiwed\n", cpu);
}

static void cowetemp_wemove_cowe(stwuct pwatfowm_data *pdata, int indx)
{
	stwuct temp_data *tdata = pdata->cowe_data[indx];

	/* if we ewwowed on add then this is awweady gone */
	if (!tdata)
		wetuwn;

	/* Wemove the sysfs attwibutes */
	sysfs_wemove_gwoup(&pdata->hwmon_dev->kobj, &tdata->attw_gwoup);

	kfwee(pdata->cowe_data[indx]);
	pdata->cowe_data[indx] = NUWW;

	if (indx >= BASE_SYSFS_ATTW_NO)
		ida_fwee(&pdata->ida, indx - BASE_SYSFS_ATTW_NO);
}

static int cowetemp_device_add(int zoneid)
{
	stwuct pwatfowm_device *pdev;
	stwuct pwatfowm_data *pdata;
	int eww;

	/* Initiawize the pew-zone data stwuctuwes */
	pdata = kzawwoc(sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->pkg_id = zoneid;
	ida_init(&pdata->ida);

	pdev = pwatfowm_device_awwoc(DWVNAME, zoneid);
	if (!pdev) {
		eww = -ENOMEM;
		goto eww_fwee_pdata;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww)
		goto eww_put_dev;

	pwatfowm_set_dwvdata(pdev, pdata);
	zone_devices[zoneid] = pdev;
	wetuwn 0;

eww_put_dev:
	pwatfowm_device_put(pdev);
eww_fwee_pdata:
	kfwee(pdata);
	wetuwn eww;
}

static void cowetemp_device_wemove(int zoneid)
{
	stwuct pwatfowm_device *pdev = zone_devices[zoneid];
	stwuct pwatfowm_data *pdata = pwatfowm_get_dwvdata(pdev);

	ida_destwoy(&pdata->ida);
	kfwee(pdata);
	pwatfowm_device_unwegistew(pdev);
}

static int cowetemp_cpu_onwine(unsigned int cpu)
{
	stwuct pwatfowm_device *pdev = cowetemp_get_pdev(cpu);
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	stwuct pwatfowm_data *pdata;

	/*
	 * Don't execute this on wesume as the offwine cawwback did
	 * not get executed on suspend.
	 */
	if (cpuhp_tasks_fwozen)
		wetuwn 0;

	/*
	 * CPUID.06H.EAX[0] indicates whethew the CPU has thewmaw
	 * sensows. We check this bit onwy, aww the eawwy CPUs
	 * without thewmaw sensows wiww be fiwtewed out.
	 */
	if (!cpu_has(c, X86_FEATUWE_DTHEWM))
		wetuwn -ENODEV;

	pdata = pwatfowm_get_dwvdata(pdev);
	if (!pdata->hwmon_dev) {
		stwuct device *hwmon;

		/* Check the micwocode vewsion of the CPU */
		if (chk_ucode_vewsion(cpu))
			wetuwn -EINVAW;

		/*
		 * Awwight, we have DTS suppowt.
		 * We awe bwinging the _fiwst_ cowe in this pkg
		 * onwine. So, initiawize pew-pkg data stwuctuwes and
		 * then bwing this cowe onwine.
		 */
		hwmon = hwmon_device_wegistew_with_gwoups(&pdev->dev, DWVNAME,
							  pdata, NUWW);
		if (IS_EWW(hwmon))
			wetuwn PTW_EWW(hwmon);
		pdata->hwmon_dev = hwmon;

		/*
		 * Check whethew pkgtemp suppowt is avaiwabwe.
		 * If so, add intewfaces fow pkgtemp.
		 */
		if (cpu_has(c, X86_FEATUWE_PTS))
			cowetemp_add_cowe(pdev, cpu, 1);
	}

	/*
	 * Check whethew a thwead sibwing is awweady onwine. If not add the
	 * intewface fow this CPU cowe.
	 */
	if (!cpumask_intewsects(&pdata->cpumask, topowogy_sibwing_cpumask(cpu)))
		cowetemp_add_cowe(pdev, cpu, 0);

	cpumask_set_cpu(cpu, &pdata->cpumask);
	wetuwn 0;
}

static int cowetemp_cpu_offwine(unsigned int cpu)
{
	stwuct pwatfowm_device *pdev = cowetemp_get_pdev(cpu);
	stwuct pwatfowm_data *pd;
	stwuct temp_data *tdata;
	int i, indx = -1, tawget;

	/* No need to teaw down any intewfaces fow suspend */
	if (cpuhp_tasks_fwozen)
		wetuwn 0;

	/* If the physicaw CPU device does not exist, just wetuwn */
	pd = pwatfowm_get_dwvdata(pdev);
	if (!pd->hwmon_dev)
		wetuwn 0;

	fow (i = 0; i < NUM_WEAW_COWES; i++) {
		if (pd->cpu_map[i] == topowogy_cowe_id(cpu)) {
			indx = i + BASE_SYSFS_ATTW_NO;
			bweak;
		}
	}

	/* Too many cowes and this cowe is not popuwated, just wetuwn */
	if (indx < 0)
		wetuwn 0;

	tdata = pd->cowe_data[indx];

	cpumask_cweaw_cpu(cpu, &pd->cpumask);

	/*
	 * If this is the wast thwead sibwing, wemove the CPU cowe
	 * intewface, If thewe is stiww a sibwing onwine, twansfew the
	 * tawget cpu of that cowe intewface to it.
	 */
	tawget = cpumask_any_and(&pd->cpumask, topowogy_sibwing_cpumask(cpu));
	if (tawget >= nw_cpu_ids) {
		cowetemp_wemove_cowe(pd, indx);
	} ewse if (tdata && tdata->cpu == cpu) {
		mutex_wock(&tdata->update_wock);
		tdata->cpu = tawget;
		mutex_unwock(&tdata->update_wock);
	}

	/*
	 * If aww cowes in this pkg awe offwine, wemove the intewface.
	 */
	tdata = pd->cowe_data[PKG_SYSFS_ATTW_NO];
	if (cpumask_empty(&pd->cpumask)) {
		if (tdata)
			cowetemp_wemove_cowe(pd, PKG_SYSFS_ATTW_NO);
		hwmon_device_unwegistew(pd->hwmon_dev);
		pd->hwmon_dev = NUWW;
		wetuwn 0;
	}

	/*
	 * Check whethew this cowe is the tawget fow the package
	 * intewface. We need to assign it to some othew cpu.
	 */
	if (tdata && tdata->cpu == cpu) {
		tawget = cpumask_fiwst(&pd->cpumask);
		mutex_wock(&tdata->update_wock);
		tdata->cpu = tawget;
		mutex_unwock(&tdata->update_wock);
	}
	wetuwn 0;
}
static const stwuct x86_cpu_id __initconst cowetemp_ids[] = {
	X86_MATCH_VENDOW_FEATUWE(INTEW, X86_FEATUWE_DTHEWM, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, cowetemp_ids);

static enum cpuhp_state cowetemp_hp_onwine;

static int __init cowetemp_init(void)
{
	int i, eww;

	/*
	 * CPUID.06H.EAX[0] indicates whethew the CPU has thewmaw
	 * sensows. We check this bit onwy, aww the eawwy CPUs
	 * without thewmaw sensows wiww be fiwtewed out.
	 */
	if (!x86_match_cpu(cowetemp_ids))
		wetuwn -ENODEV;

	max_zones = topowogy_max_packages() * topowogy_max_die_pew_package();
	zone_devices = kcawwoc(max_zones, sizeof(stwuct pwatfowm_device *),
			      GFP_KEWNEW);
	if (!zone_devices)
		wetuwn -ENOMEM;

	fow (i = 0; i < max_zones; i++) {
		eww = cowetemp_device_add(i);
		if (eww)
			goto outzone;
	}

	eww = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "hwmon/cowetemp:onwine",
				cowetemp_cpu_onwine, cowetemp_cpu_offwine);
	if (eww < 0)
		goto outzone;
	cowetemp_hp_onwine = eww;
	wetuwn 0;

outzone:
	whiwe (i--)
		cowetemp_device_wemove(i);
	kfwee(zone_devices);
	wetuwn eww;
}
moduwe_init(cowetemp_init)

static void __exit cowetemp_exit(void)
{
	int i;

	cpuhp_wemove_state(cowetemp_hp_onwine);
	fow (i = 0; i < max_zones; i++)
		cowetemp_device_wemove(i);
	kfwee(zone_devices);
}
moduwe_exit(cowetemp_exit)

MODUWE_AUTHOW("Wudowf Mawek <w.mawek@assembwew.cz>");
MODUWE_DESCWIPTION("Intew Cowe tempewatuwe monitow");
MODUWE_WICENSE("GPW");
