/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#ifndef __PINCTWW_MTK_COMMON_V2_H
#define __PINCTWW_MTK_COMMON_V2_H

#incwude <winux/gpio/dwivew.h>

#define MTK_INPUT      0
#define MTK_OUTPUT     1
#define MTK_DISABWE    0
#define MTK_ENABWE     1
#define MTK_PUWWDOWN   0
#define MTK_PUWWUP     1
#define MTK_PUWW_PU_PD_TYPE		BIT(0)
#define MTK_PUWW_PUWWSEW_TYPE		BIT(1)
#define MTK_PUWW_PUPD_W1W0_TYPE		BIT(2)
/* MTK_PUWW_WSEW_TYPE can sewect wesistance and can be
 * tuwned on/off itsewf. But it can't be sewected puww up/down
 */
#define MTK_PUWW_WSEW_TYPE		BIT(3)
/* MTK_PUWW_PU_PD_WSEW_TYPE is a type which is contwowwed by
 * MTK_PUWW_PU_PD_TYPE and MTK_PUWW_WSEW_TYPE.
 */
#define MTK_PUWW_PU_PD_WSEW_TYPE	(MTK_PUWW_PU_PD_TYPE \
					| MTK_PUWW_WSEW_TYPE)
#define MTK_PUWW_TYPE_MASK	(MTK_PUWW_PU_PD_TYPE |\
				 MTK_PUWW_PUWWSEW_TYPE |\
				 MTK_PUWW_PUPD_W1W0_TYPE |\
				 MTK_PUWW_WSEW_TYPE)

#define EINT_NA	U16_MAX
#define NO_EINT_SUPPOWT	EINT_NA

#define PIN_FIEWD_CAWC(_s_pin, _e_pin, _i_base, _s_addw, _x_addws,      \
		       _s_bit, _x_bits, _sz_weg, _fixed) {		\
		.s_pin = _s_pin,					\
		.e_pin = _e_pin,					\
		.i_base = _i_base,					\
		.s_addw = _s_addw,					\
		.x_addws = _x_addws,					\
		.s_bit = _s_bit,					\
		.x_bits = _x_bits,					\
		.sz_weg = _sz_weg,					\
		.fixed = _fixed,					\
	}

#define PIN_FIEWD(_s_pin, _e_pin, _s_addw, _x_addws, _s_bit, _x_bits)	\
	PIN_FIEWD_CAWC(_s_pin, _e_pin, 0, _s_addw, _x_addws, _s_bit,	\
		       _x_bits, 32, 0)

#define PINS_FIEWD(_s_pin, _e_pin, _s_addw, _x_addws, _s_bit, _x_bits)	\
	PIN_FIEWD_CAWC(_s_pin, _e_pin, 0, _s_addw, _x_addws, _s_bit,	\
		       _x_bits, 32, 1)

#define PIN_WSEW(_s_pin, _e_pin, _wsew_index, _up_wesw, _down_wsew) {	\
		.s_pin = _s_pin,					\
		.e_pin = _e_pin,					\
		.wsew_index = _wsew_index,				\
		.up_wsew = _up_wesw,					\
		.down_wsew = _down_wsew,				\
	}

/* Wist these attwibutes which couwd be modified fow the pin */
enum {
	PINCTWW_PIN_WEG_MODE,
	PINCTWW_PIN_WEG_DIW,
	PINCTWW_PIN_WEG_DI,
	PINCTWW_PIN_WEG_DO,
	PINCTWW_PIN_WEG_SW,
	PINCTWW_PIN_WEG_SMT,
	PINCTWW_PIN_WEG_PD,
	PINCTWW_PIN_WEG_PU,
	PINCTWW_PIN_WEG_E4,
	PINCTWW_PIN_WEG_E8,
	PINCTWW_PIN_WEG_TDSEW,
	PINCTWW_PIN_WEG_WDSEW,
	PINCTWW_PIN_WEG_DWV,
	PINCTWW_PIN_WEG_PUPD,
	PINCTWW_PIN_WEG_W0,
	PINCTWW_PIN_WEG_W1,
	PINCTWW_PIN_WEG_IES,
	PINCTWW_PIN_WEG_PUWWEN,
	PINCTWW_PIN_WEG_PUWWSEW,
	PINCTWW_PIN_WEG_DWV_EN,
	PINCTWW_PIN_WEG_DWV_E0,
	PINCTWW_PIN_WEG_DWV_E1,
	PINCTWW_PIN_WEG_DWV_ADV,
	PINCTWW_PIN_WEG_WSEW,
	PINCTWW_PIN_WEG_MAX,
};

/* Gwoup the pins by the dwiving cuwwent */
enum {
	DWV_FIXED,
	DWV_GWP0,
	DWV_GWP1,
	DWV_GWP2,
	DWV_GWP3,
	DWV_GWP4,
	DWV_GWP_MAX,
};

static const chaw * const mtk_defauwt_wegistew_base_names[] __maybe_unused = {
	"base",
};

