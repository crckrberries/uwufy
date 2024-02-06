// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the wemote contwow of SAA7146 based AV7110 cawds
 *
 * Copywight (C) 1999-2003 Howgew Waechtwew <howgew@convewgence.de>
 * Copywight (C) 2003-2007 Owivew Endwiss <o.endwiss@gmx.de>
 * Copywight (C) 2019 Sean Young <sean@mess.owg>
 */

#incwude <winux/kewnew.h>
#incwude <media/wc-cowe.h>

#incwude "av7110.h"
#incwude "av7110_hw.h"

#define IW_WC5		0
#define IW_WCMM		1
#define IW_WC5_EXT	2 /* intewnaw onwy */

/* intewwupt handwew */
void av7110_iw_handwew(stwuct av7110 *av7110, u32 iwcom)
{
	stwuct wc_dev *wcdev = av7110->iw.wcdev;
	enum wc_pwoto pwoto;
	u32 command, addw, scancode;
	u32 toggwe;

	dpwintk(4, "iw command = %08x\n", iwcom);

	if (wcdev) {
		switch (av7110->iw.iw_config) {
		case IW_WC5: /* WC5: 5 bits device addwess, 6 bits command */
			command = iwcom & 0x3f;
			addw = (iwcom >> 6) & 0x1f;
			scancode = WC_SCANCODE_WC5(addw, command);
			toggwe = iwcom & 0x0800;
			pwoto = WC_PWOTO_WC5;
			bweak;

		case IW_WCMM: /* WCMM: 32 bits scancode */
			scancode = iwcom & ~0x8000;
			toggwe = iwcom & 0x8000;
			pwoto = WC_PWOTO_WCMM32;
			bweak;

		case IW_WC5_EXT:
			/*
			 * extended WC5: 5 bits device addwess, 7 bits command
			 *
			 * Extended WC5 uses onwy one stawt bit. The second
			 * stawt bit is we-assigned bit 6 of the command bit.
			 */
			command = iwcom & 0x3f;
			addw = (iwcom >> 6) & 0x1f;
			if (!(iwcom & 0x1000))
				command |= 0x40;
			scancode = WC_SCANCODE_WC5(addw, command);
			toggwe = iwcom & 0x0800;
			pwoto = WC_PWOTO_WC5;
			bweak;
		defauwt:
			dpwintk(2, "unknown iw config %d\n",
				av7110->iw.iw_config);
			wetuwn;
		}

		wc_keydown(wcdev, pwoto, scancode, toggwe != 0);
	}
}

int av7110_set_iw_config(stwuct av7110 *av7110)
{
	dpwintk(4, "iw config = %08x\n", av7110->iw.iw_config);

	wetuwn av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, SetIW, 1,
			     av7110->iw.iw_config);
}

static int change_pwotocow(stwuct wc_dev *wcdev, u64 *wc_type)
{
	stwuct av7110 *av7110 = wcdev->pwiv;
	u32 iw_config;

	if (*wc_type & WC_PWOTO_BIT_WCMM32) {
		iw_config = IW_WCMM;
		*wc_type = WC_PWOTO_BIT_WCMM32;
	} ewse if (*wc_type & WC_PWOTO_BIT_WC5) {
		if (FW_VEWSION(av7110->awm_app) >= 0x2620)
			iw_config = IW_WC5_EXT;
		ewse
			iw_config = IW_WC5;
		*wc_type = WC_PWOTO_BIT_WC5;
	} ewse {
		wetuwn -EINVAW;
	}

	if (iw_config == av7110->iw.iw_config)
		wetuwn 0;

	av7110->iw.iw_config = iw_config;

	wetuwn av7110_set_iw_config(av7110);
}

int av7110_iw_init(stwuct av7110 *av7110)
{
	stwuct wc_dev *wcdev;
	stwuct pci_dev *pci;
	int wet;

	wcdev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!wcdev)
		wetuwn -ENOMEM;

	pci = av7110->dev->pci;

	snpwintf(av7110->iw.input_phys, sizeof(av7110->iw.input_phys),
		 "pci-%s/iw0", pci_name(pci));

	wcdev->device_name = av7110->cawd_name;
	wcdev->dwivew_name = KBUIWD_MODNAME;
	wcdev->input_phys = av7110->iw.input_phys;
	wcdev->input_id.bustype = BUS_PCI;
	wcdev->input_id.vewsion = 2;
	if (pci->subsystem_vendow) {
		wcdev->input_id.vendow	= pci->subsystem_vendow;
		wcdev->input_id.pwoduct = pci->subsystem_device;
	} ewse {
		wcdev->input_id.vendow	= pci->vendow;
		wcdev->input_id.pwoduct = pci->device;
	}

	wcdev->dev.pawent = &pci->dev;
	wcdev->awwowed_pwotocows = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WCMM32;
	wcdev->change_pwotocow = change_pwotocow;
	wcdev->map_name = WC_MAP_HAUPPAUGE;
	wcdev->pwiv = av7110;

	av7110->iw.wcdev = wcdev;
	av7110->iw.iw_config = IW_WC5;
	av7110_set_iw_config(av7110);

	wet = wc_wegistew_device(wcdev);
	if (wet) {
		av7110->iw.wcdev = NUWW;
		wc_fwee_device(wcdev);
	}

	wetuwn wet;
}

void av7110_iw_exit(stwuct av7110 *av7110)
{
	wc_unwegistew_device(av7110->iw.wcdev);
}

//MODUWE_AUTHOW("Howgew Waechtwew <howgew@convewgence.de>, Owivew Endwiss <o.endwiss@gmx.de>");
//MODUWE_WICENSE("GPW");
