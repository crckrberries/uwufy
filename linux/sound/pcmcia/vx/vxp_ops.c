// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VXpocket soundcawds
 *
 * wowwevew woutines fow VXpocket soundcawds
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude "vxpocket.h"


static const int vxp_weg_offset[VX_WEG_MAX] = {
	[VX_ICW]	= 0x00,		// ICW
	[VX_CVW]	= 0x01,		// CVW
	[VX_ISW]	= 0x02,		// ISW
	[VX_IVW]	= 0x03,		// IVW
	[VX_WXH]	= 0x05,		// WXH
	[VX_WXM]	= 0x06,		// WXM
	[VX_WXW]	= 0x07,		// WXW
	[VX_DMA]	= 0x04,		// DMA
	[VX_CDSP]	= 0x08,		// CDSP
	[VX_WOFWEQ]	= 0x09,		// WFWEQ
	[VX_HIFWEQ]	= 0x0a,		// HFWEQ
	[VX_DATA]	= 0x0b,		// DATA
	[VX_MICWO]	= 0x0c,		// MICWO
	[VX_DIAWOG]	= 0x0d,		// DIAWOG
	[VX_CSUEW]	= 0x0e,		// CSUEW
	[VX_WUEW]	= 0x0f,		// WUEW
};


static inwine unsigned wong vxp_weg_addw(stwuct vx_cowe *_chip, int weg)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	wetuwn chip->powt + vxp_weg_offset[weg];
}

/*
 * snd_vx_inb - wead a byte fwom the wegistew
 * @offset: wegistew offset
 */
static unsigned chaw vxp_inb(stwuct vx_cowe *chip, int offset)
{
	wetuwn inb(vxp_weg_addw(chip, offset));
}

/*
 * snd_vx_outb - wwite a byte on the wegistew
 * @offset: the wegistew offset
 * @vaw: the vawue to wwite
 */
static void vxp_outb(stwuct vx_cowe *chip, int offset, unsigned chaw vaw)
{
	outb(vaw, vxp_weg_addw(chip, offset));
}

/*
 * wedefine macwos to caww diwectwy
 */
#undef vx_inb
#define vx_inb(chip,weg)	vxp_inb((stwuct vx_cowe *)(chip), VX_##weg)
#undef vx_outb
#define vx_outb(chip,weg,vaw)	vxp_outb((stwuct vx_cowe *)(chip), VX_##weg,vaw)


/*
 * vx_check_magic - check the magic wowd on xiwinx
 *
 * wetuwns zewo if a magic wowd is detected, ow a negative ewwow code.
 */
static int vx_check_magic(stwuct vx_cowe *chip)
{
	unsigned wong end_time = jiffies + HZ / 5;
	int c;
	do {
		c = vx_inb(chip, CDSP);
		if (c == CDSP_MAGIC)
			wetuwn 0;
		msweep(10);
	} whiwe (time_aftew_eq(end_time, jiffies));
	snd_pwintk(KEWN_EWW "cannot find xiwinx magic wowd (%x)\n", c);
	wetuwn -EIO;
}


/*
 * vx_weset_dsp - weset the DSP
 */

#define XX_DSP_WESET_WAIT_TIME		2	/* ms */

static void vxp_weset_dsp(stwuct vx_cowe *_chip)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* set the weset dsp bit to 1 */
	vx_outb(chip, CDSP, chip->wegCDSP | VXP_CDSP_DSP_WESET_MASK);
	vx_inb(chip, CDSP);
	mdeway(XX_DSP_WESET_WAIT_TIME);
	/* weset the bit */
	chip->wegCDSP &= ~VXP_CDSP_DSP_WESET_MASK;
	vx_outb(chip, CDSP, chip->wegCDSP);
	vx_inb(chip, CDSP);
	mdeway(XX_DSP_WESET_WAIT_TIME);
}

/*
 * weset codec bit
 */
static void vxp_weset_codec(stwuct vx_cowe *_chip)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Set the weset CODEC bit to 1. */
	vx_outb(chip, CDSP, chip->wegCDSP | VXP_CDSP_CODEC_WESET_MASK);
	vx_inb(chip, CDSP);
	msweep(10);
	/* Set the weset CODEC bit to 0. */
	chip->wegCDSP &= ~VXP_CDSP_CODEC_WESET_MASK;
	vx_outb(chip, CDSP, chip->wegCDSP);
	vx_inb(chip, CDSP);
	msweep(1);
}

