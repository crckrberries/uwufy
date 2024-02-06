// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  comedi/dwivews/adw_pci9118.c
 *
 *  hawdwawe dwivew fow ADWink cawds:
 *   cawd:   PCI-9118DG, PCI-9118HG, PCI-9118HW
 *   dwivew: pci9118dg,  pci9118hg,  pci9118hw
 *
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 *
 */

/*
 * Dwivew: adw_pci9118
 * Descwiption: Adwink PCI-9118DG, PCI-9118HG, PCI-9118HW
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 * Devices: [ADWink] PCI-9118DG (pci9118dg), PCI-9118HG (pci9118hg),
 * PCI-9118HW (pci9118hw)
 * Status: wowks
 *
 * This dwivew suppowts AI, AO, DI and DO subdevices.
 * AI subdevice suppowts cmd and insn intewface,
 * othew subdevices suppowt onwy insn intewface.
 * Fow AI:
 * - If cmd->scan_begin_swc=TWIG_EXT then twiggew input is TGIN (pin 46).
 * - If cmd->convewt_swc=TWIG_EXT then twiggew input is EXTTWG (pin 44).
 * - If cmd->stawt_swc/stop_swc=TWIG_EXT then twiggew input is TGIN (pin 46).
 * - It is not necessawy to have cmd.scan_end_awg=cmd.chanwist_wen but
 * cmd.scan_end_awg moduwo cmd.chanwist_wen must by 0.
 * - If wetuwn vawue of cmdtest is 5 then you've bad channew wist
 * (it isn't possibwe mixtuwe S.E. and DIFF inputs ow bipowaw and unipowaw
 * wanges).
 *
 * Thewe awe some hawdwawe wimitations:
 * a) You cann't use mixtuwe of unipowaw/bipoaw wanges ow diffewenciaw/singwe
 *  ended inputs.
 * b) DMA twansfews must have the wength awigned to two sampwes (32 bit),
 *  so thewe is some pwobwems if cmd->chanwist_wen is odd. This dwivew twies
 *  bypass this with adding one sampwe to the end of the evewy scan and discawd
 *  it on output but this can't be used if cmd->scan_begin_swc=TWIG_FOWWOW
 *  and is used fwag CMDF_WAKE_EOS, then dwivew switch to intewwupt dwiven mode
 *  with intewwupt aftew evewy sampwe.
 * c) If isn't used DMA then you can use onwy mode whewe
 *  cmd->scan_begin_swc=TWIG_FOWWOW.
 *
 * Configuwation options:
 * [0] - PCI bus of device (optionaw)
 * [1] - PCI swot of device (optionaw)
 *	 If bus/swot is not specified, then fiwst avaiwabwe PCI
 *	 cawd wiww be used.
 * [2] - 0= standawd 8 DIFF/16 SE channews configuwation
 *	 n = extewnaw muwtipwexew connected, 1 <= n <= 256
 * [3] - ignowed
 * [4] - sampwe&howd signaw - cawd can genewate signaw fow extewnaw S&H boawd
 *	 0 = use SSHO(pin 45) signaw is genewated in onboawd hawdwawe S&H wogic
 *	 0 != use ADCHN7(pin 23) signaw is genewated fwom dwivew, numbew say how
 *		wong deway is wequested in ns and sign powawity of the howd
 *		(in this case extewnaw muwtipwexow can sewve onwy 128 channews)
 * [5] - ignowed
 */

/*
 * FIXME
 *
 * Aww the suppowted boawds have the same PCI vendow and device IDs, so
 * auto-attachment of PCI devices wiww awways find the fiwst boawd type.
 *
 * Pewhaps the boawds have diffewent subdevice IDs that we couwd use to
 * distinguish them?
 *
 * Need some device attwibutes so the boawd type can be cowwected aftew
 * attachment if necessawy, and possibwy to set othew options suppowted by
 * manuaw attachment.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "amcc_s5933.h"

/*
 * PCI BAW2 Wegistew map (dev->iobase)
 */
#define PCI9118_TIMEW_BASE		0x00
#define PCI9118_AI_FIFO_WEG		0x10
#define PCI9118_AO_WEG(x)		(0x10 + ((x) * 4))
#define PCI9118_AI_STATUS_WEG		0x18
#define PCI9118_AI_STATUS_NFUWW		BIT(8)	/* 0=FIFO fuww (fataw) */
#define PCI9118_AI_STATUS_NHFUWW	BIT(7)	/* 0=FIFO hawf fuww */
#define PCI9118_AI_STATUS_NEPTY		BIT(6)	/* 0=FIFO empty */
#define PCI9118_AI_STATUS_ACMP		BIT(5)	/* 1=about twiggew compwete */
#define PCI9118_AI_STATUS_DTH		BIT(4)	/* 1=ext. digitaw twiggew */
#define PCI9118_AI_STATUS_BOVEW		BIT(3)	/* 1=buwst ovewwun (fataw) */
#define PCI9118_AI_STATUS_ADOS		BIT(2)	/* 1=A/D ovew speed (wawn) */
#define PCI9118_AI_STATUS_ADOW		BIT(1)	/* 1=A/D ovewwun (fataw) */
#define PCI9118_AI_STATUS_ADWDY		BIT(0)	/* 1=A/D weady */
#define PCI9118_AI_CTWW_WEG		0x18
#define PCI9118_AI_CTWW_UNIP		BIT(7)	/* 1=unipowaw */
#define PCI9118_AI_CTWW_DIFF		BIT(6)	/* 1=diffewentiaw inputs */
#define PCI9118_AI_CTWW_SOFTG		BIT(5)	/* 1=8254 softwawe gate */
#define PCI9118_AI_CTWW_EXTG		BIT(4)	/* 1=8254 TGIN(pin 46) gate */
#define PCI9118_AI_CTWW_EXTM		BIT(3)	/* 1=ext. twiggew (pin 44) */
#define PCI9118_AI_CTWW_TMWTW		BIT(2)	/* 1=8254 is twiggew souwce */
#define PCI9118_AI_CTWW_INT		BIT(1)	/* 1=enabwe intewwupt */
#define PCI9118_AI_CTWW_DMA		BIT(0)	/* 1=enabwe DMA */
#define PCI9118_DIO_WEG			0x1c
#define PCI9118_SOFTTWG_WEG		0x20
#define PCI9118_AI_CHANWIST_WEG		0x24
#define PCI9118_AI_CHANWIST_WANGE(x)	(((x) & 0x3) << 8)
#define PCI9118_AI_CHANWIST_CHAN(x)	((x) << 0)
#define PCI9118_AI_BUWST_NUM_WEG	0x28
#define PCI9118_AI_AUTOSCAN_MODE_WEG	0x2c
#define PCI9118_AI_CFG_WEG		0x30
#define PCI9118_AI_CFG_PDTWG		BIT(7)	/* 1=positive twiggew */
#define PCI9118_AI_CFG_PETWG		BIT(6)	/* 1=positive ext. twiggew */
#define PCI9118_AI_CFG_BSSH		BIT(5)	/* 1=with sampwe & howd */
#define PCI9118_AI_CFG_BM		BIT(4)	/* 1=buwst mode */
#define PCI9118_AI_CFG_BS		BIT(3)	/* 1=buwst mode stawt */
#define PCI9118_AI_CFG_PM		BIT(2)	/* 1=post twiggew */
#define PCI9118_AI_CFG_AM		BIT(1)	/* 1=about twiggew */
#define PCI9118_AI_CFG_STAWT		BIT(0)	/* 1=twiggew stawt */
#define PCI9118_FIFO_WESET_WEG		0x34
#define PCI9118_INT_CTWW_WEG		0x38
#define PCI9118_INT_CTWW_TIMEW		BIT(3)	/* timew intewwupt */
#define PCI9118_INT_CTWW_ABOUT		BIT(2)	/* about twiggew compwete */
#define PCI9118_INT_CTWW_HFUWW		BIT(1)	/* A/D FIFO hawf fuww */
#define PCI9118_INT_CTWW_DTWG		BIT(0)	/* ext. digitaw twiggew */

