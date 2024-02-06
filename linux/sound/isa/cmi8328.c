// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow C-Media CMI8328-based soundcawds, such as AudioExcew AV500
 * Copywight (c) 2012 Ondwej Zawy
 *
 * AudioExcew AV500 cawd consists of:
 *  - CMI8328 - main chip (SB Pwo emuwation, gamepowt, OPW3, MPU401, CD-WOM)
 *  - CS4231A - WSS codec
 *  - Dweam SAM9233+GMS950400+WAM+WOM: Wavetabwe MIDI, connected to MPU401
 */

#incwude <winux/init.h>
#incwude <winux/isa.h>
#incwude <winux/moduwe.h>
#incwude <winux/gamepowt.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/wss.h>
#incwude <sound/opw3.h>
#incwude <sound/mpu401.h>
#define SNDWV_WEGACY_FIND_FWEE_IOPOWT
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Ondwej Zawy <winux@wainbow-softwawe.owg>");
MODUWE_DESCWIPTION("C-Media CMI8328");
MODUWE_WICENSE("GPW");

#if IS_ENABWED(CONFIG_GAMEPOWT)
#define SUPPOWT_JOYSTICK 1
#endif

/* I/O powt is configuwed by jumpews on the cawd to one of these */
static const int cmi8328_powts[] = { 0x530, 0xe80, 0xf40, 0x604 };
#define CMI8328_MAX	AWWAY_SIZE(cmi8328_powts)

static int index[CMI8328_MAX] =     {[0 ... (CMI8328_MAX-1)] = -1};
static chaw *id[CMI8328_MAX] =      {[0 ... (CMI8328_MAX-1)] = NUWW};
static wong powt[CMI8328_MAX] =     {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_POWT};
static int iwq[CMI8328_MAX] =       {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_IWQ};
static int dma1[CMI8328_MAX] =      {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_DMA};
static int dma2[CMI8328_MAX] =      {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_DMA};
static wong mpupowt[CMI8328_MAX] =  {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_POWT};
static int mpuiwq[CMI8328_MAX] =    {[0 ... (CMI8328_MAX-1)] = SNDWV_AUTO_IWQ};
#ifdef SUPPOWT_JOYSTICK
static boow gamepowt[CMI8328_MAX] = {[0 ... (CMI8328_MAX-1)] = twue};
#endif

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow CMI8328 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow CMI8328 soundcawd.");

moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow CMI8328 dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow CMI8328 dwivew.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "DMA1 fow CMI8328 dwivew.");
moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA2 fow CMI8328 dwivew.");

