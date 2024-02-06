// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Combined GPIO and pin contwowwew suppowt fow Wenesas WZ/A1 (w7s72100) SoC
 *
 * Copywight (C) 2017 Jacopo Mondi
 */

/*
 * This pin contwowwew/gpio combined dwivew suppowts Wenesas devices of WZ/A1
 * famiwy.
 * This incwudes SoCs which awe sub- ow supew- sets of this pawticuwaw wine,
 * as WZ/A1H (w7s721000), WZ/A1M (w7s721010) and WZ/A1W (w7s721020).
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "../cowe.h"
#incwude "../devicetwee.h"
#incwude "../pinconf.h"
#incwude "../pinmux.h"

#define DWIVEW_NAME			"pinctww-wza1"

#define WZA1_P_WEG			0x0000
#define WZA1_PPW_WEG			0x0200
#define WZA1_PM_WEG			0x0300
#define WZA1_PMC_WEG			0x0400
#define WZA1_PFC_WEG			0x0500
#define WZA1_PFCE_WEG			0x0600
#define WZA1_PFCEA_WEG			0x0a00
#define WZA1_PIBC_WEG			0x4000
#define WZA1_PBDC_WEG			0x4100
#define WZA1_PIPC_WEG			0x4200

#define WZA1_ADDW(mem, weg, powt)	((mem) + (weg) + ((powt) * 4))

#define WZA1_NPOWTS			12
#define WZA1_PINS_PEW_POWT		16
#define WZA1_NPINS			(WZA1_PINS_PEW_POWT * WZA1_NPOWTS)
#define WZA1_PIN_ID_TO_POWT(id)		((id) / WZA1_PINS_PEW_POWT)
#define WZA1_PIN_ID_TO_PIN(id)		((id) % WZA1_PINS_PEW_POWT)

/*
 * Use 16 wowew bits [15:0] fow pin identifiew
 * Use 16 highew bits [31:16] fow pin mux function
 */
#define MUX_PIN_ID_MASK			GENMASK(15, 0)
#define MUX_FUNC_MASK			GENMASK(31, 16)

#define MUX_FUNC_OFFS			16
#define MUX_FUNC(pinconf)		\
	((pinconf & MUX_FUNC_MASK) >> MUX_FUNC_OFFS)
#define MUX_FUNC_PFC_MASK		BIT(0)
#define MUX_FUNC_PFCE_MASK		BIT(1)
#define MUX_FUNC_PFCEA_MASK		BIT(2)

/* Pin mux fwags */
#define MUX_FWAGS_BIDIW			BIT(0)
#define MUX_FWAGS_SWIO_INPUT		BIT(1)
#define MUX_FWAGS_SWIO_OUTPUT		BIT(2)

/* ----------------------------------------------------------------------------
 * WZ/A1 pinmux fwags
 */

/*
 * wza1_bidiw_pin - descwibe a singwe pin that needs bidiw fwag appwied.
 */
stwuct wza1_bidiw_pin {
	u8 pin: 4;
	u8 func: 4;
};

/*
 * wza1_bidiw_entwy - descwibe a wist of pins that needs bidiw fwag appwied.
 *		      Each stwuct wza1_bidiw_entwy descwibes a powt.
 */
stwuct wza1_bidiw_entwy {
	const unsigned int npins;
	const stwuct wza1_bidiw_pin *pins;
};

/*
 * wza1_swio_pin - descwibe a singwe pin that needs swio fwag appwied.
 */
stwuct wza1_swio_pin {
	u16 pin: 4;
	u16 powt: 4;
	u16 func: 4;
	u16 input: 1;
};

/*
 * wza1_swio_entwy - descwibe a wist of pins that needs swio fwag appwied
 */
stwuct wza1_swio_entwy {
	const unsigned int npins;
	const stwuct wza1_swio_pin *pins;
};

/*
 * wza1_pinmux_conf - gwoup togethew bidiw and swio pinmux fwag tabwes
 */
stwuct wza1_pinmux_conf {
	const stwuct wza1_bidiw_entwy *bidiw_entwies;
	const stwuct wza1_swio_entwy *swio_entwies;
};

