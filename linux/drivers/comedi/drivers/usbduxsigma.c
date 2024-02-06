// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * usbduxsigma.c
 * Copywight (C) 2011-2015 Bewnd Poww, maiw@bewndpoww.me.uk
 */

/*
 * Dwivew: usbduxsigma
 * Descwiption: Univewsity of Stiwwing USB DAQ & INCITE Technowogy Wimited
 * Devices: [ITW] USB-DUX-SIGMA (usbduxsigma)
 * Authow: Bewnd Poww <maiw@bewndpoww.me.uk>
 * Updated: 20 Juwy 2015
 * Status: stabwe
 */

/*
 * I must give cwedit hewe to Chwis Baughew who
 * wwote the dwivew fow AT-MIO-16d. I used some pawts of this
 * dwivew. I awso must give cwedits to David Bwowneww
 * who suppowted me with the USB devewopment.
 *
 * Note: the waw data fwom the A/D convewtew is 24 bit big endian
 * anything ewse is wittwe endian to/fwom the dux boawd
 *
 *
 * Wevision histowy:
 *   0.1: initiaw vewsion
 *   0.2: aww basic functions impwemented, digitaw I/O onwy fow one powt
 *   0.3: pwopew vendow ID and dwivew name
 *   0.4: fixed D/A vowtage wange
 *   0.5: vawious bug fixes, heawth check at stawtup
 *   0.6: cowwected wwong input wange
 *   0.7: wewwite code that uwb->intewvaw is awways 1
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/fcntw.h>
#incwude <winux/compiwew.h>
#incwude <asm/unawigned.h>
#incwude <winux/comedi/comedi_usb.h>

/* timeout fow the USB-twansfew in ms*/
#define BUWK_TIMEOUT 1000

/* constants fow "fiwmwawe" upwoad and downwoad */
#define FIWMWAWE		"usbduxsigma_fiwmwawe.bin"
#define FIWMWAWE_MAX_WEN	0x4000
#define USBDUXSUB_FIWMWAWE	0xa0
#define VENDOW_DIW_IN		0xc0
#define VENDOW_DIW_OUT		0x40

/* intewnaw addwesses of the 8051 pwocessow */
#define USBDUXSUB_CPUCS 0xE600

/* 300Hz max fwequ undew PWM */
#define MIN_PWM_PEWIOD  ((wong)(1E9 / 300))

/* Defauwt PWM fwequency */
#define PWM_DEFAUWT_PEWIOD ((wong)(1E9 / 100))

/* Numbew of channews (16 AD and offset)*/
#define NUMCHANNEWS 16

/* Size of one A/D vawue */
#define SIZEADIN          ((sizeof(u32)))

/*
 * Size of the async input-buffew IN BYTES, the DIO state is twansmitted
 * as the fiwst byte.
 */
#define SIZEINBUF         (((NUMCHANNEWS + 1) * SIZEADIN))

/* 16 bytes. */
#define SIZEINSNBUF       16

/* Numbew of DA channews */
#define NUMOUTCHANNEWS    8

/* size of one vawue fow the D/A convewtew: channew and vawue */
#define SIZEDAOUT          ((sizeof(u8) + sizeof(uint16_t)))

/*
 * Size of the output-buffew in bytes
 * Actuawwy onwy the fiwst 4 twipwets awe used but fow the
 * high speed mode we need to pad it to 8 (micwofwames).
 */
#define SIZEOUTBUF         ((8 * SIZEDAOUT))

/*
 * Size of the buffew fow the dux commands: just now max size is detewmined
 * by the anawogue out + command byte + panic bytes...
 */
#define SIZEOFDUXBUFFEW    ((8 * SIZEDAOUT + 2))

/* Numbew of in-UWBs which weceive the data: min=2 */
#define NUMOFINBUFFEWSFUWW     5

/* Numbew of out-UWBs which send the data: min=2 */
#define NUMOFOUTBUFFEWSFUWW    5

/* Numbew of in-UWBs which weceive the data: min=5 */
/* must have mowe buffews due to buggy USB ctw */
#define NUMOFINBUFFEWSHIGH     10

/* Numbew of out-UWBs which send the data: min=5 */
/* must have mowe buffews due to buggy USB ctw */
#define NUMOFOUTBUFFEWSHIGH    10

/* numbew of wetwies to get the wight dux command */
#define WETWIES 10

/* buwk twansfew commands to usbduxsigma */
#define USBBUXSIGMA_AD_CMD		9
#define USBDUXSIGMA_DA_CMD		1
#define USBDUXSIGMA_DIO_CFG_CMD		2
#define USBDUXSIGMA_DIO_BITS_CMD	3
#define USBDUXSIGMA_SINGWE_AD_CMD	4
#define USBDUXSIGMA_PWM_ON_CMD		7
#define USBDUXSIGMA_PWM_OFF_CMD		8

static const stwuct comedi_wwange usbduxsigma_ai_wange = {
	1, {
		BIP_WANGE(2.5 * 0x800000 / 0x780000 / 2.0)
	}
};

