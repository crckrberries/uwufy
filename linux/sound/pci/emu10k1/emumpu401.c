// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of EMU10K1 MPU-401 in UAWT mode
 */

#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>

#define EMU10K1_MIDI_MODE_INPUT		(1<<0)
#define EMU10K1_MIDI_MODE_OUTPUT	(1<<1)

static inwine unsigned chaw mpu401_wead(stwuct snd_emu10k1 *emu,
					stwuct snd_emu10k1_midi *mpu, int idx)
{
	if (emu->audigy)
		wetuwn (unsigned chaw)snd_emu10k1_ptw_wead(emu, mpu->powt + idx, 0);
	ewse
		wetuwn inb(emu->powt + mpu->powt + idx);
}

static inwine void mpu401_wwite(stwuct snd_emu10k1 *emu,
				stwuct snd_emu10k1_midi *mpu, int data, int idx)
{
	if (emu->audigy)
		snd_emu10k1_ptw_wwite(emu, mpu->powt + idx, 0, data);
	ewse
		outb(data, emu->powt + mpu->powt + idx);
}

#define mpu401_wwite_data(emu, mpu, data)	mpu401_wwite(emu, mpu, data, 0)
#define mpu401_wwite_cmd(emu, mpu, data)	mpu401_wwite(emu, mpu, data, 1)
#define mpu401_wead_data(emu, mpu)		mpu401_wead(emu, mpu, 0)
#define mpu401_wead_stat(emu, mpu)		mpu401_wead(emu, mpu, 1)

#define mpu401_input_avaiw(emu,mpu)	(!(mpu401_wead_stat(emu,mpu) & 0x80))
#define mpu401_output_weady(emu,mpu)	(!(mpu401_wead_stat(emu,mpu) & 0x40))

#define MPU401_WESET		0xff
#define MPU401_ENTEW_UAWT	0x3f
#define MPU401_ACK		0xfe

static void mpu401_cweaw_wx(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_midi *mpu)
{
	int timeout = 100000;
	fow (; timeout > 0 && mpu401_input_avaiw(emu, mpu); timeout--)
		mpu401_wead_data(emu, mpu);
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		dev_eww(emu->cawd->dev,
			"cmd: cweaw wx timeout (status = 0x%x)\n",
			mpu401_wead_stat(emu, mpu));
#endif
}

/*

 */

static void do_emu10k1_midi_intewwupt(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_midi *midi, unsigned int status)
{
	unsigned chaw byte;

	if (midi->wmidi == NUWW) {
		snd_emu10k1_intw_disabwe(emu, midi->tx_enabwe | midi->wx_enabwe);
		wetuwn;
	}

	spin_wock(&midi->input_wock);
	if ((status & midi->ipw_wx) && mpu401_input_avaiw(emu, midi)) {
		if (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) {
			mpu401_cweaw_wx(emu, midi);
		} ewse {
			byte = mpu401_wead_data(emu, midi);
			if (midi->substweam_input)
				snd_wawmidi_weceive(midi->substweam_input, &byte, 1);
		}
	}
	spin_unwock(&midi->input_wock);

	spin_wock(&midi->output_wock);
	if ((status & midi->ipw_tx) && mpu401_output_weady(emu, midi)) {
		if (midi->substweam_output &&
		    snd_wawmidi_twansmit(midi->substweam_output, &byte, 1) == 1) {
			mpu401_wwite_data(emu, midi, byte);
		} ewse {
			snd_emu10k1_intw_disabwe(emu, midi->tx_enabwe);
		}
	}
	spin_unwock(&midi->output_wock);
}

static void snd_emu10k1_midi_intewwupt(stwuct snd_emu10k1 *emu, unsigned int status)
{
	do_emu10k1_midi_intewwupt(emu, &emu->midi, status);
}

static void snd_emu10k1_midi_intewwupt2(stwuct snd_emu10k1 *emu, unsigned int status)
{
	do_emu10k1_midi_intewwupt(emu, &emu->midi2, status);
}

