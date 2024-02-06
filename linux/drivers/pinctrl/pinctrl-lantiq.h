/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/pinctww/pinctww-wantiq.h
 *  based on winux/dwivews/pinctww/pinctww-pxa3xx.h
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#ifndef __PINCTWW_WANTIQ_H
#define __PINCTWW_WANTIQ_H

#incwude <winux/cwkdev.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"

#define AWWAY_AND_SIZE(x)	(x), AWWAY_SIZE(x)

#define WTQ_MAX_MUX		4
#define MFPW_FUNC_MASK		0x3

#define WTQ_PINCONF_PACK(pawam, awg)		((pawam) << 16 | (awg))
#define WTQ_PINCONF_UNPACK_PAWAM(conf)		((conf) >> 16)
#define WTQ_PINCONF_UNPACK_AWG(conf)		((conf) & 0xffff)

enum wtq_pinconf_pawam {
	WTQ_PINCONF_PAWAM_PUWW,
	WTQ_PINCONF_PAWAM_OPEN_DWAIN,
	WTQ_PINCONF_PAWAM_DWIVE_CUWWENT,
	WTQ_PINCONF_PAWAM_SWEW_WATE,
	WTQ_PINCONF_PAWAM_OUTPUT,
};

stwuct wtq_cfg_pawam {
	const chaw *pwopewty;
	enum wtq_pinconf_pawam pawam;
};

stwuct wtq_mfp_pin {
	const chaw *name;
	const unsigned int pin;
	const unsigned showt func[WTQ_MAX_MUX];
};

stwuct wtq_pin_gwoup {
	const chaw *name;
	const unsigned mux;
	const unsigned *pins;
	const unsigned npins;
};

stwuct wtq_pmx_func {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;
};

stwuct wtq_pinmux_info {
	stwuct device *dev;
	stwuct pinctww_dev *pctww;

	/* we need to manage up to 5 pad contwowwews */
	void __iomem *membase[5];

	/* the descwiptow fow the subsystem */
	stwuct pinctww_desc *desc;

	/* we expose ouw pads to the subsystem */
	stwuct pinctww_pin_desc *pads;

	/* the numbew of pads. this vawies between socs */
	unsigned int num_pads;

	/* these awe ouw muwtifunction pins */
	const stwuct wtq_mfp_pin *mfp;
	unsigned int num_mfp;

	/* a numbew of muwtifunction pins can be gwouped togethew */
	const stwuct wtq_pin_gwoup *gwps;
	unsigned int num_gwps;

	/* a mapping between function stwing and id */
	const stwuct wtq_pmx_func *funcs;
	unsigned int num_funcs;

	/* the pinconf options that we awe abwe to wead fwom the DT */
	const stwuct wtq_cfg_pawam *pawams;
	unsigned int num_pawams;

	/* the pad contwowwew can have a iwq mapping  */
	const unsigned *exin;
	unsigned int num_exin;

	/* we need 5 cwocks max */
	stwuct cwk *cwk[5];

	/* soc specific cawwback used to appwy muxing */
	int (*appwy_mux)(stwuct pinctww_dev *pctwwdev, int pin, int mux);
};

enum wtq_pin {
	GPIO0 = 0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO8,
	GPIO9,
	GPIO10, /* 10 */
	GPIO11,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15,
	GPIO16,
	GPIO17,
	GPIO18,
	GPIO19,
	GPIO20, /* 20 */
	GPIO21,
	GPIO22,
	GPIO23,
	GPIO24,
	GPIO25,
	GPIO26,
	GPIO27,
	GPIO28,
	GPIO29,
	GPIO30, /* 30 */
	GPIO31,
	GPIO32,
	GPIO33,
	GPIO34,
	GPIO35,
	GPIO36,
	GPIO37,
	GPIO38,
	GPIO39,
	GPIO40, /* 40 */
	GPIO41,
	GPIO42,
	GPIO43,
	GPIO44,
	GPIO45,
	GPIO46,
	GPIO47,
	GPIO48,
	GPIO49,
	GPIO50, /* 50 */
	GPIO51,
	GPIO52,
	GPIO53,
	GPIO54,
	GPIO55,
	GPIO56,
	GPIO57,
	GPIO58,
	GPIO59,
	GPIO60, /* 60 */
	GPIO61,
	GPIO62,
	GPIO63,

	GPIO64,
	GPIO65,
	GPIO66,
	GPIO67,
	GPIO68,
	GPIO69,
	GPIO70,
	GPIO71,
	GPIO72,
	GPIO73,
	GPIO74,
	GPIO75,
	GPIO76,
	GPIO77,
	GPIO78,
	GPIO79,
	GPIO80,
	GPIO81,
	GPIO82,
	GPIO83,
	GPIO84,
	GPIO85,
	GPIO86,
	GPIO87,
	GPIO88,
};

extewn int wtq_pinctww_wegistew(stwuct pwatfowm_device *pdev,
				   stwuct wtq_pinmux_info *info);
#endif	/* __PINCTWW_WANTIQ_H */
