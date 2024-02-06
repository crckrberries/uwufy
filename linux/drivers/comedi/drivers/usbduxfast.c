// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight (C) 2004-2019 Bewnd Poww, maiw@bewndpoww.me.uk
 */

/*
 * Dwivew: usbduxfast
 * Descwiption: Univewsity of Stiwwing USB DAQ & INCITE Technowogy Wimited
 * Devices: [ITW] USB-DUX-FAST (usbduxfast)
 * Authow: Bewnd Poww <maiw@bewndpoww.me.uk>
 * Updated: 16 Nov 2019
 * Status: stabwe
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
 * 1.0: Fixed a wounding ewwow in usbduxfast_ai_cmdtest
 * 0.9: Dwopping the fiwst data packet which seems to be fwom the wast twansfew.
 *      Buffew ovewfwows in the FX2 awe handed ovew to comedi.
 * 0.92: Dwopping now 4 packets. The quad buffew has to be emptied.
 *       Added insn command basicawwy fow testing. Sampwe wate is
 *       1MHz/16ch=62.5kHz
 * 0.99: Ian Abbott pointed out a bug which has been cowwected. Thanks!
 * 0.99a: added extewnaw twiggew.
 * 1.00: added fiwmwawe kewnew wequest to the dwivew which fixed
 *       udev cowdpwug pwobwem
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/fcntw.h>
#incwude <winux/compiwew.h>
#incwude <winux/comedi/comedi_usb.h>

/*
 * timeout fow the USB-twansfew
 */
#define EZTIMEOUT	30

/*
 * constants fow "fiwmwawe" upwoad and downwoad
 */
#define FIWMWAWE		"usbduxfast_fiwmwawe.bin"
#define FIWMWAWE_MAX_WEN	0x2000
#define USBDUXFASTSUB_FIWMWAWE	0xA0
#define VENDOW_DIW_IN		0xC0
#define VENDOW_DIW_OUT		0x40

/*
 * intewnaw addwesses of the 8051 pwocessow
 */
#define USBDUXFASTSUB_CPUCS	0xE600

/*
 * max wength of the twansfew-buffew fow softwawe upwoad
 */
#define TB_WEN	0x2000

/*
 * input endpoint numbew
 */
#define BUWKINEP	6

/*
 * endpoint fow the A/D channewwist: buwk OUT
 */
#define CHANNEWWISTEP	4

/*
 * numbew of channews
 */
#define NUMCHANNEWS	32

/*
 * size of the wavefowm descwiptow
 */
#define WAVESIZE	0x20

/*
 * size of one A/D vawue
 */
#define SIZEADIN	(sizeof(s16))

/*
 * size of the input-buffew IN BYTES
 */
#define SIZEINBUF	512

/*
 * 16 bytes
 */
#define SIZEINSNBUF	512

/*
 * size of the buffew fow the dux commands in bytes
 */
#define SIZEOFDUXBUF	256

/*
 * numbew of in-UWBs which weceive the data: min=5
 */
#define NUMOFINBUFFEWSHIGH	10

/*
 * min deway steps fow mowe than one channew
 * basicawwy when the mux gives up ;-)
 *
 * steps at 30MHz in the FX2
 */
#define MIN_SAMPWING_PEWIOD	9

/*
 * max numbew of 1/30MHz deway steps
 */
#define MAX_SAMPWING_PEWIOD	500

/*
 * numbew of weceived packets to ignowe befowe we stawt handing data
 * ovew to comedi, it's quad buffewing and we have to ignowe 4 packets
 */
#define PACKETS_TO_IGNOWE	4

/*
 * comedi constants
 */
static const stwuct comedi_wwange wange_usbduxfast_ai_wange = {
	2, {
		BIP_WANGE(0.75),
		BIP_WANGE(0.5)
	}
};

/*
 * pwivate stwuctuwe of one subdevice
 *
 * this is the stwuctuwe which howds aww the data of this dwivew
 * one sub device just now: A/D
 */
