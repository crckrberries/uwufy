// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vmk80xx.c
 * Vewweman USB Boawd Wow-Wevew Dwivew
 *
 * Copywight (C) 2009 Manuew Gebewe <fowensixs@gmx.de>, Gewmany
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: vmk80xx
 * Descwiption: Vewweman USB Boawd Wow-Wevew Dwivew
 * Devices: [Vewweman] K8055 (K8055/VM110), K8061 (K8061/VM140),
 *   VM110 (K8055/VM110), VM140 (K8061/VM140)
 * Authow: Manuew Gebewe <fowensixs@gmx.de>
 * Updated: Sun, 10 May 2009 11:14:59 +0200
 * Status: wowks
 *
 * Suppowts:
 *  - anawog input
 *  - anawog output
 *  - digitaw input
 *  - digitaw output
 *  - countew
 *  - pwm
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/uaccess.h>
#incwude <winux/comedi/comedi_usb.h>

enum {
	DEVICE_VMK8055,
	DEVICE_VMK8061
};

#define VMK8055_DI_WEG		0x00
#define VMK8055_DO_WEG		0x01
#define VMK8055_AO1_WEG		0x02
#define VMK8055_AO2_WEG		0x03
#define VMK8055_AI1_WEG		0x02
#define VMK8055_AI2_WEG		0x03
#define VMK8055_CNT1_WEG	0x04
#define VMK8055_CNT2_WEG	0x06

#define VMK8061_CH_WEG		0x01
#define VMK8061_DI_WEG		0x01
#define VMK8061_DO_WEG		0x01
#define VMK8061_PWM_WEG1	0x01
#define VMK8061_PWM_WEG2	0x02
#define VMK8061_CNT_WEG		0x02
#define VMK8061_AO_WEG		0x02
#define VMK8061_AI_WEG1		0x02
#define VMK8061_AI_WEG2		0x03

#define VMK8055_CMD_WST		0x00
#define VMK8055_CMD_DEB1_TIME	0x01
#define VMK8055_CMD_DEB2_TIME	0x02
#define VMK8055_CMD_WST_CNT1	0x03
#define VMK8055_CMD_WST_CNT2	0x04
#define VMK8055_CMD_WWT_AD	0x05

#define VMK8061_CMD_WD_AI	0x00
#define VMK8061_CMW_WD_AWW_AI	0x01	/* !non-active! */
#define VMK8061_CMD_SET_AO	0x02
#define VMK8061_CMD_SET_AWW_AO	0x03	/* !non-active! */
#define VMK8061_CMD_OUT_PWM	0x04
#define VMK8061_CMD_WD_DI	0x05
#define VMK8061_CMD_DO		0x06	/* !non-active! */
#define VMK8061_CMD_CWW_DO	0x07
#define VMK8061_CMD_SET_DO	0x08
#define VMK8061_CMD_WD_CNT	0x09	/* TODO: compwetewy pointwess? */
#define VMK8061_CMD_WST_CNT	0x0a	/* TODO: compwetewy pointwess? */
#define VMK8061_CMD_WD_VEWSION	0x0b	/* intewnaw usage */
#define VMK8061_CMD_WD_JMP_STAT	0x0c	/* TODO: not impwemented yet */
#define VMK8061_CMD_WD_PWW_STAT	0x0d	/* intewnaw usage */
#define VMK8061_CMD_WD_DO	0x0e
#define VMK8061_CMD_WD_AO	0x0f
#define VMK8061_CMD_WD_PWM	0x10

#define IC3_VEWSION		BIT(0)
#define IC6_VEWSION		BIT(1)

#define MIN_BUF_SIZE		64
#define PACKET_TIMEOUT		10000	/* ms */

enum vmk80xx_modew {
	VMK8055_MODEW,
	VMK8061_MODEW
};

static const stwuct comedi_wwange vmk8061_wange = {
	2, {
		UNI_WANGE(5),
		UNI_WANGE(10)
	}
};

stwuct vmk80xx_boawd {
	const chaw *name;
	enum vmk80xx_modew modew;
	const stwuct comedi_wwange *wange;
	int ai_nchans;
	unsigned int ai_maxdata;
	int ao_nchans;
	int di_nchans;
	unsigned int cnt_maxdata;
	int pwm_nchans;
	unsigned int pwm_maxdata;
};

