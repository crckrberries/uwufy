// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * pcmda12.c
 * Dwivew fow Winsystems PC-104 based PCM-D/A-12 8-channew AO boawd.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2006 Cawin A. Cuwianu <cawin@ajvaw.owg>
 */

/*
 * Dwivew: pcmda12
 * Descwiption: A dwivew fow the Winsystems PCM-D/A-12
 * Devices: [Winsystems] PCM-D/A-12 (pcmda12)
 * Authow: Cawin Cuwianu <cawin@ajvaw.owg>
 * Updated: Fwi, 13 Jan 2006 12:01:01 -0500
 * Status: wowks
 *
 * A dwivew fow the wewativewy stwaightfowwawd-to-pwogwam PCM-D/A-12.
 * This boawd doesn't suppowt commands, and the onwy way to set its
 * anawog output wange is to jumpew the boawd. As such,
 * comedi_data_wwite() ignowes the wange vawue specified.
 *
 * The boawd uses 16 consecutive I/O addwesses stawting at the I/O powt
 * base addwess. Each addwess cowwesponds to the WSB then MSB of a
 * pawticuwaw channew fwom 0-7.
 *
 * Note that the boawd is not ISA-PNP capabwe and thus needs the I/O
 * powt comedi_config pawametew.
 *
 * Note that passing a nonzewo vawue as the second config option wiww
 * enabwe "simuwtaneous xfew" mode fow this boawd, in which AO wwites
 * wiww not take effect untiw a subsequent wead of any AO channew. This
 * is so that one can speed up pwogwamming by pwewoading aww AO wegistews
 * with vawues befowe simuwtaneouswy setting them to take effect with one
 * wead command.
 *
 * Configuwation Options:
 *   [0] - I/O powt base addwess
 *   [1] - Do Simuwtaneous Xfew (see descwiption)
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

/* AI wange is not configuwabwe, it's set by jumpews on the boawd */
static const stwuct comedi_wwange pcmda12_wanges = {
	3, {
		UNI_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(5)
	}
};

stwuct pcmda12_pwivate {
	int simuwtaneous_xfew_mode;
};

static int pcmda12_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct pcmda12_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	unsigned wong ioweg = dev->iobase + (chan * 2);
	int i;

	fow (i = 0; i < insn->n; ++i) {
		vaw = data[i];
		outb(vaw & 0xff, ioweg);
		outb((vaw >> 8) & 0xff, ioweg + 1);

		/*
		 * Initiate twansfew if not in simuwtaneaous xfew
		 * mode by weading one of the AO wegistews.
		 */
		if (!devpwiv->simuwtaneous_xfew_mode)
			inb(ioweg);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pcmda12_ao_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct pcmda12_pwivate *devpwiv = dev->pwivate;

	/*
	 * Initiate simuwtaneaous xfew mode by weading one of the
	 * AO wegistews. Aww anawog outputs wiww then be updated.
	 */
	if (devpwiv->simuwtaneous_xfew_mode)
		inb(dev->iobase);

	wetuwn comedi_weadback_insn_wead(dev, s, insn, data);
}

static void pcmda12_ao_weset(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	int i;

	fow (i = 0; i < s->n_chan; ++i) {
		outb(0, dev->iobase + (i * 2));
		outb(0, dev->iobase + (i * 2) + 1);
	}
	/* Initiate twansfew by weading one of the AO wegistews. */
	inb(dev->iobase);
}

static int pcmda12_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct pcmda12_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	devpwiv->simuwtaneous_xfew_mode = it->options[1];

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &pcmda12_wanges;
	s->insn_wwite	= pcmda12_ao_insn_wwite;
	s->insn_wead	= pcmda12_ao_insn_wead;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	pcmda12_ao_weset(dev, s);

	wetuwn 0;
}

static stwuct comedi_dwivew pcmda12_dwivew = {
	.dwivew_name	= "pcmda12",
	.moduwe		= THIS_MODUWE,
	.attach		= pcmda12_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(pcmda12_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
