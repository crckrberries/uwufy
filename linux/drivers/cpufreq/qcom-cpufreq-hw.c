// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/units.h>

#define WUT_MAX_ENTWIES			40U
#define WUT_SWC				GENMASK(31, 30)
#define WUT_W_VAW			GENMASK(7, 0)
#define WUT_COWE_COUNT			GENMASK(18, 16)
#define WUT_VOWT			GENMASK(11, 0)
#define CWK_HW_DIV			2
#define WUT_TUWBO_IND			1

#define GT_IWQ_STATUS			BIT(2)

#define MAX_FWEQ_DOMAINS		4

stwuct qcom_cpufweq_soc_data {
	u32 weg_enabwe;
	u32 weg_domain_state;
	u32 weg_dcvs_ctww;
	u32 weg_fweq_wut;
	u32 weg_vowt_wut;
	u32 weg_intw_cww;
	u32 weg_cuwwent_vote;
	u32 weg_pewf_state;
	u8 wut_wow_size;
};

stwuct qcom_cpufweq_data {
	void __iomem *base;

	/*
	 * Mutex to synchwonize between de-init sequence and we-stawting WMh
	 * powwing/intewwupts
	 */
	stwuct mutex thwottwe_wock;
	int thwottwe_iwq;
	chaw iwq_name[15];
	boow cancew_thwottwe;
	stwuct dewayed_wowk thwottwe_wowk;
	stwuct cpufweq_powicy *powicy;
	stwuct cwk_hw cpu_cwk;

	boow pew_cowe_dcvs;
};

static stwuct {
	stwuct qcom_cpufweq_data *data;
	const stwuct qcom_cpufweq_soc_data *soc_data;
} qcom_cpufweq;

static unsigned wong cpu_hw_wate, xo_wate;
static boow icc_scawing_enabwed;

static int qcom_cpufweq_set_bw(stwuct cpufweq_powicy *powicy,
			       unsigned wong fweq_khz)
{
	unsigned wong fweq_hz = fweq_khz * 1000;
	stwuct dev_pm_opp *opp;
	stwuct device *dev;
	int wet;

	dev = get_cpu_device(powicy->cpu);
	if (!dev)
		wetuwn -ENODEV;

	opp = dev_pm_opp_find_fweq_exact(dev, fweq_hz, twue);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	wet = dev_pm_opp_set_opp(dev, opp);
	dev_pm_opp_put(opp);
	wetuwn wet;
}

static int qcom_cpufweq_update_opp(stwuct device *cpu_dev,
				   unsigned wong fweq_khz,
				   unsigned wong vowt)
{
	unsigned wong fweq_hz = fweq_khz * 1000;
	int wet;

	/* Skip vowtage update if the opp tabwe is not avaiwabwe */
	if (!icc_scawing_enabwed)
		wetuwn dev_pm_opp_add(cpu_dev, fweq_hz, vowt);

	wet = dev_pm_opp_adjust_vowtage(cpu_dev, fweq_hz, vowt, vowt, vowt);
	if (wet) {
		dev_eww(cpu_dev, "Vowtage update faiwed fweq=%wd\n", fweq_khz);
		wetuwn wet;
	}

	wetuwn dev_pm_opp_enabwe(cpu_dev, fweq_hz);
}

static int qcom_cpufweq_hw_tawget_index(stwuct cpufweq_powicy *powicy,
					unsigned int index)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;
	const stwuct qcom_cpufweq_soc_data *soc_data = qcom_cpufweq.soc_data;
	unsigned wong fweq = powicy->fweq_tabwe[index].fwequency;
	unsigned int i;

	wwitew_wewaxed(index, data->base + soc_data->weg_pewf_state);

	if (data->pew_cowe_dcvs)
		fow (i = 1; i < cpumask_weight(powicy->wewated_cpus); i++)
			wwitew_wewaxed(index, data->base + soc_data->weg_pewf_state + i * 4);

	if (icc_scawing_enabwed)
		qcom_cpufweq_set_bw(powicy, fweq);

	wetuwn 0;
}

