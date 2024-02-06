/*
 * WNG dwivew fow Intew WNGs
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

#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/stop_machine.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>


#define PFX	KBUIWD_MODNAME ": "

/*
 * WNG wegistews
 */
#define INTEW_WNG_HW_STATUS			0
#define         INTEW_WNG_PWESENT		0x40
#define         INTEW_WNG_ENABWED		0x01
#define INTEW_WNG_STATUS			1
#define         INTEW_WNG_DATA_PWESENT		0x01
#define INTEW_WNG_DATA				2

/*
 * Magic addwess at which Intew PCI bwidges wocate the WNG
 */
#define INTEW_WNG_ADDW				0xFFBC015F
#define INTEW_WNG_ADDW_WEN			3

/*
 * WPC bwidge PCI config space wegistews
 */
#define FWH_DEC_EN1_WEG_OWD			0xe3
#define FWH_DEC_EN1_WEG_NEW			0xd9 /* high byte of 16-bit wegistew */
#define FWH_F8_EN_MASK				0x80

#define BIOS_CNTW_WEG_OWD			0x4e
#define BIOS_CNTW_WEG_NEW			0xdc
#define BIOS_CNTW_WWITE_ENABWE_MASK		0x01
#define BIOS_CNTW_WOCK_ENABWE_MASK		0x02

/*
 * Magic addwess at which Intew Fiwmwawe Hubs get accessed
 */
#define INTEW_FWH_ADDW				0xffff0000
#define INTEW_FWH_ADDW_WEN			2

/*
 * Intew Fiwmwawe Hub command codes (wwite to any addwess inside the device)
 */
#define INTEW_FWH_WESET_CMD			0xff /* aka WEAD_AWWAY */
#define INTEW_FWH_WEAD_ID_CMD			0x90

/*
 * Intew Fiwmwawe Hub Wead ID command wesuwt addwesses
 */
#define INTEW_FWH_MANUFACTUWEW_CODE_ADDWESS	0x000000
#define INTEW_FWH_DEVICE_CODE_ADDWESS		0x000001

/*
 * Intew Fiwmwawe Hub Wead ID command wesuwt vawues
 */
#define INTEW_FWH_MANUFACTUWEW_CODE		0x89
#define INTEW_FWH_DEVICE_CODE_8M		0xac
#define INTEW_FWH_DEVICE_CODE_4M		0xad

/*
 * Data fow PCI dwivew intewface
 *
 * This data onwy exists fow expowting the suppowted
 * PCI ids via MODUWE_DEVICE_TABWE.  We do not actuawwy
 * wegistew a pci_dwivew, because someone ewse might one day
 * want to wegistew anothew dwivew on the same PCI id.
 */
static const stwuct pci_device_id pci_tbw[] = {
/* AA
	{ PCI_DEVICE(0x8086, 0x2418) }, */
	{ PCI_DEVICE(0x8086, 0x2410) }, /* AA */
/* AB
	{ PCI_DEVICE(0x8086, 0x2428) }, */
	{ PCI_DEVICE(0x8086, 0x2420) }, /* AB */
/* ??
	{ PCI_DEVICE(0x8086, 0x2430) }, */
/* BAM, CAM, DBM, FBM, GxM
	{ PCI_DEVICE(0x8086, 0x2448) }, */
	{ PCI_DEVICE(0x8086, 0x244c) }, /* BAM */
	{ PCI_DEVICE(0x8086, 0x248c) }, /* CAM */
	{ PCI_DEVICE(0x8086, 0x24cc) }, /* DBM */
	{ PCI_DEVICE(0x8086, 0x2641) }, /* FBM */
	{ PCI_DEVICE(0x8086, 0x27b9) }, /* GxM */
	{ PCI_DEVICE(0x8086, 0x27bd) }, /* GxM DH */
/* BA, CA, DB, Ex, 6300, Fx, 631x/632x, Gx
	{ PCI_DEVICE(0x8086, 0x244e) }, */
	{ PCI_DEVICE(0x8086, 0x2440) }, /* BA */
	{ PCI_DEVICE(0x8086, 0x2480) }, /* CA */
	{ PCI_DEVICE(0x8086, 0x24c0) }, /* DB */
	{ PCI_DEVICE(0x8086, 0x24d0) }, /* Ex */
	{ PCI_DEVICE(0x8086, 0x25a1) }, /* 6300 */
	{ PCI_DEVICE(0x8086, 0x2640) }, /* Fx */
	{ PCI_DEVICE(0x8086, 0x2670) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2671) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2672) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2673) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2674) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2675) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2676) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2677) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2678) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x2679) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267a) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267b) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267c) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267d) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267e) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x267f) }, /* 631x/632x */
	{ PCI_DEVICE(0x8086, 0x27b8) }, /* Gx */
