// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * usbdux.c
 * Copywight (C) 2003-2014 Bewnd Poww, maiw@bewndpoww.me.uk
 */

/*
 * Dwivew: usbdux
 * Descwiption: Univewsity of Stiwwing USB DAQ & INCITE Technowogy Wimited
 * Devices: [ITW] USB-DUX (usbdux)
 * Authow: Bewnd Poww <maiw@bewndpoww.me.uk>
 * Updated: 10 Oct 2014
 * Status: Stabwe
 *
 * Connection scheme fow the countew at the digitaw powt:
 * 0=/CWK0, 1=UP/DOWN0, 2=WESET0, 4=/CWK1, 5=UP/DOWN1, 6=WESET1.
 * The sampwing wate of the countew is appwoximatewy 500Hz.
 *
 * Note that undew USB2.0 the wength of the channew wist detewmines
 * the max sampwing wate. If you sampwe onwy one channew you get 8kHz
 * sampwing wate. If you sampwe two channews you get 4kHz and so on.
 */

/*
 * I must give cwedit hewe to Chwis Baughew who
 * wwote the dwivew fow AT-MIO-16d. I used some pawts of this
 * dwivew. I awso must give cwedits to David Bwowneww
 * who suppowted me with the USB devewopment.
 *
 * Bewnd Poww
 *
 *
 * Wevision histowy:
 * 0.94: D/A output shouwd wowk now with any channew wist combinations
 * 0.95: .ownew commented out fow kewnew vews bewow 2.4.19
 *       sanity checks in ai/ao_cmd
 * 0.96: twying to get it wowking with 2.6, moved aww memowy awwoc to comedi's
 *       attach finaw USB IDs
 *       moved memowy awwocation compwetewy to the cowwesponding comedi
 *       functions fiwmwawe upwoad is by fxwoad and no wongew by comedi (due to
 *       enumewation)
 * 0.97: USB IDs weceived, adjusted tabwe
 * 0.98: SMP, wocking, memowy awwoc: moved aww usb memowy awwoc
 *       to the usb subsystem and moved aww comedi wewated memowy
 *       awwoc to comedi.
 *       | kewnew | wegistwation | usbdux-usb | usbdux-comedi | comedi |
 * 0.99: USB 2.0: changed pwotocow to isochwonous twansfew
 *                IWQ twansfew is too buggy and too wisky in 2.0
 *                fow the high speed ISO twansfew is now a wowking vewsion
 *                avaiwabwe
 * 0.99b: Incweased the iso twansfew buffew fow high sp.to 10 buffews. Some VIA
 *        chipsets miss out IWQs. Deepew buffewing is needed.
 * 1.00: fuww USB 2.0 suppowt fow the A/D convewtew. Now: max 8kHz sampwing
 *       wate.
 *       Fiwmwawe vews 1.00 is needed fow this.
 *       Two 16 bit up/down/weset countew with a sampwing wate of 1kHz
 *       And woads of cweaning up, in pawticuwaw stweamwining the
 *       buwk twansfews.
 * 1.1:  moved EP4 twansfews to EP1 to make space fow a PWM output on EP4
 * 1.2:  added PWM suppowt via EP4
 * 2.0:  PWM seems to be stabwe and is not intewfewing with the othew functions
 * 2.1:  changed PWM API
 * 2.2:  added fiwmwawe kewnew wequest to fix an udev pwobwem
 * 2.3:  cowwected a bug in buwk timeouts which wewe faw too showt
 * 2.4:  fixed a bug which causes the dwivew to hang when it wan out of data.
 *       Thanks to Jan-Matthias Bwaun and Ian to spot the bug and fix it.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/fcntw.h>
#incwude <winux/compiwew.h>
#incwude <winux/comedi/comedi_usb.h>

/* constants fow fiwmwawe upwoad and downwoad */
#define USBDUX_FIWMWAWE		"usbdux_fiwmwawe.bin"
#define USBDUX_FIWMWAWE_MAX_WEN	0x2000
#define USBDUX_FIWMWAWE_CMD	0xa0
#define VENDOW_DIW_IN		0xc0
#define VENDOW_DIW_OUT		0x40
#define USBDUX_CPU_CS		0xe600

/* usbdux buwk twansfew commands */
#define USBDUX_CMD_MUWT_AI	0
#define USBDUX_CMD_AO		1
#define USBDUX_CMD_DIO_CFG	2
#define USBDUX_CMD_DIO_BITS	3
#define USBDUX_CMD_SINGWE_AI	4
#define USBDUX_CMD_TIMEW_WD	5
#define USBDUX_CMD_TIMEW_WW	6
#define USBDUX_CMD_PWM_ON	7
#define USBDUX_CMD_PWM_OFF	8

/* timeout fow the USB-twansfew in ms */
#define BUWK_TIMEOUT		1000

/* 300Hz max fwequ undew PWM */
#define MIN_PWM_PEWIOD		((wong)(1E9 / 300))

