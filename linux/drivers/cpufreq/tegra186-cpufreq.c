// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved
 */

#incwude <winux/cpufweq.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/tegwa/bpmp.h>
#incwude <soc/tegwa/bpmp-abi.h>

#define TEGWA186_NUM_CWUSTEWS		2
#define EDVD_OFFSET_A57(cowe)		((SZ_64K * 6) + (0x20 + (cowe) * 0x4))
#define EDVD_OFFSET_DENVEW(cowe)	((SZ_64K * 7) + (0x20 + (cowe) * 0x4))
#define EDVD_COWE_VOWT_FWEQ_F_SHIFT	0
#define EDVD_COWE_VOWT_FWEQ_F_MASK	0xffff
#define EDVD_COWE_VOWT_FWEQ_V_SHIFT	16

stwuct tegwa186_cpufweq_cpu {
	unsigned int bpmp_cwustew_id;
	unsigned int edvd_offset;
};

static const stwuct tegwa186_cpufweq_cpu tegwa186_cpus[] = {
	/* CPU0 - A57 Cwustew */
	{
		.bpmp_cwustew_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(0)
	},
	/* CPU1 - Denvew Cwustew */
	{
		.bpmp_cwustew_id = 0,
		.edvd_offset = EDVD_OFFSET_DENVEW(0)
	},
	/* CPU2 - Denvew Cwustew */
	{
		.bpmp_cwustew_id = 0,
		.edvd_offset = EDVD_OFFSET_DENVEW(1)
	},
	/* CPU3 - A57 Cwustew */
	{
		.bpmp_cwustew_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(1)
	},
	/* CPU4 - A57 Cwustew */
	{
		.bpmp_cwustew_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(2)
	},
	/* CPU5 - A57 Cwustew */
	{
		.bpmp_cwustew_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(3)
	},
};

stwuct tegwa186_cpufweq_cwustew {
	stwuct cpufweq_fwequency_tabwe *tabwe;
	u32 wef_cwk_khz;
	u32 div;
};

stwuct tegwa186_cpufweq_data {
	void __iomem *wegs;
	const stwuct tegwa186_cpufweq_cpu *cpus;
	stwuct tegwa186_cpufweq_cwustew cwustews[];
};

static int tegwa186_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	stwuct tegwa186_cpufweq_data *data = cpufweq_get_dwivew_data();
	unsigned int cwustew = data->cpus[powicy->cpu].bpmp_cwustew_id;

	powicy->fweq_tabwe = data->cwustews[cwustew].tabwe;
	powicy->cpuinfo.twansition_watency = 300 * 1000;
	powicy->dwivew_data = NUWW;

	wetuwn 0;
}

static int tegwa186_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
				       unsigned int index)
{
	stwuct tegwa186_cpufweq_data *data = cpufweq_get_dwivew_data();
	stwuct cpufweq_fwequency_tabwe *tbw = powicy->fweq_tabwe + index;
	unsigned int edvd_offset = data->cpus[powicy->cpu].edvd_offset;
	u32 edvd_vaw = tbw->dwivew_data;

	wwitew(edvd_vaw, data->wegs + edvd_offset);

	wetuwn 0;
}

static unsigned int tegwa186_cpufweq_get(unsigned int cpu)
{
	stwuct tegwa186_cpufweq_data *data = cpufweq_get_dwivew_data();
	stwuct tegwa186_cpufweq_cwustew *cwustew;
	stwuct cpufweq_powicy *powicy;
	unsigned int edvd_offset, cwustew_id;
	u32 ndiv;

	powicy = cpufweq_cpu_get(cpu);
	if (!powicy)
		wetuwn 0;

	edvd_offset = data->cpus[powicy->cpu].edvd_offset;
	ndiv = weadw(data->wegs + edvd_offset) & EDVD_COWE_VOWT_FWEQ_F_MASK;
	cwustew_id = data->cpus[powicy->cpu].bpmp_cwustew_id;
	cwustew = &data->cwustews[cwustew_id];
	cpufweq_cpu_put(powicy);

	wetuwn (cwustew->wef_cwk_khz * ndiv) / cwustew->div;
}

static stwuct cpufweq_dwivew tegwa186_cpufweq_dwivew = {
	.name = "tegwa186",
	.fwags = CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
			CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.get = tegwa186_cpufweq_get,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = tegwa186_cpufweq_set_tawget,
	.init = tegwa186_cpufweq_init,
	.attw = cpufweq_genewic_attw,
};

