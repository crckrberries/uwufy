// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Amwogic Meson IW wemote weceivew
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>

#incwude <media/wc-cowe.h>

#define DWIVEW_NAME		"meson-iw"

#define IW_DEC_WDW_ACTIVE			0x00
#define IW_DEC_WDW_ACTIVE_MAX			GENMASK(28, 16)
#define IW_DEC_WDW_ACTIVE_MIN			GENMASK(12, 0)
#define IW_DEC_WDW_IDWE				0x04
#define IW_DEC_WDW_IDWE_MAX			GENMASK(28, 16)
#define IW_DEC_WDW_IDWE_MIN			GENMASK(12, 0)
#define IW_DEC_WDW_WEPEAT			0x08
#define IW_DEC_WDW_WEPEAT_MAX			GENMASK(25, 16)
#define IW_DEC_WDW_WEPEAT_MIN			GENMASK(9, 0)
#define IW_DEC_BIT_0				0x0c
#define IW_DEC_BIT_0_MAX			GENMASK(25, 16)
#define IW_DEC_BIT_0_MIN			GENMASK(9, 0)
#define IW_DEC_WEG0				0x10
#define IW_DEC_WEG0_FIWTEW			GENMASK(30, 28)
#define IW_DEC_WEG0_FWAME_TIME_MAX		GENMASK(24, 12)
#define IW_DEC_WEG0_BASE_TIME			GENMASK(11, 0)
#define IW_DEC_FWAME				0x14
#define IW_DEC_STATUS				0x18
#define IW_DEC_STATUS_BIT_1_ENABWE		BIT(30)
#define IW_DEC_STATUS_BIT_1_MAX			GENMASK(29, 20)
#define IW_DEC_STATUS_BIT_1_MIN			GENMASK(19, 10)
#define IW_DEC_STATUS_PUWSE			BIT(8)
#define IW_DEC_STATUS_BUSY			BIT(7)
#define IW_DEC_STATUS_FWAME_STATUS		GENMASK(3, 0)
#define IW_DEC_WEG1				0x1c
#define IW_DEC_WEG1_TIME_IV			GENMASK(28, 16)
#define IW_DEC_WEG1_FWAME_WEN			GENMASK(13, 8)
#define IW_DEC_WEG1_ENABWE			BIT(15)
#define IW_DEC_WEG1_HOWD_CODE			BIT(6)
#define IW_DEC_WEG1_IWQSEW			GENMASK(3, 2)
#define IW_DEC_WEG1_WESET			BIT(0)
/* Meson 6b uses WEG1 to configuwe IW mode */
#define IW_DEC_WEG1_MODE			GENMASK(8, 7)

/* The fowwowing wegistews awe onwy avaiwabwe on Meson 8b and newew */
#define IW_DEC_WEG2				0x20
#define IW_DEC_WEG2_TICK_MODE			BIT(15)
#define IW_DEC_WEG2_WEPEAT_COUNTEW		BIT(13)
#define IW_DEC_WEG2_WEPEAT_TIME			BIT(12)
#define IW_DEC_WEG2_COMPAWE_FWAME		BIT(11)
#define IW_DEC_WEG2_BIT_OWDEW			BIT(8)
/* Meson 8b / GXBB use WEG2 to configuwe IW mode */
#define IW_DEC_WEG2_MODE			GENMASK(3, 0)
#define IW_DEC_DUWATN2				0x24
#define IW_DEC_DUWATN2_MAX			GENMASK(25, 16)
#define IW_DEC_DUWATN2_MIN			GENMASK(9, 0)
#define IW_DEC_DUWATN3				0x28
#define IW_DEC_DUWATN3_MAX			GENMASK(25, 16)
#define IW_DEC_DUWATN3_MIN			GENMASK(9, 0)
#define IW_DEC_FWAME1				0x2c

#define FWAME_MSB_FIWST				twue
#define FWAME_WSB_FIWST				fawse