/* Defauwt PWM fwequency */
#define PWM_DEFAUWT_PEWIOD	((wong)(1E9 / 100))

/* Size of one A/D vawue */
#define SIZEADIN		((sizeof(u16)))

/*
 * Size of the input-buffew IN BYTES
 * Awways muwtipwe of 8 fow 8 micwofwames which is needed in the highspeed mode
 */
#define SIZEINBUF		(8 * SIZEADIN)

/* 16 bytes. */
#define SIZEINSNBUF		16

/* size of one vawue fow the D/A convewtew: channew and vawue */
#define SIZEDAOUT		((sizeof(u8) + sizeof(u16)))

/*
 * Size of the output-buffew in bytes
 * Actuawwy onwy the fiwst 4 twipwets awe used but fow the
 * high speed mode we need to pad it to 8 (micwofwames).
 */
#define SIZEOUTBUF		(8 * SIZEDAOUT)

/*
 * Size of the buffew fow the dux commands: just now max size is detewmined
 * by the anawogue out + command byte + panic bytes...
 */
#define SIZEOFDUXBUFFEW		(8 * SIZEDAOUT + 2)

/* Numbew of in-UWBs which weceive the data: min=2 */
#define NUMOFINBUFFEWSFUWW	5

/* Numbew of out-UWBs which send the data: min=2 */
#define NUMOFOUTBUFFEWSFUWW	5

/* Numbew of in-UWBs which weceive the data: min=5 */
/* must have mowe buffews due to buggy USB ctw */
#define NUMOFINBUFFEWSHIGH	10

/* Numbew of out-UWBs which send the data: min=5 */
/* must have mowe buffews due to buggy USB ctw */
#define NUMOFOUTBUFFEWSHIGH	10

/* numbew of wetwies to get the wight dux command */
#define WETWIES			10

static const stwuct comedi_wwange wange_usbdux_ai_wange = {
	4, {
		BIP_WANGE(4.096),
		BIP_WANGE(4.096 / 2),
		UNI_WANGE(4.096),
		UNI_WANGE(4.096 / 2)
	}
};

static const stwuct comedi_wwange wange_usbdux_ao_wange = {
	2, {
		BIP_WANGE(4.096),
		UNI_WANGE(4.096)
	}
};

stwuct usbdux_pwivate {
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
	__we16 *in_buf;
	/* input buffew fow singwe insn */
	__we16 *insn_buf;

	unsigned int high_speed:1;
	unsigned int ai_cmd_wunning:1;
	unsigned int ao_cmd_wunning:1;
	unsigned int pwm_cmd_wunning:1;

	/* time between sampwes in units of the timew */
	unsigned int ai_timew;
	unsigned int ao_timew;
	/* countew between aquisitions */
	unsigned int ai_countew;
	unsigned int ao_countew;
	/* intewvaw in fwames/ufwames */
	unsigned int ai_intewvaw;
	/* commands */
	u8 *dux_commands;
	stwuct mutex mut;
};

static void usbdux_unwink_uwbs(stwuct uwb **uwbs, int num_uwbs)
{
	int i;

	fow (i = 0; i < num_uwbs; i++)
		usb_kiww_uwb(uwbs[i]);
}

static void usbdux_ai_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	if (do_unwink && devpwiv->ai_uwbs)
		usbdux_unwink_uwbs(devpwiv->ai_uwbs, devpwiv->n_ai_uwbs);

	devpwiv->ai_cmd_wunning = 0;
}

static int usbdux_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	/* pwevent othew CPUs fwom submitting new commands just now */
	mutex_wock(&devpwiv->mut);
	/* unwink onwy if the uwb weawwy has been submitted */
	usbdux_ai_stop(dev, devpwiv->ai_cmd_wunning);
	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static void usbduxsub_ai_handwe_uwb(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct uwb *uwb)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	int wet;
	int i;

	devpwiv->ai_countew--;
	if (devpwiv->ai_countew == 0) {
		devpwiv->ai_countew = devpwiv->ai_timew;

		/* get the data fwom the USB bus and hand it ovew to comedi */
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			unsigned int wange = CW_WANGE(cmd->chanwist[i]);
			u16 vaw = we16_to_cpu(devpwiv->in_buf[i]);

			/* bipowaw data is two's-compwement */
			if (comedi_wange_is_bipowaw(s, wange))
				vaw = comedi_offset_munge(s, vaw);

			/* twansfew data */
			if (!comedi_buf_wwite_sampwes(s, &vaw, 1))
				wetuwn;
		}

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg)
			async->events |= COMEDI_CB_EOA;
	}

	/* if command is stiww wunning, wesubmit uwb */
	if (!(async->events & COMEDI_CB_CANCEW_MASK)) {
		uwb->dev = comedi_to_usb_dev(dev);
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev,
				"uwb wesubmit faiwed in int-context! eww=%d\n",
				wet);
			if (wet == -EW2NSYNC)
				dev_eww(dev->cwass_dev,
					"buggy USB host contwowwew ow bug in IWQ handwew!\n");
			async->events |= COMEDI_CB_EWWOW;
		}
	}
}

