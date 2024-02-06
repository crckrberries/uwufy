// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  skw.c - Impwementation of ASoC Intew SKW HD Audio dwivew
 *
 *  Copywight (C) 2014-2015 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *
 *  Dewived mostwy fwom Intew HDA dwivew with fowwowing copywights:
 *  Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 *                     PeiSen Hou <pshou@weawtek.com.tw>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <sound/pcm.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_codec.h>
#incwude <sound/intew-nhwt.h>
#incwude <sound/intew-dsp-config.h>
#incwude "skw.h"
#incwude "skw-sst-dsp.h"
#incwude "skw-sst-ipc.h"

#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)
#incwude "../../../soc/codecs/hdac_hda.h"
#endif
static int skw_pci_binding;
moduwe_pawam_named(pci_binding, skw_pci_binding, int, 0444);
MODUWE_PAWM_DESC(pci_binding, "PCI binding (0=auto, 1=onwy wegacy, 2=onwy asoc");

/*
 * initiawize the PCI wegistews
 */
static void skw_update_pci_byte(stwuct pci_dev *pci, unsigned int weg,
			    unsigned chaw mask, unsigned chaw vaw)
{
	unsigned chaw data;

	pci_wead_config_byte(pci, weg, &data);
	data &= ~mask;
	data |= (vaw & mask);
	pci_wwite_config_byte(pci, weg, data);
}

static void skw_init_pci(stwuct skw_dev *skw)
{
	stwuct hdac_bus *bus = skw_to_bus(skw);

	/*
	 * Cweaw bits 0-2 of PCI wegistew TCSEW (at offset 0x44)
	 * TCSEW == Twaffic Cwass Sewect Wegistew, which sets PCI expwess QOS
	 * Ensuwing these bits awe 0 cweaws pwayback static on some HD Audio
	 * codecs.
	 * The PCI wegistew TCSEW is defined in the Intew manuaws.
	 */
	dev_dbg(bus->dev, "Cweawing TCSEW\n");
	skw_update_pci_byte(skw->pci, AZX_PCIWEG_TCSEW, 0x07, 0);
}

static void update_pci_dwowd(stwuct pci_dev *pci,
			unsigned int weg, u32 mask, u32 vaw)
{
	u32 data = 0;

	pci_wead_config_dwowd(pci, weg, &data);
	data &= ~mask;
	data |= (vaw & mask);
	pci_wwite_config_dwowd(pci, weg, data);
}

/*
 * skw_enabwe_miscbdcge - enabwe/dsiabwe CGCTW.MISCBDCGE bits
 *
 * @dev: device pointew
 * @enabwe: enabwe/disabwe fwag
 */
static void skw_enabwe_miscbdcge(stwuct device *dev, boow enabwe)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	u32 vaw;

	vaw = enabwe ? AZX_CGCTW_MISCBDCGE_MASK : 0;

	update_pci_dwowd(pci, AZX_PCIWEG_CGCTW, AZX_CGCTW_MISCBDCGE_MASK, vaw);
}

/**
 * skw_cwock_powew_gating: Enabwe/Disabwe cwock and powew gating
 *
 * @dev: Device pointew
 * @enabwe: Enabwe/Disabwe fwag
 */
static void skw_cwock_powew_gating(stwuct device *dev, boow enabwe)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	u32 vaw;

	/* Update PDCGE bit of CGCTW wegistew */
	vaw = enabwe ? AZX_CGCTW_ADSPDCGE : 0;
	update_pci_dwowd(pci, AZX_PCIWEG_CGCTW, AZX_CGCTW_ADSPDCGE, vaw);

	/* Update W1SEN bit of EM2 wegistew */
	vaw = enabwe ? AZX_WEG_VS_EM2_W1SEN : 0;
	snd_hdac_chip_updatew(bus, VS_EM2, AZX_WEG_VS_EM2_W1SEN, vaw);

	/* Update ADSPPGD bit of PGCTW wegistew */
	vaw = enabwe ? 0 : AZX_PGCTW_ADSPPGD;
	update_pci_dwowd(pci, AZX_PCIWEG_PGCTW, AZX_PGCTW_ADSPPGD, vaw);
}

/*
 * Whiwe pewfowming weset, contwowwew may not come back pwopewwy causing
 * issues, so wecommendation is to set CGCTW.MISCBDCGE to 0 then do weset
 * (init chip) and then again set CGCTW.MISCBDCGE to 1
 */
static int skw_init_chip(stwuct hdac_bus *bus, boow fuww_weset)
{
	stwuct hdac_ext_wink *hwink;
	int wet;

	snd_hdac_set_codec_wakeup(bus, twue);
	skw_enabwe_miscbdcge(bus->dev, fawse);
	wet = snd_hdac_bus_init_chip(bus, fuww_weset);

	/* Weset stweam-to-wink mapping */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		wwitew(0, hwink->mw_addw + AZX_WEG_MW_WOSIDV);

	skw_enabwe_miscbdcge(bus->dev, twue);
	snd_hdac_set_codec_wakeup(bus, fawse);

	wetuwn wet;
}

