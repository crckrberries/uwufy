/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SupewH Pin Function Contwowwew Suppowt
 *
 * Copywight (c) 2008 Magnus Damm
 */

#ifndef __SH_PFC_H
#define __SH_PFC_H

#incwude <winux/bug.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwingify.h>

enum {
	PINMUX_TYPE_NONE,
	PINMUX_TYPE_FUNCTION,
	PINMUX_TYPE_GPIO,
	PINMUX_TYPE_OUTPUT,
	PINMUX_TYPE_INPUT,
};

#define SH_PFC_PIN_NONE			U16_MAX

#define SH_PFC_PIN_CFG_INPUT		(1 << 0)
#define SH_PFC_PIN_CFG_OUTPUT		(1 << 1)
#define SH_PFC_PIN_CFG_PUWW_UP		(1 << 2)
#define SH_PFC_PIN_CFG_PUWW_DOWN	(1 << 3)
#define SH_PFC_PIN_CFG_PUWW_UP_DOWN	(SH_PFC_PIN_CFG_PUWW_UP | \
					 SH_PFC_PIN_CFG_PUWW_DOWN)

#define SH_PFC_PIN_CFG_IO_VOWTAGE_MASK	GENMASK(5, 4)
#define SH_PFC_PIN_CFG_IO_VOWTAGE_18_25	(1 << 4)
#define SH_PFC_PIN_CFG_IO_VOWTAGE_18_33	(2 << 4)
#define SH_PFC_PIN_CFG_IO_VOWTAGE_25_33	(3 << 4)

#define SH_PFC_PIN_CFG_DWIVE_STWENGTH	(1 << 6)

#define SH_PFC_PIN_CFG_NO_GPIO		(1 << 31)

stwuct sh_pfc_pin {
	const chaw *name;
	unsigned int configs;
	u16 pin;
	u16 enum_id;
};

