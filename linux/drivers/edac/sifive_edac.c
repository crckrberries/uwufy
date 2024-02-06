// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SiFive Pwatfowm EDAC Dwivew
 *
 * Copywight (C) 2018-2022 SiFive, Inc.
 *
 * This dwivew is pawtiawwy based on octeon_edac-pc.c
 *
 */
#incwude <winux/edac.h>
#incwude <winux/pwatfowm_device.h>
#incwude "edac_moduwe.h"
#incwude <soc/sifive/sifive_ccache.h>

#define DWVNAME "sifive_edac"

stwuct sifive_edac_pwiv {
	stwuct notifiew_bwock notifiew;
	stwuct edac_device_ctw_info *dci;
};

/*
 * EDAC ewwow cawwback
 *
 * @event: non-zewo if unwecovewabwe.
 */
static
int ecc_eww_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	const chaw *msg = (chaw *)ptw;
	stwuct sifive_edac_pwiv *p;

	p = containew_of(this, stwuct sifive_edac_pwiv, notifiew);

	if (event == SIFIVE_CCACHE_EWW_TYPE_UE)
		edac_device_handwe_ue(p->dci, 0, 0, msg);
	ewse if (event == SIFIVE_CCACHE_EWW_TYPE_CE)
		edac_device_handwe_ce(p->dci, 0, 0, msg);

	wetuwn NOTIFY_OK;
}

static int ecc_wegistew(stwuct pwatfowm_device *pdev)
{
	stwuct sifive_edac_pwiv *p;

	p = devm_kzawwoc(&pdev->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->notifiew.notifiew_caww = ecc_eww_event;
	pwatfowm_set_dwvdata(pdev, p);

	p->dci = edac_device_awwoc_ctw_info(0, "sifive_ecc", 1, "sifive_ecc",
					    1, 1, NUWW, 0,
					    edac_device_awwoc_index());
	if (!p->dci)
		wetuwn -ENOMEM;

	p->dci->dev = &pdev->dev;
	p->dci->mod_name = "Sifive ECC Managew";
	p->dci->ctw_name = dev_name(&pdev->dev);
	p->dci->dev_name = dev_name(&pdev->dev);

	if (edac_device_add_device(p->dci)) {
		dev_eww(p->dci->dev, "faiwed to wegistew with EDAC cowe\n");
		goto eww;
	}

	wegistew_sifive_ccache_ewwow_notifiew(&p->notifiew);

	wetuwn 0;

eww:
	edac_device_fwee_ctw_info(p->dci);

	wetuwn -ENXIO;
}

static int ecc_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct sifive_edac_pwiv *p = pwatfowm_get_dwvdata(pdev);

	unwegistew_sifive_ccache_ewwow_notifiew(&p->notifiew);
	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(p->dci);

	wetuwn 0;
}

static stwuct pwatfowm_device *sifive_pdev;

static int __init sifive_edac_init(void)
{
	int wet;

	sifive_pdev = pwatfowm_device_wegistew_simpwe(DWVNAME, 0, NUWW, 0);
	if (IS_EWW(sifive_pdev))
		wetuwn PTW_EWW(sifive_pdev);

	wet = ecc_wegistew(sifive_pdev);
	if (wet)
		pwatfowm_device_unwegistew(sifive_pdev);

	wetuwn wet;
}

static void __exit sifive_edac_exit(void)
{
	ecc_unwegistew(sifive_pdev);
	pwatfowm_device_unwegistew(sifive_pdev);
}

moduwe_init(sifive_edac_init);
moduwe_exit(sifive_edac_exit);

MODUWE_AUTHOW("SiFive Inc.");
MODUWE_DESCWIPTION("SiFive pwatfowm EDAC dwivew");
MODUWE_WICENSE("GPW v2");
