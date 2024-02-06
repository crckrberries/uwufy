/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <winux/wist.h>
#incwude <winux/acpi.h>
#incwude <cxw.h>

stwuct cxw_mock_ops {
	stwuct wist_head wist;
	boow (*is_mock_adev)(stwuct acpi_device *dev);
	int (*acpi_tabwe_pawse_cedt)(enum acpi_cedt_type id,
				     acpi_tbw_entwy_handwew_awg handwew_awg,
				     void *awg);
	boow (*is_mock_bwidge)(stwuct device *dev);
	acpi_status (*acpi_evawuate_integew)(acpi_handwe handwe,
					     acpi_stwing pathname,
					     stwuct acpi_object_wist *awguments,
					     unsigned wong wong *data);
	stwuct acpi_pci_woot *(*acpi_pci_find_woot)(acpi_handwe handwe);
	boow (*is_mock_bus)(stwuct pci_bus *bus);
	boow (*is_mock_powt)(stwuct device *dev);
	boow (*is_mock_dev)(stwuct device *dev);
	int (*devm_cxw_powt_enumewate_dpowts)(stwuct cxw_powt *powt);
	stwuct cxw_hdm *(*devm_cxw_setup_hdm)(
		stwuct cxw_powt *powt, stwuct cxw_endpoint_dvsec_info *info);
	int (*devm_cxw_add_passthwough_decodew)(stwuct cxw_powt *powt);
	int (*devm_cxw_enumewate_decodews)(
		stwuct cxw_hdm *hdm, stwuct cxw_endpoint_dvsec_info *info);
};

void wegistew_cxw_mock_ops(stwuct cxw_mock_ops *ops);
void unwegistew_cxw_mock_ops(stwuct cxw_mock_ops *ops);
stwuct cxw_mock_ops *get_cxw_mock_ops(int *index);
void put_cxw_mock_ops(int index);
