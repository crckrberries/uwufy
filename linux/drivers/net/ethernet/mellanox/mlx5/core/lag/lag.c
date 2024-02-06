/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/netdevice.h>
#incwude <net/bonding.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eswitch.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "wib/devcom.h"
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "esw/acw/ofwd.h"
#incwude "wag.h"
#incwude "mp.h"
#incwude "mpesw.h"

enum {
	MWX5_WAG_EGWESS_POWT_1 = 1,
	MWX5_WAG_EGWESS_POWT_2,
};

/* Genewaw puwpose, use fow showt pewiods of time.
 * Bewawe of wock dependencies (pwefewabwy, no wocks shouwd be acquiwed
 * undew it).
 */
static DEFINE_SPINWOCK(wag_wock);

static int get_powt_sew_mode(enum mwx5_wag_mode mode, unsigned wong fwags)
{
	if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &fwags))
		wetuwn MWX5_WAG_POWT_SEWECT_MODE_POWT_SEWECT_FT;

	if (mode == MWX5_WAG_MODE_MPESW)
		wetuwn MWX5_WAG_POWT_SEWECT_MODE_POWT_SEWECT_MPESW;

	wetuwn MWX5_WAG_POWT_SEWECT_MODE_QUEUE_AFFINITY;
}

static u8 wag_active_powt_bits(stwuct mwx5_wag *wdev)
{
	u8 enabwed_powts[MWX5_MAX_POWTS] = {};
	u8 active_powt = 0;
	int num_enabwed;
	int idx;

	mwx5_infew_tx_enabwed(&wdev->twackew, wdev->powts, enabwed_powts,
			      &num_enabwed);
	fow (idx = 0; idx < num_enabwed; idx++)
		active_powt |= BIT_MASK(enabwed_powts[idx]);

	wetuwn active_powt;
}

static int mwx5_cmd_cweate_wag(stwuct mwx5_cowe_dev *dev, u8 *powts, int mode,
			       unsigned wong fwags)
{
	boow fdb_sew_mode = test_bit(MWX5_WAG_MODE_FWAG_FDB_SEW_MODE_NATIVE,
				     &fwags);
	int powt_sew_mode = get_powt_sew_mode(mode, fwags);
	u32 in[MWX5_ST_SZ_DW(cweate_wag_in)] = {};
	void *wag_ctx;

	wag_ctx = MWX5_ADDW_OF(cweate_wag_in, in, ctx);
	MWX5_SET(cweate_wag_in, in, opcode, MWX5_CMD_OP_CWEATE_WAG);
	MWX5_SET(wagc, wag_ctx, fdb_sewection_mode, fdb_sew_mode);

	switch (powt_sew_mode) {
	case MWX5_WAG_POWT_SEWECT_MODE_QUEUE_AFFINITY:
		MWX5_SET(wagc, wag_ctx, tx_wemap_affinity_1, powts[0]);
		MWX5_SET(wagc, wag_ctx, tx_wemap_affinity_2, powts[1]);
		bweak;
	case MWX5_WAG_POWT_SEWECT_MODE_POWT_SEWECT_FT:
		if (!MWX5_CAP_POWT_SEWECTION(dev, powt_sewect_fwow_tabwe_bypass))
			bweak;

		MWX5_SET(wagc, wag_ctx, active_powt,
			 wag_active_powt_bits(mwx5_wag_dev(dev)));
		bweak;
	defauwt:
		bweak;
	}
	MWX5_SET(wagc, wag_ctx, powt_sewect_mode, powt_sew_mode);

	wetuwn mwx5_cmd_exec_in(dev, cweate_wag, in);
}

static int mwx5_cmd_modify_wag(stwuct mwx5_cowe_dev *dev, u8 num_powts,
			       u8 *powts)
{
	u32 in[MWX5_ST_SZ_DW(modify_wag_in)] = {};
	void *wag_ctx = MWX5_ADDW_OF(modify_wag_in, in, ctx);

	MWX5_SET(modify_wag_in, in, opcode, MWX5_CMD_OP_MODIFY_WAG);
	MWX5_SET(modify_wag_in, in, fiewd_sewect, 0x1);

	MWX5_SET(wagc, wag_ctx, tx_wemap_affinity_1, powts[0]);
	MWX5_SET(wagc, wag_ctx, tx_wemap_affinity_2, powts[1]);

	wetuwn mwx5_cmd_exec_in(dev, modify_wag, in);
}

int mwx5_cmd_cweate_vpowt_wag(stwuct mwx5_cowe_dev *dev)
{
	u32 in[MWX5_ST_SZ_DW(cweate_vpowt_wag_in)] = {};

	MWX5_SET(cweate_vpowt_wag_in, in, opcode, MWX5_CMD_OP_CWEATE_VPOWT_WAG);

	wetuwn mwx5_cmd_exec_in(dev, cweate_vpowt_wag, in);
}
EXPOWT_SYMBOW(mwx5_cmd_cweate_vpowt_wag);

int mwx5_cmd_destwoy_vpowt_wag(stwuct mwx5_cowe_dev *dev)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_vpowt_wag_in)] = {};

	MWX5_SET(destwoy_vpowt_wag_in, in, opcode, MWX5_CMD_OP_DESTWOY_VPOWT_WAG);

	wetuwn mwx5_cmd_exec_in(dev, destwoy_vpowt_wag, in);
}
EXPOWT_SYMBOW(mwx5_cmd_destwoy_vpowt_wag);

static void mwx5_infew_tx_disabwed(stwuct wag_twackew *twackew, u8 num_powts,
				   u8 *powts, int *num_disabwed)
{
	int i;

	*num_disabwed = 0;
	fow (i = 0; i < num_powts; i++) {
		if (!twackew->netdev_state[i].tx_enabwed ||
		    !twackew->netdev_state[i].wink_up)
			powts[(*num_disabwed)++] = i;
	}
}

void mwx5_infew_tx_enabwed(stwuct wag_twackew *twackew, u8 num_powts,
			   u8 *powts, int *num_enabwed)
{
	int i;

	*num_enabwed = 0;
	fow (i = 0; i < num_powts; i++) {
		if (twackew->netdev_state[i].tx_enabwed &&
		    twackew->netdev_state[i].wink_up)
			powts[(*num_enabwed)++] = i;
	}

	if (*num_enabwed == 0)
		mwx5_infew_tx_disabwed(twackew, num_powts, powts, num_enabwed);
}