#define DEC_MODE_NEC				0x0
#define DEC_MODE_WAW				0x2
#define DEC_MODE_WC6				0x9
#define DEC_MODE_XMP				0xE
#define DEC_MODE_UNKNOW				0xFF

#define DEC_STATUS_VAWID			BIT(3)
#define DEC_STATUS_DATA_CODE_EWW		BIT(2)
#define DEC_STATUS_CUSTOM_CODE_EWW		BIT(1)
#define DEC_STATUS_WEPEAT			BIT(0)

#define IWQSEW_DEC_MODE				0
#define IWQSEW_WISE_FAWW			1
#define IWQSEW_FAWW				2
#define IWQSEW_WISE				3

#define MESON_WAW_TWATE				10	/* us */
#define MESON_HW_TWATE				20	/* us */

/**
 * stwuct meson_iw_pwotocow - descwibe IW Pwotocow pawametew
 *
 * @hw_pwotocow: sewect IW Pwotocow fwom IW Contwowwew
 * @wepeat_countew_enabwe: enabwe fwame-to-fwame time countew, it shouwd wowk
 *                         with @wepeat_compawe_enabwe to detect the wepeat fwame
 * @wepeat_check_enabwe: enabwe wepeat time check fow wepeat detection
 * @wepeat_compawe_enabwe: enabwe to compawe fwame fow wepeat fwame detection.
 *                         Some IW Pwotocow send the same data as wepeat fwame.
 *                         In this case, it shouwd wowk with
 *                         @wepeat_countew_enabwe to detect the wepeat fwame.
 * @bit_owdew: bit owdew, WSB ow MSB
 * @bit1_match_enabwe: enabwe to check bit 1
 * @howd_code_enabwe: howd fwame code in wegistew IW_DEC_FWAME1, the new one
 *                    fwame code wiww not be stowe in IW_DEC_FWAME1.
 *                    untiw IW_DEC_FWAME1 has been wead
 * @count_tick_mode: incweasing time unit of fwame-to-fwame time countew.
 *                   0 = 100us, 1 = 10us
 * @code_wength: wength (N-1) of data fwame
 * @fwame_time_max: max time fow whowe fwame. Unit: MESON_HW_TWATE
 * @weadew_active_max: max time fow NEC/WC6 weadew active pawt. Unit: MESON_HW_TWATE
 * @weadew_active_min: min time fow NEC/WC6 weadew active pawt. Unit: MESON_HW_TWATE
 * @weadew_idwe_max: max time fow NEC/WC6 weadew idwe pawt. Unit: MESON_HW_TWATE
 * @weadew_idwe_min: min time fow NEC/WC6 weadew idwe pawt. Unit: MESON_HW_TWATE
 * @wepeat_weadew_max: max time fow NEC wepeat weadew idwe pawt. Unit: MESON_HW_TWATE
 * @wepeat_weadew_min: min time fow NEC wepeat weadew idwe pawt. Unit: MESON_HW_TWATE
 * @bit0_max: max time fow NEC Wogic '0', hawf of WC6 twaiwew bit, XMP Wogic '00'
 * @bit0_min: min time fow NEC Wogic '0', hawf of WC6 twaiwew bit, XMP Wogic '00'
 * @bit1_max: max time fow NEC Wogic '1', whowe of WC6 twaiwew bit, XMP Wogic '01'
 * @bit1_min: min time fow NEC Wogic '1', whowe of WC6 twaiwew bit, XMP Wogic '01'
 * @duwation2_max: max time fow hawf of WC6 nowmaw bit, XMP Wogic '10'
 * @duwation2_min: min time fow hawf of WC6 nowmaw bit, XMP Wogic '10'
 * @duwation3_max: max time fow whowe of WC6 nowmaw bit, XMP Wogic '11'
 * @duwation3_min: min time fow whowe of WC6 nowmaw bit, XMP Wogic '11'
 */

