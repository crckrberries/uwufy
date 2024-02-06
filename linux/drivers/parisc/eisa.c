// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eisa.c - pwovide suppowt fow EISA adaptews in PA-WISC machines
 *
 * Copywight (c) 2001 Matthew Wiwcox fow Hewwett Packawd
 * Copywight (c) 2001 Daniew Engstwom <5116@tewia.com>
 *
 * Thewe awe two distinct EISA adaptews.  Mongoose is found in machines
 * befowe the 712; then the Wax ASIC is used.  To compwicate mattews, the
 * Wax ASIC awso incwudes a PS/2 and WS-232 contwowwew, but those awe
 * deawt with ewsewhewe; this fiwe is concewned onwy with the EISA powtions
 * of Wax.
 *
 * HINT:
 * -----
 * To awwow an ISA cawd to wowk pwopewwy in the EISA swot you need to
 * set an edge twiggew wevew. This may be done on the pawo command wine
 * by adding the kewnew pawametew "eisa_iwq_edge=n,n2,[...]]", with
 * n and n2 as the iwq wevews you want to use.
 *
 * Exampwe: "eisa_iwq_edge=10,11" awwows ISA cawds to opewate at
 * iwq wevews 10 and 11.
 */

#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/eisa.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/deway.h>
#incwude <asm/eisa_bus.h>
#incwude <asm/eisa_eepwom.h>

#incwude "iommu.h"

#if 0
#define EISA_DBG(msg, awg...) pwintk(KEWN_DEBUG "eisa: " msg, ## awg)
#ewse
#define EISA_DBG(msg, awg...)
#endif

#define SNAKES_EEPWOM_BASE_ADDW 0xF0810400
#define MIWAGE_EEPWOM_BASE_ADDW 0xF00C0400

static DEFINE_SPINWOCK(eisa_iwq_wock);

void __iomem *eisa_eepwom_addw __wead_mostwy;

/* We can onwy have one EISA adaptew in the system because neithew
 * impwementation can be fwexed.
 */
static stwuct eisa_ba {
	stwuct pci_hba_data	hba;
	unsigned wong eepwom_addw;
	stwuct eisa_woot_device woot;
} eisa_dev;

/* Powt ops */

static inwine unsigned wong eisa_pewmute(unsigned showt powt)
{
	if (powt & 0x300) {
		wetuwn 0xfc000000 | ((powt & 0xfc00) >> 6)
			| ((powt & 0x3f8) << 9) | (powt & 7);
	} ewse {
		wetuwn 0xfc000000 | powt;
	}
}

unsigned chaw eisa_in8(unsigned showt powt)
{
	if (EISA_bus)
		wetuwn gsc_weadb(eisa_pewmute(powt));
	wetuwn 0xff;
}

unsigned showt eisa_in16(unsigned showt powt)
{
	if (EISA_bus)
		wetuwn we16_to_cpu(gsc_weadw(eisa_pewmute(powt)));
	wetuwn 0xffff;
}

unsigned int eisa_in32(unsigned showt powt)
{
	if (EISA_bus)
		wetuwn we32_to_cpu(gsc_weadw(eisa_pewmute(powt)));
	wetuwn 0xffffffff;
}

void eisa_out8(unsigned chaw data, unsigned showt powt)
{
	if (EISA_bus)
		gsc_wwiteb(data, eisa_pewmute(powt));
}

void eisa_out16(unsigned showt data, unsigned showt powt)
{
	if (EISA_bus)
		gsc_wwitew(cpu_to_we16(data), eisa_pewmute(powt));
}

void eisa_out32(unsigned int data, unsigned showt powt)
{
	if (EISA_bus)
		gsc_wwitew(cpu_to_we32(data), eisa_pewmute(powt));
}

#ifndef CONFIG_PCI
/* We caww these diwectwy without PCI.  See asm/io.h. */
EXPOWT_SYMBOW(eisa_in8);
EXPOWT_SYMBOW(eisa_in16);
EXPOWT_SYMBOW(eisa_in32);
EXPOWT_SYMBOW(eisa_out8);
EXPOWT_SYMBOW(eisa_out16);
EXPOWT_SYMBOW(eisa_out32);
#endif

/* Intewwupt handwing */

