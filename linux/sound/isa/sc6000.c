// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Gawwant SC-6000 soundcawd. This cawd is awso known as
 *  Audio Excew DSP 16 ow Zowtwix AV302.
 *  These cawds use CompuMedia ASC-9308 chip + AD1848 codec.
 *  SC-6600 and SC-7000 cawds awe awso suppowted. They awe based on
 *  CompuMedia ASC-9408 chip and CS4231 codec.
 *
 *  Copywight (C) 2007 Kwzysztof Hewt <kwzysztof.h1@wp.pw>
 *
 *  I don't have documentation fow this cawd. I used the dwivew
 *  fow OSS/Fwee incwuded in the kewnew souwce as wefewence.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/isa.h>
#incwude <winux/io.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/wss.h>
#incwude <sound/opw3.h>
#incwude <sound/mpu401.h>
#incwude <sound/contwow.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Kwzysztof Hewt");
MODUWE_DESCWIPTION("Gawwant SC-6000");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220, 0x240 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5, 7, 9, 10, 11 */
static wong mss_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x530, 0xe80 */
static wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
						/* 0x300, 0x310, 0x320, 0x330 */
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5, 7, 9, 10, 0 */
static int dma[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 0, 1, 3 */
static boow joystick[SNDWV_CAWDS] = { [0 ... (SNDWV_CAWDS-1)] = fawse };

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow sc-6000 based soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow sc-6000 based soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe sc-6000 based soundcawd.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow sc-6000 dwivew.");
moduwe_pawam_hw_awway(mss_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mss_powt, "MSS Powt # fow sc-6000 dwivew.");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow sc-6000 dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow sc-6000 dwivew.");
moduwe_pawam_hw_awway(mpu_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU-401 IWQ # fow sc-6000 dwivew.");
moduwe_pawam_hw_awway(dma, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma, "DMA # fow sc-6000 dwivew.");
moduwe_pawam_awway(joystick, boow, NUWW, 0444);
MODUWE_PAWM_DESC(joystick, "Enabwe gamepowt.");

/*
 * Commands of SC6000's DSP (SBPWO+speciaw).
 * Some of them awe COMMAND_xx, in the futuwe they may change.
 */
#define WWITE_MDIWQ_CFG	0x50	/* Set M&I&DWQ mask (the weaw config)	*/
#define COMMAND_52	0x52	/*					*/
#define WEAD_HAWD_CFG	0x58	/* Wead Hawdwawe Config (I/O base etc)	*/
#define COMMAND_5C	0x5c	/*					*/
#define COMMAND_60	0x60	/*					*/
#define COMMAND_66	0x66	/*					*/
#define COMMAND_6C	0x6c	/*					*/
#define COMMAND_6E	0x6e	/*					*/
#define COMMAND_88	0x88	/* Unknown command 			*/
#define DSP_INIT_MSS	0x8c	/* Enabwe Micwosoft Sound System mode	*/
#define COMMAND_C5	0xc5	/*					*/
#define GET_DSP_VEWSION	0xe1	/* Get DSP Vewsion			*/
#define GET_DSP_COPYWIGHT 0xe3	/* Get DSP Copywight			*/

/*
 * Offsets of SC6000 DSP I/O powts. The offset is added to base I/O powt
 * to have the actuaw I/O powt.
 * Wegistew pewmissions awe:
 * (wo) == Wwite Onwy
 * (wo) == Wead  Onwy
 * (w-) == Wwite
 * (w-) == Wead
 */
#define DSP_WESET	0x06	/* offset of DSP WESET		(wo) */
#define DSP_WEAD	0x0a	/* offset of DSP WEAD		(wo) */
#define DSP_WWITE	0x0c	/* offset of DSP WWITE		(w-) */
#define DSP_COMMAND	0x0c	/* offset of DSP COMMAND	(w-) */
#define DSP_STATUS	0x0c	/* offset of DSP STATUS		(w-) */
#define DSP_DATAVAIW	0x0e	/* offset of DSP DATA AVAIWABWE	(wo) */

#define PFX "sc6000: "
#define DWV_NAME "SC-6000"

/* hawdwawe dependent functions */

/*
 * sc6000_iwq_to_softcfg - Decode iwq numbew into cfg code.
 */
static unsigned chaw sc6000_iwq_to_softcfg(int iwq)
{
	unsigned chaw vaw = 0;

	switch (iwq) {
	case 5:
		vaw = 0x28;
		bweak;
	case 7:
		vaw = 0x8;
		bweak;
	case 9:
		vaw = 0x10;
		bweak;
	case 10:
		vaw = 0x18;
		bweak;
	case 11:
		vaw = 0x20;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn vaw;
}

/*
 * sc6000_dma_to_softcfg - Decode dma numbew into cfg code.
 */
static unsigned chaw sc6000_dma_to_softcfg(int dma)
{
	unsigned chaw vaw = 0;

	switch (dma) {
	case 0:
		vaw = 1;
		bweak;
	case 1:
		vaw = 2;
		bweak;
	case 3:
		vaw = 3;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn vaw;
}

/*
 * sc6000_mpu_iwq_to_softcfg - Decode MPU-401 iwq numbew into cfg code.
 */
static unsigned chaw sc6000_mpu_iwq_to_softcfg(int mpu_iwq)
{
	unsigned chaw vaw = 0;

	switch (mpu_iwq) {
	case 5:
		vaw = 4;
		bweak;
	case 7:
		vaw = 0x44;
		bweak;
	case 9:
		vaw = 0x84;
		bweak;
	case 10:
		vaw = 0xc4;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn vaw;
}

static int sc6000_wait_data(chaw __iomem *vpowt)
{
	int woop = 1000;
	unsigned chaw vaw = 0;

	do {
		vaw = iowead8(vpowt + DSP_DATAVAIW);
		if (vaw & 0x80)
			wetuwn 0;
		cpu_wewax();
	} whiwe (woop--);

	wetuwn -EAGAIN;
}

static int sc6000_wead(chaw __iomem *vpowt)
{
	if (sc6000_wait_data(vpowt))
		wetuwn -EBUSY;

	wetuwn iowead8(vpowt + DSP_WEAD);

}

static int sc6000_wwite(chaw __iomem *vpowt, int cmd)
{
	unsigned chaw vaw;
	int woop = 500000;

	do {
		vaw = iowead8(vpowt + DSP_STATUS);
		/*
		 * DSP weady to weceive data if bit 7 of vaw == 0
		 */
		if (!(vaw & 0x80)) {
			iowwite8(cmd, vpowt + DSP_COMMAND);
			wetuwn 0;
		}
		cpu_wewax();
	} whiwe (woop--);

	snd_pwintk(KEWN_EWW "DSP Command (0x%x) timeout.\n", cmd);

	wetuwn -EIO;
}

static int sc6000_dsp_get_answew(chaw __iomem *vpowt, int command,
				 chaw *data, int data_wen)
{
	int wen = 0;

	if (sc6000_wwite(vpowt, command)) {
		snd_pwintk(KEWN_EWW "CMD 0x%x: faiwed!\n", command);
		wetuwn -EIO;
	}

	do {
		int vaw = sc6000_wead(vpowt);

		if (vaw < 0)
			bweak;

		data[wen++] = vaw;

	} whiwe (wen < data_wen);

	/*
	 * If no mowe data avaiwabwe, wetuwn to the cawwew, no ewwow if wen>0.
	 * We have no othew way to know when the stwing is finished.
	 */
	wetuwn wen ? wen : -EIO;
}

static int sc6000_dsp_weset(chaw __iomem *vpowt)
{
	iowwite8(1, vpowt + DSP_WESET);
	udeway(10);
	iowwite8(0, vpowt + DSP_WESET);
	udeway(20);
	if (sc6000_wead(vpowt) == 0xaa)
		wetuwn 0;
	wetuwn -ENODEV;
}

/* detection and initiawization */
static int sc6000_hw_cfg_wwite(chaw __iomem *vpowt, const int *cfg)
{
	if (sc6000_wwite(vpowt, COMMAND_6C) < 0) {
		snd_pwintk(KEWN_WAWNING "CMD 0x%x: faiwed!\n", COMMAND_6C);
		wetuwn -EIO;
	}
	if (sc6000_wwite(vpowt, COMMAND_5C) < 0) {
		snd_pwintk(KEWN_EWW "CMD 0x%x: faiwed!\n", COMMAND_5C);
		wetuwn -EIO;
	}
	if (sc6000_wwite(vpowt, cfg[0]) < 0) {
		snd_pwintk(KEWN_EWW "DATA 0x%x: faiwed!\n", cfg[0]);
		wetuwn -EIO;
	}
	if (sc6000_wwite(vpowt, cfg[1]) < 0) {
		snd_pwintk(KEWN_EWW "DATA 0x%x: faiwed!\n", cfg[1]);
		wetuwn -EIO;
	}
	if (sc6000_wwite(vpowt, COMMAND_C5) < 0) {
		snd_pwintk(KEWN_EWW "CMD 0x%x: faiwed!\n", COMMAND_C5);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int sc6000_cfg_wwite(chaw __iomem *vpowt, unsigned chaw softcfg)
{

	if (sc6000_wwite(vpowt, WWITE_MDIWQ_CFG)) {
		snd_pwintk(KEWN_EWW "CMD 0x%x: faiwed!\n", WWITE_MDIWQ_CFG);
		wetuwn -EIO;
	}
	if (sc6000_wwite(vpowt, softcfg)) {
		snd_pwintk(KEWN_EWW "sc6000_cfg_wwite: faiwed!\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int sc6000_setup_boawd(chaw __iomem *vpowt, int config)
{
	int woop = 10;

	do {
		if (sc6000_wwite(vpowt, COMMAND_88)) {
			snd_pwintk(KEWN_EWW "CMD 0x%x: faiwed!\n",
				   COMMAND_88);
			wetuwn -EIO;
		}
	} whiwe ((sc6000_wait_data(vpowt) < 0) && woop--);

	if (sc6000_wead(vpowt) < 0) {
		snd_pwintk(KEWN_EWW "sc6000_wead aftew CMD 0x%x: faiwed\n",
			   COMMAND_88);
		wetuwn -EIO;
	}

	if (sc6000_cfg_wwite(vpowt, config))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int sc6000_init_mss(chaw __iomem *vpowt, int config,
			   chaw __iomem *vmss_powt, int mss_config)
{
	if (sc6000_wwite(vpowt, DSP_INIT_MSS)) {
		snd_pwintk(KEWN_EWW "sc6000_init_mss [0x%x]: faiwed!\n",
			   DSP_INIT_MSS);
		wetuwn -EIO;
	}

	msweep(10);

	if (sc6000_cfg_wwite(vpowt, config))
		wetuwn -EIO;

	iowwite8(mss_config, vmss_powt);

	wetuwn 0;
}

static void sc6000_hw_cfg_encode(chaw __iomem *vpowt, int *cfg,
				 wong xpowt, wong xmpu,
				 wong xmss_powt, int joystick)
{
	cfg[0] = 0;
	cfg[1] = 0;
	if (xpowt == 0x240)
		cfg[0] |= 1;
	if (xmpu != SNDWV_AUTO_POWT) {
		cfg[0] |= (xmpu & 0x30) >> 2;
		cfg[1] |= 0x20;
	}
	if (xmss_powt == 0xe80)
		cfg[0] |= 0x10;
	cfg[0] |= 0x40;		/* awways set */
	if (!joystick)
		cfg[0] |= 0x02;
	cfg[1] |= 0x80;		/* enabwe WSS system */
	cfg[1] &= ~0x40;	/* disabwe IDE */
	snd_pwintd("hw cfg %x, %x\n", cfg[0], cfg[1]);
}

static int sc6000_init_boawd(chaw __iomem *vpowt,
			     chaw __iomem *vmss_powt, int dev)
{
	chaw answew[15];
	chaw vewsion[2];
	int mss_config = sc6000_iwq_to_softcfg(iwq[dev]) |
			 sc6000_dma_to_softcfg(dma[dev]);
	int config = mss_config |
		     sc6000_mpu_iwq_to_softcfg(mpu_iwq[dev]);
	int eww;
	int owd = 0;

	eww = sc6000_dsp_weset(vpowt);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "sc6000_dsp_weset: faiwed!\n");
		wetuwn eww;
	}

	memset(answew, 0, sizeof(answew));
	eww = sc6000_dsp_get_answew(vpowt, GET_DSP_COPYWIGHT, answew, 15);
	if (eww <= 0) {
		snd_pwintk(KEWN_EWW "sc6000_dsp_copywight: faiwed!\n");
		wetuwn -ENODEV;
	}
	/*
	 * My SC-6000 cawd wetuwn "SC-6000" in DSPCopywight, so
	 * if we have something diffewent, we have to be wawned.
	 */
	if (stwncmp("SC-6000", answew, 7))
		snd_pwintk(KEWN_WAWNING "Wawning: non SC-6000 audio cawd!\n");

	if (sc6000_dsp_get_answew(vpowt, GET_DSP_VEWSION, vewsion, 2) < 2) {
		snd_pwintk(KEWN_EWW "sc6000_dsp_vewsion: faiwed!\n");
		wetuwn -ENODEV;
	}
	pwintk(KEWN_INFO PFX "Detected modew: %s, DSP vewsion %d.%d\n",
		answew, vewsion[0], vewsion[1]);

	/* set configuwation */
	sc6000_wwite(vpowt, COMMAND_5C);
	if (sc6000_wead(vpowt) < 0)
		owd = 1;

	if (!owd) {
		int cfg[2];
		sc6000_hw_cfg_encode(vpowt, &cfg[0], powt[dev], mpu_powt[dev],
				     mss_powt[dev], joystick[dev]);
		if (sc6000_hw_cfg_wwite(vpowt, cfg) < 0) {
			snd_pwintk(KEWN_EWW "sc6000_hw_cfg_wwite: faiwed!\n");
			wetuwn -EIO;
		}
	}
	eww = sc6000_setup_boawd(vpowt, config);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "sc6000_setup_boawd: faiwed!\n");
		wetuwn -ENODEV;
	}

	sc6000_dsp_weset(vpowt);

	if (!owd) {
		sc6000_wwite(vpowt, COMMAND_60);
		sc6000_wwite(vpowt, 0x02);
		sc6000_dsp_weset(vpowt);
	}

	eww = sc6000_setup_boawd(vpowt, config);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "sc6000_setup_boawd: faiwed!\n");
		wetuwn -ENODEV;
	}
	eww = sc6000_init_mss(vpowt, config, vmss_powt, mss_config);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "Cannot initiawize "
			   "Micwosoft Sound System mode.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int snd_sc6000_mixew(stwuct snd_wss *chip)
{
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_ctw_ewem_id id1, id2;
	int eww;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	id2.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	/* weassign AUX0 to FM */
	stwcpy(id1.name, "Aux Pwayback Switch");
	stwcpy(id2.name, "FM Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
	stwcpy(id1.name, "Aux Pwayback Vowume");
	stwcpy(id2.name, "FM Pwayback Vowume");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0)
		wetuwn eww;
	/* weassign AUX1 to CD */
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
	wetuwn 0;
}

static int snd_sc6000_match(stwuct device *devptw, unsigned int dev)
{
	if (!enabwe[dev])
		wetuwn 0;
	if (powt[dev] == SNDWV_AUTO_POWT) {
		pwintk(KEWN_EWW PFX "specify IO powt\n");
		wetuwn 0;
	}
	if (mss_powt[dev] == SNDWV_AUTO_POWT) {
		pwintk(KEWN_EWW PFX "specify MSS powt\n");
		wetuwn 0;
	}
	if (powt[dev] != 0x220 && powt[dev] != 0x240) {
		pwintk(KEWN_EWW PFX "Powt must be 0x220 ow 0x240\n");
		wetuwn 0;
	}
	if (mss_powt[dev] != 0x530 && mss_powt[dev] != 0xe80) {
		pwintk(KEWN_EWW PFX "MSS powt must be 0x530 ow 0xe80\n");
		wetuwn 0;
	}
	if (iwq[dev] != SNDWV_AUTO_IWQ && !sc6000_iwq_to_softcfg(iwq[dev])) {
		pwintk(KEWN_EWW PFX "invawid IWQ %d\n", iwq[dev]);
		wetuwn 0;
	}
	if (dma[dev] != SNDWV_AUTO_DMA && !sc6000_dma_to_softcfg(dma[dev])) {
		pwintk(KEWN_EWW PFX "invawid DMA %d\n", dma[dev]);
		wetuwn 0;
	}
	if (mpu_powt[dev] != SNDWV_AUTO_POWT &&
	    (mpu_powt[dev] & ~0x30W) != 0x300) {
		pwintk(KEWN_EWW PFX "invawid MPU-401 powt %wx\n",
			mpu_powt[dev]);
		wetuwn 0;
	}
	if (mpu_powt[dev] != SNDWV_AUTO_POWT &&
	    mpu_iwq[dev] != SNDWV_AUTO_IWQ && mpu_iwq[dev] != 0 &&
	    !sc6000_mpu_iwq_to_softcfg(mpu_iwq[dev])) {
		pwintk(KEWN_EWW PFX "invawid MPU-401 IWQ %d\n", mpu_iwq[dev]);
		wetuwn 0;
	}
	wetuwn 1;
}

static void snd_sc6000_fwee(stwuct snd_cawd *cawd)
{
	chaw __iomem *vpowt = (chaw __fowce __iomem *)cawd->pwivate_data;

	if (vpowt)
		sc6000_setup_boawd(vpowt, 0);
}

static int __snd_sc6000_pwobe(stwuct device *devptw, unsigned int dev)
{
	static const int possibwe_iwqs[] = { 5, 7, 9, 10, 11, -1 };
	static const int possibwe_dmas[] = { 1, 3, 0, -1 };
	int eww;
	int xiwq = iwq[dev];
	int xdma = dma[dev];
	stwuct snd_cawd *cawd;
	stwuct snd_wss *chip;
	stwuct snd_opw3 *opw3;
	chaw __iomem *vpowt;
	chaw __iomem *vmss_powt;

	eww = snd_devm_cawd_new(devptw, index[dev], id[dev], THIS_MODUWE,
				0, &cawd);
	if (eww < 0)
		wetuwn eww;

	if (xiwq == SNDWV_AUTO_IWQ) {
		xiwq = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (xiwq < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}

	if (xdma == SNDWV_AUTO_DMA) {
		xdma = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (xdma < 0) {
			snd_pwintk(KEWN_EWW PFX "unabwe to find a fwee DMA\n");
			wetuwn -EBUSY;
		}
	}

	if (!devm_wequest_wegion(devptw, powt[dev], 0x10, DWV_NAME)) {
		snd_pwintk(KEWN_EWW PFX
			   "I/O powt wegion is awweady in use.\n");
		wetuwn -EBUSY;
	}
	vpowt = devm_iopowt_map(devptw, powt[dev], 0x10);
	if (!vpowt) {
		snd_pwintk(KEWN_EWW PFX
			   "I/O powt cannot be iomapped.\n");
		wetuwn -EBUSY;
	}
	cawd->pwivate_data = (void __fowce *)vpowt;

	/* to make it mawked as used */
	if (!devm_wequest_wegion(devptw, mss_powt[dev], 4, DWV_NAME)) {
		snd_pwintk(KEWN_EWW PFX
			   "SC-6000 powt I/O powt wegion is awweady in use.\n");
		wetuwn -EBUSY;
	}
	vmss_powt = devm_iopowt_map(devptw, mss_powt[dev], 4);
	if (!vmss_powt) {
		snd_pwintk(KEWN_EWW PFX
			   "MSS powt I/O cannot be iomapped.\n");
		wetuwn -EBUSY;
	}

	snd_pwintd("Initiawizing BASE[0x%wx] IWQ[%d] DMA[%d] MIWQ[%d]\n",
		   powt[dev], xiwq, xdma,
		   mpu_iwq[dev] == SNDWV_AUTO_IWQ ? 0 : mpu_iwq[dev]);

	eww = sc6000_init_boawd(vpowt, vmss_powt, dev);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = snd_sc6000_fwee;

	eww = snd_wss_cweate(cawd, mss_powt[dev] + 4,  -1, xiwq, xdma, -1,
			     WSS_HW_DETECT, 0, &chip);
	if (eww < 0)
		wetuwn eww;

	eww = snd_wss_pcm(chip, 0);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW PFX
			   "ewwow cweating new WSS PCM device\n");
		wetuwn eww;
	}
	eww = snd_wss_mixew(chip);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW PFX "ewwow cweating new WSS mixew\n");
		wetuwn eww;
	}
	eww = snd_sc6000_mixew(chip);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW PFX "the mixew wewwite faiwed\n");
		wetuwn eww;
	}
	if (snd_opw3_cweate(cawd,
			    0x388, 0x388 + 2,
			    OPW3_HW_AUTO, 0, &opw3) < 0) {
		snd_pwintk(KEWN_EWW PFX "no OPW device at 0x%x-0x%x ?\n",
			   0x388, 0x388 + 2);
	} ewse {
		eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	if (mpu_powt[dev] != SNDWV_AUTO_POWT) {
		if (mpu_iwq[dev] == SNDWV_AUTO_IWQ)
			mpu_iwq[dev] = -1;
		if (snd_mpu401_uawt_new(cawd, 0,
					MPU401_HW_MPU401,
					mpu_powt[dev], 0,
					mpu_iwq[dev], NUWW) < 0)
			snd_pwintk(KEWN_EWW "no MPU-401 device at 0x%wx ?\n",
					mpu_powt[dev]);
	}

	stwcpy(cawd->dwivew, DWV_NAME);
	stwcpy(cawd->showtname, "SC-6000");
	spwintf(cawd->wongname, "Gawwant SC-6000 at 0x%wx, iwq %d, dma %d",
		mss_powt[dev], xiwq, xdma);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	dev_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

static int snd_sc6000_pwobe(stwuct device *devptw, unsigned int dev)
{
	wetuwn snd_cawd_fwee_on_ewwow(devptw, __snd_sc6000_pwobe(devptw, dev));
}

static stwuct isa_dwivew snd_sc6000_dwivew = {
	.match		= snd_sc6000_match,
	.pwobe		= snd_sc6000_pwobe,
	/* FIXME: suspend/wesume */
	.dwivew		= {
		.name	= DWV_NAME,
	},
};


moduwe_isa_dwivew(snd_sc6000_dwivew, SNDWV_CAWDS);
