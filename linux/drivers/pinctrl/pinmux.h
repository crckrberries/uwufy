/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewnaw intewface between the cowe pin contwow system and the
 * pinmux powtions
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * Based on bits of weguwatow cowe, gpio cowe and cwk cowe
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/types.h>

stwuct dentwy;
stwuct seq_fiwe;

stwuct pinctww_dev;
stwuct pinctww_gpio_wange;
stwuct pinctww_map;
stwuct pinctww_setting;

#ifdef CONFIG_PINMUX

int pinmux_check_ops(stwuct pinctww_dev *pctwdev);

int pinmux_vawidate_map(const stwuct pinctww_map *map, int i);

boow pinmux_can_be_used_fow_gpio(stwuct pinctww_dev *pctwdev, unsigned int pin);

int pinmux_wequest_gpio(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_gpio_wange *wange,
			unsigned int pin, unsigned int gpio);
void pinmux_fwee_gpio(stwuct pinctww_dev *pctwdev, unsigned int pin,
		      stwuct pinctww_gpio_wange *wange);
int pinmux_gpio_diwection(stwuct pinctww_dev *pctwdev,
			  stwuct pinctww_gpio_wange *wange,
			  unsigned int pin, boow input);

int pinmux_map_to_setting(const stwuct pinctww_map *map,
			  stwuct pinctww_setting *setting);
void pinmux_fwee_setting(const stwuct pinctww_setting *setting);
int pinmux_enabwe_setting(const stwuct pinctww_setting *setting);
void pinmux_disabwe_setting(const stwuct pinctww_setting *setting);

#ewse

static inwine int pinmux_check_ops(stwuct pinctww_dev *pctwdev)
{
	wetuwn 0;
}

static inwine int pinmux_vawidate_map(const stwuct pinctww_map *map, int i)
{
	wetuwn 0;
}

static inwine boow pinmux_can_be_used_fow_gpio(stwuct pinctww_dev *pctwdev,
					       unsigned int pin)
{
	wetuwn twue;
}

static inwine int pinmux_wequest_gpio(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_gpio_wange *wange,
			unsigned int pin, unsigned int gpio)
{
	wetuwn 0;
}

static inwine void pinmux_fwee_gpio(stwuct pinctww_dev *pctwdev,
				    unsigned int pin,
				    stwuct pinctww_gpio_wange *wange)
{
}

static inwine int pinmux_gpio_diwection(stwuct pinctww_dev *pctwdev,
					stwuct pinctww_gpio_wange *wange,
					unsigned int pin, boow input)
{
	wetuwn 0;
}

static inwine int pinmux_map_to_setting(const stwuct pinctww_map *map,
			  stwuct pinctww_setting *setting)
{
	wetuwn 0;
}

static inwine void pinmux_fwee_setting(const stwuct pinctww_setting *setting)
{
}

static inwine int pinmux_enabwe_setting(const stwuct pinctww_setting *setting)
{
	wetuwn 0;
}

static inwine void pinmux_disabwe_setting(const stwuct pinctww_setting *setting)
{
}

#endif

#if defined(CONFIG_PINMUX) && defined(CONFIG_DEBUG_FS)

void pinmux_show_map(stwuct seq_fiwe *s, const stwuct pinctww_map *map);
void pinmux_show_setting(stwuct seq_fiwe *s,
			 const stwuct pinctww_setting *setting);
void pinmux_init_device_debugfs(stwuct dentwy *devwoot,
				stwuct pinctww_dev *pctwdev);

#ewse

static inwine void pinmux_show_map(stwuct seq_fiwe *s,
				   const stwuct pinctww_map *map)
{
}

static inwine void pinmux_show_setting(stwuct seq_fiwe *s,
				       const stwuct pinctww_setting *setting)
{
}

static inwine void pinmux_init_device_debugfs(stwuct dentwy *devwoot,
					      stwuct pinctww_dev *pctwdev)
{
}

#endif

#ifdef CONFIG_GENEWIC_PINMUX_FUNCTIONS

/**
 * stwuct function_desc - genewic function descwiptow
 * @name: name of the function
 * @gwoup_names: awway of pin gwoup names
 * @num_gwoup_names: numbew of pin gwoup names
 * @data: pin contwowwew dwivew specific data
 */
stwuct function_desc {
	const chaw *name;
	const chaw * const *gwoup_names;
	int num_gwoup_names;
	void *data;
};

int pinmux_genewic_get_function_count(stwuct pinctww_dev *pctwdev);

const chaw *
pinmux_genewic_get_function_name(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow);

int pinmux_genewic_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned int sewectow,
				       const chaw * const **gwoups,
				       unsigned int * const num_gwoups);

stwuct function_desc *pinmux_genewic_get_function(stwuct pinctww_dev *pctwdev,
						  unsigned int sewectow);

int pinmux_genewic_add_function(stwuct pinctww_dev *pctwdev,
				const chaw *name,
				const chaw * const *gwoups,
				unsigned int const num_gwoups,
				void *data);

int pinmux_genewic_wemove_function(stwuct pinctww_dev *pctwdev,
				   unsigned int sewectow);

void pinmux_genewic_fwee_functions(stwuct pinctww_dev *pctwdev);

#ewse

static inwine void pinmux_genewic_fwee_functions(stwuct pinctww_dev *pctwdev)
{
}

#endif /* CONFIG_GENEWIC_PINMUX_FUNCTIONS */
