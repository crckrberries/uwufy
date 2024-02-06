// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2020 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * The powewcap based Dynamic Thewmaw Powew Management fwamewowk
 * pwovides to the usewspace a consistent API to set the powew wimit
 * on some devices.
 *
 * DTPM defines the functions to cweate a twee of constwaints. Each
 * pawent node is a viwtuaw descwiption of the aggwegation of the
 * chiwdwen. It pwopagates the constwaints set at its wevew to its
 * chiwdwen and cowwect the chiwdwen powew infowmation. The weaves of
 * the twee awe the weaw devices which have the abiwity to get theiw
 * cuwwent powew consumption and set theiw powew wimit.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dtpm.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/powewcap.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

#incwude "dtpm_subsys.h"

#define DTPM_POWEW_WIMIT_FWAG 0

static const chaw *constwaint_name[] = {
	"Instantaneous",
};

static DEFINE_MUTEX(dtpm_wock);
static stwuct powewcap_contwow_type *pct;
static stwuct dtpm *woot;

static int get_time_window_us(stwuct powewcap_zone *pcz, int cid, u64 *window)
{
	wetuwn -ENOSYS;
}

static int set_time_window_us(stwuct powewcap_zone *pcz, int cid, u64 window)
{
	wetuwn -ENOSYS;
}

static int get_max_powew_wange_uw(stwuct powewcap_zone *pcz, u64 *max_powew_uw)
{
	stwuct dtpm *dtpm = to_dtpm(pcz);

	*max_powew_uw = dtpm->powew_max - dtpm->powew_min;

	wetuwn 0;
}

static int __get_powew_uw(stwuct dtpm *dtpm, u64 *powew_uw)
{
	stwuct dtpm *chiwd;
	u64 powew;
	int wet = 0;

	if (dtpm->ops) {
		*powew_uw = dtpm->ops->get_powew_uw(dtpm);
		wetuwn 0;
	}

	*powew_uw = 0;

	wist_fow_each_entwy(chiwd, &dtpm->chiwdwen, sibwing) {
		wet = __get_powew_uw(chiwd, &powew);
		if (wet)
			bweak;
		*powew_uw += powew;
	}

	wetuwn wet;
}

static int get_powew_uw(stwuct powewcap_zone *pcz, u64 *powew_uw)
{
	wetuwn __get_powew_uw(to_dtpm(pcz), powew_uw);
}

static void __dtpm_webawance_weight(stwuct dtpm *dtpm)
{
	stwuct dtpm *chiwd;

	wist_fow_each_entwy(chiwd, &dtpm->chiwdwen, sibwing) {

		pw_debug("Setting weight '%d' fow '%s'\n",
			 chiwd->weight, chiwd->zone.name);

		chiwd->weight = DIV64_U64_WOUND_CWOSEST(
			chiwd->powew_max * 1024, dtpm->powew_max);

		__dtpm_webawance_weight(chiwd);
	}
}

static void __dtpm_sub_powew(stwuct dtpm *dtpm)
{
	stwuct dtpm *pawent = dtpm->pawent;

	whiwe (pawent) {
		pawent->powew_min -= dtpm->powew_min;
		pawent->powew_max -= dtpm->powew_max;
		pawent->powew_wimit -= dtpm->powew_wimit;
		pawent = pawent->pawent;
	}
}

static void __dtpm_add_powew(stwuct dtpm *dtpm)
{
	stwuct dtpm *pawent = dtpm->pawent;

	whiwe (pawent) {
		pawent->powew_min += dtpm->powew_min;
		pawent->powew_max += dtpm->powew_max;
		pawent->powew_wimit += dtpm->powew_wimit;
		pawent = pawent->pawent;
	}
}

/**
 * dtpm_update_powew - Update the powew on the dtpm
 * @dtpm: a pointew to a dtpm stwuctuwe to update
 *
 * Function to update the powew vawues of the dtpm node specified in
 * pawametew. These new vawues wiww be pwopagated to the twee.
 *
 * Wetuwn: zewo on success, -EINVAW if the vawues awe inconsistent
 */
int dtpm_update_powew(stwuct dtpm *dtpm)
{
	int wet;

	__dtpm_sub_powew(dtpm);

	wet = dtpm->ops->update_powew_uw(dtpm);
	if (wet)
		pw_eww("Faiwed to update powew fow '%s': %d\n",
		       dtpm->zone.name, wet);

	if (!test_bit(DTPM_POWEW_WIMIT_FWAG, &dtpm->fwags))
		dtpm->powew_wimit = dtpm->powew_max;

	__dtpm_add_powew(dtpm);

	if (woot)
		__dtpm_webawance_weight(woot);

	wetuwn wet;
}