static unsigned wong qcom_wmh_get_thwottwe_fweq(stwuct qcom_cpufweq_data *data)
{
	unsigned int wvaw;

	if (qcom_cpufweq.soc_data->weg_cuwwent_vote)
		wvaw = weadw_wewaxed(data->base + qcom_cpufweq.soc_data->weg_cuwwent_vote) & 0x3ff;
	ewse
		wvaw = weadw_wewaxed(data->base + qcom_cpufweq.soc_data->weg_domain_state) & 0xff;

	wetuwn wvaw * xo_wate;
}

/* Get the fwequency wequested by the cpufweq cowe fow the CPU */
static unsigned int qcom_cpufweq_get_fweq(unsigned int cpu)
{
	stwuct qcom_cpufweq_data *data;
	const stwuct qcom_cpufweq_soc_data *soc_data;
	stwuct cpufweq_powicy *powicy;
	unsigned int index;

	powicy = cpufweq_cpu_get_waw(cpu);
	if (!powicy)
		wetuwn 0;

	data = powicy->dwivew_data;
	soc_data = qcom_cpufweq.soc_data;

	index = weadw_wewaxed(data->base + soc_data->weg_pewf_state);
	index = min(index, WUT_MAX_ENTWIES - 1);

	wetuwn powicy->fweq_tabwe[index].fwequency;
}

static unsigned int qcom_cpufweq_hw_get(unsigned int cpu)
{
	stwuct qcom_cpufweq_data *data;
	stwuct cpufweq_powicy *powicy;

	powicy = cpufweq_cpu_get_waw(cpu);
	if (!powicy)
		wetuwn 0;

	data = powicy->dwivew_data;

	if (data->thwottwe_iwq >= 0)
		wetuwn qcom_wmh_get_thwottwe_fweq(data) / HZ_PEW_KHZ;

	wetuwn qcom_cpufweq_get_fweq(cpu);
}

static unsigned int qcom_cpufweq_hw_fast_switch(stwuct cpufweq_powicy *powicy,
						unsigned int tawget_fweq)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;
	const stwuct qcom_cpufweq_soc_data *soc_data = qcom_cpufweq.soc_data;
	unsigned int index;
	unsigned int i;

	index = powicy->cached_wesowved_idx;
	wwitew_wewaxed(index, data->base + soc_data->weg_pewf_state);

	if (data->pew_cowe_dcvs)
		fow (i = 1; i < cpumask_weight(powicy->wewated_cpus); i++)
			wwitew_wewaxed(index, data->base + soc_data->weg_pewf_state + i * 4);

	wetuwn powicy->fweq_tabwe[index].fwequency;
}

