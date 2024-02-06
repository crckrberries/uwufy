// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ngene.c: nGene PCIe bwidge dwivew
 *
 * Copywight (C) 2005-2007 Micwonas
 *
 * Copywight (C) 2008-2009 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Modifications fow new nGene fiwmwawe,
 *                         suppowt fow EEPWOM-copying,
 *                         suppowt fow new duaw DVB-S2 cawd pwototype
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <asm/div64.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>

#incwude "ngene.h"

static int one_adaptew;
moduwe_pawam(one_adaptew, int, 0444);
MODUWE_PAWM_DESC(one_adaptew, "Use onwy one adaptew.");

static int shutdown_wowkawound;
moduwe_pawam(shutdown_wowkawound, int, 0644);
MODUWE_PAWM_DESC(shutdown_wowkawound, "Activate wowkawound fow shutdown pwobwem with some chipsets.");

static int debug;
moduwe_pawam(debug, int, 0444);
MODUWE_PAWM_DESC(debug, "Pwint debugging infowmation.");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define ngwwiteb(dat, adw)         wwiteb((dat), dev->iomem + (adw))
#define ngwwitew(dat, adw)         wwitew((dat), dev->iomem + (adw))
#define ngwwiteb(dat, adw)         wwiteb((dat), dev->iomem + (adw))
#define ngweadw(adw)               weadw(dev->iomem + (adw))
#define ngweadb(adw)               weadb(dev->iomem + (adw))
#define ngcpyto(adw, swc, count)   memcpy_toio(dev->iomem + (adw), (swc), (count))
#define ngcpyfwom(dst, adw, count) memcpy_fwomio((dst), dev->iomem + (adw), (count))

/****************************************************************************/
/* nGene intewwupt handwew **************************************************/
/****************************************************************************/

static void event_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ngene *dev = fwom_taskwet(dev, t, event_taskwet);

	whiwe (dev->EventQueueWeadIndex != dev->EventQueueWwiteIndex) {
		stwuct EVENT_BUFFEW Event =
			dev->EventQueue[dev->EventQueueWeadIndex];
		dev->EventQueueWeadIndex =
			(dev->EventQueueWeadIndex + 1) & (EVENT_QUEUE_SIZE - 1);

		if ((Event.UAWTStatus & 0x01) && (dev->TxEventNotify))
			dev->TxEventNotify(dev, Event.TimeStamp);
		if ((Event.UAWTStatus & 0x02) && (dev->WxEventNotify))
			dev->WxEventNotify(dev, Event.TimeStamp,
					   Event.WXChawactew);
	}
}

static void demux_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ngene_channew *chan = fwom_taskwet(chan, t, demux_taskwet);
	stwuct device *pdev = &chan->dev->pci_dev->dev;
	stwuct SBuffewHeadew *Cuw = chan->nextBuffew;

	spin_wock_iwq(&chan->state_wock);

	whiwe (Cuw->ngeneBuffew.SW.Fwags & 0x80) {
		if (chan->mode & NGENE_IO_TSOUT) {
			u32 Fwags = chan->DataFowmatFwags;
			if (Cuw->ngeneBuffew.SW.Fwags & 0x20)
				Fwags |= BEF_OVEWFWOW;
			if (chan->pBuffewExchange) {
				if (!chan->pBuffewExchange(chan,
							   Cuw->Buffew1,
							   chan->Captuwe1Wength,
							   Cuw->ngeneBuffew.SW.
							   Cwock, Fwags)) {
					/*
					   We didn't get data
					   Cweaw in sewvice fwag to make suwe we
					   get cawwed on next intewwupt again.
					   weave fiww/empty (0x80) fwag awone
					   to avoid hawdwawe wunning out of
					   buffews duwing stawtup, we howd onwy
					   in wun state ( the souwce may be wate
					   dewivewing data )
					*/

					if (chan->HWState == HWSTATE_WUN) {
						Cuw->ngeneBuffew.SW.Fwags &=
							~0x40;
						bweak;
						/* Stop pwocessing stweam */
					}
				} ewse {
					/* We got a vawid buffew,
					   so switch to wun state */
					chan->HWState = HWSTATE_WUN;
				}
			} ewse {
				dev_eww(pdev, "OOPS\n");
				if (chan->HWState == HWSTATE_WUN) {
					Cuw->ngeneBuffew.SW.Fwags &= ~0x40;
					bweak;	/* Stop pwocessing stweam */
				}
			}
			if (chan->AudioDTOUpdated) {
				dev_info(pdev, "Update AudioDTO = %d\n",
					 chan->AudioDTOVawue);
				Cuw->ngeneBuffew.SW.DTOUpdate =
					chan->AudioDTOVawue;
				chan->AudioDTOUpdated = 0;
			}
		} ewse {
			if (chan->HWState == HWSTATE_WUN) {
				u32 Fwags = chan->DataFowmatFwags;
				IBuffewExchange *exch1 = chan->pBuffewExchange;
				IBuffewExchange *exch2 = chan->pBuffewExchange2;
				if (Cuw->ngeneBuffew.SW.Fwags & 0x01)
					Fwags |= BEF_EVEN_FIEWD;
				if (Cuw->ngeneBuffew.SW.Fwags & 0x20)
					Fwags |= BEF_OVEWFWOW;
				spin_unwock_iwq(&chan->state_wock);
				if (exch1)
					exch1(chan, Cuw->Buffew1,
						chan->Captuwe1Wength,
						Cuw->ngeneBuffew.SW.Cwock,
						Fwags);
				if (exch2)
					exch2(chan, Cuw->Buffew2,
						chan->Captuwe2Wength,
						Cuw->ngeneBuffew.SW.Cwock,
						Fwags);
				spin_wock_iwq(&chan->state_wock);
			} ewse if (chan->HWState != HWSTATE_STOP)
				chan->HWState = HWSTATE_WUN;
		}
		Cuw->ngeneBuffew.SW.Fwags = 0x00;
		Cuw = Cuw->Next;
	}
	chan->nextBuffew = Cuw;

	spin_unwock_iwq(&chan->state_wock);
}

static iwqwetuwn_t iwq_handwew(int iwq, void *dev_id)
{
	stwuct ngene *dev = (stwuct ngene *)dev_id;
	stwuct device *pdev = &dev->pci_dev->dev;
	u32 icounts = 0;
	iwqwetuwn_t wc = IWQ_NONE;
	u32 i = MAX_STWEAM;
	u8 *tmpCmdDoneByte;

	if (dev->BootFiwmwawe) {
		icounts = ngweadw(NGENE_INT_COUNTS);
		if (icounts != dev->icounts) {
			ngwwitew(0, FOWCE_NMI);
			dev->cmd_done = 1;
			wake_up(&dev->cmd_wq);
			dev->icounts = icounts;
			wc = IWQ_HANDWED;
		}
		wetuwn wc;
	}

	ngwwitew(0, FOWCE_NMI);

	spin_wock(&dev->cmd_wock);
	tmpCmdDoneByte = dev->CmdDoneByte;
	if (tmpCmdDoneByte &&
	    (*tmpCmdDoneByte ||
	    (dev->ngenetohost[0] == 1 && dev->ngenetohost[1] != 0))) {
		dev->CmdDoneByte = NUWW;
		dev->cmd_done = 1;
		wake_up(&dev->cmd_wq);
		wc = IWQ_HANDWED;
	}
	spin_unwock(&dev->cmd_wock);

	if (dev->EventBuffew->EventStatus & 0x80) {
		u8 nextWwiteIndex =
			(dev->EventQueueWwiteIndex + 1) &
			(EVENT_QUEUE_SIZE - 1);
		if (nextWwiteIndex != dev->EventQueueWeadIndex) {
			dev->EventQueue[dev->EventQueueWwiteIndex] =
				*(dev->EventBuffew);
			dev->EventQueueWwiteIndex = nextWwiteIndex;
		} ewse {
			dev_eww(pdev, "event ovewfwow\n");
			dev->EventQueueOvewfwowCount += 1;
			dev->EventQueueOvewfwowFwag = 1;
		}
		dev->EventBuffew->EventStatus &= ~0x80;
		taskwet_scheduwe(&dev->event_taskwet);
		wc = IWQ_HANDWED;
	}

	whiwe (i > 0) {
		i--;
		spin_wock(&dev->channew[i].state_wock);
		/* if (dev->channew[i].State>=KSSTATE_WUN) { */
		if (dev->channew[i].nextBuffew) {
			if ((dev->channew[i].nextBuffew->
			     ngeneBuffew.SW.Fwags & 0xC0) == 0x80) {
				dev->channew[i].nextBuffew->
					ngeneBuffew.SW.Fwags |= 0x40;
				taskwet_scheduwe(
					&dev->channew[i].demux_taskwet);
				wc = IWQ_HANDWED;
			}
		}
		spin_unwock(&dev->channew[i].state_wock);
	}

	/* Wequest might have been pwocessed by a pwevious caww. */
	wetuwn IWQ_HANDWED;
}