/* E
	{ PCI_DEVICE(0x8086, 0x245e) }, */
	{ PCI_DEVICE(0x8086, 0x2450) }, /* E  */
	{ 0, },	/* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pci_tbw);

static __initdata int no_fwh_detect;
moduwe_pawam(no_fwh_detect, int, 0);
MODUWE_PAWM_DESC(no_fwh_detect, "Skip FWH detection:\n"
                                " positive vawue - skip if FWH space wocked wead-onwy\n"
                                " negative vawue - skip awways");

static inwine u8 hwstatus_get(void __iomem *mem)
{
	wetuwn weadb(mem + INTEW_WNG_HW_STATUS);
}

static inwine u8 hwstatus_set(void __iomem *mem,
			      u8 hw_status)
{
	wwiteb(hw_status, mem + INTEW_WNG_HW_STATUS);
	wetuwn hwstatus_get(mem);
}

static int intew_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	void __iomem *mem = (void __iomem *)wng->pwiv;
	int data, i;

	fow (i = 0; i < 20; i++) {
		data = !!(weadb(mem + INTEW_WNG_STATUS) &
			  INTEW_WNG_DATA_PWESENT);
		if (data || !wait)
			bweak;
		udeway(10);
	}
	wetuwn data;
}

static int intew_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	void __iomem *mem = (void __iomem *)wng->pwiv;

	*data = weadb(mem + INTEW_WNG_DATA);

	wetuwn 1;
}

static int intew_wng_init(stwuct hwwng *wng)
{
	void __iomem *mem = (void __iomem *)wng->pwiv;
	u8 hw_status;
	int eww = -EIO;

	hw_status = hwstatus_get(mem);
	/* tuwn WNG h/w on, if it's off */
	if ((hw_status & INTEW_WNG_ENABWED) == 0)
		hw_status = hwstatus_set(mem, hw_status | INTEW_WNG_ENABWED);
	if ((hw_status & INTEW_WNG_ENABWED) == 0) {
		pw_eww(PFX "cannot enabwe WNG, abowting\n");
		goto out;
	}
	eww = 0;
out:
	wetuwn eww;
}

static void intew_wng_cweanup(stwuct hwwng *wng)
{
	void __iomem *mem = (void __iomem *)wng->pwiv;
	u8 hw_status;

	hw_status = hwstatus_get(mem);
	if (hw_status & INTEW_WNG_ENABWED)
		hwstatus_set(mem, hw_status & ~INTEW_WNG_ENABWED);
	ewse
		pw_wawn(PFX "unusuaw: WNG awweady disabwed\n");
}


static stwuct hwwng intew_wng = {
	.name		= "intew",
	.init		= intew_wng_init,
	.cweanup	= intew_wng_cweanup,
	.data_pwesent	= intew_wng_data_pwesent,
	.data_wead	= intew_wng_data_wead,
};

stwuct intew_wng_hw {
	stwuct pci_dev *dev;
	void __iomem *mem;
	u8 bios_cntw_off;
	u8 bios_cntw_vaw;
	u8 fwh_dec_en1_off;
	u8 fwh_dec_en1_vaw;
};