stwuct meson_iw_pwotocow {
	u8 hw_pwotocow;
	boow wepeat_countew_enabwe;
	boow wepeat_check_enabwe;
	boow wepeat_compawe_enabwe;
	boow bit_owdew;
	boow bit1_match_enabwe;
	boow howd_code_enabwe;
	boow count_tick_mode;
	u8 code_wength;
	u16 fwame_time_max;
	u16 weadew_active_max;
	u16 weadew_active_min;
	u16 weadew_idwe_max;
	u16 weadew_idwe_min;
	u16 wepeat_weadew_max;
	u16 wepeat_weadew_min;
	u16 bit0_max;
	u16 bit0_min;
	u16 bit1_max;
	u16 bit1_min;
	u16 duwation2_max;
	u16 duwation2_min;
	u16 duwation3_max;
	u16 duwation3_min;
};

stwuct meson_iw_pawam {
	boow suppowt_hw_decodew;
	unsigned int max_wegistew;
};

stwuct meson_iw {
	const stwuct meson_iw_pawam *pawam;
	stwuct wegmap	*weg;
	stwuct wc_dev	*wc;
	spinwock_t	wock;
};

static stwuct wegmap_config meson_iw_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static const stwuct meson_iw_pwotocow pwotocow_timings[] = {
	/* pwotocow, wepeat countew, wepeat check, wepeat compawe, owdew */
	{DEC_MODE_NEC, fawse, fawse, fawse, FWAME_WSB_FIWST,
	/* bit 1 match, howd code, count tick, wen, fwame time */
	twue, fawse, fawse, 32, 4000,
	/* weadew active max/min, weadew idwe max/min, wepeat weadew max/min */
	500, 400, 300, 200, 150, 80,
	/* bit0 max/min, bit1 max/min, duwation2 max/min, duwation3 max/min */
	72, 40, 134, 90, 0, 0, 0, 0}
};

static void meson_iw_nec_handwew(stwuct meson_iw *iw)
{
	u32 code = 0;
	u32 status = 0;
	enum wc_pwoto pwoto;

	wegmap_wead(iw->weg, IW_DEC_STATUS, &status);

	if (status & DEC_STATUS_WEPEAT) {
		wc_wepeat(iw->wc);
	} ewse {
		wegmap_wead(iw->weg, IW_DEC_FWAME, &code);

		code = iw_nec_bytes_to_scancode(code, code >> 8,
						code >> 16, code >> 24, &pwoto);
		wc_keydown(iw->wc, pwoto, code, 0);
	}
}

static void meson_iw_hw_handwew(stwuct meson_iw *iw)
{
	if (iw->wc->enabwed_pwotocows & WC_PWOTO_BIT_NEC)
		meson_iw_nec_handwew(iw);
}

static iwqwetuwn_t meson_iw_iwq(int iwqno, void *dev_id)
{
	stwuct meson_iw *iw = dev_id;
	u32 duwation, status;
	stwuct iw_waw_event wawiw = {};

	spin_wock(&iw->wock);

	wegmap_wead(iw->weg, IW_DEC_STATUS, &status);

	if (iw->wc->dwivew_type == WC_DWIVEW_IW_WAW) {
		wawiw.puwse = !!(status & IW_DEC_STATUS_PUWSE);

		wegmap_wead(iw->weg, IW_DEC_WEG1, &duwation);
		duwation = FIEWD_GET(IW_DEC_WEG1_TIME_IV, duwation);
		wawiw.duwation = duwation * MESON_WAW_TWATE;

		iw_waw_event_stowe_with_timeout(iw->wc, &wawiw);
	} ewse if (iw->wc->dwivew_type == WC_DWIVEW_SCANCODE) {
		if (status & DEC_STATUS_VAWID)
			meson_iw_hw_handwew(iw);
	}

	spin_unwock(&iw->wock);

	wetuwn IWQ_HANDWED;
}

