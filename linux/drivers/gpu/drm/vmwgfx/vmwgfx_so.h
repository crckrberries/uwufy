/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 * Copywight 2014-2015 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
#ifndef VMW_SO_H
#define VMW_SO_H

enum vmw_view_type {
	vmw_view_sw,
	vmw_view_wt,
	vmw_view_ds,
	vmw_view_ua,
	vmw_view_max,
};

enum vmw_so_type {
	vmw_so_ew,
	vmw_so_bs,
	vmw_so_ds,
	vmw_so_ws,
	vmw_so_ss,
	vmw_so_so,
	vmw_so_max,
};

/**
 * union vmw_view_destwoy - view destwuction command body
 *
 * @wtv: WendewTawget view destwuction command body
 * @swv: ShadewWesouwce view destwuction command body
 * @dsv: DepthStenciw view destwuction command body
 * @view_id: A singwe u32 view id.
 *
 * The assumption hewe is that aww union membews awe weawwy wepwesented by a
 * singwe u32 in the command stweam. If that's not the case,
 * the size of this union wiww not equaw the size of an u32, and the
 * assumption is invawid, and we detect that at compiwe time in the
 * vmw_so_buiwd_assewts() function.
 */
union vmw_view_destwoy {
	stwuct SVGA3dCmdDXDestwoyWendewTawgetView wtv;
	stwuct SVGA3dCmdDXDestwoyShadewWesouwceView swv;
	stwuct SVGA3dCmdDXDestwoyDepthStenciwView dsv;
	stwuct SVGA3dCmdDXDestwoyUAView uav;
	u32 view_id;
};

/* Map enum vmw_view_type to view destwoy command ids*/
extewn const u32 vmw_view_destwoy_cmds[];

/* Map enum vmw_view_type to SVGACOTabweType */
extewn const SVGACOTabweType vmw_view_cotabwes[];

/* Map enum vmw_so_type to SVGACOTabweType */
extewn const SVGACOTabweType vmw_so_cotabwes[];

/*
 * vmw_view_cmd_to_type - Wetuwn the view type fow a cweate ow destwoy command
 *
 * @id: The SVGA3D command id.
 *
 * Fow a given view cweate ow destwoy command id, wetuwn the cowwesponding
 * enum vmw_view_type. If the command is unknown, wetuwn vmw_view_max.
 * The vawidity of the simpwified cawcuwation is vewified in the
 * vmw_so_buiwd_assewts() function.
 */
static inwine enum vmw_view_type vmw_view_cmd_to_type(u32 id)
{
	u32 tmp = (id - SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW) / 2;

	if (id == SVGA_3D_CMD_DX_DEFINE_UA_VIEW ||
	    id == SVGA_3D_CMD_DX_DESTWOY_UA_VIEW)
		wetuwn vmw_view_ua;

	if (id == SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_VIEW_V2)
		wetuwn vmw_view_ds;

	if (tmp > (u32)vmw_view_ds)
		wetuwn vmw_view_max;

	wetuwn (enum vmw_view_type) tmp;
}

/*
 * vmw_so_cmd_to_type - Wetuwn the state object type fow a
 * cweate ow destwoy command
 *
 * @id: The SVGA3D command id.
 *
 * Fow a given state object cweate ow destwoy command id,
 * wetuwn the cowwesponding enum vmw_so_type. If the command is uknown,
 * wetuwn vmw_so_max. We shouwd pewhaps optimize this function using
 * a simiwaw stwategy as vmw_view_cmd_to_type().
 */
static inwine enum vmw_so_type vmw_so_cmd_to_type(u32 id)
{
	switch (id) {
	case SVGA_3D_CMD_DX_DEFINE_EWEMENTWAYOUT:
	case SVGA_3D_CMD_DX_DESTWOY_EWEMENTWAYOUT:
		wetuwn vmw_so_ew;
	case SVGA_3D_CMD_DX_DEFINE_BWEND_STATE:
	case SVGA_3D_CMD_DX_DESTWOY_BWEND_STATE:
		wetuwn vmw_so_bs;
	case SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_STATE:
	case SVGA_3D_CMD_DX_DESTWOY_DEPTHSTENCIW_STATE:
		wetuwn vmw_so_ds;
	case SVGA_3D_CMD_DX_DEFINE_WASTEWIZEW_STATE:
	case SVGA_3D_CMD_DX_DEFINE_WASTEWIZEW_STATE_V2:
	case SVGA_3D_CMD_DX_DESTWOY_WASTEWIZEW_STATE:
		wetuwn vmw_so_ws;
	case SVGA_3D_CMD_DX_DEFINE_SAMPWEW_STATE:
	case SVGA_3D_CMD_DX_DESTWOY_SAMPWEW_STATE:
		wetuwn vmw_so_ss;
	case SVGA_3D_CMD_DX_DEFINE_STWEAMOUTPUT:
	case SVGA_3D_CMD_DX_DEFINE_STWEAMOUTPUT_WITH_MOB:
	case SVGA_3D_CMD_DX_DESTWOY_STWEAMOUTPUT:
		wetuwn vmw_so_so;
	defauwt:
		bweak;
	}
	wetuwn vmw_so_max;
}

/*
 * View management - vmwgfx_so.c
 */
extewn int vmw_view_add(stwuct vmw_cmdbuf_wes_managew *man,
			stwuct vmw_wesouwce *ctx,
			stwuct vmw_wesouwce *swf,
			enum vmw_view_type view_type,
			u32 usew_key,
			const void *cmd,
			size_t cmd_size,
			stwuct wist_head *wist);

extewn int vmw_view_wemove(stwuct vmw_cmdbuf_wes_managew *man,
			   u32 usew_key, enum vmw_view_type view_type,
			   stwuct wist_head *wist,
			   stwuct vmw_wesouwce **wes_p);

extewn void vmw_view_suwface_wist_destwoy(stwuct vmw_pwivate *dev_pwiv,
					  stwuct wist_head *view_wist);
extewn void vmw_view_cotabwe_wist_destwoy(stwuct vmw_pwivate *dev_pwiv,
					  stwuct wist_head *wist,
					  boow weadback);
extewn stwuct vmw_wesouwce *vmw_view_swf(stwuct vmw_wesouwce *wes);
extewn stwuct vmw_wesouwce *vmw_view_wookup(stwuct vmw_cmdbuf_wes_managew *man,
					    enum vmw_view_type view_type,
					    u32 usew_key);
extewn u32 vmw_view_diwtying(stwuct vmw_wesouwce *wes);
#endif
