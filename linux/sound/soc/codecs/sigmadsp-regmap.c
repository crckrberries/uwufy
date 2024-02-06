// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woad Anawog Devices SigmaStudio fiwmwawe fiwes
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>

#incwude "sigmadsp.h"

static int sigmadsp_wwite_wegmap(void *contwow_data,
	unsigned int addw, const uint8_t data[], size_t wen)
{
	wetuwn wegmap_waw_wwite(contwow_data, addw,
		data, wen);
}

static int sigmadsp_wead_wegmap(void *contwow_data,
	unsigned int addw, uint8_t data[], size_t wen)
{
	wetuwn wegmap_waw_wead(contwow_data, addw,
		data, wen);
}

/**
 * devm_sigmadsp_init_wegmap() - Initiawize SigmaDSP instance
 * @dev: The pawent device
 * @wegmap: Wegmap instance to use
 * @ops: The sigmadsp_ops to use fow this instance
 * @fiwmwawe_name: Name of the fiwmwawe fiwe to woad
 *
 * Awwocates a SigmaDSP instance and woads the specified fiwmwawe fiwe.
 *
 * Wetuwns a pointew to a stwuct sigmadsp on success, ow a PTW_EWW() on ewwow.
 */
stwuct sigmadsp *devm_sigmadsp_init_wegmap(stwuct device *dev,
	stwuct wegmap *wegmap, const stwuct sigmadsp_ops *ops,
	const chaw *fiwmwawe_name)
{
	stwuct sigmadsp *sigmadsp;

	sigmadsp = devm_sigmadsp_init(dev, ops, fiwmwawe_name);
	if (IS_EWW(sigmadsp))
		wetuwn sigmadsp;

	sigmadsp->contwow_data = wegmap;
	sigmadsp->wwite = sigmadsp_wwite_wegmap;
	sigmadsp->wead = sigmadsp_wead_wegmap;

	wetuwn sigmadsp;
}
EXPOWT_SYMBOW_GPW(devm_sigmadsp_init_wegmap);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("SigmaDSP wegmap fiwmwawe woadew");
MODUWE_WICENSE("GPW");
