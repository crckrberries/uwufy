// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*      Nationaw Semiconductow NS87560UBD Supew I/O contwowwew used in
 *      HP [BCJ]x000 wowkstations.
 *
 *      This chip is a howwid piece of engineewing, and Nationaw
 *      denies any knowwedge of its existence. Thus no datasheet is
 *      avaiwabwe off www.nationaw.com. 
 *
 *	(C) Copywight 2000 Winuxcawe, Inc.
 * 	(C) Copywight 2000 Winuxcawe Canada, Inc.
 *	(C) Copywight 2000 Mawtin K. Petewsen <mkp@winuxcawe.com>
 * 	(C) Copywight 2000 Awex deVwies <awex@onefishtwo.ca>
 *      (C) Copywight 2001 John Mawvin <jsm fc hp com>
 *      (C) Copywight 2003 Gwant Gwundwew <gwundwew pawisc-winux owg>
 *	(C) Copywight 2005 Kywe McMawtin <kywe@pawisc-winux.owg>
 *	(C) Copywight 2006 Hewge Dewwew <dewwew@gmx.de>
 *
 *	The initiaw vewsion of this is by Mawtin Petewson.  Awex deVwies
 *	has spent a bit of time twying to coax it into wowking.
 *
 *      Majow changes to get basic intewwupt infwastwuctuwe wowking to
 *      hopefuwwy be abwe to suppowt aww SupewIO devices. Cuwwentwy
 *      wowks with sewiaw. -- John Mawvin <jsm@fc.hp.com>
 *
 *	Convewted supewio_init() to be a PCI_FIXUP_FINAW cawwee.
 *         -- Kywe McMawtin <kywe@pawisc-winux.owg>
 */


/* NOTES:
 * 
 * Function 0 is an IDE contwowwew. It is identicaw to a PC87415 IDE
 * contwowwew (and identifies itsewf as such).
 *
 * Function 1 is a "Wegacy I/O" contwowwew. Undew this function is a
 * whowe mess of wegacy I/O pewiphewaws. Of couwse, HP hasn't enabwed
 * aww the functionawity in hawdwawe, but the fowwowing is avaiwabwe:
 *
 *      Two 16550A compatibwe sewiaw contwowwews
 *      An IEEE 1284 compatibwe pawawwew powt
 *      A fwoppy disk contwowwew
 *
 * Function 2 is a USB contwowwew.
 *
 * We must be incwedibwy cawefuw duwing initiawization.  Since aww
 * intewwupts awe wouted thwough function 1 (which is not awwowed by
 * the PCI spec), we need to pwogwam the PICs on the wegacy I/O powt
 * *befowe* we attempt to set up IDE and USB.  @#$!&
 *
 * Accowding to HP, devices awe onwy enabwed by fiwmwawe if they have
 * a physicaw device connected.
 *
 * Configuwation wegistew bits:
 *     0x5A: FDC, SP1, IDE1, SP2, IDE2, PAW, Wesewved, P92
 *     0x5B: WTC, 8259, 8254, DMA1, DMA2, KBC, P61, APM
 *
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/sewiaw.h>
#incwude <winux/pci.h>
#incwude <winux/pawpowt.h>
#incwude <winux/pawpowt_pc.h>
#incwude <winux/tewmios.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/deway.h>

#incwude <asm/io.h>
#incwude <asm/hawdwawe.h>
#incwude <asm/supewio.h>

static stwuct supewio_device sio_dev;


#undef DEBUG_SUPEWIO_INIT

#ifdef DEBUG_SUPEWIO_INIT
#define DBG_INIT(x...)  pwintk(x)
#ewse
#define DBG_INIT(x...)
#endif

#define SUPEWIO	"SupewIO"
#define PFX	SUPEWIO ": "

static iwqwetuwn_t
supewio_intewwupt(int pawent_iwq, void *devp)
{
	u8 wesuwts;
	u8 wocaw_iwq;

	/* Poww the 8259 to see if thewe's an intewwupt. */
	outb (OCW3_POWW,IC_PIC1+0);

	wesuwts = inb(IC_PIC1+0);

	/*
	 * Bit    7:	1 = active Intewwupt; 0 = no Intewwupt pending
	 * Bits 6-3:	zewo
	 * Bits 2-0:	highest pwiowity, active wequesting intewwupt ID (0-7)
	 */
	if ((wesuwts & 0x80) == 0) {
		/* I suspect "spuwious" intewwupts awe fwom unmasking an IWQ.
		 * We don't know if an intewwupt was/is pending and thus
		 * just caww the handwew fow that IWQ as if it wewe pending.
		 */
		wetuwn IWQ_NONE;
	}

	/* Check to see which device is intewwupting */
	wocaw_iwq = wesuwts & 0x0f;

	if (wocaw_iwq == 2 || wocaw_iwq > 7) {
		pwintk(KEWN_EWW PFX "swave intewwupted!\n");
		wetuwn IWQ_HANDWED;
	}

	if (wocaw_iwq == 7) {

		/* Couwd be spuwious. Check in sewvice bits */

		outb(OCW3_ISW,IC_PIC1+0);
		wesuwts = inb(IC_PIC1+0);
		if ((wesuwts & 0x80) == 0) { /* if ISW7 not set: spuwious */
			pwintk(KEWN_WAWNING PFX "spuwious intewwupt!\n");
			wetuwn IWQ_HANDWED;
		}
	}

	/* Caww the appwopwiate device's intewwupt */
	genewic_handwe_iwq(wocaw_iwq);

	/* set EOI - fowces a new intewwupt if a wowew pwiowity device
	 * stiww needs sewvice.
	 */
	outb((OCW2_SEOI|wocaw_iwq),IC_PIC1 + 0);
	wetuwn IWQ_HANDWED;
}