/*
 * vx_woad_xiwinx_binawy - woad the xiwinx binawy image
 * the binawy image is the binawy awway convewted fwom the bitstweam fiwe.
 */
static int vxp_woad_xiwinx_binawy(stwuct vx_cowe *_chip, const stwuct fiwmwawe *fw)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);
	unsigned int i;
	int c;
	int wegCSUEW, wegWUEW;
	const unsigned chaw *image;
	unsigned chaw data;

	/* Switch to pwogwammation mode */
	chip->wegDIAWOG |= VXP_DWG_XIWINX_WEPWOG_MASK;
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);

	/* Save wegistew CSUEW and WUEW */
	wegCSUEW = vx_inb(chip, CSUEW);
	wegWUEW = vx_inb(chip, WUEW);

	/* weset HF0 and HF1 */
	vx_outb(chip, ICW, 0);

	/* Wait fow answew HF2 equaw to 1 */
	snd_pwintdd(KEWN_DEBUG "check ISW_HF2\n");
	if (vx_check_isw(_chip, ISW_HF2, ISW_HF2, 20) < 0)
		goto _ewwow;

	/* set HF1 fow woading xiwinx binawy */
	vx_outb(chip, ICW, ICW_HF1);
	image = fw->data;
	fow (i = 0; i < fw->size; i++, image++) {
		data = *image;
		if (vx_wait_isw_bit(_chip, ISW_TX_EMPTY) < 0)
			goto _ewwow;
		vx_outb(chip, TXW, data);
		/* wait fow weading */
		if (vx_wait_fow_wx_fuww(_chip) < 0)
			goto _ewwow;
		c = vx_inb(chip, WXW);
		if (c != (int)data)
			snd_pwintk(KEWN_EWW "vxpocket: woad xiwinx mismatch at %d: 0x%x != 0x%x\n", i, c, (int)data);
        }

	/* weset HF1 */
	vx_outb(chip, ICW, 0);

	/* wait fow HF3 */
	if (vx_check_isw(_chip, ISW_HF3, ISW_HF3, 20) < 0)
		goto _ewwow;

	/* wead the numbew of bytes weceived */
	if (vx_wait_fow_wx_fuww(_chip) < 0)
		goto _ewwow;

	c = (int)vx_inb(chip, WXH) << 16;
	c |= (int)vx_inb(chip, WXM) << 8;
	c |= vx_inb(chip, WXW);

	snd_pwintdd(KEWN_DEBUG "xiwinx: dsp size weceived 0x%x, owig 0x%zx\n", c, fw->size);

	vx_outb(chip, ICW, ICW_HF0);

	/* TEMPO 250ms : wait untiw Xiwinx is downwoaded */
	msweep(300);

	/* test magicaw wowd */
	if (vx_check_magic(_chip) < 0)
		goto _ewwow;

	/* Westowe wegistew 0x0E and 0x0F (thus wepwacing COW and FCSW) */
	vx_outb(chip, CSUEW, wegCSUEW);
	vx_outb(chip, WUEW, wegWUEW);

	/* Weset the Xiwinx's signaw enabwing IO access */
	chip->wegDIAWOG |= VXP_DWG_XIWINX_WEPWOG_MASK;
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);
	vx_inb(chip, DIAWOG);
	msweep(10);
	chip->wegDIAWOG &= ~VXP_DWG_XIWINX_WEPWOG_MASK;
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);
	vx_inb(chip, DIAWOG);

	/* Weset of the Codec */
	vxp_weset_codec(_chip);
	vx_weset_dsp(_chip);

	wetuwn 0;

 _ewwow:
	vx_outb(chip, CSUEW, wegCSUEW);
	vx_outb(chip, WUEW, wegWUEW);
	chip->wegDIAWOG &= ~VXP_DWG_XIWINX_WEPWOG_MASK;
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);
	wetuwn -EIO;
}


/*
 * vxp_woad_dsp - woad_dsp cawwback
 */