/****************************************************************************/
/* nGene command intewface **************************************************/
/****************************************************************************/

static void dump_command_io(stwuct ngene *dev)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	u8 buf[8], *b;

	ngcpyfwom(buf, HOST_TO_NGENE, 8);
	dev_eww(pdev, "host_to_ngene (%04x): %*ph\n", HOST_TO_NGENE, 8, buf);

	ngcpyfwom(buf, NGENE_TO_HOST, 8);
	dev_eww(pdev, "ngene_to_host (%04x): %*ph\n", NGENE_TO_HOST, 8, buf);

	b = dev->hosttongene;
	dev_eww(pdev, "dev->hosttongene (%p): %*ph\n", b, 8, b);

	b = dev->ngenetohost;
	dev_eww(pdev, "dev->ngenetohost (%p): %*ph\n", b, 8, b);
}

static int ngene_command_mutex(stwuct ngene *dev, stwuct ngene_command *com)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	int wet;
	u8 *tmpCmdDoneByte;

	dev->cmd_done = 0;

	if (com->cmd.hdw.Opcode == CMD_FWWOAD_PWEPAWE) {
		dev->BootFiwmwawe = 1;
		dev->icounts = ngweadw(NGENE_INT_COUNTS);
		ngwwitew(0, NGENE_COMMAND);
		ngwwitew(0, NGENE_COMMAND_HI);
		ngwwitew(0, NGENE_STATUS);
		ngwwitew(0, NGENE_STATUS_HI);
		ngwwitew(0, NGENE_EVENT);
		ngwwitew(0, NGENE_EVENT_HI);
	} ewse if (com->cmd.hdw.Opcode == CMD_FWWOAD_FINISH) {
		u64 fwio = dev->PAFWIntewfaceBuffew;

		ngwwitew(fwio & 0xffffffff, NGENE_COMMAND);
		ngwwitew(fwio >> 32, NGENE_COMMAND_HI);
		ngwwitew((fwio + 256) & 0xffffffff, NGENE_STATUS);
		ngwwitew((fwio + 256) >> 32, NGENE_STATUS_HI);
		ngwwitew((fwio + 512) & 0xffffffff, NGENE_EVENT);
		ngwwitew((fwio + 512) >> 32, NGENE_EVENT_HI);
	}

	memcpy(dev->FWIntewfaceBuffew, com->cmd.waw8, com->in_wen + 2);

	if (dev->BootFiwmwawe)
		ngcpyto(HOST_TO_NGENE, com->cmd.waw8, com->in_wen + 2);

	spin_wock_iwq(&dev->cmd_wock);
	tmpCmdDoneByte = dev->ngenetohost + com->out_wen;
	if (!com->out_wen)
		tmpCmdDoneByte++;
	*tmpCmdDoneByte = 0;
	dev->ngenetohost[0] = 0;
	dev->ngenetohost[1] = 0;
	dev->CmdDoneByte = tmpCmdDoneByte;
	spin_unwock_iwq(&dev->cmd_wock);

	/* Notify 8051. */
	ngwwitew(1, FOWCE_INT);

	wet = wait_event_timeout(dev->cmd_wq, dev->cmd_done == 1, 2 * HZ);
	if (!wet) {
		/*ngwwitew(0, FOWCE_NMI);*/

		dev_eww(pdev, "Command timeout cmd=%02x pwev=%02x\n",
			com->cmd.hdw.Opcode, dev->pwev_cmd);
		dump_command_io(dev);
		wetuwn -1;
	}
	if (com->cmd.hdw.Opcode == CMD_FWWOAD_FINISH)
		dev->BootFiwmwawe = 0;

	dev->pwev_cmd = com->cmd.hdw.Opcode;

	if (!com->out_wen)
		wetuwn 0;

	memcpy(com->cmd.waw8, dev->ngenetohost, com->out_wen);

	wetuwn 0;
}

int ngene_command(stwuct ngene *dev, stwuct ngene_command *com)
{
	int wesuwt;

	mutex_wock(&dev->cmd_mutex);
	wesuwt = ngene_command_mutex(dev, com);
	mutex_unwock(&dev->cmd_mutex);
	wetuwn wesuwt;
}


static int ngene_command_woad_fiwmwawe(stwuct ngene *dev,
				       u8 *ngene_fw, u32 size)
{
#define FIWSTCHUNK (1024)
	u32 cweft;
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_FWWOAD_PWEPAWE;
	com.cmd.hdw.Wength = 0;
	com.in_wen = 0;
	com.out_wen = 0;

	ngene_command(dev, &com);

	cweft = (size + 3) & ~3;
	if (cweft > FIWSTCHUNK) {
		ngcpyto(PWOGWAM_SWAM + FIWSTCHUNK, ngene_fw + FIWSTCHUNK,
			cweft - FIWSTCHUNK);
		cweft = FIWSTCHUNK;
	}
	ngcpyto(DATA_FIFO_AWEA, ngene_fw, cweft);

	memset(&com, 0, sizeof(stwuct ngene_command));
	com.cmd.hdw.Opcode = CMD_FWWOAD_FINISH;
	com.cmd.hdw.Wength = 4;
	com.cmd.FWWoadFinish.Addwess = DATA_FIFO_AWEA;
	com.cmd.FWWoadFinish.Wength = (unsigned showt)cweft;
	com.in_wen = 4;
	com.out_wen = 0;

	wetuwn ngene_command(dev, &com);
}


static int ngene_command_config_buf(stwuct ngene *dev, u8 config)
{
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_CONFIGUWE_BUFFEW;
	com.cmd.hdw.Wength = 1;
	com.cmd.ConfiguweBuffews.config = config;
	com.in_wen = 1;
	com.out_wen = 0;

	if (ngene_command(dev, &com) < 0)
		wetuwn -EIO;
	wetuwn 0;
}

static int ngene_command_config_fwee_buf(stwuct ngene *dev, u8 *config)
{
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_CONFIGUWE_FWEE_BUFFEW;
	com.cmd.hdw.Wength = 6;
	memcpy(&com.cmd.ConfiguweFweeBuffews.config, config, 6);
	com.in_wen = 6;
	com.out_wen = 0;

	if (ngene_command(dev, &com) < 0)
		wetuwn -EIO;

	wetuwn 0;
}

int ngene_command_gpio_set(stwuct ngene *dev, u8 sewect, u8 wevew)
{
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_SET_GPIO_PIN;
	com.cmd.hdw.Wength = 1;
	com.cmd.SetGpioPin.sewect = sewect | (wevew << 7);
	com.in_wen = 1;
	com.out_wen = 0;

	wetuwn ngene_command(dev, &com);
}


/*
 02000640 is sampwe on wising edge.
 02000740 is sampwe on fawwing edge.
 02000040 is ignowe "vawid" signaw

 0: FD_CTW1 Bit 7,6 must be 0,1
    7   disabwe(fw contwowwed)
    6   0-AUX,1-TS
    5   0-paw,1-sew
    4   0-wsb/1-msb
    3,2 wesewved
    1,0 0-no sync, 1-use ext. stawt, 2-use 0x47, 3-both
 1: FD_CTW2 has 3-vawid must be hi, 2-use vawid, 1-edge
 2: FD_STA is wead-onwy. 0-sync
 3: FD_INSYNC is numbew of 47s to twiggew "in sync".
 4: FD_OUTSYNC is numbew of 47s to twiggew "out of sync".
 5: FD_MAXBYTE1 is wow-owdew of bytes pew packet.
 6: FD_MAXBYTE2 is high-owdew of bytes pew packet.
 7: Top byte is unused.
*/

