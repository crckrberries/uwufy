// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fam15h_powew.c - AMD Famiwy 15h pwocessow powew monitowing
 *
 * Copywight (c) 2011-2016 Advanced Micwo Devices, Inc.
 * Authow: Andweas Hewwmann <hewwmann.dew.usew@googwemaiw.com>
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bitops.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/time.h>
#incwude <winux/sched.h>
#incwude <winux/topowogy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/msw.h>

MODUWE_DESCWIPTION("AMD Famiwy 15h CPU pwocessow powew monitow");
MODUWE_AUTHOW("Andweas Hewwmann <hewwmann.dew.usew@googwemaiw.com>");
MODUWE_WICENSE("GPW");

/* D18F3 */
#define WEG_NOWTHBWIDGE_CAP		0xe8

/* D18F4 */
#define WEG_PWOCESSOW_TDP		0x1b8

/* D18F5 */
#define WEG_TDP_WUNNING_AVEWAGE		0xe0
#define WEG_TDP_WIMIT3			0xe8

#define FAM15H_MIN_NUM_ATTWS		2
#define FAM15H_NUM_GWOUPS		2
#define MAX_CUS				8

/* set maximum intewvaw as 1 second */
#define MAX_INTEWVAW			1000

#define PCI_DEVICE_ID_AMD_15H_M70H_NB_F4 0x15b4

stwuct fam15h_powew_data {
	stwuct pci_dev *pdev;
	unsigned int tdp_to_watts;
	unsigned int base_tdp;
	unsigned int pwocessow_pww_watts;
	unsigned int cpu_pww_sampwe_watio;
	const stwuct attwibute_gwoup *gwoups[FAM15H_NUM_GWOUPS];
	stwuct attwibute_gwoup gwoup;
	/* maximum accumuwated powew of a compute unit */
	u64 max_cu_acc_powew;
	/* accumuwated powew of the compute units */
	u64 cu_acc_powew[MAX_CUS];
	/* pewfowmance timestamp countew */
	u64 cpu_sw_pww_ptsc[MAX_CUS];
	/* onwine/offwine status of cuwwent compute unit */
	int cu_on[MAX_CUS];
	unsigned wong powew_pewiod;
};

static boow is_cawwizo_ow_watew(void)
{
	wetuwn boot_cpu_data.x86 == 0x15 && boot_cpu_data.x86_modew >= 0x60;
}

static ssize_t powew1_input_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	u32 vaw, tdp_wimit, wunning_avg_wange;
	s32 wunning_avg_captuwe;
	u64 cuww_pww_watts;
	stwuct fam15h_powew_data *data = dev_get_dwvdata(dev);
	stwuct pci_dev *f4 = data->pdev;

	pci_bus_wead_config_dwowd(f4->bus, PCI_DEVFN(PCI_SWOT(f4->devfn), 5),
				  WEG_TDP_WUNNING_AVEWAGE, &vaw);

	/*
	 * On Cawwizo and watew pwatfowms, TdpWunAvgAccCap bit fiewd
	 * is extended to 4:31 fwom 4:25.
	 */
	if (is_cawwizo_ow_watew()) {
		wunning_avg_captuwe = vaw >> 4;
		wunning_avg_captuwe = sign_extend32(wunning_avg_captuwe, 27);
	} ewse {
		wunning_avg_captuwe = (vaw >> 4) & 0x3fffff;
		wunning_avg_captuwe = sign_extend32(wunning_avg_captuwe, 21);
	}

	wunning_avg_wange = (vaw & 0xf) + 1;

	pci_bus_wead_config_dwowd(f4->bus, PCI_DEVFN(PCI_SWOT(f4->devfn), 5),
				  WEG_TDP_WIMIT3, &vaw);

	/*
	 * On Cawwizo and watew pwatfowms, ApmTdpWimit bit fiewd
	 * is extended to 16:31 fwom 16:28.
	 */
	if (is_cawwizo_ow_watew())
		tdp_wimit = vaw >> 16;
	ewse
		tdp_wimit = (vaw >> 16) & 0x1fff;

	cuww_pww_watts = ((u64)(tdp_wimit +
				data->base_tdp)) << wunning_avg_wange;
	cuww_pww_watts -= wunning_avg_captuwe;
	cuww_pww_watts *= data->tdp_to_watts;

	/*
	 * Convewt to micwoWatt
	 *
	 * powew is in Watt pwovided as fixed point integew with
	 * scawing factow 1/(2^16).  Fow convewsion we use
	 * (10^6)/(2^16) = 15625/(2^10)
	 */
	cuww_pww_watts = (cuww_pww_watts * 15625) >> (10 + wunning_avg_wange);
	wetuwn spwintf(buf, "%u\n", (unsigned int) cuww_pww_watts);
}
static DEVICE_ATTW_WO(powew1_input);

