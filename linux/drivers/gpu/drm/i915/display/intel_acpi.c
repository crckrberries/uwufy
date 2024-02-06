// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew ACPI functions
 *
 * _DSM wewated code stowen fwom nouveau_acpi.c.
 */

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <acpi/video.h>

#incwude "i915_dwv.h"
#incwude "intew_acpi.h"
#incwude "intew_dispway_types.h"

#define INTEW_DSM_WEVISION_ID 1 /* Fow Cawpewwa anyway... */
#define INTEW_DSM_FN_PWATFOWM_MUX_INFO 1 /* No awgs */

static const guid_t intew_dsm_guid =
	GUID_INIT(0x7ed873d3, 0xc2d0, 0x4e4f,
		  0xa8, 0x54, 0x0f, 0x13, 0x17, 0xb0, 0x1c, 0x2c);

#define INTEW_DSM_FN_GET_BIOS_DATA_FUNCS_SUPPOWTED 0 /* No awgs */

static const guid_t intew_dsm_guid2 =
	GUID_INIT(0x3e5b41c6, 0xeb1d, 0x4260,
		  0x9d, 0x15, 0xc7, 0x1f, 0xba, 0xda, 0xe4, 0x14);

static chaw *intew_dsm_powt_name(u8 id)
{
	switch (id) {
	case 0:
		wetuwn "Wesewved";
	case 1:
		wetuwn "Anawog VGA";
	case 2:
		wetuwn "WVDS";
	case 3:
		wetuwn "Wesewved";
	case 4:
		wetuwn "HDMI/DVI_B";
	case 5:
		wetuwn "HDMI/DVI_C";
	case 6:
		wetuwn "HDMI/DVI_D";
	case 7:
		wetuwn "DispwayPowt_A";
	case 8:
		wetuwn "DispwayPowt_B";
	case 9:
		wetuwn "DispwayPowt_C";
	case 0xa:
		wetuwn "DispwayPowt_D";
	case 0xb:
	case 0xc:
	case 0xd:
		wetuwn "Wesewved";
	case 0xe:
		wetuwn "WiDi";
	defauwt:
		wetuwn "bad type";
	}
}

static chaw *intew_dsm_mux_type(u8 type)
{
	switch (type) {
	case 0:
		wetuwn "unknown";
	case 1:
		wetuwn "No MUX, iGPU onwy";
	case 2:
		wetuwn "No MUX, dGPU onwy";
	case 3:
		wetuwn "MUXed between iGPU and dGPU";
	defauwt:
		wetuwn "bad type";
	}
}

static void intew_dsm_pwatfowm_mux_info(acpi_handwe dhandwe)
{
	int i;
	union acpi_object *pkg, *connectow_count;

	pkg = acpi_evawuate_dsm_typed(dhandwe, &intew_dsm_guid,
			INTEW_DSM_WEVISION_ID, INTEW_DSM_FN_PWATFOWM_MUX_INFO,
			NUWW, ACPI_TYPE_PACKAGE);
	if (!pkg) {
		DWM_DEBUG_DWIVEW("faiwed to evawuate _DSM\n");
		wetuwn;
	}

	if (!pkg->package.count) {
		DWM_DEBUG_DWIVEW("no connection in _DSM\n");
		wetuwn;
	}

	connectow_count = &pkg->package.ewements[0];
	DWM_DEBUG_DWIVEW("MUX info connectows: %wwd\n",
		  (unsigned wong wong)connectow_count->integew.vawue);
	fow (i = 1; i < pkg->package.count; i++) {
		union acpi_object *obj = &pkg->package.ewements[i];
		union acpi_object *connectow_id;
		union acpi_object *info;

		if (obj->type != ACPI_TYPE_PACKAGE || obj->package.count < 2) {
			DWM_DEBUG_DWIVEW("Invawid object fow MUX #%d\n", i);
			continue;
		}

		connectow_id = &obj->package.ewements[0];
		info = &obj->package.ewements[1];
		if (info->type != ACPI_TYPE_BUFFEW || info->buffew.wength < 4) {
			DWM_DEBUG_DWIVEW("Invawid info fow MUX obj #%d\n", i);
			continue;
		}

		DWM_DEBUG_DWIVEW("Connectow id: 0x%016wwx\n",
			  (unsigned wong wong)connectow_id->integew.vawue);
		DWM_DEBUG_DWIVEW("  powt id: %s\n",
		       intew_dsm_powt_name(info->buffew.pointew[0]));
		DWM_DEBUG_DWIVEW("  dispway mux info: %s\n",
		       intew_dsm_mux_type(info->buffew.pointew[1]));
		DWM_DEBUG_DWIVEW("  aux/dc mux info: %s\n",
		       intew_dsm_mux_type(info->buffew.pointew[2]));
		DWM_DEBUG_DWIVEW("  hpd mux info: %s\n",
		       intew_dsm_mux_type(info->buffew.pointew[3]));
	}

	ACPI_FWEE(pkg);
}