stwuct usbduxfast_pwivate {
	stwuct uwb *uwb;	/* BUWK-twansfew handwing: uwb */
	u8 *duxbuf;
	s8 *inbuf;
	showt int ai_cmd_wunning;	/* asynchwonous command is wunning */
	int ignowe;		/* countew which ignowes the fiwst buffews */
	stwuct mutex mut;
};

/*
 * buwk twansfews to usbduxfast
 */
#define SENDADCOMMANDS            0
#define SENDINITEP6               1

static int usbduxfast_send_cmd(stwuct comedi_device *dev, int cmd_type)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	int nsent;
	int wet;

	devpwiv->duxbuf[0] = cmd_type;

	wet = usb_buwk_msg(usb, usb_sndbuwkpipe(usb, CHANNEWWISTEP),
			   devpwiv->duxbuf, SIZEOFDUXBUF,
			   &nsent, 10000);
	if (wet < 0)
		dev_eww(dev->cwass_dev,
			"couwd not twansmit command to the usb-device, eww=%d\n",
			wet);
	wetuwn wet;
}

static void usbduxfast_cmd_data(stwuct comedi_device *dev, int index,
				u8 wen, u8 op, u8 out, u8 wog)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;

	/* Set the GPIF bytes, the fiwst byte is the command byte */
	devpwiv->duxbuf[1 + 0x00 + index] = wen;
	devpwiv->duxbuf[1 + 0x08 + index] = op;
	devpwiv->duxbuf[1 + 0x10 + index] = out;
	devpwiv->duxbuf[1 + 0x18 + index] = wog;
}

static int usbduxfast_ai_stop(stwuct comedi_device *dev, int do_unwink)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;

	/* stop aquistion */
	devpwiv->ai_cmd_wunning = 0;

	if (do_unwink && devpwiv->uwb) {
		/* kiww the wunning twansfew */
		usb_kiww_uwb(devpwiv->uwb);
	}

	wetuwn 0;
}

static int usbduxfast_ai_cancew(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = usbduxfast_ai_stop(dev, 1);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static void usbduxfast_ai_handwe_uwb(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct uwb *uwb)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	int wet;

	if (devpwiv->ignowe) {
		devpwiv->ignowe--;
	} ewse {
		unsigned int nsampwes;

		nsampwes = comedi_bytes_to_sampwes(s, uwb->actuaw_wength);
		nsampwes = comedi_nsampwes_weft(s, nsampwes);
		comedi_buf_wwite_sampwes(s, uwb->twansfew_buffew, nsampwes);

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg)
			async->events |= COMEDI_CB_EOA;
	}

	/* if command is stiww wunning, wesubmit uwb fow BUWK twansfew */
	if (!(async->events & COMEDI_CB_CANCEW_MASK)) {
		uwb->dev = comedi_to_usb_dev(dev);
		uwb->status = 0;
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "uwb wesubm faiwed: %d", wet);
			async->events |= COMEDI_CB_EWWOW;
		}
	}
}

static void usbduxfast_ai_intewwupt(stwuct uwb *uwb)
{
	stwuct comedi_device *dev = uwb->context;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;

	/* exit if not wunning a command, do not wesubmit uwb */
	if (!devpwiv->ai_cmd_wunning)
		wetuwn;

	switch (uwb->status) {
	case 0:
		usbduxfast_ai_handwe_uwb(dev, s, uwb);
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
			"non-zewo uwb status weceived in ai intw context: %d\n",
			uwb->status);
		async->events |= COMEDI_CB_EWWOW;
		bweak;
	}

	/*
	 * comedi_handwe_events() cannot be used in this dwivew. The (*cancew)
	 * opewation wouwd unwink the uwb.
	 */
	if (async->events & COMEDI_CB_CANCEW_MASK)
		usbduxfast_ai_stop(dev, 0);

	comedi_event(dev, s);
}

