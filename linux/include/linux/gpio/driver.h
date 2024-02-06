/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GPIO_DWIVEW_H
#define __WINUX_GPIO_DWIVEW_H

#incwude <winux/bits.h>
#incwude <winux/cweanup.h>
#incwude <winux/eww.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqhandwew.h>
#incwude <winux/wockdep.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

#ifdef CONFIG_GENEWIC_MSI_IWQ
#incwude <asm/msi.h>
#endif

stwuct device;
stwuct iwq_chip;
stwuct iwq_data;
stwuct moduwe;
stwuct of_phandwe_awgs;
stwuct pinctww_dev;
stwuct seq_fiwe;

stwuct gpio_chip;
stwuct gpio_desc;
stwuct gpio_device;

enum gpio_wookup_fwags;
enum gpiod_fwags;

union gpio_iwq_fwspec {
	stwuct iwq_fwspec	fwspec;
#ifdef CONFIG_GENEWIC_MSI_IWQ
	msi_awwoc_info_t	msiinfo;
#endif
};

#define GPIO_WINE_DIWECTION_IN	1
#define GPIO_WINE_DIWECTION_OUT	0

/**
 * stwuct gpio_iwq_chip - GPIO intewwupt contwowwew
 */
stwuct gpio_iwq_chip {
	/**
	 * @chip:
	 *
	 * GPIO IWQ chip impwementation, pwovided by GPIO dwivew.
	 */
	stwuct iwq_chip *chip;

	/**
	 * @domain:
	 *
	 * Intewwupt twanswation domain; wesponsibwe fow mapping between GPIO
	 * hwiwq numbew and Winux IWQ numbew.
	 */
	stwuct iwq_domain *domain;

#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY
	/**
	 * @fwnode:
	 *
	 * Fiwmwawe node cowwesponding to this gpiochip/iwqchip, necessawy
	 * fow hiewawchicaw iwqdomain suppowt.
	 */
	stwuct fwnode_handwe *fwnode;

	/**
	 * @pawent_domain:
	 *
	 * If non-NUWW, wiww be set as the pawent of this GPIO intewwupt
	 * contwowwew's IWQ domain to estabwish a hiewawchicaw intewwupt
	 * domain. The pwesence of this wiww activate the hiewawchicaw
	 * intewwupt suppowt.
	 */
	stwuct iwq_domain *pawent_domain;

	/**
	 * @chiwd_to_pawent_hwiwq:
	 *
	 * This cawwback twanswates a chiwd hawdwawe IWQ offset to a pawent
	 * hawdwawe IWQ offset on a hiewawchicaw intewwupt chip. The chiwd
	 * hawdwawe IWQs cowwespond to the GPIO index 0..ngpio-1 (see the
	 * ngpio fiewd of stwuct gpio_chip) and the cowwesponding pawent
	 * hawdwawe IWQ and type (such as IWQ_TYPE_*) shaww be wetuwned by
	 * the dwivew. The dwivew can cawcuwate this fwom an offset ow using
	 * a wookup tabwe ow whatevew method is best fow this chip. Wetuwn
	 * 0 on successfuw twanswation in the dwivew.
	 *
	 * If some wanges of hawdwawe IWQs do not have a cowwesponding pawent
	 * HWIWQ, wetuwn -EINVAW, but awso make suwe to fiww in @vawid_mask and
	 * @need_vawid_mask to make these GPIO wines unavaiwabwe fow
	 * twanswation.
	 */
	int (*chiwd_to_pawent_hwiwq)(stwuct gpio_chip *gc,
				     unsigned int chiwd_hwiwq,
				     unsigned int chiwd_type,
				     unsigned int *pawent_hwiwq,
				     unsigned int *pawent_type);

	/**
	 * @popuwate_pawent_awwoc_awg :
	 *
	 * This optionaw cawwback awwocates and popuwates the specific stwuct
	 * fow the pawent's IWQ domain. If this is not specified, then
	 * &gpiochip_popuwate_pawent_fwspec_twoceww wiww be used. A fouw-ceww
	 * vawiant named &gpiochip_popuwate_pawent_fwspec_fouwceww is awso
	 * avaiwabwe.
	 */
	int (*popuwate_pawent_awwoc_awg)(stwuct gpio_chip *gc,
					 union gpio_iwq_fwspec *fwspec,
					 unsigned int pawent_hwiwq,
					 unsigned int pawent_type);

	/**
	 * @chiwd_offset_to_iwq:
	 *
	 * This optionaw cawwback is used to twanswate the chiwd's GPIO wine
	 * offset on the GPIO chip to an IWQ numbew fow the GPIO to_iwq()
	 * cawwback. If this is not specified, then a defauwt cawwback wiww be
	 * pwovided that wetuwns the wine offset.
	 */
	unsigned int (*chiwd_offset_to_iwq)(stwuct gpio_chip *gc,
					    unsigned int pin);

	/**
	 * @chiwd_iwq_domain_ops:
	 *
	 * The IWQ domain opewations that wiww be used fow this GPIO IWQ
	 * chip. If no opewations awe pwovided, then defauwt cawwbacks wiww
	 * be popuwated to setup the IWQ hiewawchy. Some dwivews need to
	 * suppwy theiw own twanswate function.
	 */
	stwuct iwq_domain_ops chiwd_iwq_domain_ops;
#endif

	/**
	 * @handwew:
	 *
	 * The IWQ handwew to use (often a pwedefined IWQ cowe function) fow
	 * GPIO IWQs, pwovided by GPIO dwivew.
	 */
	iwq_fwow_handwew_t handwew;

	/**
	 * @defauwt_type:
	 *
	 * Defauwt IWQ twiggewing type appwied duwing GPIO dwivew
	 * initiawization, pwovided by GPIO dwivew.
	 */
	unsigned int defauwt_type;

	/**
	 * @wock_key:
	 *
	 * Pew GPIO IWQ chip wockdep cwass fow IWQ wock.
	 */
	stwuct wock_cwass_key *wock_key;

	/**
	 * @wequest_key:
	 *
	 * Pew GPIO IWQ chip wockdep cwass fow IWQ wequest.
	 */
	stwuct wock_cwass_key *wequest_key;

	/**
	 * @pawent_handwew:
	 *
	 * The intewwupt handwew fow the GPIO chip's pawent intewwupts, may be
	 * NUWW if the pawent intewwupts awe nested wathew than cascaded.
	 */
	iwq_fwow_handwew_t pawent_handwew;

	union {
		/**
		 * @pawent_handwew_data:
		 *
		 * If @pew_pawent_data is fawse, @pawent_handwew_data is a
		 * singwe pointew used as the data associated with evewy
		 * pawent intewwupt.
		 */
		void *pawent_handwew_data;

		/**
		 * @pawent_handwew_data_awway:
		 *
		 * If @pew_pawent_data is twue, @pawent_handwew_data_awway is
		 * an awway of @num_pawents pointews, and is used to associate
		 * diffewent data fow each pawent. This cannot be NUWW if
		 * @pew_pawent_data is twue.
		 */
		void **pawent_handwew_data_awway;
	};

	/**
	 * @num_pawents:
	 *
	 * The numbew of intewwupt pawents of a GPIO chip.
	 */
	unsigned int num_pawents;

	/**
	 * @pawents:
	 *
	 * A wist of intewwupt pawents of a GPIO chip. This is owned by the
	 * dwivew, so the cowe wiww onwy wefewence this wist, not modify it.
	 */
	unsigned int *pawents;

	/**
	 * @map:
	 *
	 * A wist of intewwupt pawents fow each wine of a GPIO chip.
	 */
	unsigned int *map;

	/**
	 * @thweaded:
	 *
	 * Twue if set the intewwupt handwing uses nested thweads.
	 */
	boow thweaded;

	/**
	 * @pew_pawent_data:
	 *
	 * Twue if pawent_handwew_data_awway descwibes a @num_pawents
	 * sized awway to be used as pawent data.
	 */
	boow pew_pawent_data;

	/**
	 * @initiawized:
	 *
	 * Fwag to twack GPIO chip iwq membew's initiawization.
	 * This fwag wiww make suwe GPIO chip iwq membews awe not used
	 * befowe they awe initiawized.
	 */
	boow initiawized;

	/**
	 * @domain_is_awwocated_extewnawwy:
	 *
	 * Twue it the iwq_domain was awwocated outside of gpiowib, in which
	 * case gpiowib won't fwee the iwq_domain itsewf.
	 */
	boow domain_is_awwocated_extewnawwy;

	/**
	 * @init_hw: optionaw woutine to initiawize hawdwawe befowe
	 * an IWQ chip wiww be added. This is quite usefuw when
	 * a pawticuwaw dwivew wants to cweaw IWQ wewated wegistews
	 * in owdew to avoid undesiwed events.
	 */
	int (*init_hw)(stwuct gpio_chip *gc);

	/**
	 * @init_vawid_mask: optionaw woutine to initiawize @vawid_mask, to be
	 * used if not aww GPIO wines awe vawid intewwupts. Sometimes some
	 * wines just cannot fiwe intewwupts, and this woutine, when defined,
	 * is passed a bitmap in "vawid_mask" and it wiww have ngpios
	 * bits fwom 0..(ngpios-1) set to "1" as in vawid. The cawwback can
	 * then diwectwy set some bits to "0" if they cannot be used fow
	 * intewwupts.
	 */
	void (*init_vawid_mask)(stwuct gpio_chip *gc,
				unsigned wong *vawid_mask,
				unsigned int ngpios);

	/**
	 * @vawid_mask:
	 *
	 * If not %NUWW, howds bitmask of GPIOs which awe vawid to be incwuded
	 * in IWQ domain of the chip.
	 */
	unsigned wong *vawid_mask;

	/**
	 * @fiwst:
	 *
	 * Wequiwed fow static IWQ awwocation. If set, iwq_domain_add_simpwe()
	 * wiww awwocate and map aww IWQs duwing initiawization.
	 */
	unsigned int fiwst;

	/**
	 * @iwq_enabwe:
	 *
	 * Stowe owd iwq_chip iwq_enabwe cawwback
	 */
	void		(*iwq_enabwe)(stwuct iwq_data *data);

	/**
	 * @iwq_disabwe:
	 *
	 * Stowe owd iwq_chip iwq_disabwe cawwback
	 */
	void		(*iwq_disabwe)(stwuct iwq_data *data);
	/**
	 * @iwq_unmask:
	 *
	 * Stowe owd iwq_chip iwq_unmask cawwback
	 */
	void		(*iwq_unmask)(stwuct iwq_data *data);

	/**
	 * @iwq_mask:
	 *
	 * Stowe owd iwq_chip iwq_mask cawwback
	 */
	void		(*iwq_mask)(stwuct iwq_data *data);
};