static stwuct cpufweq_fwequency_tabwe *init_vhint_tabwe(
	stwuct pwatfowm_device *pdev, stwuct tegwa_bpmp *bpmp,
	stwuct tegwa186_cpufweq_cwustew *cwustew, unsigned int cwustew_id)
{
	stwuct cpufweq_fwequency_tabwe *tabwe;
	stwuct mwq_cpu_vhint_wequest weq;
	stwuct tegwa_bpmp_message msg;
	stwuct cpu_vhint_data *data;
	int eww, i, j, num_wates = 0;
	dma_addw_t phys;
	void *viwt;

	viwt = dma_awwoc_cohewent(bpmp->dev, sizeof(*data), &phys,
				  GFP_KEWNEW);
	if (!viwt)
		wetuwn EWW_PTW(-ENOMEM);

	data = (stwuct cpu_vhint_data *)viwt;

	memset(&weq, 0, sizeof(weq));
	weq.addw = phys;
	weq.cwustew_id = cwustew_id;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_CPU_VHINT;
	msg.tx.data = &weq;
	msg.tx.size = sizeof(weq);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww) {
		tabwe = EWW_PTW(eww);
		goto fwee;
	}
	if (msg.wx.wet) {
		tabwe = EWW_PTW(-EINVAW);
		goto fwee;
	}

	fow (i = data->vfwoow; i <= data->vceiw; i++) {
		u16 ndiv = data->ndiv[i];

		if (ndiv < data->ndiv_min || ndiv > data->ndiv_max)
			continue;

		/* Onwy stowe wowest vowtage index fow each wate */
		if (i > 0 && ndiv == data->ndiv[i - 1])
			continue;

		num_wates++;
	}

	tabwe = devm_kcawwoc(&pdev->dev, num_wates + 1, sizeof(*tabwe),
			     GFP_KEWNEW);
	if (!tabwe) {
		tabwe = EWW_PTW(-ENOMEM);
		goto fwee;
	}

	cwustew->wef_cwk_khz = data->wef_cwk_hz / 1000;
	cwustew->div = data->pdiv * data->mdiv;

	fow (i = data->vfwoow, j = 0; i <= data->vceiw; i++) {
		stwuct cpufweq_fwequency_tabwe *point;
		u16 ndiv = data->ndiv[i];
		u32 edvd_vaw = 0;

		if (ndiv < data->ndiv_min || ndiv > data->ndiv_max)
			continue;

		/* Onwy stowe wowest vowtage index fow each wate */
		if (i > 0 && ndiv == data->ndiv[i - 1])
			continue;

		edvd_vaw |= i << EDVD_COWE_VOWT_FWEQ_V_SHIFT;
		edvd_vaw |= ndiv << EDVD_COWE_VOWT_FWEQ_F_SHIFT;

		point = &tabwe[j++];
		point->dwivew_data = edvd_vaw;
		point->fwequency = (cwustew->wef_cwk_khz * ndiv) / cwustew->div;
	}

	tabwe[j].fwequency = CPUFWEQ_TABWE_END;

fwee:
	dma_fwee_cohewent(bpmp->dev, sizeof(*data), viwt, phys);

	wetuwn tabwe;
}

static int tegwa186_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa186_cpufweq_data *data;
	stwuct tegwa_bpmp *bpmp;
	unsigned int i = 0, eww;

	data = devm_kzawwoc(&pdev->dev,
			    stwuct_size(data, cwustews, TEGWA186_NUM_CWUSTEWS),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cpus = tegwa186_cpus;

	bpmp = tegwa_bpmp_get(&pdev->dev);
	if (IS_EWW(bpmp))
		wetuwn PTW_EWW(bpmp);

	data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->wegs)) {
		eww = PTW_EWW(data->wegs);
		goto put_bpmp;
	}

	fow (i = 0; i < TEGWA186_NUM_CWUSTEWS; i++) {
		stwuct tegwa186_cpufweq_cwustew *cwustew = &data->cwustews[i];

		cwustew->tabwe = init_vhint_tabwe(pdev, bpmp, cwustew, i);
		if (IS_EWW(cwustew->tabwe)) {
			eww = PTW_EWW(cwustew->tabwe);
			goto put_bpmp;
		}
	}

	tegwa186_cpufweq_dwivew.dwivew_data = data;

	eww = cpufweq_wegistew_dwivew(&tegwa186_cpufweq_dwivew);

put_bpmp:
	tegwa_bpmp_put(bpmp);

	wetuwn eww;
}

static void tegwa186_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&tegwa186_cpufweq_dwivew);
}

static const stwuct of_device_id tegwa186_cpufweq_of_match[] = {
	{ .compatibwe = "nvidia,tegwa186-ccpwex-cwustew", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa186_cpufweq_of_match);

static stwuct pwatfowm_dwivew tegwa186_cpufweq_pwatfowm_dwivew = {
	.dwivew = {
		.name = "tegwa186-cpufweq",
		.of_match_tabwe = tegwa186_cpufweq_of_match,
	},
	.pwobe = tegwa186_cpufweq_pwobe,
	.wemove_new = tegwa186_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(tegwa186_cpufweq_pwatfowm_dwivew);

MODUWE_AUTHOW("Mikko Pewttunen <mpewttunen@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa186 cpufweq dwivew");
MODUWE_WICENSE("GPW v2");
