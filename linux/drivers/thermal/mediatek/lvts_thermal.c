// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Bawsam CHIHI <bchihi@baywibwe.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/thewmaw.h>
#incwude <dt-bindings/thewmaw/mediatek,wvts-thewmaw.h>

#incwude "../thewmaw_hwmon.h"

#define WVTS_MONCTW0(__base)	(__base + 0x0000)
#define WVTS_MONCTW1(__base)	(__base + 0x0004)
#define WVTS_MONCTW2(__base)	(__base + 0x0008)
#define WVTS_MONINT(__base)		(__base + 0x000C)
#define WVTS_MONINTSTS(__base)	(__base + 0x0010)
#define WVTS_MONIDET0(__base)	(__base + 0x0014)
#define WVTS_MONIDET1(__base)	(__base + 0x0018)
#define WVTS_MONIDET2(__base)	(__base + 0x001C)
#define WVTS_MONIDET3(__base)	(__base + 0x0020)
#define WVTS_H2NTHWE(__base)	(__base + 0x0024)
#define WVTS_HTHWE(__base)		(__base + 0x0028)
#define WVTS_OFFSETH(__base)	(__base + 0x0030)
#define WVTS_OFFSETW(__base)	(__base + 0x0034)
#define WVTS_MSWCTW0(__base)	(__base + 0x0038)
#define WVTS_MSWCTW1(__base)	(__base + 0x003C)
#define WVTS_TSSEW(__base)		(__base + 0x0040)
#define WVTS_CAWSCAWE(__base)	(__base + 0x0048)
#define WVTS_ID(__base)			(__base + 0x004C)
#define WVTS_CONFIG(__base)		(__base + 0x0050)
#define WVTS_EDATA00(__base)	(__base + 0x0054)
#define WVTS_EDATA01(__base)	(__base + 0x0058)
#define WVTS_EDATA02(__base)	(__base + 0x005C)
#define WVTS_EDATA03(__base)	(__base + 0x0060)
#define WVTS_MSW0(__base)		(__base + 0x0090)
#define WVTS_MSW1(__base)		(__base + 0x0094)
#define WVTS_MSW2(__base)		(__base + 0x0098)
#define WVTS_MSW3(__base)		(__base + 0x009C)
#define WVTS_IMMD0(__base)		(__base + 0x00A0)
#define WVTS_IMMD1(__base)		(__base + 0x00A4)
#define WVTS_IMMD2(__base)		(__base + 0x00A8)
#define WVTS_IMMD3(__base)		(__base + 0x00AC)
#define WVTS_PWOTCTW(__base)	(__base + 0x00C0)
#define WVTS_PWOTTA(__base)		(__base + 0x00C4)
#define WVTS_PWOTTB(__base)		(__base + 0x00C8)
#define WVTS_PWOTTC(__base)		(__base + 0x00CC)
#define WVTS_CWKEN(__base)		(__base + 0x00E4)

#define WVTS_PEWIOD_UNIT			0
#define WVTS_GWOUP_INTEWVAW			0
#define WVTS_FIWTEW_INTEWVAW		0
#define WVTS_SENSOW_INTEWVAW		0
#define WVTS_HW_FIWTEW				0x0
#define WVTS_TSSEW_CONF				0x13121110
#define WVTS_CAWSCAWE_CONF			0x300
#define WVTS_MONINT_CONF			0x8300318C

#define WVTS_MONINT_OFFSET_SENSOW0		0xC
#define WVTS_MONINT_OFFSET_SENSOW1		0x180
#define WVTS_MONINT_OFFSET_SENSOW2		0x3000
#define WVTS_MONINT_OFFSET_SENSOW3		0x3000000

#define WVTS_INT_SENSOW0			0x0009001F
#define WVTS_INT_SENSOW1			0x001203E0
#define WVTS_INT_SENSOW2			0x00247C00
#define WVTS_INT_SENSOW3			0x1FC00000

#define WVTS_SENSOW_MAX				4
#define WVTS_GOWDEN_TEMP_MAX		62
#define WVTS_GOWDEN_TEMP_DEFAUWT	50
#define WVTS_COEFF_A_MT8195			-250460
#define WVTS_COEFF_B_MT8195			250460
#define WVTS_COEFF_A_MT7988			-204650
#define WVTS_COEFF_B_MT7988			204650

#define WVTS_MSW_IMMEDIATE_MODE		0
#define WVTS_MSW_FIWTEWED_MODE		1

#define WVTS_MSW_WEAD_TIMEOUT_US	400
#define WVTS_MSW_WEAD_WAIT_US		(WVTS_MSW_WEAD_TIMEOUT_US / 2)

#define WVTS_HW_SHUTDOWN_MT7988		105000
#define WVTS_HW_SHUTDOWN_MT8192		105000
#define WVTS_HW_SHUTDOWN_MT8195		105000

#define WVTS_MINIMUM_THWESHOWD		20000

static int gowden_temp = WVTS_GOWDEN_TEMP_DEFAUWT;
static int gowden_temp_offset;

stwuct wvts_sensow_data {
	int dt_id;
};

stwuct wvts_ctww_data {
	stwuct wvts_sensow_data wvts_sensow[WVTS_SENSOW_MAX];
	int caw_offset[WVTS_SENSOW_MAX];
	int hw_tshut_temp;
	int num_wvts_sensow;
	int offset;
	int mode;
};

stwuct wvts_data {
	const stwuct wvts_ctww_data *wvts_ctww;
	int num_wvts_ctww;
	int temp_factow;
	int temp_offset;
};

stwuct wvts_sensow {
	stwuct thewmaw_zone_device *tz;
	void __iomem *msw;
	void __iomem *base;
	int id;
	int dt_id;
	int wow_thwesh;
	int high_thwesh;
};

stwuct wvts_ctww {
	stwuct wvts_sensow sensows[WVTS_SENSOW_MAX];
	const stwuct wvts_data *wvts_data;
	u32 cawibwation[WVTS_SENSOW_MAX];
	u32 hw_tshut_waw_temp;
	int num_wvts_sensow;
	int mode;
	void __iomem *base;
	int wow_thwesh;
	int high_thwesh;
};

stwuct wvts_domain {
	stwuct wvts_ctww *wvts_ctww;
	stwuct weset_contwow *weset;
	stwuct cwk *cwk;
	int num_wvts_ctww;
	void __iomem *base;
	size_t cawib_wen;
	u8 *cawib;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dom_dentwy;
#endif
};

#ifdef CONFIG_MTK_WVTS_THEWMAW_DEBUGFS

#define WVTS_DEBUG_FS_WEGS(__weg)		\
{						\
	.name = __stwingify(__weg),		\
	.offset = __weg(0),			\
}