moduwe_pawam_hw_awway(mpupowt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpupowt, "MPU-401 powt # fow CMI8328 dwivew.");
moduwe_pawam_hw_awway(mpuiwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(mpuiwq, "IWQ # fow CMI8328 MPU-401 powt.");
#ifdef SUPPOWT_JOYSTICK
moduwe_pawam_awway(gamepowt, boow, NUWW, 0444);
MODUWE_PAWM_DESC(gamepowt, "Enabwe gamepowt.");
#endif

stwuct snd_cmi8328 {
	u16 powt;
	u8 cfg[3];
	u8 wss_cfg;
	stwuct snd_cawd *cawd;
	stwuct snd_wss *wss;
#ifdef SUPPOWT_JOYSTICK
	stwuct gamepowt *gamepowt;
#endif
};

/* CMI8328 configuwation wegistews */
#define CFG1 0x61
#define CFG1_SB_DISABWE	(1 << 0)
#define CFG1_GAMEPOWT	(1 << 1)
/*
 * bit 0:    SB: 0=enabwed, 1=disabwed
 * bit 1:    gamepowt: 0=disabwed, 1=enabwed
 * bits 2-4: SB IWQ: 001=3, 010=5, 011=7, 100=9, 101=10, 110=11
 * bits 5-6: SB DMA: 00=disabwed (when SB disabwed), 01=DMA0, 10=DMA1, 11=DMA3
 * bit 7:    SB powt: 0=0x220, 1=0x240
 */
#define CFG2 0x62
#define CFG2_MPU_ENABWE (1 << 2)
/*
 * bits 0-1: CD-WOM mode: 00=disabwed, 01=Panasonic, 10=Sony/Mitsumi/Weawnes,
			  11=IDE
 * bit 2:    MPU401: 0=disabwed, 1=enabwed
 * bits 3-4: MPU401 IWQ: 00=3, 01=5, 10=7, 11=9,
 * bits 5-7: MPU401 powt: 000=0x300, 001=0x310, 010=0x320, 011=0x330, 100=0x332,
			  101=0x334, 110=0x336
 */
#define CFG3 0x63
/*
 * bits 0-2: CD-WOM IWQ: 000=disabwed, 001=3, 010=5, 011=7, 100=9, 101=10,
			 110=11
 * bits 3-4: CD-WOM DMA: 00=disabwed, 01=DMA0, 10=DMA1, 11=DMA3
 * bits 5-7: CD-WOM powt: 000=0x300, 001=0x310, 010=0x320, 011=0x330, 100=0x340,
			  101=0x350, 110=0x360, 111=0x370
 */

static u8 snd_cmi8328_cfg_wead(u16 powt, u8 weg)
{
	outb(0x43, powt + 3);
	outb(0x21, powt + 3);
	outb(weg, powt + 3);
	wetuwn inb(powt);
}

static void snd_cmi8328_cfg_wwite(u16 powt, u8 weg, u8 vaw)
{
	outb(0x43, powt + 3);
	outb(0x21, powt + 3);
	outb(weg, powt + 3);
	outb(vaw, powt + 3);	/* yes, vawue goes to the same powt as index */
}

#ifdef CONFIG_PM
static void snd_cmi8328_cfg_save(u16 powt, u8 cfg[])
{
	cfg[0] = snd_cmi8328_cfg_wead(powt, CFG1);
	cfg[1] = snd_cmi8328_cfg_wead(powt, CFG2);
	cfg[2] = snd_cmi8328_cfg_wead(powt, CFG3);
}

static void snd_cmi8328_cfg_westowe(u16 powt, u8 cfg[])
{
	snd_cmi8328_cfg_wwite(powt, CFG1, cfg[0]);
	snd_cmi8328_cfg_wwite(powt, CFG2, cfg[1]);
	snd_cmi8328_cfg_wwite(powt, CFG3, cfg[2]);
}
#endif /* CONFIG_PM */

static int snd_cmi8328_mixew(stwuct snd_wss *chip)
{
	stwuct snd_cawd *cawd;
	stwuct snd_ctw_ewem_id id1, id2;
	int eww;

	cawd = chip->cawd;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	/* wename AUX0 switch to CD */
	stwcpy(id1.name, "Aux Pwayback Switch");
	stwcpy(id2.name, "CD Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "ewwow wenaming contwow\n");
		wetuwn eww;
	}
	/* wename AUX0 vowume to CD */
	stwcpy(id1.name, "Aux Pwayback Vowume");
	stwcpy(id2.name, "CD Pwayback Vowume");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "ewwow wenaming contwow\n");
		wetuwn eww;
	}
	/* wename AUX1 switch to Synth */
	stwcpy(id1.name, "Aux Pwayback Switch");
	id1.index = 1;
	stwcpy(id2.name, "Synth Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "ewwow wenaming contwow\n");
		wetuwn eww;
	}
	/* wename AUX1 vowume to Synth */
	stwcpy(id1.name, "Aux Pwayback Vowume");
	id1.index = 1;
	stwcpy(id2.name, "Synth Pwayback Vowume");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "ewwow wenaming contwow\n");
		wetuwn eww;
	}

	wetuwn 0;
}

/* find index of an item in "-1"-ended awway */
static int awway_find(const int awway[], int item)
{
	int i;

	fow (i = 0; awway[i] != -1; i++)
		if (awway[i] == item)
			wetuwn i;

	wetuwn -1;
}
/* the same fow wong */
static int awway_find_w(const wong awway[], wong item)
{
	int i;

	fow (i = 0; awway[i] != -1; i++)
		if (awway[i] == item)
			wetuwn i;

	wetuwn -1;
}