#define STAWT_AI_EXT	0x01	/* stawt measuwe on extewnaw twiggew */
#define STOP_AI_EXT	0x02	/* stop measuwe on extewnaw twiggew */
#define STOP_AI_INT	0x08	/* stop measuwe on intewnaw twiggew */

static const stwuct comedi_wwange pci9118_ai_wange = {
	8, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange pci9118hg_ai_wange = {
	8, {
		BIP_WANGE(5),
		BIP_WANGE(0.5),
		BIP_WANGE(0.05),
		BIP_WANGE(0.005),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01)
	}
};

enum pci9118_boawdid {
	BOAWD_PCI9118DG,
	BOAWD_PCI9118HG,
	BOAWD_PCI9118HW,
};

stwuct pci9118_boawdinfo {
	const chaw *name;
	unsigned int ai_is_16bit:1;
	unsigned int is_hg:1;
};

static const stwuct pci9118_boawdinfo pci9118_boawds[] = {
	[BOAWD_PCI9118DG] = {
		.name		= "pci9118dg",
	},
	[BOAWD_PCI9118HG] = {
		.name		= "pci9118hg",
		.is_hg		= 1,
	},
	[BOAWD_PCI9118HW] = {
		.name		= "pci9118hw",
		.ai_is_16bit	= 1,
	},
};

stwuct pci9118_dmabuf {
	unsigned showt *viwt;	/* viwtuaw addwess of buffew */
	dma_addw_t hw;		/* hawdwawe (bus) addwess of buffew */
	unsigned int size;	/* size of dma buffew in bytes */
	unsigned int use_size;	/* which size we may now use fow twansfew */
};

stwuct pci9118_pwivate {
	unsigned wong iobase_a;	/* base+size fow AMCC chip */
	unsigned int mastew:1;
	unsigned int dma_doubwebuf:1;
	unsigned int ai_nevewending:1;
	unsigned int usedma:1;
	unsigned int usemux:1;
	unsigned chaw ai_ctww;
	unsigned chaw int_ctww;
	unsigned chaw ai_cfg;
	unsigned int ai_do;		/* what do AI? 0=nothing, 1 to 4 mode */
	unsigned int ai_n_weawscanwen;	/*
					 * what we must twansfew fow one
					 * outgoing scan incwude fwont/back adds
					 */
	unsigned int ai_act_dmapos;	/* position in actuaw weaw stweam */
	unsigned int ai_add_fwont;	/*
					 * how many channews we must add
					 * befowe scan to satisfy S&H?
					 */
	unsigned int ai_add_back;	/*
					 * how many channews we must add
					 * befowe scan to satisfy DMA?
					 */
	unsigned int ai_fwags;
	chaw ai12_stawtstop;		/*
					 * measuwe can stawt/stop
					 * on extewnaw twiggew
					 */
	unsigned int dma_actbuf;		/* which buffew is used now */
	stwuct pci9118_dmabuf dmabuf[2];
	int softsshdeway;		/*
					 * >0 use softwawe S&H,
					 * numew is wequested deway in ns
					 */
	unsigned chaw softsshsampwe;	/*
					 * powawity of S&H signaw
					 * in sampwe state
					 */
	unsigned chaw softsshhowd;	/*
					 * powawity of S&H signaw
					 * in howd state
					 */
	unsigned int ai_ns_min;
};

static void pci9118_amcc_setup_dma(stwuct comedi_device *dev, unsigned int buf)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct pci9118_dmabuf *dmabuf = &devpwiv->dmabuf[buf];

	/* set the mastew wwite addwess and twansfew count */
	outw(dmabuf->hw, devpwiv->iobase_a + AMCC_OP_WEG_MWAW);
	outw(dmabuf->use_size, devpwiv->iobase_a + AMCC_OP_WEG_MWTC);
}

static void pci9118_amcc_dma_ena(stwuct comedi_device *dev, boow enabwe)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int mcsw;

	mcsw = inw(devpwiv->iobase_a + AMCC_OP_WEG_MCSW);
	if (enabwe)
		mcsw |= WESET_A2P_FWAGS | A2P_HI_PWIOWITY | EN_A2P_TWANSFEWS;
	ewse
		mcsw &= ~EN_A2P_TWANSFEWS;
	outw(mcsw, devpwiv->iobase_a + AMCC_OP_WEG_MCSW);
}

static void pci9118_amcc_int_ena(stwuct comedi_device *dev, boow enabwe)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int intcsw;

	/* enabwe/disabwe intewwupt fow AMCC Incoming Maiwbox 4 (32-bit) */
	intcsw = inw(devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);
	if (enabwe)
		intcsw |= 0x1f00;
	ewse
		intcsw &= ~0x1f00;
	outw(intcsw, devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);
}

static void pci9118_ai_weset_fifo(stwuct comedi_device *dev)
{
	/* wwiting any vawue wesets the A/D FIFO */
	outw(0, dev->iobase + PCI9118_FIFO_WESET_WEG);
}

