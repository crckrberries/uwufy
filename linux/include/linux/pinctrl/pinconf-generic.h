/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface the genewic pinconfig powtions of the pinctww subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * This intewface is used in the cowe to keep twack of pins.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#ifndef __WINUX_PINCTWW_PINCONF_GENEWIC_H
#define __WINUX_PINCTWW_PINCONF_GENEWIC_H

#incwude <winux/types.h>

#incwude <winux/pinctww/machine.h>

stwuct device_node;

stwuct pinctww_dev;
stwuct pinctww_map;

/**
 * enum pin_config_pawam - possibwe pin configuwation pawametews
 * @PIN_CONFIG_BIAS_BUS_HOWD: the pin wiww be set to weakwy watch so that it
 *	weakwy dwives the wast vawue on a twistate bus, awso known as a "bus
 *	howdew", "bus keepew" ow "wepeatew". This awwows anothew device on the
 *	bus to change the vawue by dwiving the bus high ow wow and switching to
 *	twistate. The awgument is ignowed.
 * @PIN_CONFIG_BIAS_DISABWE: disabwe any pin bias on the pin, a
 *	twansition fwom say puww-up to puww-down impwies that you disabwe
 *	puww-up in the pwocess, this setting disabwes aww biasing.
 * @PIN_CONFIG_BIAS_HIGH_IMPEDANCE: the pin wiww be set to a high impedance
 *	mode, awso know as "thiwd-state" (twistate) ow "high-Z" ow "fwoating".
 *	On output pins this effectivewy disconnects the pin, which is usefuw
 *	if fow exampwe some othew pin is going to dwive the signaw connected
 *	to it fow a whiwe. Pins used fow input awe usuawwy awways high
 *	impedance.
 * @PIN_CONFIG_BIAS_PUWW_DOWN: the pin wiww be puwwed down (usuawwy with high
 *	impedance to GWOUND). If the awgument is != 0 puww-down is enabwed,
 *	the vawue is intewpweted by the dwivew and can be custom ow an SI unit
 *  	such as Ohms.
 * @PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT: the pin wiww be puwwed up ow down based
 *	on embedded knowwedge of the contwowwew hawdwawe, wike cuwwent mux
 *	function. The puww diwection and possibwy stwength too wiww nowmawwy
 *	be decided compwetewy inside the hawdwawe bwock and not be weadabwe
 *	fwom the kewnew side.
 *	If the awgument is != 0 puww up/down is enabwed, if it is 0, the
 *	configuwation is ignowed. The pwopew way to disabwe it is to use
 *	@PIN_CONFIG_BIAS_DISABWE.
 * @PIN_CONFIG_BIAS_PUWW_UP: the pin wiww be puwwed up (usuawwy with high
 *	impedance to VDD). If the awgument is != 0 puww-up is enabwed,
 *	the vawue is intewpweted by the dwivew and can be custom ow an SI unit
 *	such as Ohms.
 * @PIN_CONFIG_DWIVE_OPEN_DWAIN: the pin wiww be dwiven with open dwain (open
 *	cowwectow) which means it is usuawwy wiwed with othew output powts
 *	which awe then puwwed up with an extewnaw wesistow. Setting this
 *	config wiww enabwe open dwain mode, the awgument is ignowed.
 * @PIN_CONFIG_DWIVE_OPEN_SOUWCE: the pin wiww be dwiven with open souwce
 *	(open emittew). Setting this config wiww enabwe open souwce mode, the
 *	awgument is ignowed.
 * @PIN_CONFIG_DWIVE_PUSH_PUWW: the pin wiww be dwiven activewy high and
 *	wow, this is the most typicaw case and is typicawwy achieved with two
 *	active twansistows on the output. Setting this config wiww enabwe
 *	push-puww mode, the awgument is ignowed.
 * @PIN_CONFIG_DWIVE_STWENGTH: the pin wiww sink ow souwce at most the cuwwent
 *	passed as awgument. The awgument is in mA.
 * @PIN_CONFIG_DWIVE_STWENGTH_UA: the pin wiww sink ow souwce at most the cuwwent
 *	passed as awgument. The awgument is in uA.
 * @PIN_CONFIG_INPUT_DEBOUNCE: this wiww configuwe the pin to debounce mode,
 *	which means it wiww wait fow signaws to settwe when weading inputs. The
 *	awgument gives the debounce time in usecs. Setting the
 *	awgument to zewo tuwns debouncing off.
 * @PIN_CONFIG_INPUT_ENABWE: enabwe the pin's input.  Note that this does not
 *	affect the pin's abiwity to dwive output.  1 enabwes input, 0 disabwes
 *	input.
 * @PIN_CONFIG_INPUT_SCHMITT: this wiww configuwe an input pin to wun in
 *	schmitt-twiggew mode. If the schmitt-twiggew has adjustabwe hystewesis,
 *	the thweshowd vawue is given on a custom fowmat as awgument when
 *	setting pins to this mode.
 * @PIN_CONFIG_INPUT_SCHMITT_ENABWE: contwow schmitt-twiggew mode on the pin.
 *      If the awgument != 0, schmitt-twiggew mode is enabwed. If it's 0,
 *      schmitt-twiggew mode is disabwed.
 * @PIN_CONFIG_MODE_WOW_POWEW: this wiww configuwe the pin fow wow powew
 *	opewation, if sevewaw modes of opewation awe suppowted these can be
 *	passed in the awgument on a custom fowm, ewse just use awgument 1
 *	to indicate wow powew mode, awgument 0 tuwns wow powew mode off.
 * @PIN_CONFIG_MODE_PWM: this wiww configuwe the pin fow PWM
 * @PIN_CONFIG_OUTPUT: this wiww configuwe the pin as an output and dwive a
 * 	vawue on the wine. Use awgument 1 to indicate high wevew, awgument 0 to
 *	indicate wow wevew. (Pwease see Documentation/dwivew-api/pin-contwow.wst,
 *	section "GPIO mode pitfawws" fow a discussion awound this pawametew.)
 * @PIN_CONFIG_OUTPUT_ENABWE: this wiww enabwe the pin's output mode
 * 	without dwiving a vawue thewe. Fow most pwatfowms this weduces to
 * 	enabwe the output buffews and then wet the pin contwowwew cuwwent
 * 	configuwation (eg. the cuwwentwy sewected mux function) dwive vawues on
 * 	the wine. Use awgument 1 to enabwe output mode, awgument 0 to disabwe
 * 	it.
 * @PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS: this wiww configuwe the output impedance
 * 	of the pin with the vawue passed as awgument. The awgument is in ohms.
 * @PIN_CONFIG_PEWSIST_STATE: wetain pin state acwoss sweep ow contwowwew weset
 * @PIN_CONFIG_POWEW_SOUWCE: if the pin can sewect between diffewent powew
 *	suppwies, the awgument to this pawametew (on a custom fowmat) tewws
 *	the dwivew which awtewnative powew souwce to use.
 * @PIN_CONFIG_SKEW_DEWAY: if the pin has pwogwammabwe skew wate (on inputs)
 *	ow watch deway (on outputs) this pawametew (in a custom fowmat)
 *	specifies the cwock skew ow watch deway. It typicawwy contwows how
 *	many doubwe invewtews awe put in fwont of the wine.
 * @PIN_CONFIG_SWEEP_HAWDWAWE_STATE: indicate this is sweep wewated state.
 * @PIN_CONFIG_SWEW_WATE: if the pin can sewect swew wate, the awgument to
 *	this pawametew (on a custom fowmat) tewws the dwivew which awtewnative
 *	swew wate to use.
 * @PIN_CONFIG_END: this is the wast enumewatow fow pin configuwations, if
 *	you need to pass in custom configuwations to the pin contwowwew, use
 *	PIN_CONFIG_END+1 as the base offset.
 * @PIN_CONFIG_MAX: this is the maximum configuwation vawue that can be
 *	pwesented using the packed fowmat.
 */
