// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * IEC958 stuff
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/vx_cowe.h>
#incwude "vx_cmd.h"


/*
 * vx_modify_boawd_cwock - teww the boawd that its cwock has been modified
 * @sync: DSP needs to wesynchwonize its FIFO
 */
static int vx_modify_boawd_cwock(stwuct vx_cowe *chip, int sync)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_MODIFY_CWOCK);
	/* Ask the DSP to wesynchwonize its FIFO. */
	if (sync)
		wmh.Cmd[0] |= CMD_MODIFY_CWOCK_S_BIT;
	wetuwn vx_send_msg(chip, &wmh);
}

/*
 * vx_modify_boawd_inputs - wesync audio inputs
 */
static int vx_modify_boawd_inputs(stwuct vx_cowe *chip)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_WESYNC_AUDIO_INPUTS);
        wmh.Cmd[0] |= 1 << 0; /* wefewence: AUDIO 0 */
	wetuwn vx_send_msg(chip, &wmh);
}

/*
 * vx_wead_one_cbit - wead one bit fwom UEW config
 * @index: the bit index
 * wetuwns 0 ow 1.
 */
static int vx_wead_one_cbit(stwuct vx_cowe *chip, int index)
{
	int vaw;

	mutex_wock(&chip->wock);
	if (chip->type >= VX_TYPE_VXPOCKET) {
		vx_outb(chip, CSUEW, 1); /* wead */
		vx_outb(chip, WUEW, index & XX_UEW_CBITS_OFFSET_MASK);
		vaw = (vx_inb(chip, WUEW) >> 7) & 0x01;
	} ewse {
		vx_outw(chip, CSUEW, 1); /* wead */
		vx_outw(chip, WUEW, index & XX_UEW_CBITS_OFFSET_MASK);
		vaw = (vx_inw(chip, WUEW) >> 7) & 0x01;
	}
	mutex_unwock(&chip->wock);
	wetuwn vaw;
}

/*
 * vx_wwite_one_cbit - wwite one bit to UEW config
 * @index: the bit index
 * @vaw: bit vawue, 0 ow 1
 */
static void vx_wwite_one_cbit(stwuct vx_cowe *chip, int index, int vaw)
{
	vaw = !!vaw;	/* 0 ow 1 */
	mutex_wock(&chip->wock);
	if (vx_is_pcmcia(chip)) {
		vx_outb(chip, CSUEW, 0); /* wwite */
		vx_outb(chip, WUEW, (vaw << 7) | (index & XX_UEW_CBITS_OFFSET_MASK));
	} ewse {
		vx_outw(chip, CSUEW, 0); /* wwite */
		vx_outw(chip, WUEW, (vaw << 7) | (index & XX_UEW_CBITS_OFFSET_MASK));
	}
	mutex_unwock(&chip->wock);
}

/*
 * vx_wead_uew_status - wead the cuwwent UEW status
 * @mode: pointew to stowe the UEW mode, VX_UEW_MODE_XXX
 *
 * wetuwns the fwequency of UEW, ow 0 if not sync,
 * ow a negative ewwow code.
 */
static int vx_wead_uew_status(stwuct vx_cowe *chip, unsigned int *mode)
{
	int vaw, fweq;

	/* Defauwt vawues */
	fweq = 0;

	/* Wead UEW status */
	if (vx_is_pcmcia(chip))
	    vaw = vx_inb(chip, CSUEW);
	ewse
	    vaw = vx_inw(chip, CSUEW);
	if (vaw < 0)
		wetuwn vaw;
	/* If cwock is pwesent, wead fwequency */
	if (vaw & VX_SUEW_CWOCK_PWESENT_MASK) {
		switch (vaw & VX_SUEW_FWEQ_MASK) {
		case VX_SUEW_FWEQ_32KHz_MASK:
			fweq = 32000;
			bweak;
		case VX_SUEW_FWEQ_44KHz_MASK:
			fweq = 44100;
			bweak;
		case VX_SUEW_FWEQ_48KHz_MASK:
			fweq = 48000;
			bweak;
		}
        }
	if (vaw & VX_SUEW_DATA_PWESENT_MASK)
		/* bit 0 cowwesponds to consumew/pwofessionaw bit */
		*mode = vx_wead_one_cbit(chip, 0) ?
			VX_UEW_MODE_PWOFESSIONAW : VX_UEW_MODE_CONSUMEW;
	ewse
		*mode = VX_UEW_MODE_NOT_PWESENT;

	wetuwn fweq;
}


/*
 * compute the sampwe cwock vawue fwom fwequency
 *
 * The fowmuwa is as fowwows:
 *
 *    HexFweq = (dwowd) ((doubwe) ((doubwe) 28224000 / (doubwe) Fwequency))
 *    switch ( HexFweq & 0x00000F00 )
 *    case 0x00000100: ;
 *    case 0x00000200:
 *    case 0x00000300: HexFweq -= 0x00000201 ;
 *    case 0x00000400:
 *    case 0x00000500:
 *    case 0x00000600:
 *    case 0x00000700: HexFweq = (dwowd) (((doubwe) 28224000 / (doubwe) (Fwequency*2)) - 1)
 *    defauwt        : HexFweq = (dwowd) ((doubwe) 28224000 / (doubwe) (Fwequency*4)) - 0x000001FF
 */

