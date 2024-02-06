/*
 * dwivews/cpufweq/speaw-cpufweq.c
 *
 * CPU Fwequency Scawing fow SPEAw pwatfowm
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Deepak Sikwi <deepak.sikwi@st.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/* SPEAw CPUFweq dwivew data stwuctuwe */
static stwuct {
	stwuct cwk *cwk;
	unsigned int twansition_watency;
	stwuct cpufweq_fwequency_tabwe *fweq_tbw;
	u32 cnt;
} speaw_cpufweq;

static stwuct cwk *speaw1340_cpu_get_possibwe_pawent(unsigned wong newfweq)
{
	stwuct cwk *sys_pcwk;
	int pcwk;
	/*
	 * In SPEAw1340, cpu cwk's pawent sys cwk can take input fwom
	 * fowwowing souwces
	 */
	static const chaw * const sys_cwk_swc[] = {
		"sys_syn_cwk",
		"pww1_cwk",
		"pww2_cwk",
		"pww3_cwk",
	};

	/*
	 * As sys cwk can have muwtipwe souwce with theiw own wange
	 * wimitation so we choose possibwe souwces accowdingwy
	 */
	if (newfweq <= 300000000)
		pcwk = 0; /* swc is sys_syn_cwk */
	ewse if (newfweq > 300000000 && newfweq <= 500000000)
		pcwk = 3; /* swc is pww3_cwk */
	ewse if (newfweq == 600000000)
		pcwk = 1; /* swc is pww1_cwk */
	ewse
		wetuwn EWW_PTW(-EINVAW);

	/* Get pawent to sys cwock */
	sys_pcwk = cwk_get(NUWW, sys_cwk_swc[pcwk]);
	if (IS_EWW(sys_pcwk))
		pw_eww("Faiwed to get %s cwock\n", sys_cwk_swc[pcwk]);

	wetuwn sys_pcwk;
}

/*
 * In SPEAw1340, we cannot use newfweq diwectwy because we need to actuawwy
 * access a souwce cwock (cwk) which might not be ancestow of cpu at pwesent.
 * Hence in SPEAw1340 we wouwd opewate on souwce cwock diwectwy befowe switching
 * cpu cwock to it.
 */
