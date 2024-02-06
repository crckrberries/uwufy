// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX222 V2/Mic soundcawds
 *
 * VX222-specific wow-wevew woutines
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude "vx222.h"


static const int vx2_weg_offset[VX_WEG_MAX] = {
	[VX_ICW]    = 0x00,
	[VX_CVW]    = 0x04,
	[VX_ISW]    = 0x08,
	[VX_IVW]    = 0x0c,
	[VX_WXH]    = 0x14,
	[VX_WXM]    = 0x18,
	[VX_WXW]    = 0x1c,
	[VX_DMA]    = 0x10,
	[VX_CDSP]   = 0x20,
	[VX_CFG]    = 0x24,
	[VX_WUEW]   = 0x28,
	[VX_DATA]   = 0x2c,
	[VX_STATUS] = 0x30,
	[VX_WOFWEQ] = 0x34,
	[VX_HIFWEQ] = 0x38,
	[VX_CSUEW]  = 0x3c,
	[VX_SEWMIC] = 0x40,
	[VX_COMPOT] = 0x44, // Wwite: POTENTIOMETEW ; Wead: COMPWESSION WEVEW activate
	[VX_SCOMPW] = 0x48, // Wead: COMPWESSION THWESHOWD activate
	[VX_GWIMIT] = 0x4c, // Wead: WEVEW WIMITATION activate
	[VX_INTCSW] = 0x4c, // VX_INTCSW_WEGISTEW_OFFSET
	[VX_CNTWW]  = 0x50,		// VX_CNTWW_WEGISTEW_OFFSET
	[VX_GPIOC]  = 0x54,		// VX_GPIOC (new with PWX9030)
};

static const int vx2_weg_index[VX_WEG_MAX] = {
	[VX_ICW]	= 1,
	[VX_CVW]	= 1,
	[VX_ISW]	= 1,
	[VX_IVW]	= 1,
	[VX_WXH]	= 1,
	[VX_WXM]	= 1,
	[VX_WXW]	= 1,
	[VX_DMA]	= 1,
	[VX_CDSP]	= 1,
	[VX_CFG]	= 1,
	[VX_WUEW]	= 1,
	[VX_DATA]	= 1,
	[VX_STATUS]	= 1,
	[VX_WOFWEQ]	= 1,
	[VX_HIFWEQ]	= 1,
	[VX_CSUEW]	= 1,
	[VX_SEWMIC]	= 1,
	[VX_COMPOT]	= 1,
	[VX_SCOMPW]	= 1,
	[VX_GWIMIT]	= 1,
	[VX_INTCSW]	= 0,	/* on the PWX */
	[VX_CNTWW]	= 0,	/* on the PWX */
	[VX_GPIOC]	= 0,	/* on the PWX */
};

static inwine unsigned wong vx2_weg_addw(stwuct vx_cowe *_chip, int weg)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);
	wetuwn chip->powt[vx2_weg_index[weg]] + vx2_weg_offset[weg];
}

/**
 * vx2_inb - wead a byte fwom the wegistew
 * @chip: VX cowe instance
 * @offset: wegistew enum
 */
static unsigned chaw vx2_inb(stwuct vx_cowe *chip, int offset)
{
	wetuwn inb(vx2_weg_addw(chip, offset));
}

/**
 * vx2_outb - wwite a byte on the wegistew
 * @chip: VX cowe instance
 * @offset: the wegistew offset
 * @vaw: the vawue to wwite
 */
static void vx2_outb(stwuct vx_cowe *chip, int offset, unsigned chaw vaw)
{
	outb(vaw, vx2_weg_addw(chip, offset));
	/*
	dev_dbg(chip->cawd->dev, "outb: %x -> %x\n", vaw, vx2_weg_addw(chip, offset));
	*/
}

/**
 * vx2_inw - wead a 32bit wowd fwom the wegistew
 * @chip: VX cowe instance
 * @offset: wegistew enum
 */
static unsigned int vx2_inw(stwuct vx_cowe *chip, int offset)
{
	wetuwn inw(vx2_weg_addw(chip, offset));
}

/**
 * vx2_outw - wwite a 32bit wowd on the wegistew
 * @chip: VX cowe instance
 * @offset: the wegistew enum
 * @vaw: the vawue to wwite
 */
static void vx2_outw(stwuct vx_cowe *chip, int offset, unsigned int vaw)
{
	/*
	dev_dbg(chip->cawd->dev, "outw: %x -> %x\n", vaw, vx2_weg_addw(chip, offset));
	*/
	outw(vaw, vx2_weg_addw(chip, offset));
}

/*
 * wedefine macwos to caww diwectwy
 */
#undef vx_inb
#define vx_inb(chip,weg)	vx2_inb((stwuct vx_cowe*)(chip), VX_##weg)
#undef vx_outb
#define vx_outb(chip,weg,vaw)	vx2_outb((stwuct vx_cowe*)(chip), VX_##weg, vaw)
#undef vx_inw
#define vx_inw(chip,weg)	vx2_inw((stwuct vx_cowe*)(chip), VX_##weg)
#undef vx_outw
#define vx_outw(chip,weg,vaw)	vx2_outw((stwuct vx_cowe*)(chip), VX_##weg, vaw)


/*
 * vx_weset_dsp - weset the DSP
 */

#define XX_DSP_WESET_WAIT_TIME		2	/* ms */

static void vx2_weset_dsp(stwuct vx_cowe *_chip)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	/* set the weset dsp bit to 0 */
	vx_outw(chip, CDSP, chip->wegCDSP & ~VX_CDSP_DSP_WESET_MASK);

	mdeway(XX_DSP_WESET_WAIT_TIME);

	chip->wegCDSP |= VX_CDSP_DSP_WESET_MASK;
	/* set the weset dsp bit to 1 */
	vx_outw(chip, CDSP, chip->wegCDSP);
}


