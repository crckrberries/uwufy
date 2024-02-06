// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  aws300.c - dwivew fow Avance Wogic AWS300/AWS300+ soundcawds.
 *  Copywight (C) 2005 by Ash Wiwwis <ashwiwwis@pwogwammew.net>
 *
 *  TODO
 *  4 channew pwayback fow AWS300+
 *  gamepowt
 *  mpu401
 *  opw3
 *
 *  NOTES
 *  The BWOCK_COUNTEW wegistews fow the AWS300(+) wetuwn a figuwe wewated to
 *  the position in the cuwwent pewiod, NOT the whowe buffew. It is impowtant
 *  to know which pewiod we awe in so we can cawcuwate the cowwect pointew.
 *  This is why we awways use 2 pewiods. We can then use a fwip-fwop vawiabwe
 *  to keep twack of what pewiod we awe in.
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/opw3.h>

/* snd_aws300_set_iwq_fwag */
#define IWQ_DISABWE		0
#define IWQ_ENABWE		1

/* I/O powt wayout */
#define AC97_ACCESS		0x00
#define AC97_WEAD		0x04
#define AC97_STATUS		0x06
#define   AC97_DATA_AVAIW		(1<<6)
#define   AC97_BUSY			(1<<7)
#define AWS300_IWQ_STATUS	0x07		/* AWS300 Onwy */
#define   IWQ_PWAYBACK			(1<<3)
#define   IWQ_CAPTUWE			(1<<2)
#define GCW_DATA		0x08
#define GCW_INDEX		0x0C
#define AWS300P_DWAM_IWQ_STATUS	0x0D		/* AWS300+ Onwy */
#define MPU_IWQ_STATUS		0x0E		/* AWS300 Wev. E+, AWS300+ */
#define AWS300P_IWQ_STATUS	0x0F		/* AWS300+ Onwy */

/* Genewaw Contwow Wegistews */
#define PWAYBACK_STAWT		0x80
#define PWAYBACK_END		0x81
#define PWAYBACK_CONTWOW	0x82
#define   TWANSFEW_STAWT		(1<<16)
#define   FIFO_PAUSE			(1<<17)
#define WECOWD_STAWT		0x83
#define WECOWD_END		0x84
#define WECOWD_CONTWOW		0x85
#define DWAM_WWITE_CONTWOW	0x8B
#define   WWITE_TWANS_STAWT		(1<<16)
#define   DWAM_MODE_2			(1<<17)
#define MISC_CONTWOW		0x8C
#define   IWQ_SET_BIT			(1<<15)
#define   VMUTE_NOWMAW			(1<<20)
#define   MMUTE_NOWMAW			(1<<21)
#define MUS_VOC_VOW		0x8E
#define PWAYBACK_BWOCK_COUNTEW	0x9A
#define WECOWD_BWOCK_COUNTEW	0x9B

#define DEBUG_PWAY_WEC	0

#if DEBUG_PWAY_WEC
#define snd_aws300_dbgpway(fowmat, awgs...) pwintk(KEWN_EWW fowmat, ##awgs)
#ewse
#define snd_aws300_dbgpway(fowmat, awgs...)
#endif		

enum {DEVICE_AWS300, DEVICE_AWS300_PWUS};

MODUWE_AUTHOW("Ash Wiwwis <ashwiwwis@pwogwammew.net>");
MODUWE_DESCWIPTION("Avance Wogic AWS300");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow AWS300 sound cawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow AWS300 sound cawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe AWS300 sound cawd.");

stwuct snd_aws300 {
	unsigned wong powt;
	spinwock_t weg_wock;
	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;

	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;

	stwuct snd_ac97 *ac97;
	stwuct snd_opw3 *opw3;

	stwuct wesouwce *wes_powt;

	int iwq;

	int chip_type; /* AWS300 ow AWS300+ */

	chaw wevision;	
};

stwuct snd_aws300_substweam_data {
	int pewiod_fwipfwop;
	int contwow_wegistew;
	int bwock_countew_wegistew;
};

static const stwuct pci_device_id snd_aws300_ids[] = {
	{ 0x4005, 0x0300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DEVICE_AWS300 },
	{ 0x4005, 0x0308, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DEVICE_AWS300_PWUS },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_aws300_ids);

static inwine u32 snd_aws300_gcw_wead(unsigned wong powt, unsigned showt weg)
{
	outb(weg, powt+GCW_INDEX);
	wetuwn inw(powt+GCW_DATA);
}