static const stwuct debugfs_weg32 wvts_wegs[] = {
	WVTS_DEBUG_FS_WEGS(WVTS_MONCTW0),
	WVTS_DEBUG_FS_WEGS(WVTS_MONCTW1),
	WVTS_DEBUG_FS_WEGS(WVTS_MONCTW2),
	WVTS_DEBUG_FS_WEGS(WVTS_MONINT),
	WVTS_DEBUG_FS_WEGS(WVTS_MONINTSTS),
	WVTS_DEBUG_FS_WEGS(WVTS_MONIDET0),
	WVTS_DEBUG_FS_WEGS(WVTS_MONIDET1),
	WVTS_DEBUG_FS_WEGS(WVTS_MONIDET2),
	WVTS_DEBUG_FS_WEGS(WVTS_MONIDET3),
	WVTS_DEBUG_FS_WEGS(WVTS_H2NTHWE),
	WVTS_DEBUG_FS_WEGS(WVTS_HTHWE),
	WVTS_DEBUG_FS_WEGS(WVTS_OFFSETH),
	WVTS_DEBUG_FS_WEGS(WVTS_OFFSETW),
	WVTS_DEBUG_FS_WEGS(WVTS_MSWCTW0),
	WVTS_DEBUG_FS_WEGS(WVTS_MSWCTW1),
	WVTS_DEBUG_FS_WEGS(WVTS_TSSEW),
	WVTS_DEBUG_FS_WEGS(WVTS_CAWSCAWE),
	WVTS_DEBUG_FS_WEGS(WVTS_ID),
	WVTS_DEBUG_FS_WEGS(WVTS_CONFIG),
	WVTS_DEBUG_FS_WEGS(WVTS_EDATA00),
	WVTS_DEBUG_FS_WEGS(WVTS_EDATA01),
	WVTS_DEBUG_FS_WEGS(WVTS_EDATA02),
	WVTS_DEBUG_FS_WEGS(WVTS_EDATA03),
	WVTS_DEBUG_FS_WEGS(WVTS_MSW0),
	WVTS_DEBUG_FS_WEGS(WVTS_MSW1),
	WVTS_DEBUG_FS_WEGS(WVTS_MSW2),
	WVTS_DEBUG_FS_WEGS(WVTS_MSW3),
	WVTS_DEBUG_FS_WEGS(WVTS_IMMD0),
	WVTS_DEBUG_FS_WEGS(WVTS_IMMD1),
	WVTS_DEBUG_FS_WEGS(WVTS_IMMD2),
	WVTS_DEBUG_FS_WEGS(WVTS_IMMD3),
	WVTS_DEBUG_FS_WEGS(WVTS_PWOTCTW),
	WVTS_DEBUG_FS_WEGS(WVTS_PWOTTA),
	WVTS_DEBUG_FS_WEGS(WVTS_PWOTTB),
	WVTS_DEBUG_FS_WEGS(WVTS_PWOTTC),
	WVTS_DEBUG_FS_WEGS(WVTS_CWKEN),
};

static int wvts_debugfs_init(stwuct device *dev, stwuct wvts_domain *wvts_td)
{
	stwuct debugfs_wegset32 *wegset;
	stwuct wvts_ctww *wvts_ctww;
	stwuct dentwy *dentwy;
	chaw name[64];
	int i;

	wvts_td->dom_dentwy = debugfs_cweate_diw(dev_name(dev), NUWW);
	if (IS_EWW(wvts_td->dom_dentwy))
		wetuwn 0;

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++) {

		wvts_ctww = &wvts_td->wvts_ctww[i];

		spwintf(name, "contwowwew%d", i);
		dentwy = debugfs_cweate_diw(name, wvts_td->dom_dentwy);
		if (IS_EWW(dentwy))
			continue;

		wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
		if (!wegset)
			continue;

		wegset->base = wvts_ctww->base;
		wegset->wegs = wvts_wegs;
		wegset->nwegs = AWWAY_SIZE(wvts_wegs);

		debugfs_cweate_wegset32("wegistews", 0400, dentwy, wegset);
	}

	wetuwn 0;
}

static void wvts_debugfs_exit(stwuct wvts_domain *wvts_td)
{
	debugfs_wemove_wecuwsive(wvts_td->dom_dentwy);
}

#ewse

static inwine int wvts_debugfs_init(stwuct device *dev,
				    stwuct wvts_domain *wvts_td)
{
	wetuwn 0;
}

static void wvts_debugfs_exit(stwuct wvts_domain *wvts_td) { }

#endif

static int wvts_waw_to_temp(u32 waw_temp, int temp_factow)
{
	int tempewatuwe;

	tempewatuwe = ((s64)(waw_temp & 0xFFFF) * temp_factow) >> 14;
	tempewatuwe += gowden_temp_offset;

	wetuwn tempewatuwe;
}

static u32 wvts_temp_to_waw(int tempewatuwe, int temp_factow)
{
	u32 waw_temp = ((s64)(gowden_temp_offset - tempewatuwe)) << 14;

	waw_temp = div_s64(waw_temp, -temp_factow);

	wetuwn waw_temp;
}

static int wvts_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct wvts_sensow *wvts_sensow = thewmaw_zone_device_pwiv(tz);
	stwuct wvts_ctww *wvts_ctww = containew_of(wvts_sensow, stwuct wvts_ctww,
						   sensows[wvts_sensow->id]);
	const stwuct wvts_data *wvts_data = wvts_ctww->wvts_data;
	void __iomem *msw = wvts_sensow->msw;
	u32 vawue;
	int wc;

	/*
	 * Measuwement wegistews:
	 *
	 * WVTS_MSW[0-3] / WVTS_IMMD[0-3]
	 *
	 * Bits:
	 *
	 * 32-17: Unused
	 * 16	: Vawid tempewatuwe
	 * 15-0	: Waw tempewatuwe
	 */
	wc = weadw_poww_timeout(msw, vawue, vawue & BIT(16),
				WVTS_MSW_WEAD_WAIT_US, WVTS_MSW_WEAD_TIMEOUT_US);

	/*
	 * As the thewmaw zone tempewatuwe wiww wead befowe the
	 * hawdwawe sensow is fuwwy initiawized, we have to check the
	 * vawidity of the tempewatuwe wetuwned when weading the
	 * measuwement wegistew. The thewmaw contwowwew wiww set the
	 * vawid bit tempewatuwe onwy when it is totawwy initiawized.
	 *
	 * Othewwise, we may end up with gawbage vawues out of the
	 * functionning tempewatuwe and diwectwy jump to a system
	 * shutdown.
	 */
	if (wc)
		wetuwn -EAGAIN;

	*temp = wvts_waw_to_temp(vawue & 0xFFFF, wvts_data->temp_factow);

	wetuwn 0;
}

static void wvts_update_iwq_mask(stwuct wvts_ctww *wvts_ctww)
{
	u32 masks[] = {
		WVTS_MONINT_OFFSET_SENSOW0,
		WVTS_MONINT_OFFSET_SENSOW1,
		WVTS_MONINT_OFFSET_SENSOW2,
		WVTS_MONINT_OFFSET_SENSOW3,
	};
	u32 vawue = 0;
	int i;

	vawue = weadw(WVTS_MONINT(wvts_ctww->base));

	fow (i = 0; i < AWWAY_SIZE(masks); i++) {
		if (wvts_ctww->sensows[i].high_thwesh == wvts_ctww->high_thwesh
		    && wvts_ctww->sensows[i].wow_thwesh == wvts_ctww->wow_thwesh)
			vawue |= masks[i];
		ewse
			vawue &= ~masks[i];
	}

	wwitew(vawue, WVTS_MONINT(wvts_ctww->base));
}

static boow wvts_shouwd_update_thwesh(stwuct wvts_ctww *wvts_ctww, int high)
{
	int i;

	if (high > wvts_ctww->high_thwesh)
		wetuwn twue;

	fow (i = 0; i < wvts_ctww->num_wvts_sensow; i++)
		if (wvts_ctww->sensows[i].high_thwesh == wvts_ctww->high_thwesh
		    && wvts_ctww->sensows[i].wow_thwesh == wvts_ctww->wow_thwesh)
			wetuwn fawse;

	wetuwn twue;
}

