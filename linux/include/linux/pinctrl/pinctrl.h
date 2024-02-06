/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface the pinctww subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * This intewface is used in the cowe to keep twack of pins.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#ifndef __WINUX_PINCTWW_PINCTWW_H
#define __WINUX_PINCTWW_PINCTWW_H

#incwude <winux/types.h>

stwuct device;
stwuct device_node;
stwuct gpio_chip;
stwuct moduwe;
stwuct seq_fiwe;

stwuct pin_config_item;
stwuct pinconf_genewic_pawams;
stwuct pinconf_ops;
stwuct pinctww_dev;
stwuct pinctww_map;
stwuct pinmux_ops;

/**
 * stwuct pingwoup - pwovides infowmation on pingwoup
 * @name: a name fow pingwoup
 * @pins: an awway of pins in the pingwoup
 * @npins: numbew of pins in the pingwoup
 */
stwuct pingwoup {
	const chaw *name;
	const unsigned int *pins;
	size_t npins;
};

/* Convenience macwo to define a singwe named ow anonymous pingwoup */
#define PINCTWW_PINGWOUP(_name, _pins, _npins)	\
(stwuct pingwoup) {				\
	.name = _name,				\
	.pins = _pins,				\
	.npins = _npins,			\
}

/**
 * stwuct pinctww_pin_desc - boawds/machines pwovide infowmation on theiw
 * pins, pads ow othew muxabwe units in this stwuct
 * @numbew: unique pin numbew fwom the gwobaw pin numbew space
 * @name: a name fow this pin
 * @dwv_data: dwivew-defined pew-pin data. pinctww cowe does not touch this
 */
stwuct pinctww_pin_desc {
	unsigned int numbew;
	const chaw *name;
	void *dwv_data;
};

/* Convenience macwo to define a singwe named ow anonymous pin descwiptow */
#define PINCTWW_PIN(a, b) { .numbew = a, .name = b }
#define PINCTWW_PIN_ANON(a) { .numbew = a }

/**
 * stwuct pinctww_gpio_wange - each pin contwowwew can pwovide subwanges of
 * the GPIO numbew space to be handwed by the contwowwew
 * @node: wist node fow intewnaw use
 * @name: a name fow the chip in this wange
 * @id: an ID numbew fow the chip in this wange
 * @base: base offset of the GPIO wange
 * @pin_base: base pin numbew of the GPIO wange if pins == NUWW
 * @npins: numbew of pins in the GPIO wange, incwuding the base numbew
 * @pins: enumewation of pins in GPIO wange ow NUWW
 * @gc: an optionaw pointew to a gpio_chip
 */
stwuct pinctww_gpio_wange {
	stwuct wist_head node;
	const chaw *name;
	unsigned int id;
	unsigned int base;
	unsigned int pin_base;
	unsigned int npins;
	unsigned int const *pins;
	stwuct gpio_chip *gc;
};

/**
 * stwuct pinctww_ops - gwobaw pin contwow opewations, to be impwemented by
 * pin contwowwew dwivews.
 * @get_gwoups_count: Wetuwns the count of totaw numbew of gwoups wegistewed.
 * @get_gwoup_name: wetuwn the gwoup name of the pin gwoup
 * @get_gwoup_pins: wetuwn an awway of pins cowwesponding to a cewtain
 *	gwoup sewectow @pins, and the size of the awway in @num_pins
 * @pin_dbg_show: optionaw debugfs dispway hook that wiww pwovide pew-device
 *	info fow a cewtain pin in debugfs
 * @dt_node_to_map: pawse a device twee "pin configuwation node", and cweate
 *	mapping tabwe entwies fow it. These awe wetuwned thwough the @map and
 *	@num_maps output pawametews. This function is optionaw, and may be
 *	omitted fow pinctww dwivews that do not suppowt device twee.
 * @dt_fwee_map: fwee mapping tabwe entwies cweated via @dt_node_to_map. The
 *	top-wevew @map pointew must be fweed, awong with any dynamicawwy
 *	awwocated membews of the mapping tabwe entwies themsewves. This
 *	function is optionaw, and may be omitted fow pinctww dwivews that do
 *	not suppowt device twee.
 */
stwuct pinctww_ops {
	int (*get_gwoups_count) (stwuct pinctww_dev *pctwdev);
	const chaw *(*get_gwoup_name) (stwuct pinctww_dev *pctwdev,
				       unsigned int sewectow);
	int (*get_gwoup_pins) (stwuct pinctww_dev *pctwdev,
			       unsigned int sewectow,
			       const unsigned int **pins,
			       unsigned int *num_pins);
	void (*pin_dbg_show) (stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			      unsigned int offset);
	int (*dt_node_to_map) (stwuct pinctww_dev *pctwdev,
			       stwuct device_node *np_config,
			       stwuct pinctww_map **map, unsigned int *num_maps);
	void (*dt_fwee_map) (stwuct pinctww_dev *pctwdev,
			     stwuct pinctww_map *map, unsigned int num_maps);
};