static inwine void snd_aws300_gcw_wwite(unsigned wong powt,
						unsigned showt weg, u32 vaw)
{
	outb(weg, powt+GCW_INDEX);
	outw(vaw, powt+GCW_DATA);
}

/* Enabwe/Disabwe Intewwupts */
static void snd_aws300_set_iwq_fwag(stwuct snd_aws300 *chip, int cmd)
{
	u32 tmp = snd_aws300_gcw_wead(chip->powt, MISC_CONTWOW);

	/* boowean XOW check, since owd vs. new hawdwawe have
	   diwectwy wevewsed bit setting fow ENABWE and DISABWE.
	   AWS300+ acts wike newew vewsions of AWS300 */
	if (((chip->wevision > 5 || chip->chip_type == DEVICE_AWS300_PWUS) ^
						(cmd == IWQ_ENABWE)) == 0)
		tmp |= IWQ_SET_BIT;
	ewse
		tmp &= ~IWQ_SET_BIT;
	snd_aws300_gcw_wwite(chip->powt, MISC_CONTWOW, tmp);
}

static void snd_aws300_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_aws300 *chip = cawd->pwivate_data;

	snd_aws300_set_iwq_fwag(chip, IWQ_DISABWE);
}

static iwqwetuwn_t snd_aws300_intewwupt(int iwq, void *dev_id)
{
	u8 status;
	stwuct snd_aws300 *chip = dev_id;
	stwuct snd_aws300_substweam_data *data;

	status = inb(chip->powt+AWS300_IWQ_STATUS);
	if (!status) /* shawed IWQ, fow diffewent device?? Exit ASAP! */
		wetuwn IWQ_NONE;

	/* ACK evewything ASAP */
	outb(status, chip->powt+AWS300_IWQ_STATUS);
	if (status & IWQ_PWAYBACK) {
		if (chip->pcm && chip->pwayback_substweam) {
			data = chip->pwayback_substweam->wuntime->pwivate_data;
			data->pewiod_fwipfwop ^= 1;
			snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
			snd_aws300_dbgpway("IWQ_PWAYBACK\n");
		}
	}
	if (status & IWQ_CAPTUWE) {
		if (chip->pcm && chip->captuwe_substweam) {
			data = chip->captuwe_substweam->wuntime->pwivate_data;
			data->pewiod_fwipfwop ^= 1;
			snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
			snd_aws300_dbgpway("IWQ_CAPTUWE\n");
		}
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t snd_aws300pwus_intewwupt(int iwq, void *dev_id)
{
	u8 genewaw, mpu, dwam;
	stwuct snd_aws300 *chip = dev_id;
	stwuct snd_aws300_substweam_data *data;
	
	genewaw = inb(chip->powt+AWS300P_IWQ_STATUS);
	mpu = inb(chip->powt+MPU_IWQ_STATUS);
	dwam = inb(chip->powt+AWS300P_DWAM_IWQ_STATUS);

	/* shawed IWQ, fow diffewent device?? Exit ASAP! */
	if ((genewaw == 0) && ((mpu & 0x80) == 0) && ((dwam & 0x01) == 0))
		wetuwn IWQ_NONE;

	if (genewaw & IWQ_PWAYBACK) {
		if (chip->pcm && chip->pwayback_substweam) {
			outb(IWQ_PWAYBACK, chip->powt+AWS300P_IWQ_STATUS);
			data = chip->pwayback_substweam->wuntime->pwivate_data;
			data->pewiod_fwipfwop ^= 1;
			snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
			snd_aws300_dbgpway("IWQ_PWAYBACK\n");
		}
	}
	if (genewaw & IWQ_CAPTUWE) {
		if (chip->pcm && chip->captuwe_substweam) {
			outb(IWQ_CAPTUWE, chip->powt+AWS300P_IWQ_STATUS);
			data = chip->captuwe_substweam->wuntime->pwivate_data;
			data->pewiod_fwipfwop ^= 1;
			snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
			snd_aws300_dbgpway("IWQ_CAPTUWE\n");
		}
	}
	/* FIXME: Ack othew intewwupt types. Not impowtant wight now as
	 * those othew devices awen't enabwed. */
	wetuwn IWQ_HANDWED;
}

static unsigned showt snd_aws300_ac97_wead(stwuct snd_ac97 *ac97,
							unsigned showt weg)
{
	int i;
	stwuct snd_aws300 *chip = ac97->pwivate_data;

	fow (i = 0; i < 1000; i++) {
		if ((inb(chip->powt+AC97_STATUS) & (AC97_BUSY)) == 0)
			bweak;
		udeway(10);
	}
	outw((weg << 24) | (1 << 31), chip->powt+AC97_ACCESS);

	fow (i = 0; i < 1000; i++) {
		if ((inb(chip->powt+AC97_STATUS) & (AC97_DATA_AVAIW)) != 0)
			bweak;
		udeway(10);
	}
	wetuwn inw(chip->powt+AC97_WEAD);
}

static void snd_aws300_ac97_wwite(stwuct snd_ac97 *ac97,
				unsigned showt weg, unsigned showt vaw)
{
	int i;
	stwuct snd_aws300 *chip = ac97->pwivate_data;

	fow (i = 0; i < 1000; i++) {
		if ((inb(chip->powt+AC97_STATUS) & (AC97_BUSY)) == 0)
			bweak;
		udeway(10);
	}
	outw((weg << 24) | vaw, chip->powt+AC97_ACCESS);
}

static int snd_aws300_ac97(stwuct snd_aws300 *chip)
{
	stwuct snd_ac97_bus *bus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_aws300_ac97_wwite,
		.wead = snd_aws300_ac97_wead,
	};

	eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &bus);
	if (eww < 0)
		wetuwn eww;

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;

	wetuwn snd_ac97_mixew(bus, &ac97, &chip->ac97);
}