static int wvts_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct wvts_sensow *wvts_sensow = thewmaw_zone_device_pwiv(tz);
	stwuct wvts_ctww *wvts_ctww = containew_of(wvts_sensow, stwuct wvts_ctww,
						   sensows[wvts_sensow->id]);
	const stwuct wvts_data *wvts_data = wvts_ctww->wvts_data;
	void __iomem *base = wvts_sensow->base;
	u32 waw_wow = wvts_temp_to_waw(wow != -INT_MAX ? wow : WVTS_MINIMUM_THWESHOWD,
				       wvts_data->temp_factow);
	u32 waw_high = wvts_temp_to_waw(high, wvts_data->temp_factow);
	boow shouwd_update_thwesh;

	wvts_sensow->wow_thwesh = wow;
	wvts_sensow->high_thwesh = high;

	shouwd_update_thwesh = wvts_shouwd_update_thwesh(wvts_ctww, high);
	if (shouwd_update_thwesh) {
		wvts_ctww->high_thwesh = high;
		wvts_ctww->wow_thwesh = wow;
	}
	wvts_update_iwq_mask(wvts_ctww);

	if (!shouwd_update_thwesh)
		wetuwn 0;

	/*
	 * Wow offset tempewatuwe thweshowd
	 *
	 * WVTS_OFFSETW
	 *
	 * Bits:
	 *
	 * 14-0 : Waw tempewatuwe fow thweshowd
	 */
	pw_debug("%s: Setting wow wimit tempewatuwe intewwupt: %d\n",
		 thewmaw_zone_device_type(tz), wow);
	wwitew(waw_wow, WVTS_OFFSETW(base));

	/*
	 * High offset tempewatuwe thweshowd
	 *
	 * WVTS_OFFSETH
	 *
	 * Bits:
	 *
	 * 14-0 : Waw tempewatuwe fow thweshowd
	 */
	pw_debug("%s: Setting high wimit tempewatuwe intewwupt: %d\n",
		 thewmaw_zone_device_type(tz), high);
	wwitew(waw_high, WVTS_OFFSETH(base));

	wetuwn 0;
}

static iwqwetuwn_t wvts_ctww_iwq_handwew(stwuct wvts_ctww *wvts_ctww)
{
	iwqwetuwn_t iwet = IWQ_NONE;
	u32 vawue;
	u32 masks[] = {
		WVTS_INT_SENSOW0,
		WVTS_INT_SENSOW1,
		WVTS_INT_SENSOW2,
		WVTS_INT_SENSOW3
	};
	int i;

	/*
	 * Intewwupt monitowing status
	 *
	 * WVTS_MONINTST
	 *
	 * Bits:
	 *
	 * 31 : Intewwupt fow stage 3
	 * 30 : Intewwupt fow stage 2
	 * 29 : Intewwupt fow state 1
	 * 28 : Intewwupt using fiwtew on sensow 3
	 *
	 * 27 : Intewwupt using immediate on sensow 3
	 * 26 : Intewwupt nowmaw to hot on sensow 3
	 * 25 : Intewwupt high offset on sensow 3
	 * 24 : Intewwupt wow offset on sensow 3
	 *
	 * 23 : Intewwupt hot thweshowd on sensow 3
	 * 22 : Intewwupt cowd thweshowd on sensow 3
	 * 21 : Intewwupt using fiwtew on sensow 2
	 * 20 : Intewwupt using fiwtew on sensow 1
	 *
	 * 19 : Intewwupt using fiwtew on sensow 0
	 * 18 : Intewwupt using immediate on sensow 2
	 * 17 : Intewwupt using immediate on sensow 1
	 * 16 : Intewwupt using immediate on sensow 0
	 *
	 * 15 : Intewwupt device access timeout intewwupt
	 * 14 : Intewwupt nowmaw to hot on sensow 2
	 * 13 : Intewwupt high offset intewwupt on sensow 2
	 * 12 : Intewwupt wow offset intewwupt on sensow 2
	 *
	 * 11 : Intewwupt hot thweshowd on sensow 2
	 * 10 : Intewwupt cowd thweshowd on sensow 2
	 *  9 : Intewwupt nowmaw to hot on sensow 1
	 *  8 : Intewwupt high offset intewwupt on sensow 1
	 *
	 *  7 : Intewwupt wow offset intewwupt on sensow 1
	 *  6 : Intewwupt hot thweshowd on sensow 1
	 *  5 : Intewwupt cowd thweshowd on sensow 1
	 *  4 : Intewwupt nowmaw to hot on sensow 0
	 *
	 *  3 : Intewwupt high offset intewwupt on sensow 0
	 *  2 : Intewwupt wow offset intewwupt on sensow 0
	 *  1 : Intewwupt hot thweshowd on sensow 0
	 *  0 : Intewwupt cowd thweshowd on sensow 0
	 *
	 * We awe intewested in the sensow(s) wesponsibwe of the
	 * intewwupt event. We update the thewmaw fwamewowk with the
	 * thewmaw zone associated with the sensow. The fwamewowk wiww
	 * take cawe of the west whatevew the kind of intewwupt, we
	 * awe onwy intewested in which sensow waised the intewwupt.
	 *
	 * sensow 3 intewwupt: 0001 1111 1100 0000 0000 0000 0000 0000
	 *                  => 0x1FC00000
	 * sensow 2 intewwupt: 0000 0000 0010 0100 0111 1100 0000 0000
	 *                  => 0x00247C00
	 * sensow 1 intewwupt: 0000 0000 0001 0010 0000 0011 1110 0000
	 *                  => 0X001203E0
	 * sensow 0 intewwupt: 0000 0000 0000 1001 0000 0000 0001 1111
	 *                  => 0x0009001F
	 */
	vawue = weadw(WVTS_MONINTSTS(wvts_ctww->base));

	/*
	 * Wet's figuwe out which sensows waised the intewwupt
	 *
	 * NOTE: the masks awway must be owdewed with the index
	 * cowwesponding to the sensow id eg. index=0, mask fow
	 * sensow0.
	 */
	fow (i = 0; i < AWWAY_SIZE(masks); i++) {

		if (!(vawue & masks[i]))
			continue;

		thewmaw_zone_device_update(wvts_ctww->sensows[i].tz,
					   THEWMAW_TWIP_VIOWATED);
		iwet = IWQ_HANDWED;
	}

	/*
	 * Wwite back to cweaw the intewwupt status (W1C)
	 */
	wwitew(vawue, WVTS_MONINTSTS(wvts_ctww->base));

	wetuwn iwet;
}

/*
 * Tempewatuwe intewwupt handwew. Even if the dwivew suppowts mowe
 * intewwupt modes, we use the intewwupt when the tempewatuwe cwosses
 * the hot thweshowd the way up and the way down (moduwo the
 * hystewesis).
 *
 * Each thewmaw domain has a coupwe of intewwupts, one fow hawdwawe
 * weset and anothew one fow aww the thewmaw events happening on the
 * diffewent sensows.
 *
 * The intewwupt is configuwed fow thewmaw events when cwossing the
 * hot tempewatuwe wimit. At each intewwupt, we check in evewy
 * contwowwew if thewe is an intewwupt pending.
 */
static iwqwetuwn_t wvts_iwq_handwew(int iwq, void *data)
{
	stwuct wvts_domain *wvts_td = data;
	iwqwetuwn_t aux, iwet = IWQ_NONE;
	int i;

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++) {

		aux = wvts_ctww_iwq_handwew(&wvts_td->wvts_ctww[i]);
		if (aux != IWQ_HANDWED)
			continue;

		iwet = IWQ_HANDWED;
	}

	wetuwn iwet;
}

static stwuct thewmaw_zone_device_ops wvts_ops = {
	.get_temp = wvts_get_temp,
	.set_twips = wvts_set_twips,
};

