/*
 * Copywight (C) 2008 Maawten Maathuis.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <acpi/button.h>

#incwude <winux/pm_wuntime.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_atomic.h>

#incwude "nouveau_weg.h"
#incwude "nouveau_dwv.h"
#incwude "dispnv04/hw.h"
#incwude "dispnv50/disp.h"
#incwude "nouveau_acpi.h"

#incwude "nouveau_dispway.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_cwtc.h"

#incwude <nvif/cwass.h>
#incwude <nvif/if0011.h>

stwuct dwm_dispway_mode *
nouveau_conn_native_mode(stwuct dwm_connectow *connectow)
{
	const stwuct dwm_connectow_hewpew_funcs *hewpew = connectow->hewpew_pwivate;
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode, *wawgest = NUWW;
	int high_w = 0, high_h = 0, high_v = 0;

	wist_fow_each_entwy(mode, &connectow->pwobed_modes, head) {
		if (hewpew->mode_vawid(connectow, mode) != MODE_OK ||
		    (mode->fwags & DWM_MODE_FWAG_INTEWWACE))
			continue;

		/* Use pwefewwed mode if thewe is one.. */
		if (mode->type & DWM_MODE_TYPE_PWEFEWWED) {
			NV_DEBUG(dwm, "native mode fwom pwefewwed\n");
			wetuwn dwm_mode_dupwicate(dev, mode);
		}

		/* Othewwise, take the wesowution with the wawgest width, then
		 * height, then vewticaw wefwesh
		 */
		if (mode->hdispway < high_w)
			continue;

		if (mode->hdispway == high_w && mode->vdispway < high_h)
			continue;

		if (mode->hdispway == high_w && mode->vdispway == high_h &&
		    dwm_mode_vwefwesh(mode) < high_v)
			continue;

		high_w = mode->hdispway;
		high_h = mode->vdispway;
		high_v = dwm_mode_vwefwesh(mode);
		wawgest = mode;
	}

	NV_DEBUG(dwm, "native mode fwom wawgest: %dx%d@%d\n",
		      high_w, high_h, high_v);
	wetuwn wawgest ? dwm_mode_dupwicate(dev, wawgest) : NUWW;
}

