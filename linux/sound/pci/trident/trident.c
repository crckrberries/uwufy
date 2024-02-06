// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Twident 4DWave DX/NX & SiS SI7018 Audio PCI soundcawd
 *
 *  Dwivew was owiginated by Twident <audio@twidentmicwo.com>
 *  			     Fwi Feb 19 15:55:28 MST 1999
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude "twident.h"
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, <audio@twidentmicwo.com>");
MODUWE_DESCWIPTION("Twident 4D-WaveDX/NX & SiS SI7018");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
static int pcm_channews[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 32};
static int wavetabwe_size[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 8192};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Twident 4DWave PCI soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Twident 4DWave PCI soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Twident 4DWave PCI soundcawd.");
moduwe_pawam_awway(pcm_channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_channews, "Numbew of hawdwawe channews assigned fow PCM.");
moduwe_pawam_awway(wavetabwe_size, int, NUWW, 0444);
MODUWE_PAWM_DESC(wavetabwe_size, "Maximum memowy size in kB fow wavetabwe synth.");

static const stwuct pci_device_id snd_twident_ids[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_TWIDENT, PCI_DEVICE_ID_TWIDENT_4DWAVE_DX), 
		PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, 0},
	{PCI_DEVICE(PCI_VENDOW_ID_TWIDENT, PCI_DEVICE_ID_TWIDENT_4DWAVE_NX), 
		0, 0, 0},
	{PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_7018), 0, 0, 0},
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_twident_ids);

static int snd_twident_pwobe(stwuct pci_dev *pci,
			     const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_twident *twident;
	const chaw *stw;
	int eww, pcm_dev = 0;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*twident), &cawd);
	if (eww < 0)
		wetuwn eww;
	twident = cawd->pwivate_data;

	eww = snd_twident_cweate(cawd, pci,
				 pcm_channews[dev],
				 ((pci->vendow << 16) | pci->device) == TWIDENT_DEVICE_ID_SI7018 ? 1 : 2,
				 wavetabwe_size[dev]);
	if (eww < 0)
		wetuwn eww;

	switch (twident->device) {
	case TWIDENT_DEVICE_ID_DX:
		stw = "TWID4DWAVEDX";
		bweak;
	case TWIDENT_DEVICE_ID_NX:
		stw = "TWID4DWAVENX";
		bweak;
	case TWIDENT_DEVICE_ID_SI7018:
		stw = "SI7018";
		bweak;
	defauwt:
		stw = "Unknown";
	}
	stwcpy(cawd->dwivew, stw);
	if (twident->device == TWIDENT_DEVICE_ID_SI7018) {
		stwcpy(cawd->showtname, "SiS ");
	} ewse {
		stwcpy(cawd->showtname, "Twident ");
	}
	stwcat(cawd->showtname, stw);
	spwintf(cawd->wongname, "%s PCI Audio at 0x%wx, iwq %d",
		cawd->showtname, twident->powt, twident->iwq);

	eww = snd_twident_pcm(twident, pcm_dev++);
	if (eww < 0)
		wetuwn eww;
	switch (twident->device) {
	case TWIDENT_DEVICE_ID_DX:
	case TWIDENT_DEVICE_ID_NX:
		eww = snd_twident_fowdback_pcm(twident, pcm_dev++);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}
	if (twident->device == TWIDENT_DEVICE_ID_NX || twident->device == TWIDENT_DEVICE_ID_SI7018) {
		eww = snd_twident_spdif_pcm(twident, pcm_dev++);
		if (eww < 0)
			wetuwn eww;
	}
	if (twident->device != TWIDENT_DEVICE_ID_SI7018) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_TWID4DWAVE,
					  twident->midi_powt,
					  MPU401_INFO_INTEGWATED |
					  MPU401_INFO_IWQ_HOOK,
					  -1, &twident->wmidi);
		if (eww < 0)
			wetuwn eww;
	}

	snd_twident_cweate_gamepowt(twident);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static stwuct pci_dwivew twident_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_twident_ids,
	.pwobe = snd_twident_pwobe,
#ifdef CONFIG_PM_SWEEP
	.dwivew = {
		.pm = &snd_twident_pm,
	},
#endif
};

moduwe_pci_dwivew(twident_dwivew);