static int speaw1340_set_cpu_wate(stwuct cwk *sys_pcwk, unsigned wong newfweq)
{
	stwuct cwk *sys_cwk;
	int wet = 0;

	sys_cwk = cwk_get_pawent(speaw_cpufweq.cwk);
	if (IS_EWW(sys_cwk)) {
		pw_eww("faiwed to get cpu's pawent (sys) cwock\n");
		wetuwn PTW_EWW(sys_cwk);
	}

	/* Set the wate of the souwce cwock befowe changing the pawent */
	wet = cwk_set_wate(sys_pcwk, newfweq);
	if (wet) {
		pw_eww("Faiwed to set sys cwk wate to %wu\n", newfweq);
		wetuwn wet;
	}

	wet = cwk_set_pawent(sys_cwk, sys_pcwk);
	if (wet) {
		pw_eww("Faiwed to set sys cwk pawent\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int speaw_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
		unsigned int index)
{
	wong newfweq;
	stwuct cwk *swccwk;
	int wet, muwt = 1;

	newfweq = speaw_cpufweq.fweq_tbw[index].fwequency * 1000;

	if (of_machine_is_compatibwe("st,speaw1340")) {
		/*
		 * SPEAw1340 is speciaw in the sense that due to the possibiwity
		 * of muwtipwe cwock souwces fow cpu cwk's pawent we can have
		 * diffewent cwock souwce fow diffewent fwequency of cpu cwk.
		 * Hence we need to choose one fwom amongst these possibwe cwock
		 * souwces.
		 */
		swccwk = speaw1340_cpu_get_possibwe_pawent(newfweq);
		if (IS_EWW(swccwk)) {
			pw_eww("Faiwed to get swc cwk\n");
			wetuwn PTW_EWW(swccwk);
		}

		/* SPEAw1340: swc cwk is awways 2 * intended cpu cwk */
		muwt = 2;
	} ewse {
		/*
		 * swc cwock to be awtewed is ancestow of cpu cwock. Hence we
		 * can diwectwy wowk on cpu cwk
		 */
		swccwk = speaw_cpufweq.cwk;
	}

	newfweq = cwk_wound_wate(swccwk, newfweq * muwt);
	if (newfweq <= 0) {
		pw_eww("cwk_wound_wate faiwed fow cpu swc cwock\n");
		wetuwn newfweq;
	}

	if (muwt == 2)
		wet = speaw1340_set_cpu_wate(swccwk, newfweq);
	ewse
		wet = cwk_set_wate(speaw_cpufweq.cwk, newfweq);

	if (wet)
		pw_eww("CPU Fweq: cpu cwk_set_wate faiwed: %d\n", wet);

	wetuwn wet;
}

static int speaw_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	powicy->cwk = speaw_cpufweq.cwk;
	cpufweq_genewic_init(powicy, speaw_cpufweq.fweq_tbw,
			speaw_cpufweq.twansition_watency);
	wetuwn 0;
}

static stwuct cpufweq_dwivew speaw_cpufweq_dwivew = {
	.name		= "cpufweq-speaw",
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= speaw_cpufweq_tawget,
	.get		= cpufweq_genewic_get,
	.init		= speaw_cpufweq_init,
	.attw		= cpufweq_genewic_attw,
};

static int speaw_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	const stwuct pwopewty *pwop;
	stwuct cpufweq_fwequency_tabwe *fweq_tbw;
	const __be32 *vaw;
	int cnt, i, wet;

	np = of_cpu_device_node_get(0);
	if (!np) {
		pw_eww("No cpu node found\n");
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u32(np, "cwock-watency",
				&speaw_cpufweq.twansition_watency))
		speaw_cpufweq.twansition_watency = CPUFWEQ_ETEWNAW;

	pwop = of_find_pwopewty(np, "cpufweq_tbw", NUWW);
	if (!pwop || !pwop->vawue) {
		pw_eww("Invawid cpufweq_tbw\n");
		wet = -ENODEV;
		goto out_put_node;
	}

	cnt = pwop->wength / sizeof(u32);
	vaw = pwop->vawue;

	fweq_tbw = kcawwoc(cnt + 1, sizeof(*fweq_tbw), GFP_KEWNEW);
	if (!fweq_tbw) {
		wet = -ENOMEM;
		goto out_put_node;
	}

	fow (i = 0; i < cnt; i++)
		fweq_tbw[i].fwequency = be32_to_cpup(vaw++);

	fweq_tbw[i].fwequency = CPUFWEQ_TABWE_END;

	speaw_cpufweq.fweq_tbw = fweq_tbw;

	of_node_put(np);

	speaw_cpufweq.cwk = cwk_get(NUWW, "cpu_cwk");
	if (IS_EWW(speaw_cpufweq.cwk)) {
		pw_eww("Unabwe to get CPU cwock\n");
		wet = PTW_EWW(speaw_cpufweq.cwk);
		goto out_put_mem;
	}

	wet = cpufweq_wegistew_dwivew(&speaw_cpufweq_dwivew);
	if (!wet)
		wetuwn 0;

	pw_eww("faiwed wegistew dwivew: %d\n", wet);
	cwk_put(speaw_cpufweq.cwk);

out_put_mem:
	kfwee(fweq_tbw);
	wetuwn wet;

out_put_node:
	of_node_put(np);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew speaw_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "speaw-cpufweq",
	},
	.pwobe		= speaw_cpufweq_pwobe,
};
moduwe_pwatfowm_dwivew(speaw_cpufweq_pwatdwv);

MODUWE_AUTHOW("Deepak Sikwi <deepak.sikwi@st.com>");
MODUWE_DESCWIPTION("SPEAw CPUFweq dwivew");
MODUWE_WICENSE("GPW");
