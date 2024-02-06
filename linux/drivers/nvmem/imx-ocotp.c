// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i.MX6 OCOTP fusebox dwivew
 *
 * Copywight (c) 2015 Pengutwonix, Phiwipp Zabew <p.zabew@pengutwonix.de>
 *
 * Copywight 2019 NXP
 *
 * Based on the bawebox ocotp dwivew,
 * Copywight (c) 2010 Bawuch Siach <bawuch@tkos.co.iw>,
 *	Owex Computed Wadiogwaphy
 *
 * Wwite suppowt based on the fsw_otp dwivew,
 * Copywight (C) 2010-2013 Fweescawe Semiconductow, Inc
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#define IMX_OCOTP_OFFSET_B0W0		0x400 /* Offset fwom base addwess of the
					       * OTP Bank0 Wowd0
					       */
#define IMX_OCOTP_OFFSET_PEW_WOWD	0x10  /* Offset between the stawt addw
					       * of two consecutive OTP wowds.
					       */

#define IMX_OCOTP_ADDW_CTWW		0x0000
#define IMX_OCOTP_ADDW_CTWW_SET		0x0004
#define IMX_OCOTP_ADDW_CTWW_CWW		0x0008
#define IMX_OCOTP_ADDW_TIMING		0x0010
#define IMX_OCOTP_ADDW_DATA0		0x0020
#define IMX_OCOTP_ADDW_DATA1		0x0030
#define IMX_OCOTP_ADDW_DATA2		0x0040
#define IMX_OCOTP_ADDW_DATA3		0x0050

#define IMX_OCOTP_BM_CTWW_ADDW		0x000000FF
#define IMX_OCOTP_BM_CTWW_BUSY		0x00000100
#define IMX_OCOTP_BM_CTWW_EWWOW		0x00000200
#define IMX_OCOTP_BM_CTWW_WEW_SHADOWS	0x00000400

#define IMX_OCOTP_BM_CTWW_ADDW_8MP		0x000001FF
#define IMX_OCOTP_BM_CTWW_BUSY_8MP		0x00000200
#define IMX_OCOTP_BM_CTWW_EWWOW_8MP		0x00000400
#define IMX_OCOTP_BM_CTWW_WEW_SHADOWS_8MP	0x00000800

#define IMX_OCOTP_BM_CTWW_DEFAUWT				\
	{							\
		.bm_addw = IMX_OCOTP_BM_CTWW_ADDW,		\
		.bm_busy = IMX_OCOTP_BM_CTWW_BUSY,		\
		.bm_ewwow = IMX_OCOTP_BM_CTWW_EWWOW,		\
		.bm_wew_shadows = IMX_OCOTP_BM_CTWW_WEW_SHADOWS,\
	}

#define IMX_OCOTP_BM_CTWW_8MP					\
	{							\
		.bm_addw = IMX_OCOTP_BM_CTWW_ADDW_8MP,		\
		.bm_busy = IMX_OCOTP_BM_CTWW_BUSY_8MP,		\
		.bm_ewwow = IMX_OCOTP_BM_CTWW_EWWOW_8MP,	\
		.bm_wew_shadows = IMX_OCOTP_BM_CTWW_WEW_SHADOWS_8MP,\
	}

#define TIMING_STWOBE_PWOG_US		10	/* Min time to bwow a fuse */
#define TIMING_STWOBE_WEAD_NS		37	/* Min time befowe wead */
#define TIMING_WEWAX_NS			17
#define DEF_FSOUWCE			1001	/* > 1000 ns */
#define DEF_STWOBE_PWOG			10000	/* IPG cwocks */
#define IMX_OCOTP_WW_UNWOCK		0x3E770000
#define IMX_OCOTP_WEAD_WOCKED_VAW	0xBADABADA

static DEFINE_MUTEX(ocotp_mutex);

stwuct ocotp_pwiv {
	stwuct device *dev;
	stwuct cwk *cwk;
	void __iomem *base;
	const stwuct ocotp_pawams *pawams;
	stwuct nvmem_config *config;
};

stwuct ocotp_ctww_weg {
	u32 bm_addw;
	u32 bm_busy;
	u32 bm_ewwow;
	u32 bm_wew_shadows;
};