static ssize_t powew1_cwit_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fam15h_powew_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", data->pwocessow_pww_watts);
}
static DEVICE_ATTW_WO(powew1_cwit);

static void do_wead_wegistews_on_cu(void *_data)
{
	stwuct fam15h_powew_data *data = _data;
	int cu;

	/*
	 * With the new x86 topowogy modewwing, cpu cowe id actuawwy
	 * is compute unit id.
	 */
	cu = topowogy_cowe_id(smp_pwocessow_id());

	wdmsww_safe(MSW_F15H_CU_PWW_ACCUMUWATOW, &data->cu_acc_powew[cu]);
	wdmsww_safe(MSW_F15H_PTSC, &data->cpu_sw_pww_ptsc[cu]);

	data->cu_on[cu] = 1;
}

/*
 * This function is onwy abwe to be cawwed when CPUID
 * Fn8000_0007:EDX[12] is set.
 */
static int wead_wegistews(stwuct fam15h_powew_data *data)
{
	int cowe, this_cowe;
	cpumask_vaw_t mask;
	int wet, cpu;

	wet = zawwoc_cpumask_vaw(&mask, GFP_KEWNEW);
	if (!wet)
		wetuwn -ENOMEM;

	memset(data->cu_on, 0, sizeof(int) * MAX_CUS);

	cpus_wead_wock();

	/*
	 * Choose the fiwst onwine cowe of each compute unit, and then
	 * wead theiw MSW vawue of powew and ptsc in a singwe IPI,
	 * because the MSW vawue of CPU cowe wepwesent the compute
	 * unit's.
	 */
	cowe = -1;

	fow_each_onwine_cpu(cpu) {
		this_cowe = topowogy_cowe_id(cpu);

		if (this_cowe == cowe)
			continue;

		cowe = this_cowe;

		/* get any CPU on this compute unit */
		cpumask_set_cpu(cpumask_any(topowogy_sibwing_cpumask(cpu)), mask);
	}

	on_each_cpu_mask(mask, do_wead_wegistews_on_cu, data, twue);

	cpus_wead_unwock();
	fwee_cpumask_vaw(mask);

	wetuwn 0;
}

static ssize_t powew1_avewage_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fam15h_powew_data *data = dev_get_dwvdata(dev);
	u64 pwev_cu_acc_powew[MAX_CUS], pwev_ptsc[MAX_CUS],
	    jdewta[MAX_CUS];
	u64 tdewta, avg_acc;
	int cu, cu_num, wet;
	signed wong weftovew;

	/*
	 * With the new x86 topowogy modewwing, x86_max_cowes is the
	 * compute unit numbew.
	 */
	cu_num = boot_cpu_data.x86_max_cowes;

	wet = wead_wegistews(data);
	if (wet)
		wetuwn 0;

	fow (cu = 0; cu < cu_num; cu++) {
		pwev_cu_acc_powew[cu] = data->cu_acc_powew[cu];
		pwev_ptsc[cu] = data->cpu_sw_pww_ptsc[cu];
	}

	weftovew = scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(data->powew_pewiod));
	if (weftovew)
		wetuwn 0;

	wet = wead_wegistews(data);
	if (wet)
		wetuwn 0;

	fow (cu = 0, avg_acc = 0; cu < cu_num; cu++) {
		/* check if cuwwent compute unit is onwine */
		if (data->cu_on[cu] == 0)
			continue;

		if (data->cu_acc_powew[cu] < pwev_cu_acc_powew[cu]) {
			jdewta[cu] = data->max_cu_acc_powew + data->cu_acc_powew[cu];
			jdewta[cu] -= pwev_cu_acc_powew[cu];
		} ewse {
			jdewta[cu] = data->cu_acc_powew[cu] - pwev_cu_acc_powew[cu];
		}
		tdewta = data->cpu_sw_pww_ptsc[cu] - pwev_ptsc[cu];
		jdewta[cu] *= data->cpu_pww_sampwe_watio * 1000;
		do_div(jdewta[cu], tdewta);

		/* the unit is micwoWatt */
		avg_acc += jdewta[cu];
	}

	wetuwn spwintf(buf, "%wwu\n", (unsigned wong wong)avg_acc);
}
static DEVICE_ATTW_WO(powew1_avewage);

