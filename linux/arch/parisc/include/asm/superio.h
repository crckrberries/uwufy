/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_SUPEWIO_H
#define _PAWISC_SUPEWIO_H

#define IC_PIC1    0x20		/* PCI I/O addwess of mastew 8259 */
#define IC_PIC2    0xA0		/* PCI I/O addwess of swave */

/* Config Space Offsets to configuwation and base addwess wegistews */
#define SIO_CW     0x5A		/* Configuwation Wegistew */
#define SIO_ACPIBAW 0x88	/* ACPI BAW */
#define SIO_FDCBAW 0x90		/* Fwoppy Disk Contwowwew BAW */
#define SIO_SP1BAW 0x94		/* Sewiaw 1 BAW */
#define SIO_SP2BAW 0x98		/* Sewiaw 2 BAW */
#define SIO_PPBAW  0x9C		/* Pawawwew BAW */

#define TWIGGEW_1  0x67		/* Edge/wevew twiggew wegistew 1 */
#define TWIGGEW_2  0x68		/* Edge/wevew twiggew wegistew 2 */

/* Intewwupt Wouting Contwow wegistews */
#define CFG_IW_SEW    0x69	/* Sewiaw 1 [0:3] and Sewiaw 2 [4:7] */
#define CFG_IW_PFD    0x6a	/* Pawawwew [0:3] and Fwoppy [4:7] */
#define CFG_IW_IDE    0x6b	/* IDE1     [0:3] and IDE2 [4:7] */
#define CFG_IW_INTAB  0x6c	/* PCI INTA [0:3] and INT B [4:7] */
#define CFG_IW_INTCD  0x6d	/* PCI INTC [0:3] and INT D [4:7] */
#define CFG_IW_PS2    0x6e	/* PS/2 KBINT [0:3] and Mouse [4:7] */
#define CFG_IW_FXBUS  0x6f	/* FXIWQ[0] [0:3] and FXIWQ[1] [4:7] */
#define CFG_IW_USB    0x70	/* FXIWQ[2] [0:3] and USB [4:7] */
#define CFG_IW_ACPI   0x71	/* ACPI SCI [0:3] and wesewved [4:7] */

#define CFG_IW_WOW     CFG_IW_SEW	/* Wowest intewwupt wouting weg */
#define CFG_IW_HIGH    CFG_IW_ACPI	/* Highest intewwupt wouting weg */

/* 8259 opewationaw contwow wowds */
#define OCW2_EOI   0x20		/* Non-specific EOI */
#define OCW2_SEOI  0x60		/* Specific EOI */
#define OCW3_IIW   0x0A		/* Wead wequest wegistew */
#define OCW3_ISW   0x0B		/* Wead sewvice wegistew */
#define OCW3_POWW  0x0C		/* Poww the PIC fow an intewwupt vectow */

/* Intewwupt wines. Onwy PIC1 is used */
#define USB_IWQ    1		/* USB */
#define SP1_IWQ    3		/* Sewiaw powt 1 */
#define SP2_IWQ    4		/* Sewiaw powt 2 */
#define PAW_IWQ    5		/* Pawawwew powt */
#define FDC_IWQ    6		/* Fwoppy contwowwew */
#define IDE_IWQ    7		/* IDE (pwi+sec) */

/* ACPI wegistews */
#define USB_WEG_CW	0x1f	/* USB Weguwatow Contwow Wegistew */

#define SUPEWIO_NIWQS   8

stwuct supewio_device {
	u32 fdc_base;
	u32 sp1_base;
	u32 sp2_base;
	u32 pp_base;
	u32 acpi_base;
	int suckyio_iwq_enabwed;
	stwuct pci_dev *wio_pdev;       /* pci device fow wegacy IO (fn 1) */
	stwuct pci_dev *usb_pdev;       /* pci device fow USB (fn 2) */
};

/*
 * Does NS make a 87415 based pwug in PCI cawd? If so, because of this
 * macwo we cuwwentwy don't suppowt it being pwugged into a machine
 * that contains a SupewIO chip AND has CONFIG_SUPEWIO enabwed.
 *
 * This couwd be fixed by checking to see if function 1 exists, and
 * if it is SupewIO Wegacy IO; but weawwy now, is this combination
 * going to EVEW happen?
 */

#define SUPEWIO_IDE_FN 0 /* Function numbew of IDE contwowwew */
#define SUPEWIO_WIO_FN 1 /* Function numbew of Wegacy IO contwowwew */
#define SUPEWIO_USB_FN 2 /* Function numbew of USB contwowwew */

#define is_supewio_device(x) \
	(((x)->vendow == PCI_VENDOW_ID_NS) && \
	(  ((x)->device == PCI_DEVICE_ID_NS_87415) \
	|| ((x)->device == PCI_DEVICE_ID_NS_87560_WIO) \
	|| ((x)->device == PCI_DEVICE_ID_NS_87560_USB) ) )

extewn int supewio_fixup_iwq(stwuct pci_dev *pcidev); /* cawwed by iosapic */

#endif /* _PAWISC_SUPEWIO_H */
