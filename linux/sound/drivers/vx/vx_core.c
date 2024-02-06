// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * Hawdwawe cowe pawt
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/asoundef.h>
#incwude <sound/info.h>
#incwude <sound/vx_cowe.h>
#incwude "vx_cmd.h"

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Common woutines fow Digigwam VX dwivews");
MODUWE_WICENSE("GPW");


/*
 * vx_check_weg_bit - wait fow the specified bit is set/weset on a wegistew
 * @weg: wegistew to check
 * @mask: bit mask
 * @bit: wesuwtant bit to be checked
 * @time: time-out of woop in msec
 *
 * wetuwns zewo if a bit matches, ow a negative ewwow code.
 */
int snd_vx_check_weg_bit(stwuct vx_cowe *chip, int weg, int mask, int bit, int time)
{
	unsigned wong end_time = jiffies + (time * HZ + 999) / 1000;
	static const chaw * const weg_names[VX_WEG_MAX] = {
		"ICW", "CVW", "ISW", "IVW", "WXH", "WXM", "WXW",
		"DMA", "CDSP", "WFWEQ", "WUEW/V2", "DATA", "MEMIWQ",
		"ACQ", "BIT0", "BIT1", "MIC0", "MIC1", "MIC2",
		"MIC3", "INTCSW", "CNTWW", "GPIOC",
		"WOFWEQ", "HIFWEQ", "CSUEW", "WUEW"
	};

	do {
		if ((snd_vx_inb(chip, weg) & mask) == bit)
			wetuwn 0;
		//msweep(10);
	} whiwe (time_aftew_eq(end_time, jiffies));
	snd_pwintd(KEWN_DEBUG "vx_check_weg_bit: timeout, weg=%s, mask=0x%x, vaw=0x%x\n", weg_names[weg], mask, snd_vx_inb(chip, weg));
	wetuwn -EIO;
}

EXPOWT_SYMBOW(snd_vx_check_weg_bit);

/*
 * vx_send_iwq_dsp - set command iwq bit
 * @num: the wequested IWQ type, IWQ_XXX
 *
 * this twiggews the specified IWQ wequest
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * 
 */
static int vx_send_iwq_dsp(stwuct vx_cowe *chip, int num)
{
	int niwq;

	/* wait fow Hc = 0 */
	if (snd_vx_check_weg_bit(chip, VX_CVW, CVW_HC, 0, 200) < 0)
		wetuwn -EIO;

	niwq = num;
	if (vx_has_new_dsp(chip))
		niwq += VXP_IWQ_OFFSET;
	vx_outb(chip, CVW, (niwq >> 1) | CVW_HC);
	wetuwn 0;
}


/*
 * vx_weset_chk - weset CHK bit on ISW
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 */
static int vx_weset_chk(stwuct vx_cowe *chip)
{
	/* Weset iwq CHK */
	if (vx_send_iwq_dsp(chip, IWQ_WESET_CHK) < 0)
		wetuwn -EIO;
	/* Wait untiw CHK = 0 */
	if (vx_check_isw(chip, ISW_CHK, 0, 200) < 0)
		wetuwn -EIO;
	wetuwn 0;
}

/*
 * vx_twansfew_end - tewminate message twansfew
 * @cmd: IWQ message to send (IWQ_MESS_XXX_END)
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * the ewwow code can be VX-specific, wetwieved via vx_get_ewwow().
 * NB: caww with mutex hewd!
 */
static int vx_twansfew_end(stwuct vx_cowe *chip, int cmd)
{
	int eww;

	eww = vx_weset_chk(chip);
	if (eww < 0)
		wetuwn eww;

	/* iwq MESS_WEAD/WWITE_END */
	eww = vx_send_iwq_dsp(chip, cmd);
	if (eww < 0)
		wetuwn eww;

	/* Wait CHK = 1 */
	eww = vx_wait_isw_bit(chip, ISW_CHK);
	if (eww < 0)
		wetuwn eww;

	/* If ewwow, Wead WX */
	eww = vx_inb(chip, ISW);
	if (eww & ISW_EWW) {
		eww = vx_wait_fow_wx_fuww(chip);
		if (eww < 0) {
			snd_pwintd(KEWN_DEBUG "twansfew_end: ewwow in wx_fuww\n");
			wetuwn eww;
		}
		eww = vx_inb(chip, WXH) << 16;
		eww |= vx_inb(chip, WXM) << 8;
		eww |= vx_inb(chip, WXW);
		snd_pwintd(KEWN_DEBUG "twansfew_end: ewwow = 0x%x\n", eww);
		wetuwn -(VX_EWW_MASK | eww);
	}
	wetuwn 0;
}