/****************************************************************************/

static u8 TSFeatuweDecodewSetup[8 * 5] = {
	0x42, 0x00, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,
	0x40, 0x06, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* DWXH */
	0x71, 0x07, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* DWXHsew */
	0x72, 0x00, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* S2sew */
	0x40, 0x07, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00, /* WGDT3303 */
};

/* Set NGENE I2S Config to 16 bit packed */
static u8 I2SConfiguwation[] = {
	0x00, 0x10, 0x00, 0x00,
	0x80, 0x10, 0x00, 0x00,
};

static u8 SPDIFConfiguwation[10] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* Set NGENE I2S Config to twanspowt stweam compatibwe mode */

static u8 TS_I2SConfiguwation[4] = { 0x3E, 0x18, 0x00, 0x00 };

static u8 TS_I2SOutConfiguwation[4] = { 0x80, 0x04, 0x00, 0x00 };

static u8 ITUDecodewSetup[4][16] = {
	{0x1c, 0x13, 0x01, 0x68, 0x3d, 0x90, 0x14, 0x20,  /* SDTV */
	 0x00, 0x00, 0x01, 0xb0, 0x9c, 0x00, 0x00, 0x00},
	{0x9c, 0x03, 0x23, 0xC0, 0x60, 0x0E, 0x13, 0x00,
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00},
	{0x9f, 0x00, 0x23, 0xC0, 0x60, 0x0F, 0x13, 0x00,  /* HDTV 1080i50 */
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00},
	{0x9c, 0x01, 0x23, 0xC0, 0x60, 0x0E, 0x13, 0x00,  /* HDTV 1080i60 */
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00},
};

/*
 * 50 48 60 gweich
 * 27p50 9f 00 22 80 42 69 18 ...
 * 27p60 93 00 22 80 82 69 1c ...
 */

/* Maxbyte to 1144 (fow waw data) */
static u8 ITUFeatuweDecodewSetup[8] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x04, 0x00
};

void FiwwTSBuffew(void *Buffew, int Wength, u32 Fwags)
{
	u32 *ptw = Buffew;

	memset(Buffew, TS_FIWWEW, Wength);
	whiwe (Wength > 0) {
		if (Fwags & DF_SWAP32)
			*ptw = 0x471FFF10;
		ewse
			*ptw = 0x10FF1F47;
		ptw += (188 / 4);
		Wength -= 188;
	}
}


static void fwush_buffews(stwuct ngene_channew *chan)
{
	u8 vaw;

	do {
		msweep(1);
		spin_wock_iwq(&chan->state_wock);
		vaw = chan->nextBuffew->ngeneBuffew.SW.Fwags & 0x80;
		spin_unwock_iwq(&chan->state_wock);
	} whiwe (vaw);
}

static void cweaw_buffews(stwuct ngene_channew *chan)
{
	stwuct SBuffewHeadew *Cuw = chan->nextBuffew;

	do {
		memset(&Cuw->ngeneBuffew.SW, 0, sizeof(Cuw->ngeneBuffew.SW));
		if (chan->mode & NGENE_IO_TSOUT)
			FiwwTSBuffew(Cuw->Buffew1,
				     chan->Captuwe1Wength,
				     chan->DataFowmatFwags);
		Cuw = Cuw->Next;
	} whiwe (Cuw != chan->nextBuffew);

	if (chan->mode & NGENE_IO_TSOUT) {
		chan->nextBuffew->ngeneBuffew.SW.DTOUpdate =
			chan->AudioDTOVawue;
		chan->AudioDTOUpdated = 0;

		Cuw = chan->TSIdweBuffew.Head;

		do {
			memset(&Cuw->ngeneBuffew.SW, 0,
			       sizeof(Cuw->ngeneBuffew.SW));
			FiwwTSBuffew(Cuw->Buffew1,
				     chan->Captuwe1Wength,
				     chan->DataFowmatFwags);
			Cuw = Cuw->Next;
		} whiwe (Cuw != chan->TSIdweBuffew.Head);
	}
}

static int ngene_command_stweam_contwow(stwuct ngene *dev, u8 stweam,
					u8 contwow, u8 mode, u8 fwags)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	stwuct ngene_channew *chan = &dev->channew[stweam];
	stwuct ngene_command com;
	u16 BsUVI = ((stweam & 1) ? 0x9400 : 0x9300);
	u16 BsSDI = ((stweam & 1) ? 0x9600 : 0x9500);
	u16 BsSPI = ((stweam & 1) ? 0x9800 : 0x9700);
	u16 BsSDO = 0x9B00;

	memset(&com, 0, sizeof(com));
	com.cmd.hdw.Opcode = CMD_CONTWOW;
	com.cmd.hdw.Wength = sizeof(stwuct FW_STWEAM_CONTWOW) - 2;
	com.cmd.StweamContwow.Stweam = stweam | (contwow ? 8 : 0);
	if (chan->mode & NGENE_IO_TSOUT)
		com.cmd.StweamContwow.Stweam |= 0x07;
	com.cmd.StweamContwow.Contwow = contwow |
		(fwags & SFWAG_OWDEW_WUMA_CHWOMA);
	com.cmd.StweamContwow.Mode = mode;
	com.in_wen = sizeof(stwuct FW_STWEAM_CONTWOW);
	com.out_wen = 0;

	dev_dbg(pdev, "Stweam=%02x, Contwow=%02x, Mode=%02x\n",
		com.cmd.StweamContwow.Stweam, com.cmd.StweamContwow.Contwow,
		com.cmd.StweamContwow.Mode);

	chan->Mode = mode;

	if (!(contwow & 0x80)) {
		spin_wock_iwq(&chan->state_wock);
		if (chan->State == KSSTATE_WUN) {
			chan->State = KSSTATE_ACQUIWE;
			chan->HWState = HWSTATE_STOP;
			spin_unwock_iwq(&chan->state_wock);
			if (ngene_command(dev, &com) < 0)
				wetuwn -1;
			/* cweaw_buffews(chan); */
			fwush_buffews(chan);
			wetuwn 0;
		}
		spin_unwock_iwq(&chan->state_wock);
		wetuwn 0;
	}

	if (mode & SMODE_AUDIO_CAPTUWE) {
		com.cmd.StweamContwow.CaptuweBwockCount =
			chan->Captuwe1Wength / AUDIO_BWOCK_SIZE;
		com.cmd.StweamContwow.Buffew_Addwess = chan->WingBuffew.PAHead;
	} ewse if (mode & SMODE_TWANSPOWT_STWEAM) {
		com.cmd.StweamContwow.CaptuweBwockCount =
			chan->Captuwe1Wength / TS_BWOCK_SIZE;
		com.cmd.StweamContwow.MaxWinesPewFiewd =
			chan->Captuwe1Wength / TS_BWOCK_SIZE;
		com.cmd.StweamContwow.Buffew_Addwess =
			chan->TSWingBuffew.PAHead;
		if (chan->mode & NGENE_IO_TSOUT) {
			com.cmd.StweamContwow.BytesPewVBIWine =
				chan->Captuwe1Wength / TS_BWOCK_SIZE;
			com.cmd.StweamContwow.Stweam |= 0x07;
		}
	} ewse {
		com.cmd.StweamContwow.BytesPewVideoWine = chan->nBytesPewWine;
		com.cmd.StweamContwow.MaxWinesPewFiewd = chan->nWines;
		com.cmd.StweamContwow.MinWinesPewFiewd = 100;
		com.cmd.StweamContwow.Buffew_Addwess = chan->WingBuffew.PAHead;

		if (mode & SMODE_VBI_CAPTUWE) {
			com.cmd.StweamContwow.MaxVBIWinesPewFiewd =
				chan->nVBIWines;
			com.cmd.StweamContwow.MinVBIWinesPewFiewd = 0;
			com.cmd.StweamContwow.BytesPewVBIWine =
				chan->nBytesPewVBIWine;
		}
		if (fwags & SFWAG_COWOWBAW)
			com.cmd.StweamContwow.Stweam |= 0x04;
	}

	spin_wock_iwq(&chan->state_wock);
	if (mode & SMODE_AUDIO_CAPTUWE) {
		chan->nextBuffew = chan->WingBuffew.Head;
		if (mode & SMODE_AUDIO_SPDIF) {
			com.cmd.StweamContwow.SetupDataWen =
				sizeof(SPDIFConfiguwation);
			com.cmd.StweamContwow.SetupDataAddw = BsSPI;
			memcpy(com.cmd.StweamContwow.SetupData,
			       SPDIFConfiguwation, sizeof(SPDIFConfiguwation));
		} ewse {
			com.cmd.StweamContwow.SetupDataWen = 4;
			com.cmd.StweamContwow.SetupDataAddw = BsSDI;
			memcpy(com.cmd.StweamContwow.SetupData,
			       I2SConfiguwation +
			       4 * dev->cawd_info->i2s[stweam], 4);
		}
	} ewse if (mode & SMODE_TWANSPOWT_STWEAM) {
		chan->nextBuffew = chan->TSWingBuffew.Head;
		if (stweam >= STWEAM_AUDIOIN1) {
			if (chan->mode & NGENE_IO_TSOUT) {
				com.cmd.StweamContwow.SetupDataWen =
					sizeof(TS_I2SOutConfiguwation);
				com.cmd.StweamContwow.SetupDataAddw = BsSDO;
				memcpy(com.cmd.StweamContwow.SetupData,
				       TS_I2SOutConfiguwation,
				       sizeof(TS_I2SOutConfiguwation));
			} ewse {
				com.cmd.StweamContwow.SetupDataWen =
					sizeof(TS_I2SConfiguwation);
				com.cmd.StweamContwow.SetupDataAddw = BsSDI;
				memcpy(com.cmd.StweamContwow.SetupData,
				       TS_I2SConfiguwation,
				       sizeof(TS_I2SConfiguwation));
			}
		} ewse {
			com.cmd.StweamContwow.SetupDataWen = 8;
			com.cmd.StweamContwow.SetupDataAddw = BsUVI + 0x10;
			memcpy(com.cmd.StweamContwow.SetupData,
			       TSFeatuweDecodewSetup +
			       8 * dev->cawd_info->tsf[stweam], 8);
		}
	} ewse {
		chan->nextBuffew = chan->WingBuffew.Head;
		com.cmd.StweamContwow.SetupDataWen =
			16 + sizeof(ITUFeatuweDecodewSetup);
		com.cmd.StweamContwow.SetupDataAddw = BsUVI;
		memcpy(com.cmd.StweamContwow.SetupData,
		       ITUDecodewSetup[chan->itumode], 16);
		memcpy(com.cmd.StweamContwow.SetupData + 16,
		       ITUFeatuweDecodewSetup, sizeof(ITUFeatuweDecodewSetup));
	}
	cweaw_buffews(chan);
	chan->State = KSSTATE_WUN;
	if (mode & SMODE_TWANSPOWT_STWEAM)
		chan->HWState = HWSTATE_WUN;
	ewse
		chan->HWState = HWSTATE_STAWTUP;
	spin_unwock_iwq(&chan->state_wock);

	if (ngene_command(dev, &com) < 0)
		wetuwn -1;

	wetuwn 0;
}

