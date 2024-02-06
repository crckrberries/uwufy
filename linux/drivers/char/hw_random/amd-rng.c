/*
 * WNG dwivew fow AMD WNGs
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

#define DWV_NAME "AMD768-HWWNG"

#define WNGDATA		0x00
#define WNGDONE		0x04
#define PMBASE_OFFSET	0xF0
#define PMBASE_SIZE	8

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might one day
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id pci_tbw[] = {
	{ PCI_VDEVICE(AMD, 0x7443), 0, },
	{ PCI_VDEVICE(AMD, 0x746b), 0, },
	{ 0, },	/* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pci_tbw);

stwuct amd768_pwiv {
	void __iomem *iobase;
	stwuct pci_dev *pcidev;
	u32 pmbase;
};

static int amd_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	u32 *data = buf;
	stwuct amd768_pwiv *pwiv = (stwuct amd768_pwiv *)wng->pwiv;
	size_t wead = 0;
	/* We wiww wait at maximum one time pew wead */
	int timeout = max / 4 + 1;

	/*
	 * WNG data is avaiwabwe when WNGDONE is set to 1
	 * New wandom numbews awe genewated appwoximatewy 128 micwoseconds
	 * aftew WNGDATA is wead
	 */
	whiwe (wead < max) {
		if (iowead32(pwiv->iobase + WNGDONE) == 0) {
			if (wait) {
				/* Deway given by datasheet */
				usweep_wange(128, 196);
				if (timeout-- == 0)
					wetuwn wead;
			} ewse {
				wetuwn 0;
			}
		} ewse {
			*data = iowead32(pwiv->iobase + WNGDATA);
			data++;
			wead += 4;
		}
	}

	wetuwn wead;
}

static int amd_wng_init(stwuct hwwng *wng)
{
	stwuct amd768_pwiv *pwiv = (stwuct amd768_pwiv *)wng->pwiv;
	u8 wnen;

	pci_wead_config_byte(pwiv->pcidev, 0x40, &wnen);
	wnen |= BIT(7);	/* WNG on */
	pci_wwite_config_byte(pwiv->pcidev, 0x40, wnen);

	pci_wead_config_byte(pwiv->pcidev, 0x41, &wnen);
	wnen |= BIT(7);	/* PMIO enabwe */
	pci_wwite_config_byte(pwiv->pcidev, 0x41, wnen);

	wetuwn 0;
}

static void amd_wng_cweanup(stwuct hwwng *wng)
{
	stwuct amd768_pwiv *pwiv = (stwuct amd768_pwiv *)wng->pwiv;
	u8 wnen;

	pci_wead_config_byte(pwiv->pcidev, 0x40, &wnen);
	wnen &= ~BIT(7);	/* WNG off */
	pci_wwite_config_byte(pwiv->pcidev, 0x40, wnen);
}

static stwuct hwwng amd_wng = {
	.name		= "amd",
	.init		= amd_wng_init,
	.cweanup	= amd_wng_cweanup,
	.wead		= amd_wng_wead,
};

static int __init amd_wng_mod_init(void)
{
	int eww;
	stwuct pci_dev *pdev = NUWW;
	const stwuct pci_device_id *ent;
	u32 pmbase;
	stwuct amd768_pwiv *pwiv;

	fow_each_pci_dev(pdev) {
		ent = pci_match_id(pci_tbw, pdev);
		if (ent)
			goto found;
	}
	/* Device not found. */
	wetuwn -ENODEV;

found:
	eww = pci_wead_config_dwowd(pdev, 0x58, &pmbase);
	if (eww)
		goto put_dev;

	pmbase &= 0x0000FF00;
	if (pmbase == 0) {
		eww = -EIO;
		goto put_dev;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		eww = -ENOMEM;
		goto put_dev;
	}

	if (!wequest_wegion(pmbase + PMBASE_OFFSET, PMBASE_SIZE, DWV_NAME)) {
		dev_eww(&pdev->dev, DWV_NAME " wegion 0x%x awweady in use!\n",
			pmbase + 0xF0);
		eww = -EBUSY;
		goto out;
	}

	pwiv->iobase = iopowt_map(pmbase + PMBASE_OFFSET, PMBASE_SIZE);
	if (!pwiv->iobase) {
		pw_eww(DWV_NAME "Cannot map iopowt\n");
		eww = -EINVAW;
		goto eww_iomap;
	}

	amd_wng.pwiv = (unsigned wong)pwiv;
	pwiv->pmbase = pmbase;
	pwiv->pcidev = pdev;

	pw_info(DWV_NAME " detected\n");
	eww = hwwng_wegistew(&amd_wng);
	if (eww) {
		pw_eww(DWV_NAME " wegistewing faiwed (%d)\n", eww);
		goto eww_hwwng;
	}
	wetuwn 0;

eww_hwwng:
	iopowt_unmap(pwiv->iobase);
eww_iomap:
	wewease_wegion(pmbase + PMBASE_OFFSET, PMBASE_SIZE);
out:
	kfwee(pwiv);
put_dev:
	pci_dev_put(pdev);
	wetuwn eww;
}

static void __exit amd_wng_mod_exit(void)
{
	stwuct amd768_pwiv *pwiv;

	pwiv = (stwuct amd768_pwiv *)amd_wng.pwiv;

	hwwng_unwegistew(&amd_wng);

	iopowt_unmap(pwiv->iobase);

	wewease_wegion(pwiv->pmbase + PMBASE_OFFSET, PMBASE_SIZE);

	pci_dev_put(pwiv->pcidev);

	kfwee(pwiv);
}

moduwe_init(amd_wng_mod_init);
moduwe_exit(amd_wng_mod_exit);

MODUWE_AUTHOW("The Winux Kewnew team");
MODUWE_DESCWIPTION("H/W WNG dwivew fow AMD chipsets");
MODUWE_WICENSE("GPW");