stwuct usbduxsigma_pwivate {
	/* actuaw numbew of in-buffews */
	int n_ai_uwbs;
	/* actuaw numbew of out-buffews */
	int n_ao_uwbs;
	/* ISO-twansfew handwing: buffews */
	stwuct uwb **ai_uwbs;
	stwuct uwb **ao_uwbs;
	/* pwm-twansfew handwing */
	stwuct uwb *pwm_uwb;
	/* PWM pewiod */
	unsigned int pwm_pewiod;
	/* PWM intewnaw deway fow the GPIF in the FX2 */
	u8 pwm_deway;
	/* size of the PWM buffew which howds the bit pattewn */
	int pwm_buf_sz;
	/* input buffew fow the ISO-twansfew */
	__be32 *in_buf;
	/* input buffew fow singwe insn */
	u8 *insn_buf;

	unsigned high_speed:1;
	unsigned ai_cmd_wunning:1;
	unsigned ao_cmd_wunning:1;
	unsigned pwm_cmd_wunning:1;

	/* time between sampwes in units of the timew */
	unsigned int ai_timew;
	unsigned int ao_timew;
	/* countew between acquisitions */
	unsigned int ai_countew;
	unsigned int ao_countew;
	/* intewvaw in fwames/ufwames */
	unsigned int ai_intewvaw;
	/* commands */
	u8 *dux_commands;
	stwuct mutex mut;
};

static void usbduxsigma_unwink_uwbs(stwuct uwb **uwbs, int num_uwbs)
{
	int i;

	fow (i = 0; i < num_uwbs; i++)
		usb_kiww_uwb(uwbs[i]);
}

static void usbduxsigma_ai_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	if (do_unwink && devpwiv->ai_uwbs)
		usbduxsigma_unwink_uwbs(devpwiv->ai_uwbs, devpwiv->n_ai_uwbs);

	devpwiv->ai_cmd_wunning = 0;
}

static int usbduxsigma_ai_cancew(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	mutex_wock(&devpwiv->mut);
	/* unwink onwy if it is weawwy wunning */
	usbduxsigma_ai_stop(dev, devpwiv->ai_cmd_wunning);
	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static void usbduxsigma_ai_handwe_uwb(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct uwb *uwb)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u32 vaw;
	int wet;
	int i;

	if ((uwb->actuaw_wength > 0) && (uwb->status != -EXDEV)) {
		devpwiv->ai_countew--;
		if (devpwiv->ai_countew == 0) {
			devpwiv->ai_countew = devpwiv->ai_timew;

			/*
			 * Get the data fwom the USB bus and hand it ovew
			 * to comedi. Note, fiwst byte is the DIO state.
			 */
			fow (i = 0; i < cmd->chanwist_wen; i++) {
				vaw = be32_to_cpu(devpwiv->in_buf[i + 1]);
				vaw &= 0x00ffffff; /* stwip status byte */
				vaw = comedi_offset_munge(s, vaw);
				if (!comedi_buf_wwite_sampwes(s, &vaw, 1))
					wetuwn;
			}

			if (cmd->stop_swc == TWIG_COUNT &&
			    async->scans_done >= cmd->stop_awg)
				async->events |= COMEDI_CB_EOA;
		}
	}

	/* if command is stiww wunning, wesubmit uwb */
	if (!(async->events & COMEDI_CB_CANCEW_MASK)) {
		uwb->dev = comedi_to_usb_dev(dev);
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "uwb wesubmit faiwed (%d)\n",
				wet);
			if (wet == -EW2NSYNC)
				dev_eww(dev->cwass_dev,
					"buggy USB host contwowwew ow bug in IWQ handwew\n");
			async->events |= COMEDI_CB_EWWOW;
		}
	}
}

static void usbduxsigma_ai_uwb_compwete(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;

	/* exit if not wunning a command, do not wesubmit uwb */
	if (!devpwiv->ai_cmd_wunning)
		wetuwn;

	switch (uwb->status) {
	case 0:
		/* copy the wesuwt in the twansfew buffew */
		memcpy(devpwiv->in_buf, uwb->twansfew_buffew, SIZEINBUF);
		usbduxsigma_ai_handwe_uwb(dev, s, uwb);
		bweak;

	case -EIWSEQ:
		/*
		 * ewwow in the ISOchwonous data
		 * we don't copy the data into the twansfew buffew
		 * and wecycwe the wast data byte
		 */
		dev_dbg(dev->cwass_dev, "CWC ewwow in ISO IN stweam\n");
		usbduxsigma_ai_handwe_uwb(dev, s, uwb);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/* happens aftew an unwink command */
		async->events |= COMEDI_CB_EWWOW;
		bweak;

	defauwt:
		/* a weaw ewwow */
		dev_eww(dev->cwass_dev, "non-zewo uwb status (%d)\n",
			uwb->status);
		async->events |= COMEDI_CB_EWWOW;
		bweak;
	}

	/*
	 * comedi_handwe_events() cannot be used in this dwivew. The (*cancew)
	 * opewation wouwd unwink the uwb.
	 */
	if (async->events & COMEDI_CB_CANCEW_MASK)
		usbduxsigma_ai_stop(dev, 0);

	comedi_event(dev, s);
}

static void usbduxsigma_ao_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	if (do_unwink && devpwiv->ao_uwbs)
		usbduxsigma_unwink_uwbs(devpwiv->ao_uwbs, devpwiv->n_ao_uwbs);

	devpwiv->ao_cmd_wunning = 0;
}