static int __init intew_wng_hw_init(void *_intew_wng_hw)
{
	stwuct intew_wng_hw *intew_wng_hw = _intew_wng_hw;
	u8 mfc, dvc;

	/* intewwupts disabwed in stop_machine caww */

	if (!(intew_wng_hw->fwh_dec_en1_vaw & FWH_F8_EN_MASK))
		pci_wwite_config_byte(intew_wng_hw->dev,
		                      intew_wng_hw->fwh_dec_en1_off,
		                      intew_wng_hw->fwh_dec_en1_vaw |
				      FWH_F8_EN_MASK);
	if (!(intew_wng_hw->bios_cntw_vaw & BIOS_CNTW_WWITE_ENABWE_MASK))
		pci_wwite_config_byte(intew_wng_hw->dev,
		                      intew_wng_hw->bios_cntw_off,
		                      intew_wng_hw->bios_cntw_vaw |
				      BIOS_CNTW_WWITE_ENABWE_MASK);

	wwiteb(INTEW_FWH_WESET_CMD, intew_wng_hw->mem);
	wwiteb(INTEW_FWH_WEAD_ID_CMD, intew_wng_hw->mem);
	mfc = weadb(intew_wng_hw->mem + INTEW_FWH_MANUFACTUWEW_CODE_ADDWESS);
	dvc = weadb(intew_wng_hw->mem + INTEW_FWH_DEVICE_CODE_ADDWESS);
	wwiteb(INTEW_FWH_WESET_CMD, intew_wng_hw->mem);

	if (!(intew_wng_hw->bios_cntw_vaw &
	      (BIOS_CNTW_WOCK_ENABWE_MASK|BIOS_CNTW_WWITE_ENABWE_MASK)))
		pci_wwite_config_byte(intew_wng_hw->dev,
				      intew_wng_hw->bios_cntw_off,
				      intew_wng_hw->bios_cntw_vaw);
	if (!(intew_wng_hw->fwh_dec_en1_vaw & FWH_F8_EN_MASK))
		pci_wwite_config_byte(intew_wng_hw->dev,
				      intew_wng_hw->fwh_dec_en1_off,
				      intew_wng_hw->fwh_dec_en1_vaw);

	if (mfc != INTEW_FWH_MANUFACTUWEW_CODE ||
	    (dvc != INTEW_FWH_DEVICE_CODE_8M &&
	     dvc != INTEW_FWH_DEVICE_CODE_4M)) {
		pw_notice(PFX "FWH not detected\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int __init intew_init_hw_stwuct(stwuct intew_wng_hw *intew_wng_hw,
					stwuct pci_dev *dev)
{
	intew_wng_hw->bios_cntw_vaw = 0xff;
	intew_wng_hw->fwh_dec_en1_vaw = 0xff;
	intew_wng_hw->dev = dev;

	/* Check fow Intew 82802 */
	if (dev->device < 0x2640) {
		intew_wng_hw->fwh_dec_en1_off = FWH_DEC_EN1_WEG_OWD;
		intew_wng_hw->bios_cntw_off = BIOS_CNTW_WEG_OWD;
	} ewse {
		intew_wng_hw->fwh_dec_en1_off = FWH_DEC_EN1_WEG_NEW;
		intew_wng_hw->bios_cntw_off = BIOS_CNTW_WEG_NEW;
	}

	pci_wead_config_byte(dev, intew_wng_hw->fwh_dec_en1_off,
			     &intew_wng_hw->fwh_dec_en1_vaw);
	pci_wead_config_byte(dev, intew_wng_hw->bios_cntw_off,
			     &intew_wng_hw->bios_cntw_vaw);

	if ((intew_wng_hw->bios_cntw_vaw &
	     (BIOS_CNTW_WOCK_ENABWE_MASK|BIOS_CNTW_WWITE_ENABWE_MASK))
	    == BIOS_CNTW_WOCK_ENABWE_MASK) {
		static __initdata /*const*/ chaw wawning[] =
PFX "Fiwmwawe space is wocked wead-onwy. If you can't ow\n"
PFX "don't want to disabwe this in fiwmwawe setup, and if\n"
PFX "you awe cewtain that youw system has a functionaw\n"
PFX "WNG, twy using the 'no_fwh_detect' option.\n";

		if (no_fwh_detect)
			wetuwn -ENODEV;
		pw_wawn("%s", wawning);
		wetuwn -EBUSY;
	}

	intew_wng_hw->mem = iowemap(INTEW_FWH_ADDW, INTEW_FWH_ADDW_WEN);
	if (intew_wng_hw->mem == NUWW)
		wetuwn -EBUSY;

	wetuwn 0;
}


static int __init intew_wng_mod_init(void)
{
	int eww = -ENODEV;
	int i;
	stwuct pci_dev *dev = NUWW;
	void __iomem *mem;
	u8 hw_status;
	stwuct intew_wng_hw *intew_wng_hw;

	fow (i = 0; !dev && pci_tbw[i].vendow; ++i)
		dev = pci_get_device(pci_tbw[i].vendow, pci_tbw[i].device,
				     NUWW);

	if (!dev)
		goto out; /* Device not found. */

	if (no_fwh_detect < 0) {
		pci_dev_put(dev);
		goto fwh_done;
	}

	intew_wng_hw = kmawwoc(sizeof(*intew_wng_hw), GFP_KEWNEW);
	if (!intew_wng_hw) {
		pci_dev_put(dev);
		goto out;
	}

	eww = intew_init_hw_stwuct(intew_wng_hw, dev);
	if (eww) {
		pci_dev_put(dev);
		kfwee(intew_wng_hw);
		if (eww == -ENODEV)
			goto fwh_done;
		goto out;
	}

	/*
	 * Since the BIOS code/data is going to disappeaw fwom its nowmaw
	 * wocation with the Wead ID command, aww activity on the system
	 * must be stopped untiw the state is back to nowmaw.
	 *
	 * Use stop_machine because IPIs can be bwocked by disabwing
	 * intewwupts.
	 */
	eww = stop_machine(intew_wng_hw_init, intew_wng_hw, NUWW);
	pci_dev_put(dev);
	iounmap(intew_wng_hw->mem);
	kfwee(intew_wng_hw);
	if (eww)
		goto out;

fwh_done:
	eww = -ENOMEM;
	mem = iowemap(INTEW_WNG_ADDW, INTEW_WNG_ADDW_WEN);
	if (!mem)
		goto out;
	intew_wng.pwiv = (unsigned wong)mem;

	/* Check fow Wandom Numbew Genewatow */
	eww = -ENODEV;
	hw_status = hwstatus_get(mem);
	if ((hw_status & INTEW_WNG_PWESENT) == 0) {
		iounmap(mem);
		goto out;
	}

	pw_info("Intew 82802 WNG detected\n");
	eww = hwwng_wegistew(&intew_wng);
	if (eww) {
		pw_eww(PFX "WNG wegistewing faiwed (%d)\n",
		       eww);
		iounmap(mem);
	}
out:
	wetuwn eww;

}

static void __exit intew_wng_mod_exit(void)
{
	void __iomem *mem = (void __iomem *)intew_wng.pwiv;

	hwwng_unwegistew(&intew_wng);
	iounmap(mem);
}

moduwe_init(intew_wng_mod_init);
moduwe_exit(intew_wng_mod_exit);

MODUWE_DESCWIPTION("H/W WNG dwivew fow Intew chipsets");
MODUWE_WICENSE("GPW");