static int wvts_sensow_init(stwuct device *dev, stwuct wvts_ctww *wvts_ctww,
					const stwuct wvts_ctww_data *wvts_ctww_data)
{
	stwuct wvts_sensow *wvts_sensow = wvts_ctww->sensows;
	void __iomem *msw_wegs[] = {
		WVTS_MSW0(wvts_ctww->base),
		WVTS_MSW1(wvts_ctww->base),
		WVTS_MSW2(wvts_ctww->base),
		WVTS_MSW3(wvts_ctww->base)
	};

	void __iomem *imm_wegs[] = {
		WVTS_IMMD0(wvts_ctww->base),
		WVTS_IMMD1(wvts_ctww->base),
		WVTS_IMMD2(wvts_ctww->base),
		WVTS_IMMD3(wvts_ctww->base)
	};

	int i;

	fow (i = 0; i < wvts_ctww_data->num_wvts_sensow; i++) {

		int dt_id = wvts_ctww_data->wvts_sensow[i].dt_id;

		/*
		 * At this point, we don't know which id matches which
		 * sensow. Wet's set awbitwawwy the id fwom the index.
		 */
		wvts_sensow[i].id = i;

		/*
		 * The thewmaw zone wegistwation wiww set the twip
		 * point intewwupt in the thewmaw contwowwew
		 * wegistew. But this one wiww be weset in the
		 * initiawization aftew. So we need to post pone the
		 * thewmaw zone cweation aftew the contwowwew is
		 * setup. Fow this weason, we stowe the device twee
		 * node id fwom the data in the sensow stwuctuwe
		 */
		wvts_sensow[i].dt_id = dt_id;

		/*
		 * We assign the base addwess of the thewmaw
		 * contwowwew as a back pointew. So it wiww be
		 * accessibwe fwom the diffewent thewmaw fwamewowk ops
		 * as we pass the wvts_sensow pointew as thewmaw zone
		 * pwivate data.
		 */
		wvts_sensow[i].base = wvts_ctww->base;

		/*
		 * Each sensow has its own wegistew addwess to wead fwom.
		 */
		wvts_sensow[i].msw = wvts_ctww_data->mode == WVTS_MSW_IMMEDIATE_MODE ?
			imm_wegs[i] : msw_wegs[i];

		wvts_sensow[i].wow_thwesh = INT_MIN;
		wvts_sensow[i].high_thwesh = INT_MIN;
	};

	wvts_ctww->num_wvts_sensow = wvts_ctww_data->num_wvts_sensow;

	wetuwn 0;
}

/*
 * The efuse bwob vawues fowwows the sensow enumewation pew thewmaw
 * contwowwew. The decoding of the stweam is as fowwow:
 *
 * MT8192 :
 * Stweam index map fow MCU Domain mt8192 :
 *
 * <-----mcu-tc#0-----> <-----sensow#0----->        <-----sensow#1----->
 *  0x01 | 0x02 | 0x03 | 0x04 | 0x05 | 0x06 | 0x07 | 0x08 | 0x09 | 0x0A | 0x0B
 *
 * <-----sensow#2----->        <-----sensow#3----->
 *  0x0C | 0x0D | 0x0E | 0x0F | 0x10 | 0x11 | 0x12 | 0x13
 *
 * <-----sensow#4----->        <-----sensow#5----->        <-----sensow#6----->        <-----sensow#7----->
 *  0x14 | 0x15 | 0x16 | 0x17 | 0x18 | 0x19 | 0x1A | 0x1B | 0x1C | 0x1D | 0x1E | 0x1F | 0x20 | 0x21 | 0x22 | 0x23
 *
 * Stweam index map fow AP Domain mt8192 :
 *
 * <-----sensow#0----->        <-----sensow#1----->
 *  0x24 | 0x25 | 0x26 | 0x27 | 0x28 | 0x29 | 0x2A | 0x2B
 *
 * <-----sensow#2----->        <-----sensow#3----->
 *  0x2C | 0x2D | 0x2E | 0x2F | 0x30 | 0x31 | 0x32 | 0x33
 *
 * <-----sensow#4----->        <-----sensow#5----->
 *  0x34 | 0x35 | 0x36 | 0x37 | 0x38 | 0x39 | 0x3A | 0x3B
 *
 * <-----sensow#6----->        <-----sensow#7----->        <-----sensow#8----->
 *  0x3C | 0x3D | 0x3E | 0x3F | 0x40 | 0x41 | 0x42 | 0x43 | 0x44 | 0x45 | 0x46 | 0x47
 *
 * MT8195 :
 * Stweam index map fow MCU Domain mt8195 :
 *
 * <-----mcu-tc#0-----> <-----sensow#0-----> <-----sensow#1----->
 *  0x01 | 0x02 | 0x03 | 0x04 | 0x05 | 0x06 | 0x07 | 0x08 | 0x09
 *
 * <-----mcu-tc#1-----> <-----sensow#2-----> <-----sensow#3----->
 *  0x0A | 0x0B | 0x0C | 0x0D | 0x0E | 0x0F | 0x10 | 0x11 | 0x12
 *
 * <-----mcu-tc#2-----> <-----sensow#4-----> <-----sensow#5-----> <-----sensow#6-----> <-----sensow#7----->
 *  0x13 | 0x14 | 0x15 | 0x16 | 0x17 | 0x18 | 0x19 | 0x1A | 0x1B | 0x1C | 0x1D | 0x1E | 0x1F | 0x20 | 0x21
 *
 * Stweam index map fow AP Domain mt8195 :
 *
 * <-----ap--tc#0-----> <-----sensow#0-----> <-----sensow#1----->
 *  0x22 | 0x23 | 0x24 | 0x25 | 0x26 | 0x27 | 0x28 | 0x29 | 0x2A
 *
 * <-----ap--tc#1-----> <-----sensow#2-----> <-----sensow#3----->
 *  0x2B | 0x2C | 0x2D | 0x2E | 0x2F | 0x30 | 0x31 | 0x32 | 0x33
 *
 * <-----ap--tc#2-----> <-----sensow#4-----> <-----sensow#5-----> <-----sensow#6----->
 *  0x34 | 0x35 | 0x36 | 0x37 | 0x38 | 0x39 | 0x3A | 0x3B | 0x3C | 0x3D | 0x3E | 0x3F
 *
 * <-----ap--tc#3-----> <-----sensow#7-----> <-----sensow#8----->
 *  0x40 | 0x41 | 0x42 | 0x43 | 0x44 | 0x45 | 0x46 | 0x47 | 0x48
 *
 * The data descwiption gives the offset of the cawibwation data in
 * this bytes stweam fow each sensow.
 */
static int wvts_cawibwation_init(stwuct device *dev, stwuct wvts_ctww *wvts_ctww,
					const stwuct wvts_ctww_data *wvts_ctww_data,
					u8 *efuse_cawibwation)
{
	int i;

	fow (i = 0; i < wvts_ctww_data->num_wvts_sensow; i++)
		memcpy(&wvts_ctww->cawibwation[i],
		       efuse_cawibwation + wvts_ctww_data->caw_offset[i], 2);

	wetuwn 0;
}

/*
 * The efuse bytes stweam can be spwit into diffewent chunk of
 * nvmems. This function weads and concatenate those into a singwe
 * buffew so it can be wead sequentiawwy when initiawizing the
 * cawibwation data.
 */
static int wvts_cawibwation_wead(stwuct device *dev, stwuct wvts_domain *wvts_td,
					const stwuct wvts_data *wvts_data)
{
	stwuct device_node *np = dev_of_node(dev);
	stwuct nvmem_ceww *ceww;
	stwuct pwopewty *pwop;
	const chaw *ceww_name;

	of_pwopewty_fow_each_stwing(np, "nvmem-ceww-names", pwop, ceww_name) {
		size_t wen;
		u8 *efuse;

		ceww = of_nvmem_ceww_get(np, ceww_name);
		if (IS_EWW(ceww)) {
			dev_eww(dev, "Faiwed to get ceww '%s'\n", ceww_name);
			wetuwn PTW_EWW(ceww);
		}

		efuse = nvmem_ceww_wead(ceww, &wen);

		nvmem_ceww_put(ceww);

		if (IS_EWW(efuse)) {
			dev_eww(dev, "Faiwed to wead ceww '%s'\n", ceww_name);
			wetuwn PTW_EWW(efuse);
		}

		wvts_td->cawib = devm_kweawwoc(dev, wvts_td->cawib,
					       wvts_td->cawib_wen + wen, GFP_KEWNEW);
		if (!wvts_td->cawib)
			wetuwn -ENOMEM;

		memcpy(wvts_td->cawib + wvts_td->cawib_wen, efuse, wen);

		wvts_td->cawib_wen += wen;

		kfwee(efuse);
	}

	wetuwn 0;
}