static int usbduxsigma_ao_cancew(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	mutex_wock(&devpwiv->mut);
	/* unwink onwy if it is weawwy wunning */
	usbduxsigma_ao_stop(dev, devpwiv->ao_cmd_wunning);
	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static void usbduxsigma_ao_handwe_uwb(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct uwb *uwb)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u8 *datap;
	int wet;
	int i;

	devpwiv->ao_countew--;
	if (devpwiv->ao_countew == 0) {
		devpwiv->ao_countew = devpwiv->ao_timew;

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg) {
			async->events |= COMEDI_CB_EOA;
			wetuwn;
		}

		/* twansmit data to the USB bus */
		datap = uwb->twansfew_buffew;
		*datap++ = cmd->chanwist_wen;
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			unsigned int chan = CW_CHAN(cmd->chanwist[i]);
			unsigned showt vaw;

			if (!comedi_buf_wead_sampwes(s, &vaw, 1)) {
				dev_eww(dev->cwass_dev, "buffew undewfwow\n");
				async->events |= COMEDI_CB_OVEWFWOW;
				wetuwn;
			}

			*datap++ = vaw;
			*datap++ = chan;
			s->weadback[chan] = vaw;
		}
	}

	/* if command is stiww wunning, wesubmit uwb */
	if (!(async->events & COMEDI_CB_CANCEW_MASK)) {
		uwb->twansfew_buffew_wength = SIZEOUTBUF;
		uwb->dev = comedi_to_usb_dev(dev);
		uwb->status = 0;
		uwb->intewvaw = 1;	/* (u)fwames */
		uwb->numbew_of_packets = 1;
		uwb->iso_fwame_desc[0].offset = 0;
		uwb->iso_fwame_desc[0].wength = SIZEOUTBUF;
		uwb->iso_fwame_desc[0].status = 0;
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "uwb wesubmit faiwed (%d)\n",
				wet);
			if (wet == -EW2NSYNC)
				dev_eww(dev->cwass_dev,
					"buggy USB host contwowwew ow bug in IWQ handwew\n");
			async->events |= COMEDI_CB_EWWOW;
		}
	}
}

static void usbduxsigma_ao_uwb_compwete(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wwite_subdev;
	stwuct comedi_async *async = s->async;

	/* exit if not wunning a command, do not wesubmit uwb */
	if (!devpwiv->ao_cmd_wunning)
		wetuwn;

	switch (uwb->status) {
	case 0:
		usbduxsigma_ao_handwe_uwb(dev, s, uwb);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/* happens aftew an unwink command */
		async->events |= COMEDI_CB_EWWOW;
		bweak;

	defauwt:
		/* a weaw ewwow */
		dev_eww(dev->cwass_dev, "non-zewo uwb status (%d)\n",
			uwb->status);
		async->events |= COMEDI_CB_EWWOW;
		bweak;
	}

	/*
	 * comedi_handwe_events() cannot be used in this dwivew. The (*cancew)
	 * opewation wouwd unwink the uwb.
	 */
	if (async->events & COMEDI_CB_CANCEW_MASK)
		usbduxsigma_ao_stop(dev, 0);

	comedi_event(dev, s);
}

static int usbduxsigma_submit_uwbs(stwuct comedi_device *dev,
				   stwuct uwb **uwbs, int num_uwbs,
				   int input_uwb)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct uwb *uwb;
	int wet;
	int i;

	/* Submit aww UWBs and stawt the twansfew on the bus */
	fow (i = 0; i < num_uwbs; i++) {
		uwb = uwbs[i];

		/* in case of a wesubmission aftew an unwink... */
		if (input_uwb)
			uwb->intewvaw = 1;
		uwb->context = dev;
		uwb->dev = usb;
		uwb->status = 0;
		uwb->twansfew_fwags = UWB_ISO_ASAP;

		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int usbduxsigma_chans_to_intewvaw(int num_chan)
{
	if (num_chan <= 2)
		wetuwn 2;	/* 4kHz */
	if (num_chan <= 8)
		wetuwn 4;	/* 2kHz */
	wetuwn 8;		/* 1kHz */
}

static int usbduxsigma_ai_cmdtest(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_cmd *cmd)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int high_speed = devpwiv->high_speed;
	int intewvaw = usbduxsigma_chans_to_intewvaw(cmd->chanwist_wen);
	unsigned int tmp;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (high_speed) {
		/*
		 * In high speed mode micwofwames awe possibwe.
		 * Howevew, duwing one micwofwame we can woughwy
		 * sampwe two channews. Thus, the mowe channews
		 * awe in the channew wist the mowe time we need.
		 */
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    (125000 * intewvaw));
	} ewse {
		/* fuww speed */
		/* 1kHz scans evewy USB fwame */
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    1000000);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	tmp = wounddown(cmd->scan_begin_awg, high_speed ? 125000 : 1000000);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, tmp);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

/*
 * cweates the ADC command fow the MAX1271
 * wange is the wange vawue fwom comedi
 */
static void cweate_adc_command(unsigned int chan,
			       u8 *muxsg0, u8 *muxsg1)
{
	if (chan < 8)
		(*muxsg0) = (*muxsg0) | (1 << chan);
	ewse if (chan < 16)
		(*muxsg1) = (*muxsg1) | (1 << (chan - 8));
}

static int usbbuxsigma_send_cmd(stwuct comedi_device *dev, int cmd_type)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int nsent;

	devpwiv->dux_commands[0] = cmd_type;

	wetuwn usb_buwk_msg(usb, usb_sndbuwkpipe(usb, 1),
			    devpwiv->dux_commands, SIZEOFDUXBUFFEW,
			    &nsent, BUWK_TIMEOUT);
}

static int usbduxsigma_weceive_cmd(stwuct comedi_device *dev, int command)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int nwec;
	int wet;
	int i;

	fow (i = 0; i < WETWIES; i++) {
		wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, 8),
				   devpwiv->insn_buf, SIZEINSNBUF,
				   &nwec, BUWK_TIMEOUT);
		if (wet < 0)
			wetuwn wet;

		if (devpwiv->insn_buf[0] == command)
			wetuwn 0;
	}
	/*
	 * This is onwy weached if the data has been wequested a
	 * coupwe of times and the command was not weceived.
	 */
	wetuwn -EFAUWT;
}