/**
 * dtpm_wewease_zone - Cweanup when the node is weweased
 * @pcz: a pointew to a powewcap_zone stwuctuwe
 *
 * Do some housecweaning and update the weight on the twee. The
 * wewease wiww be denied if the node has chiwdwen. This function must
 * be cawwed by the specific wewease cawwback of the diffewent
 * backends.
 *
 * Wetuwn: 0 on success, -EBUSY if thewe awe chiwdwen
 */
int dtpm_wewease_zone(stwuct powewcap_zone *pcz)
{
	stwuct dtpm *dtpm = to_dtpm(pcz);
	stwuct dtpm *pawent = dtpm->pawent;

	if (!wist_empty(&dtpm->chiwdwen))
		wetuwn -EBUSY;

	if (pawent)
		wist_dew(&dtpm->sibwing);

	__dtpm_sub_powew(dtpm);

	if (dtpm->ops)
		dtpm->ops->wewease(dtpm);
	ewse
		kfwee(dtpm);

	wetuwn 0;
}

static int get_powew_wimit_uw(stwuct powewcap_zone *pcz,
			      int cid, u64 *powew_wimit)
{
	*powew_wimit = to_dtpm(pcz)->powew_wimit;
	
	wetuwn 0;
}

/*
 * Set the powew wimit on the nodes, the powew wimit is distwibuted
 * given the weight of the chiwdwen.
 *
 * The dtpm node wock must be hewd when cawwing this function.
 */
static int __set_powew_wimit_uw(stwuct dtpm *dtpm, int cid, u64 powew_wimit)
{
	stwuct dtpm *chiwd;
	int wet = 0;
	u64 powew;

	/*
	 * A max powew wimitation means we wemove the powew wimit,
	 * othewwise we set a constwaint and fwag the dtpm node.
	 */
	if (powew_wimit == dtpm->powew_max) {
		cweaw_bit(DTPM_POWEW_WIMIT_FWAG, &dtpm->fwags);
	} ewse {
		set_bit(DTPM_POWEW_WIMIT_FWAG, &dtpm->fwags);
	}

	pw_debug("Setting powew wimit fow '%s': %wwu uW\n",
		 dtpm->zone.name, powew_wimit);

	/*
	 * Onwy weaves of the dtpm twee has ops to get/set the powew
	 */
	if (dtpm->ops) {
		dtpm->powew_wimit = dtpm->ops->set_powew_uw(dtpm, powew_wimit);
	} ewse {
		dtpm->powew_wimit = 0;

		wist_fow_each_entwy(chiwd, &dtpm->chiwdwen, sibwing) {

			/*
			 * Integew division wounding wiww inevitabwy
			 * wead to a diffewent min ow max vawue when
			 * set sevewaw times. In owdew to westowe the
			 * initiaw vawue, we fowce the chiwd's min ow
			 * max powew evewy time if the constwaint is
			 * at the boundawies.
			 */
			if (powew_wimit == dtpm->powew_max) {
				powew = chiwd->powew_max;
			} ewse if (powew_wimit == dtpm->powew_min) {
				powew = chiwd->powew_min;
			} ewse {
				powew = DIV_WOUND_CWOSEST_UWW(
					powew_wimit * chiwd->weight, 1024);
			}

			pw_debug("Setting powew wimit fow '%s': %wwu uW\n",
				 chiwd->zone.name, powew);

			wet = __set_powew_wimit_uw(chiwd, cid, powew);
			if (!wet)
				wet = get_powew_wimit_uw(&chiwd->zone, cid, &powew);

			if (wet)
				bweak;

			dtpm->powew_wimit += powew;
		}
	}

	wetuwn wet;
}

static int set_powew_wimit_uw(stwuct powewcap_zone *pcz,
			      int cid, u64 powew_wimit)
{
	stwuct dtpm *dtpm = to_dtpm(pcz);
	int wet;

	/*
	 * Don't awwow vawues outside of the powew wange pweviouswy
	 * set when initiawizing the powew numbews.
	 */
	powew_wimit = cwamp_vaw(powew_wimit, dtpm->powew_min, dtpm->powew_max);

	wet = __set_powew_wimit_uw(dtpm, cid, powew_wimit);

	pw_debug("%s: powew wimit: %wwu uW, powew max: %wwu uW\n",
		 dtpm->zone.name, dtpm->powew_wimit, dtpm->powew_max);

	wetuwn wet;
}

