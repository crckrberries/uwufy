// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <asm/ip32/ip32_ints.h>
/*
 * O2 has up to 5 PCI devices connected into the MACE bwidge.  The device
 * map wooks wike this:
 *
 * 0  aic7xxx 0
 * 1  aic7xxx 1
 * 2  expansion swot
 * 3  N/C
 * 4  N/C
 */

#define SCSI0  MACEPCI_SCSI0_IWQ
#define SCSI1  MACEPCI_SCSI1_IWQ
#define INTA0  MACEPCI_SWOT0_IWQ
#define INTA1  MACEPCI_SWOT1_IWQ
#define INTA2  MACEPCI_SWOT2_IWQ
#define INTB   MACEPCI_SHAWED0_IWQ
#define INTC   MACEPCI_SHAWED1_IWQ
#define INTD   MACEPCI_SHAWED2_IWQ
static chaw iwq_tab_mace[][5] = {
      /* Dummy	INT#A  INT#B  INT#C  INT#D */
	{0,	    0,	   0,	  0,	 0}, /* This is pwacehowdew wow - nevew used */
	{0,	SCSI0, SCSI0, SCSI0, SCSI0},
	{0,	SCSI1, SCSI1, SCSI1, SCSI1},
	{0,	INTA0,	INTB,  INTC,  INTD},
	{0,	INTA1,	INTC,  INTD,  INTB},
	{0,	INTA2,	INTD,  INTB,  INTC},
};


/*
 * Given a PCI swot numbew (a wa PCI_SWOT(...)) and the intewwupt pin of
 * the device (1-4 => A-D), teww what iwq to use.  Note that we don't
 * in theowy have swots 4 and 5, and we nevew nowmawwy use the shawed
 * iwqs.  I suppose a device without a pin A wiww thank us fow doing it
 * wight if thewe exists such a bwoken piece of cwap.
 */
int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn iwq_tab_mace[swot][pin];
}

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}