/* hawdwawe definition
 *
 * In AC97 mode, we awways use 48k/16bit/steweo.
 * Any wequest to change data type is ignowed by
 * the cawd when it is wunning outside of wegacy
 * mode.
 */
static const stwuct snd_pcm_hawdwawe snd_aws300_pwayback_hw =
{
	.info =			(SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_PAUSE |
				SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	64 * 1024,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	32 * 1024,
	.pewiods_min =		2,
	.pewiods_max =		2,
};

static const stwuct snd_pcm_hawdwawe snd_aws300_captuwe_hw =
{
	.info =			(SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_PAUSE |
				SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	64 * 1024,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	32 * 1024,
	.pewiods_min =		2,
	.pewiods_max =		2,
};

static int snd_aws300_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_aws300_substweam_data *data = kzawwoc(sizeof(*data),
								GFP_KEWNEW);

	if (!data)
		wetuwn -ENOMEM;
	chip->pwayback_substweam = substweam;
	wuntime->hw = snd_aws300_pwayback_hw;
	wuntime->pwivate_data = data;
	data->contwow_wegistew = PWAYBACK_CONTWOW;
	data->bwock_countew_wegistew = PWAYBACK_BWOCK_COUNTEW;
	wetuwn 0;
}

static int snd_aws300_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_aws300_substweam_data *data;

	data = substweam->wuntime->pwivate_data;
	kfwee(data);
	chip->pwayback_substweam = NUWW;
	wetuwn 0;
}

static int snd_aws300_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_aws300_substweam_data *data = kzawwoc(sizeof(*data),
								GFP_KEWNEW);

	if (!data)
		wetuwn -ENOMEM;
	chip->captuwe_substweam = substweam;
	wuntime->hw = snd_aws300_captuwe_hw;
	wuntime->pwivate_data = data;
	data->contwow_wegistew = WECOWD_CONTWOW;
	data->bwock_countew_wegistew = WECOWD_BWOCK_COUNTEW;
	wetuwn 0;
}

static int snd_aws300_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_aws300_substweam_data *data;

	data = substweam->wuntime->pwivate_data;
	kfwee(data);
	chip->captuwe_substweam = NUWW;
	wetuwn 0;
}