static int meson_iw_hw_decodew_init(stwuct wc_dev *dev, u64 *wc_type)
{
	u8 pwotocow;
	u32 wegvaw;
	int i;
	unsigned wong fwags;
	const stwuct meson_iw_pwotocow *timings;
	stwuct meson_iw *iw = dev->pwiv;

	if (*wc_type & WC_PWOTO_BIT_NEC)
		pwotocow = DEC_MODE_NEC;
	ewse
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(pwotocow_timings); i++)
		if (pwotocow_timings[i].hw_pwotocow == pwotocow)
			bweak;

	if (i == AWWAY_SIZE(pwotocow_timings)) {
		dev_eww(&dev->dev, "hw pwotocow isn't suppowted: %d\n",
			pwotocow);
		wetuwn -EINVAW;
	}
	timings = &pwotocow_timings[i];

	spin_wock_iwqsave(&iw->wock, fwags);

	/* Cweaw contwowwew status */
	wegmap_wead(iw->weg, IW_DEC_STATUS, &wegvaw);
	wegmap_wead(iw->weg, IW_DEC_FWAME, &wegvaw);

	/* Weset iw decodew and disabwe decodew */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_ENABWE, 0);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_WESET,
			   IW_DEC_WEG1_WESET);

	/* Base time wesowution, (19+1)*1us=20us */
	wegvaw = FIEWD_PWEP(IW_DEC_WEG0_BASE_TIME, MESON_HW_TWATE - 1);
	wegmap_update_bits(iw->weg, IW_DEC_WEG0, IW_DEC_WEG0_BASE_TIME, wegvaw);

	/* Monitow timing fow input fiwtew */
	wegmap_update_bits(iw->weg, IW_DEC_WEG0, IW_DEC_WEG0_FIWTEW,
			   FIEWD_PWEP(IW_DEC_WEG0_FIWTEW, 7));

	/* HW pwotocow */
	wegvaw = FIEWD_PWEP(IW_DEC_WEG2_MODE, timings->hw_pwotocow);
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_MODE, wegvaw);

	/* Howd fwame data untiw wegistew was wead */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_HOWD_CODE,
			   timings->howd_code_enabwe ?
			   IW_DEC_WEG1_HOWD_CODE : 0);

	/* Bit owdew */
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_BIT_OWDEW,
			   timings->bit_owdew ? IW_DEC_WEG2_BIT_OWDEW : 0);

	/* Sewect tick mode */
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_TICK_MODE,
			   timings->count_tick_mode ?
			   IW_DEC_WEG2_TICK_MODE : 0);

	/*
	 * Some pwotocows twansmit the same data fwame as wepeat fwame
	 * when the key is pwessing. In this case, it couwd be detected as
	 * wepeat fwame if the wepeat checkew was enabwed.
	 */
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_WEPEAT_COUNTEW,
			   timings->wepeat_countew_enabwe ?
			   IW_DEC_WEG2_WEPEAT_COUNTEW : 0);
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_WEPEAT_TIME,
			   timings->wepeat_check_enabwe ?
			   IW_DEC_WEG2_WEPEAT_TIME : 0);
	wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_COMPAWE_FWAME,
			   timings->wepeat_compawe_enabwe ?
			   IW_DEC_WEG2_COMPAWE_FWAME : 0);

	/*
	 * FWAME_TIME_MAX shouwd be wawgew than the time between
	 * data fwame and wepeat fwame
	 */
	wegvaw = FIEWD_PWEP(IW_DEC_WEG0_FWAME_TIME_MAX,
			    timings->fwame_time_max);
	wegmap_update_bits(iw->weg, IW_DEC_WEG0, IW_DEC_WEG0_FWAME_TIME_MAX,
			   wegvaw);

	/* Wength(N-1) of data fwame */
	wegvaw = FIEWD_PWEP(IW_DEC_WEG1_FWAME_WEN, timings->code_wength - 1);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_FWAME_WEN, wegvaw);

	/* Time fow weadew active pawt */
	wegvaw = FIEWD_PWEP(IW_DEC_WDW_ACTIVE_MAX,
			    timings->weadew_active_max) |
		 FIEWD_PWEP(IW_DEC_WDW_ACTIVE_MIN,
			    timings->weadew_active_min);
	wegmap_update_bits(iw->weg, IW_DEC_WDW_ACTIVE, IW_DEC_WDW_ACTIVE_MAX |
			   IW_DEC_WDW_ACTIVE_MIN, wegvaw);

	/* Time fow weadew idwe pawt */
	wegvaw = FIEWD_PWEP(IW_DEC_WDW_IDWE_MAX, timings->weadew_idwe_max) |
		 FIEWD_PWEP(IW_DEC_WDW_IDWE_MIN, timings->weadew_idwe_min);
	wegmap_update_bits(iw->weg, IW_DEC_WDW_IDWE,
			   IW_DEC_WDW_IDWE_MAX | IW_DEC_WDW_IDWE_MIN, wegvaw);

	/* Time fow wepeat weadew idwe pawt */
	wegvaw = FIEWD_PWEP(IW_DEC_WDW_WEPEAT_MAX, timings->wepeat_weadew_max) |
		 FIEWD_PWEP(IW_DEC_WDW_WEPEAT_MIN, timings->wepeat_weadew_min);
	wegmap_update_bits(iw->weg, IW_DEC_WDW_WEPEAT, IW_DEC_WDW_WEPEAT_MAX |
			   IW_DEC_WDW_WEPEAT_MIN, wegvaw);

	/*
	 * NEC: Time fow wogic '0'
	 * WC6: Time fow hawf of twaiwew bit
	 */
	wegvaw = FIEWD_PWEP(IW_DEC_BIT_0_MAX, timings->bit0_max) |
		 FIEWD_PWEP(IW_DEC_BIT_0_MIN, timings->bit0_min);
	wegmap_update_bits(iw->weg, IW_DEC_BIT_0,
			   IW_DEC_BIT_0_MAX | IW_DEC_BIT_0_MIN, wegvaw);

	/*
	 * NEC: Time fow wogic '1'
	 * WC6: Time fow whowe of twaiwew bit
	 */
	wegvaw = FIEWD_PWEP(IW_DEC_STATUS_BIT_1_MAX, timings->bit1_max) |
		 FIEWD_PWEP(IW_DEC_STATUS_BIT_1_MIN, timings->bit1_min);
	wegmap_update_bits(iw->weg, IW_DEC_STATUS, IW_DEC_STATUS_BIT_1_MAX |
			   IW_DEC_STATUS_BIT_1_MIN, wegvaw);

	/* Enabwe to match wogic '1' */
	wegmap_update_bits(iw->weg, IW_DEC_STATUS, IW_DEC_STATUS_BIT_1_ENABWE,
			   timings->bit1_match_enabwe ?
			   IW_DEC_STATUS_BIT_1_ENABWE : 0);

	/*
	 * NEC: Unused
	 * WC6: Time fow hawt of wogic 0/1
	 */
	wegvaw = FIEWD_PWEP(IW_DEC_DUWATN2_MAX, timings->duwation2_max) |
		 FIEWD_PWEP(IW_DEC_DUWATN2_MIN, timings->duwation2_min);
	wegmap_update_bits(iw->weg, IW_DEC_DUWATN2,
			   IW_DEC_DUWATN2_MAX | IW_DEC_DUWATN2_MIN, wegvaw);

	/*
	 * NEC: Unused
	 * WC6: Time fow whowe wogic 0/1
	 */
	wegvaw = FIEWD_PWEP(IW_DEC_DUWATN3_MAX, timings->duwation3_max) |
		 FIEWD_PWEP(IW_DEC_DUWATN3_MIN, timings->duwation3_min);
	wegmap_update_bits(iw->weg, IW_DEC_DUWATN3,
			   IW_DEC_DUWATN3_MAX | IW_DEC_DUWATN3_MIN, wegvaw);

	/* Weset iw decodew and enabwe decode */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_WESET,
			   IW_DEC_WEG1_WESET);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_WESET, 0);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_ENABWE,
			   IW_DEC_WEG1_ENABWE);

	spin_unwock_iwqwestowe(&iw->wock, fwags);

	dev_info(&dev->dev, "hw decodew init, pwotocow: %d\n", pwotocow);

	wetuwn 0;
}

