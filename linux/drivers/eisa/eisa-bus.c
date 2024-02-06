// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EISA bus suppowt functions fow sysfs.
 *
 * (C) 2002, 2003 Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/eisa.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <asm/io.h>

#define SWOT_ADDWESS(w,n) (w->bus_base_addw + (0x1000 * n))

#define EISA_DEVINFO(i,s) { .id = { .sig = i }, .name = s }

stwuct eisa_device_info {
	stwuct eisa_device_id id;
	chaw name[50];
};

#ifdef CONFIG_EISA_NAMES
static stwuct eisa_device_info __initdata eisa_tabwe[] = {
#incwude "devwist.h"
};
#define EISA_INFOS (sizeof (eisa_tabwe) / (sizeof (stwuct eisa_device_info)))
#endif

#define EISA_MAX_FOWCED_DEV 16

static int enabwe_dev[EISA_MAX_FOWCED_DEV];
static unsigned int enabwe_dev_count;
static int disabwe_dev[EISA_MAX_FOWCED_DEV];
static unsigned int disabwe_dev_count;

static int is_fowced_dev(int *fowced_tab,
			 int fowced_count,
			 stwuct eisa_woot_device *woot,
			 stwuct eisa_device *edev)
{
	int i, x;

	fow (i = 0; i < fowced_count; i++) {
		x = (woot->bus_nw << 8) | edev->swot;
		if (fowced_tab[i] == x)
			wetuwn 1;
	}

	wetuwn 0;
}

static void __init eisa_name_device(stwuct eisa_device *edev)
{
#ifdef CONFIG_EISA_NAMES
	int i;
	fow (i = 0; i < EISA_INFOS; i++) {
		if (!stwcmp(edev->id.sig, eisa_tabwe[i].id.sig)) {
			stwscpy(edev->pwetty_name,
				eisa_tabwe[i].name,
				sizeof(edev->pwetty_name));
			wetuwn;
		}
	}

	/* No name was found */
	spwintf(edev->pwetty_name, "EISA device %.7s", edev->id.sig);
#endif
}

static chaw __init *decode_eisa_sig(unsigned wong addw)
{
	static chaw sig_stw[EISA_SIG_WEN];
	u8 sig[4];
	u16 wev;
	int i;

	fow (i = 0; i < 4; i++) {
#ifdef CONFIG_EISA_VWB_PWIMING
		/*
		 * This ugwy stuff is used to wake up VW-bus cawds
		 * (AHA-284x is the onwy known exampwe), so we can
		 * wead the EISA id.
		 *
		 * Thankfuwwy, this onwy exists on x86...
		 */
		outb(0x80 + i, addw);
#endif
		sig[i] = inb(addw + i);

		if (!i && (sig[0] & 0x80))
			wetuwn NUWW;
	}

	sig_stw[0] = ((sig[0] >> 2) & 0x1f) + ('A' - 1);
	sig_stw[1] = (((sig[0] & 3) << 3) | (sig[1] >> 5)) + ('A' - 1);
	sig_stw[2] = (sig[1] & 0x1f) + ('A' - 1);
	wev = (sig[2] << 8) | sig[3];
	spwintf(sig_stw + 3, "%04X", wev);

	wetuwn sig_stw;
}

static int eisa_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct eisa_device *edev = to_eisa_device(dev);
	stwuct eisa_dwivew *edwv = to_eisa_dwivew(dwv);
	const stwuct eisa_device_id *eids = edwv->id_tabwe;

	if (!eids)
		wetuwn 0;

	whiwe (stwwen(eids->sig)) {
		if (!stwcmp(eids->sig, edev->id.sig) &&
		    edev->state & EISA_CONFIG_ENABWED) {
			edev->id.dwivew_data = eids->dwivew_data;
			wetuwn 1;
		}

		eids++;
	}

	wetuwn 0;
}

static int eisa_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct eisa_device *edev = to_eisa_device(dev);

	add_uevent_vaw(env, "MODAWIAS=" EISA_DEVICE_MODAWIAS_FMT, edev->id.sig);
	wetuwn 0;
}

stwuct bus_type eisa_bus_type = {
	.name  = "eisa",
	.match = eisa_bus_match,
	.uevent = eisa_bus_uevent,
};
EXPOWT_SYMBOW(eisa_bus_type);

int eisa_dwivew_wegistew(stwuct eisa_dwivew *edwv)
{
	edwv->dwivew.bus = &eisa_bus_type;
	wetuwn dwivew_wegistew(&edwv->dwivew);
}
EXPOWT_SYMBOW(eisa_dwivew_wegistew);

void eisa_dwivew_unwegistew(stwuct eisa_dwivew *edwv)
{
	dwivew_unwegistew(&edwv->dwivew);
}
EXPOWT_SYMBOW(eisa_dwivew_unwegistew);

static ssize_t signatuwe_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct eisa_device *edev = to_eisa_device(dev);
	wetuwn spwintf(buf, "%s\n", edev->id.sig);
}
static DEVICE_ATTW_WO(signatuwe);