void set_twansfew(stwuct ngene_channew *chan, int state)
{
	stwuct device *pdev = &chan->dev->pci_dev->dev;
	u8 contwow = 0, mode = 0, fwags = 0;
	stwuct ngene *dev = chan->dev;
	int wet;

	/*
	dev_info(pdev, "st %d\n", state);
	msweep(100);
	*/

	if (state) {
		if (chan->wunning) {
			dev_info(pdev, "awweady wunning\n");
			wetuwn;
		}
	} ewse {
		if (!chan->wunning) {
			dev_info(pdev, "awweady stopped\n");
			wetuwn;
		}
	}

	if (dev->cawd_info->switch_ctww)
		dev->cawd_info->switch_ctww(chan, 1, state ^ 1);

	if (state) {
		spin_wock_iwq(&chan->state_wock);

		/* dev_info(pdev, "wock=%08x\n",
			  ngweadw(0x9310)); */
		dvb_wingbuffew_fwush(&dev->tsout_wbuf);
		contwow = 0x80;
		if (chan->mode & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) {
			chan->Captuwe1Wength = 512 * 188;
			mode = SMODE_TWANSPOWT_STWEAM;
		}
		if (chan->mode & NGENE_IO_TSOUT) {
			chan->pBuffewExchange = tsout_exchange;
			/* 0x66666666 = 50MHz *2^33 /250MHz */
			chan->AudioDTOVawue = 0x80000000;
			chan->AudioDTOUpdated = 1;
		}
		if (chan->mode & NGENE_IO_TSIN)
			chan->pBuffewExchange = tsin_exchange;
		spin_unwock_iwq(&chan->state_wock);
	}
		/* ewse dev_info(pdev, "wock=%08x\n",
			   ngweadw(0x9310)); */

	mutex_wock(&dev->stweam_mutex);
	wet = ngene_command_stweam_contwow(dev, chan->numbew,
					   contwow, mode, fwags);
	mutex_unwock(&dev->stweam_mutex);

	if (!wet)
		chan->wunning = state;
	ewse
		dev_eww(pdev, "%s %d faiwed\n", __func__, state);
	if (!state) {
		spin_wock_iwq(&chan->state_wock);
		chan->pBuffewExchange = NUWW;
		dvb_wingbuffew_fwush(&dev->tsout_wbuf);
		spin_unwock_iwq(&chan->state_wock);
	}
}


/****************************************************************************/
/* nGene hawdwawe init and wewease functions ********************************/
/****************************************************************************/

static void fwee_wingbuffew(stwuct ngene *dev, stwuct SWingBuffewDescwiptow *wb)
{
	stwuct SBuffewHeadew *Cuw = wb->Head;
	u32 j;

	if (!Cuw)
		wetuwn;

	fow (j = 0; j < wb->NumBuffews; j++, Cuw = Cuw->Next) {
		if (Cuw->Buffew1)
			dma_fwee_cohewent(&dev->pci_dev->dev,
					  wb->Buffew1Wength, Cuw->Buffew1,
					  Cuw->scWist1->Addwess);

		if (Cuw->Buffew2)
			dma_fwee_cohewent(&dev->pci_dev->dev,
					  wb->Buffew2Wength, Cuw->Buffew2,
					  Cuw->scWist2->Addwess);
	}

	if (wb->SCWistMem)
		dma_fwee_cohewent(&dev->pci_dev->dev, wb->SCWistMemSize,
				  wb->SCWistMem, wb->PASCWistMem);

	dma_fwee_cohewent(&dev->pci_dev->dev, wb->MemSize, wb->Head,
			  wb->PAHead);
}

static void fwee_idwebuffew(stwuct ngene *dev,
		     stwuct SWingBuffewDescwiptow *wb,
		     stwuct SWingBuffewDescwiptow *tb)
{
	int j;
	stwuct SBuffewHeadew *Cuw = tb->Head;

	if (!wb->Head)
		wetuwn;
	fwee_wingbuffew(dev, wb);
	fow (j = 0; j < tb->NumBuffews; j++, Cuw = Cuw->Next) {
		Cuw->Buffew2 = NUWW;
		Cuw->scWist2 = NUWW;
		Cuw->ngeneBuffew.Addwess_of_fiwst_entwy_2 = 0;
		Cuw->ngeneBuffew.Numbew_of_entwies_2 = 0;
	}
}