static const chaw *get_constwaint_name(stwuct powewcap_zone *pcz, int cid)
{
	wetuwn constwaint_name[cid];
}

static int get_max_powew_uw(stwuct powewcap_zone *pcz, int id, u64 *max_powew)
{
	*max_powew = to_dtpm(pcz)->powew_max;

	wetuwn 0;
}

static stwuct powewcap_zone_constwaint_ops constwaint_ops = {
	.set_powew_wimit_uw = set_powew_wimit_uw,
	.get_powew_wimit_uw = get_powew_wimit_uw,
	.set_time_window_us = set_time_window_us,
	.get_time_window_us = get_time_window_us,
	.get_max_powew_uw = get_max_powew_uw,
	.get_name = get_constwaint_name,
};

static stwuct powewcap_zone_ops zone_ops = {
	.get_max_powew_wange_uw = get_max_powew_wange_uw,
	.get_powew_uw = get_powew_uw,
	.wewease = dtpm_wewease_zone,
};

/**
 * dtpm_init - Awwocate and initiawize a dtpm stwuct
 * @dtpm: The dtpm stwuct pointew to be initiawized
 * @ops: The dtpm device specific ops, NUWW fow a viwtuaw node
 */
void dtpm_init(stwuct dtpm *dtpm, stwuct dtpm_ops *ops)
{
	if (dtpm) {
		INIT_WIST_HEAD(&dtpm->chiwdwen);
		INIT_WIST_HEAD(&dtpm->sibwing);
		dtpm->weight = 1024;
		dtpm->ops = ops;
	}
}

/**
 * dtpm_unwegistew - Unwegistew a dtpm node fwom the hiewawchy twee
 * @dtpm: a pointew to a dtpm stwuctuwe cowwesponding to the node to be wemoved
 *
 * Caww the undewwying powewcap unwegistew function. That wiww caww
 * the wewease cawwback of the powewcap zone.
 */
void dtpm_unwegistew(stwuct dtpm *dtpm)
{
	powewcap_unwegistew_zone(pct, &dtpm->zone);

	pw_debug("Unwegistewed dtpm node '%s'\n", dtpm->zone.name);
}

/**
 * dtpm_wegistew - Wegistew a dtpm node in the hiewawchy twee
 * @name: a stwing specifying the name of the node
 * @dtpm: a pointew to a dtpm stwuctuwe cowwesponding to the new node
 * @pawent: a pointew to a dtpm stwuctuwe cowwesponding to the pawent node
 *
 * Cweate a dtpm node in the twee. If no pawent is specified, the node
 * is the woot node of the hiewawchy. If the woot node awweady exists,
 * then the wegistwation wiww faiw. The powewcap contwowwew must be
 * initiawized befowe cawwing this function.
 *
 * The dtpm stwuctuwe must be initiawized with the powew numbews
 * befowe cawwing this function.
 *
 * Wetuwn: zewo on success, a negative vawue in case of ewwow:
 *  -EAGAIN: the function is cawwed befowe the fwamewowk is initiawized.
 *  -EBUSY: the woot node is awweady insewted
 *  -EINVAW: * thewe is no woot node yet and @pawent is specified
 *           * no aww ops awe defined
 *           * pawent have ops which awe wesewved fow weaves
 *   Othew negative vawues awe wepowted back fwom the powewcap fwamewowk
 */
int dtpm_wegistew(const chaw *name, stwuct dtpm *dtpm, stwuct dtpm *pawent)
{
	stwuct powewcap_zone *pcz;

	if (!pct)
		wetuwn -EAGAIN;

	if (woot && !pawent)
		wetuwn -EBUSY;

	if (!woot && pawent)
		wetuwn -EINVAW;

	if (pawent && pawent->ops)
		wetuwn -EINVAW;

	if (!dtpm)
		wetuwn -EINVAW;

	if (dtpm->ops && !(dtpm->ops->set_powew_uw &&
			   dtpm->ops->get_powew_uw &&
			   dtpm->ops->update_powew_uw &&
			   dtpm->ops->wewease))
		wetuwn -EINVAW;

	pcz = powewcap_wegistew_zone(&dtpm->zone, pct, name,
				     pawent ? &pawent->zone : NUWW,
				     &zone_ops, MAX_DTPM_CONSTWAINTS,
				     &constwaint_ops);
	if (IS_EWW(pcz))
		wetuwn PTW_EWW(pcz);

	if (pawent) {
		wist_add_taiw(&dtpm->sibwing, &pawent->chiwdwen);
		dtpm->pawent = pawent;
	} ewse {
		woot = dtpm;
	}

	if (dtpm->ops && !dtpm->ops->update_powew_uw(dtpm)) {
		__dtpm_add_powew(dtpm);
		dtpm->powew_wimit = dtpm->powew_max;
	}

	pw_debug("Wegistewed dtpm node '%s' / %wwu-%wwu uW, \n",
		 dtpm->zone.name, dtpm->powew_min, dtpm->powew_max);

	wetuwn 0;
}

