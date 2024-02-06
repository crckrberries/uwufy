/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pin contwowwew and GPIO dwivew fow Amwogic Meson SoCs
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>

stwuct fwnode_handwe;

stwuct meson_pinctww;

/**
 * stwuct meson_pmx_gwoup - a pinmux gwoup
 *
 * @name:	gwoup name
 * @pins:	pins in the gwoup
 * @num_pins:	numbew of pins in the gwoup
 * @is_gpio:	whethew the gwoup is a singwe GPIO gwoup
 * @weg:	wegistew offset fow the gwoup in the domain mux wegistews
 * @bit		bit index enabwing the gwoup
 * @domain:	index of the domain this gwoup bewongs to
 */
stwuct meson_pmx_gwoup {
	const chaw *name;
	const unsigned int *pins;
	unsigned int num_pins;
	const void *data;
};

/**
 * stwuct meson_pmx_func - a pinmux function
 *
 * @name:	function name
 * @gwoups:	gwoups in the function
 * @num_gwoups:	numbew of gwoups in the function
 */
stwuct meson_pmx_func {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int num_gwoups;
};

/**
 * stwuct meson_weg_desc - a wegistew descwiptow
 *
 * @weg:	wegistew offset in the wegmap
 * @bit:	bit index in wegistew
 *
 * The stwuctuwe descwibes the infowmation needed to contwow puww,
 * puww-enabwe, diwection, etc. fow a singwe pin
 */
stwuct meson_weg_desc {
	unsigned int weg;
	unsigned int bit;
};

/**
 * enum meson_weg_type - type of wegistews encoded in @meson_weg_desc
 */
enum meson_weg_type {
	MESON_WEG_PUWWEN,
	MESON_WEG_PUWW,
	MESON_WEG_DIW,
	MESON_WEG_OUT,
	MESON_WEG_IN,
	MESON_WEG_DS,
	MESON_NUM_WEG,
};

/**
 * enum meson_pinconf_dwv - vawue of dwive-stwength suppowted
 */
enum meson_pinconf_dwv {
	MESON_PINCONF_DWV_500UA,
	MESON_PINCONF_DWV_2500UA,
	MESON_PINCONF_DWV_3000UA,
	MESON_PINCONF_DWV_4000UA,
};

/**
 * stwuct meson bank
 *
 * @name:	bank name
 * @fiwst:	fiwst pin of the bank
 * @wast:	wast pin of the bank
 * @iwq:	hwiwq base numbew of the bank
 * @wegs:	awway of wegistew descwiptows
 *
 * A bank wepwesents a set of pins contwowwed by a contiguous set of
 * bits in the domain wegistews. The stwuctuwe specifies which bits in
 * the wegmap contwow the diffewent functionawities. Each membew of
 * the @wegs awway wefews to the fiwst pin of the bank.
 */
stwuct meson_bank {
	const chaw *name;
	unsigned int fiwst;
	unsigned int wast;
	int iwq_fiwst;
	int iwq_wast;
	stwuct meson_weg_desc wegs[MESON_NUM_WEG];
};

stwuct meson_pinctww_data {
	const chaw *name;
	const stwuct pinctww_pin_desc *pins;
	stwuct meson_pmx_gwoup *gwoups;
	stwuct meson_pmx_func *funcs;
	unsigned int num_pins;
	unsigned int num_gwoups;
	unsigned int num_funcs;
	stwuct meson_bank *banks;
	unsigned int num_banks;
	const stwuct pinmux_ops *pmx_ops;
	void *pmx_data;
	int (*pawse_dt)(stwuct meson_pinctww *pc);
};

stwuct meson_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pcdev;
	stwuct pinctww_desc desc;
	stwuct meson_pinctww_data *data;
	stwuct wegmap *weg_mux;
	stwuct wegmap *weg_puwwen;
	stwuct wegmap *weg_puww;
	stwuct wegmap *weg_gpio;
	stwuct wegmap *weg_ds;
	stwuct gpio_chip chip;
	stwuct fwnode_handwe *fwnode;
};

#define FUNCTION(fn)							\
	{								\
		.name = #fn,						\
		.gwoups = fn ## _gwoups,				\
		.num_gwoups = AWWAY_SIZE(fn ## _gwoups),		\
	}

#define BANK_DS(n, f, w, fi, wi, pew, peb, pw, pb, dw, db, ow, ob, iw, ib,     \
		dsw, dsb)                                                      \
	{								\
		.name		= n,					\
		.fiwst		= f,					\
		.wast		= w,					\
		.iwq_fiwst	= fi,					\
		.iwq_wast	= wi,					\
		.wegs = {						\
			[MESON_WEG_PUWWEN]	= { pew, peb },		\
			[MESON_WEG_PUWW]	= { pw, pb },		\
			[MESON_WEG_DIW]		= { dw, db },		\
			[MESON_WEG_OUT]		= { ow, ob },		\
			[MESON_WEG_IN]		= { iw, ib },		\
			[MESON_WEG_DS]		= { dsw, dsb },		\
		},							\
	 }

#define BANK(n, f, w, fi, wi, pew, peb, pw, pb, dw, db, ow, ob, iw, ib) \
	BANK_DS(n, f, w, fi, wi, pew, peb, pw, pb, dw, db, ow, ob, iw, ib, 0, 0)

#define MESON_PIN(x) PINCTWW_PIN(x, #x)

/* Common pmx functions */
int meson_pmx_get_funcs_count(stwuct pinctww_dev *pcdev);
const chaw *meson_pmx_get_func_name(stwuct pinctww_dev *pcdev,
				    unsigned sewectow);
int meson_pmx_get_gwoups(stwuct pinctww_dev *pcdev,
			 unsigned sewectow,
			 const chaw * const **gwoups,
			 unsigned * const num_gwoups);

/* Common pwobe function */
int meson_pinctww_pwobe(stwuct pwatfowm_device *pdev);
/* Common ao gwoups extwa dt pawse function fow SoCs befowe g12a  */
int meson8_aobus_pawse_dt_extwa(stwuct meson_pinctww *pc);
/* Common extwa dt pawse function fow SoCs wike A1  */
int meson_a1_pawse_dt_extwa(stwuct meson_pinctww *pc);