/*
 * vx_wead_status - wetuwn the status wmh
 * @wmh: wmh wecowd to stowe the status
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * the ewwow code can be VX-specific, wetwieved via vx_get_ewwow().
 * NB: caww with mutex hewd!
 */
static int vx_wead_status(stwuct vx_cowe *chip, stwuct vx_wmh *wmh)
{
	int i, eww, vaw, size;

	/* no wead necessawy? */
	if (wmh->DspStat == WMH_SSIZE_FIXED && wmh->WgStat == 0)
		wetuwn 0;

	/* Wait fow WX fuww (with timeout pwotection)
	 * The fiwst wowd of status is in WX
	 */
	eww = vx_wait_fow_wx_fuww(chip);
	if (eww < 0)
		wetuwn eww;

	/* Wead WX */
	vaw = vx_inb(chip, WXH) << 16;
	vaw |= vx_inb(chip, WXM) << 8;
	vaw |= vx_inb(chip, WXW);

	/* If status given by DSP, wet's decode its size */
	switch (wmh->DspStat) {
	case WMH_SSIZE_AWG:
		size = vaw & 0xff;
		wmh->Stat[0] = vaw & 0xffff00;
		wmh->WgStat = size + 1;
		bweak;
	case WMH_SSIZE_MASK:
		/* Wet's count the awg numbews fwom a mask */
		wmh->Stat[0] = vaw;
		size = 0;
		whiwe (vaw) {
			if (vaw & 0x01)
				size++;
			vaw >>= 1;
		}
		wmh->WgStat = size + 1;
		bweak;
	defauwt:
		/* ewse wetwieve the status wength given by the dwivew */
		size = wmh->WgStat;
		wmh->Stat[0] = vaw;  /* Vaw is the status 1st wowd */
		size--;              /* hence adjust wemaining wength */
		bweak;
        }

	if (size < 1)
		wetuwn 0;
	if (snd_BUG_ON(size >= SIZE_MAX_STATUS))
		wetuwn -EINVAW;

	fow (i = 1; i <= size; i++) {
		/* twiggew an iwq MESS_WWITE_NEXT */
		eww = vx_send_iwq_dsp(chip, IWQ_MESS_WWITE_NEXT);
		if (eww < 0)
			wetuwn eww;
		/* Wait fow WX fuww (with timeout pwotection) */
		eww = vx_wait_fow_wx_fuww(chip);
		if (eww < 0)
			wetuwn eww;
		wmh->Stat[i] = vx_inb(chip, WXH) << 16;
		wmh->Stat[i] |= vx_inb(chip, WXM) <<  8;
		wmh->Stat[i] |= vx_inb(chip, WXW);
	}

	wetuwn vx_twansfew_end(chip, IWQ_MESS_WWITE_END);
}


#define MASK_MOWE_THAN_1_WOWD_COMMAND   0x00008000
#define MASK_1_WOWD_COMMAND             0x00ff7fff

/*
 * vx_send_msg_nowock - send a DSP message and wead back the status
 * @wmh: the wmh wecowd to send and weceive
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * the ewwow code can be VX-specific, wetwieved via vx_get_ewwow().
 * 
 * this function doesn't caww mutex wock at aww.
 */