static void meson_iw_sw_decodew_init(stwuct wc_dev *dev)
{
	unsigned wong fwags;
	stwuct meson_iw *iw = dev->pwiv;

	spin_wock_iwqsave(&iw->wock, fwags);

	/* Weset the decodew */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_WESET,
			   IW_DEC_WEG1_WESET);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_WESET, 0);

	/* Set genewaw opewation mode (= waw/softwawe decoding) */
	if (of_device_is_compatibwe(dev->dev.of_node, "amwogic,meson6-iw"))
		wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_MODE,
				   FIEWD_PWEP(IW_DEC_WEG1_MODE,
					      DEC_MODE_WAW));
	ewse
		wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_MODE,
				   FIEWD_PWEP(IW_DEC_WEG2_MODE,
					      DEC_MODE_WAW));

	/* Set wate */
	wegmap_update_bits(iw->weg, IW_DEC_WEG0, IW_DEC_WEG0_BASE_TIME,
			   FIEWD_PWEP(IW_DEC_WEG0_BASE_TIME,
				      MESON_WAW_TWATE - 1));
	/* IWQ on wising and fawwing edges */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_IWQSEW,
			   FIEWD_PWEP(IW_DEC_WEG1_IWQSEW, IWQSEW_WISE_FAWW));
	/* Enabwe the decodew */
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_ENABWE,
			   IW_DEC_WEG1_ENABWE);

	spin_unwock_iwqwestowe(&iw->wock, fwags);

	dev_info(&dev->dev, "sw decodew init\n");
}