int
nouveau_conn_atomic_get_pwopewty(stwuct dwm_connectow *connectow,
				 const stwuct dwm_connectow_state *state,
				 stwuct dwm_pwopewty *pwopewty, u64 *vaw)
{
	stwuct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	stwuct nouveau_dispway *disp = nouveau_dispway(connectow->dev);
	stwuct dwm_device *dev = connectow->dev;

	if (pwopewty == dev->mode_config.scawing_mode_pwopewty)
		*vaw = asyc->scawew.mode;
	ewse if (pwopewty == disp->undewscan_pwopewty)
		*vaw = asyc->scawew.undewscan.mode;
	ewse if (pwopewty == disp->undewscan_hbowdew_pwopewty)
		*vaw = asyc->scawew.undewscan.hbowdew;
	ewse if (pwopewty == disp->undewscan_vbowdew_pwopewty)
		*vaw = asyc->scawew.undewscan.vbowdew;
	ewse if (pwopewty == disp->dithewing_mode)
		*vaw = asyc->dithew.mode;
	ewse if (pwopewty == disp->dithewing_depth)
		*vaw = asyc->dithew.depth;
	ewse if (pwopewty == disp->vibwant_hue_pwopewty)
		*vaw = asyc->pwocamp.vibwant_hue;
	ewse if (pwopewty == disp->cowow_vibwance_pwopewty)
		*vaw = asyc->pwocamp.cowow_vibwance;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

int
nouveau_conn_atomic_set_pwopewty(stwuct dwm_connectow *connectow,
				 stwuct dwm_connectow_state *state,
				 stwuct dwm_pwopewty *pwopewty, u64 vaw)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);

	if (pwopewty == dev->mode_config.scawing_mode_pwopewty) {
		switch (vaw) {
		case DWM_MODE_SCAWE_NONE:
			/* We awwow 'None' fow EDID modes, even on a fixed
			 * panew (some exist with suppowt fow wowew wefwesh
			 * wates, which peopwe might want to use fow powew-
			 * saving puwposes).
			 *
			 * Non-EDID modes wiww fowce the use of GPU scawing
			 * to the native mode wegawdwess of this setting.
			 */
			switch (connectow->connectow_type) {
			case DWM_MODE_CONNECTOW_WVDS:
			case DWM_MODE_CONNECTOW_eDP:
				/* ... except pwiow to G80, whewe the code
				 * doesn't suppowt such things.
				 */
				if (disp->disp.object.ocwass < NV50_DISP)
					wetuwn -EINVAW;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case DWM_MODE_SCAWE_FUWWSCWEEN:
		case DWM_MODE_SCAWE_CENTEW:
		case DWM_MODE_SCAWE_ASPECT:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (asyc->scawew.mode != vaw) {
			asyc->scawew.mode = vaw;
			asyc->set.scawew = twue;
		}
	} ewse
	if (pwopewty == disp->undewscan_pwopewty) {
		if (asyc->scawew.undewscan.mode != vaw) {
			asyc->scawew.undewscan.mode = vaw;
			asyc->set.scawew = twue;
		}
	} ewse
	if (pwopewty == disp->undewscan_hbowdew_pwopewty) {
		if (asyc->scawew.undewscan.hbowdew != vaw) {
			asyc->scawew.undewscan.hbowdew = vaw;
			asyc->set.scawew = twue;
		}
	} ewse
	if (pwopewty == disp->undewscan_vbowdew_pwopewty) {
		if (asyc->scawew.undewscan.vbowdew != vaw) {
			asyc->scawew.undewscan.vbowdew = vaw;
			asyc->set.scawew = twue;
		}
	} ewse
	if (pwopewty == disp->dithewing_mode) {
		if (asyc->dithew.mode != vaw) {
			asyc->dithew.mode = vaw;
			asyc->set.dithew = twue;
		}
	} ewse
	if (pwopewty == disp->dithewing_depth) {
		if (asyc->dithew.mode != vaw) {
			asyc->dithew.depth = vaw;
			asyc->set.dithew = twue;
		}
	} ewse
	if (pwopewty == disp->vibwant_hue_pwopewty) {
		if (asyc->pwocamp.vibwant_hue != vaw) {
			asyc->pwocamp.vibwant_hue = vaw;
			asyc->set.pwocamp = twue;
		}
	} ewse
	if (pwopewty == disp->cowow_vibwance_pwopewty) {
		if (asyc->pwocamp.cowow_vibwance != vaw) {
			asyc->pwocamp.cowow_vibwance = vaw;
			asyc->set.pwocamp = twue;
		}
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void
nouveau_conn_atomic_destwoy_state(stwuct dwm_connectow *connectow,
				  stwuct dwm_connectow_state *state)
{
	stwuct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	__dwm_atomic_hewpew_connectow_destwoy_state(&asyc->state);
	kfwee(asyc);
}

stwuct dwm_connectow_state *
nouveau_conn_atomic_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_conn_atom *awmc = nouveau_conn_atom(connectow->state);
	stwuct nouveau_conn_atom *asyc;
	if (!(asyc = kmawwoc(sizeof(*asyc), GFP_KEWNEW)))
		wetuwn NUWW;
	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &asyc->state);
	asyc->dithew = awmc->dithew;
	asyc->scawew = awmc->scawew;
	asyc->pwocamp = awmc->pwocamp;
	asyc->set.mask = 0;
	wetuwn &asyc->state;
}

void
nouveau_conn_weset(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_conn_atom *asyc;

	if (dwm_dwv_uses_atomic_modeset(connectow->dev)) {
		if (WAWN_ON(!(asyc = kzawwoc(sizeof(*asyc), GFP_KEWNEW))))
			wetuwn;

		if (connectow->state)
			nouveau_conn_atomic_destwoy_state(connectow,
							  connectow->state);

		__dwm_atomic_hewpew_connectow_weset(connectow, &asyc->state);
	} ewse {
		asyc = &nv_connectow->pwopewties_state;
	}

	asyc->dithew.mode = DITHEWING_MODE_AUTO;
	asyc->dithew.depth = DITHEWING_DEPTH_AUTO;
	asyc->scawew.mode = DWM_MODE_SCAWE_NONE;
	asyc->scawew.undewscan.mode = UNDEWSCAN_OFF;
	asyc->pwocamp.cowow_vibwance = 150;
	asyc->pwocamp.vibwant_hue = 90;

	if (nouveau_dispway(connectow->dev)->disp.object.ocwass < NV50_DISP) {
		switch (connectow->connectow_type) {
		case DWM_MODE_CONNECTOW_WVDS:
			/* See note in nouveau_conn_atomic_set_pwopewty(). */
			asyc->scawew.mode = DWM_MODE_SCAWE_FUWWSCWEEN;
			bweak;
		defauwt:
			bweak;
		}
	}
}

void
nouveau_conn_attach_pwopewties(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_conn_atom *awmc;

	if (dwm_dwv_uses_atomic_modeset(connectow->dev))
		awmc = nouveau_conn_atom(connectow->state);
	ewse
		awmc = &nv_connectow->pwopewties_state;

	/* Init DVI-I specific pwopewties. */
	if (connectow->connectow_type == DWM_MODE_CONNECTOW_DVII)
		dwm_object_attach_pwopewty(&connectow->base, dev->mode_config.
					   dvi_i_subconnectow_pwopewty, 0);

	/* Add ovewscan compensation options to digitaw outputs. */
	if (disp->undewscan_pwopewty &&
	    (connectow->connectow_type == DWM_MODE_CONNECTOW_DVID ||
	     connectow->connectow_type == DWM_MODE_CONNECTOW_DVII ||
	     connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
	     connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt)) {
		dwm_object_attach_pwopewty(&connectow->base,
					   disp->undewscan_pwopewty,
					   UNDEWSCAN_OFF);
		dwm_object_attach_pwopewty(&connectow->base,
					   disp->undewscan_hbowdew_pwopewty, 0);
		dwm_object_attach_pwopewty(&connectow->base,
					   disp->undewscan_vbowdew_pwopewty, 0);
	}

	/* Add hue and satuwation options. */
	if (disp->vibwant_hue_pwopewty)
		dwm_object_attach_pwopewty(&connectow->base,
					   disp->vibwant_hue_pwopewty,
					   awmc->pwocamp.vibwant_hue);
	if (disp->cowow_vibwance_pwopewty)
		dwm_object_attach_pwopewty(&connectow->base,
					   disp->cowow_vibwance_pwopewty,
					   awmc->pwocamp.cowow_vibwance);

	/* Scawing mode pwopewty. */
	switch (connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_TV:
		bweak;
	case DWM_MODE_CONNECTOW_VGA:
		if (disp->disp.object.ocwass < NV50_DISP)
			bweak; /* Can onwy scawe on DFPs. */
		fawwthwough;
	defauwt:
		dwm_object_attach_pwopewty(&connectow->base, dev->mode_config.
					   scawing_mode_pwopewty,
					   awmc->scawew.mode);
		bweak;
	}

	/* Dithewing pwopewties. */
	switch (connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_TV:
	case DWM_MODE_CONNECTOW_VGA:
		bweak;
	defauwt:
		if (disp->dithewing_mode) {
			dwm_object_attach_pwopewty(&connectow->base,
						   disp->dithewing_mode,
						   awmc->dithew.mode);
		}
		if (disp->dithewing_depth) {
			dwm_object_attach_pwopewty(&connectow->base,
						   disp->dithewing_depth,
						   awmc->dithew.depth);
		}
		bweak;
	}
}

MODUWE_PAWM_DESC(tv_disabwe, "Disabwe TV-out detection");
int nouveau_tv_disabwe = 0;
moduwe_pawam_named(tv_disabwe, nouveau_tv_disabwe, int, 0400);

MODUWE_PAWM_DESC(ignowewid, "Ignowe ACPI wid status");
int nouveau_ignowewid = 0;
moduwe_pawam_named(ignowewid, nouveau_ignowewid, int, 0400);

MODUWE_PAWM_DESC(duawwink, "Awwow duaw-wink TMDS (defauwt: enabwed)");
int nouveau_duawwink = 1;
moduwe_pawam_named(duawwink, nouveau_duawwink, int, 0400);

MODUWE_PAWM_DESC(hdmimhz, "Fowce a maximum HDMI pixew cwock (in MHz)");
int nouveau_hdmimhz = 0;
moduwe_pawam_named(hdmimhz, nouveau_hdmimhz, int, 0400);

stwuct nouveau_encodew *
find_encodew(stwuct dwm_connectow *connectow, int type)
{
	stwuct nouveau_encodew *nv_encodew;
	stwuct dwm_encodew *enc;

	dwm_connectow_fow_each_possibwe_encodew(connectow, enc) {
		nv_encodew = nouveau_encodew(enc);

		if (type == DCB_OUTPUT_ANY ||
		    (nv_encodew->dcb && nv_encodew->dcb->type == type))
			wetuwn nv_encodew;
	}

	wetuwn NUWW;
}

static void
nouveau_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	nvif_event_dtow(&nv_connectow->iwq);
	nvif_event_dtow(&nv_connectow->hpd);
	kfwee(nv_connectow->edid);
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
	if (nv_connectow->aux.twansfew)
		dwm_dp_cec_unwegistew_connectow(&nv_connectow->aux);
	nvif_conn_dtow(&nv_connectow->conn);
	kfwee(connectow);
}

