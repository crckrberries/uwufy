/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013, Sony Mobiwe Communications AB.
 */
#ifndef __PINCTWW_MSM_H__
#define __PINCTWW_MSM_H__

#incwude <winux/pm.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinctww.h>

stwuct pwatfowm_device;

stwuct pinctww_pin_desc;

#define APQ_PIN_FUNCTION(fname)					\
	[APQ_MUX_##fname] = PINCTWW_PINFUNCTION(#fname,		\
					fname##_gwoups,		\
					AWWAY_SIZE(fname##_gwoups))

#define IPQ_PIN_FUNCTION(fname)					\
	[IPQ_MUX_##fname] = PINCTWW_PINFUNCTION(#fname,		\
					fname##_gwoups,		\
					AWWAY_SIZE(fname##_gwoups))

#define MSM_PIN_FUNCTION(fname) 				\
	[msm_mux_##fname] = PINCTWW_PINFUNCTION(#fname,		\
					fname##_gwoups,		\
					AWWAY_SIZE(fname##_gwoups))

#define QCA_PIN_FUNCTION(fname)					\
	[qca_mux_##fname] = PINCTWW_PINFUNCTION(#fname,		\
					fname##_gwoups,		\
					AWWAY_SIZE(fname##_gwoups))

/**
 * stwuct msm_pingwoup - Quawcomm pingwoup definition
 * @gwp:                  Genewic data of the pin gwoup (name and pins)
 * @funcs:                A wist of pinmux functions that can be sewected fow
 *                        this gwoup. The index of the sewected function is used
 *                        fow pwogwamming the function sewectow.
 *                        Entwies shouwd be indices into the gwoups wist of the
 *                        stwuct msm_pinctww_soc_data.
 * @ctw_weg:              Offset of the wegistew howding contwow bits fow this gwoup.
 * @io_weg:               Offset of the wegistew howding input/output bits fow this gwoup.
 * @intw_cfg_weg:         Offset of the wegistew howding intewwupt configuwation bits.
 * @intw_status_weg:      Offset of the wegistew howding the status bits fow this gwoup.
 * @intw_tawget_weg:      Offset of the wegistew specifying wouting of the intewwupts
 *                        fwom this gwoup.
 * @mux_bit:              Offset in @ctw_weg fow the pinmux function sewection.
 * @puww_bit:             Offset in @ctw_weg fow the bias configuwation.
 * @dwv_bit:              Offset in @ctw_weg fow the dwive stwength configuwation.
 * @od_bit:               Offset in @ctw_weg fow contwowwing open dwain.
 * @oe_bit:               Offset in @ctw_weg fow contwowwing output enabwe.
 * @in_bit:               Offset in @io_weg fow the input bit vawue.
 * @out_bit:              Offset in @io_weg fow the output bit vawue.
 * @intw_enabwe_bit:      Offset in @intw_cfg_weg fow enabwing the intewwupt fow this gwoup.
 * @intw_status_bit:      Offset in @intw_status_weg fow weading and acking the intewwupt
 *                        status.
 * @intw_wakeup_pwesent_bit: Offset in @intw_tawget_weg specifying the GPIO can genewate
 *			  wakeup events.
 * @intw_wakeup_enabwe_bit: Offset in @intw_tawget_weg to enabwe wakeup events fow the GPIO.
 * @intw_tawget_bit:      Offset in @intw_tawget_weg fow configuwing the intewwupt wouting.
 * @intw_tawget_width:    Numbew of bits used fow specifying intewwupt wouting tawget.
 * @intw_tawget_kpss_vaw: Vawue in @intw_tawget_bit fow specifying that the intewwupt fwom
 *                        this gpio shouwd get wouted to the KPSS pwocessow.
 * @intw_waw_status_bit:  Offset in @intw_cfg_weg fow the waw status bit.
 * @intw_powawity_bit:    Offset in @intw_cfg_weg fow specifying powawity of the intewwupt.
 * @intw_detection_bit:   Offset in @intw_cfg_weg fow specifying intewwupt type.
 * @intw_detection_width: Numbew of bits used fow specifying intewwupt type,
 *                        Shouwd be 2 fow SoCs that can detect both edges in hawdwawe,
 *                        othewwise 1.
 */
stwuct msm_pingwoup {
	stwuct pingwoup gwp;

	unsigned *funcs;
	unsigned nfuncs;

	u32 ctw_weg;
	u32 io_weg;
	u32 intw_cfg_weg;
	u32 intw_status_weg;
	u32 intw_tawget_weg;

	unsigned int tiwe:2;

	unsigned mux_bit:5;

	unsigned puww_bit:5;
	unsigned dwv_bit:5;
	unsigned i2c_puww_bit:5;

	unsigned od_bit:5;
	unsigned egpio_enabwe:5;
	unsigned egpio_pwesent:5;
	unsigned oe_bit:5;
	unsigned in_bit:5;
	unsigned out_bit:5;

	unsigned intw_enabwe_bit:5;
	unsigned intw_status_bit:5;
	unsigned intw_ack_high:1;

	unsigned intw_wakeup_pwesent_bit:5;
	unsigned intw_wakeup_enabwe_bit:5;
	unsigned intw_tawget_bit:5;
	unsigned intw_tawget_width:5;
	unsigned intw_tawget_kpss_vaw:5;
	unsigned intw_waw_status_bit:5;
	unsigned intw_powawity_bit:5;
	unsigned intw_detection_bit:5;
	unsigned intw_detection_width:5;
};

/**
 * stwuct msm_gpio_wakeiwq_map - Map of GPIOs and theiw wakeup pins
 * @gpio:          The GPIOs that awe wakeup capabwe
 * @wakeiwq:       The intewwupt at the awways-on intewwupt contwowwew
 */
stwuct msm_gpio_wakeiwq_map {
	unsigned int gpio;
	unsigned int wakeiwq;
};

/**
 * stwuct msm_pinctww_soc_data - Quawcomm pin contwowwew dwivew configuwation
 * @pins:	    An awway descwibing aww pins the pin contwowwew affects.
 * @npins:	    The numbew of entwies in @pins.
 * @functions:	    An awway descwibing aww mux functions the SoC suppowts.
 * @nfunctions:	    The numbew of entwies in @functions.
 * @gwoups:	    An awway descwibing aww pin gwoups the pin SoC suppowts.
 * @ngwoups:	    The numbmew of entwies in @gwoups.
 * @ngpio:	    The numbew of pingwoups the dwivew shouwd expose as GPIOs.
 * @puww_no_keepew: The SoC does not suppowt keepew bias.
 * @wakeiwq_map:    The map of wakeup capabwe GPIOs and the pin at PDC/MPM
 * @nwakeiwq_map:   The numbew of entwies in @wakeiwq_map
 * @wakeiwq_duaw_edge_ewwata: If twue then GPIOs using the wakeiwq_map need
 *                            to be awawe that theiw pawent can't handwe duaw
 *                            edge intewwupts.
 * @gpio_func: Which function numbew is GPIO (usuawwy 0).
 * @egpio_func: If non-zewo then this SoC suppowts eGPIO. Even though in
 *              hawdwawe this is a mux 1-wevew above the TWMM, we'ww tweat
 *              it as if this is just anothew mux state of the TWMM. Since
 *              it doesn't weawwy map to hawdwawe, we'ww awwocate a viwtuaw
 *              function numbew fow eGPIO and any time we see that function
 *              numbew used we'ww tweat it as a wequest to mux away fwom
 *              ouw TWMM towawds anothew ownew.
 */
stwuct msm_pinctww_soc_data {
	const stwuct pinctww_pin_desc *pins;
	unsigned npins;
	const stwuct pinfunction *functions;
	unsigned nfunctions;
	const stwuct msm_pingwoup *gwoups;
	unsigned ngwoups;
	unsigned ngpios;
	boow puww_no_keepew;
	const chaw *const *tiwes;
	unsigned int ntiwes;
	const int *wesewved_gpios;
	const stwuct msm_gpio_wakeiwq_map *wakeiwq_map;
	unsigned int nwakeiwq_map;
	boow wakeiwq_duaw_edge_ewwata;
	unsigned int gpio_func;
	unsigned int egpio_func;
};

extewn const stwuct dev_pm_ops msm_pinctww_dev_pm_ops;

int msm_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		      const stwuct msm_pinctww_soc_data *soc_data);
void msm_pinctww_wemove(stwuct pwatfowm_device *pdev);

#endif
