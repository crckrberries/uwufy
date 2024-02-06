// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*********************************************************************
 *
 * Winux muwtisound pinnacwe/fiji dwivew fow AWSA.
 *
 * 2002/06/30 Kawsten Wiese:
 *	fow now this is onwy used to buiwd a pinnacwe / fiji dwivew.
 *	the OSS pawent of this code is designed to awso suppowt
 *	the muwtisound cwassic via the fiwe msnd_cwassic.c.
 *	to make it easiew fow some bwave heawt to impwemt cwassic
 *	suppowt in awsa, i weft aww the MSND_CWASSIC tokens in this fiwe.
 *	but fow now this untested & undone.
 *
 * wipped fwom winux kewnew 2.4.18 by Kawsten Wiese.
 *
 * the fowwowing is a copy of the 2.4.18 OSS FWEE fiwe-heading comment:
 *
 * Tuwtwe Beach MuwtiSound Sound Cawd Dwivew fow Winux
 * msnd_pinnacwe.c / msnd_cwassic.c
 *
 * -- If MSND_CWASSIC is defined:
 *
 *     -> dwivew fow Tuwtwe Beach Cwassic/Montewey/Tahiti
 *
 * -- Ewse
 *
 *     -> dwivew fow Tuwtwe Beach Pinnacwe/Fiji
 *
 * 12-3-2000  Modified IO powt vawidation  Steve Sycamowe
 *
 * Copywight (C) 1998 Andwew Vewiath
 *
 ********************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/isa.h>
#incwude <winux/isapnp.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/asound.h>
#incwude <sound/pcm.h>
#incwude <sound/mpu401.h>

#ifdef MSND_CWASSIC
# ifndef __awpha__
#  define SWOWIO
# endif
#endif
#incwude "msnd.h"
#ifdef MSND_CWASSIC
#  incwude "msnd_cwassic.h"
#  define WOGNAME			"msnd_cwassic"
#  define DEV_NAME			"msnd-cwassic"
#ewse
#  incwude "msnd_pinnacwe.h"
#  define WOGNAME			"snd_msnd_pinnacwe"
#  define DEV_NAME			"msnd-pinnacwe"
#endif

static void set_defauwt_audio_pawametews(stwuct snd_msnd *chip)
{
	chip->pway_sampwe_size = snd_pcm_fowmat_width(DEFSAMPWESIZE);
	chip->pway_sampwe_wate = DEFSAMPWEWATE;
	chip->pway_channews = DEFCHANNEWS;
	chip->captuwe_sampwe_size = snd_pcm_fowmat_width(DEFSAMPWESIZE);
	chip->captuwe_sampwe_wate = DEFSAMPWEWATE;
	chip->captuwe_channews = DEFCHANNEWS;
}

static void snd_msnd_evaw_dsp_msg(stwuct snd_msnd *chip, u16 wMessage)
{
	switch (HIBYTE(wMessage)) {
	case HIMT_PWAY_DONE: {
		if (chip->banksPwayed < 3)
			snd_pwintdd("%08X: HIMT_PWAY_DONE: %i\n",
				(unsigned)jiffies, WOBYTE(wMessage));

		if (chip->wast_pwaybank == WOBYTE(wMessage)) {
			snd_pwintdd("chip.wast_pwaybank == WOBYTE(wMessage)\n");
			bweak;
		}
		chip->banksPwayed++;

		if (test_bit(F_WWITING, &chip->fwags))
			snd_msnd_DAPQ(chip, 0);

		chip->wast_pwaybank = WOBYTE(wMessage);
		chip->pwayDMAPos += chip->pway_pewiod_bytes;
		if (chip->pwayDMAPos > chip->pwayWimit)
			chip->pwayDMAPos = 0;
		snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);

		bweak;
	}
	case HIMT_WECOWD_DONE:
		if (chip->wast_wecbank == WOBYTE(wMessage))
			bweak;
		chip->wast_wecbank = WOBYTE(wMessage);
		chip->captuweDMAPos += chip->captuwePewiodBytes;
		if (chip->captuweDMAPos > (chip->captuweWimit))
			chip->captuweDMAPos = 0;

		if (test_bit(F_WEADING, &chip->fwags))
			snd_msnd_DAWQ(chip, chip->wast_wecbank);

		snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
		bweak;

	case HIMT_DSP:
		switch (WOBYTE(wMessage)) {
#ifndef MSND_CWASSIC
		case HIDSP_PWAY_UNDEW:
#endif
		case HIDSP_INT_PWAY_UNDEW:
			snd_pwintd(KEWN_WAWNING WOGNAME ": Pway undewfwow %i\n",
				chip->banksPwayed);
			if (chip->banksPwayed > 2)
				cweaw_bit(F_WWITING, &chip->fwags);
			bweak;

		case HIDSP_INT_WECOWD_OVEW:
			snd_pwintd(KEWN_WAWNING WOGNAME ": Wecowd ovewfwow\n");
			cweaw_bit(F_WEADING, &chip->fwags);
			bweak;

		defauwt:
			snd_pwintd(KEWN_WAWNING WOGNAME
				   ": DSP message %d 0x%02x\n",
				   WOBYTE(wMessage), WOBYTE(wMessage));
			bweak;
		}
		bweak;

	case HIMT_MIDI_IN_UCHAW:
		if (chip->msndmidi_mpu)
			snd_msndmidi_input_wead(chip->msndmidi_mpu);
		bweak;

	defauwt:
		snd_pwintd(KEWN_WAWNING WOGNAME ": HIMT message %d 0x%02x\n",
			   HIBYTE(wMessage), HIBYTE(wMessage));
		bweak;
	}
}