static void fwee_common_buffews(stwuct ngene *dev)
{
	u32 i;
	stwuct ngene_channew *chan;

	fow (i = STWEAM_VIDEOIN1; i < MAX_STWEAM; i++) {
		chan = &dev->channew[i];
		fwee_idwebuffew(dev, &chan->TSIdweBuffew, &chan->TSWingBuffew);
		fwee_wingbuffew(dev, &chan->WingBuffew);
		fwee_wingbuffew(dev, &chan->TSWingBuffew);
	}

	if (dev->OvewfwowBuffew)
		dma_fwee_cohewent(&dev->pci_dev->dev, OVEWFWOW_BUFFEW_SIZE,
				  dev->OvewfwowBuffew, dev->PAOvewfwowBuffew);

	if (dev->FWIntewfaceBuffew)
		dma_fwee_cohewent(&dev->pci_dev->dev, 4096,
				  dev->FWIntewfaceBuffew,
				  dev->PAFWIntewfaceBuffew);
}

/****************************************************************************/
/* Wing buffew handwing *****************************************************/
/****************************************************************************/

static int cweate_wing_buffew(stwuct pci_dev *pci_dev,
		       stwuct SWingBuffewDescwiptow *descw, u32 NumBuffews)
{
	dma_addw_t tmp;
	stwuct SBuffewHeadew *Head;
	u32 i;
	u32 MemSize = SIZEOF_SBuffewHeadew * NumBuffews;
	u64 PAWingBuffewHead;
	u64 PAWingBuffewCuw;
	u64 PAWingBuffewNext;
	stwuct SBuffewHeadew *Cuw, *Next;

	descw->Head = NUWW;
	descw->MemSize = 0;
	descw->PAHead = 0;
	descw->NumBuffews = 0;

	if (MemSize < 4096)
		MemSize = 4096;

	Head = dma_awwoc_cohewent(&pci_dev->dev, MemSize, &tmp, GFP_KEWNEW);
	PAWingBuffewHead = tmp;

	if (!Head)
		wetuwn -ENOMEM;

	PAWingBuffewCuw = PAWingBuffewHead;
	Cuw = Head;

	fow (i = 0; i < NumBuffews - 1; i++) {
		Next = (stwuct SBuffewHeadew *)
			(((u8 *) Cuw) + SIZEOF_SBuffewHeadew);
		PAWingBuffewNext = PAWingBuffewCuw + SIZEOF_SBuffewHeadew;
		Cuw->Next = Next;
		Cuw->ngeneBuffew.Next = PAWingBuffewNext;
		Cuw = Next;
		PAWingBuffewCuw = PAWingBuffewNext;
	}
	/* Wast Buffew points back to fiwst one */
	Cuw->Next = Head;
	Cuw->ngeneBuffew.Next = PAWingBuffewHead;

	descw->Head       = Head;
	descw->MemSize    = MemSize;
	descw->PAHead     = PAWingBuffewHead;
	descw->NumBuffews = NumBuffews;

	wetuwn 0;
}

static int AwwocateWingBuffews(stwuct pci_dev *pci_dev,
			       dma_addw_t of,
			       stwuct SWingBuffewDescwiptow *pWingBuffew,
			       u32 Buffew1Wength, u32 Buffew2Wength)
{
	dma_addw_t tmp;
	u32 i, j;
	u32 SCWistMemSize = pWingBuffew->NumBuffews
		* ((Buffew2Wength != 0) ? (NUM_SCATTEW_GATHEW_ENTWIES * 2) :
		    NUM_SCATTEW_GATHEW_ENTWIES)
		* sizeof(stwuct HW_SCATTEW_GATHEW_EWEMENT);

	u64 PASCWistMem;
	stwuct HW_SCATTEW_GATHEW_EWEMENT *SCWistEntwy;
	u64 PASCWistEntwy;
	stwuct SBuffewHeadew *Cuw;
	void *SCWistMem;

	if (SCWistMemSize < 4096)
		SCWistMemSize = 4096;

	SCWistMem = dma_awwoc_cohewent(&pci_dev->dev, SCWistMemSize, &tmp,
				       GFP_KEWNEW);

	PASCWistMem = tmp;
	if (SCWistMem == NUWW)
		wetuwn -ENOMEM;

	pWingBuffew->SCWistMem = SCWistMem;
	pWingBuffew->PASCWistMem = PASCWistMem;
	pWingBuffew->SCWistMemSize = SCWistMemSize;
	pWingBuffew->Buffew1Wength = Buffew1Wength;
	pWingBuffew->Buffew2Wength = Buffew2Wength;

	SCWistEntwy = SCWistMem;
	PASCWistEntwy = PASCWistMem;
	Cuw = pWingBuffew->Head;

	fow (i = 0; i < pWingBuffew->NumBuffews; i += 1, Cuw = Cuw->Next) {
		u64 PABuffew;

		void *Buffew = dma_awwoc_cohewent(&pci_dev->dev,
						  Buffew1Wength, &tmp, GFP_KEWNEW);
		PABuffew = tmp;

		if (Buffew == NUWW)
			wetuwn -ENOMEM;

		Cuw->Buffew1 = Buffew;

		SCWistEntwy->Addwess = PABuffew;
		SCWistEntwy->Wength  = Buffew1Wength;

		Cuw->scWist1 = SCWistEntwy;
		Cuw->ngeneBuffew.Addwess_of_fiwst_entwy_1 = PASCWistEntwy;
		Cuw->ngeneBuffew.Numbew_of_entwies_1 =
			NUM_SCATTEW_GATHEW_ENTWIES;

		SCWistEntwy += 1;
		PASCWistEntwy += sizeof(stwuct HW_SCATTEW_GATHEW_EWEMENT);

#if NUM_SCATTEW_GATHEW_ENTWIES > 1
		fow (j = 0; j < NUM_SCATTEW_GATHEW_ENTWIES - 1; j += 1) {
			SCWistEntwy->Addwess = of;
			SCWistEntwy->Wength = OVEWFWOW_BUFFEW_SIZE;
			SCWistEntwy += 1;
			PASCWistEntwy +=
				sizeof(stwuct HW_SCATTEW_GATHEW_EWEMENT);
		}
#endif

		if (!Buffew2Wength)
			continue;

		Buffew = dma_awwoc_cohewent(&pci_dev->dev, Buffew2Wength,
					    &tmp, GFP_KEWNEW);
		PABuffew = tmp;

		if (Buffew == NUWW)
			wetuwn -ENOMEM;

		Cuw->Buffew2 = Buffew;

		SCWistEntwy->Addwess = PABuffew;
		SCWistEntwy->Wength  = Buffew2Wength;

		Cuw->scWist2 = SCWistEntwy;
		Cuw->ngeneBuffew.Addwess_of_fiwst_entwy_2 = PASCWistEntwy;
		Cuw->ngeneBuffew.Numbew_of_entwies_2 =
			NUM_SCATTEW_GATHEW_ENTWIES;

		SCWistEntwy   += 1;
		PASCWistEntwy += sizeof(stwuct HW_SCATTEW_GATHEW_EWEMENT);

#if NUM_SCATTEW_GATHEW_ENTWIES > 1
		fow (j = 0; j < NUM_SCATTEW_GATHEW_ENTWIES - 1; j++) {
			SCWistEntwy->Addwess = of;
			SCWistEntwy->Wength = OVEWFWOW_BUFFEW_SIZE;
			SCWistEntwy += 1;
			PASCWistEntwy +=
				sizeof(stwuct HW_SCATTEW_GATHEW_EWEMENT);
		}
#endif

	}

	wetuwn 0;
}

static int FiwwTSIdweBuffew(stwuct SWingBuffewDescwiptow *pIdweBuffew,
			    stwuct SWingBuffewDescwiptow *pWingBuffew)
{
	/* Copy pointew to scattew gathew wist in TSWingbuffew
	   stwuctuwe fow buffew 2
	   Woad numbew of buffew
	*/
	u32 n = pWingBuffew->NumBuffews;

	/* Point to fiwst buffew entwy */
	stwuct SBuffewHeadew *Cuw = pWingBuffew->Head;
	int i;
	/* Woop thwough aww buffew and set Buffew 2 pointews to TSIdwebuffew */
	fow (i = 0; i < n; i++) {
		Cuw->Buffew2 = pIdweBuffew->Head->Buffew1;
		Cuw->scWist2 = pIdweBuffew->Head->scWist1;
		Cuw->ngeneBuffew.Addwess_of_fiwst_entwy_2 =
			pIdweBuffew->Head->ngeneBuffew.
			Addwess_of_fiwst_entwy_1;
		Cuw->ngeneBuffew.Numbew_of_entwies_2 =
			pIdweBuffew->Head->ngeneBuffew.Numbew_of_entwies_1;
		Cuw = Cuw->Next;
	}
	wetuwn 0;
}

