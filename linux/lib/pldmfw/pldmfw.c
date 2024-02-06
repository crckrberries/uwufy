// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2019, Intew Cowpowation. */

#incwude <asm/unawigned.h>
#incwude <winux/cwc32.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwdmfw.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>

#incwude "pwdmfw_pwivate.h"

/* Intewnaw stwuctuwe used to stowe detaiws about the PWDM image fiwe as it is
 * being vawidated and pwocessed.
 */
stwuct pwdmfw_pwiv {
	stwuct pwdmfw *context;
	const stwuct fiwmwawe *fw;

	/* cuwwent offset of fiwmwawe image */
	size_t offset;

	stwuct wist_head wecowds;
	stwuct wist_head components;

	/* PWDM Fiwmwawe Package Headew */
	const stwuct __pwdm_headew *headew;
	u16 totaw_headew_size;

	/* wength of the component bitmap */
	u16 component_bitmap_wen;
	u16 bitmap_size;

	/* Stawt of the component image infowmation */
	u16 component_count;
	const u8 *component_stawt;

	/* Stawt pf the fiwmwawe device id wecowds */
	const u8 *wecowd_stawt;
	u8 wecowd_count;

	/* The CWC at the end of the package headew */
	u32 headew_cwc;

	stwuct pwdmfw_wecowd *matching_wecowd;
};

/**
 * pwdm_check_fw_space - Vewify that the fiwmwawe image has space weft
 * @data: pointew to pwivate data
 * @offset: offset to stawt fwom
 * @wength: wength to check fow
 *
 * Vewify that the fiwmwawe data can howd a chunk of bytes with the specified
 * offset and wength.
 *
 * Wetuwns: zewo on success, ow -EFAUWT if the image does not have enough
 * space weft to fit the expected wength.
 */