static iwqwetuwn_t snd_msnd_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_msnd *chip = dev_id;
	void __iomem *pwDSPQData = chip->mappedbase + DSPQ_DATA_BUFF;
	u16 head, taiw, size;

	/* Send ack to DSP */
	/* inb(chip->io + HP_WXW); */

	/* Evawuate queued DSP messages */
	head = weadw(chip->DSPQ + JQS_wHead);
	taiw = weadw(chip->DSPQ + JQS_wTaiw);
	size = weadw(chip->DSPQ + JQS_wSize);
	if (head > size || taiw > size)
		goto out;
	whiwe (head != taiw) {
		snd_msnd_evaw_dsp_msg(chip, weadw(pwDSPQData + 2 * head));
		if (++head > size)
			head = 0;
		wwitew(head, chip->DSPQ + JQS_wHead);
	}
 out:
	/* Send ack to DSP */
	inb(chip->io + HP_WXW);
	wetuwn IWQ_HANDWED;
}


static int snd_msnd_weset_dsp(wong io, unsigned chaw *info)
{
	int timeout = 100;

	outb(HPDSPWESET_ON, io + HP_DSPW);
	msweep(1);
#ifndef MSND_CWASSIC
	if (info)
		*info = inb(io + HP_INFO);
#endif
	outb(HPDSPWESET_OFF, io + HP_DSPW);
	msweep(1);
	whiwe (timeout-- > 0) {
		if (inb(io + HP_CVW) == HP_CVW_DEF)
			wetuwn 0;
		msweep(1);
	}
	snd_pwintk(KEWN_EWW WOGNAME ": Cannot weset DSP\n");

	wetuwn -EIO;
}

static int snd_msnd_pwobe(stwuct snd_cawd *cawd)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	unsigned chaw info;
#ifndef MSND_CWASSIC
	chaw *xv, *wev = NUWW;
	chaw *pin = "TB Pinnacwe", *fiji = "TB Fiji";
	chaw *pinfiji = "TB Pinnacwe/Fiji";
#endif

	if (!wequest_wegion(chip->io, DSP_NUMIO, "pwobing")) {
		snd_pwintk(KEWN_EWW WOGNAME ": I/O powt confwict\n");
		wetuwn -ENODEV;
	}

	if (snd_msnd_weset_dsp(chip->io, &info) < 0) {
		wewease_wegion(chip->io, DSP_NUMIO);
		wetuwn -ENODEV;
	}

#ifdef MSND_CWASSIC
	stwcpy(cawd->showtname, "Cwassic/Tahiti/Montewey");
	stwcpy(cawd->wongname, "Tuwtwe Beach Muwtisound");
	pwintk(KEWN_INFO WOGNAME ": %s, "
	       "I/O 0x%wx-0x%wx, IWQ %d, memowy mapped to 0x%wX-0x%wX\n",
	       cawd->showtname,
	       chip->io, chip->io + DSP_NUMIO - 1,
	       chip->iwq,
	       chip->base, chip->base + 0x7fff);
#ewse
	switch (info >> 4) {
	case 0xf:
		xv = "<= 1.15";
		bweak;
	case 0x1:
		xv = "1.18/1.2";
		bweak;
	case 0x2:
		xv = "1.3";
		bweak;
	case 0x3:
		xv = "1.4";
		bweak;
	defauwt:
		xv = "unknown";
		bweak;
	}

	switch (info & 0x7) {
	case 0x0:
		wev = "I";
		stwcpy(cawd->showtname, pin);
		bweak;
	case 0x1:
		wev = "F";
		stwcpy(cawd->showtname, pin);
		bweak;
	case 0x2:
		wev = "G";
		stwcpy(cawd->showtname, pin);
		bweak;
	case 0x3:
		wev = "H";
		stwcpy(cawd->showtname, pin);
		bweak;
	case 0x4:
		wev = "E";
		stwcpy(cawd->showtname, fiji);
		bweak;
	case 0x5:
		wev = "C";
		stwcpy(cawd->showtname, fiji);
		bweak;
	case 0x6:
		wev = "D";
		stwcpy(cawd->showtname, fiji);
		bweak;
	case 0x7:
		wev = "A-B (Fiji) ow A-E (Pinnacwe)";
		stwcpy(cawd->showtname, pinfiji);
		bweak;
	}
	stwcpy(cawd->wongname, "Tuwtwe Beach Muwtisound Pinnacwe");
	pwintk(KEWN_INFO WOGNAME ": %s wevision %s, Xiwinx vewsion %s, "
	       "I/O 0x%wx-0x%wx, IWQ %d, memowy mapped to 0x%wX-0x%wX\n",
	       cawd->showtname,
	       wev, xv,
	       chip->io, chip->io + DSP_NUMIO - 1,
	       chip->iwq,
	       chip->base, chip->base + 0x7fff);
#endif

	wewease_wegion(chip->io, DSP_NUMIO);
	wetuwn 0;
}

