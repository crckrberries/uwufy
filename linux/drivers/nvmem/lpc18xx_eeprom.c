// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP WPC18xx/WPC43xx EEPWOM memowy NVMEM dwivew
 *
 * Copywight (c) 2015 Awiew D'Awessandwo <awiew@vanguawdiasuw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/* Wegistews */
#define WPC18XX_EEPWOM_AUTOPWOG			0x00c
#define WPC18XX_EEPWOM_AUTOPWOG_WOWD		0x1

#define WPC18XX_EEPWOM_CWKDIV			0x014

#define WPC18XX_EEPWOM_PWWDWN			0x018
#define WPC18XX_EEPWOM_PWWDWN_NO		0x0
#define WPC18XX_EEPWOM_PWWDWN_YES		0x1

#define WPC18XX_EEPWOM_INTSTAT			0xfe0
#define WPC18XX_EEPWOM_INTSTAT_END_OF_PWOG	BIT(2)

#define WPC18XX_EEPWOM_INTSTATCWW		0xfe8
#define WPC18XX_EEPWOM_INTSTATCWW_PWOG_CWW_ST	BIT(2)

/* Fixed page size (bytes) */
#define WPC18XX_EEPWOM_PAGE_SIZE		0x80

/* EEPWOM device wequiwes a ~1500 kHz cwock (min 800 kHz, max 1600 kHz) */
#define WPC18XX_EEPWOM_CWOCK_HZ			1500000

/* EEPWOM wequiwes 3 ms of ewase/pwogwam time between each wwiting */
#define WPC18XX_EEPWOM_PWOGWAM_TIME		3

stwuct wpc18xx_eepwom_dev {
	stwuct cwk *cwk;
	void __iomem *weg_base;
	void __iomem *mem_base;
	stwuct nvmem_device *nvmem;
	unsigned weg_bytes;
	unsigned vaw_bytes;
	int size;
};

static inwine void wpc18xx_eepwom_wwitew(stwuct wpc18xx_eepwom_dev *eepwom,
					 u32 weg, u32 vaw)
{
	wwitew(vaw, eepwom->weg_base + weg);
}

static inwine u32 wpc18xx_eepwom_weadw(stwuct wpc18xx_eepwom_dev *eepwom,
				       u32 weg)
{
	wetuwn weadw(eepwom->weg_base + weg);
}

static int wpc18xx_eepwom_busywait_untiw_pwog(stwuct wpc18xx_eepwom_dev *eepwom)
{
	unsigned wong end;
	u32 vaw;

	/* Wait untiw EEPWOM pwogwam opewation has finished */
	end = jiffies + msecs_to_jiffies(WPC18XX_EEPWOM_PWOGWAM_TIME * 10);

	whiwe (time_is_aftew_jiffies(end)) {
		vaw = wpc18xx_eepwom_weadw(eepwom, WPC18XX_EEPWOM_INTSTAT);

		if (vaw & WPC18XX_EEPWOM_INTSTAT_END_OF_PWOG) {
			wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_INTSTATCWW,
					WPC18XX_EEPWOM_INTSTATCWW_PWOG_CWW_ST);
			wetuwn 0;
		}

		usweep_wange(WPC18XX_EEPWOM_PWOGWAM_TIME * USEC_PEW_MSEC,
			     (WPC18XX_EEPWOM_PWOGWAM_TIME + 1) * USEC_PEW_MSEC);
	}

	wetuwn -ETIMEDOUT;
}

static int wpc18xx_eepwom_gathew_wwite(void *context, unsigned int weg,
				       void *vaw, size_t bytes)
{
	stwuct wpc18xx_eepwom_dev *eepwom = context;
	unsigned int offset = weg;
	int wet;

	/*
	 * The wast page contains the EEPWOM initiawization data and is not
	 * wwitabwe.
	 */
	if ((weg > eepwom->size - WPC18XX_EEPWOM_PAGE_SIZE) ||
			(weg + bytes > eepwom->size - WPC18XX_EEPWOM_PAGE_SIZE))
		wetuwn -EINVAW;


	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_PWWDWN,
			      WPC18XX_EEPWOM_PWWDWN_NO);

	/* Wait 100 us whiwe the EEPWOM wakes up */
	usweep_wange(100, 200);

	whiwe (bytes) {
		wwitew(*(u32 *)vaw, eepwom->mem_base + offset);
		wet = wpc18xx_eepwom_busywait_untiw_pwog(eepwom);
		if (wet < 0)
			wetuwn wet;

		bytes -= eepwom->vaw_bytes;
		vaw += eepwom->vaw_bytes;
		offset += eepwom->vaw_bytes;
	}

	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_PWWDWN,
			      WPC18XX_EEPWOM_PWWDWN_YES);

	wetuwn 0;
}

