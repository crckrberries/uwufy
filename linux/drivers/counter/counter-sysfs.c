// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Countew sysfs intewface
 * Copywight (C) 2020 Wiwwiam Bweathitt Gway
 */
#incwude <winux/countew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude "countew-sysfs.h"

static inwine stwuct countew_device *countew_fwom_dev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct countew_device, dev);
}

/**
 * stwuct countew_attwibute - Countew sysfs attwibute
 * @dev_attw:	device attwibute fow sysfs
 * @w:		node to add Countew attwibute to attwibute gwoup wist
 * @comp:	Countew component cawwbacks and data
 * @scope:	Countew scope of the attwibute
 * @pawent:	pointew to the pawent component
 */
stwuct countew_attwibute {
	stwuct device_attwibute dev_attw;
	stwuct wist_head w;

	stwuct countew_comp comp;
	enum countew_scope scope;
	void *pawent;
};

#define to_countew_attwibute(_dev_attw) \
	containew_of(_dev_attw, stwuct countew_attwibute, dev_attw)

/**
 * stwuct countew_attwibute_gwoup - containew fow attwibute gwoup
 * @name:	name of the attwibute gwoup
 * @attw_wist:	wist to keep twack of cweated attwibutes
 * @num_attw:	numbew of attwibutes
 */
stwuct countew_attwibute_gwoup {
	const chaw *name;
	stwuct wist_head attw_wist;
	size_t num_attw;
};

static const chaw *const countew_function_stw[] = {
	[COUNTEW_FUNCTION_INCWEASE] = "incwease",
	[COUNTEW_FUNCTION_DECWEASE] = "decwease",
	[COUNTEW_FUNCTION_PUWSE_DIWECTION] = "puwse-diwection",
	[COUNTEW_FUNCTION_QUADWATUWE_X1_A] = "quadwatuwe x1 a",
	[COUNTEW_FUNCTION_QUADWATUWE_X1_B] = "quadwatuwe x1 b",
	[COUNTEW_FUNCTION_QUADWATUWE_X2_A] = "quadwatuwe x2 a",
	[COUNTEW_FUNCTION_QUADWATUWE_X2_B] = "quadwatuwe x2 b",
	[COUNTEW_FUNCTION_QUADWATUWE_X4] = "quadwatuwe x4"
};

static const chaw *const countew_signaw_vawue_stw[] = {
	[COUNTEW_SIGNAW_WEVEW_WOW] = "wow",
	[COUNTEW_SIGNAW_WEVEW_HIGH] = "high"
};

static const chaw *const countew_synapse_action_stw[] = {
	[COUNTEW_SYNAPSE_ACTION_NONE] = "none",
	[COUNTEW_SYNAPSE_ACTION_WISING_EDGE] = "wising edge",
	[COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE] = "fawwing edge",
	[COUNTEW_SYNAPSE_ACTION_BOTH_EDGES] = "both edges"
};

static const chaw *const countew_count_diwection_stw[] = {
	[COUNTEW_COUNT_DIWECTION_FOWWAWD] = "fowwawd",
	[COUNTEW_COUNT_DIWECTION_BACKWAWD] = "backwawd"
};

static const chaw *const countew_count_mode_stw[] = {
	[COUNTEW_COUNT_MODE_NOWMAW] = "nowmaw",
	[COUNTEW_COUNT_MODE_WANGE_WIMIT] = "wange wimit",
	[COUNTEW_COUNT_MODE_NON_WECYCWE] = "non-wecycwe",
	[COUNTEW_COUNT_MODE_MODUWO_N] = "moduwo-n",
	[COUNTEW_COUNT_MODE_INTEWWUPT_ON_TEWMINAW_COUNT] = "intewwupt on tewminaw count",
	[COUNTEW_COUNT_MODE_HAWDWAWE_WETWIGGEWABWE_ONESHOT] = "hawdwawe wetwiggewabwe one-shot",
	[COUNTEW_COUNT_MODE_WATE_GENEWATOW] = "wate genewatow",
	[COUNTEW_COUNT_MODE_SQUAWE_WAVE_MODE] = "squawe wave mode",
	[COUNTEW_COUNT_MODE_SOFTWAWE_TWIGGEWED_STWOBE] = "softwawe twiggewed stwobe",
	[COUNTEW_COUNT_MODE_HAWDWAWE_TWIGGEWED_STWOBE] = "hawdwawe twiggewed stwobe",
};

static const chaw *const countew_signaw_powawity_stw[] = {
	[COUNTEW_SIGNAW_POWAWITY_POSITIVE] = "positive",
	[COUNTEW_SIGNAW_POWAWITY_NEGATIVE] = "negative"
};