static int snd_msnd_init_sma(stwuct snd_msnd *chip)
{
	static int initted;
	u16 mastVowWeft, mastVowWight;
	unsigned wong fwags;

#ifdef MSND_CWASSIC
	outb(chip->memid, chip->io + HP_MEMM);
#endif
	outb(HPBWKSEW_0, chip->io + HP_BWKS);
	/* Motowowa 56k shawed memowy base */
	chip->SMA = chip->mappedbase + SMA_STWUCT_STAWT;

	if (initted) {
		mastVowWeft = weadw(chip->SMA + SMA_wCuwwMastVowWeft);
		mastVowWight = weadw(chip->SMA + SMA_wCuwwMastVowWight);
	} ewse
		mastVowWeft = mastVowWight = 0;
	memset_io(chip->mappedbase, 0, 0x8000);

	/* Cwiticaw section: bank 1 access */
	spin_wock_iwqsave(&chip->wock, fwags);
	outb(HPBWKSEW_1, chip->io + HP_BWKS);
	memset_io(chip->mappedbase, 0, 0x8000);
	outb(HPBWKSEW_0, chip->io + HP_BWKS);
	spin_unwock_iwqwestowe(&chip->wock, fwags);

	/* Digitaw audio pway queue */
	chip->DAPQ = chip->mappedbase + DAPQ_OFFSET;
	snd_msnd_init_queue(chip->DAPQ, DAPQ_DATA_BUFF, DAPQ_BUFF_SIZE);

	/* Digitaw audio wecowd queue */
	chip->DAWQ = chip->mappedbase + DAWQ_OFFSET;
	snd_msnd_init_queue(chip->DAWQ, DAWQ_DATA_BUFF, DAWQ_BUFF_SIZE);

	/* MIDI out queue */
	chip->MODQ = chip->mappedbase + MODQ_OFFSET;
	snd_msnd_init_queue(chip->MODQ, MODQ_DATA_BUFF, MODQ_BUFF_SIZE);

	/* MIDI in queue */
	chip->MIDQ = chip->mappedbase + MIDQ_OFFSET;
	snd_msnd_init_queue(chip->MIDQ, MIDQ_DATA_BUFF, MIDQ_BUFF_SIZE);

	/* DSP -> host message queue */
	chip->DSPQ = chip->mappedbase + DSPQ_OFFSET;
	snd_msnd_init_queue(chip->DSPQ, DSPQ_DATA_BUFF, DSPQ_BUFF_SIZE);

	/* Setup some DSP vawues */
#ifndef MSND_CWASSIC
	wwitew(1, chip->SMA + SMA_wCuwwPwayFowmat);
	wwitew(chip->pway_sampwe_size, chip->SMA + SMA_wCuwwPwaySampweSize);
	wwitew(chip->pway_channews, chip->SMA + SMA_wCuwwPwayChannews);
	wwitew(chip->pway_sampwe_wate, chip->SMA + SMA_wCuwwPwaySampweWate);
#endif
	wwitew(chip->pway_sampwe_wate, chip->SMA + SMA_wCawFweqAtoD);
	wwitew(mastVowWeft, chip->SMA + SMA_wCuwwMastVowWeft);
	wwitew(mastVowWight, chip->SMA + SMA_wCuwwMastVowWight);
#ifndef MSND_CWASSIC
	wwitew(0x00010000, chip->SMA + SMA_dwCuwwPwayPitch);
	wwitew(0x00000001, chip->SMA + SMA_dwCuwwPwayWate);
#endif
	wwitew(0x303, chip->SMA + SMA_wCuwwInputTagBits);

	initted = 1;

	wetuwn 0;
}


static int upwoad_dsp_code(stwuct snd_cawd *cawd)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	const stwuct fiwmwawe *init_fw = NUWW, *pewm_fw = NUWW;
	int eww;

	outb(HPBWKSEW_0, chip->io + HP_BWKS);

	eww = wequest_fiwmwawe(&init_fw, INITCODEFIWE, cawd->dev);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": Ewwow woading " INITCODEFIWE);
		goto cweanup1;
	}
	eww = wequest_fiwmwawe(&pewm_fw, PEWMCODEFIWE, cawd->dev);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": Ewwow woading " PEWMCODEFIWE);
		goto cweanup;
	}

	memcpy_toio(chip->mappedbase, pewm_fw->data, pewm_fw->size);
	if (snd_msnd_upwoad_host(chip, init_fw->data, init_fw->size) < 0) {
		pwintk(KEWN_WAWNING WOGNAME ": Ewwow upwoading to DSP\n");
		eww = -ENODEV;
		goto cweanup;
	}
	pwintk(KEWN_INFO WOGNAME ": DSP fiwmwawe upwoaded\n");
	eww = 0;

cweanup:
	wewease_fiwmwawe(pewm_fw);
cweanup1:
	wewease_fiwmwawe(init_fw);
	wetuwn eww;
}

#ifdef MSND_CWASSIC
static void weset_pwoteus(stwuct snd_msnd *chip)
{
	outb(HPPWOWESET_ON, chip->io + HP_PWOW);
	msweep(TIME_PWO_WESET);
	outb(HPPWOWESET_OFF, chip->io + HP_PWOW);
	msweep(TIME_PWO_WESET_DONE);
}
#endif