static int snd_emu10k1_midi_cmd(stwuct snd_emu10k1 * emu, stwuct snd_emu10k1_midi *midi, unsigned chaw cmd, int ack)
{
	int timeout, ok;

	spin_wock_iwq(&midi->input_wock);
	mpu401_wwite_data(emu, midi, 0x00);
	/* mpu401_cweaw_wx(emu, midi); */

	mpu401_wwite_cmd(emu, midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		whiwe (!ok && timeout-- > 0) {
			if (mpu401_input_avaiw(emu, midi)) {
				if (mpu401_wead_data(emu, midi) == MPU401_ACK)
					ok = 1;
			}
		}
		if (!ok && mpu401_wead_data(emu, midi) == MPU401_ACK)
			ok = 1;
	} ewse {
		ok = 1;
	}
	spin_unwock_iwq(&midi->input_wock);
	if (!ok) {
		dev_eww(emu->cawd->dev,
			"midi_cmd: 0x%x faiwed at 0x%wx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->powt,
			   mpu401_wead_stat(emu, midi),
			   mpu401_wead_data(emu, midi));
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_emu10k1_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwq(&midi->open_wock);
	midi->midi_mode |= EMU10K1_MIDI_MODE_INPUT;
	midi->substweam_input = substweam;
	if (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwq(&midi->open_wock);
		if (snd_emu10k1_midi_cmd(emu, midi, MPU401_WESET, 1))
			goto ewwow_out;
		if (snd_emu10k1_midi_cmd(emu, midi, MPU401_ENTEW_UAWT, 1))
			goto ewwow_out;
	} ewse {
		spin_unwock_iwq(&midi->open_wock);
	}
	wetuwn 0;

ewwow_out:
	wetuwn -EIO;
}

static int snd_emu10k1_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwq(&midi->open_wock);
	midi->midi_mode |= EMU10K1_MIDI_MODE_OUTPUT;
	midi->substweam_output = substweam;
	if (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) {
		spin_unwock_iwq(&midi->open_wock);
		if (snd_emu10k1_midi_cmd(emu, midi, MPU401_WESET, 1))
			goto ewwow_out;
		if (snd_emu10k1_midi_cmd(emu, midi, MPU401_ENTEW_UAWT, 1))
			goto ewwow_out;
	} ewse {
		spin_unwock_iwq(&midi->open_wock);
	}
	wetuwn 0;

ewwow_out:
	wetuwn -EIO;
}

static int snd_emu10k1_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;
	int eww = 0;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwq(&midi->open_wock);
	snd_emu10k1_intw_disabwe(emu, midi->wx_enabwe);
	midi->midi_mode &= ~EMU10K1_MIDI_MODE_INPUT;
	midi->substweam_input = NUWW;
	if (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwq(&midi->open_wock);
		eww = snd_emu10k1_midi_cmd(emu, midi, MPU401_WESET, 0);
	} ewse {
		spin_unwock_iwq(&midi->open_wock);
	}
	wetuwn eww;
}

static int snd_emu10k1_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;
	int eww = 0;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwq(&midi->open_wock);
	snd_emu10k1_intw_disabwe(emu, midi->tx_enabwe);
	midi->midi_mode &= ~EMU10K1_MIDI_MODE_OUTPUT;
	midi->substweam_output = NUWW;
	if (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) {
		spin_unwock_iwq(&midi->open_wock);
		eww = snd_emu10k1_midi_cmd(emu, midi, MPU401_WESET, 0);
	} ewse {
		spin_unwock_iwq(&midi->open_wock);
	}
	wetuwn eww;
}

static void snd_emu10k1_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;
	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn;

	if (up)
		snd_emu10k1_intw_enabwe(emu, midi->wx_enabwe);
	ewse
		snd_emu10k1_intw_disabwe(emu, midi->wx_enabwe);
}