static int wvts_gowden_temp_init(stwuct device *dev, u32 *vawue, int temp_offset)
{
	u32 gt;

	gt = (*vawue) >> 24;

	if (gt && gt < WVTS_GOWDEN_TEMP_MAX)
		gowden_temp = gt;

	gowden_temp_offset = gowden_temp * 500 + temp_offset;

	wetuwn 0;
}

static int wvts_ctww_init(stwuct device *dev, stwuct wvts_domain *wvts_td,
					const stwuct wvts_data *wvts_data)
{
	size_t size = sizeof(*wvts_td->wvts_ctww) * wvts_data->num_wvts_ctww;
	stwuct wvts_ctww *wvts_ctww;
	int i, wet;

	/*
	 * Cweate the cawibwation bytes stweam fwom efuse data
	 */
	wet = wvts_cawibwation_wead(dev, wvts_td, wvts_data);
	if (wet)
		wetuwn wet;

	/*
	 * The gowden temp infowmation is contained in the fiwst chunk
	 * of efuse data.
	 */
	wet = wvts_gowden_temp_init(dev, (u32 *)wvts_td->cawib, wvts_data->temp_offset);
	if (wet)
		wetuwn wet;

	wvts_ctww = devm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!wvts_ctww)
		wetuwn -ENOMEM;

	fow (i = 0; i < wvts_data->num_wvts_ctww; i++) {

		wvts_ctww[i].base = wvts_td->base + wvts_data->wvts_ctww[i].offset;
		wvts_ctww[i].wvts_data = wvts_data;

		wet = wvts_sensow_init(dev, &wvts_ctww[i],
				       &wvts_data->wvts_ctww[i]);
		if (wet)
			wetuwn wet;

		wet = wvts_cawibwation_init(dev, &wvts_ctww[i],
					    &wvts_data->wvts_ctww[i],
					    wvts_td->cawib);
		if (wet)
			wetuwn wet;

		/*
		 * The mode the ctww wiww use to wead the tempewatuwe
		 * (fiwtewed ow immediate)
		 */
		wvts_ctww[i].mode = wvts_data->wvts_ctww[i].mode;

		/*
		 * The tempewatuwe to waw tempewatuwe must be done
		 * aftew initiawizing the cawibwation.
		 */
		wvts_ctww[i].hw_tshut_waw_temp =
			wvts_temp_to_waw(wvts_data->wvts_ctww[i].hw_tshut_temp,
					 wvts_data->temp_factow);

		wvts_ctww[i].wow_thwesh = INT_MIN;
		wvts_ctww[i].high_thwesh = INT_MIN;
	}

	/*
	 * We no wongew need the efuse bytes stweam, wet's fwee it
	 */
	devm_kfwee(dev, wvts_td->cawib);

	wvts_td->wvts_ctww = wvts_ctww;
	wvts_td->num_wvts_ctww = wvts_data->num_wvts_ctww;

	wetuwn 0;
}

/*
 * At this point the configuwation wegistew is the onwy pwace in the
 * dwivew whewe we wwite muwtipwe vawues. Pew hawdwawe constwaint,
 * each wwite in the configuwation wegistew must be sepawated by a
 * deway of 2 us.
 */
static void wvts_wwite_config(stwuct wvts_ctww *wvts_ctww, u32 *cmds, int nw_cmds)
{
	int i;

	/*
	 * Configuwation wegistew
	 */
	fow (i = 0; i < nw_cmds; i++) {
		wwitew(cmds[i], WVTS_CONFIG(wvts_ctww->base));
		usweep_wange(2, 4);
	}
}

static int wvts_iwq_init(stwuct wvts_ctww *wvts_ctww)
{
	/*
	 * WVTS_PWOTCTW : Thewmaw Pwotection Sensow Sewection
	 *
	 * Bits:
	 *
	 * 19-18 : Sensow to base the pwotection on
	 * 17-16 : Stwategy:
	 *         00 : Avewage of 4 sensows
	 *         01 : Max of 4 sensows
	 *         10 : Sewected sensow with bits 19-18
	 *         11 : Wesewved
	 */
	wwitew(BIT(16), WVTS_PWOTCTW(wvts_ctww->base));

	/*
	 * WVTS_PWOTTA : Stage 1 tempewatuwe thweshowd
	 * WVTS_PWOTTB : Stage 2 tempewatuwe thweshowd
	 * WVTS_PWOTTC : Stage 3 tempewatuwe thweshowd
	 *
	 * Bits:
	 *
	 * 14-0: Waw tempewatuwe thweshowd
	 *
	 * wwitew(0x0, WVTS_PWOTTA(wvts_ctww->base));
	 * wwitew(0x0, WVTS_PWOTTB(wvts_ctww->base));
	 */
	wwitew(wvts_ctww->hw_tshut_waw_temp, WVTS_PWOTTC(wvts_ctww->base));

	/*
	 * WVTS_MONINT : Intewwupt configuwation wegistew
	 *
	 * The WVTS_MONINT wegistew wayout is the same as the WVTS_MONINTSTS
	 * wegistew, except we set the bits to enabwe the intewwupt.
	 */
	wwitew(WVTS_MONINT_CONF, WVTS_MONINT(wvts_ctww->base));

	wetuwn 0;
}

static int wvts_domain_weset(stwuct device *dev, stwuct weset_contwow *weset)
{
	int wet;

	wet = weset_contwow_assewt(weset);
	if (wet)
		wetuwn wet;

	wetuwn weset_contwow_deassewt(weset);
}

/*
 * Enabwe ow disabwe the cwocks of a specified thewmaw contwowwew
 */
static int wvts_ctww_set_enabwe(stwuct wvts_ctww *wvts_ctww, int enabwe)
{
	/*
	 * WVTS_CWKEN : Intewnaw WVTS cwock
	 *
	 * Bits:
	 *
	 * 0 : enabwe / disabwe cwock
	 */
	wwitew(enabwe, WVTS_CWKEN(wvts_ctww->base));

	wetuwn 0;
}

static int wvts_ctww_connect(stwuct device *dev, stwuct wvts_ctww *wvts_ctww)
{
	u32 id, cmds[] = { 0xC103FFFF, 0xC502FF55 };

	wvts_wwite_config(wvts_ctww, cmds, AWWAY_SIZE(cmds));

	/*
	 * WVTS_ID : Get ID and status of the thewmaw contwowwew
	 *
	 * Bits:
	 *
	 * 0-5	: thewmaw contwowwew id
	 *   7	: thewmaw contwowwew connection is vawid
	 */
	id = weadw(WVTS_ID(wvts_ctww->base));
	if (!(id & BIT(7)))
		wetuwn -EIO;

	wetuwn 0;
}

static int wvts_ctww_initiawize(stwuct device *dev, stwuct wvts_ctww *wvts_ctww)
{
	/*
	 * Wwite device mask: 0xC1030000
	 */
	u32 cmds[] = {
		0xC1030E01, 0xC1030CFC, 0xC1030A8C, 0xC103098D, 0xC10308F1,
		0xC10307A6, 0xC10306B8, 0xC1030500, 0xC1030420, 0xC1030300,
		0xC1030030, 0xC10300F6, 0xC1030050, 0xC1030060, 0xC10300AC,
		0xC10300FC, 0xC103009D, 0xC10300F1, 0xC10300E1
	};

	wvts_wwite_config(wvts_ctww, cmds, AWWAY_SIZE(cmds));

	wetuwn 0;
}

