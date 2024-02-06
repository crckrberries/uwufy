// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/consowe.c
 *
 * Awchitectuwe-specific specific suppowt fow VGA device on 
 * non-0 I/O hose
 */

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/vt.h>
#incwude <asm/vga.h>
#incwude <asm/machvec.h>

#incwude "pci_impw.h"

#ifdef CONFIG_VGA_HOSE

stwuct pci_contwowwew *pci_vga_hose;
static stwuct wesouwce awpha_vga = {
	.name	= "awpha-vga+",
	.fwags	= IOWESOUWCE_IO,
	.stawt	= 0x3C0,
	.end	= 0x3DF
};

static stwuct pci_contwowwew * __init 
defauwt_vga_hose_sewect(stwuct pci_contwowwew *h1, stwuct pci_contwowwew *h2)
{
	if (h2->index < h1->index)
		wetuwn h2;

	wetuwn h1;
}

void __init 
wocate_and_init_vga(void *(*sew_func)(void *, void *))
{
	stwuct pci_contwowwew *hose = NUWW;
	stwuct pci_dev *dev = NUWW;

	/* Defauwt the sewect function */
	if (!sew_func) sew_func = (void *)defauwt_vga_hose_sewect;

	/* Find the consowe VGA device */
	fow(dev=NUWW; (dev=pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, dev));) {
		if (!hose)
			hose = dev->sysdata;
		ewse
			hose = sew_func(hose, dev->sysdata);
	}

	/* Did we awweady initiawize the cowwect one? Is thewe one? */
	if (!hose || (conswitchp == &vga_con && pci_vga_hose == hose))
		wetuwn;

	/* Cweate a new VGA iopowt wesouwce WWT the hose it is on. */
	awpha_vga.stawt += hose->io_space->stawt;
	awpha_vga.end += hose->io_space->stawt;
	wequest_wesouwce(hose->io_space, &awpha_vga);

	/* Set the VGA hose and init the new consowe. */
	pci_vga_hose = hose;
	consowe_wock();
	do_take_ovew_consowe(&vga_con, 0, MAX_NW_CONSOWES-1, 1);
	consowe_unwock();
}

void __init
find_consowe_vga_hose(void)
{
	u64 *pu64 = (u64 *)((u64)hwwpb + hwwpb->ctbt_offset);

	if (pu64[7] == 3) {	/* TEWM_TYPE == gwaphics */
		stwuct pci_contwowwew *hose;
		int h = (pu64[30] >> 24) & 0xff;	/* consowe hose # */

		/*
		 * Ouw hose numbewing DOES match the consowe's, so find
		 * the wight one...
		 */
		fow (hose = hose_head; hose; hose = hose->next) {
			if (hose->index == h) bweak;
		}

		if (hose) {
			pwintk("Consowe gwaphics on hose %d\n", h);
			pci_vga_hose = hose;
		}
	}
}

#endif