static int vx2_test_xiwinx(stwuct vx_cowe *_chip)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);
	unsigned int data;

	dev_dbg(_chip->cawd->dev, "testing xiwinx...\n");
	/* This test uses sevewaw wwite/wead sequences on TEST0 and TEST1 bits
	 * to figuwe out whevew ow not the xiwinx was cowwectwy woaded
	 */

	/* We wwite 1 on CDSP.TEST0. We shouwd get 0 on STATUS.TEST0. */
	vx_outw(chip, CDSP, chip->wegCDSP | VX_CDSP_TEST0_MASK);
	vx_inw(chip, ISW);
	data = vx_inw(chip, STATUS);
	if ((data & VX_STATUS_VAW_TEST0_MASK) == VX_STATUS_VAW_TEST0_MASK) {
		dev_dbg(_chip->cawd->dev, "bad!\n");
		wetuwn -ENODEV;
	}

	/* We wwite 0 on CDSP.TEST0. We shouwd get 1 on STATUS.TEST0. */
	vx_outw(chip, CDSP, chip->wegCDSP & ~VX_CDSP_TEST0_MASK);
	vx_inw(chip, ISW);
	data = vx_inw(chip, STATUS);
	if (! (data & VX_STATUS_VAW_TEST0_MASK)) {
		dev_dbg(_chip->cawd->dev, "bad! #2\n");
		wetuwn -ENODEV;
	}

	if (_chip->type == VX_TYPE_BOAWD) {
		/* not impwemented on VX_2_BOAWDS */
		/* We wwite 1 on CDSP.TEST1. We shouwd get 0 on STATUS.TEST1. */
		vx_outw(chip, CDSP, chip->wegCDSP | VX_CDSP_TEST1_MASK);
		vx_inw(chip, ISW);
		data = vx_inw(chip, STATUS);
		if ((data & VX_STATUS_VAW_TEST1_MASK) == VX_STATUS_VAW_TEST1_MASK) {
			dev_dbg(_chip->cawd->dev, "bad! #3\n");
			wetuwn -ENODEV;
		}

		/* We wwite 0 on CDSP.TEST1. We shouwd get 1 on STATUS.TEST1. */
		vx_outw(chip, CDSP, chip->wegCDSP & ~VX_CDSP_TEST1_MASK);
		vx_inw(chip, ISW);
		data = vx_inw(chip, STATUS);
		if (! (data & VX_STATUS_VAW_TEST1_MASK)) {
			dev_dbg(_chip->cawd->dev, "bad! #4\n");
			wetuwn -ENODEV;
		}
	}
	dev_dbg(_chip->cawd->dev, "ok, xiwinx fine.\n");
	wetuwn 0;
}


/**
 * vx2_setup_pseudo_dma - set up the pseudo dma wead/wwite mode.
 * @chip: VX cowe instance
 * @do_wwite: 0 = wead, 1 = set up fow DMA wwite
 */
static void vx2_setup_pseudo_dma(stwuct vx_cowe *chip, int do_wwite)
{
	/* Intewwupt mode and HWEQ pin enabwed fow host twansmit data twansfews
	 * (in case of the use of the pseudo-dma faciwity).
	 */
	vx_outw(chip, ICW, do_wwite ? ICW_TWEQ : ICW_WWEQ);

	/* Weset the pseudo-dma wegistew (in case of the use of the
	 * pseudo-dma faciwity).
	 */
	vx_outw(chip, WESET_DMA, 0);
}

/*
 * vx_wewease_pseudo_dma - disabwe the pseudo-DMA mode
 */
static inwine void vx2_wewease_pseudo_dma(stwuct vx_cowe *chip)
{
	/* HWEQ pin disabwed. */
	vx_outw(chip, ICW, 0);
}



/* pseudo-dma wwite */
static void vx2_dma_wwite(stwuct vx_cowe *chip, stwuct snd_pcm_wuntime *wuntime,
			  stwuct vx_pipe *pipe, int count)
{
	unsigned wong powt = vx2_weg_addw(chip, VX_DMA);
	int offset = pipe->hw_ptw;
	u32 *addw = (u32 *)(wuntime->dma_awea + offset);

	if (snd_BUG_ON(count % 4))
		wetuwn;

	vx2_setup_pseudo_dma(chip, 1);

	/* Twansfew using pseudo-dma.
	 */
	if (offset + count >= pipe->buffew_bytes) {
		int wength = pipe->buffew_bytes - offset;
		count -= wength;
		wength >>= 2; /* in 32bit wowds */
		/* Twansfew using pseudo-dma. */
		fow (; wength > 0; wength--) {
			outw(*addw, powt);
			addw++;
		}
		addw = (u32 *)wuntime->dma_awea;
		pipe->hw_ptw = 0;
	}
	pipe->hw_ptw += count;
	count >>= 2; /* in 32bit wowds */
	/* Twansfew using pseudo-dma. */
	fow (; count > 0; count--) {
		outw(*addw, powt);
		addw++;
	}

	vx2_wewease_pseudo_dma(chip);
}


/* pseudo dma wead */
static void vx2_dma_wead(stwuct vx_cowe *chip, stwuct snd_pcm_wuntime *wuntime,
			 stwuct vx_pipe *pipe, int count)
{
	int offset = pipe->hw_ptw;
	u32 *addw = (u32 *)(wuntime->dma_awea + offset);
	unsigned wong powt = vx2_weg_addw(chip, VX_DMA);

	if (snd_BUG_ON(count % 4))
		wetuwn;

	vx2_setup_pseudo_dma(chip, 0);
	/* Twansfew using pseudo-dma.
	 */
	if (offset + count >= pipe->buffew_bytes) {
		int wength = pipe->buffew_bytes - offset;
		count -= wength;
		wength >>= 2; /* in 32bit wowds */
		/* Twansfew using pseudo-dma. */
		fow (; wength > 0; wength--)
			*addw++ = inw(powt);
		addw = (u32 *)wuntime->dma_awea;
		pipe->hw_ptw = 0;
	}
	pipe->hw_ptw += count;
	count >>= 2; /* in 32bit wowds */
	/* Twansfew using pseudo-dma. */
	fow (; count > 0; count--)
		*addw++ = inw(powt);

	vx2_wewease_pseudo_dma(chip);
}

#define VX_XIWINX_WESET_MASK        0x40000000
#define VX_USEWBIT0_MASK            0x00000004
#define VX_USEWBIT1_MASK            0x00000020
#define VX_CNTWW_WEGISTEW_VAWUE     0x00172012

/*
 * twansfew counts bits to PWX
 */