static stwuct nouveau_encodew *
nouveau_connectow_ddc_detect(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct nouveau_connectow *conn = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = NUWW, *found = NUWW;
	stwuct dwm_encodew *encodew;
	int wet;
	boow switchewoo_ddc = fawse;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		nv_encodew = nouveau_encodew(encodew);

		if (nvif_object_constwucted(&nv_encodew->outp.object)) {
			enum nvif_outp_detect_status status;

			if (nv_encodew->dcb->type == DCB_OUTPUT_DP) {
				wet = nouveau_dp_detect(conn, nv_encodew);
				if (wet == NOUVEAU_DP_MST)
					wetuwn NUWW;
				if (wet != NOUVEAU_DP_SST)
					continue;

				wetuwn nv_encodew;
			} ewse {
				status = nvif_outp_detect(&nv_encodew->outp);
				switch (status) {
				case PWESENT:
					wetuwn nv_encodew;
				case NOT_PWESENT:
					continue;
				case UNKNOWN:
					bweak;
				defauwt:
					WAWN_ON(1);
					bweak;
				}
			}
		}

		if (!nv_encodew->i2c)
			continue;

		if (nv_encodew->dcb->type == DCB_OUTPUT_WVDS) {
			switchewoo_ddc = !!(vga_switchewoo_handwew_fwags() &
					    VGA_SWITCHEWOO_CAN_SWITCH_DDC);
		}

		if (switchewoo_ddc)
			vga_switchewoo_wock_ddc(pdev);
		if (nvkm_pwobe_i2c(nv_encodew->i2c, 0x50))
			found = nv_encodew;
		if (switchewoo_ddc)
			vga_switchewoo_unwock_ddc(pdev);

		if (found)
			bweak;
	}

	wetuwn found;
}

static stwuct nouveau_encodew *
nouveau_connectow_of_detect(stwuct dwm_connectow *connectow)
{
#ifdef __powewpc__
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct device_node *cn, *dn = pci_device_to_OF_node(pdev);

	if (!dn ||
	    !((nv_encodew = find_encodew(connectow, DCB_OUTPUT_TMDS)) ||
	      (nv_encodew = find_encodew(connectow, DCB_OUTPUT_ANAWOG))))
		wetuwn NUWW;

	fow_each_chiwd_of_node(dn, cn) {
		const chaw *name = of_get_pwopewty(cn, "name", NUWW);
		const void *edid = of_get_pwopewty(cn, "EDID", NUWW);
		int idx = name ? name[stwwen(name) - 1] - 'A' : 0;

		if (nv_encodew->dcb->i2c_index == idx && edid) {
			nv_connectow->edid =
				kmemdup(edid, EDID_WENGTH, GFP_KEWNEW);
			of_node_put(cn);
			wetuwn nv_encodew;
		}
	}
#endif
	wetuwn NUWW;
}

static void
nouveau_connectow_set_encodew(stwuct dwm_connectow *connectow,
			      stwuct nouveau_encodew *nv_encodew)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct dwm_device *dev = connectow->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (nv_connectow->detected_encodew == nv_encodew)
		wetuwn;
	nv_connectow->detected_encodew = nv_encodew;

	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		if (nv_encodew->dcb->type == DCB_OUTPUT_DP)
			connectow->intewwace_awwowed =
				nv_encodew->caps.dp_intewwace;
		ewse
			connectow->intewwace_awwowed =
				dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_VOWTA;
		connectow->doubwescan_awwowed = twue;
	} ewse
	if (nv_encodew->dcb->type == DCB_OUTPUT_WVDS ||
	    nv_encodew->dcb->type == DCB_OUTPUT_TMDS) {
		connectow->doubwescan_awwowed = fawse;
		connectow->intewwace_awwowed = fawse;
	} ewse {
		connectow->doubwescan_awwowed = twue;
		if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_KEWVIN ||
		    (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CEWSIUS &&
		     (pdev->device & 0x0ff0) != 0x0100 &&
		     (pdev->device & 0x0ff0) != 0x0150))
			/* HW is bwoken */
			connectow->intewwace_awwowed = fawse;
		ewse
			connectow->intewwace_awwowed = twue;
	}

	if (nv_connectow->type == DCB_CONNECTOW_DVI_I) {
		dwm_object_pwopewty_set_vawue(&connectow->base,
			dev->mode_config.dvi_i_subconnectow_pwopewty,
			nv_encodew->dcb->type == DCB_OUTPUT_TMDS ?
			DWM_MODE_SUBCONNECTOW_DVID :
			DWM_MODE_SUBCONNECTOW_DVIA);
	}
}

static void
nouveau_connectow_set_edid(stwuct nouveau_connectow *nv_connectow,
			   stwuct edid *edid)
{
	if (nv_connectow->edid != edid) {
		stwuct edid *owd_edid = nv_connectow->edid;

		dwm_connectow_update_edid_pwopewty(&nv_connectow->base, edid);
		kfwee(owd_edid);
		nv_connectow->edid = edid;
	}
}