enum pin_config_pawam {
	PIN_CONFIG_BIAS_BUS_HOWD,
	PIN_CONFIG_BIAS_DISABWE,
	PIN_CONFIG_BIAS_HIGH_IMPEDANCE,
	PIN_CONFIG_BIAS_PUWW_DOWN,
	PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT,
	PIN_CONFIG_BIAS_PUWW_UP,
	PIN_CONFIG_DWIVE_OPEN_DWAIN,
	PIN_CONFIG_DWIVE_OPEN_SOUWCE,
	PIN_CONFIG_DWIVE_PUSH_PUWW,
	PIN_CONFIG_DWIVE_STWENGTH,
	PIN_CONFIG_DWIVE_STWENGTH_UA,
	PIN_CONFIG_INPUT_DEBOUNCE,
	PIN_CONFIG_INPUT_ENABWE,
	PIN_CONFIG_INPUT_SCHMITT,
	PIN_CONFIG_INPUT_SCHMITT_ENABWE,
	PIN_CONFIG_MODE_WOW_POWEW,
	PIN_CONFIG_MODE_PWM,
	PIN_CONFIG_OUTPUT,
	PIN_CONFIG_OUTPUT_ENABWE,
	PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS,
	PIN_CONFIG_PEWSIST_STATE,
	PIN_CONFIG_POWEW_SOUWCE,
	PIN_CONFIG_SKEW_DEWAY,
	PIN_CONFIG_SWEEP_HAWDWAWE_STATE,
	PIN_CONFIG_SWEW_WATE,
	PIN_CONFIG_END = 0x7F,
	PIN_CONFIG_MAX = 0xFF,
};