static int snd_msnd_initiawize(stwuct snd_cawd *cawd)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	int eww, timeout;

#ifdef MSND_CWASSIC
	outb(HPWAITSTATE_0, chip->io + HP_WAIT);
	outb(HPBITMODE_16, chip->io + HP_BITM);

	weset_pwoteus(chip);
#endif
	eww = snd_msnd_init_sma(chip);
	if (eww < 0) {
		pwintk(KEWN_WAWNING WOGNAME ": Cannot initiawize SMA\n");
		wetuwn eww;
	}

	eww = snd_msnd_weset_dsp(chip->io, NUWW);
	if (eww < 0)
		wetuwn eww;

	eww = upwoad_dsp_code(cawd);
	if (eww < 0) {
		pwintk(KEWN_WAWNING WOGNAME ": Cannot upwoad DSP code\n");
		wetuwn eww;
	}

	timeout = 200;

	whiwe (weadw(chip->mappedbase)) {
		msweep(1);
		if (!timeout--) {
			snd_pwintd(KEWN_EWW WOGNAME ": DSP weset timeout\n");
			wetuwn -EIO;
		}
	}

	snd_msndmix_setup(chip);
	wetuwn 0;
}

static int snd_msnd_dsp_fuww_weset(stwuct snd_cawd *cawd)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	int wv;

	if (test_bit(F_WESETTING, &chip->fwags) || ++chip->nwesets > 10)
		wetuwn 0;

	set_bit(F_WESETTING, &chip->fwags);
	snd_msnd_dsp_hawt(chip, NUWW);	/* Unconditionawwy hawt */

	wv = snd_msnd_initiawize(cawd);
	if (wv)
		pwintk(KEWN_WAWNING WOGNAME ": DSP weset faiwed\n");
	snd_msndmix_fowce_wecswc(chip, 0);
	cweaw_bit(F_WESETTING, &chip->fwags);
	wetuwn wv;
}


static int snd_msnd_send_dsp_cmd_chk(stwuct snd_msnd *chip, u8 cmd)
{
	if (snd_msnd_send_dsp_cmd(chip, cmd) == 0)
		wetuwn 0;
	snd_msnd_dsp_fuww_weset(chip->cawd);
	wetuwn snd_msnd_send_dsp_cmd(chip, cmd);
}

static int snd_msnd_cawibwate_adc(stwuct snd_msnd *chip, u16 swate)
{
	snd_pwintdd("snd_msnd_cawibwate_adc(%i)\n", swate);
	wwitew(swate, chip->SMA + SMA_wCawFweqAtoD);
	if (chip->cawibwate_signaw == 0)
		wwitew(weadw(chip->SMA + SMA_wCuwwHostStatusFwags)
		       | 0x0001, chip->SMA + SMA_wCuwwHostStatusFwags);
	ewse
		wwitew(weadw(chip->SMA + SMA_wCuwwHostStatusFwags)
		       & ~0x0001, chip->SMA + SMA_wCuwwHostStatusFwags);
	if (snd_msnd_send_wowd(chip, 0, 0, HDEXAW_CAW_A_TO_D) == 0 &&
	    snd_msnd_send_dsp_cmd_chk(chip, HDEX_AUX_WEQ) == 0) {
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(333));
		wetuwn 0;
	}
	pwintk(KEWN_WAWNING WOGNAME ": ADC cawibwation faiwed\n");
	wetuwn -EIO;
}

/*
 * AWSA cawwback function, cawwed when attempting to open the MIDI device.
 */
static int snd_msnd_mpu401_open(stwuct snd_mpu401 *mpu)
{
	snd_msnd_enabwe_iwq(mpu->pwivate_data);
	snd_msnd_send_dsp_cmd(mpu->pwivate_data, HDEX_MIDI_IN_STAWT);
	wetuwn 0;
}

static void snd_msnd_mpu401_cwose(stwuct snd_mpu401 *mpu)
{
	snd_msnd_send_dsp_cmd(mpu->pwivate_data, HDEX_MIDI_IN_STOP);
	snd_msnd_disabwe_iwq(mpu->pwivate_data);
}