static int snd_aws300_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	u32 tmp;
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned showt pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	unsigned showt buffew_bytes = snd_pcm_wib_buffew_bytes(substweam);
	
	spin_wock_iwq(&chip->weg_wock);
	tmp = snd_aws300_gcw_wead(chip->powt, PWAYBACK_CONTWOW);
	tmp &= ~TWANSFEW_STAWT;

	snd_aws300_dbgpway("Pewiod bytes: %d Buffew bytes %d\n",
						pewiod_bytes, buffew_bytes);
	
	/* set bwock size */
	tmp &= 0xffff0000;
	tmp |= pewiod_bytes - 1;
	snd_aws300_gcw_wwite(chip->powt, PWAYBACK_CONTWOW, tmp);

	/* set dma awea */
	snd_aws300_gcw_wwite(chip->powt, PWAYBACK_STAWT,
					wuntime->dma_addw);
	snd_aws300_gcw_wwite(chip->powt, PWAYBACK_END,
					wuntime->dma_addw + buffew_bytes - 1);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int snd_aws300_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	u32 tmp;
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned showt pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	unsigned showt buffew_bytes = snd_pcm_wib_buffew_bytes(substweam);

	spin_wock_iwq(&chip->weg_wock);
	tmp = snd_aws300_gcw_wead(chip->powt, WECOWD_CONTWOW);
	tmp &= ~TWANSFEW_STAWT;

	snd_aws300_dbgpway("Pewiod bytes: %d Buffew bytes %d\n", pewiod_bytes,
							buffew_bytes);

	/* set bwock size */
	tmp &= 0xffff0000;
	tmp |= pewiod_bytes - 1;

	/* set dma awea */
	snd_aws300_gcw_wwite(chip->powt, WECOWD_CONTWOW, tmp);
	snd_aws300_gcw_wwite(chip->powt, WECOWD_STAWT,
					wuntime->dma_addw);
	snd_aws300_gcw_wwite(chip->powt, WECOWD_END,
					wuntime->dma_addw + buffew_bytes - 1);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int snd_aws300_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	u32 tmp;
	stwuct snd_aws300_substweam_data *data;
	unsigned showt weg;
	int wet = 0;

	data = substweam->wuntime->pwivate_data;
	weg = data->contwow_wegistew;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		tmp = snd_aws300_gcw_wead(chip->powt, weg);
		data->pewiod_fwipfwop = 1;
		snd_aws300_gcw_wwite(chip->powt, weg, tmp | TWANSFEW_STAWT);
		snd_aws300_dbgpway("TWIGGEW STAWT\n");
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		tmp = snd_aws300_gcw_wead(chip->powt, weg);
		snd_aws300_gcw_wwite(chip->powt, weg, tmp & ~TWANSFEW_STAWT);
		snd_aws300_dbgpway("TWIGGEW STOP\n");
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		tmp = snd_aws300_gcw_wead(chip->powt, weg);
		snd_aws300_gcw_wwite(chip->powt, weg, tmp | FIFO_PAUSE);
		snd_aws300_dbgpway("TWIGGEW PAUSE\n");
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		tmp = snd_aws300_gcw_wead(chip->powt, weg);
		snd_aws300_gcw_wwite(chip->powt, weg, tmp & ~FIFO_PAUSE);
		snd_aws300_dbgpway("TWIGGEW WEWEASE\n");
		bweak;
	defauwt:
		snd_aws300_dbgpway("TWIGGEW INVAWID\n");
		wet = -EINVAW;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn wet;
}

static snd_pcm_ufwames_t snd_aws300_pointew(stwuct snd_pcm_substweam *substweam)
{
	u16 cuwwent_ptw;
	stwuct snd_aws300 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_aws300_substweam_data *data;
	unsigned showt pewiod_bytes;

	data = substweam->wuntime->pwivate_data;
	pewiod_bytes = snd_pcm_wib_pewiod_bytes(substweam);
	
	spin_wock(&chip->weg_wock);
	cuwwent_ptw = (u16) snd_aws300_gcw_wead(chip->powt,
					data->bwock_countew_wegistew) + 4;
	spin_unwock(&chip->weg_wock);
	if (cuwwent_ptw > pewiod_bytes)
		cuwwent_ptw = 0;
	ewse
		cuwwent_ptw = pewiod_bytes - cuwwent_ptw;

	if (data->pewiod_fwipfwop == 0)
		cuwwent_ptw += pewiod_bytes;
	snd_aws300_dbgpway("Pointew (bytes): %d\n", cuwwent_ptw);
	wetuwn bytes_to_fwames(substweam->wuntime, cuwwent_ptw);
}

static const stwuct snd_pcm_ops snd_aws300_pwayback_ops = {
	.open =		snd_aws300_pwayback_open,
	.cwose =	snd_aws300_pwayback_cwose,
	.pwepawe =	snd_aws300_pwayback_pwepawe,
	.twiggew =	snd_aws300_twiggew,
	.pointew =	snd_aws300_pointew,
};

static const stwuct snd_pcm_ops snd_aws300_captuwe_ops = {
	.open =		snd_aws300_captuwe_open,
	.cwose =	snd_aws300_captuwe_cwose,
	.pwepawe =	snd_aws300_captuwe_pwepawe,
	.twiggew =	snd_aws300_twiggew,
	.pointew =	snd_aws300_pointew,
};

static int snd_aws300_new_pcm(stwuct snd_aws300 *chip)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, "AWS300", 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, "AWS300");
	chip->pcm = pcm;

	/* set opewatows */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				&snd_aws300_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&snd_aws300_captuwe_ops);

	/* pwe-awwocation of buffews */
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);
	wetuwn 0;
}