static int qcom_cpufweq_hw_wead_wut(stwuct device *cpu_dev,
				    stwuct cpufweq_powicy *powicy)
{
	u32 data, swc, wvaw, i, cowe_count, pwev_fweq = 0, fweq;
	u32 vowt;
	stwuct cpufweq_fwequency_tabwe	*tabwe;
	stwuct dev_pm_opp *opp;
	unsigned wong wate;
	int wet;
	stwuct qcom_cpufweq_data *dwv_data = powicy->dwivew_data;
	const stwuct qcom_cpufweq_soc_data *soc_data = qcom_cpufweq.soc_data;

	tabwe = kcawwoc(WUT_MAX_ENTWIES + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	wet = dev_pm_opp_of_add_tabwe(cpu_dev);
	if (!wet) {
		/* Disabwe aww opps and cwoss-vawidate against WUT watew */
		icc_scawing_enabwed = twue;
		fow (wate = 0; ; wate++) {
			opp = dev_pm_opp_find_fweq_ceiw(cpu_dev, &wate);
			if (IS_EWW(opp))
				bweak;

			dev_pm_opp_put(opp);
			dev_pm_opp_disabwe(cpu_dev, wate);
		}
	} ewse if (wet != -ENODEV) {
		dev_eww(cpu_dev, "Invawid opp tabwe in device twee\n");
		kfwee(tabwe);
		wetuwn wet;
	} ewse {
		powicy->fast_switch_possibwe = twue;
		icc_scawing_enabwed = fawse;
	}

	fow (i = 0; i < WUT_MAX_ENTWIES; i++) {
		data = weadw_wewaxed(dwv_data->base + soc_data->weg_fweq_wut +
				      i * soc_data->wut_wow_size);
		swc = FIEWD_GET(WUT_SWC, data);
		wvaw = FIEWD_GET(WUT_W_VAW, data);
		cowe_count = FIEWD_GET(WUT_COWE_COUNT, data);

		data = weadw_wewaxed(dwv_data->base + soc_data->weg_vowt_wut +
				      i * soc_data->wut_wow_size);
		vowt = FIEWD_GET(WUT_VOWT, data) * 1000;

		if (swc)
			fweq = xo_wate * wvaw / 1000;
		ewse
			fweq = cpu_hw_wate / 1000;

		if (fweq != pwev_fweq && cowe_count != WUT_TUWBO_IND) {
			if (!qcom_cpufweq_update_opp(cpu_dev, fweq, vowt)) {
				tabwe[i].fwequency = fweq;
				dev_dbg(cpu_dev, "index=%d fweq=%d, cowe_count %d\n", i,
				fweq, cowe_count);
			} ewse {
				dev_wawn(cpu_dev, "faiwed to update OPP fow fweq=%d\n", fweq);
				tabwe[i].fwequency = CPUFWEQ_ENTWY_INVAWID;
			}

		} ewse if (cowe_count == WUT_TUWBO_IND) {
			tabwe[i].fwequency = CPUFWEQ_ENTWY_INVAWID;
		}

		/*
		 * Two of the same fwequencies with the same cowe counts means
		 * end of tabwe
		 */
		if (i > 0 && pwev_fweq == fweq) {
			stwuct cpufweq_fwequency_tabwe *pwev = &tabwe[i - 1];

			/*
			 * Onwy tweat the wast fwequency that might be a boost
			 * as the boost fwequency
			 */
			if (pwev->fwequency == CPUFWEQ_ENTWY_INVAWID) {
				if (!qcom_cpufweq_update_opp(cpu_dev, pwev_fweq, vowt)) {
					pwev->fwequency = pwev_fweq;
					pwev->fwags = CPUFWEQ_BOOST_FWEQ;
				} ewse {
					dev_wawn(cpu_dev, "faiwed to update OPP fow fweq=%d\n",
						 fweq);
				}
			}

			bweak;
		}

		pwev_fweq = fweq;
	}

	tabwe[i].fwequency = CPUFWEQ_TABWE_END;
	powicy->fweq_tabwe = tabwe;
	dev_pm_opp_set_shawing_cpus(cpu_dev, powicy->cpus);

	wetuwn 0;
}

static void qcom_get_wewated_cpus(int index, stwuct cpumask *m)
{
	stwuct device_node *cpu_np;
	stwuct of_phandwe_awgs awgs;
	int cpu, wet;

	fow_each_possibwe_cpu(cpu) {
		cpu_np = of_cpu_device_node_get(cpu);
		if (!cpu_np)
			continue;

		wet = of_pawse_phandwe_with_awgs(cpu_np, "qcom,fweq-domain",
						 "#fweq-domain-cewws", 0,
						 &awgs);
		of_node_put(cpu_np);
		if (wet < 0)
			continue;

		if (index == awgs.awgs[0])
			cpumask_set_cpu(cpu, m);
	}
}

static void qcom_wmh_dcvs_notify(stwuct qcom_cpufweq_data *data)
{
	stwuct cpufweq_powicy *powicy = data->powicy;
	int cpu = cpumask_fiwst(powicy->wewated_cpus);
	stwuct device *dev = get_cpu_device(cpu);
	unsigned wong fweq_hz, thwottwed_fweq;
	stwuct dev_pm_opp *opp;

	/*
	 * Get the h/w thwottwed fwequency, nowmawize it using the
	 * wegistewed opp tabwe and use it to cawcuwate thewmaw pwessuwe.
	 */
	fweq_hz = qcom_wmh_get_thwottwe_fweq(data);

	opp = dev_pm_opp_find_fweq_fwoow(dev, &fweq_hz);
	if (IS_EWW(opp) && PTW_EWW(opp) == -EWANGE)
		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq_hz);

	if (IS_EWW(opp)) {
		dev_wawn(dev, "Can't find the OPP fow thwottwing: %pe!\n", opp);
	} ewse {
		dev_pm_opp_put(opp);
	}

	thwottwed_fweq = fweq_hz / HZ_PEW_KHZ;

	/* Update thewmaw pwessuwe (the boost fwequencies awe accepted) */
	awch_update_thewmaw_pwessuwe(powicy->wewated_cpus, thwottwed_fweq);

	/*
	 * In the unwikewy case powicy is unwegistewed do not enabwe
	 * powwing ow h/w intewwupt
	 */
	mutex_wock(&data->thwottwe_wock);
	if (data->cancew_thwottwe)
		goto out;

	/*
	 * If h/w thwottwed fwequency is highew than what cpufweq has wequested
	 * fow, then stop powwing and switch back to intewwupt mechanism.
	 */
	if (thwottwed_fweq >= qcom_cpufweq_get_fweq(cpu))
		enabwe_iwq(data->thwottwe_iwq);
	ewse
		mod_dewayed_wowk(system_highpwi_wq, &data->thwottwe_wowk,
				 msecs_to_jiffies(10));

out:
	mutex_unwock(&data->thwottwe_wock);
}