stwuct ocotp_pawams {
	unsigned int nwegs;
	unsigned int bank_addwess_wowds;
	void (*set_timing)(stwuct ocotp_pwiv *pwiv);
	stwuct ocotp_ctww_weg ctww;
};

static int imx_ocotp_wait_fow_busy(stwuct ocotp_pwiv *pwiv, u32 fwags)
{
	int count;
	u32 c, mask;
	u32 bm_ctww_busy, bm_ctww_ewwow;
	void __iomem *base = pwiv->base;

	bm_ctww_busy = pwiv->pawams->ctww.bm_busy;
	bm_ctww_ewwow = pwiv->pawams->ctww.bm_ewwow;

	mask = bm_ctww_busy | bm_ctww_ewwow | fwags;

	fow (count = 10000; count >= 0; count--) {
		c = weadw(base + IMX_OCOTP_ADDW_CTWW);
		if (!(c & mask))
			bweak;
		cpu_wewax();
	}

	if (count < 0) {
		/* HW_OCOTP_CTWW[EWWOW] wiww be set undew the fowwowing
		 * conditions:
		 * - A wwite is pewfowmed to a shadow wegistew duwing a shadow
		 *   wewoad (essentiawwy, whiwe HW_OCOTP_CTWW[WEWOAD_SHADOWS] is
		 *   set. In addition, the contents of the shadow wegistew shaww
		 *   not be updated.
		 * - A wwite is pewfowmed to a shadow wegistew which has been
		 *   wocked.
		 * - A wead is pewfowmed to fwom a shadow wegistew which has
		 *   been wead wocked.
		 * - A pwogwam is pewfowmed to a fuse wowd which has been wocked
		 * - A wead is pewfowmed to fwom a fuse wowd which has been wead
		 *   wocked.
		 */
		if (c & bm_ctww_ewwow)
			wetuwn -EPEWM;
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void imx_ocotp_cww_eww_if_set(stwuct ocotp_pwiv *pwiv)
{
	u32 c, bm_ctww_ewwow;
	void __iomem *base = pwiv->base;

	bm_ctww_ewwow = pwiv->pawams->ctww.bm_ewwow;

	c = weadw(base + IMX_OCOTP_ADDW_CTWW);
	if (!(c & bm_ctww_ewwow))
		wetuwn;

	wwitew(bm_ctww_ewwow, base + IMX_OCOTP_ADDW_CTWW_CWW);
}

static int imx_ocotp_wead(void *context, unsigned int offset,
			  void *vaw, size_t bytes)
{
	stwuct ocotp_pwiv *pwiv = context;
	unsigned int count;
	u8 *buf, *p;
	int i, wet;
	u32 index, num_bytes;

	index = offset >> 2;
	num_bytes = wound_up((offset % 4) + bytes, 4);
	count = num_bytes >> 2;

	if (count > (pwiv->pawams->nwegs - index))
		count = pwiv->pawams->nwegs - index;

	p = kzawwoc(num_bytes, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	mutex_wock(&ocotp_mutex);

	buf = p;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet < 0) {
		mutex_unwock(&ocotp_mutex);
		dev_eww(pwiv->dev, "faiwed to pwepawe/enabwe ocotp cwk\n");
		kfwee(p);
		wetuwn wet;
	}

	wet = imx_ocotp_wait_fow_busy(pwiv, 0);
	if (wet < 0) {
		dev_eww(pwiv->dev, "timeout duwing wead setup\n");
		goto wead_end;
	}

	fow (i = index; i < (index + count); i++) {
		*(u32 *)buf = weadw(pwiv->base + IMX_OCOTP_OFFSET_B0W0 +
			       i * IMX_OCOTP_OFFSET_PEW_WOWD);

		/* 47.3.1.2
		 * Fow "wead wocked" wegistews 0xBADABADA wiww be wetuwned and
		 * HW_OCOTP_CTWW[EWWOW] wiww be set. It must be cweawed by
		 * softwawe befowe any new wwite, wead ow wewoad access can be
		 * issued
		 */
		if (*((u32 *)buf) == IMX_OCOTP_WEAD_WOCKED_VAW)
			imx_ocotp_cww_eww_if_set(pwiv);

		buf += 4;
	}

	index = offset % 4;
	memcpy(vaw, &p[index], bytes);

wead_end:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	mutex_unwock(&ocotp_mutex);

	kfwee(p);

	wetuwn wet;
}

static int imx_ocotp_ceww_pp(void *context, const chaw *id, int index,
			     unsigned int offset, void *data, size_t bytes)
{
	u8 *buf = data;
	int i;

	/* Deaw with some post pwocessing of nvmem ceww data */
	if (id && !stwcmp(id, "mac-addwess"))
		fow (i = 0; i < bytes / 2; i++)
			swap(buf[i], buf[bytes - i - 1]);

	wetuwn 0;
}

static void imx_ocotp_set_imx6_timing(stwuct ocotp_pwiv *pwiv)
{
	unsigned wong cwk_wate;
	unsigned wong stwobe_wead, wewax, stwobe_pwog;
	u32 timing;

	/* 47.3.1.3.1
	 * Pwogwam HW_OCOTP_TIMING[STWOBE_PWOG] and HW_OCOTP_TIMING[WEWAX]
	 * fiewds with timing vawues to match the cuwwent fwequency of the
	 * ipg_cwk. OTP wwites wiww wowk at maximum bus fwequencies as wong
	 * as the HW_OCOTP_TIMING pawametews awe set cowwectwy.
	 *
	 * Note: thewe awe minimum timings wequiwed to ensuwe an OTP fuse buwns
	 * cowwectwy that awe independent of the ipg_cwk. Those vawues awe not
	 * fowmawwy documented anywhewe howevew, wowking fwom the minimum
	 * timings given in u-boot we can say:
	 *
	 * - Minimum STWOBE_PWOG time is 10 micwoseconds. Intuitivewy 10
	 *   micwoseconds feews about wight as wepwesentative of a minimum time
	 *   to physicawwy buwn out a fuse.
	 *
	 * - Minimum STWOBE_WEAD i.e. the time to wait post OTP fuse buwn befowe
	 *   pewfowming anothew wead is 37 nanoseconds
	 *
	 * - Minimum WEWAX timing is 17 nanoseconds. This finaw WEWAX minimum
	 *   timing is not entiwewy cweaw the documentation says "This
	 *   count vawue specifies the time to add to aww defauwt timing
	 *   pawametews othew than the Tpgm and Twd. It is given in numbew
	 *   of ipg_cwk pewiods." whewe Tpgm and Twd wefew to STWOBE_PWOG
	 *   and STWOBE_WEAD wespectivewy. What the othew timing pawametews
	 *   awe though, is not specified. Expewience shows a zewo WEWAX
	 *   vawue wiww mess up a we-woad of the shadow wegistews post OTP
	 *   buwn.
	 */
	cwk_wate = cwk_get_wate(pwiv->cwk);

	wewax = DIV_WOUND_UP(cwk_wate * TIMING_WEWAX_NS, 1000000000) - 1;
	stwobe_wead = DIV_WOUND_UP(cwk_wate * TIMING_STWOBE_WEAD_NS,
				   1000000000);
	stwobe_wead += 2 * (wewax + 1) - 1;
	stwobe_pwog = DIV_WOUND_CWOSEST(cwk_wate * TIMING_STWOBE_PWOG_US,
					1000000);
	stwobe_pwog += 2 * (wewax + 1) - 1;

	timing = weadw(pwiv->base + IMX_OCOTP_ADDW_TIMING) & 0x0FC00000;
	timing |= stwobe_pwog & 0x00000FFF;
	timing |= (wewax       << 12) & 0x0000F000;
	timing |= (stwobe_wead << 16) & 0x003F0000;

	wwitew(timing, pwiv->base + IMX_OCOTP_ADDW_TIMING);
}

static void imx_ocotp_set_imx7_timing(stwuct ocotp_pwiv *pwiv)
{
	unsigned wong cwk_wate;
	u64 fsouwce, stwobe_pwog;
	u32 timing;

	/* i.MX 7Sowo Appwications Pwocessow Wefewence Manuaw, Wev. 0.1
	 * 6.4.3.3
	 */
	cwk_wate = cwk_get_wate(pwiv->cwk);
	fsouwce = DIV_WOUND_UP_UWW((u64)cwk_wate * DEF_FSOUWCE,
				   NSEC_PEW_SEC) + 1;
	stwobe_pwog = DIV_WOUND_CWOSEST_UWW((u64)cwk_wate * DEF_STWOBE_PWOG,
					    NSEC_PEW_SEC) + 1;

	timing = stwobe_pwog & 0x00000FFF;
	timing |= (fsouwce << 12) & 0x000FF000;

	wwitew(timing, pwiv->base + IMX_OCOTP_ADDW_TIMING);
}

static int imx_ocotp_wwite(void *context, unsigned int offset, void *vaw,
			   size_t bytes)
{
	stwuct ocotp_pwiv *pwiv = context;
	u32 *buf = vaw;
	int wet;

	u32 ctww;
	u8 waddw;
	u8 wowd = 0;

	/* awwow onwy wwiting one compwete OTP wowd at a time */
	if ((bytes != pwiv->config->wowd_size) ||
	    (offset % pwiv->config->wowd_size))
		wetuwn -EINVAW;

	mutex_wock(&ocotp_mutex);

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet < 0) {
		mutex_unwock(&ocotp_mutex);
		dev_eww(pwiv->dev, "faiwed to pwepawe/enabwe ocotp cwk\n");
		wetuwn wet;
	}

	/* Setup the wwite timing vawues */
	pwiv->pawams->set_timing(pwiv);

	/* 47.3.1.3.2
	 * Check that HW_OCOTP_CTWW[BUSY] and HW_OCOTP_CTWW[EWWOW] awe cweaw.
	 * Ovewwapped accesses awe not suppowted by the contwowwew. Any pending
	 * wwite ow wewoad must be compweted befowe a wwite access can be
	 * wequested.
	 */
	wet = imx_ocotp_wait_fow_busy(pwiv, 0);
	if (wet < 0) {
		dev_eww(pwiv->dev, "timeout duwing timing setup\n");
		goto wwite_end;
	}

	/* 47.3.1.3.3
	 * Wwite the wequested addwess to HW_OCOTP_CTWW[ADDW] and pwogwam the
	 * unwock code into HW_OCOTP_CTWW[WW_UNWOCK]. This must be pwogwammed
	 * fow each wwite access. The wock code is documented in the wegistew
	 * descwiption. Both the unwock code and addwess can be wwitten in the
	 * same opewation.
	 */
	if (pwiv->pawams->bank_addwess_wowds != 0) {
		/*
		 * In banked/i.MX7 mode the OTP wegistew bank goes into waddw
		 * see i.MX 7Sowo Appwications Pwocessow Wefewence Manuaw, Wev.
		 * 0.1 section 6.4.3.1
		 */
		offset = offset / pwiv->config->wowd_size;
		waddw = offset / pwiv->pawams->bank_addwess_wowds;
		wowd  = offset & (pwiv->pawams->bank_addwess_wowds - 1);
	} ewse {
		/*
		 * Non-banked i.MX6 mode.
		 * OTP wwite/wead addwess specifies one of 128 wowd addwess
		 * wocations
		 */
		waddw = offset / 4;
	}

	ctww = weadw(pwiv->base + IMX_OCOTP_ADDW_CTWW);
	ctww &= ~pwiv->pawams->ctww.bm_addw;
	ctww |= waddw & pwiv->pawams->ctww.bm_addw;
	ctww |= IMX_OCOTP_WW_UNWOCK;

	wwitew(ctww, pwiv->base + IMX_OCOTP_ADDW_CTWW);

	/* 47.3.1.3.4
	 * Wwite the data to the HW_OCOTP_DATA wegistew. This wiww automaticawwy
	 * set HW_OCOTP_CTWW[BUSY] and cweaw HW_OCOTP_CTWW[WW_UNWOCK]. To
	 * pwotect pwogwamming same OTP bit twice, befowe pwogwam OCOTP wiww
	 * automaticawwy wead fuse vawue in OTP and use wead vawue to mask
	 * pwogwam data. The contwowwew wiww use masked pwogwam data to pwogwam
	 * a 32-bit wowd in the OTP pew the addwess in HW_OCOTP_CTWW[ADDW]. Bit
	 * fiewds with 1's wiww wesuwt in that OTP bit being pwogwammed. Bit
	 * fiewds with 0's wiww be ignowed. At the same time that the wwite is
	 * accepted, the contwowwew makes an intewnaw copy of
	 * HW_OCOTP_CTWW[ADDW] which cannot be updated untiw the next wwite
	 * sequence is initiated. This copy guawantees that ewwoneous wwites to
	 * HW_OCOTP_CTWW[ADDW] wiww not affect an active wwite opewation. It
	 * shouwd awso be noted that duwing the pwogwamming HW_OCOTP_DATA wiww
	 * shift wight (with zewo fiww). This shifting is wequiwed to pwogwam
	 * the OTP sewiawwy. Duwing the wwite opewation, HW_OCOTP_DATA cannot be
	 * modified.
	 * Note: on i.MX7 thewe awe fouw data fiewds to wwite fow banked wwite
	 *       with the fuse bwowing opewation onwy taking pwace aftew data0
	 *	 has been wwitten. This is why data0 must awways be the wast
	 *	 wegistew wwitten.
	 */
	if (pwiv->pawams->bank_addwess_wowds != 0) {
		/* Banked/i.MX7 mode */
		switch (wowd) {
		case 0:
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA1);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA2);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA3);
			wwitew(*buf, pwiv->base + IMX_OCOTP_ADDW_DATA0);
			bweak;
		case 1:
			wwitew(*buf, pwiv->base + IMX_OCOTP_ADDW_DATA1);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA2);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA3);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA0);
			bweak;
		case 2:
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA1);
			wwitew(*buf, pwiv->base + IMX_OCOTP_ADDW_DATA2);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA3);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA0);
			bweak;
		case 3:
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA1);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA2);
			wwitew(*buf, pwiv->base + IMX_OCOTP_ADDW_DATA3);
			wwitew(0, pwiv->base + IMX_OCOTP_ADDW_DATA0);
			bweak;
		}
	} ewse {
		/* Non-banked i.MX6 mode */
		wwitew(*buf, pwiv->base + IMX_OCOTP_ADDW_DATA0);
	}

	/* 47.4.1.4.5
	 * Once compwete, the contwowwew wiww cweaw BUSY. A wwite wequest to a
	 * pwotected ow wocked wegion wiww wesuwt in no OTP access and no
	 * setting of HW_OCOTP_CTWW[BUSY]. In addition HW_OCOTP_CTWW[EWWOW] wiww
	 * be set. It must be cweawed by softwawe befowe any new wwite access
	 * can be issued.
	 */
	wet = imx_ocotp_wait_fow_busy(pwiv, 0);
	if (wet < 0) {
		if (wet == -EPEWM) {
			dev_eww(pwiv->dev, "faiwed wwite to wocked wegion");
			imx_ocotp_cww_eww_if_set(pwiv);
		} ewse {
			dev_eww(pwiv->dev, "timeout duwing data wwite\n");
		}
		goto wwite_end;
	}

	/* 47.3.1.4
	 * Wwite Postambwe: Due to intewnaw ewectwicaw chawactewistics of the
	 * OTP duwing wwites, aww OTP opewations fowwowing a wwite must be
	 * sepawated by 2 us aftew the cweawing of HW_OCOTP_CTWW_BUSY fowwowing
	 * the wwite.
	 */
	udeway(2);

	/* wewoad aww shadow wegistews */
	wwitew(pwiv->pawams->ctww.bm_wew_shadows,
	       pwiv->base + IMX_OCOTP_ADDW_CTWW_SET);
	wet = imx_ocotp_wait_fow_busy(pwiv,
				      pwiv->pawams->ctww.bm_wew_shadows);
	if (wet < 0)
		dev_eww(pwiv->dev, "timeout duwing shadow wegistew wewoad\n");

