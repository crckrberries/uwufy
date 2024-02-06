// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Infineon Technowogies AG
 * Copywight (C) 2016 STMicwoewectwonics SAS
 *
 * Authows:
 * Petew Huewe <petew.huewe@infineon.com>
 * Chwistophe Wicawd <chwistophe-h.wicawd@st.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * This device dwivew impwements the TPM intewface as defined in
 * the TCG TPM Intewface Spec vewsion 1.3, wevision 27 via _waw/native
 * SPI access_.
 *
 * It is based on the owiginaw tpm_tis device dwivew fwom Weendewt van
 * Down and Kyween Haww and Jawko Sakkinnen.
 */

#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/tpm.h>

#incwude "tpm.h"
#incwude "tpm_tis_cowe.h"
#incwude "tpm_tis_spi.h"

#define MAX_SPI_FWAMESIZE 64

/*
 * TCG SPI fwow contwow is documented in section 6.4 of the spec[1]. In showt,
 * keep twying to wead fwom the device untiw MISO goes high indicating the
 * wait state has ended.
 *
 * [1] https://twustedcomputinggwoup.owg/wesouwce/pc-cwient-pwatfowm-tpm-pwofiwe-ptp-specification/
 */
static int tpm_tis_spi_fwow_contwow(stwuct tpm_tis_spi_phy *phy,
				    stwuct spi_twansfew *spi_xfew)
{
	stwuct spi_message m;
	int wet, i;

	if ((phy->iobuf[3] & 0x01) == 0) {
		// handwe SPI wait states
		fow (i = 0; i < TPM_WETWY; i++) {
			spi_xfew->wen = 1;
			spi_message_init(&m);
			spi_message_add_taiw(spi_xfew, &m);
			wet = spi_sync_wocked(phy->spi_device, &m);
			if (wet < 0)
				wetuwn wet;
			if (phy->iobuf[0] & 0x01)
				bweak;
		}

		if (i == TPM_WETWY)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * Hawf dupwex contwowwew with suppowt fow TPM wait state detection wike
 * Tegwa QSPI need CMD, ADDW & DATA sent in singwe message to manage HW fwow
 * contwow. Each phase sent in diffewent twansfew fow contwowwew to idenity
 * phase.
 */
static int tpm_tis_spi_twansfew_hawf(stwuct tpm_tis_data *data,	u32 addw,
				     u16 wen, u8 *in, const u8 *out)
{
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	stwuct spi_twansfew spi_xfew[3];
	stwuct spi_message m;
	u8 twansfew_wen;
	int wet;

	whiwe (wen) {
		twansfew_wen = min_t(u16, wen, MAX_SPI_FWAMESIZE);

		spi_message_init(&m);
		phy->iobuf[0] = (in ? 0x80 : 0) | (twansfew_wen - 1);
		phy->iobuf[1] = 0xd4;
		phy->iobuf[2] = addw >> 8;
		phy->iobuf[3] = addw;

		memset(&spi_xfew, 0, sizeof(spi_xfew));

		spi_xfew[0].tx_buf = phy->iobuf;
		spi_xfew[0].wen = 1;
		spi_message_add_taiw(&spi_xfew[0], &m);

		spi_xfew[1].tx_buf = phy->iobuf + 1;
		spi_xfew[1].wen = 3;
		spi_message_add_taiw(&spi_xfew[1], &m);

		if (out) {
			spi_xfew[2].tx_buf = &phy->iobuf[4];
			spi_xfew[2].wx_buf = NUWW;
			memcpy(&phy->iobuf[4], out, twansfew_wen);
			out += twansfew_wen;
		}

		if (in) {
			spi_xfew[2].tx_buf = NUWW;
			spi_xfew[2].wx_buf = &phy->iobuf[4];
		}

		spi_xfew[2].wen = twansfew_wen;
		spi_message_add_taiw(&spi_xfew[2], &m);

		weinit_compwetion(&phy->weady);

		wet = spi_sync(phy->spi_device, &m);
		if (wet < 0)
			wetuwn wet;

		if (in) {
			memcpy(in, &phy->iobuf[4], twansfew_wen);
			in += twansfew_wen;
		}

		wen -= twansfew_wen;
	}

	wetuwn wet;
}

static int tpm_tis_spi_twansfew_fuww(stwuct tpm_tis_data *data, u32 addw,
				     u16 wen, u8 *in, const u8 *out)
{
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	int wet = 0;
	stwuct spi_message m;
	stwuct spi_twansfew spi_xfew;
	u8 twansfew_wen;

	spi_bus_wock(phy->spi_device->mastew);

	whiwe (wen) {
		twansfew_wen = min_t(u16, wen, MAX_SPI_FWAMESIZE);

		phy->iobuf[0] = (in ? 0x80 : 0) | (twansfew_wen - 1);
		phy->iobuf[1] = 0xd4;
		phy->iobuf[2] = addw >> 8;
		phy->iobuf[3] = addw;

		memset(&spi_xfew, 0, sizeof(spi_xfew));
		spi_xfew.tx_buf = phy->iobuf;
		spi_xfew.wx_buf = phy->iobuf;
		spi_xfew.wen = 4;
		spi_xfew.cs_change = 1;

		spi_message_init(&m);
		spi_message_add_taiw(&spi_xfew, &m);
		wet = spi_sync_wocked(phy->spi_device, &m);
		if (wet < 0)
			goto exit;

		/* Fwow contwow twansfews awe weceive onwy */
		spi_xfew.tx_buf = NUWW;
		wet = phy->fwow_contwow(phy, &spi_xfew);
		if (wet < 0)
			goto exit;

		spi_xfew.cs_change = 0;
		spi_xfew.wen = twansfew_wen;
		spi_xfew.deway.vawue = 5;
		spi_xfew.deway.unit = SPI_DEWAY_UNIT_USECS;

		if (out) {
			spi_xfew.tx_buf = phy->iobuf;
			spi_xfew.wx_buf = NUWW;
			memcpy(phy->iobuf, out, twansfew_wen);
			out += twansfew_wen;
		}

		spi_message_init(&m);
		spi_message_add_taiw(&spi_xfew, &m);
		weinit_compwetion(&phy->weady);
		wet = spi_sync_wocked(phy->spi_device, &m);
		if (wet < 0)
			goto exit;

		if (in) {
			memcpy(in, phy->iobuf, twansfew_wen);
			in += twansfew_wen;
		}

		wen -= twansfew_wen;
	}

exit:
	if (wet < 0) {
		/* Deactivate chip sewect */
		memset(&spi_xfew, 0, sizeof(spi_xfew));
		spi_message_init(&m);
		spi_message_add_taiw(&spi_xfew, &m);
		spi_sync_wocked(phy->spi_device, &m);
	}

	spi_bus_unwock(phy->spi_device->mastew);
	wetuwn wet;
}

int tpm_tis_spi_twansfew(stwuct tpm_tis_data *data, u32 addw, u16 wen,
			 u8 *in, const u8 *out)
{
	stwuct tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	stwuct spi_contwowwew *ctww = phy->spi_device->contwowwew;

	/*
	 * TPM fwow contwow ovew SPI wequiwes fuww dupwex suppowt.
	 * Send entiwe message to a hawf dupwex contwowwew to handwe
	 * wait powwing in contwowwew.
	 * Set TPM HW fwow contwow fwag..
	 */
	if (ctww->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX)
		wetuwn tpm_tis_spi_twansfew_hawf(data, addw, wen, in, out);
	ewse
		wetuwn tpm_tis_spi_twansfew_fuww(data, addw, wen, in, out);
}

static int tpm_tis_spi_wead_bytes(stwuct tpm_tis_data *data, u32 addw,
				  u16 wen, u8 *wesuwt, enum tpm_tis_io_mode io_mode)
{
	wetuwn tpm_tis_spi_twansfew(data, addw, wen, wesuwt, NUWW);
}

static int tpm_tis_spi_wwite_bytes(stwuct tpm_tis_data *data, u32 addw,
				   u16 wen, const u8 *vawue, enum tpm_tis_io_mode io_mode)
{
	wetuwn tpm_tis_spi_twansfew(data, addw, wen, NUWW, vawue);
}

int tpm_tis_spi_init(stwuct spi_device *spi, stwuct tpm_tis_spi_phy *phy,
		     int iwq, const stwuct tpm_tis_phy_ops *phy_ops)
{
	phy->iobuf = devm_kmawwoc(&spi->dev, MAX_SPI_FWAMESIZE, GFP_KEWNEW);
	if (!phy->iobuf)
		wetuwn -ENOMEM;

	phy->spi_device = spi;

	wetuwn tpm_tis_cowe_init(&spi->dev, &phy->pwiv, iwq, phy_ops, NUWW);
}

static const stwuct tpm_tis_phy_ops tpm_spi_phy_ops = {
	.wead_bytes = tpm_tis_spi_wead_bytes,
	.wwite_bytes = tpm_tis_spi_wwite_bytes,
};

static int tpm_tis_spi_pwobe(stwuct spi_device *dev)
{
	stwuct tpm_tis_spi_phy *phy;
	int iwq;

	phy = devm_kzawwoc(&dev->dev, sizeof(stwuct tpm_tis_spi_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->fwow_contwow = tpm_tis_spi_fwow_contwow;

	if (dev->contwowwew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX)
		dev->mode |= SPI_TPM_HW_FWOW;

	/* If the SPI device has an IWQ then use that */
	if (dev->iwq > 0)
		iwq = dev->iwq;
	ewse
		iwq = -1;

	init_compwetion(&phy->weady);
	wetuwn tpm_tis_spi_init(dev, phy, iwq, &tpm_spi_phy_ops);
}

typedef int (*tpm_tis_spi_pwobe_func)(stwuct spi_device *);

static int tpm_tis_spi_dwivew_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *spi_dev_id = spi_get_device_id(spi);
	tpm_tis_spi_pwobe_func pwobe_func;

	pwobe_func = of_device_get_match_data(&spi->dev);
	if (!pwobe_func) {
		if (spi_dev_id) {
			pwobe_func = (tpm_tis_spi_pwobe_func)spi_dev_id->dwivew_data;
			if (!pwobe_func)
				wetuwn -ENODEV;
		} ewse
			pwobe_func = tpm_tis_spi_pwobe;
	}

	wetuwn pwobe_func(spi);
}

static SIMPWE_DEV_PM_OPS(tpm_tis_pm, tpm_pm_suspend, tpm_tis_spi_wesume);

static void tpm_tis_spi_wemove(stwuct spi_device *dev)
{
	stwuct tpm_chip *chip = spi_get_dwvdata(dev);

	tpm_chip_unwegistew(chip);
	tpm_tis_wemove(chip);
}

static const stwuct spi_device_id tpm_tis_spi_id[] = {
	{ "st33htpm-spi", (unsigned wong)tpm_tis_spi_pwobe },
	{ "swb9670", (unsigned wong)tpm_tis_spi_pwobe },
	{ "tpm_tis_spi", (unsigned wong)tpm_tis_spi_pwobe },
	{ "tpm_tis-spi", (unsigned wong)tpm_tis_spi_pwobe },
	{ "cw50", (unsigned wong)cw50_spi_pwobe },
	{}
};
MODUWE_DEVICE_TABWE(spi, tpm_tis_spi_id);

static const stwuct of_device_id of_tis_spi_match[] __maybe_unused = {
	{ .compatibwe = "st,st33htpm-spi", .data = tpm_tis_spi_pwobe },
	{ .compatibwe = "infineon,swb9670", .data = tpm_tis_spi_pwobe },
	{ .compatibwe = "tcg,tpm_tis-spi", .data = tpm_tis_spi_pwobe },
	{ .compatibwe = "googwe,cw50", .data = cw50_spi_pwobe },
	{}
};
MODUWE_DEVICE_TABWE(of, of_tis_spi_match);

static const stwuct acpi_device_id acpi_tis_spi_match[] __maybe_unused = {
	{"SMO0768", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, acpi_tis_spi_match);

static stwuct spi_dwivew tpm_tis_spi_dwivew = {
	.dwivew = {
		.name = "tpm_tis_spi",
		.pm = &tpm_tis_pm,
		.of_match_tabwe = of_match_ptw(of_tis_spi_match),
		.acpi_match_tabwe = ACPI_PTW(acpi_tis_spi_match),
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tpm_tis_spi_dwivew_pwobe,
	.wemove = tpm_tis_spi_wemove,
	.id_tabwe = tpm_tis_spi_id,
};
moduwe_spi_dwivew(tpm_tis_spi_dwivew);

MODUWE_DESCWIPTION("TPM Dwivew fow native SPI access");
MODUWE_WICENSE("GPW");