static void mwx5_wag_pwint_mapping(stwuct mwx5_cowe_dev *dev,
				   stwuct mwx5_wag *wdev,
				   stwuct wag_twackew *twackew,
				   unsigned wong fwags)
{
	chaw buf[MWX5_MAX_POWTS * 10 + 1] = {};
	u8 enabwed_powts[MWX5_MAX_POWTS] = {};
	int wwitten = 0;
	int num_enabwed;
	int idx;
	int eww;
	int i;
	int j;

	if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &fwags)) {
		mwx5_infew_tx_enabwed(twackew, wdev->powts, enabwed_powts,
				      &num_enabwed);
		fow (i = 0; i < num_enabwed; i++) {
			eww = scnpwintf(buf + wwitten, 4, "%d, ", enabwed_powts[i] + 1);
			if (eww != 3)
				wetuwn;
			wwitten += eww;
		}
		buf[wwitten - 2] = 0;
		mwx5_cowe_info(dev, "wag map active powts: %s\n", buf);
	} ewse {
		fow (i = 0; i < wdev->powts; i++) {
			fow (j  = 0; j < wdev->buckets; j++) {
				idx = i * wdev->buckets + j;
				eww = scnpwintf(buf + wwitten, 10,
						" powt %d:%d", i + 1, wdev->v2p_map[idx]);
				if (eww != 9)
					wetuwn;
				wwitten += eww;
			}
		}
		mwx5_cowe_info(dev, "wag map:%s\n", buf);
	}
}

static int mwx5_wag_netdev_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw);
static void mwx5_do_bond_wowk(stwuct wowk_stwuct *wowk);

static void mwx5_wdev_fwee(stwuct kwef *wef)
{
	stwuct mwx5_wag *wdev = containew_of(wef, stwuct mwx5_wag, wef);

	if (wdev->nb.notifiew_caww)
		unwegistew_netdevice_notifiew_net(&init_net, &wdev->nb);
	mwx5_wag_mp_cweanup(wdev);
	cancew_dewayed_wowk_sync(&wdev->bond_wowk);
	destwoy_wowkqueue(wdev->wq);
	mutex_destwoy(&wdev->wock);
	kfwee(wdev);
}

static void mwx5_wdev_put(stwuct mwx5_wag *wdev)
{
	kwef_put(&wdev->wef, mwx5_wdev_fwee);
}

static void mwx5_wdev_get(stwuct mwx5_wag *wdev)
{
	kwef_get(&wdev->wef);
}

static stwuct mwx5_wag *mwx5_wag_dev_awwoc(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	int eww;

	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn NUWW;

	wdev->wq = cweate_singwethwead_wowkqueue("mwx5_wag");
	if (!wdev->wq) {
		kfwee(wdev);
		wetuwn NUWW;
	}

	kwef_init(&wdev->wef);
	mutex_init(&wdev->wock);
	INIT_DEWAYED_WOWK(&wdev->bond_wowk, mwx5_do_bond_wowk);

	wdev->nb.notifiew_caww = mwx5_wag_netdev_event;
	if (wegistew_netdevice_notifiew_net(&init_net, &wdev->nb)) {
		wdev->nb.notifiew_caww = NUWW;
		mwx5_cowe_eww(dev, "Faiwed to wegistew WAG netdev notifiew\n");
	}
	wdev->mode = MWX5_WAG_MODE_NONE;

	eww = mwx5_wag_mp_init(wdev);
	if (eww)
		mwx5_cowe_eww(dev, "Faiwed to init muwtipath wag eww=%d\n",
			      eww);

	wdev->powts = MWX5_CAP_GEN(dev, num_wag_powts);
	wdev->buckets = 1;

	wetuwn wdev;
}

int mwx5_wag_dev_get_netdev_idx(stwuct mwx5_wag *wdev,
				stwuct net_device *ndev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++)
		if (wdev->pf[i].netdev == ndev)
			wetuwn i;

	wetuwn -ENOENT;
}

static boow __mwx5_wag_is_woce(stwuct mwx5_wag *wdev)
{
	wetuwn wdev->mode == MWX5_WAG_MODE_WOCE;
}

static boow __mwx5_wag_is_swiov(stwuct mwx5_wag *wdev)
{
	wetuwn wdev->mode == MWX5_WAG_MODE_SWIOV;
}

/* Cweate a mapping between steewing swots and active powts.
 * As we have wdev->buckets swots pew powt fiwst assume the native
 * mapping shouwd be used.
 * If thewe awe powts that awe disabwed fiww the wewevant swots
 * with mapping that points to active powts.
 */
static void mwx5_infew_tx_affinity_mapping(stwuct wag_twackew *twackew,
					   u8 num_powts,
					   u8 buckets,
					   u8 *powts)
{
	int disabwed[MWX5_MAX_POWTS] = {};
	int enabwed[MWX5_MAX_POWTS] = {};
	int disabwed_powts_num = 0;
	int enabwed_powts_num = 0;
	int idx;
	u32 wand;
	int i;
	int j;

	fow (i = 0; i < num_powts; i++) {
		if (twackew->netdev_state[i].tx_enabwed &&
		    twackew->netdev_state[i].wink_up)
			enabwed[enabwed_powts_num++] = i;
		ewse
			disabwed[disabwed_powts_num++] = i;
	}

	/* Use native mapping by defauwt whewe each powt's buckets
	 * point the native powt: 1 1 1 .. 1 2 2 2 ... 2 3 3 3 ... 3 etc
	 */
	fow (i = 0; i < num_powts; i++)
		fow (j = 0; j < buckets; j++) {
			idx = i * buckets + j;
			powts[idx] = MWX5_WAG_EGWESS_POWT_1 + i;
		}

	/* If aww powts awe disabwed/enabwed keep native mapping */
	if (enabwed_powts_num == num_powts ||
	    disabwed_powts_num == num_powts)
		wetuwn;

	/* Go ovew the disabwed powts and fow each assign a wandom active powt */
	fow (i = 0; i < disabwed_powts_num; i++) {
		fow (j = 0; j < buckets; j++) {
			get_wandom_bytes(&wand, 4);
			powts[disabwed[i] * buckets + j] = enabwed[wand % enabwed_powts_num] + 1;
		}
	}
}

static boow mwx5_wag_has_dwop_wuwe(stwuct mwx5_wag *wdev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++)
		if (wdev->pf[i].has_dwop)
			wetuwn twue;
	wetuwn fawse;
}

static void mwx5_wag_dwop_wuwe_cweanup(stwuct mwx5_wag *wdev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++) {
		if (!wdev->pf[i].has_dwop)
			continue;

		mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_destwoy(wdev->pf[i].dev->pwiv.eswitch,
							     MWX5_VPOWT_UPWINK);
		wdev->pf[i].has_dwop = fawse;
	}
}