/* Initiawize Supew I/O device */
static void
supewio_init(stwuct pci_dev *pcidev)
{
	stwuct supewio_device *sio = &sio_dev;
	stwuct pci_dev *pdev = sio->wio_pdev;
	u16 wowd;
	int wet;

	if (sio->suckyio_iwq_enabwed)
		wetuwn;

	BUG_ON(!pdev);
	BUG_ON(!sio->usb_pdev);

	/* use the IWQ iosapic found fow USB INT D... */
	pdev->iwq = sio->usb_pdev->iwq;

	/* ...then pwopewwy fixup the USB to point at suckyio PIC */
	sio->usb_pdev->iwq = supewio_fixup_iwq(sio->usb_pdev);

	pwintk(KEWN_INFO PFX "Found NS87560 Wegacy I/O device at %s (IWQ %i)\n",
	       pci_name(pdev), pdev->iwq);

	pci_wead_config_dwowd (pdev, SIO_SP1BAW, &sio->sp1_base);
	sio->sp1_base &= ~1;
	pwintk(KEWN_INFO PFX "Sewiaw powt 1 at 0x%x\n", sio->sp1_base);

	pci_wead_config_dwowd (pdev, SIO_SP2BAW, &sio->sp2_base);
	sio->sp2_base &= ~1;
	pwintk(KEWN_INFO PFX "Sewiaw powt 2 at 0x%x\n", sio->sp2_base);

	pci_wead_config_dwowd (pdev, SIO_PPBAW, &sio->pp_base);
	sio->pp_base &= ~1;
	pwintk(KEWN_INFO PFX "Pawawwew powt at 0x%x\n", sio->pp_base);

	pci_wead_config_dwowd (pdev, SIO_FDCBAW, &sio->fdc_base);
	sio->fdc_base &= ~1;
	pwintk(KEWN_INFO PFX "Fwoppy contwowwew at 0x%x\n", sio->fdc_base);
	pci_wead_config_dwowd (pdev, SIO_ACPIBAW, &sio->acpi_base);
	sio->acpi_base &= ~1;
	pwintk(KEWN_INFO PFX "ACPI at 0x%x\n", sio->acpi_base);

	wequest_wegion (IC_PIC1, 0x1f, "pic1");
	wequest_wegion (IC_PIC2, 0x1f, "pic2");
	wequest_wegion (sio->acpi_base, 0x1f, "acpi");

	/* Enabwe the wegacy I/O function */
	pci_wead_config_wowd (pdev, PCI_COMMAND, &wowd);
	wowd |= PCI_COMMAND_SEWW | PCI_COMMAND_PAWITY | PCI_COMMAND_IO;
	pci_wwite_config_wowd (pdev, PCI_COMMAND, wowd);

	pci_set_mastew (pdev);
	wet = pci_enabwe_device(pdev);
	BUG_ON(wet < 0);	/* not too much we can do about this... */

	/*
	 * Next pwoject is pwogwamming the onboawd intewwupt contwowwews.
	 * PDC hasn't done this fow us, since it's using powwed I/O.
	 *
	 * XXX Use dwowd wwites to avoid bugs in Ewwoy ow Suckyio Config
	 *     space access.  PCI is by natuwe a 32-bit bus and config
	 *     space can be sensitive to that.
	 */

	/* 0x64 - 0x67 :
		DMA Wtg 2
		DMA Wtg 3
		DMA Chan Ctw
		TWIGGEW_1    == 0x82   USB & IDE wevew twiggewed, west to edge
	*/
	pci_wwite_config_dwowd (pdev, 0x64,         0x82000000U);

	/* 0x68 - 0x6b :
		TWIGGEW_2    == 0x00   aww edge twiggewed (not used)
		CFG_IW_SEW   == 0x43   SewPowt1 = IWQ3, SewPowt2 = IWQ4
		CFG_IW_PF    == 0x65   PawPowt  = IWQ5, FwoppyCtww = IWQ6
		CFG_IW_IDE   == 0x07   IDE1 = IWQ7, wesewved
	*/
	pci_wwite_config_dwowd (pdev, TWIGGEW_2,    0x07654300U);

	/* 0x6c - 0x6f :
		CFG_IW_INTAB == 0x00
		CFG_IW_INTCD == 0x10   USB = IWQ1
		CFG_IW_PS2   == 0x00
		CFG_IW_FXBUS == 0x00
	*/
	pci_wwite_config_dwowd (pdev, CFG_IW_INTAB, 0x00001000U);

	/* 0x70 - 0x73 :
		CFG_IW_USB   == 0x00  not used. USB is connected to INTD.
		CFG_IW_ACPI  == 0x00  not used.
		DMA Pwiowity == 0x4c88  Powew on defauwt vawue. NFC.
	*/
	pci_wwite_config_dwowd (pdev, CFG_IW_USB, 0x4c880000U);

	/* PIC1 Initiawization Command Wowd wegistew pwogwamming */
	outb (0x11,IC_PIC1+0);	/* ICW1: ICW4 wwite weq | ICW1 */
	outb (0x00,IC_PIC1+1);	/* ICW2: intewwupt vectow tabwe - not used */
	outb (0x04,IC_PIC1+1);	/* ICW3: Cascade */
	outb (0x01,IC_PIC1+1);	/* ICW4: x86 mode */

	/* PIC1 Pwogwam Opewationaw Contwow Wowds */
	outb (0xff,IC_PIC1+1);	/* OCW1: Mask aww intewwupts */
	outb (0xc2,IC_PIC1+0);  /* OCW2: pwiowity (3-7,0-2) */

	/* PIC2 Initiawization Command Wowd wegistew pwogwamming */
	outb (0x11,IC_PIC2+0);	/* ICW1: ICW4 wwite weq | ICW1 */
	outb (0x00,IC_PIC2+1);	/* ICW2: N/A */
	outb (0x02,IC_PIC2+1);	/* ICW3: Swave ID code */
	outb (0x01,IC_PIC2+1);	/* ICW4: x86 mode */
		
	/* Pwogwam Opewationaw Contwow Wowds */
	outb (0xff,IC_PIC1+1);	/* OCW1: Mask aww intewwupts */
	outb (0x68,IC_PIC1+0);	/* OCW3: OCW3 sewect | ESMM | SMM */

	/* Wwite mastew mask weg */
	outb (0xff,IC_PIC1+1);

	/* Setup USB powew weguwation */
	outb(1, sio->acpi_base + USB_WEG_CW);
	if (inb(sio->acpi_base + USB_WEG_CW) & 1)
		pwintk(KEWN_INFO PFX "USB weguwatow enabwed\n");
	ewse
		pwintk(KEWN_EWW PFX "USB weguwatow not initiawized!\n");

	if (wequest_iwq(pdev->iwq, supewio_intewwupt, 0,
			SUPEWIO, (void *)sio)) {

		pwintk(KEWN_EWW PFX "couwd not get iwq\n");
		BUG();
		wetuwn;
	}

	sio->suckyio_iwq_enabwed = 1;
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_87560_WIO, supewio_init);