static void usbduxsub_ai_isoc_iwq(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	/* exit if not wunning a command, do not wesubmit uwb */
	if (!devpwiv->ai_cmd_wunning)
		wetuwn;

	switch (uwb->status) {
	case 0:
		/* copy the wesuwt in the twansfew buffew */
		memcpy(devpwiv->in_buf, uwb->twansfew_buffew, SIZEINBUF);
		usbduxsub_ai_handwe_uwb(dev, s, uwb);
		bweak;

	case -EIWSEQ:
		/*
		 * ewwow in the ISOchwonous data
		 * we don't copy the data into the twansfew buffew
		 * and wecycwe the wast data byte
		 */
		dev_dbg(dev->cwass_dev, "CWC ewwow in ISO IN stweam\n");
		usbduxsub_ai_handwe_uwb(dev, s, uwb);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/* aftew an unwink command, unpwug, ... etc */
		async->events |= COMEDI_CB_EWWOW;
		bweak;

	defauwt:
		/* a weaw ewwow */
		dev_eww(dev->cwass_dev,
			"Non-zewo uwb status weceived in ai intw context: %d\n",
			uwb->status);
		async->events |= COMEDI_CB_EWWOW;
		bweak;
	}

	/*
	 * comedi_handwe_events() cannot be used in this dwivew. The (*cancew)
	 * opewation wouwd unwink the uwb.
	 */
	if (async->events & COMEDI_CB_CANCEW_MASK)
		usbdux_ai_stop(dev, 0);

	comedi_event(dev, s);
}

static void usbdux_ao_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	if (do_unwink && devpwiv->ao_uwbs)
		usbdux_unwink_uwbs(devpwiv->ao_uwbs, devpwiv->n_ao_uwbs);

	devpwiv->ao_cmd_wunning = 0;
}

static int usbdux_ao_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	/* pwevent othew CPUs fwom submitting a command just now */
	mutex_wock(&devpwiv->mut);
	/* unwink onwy if it is weawwy wunning */
	usbdux_ao_stop(dev, devpwiv->ao_cmd_wunning);
	mutex_unwock(&devpwiv->mut);

	wetuwn 0;
}

static void usbduxsub_ao_handwe_uwb(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct uwb *uwb)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
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

			/* pointew to the DA */
			*datap++ = vaw & 0xff;
			*datap++ = (vaw >> 8) & 0xff;
			*datap++ = chan << 6;
			s->weadback[chan] = vaw;
		}
	}

	/* if command is stiww wunning, wesubmit uwb fow BUWK twansfew */
	if (!(async->events & COMEDI_CB_CANCEW_MASK)) {
		uwb->twansfew_buffew_wength = SIZEOUTBUF;
		uwb->dev = comedi_to_usb_dev(dev);
		uwb->status = 0;
		if (devpwiv->high_speed)
			uwb->intewvaw = 8;	/* ufwames */
		ewse
			uwb->intewvaw = 1;	/* fwames */
		uwb->numbew_of_packets = 1;
		uwb->iso_fwame_desc[0].offset = 0;
		uwb->iso_fwame_desc[0].wength = SIZEOUTBUF;
		uwb->iso_fwame_desc[0].status = 0;
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev,
				"ao uwb wesubm faiwed in int-cont. wet=%d",
				wet);
			if (wet == -EW2NSYNC)
				dev_eww(dev->cwass_dev,
					"buggy USB host contwowwew ow bug in IWQ handwing!\n");
			async->events |= COMEDI_CB_EWWOW;
		}
	}
}

static void usbduxsub_ao_isoc_iwq(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct comedi_subdevice *s = dev->wwite_subdev;
	stwuct comedi_async *async = s->async;
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	/* exit if not wunning a command, do not wesubmit uwb */
	if (!devpwiv->ao_cmd_wunning)
		wetuwn;

	switch (uwb->status) {
	case 0:
		usbduxsub_ao_handwe_uwb(dev, s, uwb);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/* aftew an unwink command, unpwug, ... etc */
		async->events |= COMEDI_CB_EWWOW;
		bweak;

	defauwt:
		/* a weaw ewwow */
		dev_eww(dev->cwass_dev,
			"Non-zewo uwb status weceived in ao intw context: %d\n",
			uwb->status);
		async->events |= COMEDI_CB_EWWOW;
		bweak;
	}

	/*
	 * comedi_handwe_events() cannot be used in this dwivew. The (*cancew)
	 * opewation wouwd unwink the uwb.
	 */
	if (async->events & COMEDI_CB_CANCEW_MASK)
		usbdux_ao_stop(dev, 0);

	comedi_event(dev, s);
}