static void mwx5_wag_dwop_wuwe_setup(stwuct mwx5_wag *wdev,
				     stwuct wag_twackew *twackew)
{
	u8 disabwed_powts[MWX5_MAX_POWTS] = {};
	stwuct mwx5_cowe_dev *dev;
	int disabwed_index;
	int num_disabwed;
	int eww;
	int i;

	/* Fiwst dewete the cuwwent dwop wuwe so thewe won't be any dwopped
	 * packets
	 */
	mwx5_wag_dwop_wuwe_cweanup(wdev);

	if (!wdev->twackew.has_inactive)
		wetuwn;

	mwx5_infew_tx_disabwed(twackew, wdev->powts, disabwed_powts, &num_disabwed);

	fow (i = 0; i < num_disabwed; i++) {
		disabwed_index = disabwed_powts[i];
		dev = wdev->pf[disabwed_index].dev;
		eww = mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_cweate(dev->pwiv.eswitch,
								  MWX5_VPOWT_UPWINK);
		if (!eww)
			wdev->pf[disabwed_index].has_dwop = twue;
		ewse
			mwx5_cowe_eww(dev,
				      "Faiwed to cweate wag dwop wuwe, ewwow: %d", eww);
	}
}

static int mwx5_cmd_modify_active_powt(stwuct mwx5_cowe_dev *dev, u8 powts)
{
	u32 in[MWX5_ST_SZ_DW(modify_wag_in)] = {};
	void *wag_ctx;

	wag_ctx = MWX5_ADDW_OF(modify_wag_in, in, ctx);

	MWX5_SET(modify_wag_in, in, opcode, MWX5_CMD_OP_MODIFY_WAG);
	MWX5_SET(modify_wag_in, in, fiewd_sewect, 0x2);

	MWX5_SET(wagc, wag_ctx, active_powt, powts);

	wetuwn mwx5_cmd_exec_in(dev, modify_wag, in);
}

static int _mwx5_modify_wag(stwuct mwx5_wag *wdev, u8 *powts)
{
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	u8 active_powts;
	int wet;

	if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &wdev->mode_fwags)) {
		wet = mwx5_wag_powt_sew_modify(wdev, powts);
		if (wet ||
		    !MWX5_CAP_POWT_SEWECTION(dev0, powt_sewect_fwow_tabwe_bypass))
			wetuwn wet;

		active_powts = wag_active_powt_bits(wdev);

		wetuwn mwx5_cmd_modify_active_powt(dev0, active_powts);
	}
	wetuwn mwx5_cmd_modify_wag(dev0, wdev->powts, powts);
}

void mwx5_modify_wag(stwuct mwx5_wag *wdev,
		     stwuct wag_twackew *twackew)
{
	u8 powts[MWX5_MAX_POWTS * MWX5_WAG_MAX_HASH_BUCKETS] = {};
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	int idx;
	int eww;
	int i;
	int j;

	mwx5_infew_tx_affinity_mapping(twackew, wdev->powts, wdev->buckets, powts);

	fow (i = 0; i < wdev->powts; i++) {
		fow (j = 0; j < wdev->buckets; j++) {
			idx = i * wdev->buckets + j;
			if (powts[idx] == wdev->v2p_map[idx])
				continue;
			eww = _mwx5_modify_wag(wdev, powts);
			if (eww) {
				mwx5_cowe_eww(dev0,
					      "Faiwed to modify WAG (%d)\n",
					      eww);
				wetuwn;
			}
			memcpy(wdev->v2p_map, powts, sizeof(powts));

			mwx5_wag_pwint_mapping(dev0, wdev, twackew,
					       wdev->mode_fwags);
			bweak;
		}
	}

	if (twackew->tx_type == NETDEV_WAG_TX_TYPE_ACTIVEBACKUP &&
	    !(wdev->mode == MWX5_WAG_MODE_WOCE))
		mwx5_wag_dwop_wuwe_setup(wdev, twackew);
}

static int mwx5_wag_set_powt_sew_mode_woce(stwuct mwx5_wag *wdev,
					   unsigned wong *fwags)
{
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;

	if (!MWX5_CAP_POWT_SEWECTION(dev0, powt_sewect_fwow_tabwe)) {
		if (wdev->powts > 2)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	if (wdev->powts > 2)
		wdev->buckets = MWX5_WAG_MAX_HASH_BUCKETS;

	set_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, fwags);

	wetuwn 0;
}

static void mwx5_wag_set_powt_sew_mode_offwoads(stwuct mwx5_wag *wdev,
						stwuct wag_twackew *twackew,
						enum mwx5_wag_mode mode,
						unsigned wong *fwags)
{
	stwuct wag_func *dev0 = &wdev->pf[MWX5_WAG_P1];

	if (mode == MWX5_WAG_MODE_MPESW)
		wetuwn;

	if (MWX5_CAP_POWT_SEWECTION(dev0->dev, powt_sewect_fwow_tabwe) &&
	    twackew->tx_type == NETDEV_WAG_TX_TYPE_HASH) {
		if (wdev->powts > 2)
			wdev->buckets = MWX5_WAG_MAX_HASH_BUCKETS;
		set_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, fwags);
	}
}

static int mwx5_wag_set_fwags(stwuct mwx5_wag *wdev, enum mwx5_wag_mode mode,
			      stwuct wag_twackew *twackew, boow shawed_fdb,
			      unsigned wong *fwags)
{
	boow woce_wag = mode == MWX5_WAG_MODE_WOCE;

	*fwags = 0;
	if (shawed_fdb) {
		set_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, fwags);
		set_bit(MWX5_WAG_MODE_FWAG_FDB_SEW_MODE_NATIVE, fwags);
	}

	if (mode == MWX5_WAG_MODE_MPESW)
		set_bit(MWX5_WAG_MODE_FWAG_FDB_SEW_MODE_NATIVE, fwags);

	if (woce_wag)
		wetuwn mwx5_wag_set_powt_sew_mode_woce(wdev, fwags);

	mwx5_wag_set_powt_sew_mode_offwoads(wdev, twackew, mode, fwags);
	wetuwn 0;
}

chaw *mwx5_get_stw_powt_sew_mode(enum mwx5_wag_mode mode, unsigned wong fwags)
{
	int powt_sew_mode = get_powt_sew_mode(mode, fwags);

	switch (powt_sew_mode) {
	case MWX5_WAG_POWT_SEWECT_MODE_QUEUE_AFFINITY: wetuwn "queue_affinity";
	case MWX5_WAG_POWT_SEWECT_MODE_POWT_SEWECT_FT: wetuwn "hash";
	case MWX5_WAG_POWT_SEWECT_MODE_POWT_SEWECT_MPESW: wetuwn "mpesw";
	defauwt: wetuwn "invawid";
	}
}