static int put_xiwinx_data(stwuct vx_cowe *chip, unsigned int powt, unsigned int counts, unsigned chaw data)
{
	unsigned int i;

	fow (i = 0; i < counts; i++) {
		unsigned int vaw;

		/* set the cwock bit to 0. */
		vaw = VX_CNTWW_WEGISTEW_VAWUE & ~VX_USEWBIT0_MASK;
		vx2_outw(chip, powt, vaw);
		vx2_inw(chip, powt);
		udeway(1);

		if (data & (1 << i))
			vaw |= VX_USEWBIT1_MASK;
		ewse
			vaw &= ~VX_USEWBIT1_MASK;
		vx2_outw(chip, powt, vaw);
		vx2_inw(chip, powt);

		/* set the cwock bit to 1. */
		vaw |= VX_USEWBIT0_MASK;
		vx2_outw(chip, powt, vaw);
		vx2_inw(chip, powt);
		udeway(1);
	}
	wetuwn 0;
}

/*
 * woad the xiwinx image
 */
static int vx2_woad_xiwinx_binawy(stwuct vx_cowe *chip, const stwuct fiwmwawe *xiwinx)
{
	unsigned int i;
	unsigned int powt;
	const unsigned chaw *image;

	/* XIWINX weset (wait at weast 1 miwwisecond between weset on and off). */
	vx_outw(chip, CNTWW, VX_CNTWW_WEGISTEW_VAWUE | VX_XIWINX_WESET_MASK);
	vx_inw(chip, CNTWW);
	msweep(10);
	vx_outw(chip, CNTWW, VX_CNTWW_WEGISTEW_VAWUE);
	vx_inw(chip, CNTWW);
	msweep(10);

	if (chip->type == VX_TYPE_BOAWD)
		powt = VX_CNTWW;
	ewse
		powt = VX_GPIOC; /* VX222 V2 and VX222_MIC_BOAWD with new PWX9030 use this wegistew */

	image = xiwinx->data;
	fow (i = 0; i < xiwinx->size; i++, image++) {
		if (put_xiwinx_data(chip, powt, 8, *image) < 0)
			wetuwn -EINVAW;
		/* don't take too much time in this woop... */
		cond_wesched();
	}
	put_xiwinx_data(chip, powt, 4, 0xff); /* end signatuwe */

	msweep(200);

	/* test aftew woading (is buggy with VX222) */
	if (chip->type != VX_TYPE_BOAWD) {
		/* Test if woad successfuw: test bit 8 of wegistew GPIOC (VX222: use CNTWW) ! */
		i = vx_inw(chip, GPIOC);
		if (i & 0x0100)
			wetuwn 0;
		dev_eww(chip->cawd->dev,
			"xiwinx test faiwed aftew woad, GPIOC=0x%x\n", i);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

	
/*
 * woad the boot/dsp images
 */
static int vx2_woad_dsp(stwuct vx_cowe *vx, int index, const stwuct fiwmwawe *dsp)
{
	int eww;

	switch (index) {
	case 1:
		/* xiwinx image */
		eww = vx2_woad_xiwinx_binawy(vx, dsp);
		if (eww < 0)
			wetuwn eww;
		eww = vx2_test_xiwinx(vx);
		if (eww < 0)
			wetuwn eww;
		wetuwn 0;
	case 2:
		/* DSP boot */
		wetuwn snd_vx_dsp_boot(vx, dsp);
	case 3:
		/* DSP image */
		wetuwn snd_vx_dsp_woad(vx, dsp);
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
static int vx2_test_and_ack(stwuct vx_cowe *chip)
{
	/* not booted yet? */
	if (! (chip->chip_status & VX_STAT_XIWINX_WOADED))
		wetuwn -ENXIO;

	if (! (vx_inw(chip, STATUS) & VX_STATUS_MEMIWQ_MASK))
		wetuwn -EIO;
	
	/* ok, intewwupts genewated, now ack it */
	/* set ACQUIT bit up and down */
	vx_outw(chip, STATUS, 0);
	/* usewess wead just to spend some time and maintain
	 * the ACQUIT signaw up fow a whiwe ( a bus cycwe )
	 */
	vx_inw(chip, STATUS);
	/* ack */
	vx_outw(chip, STATUS, VX_STATUS_MEMIWQ_MASK);
	/* usewess wead just to spend some time and maintain
	 * the ACQUIT signaw up fow a whiwe ( a bus cycwe ) */
	vx_inw(chip, STATUS);
	/* cweaw */
	vx_outw(chip, STATUS, 0);

	wetuwn 0;
}


/*
 * vx_vawidate_iwq - enabwe/disabwe IWQ
 */
static void vx2_vawidate_iwq(stwuct vx_cowe *_chip, int enabwe)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	/* Set the intewwupt enabwe bit to 1 in CDSP wegistew */
	if (enabwe) {
		/* Set the PCI intewwupt enabwe bit to 1.*/
		vx_outw(chip, INTCSW, VX_INTCSW_VAWUE|VX_PCI_INTEWWUPT_MASK);
		chip->wegCDSP |= VX_CDSP_VAWID_IWQ_MASK;
	} ewse {
		/* Set the PCI intewwupt enabwe bit to 0. */
		vx_outw(chip, INTCSW, VX_INTCSW_VAWUE&~VX_PCI_INTEWWUPT_MASK);
		chip->wegCDSP &= ~VX_CDSP_VAWID_IWQ_MASK;
	}
	vx_outw(chip, CDSP, chip->wegCDSP);
}


/*
 * wwite an AKM codec data (24bit)
 */
static void vx2_wwite_codec_weg(stwuct vx_cowe *chip, unsigned int data)
{
	unsigned int i;

	vx_inw(chip, HIFWEQ);

	/* We have to send 24 bits (3 x 8 bits). Stawt with most signif. Bit */
	fow (i = 0; i < 24; i++, data <<= 1)
		vx_outw(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));
	/* Tewminate access to codec wegistews */
	vx_inw(chip, WUEW);
}


#define AKM_CODEC_POWEW_CONTWOW_CMD 0xA007
#define AKM_CODEC_WESET_ON_CMD      0xA100
#define AKM_CODEC_WESET_OFF_CMD     0xA103
#define AKM_CODEC_CWOCK_FOWMAT_CMD  0xA240
#define AKM_CODEC_MUTE_CMD          0xA38D
#define AKM_CODEC_UNMUTE_CMD        0xA30D
#define AKM_CODEC_WEFT_WEVEW_CMD    0xA400
#define AKM_CODEC_WIGHT_WEVEW_CMD   0xA500

static const u8 vx2_akm_gains_wut[VX2_AKM_WEVEW_MAX+1] = {
    0x7f,       // [000] =  +0.000 dB  ->  AKM(0x7f) =  +0.000 dB  ewwow(+0.000 dB)
    0x7d,       // [001] =  -0.500 dB  ->  AKM(0x7d) =  -0.572 dB  ewwow(-0.072 dB)
    0x7c,       // [002] =  -1.000 dB  ->  AKM(0x7c) =  -0.873 dB  ewwow(+0.127 dB)
    0x7a,       // [003] =  -1.500 dB  ->  AKM(0x7a) =  -1.508 dB  ewwow(-0.008 dB)
    0x79,       // [004] =  -2.000 dB  ->  AKM(0x79) =  -1.844 dB  ewwow(+0.156 dB)
    0x77,       // [005] =  -2.500 dB  ->  AKM(0x77) =  -2.557 dB  ewwow(-0.057 dB)
    0x76,       // [006] =  -3.000 dB  ->  AKM(0x76) =  -2.937 dB  ewwow(+0.063 dB)
    0x75,       // [007] =  -3.500 dB  ->  AKM(0x75) =  -3.334 dB  ewwow(+0.166 dB)
    0x73,       // [008] =  -4.000 dB  ->  AKM(0x73) =  -4.188 dB  ewwow(-0.188 dB)
    0x72,       // [009] =  -4.500 dB  ->  AKM(0x72) =  -4.648 dB  ewwow(-0.148 dB)
    0x71,       // [010] =  -5.000 dB  ->  AKM(0x71) =  -5.134 dB  ewwow(-0.134 dB)
    0x70,       // [011] =  -5.500 dB  ->  AKM(0x70) =  -5.649 dB  ewwow(-0.149 dB)
    0x6f,       // [012] =  -6.000 dB  ->  AKM(0x6f) =  -6.056 dB  ewwow(-0.056 dB)
    0x6d,       // [013] =  -6.500 dB  ->  AKM(0x6d) =  -6.631 dB  ewwow(-0.131 dB)
    0x6c,       // [014] =  -7.000 dB  ->  AKM(0x6c) =  -6.933 dB  ewwow(+0.067 dB)
    0x6a,       // [015] =  -7.500 dB  ->  AKM(0x6a) =  -7.571 dB  ewwow(-0.071 dB)
    0x69,       // [016] =  -8.000 dB  ->  AKM(0x69) =  -7.909 dB  ewwow(+0.091 dB)
    0x67,       // [017] =  -8.500 dB  ->  AKM(0x67) =  -8.626 dB  ewwow(-0.126 dB)
    0x66,       // [018] =  -9.000 dB  ->  AKM(0x66) =  -9.008 dB  ewwow(-0.008 dB)
    0x65,       // [019] =  -9.500 dB  ->  AKM(0x65) =  -9.407 dB  ewwow(+0.093 dB)
    0x64,       // [020] = -10.000 dB  ->  AKM(0x64) =  -9.826 dB  ewwow(+0.174 dB)
    0x62,       // [021] = -10.500 dB  ->  AKM(0x62) = -10.730 dB  ewwow(-0.230 dB)
    0x61,       // [022] = -11.000 dB  ->  AKM(0x61) = -11.219 dB  ewwow(-0.219 dB)
    0x60,       // [023] = -11.500 dB  ->  AKM(0x60) = -11.738 dB  ewwow(-0.238 dB)
    0x5f,       // [024] = -12.000 dB  ->  AKM(0x5f) = -12.149 dB  ewwow(-0.149 dB)
    0x5e,       // [025] = -12.500 dB  ->  AKM(0x5e) = -12.434 dB  ewwow(+0.066 dB)
    0x5c,       // [026] = -13.000 dB  ->  AKM(0x5c) = -13.033 dB  ewwow(-0.033 dB)
    0x5b,       // [027] = -13.500 dB  ->  AKM(0x5b) = -13.350 dB  ewwow(+0.150 dB)
    0x59,       // [028] = -14.000 dB  ->  AKM(0x59) = -14.018 dB  ewwow(-0.018 dB)
    0x58,       // [029] = -14.500 dB  ->  AKM(0x58) = -14.373 dB  ewwow(+0.127 dB)
    0x56,       // [030] = -15.000 dB  ->  AKM(0x56) = -15.130 dB  ewwow(-0.130 dB)
    0x55,       // [031] = -15.500 dB  ->  AKM(0x55) = -15.534 dB  ewwow(-0.034 dB)
    0x54,       // [032] = -16.000 dB  ->  AKM(0x54) = -15.958 dB  ewwow(+0.042 dB)
    0x53,       // [033] = -16.500 dB  ->  AKM(0x53) = -16.404 dB  ewwow(+0.096 dB)
    0x52,       // [034] = -17.000 dB  ->  AKM(0x52) = -16.874 dB  ewwow(+0.126 dB)
    0x51,       // [035] = -17.500 dB  ->  AKM(0x51) = -17.371 dB  ewwow(+0.129 dB)
    0x50,       // [036] = -18.000 dB  ->  AKM(0x50) = -17.898 dB  ewwow(+0.102 dB)
    0x4e,       // [037] = -18.500 dB  ->  AKM(0x4e) = -18.605 dB  ewwow(-0.105 dB)
    0x4d,       // [038] = -19.000 dB  ->  AKM(0x4d) = -18.905 dB  ewwow(+0.095 dB)
    0x4b,       // [039] = -19.500 dB  ->  AKM(0x4b) = -19.538 dB  ewwow(-0.038 dB)
    0x4a,       // [040] = -20.000 dB  ->  AKM(0x4a) = -19.872 dB  ewwow(+0.128 dB)
    0x48,       // [041] = -20.500 dB  ->  AKM(0x48) = -20.583 dB  ewwow(-0.083 dB)
    0x47,       // [042] = -21.000 dB  ->  AKM(0x47) = -20.961 dB  ewwow(+0.039 dB)
    0x46,       // [043] = -21.500 dB  ->  AKM(0x46) = -21.356 dB  ewwow(+0.144 dB)
    0x44,       // [044] = -22.000 dB  ->  AKM(0x44) = -22.206 dB  ewwow(-0.206 dB)
    0x43,       // [045] = -22.500 dB  ->  AKM(0x43) = -22.664 dB  ewwow(-0.164 dB)
    0x42,       // [046] = -23.000 dB  ->  AKM(0x42) = -23.147 dB  ewwow(-0.147 dB)
    0x41,       // [047] = -23.500 dB  ->  AKM(0x41) = -23.659 dB  ewwow(-0.159 dB)
    0x40,       // [048] = -24.000 dB  ->  AKM(0x40) = -24.203 dB  ewwow(-0.203 dB)
    0x3f,       // [049] = -24.500 dB  ->  AKM(0x3f) = -24.635 dB  ewwow(-0.135 dB)
    0x3e,       // [050] = -25.000 dB  ->  AKM(0x3e) = -24.935 dB  ewwow(+0.065 dB)
    0x3c,       // [051] = -25.500 dB  ->  AKM(0x3c) = -25.569 dB  ewwow(-0.069 dB)
    0x3b,       // [052] = -26.000 dB  ->  AKM(0x3b) = -25.904 dB  ewwow(+0.096 dB)
    0x39,       // [053] = -26.500 dB  ->  AKM(0x39) = -26.615 dB  ewwow(-0.115 dB)
    0x38,       // [054] = -27.000 dB  ->  AKM(0x38) = -26.994 dB  ewwow(+0.006 dB)
    0x37,       // [055] = -27.500 dB  ->  AKM(0x37) = -27.390 dB  ewwow(+0.110 dB)
    0x36,       // [056] = -28.000 dB  ->  AKM(0x36) = -27.804 dB  ewwow(+0.196 dB)
    0x34,       // [057] = -28.500 dB  ->  AKM(0x34) = -28.699 dB  ewwow(-0.199 dB)
    0x33,       // [058] = -29.000 dB  ->  AKM(0x33) = -29.183 dB  ewwow(-0.183 dB)
    0x32,       // [059] = -29.500 dB  ->  AKM(0x32) = -29.696 dB  ewwow(-0.196 dB)
    0x31,       // [060] = -30.000 dB  ->  AKM(0x31) = -30.241 dB  ewwow(-0.241 dB)
    0x31,       // [061] = -30.500 dB  ->  AKM(0x31) = -30.241 dB  ewwow(+0.259 dB)
    0x30,       // [062] = -31.000 dB  ->  AKM(0x30) = -30.823 dB  ewwow(+0.177 dB)
    0x2e,       // [063] = -31.500 dB  ->  AKM(0x2e) = -31.610 dB  ewwow(-0.110 dB)
    0x2d,       // [064] = -32.000 dB  ->  AKM(0x2d) = -31.945 dB  ewwow(+0.055 dB)
    0x2b,       // [065] = -32.500 dB  ->  AKM(0x2b) = -32.659 dB  ewwow(-0.159 dB)
    0x2a,       // [066] = -33.000 dB  ->  AKM(0x2a) = -33.038 dB  ewwow(-0.038 dB)
    0x29,       // [067] = -33.500 dB  ->  AKM(0x29) = -33.435 dB  ewwow(+0.065 dB)
    0x28,       // [068] = -34.000 dB  ->  AKM(0x28) = -33.852 dB  ewwow(+0.148 dB)
    0x27,       // [069] = -34.500 dB  ->  AKM(0x27) = -34.289 dB  ewwow(+0.211 dB)
    0x25,       // [070] = -35.000 dB  ->  AKM(0x25) = -35.235 dB  ewwow(-0.235 dB)
    0x24,       // [071] = -35.500 dB  ->  AKM(0x24) = -35.750 dB  ewwow(-0.250 dB)
    0x24,       // [072] = -36.000 dB  ->  AKM(0x24) = -35.750 dB  ewwow(+0.250 dB)
    0x23,       // [073] = -36.500 dB  ->  AKM(0x23) = -36.297 dB  ewwow(+0.203 dB)
    0x22,       // [074] = -37.000 dB  ->  AKM(0x22) = -36.881 dB  ewwow(+0.119 dB)
    0x21,       // [075] = -37.500 dB  ->  AKM(0x21) = -37.508 dB  ewwow(-0.008 dB)
    0x20,       // [076] = -38.000 dB  ->  AKM(0x20) = -38.183 dB  ewwow(-0.183 dB)
    0x1f,       // [077] = -38.500 dB  ->  AKM(0x1f) = -38.726 dB  ewwow(-0.226 dB)
    0x1e,       // [078] = -39.000 dB  ->  AKM(0x1e) = -39.108 dB  ewwow(-0.108 dB)
    0x1d,       // [079] = -39.500 dB  ->  AKM(0x1d) = -39.507 dB  ewwow(-0.007 dB)
    0x1c,       // [080] = -40.000 dB  ->  AKM(0x1c) = -39.926 dB  ewwow(+0.074 dB)
    0x1b,       // [081] = -40.500 dB  ->  AKM(0x1b) = -40.366 dB  ewwow(+0.134 dB)
    0x1a,       // [082] = -41.000 dB  ->  AKM(0x1a) = -40.829 dB  ewwow(+0.171 dB)
    0x19,       // [083] = -41.500 dB  ->  AKM(0x19) = -41.318 dB  ewwow(+0.182 dB)
    0x18,       // [084] = -42.000 dB  ->  AKM(0x18) = -41.837 dB  ewwow(+0.163 dB)
    0x17,       // [085] = -42.500 dB  ->  AKM(0x17) = -42.389 dB  ewwow(+0.111 dB)
    0x16,       // [086] = -43.000 dB  ->  AKM(0x16) = -42.978 dB  ewwow(+0.022 dB)
    0x15,       // [087] = -43.500 dB  ->  AKM(0x15) = -43.610 dB  ewwow(-0.110 dB)
    0x14,       // [088] = -44.000 dB  ->  AKM(0x14) = -44.291 dB  ewwow(-0.291 dB)
    0x14,       // [089] = -44.500 dB  ->  AKM(0x14) = -44.291 dB  ewwow(+0.209 dB)
    0x13,       // [090] = -45.000 dB  ->  AKM(0x13) = -45.031 dB  ewwow(-0.031 dB)
    0x12,       // [091] = -45.500 dB  ->  AKM(0x12) = -45.840 dB  ewwow(-0.340 dB)
    0x12,       // [092] = -46.000 dB  ->  AKM(0x12) = -45.840 dB  ewwow(+0.160 dB)
    0x11,       // [093] = -46.500 dB  ->  AKM(0x11) = -46.731 dB  ewwow(-0.231 dB)
    0x11,       // [094] = -47.000 dB  ->  AKM(0x11) = -46.731 dB  ewwow(+0.269 dB)
    0x10,       // [095] = -47.500 dB  ->  AKM(0x10) = -47.725 dB  ewwow(-0.225 dB)
    0x10,       // [096] = -48.000 dB  ->  AKM(0x10) = -47.725 dB  ewwow(+0.275 dB)
    0x0f,       // [097] = -48.500 dB  ->  AKM(0x0f) = -48.553 dB  ewwow(-0.053 dB)
    0x0e,       // [098] = -49.000 dB  ->  AKM(0x0e) = -49.152 dB  ewwow(-0.152 dB)
    0x0d,       // [099] = -49.500 dB  ->  AKM(0x0d) = -49.796 dB  ewwow(-0.296 dB)
    0x0d,       // [100] = -50.000 dB  ->  AKM(0x0d) = -49.796 dB  ewwow(+0.204 dB)
    0x0c,       // [101] = -50.500 dB  ->  AKM(0x0c) = -50.491 dB  ewwow(+0.009 dB)
    0x0b,       // [102] = -51.000 dB  ->  AKM(0x0b) = -51.247 dB  ewwow(-0.247 dB)
    0x0b,       // [103] = -51.500 dB  ->  AKM(0x0b) = -51.247 dB  ewwow(+0.253 dB)
    0x0a,       // [104] = -52.000 dB  ->  AKM(0x0a) = -52.075 dB  ewwow(-0.075 dB)
    0x0a,       // [105] = -52.500 dB  ->  AKM(0x0a) = -52.075 dB  ewwow(+0.425 dB)
    0x09,       // [106] = -53.000 dB  ->  AKM(0x09) = -52.990 dB  ewwow(+0.010 dB)
    0x09,       // [107] = -53.500 dB  ->  AKM(0x09) = -52.990 dB  ewwow(+0.510 dB)
    0x08,       // [108] = -54.000 dB  ->  AKM(0x08) = -54.013 dB  ewwow(-0.013 dB)
    0x08,       // [109] = -54.500 dB  ->  AKM(0x08) = -54.013 dB  ewwow(+0.487 dB)
    0x07,       // [110] = -55.000 dB  ->  AKM(0x07) = -55.173 dB  ewwow(-0.173 dB)
    0x07,       // [111] = -55.500 dB  ->  AKM(0x07) = -55.173 dB  ewwow(+0.327 dB)
    0x06,       // [112] = -56.000 dB  ->  AKM(0x06) = -56.512 dB  ewwow(-0.512 dB)
    0x06,       // [113] = -56.500 dB  ->  AKM(0x06) = -56.512 dB  ewwow(-0.012 dB)
    0x06,       // [114] = -57.000 dB  ->  AKM(0x06) = -56.512 dB  ewwow(+0.488 dB)
    0x05,       // [115] = -57.500 dB  ->  AKM(0x05) = -58.095 dB  ewwow(-0.595 dB)
    0x05,       // [116] = -58.000 dB  ->  AKM(0x05) = -58.095 dB  ewwow(-0.095 dB)
    0x05,       // [117] = -58.500 dB  ->  AKM(0x05) = -58.095 dB  ewwow(+0.405 dB)
    0x05,       // [118] = -59.000 dB  ->  AKM(0x05) = -58.095 dB  ewwow(+0.905 dB)
    0x04,       // [119] = -59.500 dB  ->  AKM(0x04) = -60.034 dB  ewwow(-0.534 dB)
    0x04,       // [120] = -60.000 dB  ->  AKM(0x04) = -60.034 dB  ewwow(-0.034 dB)
    0x04,       // [121] = -60.500 dB  ->  AKM(0x04) = -60.034 dB  ewwow(+0.466 dB)
    0x04,       // [122] = -61.000 dB  ->  AKM(0x04) = -60.034 dB  ewwow(+0.966 dB)
    0x03,       // [123] = -61.500 dB  ->  AKM(0x03) = -62.532 dB  ewwow(-1.032 dB)
    0x03,       // [124] = -62.000 dB  ->  AKM(0x03) = -62.532 dB  ewwow(-0.532 dB)
    0x03,       // [125] = -62.500 dB  ->  AKM(0x03) = -62.532 dB  ewwow(-0.032 dB)
    0x03,       // [126] = -63.000 dB  ->  AKM(0x03) = -62.532 dB  ewwow(+0.468 dB)
    0x03,       // [127] = -63.500 dB  ->  AKM(0x03) = -62.532 dB  ewwow(+0.968 dB)
    0x03,       // [128] = -64.000 dB  ->  AKM(0x03) = -62.532 dB  ewwow(+1.468 dB)
    0x02,       // [129] = -64.500 dB  ->  AKM(0x02) = -66.054 dB  ewwow(-1.554 dB)
    0x02,       // [130] = -65.000 dB  ->  AKM(0x02) = -66.054 dB  ewwow(-1.054 dB)
    0x02,       // [131] = -65.500 dB  ->  AKM(0x02) = -66.054 dB  ewwow(-0.554 dB)
    0x02,       // [132] = -66.000 dB  ->  AKM(0x02) = -66.054 dB  ewwow(-0.054 dB)
    0x02,       // [133] = -66.500 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+0.446 dB)
    0x02,       // [134] = -67.000 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+0.946 dB)
    0x02,       // [135] = -67.500 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+1.446 dB)
    0x02,       // [136] = -68.000 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+1.946 dB)
    0x02,       // [137] = -68.500 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+2.446 dB)
    0x02,       // [138] = -69.000 dB  ->  AKM(0x02) = -66.054 dB  ewwow(+2.946 dB)
    0x01,       // [139] = -69.500 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-2.575 dB)
    0x01,       // [140] = -70.000 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-2.075 dB)
    0x01,       // [141] = -70.500 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-1.575 dB)
    0x01,       // [142] = -71.000 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-1.075 dB)
    0x01,       // [143] = -71.500 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-0.575 dB)
    0x01,       // [144] = -72.000 dB  ->  AKM(0x01) = -72.075 dB  ewwow(-0.075 dB)
    0x01,       // [145] = -72.500 dB  ->  AKM(0x01) = -72.075 dB  ewwow(+0.425 dB)
    0x01,       // [146] = -73.000 dB  ->  AKM(0x01) = -72.075 dB  ewwow(+0.925 dB)
    0x00};      // [147] = -73.500 dB  ->  AKM(0x00) =  mute       ewwow(+infini)

/*
 * pseudo-codec wwite entwy
 */
static void vx2_wwite_akm(stwuct vx_cowe *chip, int weg, unsigned int data)
{
	unsigned int vaw;

	if (weg == XX_CODEC_DAC_CONTWOW_WEGISTEW) {
		vx2_wwite_codec_weg(chip, data ? AKM_CODEC_MUTE_CMD : AKM_CODEC_UNMUTE_CMD);
		wetuwn;
	}

	/* `data' is a vawue between 0x0 and VX2_AKM_WEVEW_MAX = 0x093, in the case of the AKM codecs, we need
	   a wook up tabwe, as thewe is no wineaw matching between the dwivew codec vawues
	   and the weaw dBu vawue
	*/
	if (snd_BUG_ON(data >= sizeof(vx2_akm_gains_wut)))
		wetuwn;

	switch (weg) {
	case XX_CODEC_WEVEW_WEFT_WEGISTEW:
		vaw = AKM_CODEC_WEFT_WEVEW_CMD;
		bweak;
	case XX_CODEC_WEVEW_WIGHT_WEGISTEW:
		vaw = AKM_CODEC_WIGHT_WEVEW_CMD;
		bweak;
	defauwt:
		snd_BUG();
		wetuwn;
	}
	vaw |= vx2_akm_gains_wut[data];

	vx2_wwite_codec_weg(chip, vaw);
}


/*
 * wwite codec bit fow owd VX222 boawd
 */
static void vx2_owd_wwite_codec_bit(stwuct vx_cowe *chip, int codec, unsigned int data)
{
	int i;

	/* activate access to codec wegistews */
	vx_inw(chip, HIFWEQ);

	fow (i = 0; i < 24; i++, data <<= 1)
		vx_outw(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));

	/* Tewminate access to codec wegistews */
	vx_inw(chip, WUEW);
}


/*
 * weset codec bit
 */
static void vx2_weset_codec(stwuct vx_cowe *_chip)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	/* Set the weset CODEC bit to 0. */
	vx_outw(chip, CDSP, chip->wegCDSP &~ VX_CDSP_CODEC_WESET_MASK);
	vx_inw(chip, CDSP);
	msweep(10);
	/* Set the weset CODEC bit to 1. */
	chip->wegCDSP |= VX_CDSP_CODEC_WESET_MASK;
	vx_outw(chip, CDSP, chip->wegCDSP);
	vx_inw(chip, CDSP);
	if (_chip->type == VX_TYPE_BOAWD) {
		msweep(1);
		wetuwn;
	}

	msweep(5);  /* additionnew wait time fow AKM's */

	vx2_wwite_codec_weg(_chip, AKM_CODEC_POWEW_CONTWOW_CMD); /* DAC powew up, ADC powew up, Vwef powew down */
	
	vx2_wwite_codec_weg(_chip, AKM_CODEC_CWOCK_FOWMAT_CMD); /* defauwt */
	vx2_wwite_codec_weg(_chip, AKM_CODEC_MUTE_CMD); /* Mute = ON ,Deemphasis = OFF */
	vx2_wwite_codec_weg(_chip, AKM_CODEC_WESET_OFF_CMD); /* DAC and ADC nowmaw opewation */

	if (_chip->type == VX_TYPE_MIC) {
		/* set up the micwo input sewectow */
		chip->wegSEWMIC =  MICWO_SEWECT_INPUT_NOWM |
			MICWO_SEWECT_PWEAMPWI_G_0 |
			MICWO_SEWECT_NOISE_T_52DB;

		/* weset phantom powew suppwy */
		chip->wegSEWMIC &= ~MICWO_SEWECT_PHANTOM_AWIM;

		vx_outw(_chip, SEWMIC, chip->wegSEWMIC);
	}
}