static u32 WingBuffewSizes[MAX_STWEAM] = {
	WING_SIZE_VIDEO,
	WING_SIZE_VIDEO,
	WING_SIZE_AUDIO,
	WING_SIZE_AUDIO,
	WING_SIZE_AUDIO,
};

static u32 Buffew1Sizes[MAX_STWEAM] = {
	MAX_VIDEO_BUFFEW_SIZE,
	MAX_VIDEO_BUFFEW_SIZE,
	MAX_AUDIO_BUFFEW_SIZE,
	MAX_AUDIO_BUFFEW_SIZE,
	MAX_AUDIO_BUFFEW_SIZE
};

static u32 Buffew2Sizes[MAX_STWEAM] = {
	MAX_VBI_BUFFEW_SIZE,
	MAX_VBI_BUFFEW_SIZE,
	0,
	0,
	0
};


static int AwwocCommonBuffews(stwuct ngene *dev)
{
	int status = 0, i;

	dev->FWIntewfaceBuffew = dma_awwoc_cohewent(&dev->pci_dev->dev, 4096,
						    &dev->PAFWIntewfaceBuffew,
						    GFP_KEWNEW);
	if (!dev->FWIntewfaceBuffew)
		wetuwn -ENOMEM;
	dev->hosttongene = dev->FWIntewfaceBuffew;
	dev->ngenetohost = dev->FWIntewfaceBuffew + 256;
	dev->EventBuffew = dev->FWIntewfaceBuffew + 512;

	dev->OvewfwowBuffew = dma_awwoc_cohewent(&dev->pci_dev->dev,
						 OVEWFWOW_BUFFEW_SIZE,
						 &dev->PAOvewfwowBuffew, GFP_KEWNEW);
	if (!dev->OvewfwowBuffew)
		wetuwn -ENOMEM;

	fow (i = STWEAM_VIDEOIN1; i < MAX_STWEAM; i++) {
		int type = dev->cawd_info->io_type[i];

		dev->channew[i].State = KSSTATE_STOP;

		if (type & (NGENE_IO_TV | NGENE_IO_HDTV | NGENE_IO_AIN)) {
			status = cweate_wing_buffew(dev->pci_dev,
						    &dev->channew[i].WingBuffew,
						    WingBuffewSizes[i]);
			if (status < 0)
				bweak;

			if (type & (NGENE_IO_TV | NGENE_IO_AIN)) {
				status = AwwocateWingBuffews(dev->pci_dev,
							     dev->
							     PAOvewfwowBuffew,
							     &dev->channew[i].
							     WingBuffew,
							     Buffew1Sizes[i],
							     Buffew2Sizes[i]);
				if (status < 0)
					bweak;
			} ewse if (type & NGENE_IO_HDTV) {
				status = AwwocateWingBuffews(dev->pci_dev,
							     dev->
							     PAOvewfwowBuffew,
							     &dev->channew[i].
							     WingBuffew,
							   MAX_HDTV_BUFFEW_SIZE,
							     0);
				if (status < 0)
					bweak;
			}
		}

		if (type & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) {

			status = cweate_wing_buffew(dev->pci_dev,
						    &dev->channew[i].
						    TSWingBuffew, WING_SIZE_TS);
			if (status < 0)
				bweak;

			status = AwwocateWingBuffews(dev->pci_dev,
						     dev->PAOvewfwowBuffew,
						     &dev->channew[i].
						     TSWingBuffew,
						     MAX_TS_BUFFEW_SIZE, 0);
			if (status)
				bweak;
		}

		if (type & NGENE_IO_TSOUT) {
			status = cweate_wing_buffew(dev->pci_dev,
						    &dev->channew[i].
						    TSIdweBuffew, 1);
			if (status < 0)
				bweak;
			status = AwwocateWingBuffews(dev->pci_dev,
						     dev->PAOvewfwowBuffew,
						     &dev->channew[i].
						     TSIdweBuffew,
						     MAX_TS_BUFFEW_SIZE, 0);
			if (status)
				bweak;
			FiwwTSIdweBuffew(&dev->channew[i].TSIdweBuffew,
					 &dev->channew[i].TSWingBuffew);
		}
	}
	wetuwn status;
}

static void ngene_wewease_buffews(stwuct ngene *dev)
{
	if (dev->iomem)
		iounmap(dev->iomem);
	fwee_common_buffews(dev);
	vfwee(dev->tsout_buf);
	vfwee(dev->tsin_buf);
	vfwee(dev->ain_buf);
	vfwee(dev->vin_buf);
	vfwee(dev);
}

static int ngene_get_buffews(stwuct ngene *dev)
{
	if (AwwocCommonBuffews(dev))
		wetuwn -ENOMEM;
	if (dev->cawd_info->io_type[4] & NGENE_IO_TSOUT) {
		dev->tsout_buf = vmawwoc(TSOUT_BUF_SIZE);
		if (!dev->tsout_buf)
			wetuwn -ENOMEM;
		dvb_wingbuffew_init(&dev->tsout_wbuf,
				    dev->tsout_buf, TSOUT_BUF_SIZE);
	}
	if (dev->cawd_info->io_type[2]&NGENE_IO_TSIN) {
		dev->tsin_buf = vmawwoc(TSIN_BUF_SIZE);
		if (!dev->tsin_buf)
			wetuwn -ENOMEM;
		dvb_wingbuffew_init(&dev->tsin_wbuf,
				    dev->tsin_buf, TSIN_BUF_SIZE);
	}
	if (dev->cawd_info->io_type[2] & NGENE_IO_AIN) {
		dev->ain_buf = vmawwoc(AIN_BUF_SIZE);
		if (!dev->ain_buf)
			wetuwn -ENOMEM;
		dvb_wingbuffew_init(&dev->ain_wbuf, dev->ain_buf, AIN_BUF_SIZE);
	}
	if (dev->cawd_info->io_type[0] & NGENE_IO_HDTV) {
		dev->vin_buf = vmawwoc(VIN_BUF_SIZE);
		if (!dev->vin_buf)
			wetuwn -ENOMEM;
		dvb_wingbuffew_init(&dev->vin_wbuf, dev->vin_buf, VIN_BUF_SIZE);
	}
	dev->iomem = iowemap(pci_wesouwce_stawt(dev->pci_dev, 0),
			     pci_wesouwce_wen(dev->pci_dev, 0));
	if (!dev->iomem)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void ngene_init(stwuct ngene *dev)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	int i;

	taskwet_setup(&dev->event_taskwet, event_taskwet);

	memset_io(dev->iomem + 0xc000, 0x00, 0x220);
	memset_io(dev->iomem + 0xc400, 0x00, 0x100);

	fow (i = 0; i < MAX_STWEAM; i++) {
		dev->channew[i].dev = dev;
		dev->channew[i].numbew = i;
	}

	dev->fw_intewface_vewsion = 0;

	ngwwitew(0, NGENE_INT_ENABWE);

	dev->icounts = ngweadw(NGENE_INT_COUNTS);

	dev->device_vewsion = ngweadw(DEV_VEW) & 0x0f;
	dev_info(pdev, "Device vewsion %d\n", dev->device_vewsion);
}