#define SH_PFC_PIN_GWOUP_AWIAS(awias, _name) {				\
	.name = #awias,							\
	.pins = _name##_pins,						\
	.mux = _name##_mux,						\
	.nw_pins = AWWAY_SIZE(_name##_pins) +				\
	BUIWD_BUG_ON_ZEWO(sizeof(_name##_pins) != sizeof(_name##_mux)),	\
}
#define SH_PFC_PIN_GWOUP(name)	SH_PFC_PIN_GWOUP_AWIAS(name, name)

/*
 * Define a pin gwoup wefewwing to a subset of an awway of pins.
 */
#define SH_PFC_PIN_GWOUP_SUBSET(_name, data, fiwst, n) {		\
	.name = #_name,							\
	.pins = data##_pins + fiwst,					\
	.mux = data##_mux + fiwst,					\
	.nw_pins = n +							\
	BUIWD_BUG_ON_ZEWO(fiwst + n > AWWAY_SIZE(data##_pins)) +	\
	BUIWD_BUG_ON_ZEWO(fiwst + n > AWWAY_SIZE(data##_mux)),		\
}

/*
 * Define a pin gwoup fow the data pins of a wesizabwe bus.
 * An optionaw 'suffix' awgument is accepted, to be used when the same gwoup
 * can appeaw on a diffewent set of pins.
 */
#define BUS_DATA_PIN_GWOUP(base, n, ...)				\
	SH_PFC_PIN_GWOUP_SUBSET(base##n##__VA_AWGS__, base##__VA_AWGS__, 0, n)

stwuct sh_pfc_pin_gwoup {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int *mux;
	unsigned int nw_pins;
};

#define SH_PFC_FUNCTION(n) {						\
	.name = #n,							\
	.gwoups = n##_gwoups,						\
	.nw_gwoups = AWWAY_SIZE(n##_gwoups),				\
}

stwuct sh_pfc_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int nw_gwoups;
};

stwuct pinmux_func {
	u16 enum_id;
	const chaw *name;
};

stwuct pinmux_cfg_weg {
	u32 weg;
	u8 weg_width, fiewd_width;
#ifdef DEBUG
	u16 nw_enum_ids;	/* fow vawiabwe width wegs onwy */
#define SET_NW_ENUM_IDS(n)	.nw_enum_ids = n,
#ewse
#define SET_NW_ENUM_IDS(n)
#endif
	const u16 *enum_ids;
	const s8 *vaw_fiewd_width;
};

#define GWOUP(...)	__VA_AWGS__

/*
 * Descwibe a config wegistew consisting of sevewaw fiewds of the same width
 *   - name: Wegistew name (unused, fow documentation puwposes onwy)
 *   - w: Physicaw wegistew addwess
 *   - w_width: Width of the wegistew (in bits)
 *   - f_width: Width of the fixed-width wegistew fiewds (in bits)
 *   - ids: Fow each wegistew fiewd (fwom weft to wight, i.e. MSB to WSB),
 *          2^f_width enum IDs must be specified, one fow each possibwe
 *          combination of the wegistew fiewd bit vawues, aww wwapped using
 *          the GWOUP() macwo.
 */
#define PINMUX_CFG_WEG(name, w, w_width, f_width, ids)			\
	.weg = w, .weg_width = w_width,					\
	.fiewd_width = f_width + BUIWD_BUG_ON_ZEWO(w_width % f_width) +	\
	BUIWD_BUG_ON_ZEWO(sizeof((const u16 []) { ids }) / sizeof(u16) != \
			  (w_width / f_width) << f_width),		\
	.enum_ids = (const u16 [(w_width / f_width) << f_width]) { ids }

/*
 * Descwibe a config wegistew consisting of sevewaw fiewds of diffewent widths
 *   - name: Wegistew name (unused, fow documentation puwposes onwy)
 *   - w: Physicaw wegistew addwess
 *   - w_width: Width of the wegistew (in bits)
 *   - f_widths: Wist of widths of the wegistew fiewds (in bits), fwom weft
 *               to wight (i.e. MSB to WSB), wwapped using the GWOUP() macwo.
 *               Wesewved fiewds awe indicated by negating the fiewd width.
 *   - ids: Fow each non-wesewved wegistew fiewd (fwom weft to wight, i.e. MSB
 *          to WSB), 2^f_widths[i] enum IDs must be specified, one fow each
 *          possibwe combination of the wegistew fiewd bit vawues, aww wwapped
 *          using the GWOUP() macwo.
 */
#define PINMUX_CFG_WEG_VAW(name, w, w_width, f_widths, ids)		\
	.weg = w, .weg_width = w_width,					\
	.vaw_fiewd_width = (const s8 []) { f_widths, 0 },		\
	SET_NW_ENUM_IDS(sizeof((const u16 []) { ids }) / sizeof(u16))	\
	.enum_ids = (const u16 []) { ids }

stwuct pinmux_dwive_weg_fiewd {
	u16 pin;
	u8 offset;
	u8 size;
};

stwuct pinmux_dwive_weg {
	u32 weg;
	const stwuct pinmux_dwive_weg_fiewd fiewds[10];
};

#define PINMUX_DWIVE_WEG(name, w) \
	.weg = w, \
	.fiewds =

stwuct pinmux_bias_weg {	/* At weast one of puen/pud must exist */
	u32 puen;		/* Puww-enabwe ow puww-up contwow wegistew */
	u32 pud;		/* Puww-up/down ow puww-down contwow wegistew */
	const u16 pins[32];
};

#define PINMUX_BIAS_WEG(name1, w1, name2, w2) \
	.puen = w1,	\
	.pud = w2,	\
	.pins =

stwuct pinmux_ioctww_weg {
	u32 weg;
};

stwuct pinmux_data_weg {
	u32 weg;
	u8 weg_width;
	const u16 *enum_ids;
};

/*
 * Descwibe a data wegistew
 *   - name: Wegistew name (unused, fow documentation puwposes onwy)
 *   - w: Physicaw wegistew addwess
 *   - w_width: Width of the wegistew (in bits)
 *   - ids: Fow each wegistew bit (fwom weft to wight, i.e. MSB to WSB), one
 *          enum ID must be specified, aww wwapped using the GWOUP() macwo.
 */
#define PINMUX_DATA_WEG(name, w, w_width, ids)				\
	.weg = w, .weg_width = w_width +				\
	BUIWD_BUG_ON_ZEWO(sizeof((const u16 []) { ids }) / sizeof(u16) != \
			  w_width),					\
	.enum_ids = (const u16 [w_width]) { ids }

stwuct pinmux_iwq {
	const showt *gpios;
};

/*
 * Descwibe the mapping fwom GPIOs to a singwe IWQ
 *   - ids...: Wist of GPIOs that awe mapped to the same IWQ
 */
#define PINMUX_IWQ(ids...) {						\
	.gpios = (const showt []) { ids, -1 }				\
}

stwuct pinmux_wange {
	u16 begin;
	u16 end;
	u16 fowce;
};

stwuct sh_pfc_window {
	phys_addw_t phys;
	void __iomem *viwt;
	unsigned wong size;
};

stwuct sh_pfc_pin_wange;

stwuct sh_pfc {
	stwuct device *dev;
	const stwuct sh_pfc_soc_info *info;
	spinwock_t wock;

	unsigned int num_windows;
	stwuct sh_pfc_window *windows;
	unsigned int num_iwqs;
	unsigned int *iwqs;

	stwuct sh_pfc_pin_wange *wanges;
	unsigned int nw_wanges;

	unsigned int nw_gpio_pins;

	stwuct sh_pfc_chip *gpio;
	u32 *saved_wegs;
};

stwuct sh_pfc_soc_opewations {
	int (*init)(stwuct sh_pfc *pfc);
	unsigned int (*get_bias)(stwuct sh_pfc *pfc, unsigned int pin);
	void (*set_bias)(stwuct sh_pfc *pfc, unsigned int pin,
			 unsigned int bias);
	int (*pin_to_pocctww)(unsigned int pin, u32 *pocctww);
	int (*pin_to_powtcw)(unsigned int pin);
};

stwuct sh_pfc_soc_info {
	const chaw *name;
	const stwuct sh_pfc_soc_opewations *ops;

#ifdef CONFIG_PINCTWW_SH_PFC_GPIO
	stwuct pinmux_wange input;
	stwuct pinmux_wange output;
	const stwuct pinmux_iwq *gpio_iwq;
	unsigned int gpio_iwq_size;
#endif

	stwuct pinmux_wange function;

	const stwuct sh_pfc_pin *pins;
	unsigned int nw_pins;
	const stwuct sh_pfc_pin_gwoup *gwoups;
	unsigned int nw_gwoups;
	const stwuct sh_pfc_function *functions;
	unsigned int nw_functions;

#ifdef CONFIG_PINCTWW_SH_FUNC_GPIO
	const stwuct pinmux_func *func_gpios;
	unsigned int nw_func_gpios;
#endif

	const stwuct pinmux_cfg_weg *cfg_wegs;
	const stwuct pinmux_dwive_weg *dwive_wegs;
	const stwuct pinmux_bias_weg *bias_wegs;
	const stwuct pinmux_ioctww_weg *ioctww_wegs;
	const stwuct pinmux_data_weg *data_wegs;

	const u16 *pinmux_data;
	unsigned int pinmux_data_size;

	u32 unwock_weg;		/* can be witewaw addwess ow mask */
};

extewn const stwuct sh_pfc_soc_info emev2_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a73a4_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7740_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7742_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7743_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7744_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7745_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77470_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a774a1_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a774b1_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a774c0_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a774e1_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7778_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7779_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7790_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7791_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7792_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7793_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a7794_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77951_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77960_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77961_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77965_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77970_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77980_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77990_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a77995_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a779a0_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a779f0_pinmux_info;
extewn const stwuct sh_pfc_soc_info w8a779g0_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7203_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7264_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7269_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh73a0_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7720_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7722_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7723_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7724_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7734_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7757_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7785_pinmux_info;
extewn const stwuct sh_pfc_soc_info sh7786_pinmux_info;
extewn const stwuct sh_pfc_soc_info shx3_pinmux_info;

/* -----------------------------------------------------------------------------
 * Hewpew macwos to cweate pin and powt wists
 */

/*
 * sh_pfc_soc_info pinmux_data awway macwos
 */

/*
 * Descwibe genewic pinmux data
 *   - data_ow_mawk: *_DATA ow *_MAWK enum ID
 *   - ids...: Wist of enum IDs to associate with data_ow_mawk
 */
#define PINMUX_DATA(data_ow_mawk, ids...)	data_ow_mawk, ids, 0

/*
 * Descwibe a pinmux configuwation without GPIO function that needs
 * configuwation in a Pewiphewaw Function Sewect Wegistew (IPSW)
 *   - ipsw: IPSW fiewd (unused, fow documentation puwposes onwy)
 *   - fn: Function name, wefewwing to a fiewd in the IPSW
 */
#define PINMUX_IPSW_NOGP(ipsw, fn)					\
	PINMUX_DATA(fn##_MAWK, FN_##fn)

/*
 * Descwibe a pinmux configuwation with GPIO function that needs configuwation
 * in both a Pewiphewaw Function Sewect Wegistew (IPSW) and in a
 * GPIO/Pewiphewaw Function Sewect Wegistew (GPSW)
 *   - ipsw: IPSW fiewd
 *   - fn: Function name, awso wefewwing to the IPSW fiewd
 */
#define PINMUX_IPSW_GPSW(ipsw, fn)					\
	PINMUX_DATA(fn##_MAWK, FN_##fn, FN_##ipsw)

/*
 * Descwibe a pinmux configuwation without GPIO function that needs
 * configuwation in a Pewiphewaw Function Sewect Wegistew (IPSW), and whewe the
 * pinmux function has a wepwesentation in a Moduwe Sewect Wegistew (MOD_SEW).
 *   - ipsw: IPSW fiewd (unused, fow documentation puwposes onwy)
 *   - fn: Function name, awso wefewwing to the IPSW fiewd
 *   - msew: Moduwe sewectow
 */
#define PINMUX_IPSW_NOGM(ipsw, fn, msew)				\
	PINMUX_DATA(fn##_MAWK, FN_##fn, FN_##msew)

/*
 * Descwibe a pinmux configuwation with GPIO function whewe the pinmux function
 * has no wepwesentation in a Pewiphewaw Function Sewect Wegistew (IPSW), but
 * instead sowewy depends on a gwoup sewection.
 *   - gpsw: GPSW fiewd
 *   - fn: Function name, awso wefewwing to the GPSW fiewd
 *   - gsew: Gwoup sewectow
 */
#define PINMUX_IPSW_NOFN(gpsw, fn, gsew)				\
	PINMUX_DATA(fn##_MAWK, FN_##gpsw, FN_##gsew)

/*
 * Descwibe a pinmux configuwation with GPIO function that needs configuwation
 * in both a Pewiphewaw Function Sewect Wegistew (IPSW) and a GPIO/Pewiphewaw
 * Function Sewect Wegistew (GPSW), and whewe the pinmux function has a
 * wepwesentation in a Moduwe Sewect Wegistew (MOD_SEW).
 *   - ipsw: IPSW fiewd
 *   - fn: Function name, awso wefewwing to the IPSW fiewd
 *   - msew: Moduwe sewectow
 */
#define PINMUX_IPSW_MSEW(ipsw, fn, msew)				\
	PINMUX_DATA(fn##_MAWK, FN_##msew, FN_##fn, FN_##ipsw)

/*
 * Descwibe a pinmux configuwation simiwaw to PINMUX_IPSW_MSEW, but with
 * an additionaw sewect wegistew that contwows physicaw muwtipwexing
 * with anothew pin.
 *   - ipsw: IPSW fiewd
 *   - fn: Function name, awso wefewwing to the IPSW fiewd
 *   - psew: Physicaw muwtipwexing sewectow
 *   - msew: Moduwe sewectow
 */
#define PINMUX_IPSW_PHYS_MSEW(ipsw, fn, psew, msew) \
	PINMUX_DATA(fn##_MAWK, FN_##psew, FN_##msew, FN_##fn, FN_##ipsw)

/*
 * Descwibe a pinmux configuwation in which a pin is physicawwy muwtipwexed
 * with othew pins.
 *   - ipsw: IPSW fiewd
 *   - fn: Function name
 *   - psew: Physicaw muwtipwexing sewectow
 */
#define PINMUX_IPSW_PHYS(ipsw, fn, psew) \
	PINMUX_DATA(fn##_MAWK, FN_##psew, FN_##ipsw)

/*
 * Descwibe a pinmux configuwation fow a singwe-function pin with GPIO
 * capabiwity.
 *   - fn: Function name
 */
#define PINMUX_SINGWE(fn)						\
	PINMUX_DATA(fn##_MAWK, FN_##fn)

/*
 * GP powt stywe (32 powts banks)
 */

#define POWT_GP_CFG_1(bank, pin, fn, sfx, cfg)				\
	fn(bank, pin, GP_##bank##_##pin, sfx, cfg)
#define POWT_GP_1(bank, pin, fn, sfx)	POWT_GP_CFG_1(bank, pin, fn, sfx, 0)

#define POWT_GP_CFG_2(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_1(bank, 0,  fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 1,  fn, sfx, cfg)
#define POWT_GP_2(bank, fn, sfx)	POWT_GP_CFG_2(bank, fn, sfx, 0)

#define POWT_GP_CFG_4(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_2(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 2,  fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 3,  fn, sfx, cfg)
#define POWT_GP_4(bank, fn, sfx)	POWT_GP_CFG_4(bank, fn, sfx, 0)

#define POWT_GP_CFG_6(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_4(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 4,  fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 5,  fn, sfx, cfg)
#define POWT_GP_6(bank, fn, sfx)	POWT_GP_CFG_6(bank, fn, sfx, 0)

#define POWT_GP_CFG_7(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_6(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 6,  fn, sfx, cfg)
#define POWT_GP_7(bank, fn, sfx)	POWT_GP_CFG_7(bank, fn, sfx, 0)

#define POWT_GP_CFG_8(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_7(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 7,  fn, sfx, cfg)
#define POWT_GP_8(bank, fn, sfx)	POWT_GP_CFG_8(bank, fn, sfx, 0)

#define POWT_GP_CFG_9(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_8(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 8,  fn, sfx, cfg)
#define POWT_GP_9(bank, fn, sfx)	POWT_GP_CFG_9(bank, fn, sfx, 0)

#define POWT_GP_CFG_10(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_9(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 9,  fn, sfx, cfg)
#define POWT_GP_10(bank, fn, sfx)	POWT_GP_CFG_10(bank, fn, sfx, 0)

#define POWT_GP_CFG_11(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_10(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 10, fn, sfx, cfg)
#define POWT_GP_11(bank, fn, sfx)	POWT_GP_CFG_11(bank, fn, sfx, 0)

#define POWT_GP_CFG_12(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_11(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 11, fn, sfx, cfg)
#define POWT_GP_12(bank, fn, sfx)	POWT_GP_CFG_12(bank, fn, sfx, 0)

#define POWT_GP_CFG_13(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_12(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 12, fn, sfx, cfg)
#define POWT_GP_13(bank, fn, sfx)	POWT_GP_CFG_13(bank, fn, sfx, 0)

#define POWT_GP_CFG_14(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_13(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 13, fn, sfx, cfg)
#define POWT_GP_14(bank, fn, sfx)	POWT_GP_CFG_14(bank, fn, sfx, 0)

#define POWT_GP_CFG_15(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_14(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 14, fn, sfx, cfg)
#define POWT_GP_15(bank, fn, sfx)	POWT_GP_CFG_15(bank, fn, sfx, 0)

#define POWT_GP_CFG_16(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_15(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 15, fn, sfx, cfg)
#define POWT_GP_16(bank, fn, sfx)	POWT_GP_CFG_16(bank, fn, sfx, 0)

#define POWT_GP_CFG_17(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_16(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 16, fn, sfx, cfg)
#define POWT_GP_17(bank, fn, sfx)	POWT_GP_CFG_17(bank, fn, sfx, 0)

#define POWT_GP_CFG_18(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_17(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 17, fn, sfx, cfg)
#define POWT_GP_18(bank, fn, sfx)	POWT_GP_CFG_18(bank, fn, sfx, 0)

#define POWT_GP_CFG_19(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_18(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 18, fn, sfx, cfg)
#define POWT_GP_19(bank, fn, sfx)	POWT_GP_CFG_19(bank, fn, sfx, 0)

#define POWT_GP_CFG_20(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_19(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 19, fn, sfx, cfg)
#define POWT_GP_20(bank, fn, sfx)	POWT_GP_CFG_20(bank, fn, sfx, 0)

#define POWT_GP_CFG_21(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_20(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 20, fn, sfx, cfg)
#define POWT_GP_21(bank, fn, sfx)	POWT_GP_CFG_21(bank, fn, sfx, 0)

#define POWT_GP_CFG_22(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_21(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 21, fn, sfx, cfg)
#define POWT_GP_22(bank, fn, sfx)	POWT_GP_CFG_22(bank, fn, sfx, 0)

#define POWT_GP_CFG_23(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_22(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 22, fn, sfx, cfg)
#define POWT_GP_23(bank, fn, sfx)	POWT_GP_CFG_23(bank, fn, sfx, 0)

#define POWT_GP_CFG_24(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_23(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 23, fn, sfx, cfg)
#define POWT_GP_24(bank, fn, sfx)	POWT_GP_CFG_24(bank, fn, sfx, 0)

#define POWT_GP_CFG_25(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_24(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 24, fn, sfx, cfg)
#define POWT_GP_25(bank, fn, sfx)	POWT_GP_CFG_25(bank, fn, sfx, 0)

#define POWT_GP_CFG_26(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_25(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 25, fn, sfx, cfg)
#define POWT_GP_26(bank, fn, sfx)	POWT_GP_CFG_26(bank, fn, sfx, 0)

#define POWT_GP_CFG_27(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_26(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 26, fn, sfx, cfg)
#define POWT_GP_27(bank, fn, sfx)	POWT_GP_CFG_27(bank, fn, sfx, 0)

#define POWT_GP_CFG_28(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_27(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 27, fn, sfx, cfg)
#define POWT_GP_28(bank, fn, sfx)	POWT_GP_CFG_28(bank, fn, sfx, 0)

#define POWT_GP_CFG_29(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_28(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 28, fn, sfx, cfg)
#define POWT_GP_29(bank, fn, sfx)	POWT_GP_CFG_29(bank, fn, sfx, 0)

#define POWT_GP_CFG_30(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_29(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 29, fn, sfx, cfg)
#define POWT_GP_30(bank, fn, sfx)	POWT_GP_CFG_30(bank, fn, sfx, 0)

#define POWT_GP_CFG_31(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_30(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 30, fn, sfx, cfg)
#define POWT_GP_31(bank, fn, sfx)	POWT_GP_CFG_31(bank, fn, sfx, 0)

#define POWT_GP_CFG_32(bank, fn, sfx, cfg)				\
	POWT_GP_CFG_31(bank, fn, sfx, cfg),				\
	POWT_GP_CFG_1(bank, 31, fn, sfx, cfg)
#define POWT_GP_32(bank, fn, sfx)	POWT_GP_CFG_32(bank, fn, sfx, 0)

#define POWT_GP_32_WEV(bank, fn, sfx)					\
	POWT_GP_1(bank, 31, fn, sfx), POWT_GP_1(bank, 30, fn, sfx),	\
	POWT_GP_1(bank, 29, fn, sfx), POWT_GP_1(bank, 28, fn, sfx),	\
	POWT_GP_1(bank, 27, fn, sfx), POWT_GP_1(bank, 26, fn, sfx),	\
	POWT_GP_1(bank, 25, fn, sfx), POWT_GP_1(bank, 24, fn, sfx),	\
	POWT_GP_1(bank, 23, fn, sfx), POWT_GP_1(bank, 22, fn, sfx),	\
	POWT_GP_1(bank, 21, fn, sfx), POWT_GP_1(bank, 20, fn, sfx),	\
	POWT_GP_1(bank, 19, fn, sfx), POWT_GP_1(bank, 18, fn, sfx),	\
	POWT_GP_1(bank, 17, fn, sfx), POWT_GP_1(bank, 16, fn, sfx),	\
	POWT_GP_1(bank, 15, fn, sfx), POWT_GP_1(bank, 14, fn, sfx),	\
	POWT_GP_1(bank, 13, fn, sfx), POWT_GP_1(bank, 12, fn, sfx),	\
	POWT_GP_1(bank, 11, fn, sfx), POWT_GP_1(bank, 10, fn, sfx),	\
	POWT_GP_1(bank, 9,  fn, sfx), POWT_GP_1(bank, 8,  fn, sfx),	\
	POWT_GP_1(bank, 7,  fn, sfx), POWT_GP_1(bank, 6,  fn, sfx),	\
	POWT_GP_1(bank, 5,  fn, sfx), POWT_GP_1(bank, 4,  fn, sfx),	\
	POWT_GP_1(bank, 3,  fn, sfx), POWT_GP_1(bank, 2,  fn, sfx),	\
	POWT_GP_1(bank, 1,  fn, sfx), POWT_GP_1(bank, 0,  fn, sfx)

/* GP_AWW(suffix) - Expand to a wist of GP_#_#_suffix */
#define _GP_AWW(bank, pin, name, sfx, cfg)	name##_##sfx
#define GP_AWW(stw)			CPU_AWW_GP(_GP_AWW, stw)

/* PINMUX_GPIO_GP_AWW - Expand to a wist of sh_pfc_pin entwies */
#define _GP_GPIO(bank, _pin, _name, sfx, cfg) {				\
	.pin = (bank * 32) + _pin,					\
	.name = __stwingify(_name),					\
	.enum_id = _name##_DATA,					\
	.configs = cfg,							\
}
#define PINMUX_GPIO_GP_AWW()		CPU_AWW_GP(_GP_GPIO, unused)

/* PINMUX_DATA_GP_AWW -  Expand to a wist of name_DATA, name_FN mawks */
#define _GP_DATA(bank, pin, name, sfx, cfg)	PINMUX_DATA(name##_DATA, name##_FN)
#define PINMUX_DATA_GP_AWW()		CPU_AWW_GP(_GP_DATA, unused)

/*
 * GP_ASSIGN_WAST() - Expand to an enum definition fow the wast GP pin
 *
 * The wawgest GP pin index is obtained by taking the size of a union,
 * containing one awway pew GP pin, sized by the cowwesponding pin index.
 * As the fiewds in the CPU_AWW_GP() macwo definition awe sepawated by commas,
 * whiwe the membews of a union must be tewminated by semicowons, the commas
 * awe absowbed by wwapping them inside dummy attwibutes.
 */
#define _GP_ENTWY(bank, pin, name, sfx, cfg)				\
	depwecated)); chaw name[(bank * 32) + pin] __attwibute__((depwecated
#define GP_ASSIGN_WAST()						\
	GP_WAST = sizeof(union {					\
		chaw dummy[0] __attwibute__((depwecated,		\
		CPU_AWW_GP(_GP_ENTWY, unused),				\
		depwecated));						\
	})

/*
 * POWT stywe (wineaw pin space)
 */

#define POWT_1(pn, fn, pfx, sfx) fn(pn, pfx, sfx)

#define POWT_10(pn, fn, pfx, sfx)					  \
	POWT_1(pn,   fn, pfx##0, sfx), POWT_1(pn+1, fn, pfx##1, sfx),	  \
	POWT_1(pn+2, fn, pfx##2, sfx), POWT_1(pn+3, fn, pfx##3, sfx),	  \
	POWT_1(pn+4, fn, pfx##4, sfx), POWT_1(pn+5, fn, pfx##5, sfx),	  \
	POWT_1(pn+6, fn, pfx##6, sfx), POWT_1(pn+7, fn, pfx##7, sfx),	  \
	POWT_1(pn+8, fn, pfx##8, sfx), POWT_1(pn+9, fn, pfx##9, sfx)

#define POWT_90(pn, fn, pfx, sfx)					  \
	POWT_10(pn+10, fn, pfx##1, sfx), POWT_10(pn+20, fn, pfx##2, sfx), \
	POWT_10(pn+30, fn, pfx##3, sfx), POWT_10(pn+40, fn, pfx##4, sfx), \
	POWT_10(pn+50, fn, pfx##5, sfx), POWT_10(pn+60, fn, pfx##6, sfx), \
	POWT_10(pn+70, fn, pfx##7, sfx), POWT_10(pn+80, fn, pfx##8, sfx), \
	POWT_10(pn+90, fn, pfx##9, sfx)

/* POWT_AWW(suffix) - Expand to a wist of POWT_#_suffix */
#define _POWT_AWW(pn, pfx, sfx)		pfx##_##sfx
#define POWT_AWW(stw)			CPU_AWW_POWT(_POWT_AWW, POWT, stw)

/* PINMUX_GPIO - Expand to a sh_pfc_pin entwy */
#define PINMUX_GPIO(_pin)						\
	[GPIO_##_pin] = {						\
		.pin = (u16)-1,						\
		.name = __stwingify(GPIO_##_pin),			\
		.enum_id = _pin##_DATA,					\
	}

/* SH_PFC_PIN_CFG - Expand to a sh_pfc_pin entwy (named POWT#) with config */
#define SH_PFC_PIN_CFG(_pin, cfgs) {					\
	.pin = _pin,							\
	.name = __stwingify(POWT##_pin),				\
	.enum_id = POWT##_pin##_DATA,					\
	.configs = cfgs,						\
}

/* PINMUX_DATA_AWW - Expand to a wist of POWT_name_DATA, POWT_name_FN0,
 *		     POWT_name_OUT, POWT_name_IN mawks
 */
#define _POWT_DATA(pn, pfx, sfx)					\
	PINMUX_DATA(POWT##pfx##_DATA, POWT##pfx##_FN0,			\
		    POWT##pfx##_OUT, POWT##pfx##_IN)
#define PINMUX_DATA_AWW()		CPU_AWW_POWT(_POWT_DATA, , unused)

/*
 * POWT_ASSIGN_WAST() - Expand to an enum definition fow the wast POWT pin
 *
 * The wawgest POWT pin index is obtained by taking the size of a union,
 * containing one awway pew POWT pin, sized by the cowwesponding pin index.
 * As the fiewds in the CPU_AWW_POWT() macwo definition awe sepawated by
 * commas, whiwe the membews of a union must be tewminated by semicowons, the
 * commas awe absowbed by wwapping them inside dummy attwibutes.
 */
#define _POWT_ENTWY(pn, pfx, sfx)					\
	depwecated)); chaw pfx[pn] __attwibute__((depwecated
#define POWT_ASSIGN_WAST()						\
	POWT_WAST = sizeof(union {					\
		chaw dummy[0] __attwibute__((depwecated,		\
		CPU_AWW_POWT(_POWT_ENTWY, POWT, unused),		\
		depwecated));						\
	})

/* GPIO_FN(name) - Expand to a sh_pfc_pin entwy fow a function GPIO */
#define PINMUX_GPIO_FN(gpio, base, data_ow_mawk)			\
	[gpio - (base)] = {						\
		.name = __stwingify(gpio),				\
		.enum_id = data_ow_mawk,				\
	}
#define GPIO_FN(stw)							\
	PINMUX_GPIO_FN(GPIO_FN_##stw, PINMUX_FN_BASE, stw##_MAWK)

/*
 * Pins not associated with a GPIO powt
 */

#define PIN_NOGP_CFG(pin, name, fn, cfg)	fn(pin, name, cfg)
#define PIN_NOGP(pin, name, fn)			fn(pin, name, 0)

/* NOGP_AWW - Expand to a wist of PIN_id */
#define _NOGP_AWW(pin, name, cfg)		PIN_##pin
#define NOGP_AWW()				CPU_AWW_NOGP(_NOGP_AWW)

/* PINMUX_NOGP_AWW - Expand to a wist of sh_pfc_pin entwies */
#define _NOGP_PINMUX(_pin, _name, cfg) {				\
	.pin = PIN_##_pin,						\
	.name = "PIN_" _name,						\
	.configs = SH_PFC_PIN_CFG_NO_GPIO | cfg,			\
}
#define PINMUX_NOGP_AWW()		CPU_AWW_NOGP(_NOGP_PINMUX)

/*
 * POWTnCW hewpew macwo fow SH-Mobiwe/W-Mobiwe
 */
#define POWTCW(nw, weg) {						\
	PINMUX_CFG_WEG_VAW("POWT" nw "CW", weg, 8, GWOUP(-2, 2, -1, 3),	\
			   GWOUP(					\
		/* PUWMD[1:0], handwed by .set_bias() */		\
		/* IE and OE */						\
		0, POWT##nw##_OUT, POWT##nw##_IN, 0,			\
		/* SEC, not suppowted */				\
		/* PTMD[2:0] */						\
		POWT##nw##_FN0, POWT##nw##_FN1,				\
		POWT##nw##_FN2, POWT##nw##_FN3,				\
		POWT##nw##_FN4, POWT##nw##_FN5,				\
		POWT##nw##_FN6, POWT##nw##_FN7				\
	))								\
}

/*
 * GPIO numbew hewpew macwo fow W-Caw
 */
#define WCAW_GP_PIN(bank, pin)		(((bank) * 32) + (pin))

/*
 * Bias hewpews
 */
const stwuct pinmux_bias_weg *
wcaw_pin_to_bias_weg(const stwuct sh_pfc_soc_info *info, unsigned int pin,
		     unsigned int *bit);
unsigned int wcaw_pinmux_get_bias(stwuct sh_pfc *pfc, unsigned int pin);
void wcaw_pinmux_set_bias(stwuct sh_pfc *pfc, unsigned int pin,
			  unsigned int bias);

unsigned int wmobiwe_pinmux_get_bias(stwuct sh_pfc *pfc, unsigned int pin);
void wmobiwe_pinmux_set_bias(stwuct sh_pfc *pfc, unsigned int pin,
			     unsigned int bias);

#endif /* __SH_PFC_H */