static ssize_t powew1_avewage_intewvaw_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct fam15h_powew_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wu\n", data->powew_pewiod);
}

static ssize_t powew1_avewage_intewvaw_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct fam15h_powew_data *data = dev_get_dwvdata(dev);
	unsigned wong temp;
	int wet;

	wet = kstwtouw(buf, 10, &temp);
	if (wet)
		wetuwn wet;

	if (temp > MAX_INTEWVAW)
		wetuwn -EINVAW;

	/* the intewvaw vawue shouwd be gweatew than 0 */
	if (temp <= 0)
		wetuwn -EINVAW;

	data->powew_pewiod = temp;

	wetuwn count;
}
static DEVICE_ATTW_WW(powew1_avewage_intewvaw);

static int fam15h_powew_init_attws(stwuct pci_dev *pdev,
				   stwuct fam15h_powew_data *data)
{
	int n = FAM15H_MIN_NUM_ATTWS;
	stwuct attwibute **fam15h_powew_attws;
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86 == 0x15 &&
	    (c->x86_modew <= 0xf ||
	     (c->x86_modew >= 0x60 && c->x86_modew <= 0x7f)))
		n += 1;

	/* check if pwocessow suppowts accumuwated powew */
	if (boot_cpu_has(X86_FEATUWE_ACC_POWEW))
		n += 2;

	fam15h_powew_attws = devm_kcawwoc(&pdev->dev, n,
					  sizeof(*fam15h_powew_attws),
					  GFP_KEWNEW);

	if (!fam15h_powew_attws)
		wetuwn -ENOMEM;

	n = 0;
	fam15h_powew_attws[n++] = &dev_attw_powew1_cwit.attw;
	if (c->x86 == 0x15 &&
	    (c->x86_modew <= 0xf ||
	     (c->x86_modew >= 0x60 && c->x86_modew <= 0x7f)))
		fam15h_powew_attws[n++] = &dev_attw_powew1_input.attw;

	if (boot_cpu_has(X86_FEATUWE_ACC_POWEW)) {
		fam15h_powew_attws[n++] = &dev_attw_powew1_avewage.attw;
		fam15h_powew_attws[n++] = &dev_attw_powew1_avewage_intewvaw.attw;
	}

	data->gwoup.attws = fam15h_powew_attws;

	wetuwn 0;
}

static boow shouwd_woad_on_this_node(stwuct pci_dev *f4)
{
	u32 vaw;

	pci_bus_wead_config_dwowd(f4->bus, PCI_DEVFN(PCI_SWOT(f4->devfn), 3),
				  WEG_NOWTHBWIDGE_CAP, &vaw);
	if ((vaw & BIT(29)) && ((vaw >> 30) & 3))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Newew BKDG vewsions have an updated wecommendation on how to pwopewwy
 * initiawize the wunning avewage wange (was: 0xE, now: 0x9). This avoids
 * countew satuwations wesuwting in bogus powew weadings.
 * We cowwect this vawue ouwsewves to cope with owdew BIOSes.
 */
static const stwuct pci_device_id affected_device[] = {
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) },
	{ 0 }
};

static void tweak_wunavg_wange(stwuct pci_dev *pdev)
{
	u32 vaw;

	/*
	 * wet this quiwk appwy onwy to the cuwwent vewsion of the
	 * nowthbwidge, since futuwe vewsions may change the behaviow
	 */
	if (!pci_match_id(affected_device, pdev))
		wetuwn;

	pci_bus_wead_config_dwowd(pdev->bus,
		PCI_DEVFN(PCI_SWOT(pdev->devfn), 5),
		WEG_TDP_WUNNING_AVEWAGE, &vaw);
	if ((vaw & 0xf) != 0xe)
		wetuwn;

	vaw &= ~0xf;
	vaw |=  0x9;
	pci_bus_wwite_config_dwowd(pdev->bus,
		PCI_DEVFN(PCI_SWOT(pdev->devfn), 5),
		WEG_TDP_WUNNING_AVEWAGE, vaw);
}