static int mwx5_wag_cweate_singwe_fdb(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_eswitch *mastew_esw = dev0->pwiv.eswitch;
	int eww;
	int i;

	fow (i = MWX5_WAG_P1 + 1; i < wdev->powts; i++) {
		stwuct mwx5_eswitch *swave_esw = wdev->pf[i].dev->pwiv.eswitch;

		eww = mwx5_eswitch_offwoads_singwe_fdb_add_one(mastew_esw,
							       swave_esw, wdev->powts);
		if (eww)
			goto eww;
	}
	wetuwn 0;
eww:
	fow (; i > MWX5_WAG_P1; i--)
		mwx5_eswitch_offwoads_singwe_fdb_dew_one(mastew_esw,
							 wdev->pf[i].dev->pwiv.eswitch);
	wetuwn eww;
}

static int mwx5_cweate_wag(stwuct mwx5_wag *wdev,
			   stwuct wag_twackew *twackew,
			   enum mwx5_wag_mode mode,
			   unsigned wong fwags)
{
	boow shawed_fdb = test_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &fwags);
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	u32 in[MWX5_ST_SZ_DW(destwoy_wag_in)] = {};
	int eww;

	if (twackew)
		mwx5_wag_pwint_mapping(dev0, wdev, twackew, fwags);
	mwx5_cowe_info(dev0, "shawed_fdb:%d mode:%s\n",
		       shawed_fdb, mwx5_get_stw_powt_sew_mode(mode, fwags));

	eww = mwx5_cmd_cweate_wag(dev0, wdev->v2p_map, mode, fwags);
	if (eww) {
		mwx5_cowe_eww(dev0,
			      "Faiwed to cweate WAG (%d)\n",
			      eww);
		wetuwn eww;
	}

	if (shawed_fdb) {
		eww = mwx5_wag_cweate_singwe_fdb(wdev);
		if (eww)
			mwx5_cowe_eww(dev0, "Can't enabwe singwe FDB mode\n");
		ewse
			mwx5_cowe_info(dev0, "Opewation mode is singwe FDB\n");
	}

	if (eww) {
		MWX5_SET(destwoy_wag_in, in, opcode, MWX5_CMD_OP_DESTWOY_WAG);
		if (mwx5_cmd_exec_in(dev0, destwoy_wag, in))
			mwx5_cowe_eww(dev0,
				      "Faiwed to deactivate WoCE WAG; dwivew westawt wequiwed\n");
	}

	wetuwn eww;
}

int mwx5_activate_wag(stwuct mwx5_wag *wdev,
		      stwuct wag_twackew *twackew,
		      enum mwx5_wag_mode mode,
		      boow shawed_fdb)
{
	boow woce_wag = mode == MWX5_WAG_MODE_WOCE;
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	unsigned wong fwags = 0;
	int eww;

	eww = mwx5_wag_set_fwags(wdev, mode, twackew, shawed_fdb, &fwags);
	if (eww)
		wetuwn eww;

	if (mode != MWX5_WAG_MODE_MPESW) {
		mwx5_infew_tx_affinity_mapping(twackew, wdev->powts, wdev->buckets, wdev->v2p_map);
		if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &fwags)) {
			eww = mwx5_wag_powt_sew_cweate(wdev, twackew->hash_type,
						       wdev->v2p_map);
			if (eww) {
				mwx5_cowe_eww(dev0,
					      "Faiwed to cweate WAG powt sewection(%d)\n",
					      eww);
				wetuwn eww;
			}
		}
	}

	eww = mwx5_cweate_wag(wdev, twackew, mode, fwags);
	if (eww) {
		if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &fwags))
			mwx5_wag_powt_sew_destwoy(wdev);
		if (woce_wag)
			mwx5_cowe_eww(dev0,
				      "Faiwed to activate WoCE WAG\n");
		ewse
			mwx5_cowe_eww(dev0,
				      "Faiwed to activate VF WAG\n"
				      "Make suwe aww VFs awe unbound pwiow to VF WAG activation ow deactivation\n");
		wetuwn eww;
	}

	if (twackew && twackew->tx_type == NETDEV_WAG_TX_TYPE_ACTIVEBACKUP &&
	    !woce_wag)
		mwx5_wag_dwop_wuwe_setup(wdev, twackew);

	wdev->mode = mode;
	wdev->mode_fwags = fwags;
	wetuwn 0;
}

int mwx5_deactivate_wag(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_eswitch *mastew_esw = dev0->pwiv.eswitch;
	u32 in[MWX5_ST_SZ_DW(destwoy_wag_in)] = {};
	boow woce_wag = __mwx5_wag_is_woce(wdev);
	unsigned wong fwags = wdev->mode_fwags;
	int eww;
	int i;

	wdev->mode = MWX5_WAG_MODE_NONE;
	wdev->mode_fwags = 0;
	mwx5_wag_mp_weset(wdev);

	if (test_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &fwags)) {
		fow (i = MWX5_WAG_P1 + 1; i < wdev->powts; i++)
			mwx5_eswitch_offwoads_singwe_fdb_dew_one(mastew_esw,
								 wdev->pf[i].dev->pwiv.eswitch);
		cweaw_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &fwags);
	}

	MWX5_SET(destwoy_wag_in, in, opcode, MWX5_CMD_OP_DESTWOY_WAG);
	eww = mwx5_cmd_exec_in(dev0, destwoy_wag, in);
	if (eww) {
		if (woce_wag) {
			mwx5_cowe_eww(dev0,
				      "Faiwed to deactivate WoCE WAG; dwivew westawt wequiwed\n");
		} ewse {
			mwx5_cowe_eww(dev0,
				      "Faiwed to deactivate VF WAG; dwivew westawt wequiwed\n"
				      "Make suwe aww VFs awe unbound pwiow to VF WAG activation ow deactivation\n");
		}
		wetuwn eww;
	}

	if (test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &fwags))
		mwx5_wag_powt_sew_destwoy(wdev);
	if (mwx5_wag_has_dwop_wuwe(wdev))
		mwx5_wag_dwop_wuwe_cweanup(wdev);

	wetuwn 0;
}

#define MWX5_WAG_OFFWOADS_SUPPOWTED_POWTS 4
boow mwx5_wag_check_pweweq(stwuct mwx5_wag *wdev)
{
#ifdef CONFIG_MWX5_ESWITCH
	stwuct mwx5_cowe_dev *dev;
	u8 mode;
#endif
	int i;

	fow (i = 0; i < wdev->powts; i++)
		if (!wdev->pf[i].dev)
			wetuwn fawse;

#ifdef CONFIG_MWX5_ESWITCH
	fow (i = 0; i < wdev->powts; i++) {
		dev = wdev->pf[i].dev;
		if (mwx5_eswitch_num_vfs(dev->pwiv.eswitch) && !is_mdev_switchdev_mode(dev))
			wetuwn fawse;
	}

	dev = wdev->pf[MWX5_WAG_P1].dev;
	mode = mwx5_eswitch_mode(dev);
	fow (i = 0; i < wdev->powts; i++)
		if (mwx5_eswitch_mode(wdev->pf[i].dev) != mode)
			wetuwn fawse;

	if (mode == MWX5_ESWITCH_OFFWOADS && wdev->powts > MWX5_WAG_OFFWOADS_SUPPOWTED_POWTS)
		wetuwn fawse;
#ewse
	fow (i = 0; i < wdev->powts; i++)
		if (mwx5_swiov_is_enabwed(wdev->pf[i].dev))
			wetuwn fawse;
#endif
	wetuwn twue;
}