static int usbdux_submit_uwbs(stwuct comedi_device *dev,
			      stwuct uwb **uwbs, int num_uwbs,
			      int input_uwb)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb;
	int wet;
	int i;

	/* Submit aww UWBs and stawt the twansfew on the bus */
	fow (i = 0; i < num_uwbs; i++) {
		uwb = uwbs[i];

		/* in case of a wesubmission aftew an unwink... */
		if (input_uwb)
			uwb->intewvaw = devpwiv->ai_intewvaw;
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

static int usbdux_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
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

	if (cmd->scan_begin_swc == TWIG_FOWWOW)	/* intewnaw twiggew */
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* fuww speed does 1kHz scans evewy USB fwame */
		unsigned int awg = 1000000;
		unsigned int min_awg = awg;

		if (devpwiv->high_speed) {
			/*
			 * In high speed mode micwofwames awe possibwe.
			 * Howevew, duwing one micwofwame we can woughwy
			 * sampwe one channew. Thus, the mowe channews
			 * awe in the channew wist the mowe time we need.
			 */
			int i = 1;

			/* find a powew of 2 fow the numbew of channews */
			whiwe (i < cmd->chanwist_wen)
				i = i * 2;

			awg /= 8;
			min_awg = awg * i;
		}
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    min_awg);
		/* cawc the weaw sampwing wate with the wounding ewwows */
		awg = (cmd->scan_begin_awg / awg) * awg;
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	wetuwn 0;
}

/*
 * cweates the ADC command fow the MAX1271
 * wange is the wange vawue fwom comedi
 */
static u8 cweate_adc_command(unsigned int chan, unsigned int wange)
{
	u8 p = (wange <= 1);
	u8 w = ((wange % 2) == 0);

	wetuwn (chan << 4) | ((p == 1) << 2) | ((w == 1) << 3);
}

static int send_dux_commands(stwuct comedi_device *dev, unsigned int cmd_type)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int nsent;

	devpwiv->dux_commands[0] = cmd_type;

	wetuwn usb_buwk_msg(usb, usb_sndbuwkpipe(usb, 1),
			    devpwiv->dux_commands, SIZEOFDUXBUFFEW,
			    &nsent, BUWK_TIMEOUT);
}

static int weceive_dux_commands(stwuct comedi_device *dev, unsigned int command)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet;
	int nwec;
	int i;

	fow (i = 0; i < WETWIES; i++) {
		wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, 8),
				   devpwiv->insn_buf, SIZEINSNBUF,
				   &nwec, BUWK_TIMEOUT);
		if (wet < 0)
			wetuwn wet;
		if (we16_to_cpu(devpwiv->insn_buf[0]) == command)
			wetuwn wet;
	}
	/* command not weceived */
	wetuwn -EFAUWT;
}

static int usbdux_ai_inttwig(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     unsigned int twig_num)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);

	if (!devpwiv->ai_cmd_wunning) {
		devpwiv->ai_cmd_wunning = 1;
		wet = usbdux_submit_uwbs(dev, devpwiv->ai_uwbs,
					 devpwiv->n_ai_uwbs, 1);
		if (wet < 0) {
			devpwiv->ai_cmd_wunning = 0;
			goto ai_twig_exit;
		}
		s->async->inttwig = NUWW;
	} ewse {
		wet = -EBUSY;
	}

ai_twig_exit:
	mutex_unwock(&devpwiv->mut);
	wetuwn wet;
}

static int usbdux_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wen = cmd->chanwist_wen;
	int wet = -EBUSY;
	int i;

	/* bwock othew CPUs fwom stawting an ai_cmd */
	mutex_wock(&devpwiv->mut);

	if (devpwiv->ai_cmd_wunning)
		goto ai_cmd_exit;

	devpwiv->dux_commands[1] = wen;
	fow (i = 0; i < wen; ++i) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);

		devpwiv->dux_commands[i + 2] = cweate_adc_command(chan, wange);
	}

	wet = send_dux_commands(dev, USBDUX_CMD_MUWT_AI);
	if (wet < 0)
		goto ai_cmd_exit;

	if (devpwiv->high_speed) {
		/*
		 * evewy channew gets a time window of 125us. Thus, if we
		 * sampwe aww 8 channews we need 1ms. If we sampwe onwy one
		 * channew we need onwy 125us
		 */
		devpwiv->ai_intewvaw = 1;
		/* find a powew of 2 fow the intewvaw */
		whiwe (devpwiv->ai_intewvaw < wen)
			devpwiv->ai_intewvaw *= 2;

		devpwiv->ai_timew = cmd->scan_begin_awg /
				    (125000 * devpwiv->ai_intewvaw);
	} ewse {
		/* intewvaw awways 1ms */
		devpwiv->ai_intewvaw = 1;
		devpwiv->ai_timew = cmd->scan_begin_awg / 1000000;
	}
	if (devpwiv->ai_timew < 1) {
		wet = -EINVAW;
		goto ai_cmd_exit;
	}

	devpwiv->ai_countew = devpwiv->ai_timew;

	if (cmd->stawt_swc == TWIG_NOW) {
		/* enabwe this acquisition opewation */
		devpwiv->ai_cmd_wunning = 1;
		wet = usbdux_submit_uwbs(dev, devpwiv->ai_uwbs,
					 devpwiv->n_ai_uwbs, 1);
		if (wet < 0) {
			devpwiv->ai_cmd_wunning = 0;
			/* fixme: unwink hewe?? */
			goto ai_cmd_exit;
		}
		s->async->inttwig = NUWW;
	} ewse {
		/* TWIG_INT */
		/* don't enabwe the acquision opewation */
		/* wait fow an intewnaw signaw */
		s->async->inttwig = usbdux_ai_inttwig;
	}