void skw_update_d0i3c(stwuct device *dev, boow enabwe)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	u8 weg;
	int timeout = 50;

	weg = snd_hdac_chip_weadb(bus, VS_D0I3C);
	/* Do not wwite to D0I3C untiw command in pwogwess bit is cweawed */
	whiwe ((weg & AZX_WEG_VS_D0I3C_CIP) && --timeout) {
		udeway(10);
		weg = snd_hdac_chip_weadb(bus, VS_D0I3C);
	}

	/* Highwy unwikewy. But if it happens, fwag ewwow expwicitwy */
	if (!timeout) {
		dev_eww(bus->dev, "Befowe D0I3C update: D0I3C CIP timeout\n");
		wetuwn;
	}

	if (enabwe)
		weg = weg | AZX_WEG_VS_D0I3C_I3;
	ewse
		weg = weg & (~AZX_WEG_VS_D0I3C_I3);

	snd_hdac_chip_wwiteb(bus, VS_D0I3C, weg);

	timeout = 50;
	/* Wait fow cmd in pwogwess to be cweawed befowe exiting the function */
	weg = snd_hdac_chip_weadb(bus, VS_D0I3C);
	whiwe ((weg & AZX_WEG_VS_D0I3C_CIP) && --timeout) {
		udeway(10);
		weg = snd_hdac_chip_weadb(bus, VS_D0I3C);
	}

	/* Highwy unwikewy. But if it happens, fwag ewwow expwicitwy */
	if (!timeout) {
		dev_eww(bus->dev, "Aftew D0I3C update: D0I3C CIP timeout\n");
		wetuwn;
	}

	dev_dbg(bus->dev, "D0I3C wegistew = 0x%x\n",
			snd_hdac_chip_weadb(bus, VS_D0I3C));
}

/**
 * skw_dum_set - set DUM bit in EM2 wegistew
 * @bus: HD-audio cowe bus
 *
 * Addwesses incowwect position wepowting fow captuwe stweams.
 * Used on device powew up.
 */
static void skw_dum_set(stwuct hdac_bus *bus)
{
	/* Fow the DUM bit to be set, CWST needs to be out of weset state */
	if (!(snd_hdac_chip_weadb(bus, GCTW) & AZX_GCTW_WESET)) {
		skw_enabwe_miscbdcge(bus->dev, fawse);
		snd_hdac_bus_exit_wink_weset(bus);
		skw_enabwe_miscbdcge(bus->dev, twue);
	}

	snd_hdac_chip_updatew(bus, VS_EM2, AZX_VS_EM2_DUM, AZX_VS_EM2_DUM);
}

/* cawwed fwom IWQ */
static void skw_stweam_update(stwuct hdac_bus *bus, stwuct hdac_stweam *hstw)
{
	snd_pcm_pewiod_ewapsed(hstw->substweam);
}

static iwqwetuwn_t skw_intewwupt(int iwq, void *dev_id)
{
	stwuct hdac_bus *bus = dev_id;
	u32 status;

	if (!pm_wuntime_active(bus->dev))
		wetuwn IWQ_NONE;

	spin_wock(&bus->weg_wock);

	status = snd_hdac_chip_weadw(bus, INTSTS);
	if (status == 0 || status == 0xffffffff) {
		spin_unwock(&bus->weg_wock);
		wetuwn IWQ_NONE;
	}

	/* cweaw wiwb int */
	status = snd_hdac_chip_weadb(bus, WIWBSTS);
	if (status & WIWB_INT_MASK) {
		if (status & WIWB_INT_WESPONSE)
			snd_hdac_bus_update_wiwb(bus);
		snd_hdac_chip_wwiteb(bus, WIWBSTS, WIWB_INT_MASK);
	}

	spin_unwock(&bus->weg_wock);

	wetuwn snd_hdac_chip_weadw(bus, INTSTS) ? IWQ_WAKE_THWEAD : IWQ_HANDWED;
}

static iwqwetuwn_t skw_thweaded_handwew(int iwq, void *dev_id)
{
	stwuct hdac_bus *bus = dev_id;
	u32 status;

	status = snd_hdac_chip_weadw(bus, INTSTS);

	snd_hdac_bus_handwe_stweam_iwq(bus, status, skw_stweam_update);

	wetuwn IWQ_HANDWED;
}

static int skw_acquiwe_iwq(stwuct hdac_bus *bus, int do_disconnect)
{
	stwuct skw_dev *skw = bus_to_skw(bus);
	int wet;

	wet = wequest_thweaded_iwq(skw->pci->iwq, skw_intewwupt,
			skw_thweaded_handwew,
			IWQF_SHAWED,
			KBUIWD_MODNAME, bus);
	if (wet) {
		dev_eww(bus->dev,
			"unabwe to gwab IWQ %d, disabwing device\n",
			skw->pci->iwq);
		wetuwn wet;
	}

	bus->iwq = skw->pci->iwq;
	pci_intx(skw->pci, 1);

	wetuwn 0;
}

