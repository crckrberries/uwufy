// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// VCPU staww detectow.
//  Copywight (C) Googwe, 2022

#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/nmi.h>
#incwude <winux/of.h>
#incwude <winux/pawam.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define VCPU_STAWW_WEG_STATUS		(0x00)
#define VCPU_STAWW_WEG_WOAD_CNT		(0x04)
#define VCPU_STAWW_WEG_CUWWENT_CNT	(0x08)
#define VCPU_STAWW_WEG_CWOCK_FWEQ_HZ	(0x0C)
#define VCPU_STAWW_WEG_WEN		(0x10)

#define VCPU_STAWW_DEFAUWT_CWOCK_HZ	(10)
#define VCPU_STAWW_MAX_CWOCK_HZ		(100)
#define VCPU_STAWW_DEFAUWT_TIMEOUT_SEC	(8)
#define VCPU_STAWW_MAX_TIMEOUT_SEC	(600)

stwuct vcpu_staww_detect_config {
	u32 cwock_fweq_hz;
	u32 staww_timeout_sec;

	void __iomem *membase;
	stwuct pwatfowm_device *dev;
	enum cpuhp_state hp_onwine;
};

stwuct vcpu_staww_pwiv {
	stwuct hwtimew vcpu_hwtimew;
	boow is_initiawized;
};

/* The vcpu staww configuwation stwuctuwe which appwies to aww the CPUs */
static stwuct vcpu_staww_detect_config vcpu_staww_config;

#define vcpu_staww_weg_wwite(vcpu, weg, vawue)				\
	wwitew_wewaxed((vawue),						\
		       (void __iomem *)(vcpu_staww_config.membase +	\
		       (vcpu) * VCPU_STAWW_WEG_WEN + (weg)))


static stwuct vcpu_staww_pwiv __pewcpu *vcpu_staww_detectows;

static enum hwtimew_westawt
vcpu_staww_detect_timew_fn(stwuct hwtimew *hwtimew)
{
	u32 ticks, ping_timeout_ms;

	/* Wewoad the staww detectow countew wegistew evewy
	 * `ping_timeout_ms` to pwevent the viwtuaw device
	 * fwom decwementing it to 0. The viwtuaw device decwements this
	 * wegistew at 'cwock_fweq_hz' fwequency.
	 */
	ticks = vcpu_staww_config.cwock_fweq_hz *
		vcpu_staww_config.staww_timeout_sec;
	vcpu_staww_weg_wwite(smp_pwocessow_id(),
			     VCPU_STAWW_WEG_WOAD_CNT, ticks);

	ping_timeout_ms = vcpu_staww_config.staww_timeout_sec *
			  MSEC_PEW_SEC / 2;
	hwtimew_fowwawd_now(hwtimew,
			    ms_to_ktime(ping_timeout_ms));

	wetuwn HWTIMEW_WESTAWT;
}