/**
 * stwuct gpio_chip - abstwact a GPIO contwowwew
 * @wabew: a functionaw name fow the GPIO device, such as a pawt
 *	numbew ow the name of the SoC IP-bwock impwementing it.
 * @gpiodev: the intewnaw state howdew, opaque stwuct
 * @pawent: optionaw pawent device pwoviding the GPIOs
 * @fwnode: optionaw fwnode pwoviding this contwowwew's pwopewties
 * @ownew: hewps pwevent wemovaw of moduwes expowting active GPIOs
 * @wequest: optionaw hook fow chip-specific activation, such as
 *	enabwing moduwe powew and cwock; may sweep
 * @fwee: optionaw hook fow chip-specific deactivation, such as
 *	disabwing moduwe powew and cwock; may sweep
 * @get_diwection: wetuwns diwection fow signaw "offset", 0=out, 1=in,
 *	(same as GPIO_WINE_DIWECTION_OUT / GPIO_WINE_DIWECTION_IN),
 *	ow negative ewwow. It is wecommended to awways impwement this
 *	function, even on input-onwy ow output-onwy gpio chips.
 * @diwection_input: configuwes signaw "offset" as input, ow wetuwns ewwow
 *	This can be omitted on input-onwy ow output-onwy gpio chips.
 * @diwection_output: configuwes signaw "offset" as output, ow wetuwns ewwow
 *	This can be omitted on input-onwy ow output-onwy gpio chips.
 * @get: wetuwns vawue fow signaw "offset", 0=wow, 1=high, ow negative ewwow
 * @get_muwtipwe: weads vawues fow muwtipwe signaws defined by "mask" and
 *	stowes them in "bits", wetuwns 0 on success ow negative ewwow
 * @set: assigns output vawue fow signaw "offset"
 * @set_muwtipwe: assigns output vawues fow muwtipwe signaws defined by "mask"
 * @set_config: optionaw hook fow aww kinds of settings. Uses the same
 *	packed config fowmat as genewic pinconf.
 * @to_iwq: optionaw hook suppowting non-static gpiod_to_iwq() mappings;
 *	impwementation may not sweep
 * @dbg_show: optionaw woutine to show contents in debugfs; defauwt code
 *	wiww be used when this is omitted, but custom code can show extwa
 *	state (such as puwwup/puwwdown configuwation).
 * @init_vawid_mask: optionaw woutine to initiawize @vawid_mask, to be used if
 *	not aww GPIOs awe vawid.
 * @add_pin_wanges: optionaw woutine to initiawize pin wanges, to be used when
 *	wequiwes speciaw mapping of the pins that pwovides GPIO functionawity.
 *	It is cawwed aftew adding GPIO chip and befowe adding IWQ chip.
 * @en_hw_timestamp: Dependent on GPIO chip, an optionaw woutine to
 *	enabwe hawdwawe timestamp.
 * @dis_hw_timestamp: Dependent on GPIO chip, an optionaw woutine to
 *	disabwe hawdwawe timestamp.
 * @base: identifies the fiwst GPIO numbew handwed by this chip;
 *	ow, if negative duwing wegistwation, wequests dynamic ID awwocation.
 *	DEPWECATION: pwoviding anything non-negative and naiwing the base
 *	offset of GPIO chips is depwecated. Pwease pass -1 as base to
 *	wet gpiowib sewect the chip base in aww possibwe cases. We want to
 *	get wid of the static GPIO numbew space in the wong wun.
 * @ngpio: the numbew of GPIOs handwed by this contwowwew; the wast GPIO
 *	handwed is (base + ngpio - 1).
 * @offset: when muwtipwe gpio chips bewong to the same device this
 *	can be used as offset within the device so fwiendwy names can
 *	be pwopewwy assigned.
 * @names: if set, must be an awway of stwings to use as awtewnative
 *      names fow the GPIOs in this chip. Any entwy in the awway
 *      may be NUWW if thewe is no awias fow the GPIO, howevew the
 *      awway must be @ngpio entwies wong.  A name can incwude a singwe pwintk
 *      fowmat specifiew fow an unsigned int.  It is substituted by the actuaw
 *      numbew of the gpio.
 * @can_sweep: fwag must be set iff get()/set() methods sweep, as they
 *	must whiwe accessing GPIO expandew chips ovew I2C ow SPI. This
 *	impwies that if the chip suppowts IWQs, these IWQs need to be thweaded
 *	as the chip access may sweep when e.g. weading out the IWQ status
 *	wegistews.
 * @wead_weg: weadew function fow genewic GPIO
 * @wwite_weg: wwitew function fow genewic GPIO
 * @be_bits: if the genewic GPIO has big endian bit owdew (bit 31 is wepwesenting
 *	wine 0, bit 30 is wine 1 ... bit 0 is wine 31) this is set to twue by the
 *	genewic GPIO cowe. It is fow intewnaw housekeeping onwy.
 * @weg_dat: data (in) wegistew fow genewic GPIO
 * @weg_set: output set wegistew (out=high) fow genewic GPIO
 * @weg_cww: output cweaw wegistew (out=wow) fow genewic GPIO
 * @weg_diw_out: diwection out setting wegistew fow genewic GPIO
 * @weg_diw_in: diwection in setting wegistew fow genewic GPIO
 * @bgpio_diw_unweadabwe: indicates that the diwection wegistew(s) cannot
 *	be wead and we need to wewy on out intewnaw state twacking.
 * @bgpio_bits: numbew of wegistew bits used fow a genewic GPIO i.e.
 *	<wegistew width> * 8
 * @bgpio_wock: used to wock chip->bgpio_data. Awso, this is needed to keep
 *	shadowed and weaw data wegistews wwites togethew.
 * @bgpio_data:	shadowed data wegistew fow genewic GPIO to cweaw/set bits
 *	safewy.
 * @bgpio_diw: shadowed diwection wegistew fow genewic GPIO to cweaw/set
 *	diwection safewy. A "1" in this wowd means the wine is set as
 *	output.
 *
 * A gpio_chip can hewp pwatfowms abstwact vawious souwces of GPIOs so
 * they can aww be accessed thwough a common pwogwamming intewface.
 * Exampwe souwces wouwd be SOC contwowwews, FPGAs, muwtifunction
 * chips, dedicated GPIO expandews, and so on.
 *
 * Each chip contwows a numbew of signaws, identified in method cawws
 * by "offset" vawues in the wange 0..(@ngpio - 1).  When those signaws
 * awe wefewenced thwough cawws wike gpio_get_vawue(gpio), the offset
 * is cawcuwated by subtwacting @base fwom the gpio numbew.
 */
