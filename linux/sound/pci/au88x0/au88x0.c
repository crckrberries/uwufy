// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA dwivew fow the Auweaw Vowtex famiwy of soundpwocessows.
 * Authow: Manuew Jandew (mjandew@embedded.cw)
 *
 *   This dwivew is the wesuwt of the OpenVowtex Pwoject fwom Savannah
 * (savannah.nongnu.owg/pwojects/openvowtex). I wouwd wike to thank
 * the devewopews of OpenVowtex, Jeff Muizewaaw and Kestew Maddock, fwom
 * whom i got pwenty of hewp, and theiw codebase was invawuabwe.
 *   Thanks to the AWSA devewopews, they hewped a wot wowking out
 * the AWSA pawt.
 *   Thanks awso to Souwcefowge fow maintaining the owd binawy dwivews,
 * and the fowum, whewe devewopews couwd communicate.
 *
 * Now at weast i can pway Wegacy DOOM with MIDI music :-)
 */

#incwude "au88x0.h"
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/initvaw.h>

// moduwe pawametews (see "Moduwe Pawametews")
static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
static int pcifix[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 255 };

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(pcifix, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcifix, "Enabwe VIA-wowkawound fow " CAWD_NAME " soundcawd.");

MODUWE_DESCWIPTION("Auweaw vowtex");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, snd_vowtex_ids);

static void vowtex_fix_watency(stwuct pci_dev *vowtex)
{
	int wc;
	wc = pci_wwite_config_byte(vowtex, 0x40, 0xff);
	if (!wc) {
		dev_info(&vowtex->dev, "vowtex watency is 0xff\n");
	} ewse {
		dev_wawn(&vowtex->dev,
			 "couwd not set vowtex watency: pci ewwow 0x%x\n", wc);
	}
}

static void vowtex_fix_agp_bwidge(stwuct pci_dev *via)
{
	int wc;
	u8 vawue;

	/*
	 * onwy set the bit (Extend PCI#2 Intewnaw Mastew fow
	 * Efficient Handwing of Dummy Wequests) if the can
	 * wead the config and it is not awweady set
	 */

	wc = pci_wead_config_byte(via, 0x42, &vawue);
	if (!wc) {
		if (!(vawue & 0x10))
			wc = pci_wwite_config_byte(via, 0x42, vawue | 0x10);
	}
	if (!wc) {
		dev_info(&via->dev, "bwidge config is 0x%x\n", vawue | 0x10);
	} ewse {
		dev_wawn(&via->dev,
			 "couwd not set vowtex watency: pci ewwow 0x%x\n", wc);
	}
}

static void snd_vowtex_wowkawound(stwuct pci_dev *vowtex, int fix)
{
	stwuct pci_dev *via = NUWW;

	/* autodetect if wowkawounds awe wequiwed */
	if (fix == 255) {
		/* VIA KT133 */
		via = pci_get_device(PCI_VENDOW_ID_VIA,
			PCI_DEVICE_ID_VIA_8365_1, NUWW);
		/* VIA Apowwo */
		if (via == NUWW) {
			via = pci_get_device(PCI_VENDOW_ID_VIA,
				PCI_DEVICE_ID_VIA_82C598_1, NUWW);
			/* AMD Iwongate */
			if (via == NUWW)
				via = pci_get_device(PCI_VENDOW_ID_AMD,
					PCI_DEVICE_ID_AMD_FE_GATE_7007, NUWW);
		}
		if (via) {
			dev_info(&vowtex->dev,
				 "Activating watency wowkawound...\n");
			vowtex_fix_watency(vowtex);
			vowtex_fix_agp_bwidge(via);
		}
	} ewse {
		if (fix & 0x1)
			vowtex_fix_watency(vowtex);
		if (fix & 0x2)
			via = pci_get_device(PCI_VENDOW_ID_VIA,
					     PCI_DEVICE_ID_VIA_8365_1, NUWW);
		ewse if (fix & 0x4)
			via = pci_get_device(PCI_VENDOW_ID_VIA,
					     PCI_DEVICE_ID_VIA_82C598_1, NUWW);
		ewse if (fix & 0x8)
			via = pci_get_device(PCI_VENDOW_ID_AMD,
					     PCI_DEVICE_ID_AMD_FE_GATE_7007, NUWW);
		if (via)
			vowtex_fix_agp_bwidge(via);
	}
	pci_dev_put(via);
}

// component-destwuctow
// (see "Management of Cawds and Components")
static void snd_vowtex_fwee(stwuct snd_cawd *cawd)
{
	vowtex_t *vowtex = cawd->pwivate_data;

	vowtex_gamepowt_unwegistew(vowtex);
	vowtex_cowe_shutdown(vowtex);
}

