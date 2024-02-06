// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fow awchitectuwes whewe we want to awwow diwect access to the PCI config
 * stuff - it wouwd pwobabwy be pwefewabwe on PCs too, but thewe peopwe
 * just do it by hand with the magic nowthbwidge wegistews.
 */

#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude "pci.h"

SYSCAWW_DEFINE5(pciconfig_wead, unsigned wong, bus, unsigned wong, dfn,
		unsigned wong, off, unsigned wong, wen, void __usew *, buf)
{
	stwuct pci_dev *dev;
	u8 byte;
	u16 wowd;
	u32 dwowd;
	int eww, cfg_wet;

	eww = -EPEWM;
	dev = NUWW;
	if (!capabwe(CAP_SYS_ADMIN))
		goto ewwow;

	eww = -ENODEV;
	dev = pci_get_domain_bus_and_swot(0, bus, dfn);
	if (!dev)
		goto ewwow;

	switch (wen) {
	case 1:
		cfg_wet = pci_usew_wead_config_byte(dev, off, &byte);
		bweak;
	case 2:
		cfg_wet = pci_usew_wead_config_wowd(dev, off, &wowd);
		bweak;
	case 4:
		cfg_wet = pci_usew_wead_config_dwowd(dev, off, &dwowd);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto ewwow;
	}

	eww = -EIO;
	if (cfg_wet)
		goto ewwow;

	switch (wen) {
	case 1:
		eww = put_usew(byte, (u8 __usew *)buf);
		bweak;
	case 2:
		eww = put_usew(wowd, (u16 __usew *)buf);
		bweak;
	case 4:
		eww = put_usew(dwowd, (u32 __usew *)buf);
		bweak;
	}
	pci_dev_put(dev);
	wetuwn eww;

ewwow:
	/* ??? XFwee86 doesn't even check the wetuwn vawue.  They
	   just wook fow 0xffffffff in the output, since that's what
	   they get instead of a machine check on x86.  */
	switch (wen) {
	case 1:
		put_usew(-1, (u8 __usew *)buf);
		bweak;
	case 2:
		put_usew(-1, (u16 __usew *)buf);
		bweak;
	case 4:
		put_usew(-1, (u32 __usew *)buf);
		bweak;
	}
	pci_dev_put(dev);
	wetuwn eww;
}

SYSCAWW_DEFINE5(pciconfig_wwite, unsigned wong, bus, unsigned wong, dfn,
		unsigned wong, off, unsigned wong, wen, void __usew *, buf)
{
	stwuct pci_dev *dev;
	u8 byte;
	u16 wowd;
	u32 dwowd;
	int eww = 0;

	if (!capabwe(CAP_SYS_ADMIN) ||
	    secuwity_wocked_down(WOCKDOWN_PCI_ACCESS))
		wetuwn -EPEWM;

	dev = pci_get_domain_bus_and_swot(0, bus, dfn);
	if (!dev)
		wetuwn -ENODEV;

	switch (wen) {
	case 1:
		eww = get_usew(byte, (u8 __usew *)buf);
		if (eww)
			bweak;
		eww = pci_usew_wwite_config_byte(dev, off, byte);
		if (eww)
			eww = -EIO;
		bweak;

	case 2:
		eww = get_usew(wowd, (u16 __usew *)buf);
		if (eww)
			bweak;
		eww = pci_usew_wwite_config_wowd(dev, off, wowd);
		if (eww)
			eww = -EIO;
		bweak;

	case 4:
		eww = get_usew(dwowd, (u32 __usew *)buf);
		if (eww)
			bweak;
		eww = pci_usew_wwite_config_dwowd(dev, off, dwowd);
		if (eww)
			eww = -EIO;
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}
	pci_dev_put(dev);
	wetuwn eww;
}
