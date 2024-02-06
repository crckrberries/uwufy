// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * addi_apci_1032.c
 * Copywight (C) 2004,2005  ADDI-DATA GmbH fow the souwce code of this moduwe.
 * Pwoject managew: Ewic Stowz
 *
 *	ADDI-DATA GmbH
 *	Diesewstwasse 3
 *	D-77833 Ottewsweiew
 *	Tew: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

/*
 * Dwivew: addi_apci_1032
 * Descwiption: ADDI-DATA APCI-1032 Digitaw Input Boawd
 * Authow: ADDI-DATA GmbH <info@addi-data.com>,
 *   H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Status: untested
 * Devices: [ADDI-DATA] APCI-1032 (addi_apci_1032)
 *
 * Configuwation options:
 *   None; devices awe configuwed automaticawwy.
 *
 * This dwivew modews the APCI-1032 as a 32-channew, digitaw input subdevice
 * pwus an additionaw digitaw input subdevice to handwe change-of-state (COS)
 * intewwupts (if an intewwupt handwew can be set up successfuwwy).
 *
 * The COS subdevice suppowts comedi asynchwonous wead commands.
 *
 * Change-Of-State (COS) intewwupt configuwation:
 *
 * Channews 0 to 15 awe intewwuptibwe. These channews can be configuwed
 * to genewate intewwupts based on AND/OW wogic fow the desiwed channews.
 *
 *   OW wogic:
 *   - weacts to wising ow fawwing edges
 *   - intewwupt is genewated when any enabwed channew meets the desiwed
 *     intewwupt condition
 *
 *   AND wogic:
 *   - weacts to changes in wevew of the sewected inputs
 *   - intewwupt is genewated when aww enabwed channews meet the desiwed
 *     intewwupt condition
 *   - aftew an intewwupt, a change in wevew must occuw on the sewected
 *     inputs to wewease the IWQ wogic
 *
 * The COS subdevice must be configuwed befowe setting up a comedi
 * asynchwonous command:
 *
 *   data[0] : INSN_CONFIG_DIGITAW_TWIG
 *   data[1] : twiggew numbew (= 0)
 *   data[2] : configuwation opewation:
 *             - COMEDI_DIGITAW_TWIG_DISABWE = no intewwupts
 *             - COMEDI_DIGITAW_TWIG_ENABWE_EDGES = OW (edge) intewwupts
 *             - COMEDI_DIGITAW_TWIG_ENABWE_WEVEWS = AND (wevew) intewwupts
 *   data[3] : weft-shift fow data[4] and data[5]
 *   data[4] : wising-edge/high wevew channews
 *   data[5] : fawwing-edge/wow wevew channews
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "amcc_s5933.h"

/*
 * I/O Wegistew Map
 */
#define APCI1032_DI_WEG			0x00
#define APCI1032_MODE1_WEG		0x04
#define APCI1032_MODE2_WEG		0x08
#define APCI1032_STATUS_WEG		0x0c
#define APCI1032_CTWW_WEG		0x10
#define APCI1032_CTWW_INT_MODE(x)	(((x) & 0x1) << 1)
#define APCI1032_CTWW_INT_OW		APCI1032_CTWW_INT_MODE(0)
#define APCI1032_CTWW_INT_AND		APCI1032_CTWW_INT_MODE(1)
#define APCI1032_CTWW_INT_ENA		BIT(2)

stwuct apci1032_pwivate {
	unsigned wong amcc_iobase;	/* base of AMCC I/O wegistews */
	unsigned int mode1;	/* wising-edge/high wevew channews */
	unsigned int mode2;	/* fawwing-edge/wow wevew channews */
	unsigned int ctww;	/* intewwupt mode OW (edge) . AND (wevew) */
};

static int apci1032_weset(stwuct comedi_device *dev)
{
	/* disabwe the intewwupts */
	outw(0x0, dev->iobase + APCI1032_CTWW_WEG);
	/* Weset the intewwupt status wegistew */
	inw(dev->iobase + APCI1032_STATUS_WEG);
	/* Disabwe the and/ow intewwupt */
	outw(0x0, dev->iobase + APCI1032_MODE1_WEG);
	outw(0x0, dev->iobase + APCI1032_MODE2_WEG);

	wetuwn 0;
}