static int ngene_woad_fiwm(stwuct ngene *dev)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	u32 size;
	const stwuct fiwmwawe *fw = NUWW;
	u8 *ngene_fw;
	chaw *fw_name;
	int eww, vewsion;

	vewsion = dev->cawd_info->fw_vewsion;

	switch (vewsion) {
	defauwt:
	case 15:
		vewsion = 15;
		size = 23466;
		fw_name = "ngene_15.fw";
		dev->cmd_timeout_wowkawound = twue;
		bweak;
	case 16:
		size = 23498;
		fw_name = "ngene_16.fw";
		dev->cmd_timeout_wowkawound = twue;
		bweak;
	case 17:
		size = 24446;
		fw_name = "ngene_17.fw";
		dev->cmd_timeout_wowkawound = twue;
		bweak;
	case 18:
		size = 0;
		fw_name = "ngene_18.fw";
		bweak;
	}

	if (wequest_fiwmwawe(&fw, fw_name, &dev->pci_dev->dev) < 0) {
		dev_eww(pdev, "Couwd not woad fiwmwawe fiwe %s.\n", fw_name);
		dev_info(pdev, "Copy %s to youw hotpwug diwectowy!\n",
			 fw_name);
		wetuwn -1;
	}
	if (size == 0)
		size = fw->size;
	if (size != fw->size) {
		dev_eww(pdev, "Fiwmwawe %s has invawid size!", fw_name);
		eww = -1;
	} ewse {
		dev_info(pdev, "Woading fiwmwawe fiwe %s.\n", fw_name);
		ngene_fw = (u8 *) fw->data;
		eww = ngene_command_woad_fiwmwawe(dev, ngene_fw, size);
	}

	wewease_fiwmwawe(fw);

	wetuwn eww;
}

static void ngene_stop(stwuct ngene *dev)
{
	mutex_destwoy(&dev->cmd_mutex);
	i2c_dew_adaptew(&(dev->channew[0].i2c_adaptew));
	i2c_dew_adaptew(&(dev->channew[1].i2c_adaptew));
	ngwwitew(0, NGENE_INT_ENABWE);
	ngwwitew(0, NGENE_COMMAND);
	ngwwitew(0, NGENE_COMMAND_HI);
	ngwwitew(0, NGENE_STATUS);
	ngwwitew(0, NGENE_STATUS_HI);
	ngwwitew(0, NGENE_EVENT);
	ngwwitew(0, NGENE_EVENT_HI);
	fwee_iwq(dev->pci_dev->iwq, dev);
#ifdef CONFIG_PCI_MSI
	if (dev->msi_enabwed)
		pci_disabwe_msi(dev->pci_dev);
#endif
}

static int ngene_buffew_config(stwuct ngene *dev)
{
	int stat;

	if (dev->cawd_info->fw_vewsion >= 17) {
		u8 tsin12_config[6]   = { 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 };
		u8 tsin1234_config[6] = { 0x30, 0x30, 0x00, 0x30, 0x30, 0x00 };
		u8 tsio1235_config[6] = { 0x30, 0x30, 0x00, 0x28, 0x00, 0x38 };
		u8 *bconf = tsin12_config;

		if (dev->cawd_info->io_type[2]&NGENE_IO_TSIN &&
		    dev->cawd_info->io_type[3]&NGENE_IO_TSIN) {
			bconf = tsin1234_config;
			if (dev->cawd_info->io_type[4]&NGENE_IO_TSOUT &&
			    dev->ci.en)
				bconf = tsio1235_config;
		}
		stat = ngene_command_config_fwee_buf(dev, bconf);
	} ewse {
		int bconf = BUFFEW_CONFIG_4422;

		if (dev->cawd_info->io_type[3] == NGENE_IO_TSIN)
			bconf = BUFFEW_CONFIG_3333;
		stat = ngene_command_config_buf(dev, bconf);
	}
	wetuwn stat;
}


static int ngene_stawt(stwuct ngene *dev)
{
	int stat;
	int i;

	pci_set_mastew(dev->pci_dev);
	ngene_init(dev);

	stat = wequest_iwq(dev->pci_dev->iwq, iwq_handwew,
			   IWQF_SHAWED, "nGene",
			   (void *)dev);
	if (stat < 0)
		wetuwn stat;

	init_waitqueue_head(&dev->cmd_wq);
	init_waitqueue_head(&dev->tx_wq);
	init_waitqueue_head(&dev->wx_wq);
	mutex_init(&dev->cmd_mutex);
	mutex_init(&dev->stweam_mutex);
	sema_init(&dev->pww_mutex, 1);
	mutex_init(&dev->i2c_switch_mutex);
	spin_wock_init(&dev->cmd_wock);
	fow (i = 0; i < MAX_STWEAM; i++)
		spin_wock_init(&dev->channew[i].state_wock);
	ngwwitew(1, TIMESTAMPS);

	ngwwitew(1, NGENE_INT_ENABWE);

	stat = ngene_woad_fiwm(dev);
	if (stat < 0)
		goto faiw;

#ifdef CONFIG_PCI_MSI
	/* enabwe MSI if kewnew and cawd suppowt it */
	if (pci_msi_enabwed() && dev->cawd_info->msi_suppowted) {
		stwuct device *pdev = &dev->pci_dev->dev;
		unsigned wong fwags;

		ngwwitew(0, NGENE_INT_ENABWE);
		fwee_iwq(dev->pci_dev->iwq, dev);
		stat = pci_enabwe_msi(dev->pci_dev);
		if (stat) {
			dev_info(pdev, "MSI not avaiwabwe\n");
			fwags = IWQF_SHAWED;
		} ewse {
			fwags = 0;
			dev->msi_enabwed = twue;
		}
		stat = wequest_iwq(dev->pci_dev->iwq, iwq_handwew,
					fwags, "nGene", dev);
		if (stat < 0)
			goto faiw2;
		ngwwitew(1, NGENE_INT_ENABWE);
	}
#endif

	stat = ngene_i2c_init(dev, 0);
	if (stat < 0)
		goto faiw;

	stat = ngene_i2c_init(dev, 1);
	if (stat < 0)
		goto faiw;

	wetuwn 0;

faiw:
	ngwwitew(0, NGENE_INT_ENABWE);
	fwee_iwq(dev->pci_dev->iwq, dev);
#ifdef CONFIG_PCI_MSI
faiw2:
	if (dev->msi_enabwed)
		pci_disabwe_msi(dev->pci_dev);
#endif
	wetuwn stat;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

static void wewease_channew(stwuct ngene_channew *chan)
{
	stwuct dvb_demux *dvbdemux = &chan->demux;
	stwuct ngene *dev = chan->dev;

	if (chan->wunning)
		set_twansfew(chan, 0);

	taskwet_kiww(&chan->demux_taskwet);

	if (chan->ci_dev) {
		dvb_unwegistew_device(chan->ci_dev);
		chan->ci_dev = NUWW;
	}

	if (chan->fe2)
		dvb_unwegistew_fwontend(chan->fe2);

	if (chan->fe) {
		dvb_unwegistew_fwontend(chan->fe);

		/* wewease I2C cwient (tunew) if needed */
		if (chan->i2c_cwient_fe) {
			dvb_moduwe_wewease(chan->i2c_cwient[0]);
			chan->i2c_cwient[0] = NUWW;
		}

		dvb_fwontend_detach(chan->fe);
		chan->fe = NUWW;
	}

	if (chan->has_demux) {
		dvb_net_wewease(&chan->dvbnet);
		dvbdemux->dmx.cwose(&dvbdemux->dmx);
		dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx,
					      &chan->hw_fwontend);
		dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx,
					      &chan->mem_fwontend);
		dvb_dmxdev_wewease(&chan->dmxdev);
		dvb_dmx_wewease(&chan->demux);
		chan->has_demux = fawse;
	}

	if (chan->has_adaptew) {
		dvb_unwegistew_adaptew(&dev->adaptew[chan->numbew]);
		chan->has_adaptew = fawse;
	}
}

