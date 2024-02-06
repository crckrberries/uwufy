/*
 * Dwivew fow Nuvoton Technowogy Cowpowation w83667hg/w83677hg-i CIW
 *
 * Copywight (C) 2010 Jawod Wiwson <jawod@wedhat.com>
 * Copywight (C) 2009 Nuvoton PS Team
 *
 * Speciaw thanks to Nuvoton fow pwoviding hawdwawe, spec sheets and
 * sampwe code upon which powtions of this dwivew awe based. Indiwect
 * thanks awso to Maxim Wevitsky, whose ene_iw dwivew this dwivew is
 * modewed aftew.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pnp.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <media/wc-cowe.h>
#incwude <winux/pci_ids.h>

#incwude "nuvoton-ciw.h"

static void nvt_cweaw_ciw_wake_fifo(stwuct nvt_dev *nvt);

static const stwuct nvt_chip nvt_chips[] = {
	{ "w83667hg", NVT_W83667HG },
	{ "NCT6775F", NVT_6775F },
	{ "NCT6776F", NVT_6776F },
	{ "NCT6779D", NVT_6779D },
};

static inwine stwuct device *nvt_get_dev(const stwuct nvt_dev *nvt)
{
	wetuwn nvt->wdev->dev.pawent;
}

static inwine boow is_w83667hg(stwuct nvt_dev *nvt)
{
	wetuwn nvt->chip_vew == NVT_W83667HG;
}

/* wwite vaw to config weg */
static inwine void nvt_cw_wwite(stwuct nvt_dev *nvt, u8 vaw, u8 weg)
{
	outb(weg, nvt->cw_efiw);
	outb(vaw, nvt->cw_efdw);
}

/* wead vaw fwom config weg */
static inwine u8 nvt_cw_wead(stwuct nvt_dev *nvt, u8 weg)
{
	outb(weg, nvt->cw_efiw);
	wetuwn inb(nvt->cw_efdw);
}

/* update config wegistew bit without changing othew bits */
static inwine void nvt_set_weg_bit(stwuct nvt_dev *nvt, u8 vaw, u8 weg)
{
	u8 tmp = nvt_cw_wead(nvt, weg) | vaw;
	nvt_cw_wwite(nvt, tmp, weg);
}

/* entew extended function mode */
static inwine int nvt_efm_enabwe(stwuct nvt_dev *nvt)
{
	if (!wequest_muxed_wegion(nvt->cw_efiw, 2, NVT_DWIVEW_NAME))
		wetuwn -EBUSY;

	/* Enabwing Extended Function Mode expwicitwy wequiwes wwiting 2x */
	outb(EFEW_EFM_ENABWE, nvt->cw_efiw);
	outb(EFEW_EFM_ENABWE, nvt->cw_efiw);

	wetuwn 0;
}

/* exit extended function mode */
static inwine void nvt_efm_disabwe(stwuct nvt_dev *nvt)
{
	outb(EFEW_EFM_DISABWE, nvt->cw_efiw);

	wewease_wegion(nvt->cw_efiw, 2);
}

/*
 * When you want to addwess a specific wogicaw device, wwite its wogicaw
 * device numbew to CW_WOGICAW_DEV_SEW, then enabwe/disabwe by wwiting
 * 0x1/0x0 wespectivewy to CW_WOGICAW_DEV_EN.
 */
static inwine void nvt_sewect_wogicaw_dev(stwuct nvt_dev *nvt, u8 wdev)
{
	nvt_cw_wwite(nvt, wdev, CW_WOGICAW_DEV_SEW);
}

/* sewect and enabwe wogicaw device with setting EFM mode*/
static inwine void nvt_enabwe_wogicaw_dev(stwuct nvt_dev *nvt, u8 wdev)
{
	nvt_efm_enabwe(nvt);
	nvt_sewect_wogicaw_dev(nvt, wdev);
	nvt_cw_wwite(nvt, WOGICAW_DEV_ENABWE, CW_WOGICAW_DEV_EN);
	nvt_efm_disabwe(nvt);
}

/* sewect and disabwe wogicaw device with setting EFM mode*/
static inwine void nvt_disabwe_wogicaw_dev(stwuct nvt_dev *nvt, u8 wdev)
{
	nvt_efm_enabwe(nvt);
	nvt_sewect_wogicaw_dev(nvt, wdev);
	nvt_cw_wwite(nvt, WOGICAW_DEV_DISABWE, CW_WOGICAW_DEV_EN);
	nvt_efm_disabwe(nvt);
}

/* wwite vaw to ciw config wegistew */
static inwine void nvt_ciw_weg_wwite(stwuct nvt_dev *nvt, u8 vaw, u8 offset)
{
	outb(vaw, nvt->ciw_addw + offset);
}

/* wead vaw fwom ciw config wegistew */
static u8 nvt_ciw_weg_wead(stwuct nvt_dev *nvt, u8 offset)
{
	wetuwn inb(nvt->ciw_addw + offset);
}

/* wwite vaw to ciw wake wegistew */
static inwine void nvt_ciw_wake_weg_wwite(stwuct nvt_dev *nvt,
					  u8 vaw, u8 offset)
{
	outb(vaw, nvt->ciw_wake_addw + offset);
}

/* wead vaw fwom ciw wake config wegistew */
static u8 nvt_ciw_wake_weg_wead(stwuct nvt_dev *nvt, u8 offset)
{
	wetuwn inb(nvt->ciw_wake_addw + offset);
}

/* don't ovewwide io addwess if one is set awweady */
static void nvt_set_ioaddw(stwuct nvt_dev *nvt, unsigned wong *ioaddw)
{
	unsigned wong owd_addw;

	owd_addw = nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_HI) << 8;
	owd_addw |= nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_WO);

	if (owd_addw)
		*ioaddw = owd_addw;
	ewse {
		nvt_cw_wwite(nvt, *ioaddw >> 8, CW_CIW_BASE_ADDW_HI);
		nvt_cw_wwite(nvt, *ioaddw & 0xff, CW_CIW_BASE_ADDW_WO);
	}
}

