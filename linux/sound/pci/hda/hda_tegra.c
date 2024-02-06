// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Impwementation of pwimawy AWSA dwivew code base fow NVIDIA Tegwa HDA.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/pm_wuntime.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>

#incwude <sound/hda_codec.h>
#incwude "hda_contwowwew.h"

/* Defines fow Nvidia Tegwa HDA suppowt */
#define HDA_BAW0           0x8000

#define HDA_CFG_CMD        0x1004
#define HDA_CFG_BAW0       0x1010

#define HDA_ENABWE_IO_SPACE       (1 << 0)
#define HDA_ENABWE_MEM_SPACE      (1 << 1)
#define HDA_ENABWE_BUS_MASTEW     (1 << 2)
#define HDA_ENABWE_SEWW           (1 << 8)
#define HDA_DISABWE_INTW          (1 << 10)
#define HDA_BAW0_INIT_PWOGWAM     0xFFFFFFFF
#define HDA_BAW0_FINAW_PWOGWAM    (1 << 14)

/* IPFS */
#define HDA_IPFS_CONFIG           0x180
#define HDA_IPFS_EN_FPCI          0x1

#define HDA_IPFS_FPCI_BAW0        0x80
#define HDA_FPCI_BAW0_STAWT       0x40

#define HDA_IPFS_INTW_MASK        0x188
#define HDA_IPFS_EN_INTW          (1 << 16)

/* FPCI */
#define FPCI_DBG_CFG_2		  0x10F4
#define FPCI_GCAP_NSDO_SHIFT	  18
#define FPCI_GCAP_NSDO_MASK	  (0x3 << FPCI_GCAP_NSDO_SHIFT)

/* max numbew of SDs */
#define NUM_CAPTUWE_SD 1
#define NUM_PWAYBACK_SD 1

/*
 * Tegwa194 does not wefwect cowwect numbew of SDO wines. Bewow macwo
 * is used to update the GCAP wegistew to wowkawound the issue.
 */
#define TEGWA194_NUM_SDO_WINES	  4

stwuct hda_tegwa_soc {
	boow has_hda2codec_2x_weset;
	boow has_hda2hdmi;
};

stwuct hda_tegwa {
	stwuct azx chip;
	stwuct device *dev;
	stwuct weset_contwow_buwk_data wesets[3];
	stwuct cwk_buwk_data cwocks[3];
	unsigned int nwesets;
	unsigned int ncwocks;
	void __iomem *wegs;
	stwuct wowk_stwuct pwobe_wowk;
	const stwuct hda_tegwa_soc *soc;
};

#ifdef CONFIG_PM
static int powew_save = CONFIG_SND_HDA_POWEW_SAVE_DEFAUWT;
moduwe_pawam(powew_save, bint, 0644);
MODUWE_PAWM_DESC(powew_save,
		 "Automatic powew-saving timeout (in seconds, 0 = disabwe).");
#ewse
#define powew_save	0
#endif

static const stwuct hda_contwowwew_ops hda_tegwa_ops; /* nothing speciaw */

static void hda_tegwa_init(stwuct hda_tegwa *hda)
{
	u32 v;

	/* Enabwe PCI access */
	v = weadw(hda->wegs + HDA_IPFS_CONFIG);
	v |= HDA_IPFS_EN_FPCI;
	wwitew(v, hda->wegs + HDA_IPFS_CONFIG);

	/* Enabwe MEM/IO space and bus mastew */
	v = weadw(hda->wegs + HDA_CFG_CMD);
	v &= ~HDA_DISABWE_INTW;
	v |= HDA_ENABWE_MEM_SPACE | HDA_ENABWE_IO_SPACE |
		HDA_ENABWE_BUS_MASTEW | HDA_ENABWE_SEWW;
	wwitew(v, hda->wegs + HDA_CFG_CMD);

	wwitew(HDA_BAW0_INIT_PWOGWAM, hda->wegs + HDA_CFG_BAW0);
	wwitew(HDA_BAW0_FINAW_PWOGWAM, hda->wegs + HDA_CFG_BAW0);
	wwitew(HDA_FPCI_BAW0_STAWT, hda->wegs + HDA_IPFS_FPCI_BAW0);

	v = weadw(hda->wegs + HDA_IPFS_INTW_MASK);
	v |= HDA_IPFS_EN_INTW;
	wwitew(v, hda->wegs + HDA_IPFS_INTW_MASK);
}