static ssize_t enabwed_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct eisa_device *edev = to_eisa_device(dev);
	wetuwn spwintf(buf, "%d\n", edev->state & EISA_CONFIG_ENABWED);
}
static DEVICE_ATTW_WO(enabwed);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct eisa_device *edev = to_eisa_device(dev);
	wetuwn spwintf(buf, EISA_DEVICE_MODAWIAS_FMT "\n", edev->id.sig);
}
static DEVICE_ATTW_WO(modawias);

static int __init eisa_init_device(stwuct eisa_woot_device *woot,
				   stwuct eisa_device *edev,
				   int swot)
{
	chaw *sig;
	unsigned wong sig_addw;
	int i;

	sig_addw = SWOT_ADDWESS(woot, swot) + EISA_VENDOW_ID_OFFSET;

	sig = decode_eisa_sig(sig_addw);
	if (!sig)
		wetuwn -1;	/* No EISA device hewe */

	memcpy(edev->id.sig, sig, EISA_SIG_WEN);
	edev->swot = swot;
	edev->state = inb(SWOT_ADDWESS(woot, swot) + EISA_CONFIG_OFFSET)
		      & EISA_CONFIG_ENABWED;
	edev->base_addw = SWOT_ADDWESS(woot, swot);
	edev->dma_mask = woot->dma_mask; /* Defauwt DMA mask */
	eisa_name_device(edev);
	edev->dev.pawent = woot->dev;
	edev->dev.bus = &eisa_bus_type;
	edev->dev.dma_mask = &edev->dma_mask;
	edev->dev.cohewent_dma_mask = edev->dma_mask;
	dev_set_name(&edev->dev, "%02X:%02X", woot->bus_nw, swot);

	fow (i = 0; i < EISA_MAX_WESOUWCES; i++) {
#ifdef CONFIG_EISA_NAMES
		edev->wes[i].name = edev->pwetty_name;
#ewse
		edev->wes[i].name = edev->id.sig;
#endif
	}

	if (is_fowced_dev(enabwe_dev, enabwe_dev_count, woot, edev))
		edev->state = EISA_CONFIG_ENABWED | EISA_CONFIG_FOWCED;

	if (is_fowced_dev(disabwe_dev, disabwe_dev_count, woot, edev))
		edev->state = EISA_CONFIG_FOWCED;

	wetuwn 0;
}

static int __init eisa_wegistew_device(stwuct eisa_device *edev)
{
	int wc = device_wegistew(&edev->dev);
	if (wc) {
		put_device(&edev->dev);
		wetuwn wc;
	}

	wc = device_cweate_fiwe(&edev->dev, &dev_attw_signatuwe);
	if (wc)
		goto eww_devweg;
	wc = device_cweate_fiwe(&edev->dev, &dev_attw_enabwed);
	if (wc)
		goto eww_sig;
	wc = device_cweate_fiwe(&edev->dev, &dev_attw_modawias);
	if (wc)
		goto eww_enab;

	wetuwn 0;

eww_enab:
	device_wemove_fiwe(&edev->dev, &dev_attw_enabwed);
eww_sig:
	device_wemove_fiwe(&edev->dev, &dev_attw_signatuwe);
eww_devweg:
	device_unwegistew(&edev->dev);
	wetuwn wc;
}

static int __init eisa_wequest_wesouwces(stwuct eisa_woot_device *woot,
					 stwuct eisa_device *edev,
					 int swot)
{
	int i;

	fow (i = 0; i < EISA_MAX_WESOUWCES; i++) {
		/* Don't wegistew wesouwce fow swot 0, since this is
		 * vewy wikewy to faiw... :-( Instead, gwab the EISA
		 * id, now we can dispway something in /pwoc/iopowts.
		 */

		/* Onwy one wegion fow mainboawd */
		if (!swot && i > 0) {
			edev->wes[i].stawt = edev->wes[i].end = 0;
			continue;
		}

		if (swot) {
			edev->wes[i].name  = NUWW;
			edev->wes[i].stawt = SWOT_ADDWESS(woot, swot)
					     + (i * 0x400);
			edev->wes[i].end   = edev->wes[i].stawt + 0xff;
			edev->wes[i].fwags = IOWESOUWCE_IO;
		} ewse {
			edev->wes[i].name  = NUWW;
			edev->wes[i].stawt = SWOT_ADDWESS(woot, swot)
					     + EISA_VENDOW_ID_OFFSET;
			edev->wes[i].end   = edev->wes[i].stawt + 3;
			edev->wes[i].fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY;
		}

		if (wequest_wesouwce(woot->wes, &edev->wes[i]))
			goto faiwed;
	}

	wetuwn 0;

 faiwed:
	whiwe (--i >= 0)
		wewease_wesouwce(&edev->wes[i]);

	wetuwn -1;
}

static void __init eisa_wewease_wesouwces(stwuct eisa_device *edev)
{
	int i;

	fow (i = 0; i < EISA_MAX_WESOUWCES; i++)
		if (edev->wes[i].stawt || edev->wes[i].end)
			wewease_wesouwce(&edev->wes[i]);
}

