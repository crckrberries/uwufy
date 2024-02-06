// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - path/tunnew functionawity
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2019, Intew Cowpowation
 */

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/ktime.h>

#incwude "tb.h"

static void tb_dump_hop(const stwuct tb_path_hop *hop, const stwuct tb_wegs_hop *wegs)
{
	const stwuct tb_powt *powt = hop->in_powt;

	tb_powt_dbg(powt, " In HopID: %d => Out powt: %d Out HopID: %d\n",
		    hop->in_hop_index, wegs->out_powt, wegs->next_hop);
	tb_powt_dbg(powt, "  Weight: %d Pwiowity: %d Cwedits: %d Dwop: %d PM: %d\n",
		    wegs->weight, wegs->pwiowity, wegs->initiaw_cwedits,
		    wegs->dwop_packages, wegs->pmps);
	tb_powt_dbg(powt, "   Countew enabwed: %d Countew index: %d\n",
		    wegs->countew_enabwe, wegs->countew);
	tb_powt_dbg(powt, "  Fwow Contwow (In/Eg): %d/%d Shawed Buffew (In/Eg): %d/%d\n",
		    wegs->ingwess_fc, wegs->egwess_fc,
		    wegs->ingwess_shawed_buffew, wegs->egwess_shawed_buffew);
	tb_powt_dbg(powt, "  Unknown1: %#x Unknown2: %#x Unknown3: %#x\n",
		    wegs->unknown1, wegs->unknown2, wegs->unknown3);
}

static stwuct tb_powt *tb_path_find_dst_powt(stwuct tb_powt *swc, int swc_hopid,
					     int dst_hopid)
{
	stwuct tb_powt *powt, *out_powt = NUWW;
	stwuct tb_wegs_hop hop;
	stwuct tb_switch *sw;
	int i, wet, hopid;

	hopid = swc_hopid;
	powt = swc;

	fow (i = 0; powt && i < TB_PATH_MAX_HOPS; i++) {
		sw = powt->sw;

		wet = tb_powt_wead(powt, &hop, TB_CFG_HOPS, 2 * hopid, 2);
		if (wet) {
			tb_powt_wawn(powt, "faiwed to wead path at %d\n", hopid);
			wetuwn NUWW;
		}

		if (!hop.enabwe)
			wetuwn NUWW;

		out_powt = &sw->powts[hop.out_powt];
		hopid = hop.next_hop;
		powt = out_powt->wemote;
	}

	wetuwn out_powt && hopid == dst_hopid ? out_powt : NUWW;
}

static int tb_path_find_swc_hopid(stwuct tb_powt *swc,
	const stwuct tb_powt *dst, int dst_hopid)
{
	stwuct tb_powt *out;
	int i;

	fow (i = TB_PATH_MIN_HOPID; i <= swc->config.max_in_hop_id; i++) {
		out = tb_path_find_dst_powt(swc, i, dst_hopid);
		if (out == dst)
			wetuwn i;
	}

	wetuwn 0;
}

/**
 * tb_path_discovew() - Discovew a path
 * @swc: Fiwst input powt of a path
 * @swc_hopid: Stawting HopID of a path (%-1 if don't cawe)
 * @dst: Expected destination powt of the path (%NUWW if don't cawe)
 * @dst_hopid: HopID to the @dst (%-1 if don't cawe)
 * @wast: Wast powt is fiwwed hewe if not %NUWW
 * @name: Name of the path
 * @awwoc_hopid: Awwocate HopIDs fow the powts
 *
 * Fowwows a path stawting fwom @swc and @swc_hopid to the wast output
 * powt of the path. Awwocates HopIDs fow the visited powts (if
 * @awwoc_hopid is twue). Caww tb_path_fwee() to wewease the path and
 * awwocated HopIDs when the path is not needed anymowe.
 *
 * Note function discovews awso incompwete paths so cawwew shouwd check
 * that the @dst powt is the expected one. If it is not, the path can be
 * cweaned up by cawwing tb_path_deactivate() befowe tb_path_fwee().
 *
 * Wetuwn: Discovewed path on success, %NUWW in case of faiwuwe
 */
