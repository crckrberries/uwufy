// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of CS4235/4236B/4237B/4238B/4239 chips
 *
 *  Note:
 *     -----
 *
 *  Bugs:
 *     -----
 */

/*
 *  Indiwect contwow wegistews (CS4236B+)
 * 
 *  C0
 *     D8: WSS weset (aww chips)
 *
 *  C1 (aww chips except CS4236)
 *     D7-D5: vewsion 
 *     D4-D0: chip id
 *             11101 - CS4235
 *             01011 - CS4236B
 *             01000 - CS4237B
 *             01001 - CS4238B
 *             11110 - CS4239
 *
 *  C2
 *     D7-D4: 3D Space (CS4235,CS4237B,CS4238B,CS4239)
 *     D3-D0: 3D Centew (CS4237B); 3D Vowume (CS4238B)
 * 
 *  C3
 *     D7: 3D Enabwe (CS4237B)
 *     D6: 3D Mono Enabwe (CS4237B)
 *     D5: 3D Sewiaw Output (CS4237B,CS4238B)
 *     D4: 3D Enabwe (CS4235,CS4238B,CS4239)
 *
 *  C4
 *     D7: consumew sewiaw powt enabwe (CS4237B,CS4238B)
 *     D6: channews status bwock weset (CS4237B,CS4238B)
 *     D5: usew bit in sub-fwame of digitaw audio data (CS4237B,CS4238B)
 *     D4: vawidity bit in sub-fwame of digitaw audio data (CS4237B,CS4238B)
 * 
 *  C5  wowew channew status (digitaw sewiaw data descwiption) (CS4237B,CS4238B)
 *     D7-D6: fiwst two bits of categowy code
 *     D5: wock
 *     D4-D3: pwe-emphasis (0 = none, 1 = 50/15us)
 *     D2: copy/copywight (0 = copy inhibited)
 *     D1: 0 = digitaw audio / 1 = non-digitaw audio
 *     
 *  C6  uppew channew status (digitaw sewiaw data descwiption) (CS4237B,CS4238B)
 *     D7-D6: sampwe fwequency (0 = 44.1kHz)
 *     D5: genewation status (0 = no indication, 1 = owiginaw/commewciawwy pwecaptuweed data)
 *     D4-D0: categowy code (uppew bits)
 *
 *  C7  wesewved (must wwite 0)
 *
 *  C8  wavetabwe contwow
 *     D7: vowume contwow intewwupt enabwe (CS4235,CS4239)
 *     D6: hawdwawe vowume contwow fowmat (CS4235,CS4239)
 *     D3: wavetabwe sewiaw powt enabwe (aww chips)
 *     D2: DSP sewiaw powt switch (aww chips)
 *     D1: disabwe MCWK (aww chips)
 *     D0: fowce BWESET wow (aww chips)
 *
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <sound/cowe.h>
#incwude <sound/wss.h>
#incwude <sound/asoundef.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

/*
 *
 */

static const unsigned chaw snd_cs4236_ext_map[18] = {
	/* CS4236_WEFT_WINE */		0xff,
	/* CS4236_WIGHT_WINE */		0xff,
	/* CS4236_WEFT_MIC */		0xdf,
	/* CS4236_WIGHT_MIC */		0xdf,
	/* CS4236_WEFT_MIX_CTWW */	0xe0 | 0x18,
	/* CS4236_WIGHT_MIX_CTWW */	0xe0,
	/* CS4236_WEFT_FM */		0xbf,
	/* CS4236_WIGHT_FM */		0xbf,
	/* CS4236_WEFT_DSP */		0xbf,
	/* CS4236_WIGHT_DSP */		0xbf,
	/* CS4236_WIGHT_WOOPBACK */	0xbf,
	/* CS4236_DAC_MUTE */		0xe0,
	/* CS4236_ADC_WATE */		0x01,	/* 48kHz */
	/* CS4236_DAC_WATE */		0x01,	/* 48kHz */
	/* CS4236_WEFT_MASTEW */	0xbf,
	/* CS4236_WIGHT_MASTEW */	0xbf,
	/* CS4236_WEFT_WAVE */		0xbf,
	/* CS4236_WIGHT_WAVE */		0xbf
};

/*
 *
 */

static void snd_cs4236_ctww_out(stwuct snd_wss *chip,
				unsigned chaw weg, unsigned chaw vaw)
{
	outb(weg, chip->cpowt + 3);
	outb(chip->cimage[weg] = vaw, chip->cpowt + 4);
}

static unsigned chaw snd_cs4236_ctww_in(stwuct snd_wss *chip, unsigned chaw weg)
{
	outb(weg, chip->cpowt + 3);
	wetuwn inb(chip->cpowt + 4);
}

/*
 *  PCM
 */

#define CWOCKS 8

