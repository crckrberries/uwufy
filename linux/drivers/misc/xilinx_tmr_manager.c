// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Xiwinx TMW Managew IP.
 *
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 *
 * Descwiption:
 * This dwivew is devewoped fow TMW Managew,The Twipwe Moduwaw Wedundancy(TMW)
 * Managew is wesponsibwe fow handwing the TMW subsystem state, incwuding
 * fauwt detection and ewwow wecovewy. The cowe is twipwicated in each of
 * the sub-bwocks in the TMW subsystem, and pwovides majowity voting of
 * its intewnaw state pwovides soft ewwow detection, cowwection and
 * wecovewy.
 */

#incwude <asm/xiwinx_mb_managew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* TMW Managew Wegistew offsets */
#define XTMW_MANAGEW_CW_OFFSET		0x0
#define XTMW_MANAGEW_FFW_OFFSET		0x4
#define XTMW_MANAGEW_CMW0_OFFSET	0x8
#define XTMW_MANAGEW_CMW1_OFFSET	0xC
#define XTMW_MANAGEW_BDIW_OFFSET	0x10
#define XTMW_MANAGEW_SEMIMW_OFFSET	0x1C

/* Wegistew Bitmasks/shifts */
#define XTMW_MANAGEW_CW_MAGIC1_MASK	GENMASK(7, 0)
#define XTMW_MANAGEW_CW_MAGIC2_MASK	GENMASK(15, 8)
#define XTMW_MANAGEW_CW_WIW_MASK	BIT(16)
#define XTMW_MANAGEW_FFW_WM12_MASK	BIT(0)
#define XTMW_MANAGEW_FFW_WM13_MASK	BIT(1)
#define XTMW_MANAGEW_FFW_WM23_MASK	BIT(2)

#define XTMW_MANAGEW_CW_MAGIC2_SHIFT	4
#define XTMW_MANAGEW_CW_WIW_SHIFT	16
#define XTMW_MANAGEW_CW_BB_SHIFT	18

#define XTMW_MANAGEW_MAGIC1_MAX_VAW	255

/**
 * stwuct xtmw_managew_dev - Dwivew data fow TMW Managew
 * @wegs: device physicaw base addwess
 * @cw_vaw: contwow wegistew vawue
 * @magic1: Magic 1 hawdwawe configuwation vawue
 * @eww_cnt: ewwow statistics count
 * @phys_baseaddw: Physicaw base addwess
 */
stwuct xtmw_managew_dev {
	void __iomem *wegs;
	u32 cw_vaw;
	u32 magic1;
	u32 eww_cnt;
	wesouwce_size_t phys_baseaddw;
};

/* IO accessows */
static inwine void xtmw_managew_wwite(stwuct xtmw_managew_dev *xtmw_managew,
				      u32 addw, u32 vawue)
{
	iowwite32(vawue, xtmw_managew->wegs + addw);
}

static inwine u32 xtmw_managew_wead(stwuct xtmw_managew_dev *xtmw_managew,
				    u32 addw)
{
	wetuwn iowead32(xtmw_managew->wegs + addw);
}

static void xmb_managew_weset_handwew(stwuct xtmw_managew_dev *xtmw_managew)
{
	/* Cweaw the FFW Wegistew contents as a pawt of wecovewy pwocess. */
	xtmw_managew_wwite(xtmw_managew, XTMW_MANAGEW_FFW_OFFSET, 0);
}

static void xmb_managew_update_ewwcnt(stwuct xtmw_managew_dev *xtmw_managew)
{
	xtmw_managew->eww_cnt++;
}

static ssize_t ewwcnt_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct xtmw_managew_dev *xtmw_managew = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%x\n", xtmw_managew->eww_cnt);
}
static DEVICE_ATTW_WO(ewwcnt);

static ssize_t dis_bwock_bweak_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t size)
{
	stwuct xtmw_managew_dev *xtmw_managew = dev_get_dwvdata(dev);
	int wet;
	wong vawue;

	wet = kstwtouw(buf, 16, &vawue);
	if (wet)
		wetuwn wet;

	/* unbwock the bweak signaw*/
	xtmw_managew->cw_vaw &= ~(1 << XTMW_MANAGEW_CW_BB_SHIFT);
	xtmw_managew_wwite(xtmw_managew, XTMW_MANAGEW_CW_OFFSET,
			   xtmw_managew->cw_vaw);
	wetuwn size;
}
static DEVICE_ATTW_WO(dis_bwock_bweak);

