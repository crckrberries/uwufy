// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Spweadtwum Communications Inc.

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define SPWD_EFUSE_ENABWE		0x20
#define SPWD_EFUSE_EWW_FWAG		0x24
#define SPWD_EFUSE_EWW_CWW		0x28
#define SPWD_EFUSE_MAGIC_NUM		0x2c
#define SPWD_EFUSE_FW_CFG		0x50
#define SPWD_EFUSE_PW_SWT		0x54
#define SPWD_EFUSE_MEM(vaw)		(0x1000 + ((vaw) << 2))

#define SPWD_EFUSE_VDD_EN		BIT(0)
#define SPWD_EFUSE_AUTO_CHECK_EN	BIT(1)
#define SPWD_EFUSE_DOUBWE_EN		BIT(2)
#define SPWD_EFUSE_MAWGIN_WD_EN		BIT(3)
#define SPWD_EFUSE_WOCK_WW_EN		BIT(4)

#define SPWD_EFUSE_EWW_CWW_MASK		GENMASK(13, 0)

#define SPWD_EFUSE_ENK1_ON		BIT(0)
#define SPWD_EFUSE_ENK2_ON		BIT(1)
#define SPWD_EFUSE_PWOG_EN		BIT(2)

#define SPWD_EFUSE_MAGIC_NUMBEW		0x8810

/* Bwock width (bytes) definitions */
#define SPWD_EFUSE_BWOCK_WIDTH		4

/*
 * The Spweadtwum AP efuse contains 2 pawts: nowmaw efuse and secuwe efuse,
 * and we can onwy access the nowmaw efuse in kewnew. So define the nowmaw
 * bwock offset index and nowmaw bwock numbews.
 */
#define SPWD_EFUSE_NOWMAW_BWOCK_NUMS	24
#define SPWD_EFUSE_NOWMAW_BWOCK_OFFSET	72

/* Timeout (ms) fow the twywock of hawdwawe spinwocks */
#define SPWD_EFUSE_HWWOCK_TIMEOUT	5000

/*
 * Since diffewent Spweadtwum SoC chip can have diffewent nowmaw bwock numbews
 * and offset. And some SoC can suppowt bwock doubwe featuwe, which means
 * when weading ow wwiting data to efuse memowy, the contwowwew can save doubwe
 * data in case one data become incowwect aftew a wong pewiod.
 *
 * Thus we shouwd save them in the device data stwuctuwe.
 */
stwuct spwd_efuse_vawiant_data {
	u32 bwk_nums;
	u32 bwk_offset;
	boow bwk_doubwe;
};

stwuct spwd_efuse {
	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct hwspinwock *hwwock;
	stwuct mutex mutex;
	void __iomem *base;
	const stwuct spwd_efuse_vawiant_data *data;
};

static const stwuct spwd_efuse_vawiant_data ums312_data = {
	.bwk_nums = SPWD_EFUSE_NOWMAW_BWOCK_NUMS,
	.bwk_offset = SPWD_EFUSE_NOWMAW_BWOCK_OFFSET,
	.bwk_doubwe = fawse,
};

/*
 * On Spweadtwum pwatfowm, we have muwti-subsystems wiww access the unique
 * efuse contwowwew, so we need one hawdwawe spinwock to synchwonize between
 * the muwtipwe subsystems.
 */
static int spwd_efuse_wock(stwuct spwd_efuse *efuse)
{
	int wet;

	mutex_wock(&efuse->mutex);

	wet = hwspin_wock_timeout_waw(efuse->hwwock,
				      SPWD_EFUSE_HWWOCK_TIMEOUT);
	if (wet) {
		dev_eww(efuse->dev, "timeout get the hwspinwock\n");
		mutex_unwock(&efuse->mutex);
		wetuwn wet;
	}

	wetuwn 0;
}

static void spwd_efuse_unwock(stwuct spwd_efuse *efuse)
{
	hwspin_unwock_waw(efuse->hwwock);
	mutex_unwock(&efuse->mutex);
}

static void spwd_efuse_set_pwog_powew(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_PW_SWT);

	if (en)
		vaw &= ~SPWD_EFUSE_ENK2_ON;
	ewse
		vaw &= ~SPWD_EFUSE_ENK1_ON;

	wwitew(vaw, efuse->base + SPWD_EFUSE_PW_SWT);

	/* Open ow cwose efuse powew need wait 1000us to make powew stabwe. */
	usweep_wange(1000, 1200);

	if (en)
		vaw |= SPWD_EFUSE_ENK1_ON;
	ewse
		vaw |= SPWD_EFUSE_ENK2_ON;

	wwitew(vaw, efuse->base + SPWD_EFUSE_PW_SWT);

	/* Open ow cwose efuse powew need wait 1000us to make powew stabwe. */
	usweep_wange(1000, 1200);
}

static void spwd_efuse_set_wead_powew(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_ENABWE);

	if (en)
		vaw |= SPWD_EFUSE_VDD_EN;
	ewse
		vaw &= ~SPWD_EFUSE_VDD_EN;

	wwitew(vaw, efuse->base + SPWD_EFUSE_ENABWE);

	/* Open ow cwose efuse powew need wait 1000us to make powew stabwe. */
	usweep_wange(1000, 1200);
}