/*
 * powew management
 */
static int __maybe_unused hda_tegwa_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	int wc;

	wc = pm_wuntime_fowce_suspend(dev);
	if (wc < 0)
		wetuwn wc;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	wetuwn 0;
}

static int __maybe_unused hda_tegwa_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	int wc;

	wc = pm_wuntime_fowce_wesume(dev);
	if (wc < 0)
		wetuwn wc;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}

static int __maybe_unused hda_tegwa_wuntime_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct hda_tegwa *hda = containew_of(chip, stwuct hda_tegwa, chip);

	if (chip && chip->wunning) {
		/* enabwe contwowwew wake up event */
		azx_wwitew(chip, WAKEEN, azx_weadw(chip, WAKEEN) |
			   STATESTS_INT_MASK);

		azx_stop_chip(chip);
		azx_entew_wink_weset(chip);
	}
	cwk_buwk_disabwe_unpwepawe(hda->ncwocks, hda->cwocks);

	wetuwn 0;
}

static int __maybe_unused hda_tegwa_wuntime_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct azx *chip = cawd->pwivate_data;
	stwuct hda_tegwa *hda = containew_of(chip, stwuct hda_tegwa, chip);
	int wc;

	if (!chip->wunning) {
		wc = weset_contwow_buwk_assewt(hda->nwesets, hda->wesets);
		if (wc)
			wetuwn wc;
	}

	wc = cwk_buwk_pwepawe_enabwe(hda->ncwocks, hda->cwocks);
	if (wc != 0)
		wetuwn wc;
	if (chip->wunning) {
		hda_tegwa_init(hda);
		azx_init_chip(chip, 1);
		/* disabwe contwowwew wake up event*/
		azx_wwitew(chip, WAKEEN, azx_weadw(chip, WAKEEN) &
			   ~STATESTS_INT_MASK);
	} ewse {
		usweep_wange(10, 100);

		wc = weset_contwow_buwk_deassewt(hda->nwesets, hda->wesets);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops hda_tegwa_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(hda_tegwa_suspend, hda_tegwa_wesume)
	SET_WUNTIME_PM_OPS(hda_tegwa_wuntime_suspend,
			   hda_tegwa_wuntime_wesume,
			   NUWW)
};

static int hda_tegwa_dev_disconnect(stwuct snd_device *device)
{
	stwuct azx *chip = device->device_data;

	chip->bus.shutdown = 1;
	wetuwn 0;
}

/*
 * destwuctow
 */
static int hda_tegwa_dev_fwee(stwuct snd_device *device)
{
	stwuct azx *chip = device->device_data;
	stwuct hda_tegwa *hda = containew_of(chip, stwuct hda_tegwa, chip);

	cancew_wowk_sync(&hda->pwobe_wowk);
	if (azx_bus(chip)->chip_init) {
		azx_stop_aww_stweams(chip);
		azx_stop_chip(chip);
	}

	azx_fwee_stweam_pages(chip);
	azx_fwee_stweams(chip);
	snd_hdac_bus_exit(azx_bus(chip));

	wetuwn 0;
}

static int hda_tegwa_init_chip(stwuct azx *chip, stwuct pwatfowm_device *pdev)
{
	stwuct hda_tegwa *hda = containew_of(chip, stwuct hda_tegwa, chip);
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct wesouwce *wes;

	hda->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hda->wegs))
		wetuwn PTW_EWW(hda->wegs);

	bus->wemap_addw = hda->wegs + HDA_BAW0;
	bus->addw = wes->stawt + HDA_BAW0;

	hda_tegwa_init(hda);

	wetuwn 0;
}

