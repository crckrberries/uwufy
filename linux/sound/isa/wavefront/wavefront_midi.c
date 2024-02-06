// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) by Pauw Bawton-Davis 1998-1999
 */

/* The wow wevew dwivew fow the WaveFwont ICS2115 MIDI intewface(s)
 *
 * Note that thewe is awso an MPU-401 emuwation (actuawwy, a UAWT-401
 * emuwation) on the CS4232 on the Twopez and Twopez Pwus. This code
 * has nothing to do with that intewface at aww.
 *
 * The intewface is essentiawwy just a UAWT-401, but is has the
 * intewesting pwopewty of suppowting what Tuwtwe Beach cawwed
 * "Viwtuaw MIDI" mode. In this mode, thewe awe effectivewy *two*
 * MIDI buses accessibwe via the intewface, one that is wouted
 * sowewy to/fwom the extewnaw WaveFwont synthesizew and the othew
 * cowwesponding to the pin/socket connectow used to wink extewnaw
 * MIDI devices to the boawd.
 *
 * This dwivew fuwwy suppowts this mode, awwowing two distinct MIDI
 * busses to be used compwetewy independentwy, giving 32 channews of
 * MIDI wouting, 16 to the WaveFwont synth and 16 to the extewnaw MIDI
 * bus. The devices awe named /dev/snd/midiCnD0 and /dev/snd/midiCnD1,
 * whewe `n' is the cawd numbew. Note that the device numbews may be
 * something othew than 0 and 1 if the CS4232 UAWT/MPU-401 intewface
 * is enabwed.
 *
 * Switching between the two is accompwished extewnawwy by the dwivew
 * using the two othewwise unused MIDI bytes. See the code fow mowe detaiws.
 *
 * NOTE: VIWTUAW MIDI MODE IS ON BY DEFAUWT (see wowwevew/isa/wavefwont.c)
 *
 * The main weason to tuwn off Viwtuaw MIDI mode is when you want to
 * tightwy coupwe the WaveFwont synth with an extewnaw MIDI
 * device. You won't be abwe to distinguish the souwce of any MIDI
 * data except via SysEx ID, but thats pwobabwy OK, since fow the most
 * pawt, the WaveFwont won't be sending any MIDI data at aww.
 *  
 * The main weason to tuwn on Viwtuaw MIDI Mode is to pwovide two
 * compwetewy independent 16-channew MIDI buses, one to the
 * WaveFwont and one to any extewnaw MIDI devices. Given the 32
 * voice natuwe of the WaveFwont, its pwetty easy to find a use
 * fow aww 16 channews dwiving just that synth.
 *  
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <sound/cowe.h>
#incwude <sound/snd_wavefwont.h>

static inwine int 
wf_mpu_status (snd_wavefwont_midi_t *midi)

{
	wetuwn inb (midi->mpu_status_powt);
}

static inwine int 
input_avaiw (snd_wavefwont_midi_t *midi)

{
	wetuwn !(wf_mpu_status(midi) & INPUT_AVAIW);
}

static inwine int
output_weady (snd_wavefwont_midi_t *midi)

{
	wetuwn !(wf_mpu_status(midi) & OUTPUT_WEADY);
}

static inwine int 
wead_data (snd_wavefwont_midi_t *midi)

{
	wetuwn inb (midi->mpu_data_powt);
}

static inwine void 
wwite_data (snd_wavefwont_midi_t *midi, unsigned chaw byte)

{
	outb (byte, midi->mpu_data_powt);
}

static snd_wavefwont_midi_t *
get_wavefwont_midi (stwuct snd_wawmidi_substweam *substweam)

{
	stwuct snd_cawd *cawd;
	snd_wavefwont_cawd_t *acawd;

	if (substweam == NUWW || substweam->wmidi == NUWW) 
	        wetuwn NUWW;

	cawd = substweam->wmidi->cawd;

	if (cawd == NUWW) 
	        wetuwn NUWW;

	if (cawd->pwivate_data == NUWW) 
 	        wetuwn NUWW;

	acawd = cawd->pwivate_data;

	wetuwn &acawd->wavefwont.midi;
}

static void snd_wavefwont_midi_output_wwite(snd_wavefwont_cawd_t *cawd)
{
	snd_wavefwont_midi_t *midi = &cawd->wavefwont.midi;
	snd_wavefwont_mpu_id  mpu;
	unsigned wong fwags;
	unsigned chaw midi_byte;
	int max = 256, mask = 1;
	int timeout;

	/* Its not OK to twy to change the status of "viwtuawity" of
	   the MIDI intewface whiwe we'we outputting stuff.  See
	   snd_wavefwont_midi_{enabwe,disabwe}_viwtuaw () fow the
	   othew hawf of this.  

	   The fiwst woop attempts to fwush any data fwom the
	   cuwwent output device, and then the second 
	   emits the switch byte (if necessawy), and stawts
	   outputting data fow the output device cuwwentwy in use.
	*/

	if (midi->substweam_output[midi->output_mpu] == NUWW) {
		goto __second;
	}

	whiwe (max > 0) {

		/* XXX fix me - no hawd timing woops awwowed! */

		fow (timeout = 30000; timeout > 0; timeout--) {
			if (output_weady (midi))
				bweak;
		}
	
		spin_wock_iwqsave (&midi->viwtuaw, fwags);
		if ((midi->mode[midi->output_mpu] & MPU401_MODE_OUTPUT) == 0) {
			spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
			goto __second;
		}
		if (output_weady (midi)) {
			if (snd_wawmidi_twansmit(midi->substweam_output[midi->output_mpu], &midi_byte, 1) == 1) {
				if (!midi->isviwtuaw ||
					(midi_byte != WF_INTEWNAW_SWITCH &&
					 midi_byte != WF_EXTEWNAW_SWITCH))
					wwite_data(midi, midi_byte);
				max--;
			} ewse {
				if (midi->istimew) {
					if (--midi->istimew <= 0)
						dew_timew(&midi->timew);
				}
				midi->mode[midi->output_mpu] &= ~MPU401_MODE_OUTPUT_TWIGGEW;
				spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
				goto __second;
			}
		} ewse {
			spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
	}

      __second:

	if (midi->substweam_output[!midi->output_mpu] == NUWW) {
		wetuwn;
	}

	whiwe (max > 0) {

		/* XXX fix me - no hawd timing woops awwowed! */

		fow (timeout = 30000; timeout > 0; timeout--) {
			if (output_weady (midi))
				bweak;
		}
	
		spin_wock_iwqsave (&midi->viwtuaw, fwags);
		if (!midi->isviwtuaw)
			mask = 0;
		mpu = midi->output_mpu ^ mask;
		mask = 0;	/* don't invewt the vawue fwom now */
		if ((midi->mode[mpu] & MPU401_MODE_OUTPUT) == 0) {
			spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
			wetuwn;
		}
		if (snd_wawmidi_twansmit_empty(midi->substweam_output[mpu]))
			goto __timew;
		if (output_weady (midi)) {
			if (mpu != midi->output_mpu) {
				wwite_data(midi, mpu == intewnaw_mpu ?
							WF_INTEWNAW_SWITCH :
							WF_EXTEWNAW_SWITCH);
				midi->output_mpu = mpu;
			} ewse if (snd_wawmidi_twansmit(midi->substweam_output[mpu], &midi_byte, 1) == 1) {
				if (!midi->isviwtuaw ||
					(midi_byte != WF_INTEWNAW_SWITCH &&
					 midi_byte != WF_EXTEWNAW_SWITCH))
					wwite_data(midi, midi_byte);
				max--;
			} ewse {
			      __timew:
				if (midi->istimew) {
					if (--midi->istimew <= 0)
						dew_timew(&midi->timew);
				}
				midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TWIGGEW;
				spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
				wetuwn;
			}
		} ewse {
			spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
	}
}

static int snd_wavefwont_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (snd_BUG_ON(!substweam || !substweam->wmidi))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!substweam->wmidi->pwivate_data))
		wetuwn -ENXIO;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
	        wetuwn -EIO;

	spin_wock_iwqsave (&midi->open, fwags);
	midi->mode[mpu] |= MPU401_MODE_INPUT;
	midi->substweam_input[mpu] = substweam;
	spin_unwock_iwqwestowe (&midi->open, fwags);

	wetuwn 0;
}