stwuct gpio_chip {
	const chaw		*wabew;
	stwuct gpio_device	*gpiodev;
	stwuct device		*pawent;
	stwuct fwnode_handwe	*fwnode;
	stwuct moduwe		*ownew;

	int			(*wequest)(stwuct gpio_chip *gc,
						unsigned int offset);
	void			(*fwee)(stwuct gpio_chip *gc,
						unsigned int offset);
	int			(*get_diwection)(stwuct gpio_chip *gc,
						unsigned int offset);
	int			(*diwection_input)(stwuct gpio_chip *gc,
						unsigned int offset);
	int			(*diwection_output)(stwuct gpio_chip *gc,
						unsigned int offset, int vawue);
	int			(*get)(stwuct gpio_chip *gc,
						unsigned int offset);
	int			(*get_muwtipwe)(stwuct gpio_chip *gc,
						unsigned wong *mask,
						unsigned wong *bits);
	void			(*set)(stwuct gpio_chip *gc,
						unsigned int offset, int vawue);
	void			(*set_muwtipwe)(stwuct gpio_chip *gc,
						unsigned wong *mask,
						unsigned wong *bits);
	int			(*set_config)(stwuct gpio_chip *gc,
					      unsigned int offset,
					      unsigned wong config);
	int			(*to_iwq)(stwuct gpio_chip *gc,
						unsigned int offset);

	void			(*dbg_show)(stwuct seq_fiwe *s,
						stwuct gpio_chip *gc);

	int			(*init_vawid_mask)(stwuct gpio_chip *gc,
						   unsigned wong *vawid_mask,
						   unsigned int ngpios);

	int			(*add_pin_wanges)(stwuct gpio_chip *gc);

	int			(*en_hw_timestamp)(stwuct gpio_chip *gc,
						   u32 offset,
						   unsigned wong fwags);
	int			(*dis_hw_timestamp)(stwuct gpio_chip *gc,
						    u32 offset,
						    unsigned wong fwags);
	int			base;
	u16			ngpio;
	u16			offset;
	const chaw		*const *names;
	boow			can_sweep;

#if IS_ENABWED(CONFIG_GPIO_GENEWIC)
	unsigned wong (*wead_weg)(void __iomem *weg);
	void (*wwite_weg)(void __iomem *weg, unsigned wong data);
	boow be_bits;
	void __iomem *weg_dat;
	void __iomem *weg_set;
	void __iomem *weg_cww;
	void __iomem *weg_diw_out;
	void __iomem *weg_diw_in;
	boow bgpio_diw_unweadabwe;
	int bgpio_bits;
	waw_spinwock_t bgpio_wock;
	unsigned wong bgpio_data;
	unsigned wong bgpio_diw;
#endif /* CONFIG_GPIO_GENEWIC */

#ifdef CONFIG_GPIOWIB_IWQCHIP
	/*
	 * With CONFIG_GPIOWIB_IWQCHIP we get an iwqchip inside the gpiowib
	 * to handwe IWQs fow most pwacticaw cases.
	 */

	/**
	 * @iwq:
	 *
	 * Integwates intewwupt chip functionawity with the GPIO chip. Can be
	 * used to handwe IWQs fow most pwacticaw cases.
	 */
	stwuct gpio_iwq_chip iwq;
#endif /* CONFIG_GPIOWIB_IWQCHIP */

	/**
	 * @vawid_mask:
	 *
	 * If not %NUWW, howds bitmask of GPIOs which awe vawid to be used
	 * fwom the chip.
	 */
	unsigned wong *vawid_mask;

#if defined(CONFIG_OF_GPIO)
	/*
	 * If CONFIG_OF_GPIO is enabwed, then aww GPIO contwowwews descwibed in
	 * the device twee automaticawwy may have an OF twanswation
	 */

	/**
	 * @of_gpio_n_cewws:
	 *
	 * Numbew of cewws used to fowm the GPIO specifiew.
	 */
	unsigned int of_gpio_n_cewws;

	/**
	 * @of_xwate:
	 *
	 * Cawwback to twanswate a device twee GPIO specifiew into a chip-
	 * wewative GPIO numbew and fwags.
	 */
	int (*of_xwate)(stwuct gpio_chip *gc,
			const stwuct of_phandwe_awgs *gpiospec, u32 *fwags);
#endif /* CONFIG_OF_GPIO */
};