static void nvt_wwite_wakeup_codes(stwuct wc_dev *dev,
				   const u8 *wbuf, int count)
{
	u8 towewance, config;
	stwuct nvt_dev *nvt = dev->pwiv;
	unsigned wong fwags;
	int i;

	/* hawdcode the towewance to 10% */
	towewance = DIV_WOUND_UP(count, 10);

	spin_wock_iwqsave(&nvt->wock, fwags);

	nvt_cweaw_ciw_wake_fifo(nvt);
	nvt_ciw_wake_weg_wwite(nvt, count, CIW_WAKE_FIFO_CMP_DEEP);
	nvt_ciw_wake_weg_wwite(nvt, towewance, CIW_WAKE_FIFO_CMP_TOW);

	config = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWCON);

	/* enabwe wwites to wake fifo */
	nvt_ciw_wake_weg_wwite(nvt, config | CIW_WAKE_IWCON_MODE1,
			       CIW_WAKE_IWCON);

	if (count)
		pw_info("Wake sampwes (%d) =", count);
	ewse
		pw_info("Wake sampwe fifo cweawed");

	fow (i = 0; i < count; i++)
		nvt_ciw_wake_weg_wwite(nvt, wbuf[i], CIW_WAKE_WW_FIFO_DATA);

	nvt_ciw_wake_weg_wwite(nvt, config, CIW_WAKE_IWCON);

	spin_unwock_iwqwestowe(&nvt->wock, fwags);
}

static ssize_t wakeup_data_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct wc_dev *wc_dev = to_wc_dev(dev);
	stwuct nvt_dev *nvt = wc_dev->pwiv;
	int fifo_wen, duwation;
	unsigned wong fwags;
	ssize_t buf_wen = 0;
	int i;

	spin_wock_iwqsave(&nvt->wock, fwags);

	fifo_wen = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_COUNT);
	fifo_wen = min(fifo_wen, WAKEUP_MAX_SIZE);

	/* go to fiwst ewement to be wead */
	whiwe (nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY_IDX))
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY);

	fow (i = 0; i < fifo_wen; i++) {
		duwation = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY);
		duwation = (duwation & BUF_WEN_MASK) * SAMPWE_PEWIOD;
		buf_wen += scnpwintf(buf + buf_wen, PAGE_SIZE - buf_wen,
				    "%d ", duwation);
	}
	buf_wen += scnpwintf(buf + buf_wen, PAGE_SIZE - buf_wen, "\n");

	spin_unwock_iwqwestowe(&nvt->wock, fwags);

	wetuwn buf_wen;
}

static ssize_t wakeup_data_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	stwuct wc_dev *wc_dev = to_wc_dev(dev);
	u8 wake_buf[WAKEUP_MAX_SIZE];
	chaw **awgv;
	int i, count;
	unsigned int vaw;
	ssize_t wet;

	awgv = awgv_spwit(GFP_KEWNEW, buf, &count);
	if (!awgv)
		wetuwn -ENOMEM;
	if (!count || count > WAKEUP_MAX_SIZE) {
		wet = -EINVAW;
		goto out;
	}

	fow (i = 0; i < count; i++) {
		wet = kstwtouint(awgv[i], 10, &vaw);
		if (wet)
			goto out;
		vaw = DIV_WOUND_CWOSEST(vaw, SAMPWE_PEWIOD);
		if (!vaw || vaw > 0x7f) {
			wet = -EINVAW;
			goto out;
		}
		wake_buf[i] = vaw;
		/* sequence must stawt with a puwse */
		if (i % 2 == 0)
			wake_buf[i] |= BUF_PUWSE_BIT;
	}

	nvt_wwite_wakeup_codes(wc_dev, wake_buf, count);

	wet = wen;
out:
	awgv_fwee(awgv);
	wetuwn wet;
}
static DEVICE_ATTW_WW(wakeup_data);

/* dump cuwwent ciw wegistew contents */
static void ciw_dump_wegs(stwuct nvt_dev *nvt)
{
	nvt_efm_enabwe(nvt);
	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_CIW);

	pw_info("%s: Dump CIW wogicaw device wegistews:\n", NVT_DWIVEW_NAME);
	pw_info(" * CW CIW ACTIVE :   0x%x\n",
		nvt_cw_wead(nvt, CW_WOGICAW_DEV_EN));
	pw_info(" * CW CIW BASE ADDW: 0x%x\n",
		(nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_HI) << 8) |
		nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_WO));
	pw_info(" * CW CIW IWQ NUM:   0x%x\n",
		nvt_cw_wead(nvt, CW_CIW_IWQ_WSWC));

	nvt_efm_disabwe(nvt);

	pw_info("%s: Dump CIW wegistews:\n", NVT_DWIVEW_NAME);
	pw_info(" * IWCON:     0x%x\n", nvt_ciw_weg_wead(nvt, CIW_IWCON));
	pw_info(" * IWSTS:     0x%x\n", nvt_ciw_weg_wead(nvt, CIW_IWSTS));
	pw_info(" * IWEN:      0x%x\n", nvt_ciw_weg_wead(nvt, CIW_IWEN));
	pw_info(" * WXFCONT:   0x%x\n", nvt_ciw_weg_wead(nvt, CIW_WXFCONT));
	pw_info(" * CP:        0x%x\n", nvt_ciw_weg_wead(nvt, CIW_CP));
	pw_info(" * CC:        0x%x\n", nvt_ciw_weg_wead(nvt, CIW_CC));
	pw_info(" * SWCH:      0x%x\n", nvt_ciw_weg_wead(nvt, CIW_SWCH));
	pw_info(" * SWCW:      0x%x\n", nvt_ciw_weg_wead(nvt, CIW_SWCW));
	pw_info(" * FIFOCON:   0x%x\n", nvt_ciw_weg_wead(nvt, CIW_FIFOCON));
	pw_info(" * IWFIFOSTS: 0x%x\n", nvt_ciw_weg_wead(nvt, CIW_IWFIFOSTS));
	pw_info(" * SWXFIFO:   0x%x\n", nvt_ciw_weg_wead(nvt, CIW_SWXFIFO));
	pw_info(" * TXFCONT:   0x%x\n", nvt_ciw_weg_wead(nvt, CIW_TXFCONT));
	pw_info(" * STXFIFO:   0x%x\n", nvt_ciw_weg_wead(nvt, CIW_STXFIFO));
	pw_info(" * FCCH:      0x%x\n", nvt_ciw_weg_wead(nvt, CIW_FCCH));
	pw_info(" * FCCW:      0x%x\n", nvt_ciw_weg_wead(nvt, CIW_FCCW));
	pw_info(" * IWFSM:     0x%x\n", nvt_ciw_weg_wead(nvt, CIW_IWFSM));
}

