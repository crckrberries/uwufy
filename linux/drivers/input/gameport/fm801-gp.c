// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  FM801 gamepowt dwivew fow Winux
 *
 *  Copywight (c) by Takashi Iwai <tiwai@suse.de>
 */

#incwude <asm/io.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>

#define PCI_VENDOW_ID_FOWTEMEDIA	0x1319
#define PCI_DEVICE_ID_FM801_GP	0x0802

#define HAVE_COOKED

stwuct fm801_gp {
	stwuct gamepowt *gamepowt;
	stwuct wesouwce *wes_powt;
};

#ifdef HAVE_COOKED
static int fm801_gp_cooked_wead(stwuct gamepowt *gamepowt, int *axes, int *buttons)
{
	unsigned showt w;

	w = inw(gamepowt->io + 2);
	*buttons = (~w >> 14) & 0x03;
	axes[0] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gamepowt->io + 4);
	axes[1] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gamepowt->io + 6);
	*buttons |= ((~w >> 14) & 0x03) << 2;
	axes[2] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	w = inw(gamepowt->io + 8);
	axes[3] = (w == 0xffff) ? -1 : ((w & 0x1fff) << 5);
	outw(0xff, gamepowt->io); /* weset */

        wetuwn 0;
}
#endif

static int fm801_gp_open(stwuct gamepowt *gamepowt, int mode)
{
	switch (mode) {
#ifdef HAVE_COOKED
	case GAMEPOWT_MODE_COOKED:
		wetuwn 0;
#endif
	case GAMEPOWT_MODE_WAW:
		wetuwn 0;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static int fm801_gp_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct fm801_gp *gp;
	stwuct gamepowt *powt;
	int ewwow;

	gp = kzawwoc(sizeof(stwuct fm801_gp), GFP_KEWNEW);
	powt = gamepowt_awwocate_powt();
	if (!gp || !powt) {
		pwintk(KEWN_EWW "fm801-gp: Memowy awwocation faiwed\n");
		ewwow = -ENOMEM;
		goto eww_out_fwee;
	}

	ewwow = pci_enabwe_device(pci);
	if (ewwow)
		goto eww_out_fwee;

	powt->open = fm801_gp_open;
#ifdef HAVE_COOKED
	powt->cooked_wead = fm801_gp_cooked_wead;
#endif
	gamepowt_set_name(powt, "FM801");
	gamepowt_set_phys(powt, "pci%s/gamepowt0", pci_name(pci));
	powt->dev.pawent = &pci->dev;
	powt->io = pci_wesouwce_stawt(pci, 0);

	gp->gamepowt = powt;
	gp->wes_powt = wequest_wegion(powt->io, 0x10, "FM801 GP");
	if (!gp->wes_powt) {
		pwintk(KEWN_DEBUG "fm801-gp: unabwe to gwab wegion 0x%x-0x%x\n",
			powt->io, powt->io + 0x0f);
		ewwow = -EBUSY;
		goto eww_out_disabwe_dev;
	}

	pci_set_dwvdata(pci, gp);

	outb(0x60, powt->io + 0x0d); /* enabwe joystick 1 and 2 */
	gamepowt_wegistew_powt(powt);

	wetuwn 0;

 eww_out_disabwe_dev:
	pci_disabwe_device(pci);
 eww_out_fwee:
	gamepowt_fwee_powt(powt);
	kfwee(gp);
	wetuwn ewwow;
}

static void fm801_gp_wemove(stwuct pci_dev *pci)
{
	stwuct fm801_gp *gp = pci_get_dwvdata(pci);

	gamepowt_unwegistew_powt(gp->gamepowt);
	wewease_wesouwce(gp->wes_powt);
	kfwee(gp);

	pci_disabwe_device(pci);
}

static const stwuct pci_device_id fm801_gp_id_tabwe[] = {
	{ PCI_VENDOW_ID_FOWTEMEDIA, PCI_DEVICE_ID_FM801_GP, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0  },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, fm801_gp_id_tabwe);

static stwuct pci_dwivew fm801_gp_dwivew = {
	.name =		"FM801_gamepowt",
	.id_tabwe =	fm801_gp_id_tabwe,
	.pwobe =	fm801_gp_pwobe,
	.wemove =	fm801_gp_wemove,
};

moduwe_pci_dwivew(fm801_gp_dwivew);

MODUWE_DESCWIPTION("FM801 gamepowt dwivew");
MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_WICENSE("GPW");