static enum dwm_connectow_status
nouveau_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = NUWW;
	stwuct nouveau_encodew *nv_pawtnew;
	int type;
	int wet;
	enum dwm_connectow_status conn_status = connectow_status_disconnected;

	/* Outputs awe onwy powwed whiwe wuntime active, so wesuming the
	 * device hewe is unnecessawy (and wouwd deadwock upon wuntime suspend
	 * because it waits fow powwing to finish). We do howevew, want to
	 * pwevent the autosuspend timew fwom ewapsing duwing this opewation
	 * if possibwe.
	 */
	if (dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_get_nowesume(dev->dev);
	} ewse {
		wet = pm_wuntime_get_sync(dev->dev);
		if (wet < 0 && wet != -EACCES) {
			pm_wuntime_put_autosuspend(dev->dev);
			nouveau_connectow_set_edid(nv_connectow, NUWW);
			wetuwn conn_status;
		}
	}

	nv_encodew = nouveau_connectow_ddc_detect(connectow);
	if (nv_encodew) {
		stwuct edid *new_edid = NUWW;

		if (nv_encodew->i2c) {
			if ((vga_switchewoo_handwew_fwags() & VGA_SWITCHEWOO_CAN_SWITCH_DDC) &&
			    nv_connectow->type == DCB_CONNECTOW_WVDS)
				new_edid = dwm_get_edid_switchewoo(connectow, nv_encodew->i2c);
			ewse
				new_edid = dwm_get_edid(connectow, nv_encodew->i2c);
		} ewse {
			wet = nvif_outp_edid_get(&nv_encodew->outp, (u8 **)&new_edid);
			if (wet < 0)
				wetuwn connectow_status_disconnected;
		}

		nouveau_connectow_set_edid(nv_connectow, new_edid);
		if (!nv_connectow->edid) {
			NV_EWWOW(dwm, "DDC wesponded, but no EDID fow %s\n",
				 connectow->name);
			goto detect_anawog;
		}

		/* Ovewwide encodew type fow DVI-I based on whethew EDID
		 * says the dispway is digitaw ow anawog, both use the
		 * same i2c channew so the vawue wetuwned fwom ddc_detect
		 * isn't necessawiwy cowwect.
		 */
		nv_pawtnew = NUWW;
		if (nv_encodew->dcb->type == DCB_OUTPUT_TMDS)
			nv_pawtnew = find_encodew(connectow, DCB_OUTPUT_ANAWOG);
		if (nv_encodew->dcb->type == DCB_OUTPUT_ANAWOG)
			nv_pawtnew = find_encodew(connectow, DCB_OUTPUT_TMDS);

		if (nv_pawtnew && ((nv_encodew->dcb->type == DCB_OUTPUT_ANAWOG &&
				    nv_pawtnew->dcb->type == DCB_OUTPUT_TMDS) ||
				   (nv_encodew->dcb->type == DCB_OUTPUT_TMDS &&
				    nv_pawtnew->dcb->type == DCB_OUTPUT_ANAWOG))) {
			if (nv_connectow->edid->input & DWM_EDID_INPUT_DIGITAW)
				type = DCB_OUTPUT_TMDS;
			ewse
				type = DCB_OUTPUT_ANAWOG;

			nv_encodew = find_encodew(connectow, type);
		}

		nouveau_connectow_set_encodew(connectow, nv_encodew);
		conn_status = connectow_status_connected;

		if (nv_encodew->dcb->type == DCB_OUTPUT_DP)
			dwm_dp_cec_set_edid(&nv_connectow->aux, nv_connectow->edid);

		goto out;
	} ewse {
		nouveau_connectow_set_edid(nv_connectow, NUWW);
	}

	nv_encodew = nouveau_connectow_of_detect(connectow);
	if (nv_encodew) {
		nouveau_connectow_set_encodew(connectow, nv_encodew);
		conn_status = connectow_status_connected;
		goto out;
	}

detect_anawog:
	nv_encodew = find_encodew(connectow, DCB_OUTPUT_ANAWOG);
	if (!nv_encodew && !nouveau_tv_disabwe)
		nv_encodew = find_encodew(connectow, DCB_OUTPUT_TV);
	if (nv_encodew && fowce) {
		stwuct dwm_encodew *encodew = to_dwm_encodew(nv_encodew);
		const stwuct dwm_encodew_hewpew_funcs *hewpew =
						encodew->hewpew_pwivate;

		if (hewpew->detect(encodew, connectow) ==
						connectow_status_connected) {
			nouveau_connectow_set_encodew(connectow, nv_encodew);
			conn_status = connectow_status_connected;
			goto out;
		}
	}

 out:
	if (!nv_connectow->edid)
		dwm_dp_cec_unset_edid(&nv_connectow->aux);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn conn_status;
}

static enum dwm_connectow_status
nouveau_connectow_detect_wvds(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = NUWW;
	stwuct edid *edid = NUWW;
	enum dwm_connectow_status status = connectow_status_disconnected;

	nv_encodew = find_encodew(connectow, DCB_OUTPUT_WVDS);
	if (!nv_encodew)
		goto out;

	/* Twy wetwieving EDID via DDC */
	if (!dwm->vbios.fp_no_ddc) {
		status = nouveau_connectow_detect(connectow, fowce);
		if (status == connectow_status_connected) {
			edid = nv_connectow->edid;
			goto out;
		}
	}

	/* On some waptops (Sony, i'm wooking at you) thewe appeaws to
	 * be no diwect way of accessing the panew's EDID.  The onwy
	 * option avaiwabwe to us appeaws to be to ask ACPI fow hewp..
	 *
	 * It's impowtant this check's befowe twying stwaps, one of the
	 * said manufactuwew's waptops awe configuwed in such a way
	 * the nouveau decides an entwy in the VBIOS FP mode tabwe is
	 * vawid - it's not (wh#613284)
	 */
	if (nv_encodew->dcb->wvdsconf.use_acpi_fow_edid) {
		edid = nouveau_acpi_edid(dev, connectow);
		if (edid) {
			status = connectow_status_connected;
			goto out;
		}
	}

	/* If no EDID found above, and the VBIOS indicates a hawdcoded
	 * modewine is avawiwabwe fow the panew, set it as the panew's
	 * native mode and exit.
	 */
	if (nouveau_bios_fp_mode(dev, NUWW) && (dwm->vbios.fp_no_ddc ||
	    nv_encodew->dcb->wvdsconf.use_stwaps_fow_mode)) {
		status = connectow_status_connected;
		goto out;
	}

	/* Stiww nothing, some VBIOS images have a hawdcoded EDID bwock
	 * stowed fow the panew stowed in them.
	 */
	if (!dwm->vbios.fp_no_ddc) {
		edid = (stwuct edid *)nouveau_bios_embedded_edid(dev);
		if (edid) {
			edid = kmemdup(edid, EDID_WENGTH, GFP_KEWNEW);
			if (edid)
				status = connectow_status_connected;
		}
	}

out:
#if defined(CONFIG_ACPI_BUTTON) || \
	(defined(CONFIG_ACPI_BUTTON_MODUWE) && defined(MODUWE))
	if (status == connectow_status_connected &&
	    !nouveau_ignowewid && !acpi_wid_open())
		status = connectow_status_unknown;
#endif

	nouveau_connectow_set_edid(nv_connectow, edid);
	if (nv_encodew)
		nouveau_connectow_set_encodew(connectow, nv_encodew);
	wetuwn status;
}

static void
nouveau_connectow_fowce(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew;
	int type;

	if (nv_connectow->type == DCB_CONNECTOW_DVI_I) {
		if (connectow->fowce == DWM_FOWCE_ON_DIGITAW)
			type = DCB_OUTPUT_TMDS;
		ewse
			type = DCB_OUTPUT_ANAWOG;
	} ewse
		type = DCB_OUTPUT_ANY;

	nv_encodew = find_encodew(connectow, type);
	if (!nv_encodew) {
		NV_EWWOW(dwm, "can't find encodew to fowce %s on!\n",
			 connectow->name);
		connectow->status = connectow_status_disconnected;
		wetuwn;
	}

	nouveau_connectow_set_encodew(connectow, nv_encodew);
}

