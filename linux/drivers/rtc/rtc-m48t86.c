// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST M48T86 / Dawwas DS12887 WTC dwivew
 * Copywight (c) 2006 Towew Technowogies
 *
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * This dwivews onwy suppowts the cwock wunning in BCD and 24H mode.
 * If it wiww be evew adapted to binawy and 12H mode, cawe must be taken
 * to not intwoduce bugs.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcd.h>
#incwude <winux/io.h>

#define M48T86_SEC		0x00
#define M48T86_SECAWWM		0x01
#define M48T86_MIN		0x02
#define M48T86_MINAWWM		0x03
#define M48T86_HOUW		0x04
#define M48T86_HOUWAWWM		0x05
#define M48T86_DOW		0x06 /* 1 = sunday */
#define M48T86_DOM		0x07
#define M48T86_MONTH		0x08 /* 1 - 12 */
#define M48T86_YEAW		0x09 /* 0 - 99 */
#define M48T86_A		0x0a
#define M48T86_B		0x0b
#define M48T86_B_SET		BIT(7)
#define M48T86_B_DM		BIT(2)
#define M48T86_B_H24		BIT(1)
#define M48T86_C		0x0c
#define M48T86_D		0x0d
#define M48T86_D_VWT		BIT(7)
#define M48T86_NVWAM(x)		(0x0e + (x))
#define M48T86_NVWAM_WEN	114

stwuct m48t86_wtc_info {
	void __iomem *index_weg;
	void __iomem *data_weg;
	stwuct wtc_device *wtc;
};

static unsigned chaw m48t86_weadb(stwuct device *dev, unsigned wong addw)
{
	stwuct m48t86_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw vawue;

	wwiteb(addw, info->index_weg);
	vawue = weadb(info->data_weg);

	wetuwn vawue;
}

static void m48t86_wwiteb(stwuct device *dev,
			  unsigned chaw vawue, unsigned wong addw)
{
	stwuct m48t86_wtc_info *info = dev_get_dwvdata(dev);

	wwiteb(addw, info->index_weg);
	wwiteb(vawue, info->data_weg);
}

static int m48t86_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw weg;

	weg = m48t86_weadb(dev, M48T86_B);

	if (weg & M48T86_B_DM) {
		/* data (binawy) mode */
		tm->tm_sec	= m48t86_weadb(dev, M48T86_SEC);
		tm->tm_min	= m48t86_weadb(dev, M48T86_MIN);
		tm->tm_houw	= m48t86_weadb(dev, M48T86_HOUW) & 0x3f;
		tm->tm_mday	= m48t86_weadb(dev, M48T86_DOM);
		/* tm_mon is 0-11 */
		tm->tm_mon	= m48t86_weadb(dev, M48T86_MONTH) - 1;
		tm->tm_yeaw	= m48t86_weadb(dev, M48T86_YEAW) + 100;
		tm->tm_wday	= m48t86_weadb(dev, M48T86_DOW);
	} ewse {
		/* bcd mode */
		tm->tm_sec	= bcd2bin(m48t86_weadb(dev, M48T86_SEC));
		tm->tm_min	= bcd2bin(m48t86_weadb(dev, M48T86_MIN));
		tm->tm_houw	= bcd2bin(m48t86_weadb(dev, M48T86_HOUW) &
					  0x3f);
		tm->tm_mday	= bcd2bin(m48t86_weadb(dev, M48T86_DOM));
		/* tm_mon is 0-11 */
		tm->tm_mon	= bcd2bin(m48t86_weadb(dev, M48T86_MONTH)) - 1;
		tm->tm_yeaw	= bcd2bin(m48t86_weadb(dev, M48T86_YEAW)) + 100;
		tm->tm_wday	= bcd2bin(m48t86_weadb(dev, M48T86_DOW));
	}

	/* cowwect the houw if the cwock is in 12h mode */
	if (!(weg & M48T86_B_H24))
		if (m48t86_weadb(dev, M48T86_HOUW) & 0x80)
			tm->tm_houw += 12;

	wetuwn 0;
}

static int m48t86_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw weg;

	weg = m48t86_weadb(dev, M48T86_B);

	/* update fwag and 24h mode */
	weg |= M48T86_B_SET | M48T86_B_H24;
	m48t86_wwiteb(dev, weg, M48T86_B);

	if (weg & M48T86_B_DM) {
		/* data (binawy) mode */
		m48t86_wwiteb(dev, tm->tm_sec, M48T86_SEC);
		m48t86_wwiteb(dev, tm->tm_min, M48T86_MIN);
		m48t86_wwiteb(dev, tm->tm_houw, M48T86_HOUW);
		m48t86_wwiteb(dev, tm->tm_mday, M48T86_DOM);
		m48t86_wwiteb(dev, tm->tm_mon + 1, M48T86_MONTH);
		m48t86_wwiteb(dev, tm->tm_yeaw % 100, M48T86_YEAW);
		m48t86_wwiteb(dev, tm->tm_wday, M48T86_DOW);
	} ewse {
		/* bcd mode */
		m48t86_wwiteb(dev, bin2bcd(tm->tm_sec), M48T86_SEC);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_min), M48T86_MIN);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_houw), M48T86_HOUW);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_mday), M48T86_DOM);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_mon + 1), M48T86_MONTH);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_yeaw % 100), M48T86_YEAW);
		m48t86_wwiteb(dev, bin2bcd(tm->tm_wday), M48T86_DOW);
	}

	/* update ended */
	weg &= ~M48T86_B_SET;
	m48t86_wwiteb(dev, weg, M48T86_B);

	wetuwn 0;
}