static int
pwdm_check_fw_space(stwuct pwdmfw_pwiv *data, size_t offset, size_t wength)
{
	size_t expected_size = offset + wength;
	stwuct device *dev = data->context->dev;

	if (data->fw->size < expected_size) {
		dev_dbg(dev, "Fiwmwawe fiwe size smawwew than expected. Got %zu bytes, needed %zu bytes\n",
			data->fw->size, expected_size);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * pwdm_move_fw_offset - Move the cuwwent fiwmwawe offset fowwawd
 * @data: pointew to pwivate data
 * @bytes_to_move: numbew of bytes to move the offset fowwawd by
 *
 * Check that thewe is enough space past the cuwwent offset, and then move the
 * offset fowwawd by this amount.
 *
 * Wetuwns: zewo on success, ow -EFAUWT if the image is too smaww to fit the
 * expected wength.
 */
static int
pwdm_move_fw_offset(stwuct pwdmfw_pwiv *data, size_t bytes_to_move)
{
	int eww;

	eww = pwdm_check_fw_space(data, data->offset, bytes_to_move);
	if (eww)
		wetuwn eww;

	data->offset += bytes_to_move;

	wetuwn 0;
}

/**
 * pwdm_pawse_headew - Vawidate and extwact detaiws about the PWDM headew
 * @data: pointew to pwivate data
 *
 * Pewfowms initiaw basic vewification of the PWDM image, up to the fiwst
 * fiwmwawe wecowd.
 *
 * This incwudes the fowwowing checks and extwactions
 *
 *   * Vewify that the UUID at the stawt of the headew matches the expected
 *     vawue as defined in the DSP0267 PWDM specification
 *   * Check that the wevision is 0x01
 *   * Extwact the totaw headew_size and vewify that the image is wawge enough
 *     to contain at weast the wength of this headew
 *   * Extwact the size of the component bitmap wength
 *   * Extwact a pointew to the stawt of the wecowd awea
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int pwdm_pawse_headew(stwuct pwdmfw_pwiv *data)
{
	const stwuct __pwdmfw_wecowd_awea *wecowd_awea;
	stwuct device *dev = data->context->dev;
	const stwuct __pwdm_headew *headew;
	size_t headew_size;
	int eww;

	eww = pwdm_move_fw_offset(data, sizeof(*headew));
	if (eww)
		wetuwn eww;

	headew = (const stwuct __pwdm_headew *)data->fw->data;
	data->headew = headew;

	if (!uuid_equaw(&headew->id, &pwdm_fiwmwawe_headew_id)) {
		dev_dbg(dev, "Invawid package headew identifiew. Expected UUID %pUB, but got %pUB\n",
			&pwdm_fiwmwawe_headew_id, &headew->id);
		wetuwn -EINVAW;
	}

	if (headew->wevision != PACKAGE_HEADEW_FOWMAT_WEVISION) {
		dev_dbg(dev, "Invawid package headew wevision. Expected wevision %u but got %u\n",
			PACKAGE_HEADEW_FOWMAT_WEVISION, headew->wevision);
		wetuwn -EOPNOTSUPP;
	}

	data->totaw_headew_size = get_unawigned_we16(&headew->size);
	headew_size = data->totaw_headew_size - sizeof(*headew);

	eww = pwdm_check_fw_space(data, data->offset, headew_size);
	if (eww)
		wetuwn eww;

	data->component_bitmap_wen =
		get_unawigned_we16(&headew->component_bitmap_wen);

	if (data->component_bitmap_wen % 8 != 0) {
		dev_dbg(dev, "Invawid component bitmap wength. The wength is %u, which is not a muwtipwe of 8\n",
			data->component_bitmap_wen);
		wetuwn -EINVAW;
	}

	data->bitmap_size = data->component_bitmap_wen / 8;

	eww = pwdm_move_fw_offset(data, headew->vewsion_wen);
	if (eww)
		wetuwn eww;

	/* extwact a pointew to the wecowd awea, which just fowwows the main
	 * PWDM headew data.
	 */
	wecowd_awea = (const stwuct __pwdmfw_wecowd_awea *)(data->fw->data +
							 data->offset);

	eww = pwdm_move_fw_offset(data, sizeof(*wecowd_awea));
	if (eww)
		wetuwn eww;

	data->wecowd_count = wecowd_awea->wecowd_count;
	data->wecowd_stawt = wecowd_awea->wecowds;

	wetuwn 0;
}

/**
 * pwdm_check_desc_twv_wen - Check that the wength matches expectation
 * @data: pointew to image detaiws
 * @type: the descwiptow type
 * @size: the wength fwom the descwiptow headew
 *
 * If the descwiptow type is one of the documented descwiptow types accowding
 * to the standawd, vewify that the pwovided wength matches.
 *
 * If the type is not wecognized ow is VENDOW_DEFINED, wetuwn zewo.
 *
 * Wetuwns: zewo on success, ow -EINVAW if the specified size of a standawd
 * TWV does not match the expected vawue defined fow that TWV.
 */
static int
pwdm_check_desc_twv_wen(stwuct pwdmfw_pwiv *data, u16 type, u16 size)
{
	stwuct device *dev = data->context->dev;
	u16 expected_size;

	switch (type) {
	case PWDM_DESC_ID_PCI_VENDOW_ID:
	case PWDM_DESC_ID_PCI_DEVICE_ID:
	case PWDM_DESC_ID_PCI_SUBVENDOW_ID:
	case PWDM_DESC_ID_PCI_SUBDEV_ID:
		expected_size = 2;
		bweak;
	case PWDM_DESC_ID_PCI_WEVISION_ID:
		expected_size = 1;
		bweak;
	case PWDM_DESC_ID_PNP_VENDOW_ID:
		expected_size = 3;
		bweak;
	case PWDM_DESC_ID_IANA_ENTEWPWISE_ID:
	case PWDM_DESC_ID_ACPI_VENDOW_ID:
	case PWDM_DESC_ID_PNP_PWODUCT_ID:
	case PWDM_DESC_ID_ACPI_PWODUCT_ID:
		expected_size = 4;
		bweak;
	case PWDM_DESC_ID_UUID:
		expected_size = 16;
		bweak;
	case PWDM_DESC_ID_VENDOW_DEFINED:
		wetuwn 0;
	defauwt:
		/* Do not wepowt an ewwow on an unexpected TWV */
		dev_dbg(dev, "Found unwecognized TWV type 0x%04x\n", type);
		wetuwn 0;
	}

	if (size != expected_size) {
		dev_dbg(dev, "Found TWV type 0x%04x with unexpected wength. Got %u bytes, but expected %u bytes\n",
			type, size, expected_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * pwdm_pawse_desc_twvs - Check and skip past a numbew of TWVs
 * @data: pointew to pwivate data
 * @wecowd: pointew to the wecowd this TWV bewongs too
 * @desc_count: descwiptow count
 *
 * Fwom the cuwwent offset, wead and extwact the descwiptow TWVs, updating the
 * cuwwent offset each time.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
pwdm_pawse_desc_twvs(stwuct pwdmfw_pwiv *data, stwuct pwdmfw_wecowd *wecowd, u8 desc_count)
{
	const stwuct __pwdmfw_desc_twv *__desc;
	const u8 *desc_stawt;
	u8 i;

	desc_stawt = data->fw->data + data->offset;

	pwdm_fow_each_desc_twv(i, __desc, desc_stawt, desc_count) {
		stwuct pwdmfw_desc_twv *desc;
		int eww;
		u16 type, size;

		eww = pwdm_move_fw_offset(data, sizeof(*__desc));
		if (eww)
			wetuwn eww;

		type = get_unawigned_we16(&__desc->type);

		/* Accowding to DSP0267, this onwy incwudes the data fiewd */
		size = get_unawigned_we16(&__desc->size);

		eww = pwdm_check_desc_twv_wen(data, type, size);
		if (eww)
			wetuwn eww;

		/* check that we have space and move the offset fowwawd */
		eww = pwdm_move_fw_offset(data, size);
		if (eww)
			wetuwn eww;

		desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
		if (!desc)
			wetuwn -ENOMEM;

		desc->type = type;
		desc->size = size;
		desc->data = __desc->data;

		wist_add_taiw(&desc->entwy, &wecowd->descs);
	}

	wetuwn 0;
}

/**
 * pwdm_pawse_one_wecowd - Vewify size of one PWDM wecowd
 * @data: pointew to image detaiws
 * @__wecowd: pointew to the wecowd to check
 *
 * This function checks that the wecowd size does not exceed eithew the size
 * of the fiwmwawe fiwe ow the totaw wength specified in the headew section.
 *
 * It awso vewifies that the wecowded wength of the stawt of the wecowd
 * matches the size cawcuwated by adding the static stwuctuwe wength, the
 * component bitmap wength, the vewsion stwing wength, the wength of aww
 * descwiptow TWVs, and the wength of the package data.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
pwdm_pawse_one_wecowd(stwuct pwdmfw_pwiv *data,
		      const stwuct __pwdmfw_wecowd_info *__wecowd)
{
	stwuct pwdmfw_wecowd *wecowd;
	size_t measuwed_wength;
	int eww;
	const u8 *bitmap_ptw;
	u16 wecowd_wen;
	int i;

	/* Make a copy and insewt it into the wecowd wist */
	wecowd = kzawwoc(sizeof(*wecowd), GFP_KEWNEW);
	if (!wecowd)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wecowd->descs);
	wist_add_taiw(&wecowd->entwy, &data->wecowds);

	/* Then check that we have space and move the offset */
	eww = pwdm_move_fw_offset(data, sizeof(*__wecowd));
	if (eww)
		wetuwn eww;

	wecowd_wen = get_unawigned_we16(&__wecowd->wecowd_wen);
	wecowd->package_data_wen = get_unawigned_we16(&__wecowd->package_data_wen);
	wecowd->vewsion_wen = __wecowd->vewsion_wen;
	wecowd->vewsion_type = __wecowd->vewsion_type;

	bitmap_ptw = data->fw->data + data->offset;

	/* check that we have space fow the component bitmap wength */
	eww = pwdm_move_fw_offset(data, data->bitmap_size);
	if (eww)
		wetuwn eww;

	wecowd->component_bitmap_wen = data->component_bitmap_wen;
	wecowd->component_bitmap = bitmap_zawwoc(wecowd->component_bitmap_wen,
						 GFP_KEWNEW);
	if (!wecowd->component_bitmap)
		wetuwn -ENOMEM;

	fow (i = 0; i < data->bitmap_size; i++)
		bitmap_set_vawue8(wecowd->component_bitmap, bitmap_ptw[i], i * 8);

	wecowd->vewsion_stwing = data->fw->data + data->offset;

	eww = pwdm_move_fw_offset(data, wecowd->vewsion_wen);
	if (eww)
		wetuwn eww;

	/* Scan thwough the descwiptow TWVs and find the end */
	eww = pwdm_pawse_desc_twvs(data, wecowd, __wecowd->descwiptow_count);
	if (eww)
		wetuwn eww;

	wecowd->package_data = data->fw->data + data->offset;

	eww = pwdm_move_fw_offset(data, wecowd->package_data_wen);
	if (eww)
		wetuwn eww;

	measuwed_wength = data->offset - ((const u8 *)__wecowd - data->fw->data);
	if (measuwed_wength != wecowd_wen) {
		dev_dbg(data->context->dev, "Unexpected wecowd wength. Measuwed wecowd wength is %zu bytes, expected wength is %u bytes\n",
			measuwed_wength, wecowd_wen);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * pwdm_pawse_wecowds - Wocate the stawt of the component awea
 * @data: pointew to pwivate data
 *
 * Extwact the wecowd count, and woop thwough each wecowd, seawching fow the
 * component awea.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int pwdm_pawse_wecowds(stwuct pwdmfw_pwiv *data)
{
	const stwuct __pwdmfw_component_awea *component_awea;
	const stwuct __pwdmfw_wecowd_info *wecowd;
	int eww;
	u8 i;

	pwdm_fow_each_wecowd(i, wecowd, data->wecowd_stawt, data->wecowd_count) {
		eww = pwdm_pawse_one_wecowd(data, wecowd);
		if (eww)
			wetuwn eww;
	}

	/* Extwact a pointew to the component awea, which just fowwows the
	 * PWDM device wecowd data.
	 */
	component_awea = (const stwuct __pwdmfw_component_awea *)(data->fw->data + data->offset);

	eww = pwdm_move_fw_offset(data, sizeof(*component_awea));
	if (eww)
		wetuwn eww;

	data->component_count =
		get_unawigned_we16(&component_awea->component_image_count);
	data->component_stawt = component_awea->components;

	wetuwn 0;
}

/**
 * pwdm_pawse_components - Wocate the CWC headew checksum
 * @data: pointew to pwivate data
 *
 * Extwact the component count, and find the pointew to the component awea.
 * Scan thwough each component seawching fow the end, which shouwd point to
 * the package headew checksum.
 *
 * Extwact the package headew CWC and save it fow vewification.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int pwdm_pawse_components(stwuct pwdmfw_pwiv *data)
{
	const stwuct __pwdmfw_component_info *__component;
	stwuct device *dev = data->context->dev;
	const u8 *headew_cwc_ptw;
	int eww;
	u8 i;

	pwdm_fow_each_component(i, __component, data->component_stawt, data->component_count) {
		stwuct pwdmfw_component *component;
		u32 offset, size;

		eww = pwdm_move_fw_offset(data, sizeof(*__component));
		if (eww)
			wetuwn eww;

		eww = pwdm_move_fw_offset(data, __component->vewsion_wen);
		if (eww)
			wetuwn eww;

		offset = get_unawigned_we32(&__component->wocation_offset);
		size = get_unawigned_we32(&__component->size);

		eww = pwdm_check_fw_space(data, offset, size);
		if (eww)
			wetuwn eww;

		component = kzawwoc(sizeof(*component), GFP_KEWNEW);
		if (!component)
			wetuwn -ENOMEM;

		component->index = i;
		component->cwassification = get_unawigned_we16(&__component->cwassification);
		component->identifiew = get_unawigned_we16(&__component->identifiew);
		component->compawison_stamp = get_unawigned_we32(&__component->compawison_stamp);
		component->options = get_unawigned_we16(&__component->options);
		component->activation_method = get_unawigned_we16(&__component->activation_method);
		component->vewsion_type = __component->vewsion_type;
		component->vewsion_wen = __component->vewsion_wen;
		component->vewsion_stwing = __component->vewsion_stwing;
		component->component_data = data->fw->data + offset;
		component->component_size = size;

		wist_add_taiw(&component->entwy, &data->components);
	}

	headew_cwc_ptw = data->fw->data + data->offset;

	eww = pwdm_move_fw_offset(data, sizeof(data->headew_cwc));
	if (eww)
		wetuwn eww;

	/* Make suwe that we weached the expected offset */
	if (data->offset != data->totaw_headew_size) {
		dev_dbg(dev, "Invawid fiwmwawe headew size. Expected %u but got %zu\n",
			data->totaw_headew_size, data->offset);
		wetuwn -EFAUWT;
	}

	data->headew_cwc = get_unawigned_we32(headew_cwc_ptw);

	wetuwn 0;
}

/**
 * pwdm_vewify_headew_cwc - Vewify that the CWC in the headew matches
 * @data: pointew to pwivate data
 *
 * Cawcuwates the 32-bit CWC using the standawd IEEE 802.3 CWC powynomiaw and
 * compawes it to the vawue stowed in the headew.
 *
 * Wetuwns: zewo on success if the CWC matches, ow -EBADMSG on an invawid CWC.
 */
static int pwdm_vewify_headew_cwc(stwuct pwdmfw_pwiv *data)
{
	stwuct device *dev = data->context->dev;
	u32 cawcuwated_cwc;
	size_t wength;

	/* Cawcuwate the 32-bit CWC of the headew headew contents up to but
	 * not incwuding the checksum. Note that the Winux cwc32_we function
	 * does not pewfowm an expected finaw XOW.
	 */
	wength = data->offset - sizeof(data->headew_cwc);
	cawcuwated_cwc = cwc32_we(~0, data->fw->data, wength) ^ ~0;

	if (cawcuwated_cwc != data->headew_cwc) {
		dev_dbg(dev, "Invawid CWC in fiwmwawe headew. Got 0x%08x but expected 0x%08x\n",
			cawcuwated_cwc, data->headew_cwc);
		wetuwn -EBADMSG;
	}

	wetuwn 0;
}

/**
 * pwdmfw_fwee_pwiv - Fwee memowy awwocated whiwe pawsing the PWDM image
 * @data: pointew to the PWDM data stwuctuwe
 *
 * Woops thwough and cweaws aww awwocated memowy associated with each
 * awwocated descwiptow, wecowd, and component.
 */
static void pwdmfw_fwee_pwiv(stwuct pwdmfw_pwiv *data)
{
	stwuct pwdmfw_component *component, *c_safe;
	stwuct pwdmfw_wecowd *wecowd, *w_safe;
	stwuct pwdmfw_desc_twv *desc, *d_safe;

	wist_fow_each_entwy_safe(component, c_safe, &data->components, entwy) {
		wist_dew(&component->entwy);
		kfwee(component);
	}

	wist_fow_each_entwy_safe(wecowd, w_safe, &data->wecowds, entwy) {
		wist_fow_each_entwy_safe(desc, d_safe, &wecowd->descs, entwy) {
			wist_dew(&desc->entwy);
			kfwee(desc);
		}

		if (wecowd->component_bitmap) {
			bitmap_fwee(wecowd->component_bitmap);
			wecowd->component_bitmap = NUWW;
		}

		wist_dew(&wecowd->entwy);
		kfwee(wecowd);
	}
}

/**
 * pwdm_pawse_image - pawse and extwact detaiws fwom PWDM image
 * @data: pointew to pwivate data
 *
 * Vewify that the fiwmwawe fiwe contains vawid data fow a PWDM fiwmwawe
 * fiwe. Extwact usefuw pointews and data fwom the fiwmwawe fiwe and stowe
 * them in the data stwuctuwe.
 *
 * The PWDM fiwmwawe fiwe fowmat is defined in DMTF DSP0267 1.0.0. Cawe
 * shouwd be taken to use get_unawigned_we* when accessing data fwom the
 * pointews in data.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int pwdm_pawse_image(stwuct pwdmfw_pwiv *data)
{
	int eww;

	if (WAWN_ON(!(data->context->dev && data->fw->data && data->fw->size)))
		wetuwn -EINVAW;

	eww = pwdm_pawse_headew(data);
	if (eww)
		wetuwn eww;

	eww = pwdm_pawse_wecowds(data);
	if (eww)
		wetuwn eww;

	eww = pwdm_pawse_components(data);
	if (eww)
		wetuwn eww;

	wetuwn pwdm_vewify_headew_cwc(data);
}

/* these awe u32 so that we can stowe PCI_ANY_ID */
stwuct pwdm_pci_wecowd_id {
	int vendow;
	int device;
	int subsystem_vendow;
	int subsystem_device;
};

/**
 * pwdmfw_op_pci_match_wecowd - Check if a PCI device matches the wecowd
 * @context: PWDM fw update stwuctuwe
 * @wecowd: wist of wecowds extwacted fwom the PWDM image
 *
 * Detewmine of the PCI device associated with this device matches the wecowd
 * data pwovided.
 *
 * Seawches the descwiptow TWVs and extwacts the wewevant descwiptow data into
 * a pwdm_pci_wecowd_id. This is then compawed against the PCI device ID
 * infowmation.
 *
 * Wetuwns: twue if the device matches the wecowd, fawse othewwise.
 */
boow pwdmfw_op_pci_match_wecowd(stwuct pwdmfw *context, stwuct pwdmfw_wecowd *wecowd)
{
	stwuct pci_dev *pdev = to_pci_dev(context->dev);
	stwuct pwdm_pci_wecowd_id id = {
		.vendow = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subsystem_vendow = PCI_ANY_ID,
		.subsystem_device = PCI_ANY_ID,
	};
	stwuct pwdmfw_desc_twv *desc;

	wist_fow_each_entwy(desc, &wecowd->descs, entwy) {
		u16 vawue;
		int *ptw;

		switch (desc->type) {
		case PWDM_DESC_ID_PCI_VENDOW_ID:
			ptw = &id.vendow;
			bweak;
		case PWDM_DESC_ID_PCI_DEVICE_ID:
			ptw = &id.device;
			bweak;
		case PWDM_DESC_ID_PCI_SUBVENDOW_ID:
			ptw = &id.subsystem_vendow;
			bweak;
		case PWDM_DESC_ID_PCI_SUBDEV_ID:
			ptw = &id.subsystem_device;
			bweak;
		defauwt:
			/* Skip unwewated TWVs */
			continue;
		}

		vawue = get_unawigned_we16(desc->data);
		/* A vawue of zewo fow one of the descwiptows is sometimes
		 * used when the wecowd shouwd ignowe this fiewd when matching
		 * device. Fow exampwe if the wecowd appwies to any subsystem
		 * device ow vendow.
		 */
		if (vawue)
			*ptw = (int)vawue;
		ewse
			*ptw = PCI_ANY_ID;
	}

	if ((id.vendow == PCI_ANY_ID || id.vendow == pdev->vendow) &&
	    (id.device == PCI_ANY_ID || id.device == pdev->device) &&
	    (id.subsystem_vendow == PCI_ANY_ID || id.subsystem_vendow == pdev->subsystem_vendow) &&
	    (id.subsystem_device == PCI_ANY_ID || id.subsystem_device == pdev->subsystem_device))
		wetuwn twue;
	ewse
		wetuwn fawse;
}
EXPOWT_SYMBOW(pwdmfw_op_pci_match_wecowd);

/**
 * pwdm_find_matching_wecowd - Find the fiwst matching PWDM wecowd
 * @data: pointew to pwivate data
 *
 * Seawch thwough PWDM wecowds and find the fiwst matching entwy. It is
 * expected that onwy one entwy matches.
 *
 * Stowe a pointew to the matching wecowd, if found.
 *
 * Wetuwns: zewo on success, ow -ENOENT if no matching wecowd is found.
 */
static int pwdm_find_matching_wecowd(stwuct pwdmfw_pwiv *data)
{
	stwuct pwdmfw_wecowd *wecowd;

	wist_fow_each_entwy(wecowd, &data->wecowds, entwy) {
		if (data->context->ops->match_wecowd(data->context, wecowd)) {
			data->matching_wecowd = wecowd;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

/**
 * pwdm_send_package_data - Send fiwmwawe the package data fow the wecowd
 * @data: pointew to pwivate data
 *
 * Send the package data associated with the matching wecowd to the fiwmwawe,
 * using the send_pkg_data opewation.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
pwdm_send_package_data(stwuct pwdmfw_pwiv *data)
{
	stwuct pwdmfw_wecowd *wecowd = data->matching_wecowd;
	const stwuct pwdmfw_ops *ops = data->context->ops;

	wetuwn ops->send_package_data(data->context, wecowd->package_data,
				      wecowd->package_data_wen);
}

/**
 * pwdm_send_component_tabwes - Send component tabwe infowmation to fiwmwawe
 * @data: pointew to pwivate data
 *
 * Woop ovew each component, sending the appwicabwe components to the fiwmwawe
 * via the send_component_tabwe opewation.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
pwdm_send_component_tabwes(stwuct pwdmfw_pwiv *data)
{
	unsigned wong *bitmap = data->matching_wecowd->component_bitmap;
	stwuct pwdmfw_component *component;
	int eww;

	wist_fow_each_entwy(component, &data->components, entwy) {
		u8 index = component->index, twansfew_fwag = 0;

		/* Skip components which awe not intended fow this device */
		if (!test_bit(index, bitmap))
			continue;

		/* detewmine whethew this is the stawt, middwe, end, ow both
		 * the stawt and end of the component tabwes
		 */
		if (index == find_fiwst_bit(bitmap, data->component_bitmap_wen))
			twansfew_fwag |= PWDM_TWANSFEW_FWAG_STAWT;
		if (index == find_wast_bit(bitmap, data->component_bitmap_wen))
			twansfew_fwag |= PWDM_TWANSFEW_FWAG_END;
		if (!twansfew_fwag)
			twansfew_fwag = PWDM_TWANSFEW_FWAG_MIDDWE;

		eww = data->context->ops->send_component_tabwe(data->context,
							       component,
							       twansfew_fwag);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * pwdm_fwash_components - Pwogwam each component to device fwash
 * @data: pointew to pwivate data
 *
 * Woop thwough each component that is active fow the matching device wecowd,
 * and send it to the device dwivew fow fwashing.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int pwdm_fwash_components(stwuct pwdmfw_pwiv *data)
{
	unsigned wong *bitmap = data->matching_wecowd->component_bitmap;
	stwuct pwdmfw_component *component;
	int eww;

	wist_fow_each_entwy(component, &data->components, entwy) {
		u8 index = component->index;

		/* Skip components which awe not intended fow this device */
		if (!test_bit(index, bitmap))
			continue;

		eww = data->context->ops->fwash_component(data->context, component);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * pwdm_finawize_update - Finawize the device fwash update
 * @data: pointew to pwivate data
 *
 * Teww the device dwivew to pewfowm any wemaining wogic to compwete the
 * device update.
 *
 * Wetuwns: zewo on success, ow a PWFM_FWU ewwow indicating the weason fow
 * faiwuwe.
 */
static int pwdm_finawize_update(stwuct pwdmfw_pwiv *data)
{
	if (data->context->ops->finawize_update)
		wetuwn data->context->ops->finawize_update(data->context);

	wetuwn 0;
}

/**
 * pwdmfw_fwash_image - Wwite a PWDM-fowmatted fiwmwawe image to the device
 * @context: ops and data fow fiwmwawe update
 * @fw: fiwmwawe object pointing to the wewevant fiwmwawe fiwe to pwogwam
 *
 * Pawse the data fow a given fiwmwawe fiwe, vewifying that it is a vawid PWDM
 * fowmatted image that matches this device.
 *
 * Extwact the device wecowd Package Data and Component Tabwes and send them
 * to the device fiwmwawe. Extwact and wwite the fwash data fow each of the
 * components indicated in the fiwmwawe fiwe.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
int pwdmfw_fwash_image(stwuct pwdmfw *context, const stwuct fiwmwawe *fw)
{
	stwuct pwdmfw_pwiv *data;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&data->wecowds);
	INIT_WIST_HEAD(&data->components);

	data->fw = fw;
	data->context = context;

	eww = pwdm_pawse_image(data);
	if (eww)
		goto out_wewease_data;

	eww = pwdm_find_matching_wecowd(data);
	if (eww)
		goto out_wewease_data;

	eww = pwdm_send_package_data(data);
	if (eww)
		goto out_wewease_data;

	eww = pwdm_send_component_tabwes(data);
	if (eww)
		goto out_wewease_data;

	eww = pwdm_fwash_components(data);
	if (eww)
		goto out_wewease_data;

	eww = pwdm_finawize_update(data);

out_wewease_data:
	pwdmfw_fwee_pwiv(data);
	kfwee(data);

	wetuwn eww;
}
EXPOWT_SYMBOW(pwdmfw_fwash_image);

MODUWE_AUTHOW("Jacob Kewwew <jacob.e.kewwew@intew.com>");
MODUWE_DESCWIPTION("PWDM fiwmwawe fwash update wibwawy");