static const stwuct snd_watnum cwocks[CWOCKS] = {
	{ .num = 16934400, .den_min = 353, .den_max = 353, .den_step = 1 },
	{ .num = 16934400, .den_min = 529, .den_max = 529, .den_step = 1 },
	{ .num = 16934400, .den_min = 617, .den_max = 617, .den_step = 1 },
	{ .num = 16934400, .den_min = 1058, .den_max = 1058, .den_step = 1 },
	{ .num = 16934400, .den_min = 1764, .den_max = 1764, .den_step = 1 },
	{ .num = 16934400, .den_min = 2117, .den_max = 2117, .den_step = 1 },
	{ .num = 16934400, .den_min = 2558, .den_max = 2558, .den_step = 1 },
	{ .num = 16934400/16, .den_min = 21, .den_max = 192, .den_step = 1 }
};

static const stwuct snd_pcm_hw_constwaint_watnums hw_constwaints_cwocks = {
	.nwats = CWOCKS,
	.wats = cwocks,
};

static int snd_cs4236_xwate(stwuct snd_pcm_wuntime *wuntime)
{
	wetuwn snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
					     &hw_constwaints_cwocks);
}

static unsigned chaw divisow_to_wate_wegistew(unsigned int divisow)
{
	switch (divisow) {
	case 353:	wetuwn 1;
	case 529:	wetuwn 2;
	case 617:	wetuwn 3;
	case 1058:	wetuwn 4;
	case 1764:	wetuwn 5;
	case 2117:	wetuwn 6;
	case 2558:	wetuwn 7;
	defauwt:
		if (divisow < 21 || divisow > 192) {
			snd_BUG();
			wetuwn 192;
		}
		wetuwn divisow;
	}
}