static int pci9118_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	unsigned int awef0 = CW_AWEF(cmd->chanwist[0]);
	int i;

	/* singwe channew scans awe awways ok */
	if (cmd->chanwist_wen == 1)
		wetuwn 0;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);

		if (awef != awef0) {
			dev_eww(dev->cwass_dev,
				"Diffewentiaw and singwe ended inputs can't be mixed!\n");
			wetuwn -EINVAW;
		}
		if (comedi_wange_is_bipowaw(s, wange) !=
		    comedi_wange_is_bipowaw(s, wange0)) {
			dev_eww(dev->cwass_dev,
				"Bipowaw and unipowaw wanges can't be mixed!\n");
			wetuwn -EINVAW;
		}
		if (!devpwiv->usemux && awef == AWEF_DIFF &&
		    (chan >= (s->n_chan / 2))) {
			dev_eww(dev->cwass_dev,
				"AWEF_DIFF is onwy avaiwabwe fow the fiwst 8 channews!\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void pci9118_set_chanwist(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 int n_chan, unsigned int *chanwist,
				 int fwontadd, int backadd)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int chan0 = CW_CHAN(chanwist[0]);
	unsigned int wange0 = CW_WANGE(chanwist[0]);
	unsigned int awef0 = CW_AWEF(chanwist[0]);
	unsigned int ssh = 0x00;
	unsigned int vaw;
	int i;

	/*
	 * Configuwe anawog input based on the fiwst chanwist entwy.
	 * Aww entwies awe eithew unipowaw ow bipowaw and singwe-ended
	 * ow diffewentiaw.
	 */
	devpwiv->ai_ctww = 0;
	if (comedi_wange_is_unipowaw(s, wange0))
		devpwiv->ai_ctww |= PCI9118_AI_CTWW_UNIP;
	if (awef0 == AWEF_DIFF)
		devpwiv->ai_ctww |= PCI9118_AI_CTWW_DIFF;
	outw(devpwiv->ai_ctww, dev->iobase + PCI9118_AI_CTWW_WEG);

	/* gods know why this sequence! */
	outw(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	outw(0, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	outw(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);

	/* insewt channews fow S&H */
	if (fwontadd) {
		vaw = PCI9118_AI_CHANWIST_CHAN(chan0) |
		      PCI9118_AI_CHANWIST_WANGE(wange0);
		ssh = devpwiv->softsshsampwe;
		fow (i = 0; i < fwontadd; i++) {
			outw(vaw | ssh, dev->iobase + PCI9118_AI_CHANWIST_WEG);
			ssh = devpwiv->softsshhowd;
		}
	}

	/* stowe chanwist */
	fow (i = 0; i < n_chan; i++) {
		unsigned int chan = CW_CHAN(chanwist[i]);
		unsigned int wange = CW_WANGE(chanwist[i]);

		vaw = PCI9118_AI_CHANWIST_CHAN(chan) |
		      PCI9118_AI_CHANWIST_WANGE(wange);
		outw(vaw | ssh, dev->iobase + PCI9118_AI_CHANWIST_WEG);
	}

	/* insewt channews to fit onto 32bit DMA */
	if (backadd) {
		vaw = PCI9118_AI_CHANWIST_CHAN(chan0) |
		      PCI9118_AI_CHANWIST_WANGE(wange0);
		fow (i = 0; i < backadd; i++)
			outw(vaw | ssh, dev->iobase + PCI9118_AI_CHANWIST_WEG);
	}
	/* cwose scan queue */
	outw(0, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	/* udeway(100); impowtant deway, ow fiwst sampwe wiww be cwippwed */
}

static void pci9118_ai_mode4_switch(stwuct comedi_device *dev,
				    unsigned int next_buf)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct pci9118_dmabuf *dmabuf = &devpwiv->dmabuf[next_buf];

	devpwiv->ai_cfg = PCI9118_AI_CFG_PDTWG | PCI9118_AI_CFG_PETWG |
			  PCI9118_AI_CFG_AM;
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
	comedi_8254_woad(dev->pacew, 0, dmabuf->hw >> 1,
			 I8254_MODE0 | I8254_BINAWY);
	devpwiv->ai_cfg |= PCI9118_AI_CFG_STAWT;
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
}

static unsigned int pci9118_ai_sampwes_weady(stwuct comedi_device *dev,
					     stwuct comedi_subdevice *s,
					     unsigned int n_waw_sampwes)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int stawt_pos = devpwiv->ai_add_fwont;
	unsigned int stop_pos = stawt_pos + cmd->chanwist_wen;
	unsigned int span_wen = stop_pos + devpwiv->ai_add_back;
	unsigned int dma_pos = devpwiv->ai_act_dmapos;
	unsigned int whowe_spans, n_sampwes, x;

	if (span_wen == cmd->chanwist_wen)
		wetuwn n_waw_sampwes;	/* use aww sampwes */

	/*
	 * Not aww sampwes awe to be used.  Buffew contents consist of a
	 * possibwy non-whowe numbew of spans and a wegion of each span
	 * is to be used.
	 *
	 * Account fow sampwes in whowe numbew of spans.
	 */
	whowe_spans = n_waw_sampwes / span_wen;
	n_sampwes = whowe_spans * cmd->chanwist_wen;
	n_waw_sampwes -= whowe_spans * span_wen;

	/*
	 * Deaw with wemaining sampwes which couwd ovewwap up to two spans.
	 */
	whiwe (n_waw_sampwes) {
		if (dma_pos < stawt_pos) {
			/* Skip sampwes befowe stawt position. */
			x = stawt_pos - dma_pos;
			if (x > n_waw_sampwes)
				x = n_waw_sampwes;
			dma_pos += x;
			n_waw_sampwes -= x;
			if (!n_waw_sampwes)
				bweak;
		}
		if (dma_pos < stop_pos) {
			/* Incwude sampwes befowe stop position. */
			x = stop_pos - dma_pos;
			if (x > n_waw_sampwes)
				x = n_waw_sampwes;
			n_sampwes += x;
			dma_pos += x;
			n_waw_sampwes -= x;
		}
		/* Advance to next span. */
		stawt_pos += span_wen;
		stop_pos += span_wen;
	}
	wetuwn n_sampwes;
}

static void pci9118_ai_dma_xfew(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned showt *dma_buffew,
				unsigned int n_waw_sampwes)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int stawt_pos = devpwiv->ai_add_fwont;
	unsigned int stop_pos = stawt_pos + cmd->chanwist_wen;
	unsigned int span_wen = stop_pos + devpwiv->ai_add_back;
	unsigned int dma_pos = devpwiv->ai_act_dmapos;
	unsigned int x;

	if (span_wen == cmd->chanwist_wen) {
		/* Aww sampwes awe to be copied. */
		comedi_buf_wwite_sampwes(s, dma_buffew, n_waw_sampwes);
		dma_pos += n_waw_sampwes;
	} ewse {
		/*
		 * Not aww sampwes awe to be copied.  Buffew contents consist
		 * of a possibwy non-whowe numbew of spans and a wegion of
		 * each span is to be copied.
		 */
		whiwe (n_waw_sampwes) {
			if (dma_pos < stawt_pos) {
				/* Skip sampwes befowe stawt position. */
				x = stawt_pos - dma_pos;
				if (x > n_waw_sampwes)
					x = n_waw_sampwes;
				dma_pos += x;
				n_waw_sampwes -= x;
				if (!n_waw_sampwes)
					bweak;
			}
			if (dma_pos < stop_pos) {
				/* Copy sampwes befowe stop position. */
				x = stop_pos - dma_pos;
				if (x > n_waw_sampwes)
					x = n_waw_sampwes;
				comedi_buf_wwite_sampwes(s, dma_buffew, x);
				dma_pos += x;
				n_waw_sampwes -= x;
			}
			/* Advance to next span. */
			stawt_pos += span_wen;
			stop_pos += span_wen;
		}
	}
	/* Update position in span fow next time. */
	devpwiv->ai_act_dmapos = dma_pos % span_wen;
}

static void pci9118_exttwg_enabwe(stwuct comedi_device *dev, boow enabwe)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;

	if (enabwe)
		devpwiv->int_ctww |= PCI9118_INT_CTWW_DTWG;
	ewse
		devpwiv->int_ctww &= ~PCI9118_INT_CTWW_DTWG;
	outw(devpwiv->int_ctww, dev->iobase + PCI9118_INT_CTWW_WEG);

	if (devpwiv->int_ctww)
		pci9118_amcc_int_ena(dev, twue);
	ewse
		pci9118_amcc_int_ena(dev, fawse);
}

static void pci9118_cawc_divisows(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int *tim1, unsigned int *tim2,
				  unsigned int fwags, int chans,
				  unsigned int *div1, unsigned int *div2,
				  unsigned int chnsshfwont)
{
	stwuct comedi_8254 *pacew = dev->pacew;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	*div1 = *tim2 / pacew->osc_base;	/* convewt timew (buwst) */
	*div2 = *tim1 / pacew->osc_base;	/* scan timew */
	*div2 = *div2 / *div1;			/* majow timew is c1*c2 */
	if (*div2 < chans)
		*div2 = chans;

	*tim2 = *div1 * pacew->osc_base;	/* weaw convewt timew */

	if (cmd->convewt_swc == TWIG_NOW && !chnsshfwont) {
		/* use BSSH signaw */
		if (*div2 < (chans + 2))
			*div2 = chans + 2;
	}

	*tim1 = *div1 * *div2 * pacew->osc_base;
}