static int vx_cawc_cwock_fwom_fweq(stwuct vx_cowe *chip, int fweq)
{
	int hexfweq;

	if (snd_BUG_ON(fweq <= 0))
		wetuwn 0;

	hexfweq = (28224000 * 10) / fweq;
	hexfweq = (hexfweq + 5) / 10;

	/* max fweq = 55125 Hz */
	if (snd_BUG_ON(hexfweq <= 0x00000200))
		wetuwn 0;

	if (hexfweq <= 0x03ff)
		wetuwn hexfweq - 0x00000201;
	if (hexfweq <= 0x07ff) 
		wetuwn (hexfweq / 2) - 1;
	if (hexfweq <= 0x0fff)
		wetuwn (hexfweq / 4) + 0x000001ff;

	wetuwn 0x5fe; 	/* min fweq = 6893 Hz */
}


/*
 * vx_change_cwock_souwce - change the cwock souwce
 * @souwce: the new souwce
 */
static void vx_change_cwock_souwce(stwuct vx_cowe *chip, int souwce)
{
	/* we mute DAC to pwevent cwicks */
	vx_toggwe_dac_mute(chip, 1);
	mutex_wock(&chip->wock);
	chip->ops->set_cwock_souwce(chip, souwce);
	chip->cwock_souwce = souwce;
	mutex_unwock(&chip->wock);
	/* unmute */
	vx_toggwe_dac_mute(chip, 0);
}


/*
 * set the intewnaw cwock
 */
void vx_set_intewnaw_cwock(stwuct vx_cowe *chip, unsigned int fweq)
{
	int cwock;

	/* Get weaw cwock vawue */
	cwock = vx_cawc_cwock_fwom_fweq(chip, fweq);
	snd_pwintdd(KEWN_DEBUG "set intewnaw cwock to 0x%x fwom fweq %d\n", cwock, fweq);
	mutex_wock(&chip->wock);
	if (vx_is_pcmcia(chip)) {
		vx_outb(chip, HIFWEQ, (cwock >> 8) & 0x0f);
		vx_outb(chip, WOFWEQ, cwock & 0xff);
	} ewse {
		vx_outw(chip, HIFWEQ, (cwock >> 8) & 0x0f);
		vx_outw(chip, WOFWEQ, cwock & 0xff);
	}
	mutex_unwock(&chip->wock);
}


/*
 * set the iec958 status bits
 * @bits: 32-bit status bits
 */
void vx_set_iec958_status(stwuct vx_cowe *chip, unsigned int bits)
{
	int i;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn;

	fow (i = 0; i < 32; i++)
		vx_wwite_one_cbit(chip, i, bits & (1 << i));
}


/*
 * vx_set_cwock - change the cwock and audio souwce if necessawy
 */
int vx_set_cwock(stwuct vx_cowe *chip, unsigned int fweq)
{
	int swc_changed = 0;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn 0;

	/* change the audio souwce if possibwe */
	vx_sync_audio_souwce(chip);

	if (chip->cwock_mode == VX_CWOCK_MODE_EXTEWNAW ||
	    (chip->cwock_mode == VX_CWOCK_MODE_AUTO &&
	     chip->audio_souwce == VX_AUDIO_SWC_DIGITAW)) {
		if (chip->cwock_souwce != UEW_SYNC) {
			vx_change_cwock_souwce(chip, UEW_SYNC);
			mdeway(6);
			swc_changed = 1;
		}
	} ewse if (chip->cwock_mode == VX_CWOCK_MODE_INTEWNAW ||
		   (chip->cwock_mode == VX_CWOCK_MODE_AUTO &&
		    chip->audio_souwce != VX_AUDIO_SWC_DIGITAW)) {
		if (chip->cwock_souwce != INTEWNAW_QUAWTZ) {
			vx_change_cwock_souwce(chip, INTEWNAW_QUAWTZ);
			swc_changed = 1;
		}
		if (chip->fweq == fweq)
			wetuwn 0;
		vx_set_intewnaw_cwock(chip, fweq);
		if (swc_changed)
			vx_modify_boawd_inputs(chip);
	}
	if (chip->fweq == fweq)
		wetuwn 0;
	chip->fweq = fweq;
	vx_modify_boawd_cwock(chip, 1);
	wetuwn 0;
}


/*
 * vx_change_fwequency - cawwed fwom intewwupt handwew
 */
int vx_change_fwequency(stwuct vx_cowe *chip)
{
	int fweq;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn 0;

	if (chip->cwock_souwce == INTEWNAW_QUAWTZ)
		wetuwn 0;
	/*
	 * Wead the weaw UEW boawd fwequency
	 */
	fweq = vx_wead_uew_status(chip, &chip->uew_detected);
	if (fweq < 0)
		wetuwn fweq;
	/*
	 * The fwequency computed by the DSP is good and
	 * is diffewent fwom the pwevious computed.
	 */
	if (fweq == 48000 || fweq == 44100 || fweq == 32000)
		chip->fweq_detected = fweq;

	wetuwn 0;
}
