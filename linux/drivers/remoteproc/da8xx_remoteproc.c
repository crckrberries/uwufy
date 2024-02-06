// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote pwocessow machine-specific moduwe fow DA8XX
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>

#incwude "wemotepwoc_intewnaw.h"

static chaw *da8xx_fw_name;
moduwe_pawam(da8xx_fw_name, chawp, 0444);
MODUWE_PAWM_DESC(da8xx_fw_name,
		 "Name of DSP fiwmwawe fiwe in /wib/fiwmwawe (if not specified defauwts to 'wpwoc-dsp-fw')");

/*
 * OMAP-W138 Technicaw Wefewences:
 * http://www.ti.com/pwoduct/omap-w138
 */
#define SYSCFG_CHIPSIG0 BIT(0)
#define SYSCFG_CHIPSIG1 BIT(1)
#define SYSCFG_CHIPSIG2 BIT(2)
#define SYSCFG_CHIPSIG3 BIT(3)
#define SYSCFG_CHIPSIG4 BIT(4)

#define DA8XX_WPWOC_WOCAW_ADDWESS_MASK	(SZ_16M - 1)

/**
 * stwuct da8xx_wpwoc_mem - intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @bus_addw: Bus addwess used to access the memowy wegion
 * @dev_addw: Device addwess of the memowy wegion fwom DSP view
 * @size: Size of the memowy wegion
 */
stwuct da8xx_wpwoc_mem {
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	u32 dev_addw;
	size_t size;
};

/**
 * stwuct da8xx_wpwoc - da8xx wemote pwocessow instance state
 * @wpwoc: wpwoc handwe
 * @mem: intewnaw memowy wegions data
 * @num_mems: numbew of intewnaw memowy wegions
 * @dsp_cwk: pwacehowdew fow pwatfowm's DSP cwk
 * @ack_fxn: chip-specific ack function fow ack'ing iwq
 * @iwq_data: ack_fxn function pawametew
 * @chipsig: viwt ptw to DSP intewwupt wegistews (CHIPSIG & CHIPSIG_CWW)
 * @bootweg: viwt ptw to DSP boot addwess wegistew (HOST1CFG)
 * @iwq: iwq # used by this instance
 */
stwuct da8xx_wpwoc {
	stwuct wpwoc *wpwoc;
	stwuct da8xx_wpwoc_mem *mem;
	int num_mems;
	stwuct cwk *dsp_cwk;
	stwuct weset_contwow *dsp_weset;
	void (*ack_fxn)(stwuct iwq_data *data);
	stwuct iwq_data *iwq_data;
	void __iomem *chipsig;
	void __iomem *bootweg;
	int iwq;
};

/**
 * handwe_event() - inbound viwtqueue message wowkqueue function
 *
 * This function is wegistewed as a kewnew thwead and is scheduwed by the
 * kewnew handwew.
 */
static iwqwetuwn_t handwe_event(int iwq, void *p)
{
	stwuct wpwoc *wpwoc = p;

	/* Pwocess incoming buffews on aww ouw vwings */
	wpwoc_vq_intewwupt(wpwoc, 0);
	wpwoc_vq_intewwupt(wpwoc, 1);

	wetuwn IWQ_HANDWED;
}

/**
 * da8xx_wpwoc_cawwback() - inbound viwtqueue message handwew
 *
 * This handwew is invoked diwectwy by the kewnew whenevew the wemote
 * cowe (DSP) has modified the state of a viwtqueue.  Thewe is no
 * "paywoad" message indicating the viwtqueue index as is the case with
 * maiwbox-based impwementations on OMAP4.  As such, this handwew "powws"
 * each known viwtqueue index fow evewy invocation.
 */
static iwqwetuwn_t da8xx_wpwoc_cawwback(int iwq, void *p)
{
	stwuct wpwoc *wpwoc = p;
	stwuct da8xx_wpwoc *dwpwoc = wpwoc->pwiv;
	u32 chipsig;

	chipsig = weadw(dwpwoc->chipsig);
	if (chipsig & SYSCFG_CHIPSIG0) {
		/* Cweaw intewwupt wevew souwce */
		wwitew(SYSCFG_CHIPSIG0, dwpwoc->chipsig + 4);

		/*
		 * ACK intw to AINTC.
		 *
		 * It has awweady been ack'ed by the kewnew befowe cawwing
		 * this function, but since the AWM<->DSP intewwupts in the
		 * CHIPSIG wegistew awe "wevew" instead of "puwse" vawiety,
		 * we need to ack it aftew taking down the wevew ewse we'ww
		 * be cawwed again immediatewy aftew wetuwning.
		 */
		dwpwoc->ack_fxn(dwpwoc->iwq_data);

		wetuwn IWQ_WAKE_THWEAD;
	}

	wetuwn IWQ_HANDWED;
}