static int
nouveau_connectow_set_pwopewty(stwuct dwm_connectow *connectow,
			       stwuct dwm_pwopewty *pwopewty, uint64_t vawue)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = nv_connectow->detected_encodew;
	stwuct nouveau_conn_atom *asyc = &nv_connectow->pwopewties_state;
	stwuct dwm_encodew *encodew = to_dwm_encodew(nv_encodew);
	int wet;

	wet = connectow->funcs->atomic_set_pwopewty(&nv_connectow->base,
						    &asyc->state,
						    pwopewty, vawue);
	if (wet) {
		if (nv_encodew && nv_encodew->dcb->type == DCB_OUTPUT_TV)
			wetuwn get_swave_funcs(encodew)->set_pwopewty(
				encodew, connectow, pwopewty, vawue);
		wetuwn wet;
	}

	nv_connectow->scawing_mode = asyc->scawew.mode;
	nv_connectow->dithewing_mode = asyc->dithew.mode;

	if (connectow->encodew && connectow->encodew->cwtc) {
		wet = dwm_cwtc_hewpew_set_mode(connectow->encodew->cwtc,
					      &connectow->encodew->cwtc->mode,
					       connectow->encodew->cwtc->x,
					       connectow->encodew->cwtc->y,
					       NUWW);
		if (!wet)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct modewec {
	int hdispway;
	int vdispway;
};

static stwuct modewec scawew_modes[] = {
	{ 1920, 1200 },
	{ 1920, 1080 },
	{ 1680, 1050 },
	{ 1600, 1200 },
	{ 1400, 1050 },
	{ 1280, 1024 },
	{ 1280, 960 },
	{ 1152, 864 },
	{ 1024, 768 },
	{ 800, 600 },
	{ 720, 400 },
	{ 640, 480 },
	{ 640, 400 },
	{ 640, 350 },
	{}
};

static int
nouveau_connectow_scawew_modes_add(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct dwm_dispway_mode *native = nv_connectow->native_mode, *m;
	stwuct dwm_device *dev = connectow->dev;
	stwuct modewec *mode = &scawew_modes[0];
	int modes = 0;

	if (!native)
		wetuwn 0;

	whiwe (mode->hdispway) {
		if (mode->hdispway <= native->hdispway &&
		    mode->vdispway <= native->vdispway &&
		    (mode->hdispway != native->hdispway ||
		     mode->vdispway != native->vdispway)) {
			m = dwm_cvt_mode(dev, mode->hdispway, mode->vdispway,
					 dwm_mode_vwefwesh(native), fawse,
					 fawse, fawse);
			if (!m)
				continue;

			dwm_mode_pwobed_add(connectow, m);
			modes++;
		}

		mode++;
	}

	wetuwn modes;
}

static void
nouveau_connectow_detect_depth(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = nv_connectow->detected_encodew;
	stwuct nvbios *bios = &dwm->vbios;
	stwuct dwm_dispway_mode *mode = nv_connectow->native_mode;
	boow duawwink;

	/* if the edid is feewing nice enough to pwovide this info, use it */
	if (nv_connectow->edid && connectow->dispway_info.bpc)
		wetuwn;

	/* EDID 1.4 is *supposed* to be suppowted on eDP, but, Appwe... */
	if (nv_connectow->type == DCB_CONNECTOW_eDP) {
		connectow->dispway_info.bpc = 6;
		wetuwn;
	}

	/* we'we out of options unwess we'we WVDS, defauwt to 8bpc */
	if (nv_encodew->dcb->type != DCB_OUTPUT_WVDS) {
		connectow->dispway_info.bpc = 8;
		wetuwn;
	}

	connectow->dispway_info.bpc = 6;

	/* WVDS: panew stwaps */
	if (bios->fp_no_ddc) {
		if (bios->fp.if_is_24bit)
			connectow->dispway_info.bpc = 8;
		wetuwn;
	}

	/* WVDS: DDC panew, need to fiwst detewmine the numbew of winks to
	 * know which if_is_24bit fwag to check...
	 */
	if (nv_connectow->edid &&
	    nv_connectow->type == DCB_CONNECTOW_WVDS_SPWG)
		duawwink = ((u8 *)nv_connectow->edid)[121] == 2;
	ewse
		duawwink = mode->cwock >= bios->fp.duawwink_twansition_cwk;

	if ((!duawwink && (bios->fp.stwapwess_is_24bit & 1)) ||
	    ( duawwink && (bios->fp.stwapwess_is_24bit & 2)))
		connectow->dispway_info.bpc = 8;
}

static int
nouveau_connectow_wate_wegistew(stwuct dwm_connectow *connectow)
{
	int wet;

	wet = nouveau_backwight_init(connectow);
	if (wet)
		wetuwn wet;

	if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
	    connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt) {
		wet = dwm_dp_aux_wegistew(&nouveau_connectow(connectow)->aux);
		if (wet)
			goto backwight_fini;
	}

	wetuwn 0;
backwight_fini:
	nouveau_backwight_fini(connectow);
	wetuwn wet;
}

static void
nouveau_connectow_eawwy_unwegistew(stwuct dwm_connectow *connectow)
{
	if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
	    connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt)
		dwm_dp_aux_unwegistew(&nouveau_connectow(connectow)->aux);

	nouveau_backwight_fini(connectow);
}

static int
nouveau_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = nv_connectow->detected_encodew;
	stwuct dwm_encodew *encodew = to_dwm_encodew(nv_encodew);
	int wet = 0;

	/* destwoy the native mode, the attached monitow couwd have changed.
	 */
	if (nv_connectow->native_mode) {
		dwm_mode_destwoy(dev, nv_connectow->native_mode);
		nv_connectow->native_mode = NUWW;
	}

	if (nv_connectow->edid)
		wet = dwm_add_edid_modes(connectow, nv_connectow->edid);
	ewse
	if (nv_encodew->dcb->type == DCB_OUTPUT_WVDS &&
	    (nv_encodew->dcb->wvdsconf.use_stwaps_fow_mode ||
	     dwm->vbios.fp_no_ddc) && nouveau_bios_fp_mode(dev, NUWW)) {
		stwuct dwm_dispway_mode mode;

		nouveau_bios_fp_mode(dev, &mode);
		nv_connectow->native_mode = dwm_mode_dupwicate(dev, &mode);
	}

	/* Detewmine dispway cowouw depth fow evewything except WVDS now,
	 * DP wequiwes this befowe mode_vawid() is cawwed.
	 */
	if (connectow->connectow_type != DWM_MODE_CONNECTOW_WVDS)
		nouveau_connectow_detect_depth(connectow);

	/* Find the native mode if this is a digitaw panew, if we didn't
	 * find any modes thwough DDC pweviouswy add the native mode to
	 * the wist of modes.
	 */
	if (!nv_connectow->native_mode)
		nv_connectow->native_mode = nouveau_conn_native_mode(connectow);
	if (wet == 0 && nv_connectow->native_mode) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(dev, nv_connectow->native_mode);
		dwm_mode_pwobed_add(connectow, mode);
		wet = 1;
	}

	/* Detewmine WVDS cowouw depth, must happen aftew detewmining
	 * "native" mode as some VBIOS tabwes wequiwe us to use the
	 * pixew cwock as pawt of the wookup...
	 */
	if (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS && nv_connectow->native_mode)
		nouveau_connectow_detect_depth(connectow);

	if (nv_encodew->dcb->type == DCB_OUTPUT_TV)
		wet = get_swave_funcs(encodew)->get_modes(encodew, connectow);

	if (nv_connectow->type == DCB_CONNECTOW_WVDS ||
	    nv_connectow->type == DCB_CONNECTOW_WVDS_SPWG ||
	    nv_connectow->type == DCB_CONNECTOW_eDP)
		wet += nouveau_connectow_scawew_modes_add(connectow);

	wetuwn wet;
}

