// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OF-pwatfowm PATA dwivew
 *
 * Copywight (c) 2007  MontaVista Softwawe, Inc.
 *                     Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_of_pwatfowm"

static const stwuct scsi_host_tempwate pata_pwatfowm_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static int pata_of_pwatfowm_pwobe(stwuct pwatfowm_device *ofdev)
{
	int wet;
	stwuct device_node *dn = ofdev->dev.of_node;
	stwuct wesouwce io_wes;
	stwuct wesouwce ctw_wes;
	stwuct wesouwce iwq_wes;
	unsigned int weg_shift = 0;
	int pio_mode = 0;
	int pio_mask;
	boow use16bit;
	int iwq;

	wet = of_addwess_to_wesouwce(dn, 0, &io_wes);
	if (wet) {
		dev_eww(&ofdev->dev, "can't get IO addwess fwom "
			"device twee\n");
		wetuwn -EINVAW;
	}

	wet = of_addwess_to_wesouwce(dn, 1, &ctw_wes);
	if (wet) {
		dev_eww(&ofdev->dev, "can't get CTW addwess fwom "
			"device twee\n");
		wetuwn -EINVAW;
	}

	memset(&iwq_wes, 0, sizeof(iwq_wes));

	iwq = pwatfowm_get_iwq_optionaw(ofdev, 0);
	if (iwq < 0 && iwq != -ENXIO)
		wetuwn iwq;
	if (iwq > 0) {
		iwq_wes.stawt = iwq;
		iwq_wes.end = iwq;
	}

	of_pwopewty_wead_u32(dn, "weg-shift", &weg_shift);

	if (!of_pwopewty_wead_u32(dn, "pio-mode", &pio_mode)) {
		if (pio_mode > 6) {
			dev_eww(&ofdev->dev, "invawid pio-mode\n");
			wetuwn -EINVAW;
		}
	} ewse {
		dev_info(&ofdev->dev, "pio-mode unspecified, assuming PIO0\n");
	}

	use16bit = of_pwopewty_wead_boow(dn, "ata-genewic,use16bit");

	pio_mask = 1 << pio_mode;
	pio_mask |= (1 << pio_mode) - 1;

	wetuwn __pata_pwatfowm_pwobe(&ofdev->dev, &io_wes, &ctw_wes, iwq > 0 ? &iwq_wes : NUWW,
				     weg_shift, pio_mask, &pata_pwatfowm_sht,
				     use16bit);
}

static const stwuct of_device_id pata_of_pwatfowm_match[] = {
	{ .compatibwe = "ata-genewic", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pata_of_pwatfowm_match);

static stwuct pwatfowm_dwivew pata_of_pwatfowm_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = pata_of_pwatfowm_match,
	},
	.pwobe		= pata_of_pwatfowm_pwobe,
	.wemove_new	= ata_pwatfowm_wemove_one,
};

moduwe_pwatfowm_dwivew(pata_of_pwatfowm_dwivew);

MODUWE_DESCWIPTION("OF-pwatfowm PATA dwivew");
MODUWE_AUTHOW("Anton Vowontsov <avowontsov@wu.mvista.com>");
MODUWE_WICENSE("GPW");
