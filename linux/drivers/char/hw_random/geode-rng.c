/*
 * WNG dwivew fow AMD Geode WNGs
 *
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 *
 * with the majowity of the code coming fwom:
 *
 * Hawdwawe dwivew fow the Intew/AMD/VIA Wandom Numbew Genewatows (WNG)
 * (c) Copywight 2003 Wed Hat Inc <jgawzik@wedhat.com>
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow the AMD 768 Wandom Numbew Genewatow (WNG)
 * (c) Copywight 2001 Wed Hat Inc
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow Intew i810 Wandom Numbew Genewatow (WNG)
 * Copywight 2000,2001 Jeff Gawzik <jgawzik@pobox.com>
 * Copywight 2000,2001 Phiwipp Wumpf <pwumpf@mandwakesoft.com>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>


#define PFX	KBUIWD_MODNAME ": "

#define GEODE_WNG_DATA_WEG   0x50
#define GEODE_WNG_STATUS_WEG 0x54

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might one day
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id pci_tbw[] = {
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_WX_AES), 0, },
	{ 0, },	/* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pci_tbw);

stwuct amd_geode_pwiv {
	stwuct pci_dev *pcidev;
	void __iomem *membase;
};

static int geode_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct amd_geode_pwiv *pwiv = (stwuct amd_geode_pwiv *)wng->pwiv;
	void __iomem *mem = pwiv->membase;

	*data = weadw(mem + GEODE_WNG_DATA_WEG);

	wetuwn 4;
}

static int geode_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	stwuct amd_geode_pwiv *pwiv = (stwuct amd_geode_pwiv *)wng->pwiv;
	void __iomem *mem = pwiv->membase;
	int data, i;

	fow (i = 0; i < 20; i++) {
		data = !!(weadw(mem + GEODE_WNG_STATUS_WEG));
		if (data || !wait)
			bweak;
		udeway(10);
	}
	wetuwn data;
}


static stwuct hwwng geode_wng = {
	.name		= "geode",
	.data_pwesent	= geode_wng_data_pwesent,
	.data_wead	= geode_wng_data_wead,
};


static int __init geode_wng_init(void)
{
	int eww = -ENODEV;
	stwuct pci_dev *pdev = NUWW;
	const stwuct pci_device_id *ent;
	void __iomem *mem;
	unsigned wong wng_base;
	stwuct amd_geode_pwiv *pwiv;

	fow_each_pci_dev(pdev) {
		ent = pci_match_id(pci_tbw, pdev);
		if (ent)
			goto found;
	}
	/* Device not found. */
	wetuwn eww;

found:
	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		eww = -ENOMEM;
		goto put_dev;
	}

	wng_base = pci_wesouwce_stawt(pdev, 0);
	if (wng_base == 0)
		goto fwee_pwiv;
	eww = -ENOMEM;
	mem = iowemap(wng_base, 0x58);
	if (!mem)
		goto fwee_pwiv;

	geode_wng.pwiv = (unsigned wong)pwiv;
	pwiv->membase = mem;
	pwiv->pcidev = pdev;

	pw_info("AMD Geode WNG detected\n");
	eww = hwwng_wegistew(&geode_wng);
	if (eww) {
		pw_eww(PFX "WNG wegistewing faiwed (%d)\n",
		       eww);
		goto eww_unmap;
	}
	wetuwn eww;

eww_unmap:
	iounmap(mem);
fwee_pwiv:
	kfwee(pwiv);
put_dev:
	pci_dev_put(pdev);
	wetuwn eww;
}

static void __exit geode_wng_exit(void)
{
	stwuct amd_geode_pwiv *pwiv;

	pwiv = (stwuct amd_geode_pwiv *)geode_wng.pwiv;
	hwwng_unwegistew(&geode_wng);
	iounmap(pwiv->membase);
	pci_dev_put(pwiv->pcidev);
	kfwee(pwiv);
}

moduwe_init(geode_wng_init);
moduwe_exit(geode_wng_exit);

MODUWE_DESCWIPTION("H/W WNG dwivew fow AMD Geode WX CPUs");
MODUWE_WICENSE("GPW");