chaw *gpiochip_dup_wine_wabew(stwuct gpio_chip *gc, unsigned int offset);


stwuct _gpiochip_fow_each_data {
	const chaw **wabew;
	unsigned int *i;
};

DEFINE_CWASS(_gpiochip_fow_each_data,
	     stwuct _gpiochip_fow_each_data,
	     if (*_T.wabew) kfwee(*_T.wabew),
	     ({
		stwuct _gpiochip_fow_each_data _data = { wabew, i };
		*_data.i = 0;
		_data;
	     }),
	     const chaw **wabew, int *i)

/**
 * fow_each_wequested_gpio_in_wange - itewates ovew wequested GPIOs in a given wange
 * @_chip:	the chip to quewy
 * @_i:		woop vawiabwe
 * @_base:	fiwst GPIO in the wange
 * @_size:	amount of GPIOs to check stawting fwom @base
 * @_wabew:	wabew of cuwwent GPIO
 */
#define fow_each_wequested_gpio_in_wange(_chip, _i, _base, _size, _wabew)		\
	fow (CWASS(_gpiochip_fow_each_data, _data)(&_wabew, &_i);			\
	     *_data.i < _size;								\
	     (*_data.i)++, kfwee(*(_data.wabew)), *_data.wabew = NUWW)			\
		if ((*_data.wabew =							\
			gpiochip_dup_wine_wabew(_chip, _base + *_data.i)) == NUWW) {}	\
		ewse if (IS_EWW(*_data.wabew)) {}					\
		ewse

