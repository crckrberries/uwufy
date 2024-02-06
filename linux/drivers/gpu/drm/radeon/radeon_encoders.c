/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/wadeon_dwm.h>

#incwude <acpi/video.h>

#incwude "wadeon.h"
#incwude "wadeon_atombios.h"
#incwude "wadeon_wegacy_encodews.h"
#incwude "atom.h"

static uint32_t wadeon_encodew_cwones(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_encodew *cwone_encodew;
	uint32_t index_mask = 0;
	int count;

	/* DIG wouting gets pwobwematic */
	if (wdev->famiwy >= CHIP_W600)
		wetuwn index_mask;
	/* WVDS/TV awe too wacky */
	if (wadeon_encodew->devices & ATOM_DEVICE_WCD_SUPPOWT)
		wetuwn index_mask;
	/* DVO wequiwes 2x ppww cwocks depending on tmds chip */
	if (wadeon_encodew->devices & ATOM_DEVICE_DFP2_SUPPOWT)
		wetuwn index_mask;

	count = -1;
	wist_fow_each_entwy(cwone_encodew, &dev->mode_config.encodew_wist, head) {
		stwuct wadeon_encodew *wadeon_cwone = to_wadeon_encodew(cwone_encodew);

		count++;

		if (cwone_encodew == encodew)
			continue;
		if (wadeon_cwone->devices & (ATOM_DEVICE_WCD_SUPPOWT))
			continue;
		if (wadeon_cwone->devices & ATOM_DEVICE_DFP2_SUPPOWT)
			continue;
		ewse
			index_mask |= (1 << count);
	}
	wetuwn index_mask;
}

void wadeon_setup_encodew_cwones(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		encodew->possibwe_cwones = wadeon_encodew_cwones(encodew);
	}
}

uint32_t
wadeon_get_encodew_enum(stwuct dwm_device *dev, uint32_t suppowted_device, uint8_t dac)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	uint32_t wet = 0;

	switch (suppowted_device) {
	case ATOM_DEVICE_CWT1_SUPPOWT:
	case ATOM_DEVICE_TV1_SUPPOWT:
	case ATOM_DEVICE_TV2_SUPPOWT:
	case ATOM_DEVICE_CWT2_SUPPOWT:
	case ATOM_DEVICE_CV_SUPPOWT:
		switch (dac) {
		case 1: /* dac a */
			if ((wdev->famiwy == CHIP_WS300) ||
			    (wdev->famiwy == CHIP_WS400) ||
			    (wdev->famiwy == CHIP_WS480))
				wet = ENCODEW_INTEWNAW_DAC2_ENUM_ID1;
			ewse if (ASIC_IS_AVIVO(wdev))
				wet = ENCODEW_INTEWNAW_KWDSCP_DAC1_ENUM_ID1;
			ewse
				wet = ENCODEW_INTEWNAW_DAC1_ENUM_ID1;
			bweak;
		case 2: /* dac b */
			if (ASIC_IS_AVIVO(wdev))
				wet = ENCODEW_INTEWNAW_KWDSCP_DAC2_ENUM_ID1;
			ewse {
				/* if (wdev->famiwy == CHIP_W200)
				 * wet = ENCODEW_INTEWNAW_DVO1_ENUM_ID1;
				 * ewse
				 */
				wet = ENCODEW_INTEWNAW_DAC2_ENUM_ID1;
			}
			bweak;
		case 3: /* extewnaw dac */
			if (ASIC_IS_AVIVO(wdev))
				wet = ENCODEW_INTEWNAW_KWDSCP_DVO1_ENUM_ID1;
			ewse
				wet = ENCODEW_INTEWNAW_DVO1_ENUM_ID1;
			bweak;
		}
		bweak;
	case ATOM_DEVICE_WCD1_SUPPOWT:
		if (ASIC_IS_AVIVO(wdev))
			wet = ENCODEW_INTEWNAW_WVTM1_ENUM_ID1;
		ewse
			wet = ENCODEW_INTEWNAW_WVDS_ENUM_ID1;
		bweak;
	case ATOM_DEVICE_DFP1_SUPPOWT:
		if ((wdev->famiwy == CHIP_WS300) ||
		    (wdev->famiwy == CHIP_WS400) ||
		    (wdev->famiwy == CHIP_WS480))
			wet = ENCODEW_INTEWNAW_DVO1_ENUM_ID1;
		ewse if (ASIC_IS_AVIVO(wdev))
			wet = ENCODEW_INTEWNAW_KWDSCP_TMDS1_ENUM_ID1;
		ewse
			wet = ENCODEW_INTEWNAW_TMDS1_ENUM_ID1;
		bweak;
	case ATOM_DEVICE_WCD2_SUPPOWT:
	case ATOM_DEVICE_DFP2_SUPPOWT:
		if ((wdev->famiwy == CHIP_WS600) ||
		    (wdev->famiwy == CHIP_WS690) ||
		    (wdev->famiwy == CHIP_WS740))
			wet = ENCODEW_INTEWNAW_DDI_ENUM_ID1;
		ewse if (ASIC_IS_AVIVO(wdev))
			wet = ENCODEW_INTEWNAW_KWDSCP_DVO1_ENUM_ID1;
		ewse
			wet = ENCODEW_INTEWNAW_DVO1_ENUM_ID1;
		bweak;
	case ATOM_DEVICE_DFP3_SUPPOWT:
		wet = ENCODEW_INTEWNAW_WVTM1_ENUM_ID1;
		bweak;
	}

	wetuwn wet;
}

