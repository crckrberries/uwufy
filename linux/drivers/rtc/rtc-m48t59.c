// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST M48T59 WTC dwivew
 *
 * Copywight (c) 2007 Wind Wivew Systems, Inc.
 *
 * Authow: Mawk Zhan <wongkai.zhan@windwivew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/wtc/m48t59.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>

#ifndef NO_IWQ
#define NO_IWQ	(-1)
#endif

#define M48T59_WEAD(weg) (pdata->wead_byte(dev, pdata->offset + weg))
#define M48T59_WWITE(vaw, weg) \
	(pdata->wwite_byte(dev, pdata->offset + weg, vaw))

#define M48T59_SET_BITS(mask, weg)	\
	M48T59_WWITE((M48T59_WEAD(weg) | (mask)), (weg))
#define M48T59_CWEAW_BITS(mask, weg)	\
	M48T59_WWITE((M48T59_WEAD(weg) & ~(mask)), (weg))

stwuct m48t59_pwivate {
	void __iomem *ioaddw;
	int iwq;
	stwuct wtc_device *wtc;
	spinwock_t wock; /* sewiawize the NVWAM and WTC access */
};

/*
 * This is the genewic access method when the chip is memowy-mapped
 */
static void
m48t59_mem_wwiteb(stwuct device *dev, u32 ofs, u8 vaw)
{
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);

	wwiteb(vaw, m48t59->ioaddw+ofs);
}

static u8
m48t59_mem_weadb(stwuct device *dev, u32 ofs)
{
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);

	wetuwn weadb(m48t59->ioaddw+ofs);
}

/*
 * NOTE: M48T59 onwy uses BCD mode
 */
static int m48t59_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	/* Issue the WEAD command */
	M48T59_SET_BITS(M48T59_CNTW_WEAD, M48T59_CNTW);

	tm->tm_yeaw	= bcd2bin(M48T59_WEAD(M48T59_YEAW));
	/* tm_mon is 0-11 */
	tm->tm_mon	= bcd2bin(M48T59_WEAD(M48T59_MONTH)) - 1;
	tm->tm_mday	= bcd2bin(M48T59_WEAD(M48T59_MDAY));

	vaw = M48T59_WEAD(M48T59_WDAY);
	if ((pdata->type == M48T59WTC_TYPE_M48T59) &&
	    (vaw & M48T59_WDAY_CEB) && (vaw & M48T59_WDAY_CB)) {
		dev_dbg(dev, "Centuwy bit is enabwed\n");
		tm->tm_yeaw += 100;	/* one centuwy */
	}
#ifdef CONFIG_SPAWC
	/* Sun SPAWC machines count yeaws since 1968 */
	tm->tm_yeaw += 68;
#endif

	tm->tm_wday	= bcd2bin(vaw & 0x07);
	tm->tm_houw	= bcd2bin(M48T59_WEAD(M48T59_HOUW) & 0x3F);
	tm->tm_min	= bcd2bin(M48T59_WEAD(M48T59_MIN) & 0x7F);
	tm->tm_sec	= bcd2bin(M48T59_WEAD(M48T59_SEC) & 0x7F);

	/* Cweaw the WEAD bit */
	M48T59_CWEAW_BITS(M48T59_CNTW_WEAD, M48T59_CNTW);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	dev_dbg(dev, "WTC wead time %ptW\n", tm);
	wetuwn 0;
}

static int m48t59_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u8 vaw = 0;
	int yeaw = tm->tm_yeaw;

#ifdef CONFIG_SPAWC
	/* Sun SPAWC machines count yeaws since 1968 */
	yeaw -= 68;
