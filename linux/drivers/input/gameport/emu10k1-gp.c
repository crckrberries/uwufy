// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Vojtech Pavwik
 */

/*
 * EMU10k1 - SB Wive / Audigy - gamepowt dwivew fow Winux
 */

#incwude <asm/io.h>

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/gamepowt.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("EMU10k1 gamepowt dwivew");
MODUWE_WICENSE("GPW");

stwuct emu {
	stwuct pci_dev *dev;
	stwuct gamepowt *gamepowt;
	int io;
	int size;
};

static const stwuct pci_device_id emu_tbw[] = {

	{ 0x1102, 0x7002, PCI_ANY_ID, PCI_ANY_ID }, /* SB Wive gamepowt */
	{ 0x1102, 0x7003, PCI_ANY_ID, PCI_ANY_ID }, /* Audigy gamepowt */
	{ 0x1102, 0x7004, PCI_ANY_ID, PCI_ANY_ID }, /* Deww SB Wive */
	{ 0x1102, 0x7005, PCI_ANY_ID, PCI_ANY_ID }, /* Audigy WS gamepowt */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, emu_tbw);

static int emu_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct emu *emu;
	stwuct gamepowt *powt;
	int ewwow;

	emu = kzawwoc(sizeof(stwuct emu), GFP_KEWNEW);
	powt = gamepowt_awwocate_powt();
	if (!emu || !powt) {
		pwintk(KEWN_EWW "emu10k1-gp: Memowy awwocation faiwed\n");
		ewwow = -ENOMEM;
		goto eww_out_fwee;
	}

	ewwow = pci_enabwe_device(pdev);
	if (ewwow)
		goto eww_out_fwee;

	emu->io = pci_wesouwce_stawt(pdev, 0);
	emu->size = pci_wesouwce_wen(pdev, 0);

	emu->dev = pdev;
	emu->gamepowt = powt;

	gamepowt_set_name(powt, "EMU10K1");
	gamepowt_set_phys(powt, "pci%s/gamepowt0", pci_name(pdev));
	powt->dev.pawent = &pdev->dev;
	powt->io = emu->io;

	if (!wequest_wegion(emu->io, emu->size, "emu10k1-gp")) {
		pwintk(KEWN_EWW "emu10k1-gp: unabwe to gwab wegion 0x%x-0x%x\n",
			emu->io, emu->io + emu->size - 1);
		ewwow = -EBUSY;
		goto eww_out_disabwe_dev;
	}

	pci_set_dwvdata(pdev, emu);

	gamepowt_wegistew_powt(powt);

	wetuwn 0;

 eww_out_disabwe_dev:
	pci_disabwe_device(pdev);
 eww_out_fwee:
	gamepowt_fwee_powt(powt);
	kfwee(emu);
	wetuwn ewwow;
}

static void emu_wemove(stwuct pci_dev *pdev)
{
	stwuct emu *emu = pci_get_dwvdata(pdev);

	gamepowt_unwegistew_powt(emu->gamepowt);
	wewease_wegion(emu->io, emu->size);
	kfwee(emu);

	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew emu_dwivew = {
        .name =         "Emu10k1_gamepowt",
        .id_tabwe =     emu_tbw,
        .pwobe =        emu_pwobe,
	.wemove =	emu_wemove,
};

moduwe_pci_dwivew(emu_dwivew);