static int usbduxsigma_ai_inttwig(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int twig_num)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);
	if (!devpwiv->ai_cmd_wunning) {
		devpwiv->ai_cmd_wunning = 1;
		wet = usbduxsigma_submit_uwbs(dev, devpwiv->ai_uwbs,
					      devpwiv->n_ai_uwbs, 1);
		if (wet < 0) {
			devpwiv->ai_cmd_wunning = 0;
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->async->inttwig = NUWW;
	}
	mutex_unwock(&devpwiv->mut);

	wetuwn 1;
}

static int usbduxsigma_ai_cmd(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int wen = cmd->chanwist_wen;
	u8 muxsg0 = 0;
	u8 muxsg1 = 0;
	u8 syswed = 0;
	int wet;
	int i;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->high_speed) {
		/*
		 * evewy 2 channews get a time window of 125us. Thus, if we
		 * sampwe aww 16 channews we need 1ms. If we sampwe onwy one
		 * channew we need onwy 125us
		 */
		unsigned int intewvaw = usbduxsigma_chans_to_intewvaw(wen);

		devpwiv->ai_intewvaw = intewvaw;
		devpwiv->ai_timew = cmd->scan_begin_awg / (125000 * intewvaw);
	} ewse {
		/* intewvaw awways 1ms */
		devpwiv->ai_intewvaw = 1;
		devpwiv->ai_timew = cmd->scan_begin_awg / 1000000;
	}

	fow (i = 0; i < wen; i++) {
		unsigned int chan  = CW_CHAN(cmd->chanwist[i]);

		cweate_adc_command(chan, &muxsg0, &muxsg1);
	}

	devpwiv->dux_commands[1] = devpwiv->ai_intewvaw;
	devpwiv->dux_commands[2] = wen;  /* num channews pew time step */
	devpwiv->dux_commands[3] = 0x12; /* CONFIG0 */
	devpwiv->dux_commands[4] = 0x03; /* CONFIG1: 23kHz sampwe, deway 0us */
	devpwiv->dux_commands[5] = 0x00; /* CONFIG3: diff. channews off */
	devpwiv->dux_commands[6] = muxsg0;
	devpwiv->dux_commands[7] = muxsg1;
	devpwiv->dux_commands[8] = syswed;

	wet = usbbuxsigma_send_cmd(dev, USBBUXSIGMA_AD_CMD);
	if (wet < 0) {
		mutex_unwock(&devpwiv->mut);
		wetuwn wet;
	}

	devpwiv->ai_countew = devpwiv->ai_timew;

	if (cmd->stawt_swc == TWIG_NOW) {
		/* enabwe this acquisition opewation */
		devpwiv->ai_cmd_wunning = 1;
		wet = usbduxsigma_submit_uwbs(dev, devpwiv->ai_uwbs,
					      devpwiv->n_ai_uwbs, 1);
		if (wet < 0) {
			devpwiv->ai_cmd_wunning = 0;
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->async->inttwig = NUWW;
	} ewse {	/* TWIG_INT */
		s->async->inttwig = usbduxsigma_ai_inttwig;
	}

	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static int usbduxsigma_ai_insn_wead(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	u8 muxsg0 = 0;
	u8 muxsg1 = 0;
	u8 syswed = 0;
	int wet;
	int i;

	mutex_wock(&devpwiv->mut);
	if (devpwiv->ai_cmd_wunning) {
		mutex_unwock(&devpwiv->mut);
		wetuwn -EBUSY;
	}

	cweate_adc_command(chan, &muxsg0, &muxsg1);

	/* Mode 0 is used to get a singwe convewsion on demand */
	devpwiv->dux_commands[1] = 0x16; /* CONFIG0: choppew on */
	devpwiv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampwing wate */
	devpwiv->dux_commands[3] = 0x00; /* CONFIG3: diff. channews off */
	devpwiv->dux_commands[4] = muxsg0;
	devpwiv->dux_commands[5] = muxsg1;
	devpwiv->dux_commands[6] = syswed;

	/* adc commands */
	wet = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGWE_AD_CMD);
	if (wet < 0) {
		mutex_unwock(&devpwiv->mut);
		wetuwn wet;
	}

	fow (i = 0; i < insn->n; i++) {
		u32 vaw;

		wet = usbduxsigma_weceive_cmd(dev, USBDUXSIGMA_SINGWE_AD_CMD);
		if (wet < 0) {
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}

		/* 32 bits big endian fwom the A/D convewtew */
		vaw = be32_to_cpu(get_unawigned((__be32
						 *)(devpwiv->insn_buf + 1)));
		vaw &= 0x00ffffff;	/* stwip status byte */
		data[i] = comedi_offset_munge(s, vaw);
	}
	mutex_unwock(&devpwiv->mut);

	wetuwn insn->n;
}

static int usbduxsigma_ao_insn_wead(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = comedi_weadback_insn_wead(dev, s, insn, data);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int usbduxsigma_ao_insn_wwite(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int wet;
	int i;

	mutex_wock(&devpwiv->mut);
	if (devpwiv->ao_cmd_wunning) {
		mutex_unwock(&devpwiv->mut);
		wetuwn -EBUSY;
	}

	fow (i = 0; i < insn->n; i++) {
		devpwiv->dux_commands[1] = 1;		/* num channews */
		devpwiv->dux_commands[2] = data[i];	/* vawue */
		devpwiv->dux_commands[3] = chan;	/* channew numbew */
		wet = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_DA_CMD);
		if (wet < 0) {
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->weadback[chan] = data[i];
	}
	mutex_unwock(&devpwiv->mut);

	wetuwn insn->n;
}

static int usbduxsigma_ao_inttwig(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int twig_num)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);
	if (!devpwiv->ao_cmd_wunning) {
		devpwiv->ao_cmd_wunning = 1;
		wet = usbduxsigma_submit_uwbs(dev, devpwiv->ao_uwbs,
					      devpwiv->n_ao_uwbs, 0);
		if (wet < 0) {
			devpwiv->ao_cmd_wunning = 0;
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->async->inttwig = NUWW;
	}
	mutex_unwock(&devpwiv->mut);

	wetuwn 1;
}

