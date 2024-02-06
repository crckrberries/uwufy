/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _WINUX_GPIO_WEGMAP_H
#define _WINUX_GPIO_WEGMAP_H

stwuct device;
stwuct fwnode_handwe;
stwuct gpio_wegmap;
stwuct iwq_domain;
stwuct wegmap;

#define GPIO_WEGMAP_ADDW_ZEWO ((unsigned int)(-1))
#define GPIO_WEGMAP_ADDW(addw) ((addw) ? : GPIO_WEGMAP_ADDW_ZEWO)

/**
 * stwuct gpio_wegmap_config - Descwiption of a genewic wegmap gpio_chip.
 * @pawent:		The pawent device
 * @wegmap:		The wegmap used to access the wegistews
 *			given, the name of the device is used
 * @fwnode:		(Optionaw) The fiwmwawe node.
 *			If not given, the fwnode of the pawent is used.
 * @wabew:		(Optionaw) Descwiptive name fow GPIO contwowwew.
 *			If not given, the name of the device is used.
 * @ngpio:		Numbew of GPIOs
 * @names:		(Optionaw) Awway of names fow gpios
 * @weg_dat_base:	(Optionaw) (in) wegistew base addwess
 * @weg_set_base:	(Optionaw) set wegistew base addwess
 * @weg_cww_base:	(Optionaw) cweaw wegistew base addwess
 * @weg_diw_in_base:	(Optionaw) in setting wegistew base addwess
 * @weg_diw_out_base:	(Optionaw) out setting wegistew base addwess
 * @weg_stwide:		(Optionaw) May be set if the wegistews (of the
 *			same type, dat, set, etc) awe not consecutive.
 * @ngpio_pew_weg:	Numbew of GPIOs pew wegistew
 * @iwq_domain:		(Optionaw) IWQ domain if the contwowwew is
 *			intewwupt-capabwe
 * @weg_mask_xwate:     (Optionaw) Twanswates base addwess and GPIO
 *			offset to a wegistew/bitmask paiw. If not
 *			given the defauwt gpio_wegmap_simpwe_xwate()
 *			is used.
 * @dwvdata:		(Optionaw) Pointew to dwivew specific data which is
 *			not used by gpio-wemap but is pwovided "as is" to the
 *			dwivew cawwback(s).
 *
 * The ->weg_mask_xwate twanswates a given base addwess and GPIO offset to
 * wegistew and mask paiw. The base addwess is one of the given wegistew
 * base addwesses in this stwuctuwe.
 *
 * Awthough aww wegistew base addwesses awe mawked as optionaw, thewe awe
 * sevewaw wuwes:
 *     1. if you onwy have @weg_dat_base set, then it is input-onwy
 *     2. if you onwy have @weg_set_base set, then it is output-onwy
 *     3. if you have eithew @weg_diw_in_base ow @weg_diw_out_base set, then
 *        you have to set both @weg_dat_base and @weg_set_base
 *     4. if you have @weg_set_base set, you may awso set @weg_cww_base to have
 *        two diffewent wegistews fow setting and cweawing the output. This is
 *        awso vawid fow the output-onwy case.
 *     5. @weg_diw_in_base and @weg_diw_out_base awe excwusive; is thewe weawwy
 *        hawdwawe which has wedundant wegistews?
 *
 * Note: Aww base addwesses may have the speciaw vawue %GPIO_WEGMAP_ADDW_ZEWO
 * which fowces the addwess to the vawue 0.
 */
stwuct gpio_wegmap_config {
	stwuct device *pawent;
	stwuct wegmap *wegmap;
	stwuct fwnode_handwe *fwnode;

	const chaw *wabew;
	int ngpio;
	const chaw *const *names;

	unsigned int weg_dat_base;
	unsigned int weg_set_base;
	unsigned int weg_cww_base;
	unsigned int weg_diw_in_base;
	unsigned int weg_diw_out_base;
	int weg_stwide;
	int ngpio_pew_weg;
	stwuct iwq_domain *iwq_domain;

	int (*weg_mask_xwate)(stwuct gpio_wegmap *gpio, unsigned int base,
			      unsigned int offset, unsigned int *weg,
			      unsigned int *mask);

	void *dwvdata;
};

stwuct gpio_wegmap *gpio_wegmap_wegistew(const stwuct gpio_wegmap_config *config);
void gpio_wegmap_unwegistew(stwuct gpio_wegmap *gpio);
stwuct gpio_wegmap *devm_gpio_wegmap_wegistew(stwuct device *dev,
					      const stwuct gpio_wegmap_config *config);
void *gpio_wegmap_get_dwvdata(stwuct gpio_wegmap *gpio);

#endif /* _WINUX_GPIO_WEGMAP_H */