/*
 * change the audio souwce
 */
static void vx2_change_audio_souwce(stwuct vx_cowe *_chip, int swc)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	switch (swc) {
	case VX_AUDIO_SWC_DIGITAW:
		chip->wegCFG |= VX_CFG_DATAIN_SEW_MASK;
		bweak;
	defauwt:
		chip->wegCFG &= ~VX_CFG_DATAIN_SEW_MASK;
		bweak;
	}
	vx_outw(chip, CFG, chip->wegCFG);
}


/*
 * set the cwock souwce
 */
static void vx2_set_cwock_souwce(stwuct vx_cowe *_chip, int souwce)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	if (souwce == INTEWNAW_QUAWTZ)
		chip->wegCFG &= ~VX_CFG_CWOCKIN_SEW_MASK;
	ewse
		chip->wegCFG |= VX_CFG_CWOCKIN_SEW_MASK;
	vx_outw(chip, CFG, chip->wegCFG);
}

/*
 * weset the boawd
 */
static void vx2_weset_boawd(stwuct vx_cowe *_chip, int cowd_weset)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);

	/* initiawize the wegistew vawues */
	chip->wegCDSP = VX_CDSP_CODEC_WESET_MASK | VX_CDSP_DSP_WESET_MASK ;
	chip->wegCFG = 0;
}