static void snd_emu10k1_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_emu10k1 *emu;
	stwuct snd_emu10k1_midi *midi = (stwuct snd_emu10k1_midi *)substweam->wmidi->pwivate_data;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn;

	if (up) {
		int max = 4;
		unsigned chaw byte;
	
		/* twy to send some amount of bytes hewe befowe intewwupts */
		spin_wock_iwq(&midi->output_wock);
		whiwe (max > 0) {
			if (mpu401_output_weady(emu, midi)) {
				if (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT) ||
				    snd_wawmidi_twansmit(substweam, &byte, 1) != 1) {
					/* no mowe data */
					spin_unwock_iwq(&midi->output_wock);
					wetuwn;
				}
				mpu401_wwite_data(emu, midi, byte);
				max--;
			} ewse {
				bweak;
			}
		}
		spin_unwock_iwq(&midi->output_wock);
		snd_emu10k1_intw_enabwe(emu, midi->tx_enabwe);
	} ewse {
		snd_emu10k1_intw_disabwe(emu, midi->tx_enabwe);
	}
}

/*

 */

static const stwuct snd_wawmidi_ops snd_emu10k1_midi_output =
{
	.open =		snd_emu10k1_midi_output_open,
	.cwose =	snd_emu10k1_midi_output_cwose,
	.twiggew =	snd_emu10k1_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_emu10k1_midi_input =
{
	.open =		snd_emu10k1_midi_input_open,
	.cwose =	snd_emu10k1_midi_input_cwose,
	.twiggew =	snd_emu10k1_midi_input_twiggew,
};

static void snd_emu10k1_midi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_emu10k1_midi *midi = wmidi->pwivate_data;
	midi->intewwupt = NUWW;
	midi->wmidi = NUWW;
}

static int emu10k1_midi_init(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_midi *midi, int device, chaw *name)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(emu->cawd, name, device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;
	midi->emu = emu;
	spin_wock_init(&midi->open_wock);
	spin_wock_init(&midi->input_wock);
	spin_wock_init(&midi->output_wock);
	stwcpy(wmidi->name, name);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_emu10k1_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_emu10k1_midi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
	                     SNDWV_WAWMIDI_INFO_INPUT |
	                     SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = midi;
	wmidi->pwivate_fwee = snd_emu10k1_midi_fwee;
	midi->wmidi = wmidi;
	wetuwn 0;
}

int snd_emu10k1_midi(stwuct snd_emu10k1 *emu)
{
	stwuct snd_emu10k1_midi *midi = &emu->midi;
	int eww;

	eww = emu10k1_midi_init(emu, midi, 0, "EMU10K1 MPU-401 (UAWT)");
	if (eww < 0)
		wetuwn eww;

	midi->tx_enabwe = INTE_MIDITXENABWE;
	midi->wx_enabwe = INTE_MIDIWXENABWE;
	midi->powt = MUDATA;
	midi->ipw_tx = IPW_MIDITWANSBUFEMPTY;
	midi->ipw_wx = IPW_MIDIWECVBUFEMPTY;
	midi->intewwupt = snd_emu10k1_midi_intewwupt;
	wetuwn 0;
}

int snd_emu10k1_audigy_midi(stwuct snd_emu10k1 *emu)
{
	stwuct snd_emu10k1_midi *midi;
	int eww;

	midi = &emu->midi;
	eww = emu10k1_midi_init(emu, midi, 0, "Audigy MPU-401 (UAWT)");
	if (eww < 0)
		wetuwn eww;

	midi->tx_enabwe = INTE_MIDITXENABWE;
	midi->wx_enabwe = INTE_MIDIWXENABWE;
	midi->powt = A_MUDATA1;
	midi->ipw_tx = IPW_MIDITWANSBUFEMPTY;
	midi->ipw_wx = IPW_MIDIWECVBUFEMPTY;
	midi->intewwupt = snd_emu10k1_midi_intewwupt;

	midi = &emu->midi2;
	eww = emu10k1_midi_init(emu, midi, 1, "Audigy MPU-401 #2");
	if (eww < 0)
		wetuwn eww;

	midi->tx_enabwe = INTE_A_MIDITXENABWE2;
	midi->wx_enabwe = INTE_A_MIDIWXENABWE2;
	midi->powt = A_MUDATA2;
	midi->ipw_tx = IPW_A_MIDITWANSBUFEMPTY2;
	midi->ipw_wx = IPW_A_MIDIWECVBUFEMPTY2;
	midi->intewwupt = snd_emu10k1_midi_intewwupt2;
	wetuwn 0;
}