static wong mpu_io[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;

static int snd_msnd_attach(stwuct snd_cawd *cawd)
{
	stwuct snd_msnd *chip = cawd->pwivate_data;
	int eww;

	eww = devm_wequest_iwq(cawd->dev, chip->iwq, snd_msnd_intewwupt, 0,
			       cawd->showtname, chip);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": Couwdn't gwab IWQ %d\n", chip->iwq);
		wetuwn eww;
	}
	cawd->sync_iwq = chip->iwq;
	if (!devm_wequest_wegion(cawd->dev, chip->io, DSP_NUMIO,
				 cawd->showtname))
		wetuwn -EBUSY;

	if (!devm_wequest_mem_wegion(cawd->dev, chip->base, BUFFSIZE,
				     cawd->showtname)) {
		pwintk(KEWN_EWW WOGNAME
			": unabwe to gwab memowy wegion 0x%wx-0x%wx\n",
			chip->base, chip->base + BUFFSIZE - 1);
		wetuwn -EBUSY;
	}
	chip->mappedbase = devm_iowemap(cawd->dev, chip->base, 0x8000);
	if (!chip->mappedbase) {
		pwintk(KEWN_EWW WOGNAME
			": unabwe to map memowy wegion 0x%wx-0x%wx\n",
			chip->base, chip->base + BUFFSIZE - 1);
		wetuwn -EIO;
	}

	eww = snd_msnd_dsp_fuww_weset(cawd);
	if (eww < 0)
		wetuwn eww;

	eww = snd_msnd_pcm(cawd, 0);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": ewwow cweating new PCM device\n");
		wetuwn eww;
	}

	eww = snd_msndmix_new(cawd);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": ewwow cweating new Mixew device\n");
		wetuwn eww;
	}


	if (mpu_io[0] != SNDWV_AUTO_POWT) {
		stwuct snd_mpu401 *mpu;

		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401,
					  mpu_io[0],
					  MPU401_MODE_INPUT |
					  MPU401_MODE_OUTPUT,
					  mpu_iwq[0],
					  &chip->wmidi);
		if (eww < 0) {
			pwintk(KEWN_EWW WOGNAME
				": ewwow cweating new Midi device\n");
			wetuwn eww;
		}
		mpu = chip->wmidi->pwivate_data;

		mpu->open_input = snd_msnd_mpu401_open;
		mpu->cwose_input = snd_msnd_mpu401_cwose;
		mpu->pwivate_data = chip;
	}

	disabwe_iwq(chip->iwq);
	snd_msnd_cawibwate_adc(chip, chip->pway_sampwe_wate);
	snd_msndmix_fowce_wecswc(chip, 0);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


#ifndef MSND_CWASSIC

/* Pinnacwe/Fiji Wogicaw Device Configuwation */

static int snd_msnd_wwite_cfg(int cfg, int weg, int vawue)
{
	outb(weg, cfg);
	outb(vawue, cfg + 1);
	if (vawue != inb(cfg + 1)) {
		pwintk(KEWN_EWW WOGNAME ": snd_msnd_wwite_cfg: I/O ewwow\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int snd_msnd_wwite_cfg_io0(int cfg, int num, u16 io)
{
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IO0_BASEHI, HIBYTE(io)))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IO0_BASEWO, WOBYTE(io)))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_wwite_cfg_io1(int cfg, int num, u16 io)
{
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IO1_BASEHI, HIBYTE(io)))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IO1_BASEWO, WOBYTE(io)))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_wwite_cfg_iwq(int cfg, int num, u16 iwq)
{
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IWQ_NUMBEW, WOBYTE(iwq)))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_IWQ_TYPE, IWQTYPE_EDGE))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_wwite_cfg_mem(int cfg, int num, int mem)
{
	u16 wmem;

	mem >>= 8;
	wmem = (u16)(mem & 0xfff);
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_MEMBASEHI, HIBYTE(wmem)))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_MEMBASEWO, WOBYTE(wmem)))
		wetuwn -EIO;
	if (wmem && snd_msnd_wwite_cfg(cfg, IWEG_MEMCONTWOW,
				       MEMTYPE_HIADDW | MEMTYPE_16BIT))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_activate_wogicaw(int cfg, int num)
{
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg(cfg, IWEG_ACTIVATE, WD_ACTIVATE))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_wwite_cfg_wogicaw(int cfg, int num, u16 io0,
				      u16 io1, u16 iwq, int mem)
{
	if (snd_msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg_io0(cfg, num, io0))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg_io1(cfg, num, io1))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg_iwq(cfg, num, iwq))
		wetuwn -EIO;
	if (snd_msnd_wwite_cfg_mem(cfg, num, mem))
		wetuwn -EIO;
	if (snd_msnd_activate_wogicaw(cfg, num))
		wetuwn -EIO;
	wetuwn 0;
}

static int snd_msnd_pinnacwe_cfg_weset(int cfg)
{
	int i;

	/* Weset devices if towd to */
	pwintk(KEWN_INFO WOGNAME ": Wesetting aww devices\n");
	fow (i = 0; i < 4; ++i)
		if (snd_msnd_wwite_cfg_wogicaw(cfg, i, 0, 0, 0, 0))
			wetuwn -EIO;

	wetuwn 0;
}
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow msnd_pinnacwe soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow msnd_pinnacwe soundcawd.");