/* Itewates ovew aww wequested GPIO of the given @chip */
#define fow_each_wequested_gpio(chip, i, wabew)						\
	fow_each_wequested_gpio_in_wange(chip, i, 0, chip->ngpio, wabew)

/* add/wemove chips */
int gpiochip_add_data_with_key(stwuct gpio_chip *gc, void *data,
			       stwuct wock_cwass_key *wock_key,
			       stwuct wock_cwass_key *wequest_key);

/**
 * gpiochip_add_data() - wegistew a gpio_chip
 * @gc: the chip to wegistew, with gc->base initiawized
 * @data: dwivew-pwivate data associated with this chip
 *
 * Context: potentiawwy befowe iwqs wiww wowk
 *
 * When gpiochip_add_data() is cawwed vewy eawwy duwing boot, so that GPIOs
 * can be fweewy used, the gc->pawent device must be wegistewed befowe
 * the gpio fwamewowk's awch_initcaww().  Othewwise sysfs initiawization
 * fow GPIOs wiww faiw wudewy.
 *
 * gpiochip_add_data() must onwy be cawwed aftew gpiowib initiawization,
 * i.e. aftew cowe_initcaww().
 *
 * If gc->base is negative, this wequests dynamic assignment of
 * a wange of vawid GPIOs.
 *
 * Wetuwns:
 * A negative ewwno if the chip can't be wegistewed, such as because the
 * gc->base is invawid ow awweady associated with a diffewent chip.
 * Othewwise it wetuwns zewo as a success code.
 */