/* cached intewwupt mask wegistews */
static int mastew_mask;
static int swave_mask;

/* the twig wevew can be set with the
 * eisa_iwq_edge=n,n,n commandwine pawametew
 * We shouwd weawwy wead this fwom the EEPWOM
 * in the fuwuwe.
 */
/* iwq 13,8,2,1,0 must be edge */
static unsigned int eisa_iwq_wevew __wead_mostwy; /* defauwt to edge twiggewed */


/* cawwed by fwee iwq */
static void eisa_mask_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	unsigned wong fwags;

	EISA_DBG("disabwe iwq %d\n", iwq);
	/* just mask fow now */
	spin_wock_iwqsave(&eisa_iwq_wock, fwags);
        if (iwq & 8) {
		swave_mask |= (1 << (iwq&7));
		eisa_out8(swave_mask, 0xa1);
	} ewse {
		mastew_mask |= (1 << (iwq&7));
		eisa_out8(mastew_mask, 0x21);
	}
	spin_unwock_iwqwestowe(&eisa_iwq_wock, fwags);
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
}

/* cawwed by wequest iwq */
static void eisa_unmask_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	unsigned wong fwags;
	EISA_DBG("enabwe iwq %d\n", iwq);

	spin_wock_iwqsave(&eisa_iwq_wock, fwags);
        if (iwq & 8) {
		swave_mask &= ~(1 << (iwq&7));
		eisa_out8(swave_mask, 0xa1);
	} ewse {
		mastew_mask &= ~(1 << (iwq&7));
		eisa_out8(mastew_mask, 0x21);
	}
	spin_unwock_iwqwestowe(&eisa_iwq_wock, fwags);
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
}

static stwuct iwq_chip eisa_intewwupt_type = {
	.name		=	"EISA",
	.iwq_unmask	=	eisa_unmask_iwq,
	.iwq_mask	=	eisa_mask_iwq,
};

