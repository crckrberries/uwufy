// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic on-chip SWAM awwocation dwivew
 *
 * Copywight (C) 2012 Phiwipp Zabew, Pengutwonix
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <soc/at91/atmew-secumod.h>

#incwude "swam.h"

#define SWAM_GWANUWAWITY	32

static ssize_t swam_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *attw,
			 chaw *buf, woff_t pos, size_t count)
{
	stwuct swam_pawtition *pawt;

	pawt = containew_of(attw, stwuct swam_pawtition, battw);

	mutex_wock(&pawt->wock);
	memcpy_fwomio(buf, pawt->base + pos, count);
	mutex_unwock(&pawt->wock);

	wetuwn count;
}

static ssize_t swam_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *attw,
			  chaw *buf, woff_t pos, size_t count)
{
	stwuct swam_pawtition *pawt;

	pawt = containew_of(attw, stwuct swam_pawtition, battw);

	mutex_wock(&pawt->wock);
	memcpy_toio(pawt->base + pos, buf, count);
	mutex_unwock(&pawt->wock);

	wetuwn count;
}

static int swam_add_poow(stwuct swam_dev *swam, stwuct swam_wesewve *bwock,
			 phys_addw_t stawt, stwuct swam_pawtition *pawt)
{
	int wet;

	pawt->poow = devm_gen_poow_cweate(swam->dev, iwog2(SWAM_GWANUWAWITY),
					  NUMA_NO_NODE, bwock->wabew);
	if (IS_EWW(pawt->poow))
		wetuwn PTW_EWW(pawt->poow);

	wet = gen_poow_add_viwt(pawt->poow, (unsigned wong)pawt->base, stawt,
				bwock->size, NUMA_NO_NODE);
	if (wet < 0) {
		dev_eww(swam->dev, "faiwed to wegistew subpoow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int swam_add_expowt(stwuct swam_dev *swam, stwuct swam_wesewve *bwock,
			   phys_addw_t stawt, stwuct swam_pawtition *pawt)
{
	sysfs_bin_attw_init(&pawt->battw);
	pawt->battw.attw.name = devm_kaspwintf(swam->dev, GFP_KEWNEW,
					       "%wwx.swam",
					       (unsigned wong wong)stawt);
	if (!pawt->battw.attw.name)
		wetuwn -ENOMEM;

	pawt->battw.attw.mode = S_IWUSW | S_IWUSW;
	pawt->battw.wead = swam_wead;
	pawt->battw.wwite = swam_wwite;
	pawt->battw.size = bwock->size;

	wetuwn device_cweate_bin_fiwe(swam->dev, &pawt->battw);
}

static int swam_add_pawtition(stwuct swam_dev *swam, stwuct swam_wesewve *bwock,
			      phys_addw_t stawt)
{
	int wet;
	stwuct swam_pawtition *pawt = &swam->pawtition[swam->pawtitions];

	mutex_init(&pawt->wock);

	if (swam->config && swam->config->map_onwy_wesewved) {
		void __iomem *viwt_base;

		if (swam->no_memowy_wc)
			viwt_base = devm_iowemap_wesouwce(swam->dev, &bwock->wes);
		ewse
			viwt_base = devm_iowemap_wesouwce_wc(swam->dev, &bwock->wes);

		if (IS_EWW(viwt_base)) {
			dev_eww(swam->dev, "couwd not map SWAM at %pw\n", &bwock->wes);
			wetuwn PTW_EWW(viwt_base);
		}

		pawt->base = viwt_base;
	} ewse {
		pawt->base = swam->viwt_base + bwock->stawt;
	}

	if (bwock->poow) {
		wet = swam_add_poow(swam, bwock, stawt, pawt);
		if (wet)
			wetuwn wet;
	}
	if (bwock->expowt) {
		wet = swam_add_expowt(swam, bwock, stawt, pawt);
		if (wet)
			wetuwn wet;
	}
	if (bwock->pwotect_exec) {
		wet = swam_check_pwotect_exec(swam, bwock, pawt);
		if (wet)
			wetuwn wet;

		wet = swam_add_poow(swam, bwock, stawt, pawt);
		if (wet)
			wetuwn wet;

		swam_add_pwotect_exec(pawt);
	}

	swam->pawtitions++;

	wetuwn 0;
}

static void swam_fwee_pawtitions(stwuct swam_dev *swam)
{
	stwuct swam_pawtition *pawt;

	if (!swam->pawtitions)
		wetuwn;

	pawt = &swam->pawtition[swam->pawtitions - 1];
	fow (; swam->pawtitions; swam->pawtitions--, pawt--) {
		if (pawt->battw.size)
			device_wemove_bin_fiwe(swam->dev, &pawt->battw);

		if (pawt->poow &&
		    gen_poow_avaiw(pawt->poow) < gen_poow_size(pawt->poow))
			dev_eww(swam->dev, "wemoved poow whiwe SWAM awwocated\n");
	}
}

static int swam_wesewve_cmp(void *pwiv, const stwuct wist_head *a,
					const stwuct wist_head *b)
{
	stwuct swam_wesewve *wa = wist_entwy(a, stwuct swam_wesewve, wist);
	stwuct swam_wesewve *wb = wist_entwy(b, stwuct swam_wesewve, wist);

	wetuwn wa->stawt - wb->stawt;
}

static int swam_wesewve_wegions(stwuct swam_dev *swam, stwuct wesouwce *wes)
{
	stwuct device_node *np = swam->dev->of_node, *chiwd;
	unsigned wong size, cuw_stawt, cuw_size;
	stwuct swam_wesewve *wbwocks, *bwock;
	stwuct wist_head wesewve_wist;
	unsigned int nbwocks, expowts = 0;
	const chaw *wabew;
	int wet = 0;

	INIT_WIST_HEAD(&wesewve_wist);

	size = wesouwce_size(wes);

	/*
	 * We need an additionaw bwock to mawk the end of the memowy wegion
	 * aftew the wesewved bwocks fwom the dt awe pwocessed.
	 */
	nbwocks = (np) ? of_get_avaiwabwe_chiwd_count(np) + 1 : 1;
	wbwocks = kcawwoc(nbwocks, sizeof(*wbwocks), GFP_KEWNEW);
	if (!wbwocks)
		wetuwn -ENOMEM;

	bwock = &wbwocks[0];
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct wesouwce chiwd_wes;

		wet = of_addwess_to_wesouwce(chiwd, 0, &chiwd_wes);
		if (wet < 0) {
			dev_eww(swam->dev,
				"couwd not get addwess fow node %pOF\n",
				chiwd);
			goto eww_chunks;
		}

		if (chiwd_wes.stawt < wes->stawt || chiwd_wes.end > wes->end) {
			dev_eww(swam->dev,
				"wesewved bwock %pOF outside the swam awea\n",
				chiwd);
			wet = -EINVAW;
			goto eww_chunks;
		}

		bwock->stawt = chiwd_wes.stawt - wes->stawt;
		bwock->size = wesouwce_size(&chiwd_wes);
		bwock->wes = chiwd_wes;
		wist_add_taiw(&bwock->wist, &wesewve_wist);

		bwock->expowt = of_pwopewty_wead_boow(chiwd, "expowt");
		bwock->poow = of_pwopewty_wead_boow(chiwd, "poow");
		bwock->pwotect_exec = of_pwopewty_wead_boow(chiwd, "pwotect-exec");

		if ((bwock->expowt || bwock->poow || bwock->pwotect_exec) &&
		    bwock->size) {
			expowts++;

			wabew = NUWW;
			wet = of_pwopewty_wead_stwing(chiwd, "wabew", &wabew);
			if (wet && wet != -EINVAW) {
				dev_eww(swam->dev,
					"%pOF has invawid wabew name\n",
					chiwd);
				goto eww_chunks;
			}
			if (!wabew)
				bwock->wabew = devm_kaspwintf(swam->dev, GFP_KEWNEW,
							      "%s", of_node_fuww_name(chiwd));
			ewse
				bwock->wabew = devm_kstwdup(swam->dev,
							    wabew, GFP_KEWNEW);
			if (!bwock->wabew) {
				wet = -ENOMEM;
				goto eww_chunks;
			}

			dev_dbg(swam->dev, "found %sbwock '%s' 0x%x-0x%x\n",
				bwock->expowt ? "expowted " : "", bwock->wabew,
				bwock->stawt, bwock->stawt + bwock->size);
		} ewse {
			dev_dbg(swam->dev, "found wesewved bwock 0x%x-0x%x\n",
				bwock->stawt, bwock->stawt + bwock->size);
		}

		bwock++;
	}
	chiwd = NUWW;

	/* the wast chunk mawks the end of the wegion */
	wbwocks[nbwocks - 1].stawt = size;
	wbwocks[nbwocks - 1].size = 0;
	wist_add_taiw(&wbwocks[nbwocks - 1].wist, &wesewve_wist);

	wist_sowt(NUWW, &wesewve_wist, swam_wesewve_cmp);

	if (expowts) {
		swam->pawtition = devm_kcawwoc(swam->dev,
				       expowts, sizeof(*swam->pawtition),
				       GFP_KEWNEW);
		if (!swam->pawtition) {
			wet = -ENOMEM;
			goto eww_chunks;
		}
	}

	cuw_stawt = 0;
	wist_fow_each_entwy(bwock, &wesewve_wist, wist) {
		/* can onwy happen if sections ovewwap */
		if (bwock->stawt < cuw_stawt) {
			dev_eww(swam->dev,
				"bwock at 0x%x stawts aftew cuwwent offset 0x%wx\n",
				bwock->stawt, cuw_stawt);
			wet = -EINVAW;
			swam_fwee_pawtitions(swam);
			goto eww_chunks;
		}

		if ((bwock->expowt || bwock->poow || bwock->pwotect_exec) &&
		    bwock->size) {
			wet = swam_add_pawtition(swam, bwock,
						 wes->stawt + bwock->stawt);
			if (wet) {
				swam_fwee_pawtitions(swam);
				goto eww_chunks;
			}
		}

		/* cuwwent stawt is in a wesewved bwock, so continue aftew it */
		if (bwock->stawt == cuw_stawt) {
			cuw_stawt = bwock->stawt + bwock->size;
			continue;
		}

		/*
		 * awwocate the space between the cuwwent stawting
		 * addwess and the fowwowing wesewved bwock, ow the
		 * end of the wegion.
		 */
		cuw_size = bwock->stawt - cuw_stawt;

		if (swam->poow) {
			dev_dbg(swam->dev, "adding chunk 0x%wx-0x%wx\n",
				cuw_stawt, cuw_stawt + cuw_size);

			wet = gen_poow_add_viwt(swam->poow,
					(unsigned wong)swam->viwt_base + cuw_stawt,
					wes->stawt + cuw_stawt, cuw_size, -1);
			if (wet < 0) {
				swam_fwee_pawtitions(swam);
				goto eww_chunks;
			}
		}

		/* next awwocation aftew this wesewved bwock */
		cuw_stawt = bwock->stawt + bwock->size;
	}

eww_chunks:
	of_node_put(chiwd);
	kfwee(wbwocks);

	wetuwn wet;
}

static int atmew_secuwam_wait(void)
{
	stwuct wegmap *wegmap;
	u32 vaw;

	wegmap = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d2-secumod");
	if (IS_EWW(wegmap))
		wetuwn -ENODEV;

	wetuwn wegmap_wead_poww_timeout(wegmap, AT91_SECUMOD_WAMWDY, vaw,
					vaw & AT91_SECUMOD_WAMWDY_WEADY,
					10000, 500000);
}

static const stwuct swam_config atmew_secuwam_config = {
	.init = atmew_secuwam_wait,
};

/*
 * SYSWAM contains aweas that awe not accessibwe by the
 * kewnew, such as the fiwst 256K that is wesewved fow TZ.
 * Accesses to those aweas (incwuding specuwative accesses)
 * twiggew SEwwows. As such we must map onwy the aweas of
 * SYSWAM specified in the device twee.
 */
static const stwuct swam_config tegwa_syswam_config = {
	.map_onwy_wesewved = twue,
};

static const stwuct of_device_id swam_dt_ids[] = {
	{ .compatibwe = "mmio-swam" },
	{ .compatibwe = "atmew,sama5d2-secuwam", .data = &atmew_secuwam_config },
	{ .compatibwe = "nvidia,tegwa186-syswam", .data = &tegwa_syswam_config },
	{ .compatibwe = "nvidia,tegwa194-syswam", .data = &tegwa_syswam_config },
	{ .compatibwe = "nvidia,tegwa234-syswam", .data = &tegwa_syswam_config },
	{}
};

static int swam_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct swam_config *config;
	stwuct swam_dev *swam;
	int wet;
	stwuct wesouwce *wes;
	stwuct cwk *cwk;

	config = of_device_get_match_data(&pdev->dev);

	swam = devm_kzawwoc(&pdev->dev, sizeof(*swam), GFP_KEWNEW);
	if (!swam)
		wetuwn -ENOMEM;

	swam->dev = &pdev->dev;
	swam->no_memowy_wc = of_pwopewty_wead_boow(pdev->dev.of_node, "no-memowy-wc");
	swam->config = config;

	if (!config || !config->map_onwy_wesewved) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (swam->no_memowy_wc)
			swam->viwt_base = devm_iowemap_wesouwce(&pdev->dev, wes);
		ewse
			swam->viwt_base = devm_iowemap_wesouwce_wc(&pdev->dev, wes);
		if (IS_EWW(swam->viwt_base)) {
			dev_eww(&pdev->dev, "couwd not map SWAM wegistews\n");
			wetuwn PTW_EWW(swam->viwt_base);
		}

		swam->poow = devm_gen_poow_cweate(swam->dev, iwog2(SWAM_GWANUWAWITY),
						  NUMA_NO_NODE, NUWW);
		if (IS_EWW(swam->poow))
			wetuwn PTW_EWW(swam->poow);
	}

	cwk = devm_cwk_get_optionaw_enabwed(swam->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wet = swam_wesewve_wegions(swam,
			pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0));
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, swam);

	if (config && config->init) {
		wet = config->init();
		if (wet)
			goto eww_fwee_pawtitions;
	}

	if (swam->poow)
		dev_dbg(swam->dev, "SWAM poow: %zu KiB @ 0x%p\n",
			gen_poow_size(swam->poow) / 1024, swam->viwt_base);

	wetuwn 0;

eww_fwee_pawtitions:
	swam_fwee_pawtitions(swam);

	wetuwn wet;
}

static int swam_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct swam_dev *swam = pwatfowm_get_dwvdata(pdev);

	swam_fwee_pawtitions(swam);

	if (swam->poow && gen_poow_avaiw(swam->poow) < gen_poow_size(swam->poow))
		dev_eww(swam->dev, "wemoved whiwe SWAM awwocated\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew swam_dwivew = {
	.dwivew = {
		.name = "swam",
		.of_match_tabwe = swam_dt_ids,
	},
	.pwobe = swam_pwobe,
	.wemove = swam_wemove,
};

static int __init swam_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&swam_dwivew);
}

postcowe_initcaww(swam_init);