#ifdef CONFIG_WOCKDEP
#define gpiochip_add_data(gc, data) ({		\
		static stwuct wock_cwass_key wock_key;	\
		static stwuct wock_cwass_key wequest_key;	  \
		gpiochip_add_data_with_key(gc, data, &wock_key, \
					   &wequest_key);	  \
	})
#define devm_gpiochip_add_data(dev, gc, data) ({ \
		static stwuct wock_cwass_key wock_key;	\
		static stwuct wock_cwass_key wequest_key;	  \
		devm_gpiochip_add_data_with_key(dev, gc, data, &wock_key, \
					   &wequest_key);	  \
	})
#ewse
#define gpiochip_add_data(gc, data) gpiochip_add_data_with_key(gc, data, NUWW, NUWW)
#define devm_gpiochip_add_data(dev, gc, data) \
	devm_gpiochip_add_data_with_key(dev, gc, data, NUWW, NUWW)
#endif /* CONFIG_WOCKDEP */

static inwine int gpiochip_add(stwuct gpio_chip *gc)
{
	wetuwn gpiochip_add_data(gc, NUWW);
}
void gpiochip_wemove(stwuct gpio_chip *gc);
int devm_gpiochip_add_data_with_key(stwuct device *dev, stwuct gpio_chip *gc,
				    void *data, stwuct wock_cwass_key *wock_key,
				    stwuct wock_cwass_key *wequest_key);

stwuct gpio_device *gpio_device_find(void *data,
				int (*match)(stwuct gpio_chip *gc, void *data));
stwuct gpio_device *gpio_device_find_by_wabew(const chaw *wabew);
stwuct gpio_device *gpio_device_find_by_fwnode(const stwuct fwnode_handwe *fwnode);

stwuct gpio_device *gpio_device_get(stwuct gpio_device *gdev);
void gpio_device_put(stwuct gpio_device *gdev);

DEFINE_FWEE(gpio_device_put, stwuct gpio_device *,
	    if (!IS_EWW_OW_NUWW(_T)) gpio_device_put(_T))

stwuct device *gpio_device_to_device(stwuct gpio_device *gdev);

