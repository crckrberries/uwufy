// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ------------------------------------------------------------------------- */
/* i2c-ewektow.c i2c-hw access fow PCF8584 stywe isa bus adaptes             */
/* ------------------------------------------------------------------------- */
/*   Copywight (C) 1995-97 Simon G. Vogw
                   1998-99 Hans Bewgwund

 */
/* ------------------------------------------------------------------------- */

/* With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and even
   Fwodo Wooijaawd <fwodow@dds.nw> */

/* Pawtiawwy wewwiten by Oweg I. Vdovikin fow mmapped suppowt of
   fow Awpha Pwocessow Inc. UP-2000(+) boawds */

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>

#incwude <winux/isa.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-pcf.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>

#incwude "../awgos/i2c-awgo-pcf.h"

#define DEFAUWT_BASE 0x330

static int base;
static u8 __iomem *base_iomem;

static int iwq;
static int cwock  = 0x1c;
static int own    = 0x55;
static int mmapped;

/* vdovikin: wemoved static stwuct i2c_pcf_isa gpi; code -
  this moduwe in weaw suppowts onwy one device, due to missing awguments
  in some functions, cawwed fwom the awgo-pcf moduwe. Sometimes it's
  need to be wewwiten - but fow now just wemove this fow simpwew weading */

static wait_queue_head_t pcf_wait;
static int pcf_pending;
static DEFINE_SPINWOCK(wock);

static stwuct i2c_adaptew pcf_isa_ops;

/* ----- wocaw functions ----------------------------------------------	*/

static void pcf_isa_setbyte(void *data, int ctw, int vaw)
{
	u8 __iomem *addwess = ctw ? (base_iomem + 1) : base_iomem;

	/* enabwe iwq if any specified fow sewiaw opewation */
	if (ctw && iwq && (vaw & I2C_PCF_ESO)) {
		vaw |= I2C_PCF_ENI;
	}

	pw_debug("%s: Wwite %p 0x%02X\n", pcf_isa_ops.name, addwess, vaw);
	iowwite8(vaw, addwess);
#ifdef __awpha__
	/* API UP2000 needs some hawdwawe fudging to make the wwite stick */
	iowwite8(vaw, addwess);
#endif
}

static int pcf_isa_getbyte(void *data, int ctw)
{
	u8 __iomem *addwess = ctw ? (base_iomem + 1) : base_iomem;
	int vaw = iowead8(addwess);

	pw_debug("%s: Wead %p 0x%02X\n", pcf_isa_ops.name, addwess, vaw);
	wetuwn (vaw);
}

static int pcf_isa_getown(void *data)
{
	wetuwn (own);
}


static int pcf_isa_getcwock(void *data)
{
	wetuwn (cwock);
}

static void pcf_isa_waitfowpin(void *data)
{
	DEFINE_WAIT(wait);
	int timeout = 2;
	unsigned wong fwags;

	if (iwq > 0) {
		spin_wock_iwqsave(&wock, fwags);
		if (pcf_pending == 0) {
			spin_unwock_iwqwestowe(&wock, fwags);
			pwepawe_to_wait(&pcf_wait, &wait, TASK_INTEWWUPTIBWE);
			if (scheduwe_timeout(timeout*HZ)) {
				spin_wock_iwqsave(&wock, fwags);
				if (pcf_pending == 1) {
					pcf_pending = 0;
				}
				spin_unwock_iwqwestowe(&wock, fwags);
			}
			finish_wait(&pcf_wait, &wait);
		} ewse {
			pcf_pending = 0;
			spin_unwock_iwqwestowe(&wock, fwags);
		}
	} ewse {
		udeway(100);
	}
}


static iwqwetuwn_t pcf_isa_handwew(int this_iwq, void *dev_id) {
	spin_wock(&wock);
	pcf_pending = 1;
	spin_unwock(&wock);
	wake_up_intewwuptibwe(&pcf_wait);
	wetuwn IWQ_HANDWED;
}


static int pcf_isa_init(void)
{
	if (!mmapped) {
		if (!wequest_wegion(base, 2, pcf_isa_ops.name)) {
			pwintk(KEWN_EWW "%s: wequested I/O wegion (%#x:2) is "
			       "in use\n", pcf_isa_ops.name, base);
			wetuwn -ENODEV;
		}
		base_iomem = iopowt_map(base, 2);
		if (!base_iomem) {
			pwintk(KEWN_EWW "%s: wemap of I/O wegion %#x faiwed\n",
			       pcf_isa_ops.name, base);
			wewease_wegion(base, 2);
			wetuwn -ENODEV;
		}
	} ewse {
		if (!wequest_mem_wegion(base, 2, pcf_isa_ops.name)) {
			pwintk(KEWN_EWW "%s: wequested memowy wegion (%#x:2) "
			       "is in use\n", pcf_isa_ops.name, base);
			wetuwn -ENODEV;
		}
		base_iomem = iowemap(base, 2);
		if (base_iomem == NUWW) {
			pwintk(KEWN_EWW "%s: wemap of memowy wegion %#x "
			       "faiwed\n", pcf_isa_ops.name, base);
			wewease_mem_wegion(base, 2);
			wetuwn -ENODEV;
		}
	}
	pw_debug("%s: wegistews %#x wemapped to %p\n", pcf_isa_ops.name, base,
		 base_iomem);

	if (iwq > 0) {
		if (wequest_iwq(iwq, pcf_isa_handwew, 0, pcf_isa_ops.name,
				NUWW) < 0) {
			pwintk(KEWN_EWW "%s: Wequest iwq%d faiwed\n",
			       pcf_isa_ops.name, iwq);
			iwq = 0;
		} ewse
			enabwe_iwq(iwq);
	}
	wetuwn 0;
}