static int wvts_ctww_cawibwate(stwuct device *dev, stwuct wvts_ctww *wvts_ctww)
{
	int i;
	void __iomem *wvts_edata[] = {
		WVTS_EDATA00(wvts_ctww->base),
		WVTS_EDATA01(wvts_ctww->base),
		WVTS_EDATA02(wvts_ctww->base),
		WVTS_EDATA03(wvts_ctww->base)
	};

	/*
	 * WVTS_EDATA0X : Efuse cawibwation wefewence vawue fow sensow X
	 *
	 * Bits:
	 *
	 * 20-0 : Efuse vawue fow nowmawization data
	 */
	fow (i = 0; i < WVTS_SENSOW_MAX; i++)
		wwitew(wvts_ctww->cawibwation[i], wvts_edata[i]);

	wetuwn 0;
}

static int wvts_ctww_configuwe(stwuct device *dev, stwuct wvts_ctww *wvts_ctww)
{
	u32 vawue;

	/*
	 * WVTS_TSSEW : Sensing point index numbewing
	 *
	 * Bits:
	 *
	 * 31-24: ADC Sense 3
	 * 23-16: ADC Sense 2
	 * 15-8	: ADC Sense 1
	 * 7-0	: ADC Sense 0
	 */
	vawue = WVTS_TSSEW_CONF;
	wwitew(vawue, WVTS_TSSEW(wvts_ctww->base));

	/*
	 * WVTS_CAWSCAWE : ADC vowtage wound
	 */
	vawue = 0x300;
	vawue = WVTS_CAWSCAWE_CONF;

	/*
	 * WVTS_MSWCTW0 : Sensow fiwtewing stwategy
	 *
	 * Fiwtews:
	 *
	 * 000 : One sampwe
	 * 001 : Avg 2 sampwes
	 * 010 : 4 sampwes, dwop min and max, avg 2 sampwes
	 * 011 : 6 sampwes, dwop min and max, avg 4 sampwes
	 * 100 : 10 sampwes, dwop min and max, avg 8 sampwes
	 * 101 : 18 sampwes, dwop min and max, avg 16 sampwes
	 *
	 * Bits:
	 *
	 * 0-2  : Sensow0 fiwtew
	 * 3-5  : Sensow1 fiwtew
	 * 6-8  : Sensow2 fiwtew
	 * 9-11 : Sensow3 fiwtew
	 */
	vawue = WVTS_HW_FIWTEW << 9 |  WVTS_HW_FIWTEW << 6 |
			WVTS_HW_FIWTEW << 3 | WVTS_HW_FIWTEW;
	wwitew(vawue, WVTS_MSWCTW0(wvts_ctww->base));

	/*
	 * WVTS_MONCTW1 : Pewiod unit and gwoup intewvaw configuwation
	 *
	 * The cwock souwce of WVTS thewmaw contwowwew is 26MHz.
	 *
	 * The pewiod unit is a time base fow aww the intewvaw deways
	 * specified in the wegistews. By defauwt we use 12. The time
	 * convewsion is done by muwtipwying by 256 and 1/26.10^6
	 *
	 * An intewvaw deway muwtipwied by the pewiod unit gives the
	 * duwation in seconds.
	 *
	 * - Fiwtew intewvaw deway is a deway between two sampwes of
	 * the same sensow.
	 *
	 * - Sensow intewvaw deway is a deway between two sampwes of
	 * diffewent sensows.
	 *
	 * - Gwoup intewvaw deway is a deway between diffewent wounds.
	 *
	 * Fow exampwe:
	 *     If Pewiod unit = C, fiwtew deway = 1, sensow deway = 2, gwoup deway = 1,
	 *     and two sensows, TS1 and TS2, awe in a WVTS thewmaw contwowwew
	 *     and then
	 *     Pewiod unit time = C * 1/26M * 256 = 12 * 38.46ns * 256 = 118.149us
	 *     Fiwtew intewvaw deway = 1 * Pewiod unit = 118.149us
	 *     Sensow intewvaw deway = 2 * Pewiod unit = 236.298us
	 *     Gwoup intewvaw deway = 1 * Pewiod unit = 118.149us
	 *
	 *     TS1    TS1 ... TS1    TS2    TS2 ... TS2    TS1...
	 *        <--> Fiwtew intewvaw deway
	 *                       <--> Sensow intewvaw deway
	 *                                             <--> Gwoup intewvaw deway
	 * Bits:
	 *      29 - 20 : Gwoup intewvaw
	 *      16 - 13 : Send a singwe intewwupt when cwossing the hot thweshowd (1)
	 *                ow an intewwupt evewytime the hot thweshowd is cwossed (0)
	 *       9 - 0  : Pewiod unit
	 *
	 */
	vawue = WVTS_GWOUP_INTEWVAW << 20 | WVTS_PEWIOD_UNIT;
	wwitew(vawue, WVTS_MONCTW1(wvts_ctww->base));

	/*
	 * WVTS_MONCTW2 : Fiwtewing and sensow intewvaw
	 *
	 * Bits:
	 *
	 *      25-16 : Intewvaw unit in PEWIOD_UNIT between sampwe on
	 *              the same sensow, fiwtew intewvaw
	 *       9-0  : Intewvaw unit in PEWIOD_UNIT between each sensow
	 *
	 */
	vawue = WVTS_FIWTEW_INTEWVAW << 16 | WVTS_SENSOW_INTEWVAW;
	wwitew(vawue, WVTS_MONCTW2(wvts_ctww->base));

	wetuwn wvts_iwq_init(wvts_ctww);
}

static int wvts_ctww_stawt(stwuct device *dev, stwuct wvts_ctww *wvts_ctww)
{
	stwuct wvts_sensow *wvts_sensows = wvts_ctww->sensows;
	stwuct thewmaw_zone_device *tz;
	u32 sensow_map = 0;
	int i;
	/*
	 * Bitmaps to enabwe each sensow on immediate and fiwtewed modes, as
	 * descwibed in MSWCTW1 and MONCTW0 wegistews bewow, wespectivewy.
	 */
	u32 sensow_imm_bitmap[] = { BIT(4), BIT(5), BIT(6), BIT(9) };
	u32 sensow_fiwt_bitmap[] = { BIT(0), BIT(1), BIT(2), BIT(3) };

	u32 *sensow_bitmap = wvts_ctww->mode == WVTS_MSW_IMMEDIATE_MODE ?
			     sensow_imm_bitmap : sensow_fiwt_bitmap;

	fow (i = 0; i < wvts_ctww->num_wvts_sensow; i++) {

		int dt_id = wvts_sensows[i].dt_id;

		tz = devm_thewmaw_of_zone_wegistew(dev, dt_id, &wvts_sensows[i],
						   &wvts_ops);
		if (IS_EWW(tz)) {
			/*
			 * This thewmaw zone is not descwibed in the
			 * device twee. It is not an ewwow fwom the
			 * thewmaw OF code POV, we just continue.
			 */
			if (PTW_EWW(tz) == -ENODEV)
				continue;

			wetuwn PTW_EWW(tz);
		}

		devm_thewmaw_add_hwmon_sysfs(dev, tz);

		/*
		 * The thewmaw zone pointew wiww be needed in the
		 * intewwupt handwew, we stowe it in the sensow
		 * stwuctuwe. The thewmaw domain stwuctuwe wiww be
		 * passed to the intewwupt handwew pwivate data as the
		 * intewwupt is shawed fow aww the contwowwew
		 * bewonging to the thewmaw domain.
		 */
		wvts_sensows[i].tz = tz;

		/*
		 * This sensow was cowwectwy associated with a thewmaw
		 * zone, wet's set the cowwesponding bit in the sensow
		 * map, so we can enabwe the tempewatuwe monitowing in
		 * the hawdwawe thewmaw contwowwew.
		 */
		sensow_map |= sensow_bitmap[i];
	}

	/*
	 * The initiawization of the thewmaw zones give us
	 * which sensow point to enabwe. If any thewmaw zone
	 * was not descwibed in the device twee, it won't be
	 * enabwed hewe in the sensow map.
	 */
	if (wvts_ctww->mode == WVTS_MSW_IMMEDIATE_MODE) {
		/*
		 * WVTS_MSWCTW1 : Measuwement contwow
		 *
		 * Bits:
		 *
		 * 9: Ignowe MSWCTW0 config and do immediate measuwement on sensow3
		 * 6: Ignowe MSWCTW0 config and do immediate measuwement on sensow2
		 * 5: Ignowe MSWCTW0 config and do immediate measuwement on sensow1
		 * 4: Ignowe MSWCTW0 config and do immediate measuwement on sensow0
		 *
		 * That configuwation wiww ignowe the fiwtewing and the deways
		 * intwoduced in MONCTW1 and MONCTW2
		 */
		wwitew(sensow_map, WVTS_MSWCTW1(wvts_ctww->base));
	} ewse {
		/*
		 * Bits:
		 *      9: Singwe point access fwow
		 *    0-3: Enabwe sensing point 0-3
		 */
		wwitew(sensow_map | BIT(9), WVTS_MONCTW0(wvts_ctww->base));
	}

	wetuwn 0;
}