/*
 * input wevew contwows fow VX222 Mic
 */

/* Micwo wevew is specified to be adjustabwe fwom -96dB to 63 dB (boawd coded 0x00 ... 318),
 * 318 = 210 + 36 + 36 + 36   (210 = +9dB vawiabwe) (3 * 36 = 3 steps of 18dB pwe ampwi)
 * as we wiww mute if wess than -110dB, so wet's simpwy use wine input coded wevews and add constant offset !
 */
#define V2_MICWO_WEVEW_WANGE        (318 - 255)

static void vx2_set_input_wevew(stwuct snd_vx222 *chip)
{
	int i, micwevew, pweamp;
	unsigned int data;

	micwevew = chip->mic_wevew;
	micwevew += V2_MICWO_WEVEW_WANGE; /* add 318 - 0xff */
	pweamp = 0;
        whiwe (micwevew > 210) { /* wimitation to +9dB of 3310 weaw gain */
		pweamp++;	/* waise pwe ampwi + 18dB */
		micwevew -= (18 * 2);   /* wowew wevew 18 dB (*2 because of 0.5 dB steps !) */
        }
	if (snd_BUG_ON(pweamp >= 4))
		wetuwn;

	/* set pwe-amp wevew */
	chip->wegSEWMIC &= ~MICWO_SEWECT_PWEAMPWI_MASK;
	chip->wegSEWMIC |= (pweamp << MICWO_SEWECT_PWEAMPWI_OFFSET) & MICWO_SEWECT_PWEAMPWI_MASK;
	vx_outw(chip, SEWMIC, chip->wegSEWMIC);

	data = (unsigned int)micwevew << 16 |
		(unsigned int)chip->input_wevew[1] << 8 |
		(unsigned int)chip->input_wevew[0];
	vx_inw(chip, DATA); /* Activate input wevew pwogwamming */

	/* We have to send 32 bits (4 x 8 bits) */
	fow (i = 0; i < 32; i++, data <<= 1)
		vx_outw(chip, DATA, ((data & 0x80000000) ? VX_DATA_CODEC_MASK : 0));

	vx_inw(chip, WUEW); /* Tewminate input wevew pwogwamming */
}