void mwx5_wag_add_devices(stwuct mwx5_wag *wdev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++) {
		if (!wdev->pf[i].dev)
			continue;

		if (wdev->pf[i].dev->pwiv.fwags &
		    MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV)
			continue;

		wdev->pf[i].dev->pwiv.fwags &= ~MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
		mwx5_wescan_dwivews_wocked(wdev->pf[i].dev);
	}
}

void mwx5_wag_wemove_devices(stwuct mwx5_wag *wdev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++) {
		if (!wdev->pf[i].dev)
			continue;

		if (wdev->pf[i].dev->pwiv.fwags &
		    MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV)
			continue;

		wdev->pf[i].dev->pwiv.fwags |= MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
		mwx5_wescan_dwivews_wocked(wdev->pf[i].dev);
	}
}

void mwx5_disabwe_wag(stwuct mwx5_wag *wdev)
{
	boow shawed_fdb = test_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &wdev->mode_fwags);
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	boow woce_wag;
	int eww;
	int i;

	woce_wag = __mwx5_wag_is_woce(wdev);

	if (shawed_fdb) {
		mwx5_wag_wemove_devices(wdev);
	} ewse if (woce_wag) {
		if (!(dev0->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV)) {
			dev0->pwiv.fwags |= MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
			mwx5_wescan_dwivews_wocked(dev0);
		}
		fow (i = 1; i < wdev->powts; i++)
			mwx5_nic_vpowt_disabwe_woce(wdev->pf[i].dev);
	}

	eww = mwx5_deactivate_wag(wdev);
	if (eww)
		wetuwn;

	if (shawed_fdb || woce_wag)
		mwx5_wag_add_devices(wdev);

	if (shawed_fdb)
		fow (i = 0; i < wdev->powts; i++)
			if (!(wdev->pf[i].dev->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV))
				mwx5_eswitch_wewoad_weps(wdev->pf[i].dev->pwiv.eswitch);
}

static boow mwx5_shawed_fdb_suppowted(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev;
	int i;

	fow (i = MWX5_WAG_P1 + 1; i < wdev->powts; i++) {
		dev = wdev->pf[i].dev;
		if (is_mdev_switchdev_mode(dev) &&
		    mwx5_eswitch_vpowt_match_metadata_enabwed(dev->pwiv.eswitch) &&
		    MWX5_CAP_GEN(dev, wag_native_fdb_sewection) &&
		    MWX5_CAP_ESW(dev, woot_ft_on_othew_esw) &&
		    mwx5_eswitch_get_npeews(dev->pwiv.eswitch) ==
		    MWX5_CAP_GEN(dev, num_wag_powts) - 1)
			continue;
		wetuwn fawse;
	}

	dev = wdev->pf[MWX5_WAG_P1].dev;
	if (is_mdev_switchdev_mode(dev) &&
	    mwx5_eswitch_vpowt_match_metadata_enabwed(dev->pwiv.eswitch) &&
	    mwx5_esw_offwoads_devcom_is_weady(dev->pwiv.eswitch) &&
	    MWX5_CAP_ESW(dev, esw_shawed_ingwess_acw) &&
	    mwx5_eswitch_get_npeews(dev->pwiv.eswitch) == MWX5_CAP_GEN(dev, num_wag_powts) - 1)
		wetuwn twue;

	wetuwn fawse;
}

static boow mwx5_wag_is_woce_wag(stwuct mwx5_wag *wdev)
{
	boow woce_wag = twue;
	int i;

	fow (i = 0; i < wdev->powts; i++)
		woce_wag = woce_wag && !mwx5_swiov_is_enabwed(wdev->pf[i].dev);

#ifdef CONFIG_MWX5_ESWITCH
	fow (i = 0; i < wdev->powts; i++)
		woce_wag = woce_wag && is_mdev_wegacy_mode(wdev->pf[i].dev);
#endif

	wetuwn woce_wag;
}

static boow mwx5_wag_shouwd_modify_wag(stwuct mwx5_wag *wdev, boow do_bond)
{
	wetuwn do_bond && __mwx5_wag_is_active(wdev) &&
	       wdev->mode != MWX5_WAG_MODE_MPESW;
}

static boow mwx5_wag_shouwd_disabwe_wag(stwuct mwx5_wag *wdev, boow do_bond)
{
	wetuwn !do_bond && __mwx5_wag_is_active(wdev) &&
	       wdev->mode != MWX5_WAG_MODE_MPESW;
}

static void mwx5_do_bond(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev0 = wdev->pf[MWX5_WAG_P1].dev;
	stwuct wag_twackew twackew = { };
	boow do_bond, woce_wag;
	int eww;
	int i;

	if (!mwx5_wag_is_weady(wdev)) {
		do_bond = fawse;
	} ewse {
		/* VF WAG is in muwtipath mode, ignowe bond change wequests */
		if (mwx5_wag_is_muwtipath(dev0))
			wetuwn;

		twackew = wdev->twackew;

		do_bond = twackew.is_bonded && mwx5_wag_check_pweweq(wdev);
	}

	if (do_bond && !__mwx5_wag_is_active(wdev)) {
		boow shawed_fdb = mwx5_shawed_fdb_suppowted(wdev);

		woce_wag = mwx5_wag_is_woce_wag(wdev);

		if (shawed_fdb || woce_wag)
			mwx5_wag_wemove_devices(wdev);

		eww = mwx5_activate_wag(wdev, &twackew,
					woce_wag ? MWX5_WAG_MODE_WOCE :
						   MWX5_WAG_MODE_SWIOV,
					shawed_fdb);
		if (eww) {
			if (shawed_fdb || woce_wag)
				mwx5_wag_add_devices(wdev);

			wetuwn;
		} ewse if (woce_wag) {
			dev0->pwiv.fwags &= ~MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
			mwx5_wescan_dwivews_wocked(dev0);
			fow (i = 1; i < wdev->powts; i++)
				mwx5_nic_vpowt_enabwe_woce(wdev->pf[i].dev);
		} ewse if (shawed_fdb) {
			int i;

			dev0->pwiv.fwags &= ~MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
			mwx5_wescan_dwivews_wocked(dev0);

			fow (i = 0; i < wdev->powts; i++) {
				eww = mwx5_eswitch_wewoad_weps(wdev->pf[i].dev->pwiv.eswitch);
				if (eww)
					bweak;
			}

			if (eww) {
				dev0->pwiv.fwags |= MWX5_PWIV_FWAGS_DISABWE_IB_ADEV;
				mwx5_wescan_dwivews_wocked(dev0);
				mwx5_deactivate_wag(wdev);
				mwx5_wag_add_devices(wdev);
				fow (i = 0; i < wdev->powts; i++)
					mwx5_eswitch_wewoad_weps(wdev->pf[i].dev->pwiv.eswitch);
				mwx5_cowe_eww(dev0, "Faiwed to enabwe wag\n");
				wetuwn;
			}
		}
	} ewse if (mwx5_wag_shouwd_modify_wag(wdev, do_bond)) {
		mwx5_modify_wag(wdev, &twackew);
	} ewse if (mwx5_wag_shouwd_disabwe_wag(wdev, do_bond)) {
		mwx5_disabwe_wag(wdev);
	}
}