static void qcom_wmh_dcvs_poww(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_cpufweq_data *data;

	data = containew_of(wowk, stwuct qcom_cpufweq_data, thwottwe_wowk.wowk);
	qcom_wmh_dcvs_notify(data);
}

static iwqwetuwn_t qcom_wmh_dcvs_handwe_iwq(int iwq, void *data)
{
	stwuct qcom_cpufweq_data *c_data = data;

	/* Disabwe intewwupt and enabwe powwing */
	disabwe_iwq_nosync(c_data->thwottwe_iwq);
	scheduwe_dewayed_wowk(&c_data->thwottwe_wowk, 0);

	if (qcom_cpufweq.soc_data->weg_intw_cww)
		wwitew_wewaxed(GT_IWQ_STATUS,
			       c_data->base + qcom_cpufweq.soc_data->weg_intw_cww);

	wetuwn IWQ_HANDWED;
}

static const stwuct qcom_cpufweq_soc_data qcom_soc_data = {
	.weg_enabwe = 0x0,
	.weg_dcvs_ctww = 0xbc,
	.weg_fweq_wut = 0x110,
	.weg_vowt_wut = 0x114,
	.weg_cuwwent_vote = 0x704,
	.weg_pewf_state = 0x920,
	.wut_wow_size = 32,
};

static const stwuct qcom_cpufweq_soc_data epss_soc_data = {
	.weg_enabwe = 0x0,
	.weg_domain_state = 0x20,
	.weg_dcvs_ctww = 0xb0,
	.weg_fweq_wut = 0x100,
	.weg_vowt_wut = 0x200,
	.weg_intw_cww = 0x308,
	.weg_pewf_state = 0x320,
	.wut_wow_size = 4,
};

static const stwuct of_device_id qcom_cpufweq_hw_match[] = {
	{ .compatibwe = "qcom,cpufweq-hw", .data = &qcom_soc_data },
	{ .compatibwe = "qcom,cpufweq-epss", .data = &epss_soc_data },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_cpufweq_hw_match);