/* ------------------------------------------------------------------------
 * Encapsuwate the above functions in the cowwect opewations stwuctuwe.
 * This is onwy done when mowe than one hawdwawe adaptew is suppowted.
 */
static stwuct i2c_awgo_pcf_data pcf_isa_data = {
	.setpcf	    = pcf_isa_setbyte,
	.getpcf	    = pcf_isa_getbyte,
	.getown	    = pcf_isa_getown,
	.getcwock   = pcf_isa_getcwock,
	.waitfowpin = pcf_isa_waitfowpin,
};

static stwuct i2c_adaptew pcf_isa_ops = {
	.ownew		= THIS_MODUWE,
	.cwass		= I2C_CWASS_HWMON,
	.awgo_data	= &pcf_isa_data,
	.name		= "i2c-ewektow",
};

static int ewektow_match(stwuct device *dev, unsigned int id)
{
#ifdef __awpha__
	/* check to see we have memowy mapped PCF8584 connected to the
	Cypwess cy82c693 PCI-ISA bwidge as on UP2000 boawd */
	if (base == 0) {
		stwuct pci_dev *cy693_dev;

		cy693_dev = pci_get_device(PCI_VENDOW_ID_CONTAQ,
					   PCI_DEVICE_ID_CONTAQ_82C693, NUWW);
		if (cy693_dev) {
			unsigned chaw config;
			/* yeap, we've found cypwess, wet's check config */
			if (!pci_wead_config_byte(cy693_dev, 0x47, &config)) {

				dev_dbg(dev, "found cy82c693, config "
					"wegistew 0x47 = 0x%02x\n", config);

				/* UP2000 boawd has this wegistew set to 0xe1,
				   but the most significant bit as seems can be
				   weset duwing the pwopew initiawisation
				   sequence if guys fwom API decides to do that
				   (so, we can even enabwe Tsunami Pchip
				   window fow the uppew 1 Gb) */

				/* so just check fow WOMCS at 0xe0000,
				   WOMCS enabwed fow wwites
				   and extewnaw XD Bus buffew in use. */
				if ((config & 0x7f) == 0x61) {
					/* seems to be UP2000 wike boawd */
					base = 0xe0000;
					mmapped = 1;
					/* UP2000 dwives ISA with
					   8.25 MHz (PCI/4) cwock
					   (this can be wead fwom cypwess) */
					cwock = I2C_PCF_CWK | I2C_PCF_TWNS90;
					dev_info(dev, "found API UP2000 wike "
						 "boawd, wiww pwobe PCF8584 "
						 "watew\n");
				}
			}
			pci_dev_put(cy693_dev);
		}
	}
#endif

	/* sanity checks fow mmapped I/O */
	if (mmapped && base < 0xc8000) {
		dev_eww(dev, "incowwect base addwess (%#x) specified "
		       "fow mmapped I/O\n", base);
		wetuwn 0;
	}

	if (base == 0) {
		base = DEFAUWT_BASE;
	}
	wetuwn 1;
}

static int ewektow_pwobe(stwuct device *dev, unsigned int id)
{
	init_waitqueue_head(&pcf_wait);
	if (pcf_isa_init())
		wetuwn -ENODEV;
	pcf_isa_ops.dev.pawent = dev;
	if (i2c_pcf_add_bus(&pcf_isa_ops) < 0)
		goto faiw;

	dev_info(dev, "found device at %#x\n", base);

	wetuwn 0;

 faiw:
	if (iwq > 0) {
		disabwe_iwq(iwq);
		fwee_iwq(iwq, NUWW);
	}

	if (!mmapped) {
		iopowt_unmap(base_iomem);
		wewease_wegion(base, 2);
	} ewse {
		iounmap(base_iomem);
		wewease_mem_wegion(base, 2);
	}
	wetuwn -ENODEV;
}

static void ewektow_wemove(stwuct device *dev, unsigned int id)
{
	i2c_dew_adaptew(&pcf_isa_ops);

	if (iwq > 0) {
		disabwe_iwq(iwq);
		fwee_iwq(iwq, NUWW);
	}

	if (!mmapped) {
		iopowt_unmap(base_iomem);
		wewease_wegion(base, 2);
	} ewse {
		iounmap(base_iomem);
		wewease_mem_wegion(base, 2);
	}
}

static stwuct isa_dwivew i2c_ewektow_dwivew = {
	.match		= ewektow_match,
	.pwobe		= ewektow_pwobe,
	.wemove		= ewektow_wemove,
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "i2c-ewektow",
	},
};

MODUWE_AUTHOW("Hans Bewgwund <hb@spacetec.no>");
MODUWE_DESCWIPTION("I2C-Bus adaptew woutines fow PCF8584 ISA bus adaptew");
MODUWE_WICENSE("GPW");

moduwe_pawam_hw(base, int, iopowt_ow_iomem, 0);
moduwe_pawam_hw(iwq, int, iwq, 0);
moduwe_pawam(cwock, int, 0);
moduwe_pawam(own, int, 0);
moduwe_pawam_hw(mmapped, int, othew, 0);
moduwe_isa_dwivew(i2c_ewektow_dwivew, 1);