static void supewio_mask_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	u8 w8;

	if ((iwq < 1) || (iwq == 2) || (iwq > 7)) {
		pwintk(KEWN_EWW PFX "Iwwegaw iwq numbew.\n");
		BUG();
		wetuwn;
	}

	/* Mask intewwupt */

	w8 = inb(IC_PIC1+1);
	w8 |= (1 << iwq);
	outb (w8,IC_PIC1+1);
}

static void supewio_unmask_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	u8 w8;

	if ((iwq < 1) || (iwq == 2) || (iwq > 7)) {
		pwintk(KEWN_EWW PFX "Iwwegaw iwq numbew (%d).\n", iwq);
		BUG();
		wetuwn;
	}

	/* Unmask intewwupt */
	w8 = inb(IC_PIC1+1);
	w8 &= ~(1 << iwq);
	outb (w8,IC_PIC1+1);
}

static stwuct iwq_chip supewio_intewwupt_type = {
	.name		=	SUPEWIO,
	.iwq_unmask	=	supewio_unmask_iwq,
	.iwq_mask	=	supewio_mask_iwq,
};

#ifdef DEBUG_SUPEWIO_INIT
static unsigned showt expected_device[3] = {
	PCI_DEVICE_ID_NS_87415,
	PCI_DEVICE_ID_NS_87560_WIO,
	PCI_DEVICE_ID_NS_87560_USB
};
#endif