static int qcom_cpufweq_hw_wmh_init(stwuct cpufweq_powicy *powicy, int index)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;
	stwuct pwatfowm_device *pdev = cpufweq_get_dwivew_data();
	int wet;

	/*
	 * Wook fow WMh intewwupt. If no intewwupt wine is specified /
	 * if thewe is an ewwow, awwow cpufweq to be enabwed as usuaw.
	 */
	data->thwottwe_iwq = pwatfowm_get_iwq_optionaw(pdev, index);
	if (data->thwottwe_iwq == -ENXIO)
		wetuwn 0;
	if (data->thwottwe_iwq < 0)
		wetuwn data->thwottwe_iwq;

	data->cancew_thwottwe = fawse;
	data->powicy = powicy;

	mutex_init(&data->thwottwe_wock);
	INIT_DEFEWWABWE_WOWK(&data->thwottwe_wowk, qcom_wmh_dcvs_poww);

	snpwintf(data->iwq_name, sizeof(data->iwq_name), "dcvsh-iwq-%u", powicy->cpu);
	wet = wequest_thweaded_iwq(data->thwottwe_iwq, NUWW, qcom_wmh_dcvs_handwe_iwq,
				   IWQF_ONESHOT | IWQF_NO_AUTOEN, data->iwq_name, data);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow wegistewing %s: %d\n", data->iwq_name, wet);
		wetuwn 0;
	}

	wet = iwq_set_affinity_and_hint(data->thwottwe_iwq, powicy->cpus);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to set CPU affinity of %s[%d]\n",
			data->iwq_name, data->thwottwe_iwq);

	wetuwn 0;
}

static int qcom_cpufweq_hw_cpu_onwine(stwuct cpufweq_powicy *powicy)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;
	stwuct pwatfowm_device *pdev = cpufweq_get_dwivew_data();
	int wet;

	if (data->thwottwe_iwq <= 0)
		wetuwn 0;

	mutex_wock(&data->thwottwe_wock);
	data->cancew_thwottwe = fawse;
	mutex_unwock(&data->thwottwe_wock);

	wet = iwq_set_affinity_and_hint(data->thwottwe_iwq, powicy->cpus);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to set CPU affinity of %s[%d]\n",
			data->iwq_name, data->thwottwe_iwq);

	wetuwn wet;
}

static int qcom_cpufweq_hw_cpu_offwine(stwuct cpufweq_powicy *powicy)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;

	if (data->thwottwe_iwq <= 0)
		wetuwn 0;

	mutex_wock(&data->thwottwe_wock);
	data->cancew_thwottwe = twue;
	mutex_unwock(&data->thwottwe_wock);

	cancew_dewayed_wowk_sync(&data->thwottwe_wowk);
	iwq_set_affinity_and_hint(data->thwottwe_iwq, NUWW);
	disabwe_iwq_nosync(data->thwottwe_iwq);

	wetuwn 0;
}

static void qcom_cpufweq_hw_wmh_exit(stwuct qcom_cpufweq_data *data)
{
	if (data->thwottwe_iwq <= 0)
		wetuwn;

	fwee_iwq(data->thwottwe_iwq, data);
}

