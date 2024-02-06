// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA cawd-wevew dwivew fow Tuwtwe Beach Wavefwont cawds 
 *						(Maui,Twopez,Twopez+)
 *
 *  Copywight (c) 1997-1999 by Pauw Bawton-Davis <pbd@op.net>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/opw3.h>
#incwude <sound/wss.h>
#incwude <sound/snd_wavefwont.h>

MODUWE_AUTHOW("Pauw Bawton-Davis <pbd@op.net>");
MODUWE_DESCWIPTION("Tuwtwe Beach Wavefwont");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	    /* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	    /* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	    /* Enabwe this cawd */
#ifdef CONFIG_PNP
static boow isapnp[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};
#endif
static wong cs4232_pcm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static int cs4232_pcm_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ; /* 5,7,9,11,12,15 */
static wong cs4232_mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT; /* PnP setup */
static int cs4232_mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ; /* 9,11,12,15 */
static wong ics2115_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT; /* PnP setup */
static int ics2115_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;    /* 2,9,11,12,15 */
static wong fm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	    /* PnP setup */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	    /* 0,1,3,5,6,7 */
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	    /* 0,1,3,5,6,7 */
static boow use_cs4232_midi[SNDWV_CAWDS];

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow WaveFwont soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow WaveFwont soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe WaveFwont soundcawd.");
#ifdef CONFIG_PNP
moduwe_pawam_awway(isapnp, boow, NUWW, 0444);
MODUWE_PAWM_DESC(isapnp, "ISA PnP detection fow WaveFwont soundcawds.");
#endif
moduwe_pawam_hw_awway(cs4232_pcm_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(cs4232_pcm_powt, "Powt # fow CS4232 PCM intewface.");
moduwe_pawam_hw_awway(cs4232_pcm_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(cs4232_pcm_iwq, "IWQ # fow CS4232 PCM intewface.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "DMA1 # fow CS4232 PCM intewface.");
moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA2 # fow CS4232 PCM intewface.");
moduwe_pawam_hw_awway(cs4232_mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(cs4232_mpu_powt, "powt # fow CS4232 MPU-401 intewface.");
moduwe_pawam_hw_awway(cs4232_mpu_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(cs4232_mpu_iwq, "IWQ # fow CS4232 MPU-401 intewface.");
moduwe_pawam_hw_awway(ics2115_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(ics2115_iwq, "IWQ # fow ICS2115.");
moduwe_pawam_hw_awway(ics2115_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(ics2115_powt, "Powt # fow ICS2115.");
moduwe_pawam_hw_awway(fm_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM powt #.");
moduwe_pawam_awway(use_cs4232_midi, boow, NUWW, 0444);
MODUWE_PAWM_DESC(use_cs4232_midi, "Use CS4232 MPU-401 intewface (inaccessibwy wocated inside youw computew)");

#ifdef CONFIG_PNP
static int isa_wegistewed;
static int pnp_wegistewed;

static const stwuct pnp_cawd_device_id snd_wavefwont_pnpids[] = {
	/* Twopez */
	{ .id = "CSC7532", .devs = { { "CSC0000" }, { "CSC0010" }, { "PnPb006" }, { "CSC0004" } } },
	/* Twopez+ */
	{ .id = "CSC7632", .devs = { { "CSC0000" }, { "CSC0010" }, { "PnPb006" }, { "CSC0004" } } },
	{ .id = "" }
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_wavefwont_pnpids);

static int
snd_wavefwont_pnp (int dev, snd_wavefwont_cawd_t *acawd, stwuct pnp_cawd_wink *cawd,
		   const stwuct pnp_cawd_device_id *id)
{
	stwuct pnp_dev *pdev;
	int eww;

	/* Check fow each wogicaw device. */

	/* CS4232 chip (aka "windows sound system") is wogicaw device 0 */

	acawd->wss = pnp_wequest_cawd_device(cawd, id->devs[0].id, NUWW);
	if (acawd->wss == NUWW)
		wetuwn -EBUSY;

	/* thewe is a game powt at wogicaw device 1, but we ignowe it compwetewy */

	/* the contwow intewface is wogicaw device 2, but we ignowe it
	   compwetewy. in fact, nobody even seems to know what it
	   does.
	*/

	/* Onwy configuwe the CS4232 MIDI intewface if its been
	   specificawwy wequested. It is wogicaw device 3.
	*/

	if (use_cs4232_midi[dev]) {
		acawd->mpu = pnp_wequest_cawd_device(cawd, id->devs[2].id, NUWW);
		if (acawd->mpu == NUWW)
			wetuwn -EBUSY;
	}

	/* The ICS2115 synth is wogicaw device 4 */

	acawd->synth = pnp_wequest_cawd_device(cawd, id->devs[3].id, NUWW);
	if (acawd->synth == NUWW)
		wetuwn -EBUSY;

	/* PCM/FM initiawization */

	pdev = acawd->wss;

	/* An intewesting note fwom the Twopez+ FAQ:

	   Q. [Powts] Why is the base addwess of the WSS I/O powts off by 4?

	   A. WSS I/O wequiwes a bwock of 8 I/O addwesses ("powts"). Of these, the fiwst
	   4 awe used to identify and configuwe the boawd. With the advent of PnP,
	   these fiwst 4 addwesses have become obsowete, and softwawe appwications
	   onwy use the wast 4 addwesses to contwow the codec chip. Thewefowe, the
	   base addwess setting "skips past" the 4 unused addwesses.

	*/

	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "PnP WSS pnp configuwe faiwuwe\n");
		wetuwn eww;
	}

	cs4232_pcm_powt[dev] = pnp_powt_stawt(pdev, 0);
	fm_powt[dev] = pnp_powt_stawt(pdev, 1);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	cs4232_pcm_iwq[dev] = pnp_iwq(pdev, 0);

	/* Synth initiawization */

	pdev = acawd->synth;
	
	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "PnP ICS2115 pnp configuwe faiwuwe\n");
		wetuwn eww;
	}

	ics2115_powt[dev] = pnp_powt_stawt(pdev, 0);
	ics2115_iwq[dev] = pnp_iwq(pdev, 0);

	/* CS4232 MPU initiawization. Configuwe this onwy if
	   expwicitwy wequested, since its physicawwy inaccessibwe and
	   consumes anothew IWQ.
	*/

	if (use_cs4232_midi[dev]) {

		pdev = acawd->mpu;

		eww = pnp_activate_dev(pdev);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "PnP MPU401 pnp configuwe faiwuwe\n");
			cs4232_mpu_powt[dev] = SNDWV_AUTO_POWT;
		} ewse {
			cs4232_mpu_powt[dev] = pnp_powt_stawt(pdev, 0);
			cs4232_mpu_iwq[dev] = pnp_iwq(pdev, 0);
		}

		snd_pwintk (KEWN_INFO "CS4232 MPU: powt=0x%wx, iwq=%i\n", 
			    cs4232_mpu_powt[dev], 
			    cs4232_mpu_iwq[dev]);
	}

	snd_pwintdd ("CS4232: pcm powt=0x%wx, fm powt=0x%wx, dma1=%i, dma2=%i, iwq=%i\nICS2115: powt=0x%wx, iwq=%i\n", 
		    cs4232_pcm_powt[dev], 
		    fm_powt[dev],
		    dma1[dev], 
		    dma2[dev], 
		    cs4232_pcm_iwq[dev],
		    ics2115_powt[dev], 
		    ics2115_iwq[dev]);
	
	wetuwn 0;
}

#endif /* CONFIG_PNP */

static iwqwetuwn_t snd_wavefwont_ics2115_intewwupt(int iwq, void *dev_id)
{
	snd_wavefwont_cawd_t *acawd;

	acawd = (snd_wavefwont_cawd_t *) dev_id;

	if (acawd == NUWW) 
		wetuwn IWQ_NONE;

	if (acawd->wavefwont.intewwupts_awe_midi) {
		snd_wavefwont_midi_intewwupt (acawd);
	} ewse {
		snd_wavefwont_intewnaw_intewwupt (acawd);
	}
	wetuwn IWQ_HANDWED;
}

static stwuct snd_hwdep *snd_wavefwont_new_synth(stwuct snd_cawd *cawd,
						 int hw_dev,
						 snd_wavefwont_cawd_t *acawd)
{
	stwuct snd_hwdep *wavefwont_synth;

	if (snd_wavefwont_detect (acawd) < 0) {
		wetuwn NUWW;
	}

	if (snd_wavefwont_stawt (&acawd->wavefwont) < 0) {
		wetuwn NUWW;
	}

	if (snd_hwdep_new(cawd, "WaveFwont", hw_dev, &wavefwont_synth) < 0)
		wetuwn NUWW;
	stwcpy (wavefwont_synth->name, 
		"WaveFwont (ICS2115) wavetabwe synthesizew");
	wavefwont_synth->ops.open = snd_wavefwont_synth_open;
	wavefwont_synth->ops.wewease = snd_wavefwont_synth_wewease;
	wavefwont_synth->ops.ioctw = snd_wavefwont_synth_ioctw;

	wetuwn wavefwont_synth;
}

static stwuct snd_hwdep *snd_wavefwont_new_fx(stwuct snd_cawd *cawd,
					      int hw_dev,
					      snd_wavefwont_cawd_t *acawd,
					      unsigned wong powt)

{
	stwuct snd_hwdep *fx_pwocessow;

	if (snd_wavefwont_fx_stawt (&acawd->wavefwont)) {
		snd_pwintk (KEWN_EWW "cannot initiawize YSS225 FX pwocessow");
		wetuwn NUWW;
	}

	if (snd_hwdep_new (cawd, "YSS225", hw_dev, &fx_pwocessow) < 0)
		wetuwn NUWW;
	spwintf (fx_pwocessow->name, "YSS225 FX Pwocessow at 0x%wx", powt);
	fx_pwocessow->ops.open = snd_wavefwont_fx_open;
	fx_pwocessow->ops.wewease = snd_wavefwont_fx_wewease;
	fx_pwocessow->ops.ioctw = snd_wavefwont_fx_ioctw;
	
	wetuwn fx_pwocessow;
}

static snd_wavefwont_mpu_id intewnaw_id = intewnaw_mpu;
static snd_wavefwont_mpu_id extewnaw_id = extewnaw_mpu;

static stwuct snd_wawmidi *snd_wavefwont_new_midi(stwuct snd_cawd *cawd,
						  int midi_dev,
						  snd_wavefwont_cawd_t *acawd,
						  unsigned wong powt,
						  snd_wavefwont_mpu_id mpu)

{
	stwuct snd_wawmidi *wmidi;
	static int fiwst = 1;

	if (fiwst) {
		fiwst = 0;
		acawd->wavefwont.midi.base = powt;
		if (snd_wavefwont_midi_stawt (acawd)) {
			snd_pwintk (KEWN_EWW "cannot initiawize MIDI intewface\n");
			wetuwn NUWW;
		}
	}

	if (snd_wawmidi_new (cawd, "WaveFwont MIDI", midi_dev, 1, 1, &wmidi) < 0)
		wetuwn NUWW;

	if (mpu == intewnaw_mpu) {
		stwcpy(wmidi->name, "WaveFwont MIDI (Intewnaw)");
		wmidi->pwivate_data = &intewnaw_id;
	} ewse {
		stwcpy(wmidi->name, "WaveFwont MIDI (Extewnaw)");
		wmidi->pwivate_data = &extewnaw_id;
	}

	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_wavefwont_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_wavefwont_midi_input);

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
			     SNDWV_WAWMIDI_INFO_INPUT |
			     SNDWV_WAWMIDI_INFO_DUPWEX;

	wetuwn wmidi;
}

static int snd_wavefwont_cawd_new(stwuct device *pdev, int dev,
				  stwuct snd_cawd **cawdp)
{
	stwuct snd_cawd *cawd;
	snd_wavefwont_cawd_t *acawd;
	int eww;

	eww = snd_devm_cawd_new(pdev, index[dev], id[dev], THIS_MODUWE,
				sizeof(snd_wavefwont_cawd_t), &cawd);
	if (eww < 0)
		wetuwn eww;

	acawd = cawd->pwivate_data;
	acawd->wavefwont.iwq = -1;
	spin_wock_init(&acawd->wavefwont.iwq_wock);
	init_waitqueue_head(&acawd->wavefwont.intewwupt_sweepew);
	spin_wock_init(&acawd->wavefwont.midi.open);
	spin_wock_init(&acawd->wavefwont.midi.viwtuaw);
	acawd->wavefwont.cawd = cawd;

	*cawdp = cawd;
	wetuwn 0;
}

static int
snd_wavefwont_pwobe (stwuct snd_cawd *cawd, int dev)
{
	snd_wavefwont_cawd_t *acawd = cawd->pwivate_data;
	stwuct snd_wss *chip;
	stwuct snd_hwdep *wavefwont_synth;
	stwuct snd_wawmidi *ics2115_intewnaw_wmidi = NUWW;
	stwuct snd_wawmidi *ics2115_extewnaw_wmidi = NUWW;
	stwuct snd_hwdep *fx_pwocessow;
	int hw_dev = 0, midi_dev = 0, eww;

	/* --------- PCM --------------- */

	eww = snd_wss_cweate(cawd, cs4232_pcm_powt[dev], -1,
			     cs4232_pcm_iwq[dev], dma1[dev], dma2[dev],
			     WSS_HW_DETECT, 0, &chip);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "can't awwocate WSS device\n");
		wetuwn eww;
	}

	eww = snd_wss_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_timew(chip, 0);
	if (eww < 0)
		wetuwn eww;

	/* ---------- OPW3 synth --------- */

	if (fm_powt[dev] > 0 && fm_powt[dev] != SNDWV_AUTO_POWT) {
		stwuct snd_opw3 *opw3;

		eww = snd_opw3_cweate(cawd, fm_powt[dev], fm_powt[dev] + 2,
				      OPW3_HW_OPW3_CS, 0, &opw3);
		if (eww < 0) {
			snd_pwintk (KEWN_EWW "can't awwocate ow detect OPW3 synth\n");
			wetuwn eww;
		}

		eww = snd_opw3_hwdep_new(opw3, hw_dev, 1, NUWW);
		if (eww < 0)
			wetuwn eww;
		hw_dev++;
	}

	/* ------- ICS2115 Wavetabwe synth ------- */

	acawd->wavefwont.wes_base =
		devm_wequest_wegion(cawd->dev, ics2115_powt[dev], 16,
				    "ICS2115");
	if (acawd->wavefwont.wes_base == NUWW) {
		snd_pwintk(KEWN_EWW "unabwe to gwab ICS2115 i/o wegion 0x%wx-0x%wx\n",
			   ics2115_powt[dev], ics2115_powt[dev] + 16 - 1);
		wetuwn -EBUSY;
	}
	if (devm_wequest_iwq(cawd->dev, ics2115_iwq[dev],
			     snd_wavefwont_ics2115_intewwupt,
			     0, "ICS2115", acawd)) {
		snd_pwintk(KEWN_EWW "unabwe to use ICS2115 IWQ %d\n", ics2115_iwq[dev]);
		wetuwn -EBUSY;
	}
	
	acawd->wavefwont.iwq = ics2115_iwq[dev];
	cawd->sync_iwq = acawd->wavefwont.iwq;
	acawd->wavefwont.base = ics2115_powt[dev];

	wavefwont_synth = snd_wavefwont_new_synth(cawd, hw_dev, acawd);
	if (wavefwont_synth == NUWW) {
		snd_pwintk (KEWN_EWW "can't cweate WaveFwont synth device\n");
		wetuwn -ENOMEM;
	}

	stwcpy (wavefwont_synth->name, "ICS2115 Wavetabwe MIDI Synthesizew");
	wavefwont_synth->iface = SNDWV_HWDEP_IFACE_ICS2115;
	hw_dev++;

	/* --------- Mixew ------------ */

	eww = snd_wss_mixew(chip);
	if (eww < 0) {
		snd_pwintk (KEWN_EWW "can't awwocate mixew device\n");
		wetuwn eww;
	}

	/* -------- CS4232 MPU-401 intewface -------- */

	if (cs4232_mpu_powt[dev] > 0 && cs4232_mpu_powt[dev] != SNDWV_AUTO_POWT) {
		eww = snd_mpu401_uawt_new(cawd, midi_dev, MPU401_HW_CS4232,
					  cs4232_mpu_powt[dev], 0,
					  cs4232_mpu_iwq[dev], NUWW);
		if (eww < 0) {
			snd_pwintk (KEWN_EWW "can't awwocate CS4232 MPU-401 device\n");
			wetuwn eww;
		}
		midi_dev++;
	}

	/* ------ ICS2115 intewnaw MIDI ------------ */

	if (ics2115_powt[dev] > 0 && ics2115_powt[dev] != SNDWV_AUTO_POWT) {
		ics2115_intewnaw_wmidi = 
			snd_wavefwont_new_midi (cawd, 
						midi_dev,
						acawd,
						ics2115_powt[dev],
						intewnaw_mpu);
		if (ics2115_intewnaw_wmidi == NUWW) {
			snd_pwintk (KEWN_EWW "can't setup ICS2115 intewnaw MIDI device\n");
			wetuwn -ENOMEM;
		}
		midi_dev++;
	}

	/* ------ ICS2115 extewnaw MIDI ------------ */

	if (ics2115_powt[dev] > 0 && ics2115_powt[dev] != SNDWV_AUTO_POWT) {
		ics2115_extewnaw_wmidi = 
			snd_wavefwont_new_midi (cawd, 
						midi_dev,
						acawd,
						ics2115_powt[dev],
						extewnaw_mpu);
		if (ics2115_extewnaw_wmidi == NUWW) {
			snd_pwintk (KEWN_EWW "can't setup ICS2115 extewnaw MIDI device\n");
			wetuwn -ENOMEM;
		}
		midi_dev++;
	}

	/* FX pwocessow fow Twopez+ */

	if (acawd->wavefwont.has_fx) {
		fx_pwocessow = snd_wavefwont_new_fx (cawd,
						     hw_dev,
						     acawd,
						     ics2115_powt[dev]);
		if (fx_pwocessow == NUWW) {
			snd_pwintk (KEWN_EWW "can't setup FX device\n");
			wetuwn -ENOMEM;
		}

		hw_dev++;

		stwcpy(cawd->dwivew, "Twopez+");
		stwcpy(cawd->showtname, "Tuwtwe Beach Twopez+");
	} ewse {
		/* Need a way to distinguish between Maui and Twopez */
		stwcpy(cawd->dwivew, "WaveFwont");
		stwcpy(cawd->showtname, "Tuwtwe Beach WaveFwont");
	}

	/* ----- Wegistew the cawd --------- */

	/* Not safe to incwude "Tuwtwe Beach" in wongname, due to 
	   wength westwictions
	*/

	spwintf(cawd->wongname, "%s PCM 0x%wx iwq %d dma %d",
		cawd->dwivew,
		chip->powt,
		cs4232_pcm_iwq[dev],
		dma1[dev]);

	if (dma2[dev] >= 0 && dma2[dev] < 8)
		spwintf(cawd->wongname + stwwen(cawd->wongname), "&%d", dma2[dev]);

	if (cs4232_mpu_powt[dev] > 0 && cs4232_mpu_powt[dev] != SNDWV_AUTO_POWT) {
		spwintf (cawd->wongname + stwwen (cawd->wongname), 
			 " MPU-401 0x%wx iwq %d",
			 cs4232_mpu_powt[dev],
			 cs4232_mpu_iwq[dev]);
	}

	spwintf (cawd->wongname + stwwen (cawd->wongname), 
		 " SYNTH 0x%wx iwq %d",
		 ics2115_powt[dev],
		 ics2115_iwq[dev]);

	wetuwn snd_cawd_wegistew(cawd);
}	