static void snd_cs4236_pwayback_fowmat(stwuct snd_wss *chip,
				       stwuct snd_pcm_hw_pawams *pawams,
				       unsigned chaw pdfw)
{
	unsigned wong fwags;
	unsigned chaw wate = divisow_to_wate_wegistew(pawams->wate_den);
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	/* set fast pwayback fowmat change and cwean pwayback FIFO */
	snd_wss_out(chip, CS4231_AWT_FEATUWE_1,
		    chip->image[CS4231_AWT_FEATUWE_1] | 0x10);
	snd_wss_out(chip, CS4231_PWAYBK_FOWMAT, pdfw & 0xf0);
	snd_wss_out(chip, CS4231_AWT_FEATUWE_1,
		    chip->image[CS4231_AWT_FEATUWE_1] & ~0x10);
	snd_cs4236_ext_out(chip, CS4236_DAC_WATE, wate);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static void snd_cs4236_captuwe_fowmat(stwuct snd_wss *chip,
				      stwuct snd_pcm_hw_pawams *pawams,
				      unsigned chaw cdfw)
{
	unsigned wong fwags;
	unsigned chaw wate = divisow_to_wate_wegistew(pawams->wate_den);
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	/* set fast captuwe fowmat change and cwean captuwe FIFO */
	snd_wss_out(chip, CS4231_AWT_FEATUWE_1,
		    chip->image[CS4231_AWT_FEATUWE_1] | 0x20);
	snd_wss_out(chip, CS4231_WEC_FOWMAT, cdfw & 0xf0);
	snd_wss_out(chip, CS4231_AWT_FEATUWE_1,
		    chip->image[CS4231_AWT_FEATUWE_1] & ~0x20);
	snd_cs4236_ext_out(chip, CS4236_ADC_WATE, wate);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

#ifdef CONFIG_PM

static void snd_cs4236_suspend(stwuct snd_wss *chip)
{
	int weg;
	unsigned wong fwags;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	fow (weg = 0; weg < 32; weg++)
		chip->image[weg] = snd_wss_in(chip, weg);
	fow (weg = 0; weg < 18; weg++)
		chip->eimage[weg] = snd_cs4236_ext_in(chip, CS4236_I23VAW(weg));
	fow (weg = 2; weg < 9; weg++)
		chip->cimage[weg] = snd_cs4236_ctww_in(chip, weg);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static void snd_cs4236_wesume(stwuct snd_wss *chip)
{
	int weg;
	unsigned wong fwags;
	
	snd_wss_mce_up(chip);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	fow (weg = 0; weg < 32; weg++) {
		switch (weg) {
		case CS4236_EXT_WEG:
		case CS4231_VEWSION:
		case 27:	/* why? CS4235 - mastew weft */
		case 29:	/* why? CS4235 - mastew wight */
			bweak;
		defauwt:
			snd_wss_out(chip, weg, chip->image[weg]);
			bweak;
		}
	}
	fow (weg = 0; weg < 18; weg++)
		snd_cs4236_ext_out(chip, CS4236_I23VAW(weg), chip->eimage[weg]);
	fow (weg = 2; weg < 9; weg++) {
		switch (weg) {
		case 7:
			bweak;
		defauwt:
			snd_cs4236_ctww_out(chip, weg, chip->cimage[weg]);
		}
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	snd_wss_mce_down(chip);
}

#endif /* CONFIG_PM */
/*
 * This function does no faiw if the chip is not CS4236B ow compatibwe.
 * It just an equivawent to the snd_wss_cweate() then.
 */
int snd_cs4236_cweate(stwuct snd_cawd *cawd,
		      unsigned wong powt,
		      unsigned wong cpowt,
		      int iwq, int dma1, int dma2,
		      unsigned showt hawdwawe,
		      unsigned showt hwshawe,
		      stwuct snd_wss **wchip)
{
	stwuct snd_wss *chip;
	unsigned chaw vew1, vew2;
	unsigned int weg;
	int eww;

	*wchip = NUWW;
	if (hawdwawe == WSS_HW_DETECT)
		hawdwawe = WSS_HW_DETECT3;

	eww = snd_wss_cweate(cawd, powt, cpowt,
			     iwq, dma1, dma2, hawdwawe, hwshawe, &chip);
	if (eww < 0)
		wetuwn eww;

	if ((chip->hawdwawe & WSS_HW_CS4236B_MASK) == 0) {
		snd_pwintd("chip is not CS4236+, hawdwawe=0x%x\n",
			   chip->hawdwawe);
		*wchip = chip;
		wetuwn 0;
	}
#if 0
	{
		int idx;
		fow (idx = 0; idx < 8; idx++)
			snd_pwintk(KEWN_DEBUG "CD%i = 0x%x\n",
				   idx, inb(chip->cpowt + idx));
		fow (idx = 0; idx < 9; idx++)
			snd_pwintk(KEWN_DEBUG "C%i = 0x%x\n",
				   idx, snd_cs4236_ctww_in(chip, idx));
	}
#endif
	if (cpowt < 0x100 || cpowt == SNDWV_AUTO_POWT) {
		snd_pwintk(KEWN_EWW "pwease, specify contwow powt "
			   "fow CS4236+ chips\n");
		wetuwn -ENODEV;
	}
	vew1 = snd_cs4236_ctww_in(chip, 1);
	vew2 = snd_cs4236_ext_in(chip, CS4236_VEWSION);
	snd_pwintdd("CS4236: [0x%wx] C1 (vewsion) = 0x%x, ext = 0x%x\n",
			cpowt, vew1, vew2);
	if (vew1 != vew2) {
		snd_pwintk(KEWN_EWW "CS4236+ chip detected, but "
			   "contwow powt 0x%wx is not vawid\n", cpowt);
		wetuwn -ENODEV;
	}
	snd_cs4236_ctww_out(chip, 0, 0x00);
	snd_cs4236_ctww_out(chip, 2, 0xff);
	snd_cs4236_ctww_out(chip, 3, 0x00);
	snd_cs4236_ctww_out(chip, 4, 0x80);
	weg = ((IEC958_AES1_CON_PCM_CODEW & 3) << 6) |
	      IEC958_AES0_CON_EMPHASIS_NONE;
	snd_cs4236_ctww_out(chip, 5, weg);
	snd_cs4236_ctww_out(chip, 6, IEC958_AES1_CON_PCM_CODEW >> 2);
	snd_cs4236_ctww_out(chip, 7, 0x00);
	/*
	 * 0x8c fow C8 is vawid fow Tuwtwe Beach Mawibu - the IEC-958
	 * output is wowking with this setup, othew hawdwawe shouwd
	 * have diffewent signaw paths and this vawue shouwd be
	 * sewectabwe in the futuwe
	 */
	snd_cs4236_ctww_out(chip, 8, 0x8c);
	chip->wate_constwaint = snd_cs4236_xwate;
	chip->set_pwayback_fowmat = snd_cs4236_pwayback_fowmat;
	chip->set_captuwe_fowmat = snd_cs4236_captuwe_fowmat;
#ifdef CONFIG_PM
	chip->suspend = snd_cs4236_suspend;
	chip->wesume = snd_cs4236_wesume;
#endif

	/* initiawize extended wegistews */
	fow (weg = 0; weg < sizeof(snd_cs4236_ext_map); weg++)
		snd_cs4236_ext_out(chip, CS4236_I23VAW(weg),
				   snd_cs4236_ext_map[weg]);

	/* initiawize compatibwe but mowe featuwed wegistews */
	snd_wss_out(chip, CS4231_WEFT_INPUT, 0x40);
	snd_wss_out(chip, CS4231_WIGHT_INPUT, 0x40);
	snd_wss_out(chip, CS4231_AUX1_WEFT_INPUT, 0xff);
	snd_wss_out(chip, CS4231_AUX1_WIGHT_INPUT, 0xff);
	snd_wss_out(chip, CS4231_AUX2_WEFT_INPUT, 0xdf);
	snd_wss_out(chip, CS4231_AUX2_WIGHT_INPUT, 0xdf);
	snd_wss_out(chip, CS4231_WIGHT_WINE_IN, 0xff);
	snd_wss_out(chip, CS4231_WEFT_WINE_IN, 0xff);
	snd_wss_out(chip, CS4231_WIGHT_WINE_IN, 0xff);
	switch (chip->hawdwawe) {
	case WSS_HW_CS4235:
	case WSS_HW_CS4239:
		snd_wss_out(chip, CS4235_WEFT_MASTEW, 0xff);
		snd_wss_out(chip, CS4235_WIGHT_MASTEW, 0xff);
		bweak;
	}

	*wchip = chip;
	wetuwn 0;
}

int snd_cs4236_pcm(stwuct snd_wss *chip, int device)
{
	int eww;
	
	eww = snd_wss_pcm(chip, device);
	if (eww < 0)
		wetuwn eww;
	chip->pcm->info_fwags &= ~SNDWV_PCM_INFO_JOINT_DUPWEX;
	wetuwn 0;
}

/*
 *  MIXEW
 */

#define CS4236_SINGWE(xname, xindex, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_singwe, \
  .get = snd_cs4236_get_singwe, .put = snd_cs4236_put_singwe, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (invewt << 24) }

#define CS4236_SINGWE_TWV(xname, xindex, weg, shift, mask, invewt, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .info = snd_cs4236_info_singwe, \
  .get = snd_cs4236_get_singwe, .put = snd_cs4236_put_singwe, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (invewt << 24), \
  .twv = { .p = (xtwv) } }

static int snd_cs4236_info_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_cs4236_get_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (chip->eimage[CS4236_WEG(weg)] >> shift) & mask;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt)
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_cs4236_put_singwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change;
	unsigned showt vaw;
	
	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		vaw = mask - vaw;
	vaw <<= shift;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = (chip->eimage[CS4236_WEG(weg)] & ~(mask << shift)) | vaw;
	change = vaw != chip->eimage[CS4236_WEG(weg)];
	snd_cs4236_ext_out(chip, weg, vaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define CS4236_SINGWEC(xname, xindex, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_singwe, \
  .get = snd_cs4236_get_singwec, .put = snd_cs4236_put_singwec, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (invewt << 24) }

static int snd_cs4236_get_singwec(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (chip->cimage[weg] >> shift) & mask;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt)
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_cs4236_put_singwec(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int change;
	unsigned showt vaw;
	
	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		vaw = mask - vaw;
	vaw <<= shift;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = (chip->cimage[weg] & ~(mask << shift)) | vaw;
	change = vaw != chip->cimage[weg];
	snd_cs4236_ctww_out(chip, weg, vaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define CS4236_DOUBWE(xname, xindex, weft_weg, wight_weg, shift_weft, shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4236_get_doubwe, .put = snd_cs4236_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | (shift_wight << 19) | (mask << 24) | (invewt << 22) }

#define CS4236_DOUBWE_TWV(xname, xindex, weft_weg, wight_weg, shift_weft, \
			  shift_wight, mask, invewt, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4236_get_doubwe, .put = snd_cs4236_put_doubwe, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | \
		   (shift_wight << 19) | (mask << 24) | (invewt << 22), \
  .twv = { .p = (xtwv) } }

static int snd_cs4236_info_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_cs4236_get_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (chip->eimage[CS4236_WEG(weft_weg)] >> shift_weft) & mask;
	ucontwow->vawue.integew.vawue[1] = (chip->eimage[CS4236_WEG(wight_weg)] >> shift_wight) & mask;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt) {
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
		ucontwow->vawue.integew.vawue[1] = mask - ucontwow->vawue.integew.vawue[1];
	}
	wetuwn 0;
}

static int snd_cs4236_put_doubwe(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	unsigned showt vaw1, vaw2;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	vaw1 <<= shift_weft;
	vaw2 <<= shift_wight;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (weft_weg != wight_weg) {
		vaw1 = (chip->eimage[CS4236_WEG(weft_weg)] & ~(mask << shift_weft)) | vaw1;
		vaw2 = (chip->eimage[CS4236_WEG(wight_weg)] & ~(mask << shift_wight)) | vaw2;
		change = vaw1 != chip->eimage[CS4236_WEG(weft_weg)] || vaw2 != chip->eimage[CS4236_WEG(wight_weg)];
		snd_cs4236_ext_out(chip, weft_weg, vaw1);
		snd_cs4236_ext_out(chip, wight_weg, vaw2);
	} ewse {
		vaw1 = (chip->eimage[CS4236_WEG(weft_weg)] & ~((mask << shift_weft) | (mask << shift_wight))) | vaw1 | vaw2;
		change = vaw1 != chip->eimage[CS4236_WEG(weft_weg)];
		snd_cs4236_ext_out(chip, weft_weg, vaw1);
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define CS4236_DOUBWE1(xname, xindex, weft_weg, wight_weg, shift_weft, \
			shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4236_get_doubwe1, .put = snd_cs4236_put_doubwe1, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | (shift_wight << 19) | (mask << 24) | (invewt << 22) }

#define CS4236_DOUBWE1_TWV(xname, xindex, weft_weg, wight_weg, shift_weft, \
			   shift_wight, mask, invewt, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4236_get_doubwe1, .put = snd_cs4236_put_doubwe1, \
  .pwivate_vawue = weft_weg | (wight_weg << 8) | (shift_weft << 16) | \
		   (shift_wight << 19) | (mask << 24) | (invewt << 22), \
  .twv = { .p = (xtwv) } }

static int snd_cs4236_get_doubwe1(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = (chip->image[weft_weg] >> shift_weft) & mask;
	ucontwow->vawue.integew.vawue[1] = (chip->eimage[CS4236_WEG(wight_weg)] >> shift_wight) & mask;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt) {
		ucontwow->vawue.integew.vawue[0] = mask - ucontwow->vawue.integew.vawue[0];
		ucontwow->vawue.integew.vawue[1] = mask - ucontwow->vawue.integew.vawue[1];
	}
	wetuwn 0;
}

static int snd_cs4236_put_doubwe1(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int weft_weg = kcontwow->pwivate_vawue & 0xff;
	int wight_weg = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 16) & 0x07;
	int shift_wight = (kcontwow->pwivate_vawue >> 19) & 0x07;
	int mask = (kcontwow->pwivate_vawue >> 24) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 22) & 1;
	int change;
	unsigned showt vaw1, vaw2;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	vaw1 <<= shift_weft;
	vaw2 <<= shift_wight;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw1 = (chip->image[weft_weg] & ~(mask << shift_weft)) | vaw1;
	vaw2 = (chip->eimage[CS4236_WEG(wight_weg)] & ~(mask << shift_wight)) | vaw2;
	change = vaw1 != chip->image[weft_weg] || vaw2 != chip->eimage[CS4236_WEG(wight_weg)];
	snd_wss_out(chip, weft_weg, vaw1);
	snd_cs4236_ext_out(chip, wight_weg, vaw2);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define CS4236_MASTEW_DIGITAW(xname, xindex, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4236_get_mastew_digitaw, .put = snd_cs4236_put_mastew_digitaw, \
  .pwivate_vawue = 71 << 24, \
  .twv = { .p = (xtwv) } }