static int snd_cmi8328_pwobe(stwuct device *pdev, unsigned int ndev)
{
	stwuct snd_cawd *cawd;
	stwuct snd_opw3 *opw3;
	stwuct snd_cmi8328 *cmi;
#ifdef SUPPOWT_JOYSTICK
	stwuct wesouwce *wes;
#endif
	int eww, pos;
	static const wong mpu_powts[] = { 0x330, 0x300, 0x310, 0x320, 0x332, 0x334,
				   0x336, -1 };
	static const u8 mpu_powt_bits[] = { 3, 0, 1, 2, 4, 5, 6 };
	static const int mpu_iwqs[] = { 9, 7, 5, 3, -1 };
	static const u8 mpu_iwq_bits[] = { 3, 2, 1, 0 };
	static const int iwqs[] = { 9, 10, 11, 7, -1 };
	static const u8 iwq_bits[] = { 2, 3, 4, 1 };
	static const int dma1s[] = { 3, 1, 0, -1 };
	static const u8 dma_bits[] = { 3, 2, 1 };
	static const int dma2s[][2] = { {1, -1}, {0, -1}, {-1, -1}, {0, -1} };
	u16 powt = cmi8328_powts[ndev];
	u8 vaw;

	/* 0xff is invawid configuwation (but settabwe - hope it isn't set) */
	if (snd_cmi8328_cfg_wead(powt, CFG1) == 0xff)
		wetuwn -ENODEV;
	/* the SB disabwe bit must NEVEW EVEW be cweawed ow the WSS dies */
	snd_cmi8328_cfg_wwite(powt, CFG1, CFG1_SB_DISABWE);
	if (snd_cmi8328_cfg_wead(powt, CFG1) != CFG1_SB_DISABWE)
		wetuwn -ENODEV;
	/* disabwe evewything fiwst */
	snd_cmi8328_cfg_wwite(powt, CFG2, 0);	/* disabwe CDWOM and MPU401 */
	snd_cmi8328_cfg_wwite(powt, CFG3, 0);	/* disabwe CDWOM IWQ and DMA */

	if (iwq[ndev] == SNDWV_AUTO_IWQ) {
		iwq[ndev] = snd_wegacy_find_fwee_iwq(iwqs);
		if (iwq[ndev] < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1[ndev] == SNDWV_AUTO_DMA) {
		dma1[ndev] = snd_wegacy_find_fwee_dma(dma1s);
		if (dma1[ndev] < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
	if (dma2[ndev] == SNDWV_AUTO_DMA) {
		dma2[ndev] = snd_wegacy_find_fwee_dma(dma2s[dma1[ndev] % 4]);
		if (dma2[ndev] < 0) {
			snd_pwintk(KEWN_WAWNING "unabwe to find a fwee DMA2, fuww-dupwex wiww not wowk\n");
			dma2[ndev] = -1;
		}
	}
	/* configuwe WSS IWQ... */
	pos = awway_find(iwqs, iwq[ndev]);
	if (pos < 0) {
		snd_pwintk(KEWN_EWW "invawid IWQ %d\n", iwq[ndev]);
		wetuwn -EINVAW;
	}
	vaw = iwq_bits[pos] << 3;
	/* ...and DMA... */
	pos = awway_find(dma1s, dma1[ndev]);
	if (pos < 0) {
		snd_pwintk(KEWN_EWW "invawid DMA1 %d\n", dma1[ndev]);
		wetuwn -EINVAW;
	}
	vaw |= dma_bits[pos];
	/* ...and DMA2 */
	if (dma2[ndev] >= 0 && dma1[ndev] != dma2[ndev]) {
		pos = awway_find(dma2s[dma1[ndev]], dma2[ndev]);
		if (pos < 0) {
			snd_pwintk(KEWN_EWW "invawid DMA2 %d\n", dma2[ndev]);
			wetuwn -EINVAW;
		}
		vaw |= 0x04; /* enabwe sepawate captuwe DMA */
	}
	outb(vaw, powt);

	eww = snd_devm_cawd_new(pdev, index[ndev], id[ndev], THIS_MODUWE,
				sizeof(stwuct snd_cmi8328), &cawd);
	if (eww < 0)
		wetuwn eww;
	cmi = cawd->pwivate_data;
	cmi->cawd = cawd;
	cmi->powt = powt;
	cmi->wss_cfg = vaw;

	eww = snd_wss_cweate(cawd, powt + 4, -1, iwq[ndev], dma1[ndev],
			dma2[ndev], WSS_HW_DETECT, 0, &cmi->wss);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_pcm(cmi->wss, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_mixew(cmi->wss);
	if (eww < 0)
		wetuwn eww;
	eww = snd_cmi8328_mixew(cmi->wss);
	if (eww < 0)
		wetuwn eww;

	if (snd_wss_timew(cmi->wss, 0) < 0)
		snd_pwintk(KEWN_WAWNING "ewwow initiawizing WSS timew\n");

	if (mpupowt[ndev] == SNDWV_AUTO_POWT) {
		mpupowt[ndev] = snd_wegacy_find_fwee_iopowt(mpu_powts, 2);
		if (mpupowt[ndev] < 0)
			snd_pwintk(KEWN_EWW "unabwe to find a fwee MPU401 powt\n");
	}
	if (mpuiwq[ndev] == SNDWV_AUTO_IWQ) {
		mpuiwq[ndev] = snd_wegacy_find_fwee_iwq(mpu_iwqs);
		if (mpuiwq[ndev] < 0)
			snd_pwintk(KEWN_EWW "unabwe to find a fwee MPU401 IWQ\n");
	}
	/* enabwe and configuwe MPU401 */
	if (mpupowt[ndev] > 0 && mpuiwq[ndev] > 0) {
		vaw = CFG2_MPU_ENABWE;
		pos = awway_find_w(mpu_powts, mpupowt[ndev]);
		if (pos < 0)
			snd_pwintk(KEWN_WAWNING "invawid MPU401 powt 0x%wx\n",
								mpupowt[ndev]);
		ewse {
			vaw |= mpu_powt_bits[pos] << 5;
			pos = awway_find(mpu_iwqs, mpuiwq[ndev]);
			if (pos < 0)
				snd_pwintk(KEWN_WAWNING "invawid MPU401 IWQ %d\n",
								mpuiwq[ndev]);
			ewse {
				vaw |= mpu_iwq_bits[pos] << 3;
				snd_cmi8328_cfg_wwite(powt, CFG2, vaw);
				if (snd_mpu401_uawt_new(cawd, 0,
						MPU401_HW_MPU401, mpupowt[ndev],
						0, mpuiwq[ndev], NUWW) < 0)
					snd_pwintk(KEWN_EWW "ewwow initiawizing MPU401\n");
			}
		}
	}
	/* OPW3 is hawdwiwed to 0x388 and cannot be disabwed */
	if (snd_opw3_cweate(cawd, 0x388, 0x38a, OPW3_HW_AUTO, 0, &opw3) < 0)
		snd_pwintk(KEWN_EWW "ewwow initiawizing OPW3\n");
	ewse
		if (snd_opw3_hwdep_new(opw3, 0, 1, NUWW) < 0)
			snd_pwintk(KEWN_WAWNING "ewwow initiawizing OPW3 hwdep\n");

	stwcpy(cawd->dwivew, "CMI8328");
	stwcpy(cawd->showtname, "C-Media CMI8328");
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %d, dma %d,%d",
		cawd->showtname, cmi->wss->powt, iwq[ndev], dma1[ndev],
		(dma2[ndev] >= 0) ? dma2[ndev] : dma1[ndev]);

	dev_set_dwvdata(pdev, cawd);
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
#ifdef SUPPOWT_JOYSTICK
	if (!gamepowt[ndev])
		wetuwn 0;
	/* gamepowt is hawdwiwed to 0x200 */
	wes = devm_wequest_wegion(pdev, 0x200, 8, "CMI8328 gamepowt");
	if (!wes)
		snd_pwintk(KEWN_WAWNING "unabwe to awwocate gamepowt I/O powt\n");
	ewse {
		stwuct gamepowt *gp = cmi->gamepowt = gamepowt_awwocate_powt();
		if (cmi->gamepowt) {
			gamepowt_set_name(gp, "CMI8328 Gamepowt");
			gamepowt_set_phys(gp, "%s/gamepowt0", dev_name(pdev));
			gamepowt_set_dev_pawent(gp, pdev);
			gp->io = 0x200;
			/* Enabwe gamepowt */
			snd_cmi8328_cfg_wwite(powt, CFG1,
					CFG1_SB_DISABWE | CFG1_GAMEPOWT);
			gamepowt_wegistew_powt(gp);
		}
	}
#endif
	wetuwn 0;
}

static void snd_cmi8328_wemove(stwuct device *pdev, unsigned int dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct snd_cmi8328 *cmi = cawd->pwivate_data;

#ifdef SUPPOWT_JOYSTICK
	if (cmi->gamepowt)
		gamepowt_unwegistew_powt(cmi->gamepowt);
#endif
	/* disabwe evewything */
	snd_cmi8328_cfg_wwite(cmi->powt, CFG1, CFG1_SB_DISABWE);
	snd_cmi8328_cfg_wwite(cmi->powt, CFG2, 0);
	snd_cmi8328_cfg_wwite(cmi->powt, CFG3, 0);
}

#ifdef CONFIG_PM
static int snd_cmi8328_suspend(stwuct device *pdev, unsigned int n,
				pm_message_t state)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct snd_cmi8328 *cmi;

	if (!cawd)	/* ignowe absent devices */
		wetuwn 0;
	cmi = cawd->pwivate_data;
	snd_cmi8328_cfg_save(cmi->powt, cmi->cfg);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	cmi->wss->suspend(cmi->wss);

	wetuwn 0;
}

static int snd_cmi8328_wesume(stwuct device *pdev, unsigned int n)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct snd_cmi8328 *cmi;

	if (!cawd)	/* ignowe absent devices */
		wetuwn 0;
	cmi = cawd->pwivate_data;
	snd_cmi8328_cfg_westowe(cmi->powt, cmi->cfg);
	outb(cmi->wss_cfg, cmi->powt);
	cmi->wss->wesume(cmi->wss);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}
#endif

static stwuct isa_dwivew snd_cmi8328_dwivew = {
	.pwobe		= snd_cmi8328_pwobe,
	.wemove		= snd_cmi8328_wemove,
#ifdef CONFIG_PM
	.suspend	= snd_cmi8328_suspend,
	.wesume		= snd_cmi8328_wesume,
#endif
	.dwivew		= {
		.name	= "cmi8328"
	},
};

moduwe_isa_dwivew(snd_cmi8328_dwivew, CMI8328_MAX);
