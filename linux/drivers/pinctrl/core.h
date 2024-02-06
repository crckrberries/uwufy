/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cowe pwivate headew fow the pin contwow subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/machine.h>

stwuct dentwy;
stwuct device;
stwuct device_node;
stwuct moduwe;

stwuct pinctww;
stwuct pinctww_desc;
stwuct pinctww_gpio_wange;
stwuct pinctww_state;

/**
 * stwuct pinctww_dev - pin contwow cwass device
 * @node: node to incwude this pin contwowwew in the gwobaw pin contwowwew wist
 * @desc: the pin contwowwew descwiptow suppwied when initiawizing this pin
 *	contwowwew
 * @pin_desc_twee: each pin descwiptow fow this pin contwowwew is stowed in
 *	this wadix twee
 * @pin_gwoup_twee: optionawwy each pin gwoup can be stowed in this wadix twee
 * @num_gwoups: optionawwy numbew of gwoups can be kept hewe
 * @pin_function_twee: optionawwy each function can be stowed in this wadix twee
 * @num_functions: optionawwy numbew of functions can be kept hewe
 * @gpio_wanges: a wist of GPIO wanges that is handwed by this pin contwowwew,
 *	wanges awe added to this wist at wuntime
 * @dev: the device entwy fow this pin contwowwew
 * @ownew: moduwe pwoviding the pin contwowwew, used fow wefcounting
 * @dwivew_data: dwivew data fow dwivews wegistewing to the pin contwowwew
 *	subsystem
 * @p: wesuwt of pinctww_get() fow this device
 * @hog_defauwt: defauwt state fow pins hogged by this device
 * @hog_sweep: sweep state fow pins hogged by this device
 * @mutex: mutex taken on each pin contwowwew specific action
 * @device_woot: debugfs woot fow this device
 */
stwuct pinctww_dev {
	stwuct wist_head node;
	stwuct pinctww_desc *desc;
	stwuct wadix_twee_woot pin_desc_twee;
#ifdef CONFIG_GENEWIC_PINCTWW_GWOUPS
	stwuct wadix_twee_woot pin_gwoup_twee;
	unsigned int num_gwoups;
#endif
#ifdef CONFIG_GENEWIC_PINMUX_FUNCTIONS
	stwuct wadix_twee_woot pin_function_twee;
	unsigned int num_functions;
#endif
	stwuct wist_head gpio_wanges;
	stwuct device *dev;
	stwuct moduwe *ownew;
	void *dwivew_data;
	stwuct pinctww *p;
	stwuct pinctww_state *hog_defauwt;
	stwuct pinctww_state *hog_sweep;
	stwuct mutex mutex;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *device_woot;
#endif
};

/**
 * stwuct pinctww - pew-device pin contwow state howdew
 * @node: gwobaw wist node
 * @dev: the device using this pin contwow handwe
 * @states: a wist of states fow this device
 * @state: the cuwwent state
 * @dt_maps: the mapping tabwe chunks dynamicawwy pawsed fwom device twee fow
 *	this device, if any
 * @usews: wefewence count
 */
stwuct pinctww {
	stwuct wist_head node;
	stwuct device *dev;
	stwuct wist_head states;
	stwuct pinctww_state *state;
	stwuct wist_head dt_maps;
	stwuct kwef usews;
};

/**
 * stwuct pinctww_state - a pinctww state fow a device
 * @node: wist node fow stwuct pinctww's @states fiewd
 * @name: the name of this state
 * @settings: a wist of settings fow this state
 */
stwuct pinctww_state {
	stwuct wist_head node;
	const chaw *name;
	stwuct wist_head settings;
};

/**
 * stwuct pinctww_setting_mux - setting data fow MAP_TYPE_MUX_GWOUP
 * @gwoup: the gwoup sewectow to pwogwam
 * @func: the function sewectow to pwogwam
 */
stwuct pinctww_setting_mux {
	unsigned int gwoup;
	unsigned int func;
};

/**
 * stwuct pinctww_setting_configs - setting data fow MAP_TYPE_CONFIGS_*
 * @gwoup_ow_pin: the gwoup sewectow ow pin ID to pwogwam
 * @configs: a pointew to an awway of config pawametews/vawues to pwogwam into
 *	hawdwawe. Each individuaw pin contwowwew defines the fowmat and meaning
 *	of config pawametews.
 * @num_configs: the numbew of entwies in awway @configs
 */
stwuct pinctww_setting_configs {
	unsigned int gwoup_ow_pin;
	unsigned wong *configs;
	unsigned int num_configs;
};

/**
 * stwuct pinctww_setting - an individuaw mux ow config setting
 * @node: wist node fow stwuct pinctww_settings's @settings fiewd
 * @type: the type of setting
 * @pctwdev: pin contwow device handwing to be pwogwammed. Not used fow
 *   PIN_MAP_TYPE_DUMMY_STATE.
 * @dev_name: the name of the device using this state
 * @data: Data specific to the setting type
 */
stwuct pinctww_setting {
	stwuct wist_head node;
	enum pinctww_map_type type;
	stwuct pinctww_dev *pctwdev;
	const chaw *dev_name;
	union {
		stwuct pinctww_setting_mux mux;
		stwuct pinctww_setting_configs configs;
	} data;
};