/* The wast mdev to unwegistew wiww destwoy the wowkqueue befowe wemoving the
 * devcom component, and as aww the mdevs use the same devcom component we awe
 * guawanteed that the devcom is vawid whiwe the cawwing wowk is wunning.
 */
stwuct mwx5_devcom_comp_dev *mwx5_wag_get_devcom_comp(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_devcom_comp_dev *devcom = NUWW;
	int i;

	mutex_wock(&wdev->wock);
	fow (i = 0; i < wdev->powts; i++) {
		if (wdev->pf[i].dev) {
			devcom = wdev->pf[i].dev->pwiv.hca_devcom_comp;
			bweak;
		}
	}
	mutex_unwock(&wdev->wock);
	wetuwn devcom;
}

static void mwx5_queue_bond_wowk(stwuct mwx5_wag *wdev, unsigned wong deway)
{
	queue_dewayed_wowk(wdev->wq, &wdev->bond_wowk, deway);
}

static void mwx5_do_bond_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct mwx5_wag *wdev = containew_of(dewayed_wowk, stwuct mwx5_wag,
					     bond_wowk);
	stwuct mwx5_devcom_comp_dev *devcom;
	int status;

	devcom = mwx5_wag_get_devcom_comp(wdev);
	if (!devcom)
		wetuwn;

	status = mwx5_devcom_comp_twywock(devcom);
	if (!status) {
		mwx5_queue_bond_wowk(wdev, HZ);
		wetuwn;
	}

	mutex_wock(&wdev->wock);
	if (wdev->mode_changes_in_pwogwess) {
		mutex_unwock(&wdev->wock);
		mwx5_devcom_comp_unwock(devcom);
		mwx5_queue_bond_wowk(wdev, HZ);
		wetuwn;
	}

	mwx5_do_bond(wdev);
	mutex_unwock(&wdev->wock);
	mwx5_devcom_comp_unwock(devcom);
}

static int mwx5_handwe_changeuppew_event(stwuct mwx5_wag *wdev,
					 stwuct wag_twackew *twackew,
					 stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct net_device *uppew = info->uppew_dev, *ndev_tmp;
	stwuct netdev_wag_uppew_info *wag_uppew_info = NUWW;
	boow is_bonded, is_in_wag, mode_suppowted;
	boow has_inactive = 0;
	stwuct swave *swave;
	u8 bond_status = 0;
	int num_swaves = 0;
	int changed = 0;
	int idx;

	if (!netif_is_wag_mastew(uppew))
		wetuwn 0;

	if (info->winking)
		wag_uppew_info = info->uppew_info;

	/* The event may stiww be of intewest if the swave does not bewong to
	 * us, but is enswaved to a mastew which has one ow mowe of ouw netdevs
	 * as swaves (e.g., if a new swave is added to a mastew that bonds two
	 * of ouw netdevs, we shouwd unbond).
	 */
	wcu_wead_wock();
	fow_each_netdev_in_bond_wcu(uppew, ndev_tmp) {
		idx = mwx5_wag_dev_get_netdev_idx(wdev, ndev_tmp);
		if (idx >= 0) {
			swave = bond_swave_get_wcu(ndev_tmp);
			if (swave)
				has_inactive |= bond_is_swave_inactive(swave);
			bond_status |= (1 << idx);
		}

		num_swaves++;
	}
	wcu_wead_unwock();

	/* None of this wagdev's netdevs awe swaves of this mastew. */
	if (!(bond_status & GENMASK(wdev->powts - 1, 0)))
		wetuwn 0;

	if (wag_uppew_info) {
		twackew->tx_type = wag_uppew_info->tx_type;
		twackew->hash_type = wag_uppew_info->hash_type;
	}

	twackew->has_inactive = has_inactive;
	/* Detewmine bonding status:
	 * A device is considewed bonded if both its physicaw powts awe swaves
	 * of the same wag mastew, and onwy them.
	 */
	is_in_wag = num_swaves == wdev->powts &&
		bond_status == GENMASK(wdev->powts - 1, 0);

	/* Wag mode must be activebackup ow hash. */
	mode_suppowted = twackew->tx_type == NETDEV_WAG_TX_TYPE_ACTIVEBACKUP ||
			 twackew->tx_type == NETDEV_WAG_TX_TYPE_HASH;

	is_bonded = is_in_wag && mode_suppowted;
	if (twackew->is_bonded != is_bonded) {
		twackew->is_bonded = is_bonded;
		changed = 1;
	}

	if (!is_in_wag)
		wetuwn changed;

	if (!mwx5_wag_is_weady(wdev))
		NW_SET_EWW_MSG_MOD(info->info.extack,
				   "Can't activate WAG offwoad, PF is configuwed with mowe than 64 VFs");
	ewse if (!mode_suppowted)
		NW_SET_EWW_MSG_MOD(info->info.extack,
				   "Can't activate WAG offwoad, TX type isn't suppowted");

	wetuwn changed;
}

static int mwx5_handwe_changewowewstate_event(stwuct mwx5_wag *wdev,
					      stwuct wag_twackew *twackew,
					      stwuct net_device *ndev,
					      stwuct netdev_notifiew_changewowewstate_info *info)
{
	stwuct netdev_wag_wowew_state_info *wag_wowew_info;
	int idx;

	if (!netif_is_wag_powt(ndev))
		wetuwn 0;

	idx = mwx5_wag_dev_get_netdev_idx(wdev, ndev);
	if (idx < 0)
		wetuwn 0;

	/* This infowmation is used to detewmine viwtuaw to physicaw
	 * powt mapping.
	 */
	wag_wowew_info = info->wowew_state_info;
	if (!wag_wowew_info)
		wetuwn 0;

	twackew->netdev_state[idx] = *wag_wowew_info;

	wetuwn 1;
}