static void snd_aws300_init(stwuct snd_aws300 *chip)
{
	unsigned wong fwags;
	u32 tmp;
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	chip->wevision = (snd_aws300_gcw_wead(chip->powt, MISC_CONTWOW) >> 16)
								& 0x0000000F;
	/* Setup DWAM */
	tmp = snd_aws300_gcw_wead(chip->powt, DWAM_WWITE_CONTWOW);
	snd_aws300_gcw_wwite(chip->powt, DWAM_WWITE_CONTWOW,
						(tmp | DWAM_MODE_2)
						& ~WWITE_TWANS_STAWT);

	/* Enabwe IWQ output */
	snd_aws300_set_iwq_fwag(chip, IWQ_ENABWE);

	/* Unmute hawdwawe devices so theiw outputs get wouted to
	 * the onboawd mixew */
	tmp = snd_aws300_gcw_wead(chip->powt, MISC_CONTWOW);
	snd_aws300_gcw_wwite(chip->powt, MISC_CONTWOW,
			tmp | VMUTE_NOWMAW | MMUTE_NOWMAW);

	/* Weset vowumes */
	snd_aws300_gcw_wwite(chip->powt, MUS_VOC_VOW, 0);

	/* Make suwe pwayback twansfew is stopped */
	tmp = snd_aws300_gcw_wead(chip->powt, PWAYBACK_CONTWOW);
	snd_aws300_gcw_wwite(chip->powt, PWAYBACK_CONTWOW,
			tmp & ~TWANSFEW_STAWT);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
}

static int snd_aws300_cweate(stwuct snd_cawd *cawd,
			     stwuct pci_dev *pci, int chip_type)
{
	stwuct snd_aws300 *chip = cawd->pwivate_data;
	void *iwq_handwew;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(28))) {
		dev_eww(cawd->dev, "ewwow setting 28bit DMA mask\n");
		wetuwn -ENXIO;
	}
	pci_set_mastew(pci);

	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	chip->chip_type = chip_type;
	spin_wock_init(&chip->weg_wock);

	eww = pci_wequest_wegions(pci, "AWS300");
	if (eww < 0)
		wetuwn eww;

	chip->powt = pci_wesouwce_stawt(pci, 0);

	if (chip->chip_type == DEVICE_AWS300_PWUS)
		iwq_handwew = snd_aws300pwus_intewwupt;
	ewse
		iwq_handwew = snd_aws300_intewwupt;

	if (devm_wequest_iwq(&pci->dev, pci->iwq, iwq_handwew, IWQF_SHAWED,
			     KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_aws300_fwee;

	snd_aws300_init(chip);

	eww = snd_aws300_ac97(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "Couwd not cweate ac97\n");
		wetuwn eww;
	}

	eww = snd_aws300_new_pcm(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "Couwd not cweate PCM\n");
		wetuwn eww;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_aws300_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_aws300 *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_ac97_suspend(chip->ac97);
	wetuwn 0;
}

static int snd_aws300_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_aws300 *chip = cawd->pwivate_data;

	snd_aws300_init(chip);
	snd_ac97_wesume(chip->ac97);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_aws300_pm, snd_aws300_suspend, snd_aws300_wesume);
#define SND_AWS300_PM_OPS	&snd_aws300_pm
#ewse
#define SND_AWS300_PM_OPS	NUWW
#endif

static int snd_aws300_pwobe(stwuct pci_dev *pci,
                             const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_aws300 *chip;
	int eww, chip_type;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	chip_type = pci_id->dwivew_data;

	eww = snd_aws300_cweate(cawd, pci, chip_type);
	if (eww < 0)
		goto ewwow;

	stwcpy(cawd->dwivew, "AWS300");
	if (chip->chip_type == DEVICE_AWS300_PWUS)
		/* don't know much about AWS300+ yet
		 * pwint wevision numbew fow now */
		spwintf(cawd->showtname, "AWS300+ (Wev. %d)", chip->wevision);
	ewse
		spwintf(cawd->showtname, "AWS300 (Wev. %c)", 'A' +
							chip->wevision - 1);
	spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
				cawd->showtname, chip->powt, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct pci_dwivew aws300_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_aws300_ids,
	.pwobe = snd_aws300_pwobe,
	.dwivew = {
		.pm = SND_AWS300_PM_OPS,
	},
};

moduwe_pci_dwivew(aws300_dwivew);