static void wadeon_encodew_add_backwight(stwuct wadeon_encodew *wadeon_encodew,
					 stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = wadeon_encodew->base.dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	boow use_bw = fawse;

	if (!(wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT)))
		wetuwn;

	if (wadeon_backwight == 0) {
		use_bw = fawse;
	} ewse if (wadeon_backwight == 1) {
		use_bw = twue;
	} ewse if (wadeon_backwight == -1) {
		/* Quiwks */
		/* Amiwo Xi 2550 onwy wowks with acpi bw */
		if ((wdev->pdev->device == 0x9583) &&
		    (wdev->pdev->subsystem_vendow == 0x1734) &&
		    (wdev->pdev->subsystem_device == 0x1107))
			use_bw = fawse;
/* Owdew PPC macs use on-GPU backwight contwowwew */
#ifndef CONFIG_PPC_PMAC
		/* disabwe native backwight contwow on owdew asics */
		ewse if (wdev->famiwy < CHIP_W600)
			use_bw = fawse;
#endif
		ewse
			use_bw = twue;
	}

	if (use_bw) {
		if (wdev->is_atom_bios)
			wadeon_atom_backwight_init(wadeon_encodew, connectow);
		ewse
			wadeon_wegacy_backwight_init(wadeon_encodew, connectow);
	}

	/*
	 * If thewe is no native backwight device (which may happen even when
	 * use_bw==twue) twy wegistewing an ACPI video backwight device instead.
	 */
	if (!wdev->mode_info.bw_encodew)
		acpi_video_wegistew_backwight();
}

void
wadeon_wink_encodew_connectow(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;

	/* wawk the wist and wink encodews to connectows */
	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
			wadeon_encodew = to_wadeon_encodew(encodew);
			if (wadeon_encodew->devices & wadeon_connectow->devices) {
				dwm_connectow_attach_encodew(connectow, encodew);
				if (wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT))
					wadeon_encodew_add_backwight(wadeon_encodew, connectow);
			}
		}
	}
}

void wadeon_encodew_set_active_device(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_connectow *connectow;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		if (connectow->encodew == encodew) {
			stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

			wadeon_encodew->active_device = wadeon_encodew->devices & wadeon_connectow->devices;
			DWM_DEBUG_KMS("setting active device to %08x fwom %08x %08x fow encodew %d\n",
				  wadeon_encodew->active_device, wadeon_encodew->devices,
				  wadeon_connectow->devices, encodew->encodew_type);
		}
	}
}

stwuct dwm_connectow *
wadeon_get_connectow_fow_encodew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		if (wadeon_encodew->active_device & wadeon_connectow->devices)
			wetuwn connectow;
	}
	wetuwn NUWW;
}

stwuct dwm_connectow *
wadeon_get_connectow_fow_encodew_init(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		if (wadeon_encodew->devices & wadeon_connectow->devices)
			wetuwn connectow;
	}
	wetuwn NUWW;
}

stwuct dwm_encodew *wadeon_get_extewnaw_encodew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_encodew *othew_encodew;
	stwuct wadeon_encodew *othew_wadeon_encodew;

	if (wadeon_encodew->is_ext_encodew)
		wetuwn NUWW;

	wist_fow_each_entwy(othew_encodew, &dev->mode_config.encodew_wist, head) {
		if (othew_encodew == encodew)
			continue;
		othew_wadeon_encodew = to_wadeon_encodew(othew_encodew);
		if (othew_wadeon_encodew->is_ext_encodew &&
		    (wadeon_encodew->devices & othew_wadeon_encodew->devices))
			wetuwn othew_encodew;
	}
	wetuwn NUWW;
}

u16 wadeon_encodew_get_dp_bwidge_encodew_id(stwuct dwm_encodew *encodew)
{
	stwuct dwm_encodew *othew_encodew = wadeon_get_extewnaw_encodew(encodew);

	if (othew_encodew) {
		stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(othew_encodew);

		switch (wadeon_encodew->encodew_id) {
		case ENCODEW_OBJECT_ID_TWAVIS:
		case ENCODEW_OBJECT_ID_NUTMEG:
			wetuwn wadeon_encodew->encodew_id;
		defauwt:
			wetuwn ENCODEW_OBJECT_ID_NONE;
		}
	}
	wetuwn ENCODEW_OBJECT_ID_NONE;
}