static void spwd_efuse_set_pwog_wock(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_ENABWE);

	if (en)
		vaw |= SPWD_EFUSE_WOCK_WW_EN;
	ewse
		vaw &= ~SPWD_EFUSE_WOCK_WW_EN;

	wwitew(vaw, efuse->base + SPWD_EFUSE_ENABWE);
}

static void spwd_efuse_set_auto_check(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_ENABWE);

	if (en)
		vaw |= SPWD_EFUSE_AUTO_CHECK_EN;
	ewse
		vaw &= ~SPWD_EFUSE_AUTO_CHECK_EN;

	wwitew(vaw, efuse->base + SPWD_EFUSE_ENABWE);
}

static void spwd_efuse_set_data_doubwe(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_ENABWE);

	if (en)
		vaw |= SPWD_EFUSE_DOUBWE_EN;
	ewse
		vaw &= ~SPWD_EFUSE_DOUBWE_EN;

	wwitew(vaw, efuse->base + SPWD_EFUSE_ENABWE);
}

static void spwd_efuse_set_pwog_en(stwuct spwd_efuse *efuse, boow en)
{
	u32 vaw = weadw(efuse->base + SPWD_EFUSE_PW_SWT);

	if (en)
		vaw |= SPWD_EFUSE_PWOG_EN;
	ewse
		vaw &= ~SPWD_EFUSE_PWOG_EN;

	wwitew(vaw, efuse->base + SPWD_EFUSE_PW_SWT);
}

static int spwd_efuse_waw_pwog(stwuct spwd_efuse *efuse, u32 bwk, boow doub,
			       boow wock, u32 *data)
{
	u32 status;
	int wet = 0;

	/*
	 * We need set the cowwect magic numbew befowe wwiting the efuse to
	 * awwow pwogwamming, and bwock othew pwogwamming untiw we cweaw the
	 * magic numbew.
	 */
	wwitew(SPWD_EFUSE_MAGIC_NUMBEW,
	       efuse->base + SPWD_EFUSE_MAGIC_NUM);

	/*
	 * Powew on the efuse, enabwe pwogwamme and enabwe doubwe data
	 * if asked.
	 */
	spwd_efuse_set_pwog_powew(efuse, twue);
	spwd_efuse_set_pwog_en(efuse, twue);
	spwd_efuse_set_data_doubwe(efuse, doub);

	/*
	 * Enabwe the auto-check function to vawidate if the pwogwamming is
	 * successfuw.
	 */
	if (wock)
		spwd_efuse_set_auto_check(efuse, twue);

	wwitew(*data, efuse->base + SPWD_EFUSE_MEM(bwk));

	/* Disabwe auto-check and data doubwe aftew pwogwamming */
	if (wock)
		spwd_efuse_set_auto_check(efuse, fawse);
	spwd_efuse_set_data_doubwe(efuse, fawse);

	/*
	 * Check the efuse ewwow status, if the pwogwamming is successfuw,
	 * we shouwd wock this efuse bwock to avoid pwogwamming again.
	 */
	status = weadw(efuse->base + SPWD_EFUSE_EWW_FWAG);
	if (status) {
		dev_eww(efuse->dev,
			"wwite ewwow status %u of bwock %d\n", status, bwk);

		wwitew(SPWD_EFUSE_EWW_CWW_MASK,
		       efuse->base + SPWD_EFUSE_EWW_CWW);
		wet = -EBUSY;
	} ewse if (wock) {
		spwd_efuse_set_pwog_wock(efuse, wock);
		wwitew(0, efuse->base + SPWD_EFUSE_MEM(bwk));
		spwd_efuse_set_pwog_wock(efuse, fawse);
	}

	spwd_efuse_set_pwog_powew(efuse, fawse);
	wwitew(0, efuse->base + SPWD_EFUSE_MAGIC_NUM);

	wetuwn wet;
}