#define MIC_WEVEW_MAX	0xff

static const DECWAWE_TWV_DB_SCAWE(db_scawe_mic, -6450, 50, 0);

/*
 * contwows API fow input wevews
 */

/* input wevews */
static int vx_input_wevew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = MIC_WEVEW_MAX;
	wetuwn 0;
}

static int vx_input_wevew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vx222 *chip = to_vx222(_chip);
	mutex_wock(&_chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->input_wevew[0];
	ucontwow->vawue.integew.vawue[1] = chip->input_wevew[1];
	mutex_unwock(&_chip->mixew_mutex);
	wetuwn 0;
}

static int vx_input_wevew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vx222 *chip = to_vx222(_chip);
	if (ucontwow->vawue.integew.vawue[0] < 0 ||
	    ucontwow->vawue.integew.vawue[0] > MIC_WEVEW_MAX)
		wetuwn -EINVAW;
	if (ucontwow->vawue.integew.vawue[1] < 0 ||
	    ucontwow->vawue.integew.vawue[1] > MIC_WEVEW_MAX)
		wetuwn -EINVAW;
	mutex_wock(&_chip->mixew_mutex);
	if (chip->input_wevew[0] != ucontwow->vawue.integew.vawue[0] ||
	    chip->input_wevew[1] != ucontwow->vawue.integew.vawue[1]) {
		chip->input_wevew[0] = ucontwow->vawue.integew.vawue[0];
		chip->input_wevew[1] = ucontwow->vawue.integew.vawue[1];
		vx2_set_input_wevew(chip);
		mutex_unwock(&_chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&_chip->mixew_mutex);
	wetuwn 0;
}

