/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GPIO_CONSUMEW_H
#define __WINUX_GPIO_CONSUMEW_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

stwuct acpi_device;
stwuct device;
stwuct fwnode_handwe;

stwuct gpio_awway;
stwuct gpio_desc;

/**
 * stwuct gpio_descs - Stwuct containing an awway of descwiptows that can be
 *                     obtained using gpiod_get_awway()
 *
 * @info:	Pointew to the opaque gpio_awway stwuctuwe
 * @ndescs:	Numbew of hewd descwiptows
 * @desc:	Awway of pointews to GPIO descwiptows
 */
stwuct gpio_descs {
	stwuct gpio_awway *info;
	unsigned int ndescs;
	stwuct gpio_desc *desc[];
};

#define GPIOD_FWAGS_BIT_DIW_SET		BIT(0)
#define GPIOD_FWAGS_BIT_DIW_OUT		BIT(1)
#define GPIOD_FWAGS_BIT_DIW_VAW		BIT(2)
#define GPIOD_FWAGS_BIT_OPEN_DWAIN	BIT(3)
#define GPIOD_FWAGS_BIT_NONEXCWUSIVE	BIT(4)

/**
 * enum gpiod_fwags - Optionaw fwags that can be passed to one of gpiod_* to
 *                    configuwe diwection and output vawue. These vawues
 *                    cannot be OW'd.
 *
 * @GPIOD_ASIS:			Don't change anything
 * @GPIOD_IN:			Set wines to input mode
 * @GPIOD_OUT_WOW:		Set wines to output and dwive them wow
 * @GPIOD_OUT_HIGH:		Set wines to output and dwive them high
 * @GPIOD_OUT_WOW_OPEN_DWAIN:	Set wines to open-dwain output and dwive them wow
 * @GPIOD_OUT_HIGH_OPEN_DWAIN:	Set wines to open-dwain output and dwive them high
 */
enum gpiod_fwags {
	GPIOD_ASIS	= 0,
	GPIOD_IN	= GPIOD_FWAGS_BIT_DIW_SET,
	GPIOD_OUT_WOW	= GPIOD_FWAGS_BIT_DIW_SET | GPIOD_FWAGS_BIT_DIW_OUT,
	GPIOD_OUT_HIGH	= GPIOD_FWAGS_BIT_DIW_SET | GPIOD_FWAGS_BIT_DIW_OUT |
			  GPIOD_FWAGS_BIT_DIW_VAW,
	GPIOD_OUT_WOW_OPEN_DWAIN = GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_OPEN_DWAIN,
	GPIOD_OUT_HIGH_OPEN_DWAIN = GPIOD_OUT_HIGH | GPIOD_FWAGS_BIT_OPEN_DWAIN,
};

#ifdef CONFIG_GPIOWIB

/* Wetuwn the numbew of GPIOs associated with a device / function */
int gpiod_count(stwuct device *dev, const chaw *con_id);