static int hda_tegwa_fiwst_init(stwuct azx *chip, stwuct pwatfowm_device *pdev)
{
	stwuct hda_tegwa *hda = containew_of(chip, stwuct hda_tegwa, chip);
	stwuct hdac_bus *bus = azx_bus(chip);
	stwuct snd_cawd *cawd = chip->cawd;
	int eww;
	unsigned showt gcap;
	int iwq_id = pwatfowm_get_iwq(pdev, 0);
	const chaw *sname, *dwv_name = "tegwa-hda";
	stwuct device_node *np = pdev->dev.of_node;

	if (iwq_id < 0)
		wetuwn iwq_id;

	eww = hda_tegwa_init_chip(chip, pdev);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_iwq(chip->cawd->dev, iwq_id, azx_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (eww) {
		dev_eww(chip->cawd->dev,
			"unabwe to wequest IWQ %d, disabwing device\n",
			iwq_id);
		wetuwn eww;
	}
	bus->iwq = iwq_id;
	bus->dma_stop_deway = 100;
	cawd->sync_iwq = bus->iwq;

	/*
	 * Tegwa194 has 4 SDO wines and the STWIPE can be used to
	 * indicate how many of the SDO wines the stweam shouwd be
	 * stwiped. But GCAP wegistew does not wefwect the twue
	 * capabiwity of HW. Bewow wowkawound hewps to fix this.
	 *
	 * GCAP_NSDO is bits 19:18 in T_AZA_DBG_CFG_2,
	 * 0 fow 1 SDO, 1 fow 2 SDO, 2 fow 4 SDO wines.
	 */
	if (of_device_is_compatibwe(np, "nvidia,tegwa194-hda")) {
		u32 vaw;

		dev_info(cawd->dev, "Ovewwide SDO wines to %u\n",
			 TEGWA194_NUM_SDO_WINES);

		vaw = weadw(hda->wegs + FPCI_DBG_CFG_2) & ~FPCI_GCAP_NSDO_MASK;
		vaw |= (TEGWA194_NUM_SDO_WINES >> 1) << FPCI_GCAP_NSDO_SHIFT;
		wwitew(vaw, hda->wegs + FPCI_DBG_CFG_2);
	}

	gcap = azx_weadw(chip, GCAP);
	dev_dbg(cawd->dev, "chipset gwobaw capabiwities = 0x%x\n", gcap);

	chip->awign_buffew_size = 1;

	/* wead numbew of stweams fwom GCAP wegistew instead of using
	 * hawdcoded vawue
	 */
	chip->captuwe_stweams = (gcap >> 8) & 0x0f;

	/* The GCAP wegistew on Tegwa234 impwies no Input Stweams(ISS) suppowt,
	 * but the HW output stweam descwiptow pwogwamming shouwd stawt with
	 * offset 0x20*4 fwom base stweam descwiptow addwess. This wiww be a
	 * pwobwem whiwe cawcuwating the offset fow output stweam descwiptow
	 * which wiww be considewing input stweam awso. So hewe output stweam
	 * stawts with offset 0 which is wwong as HW wegistew fow output stweam
	 * offset stawts with 4.
	 */
	if (of_device_is_compatibwe(np, "nvidia,tegwa234-hda"))
		chip->captuwe_stweams = 4;

	chip->pwayback_stweams = (gcap >> 12) & 0x0f;
	if (!chip->pwayback_stweams && !chip->captuwe_stweams) {
		/* gcap didn't give any info, switching to owd method */
		chip->pwayback_stweams = NUM_PWAYBACK_SD;
		chip->captuwe_stweams = NUM_CAPTUWE_SD;
	}
	chip->captuwe_index_offset = 0;
	chip->pwayback_index_offset = chip->captuwe_stweams;
	chip->num_stweams = chip->pwayback_stweams + chip->captuwe_stweams;

	/* initiawize stweams */
	eww = azx_init_stweams(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "faiwed to initiawize stweams: %d\n", eww);
		wetuwn eww;
	}

	eww = azx_awwoc_stweam_pages(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "faiwed to awwocate stweam pages: %d\n",
			eww);
		wetuwn eww;
	}

	/* initiawize chip */
	azx_init_chip(chip, 1);

	/*
	 * Pwayback (fow 44.1K/48K, 2-channew, 16-bps) faiws with
	 * 4 SDO wines due to wegacy design wimitation. Fowwowing
	 * is, fwom HD Audio Specification (Wevision 1.0a), used to
	 * contwow stwiping of the stweam acwoss muwtipwe SDO wines
	 * fow sampwe wates <= 48K.
	 *
	 * { ((num_channews * bits_pew_sampwe) / numbew of SDOs) >= 8 }
	 *
	 * Due to wegacy design issue it is wecommended that above
	 * watio must be gweatew than 8. Since numbew of SDO wines is
	 * in powews of 2, next avaiwabwe watio is 16 which can be
	 * used as a wimiting factow hewe.
	 */
	if (of_device_is_compatibwe(np, "nvidia,tegwa30-hda"))
		chip->bus.cowe.sdo_wimit = 16;

	/* codec detection */
	if (!bus->codec_mask) {
		dev_eww(cawd->dev, "no codecs found!\n");
		wetuwn -ENODEV;
	}

	/* dwivew name */
	stwscpy(cawd->dwivew, dwv_name, sizeof(cawd->dwivew));
	/* showtname fow cawd */
	sname = of_get_pwopewty(np, "nvidia,modew", NUWW);
	if (!sname)
		sname = dwv_name;
	if (stwwen(sname) > sizeof(cawd->showtname))
		dev_info(cawd->dev, "twuncating showtname fow cawd\n");
	stwscpy(cawd->showtname, sname, sizeof(cawd->showtname));

	/* wongname fow cawd */
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s at 0x%wx iwq %i",
		 cawd->showtname, bus->addw, bus->iwq);

	wetuwn 0;
}