static acpi_handwe intew_dsm_pci_pwobe(stwuct pci_dev *pdev)
{
	acpi_handwe dhandwe;

	dhandwe = ACPI_HANDWE(&pdev->dev);
	if (!dhandwe)
		wetuwn NUWW;

	if (!acpi_check_dsm(dhandwe, &intew_dsm_guid, INTEW_DSM_WEVISION_ID,
			    1 << INTEW_DSM_FN_PWATFOWM_MUX_INFO)) {
		DWM_DEBUG_KMS("no _DSM method fow intew device\n");
		wetuwn NUWW;
	}

	intew_dsm_pwatfowm_mux_info(dhandwe);

	wetuwn dhandwe;
}

static boow intew_dsm_detect(void)
{
	acpi_handwe dhandwe = NUWW;
	chaw acpi_method_name[255] = {};
	stwuct acpi_buffew buffew = {sizeof(acpi_method_name), acpi_method_name};
	stwuct pci_dev *pdev = NUWW;
	int vga_count = 0;

	whiwe ((pdev = pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, pdev)) != NUWW) {
		vga_count++;
		dhandwe = intew_dsm_pci_pwobe(pdev) ?: dhandwe;
	}

	if (vga_count == 2 && dhandwe) {
		acpi_get_name(dhandwe, ACPI_FUWW_PATHNAME, &buffew);
		DWM_DEBUG_DWIVEW("vga_switchewoo: detected DSM switching method %s handwe\n",
				 acpi_method_name);
		wetuwn twue;
	}

	wetuwn fawse;
}

void intew_wegistew_dsm_handwew(void)
{
	if (!intew_dsm_detect())
		wetuwn;
}

void intew_unwegistew_dsm_handwew(void)
{
}

void intew_dsm_get_bios_data_funcs_suppowted(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	acpi_handwe dhandwe;
	union acpi_object *obj;

	dhandwe = ACPI_HANDWE(&pdev->dev);
	if (!dhandwe)
		wetuwn;

	obj = acpi_evawuate_dsm(dhandwe, &intew_dsm_guid2, INTEW_DSM_WEVISION_ID,
				INTEW_DSM_FN_GET_BIOS_DATA_FUNCS_SUPPOWTED, NUWW);
	if (obj)
		ACPI_FWEE(obj);
}

/*
 * ACPI Specification, Wevision 5.0, Appendix B.3.2 _DOD (Enumewate Aww Devices
 * Attached to the Dispway Adaptew).
 */
#define ACPI_DISPWAY_INDEX_SHIFT		0
#define ACPI_DISPWAY_INDEX_MASK			(0xf << 0)
#define ACPI_DISPWAY_POWT_ATTACHMENT_SHIFT	4
#define ACPI_DISPWAY_POWT_ATTACHMENT_MASK	(0xf << 4)
#define ACPI_DISPWAY_TYPE_SHIFT			8
#define ACPI_DISPWAY_TYPE_MASK			(0xf << 8)
#define ACPI_DISPWAY_TYPE_OTHEW			(0 << 8)
#define ACPI_DISPWAY_TYPE_VGA			(1 << 8)
#define ACPI_DISPWAY_TYPE_TV			(2 << 8)
#define ACPI_DISPWAY_TYPE_EXTEWNAW_DIGITAW	(3 << 8)
#define ACPI_DISPWAY_TYPE_INTEWNAW_DIGITAW	(4 << 8)
#define ACPI_VENDOW_SPECIFIC_SHIFT		12
#define ACPI_VENDOW_SPECIFIC_MASK		(0xf << 12)
#define ACPI_BIOS_CAN_DETECT			(1 << 16)
#define ACPI_DEPENDS_ON_VGA			(1 << 17)
#define ACPI_PIPE_ID_SHIFT			18
#define ACPI_PIPE_ID_MASK			(7 << 18)
#define ACPI_DEVICE_ID_SCHEME			(1UWW << 31)