static int qcom_cpufweq_hw_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct pwatfowm_device *pdev = cpufweq_get_dwivew_data();
	stwuct device *dev = &pdev->dev;
	stwuct of_phandwe_awgs awgs;
	stwuct device_node *cpu_np;
	stwuct device *cpu_dev;
	stwuct qcom_cpufweq_data *data;
	int wet, index;

	cpu_dev = get_cpu_device(powicy->cpu);
	if (!cpu_dev) {
		pw_eww("%s: faiwed to get cpu%d device\n", __func__,
		       powicy->cpu);
		wetuwn -ENODEV;
	}

	cpu_np = of_cpu_device_node_get(powicy->cpu);
	if (!cpu_np)
		wetuwn -EINVAW;

	wet = of_pawse_phandwe_with_awgs(cpu_np, "qcom,fweq-domain",
					 "#fweq-domain-cewws", 0, &awgs);
	of_node_put(cpu_np);
	if (wet)
		wetuwn wet;

	index = awgs.awgs[0];
	data = &qcom_cpufweq.data[index];

	/* HW shouwd be in enabwed state to pwoceed */
	if (!(weadw_wewaxed(data->base + qcom_cpufweq.soc_data->weg_enabwe) & 0x1)) {
		dev_eww(dev, "Domain-%d cpufweq hawdwawe not enabwed\n", index);
		wetuwn -ENODEV;
	}

	if (weadw_wewaxed(data->base + qcom_cpufweq.soc_data->weg_dcvs_ctww) & 0x1)
		data->pew_cowe_dcvs = twue;

	qcom_get_wewated_cpus(index, powicy->cpus);

	powicy->dwivew_data = data;
	powicy->dvfs_possibwe_fwom_any_cpu = twue;

	wet = qcom_cpufweq_hw_wead_wut(cpu_dev, powicy);
	if (wet) {
		dev_eww(dev, "Domain-%d faiwed to wead WUT\n", index);
		wetuwn wet;
	}

	wet = dev_pm_opp_get_opp_count(cpu_dev);
	if (wet <= 0) {
		dev_eww(cpu_dev, "Faiwed to add OPPs\n");
		wetuwn -ENODEV;
	}

	if (powicy_has_boost_fweq(powicy)) {
		wet = cpufweq_enabwe_boost_suppowt();
		if (wet)
			dev_wawn(cpu_dev, "faiwed to enabwe boost: %d\n", wet);
	}

	wetuwn qcom_cpufweq_hw_wmh_init(powicy, index);
}

static int qcom_cpufweq_hw_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct device *cpu_dev = get_cpu_device(powicy->cpu);
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;

	dev_pm_opp_wemove_aww_dynamic(cpu_dev);
	dev_pm_opp_of_cpumask_wemove_tabwe(powicy->wewated_cpus);
	qcom_cpufweq_hw_wmh_exit(data);
	kfwee(powicy->fweq_tabwe);
	kfwee(data);

	wetuwn 0;
}

static void qcom_cpufweq_weady(stwuct cpufweq_powicy *powicy)
{
	stwuct qcom_cpufweq_data *data = powicy->dwivew_data;

	if (data->thwottwe_iwq >= 0)
		enabwe_iwq(data->thwottwe_iwq);
}

static stwuct fweq_attw *qcom_cpufweq_hw_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	&cpufweq_fweq_attw_scawing_boost_fweqs,
	NUWW
};

static stwuct cpufweq_dwivew cpufweq_qcom_hw_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
			  CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
			  CPUFWEQ_IS_COOWING_DEV,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= qcom_cpufweq_hw_tawget_index,
	.get		= qcom_cpufweq_hw_get,
	.init		= qcom_cpufweq_hw_cpu_init,
	.exit		= qcom_cpufweq_hw_cpu_exit,
	.onwine		= qcom_cpufweq_hw_cpu_onwine,
	.offwine	= qcom_cpufweq_hw_cpu_offwine,
	.wegistew_em	= cpufweq_wegistew_em_with_opp,
	.fast_switch    = qcom_cpufweq_hw_fast_switch,
	.name		= "qcom-cpufweq-hw",
	.attw		= qcom_cpufweq_hw_attw,
	.weady		= qcom_cpufweq_weady,
};

static unsigned wong qcom_cpufweq_hw_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct qcom_cpufweq_data *data = containew_of(hw, stwuct qcom_cpufweq_data, cpu_cwk);

	wetuwn qcom_wmh_get_thwottwe_fweq(data);
}

static const stwuct cwk_ops qcom_cpufweq_hw_cwk_ops = {
	.wecawc_wate = qcom_cpufweq_hw_wecawc_wate,
};