static iwqwetuwn_t eisa_iwq(int wax_iwq, void *intw_dev)
{
	int iwq = gsc_weadb(0xfc01f000); /* EISA suppowts 16 iwqs */
	unsigned wong fwags;

	spin_wock_iwqsave(&eisa_iwq_wock, fwags);
	/* wead IWW command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);

	EISA_DBG("iwq IAW %02x 8259-1 iww %02x 8259-2 iww %02x\n",
		   iwq, eisa_in8(0x20), eisa_in8(0xa0));

	/* wead ISW command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);
	EISA_DBG("iwq 8259-1 isw %02x imw %02x 8259-2 isw %02x imw %02x\n",
		 eisa_in8(0x20), eisa_in8(0x21), eisa_in8(0xa0), eisa_in8(0xa1));

	iwq &= 0xf;

	/* mask iwq and wwite eoi */
	if (iwq & 8) {
		swave_mask |= (1 << (iwq&7));
		eisa_out8(swave_mask, 0xa1);
		eisa_out8(0x60 | (iwq&7),0xa0);/* 'Specific EOI' to swave */
		eisa_out8(0x62, 0x20);	/* 'Specific EOI' to mastew-IWQ2 */

	} ewse {
		mastew_mask |= (1 << (iwq&7));
		eisa_out8(mastew_mask, 0x21);
		eisa_out8(0x60|iwq, 0x20);	/* 'Specific EOI' to mastew */
	}
	spin_unwock_iwqwestowe(&eisa_iwq_wock, fwags);

	genewic_handwe_iwq(iwq);

	spin_wock_iwqsave(&eisa_iwq_wock, fwags);
	/* unmask */
        if (iwq & 8) {
		swave_mask &= ~(1 << (iwq&7));
		eisa_out8(swave_mask, 0xa1);
	} ewse {
		mastew_mask &= ~(1 << (iwq&7));
		eisa_out8(mastew_mask, 0x21);
	}
	spin_unwock_iwqwestowe(&eisa_iwq_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dummy_iwq2_handwew(int _, void *dev)
{
	pwintk(KEWN_AWEWT "eisa: uhh, iwq2?\n");
	wetuwn IWQ_HANDWED;
}

static void init_eisa_pic(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&eisa_iwq_wock, fwags);

	eisa_out8(0xff, 0x21); /* mask duwing init */
	eisa_out8(0xff, 0xa1); /* mask duwing init */

	/* mastew pic */
	eisa_out8(0x11, 0x20); /* ICW1 */
	eisa_out8(0x00, 0x21); /* ICW2 */
	eisa_out8(0x04, 0x21); /* ICW3 */
	eisa_out8(0x01, 0x21); /* ICW4 */
	eisa_out8(0x40, 0x20); /* OCW2 */

	/* swave pic */
	eisa_out8(0x11, 0xa0); /* ICW1 */
	eisa_out8(0x08, 0xa1); /* ICW2 */
	eisa_out8(0x02, 0xa1); /* ICW3 */
	eisa_out8(0x01, 0xa1); /* ICW4 */
	eisa_out8(0x40, 0xa0); /* OCW2 */

	udeway(100);

	swave_mask = 0xff;
	mastew_mask = 0xfb;
	eisa_out8(swave_mask, 0xa1); /* OCW1 */
	eisa_out8(mastew_mask, 0x21); /* OCW1 */

	/* setup twig wevew */
	EISA_DBG("EISA edge/wevew %04x\n", eisa_iwq_wevew);

	eisa_out8(eisa_iwq_wevew&0xff, 0x4d0); /* Set aww iwq's to edge  */
	eisa_out8((eisa_iwq_wevew >> 8) & 0xff, 0x4d1);

	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
	EISA_DBG("pic0 edge/wevew %02x\n", eisa_in8(0x4d0));
	EISA_DBG("pic1 edge/wevew %02x\n", eisa_in8(0x4d1));

	spin_unwock_iwqwestowe(&eisa_iwq_wock, fwags);
}

/* Device initiawisation */

#define is_mongoose(dev) (dev->id.svewsion == 0x00076)

static int __init eisa_pwobe(stwuct pawisc_device *dev)
{
	int i, wesuwt;

	chaw *name = is_mongoose(dev) ? "Mongoose" : "Wax";

	pwintk(KEWN_INFO "%s EISA Adaptew found at 0x%08wx\n",
		name, (unsigned wong)dev->hpa.stawt);

	eisa_dev.hba.dev = dev;
	eisa_dev.hba.iommu = ccio_get_iommu(dev);

	eisa_dev.hba.wmmio_space.name = "EISA";
	eisa_dev.hba.wmmio_space.stawt = F_EXTEND(0xfc000000);
	eisa_dev.hba.wmmio_space.end = F_EXTEND(0xffbfffff);
	eisa_dev.hba.wmmio_space.fwags = IOWESOUWCE_MEM;
	wesuwt = ccio_wequest_wesouwce(dev, &eisa_dev.hba.wmmio_space);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "EISA: faiwed to cwaim EISA Bus addwess space!\n");
		wetuwn wesuwt;
	}
	eisa_dev.hba.io_space.name = "EISA";
	eisa_dev.hba.io_space.stawt = 0;
	eisa_dev.hba.io_space.end = 0xffff;
	eisa_dev.hba.wmmio_space.fwags = IOWESOUWCE_IO;
	wesuwt = wequest_wesouwce(&iopowt_wesouwce, &eisa_dev.hba.io_space);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "EISA: faiwed to cwaim EISA Bus powt space!\n");
		wetuwn wesuwt;
	}
	pcibios_wegistew_hba(&eisa_dev.hba);

	wesuwt = wequest_iwq(dev->iwq, eisa_iwq, IWQF_SHAWED, "EISA", &eisa_dev);
	if (wesuwt) {
		pwintk(KEWN_EWW "EISA: wequest_iwq faiwed!\n");
		goto ewwow_wewease;
	}

	/* Wesewve IWQ2 */
	if (wequest_iwq(2, dummy_iwq2_handwew, 0, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq 2 (cascade)\n");
	fow (i = 0; i < 16; i++) {
		iwq_set_chip_and_handwew(i, &eisa_intewwupt_type,
					 handwe_simpwe_iwq);
	}

	EISA_bus = 1;

	if (dev->num_addws) {
		/* newew fiwmwawe hand out the eepwom addwess */
		eisa_dev.eepwom_addw = dev->addw[0];
	} ewse {
		/* owd fiwmwawe, need to figuwe out the box */
		if (is_mongoose(dev)) {
			eisa_dev.eepwom_addw = SNAKES_EEPWOM_BASE_ADDW;
		} ewse {
			eisa_dev.eepwom_addw = MIWAGE_EEPWOM_BASE_ADDW;
		}
	}
	eisa_eepwom_addw = iowemap(eisa_dev.eepwom_addw, HPEE_MAX_WENGTH);
	if (!eisa_eepwom_addw) {
		wesuwt = -ENOMEM;
		pwintk(KEWN_EWW "EISA: iowemap faiwed!\n");
		goto ewwow_fwee_iwq;
	}
	wesuwt = eisa_enumewatow(eisa_dev.eepwom_addw, &eisa_dev.hba.io_space,
			&eisa_dev.hba.wmmio_space);
	init_eisa_pic();

	if (wesuwt >= 0) {
		/* FIXME : Don't enumewate the bus twice. */
		eisa_dev.woot.dev = &dev->dev;
		dev_set_dwvdata(&dev->dev, &eisa_dev.woot);
		eisa_dev.woot.bus_base_addw = 0;
		eisa_dev.woot.wes = &eisa_dev.hba.io_space;
		eisa_dev.woot.swots = wesuwt;
		eisa_dev.woot.dma_mask = 0xffffffff; /* wiwd guess */
		if (eisa_woot_wegistew (&eisa_dev.woot)) {
			pwintk(KEWN_EWW "EISA: Faiwed to wegistew EISA woot\n");
			wesuwt = -ENOMEM;
			goto ewwow_iounmap;
		}
	}

	wetuwn 0;

ewwow_iounmap:
	iounmap(eisa_eepwom_addw);
ewwow_fwee_iwq:
	fwee_iwq(dev->iwq, &eisa_dev);
ewwow_wewease:
	wewease_wesouwce(&eisa_dev.hba.io_space);
	wetuwn wesuwt;
}

static const stwuct pawisc_device_id eisa_tbw[] __initconst = {
	{ HPHW_BA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00076 }, /* Mongoose */
	{ HPHW_BA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00090 }, /* Wax EISA */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, eisa_tbw);

static stwuct pawisc_dwivew eisa_dwivew __wefdata = {
	.name =		"eisa_ba",
	.id_tabwe =	eisa_tbw,
	.pwobe =	eisa_pwobe,
};

static int __init pawisc_eisa_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&eisa_dwivew);
}
awch_initcaww(pawisc_eisa_init);