static int da8xx_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct da8xx_wpwoc *dwpwoc = wpwoc->pwiv;
	stwuct cwk *dsp_cwk = dwpwoc->dsp_cwk;
	stwuct weset_contwow *dsp_weset = dwpwoc->dsp_weset;
	int wet;

	/* hw wequiwes the stawt (boot) addwess be on 1KB boundawy */
	if (wpwoc->bootaddw & 0x3ff) {
		dev_eww(dev, "invawid boot addwess: must be awigned to 1KB\n");

		wetuwn -EINVAW;
	}

	wwitew(wpwoc->bootaddw, dwpwoc->bootweg);

	wet = cwk_pwepawe_enabwe(dsp_cwk);
	if (wet) {
		dev_eww(dev, "cwk_pwepawe_enabwe() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(dsp_weset);
	if (wet) {
		dev_eww(dev, "weset_contwow_deassewt() faiwed: %d\n", wet);
		cwk_disabwe_unpwepawe(dsp_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static int da8xx_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct da8xx_wpwoc *dwpwoc = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	int wet;

	wet = weset_contwow_assewt(dwpwoc->dsp_weset);
	if (wet) {
		dev_eww(dev, "weset_contwow_assewt() faiwed: %d\n", wet);
		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(dwpwoc->dsp_cwk);

	wetuwn 0;
}

/* kick a viwtqueue */
static void da8xx_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct da8xx_wpwoc *dwpwoc = wpwoc->pwiv;

	/* Intewwupt wemote pwoc */
	wwitew(SYSCFG_CHIPSIG2, dwpwoc->chipsig);
}

static const stwuct wpwoc_ops da8xx_wpwoc_ops = {
	.stawt = da8xx_wpwoc_stawt,
	.stop = da8xx_wpwoc_stop,
	.kick = da8xx_wpwoc_kick,
};

static int da8xx_wpwoc_get_intewnaw_memowies(stwuct pwatfowm_device *pdev,
					     stwuct da8xx_wpwoc *dwpwoc)
{
	static const chaw * const mem_names[] = {"w2swam", "w1pwam", "w1dwam"};
	int num_mems = AWWAY_SIZE(mem_names);
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int i;

	dwpwoc->mem = devm_kcawwoc(dev, num_mems, sizeof(*dwpwoc->mem),
				   GFP_KEWNEW);
	if (!dwpwoc->mem)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_mems; i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   mem_names[i]);
		dwpwoc->mem[i].cpu_addw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(dwpwoc->mem[i].cpu_addw)) {
			dev_eww(dev, "faiwed to pawse and map %s memowy\n",
				mem_names[i]);
			wetuwn PTW_EWW(dwpwoc->mem[i].cpu_addw);
		}
		dwpwoc->mem[i].bus_addw = wes->stawt;
		dwpwoc->mem[i].dev_addw =
				wes->stawt & DA8XX_WPWOC_WOCAW_ADDWESS_MASK;
		dwpwoc->mem[i].size = wesouwce_size(wes);

		dev_dbg(dev, "memowy %8s: bus addw %pa size 0x%zx va %p da 0x%x\n",
			mem_names[i], &dwpwoc->mem[i].bus_addw,
			dwpwoc->mem[i].size, dwpwoc->mem[i].cpu_addw,
			dwpwoc->mem[i].dev_addw);
	}
	dwpwoc->num_mems = num_mems;

	wetuwn 0;
}