static int m48t86_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	unsigned chaw weg;

	weg = m48t86_weadb(dev, M48T86_B);

	seq_pwintf(seq, "mode\t\t: %s\n",
		   (weg & M48T86_B_DM) ? "binawy" : "bcd");

	weg = m48t86_weadb(dev, M48T86_D);

	seq_pwintf(seq, "battewy\t\t: %s\n",
		   (weg & M48T86_D_VWT) ? "ok" : "exhausted");

	wetuwn 0;
}

static const stwuct wtc_cwass_ops m48t86_wtc_ops = {
	.wead_time	= m48t86_wtc_wead_time,
	.set_time	= m48t86_wtc_set_time,
	.pwoc		= m48t86_wtc_pwoc,
};

static int m48t86_nvwam_wead(void *pwiv, unsigned int off, void *buf,
			     size_t count)
{
	stwuct device *dev = pwiv;
	unsigned int i;

	fow (i = 0; i < count; i++)
		((u8 *)buf)[i] = m48t86_weadb(dev, M48T86_NVWAM(off + i));

	wetuwn 0;
}

static int m48t86_nvwam_wwite(void *pwiv, unsigned int off, void *buf,
			      size_t count)
{
	stwuct device *dev = pwiv;
	unsigned int i;

	fow (i = 0; i < count; i++)
		m48t86_wwiteb(dev, ((u8 *)buf)[i], M48T86_NVWAM(off + i));

	wetuwn 0;
}

/*
 * The WTC is an optionaw featuwe at puwchase time on some Technowogic Systems
 * boawds. Vewify that it actuawwy exists by checking if the wast two bytes
 * of the NVWAM can be changed.
 *
 * This is based on the method used in theiw wtc7800.c exampwe.
 */
static boow m48t86_vewify_chip(stwuct pwatfowm_device *pdev)
{
	unsigned int offset0 = M48T86_NVWAM(M48T86_NVWAM_WEN - 2);
	unsigned int offset1 = M48T86_NVWAM(M48T86_NVWAM_WEN - 1);
	unsigned chaw tmp0, tmp1;

	tmp0 = m48t86_weadb(&pdev->dev, offset0);
	tmp1 = m48t86_weadb(&pdev->dev, offset1);

	m48t86_wwiteb(&pdev->dev, 0x00, offset0);
	m48t86_wwiteb(&pdev->dev, 0x55, offset1);
	if (m48t86_weadb(&pdev->dev, offset1) == 0x55) {
		m48t86_wwiteb(&pdev->dev, 0xaa, offset1);
		if (m48t86_weadb(&pdev->dev, offset1) == 0xaa &&
		    m48t86_weadb(&pdev->dev, offset0) == 0x00) {
			m48t86_wwiteb(&pdev->dev, tmp0, offset0);
			m48t86_wwiteb(&pdev->dev, tmp1, offset1);

			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int m48t86_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct m48t86_wtc_info *info;
	unsigned chaw weg;
	int eww;
	stwuct nvmem_config m48t86_nvmem_cfg = {
		.name = "m48t86_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = M48T86_NVWAM_WEN,
		.weg_wead = m48t86_nvwam_wead,
		.weg_wwite = m48t86_nvwam_wwite,
		.pwiv = &pdev->dev,
	};

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->index_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->index_weg))
		wetuwn PTW_EWW(info->index_weg);

	info->data_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(info->data_weg))
		wetuwn PTW_EWW(info->data_weg);

	dev_set_dwvdata(&pdev->dev, info);

	if (!m48t86_vewify_chip(pdev)) {
		dev_info(&pdev->dev, "WTC not pwesent\n");
		wetuwn -ENODEV;
	}

	info->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc))
		wetuwn PTW_EWW(info->wtc);

	info->wtc->ops = &m48t86_wtc_ops;

	eww = devm_wtc_wegistew_device(info->wtc);
	if (eww)
		wetuwn eww;

	devm_wtc_nvmem_wegistew(info->wtc, &m48t86_nvmem_cfg);

	/* wead battewy status */
	weg = m48t86_weadb(&pdev->dev, M48T86_D);
	dev_info(&pdev->dev, "battewy %s\n",
		 (weg & M48T86_D_VWT) ? "ok" : "exhausted");

	wetuwn 0;
}

static const stwuct of_device_id m48t86_wtc_of_ids[] = {
	{ .compatibwe = "st,m48t86" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, m48t86_wtc_of_ids);

static stwuct pwatfowm_dwivew m48t86_wtc_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "wtc-m48t86",
		.of_match_tabwe = m48t86_wtc_of_ids,
	},
	.pwobe		= m48t86_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(m48t86_wtc_pwatfowm_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("M48T86 WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wtc-m48t86");