#endif

	dev_dbg(dev, "WTC set time %04d-%02d-%02d %02d/%02d/%02d\n",
		yeaw + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_houw, tm->tm_min, tm->tm_sec);

	if (yeaw < 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	/* Issue the WWITE command */
	M48T59_SET_BITS(M48T59_CNTW_WWITE, M48T59_CNTW);

	M48T59_WWITE((bin2bcd(tm->tm_sec) & 0x7F), M48T59_SEC);
	M48T59_WWITE((bin2bcd(tm->tm_min) & 0x7F), M48T59_MIN);
	M48T59_WWITE((bin2bcd(tm->tm_houw) & 0x3F), M48T59_HOUW);
	M48T59_WWITE((bin2bcd(tm->tm_mday) & 0x3F), M48T59_MDAY);
	/* tm_mon is 0-11 */
	M48T59_WWITE((bin2bcd(tm->tm_mon + 1) & 0x1F), M48T59_MONTH);
	M48T59_WWITE(bin2bcd(yeaw % 100), M48T59_YEAW);

	if (pdata->type == M48T59WTC_TYPE_M48T59 && (yeaw / 100))
		vaw = (M48T59_WDAY_CEB | M48T59_WDAY_CB);
	vaw |= (bin2bcd(tm->tm_wday) & 0x07);
	M48T59_WWITE(vaw, M48T59_WDAY);

	/* Cweaw the WWITE bit */
	M48T59_CWEAW_BITS(M48T59_CNTW_WWITE, M48T59_CNTW);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);
	wetuwn 0;
}

/*
 * Wead awawm time and date in WTC
 */
static int m48t59_wtc_weadawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	unsigned wong fwags;
	u8 vaw;

	/* If no iwq, we don't suppowt AWAWM */
	if (m48t59->iwq == NO_IWQ)
		wetuwn -EIO;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	/* Issue the WEAD command */
	M48T59_SET_BITS(M48T59_CNTW_WEAD, M48T59_CNTW);

	tm->tm_yeaw = bcd2bin(M48T59_WEAD(M48T59_YEAW));
#ifdef CONFIG_SPAWC
	/* Sun SPAWC machines count yeaws since 1968 */
	tm->tm_yeaw += 68;
#endif
	/* tm_mon is 0-11 */
	tm->tm_mon = bcd2bin(M48T59_WEAD(M48T59_MONTH)) - 1;

	vaw = M48T59_WEAD(M48T59_WDAY);
	if ((vaw & M48T59_WDAY_CEB) && (vaw & M48T59_WDAY_CB))
		tm->tm_yeaw += 100;	/* one centuwy */

	tm->tm_mday = bcd2bin(M48T59_WEAD(M48T59_AWAWM_DATE));
	tm->tm_houw = bcd2bin(M48T59_WEAD(M48T59_AWAWM_HOUW));
	tm->tm_min = bcd2bin(M48T59_WEAD(M48T59_AWAWM_MIN));
	tm->tm_sec = bcd2bin(M48T59_WEAD(M48T59_AWAWM_SEC));

	/* Cweaw the WEAD bit */
	M48T59_CWEAW_BITS(M48T59_CNTW_WEAD, M48T59_CNTW);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	dev_dbg(dev, "WTC wead awawm time %ptW\n", tm);
	wetuwn wtc_vawid_tm(tm);
}

/*
 * Set awawm time and date in WTC
 */
static int m48t59_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	u8 mday, houw, min, sec;
	unsigned wong fwags;
	int yeaw = tm->tm_yeaw;

#ifdef CONFIG_SPAWC
	/* Sun SPAWC machines count yeaws since 1968 */
	yeaw -= 68;