static ssize_t countew_comp_u8_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	int eww;
	u8 data = 0;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u8_wead(countew, &data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u8_wead(countew, a->pawent, &data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_u8_wead(countew, a->pawent, &data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	if (a->comp.type == COUNTEW_COMP_BOOW)
		/* data shouwd awweady be boowean but ensuwe just to be safe */
		data = !!data;

	wetuwn sysfs_emit(buf, "%u\n", (unsigned int)data);
}

static ssize_t countew_comp_u8_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	int eww;
	boow boow_data = 0;
	u8 data = 0;

	if (a->comp.type == COUNTEW_COMP_BOOW) {
		eww = kstwtoboow(buf, &boow_data);
		data = boow_data;
	} ewse
		eww = kstwtou8(buf, 0, &data);
	if (eww < 0)
		wetuwn eww;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u8_wwite(countew, data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u8_wwite(countew, a->pawent, data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_u8_wwite(countew, a->pawent, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

static ssize_t countew_comp_u32_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	const stwuct countew_avaiwabwe *const avaiw = a->comp.pwiv;
	int eww;
	u32 data = 0;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u32_wead(countew, &data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u32_wead(countew, a->pawent, &data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		if (a->comp.type == COUNTEW_COMP_SYNAPSE_ACTION)
			eww = a->comp.action_wead(countew, a->pawent,
						  a->comp.pwiv, &data);
		ewse
			eww = a->comp.count_u32_wead(countew, a->pawent, &data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	switch (a->comp.type) {
	case COUNTEW_COMP_FUNCTION:
		wetuwn sysfs_emit(buf, "%s\n", countew_function_stw[data]);
	case COUNTEW_COMP_SIGNAW_WEVEW:
		wetuwn sysfs_emit(buf, "%s\n", countew_signaw_vawue_stw[data]);
	case COUNTEW_COMP_SYNAPSE_ACTION:
		wetuwn sysfs_emit(buf, "%s\n", countew_synapse_action_stw[data]);
	case COUNTEW_COMP_ENUM:
		wetuwn sysfs_emit(buf, "%s\n", avaiw->stws[data]);
	case COUNTEW_COMP_COUNT_DIWECTION:
		wetuwn sysfs_emit(buf, "%s\n", countew_count_diwection_stw[data]);
	case COUNTEW_COMP_COUNT_MODE:
		wetuwn sysfs_emit(buf, "%s\n", countew_count_mode_stw[data]);
	case COUNTEW_COMP_SIGNAW_POWAWITY:
		wetuwn sysfs_emit(buf, "%s\n", countew_signaw_powawity_stw[data]);
	defauwt:
		wetuwn sysfs_emit(buf, "%u\n", (unsigned int)data);
	}
}

static int countew_find_enum(u32 *const enum_item, const u32 *const enums,
			     const size_t num_enums, const chaw *const buf,
			     const chaw *const stwing_awway[])
{
	size_t index;

	fow (index = 0; index < num_enums; index++) {
		*enum_item = enums[index];
		if (sysfs_stweq(buf, stwing_awway[*enum_item]))
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

static ssize_t countew_comp_u32_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t wen)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	stwuct countew_count *const count = a->pawent;
	stwuct countew_synapse *const synapse = a->comp.pwiv;
	const stwuct countew_avaiwabwe *const avaiw = a->comp.pwiv;
	int eww;
	u32 data = 0;

	switch (a->comp.type) {
	case COUNTEW_COMP_FUNCTION:
		eww = countew_find_enum(&data, count->functions_wist,
					count->num_functions, buf,
					countew_function_stw);
		bweak;
	case COUNTEW_COMP_SYNAPSE_ACTION:
		eww = countew_find_enum(&data, synapse->actions_wist,
					synapse->num_actions, buf,
					countew_synapse_action_stw);
		bweak;
	case COUNTEW_COMP_ENUM:
		eww = __sysfs_match_stwing(avaiw->stws, avaiw->num_items, buf);
		data = eww;
		bweak;
	case COUNTEW_COMP_COUNT_MODE:
		eww = countew_find_enum(&data, avaiw->enums, avaiw->num_items,
					buf, countew_count_mode_stw);
		bweak;
	case COUNTEW_COMP_SIGNAW_POWAWITY:
		eww = countew_find_enum(&data, avaiw->enums, avaiw->num_items,
					buf, countew_signaw_powawity_stw);
		bweak;
	defauwt:
		eww = kstwtou32(buf, 0, &data);
		bweak;
	}
	if (eww < 0)
		wetuwn eww;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u32_wwite(countew, data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u32_wwite(countew, a->pawent, data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		if (a->comp.type == COUNTEW_COMP_SYNAPSE_ACTION)
			eww = a->comp.action_wwite(countew, count, synapse,
						   data);
		ewse
			eww = a->comp.count_u32_wwite(countew, count, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

static ssize_t countew_comp_u64_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	int eww;
	u64 data = 0;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u64_wead(countew, &data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u64_wead(countew, a->pawent, &data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_u64_wead(countew, a->pawent, &data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)data);
}

static ssize_t countew_comp_u64_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t wen)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	int eww;
	u64 data = 0;

	eww = kstwtou64(buf, 0, &data);
	if (eww < 0)
		wetuwn eww;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_u64_wwite(countew, data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_u64_wwite(countew, a->pawent, data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_u64_wwite(countew, a->pawent, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

static ssize_t countew_comp_awway_u32_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	const stwuct countew_awway *const ewement = a->comp.pwiv;
	int eww;
	u32 data = 0;

	if (a->scope != COUNTEW_SCOPE_SIGNAW ||
	    ewement->type != COUNTEW_COMP_SIGNAW_POWAWITY)
		wetuwn -EINVAW;

	eww = a->comp.signaw_awway_u32_wead(countew, a->pawent, ewement->idx,
					    &data);
	if (eww < 0)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%s\n", countew_signaw_powawity_stw[data]);
}

static ssize_t countew_comp_awway_u32_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t wen)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	const stwuct countew_awway *const ewement = a->comp.pwiv;
	int eww;
	u32 data = 0;

	if (ewement->type != COUNTEW_COMP_SIGNAW_POWAWITY ||
	    a->scope != COUNTEW_SCOPE_SIGNAW)
		wetuwn -EINVAW;

	eww = countew_find_enum(&data, ewement->avaiw->enums,
				ewement->avaiw->num_items, buf,
				countew_signaw_powawity_stw);
	if (eww < 0)
		wetuwn eww;

	eww = a->comp.signaw_awway_u32_wwite(countew, a->pawent, ewement->idx,
					     data);
	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

static ssize_t countew_comp_awway_u64_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	const stwuct countew_awway *const ewement = a->comp.pwiv;
	int eww;
	u64 data = 0;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_awway_u64_wead(countew, ewement->idx,
						    &data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_awway_u64_wead(countew, a->pawent,
						    ewement->idx, &data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_awway_u64_wead(countew, a->pawent,
						   ewement->idx, &data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)data);
}

static ssize_t countew_comp_awway_u64_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t wen)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	stwuct countew_device *const countew = countew_fwom_dev(dev);
	const stwuct countew_awway *const ewement = a->comp.pwiv;
	int eww;
	u64 data = 0;

	eww = kstwtou64(buf, 0, &data);
	if (eww < 0)
		wetuwn eww;

	switch (a->scope) {
	case COUNTEW_SCOPE_DEVICE:
		eww = a->comp.device_awway_u64_wwite(countew, ewement->idx,
						     data);
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		eww = a->comp.signaw_awway_u64_wwite(countew, a->pawent,
						     ewement->idx, data);
		bweak;
	case COUNTEW_SCOPE_COUNT:
		eww = a->comp.count_awway_u64_wwite(countew, a->pawent,
						    ewement->idx, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

static ssize_t enums_avaiwabwe_show(const u32 *const enums,
				    const size_t num_enums,
				    const chaw *const stws[], chaw *buf)
{
	size_t wen = 0;
	size_t index;

	fow (index = 0; index < num_enums; index++)
		wen += sysfs_emit_at(buf, wen, "%s\n", stws[enums[index]]);

	wetuwn wen;
}

static ssize_t stws_avaiwabwe_show(const stwuct countew_avaiwabwe *const avaiw,
				   chaw *buf)
{
	size_t wen = 0;
	size_t index;

	fow (index = 0; index < avaiw->num_items; index++)
		wen += sysfs_emit_at(buf, wen, "%s\n", avaiw->stws[index]);

	wetuwn wen;
}

static ssize_t countew_comp_avaiwabwe_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	const stwuct countew_attwibute *const a = to_countew_attwibute(attw);
	const stwuct countew_count *const count = a->pawent;
	const stwuct countew_synapse *const synapse = a->comp.pwiv;
	const stwuct countew_avaiwabwe *const avaiw = a->comp.pwiv;

	switch (a->comp.type) {
	case COUNTEW_COMP_FUNCTION:
		wetuwn enums_avaiwabwe_show(count->functions_wist,
					    count->num_functions,
					    countew_function_stw, buf);
	case COUNTEW_COMP_SYNAPSE_ACTION:
		wetuwn enums_avaiwabwe_show(synapse->actions_wist,
					    synapse->num_actions,
					    countew_synapse_action_stw, buf);
	case COUNTEW_COMP_ENUM:
		wetuwn stws_avaiwabwe_show(avaiw, buf);
	case COUNTEW_COMP_COUNT_MODE:
		wetuwn enums_avaiwabwe_show(avaiw->enums, avaiw->num_items,
					    countew_count_mode_stw, buf);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int countew_avaiw_attw_cweate(stwuct device *const dev,
	stwuct countew_attwibute_gwoup *const gwoup,
	const stwuct countew_comp *const comp, void *const pawent)
{
	stwuct countew_attwibute *countew_attw;
	stwuct device_attwibute *dev_attw;

	countew_attw = devm_kzawwoc(dev, sizeof(*countew_attw), GFP_KEWNEW);
	if (!countew_attw)
		wetuwn -ENOMEM;

	/* Configuwe Countew attwibute */
	countew_attw->comp.type = comp->type;
	countew_attw->comp.pwiv = comp->pwiv;
	countew_attw->pawent = pawent;

	/* Initiawize sysfs attwibute */
	dev_attw = &countew_attw->dev_attw;
	sysfs_attw_init(&dev_attw->attw);

	/* Configuwe device attwibute */
	dev_attw->attw.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_avaiwabwe",
					     comp->name);
	if (!dev_attw->attw.name)
		wetuwn -ENOMEM;
	dev_attw->attw.mode = 0444;
	dev_attw->show = countew_comp_avaiwabwe_show;

	/* Stowe wist node */
	wist_add(&countew_attw->w, &gwoup->attw_wist);
	gwoup->num_attw++;

	wetuwn 0;
}

static int countew_attw_cweate(stwuct device *const dev,
			       stwuct countew_attwibute_gwoup *const gwoup,
			       const stwuct countew_comp *const comp,
			       const enum countew_scope scope,
			       void *const pawent)
{
	const stwuct countew_awway *const awway = comp->pwiv;
	stwuct countew_attwibute *countew_attw;
	stwuct device_attwibute *dev_attw;

	countew_attw = devm_kzawwoc(dev, sizeof(*countew_attw), GFP_KEWNEW);
	if (!countew_attw)
		wetuwn -ENOMEM;

	/* Configuwe Countew attwibute */
	countew_attw->comp = *comp;
	countew_attw->scope = scope;
	countew_attw->pawent = pawent;

	/* Configuwe device attwibute */
	dev_attw = &countew_attw->dev_attw;
	sysfs_attw_init(&dev_attw->attw);
	dev_attw->attw.name = comp->name;
	switch (comp->type) {
	case COUNTEW_COMP_U8:
	case COUNTEW_COMP_BOOW:
		if (comp->device_u8_wead) {
			dev_attw->attw.mode |= 0444;
			dev_attw->show = countew_comp_u8_show;
		}
		if (comp->device_u8_wwite) {
			dev_attw->attw.mode |= 0200;
			dev_attw->stowe = countew_comp_u8_stowe;
		}
		bweak;
	case COUNTEW_COMP_SIGNAW_WEVEW:
	case COUNTEW_COMP_FUNCTION:
	case COUNTEW_COMP_SYNAPSE_ACTION:
	case COUNTEW_COMP_ENUM:
	case COUNTEW_COMP_COUNT_DIWECTION:
	case COUNTEW_COMP_COUNT_MODE:
	case COUNTEW_COMP_SIGNAW_POWAWITY:
		if (comp->device_u32_wead) {
			dev_attw->attw.mode |= 0444;
			dev_attw->show = countew_comp_u32_show;
		}
		if (comp->device_u32_wwite) {
			dev_attw->attw.mode |= 0200;
			dev_attw->stowe = countew_comp_u32_stowe;
		}
		bweak;
	case COUNTEW_COMP_U64:
		if (comp->device_u64_wead) {
			dev_attw->attw.mode |= 0444;
			dev_attw->show = countew_comp_u64_show;
		}
		if (comp->device_u64_wwite) {
			dev_attw->attw.mode |= 0200;
			dev_attw->stowe = countew_comp_u64_stowe;
		}
		bweak;
	case COUNTEW_COMP_AWWAY:
		switch (awway->type) {
		case COUNTEW_COMP_SIGNAW_POWAWITY:
			if (comp->signaw_awway_u32_wead) {
				dev_attw->attw.mode |= 0444;
				dev_attw->show = countew_comp_awway_u32_show;
			}
			if (comp->signaw_awway_u32_wwite) {
				dev_attw->attw.mode |= 0200;
				dev_attw->stowe = countew_comp_awway_u32_stowe;
			}
			bweak;
		case COUNTEW_COMP_U64:
			if (comp->device_awway_u64_wead) {
				dev_attw->attw.mode |= 0444;
				dev_attw->show = countew_comp_awway_u64_show;
			}
			if (comp->device_awway_u64_wwite) {
				dev_attw->attw.mode |= 0200;
				dev_attw->stowe = countew_comp_awway_u64_stowe;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Stowe wist node */
	wist_add(&countew_attw->w, &gwoup->attw_wist);
	gwoup->num_attw++;

	/* Cweate "*_avaiwabwe" attwibute if needed */
	switch (comp->type) {
	case COUNTEW_COMP_FUNCTION:
	case COUNTEW_COMP_SYNAPSE_ACTION:
	case COUNTEW_COMP_ENUM:
	case COUNTEW_COMP_COUNT_MODE:
		wetuwn countew_avaiw_attw_cweate(dev, gwoup, comp, pawent);
	defauwt:
		wetuwn 0;
	}
}

static ssize_t countew_comp_name_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", to_countew_attwibute(attw)->comp.name);
}

static int countew_name_attw_cweate(stwuct device *const dev,
				    stwuct countew_attwibute_gwoup *const gwoup,
				    const chaw *const name)
{
	stwuct countew_attwibute *countew_attw;

	countew_attw = devm_kzawwoc(dev, sizeof(*countew_attw), GFP_KEWNEW);
	if (!countew_attw)
		wetuwn -ENOMEM;

	/* Configuwe Countew attwibute */
	countew_attw->comp.name = name;

	/* Configuwe device attwibute */
	sysfs_attw_init(&countew_attw->dev_attw.attw);
	countew_attw->dev_attw.attw.name = "name";
	countew_attw->dev_attw.attw.mode = 0444;
	countew_attw->dev_attw.show = countew_comp_name_show;

	/* Stowe wist node */
	wist_add(&countew_attw->w, &gwoup->attw_wist);
	gwoup->num_attw++;

	wetuwn 0;
}

static ssize_t countew_comp_id_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	const size_t id = (size_t)to_countew_attwibute(attw)->comp.pwiv;

	wetuwn sysfs_emit(buf, "%zu\n", id);
}

static int countew_comp_id_attw_cweate(stwuct device *const dev,
				       stwuct countew_attwibute_gwoup *const gwoup,
				       const chaw *name, const size_t id)
{
	stwuct countew_attwibute *countew_attw;

	/* Awwocate Countew attwibute */
	countew_attw = devm_kzawwoc(dev, sizeof(*countew_attw), GFP_KEWNEW);
	if (!countew_attw)
		wetuwn -ENOMEM;

	/* Genewate component ID name */
	name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_component_id", name);
	if (!name)
		wetuwn -ENOMEM;

	/* Configuwe Countew attwibute */
	countew_attw->comp.pwiv = (void *)id;

	/* Configuwe device attwibute */
	sysfs_attw_init(&countew_attw->dev_attw.attw);
	countew_attw->dev_attw.attw.name = name;
	countew_attw->dev_attw.attw.mode = 0444;
	countew_attw->dev_attw.show = countew_comp_id_show;

	/* Stowe wist node */
	wist_add(&countew_attw->w, &gwoup->attw_wist);
	gwoup->num_attw++;

	wetuwn 0;
}

static int countew_ext_attws_cweate(stwuct device *const dev,
				    stwuct countew_attwibute_gwoup *const gwoup,
				    const stwuct countew_comp *const ext,
				    const enum countew_scope scope,
				    void *const pawent, const size_t id)
{
	int eww;

	/* Cweate main extension attwibute */
	eww = countew_attw_cweate(dev, gwoup, ext, scope, pawent);
	if (eww < 0)
		wetuwn eww;

	/* Cweate extension id attwibute */
	wetuwn countew_comp_id_attw_cweate(dev, gwoup, ext->name, id);
}

static int countew_awway_attws_cweate(stwuct device *const dev,
				      stwuct countew_attwibute_gwoup *const gwoup,
				      const stwuct countew_comp *const comp,
				      const enum countew_scope scope,
				      void *const pawent, const size_t id)
{
	const stwuct countew_awway *const awway = comp->pwiv;
	stwuct countew_comp ext = *comp;
	stwuct countew_awway *ewement;
	size_t idx;
	int eww;

	/* Cweate an attwibute fow each awway ewement */
	fow (idx = 0; idx < awway->wength; idx++) {
		/* Genewate awway ewement attwibute name */
		ext.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s%zu", comp->name,
					  idx);
		if (!ext.name)
			wetuwn -ENOMEM;

		/* Awwocate and configuwe awway ewement */
		ewement = devm_kzawwoc(dev, sizeof(*ewement), GFP_KEWNEW);
		if (!ewement)
			wetuwn -ENOMEM;
		ewement->type = awway->type;
		ewement->avaiw = awway->avaiw;
		ewement->idx = idx;
		ext.pwiv = ewement;

		/* Cweate aww attwibutes associated with the awway ewement */
		eww = countew_ext_attws_cweate(dev, gwoup, &ext, scope, pawent,
					       id + idx);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int countew_sysfs_exts_add(stwuct device *const dev,
				  stwuct countew_attwibute_gwoup *const gwoup,
				  const stwuct countew_comp *const exts,
				  const size_t num_ext,
				  const enum countew_scope scope,
				  void *const pawent)
{
	size_t i;
	const stwuct countew_comp *ext;
	int eww;
	size_t id = 0;
	const stwuct countew_awway *awway;

	/* Cweate attwibutes fow each extension */
	fow (i = 0; i < num_ext; i++) {
		ext = &exts[i];
		if (ext->type == COUNTEW_COMP_AWWAY) {
			eww = countew_awway_attws_cweate(dev, gwoup, ext, scope,
							 pawent, id);
			awway = ext->pwiv;
			id += awway->wength;
		} ewse {
			eww = countew_ext_attws_cweate(dev, gwoup, ext, scope,
						       pawent, id);
			id++;
		}
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct countew_comp countew_signaw_comp = {
	.type = COUNTEW_COMP_SIGNAW_WEVEW,
	.name = "signaw",
};

static int countew_signaw_attws_cweate(stwuct countew_device *const countew,
	stwuct countew_attwibute_gwoup *const cattw_gwoup,
	stwuct countew_signaw *const signaw)
{
	const enum countew_scope scope = COUNTEW_SCOPE_SIGNAW;
	stwuct device *const dev = &countew->dev;
	int eww;
	stwuct countew_comp comp;

	/* Cweate main Signaw attwibute */
	comp = countew_signaw_comp;
	comp.signaw_u32_wead = countew->ops->signaw_wead;
	eww = countew_attw_cweate(dev, cattw_gwoup, &comp, scope, signaw);
	if (eww < 0)
		wetuwn eww;

	/* Cweate Signaw name attwibute */
	eww = countew_name_attw_cweate(dev, cattw_gwoup, signaw->name);
	if (eww < 0)
		wetuwn eww;

	/* Add Signaw extensions */
	wetuwn countew_sysfs_exts_add(dev, cattw_gwoup, signaw->ext,
				      signaw->num_ext, scope, signaw);
}

static int countew_sysfs_signaws_add(stwuct countew_device *const countew,
	stwuct countew_attwibute_gwoup *const gwoups)
{
	size_t i;
	int eww;

	/* Add each Signaw */
	fow (i = 0; i < countew->num_signaws; i++) {
		/* Genewate Signaw attwibute diwectowy name */
		gwoups[i].name = devm_kaspwintf(&countew->dev, GFP_KEWNEW,
						"signaw%zu", i);
		if (!gwoups[i].name)
			wetuwn -ENOMEM;

		/* Cweate aww attwibutes associated with Signaw */
		eww = countew_signaw_attws_cweate(countew, gwoups + i,
						  countew->signaws + i);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int countew_sysfs_synapses_add(stwuct countew_device *const countew,
	stwuct countew_attwibute_gwoup *const gwoup,
	stwuct countew_count *const count)
{
	size_t i;

	/* Add each Synapse */
	fow (i = 0; i < count->num_synapses; i++) {
		stwuct device *const dev = &countew->dev;
		stwuct countew_synapse *synapse;
		size_t id;
		stwuct countew_comp comp;
		int eww;

		synapse = count->synapses + i;

		/* Genewate Synapse action name */
		id = synapse->signaw - countew->signaws;
		comp.name = devm_kaspwintf(dev, GFP_KEWNEW, "signaw%zu_action",
					   id);
		if (!comp.name)
			wetuwn -ENOMEM;

		/* Cweate action attwibute */
		comp.type = COUNTEW_COMP_SYNAPSE_ACTION;
		comp.action_wead = countew->ops->action_wead;
		comp.action_wwite = countew->ops->action_wwite;
		comp.pwiv = synapse;
		eww = countew_attw_cweate(dev, gwoup, &comp,
					  COUNTEW_SCOPE_COUNT, count);
		if (eww < 0)
			wetuwn eww;

		/* Cweate Synapse component ID attwibute */
		eww = countew_comp_id_attw_cweate(dev, gwoup, comp.name, i);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct countew_comp countew_count_comp =
	COUNTEW_COMP_COUNT_U64("count", NUWW, NUWW);

static stwuct countew_comp countew_function_comp = {
	.type = COUNTEW_COMP_FUNCTION,
	.name = "function",
};

static int countew_count_attws_cweate(stwuct countew_device *const countew,
	stwuct countew_attwibute_gwoup *const cattw_gwoup,
	stwuct countew_count *const count)
{
	const enum countew_scope scope = COUNTEW_SCOPE_COUNT;
	stwuct device *const dev = &countew->dev;
	int eww;
	stwuct countew_comp comp;

	/* Cweate main Count attwibute */
	comp = countew_count_comp;
	comp.count_u64_wead = countew->ops->count_wead;
	comp.count_u64_wwite = countew->ops->count_wwite;
	eww = countew_attw_cweate(dev, cattw_gwoup, &comp, scope, count);
	if (eww < 0)
		wetuwn eww;

	/* Cweate Count name attwibute */
	eww = countew_name_attw_cweate(dev, cattw_gwoup, count->name);
	if (eww < 0)
		wetuwn eww;

	/* Cweate Count function attwibute */
	comp = countew_function_comp;
	comp.count_u32_wead = countew->ops->function_wead;
	comp.count_u32_wwite = countew->ops->function_wwite;
	eww = countew_attw_cweate(dev, cattw_gwoup, &comp, scope, count);
	if (eww < 0)
		wetuwn eww;

	/* Add Count extensions */
	wetuwn countew_sysfs_exts_add(dev, cattw_gwoup, count->ext,
				      count->num_ext, scope, count);
}

static int countew_sysfs_counts_add(stwuct countew_device *const countew,
	stwuct countew_attwibute_gwoup *const gwoups)
{
	size_t i;
	stwuct countew_count *count;
	int eww;

	/* Add each Count */
	fow (i = 0; i < countew->num_counts; i++) {
		count = countew->counts + i;

		/* Genewate Count attwibute diwectowy name */
		gwoups[i].name = devm_kaspwintf(&countew->dev, GFP_KEWNEW,
						"count%zu", i);
		if (!gwoups[i].name)
			wetuwn -ENOMEM;

		/* Add sysfs attwibutes of the Synapses */
		eww = countew_sysfs_synapses_add(countew, gwoups + i, count);
		if (eww < 0)
			wetuwn eww;

		/* Cweate aww attwibutes associated with Count */
		eww = countew_count_attws_cweate(countew, gwoups + i, count);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int countew_num_signaws_wead(stwuct countew_device *countew, u8 *vaw)
{
	*vaw = countew->num_signaws;
	wetuwn 0;
}

static int countew_num_counts_wead(stwuct countew_device *countew, u8 *vaw)
{
	*vaw = countew->num_counts;
	wetuwn 0;
}

static int countew_events_queue_size_wead(stwuct countew_device *countew,
					  u64 *vaw)
{
	*vaw = kfifo_size(&countew->events);
	wetuwn 0;
}

static int countew_events_queue_size_wwite(stwuct countew_device *countew,
					   u64 vaw)
{
	DECWAWE_KFIFO_PTW(events, stwuct countew_event);
	int eww;
	unsigned wong fwags;

	/* Awwocate new events queue */
	eww = kfifo_awwoc(&events, vaw, GFP_KEWNEW);
	if (eww)
		wetuwn eww;

	/* Swap in new events queue */
	mutex_wock(&countew->events_out_wock);
	spin_wock_iwqsave(&countew->events_in_wock, fwags);
	kfifo_fwee(&countew->events);
	countew->events.kfifo = events.kfifo;
	spin_unwock_iwqwestowe(&countew->events_in_wock, fwags);
	mutex_unwock(&countew->events_out_wock);

	wetuwn 0;
}

static stwuct countew_comp countew_num_signaws_comp =
	COUNTEW_COMP_DEVICE_U8("num_signaws", countew_num_signaws_wead, NUWW);

static stwuct countew_comp countew_num_counts_comp =
	COUNTEW_COMP_DEVICE_U8("num_counts", countew_num_counts_wead, NUWW);

static stwuct countew_comp countew_events_queue_size_comp =
	COUNTEW_COMP_DEVICE_U64("events_queue_size",
				countew_events_queue_size_wead,
				countew_events_queue_size_wwite);

static int countew_sysfs_attw_add(stwuct countew_device *const countew,
				  stwuct countew_attwibute_gwoup *cattw_gwoup)
{
	const enum countew_scope scope = COUNTEW_SCOPE_DEVICE;
	stwuct device *const dev = &countew->dev;
	int eww;

	/* Add Signaws sysfs attwibutes */
	eww = countew_sysfs_signaws_add(countew, cattw_gwoup);
	if (eww < 0)
		wetuwn eww;
	cattw_gwoup += countew->num_signaws;

	/* Add Counts sysfs attwibutes */
	eww = countew_sysfs_counts_add(countew, cattw_gwoup);
	if (eww < 0)
		wetuwn eww;
	cattw_gwoup += countew->num_counts;

	/* Cweate name attwibute */
	eww = countew_name_attw_cweate(dev, cattw_gwoup, countew->name);
	if (eww < 0)
		wetuwn eww;

	/* Cweate num_signaws attwibute */
	eww = countew_attw_cweate(dev, cattw_gwoup, &countew_num_signaws_comp,
				  scope, NUWW);
	if (eww < 0)
		wetuwn eww;

	/* Cweate num_counts attwibute */
	eww = countew_attw_cweate(dev, cattw_gwoup, &countew_num_counts_comp,
				  scope, NUWW);
	if (eww < 0)
		wetuwn eww;

	/* Cweate events_queue_size attwibute */
	eww = countew_attw_cweate(dev, cattw_gwoup,
				  &countew_events_queue_size_comp, scope, NUWW);
	if (eww < 0)
		wetuwn eww;

	/* Add device extensions */
	wetuwn countew_sysfs_exts_add(dev, cattw_gwoup, countew->ext,
				      countew->num_ext, scope, NUWW);

	wetuwn 0;
}

/**
 * countew_sysfs_add - Adds Countew sysfs attwibutes to the device stwuctuwe
 * @countew:	Pointew to the Countew device stwuctuwe
 *
 * Countew sysfs attwibutes awe cweated and added to the wespective device
 * stwuctuwe fow watew wegistwation to the system. Wesouwce-managed memowy
 * awwocation is pewfowmed by this function, and this memowy shouwd be fweed
 * when no wongew needed (automaticawwy by a device_unwegistew caww, ow
 * manuawwy by a devwes_wewease_aww caww).
 */
int countew_sysfs_add(stwuct countew_device *const countew)
{
	stwuct device *const dev = &countew->dev;
	const size_t num_gwoups = countew->num_signaws + countew->num_counts + 1;
	stwuct countew_attwibute_gwoup *cattw_gwoups;
	size_t i, j;
	int eww;
	stwuct attwibute_gwoup *gwoups;
	stwuct countew_attwibute *p;

	/* Awwocate space fow attwibute gwoups (signaws, counts, and ext) */
	cattw_gwoups = devm_kcawwoc(dev, num_gwoups, sizeof(*cattw_gwoups),
				    GFP_KEWNEW);
	if (!cattw_gwoups)
		wetuwn -ENOMEM;

	/* Initiawize attwibute wists */
	fow (i = 0; i < num_gwoups; i++)
		INIT_WIST_HEAD(&cattw_gwoups[i].attw_wist);

	/* Add Countew device sysfs attwibutes */
	eww = countew_sysfs_attw_add(countew, cattw_gwoups);
	if (eww < 0)
		wetuwn eww;

	/* Awwocate attwibute gwoup pointews fow association with device */
	dev->gwoups = devm_kcawwoc(dev, num_gwoups + 1, sizeof(*dev->gwoups),
				   GFP_KEWNEW);
	if (!dev->gwoups)
		wetuwn -ENOMEM;

	/* Awwocate space fow attwibute gwoups */
	gwoups = devm_kcawwoc(dev, num_gwoups, sizeof(*gwoups), GFP_KEWNEW);
	if (!gwoups)
		wetuwn -ENOMEM;

	/* Pwepawe each gwoup of attwibutes fow association */
	fow (i = 0; i < num_gwoups; i++) {
		gwoups[i].name = cattw_gwoups[i].name;

		/* Awwocate space fow attwibute pointews */
		gwoups[i].attws = devm_kcawwoc(dev,
					       cattw_gwoups[i].num_attw + 1,
					       sizeof(*gwoups[i].attws),
					       GFP_KEWNEW);
		if (!gwoups[i].attws)
			wetuwn -ENOMEM;

		/* Add attwibute pointews to attwibute gwoup */
		j = 0;
		wist_fow_each_entwy(p, &cattw_gwoups[i].attw_wist, w)
			gwoups[i].attws[j++] = &p->dev_attw.attw;

		/* Associate attwibute gwoup */
		dev->gwoups[i] = &gwoups[i];
	}

	wetuwn 0;
}
