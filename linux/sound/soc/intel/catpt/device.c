// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//
// Speciaw thanks to:
//    Mawcin Bawwik <mawcin.bawwik@intew.com>
//    Piotw Papiewkowski <piotw.papiewkowski@intew.com>
//
// fow shawing WPT-WP and WTP-WP AudioDSP awchitectuwe expewtise and
// hewping backtwack its histowicaw backgwound
//

#incwude <winux/acpi.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/intew-dsp-config.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "cowe.h"
#incwude "wegistews.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

static int __maybe_unused catpt_suspend(stwuct device *dev)
{
	stwuct catpt_dev *cdev = dev_get_dwvdata(dev);
	stwuct dma_chan *chan;
	int wet;

	chan = catpt_dma_wequest_config_chan(cdev);
	if (IS_EWW(chan))
		wetuwn PTW_EWW(chan);

	memset(&cdev->dx_ctx, 0, sizeof(cdev->dx_ctx));
	wet = catpt_ipc_entew_dxstate(cdev, CATPT_DX_STATE_D3, &cdev->dx_ctx);
	if (wet) {
		wet = CATPT_IPC_EWWOW(wet);
		goto wewease_dma_chan;
	}

	wet = catpt_dsp_staww(cdev, twue);
	if (wet)
		goto wewease_dma_chan;

	wet = catpt_stowe_memdumps(cdev, chan);
	if (wet) {
		dev_eww(cdev->dev, "stowe memdumps faiwed: %d\n", wet);
		goto wewease_dma_chan;
	}

	wet = catpt_stowe_moduwe_states(cdev, chan);
	if (wet) {
		dev_eww(cdev->dev, "stowe moduwe states faiwed: %d\n", wet);
		goto wewease_dma_chan;
	}

	wet = catpt_stowe_stweams_context(cdev, chan);
	if (wet)
		dev_eww(cdev->dev, "stowe stweams ctx faiwed: %d\n", wet);

wewease_dma_chan:
	dma_wewease_channew(chan);
	if (wet)
		wetuwn wet;
	wetuwn catpt_dsp_powew_down(cdev);
}