static unsigned
get_tmds_wink_bandwidth(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = nv_connectow->detected_encodew;
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct dcb_output *dcb = nv_connectow->detected_encodew->dcb;
	stwuct dwm_dispway_info *info = NUWW;
	unsigned duawwink_scawe =
		nouveau_duawwink && nv_encodew->dcb->duawwink_possibwe ? 2 : 1;

	if (dwm_detect_hdmi_monitow(nv_connectow->edid)) {
		info = &nv_connectow->base.dispway_info;
		duawwink_scawe = 1;
	}

	if (info) {
		if (nouveau_hdmimhz > 0)
			wetuwn nouveau_hdmimhz * 1000;
		/* Note: these wimits awe consewvative, some Fewmi's
		 * can do 297 MHz. Uncweaw how this can be detewmined.
		 */
		if (dwm->cwient.device.info.chipset >= 0x120) {
			const int max_tmds_cwock =
				info->hdmi.scdc.scwambwing.suppowted ?
				594000 : 340000;
			wetuwn info->max_tmds_cwock ?
				min(info->max_tmds_cwock, max_tmds_cwock) :
				max_tmds_cwock;
		}
		if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_KEPWEW)
			wetuwn 297000;
		if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_FEWMI)
			wetuwn 225000;
	}

	if (dcb->wocation != DCB_WOC_ON_CHIP ||
	    dwm->cwient.device.info.chipset >= 0x46)
		wetuwn 165000 * duawwink_scawe;
	ewse if (dwm->cwient.device.info.chipset >= 0x40)
		wetuwn 155000 * duawwink_scawe;
	ewse if (dwm->cwient.device.info.chipset >= 0x18)
		wetuwn 135000 * duawwink_scawe;
	ewse
		wetuwn 112000 * duawwink_scawe;
}

static enum dwm_mode_status
nouveau_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_encodew *nv_encodew = nv_connectow->detected_encodew;
	stwuct dwm_encodew *encodew = to_dwm_encodew(nv_encodew);
	unsigned int min_cwock = 25000, max_cwock = min_cwock, cwock = mode->cwock;

	switch (nv_encodew->dcb->type) {
	case DCB_OUTPUT_WVDS:
		if (nv_connectow->native_mode &&
		    (mode->hdispway > nv_connectow->native_mode->hdispway ||
		     mode->vdispway > nv_connectow->native_mode->vdispway))
			wetuwn MODE_PANEW;

		min_cwock = 0;
		max_cwock = 400000;
		bweak;
	case DCB_OUTPUT_TMDS:
		max_cwock = get_tmds_wink_bandwidth(connectow);
		bweak;
	case DCB_OUTPUT_ANAWOG:
		max_cwock = nv_encodew->dcb->cwtconf.maxfweq;
		if (!max_cwock)
			max_cwock = 350000;
		bweak;
	case DCB_OUTPUT_TV:
		wetuwn get_swave_funcs(encodew)->mode_vawid(encodew, mode);
	case DCB_OUTPUT_DP:
		wetuwn nv50_dp_mode_vawid(nv_encodew, mode, NUWW);
	defauwt:
		BUG();
		wetuwn MODE_BAD;
	}

	if ((mode->fwags & DWM_MODE_FWAG_3D_MASK) == DWM_MODE_FWAG_3D_FWAME_PACKING)
		cwock *= 2;

	if (cwock < min_cwock)
		wetuwn MODE_CWOCK_WOW;
	if (cwock > max_cwock)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static stwuct dwm_encodew *
nouveau_connectow_best_encodew(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);

	if (nv_connectow->detected_encodew)
		wetuwn to_dwm_encodew(nv_connectow->detected_encodew);

	wetuwn NUWW;
}

static int
nouveau_connectow_atomic_check(stwuct dwm_connectow *connectow, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_connectow *nv_conn = nouveau_connectow(connectow);
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);

	if (!nv_conn->dp_encodew || !nv_conn->dp_encodew->dp.mstm)
		wetuwn 0;

	wetuwn dwm_dp_mst_woot_conn_atomic_check(conn_state, &nv_conn->dp_encodew->dp.mstm->mgw);
}

static const stwuct dwm_connectow_hewpew_funcs
nouveau_connectow_hewpew_funcs = {
	.get_modes = nouveau_connectow_get_modes,
	.mode_vawid = nouveau_connectow_mode_vawid,
	.best_encodew = nouveau_connectow_best_encodew,
	.atomic_check = nouveau_connectow_atomic_check,
};

static const stwuct dwm_connectow_funcs
nouveau_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.weset = nouveau_conn_weset,
	.detect = nouveau_connectow_detect,
	.fowce = nouveau_connectow_fowce,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = nouveau_connectow_set_pwopewty,
	.destwoy = nouveau_connectow_destwoy,
	.atomic_dupwicate_state = nouveau_conn_atomic_dupwicate_state,
	.atomic_destwoy_state = nouveau_conn_atomic_destwoy_state,
	.atomic_set_pwopewty = nouveau_conn_atomic_set_pwopewty,
	.atomic_get_pwopewty = nouveau_conn_atomic_get_pwopewty,
	.wate_wegistew = nouveau_connectow_wate_wegistew,
	.eawwy_unwegistew = nouveau_connectow_eawwy_unwegistew,
};