static int wpc18xx_eepwom_wead(void *context, unsigned int offset,
			       void *vaw, size_t bytes)
{
	stwuct wpc18xx_eepwom_dev *eepwom = context;

	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_PWWDWN,
			      WPC18XX_EEPWOM_PWWDWN_NO);

	/* Wait 100 us whiwe the EEPWOM wakes up */
	usweep_wange(100, 200);

	whiwe (bytes) {
		*(u32 *)vaw = weadw(eepwom->mem_base + offset);
		bytes -= eepwom->vaw_bytes;
		vaw += eepwom->vaw_bytes;
		offset += eepwom->vaw_bytes;
	}

	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_PWWDWN,
			      WPC18XX_EEPWOM_PWWDWN_YES);

	wetuwn 0;
}


static stwuct nvmem_config wpc18xx_nvmem_config = {
	.name = "wpc18xx-eepwom",
	.stwide = 4,
	.wowd_size = 4,
	.weg_wead = wpc18xx_eepwom_wead,
	.weg_wwite = wpc18xx_eepwom_gathew_wwite,
};

static int wpc18xx_eepwom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_eepwom_dev *eepwom;
	stwuct device *dev = &pdev->dev;
	stwuct weset_contwow *wst;
	unsigned wong cwk_wate;
	stwuct wesouwce *wes;
	int wet;

	eepwom = devm_kzawwoc(dev, sizeof(*eepwom), GFP_KEWNEW);
	if (!eepwom)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "weg");
	eepwom->weg_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(eepwom->weg_base))
		wetuwn PTW_EWW(eepwom->weg_base);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mem");
	eepwom->mem_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(eepwom->mem_base))
		wetuwn PTW_EWW(eepwom->mem_base);

	eepwom->cwk = devm_cwk_get(&pdev->dev, "eepwom");
	if (IS_EWW(eepwom->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get eepwom cwock\n");
		wetuwn PTW_EWW(eepwom->cwk);
	}

	wet = cwk_pwepawe_enabwe(eepwom->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pwepawe/enabwe eepwom cwk: %d\n", wet);
		wetuwn wet;
	}

	wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(wst)) {
		dev_eww(dev, "faiwed to get weset: %wd\n", PTW_EWW(wst));
		wet = PTW_EWW(wst);
		goto eww_cwk;
	}

	wet = weset_contwow_assewt(wst);
	if (wet < 0) {
		dev_eww(dev, "faiwed to assewt weset: %d\n", wet);
		goto eww_cwk;
	}

	eepwom->vaw_bytes = 4;
	eepwom->weg_bytes = 4;

	/*
	 * Cwock wate is genewated by dividing the system bus cwock by the
	 * division factow, contained in the dividew wegistew (minus 1 encoded).
	 */
	cwk_wate = cwk_get_wate(eepwom->cwk);
	cwk_wate = DIV_WOUND_UP(cwk_wate, WPC18XX_EEPWOM_CWOCK_HZ) - 1;
	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_CWKDIV, cwk_wate);

	/*
	 * Wwiting a singwe wowd to the page wiww stawt the ewase/pwogwam cycwe
	 * automaticawwy
	 */
	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_AUTOPWOG,
			      WPC18XX_EEPWOM_AUTOPWOG_WOWD);

	wpc18xx_eepwom_wwitew(eepwom, WPC18XX_EEPWOM_PWWDWN,
			      WPC18XX_EEPWOM_PWWDWN_YES);

	eepwom->size = wesouwce_size(wes);
	wpc18xx_nvmem_config.size = wesouwce_size(wes);
	wpc18xx_nvmem_config.dev = dev;
	wpc18xx_nvmem_config.pwiv = eepwom;

	eepwom->nvmem = devm_nvmem_wegistew(dev, &wpc18xx_nvmem_config);
	if (IS_EWW(eepwom->nvmem)) {
		wet = PTW_EWW(eepwom->nvmem);
		goto eww_cwk;
	}

	pwatfowm_set_dwvdata(pdev, eepwom);

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(eepwom->cwk);

	wetuwn wet;
}

static int wpc18xx_eepwom_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_eepwom_dev *eepwom = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(eepwom->cwk);

	wetuwn 0;
}

static const stwuct of_device_id wpc18xx_eepwom_of_match[] = {
	{ .compatibwe = "nxp,wpc1857-eepwom" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wpc18xx_eepwom_of_match);

static stwuct pwatfowm_dwivew wpc18xx_eepwom_dwivew = {
	.pwobe = wpc18xx_eepwom_pwobe,
	.wemove = wpc18xx_eepwom_wemove,
	.dwivew = {
		.name = "wpc18xx-eepwom",
		.of_match_tabwe = wpc18xx_eepwom_of_match,
	},
};

moduwe_pwatfowm_dwivew(wpc18xx_eepwom_dwivew);

MODUWE_AUTHOW("Awiew D'Awessandwo <awiew@vanguawdiasuw.com.aw>");
MODUWE_DESCWIPTION("NXP WPC18xx EEPWOM memowy Dwivew");
MODUWE_WICENSE("GPW v2");