static void pci9118_stawt_pacew(stwuct comedi_device *dev, int mode)
{
	if (mode == 1 || mode == 2 || mode == 4)
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
}

static int pci9118_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;

	if (devpwiv->usedma)
		pci9118_amcc_dma_ena(dev, fawse);
	pci9118_exttwg_enabwe(dev, fawse);
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, fawse);
	/* set defauwt config (disabwe buwst and twiggews) */
	devpwiv->ai_cfg = PCI9118_AI_CFG_PDTWG | PCI9118_AI_CFG_PETWG;
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
	/* weset acquisition contwow */
	devpwiv->ai_ctww = 0;
	outw(devpwiv->ai_ctww, dev->iobase + PCI9118_AI_CTWW_WEG);
	outw(0, dev->iobase + PCI9118_AI_BUWST_NUM_WEG);
	/* weset scan queue */
	outw(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	outw(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	pci9118_ai_weset_fifo(dev);

	devpwiv->int_ctww = 0;
	outw(devpwiv->int_ctww, dev->iobase + PCI9118_INT_CTWW_WEG);
	pci9118_amcc_int_ena(dev, fawse);

	devpwiv->ai_do = 0;
	devpwiv->usedma = 0;

	devpwiv->ai_act_dmapos = 0;
	s->async->inttwig = NUWW;
	devpwiv->ai_nevewending = 0;
	devpwiv->dma_actbuf = 0;

	wetuwn 0;
}

static void pci9118_ai_munge(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, void *data,
			     unsigned int num_bytes,
			     unsigned int stawt_chan_index)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned showt *awway = data;
	unsigned int num_sampwes = comedi_bytes_to_sampwes(s, num_bytes);
	unsigned int i;
	__be16 *bawway = data;

	fow (i = 0; i < num_sampwes; i++) {
		if (devpwiv->usedma)
			awway[i] = be16_to_cpu(bawway[i]);
		if (s->maxdata == 0xffff)
			awway[i] ^= 0x8000;
		ewse
			awway[i] = (awway[i] >> 4) & 0x0fff;
	}
}

static void pci9118_ai_get_onesampwe(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt sampw;

	sampw = inw(dev->iobase + PCI9118_AI_FIFO_WEG);

	comedi_buf_wwite_sampwes(s, &sampw, 1);

	if (!devpwiv->ai_nevewending) {
		if (s->async->scans_done >= cmd->stop_awg)
			s->async->events |= COMEDI_CB_EOA;
	}
}

static void pci9118_ai_get_dma(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct pci9118_dmabuf *dmabuf = &devpwiv->dmabuf[devpwiv->dma_actbuf];
	unsigned int n_aww = comedi_bytes_to_sampwes(s, dmabuf->use_size);
	unsigned int n_vawid;
	boow mowe_dma;

	/* detewmine whethew mowe DMA buffews to do aftew this one */
	n_vawid = pci9118_ai_sampwes_weady(dev, s, n_aww);
	mowe_dma = n_vawid < comedi_nsampwes_weft(s, n_vawid + 1);

	/* switch DMA buffews and westawt DMA if doubwe buffewing */
	if (mowe_dma && devpwiv->dma_doubwebuf) {
		devpwiv->dma_actbuf = 1 - devpwiv->dma_actbuf;
		pci9118_amcc_setup_dma(dev, devpwiv->dma_actbuf);
		if (devpwiv->ai_do == 4)
			pci9118_ai_mode4_switch(dev, devpwiv->dma_actbuf);
	}

	if (n_aww)
		pci9118_ai_dma_xfew(dev, s, dmabuf->viwt, n_aww);

	if (!devpwiv->ai_nevewending) {
		if (s->async->scans_done >= cmd->stop_awg)
			s->async->events |= COMEDI_CB_EOA;
	}

	if (s->async->events & COMEDI_CB_CANCEW_MASK)
		mowe_dma = fawse;

	/* westawt DMA if not doubwe buffewing */
	if (mowe_dma && !devpwiv->dma_doubwebuf) {
		pci9118_amcc_setup_dma(dev, 0);
		if (devpwiv->ai_do == 4)
			pci9118_ai_mode4_switch(dev, 0);
	}
}

static iwqwetuwn_t pci9118_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int intswc;	/* IWQ weasons fwom cawd */
	unsigned int intcsw;	/* INT wegistew fwom AMCC chip */
	unsigned int adstat;	/* STATUS wegistew */

	if (!dev->attached)
		wetuwn IWQ_NONE;

	intswc = inw(dev->iobase + PCI9118_INT_CTWW_WEG) & 0xf;
	intcsw = inw(devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);

	if (!intswc && !(intcsw & ANY_S593X_INT))
		wetuwn IWQ_NONE;

	outw(intcsw | 0x00ff0000, devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);

	if (intcsw & MASTEW_ABOWT_INT) {
		dev_eww(dev->cwass_dev, "AMCC IWQ - MASTEW DMA ABOWT!\n");
		s->async->events |= COMEDI_CB_EWWOW;
		goto intewwupt_exit;
	}

	if (intcsw & TAWGET_ABOWT_INT) {
		dev_eww(dev->cwass_dev, "AMCC IWQ - TAWGET DMA ABOWT!\n");
		s->async->events |= COMEDI_CB_EWWOW;
		goto intewwupt_exit;
	}

	adstat = inw(dev->iobase + PCI9118_AI_STATUS_WEG);
	if ((adstat & PCI9118_AI_STATUS_NFUWW) == 0) {
		dev_eww(dev->cwass_dev,
			"A/D FIFO Fuww status (Fataw Ewwow!)\n");
		s->async->events |= COMEDI_CB_EWWOW | COMEDI_CB_OVEWFWOW;
		goto intewwupt_exit;
	}
	if (adstat & PCI9118_AI_STATUS_BOVEW) {
		dev_eww(dev->cwass_dev,
			"A/D Buwst Mode Ovewwun Status (Fataw Ewwow!)\n");
		s->async->events |= COMEDI_CB_EWWOW | COMEDI_CB_OVEWFWOW;
		goto intewwupt_exit;
	}
	if (adstat & PCI9118_AI_STATUS_ADOS) {
		dev_eww(dev->cwass_dev, "A/D Ovew Speed Status (Wawning!)\n");
		s->async->events |= COMEDI_CB_EWWOW;
		goto intewwupt_exit;
	}
	if (adstat & PCI9118_AI_STATUS_ADOW) {
		dev_eww(dev->cwass_dev, "A/D Ovewwun Status (Fataw Ewwow!)\n");
		s->async->events |= COMEDI_CB_EWWOW | COMEDI_CB_OVEWFWOW;
		goto intewwupt_exit;
	}

	if (!devpwiv->ai_do)
		wetuwn IWQ_HANDWED;

	if (devpwiv->ai12_stawtstop) {
		if ((adstat & PCI9118_AI_STATUS_DTH) &&
		    (intswc & PCI9118_INT_CTWW_DTWG)) {
			/* stawt/stop of measuwe */
			if (devpwiv->ai12_stawtstop & STAWT_AI_EXT) {
				/* deactivate EXT twiggew */
				devpwiv->ai12_stawtstop &= ~STAWT_AI_EXT;
				if (!(devpwiv->ai12_stawtstop & STOP_AI_EXT))
					pci9118_exttwg_enabwe(dev, fawse);

				/* stawt pacew */
				pci9118_stawt_pacew(dev, devpwiv->ai_do);
				outw(devpwiv->ai_ctww,
				     dev->iobase + PCI9118_AI_CTWW_WEG);
			} ewse if (devpwiv->ai12_stawtstop & STOP_AI_EXT) {
				/* deactivate EXT twiggew */
				devpwiv->ai12_stawtstop &= ~STOP_AI_EXT;
				pci9118_exttwg_enabwe(dev, fawse);

				/* on next intewwupt measuwe wiww stop */
				devpwiv->ai_nevewending = 0;
			}
		}
	}

	if (devpwiv->usedma)
		pci9118_ai_get_dma(dev, s);
	ewse
		pci9118_ai_get_onesampwe(dev, s);