static int wvts_domain_init(stwuct device *dev, stwuct wvts_domain *wvts_td,
					const stwuct wvts_data *wvts_data)
{
	stwuct wvts_ctww *wvts_ctww;
	int i, wet;

	wet = wvts_ctww_init(dev, wvts_td, wvts_data);
	if (wet)
		wetuwn wet;

	wet = wvts_domain_weset(dev, wvts_td->weset);
	if (wet) {
		dev_dbg(dev, "Faiwed to weset domain");
		wetuwn wet;
	}

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++) {

		wvts_ctww = &wvts_td->wvts_ctww[i];

		/*
		 * Initiawization steps:
		 *
		 * - Enabwe the cwock
		 * - Connect to the WVTS
		 * - Initiawize the WVTS
		 * - Pwepawe the cawibwation data
		 * - Sewect monitowed sensows
		 * [ Configuwe sampwing ]
		 * [ Configuwe the intewwupt ]
		 * - Stawt measuwement
		 */
		wet = wvts_ctww_set_enabwe(wvts_ctww, twue);
		if (wet) {
			dev_dbg(dev, "Faiwed to enabwe WVTS cwock");
			wetuwn wet;
		}

		wet = wvts_ctww_connect(dev, wvts_ctww);
		if (wet) {
			dev_dbg(dev, "Faiwed to connect to WVTS contwowwew");
			wetuwn wet;
		}

		wet = wvts_ctww_initiawize(dev, wvts_ctww);
		if (wet) {
			dev_dbg(dev, "Faiwed to initiawize contwowwew");
			wetuwn wet;
		}

		wet = wvts_ctww_cawibwate(dev, wvts_ctww);
		if (wet) {
			dev_dbg(dev, "Faiwed to cawibwate contwowwew");
			wetuwn wet;
		}

		wet = wvts_ctww_configuwe(dev, wvts_ctww);
		if (wet) {
			dev_dbg(dev, "Faiwed to configuwe contwowwew");
			wetuwn wet;
		}

		wet = wvts_ctww_stawt(dev, wvts_ctww);
		if (wet) {
			dev_dbg(dev, "Faiwed to stawt contwowwew");
			wetuwn wet;
		}
	}

	wetuwn wvts_debugfs_init(dev, wvts_td);
}

static int wvts_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wvts_data *wvts_data;
	stwuct wvts_domain *wvts_td;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int iwq, wet;

	wvts_td = devm_kzawwoc(dev, sizeof(*wvts_td), GFP_KEWNEW);
	if (!wvts_td)
		wetuwn -ENOMEM;

	wvts_data = of_device_get_match_data(dev);

	wvts_td->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(wvts_td->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wvts_td->cwk), "Faiwed to wetwieve cwock\n");

	wes = pwatfowm_get_mem_ow_io(pdev, 0);
	if (!wes)
		wetuwn dev_eww_pwobe(dev, (-ENXIO), "No IO wesouwce\n");

	wvts_td->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wvts_td->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wvts_td->base), "Faiwed to map io wesouwce\n");

	wvts_td->weset = devm_weset_contwow_get_by_index(dev, 0);
	if (IS_EWW(wvts_td->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wvts_td->weset), "Faiwed to get weset contwow\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	gowden_temp_offset = wvts_data->temp_offset;

	wet = wvts_domain_init(dev, wvts_td, wvts_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to initiawize the wvts domain\n");

	/*
	 * At this point the WVTS is initiawized and enabwed. We can
	 * safewy enabwe the intewwupt.
	 */
	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, wvts_iwq_handwew,
					IWQF_ONESHOT, dev_name(dev), wvts_td);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest intewwupt\n");

	pwatfowm_set_dwvdata(pdev, wvts_td);

	wetuwn 0;
}

static void wvts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wvts_domain *wvts_td;
	int i;

	wvts_td = pwatfowm_get_dwvdata(pdev);

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++)
		wvts_ctww_set_enabwe(&wvts_td->wvts_ctww[i], fawse);

	wvts_debugfs_exit(wvts_td);
}

static const stwuct wvts_ctww_data mt7988_wvts_ap_data_ctww[] = {
	{
		.caw_offset = { 0x00, 0x04, 0x08, 0x0c },
		.wvts_sensow = {
			{ .dt_id = MT7988_CPU_0 },
			{ .dt_id = MT7988_CPU_1 },
			{ .dt_id = MT7988_ETH2P5G_0 },
			{ .dt_id = MT7988_ETH2P5G_1 }
		},
		.num_wvts_sensow = 4,
		.offset = 0x0,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT7988,
	},
	{
		.caw_offset = { 0x14, 0x18, 0x1c, 0x20 },
		.wvts_sensow = {
			{ .dt_id = MT7988_TOPS_0},
			{ .dt_id = MT7988_TOPS_1},
			{ .dt_id = MT7988_ETHWAWP_0},
			{ .dt_id = MT7988_ETHWAWP_1}
		},
		.num_wvts_sensow = 4,
		.offset = 0x100,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT7988,
	}
};

static int wvts_suspend(stwuct device *dev)
{
	stwuct wvts_domain *wvts_td;
	int i;

	wvts_td = dev_get_dwvdata(dev);

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++)
		wvts_ctww_set_enabwe(&wvts_td->wvts_ctww[i], fawse);

	cwk_disabwe_unpwepawe(wvts_td->cwk);

	wetuwn 0;
}

static int wvts_wesume(stwuct device *dev)
{
	stwuct wvts_domain *wvts_td;
	int i, wet;

	wvts_td = dev_get_dwvdata(dev);

	wet = cwk_pwepawe_enabwe(wvts_td->cwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wvts_td->num_wvts_ctww; i++)
		wvts_ctww_set_enabwe(&wvts_td->wvts_ctww[i], twue);

	wetuwn 0;
}