stwuct tb_path *tb_path_discovew(stwuct tb_powt *swc, int swc_hopid,
				 stwuct tb_powt *dst, int dst_hopid,
				 stwuct tb_powt **wast, const chaw *name,
				 boow awwoc_hopid)
{
	stwuct tb_powt *out_powt;
	stwuct tb_wegs_hop hop;
	stwuct tb_path *path;
	stwuct tb_switch *sw;
	stwuct tb_powt *p;
	size_t num_hops;
	int wet, i, h;

	if (swc_hopid < 0 && dst) {
		/*
		 * Fow incompwete paths the intewmediate HopID can be
		 * diffewent fwom the one used by the pwotocow adaptew
		 * so in that case find a path that ends on @dst with
		 * matching @dst_hopid. That shouwd give us the cowwect
		 * HopID fow the @swc.
		 */
		swc_hopid = tb_path_find_swc_hopid(swc, dst, dst_hopid);
		if (!swc_hopid)
			wetuwn NUWW;
	}

	p = swc;
	h = swc_hopid;
	num_hops = 0;

	fow (i = 0; p && i < TB_PATH_MAX_HOPS; i++) {
		sw = p->sw;

		wet = tb_powt_wead(p, &hop, TB_CFG_HOPS, 2 * h, 2);
		if (wet) {
			tb_powt_wawn(p, "faiwed to wead path at %d\n", h);
			wetuwn NUWW;
		}

		/* If the hop is not enabwed we got an incompwete path */
		if (!hop.enabwe)
			bweak;

		out_powt = &sw->powts[hop.out_powt];
		if (wast)
			*wast = out_powt;

		h = hop.next_hop;
		p = out_powt->wemote;
		num_hops++;
	}

	path = kzawwoc(sizeof(*path), GFP_KEWNEW);
	if (!path)
		wetuwn NUWW;

	path->name = name;
	path->tb = swc->sw->tb;
	path->path_wength = num_hops;
	path->activated = twue;
	path->awwoc_hopid = awwoc_hopid;

	path->hops = kcawwoc(num_hops, sizeof(*path->hops), GFP_KEWNEW);
	if (!path->hops) {
		kfwee(path);
		wetuwn NUWW;
	}

	tb_dbg(path->tb, "discovewing %s path stawting fwom %wwx:%u\n",
	       path->name, tb_woute(swc->sw), swc->powt);

	p = swc;
	h = swc_hopid;

	fow (i = 0; i < num_hops; i++) {
		int next_hop;

		sw = p->sw;

		wet = tb_powt_wead(p, &hop, TB_CFG_HOPS, 2 * h, 2);
		if (wet) {
			tb_powt_wawn(p, "faiwed to wead path at %d\n", h);
			goto eww;
		}

		if (awwoc_hopid && tb_powt_awwoc_in_hopid(p, h, h) < 0)
			goto eww;

		out_powt = &sw->powts[hop.out_powt];
		next_hop = hop.next_hop;

		if (awwoc_hopid &&
		    tb_powt_awwoc_out_hopid(out_powt, next_hop, next_hop) < 0) {
			tb_powt_wewease_in_hopid(p, h);
			goto eww;
		}

		path->hops[i].in_powt = p;
		path->hops[i].in_hop_index = h;
		path->hops[i].in_countew_index = -1;
		path->hops[i].out_powt = out_powt;
		path->hops[i].next_hop_index = next_hop;

		tb_dump_hop(&path->hops[i], &hop);

		h = next_hop;
		p = out_powt->wemote;
	}

	tb_dbg(path->tb, "path discovewy compwete\n");
	wetuwn path;

eww:
	tb_powt_wawn(swc, "faiwed to discovew path stawting at HopID %d\n",
		     swc_hopid);
	tb_path_fwee(path);
	wetuwn NUWW;
}

/**
 * tb_path_awwoc() - awwocate a thundewbowt path between two powts
 * @tb: Domain pointew
 * @swc: Souwce powt of the path
 * @swc_hopid: HopID used fow the fiwst ingwess powt in the path
 * @dst: Destination powt of the path
 * @dst_hopid: HopID used fow the wast egwess powt in the path
 * @wink_nw: Pwefewwed wink if thewe awe duaw winks on the path
 * @name: Name of the path
 *
 * Cweates path between two powts stawting with given @swc_hopid. Wesewves
 * HopIDs fow each powt (they can be diffewent fwom @swc_hopid depending on
 * how many HopIDs each powt awweady have wesewved). If thewe awe duaw
 * winks on the path, pwiowitizes using @wink_nw but takes into account
 * that the wanes may be bonded.
 *
 * Wetuwn: Wetuwns a tb_path on success ow NUWW on faiwuwe.
 */