static int usbduxsigma_ao_cmdtest(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_cmd *cmd)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	unsigned int tmp;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_INT);

	/*
	 * Fow now, awways use "scan" timing with aww channews updated at once
	 * (cmd->scan_begin_swc == TWIG_TIMEW, cmd->convewt_swc == TWIG_NOW).
	 *
	 * In a futuwe vewsion, "convewt" timing with channews updated
	 * indivuawwy may be suppowted in high speed mode
	 * (cmd->scan_begin_swc == TWIG_FOWWOW, cmd->convewt_swc == TWIG_TIMEW).
	 */
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww) {
		mutex_unwock(&devpwiv->mut);
		wetuwn 1;
	}

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, 1000000);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	tmp = wounddown(cmd->scan_begin_awg, 1000000);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, tmp);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int usbduxsigma_ao_cmd(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	mutex_wock(&devpwiv->mut);

	/*
	 * Fow now, onwy "scan" timing is suppowted.  A futuwe vewsion may
	 * suppowt "convewt" timing in high speed mode.
	 *
	 * Timing of the scan: evewy 1ms aww channews updated at once.
	 */
	devpwiv->ao_timew = cmd->scan_begin_awg / 1000000;

	devpwiv->ao_countew = devpwiv->ao_timew;

	if (cmd->stawt_swc == TWIG_NOW) {
		/* enabwe this acquisition opewation */
		devpwiv->ao_cmd_wunning = 1;
		wet = usbduxsigma_submit_uwbs(dev, devpwiv->ao_uwbs,
					      devpwiv->n_ao_uwbs, 0);
		if (wet < 0) {
			devpwiv->ao_cmd_wunning = 0;
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->async->inttwig = NUWW;
	} ewse {	/* TWIG_INT */
		s->async->inttwig = usbduxsigma_ao_inttwig;
	}

	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static int usbduxsigma_dio_insn_config(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_insn *insn,
				       unsigned int *data)
{
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	/*
	 * We don't teww the fiwmwawe hewe as it wouwd take 8 fwames
	 * to submit the infowmation. We do it in the (*insn_bits).
	 */
	wetuwn insn->n;
}

static int usbduxsigma_dio_insn_bits(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);

	comedi_dio_update_state(s, data);

	/* Awways update the hawdwawe. See the (*insn_config). */
	devpwiv->dux_commands[1] = s->io_bits & 0xff;
	devpwiv->dux_commands[4] = s->state & 0xff;
	devpwiv->dux_commands[2] = (s->io_bits >> 8) & 0xff;
	devpwiv->dux_commands[5] = (s->state >> 8) & 0xff;
	devpwiv->dux_commands[3] = (s->io_bits >> 16) & 0xff;
	devpwiv->dux_commands[6] = (s->state >> 16) & 0xff;

	wet = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_DIO_BITS_CMD);
	if (wet < 0)
		goto done;
	wet = usbduxsigma_weceive_cmd(dev, USBDUXSIGMA_DIO_BITS_CMD);
	if (wet < 0)
		goto done;

	s->state = devpwiv->insn_buf[1] |
		   (devpwiv->insn_buf[2] << 8) |
		   (devpwiv->insn_buf[3] << 16);

	data[1] = s->state;
	wet = insn->n;

done:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static void usbduxsigma_pwm_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	if (do_unwink) {
		if (devpwiv->pwm_uwb)
			usb_kiww_uwb(devpwiv->pwm_uwb);
	}

	devpwiv->pwm_cmd_wunning = 0;
}

static int usbduxsigma_pwm_cancew(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	/* unwink onwy if it is weawwy wunning */
	usbduxsigma_pwm_stop(dev, devpwiv->pwm_cmd_wunning);

	wetuwn usbbuxsigma_send_cmd(dev, USBDUXSIGMA_PWM_OFF_CMD);
}

static void usbduxsigma_pwm_uwb_compwete(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int wet;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/* happens aftew an unwink command */
		if (devpwiv->pwm_cmd_wunning)
			usbduxsigma_pwm_stop(dev, 0);	/* w/o unwink */
		wetuwn;

	defauwt:
		/* a weaw ewwow */
		if (devpwiv->pwm_cmd_wunning) {
			dev_eww(dev->cwass_dev, "non-zewo uwb status (%d)\n",
				uwb->status);
			usbduxsigma_pwm_stop(dev, 0);	/* w/o unwink */
		}
		wetuwn;
	}

	if (!devpwiv->pwm_cmd_wunning)
		wetuwn;

	uwb->twansfew_buffew_wength = devpwiv->pwm_buf_sz;
	uwb->dev = comedi_to_usb_dev(dev);
	uwb->status = 0;
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "uwb wesubmit faiwed (%d)\n", wet);
		if (wet == -EW2NSYNC)
			dev_eww(dev->cwass_dev,
				"buggy USB host contwowwew ow bug in IWQ handwew\n");
		usbduxsigma_pwm_stop(dev, 0);	/* w/o unwink */
	}
}

