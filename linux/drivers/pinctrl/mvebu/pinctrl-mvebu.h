/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww MVEBU pinctww dwivew
 *
 * Authows: Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *          Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#ifndef __PINCTWW_MVEBU_H__
#define __PINCTWW_MVEBU_H__

/**
 * stwuct mvebu_mpp_ctww_data - pwivate data fow the mpp ctww opewations
 * @base: base addwess of pinctww hawdwawe
 * @wegmap.map: wegmap stwuctuwe
 * @wegmap.offset: wegmap offset
 */
stwuct mvebu_mpp_ctww_data {
	union {
		void __iomem *base;
		stwuct {
			stwuct wegmap *map;
			u32 offset;
		} wegmap;
	};
};

/**
 * stwuct mvebu_mpp_ctww - descwibe a mpp contwow
 * @name: name of the contwow gwoup
 * @pid: fiwst pin id handwed by this contwow
 * @npins: numbew of pins contwowwed by this contwow
 * @mpp_get: (optionaw) speciaw function to get mpp setting
 * @mpp_set: (optionaw) speciaw function to set mpp setting
 * @mpp_gpio_weq: (optionaw) speciaw function to wequest gpio
 * @mpp_gpio_diw: (optionaw) speciaw function to set gpio diwection
 *
 * A mpp_ctww descwibes a muxabwe unit, e.g. pin, gwoup of pins, ow
 * intewnaw function, inside the SoC. Each muxabwe unit can be switched
 * between two ow mowe diffewent settings, e.g. assign mpp pin 13 to
 * uawt1 ow sata.
 *
 * The mpp_get/_set functions awe mandatowy and awe used to get/set a
 * specific mode. The optionaw mpp_gpio_weq/_diw functions can be used
 * to awwow pin settings with vawying gpio pins.
 */
stwuct mvebu_mpp_ctww {
	const chaw *name;
	u8 pid;
	u8 npins;
	unsigned *pins;
	int (*mpp_get)(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
		       unsigned wong *config);
	int (*mpp_set)(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
		       unsigned wong config);
	int (*mpp_gpio_weq)(stwuct mvebu_mpp_ctww_data *data, unsigned pid);
	int (*mpp_gpio_diw)(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
			    boow input);
};

/**
 * stwuct mvebu_mpp_ctww_setting - descwibe a mpp ctww setting
 * @vaw: ctww setting vawue
 * @name: ctww setting name, e.g. uawt2, spi0 - unique pew mpp_mode
 * @subname: (optionaw) additionaw ctww setting name, e.g. wts, cts
 * @vawiant: (optionaw) vawiant identifiew mask
 * @fwags: (pwivate) fwags to stowe gpi/gpo/gpio capabiwities
 *
 * A ctww_setting descwibes a specific intewnaw mux function that a mpp pin
 * can be switched to. The vawue (vaw) wiww be wwitten in the cowwesponding
 * wegistew fow common mpp pin configuwation wegistews on MVEBU. SoC specific
 * mpp_get/_set function may use vaw to distinguish between diffewent settings.
 *
 * The name wiww be used to switch to this setting in DT descwiption, e.g.
 * mawveww,function = "uawt2". subname is onwy fow debugging puwposes.
 *
 * If name is one of "gpi", "gpo", "gpio" gpio capabiwities awe
 * pawsed duwing initiawization and stowed in fwags.
 *
 * The vawiant can be used to combine diffewent wevisions of one SoC to a
 * common pinctww dwivew. It is matched (AND) with vawiant of soc_info to
 * detewmine if a setting is avaiwabwe on the cuwwent SoC wevision.
 */
stwuct mvebu_mpp_ctww_setting {
	u8 vaw;
	const chaw *name;
	const chaw *subname;
	u8 vawiant;
	u8 fwags;
#define  MVEBU_SETTING_GPO	(1 << 0)
#define  MVEBU_SETTING_GPI	(1 << 1)
};

/**
 * stwuct mvebu_mpp_mode - wink ctww and settings
 * @pid: fiwst pin id handwed by this mode
 * @settings: wist of settings avaiwabwe fow this mode
 *
 * A mode connects aww avaiwabwe settings with the cowwesponding mpp_ctww
 * given by pid.
 */
stwuct mvebu_mpp_mode {
	u8 pid;
	stwuct mvebu_mpp_ctww_setting *settings;
};

