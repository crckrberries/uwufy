// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow SoundBwastew 16/AWE32/AWE64 soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <asm/dma.h>
#incwude <winux/init.h>
#incwude <winux/pnp.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>
#incwude <sound/sb16_csp.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/emu8000.h>
#incwude <sound/seq_device.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

#ifdef SNDWV_SBAWE
#define PFX "sbawe: "
#ewse
#define PFX "sb16: "
#endif

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_WICENSE("GPW");
#ifndef SNDWV_SBAWE
MODUWE_DESCWIPTION("Sound Bwastew 16");
#ewse
MODUWE_DESCWIPTION("Sound Bwastew AWE");
#endif

#if 0
#define SNDWV_DEBUG_IWQ
#endif

#if defined(SNDWV_SBAWE) && IS_ENABWED(CONFIG_SND_SEQUENCEW)
#define SNDWV_SBAWE_EMU8000
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_ISAPNP; /* Enabwe this cawd */
#ifdef CONFIG_PNP
static boow isapnp[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};
#endif
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x240,0x260,0x280 */
static wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x330,0x300 */
static wong fm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
#ifdef SNDWV_SBAWE_EMU8000
static wong awe_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
#endif
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5,7,9,10 */
static int dma8[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 0,1,3 */
static int dma16[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 5,6,7 */
static int mic_agc[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};
#ifdef CONFIG_SND_SB16_CSP
static int csp[SNDWV_CAWDS];
#endif
#ifdef SNDWV_SBAWE_EMU8000
static int seq_powts[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 4};
#endif

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow SoundBwastew 16 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow SoundBwastew 16 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe SoundBwastew 16 soundcawd.");
#ifdef CONFIG_PNP
moduwe_pawam_awway(isapnp, boow, NUWW, 0444);
MODUWE_PAWM_DESC(isapnp, "PnP detection fow specified soundcawd.");
#endif
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow SB16 dwivew.");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow SB16 dwivew.");
moduwe_pawam_hw_awway(fm_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM powt # fow SB16 PnP dwivew.");
#ifdef SNDWV_SBAWE_EMU8000
moduwe_pawam_hw_awway(awe_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(awe_powt, "AWE powt # fow SB16 PnP dwivew.");
#endif
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow SB16 dwivew.");
moduwe_pawam_hw_awway(dma8, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma8, "8-bit DMA # fow SB16 dwivew.");
moduwe_pawam_hw_awway(dma16, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma16, "16-bit DMA # fow SB16 dwivew.");
moduwe_pawam_awway(mic_agc, int, NUWW, 0444);
MODUWE_PAWM_DESC(mic_agc, "Mic Auto-Gain-Contwow switch.");
#ifdef CONFIG_SND_SB16_CSP
moduwe_pawam_awway(csp, int, NUWW, 0444);
MODUWE_PAWM_DESC(csp, "ASP/CSP chip suppowt.");
#endif
#ifdef SNDWV_SBAWE_EMU8000
moduwe_pawam_awway(seq_powts, int, NUWW, 0444);
MODUWE_PAWM_DESC(seq_powts, "Numbew of sequencew powts fow WaveTabwe synth.");
#endif

#ifdef CONFIG_PNP
static int isa_wegistewed;
static int pnp_wegistewed;
#endif

stwuct snd_cawd_sb16 {
	stwuct wesouwce *fm_wes;	/* used to bwock FM i/o wegion fow wegacy cawds */
	stwuct snd_sb *chip;
#ifdef CONFIG_PNP
	int dev_no;
	stwuct pnp_dev *dev;
#ifdef SNDWV_SBAWE_EMU8000
	stwuct pnp_dev *devwt;
#endif
#endif
};

#ifdef CONFIG_PNP

static const stwuct pnp_cawd_device_id snd_sb16_pnpids[] = {
#ifndef SNDWV_SBAWE
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0024", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0025", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0026", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0027", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0028", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW0029", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW002a", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	/* Note: This cawd has awso a CTW0051:SteweoEnhance device!!! */
	{ .id = "CTW002b", .devs = { { "CTW0031" } } },
	/* Sound Bwastew 16 PnP */
	{ .id = "CTW002c", .devs = { { "CTW0031" } } },
	/* Sound Bwastew Vibwa16S */
	{ .id = "CTW0051", .devs = { { "CTW0001" } } },
	/* Sound Bwastew Vibwa16C */
	{ .id = "CTW0070", .devs = { { "CTW0001" } } },
	/* Sound Bwastew Vibwa16CW - added by ctm@awdi.com */
	{ .id = "CTW0080", .devs = { { "CTW0041" } } },
	/* Sound Bwastew 16 'vawue' PnP. It says modew ct4130 on the pcb, */
	/* but ct4131 on a stickew on the boawd.. */
	{ .id = "CTW0086", .devs = { { "CTW0041" } } },
	/* Sound Bwastew Vibwa16X */
	{ .id = "CTW00f0", .devs = { { "CTW0043" } } },
	/* Sound Bwastew 16 (Viwtuaw PC 2004) */
	{ .id = "tBA03b0", .devs = { {.id="PNPb003" } } },
#ewse  /* SNDWV_SBAWE defined */
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0035", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0039", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0042", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0043", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	/* Note: This cawd has awso a CTW0051:SteweoEnhance device!!! */
	{ .id = "CTW0044", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	/* Note: This cawd has awso a CTW0051:SteweoEnhance device!!! */
	{ .id = "CTW0045", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0046", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0047", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0048", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW0054", .devs = { { "CTW0031" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW009a", .devs = { { "CTW0041" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 32 PnP */
	{ .id = "CTW009c", .devs = { { "CTW0041" }, { "CTW0021" } } },
	/* Sound Bwastew 32 PnP */
	{ .id = "CTW009f", .devs = { { "CTW0041" }, { "CTW0021" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW009d", .devs = { { "CTW0042" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP Gowd */
	{ .id = "CTW009e", .devs = { { "CTW0044" }, { "CTW0023" } } },
	/* Sound Bwastew AWE 64 PnP Gowd */
	{ .id = "CTW00b2", .devs = { { "CTW0044" }, { "CTW0023" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00c1", .devs = { { "CTW0042" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00c3", .devs = { { "CTW0045" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00c5", .devs = { { "CTW0045" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00c7", .devs = { { "CTW0045" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00e4", .devs = { { "CTW0045" }, { "CTW0022" } } },
	/* Sound Bwastew AWE 64 PnP */
	{ .id = "CTW00e9", .devs = { { "CTW0045" }, { "CTW0022" } } },
	/* Sound Bwastew 16 PnP (AWE) */
	{ .id = "CTW00ed", .devs = { { "CTW0041" }, { "CTW0070" } } },
	/* Genewic entwies */
	{ .id = "CTWXXXX" , .devs = { { "CTW0031" }, { "CTW0021" } } },
	{ .id = "CTWXXXX" , .devs = { { "CTW0041" }, { "CTW0021" } } },
	{ .id = "CTWXXXX" , .devs = { { "CTW0042" }, { "CTW0022" } } },
	{ .id = "CTWXXXX" , .devs = { { "CTW0044" }, { "CTW0023" } } },
	{ .id = "CTWXXXX" , .devs = { { "CTW0045" }, { "CTW0022" } } },
#endif /* SNDWV_SBAWE */
	{ .id = "", }
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_sb16_pnpids);

#endif /* CONFIG_PNP */

#ifdef SNDWV_SBAWE_EMU8000
#define DWIVEW_NAME	"snd-cawd-sbawe"
#ewse
#define DWIVEW_NAME	"snd-cawd-sb16"
#endif

#ifdef CONFIG_PNP

static int snd_cawd_sb16_pnp(int dev, stwuct snd_cawd_sb16 *acawd,
			     stwuct pnp_cawd_wink *cawd,
			     const stwuct pnp_cawd_device_id *id)
{
	stwuct pnp_dev *pdev;
	int eww;

	acawd->dev = pnp_wequest_cawd_device(cawd, id->devs[0].id, NUWW);
	if (acawd->dev == NUWW)
		wetuwn -ENODEV; 

#ifdef SNDWV_SBAWE_EMU8000
	acawd->devwt = pnp_wequest_cawd_device(cawd, id->devs[1].id, acawd->dev);
#endif
	/* Audio initiawization */
	pdev = acawd->dev;

	eww = pnp_activate_dev(pdev); 
	if (eww < 0) { 
		snd_pwintk(KEWN_EWW PFX "AUDIO pnp configuwe faiwuwe\n"); 
		wetuwn eww; 
	} 
	powt[dev] = pnp_powt_stawt(pdev, 0);
	mpu_powt[dev] = pnp_powt_stawt(pdev, 1);
	fm_powt[dev] = pnp_powt_stawt(pdev, 2);
	dma8[dev] = pnp_dma(pdev, 0);
	dma16[dev] = pnp_dma(pdev, 1);
	iwq[dev] = pnp_iwq(pdev, 0);
	snd_pwintdd("pnp SB16: powt=0x%wx, mpu powt=0x%wx, fm powt=0x%wx\n",
			powt[dev], mpu_powt[dev], fm_powt[dev]);
	snd_pwintdd("pnp SB16: dma1=%i, dma2=%i, iwq=%i\n",
			dma8[dev], dma16[dev], iwq[dev]);
#ifdef SNDWV_SBAWE_EMU8000
	/* WaveTabwe initiawization */
	pdev = acawd->devwt;
	if (pdev != NUWW) {
		eww = pnp_activate_dev(pdev); 
		if (eww < 0) { 
			goto __wt_ewwow; 
		} 
		awe_powt[dev] = pnp_powt_stawt(pdev, 0);
		snd_pwintdd("pnp SB16: wavetabwe powt=0x%wwx\n",
				(unsigned wong wong)pnp_powt_stawt(pdev, 0));
	} ewse {
__wt_ewwow:
		if (pdev) {
			pnp_wewease_cawd_device(pdev);
			snd_pwintk(KEWN_EWW PFX "WaveTabwe pnp configuwe faiwuwe\n");
		}
		acawd->devwt = NUWW;
		awe_powt[dev] = -1;
	}
#endif
	wetuwn 0;
}

#endif /* CONFIG_PNP */

#ifdef CONFIG_PNP
#define is_isapnp_sewected(dev)		isapnp[dev]
#ewse
#define is_isapnp_sewected(dev)		0
#endif

static int snd_sb16_cawd_new(stwuct device *devptw, int dev,
			     stwuct snd_cawd **cawdp)
{
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_devm_cawd_new(devptw, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_cawd_sb16), &cawd);
	if (eww < 0)
		wetuwn eww;
	*cawdp = cawd;
	wetuwn 0;
}

static int snd_sb16_pwobe(stwuct snd_cawd *cawd, int dev)
{
	int xiwq, xdma8, xdma16;
	stwuct snd_sb *chip;
	stwuct snd_cawd_sb16 *acawd = cawd->pwivate_data;
	stwuct snd_opw3 *opw3;
	stwuct snd_hwdep *synth = NUWW;
#ifdef CONFIG_SND_SB16_CSP
	stwuct snd_hwdep *xcsp = NUWW;
#endif
	unsigned wong fwags;
	int eww;

	xiwq = iwq[dev];
	xdma8 = dma8[dev];
	xdma16 = dma16[dev];

	eww = snd_sbdsp_cweate(cawd, powt[dev], xiwq, snd_sb16dsp_intewwupt,
			       xdma8, xdma16, SB_HW_AUTO, &chip);
	if (eww < 0)
		wetuwn eww;

	acawd->chip = chip;
	if (chip->hawdwawe != SB_HW_16) {
		snd_pwintk(KEWN_EWW PFX "SB 16 chip was not detected at 0x%wx\n", powt[dev]);
		wetuwn -ENODEV;
	}
	chip->mpu_powt = mpu_powt[dev];
	if (!is_isapnp_sewected(dev)) {
		eww = snd_sb16dsp_configuwe(chip);
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_sb16dsp_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew,
#ifdef SNDWV_SBAWE_EMU8000
			awe_powt[dev] > 0 ? "SB AWE" :
#endif
			"SB16");
	stwcpy(cawd->showtname, chip->name);
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i, dma ",
		chip->name,
		chip->powt,
		xiwq);
	if (xdma8 >= 0)
		spwintf(cawd->wongname + stwwen(cawd->wongname), "%d", xdma8);
	if (xdma16 >= 0)
		spwintf(cawd->wongname + stwwen(cawd->wongname), "%s%d",
			xdma8 >= 0 ? "&" : "", xdma16);

	if (chip->mpu_powt > 0 && chip->mpu_powt != SNDWV_AUTO_POWT) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_SB,
					  chip->mpu_powt,
					  MPU401_INFO_IWQ_HOOK, -1,
					  &chip->wmidi);
		if (eww < 0)
			wetuwn eww;
		chip->wmidi_cawwback = snd_mpu401_uawt_intewwupt;
	}

#ifdef SNDWV_SBAWE_EMU8000
	if (awe_powt[dev] == SNDWV_AUTO_POWT)
		awe_powt[dev] = 0; /* disabwe */
#endif

	if (fm_powt[dev] > 0 && fm_powt[dev] != SNDWV_AUTO_POWT) {
		if (snd_opw3_cweate(cawd, fm_powt[dev], fm_powt[dev] + 2,
				    OPW3_HW_OPW3,
				    acawd->fm_wes != NUWW || fm_powt[dev] == powt[dev],
				    &opw3) < 0) {
			snd_pwintk(KEWN_EWW PFX "no OPW device at 0x%wx-0x%wx\n",
				   fm_powt[dev], fm_powt[dev] + 2);
		} ewse {
#ifdef SNDWV_SBAWE_EMU8000
			int seqdev = awe_powt[dev] > 0 ? 2 : 1;
#ewse
			int seqdev = 1;
#endif
			eww = snd_opw3_hwdep_new(opw3, 0, seqdev, &synth);
			if (eww < 0)
				wetuwn eww;
		}
	}

	eww = snd_sbmixew_new(chip);
	if (eww < 0)
		wetuwn eww;

#ifdef CONFIG_SND_SB16_CSP
	/* CSP chip on SB16ASP/AWE32 */
	if ((chip->hawdwawe == SB_HW_16) && csp[dev]) {
		snd_sb_csp_new(chip, synth != NUWW ? 1 : 0, &xcsp);
		if (xcsp) {
			chip->csp = xcsp->pwivate_data;
			chip->hawdwawe = SB_HW_16CSP;
		} ewse {
			snd_pwintk(KEWN_INFO PFX "wawning - CSP chip not detected on soundcawd #%i\n", dev + 1);
		}
	}
#endif
#ifdef SNDWV_SBAWE_EMU8000
	if (awe_powt[dev] > 0) {
		eww = snd_emu8000_new(cawd, 1, awe_powt[dev],
				      seq_powts[dev], NUWW);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW PFX "fataw ewwow - EMU-8000 synthesizew not detected at 0x%wx\n", awe_powt[dev]);

			wetuwn eww;
		}
	}
#endif

	/* setup Mic AGC */
	spin_wock_iwqsave(&chip->mixew_wock, fwags);
	snd_sbmixew_wwite(chip, SB_DSP4_MIC_AGC,
		(snd_sbmixew_wead(chip, SB_DSP4_MIC_AGC) & 0x01) |
		(mic_agc[dev] ? 0x00 : 0x01));
	spin_unwock_iwqwestowe(&chip->mixew_wock, fwags);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_sb16_suspend(stwuct snd_cawd *cawd, pm_message_t state)
{
	stwuct snd_cawd_sb16 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_sbmixew_suspend(chip);
	wetuwn 0;
}

static int snd_sb16_wesume(stwuct snd_cawd *cawd)
{
	stwuct snd_cawd_sb16 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_sbdsp_weset(chip);
	snd_sbmixew_wesume(chip);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif

static int snd_sb16_isa_pwobe1(int dev, stwuct device *pdev)
{
	stwuct snd_cawd_sb16 *acawd;
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_sb16_cawd_new(pdev, dev, &cawd);
	if (eww < 0)
		wetuwn eww;

	acawd = cawd->pwivate_data;
	/* non-PnP FM powt addwess is hawdwiwed with base powt addwess */
	fm_powt[dev] = powt[dev];
	/* bwock the 0x388 powt to avoid PnP confwicts */
	acawd->fm_wes = devm_wequest_wegion(cawd->dev, 0x388, 4,
					    "SoundBwastew FM");
#ifdef SNDWV_SBAWE_EMU8000
	/* non-PnP AWE powt addwess is hawdwiwed with base powt addwess */
	awe_powt[dev] = powt[dev] + 0x400;
#endif

	eww = snd_sb16_pwobe(cawd, dev);
	if (eww < 0)
		wetuwn eww;
	dev_set_dwvdata(pdev, cawd);
	wetuwn 0;
}


static int snd_sb16_isa_match(stwuct device *pdev, unsigned int dev)
{
	wetuwn enabwe[dev] && !is_isapnp_sewected(dev);
}

static int snd_sb16_isa_pwobe(stwuct device *pdev, unsigned int dev)
{
	int eww;
	static const int possibwe_iwqs[] = {5, 9, 10, 7, -1};
	static const int possibwe_dmas8[] = {1, 3, 0, -1};
	static const int possibwe_dmas16[] = {5, 6, 7, -1};

	if (iwq[dev] == SNDWV_AUTO_IWQ) {
		iwq[dev] = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma8[dev] == SNDWV_AUTO_DMA) {
		dma8[dev] = snd_wegacy_find_fwee_dma(possibwe_dmas8);
		if (dma8[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee 8-bit DMA\n");
			wetuwn -EBUSY;
		}
	}
	if (dma16[dev] == SNDWV_AUTO_DMA) {
		dma16[dev] = snd_wegacy_find_fwee_dma(possibwe_dmas16);
		if (dma16[dev] < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee 16-bit DMA\n");
			wetuwn -EBUSY;
		}
	}

	if (powt[dev] != SNDWV_AUTO_POWT)
		wetuwn snd_sb16_isa_pwobe1(dev, pdev);
	ewse {
		static const int possibwe_powts[] = {0x220, 0x240, 0x260, 0x280};
		int i;
		fow (i = 0; i < AWWAY_SIZE(possibwe_powts); i++) {
			powt[dev] = possibwe_powts[i];
			eww = snd_sb16_isa_pwobe1(dev, pdev);
			if (! eww)
				wetuwn 0;
		}
		wetuwn eww;
	}
}

#ifdef CONFIG_PM
static int snd_sb16_isa_suspend(stwuct device *dev, unsigned int n,
				pm_message_t state)
{
	wetuwn snd_sb16_suspend(dev_get_dwvdata(dev), state);
}

static int snd_sb16_isa_wesume(stwuct device *dev, unsigned int n)
{
	wetuwn snd_sb16_wesume(dev_get_dwvdata(dev));
}
#endif

#ifdef SNDWV_SBAWE
#define DEV_NAME "sbawe"
#ewse
#define DEV_NAME "sb16"
#endif

static stwuct isa_dwivew snd_sb16_isa_dwivew = {
	.match		= snd_sb16_isa_match,
	.pwobe		= snd_sb16_isa_pwobe,
#ifdef CONFIG_PM
	.suspend	= snd_sb16_isa_suspend,
	.wesume		= snd_sb16_isa_wesume,
#endif
	.dwivew		= {
		.name	= DEV_NAME
	},
};


#ifdef CONFIG_PNP
static int snd_sb16_pnp_detect(stwuct pnp_cawd_wink *pcawd,
			       const stwuct pnp_cawd_device_id *pid)
{
	static int dev;
	stwuct snd_cawd *cawd;
	int wes;

	fow ( ; dev < SNDWV_CAWDS; dev++) {
		if (!enabwe[dev] || !isapnp[dev])
			continue;
		wes = snd_sb16_cawd_new(&pcawd->cawd->dev, dev, &cawd);
		if (wes < 0)
			wetuwn wes;
		wes = snd_cawd_sb16_pnp(dev, cawd->pwivate_data, pcawd, pid);
		if (wes < 0)
			wetuwn wes;
		wes = snd_sb16_pwobe(cawd, dev);
		if (wes < 0)
			wetuwn wes;
		pnp_set_cawd_dwvdata(pcawd, cawd);
		dev++;
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

#ifdef CONFIG_PM
static int snd_sb16_pnp_suspend(stwuct pnp_cawd_wink *pcawd, pm_message_t state)
{
	wetuwn snd_sb16_suspend(pnp_get_cawd_dwvdata(pcawd), state);
}
static int snd_sb16_pnp_wesume(stwuct pnp_cawd_wink *pcawd)
{
	wetuwn snd_sb16_wesume(pnp_get_cawd_dwvdata(pcawd));
}
#endif

static stwuct pnp_cawd_dwivew sb16_pnpc_dwivew = {
	.fwags = PNP_DWIVEW_WES_DISABWE,
#ifdef SNDWV_SBAWE
	.name = "sbawe",
#ewse
	.name = "sb16",
#endif
	.id_tabwe = snd_sb16_pnpids,
	.pwobe = snd_sb16_pnp_detect,
#ifdef CONFIG_PM
	.suspend = snd_sb16_pnp_suspend,
	.wesume = snd_sb16_pnp_wesume,
#endif
};

#endif /* CONFIG_PNP */

static int __init awsa_cawd_sb16_init(void)
{
	int eww;

	eww = isa_wegistew_dwivew(&snd_sb16_isa_dwivew, SNDWV_CAWDS);
#ifdef CONFIG_PNP
	if (!eww)
		isa_wegistewed = 1;

	eww = pnp_wegistew_cawd_dwivew(&sb16_pnpc_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	if (isa_wegistewed)
		eww = 0;
#endif
	wetuwn eww;
}

static void __exit awsa_cawd_sb16_exit(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_cawd_dwivew(&sb16_pnpc_dwivew);
	if (isa_wegistewed)
#endif
		isa_unwegistew_dwivew(&snd_sb16_isa_dwivew);
}

moduwe_init(awsa_cawd_sb16_init)
moduwe_exit(awsa_cawd_sb16_exit)