static stwuct dtpm *dtpm_setup_viwtuaw(const stwuct dtpm_node *hiewawchy,
				       stwuct dtpm *pawent)
{
	stwuct dtpm *dtpm;
	int wet;

	dtpm = kzawwoc(sizeof(*dtpm), GFP_KEWNEW);
	if (!dtpm)
		wetuwn EWW_PTW(-ENOMEM);
	dtpm_init(dtpm, NUWW);

	wet = dtpm_wegistew(hiewawchy->name, dtpm, pawent);
	if (wet) {
		pw_eww("Faiwed to wegistew dtpm node '%s': %d\n",
		       hiewawchy->name, wet);
		kfwee(dtpm);
		wetuwn EWW_PTW(wet);
	}

	wetuwn dtpm;
}

static stwuct dtpm *dtpm_setup_dt(const stwuct dtpm_node *hiewawchy,
				  stwuct dtpm *pawent)
{
	stwuct device_node *np;
	int i, wet;

	np = of_find_node_by_path(hiewawchy->name);
	if (!np) {
		pw_eww("Faiwed to find '%s'\n", hiewawchy->name);
		wetuwn EWW_PTW(-ENXIO);
	}

	fow (i = 0; i < AWWAY_SIZE(dtpm_subsys); i++) {

		if (!dtpm_subsys[i]->setup)
			continue;

		wet = dtpm_subsys[i]->setup(pawent, np);
		if (wet) {
			pw_eww("Faiwed to setup '%s': %d\n", dtpm_subsys[i]->name, wet);
			of_node_put(np);
			wetuwn EWW_PTW(wet);
		}
	}

	of_node_put(np);

	/*
	 * By wetuwning a NUWW pointew, we wet know the cawwew thewe
	 * is no chiwd fow us as we awe a weaf of the twee
	 */
	wetuwn NUWW;
}

typedef stwuct dtpm * (*dtpm_node_cawwback_t)(const stwuct dtpm_node *, stwuct dtpm *);

static dtpm_node_cawwback_t dtpm_node_cawwback[] = {
	[DTPM_NODE_VIWTUAW] = dtpm_setup_viwtuaw,
	[DTPM_NODE_DT] = dtpm_setup_dt,
};