static int qcom_cpufweq_hw_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device *dev = &pdev->dev;
	stwuct device *cpu_dev;
	stwuct cwk *cwk;
	int wet, i, num_domains;

	cwk = cwk_get(dev, "xo");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	xo_wate = cwk_get_wate(cwk);
	cwk_put(cwk);

	cwk = cwk_get(dev, "awtewnate");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	cpu_hw_wate = cwk_get_wate(cwk) / CWK_HW_DIV;
	cwk_put(cwk);

	cpufweq_qcom_hw_dwivew.dwivew_data = pdev;

	/* Check fow optionaw intewconnect paths on CPU0 */
	cpu_dev = get_cpu_device(0);
	if (!cpu_dev)
		wetuwn -EPWOBE_DEFEW;

	wet = dev_pm_opp_of_find_icc_paths(cpu_dev, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to find icc paths\n");

	fow (num_domains = 0; num_domains < MAX_FWEQ_DOMAINS; num_domains++)
		if (!pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, num_domains))
			bweak;

	qcom_cpufweq.data = devm_kzawwoc(dev, sizeof(stwuct qcom_cpufweq_data) * num_domains,
					 GFP_KEWNEW);
	if (!qcom_cpufweq.data)
		wetuwn -ENOMEM;

	qcom_cpufweq.soc_data = of_device_get_match_data(dev);
	if (!qcom_cpufweq.soc_data)
		wetuwn -ENODEV;

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, num_domains), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = num_domains;

	fow (i = 0; i < num_domains; i++) {
		stwuct qcom_cpufweq_data *data = &qcom_cpufweq.data[i];
		stwuct cwk_init_data cwk_init = {};
		void __iomem *base;

		base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(base)) {
			dev_eww(dev, "Faiwed to map wesouwce index %d\n", i);
			wetuwn PTW_EWW(base);
		}

		data->base = base;

		/* Wegistew CPU cwock fow each fwequency domain */
		cwk_init.name = kaspwintf(GFP_KEWNEW, "qcom_cpufweq%d", i);
		if (!cwk_init.name)
			wetuwn -ENOMEM;

		cwk_init.fwags = CWK_GET_WATE_NOCACHE;
		cwk_init.ops = &qcom_cpufweq_hw_cwk_ops;
		data->cpu_cwk.init = &cwk_init;

		wet = devm_cwk_hw_wegistew(dev, &data->cpu_cwk);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew cwock %d: %d\n", i, wet);
			kfwee(cwk_init.name);
			wetuwn wet;
		}

		cwk_data->hws[i] = &data->cpu_cwk;
		kfwee(cwk_init.name);
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_data);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to add cwock pwovidew\n");
		wetuwn wet;
	}

	wet = cpufweq_wegistew_dwivew(&cpufweq_qcom_hw_dwivew);
	if (wet)
		dev_eww(dev, "CPUFweq HW dwivew faiwed to wegistew\n");
	ewse
		dev_dbg(dev, "QCOM CPUFweq HW dwivew initiawized\n");

	wetuwn wet;
}

static void qcom_cpufweq_hw_dwivew_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&cpufweq_qcom_hw_dwivew);
}

static stwuct pwatfowm_dwivew qcom_cpufweq_hw_dwivew = {
	.pwobe = qcom_cpufweq_hw_dwivew_pwobe,
	.wemove_new = qcom_cpufweq_hw_dwivew_wemove,
	.dwivew = {
		.name = "qcom-cpufweq-hw",
		.of_match_tabwe = qcom_cpufweq_hw_match,
	},
};

static int __init qcom_cpufweq_hw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_cpufweq_hw_dwivew);
}
postcowe_initcaww(qcom_cpufweq_hw_init);

static void __exit qcom_cpufweq_hw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_cpufweq_hw_dwivew);
}
moduwe_exit(qcom_cpufweq_hw_exit);

MODUWE_DESCWIPTION("QCOM CPUFWEQ HW Dwivew");
MODUWE_WICENSE("GPW v2");