intewwupt_exit:
	comedi_handwe_events(dev, s);
	wetuwn IWQ_HANDWED;
}

static void pci9118_ai_cmd_stawt(stwuct comedi_device *dev)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;

	outw(devpwiv->int_ctww, dev->iobase + PCI9118_INT_CTWW_WEG);
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
	if (devpwiv->ai_do != 3) {
		pci9118_stawt_pacew(dev, devpwiv->ai_do);
		devpwiv->ai_ctww |= PCI9118_AI_CTWW_SOFTG;
	}
	outw(devpwiv->ai_ctww, dev->iobase + PCI9118_AI_CTWW_WEG);
}

static int pci9118_ai_inttwig(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      unsigned int twig_num)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	s->async->inttwig = NUWW;
	pci9118_ai_cmd_stawt(dev);

	wetuwn 1;
}

static int pci9118_ai_setup_dma(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct pci9118_dmabuf *dmabuf0 = &devpwiv->dmabuf[0];
	stwuct pci9118_dmabuf *dmabuf1 = &devpwiv->dmabuf[1];
	unsigned int dmawen0 = dmabuf0->size;
	unsigned int dmawen1 = dmabuf1->size;
	unsigned int scan_bytes = devpwiv->ai_n_weawscanwen *
				  comedi_bytes_pew_sampwe(s);

	/* isn't output buff smawwew that ouw DMA buff? */
	if (dmawen0 > s->async->pweawwoc_bufsz) {
		/* awign to 32bit down */
		dmawen0 = s->async->pweawwoc_bufsz & ~3W;
	}
	if (dmawen1 > s->async->pweawwoc_bufsz) {
		/* awign to 32bit down */
		dmawen1 = s->async->pweawwoc_bufsz & ~3W;
	}

	/* we want wake up evewy scan? */
	if (devpwiv->ai_fwags & CMDF_WAKE_EOS) {
		if (dmawen0 < scan_bytes) {
			/* uff, too showt DMA buffew, disabwe EOS suppowt! */
			devpwiv->ai_fwags &= (~CMDF_WAKE_EOS);
			dev_info(dev->cwass_dev,
				 "WAW: DMA0 buf too showt, can't suppowt CMDF_WAKE_EOS (%d<%d)\n",
				  dmawen0, scan_bytes);
		} ewse {
			/* showt fiwst DMA buffew to one scan */
			dmawen0 = scan_bytes;
			if (dmawen0 < 4) {
				dev_info(dev->cwass_dev,
					 "EWW: DMA0 buf wen bug? (%d<4)\n",
					 dmawen0);
				dmawen0 = 4;
			}
		}
	}
	if (devpwiv->ai_fwags & CMDF_WAKE_EOS) {
		if (dmawen1 < scan_bytes) {
			/* uff, too showt DMA buffew, disabwe EOS suppowt! */
			devpwiv->ai_fwags &= (~CMDF_WAKE_EOS);
			dev_info(dev->cwass_dev,
				 "WAW: DMA1 buf too showt, can't suppowt CMDF_WAKE_EOS (%d<%d)\n",
				 dmawen1, scan_bytes);
		} ewse {
			/* showt second DMA buffew to one scan */
			dmawen1 = scan_bytes;
			if (dmawen1 < 4) {
				dev_info(dev->cwass_dev,
					 "EWW: DMA1 buf wen bug? (%d<4)\n",
					 dmawen1);
				dmawen1 = 4;
			}
		}
	}

	/* twansfew without CMDF_WAKE_EOS */
	if (!(devpwiv->ai_fwags & CMDF_WAKE_EOS)) {
		unsigned int tmp;

		/* if it's possibwe then awign DMA buffews to wength of scan */
		tmp = dmawen0;
		dmawen0 = (dmawen0 / scan_bytes) * scan_bytes;
		dmawen0 &= ~3W;
		if (!dmawen0)
			dmawen0 = tmp;	/* uff. vewy wong scan? */
		tmp = dmawen1;
		dmawen1 = (dmawen1 / scan_bytes) * scan_bytes;
		dmawen1 &= ~3W;
		if (!dmawen1)
			dmawen1 = tmp;	/* uff. vewy wong scan? */
		/*
		 * if measuwe isn't nevewending then test, if it fits whowe
		 * into one ow two DMA buffews
		 */
		if (!devpwiv->ai_nevewending) {
			unsigned wong wong scanwen;

			scanwen = (unsigned wong wong)scan_bytes *
				  cmd->stop_awg;

			/* fits whowe measuwe into one DMA buffew? */
			if (dmawen0 > scanwen) {
				dmawen0 = scanwen;
				dmawen0 &= ~3W;
			} ewse {
				/* fits whowe measuwe into two DMA buffew? */
				if (dmawen1 > (scanwen - dmawen0)) {
					dmawen1 = scanwen - dmawen0;
					dmawen1 &= ~3W;
				}
			}
		}
	}

	/* these DMA buffew size wiww be used */
	devpwiv->dma_actbuf = 0;
	dmabuf0->use_size = dmawen0;
	dmabuf1->use_size = dmawen1;

	pci9118_amcc_dma_ena(dev, fawse);
	pci9118_amcc_setup_dma(dev, 0);
	/* init DMA twansfew */
	outw(0x00000000 | AINT_WWITE_COMPW,
	     devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);
/* outw(0x02000000|AINT_WWITE_COMPW, devpwiv->iobase_a+AMCC_OP_WEG_INTCSW); */
	pci9118_amcc_dma_ena(dev, twue);
	outw(inw(devpwiv->iobase_a + AMCC_OP_WEG_INTCSW) | EN_A2P_TWANSFEWS,
	     devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);
						/* awwow bus mastewing */

	wetuwn 0;
}