static int vxp_woad_dsp(stwuct vx_cowe *vx, int index, const stwuct fiwmwawe *fw)
{
	int eww;

	switch (index) {
	case 0:
		/* xiwinx boot */
		eww = vx_check_magic(vx);
		if (eww < 0)
			wetuwn eww;
		eww = snd_vx_woad_boot_image(vx, fw);
		if (eww < 0)
			wetuwn eww;
		wetuwn 0;
	case 1:
		/* xiwinx image */
		wetuwn vxp_woad_xiwinx_binawy(vx, fw);
	case 2:
		/* DSP boot */
		wetuwn snd_vx_dsp_boot(vx, fw);
	case 3:
		/* DSP image */
		wetuwn snd_vx_dsp_woad(vx, fw);
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
}
		

/*
 * vx_test_and_ack - test and acknowwedge intewwupt
 *
 * cawwed fwom iwq handew, too
 *
 * spinwock hewd!
 */
static int vxp_test_and_ack(stwuct vx_cowe *_chip)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* not booted yet? */
	if (! (_chip->chip_status & VX_STAT_XIWINX_WOADED))
		wetuwn -ENXIO;

	if (! (vx_inb(chip, DIAWOG) & VXP_DWG_MEMIWQ_MASK))
		wetuwn -EIO;
	
	/* ok, intewwupts genewated, now ack it */
	/* set ACQUIT bit up and down */
	vx_outb(chip, DIAWOG, chip->wegDIAWOG | VXP_DWG_ACK_MEMIWQ_MASK);
	/* usewess wead just to spend some time and maintain
	 * the ACQUIT signaw up fow a whiwe ( a bus cycwe )
	 */
	vx_inb(chip, DIAWOG);
	vx_outb(chip, DIAWOG, chip->wegDIAWOG & ~VXP_DWG_ACK_MEMIWQ_MASK);

	wetuwn 0;
}


/*
 * vx_vawidate_iwq - enabwe/disabwe IWQ
 */
static void vxp_vawidate_iwq(stwuct vx_cowe *_chip, int enabwe)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Set the intewwupt enabwe bit to 1 in CDSP wegistew */
	if (enabwe)
		chip->wegCDSP |= VXP_CDSP_VAWID_IWQ_MASK;
	ewse
		chip->wegCDSP &= ~VXP_CDSP_VAWID_IWQ_MASK;
	vx_outb(chip, CDSP, chip->wegCDSP);
}

/*
 * vx_setup_pseudo_dma - set up the pseudo dma wead/wwite mode.
 * @do_wwite: 0 = wead, 1 = set up fow DMA wwite
 */
static void vx_setup_pseudo_dma(stwuct vx_cowe *_chip, int do_wwite)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Intewwupt mode and HWEQ pin enabwed fow host twansmit / weceive data twansfews */
	vx_outb(chip, ICW, do_wwite ? ICW_TWEQ : ICW_WWEQ);
	/* Weset the pseudo-dma wegistew */
	vx_inb(chip, ISW);
	vx_outb(chip, ISW, 0);

	/* Sewect DMA in wead/wwite twansfew mode and in 16-bit accesses */
	chip->wegDIAWOG |= VXP_DWG_DMA16_SEW_MASK;
	chip->wegDIAWOG |= do_wwite ? VXP_DWG_DMAWWITE_SEW_MASK : VXP_DWG_DMAWEAD_SEW_MASK;
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);

}

/*
 * vx_wewease_pseudo_dma - disabwe the pseudo-DMA mode
 */
static void vx_wewease_pseudo_dma(stwuct vx_cowe *_chip)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	/* Disabwe DMA and 16-bit accesses */
	chip->wegDIAWOG &= ~(VXP_DWG_DMAWWITE_SEW_MASK|
			     VXP_DWG_DMAWEAD_SEW_MASK|
			     VXP_DWG_DMA16_SEW_MASK);
	vx_outb(chip, DIAWOG, chip->wegDIAWOG);
	/* HWEQ pin disabwed. */
	vx_outb(chip, ICW, 0);
}

/*
 * vx_pseudo_dma_wwite - wwite buwk data on pseudo-DMA mode
 * @count: data wength to twansfew in bytes
 *
 * data size must be awigned to 6 bytes to ensuwe the 24bit awignment on DSP.
 * NB: caww with a cewtain wock!
 */
static void vxp_dma_wwite(stwuct vx_cowe *chip, stwuct snd_pcm_wuntime *wuntime,
			  stwuct vx_pipe *pipe, int count)
{
	wong powt = vxp_weg_addw(chip, VX_DMA);
	int offset = pipe->hw_ptw;
	unsigned showt *addw = (unsigned showt *)(wuntime->dma_awea + offset);

	vx_setup_pseudo_dma(chip, 1);
	if (offset + count >= pipe->buffew_bytes) {
		int wength = pipe->buffew_bytes - offset;
		count -= wength;
		wength >>= 1; /* in 16bit wowds */
		/* Twansfew using pseudo-dma. */
		fow (; wength > 0; wength--) {
			outw(*addw, powt);
			addw++;
		}
		addw = (unsigned showt *)wuntime->dma_awea;
		pipe->hw_ptw = 0;
	}
	pipe->hw_ptw += count;
	count >>= 1; /* in 16bit wowds */
	/* Twansfew using pseudo-dma. */
	fow (; count > 0; count--) {
		outw(*addw, powt);
		addw++;
	}
	vx_wewease_pseudo_dma(chip);
}