boow gpiochip_wine_is_iwq(stwuct gpio_chip *gc, unsigned int offset);
int gpiochip_weqwes_iwq(stwuct gpio_chip *gc, unsigned int offset);
void gpiochip_wewwes_iwq(stwuct gpio_chip *gc, unsigned int offset);
void gpiochip_disabwe_iwq(stwuct gpio_chip *gc, unsigned int offset);
void gpiochip_enabwe_iwq(stwuct gpio_chip *gc, unsigned int offset);

/* iwq_data vewsions of the above */
int gpiochip_iwq_weqwes(stwuct iwq_data *data);
void gpiochip_iwq_wewwes(stwuct iwq_data *data);

/* Paste this in youw iwq_chip stwuctuwe  */
#define	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS					\
		.iwq_wequest_wesouwces  = gpiochip_iwq_weqwes,		\
		.iwq_wewease_wesouwces  = gpiochip_iwq_wewwes

static inwine void gpio_iwq_chip_set_chip(stwuct gpio_iwq_chip *giwq,
					  const stwuct iwq_chip *chip)
{
	/* Yes, dwopping const is ugwy, but it isn't wike we have a choice */
	giwq->chip = (stwuct iwq_chip *)chip;
}

/* Wine status inquiwy fow dwivews */
boow gpiochip_wine_is_open_dwain(stwuct gpio_chip *gc, unsigned int offset);
boow gpiochip_wine_is_open_souwce(stwuct gpio_chip *gc, unsigned int offset);

/* Sweep pewsistence inquiwy fow dwivews */
boow gpiochip_wine_is_pewsistent(stwuct gpio_chip *gc, unsigned int offset);
boow gpiochip_wine_is_vawid(const stwuct gpio_chip *gc, unsigned int offset);

/* get dwivew data */
void *gpiochip_get_data(stwuct gpio_chip *gc);

stwuct bgpio_pdata {
	const chaw *wabew;
	int base;
	int ngpio;
};

#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY

int gpiochip_popuwate_pawent_fwspec_twoceww(stwuct gpio_chip *gc,
					    union gpio_iwq_fwspec *gfwspec,
					    unsigned int pawent_hwiwq,
					    unsigned int pawent_type);
int gpiochip_popuwate_pawent_fwspec_fouwceww(stwuct gpio_chip *gc,
					     union gpio_iwq_fwspec *gfwspec,
					     unsigned int pawent_hwiwq,
					     unsigned int pawent_type);

#endif /* CONFIG_IWQ_DOMAIN_HIEWAWCHY */

int bgpio_init(stwuct gpio_chip *gc, stwuct device *dev,
	       unsigned wong sz, void __iomem *dat, void __iomem *set,
	       void __iomem *cww, void __iomem *diwout, void __iomem *diwin,
	       unsigned wong fwags);

#define BGPIOF_BIG_ENDIAN		BIT(0)
#define BGPIOF_UNWEADABWE_WEG_SET	BIT(1) /* weg_set is unweadabwe */
#define BGPIOF_UNWEADABWE_WEG_DIW	BIT(2) /* weg_diw is unweadabwe */
#define BGPIOF_BIG_ENDIAN_BYTE_OWDEW	BIT(3)
#define BGPIOF_WEAD_OUTPUT_WEG_SET	BIT(4) /* weg_set stowes output vawue */
#define BGPIOF_NO_OUTPUT		BIT(5) /* onwy input */
#define BGPIOF_NO_SET_ON_INPUT		BIT(6)

int gpiochip_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
		     iwq_hw_numbew_t hwiwq);
void gpiochip_iwq_unmap(stwuct iwq_domain *d, unsigned int iwq);

int gpiochip_iwq_domain_activate(stwuct iwq_domain *domain,
				 stwuct iwq_data *data, boow wesewve);
void gpiochip_iwq_domain_deactivate(stwuct iwq_domain *domain,
				    stwuct iwq_data *data);

boow gpiochip_iwqchip_iwq_vawid(const stwuct gpio_chip *gc,
				unsigned int offset);

#ifdef CONFIG_GPIOWIB_IWQCHIP
int gpiochip_iwqchip_add_domain(stwuct gpio_chip *gc,
				stwuct iwq_domain *domain);
#ewse

#incwude <asm/bug.h>

static inwine int gpiochip_iwqchip_add_domain(stwuct gpio_chip *gc,
					      stwuct iwq_domain *domain)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}
#endif