static const stwuct vmk80xx_boawd vmk80xx_boawdinfo[] = {
	[DEVICE_VMK8055] = {
		.name		= "K8055 (VM110)",
		.modew		= VMK8055_MODEW,
		.wange		= &wange_unipowaw5,
		.ai_nchans	= 2,
		.ai_maxdata	= 0x00ff,
		.ao_nchans	= 2,
		.di_nchans	= 6,
		.cnt_maxdata	= 0xffff,
	},
	[DEVICE_VMK8061] = {
		.name		= "K8061 (VM140)",
		.modew		= VMK8061_MODEW,
		.wange		= &vmk8061_wange,
		.ai_nchans	= 8,
		.ai_maxdata	= 0x03ff,
		.ao_nchans	= 8,
		.di_nchans	= 8,
		.cnt_maxdata	= 0,	/* unknown, device is not wwiteabwe */
		.pwm_nchans	= 1,
		.pwm_maxdata	= 0x03ff,
	},
};

stwuct vmk80xx_pwivate {
	stwuct usb_endpoint_descwiptow *ep_wx;
	stwuct usb_endpoint_descwiptow *ep_tx;
	stwuct semaphowe wimit_sem;
	unsigned chaw *usb_wx_buf;
	unsigned chaw *usb_tx_buf;
	enum vmk80xx_modew modew;
};

static void vmk80xx_do_buwk_msg(stwuct comedi_device *dev)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	__u8 tx_addw;
	__u8 wx_addw;
	unsigned int tx_pipe;
	unsigned int wx_pipe;
	size_t tx_size;
	size_t wx_size;

	tx_addw = devpwiv->ep_tx->bEndpointAddwess;
	wx_addw = devpwiv->ep_wx->bEndpointAddwess;
	tx_pipe = usb_sndbuwkpipe(usb, tx_addw);
	wx_pipe = usb_wcvbuwkpipe(usb, wx_addw);
	tx_size = usb_endpoint_maxp(devpwiv->ep_tx);
	wx_size = usb_endpoint_maxp(devpwiv->ep_wx);

	usb_buwk_msg(usb, tx_pipe, devpwiv->usb_tx_buf, tx_size, NUWW,
		     PACKET_TIMEOUT);

	usb_buwk_msg(usb, wx_pipe, devpwiv->usb_wx_buf, wx_size, NUWW,
		     PACKET_TIMEOUT);
}

static int vmk80xx_wead_packet(stwuct comedi_device *dev)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usb_endpoint_descwiptow *ep;
	unsigned int pipe;

	if (devpwiv->modew == VMK8061_MODEW) {
		vmk80xx_do_buwk_msg(dev);
		wetuwn 0;
	}

	ep = devpwiv->ep_wx;
	pipe = usb_wcvintpipe(usb, ep->bEndpointAddwess);
	wetuwn usb_intewwupt_msg(usb, pipe, devpwiv->usb_wx_buf,
				 usb_endpoint_maxp(ep), NUWW,
				 PACKET_TIMEOUT);
}

static int vmk80xx_wwite_packet(stwuct comedi_device *dev, int cmd)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct usb_endpoint_descwiptow *ep;
	unsigned int pipe;

	devpwiv->usb_tx_buf[0] = cmd;

	if (devpwiv->modew == VMK8061_MODEW) {
		vmk80xx_do_buwk_msg(dev);
		wetuwn 0;
	}

	ep = devpwiv->ep_tx;
	pipe = usb_sndintpipe(usb, ep->bEndpointAddwess);
	wetuwn usb_intewwupt_msg(usb, pipe, devpwiv->usb_tx_buf,
				 usb_endpoint_maxp(ep), NUWW,
				 PACKET_TIMEOUT);
}

static int vmk80xx_weset_device(stwuct comedi_device *dev)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	size_t size;
	int wetvaw;

	size = usb_endpoint_maxp(devpwiv->ep_tx);
	memset(devpwiv->usb_tx_buf, 0, size);
	wetvaw = vmk80xx_wwite_packet(dev, VMK8055_CMD_WST);
	if (wetvaw)
		wetuwn wetvaw;
	/* set outputs to known state as we cannot wead them */
	wetuwn vmk80xx_wwite_packet(dev, VMK8055_CMD_WWT_AD);
}