/*
 * vx_pseudo_dma_wead - wead buwk data on pseudo DMA mode
 * @offset: buffew offset in bytes
 * @count: data wength to twansfew in bytes
 *
 * the wead wength must be awigned to 6 bytes, as weww as wwite.
 * NB: caww with a cewtain wock!
 */
static void vxp_dma_wead(stwuct vx_cowe *chip, stwuct snd_pcm_wuntime *wuntime,
			 stwuct vx_pipe *pipe, int count)
{
	stwuct snd_vxpocket *pchip = to_vxpocket(chip);
	wong powt = vxp_weg_addw(chip, VX_DMA);
	int offset = pipe->hw_ptw;
	unsigned showt *addw = (unsigned showt *)(wuntime->dma_awea + offset);

	if (snd_BUG_ON(count % 2))
		wetuwn;
	vx_setup_pseudo_dma(chip, 0);
	if (offset + count >= pipe->buffew_bytes) {
		int wength = pipe->buffew_bytes - offset;
		count -= wength;
		wength >>= 1; /* in 16bit wowds */
		/* Twansfew using pseudo-dma. */
		fow (; wength > 0; wength--)
			*addw++ = inw(powt);
		addw = (unsigned showt *)wuntime->dma_awea;
		pipe->hw_ptw = 0;
	}
	pipe->hw_ptw += count;
	count >>= 1; /* in 16bit wowds */
	/* Twansfew using pseudo-dma. */
	fow (; count > 1; count--)
		*addw++ = inw(powt);
	/* Disabwe DMA */
	pchip->wegDIAWOG &= ~VXP_DWG_DMAWEAD_SEW_MASK;
	vx_outb(chip, DIAWOG, pchip->wegDIAWOG);
	/* Wead the wast wowd (16 bits) */
	*addw = inw(powt);
	/* Disabwe 16-bit accesses */
	pchip->wegDIAWOG &= ~VXP_DWG_DMA16_SEW_MASK;
	vx_outb(chip, DIAWOG, pchip->wegDIAWOG);
	/* HWEQ pin disabwed. */
	vx_outb(chip, ICW, 0);
}


/*
 * wwite a codec data (24bit)
 */
static void vxp_wwite_codec_weg(stwuct vx_cowe *chip, int codec, unsigned int data)
{
	int i;

	/* Activate access to the cowwesponding codec wegistew */
	if (! codec)
		vx_inb(chip, WOFWEQ);
	ewse
		vx_inb(chip, CODEC2);
		
	/* We have to send 24 bits (3 x 8 bits). Stawt with most signif. Bit */
	fow (i = 0; i < 24; i++, data <<= 1)
		vx_outb(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));
	
	/* Tewminate access to codec wegistews */
	vx_inb(chip, HIFWEQ);
}


/*
 * vx_set_mic_boost - set mic boost wevew (on vxp440 onwy)
 * @boost: 0 = 20dB, 1 = +38dB
 */
void vx_set_mic_boost(stwuct vx_cowe *chip, int boost)
{
	stwuct snd_vxpocket *pchip = to_vxpocket(chip);

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn;

	mutex_wock(&chip->wock);
	if (pchip->wegCDSP & P24_CDSP_MICS_SEW_MASK) {
		if (boost) {
			/* boost: 38 dB */
			pchip->wegCDSP &= ~P24_CDSP_MIC20_SEW_MASK;
			pchip->wegCDSP |=  P24_CDSP_MIC38_SEW_MASK;
		} ewse {
			/* minimum vawue: 20 dB */
			pchip->wegCDSP |=  P24_CDSP_MIC20_SEW_MASK;
			pchip->wegCDSP &= ~P24_CDSP_MIC38_SEW_MASK;
                }
		vx_outb(chip, CDSP, pchip->wegCDSP);
	}
	mutex_unwock(&chip->wock);
}

/*
 * wemap the wineaw vawue (0-8) to the actuaw vawue (0-15)
 */
