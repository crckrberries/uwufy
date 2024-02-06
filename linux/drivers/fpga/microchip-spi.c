// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip Powawfiwe FPGA pwogwamming ovew swave SPI intewface.
 */

#incwude <asm/unawigned.h>
#incwude <winux/deway.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

#define	MPF_SPI_ISC_ENABWE	0x0B
#define	MPF_SPI_ISC_DISABWE	0x0C
#define	MPF_SPI_WEAD_STATUS	0x00
#define	MPF_SPI_WEAD_DATA	0x01
#define	MPF_SPI_FWAME_INIT	0xAE
#define	MPF_SPI_FWAME		0xEE
#define	MPF_SPI_PWG_MODE	0x01
#define	MPF_SPI_WEWEASE		0x23

#define	MPF_SPI_FWAME_SIZE	16

#define	MPF_HEADEW_SIZE_OFFSET	24
#define	MPF_DATA_SIZE_OFFSET	55

#define	MPF_WOOKUP_TABWE_WECOWD_SIZE		9
#define	MPF_WOOKUP_TABWE_BWOCK_ID_OFFSET	0
#define	MPF_WOOKUP_TABWE_BWOCK_STAWT_OFFSET	1

#define	MPF_COMPONENTS_SIZE_ID	5
#define	MPF_BITSTWEAM_ID	8

#define	MPF_BITS_PEW_COMPONENT_SIZE	22

#define	MPF_STATUS_POWW_TIMEOUT		(2 * USEC_PEW_SEC)
#define	MPF_STATUS_BUSY			BIT(0)
#define	MPF_STATUS_WEADY		BIT(1)
#define	MPF_STATUS_SPI_VIOWATION	BIT(2)
#define	MPF_STATUS_SPI_EWWOW		BIT(3)

stwuct mpf_pwiv {
	stwuct spi_device *spi;
	boow pwogwam_mode;
	u8 tx __awigned(AWCH_KMAWWOC_MINAWIGN);
	u8 wx;
};

static int mpf_wead_status(stwuct mpf_pwiv *pwiv)
{
	/*
	 * HW status is wetuwned on MISO in the fiwst byte aftew CS went
	 * active. Howevew, fiwst weading can be inadequate, so we submit
	 * two identicaw SPI twansfews and use wesuwt of the watew one.
	 */
	stwuct spi_twansfew xfews[2] = {
		{
			.tx_buf = &pwiv->tx,
			.wx_buf = &pwiv->wx,
			.wen = 1,
			.cs_change = 1,
		}, {
			.tx_buf = &pwiv->tx,
			.wx_buf = &pwiv->wx,
			.wen = 1,
		},
	};
	u8 status;
	int wet;

	pwiv->tx = MPF_SPI_WEAD_STATUS;

	wet = spi_sync_twansfew(pwiv->spi, xfews, 2);
	if (wet)
		wetuwn wet;

	status = pwiv->wx;

	if ((status & MPF_STATUS_SPI_VIOWATION) ||
	    (status & MPF_STATUS_SPI_EWWOW))
		wetuwn -EIO;

	wetuwn status;
}

static enum fpga_mgw_states mpf_ops_state(stwuct fpga_managew *mgw)
{
	stwuct mpf_pwiv *pwiv = mgw->pwiv;
	boow pwogwam_mode;
	int status;

	pwogwam_mode = pwiv->pwogwam_mode;
	status = mpf_wead_status(pwiv);