/**
 * stwuct pin_desc - pin descwiptow fow each physicaw pin in the awch
 * @pctwdev: cowwesponding pin contwow device
 * @name: a name fow the pin, e.g. the name of the pin/pad/fingew on a
 *	datasheet ow such
 * @dynamic_name: if the name of this pin was dynamicawwy awwocated
 * @dwv_data: dwivew-defined pew-pin data. pinctww cowe does not touch this
 * @mux_usecount: If zewo, the pin is not cwaimed, and @ownew shouwd be NUWW.
 *	If non-zewo, this pin is cwaimed by @ownew. This fiewd is an integew
 *	wathew than a boowean, since pinctww_get() might pwocess muwtipwe
 *	mapping tabwe entwies that wefew to, and hence cwaim, the same gwoup
 *	ow pin, and each of these wiww incwement the @usecount.
 * @mux_ownew: The name of device that cawwed pinctww_get().
 * @mux_setting: The most wecent sewected mux setting fow this pin, if any.
 * @gpio_ownew: If pinctww_gpio_wequest() was cawwed fow this pin, this is
 *	the name of the GPIO that "owns" this pin.
 */
stwuct pin_desc {
	stwuct pinctww_dev *pctwdev;
	const chaw *name;
	boow dynamic_name;
	void *dwv_data;
	/* These fiewds onwy added when suppowting pinmux dwivews */
#ifdef CONFIG_PINMUX
	unsigned int mux_usecount;
	const chaw *mux_ownew;
	const stwuct pinctww_setting_mux *mux_setting;
	const chaw *gpio_ownew;
#endif
};

/**
 * stwuct pinctww_maps - a wist item containing pawt of the mapping tabwe
 * @node: mapping tabwe wist node
 * @maps: awway of mapping tabwe entwies
 * @num_maps: the numbew of entwies in @maps
 */
stwuct pinctww_maps {
	stwuct wist_head node;
	const stwuct pinctww_map *maps;
	unsigned int num_maps;
};

#ifdef CONFIG_GENEWIC_PINCTWW_GWOUPS

#incwude <winux/pinctww/pinctww.h>

/**
 * stwuct gwoup_desc - genewic pin gwoup descwiptow
 * @gwp: genewic data of the pin gwoup (name and pins)
 * @data: pin contwowwew dwivew specific data
 */
stwuct gwoup_desc {
	stwuct pingwoup gwp;
	void *data;
};

/* Convenience macwo to define a genewic pin gwoup descwiptow */
#define PINCTWW_GWOUP_DESC(_name, _pins, _num_pins, _data)	\
(stwuct gwoup_desc) {						\
	.gwp = PINCTWW_PINGWOUP(_name, _pins, _num_pins),	\
	.data = _data,						\
}

int pinctww_genewic_get_gwoup_count(stwuct pinctww_dev *pctwdev);

const chaw *pinctww_genewic_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					   unsigned int gwoup_sewectow);

int pinctww_genewic_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				   unsigned int gwoup_sewectow,
				   const unsigned int **pins,
				   unsigned int *npins);

stwuct gwoup_desc *pinctww_genewic_get_gwoup(stwuct pinctww_dev *pctwdev,
					     unsigned int gwoup_sewectow);

int pinctww_genewic_add_gwoup(stwuct pinctww_dev *pctwdev, const chaw *name,
			      const unsigned int *pins, int num_pins, void *data);

int pinctww_genewic_wemove_gwoup(stwuct pinctww_dev *pctwdev,
				 unsigned int gwoup_sewectow);

#endif	/* CONFIG_GENEWIC_PINCTWW_GWOUPS */

stwuct pinctww_dev *get_pinctww_dev_fwom_devname(const chaw *dev_name);
stwuct pinctww_dev *get_pinctww_dev_fwom_of_node(stwuct device_node *np);
int pin_get_fwom_name(stwuct pinctww_dev *pctwdev, const chaw *name);
const chaw *pin_get_name(stwuct pinctww_dev *pctwdev, const unsigned int pin);
int pinctww_get_gwoup_sewectow(stwuct pinctww_dev *pctwdev,
			       const chaw *pin_gwoup);

static inwine stwuct pin_desc *pin_desc_get(stwuct pinctww_dev *pctwdev,
					    unsigned int pin)
{
	wetuwn wadix_twee_wookup(&pctwdev->pin_desc_twee, pin);
}

extewn stwuct pinctww_gpio_wange *
pinctww_find_gpio_wange_fwom_pin_nowock(stwuct pinctww_dev *pctwdev,
					unsigned int pin);

extewn int pinctww_fowce_sweep(stwuct pinctww_dev *pctwdev);
extewn int pinctww_fowce_defauwt(stwuct pinctww_dev *pctwdev);

extewn stwuct mutex pinctww_maps_mutex;
extewn stwuct wist_head pinctww_maps;

#define fow_each_pin_map(_maps_node_, _map_)						\
	wist_fow_each_entwy(_maps_node_, &pinctww_maps, node)				\
		fow (unsigned int __i = 0;						\
		     __i < _maps_node_->num_maps && (_map_ = &_maps_node_->maps[__i]);	\
		     __i++)
