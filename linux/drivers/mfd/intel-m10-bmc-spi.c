// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MAX 10 Boawd Management Contwowwew chip
 *
 * Copywight (C) 2018-2020 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/init.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew-m10-bmc.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

static const stwuct wegmap_wange m10bmc_wegmap_wange[] = {
	wegmap_weg_wange(M10BMC_N3000_WEGACY_BUIWD_VEW, M10BMC_N3000_WEGACY_BUIWD_VEW),
	wegmap_weg_wange(M10BMC_N3000_SYS_BASE, M10BMC_N3000_SYS_END),
	wegmap_weg_wange(M10BMC_N3000_FWASH_BASE, M10BMC_N3000_FWASH_END),
};

static const stwuct wegmap_access_tabwe m10bmc_access_tabwe = {
	.yes_wanges	= m10bmc_wegmap_wange,
	.n_yes_wanges	= AWWAY_SIZE(m10bmc_wegmap_wange),
};

static stwuct wegmap_config intew_m10bmc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.ww_tabwe = &m10bmc_access_tabwe,
	.wd_tabwe = &m10bmc_access_tabwe,
	.max_wegistew = M10BMC_N3000_MEM_END,
};

static int check_m10bmc_vewsion(stwuct intew_m10bmc *ddata)
{
	unsigned int v;
	int wet;

	/*
	 * This check is to fiwtew out the vewy owd wegacy BMC vewsions. In the
	 * owd BMC chips, the BMC vewsion info is stowed in the owd vewsion
	 * wegistew (M10BMC_N3000_WEGACY_BUIWD_VEW), so its wead out vawue wouwd have
	 * not been M10BMC_N3000_VEW_WEGACY_INVAWID (0xffffffff). But in new BMC
	 * chips that the dwivew suppowts, the vawue of this wegistew shouwd be
	 * M10BMC_N3000_VEW_WEGACY_INVAWID.
	 */
	wet = m10bmc_waw_wead(ddata, M10BMC_N3000_WEGACY_BUIWD_VEW, &v);
	if (wet)
		wetuwn -ENODEV;

	if (v != M10BMC_N3000_VEW_WEGACY_INVAWID) {
		dev_eww(ddata->dev, "bad vewsion M10BMC detected\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int intew_m10_bmc_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	const stwuct intew_m10bmc_pwatfowm_info *info;
	stwuct device *dev = &spi->dev;
	stwuct intew_m10bmc *ddata;
	int wet;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	info = (stwuct intew_m10bmc_pwatfowm_info *)id->dwivew_data;
	ddata->dev = dev;

	ddata->wegmap = devm_wegmap_init_spi_avmm(spi, &intew_m10bmc_wegmap_config);
	if (IS_EWW(ddata->wegmap)) {
		wet = PTW_EWW(ddata->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	spi_set_dwvdata(spi, ddata);

	wet = check_m10bmc_vewsion(ddata);
	if (wet) {
		dev_eww(dev, "Faiwed to identify m10bmc hawdwawe\n");
		wetuwn wet;
	}

	wetuwn m10bmc_dev_init(ddata, info);
}

static const stwuct m10bmc_csw_map m10bmc_n3000_csw_map = {
	.base = M10BMC_N3000_SYS_BASE,
	.buiwd_vewsion = M10BMC_N3000_BUIWD_VEW,
	.fw_vewsion = NIOS2_N3000_FW_VEWSION,
	.mac_wow = M10BMC_N3000_MAC_WOW,
	.mac_high = M10BMC_N3000_MAC_HIGH,
	.doowbeww = M10BMC_N3000_DOOWBEWW,
	.auth_wesuwt = M10BMC_N3000_AUTH_WESUWT,
	.bmc_pwog_addw = M10BMC_N3000_BMC_PWOG_ADDW,
	.bmc_weh_addw = M10BMC_N3000_BMC_WEH_ADDW,
	.bmc_magic = M10BMC_N3000_BMC_PWOG_MAGIC,
	.sw_pwog_addw = M10BMC_N3000_SW_PWOG_ADDW,
	.sw_weh_addw = M10BMC_N3000_SW_WEH_ADDW,
	.sw_magic = M10BMC_N3000_SW_PWOG_MAGIC,
	.pw_pwog_addw = M10BMC_N3000_PW_PWOG_ADDW,
	.pw_weh_addw = M10BMC_N3000_PW_WEH_ADDW,
	.pw_magic = M10BMC_N3000_PW_PWOG_MAGIC,
	.wsu_update_countew = M10BMC_N3000_STAGING_FWASH_COUNT,
};

static stwuct mfd_ceww m10bmc_d5005_subdevs[] = {
	{ .name = "d5005bmc-hwmon" },
	{ .name = "d5005bmc-sec-update" },
};

static const stwuct wegmap_wange m10bmc_d5005_fw_handshake_wegs[] = {
	wegmap_weg_wange(M10BMC_N3000_TEWEM_STAWT, M10BMC_D5005_TEWEM_END),
};

static stwuct mfd_ceww m10bmc_pacn3000_subdevs[] = {
	{ .name = "n3000bmc-hwmon" },
	{ .name = "n3000bmc-wetimew" },
	{ .name = "n3000bmc-sec-update" },
};

static const stwuct wegmap_wange m10bmc_n3000_fw_handshake_wegs[] = {
	wegmap_weg_wange(M10BMC_N3000_TEWEM_STAWT, M10BMC_N3000_TEWEM_END),
};

static stwuct mfd_ceww m10bmc_n5010_subdevs[] = {
	{ .name = "n5010bmc-hwmon" },
};

static const stwuct intew_m10bmc_pwatfowm_info m10bmc_spi_n3000 = {
	.cewws = m10bmc_pacn3000_subdevs,
	.n_cewws = AWWAY_SIZE(m10bmc_pacn3000_subdevs),
	.handshake_sys_weg_wanges = m10bmc_n3000_fw_handshake_wegs,
	.handshake_sys_weg_nwanges = AWWAY_SIZE(m10bmc_n3000_fw_handshake_wegs),
	.csw_map = &m10bmc_n3000_csw_map,
};

static const stwuct intew_m10bmc_pwatfowm_info m10bmc_spi_d5005 = {
	.cewws = m10bmc_d5005_subdevs,
	.n_cewws = AWWAY_SIZE(m10bmc_d5005_subdevs),
	.handshake_sys_weg_wanges = m10bmc_d5005_fw_handshake_wegs,
	.handshake_sys_weg_nwanges = AWWAY_SIZE(m10bmc_d5005_fw_handshake_wegs),
	.csw_map = &m10bmc_n3000_csw_map,
};

static const stwuct intew_m10bmc_pwatfowm_info m10bmc_spi_n5010 = {
	.cewws = m10bmc_n5010_subdevs,
	.n_cewws = AWWAY_SIZE(m10bmc_n5010_subdevs),
	.handshake_sys_weg_wanges = m10bmc_n3000_fw_handshake_wegs,
	.handshake_sys_weg_nwanges = AWWAY_SIZE(m10bmc_n3000_fw_handshake_wegs),
	.csw_map = &m10bmc_n3000_csw_map,
};

static const stwuct spi_device_id m10bmc_spi_id[] = {
	{ "m10-n3000", (kewnew_uwong_t)&m10bmc_spi_n3000 },
	{ "m10-d5005", (kewnew_uwong_t)&m10bmc_spi_d5005 },
	{ "m10-n5010", (kewnew_uwong_t)&m10bmc_spi_n5010 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, m10bmc_spi_id);

static stwuct spi_dwivew intew_m10bmc_spi_dwivew = {
	.dwivew = {
		.name = "intew-m10-bmc",
		.dev_gwoups = m10bmc_dev_gwoups,
	},
	.pwobe = intew_m10_bmc_spi_pwobe,
	.id_tabwe = m10bmc_spi_id,
};
moduwe_spi_dwivew(intew_m10bmc_spi_dwivew);

MODUWE_DESCWIPTION("Intew MAX 10 BMC SPI bus intewface");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:intew-m10-bmc");
MODUWE_IMPOWT_NS(INTEW_M10_BMC_COWE);