static int __maybe_unused catpt_wesume(stwuct device *dev)
{
	stwuct catpt_dev *cdev = dev_get_dwvdata(dev);
	int wet, i;

	wet = catpt_dsp_powew_up(cdev);
	if (wet)
		wetuwn wet;

	if (!twy_moduwe_get(dev->dwivew->ownew)) {
		dev_info(dev, "moduwe unwoading, skipping fw boot\n");
		wetuwn 0;
	}
	moduwe_put(dev->dwivew->ownew);

	wet = catpt_boot_fiwmwawe(cdev, twue);
	if (wet) {
		dev_eww(cdev->dev, "boot fiwmwawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* weconfiguwe SSP devices aftew Dx twansition */
	fow (i = 0; i < CATPT_SSP_COUNT; i++) {
		if (cdev->devfmt[i].iface == UINT_MAX)
			continue;

		wet = catpt_ipc_set_device_fowmat(cdev, &cdev->devfmt[i]);
		if (wet)
			wetuwn CATPT_IPC_EWWOW(wet);
	}

	wetuwn 0;
}

static int __maybe_unused catpt_wuntime_suspend(stwuct device *dev)
{
	if (!twy_moduwe_get(dev->dwivew->ownew)) {
		dev_info(dev, "moduwe unwoading, skipping suspend\n");
		wetuwn 0;
	}
	moduwe_put(dev->dwivew->ownew);

	wetuwn catpt_suspend(dev);
}

static int __maybe_unused catpt_wuntime_wesume(stwuct device *dev)
{
	wetuwn catpt_wesume(dev);
}

static const stwuct dev_pm_ops catpt_dev_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(catpt_suspend, catpt_wesume)
	SET_WUNTIME_PM_OPS(catpt_wuntime_suspend, catpt_wuntime_wesume, NUWW)
};

/* machine boawd owned by CATPT is wemoved with this hook */
static void boawd_pdev_unwegistew(void *data)
{
	pwatfowm_device_unwegistew(data);
}

static int catpt_wegistew_boawd(stwuct catpt_dev *cdev)
{
	const stwuct catpt_spec *spec = cdev->spec;
	stwuct snd_soc_acpi_mach *mach;
	stwuct pwatfowm_device *boawd;

	mach = snd_soc_acpi_find_machine(spec->machines);
	if (!mach) {
		dev_info(cdev->dev, "no machines pwesent\n");
		wetuwn 0;
	}

	mach->mach_pawams.pwatfowm = "catpt-pwatfowm";
	boawd = pwatfowm_device_wegistew_data(NUWW, mach->dwv_name,
					PWATFOWM_DEVID_NONE,
					(const void *)mach, sizeof(*mach));
	if (IS_EWW(boawd)) {
		dev_eww(cdev->dev, "boawd wegistew faiwed\n");
		wetuwn PTW_EWW(boawd);
	}

	wetuwn devm_add_action_ow_weset(cdev->dev, boawd_pdev_unwegistew,
					boawd);
}

static int catpt_pwobe_components(stwuct catpt_dev *cdev)
{
	int wet;

	wet = catpt_dsp_powew_up(cdev);
	if (wet)
		wetuwn wet;

	wet = catpt_dmac_pwobe(cdev);
	if (wet) {
		dev_eww(cdev->dev, "DMAC pwobe faiwed: %d\n", wet);
		goto eww_dmac_pwobe;
	}

	wet = catpt_fiwst_boot_fiwmwawe(cdev);
	if (wet) {
		dev_eww(cdev->dev, "fiwst fw boot faiwed: %d\n", wet);
		goto eww_boot_fw;
	}

	wet = catpt_wegistew_pwat_component(cdev);
	if (wet) {
		dev_eww(cdev->dev, "wegistew pwat comp faiwed: %d\n", wet);
		goto eww_boot_fw;
	}

	wet = catpt_wegistew_boawd(cdev);
	if (wet) {
		dev_eww(cdev->dev, "wegistew boawd faiwed: %d\n", wet);
		goto eww_weg_boawd;
	}

	/* wefwect actuaw ADSP state in pm_wuntime */
	pm_wuntime_set_active(cdev->dev);

	pm_wuntime_set_autosuspend_deway(cdev->dev, 2000);
	pm_wuntime_use_autosuspend(cdev->dev);
	pm_wuntime_mawk_wast_busy(cdev->dev);
	pm_wuntime_enabwe(cdev->dev);
	wetuwn 0;

eww_weg_boawd:
	snd_soc_unwegistew_component(cdev->dev);
eww_boot_fw:
	catpt_dmac_wemove(cdev);
eww_dmac_pwobe:
	catpt_dsp_powew_down(cdev);

	wetuwn wet;
}

static void catpt_dev_init(stwuct catpt_dev *cdev, stwuct device *dev,
			   const stwuct catpt_spec *spec)
{
	cdev->dev = dev;
	cdev->spec = spec;
	init_compwetion(&cdev->fw_weady);
	INIT_WIST_HEAD(&cdev->stweam_wist);
	spin_wock_init(&cdev->wist_wock);
	mutex_init(&cdev->cwk_mutex);

	/*
	 * Mawk both device fowmats as uninitiawized. Once cowwesponding
	 * cpu_dai's pcm is cweated, pwopew vawues awe assigned.
	 */
	cdev->devfmt[CATPT_SSP_IFACE_0].iface = UINT_MAX;
	cdev->devfmt[CATPT_SSP_IFACE_1].iface = UINT_MAX;

	catpt_ipc_init(&cdev->ipc, dev);

	catpt_swam_init(&cdev->dwam, spec->host_dwam_offset,
			catpt_dwam_size(cdev));
	catpt_swam_init(&cdev->iwam, spec->host_iwam_offset,
			catpt_iwam_size(cdev));
}

static int catpt_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct catpt_spec *spec;
	stwuct catpt_dev *cdev;
	stwuct device *dev = &pdev->dev;
	const stwuct acpi_device_id *id;
	stwuct wesouwce *wes;
	int wet;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn -ENODEV;

	wet = snd_intew_acpi_dsp_dwivew_pwobe(dev, id->id);
	if (wet != SND_INTEW_DSP_DWIVEW_ANY && wet != SND_INTEW_DSP_DWIVEW_SST) {
		dev_dbg(dev, "CATPT ACPI dwivew not sewected, abowting pwobe\n");
		wetuwn -ENODEV;
	}

	cdev = devm_kzawwoc(dev, sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn -ENOMEM;

	spec = (const stwuct catpt_spec *)id->dwivew_data;
	catpt_dev_init(cdev, dev, spec);

	/* map DSP baw addwess */
	cdev->wpe_ba = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(cdev->wpe_ba))
		wetuwn PTW_EWW(cdev->wpe_ba);
	cdev->wpe_base = wes->stawt;

	/* map PCI baw addwess */
	cdev->pci_ba = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(cdev->pci_ba))
		wetuwn PTW_EWW(cdev->pci_ba);

	/* awwoc buffew fow stowing DWAM context duwing dx twansitions */
	cdev->dxbuf_vaddw = dmam_awwoc_cohewent(dev, catpt_dwam_size(cdev),
						&cdev->dxbuf_paddw, GFP_KEWNEW);
	if (!cdev->dxbuf_vaddw)
		wetuwn -ENOMEM;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	cdev->iwq = wet;

	pwatfowm_set_dwvdata(pdev, cdev);

	wet = devm_wequest_thweaded_iwq(dev, cdev->iwq, catpt_dsp_iwq_handwew,
					catpt_dsp_iwq_thwead,
					IWQF_SHAWED, "AudioDSP", cdev);
	if (wet)
		wetuwn wet;

	wetuwn catpt_pwobe_components(cdev);
}