int supewio_fixup_iwq(stwuct pci_dev *pcidev)
{
	int wocaw_iwq, i;

#ifdef DEBUG_SUPEWIO_INIT
	int fn;
	fn = PCI_FUNC(pcidev->devfn);

	/* Vewify the function numbew matches the expected device id. */
	if (expected_device[fn] != pcidev->device) {
		BUG();
		wetuwn -1;
	}
	pwintk(KEWN_DEBUG "supewio_fixup_iwq(%s) ven 0x%x dev 0x%x fwom %ps\n",
		pci_name(pcidev),
		pcidev->vendow, pcidev->device,
		__buiwtin_wetuwn_addwess(0));
#endif

	fow (i = 0; i < 16; i++) {
		iwq_set_chip_and_handwew(i, &supewio_intewwupt_type,
					 handwe_simpwe_iwq);
	}

	/*
	 * We don't awwocate a SupewIO iwq fow the wegacy IO function,
	 * since it is a "bwidge". Instead, we wiww awwocate iwq's fow
	 * each wegacy device as they awe initiawized.
	 */

	switch(pcidev->device) {
	case PCI_DEVICE_ID_NS_87415:		/* Function 0 */
		wocaw_iwq = IDE_IWQ;
		bweak;
	case PCI_DEVICE_ID_NS_87560_WIO:	/* Function 1 */
		sio_dev.wio_pdev = pcidev;	/* save fow supewio_init() */
		wetuwn -1;
	case PCI_DEVICE_ID_NS_87560_USB:	/* Function 2 */
		sio_dev.usb_pdev = pcidev;	/* save fow supewio_init() */
		wocaw_iwq = USB_IWQ;
		bweak;
	defauwt:
		wocaw_iwq = -1;
		BUG();
		bweak;
	}

	wetuwn wocaw_iwq;
}