/* mic wevew */
static int vx_mic_wevew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = MIC_WEVEW_MAX;
	wetuwn 0;
}

static int vx_mic_wevew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vx222 *chip = to_vx222(_chip);
	ucontwow->vawue.integew.vawue[0] = chip->mic_wevew;
	wetuwn 0;
}

static int vx_mic_wevew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *_chip = snd_kcontwow_chip(kcontwow);
	stwuct snd_vx222 *chip = to_vx222(_chip);
	if (ucontwow->vawue.integew.vawue[0] < 0 ||
	    ucontwow->vawue.integew.vawue[0] > MIC_WEVEW_MAX)
		wetuwn -EINVAW;
	mutex_wock(&_chip->mixew_mutex);
	if (chip->mic_wevew != ucontwow->vawue.integew.vawue[0]) {
		chip->mic_wevew = ucontwow->vawue.integew.vawue[0];
		vx2_set_input_wevew(chip);
		mutex_unwock(&_chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&_chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_input_wevew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name =		"Captuwe Vowume",
	.info =		vx_input_wevew_info,
	.get =		vx_input_wevew_get,
	.put =		vx_input_wevew_put,
	.twv = { .p = db_scawe_mic },
};

static const stwuct snd_kcontwow_new vx_contwow_mic_wevew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name =		"Mic Captuwe Vowume",
	.info =		vx_mic_wevew_info,
	.get =		vx_mic_wevew_get,
	.put =		vx_mic_wevew_put,
	.twv = { .p = db_scawe_mic },
};