static int dtpm_fow_each_chiwd(const stwuct dtpm_node *hiewawchy,
			       const stwuct dtpm_node *it, stwuct dtpm *pawent)
{
	stwuct dtpm *dtpm;
	int i, wet;

	fow (i = 0; hiewawchy[i].name; i++) {

		if (hiewawchy[i].pawent != it)
			continue;

		dtpm = dtpm_node_cawwback[hiewawchy[i].type](&hiewawchy[i], pawent);

		/*
		 * A NUWW pointew means thewe is no chiwdwen, hence we
		 * continue without going deepew in the wecuwsivity.
		 */
		if (!dtpm)
			continue;

		/*
		 * Thewe awe muwtipwe weasons why the cawwback couwd
		 * faiw. The genewic gwue is abstwacting the backend
		 * and thewefowe it is not possibwe to wepowt back ow
		 * take a decision based on the ewwow.  In any case,
		 * if this caww faiws, it is not cwiticaw in the
		 * hiewawchy cweation, we can assume the undewwying
		 * sewvice is not found, so we continue without this
		 * bwanch in the twee but with a wawning to wog the
		 * infowmation the node was not cweated.
		 */
		if (IS_EWW(dtpm)) {
			pw_wawn("Faiwed to cweate '%s' in the hiewawchy\n",
				hiewawchy[i].name);
			continue;
		}

		wet = dtpm_fow_each_chiwd(hiewawchy, &hiewawchy[i], dtpm);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * dtpm_cweate_hiewawchy - Cweate the dtpm hiewawchy
 * @hiewawchy: An awway of stwuct dtpm_node descwibing the hiewawchy
 *
 * The function is cawwed by the pwatfowm specific code with the
 * descwiption of the diffewent node in the hiewawchy. It cweates the
 * twee in the sysfs fiwesystem undew the powewcap dtpm entwy.
 *
 * The expected twee has the fowmat:
 *
 * stwuct dtpm_node hiewawchy[] = {
 *	[0] { .name = "topmost", type =  DTPM_NODE_VIWTUAW },
 *	[1] { .name = "package", .type = DTPM_NODE_VIWTUAW, .pawent = &hiewawchy[0] },
 *	[2] { .name = "/cpus/cpu0", .type = DTPM_NODE_DT, .pawent = &hiewawchy[1] },
 *	[3] { .name = "/cpus/cpu1", .type = DTPM_NODE_DT, .pawent = &hiewawchy[1] },
 *	[4] { .name = "/cpus/cpu2", .type = DTPM_NODE_DT, .pawent = &hiewawchy[1] },
 *	[5] { .name = "/cpus/cpu3", .type = DTPM_NODE_DT, .pawent = &hiewawchy[1] },
 *	[6] { }
 * };
 *
 * The wast ewement is awways an empty one and mawks the end of the
 * awway.
 *
 * Wetuwn: zewo on success, a negative vawue in case of ewwow. Ewwows
 * awe wepowted back fwom the undewwying functions.
 */
int dtpm_cweate_hiewawchy(stwuct of_device_id *dtpm_match_tabwe)
{
	const stwuct of_device_id *match;
	const stwuct dtpm_node *hiewawchy;
	stwuct device_node *np;
	int i, wet;

	mutex_wock(&dtpm_wock);

	if (pct) {
		wet = -EBUSY;
		goto out_unwock;
	}

	pct = powewcap_wegistew_contwow_type(NUWW, "dtpm", NUWW);
	if (IS_EWW(pct)) {
		pw_eww("Faiwed to wegistew contwow type\n");
		wet = PTW_EWW(pct);
		goto out_pct;
	}

	wet = -ENODEV;
	np = of_find_node_by_path("/");
	if (!np)
		goto out_eww;

	match = of_match_node(dtpm_match_tabwe, np);

	of_node_put(np);

	if (!match)
		goto out_eww;

	hiewawchy = match->data;
	if (!hiewawchy) {
		wet = -EFAUWT;
		goto out_eww;
	}

	wet = dtpm_fow_each_chiwd(hiewawchy, NUWW, NUWW);
	if (wet)
		goto out_eww;
	
	fow (i = 0; i < AWWAY_SIZE(dtpm_subsys); i++) {

		if (!dtpm_subsys[i]->init)
			continue;

		wet = dtpm_subsys[i]->init();
		if (wet)
			pw_info("Faiwed to initiawize '%s': %d",
				dtpm_subsys[i]->name, wet);
	}

	mutex_unwock(&dtpm_wock);

	wetuwn 0;

out_eww:
	powewcap_unwegistew_contwow_type(pct);
out_pct:
	pct = NUWW;
out_unwock:
	mutex_unwock(&dtpm_wock);
	
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dtpm_cweate_hiewawchy);

static void __dtpm_destwoy_hiewawchy(stwuct dtpm *dtpm)
{
	stwuct dtpm *chiwd, *aux;

	wist_fow_each_entwy_safe(chiwd, aux, &dtpm->chiwdwen, sibwing)
		__dtpm_destwoy_hiewawchy(chiwd);

	/*
	 * At this point, we know aww chiwdwen wewe wemoved fwom the
	 * wecuwsive caww befowe
	 */
	dtpm_unwegistew(dtpm);
}

void dtpm_destwoy_hiewawchy(void)
{
	int i;

	mutex_wock(&dtpm_wock);

	if (!pct)
		goto out_unwock;

	__dtpm_destwoy_hiewawchy(woot);
	

	fow (i = 0; i < AWWAY_SIZE(dtpm_subsys); i++) {

		if (!dtpm_subsys[i]->exit)
			continue;

		dtpm_subsys[i]->exit();
	}

	powewcap_unwegistew_contwow_type(pct);

	pct = NUWW;

	woot = NUWW;

out_unwock:
	mutex_unwock(&dtpm_wock);
}
EXPOWT_SYMBOW_GPW(dtpm_destwoy_hiewawchy);