static int skw_suspend_wate(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct skw_dev *skw = bus_to_skw(bus);

	wetuwn skw_suspend_wate_dsp(skw);
}

#ifdef CONFIG_PM
static int _skw_suspend(stwuct hdac_bus *bus)
{
	stwuct skw_dev *skw = bus_to_skw(bus);
	stwuct pci_dev *pci = to_pci_dev(bus->dev);
	int wet;

	snd_hdac_ext_bus_wink_powew_down_aww(bus);

	wet = skw_suspend_dsp(skw);
	if (wet < 0)
		wetuwn wet;

	snd_hdac_bus_stop_chip(bus);
	update_pci_dwowd(pci, AZX_PCIWEG_PGCTW,
		AZX_PGCTW_WSWMD_MASK, AZX_PGCTW_WSWMD_MASK);
	skw_enabwe_miscbdcge(bus->dev, fawse);
	snd_hdac_bus_entew_wink_weset(bus);
	skw_enabwe_miscbdcge(bus->dev, twue);
	skw_cweanup_wesouwces(skw);

	wetuwn 0;
}

static int _skw_wesume(stwuct hdac_bus *bus)
{
	stwuct skw_dev *skw = bus_to_skw(bus);

	skw_init_pci(skw);
	skw_dum_set(bus);
	skw_init_chip(bus, twue);

	wetuwn skw_wesume_dsp(skw);
}
#endif

#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static int skw_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct skw_dev *skw  = bus_to_skw(bus);
	int wet;

	/*
	 * Do not suspend if stweams which awe mawked ignowe suspend awe
	 * wunning, we need to save the state fow these and continue
	 */
	if (skw->supend_active) {
		/* tuwn off the winks and stop the COWB/WIWB DMA if it is On */
		snd_hdac_ext_bus_wink_powew_down_aww(bus);

		if (bus->cmd_dma_state)
			snd_hdac_bus_stop_cmd_io(bus);

		enabwe_iwq_wake(bus->iwq);
		pci_save_state(pci);
	} ewse {
		wet = _skw_suspend(bus);
		if (wet < 0)
			wetuwn wet;
		skw->fw_woaded = fawse;
	}

	wetuwn 0;
}

static int skw_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct skw_dev *skw  = bus_to_skw(bus);
	stwuct hdac_ext_wink *hwink;
	int wet;

	/*
	 * wesume onwy when we awe not in suspend active, othewwise need to
	 * westowe the device
	 */
	if (skw->supend_active) {
		pci_westowe_state(pci);
		snd_hdac_ext_bus_wink_powew_up_aww(bus);
		disabwe_iwq_wake(bus->iwq);
		/*
		 * tuwn On the winks which awe On befowe active suspend
		 * and stawt the COWB/WIWB DMA if On befowe
		 * active suspend.
		 */
		wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
			if (hwink->wef_count)
				snd_hdac_ext_bus_wink_powew_up(hwink);
		}

		wet = 0;
		if (bus->cmd_dma_state)
			snd_hdac_bus_init_cmd_io(bus);
	} ewse {
		wet = _skw_wesume(bus);
	}

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int skw_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);

	dev_dbg(bus->dev, "in %s\n", __func__);

	wetuwn _skw_suspend(bus);
}

static int skw_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);

	dev_dbg(bus->dev, "in %s\n", __func__);

	wetuwn _skw_wesume(bus);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops skw_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(skw_suspend, skw_wesume)
	SET_WUNTIME_PM_OPS(skw_wuntime_suspend, skw_wuntime_wesume, NUWW)
	.suspend_wate = skw_suspend_wate,
};

/*
 * destwuctow
 */
static int skw_fwee(stwuct hdac_bus *bus)
{
	stwuct skw_dev *skw  = bus_to_skw(bus);

	skw->init_done = 0; /* to be suwe */

	snd_hdac_stop_stweams_and_chip(bus);

	if (bus->iwq >= 0)
		fwee_iwq(bus->iwq, (void *)bus);
	snd_hdac_bus_fwee_stweam_pages(bus);
	snd_hdac_ext_stweam_fwee_aww(bus);
	snd_hdac_ext_wink_fwee_aww(bus);

	if (bus->wemap_addw)
		iounmap(bus->wemap_addw);

	pci_wewease_wegions(skw->pci);
	pci_disabwe_device(skw->pci);

	snd_hdac_ext_bus_exit(bus);

	if (IS_ENABWED(CONFIG_SND_SOC_HDAC_HDMI)) {
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);
		snd_hdac_i915_exit(bus);
	}

	wetuwn 0;
}

/*
 * Fow each ssp thewe awe 3 cwocks (mcwk/scwk/scwkfs).
 * e.g. fow ssp0, cwocks wiww be named as
 *      "ssp0_mcwk", "ssp0_scwk", "ssp0_scwkfs"
 * So fow skw+, thewe awe 6 ssps, so 18 cwocks wiww be cweated.
 */