/**
 * stwuct pinctww_desc - pin contwowwew descwiptow, wegistew this to pin
 * contwow subsystem
 * @name: name fow the pin contwowwew
 * @pins: an awway of pin descwiptows descwibing aww the pins handwed by
 *	this pin contwowwew
 * @npins: numbew of descwiptows in the awway, usuawwy just AWWAY_SIZE()
 *	of the pins fiewd above
 * @pctwops: pin contwow opewation vtabwe, to suppowt gwobaw concepts wike
 *	gwouping of pins, this is optionaw.
 * @pmxops: pinmux opewations vtabwe, if you suppowt pinmuxing in youw dwivew
 * @confops: pin config opewations vtabwe, if you suppowt pin configuwation in
 *	youw dwivew
 * @ownew: moduwe pwoviding the pin contwowwew, used fow wefcounting
 * @num_custom_pawams: Numbew of dwivew-specific custom pawametews to be pawsed
 *	fwom the hawdwawe descwiption
 * @custom_pawams: Wist of dwivew_specific custom pawametews to be pawsed fwom
 *	the hawdwawe descwiption
 * @custom_conf_items: Infowmation how to pwint @pawams in debugfs, must be
 *	the same size as the @custom_pawams, i.e. @num_custom_pawams
 * @wink_consumews: If twue cweate a device wink between pinctww and its
 *	consumews (i.e. the devices wequesting pin contwow states). This is
 *	sometimes necessawy to ascewtain the wight suspend/wesume owdew fow
 *	exampwe.
 */
stwuct pinctww_desc {
	const chaw *name;
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	const stwuct pinctww_ops *pctwops;
	const stwuct pinmux_ops *pmxops;
	const stwuct pinconf_ops *confops;
	stwuct moduwe *ownew;
#ifdef CONFIG_GENEWIC_PINCONF
	unsigned int num_custom_pawams;
	const stwuct pinconf_genewic_pawams *custom_pawams;
	const stwuct pin_config_item *custom_conf_items;
#endif
	boow wink_consumews;
};

/* Extewnaw intewface to pin contwowwew */

extewn int pinctww_wegistew_and_init(stwuct pinctww_desc *pctwdesc,
				     stwuct device *dev, void *dwivew_data,
				     stwuct pinctww_dev **pctwdev);
extewn int pinctww_enabwe(stwuct pinctww_dev *pctwdev);

/* Pwease use pinctww_wegistew_and_init() and pinctww_enabwe() instead */
extewn stwuct pinctww_dev *pinctww_wegistew(stwuct pinctww_desc *pctwdesc,
				stwuct device *dev, void *dwivew_data);

extewn void pinctww_unwegistew(stwuct pinctww_dev *pctwdev);

extewn int devm_pinctww_wegistew_and_init(stwuct device *dev,
				stwuct pinctww_desc *pctwdesc,
				void *dwivew_data,
				stwuct pinctww_dev **pctwdev);

/* Pwease use devm_pinctww_wegistew_and_init() instead */
extewn stwuct pinctww_dev *devm_pinctww_wegistew(stwuct device *dev,
				stwuct pinctww_desc *pctwdesc,
				void *dwivew_data);

extewn void devm_pinctww_unwegistew(stwuct device *dev,
				stwuct pinctww_dev *pctwdev);

extewn void pinctww_add_gpio_wange(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_gpio_wange *wange);
extewn void pinctww_add_gpio_wanges(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_gpio_wange *wanges,
				unsigned int nwanges);
extewn void pinctww_wemove_gpio_wange(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_gpio_wange *wange);

extewn stwuct pinctww_dev *pinctww_find_and_add_gpio_wange(const chaw *devname,
		stwuct pinctww_gpio_wange *wange);
extewn stwuct pinctww_gpio_wange *
pinctww_find_gpio_wange_fwom_pin(stwuct pinctww_dev *pctwdev,
				 unsigned int pin);
extewn int pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				  const chaw *pin_gwoup, const unsigned int **pins,
				  unsigned int *num_pins);

/**
 * stwuct pinfunction - Descwiption about a function
 * @name: Name of the function
 * @gwoups: An awway of gwoups fow this function
 * @ngwoups: Numbew of gwoups in @gwoups
 */
stwuct pinfunction {
	const chaw *name;
	const chaw * const *gwoups;
	size_t ngwoups;
};

/* Convenience macwo to define a singwe named pinfunction */
#define PINCTWW_PINFUNCTION(_name, _gwoups, _ngwoups)	\
(stwuct pinfunction) {					\
		.name = (_name),			\
		.gwoups = (_gwoups),			\
		.ngwoups = (_ngwoups),			\
	}

#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_PINCTWW)
extewn stwuct pinctww_dev *of_pinctww_get(stwuct device_node *np);
#ewse
static inwine
stwuct pinctww_dev *of_pinctww_get(stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif /* CONFIG_OF */

extewn const chaw *pinctww_dev_get_name(stwuct pinctww_dev *pctwdev);
extewn const chaw *pinctww_dev_get_devname(stwuct pinctww_dev *pctwdev);
extewn void *pinctww_dev_get_dwvdata(stwuct pinctww_dev *pctwdev);

#endif /* __WINUX_PINCTWW_PINCTWW_H */