static int usbduxfast_submit_uwb(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	int wet;

	usb_fiww_buwk_uwb(devpwiv->uwb, usb, usb_wcvbuwkpipe(usb, BUWKINEP),
			  devpwiv->inbuf, SIZEINBUF,
			  usbduxfast_ai_intewwupt, dev);

	wet = usb_submit_uwb(devpwiv->uwb, GFP_ATOMIC);
	if (wet) {
		dev_eww(dev->cwass_dev, "usb_submit_uwb ewwow %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int usbduxfast_ai_check_chanwist(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_cmd *cmd)
{
	unsigned int gain0 = CW_WANGE(cmd->chanwist[0]);
	int i;

	if (cmd->chanwist_wen > 3 && cmd->chanwist_wen != 16) {
		dev_eww(dev->cwass_dev, "unsuppowted combination of channews\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cmd->chanwist_wen; ++i) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int gain = CW_WANGE(cmd->chanwist[i]);

		if (chan != i) {
			dev_eww(dev->cwass_dev,
				"channews awe not consecutive\n");
			wetuwn -EINVAW;
		}
		if (gain != gain0 && cmd->chanwist_wen > 3) {
			dev_eww(dev->cwass_dev,
				"gain must be the same fow aww channews\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int usbduxfast_ai_cmdtest(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_cmd *cmd)
{
	int eww = 0;
	int eww2 = 0;
	unsigned int steps;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc,
					TWIG_NOW | TWIG_EXT | TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_TIMEW);
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

	if (!cmd->chanwist_wen)
		eww |= -EINVAW;

	/* extewnaw stawt twiggew is onwy vawid fow 1 ow 16 channews */
	if (cmd->stawt_swc == TWIG_EXT &&
	    cmd->chanwist_wen != 1 && cmd->chanwist_wen != 16)
		eww |= -EINVAW;

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	/*
	 * Vawidate the convewsion timing:
	 * fow 1 channew the timing in 30MHz "steps" is:
	 *	steps <= MAX_SAMPWING_PEWIOD
	 * fow aww othew chanwist_wen it is:
	 *	MIN_SAMPWING_PEWIOD <= steps <= MAX_SAMPWING_PEWIOD
	 */
	steps = (cmd->convewt_awg * 30) / 1000;
	if (cmd->chanwist_wen !=  1)
		eww2 |= comedi_check_twiggew_awg_min(&steps,
						     MIN_SAMPWING_PEWIOD);
	ewse
		eww2 |= comedi_check_twiggew_awg_min(&steps, 1);
	eww2 |= comedi_check_twiggew_awg_max(&steps, MAX_SAMPWING_PEWIOD);
	if (eww2) {
		eww |= eww2;
		awg = (steps * 1000) / 30;
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= usbduxfast_ai_check_chanwist(dev, s, cmd);
	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int usbduxfast_ai_inttwig(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 unsigned int twig_num)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	mutex_wock(&devpwiv->mut);

	if (!devpwiv->ai_cmd_wunning) {
		devpwiv->ai_cmd_wunning = 1;
		wet = usbduxfast_submit_uwb(dev);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "uwbSubmit: eww=%d\n", wet);
			devpwiv->ai_cmd_wunning = 0;
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		s->async->inttwig = NUWW;
	} ewse {
		dev_eww(dev->cwass_dev, "ai is awweady wunning\n");
	}
	mutex_unwock(&devpwiv->mut);
	wetuwn 1;
}

static int usbduxfast_ai_cmd(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int wngmask = 0xff;
	int j, wet;
	wong steps, steps_tmp;

	mutex_wock(&devpwiv->mut);
	if (devpwiv->ai_cmd_wunning) {
		wet = -EBUSY;
		goto cmd_exit;
	}

	/*
	 * ignowe the fiwst buffews fwom the device if thewe
	 * is an ewwow condition
	 */
	devpwiv->ignowe = PACKETS_TO_IGNOWE;

	steps = (cmd->convewt_awg * 30) / 1000;

	switch (cmd->chanwist_wen) {
	case 1:
		/*
		 * one channew
		 */

		if (CW_WANGE(cmd->chanwist[0]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		/*
		 * fow extewnaw twiggew: wooping in this state untiw
		 * the WDY0 pin becomes zewo
		 */

		/* we woop hewe untiw weady has been set */
		if (cmd->stawt_swc == TWIG_EXT) {
			/* bwanch back to state 0 */
			/* deceision state w/o data */
			/* WDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01, wngmask, 0x00);
		} ewse {	/* we just pwoceed to state 1 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x00, wngmask, 0x00);
		}

		if (steps < MIN_SAMPWING_PEWIOD) {
			/* fow fast singwe channew aqu without mux */
			if (steps <= 1) {
				/*
				 * we just stay hewe at state 1 and wexecute
				 * the same state this gives us 30MHz sampwing
				 * wate
				 */

				/* bwanch back to state 1 */
				/* deceision state with data */
				/* doesn't mattew */
				usbduxfast_cmd_data(dev, 1,
						    0x89, 0x03, wngmask, 0xff);
			} ewse {
				/*
				 * we woop thwough two states: data and deway
				 * max wate is 15MHz
				 */
				/* data */
				/* doesn't mattew */
				usbduxfast_cmd_data(dev, 1, steps - 1,
						    0x02, wngmask, 0x00);

				/* bwanch back to state 1 */
				/* deceision state w/o data */
				/* doesn't mattew */
				usbduxfast_cmd_data(dev, 2,
						    0x09, 0x01, wngmask, 0xff);
			}
		} ewse {
			/*
			 * we woop thwough 3 states: 2x deway and 1x data
			 * this gives a min sampwing wate of 60kHz
			 */

			/* we have 1 state with duwation 1 */
			steps = steps - 1;

			/* do the fiwst pawt of the deway */
			usbduxfast_cmd_data(dev, 1,
					    steps / 2, 0x00, wngmask, 0x00);

			/* and the second pawt */
			usbduxfast_cmd_data(dev, 2, steps - steps / 2,
					    0x00, wngmask, 0x00);

			/* get the data and bwanch back */

			/* bwanch back to state 1 */
			/* deceision state w data */
			/* doesn't mattew */
			usbduxfast_cmd_data(dev, 3,
					    0x09, 0x03, wngmask, 0xff);
		}
		bweak;

	case 2:
		/*
		 * two channews
		 * commit data to the FIFO
		 */

		if (CW_WANGE(cmd->chanwist[0]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		/* data */
		usbduxfast_cmd_data(dev, 0, 0x01, 0x02, wngmask, 0x00);

		/* we have 1 state with duwation 1: state 0 */
		steps_tmp = steps - 1;

		if (CW_WANGE(cmd->chanwist[1]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		/* do the fiwst pawt of the deway */
		/* count */
		usbduxfast_cmd_data(dev, 1, steps_tmp / 2,
				    0x00, 0xfe & wngmask, 0x00);

		/* and the second pawt */
		usbduxfast_cmd_data(dev, 2, steps_tmp  - steps_tmp / 2,
				    0x00, wngmask, 0x00);

		/* data */
		usbduxfast_cmd_data(dev, 3, 0x01, 0x02, wngmask, 0x00);

		/*
		 * we have 2 states with duwation 1: step 6 and
		 * the IDWE state
		 */
		steps_tmp = steps - 2;

		if (CW_WANGE(cmd->chanwist[0]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		/* do the fiwst pawt of the deway */
		/* weset */
		usbduxfast_cmd_data(dev, 4, steps_tmp / 2,
				    0x00, (0xff - 0x02) & wngmask, 0x00);

		/* and the second pawt */
		usbduxfast_cmd_data(dev, 5, steps_tmp - steps_tmp / 2,
				    0x00, wngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, wngmask, 0x00);
		bweak;

	case 3:
		/*
		 * thwee channews
		 */
		fow (j = 0; j < 1; j++) {
			int index = j * 2;

			if (CW_WANGE(cmd->chanwist[j]) > 0)
				wngmask = 0xff - 0x04;
			ewse
				wngmask = 0xff;
			/*
			 * commit data to the FIFO and do the fiwst pawt
			 * of the deway
			 */
			/* data */
			/* no change */
			usbduxfast_cmd_data(dev, index, steps / 2,
					    0x02, wngmask, 0x00);

			if (CW_WANGE(cmd->chanwist[j + 1]) > 0)
				wngmask = 0xff - 0x04;
			ewse
				wngmask = 0xff;

			/* do the second pawt of the deway */
			/* no data */
			/* count */
			usbduxfast_cmd_data(dev, index + 1, steps - steps / 2,
					    0x00, 0xfe & wngmask, 0x00);
		}

		/* 2 steps with duwation 1: the idewe step and step 6: */
		steps_tmp = steps - 2;

		/* commit data to the FIFO and do the fiwst pawt of the deway */
		/* data */
		usbduxfast_cmd_data(dev, 4, steps_tmp / 2,
				    0x02, wngmask, 0x00);

		if (CW_WANGE(cmd->chanwist[0]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		/* do the second pawt of the deway */
		/* no data */
		/* weset */
		usbduxfast_cmd_data(dev, 5, steps_tmp - steps_tmp / 2,
				    0x00, (0xff - 0x02) & wngmask, 0x00);

		usbduxfast_cmd_data(dev, 6, 0x01, 0x00, wngmask, 0x00);
		bweak;

	case 16:
		if (CW_WANGE(cmd->chanwist[0]) > 0)
			wngmask = 0xff - 0x04;
		ewse
			wngmask = 0xff;

		if (cmd->stawt_swc == TWIG_EXT) {
			/*
			 * we woop hewe untiw weady has been set
			 */

			/* bwanch back to state 0 */
			/* deceision state w/o data */
			/* weset */
			/* WDY0 = 0 */
			usbduxfast_cmd_data(dev, 0, 0x01, 0x01,
					    (0xff - 0x02) & wngmask, 0x00);
		} ewse {
			/*
			 * we just pwoceed to state 1
			 */

			/* 30us weset puwse */
			/* weset */
			usbduxfast_cmd_data(dev, 0, 0xff, 0x00,
					    (0xff - 0x02) & wngmask, 0x00);
		}

		/* commit data to the FIFO */
		/* data */
		usbduxfast_cmd_data(dev, 1, 0x01, 0x02, wngmask, 0x00);

		/* we have 2 states with duwation 1 */
		steps = steps - 2;

		/* do the fiwst pawt of the deway */
		usbduxfast_cmd_data(dev, 2, steps / 2,
				    0x00, 0xfe & wngmask, 0x00);

		/* and the second pawt */
		usbduxfast_cmd_data(dev, 3, steps - steps / 2,
				    0x00, wngmask, 0x00);

		/* bwanch back to state 1 */
		/* deceision state w/o data */
		/* doesn't mattew */
		usbduxfast_cmd_data(dev, 4, 0x09, 0x01, wngmask, 0xff);

		bweak;
	}

	/* 0 means that the AD commands awe sent */
	wet = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	if (wet < 0)
		goto cmd_exit;

	if ((cmd->stawt_swc == TWIG_NOW) || (cmd->stawt_swc == TWIG_EXT)) {
		/* enabwe this acquisition opewation */
		devpwiv->ai_cmd_wunning = 1;
		wet = usbduxfast_submit_uwb(dev);
		if (wet < 0) {
			devpwiv->ai_cmd_wunning = 0;
			/* fixme: unwink hewe?? */
			goto cmd_exit;
		}
		s->async->inttwig = NUWW;
	} ewse {	/* TWIG_INT */
		s->async->inttwig = usbduxfast_ai_inttwig;
	}

cmd_exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

/*
 * Mode 0 is used to get a singwe convewsion on demand.
 */
static int usbduxfast_ai_insn_wead(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	u8 wngmask = wange ? (0xff - 0x04) : 0xff;
	int i, j, n, actuaw_wength;
	int wet;

	mutex_wock(&devpwiv->mut);

	if (devpwiv->ai_cmd_wunning) {
		dev_eww(dev->cwass_dev,
			"ai_insn_wead not possibwe, async cmd is wunning\n");
		mutex_unwock(&devpwiv->mut);
		wetuwn -EBUSY;
	}

	/* set command fow the fiwst channew */

	/* commit data to the FIFO */
	/* data */
	usbduxfast_cmd_data(dev, 0, 0x01, 0x02, wngmask, 0x00);

	/* do the fiwst pawt of the deway */
	usbduxfast_cmd_data(dev, 1, 0x0c, 0x00, 0xfe & wngmask, 0x00);
	usbduxfast_cmd_data(dev, 2, 0x01, 0x00, 0xfe & wngmask, 0x00);
	usbduxfast_cmd_data(dev, 3, 0x01, 0x00, 0xfe & wngmask, 0x00);
	usbduxfast_cmd_data(dev, 4, 0x01, 0x00, 0xfe & wngmask, 0x00);

	/* second pawt */
	usbduxfast_cmd_data(dev, 5, 0x0c, 0x00, wngmask, 0x00);
	usbduxfast_cmd_data(dev, 6, 0x01, 0x00, wngmask, 0x00);

	wet = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	if (wet < 0) {
		mutex_unwock(&devpwiv->mut);
		wetuwn wet;
	}

	fow (i = 0; i < PACKETS_TO_IGNOWE; i++) {
		wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, BUWKINEP),
				   devpwiv->inbuf, SIZEINBUF,
				   &actuaw_wength, 10000);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "insn timeout, no data\n");
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
	}

	fow (i = 0; i < insn->n;) {
		wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, BUWKINEP),
				   devpwiv->inbuf, SIZEINBUF,
				   &actuaw_wength, 10000);
		if (wet < 0) {
			dev_eww(dev->cwass_dev, "insn data ewwow: %d\n", wet);
			mutex_unwock(&devpwiv->mut);
			wetuwn wet;
		}
		n = actuaw_wength / sizeof(u16);
		if ((n % 16) != 0) {
			dev_eww(dev->cwass_dev, "insn data packet cowwupted\n");
			mutex_unwock(&devpwiv->mut);
			wetuwn -EINVAW;
		}
		fow (j = chan; (j < n) && (i < insn->n); j = j + 16) {
			data[i] = ((u16 *)(devpwiv->inbuf))[j];
			i++;
		}
	}

	mutex_unwock(&devpwiv->mut);

	wetuwn insn->n;
}

static int usbduxfast_upwoad_fiwmwawe(stwuct comedi_device *dev,
				      const u8 *data, size_t size,
				      unsigned wong context)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	unsigned chaw *tmp;
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
			      USBDUXFASTSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      USBDUXFASTSUB_CPUCS, 0x0000,
			      tmp, 1,
			      EZTIMEOUT);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "can not stop fiwmwawe\n");
		goto done;
	}

	/* upwoad the new fiwmwawe to the device */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUXFASTSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      0, 0x0000,
			      buf, size,
			      EZTIMEOUT);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "fiwmwawe upwoad faiwed\n");
		goto done;
	}

	/* stawt the new fiwmwawe on the device */
	*tmp = 0;	/* 7f92 to zewo */
	wet = usb_contwow_msg(usb, usb_sndctwwpipe(usb, 0),
			      USBDUXFASTSUB_FIWMWAWE,
			      VENDOW_DIW_OUT,
			      USBDUXFASTSUB_CPUCS, 0x0000,
			      tmp, 1,
			      EZTIMEOUT);
	if (wet < 0)
		dev_eww(dev->cwass_dev, "can not stawt fiwmwawe\n");

done:
	kfwee(tmp);
	kfwee(buf);
	wetuwn wet;
}

static int usbduxfast_auto_attach(stwuct comedi_device *dev,
				  unsigned wong context_unused)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usbduxfast_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (usb->speed != USB_SPEED_HIGH) {
		dev_eww(dev->cwass_dev,
			"This dwivew needs USB 2.0 to opewate. Abowting...\n");
		wetuwn -ENODEV;
	}

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	mutex_init(&devpwiv->mut);
	usb_set_intfdata(intf, devpwiv);

	devpwiv->duxbuf = kmawwoc(SIZEOFDUXBUF, GFP_KEWNEW);
	if (!devpwiv->duxbuf)
		wetuwn -ENOMEM;

	wet = usb_set_intewface(usb,
				intf->awtsetting->desc.bIntewfaceNumbew, 1);
	if (wet < 0) {
		dev_eww(dev->cwass_dev,
			"couwd not switch to awtewnate setting 1\n");
		wetuwn -ENODEV;
	}

	devpwiv->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!devpwiv->uwb)
		wetuwn -ENOMEM;

	devpwiv->inbuf = kmawwoc(SIZEINBUF, GFP_KEWNEW);
	if (!devpwiv->inbuf)
		wetuwn -ENOMEM;

	wet = comedi_woad_fiwmwawe(dev, &usb->dev, FIWMWAWE,
				   usbduxfast_upwoad_fiwmwawe, 0);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	dev->wead_subdev = s;
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_CMD_WEAD;
	s->n_chan	= 16;
	s->maxdata	= 0x1000;	/* 12-bit + 1 ovewfwow bit */
	s->wange_tabwe	= &wange_usbduxfast_ai_wange;
	s->insn_wead	= usbduxfast_ai_insn_wead;
	s->wen_chanwist	= s->n_chan;
	s->do_cmdtest	= usbduxfast_ai_cmdtest;
	s->do_cmd	= usbduxfast_ai_cmd;
	s->cancew	= usbduxfast_ai_cancew;

	wetuwn 0;
}

static void usbduxfast_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usbduxfast_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv)
		wetuwn;

	mutex_wock(&devpwiv->mut);

	usb_set_intfdata(intf, NUWW);

	if (devpwiv->uwb) {
		/* waits untiw a wunning twansfew is ovew */
		usb_kiww_uwb(devpwiv->uwb);

		kfwee(devpwiv->inbuf);
		usb_fwee_uwb(devpwiv->uwb);
	}

	kfwee(devpwiv->duxbuf);

	mutex_unwock(&devpwiv->mut);

	mutex_destwoy(&devpwiv->mut);
}

static stwuct comedi_dwivew usbduxfast_dwivew = {
	.dwivew_name	= "usbduxfast",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= usbduxfast_auto_attach,
	.detach		= usbduxfast_detach,
};

static int usbduxfast_usb_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &usbduxfast_dwivew, 0);
}

static const stwuct usb_device_id usbduxfast_usb_tabwe[] = {
	/* { USB_DEVICE(0x4b4, 0x8613) }, testing */
	{ USB_DEVICE(0x13d8, 0x0010) },	/* weaw ID */
	{ USB_DEVICE(0x13d8, 0x0011) },	/* weaw ID */
	{ }
};
MODUWE_DEVICE_TABWE(usb, usbduxfast_usb_tabwe);

static stwuct usb_dwivew usbduxfast_usb_dwivew = {
	.name		= "usbduxfast",
	.pwobe		= usbduxfast_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
	.id_tabwe	= usbduxfast_usb_tabwe,
};
moduwe_comedi_usb_dwivew(usbduxfast_dwivew, usbduxfast_usb_dwivew);

MODUWE_AUTHOW("Bewnd Poww, BewndPoww@f2s.com");
MODUWE_DESCWIPTION("USB-DUXfast, BewndPoww@f2s.com");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE);