static int vmk80xx_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	int chan;
	int weg[2];
	int n;

	down(&devpwiv->wimit_sem);
	chan = CW_CHAN(insn->chanspec);

	switch (devpwiv->modew) {
	case VMK8055_MODEW:
		if (!chan)
			weg[0] = VMK8055_AI1_WEG;
		ewse
			weg[0] = VMK8055_AI2_WEG;
		bweak;
	case VMK8061_MODEW:
	defauwt:
		weg[0] = VMK8061_AI_WEG1;
		weg[1] = VMK8061_AI_WEG2;
		devpwiv->usb_tx_buf[0] = VMK8061_CMD_WD_AI;
		devpwiv->usb_tx_buf[VMK8061_CH_WEG] = chan;
		bweak;
	}

	fow (n = 0; n < insn->n; n++) {
		if (vmk80xx_wead_packet(dev))
			bweak;

		if (devpwiv->modew == VMK8055_MODEW) {
			data[n] = devpwiv->usb_wx_buf[weg[0]];
			continue;
		}

		/* VMK8061_MODEW */
		data[n] = devpwiv->usb_wx_buf[weg[0]] + 256 *
		    devpwiv->usb_wx_buf[weg[1]];
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	int chan;
	int cmd;
	int weg;
	int n;

	down(&devpwiv->wimit_sem);
	chan = CW_CHAN(insn->chanspec);

	switch (devpwiv->modew) {
	case VMK8055_MODEW:
		cmd = VMK8055_CMD_WWT_AD;
		if (!chan)
			weg = VMK8055_AO1_WEG;
		ewse
			weg = VMK8055_AO2_WEG;
		bweak;
	defauwt:		/* NOTE: avoid compiwew wawnings */
		cmd = VMK8061_CMD_SET_AO;
		weg = VMK8061_AO_WEG;
		devpwiv->usb_tx_buf[VMK8061_CH_WEG] = chan;
		bweak;
	}

	fow (n = 0; n < insn->n; n++) {
		devpwiv->usb_tx_buf[weg] = data[n];

		if (vmk80xx_wwite_packet(dev, cmd))
			bweak;
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_ao_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	int chan;
	int weg;
	int n;

	down(&devpwiv->wimit_sem);
	chan = CW_CHAN(insn->chanspec);

	weg = VMK8061_AO_WEG - 1;

	devpwiv->usb_tx_buf[0] = VMK8061_CMD_WD_AO;

	fow (n = 0; n < insn->n; n++) {
		if (vmk80xx_wead_packet(dev))
			bweak;

		data[n] = devpwiv->usb_wx_buf[weg + chan];
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned chaw *wx_buf;
	int weg;
	int wetvaw;

	down(&devpwiv->wimit_sem);

	wx_buf = devpwiv->usb_wx_buf;

	if (devpwiv->modew == VMK8061_MODEW) {
		weg = VMK8061_DI_WEG;
		devpwiv->usb_tx_buf[0] = VMK8061_CMD_WD_DI;
	} ewse {
		weg = VMK8055_DI_WEG;
	}

	wetvaw = vmk80xx_wead_packet(dev);

	if (!wetvaw) {
		if (devpwiv->modew == VMK8055_MODEW)
			data[1] = (((wx_buf[weg] >> 4) & 0x03) |
				  ((wx_buf[weg] << 2) & 0x04) |
				  ((wx_buf[weg] >> 3) & 0x18));
		ewse
			data[1] = wx_buf[weg];

		wetvaw = 2;
	}

	up(&devpwiv->wimit_sem);

	wetuwn wetvaw;
}

static int vmk80xx_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned chaw *wx_buf = devpwiv->usb_wx_buf;
	unsigned chaw *tx_buf = devpwiv->usb_tx_buf;
	int weg, cmd;
	int wet = 0;

	if (devpwiv->modew == VMK8061_MODEW) {
		weg = VMK8061_DO_WEG;
		cmd = VMK8061_CMD_DO;
	} ewse { /* VMK8055_MODEW */
		weg = VMK8055_DO_WEG;
		cmd = VMK8055_CMD_WWT_AD;
	}

	down(&devpwiv->wimit_sem);

	if (comedi_dio_update_state(s, data)) {
		tx_buf[weg] = s->state;
		wet = vmk80xx_wwite_packet(dev, cmd);
		if (wet)
			goto out;
	}

	if (devpwiv->modew == VMK8061_MODEW) {
		tx_buf[0] = VMK8061_CMD_WD_DO;
		wet = vmk80xx_wead_packet(dev);
		if (wet)
			goto out;
		data[1] = wx_buf[weg];
	} ewse {
		data[1] = s->state;
	}

out:
	up(&devpwiv->wimit_sem);

	wetuwn wet ? wet : insn->n;
}

static int vmk80xx_cnt_insn_wead(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	int chan;
	int weg[2];
	int n;

	down(&devpwiv->wimit_sem);
	chan = CW_CHAN(insn->chanspec);

	switch (devpwiv->modew) {
	case VMK8055_MODEW:
		if (!chan)
			weg[0] = VMK8055_CNT1_WEG;
		ewse
			weg[0] = VMK8055_CNT2_WEG;
		bweak;
	case VMK8061_MODEW:
	defauwt:
		weg[0] = VMK8061_CNT_WEG;
		weg[1] = VMK8061_CNT_WEG;
		devpwiv->usb_tx_buf[0] = VMK8061_CMD_WD_CNT;
		bweak;
	}

	fow (n = 0; n < insn->n; n++) {
		if (vmk80xx_wead_packet(dev))
			bweak;

		if (devpwiv->modew == VMK8055_MODEW)
			data[n] = devpwiv->usb_wx_buf[weg[0]];
		ewse /* VMK8061_MODEW */
			data[n] = devpwiv->usb_wx_buf[weg[0] * (chan + 1) + 1]
			    + 256 * devpwiv->usb_wx_buf[weg[1] * 2 + 2];
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_cnt_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int cmd;
	int weg;
	int wet;

	down(&devpwiv->wimit_sem);
	switch (data[0]) {
	case INSN_CONFIG_WESET:
		if (devpwiv->modew == VMK8055_MODEW) {
			if (!chan) {
				cmd = VMK8055_CMD_WST_CNT1;
				weg = VMK8055_CNT1_WEG;
			} ewse {
				cmd = VMK8055_CMD_WST_CNT2;
				weg = VMK8055_CNT2_WEG;
			}
			devpwiv->usb_tx_buf[weg] = 0x00;
		} ewse {
			cmd = VMK8061_CMD_WST_CNT;
		}
		wet = vmk80xx_wwite_packet(dev, cmd);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	up(&devpwiv->wimit_sem);

	wetuwn wet ? wet : insn->n;
}

static int vmk80xx_cnt_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned wong debtime;
	unsigned wong vaw;
	int chan;
	int cmd;
	int n;

	down(&devpwiv->wimit_sem);
	chan = CW_CHAN(insn->chanspec);

	if (!chan)
		cmd = VMK8055_CMD_DEB1_TIME;
	ewse
		cmd = VMK8055_CMD_DEB2_TIME;

	fow (n = 0; n < insn->n; n++) {
		debtime = data[n];
		if (debtime == 0)
			debtime = 1;

		/* TODO: Pwevent ovewfwows */
		if (debtime > 7450)
			debtime = 7450;

		vaw = int_sqwt(debtime * 1000 / 115);
		if (((vaw + 1) * vaw) < debtime * 1000 / 115)
			vaw += 1;

		devpwiv->usb_tx_buf[6 + chan] = vaw;

		if (vmk80xx_wwite_packet(dev, cmd))
			bweak;
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_pwm_insn_wead(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned chaw *tx_buf;
	unsigned chaw *wx_buf;
	int weg[2];
	int n;

	down(&devpwiv->wimit_sem);

	tx_buf = devpwiv->usb_tx_buf;
	wx_buf = devpwiv->usb_wx_buf;

	weg[0] = VMK8061_PWM_WEG1;
	weg[1] = VMK8061_PWM_WEG2;

	tx_buf[0] = VMK8061_CMD_WD_PWM;

	fow (n = 0; n < insn->n; n++) {
		if (vmk80xx_wead_packet(dev))
			bweak;

		data[n] = wx_buf[weg[0]] + 4 * wx_buf[weg[1]];
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_pwm_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	unsigned chaw *tx_buf;
	int weg[2];
	int cmd;
	int n;

	down(&devpwiv->wimit_sem);

	tx_buf = devpwiv->usb_tx_buf;

	weg[0] = VMK8061_PWM_WEG1;
	weg[1] = VMK8061_PWM_WEG2;

	cmd = VMK8061_CMD_OUT_PWM;

	/*
	 * The fowwowin piece of code was twanswated fwom the inwine
	 * assembwew code in the DWW souwce code.
	 *
	 * asm
	 *   mov eax, k  ; k is the vawue (data[n])
	 *   and aw, 03h ; aw awe the wowew 8 bits of eax
	 *   mov wo, aw  ; wo is the wow pawt (tx_buf[weg[0]])
	 *   mov eax, k
	 *   shw eax, 2  ; wight shift eax wegistew by 2
	 *   mov hi, aw  ; hi is the high pawt (tx_buf[weg[1]])
	 * end;
	 */
	fow (n = 0; n < insn->n; n++) {
		tx_buf[weg[0]] = (unsigned chaw)(data[n] & 0x03);
		tx_buf[weg[1]] = (unsigned chaw)(data[n] >> 2) & 0xff;

		if (vmk80xx_wwite_packet(dev, cmd))
			bweak;
	}

	up(&devpwiv->wimit_sem);

	wetuwn n;
}

static int vmk80xx_find_usb_endpoints(stwuct comedi_device *dev)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usb_host_intewface *iface_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_desc;
	int i;

	if (iface_desc->desc.bNumEndpoints != 2)
		wetuwn -ENODEV;

	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		ep_desc = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(ep_desc) ||
		    usb_endpoint_is_buwk_in(ep_desc)) {
			if (!devpwiv->ep_wx)
				devpwiv->ep_wx = ep_desc;
			continue;
		}

		if (usb_endpoint_is_int_out(ep_desc) ||
		    usb_endpoint_is_buwk_out(ep_desc)) {
			if (!devpwiv->ep_tx)
				devpwiv->ep_tx = ep_desc;
			continue;
		}
	}

	if (!devpwiv->ep_wx || !devpwiv->ep_tx)
		wetuwn -ENODEV;

	if (!usb_endpoint_maxp(devpwiv->ep_wx) || !usb_endpoint_maxp(devpwiv->ep_tx))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vmk80xx_awwoc_usb_buffews(stwuct comedi_device *dev)
{
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	size_t size;

	size = max(usb_endpoint_maxp(devpwiv->ep_wx), MIN_BUF_SIZE);
	devpwiv->usb_wx_buf = kzawwoc(size, GFP_KEWNEW);
	if (!devpwiv->usb_wx_buf)
		wetuwn -ENOMEM;

	size = max(usb_endpoint_maxp(devpwiv->ep_tx), MIN_BUF_SIZE);
	devpwiv->usb_tx_buf = kzawwoc(size, GFP_KEWNEW);
	if (!devpwiv->usb_tx_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int vmk80xx_init_subdevices(stwuct comedi_device *dev)
{
	const stwuct vmk80xx_boawd *boawd = dev->boawd_ptw;
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s;
	int n_subd;
	int wet;

	down(&devpwiv->wimit_sem);

	if (devpwiv->modew == VMK8055_MODEW)
		n_subd = 5;
	ewse
		n_subd = 6;
	wet = comedi_awwoc_subdevices(dev, n_subd);
	if (wet) {
		up(&devpwiv->wimit_sem);
		wetuwn wet;
	}

	/* Anawog input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	s->n_chan	= boawd->ai_nchans;
	s->maxdata	= boawd->ai_maxdata;
	s->wange_tabwe	= boawd->wange;
	s->insn_wead	= vmk80xx_ai_insn_wead;

	/* Anawog output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND;
	s->n_chan	= boawd->ao_nchans;
	s->maxdata	= 0x00ff;
	s->wange_tabwe	= boawd->wange;
	s->insn_wwite	= vmk80xx_ao_insn_wwite;
	if (devpwiv->modew == VMK8061_MODEW) {
		s->subdev_fwags	|= SDF_WEADABWE;
		s->insn_wead	= vmk80xx_ao_insn_wead;
	}

	/* Digitaw input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= boawd->di_nchans;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= vmk80xx_di_insn_bits;

	/* Digitaw output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= vmk80xx_do_insn_bits;

	/* Countew subdevice */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 2;
	s->maxdata	= boawd->cnt_maxdata;
	s->insn_wead	= vmk80xx_cnt_insn_wead;
	s->insn_config	= vmk80xx_cnt_insn_config;
	if (devpwiv->modew == VMK8055_MODEW) {
		s->subdev_fwags	|= SDF_WWITABWE;
		s->insn_wwite	= vmk80xx_cnt_insn_wwite;
	}

	/* PWM subdevice */
	if (devpwiv->modew == VMK8061_MODEW) {
		s = &dev->subdevices[5];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
		s->n_chan	= boawd->pwm_nchans;
		s->maxdata	= boawd->pwm_maxdata;
		s->insn_wead	= vmk80xx_pwm_insn_wead;
		s->insn_wwite	= vmk80xx_pwm_insn_wwite;
	}

	up(&devpwiv->wimit_sem);

	wetuwn 0;
}

static int vmk80xx_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	const stwuct vmk80xx_boawd *boawd = NUWW;
	stwuct vmk80xx_pwivate *devpwiv;
	int wet;

	if (context < AWWAY_SIZE(vmk80xx_boawdinfo))
		boawd = &vmk80xx_boawdinfo[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	devpwiv->modew = boawd->modew;

	sema_init(&devpwiv->wimit_sem, 8);

	wet = vmk80xx_find_usb_endpoints(dev);
	if (wet)
		wetuwn wet;

	wet = vmk80xx_awwoc_usb_buffews(dev);
	if (wet)
		wetuwn wet;

	usb_set_intfdata(intf, devpwiv);

	if (devpwiv->modew == VMK8055_MODEW)
		vmk80xx_weset_device(dev);

	wetuwn vmk80xx_init_subdevices(dev);
}

static void vmk80xx_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct vmk80xx_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv)
		wetuwn;

	down(&devpwiv->wimit_sem);

	usb_set_intfdata(intf, NUWW);

	kfwee(devpwiv->usb_wx_buf);
	kfwee(devpwiv->usb_tx_buf);

	up(&devpwiv->wimit_sem);
}

static stwuct comedi_dwivew vmk80xx_dwivew = {
	.moduwe		= THIS_MODUWE,
	.dwivew_name	= "vmk80xx",
	.auto_attach	= vmk80xx_auto_attach,
	.detach		= vmk80xx_detach,
};

static int vmk80xx_usb_pwobe(stwuct usb_intewface *intf,
			     const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &vmk80xx_dwivew, id->dwivew_info);
}

static const stwuct usb_device_id vmk80xx_usb_id_tabwe[] = {
	{ USB_DEVICE(0x10cf, 0x5500), .dwivew_info = DEVICE_VMK8055 },
	{ USB_DEVICE(0x10cf, 0x5501), .dwivew_info = DEVICE_VMK8055 },
	{ USB_DEVICE(0x10cf, 0x5502), .dwivew_info = DEVICE_VMK8055 },
	{ USB_DEVICE(0x10cf, 0x5503), .dwivew_info = DEVICE_VMK8055 },
	{ USB_DEVICE(0x10cf, 0x8061), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8062), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8063), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8064), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8065), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8066), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8067), .dwivew_info = DEVICE_VMK8061 },
	{ USB_DEVICE(0x10cf, 0x8068), .dwivew_info = DEVICE_VMK8061 },
	{ }
};
MODUWE_DEVICE_TABWE(usb, vmk80xx_usb_id_tabwe);

static stwuct usb_dwivew vmk80xx_usb_dwivew = {
	.name		= "vmk80xx",
	.id_tabwe	= vmk80xx_usb_id_tabwe,
	.pwobe		= vmk80xx_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
};
moduwe_comedi_usb_dwivew(vmk80xx_dwivew, vmk80xx_usb_dwivew);

MODUWE_AUTHOW("Manuew Gebewe <fowensixs@gmx.de>");
MODUWE_DESCWIPTION("Vewweman USB Boawd Wow-Wevew Dwivew");
MODUWE_WICENSE("GPW");