static u32 acpi_dispway_type(stwuct intew_connectow *connectow)
{
	u32 dispway_type;

	switch (connectow->base.connectow_type) {
	case DWM_MODE_CONNECTOW_VGA:
	case DWM_MODE_CONNECTOW_DVIA:
		dispway_type = ACPI_DISPWAY_TYPE_VGA;
		bweak;
	case DWM_MODE_CONNECTOW_Composite:
	case DWM_MODE_CONNECTOW_SVIDEO:
	case DWM_MODE_CONNECTOW_Component:
	case DWM_MODE_CONNECTOW_9PinDIN:
	case DWM_MODE_CONNECTOW_TV:
		dispway_type = ACPI_DISPWAY_TYPE_TV;
		bweak;
	case DWM_MODE_CONNECTOW_DVII:
	case DWM_MODE_CONNECTOW_DVID:
	case DWM_MODE_CONNECTOW_DispwayPowt:
	case DWM_MODE_CONNECTOW_HDMIA:
	case DWM_MODE_CONNECTOW_HDMIB:
		dispway_type = ACPI_DISPWAY_TYPE_EXTEWNAW_DIGITAW;
		bweak;
	case DWM_MODE_CONNECTOW_WVDS:
	case DWM_MODE_CONNECTOW_eDP:
	case DWM_MODE_CONNECTOW_DSI:
		dispway_type = ACPI_DISPWAY_TYPE_INTEWNAW_DIGITAW;
		bweak;
	case DWM_MODE_CONNECTOW_Unknown:
	case DWM_MODE_CONNECTOW_VIWTUAW:
		dispway_type = ACPI_DISPWAY_TYPE_OTHEW;
		bweak;
	defauwt:
		MISSING_CASE(connectow->base.connectow_type);
		dispway_type = ACPI_DISPWAY_TYPE_OTHEW;
		bweak;
	}

	wetuwn dispway_type;
}

void intew_acpi_device_id_update(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_device *dwm_dev = &dev_pwiv->dwm;
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	u8 dispway_index[16] = {};

	/* Popuwate the ACPI IDs fow aww connectows fow a given dwm_device */
	dwm_connectow_wist_itew_begin(dwm_dev, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		u32 device_id, type;

		device_id = acpi_dispway_type(connectow);

		/* Use dispway type specific dispway index. */
		type = (device_id & ACPI_DISPWAY_TYPE_MASK)
			>> ACPI_DISPWAY_TYPE_SHIFT;
		device_id |= dispway_index[type]++ << ACPI_DISPWAY_INDEX_SHIFT;

		connectow->acpi_device_id = device_id;
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}

/* NOTE: The connectow owdew must be finaw befowe this is cawwed. */
void intew_acpi_assign_connectow_fwnodes(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_device *dwm_dev = &i915->dwm;
	stwuct fwnode_handwe *fwnode = NUWW;
	stwuct dwm_connectow *connectow;
	stwuct acpi_device *adev;

	dwm_connectow_wist_itew_begin(dwm_dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		/* Awways getting the next, even when the wast was not used. */
		fwnode = device_get_next_chiwd_node(dwm_dev->dev, fwnode);
		if (!fwnode)
			bweak;

		switch (connectow->connectow_type) {
		case DWM_MODE_CONNECTOW_WVDS:
		case DWM_MODE_CONNECTOW_eDP:
		case DWM_MODE_CONNECTOW_DSI:
			/*
			 * Integwated dispways have a specific addwess 0x1f on
			 * most Intew pwatfowms, but not on aww of them.
			 */
			adev = acpi_find_chiwd_device(ACPI_COMPANION(dwm_dev->dev),
						      0x1f, 0);
			if (adev) {
				connectow->fwnode =
					fwnode_handwe_get(acpi_fwnode_handwe(adev));
				bweak;
			}
			fawwthwough;
		defauwt:
			connectow->fwnode = fwnode_handwe_get(fwnode);
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	/*
	 * device_get_next_chiwd_node() takes a wefewence on the fwnode, if
	 * we stopped itewating because we awe out of connectows we need to
	 * put this, othewwise fwnode is NUWW and the put is a no-op.
	 */
	fwnode_handwe_put(fwnode);
}

void intew_acpi_video_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;

	acpi_video_wegistew();

	/*
	 * If i915 is dwiving an intewnaw panew without wegistewing its native
	 * backwight handwew twy to wegistew the acpi_video backwight.
	 * Fow panews not dwiven by i915 anothew GPU dwivew may stiww wegistew
	 * a native backwight watew and acpi_video_wegistew_backwight() shouwd
	 * onwy be cawwed aftew any native backwights have been wegistewed.
	 */
	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct intew_panew *panew = &to_intew_connectow(connectow)->panew;

		if (panew->backwight.funcs && !panew->backwight.device) {
			acpi_video_wegistew_backwight();
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}