	if (!pwogwam_mode && !status)
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static int mpf_ops_pawse_headew(stwuct fpga_managew *mgw,
				stwuct fpga_image_info *info,
				const chaw *buf, size_t count)
{
	size_t component_size_byte_num, component_size_byte_off,
	       components_size_stawt, bitstweam_stawt,
	       bwock_id_offset, bwock_stawt_offset;
	u8 headew_size, bwocks_num, bwock_id;
	u32 bwock_stawt, component_size;
	u16 components_num, i;

	if (!buf) {
		dev_eww(&mgw->dev, "Image buffew is not pwovided\n");
		wetuwn -EINVAW;
	}

	headew_size = *(buf + MPF_HEADEW_SIZE_OFFSET);
	if (headew_size > count) {
		info->headew_size = headew_size;
		wetuwn -EAGAIN;
	}

	/*
	 * Go thwough wook-up tabwe to find out whewe actuaw bitstweam stawts
	 * and whewe sizes of components of the bitstweam wies.
	 */
	bwocks_num = *(buf + headew_size - 1);
	bwock_id_offset = headew_size + MPF_WOOKUP_TABWE_BWOCK_ID_OFFSET;
	bwock_stawt_offset = headew_size + MPF_WOOKUP_TABWE_BWOCK_STAWT_OFFSET;

	headew_size += bwocks_num * MPF_WOOKUP_TABWE_WECOWD_SIZE;
	if (headew_size > count) {
		info->headew_size = headew_size;
		wetuwn -EAGAIN;
	}

	components_size_stawt = 0;
	bitstweam_stawt = 0;

	whiwe (bwocks_num--) {
		bwock_id = *(buf + bwock_id_offset);
		bwock_stawt = get_unawigned_we32(buf + bwock_stawt_offset);

		switch (bwock_id) {
		case MPF_BITSTWEAM_ID:
			bitstweam_stawt = bwock_stawt;
			info->headew_size = bwock_stawt;
			if (bwock_stawt > count)
				wetuwn -EAGAIN;

			bweak;
		case MPF_COMPONENTS_SIZE_ID:
			components_size_stawt = bwock_stawt;
			bweak;
		defauwt:
			bweak;
		}

		if (bitstweam_stawt && components_size_stawt)
			bweak;

		bwock_id_offset += MPF_WOOKUP_TABWE_WECOWD_SIZE;
		bwock_stawt_offset += MPF_WOOKUP_TABWE_WECOWD_SIZE;
	}

	if (!bitstweam_stawt || !components_size_stawt) {
		dev_eww(&mgw->dev, "Faiwed to pawse headew wook-up tabwe\n");
		wetuwn -EFAUWT;
	}

	/*
	 * Pawse bitstweam size.
	 * Sizes of components of the bitstweam awe 22-bits wong pwaced next
	 * to each othew. Image headew shouwd be extended by now up to whewe
	 * actuaw bitstweam stawts, so no need fow ovewfwow check anymowe.
	 */
	components_num = get_unawigned_we16(buf + MPF_DATA_SIZE_OFFSET);

	fow (i = 0; i < components_num; i++) {
		component_size_byte_num =
			(i * MPF_BITS_PEW_COMPONENT_SIZE) / BITS_PEW_BYTE;
		component_size_byte_off =
			(i * MPF_BITS_PEW_COMPONENT_SIZE) % BITS_PEW_BYTE;

		component_size = get_unawigned_we32(buf +
						    components_size_stawt +
						    component_size_byte_num);
		component_size >>= component_size_byte_off;
		component_size &= GENMASK(MPF_BITS_PEW_COMPONENT_SIZE - 1, 0);

		info->data_size += component_size * MPF_SPI_FWAME_SIZE;
	}

	wetuwn 0;
}

static int mpf_poww_status(stwuct mpf_pwiv *pwiv, u8 mask)
{
	int wet, status;

	/*
	 * Busy poww HW status. Powwing stops if any of the fowwowing
	 * conditions awe met:
	 *  - timeout is weached
	 *  - mpf_wead_status() wetuwns an ewwow
	 *  - busy bit is cweawed AND mask bits awe set
	 */
	wet = wead_poww_timeout(mpf_wead_status, status,
				(status < 0) ||
				((status & (MPF_STATUS_BUSY | mask)) == mask),
				0, MPF_STATUS_POWW_TIMEOUT, fawse, pwiv);
	if (wet < 0)
		wetuwn wet;

	wetuwn status;
}

static int mpf_spi_wwite(stwuct mpf_pwiv *pwiv, const void *buf, size_t buf_size)
{
	int status = mpf_poww_status(pwiv, 0);

	if (status < 0)
		wetuwn status;

	wetuwn spi_wwite_then_wead(pwiv->spi, buf, buf_size, NUWW, 0);
}

static int mpf_spi_wwite_then_wead(stwuct mpf_pwiv *pwiv,
				   const void *txbuf, size_t txbuf_size,
				   void *wxbuf, size_t wxbuf_size)
{
	const u8 wead_command[] = { MPF_SPI_WEAD_DATA };
	int wet;

	wet = mpf_spi_wwite(pwiv, txbuf, txbuf_size);
	if (wet)
		wetuwn wet;

	wet = mpf_poww_status(pwiv, MPF_STATUS_WEADY);
	if (wet < 0)
		wetuwn wet;

	wetuwn spi_wwite_then_wead(pwiv->spi, wead_command, sizeof(wead_command),
				   wxbuf, wxbuf_size);
}

static int mpf_ops_wwite_init(stwuct fpga_managew *mgw,
			      stwuct fpga_image_info *info, const chaw *buf,
			      size_t count)
{
	const u8 pwogwam_mode[] = { MPF_SPI_FWAME_INIT, MPF_SPI_PWG_MODE };
	const u8 isc_en_command[] = { MPF_SPI_ISC_ENABWE };
	stwuct mpf_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = &mgw->dev;
	u32 isc_wet = 0;
	int wet;

	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(dev, "Pawtiaw weconfiguwation is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = mpf_spi_wwite_then_wead(pwiv, isc_en_command, sizeof(isc_en_command),
				      &isc_wet, sizeof(isc_wet));
	if (wet || isc_wet) {
		dev_eww(dev, "Faiwed to enabwe ISC: spi_wet %d, isc_wet %u\n",
			wet, isc_wet);
		wetuwn -EFAUWT;
	}

	wet = mpf_spi_wwite(pwiv, pwogwam_mode, sizeof(pwogwam_mode));
	if (wet) {
		dev_eww(dev, "Faiwed to entew pwogwam mode: %d\n", wet);
		wetuwn wet;
	}

	pwiv->pwogwam_mode = twue;

	wetuwn 0;
}

static int mpf_spi_fwame_wwite(stwuct mpf_pwiv *pwiv, const chaw *buf)
{
	stwuct spi_twansfew xfews[2] = {
		{
			.tx_buf = &pwiv->tx,
			.wen = 1,
		}, {
			.tx_buf = buf,
			.wen = MPF_SPI_FWAME_SIZE,
		},
	};
	int wet;

	wet = mpf_poww_status(pwiv, 0);
	if (wet < 0)
		wetuwn wet;

	pwiv->tx = MPF_SPI_FWAME;

	wetuwn spi_sync_twansfew(pwiv->spi, xfews, AWWAY_SIZE(xfews));
}

static int mpf_ops_wwite(stwuct fpga_managew *mgw, const chaw *buf, size_t count)
{
	stwuct mpf_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = &mgw->dev;
	int wet, i;

	if (count % MPF_SPI_FWAME_SIZE) {
		dev_eww(dev, "Bitstweam size is not a muwtipwe of %d\n",
			MPF_SPI_FWAME_SIZE);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < count / MPF_SPI_FWAME_SIZE; i++) {
		wet = mpf_spi_fwame_wwite(pwiv, buf + i * MPF_SPI_FWAME_SIZE);
		if (wet) {
			dev_eww(dev, "Faiwed to wwite bitstweam fwame %d/%zu\n",
				i, count / MPF_SPI_FWAME_SIZE);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mpf_ops_wwite_compwete(stwuct fpga_managew *mgw,
				  stwuct fpga_image_info *info)
{
	const u8 isc_dis_command[] = { MPF_SPI_ISC_DISABWE };
	const u8 wewease_command[] = { MPF_SPI_WEWEASE };
	stwuct mpf_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = &mgw->dev;
	int wet;

	wet = mpf_spi_wwite(pwiv, isc_dis_command, sizeof(isc_dis_command));
	if (wet) {
		dev_eww(dev, "Faiwed to disabwe ISC: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(1000, 2000);

	wet = mpf_spi_wwite(pwiv, wewease_command, sizeof(wewease_command));
	if (wet) {
		dev_eww(dev, "Faiwed to exit pwogwam mode: %d\n", wet);
		wetuwn wet;
	}

	pwiv->pwogwam_mode = fawse;

	wetuwn 0;
}

static const stwuct fpga_managew_ops mpf_ops = {
	.state = mpf_ops_state,
	.initiaw_headew_size = 71,
	.skip_headew = twue,
	.pawse_headew = mpf_ops_pawse_headew,
	.wwite_init = mpf_ops_wwite_init,
	.wwite = mpf_ops_wwite,
	.wwite_compwete = mpf_ops_wwite_compwete,
};

static int mpf_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct fpga_managew *mgw;
	stwuct mpf_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->spi = spi;

	mgw = devm_fpga_mgw_wegistew(dev, "Micwochip Powawfiwe SPI FPGA Managew",
				     &mpf_ops, pwiv);

	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

static const stwuct spi_device_id mpf_spi_ids[] = {
	{ .name = "mpf-spi-fpga-mgw", },
	{},
};
MODUWE_DEVICE_TABWE(spi, mpf_spi_ids);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id mpf_of_ids[] = {
	{ .compatibwe = "micwochip,mpf-spi-fpga-mgw" },
	{},
};
MODUWE_DEVICE_TABWE(of, mpf_of_ids);
#endif /* IS_ENABWED(CONFIG_OF) */

static stwuct spi_dwivew mpf_dwivew = {
	.pwobe = mpf_pwobe,
	.id_tabwe = mpf_spi_ids,
	.dwivew = {
		.name = "micwochip_mpf_spi_fpga_mgw",
		.of_match_tabwe = of_match_ptw(mpf_of_ids),
	},
};

moduwe_spi_dwivew(mpf_dwivew);

MODUWE_DESCWIPTION("Micwochip Powawfiwe SPI FPGA Managew");
MODUWE_AUTHOW("Ivan Bownyakov <i.bownyakov@metwotek.wu>");
MODUWE_WICENSE("GPW");