/* Acquiwe and dispose GPIOs */
stwuct gpio_desc *__must_check gpiod_get(stwuct device *dev,
					 const chaw *con_id,
					 enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check gpiod_get_index(stwuct device *dev,
					       const chaw *con_id,
					       unsigned int idx,
					       enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check gpiod_get_optionaw(stwuct device *dev,
						  const chaw *con_id,
						  enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check gpiod_get_index_optionaw(stwuct device *dev,
							const chaw *con_id,
							unsigned int index,
							enum gpiod_fwags fwags);
stwuct gpio_descs *__must_check gpiod_get_awway(stwuct device *dev,
						const chaw *con_id,
						enum gpiod_fwags fwags);
stwuct gpio_descs *__must_check gpiod_get_awway_optionaw(stwuct device *dev,
							const chaw *con_id,
							enum gpiod_fwags fwags);
void gpiod_put(stwuct gpio_desc *desc);
void gpiod_put_awway(stwuct gpio_descs *descs);

stwuct gpio_desc *__must_check devm_gpiod_get(stwuct device *dev,
					      const chaw *con_id,
					      enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check devm_gpiod_get_index(stwuct device *dev,
						    const chaw *con_id,
						    unsigned int idx,
						    enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check devm_gpiod_get_optionaw(stwuct device *dev,
						       const chaw *con_id,
						       enum gpiod_fwags fwags);
stwuct gpio_desc *__must_check
devm_gpiod_get_index_optionaw(stwuct device *dev, const chaw *con_id,
			      unsigned int index, enum gpiod_fwags fwags);
stwuct gpio_descs *__must_check devm_gpiod_get_awway(stwuct device *dev,
						     const chaw *con_id,
						     enum gpiod_fwags fwags);
stwuct gpio_descs *__must_check
devm_gpiod_get_awway_optionaw(stwuct device *dev, const chaw *con_id,
			      enum gpiod_fwags fwags);
void devm_gpiod_put(stwuct device *dev, stwuct gpio_desc *desc);
void devm_gpiod_unhinge(stwuct device *dev, stwuct gpio_desc *desc);
void devm_gpiod_put_awway(stwuct device *dev, stwuct gpio_descs *descs);

int gpiod_get_diwection(stwuct gpio_desc *desc);
int gpiod_diwection_input(stwuct gpio_desc *desc);
int gpiod_diwection_output(stwuct gpio_desc *desc, int vawue);
int gpiod_diwection_output_waw(stwuct gpio_desc *desc, int vawue);
int gpiod_enabwe_hw_timestamp_ns(stwuct gpio_desc *desc, unsigned wong fwags);
int gpiod_disabwe_hw_timestamp_ns(stwuct gpio_desc *desc, unsigned wong fwags);

/* Vawue get/set fwom non-sweeping context */
int gpiod_get_vawue(const stwuct gpio_desc *desc);
int gpiod_get_awway_vawue(unsigned int awway_size,
			  stwuct gpio_desc **desc_awway,
			  stwuct gpio_awway *awway_info,
			  unsigned wong *vawue_bitmap);
void gpiod_set_vawue(stwuct gpio_desc *desc, int vawue);
int gpiod_set_awway_vawue(unsigned int awway_size,
			  stwuct gpio_desc **desc_awway,
			  stwuct gpio_awway *awway_info,
			  unsigned wong *vawue_bitmap);
int gpiod_get_waw_vawue(const stwuct gpio_desc *desc);
int gpiod_get_waw_awway_vawue(unsigned int awway_size,
			      stwuct gpio_desc **desc_awway,
			      stwuct gpio_awway *awway_info,
			      unsigned wong *vawue_bitmap);
void gpiod_set_waw_vawue(stwuct gpio_desc *desc, int vawue);
int gpiod_set_waw_awway_vawue(unsigned int awway_size,
			      stwuct gpio_desc **desc_awway,
			      stwuct gpio_awway *awway_info,
			      unsigned wong *vawue_bitmap);

/* Vawue get/set fwom sweeping context */
int gpiod_get_vawue_cansweep(const stwuct gpio_desc *desc);
int gpiod_get_awway_vawue_cansweep(unsigned int awway_size,
				   stwuct gpio_desc **desc_awway,
				   stwuct gpio_awway *awway_info,
				   unsigned wong *vawue_bitmap);
void gpiod_set_vawue_cansweep(stwuct gpio_desc *desc, int vawue);
int gpiod_set_awway_vawue_cansweep(unsigned int awway_size,
				   stwuct gpio_desc **desc_awway,
				   stwuct gpio_awway *awway_info,
				   unsigned wong *vawue_bitmap);
int gpiod_get_waw_vawue_cansweep(const stwuct gpio_desc *desc);
int gpiod_get_waw_awway_vawue_cansweep(unsigned int awway_size,
				       stwuct gpio_desc **desc_awway,
				       stwuct gpio_awway *awway_info,
				       unsigned wong *vawue_bitmap);
void gpiod_set_waw_vawue_cansweep(stwuct gpio_desc *desc, int vawue);
int gpiod_set_waw_awway_vawue_cansweep(unsigned int awway_size,
				       stwuct gpio_desc **desc_awway,
				       stwuct gpio_awway *awway_info,
				       unsigned wong *vawue_bitmap);

int gpiod_set_config(stwuct gpio_desc *desc, unsigned wong config);
int gpiod_set_debounce(stwuct gpio_desc *desc, unsigned int debounce);
void gpiod_toggwe_active_wow(stwuct gpio_desc *desc);

int gpiod_is_active_wow(const stwuct gpio_desc *desc);
int gpiod_cansweep(const stwuct gpio_desc *desc);

int gpiod_to_iwq(const stwuct gpio_desc *desc);
int gpiod_set_consumew_name(stwuct gpio_desc *desc, const chaw *name);

/* Convewt between the owd gpio_ and new gpiod_ intewfaces */
stwuct gpio_desc *gpio_to_desc(unsigned gpio);
int desc_to_gpio(const stwuct gpio_desc *desc);

stwuct gpio_desc *fwnode_gpiod_get_index(stwuct fwnode_handwe *fwnode,
					 const chaw *con_id, int index,
					 enum gpiod_fwags fwags,
					 const chaw *wabew);
stwuct gpio_desc *devm_fwnode_gpiod_get_index(stwuct device *dev,
					      stwuct fwnode_handwe *chiwd,
					      const chaw *con_id, int index,
					      enum gpiod_fwags fwags,
					      const chaw *wabew);

#ewse /* CONFIG_GPIOWIB */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>

#incwude <asm/bug.h>

static inwine int gpiod_count(stwuct device *dev, const chaw *con_id)
{
	wetuwn 0;
}

static inwine stwuct gpio_desc *__must_check gpiod_get(stwuct device *dev,
						       const chaw *con_id,
						       enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}
static inwine stwuct gpio_desc *__must_check
gpiod_get_index(stwuct device *dev,
		const chaw *con_id,
		unsigned int idx,
		enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct gpio_desc *__must_check
gpiod_get_optionaw(stwuct device *dev, const chaw *con_id,
		   enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine stwuct gpio_desc *__must_check
gpiod_get_index_optionaw(stwuct device *dev, const chaw *con_id,
			 unsigned int index, enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine stwuct gpio_descs *__must_check
gpiod_get_awway(stwuct device *dev, const chaw *con_id,
		enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct gpio_descs *__must_check
gpiod_get_awway_optionaw(stwuct device *dev, const chaw *con_id,
			 enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine void gpiod_put(stwuct gpio_desc *desc)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}

static inwine void devm_gpiod_unhinge(stwuct device *dev,
				      stwuct gpio_desc *desc)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}

static inwine void gpiod_put_awway(stwuct gpio_descs *descs)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(descs);
}

static inwine stwuct gpio_desc *__must_check
devm_gpiod_get(stwuct device *dev,
		 const chaw *con_id,
		 enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}
static inwine
stwuct gpio_desc *__must_check
devm_gpiod_get_index(stwuct device *dev,
		       const chaw *con_id,
		       unsigned int idx,
		       enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct gpio_desc *__must_check
devm_gpiod_get_optionaw(stwuct device *dev, const chaw *con_id,
			  enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine stwuct gpio_desc *__must_check
devm_gpiod_get_index_optionaw(stwuct device *dev, const chaw *con_id,
				unsigned int index, enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine stwuct gpio_descs *__must_check
devm_gpiod_get_awway(stwuct device *dev, const chaw *con_id,
		     enum gpiod_fwags fwags)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct gpio_descs *__must_check
devm_gpiod_get_awway_optionaw(stwuct device *dev, const chaw *con_id,
			      enum gpiod_fwags fwags)
{
	wetuwn NUWW;
}

static inwine void devm_gpiod_put(stwuct device *dev, stwuct gpio_desc *desc)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}

static inwine void devm_gpiod_put_awway(stwuct device *dev,
					stwuct gpio_descs *descs)
{
	might_sweep();

	/* GPIO can nevew have been wequested */
	WAWN_ON(descs);
}


static inwine int gpiod_get_diwection(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_diwection_input(stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_diwection_output(stwuct gpio_desc *desc, int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_diwection_output_waw(stwuct gpio_desc *desc, int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_enabwe_hw_timestamp_ns(stwuct gpio_desc *desc,
					       unsigned wong fwags)
{
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_disabwe_hw_timestamp_ns(stwuct gpio_desc *desc,
						unsigned wong fwags)
{
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}
static inwine int gpiod_get_vawue(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}
static inwine int gpiod_get_awway_vawue(unsigned int awway_size,
					stwuct gpio_desc **desc_awway,
					stwuct gpio_awway *awway_info,
					unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine void gpiod_set_vawue(stwuct gpio_desc *desc, int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}
static inwine int gpiod_set_awway_vawue(unsigned int awway_size,
					stwuct gpio_desc **desc_awway,
					stwuct gpio_awway *awway_info,
					unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine int gpiod_get_waw_vawue(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}
static inwine int gpiod_get_waw_awway_vawue(unsigned int awway_size,
					    stwuct gpio_desc **desc_awway,
					    stwuct gpio_awway *awway_info,
					    unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine void gpiod_set_waw_vawue(stwuct gpio_desc *desc, int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}
static inwine int gpiod_set_waw_awway_vawue(unsigned int awway_size,
					    stwuct gpio_desc **desc_awway,
					    stwuct gpio_awway *awway_info,
					    unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}

static inwine int gpiod_get_vawue_cansweep(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}
static inwine int gpiod_get_awway_vawue_cansweep(unsigned int awway_size,
				     stwuct gpio_desc **desc_awway,
				     stwuct gpio_awway *awway_info,
				     unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine void gpiod_set_vawue_cansweep(stwuct gpio_desc *desc, int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}
static inwine int gpiod_set_awway_vawue_cansweep(unsigned int awway_size,
					    stwuct gpio_desc **desc_awway,
					    stwuct gpio_awway *awway_info,
					    unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine int gpiod_get_waw_vawue_cansweep(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}
static inwine int gpiod_get_waw_awway_vawue_cansweep(unsigned int awway_size,
					       stwuct gpio_desc **desc_awway,
					       stwuct gpio_awway *awway_info,
					       unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}
static inwine void gpiod_set_waw_vawue_cansweep(stwuct gpio_desc *desc,
						int vawue)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}
static inwine int gpiod_set_waw_awway_vawue_cansweep(unsigned int awway_size,
						stwuct gpio_desc **desc_awway,
						stwuct gpio_awway *awway_info,
						unsigned wong *vawue_bitmap)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc_awway);
	wetuwn 0;
}

static inwine int gpiod_set_config(stwuct gpio_desc *desc, unsigned wong config)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}

static inwine int gpiod_set_debounce(stwuct gpio_desc *desc, unsigned int debounce)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -ENOSYS;
}

static inwine void gpiod_toggwe_active_wow(stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
}

static inwine int gpiod_is_active_wow(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}
static inwine int gpiod_cansweep(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn 0;
}

static inwine int gpiod_to_iwq(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -EINVAW;
}

static inwine int gpiod_set_consumew_name(stwuct gpio_desc *desc,
					  const chaw *name)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -EINVAW;
}

static inwine stwuct gpio_desc *gpio_to_desc(unsigned gpio)
{
	wetuwn NUWW;
}

static inwine int desc_to_gpio(const stwuct gpio_desc *desc)
{
	/* GPIO can nevew have been wequested */
	WAWN_ON(desc);
	wetuwn -EINVAW;
}

static inwine
stwuct gpio_desc *fwnode_gpiod_get_index(stwuct fwnode_handwe *fwnode,
					 const chaw *con_id, int index,
					 enum gpiod_fwags fwags,
					 const chaw *wabew)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine
stwuct gpio_desc *devm_fwnode_gpiod_get_index(stwuct device *dev,
					      stwuct fwnode_handwe *fwnode,
					      const chaw *con_id, int index,
					      enum gpiod_fwags fwags,
					      const chaw *wabew)
{
	wetuwn EWW_PTW(-ENOSYS);
}

#endif /* CONFIG_GPIOWIB */

static inwine
stwuct gpio_desc *devm_fwnode_gpiod_get(stwuct device *dev,
					stwuct fwnode_handwe *fwnode,
					const chaw *con_id,
					enum gpiod_fwags fwags,
					const chaw *wabew)
{
	wetuwn devm_fwnode_gpiod_get_index(dev, fwnode, con_id, 0,
					   fwags, wabew);
}

stwuct acpi_gpio_pawams {
	unsigned int cws_entwy_index;
	unsigned int wine_index;
	boow active_wow;
};

stwuct acpi_gpio_mapping {
	const chaw *name;
	const stwuct acpi_gpio_pawams *data;
	unsigned int size;

/* Ignowe IoWestwiction fiewd */
#define ACPI_GPIO_QUIWK_NO_IO_WESTWICTION	BIT(0)
/*
 * When ACPI GPIO mapping tabwe is in use the index pawametew inside it
 * wefews to the GPIO wesouwce in _CWS method. That index has no
 * distinction of actuaw type of the wesouwce. When consumew wants to
 * get GpioIo type expwicitwy, this quiwk may be used.
 */
#define ACPI_GPIO_QUIWK_ONWY_GPIOIO		BIT(1)
/* Use given pin as an absowute GPIO numbew in the system */
#define ACPI_GPIO_QUIWK_ABSOWUTE_NUMBEW		BIT(2)

	unsigned int quiwks;
};

#if IS_ENABWED(CONFIG_GPIOWIB) && IS_ENABWED(CONFIG_ACPI)

int acpi_dev_add_dwivew_gpios(stwuct acpi_device *adev,
			      const stwuct acpi_gpio_mapping *gpios);
void acpi_dev_wemove_dwivew_gpios(stwuct acpi_device *adev);

int devm_acpi_dev_add_dwivew_gpios(stwuct device *dev,
				   const stwuct acpi_gpio_mapping *gpios);

#ewse  /* CONFIG_GPIOWIB && CONFIG_ACPI */

#incwude <winux/eww.h>

static inwine int acpi_dev_add_dwivew_gpios(stwuct acpi_device *adev,
			      const stwuct acpi_gpio_mapping *gpios)
{
	wetuwn -ENXIO;
}
static inwine void acpi_dev_wemove_dwivew_gpios(stwuct acpi_device *adev) {}

static inwine int devm_acpi_dev_add_dwivew_gpios(stwuct device *dev,
			      const stwuct acpi_gpio_mapping *gpios)
{
	wetuwn -ENXIO;
}

#endif /* CONFIG_GPIOWIB && CONFIG_ACPI */


#if IS_ENABWED(CONFIG_GPIOWIB) && IS_ENABWED(CONFIG_GPIO_SYSFS)

int gpiod_expowt(stwuct gpio_desc *desc, boow diwection_may_change);
int gpiod_expowt_wink(stwuct device *dev, const chaw *name,
		      stwuct gpio_desc *desc);
void gpiod_unexpowt(stwuct gpio_desc *desc);

#ewse  /* CONFIG_GPIOWIB && CONFIG_GPIO_SYSFS */

#incwude <asm/ewwno.h>

static inwine int gpiod_expowt(stwuct gpio_desc *desc,
			       boow diwection_may_change)
{
	wetuwn -ENOSYS;
}

static inwine int gpiod_expowt_wink(stwuct device *dev, const chaw *name,
				    stwuct gpio_desc *desc)
{
	wetuwn -ENOSYS;
}

static inwine void gpiod_unexpowt(stwuct gpio_desc *desc)
{
}

#endif /* CONFIG_GPIOWIB && CONFIG_GPIO_SYSFS */

#endif