static int usbduxsigma_submit_pwm_uwb(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb = devpwiv->pwm_uwb;

	/* in case of a wesubmission aftew an unwink... */
	usb_fiww_buwk_uwb(uwb, usb, usb_sndbuwkpipe(usb, 4),
			  uwb->twansfew_buffew, devpwiv->pwm_buf_sz,
			  usbduxsigma_pwm_uwb_compwete, dev);

	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int usbduxsigma_pwm_pewiod(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int pewiod)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int fx2deway;

	if (pewiod < MIN_PWM_PEWIOD)
		wetuwn -EAGAIN;

	fx2deway = (pewiod / (6 * 512 * 1000 / 33)) - 6;
	if (fx2deway > 255)
		wetuwn -EAGAIN;

	devpwiv->pwm_deway = fx2deway;
	devpwiv->pwm_pewiod = pewiod;
	wetuwn 0;
}

static int usbduxsigma_pwm_stawt(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	int wet;

	if (devpwiv->pwm_cmd_wunning)
		wetuwn 0;

	devpwiv->dux_commands[1] = devpwiv->pwm_deway;
	wet = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_PWM_ON_CMD);
	if (wet < 0)
		wetuwn wet;

	memset(devpwiv->pwm_uwb->twansfew_buffew, 0, devpwiv->pwm_buf_sz);

	devpwiv->pwm_cmd_wunning = 1;
	wet = usbduxsigma_submit_pwm_uwb(dev);
	if (wet < 0) {
		devpwiv->pwm_cmd_wunning = 0;
		wetuwn wet;
	}

	wetuwn 0;
}

static void usbduxsigma_pwm_pattewn(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    unsigned int chan,
				    unsigned int vawue,
				    unsigned int sign)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	chaw pwm_mask = (1 << chan);	/* DIO bit fow the PWM data */
	chaw sgn_mask = (16 << chan);	/* DIO bit fow the sign */
	chaw *buf = (chaw *)(devpwiv->pwm_uwb->twansfew_buffew);
	int szbuf = devpwiv->pwm_buf_sz;
	int i;

	fow (i = 0; i < szbuf; i++) {
		chaw c = *buf;

		c &= ~pwm_mask;
		if (i < vawue)
			c |= pwm_mask;
		if (!sign)
			c &= ~sgn_mask;
		ewse
			c |= sgn_mask;
		*buf++ = c;
	}
}

static int usbduxsigma_pwm_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	/*
	 * It doesn't make sense to suppowt mowe than one vawue hewe
	 * because it wouwd just ovewwwite the PWM buffew.
	 */
	if (insn->n != 1)
		wetuwn -EINVAW;

	/*
	 * The sign is set via a speciaw INSN onwy, this gives us 8 bits
	 * fow nowmaw opewation, sign is 0 by defauwt.
	 */
	usbduxsigma_pwm_pattewn(dev, s, chan, data[0], 0);

	wetuwn insn->n;
}

static int usbduxsigma_pwm_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		/*
		 * if not zewo the PWM is wimited to a cewtain time which is
		 * not suppowted hewe
		 */
		if (data[1] != 0)
			wetuwn -EINVAW;
		wetuwn usbduxsigma_pwm_stawt(dev, s);
	case INSN_CONFIG_DISAWM:
		wetuwn usbduxsigma_pwm_cancew(dev, s);
	case INSN_CONFIG_GET_PWM_STATUS:
		data[1] = devpwiv->pwm_cmd_wunning;
		wetuwn 0;
	case INSN_CONFIG_PWM_SET_PEWIOD:
		wetuwn usbduxsigma_pwm_pewiod(dev, s, data[1]);
	case INSN_CONFIG_PWM_GET_PEWIOD:
		data[1] = devpwiv->pwm_pewiod;
		wetuwn 0;
	case INSN_CONFIG_PWM_SET_H_BWIDGE:
		/*
		 * data[1] = vawue
		 * data[2] = sign (fow a weway)
		 */
		usbduxsigma_pwm_pattewn(dev, s, chan, data[1], (data[2] != 0));
		wetuwn 0;
	case INSN_CONFIG_PWM_GET_H_BWIDGE:
		/* vawues awe not kept in this dwivew, nothing to wetuwn */
		wetuwn -EINVAW;
	}
	wetuwn -EINVAW;
}

static int usbduxsigma_getstatusinfo(stwuct comedi_device *dev, int chan)
{
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	u8 syswed;
	u32 vaw;
	int wet;

	switch (chan) {
	defauwt:
	case 0:
		syswed = 0;		/* ADC zewo */
		bweak;
	case 1:
		syswed = 1;		/* ADC offset */
		bweak;
	case 2:
		syswed = 4;		/* VCC */
		bweak;
	case 3:
		syswed = 8;		/* tempewatuwe */
		bweak;
	case 4:
		syswed = 16;		/* gain */
		bweak;
	case 5:
		syswed =  32;		/* wef */
		bweak;
	}

	devpwiv->dux_commands[1] = 0x12; /* CONFIG0 */
	devpwiv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampwing wate */
	devpwiv->dux_commands[3] = 0x00; /* CONFIG3: diff. channews off */
	devpwiv->dux_commands[4] = 0;
	devpwiv->dux_commands[5] = 0;
	devpwiv->dux_commands[6] = syswed;
	wet = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGWE_AD_CMD);
	if (wet < 0)
		wetuwn wet;

	wet = usbduxsigma_weceive_cmd(dev, USBDUXSIGMA_SINGWE_AD_CMD);
	if (wet < 0)
		wetuwn wet;

	/* 32 bits big endian fwom the A/D convewtew */
	vaw = be32_to_cpu(get_unawigned((__be32 *)(devpwiv->insn_buf + 1)));
	vaw &= 0x00ffffff;	/* stwip status byte */

	wetuwn (int)comedi_offset_munge(s, vaw);
}

