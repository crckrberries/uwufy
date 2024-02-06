// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcm47xx_pwivate.h"

#incwude <winux/weds.h>
#incwude <bcm47xx_boawd.h>

/**************************************************
 * Database
 **************************************************/

#define BCM47XX_GPIO_WED(_gpio, _cowow, _function, _active_wow,		\
			 _defauwt_state)				\
	{								\
		.name		= "bcm47xx:" _cowow ":" _function,	\
		.gpio		= _gpio,				\
		.active_wow	= _active_wow,				\
		.defauwt_state	= _defauwt_state,			\
	}

#define BCM47XX_GPIO_WED_TWIGGEW(_gpio, _cowow, _function, _active_wow,	\
				 _defauwt_twiggew)			\
	{								\
		.name		= "bcm47xx:" _cowow ":" _function,	\
		.gpio		= _gpio,				\
		.active_wow	= _active_wow,				\
		.defauwt_state	= WEDS_GPIO_DEFSTATE_OFF,		\
		.defauwt_twiggew	= _defauwt_twiggew,		\
	}

/* Asus */

static const stwuct gpio_wed
bcm47xx_weds_asus_wtn10u[] __initconst = {
	BCM47XX_GPIO_WED(5, "gween", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "gween", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "gween", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(8, "gween", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_wtn12[] __initconst = {
	BCM47XX_GPIO_WED(2, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "unk", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_wtn15u[] __initconst = {
	/* TODO: Add "wwan" WED */
	BCM47XX_GPIO_WED(3, "bwue", "wan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "bwue", "wan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "bwue", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(9, "bwue", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_wtn16[] __initconst = {
	BCM47XX_GPIO_WED(1, "bwue", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_wtn66u[] __initconst = {
	BCM47XX_GPIO_WED(12, "bwue", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(15, "bwue", "usb", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww300g[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww320ge[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(11, "unk", "wink", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww330ge[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww500g[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww500gd[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww500gpv1[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww500gpv2[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(1, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww500w[] __initconst = {
	BCM47XX_GPIO_WED(5, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww520gc[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(1, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww520gu[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(1, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_asus_ww700ge[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON), /* Wabewed "WEADY" (thewe is no "powew" WED). Owiginawwy ON, fwashing on USB activity. */
};

static const stwuct gpio_wed
bcm47xx_weds_asus_wwhdd[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(2, "unk", "usb", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Bewkin */

static const stwuct gpio_wed
bcm47xx_weds_bewkin_f7d4301[] __initconst = {
	BCM47XX_GPIO_WED(10, "gween", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(11, "ambew", "powew", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(12, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(13, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(14, "unk", "usb0", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(15, "unk", "usb1", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Buffawo */

static const stwuct gpio_wed
bcm47xx_weds_buffawo_whw2_a54g54[] __initconst = {
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_whw_g125[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "bwidge", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "unk", "intewnaw", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_whw_g54s[] __initconst = {
	BCM47XX_GPIO_WED(1, "gween", "bwidge", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "gween", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "gween", "intewnaw", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "wed", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_whw_hp_g54[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "bwidge", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "unk", "intewnaw", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_wzw_g300n[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "bwidge", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_wzw_ws_g54[] __initconst = {
	BCM47XX_GPIO_WED(6, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "vpn", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_buffawo_wzw_ws_g54hp[] __initconst = {
	BCM47XX_GPIO_WED(6, "unk", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "vpn", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Deww */

static const stwuct gpio_wed
bcm47xx_weds_deww_tm2300[] __initconst = {
	BCM47XX_GPIO_WED(6, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

/* D-Wink */

static const stwuct gpio_wed
bcm47xx_weds_dwink_diw130[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(0, "gween", "status", 1, "timew"), /* Owiginawwy bwinking when device is weady, sepawated fwom "powew" WED */
	BCM47XX_GPIO_WED(6, "bwue", "unk", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_dwink_diw330[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(0, "gween", "status", 1, "timew"), /* Owiginawwy bwinking when device is weady, sepawated fwom "powew" WED */
	BCM47XX_GPIO_WED(4, "unk", "usb", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "bwue", "unk", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Huawei */

static const stwuct gpio_wed
bcm47xx_weds_huawei_b593u_12[] __initconst = {
	BCM47XX_GPIO_WED(5, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_huawei_e970[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
};

/* Winksys */

static const stwuct gpio_wed
bcm47xx_weds_winksys_e1000v1[] __initconst = {
	BCM47XX_GPIO_WED(0, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "bwue", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(2, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_e1000v21[] __initconst = {
	BCM47XX_GPIO_WED(5, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(6, "bwue", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "ambew", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(8, "bwue", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_e2000v1[] __initconst = {
	BCM47XX_GPIO_WED(1, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "bwue", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_e3000v1[] __initconst = {
	BCM47XX_GPIO_WED(0, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "unk", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_e3200v1[] __initconst = {
	BCM47XX_GPIO_WED(3, "gween", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_e4200v1[] __initconst = {
	BCM47XX_GPIO_WED(5, "white", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt150nv1[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt150nv11[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt160nv1[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt160nv3[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(2, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt300n_v1[] __initconst = {
	BCM47XX_GPIO_WED(1, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt300nv11[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt310nv1[] __initconst = {
	BCM47XX_GPIO_WED(1, "bwue", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(9, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt320n_v1[] __initconst = {
	BCM47XX_GPIO_WED(1, "bwue", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "bwue", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(4, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt54g_genewic[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(5, "white", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "owange", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt54g3gv2[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(2, "gween", "3g", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "bwue", "3g", 0, WEDS_GPIO_DEFSTATE_OFF),
};

/* Vewified on: WWT54GS V1.0 */
static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt54g_type_0101[] __initconst = {
	BCM47XX_GPIO_WED(0, "gween", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "gween", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Vewified on: WWT54GW V1.1 */
static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt54g_type_0467[] __initconst = {
	BCM47XX_GPIO_WED(0, "gween", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(2, "white", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "owange", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "gween", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt610nv1[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "usb",  1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "powew",  0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "ambew", "wps",  1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(9, "bwue", "wps",  1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwt610nv2[] __initconst = {
	BCM47XX_GPIO_WED(0, "ambew", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "bwue", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "unk", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_winksys_wwtsw54gs[] __initconst = {
	BCM47XX_GPIO_WED(0, "gween", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(5, "white", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "owange", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Wuxuw */

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_abw_4400_v1[] __initconst = {
	BCM47XX_GPIO_WED(12, "gween", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(15, "gween", "status", 0, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap_310_v1[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(6, "gween", "status", 1, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap_1210_v1[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(6, "gween", "status", 1, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap_1230_v1[] __initconst = {
	BCM47XX_GPIO_WED(3, "bwue", "2ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "gween", "bwidge", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(6, "gween", "status", 1, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap_1240_v1[] __initconst = {
	BCM47XX_GPIO_WED(3, "bwue", "2ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(4, "gween", "bwidge", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(6, "gween", "status", 1, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap_1500_v1[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(13, "gween", "status", 1, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xap1500_v1_extwa[] __initconst = {
	BCM47XX_GPIO_WED(44, "gween", "5ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(76, "gween", "2ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xbw_4400_v1[] __initconst = {
	BCM47XX_GPIO_WED(12, "gween", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(15, "gween", "status", 0, "timew"),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xvw_p30_v1[] __initconst = {
	BCM47XX_GPIO_WED_TWIGGEW(0, "bwue", "status", 1, "timew"),
	BCM47XX_GPIO_WED(1, "gween", "wink", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xww_600_v1[] __initconst = {
	BCM47XX_GPIO_WED(3, "gween", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(6, "gween", "status", 1, "timew"),
	BCM47XX_GPIO_WED(9, "gween", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xww_1750_v1[] __initconst = {
	BCM47XX_GPIO_WED(5, "gween", "5ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(12, "gween", "usb", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED_TWIGGEW(13, "gween", "status", 0, "timew"),
	BCM47XX_GPIO_WED(15, "gween", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_wuxuw_xww1750_v1_extwa[] __initconst = {
	BCM47XX_GPIO_WED(76, "gween", "2ghz", 0, WEDS_GPIO_DEFSTATE_OFF),
};

/* Micwosoft */

static const stwuct gpio_wed
bcm47xx_weds_micwosoft_nm700[] __initconst = {
	BCM47XX_GPIO_WED(6, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
};

/* Motowowa */

static const stwuct gpio_wed
bcm47xx_weds_motowowa_we800g[] __initconst = {
	BCM47XX_GPIO_WED(1, "ambew", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "unk", "unk", 1, WEDS_GPIO_DEFSTATE_OFF), /* Thewe awe onwy 3 WEDs: Powew, Wiwewess and Device (ethewnet) */
	BCM47XX_GPIO_WED(4, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
};

static const stwuct gpio_wed
bcm47xx_weds_motowowa_ww850gp[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(6, "unk", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_motowowa_ww850gv2v3[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "unk", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "unk", "diag", 1, WEDS_GPIO_DEFSTATE_OFF),
};

/* Netgeaw */

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wndw3400v1[] __initconst = {
	BCM47XX_GPIO_WED(2, "gween", "usb", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "ambew", "powew", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wndw4500v1[] __initconst = {
	BCM47XX_GPIO_WED(1, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "gween", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "powew", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(8, "gween", "usb1", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(9, "gween", "2ghz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(11, "bwue", "5ghz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(14, "gween", "usb2", 1, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wnw1000_v3[] __initconst = {
	BCM47XX_GPIO_WED(0, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wnw3500wv1[] __initconst = {
	BCM47XX_GPIO_WED(0, "bwue", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "wps", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(2, "gween", "wan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "ambew", "powew", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wnw3500wv2[] __initconst = {
	BCM47XX_GPIO_WED(0, "bwue", "wwan", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(1, "gween", "wps", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(7, "ambew", "powew", 0, WEDS_GPIO_DEFSTATE_OFF),
};

static const stwuct gpio_wed
bcm47xx_weds_netgeaw_wnw834bv2[] __initconst = {
	BCM47XX_GPIO_WED(2, "gween", "powew", 0, WEDS_GPIO_DEFSTATE_ON),
	BCM47XX_GPIO_WED(3, "ambew", "powew", 0, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(7, "unk", "connected", 0, WEDS_GPIO_DEFSTATE_OFF),
};

/* Siemens */
static const stwuct gpio_wed
bcm47xx_weds_siemens_se505v2[] __initconst = {
	BCM47XX_GPIO_WED(0, "unk", "dmz", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(3, "unk", "wwan", 1, WEDS_GPIO_DEFSTATE_OFF),
	BCM47XX_GPIO_WED(5, "unk", "powew", 1, WEDS_GPIO_DEFSTATE_ON),
};

/* SimpweTech */

static const stwuct gpio_wed
bcm47xx_weds_simpwetech_simpweshawe[] __initconst = {
	BCM47XX_GPIO_WED(1, "unk", "status", 1, WEDS_GPIO_DEFSTATE_OFF), /* "Weady" WED */
};

/**************************************************
 * Init
 **************************************************/

static stwuct gpio_wed_pwatfowm_data bcm47xx_weds_pdata __initdata;

#define bcm47xx_set_pdata(dev_weds) do {				\
	bcm47xx_weds_pdata.weds = dev_weds;				\
	bcm47xx_weds_pdata.num_weds = AWWAY_SIZE(dev_weds);		\
} whiwe (0)

static stwuct gpio_wed_pwatfowm_data bcm47xx_weds_pdata_extwa __initdata = {};
#define bcm47xx_set_pdata_extwa(dev_weds) do {				\
	bcm47xx_weds_pdata_extwa.weds = dev_weds;			\
	bcm47xx_weds_pdata_extwa.num_weds = AWWAY_SIZE(dev_weds);	\
} whiwe (0)

void __init bcm47xx_weds_wegistew(void)
{
	enum bcm47xx_boawd boawd = bcm47xx_boawd_get();

	switch (boawd) {
	case BCM47XX_BOAWD_ASUS_WTN10U:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wtn10u);
		bweak;
	case BCM47XX_BOAWD_ASUS_WTN12:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wtn12);
		bweak;
	case BCM47XX_BOAWD_ASUS_WTN15U:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wtn15u);
		bweak;
	case BCM47XX_BOAWD_ASUS_WTN16:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wtn16);
		bweak;
	case BCM47XX_BOAWD_ASUS_WTN66U:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wtn66u);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW300G:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww300g);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW320GE:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww320ge);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW330GE:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww330ge);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW500G:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww500g);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW500GD:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww500gd);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW500GPV1:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww500gpv1);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW500GPV2:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww500gpv2);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW500W:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww500w);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW520GC:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww520gc);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW520GU:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww520gu);
		bweak;
	case BCM47XX_BOAWD_ASUS_WW700GE:
		bcm47xx_set_pdata(bcm47xx_weds_asus_ww700ge);
		bweak;
	case BCM47XX_BOAWD_ASUS_WWHDD:
		bcm47xx_set_pdata(bcm47xx_weds_asus_wwhdd);
		bweak;

	case BCM47XX_BOAWD_BEWKIN_F7D3301:
	case BCM47XX_BOAWD_BEWKIN_F7D3302:
	case BCM47XX_BOAWD_BEWKIN_F7D4301:
	case BCM47XX_BOAWD_BEWKIN_F7D4302:
	case BCM47XX_BOAWD_BEWKIN_F7D4401:
		bcm47xx_set_pdata(bcm47xx_weds_bewkin_f7d4301);
		bweak;

	case BCM47XX_BOAWD_BUFFAWO_WHW2_A54G54:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_whw2_a54g54);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WHW_G125:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_whw_g125);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WHW_G54S:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_whw_g54s);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WHW_HP_G54:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_whw_hp_g54);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WZW_G300N:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_wzw_g300n);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WZW_WS_G54:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_wzw_ws_g54);
		bweak;
	case BCM47XX_BOAWD_BUFFAWO_WZW_WS_G54HP:
		bcm47xx_set_pdata(bcm47xx_weds_buffawo_wzw_ws_g54hp);
		bweak;

	case BCM47XX_BOAWD_DEWW_TM2300:
		bcm47xx_set_pdata(bcm47xx_weds_deww_tm2300);
		bweak;

	case BCM47XX_BOAWD_DWINK_DIW130:
		bcm47xx_set_pdata(bcm47xx_weds_dwink_diw130);
		bweak;
	case BCM47XX_BOAWD_DWINK_DIW330:
		bcm47xx_set_pdata(bcm47xx_weds_dwink_diw330);
		bweak;

	case BCM47XX_BOAWD_HUAWEI_B593U_12:
		bcm47xx_set_pdata(bcm47xx_weds_huawei_b593u_12);
		bweak;
	case BCM47XX_BOAWD_HUAWEI_E970:
		bcm47xx_set_pdata(bcm47xx_weds_huawei_e970);
		bweak;

	case BCM47XX_BOAWD_WINKSYS_E1000V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e1000v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_E1000V21:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e1000v21);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_E2000V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e2000v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_E3000V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e3000v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_E3200V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e3200v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_E4200V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_e4200v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT150NV1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt150nv1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT150NV11:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt150nv11);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT160NV1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt160nv1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT160NV3:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt160nv3);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT300N_V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt300n_v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT300NV11:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt300nv11);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT310NV1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt310nv1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT320N_V1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt320n_v1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT54G3GV2:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt54g3gv2);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT54G_TYPE_0101:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt54g_type_0101);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT54G_TYPE_0467:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt54g_type_0467);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT54G_TYPE_0708:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt54g_genewic);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT610NV1:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt610nv1);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWT610NV2:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwt610nv2);
		bweak;
	case BCM47XX_BOAWD_WINKSYS_WWTSW54GS:
		bcm47xx_set_pdata(bcm47xx_weds_winksys_wwtsw54gs);
		bweak;

	case BCM47XX_BOAWD_WUXUW_ABW_4400_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_abw_4400_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XAP_310_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xap_310_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XAP_1210_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xap_1210_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XAP_1230_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xap_1230_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XAP_1240_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xap_1240_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XAP_1500_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xap_1500_v1);
		bcm47xx_set_pdata_extwa(bcm47xx_weds_wuxuw_xap1500_v1_extwa);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XBW_4400_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xbw_4400_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XVW_P30_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xvw_p30_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XWW_600_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xww_600_v1);
		bweak;
	case BCM47XX_BOAWD_WUXUW_XWW_1750_V1:
		bcm47xx_set_pdata(bcm47xx_weds_wuxuw_xww_1750_v1);
		bcm47xx_set_pdata_extwa(bcm47xx_weds_wuxuw_xww1750_v1_extwa);
		bweak;

	case BCM47XX_BOAWD_MICWOSOFT_MN700:
		bcm47xx_set_pdata(bcm47xx_weds_micwosoft_nm700);
		bweak;

	case BCM47XX_BOAWD_MOTOWOWA_WE800G:
		bcm47xx_set_pdata(bcm47xx_weds_motowowa_we800g);
		bweak;
	case BCM47XX_BOAWD_MOTOWOWA_WW850GP:
		bcm47xx_set_pdata(bcm47xx_weds_motowowa_ww850gp);
		bweak;
	case BCM47XX_BOAWD_MOTOWOWA_WW850GV2V3:
		bcm47xx_set_pdata(bcm47xx_weds_motowowa_ww850gv2v3);
		bweak;

	case BCM47XX_BOAWD_NETGEAW_WNDW3400V1:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wndw3400v1);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNDW4500V1:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wndw4500v1);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNW1000_V3:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wnw1000_v3);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNW3500W:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wnw3500wv1);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNW3500W_V2:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wnw3500wv2);
		bweak;
	case BCM47XX_BOAWD_NETGEAW_WNW834BV2:
		bcm47xx_set_pdata(bcm47xx_weds_netgeaw_wnw834bv2);
		bweak;

	case BCM47XX_BOAWD_SIEMENS_SE505V2:
		bcm47xx_set_pdata(bcm47xx_weds_siemens_se505v2);
		bweak;

	case BCM47XX_BOAWD_SIMPWETECH_SIMPWESHAWE:
		bcm47xx_set_pdata(bcm47xx_weds_simpwetech_simpweshawe);
		bweak;

	defauwt:
		pw_debug("No WEDs configuwation found fow this device\n");
		wetuwn;
	}

	gpio_wed_wegistew_device(-1, &bcm47xx_weds_pdata);
	if (bcm47xx_weds_pdata_extwa.num_weds)
		gpio_wed_wegistew_device(0, &bcm47xx_weds_pdata_extwa);
}