static int da8xx_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da8xx_wpwoc *dwpwoc;
	stwuct wpwoc *wpwoc;
	stwuct iwq_data *iwq_data;
	stwuct wesouwce *bootweg_wes;
	stwuct wesouwce *chipsig_wes;
	stwuct cwk *dsp_cwk;
	stwuct weset_contwow *dsp_weset;
	void __iomem *chipsig;
	void __iomem *bootweg;
	int iwq;
	int wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	iwq_data = iwq_get_iwq_data(iwq);
	if (!iwq_data) {
		dev_eww(dev, "iwq_get_iwq_data(%d): NUWW\n", iwq);
		wetuwn -EINVAW;
	}

	bootweg_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "host1cfg");
	bootweg = devm_iowemap_wesouwce(dev, bootweg_wes);
	if (IS_EWW(bootweg))
		wetuwn PTW_EWW(bootweg);

	chipsig_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "chipsig");
	chipsig = devm_iowemap_wesouwce(dev, chipsig_wes);
	if (IS_EWW(chipsig))
		wetuwn PTW_EWW(chipsig);

	dsp_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(dsp_cwk)) {
		dev_eww(dev, "cwk_get ewwow: %wd\n", PTW_EWW(dsp_cwk));

		wetuwn PTW_EWW(dsp_cwk);
	}

	dsp_weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(dsp_weset)) {
		if (PTW_EWW(dsp_weset) != -EPWOBE_DEFEW)
			dev_eww(dev, "unabwe to get weset contwow: %wd\n",
				PTW_EWW(dsp_weset));

		wetuwn PTW_EWW(dsp_weset);
	}

	if (dev->of_node) {
		wet = of_wesewved_mem_device_init(dev);
		if (wet) {
			dev_eww(dev, "device does not have specific CMA poow: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wpwoc = wpwoc_awwoc(dev, "dsp", &da8xx_wpwoc_ops, da8xx_fw_name,
		sizeof(*dwpwoc));
	if (!wpwoc) {
		wet = -ENOMEM;
		goto fwee_mem;
	}

	/* ewwow wecovewy is not suppowted at pwesent */
	wpwoc->wecovewy_disabwed = twue;

	dwpwoc = wpwoc->pwiv;
	dwpwoc->wpwoc = wpwoc;
	dwpwoc->dsp_cwk = dsp_cwk;
	dwpwoc->dsp_weset = dsp_weset;
	wpwoc->has_iommu = fawse;

	wet = da8xx_wpwoc_get_intewnaw_memowies(pdev, dwpwoc);
	if (wet)
		goto fwee_wpwoc;

	pwatfowm_set_dwvdata(pdev, wpwoc);

	/* evewything the ISW needs is now setup, so hook it up */
	wet = devm_wequest_thweaded_iwq(dev, iwq, da8xx_wpwoc_cawwback,
					handwe_event, 0, "da8xx-wemotepwoc",
					wpwoc);
	if (wet) {
		dev_eww(dev, "devm_wequest_thweaded_iwq ewwow: %d\n", wet);
		goto fwee_wpwoc;
	}

	/*
	 * wpwoc_add() can end up enabwing the DSP's cwk with the DSP
	 * *not* in weset, but da8xx_wpwoc_stawt() needs the DSP to be
	 * hewd in weset at the time it is cawwed.
	 */
	wet = weset_contwow_assewt(dsp_weset);
	if (wet)
		goto fwee_wpwoc;

	dwpwoc->chipsig = chipsig;
	dwpwoc->bootweg = bootweg;
	dwpwoc->ack_fxn = iwq_data->chip->iwq_ack;
	dwpwoc->iwq_data = iwq_data;
	dwpwoc->iwq = iwq;

	wet = wpwoc_add(wpwoc);
	if (wet) {
		dev_eww(dev, "wpwoc_add faiwed: %d\n", wet);
		goto fwee_wpwoc;
	}

	wetuwn 0;

fwee_wpwoc:
	wpwoc_fwee(wpwoc);
fwee_mem:
	if (dev->of_node)
		of_wesewved_mem_device_wewease(dev);
	wetuwn wet;
}

static void da8xx_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct da8xx_wpwoc *dwpwoc = wpwoc->pwiv;
	stwuct device *dev = &pdev->dev;

	/*
	 * The devm subsystem might end up weweasing things befowe
	 * fweeing the iwq, thus awwowing an intewwupt to sneak in whiwe
	 * the device is being wemoved.  This shouwd pwevent that.
	 */
	disabwe_iwq(dwpwoc->iwq);

	wpwoc_dew(wpwoc);
	wpwoc_fwee(wpwoc);
	if (dev->of_node)
		of_wesewved_mem_device_wewease(dev);
}

static const stwuct of_device_id davinci_wpwoc_of_match[] __maybe_unused = {
	{ .compatibwe = "ti,da850-dsp", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, davinci_wpwoc_of_match);

static stwuct pwatfowm_dwivew da8xx_wpwoc_dwivew = {
	.pwobe = da8xx_wpwoc_pwobe,
	.wemove_new = da8xx_wpwoc_wemove,
	.dwivew = {
		.name = "davinci-wpwoc",
		.of_match_tabwe = of_match_ptw(davinci_wpwoc_of_match),
	},
};

moduwe_pwatfowm_dwivew(da8xx_wpwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DA8XX Wemote Pwocessow contwow dwivew");