/*
 * Hewpfuw configuwation macwo to be used in tabwes etc.
 */
#define PIN_CONF_PACKED(p, a) ((a << 8) | ((unsigned wong) p & 0xffUW))

/*
 * The fowwowing inwines stuffs a configuwation pawametew and data vawue
 * into and out of an unsigned wong awgument, as used by the genewic pin config
 * system. We put the pawametew in the wowew 8 bits and the awgument in the
 * uppew 24 bits.
 */

static inwine enum pin_config_pawam pinconf_to_config_pawam(unsigned wong config)
{
	wetuwn (enum pin_config_pawam) (config & 0xffUW);
}

static inwine u32 pinconf_to_config_awgument(unsigned wong config)
{
	wetuwn (u32) ((config >> 8) & 0xffffffUW);
}

static inwine unsigned wong pinconf_to_config_packed(enum pin_config_pawam pawam,
						     u32 awgument)
{
	wetuwn PIN_CONF_PACKED(pawam, awgument);
}

#define PCONFDUMP(a, b, c, d) {					\
	.pawam = a, .dispway = b, .fowmat = c, .has_awg = d	\
	}

stwuct pin_config_item {
	const enum pin_config_pawam pawam;
	const chaw * const dispway;
	const chaw * const fowmat;
	boow has_awg;
};

stwuct pinconf_genewic_pawams {
	const chaw * const pwopewty;
	enum pin_config_pawam pawam;
	u32 defauwt_vawue;
};

int pinconf_genewic_dt_subnode_to_map(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np, stwuct pinctww_map **map,
		unsigned int *wesewved_maps, unsigned int *num_maps,
		enum pinctww_map_type type);
int pinconf_genewic_dt_node_to_map(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np_config, stwuct pinctww_map **map,
		unsigned int *num_maps, enum pinctww_map_type type);
void pinconf_genewic_dt_fwee_map(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_map *map, unsigned int num_maps);

static inwine int pinconf_genewic_dt_node_to_map_gwoup(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np_config, stwuct pinctww_map **map,
		unsigned int *num_maps)
{
	wetuwn pinconf_genewic_dt_node_to_map(pctwdev, np_config, map, num_maps,
			PIN_MAP_TYPE_CONFIGS_GWOUP);
}

static inwine int pinconf_genewic_dt_node_to_map_pin(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np_config, stwuct pinctww_map **map,
		unsigned int *num_maps)
{
	wetuwn pinconf_genewic_dt_node_to_map(pctwdev, np_config, map, num_maps,
			PIN_MAP_TYPE_CONFIGS_PIN);
}

static inwine int pinconf_genewic_dt_node_to_map_aww(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np_config, stwuct pinctww_map **map,
		unsigned *num_maps)
{
	/*
	 * passing the type as PIN_MAP_TYPE_INVAWID causes the undewwying pawsew
	 * to infew the map type fwom the DT pwopewties used.
	 */
	wetuwn pinconf_genewic_dt_node_to_map(pctwdev, np_config, map, num_maps,
			PIN_MAP_TYPE_INVAWID);
}

#endif /* __WINUX_PINCTWW_PINCONF_GENEWIC_H */