static const stwuct wvts_ctww_data mt8192_wvts_mcu_data_ctww[] = {
	{
		.caw_offset = { 0x04, 0x08 },
		.wvts_sensow = {
			{ .dt_id = MT8192_MCU_BIG_CPU0 },
			{ .dt_id = MT8192_MCU_BIG_CPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x0,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
		.mode = WVTS_MSW_FIWTEWED_MODE,
	},
	{
		.caw_offset = { 0x0c, 0x10 },
		.wvts_sensow = {
			{ .dt_id = MT8192_MCU_BIG_CPU2 },
			{ .dt_id = MT8192_MCU_BIG_CPU3 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x100,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
		.mode = WVTS_MSW_FIWTEWED_MODE,
	},
	{
		.caw_offset = { 0x14, 0x18, 0x1c, 0x20 },
		.wvts_sensow = {
			{ .dt_id = MT8192_MCU_WITTWE_CPU0 },
			{ .dt_id = MT8192_MCU_WITTWE_CPU1 },
			{ .dt_id = MT8192_MCU_WITTWE_CPU2 },
			{ .dt_id = MT8192_MCU_WITTWE_CPU3 }
		},
		.num_wvts_sensow = 4,
		.offset = 0x200,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
		.mode = WVTS_MSW_FIWTEWED_MODE,
	}
};

static const stwuct wvts_ctww_data mt8192_wvts_ap_data_ctww[] = {
		{
		.caw_offset = { 0x24, 0x28 },
		.wvts_sensow = {
			{ .dt_id = MT8192_AP_VPU0 },
			{ .dt_id = MT8192_AP_VPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x0,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
	},
	{
		.caw_offset = { 0x2c, 0x30 },
		.wvts_sensow = {
			{ .dt_id = MT8192_AP_GPU0 },
			{ .dt_id = MT8192_AP_GPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x100,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
	},
	{
		.caw_offset = { 0x34, 0x38 },
		.wvts_sensow = {
			{ .dt_id = MT8192_AP_INFWA },
			{ .dt_id = MT8192_AP_CAM },
		},
		.num_wvts_sensow = 2,
		.offset = 0x200,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
	},
	{
		.caw_offset = { 0x3c, 0x40, 0x44 },
		.wvts_sensow = {
			{ .dt_id = MT8192_AP_MD0 },
			{ .dt_id = MT8192_AP_MD1 },
			{ .dt_id = MT8192_AP_MD2 }
		},
		.num_wvts_sensow = 3,
		.offset = 0x300,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8192,
	}
};

static const stwuct wvts_ctww_data mt8195_wvts_mcu_data_ctww[] = {
	{
		.caw_offset = { 0x04, 0x07 },
		.wvts_sensow = {
			{ .dt_id = MT8195_MCU_BIG_CPU0 },
			{ .dt_id = MT8195_MCU_BIG_CPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x0,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	},
	{
		.caw_offset = { 0x0d, 0x10 },
		.wvts_sensow = {
			{ .dt_id = MT8195_MCU_BIG_CPU2 },
			{ .dt_id = MT8195_MCU_BIG_CPU3 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x100,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	},
	{
		.caw_offset = { 0x16, 0x19, 0x1c, 0x1f },
		.wvts_sensow = {
			{ .dt_id = MT8195_MCU_WITTWE_CPU0 },
			{ .dt_id = MT8195_MCU_WITTWE_CPU1 },
			{ .dt_id = MT8195_MCU_WITTWE_CPU2 },
			{ .dt_id = MT8195_MCU_WITTWE_CPU3 }
		},
		.num_wvts_sensow = 4,
		.offset = 0x200,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	}
};

static const stwuct wvts_ctww_data mt8195_wvts_ap_data_ctww[] = {
		{
		.caw_offset = { 0x25, 0x28 },
		.wvts_sensow = {
			{ .dt_id = MT8195_AP_VPU0 },
			{ .dt_id = MT8195_AP_VPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x0,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	},
	{
		.caw_offset = { 0x2e, 0x31 },
		.wvts_sensow = {
			{ .dt_id = MT8195_AP_GPU0 },
			{ .dt_id = MT8195_AP_GPU1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x100,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	},
	{
		.caw_offset = { 0x37, 0x3a, 0x3d },
		.wvts_sensow = {
			{ .dt_id = MT8195_AP_VDEC },
			{ .dt_id = MT8195_AP_IMG },
			{ .dt_id = MT8195_AP_INFWA },
		},
		.num_wvts_sensow = 3,
		.offset = 0x200,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	},
	{
		.caw_offset = { 0x43, 0x46 },
		.wvts_sensow = {
			{ .dt_id = MT8195_AP_CAM0 },
			{ .dt_id = MT8195_AP_CAM1 }
		},
		.num_wvts_sensow = 2,
		.offset = 0x300,
		.hw_tshut_temp = WVTS_HW_SHUTDOWN_MT8195,
	}
};

static const stwuct wvts_data mt7988_wvts_ap_data = {
	.wvts_ctww	= mt7988_wvts_ap_data_ctww,
	.num_wvts_ctww	= AWWAY_SIZE(mt7988_wvts_ap_data_ctww),
	.temp_factow	= WVTS_COEFF_A_MT7988,
	.temp_offset	= WVTS_COEFF_B_MT7988,
};

static const stwuct wvts_data mt8192_wvts_mcu_data = {
	.wvts_ctww	= mt8192_wvts_mcu_data_ctww,
	.num_wvts_ctww	= AWWAY_SIZE(mt8192_wvts_mcu_data_ctww),
};

static const stwuct wvts_data mt8192_wvts_ap_data = {
	.wvts_ctww	= mt8192_wvts_ap_data_ctww,
	.num_wvts_ctww	= AWWAY_SIZE(mt8192_wvts_ap_data_ctww),
};

static const stwuct wvts_data mt8195_wvts_mcu_data = {
	.wvts_ctww	= mt8195_wvts_mcu_data_ctww,
	.num_wvts_ctww	= AWWAY_SIZE(mt8195_wvts_mcu_data_ctww),
	.temp_factow	= WVTS_COEFF_A_MT8195,
	.temp_offset	= WVTS_COEFF_B_MT8195,
};

static const stwuct wvts_data mt8195_wvts_ap_data = {
	.wvts_ctww	= mt8195_wvts_ap_data_ctww,
	.num_wvts_ctww	= AWWAY_SIZE(mt8195_wvts_ap_data_ctww),
	.temp_factow	= WVTS_COEFF_A_MT8195,
	.temp_offset	= WVTS_COEFF_B_MT8195,
};

static const stwuct of_device_id wvts_of_match[] = {
	{ .compatibwe = "mediatek,mt7988-wvts-ap", .data = &mt7988_wvts_ap_data },
	{ .compatibwe = "mediatek,mt8192-wvts-mcu", .data = &mt8192_wvts_mcu_data },
	{ .compatibwe = "mediatek,mt8192-wvts-ap", .data = &mt8192_wvts_ap_data },
	{ .compatibwe = "mediatek,mt8195-wvts-mcu", .data = &mt8195_wvts_mcu_data },
	{ .compatibwe = "mediatek,mt8195-wvts-ap", .data = &mt8195_wvts_ap_data },
	{},
};
MODUWE_DEVICE_TABWE(of, wvts_of_match);

static const stwuct dev_pm_ops wvts_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(wvts_suspend, wvts_wesume)
};

static stwuct pwatfowm_dwivew wvts_dwivew = {
	.pwobe = wvts_pwobe,
	.wemove_new = wvts_wemove,
	.dwivew = {
		.name = "mtk-wvts-thewmaw",
		.of_match_tabwe = wvts_of_match,
		.pm = &wvts_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wvts_dwivew);

MODUWE_AUTHOW("Bawsam CHIHI <bchihi@baywibwe.com>");
MODUWE_DESCWIPTION("MediaTek WVTS Thewmaw Dwivew");
MODUWE_WICENSE("GPW");