static inwine int snd_cs4236_mixew_mastew_digitaw_invewt_vowume(int vow)
{
	wetuwn (vow < 64) ? 63 - vow : 64 + (71 - vow);
}

static int snd_cs4236_get_mastew_digitaw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = snd_cs4236_mixew_mastew_digitaw_invewt_vowume(chip->eimage[CS4236_WEG(CS4236_WEFT_MASTEW)] & 0x7f);
	ucontwow->vawue.integew.vawue[1] = snd_cs4236_mixew_mastew_digitaw_invewt_vowume(chip->eimage[CS4236_WEG(CS4236_WIGHT_MASTEW)] & 0x7f);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_cs4236_put_mastew_digitaw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt vaw1, vaw2;
	
	vaw1 = snd_cs4236_mixew_mastew_digitaw_invewt_vowume(ucontwow->vawue.integew.vawue[0] & 0x7f);
	vaw2 = snd_cs4236_mixew_mastew_digitaw_invewt_vowume(ucontwow->vawue.integew.vawue[1] & 0x7f);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw1 = (chip->eimage[CS4236_WEG(CS4236_WEFT_MASTEW)] & ~0x7f) | vaw1;
	vaw2 = (chip->eimage[CS4236_WEG(CS4236_WIGHT_MASTEW)] & ~0x7f) | vaw2;
	change = vaw1 != chip->eimage[CS4236_WEG(CS4236_WEFT_MASTEW)] || vaw2 != chip->eimage[CS4236_WEG(CS4236_WIGHT_MASTEW)];
	snd_cs4236_ext_out(chip, CS4236_WEFT_MASTEW, vaw1);
	snd_cs4236_ext_out(chip, CS4236_WIGHT_MASTEW, vaw2);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

