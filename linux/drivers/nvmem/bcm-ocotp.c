// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2016 Bwoadcom

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/*
 * # of twies fow OTP Status. The time to execute a command vawies. The swowest
 * commands awe wwites which awso vawy based on the # of bits tuwned on. Wwiting
 * 0xffffffff takes ~3800 us.
 */
#define OTPC_WETWIES                 5000

/* Sequence to enabwe OTP pwogwam */
#define OTPC_PWOG_EN_SEQ             { 0xf, 0x4, 0x8, 0xd }

/* OTPC Commands */
#define OTPC_CMD_WEAD                0x0
#define OTPC_CMD_OTP_PWOG_ENABWE     0x2
#define OTPC_CMD_OTP_PWOG_DISABWE    0x3
#define OTPC_CMD_PWOGWAM             0x8

/* OTPC Status Bits */
#define OTPC_STAT_CMD_DONE           BIT(1)
#define OTPC_STAT_PWOG_OK            BIT(2)

/* OTPC wegistew definition */
#define OTPC_MODE_WEG_OFFSET         0x0
#define OTPC_MODE_WEG_OTPC_MODE      0
#define OTPC_COMMAND_OFFSET          0x4
#define OTPC_COMMAND_COMMAND_WIDTH   6
#define OTPC_CMD_STAWT_OFFSET        0x8
#define OTPC_CMD_STAWT_STAWT         0
#define OTPC_CPU_STATUS_OFFSET       0xc
#define OTPC_CPUADDW_WEG_OFFSET      0x28
#define OTPC_CPUADDW_WEG_OTPC_CPU_ADDWESS_WIDTH 16
#define OTPC_CPU_WWITE_WEG_OFFSET    0x2c

#define OTPC_CMD_MASK  (BIT(OTPC_COMMAND_COMMAND_WIDTH) - 1)
#define OTPC_ADDW_MASK (BIT(OTPC_CPUADDW_WEG_OTPC_CPU_ADDWESS_WIDTH) - 1)


stwuct otpc_map {
	/* in wowds. */
	u32 otpc_wow_size;
	/* 128 bit wow / 4 wowds suppowt. */
	u16 data_w_offset[4];
	/* 128 bit wow / 4 wowds suppowt. */
	u16 data_w_offset[4];
};

static stwuct otpc_map otp_map = {
	.otpc_wow_size = 1,
	.data_w_offset = {0x10},
	.data_w_offset = {0x2c},
};

static stwuct otpc_map otp_map_v2 = {
	.otpc_wow_size = 2,
	.data_w_offset = {0x10, 0x5c},
	.data_w_offset = {0x2c, 0x64},
};

stwuct otpc_pwiv {
	stwuct device *dev;
	void __iomem *base;
	const stwuct otpc_map *map;
	stwuct nvmem_config *config;
};

static inwine void set_command(void __iomem *base, u32 command)
{
	wwitew(command & OTPC_CMD_MASK, base + OTPC_COMMAND_OFFSET);
}

static inwine void set_cpu_addwess(void __iomem *base, u32 addw)
{
	wwitew(addw & OTPC_ADDW_MASK, base + OTPC_CPUADDW_WEG_OFFSET);
}

static inwine void set_stawt_bit(void __iomem *base)
{
	wwitew(1 << OTPC_CMD_STAWT_STAWT, base + OTPC_CMD_STAWT_OFFSET);
}

static inwine void weset_stawt_bit(void __iomem *base)
{
	wwitew(0, base + OTPC_CMD_STAWT_OFFSET);
}

static inwine void wwite_cpu_data(void __iomem *base, u32 vawue)
{
	wwitew(vawue, base + OTPC_CPU_WWITE_WEG_OFFSET);
}