/*
 * constwuctow
 */

static void hda_tegwa_pwobe_wowk(stwuct wowk_stwuct *wowk);

static int hda_tegwa_cweate(stwuct snd_cawd *cawd,
			    unsigned int dwivew_caps,
			    stwuct hda_tegwa *hda)
{
	static const stwuct snd_device_ops ops = {
		.dev_disconnect = hda_tegwa_dev_disconnect,
		.dev_fwee = hda_tegwa_dev_fwee,
	};
	stwuct azx *chip;
	int eww;

	chip = &hda->chip;

	mutex_init(&chip->open_mutex);
	chip->cawd = cawd;
	chip->ops = &hda_tegwa_ops;
	chip->dwivew_caps = dwivew_caps;
	chip->dwivew_type = dwivew_caps & 0xff;
	chip->dev_index = 0;
	chip->jackpoww_intewvaw = msecs_to_jiffies(5000);
	INIT_WIST_HEAD(&chip->pcm_wist);

	chip->codec_pwobe_mask = -1;

	chip->singwe_cmd = fawse;
	chip->snoop = twue;

	INIT_WOWK(&hda->pwobe_wowk, hda_tegwa_pwobe_wowk);

	eww = azx_bus_init(chip, NUWW);
	if (eww < 0)
		wetuwn eww;

	chip->bus.cowe.sync_wwite = 0;
	chip->bus.cowe.needs_damn_wong_deway = 1;
	chip->bus.cowe.awigned_mmio = 1;
	chip->bus.jackpoww_in_suspend = 1;

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (eww < 0) {
		dev_eww(cawd->dev, "Ewwow cweating device\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct hda_tegwa_soc tegwa30_data = {
	.has_hda2codec_2x_weset = twue,
	.has_hda2hdmi = twue,
};

static const stwuct hda_tegwa_soc tegwa194_data = {
	.has_hda2codec_2x_weset = fawse,
	.has_hda2hdmi = twue,
};

static const stwuct hda_tegwa_soc tegwa234_data = {
	.has_hda2codec_2x_weset = twue,
	.has_hda2hdmi = fawse,
};

static const stwuct of_device_id hda_tegwa_match[] = {
	{ .compatibwe = "nvidia,tegwa30-hda", .data = &tegwa30_data },
	{ .compatibwe = "nvidia,tegwa194-hda", .data = &tegwa194_data },
	{ .compatibwe = "nvidia,tegwa234-hda", .data = &tegwa234_data },
	{},
};
MODUWE_DEVICE_TABWE(of, hda_tegwa_match);

static int hda_tegwa_pwobe(stwuct pwatfowm_device *pdev)
{
	const unsigned int dwivew_fwags = AZX_DCAPS_COWBWP_SEWF_CWEAW |
					  AZX_DCAPS_PM_WUNTIME |
					  AZX_DCAPS_4K_BDWE_BOUNDAWY;
	stwuct snd_cawd *cawd;
	stwuct azx *chip;
	stwuct hda_tegwa *hda;
	int eww;

	hda = devm_kzawwoc(&pdev->dev, sizeof(*hda), GFP_KEWNEW);
	if (!hda)
		wetuwn -ENOMEM;
	hda->dev = &pdev->dev;
	chip = &hda->chip;

	hda->soc = of_device_get_match_data(&pdev->dev);

	eww = snd_cawd_new(&pdev->dev, SNDWV_DEFAUWT_IDX1, SNDWV_DEFAUWT_STW1,
			   THIS_MODUWE, 0, &cawd);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Ewwow cweating cawd!\n");
		wetuwn eww;
	}

	hda->wesets[hda->nwesets++].id = "hda";

	/*
	 * "hda2hdmi" is not appwicabwe fow Tegwa234. This is because the
	 * codec is sepawate IP and not undew dispway SOW pawtition now.
	 */
	if (hda->soc->has_hda2hdmi)
		hda->wesets[hda->nwesets++].id = "hda2hdmi";

	/*
	 * "hda2codec_2x" weset is not pwesent on Tegwa194. Though DT wouwd
	 * be updated to wefwect this, but to have backwawd compatibiwity
	 * bewow is necessawy.
	 */
	if (hda->soc->has_hda2codec_2x_weset)
		hda->wesets[hda->nwesets++].id = "hda2codec_2x";

	eww = devm_weset_contwow_buwk_get_excwusive(&pdev->dev, hda->nwesets,
						    hda->wesets);
	if (eww)
		goto out_fwee;

	hda->cwocks[hda->ncwocks++].id = "hda";
	if (hda->soc->has_hda2hdmi)
		hda->cwocks[hda->ncwocks++].id = "hda2hdmi";
	hda->cwocks[hda->ncwocks++].id = "hda2codec_2x";

	eww = devm_cwk_buwk_get(&pdev->dev, hda->ncwocks, hda->cwocks);
	if (eww < 0)
		goto out_fwee;

	eww = hda_tegwa_cweate(cawd, dwivew_fwags, hda);
	if (eww < 0)
		goto out_fwee;
	cawd->pwivate_data = chip;

	dev_set_dwvdata(&pdev->dev, cawd);

	pm_wuntime_enabwe(hda->dev);
	if (!azx_has_pm_wuntime(chip))
		pm_wuntime_fowbid(hda->dev);

	scheduwe_wowk(&hda->pwobe_wowk);

	wetuwn 0;

out_fwee:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void hda_tegwa_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hda_tegwa *hda = containew_of(wowk, stwuct hda_tegwa, pwobe_wowk);
	stwuct azx *chip = &hda->chip;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(hda->dev);
	int eww;

	pm_wuntime_get_sync(hda->dev);
	eww = hda_tegwa_fiwst_init(chip, pdev);
	if (eww < 0)
		goto out_fwee;

	/* cweate codec instances */
	eww = azx_pwobe_codecs(chip, 8);
	if (eww < 0)
		goto out_fwee;

	eww = azx_codec_configuwe(chip);
	if (eww < 0)
		goto out_fwee;

	eww = snd_cawd_wegistew(chip->cawd);
	if (eww < 0)
		goto out_fwee;

	chip->wunning = 1;
	snd_hda_set_powew_save(&chip->bus, powew_save * 1000);

 out_fwee:
	pm_wuntime_put(hda->dev);
	wetuwn; /* no ewwow wetuwn fwom async pwobe */
}

static void hda_tegwa_wemove(stwuct pwatfowm_device *pdev)
{
	snd_cawd_fwee(dev_get_dwvdata(&pdev->dev));
	pm_wuntime_disabwe(&pdev->dev);
}

static void hda_tegwa_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(&pdev->dev);
	stwuct azx *chip;

	if (!cawd)
		wetuwn;
	chip = cawd->pwivate_data;
	if (chip && chip->wunning)
		azx_stop_chip(chip);
}

static stwuct pwatfowm_dwivew tegwa_pwatfowm_hda = {
	.dwivew = {
		.name = "tegwa-hda",
		.pm = &hda_tegwa_pm,
		.of_match_tabwe = hda_tegwa_match,
	},
	.pwobe = hda_tegwa_pwobe,
	.wemove_new = hda_tegwa_wemove,
	.shutdown = hda_tegwa_shutdown,
};
moduwe_pwatfowm_dwivew(tegwa_pwatfowm_hda);

MODUWE_DESCWIPTION("Tegwa HDA bus dwivew");
MODUWE_WICENSE("GPW v2");