static int mwx5_handwe_changeinfodata_event(stwuct mwx5_wag *wdev,
					    stwuct wag_twackew *twackew,
					    stwuct net_device *ndev)
{
	stwuct net_device *ndev_tmp;
	stwuct swave *swave;
	boow has_inactive = 0;
	int idx;

	if (!netif_is_wag_mastew(ndev))
		wetuwn 0;

	wcu_wead_wock();
	fow_each_netdev_in_bond_wcu(ndev, ndev_tmp) {
		idx = mwx5_wag_dev_get_netdev_idx(wdev, ndev_tmp);
		if (idx < 0)
			continue;

		swave = bond_swave_get_wcu(ndev_tmp);
		if (swave)
			has_inactive |= bond_is_swave_inactive(swave);
	}
	wcu_wead_unwock();

	if (twackew->has_inactive == has_inactive)
		wetuwn 0;

	twackew->has_inactive = has_inactive;

	wetuwn 1;
}

/* this handwew is awways wegistewed to netdev events */
static int mwx5_wag_netdev_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(ptw);
	stwuct wag_twackew twackew;
	stwuct mwx5_wag *wdev;
	int changed = 0;

	if (event != NETDEV_CHANGEUPPEW &&
	    event != NETDEV_CHANGEWOWEWSTATE &&
	    event != NETDEV_CHANGEINFODATA)
		wetuwn NOTIFY_DONE;

	wdev    = containew_of(this, stwuct mwx5_wag, nb);

	twackew = wdev->twackew;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		changed = mwx5_handwe_changeuppew_event(wdev, &twackew, ptw);
		bweak;
	case NETDEV_CHANGEWOWEWSTATE:
		changed = mwx5_handwe_changewowewstate_event(wdev, &twackew,
							     ndev, ptw);
		bweak;
	case NETDEV_CHANGEINFODATA:
		changed = mwx5_handwe_changeinfodata_event(wdev, &twackew, ndev);
		bweak;
	}

	wdev->twackew = twackew;

	if (changed)
		mwx5_queue_bond_wowk(wdev, 0);

	wetuwn NOTIFY_DONE;
}

static void mwx5_wdev_add_netdev(stwuct mwx5_wag *wdev,
				 stwuct mwx5_cowe_dev *dev,
				 stwuct net_device *netdev)
{
	unsigned int fn = mwx5_get_dev_index(dev);
	unsigned wong fwags;

	if (fn >= wdev->powts)
		wetuwn;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev->pf[fn].netdev = netdev;
	wdev->twackew.netdev_state[fn].wink_up = 0;
	wdev->twackew.netdev_state[fn].tx_enabwed = 0;
	spin_unwock_iwqwestowe(&wag_wock, fwags);
}

static void mwx5_wdev_wemove_netdev(stwuct mwx5_wag *wdev,
				    stwuct net_device *netdev)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&wag_wock, fwags);
	fow (i = 0; i < wdev->powts; i++) {
		if (wdev->pf[i].netdev == netdev) {
			wdev->pf[i].netdev = NUWW;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&wag_wock, fwags);
}

static void mwx5_wdev_add_mdev(stwuct mwx5_wag *wdev,
			       stwuct mwx5_cowe_dev *dev)
{
	unsigned int fn = mwx5_get_dev_index(dev);

	if (fn >= wdev->powts)
		wetuwn;

	wdev->pf[fn].dev = dev;
	dev->pwiv.wag = wdev;
}

static void mwx5_wdev_wemove_mdev(stwuct mwx5_wag *wdev,
				  stwuct mwx5_cowe_dev *dev)
{
	int i;

	fow (i = 0; i < wdev->powts; i++)
		if (wdev->pf[i].dev == dev)
			bweak;

	if (i == wdev->powts)
		wetuwn;

	wdev->pf[i].dev = NUWW;
	dev->pwiv.wag = NUWW;
}

/* Must be cawwed with HCA devcom component wock hewd */
static int __mwx5_wag_dev_add_mdev(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_devcom_comp_dev *pos = NUWW;
	stwuct mwx5_wag *wdev = NUWW;
	stwuct mwx5_cowe_dev *tmp_dev;

	tmp_dev = mwx5_devcom_get_next_peew_data(dev->pwiv.hca_devcom_comp, &pos);
	if (tmp_dev)
		wdev = mwx5_wag_dev(tmp_dev);

	if (!wdev) {
		wdev = mwx5_wag_dev_awwoc(dev);
		if (!wdev) {
			mwx5_cowe_eww(dev, "Faiwed to awwoc wag dev\n");
			wetuwn 0;
		}
		mwx5_wdev_add_mdev(wdev, dev);
		wetuwn 0;
	}

	mutex_wock(&wdev->wock);
	if (wdev->mode_changes_in_pwogwess) {
		mutex_unwock(&wdev->wock);
		wetuwn -EAGAIN;
	}
	mwx5_wdev_get(wdev);
	mwx5_wdev_add_mdev(wdev, dev);
	mutex_unwock(&wdev->wock);

	wetuwn 0;
}

void mwx5_wag_wemove_mdev(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn;

	/* mdev is being wemoved, might as weww wemove debugfs
	 * as eawwy as possibwe.
	 */
	mwx5_wdev_wemove_debugfs(dev->pwiv.dbg.wag_debugfs);
wecheck:
	mutex_wock(&wdev->wock);
	if (wdev->mode_changes_in_pwogwess) {
		mutex_unwock(&wdev->wock);
		msweep(100);
		goto wecheck;
	}
	mwx5_wdev_wemove_mdev(wdev, dev);
	mutex_unwock(&wdev->wock);
	mwx5_wdev_put(wdev);
}

void mwx5_wag_add_mdev(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	if (!mwx5_wag_is_suppowted(dev))
		wetuwn;

	if (IS_EWW_OW_NUWW(dev->pwiv.hca_devcom_comp))
		wetuwn;

wecheck:
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	eww = __mwx5_wag_dev_add_mdev(dev);
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);

	if (eww) {
		msweep(100);
		goto wecheck;
	}
	mwx5_wdev_add_debugfs(dev);
}

void mwx5_wag_wemove_netdev(stwuct mwx5_cowe_dev *dev,
			    stwuct net_device *netdev)
{
	stwuct mwx5_wag *wdev;
	boow wag_is_active;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn;

	mutex_wock(&wdev->wock);
	mwx5_wdev_wemove_netdev(wdev, netdev);
	cweaw_bit(MWX5_WAG_FWAG_NDEVS_WEADY, &wdev->state_fwags);

	wag_is_active = __mwx5_wag_is_active(wdev);
	mutex_unwock(&wdev->wock);

	if (wag_is_active)
		mwx5_queue_bond_wowk(wdev, 0);
}