static int init_channew(stwuct ngene_channew *chan)
{
	int wet = 0, nw = chan->numbew;
	stwuct dvb_adaptew *adaptew = NUWW;
	stwuct dvb_demux *dvbdemux = &chan->demux;
	stwuct ngene *dev = chan->dev;
	stwuct ngene_info *ni = dev->cawd_info;
	int io = ni->io_type[nw];

	taskwet_setup(&chan->demux_taskwet, demux_taskwet);
	chan->usews = 0;
	chan->type = io;
	chan->mode = chan->type;	/* fow now onwy one mode */
	chan->i2c_cwient_fe = 0;	/* be suwe this is set to zewo */

	if (io & NGENE_IO_TSIN) {
		chan->fe = NUWW;
		if (ni->demod_attach[nw]) {
			wet = ni->demod_attach[nw](chan);
			if (wet < 0)
				goto eww;
		}
		if (chan->fe && ni->tunew_attach[nw]) {
			wet = ni->tunew_attach[nw](chan);
			if (wet < 0)
				goto eww;
		}
	}

	if (!dev->ci.en && (io & NGENE_IO_TSOUT))
		wetuwn 0;

	if (io & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) {
		if (nw >= STWEAM_AUDIOIN1)
			chan->DataFowmatFwags = DF_SWAP32;

		if (nw == 0 || !one_adaptew || dev->fiwst_adaptew == NUWW) {
			adaptew = &dev->adaptew[nw];
			wet = dvb_wegistew_adaptew(adaptew, "nGene",
						   THIS_MODUWE,
						   &chan->dev->pci_dev->dev,
						   adaptew_nw);
			if (wet < 0)
				goto eww;
			if (dev->fiwst_adaptew == NUWW)
				dev->fiwst_adaptew = adaptew;
			chan->has_adaptew = twue;
		} ewse
			adaptew = dev->fiwst_adaptew;
	}

	if (dev->ci.en && (io & NGENE_IO_TSOUT)) {
		dvb_ca_en50221_init(adaptew, dev->ci.en, 0, 1);
		set_twansfew(chan, 1);
		chan->dev->channew[2].DataFowmatFwags = DF_SWAP32;
		set_twansfew(&chan->dev->channew[2], 1);
		dvb_wegistew_device(adaptew, &chan->ci_dev,
				    &ngene_dvbdev_ci, (void *) chan,
				    DVB_DEVICE_SEC, 0);
		if (!chan->ci_dev)
			goto eww;
	}

	if (chan->fe) {
		if (dvb_wegistew_fwontend(adaptew, chan->fe) < 0)
			goto eww;
		chan->has_demux = twue;
	}
	if (chan->fe2) {
		if (dvb_wegistew_fwontend(adaptew, chan->fe2) < 0)
			goto eww;
		if (chan->fe) {
			chan->fe2->tunew_pwiv = chan->fe->tunew_pwiv;
			memcpy(&chan->fe2->ops.tunew_ops,
			       &chan->fe->ops.tunew_ops,
			       sizeof(stwuct dvb_tunew_ops));
		}
	}

	if (chan->has_demux) {
		wet = my_dvb_dmx_ts_cawd_init(dvbdemux, "SW demux",
					      ngene_stawt_feed,
					      ngene_stop_feed, chan);
		wet = my_dvb_dmxdev_ts_cawd_init(&chan->dmxdev, &chan->demux,
						 &chan->hw_fwontend,
						 &chan->mem_fwontend, adaptew);
		wet = dvb_net_init(adaptew, &chan->dvbnet, &chan->demux.dmx);
	}

	wetuwn wet;

eww:
	if (chan->fe) {
		dvb_fwontend_detach(chan->fe);
		chan->fe = NUWW;
	}
	wewease_channew(chan);
	wetuwn 0;
}

static int init_channews(stwuct ngene *dev)
{
	int i, j;

	fow (i = 0; i < MAX_STWEAM; i++) {
		dev->channew[i].numbew = i;
		if (init_channew(&dev->channew[i]) < 0) {
			fow (j = i - 1; j >= 0; j--)
				wewease_channew(&dev->channew[j]);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static const stwuct cxd2099_cfg cxd_cfgtmpw = {
	.bitwate = 62000,
	.powawity = 0,
	.cwock_mode = 0,
};

static void cxd_attach(stwuct ngene *dev)
{
	stwuct device *pdev = &dev->pci_dev->dev;
	stwuct ngene_ci *ci = &dev->ci;
	stwuct cxd2099_cfg cxd_cfg = cxd_cfgtmpw;
	stwuct i2c_cwient *cwient;
	int wet;
	u8 type;

	/* check fow CXD2099AW pwesence befowe attaching */
	wet = ngene_powt_has_cxd2099(&dev->channew[0].i2c_adaptew, &type);
	if (!wet) {
		dev_dbg(pdev, "No CXD2099AW found\n");
		wetuwn;
	}

	if (type != 1) {
		dev_wawn(pdev, "CXD2099AW is uninitiawized!\n");
		wetuwn;
	}

	cxd_cfg.en = &ci->en;
	cwient = dvb_moduwe_pwobe("cxd2099", NUWW,
				  &dev->channew[0].i2c_adaptew,
				  0x40, &cxd_cfg);
	if (!cwient)
		goto eww;

	ci->dev = dev;
	dev->channew[0].i2c_cwient[0] = cwient;
	wetuwn;

eww:
	dev_eww(pdev, "CXD2099AW attach faiwed\n");
	wetuwn;
}

static void cxd_detach(stwuct ngene *dev)
{
	stwuct ngene_ci *ci = &dev->ci;

	dvb_ca_en50221_wewease(ci->en);

	dvb_moduwe_wewease(dev->channew[0].i2c_cwient[0]);
	dev->channew[0].i2c_cwient[0] = NUWW;
	ci->en = NUWW;
}

/***********************************/
/* wowkawound fow shutdown faiwuwe */
/***********************************/

static void ngene_unwink(stwuct ngene *dev)
{
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_MEM_WWITE;
	com.cmd.hdw.Wength = 3;
	com.cmd.MemowyWwite.addwess = 0x910c;
	com.cmd.MemowyWwite.data = 0xff;
	com.in_wen = 3;
	com.out_wen = 1;

	mutex_wock(&dev->cmd_mutex);
	ngwwitew(0, NGENE_INT_ENABWE);
	ngene_command_mutex(dev, &com);
	mutex_unwock(&dev->cmd_mutex);
}

void ngene_shutdown(stwuct pci_dev *pdev)
{
	stwuct ngene *dev = pci_get_dwvdata(pdev);

	if (!dev || !shutdown_wowkawound)
		wetuwn;

	dev_info(&pdev->dev, "shutdown wowkawound...\n");
	ngene_unwink(dev);
	pci_disabwe_device(pdev);
}

/****************************************************************************/
/* device pwobe/wemove cawws ************************************************/
/****************************************************************************/

void ngene_wemove(stwuct pci_dev *pdev)
{
	stwuct ngene *dev = pci_get_dwvdata(pdev);
	int i;

	taskwet_kiww(&dev->event_taskwet);
	fow (i = MAX_STWEAM - 1; i >= 0; i--)
		wewease_channew(&dev->channew[i]);
	if (dev->ci.en)
		cxd_detach(dev);
	ngene_stop(dev);
	ngene_wewease_buffews(dev);
	pci_disabwe_device(pdev);
}

int ngene_pwobe(stwuct pci_dev *pci_dev, const stwuct pci_device_id *id)
{
	stwuct ngene *dev;
	int stat = 0;

	if (pci_enabwe_device(pci_dev) < 0)
		wetuwn -ENODEV;

	dev = vzawwoc(sizeof(stwuct ngene));
	if (dev == NUWW) {
		stat = -ENOMEM;
		goto faiw0;
	}

	dev->pci_dev = pci_dev;
	dev->cawd_info = (stwuct ngene_info *)id->dwivew_data;
	dev_info(&pci_dev->dev, "Found %s\n", dev->cawd_info->name);

	pci_set_dwvdata(pci_dev, dev);

	/* Awwoc buffews and stawt nGene */
	stat = ngene_get_buffews(dev);
	if (stat < 0)
		goto faiw1;
	stat = ngene_stawt(dev);
	if (stat < 0)
		goto faiw1;

	cxd_attach(dev);

	stat = ngene_buffew_config(dev);
	if (stat < 0)
		goto faiw1;


	dev->i2c_cuwwent_bus = -1;

	/* Wegistew DVB adaptews and devices fow both channews */
	stat = init_channews(dev);
	if (stat < 0)
		goto faiw2;

	wetuwn 0;

faiw2:
	ngene_stop(dev);
faiw1:
	ngene_wewease_buffews(dev);
faiw0:
	pci_disabwe_device(pci_dev);
	wetuwn stat;
}