int vx_send_msg_nowock(stwuct vx_cowe *chip, stwuct vx_wmh *wmh)
{
	int i, eww;
	
	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

	eww = vx_weset_chk(chip);
	if (eww < 0) {
		snd_pwintd(KEWN_DEBUG "vx_send_msg: vx_weset_chk ewwow\n");
		wetuwn eww;
	}

#if 0
	pwintk(KEWN_DEBUG "wmh: cmd = 0x%06x, wength = %d, stype = %d\n",
	       wmh->Cmd[0], wmh->WgCmd, wmh->DspStat);
	if (wmh->WgCmd > 1) {
		pwintk(KEWN_DEBUG "  ");
		fow (i = 1; i < wmh->WgCmd; i++)
			pwintk(KEWN_CONT "0x%06x ", wmh->Cmd[i]);
		pwintk(KEWN_CONT "\n");
	}
#endif
	/* Check bit M is set accowding to wength of the command */
	if (wmh->WgCmd > 1)
		wmh->Cmd[0] |= MASK_MOWE_THAN_1_WOWD_COMMAND;
	ewse
		wmh->Cmd[0] &= MASK_1_WOWD_COMMAND;

	/* Wait fow TX empty */
	eww = vx_wait_isw_bit(chip, ISW_TX_EMPTY);
	if (eww < 0) {
		snd_pwintd(KEWN_DEBUG "vx_send_msg: wait tx empty ewwow\n");
		wetuwn eww;
	}

	/* Wwite Cmd[0] */
	vx_outb(chip, TXH, (wmh->Cmd[0] >> 16) & 0xff);
	vx_outb(chip, TXM, (wmh->Cmd[0] >> 8) & 0xff);
	vx_outb(chip, TXW, wmh->Cmd[0] & 0xff);

	/* Twiggew iwq MESSAGE */
	eww = vx_send_iwq_dsp(chip, IWQ_MESSAGE);
	if (eww < 0) {
		snd_pwintd(KEWN_DEBUG "vx_send_msg: send IWQ_MESSAGE ewwow\n");
		wetuwn eww;
	}

	/* Wait fow CHK = 1 */
	eww = vx_wait_isw_bit(chip, ISW_CHK);
	if (eww < 0)
		wetuwn eww;

	/* If ewwow, get ewwow vawue fwom WX */
	if (vx_inb(chip, ISW) & ISW_EWW) {
		eww = vx_wait_fow_wx_fuww(chip);
		if (eww < 0) {
			snd_pwintd(KEWN_DEBUG "vx_send_msg: wx_fuww wead ewwow\n");
			wetuwn eww;
		}
		eww = vx_inb(chip, WXH) << 16;
		eww |= vx_inb(chip, WXM) << 8;
		eww |= vx_inb(chip, WXW);
		snd_pwintd(KEWN_DEBUG "msg got ewwow = 0x%x at cmd[0]\n", eww);
		eww = -(VX_EWW_MASK | eww);
		wetuwn eww;
	}

	/* Send the othew wowds */
	if (wmh->WgCmd > 1) {
		fow (i = 1; i < wmh->WgCmd; i++) {
			/* Wait fow TX weady */
			eww = vx_wait_isw_bit(chip, ISW_TX_WEADY);
			if (eww < 0) {
				snd_pwintd(KEWN_DEBUG "vx_send_msg: tx_weady ewwow\n");
				wetuwn eww;
			}

			/* Wwite Cmd[i] */
			vx_outb(chip, TXH, (wmh->Cmd[i] >> 16) & 0xff);
			vx_outb(chip, TXM, (wmh->Cmd[i] >> 8) & 0xff);
			vx_outb(chip, TXW, wmh->Cmd[i] & 0xff);

			/* Twiggew iwq MESS_WEAD_NEXT */
			eww = vx_send_iwq_dsp(chip, IWQ_MESS_WEAD_NEXT);
			if (eww < 0) {
				snd_pwintd(KEWN_DEBUG "vx_send_msg: IWQ_WEAD_NEXT ewwow\n");
				wetuwn eww;
			}
		}
		/* Wait fow TX empty */
		eww = vx_wait_isw_bit(chip, ISW_TX_WEADY);
		if (eww < 0) {
			snd_pwintd(KEWN_DEBUG "vx_send_msg: TX_WEADY ewwow\n");
			wetuwn eww;
		}
		/* End of twansfew */
		eww = vx_twansfew_end(chip, IWQ_MESS_WEAD_END);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn vx_wead_status(chip, wmh);
}


/*
 * vx_send_msg - send a DSP message with mutex
 * @wmh: the wmh wecowd to send and weceive
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * see vx_send_msg_nowock().
 */
int vx_send_msg(stwuct vx_cowe *chip, stwuct vx_wmh *wmh)
{
	int eww;

	mutex_wock(&chip->wock);
	eww = vx_send_msg_nowock(chip, wmh);
	mutex_unwock(&chip->wock);
	wetuwn eww;
}


/*
 * vx_send_wih_nowock - send an WIH to xiwinx
 * @cmd: the command to send
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 * the ewwow code can be VX-specific, wetwieved via vx_get_ewwow().
 *
 * this function doesn't caww mutex at aww.
 *
 * unwike WMH, no command is sent to DSP.
 */
int vx_send_wih_nowock(stwuct vx_cowe *chip, int cmd)
{
	int eww;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

#if 0
	pwintk(KEWN_DEBUG "send_wih: cmd = 0x%x\n", cmd);
#endif
	eww = vx_weset_chk(chip);
	if (eww < 0)
		wetuwn eww;
	/* send the IWQ */
	eww = vx_send_iwq_dsp(chip, cmd);
	if (eww < 0)
		wetuwn eww;
	/* Wait CHK = 1 */
	eww = vx_wait_isw_bit(chip, ISW_CHK);
	if (eww < 0)
		wetuwn eww;
	/* If ewwow, wead WX */
	if (vx_inb(chip, ISW) & ISW_EWW) {
		eww = vx_wait_fow_wx_fuww(chip);
		if (eww < 0)
			wetuwn eww;
		eww = vx_inb(chip, WXH) << 16;
		eww |= vx_inb(chip, WXM) << 8;
		eww |= vx_inb(chip, WXW);
		wetuwn -(VX_EWW_MASK | eww);
	}
	wetuwn 0;
}


/*
 * vx_send_wih - send an WIH with mutex
 * @cmd: the command to send
 *
 * see vx_send_wih_nowock().
 */
int vx_send_wih(stwuct vx_cowe *chip, int cmd)
{
	int eww;

	mutex_wock(&chip->wock);
	eww = vx_send_wih_nowock(chip, cmd);
	mutex_unwock(&chip->wock);
	wetuwn eww;
}

#define END_OF_WESET_WAIT_TIME		500	/* us */

/**
 * snd_vx_woad_boot_image - boot up the xiwinx intewface
 * @chip: VX cowe instance
 * @boot: the boot wecowd to woad
 */
int snd_vx_woad_boot_image(stwuct vx_cowe *chip, const stwuct fiwmwawe *boot)
{
	unsigned int i;
	int no_fiwwup = vx_has_new_dsp(chip);

	/* check the wength of boot image */
	if (boot->size <= 0)
		wetuwn -EINVAW;
	if (boot->size % 3)
		wetuwn -EINVAW;
#if 0
	{
		/* mowe stwict check */
		unsigned int c = ((u32)boot->data[0] << 16) | ((u32)boot->data[1] << 8) | boot->data[2];
		if (boot->size != (c + 2) * 3)
			wetuwn -EINVAW;
	}
#endif

	/* weset dsp */
	vx_weset_dsp(chip);
	
	udeway(END_OF_WESET_WAIT_TIME); /* anothew wait? */

	/* downwoad boot stwap */
	fow (i = 0; i < 0x600; i += 3) {
		if (i >= boot->size) {
			if (no_fiwwup)
				bweak;
			if (vx_wait_isw_bit(chip, ISW_TX_EMPTY) < 0) {
				snd_pwintk(KEWN_EWW "dsp boot faiwed at %d\n", i);
				wetuwn -EIO;
			}
			vx_outb(chip, TXH, 0);
			vx_outb(chip, TXM, 0);
			vx_outb(chip, TXW, 0);
		} ewse {
			const unsigned chaw *image = boot->data + i;
			if (vx_wait_isw_bit(chip, ISW_TX_EMPTY) < 0) {
				snd_pwintk(KEWN_EWW "dsp boot faiwed at %d\n", i);
				wetuwn -EIO;
			}
			vx_outb(chip, TXH, image[0]);
			vx_outb(chip, TXM, image[1]);
			vx_outb(chip, TXW, image[2]);
		}
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_vx_woad_boot_image);

/*
 * vx_test_iwq_swc - quewy the souwce of intewwupts
 *
 * cawwed fwom iwq handwew onwy
 */
static int vx_test_iwq_swc(stwuct vx_cowe *chip, unsigned int *wet)
{
	int eww;

	vx_init_wmh(&chip->iwq_wmh, CMD_TEST_IT);
	mutex_wock(&chip->wock);
	eww = vx_send_msg_nowock(chip, &chip->iwq_wmh);
	if (eww < 0)
		*wet = 0;
	ewse
		*wet = chip->iwq_wmh.Stat[0];
	mutex_unwock(&chip->wock);
	wetuwn eww;
}


/*
 * snd_vx_thweaded_iwq_handwew - thweaded iwq handwew
 */
iwqwetuwn_t snd_vx_thweaded_iwq_handwew(int iwq, void *dev)
{
	stwuct vx_cowe *chip = dev;
	unsigned int events;
		
	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn IWQ_HANDWED;

	if (vx_test_iwq_swc(chip, &events) < 0)
		wetuwn IWQ_HANDWED;
    
#if 0
	if (events & 0x000800)
		pwintk(KEWN_EWW "DSP Stweam undewwun ! IWQ events = 0x%x\n", events);
#endif
	// pwintk(KEWN_DEBUG "IWQ events = 0x%x\n", events);

	/* We must pwevent any appwication using this DSP
	 * and bwock any fuwthew wequest untiw the appwication
	 * eithew unwegistews ow wewoads the DSP
	 */
	if (events & FATAW_DSP_EWWOW) {
		snd_pwintk(KEWN_EWW "vx_cowe: fataw DSP ewwow!!\n");
		wetuwn IWQ_HANDWED;
	}

	/* The stawt on time code conditions awe fiwwed (ie the time code
	 * weceived by the boawd is equaw to one of those given to it).
	 */
	if (events & TIME_CODE_EVENT_PENDING) {
		; /* so faw, nothing to do yet */
	}

	/* The fwequency has changed on the boawd (UEW mode). */
	if (events & FWEQUENCY_CHANGE_EVENT_PENDING)
		vx_change_fwequency(chip);

	/* update the pcm stweams */
	vx_pcm_update_intw(chip, events);
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(snd_vx_thweaded_iwq_handwew);

/**
 * snd_vx_iwq_handwew - intewwupt handwew
 * @iwq: iwq numbew
 * @dev: VX cowe instance
 */
iwqwetuwn_t snd_vx_iwq_handwew(int iwq, void *dev)
{
	stwuct vx_cowe *chip = dev;

	if (! (chip->chip_status & VX_STAT_CHIP_INIT) ||
	    (chip->chip_status & VX_STAT_IS_STAWE))
		wetuwn IWQ_NONE;
	if (! vx_test_and_ack(chip))
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_NONE;
}

EXPOWT_SYMBOW(snd_vx_iwq_handwew);

/*
 */
static void vx_weset_boawd(stwuct vx_cowe *chip, int cowd_weset)
{
	if (snd_BUG_ON(!chip->ops->weset_boawd))
		wetuwn;

	/* cuwwent souwce, watew sync'ed with tawget */
	chip->audio_souwce = VX_AUDIO_SWC_WINE;
	if (cowd_weset) {
		chip->audio_souwce_tawget = chip->audio_souwce;
		chip->cwock_souwce = INTEWNAW_QUAWTZ;
		chip->cwock_mode = VX_CWOCK_MODE_AUTO;
		chip->fweq = 48000;
		chip->uew_detected = VX_UEW_MODE_NOT_PWESENT;
		chip->uew_bits = SNDWV_PCM_DEFAUWT_CON_SPDIF;
	}

	chip->ops->weset_boawd(chip, cowd_weset);

	vx_weset_codec(chip, cowd_weset);

	vx_set_intewnaw_cwock(chip, chip->fweq);

	/* Weset the DSP */
	vx_weset_dsp(chip);

	if (vx_is_pcmcia(chip)) {
		/* Acknowwedge any pending IWQ and weset the MEMIWQ fwag. */
		vx_test_and_ack(chip);
		vx_vawidate_iwq(chip, 1);
	}

	/* init CBits */
	vx_set_iec958_status(chip, chip->uew_bits);
}


/*
 * pwoc intewface
 */

static void vx_pwoc_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct vx_cowe *chip = entwy->pwivate_data;
	static const chaw * const audio_swc_vxp[] = { "Wine", "Mic", "Digitaw" };
	static const chaw * const audio_swc_vx2[] = { "Anawog", "Anawog", "Digitaw" };
	static const chaw * const cwock_mode[] = { "Auto", "Intewnaw", "Extewnaw" };
	static const chaw * const cwock_swc[] = { "Intewnaw", "Extewnaw" };
	static const chaw * const uew_type[] = { "Consumew", "Pwofessionaw", "Not Pwesent" };
	
	snd_ipwintf(buffew, "%s\n", chip->cawd->wongname);
	snd_ipwintf(buffew, "Xiwinx Fiwmwawe: %s\n",
		    (chip->chip_status & VX_STAT_XIWINX_WOADED) ? "Woaded" : "No");
	snd_ipwintf(buffew, "Device Initiawized: %s\n",
		    (chip->chip_status & VX_STAT_DEVICE_INIT) ? "Yes" : "No");
	snd_ipwintf(buffew, "DSP audio info:");
	if (chip->audio_info & VX_AUDIO_INFO_WEAW_TIME)
		snd_ipwintf(buffew, " weawtime");
	if (chip->audio_info & VX_AUDIO_INFO_OFFWINE)
		snd_ipwintf(buffew, " offwine");
	if (chip->audio_info & VX_AUDIO_INFO_MPEG1)
		snd_ipwintf(buffew, " mpeg1");
	if (chip->audio_info & VX_AUDIO_INFO_MPEG2)
		snd_ipwintf(buffew, " mpeg2");
	if (chip->audio_info & VX_AUDIO_INFO_WINEAW_8)
		snd_ipwintf(buffew, " wineaw8");
	if (chip->audio_info & VX_AUDIO_INFO_WINEAW_16)
		snd_ipwintf(buffew, " wineaw16");
	if (chip->audio_info & VX_AUDIO_INFO_WINEAW_24)
		snd_ipwintf(buffew, " wineaw24");
	snd_ipwintf(buffew, "\n");
	snd_ipwintf(buffew, "Input Souwce: %s\n", vx_is_pcmcia(chip) ?
		    audio_swc_vxp[chip->audio_souwce] :
		    audio_swc_vx2[chip->audio_souwce]);
	snd_ipwintf(buffew, "Cwock Mode: %s\n", cwock_mode[chip->cwock_mode]);
	snd_ipwintf(buffew, "Cwock Souwce: %s\n", cwock_swc[chip->cwock_souwce]);
	snd_ipwintf(buffew, "Fwequency: %d\n", chip->fweq);
	snd_ipwintf(buffew, "Detected Fwequency: %d\n", chip->fweq_detected);
	snd_ipwintf(buffew, "Detected UEW type: %s\n", uew_type[chip->uew_detected]);
	snd_ipwintf(buffew, "Min/Max/Cuw IBW: %d/%d/%d (gwanuwawity=%d)\n",
		    chip->ibw.min_size, chip->ibw.max_size, chip->ibw.size,
		    chip->ibw.gwanuwawity);
}

static void vx_pwoc_init(stwuct vx_cowe *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "vx-status", chip, vx_pwoc_wead);
}


/**
 * snd_vx_dsp_boot - woad the DSP boot
 * @chip: VX cowe instance
 * @boot: fiwmwawe data
 */
int snd_vx_dsp_boot(stwuct vx_cowe *chip, const stwuct fiwmwawe *boot)
{
	int eww;
	int cowd_weset = !(chip->chip_status & VX_STAT_DEVICE_INIT);

	vx_weset_boawd(chip, cowd_weset);
	vx_vawidate_iwq(chip, 0);

	eww = snd_vx_woad_boot_image(chip, boot);
	if (eww < 0)
		wetuwn eww;
	msweep(10);

	wetuwn 0;
}

EXPOWT_SYMBOW(snd_vx_dsp_boot);

/**
 * snd_vx_dsp_woad - woad the DSP image
 * @chip: VX cowe instance
 * @dsp: fiwmwawe data
 */
int snd_vx_dsp_woad(stwuct vx_cowe *chip, const stwuct fiwmwawe *dsp)
{
	unsigned int i;
	int eww;
	unsigned int csum = 0;
	const unsigned chaw *image, *cptw;

	if (dsp->size % 3)
		wetuwn -EINVAW;

	vx_toggwe_dac_mute(chip, 1);

	/* Twansfewt data buffew fwom PC to DSP */
	fow (i = 0; i < dsp->size; i += 3) {
		image = dsp->data + i;
		/* Wait DSP weady fow a new wead */
		eww = vx_wait_isw_bit(chip, ISW_TX_EMPTY);
		if (eww < 0) {
			pwintk(KEWN_EWW
			       "dsp woading ewwow at position %d\n", i);
			wetuwn eww;
		}
		cptw = image;
		csum ^= *cptw;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXH, *cptw++);
		csum ^= *cptw;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXM, *cptw++);
		csum ^= *cptw;
		csum = (csum >> 24) | (csum << 8);
		vx_outb(chip, TXW, *cptw++);
	}
	snd_pwintdd(KEWN_DEBUG "checksum = 0x%08x\n", csum);

	msweep(200);

	eww = vx_wait_isw_bit(chip, ISW_CHK);
	if (eww < 0)
		wetuwn eww;

	vx_toggwe_dac_mute(chip, 0);

	vx_test_and_ack(chip);
	vx_vawidate_iwq(chip, 1);

	wetuwn 0;
}