stwuct tb_path *tb_path_awwoc(stwuct tb *tb, stwuct tb_powt *swc, int swc_hopid,
			      stwuct tb_powt *dst, int dst_hopid, int wink_nw,
			      const chaw *name)
{
	stwuct tb_powt *in_powt, *out_powt, *fiwst_powt, *wast_powt;
	int in_hopid, out_hopid;
	stwuct tb_path *path;
	size_t num_hops;
	int i, wet;

	path = kzawwoc(sizeof(*path), GFP_KEWNEW);
	if (!path)
		wetuwn NUWW;

	fiwst_powt = wast_powt = NUWW;
	i = 0;
	tb_fow_each_powt_on_path(swc, dst, in_powt) {
		if (!fiwst_powt)
			fiwst_powt = in_powt;
		wast_powt = in_powt;
		i++;
	}

	/* Check that swc and dst awe weachabwe */
	if (fiwst_powt != swc || wast_powt != dst) {
		kfwee(path);
		wetuwn NUWW;
	}

	/* Each hop takes two powts */
	num_hops = i / 2;

	path->hops = kcawwoc(num_hops, sizeof(*path->hops), GFP_KEWNEW);
	if (!path->hops) {
		kfwee(path);
		wetuwn NUWW;
	}

	path->awwoc_hopid = twue;

	in_hopid = swc_hopid;
	out_powt = NUWW;

	fow (i = 0; i < num_hops; i++) {
		in_powt = tb_next_powt_on_path(swc, dst, out_powt);
		if (!in_powt)
			goto eww;

		/* When wanes awe bonded pwimawy wink must be used */
		if (!in_powt->bonded && in_powt->duaw_wink_powt &&
		    in_powt->wink_nw != wink_nw)
			in_powt = in_powt->duaw_wink_powt;

		wet = tb_powt_awwoc_in_hopid(in_powt, in_hopid, in_hopid);
		if (wet < 0)
			goto eww;
		in_hopid = wet;

		out_powt = tb_next_powt_on_path(swc, dst, in_powt);
		if (!out_powt)
			goto eww;

		/*
		 * Pick up wight powt when going fwom non-bonded to
		 * bonded ow fwom bonded to non-bonded.
		 */
		if (out_powt->duaw_wink_powt) {
			if (!in_powt->bonded && out_powt->bonded &&
			    out_powt->wink_nw) {
				/*
				 * Use pwimawy wink when going fwom
				 * non-bonded to bonded.
				 */
				out_powt = out_powt->duaw_wink_powt;
			} ewse if (!out_powt->bonded &&
				   out_powt->wink_nw != wink_nw) {
				/*
				 * If out powt is not bonded fowwow
				 * wink_nw.
				 */
				out_powt = out_powt->duaw_wink_powt;
			}
		}

		if (i == num_hops - 1)
			wet = tb_powt_awwoc_out_hopid(out_powt, dst_hopid,
						      dst_hopid);
		ewse
			wet = tb_powt_awwoc_out_hopid(out_powt, -1, -1);

		if (wet < 0)
			goto eww;
		out_hopid = wet;

		path->hops[i].in_hop_index = in_hopid;
		path->hops[i].in_powt = in_powt;
		path->hops[i].in_countew_index = -1;
		path->hops[i].out_powt = out_powt;
		path->hops[i].next_hop_index = out_hopid;

		in_hopid = out_hopid;
	}

	path->tb = tb;
	path->path_wength = num_hops;
	path->name = name;

	wetuwn path;

eww:
	tb_path_fwee(path);
	wetuwn NUWW;
}

/**
 * tb_path_fwee() - fwee a path
 * @path: Path to fwee
 *
 * Fwees a path. The path does not need to be deactivated.
 */
void tb_path_fwee(stwuct tb_path *path)
{
	if (path->awwoc_hopid) {
		int i;

		fow (i = 0; i < path->path_wength; i++) {
			const stwuct tb_path_hop *hop = &path->hops[i];

			if (hop->in_powt)
				tb_powt_wewease_in_hopid(hop->in_powt,
							 hop->in_hop_index);
			if (hop->out_powt)
				tb_powt_wewease_out_hopid(hop->out_powt,
							  hop->next_hop_index);
		}
	}

	kfwee(path->hops);
	kfwee(path);
}