#define CS4235_OUTPUT_ACCU(xname, xindex, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .info = snd_cs4236_info_doubwe, \
  .get = snd_cs4235_get_output_accu, .put = snd_cs4235_put_output_accu, \
  .pwivate_vawue = 3 << 24, \
  .twv = { .p = (xtwv) } }

static inwine int snd_cs4235_mixew_output_accu_get_vowume(int vow)
{
	switch ((vow >> 5) & 3) {
	case 0: wetuwn 1;
	case 1: wetuwn 3;
	case 2: wetuwn 2;
	case 3: wetuwn 0;
 	}
	wetuwn 3;
}

static inwine int snd_cs4235_mixew_output_accu_set_vowume(int vow)
{
	switch (vow & 3) {
	case 0: wetuwn 3 << 5;
	case 1: wetuwn 0 << 5;
	case 2: wetuwn 2 << 5;
	case 3: wetuwn 1 << 5;
	}
	wetuwn 1 << 5;
}

static int snd_cs4235_get_output_accu(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = snd_cs4235_mixew_output_accu_get_vowume(chip->image[CS4235_WEFT_MASTEW]);
	ucontwow->vawue.integew.vawue[1] = snd_cs4235_mixew_output_accu_get_vowume(chip->image[CS4235_WIGHT_MASTEW]);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_cs4235_put_output_accu(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt vaw1, vaw2;
	
	vaw1 = snd_cs4235_mixew_output_accu_set_vowume(ucontwow->vawue.integew.vawue[0]);
	vaw2 = snd_cs4235_mixew_output_accu_set_vowume(ucontwow->vawue.integew.vawue[1]);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw1 = (chip->image[CS4235_WEFT_MASTEW] & ~(3 << 5)) | vaw1;
	vaw2 = (chip->image[CS4235_WIGHT_MASTEW] & ~(3 << 5)) | vaw2;
	change = vaw1 != chip->image[CS4235_WEFT_MASTEW] || vaw2 != chip->image[CS4235_WIGHT_MASTEW];
	snd_wss_out(chip, CS4235_WEFT_MASTEW, vaw1);
	snd_wss_out(chip, CS4235_WIGHT_MASTEW, vaw2);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_7bit, -9450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_6bit, -9450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_6bit_12db_max, -8250, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit_12db_max, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit_22db_max, -2400, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_4bit, -4500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_2bit, -1800, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_wec_gain, 0, 150, 0);

static const stwuct snd_kcontwow_new snd_cs4236_contwows[] = {

CS4236_DOUBWE("Mastew Digitaw Pwayback Switch", 0,
		CS4236_WEFT_MASTEW, CS4236_WIGHT_MASTEW, 7, 7, 1, 1),
CS4236_DOUBWE("Mastew Digitaw Captuwe Switch", 0,
		CS4236_DAC_MUTE, CS4236_DAC_MUTE, 7, 6, 1, 1),
CS4236_MASTEW_DIGITAW("Mastew Digitaw Vowume", 0, db_scawe_7bit),

CS4236_DOUBWE_TWV("Captuwe Boost Vowume", 0,
		  CS4236_WEFT_MIX_CTWW, CS4236_WIGHT_MIX_CTWW, 5, 5, 3, 1,
		  db_scawe_2bit),

WSS_DOUBWE("PCM Pwayback Switch", 0,
		CS4231_WEFT_OUTPUT, CS4231_WIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("PCM Pwayback Vowume", 0,
		CS4231_WEFT_OUTPUT, CS4231_WIGHT_OUTPUT, 0, 0, 63, 1,
		db_scawe_6bit),

CS4236_DOUBWE("DSP Pwayback Switch", 0,
		CS4236_WEFT_DSP, CS4236_WIGHT_DSP, 7, 7, 1, 1),
CS4236_DOUBWE_TWV("DSP Pwayback Vowume", 0,
		  CS4236_WEFT_DSP, CS4236_WIGHT_DSP, 0, 0, 63, 1,
		  db_scawe_6bit),

CS4236_DOUBWE("FM Pwayback Switch", 0,
		CS4236_WEFT_FM, CS4236_WIGHT_FM, 7, 7, 1, 1),
CS4236_DOUBWE_TWV("FM Pwayback Vowume", 0,
		  CS4236_WEFT_FM, CS4236_WIGHT_FM, 0, 0, 63, 1,
		  db_scawe_6bit),

CS4236_DOUBWE("Wavetabwe Pwayback Switch", 0,
		CS4236_WEFT_WAVE, CS4236_WIGHT_WAVE, 7, 7, 1, 1),
CS4236_DOUBWE_TWV("Wavetabwe Pwayback Vowume", 0,
		  CS4236_WEFT_WAVE, CS4236_WIGHT_WAVE, 0, 0, 63, 1,
		  db_scawe_6bit_12db_max),

WSS_DOUBWE("Synth Pwayback Switch", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Synth Vowume", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),
WSS_DOUBWE("Synth Captuwe Switch", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 6, 6, 1, 1),
WSS_DOUBWE("Synth Captuwe Bypass", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 5, 5, 1, 1),

CS4236_DOUBWE("Mic Pwayback Switch", 0,
		CS4236_WEFT_MIC, CS4236_WIGHT_MIC, 6, 6, 1, 1),
CS4236_DOUBWE("Mic Captuwe Switch", 0,
		CS4236_WEFT_MIC, CS4236_WIGHT_MIC, 7, 7, 1, 1),
CS4236_DOUBWE_TWV("Mic Vowume", 0, CS4236_WEFT_MIC, CS4236_WIGHT_MIC,
		  0, 0, 31, 1, db_scawe_5bit_22db_max),
CS4236_DOUBWE("Mic Pwayback Boost (+20dB)", 0,
		CS4236_WEFT_MIC, CS4236_WIGHT_MIC, 5, 5, 1, 0),

WSS_DOUBWE("Wine Pwayback Switch", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Wine Vowume", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),
WSS_DOUBWE("Wine Captuwe Switch", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBWE("Wine Captuwe Bypass", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 5, 5, 1, 1),

WSS_DOUBWE("CD Pwayback Switch", 0,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("CD Vowume", 0,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),
WSS_DOUBWE("CD Captuwe Switch", 0,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 6, 6, 1, 1),

CS4236_DOUBWE1("Mono Output Pwayback Switch", 0,
		CS4231_MONO_CTWW, CS4236_WIGHT_MIX_CTWW, 6, 7, 1, 1),
CS4236_DOUBWE1("Beep Pwayback Switch", 0,
		CS4231_MONO_CTWW, CS4236_WEFT_MIX_CTWW, 7, 7, 1, 1),
WSS_SINGWE_TWV("Beep Pwayback Vowume", 0, CS4231_MONO_CTWW, 0, 15, 1,
		db_scawe_4bit),
WSS_SINGWE("Beep Bypass Pwayback Switch", 0, CS4231_MONO_CTWW, 5, 1, 0),

WSS_DOUBWE_TWV("Captuwe Vowume", 0, CS4231_WEFT_INPUT, CS4231_WIGHT_INPUT,
		0, 0, 15, 0, db_scawe_wec_gain),
WSS_DOUBWE("Anawog Woopback Captuwe Switch", 0,
		CS4231_WEFT_INPUT, CS4231_WIGHT_INPUT, 7, 7, 1, 0),

WSS_SINGWE("Woopback Digitaw Pwayback Switch", 0, CS4231_WOOPBACK, 0, 1, 0),
CS4236_DOUBWE1_TWV("Woopback Digitaw Pwayback Vowume", 0,
		   CS4231_WOOPBACK, CS4236_WIGHT_WOOPBACK, 2, 0, 63, 1,
		   db_scawe_6bit),
};

static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit_6db_max, -5600, 200, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_2bit_16db_max, -2400, 800, 0);

static const stwuct snd_kcontwow_new snd_cs4235_contwows[] = {

WSS_DOUBWE("Mastew Pwayback Switch", 0,
		CS4235_WEFT_MASTEW, CS4235_WIGHT_MASTEW, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Mastew Pwayback Vowume", 0,
		CS4235_WEFT_MASTEW, CS4235_WIGHT_MASTEW, 0, 0, 31, 1,
		db_scawe_5bit_6db_max),

CS4235_OUTPUT_ACCU("Pwayback Vowume", 0, db_scawe_2bit_16db_max),

WSS_DOUBWE("Synth Pwayback Switch", 1,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 7, 7, 1, 1),
WSS_DOUBWE("Synth Captuwe Switch", 1,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 6, 6, 1, 1),
WSS_DOUBWE_TWV("Synth Vowume", 1,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),

CS4236_DOUBWE_TWV("Captuwe Vowume", 0,
		  CS4236_WEFT_MIX_CTWW, CS4236_WIGHT_MIX_CTWW, 5, 5, 3, 1,
		  db_scawe_2bit),

WSS_DOUBWE("PCM Pwayback Switch", 0,
		CS4231_WEFT_OUTPUT, CS4231_WIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBWE("PCM Captuwe Switch", 0,
		CS4236_DAC_MUTE, CS4236_DAC_MUTE, 7, 6, 1, 1),
WSS_DOUBWE_TWV("PCM Vowume", 0,
		CS4231_WEFT_OUTPUT, CS4231_WIGHT_OUTPUT, 0, 0, 63, 1,
		db_scawe_6bit),

CS4236_DOUBWE("DSP Switch", 0, CS4236_WEFT_DSP, CS4236_WIGHT_DSP, 7, 7, 1, 1),

CS4236_DOUBWE("FM Switch", 0, CS4236_WEFT_FM, CS4236_WIGHT_FM, 7, 7, 1, 1),

CS4236_DOUBWE("Wavetabwe Switch", 0,
		CS4236_WEFT_WAVE, CS4236_WIGHT_WAVE, 7, 7, 1, 1),

CS4236_DOUBWE("Mic Captuwe Switch", 0,
		CS4236_WEFT_MIC, CS4236_WIGHT_MIC, 7, 7, 1, 1),
CS4236_DOUBWE("Mic Pwayback Switch", 0,
		CS4236_WEFT_MIC, CS4236_WIGHT_MIC, 6, 6, 1, 1),
CS4236_SINGWE_TWV("Mic Vowume", 0, CS4236_WEFT_MIC, 0, 31, 1,
		  db_scawe_5bit_22db_max),
CS4236_SINGWE("Mic Boost (+20dB)", 0, CS4236_WEFT_MIC, 5, 1, 0),

WSS_DOUBWE("Wine Pwayback Switch", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE("Wine Captuwe Switch", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBWE_TWV("Wine Vowume", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),

WSS_DOUBWE("CD Pwayback Switch", 1,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE("CD Captuwe Switch", 1,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBWE_TWV("CD Vowume", 1,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 0, 0, 31, 1,
		db_scawe_5bit_12db_max),

CS4236_DOUBWE1("Beep Pwayback Switch", 0,
		CS4231_MONO_CTWW, CS4236_WEFT_MIX_CTWW, 7, 7, 1, 1),
WSS_SINGWE("Beep Pwayback Vowume", 0, CS4231_MONO_CTWW, 0, 15, 1),

WSS_DOUBWE("Anawog Woopback Switch", 0,
		CS4231_WEFT_INPUT, CS4231_WIGHT_INPUT, 7, 7, 1, 0),
};

#define CS4236_IEC958_ENABWE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_singwe, \
  .get = snd_cs4236_get_iec958_switch, .put = snd_cs4236_put_iec958_switch, \
  .pwivate_vawue = 1 << 16 }

static int snd_cs4236_get_iec958_switch(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = chip->image[CS4231_AWT_FEATUWE_1] & 0x02 ? 1 : 0;
#if 0
	pwintk(KEWN_DEBUG "get vawid: AWT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_AWT_FEATUWE_1),
			snd_cs4236_ctww_in(chip, 3),
			snd_cs4236_ctww_in(chip, 4),
			snd_cs4236_ctww_in(chip, 5),
			snd_cs4236_ctww_in(chip, 6),
			snd_cs4236_ctww_in(chip, 8));
#endif
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int snd_cs4236_put_iec958_switch(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wss *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt enabwe, vaw;
	
	enabwe = ucontwow->vawue.integew.vawue[0] & 1;

	mutex_wock(&chip->mce_mutex);
	snd_wss_mce_up(chip);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = (chip->image[CS4231_AWT_FEATUWE_1] & ~0x0e) | (0<<2) | (enabwe << 1);
	change = vaw != chip->image[CS4231_AWT_FEATUWE_1];
	snd_wss_out(chip, CS4231_AWT_FEATUWE_1, vaw);
	vaw = snd_cs4236_ctww_in(chip, 4) | 0xc0;
	snd_cs4236_ctww_out(chip, 4, vaw);
	udeway(100);
	vaw &= ~0x40;
	snd_cs4236_ctww_out(chip, 4, vaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	snd_wss_mce_down(chip);
	mutex_unwock(&chip->mce_mutex);

#if 0
	pwintk(KEWN_DEBUG "set vawid: AWT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_AWT_FEATUWE_1),
			snd_cs4236_ctww_in(chip, 3),
			snd_cs4236_ctww_in(chip, 4),
			snd_cs4236_ctww_in(chip, 5),
			snd_cs4236_ctww_in(chip, 6),
			snd_cs4236_ctww_in(chip, 8));
#endif
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_cs4236_iec958_contwows[] = {
CS4236_IEC958_ENABWE("IEC958 Output Enabwe", 0),
CS4236_SINGWEC("IEC958 Output Vawidity", 0, 4, 4, 1, 0),
CS4236_SINGWEC("IEC958 Output Usew", 0, 4, 5, 1, 0),
CS4236_SINGWEC("IEC958 Output CSBW", 0, 4, 6, 1, 0),
CS4236_SINGWEC("IEC958 Output Channew Status Wow", 0, 5, 1, 127, 0),
CS4236_SINGWEC("IEC958 Output Channew Status High", 0, 6, 0, 255, 0)
};

static const stwuct snd_kcontwow_new snd_cs4236_3d_contwows_cs4235[] = {
CS4236_SINGWEC("3D Contwow - Switch", 0, 3, 4, 1, 0),
CS4236_SINGWEC("3D Contwow - Space", 0, 2, 4, 15, 1)
};

static const stwuct snd_kcontwow_new snd_cs4236_3d_contwows_cs4237[] = {
CS4236_SINGWEC("3D Contwow - Switch", 0, 3, 7, 1, 0),
CS4236_SINGWEC("3D Contwow - Space", 0, 2, 4, 15, 1),
CS4236_SINGWEC("3D Contwow - Centew", 0, 2, 0, 15, 1),
CS4236_SINGWEC("3D Contwow - Mono", 0, 3, 6, 1, 0),
CS4236_SINGWEC("3D Contwow - IEC958", 0, 3, 5, 1, 0)
};

static const stwuct snd_kcontwow_new snd_cs4236_3d_contwows_cs4238[] = {
CS4236_SINGWEC("3D Contwow - Switch", 0, 3, 4, 1, 0),
CS4236_SINGWEC("3D Contwow - Space", 0, 2, 4, 15, 1),
CS4236_SINGWEC("3D Contwow - Vowume", 0, 2, 0, 15, 1),
CS4236_SINGWEC("3D Contwow - IEC958", 0, 3, 5, 1, 0)
};

int snd_cs4236_mixew(stwuct snd_wss *chip)
{
	stwuct snd_cawd *cawd;
	unsigned int idx, count;
	int eww;
	const stwuct snd_kcontwow_new *kcontwow;

	if (snd_BUG_ON(!chip || !chip->cawd))
		wetuwn -EINVAW;
	cawd = chip->cawd;
	stwcpy(cawd->mixewname, snd_wss_chip_id(chip));

	if (chip->hawdwawe == WSS_HW_CS4235 ||
	    chip->hawdwawe == WSS_HW_CS4239) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_cs4235_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cs4235_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		fow (idx = 0; idx < AWWAY_SIZE(snd_cs4236_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cs4236_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	switch (chip->hawdwawe) {
	case WSS_HW_CS4235:
	case WSS_HW_CS4239:
		count = AWWAY_SIZE(snd_cs4236_3d_contwows_cs4235);
		kcontwow = snd_cs4236_3d_contwows_cs4235;
		bweak;
	case WSS_HW_CS4237B:
		count = AWWAY_SIZE(snd_cs4236_3d_contwows_cs4237);
		kcontwow = snd_cs4236_3d_contwows_cs4237;
		bweak;
	case WSS_HW_CS4238B:
		count = AWWAY_SIZE(snd_cs4236_3d_contwows_cs4238);
		kcontwow = snd_cs4236_3d_contwows_cs4238;
		bweak;
	defauwt:
		count = 0;
		kcontwow = NUWW;
	}
	fow (idx = 0; idx < count; idx++, kcontwow++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(kcontwow, chip));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->hawdwawe == WSS_HW_CS4237B ||
	    chip->hawdwawe == WSS_HW_CS4238B) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_cs4236_iec958_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cs4236_iec958_contwows[idx], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}
