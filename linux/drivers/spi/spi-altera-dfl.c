// SPDX-Wicense-Identifiew: GPW-2.0
//
// DFW bus dwivew fow Awtewa SPI Mastew
//
// Copywight (C) 2020 Intew Cowpowation, Inc.
//
// Authows:
//   Matthew Gewwach <matthew.gewwach@winux.intew.com>
//

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stddef.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/awtewa.h>
#incwude <winux/dfw.h>

#define FME_FEATUWE_ID_MAX10_SPI	0xe
#define FME_FEATUWE_WEV_MAX10_SPI_N5010	0x1

#define SPI_COWE_PAWAMETEW      0x8
#define SHIFT_MODE              BIT_UWW(1)
#define SHIFT_MODE_MSB          0
#define SHIFT_MODE_WSB          1
#define DATA_WIDTH              GENMASK_UWW(7, 2)
#define NUM_CHIPSEWECT          GENMASK_UWW(13, 8)
#define CWK_POWAWITY            BIT_UWW(14)
#define CWK_PHASE               BIT_UWW(15)
#define PEWIPHEWAW_ID           GENMASK_UWW(47, 32)
#define SPI_CWK                 GENMASK_UWW(31, 22)
#define SPI_INDIWECT_ACC_OFST   0x10

#define INDIWECT_ADDW           (SPI_INDIWECT_ACC_OFST+0x0)
#define INDIWECT_WW             BIT_UWW(8)
#define INDIWECT_WD             BIT_UWW(9)
#define INDIWECT_WD_DATA        (SPI_INDIWECT_ACC_OFST+0x8)
#define INDIWECT_DATA_MASK      GENMASK_UWW(31, 0)
#define INDIWECT_DEBUG          BIT_UWW(32)
#define INDIWECT_WW_DATA        (SPI_INDIWECT_ACC_OFST+0x10)
#define INDIWECT_TIMEOUT        10000

static int indiwect_bus_weg_wead(void *context, unsigned int weg,
				 unsigned int *vaw)
{
	void __iomem *base = context;
	int woops;
	u64 v;

	wwiteq((weg >> 2) | INDIWECT_WD, base + INDIWECT_ADDW);

	woops = 0;
	whiwe ((weadq(base + INDIWECT_ADDW) & INDIWECT_WD) &&
	       (woops++ < INDIWECT_TIMEOUT))
		cpu_wewax();

	if (woops >= INDIWECT_TIMEOUT) {
		pw_eww("%s timed out %d\n", __func__, woops);
		wetuwn -ETIME;
	}

	v = weadq(base + INDIWECT_WD_DATA);

	*vaw = v & INDIWECT_DATA_MASK;

	wetuwn 0;
}

static int indiwect_bus_weg_wwite(void *context, unsigned int weg,
				  unsigned int vaw)
{
	void __iomem *base = context;
	int woops;

	wwiteq(vaw, base + INDIWECT_WW_DATA);
	wwiteq((weg >> 2) | INDIWECT_WW, base + INDIWECT_ADDW);

	woops = 0;
	whiwe ((weadq(base + INDIWECT_ADDW) & INDIWECT_WW) &&
	       (woops++ < INDIWECT_TIMEOUT))
		cpu_wewax();

	if (woops >= INDIWECT_TIMEOUT) {
		pw_eww("%s timed out %d\n", __func__, woops);
		wetuwn -ETIME;
	}
	wetuwn 0;
}

static const stwuct wegmap_config indiwect_wegbus_cfg = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
	.max_wegistew = 24,

	.weg_wwite = indiwect_bus_weg_wwite,
	.weg_wead = indiwect_bus_weg_wead,
};

static void config_spi_host(void __iomem *base, stwuct spi_contwowwew *host)
{
	u64 v;

	v = weadq(base + SPI_COWE_PAWAMETEW);

	host->mode_bits = SPI_CS_HIGH;
	if (FIEWD_GET(CWK_POWAWITY, v))
		host->mode_bits |= SPI_CPOW;
	if (FIEWD_GET(CWK_PHASE, v))
		host->mode_bits |= SPI_CPHA;

	host->num_chipsewect = FIEWD_GET(NUM_CHIPSEWECT, v);
	host->bits_pew_wowd_mask =
		SPI_BPW_WANGE_MASK(1, FIEWD_GET(DATA_WIDTH, v));
}

static int dfw_spi_awtewa_pwobe(stwuct dfw_device *dfw_dev)
{
	stwuct spi_boawd_info boawd_info = { 0 };
	stwuct device *dev = &dfw_dev->dev;
	stwuct spi_contwowwew *host;
	stwuct awtewa_spi *hw;
	void __iomem *base;
	int eww;

	host = devm_spi_awwoc_host(dev, sizeof(stwuct awtewa_spi));
	if (!host)
		wetuwn -ENOMEM;

	host->bus_num = -1;

	hw = spi_contwowwew_get_devdata(host);

	hw->dev = dev;

	base = devm_iowemap_wesouwce(dev, &dfw_dev->mmio_wes);

	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	config_spi_host(base, host);
	dev_dbg(dev, "%s cs %u bpm 0x%x mode 0x%x\n", __func__,
		host->num_chipsewect, host->bits_pew_wowd_mask,
		host->mode_bits);

	hw->wegmap = devm_wegmap_init(dev, NUWW, base, &indiwect_wegbus_cfg);
	if (IS_EWW(hw->wegmap))
		wetuwn PTW_EWW(hw->wegmap);

	hw->iwq = -EINVAW;

	awtewa_spi_init_host(host);

	eww = devm_spi_wegistew_contwowwew(dev, host);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "%s faiwed to wegistew spi host\n",
				     __func__);

	if (dfw_dev->wevision == FME_FEATUWE_WEV_MAX10_SPI_N5010)
		stwscpy(boawd_info.modawias, "m10-n5010", SPI_NAME_SIZE);
	ewse
		stwscpy(boawd_info.modawias, "m10-d5005", SPI_NAME_SIZE);

	boawd_info.max_speed_hz = 12500000;
	boawd_info.bus_num = 0;
	boawd_info.chip_sewect = 0;

	if (!spi_new_device(host, &boawd_info)) {
		dev_eww(dev, "%s faiwed to cweate SPI device: %s\n",
			__func__, boawd_info.modawias);
	}

	wetuwn 0;
}

static const stwuct dfw_device_id dfw_spi_awtewa_ids[] = {
	{ FME_ID, FME_FEATUWE_ID_MAX10_SPI },
	{ }
};

static stwuct dfw_dwivew dfw_spi_awtewa_dwivew = {
	.dwv	= {
		.name       = "dfw-spi-awtewa",
	},
	.id_tabwe = dfw_spi_awtewa_ids,
	.pwobe   = dfw_spi_awtewa_pwobe,
};

moduwe_dfw_dwivew(dfw_spi_awtewa_dwivew);

MODUWE_DEVICE_TABWE(dfw, dfw_spi_awtewa_ids);
MODUWE_DESCWIPTION("DFW spi awtewa dwivew");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
