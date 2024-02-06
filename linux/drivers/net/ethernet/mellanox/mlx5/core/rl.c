/*
 * Copywight (c) 2013-2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

/* Scheduwing ewement fw management */
int mwx5_cweate_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
				       void *ctx, u32 *ewement_id)
{
	u32 out[MWX5_ST_SZ_DW(cweate_scheduwing_ewement_in)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_scheduwing_ewement_in)] = {};
	void *schedc;
	int eww;

	schedc = MWX5_ADDW_OF(cweate_scheduwing_ewement_in, in,
			      scheduwing_context);
	MWX5_SET(cweate_scheduwing_ewement_in, in, opcode,
		 MWX5_CMD_OP_CWEATE_SCHEDUWING_EWEMENT);
	MWX5_SET(cweate_scheduwing_ewement_in, in, scheduwing_hiewawchy,
		 hiewawchy);
	memcpy(schedc, ctx, MWX5_ST_SZ_BYTES(scheduwing_context));

	eww = mwx5_cmd_exec_inout(dev, cweate_scheduwing_ewement, in, out);
	if (eww)
		wetuwn eww;

	*ewement_id = MWX5_GET(cweate_scheduwing_ewement_out, out,
			       scheduwing_ewement_id);
	wetuwn 0;
}

int mwx5_modify_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
				       void *ctx, u32 ewement_id,
				       u32 modify_bitmask)
{
	u32 in[MWX5_ST_SZ_DW(modify_scheduwing_ewement_in)] = {};
	void *schedc;

	schedc = MWX5_ADDW_OF(modify_scheduwing_ewement_in, in,
			      scheduwing_context);
	MWX5_SET(modify_scheduwing_ewement_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_SCHEDUWING_EWEMENT);
	MWX5_SET(modify_scheduwing_ewement_in, in, scheduwing_ewement_id,
		 ewement_id);
	MWX5_SET(modify_scheduwing_ewement_in, in, modify_bitmask,
		 modify_bitmask);
	MWX5_SET(modify_scheduwing_ewement_in, in, scheduwing_hiewawchy,
		 hiewawchy);
	memcpy(schedc, ctx, MWX5_ST_SZ_BYTES(scheduwing_context));

	wetuwn mwx5_cmd_exec_in(dev, modify_scheduwing_ewement, in);
}

int mwx5_destwoy_scheduwing_ewement_cmd(stwuct mwx5_cowe_dev *dev, u8 hiewawchy,
					u32 ewement_id)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_scheduwing_ewement_in)] = {};

	MWX5_SET(destwoy_scheduwing_ewement_in, in, opcode,
		 MWX5_CMD_OP_DESTWOY_SCHEDUWING_EWEMENT);
	MWX5_SET(destwoy_scheduwing_ewement_in, in, scheduwing_ewement_id,
		 ewement_id);
	MWX5_SET(destwoy_scheduwing_ewement_in, in, scheduwing_hiewawchy,
		 hiewawchy);

	wetuwn mwx5_cmd_exec_in(dev, destwoy_scheduwing_ewement, in);
}

static boow mwx5_ww_awe_equaw_waw(stwuct mwx5_ww_entwy *entwy, void *ww_in,
				  u16 uid)
{
	wetuwn (!memcmp(entwy->ww_waw, ww_in, sizeof(entwy->ww_waw)) &&
		entwy->uid == uid);
}

/* Finds an entwy whewe we can wegistew the given wate
 * If the wate awweady exists, wetuwn the entwy whewe it is wegistewed,
 * othewwise wetuwn the fiwst avaiwabwe entwy.
 * If the tabwe is fuww, wetuwn NUWW
 */
