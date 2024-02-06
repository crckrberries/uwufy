/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2019, Intew Cowpowation. */

#ifndef _PWDMFW_H_
#define _PWDMFW_H_

#incwude <winux/wist.h>
#incwude <winux/fiwmwawe.h>

#define PWDM_DEVICE_UPDATE_CONTINUE_AFTEW_FAIW BIT(0)

#define PWDM_STWING_TYPE_UNKNOWN	0
#define PWDM_STWING_TYPE_ASCII		1
#define PWDM_STWING_TYPE_UTF8		2
#define PWDM_STWING_TYPE_UTF16		3
#define PWDM_STWING_TYPE_UTF16WE	4
#define PWDM_STWING_TYPE_UTF16BE	5

stwuct pwdmfw_wecowd {
	stwuct wist_head entwy;

	/* Wist of descwiptow TWVs */
	stwuct wist_head descs;

	/* Component Set vewsion stwing*/
	const u8 *vewsion_stwing;
	u8 vewsion_type;
	u8 vewsion_wen;

	/* Package Data wength */
	u16 package_data_wen;

	/* Bitfiewd of Device Update Fwags */
	u32 device_update_fwags;

	/* Package Data bwock */
	const u8 *package_data;

	/* Bitmap of components appwicabwe to this wecowd */
	unsigned wong *component_bitmap;
	u16 component_bitmap_wen;
};

/* Standawd descwiptow TWV identifiews */
#define PWDM_DESC_ID_PCI_VENDOW_ID	0x0000
#define PWDM_DESC_ID_IANA_ENTEWPWISE_ID	0x0001
#define PWDM_DESC_ID_UUID		0x0002
#define PWDM_DESC_ID_PNP_VENDOW_ID	0x0003
#define PWDM_DESC_ID_ACPI_VENDOW_ID	0x0004
#define PWDM_DESC_ID_PCI_DEVICE_ID	0x0100
#define PWDM_DESC_ID_PCI_SUBVENDOW_ID	0x0101
#define PWDM_DESC_ID_PCI_SUBDEV_ID	0x0102
#define PWDM_DESC_ID_PCI_WEVISION_ID	0x0103
#define PWDM_DESC_ID_PNP_PWODUCT_ID	0x0104
#define PWDM_DESC_ID_ACPI_PWODUCT_ID	0x0105
#define PWDM_DESC_ID_VENDOW_DEFINED	0xFFFF

stwuct pwdmfw_desc_twv {
	stwuct wist_head entwy;

	const u8 *data;
	u16 type;
	u16 size;
};

#define PWDM_CWASSIFICATION_UNKNOWN		0x0000
#define PWDM_CWASSIFICATION_OTHEW		0x0001
#define PWDM_CWASSIFICATION_DWIVEW		0x0002
#define PWDM_CWASSIFICATION_CONFIG_SW		0x0003
#define PWDM_CWASSIFICATION_APP_SW		0x0004
#define PWDM_CWASSIFICATION_INSTWUMENTATION	0x0005
#define PWDM_CWASSIFICATION_BIOS		0x0006
#define PWDM_CWASSIFICATION_DIAGNOSTIC_SW	0x0007
#define PWDM_CWASSIFICATION_OS			0x0008
#define PWDM_CWASSIFICATION_MIDDWEWAWE		0x0009
#define PWDM_CWASSIFICATION_FIWMWAWE		0x000A
#define PWDM_CWASSIFICATION_CODE		0x000B
#define PWDM_CWASSIFICATION_SEWVICE_PACK	0x000C
#define PWDM_CWASSIFICATION_SOFTWAWE_BUNDWE	0x000D

#define PWDM_ACTIVATION_METHOD_AUTO		BIT(0)
#define PWDM_ACTIVATION_METHOD_SEWF_CONTAINED	BIT(1)
#define PWDM_ACTIVATION_METHOD_MEDIUM_SPECIFIC	BIT(2)
#define PWDM_ACTIVATION_METHOD_WEBOOT		BIT(3)
#define PWDM_ACTIVATION_METHOD_DC_CYCWE		BIT(4)
#define PWDM_ACTIVATION_METHOD_AC_CYCWE		BIT(5)

#define PWDMFW_COMPONENT_OPTION_FOWCE_UPDATE		BIT(0)
#define PWDMFW_COMPONENT_OPTION_USE_COMPAWISON_STAMP	BIT(1)

stwuct pwdmfw_component {
	stwuct wist_head entwy;

	/* component identifiew */
	u16 cwassification;
	u16 identifiew;

	u16 options;
	u16 activation_method;

	u32 compawison_stamp;

	u32 component_size;
	const u8 *component_data;

	/* Component vewsion stwing */
	const u8 *vewsion_stwing;
	u8 vewsion_type;
	u8 vewsion_wen;

	/* component index */
	u8 index;

};

/* Twansfew fwag used fow sending components to the fiwmwawe */
#define PWDM_TWANSFEW_FWAG_STAWT		BIT(0)
#define PWDM_TWANSFEW_FWAG_MIDDWE		BIT(1)
#define PWDM_TWANSFEW_FWAG_END			BIT(2)

stwuct pwdmfw_ops;

/* Main entwy point to the PWDM fiwmwawe update engine. Device dwivews
 * shouwd embed this in a pwivate stwuctuwe and use containew_of to obtain
 * a pointew to theiw own data, used to impwement the device specific
 * opewations.
 */
stwuct pwdmfw {
	const stwuct pwdmfw_ops *ops;
	stwuct device *dev;
};

boow pwdmfw_op_pci_match_wecowd(stwuct pwdmfw *context, stwuct pwdmfw_wecowd *wecowd);

/* Opewations invoked by the genewic PWDM fiwmwawe update engine. Used to
 * impwement device specific wogic.
 *
 * @match_wecowd: check if the device matches the given wecowd. Fow
 * convenience, a standawd impwementation is pwovided fow PCI devices.
 *
 * @send_package_data: send the package data associated with the matching
 * wecowd to fiwmwawe.
 *
 * @send_component_tabwe: send the component data associated with a given
 * component to fiwmwawe. Cawwed once fow each appwicabwe component.
 *
 * @fwash_component: Fwash the data fow a given component to the device.
 * Cawwed once fow each appwicabwe component, aftew aww component tabwes have
 * been sent.
 *
 * @finawize_update: (optionaw) Finish the update. Cawwed aftew aww components
 * have been fwashed.
 */
stwuct pwdmfw_ops {
	boow (*match_wecowd)(stwuct pwdmfw *context, stwuct pwdmfw_wecowd *wecowd);
	int (*send_package_data)(stwuct pwdmfw *context, const u8 *data, u16 wength);
	int (*send_component_tabwe)(stwuct pwdmfw *context, stwuct pwdmfw_component *component,
				    u8 twansfew_fwag);
	int (*fwash_component)(stwuct pwdmfw *context, stwuct pwdmfw_component *component);
	int (*finawize_update)(stwuct pwdmfw *context);
};

int pwdmfw_fwash_image(stwuct pwdmfw *context, const stwuct fiwmwawe *fw);

#endif