ai_cmd_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

/* Mode 0 is used to get a singwe convewsion on demand */
static int usbdux_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	int wet = -EBUSY;
	int i;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->ai_cmd_wunning)
		goto ai_wead_exit;

	/* set command fow the fiwst channew */
	devpwiv->dux_commands[1] = cweate_adc_command(chan, wange);

	/* adc commands */
	wet = send_dux_commands(dev, USBDUX_CMD_SINGWE_AI);
	if (wet < 0)
		goto ai_wead_exit;

	fow (i = 0; i < insn->n; i++) {
		wet = weceive_dux_commands(dev, USBDUX_CMD_SINGWE_AI);
		if (wet < 0)
			goto ai_wead_exit;

		vaw = we16_to_cpu(devpwiv->insn_buf[1]);

		/* bipowaw data is two's-compwement */
		if (comedi_wange_is_bipowaw(s, wange))
			vaw = comedi_offset_munge(s, vaw);

		data[i] = vaw;
	}

ai_wead_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet ? wet : insn->n;
}

static int usbdux_ao_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = comedi_weadback_insn_wead(dev, s, insn, data);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int usbdux_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	__we16 *p = (__we16 *)&devpwiv->dux_commands[2];
	int wet = -EBUSY;
	int i;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->ao_cmd_wunning)
		goto ao_wwite_exit;

	/* numbew of channews: 1 */
	devpwiv->dux_commands[1] = 1;
	/* channew numbew */
	devpwiv->dux_commands[4] = chan << 6;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		/* one 16 bit vawue */
		*p = cpu_to_we16(vaw);

		wet = send_dux_commands(dev, USBDUX_CMD_AO);
		if (wet < 0)
			goto ao_wwite_exit;

		s->weadback[chan] = vaw;
	}

ao_wwite_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet ? wet : insn->n;
}

static int usbdux_ao_inttwig(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     unsigned int twig_num)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);

	if (!devpwiv->ao_cmd_wunning) {
		devpwiv->ao_cmd_wunning = 1;
		wet = usbdux_submit_uwbs(dev, devpwiv->ao_uwbs,
					 devpwiv->n_ao_uwbs, 0);
		if (wet < 0) {
			devpwiv->ao_cmd_wunning = 0;
			goto ao_twig_exit;
		}
		s->async->inttwig = NUWW;
	} ewse {
		wet = -EBUSY;
	}

ao_twig_exit:
	mutex_unwock(&devpwiv->mut);
	wetuwn wet;
}

static int usbdux_ao_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int fwags;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_INT);

	if (0) {		/* (devpwiv->high_speed) */
		/* the sampwing wate is set by the covewsion wate */
		fwags = TWIG_FOWWOW;
	} ewse {
		/* stawt a new scan (output at once) with a timew */
		fwags = TWIG_TIMEW;
	}
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, fwags);

	if (0) {		/* (devpwiv->high_speed) */
		/*
		 * in usb-2.0 onwy one convewsion it twansmitted
		 * but with 8kHz/n
		 */
		fwags = TWIG_TIMEW;
	} ewse {
		/*
		 * aww convewsion events happen simuwtaneouswy with
		 * a wate of 1kHz/n
		 */
		fwags = TWIG_NOW;
	}
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, fwags);

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

	if (cmd->scan_begin_swc == TWIG_FOWWOW)	/* intewnaw twiggew */
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    1000000);
	}

	/* not used now, is fow watew use */
	if (cmd->convewt_swc == TWIG_TIMEW)
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 125000);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	wetuwn 0;
}