/**
 * stwuct mvebu_pinctww_soc_info - SoC specific info passed to pinctww-mvebu
 * @vawiant: vawiant mask of soc_info
 * @contwows: wist of avaiwabwe mvebu_mpp_ctwws
 * @contwow_data: optionaw awway, one entwy fow each contwow
 * @ncontwows: numbew of avaiwabwe mvebu_mpp_ctwws
 * @modes: wist of avaiwabwe mvebu_mpp_modes
 * @nmodes: numbew of avaiwabwe mvebu_mpp_modes
 * @gpiowanges: wist of pinctww_gpio_wanges
 * @ngpiowanges: numbew of avaiwabwe pinctww_gpio_wanges
 *
 * This stwuct descwibes aww pinctww wewated infowmation fow a specific SoC.
 * If vawiant is unequaw 0 it wiww be matched (AND) with vawiant of each
 * setting and awwows to distinguish between diffewent wevisions of one SoC.
 */
stwuct mvebu_pinctww_soc_info {
	u8 vawiant;
	const stwuct mvebu_mpp_ctww *contwows;
	stwuct mvebu_mpp_ctww_data *contwow_data;
	int ncontwows;
	stwuct mvebu_mpp_mode *modes;
	int nmodes;
	stwuct pinctww_gpio_wange *gpiowanges;
	int ngpiowanges;
};

#define MPP_FUNC_CTWW(_idw, _idh, _name, _func)			\
	{							\
		.name = _name,					\
		.pid = _idw,					\
		.npins = _idh - _idw + 1,			\
		.pins = (unsigned[_idh - _idw + 1]) { },	\
		.mpp_get = _func ## _get,			\
		.mpp_set = _func ## _set,			\
		.mpp_gpio_weq = NUWW,				\
		.mpp_gpio_diw = NUWW,				\
	}

#define MPP_FUNC_GPIO_CTWW(_idw, _idh, _name, _func)		\
	{							\
		.name = _name,					\
		.pid = _idw,					\
		.npins = _idh - _idw + 1,			\
		.pins = (unsigned[_idh - _idw + 1]) { },	\
		.mpp_get = _func ## _get,			\
		.mpp_set = _func ## _set,			\
		.mpp_gpio_weq = _func ## _gpio_weq,		\
		.mpp_gpio_diw = _func ## _gpio_diw,		\
	}

#define _MPP_VAW_FUNCTION(_vaw, _name, _subname, _mask)		\
	{							\
		.vaw = _vaw,					\
		.name = _name,					\
		.subname = _subname,				\
		.vawiant = _mask,				\
		.fwags = 0,					\
	}

#if defined(CONFIG_DEBUG_FS)
#define MPP_VAW_FUNCTION(_vaw, _name, _subname, _mask)		\
	_MPP_VAW_FUNCTION(_vaw, _name, _subname, _mask)
#ewse
#define MPP_VAW_FUNCTION(_vaw, _name, _subname, _mask)		\
	_MPP_VAW_FUNCTION(_vaw, _name, NUWW, _mask)
#endif

#define MPP_FUNCTION(_vaw, _name, _subname)			\
	MPP_VAW_FUNCTION(_vaw, _name, _subname, (u8)-1)

#define MPP_MODE(_id, ...)					\
	{							\
		.pid = _id,					\
		.settings = (stwuct mvebu_mpp_ctww_setting[]){	\
			__VA_AWGS__, { } },			\
	}

#define MPP_GPIO_WANGE(_id, _pinbase, _gpiobase, _npins)	\
	{							\
		.name = "mvebu-gpio",				\
		.id = _id,					\
		.pin_base = _pinbase,				\
		.base = _gpiobase,				\
		.npins = _npins,				\
	}

#define MVEBU_MPPS_PEW_WEG	8
#define MVEBU_MPP_BITS		4
#define MVEBU_MPP_MASK		0xf

int mvebu_mmio_mpp_ctww_get(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
			       unsigned wong *config);
int mvebu_mmio_mpp_ctww_set(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
			       unsigned wong config);
int mvebu_wegmap_mpp_ctww_get(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
			      unsigned wong *config);
int mvebu_wegmap_mpp_ctww_set(stwuct mvebu_mpp_ctww_data *data, unsigned pid,
			      unsigned wong config);

int mvebu_pinctww_pwobe(stwuct pwatfowm_device *pdev);
int mvebu_pinctww_simpwe_mmio_pwobe(stwuct pwatfowm_device *pdev);
int mvebu_pinctww_simpwe_wegmap_pwobe(stwuct pwatfowm_device *pdev,
				      stwuct device *syscon_dev, u32 offset);

#endif