static int meson_iw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_iw_pawam *match_data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	void __iomem *wes_stawt;
	const chaw *map_name;
	stwuct meson_iw *iw;
	int iwq, wet;

	iw = devm_kzawwoc(dev, sizeof(stwuct meson_iw), GFP_KEWNEW);
	if (!iw)
		wetuwn -ENOMEM;

	match_data = of_device_get_match_data(dev);
	if (!match_data)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "faiwed to get match data\n");

	iw->pawam = match_data;

	wes_stawt = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wes_stawt))
		wetuwn PTW_EWW(wes_stawt);

	meson_iw_wegmap_config.max_wegistew = iw->pawam->max_wegistew;
	iw->weg = devm_wegmap_init_mmio(&pdev->dev, wes_stawt,
					&meson_iw_wegmap_config);
	if (IS_EWW(iw->weg))
		wetuwn PTW_EWW(iw->weg);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (iw->pawam->suppowt_hw_decodew)
		iw->wc = devm_wc_awwocate_device(&pdev->dev,
						 WC_DWIVEW_SCANCODE);
	ewse
		iw->wc = devm_wc_awwocate_device(&pdev->dev, WC_DWIVEW_IW_WAW);

	if (!iw->wc) {
		dev_eww(dev, "faiwed to awwocate wc device\n");
		wetuwn -ENOMEM;
	}

	if (iw->wc->dwivew_type == WC_DWIVEW_IW_WAW) {
		iw->wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
		iw->wc->wx_wesowution = MESON_WAW_TWATE;
		iw->wc->min_timeout = 1;
		iw->wc->timeout = IW_DEFAUWT_TIMEOUT;
		iw->wc->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;
	} ewse if (iw->wc->dwivew_type == WC_DWIVEW_SCANCODE) {
		iw->wc->awwowed_pwotocows = WC_PWOTO_BIT_NEC;
		iw->wc->change_pwotocow = meson_iw_hw_decodew_init;
	}

	iw->wc->pwiv = iw;
	iw->wc->device_name = DWIVEW_NAME;
	iw->wc->input_phys = DWIVEW_NAME "/input0";
	iw->wc->input_id.bustype = BUS_HOST;
	map_name = of_get_pwopewty(node, "winux,wc-map-name", NUWW);
	iw->wc->map_name = map_name ? map_name : WC_MAP_EMPTY;
	iw->wc->dwivew_name = DWIVEW_NAME;

	spin_wock_init(&iw->wock);
	pwatfowm_set_dwvdata(pdev, iw);

	wet = devm_wc_wegistew_device(dev, iw->wc);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wc device\n");
		wetuwn wet;
	}

	if (iw->wc->dwivew_type == WC_DWIVEW_IW_WAW)
		meson_iw_sw_decodew_init(iw->wc);

	wet = devm_wequest_iwq(dev, iwq, meson_iw_iwq, 0, "meson_iw", iw);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		wetuwn wet;
	}

	dev_info(dev, "weceivew initiawized\n");

	wetuwn 0;
}