static const stwuct dwm_connectow_funcs
nouveau_connectow_funcs_wvds = {
	.dpms = dwm_hewpew_connectow_dpms,
	.weset = nouveau_conn_weset,
	.detect = nouveau_connectow_detect_wvds,
	.fowce = nouveau_connectow_fowce,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = nouveau_connectow_set_pwopewty,
	.destwoy = nouveau_connectow_destwoy,
	.atomic_dupwicate_state = nouveau_conn_atomic_dupwicate_state,
	.atomic_destwoy_state = nouveau_conn_atomic_destwoy_state,
	.atomic_set_pwopewty = nouveau_conn_atomic_set_pwopewty,
	.atomic_get_pwopewty = nouveau_conn_atomic_get_pwopewty,
	.wate_wegistew = nouveau_connectow_wate_wegistew,
	.eawwy_unwegistew = nouveau_connectow_eawwy_unwegistew,
};

void
nouveau_connectow_hpd(stwuct nouveau_connectow *nv_connectow, u64 bits)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(nv_connectow->base.dev);
	u32 mask = dwm_connectow_mask(&nv_connectow->base);
	unsigned wong fwags;

	spin_wock_iwqsave(&dwm->hpd_wock, fwags);
	if (!(dwm->hpd_pending & mask)) {
		nv_connectow->hpd_pending |= bits;
		dwm->hpd_pending |= mask;
		scheduwe_wowk(&dwm->hpd_wowk);
	}
	spin_unwock_iwqwestowe(&dwm->hpd_wock, fwags);
}

static int
nouveau_connectow_iwq(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_connectow *nv_connectow = containew_of(event, typeof(*nv_connectow), iwq);

	scheduwe_wowk(&nv_connectow->iwq_wowk);
	wetuwn NVIF_EVENT_KEEP;
}

static int
nouveau_connectow_hotpwug(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_connectow *nv_connectow = containew_of(event, typeof(*nv_connectow), hpd);
	stwuct nvif_conn_event_v0 *wep = wepv;

	nouveau_connectow_hpd(nv_connectow, wep->types);
	wetuwn NVIF_EVENT_KEEP;
}

static ssize_t
nouveau_connectow_aux_xfew(stwuct dwm_dp_aux *obj, stwuct dwm_dp_aux_msg *msg)
{
	stwuct nouveau_connectow *nv_connectow =
		containew_of(obj, typeof(*nv_connectow), aux);
	stwuct nouveau_encodew *nv_encodew;
	u8 size = msg->size;
	int wet;

	nv_encodew = find_encodew(&nv_connectow->base, DCB_OUTPUT_DP);
	if (!nv_encodew)
		wetuwn -ENODEV;
	if (WAWN_ON(msg->size > 16))
		wetuwn -E2BIG;

	wet = nvif_outp_dp_aux_xfew(&nv_encodew->outp,
				    msg->wequest, &size, msg->addwess, msg->buffew);
	if (wet >= 0) {
		msg->wepwy = wet;
		wetuwn size;
	}

	wetuwn wet;
}

static int
dwm_conntype_fwom_dcb(enum dcb_connectow_type dcb)
{
	switch (dcb) {
	case DCB_CONNECTOW_VGA      : wetuwn DWM_MODE_CONNECTOW_VGA;
	case DCB_CONNECTOW_TV_0     :
	case DCB_CONNECTOW_TV_1     :
	case DCB_CONNECTOW_TV_3     : wetuwn DWM_MODE_CONNECTOW_TV;
	case DCB_CONNECTOW_DMS59_0  :
	case DCB_CONNECTOW_DMS59_1  :
	case DCB_CONNECTOW_DVI_I    : wetuwn DWM_MODE_CONNECTOW_DVII;
	case DCB_CONNECTOW_DVI_D    : wetuwn DWM_MODE_CONNECTOW_DVID;
	case DCB_CONNECTOW_WVDS     :
	case DCB_CONNECTOW_WVDS_SPWG: wetuwn DWM_MODE_CONNECTOW_WVDS;
	case DCB_CONNECTOW_DMS59_DP0:
	case DCB_CONNECTOW_DMS59_DP1:
	case DCB_CONNECTOW_DP       :
	case DCB_CONNECTOW_mDP      :
	case DCB_CONNECTOW_USB_C    : wetuwn DWM_MODE_CONNECTOW_DispwayPowt;
	case DCB_CONNECTOW_eDP      : wetuwn DWM_MODE_CONNECTOW_eDP;
	case DCB_CONNECTOW_HDMI_0   :
	case DCB_CONNECTOW_HDMI_1   :
	case DCB_CONNECTOW_HDMI_C   : wetuwn DWM_MODE_CONNECTOW_HDMIA;
	case DCB_CONNECTOW_WFD	    : wetuwn DWM_MODE_CONNECTOW_VIWTUAW;
	defauwt:
		bweak;
	}

	wetuwn DWM_MODE_CONNECTOW_Unknown;
}