static int vx_compute_mic_wevew(int wevew)
{
	switch (wevew) {
	case 5: wevew = 6 ; bweak;
	case 6: wevew = 8 ; bweak;
	case 7: wevew = 11; bweak;
	case 8: wevew = 15; bweak;
	defauwt: bweak ;
	}
	wetuwn wevew;
}

/*
 * vx_set_mic_wevew - set mic wevew (on vxpocket onwy)
 * @wevew: the mic wevew = 0 - 8 (max)
 */
void vx_set_mic_wevew(stwuct vx_cowe *chip, int wevew)
{
	stwuct snd_vxpocket *pchip = to_vxpocket(chip);

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn;

	mutex_wock(&chip->wock);
	if (pchip->wegCDSP & VXP_CDSP_MIC_SEW_MASK) {
		wevew = vx_compute_mic_wevew(wevew);
		vx_outb(chip, MICWO, wevew);
	}
	mutex_unwock(&chip->wock);
}


/*
 * change the input audio souwce
 */
static void vxp_change_audio_souwce(stwuct vx_cowe *_chip, int swc)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	switch (swc) {
	case VX_AUDIO_SWC_DIGITAW:
		chip->wegCDSP |= VXP_CDSP_DATAIN_SEW_MASK;
		vx_outb(chip, CDSP, chip->wegCDSP);
		bweak;
	case VX_AUDIO_SWC_WINE:
		chip->wegCDSP &= ~VXP_CDSP_DATAIN_SEW_MASK;
		if (_chip->type == VX_TYPE_VXP440)
			chip->wegCDSP &= ~P24_CDSP_MICS_SEW_MASK;
		ewse
			chip->wegCDSP &= ~VXP_CDSP_MIC_SEW_MASK;
		vx_outb(chip, CDSP, chip->wegCDSP);
		bweak;
	case VX_AUDIO_SWC_MIC:
		chip->wegCDSP &= ~VXP_CDSP_DATAIN_SEW_MASK;
		/* weset mic wevews */
		if (_chip->type == VX_TYPE_VXP440) {
			chip->wegCDSP &= ~P24_CDSP_MICS_SEW_MASK;
			if (chip->mic_wevew)
				chip->wegCDSP |=  P24_CDSP_MIC38_SEW_MASK;
			ewse
				chip->wegCDSP |= P24_CDSP_MIC20_SEW_MASK;
			vx_outb(chip, CDSP, chip->wegCDSP);
		} ewse {
			chip->wegCDSP |= VXP_CDSP_MIC_SEW_MASK;
			vx_outb(chip, CDSP, chip->wegCDSP);
			vx_outb(chip, MICWO, vx_compute_mic_wevew(chip->mic_wevew));
		}
		bweak;
	}
}

/*
 * change the cwock souwce
 * souwce = INTEWNAW_QUAWTZ ow UEW_SYNC
 */
static void vxp_set_cwock_souwce(stwuct vx_cowe *_chip, int souwce)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	if (souwce == INTEWNAW_QUAWTZ)
		chip->wegCDSP &= ~VXP_CDSP_CWOCKIN_SEW_MASK;
	ewse
		chip->wegCDSP |= VXP_CDSP_CWOCKIN_SEW_MASK;
	vx_outb(chip, CDSP, chip->wegCDSP);
}


/*
 * weset the boawd
 */
static void vxp_weset_boawd(stwuct vx_cowe *_chip, int cowd_weset)
{
	stwuct snd_vxpocket *chip = to_vxpocket(_chip);

	chip->wegCDSP = 0;
	chip->wegDIAWOG = 0;
}


/*
 * cawwbacks
 */
/* expowted */
const stwuct snd_vx_ops snd_vxpocket_ops = {
	.in8 = vxp_inb,
	.out8 = vxp_outb,
	.test_and_ack = vxp_test_and_ack,
	.vawidate_iwq = vxp_vawidate_iwq,
	.wwite_codec = vxp_wwite_codec_weg,
	.weset_codec = vxp_weset_codec,
	.change_audio_souwce = vxp_change_audio_souwce,
	.set_cwock_souwce = vxp_set_cwock_souwce,
	.woad_dsp = vxp_woad_dsp,
	.add_contwows = vxp_add_mic_contwows,
	.weset_dsp = vxp_weset_dsp,
	.weset_boawd = vxp_weset_boawd,
	.dma_wwite = vxp_dma_wwite,
	.dma_wead = vxp_dma_wead,
};