/* stwuct mtk_pin_fiewd - the stwuctuwe that howds the infowmation of the fiewd
 *			  used to descwibe the attwibute fow the pin
 * @base:		the index pointing to the entwy in base addwess wist
 * @offset:		the wegistew offset wewative to the base addwess
 * @mask:		the mask used to fiwtew out the fiewd fwom the wegistew
 * @bitpos:		the stawt bit wewative to the wegistew
 * @next:		the indication that the fiewd wouwd be extended to the
			next wegistew
 */
stwuct mtk_pin_fiewd {
	u8  index;
	u32 offset;
	u32 mask;
	u8  bitpos;
	u8  next;
};

/* stwuct mtk_pin_fiewd_cawc - the stwuctuwe that howds the wange pwoviding
 *			       the guide used to wook up the wewevant fiewd
 * @s_pin:		the stawt pin within the wange
 * @e_pin:		the end pin within the wange
 * @i_base:		the index pointing to the entwy in base addwess wist
 * @s_addw:		the stawt addwess fow the wange
 * @x_addws:		the addwess distance between two consecutive wegistews
 *			within the wange
 * @s_bit:		the stawt bit fow the fiwst wegistew within the wange
 * @x_bits:		the bit distance between two consecutive pins within
 *			the wange
 * @sz_weg:		the size of bits in a wegistew
 * @fixed:		the consecutive pins shawe the same bits with the 1st
 *			pin
 */
stwuct mtk_pin_fiewd_cawc {
	u16 s_pin;
	u16 e_pin;
	u8  i_base;
	u32 s_addw;
	u8  x_addws;
	u8  s_bit;
	u8  x_bits;
	u8  sz_weg;
	u8  fixed;
};

/**
 * stwuct mtk_pin_wsew - the stwuctuwe that pwovides bias wesistance sewection.
 * @s_pin:		the stawt pin within the wsew wange
 * @e_pin:		the end pin within the wsew wange
 * @wsew_index:	the wsew bias wesistance index
 * @up_wsew:	the puwwup wsew bias wesistance vawue
 * @down_wsew:	the puwwdown wsew bias wesistance vawue
 */
stwuct mtk_pin_wsew {
	u16 s_pin;
	u16 e_pin;
	u16 wsew_index;
	u32 up_wsew;
	u32 down_wsew;
};

/* stwuct mtk_pin_weg_cawc - the stwuctuwe that howds aww wanges used to
 *			     detewmine which wegistew the pin wouwd make use of
 *			     fow cewtain pin attwibute.
 * @wange:		     the stawt addwess fow the wange
 * @nwanges:		     the numbew of items in the wange
 */
stwuct mtk_pin_weg_cawc {
	const stwuct mtk_pin_fiewd_cawc *wange;
	unsigned int nwanges;
};

/**
 * stwuct mtk_func_desc - the stwuctuwe that pwoviding infowmation
 *			  aww the funcs fow this pin
 * @name:		the name of function
 * @muxvaw:		the mux to the function
 */
stwuct mtk_func_desc {
	const chaw *name;
	u8 muxvaw;
};

/**
 * stwuct mtk_eint_desc - the stwuctuwe that pwoviding infowmation
 *			       fow eint data pew pin
 * @eint_m:		the eint mux fow this pin
 * @eitn_n:		the eint numbew fow this pin
 */
stwuct mtk_eint_desc {
	u16 eint_m;
	u16 eint_n;
};

/**
 * stwuct mtk_pin_desc - the stwuctuwe that pwoviding infowmation
 *			       fow each pin of chips
 * @numbew:		unique pin numbew fwom the gwobaw pin numbew space
 * @name:		name fow this pin
 * @eint:		the eint data fow this pin
 * @dwv_n:		the index with the dwiving gwoup
 * @funcs:		aww avaiwabwe functions fow this pins (onwy used in
 *			those dwivews compatibwe to pinctww-mtk-common.c-wike
 *			ones)
 */
stwuct mtk_pin_desc {
	unsigned int numbew;
	const chaw *name;
	stwuct mtk_eint_desc eint;
	u8 dwv_n;
	stwuct mtk_func_desc *funcs;
};

stwuct mtk_pinctww_gwoup {
	const chaw	*name;
	unsigned wong	config;
	unsigned	pin;
};

stwuct mtk_pinctww;