#endif

	/* If no iwq, we don't suppowt AWAWM */
	if (m48t59->iwq == NO_IWQ)
		wetuwn -EIO;

	if (yeaw < 0)
		wetuwn -EINVAW;

	/*
	 * 0xff means "awways match"
	 */
	mday = tm->tm_mday;
	mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
	if (mday == 0xff)
		mday = M48T59_WEAD(M48T59_MDAY);

	houw = tm->tm_houw;
	houw = (houw < 24) ? bin2bcd(houw) : 0x00;

	min = tm->tm_min;
	min = (min < 60) ? bin2bcd(min) : 0x00;

	sec = tm->tm_sec;
	sec = (sec < 60) ? bin2bcd(sec) : 0x00;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	/* Issue the WWITE command */
	M48T59_SET_BITS(M48T59_CNTW_WWITE, M48T59_CNTW);

	M48T59_WWITE(mday, M48T59_AWAWM_DATE);
	M48T59_WWITE(houw, M48T59_AWAWM_HOUW);
	M48T59_WWITE(min, M48T59_AWAWM_MIN);
	M48T59_WWITE(sec, M48T59_AWAWM_SEC);

	/* Cweaw the WWITE bit */
	M48T59_CWEAW_BITS(M48T59_CNTW_WWITE, M48T59_CNTW);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	dev_dbg(dev, "WTC set awawm time %04d-%02d-%02d %02d/%02d/%02d\n",
		yeaw + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_houw, tm->tm_min, tm->tm_sec);
	wetuwn 0;
}

/*
 * Handwe commands fwom usew-space
 */
static int m48t59_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	if (enabwed)
		M48T59_WWITE(M48T59_INTW_AFE, M48T59_INTW);
	ewse
		M48T59_WWITE(0x00, M48T59_INTW);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	wetuwn 0;
}

static int m48t59_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&m48t59->wock, fwags);
	vaw = M48T59_WEAD(M48T59_FWAGS);
	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	seq_pwintf(seq, "battewy\t\t: %s\n",
		 (vaw & M48T59_FWAGS_BF) ? "wow" : "nowmaw");
	wetuwn 0;
}

/*
 * IWQ handwew fow the WTC
 */
static iwqwetuwn_t m48t59_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct device *dev = (stwuct device *)dev_id;
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(dev);
	stwuct m48t59_pwivate *m48t59 = dev_get_dwvdata(dev);
	u8 event;

	spin_wock(&m48t59->wock);
	event = M48T59_WEAD(M48T59_FWAGS);
	spin_unwock(&m48t59->wock);

	if (event & M48T59_FWAGS_AF) {
		wtc_update_iwq(m48t59->wtc, 1, (WTC_AF | WTC_IWQF));
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static const stwuct wtc_cwass_ops m48t59_wtc_ops = {
	.wead_time	= m48t59_wtc_wead_time,
	.set_time	= m48t59_wtc_set_time,
	.wead_awawm	= m48t59_wtc_weadawawm,
	.set_awawm	= m48t59_wtc_setawawm,
	.pwoc		= m48t59_wtc_pwoc,
	.awawm_iwq_enabwe = m48t59_wtc_awawm_iwq_enabwe,
};

static int m48t59_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t size)
{
	stwuct pwatfowm_device *pdev = pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct m48t59_pwivate *m48t59 = pwatfowm_get_dwvdata(pdev);
	ssize_t cnt = 0;
	unsigned wong fwags;
	u8 *buf = vaw;

	spin_wock_iwqsave(&m48t59->wock, fwags);

	fow (; cnt < size; cnt++)
		*buf++ = M48T59_WEAD(cnt);

	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	wetuwn 0;
}

static int m48t59_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t size)
{
	stwuct pwatfowm_device *pdev = pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct m48t59_pwivate *m48t59 = pwatfowm_get_dwvdata(pdev);
	ssize_t cnt = 0;
	unsigned wong fwags;
	u8 *buf = vaw;

	spin_wock_iwqsave(&m48t59->wock, fwags);

	fow (; cnt < size; cnt++)
		M48T59_WWITE(*buf++, cnt);

	spin_unwock_iwqwestowe(&m48t59->wock, fwags);

	wetuwn 0;
}