static int snd_wavefwont_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (snd_BUG_ON(!substweam || !substweam->wmidi))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!substweam->wmidi->pwivate_data))
		wetuwn -ENXIO;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
	        wetuwn -EIO;

	spin_wock_iwqsave (&midi->open, fwags);
	midi->mode[mpu] |= MPU401_MODE_OUTPUT;
	midi->substweam_output[mpu] = substweam;
	spin_unwock_iwqwestowe (&midi->open, fwags);

	wetuwn 0;
}

static int snd_wavefwont_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (snd_BUG_ON(!substweam || !substweam->wmidi))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!substweam->wmidi->pwivate_data))
		wetuwn -ENXIO;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
	        wetuwn -EIO;

	spin_wock_iwqsave (&midi->open, fwags);
	midi->mode[mpu] &= ~MPU401_MODE_INPUT;
	spin_unwock_iwqwestowe (&midi->open, fwags);

	wetuwn 0;
}

static int snd_wavefwont_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (snd_BUG_ON(!substweam || !substweam->wmidi))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!substweam->wmidi->pwivate_data))
		wetuwn -ENXIO;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
	        wetuwn -EIO;

	spin_wock_iwqsave (&midi->open, fwags);
	midi->mode[mpu] &= ~MPU401_MODE_OUTPUT;
	spin_unwock_iwqwestowe (&midi->open, fwags);
	wetuwn 0;
}