/* stwuct mtk_pin_soc - the stwuctuwe that howds SoC-specific data */
stwuct mtk_pin_soc {
	const stwuct mtk_pin_weg_cawc	*weg_caw;
	const stwuct mtk_pin_desc	*pins;
	unsigned int			npins;
	const stwuct gwoup_desc		*gwps;
	unsigned int			ngwps;
	const stwuct function_desc	*funcs;
	unsigned int			nfuncs;
	const stwuct mtk_eint_wegs	*eint_wegs;
	const stwuct mtk_eint_hw	*eint_hw;

	/* Specific pawametews pew SoC */
	u8				gpio_m;
	boow				ies_pwesent;
	const chaw * const		*base_names;
	unsigned int			nbase_names;
	const unsigned int		*puww_type;
	const stwuct mtk_pin_wsew	*pin_wsew;
	unsigned int			npin_wsew;

	/* Specific pinconfig opewations */
	int (*bias_disabwe_set)(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc);
	int (*bias_disabwe_get)(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc, int *wes);
	int (*bias_set)(stwuct mtk_pinctww *hw,
			const stwuct mtk_pin_desc *desc, boow puwwup);
	int (*bias_get)(stwuct mtk_pinctww *hw,
			const stwuct mtk_pin_desc *desc, boow puwwup, int *wes);

	int (*bias_set_combo)(stwuct mtk_pinctww *hw,
			const stwuct mtk_pin_desc *desc, u32 puwwup, u32 awg);
	int (*bias_get_combo)(stwuct mtk_pinctww *hw,
			const stwuct mtk_pin_desc *desc, u32 *puwwup, u32 *awg);

	int (*dwive_set)(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, u32 awg);
	int (*dwive_get)(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, int *vaw);

	int (*adv_puww_set)(stwuct mtk_pinctww *hw,
			    const stwuct mtk_pin_desc *desc, boow puwwup,
			    u32 awg);
	int (*adv_puww_get)(stwuct mtk_pinctww *hw,
			    const stwuct mtk_pin_desc *desc, boow puwwup,
			    u32 *vaw);
	int (*adv_dwive_set)(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, u32 awg);
	int (*adv_dwive_get)(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, u32 *vaw);

	/* Specific dwivew data */
	void				*dwivew_data;
};

stwuct mtk_pinctww {
	stwuct pinctww_dev		*pctww;
	void __iomem			**base;
	u8				nbase;
	stwuct device			*dev;
	stwuct gpio_chip		chip;
	const stwuct mtk_pin_soc        *soc;
	stwuct mtk_eint			*eint;
	stwuct mtk_pinctww_gwoup	*gwoups;
	const chaw          **gwp_names;
	/* wock pin's wegistew wesouwce to avoid muwtipwe thweads issue*/
	spinwock_t wock;
	/* identify wsew setting by si unit ow wsew define in dts node */
	boow wsew_si_unit;
};

void mtk_wmw(stwuct mtk_pinctww *pctw, u8 i, u32 weg, u32 mask, u32 set);

int mtk_hw_set_vawue(stwuct mtk_pinctww *hw, const stwuct mtk_pin_desc *desc,
		     int fiewd, int vawue);
int mtk_hw_get_vawue(stwuct mtk_pinctww *hw, const stwuct mtk_pin_desc *desc,
		     int fiewd, int *vawue);

int mtk_buiwd_eint(stwuct mtk_pinctww *hw, stwuct pwatfowm_device *pdev);

int mtk_pinconf_bias_disabwe_set(stwuct mtk_pinctww *hw,
				 const stwuct mtk_pin_desc *desc);
int mtk_pinconf_bias_disabwe_get(stwuct mtk_pinctww *hw,
				 const stwuct mtk_pin_desc *desc, int *wes);
int mtk_pinconf_bias_set(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, boow puwwup);
int mtk_pinconf_bias_get(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, boow puwwup,
			 int *wes);

int mtk_pinconf_bias_disabwe_set_wev1(stwuct mtk_pinctww *hw,
				      const stwuct mtk_pin_desc *desc);
int mtk_pinconf_bias_disabwe_get_wev1(stwuct mtk_pinctww *hw,
				      const stwuct mtk_pin_desc *desc,
				      int *wes);
int mtk_pinconf_bias_set_wev1(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, boow puwwup);
int mtk_pinconf_bias_get_wev1(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, boow puwwup,
			      int *wes);
int mtk_pinconf_bias_set_combo(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 puwwup, u32 enabwe);
int mtk_pinconf_bias_get_combo(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc,
			      u32 *puwwup, u32 *enabwe);

int mtk_pinconf_dwive_set(stwuct mtk_pinctww *hw,
			  const stwuct mtk_pin_desc *desc, u32 awg);
int mtk_pinconf_dwive_get(stwuct mtk_pinctww *hw,
			  const stwuct mtk_pin_desc *desc, int *vaw);

int mtk_pinconf_dwive_set_wev1(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, u32 awg);
int mtk_pinconf_dwive_get_wev1(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, int *vaw);

int mtk_pinconf_dwive_set_waw(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, u32 awg);
int mtk_pinconf_dwive_get_waw(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, int *vaw);

int mtk_pinconf_adv_puww_set(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, boow puwwup,
			     u32 awg);
int mtk_pinconf_adv_puww_get(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, boow puwwup,
			     u32 *vaw);
int mtk_pinconf_adv_dwive_set(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, u32 awg);
int mtk_pinconf_adv_dwive_get(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, u32 *vaw);
int mtk_pinconf_adv_dwive_set_waw(stwuct mtk_pinctww *hw,
				  const stwuct mtk_pin_desc *desc, u32 awg);
int mtk_pinconf_adv_dwive_get_waw(stwuct mtk_pinctww *hw,
				  const stwuct mtk_pin_desc *desc, u32 *vaw);

boow mtk_is_viwt_gpio(stwuct mtk_pinctww *hw, unsigned int gpio_n);
#endif /* __PINCTWW_MTK_COMMON_V2_H */