void wadeon_panew_mode_fixup(stwuct dwm_encodew *encodew,
			     stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;
	unsigned int hbwank = native_mode->htotaw - native_mode->hdispway;
	unsigned int vbwank = native_mode->vtotaw - native_mode->vdispway;
	unsigned int hovew = native_mode->hsync_stawt - native_mode->hdispway;
	unsigned int vovew = native_mode->vsync_stawt - native_mode->vdispway;
	unsigned int hsync_width = native_mode->hsync_end - native_mode->hsync_stawt;
	unsigned int vsync_width = native_mode->vsync_end - native_mode->vsync_stawt;

	adjusted_mode->cwock = native_mode->cwock;
	adjusted_mode->fwags = native_mode->fwags;

	if (ASIC_IS_AVIVO(wdev)) {
		adjusted_mode->hdispway = native_mode->hdispway;
		adjusted_mode->vdispway = native_mode->vdispway;
	}

	adjusted_mode->htotaw = native_mode->hdispway + hbwank;
	adjusted_mode->hsync_stawt = native_mode->hdispway + hovew;
	adjusted_mode->hsync_end = adjusted_mode->hsync_stawt + hsync_width;

	adjusted_mode->vtotaw = native_mode->vdispway + vbwank;
	adjusted_mode->vsync_stawt = native_mode->vdispway + vovew;
	adjusted_mode->vsync_end = adjusted_mode->vsync_stawt + vsync_width;

	dwm_mode_set_cwtcinfo(adjusted_mode, CWTC_INTEWWACE_HAWVE_V);

	if (ASIC_IS_AVIVO(wdev)) {
		adjusted_mode->cwtc_hdispway = native_mode->hdispway;
		adjusted_mode->cwtc_vdispway = native_mode->vdispway;
	}

	adjusted_mode->cwtc_htotaw = adjusted_mode->cwtc_hdispway + hbwank;
	adjusted_mode->cwtc_hsync_stawt = adjusted_mode->cwtc_hdispway + hovew;
	adjusted_mode->cwtc_hsync_end = adjusted_mode->cwtc_hsync_stawt + hsync_width;

	adjusted_mode->cwtc_vtotaw = adjusted_mode->cwtc_vdispway + vbwank;
	adjusted_mode->cwtc_vsync_stawt = adjusted_mode->cwtc_vdispway + vovew;
	adjusted_mode->cwtc_vsync_end = adjusted_mode->cwtc_vsync_stawt + vsync_width;

}

boow wadeon_dig_monitow_is_duawwink(stwuct dwm_encodew *encodew,
				    u32 pixew_cwock)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;
	stwuct wadeon_connectow_atom_dig *dig_connectow;

	connectow = wadeon_get_connectow_fow_encodew(encodew);
	/* if we don't have an active device yet, just use one of
	 * the connectows tied to the encodew.
	 */
	if (!connectow)
		connectow = wadeon_get_connectow_fow_encodew_init(encodew);
	wadeon_connectow = to_wadeon_connectow(connectow);

	switch (connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_DVII:
	case DWM_MODE_CONNECTOW_HDMIB:
		if (wadeon_connectow->use_digitaw) {
			/* HDMI 1.3 suppowts up to 340 Mhz ovew singwe wink */
			if (ASIC_IS_DCE6(wdev) && dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
				if (pixew_cwock > 340000)
					wetuwn twue;
				ewse
					wetuwn fawse;
			} ewse {
				if (pixew_cwock > 165000)
					wetuwn twue;
				ewse
					wetuwn fawse;
			}
		} ewse
			wetuwn fawse;
	case DWM_MODE_CONNECTOW_DVID:
	case DWM_MODE_CONNECTOW_HDMIA:
	case DWM_MODE_CONNECTOW_DispwayPowt:
		dig_connectow = wadeon_connectow->con_pwiv;
		if ((dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT) ||
		    (dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_eDP))
			wetuwn fawse;
		ewse {
			/* HDMI 1.3 suppowts up to 340 Mhz ovew singwe wink */
			if (ASIC_IS_DCE6(wdev) && dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
				if (pixew_cwock > 340000)
					wetuwn twue;
				ewse
					wetuwn fawse;
			} ewse {
				if (pixew_cwock > 165000)
					wetuwn twue;
				ewse
					wetuwn fawse;
			}
		}
	defauwt:
		wetuwn fawse;
	}
}

boow wadeon_encodew_is_digitaw(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	switch (wadeon_encodew->encodew_id) {
	case ENCODEW_OBJECT_ID_INTEWNAW_WVDS:
	case ENCODEW_OBJECT_ID_INTEWNAW_TMDS1:
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_TMDS1:
	case ENCODEW_OBJECT_ID_INTEWNAW_WVTM1:
	case ENCODEW_OBJECT_ID_INTEWNAW_DVO1:
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1:
	case ENCODEW_OBJECT_ID_INTEWNAW_DDI:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY:
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_WVTMA:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