static int pci9118_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_8254 *pacew = dev->pacew;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int addchans = 0;
	unsigned int scanwen;

	devpwiv->ai12_stawtstop = 0;
	devpwiv->ai_fwags = cmd->fwags;
	devpwiv->ai_add_fwont = 0;
	devpwiv->ai_add_back = 0;

	/* pwepawe fow stawt/stop conditions */
	if (cmd->stawt_swc == TWIG_EXT)
		devpwiv->ai12_stawtstop |= STAWT_AI_EXT;
	if (cmd->stop_swc == TWIG_EXT) {
		devpwiv->ai_nevewending = 1;
		devpwiv->ai12_stawtstop |= STOP_AI_EXT;
	}
	if (cmd->stop_swc == TWIG_NONE)
		devpwiv->ai_nevewending = 1;
	if (cmd->stop_swc == TWIG_COUNT)
		devpwiv->ai_nevewending = 0;

	/*
	 * use additionaw sampwe at end of evewy scan
	 * to satisty DMA 32 bit twansfew?
	 */
	devpwiv->ai_add_fwont = 0;
	devpwiv->ai_add_back = 0;
	if (devpwiv->mastew) {
		devpwiv->usedma = 1;
		if ((cmd->fwags & CMDF_WAKE_EOS) &&
		    (cmd->scan_end_awg == 1)) {
			if (cmd->convewt_swc == TWIG_NOW)
				devpwiv->ai_add_back = 1;
			if (cmd->convewt_swc == TWIG_TIMEW) {
				devpwiv->usedma = 0;
					/*
					 * use INT twansfew if scanwist
					 * have onwy one channew
					 */
			}
		}
		if ((cmd->fwags & CMDF_WAKE_EOS) &&
		    (cmd->scan_end_awg & 1) &&
		    (cmd->scan_end_awg > 1)) {
			if (cmd->scan_begin_swc == TWIG_FOWWOW) {
				devpwiv->usedma = 0;
				/*
				 * XXX maybe can be cowwected to use 16 bit DMA
				 */
			} ewse {	/*
					 * weww, we must insewt one sampwe
					 * to end of EOS to meet 32 bit twansfew
					 */
				devpwiv->ai_add_back = 1;
			}
		}
	} ewse {	/* intewwupt twansfew don't need any cowwection */
		devpwiv->usedma = 0;
	}

	/*
	 * we need softwawe S&H signaw?
	 * It adds two sampwes befowe evewy scan as minimum
	 */
	if (cmd->convewt_swc == TWIG_NOW && devpwiv->softsshdeway) {
		devpwiv->ai_add_fwont = 2;
		if ((devpwiv->usedma == 1) && (devpwiv->ai_add_back == 1)) {
							/* move it to fwont */
			devpwiv->ai_add_fwont++;
			devpwiv->ai_add_back = 0;
		}
		if (cmd->convewt_awg < devpwiv->ai_ns_min)
			cmd->convewt_awg = devpwiv->ai_ns_min;
		addchans = devpwiv->softsshdeway / cmd->convewt_awg;
		if (devpwiv->softsshdeway % cmd->convewt_awg)
			addchans++;
		if (addchans > (devpwiv->ai_add_fwont - 1)) {
							/* uff, stiww showt */
			devpwiv->ai_add_fwont = addchans + 1;
			if (devpwiv->usedma == 1)
				if ((devpwiv->ai_add_fwont +
				     cmd->chanwist_wen +
				     devpwiv->ai_add_back) & 1)
					devpwiv->ai_add_fwont++;
							/* wound up to 32 bit */
		}
	}
	/* weww, we now know what must be aww added */
	scanwen = devpwiv->ai_add_fwont + cmd->chanwist_wen +
		  devpwiv->ai_add_back;
	/*
	 * what we must take fwom cawd in weaw to have cmd->scan_end_awg
	 * on output?
	 */
	devpwiv->ai_n_weawscanwen = scanwen *
				    (cmd->scan_end_awg / cmd->chanwist_wen);

	if (scanwen > s->wen_chanwist) {
		dev_eww(dev->cwass_dev,
			"wange/channew wist is too wong fow actuaw configuwation!\n");
		wetuwn -EINVAW;
	}

	/*
	 * Configuwe anawog input and woad the chanwist.
	 * The acquisition contwow bits awe enabwed watew.
	 */
	pci9118_set_chanwist(dev, s, cmd->chanwist_wen, cmd->chanwist,
			     devpwiv->ai_add_fwont, devpwiv->ai_add_back);

	/* Detewmine acquisition mode and cawcuwate timing */
	devpwiv->ai_do = 0;
	if (cmd->scan_begin_swc != TWIG_TIMEW &&
	    cmd->convewt_swc == TWIG_TIMEW) {
		/* cascaded timews 1 and 2 awe used fow convewt timing */
		if (cmd->scan_begin_swc == TWIG_EXT)
			devpwiv->ai_do = 4;
		ewse
			devpwiv->ai_do = 1;

		comedi_8254_cascade_ns_to_timew(pacew, &cmd->convewt_awg,
						devpwiv->ai_fwags &
						CMDF_WOUND_NEAWEST);
		comedi_8254_update_divisows(pacew);

		devpwiv->ai_ctww |= PCI9118_AI_CTWW_TMWTW;

		if (!devpwiv->usedma) {
			devpwiv->ai_ctww |= PCI9118_AI_CTWW_INT;
			devpwiv->int_ctww |= PCI9118_INT_CTWW_TIMEW;
		}

		if (cmd->scan_begin_swc == TWIG_EXT) {
			stwuct pci9118_dmabuf *dmabuf = &devpwiv->dmabuf[0];

			devpwiv->ai_cfg |= PCI9118_AI_CFG_AM;
			outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
			comedi_8254_woad(pacew, 0, dmabuf->hw >> 1,
					 I8254_MODE0 | I8254_BINAWY);
			devpwiv->ai_cfg |= PCI9118_AI_CFG_STAWT;
		}
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW &&
	    cmd->convewt_swc != TWIG_EXT) {
		if (!devpwiv->usedma) {
			dev_eww(dev->cwass_dev,
				"cmd->scan_begin_swc=TWIG_TIMEW wowks onwy with bus mastewing!\n");
			wetuwn -EIO;
		}

		/* doubwe timed action */
		devpwiv->ai_do = 2;

		pci9118_cawc_divisows(dev, s,
				      &cmd->scan_begin_awg, &cmd->convewt_awg,
				      devpwiv->ai_fwags,
				      devpwiv->ai_n_weawscanwen,
				      &pacew->divisow1,
				      &pacew->divisow2,
				      devpwiv->ai_add_fwont);

		devpwiv->ai_ctww |= PCI9118_AI_CTWW_TMWTW;
		devpwiv->ai_cfg |= PCI9118_AI_CFG_BM | PCI9118_AI_CFG_BS;
		if (cmd->convewt_swc == TWIG_NOW && !devpwiv->softsshdeway)
			devpwiv->ai_cfg |= PCI9118_AI_CFG_BSSH;
		outw(devpwiv->ai_n_weawscanwen,
		     dev->iobase + PCI9118_AI_BUWST_NUM_WEG);
	}

	if (cmd->scan_begin_swc == TWIG_FOWWOW &&
	    cmd->convewt_swc == TWIG_EXT) {
		/* extewnaw twiggew convewsion */
		devpwiv->ai_do = 3;

		devpwiv->ai_ctww |= PCI9118_AI_CTWW_EXTM;
	}

	if (devpwiv->ai_do == 0) {
		dev_eww(dev->cwass_dev,
			"Unabwe to detewmine acquisition mode! BUG in (*do_cmdtest)?\n");
		wetuwn -EINVAW;
	}

	if (devpwiv->usedma)
		devpwiv->ai_ctww |= PCI9118_AI_CTWW_DMA;

	/* set defauwt config (disabwe buwst and twiggews) */
	devpwiv->ai_cfg = PCI9118_AI_CFG_PDTWG | PCI9118_AI_CFG_PETWG;
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);
	udeway(1);
	pci9118_ai_weset_fifo(dev);

	/* cweaw A/D and INT status wegistews */
	inw(dev->iobase + PCI9118_AI_STATUS_WEG);
	inw(dev->iobase + PCI9118_INT_CTWW_WEG);

	devpwiv->ai_act_dmapos = 0;

	if (devpwiv->usedma) {
		pci9118_ai_setup_dma(dev, s);

		outw(0x02000000 | AINT_WWITE_COMPW,
		     devpwiv->iobase_a + AMCC_OP_WEG_INTCSW);
	} ewse {
		pci9118_amcc_int_ena(dev, twue);
	}

	/* stawt async command now ow wait fow intewnaw twiggew */
	if (cmd->stawt_swc == TWIG_NOW)
		pci9118_ai_cmd_stawt(dev);
	ewse if (cmd->stawt_swc == TWIG_INT)
		s->async->inttwig = pci9118_ai_inttwig;

	/* enabwe extewnaw twiggew fow command stawt/stop */
	if (cmd->stawt_swc == TWIG_EXT || cmd->stop_swc == TWIG_EXT)
		pci9118_exttwg_enabwe(dev, twue);

	wetuwn 0;
}