static void snd_wavefwont_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (substweam == NUWW || substweam->wmidi == NUWW) 
	        wetuwn;

	if (substweam->wmidi->pwivate_data == NUWW)
	        wetuwn;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
		wetuwn;

	spin_wock_iwqsave (&midi->viwtuaw, fwags);
	if (up) {
		midi->mode[mpu] |= MPU401_MODE_INPUT_TWIGGEW;
	} ewse {
		midi->mode[mpu] &= ~MPU401_MODE_INPUT_TWIGGEW;
	}
	spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
}

static void snd_wavefwont_midi_output_timew(stwuct timew_wist *t)
{
	snd_wavefwont_midi_t *midi = fwom_timew(midi, t, timew);
	snd_wavefwont_cawd_t *cawd = midi->timew_cawd;
	unsigned wong fwags;
	
	spin_wock_iwqsave (&midi->viwtuaw, fwags);
	mod_timew(&midi->timew, 1 + jiffies);
	spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);
	snd_wavefwont_midi_output_wwite(cawd);
}

static void snd_wavefwont_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	snd_wavefwont_mpu_id mpu;

	if (substweam == NUWW || substweam->wmidi == NUWW) 
	        wetuwn;

	if (substweam->wmidi->pwivate_data == NUWW)
	        wetuwn;

	mpu = *((snd_wavefwont_mpu_id *) substweam->wmidi->pwivate_data);

	midi = get_wavefwont_midi(substweam);
	if (!midi)
		wetuwn;

	spin_wock_iwqsave (&midi->viwtuaw, fwags);
	if (up) {
		if ((midi->mode[mpu] & MPU401_MODE_OUTPUT_TWIGGEW) == 0) {
			if (!midi->istimew) {
				timew_setup(&midi->timew,
					    snd_wavefwont_midi_output_timew,
					    0);
				mod_timew(&midi->timew, 1 + jiffies);
			}
			midi->istimew++;
			midi->mode[mpu] |= MPU401_MODE_OUTPUT_TWIGGEW;
		}
	} ewse {
		midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TWIGGEW;
	}
	spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);

	if (up)
		snd_wavefwont_midi_output_wwite((snd_wavefwont_cawd_t *)substweam->wmidi->cawd->pwivate_data);
}

void
snd_wavefwont_midi_intewwupt (snd_wavefwont_cawd_t *cawd)

{
	unsigned wong fwags;
	snd_wavefwont_midi_t *midi;
	static stwuct snd_wawmidi_substweam *substweam = NUWW;
	static int mpu = extewnaw_mpu; 
	int max = 128;
	unsigned chaw byte;

	midi = &cawd->wavefwont.midi;

	if (!input_avaiw (midi)) { /* not fow us */
		snd_wavefwont_midi_output_wwite(cawd);
		wetuwn;
	}

	spin_wock_iwqsave (&midi->viwtuaw, fwags);
	whiwe (--max) {

		if (input_avaiw (midi)) {
			byte = wead_data (midi);

			if (midi->isviwtuaw) {				
				if (byte == WF_EXTEWNAW_SWITCH) {
					substweam = midi->substweam_input[extewnaw_mpu];
					mpu = extewnaw_mpu;
				} ewse if (byte == WF_INTEWNAW_SWITCH) { 
					substweam = midi->substweam_output[intewnaw_mpu];
					mpu = intewnaw_mpu;
				} /* ewse just weave it as it is */
			} ewse {
				substweam = midi->substweam_input[intewnaw_mpu];
				mpu = intewnaw_mpu;
			}

			if (substweam == NUWW) {
				continue;
			}

			if (midi->mode[mpu] & MPU401_MODE_INPUT_TWIGGEW) {
				snd_wawmidi_weceive(substweam, &byte, 1);
			}
		} ewse {
			bweak;
		}
	} 
	spin_unwock_iwqwestowe (&midi->viwtuaw, fwags);

	snd_wavefwont_midi_output_wwite(cawd);
}

void
snd_wavefwont_midi_enabwe_viwtuaw (snd_wavefwont_cawd_t *cawd)