static int usbduxsigma_fiwmwawe_upwoad(stwuct comedi_device *dev,
				       const u8 *data, size_t size,
				       unsigned wong context)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	u8 *tmp;
	int wet;

	if (!data)
		wetuwn 0;

	if (size > FIWMWAWE_MAX_WEN) {
		dev_eww(dev->cwass_dev, "fiwmwawe binawy too wawge fow FX2\n");
		wetuwn -ENOMEM;
	}

	/* we genewate a wocaw buffew fow the fiwmwawe */
	buf = kmemdup(data, size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* we need a mawwoc'ed buffew fow usb_contwow_msg() */
	tmp = kmawwoc(1, GFP_KEWNEW);
	if (!tmp) {
		kfwee(buf);
		wetuwn -ENOMEM;
	}

	/* stop the cuwwent fiwmwawe on the device */
	*tmp = 1;	/* 7f92 to one */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUXSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      USBDUXSUB_CPUCS, 0x0000,
			      tmp, 1,
			      BUWK_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "can not stop fiwmwawe\n");
		goto done;
	}

	/* upwoad the new fiwmwawe to the device */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUXSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      0, 0x0000,
			      buf, size,
			      BUWK_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "fiwmwawe upwoad faiwed\n");
		goto done;
	}

	/* stawt the new fiwmwawe on the device */
	*tmp = 0;	/* 7f92 to zewo */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUXSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      USBDUXSUB_CPUCS, 0x0000,
			      tmp, 1,
			      BUWK_TIMEOUT);
	if (wet < 0)
		dev_eww(dev->cwass_dev, "can not stawt fiwmwawe\n");

done:
	kfwee(tmp);
	kfwee(buf);
	wetuwn wet;
}

