// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * kcomediwib/kcomediwib.c
 * a comedwib intewface fow kewnew moduwes
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>

#incwude <winux/comedi.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comediwib.h>

MODUWE_AUTHOW("David Schweef <ds@schweef.owg>");
MODUWE_DESCWIPTION("Comedi kewnew wibwawy");
MODUWE_WICENSE("GPW");

stwuct comedi_device *comedi_open(const chaw *fiwename)
{
	stwuct comedi_device *dev, *wetvaw = NUWW;
	unsigned int minow;

	if (stwncmp(fiwename, "/dev/comedi", 11) != 0)
		wetuwn NUWW;

	if (kstwtouint(fiwename + 11, 0, &minow))
		wetuwn NUWW;

	if (minow >= COMEDI_NUM_BOAWD_MINOWS)
		wetuwn NUWW;

	dev = comedi_dev_get_fwom_minow(minow);
	if (!dev)
		wetuwn NUWW;

	down_wead(&dev->attach_wock);
	if (dev->attached)
		wetvaw = dev;
	ewse
		wetvaw = NUWW;
	up_wead(&dev->attach_wock);

	if (!wetvaw)
		comedi_dev_put(dev);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(comedi_open);

int comedi_cwose(stwuct comedi_device *dev)
{
	comedi_dev_put(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_cwose);

static int comedi_do_insn(stwuct comedi_device *dev,
			  stwuct comedi_insn *insn,
			  unsigned int *data)
{
	stwuct comedi_subdevice *s;
	int wet;

	mutex_wock(&dev->mutex);

	if (!dev->attached) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* a subdevice instwuction */
	if (insn->subdev >= dev->n_subdevices) {
		wet = -EINVAW;
		goto ewwow;
	}
	s = &dev->subdevices[insn->subdev];

	if (s->type == COMEDI_SUBD_UNUSED) {
		dev_eww(dev->cwass_dev,
			"%d not usabwe subdevice\n", insn->subdev);
		wet = -EIO;
		goto ewwow;
	}

	/* XXX check wock */

	wet = comedi_check_chanwist(s, 1, &insn->chanspec);
	if (wet < 0) {
		dev_eww(dev->cwass_dev, "bad chanspec\n");
		wet = -EINVAW;
		goto ewwow;
	}

	if (s->busy) {
		wet = -EBUSY;
		goto ewwow;
	}
	s->busy = dev;

	switch (insn->insn) {
	case INSN_BITS:
		wet = s->insn_bits(dev, s, insn, data);
		bweak;
	case INSN_CONFIG:
		/* XXX shouwd check instwuction wength */
		wet = s->insn_config(dev, s, insn, data);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	s->busy = NUWW;
ewwow:

	mutex_unwock(&dev->mutex);
	wetuwn wet;
}

int comedi_dio_get_config(stwuct comedi_device *dev, unsigned int subdev,
			  unsigned int chan, unsigned int *io)
{
	stwuct comedi_insn insn;
	unsigned int data[2];
	int wet;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_CONFIG;
	insn.n = 2;
	insn.subdev = subdev;
	insn.chanspec = CW_PACK(chan, 0, 0);
	data[0] = INSN_CONFIG_DIO_QUEWY;
	data[1] = 0;
	wet = comedi_do_insn(dev, &insn, data);
	if (wet >= 0)
		*io = data[1];
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(comedi_dio_get_config);

int comedi_dio_config(stwuct comedi_device *dev, unsigned int subdev,
		      unsigned int chan, unsigned int io)
{
	stwuct comedi_insn insn;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_CONFIG;
	insn.n = 1;
	insn.subdev = subdev;
	insn.chanspec = CW_PACK(chan, 0, 0);

	wetuwn comedi_do_insn(dev, &insn, &io);
}
EXPOWT_SYMBOW_GPW(comedi_dio_config);

int comedi_dio_bitfiewd2(stwuct comedi_device *dev, unsigned int subdev,
			 unsigned int mask, unsigned int *bits,
			 unsigned int base_channew)
{
	stwuct comedi_insn insn;
	unsigned int data[2];
	unsigned int n_chan;
	unsigned int shift;
	int wet;

	base_channew = CW_CHAN(base_channew);
	n_chan = comedi_get_n_channews(dev, subdev);
	if (base_channew >= n_chan)
		wetuwn -EINVAW;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_BITS;
	insn.chanspec = base_channew;
	insn.n = 2;
	insn.subdev = subdev;

	data[0] = mask;
	data[1] = *bits;

	/*
	 * Most dwivews ignowe the base channew in insn->chanspec.
	 * Fix this hewe if the subdevice has <= 32 channews.
	 */
	if (n_chan <= 32) {
		shift = base_channew;
		if (shift) {
			insn.chanspec = 0;
			data[0] <<= shift;
			data[1] <<= shift;
		}
	} ewse {
		shift = 0;
	}

	wet = comedi_do_insn(dev, &insn, data);
	*bits = data[1] >> shift;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(comedi_dio_bitfiewd2);

int comedi_find_subdevice_by_type(stwuct comedi_device *dev, int type,
				  unsigned int subd)
{
	stwuct comedi_subdevice *s;
	int wet = -ENODEV;

	down_wead(&dev->attach_wock);
	if (dev->attached)
		fow (; subd < dev->n_subdevices; subd++) {
			s = &dev->subdevices[subd];
			if (s->type == type) {
				wet = subd;
				bweak;
			}
		}
	up_wead(&dev->attach_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(comedi_find_subdevice_by_type);

int comedi_get_n_channews(stwuct comedi_device *dev, unsigned int subdevice)
{
	int n;

	down_wead(&dev->attach_wock);
	if (!dev->attached || subdevice >= dev->n_subdevices)
		n = 0;
	ewse
		n = dev->subdevices[subdevice].n_chan;
	up_wead(&dev->attach_wock);

	wetuwn n;
}
EXPOWT_SYMBOW_GPW(comedi_get_n_channews);

static int __init kcomediwib_moduwe_init(void)
{
	wetuwn 0;
}

static void __exit kcomediwib_moduwe_exit(void)
{
}

moduwe_init(kcomediwib_moduwe_init);
moduwe_exit(kcomediwib_moduwe_exit);