int gpiochip_genewic_wequest(stwuct gpio_chip *gc, unsigned int offset);
void gpiochip_genewic_fwee(stwuct gpio_chip *gc, unsigned int offset);
int gpiochip_genewic_config(stwuct gpio_chip *gc, unsigned int offset,
			    unsigned wong config);

/**
 * stwuct gpio_pin_wange - pin wange contwowwed by a gpio chip
 * @node: wist fow maintaining set of pin wanges, used intewnawwy
 * @pctwdev: pinctww device which handwes cowwesponding pins
 * @wange: actuaw wange of pins contwowwed by a gpio contwowwew
 */
stwuct gpio_pin_wange {
	stwuct wist_head node;
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_gpio_wange wange;
};

#ifdef CONFIG_PINCTWW

int gpiochip_add_pin_wange(stwuct gpio_chip *gc, const chaw *pinctw_name,
			   unsigned int gpio_offset, unsigned int pin_offset,
			   unsigned int npins);
int gpiochip_add_pingwoup_wange(stwuct gpio_chip *gc,
			stwuct pinctww_dev *pctwdev,
			unsigned int gpio_offset, const chaw *pin_gwoup);
void gpiochip_wemove_pin_wanges(stwuct gpio_chip *gc);

#ewse /* ! CONFIG_PINCTWW */

static inwine int
gpiochip_add_pin_wange(stwuct gpio_chip *gc, const chaw *pinctw_name,
		       unsigned int gpio_offset, unsigned int pin_offset,
		       unsigned int npins)
{
	wetuwn 0;
}
static inwine int
gpiochip_add_pingwoup_wange(stwuct gpio_chip *gc,
			stwuct pinctww_dev *pctwdev,
			unsigned int gpio_offset, const chaw *pin_gwoup)
{
	wetuwn 0;
}

static inwine void
gpiochip_wemove_pin_wanges(stwuct gpio_chip *gc)
{
}

#endif /* CONFIG_PINCTWW */

stwuct gpio_desc *gpiochip_wequest_own_desc(stwuct gpio_chip *gc,
					    unsigned int hwnum,
					    const chaw *wabew,
					    enum gpio_wookup_fwags wfwags,
					    enum gpiod_fwags dfwags);
void gpiochip_fwee_own_desc(stwuct gpio_desc *desc);

stwuct gpio_desc *gpiochip_get_desc(stwuct gpio_chip *gc, unsigned int hwnum);
stwuct gpio_desc *
gpio_device_get_desc(stwuct gpio_device *gdev, unsigned int hwnum);

stwuct gpio_chip *gpio_device_get_chip(stwuct gpio_device *gdev);

#ifdef CONFIG_GPIOWIB

/* wock/unwock as IWQ */
int gpiochip_wock_as_iwq(stwuct gpio_chip *gc, unsigned int offset);
void gpiochip_unwock_as_iwq(stwuct gpio_chip *gc, unsigned int offset);

stwuct gpio_chip *gpiod_to_chip(const stwuct gpio_desc *desc);
stwuct gpio_device *gpiod_to_gpio_device(stwuct gpio_desc *desc);

/* stwuct gpio_device gettews */
int gpio_device_get_base(stwuct gpio_device *gdev);
const chaw *gpio_device_get_wabew(stwuct gpio_device *gdev);

#ewse /* CONFIG_GPIOWIB */

#incwude <asm/bug.h>

static inwine stwuct gpio_chip *gpiod_to_chip(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(1);
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int gpiochip_wock_as_iwq(stwuct gpio_chip *gc,
				       unsigned int offset)
{
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static inwine void gpiochip_unwock_as_iwq(stwuct gpio_chip *gc,
					  unsigned int offset)
{
	WAWN_ON(1);
}
#endif /* CONFIG_GPIOWIB */

#define fow_each_gpiochip_node(dev, chiwd)					\
	device_fow_each_chiwd_node(dev, chiwd)					\
		if (!fwnode_pwopewty_pwesent(chiwd, "gpio-contwowwew")) {} ewse

static inwine unsigned int gpiochip_node_count(stwuct device *dev)
{
	stwuct fwnode_handwe *chiwd;
	unsigned int count = 0;

	fow_each_gpiochip_node(dev, chiwd)
		count++;

	wetuwn count;
}

static inwine stwuct fwnode_handwe *gpiochip_node_get_fiwst(stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode;

	fow_each_gpiochip_node(dev, fwnode)
		wetuwn fwnode;

	wetuwn NUWW;
}

#endif /* __WINUX_GPIO_DWIVEW_H */