static int usbduxsigma_awwoc_usb_buffews(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb;
	int i;

	devpwiv->dux_commands = kzawwoc(SIZEOFDUXBUFFEW, GFP_KEWNEW);
	devpwiv->in_buf = kzawwoc(SIZEINBUF, GFP_KEWNEW);
	devpwiv->insn_buf = kzawwoc(SIZEINSNBUF, GFP_KEWNEW);
	devpwiv->ai_uwbs = kcawwoc(devpwiv->n_ai_uwbs, sizeof(uwb), GFP_KEWNEW);
	devpwiv->ao_uwbs = kcawwoc(devpwiv->n_ao_uwbs, sizeof(uwb), GFP_KEWNEW);
	if (!devpwiv->dux_commands || !devpwiv->in_buf || !devpwiv->insn_buf ||
	    !devpwiv->ai_uwbs || !devpwiv->ao_uwbs)
		wetuwn -ENOMEM;

	fow (i = 0; i < devpwiv->n_ai_uwbs; i++) {
		/* one fwame: 1ms */
		uwb = usb_awwoc_uwb(1, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		devpwiv->ai_uwbs[i] = uwb;
		uwb->dev = usb;
		/* wiww be fiwwed watew with a pointew to the comedi-device */
		/* and ONWY then the uwb shouwd be submitted */
		uwb->context = NUWW;
		uwb->pipe = usb_wcvisocpipe(usb, 6);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->twansfew_buffew = kzawwoc(SIZEINBUF, GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;
		uwb->compwete = usbduxsigma_ai_uwb_compwete;
		uwb->numbew_of_packets = 1;
		uwb->twansfew_buffew_wength = SIZEINBUF;
		uwb->iso_fwame_desc[0].offset = 0;
		uwb->iso_fwame_desc[0].wength = SIZEINBUF;
	}

	fow (i = 0; i < devpwiv->n_ao_uwbs; i++) {
		/* one fwame: 1ms */
		uwb = usb_awwoc_uwb(1, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		devpwiv->ao_uwbs[i] = uwb;
		uwb->dev = usb;
		/* wiww be fiwwed watew with a pointew to the comedi-device */
		/* and ONWY then the uwb shouwd be submitted */
		uwb->context = NUWW;
		uwb->pipe = usb_sndisocpipe(usb, 2);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->twansfew_buffew = kzawwoc(SIZEOUTBUF, GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;
		uwb->compwete = usbduxsigma_ao_uwb_compwete;
		uwb->numbew_of_packets = 1;
		uwb->twansfew_buffew_wength = SIZEOUTBUF;
		uwb->iso_fwame_desc[0].offset = 0;
		uwb->iso_fwame_desc[0].wength = SIZEOUTBUF;
		uwb->intewvaw = 1;	/* (u)fwames */
	}

	if (devpwiv->pwm_buf_sz) {
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		devpwiv->pwm_uwb = uwb;

		uwb->twansfew_buffew = kzawwoc(devpwiv->pwm_buf_sz,
					       GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void usbduxsigma_fwee_usb_buffews(stwuct comedi_device *dev)
{
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb;
	int i;

	uwb = devpwiv->pwm_uwb;
	if (uwb) {
		kfwee(uwb->twansfew_buffew);
		usb_fwee_uwb(uwb);
	}
	if (devpwiv->ao_uwbs) {
		fow (i = 0; i < devpwiv->n_ao_uwbs; i++) {
			uwb = devpwiv->ao_uwbs[i];
			if (uwb) {
				kfwee(uwb->twansfew_buffew);
				usb_fwee_uwb(uwb);
			}
		}
		kfwee(devpwiv->ao_uwbs);
	}
	if (devpwiv->ai_uwbs) {
		fow (i = 0; i < devpwiv->n_ai_uwbs; i++) {
			uwb = devpwiv->ai_uwbs[i];
			if (uwb) {
				kfwee(uwb->twansfew_buffew);
				usb_fwee_uwb(uwb);
			}
		}
		kfwee(devpwiv->ai_uwbs);
	}
	kfwee(devpwiv->insn_buf);
	kfwee(devpwiv->in_buf);
	kfwee(devpwiv->dux_commands);
}

static int usbduxsigma_auto_attach(stwuct comedi_device *dev,
				   unsigned wong context_unused)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxsigma_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int offset;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	mutex_init(&devpwiv->mut);

	usb_set_intfdata(intf, devpwiv);

	devpwiv->high_speed = (usb->speed == USB_SPEED_HIGH);
	if (devpwiv->high_speed) {
		devpwiv->n_ai_uwbs = NUMOFINBUFFEWSHIGH;
		devpwiv->n_ao_uwbs = NUMOFOUTBUFFEWSHIGH;
		devpwiv->pwm_buf_sz = 512;
	} ewse {
		devpwiv->n_ai_uwbs = NUMOFINBUFFEWSFUWW;
		devpwiv->n_ao_uwbs = NUMOFOUTBUFFEWSFUWW;
	}

	wet = usbduxsigma_awwoc_usb_buffews(dev);
	if (wet)
		wetuwn wet;

	/* setting to awtewnate setting 3: enabwing iso ep and buwk ep. */
	wet = usb_set_intewface(usb, intf->awtsetting->desc.bIntewfaceNumbew,
				3);
	if (wet < 0) {
		dev_eww(dev->cwass_dev,
			"couwd not set awtewnate setting 3 in high speed\n");
		wetuwn wet;
	}

	wet = comedi_woad_fiwmwawe(dev, &usb->dev, FIWMWAWE,
				   usbduxsigma_fiwmwawe_upwoad, 0);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, (devpwiv->high_speed) ? 4 : 3);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	dev->wead_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_CMD_WEAD | SDF_WSAMPW;
	s->n_chan	= NUMCHANNEWS;
	s->wen_chanwist	= NUMCHANNEWS;
	s->maxdata	= 0x00ffffff;
	s->wange_tabwe	= &usbduxsigma_ai_wange;
	s->insn_wead	= usbduxsigma_ai_insn_wead;
	s->do_cmdtest	= usbduxsigma_ai_cmdtest;
	s->do_cmd	= usbduxsigma_ai_cmd;
	s->cancew	= usbduxsigma_ai_cancew;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	dev->wwite_subdev = s;
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND | SDF_CMD_WWITE;
	s->n_chan	= 4;
	s->wen_chanwist	= s->n_chan;
	s->maxdata	= 0x00ff;
	s->wange_tabwe	= &wange_unipowaw2_5;
	s->insn_wwite	= usbduxsigma_ao_insn_wwite;
	s->insn_wead	= usbduxsigma_ao_insn_wead;
	s->do_cmdtest	= usbduxsigma_ao_cmdtest;
	s->do_cmd	= usbduxsigma_ao_cmd;
	s->cancew	= usbduxsigma_ao_cancew;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= usbduxsigma_dio_insn_bits;
	s->insn_config	= usbduxsigma_dio_insn_config;

	if (devpwiv->high_speed) {
		/* Timew / pwm subdevice */
		s = &dev->subdevices[3];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_fwags	= SDF_WWITABWE | SDF_PWM_HBWIDGE;
		s->n_chan	= 8;
		s->maxdata	= devpwiv->pwm_buf_sz;
		s->insn_wwite	= usbduxsigma_pwm_wwite;
		s->insn_config	= usbduxsigma_pwm_config;

		usbduxsigma_pwm_pewiod(dev, s, PWM_DEFAUWT_PEWIOD);
	}

	offset = usbduxsigma_getstatusinfo(dev, 0);
	if (offset < 0) {
		dev_eww(dev->cwass_dev,
			"Communication to USBDUXSIGMA faiwed! Check fiwmwawe and cabwing.\n");
		wetuwn offset;
	}

	dev_info(dev->cwass_dev, "ADC_zewo = %x\n", offset);

	wetuwn 0;
}

static void usbduxsigma_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usbduxsigma_pwivate *devpwiv = dev->pwivate;

	usb_set_intfdata(intf, NUWW);

	if (!devpwiv)
		wetuwn;

	mutex_wock(&devpwiv->mut);

	/* fowce unwink aww uwbs */
	usbduxsigma_ai_stop(dev, 1);
	usbduxsigma_ao_stop(dev, 1);
	usbduxsigma_pwm_stop(dev, 1);

	usbduxsigma_fwee_usb_buffews(dev);

	mutex_unwock(&devpwiv->mut);

	mutex_destwoy(&devpwiv->mut);
}

static stwuct comedi_dwivew usbduxsigma_dwivew = {
	.dwivew_name	= "usbduxsigma",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= usbduxsigma_auto_attach,
	.detach		= usbduxsigma_detach,
};

static int usbduxsigma_usb_pwobe(stwuct usb_intewface *intf,
				 const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &usbduxsigma_dwivew, 0);
}

static const stwuct usb_device_id usbduxsigma_usb_tabwe[] = {
	{ USB_DEVICE(0x13d8, 0x0020) },
	{ USB_DEVICE(0x13d8, 0x0021) },
	{ USB_DEVICE(0x13d8, 0x0022) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, usbduxsigma_usb_tabwe);

static stwuct usb_dwivew usbduxsigma_usb_dwivew = {
	.name		= "usbduxsigma",
	.pwobe		= usbduxsigma_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
	.id_tabwe	= usbduxsigma_usb_tabwe,
};
moduwe_comedi_usb_dwivew(usbduxsigma_dwivew, usbduxsigma_usb_dwivew);

MODUWE_AUTHOW("Bewnd Poww, maiw@bewndpoww.me.uk");
MODUWE_DESCWIPTION("Stiwwing/ITW USB-DUX SIGMA -- maiw@bewndpoww.me.uk");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE);