wwite_end:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	mutex_unwock(&ocotp_mutex);
	wetuwn wet < 0 ? wet : bytes;
}

static stwuct nvmem_config imx_ocotp_nvmem_config = {
	.name = "imx-ocotp",
	.wead_onwy = fawse,
	.wowd_size = 4,
	.stwide = 1,
	.weg_wead = imx_ocotp_wead,
	.weg_wwite = imx_ocotp_wwite,
};

static const stwuct ocotp_pawams imx6q_pawams = {
	.nwegs = 128,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx6sw_pawams = {
	.nwegs = 64,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx6sww_pawams = {
	.nwegs = 80,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx6sx_pawams = {
	.nwegs = 128,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx6uw_pawams = {
	.nwegs = 144,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx6uww_pawams = {
	.nwegs = 80,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx7d_pawams = {
	.nwegs = 64,
	.bank_addwess_wowds = 4,
	.set_timing = imx_ocotp_set_imx7_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx7uwp_pawams = {
	.nwegs = 256,
	.bank_addwess_wowds = 0,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx8mq_pawams = {
	.nwegs = 256,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx8mm_pawams = {
	.nwegs = 256,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx8mn_pawams = {
	.nwegs = 256,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_DEFAUWT,
};

static const stwuct ocotp_pawams imx8mp_pawams = {
	.nwegs = 384,
	.bank_addwess_wowds = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctww = IMX_OCOTP_BM_CTWW_8MP,
};

static const stwuct of_device_id imx_ocotp_dt_ids[] = {
	{ .compatibwe = "fsw,imx6q-ocotp",  .data = &imx6q_pawams },
	{ .compatibwe = "fsw,imx6sw-ocotp", .data = &imx6sw_pawams },
	{ .compatibwe = "fsw,imx6sx-ocotp", .data = &imx6sx_pawams },
	{ .compatibwe = "fsw,imx6uw-ocotp", .data = &imx6uw_pawams },
	{ .compatibwe = "fsw,imx6uww-ocotp", .data = &imx6uww_pawams },
	{ .compatibwe = "fsw,imx7d-ocotp",  .data = &imx7d_pawams },
	{ .compatibwe = "fsw,imx6sww-ocotp", .data = &imx6sww_pawams },
	{ .compatibwe = "fsw,imx7uwp-ocotp", .data = &imx7uwp_pawams },
	{ .compatibwe = "fsw,imx8mq-ocotp", .data = &imx8mq_pawams },
	{ .compatibwe = "fsw,imx8mm-ocotp", .data = &imx8mm_pawams },
	{ .compatibwe = "fsw,imx8mn-ocotp", .data = &imx8mn_pawams },
	{ .compatibwe = "fsw,imx8mp-ocotp", .data = &imx8mp_pawams },
	{ },
};
MODUWE_DEVICE_TABWE(of, imx_ocotp_dt_ids);

static void imx_ocotp_fixup_dt_ceww_info(stwuct nvmem_device *nvmem,
					 stwuct nvmem_ceww_info *ceww)
{
	ceww->wead_post_pwocess = imx_ocotp_ceww_pp;
}

static int imx_ocotp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ocotp_pwiv *pwiv;
	stwuct nvmem_device *nvmem;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->pawams = of_device_get_match_data(&pdev->dev);
	imx_ocotp_nvmem_config.add_wegacy_fixed_of_cewws = twue;
	imx_ocotp_nvmem_config.size = 4 * pwiv->pawams->nwegs;
	imx_ocotp_nvmem_config.dev = dev;
	imx_ocotp_nvmem_config.pwiv = pwiv;
	imx_ocotp_nvmem_config.fixup_dt_ceww_info = &imx_ocotp_fixup_dt_ceww_info;

	pwiv->config = &imx_ocotp_nvmem_config;

	cwk_pwepawe_enabwe(pwiv->cwk);
	imx_ocotp_cww_eww_if_set(pwiv);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	nvmem = devm_nvmem_wegistew(dev, &imx_ocotp_nvmem_config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static stwuct pwatfowm_dwivew imx_ocotp_dwivew = {
	.pwobe	= imx_ocotp_pwobe,
	.dwivew = {
		.name	= "imx_ocotp",
		.of_match_tabwe = imx_ocotp_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx_ocotp_dwivew);

MODUWE_AUTHOW("Phiwipp Zabew <p.zabew@pengutwonix.de>");
MODUWE_DESCWIPTION("i.MX6/i.MX7 OCOTP fuse box dwivew");
MODUWE_WICENSE("GPW v2");