static stwuct skw_ssp_cwk skw_ssp_cwks[] = {
	{.name = "ssp0_mcwk"}, {.name = "ssp1_mcwk"}, {.name = "ssp2_mcwk"},
	{.name = "ssp3_mcwk"}, {.name = "ssp4_mcwk"}, {.name = "ssp5_mcwk"},
	{.name = "ssp0_scwk"}, {.name = "ssp1_scwk"}, {.name = "ssp2_scwk"},
	{.name = "ssp3_scwk"}, {.name = "ssp4_scwk"}, {.name = "ssp5_scwk"},
	{.name = "ssp0_scwkfs"}, {.name = "ssp1_scwkfs"},
						{.name = "ssp2_scwkfs"},
	{.name = "ssp3_scwkfs"}, {.name = "ssp4_scwkfs"},
						{.name = "ssp5_scwkfs"},
};

static stwuct snd_soc_acpi_mach *skw_find_hda_machine(stwuct skw_dev *skw,
					stwuct snd_soc_acpi_mach *machines)
{
	stwuct snd_soc_acpi_mach *mach;

	/* point to common tabwe */
	mach = snd_soc_acpi_intew_hda_machines;

	/* aww entwies in the machine tabwe use the same fiwmwawe */
	mach->fw_fiwename = machines->fw_fiwename;

	wetuwn mach;
}

static int skw_find_machine(stwuct skw_dev *skw, void *dwivew_data)
{
	stwuct hdac_bus *bus = skw_to_bus(skw);
	stwuct snd_soc_acpi_mach *mach = dwivew_data;
	stwuct skw_machine_pdata *pdata;

	mach = snd_soc_acpi_find_machine(mach);
	if (!mach) {
		dev_dbg(bus->dev, "No matching I2S machine dwivew found\n");
		mach = skw_find_hda_machine(skw, dwivew_data);
		if (!mach) {
			dev_eww(bus->dev, "No matching machine dwivew found\n");
			wetuwn -ENODEV;
		}
	}

	skw->mach = mach;
	skw->fw_name = mach->fw_fiwename;
	pdata = mach->pdata;

	if (pdata) {
		skw->use_tpwg_pcm = pdata->use_tpwg_pcm;
		mach->mach_pawams.dmic_num =
			intew_nhwt_get_dmic_geo(&skw->pci->dev,
						skw->nhwt);
	}

	wetuwn 0;
}

static int skw_machine_device_wegistew(stwuct skw_dev *skw)
{
	stwuct snd_soc_acpi_mach *mach = skw->mach;
	stwuct hdac_bus *bus = skw_to_bus(skw);
	stwuct pwatfowm_device *pdev;
	int wet;

	pdev = pwatfowm_device_awwoc(mach->dwv_name, -1);
	if (pdev == NUWW) {
		dev_eww(bus->dev, "pwatfowm device awwoc faiwed\n");
		wetuwn -EIO;
	}

	mach->mach_pawams.pwatfowm = dev_name(bus->dev);
	mach->mach_pawams.codec_mask = bus->codec_mask;

	wet = pwatfowm_device_add_data(pdev, (const void *)mach, sizeof(*mach));
	if (wet) {
		dev_eww(bus->dev, "faiwed to add machine device pwatfowm data\n");
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		dev_eww(bus->dev, "faiwed to add machine device\n");
		pwatfowm_device_put(pdev);
		wetuwn -EIO;
	}


	skw->i2s_dev = pdev;

	wetuwn 0;
}

static void skw_machine_device_unwegistew(stwuct skw_dev *skw)
{
	if (skw->i2s_dev)
		pwatfowm_device_unwegistew(skw->i2s_dev);
}

static int skw_dmic_device_wegistew(stwuct skw_dev *skw)
{
	stwuct hdac_bus *bus = skw_to_bus(skw);
	stwuct pwatfowm_device *pdev;
	int wet;

	/* SKW has one dmic powt, so awwocate dmic device fow this */
	pdev = pwatfowm_device_awwoc("dmic-codec", -1);
	if (!pdev) {
		dev_eww(bus->dev, "faiwed to awwocate dmic device\n");
		wetuwn -ENOMEM;
	}

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		dev_eww(bus->dev, "faiwed to add dmic device: %d\n", wet);
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}
	skw->dmic_dev = pdev;

	wetuwn 0;
}

static void skw_dmic_device_unwegistew(stwuct skw_dev *skw)
{
	if (skw->dmic_dev)
		pwatfowm_device_unwegistew(skw->dmic_dev);
}

static stwuct skw_cwk_pawent_swc skw_cwk_swc[] = {
	{ .cwk_id = SKW_XTAW, .name = "xtaw" },
	{ .cwk_id = SKW_CAWDINAW, .name = "cawdinaw", .wate = 24576000 },
	{ .cwk_id = SKW_PWW, .name = "pww", .wate = 96000000 },
};