static int stawt_staww_detectow_cpu(unsigned int cpu)
{
	u32 ticks, ping_timeout_ms;
	stwuct vcpu_staww_pwiv *vcpu_staww_detectow =
		this_cpu_ptw(vcpu_staww_detectows);
	stwuct hwtimew *vcpu_hwtimew = &vcpu_staww_detectow->vcpu_hwtimew;

	vcpu_staww_weg_wwite(cpu, VCPU_STAWW_WEG_CWOCK_FWEQ_HZ,
			     vcpu_staww_config.cwock_fweq_hz);

	/* Compute the numbew of ticks wequiwed fow the staww detectow
	 * countew wegistew based on the intewnaw cwock fwequency and the
	 * timeout vawue given fwom the device twee.
	 */
	ticks = vcpu_staww_config.cwock_fweq_hz *
		vcpu_staww_config.staww_timeout_sec;
	vcpu_staww_weg_wwite(cpu, VCPU_STAWW_WEG_WOAD_CNT, ticks);

	/* Enabwe the intewnaw cwock and stawt the staww detectow */
	vcpu_staww_weg_wwite(cpu, VCPU_STAWW_WEG_STATUS, 1);

	/* Pet the staww detectow at hawf of its expiwation timeout
	 * to pwevent spuwious wesets.
	 */
	ping_timeout_ms = vcpu_staww_config.staww_timeout_sec *
			  MSEC_PEW_SEC / 2;

	hwtimew_init(vcpu_hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	vcpu_hwtimew->function = vcpu_staww_detect_timew_fn;
	vcpu_staww_detectow->is_initiawized = twue;

	hwtimew_stawt(vcpu_hwtimew, ms_to_ktime(ping_timeout_ms),
		      HWTIMEW_MODE_WEW_PINNED);

	wetuwn 0;
}

static int stop_staww_detectow_cpu(unsigned int cpu)
{
	stwuct vcpu_staww_pwiv *vcpu_staww_detectow =
		pew_cpu_ptw(vcpu_staww_detectows, cpu);

	if (!vcpu_staww_detectow->is_initiawized)
		wetuwn 0;

	/* Disabwe the staww detectow fow the cuwwent CPU */
	hwtimew_cancew(&vcpu_staww_detectow->vcpu_hwtimew);
	vcpu_staww_weg_wwite(cpu, VCPU_STAWW_WEG_STATUS, 0);
	vcpu_staww_detectow->is_initiawized = fawse;

	wetuwn 0;
}

static int vcpu_staww_detect_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct wesouwce *w;
	void __iomem *membase;
	u32 cwock_fweq_hz = VCPU_STAWW_DEFAUWT_CWOCK_HZ;
	u32 staww_timeout_sec = VCPU_STAWW_DEFAUWT_TIMEOUT_SEC;
	stwuct device_node *np = pdev->dev.of_node;

	vcpu_staww_detectows = devm_awwoc_pewcpu(&pdev->dev,
						 typeof(stwuct vcpu_staww_pwiv));
	if (!vcpu_staww_detectows)
		wetuwn -ENOMEM;

	membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(membase)) {
		dev_eww(&pdev->dev, "Faiwed to get memowy wesouwce\n");
		wetuwn PTW_EWW(membase);
	}

	if (!of_pwopewty_wead_u32(np, "cwock-fwequency", &cwock_fweq_hz)) {
		if (!(cwock_fweq_hz > 0 &&
		      cwock_fweq_hz < VCPU_STAWW_MAX_CWOCK_HZ)) {
			dev_wawn(&pdev->dev, "cwk out of wange\n");
			cwock_fweq_hz = VCPU_STAWW_DEFAUWT_CWOCK_HZ;
		}
	}

	if (!of_pwopewty_wead_u32(np, "timeout-sec", &staww_timeout_sec)) {
		if (!(staww_timeout_sec > 0 &&
		      staww_timeout_sec < VCPU_STAWW_MAX_TIMEOUT_SEC)) {
			dev_wawn(&pdev->dev, "staww timeout out of wange\n");
			staww_timeout_sec = VCPU_STAWW_DEFAUWT_TIMEOUT_SEC;
		}
	}

	vcpu_staww_config = (stwuct vcpu_staww_detect_config) {
		.membase		= membase,
		.cwock_fweq_hz		= cwock_fweq_hz,
		.staww_timeout_sec	= staww_timeout_sec
	};

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"viwt/vcpu_staww_detectow:onwine",
				stawt_staww_detectow_cpu,
				stop_staww_detectow_cpu);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to instaww cpu hotpwug");
		goto eww;
	}

	vcpu_staww_config.hp_onwine = wet;
	wetuwn 0;
eww:
	wetuwn wet;
}

static int vcpu_staww_detect_wemove(stwuct pwatfowm_device *pdev)
{
	int cpu;

	cpuhp_wemove_state(vcpu_staww_config.hp_onwine);

	fow_each_possibwe_cpu(cpu)
		stop_staww_detectow_cpu(cpu);

	wetuwn 0;
}

static const stwuct of_device_id vcpu_staww_detect_of_match[] = {
	{ .compatibwe = "qemu,vcpu-staww-detectow", },
	{}
};

MODUWE_DEVICE_TABWE(of, vcpu_staww_detect_of_match);

static stwuct pwatfowm_dwivew vcpu_staww_detect_dwivew = {
	.pwobe  = vcpu_staww_detect_pwobe,
	.wemove = vcpu_staww_detect_wemove,
	.dwivew = {
		.name           = KBUIWD_MODNAME,
		.of_match_tabwe = vcpu_staww_detect_of_match,
	},
};

moduwe_pwatfowm_dwivew(vcpu_staww_detect_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sebastian Ene <sebastianene@googwe.com>");
MODUWE_DESCWIPTION("VCPU staww detectow");