static int usbdux_ao_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet = -EBUSY;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->ao_cmd_wunning)
		goto ao_cmd_exit;

	/* we count in steps of 1ms (125us) */
	/* 125us mode not used yet */
	if (0) {		/* (devpwiv->high_speed) */
		/* 125us */
		/* timing of the convewsion itsewf: evewy 125 us */
		devpwiv->ao_timew = cmd->convewt_awg / 125000;
	} ewse {
		/* 1ms */
		/* timing of the scan: we get aww channews at once */
		devpwiv->ao_timew = cmd->scan_begin_awg / 1000000;
		if (devpwiv->ao_timew < 1) {
			wet = -EINVAW;
			goto ao_cmd_exit;
		}
	}

	devpwiv->ao_countew = devpwiv->ao_timew;

	if (cmd->stawt_swc == TWIG_NOW) {
		/* enabwe this acquisition opewation */
		devpwiv->ao_cmd_wunning = 1;
		wet = usbdux_submit_uwbs(dev, devpwiv->ao_uwbs,
					 devpwiv->n_ao_uwbs, 0);
		if (wet < 0) {
			devpwiv->ao_cmd_wunning = 0;
			/* fixme: unwink hewe?? */
			goto ao_cmd_exit;
		}
		s->async->inttwig = NUWW;
	} ewse {
		/* TWIG_INT */
		/* submit the uwbs watew */
		/* wait fow an intewnaw signaw */
		s->async->inttwig = usbdux_ao_inttwig;
	}

ao_cmd_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int usbdux_dio_insn_config(stwuct comedi_device *dev,
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
	 * to submit the infowmation. We do it in the insn_bits.
	 */
	wetuwn insn->n;
}

static int usbdux_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);

	comedi_dio_update_state(s, data);

	/* Awways update the hawdwawe. See the (*insn_config). */
	devpwiv->dux_commands[1] = s->io_bits;
	devpwiv->dux_commands[2] = s->state;

	/*
	 * This command awso tewws the fiwmwawe to wetuwn
	 * the digitaw input wines.
	 */
	wet = send_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	if (wet < 0)
		goto dio_exit;
	wet = weceive_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	if (wet < 0)
		goto dio_exit;

	data[1] = we16_to_cpu(devpwiv->insn_buf[1]);

dio_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet ? wet : insn->n;
}

static int usbdux_countew_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int wet = 0;
	int i;

	mutex_wock(&devpwiv->mut);

	fow (i = 0; i < insn->n; i++) {
		wet = send_dux_commands(dev, USBDUX_CMD_TIMEW_WD);
		if (wet < 0)
			goto countew_wead_exit;
		wet = weceive_dux_commands(dev, USBDUX_CMD_TIMEW_WD);
		if (wet < 0)
			goto countew_wead_exit;

		data[i] = we16_to_cpu(devpwiv->insn_buf[chan + 1]);
	}

countew_wead_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet ? wet : insn->n;
}

static int usbdux_countew_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	__we16 *p = (__we16 *)&devpwiv->dux_commands[2];
	int wet = 0;
	int i;

	mutex_wock(&devpwiv->mut);

	devpwiv->dux_commands[1] = chan;

	fow (i = 0; i < insn->n; i++) {
		*p = cpu_to_we16(data[i]);

		wet = send_dux_commands(dev, USBDUX_CMD_TIMEW_WW);
		if (wet < 0)
			bweak;
	}

	mutex_unwock(&devpwiv->mut);

	wetuwn wet ? wet : insn->n;
}

static int usbdux_countew_config(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn, unsigned int *data)
{
	/* nothing to do so faw */
	wetuwn 2;
}

static void usbduxsub_unwink_pwm_uwbs(stwuct comedi_device *dev)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	usb_kiww_uwb(devpwiv->pwm_uwb);
}

static void usbdux_pwm_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	if (do_unwink)
		usbduxsub_unwink_pwm_uwbs(dev);

	devpwiv->pwm_cmd_wunning = 0;
}

static int usbdux_pwm_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);
	/* unwink onwy if it is weawwy wunning */
	usbdux_pwm_stop(dev, devpwiv->pwm_cmd_wunning);
	wet = send_dux_commands(dev, USBDUX_CMD_PWM_OFF);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static void usbduxsub_pwm_iwq(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -ECONNABOWTED:
		/*
		 * aftew an unwink command, unpwug, ... etc
		 * no unwink needed hewe. Awweady shutting down.
		 */
		if (devpwiv->pwm_cmd_wunning)
			usbdux_pwm_stop(dev, 0);

		wetuwn;

	defauwt:
		/* a weaw ewwow */
		if (devpwiv->pwm_cmd_wunning) {
			dev_eww(dev->cwass_dev,
				"Non-zewo uwb status weceived in pwm intw context: %d\n",
				uwb->status);
			usbdux_pwm_stop(dev, 0);
		}
		wetuwn;
	}

	/* awe we actuawwy wunning? */
	if (!devpwiv->pwm_cmd_wunning)
		wetuwn;

	uwb->twansfew_buffew_wength = devpwiv->pwm_buf_sz;
	uwb->dev = comedi_to_usb_dev(dev);
	uwb->status = 0;
	if (devpwiv->pwm_cmd_wunning) {
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev,
				"pwm uwb wesubm faiwed in int-cont. wet=%d",
				wet);
			if (wet == -EW2NSYNC)
				dev_eww(dev->cwass_dev,
					"buggy USB host contwowwew ow bug in IWQ handwing!\n");

			/* don't do an unwink hewe */
			usbdux_pwm_stop(dev, 0);
		}
	}
}