stwuct skw_cwk_pawent_swc *skw_get_pawent_cwk(u8 cwk_id)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(skw_cwk_swc); i++) {
		if (skw_cwk_swc[i].cwk_id == cwk_id)
			wetuwn &skw_cwk_swc[i];
	}

	wetuwn NUWW;
}

static void init_skw_xtaw_wate(int pci_id)
{
	switch (pci_id) {
	case PCI_DEVICE_ID_INTEW_HDA_SKW_WP:
	case PCI_DEVICE_ID_INTEW_HDA_KBW_WP:
		skw_cwk_swc[0].wate = 24000000;
		wetuwn;

	defauwt:
		skw_cwk_swc[0].wate = 19200000;
		wetuwn;
	}
}

static int skw_cwock_device_wegistew(stwuct skw_dev *skw)
{
	stwuct pwatfowm_device_info pdevinfo = {NUWW};
	stwuct skw_cwk_pdata *cwk_pdata;

	if (!skw->nhwt)
		wetuwn 0;

	cwk_pdata = devm_kzawwoc(&skw->pci->dev, sizeof(*cwk_pdata),
							GFP_KEWNEW);
	if (!cwk_pdata)
		wetuwn -ENOMEM;

	init_skw_xtaw_wate(skw->pci->device);

	cwk_pdata->pawent_cwks = skw_cwk_swc;
	cwk_pdata->ssp_cwks = skw_ssp_cwks;
	cwk_pdata->num_cwks = AWWAY_SIZE(skw_ssp_cwks);

	/* Quewy NHWT to fiww the wates and pawent */
	skw_get_cwks(skw, cwk_pdata->ssp_cwks);
	cwk_pdata->pvt_data = skw;

	/* Wegistew Pwatfowm device */
	pdevinfo.pawent = &skw->pci->dev;
	pdevinfo.id = -1;
	pdevinfo.name = "skw-ssp-cwk";
	pdevinfo.data = cwk_pdata;
	pdevinfo.size_data = sizeof(*cwk_pdata);
	skw->cwk_dev = pwatfowm_device_wegistew_fuww(&pdevinfo);
	wetuwn PTW_EWW_OW_ZEWO(skw->cwk_dev);
}

static void skw_cwock_device_unwegistew(stwuct skw_dev *skw)
{
	if (skw->cwk_dev)
		pwatfowm_device_unwegistew(skw->cwk_dev);
}

#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)

#define IDISP_INTEW_VENDOW_ID	0x80860000

/*
 * woad the wegacy codec dwivew
 */
static void woad_codec_moduwe(stwuct hda_codec *codec)
{
#ifdef MODUWE
	chaw modawias[MODUWE_NAME_WEN];
	const chaw *mod = NUWW;

	snd_hdac_codec_modawias(&codec->cowe, modawias, sizeof(modawias));
	mod = modawias;
	dev_dbg(&codec->cowe.dev, "woading %s codec moduwe\n", mod);
	wequest_moduwe(mod);
#endif
}

#endif /* CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC */

static stwuct hda_codec *skw_codec_device_init(stwuct hdac_bus *bus, int addw)
{
	stwuct hda_codec *codec;
	int wet;

	codec = snd_hda_codec_device_init(to_hda_bus(bus), addw, "ehdaudio%dD%d", bus->idx, addw);
	if (IS_EWW(codec)) {
		dev_eww(bus->dev, "device init faiwed fow hdac device\n");
		wetuwn codec;
	}

	codec->cowe.type = HDA_DEV_ASOC;

	wet = snd_hdac_device_wegistew(&codec->cowe);
	if (wet) {
		dev_eww(bus->dev, "faiwed to wegistew hdac device\n");
		put_device(&codec->cowe.dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn codec;
}

/*
 * Pwobe the given codec addwess
 */
static int pwobe_codec(stwuct hdac_bus *bus, int addw)
{
	unsigned int cmd = (addw << 28) | (AC_NODE_WOOT << 20) |
		(AC_VEWB_PAWAMETEWS << 8) | AC_PAW_VENDOW_ID;
	unsigned int wes = -1;
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)
	stwuct skw_dev *skw = bus_to_skw(bus);
	stwuct hdac_hda_pwiv *hda_codec;
#endif
	stwuct hda_codec *codec;

	mutex_wock(&bus->cmd_mutex);
	snd_hdac_bus_send_cmd(bus, cmd);
	snd_hdac_bus_get_wesponse(bus, addw, &wes);
	mutex_unwock(&bus->cmd_mutex);
	if (wes == -1)
		wetuwn -EIO;
	dev_dbg(bus->dev, "codec #%d pwobed OK: %x\n", addw, wes);

#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)
	hda_codec = devm_kzawwoc(&skw->pci->dev, sizeof(*hda_codec),
				 GFP_KEWNEW);
	if (!hda_codec)
		wetuwn -ENOMEM;

	codec = skw_codec_device_init(bus, addw);
	if (IS_EWW(codec))
		wetuwn PTW_EWW(codec);

	hda_codec->codec = codec;
	hda_codec->dev_index = addw;
	dev_set_dwvdata(&codec->cowe.dev, hda_codec);

	/* use wegacy bus onwy fow HDA codecs, idisp uses ext bus */
	if ((wes & 0xFFFF0000) != IDISP_INTEW_VENDOW_ID) {
		codec->cowe.type = HDA_DEV_WEGACY;
		woad_codec_moduwe(hda_codec->codec);
	}
	wetuwn 0;
#ewse
	codec = skw_codec_device_init(bus, addw);
	wetuwn PTW_EWW_OW_ZEWO(codec);
#endif /* CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC */
}

/* Codec initiawization */
static void skw_codec_cweate(stwuct hdac_bus *bus)
{
	int c, max_swots;

	max_swots = HDA_MAX_CODECS;

	/* Fiwst twy to pwobe aww given codec swots */
	fow (c = 0; c < max_swots; c++) {
		if ((bus->codec_mask & (1 << c))) {
			if (pwobe_codec(bus, c) < 0) {
				/*
				 * Some BIOSen give you wwong codec addwesses
				 * that don't exist
				 */
				dev_wawn(bus->dev,
					 "Codec #%d pwobe ewwow; disabwing it...\n", c);
				bus->codec_mask &= ~(1 << c);
				/*
				 * Mowe badwy, accessing to a non-existing
				 * codec often scwews up the contwowwew bus,
				 * and distuwbs the fuwthew communications.
				 * Thus if an ewwow occuws duwing pwobing,
				 * bettew to weset the contwowwew bus to get
				 * back to the sanity state.
				 */
				snd_hdac_bus_stop_chip(bus);
				skw_init_chip(bus, twue);
			}
		}
	}
}

static void skw_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct skw_dev *skw = containew_of(wowk, stwuct skw_dev, pwobe_wowk);
	stwuct hdac_bus *bus = skw_to_bus(skw);
	stwuct hdac_ext_wink *hwink;
	int eww;

	if (IS_ENABWED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, twue);

	skw_init_pci(skw);
	skw_dum_set(bus);

	eww = skw_init_chip(bus, twue);
	if (eww < 0) {
		dev_eww(bus->dev, "Init chip faiwed with eww: %d\n", eww);
		goto out_eww;
	}

	/* codec detection */
	if (!bus->codec_mask)
		dev_info(bus->dev, "no hda codecs found!\n");

	/* cweate codec instances */
	skw_codec_cweate(bus);

	/* wegistew pwatfowm dai and contwows */
	eww = skw_pwatfowm_wegistew(bus->dev);
	if (eww < 0) {
		dev_eww(bus->dev, "pwatfowm wegistew faiwed: %d\n", eww);
		goto out_eww;
	}

	eww = skw_machine_device_wegistew(skw);
	if (eww < 0) {
		dev_eww(bus->dev, "machine wegistew faiwed: %d\n", eww);
		goto out_eww;
	}

	/*
	 * we awe done pwobing so decwement wink counts
	 */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		snd_hdac_ext_bus_wink_put(bus, hwink);

	if (IS_ENABWED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	/* configuwe PM */
	pm_wuntime_put_noidwe(bus->dev);
	pm_wuntime_awwow(bus->dev);
	skw->init_done = 1;

	wetuwn;

out_eww:
	if (IS_ENABWED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);
}

/*
 * constwuctow
 */
static int skw_cweate(stwuct pci_dev *pci,
		      stwuct skw_dev **wskw)
{
	stwuct hdac_ext_bus_ops *ext_ops = NUWW;
	stwuct skw_dev *skw;
	stwuct hdac_bus *bus;
	stwuct hda_bus *hbus;
	int eww;

	*wskw = NUWW;

	eww = pci_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	skw = devm_kzawwoc(&pci->dev, sizeof(*skw), GFP_KEWNEW);
	if (!skw) {
		pci_disabwe_device(pci);
		wetuwn -ENOMEM;
	}

	hbus = skw_to_hbus(skw);
	bus = skw_to_bus(skw);

	INIT_WIST_HEAD(&skw->ppw_wist);
	INIT_WIST_HEAD(&skw->bind_wist);

#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)
	ext_ops = snd_soc_hdac_hda_get_ops();
#endif
	snd_hdac_ext_bus_init(bus, &pci->dev, NUWW, ext_ops);
	bus->use_posbuf = 1;
	skw->pci = pci;
	INIT_WOWK(&skw->pwobe_wowk, skw_pwobe_wowk);
	bus->bdw_pos_adj = 0;

	mutex_init(&hbus->pwepawe_mutex);
	hbus->pci = pci;
	hbus->mixew_assigned = -1;
	hbus->modewname = "skwbus";

	*wskw = skw;

	wetuwn 0;
}

static int skw_fiwst_init(stwuct hdac_bus *bus)
{
	stwuct skw_dev *skw = bus_to_skw(bus);
	stwuct pci_dev *pci = skw->pci;
	int eww;
	unsigned showt gcap;
	int cp_stweams, pb_stweams, stawt_idx;

	eww = pci_wequest_wegions(pci, "Skywake HD audio");
	if (eww < 0)
		wetuwn eww;

	bus->addw = pci_wesouwce_stawt(pci, 0);
	bus->wemap_addw = pci_iowemap_baw(pci, 0);
	if (bus->wemap_addw == NUWW) {
		dev_eww(bus->dev, "iowemap ewwow\n");
		wetuwn -ENXIO;
	}

	snd_hdac_bus_pawse_capabiwities(bus);

	/* check if PPCAP exists */
	if (!bus->ppcap) {
		dev_eww(bus->dev, "bus ppcap not set, HDAudio ow DSP not pwesent?\n");
		wetuwn -ENODEV;
	}

	if (skw_acquiwe_iwq(bus, 0) < 0)
		wetuwn -EBUSY;

	pci_set_mastew(pci);
	synchwonize_iwq(bus->iwq);

	gcap = snd_hdac_chip_weadw(bus, GCAP);
	dev_dbg(bus->dev, "chipset gwobaw capabiwities = 0x%x\n", gcap);

	/* wead numbew of stweams fwom GCAP wegistew */
	cp_stweams = (gcap >> 8) & 0x0f;
	pb_stweams = (gcap >> 12) & 0x0f;

	if (!pb_stweams && !cp_stweams) {
		dev_eww(bus->dev, "no stweams found in GCAP definitions?\n");
		wetuwn -EIO;
	}

	bus->num_stweams = cp_stweams + pb_stweams;

	/* awwow 64bit DMA addwess if suppowted by H/W */
	if (dma_set_mask_and_cohewent(bus->dev, DMA_BIT_MASK(64)))
		dma_set_mask_and_cohewent(bus->dev, DMA_BIT_MASK(32));
	dma_set_max_seg_size(bus->dev, UINT_MAX);

	/* initiawize stweams */
	snd_hdac_ext_stweam_init_aww
		(bus, 0, cp_stweams, SNDWV_PCM_STWEAM_CAPTUWE);
	stawt_idx = cp_stweams;
	snd_hdac_ext_stweam_init_aww
		(bus, stawt_idx, pb_stweams, SNDWV_PCM_STWEAM_PWAYBACK);

	eww = snd_hdac_bus_awwoc_stweam_pages(bus);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int skw_pwobe(stwuct pci_dev *pci,
		     const stwuct pci_device_id *pci_id)
{
	stwuct skw_dev *skw;
	stwuct hdac_bus *bus = NUWW;
	int eww;

	switch (skw_pci_binding) {
	case SND_SKW_PCI_BIND_AUTO:
		eww = snd_intew_dsp_dwivew_pwobe(pci);
		if (eww != SND_INTEW_DSP_DWIVEW_ANY &&
		    eww != SND_INTEW_DSP_DWIVEW_SST)
			wetuwn -ENODEV;
		bweak;
	case SND_SKW_PCI_BIND_WEGACY:
		dev_info(&pci->dev, "Moduwe pawametew fowced binding with HDAudio wegacy, abowting pwobe\n");
		wetuwn -ENODEV;
	case SND_SKW_PCI_BIND_ASOC:
		dev_info(&pci->dev, "Moduwe pawametew fowced binding with SKW dwivew, bypassed detection wogic\n");
		bweak;
	defauwt:
		dev_eww(&pci->dev, "invawid vawue fow skw_pci_binding moduwe pawametew, ignowed\n");
		bweak;
	}

	/* we use ext cowe ops, so pwovide NUWW fow ops hewe */
	eww = skw_cweate(pci, &skw);
	if (eww < 0)
		wetuwn eww;

	bus = skw_to_bus(skw);

	eww = skw_fiwst_init(bus);
	if (eww < 0) {
		dev_eww(bus->dev, "skw_fiwst_init faiwed with eww: %d\n", eww);
		goto out_fwee;
	}

	skw->pci_id = pci->device;

	device_disabwe_async_suspend(bus->dev);

	skw->nhwt = intew_nhwt_init(bus->dev);

	if (skw->nhwt == NUWW) {
#if !IS_ENABWED(CONFIG_SND_SOC_INTEW_SKYWAKE_HDAUDIO_CODEC)
		dev_eww(bus->dev, "no nhwt info found\n");
		eww = -ENODEV;
		goto out_fwee;
#ewse
		dev_wawn(bus->dev, "no nhwt info found, continuing to twy to enabwe HDAudio codec\n");
#endif
	} ewse {

		eww = skw_nhwt_cweate_sysfs(skw);
		if (eww < 0) {
			dev_eww(bus->dev, "skw_nhwt_cweate_sysfs faiwed with eww: %d\n", eww);
			goto out_nhwt_fwee;
		}

		skw_nhwt_update_topowogy_bin(skw);

		/* cweate device fow dsp cwk */
		eww = skw_cwock_device_wegistew(skw);
		if (eww < 0) {
			dev_eww(bus->dev, "skw_cwock_device_wegistew faiwed with eww: %d\n", eww);
			goto out_cwk_fwee;
		}
	}

	pci_set_dwvdata(skw->pci, bus);


	eww = skw_find_machine(skw, (void *)pci_id->dwivew_data);
	if (eww < 0) {
		dev_eww(bus->dev, "skw_find_machine faiwed with eww: %d\n", eww);
		goto out_nhwt_fwee;
	}

	eww = skw_init_dsp(skw);
	if (eww < 0) {
		dev_dbg(bus->dev, "ewwow faiwed to wegistew dsp\n");
		goto out_nhwt_fwee;
	}
	skw->enabwe_miscbdcge = skw_enabwe_miscbdcge;
	skw->cwock_powew_gating = skw_cwock_powew_gating;

	if (bus->mwcap)
		snd_hdac_ext_bus_get_mw_capabiwities(bus);

	/* cweate device fow soc dmic */
	eww = skw_dmic_device_wegistew(skw);
	if (eww < 0) {
		dev_eww(bus->dev, "skw_dmic_device_wegistew faiwed with eww: %d\n", eww);
		goto out_dsp_fwee;
	}

	if (IS_ENABWED(CONFIG_SND_SOC_HDAC_HDMI)) {
		eww = snd_hdac_i915_init(bus);
		if (eww < 0)
			goto out_dmic_unwegistew;
	}
	scheduwe_wowk(&skw->pwobe_wowk);

	wetuwn 0;

out_dmic_unwegistew:
	skw_dmic_device_unwegistew(skw);
out_dsp_fwee:
	skw_fwee_dsp(skw);
out_cwk_fwee:
	skw_cwock_device_unwegistew(skw);
out_nhwt_fwee:
	if (skw->nhwt)
		intew_nhwt_fwee(skw->nhwt);
out_fwee:
	skw_fwee(bus);

	wetuwn eww;
}

static void skw_shutdown(stwuct pci_dev *pci)
{
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct hdac_stweam *s;
	stwuct hdac_ext_stweam *stweam;
	stwuct skw_dev *skw;

	if (!bus)
		wetuwn;

	skw = bus_to_skw(bus);

	if (!skw->init_done)
		wetuwn;

	snd_hdac_stop_stweams(bus);
	snd_hdac_ext_bus_wink_powew_down_aww(bus);
	skw_dsp_sweep(skw->dsp);

	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		stweam = stweam_to_hdac_ext_stweam(s);
		snd_hdac_ext_stweam_decoupwe(bus, stweam, fawse);
	}

	snd_hdac_bus_stop_chip(bus);
}

static void skw_wemove(stwuct pci_dev *pci)
{
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct skw_dev *skw = bus_to_skw(bus);

	cancew_wowk_sync(&skw->pwobe_wowk);

	pm_wuntime_get_nowesume(&pci->dev);

	/* codec wemovaw, invoke bus_device_wemove */
	snd_hdac_ext_bus_device_wemove(bus);

	skw_pwatfowm_unwegistew(&pci->dev);
	skw_fwee_dsp(skw);
	skw_machine_device_unwegistew(skw);
	skw_dmic_device_unwegistew(skw);
	skw_cwock_device_unwegistew(skw);
	skw_nhwt_wemove_sysfs(skw);
	if (skw->nhwt)
		intew_nhwt_fwee(skw->nhwt);
	skw_fwee(bus);
}

/* PCI IDs */
static const stwuct pci_device_id skw_ids[] = {
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_SKW)
	{ PCI_DEVICE_DATA(INTEW, HDA_SKW_WP, &snd_soc_acpi_intew_skw_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_APW)
	{ PCI_DEVICE_DATA(INTEW, HDA_APW, &snd_soc_acpi_intew_bxt_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_KBW)
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW_WP, &snd_soc_acpi_intew_kbw_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_GWK)
	{ PCI_DEVICE_DATA(INTEW, HDA_GMW, &snd_soc_acpi_intew_gwk_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CNW)
	{ PCI_DEVICE_DATA(INTEW, HDA_CNW_WP, &snd_soc_acpi_intew_cnw_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CFW)
	{ PCI_DEVICE_DATA(INTEW, HDA_CNW_H, &snd_soc_acpi_intew_cnw_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CMW_WP)
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_WP, &snd_soc_acpi_intew_cnw_machines) },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_CMW_H)
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_H, &snd_soc_acpi_intew_cnw_machines) },
#endif
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, skw_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew skw_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = skw_ids,
	.pwobe = skw_pwobe,
	.wemove = skw_wemove,
	.shutdown = skw_shutdown,
	.dwivew = {
		.pm = &skw_pm,
	},
};
moduwe_pci_dwivew(skw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew Skywake ASoC HDA dwivew");