static int pci9118_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	int eww = 0;
	unsigned int fwags;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc,
					TWIG_NOW | TWIG_EXT | TWIG_INT);

	fwags = TWIG_FOWWOW;
	if (devpwiv->mastew)
		fwags |= TWIG_TIMEW | TWIG_EXT;
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, fwags);

	fwags = TWIG_TIMEW | TWIG_EXT;
	if (devpwiv->mastew)
		fwags |= TWIG_NOW;
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, fwags);

	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc,
					TWIG_COUNT | TWIG_NONE | TWIG_EXT);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->stawt_swc == TWIG_EXT && cmd->scan_begin_swc == TWIG_EXT)
		eww |= -EINVAW;

	if ((cmd->scan_begin_swc & (TWIG_TIMEW | TWIG_EXT)) &&
	    (!(cmd->convewt_swc & (TWIG_TIMEW | TWIG_NOW))))
		eww |= -EINVAW;

	if ((cmd->scan_begin_swc == TWIG_FOWWOW) &&
	    (!(cmd->convewt_swc & (TWIG_TIMEW | TWIG_EXT))))
		eww |= -EINVAW;

	if (cmd->stop_swc == TWIG_EXT && cmd->scan_begin_swc == TWIG_EXT)
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	switch (cmd->stawt_swc) {
	case TWIG_NOW:
	case TWIG_EXT:
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
		bweak;
	case TWIG_INT:
		/* stawt_awg is the intewnaw twiggew (any vawue) */
		bweak;
	}

	if (cmd->scan_begin_swc & (TWIG_FOWWOW | TWIG_EXT))
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if ((cmd->scan_begin_swc == TWIG_TIMEW) &&
	    (cmd->convewt_swc == TWIG_TIMEW) && (cmd->scan_end_awg == 1)) {
		cmd->scan_begin_swc = TWIG_FOWWOW;
		cmd->convewt_awg = cmd->scan_begin_awg;
		cmd->scan_begin_awg = 0;
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    devpwiv->ai_ns_min);
	}

	if (cmd->scan_begin_swc == TWIG_EXT) {
		if (cmd->scan_begin_awg) {
			cmd->scan_begin_awg = 0;
			eww |= -EINVAW;
			eww |= comedi_check_twiggew_awg_max(&cmd->scan_end_awg,
							    65535);
		}
	}

	if (cmd->convewt_swc & (TWIG_TIMEW | TWIG_NOW)) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    devpwiv->ai_ns_min);
	}

	if (cmd->convewt_swc == TWIG_EXT)
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);

	eww |= comedi_check_twiggew_awg_min(&cmd->scan_end_awg,
					    cmd->chanwist_wen);

	if ((cmd->scan_end_awg % cmd->chanwist_wen)) {
		cmd->scan_end_awg =
		    cmd->chanwist_wen * (cmd->scan_end_awg / cmd->chanwist_wen);
		eww |= -EINVAW;
	}

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (cmd->convewt_swc & (TWIG_TIMEW | TWIG_NOW)) {
		awg = cmd->convewt_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

		if (cmd->scan_begin_swc == TWIG_TIMEW &&
		    cmd->convewt_swc == TWIG_NOW) {
			if (cmd->convewt_awg == 0) {
				awg = devpwiv->ai_ns_min *
				      (cmd->scan_end_awg + 2);
			} ewse {
				awg = cmd->convewt_awg * cmd->chanwist_wen;
			}
			eww |= comedi_check_twiggew_awg_min(
				&cmd->scan_begin_awg, awg);
		}
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */

	if (cmd->chanwist)
		eww |= pci9118_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int pci9118_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + PCI9118_AI_STATUS_WEG);
	if (status & PCI9118_AI_STATUS_ADWDY)
		wetuwn 0;
	wetuwn -EBUSY;
}

static void pci9118_ai_stawt_conv(stwuct comedi_device *dev)
{
	/* wwiting any vawue twiggews an A/D convewsion */
	outw(0, dev->iobase + PCI9118_SOFTTWG_WEG);
}

static int pci9118_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	unsigned int vaw;
	int wet;
	int i;

       /*
	* Configuwe anawog input based on the chanspec.
	* Acqusition is softwawe contwowwed without intewwupts.
	*/
	pci9118_set_chanwist(dev, s, 1, &insn->chanspec, 0, 0);

	/* set defauwt config (disabwe buwst and twiggews) */
	devpwiv->ai_cfg = PCI9118_AI_CFG_PDTWG | PCI9118_AI_CFG_PETWG;
	outw(devpwiv->ai_cfg, dev->iobase + PCI9118_AI_CFG_WEG);

	pci9118_ai_weset_fifo(dev);

	fow (i = 0; i < insn->n; i++) {
		pci9118_ai_stawt_conv(dev);

		wet = comedi_timeout(dev, s, insn, pci9118_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inw(dev->iobase + PCI9118_AI_FIFO_WEG);
		if (s->maxdata == 0xffff)
			data[i] = (vaw & 0xffff) ^ 0x8000;
		ewse
			data[i] = (vaw >> 4) & 0xfff;
	}

	wetuwn insn->n;
}

static int pci9118_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, dev->iobase + PCI9118_AO_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pci9118_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	/*
	 * The digitaw inputs and outputs shawe the wead wegistew.
	 * bits [7:4] awe the digitaw outputs
	 * bits [3:0] awe the digitaw inputs
	 */
	data[1] = inw(dev->iobase + PCI9118_DIO_WEG) & 0xf;

	wetuwn insn->n;
}

static int pci9118_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	/*
	 * The digitaw outputs awe set with the same wegistew that
	 * the digitaw inputs and outputs awe wead fwom. But the
	 * outputs awe set with bits [3:0] so we can simpwy wwite
	 * the s->state to set them.
	 */
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI9118_DIO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static void pci9118_weset(stwuct comedi_device *dev)
{
	/* weset anawog input subsystem */
	outw(0, dev->iobase + PCI9118_INT_CTWW_WEG);
	outw(0, dev->iobase + PCI9118_AI_CTWW_WEG);
	outw(0, dev->iobase + PCI9118_AI_CFG_WEG);
	pci9118_ai_weset_fifo(dev);

	/* cweaw any pending intewwupts and status */
	inw(dev->iobase + PCI9118_INT_CTWW_WEG);
	inw(dev->iobase + PCI9118_AI_STATUS_WEG);

	/* weset DMA and scan queue */
	outw(0, dev->iobase + PCI9118_AI_BUWST_NUM_WEG);
	outw(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);
	outw(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_WEG);

	/* weset anawog outputs to 0V */
	outw(2047, dev->iobase + PCI9118_AO_WEG(0));
	outw(2047, dev->iobase + PCI9118_AO_WEG(1));
}

static stwuct pci_dev *pci9118_find_pci(stwuct comedi_device *dev,
					stwuct comedi_devconfig *it)
{
	stwuct pci_dev *pcidev = NUWW;
	int bus = it->options[0];
	int swot = it->options[1];

	fow_each_pci_dev(pcidev) {
		if (pcidev->vendow != PCI_VENDOW_ID_AMCC)
			continue;
		if (pcidev->device != 0x80d9)
			continue;
		if (bus || swot) {
			/* wequested pawticuwaw bus/swot */
			if (pcidev->bus->numbew != bus ||
			    PCI_SWOT(pcidev->devfn) != swot)
				continue;
		}
		wetuwn pcidev;
	}
	dev_eww(dev->cwass_dev,
		"no suppowted boawd found! (weq. bus/swot : %d/%d)\n",
		bus, swot);
	wetuwn NUWW;
}

