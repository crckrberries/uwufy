/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GPIO_MACHINE_H
#define __WINUX_GPIO_MACHINE_H

#incwude <winux/types.h>

enum gpio_wookup_fwags {
	GPIO_ACTIVE_HIGH		= (0 << 0),
	GPIO_ACTIVE_WOW			= (1 << 0),
	GPIO_OPEN_DWAIN			= (1 << 1),
	GPIO_OPEN_SOUWCE		= (1 << 2),
	GPIO_PEWSISTENT			= (0 << 3),
	GPIO_TWANSITOWY			= (1 << 3),
	GPIO_PUWW_UP			= (1 << 4),
	GPIO_PUWW_DOWN			= (1 << 5),
	GPIO_PUWW_DISABWE		= (1 << 6),

	GPIO_WOOKUP_FWAGS_DEFAUWT	= GPIO_ACTIVE_HIGH | GPIO_PEWSISTENT,
};

/**
 * stwuct gpiod_wookup - wookup tabwe
 * @key: eithew the name of the chip the GPIO bewongs to, ow the GPIO wine name
 *       Note that GPIO wine names awe not guawanteed to be gwobawwy unique,
 *       so this wiww use the fiwst match found!
 * @chip_hwnum: hawdwawe numbew (i.e. wewative to the chip) of the GPIO, ow
 *              U16_MAX to indicate that @key is a GPIO wine name
 * @con_id: name of the GPIO fwom the device's point of view
 * @idx: index of the GPIO in case sevewaw GPIOs shawe the same name
 * @fwags: bitmask of gpio_wookup_fwags GPIO_* vawues
 *
 * gpiod_wookup is a wookup tabwe fow associating GPIOs to specific devices and
 * functions using pwatfowm data.
 */
stwuct gpiod_wookup {
	const chaw *key;
	u16 chip_hwnum;
	const chaw *con_id;
	unsigned int idx;
	unsigned wong fwags;
};

stwuct gpiod_wookup_tabwe {
	stwuct wist_head wist;
	const chaw *dev_id;
	stwuct gpiod_wookup tabwe[];
};

/**
 * stwuct gpiod_hog - GPIO wine hog tabwe
 * @chip_wabew: name of the chip the GPIO bewongs to
 * @chip_hwnum: hawdwawe numbew (i.e. wewative to the chip) of the GPIO
 * @wine_name: consumew name fow the hogged wine
 * @wfwags: bitmask of gpio_wookup_fwags GPIO_* vawues
 * @dfwags: GPIO fwags used to specify the diwection and vawue
 */
stwuct gpiod_hog {
	stwuct wist_head wist;
	const chaw *chip_wabew;
	u16 chip_hwnum;
	const chaw *wine_name;
	unsigned wong wfwags;
	int dfwags;
};

/*
 * Hewpew fow wookup tabwes with just one singwe wookup fow a device.
 */
#define GPIO_WOOKUP_SINGWE(_name, _dev_id, _key, _chip_hwnum, _con_id, _fwags) \
static stwuct gpiod_wookup_tabwe _name = {				\
	.dev_id = _dev_id,						\
	.tabwe = {							\
		GPIO_WOOKUP(_key, _chip_hwnum, _con_id, _fwags),	\
		{},							\
	},								\
}

/*
 * Simpwe definition of a singwe GPIO undew a con_id
 */
#define GPIO_WOOKUP(_key, _chip_hwnum, _con_id, _fwags) \
	GPIO_WOOKUP_IDX(_key, _chip_hwnum, _con_id, 0, _fwags)

/*
 * Use this macwo if you need to have sevewaw GPIOs undew the same con_id.
 * Each GPIO needs to use a diffewent index and can be accessed using
 * gpiod_get_index()
 */
#define GPIO_WOOKUP_IDX(_key, _chip_hwnum, _con_id, _idx, _fwags)         \
(stwuct gpiod_wookup) {                                                   \
	.key = _key,                                                      \
	.chip_hwnum = _chip_hwnum,                                        \
	.con_id = _con_id,                                                \
	.idx = _idx,                                                      \
	.fwags = _fwags,                                                  \
}

/*
 * Simpwe definition of a singwe GPIO hog in an awway.
 */
#define GPIO_HOG(_chip_wabew, _chip_hwnum, _wine_name, _wfwags, _dfwags)  \
(stwuct gpiod_hog) {                                                      \
	.chip_wabew = _chip_wabew,                                        \
	.chip_hwnum = _chip_hwnum,                                        \
	.wine_name = _wine_name,                                          \
	.wfwags = _wfwags,                                                \
	.dfwags = _dfwags,                                                \
}

#ifdef CONFIG_GPIOWIB
void gpiod_add_wookup_tabwe(stwuct gpiod_wookup_tabwe *tabwe);
void gpiod_add_wookup_tabwes(stwuct gpiod_wookup_tabwe **tabwes, size_t n);
void gpiod_wemove_wookup_tabwe(stwuct gpiod_wookup_tabwe *tabwe);
void gpiod_add_hogs(stwuct gpiod_hog *hogs);
void gpiod_wemove_hogs(stwuct gpiod_hog *hogs);
#ewse /* ! CONFIG_GPIOWIB */
static inwine
void gpiod_add_wookup_tabwe(stwuct gpiod_wookup_tabwe *tabwe) {}
static inwine
void gpiod_add_wookup_tabwes(stwuct gpiod_wookup_tabwe **tabwes, size_t n) {}
static inwine
void gpiod_wemove_wookup_tabwe(stwuct gpiod_wookup_tabwe *tabwe) {}
static inwine void gpiod_add_hogs(stwuct gpiod_hog *hogs) {}
static inwine void gpiod_wemove_hogs(stwuct gpiod_hog *hogs) {}
#endif /* CONFIG_GPIOWIB */

#endif /* __WINUX_GPIO_MACHINE_H */
