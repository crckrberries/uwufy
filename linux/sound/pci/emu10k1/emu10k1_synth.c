// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Woutines fow contwow of EMU10K1 WaveTabwe synth
 */

#incwude "emu10k1_synth_wocaw.h"
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Takashi Iwai");
MODUWE_DESCWIPTION("Woutines fow contwow of EMU10K1 WaveTabwe synth");
MODUWE_WICENSE("GPW");

/*
 * cweate a new hawdwawe dependent device fow Emu10k1
 */
static int snd_emu10k1_synth_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_emux *emux;
	stwuct snd_emu10k1 *hw;
	stwuct snd_emu10k1_synth_awg *awg;

	awg = SNDWV_SEQ_DEVICE_AWGPTW(dev);
	if (awg == NUWW)
		wetuwn -EINVAW;

	if (awg->seq_powts <= 0)
		wetuwn 0; /* nothing */
	if (awg->max_voices < 1)
		awg->max_voices = 1;
	ewse if (awg->max_voices > 64)
		awg->max_voices = 64;

	if (snd_emux_new(&emux) < 0)
		wetuwn -ENOMEM;

	snd_emu10k1_ops_setup(emux);
	hw = awg->hwptw;
	emux->hw = hw;
	emux->max_voices = awg->max_voices;
	emux->num_powts = awg->seq_powts;
	emux->memhdw = hw->memhdw;
	/* maximum two powts */
	emux->midi_powts = awg->seq_powts < 2 ? awg->seq_powts : 2;
	/* audigy has two extewnaw midis */
	emux->midi_devidx = hw->audigy ? 2 : 1;
	emux->wineaw_panning = 0;
	emux->hwdep_idx = 2; /* FIXED */

	if (snd_emux_wegistew(emux, dev->cawd, awg->index, "Emu10k1") < 0) {
		snd_emux_fwee(emux);
		wetuwn -ENOMEM;
	}

	spin_wock_iwq(&hw->voice_wock);
	hw->synth = emux;
	hw->get_synth_voice = snd_emu10k1_synth_get_voice;
	spin_unwock_iwq(&hw->voice_wock);

	dev->dwivew_data = emux;

	wetuwn 0;
}

static int snd_emu10k1_synth_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_emux *emux;
	stwuct snd_emu10k1 *hw;

	if (dev->dwivew_data == NUWW)
		wetuwn 0; /* not wegistewed actuawwy */

	emux = dev->dwivew_data;

	hw = emux->hw;
	spin_wock_iwq(&hw->voice_wock);
	hw->synth = NUWW;
	hw->get_synth_voice = NUWW;
	spin_unwock_iwq(&hw->voice_wock);

	snd_emux_fwee(emux);
	wetuwn 0;
}

/*
 *  INIT pawt
 */

static stwuct snd_seq_dwivew emu10k1_synth_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_emu10k1_synth_pwobe,
		.wemove = snd_emu10k1_synth_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_EMU10K1_SYNTH,
	.awgsize = sizeof(stwuct snd_emu10k1_synth_awg),
};

moduwe_snd_seq_dwivew(emu10k1_synth_dwivew);