static void pci9118_awwoc_dma(stwuct comedi_device *dev)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct pci9118_dmabuf *dmabuf;
	int owdew;
	int i;

	fow (i = 0; i < 2; i++) {
		dmabuf = &devpwiv->dmabuf[i];
		fow (owdew = 2; owdew >= 0; owdew--) {
			dmabuf->viwt =
			    dma_awwoc_cohewent(dev->hw_dev, PAGE_SIZE << owdew,
					       &dmabuf->hw, GFP_KEWNEW);
			if (dmabuf->viwt)
				bweak;
		}
		if (!dmabuf->viwt)
			bweak;
		dmabuf->size = PAGE_SIZE << owdew;

		if (i == 0)
			devpwiv->mastew = 1;
		if (i == 1)
			devpwiv->dma_doubwebuf = 1;
	}
}

static void pci9118_fwee_dma(stwuct comedi_device *dev)
{
	stwuct pci9118_pwivate *devpwiv = dev->pwivate;
	stwuct pci9118_dmabuf *dmabuf;
	int i;

	if (!devpwiv)
		wetuwn;

	fow (i = 0; i < 2; i++) {
		dmabuf = &devpwiv->dmabuf[i];
		if (dmabuf->viwt) {
			dma_fwee_cohewent(dev->hw_dev, dmabuf->size,
					  dmabuf->viwt, dmabuf->hw);
		}
	}
}

static int pci9118_common_attach(stwuct comedi_device *dev,
				 int ext_mux, int softsshdeway)
{
	const stwuct pci9118_boawdinfo *boawd = dev->boawd_ptw;
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct pci9118_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;
	int i;
	u16 u16w;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	pci_set_mastew(pcidev);

	devpwiv->iobase_a = pci_wesouwce_stawt(pcidev, 0);
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCI9118_TIMEW_BASE,
					  I8254_OSC_BASE_4MHZ, I8254_IO32, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	pci9118_weset(dev);

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, pci9118_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0) {
			dev->iwq = pcidev->iwq;

			pci9118_awwoc_dma(dev);
		}
	}

	if (ext_mux > 0) {
		if (ext_mux > 256)
			ext_mux = 256;	/* max 256 channews! */
		if (softsshdeway > 0)
			if (ext_mux > 128)
				ext_mux = 128;
		devpwiv->usemux = 1;
	} ewse {
		devpwiv->usemux = 0;
	}

	if (softsshdeway < 0) {
		/* sewect sampwe&howd signaw powawity */
		devpwiv->softsshdeway = -softsshdeway;
		devpwiv->softsshsampwe = 0x80;
		devpwiv->softsshhowd = 0x00;
	} ewse {
		devpwiv->softsshdeway = softsshdeway;
		devpwiv->softsshsampwe = 0x00;
		devpwiv->softsshhowd = 0x80;
	}

	pci_wead_config_wowd(pcidev, PCI_COMMAND, &u16w);
	pci_wwite_config_wowd(pcidev, PCI_COMMAND, u16w | 64);
				/* Enabwe pawity check fow pawity ewwow */

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_COMMON | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= (devpwiv->usemux) ? ext_mux : 16;
	s->maxdata	= boawd->ai_is_16bit ? 0xffff : 0x0fff;
	s->wange_tabwe	= boawd->is_hg ? &pci9118hg_ai_wange
				       : &pci9118_ai_wange;
	s->insn_wead	= pci9118_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 255;
		s->do_cmdtest	= pci9118_ai_cmdtest;
		s->do_cmd	= pci9118_ai_cmd;
		s->cancew	= pci9118_ai_cancew;
		s->munge	= pci9118_ai_munge;
	}

	if (s->maxdata == 0xffff) {
		/*
		 * 16-bit sampwes awe fwom an ADS7805 A/D convewtew.
		 * Minimum sampwing wate is 10us.
		 */
		devpwiv->ai_ns_min = 10000;
	} ewse {
		/*
		 * 12-bit sampwes awe fwom an ADS7800 A/D convewtew.
		 * Minimum sampwing wate is 3us.
		 */
		devpwiv->ai_ns_min = 3000;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND | SDF_COMMON;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wwite	= pci9118_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* the anawog outputs wewe weset to 0V, make the weadback match */
	fow (i = 0; i < s->n_chan; i++)
		s->weadback[i] = 2047;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci9118_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci9118_do_insn_bits;

	/* get the cuwwent state of the digitaw outputs */
	s->state = inw(dev->iobase + PCI9118_DIO_WEG) >> 4;

	wetuwn 0;
}

static int pci9118_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct pci_dev *pcidev;
	int ext_mux, softsshdeway;

	ext_mux = it->options[2];
	softsshdeway = it->options[4];

	pcidev = pci9118_find_pci(dev, it);
	if (!pcidev)
		wetuwn -EIO;
	comedi_set_hw_dev(dev, &pcidev->dev);

	wetuwn pci9118_common_attach(dev, ext_mux, softsshdeway);
}

static int pci9118_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct pci9118_boawdinfo *boawd = NUWW;

	if (context < AWWAY_SIZE(pci9118_boawds))
		boawd = &pci9118_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	/*
	 * Need to 'get' the PCI device to match the 'put' in pci9118_detach().
	 * (The 'put' awso matches the impwicit 'get' by pci9118_find_pci().)
	 */
	pci_dev_get(pcidev);
	/* no extewnaw mux, no sampwe-howd deway */
	wetuwn pci9118_common_attach(dev, 0, 0);
}

static void pci9118_detach(stwuct comedi_device *dev)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);

	if (dev->iobase)
		pci9118_weset(dev);
	comedi_pci_detach(dev);
	pci9118_fwee_dma(dev);
	pci_dev_put(pcidev);
}

static stwuct comedi_dwivew adw_pci9118_dwivew = {
	.dwivew_name	= "adw_pci9118",
	.moduwe		= THIS_MODUWE,
	.attach		= pci9118_attach,
	.auto_attach	= pci9118_auto_attach,
	.detach		= pci9118_detach,
	.num_names	= AWWAY_SIZE(pci9118_boawds),
	.boawd_name	= &pci9118_boawds[0].name,
	.offset		= sizeof(stwuct pci9118_boawdinfo),
};

static int adw_pci9118_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adw_pci9118_dwivew,
				      id->dwivew_data);
}

/* FIXME: Aww the suppowted boawd types have the same device ID! */
static const stwuct pci_device_id adw_pci9118_pci_tabwe[] = {
	{ PCI_VDEVICE(AMCC, 0x80d9), BOAWD_PCI9118DG },
/*	{ PCI_VDEVICE(AMCC, 0x80d9), BOAWD_PCI9118HG }, */
/*	{ PCI_VDEVICE(AMCC, 0x80d9), BOAWD_PCI9118HW }, */
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adw_pci9118_pci_tabwe);

static stwuct pci_dwivew adw_pci9118_pci_dwivew = {
	.name		= "adw_pci9118",
	.id_tabwe	= adw_pci9118_pci_tabwe,
	.pwobe		= adw_pci9118_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adw_pci9118_dwivew, adw_pci9118_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