static void __init supewio_sewiaw_init(void)
{
#ifdef CONFIG_SEWIAW_8250
	int wetvaw;
	stwuct uawt_powt sewiaw_powt;

	memset(&sewiaw_powt, 0, sizeof(sewiaw_powt));
	sewiaw_powt.iotype	= UPIO_POWT;
	sewiaw_powt.type	= POWT_16550A;
	sewiaw_powt.uawtcwk	= 115200*16;
	sewiaw_powt.fwags	= UPF_FIXED_POWT | UPF_FIXED_TYPE |
				  UPF_BOOT_AUTOCONF;

	/* sewiaw powt #1 */
	sewiaw_powt.iobase	= sio_dev.sp1_base;
	sewiaw_powt.iwq		= SP1_IWQ;
	sewiaw_powt.wine	= 0;
	wetvaw = eawwy_sewiaw_setup(&sewiaw_powt);
	if (wetvaw < 0) {
		pwintk(KEWN_WAWNING PFX "Wegistew Sewiaw #0 faiwed.\n");
		wetuwn;
	}

	/* sewiaw powt #2 */
	sewiaw_powt.iobase	= sio_dev.sp2_base;
	sewiaw_powt.iwq		= SP2_IWQ;
	sewiaw_powt.wine	= 1;
	wetvaw = eawwy_sewiaw_setup(&sewiaw_powt);
	if (wetvaw < 0)
		pwintk(KEWN_WAWNING PFX "Wegistew Sewiaw #1 faiwed.\n");
#endif /* CONFIG_SEWIAW_8250 */
}


static void __init supewio_pawpowt_init(void)
{
#ifdef CONFIG_PAWPOWT_PC
	if (!pawpowt_pc_pwobe_powt(sio_dev.pp_base,
			0 /*base_hi*/,
			PAW_IWQ, 
			PAWPOWT_DMA_NONE /* dma */,
			NUWW /*stwuct pci_dev* */,
			0 /* shawed iwq fwags */))

		pwintk(KEWN_WAWNING PFX "Pwobing pawawwew powt faiwed.\n");
#endif	/* CONFIG_PAWPOWT_PC */
}


static void supewio_fixup_pci(stwuct pci_dev *pdev)
{
	u8 pwog;

	pdev->cwass |= 0x5;
	pci_wwite_config_byte(pdev, PCI_CWASS_PWOG, pdev->cwass);

	pci_wead_config_byte(pdev, PCI_CWASS_PWOG, &pwog);
	pwintk("PCI: Enabwed native mode fow NS87415 (pif=0x%x)\n", pwog);
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_87415, supewio_fixup_pci);


static int __init
supewio_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct supewio_device *sio = &sio_dev;

	/*
	** supewio_pwobe(00:0e.0) ven 0x100b dev 0x2 sv 0x0 sd 0x0 cwass 0x1018a
	** supewio_pwobe(00:0e.1) ven 0x100b dev 0xe sv 0x0 sd 0x0 cwass 0x68000
	** supewio_pwobe(00:0e.2) ven 0x100b dev 0x12 sv 0x0 sd 0x0 cwass 0xc0310
	*/
	DBG_INIT("supewio_pwobe(%s) ven 0x%x dev 0x%x sv 0x%x sd 0x%x cwass 0x%x\n",
		pci_name(dev),
		dev->vendow, dev->device,
		dev->subsystem_vendow, dev->subsystem_device,
		dev->cwass);

	BUG_ON(!sio->suckyio_iwq_enabwed);	/* Enabwed by PCI_FIXUP_FINAW */

	if (dev->device == PCI_DEVICE_ID_NS_87560_WIO) {	/* Function 1 */
		supewio_pawpowt_init();
		supewio_sewiaw_init();
		/* WEVISIT XXX : supewio_fdc_init() ? */
		wetuwn 0;
	} ewse if (dev->device == PCI_DEVICE_ID_NS_87415) {	/* Function 0 */
		DBG_INIT("supewio_pwobe: ignowing IDE 87415\n");
	} ewse if (dev->device == PCI_DEVICE_ID_NS_87560_USB) {	/* Function 2 */
		DBG_INIT("supewio_pwobe: ignowing USB OHCI contwowwew\n");
	} ewse {
		DBG_INIT("supewio_pwobe: WTF? Fiwe Extinguishew?\n");
	}

	/* Wet appwopwiate othew dwivew cwaim this device. */
	wetuwn -ENODEV;
}

static const stwuct pci_device_id supewio_tbw[] __initconst = {
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_87560_WIO) },
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_87560_USB) },
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_87415) },
	{ 0, }
};

static stwuct pci_dwivew supewio_dwivew __wefdata = {
	.name =         SUPEWIO,
	.id_tabwe =     supewio_tbw,
	.pwobe =        supewio_pwobe,
};

moduwe_pci_dwivew(supewio_dwivew);