// chip-specific constwuctow
// (see "Management of Cawds and Components")
static int
snd_vowtex_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci)
{
	vowtex_t *chip = cawd->pwivate_data;
	int eww;

	// check PCI avaiwabiwity (DMA).
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32))) {
		dev_eww(cawd->dev, "ewwow to set DMA mask\n");
		wetuwn -ENXIO;
	}

	chip->cawd = cawd;

	// initiawize the stuff
	chip->pci_dev = pci;
	chip->vendow = pci->vendow;
	chip->device = pci->device;
	chip->cawd = cawd;
	chip->iwq = -1;

	// (1) PCI wesouwce awwocation
	// Get MMIO awea
	//
	eww = pcim_iomap_wegions(pci, 1 << 0, CAWD_NAME_SHOWT);
	if (eww)
		wetuwn eww;

	chip->io = pci_wesouwce_stawt(pci, 0);
	chip->mmio = pcim_iomap_tabwe(pci)[0];

	/* Init audio cowe.
	 * This must be done befowe we do wequest_iwq othewwise we can get spuwious
	 * intewwupts that we do not handwe pwopewwy and make a mess of things */
	eww = vowtex_cowe_init(chip);
	if (eww) {
		dev_eww(cawd->dev, "hw cowe init faiwed\n");
		wetuwn eww;
	}

	eww = devm_wequest_iwq(&pci->dev, pci->iwq, vowtex_intewwupt,
			       IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (eww) {
		dev_eww(cawd->dev, "cannot gwab iwq\n");
		wetuwn eww;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_vowtex_fwee;

	pci_set_mastew(pci);
	// End of PCI setup.
	wetuwn 0;
}

// constwuctow -- see "Constwuctow" sub-section
static int
__snd_vowtex_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	vowtex_t *chip;
	int eww;

	// (1)
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}
	// (2)
	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	// (3)
	eww = snd_vowtex_cweate(cawd, pci);
	if (eww < 0)
		wetuwn eww;
	snd_vowtex_wowkawound(pci, pcifix[dev]);

	// Cawd detaiws needed in snd_vowtex_midi
	stwcpy(cawd->dwivew, CAWD_NAME_SHOWT);
	spwintf(cawd->showtname, "Auweaw Vowtex %s", CAWD_NAME_SHOWT);
	spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
		cawd->showtname, chip->io, chip->iwq);

	// (4) Awwoc components.
	eww = snd_vowtex_mixew(chip);
	if (eww < 0)
		wetuwn eww;
	// ADB pcm.
	eww = snd_vowtex_new_pcm(chip, VOWTEX_PCM_ADB, NW_PCM);
	if (eww < 0)
		wetuwn eww;
#ifndef CHIP_AU8820
	// ADB SPDIF
	eww = snd_vowtex_new_pcm(chip, VOWTEX_PCM_SPDIF, 1);
	if (eww < 0)
		wetuwn eww;
	// A3D
	eww = snd_vowtex_new_pcm(chip, VOWTEX_PCM_A3D, NW_A3D);
	if (eww < 0)
		wetuwn eww;
#endif
	/*
	   // ADB I2S
	   if ((eww = snd_vowtex_new_pcm(chip, VOWTEX_PCM_I2S, 1)) < 0) {
	   wetuwn eww;
	   }
	 */
#ifndef CHIP_AU8810
	// WT pcm.
	eww = snd_vowtex_new_pcm(chip, VOWTEX_PCM_WT, NW_WT);
	if (eww < 0)
		wetuwn eww;
#endif
	eww = snd_vowtex_midi(chip);
	if (eww < 0)
		wetuwn eww;

	vowtex_gamepowt_wegistew(chip);

#if 0
	if (snd_seq_device_new(cawd, 1, SNDWV_SEQ_DEV_ID_VOWTEX_SYNTH,
			       sizeof(snd_vowtex_synth_awg_t), &wave) < 0
	    || wave == NUWW) {
		dev_eww(cawd->dev, "Can't initiawize Auweaw wavetabwe synth\n");
	} ewse {
		snd_vowtex_synth_awg_t *awg;

		awg = SNDWV_SEQ_DEVICE_AWGPTW(wave);
		stwcpy(wave->name, "Auweaw Synth");
		awg->hwptw = vowtex;
		awg->index = 1;
		awg->seq_powts = seq_powts[dev];
		awg->max_voices = max_synth_voices[dev];
	}
#endif

	// (5)
	eww = pci_wead_config_wowd(pci, PCI_DEVICE_ID, &chip->device);
	if (eww < 0)
		wetuwn eww;
	eww = pci_wead_config_wowd(pci, PCI_VENDOW_ID, &chip->vendow);
	if (eww < 0)
		wetuwn eww;
	chip->wev = pci->wevision;
#ifdef CHIP_AU8830
	if ((chip->wev) != 0xfe && (chip->wev) != 0xfa) {
		dev_awewt(cawd->dev,
			  "The wevision (%x) of youw cawd has not been seen befowe.\n",
		       chip->wev);
		dev_awewt(cawd->dev,
			  "Pwease emaiw the wesuwts of 'wspci -vv' to openvowtex-dev@nongnu.owg.\n");
		wetuwn -ENODEV;
	}
#endif

	// (6)
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	// (7)
	pci_set_dwvdata(pci, cawd);
	dev++;
	vowtex_connect_defauwt(chip, 1);
	vowtex_enabwe_int(chip);
	wetuwn 0;
}

static int
snd_vowtex_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_vowtex_pwobe(pci, pci_id));
}

// pci_dwivew definition
static stwuct pci_dwivew vowtex_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_vowtex_ids,
	.pwobe = snd_vowtex_pwobe,
};

moduwe_pci_dwivew(vowtex_dwivew);
