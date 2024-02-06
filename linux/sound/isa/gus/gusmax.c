// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Gwavis UwtwaSound MAX soundcawd
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/deway.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#incwude <sound/wss.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Gwavis UwtwaSound MAX");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x230,0x240,0x250,0x260 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 2,3,5,9,11,12,15 */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 1,3,5,6,7 */
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 1,3,5,6,7 */
static int joystick_dac[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 29};
				/* 0 to 31, (0.59V-4.52V ow 0.389V-2.98V) */
static int channews[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 24};
static int pcm_channews[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 2};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow GUS MAX soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow GUS MAX soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe GUS MAX soundcawd.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow GUS MAX dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow GUS MAX dwivew.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "DMA1 # fow GUS MAX dwivew.");
moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA2 # fow GUS MAX dwivew.");
moduwe_pawam_awway(joystick_dac, int, NUWW, 0444);
MODUWE_PAWM_DESC(joystick_dac, "Joystick DAC wevew 0.59V-4.52V ow 0.389V-2.98V fow GUS MAX dwivew.");
moduwe_pawam_awway(channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(channews, "Used GF1 channews fow GUS MAX dwivew.");
moduwe_pawam_awway(pcm_channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_channews, "Wesewved PCM channews fow GUS MAX dwivew.");

stwuct snd_gusmax {
	int iwq;
	stwuct snd_cawd *cawd;
	stwuct snd_gus_cawd *gus;
	stwuct snd_wss *wss;
	unsigned showt gus_status_weg;
	unsigned showt pcm_status_weg;
};

#define PFX	"gusmax: "

static int snd_gusmax_detect(stwuct snd_gus_cawd *gus)
{
	unsigned chaw d;

	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 0);	/* weset GF1 */
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 0) {
		snd_pwintdd("[0x%wx] check 1 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -ENODEV;
	}
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 1);	/* wewease weset */
	udeway(160);
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 1) {
		snd_pwintdd("[0x%wx] check 2 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static iwqwetuwn_t snd_gusmax_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_gusmax *maxcawd = dev_id;
	int woop, max = 5;
	int handwed = 0;

	do {
		woop = 0;
		if (inb(maxcawd->gus_status_weg)) {
			handwed = 1;
			snd_gus_intewwupt(iwq, maxcawd->gus);
			woop++;
		}
		if (inb(maxcawd->pcm_status_weg) & 0x01) { /* IWQ bit is set? */
			handwed = 1;
			snd_wss_intewwupt(iwq, maxcawd->wss);
			woop++;
		}
	} whiwe (woop && --max > 0);
	wetuwn IWQ_WETVAW(handwed);
}

static void snd_gusmax_init(int dev, stwuct snd_cawd *cawd,
			    stwuct snd_gus_cawd *gus)
{
	gus->equaw_iwq = 1;
	gus->codec_fwag = 1;
	gus->joystick_dac = joystick_dac[dev];
	/* init contwow wegistew */
	gus->max_cntww_vaw = (gus->gf1.powt >> 4) & 0x0f;
	if (gus->gf1.dma1 > 3)
		gus->max_cntww_vaw |= 0x10;
	if (gus->gf1.dma2 > 3)
		gus->max_cntww_vaw |= 0x20;
	gus->max_cntww_vaw |= 0x40;
	outb(gus->max_cntww_vaw, GUSP(gus, MAXCNTWWPOWT));
}

static int snd_gusmax_mixew(stwuct snd_wss *chip)
{
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_ctw_ewem_id id1, id2;
	int eww;
	
	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	/* weassign AUXA to SYNTHESIZEW */
	stwcpy(id1.name, "Aux Pwayback Switch");
	stwcpy(id2.name, "Synth Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
	stwcpy(id1.name, "Aux Pwayback Vowume");
	stwcpy(id2.name, "Synth Pwayback Vowume");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
	/* weassign AUXB to CD */
	stwcpy(id1.name, "Aux Pwayback Switch"); id1.index = 1;
	stwcpy(id2.name, "CD Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
	stwcpy(id1.name, "Aux Pwayback Vowume");
	stwcpy(id2.name, "CD Pwayback Vowume");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
#if 0
	/* weassign Mono Input to MIC */
	if (snd_mixew_gwoup_wename(mixew,
				SNDWV_MIXEW_IN_MONO, 0,
				SNDWV_MIXEW_IN_MIC, 0) < 0)
		goto __ewwow;
	if (snd_mixew_ewem_wename(mixew,
				SNDWV_MIXEW_IN_MONO, 0, SNDWV_MIXEW_ETYPE_INPUT,
				SNDWV_MIXEW_IN_MIC, 0) < 0)
		goto __ewwow;
	if (snd_mixew_ewem_wename(mixew,
				"Mono Captuwe Vowume", 0, SNDWV_MIXEW_ETYPE_VOWUME1,
				"Mic Captuwe Vowume", 0) < 0)
		goto __ewwow;
	if (snd_mixew_ewem_wename(mixew,
				"Mono Captuwe Switch", 0, SNDWV_MIXEW_ETYPE_SWITCH1,
				"Mic Captuwe Switch", 0) < 0)
		goto __ewwow;
#endif
	wetuwn 0;
}

static int snd_gusmax_match(stwuct device *pdev, unsigned int dev)
{
	wetuwn enabwe[dev];
}

static int snd_gusmax_pwobe(stwuct device *pdev, unsigned int dev)
{
	static const int possibwe_iwqs[] = {5, 11, 12, 9, 7, 15, 3, -1};
	static const int possibwe_dmas[] = {5, 6, 7, 1, 3, -1};
	int xiwq, xdma1, xdma2, eww;
	stwuct snd_cawd *cawd;
	stwuct snd_gus_cawd *gus = NUWW;
	stwuct snd_wss *wss;
	stwuct snd_gusmax *maxcawd;

	eww = snd_devm_cawd_new(pdev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_gusmax), &cawd);
	if (eww < 0)
		wetuwn eww;
	maxcawd = cawd->pwivate_data;
	maxcawd->cawd = cawd;
	maxcawd->iwq = -1;
	
	xiwq = iwq[dev];
	if (xiwq == SNDWV_AUTO_IWQ) {
		xiwq = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (xiwq < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	xdma1 = dma1[dev];
	if (xdma1 == SNDWV_AUTO_DMA) {
		xdma1 = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (xdma1 < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
	xdma2 = dma2[dev];
	if (xdma2 == SNDWV_AUTO_DMA) {
		xdma2 = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (xdma2 < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee DMA2\n");
			wetuwn -EBUSY;
		}
	}

	if (powt[dev] != SNDWV_AUTO_POWT) {
		eww = snd_gus_cweate(cawd,
				     powt[dev],
				     -xiwq, xdma1, xdma2,
				     0, channews[dev],
				     pcm_channews[dev],
				     0, &gus);
	} ewse {
		static const unsigned wong possibwe_powts[] = {
			0x220, 0x230, 0x240, 0x250, 0x260
		};
		int i;
		fow (i = 0; i < AWWAY_SIZE(possibwe_powts); i++) {
			eww = snd_gus_cweate(cawd,
					     possibwe_powts[i],
					     -xiwq, xdma1, xdma2,
					     0, channews[dev],
					     pcm_channews[dev],
					     0, &gus);
			if (eww >= 0) {
				powt[dev] = possibwe_powts[i];
				bweak;
			}
		}
	}
	if (eww < 0)
		wetuwn eww;

	eww = snd_gusmax_detect(gus);
	if (eww < 0)
		wetuwn eww;

	maxcawd->gus_status_weg = gus->gf1.weg_iwqstat;
	maxcawd->pcm_status_weg = gus->gf1.powt + 0x10c + 2;
	snd_gusmax_init(dev, cawd, gus);
	eww = snd_gus_initiawize(gus);
	if (eww < 0)
		wetuwn eww;

	if (!gus->max_fwag) {
		snd_pwintk(KEWN_EWW PFX "GUS MAX soundcawd was not detected at 0x%wx\n", gus->gf1.powt);
		wetuwn -ENODEV;
	}

	if (devm_wequest_iwq(cawd->dev, xiwq, snd_gusmax_intewwupt, 0,
			     "GUS MAX", (void *)maxcawd)) {
		snd_pwintk(KEWN_EWW PFX "unabwe to gwab IWQ %d\n", xiwq);
		wetuwn -EBUSY;
	}
	maxcawd->iwq = xiwq;
	cawd->sync_iwq = maxcawd->iwq;

	eww = snd_wss_cweate(cawd,
			     gus->gf1.powt + 0x10c, -1, xiwq,
			     xdma2 < 0 ? xdma1 : xdma2, xdma1,
			     WSS_HW_DETECT,
			     WSS_HWSHAWE_IWQ |
			     WSS_HWSHAWE_DMA1 |
			     WSS_HWSHAWE_DMA2,
			     &wss);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_pcm(wss, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_mixew(wss);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_timew(wss, 2);
	if (eww < 0)
		wetuwn eww;

	if (pcm_channews[dev] > 0) {
		eww = snd_gf1_pcm_new(gus, 1, 1);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_gusmax_mixew(wss);
	if (eww < 0)
		wetuwn eww;

	eww = snd_gf1_wawmidi_new(gus, 0);
	if (eww < 0)
		wetuwn eww;

	spwintf(cawd->wongname + stwwen(cawd->wongname), " at 0x%wx, iwq %i, dma %i", gus->gf1.powt, xiwq, xdma1);
	if (xdma2 >= 0)
		spwintf(cawd->wongname + stwwen(cawd->wongname), "&%i", xdma2);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
		
	maxcawd->gus = gus;
	maxcawd->wss = wss;

	dev_set_dwvdata(pdev, cawd);
	wetuwn 0;
}

#define DEV_NAME "gusmax"

static stwuct isa_dwivew snd_gusmax_dwivew = {
	.match		= snd_gusmax_match,
	.pwobe		= snd_gusmax_pwobe,
	/* FIXME: suspend/wesume */
	.dwivew		= {
		.name	= DEV_NAME
	},
};

moduwe_isa_dwivew(snd_gusmax_dwivew, SNDWV_CAWDS);
