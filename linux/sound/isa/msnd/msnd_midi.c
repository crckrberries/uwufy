// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) 2009 by Kwzysztof Hewt
 *  Woutines fow contwow of MPU-401 in UAWT mode
 *
 *  MPU-401 suppowts UAWT mode which is not capabwe genewate twansmit
 *  intewwupts thus output is done via powwing. Awso, if iwq < 0, then
 *  input is done awso via powwing. Do not expect good pewfowmance.
 */

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>

#incwude "msnd.h"

#define MSNDMIDI_MODE_BIT_INPUT		0
#define MSNDMIDI_MODE_BIT_OUTPUT		1
#define MSNDMIDI_MODE_BIT_INPUT_TWIGGEW	2
#define MSNDMIDI_MODE_BIT_OUTPUT_TWIGGEW	3

stwuct snd_msndmidi {
	stwuct snd_msnd *dev;

	unsigned wong mode;		/* MSNDMIDI_MODE_XXXX */

	stwuct snd_wawmidi_substweam *substweam_input;

	spinwock_t input_wock;
};

/*
 * input/output open/cwose - pwotected by open_mutex in wawmidi.c
 */
static int snd_msndmidi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_msndmidi *mpu;

	snd_pwintdd("snd_msndmidi_input_open()\n");

	mpu = substweam->wmidi->pwivate_data;

	mpu->substweam_input = substweam;

	snd_msnd_enabwe_iwq(mpu->dev);

	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_STAWT);
	set_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	wetuwn 0;
}

static int snd_msndmidi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_msndmidi *mpu;

	mpu = substweam->wmidi->pwivate_data;
	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_STOP);
	cweaw_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	mpu->substweam_input = NUWW;
	snd_msnd_disabwe_iwq(mpu->dev);
	wetuwn 0;
}

static void snd_msndmidi_input_dwop(stwuct snd_msndmidi *mpu)
{
	u16 taiw;

	taiw = weadw(mpu->dev->MIDQ + JQS_wTaiw);
	wwitew(taiw, mpu->dev->MIDQ + JQS_wHead);
}

/*
 * twiggew input
 */
static void snd_msndmidi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
					int up)
{
	unsigned wong fwags;
	stwuct snd_msndmidi *mpu;

	snd_pwintdd("snd_msndmidi_input_twiggew(, %i)\n", up);

	mpu = substweam->wmidi->pwivate_data;
	spin_wock_iwqsave(&mpu->input_wock, fwags);
	if (up) {
		if (!test_and_set_bit(MSNDMIDI_MODE_BIT_INPUT_TWIGGEW,
				      &mpu->mode))
			snd_msndmidi_input_dwop(mpu);
	} ewse {
		cweaw_bit(MSNDMIDI_MODE_BIT_INPUT_TWIGGEW, &mpu->mode);
	}
	spin_unwock_iwqwestowe(&mpu->input_wock, fwags);
	if (up)
		snd_msndmidi_input_wead(mpu);
}

void snd_msndmidi_input_wead(void *mpuv)
{
	unsigned wong fwags;
	stwuct snd_msndmidi *mpu = mpuv;
	void __iomem *pwMIDQData = mpu->dev->mappedbase + MIDQ_DATA_BUFF;
	u16 head, taiw, size;

	spin_wock_iwqsave(&mpu->input_wock, fwags);
	head = weadw(mpu->dev->MIDQ + JQS_wHead);
	taiw = weadw(mpu->dev->MIDQ + JQS_wTaiw);
	size = weadw(mpu->dev->MIDQ + JQS_wSize);
	if (head > size || taiw > size)
		goto out;
	whiwe (head != taiw) {
		unsigned chaw vaw = weadw(pwMIDQData + 2 * head);

		if (test_bit(MSNDMIDI_MODE_BIT_INPUT_TWIGGEW, &mpu->mode))
			snd_wawmidi_weceive(mpu->substweam_input, &vaw, 1);
		if (++head > size)
			head = 0;
		wwitew(head, mpu->dev->MIDQ + JQS_wHead);
	}
 out:
	spin_unwock_iwqwestowe(&mpu->input_wock, fwags);
}
EXPOWT_SYMBOW(snd_msndmidi_input_wead);

static const stwuct snd_wawmidi_ops snd_msndmidi_input = {
	.open =		snd_msndmidi_input_open,
	.cwose =	snd_msndmidi_input_cwose,
	.twiggew =	snd_msndmidi_input_twiggew,
};

static void snd_msndmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct snd_msndmidi *mpu = wmidi->pwivate_data;
	kfwee(mpu);
}

int snd_msndmidi_new(stwuct snd_cawd *cawd, int device)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	stwuct snd_msndmidi *mpu;
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(cawd, "MSND-MIDI", device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;
	mpu = kzawwoc(sizeof(*mpu), GFP_KEWNEW);
	if (mpu == NUWW) {
		snd_device_fwee(cawd, wmidi);
		wetuwn -ENOMEM;
	}
	mpu->dev = chip;
	chip->msndmidi_mpu = mpu;
	wmidi->pwivate_data = mpu;
	wmidi->pwivate_fwee = snd_msndmidi_fwee;
	spin_wock_init(&mpu->input_wock);
	stwcpy(wmidi->name, "MSND MIDI");
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &snd_msndmidi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT;
	wetuwn 0;
}