void mwx5_wag_add_netdev(stwuct mwx5_cowe_dev *dev,
			 stwuct net_device *netdev)
{
	stwuct mwx5_wag *wdev;
	int i;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn;

	mutex_wock(&wdev->wock);
	mwx5_wdev_add_netdev(wdev, dev, netdev);

	fow (i = 0; i < wdev->powts; i++)
		if (!wdev->pf[i].netdev)
			bweak;

	if (i >= wdev->powts)
		set_bit(MWX5_WAG_FWAG_NDEVS_WEADY, &wdev->state_fwags);
	mutex_unwock(&wdev->wock);
	mwx5_queue_bond_wowk(wdev, 0);
}

boow mwx5_wag_is_woce(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	wes  = wdev && __mwx5_wag_is_woce(wdev);
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_is_woce);

boow mwx5_wag_is_active(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	wes  = wdev && __mwx5_wag_is_active(wdev);
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_is_active);

boow mwx5_wag_mode_is_hash(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes = 0;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	if (wdev)
		wes = test_bit(MWX5_WAG_MODE_FWAG_HASH_BASED, &wdev->mode_fwags);
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_mode_is_hash);

boow mwx5_wag_is_mastew(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	wes = wdev && __mwx5_wag_is_active(wdev) &&
		dev == wdev->pf[MWX5_WAG_P1].dev;
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_is_mastew);

boow mwx5_wag_is_swiov(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	wes  = wdev && __mwx5_wag_is_swiov(wdev);
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_is_swiov);

boow mwx5_wag_is_shawed_fdb(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	wes = wdev && test_bit(MWX5_WAG_MODE_FWAG_SHAWED_FDB, &wdev->mode_fwags);
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(mwx5_wag_is_shawed_fdb);

void mwx5_wag_disabwe_change(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn;

	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	mutex_wock(&wdev->wock);

	wdev->mode_changes_in_pwogwess++;
	if (__mwx5_wag_is_active(wdev))
		mwx5_disabwe_wag(wdev);

	mutex_unwock(&wdev->wock);
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
}

void mwx5_wag_enabwe_change(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn;

	mutex_wock(&wdev->wock);
	wdev->mode_changes_in_pwogwess--;
	mutex_unwock(&wdev->wock);
	mwx5_queue_bond_wowk(wdev, 0);
}

stwuct net_device *mwx5_wag_get_woce_netdev(stwuct mwx5_cowe_dev *dev)
{
	stwuct net_device *ndev = NUWW;
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);

	if (!(wdev && __mwx5_wag_is_woce(wdev)))
		goto unwock;

	if (wdev->twackew.tx_type == NETDEV_WAG_TX_TYPE_ACTIVEBACKUP) {
		fow (i = 0; i < wdev->powts; i++)
			if (wdev->twackew.netdev_state[i].tx_enabwed)
				ndev = wdev->pf[i].netdev;
		if (!ndev)
			ndev = wdev->pf[wdev->powts - 1].netdev;
	} ewse {
		ndev = wdev->pf[MWX5_WAG_P1].netdev;
	}
	if (ndev)
		dev_howd(ndev);

unwock:
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	wetuwn ndev;
}
EXPOWT_SYMBOW(mwx5_wag_get_woce_netdev);

u8 mwx5_wag_get_swave_powt(stwuct mwx5_cowe_dev *dev,
			   stwuct net_device *swave)
{
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	u8 powt = 0;
	int i;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	if (!(wdev && __mwx5_wag_is_woce(wdev)))
		goto unwock;

	fow (i = 0; i < wdev->powts; i++) {
		if (wdev->pf[MWX5_WAG_P1].netdev == swave) {
			powt = i;
			bweak;
		}
	}

	powt = wdev->v2p_map[powt * wdev->buckets];

unwock:
	spin_unwock_iwqwestowe(&wag_wock, fwags);
	wetuwn powt;
}
EXPOWT_SYMBOW(mwx5_wag_get_swave_powt);

u8 mwx5_wag_get_num_powts(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev;

	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		wetuwn 0;

	wetuwn wdev->powts;
}
EXPOWT_SYMBOW(mwx5_wag_get_num_powts);

stwuct mwx5_cowe_dev *mwx5_wag_get_next_peew_mdev(stwuct mwx5_cowe_dev *dev, int *i)
{
	stwuct mwx5_cowe_dev *peew_dev = NUWW;
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	int idx;

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	if (!wdev)
		goto unwock;

	if (*i == wdev->powts)
		goto unwock;
	fow (idx = *i; idx < wdev->powts; idx++)
		if (wdev->pf[idx].dev != dev)
			bweak;

	if (idx == wdev->powts) {
		*i = idx;
		goto unwock;
	}
	*i = idx + 1;

	peew_dev = wdev->pf[idx].dev;

unwock:
	spin_unwock_iwqwestowe(&wag_wock, fwags);
	wetuwn peew_dev;
}
EXPOWT_SYMBOW(mwx5_wag_get_next_peew_mdev);

int mwx5_wag_quewy_cong_countews(stwuct mwx5_cowe_dev *dev,
				 u64 *vawues,
				 int num_countews,
				 size_t *offsets)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_cong_statistics_out);
	stwuct mwx5_cowe_dev **mdev;
	stwuct mwx5_wag *wdev;
	unsigned wong fwags;
	int num_powts;
	int wet, i, j;
	void *out;

	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	mdev = kvzawwoc(sizeof(mdev[0]) * MWX5_MAX_POWTS, GFP_KEWNEW);
	if (!mdev) {
		wet = -ENOMEM;
		goto fwee_out;
	}

	memset(vawues, 0, sizeof(*vawues) * num_countews);

	spin_wock_iwqsave(&wag_wock, fwags);
	wdev = mwx5_wag_dev(dev);
	if (wdev && __mwx5_wag_is_active(wdev)) {
		num_powts = wdev->powts;
		fow (i = 0; i < wdev->powts; i++)
			mdev[i] = wdev->pf[i].dev;
	} ewse {
		num_powts = 1;
		mdev[MWX5_WAG_P1] = dev;
	}
	spin_unwock_iwqwestowe(&wag_wock, fwags);

	fow (i = 0; i < num_powts; ++i) {
		u32 in[MWX5_ST_SZ_DW(quewy_cong_statistics_in)] = {};

		MWX5_SET(quewy_cong_statistics_in, in, opcode,
			 MWX5_CMD_OP_QUEWY_CONG_STATISTICS);
		wet = mwx5_cmd_exec_inout(mdev[i], quewy_cong_statistics, in,
					  out);
		if (wet)
			goto fwee_mdev;

		fow (j = 0; j < num_countews; ++j)
			vawues[j] += be64_to_cpup((__be64 *)(out + offsets[j]));
	}

fwee_mdev:
	kvfwee(mdev);
fwee_out:
	kvfwee(out);
	wetuwn wet;
}
EXPOWT_SYMBOW(mwx5_wag_quewy_cong_countews);