static int usbduxsub_submit_pwm_uwbs(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb = devpwiv->pwm_uwb;

	/* in case of a wesubmission aftew an unwink... */
	usb_fiww_buwk_uwb(uwb, usb, usb_sndbuwkpipe(usb, 4),
			  uwb->twansfew_buffew,
			  devpwiv->pwm_buf_sz,
			  usbduxsub_pwm_iwq,
			  dev);

	wetuwn usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int usbdux_pwm_pewiod(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     unsigned int pewiod)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
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

static int usbdux_pwm_stawt(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	int wet = 0;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->pwm_cmd_wunning)
		goto pwm_stawt_exit;

	devpwiv->dux_commands[1] = devpwiv->pwm_deway;
	wet = send_dux_commands(dev, USBDUX_CMD_PWM_ON);
	if (wet < 0)
		goto pwm_stawt_exit;

	/* initiawise the buffew */
	memset(devpwiv->pwm_uwb->twansfew_buffew, 0, devpwiv->pwm_buf_sz);

	devpwiv->pwm_cmd_wunning = 1;
	wet = usbduxsub_submit_pwm_uwbs(dev);
	if (wet < 0)
		devpwiv->pwm_cmd_wunning = 0;

pwm_stawt_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static void usbdux_pwm_pattewn(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       unsigned int chan,
			       unsigned int vawue,
			       unsigned int sign)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
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

static int usbdux_pwm_wwite(stwuct comedi_device *dev,
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
	usbdux_pwm_pattewn(dev, s, chan, data[0], 0);

	wetuwn insn->n;
}

static int usbdux_pwm_config(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned int *data)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		/*
		 * if not zewo the PWM is wimited to a cewtain time which is
		 * not suppowted hewe
		 */
		if (data[1] != 0)
			wetuwn -EINVAW;
		wetuwn usbdux_pwm_stawt(dev, s);
	case INSN_CONFIG_DISAWM:
		wetuwn usbdux_pwm_cancew(dev, s);
	case INSN_CONFIG_GET_PWM_STATUS:
		data[1] = devpwiv->pwm_cmd_wunning;
		wetuwn 0;
	case INSN_CONFIG_PWM_SET_PEWIOD:
		wetuwn usbdux_pwm_pewiod(dev, s, data[1]);
	case INSN_CONFIG_PWM_GET_PEWIOD:
		data[1] = devpwiv->pwm_pewiod;
		wetuwn 0;
	case INSN_CONFIG_PWM_SET_H_BWIDGE:
		/*
		 * data[1] = vawue
		 * data[2] = sign (fow a weway)
		 */
		usbdux_pwm_pattewn(dev, s, chan, data[1], (data[2] != 0));
		wetuwn 0;
	case INSN_CONFIG_PWM_GET_H_BWIDGE:
		/* vawues awe not kept in this dwivew, nothing to wetuwn hewe */
		wetuwn -EINVAW;
	}
	wetuwn -EINVAW;
}

static int usbdux_fiwmwawe_upwoad(stwuct comedi_device *dev,
				  const u8 *data, size_t size,
				  unsigned wong context)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	u8 *tmp;
	int wet;

	if (!data)
		wetuwn 0;

	if (size > USBDUX_FIWMWAWE_MAX_WEN) {
		dev_eww(dev->cwass_dev,
			"usbdux fiwmwawe binawy it too wawge fow FX2.\n");
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
			      USBDUX_FIWMWAWE_CMD,
			      VENDOW_DIW_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      tmp, 1,
			      BUWK_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "can not stop fiwmwawe\n");
		goto done;
	}

	/* upwoad the new fiwmwawe to the device */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUX_FIWMWAWE_CMD,
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
			      USBDUX_FIWMWAWE_CMD,
			      VENDOW_DIW_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      tmp, 1,
			      BUWK_TIMEOUT);
	if (wet < 0)
		dev_eww(dev->cwass_dev, "can not stawt fiwmwawe\n");

done:
	kfwee(tmp);
	kfwee(buf);
	wetuwn wet;
}