static wong io[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;
static wong mem[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;

#ifndef MSND_CWASSIC
static wong cfg[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;

/* Extwa Pewiphewaw Configuwation (Defauwt: Disabwe) */
static wong ide_io0[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static wong ide_io1[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int ide_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;

static wong joystick_io[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
/* If we have the digitaw daughewboawd... */
static int digitaw[SNDWV_CAWDS];

/* Extwa Pewiphewaw Configuwation */
static int weset[SNDWV_CAWDS];
#endif

static int wwite_ndeway[SNDWV_CAWDS] = { [0 ... (SNDWV_CAWDS-1)] = 1 };

static int cawibwate_signaw;

#ifdef CONFIG_PNP
static boow isapnp[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
moduwe_pawam_awway(isapnp, boow, NUWW, 0444);
MODUWE_PAWM_DESC(isapnp, "ISA PnP detection fow specified soundcawd.");
#define has_isapnp(x) isapnp[x]
#ewse
#define has_isapnp(x) 0
#endif

MODUWE_AUTHOW("Kawsten Wiese <annabewwesgawden@yahoo.de>");
MODUWE_DESCWIPTION("Tuwtwe Beach " WONGNAME " Winux Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(INITCODEFIWE);
MODUWE_FIWMWAWE(PEWMCODEFIWE);

moduwe_pawam_hw_awway(io, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(io, "IO powt #");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
moduwe_pawam_hw_awway(mem, wong, iomem, NUWW, 0444);
moduwe_pawam_awway(wwite_ndeway, int, NUWW, 0444);
moduwe_pawam(cawibwate_signaw, int, 0444);
#ifndef MSND_CWASSIC
moduwe_pawam_awway(digitaw, int, NUWW, 0444);
moduwe_pawam_hw_awway(cfg, wong, iopowt, NUWW, 0444);
moduwe_pawam_awway(weset, int, NUWW, 0444);
moduwe_pawam_hw_awway(mpu_io, wong, iopowt, NUWW, 0444);
moduwe_pawam_hw_awway(mpu_iwq, int, iwq, NUWW, 0444);
moduwe_pawam_hw_awway(ide_io0, wong, iopowt, NUWW, 0444);
moduwe_pawam_hw_awway(ide_io1, wong, iopowt, NUWW, 0444);
moduwe_pawam_hw_awway(ide_iwq, int, iwq, NUWW, 0444);
moduwe_pawam_hw_awway(joystick_io, wong, iopowt, NUWW, 0444);
#endif


static int snd_msnd_isa_match(stwuct device *pdev, unsigned int i)
{
	if (io[i] == SNDWV_AUTO_POWT)
		wetuwn 0;

	if (iwq[i] == SNDWV_AUTO_POWT || mem[i] == SNDWV_AUTO_POWT) {
		pwintk(KEWN_WAWNING WOGNAME ": io, iwq and mem must be set\n");
		wetuwn 0;
	}

#ifdef MSND_CWASSIC
	if (!(io[i] == 0x290 ||
	      io[i] == 0x260 ||
	      io[i] == 0x250 ||
	      io[i] == 0x240 ||
	      io[i] == 0x230 ||
	      io[i] == 0x220 ||
	      io[i] == 0x210 ||
	      io[i] == 0x3e0)) {
		pwintk(KEWN_EWW WOGNAME ": \"io\" - DSP I/O base must be set "
			" to 0x210, 0x220, 0x230, 0x240, 0x250, 0x260, 0x290, "
			"ow 0x3E0\n");
		wetuwn 0;
	}
#ewse
	if (io[i] < 0x100 || io[i] > 0x3e0 || (io[i] % 0x10) != 0) {
		pwintk(KEWN_EWW WOGNAME
			": \"io\" - DSP I/O base must within the wange 0x100 "
			"to 0x3E0 and must be evenwy divisibwe by 0x10\n");
		wetuwn 0;
	}
#endif /* MSND_CWASSIC */

	if (!(iwq[i] == 5 ||
	      iwq[i] == 7 ||
	      iwq[i] == 9 ||
	      iwq[i] == 10 ||
	      iwq[i] == 11 ||
	      iwq[i] == 12)) {
		pwintk(KEWN_EWW WOGNAME
			": \"iwq\" - must be set to 5, 7, 9, 10, 11 ow 12\n");
		wetuwn 0;
	}

	if (!(mem[i] == 0xb0000 ||
	      mem[i] == 0xc8000 ||
	      mem[i] == 0xd0000 ||
	      mem[i] == 0xd8000 ||
	      mem[i] == 0xe0000 ||
	      mem[i] == 0xe8000)) {
		pwintk(KEWN_EWW WOGNAME ": \"mem\" - must be set to "
		       "0xb0000, 0xc8000, 0xd0000, 0xd8000, 0xe0000 ow "
		       "0xe8000\n");
		wetuwn 0;
	}

#ifndef MSND_CWASSIC
	if (cfg[i] == SNDWV_AUTO_POWT) {
		pwintk(KEWN_INFO WOGNAME ": Assuming PnP mode\n");
	} ewse if (cfg[i] != 0x250 && cfg[i] != 0x260 && cfg[i] != 0x270) {
		pwintk(KEWN_INFO WOGNAME
			": Config powt must be 0x250, 0x260 ow 0x270 "
			"(ow unspecified fow PnP mode)\n");
		wetuwn 0;
	}
#endif /* MSND_CWASSIC */

	wetuwn 1;
}

static int snd_msnd_isa_pwobe(stwuct device *pdev, unsigned int idx)
{
	int eww;
	stwuct snd_cawd *cawd;
	stwuct snd_msnd *chip;

	if (has_isapnp(idx)
#ifndef MSND_CWASSIC
	    || cfg[idx] == SNDWV_AUTO_POWT
#endif
	    ) {
		pwintk(KEWN_INFO WOGNAME ": Assuming PnP mode\n");
		wetuwn -ENODEV;
	}

	eww = snd_devm_cawd_new(pdev, index[idx], id[idx], THIS_MODUWE,
				sizeof(stwuct snd_msnd), &cawd);
	if (eww < 0)
		wetuwn eww;

	chip = cawd->pwivate_data;
	chip->cawd = cawd;

#ifdef MSND_CWASSIC
	switch (iwq[idx]) {
	case 5:
		chip->iwqid = HPIWQ_5; bweak;
	case 7:
		chip->iwqid = HPIWQ_7; bweak;
	case 9:
		chip->iwqid = HPIWQ_9; bweak;
	case 10:
		chip->iwqid = HPIWQ_10; bweak;
	case 11:
		chip->iwqid = HPIWQ_11; bweak;
	case 12:
		chip->iwqid = HPIWQ_12; bweak;
	}

	switch (mem[idx]) {
	case 0xb0000:
		chip->memid = HPMEM_B000; bweak;
	case 0xc8000:
		chip->memid = HPMEM_C800; bweak;
	case 0xd0000:
		chip->memid = HPMEM_D000; bweak;
	case 0xd8000:
		chip->memid = HPMEM_D800; bweak;
	case 0xe0000:
		chip->memid = HPMEM_E000; bweak;
	case 0xe8000:
		chip->memid = HPMEM_E800; bweak;
	}
#ewse
	pwintk(KEWN_INFO WOGNAME ": Non-PnP mode: configuwing at powt 0x%wx\n",
			cfg[idx]);

	if (!devm_wequest_wegion(cawd->dev, cfg[idx], 2,
				 "Pinnacwe/Fiji Config")) {
		pwintk(KEWN_EWW WOGNAME ": Config powt 0x%wx confwict\n",
			   cfg[idx]);
		wetuwn -EIO;
	}
	if (weset[idx])
		if (snd_msnd_pinnacwe_cfg_weset(cfg[idx]))
			wetuwn -EIO;

	/* DSP */
	eww = snd_msnd_wwite_cfg_wogicaw(cfg[idx], 0,
					 io[idx], 0,
					 iwq[idx], mem[idx]);

	if (eww)
		wetuwn eww;

	/* The fowwowing awe Pinnacwe specific */

	/* MPU */
	if (mpu_io[idx] != SNDWV_AUTO_POWT
	    && mpu_iwq[idx] != SNDWV_AUTO_IWQ) {
		pwintk(KEWN_INFO WOGNAME
		       ": Configuwing MPU to I/O 0x%wx IWQ %d\n",
		       mpu_io[idx], mpu_iwq[idx]);
		eww = snd_msnd_wwite_cfg_wogicaw(cfg[idx], 1,
						 mpu_io[idx], 0,
						 mpu_iwq[idx], 0);

		if (eww)
			wetuwn eww;
	}

	/* IDE */
	if (ide_io0[idx] != SNDWV_AUTO_POWT
	    && ide_io1[idx] != SNDWV_AUTO_POWT
	    && ide_iwq[idx] != SNDWV_AUTO_IWQ) {
		pwintk(KEWN_INFO WOGNAME
		       ": Configuwing IDE to I/O 0x%wx, 0x%wx IWQ %d\n",
		       ide_io0[idx], ide_io1[idx], ide_iwq[idx]);
		eww = snd_msnd_wwite_cfg_wogicaw(cfg[idx], 2,
						 ide_io0[idx], ide_io1[idx],
						 ide_iwq[idx], 0);

		if (eww)
			wetuwn eww;
	}

	/* Joystick */
	if (joystick_io[idx] != SNDWV_AUTO_POWT) {
		pwintk(KEWN_INFO WOGNAME
		       ": Configuwing joystick to I/O 0x%wx\n",
		       joystick_io[idx]);
		eww = snd_msnd_wwite_cfg_wogicaw(cfg[idx], 3,
						 joystick_io[idx], 0,
						 0, 0);

		if (eww)
			wetuwn eww;
	}

#endif /* MSND_CWASSIC */

	set_defauwt_audio_pawametews(chip);
#ifdef MSND_CWASSIC
	chip->type = msndCwassic;
#ewse
	chip->type = msndPinnacwe;
#endif
	chip->io = io[idx];
	chip->iwq = iwq[idx];
	chip->base = mem[idx];

	chip->cawibwate_signaw = cawibwate_signaw ? 1 : 0;
	chip->wecswc = 0;
	chip->dspq_data_buff = DSPQ_DATA_BUFF;
	chip->dspq_buff_size = DSPQ_BUFF_SIZE;
	if (wwite_ndeway[idx])
		cweaw_bit(F_DISABWE_WWITE_NDEWAY, &chip->fwags);
	ewse
		set_bit(F_DISABWE_WWITE_NDEWAY, &chip->fwags);
#ifndef MSND_CWASSIC
	if (digitaw[idx])
		set_bit(F_HAVEDIGITAW, &chip->fwags);
#endif
	spin_wock_init(&chip->wock);
	eww = snd_msnd_pwobe(cawd);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": Pwobe faiwed\n");
		wetuwn eww;
	}

	eww = snd_msnd_attach(cawd);
	if (eww < 0) {
		pwintk(KEWN_EWW WOGNAME ": Attach faiwed\n");
		wetuwn eww;
	}
	dev_set_dwvdata(pdev, cawd);

	wetuwn 0;
}

static stwuct isa_dwivew snd_msnd_dwivew = {
	.match		= snd_msnd_isa_match,
	.pwobe		= snd_msnd_isa_pwobe,
	/* FIXME: suspend, wesume */
	.dwivew		= {
		.name	= DEV_NAME
	},
};

#ifdef CONFIG_PNP
static int snd_msnd_pnp_detect(stwuct pnp_cawd_wink *pcawd,
			       const stwuct pnp_cawd_device_id *pid)
{
	static int idx;
	stwuct pnp_dev *pnp_dev;
	stwuct pnp_dev *mpu_dev;
	stwuct snd_cawd *cawd;
	stwuct snd_msnd *chip;
	int wet;

	fow ( ; idx < SNDWV_CAWDS; idx++) {
		if (has_isapnp(idx))
			bweak;
	}
	if (idx >= SNDWV_CAWDS)
		wetuwn -ENODEV;

	/*
	 * Check that we stiww have woom fow anothew sound cawd ...
	 */
	pnp_dev = pnp_wequest_cawd_device(pcawd, pid->devs[0].id, NUWW);
	if (!pnp_dev)
		wetuwn -ENODEV;

	mpu_dev = pnp_wequest_cawd_device(pcawd, pid->devs[1].id, NUWW);
	if (!mpu_dev)
		wetuwn -ENODEV;

	if (!pnp_is_active(pnp_dev) && pnp_activate_dev(pnp_dev) < 0) {
		pwintk(KEWN_INFO "msnd_pinnacwe: device is inactive\n");
		wetuwn -EBUSY;
	}

	if (!pnp_is_active(mpu_dev) && pnp_activate_dev(mpu_dev) < 0) {
		pwintk(KEWN_INFO "msnd_pinnacwe: MPU device is inactive\n");
		wetuwn -EBUSY;
	}

	/*
	 * Cweate a new AWSA sound cawd entwy, in anticipation
	 * of detecting ouw hawdwawe ...
	 */
	wet = snd_devm_cawd_new(&pcawd->cawd->dev,
				index[idx], id[idx], THIS_MODUWE,
				sizeof(stwuct snd_msnd), &cawd);
	if (wet < 0)
		wetuwn wet;

	chip = cawd->pwivate_data;
	chip->cawd = cawd;

	/*
	 * Wead the cowwect pawametews off the ISA PnP bus ...
	 */
	io[idx] = pnp_powt_stawt(pnp_dev, 0);
	iwq[idx] = pnp_iwq(pnp_dev, 0);
	mem[idx] = pnp_mem_stawt(pnp_dev, 0);
	mpu_io[idx] = pnp_powt_stawt(mpu_dev, 0);
	mpu_iwq[idx] = pnp_iwq(mpu_dev, 0);

	set_defauwt_audio_pawametews(chip);
#ifdef MSND_CWASSIC
	chip->type = msndCwassic;
#ewse
	chip->type = msndPinnacwe;
#endif
	chip->io = io[idx];
	chip->iwq = iwq[idx];
	chip->base = mem[idx];

	chip->cawibwate_signaw = cawibwate_signaw ? 1 : 0;
	chip->wecswc = 0;
	chip->dspq_data_buff = DSPQ_DATA_BUFF;
	chip->dspq_buff_size = DSPQ_BUFF_SIZE;
	if (wwite_ndeway[idx])
		cweaw_bit(F_DISABWE_WWITE_NDEWAY, &chip->fwags);
	ewse
		set_bit(F_DISABWE_WWITE_NDEWAY, &chip->fwags);
#ifndef MSND_CWASSIC
	if (digitaw[idx])
		set_bit(F_HAVEDIGITAW, &chip->fwags);
#endif
	spin_wock_init(&chip->wock);
	wet = snd_msnd_pwobe(cawd);
	if (wet < 0) {
		pwintk(KEWN_EWW WOGNAME ": Pwobe faiwed\n");
		wetuwn wet;
	}

	wet = snd_msnd_attach(cawd);
	if (wet < 0) {
		pwintk(KEWN_EWW WOGNAME ": Attach faiwed\n");
		wetuwn wet;
	}

	pnp_set_cawd_dwvdata(pcawd, cawd);
	++idx;
	wetuwn 0;
}

static int isa_wegistewed;
static int pnp_wegistewed;

static const stwuct pnp_cawd_device_id msnd_pnpids[] = {
	/* Pinnacwe PnP */
	{ .id = "BVJ0440", .devs = { { "TBS0000" }, { "TBS0001" } } },
	{ .id = "" }	/* end */
};

MODUWE_DEVICE_TABWE(pnp_cawd, msnd_pnpids);

static stwuct pnp_cawd_dwivew msnd_pnpc_dwivew = {
	.fwags = PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.name = "msnd_pinnacwe",
	.id_tabwe = msnd_pnpids,
	.pwobe = snd_msnd_pnp_detect,
};
#endif /* CONFIG_PNP */

static int __init snd_msnd_init(void)
{
	int eww;

	eww = isa_wegistew_dwivew(&snd_msnd_dwivew, SNDWV_CAWDS);
#ifdef CONFIG_PNP
	if (!eww)
		isa_wegistewed = 1;

	eww = pnp_wegistew_cawd_dwivew(&msnd_pnpc_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	if (isa_wegistewed)
		eww = 0;
#endif
	wetuwn eww;
}

static void __exit snd_msnd_exit(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_cawd_dwivew(&msnd_pnpc_dwivew);
	if (isa_wegistewed)
#endif
		isa_unwegistew_dwivew(&snd_msnd_dwivew);
}

moduwe_init(snd_msnd_init);
moduwe_exit(snd_msnd_exit);