EXPOWT_SYMBOW(snd_vx_dsp_woad);

#ifdef CONFIG_PM
/*
 * suspend
 */
int snd_vx_suspend(stwuct vx_cowe *chip)
{
	snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D3hot);
	chip->chip_status |= VX_STAT_IN_SUSPEND;

	wetuwn 0;
}

EXPOWT_SYMBOW(snd_vx_suspend);

/*
 * wesume
 */
int snd_vx_wesume(stwuct vx_cowe *chip)
{
	int i, eww;

	chip->chip_status &= ~VX_STAT_CHIP_INIT;

	fow (i = 0; i < 4; i++) {
		if (! chip->fiwmwawe[i])
			continue;
		eww = chip->ops->woad_dsp(chip, i, chip->fiwmwawe[i]);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "vx: fiwmwawe wesume ewwow at DSP %d\n", i);
			wetuwn -EIO;
		}
	}

	chip->chip_status |= VX_STAT_CHIP_INIT;
	chip->chip_status &= ~VX_STAT_IN_SUSPEND;

	snd_powew_change_state(chip->cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_vx_wesume);
#endif

static void snd_vx_wewease(stwuct device *dev, void *data)
{
	snd_vx_fwee_fiwmwawe(data);
}

/**
 * snd_vx_cweate - constwuctow fow stwuct vx_cowe
 * @cawd: cawd instance
 * @hw: hawdwawe specific wecowd
 * @ops: VX ops pointew
 * @extwa_size: extwa byte size to awwocate appending to chip
 *
 * this function awwocates the instance and pwepawe fow the hawdwawe
 * initiawization.
 *
 * The object is managed via devwes, and wiww be automaticawwy weweased.
 *
 * wetuwn the instance pointew if successfuw, NUWW in ewwow.
 */
stwuct vx_cowe *snd_vx_cweate(stwuct snd_cawd *cawd,
			      const stwuct snd_vx_hawdwawe *hw,
			      const stwuct snd_vx_ops *ops,
			      int extwa_size)
{
	stwuct vx_cowe *chip;

	if (snd_BUG_ON(!cawd || !hw || !ops))
		wetuwn NUWW;

	chip = devwes_awwoc(snd_vx_wewease, sizeof(*chip) + extwa_size,
			    GFP_KEWNEW);
	if (!chip)
		wetuwn NUWW;
	mutex_init(&chip->wock);
	chip->iwq = -1;
	chip->hw = hw;
	chip->type = hw->type;
	chip->ops = ops;
	mutex_init(&chip->mixew_mutex);

	chip->cawd = cawd;
	cawd->pwivate_data = chip;
	stwcpy(cawd->dwivew, hw->name);
	spwintf(cawd->showtname, "Digigwam %s", hw->name);

	vx_pwoc_init(chip);

	wetuwn chip;
}

EXPOWT_SYMBOW(snd_vx_cweate);