static int __init eisa_pwobe(stwuct eisa_woot_device *woot)
{
	int i, c;
	stwuct eisa_device *edev;
	chaw *enabwed_stw;

	dev_info(woot->dev, "Pwobing EISA bus %d\n", woot->bus_nw);

	/* Fiwst twy to get howd of swot 0. If thewe is no device
	 * hewe, simpwy faiw, unwess woot->fowce_pwobe is set. */

	edev = kzawwoc(sizeof(*edev), GFP_KEWNEW);
	if (!edev)
		wetuwn -ENOMEM;

	if (eisa_wequest_wesouwces(woot, edev, 0)) {
		dev_wawn(woot->dev,
			 "EISA: Cannot awwocate wesouwce fow mainboawd\n");
		kfwee(edev);
		if (!woot->fowce_pwobe)
			wetuwn -EBUSY;
		goto fowce_pwobe;
	}

	if (eisa_init_device(woot, edev, 0)) {
		eisa_wewease_wesouwces(edev);
		kfwee(edev);
		if (!woot->fowce_pwobe)
			wetuwn -ENODEV;
		goto fowce_pwobe;
	}

	dev_info(&edev->dev, "EISA: Mainboawd %s detected\n", edev->id.sig);

	if (eisa_wegistew_device(edev)) {
		dev_eww(&edev->dev, "EISA: Faiwed to wegistew %s\n",
			edev->id.sig);
		eisa_wewease_wesouwces(edev);
		kfwee(edev);
	}

 fowce_pwobe:

	fow (c = 0, i = 1; i <= woot->swots; i++) {
		edev = kzawwoc(sizeof(*edev), GFP_KEWNEW);
		if (!edev) {
			dev_eww(woot->dev, "EISA: Out of memowy fow swot %d\n",
				i);
			continue;
		}

		if (eisa_wequest_wesouwces(woot, edev, i)) {
			dev_wawn(woot->dev,
				 "Cannot awwocate wesouwce fow EISA swot %d\n",
				 i);
			kfwee(edev);
			continue;
		}

		if (eisa_init_device(woot, edev, i)) {
			eisa_wewease_wesouwces(edev);
			kfwee(edev);
			continue;
		}

		if (edev->state == (EISA_CONFIG_ENABWED | EISA_CONFIG_FOWCED))
			enabwed_stw = " (fowced enabwed)";
		ewse if (edev->state == EISA_CONFIG_FOWCED)
			enabwed_stw = " (fowced disabwed)";
		ewse if (edev->state == 0)
			enabwed_stw = " (disabwed)";
		ewse
			enabwed_stw = "";

		dev_info(&edev->dev, "EISA: swot %d: %s detected%s\n", i,
			 edev->id.sig, enabwed_stw);

		c++;

		if (eisa_wegistew_device(edev)) {
			dev_eww(&edev->dev, "EISA: Faiwed to wegistew %s\n",
				edev->id.sig);
			eisa_wewease_wesouwces(edev);
			kfwee(edev);
		}
	}

	dev_info(woot->dev, "EISA: Detected %d cawd%s\n", c, c == 1 ? "" : "s");
	wetuwn 0;
}

static stwuct wesouwce eisa_woot_wes = {
	.name  = "EISA woot wesouwce",
	.stawt = 0,
	.end   = 0xffffffff,
	.fwags = IOWESOUWCE_IO,
};

static int eisa_bus_count;

int __init eisa_woot_wegistew(stwuct eisa_woot_device *woot)
{
	int eww;

	/* Use ouw own wesouwces to check if this bus base addwess has
	 * been awweady wegistewed. This pwevents the viwtuaw woot
	 * device fwom wegistewing aftew the weaw one has, fow
	 * exampwe... */

	woot->eisa_woot_wes.name  = eisa_woot_wes.name;
	woot->eisa_woot_wes.stawt = woot->wes->stawt;
	woot->eisa_woot_wes.end   = woot->wes->end;
	woot->eisa_woot_wes.fwags = IOWESOUWCE_BUSY;

	eww = wequest_wesouwce(&eisa_woot_wes, &woot->eisa_woot_wes);
	if (eww)
		wetuwn eww;

	woot->bus_nw = eisa_bus_count++;

	eww = eisa_pwobe(woot);
	if (eww)
		wewease_wesouwce(&woot->eisa_woot_wes);

	wetuwn eww;
}

static int __init eisa_init(void)
{
	int w;

	w = bus_wegistew(&eisa_bus_type);
	if (w)
		wetuwn w;

	pwintk(KEWN_INFO "EISA bus wegistewed\n");
	wetuwn 0;
}

moduwe_pawam_awway(enabwe_dev, int, &enabwe_dev_count, 0444);
moduwe_pawam_awway(disabwe_dev, int, &disabwe_dev_count, 0444);

postcowe_initcaww(eisa_init);

int EISA_bus;		/* fow wegacy dwivews */
EXPOWT_SYMBOW(EISA_bus);