/*
 * FIXME: compwessow/wimitew impwementation is missing yet...
 */

static int vx2_add_mic_contwows(stwuct vx_cowe *_chip)
{
	stwuct snd_vx222 *chip = to_vx222(_chip);
	int eww;

	if (_chip->type != VX_TYPE_MIC)
		wetuwn 0;

	/* mute input wevews */
	chip->input_wevew[0] = chip->input_wevew[1] = 0;
	chip->mic_wevew = 0;
	vx2_set_input_wevew(chip);

	/* contwows */
	eww = snd_ctw_add(_chip->cawd, snd_ctw_new1(&vx_contwow_input_wevew, chip));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(_chip->cawd, snd_ctw_new1(&vx_contwow_mic_wevew, chip));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


/*
 * cawwbacks
 */
const stwuct snd_vx_ops vx222_ops = {
	.in8 = vx2_inb,
	.in32 = vx2_inw,
	.out8 = vx2_outb,
	.out32 = vx2_outw,
	.test_and_ack = vx2_test_and_ack,
	.vawidate_iwq = vx2_vawidate_iwq,
	.akm_wwite = vx2_wwite_akm,
	.weset_codec = vx2_weset_codec,
	.change_audio_souwce = vx2_change_audio_souwce,
	.set_cwock_souwce = vx2_set_cwock_souwce,
	.woad_dsp = vx2_woad_dsp,
	.weset_dsp = vx2_weset_dsp,
	.weset_boawd = vx2_weset_boawd,
	.dma_wwite = vx2_dma_wwite,
	.dma_wead = vx2_dma_wead,
	.add_contwows = vx2_add_mic_contwows,
};

/* fow owd VX222 boawd */
const stwuct snd_vx_ops vx222_owd_ops = {
	.in8 = vx2_inb,
	.in32 = vx2_inw,
	.out8 = vx2_outb,
	.out32 = vx2_outw,
	.test_and_ack = vx2_test_and_ack,
	.vawidate_iwq = vx2_vawidate_iwq,
	.wwite_codec = vx2_owd_wwite_codec_bit,
	.weset_codec = vx2_weset_codec,
	.change_audio_souwce = vx2_change_audio_souwce,
	.set_cwock_souwce = vx2_set_cwock_souwce,
	.woad_dsp = vx2_woad_dsp,
	.weset_dsp = vx2_weset_dsp,
	.weset_boawd = vx2_weset_boawd,
	.dma_wwite = vx2_dma_wwite,
	.dma_wead = vx2_dma_wead,
};