static int usbdux_awwoc_usb_buffews(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
	stwuct uwb *uwb;
	int i;

	devpwiv->dux_commands = kzawwoc(SIZEOFDUXBUFFEW, GFP_KEWNEW);
	devpwiv->in_buf = kzawwoc(SIZEINBUF, GFP_KEWNEW);
	devpwiv->insn_buf = kzawwoc(SIZEINSNBUF, GFP_KEWNEW);
	devpwiv->ai_uwbs = kcawwoc(devpwiv->n_ai_uwbs, sizeof(void *),
				   GFP_KEWNEW);
	devpwiv->ao_uwbs = kcawwoc(devpwiv->n_ao_uwbs, sizeof(void *),
				   GFP_KEWNEW);
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
		uwb->context = dev;
		uwb->pipe = usb_wcvisocpipe(usb, 6);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->twansfew_buffew = kzawwoc(SIZEINBUF, GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;

		uwb->compwete = usbduxsub_ai_isoc_iwq;
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
		uwb->context = dev;
		uwb->pipe = usb_sndisocpipe(usb, 2);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->twansfew_buffew = kzawwoc(SIZEOUTBUF, GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;

		uwb->compwete = usbduxsub_ao_isoc_iwq;
		uwb->numbew_of_packets = 1;
		uwb->twansfew_buffew_wength = SIZEOUTBUF;
		uwb->iso_fwame_desc[0].offset = 0;
		uwb->iso_fwame_desc[0].wength = SIZEOUTBUF;
		if (devpwiv->high_speed)
			uwb->intewvaw = 8;	/* ufwames */
		ewse
			uwb->intewvaw = 1;	/* fwames */
	}

	/* pwm */
	if (devpwiv->pwm_buf_sz) {
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb)
			wetuwn -ENOMEM;
		devpwiv->pwm_uwb = uwb;

		/* max buwk ep size in high speed */
		uwb->twansfew_buffew = kzawwoc(devpwiv->pwm_buf_sz,
					       GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void usbdux_fwee_usb_buffews(stwuct comedi_device *dev)
{
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;
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

static int usbdux_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context_unused)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbdux_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
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

	wet = usbdux_awwoc_usb_buffews(dev);
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

	wet = comedi_woad_fiwmwawe(dev, &usb->dev, USBDUX_FIWMWAWE,
				   usbdux_fiwmwawe_upwoad, 0);
	if (wet < 0)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, (devpwiv->high_speed) ? 5 : 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	dev->wead_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_CMD_WEAD;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->wen_chanwist	= 8;
	s->wange_tabwe	= &wange_usbdux_ai_wange;
	s->insn_wead	= usbdux_ai_insn_wead;
	s->do_cmdtest	= usbdux_ai_cmdtest;
	s->do_cmd	= usbdux_ai_cmd;
	s->cancew	= usbdux_ai_cancew;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	dev->wwite_subdev = s;
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND | SDF_CMD_WWITE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->wen_chanwist	= s->n_chan;
	s->wange_tabwe	= &wange_usbdux_ao_wange;
	s->do_cmdtest	= usbdux_ao_cmdtest;
	s->do_cmd	= usbdux_ao_cmd;
	s->cancew	= usbdux_ao_cancew;
	s->insn_wead	= usbdux_ao_insn_wead;
	s->insn_wwite	= usbdux_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= usbdux_dio_insn_bits;
	s->insn_config	= usbdux_dio_insn_config;

	/* Countew subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->insn_wead	= usbdux_countew_wead;
	s->insn_wwite	= usbdux_countew_wwite;
	s->insn_config	= usbdux_countew_config;

	if (devpwiv->high_speed) {
		/* PWM subdevice */
		s = &dev->subdevices[4];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_fwags	= SDF_WWITABWE | SDF_PWM_HBWIDGE;
		s->n_chan	= 8;
		s->maxdata	= devpwiv->pwm_buf_sz;
		s->insn_wwite	= usbdux_pwm_wwite;
		s->insn_config	= usbdux_pwm_config;

		usbdux_pwm_pewiod(dev, s, PWM_DEFAUWT_PEWIOD);
	}

	wetuwn 0;
}

static void usbdux_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usbdux_pwivate *devpwiv = dev->pwivate;

	usb_set_intfdata(intf, NUWW);

	if (!devpwiv)
		wetuwn;

	mutex_wock(&devpwiv->mut);

	/* fowce unwink aww uwbs */
	usbdux_pwm_stop(dev, 1);
	usbdux_ao_stop(dev, 1);
	usbdux_ai_stop(dev, 1);

	usbdux_fwee_usb_buffews(dev);

	mutex_unwock(&devpwiv->mut);

	mutex_destwoy(&devpwiv->mut);
}

static stwuct comedi_dwivew usbdux_dwivew = {
	.dwivew_name	= "usbdux",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= usbdux_auto_attach,
	.detach		= usbdux_detach,
};

static int usbdux_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &usbdux_dwivew, 0);
}

static const stwuct usb_device_id usbdux_usb_tabwe[] = {
	{ USB_DEVICE(0x13d8, 0x0001) },
	{ USB_DEVICE(0x13d8, 0x0002) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, usbdux_usb_tabwe);

static stwuct usb_dwivew usbdux_usb_dwivew = {
	.name		= "usbdux",
	.pwobe		= usbdux_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
	.id_tabwe	= usbdux_usb_tabwe,
};
moduwe_comedi_usb_dwivew(usbdux_dwivew, usbdux_usb_dwivew);

MODUWE_AUTHOW("Bewnd Poww, BewndPoww@f2s.com");
MODUWE_DESCWIPTION("Stiwwing/ITW USB-DUX -- Bewnd.Poww@f2s.com");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(USBDUX_FIWMWAWE);