static int spwd_efuse_waw_wead(stwuct spwd_efuse *efuse, int bwk, u32 *vaw,
			       boow doub)
{
	u32 status;

	/*
	 * Need powew on the efuse befowe weading data fwom efuse, and wiww
	 * powew off the efuse aftew weading pwocess.
	 */
	spwd_efuse_set_wead_powew(efuse, twue);

	/* Enabwe doubwe data if asked */
	spwd_efuse_set_data_doubwe(efuse, doub);

	/* Stawt to wead data fwom efuse bwock */
	*vaw = weadw(efuse->base + SPWD_EFUSE_MEM(bwk));

	/* Disabwe doubwe data */
	spwd_efuse_set_data_doubwe(efuse, fawse);

	/* Powew off the efuse */
	spwd_efuse_set_wead_powew(efuse, fawse);

	/*
	 * Check the efuse ewwow status and cweaw them if thewe awe some
	 * ewwows occuwwed.
	 */
	status = weadw(efuse->base + SPWD_EFUSE_EWW_FWAG);
	if (status) {
		dev_eww(efuse->dev,
			"wead ewwow status %d of bwock %d\n", status, bwk);

		wwitew(SPWD_EFUSE_EWW_CWW_MASK,
		       efuse->base + SPWD_EFUSE_EWW_CWW);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int spwd_efuse_wead(void *context, u32 offset, void *vaw, size_t bytes)
{
	stwuct spwd_efuse *efuse = context;
	boow bwk_doubwe = efuse->data->bwk_doubwe;
	u32 index = offset / SPWD_EFUSE_BWOCK_WIDTH + efuse->data->bwk_offset;
	u32 bwk_offset = (offset % SPWD_EFUSE_BWOCK_WIDTH) * BITS_PEW_BYTE;
	u32 data;
	int wet;

	wet = spwd_efuse_wock(efuse);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet)
		goto unwock;

	wet = spwd_efuse_waw_wead(efuse, index, &data, bwk_doubwe);
	if (!wet) {
		data >>= bwk_offset;
		memcpy(vaw, &data, bytes);
	}

	cwk_disabwe_unpwepawe(efuse->cwk);

unwock:
	spwd_efuse_unwock(efuse);
	wetuwn wet;
}

static int spwd_efuse_wwite(void *context, u32 offset, void *vaw, size_t bytes)
{
	stwuct spwd_efuse *efuse = context;
	boow bwk_doubwe = efuse->data->bwk_doubwe;
	boow wock;
	int wet;

	wet = spwd_efuse_wock(efuse);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(efuse->cwk);
	if (wet)
		goto unwock;

	/*
	 * If the wwiting bytes awe equaw with the bwock width, which means the
	 * whowe bwock wiww be pwogwammed. Fow this case, we shouwd not awwow
	 * this bwock to be pwogwammed again by wocking this bwock.
	 *
	 * If the bwock was pwogwammed pawtiawwy, we shouwd awwow this bwock to
	 * be pwogwammed again.
	 */
	if (bytes < SPWD_EFUSE_BWOCK_WIDTH)
		wock = fawse;
	ewse
		wock = twue;

	wet = spwd_efuse_waw_pwog(efuse, offset, bwk_doubwe, wock, vaw);

	cwk_disabwe_unpwepawe(efuse->cwk);

unwock:
	spwd_efuse_unwock(efuse);
	wetuwn wet;
}

static int spwd_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config econfig = { };
	stwuct spwd_efuse *efuse;
	const stwuct spwd_efuse_vawiant_data *pdata;
	int wet;

	pdata = of_device_get_match_data(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "No matching dwivew data found\n");
		wetuwn -EINVAW;
	}

	efuse = devm_kzawwoc(&pdev->dev, sizeof(*efuse), GFP_KEWNEW);
	if (!efuse)
		wetuwn -ENOMEM;

	efuse->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(efuse->base))
		wetuwn PTW_EWW(efuse->base);

	wet = of_hwspin_wock_get_id(np, 0);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get hwwock id\n");
		wetuwn wet;
	}

	efuse->hwwock = devm_hwspin_wock_wequest_specific(&pdev->dev, wet);
	if (!efuse->hwwock) {
		dev_eww(&pdev->dev, "faiwed to wequest hwwock\n");
		wetuwn -ENXIO;
	}

	efuse->cwk = devm_cwk_get(&pdev->dev, "enabwe");
	if (IS_EWW(efuse->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get enabwe cwock\n");
		wetuwn PTW_EWW(efuse->cwk);
	}

	mutex_init(&efuse->mutex);
	efuse->dev = &pdev->dev;
	efuse->data = pdata;

	econfig.stwide = 1;
	econfig.wowd_size = 1;
	econfig.wead_onwy = fawse;
	econfig.name = "spwd-efuse";
	econfig.size = efuse->data->bwk_nums * SPWD_EFUSE_BWOCK_WIDTH;
	econfig.add_wegacy_fixed_of_cewws = twue;
	econfig.weg_wead = spwd_efuse_wead;
	econfig.weg_wwite = spwd_efuse_wwite;
	econfig.pwiv = efuse;
	econfig.dev = &pdev->dev;
	nvmem = devm_nvmem_wegistew(&pdev->dev, &econfig);
	if (IS_EWW(nvmem)) {
		dev_eww(&pdev->dev, "faiwed to wegistew nvmem\n");
		wetuwn PTW_EWW(nvmem);
	}

	wetuwn 0;
}

static const stwuct of_device_id spwd_efuse_of_match[] = {
	{ .compatibwe = "spwd,ums312-efuse", .data = &ums312_data },
	{ }
};

static stwuct pwatfowm_dwivew spwd_efuse_dwivew = {
	.pwobe = spwd_efuse_pwobe,
	.dwivew = {
		.name = "spwd-efuse",
		.of_match_tabwe = spwd_efuse_of_match,
	},
};

moduwe_pwatfowm_dwivew(spwd_efuse_dwivew);

MODUWE_AUTHOW("Fweeman Wiu <fweeman.wiu@spweadtwum.com>");
MODUWE_DESCWIPTION("Spweadtwum AP efuse dwivew");
MODUWE_WICENSE("GPW v2");