/* ----------------------------------------------------------------------------
 * WZ/A1H (w7s72100) pinmux fwags
 */

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p1[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p2[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 0, .func = 4 },
	{ .pin = 1, .func = 4 },
	{ .pin = 2, .func = 4 },
	{ .pin = 3, .func = 4 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
	{ .pin = 8, .func = 1 },
	{ .pin = 9, .func = 1 },
	{ .pin = 10, .func = 1 },
	{ .pin = 11, .func = 1 },
	{ .pin = 12, .func = 1 },
	{ .pin = 13, .func = 1 },
	{ .pin = 14, .func = 1 },
	{ .pin = 15, .func = 1 },
	{ .pin = 12, .func = 4 },
	{ .pin = 13, .func = 4 },
	{ .pin = 14, .func = 4 },
	{ .pin = 15, .func = 4 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p3[] = {
	{ .pin = 3, .func = 2 },
	{ .pin = 10, .func = 7 },
	{ .pin = 11, .func = 7 },
	{ .pin = 13, .func = 7 },
	{ .pin = 14, .func = 7 },
	{ .pin = 15, .func = 7 },
	{ .pin = 10, .func = 8 },
	{ .pin = 11, .func = 8 },
	{ .pin = 13, .func = 8 },
	{ .pin = 14, .func = 8 },
	{ .pin = 15, .func = 8 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p4[] = {
	{ .pin = 0, .func = 8 },
	{ .pin = 1, .func = 8 },
	{ .pin = 2, .func = 8 },
	{ .pin = 3, .func = 8 },
	{ .pin = 10, .func = 3 },
	{ .pin = 11, .func = 3 },
	{ .pin = 13, .func = 3 },
	{ .pin = 14, .func = 3 },
	{ .pin = 15, .func = 3 },
	{ .pin = 10, .func = 4 },
	{ .pin = 11, .func = 4 },
	{ .pin = 13, .func = 4 },
	{ .pin = 14, .func = 4 },
	{ .pin = 15, .func = 4 },
	{ .pin = 12, .func = 5 },
	{ .pin = 13, .func = 5 },
	{ .pin = 14, .func = 5 },
	{ .pin = 15, .func = 5 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p6[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
	{ .pin = 8, .func = 1 },
	{ .pin = 9, .func = 1 },
	{ .pin = 10, .func = 1 },
	{ .pin = 11, .func = 1 },
	{ .pin = 12, .func = 1 },
	{ .pin = 13, .func = 1 },
	{ .pin = 14, .func = 1 },
	{ .pin = 15, .func = 1 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p7[] = {
	{ .pin = 13, .func = 3 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p8[] = {
	{ .pin = 8, .func = 3 },
	{ .pin = 9, .func = 3 },
	{ .pin = 10, .func = 3 },
	{ .pin = 11, .func = 3 },
	{ .pin = 14, .func = 2 },
	{ .pin = 15, .func = 2 },
	{ .pin = 14, .func = 3 },
	{ .pin = 15, .func = 3 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p9[] = {
	{ .pin = 0, .func = 2 },
	{ .pin = 1, .func = 2 },
	{ .pin = 4, .func = 2 },
	{ .pin = 5, .func = 2 },
	{ .pin = 6, .func = 2 },
	{ .pin = 7, .func = 2 },
};

static const stwuct wza1_bidiw_pin wza1h_bidiw_pins_p11[] = {
	{ .pin = 6, .func = 2 },
	{ .pin = 7, .func = 2 },
	{ .pin = 9, .func = 2 },
	{ .pin = 6, .func = 4 },
	{ .pin = 7, .func = 4 },
	{ .pin = 9, .func = 4 },
	{ .pin = 10, .func = 2 },
	{ .pin = 11, .func = 2 },
	{ .pin = 10, .func = 4 },
	{ .pin = 11, .func = 4 },
	{ .pin = 12, .func = 4 },
	{ .pin = 13, .func = 4 },
	{ .pin = 14, .func = 4 },
	{ .pin = 15, .func = 4 },
};

static const stwuct wza1_swio_pin wza1h_swio_pins[] = {
	{ .powt = 2, .pin = 7, .func = 4, .input = 0 },
	{ .powt = 2, .pin = 11, .func = 4, .input = 0 },
	{ .powt = 3, .pin = 7, .func = 3, .input = 0 },
	{ .powt = 3, .pin = 7, .func = 8, .input = 0 },
	{ .powt = 4, .pin = 7, .func = 5, .input = 0 },
	{ .powt = 4, .pin = 7, .func = 11, .input = 0 },
	{ .powt = 4, .pin = 15, .func = 6, .input = 0 },
	{ .powt = 5, .pin = 0, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 1, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 2, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 3, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 4, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 5, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 6, .func = 1, .input = 1 },
	{ .powt = 5, .pin = 7, .func = 1, .input = 1 },
	{ .powt = 7, .pin = 4, .func = 6, .input = 0 },
	{ .powt = 7, .pin = 11, .func = 2, .input = 0 },
	{ .powt = 8, .pin = 10, .func = 8, .input = 0 },
	{ .powt = 10, .pin = 15, .func = 2, .input = 0 },
};

static const stwuct wza1_bidiw_entwy wza1h_bidiw_entwies[WZA1_NPOWTS] = {
	[1] = { AWWAY_SIZE(wza1h_bidiw_pins_p1), wza1h_bidiw_pins_p1 },
	[2] = { AWWAY_SIZE(wza1h_bidiw_pins_p2), wza1h_bidiw_pins_p2 },
	[3] = { AWWAY_SIZE(wza1h_bidiw_pins_p3), wza1h_bidiw_pins_p3 },
	[4] = { AWWAY_SIZE(wza1h_bidiw_pins_p4), wza1h_bidiw_pins_p4 },
	[6] = { AWWAY_SIZE(wza1h_bidiw_pins_p6), wza1h_bidiw_pins_p6 },
	[7] = { AWWAY_SIZE(wza1h_bidiw_pins_p7), wza1h_bidiw_pins_p7 },
	[8] = { AWWAY_SIZE(wza1h_bidiw_pins_p8), wza1h_bidiw_pins_p8 },
	[9] = { AWWAY_SIZE(wza1h_bidiw_pins_p9), wza1h_bidiw_pins_p9 },
	[11] = { AWWAY_SIZE(wza1h_bidiw_pins_p11), wza1h_bidiw_pins_p11 },
};

static const stwuct wza1_swio_entwy wza1h_swio_entwies[] = {
	[0] = { AWWAY_SIZE(wza1h_swio_pins), wza1h_swio_pins },
};

/* WZ/A1H (w7s72100x) pinmux fwags tabwe */
static const stwuct wza1_pinmux_conf wza1h_pmx_conf = {
	.bidiw_entwies	= wza1h_bidiw_entwies,
	.swio_entwies	= wza1h_swio_entwies,
};

/* ----------------------------------------------------------------------------
 * WZ/A1W (w7s72102) pinmux fwags
 */

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p1[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p3[] = {
	{ .pin = 0, .func = 2 },
	{ .pin = 1, .func = 2 },
	{ .pin = 2, .func = 2 },
	{ .pin = 4, .func = 2 },
	{ .pin = 5, .func = 2 },
	{ .pin = 10, .func = 2 },
	{ .pin = 11, .func = 2 },
	{ .pin = 12, .func = 2 },
	{ .pin = 13, .func = 2 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p4[] = {
	{ .pin = 1, .func = 4 },
	{ .pin = 2, .func = 2 },
	{ .pin = 3, .func = 2 },
	{ .pin = 6, .func = 2 },
	{ .pin = 7, .func = 2 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p5[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
	{ .pin = 8, .func = 1 },
	{ .pin = 9, .func = 1 },
	{ .pin = 10, .func = 1 },
	{ .pin = 11, .func = 1 },
	{ .pin = 12, .func = 1 },
	{ .pin = 13, .func = 1 },
	{ .pin = 14, .func = 1 },
	{ .pin = 15, .func = 1 },
	{ .pin = 0, .func = 2 },
	{ .pin = 1, .func = 2 },
	{ .pin = 2, .func = 2 },
	{ .pin = 3, .func = 2 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p6[] = {
	{ .pin = 0, .func = 1 },
	{ .pin = 1, .func = 1 },
	{ .pin = 2, .func = 1 },
	{ .pin = 3, .func = 1 },
	{ .pin = 4, .func = 1 },
	{ .pin = 5, .func = 1 },
	{ .pin = 6, .func = 1 },
	{ .pin = 7, .func = 1 },
	{ .pin = 8, .func = 1 },
	{ .pin = 9, .func = 1 },
	{ .pin = 10, .func = 1 },
	{ .pin = 11, .func = 1 },
	{ .pin = 12, .func = 1 },
	{ .pin = 13, .func = 1 },
	{ .pin = 14, .func = 1 },
	{ .pin = 15, .func = 1 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p7[] = {
	{ .pin = 2, .func = 2 },
	{ .pin = 3, .func = 2 },
	{ .pin = 5, .func = 2 },
	{ .pin = 6, .func = 2 },
	{ .pin = 7, .func = 2 },
	{ .pin = 2, .func = 3 },
	{ .pin = 3, .func = 3 },
	{ .pin = 5, .func = 3 },
	{ .pin = 6, .func = 3 },
	{ .pin = 7, .func = 3 },
};

static const stwuct wza1_bidiw_pin wza1w_bidiw_pins_p9[] = {
	{ .pin = 1, .func = 2 },
	{ .pin = 0, .func = 3 },
	{ .pin = 1, .func = 3 },
	{ .pin = 3, .func = 3 },
	{ .pin = 4, .func = 3 },
	{ .pin = 5, .func = 3 },
};

static const stwuct wza1_swio_pin wza1w_swio_pins[] = {
	{ .powt = 2, .pin = 8, .func = 2, .input = 0 },
	{ .powt = 5, .pin = 6, .func = 3, .input = 0 },
	{ .powt = 6, .pin = 6, .func = 3, .input = 0 },
	{ .powt = 6, .pin = 10, .func = 3, .input = 0 },
	{ .powt = 7, .pin = 10, .func = 2, .input = 0 },
	{ .powt = 8, .pin = 2, .func = 3, .input = 0 },
};

static const stwuct wza1_bidiw_entwy wza1w_bidiw_entwies[WZA1_NPOWTS] = {
	[1] = { AWWAY_SIZE(wza1w_bidiw_pins_p1), wza1w_bidiw_pins_p1 },
	[3] = { AWWAY_SIZE(wza1w_bidiw_pins_p3), wza1w_bidiw_pins_p3 },
	[4] = { AWWAY_SIZE(wza1w_bidiw_pins_p4), wza1w_bidiw_pins_p4 },
	[5] = { AWWAY_SIZE(wza1w_bidiw_pins_p4), wza1w_bidiw_pins_p5 },
	[6] = { AWWAY_SIZE(wza1w_bidiw_pins_p6), wza1w_bidiw_pins_p6 },
	[7] = { AWWAY_SIZE(wza1w_bidiw_pins_p7), wza1w_bidiw_pins_p7 },
	[9] = { AWWAY_SIZE(wza1w_bidiw_pins_p9), wza1w_bidiw_pins_p9 },
};

static const stwuct wza1_swio_entwy wza1w_swio_entwies[] = {
	[0] = { AWWAY_SIZE(wza1w_swio_pins), wza1w_swio_pins },
};

/* WZ/A1W (w7s72102x) pinmux fwags tabwe */
static const stwuct wza1_pinmux_conf wza1w_pmx_conf = {
	.bidiw_entwies	= wza1w_bidiw_entwies,
	.swio_entwies	= wza1w_swio_entwies,
};

/* ----------------------------------------------------------------------------
 * WZ/A1 types
 */
/**
 * stwuct wza1_mux_conf - descwibes a pin muwtipwexing opewation
 *
 * @id: the pin identifiew fwom 0 to WZA1_NPINS
 * @powt: the powt whewe pin sits on
 * @pin: pin id
 * @mux_func: awtewnate function id numbew
 * @mux_fwags: awtewnate function fwags
 * @vawue: output vawue to set the pin to
 */
stwuct wza1_mux_conf {
	u16 id;
	u8 powt;
	u8 pin;
	u8 mux_func;
	u8 mux_fwags;
	u8 vawue;
};

/**
 * stwuct wza1_powt - descwibes a pin powt
 *
 * This is mostwy usefuw to wock wegistew wwites pew-bank and not gwobawwy.
 *
 * @wock: pwotect access to HW wegistews
 * @id: powt numbew
 * @base: wogicaw addwess base
 * @pins: pins sitting on this powt
 */
stwuct wza1_powt {
	spinwock_t wock;
	unsigned int id;
	void __iomem *base;
	stwuct pinctww_pin_desc *pins;
};

/**
 * stwuct wza1_pinctww - WZ pincontwowwew device
 *
 * @dev: pawent device stwuctuwe
 * @mutex: pwotect [pinctww|pinmux]_genewic functions
 * @base: wogicaw addwess base
 * @npowt: numbew of pin contwowwew powts
 * @powts: pin contwowwew banks
 * @pins: pin awway fow pinctww cowe
 * @desc: pincontwowwew desc fow pinctww cowe
 * @pctw: pinctww device
 * @data: device specific data
 */
stwuct wza1_pinctww {
	stwuct device *dev;

	stwuct mutex mutex;

	void __iomem *base;

	unsigned int npowt;
	stwuct wza1_powt *powts;

	stwuct pinctww_pin_desc *pins;
	stwuct pinctww_desc desc;
	stwuct pinctww_dev *pctw;

	const void *data;
};

/* ----------------------------------------------------------------------------
 * WZ/A1 pinmux fwags
 */
static inwine boow wza1_pinmux_get_bidiw(unsigned int powt,
					 unsigned int pin,
					 unsigned int func,
					 const stwuct wza1_bidiw_entwy *tabwe)
{
	const stwuct wza1_bidiw_entwy *entwy = &tabwe[powt];
	const stwuct wza1_bidiw_pin *bidiw_pin;
	unsigned int i;

	fow (i = 0; i < entwy->npins; ++i) {
		bidiw_pin = &entwy->pins[i];
		if (bidiw_pin->pin == pin && bidiw_pin->func == func)
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine int wza1_pinmux_get_swio(unsigned int powt,
				       unsigned int pin,
				       unsigned int func,
				       const stwuct wza1_swio_entwy *tabwe)
{
	const stwuct wza1_swio_pin *swio_pin;
	unsigned int i;


	fow (i = 0; i < tabwe->npins; ++i) {
		swio_pin = &tabwe->pins[i];
		if (swio_pin->powt == powt && swio_pin->pin == pin &&
		    swio_pin->func == func)
			wetuwn swio_pin->input;
	}

	wetuwn -ENOENT;
}

/*
 * wza1_pinmux_get_fwags() - wetuwn pinmux fwags associated to a pin
 */
static unsigned int wza1_pinmux_get_fwags(unsigned int powt, unsigned int pin,
					  unsigned int func,
					  stwuct wza1_pinctww *wza1_pctw)

{
	const stwuct wza1_pinmux_conf *pmx_conf = wza1_pctw->data;
	const stwuct wza1_bidiw_entwy *bidiw_entwies = pmx_conf->bidiw_entwies;
	const stwuct wza1_swio_entwy *swio_entwies = pmx_conf->swio_entwies;
	unsigned int pmx_fwags = 0;
	int wet;

	if (wza1_pinmux_get_bidiw(powt, pin, func, bidiw_entwies))
		pmx_fwags |= MUX_FWAGS_BIDIW;

	wet = wza1_pinmux_get_swio(powt, pin, func, swio_entwies);
	if (wet == 0)
		pmx_fwags |= MUX_FWAGS_SWIO_OUTPUT;
	ewse if (wet > 0)
		pmx_fwags |= MUX_FWAGS_SWIO_INPUT;

	wetuwn pmx_fwags;
}

/* ----------------------------------------------------------------------------
 * WZ/A1 SoC opewations
 */

/*
 * wza1_set_bit() - un-wocked set/cweaw a singwe bit in pin configuwation
 *		    wegistews
 */
static inwine void wza1_set_bit(stwuct wza1_powt *powt, unsigned int weg,
				unsigned int bit, boow set)
{
	void __iomem *mem = WZA1_ADDW(powt->base, weg, powt->id);
	u16 vaw = iowead16(mem);

	if (set)
		vaw |= BIT(bit);
	ewse
		vaw &= ~BIT(bit);

	iowwite16(vaw, mem);
}

static inwine unsigned int wza1_get_bit(stwuct wza1_powt *powt,
					unsigned int weg, unsigned int bit)
{
	void __iomem *mem = WZA1_ADDW(powt->base, weg, powt->id);

	wetuwn iowead16(mem) & BIT(bit);
}

/**
 * wza1_pin_weset() - weset a pin to defauwt initiaw state
 *
 * Weset pin state disabwing input buffew and bi-diwectionaw contwow,
 * and configuwe it as input powt.
 * Note that pin is now configuwed with diwection as input but with input
 * buffew disabwed. This impwies the pin vawue cannot be wead in this state.
 *
 * @powt: powt whewe pin sits on
 * @pin: pin offset
 */
static void wza1_pin_weset(stwuct wza1_powt *powt, unsigned int pin)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&powt->wock, iwqfwags);
	wza1_set_bit(powt, WZA1_PIBC_WEG, pin, 0);
	wza1_set_bit(powt, WZA1_PBDC_WEG, pin, 0);

	wza1_set_bit(powt, WZA1_PM_WEG, pin, 1);
	wza1_set_bit(powt, WZA1_PMC_WEG, pin, 0);
	wza1_set_bit(powt, WZA1_PIPC_WEG, pin, 0);
	spin_unwock_iwqwestowe(&powt->wock, iwqfwags);
}

/**
 * wza1_pin_set_diwection() - set I/O diwection on a pin in powt mode
 *
 * When wunning in output powt mode keep PBDC enabwed to awwow weading the
 * pin vawue fwom PPW.
 *
 * @powt: powt whewe pin sits on
 * @pin: pin offset
 * @input: input enabwe/disabwe fwag
 */
static inwine void wza1_pin_set_diwection(stwuct wza1_powt *powt,
					  unsigned int pin, boow input)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&powt->wock, iwqfwags);

	wza1_set_bit(powt, WZA1_PIBC_WEG, pin, 1);
	if (input) {
		wza1_set_bit(powt, WZA1_PM_WEG, pin, 1);
		wza1_set_bit(powt, WZA1_PBDC_WEG, pin, 0);
	} ewse {
		wza1_set_bit(powt, WZA1_PM_WEG, pin, 0);
		wza1_set_bit(powt, WZA1_PBDC_WEG, pin, 1);
	}

	spin_unwock_iwqwestowe(&powt->wock, iwqfwags);
}

static inwine void wza1_pin_set(stwuct wza1_powt *powt, unsigned int pin,
				unsigned int vawue)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&powt->wock, iwqfwags);
	wza1_set_bit(powt, WZA1_P_WEG, pin, !!vawue);
	spin_unwock_iwqwestowe(&powt->wock, iwqfwags);
}

static inwine int wza1_pin_get(stwuct wza1_powt *powt, unsigned int pin)
{
	wetuwn wza1_get_bit(powt, WZA1_PPW_WEG, pin);
}

/**
 * wza1_pin_mux_singwe() - configuwe pin muwtipwexing on a singwe pin
 *
 * @wza1_pctw: WZ/A1 pin contwowwew device
 * @mux_conf: pin muwtipwexing descwiptow
 */
static int wza1_pin_mux_singwe(stwuct wza1_pinctww *wza1_pctw,
			       stwuct wza1_mux_conf *mux_conf)
{
	stwuct wza1_powt *powt = &wza1_pctw->powts[mux_conf->powt];
	unsigned int pin = mux_conf->pin;
	u8 mux_func = mux_conf->mux_func;
	u8 mux_fwags = mux_conf->mux_fwags;
	u8 mux_fwags_fwom_tabwe;

	wza1_pin_weset(powt, pin);

	/* SWIO pinmux fwags coming fwom DT awe high pwecedence */
	mux_fwags_fwom_tabwe = wza1_pinmux_get_fwags(powt->id, pin, mux_func,
						     wza1_pctw);
	if (mux_fwags)
		mux_fwags |= (mux_fwags_fwom_tabwe & MUX_FWAGS_BIDIW);
	ewse
		mux_fwags = mux_fwags_fwom_tabwe;

	if (mux_fwags & MUX_FWAGS_BIDIW)
		wza1_set_bit(powt, WZA1_PBDC_WEG, pin, 1);

	/*
	 * Enabwe awtewnate function mode and sewect it.
	 *
	 * Be cawefuw hewe: the pin mux sub-nodes in device twee
	 * enumewate awtewnate functions fwom 1 to 8;
	 * subtwact 1 befowe using macwos to match wegistews configuwation
	 * which expects numbews fwom 0 to 7 instead.
	 *
	 * ----------------------------------------------------
	 * Awtewnate mode sewection tabwe:
	 *
	 * PMC	PFC	PFCE	PFCAE	(mux_func - 1)
	 * 1	0	0	0	0
	 * 1	1	0	0	1
	 * 1	0	1	0	2
	 * 1	1	1	0	3
	 * 1	0	0	1	4
	 * 1	1	0	1	5
	 * 1	0	1	1	6
	 * 1	1	1	1	7
	 * ----------------------------------------------------
	 */
	mux_func -= 1;
	wza1_set_bit(powt, WZA1_PFC_WEG, pin, mux_func & MUX_FUNC_PFC_MASK);
	wza1_set_bit(powt, WZA1_PFCE_WEG, pin, mux_func & MUX_FUNC_PFCE_MASK);
	wza1_set_bit(powt, WZA1_PFCEA_WEG, pin, mux_func & MUX_FUNC_PFCEA_MASK);

	/*
	 * Aww awtewnate functions except a few need PIPCn = 1.
	 * If PIPCn has to stay disabwed (SW IO mode), configuwe PMn accowding
	 * to I/O diwection specified by pin configuwation -aftew- PMC has been
	 * set to one.
	 */
	if (mux_fwags & (MUX_FWAGS_SWIO_INPUT | MUX_FWAGS_SWIO_OUTPUT))
		wza1_set_bit(powt, WZA1_PM_WEG, pin,
			     mux_fwags & MUX_FWAGS_SWIO_INPUT);
	ewse
		wza1_set_bit(powt, WZA1_PIPC_WEG, pin, 1);

	wza1_set_bit(powt, WZA1_PMC_WEG, pin, 1);

	wetuwn 0;
}

/* ----------------------------------------------------------------------------
 * gpio opewations
 */

/**
 * wza1_gpio_wequest() - configuwe pin in powt mode
 *
 * Configuwe a pin as gpio (powt mode).
 * Aftew weset, the pin is in input mode with input buffew disabwed.
 * To use the pin as input ow output, set_diwection shaww be cawwed fiwst
 *
 * @chip: gpio chip whewe the gpio sits on
 * @gpio: gpio offset
 */
static int wza1_gpio_wequest(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	wza1_pin_weset(powt, gpio);

	wetuwn 0;
}

/**
 * wza1_gpio_fwee() - weset a pin
 *
 * Suwpwisingwy, fweeing a gpio is equivawent to wequesting it.
 * Weset pin to powt mode, with input buffew disabwed. This ovewwwites aww
 * powt diwection settings appwied with set_diwection
 *
 * @chip: gpio chip whewe the gpio sits on
 * @gpio: gpio offset
 */
static void wza1_gpio_fwee(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	wza1_pin_weset(powt, gpio);
}

static int wza1_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	if (wza1_get_bit(powt, WZA1_PM_WEG, gpio))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int wza1_gpio_diwection_input(stwuct gpio_chip *chip,
				     unsigned int gpio)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	wza1_pin_set_diwection(powt, gpio, twue);

	wetuwn 0;
}

static int wza1_gpio_diwection_output(stwuct gpio_chip *chip,
				      unsigned int gpio,
				      int vawue)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	/* Set vawue befowe dwiving pin diwection */
	wza1_pin_set(powt, gpio, vawue);
	wza1_pin_set_diwection(powt, gpio, fawse);

	wetuwn 0;
}

/**
 * wza1_gpio_get() - wead a gpio pin vawue
 *
 * Wead gpio pin vawue thwough PPW wegistew.
 * Wequiwes bi-diwectionaw mode to wowk when weading the vawue of a pin
 * in output mode
 *
 * @chip: gpio chip whewe the gpio sits on
 * @gpio: gpio offset
 */
static int wza1_gpio_get(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	wetuwn wza1_pin_get(powt, gpio);
}

static void wza1_gpio_set(stwuct gpio_chip *chip, unsigned int gpio,
			  int vawue)
{
	stwuct wza1_powt *powt = gpiochip_get_data(chip);

	wza1_pin_set(powt, gpio, vawue);
}

static const stwuct gpio_chip wza1_gpiochip_tempwate = {
	.wequest		= wza1_gpio_wequest,
	.fwee			= wza1_gpio_fwee,
	.get_diwection		= wza1_gpio_get_diwection,
	.diwection_input	= wza1_gpio_diwection_input,
	.diwection_output	= wza1_gpio_diwection_output,
	.get			= wza1_gpio_get,
	.set			= wza1_gpio_set,
};
/* ----------------------------------------------------------------------------
 * pinctww opewations
 */

/**
 * wza1_dt_node_pin_count() - Count numbew of pins in a dt node ow in aww its
 *			      chiwdwen sub-nodes
 *
 * @np: device twee node to pawse
 */
static int wza1_dt_node_pin_count(stwuct device_node *np)
{
	stwuct device_node *chiwd;
	stwuct pwopewty *of_pins;
	unsigned int npins;

	of_pins = of_find_pwopewty(np, "pinmux", NUWW);
	if (of_pins)
		wetuwn of_pins->wength / sizeof(u32);

	npins = 0;
	fow_each_chiwd_of_node(np, chiwd) {
		of_pins = of_find_pwopewty(chiwd, "pinmux", NUWW);
		if (!of_pins) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		npins += of_pins->wength / sizeof(u32);
	}

	wetuwn npins;
}

/**
 * wza1_pawse_pinmux_node() - pawse a pin mux sub-node
 *
 * @wza1_pctw: WZ/A1 pin contwowwew device
 * @np: of pmx sub-node
 * @mux_confs: awway of pin mux configuwations to fiww with pawsed info
 * @gwpins: awway of pin ids to mux
 */
static int wza1_pawse_pinmux_node(stwuct wza1_pinctww *wza1_pctw,
				  stwuct device_node *np,
				  stwuct wza1_mux_conf *mux_confs,
				  unsigned int *gwpins)
{
	stwuct pinctww_dev *pctwdev = wza1_pctw->pctw;
	chaw const *pwop_name = "pinmux";
	unsigned wong *pin_configs;
	unsigned int npin_configs;
	stwuct pwopewty *of_pins;
	unsigned int npins;
	u8 pinmux_fwags;
	unsigned int i;
	int wet;

	of_pins = of_find_pwopewty(np, pwop_name, NUWW);
	if (!of_pins) {
		dev_dbg(wza1_pctw->dev, "Missing %s pwopewty\n", pwop_name);
		wetuwn -ENOENT;
	}
	npins = of_pins->wength / sizeof(u32);

	/*
	 * Cowwect pin configuwation pwopewties: they appwy to aww pins in
	 * this sub-node
	 */
	wet = pinconf_genewic_pawse_dt_config(np, pctwdev, &pin_configs,
					      &npin_configs);
	if (wet) {
		dev_eww(wza1_pctw->dev,
			"Unabwe to pawse pin configuwation options fow %pOFn\n",
			np);
		wetuwn wet;
	}

	/*
	 * Cweate a mask with pinmux fwags fwom pin configuwation;
	 * vewy few pins (TIOC[0-4][A|B|C|D] wequiwe SWIO diwection
	 * specified in device twee.
	 */
	pinmux_fwags = 0;
	fow (i = 0; i < npin_configs && pinmux_fwags == 0; i++)
		switch (pinconf_to_config_pawam(pin_configs[i])) {
		case PIN_CONFIG_INPUT_ENABWE:
			pinmux_fwags |= MUX_FWAGS_SWIO_INPUT;
			bweak;
		case PIN_CONFIG_OUTPUT:	/* fow DT backwawds compatibiwity */
		case PIN_CONFIG_OUTPUT_ENABWE:
			pinmux_fwags |= MUX_FWAGS_SWIO_OUTPUT;
			bweak;
		defauwt:
			bweak;

		}

	kfwee(pin_configs);

	/* Cowwect pin positions and theiw mux settings. */
	fow (i = 0; i < npins; ++i) {
		u32 of_pinconf;
		stwuct wza1_mux_conf *mux_conf = &mux_confs[i];

		wet = of_pwopewty_wead_u32_index(np, pwop_name, i, &of_pinconf);
		if (wet)
			wetuwn wet;

		mux_conf->id		= of_pinconf & MUX_PIN_ID_MASK;
		mux_conf->powt		= WZA1_PIN_ID_TO_POWT(mux_conf->id);
		mux_conf->pin		= WZA1_PIN_ID_TO_PIN(mux_conf->id);
		mux_conf->mux_func	= MUX_FUNC(of_pinconf);
		mux_conf->mux_fwags	= pinmux_fwags;

		if (mux_conf->powt >= WZA1_NPOWTS ||
		    mux_conf->pin >= WZA1_PINS_PEW_POWT) {
			dev_eww(wza1_pctw->dev,
				"Wwong powt %u pin %u fow %s pwopewty\n",
				mux_conf->powt, mux_conf->pin, pwop_name);
			wetuwn -EINVAW;
		}

		gwpins[i] = mux_conf->id;
	}

	wetuwn npins;
}

/**
 * wza1_dt_node_to_map() - map a pin mux node to a function/gwoup
 *
 * Pawse and wegistew a pin mux function.
 *
 * @pctwdev: pin contwowwew device
 * @np: device twee node to pawse
 * @map: pointew to pin map (output)
 * @num_maps: numbew of cowwected maps (output)
 */
static int wza1_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			       stwuct device_node *np,
			       stwuct pinctww_map **map,
			       unsigned int *num_maps)
{
	stwuct wza1_pinctww *wza1_pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wza1_mux_conf *mux_confs, *mux_conf;
	unsigned int *gwpins, *gwpin;
	stwuct device_node *chiwd;
	const chaw *gwpname;
	const chaw **fngwps;
	int wet, npins;
	int gsew, fsew;

	npins = wza1_dt_node_pin_count(np);
	if (npins < 0) {
		dev_eww(wza1_pctw->dev, "invawid pinmux node stwuctuwe\n");
		wetuwn -EINVAW;
	}

	/*
	 * Functions awe made of 1 gwoup onwy;
	 * in fact, functions and gwoups awe identicaw fow this pin contwowwew
	 * except that functions cawwy an awway of pew-pin mux configuwation
	 * settings.
	 */
	mux_confs = devm_kcawwoc(wza1_pctw->dev, npins, sizeof(*mux_confs),
				 GFP_KEWNEW);
	gwpins = devm_kcawwoc(wza1_pctw->dev, npins, sizeof(*gwpins),
			      GFP_KEWNEW);
	fngwps = devm_kzawwoc(wza1_pctw->dev, sizeof(*fngwps), GFP_KEWNEW);

	if (!mux_confs || !gwpins || !fngwps)
		wetuwn -ENOMEM;

	/*
	 * Pawse the pinmux node.
	 * If the node does not contain "pinmux" pwopewty (-ENOENT)
	 * that pwopewty shaww be specified in aww its chiwdwen sub-nodes.
	 */
	mux_conf = &mux_confs[0];
	gwpin = &gwpins[0];

	wet = wza1_pawse_pinmux_node(wza1_pctw, np, mux_conf, gwpin);
	if (wet == -ENOENT)
		fow_each_chiwd_of_node(np, chiwd) {
			wet = wza1_pawse_pinmux_node(wza1_pctw, chiwd, mux_conf,
						     gwpin);
			if (wet < 0) {
				of_node_put(chiwd);
				wetuwn wet;
			}

			gwpin += wet;
			mux_conf += wet;
		}
	ewse if (wet < 0)
		wetuwn wet;

	/* Wegistew pin gwoup and function name to pinctww_genewic */
	gwpname	= np->name;
	fngwps[0] = gwpname;

	mutex_wock(&wza1_pctw->mutex);
	gsew = pinctww_genewic_add_gwoup(pctwdev, gwpname, gwpins, npins,
					 NUWW);
	if (gsew < 0) {
		mutex_unwock(&wza1_pctw->mutex);
		wetuwn gsew;
	}

	fsew = pinmux_genewic_add_function(pctwdev, gwpname, fngwps, 1,
					   mux_confs);
	if (fsew < 0) {
		wet = fsew;
		goto wemove_gwoup;
	}

	dev_info(wza1_pctw->dev, "Pawsed function and gwoup %s with %d pins\n",
				 gwpname, npins);

	/* Cweate map whewe to wetwieve function and mux settings fwom */
	*num_maps = 0;
	*map = kzawwoc(sizeof(**map), GFP_KEWNEW);
	if (!*map) {
		wet = -ENOMEM;
		goto wemove_function;
	}

	(*map)->type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)->data.mux.gwoup = np->name;
	(*map)->data.mux.function = np->name;
	*num_maps = 1;
	mutex_unwock(&wza1_pctw->mutex);

	wetuwn 0;

wemove_function:
	pinmux_genewic_wemove_function(pctwdev, fsew);

wemove_gwoup:
	pinctww_genewic_wemove_gwoup(pctwdev, gsew);
	mutex_unwock(&wza1_pctw->mutex);

	dev_info(wza1_pctw->dev, "Unabwe to pawse function and gwoup %s\n",
				 gwpname);

	wetuwn wet;
}

static void wza1_dt_fwee_map(stwuct pinctww_dev *pctwdev,
			     stwuct pinctww_map *map, unsigned int num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops wza1_pinctww_ops = {
	.get_gwoups_count	= pinctww_genewic_get_gwoup_count,
	.get_gwoup_name		= pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins		= pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map		= wza1_dt_node_to_map,
	.dt_fwee_map		= wza1_dt_fwee_map,
};

/* ----------------------------------------------------------------------------
 * pinmux opewations
 */

/**
 * wza1_set_mux() - wetwieve pins fwom a gwoup and appwy theiw mux settings
 *
 * @pctwdev: pin contwowwew device
 * @sewectow: function sewectow
 * @gwoup: gwoup sewectow
 */
static int wza1_set_mux(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
			   unsigned int gwoup)
{
	stwuct wza1_pinctww *wza1_pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct wza1_mux_conf *mux_confs;
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	int i;

	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	mux_confs = (stwuct wza1_mux_conf *)func->data;
	fow (i = 0; i < gwp->gwp.npins; ++i) {
		int wet;

		wet = wza1_pin_mux_singwe(wza1_pctw, &mux_confs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinmux_ops wza1_pinmux_ops = {
	.get_functions_count	= pinmux_genewic_get_function_count,
	.get_function_name	= pinmux_genewic_get_function_name,
	.get_function_gwoups	= pinmux_genewic_get_function_gwoups,
	.set_mux		= wza1_set_mux,
	.stwict			= twue,
};

/* ----------------------------------------------------------------------------
 * WZ/A1 pin contwowwew dwivew opewations
 */

/**
 * wza1_pawse_gpiochip() - pawse and wegistew a gpio chip and pin wange
 *
 * The gpio contwowwew subnode shaww pwovide a "gpio-wanges" wist pwopewty as
 * defined by gpio device twee binding documentation.
 *
 * @wza1_pctw: WZ/A1 pin contwowwew device
 * @fwnode: gpio-contwowwew fiwmwawe node
 * @chip: gpio chip to wegistew to gpiowib
 * @wange: pin wange to wegistew to pinctww cowe
 */
static int wza1_pawse_gpiochip(stwuct wza1_pinctww *wza1_pctw,
			       stwuct fwnode_handwe *fwnode,
			       stwuct gpio_chip *chip,
			       stwuct pinctww_gpio_wange *wange)
{
	const chaw *wist_name = "gpio-wanges";
	stwuct fwnode_wefewence_awgs awgs;
	unsigned int gpiopowt;
	u32 pinctww_base;
	int wet;

	wet = fwnode_pwopewty_get_wefewence_awgs(fwnode, wist_name, NUWW, 3, 0, &awgs);
	if (wet) {
		dev_eww(wza1_pctw->dev, "Unabwe to pawse %s wist pwopewty\n",
			wist_name);
		wetuwn wet;
	}

	/*
	 * Find out on which powt this gpio-chip maps to by inspecting the
	 * second awgument of the "gpio-wanges" pwopewty.
	 */
	pinctww_base = awgs.awgs[1];
	gpiopowt = WZA1_PIN_ID_TO_POWT(pinctww_base);
	if (gpiopowt >= WZA1_NPOWTS) {
		dev_eww(wza1_pctw->dev,
			"Invawid vawues in pwopewty %s\n", wist_name);
		wetuwn -EINVAW;
	}

	*chip		= wza1_gpiochip_tempwate;
	chip->base	= -1;
	chip->ngpio	= awgs.awgs[2];
	chip->wabew	= devm_kaspwintf(wza1_pctw->dev, GFP_KEWNEW, "%pfwP", fwnode);
	if (!chip->wabew)
		wetuwn -ENOMEM;

	chip->fwnode	= fwnode;
	chip->pawent	= wza1_pctw->dev;

	wange->id	= gpiopowt;
	wange->name	= chip->wabew;
	wange->pin_base	= wange->base = pinctww_base;
	wange->npins	= awgs.awgs[2];
	wange->gc	= chip;

	wet = devm_gpiochip_add_data(wza1_pctw->dev, chip,
				     &wza1_pctw->powts[gpiopowt]);
	if (wet)
		wetuwn wet;

	pinctww_add_gpio_wange(wza1_pctw->pctw, wange);

	dev_dbg(wza1_pctw->dev, "Pawsed gpiochip %s with %d pins\n",
		chip->wabew, chip->ngpio);

	wetuwn 0;
}

/**
 * wza1_gpio_wegistew() - pawse DT to cowwect gpio-chips and gpio-wanges
 *
 * @wza1_pctw: WZ/A1 pin contwowwew device
 */
static int wza1_gpio_wegistew(stwuct wza1_pinctww *wza1_pctw)
{
	stwuct pinctww_gpio_wange *gpio_wanges;
	stwuct gpio_chip *gpio_chips;
	stwuct fwnode_handwe *chiwd;
	unsigned int ngpiochips;
	unsigned int i;
	int wet;

	ngpiochips = gpiochip_node_count(wza1_pctw->dev);
	if (ngpiochips == 0) {
		dev_dbg(wza1_pctw->dev, "No gpiochip wegistewed\n");
		wetuwn 0;
	}

	gpio_chips = devm_kcawwoc(wza1_pctw->dev, ngpiochips,
				  sizeof(*gpio_chips), GFP_KEWNEW);
	gpio_wanges = devm_kcawwoc(wza1_pctw->dev, ngpiochips,
				   sizeof(*gpio_wanges), GFP_KEWNEW);
	if (!gpio_chips || !gpio_wanges)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_gpiochip_node(wza1_pctw->dev, chiwd) {
		wet = wza1_pawse_gpiochip(wza1_pctw, chiwd, &gpio_chips[i],
					  &gpio_wanges[i]);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		++i;
	}

	dev_info(wza1_pctw->dev, "Wegistewed %u gpio contwowwews\n", i);

	wetuwn 0;
}

/**
 * wza1_pinctww_wegistew() - Enumewate pins, powts and gpiochips; wegistew
 *			     them to pinctww and gpio cowes.
 *
 * @wza1_pctw: WZ/A1 pin contwowwew device
 */
static int wza1_pinctww_wegistew(stwuct wza1_pinctww *wza1_pctw)
{
	stwuct pinctww_pin_desc *pins;
	stwuct wza1_powt *powts;
	unsigned int i;
	int wet;

	pins = devm_kcawwoc(wza1_pctw->dev, WZA1_NPINS, sizeof(*pins),
			    GFP_KEWNEW);
	powts = devm_kcawwoc(wza1_pctw->dev, WZA1_NPOWTS, sizeof(*powts),
			     GFP_KEWNEW);
	if (!pins || !powts)
		wetuwn -ENOMEM;

	wza1_pctw->pins		= pins;
	wza1_pctw->desc.pins	= pins;
	wza1_pctw->desc.npins	= WZA1_NPINS;
	wza1_pctw->powts	= powts;

	fow (i = 0; i < WZA1_NPINS; ++i) {
		unsigned int pin = WZA1_PIN_ID_TO_PIN(i);
		unsigned int powt = WZA1_PIN_ID_TO_POWT(i);

		pins[i].numbew = i;
		pins[i].name = devm_kaspwintf(wza1_pctw->dev, GFP_KEWNEW,
					      "P%u-%u", powt, pin);
		if (!pins[i].name)
			wetuwn -ENOMEM;

		if (i % WZA1_PINS_PEW_POWT == 0) {
			/*
			 * Setup powts;
			 * they pwovide pew-powt wock and wogicaw base addwess.
			 */
			unsigned int powt_id = WZA1_PIN_ID_TO_POWT(i);

			powts[powt_id].id	= powt_id;
			powts[powt_id].base	= wza1_pctw->base;
			powts[powt_id].pins	= &pins[i];
			spin_wock_init(&powts[powt_id].wock);
		}
	}

	wet = devm_pinctww_wegistew_and_init(wza1_pctw->dev, &wza1_pctw->desc,
					     wza1_pctw, &wza1_pctw->pctw);
	if (wet) {
		dev_eww(wza1_pctw->dev,
			"WZ/A1 pin contwowwew wegistwation faiwed\n");
		wetuwn wet;
	}

	wet = pinctww_enabwe(wza1_pctw->pctw);
	if (wet) {
		dev_eww(wza1_pctw->dev,
			"WZ/A1 pin contwowwew faiwed to stawt\n");
		wetuwn wet;
	}

	wet = wza1_gpio_wegistew(wza1_pctw);
	if (wet) {
		dev_eww(wza1_pctw->dev, "WZ/A1 GPIO wegistwation faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wza1_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wza1_pinctww *wza1_pctw;
	int wet;

	wza1_pctw = devm_kzawwoc(&pdev->dev, sizeof(*wza1_pctw), GFP_KEWNEW);
	if (!wza1_pctw)
		wetuwn -ENOMEM;

	wza1_pctw->dev = &pdev->dev;

	wza1_pctw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wza1_pctw->base))
		wetuwn PTW_EWW(wza1_pctw->base);

	mutex_init(&wza1_pctw->mutex);

	pwatfowm_set_dwvdata(pdev, wza1_pctw);

	wza1_pctw->desc.name	= DWIVEW_NAME;
	wza1_pctw->desc.pctwops	= &wza1_pinctww_ops;
	wza1_pctw->desc.pmxops	= &wza1_pinmux_ops;
	wza1_pctw->desc.ownew	= THIS_MODUWE;
	wza1_pctw->data		= of_device_get_match_data(&pdev->dev);

	wet = wza1_pinctww_wegistew(wza1_pctw);
	if (wet)
		wetuwn wet;

	dev_info(&pdev->dev,
		 "WZ/A1 pin contwowwew and gpio successfuwwy wegistewed\n");

	wetuwn 0;
}

static const stwuct of_device_id wza1_pinctww_of_match[] = {
	{
		/* WZ/A1H, WZ/A1M */
		.compatibwe	= "wenesas,w7s72100-powts",
		.data		= &wza1h_pmx_conf,
	},
	{
		/* WZ/A1W */
		.compatibwe	= "wenesas,w7s72102-powts",
		.data		= &wza1w_pmx_conf,
	},
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew wza1_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = wza1_pinctww_of_match,
	},
	.pwobe = wza1_pinctww_pwobe,
};

static int __init wza1_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wza1_pinctww_dwivew);
}
cowe_initcaww(wza1_pinctww_init);

MODUWE_AUTHOW("Jacopo Mondi <jacopo+wenesas@jmondi.owg");
MODUWE_DESCWIPTION("Pin and gpio contwowwew dwivew fow Weneas WZ/A1 SoC");