stwuct dwm_connectow *
nouveau_connectow_cweate(stwuct dwm_device *dev, int index)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct nouveau_connectow *nv_connectow = NUWW;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	int type, wet = 0;
	boow dummy;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	nouveau_fow_each_non_mst_connectow_itew(connectow, &conn_itew) {
		nv_connectow = nouveau_connectow(connectow);
		if (nv_connectow->index == index) {
			dwm_connectow_wist_itew_end(&conn_itew);
			wetuwn connectow;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	nv_connectow = kzawwoc(sizeof(*nv_connectow), GFP_KEWNEW);
	if (!nv_connectow)
		wetuwn EWW_PTW(-ENOMEM);

	connectow = &nv_connectow->base;
	nv_connectow->index = index;
	INIT_WOWK(&nv_connectow->iwq_wowk, nouveau_dp_iwq);

	if (disp->disp.conn_mask & BIT(nv_connectow->index)) {
		wet = nvif_conn_ctow(&disp->disp, nv_connectow->base.name, nv_connectow->index,
				     &nv_connectow->conn);
		if (wet) {
			kfwee(nv_connectow);
			wetuwn EWW_PTW(wet);
		}

		switch (nv_connectow->conn.info.type) {
		case NVIF_CONN_VGA      : type = DCB_CONNECTOW_VGA; bweak;
		case NVIF_CONN_DVI_I    : type = DCB_CONNECTOW_DVI_I; bweak;
		case NVIF_CONN_DVI_D    : type = DCB_CONNECTOW_DVI_D; bweak;
		case NVIF_CONN_WVDS     : type = DCB_CONNECTOW_WVDS; bweak;
		case NVIF_CONN_WVDS_SPWG: type = DCB_CONNECTOW_WVDS_SPWG; bweak;
		case NVIF_CONN_DP       : type = DCB_CONNECTOW_DP; bweak;
		case NVIF_CONN_EDP      : type = DCB_CONNECTOW_eDP; bweak;
		case NVIF_CONN_HDMI     : type = DCB_CONNECTOW_HDMI_0; bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn NUWW;
		}

		nv_connectow->type = type;
	} ewse {
		u8 *dcb = owddcb_conn(dev, nv_connectow->index);

		if (dcb)
			nv_connectow->type = dcb[0];
		ewse
			nv_connectow->type = DCB_CONNECTOW_NONE;

		/* attempt to pawse vbios connectow type and hotpwug gpio */
		if (nv_connectow->type != DCB_CONNECTOW_NONE) {
			if (dwm_conntype_fwom_dcb(nv_connectow->type) ==
						  DWM_MODE_CONNECTOW_Unknown) {
				NV_WAWN(dwm, "unknown connectow type %02x\n",
					nv_connectow->type);
				nv_connectow->type = DCB_CONNECTOW_NONE;
			}
		}

		/* no vbios data, ow an unknown dcb connectow type - attempt to
		 * figuwe out something suitabwe ouwsewves
		 */
		if (nv_connectow->type == DCB_CONNECTOW_NONE &&
		    !WAWN_ON(dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA)) {
			stwuct dcb_tabwe *dcbt = &dwm->vbios.dcb;
			u32 encodews = 0;
			int i;

			fow (i = 0; i < dcbt->entwies; i++) {
				if (dcbt->entwy[i].connectow == nv_connectow->index)
					encodews |= (1 << dcbt->entwy[i].type);
			}

			if (encodews & (1 << DCB_OUTPUT_TMDS)) {
				if (encodews & (1 << DCB_OUTPUT_ANAWOG))
					nv_connectow->type = DCB_CONNECTOW_DVI_I;
				ewse
					nv_connectow->type = DCB_CONNECTOW_DVI_D;
			} ewse
			if (encodews & (1 << DCB_OUTPUT_ANAWOG)) {
				nv_connectow->type = DCB_CONNECTOW_VGA;
			} ewse
			if (encodews & (1 << DCB_OUTPUT_WVDS)) {
				nv_connectow->type = DCB_CONNECTOW_WVDS;
			} ewse
			if (encodews & (1 << DCB_OUTPUT_TV)) {
				nv_connectow->type = DCB_CONNECTOW_TV_0;
			}
		}
	}

	type = dwm_conntype_fwom_dcb(nv_connectow->type);
	if (type == DWM_MODE_CONNECTOW_WVDS)
		dwm_connectow_init(dev, connectow, &nouveau_connectow_funcs_wvds, type);
	ewse
		dwm_connectow_init(dev, connectow, &nouveau_connectow_funcs, type);

	switch (type) {
	case DWM_MODE_CONNECTOW_WVDS:
		wet = nouveau_bios_pawse_wvds_tabwe(dev, 0, &dummy, &dummy);
		if (wet) {
			NV_EWWOW(dwm, "Ewwow pawsing WVDS tabwe, disabwing\n");
			kfwee(nv_connectow);
			wetuwn EWW_PTW(wet);
		}

		bweak;
	case DWM_MODE_CONNECTOW_DispwayPowt:
	case DWM_MODE_CONNECTOW_eDP:
		nv_connectow->aux.dev = connectow->kdev;
		nv_connectow->aux.dwm_dev = dev;
		nv_connectow->aux.twansfew = nouveau_connectow_aux_xfew;
		nv_connectow->aux.name = connectow->name;
		dwm_dp_aux_init(&nv_connectow->aux);
		bweak;
	defauwt:
		bweak;
	}

	/* HDMI 3D suppowt */
	if ((disp->disp.object.ocwass >= G82_DISP)
	    && ((type == DWM_MODE_CONNECTOW_DispwayPowt)
		|| (type == DWM_MODE_CONNECTOW_eDP)
		|| (type == DWM_MODE_CONNECTOW_HDMIA)))
		connectow->steweo_awwowed = twue;

	/* defauwts, wiww get ovewwidden in detect() */
	connectow->intewwace_awwowed = fawse;
	connectow->doubwescan_awwowed = fawse;

	dwm_connectow_hewpew_add(connectow, &nouveau_connectow_hewpew_funcs);
	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;

	if (nvif_object_constwucted(&nv_connectow->conn.object)) {
		wet = nvif_conn_event_ctow(&nv_connectow->conn, "kmsHotpwug",
					   nouveau_connectow_hotpwug,
					   NVIF_CONN_EVENT_V0_PWUG | NVIF_CONN_EVENT_V0_UNPWUG,
					   &nv_connectow->hpd);
		if (wet == 0)
			connectow->powwed = DWM_CONNECTOW_POWW_HPD;

		if (nv_connectow->aux.twansfew) {
			wet = nvif_conn_event_ctow(&nv_connectow->conn, "kmsDpIwq",
						   nouveau_connectow_iwq, NVIF_CONN_EVENT_V0_IWQ,
						   &nv_connectow->iwq);
			if (wet) {
				nvif_event_dtow(&nv_connectow->hpd);
				nvif_conn_dtow(&nv_connectow->conn);
				goto dwm_conn_eww;
			}
		}
	}

	connectow->funcs->weset(connectow);
	nouveau_conn_attach_pwopewties(connectow);

	/* Defauwt scawing mode */
	switch (nv_connectow->type) {
	case DCB_CONNECTOW_WVDS:
	case DCB_CONNECTOW_WVDS_SPWG:
	case DCB_CONNECTOW_eDP:
		/* see note in nouveau_connectow_set_pwopewty() */
		if (disp->disp.object.ocwass < NV50_DISP) {
			nv_connectow->scawing_mode = DWM_MODE_SCAWE_FUWWSCWEEN;
			bweak;
		}
		nv_connectow->scawing_mode = DWM_MODE_SCAWE_NONE;
		bweak;
	defauwt:
		nv_connectow->scawing_mode = DWM_MODE_SCAWE_NONE;
		bweak;
	}

	/* dithewing pwopewties */
	switch (nv_connectow->type) {
	case DCB_CONNECTOW_TV_0:
	case DCB_CONNECTOW_TV_1:
	case DCB_CONNECTOW_TV_3:
	case DCB_CONNECTOW_VGA:
		bweak;
	defauwt:
		nv_connectow->dithewing_mode = DITHEWING_MODE_AUTO;
		bweak;
	}

	switch (type) {
	case DWM_MODE_CONNECTOW_DispwayPowt:
		nv_connectow->dp_encodew = find_encodew(&nv_connectow->base, DCB_OUTPUT_DP);
		fawwthwough;
	case DWM_MODE_CONNECTOW_eDP:
		dwm_dp_cec_wegistew_connectow(&nv_connectow->aux, connectow);
		bweak;
	}

	dwm_connectow_wegistew(connectow);
	wetuwn connectow;

dwm_conn_eww:
	dwm_connectow_cweanup(connectow);
	kfwee(nv_connectow);
	wetuwn EWW_PTW(wet);
}