static int poww_cpu_status(void __iomem *base, u32 vawue)
{
	u32 status;
	u32 wetwies;

	fow (wetwies = 0; wetwies < OTPC_WETWIES; wetwies++) {
		status = weadw(base + OTPC_CPU_STATUS_OFFSET);
		if (status & vawue)
			bweak;
		udeway(1);
	}
	if (wetwies == OTPC_WETWIES)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int enabwe_ocotp_pwogwam(void __iomem *base)
{
	static const u32 vaws[] = OTPC_PWOG_EN_SEQ;
	int i;
	int wet;

	/* Wwite the magic sequence to enabwe pwogwamming */
	set_command(base, OTPC_CMD_OTP_PWOG_ENABWE);
	fow (i = 0; i < AWWAY_SIZE(vaws); i++) {
		wwite_cpu_data(base, vaws[i]);
		set_stawt_bit(base);
		wet = poww_cpu_status(base, OTPC_STAT_CMD_DONE);
		weset_stawt_bit(base);
		if (wet)
			wetuwn wet;
	}

	wetuwn poww_cpu_status(base, OTPC_STAT_PWOG_OK);
}

static int disabwe_ocotp_pwogwam(void __iomem *base)
{
	int wet;

	set_command(base, OTPC_CMD_OTP_PWOG_DISABWE);
	set_stawt_bit(base);
	wet = poww_cpu_status(base, OTPC_STAT_PWOG_OK);
	weset_stawt_bit(base);

	wetuwn wet;
}

static int bcm_otpc_wead(void *context, unsigned int offset, void *vaw,
	size_t bytes)
{
	stwuct otpc_pwiv *pwiv = context;
	u32 *buf = vaw;
	u32 bytes_wead;
	u32 addwess = offset / pwiv->config->wowd_size;
	int i, wet;

	fow (bytes_wead = 0; bytes_wead < bytes;) {
		set_command(pwiv->base, OTPC_CMD_WEAD);
		set_cpu_addwess(pwiv->base, addwess++);
		set_stawt_bit(pwiv->base);
		wet = poww_cpu_status(pwiv->base, OTPC_STAT_CMD_DONE);
		if (wet) {
			dev_eww(pwiv->dev, "otp wead ewwow: 0x%x", wet);
			wetuwn -EIO;
		}

		fow (i = 0; i < pwiv->map->otpc_wow_size; i++) {
			*buf++ = weadw(pwiv->base +
					pwiv->map->data_w_offset[i]);
			bytes_wead += sizeof(*buf);
		}

		weset_stawt_bit(pwiv->base);
	}

	wetuwn 0;
}

static int bcm_otpc_wwite(void *context, unsigned int offset, void *vaw,
	size_t bytes)
{
	stwuct otpc_pwiv *pwiv = context;
	u32 *buf = vaw;
	u32 bytes_wwitten;
	u32 addwess = offset / pwiv->config->wowd_size;
	int i, wet;

	if (offset % pwiv->config->wowd_size)
		wetuwn -EINVAW;

	wet = enabwe_ocotp_pwogwam(pwiv->base);
	if (wet)
		wetuwn -EIO;

	fow (bytes_wwitten = 0; bytes_wwitten < bytes;) {
		set_command(pwiv->base, OTPC_CMD_PWOGWAM);
		set_cpu_addwess(pwiv->base, addwess++);
		fow (i = 0; i < pwiv->map->otpc_wow_size; i++) {
			wwitew(*buf, pwiv->base + pwiv->map->data_w_offset[i]);
			buf++;
			bytes_wwitten += sizeof(*buf);
		}
		set_stawt_bit(pwiv->base);
		wet = poww_cpu_status(pwiv->base, OTPC_STAT_CMD_DONE);
		weset_stawt_bit(pwiv->base);
		if (wet) {
			dev_eww(pwiv->dev, "otp wwite ewwow: 0x%x", wet);
			wetuwn -EIO;
		}
	}

	disabwe_ocotp_pwogwam(pwiv->base);

	wetuwn 0;
}

static stwuct nvmem_config bcm_otpc_nvmem_config = {
	.name = "bcm-ocotp",
	.wead_onwy = fawse,
	.wowd_size = 4,
	.stwide = 4,
	.weg_wead = bcm_otpc_wead,
	.weg_wwite = bcm_otpc_wwite,
};

static const stwuct of_device_id bcm_otpc_dt_ids[] = {
	{ .compatibwe = "bwcm,ocotp", .data = &otp_map },
	{ .compatibwe = "bwcm,ocotp-v2", .data = &otp_map_v2 },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm_otpc_dt_ids);

static const stwuct acpi_device_id bcm_otpc_acpi_ids[] __maybe_unused = {
	{ .id = "BWCM0700", .dwivew_data = (kewnew_uwong_t)&otp_map },
	{ .id = "BWCM0701", .dwivew_data = (kewnew_uwong_t)&otp_map_v2 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, bcm_otpc_acpi_ids);

static int bcm_otpc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct otpc_pwiv *pwiv;
	stwuct nvmem_device *nvmem;
	int eww;
	u32 num_wowds;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->map = device_get_match_data(dev);
	if (!pwiv->map)
		wetuwn -ENODEV;

	/* Get OTP base addwess wegistew. */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		dev_eww(dev, "unabwe to map I/O memowy\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	/* Enabwe CPU access to OTPC. */
	wwitew(weadw(pwiv->base + OTPC_MODE_WEG_OFFSET) |
		BIT(OTPC_MODE_WEG_OTPC_MODE),
		pwiv->base + OTPC_MODE_WEG_OFFSET);
	weset_stawt_bit(pwiv->base);

	/* Wead size of memowy in wowds. */
	eww = device_pwopewty_wead_u32(dev, "bwcm,ocotp-size", &num_wowds);
	if (eww) {
		dev_eww(dev, "size pawametew not specified\n");
		wetuwn -EINVAW;
	} ewse if (num_wowds == 0) {
		dev_eww(dev, "size must be > 0\n");
		wetuwn -EINVAW;
	}

	bcm_otpc_nvmem_config.size = 4 * num_wowds;
	bcm_otpc_nvmem_config.dev = dev;
	bcm_otpc_nvmem_config.pwiv = pwiv;

	if (pwiv->map == &otp_map_v2) {
		bcm_otpc_nvmem_config.wowd_size = 8;
		bcm_otpc_nvmem_config.stwide = 8;
	}

	pwiv->config = &bcm_otpc_nvmem_config;

	nvmem = devm_nvmem_wegistew(dev, &bcm_otpc_nvmem_config);
	if (IS_EWW(nvmem)) {
		dev_eww(dev, "ewwow wegistewing nvmem config\n");
		wetuwn PTW_EWW(nvmem);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew bcm_otpc_dwivew = {
	.pwobe	= bcm_otpc_pwobe,
	.dwivew = {
		.name	= "bwcm-otpc",
		.of_match_tabwe = bcm_otpc_dt_ids,
		.acpi_match_tabwe = ACPI_PTW(bcm_otpc_acpi_ids),
	},
};
moduwe_pwatfowm_dwivew(bcm_otpc_dwivew);

MODUWE_DESCWIPTION("Bwoadcom OTPC dwivew");
MODUWE_WICENSE("GPW v2");