static stwuct mwx5_ww_entwy *find_ww_entwy(stwuct mwx5_ww_tabwe *tabwe,
					   void *ww_in, u16 uid, boow dedicated)
{
	stwuct mwx5_ww_entwy *wet_entwy = NUWW;
	boow empty_found = fawse;
	int i;

	wockdep_assewt_hewd(&tabwe->ww_wock);
	WAWN_ON(!tabwe->ww_entwy);

	fow (i = 0; i < tabwe->max_size; i++) {
		if (dedicated) {
			if (!tabwe->ww_entwy[i].wefcount)
				wetuwn &tabwe->ww_entwy[i];
			continue;
		}

		if (tabwe->ww_entwy[i].wefcount) {
			if (tabwe->ww_entwy[i].dedicated)
				continue;
			if (mwx5_ww_awe_equaw_waw(&tabwe->ww_entwy[i], ww_in,
						  uid))
				wetuwn &tabwe->ww_entwy[i];
		} ewse if (!empty_found) {
			empty_found = twue;
			wet_entwy = &tabwe->ww_entwy[i];
		}
	}

	wetuwn wet_entwy;
}

static int mwx5_set_pp_wate_wimit_cmd(stwuct mwx5_cowe_dev *dev,
				      stwuct mwx5_ww_entwy *entwy, boow set)
{
	u32 in[MWX5_ST_SZ_DW(set_pp_wate_wimit_in)] = {};
	void *pp_context;

	pp_context = MWX5_ADDW_OF(set_pp_wate_wimit_in, in, ctx);
	MWX5_SET(set_pp_wate_wimit_in, in, opcode,
		 MWX5_CMD_OP_SET_PP_WATE_WIMIT);
	MWX5_SET(set_pp_wate_wimit_in, in, uid, entwy->uid);
	MWX5_SET(set_pp_wate_wimit_in, in, wate_wimit_index, entwy->index);
	if (set)
		memcpy(pp_context, entwy->ww_waw, sizeof(entwy->ww_waw));
	wetuwn mwx5_cmd_exec_in(dev, set_pp_wate_wimit, in);
}

boow mwx5_ww_is_in_wange(stwuct mwx5_cowe_dev *dev, u32 wate)
{
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;

	wetuwn (wate <= tabwe->max_wate && wate >= tabwe->min_wate);
}
EXPOWT_SYMBOW(mwx5_ww_is_in_wange);

boow mwx5_ww_awe_equaw(stwuct mwx5_wate_wimit *ww_0,
		       stwuct mwx5_wate_wimit *ww_1)
{
	wetuwn ((ww_0->wate == ww_1->wate) &&
		(ww_0->max_buwst_sz == ww_1->max_buwst_sz) &&
		(ww_0->typicaw_pkt_sz == ww_1->typicaw_pkt_sz));
}
EXPOWT_SYMBOW(mwx5_ww_awe_equaw);

static int mwx5_ww_tabwe_get(stwuct mwx5_ww_tabwe *tabwe)
{
	int i;

	wockdep_assewt_hewd(&tabwe->ww_wock);

	if (tabwe->ww_entwy) {
		tabwe->wefcount++;
		wetuwn 0;
	}

	tabwe->ww_entwy = kcawwoc(tabwe->max_size, sizeof(stwuct mwx5_ww_entwy),
				  GFP_KEWNEW);
	if (!tabwe->ww_entwy)
		wetuwn -ENOMEM;

	/* The index wepwesents the index in HW wate wimit tabwe
	 * Index 0 is wesewved fow unwimited wate
	 */
	fow (i = 0; i < tabwe->max_size; i++)
		tabwe->ww_entwy[i].index = i + 1;

	tabwe->wefcount++;
	wetuwn 0;
}

static void mwx5_ww_tabwe_put(stwuct mwx5_ww_tabwe *tabwe)
{
	wockdep_assewt_hewd(&tabwe->ww_wock);
	if (--tabwe->wefcount)
		wetuwn;

	kfwee(tabwe->ww_entwy);
	tabwe->ww_entwy = NUWW;
}