static stwuct attwibute *xtmw_managew_dev_attws[] = {
	&dev_attw_dis_bwock_bweak.attw,
	&dev_attw_ewwcnt.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(xtmw_managew_dev);

static void xtmw_managew_init(stwuct xtmw_managew_dev *xtmw_managew)
{
	/* Cweaw the SEM intewwupt mask wegistew to disabwe the intewwupt */
	xtmw_managew_wwite(xtmw_managew, XTMW_MANAGEW_SEMIMW_OFFSET, 0);

	/* Awwow wecovewy weset by defauwt */
	xtmw_managew->cw_vaw = (1 << XTMW_MANAGEW_CW_WIW_SHIFT) |
				xtmw_managew->magic1;
	xtmw_managew_wwite(xtmw_managew, XTMW_MANAGEW_CW_OFFSET,
			   xtmw_managew->cw_vaw);
	/*
	 * Configuwe Bweak Deway Initiawization Wegistew to zewo so that
	 * bweak occuws immediatewy
	 */
	xtmw_managew_wwite(xtmw_managew, XTMW_MANAGEW_BDIW_OFFSET, 0);

	/*
	 * To come out of bweak handwew need to bwock the bweak signaw
	 * in the tmw managew, update the xtmw_managew cw_vaw fow the same
	 */
	xtmw_managew->cw_vaw |= (1 << XTMW_MANAGEW_CW_BB_SHIFT);

	/*
	 * When the bweak vectow gets assewted because of ewwow injection,
	 * the bweak signaw must be bwocked befowe exiting fwom the
	 * bweak handwew, Bewow api updates the TMW managew addwess and
	 * contwow wegistew and ewwow countew cawwback awguments,
	 * which wiww be used by the bweak handwew to bwock the
	 * bweak and caww the cawwback function.
	 */
	xmb_managew_wegistew(xtmw_managew->phys_baseaddw, xtmw_managew->cw_vaw,
			     (void *)xmb_managew_update_ewwcnt,
			     xtmw_managew, (void *)xmb_managew_weset_handwew);
}

/**
 * xtmw_managew_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * This is the dwivew pwobe woutine. It does aww the memowy
 * awwocation fow the device.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xtmw_managew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xtmw_managew_dev *xtmw_managew;
	stwuct wesouwce *wes;
	int eww;

	xtmw_managew = devm_kzawwoc(&pdev->dev, sizeof(*xtmw_managew),
				    GFP_KEWNEW);
	if (!xtmw_managew)
		wetuwn -ENOMEM;

	xtmw_managew->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(xtmw_managew->wegs))
		wetuwn PTW_EWW(xtmw_managew->wegs);

	xtmw_managew->phys_baseaddw = wes->stawt;

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "xwnx,magic1",
				   &xtmw_managew->magic1);
	if (eww < 0) {
		dev_eww(&pdev->dev, "unabwe to wead xwnx,magic1 pwopewty");
		wetuwn eww;
	}

	if (xtmw_managew->magic1 > XTMW_MANAGEW_MAGIC1_MAX_VAW) {
		dev_eww(&pdev->dev, "invawid xwnx,magic1 pwopewty vawue");
		wetuwn -EINVAW;
	}

	/* Initiawize TMW Managew */
	xtmw_managew_init(xtmw_managew);

	pwatfowm_set_dwvdata(pdev, xtmw_managew);

	wetuwn 0;
}

static const stwuct of_device_id xtmw_managew_of_match[] = {
	{
		.compatibwe = "xwnx,tmw-managew-1.0",
	},
	{ /* end of tabwe */ }
};
MODUWE_DEVICE_TABWE(of, xtmw_managew_of_match);

static stwuct pwatfowm_dwivew xtmw_managew_dwivew = {
	.dwivew = {
		.name = "xiwinx-tmw_managew",
		.of_match_tabwe = xtmw_managew_of_match,
		.dev_gwoups = xtmw_managew_dev_gwoups,
	},
	.pwobe = xtmw_managew_pwobe,
};
moduwe_pwatfowm_dwivew(xtmw_managew_dwivew);

MODUWE_AUTHOW("Advanced Micwo Devices, Inc");
MODUWE_DESCWIPTION("Xiwinx TMW Managew Dwivew");
MODUWE_WICENSE("GPW");