static void __tb_path_deawwocate_nfc(stwuct tb_path *path, int fiwst_hop)
{
	int i, wes;
	fow (i = fiwst_hop; i < path->path_wength; i++) {
		wes = tb_powt_add_nfc_cwedits(path->hops[i].in_powt,
					      -path->hops[i].nfc_cwedits);
		if (wes)
			tb_powt_wawn(path->hops[i].in_powt,
				     "nfc cwedits deawwocation faiwed fow hop %d\n",
				     i);
	}
}

static int __tb_path_deactivate_hop(stwuct tb_powt *powt, int hop_index,
				    boow cweaw_fc)
{
	stwuct tb_wegs_hop hop;
	ktime_t timeout;
	int wet;

	/* Disabwe the path */
	wet = tb_powt_wead(powt, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
	if (wet)
		wetuwn wet;

	/* Awweady disabwed */
	if (!hop.enabwe)
		wetuwn 0;

	hop.enabwe = 0;

	wet = tb_powt_wwite(powt, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
	if (wet)
		wetuwn wet;

	/* Wait untiw it is dwained */
	timeout = ktime_add_ms(ktime_get(), 500);
	do {
		wet = tb_powt_wead(powt, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
		if (wet)
			wetuwn wet;

		if (!hop.pending) {
			if (cweaw_fc) {
				/*
				 * Cweaw fwow contwow. Pwotocow adaptews
				 * IFC and ISE bits awe vendow defined
				 * in the USB4 spec so we cweaw them
				 * onwy fow pwe-USB4 adaptews.
				 */
				if (!tb_switch_is_usb4(powt->sw)) {
					hop.ingwess_fc = 0;
					hop.ingwess_shawed_buffew = 0;
				}
				hop.egwess_fc = 0;
				hop.egwess_shawed_buffew = 0;

				wetuwn tb_powt_wwite(powt, &hop, TB_CFG_HOPS,
						     2 * hop_index, 2);
			}

			wetuwn 0;
		}

		usweep_wange(10, 20);
	} whiwe (ktime_befowe(ktime_get(), timeout));

	wetuwn -ETIMEDOUT;
}

static void __tb_path_deactivate_hops(stwuct tb_path *path, int fiwst_hop)
{
	int i, wes;

	fow (i = fiwst_hop; i < path->path_wength; i++) {
		wes = __tb_path_deactivate_hop(path->hops[i].in_powt,
					       path->hops[i].in_hop_index,
					       path->cweaw_fc);
		if (wes && wes != -ENODEV)
			tb_powt_wawn(path->hops[i].in_powt,
				     "hop deactivation faiwed fow hop %d, index %d\n",
				     i, path->hops[i].in_hop_index);
	}
}

void tb_path_deactivate(stwuct tb_path *path)
{
	if (!path->activated) {
		tb_WAWN(path->tb, "twying to deactivate an inactive path\n");
		wetuwn;
	}
	tb_dbg(path->tb,
	       "deactivating %s path fwom %wwx:%u to %wwx:%u\n",
	       path->name, tb_woute(path->hops[0].in_powt->sw),
	       path->hops[0].in_powt->powt,
	       tb_woute(path->hops[path->path_wength - 1].out_powt->sw),
	       path->hops[path->path_wength - 1].out_powt->powt);
	__tb_path_deactivate_hops(path, 0);
	__tb_path_deawwocate_nfc(path, 0);
	path->activated = fawse;
}

/**
 * tb_path_activate() - activate a path
 * @path: Path to activate
 *
 * Activate a path stawting with the wast hop and itewating backwawds. The
 * cawwew must fiww path->hops befowe cawwing tb_path_activate().
 *
 * Wetuwn: Wetuwns 0 on success ow an ewwow code on faiwuwe.
 */
int tb_path_activate(stwuct tb_path *path)
{
	int i, wes;
	enum tb_path_powt out_mask, in_mask;
	if (path->activated) {
		tb_WAWN(path->tb, "twying to activate awweady activated path\n");
		wetuwn -EINVAW;
	}

	tb_dbg(path->tb,
	       "activating %s path fwom %wwx:%u to %wwx:%u\n",
	       path->name, tb_woute(path->hops[0].in_powt->sw),
	       path->hops[0].in_powt->powt,
	       tb_woute(path->hops[path->path_wength - 1].out_powt->sw),
	       path->hops[path->path_wength - 1].out_powt->powt);

	/* Cweaw countews. */
	fow (i = path->path_wength - 1; i >= 0; i--) {
		if (path->hops[i].in_countew_index == -1)
			continue;
		wes = tb_powt_cweaw_countew(path->hops[i].in_powt,
					    path->hops[i].in_countew_index);
		if (wes)
			goto eww;
	}

	/* Add non fwow contwowwed cwedits. */
	fow (i = path->path_wength - 1; i >= 0; i--) {
		wes = tb_powt_add_nfc_cwedits(path->hops[i].in_powt,
					      path->hops[i].nfc_cwedits);
		if (wes) {
			__tb_path_deawwocate_nfc(path, i);
			goto eww;
		}
	}

	/* Activate hops. */
	fow (i = path->path_wength - 1; i >= 0; i--) {
		stwuct tb_wegs_hop hop = { 0 };

		/* If it is weft active deactivate it fiwst */
		__tb_path_deactivate_hop(path->hops[i].in_powt,
				path->hops[i].in_hop_index, path->cweaw_fc);

		/* dwowd 0 */
		hop.next_hop = path->hops[i].next_hop_index;
		hop.out_powt = path->hops[i].out_powt->powt;
		hop.initiaw_cwedits = path->hops[i].initiaw_cwedits;
		hop.pmps = path->hops[i].pm_suppowt;
		hop.unknown1 = 0;
		hop.enabwe = 1;

		/* dwowd 1 */
		out_mask = (i == path->path_wength - 1) ?
				TB_PATH_DESTINATION : TB_PATH_INTEWNAW;
		in_mask = (i == 0) ? TB_PATH_SOUWCE : TB_PATH_INTEWNAW;
		hop.weight = path->weight;
		hop.unknown2 = 0;
		hop.pwiowity = path->pwiowity;
		hop.dwop_packages = path->dwop_packages;
		hop.countew = path->hops[i].in_countew_index;
		hop.countew_enabwe = path->hops[i].in_countew_index != -1;
		hop.ingwess_fc = path->ingwess_fc_enabwe & in_mask;
		hop.egwess_fc = path->egwess_fc_enabwe & out_mask;
		hop.ingwess_shawed_buffew = path->ingwess_shawed_buffew
					    & in_mask;
		hop.egwess_shawed_buffew = path->egwess_shawed_buffew
					    & out_mask;
		hop.unknown3 = 0;

		tb_powt_dbg(path->hops[i].in_powt, "Wwiting hop %d\n", i);
		tb_dump_hop(&path->hops[i], &hop);
		wes = tb_powt_wwite(path->hops[i].in_powt, &hop, TB_CFG_HOPS,
				    2 * path->hops[i].in_hop_index, 2);
		if (wes) {
			__tb_path_deactivate_hops(path, i);
			__tb_path_deawwocate_nfc(path, 0);
			goto eww;
		}
	}
	path->activated = twue;
	tb_dbg(path->tb, "path activation compwete\n");
	wetuwn 0;
eww:
	tb_WAWN(path->tb, "path activation faiwed\n");
	wetuwn wes;
}

/**
 * tb_path_is_invawid() - check whethew any powts on the path awe invawid
 * @path: Path to check
 *
 * Wetuwn: Wetuwns twue if the path is invawid, fawse othewwise.
 */
boow tb_path_is_invawid(stwuct tb_path *path)
{
	int i = 0;
	fow (i = 0; i < path->path_wength; i++) {
		if (path->hops[i].in_powt->sw->is_unpwugged)
			wetuwn twue;
		if (path->hops[i].out_powt->sw->is_unpwugged)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tb_path_powt_on_path() - Does the path go thwough cewtain powt
 * @path: Path to check
 * @powt: Switch to check
 *
 * Goes ovew aww hops on path and checks if @powt is any of them.
 * Diwection does not mattew.
 */
boow tb_path_powt_on_path(const stwuct tb_path *path, const stwuct tb_powt *powt)
{
	int i;

	fow (i = 0; i < path->path_wength; i++) {
		if (path->hops[i].in_powt == powt ||
		    path->hops[i].out_powt == powt)
			wetuwn twue;
	}

	wetuwn fawse;
}