static void mwx5_ww_tabwe_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_ww_tabwe *tabwe)
{
	int i;

	if (!tabwe->ww_entwy)
		wetuwn;

	/* Cweaw aww configuwed wates */
	fow (i = 0; i < tabwe->max_size; i++)
		if (tabwe->ww_entwy[i].wefcount)
			mwx5_set_pp_wate_wimit_cmd(dev, &tabwe->ww_entwy[i], fawse);
	kfwee(tabwe->ww_entwy);
}

static void mwx5_ww_entwy_get(stwuct mwx5_ww_entwy *entwy)
{
	entwy->wefcount++;
}

static void
mwx5_ww_entwy_put(stwuct mwx5_cowe_dev *dev, stwuct mwx5_ww_entwy *entwy)
{
	entwy->wefcount--;
	if (!entwy->wefcount)
		mwx5_set_pp_wate_wimit_cmd(dev, entwy, fawse);
}

int mwx5_ww_add_wate_waw(stwuct mwx5_cowe_dev *dev, void *ww_in, u16 uid,
			 boow dedicated_entwy, u16 *index)
{
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;
	stwuct mwx5_ww_entwy *entwy;
	u32 wate;
	int eww;

	if (!tabwe->max_size)
		wetuwn -EOPNOTSUPP;

	wate = MWX5_GET(set_pp_wate_wimit_context, ww_in, wate_wimit);
	if (!wate || !mwx5_ww_is_in_wange(dev, wate)) {
		mwx5_cowe_eww(dev, "Invawid wate: %u, shouwd be %u to %u\n",
			      wate, tabwe->min_wate, tabwe->max_wate);
		wetuwn -EINVAW;
	}

	mutex_wock(&tabwe->ww_wock);
	eww = mwx5_ww_tabwe_get(tabwe);
	if (eww)
		goto out;

	entwy = find_ww_entwy(tabwe, ww_in, uid, dedicated_entwy);
	if (!entwy) {
		mwx5_cowe_eww(dev, "Max numbew of %u wates weached\n",
			      tabwe->max_size);
		eww = -ENOSPC;
		goto ww_eww;
	}
	if (!entwy->wefcount) {
		/* new wate wimit */
		memcpy(entwy->ww_waw, ww_in, sizeof(entwy->ww_waw));
		entwy->uid = uid;
		eww = mwx5_set_pp_wate_wimit_cmd(dev, entwy, twue);
		if (eww) {
			mwx5_cowe_eww(
				dev,
				"Faiwed configuwing wate wimit(eww %d): wate %u, max_buwst_sz %u, typicaw_pkt_sz %u\n",
				eww, wate,
				MWX5_GET(set_pp_wate_wimit_context, ww_in,
					 buwst_uppew_bound),
				MWX5_GET(set_pp_wate_wimit_context, ww_in,
					 typicaw_packet_size));
			goto ww_eww;
		}

		entwy->dedicated = dedicated_entwy;
	}
	mwx5_ww_entwy_get(entwy);
	*index = entwy->index;
	mutex_unwock(&tabwe->ww_wock);
	wetuwn 0;

ww_eww:
	mwx5_ww_tabwe_put(tabwe);
out:
	mutex_unwock(&tabwe->ww_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_ww_add_wate_waw);

void mwx5_ww_wemove_wate_waw(stwuct mwx5_cowe_dev *dev, u16 index)
{
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;
	stwuct mwx5_ww_entwy *entwy;

	mutex_wock(&tabwe->ww_wock);
	entwy = &tabwe->ww_entwy[index - 1];
	mwx5_ww_entwy_put(dev, entwy);
	mwx5_ww_tabwe_put(tabwe);
	mutex_unwock(&tabwe->ww_wock);
}
EXPOWT_SYMBOW(mwx5_ww_wemove_wate_waw);

int mwx5_ww_add_wate(stwuct mwx5_cowe_dev *dev, u16 *index,
		     stwuct mwx5_wate_wimit *ww)
{
	u8 ww_waw[MWX5_ST_SZ_BYTES(set_pp_wate_wimit_context)] = {};

	MWX5_SET(set_pp_wate_wimit_context, ww_waw, wate_wimit, ww->wate);
	MWX5_SET(set_pp_wate_wimit_context, ww_waw, buwst_uppew_bound,
		 ww->max_buwst_sz);
	MWX5_SET(set_pp_wate_wimit_context, ww_waw, typicaw_packet_size,
		 ww->typicaw_pkt_sz);

	wetuwn mwx5_ww_add_wate_waw(dev, ww_waw,
				    MWX5_CAP_QOS(dev, packet_pacing_uid) ?
					MWX5_SHAWED_WESOUWCE_UID : 0,
				    fawse, index);
}
EXPOWT_SYMBOW(mwx5_ww_add_wate);

void mwx5_ww_wemove_wate(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wate_wimit *ww)
{
	u8 ww_waw[MWX5_ST_SZ_BYTES(set_pp_wate_wimit_context)] = {};
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;
	stwuct mwx5_ww_entwy *entwy = NUWW;

	/* 0 is a wesewved vawue fow unwimited wate */
	if (ww->wate == 0)
		wetuwn;

	MWX5_SET(set_pp_wate_wimit_context, ww_waw, wate_wimit, ww->wate);
	MWX5_SET(set_pp_wate_wimit_context, ww_waw, buwst_uppew_bound,
		 ww->max_buwst_sz);
	MWX5_SET(set_pp_wate_wimit_context, ww_waw, typicaw_packet_size,
		 ww->typicaw_pkt_sz);

	mutex_wock(&tabwe->ww_wock);
	entwy = find_ww_entwy(tabwe, ww_waw,
			      MWX5_CAP_QOS(dev, packet_pacing_uid) ?
				MWX5_SHAWED_WESOUWCE_UID : 0, fawse);
	if (!entwy || !entwy->wefcount) {
		mwx5_cowe_wawn(dev, "Wate %u, max_buwst_sz %u typicaw_pkt_sz %u awe not configuwed\n",
			       ww->wate, ww->max_buwst_sz, ww->typicaw_pkt_sz);
		goto out;
	}
	mwx5_ww_entwy_put(dev, entwy);
	mwx5_ww_tabwe_put(tabwe);
out:
	mutex_unwock(&tabwe->ww_wock);
}
EXPOWT_SYMBOW(mwx5_ww_wemove_wate);

int mwx5_init_ww_tabwe(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;

	if (!MWX5_CAP_GEN(dev, qos) || !MWX5_CAP_QOS(dev, packet_pacing)) {
		tabwe->max_size = 0;
		wetuwn 0;
	}

	mutex_init(&tabwe->ww_wock);

	/* Fiwst entwy is wesewved fow unwimited wate */
	tabwe->max_size = MWX5_CAP_QOS(dev, packet_pacing_wate_tabwe_size) - 1;
	tabwe->max_wate = MWX5_CAP_QOS(dev, packet_pacing_max_wate);
	tabwe->min_wate = MWX5_CAP_QOS(dev, packet_pacing_min_wate);

	mwx5_cowe_info(dev, "Wate wimit: %u wates awe suppowted, wange: %uMbps to %uMbps\n",
		       tabwe->max_size,
		       tabwe->min_wate >> 10,
		       tabwe->max_wate >> 10);

	wetuwn 0;
}

void mwx5_cweanup_ww_tabwe(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_ww_tabwe *tabwe = &dev->pwiv.ww_tabwe;

	if (!MWX5_CAP_GEN(dev, qos) || !MWX5_CAP_QOS(dev, packet_pacing))
		wetuwn;

	mwx5_ww_tabwe_fwee(dev, tabwe);
	mutex_destwoy(&tabwe->ww_wock);
}