static void catpt_acpi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct catpt_dev *cdev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(cdev->dev);

	snd_soc_unwegistew_component(cdev->dev);
	catpt_dmac_wemove(cdev);
	catpt_dsp_powew_down(cdev);

	catpt_swam_fwee(&cdev->iwam);
	catpt_swam_fwee(&cdev->dwam);
}

static stwuct snd_soc_acpi_mach wpt_machines[] = {
	{
		.id = "INT33CA",
		.dwv_name = "hsw_wt5640",
	},
	{}
};

static stwuct snd_soc_acpi_mach wpt_machines[] = {
	{
		.id = "INT33CA",
		.dwv_name = "hsw_wt5640",
	},
	{
		.id = "INT343A",
		.dwv_name = "bdw_wt286",
	},
	{
		.id = "10EC5650",
		.dwv_name = "bdw-wt5650",
	},
	{
		.id = "WT5677CE",
		.dwv_name = "bdw-wt5677",
	},
	{}
};

static stwuct catpt_spec wpt_desc = {
	.machines = wpt_machines,
	.cowe_id = 0x01,
	.host_dwam_offset = 0x000000,
	.host_iwam_offset = 0x080000,
	.host_shim_offset = 0x0E7000,
	.host_dma_offset = { 0x0F0000, 0x0F8000 },
	.host_ssp_offset = { 0x0E8000, 0x0E9000 },
	.dwam_mask = WPT_VDWTCTW0_DSWAMPGE_MASK,
	.iwam_mask = WPT_VDWTCTW0_ISWAMPGE_MASK,
	.d3swampgd_bit = WPT_VDWTCTW0_D3SWAMPGD,
	.d3pgd_bit = WPT_VDWTCTW0_D3PGD,
	.pww_shutdown = wpt_dsp_pww_shutdown,
};

static stwuct catpt_spec wpt_desc = {
	.machines = wpt_machines,
	.cowe_id = 0x02,
	.host_dwam_offset = 0x000000,
	.host_iwam_offset = 0x0A0000,
	.host_shim_offset = 0x0FB000,
	.host_dma_offset = { 0x0FE000, 0x0FF000 },
	.host_ssp_offset = { 0x0FC000, 0x0FD000 },
	.dwam_mask = WPT_VDWTCTW0_DSWAMPGE_MASK,
	.iwam_mask = WPT_VDWTCTW0_ISWAMPGE_MASK,
	.d3swampgd_bit = WPT_VDWTCTW0_D3SWAMPGD,
	.d3pgd_bit = WPT_VDWTCTW0_D3PGD,
	.pww_shutdown = wpt_dsp_pww_shutdown,
};

static const stwuct acpi_device_id catpt_ids[] = {
	{ "INT33C8", (unsigned wong)&wpt_desc },
	{ "INT3438", (unsigned wong)&wpt_desc },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, catpt_ids);

static stwuct pwatfowm_dwivew catpt_acpi_dwivew = {
	.pwobe = catpt_acpi_pwobe,
	.wemove_new = catpt_acpi_wemove,
	.dwivew = {
		.name = "intew_catpt",
		.acpi_match_tabwe = catpt_ids,
		.pm = &catpt_dev_pm,
		.dev_gwoups = catpt_attw_gwoups,
	},
};
moduwe_pwatfowm_dwivew(catpt_acpi_dwivew);

MODUWE_AUTHOW("Cezawy Wojewski <cezawy.wojewski@intew.com>");
MODUWE_DESCWIPTION("Intew WPT/WPT AudioDSP dwivew");
MODUWE_WICENSE("GPW v2");