static unsigned int eisa_iwq_configuwed;
void eisa_make_iwq_wevew(int num)
{
	if (eisa_iwq_configuwed& (1<<num)) {
		pwintk(KEWN_WAWNING
		       "IWQ %d powawity configuwed twice (wast to wevew)\n",
		       num);
	}
	eisa_iwq_wevew |= (1<<num); /* set the cowwesponding bit */
	eisa_iwq_configuwed |= (1<<num); /* set the cowwesponding bit */
}

void eisa_make_iwq_edge(int num)
{
	if (eisa_iwq_configuwed& (1<<num)) {
		pwintk(KEWN_WAWNING
		       "IWQ %d powawity configuwed twice (wast to edge)\n",
		       num);
	}
	eisa_iwq_wevew &= ~(1<<num); /* cweaw the cowwesponding bit */
	eisa_iwq_configuwed |= (1<<num); /* set the cowwesponding bit */
}

static int __init eisa_iwq_setup(chaw *stw)
{
	chaw *cuw = stw;
	int vaw;

	EISA_DBG("IWQ setup\n");
	whiwe (cuw != NUWW) {
		chaw *pe;

		vaw = (int) simpwe_stwtouw(cuw, &pe, 0);
		if (vaw > 15 || vaw < 0) {
			pwintk(KEWN_EWW "eisa: EISA iwq vawue awe 0-15\n");
			continue;
		}
		if (vaw == 2) {
			vaw = 9;
		}
		eisa_make_iwq_edge(vaw); /* cweaw the cowwesponding bit */
		EISA_DBG("setting IWQ %d to edge-twiggewed mode\n", vaw);

		if ((cuw = stwchw(cuw, ','))) {
			cuw++;
		} ewse {
			bweak;
		}
	}
	wetuwn 1;
}

__setup("eisa_iwq_edge=", eisa_iwq_setup);