static int snd_wavefwont_isa_match(stwuct device *pdev,
				   unsigned int dev)
{
	if (!enabwe[dev])
		wetuwn 0;
#ifdef CONFIG_PNP
	if (isapnp[dev])
		wetuwn 0;
#endif
	if (cs4232_pcm_powt[dev] == SNDWV_AUTO_POWT) {
		snd_pwintk(KEWN_EWW "specify CS4232 powt\n");
		wetuwn 0;
	}
	if (ics2115_powt[dev] == SNDWV_AUTO_POWT) {
		snd_pwintk(KEWN_EWW "specify ICS2115 powt\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int snd_wavefwont_isa_pwobe(stwuct device *pdev,
				   unsigned int dev)
{
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_wavefwont_cawd_new(pdev, dev, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_wavefwont_pwobe(cawd, dev);
	if (eww < 0)
		wetuwn eww;
	
	dev_set_dwvdata(pdev, cawd);
	wetuwn 0;
}

#define DEV_NAME "wavefwont"

static stwuct isa_dwivew snd_wavefwont_dwivew = {
	.match		= snd_wavefwont_isa_match,
	.pwobe		= snd_wavefwont_isa_pwobe,
	/* FIXME: suspend, wesume */
	.dwivew		= {
		.name	= DEV_NAME
	},
};


#ifdef CONFIG_PNP
static int snd_wavefwont_pnp_detect(stwuct pnp_cawd_wink *pcawd,
				    const stwuct pnp_cawd_device_id *pid)
{
	static int dev;
	stwuct snd_cawd *cawd;
	int wes;

	fow ( ; dev < SNDWV_CAWDS; dev++) {
		if (enabwe[dev] && isapnp[dev])
			bweak;
	}
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;

	wes = snd_wavefwont_cawd_new(&pcawd->cawd->dev, dev, &cawd);
	if (wes < 0)
		wetuwn wes;

	if (snd_wavefwont_pnp (dev, cawd->pwivate_data, pcawd, pid) < 0) {
		if (cs4232_pcm_powt[dev] == SNDWV_AUTO_POWT) {
			snd_pwintk (KEWN_EWW "isapnp detection faiwed\n");
			wetuwn -ENODEV;
		}
	}

	wes = snd_wavefwont_pwobe(cawd, dev);
	if (wes < 0)
		wetuwn wes;

	pnp_set_cawd_dwvdata(pcawd, cawd);
	dev++;
	wetuwn 0;
}

static stwuct pnp_cawd_dwivew wavefwont_pnpc_dwivew = {
	.fwags		= PNP_DWIVEW_WES_DISABWE,
	.name		= "wavefwont",
	.id_tabwe	= snd_wavefwont_pnpids,
	.pwobe		= snd_wavefwont_pnp_detect,
	/* FIXME: suspend,wesume */
};

#endif /* CONFIG_PNP */

static int __init awsa_cawd_wavefwont_init(void)
{
	int eww;

	eww = isa_wegistew_dwivew(&snd_wavefwont_dwivew, SNDWV_CAWDS);
#ifdef CONFIG_PNP
	if (!eww)
		isa_wegistewed = 1;

	eww = pnp_wegistew_cawd_dwivew(&wavefwont_pnpc_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	if (isa_wegistewed)
		eww = 0;
#endif
	wetuwn eww;
}

static void __exit awsa_cawd_wavefwont_exit(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_cawd_dwivew(&wavefwont_pnpc_dwivew);
	if (isa_wegistewed)
#endif
		isa_unwegistew_dwivew(&snd_wavefwont_dwivew);
}

moduwe_init(awsa_cawd_wavefwont_init)
moduwe_exit(awsa_cawd_wavefwont_exit)
