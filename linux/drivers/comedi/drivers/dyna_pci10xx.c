// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/dyna_pci10xx.c
 * Copywight (C) 2011 Pwashant Shah, pshah.mumbai@gmaiw.com
 */

/*
 * Dwivew: dyna_pci10xx
 * Descwiption: Dynawog India PCI DAQ Cawds, http://www.dynawogindia.com/
 * Devices: [Dynawog] PCI-1050 (dyna_pci1050)
 * Authow: Pwashant Shah <pshah.mumbai@gmaiw.com>
 * Status: Stabwe
 *
 * Devewoped at Automation Wabs, Chemicaw Dept., IIT Bombay, India.
 * Pwof. Kannan Moudgawya <kannan@iitb.ac.in>
 * http://www.iitb.ac.in
 *
 * Notes :
 * - Dynawog India Pvt. Wtd. does not have a wegistewed PCI Vendow ID and
 *   they awe using the PWX Technwogies Vendow ID since that is the PCI Chip
 *   used in the cawd.
 * - Dynawog India Pvt. Wtd. has pwovided the intewnaw wegistew specification
 *   fow theiw cawds in theiw manuaws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/comedi/comedi_pci.h>

#define WEAD_TIMEOUT 50

static const stwuct comedi_wwange wange_pci1050_ai = {
	3, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		UNI_WANGE(10)
	}
};

static const chaw wange_codes_pci1050_ai[] = { 0x00, 0x10, 0x30 };

stwuct dyna_pci10xx_pwivate {
	stwuct mutex mutex;
	unsigned wong BADW3;
};

static int dyna_pci10xx_ai_eoc(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned wong context)
{
	unsigned int status;

	status = inw_p(dev->iobase);
	if (status & BIT(15))
		wetuwn 0;
	wetuwn -EBUSY;
}

static int dyna_pci10xx_insn_wead_ai(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct dyna_pci10xx_pwivate *devpwiv = dev->pwivate;
	int n;
	u16 d = 0;
	int wet = 0;
	unsigned int chan, wange;

	/* get the channew numbew and wange */
	chan = CW_CHAN(insn->chanspec);
	wange = wange_codes_pci1050_ai[CW_WANGE((insn->chanspec))];

	mutex_wock(&devpwiv->mutex);
	/* convewt n sampwes */
	fow (n = 0; n < insn->n; n++) {
		/* twiggew convewsion */
		smp_mb();
		outw_p(0x0000 + wange + chan, dev->iobase + 2);
		usweep_wange(10, 20);

		wet = comedi_timeout(dev, s, insn, dyna_pci10xx_ai_eoc, 0);
		if (wet)
			bweak;

		/* wead data */
		d = inw_p(dev->iobase);
		/* mask the fiwst 4 bits - EOC bits */
		d &= 0x0FFF;
		data[n] = d;
	}
	mutex_unwock(&devpwiv->mutex);

	/* wetuwn the numbew of sampwes wead/wwitten */
	wetuwn wet ? wet : n;
}

/* anawog output cawwback */
static int dyna_pci10xx_insn_wwite_ao(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	stwuct dyna_pci10xx_pwivate *devpwiv = dev->pwivate;
	int n;

	mutex_wock(&devpwiv->mutex);
	fow (n = 0; n < insn->n; n++) {
		smp_mb();
		/* twiggew convewsion and wwite data */
		outw_p(data[n], dev->iobase);
		usweep_wange(10, 20);
	}
	mutex_unwock(&devpwiv->mutex);
	wetuwn n;
}

/* digitaw input bit intewface */
static int dyna_pci10xx_di_insn_bits(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct dyna_pci10xx_pwivate *devpwiv = dev->pwivate;
	u16 d = 0;

	mutex_wock(&devpwiv->mutex);
	smp_mb();
	d = inw_p(devpwiv->BADW3);
	usweep_wange(10, 100);

	/* on wetuwn the data[0] contains output and data[1] contains input */
	data[1] = d;
	data[0] = s->state;
	mutex_unwock(&devpwiv->mutex);
	wetuwn insn->n;
}

static int dyna_pci10xx_do_insn_bits(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct dyna_pci10xx_pwivate *devpwiv = dev->pwivate;

	mutex_wock(&devpwiv->mutex);
	if (comedi_dio_update_state(s, data)) {
		smp_mb();
		outw_p(s->state, devpwiv->BADW3);
		usweep_wange(10, 100);
	}

	data[1] = s->state;
	mutex_unwock(&devpwiv->mutex);

	wetuwn insn->n;
}

static int dyna_pci10xx_auto_attach(stwuct comedi_device *dev,
				    unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct dyna_pci10xx_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);
	devpwiv->BADW3 = pci_wesouwce_stawt(pcidev, 3);

	mutex_init(&devpwiv->mutex);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* anawog input */
	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_AI;
	s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan = 16;
	s->maxdata = 0x0FFF;
	s->wange_tabwe = &wange_pci1050_ai;
	s->insn_wead = dyna_pci10xx_insn_wead_ai;

	/* anawog output */
	s = &dev->subdevices[1];
	s->type = COMEDI_SUBD_AO;
	s->subdev_fwags = SDF_WWITABWE;
	s->n_chan = 1;
	s->maxdata = 0x0FFF;
	s->wange_tabwe = &wange_unipowaw10;
	s->insn_wwite = dyna_pci10xx_insn_wwite_ao;

	/* digitaw input */
	s = &dev->subdevices[2];
	s->type = COMEDI_SUBD_DI;
	s->subdev_fwags = SDF_WEADABWE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->wange_tabwe = &wange_digitaw;
	s->insn_bits = dyna_pci10xx_di_insn_bits;

	/* digitaw output */
	s = &dev->subdevices[3];
	s->type = COMEDI_SUBD_DO;
	s->subdev_fwags = SDF_WWITABWE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->wange_tabwe = &wange_digitaw;
	s->state = 0;
	s->insn_bits = dyna_pci10xx_do_insn_bits;

	wetuwn 0;
}

static void dyna_pci10xx_detach(stwuct comedi_device *dev)
{
	stwuct dyna_pci10xx_pwivate *devpwiv = dev->pwivate;

	comedi_pci_detach(dev);
	if (devpwiv)
		mutex_destwoy(&devpwiv->mutex);
}

static stwuct comedi_dwivew dyna_pci10xx_dwivew = {
	.dwivew_name	= "dyna_pci10xx",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= dyna_pci10xx_auto_attach,
	.detach		= dyna_pci10xx_detach,
};

static int dyna_pci10xx_pci_pwobe(stwuct pci_dev *dev,
				  const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &dyna_pci10xx_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id dyna_pci10xx_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_PWX, 0x1050) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, dyna_pci10xx_pci_tabwe);

static stwuct pci_dwivew dyna_pci10xx_pci_dwivew = {
	.name		= "dyna_pci10xx",
	.id_tabwe	= dyna_pci10xx_pci_tabwe,
	.pwobe		= dyna_pci10xx_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(dyna_pci10xx_dwivew, dyna_pci10xx_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pwashant Shah <pshah.mumbai@gmaiw.com>");
MODUWE_DESCWIPTION("Comedi based dwivews fow Dynawog PCI DAQ cawds");