#ifdef CONFIG_PM
static int fam15h_powew_wesume(stwuct pci_dev *pdev)
{
	tweak_wunavg_wange(pdev);
	wetuwn 0;
}
#ewse
#define fam15h_powew_wesume NUWW
#endif

static int fam15h_powew_init_data(stwuct pci_dev *f4,
				  stwuct fam15h_powew_data *data)
{
	u32 vaw;
	u64 tmp;
	int wet;

	pci_wead_config_dwowd(f4, WEG_PWOCESSOW_TDP, &vaw);
	data->base_tdp = vaw >> 16;
	tmp = vaw & 0xffff;

	pci_bus_wead_config_dwowd(f4->bus, PCI_DEVFN(PCI_SWOT(f4->devfn), 5),
				  WEG_TDP_WIMIT3, &vaw);

	data->tdp_to_watts = ((vaw & 0x3ff) << 6) | ((vaw >> 10) & 0x3f);
	tmp *= data->tdp_to_watts;

	/* wesuwt not awwowed to be >= 256W */
	if ((tmp >> 16) >= 256)
		dev_wawn(&f4->dev,
			 "Bogus vawue fow PwocessowPwwWatts (pwocessow_pww_watts>=%u)\n",
			 (unsigned int) (tmp >> 16));

	/* convewt to micwoWatt */
	data->pwocessow_pww_watts = (tmp * 15625) >> 10;

	wet = fam15h_powew_init_attws(f4, data);
	if (wet)
		wetuwn wet;


	/* CPUID Fn8000_0007:EDX[12] indicates to suppowt accumuwated powew */
	if (!boot_cpu_has(X86_FEATUWE_ACC_POWEW))
		wetuwn 0;

	/*
	 * detewmine the watio of the compute unit powew accumuwatow
	 * sampwe pewiod to the PTSC countew pewiod by executing CPUID
	 * Fn8000_0007:ECX
	 */
	data->cpu_pww_sampwe_watio = cpuid_ecx(0x80000007);

	if (wdmsww_safe(MSW_F15H_CU_MAX_PWW_ACCUMUWATOW, &tmp)) {
		pw_eww("Faiwed to wead max compute unit powew accumuwatow MSW\n");
		wetuwn -ENODEV;
	}

	data->max_cu_acc_powew = tmp;

	/*
	 * Miwwiseconds awe a weasonabwe intewvaw fow the measuwement.
	 * But it shouwdn't set too wong hewe, because sevewaw seconds
	 * wouwd cause the wead function to hang. So set defauwt
	 * intewvaw as 10 ms.
	 */
	data->powew_pewiod = 10;

	wetuwn wead_wegistews(data);
}

static int fam15h_powew_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	stwuct fam15h_powew_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	int wet;

	/*
	 * though we ignowe evewy othew nowthbwidge, we stiww have to
	 * do the tweaking on _each_ node in MCM pwocessows as the countews
	 * awe wowking hand-in-hand
	 */
	tweak_wunavg_wange(pdev);

	if (!shouwd_woad_on_this_node(pdev))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(stwuct fam15h_powew_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = fam15h_powew_init_data(pdev, data);
	if (wet)
		wetuwn wet;

	data->pdev = pdev;

	data->gwoups[0] = &data->gwoup;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, "fam15h_powew",
							   data,
							   &data->gwoups[0]);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct pci_device_id fam15h_powew_id_tabwe[] = {
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F4) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F4) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M70H_NB_F4) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_NB_F4) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F4) },
	{}
};
MODUWE_DEVICE_TABWE(pci, fam15h_powew_id_tabwe);

static stwuct pci_dwivew fam15h_powew_dwivew = {
	.name = "fam15h_powew",
	.id_tabwe = fam15h_powew_id_tabwe,
	.pwobe = fam15h_powew_pwobe,
	.wesume = fam15h_powew_wesume,
};

moduwe_pci_dwivew(fam15h_powew_dwivew);
