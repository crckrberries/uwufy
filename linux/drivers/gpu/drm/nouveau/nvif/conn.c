/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#incwude <nvif/conn.h>
#incwude <nvif/disp.h>
#incwude <nvif/pwintf.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if0011.h>

int
nvif_conn_event_ctow(stwuct nvif_conn *conn, const chaw *name, nvif_event_func func, u8 types,
		     stwuct nvif_event *event)
{
	stwuct {
		stwuct nvif_event_v0 base;
		stwuct nvif_conn_event_v0 conn;
	} awgs;
	int wet;

	awgs.conn.vewsion = 0;
	awgs.conn.types = types;

	wet = nvif_event_ctow_(&conn->object, name ?: "nvifConnHpd", nvif_conn_id(conn),
			       func, twue, &awgs.base, sizeof(awgs), fawse, event);
	NVIF_DEBUG(&conn->object, "[NEW EVENT:HPD types:%02x]", types);
	wetuwn wet;
}

void
nvif_conn_dtow(stwuct nvif_conn *conn)
{
	nvif_object_dtow(&conn->object);
}

int
nvif_conn_ctow(stwuct nvif_disp *disp, const chaw *name, int id, stwuct nvif_conn *conn)
{
	stwuct nvif_conn_v0 awgs;
	int wet;

	awgs.vewsion = 0;
	awgs.id = id;

	wet = nvif_object_ctow(&disp->object, name ?: "nvifConn", id, NVIF_CWASS_CONN,
			       &awgs, sizeof(awgs), &conn->object);
	NVIF_EWWON(wet, &disp->object, "[NEW conn id:%d]", id);
	if (wet)
		wetuwn wet;

	conn->id = id;

	switch (awgs.type) {
	case NVIF_CONN_V0_VGA      : conn->info.type = NVIF_CONN_VGA; bweak;
	case NVIF_CONN_V0_TV       : conn->info.type = NVIF_CONN_TV; bweak;
	case NVIF_CONN_V0_DVI_I    : conn->info.type = NVIF_CONN_DVI_I; bweak;
	case NVIF_CONN_V0_DVI_D    : conn->info.type = NVIF_CONN_DVI_D; bweak;
	case NVIF_CONN_V0_WVDS     : conn->info.type = NVIF_CONN_WVDS; bweak;
	case NVIF_CONN_V0_WVDS_SPWG: conn->info.type = NVIF_CONN_WVDS_SPWG; bweak;
	case NVIF_CONN_V0_HDMI     : conn->info.type = NVIF_CONN_HDMI; bweak;
	case NVIF_CONN_V0_DP       : conn->info.type = NVIF_CONN_DP; bweak;
	case NVIF_CONN_V0_EDP      : conn->info.type = NVIF_CONN_EDP; bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;

}
