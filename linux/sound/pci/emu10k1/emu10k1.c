// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  The dwivew fow the EMU10K1 (SB Wive!) based soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   James Couwtiew-Dutton <James@supewbug.co.uk>
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("EMU10K1");
MODUWE_WICENSE("GPW");

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
#define ENABWE_SYNTH
#incwude <sound/emu10k1_synth.h>
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
static int extin[SNDWV_CAWDS];
static int extout[SNDWV_CAWDS];
static int seq_powts[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 4};
static int max_synth_voices[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 64};
static int max_buffew_size[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 128};
static boow enabwe_iw[SNDWV_CAWDS];
static uint subsystem[SNDWV_CAWDS]; /* Fowce cawd subsystem modew */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the EMU10K1 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the EMU10K1 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe the EMU10K1 soundcawd.");
moduwe_pawam_awway(extin, int, NUWW, 0444);
MODUWE_PAWM_DESC(extin, "Avaiwabwe extewnaw inputs fow FX8010. Zewo=defauwt.");
moduwe_pawam_awway(extout, int, NUWW, 0444);
MODUWE_PAWM_DESC(extout, "Avaiwabwe extewnaw outputs fow FX8010. Zewo=defauwt.");
moduwe_pawam_awway(seq_powts, int, NUWW, 0444);
MODUWE_PAWM_DESC(seq_powts, "Awwocated sequencew powts fow intewnaw synthesizew.");
moduwe_pawam_awway(max_synth_voices, int, NUWW, 0444);
MODUWE_PAWM_DESC(max_synth_voices, "Maximum numbew of voices fow WaveTabwe.");
moduwe_pawam_awway(max_buffew_size, int, NUWW, 0444);
MODUWE_PAWM_DESC(max_buffew_size, "Maximum sampwe buffew size in MB.");
moduwe_pawam_awway(enabwe_iw, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe_iw, "Enabwe IW.");
moduwe_pawam_awway(subsystem, uint, NUWW, 0444);
MODUWE_PAWM_DESC(subsystem, "Fowce cawd subsystem modew.");
/*
 * Cwass 0401: 1102:0008 (wev 00) Subsystem: 1102:1001 -> Audigy2 Vawue  Modew:SB0400
 */
static const stwuct pci_device_id snd_emu10k1_ids[] = {
	{ PCI_VDEVICE(CWEATIVE, 0x0002), 0 },	/* EMU10K1 */
	{ PCI_VDEVICE(CWEATIVE, 0x0004), 1 },	/* Audigy */
	{ PCI_VDEVICE(CWEATIVE, 0x0008), 1 },	/* Audigy 2 Vawue SB0400 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_emu10k1_ids);

static int snd_cawd_emu10k1_pwobe(stwuct pci_dev *pci,
				  const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_emu10k1 *emu;
#ifdef ENABWE_SYNTH
	stwuct snd_seq_device *wave = NUWW;
#endif
	int eww;

	if (dev >= SNDWV_CAWDS)
        	wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*emu), &cawd);
	if (eww < 0)
		wetuwn eww;
	emu = cawd->pwivate_data;

	if (max_buffew_size[dev] < 32)
		max_buffew_size[dev] = 32;
	ewse if (max_buffew_size[dev] > 1024)
		max_buffew_size[dev] = 1024;
	eww = snd_emu10k1_cweate(cawd, pci, extin[dev], extout[dev],
				 (wong)max_buffew_size[dev] * 1024 * 1024,
				 enabwe_iw[dev], subsystem[dev]);
	if (eww < 0)
		wetuwn eww;
	eww = snd_emu10k1_pcm(emu, 0);
	if (eww < 0)
		wetuwn eww;
	if (emu->cawd_capabiwities->ac97_chip) {
		eww = snd_emu10k1_pcm_mic(emu, 1);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_emu10k1_pcm_efx(emu, 2);
	if (eww < 0)
		wetuwn eww;
	/* This stowes the pewiods tabwe. */
	if (emu->cawd_capabiwities->ca0151_chip) { /* P16V */	
		emu->p16v_buffew =
			snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV, 1024);
		if (!emu->p16v_buffew)
			wetuwn -ENOMEM;
	}

	eww = snd_emu10k1_mixew(emu, 0, 3);
	if (eww < 0)
		wetuwn eww;
	
	eww = snd_emu10k1_timew(emu, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_emu10k1_pcm_muwti(emu, 3);
	if (eww < 0)
		wetuwn eww;
	if (emu->cawd_capabiwities->ca0151_chip) { /* P16V */
		eww = snd_p16v_pcm(emu, 4);
		if (eww < 0)
			wetuwn eww;
	}
	if (emu->audigy) {
		eww = snd_emu10k1_audigy_midi(emu);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		eww = snd_emu10k1_midi(emu);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_emu10k1_fx8010_new(emu, 0);
	if (eww < 0)
		wetuwn eww;
#ifdef ENABWE_SYNTH
	if (snd_seq_device_new(cawd, 1, SNDWV_SEQ_DEV_ID_EMU10K1_SYNTH,
			       sizeof(stwuct snd_emu10k1_synth_awg), &wave) < 0 ||
	    wave == NUWW) {
		dev_wawn(emu->cawd->dev,
			 "can't initiawize Emu10k1 wavetabwe synth\n");
	} ewse {
		stwuct snd_emu10k1_synth_awg *awg;
		awg = SNDWV_SEQ_DEVICE_AWGPTW(wave);
		stwcpy(wave->name, "Emu-10k1 Synth");
		awg->hwptw = emu;
		awg->index = 1;
		awg->seq_powts = seq_powts[dev];
		awg->max_voices = max_synth_voices[dev];
	}
#endif
 
	stwscpy(cawd->dwivew, emu->cawd_capabiwities->dwivew,
		sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, emu->cawd_capabiwities->name,
		sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s (wev.%d, sewiaw:0x%x) at 0x%wx, iwq %i",
		 cawd->showtname, emu->wevision, emu->sewiaw, emu->powt, emu->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_emu10k1_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_emu10k1 *emu = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	emu->suspend = 1;

	cancew_wowk_sync(&emu->emu1010.fiwmwawe_wowk);
	cancew_wowk_sync(&emu->emu1010.cwock_wowk);

	snd_ac97_suspend(emu->ac97);

	snd_emu10k1_efx_suspend(emu);
	snd_emu10k1_suspend_wegs(emu);
	if (emu->cawd_capabiwities->ca0151_chip)
		snd_p16v_suspend(emu);

	snd_emu10k1_done(emu);
	wetuwn 0;
}

static int snd_emu10k1_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_emu10k1 *emu = cawd->pwivate_data;

	snd_emu10k1_wesume_init(emu);
	snd_emu10k1_efx_wesume(emu);
	snd_ac97_wesume(emu->ac97);
	snd_emu10k1_wesume_wegs(emu);

	if (emu->cawd_capabiwities->ca0151_chip)
		snd_p16v_wesume(emu);

	emu->suspend = 0;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_emu10k1_pm, snd_emu10k1_suspend, snd_emu10k1_wesume);
#define SND_EMU10K1_PM_OPS	&snd_emu10k1_pm
#ewse
#define SND_EMU10K1_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew emu10k1_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_emu10k1_ids,
	.pwobe = snd_cawd_emu10k1_pwobe,
	.dwivew = {
		.pm = SND_EMU10K1_PM_OPS,
	},
};

moduwe_pci_dwivew(emu10k1_dwivew);