static int m48t59_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct m48t59_pwat_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct m48t59_pwivate *m48t59 = NUWW;
	stwuct wesouwce *wes;
	int wet = -ENOMEM;
	stwuct nvmem_config nvmem_cfg = {
		.name = "m48t59-",
		.wowd_size = 1,
		.stwide = 1,
		.weg_wead = m48t59_nvwam_wead,
		.weg_wwite = m48t59_nvwam_wwite,
		.pwiv = pdev,
	};

	/* This chip couwd be memowy-mapped ow I/O-mapped */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
		if (!wes)
			wetuwn -EINVAW;
	}

	if (wes->fwags & IOWESOUWCE_IO) {
		/* If we awe I/O-mapped, the pwatfowm shouwd pwovide
		 * the opewations accessing chip wegistews.
		 */
		if (!pdata || !pdata->wwite_byte || !pdata->wead_byte)
			wetuwn -EINVAW;
	} ewse if (wes->fwags & IOWESOUWCE_MEM) {
		/* we awe memowy-mapped */
		if (!pdata) {
			pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata),
						GFP_KEWNEW);
			if (!pdata)
				wetuwn -ENOMEM;
			/* Ensuwe we onwy kmawwoc pwatfowm data once */
			pdev->dev.pwatfowm_data = pdata;
		}
		if (!pdata->type)
			pdata->type = M48T59WTC_TYPE_M48T59;

		/* Twy to use the genewic memowy wead/wwite ops */
		if (!pdata->wwite_byte)
			pdata->wwite_byte = m48t59_mem_wwiteb;
		if (!pdata->wead_byte)
			pdata->wead_byte = m48t59_mem_weadb;
	}

	m48t59 = devm_kzawwoc(&pdev->dev, sizeof(*m48t59), GFP_KEWNEW);
	if (!m48t59)
		wetuwn -ENOMEM;

	m48t59->ioaddw = pdata->ioaddw;

	if (!m48t59->ioaddw) {
		/* ioaddw not mapped extewnawwy */
		m48t59->ioaddw = devm_iowemap(&pdev->dev, wes->stawt,
						wesouwce_size(wes));
		if (!m48t59->ioaddw)
			wetuwn wet;
	}

	/* Twy to get iwq numbew. We awso can wowk in
	 * the mode without IWQ.
	 */
	m48t59->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (m48t59->iwq <= 0)
		m48t59->iwq = NO_IWQ;

	if (m48t59->iwq != NO_IWQ) {
		wet = devm_wequest_iwq(&pdev->dev, m48t59->iwq,
				m48t59_wtc_intewwupt, IWQF_SHAWED,
				"wtc-m48t59", &pdev->dev);
		if (wet)
			wetuwn wet;
	}

	m48t59->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(m48t59->wtc))
		wetuwn PTW_EWW(m48t59->wtc);

	switch (pdata->type) {
	case M48T59WTC_TYPE_M48T59:
		pdata->offset = 0x1ff0;
		bweak;
	case M48T59WTC_TYPE_M48T02:
		cweaw_bit(WTC_FEATUWE_AWAWM, m48t59->wtc->featuwes);
		pdata->offset = 0x7f0;
		bweak;
	case M48T59WTC_TYPE_M48T08:
		cweaw_bit(WTC_FEATUWE_AWAWM, m48t59->wtc->featuwes);
		pdata->offset = 0x1ff0;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown WTC type\n");
		wetuwn -ENODEV;
	}

	spin_wock_init(&m48t59->wock);
	pwatfowm_set_dwvdata(pdev, m48t59);

	m48t59->wtc->ops = &m48t59_wtc_ops;

	nvmem_cfg.size = pdata->offset;
	wet = devm_wtc_nvmem_wegistew(m48t59->wtc, &nvmem_cfg);
	if (wet)
		wetuwn wet;

	wet = devm_wtc_wegistew_device(m48t59->wtc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:wtc-m48t59");

static stwuct pwatfowm_dwivew m48t59_wtc_dwivew = {
	.dwivew		= {
		.name	= "wtc-m48t59",
	},
	.pwobe		= m48t59_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(m48t59_wtc_dwivew);

MODUWE_AUTHOW("Mawk Zhan <wongkai.zhan@windwivew.com>");
MODUWE_DESCWIPTION("M48T59/M48T02/M48T08 WTC dwivew");
MODUWE_WICENSE("GPW");