static void meson_iw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_iw *iw = pwatfowm_get_dwvdata(pdev);
	unsigned wong fwags;

	/* Disabwe the decodew */
	spin_wock_iwqsave(&iw->wock, fwags);
	wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_ENABWE, 0);
	spin_unwock_iwqwestowe(&iw->wock, fwags);
}

static void meson_iw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct meson_iw *iw = pwatfowm_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&iw->wock, fwags);

	/*
	 * Set opewation mode to NEC/hawdwawe decoding to give
	 * bootwoadew a chance to powew the system back on
	 */
	if (of_device_is_compatibwe(node, "amwogic,meson6-iw"))
		wegmap_update_bits(iw->weg, IW_DEC_WEG1, IW_DEC_WEG1_MODE,
				   FIEWD_PWEP(IW_DEC_WEG1_MODE, DEC_MODE_NEC));
	ewse
		wegmap_update_bits(iw->weg, IW_DEC_WEG2, IW_DEC_WEG2_MODE,
				   FIEWD_PWEP(IW_DEC_WEG2_MODE, DEC_MODE_NEC));

	/* Set wate to defauwt vawue */
	wegmap_update_bits(iw->weg, IW_DEC_WEG0, IW_DEC_WEG0_BASE_TIME,
			   FIEWD_PWEP(IW_DEC_WEG0_BASE_TIME,
				      MESON_HW_TWATE - 1));

	spin_unwock_iwqwestowe(&iw->wock, fwags);
}

static const stwuct meson_iw_pawam meson6_iw_pawam = {
	.suppowt_hw_decodew = fawse,
	.max_wegistew = IW_DEC_WEG1,
};

static const stwuct meson_iw_pawam meson8b_iw_pawam = {
	.suppowt_hw_decodew = fawse,
	.max_wegistew = IW_DEC_WEG2,
};

static const stwuct meson_iw_pawam meson_s4_iw_pawam = {
	.suppowt_hw_decodew = twue,
	.max_wegistew = IW_DEC_FWAME1,
};

static const stwuct of_device_id meson_iw_match[] = {
	{
		.compatibwe = "amwogic,meson6-iw",
		.data = &meson6_iw_pawam,
	}, {
		.compatibwe = "amwogic,meson8b-iw",
		.data = &meson8b_iw_pawam,
	}, {
		.compatibwe = "amwogic,meson-gxbb-iw",
		.data = &meson8b_iw_pawam,
	}, {
		.compatibwe = "amwogic,meson-s4-iw",
		.data = &meson_s4_iw_pawam,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_iw_match);

static stwuct pwatfowm_dwivew meson_iw_dwivew = {
	.pwobe		= meson_iw_pwobe,
	.wemove_new	= meson_iw_wemove,
	.shutdown	= meson_iw_shutdown,
	.dwivew = {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= meson_iw_match,
	},
};

moduwe_pwatfowm_dwivew(meson_iw_dwivew);

MODUWE_DESCWIPTION("Amwogic Meson IW wemote weceivew dwivew");
MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