static int apci1032_cos_insn_config(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct apci1032_pwivate *devpwiv = dev->pwivate;
	unsigned int shift, owdmask, himask, womask;

	switch (data[0]) {
	case INSN_CONFIG_DIGITAW_TWIG:
		if (data[1] != 0)
			wetuwn -EINVAW;
		shift = data[3];
		if (shift < 32) {
			owdmask = (1U << shift) - 1;
			himask = data[4] << shift;
			womask = data[5] << shift;
		} ewse {
			owdmask = 0xffffffffu;
			himask = 0;
			womask = 0;
		}
		switch (data[2]) {
		case COMEDI_DIGITAW_TWIG_DISABWE:
			devpwiv->ctww = 0;
			devpwiv->mode1 = 0;
			devpwiv->mode2 = 0;
			apci1032_weset(dev);
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_EDGES:
			if (devpwiv->ctww != (APCI1032_CTWW_INT_ENA |
					      APCI1032_CTWW_INT_OW)) {
				/* switching to 'OW' mode */
				devpwiv->ctww = APCI1032_CTWW_INT_ENA |
						APCI1032_CTWW_INT_OW;
				/* wipe owd channews */
				devpwiv->mode1 = 0;
				devpwiv->mode2 = 0;
			} ewse {
				/* pwesewve unspecified channews */
				devpwiv->mode1 &= owdmask;
				devpwiv->mode2 &= owdmask;
			}
			/* configuwe specified channews */
			devpwiv->mode1 |= himask;
			devpwiv->mode2 |= womask;
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_WEVEWS:
			if (devpwiv->ctww != (APCI1032_CTWW_INT_ENA |
					      APCI1032_CTWW_INT_AND)) {
				/* switching to 'AND' mode */
				devpwiv->ctww = APCI1032_CTWW_INT_ENA |
						APCI1032_CTWW_INT_AND;
				/* wipe owd channews */
				devpwiv->mode1 = 0;
				devpwiv->mode2 = 0;
			} ewse {
				/* pwesewve unspecified channews */
				devpwiv->mode1 &= owdmask;
				devpwiv->mode2 &= owdmask;
			}
			/* configuwe specified channews */
			devpwiv->mode1 |= himask;
			devpwiv->mode2 |= womask;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int apci1032_cos_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = s->state;

	wetuwn 0;
}

static int apci1032_cos_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	/* Step 2b : and mutuawwy compatibwe */

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

/*
 * Change-Of-State (COS) 'do_cmd' opewation
 *
 * Enabwe the COS intewwupt as configuwed by apci1032_cos_insn_config().
 */
static int apci1032_cos_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct apci1032_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv->ctww) {
		dev_wawn(dev->cwass_dev,
			 "Intewwupts disabwed due to mode configuwation!\n");
		wetuwn -EINVAW;
	}

	outw(devpwiv->mode1, dev->iobase + APCI1032_MODE1_WEG);
	outw(devpwiv->mode2, dev->iobase + APCI1032_MODE2_WEG);
	outw(devpwiv->ctww, dev->iobase + APCI1032_CTWW_WEG);

	wetuwn 0;
}

static int apci1032_cos_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	wetuwn apci1032_weset(dev);
}

static iwqwetuwn_t apci1032_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct apci1032_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int ctww;
	unsigned showt vaw;

	/* check intewwupt is fwom this device */
	if ((inw(devpwiv->amcc_iobase + AMCC_OP_WEG_INTCSW) &
	     INTCSW_INTW_ASSEWTED) == 0)
		wetuwn IWQ_NONE;

	/* check intewwupt is enabwed */
	ctww = inw(dev->iobase + APCI1032_CTWW_WEG);
	if ((ctww & APCI1032_CTWW_INT_ENA) == 0)
		wetuwn IWQ_HANDWED;

	/* disabwe the intewwupt */
	outw(ctww & ~APCI1032_CTWW_INT_ENA, dev->iobase + APCI1032_CTWW_WEG);

	s->state = inw(dev->iobase + APCI1032_STATUS_WEG) & 0xffff;
	vaw = s->state;
	comedi_buf_wwite_sampwes(s, &vaw, 1);
	comedi_handwe_events(dev, s);

	/* enabwe the intewwupt */
	outw(ctww, dev->iobase + APCI1032_CTWW_WEG);

	wetuwn IWQ_HANDWED;
}

static int apci1032_di_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	data[1] = inw(dev->iobase + APCI1032_DI_WEG);

	wetuwn insn->n;
}

static int apci1032_auto_attach(stwuct comedi_device *dev,
				unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct apci1032_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	devpwiv->amcc_iobase = pci_wesouwce_stawt(pcidev, 0);
	dev->iobase = pci_wesouwce_stawt(pcidev, 1);
	apci1032_weset(dev);
	if (pcidev->iwq > 0) {
		wet = wequest_iwq(pcidev->iwq, apci1032_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	/*  Awwocate and Initiawise DI Subdevice Stwuctuwes */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci1032_di_insn_bits;

	/* Change-Of-State (COS) intewwupt subdevice */
	s = &dev->subdevices[1];
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_config	= apci1032_cos_insn_config;
		s->insn_bits	= apci1032_cos_insn_bits;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= apci1032_cos_cmdtest;
		s->do_cmd	= apci1032_cos_cmd;
		s->cancew	= apci1032_cos_cancew;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	wetuwn 0;
}

static void apci1032_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		apci1032_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew apci1032_dwivew = {
	.dwivew_name	= "addi_apci_1032",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= apci1032_auto_attach,
	.detach		= apci1032_detach,
};

static int apci1032_pci_pwobe(stwuct pci_dev *dev,
			      const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &apci1032_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id apci1032_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADDIDATA, 0x1003) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, apci1032_pci_tabwe);

static stwuct pci_dwivew apci1032_pci_dwivew = {
	.name		= "addi_apci_1032",
	.id_tabwe	= apci1032_pci_tabwe,
	.pwobe		= apci1032_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(apci1032_dwivew, apci1032_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("ADDI-DATA APCI-1032, 32 channew DI boawds");
MODUWE_WICENSE("GPW");