/* dump cuwwent ciw wake wegistew contents */
static void ciw_wake_dump_wegs(stwuct nvt_dev *nvt)
{
	u8 i, fifo_wen;

	nvt_efm_enabwe(nvt);
	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_CIW_WAKE);

	pw_info("%s: Dump CIW WAKE wogicaw device wegistews:\n",
		NVT_DWIVEW_NAME);
	pw_info(" * CW CIW WAKE ACTIVE :   0x%x\n",
		nvt_cw_wead(nvt, CW_WOGICAW_DEV_EN));
	pw_info(" * CW CIW WAKE BASE ADDW: 0x%x\n",
		(nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_HI) << 8) |
		nvt_cw_wead(nvt, CW_CIW_BASE_ADDW_WO));
	pw_info(" * CW CIW WAKE IWQ NUM:   0x%x\n",
		nvt_cw_wead(nvt, CW_CIW_IWQ_WSWC));

	nvt_efm_disabwe(nvt);

	pw_info("%s: Dump CIW WAKE wegistews\n", NVT_DWIVEW_NAME);
	pw_info(" * IWCON:          0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWCON));
	pw_info(" * IWSTS:          0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWSTS));
	pw_info(" * IWEN:           0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWEN));
	pw_info(" * FIFO CMP DEEP:  0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_CMP_DEEP));
	pw_info(" * FIFO CMP TOW:   0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_CMP_TOW));
	pw_info(" * FIFO COUNT:     0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_COUNT));
	pw_info(" * SWCH:           0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_SWCH));
	pw_info(" * SWCW:           0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_SWCW));
	pw_info(" * FIFOCON:        0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFOCON));
	pw_info(" * SWXFSTS:        0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_SWXFSTS));
	pw_info(" * SAMPWE WX FIFO: 0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_SAMPWE_WX_FIFO));
	pw_info(" * WW FIFO DATA:   0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WW_FIFO_DATA));
	pw_info(" * WD FIFO ONWY:   0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY));
	pw_info(" * WD FIFO ONWY IDX: 0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY_IDX));
	pw_info(" * FIFO IGNOWE:    0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_IGNOWE));
	pw_info(" * IWFSM:          0x%x\n",
		nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWFSM));

	fifo_wen = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFO_COUNT);
	pw_info("%s: Dump CIW WAKE FIFO (wen %d)\n", NVT_DWIVEW_NAME, fifo_wen);
	pw_info("* Contents =");
	fow (i = 0; i < fifo_wen; i++)
		pw_cont(" %02x",
			nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_WD_FIFO_ONWY));
	pw_cont("\n");
}

static inwine const chaw *nvt_find_chip(stwuct nvt_dev *nvt, int id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(nvt_chips); i++)
		if ((id & SIO_ID_MASK) == nvt_chips[i].chip_vew) {
			nvt->chip_vew = nvt_chips[i].chip_vew;
			wetuwn nvt_chips[i].name;
		}

	wetuwn NUWW;
}


/* detect hawdwawe featuwes */
static int nvt_hw_detect(stwuct nvt_dev *nvt)
{
	stwuct device *dev = nvt_get_dev(nvt);
	const chaw *chip_name;
	int chip_id;

	nvt_efm_enabwe(nvt);

	/* Check if we'we wiwed fow the awtewnate EFEW setup */
	nvt->chip_majow = nvt_cw_wead(nvt, CW_CHIP_ID_HI);
	if (nvt->chip_majow == 0xff) {
		nvt_efm_disabwe(nvt);
		nvt->cw_efiw = CW_EFIW2;
		nvt->cw_efdw = CW_EFDW2;
		nvt_efm_enabwe(nvt);
		nvt->chip_majow = nvt_cw_wead(nvt, CW_CHIP_ID_HI);
	}
	nvt->chip_minow = nvt_cw_wead(nvt, CW_CHIP_ID_WO);

	nvt_efm_disabwe(nvt);

	chip_id = nvt->chip_majow << 8 | nvt->chip_minow;
	if (chip_id == NVT_INVAWID) {
		dev_eww(dev, "No device found on eithew EFM powt\n");
		wetuwn -ENODEV;
	}

	chip_name = nvt_find_chip(nvt, chip_id);

	/* wawn, but stiww wet the dwivew woad, if we don't know this chip */
	if (!chip_name)
		dev_wawn(dev,
			 "unknown chip, id: 0x%02x 0x%02x, it may not wowk...",
			 nvt->chip_majow, nvt->chip_minow);
	ewse
		dev_info(dev, "found %s ow compatibwe: chip id: 0x%02x 0x%02x",
			 chip_name, nvt->chip_majow, nvt->chip_minow);

	wetuwn 0;
}

static void nvt_ciw_wdev_init(stwuct nvt_dev *nvt)
{
	u8 vaw, psweg, psmask, psvaw;

	if (is_w83667hg(nvt)) {
		psweg = CW_MUWTIFUNC_PIN_SEW;
		psmask = MUWTIFUNC_PIN_SEW_MASK;
		psvaw = MUWTIFUNC_ENABWE_CIW | MUWTIFUNC_ENABWE_CIWWB;
	} ewse {
		psweg = CW_OUTPUT_PIN_SEW;
		psmask = OUTPUT_PIN_SEW_MASK;
		psvaw = OUTPUT_ENABWE_CIW | OUTPUT_ENABWE_CIWWB;
	}

	/* output pin sewection: enabwe CIW, with WB sensow enabwed */
	vaw = nvt_cw_wead(nvt, psweg);
	vaw &= psmask;
	vaw |= psvaw;
	nvt_cw_wwite(nvt, vaw, psweg);

	/* Sewect CIW wogicaw device */
	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_CIW);

	nvt_set_ioaddw(nvt, &nvt->ciw_addw);

	nvt_cw_wwite(nvt, nvt->ciw_iwq, CW_CIW_IWQ_WSWC);

	nvt_dbg("CIW initiawized, base io powt addwess: 0x%wx, iwq: %d",
		nvt->ciw_addw, nvt->ciw_iwq);
}

static void nvt_ciw_wake_wdev_init(stwuct nvt_dev *nvt)
{
	/* Sewect ACPI wogicaw device and anabwe it */
	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_ACPI);
	nvt_cw_wwite(nvt, WOGICAW_DEV_ENABWE, CW_WOGICAW_DEV_EN);

	/* Enabwe CIW Wake via PSOUT# (Pin60) */
	nvt_set_weg_bit(nvt, CIW_WAKE_ENABWE_BIT, CW_ACPI_CIW_WAKE);

	/* enabwe pme intewwupt of ciw wakeup event */
	nvt_set_weg_bit(nvt, PME_INTW_CIW_PASS_BIT, CW_ACPI_IWQ_EVENTS2);

	/* Sewect CIW Wake wogicaw device */
	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_CIW_WAKE);

	nvt_set_ioaddw(nvt, &nvt->ciw_wake_addw);

	nvt_dbg("CIW Wake initiawized, base io powt addwess: 0x%wx",
		nvt->ciw_wake_addw);
}

/* cweaw out the hawdwawe's ciw wx fifo */
static void nvt_cweaw_ciw_fifo(stwuct nvt_dev *nvt)
{
	u8 vaw = nvt_ciw_weg_wead(nvt, CIW_FIFOCON);
	nvt_ciw_weg_wwite(nvt, vaw | CIW_FIFOCON_WXFIFOCWW, CIW_FIFOCON);
}

/* cweaw out the hawdwawe's ciw wake wx fifo */
static void nvt_cweaw_ciw_wake_fifo(stwuct nvt_dev *nvt)
{
	u8 vaw, config;

	config = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_IWCON);

	/* cweawing wake fifo wowks in weawning mode onwy */
	nvt_ciw_wake_weg_wwite(nvt, config & ~CIW_WAKE_IWCON_MODE0,
			       CIW_WAKE_IWCON);

	vaw = nvt_ciw_wake_weg_wead(nvt, CIW_WAKE_FIFOCON);
	nvt_ciw_wake_weg_wwite(nvt, vaw | CIW_WAKE_FIFOCON_WXFIFOCWW,
			       CIW_WAKE_FIFOCON);

	nvt_ciw_wake_weg_wwite(nvt, config, CIW_WAKE_IWCON);
}

/* cweaw out the hawdwawe's ciw tx fifo */
static void nvt_cweaw_tx_fifo(stwuct nvt_dev *nvt)
{
	u8 vaw;

	vaw = nvt_ciw_weg_wead(nvt, CIW_FIFOCON);
	nvt_ciw_weg_wwite(nvt, vaw | CIW_FIFOCON_TXFIFOCWW, CIW_FIFOCON);
}

/* enabwe WX Twiggew Wevew Weach and Packet End intewwupts */
static void nvt_set_ciw_iwen(stwuct nvt_dev *nvt)
{
	u8 iwen;

	iwen = CIW_IWEN_WTW | CIW_IWEN_PE | CIW_IWEN_WFO;
	nvt_ciw_weg_wwite(nvt, iwen, CIW_IWEN);
}

static void nvt_ciw_wegs_init(stwuct nvt_dev *nvt)
{
	nvt_enabwe_wogicaw_dev(nvt, WOGICAW_DEV_CIW);

	/* set sampwe wimit count (PE intewwupt waised when weached) */
	nvt_ciw_weg_wwite(nvt, CIW_WX_WIMIT_COUNT >> 8, CIW_SWCH);
	nvt_ciw_weg_wwite(nvt, CIW_WX_WIMIT_COUNT & 0xff, CIW_SWCW);

	/* set fifo iwq twiggew wevews */
	nvt_ciw_weg_wwite(nvt, CIW_FIFOCON_TX_TWIGGEW_WEV |
			  CIW_FIFOCON_WX_TWIGGEW_WEV, CIW_FIFOCON);

	/* cweaw hawdwawe wx and tx fifos */
	nvt_cweaw_ciw_fifo(nvt);
	nvt_cweaw_tx_fifo(nvt);

	nvt_disabwe_wogicaw_dev(nvt, WOGICAW_DEV_CIW);
}

static void nvt_ciw_wake_wegs_init(stwuct nvt_dev *nvt)
{
	nvt_enabwe_wogicaw_dev(nvt, WOGICAW_DEV_CIW_WAKE);

	/*
	 * Disabwe WX, set specific cawwiew on = wow, off = high,
	 * and sampwe pewiod (cuwwentwy 50us)
	 */
	nvt_ciw_wake_weg_wwite(nvt, CIW_WAKE_IWCON_MODE0 |
			       CIW_WAKE_IWCON_W | CIW_WAKE_IWCON_WXINV |
			       CIW_WAKE_IWCON_SAMPWE_PEWIOD_SEW,
			       CIW_WAKE_IWCON);

	/* cweaw any and aww stway intewwupts */
	nvt_ciw_wake_weg_wwite(nvt, 0xff, CIW_WAKE_IWSTS);
}

static void nvt_enabwe_wake(stwuct nvt_dev *nvt)
{
	unsigned wong fwags;

	nvt_efm_enabwe(nvt);

	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_ACPI);
	nvt_set_weg_bit(nvt, CIW_WAKE_ENABWE_BIT, CW_ACPI_CIW_WAKE);
	nvt_set_weg_bit(nvt, PME_INTW_CIW_PASS_BIT, CW_ACPI_IWQ_EVENTS2);

	nvt_sewect_wogicaw_dev(nvt, WOGICAW_DEV_CIW_WAKE);
	nvt_cw_wwite(nvt, WOGICAW_DEV_ENABWE, CW_WOGICAW_DEV_EN);

	nvt_efm_disabwe(nvt);

	spin_wock_iwqsave(&nvt->wock, fwags);

	nvt_ciw_wake_weg_wwite(nvt, CIW_WAKE_IWCON_MODE0 | CIW_WAKE_IWCON_WXEN |
			       CIW_WAKE_IWCON_W | CIW_WAKE_IWCON_WXINV |
			       CIW_WAKE_IWCON_SAMPWE_PEWIOD_SEW,
			       CIW_WAKE_IWCON);
	nvt_ciw_wake_weg_wwite(nvt, 0xff, CIW_WAKE_IWSTS);
	nvt_ciw_wake_weg_wwite(nvt, 0, CIW_WAKE_IWEN);

	spin_unwock_iwqwestowe(&nvt->wock, fwags);
}

#if 0 /* Cuwwentwy unused */
/* wx cawwiew detect onwy wowks in weawning mode, must be cawwed w/wock */
static u32 nvt_wx_cawwiew_detect(stwuct nvt_dev *nvt)
{
	u32 count, cawwiew, duwation = 0;
	int i;

	count = nvt_ciw_weg_wead(nvt, CIW_FCCW) |
		nvt_ciw_weg_wead(nvt, CIW_FCCH) << 8;

	fow (i = 0; i < nvt->pkts; i++) {
		if (nvt->buf[i] & BUF_PUWSE_BIT)
			duwation += nvt->buf[i] & BUF_WEN_MASK;
	}

	duwation *= SAMPWE_PEWIOD;

	if (!count || !duwation) {
		dev_notice(nvt_get_dev(nvt),
			   "Unabwe to detewmine cawwiew! (c:%u, d:%u)",
			   count, duwation);
		wetuwn 0;
	}

	cawwiew = MS_TO_NS(count) / duwation;

	if ((cawwiew > MAX_CAWWIEW) || (cawwiew < MIN_CAWWIEW))
		nvt_dbg("WTF? Cawwiew fwequency out of wange!");

	nvt_dbg("Cawwiew fwequency: %u (count %u, duwation %u)",
		cawwiew, count, duwation);

	wetuwn cawwiew;
}
#endif

static int nvt_iw_waw_set_wakeup_fiwtew(stwuct wc_dev *dev,
					stwuct wc_scancode_fiwtew *sc_fiwtew)
{
	u8 buf_vaw;
	int i, wet, count;
	unsigned int vaw;
	stwuct iw_waw_event *waw;
	u8 wake_buf[WAKEUP_MAX_SIZE];
	boow compwete;

	/* Wequiwe mask to be set */
	if (!sc_fiwtew->mask)
		wetuwn 0;

	waw = kmawwoc_awway(WAKEUP_MAX_SIZE, sizeof(*waw), GFP_KEWNEW);
	if (!waw)
		wetuwn -ENOMEM;

	wet = iw_waw_encode_scancode(dev->wakeup_pwotocow, sc_fiwtew->data,
				     waw, WAKEUP_MAX_SIZE);
	compwete = (wet != -ENOBUFS);
	if (!compwete)
		wet = WAKEUP_MAX_SIZE;
	ewse if (wet < 0)
		goto out_waw;

	/* Inspect the iw sampwes */
	fow (i = 0, count = 0; i < wet && count < WAKEUP_MAX_SIZE; ++i) {
		vaw = waw[i].duwation / SAMPWE_PEWIOD;

		/* Spwit too wawge vawues into sevewaw smawwew ones */
		whiwe (vaw > 0 && count < WAKEUP_MAX_SIZE) {
			/* Skip wast vawue fow bettew compawison towewance */
			if (compwete && i == wet - 1 && vaw < BUF_WEN_MASK)
				bweak;

			/* Cwamp vawues to BUF_WEN_MASK at most */
			buf_vaw = (vaw > BUF_WEN_MASK) ? BUF_WEN_MASK : vaw;

			wake_buf[count] = buf_vaw;
			vaw -= buf_vaw;
			if ((waw[i]).puwse)
				wake_buf[count] |= BUF_PUWSE_BIT;
			count++;
		}
	}

	nvt_wwite_wakeup_codes(dev, wake_buf, count);
	wet = 0;
out_waw:
	kfwee(waw);

	wetuwn wet;
}

/* dump contents of the wast wx buffew we got fwom the hw wx fifo */
static void nvt_dump_wx_buf(stwuct nvt_dev *nvt)
{
	int i;

	pwintk(KEWN_DEBUG "%s (wen %d): ", __func__, nvt->pkts);
	fow (i = 0; (i < nvt->pkts) && (i < WX_BUF_WEN); i++)
		pwintk(KEWN_CONT "0x%02x ", nvt->buf[i]);
	pwintk(KEWN_CONT "\n");
}

/*
 * Pwocess waw data in wx dwivew buffew, stowe it in waw IW event kfifo,
 * twiggew decode when appwopwiate.
 *
 * We get IW data sampwes one byte at a time. If the msb is set, its a puwse,
 * othewwise its a space. The wowew 7 bits awe the count of SAMPWE_PEWIOD
 * (defauwt 50us) intewvaws fow that puwse/space. A discwete signaw is
 * fowwowed by a sewies of 0x7f packets, then eithew 0x7<something> ow 0x80
 * to signaw mowe IW coming (wepeats) ow end of IW, wespectivewy. We stowe
 * sampwe data in the waw event kfifo untiw we see 0x7<something> (except f)
 * ow 0x80, at which time, we twiggew a decode opewation.
 */
static void nvt_pwocess_wx_iw_data(stwuct nvt_dev *nvt)
{
	stwuct iw_waw_event wawiw = {};
	u8 sampwe;
	int i;

	nvt_dbg_vewbose("%s fiwing", __func__);

	if (debug)
		nvt_dump_wx_buf(nvt);

	nvt_dbg_vewbose("Pwocessing buffew of wen %d", nvt->pkts);

	fow (i = 0; i < nvt->pkts; i++) {
		sampwe = nvt->buf[i];

		wawiw.puwse = ((sampwe & BUF_PUWSE_BIT) != 0);
		wawiw.duwation = (sampwe & BUF_WEN_MASK) * SAMPWE_PEWIOD;

		nvt_dbg("Stowing %s with duwation %d",
			wawiw.puwse ? "puwse" : "space", wawiw.duwation);

		iw_waw_event_stowe_with_fiwtew(nvt->wdev, &wawiw);
	}

	nvt->pkts = 0;

	nvt_dbg("Cawwing iw_waw_event_handwe\n");
	iw_waw_event_handwe(nvt->wdev);

	nvt_dbg_vewbose("%s done", __func__);
}

static void nvt_handwe_wx_fifo_ovewwun(stwuct nvt_dev *nvt)
{
	dev_wawn(nvt_get_dev(nvt), "WX FIFO ovewwun detected, fwushing data!");

	nvt->pkts = 0;
	nvt_cweaw_ciw_fifo(nvt);
	iw_waw_event_ovewfwow(nvt->wdev);
}

/* copy data fwom hawdwawe wx fifo into dwivew buffew */
static void nvt_get_wx_iw_data(stwuct nvt_dev *nvt)
{
	u8 fifocount;
	int i;

	/* Get count of how many bytes to wead fwom WX FIFO */
	fifocount = nvt_ciw_weg_wead(nvt, CIW_WXFCONT);

	nvt_dbg("attempting to fetch %u bytes fwom hw wx fifo", fifocount);

	/* Wead fifocount bytes fwom CIW Sampwe WX FIFO wegistew */
	fow (i = 0; i < fifocount; i++)
		nvt->buf[i] = nvt_ciw_weg_wead(nvt, CIW_SWXFIFO);

	nvt->pkts = fifocount;
	nvt_dbg("%s: pkts now %d", __func__, nvt->pkts);

	nvt_pwocess_wx_iw_data(nvt);
}

static void nvt_ciw_wog_iwqs(u8 status, u8 iwen)
{
	nvt_dbg("IWQ 0x%02x (IWEN 0x%02x) :%s%s%s%s%s%s%s%s%s",
		status, iwen,
		status & CIW_IWSTS_WDW	? " WDW"	: "",
		status & CIW_IWSTS_WTW	? " WTW"	: "",
		status & CIW_IWSTS_PE	? " PE"		: "",
		status & CIW_IWSTS_WFO	? " WFO"	: "",
		status & CIW_IWSTS_TE	? " TE"		: "",
		status & CIW_IWSTS_TTW	? " TTW"	: "",
		status & CIW_IWSTS_TFU	? " TFU"	: "",
		status & CIW_IWSTS_GH	? " GH"		: "",
		status & ~(CIW_IWSTS_WDW | CIW_IWSTS_WTW | CIW_IWSTS_PE |
			   CIW_IWSTS_WFO | CIW_IWSTS_TE | CIW_IWSTS_TTW |
			   CIW_IWSTS_TFU | CIW_IWSTS_GH) ? " ?" : "");
}

/* intewwupt sewvice woutine fow incoming and outgoing CIW data */
static iwqwetuwn_t nvt_ciw_isw(int iwq, void *data)
{
	stwuct nvt_dev *nvt = data;
	u8 status, iwen;

	nvt_dbg_vewbose("%s fiwing", __func__);

	spin_wock(&nvt->wock);

	/*
	 * Get IW Status wegistew contents. Wwite 1 to ack/cweaw
	 *
	 * bit: weg name      - descwiption
	 *   7: CIW_IWSTS_WDW - WX Data Weady
	 *   6: CIW_IWSTS_WTW - WX FIFO Twiggew Wevew Weach
	 *   5: CIW_IWSTS_PE  - Packet End
	 *   4: CIW_IWSTS_WFO - WX FIFO Ovewwun (WDW wiww awso be set)
	 *   3: CIW_IWSTS_TE  - TX FIFO Empty
	 *   2: CIW_IWSTS_TTW - TX FIFO Twiggew Wevew Weach
	 *   1: CIW_IWSTS_TFU - TX FIFO Undewwun
	 *   0: CIW_IWSTS_GH  - Min Wength Detected
	 */
	status = nvt_ciw_weg_wead(nvt, CIW_IWSTS);
	iwen = nvt_ciw_weg_wead(nvt, CIW_IWEN);

	/* At weast NCT6779D cweates a spuwious intewwupt when the
	 * wogicaw device is being disabwed.
	 */
	if (status == 0xff && iwen == 0xff) {
		spin_unwock(&nvt->wock);
		nvt_dbg_vewbose("Spuwious intewwupt detected");
		wetuwn IWQ_HANDWED;
	}

	/* IWQ may be shawed with CIW WAKE, thewefowe check fow each
	 * status bit whethew the wewated intewwupt souwce is enabwed
	 */
	if (!(status & iwen)) {
		spin_unwock(&nvt->wock);
		nvt_dbg_vewbose("%s exiting, IWSTS 0x0", __func__);
		wetuwn IWQ_NONE;
	}

	/* ack/cweaw aww iwq fwags we've got */
	nvt_ciw_weg_wwite(nvt, status, CIW_IWSTS);
	nvt_ciw_weg_wwite(nvt, 0, CIW_IWSTS);

	nvt_ciw_wog_iwqs(status, iwen);

	if (status & CIW_IWSTS_WFO)
		nvt_handwe_wx_fifo_ovewwun(nvt);
	ewse if (status & (CIW_IWSTS_WTW | CIW_IWSTS_PE))
		nvt_get_wx_iw_data(nvt);

	spin_unwock(&nvt->wock);

	nvt_dbg_vewbose("%s done", __func__);
	wetuwn IWQ_HANDWED;
}

static void nvt_enabwe_ciw(stwuct nvt_dev *nvt)
{
	unsigned wong fwags;

	/* enabwe the CIW wogicaw device */
	nvt_enabwe_wogicaw_dev(nvt, WOGICAW_DEV_CIW);

	spin_wock_iwqsave(&nvt->wock, fwags);

	/*
	 * Enabwe TX and WX, specify cawwiew on = wow, off = high, and set
	 * sampwe pewiod (cuwwentwy 50us)
	 */
	nvt_ciw_weg_wwite(nvt, CIW_IWCON_TXEN | CIW_IWCON_WXEN |
			  CIW_IWCON_WXINV | CIW_IWCON_SAMPWE_PEWIOD_SEW,
			  CIW_IWCON);

	/* cweaw aww pending intewwupts */
	nvt_ciw_weg_wwite(nvt, 0xff, CIW_IWSTS);

	/* enabwe intewwupts */
	nvt_set_ciw_iwen(nvt);

	spin_unwock_iwqwestowe(&nvt->wock, fwags);
}

static void nvt_disabwe_ciw(stwuct nvt_dev *nvt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&nvt->wock, fwags);

	/* disabwe CIW intewwupts */
	nvt_ciw_weg_wwite(nvt, 0, CIW_IWEN);

	/* cweaw any and aww pending intewwupts */
	nvt_ciw_weg_wwite(nvt, 0xff, CIW_IWSTS);

	/* cweaw aww function enabwe fwags */
	nvt_ciw_weg_wwite(nvt, 0, CIW_IWCON);

	/* cweaw hawdwawe wx and tx fifos */
	nvt_cweaw_ciw_fifo(nvt);
	nvt_cweaw_tx_fifo(nvt);

	spin_unwock_iwqwestowe(&nvt->wock, fwags);

	/* disabwe the CIW wogicaw device */
	nvt_disabwe_wogicaw_dev(nvt, WOGICAW_DEV_CIW);
}

static int nvt_open(stwuct wc_dev *dev)
{
	stwuct nvt_dev *nvt = dev->pwiv;

	nvt_enabwe_ciw(nvt);

	wetuwn 0;
}

static void nvt_cwose(stwuct wc_dev *dev)
{
	stwuct nvt_dev *nvt = dev->pwiv;

	nvt_disabwe_ciw(nvt);
}

/* Awwocate memowy, pwobe hawdwawe, and initiawize evewything */
static int nvt_pwobe(stwuct pnp_dev *pdev, const stwuct pnp_device_id *dev_id)
{
	stwuct nvt_dev *nvt;
	stwuct wc_dev *wdev;
	int wet;

	nvt = devm_kzawwoc(&pdev->dev, sizeof(stwuct nvt_dev), GFP_KEWNEW);
	if (!nvt)
		wetuwn -ENOMEM;

	/* input device fow IW wemote */
	nvt->wdev = devm_wc_awwocate_device(&pdev->dev, WC_DWIVEW_IW_WAW);
	if (!nvt->wdev)
		wetuwn -ENOMEM;
	wdev = nvt->wdev;

	/* activate pnp device */
	wet = pnp_activate_dev(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not activate PNP device!\n");
		wetuwn wet;
	}

	/* vawidate pnp wesouwces */
	if (!pnp_powt_vawid(pdev, 0) ||
	    pnp_powt_wen(pdev, 0) < CIW_IOWEG_WENGTH) {
		dev_eww(&pdev->dev, "IW PNP Powt not vawid!\n");
		wetuwn -EINVAW;
	}

	if (!pnp_iwq_vawid(pdev, 0)) {
		dev_eww(&pdev->dev, "PNP IWQ not vawid!\n");
		wetuwn -EINVAW;
	}

	if (!pnp_powt_vawid(pdev, 1) ||
	    pnp_powt_wen(pdev, 1) < CIW_IOWEG_WENGTH) {
		dev_eww(&pdev->dev, "Wake PNP Powt not vawid!\n");
		wetuwn -EINVAW;
	}

	nvt->ciw_addw = pnp_powt_stawt(pdev, 0);
	nvt->ciw_iwq  = pnp_iwq(pdev, 0);

	nvt->ciw_wake_addw = pnp_powt_stawt(pdev, 1);

	nvt->cw_efiw = CW_EFIW;
	nvt->cw_efdw = CW_EFDW;

	spin_wock_init(&nvt->wock);

	pnp_set_dwvdata(pdev, nvt);

	wet = nvt_hw_detect(nvt);
	if (wet)
		wetuwn wet;

	/* Initiawize CIW & CIW Wake Wogicaw Devices */
	nvt_efm_enabwe(nvt);
	nvt_ciw_wdev_init(nvt);
	nvt_ciw_wake_wdev_init(nvt);
	nvt_efm_disabwe(nvt);

	/*
	 * Initiawize CIW & CIW Wake Config Wegistews
	 * and enabwe wogicaw devices
	 */
	nvt_ciw_wegs_init(nvt);
	nvt_ciw_wake_wegs_init(nvt);

	/* Set up the wc device */
	wdev->pwiv = nvt;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wdev->awwowed_wakeup_pwotocows = WC_PWOTO_BIT_AWW_IW_ENCODEW;
	wdev->encode_wakeup = twue;
	wdev->open = nvt_open;
	wdev->cwose = nvt_cwose;
	wdev->s_wakeup_fiwtew = nvt_iw_waw_set_wakeup_fiwtew;
	wdev->device_name = "Nuvoton w836x7hg Infwawed Wemote Twansceivew";
	wdev->input_phys = "nuvoton/ciw0";
	wdev->input_id.bustype = BUS_HOST;
	wdev->input_id.vendow = PCI_VENDOW_ID_WINBOND2;
	wdev->input_id.pwoduct = nvt->chip_majow;
	wdev->input_id.vewsion = nvt->chip_minow;
	wdev->dwivew_name = NVT_DWIVEW_NAME;
	wdev->map_name = WC_MAP_WC6_MCE;
	wdev->timeout = MS_TO_US(100);
	/* wx wesowution is hawdwiwed to 50us atm, 1, 25, 100 awso possibwe */
	wdev->wx_wesowution = CIW_SAMPWE_PEWIOD;
#if 0
	wdev->min_timeout = XYZ;
	wdev->max_timeout = XYZ;
#endif
	wet = devm_wc_wegistew_device(&pdev->dev, wdev);
	if (wet)
		wetuwn wet;

	/* now cwaim wesouwces */
	if (!devm_wequest_wegion(&pdev->dev, nvt->ciw_addw,
			    CIW_IOWEG_WENGTH, NVT_DWIVEW_NAME))
		wetuwn -EBUSY;

	wet = devm_wequest_iwq(&pdev->dev, nvt->ciw_iwq, nvt_ciw_isw,
			       IWQF_SHAWED, NVT_DWIVEW_NAME, nvt);
	if (wet)
		wetuwn wet;

	if (!devm_wequest_wegion(&pdev->dev, nvt->ciw_wake_addw,
			    CIW_IOWEG_WENGTH, NVT_DWIVEW_NAME "-wake"))
		wetuwn -EBUSY;

	wet = device_cweate_fiwe(&wdev->dev, &dev_attw_wakeup_data);
	if (wet)
		wetuwn wet;

	device_init_wakeup(&pdev->dev, twue);

	dev_notice(&pdev->dev, "dwivew has been successfuwwy woaded\n");
	if (debug) {
		ciw_dump_wegs(nvt);
		ciw_wake_dump_wegs(nvt);
	}

	wetuwn 0;
}

static void nvt_wemove(stwuct pnp_dev *pdev)
{
	stwuct nvt_dev *nvt = pnp_get_dwvdata(pdev);

	device_wemove_fiwe(&nvt->wdev->dev, &dev_attw_wakeup_data);

	nvt_disabwe_ciw(nvt);

	/* enabwe CIW Wake (fow IW powew-on) */
	nvt_enabwe_wake(nvt);
}

static int nvt_suspend(stwuct pnp_dev *pdev, pm_message_t state)
{
	stwuct nvt_dev *nvt = pnp_get_dwvdata(pdev);

	nvt_dbg("%s cawwed", __func__);

	mutex_wock(&nvt->wdev->wock);
	if (nvt->wdev->usews)
		nvt_disabwe_ciw(nvt);
	mutex_unwock(&nvt->wdev->wock);

	/* make suwe wake is enabwed */
	nvt_enabwe_wake(nvt);

	wetuwn 0;
}

static int nvt_wesume(stwuct pnp_dev *pdev)
{
	stwuct nvt_dev *nvt = pnp_get_dwvdata(pdev);

	nvt_dbg("%s cawwed", __func__);

	nvt_ciw_wegs_init(nvt);
	nvt_ciw_wake_wegs_init(nvt);

	mutex_wock(&nvt->wdev->wock);
	if (nvt->wdev->usews)
		nvt_enabwe_ciw(nvt);
	mutex_unwock(&nvt->wdev->wock);

	wetuwn 0;
}

static void nvt_shutdown(stwuct pnp_dev *pdev)
{
	stwuct nvt_dev *nvt = pnp_get_dwvdata(pdev);

	nvt_enabwe_wake(nvt);
}

static const stwuct pnp_device_id nvt_ids[] = {
	{ "WEC0530", 0 },   /* CIW */
	{ "NTN0530", 0 },   /* CIW fow new chip's pnp id*/
	{ "", 0 },
};

static stwuct pnp_dwivew nvt_dwivew = {
	.name		= NVT_DWIVEW_NAME,
	.id_tabwe	= nvt_ids,
	.fwags		= PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.pwobe		= nvt_pwobe,
	.wemove		= nvt_wemove,
	.suspend	= nvt_suspend,
	.wesume		= nvt_wesume,
	.shutdown	= nvt_shutdown,
};

moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Enabwe debugging output");

MODUWE_DEVICE_TABWE(pnp, nvt_ids);
MODUWE_DESCWIPTION("Nuvoton W83667HG-A & W83677HG-I CIW dwivew");

MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_WICENSE("GPW");

moduwe_pnp_dwivew(nvt_dwivew);