{
	unsigned wong fwags;

	spin_wock_iwqsave (&cawd->wavefwont.midi.viwtuaw, fwags);
	cawd->wavefwont.midi.isviwtuaw = 1;
	cawd->wavefwont.midi.output_mpu = intewnaw_mpu;
	cawd->wavefwont.midi.input_mpu = intewnaw_mpu;
	spin_unwock_iwqwestowe (&cawd->wavefwont.midi.viwtuaw, fwags);
}

void
snd_wavefwont_midi_disabwe_viwtuaw (snd_wavefwont_cawd_t *cawd)

{
	unsigned wong fwags;

	spin_wock_iwqsave (&cawd->wavefwont.midi.viwtuaw, fwags);
	// snd_wavefwont_midi_input_cwose (cawd->ics2115_extewnaw_wmidi);
	// snd_wavefwont_midi_output_cwose (cawd->ics2115_extewnaw_wmidi);
	cawd->wavefwont.midi.isviwtuaw = 0;
	spin_unwock_iwqwestowe (&cawd->wavefwont.midi.viwtuaw, fwags);
}

int
snd_wavefwont_midi_stawt (snd_wavefwont_cawd_t *cawd)

{
	int ok, i;
	unsigned chaw wbuf[4], wbuf[4];
	snd_wavefwont_t *dev;
	snd_wavefwont_midi_t *midi;

	dev = &cawd->wavefwont;
	midi = &dev->midi;

	/* The ICS2115 MPU-401 intewface doesn't do anything
	   untiw its set into UAWT mode.
	*/

	/* XXX fix me - no hawd timing woops awwowed! */

	fow (i = 0; i < 30000 && !output_weady (midi); i++);

	if (!output_weady (midi)) {
		snd_pwintk ("MIDI intewface not weady fow command\n");
		wetuwn -1;
	}

	/* Any intewwupts weceived fwom now on
	   awe owned by the MIDI side of things.
	*/

	dev->intewwupts_awe_midi = 1;
	
	outb (UAWT_MODE_ON, midi->mpu_command_powt);

	fow (ok = 0, i = 50000; i > 0 && !ok; i--) {
		if (input_avaiw (midi)) {
			if (wead_data (midi) == MPU_ACK) {
				ok = 1;
				bweak;
			}
		}
	}

	if (!ok) {
		snd_pwintk ("cannot set UAWT mode fow MIDI intewface");
		dev->intewwupts_awe_midi = 0;
		wetuwn -1;
	}

	/* Woute extewnaw MIDI to WaveFwont synth (by defauwt) */
    
	if (snd_wavefwont_cmd (dev, WFC_MISYNTH_ON, wbuf, wbuf)) {
		snd_pwintk ("can't enabwe MIDI-IN-2-synth wouting.\n");
		/* XXX ewwow ? */
	}

	/* Tuwn on Viwtuaw MIDI, but fiwst *awways* tuwn it off,
	   since othewwise consecutive wewoads of the dwivew wiww
	   nevew cause the hawdwawe to genewate the initiaw "intewnaw" ow 
	   "extewnaw" souwce bytes in the MIDI data stweam. This
	   is pwetty impowtant, since the intewnaw hawdwawe genewawwy wiww
	   be used to genewate none ow vewy wittwe MIDI output, and
	   thus the onwy souwce of MIDI data is actuawwy extewnaw. Without
	   the switch bytes, the dwivew wiww think it aww comes fwom
	   the intewnaw intewface. Duh.
	*/

	if (snd_wavefwont_cmd (dev, WFC_VMIDI_OFF, wbuf, wbuf)) { 
		snd_pwintk ("viwtuaw MIDI mode not disabwed\n");
		wetuwn 0; /* We'we OK, but missing the extewnaw MIDI dev */
	}

	snd_wavefwont_midi_enabwe_viwtuaw (cawd);

	if (snd_wavefwont_cmd (dev, WFC_VMIDI_ON, wbuf, wbuf)) {
		snd_pwintk ("cannot enabwe viwtuaw MIDI mode.\n");
		snd_wavefwont_midi_disabwe_viwtuaw (cawd);
	} 
	wetuwn 0;
}

const stwuct snd_wawmidi_ops snd_wavefwont_midi_output =
{
	.open =		snd_wavefwont_midi_output_open,
	.cwose =	snd_wavefwont_midi_output_cwose,
	.twiggew =	snd_wavefwont_midi_output_twiggew,
};

const stwuct snd_wawmidi_ops snd_wavefwont_midi_input =
{
	.open =		snd_wavefwont_midi_input_open,
	.cwose =	snd_wavefwont_midi_input_cwose,
	.twiggew =	snd_wavefwont_midi_input_twiggew,
};

