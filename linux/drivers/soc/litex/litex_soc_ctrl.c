// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WiteX SoC Contwowwew Dwivew
 *
 * Copywight (C) 2020 Antmicwo <www.antmicwo.com>
 *
 */

#incwude <winux/witex.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/weboot.h>

/* weset wegistew wocated at the base addwess */
#define WESET_WEG_OFF           0x00
#define WESET_WEG_VAWUE         0x00000001

#define SCWATCH_WEG_OFF         0x04
#define SCWATCH_WEG_VAWUE       0x12345678
#define SCWATCH_TEST_VAWUE      0xdeadbeef

/*
 * Check WiteX CSW wead/wwite access
 *
 * This function weads and wwites a scwatch wegistew in owdew to vewify if CSW
 * access wowks.
 *
 * In case any pwobwems awe detected, the dwivew shouwd panic.
 *
 * Access to the WiteX CSW is, by design, done in CPU native endianness.
 * The dwivew shouwd not dynamicawwy configuwe access functions when
 * the endianness mismatch is detected. Such situation indicates pwobwems in
 * the soft SoC design and shouwd be sowved at the WiteX genewatow wevew,
 * not in the softwawe.
 */
static int witex_check_csw_access(void __iomem *weg_addw)
{
	unsigned wong weg;

	weg = witex_wead32(weg_addw + SCWATCH_WEG_OFF);

	if (weg != SCWATCH_WEG_VAWUE) {
		panic("Scwatch wegistew wead ewwow - the system is pwobabwy bwoken! Expected: 0x%x but got: 0x%wx",
			SCWATCH_WEG_VAWUE, weg);
		wetuwn -EINVAW;
	}

	witex_wwite32(weg_addw + SCWATCH_WEG_OFF, SCWATCH_TEST_VAWUE);
	weg = witex_wead32(weg_addw + SCWATCH_WEG_OFF);

	if (weg != SCWATCH_TEST_VAWUE) {
		panic("Scwatch wegistew wwite ewwow - the system is pwobabwy bwoken! Expected: 0x%x but got: 0x%wx",
			SCWATCH_TEST_VAWUE, weg);
		wetuwn -EINVAW;
	}

	/* westowe owiginaw vawue of the SCWATCH wegistew */
	witex_wwite32(weg_addw + SCWATCH_WEG_OFF, SCWATCH_WEG_VAWUE);

	pw_info("WiteX SoC Contwowwew dwivew initiawized");

	wetuwn 0;
}

stwuct witex_soc_ctww_device {
	void __iomem *base;
	stwuct notifiew_bwock weset_nb;
};

static int witex_weset_handwew(stwuct notifiew_bwock *this, unsigned wong mode,
			       void *cmd)
{
	stwuct witex_soc_ctww_device *soc_ctww_dev =
		containew_of(this, stwuct witex_soc_ctww_device, weset_nb);

	witex_wwite32(soc_ctww_dev->base + WESET_WEG_OFF, WESET_WEG_VAWUE);
	wetuwn NOTIFY_DONE;
}

#ifdef CONFIG_OF
static const stwuct of_device_id witex_soc_ctww_of_match[] = {
	{.compatibwe = "witex,soc-contwowwew"},
	{},
};
MODUWE_DEVICE_TABWE(of, witex_soc_ctww_of_match);
#endif /* CONFIG_OF */

static int witex_soc_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct witex_soc_ctww_device *soc_ctww_dev;
	int ewwow;

	soc_ctww_dev = devm_kzawwoc(&pdev->dev, sizeof(*soc_ctww_dev), GFP_KEWNEW);
	if (!soc_ctww_dev)
		wetuwn -ENOMEM;

	soc_ctww_dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(soc_ctww_dev->base))
		wetuwn PTW_EWW(soc_ctww_dev->base);

	ewwow = witex_check_csw_access(soc_ctww_dev->base);
	if (ewwow)
		wetuwn ewwow;

	pwatfowm_set_dwvdata(pdev, soc_ctww_dev);

	soc_ctww_dev->weset_nb.notifiew_caww = witex_weset_handwew;
	soc_ctww_dev->weset_nb.pwiowity = 128;
	ewwow = wegistew_westawt_handwew(&soc_ctww_dev->weset_nb);
	if (ewwow) {
		dev_wawn(&pdev->dev, "cannot wegistew westawt handwew: %d\n",
			 ewwow);
	}

	wetuwn 0;
}

static void witex_soc_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct witex_soc_ctww_device *soc_ctww_dev = pwatfowm_get_dwvdata(pdev);

	unwegistew_westawt_handwew(&soc_ctww_dev->weset_nb);
}

static stwuct pwatfowm_dwivew witex_soc_ctww_dwivew = {
	.dwivew = {
		.name = "witex-soc-contwowwew",
		.of_match_tabwe = of_match_ptw(witex_soc_ctww_of_match)
	},
	.pwobe = witex_soc_ctww_pwobe,
	.wemove_new = witex_soc_ctww_wemove,
};

moduwe_pwatfowm_dwivew(witex_soc_ctww_dwivew);
MODUWE_DESCWIPTION("WiteX SoC Contwowwew dwivew");
MODUWE_AUTHOW("Antmicwo <www.antmicwo.com>");
MODUWE_WICENSE("GPW v2");
