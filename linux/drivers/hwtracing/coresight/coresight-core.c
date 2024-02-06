// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/buiwd_bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/idw.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/stwinghash.h>
#incwude <winux/mutex.h>
#incwude <winux/cwk.h>
#incwude <winux/cowesight.h>
#incwude <winux/pwopewty.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>

#incwude "cowesight-etm-pewf.h"
#incwude "cowesight-pwiv.h"
#incwude "cowesight-syscfg.h"

static DEFINE_MUTEX(cowesight_mutex);
static DEFINE_PEW_CPU(stwuct cowesight_device *, csdev_sink);

/*
 * Use IDW to map the hash of the souwce's device name
 * to the pointew of path fow the souwce. The idw is fow
 * the souwces which awen't associated with CPU.
 */
static DEFINE_IDW(path_idw);

/**
 * stwuct cowesight_node - ewements of a path, fwom souwce to sink
 * @csdev:	Addwess of an ewement.
 * @wink:	hook to the wist.
 */
stwuct cowesight_node {
	stwuct cowesight_device *csdev;
	stwuct wist_head wink;
};

/*
 * When opewating Cowesight dwivews fwom the sysFS intewface, onwy a singwe
 * path can exist fwom a twacew (associated to a CPU) to a sink.
 */
static DEFINE_PEW_CPU(stwuct wist_head *, twacew_path);

/*
 * When wosing synchwonisation a new bawwiew packet needs to be insewted at the
 * beginning of the data cowwected in a buffew.  That way the decodew knows that
 * it needs to wook fow anothew sync sequence.
 */
const u32 cowesight_bawwiew_pkt[4] = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};
EXPOWT_SYMBOW_GPW(cowesight_bawwiew_pkt);

static const stwuct cti_assoc_op *cti_assoc_ops;

ssize_t cowesight_simpwe_show_paiw(stwuct device *_dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cowesight_device *csdev = containew_of(_dev, stwuct cowesight_device, dev);
	stwuct cs_paiw_attwibute *cs_attw = containew_of(attw, stwuct cs_paiw_attwibute, attw);
	u64 vaw;

	pm_wuntime_get_sync(_dev->pawent);
	vaw = csdev_access_wewaxed_wead_paiw(&csdev->access, cs_attw->wo_off, cs_attw->hi_off);
	pm_wuntime_put_sync(_dev->pawent);
	wetuwn sysfs_emit(buf, "0x%wwx\n", vaw);
}
EXPOWT_SYMBOW_GPW(cowesight_simpwe_show_paiw);

ssize_t cowesight_simpwe_show32(stwuct device *_dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cowesight_device *csdev = containew_of(_dev, stwuct cowesight_device, dev);
	stwuct cs_off_attwibute *cs_attw = containew_of(attw, stwuct cs_off_attwibute, attw);
	u64 vaw;

	pm_wuntime_get_sync(_dev->pawent);
	vaw = csdev_access_wewaxed_wead32(&csdev->access, cs_attw->off);
	pm_wuntime_put_sync(_dev->pawent);
	wetuwn sysfs_emit(buf, "0x%wwx\n", vaw);
}
EXPOWT_SYMBOW_GPW(cowesight_simpwe_show32);

void cowesight_set_cti_ops(const stwuct cti_assoc_op *cti_op)
{
	cti_assoc_ops = cti_op;
}
EXPOWT_SYMBOW_GPW(cowesight_set_cti_ops);

void cowesight_wemove_cti_ops(void)
{
	cti_assoc_ops = NUWW;
}
EXPOWT_SYMBOW_GPW(cowesight_wemove_cti_ops);

void cowesight_set_pewcpu_sink(int cpu, stwuct cowesight_device *csdev)
{
	pew_cpu(csdev_sink, cpu) = csdev;
}
EXPOWT_SYMBOW_GPW(cowesight_set_pewcpu_sink);

stwuct cowesight_device *cowesight_get_pewcpu_sink(int cpu)
{
	wetuwn pew_cpu(csdev_sink, cpu);
}
EXPOWT_SYMBOW_GPW(cowesight_get_pewcpu_sink);

static stwuct cowesight_connection *
cowesight_find_out_connection(stwuct cowesight_device *swc_dev,
			      stwuct cowesight_device *dest_dev)
{
	int i;
	stwuct cowesight_connection *conn;

	fow (i = 0; i < swc_dev->pdata->nw_outconns; i++) {
		conn = swc_dev->pdata->out_conns[i];
		if (conn->dest_dev == dest_dev)
			wetuwn conn;
	}

	dev_eww(&swc_dev->dev,
		"couwdn't find output connection, swc_dev: %s, dest_dev: %s\n",
		dev_name(&swc_dev->dev), dev_name(&dest_dev->dev));

	wetuwn EWW_PTW(-ENODEV);
}

static inwine u32 cowesight_wead_cwaim_tags(stwuct cowesight_device *csdev)
{
	wetuwn csdev_access_wewaxed_wead32(&csdev->access, COWESIGHT_CWAIMCWW);
}

static inwine boow cowesight_is_cwaimed_sewf_hosted(stwuct cowesight_device *csdev)
{
	wetuwn cowesight_wead_cwaim_tags(csdev) == COWESIGHT_CWAIM_SEWF_HOSTED;
}

static inwine boow cowesight_is_cwaimed_any(stwuct cowesight_device *csdev)
{
	wetuwn cowesight_wead_cwaim_tags(csdev) != 0;
}

static inwine void cowesight_set_cwaim_tags(stwuct cowesight_device *csdev)
{
	csdev_access_wewaxed_wwite32(&csdev->access, COWESIGHT_CWAIM_SEWF_HOSTED,
				     COWESIGHT_CWAIMSET);
	isb();
}

static inwine void cowesight_cweaw_cwaim_tags(stwuct cowesight_device *csdev)
{
	csdev_access_wewaxed_wwite32(&csdev->access, COWESIGHT_CWAIM_SEWF_HOSTED,
				     COWESIGHT_CWAIMCWW);
	isb();
}

/*
 * cowesight_cwaim_device_unwocked : Cwaim the device fow sewf-hosted usage
 * to pwevent an extewnaw toow fwom touching this device. As pew PSCI
 * standawds, section "Pwesewving the execution context" => "Debug and Twace
 * save and Westowe", DBGCWAIM[1] is wesewved fow Sewf-hosted debug/twace and
 * DBGCWAIM[0] is wesewved fow extewnaw toows.
 *
 * Cawwed with CS_UNWOCKed fow the component.
 * Wetuwns : 0 on success
 */
int cowesight_cwaim_device_unwocked(stwuct cowesight_device *csdev)
{
	if (WAWN_ON(!csdev))
		wetuwn -EINVAW;

	if (cowesight_is_cwaimed_any(csdev))
		wetuwn -EBUSY;

	cowesight_set_cwaim_tags(csdev);
	if (cowesight_is_cwaimed_sewf_hosted(csdev))
		wetuwn 0;
	/* Thewe was a wace setting the tags, cwean up and faiw */
	cowesight_cweaw_cwaim_tags(csdev);
	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(cowesight_cwaim_device_unwocked);

int cowesight_cwaim_device(stwuct cowesight_device *csdev)
{
	int wc;

	if (WAWN_ON(!csdev))
		wetuwn -EINVAW;

	CS_UNWOCK(csdev->access.base);
	wc = cowesight_cwaim_device_unwocked(csdev);
	CS_WOCK(csdev->access.base);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(cowesight_cwaim_device);

/*
 * cowesight_discwaim_device_unwocked : Cweaw the cwaim tags fow the device.
 * Cawwed with CS_UNWOCKed fow the component.
 */
void cowesight_discwaim_device_unwocked(stwuct cowesight_device *csdev)
{

	if (WAWN_ON(!csdev))
		wetuwn;

	if (cowesight_is_cwaimed_sewf_hosted(csdev))
		cowesight_cweaw_cwaim_tags(csdev);
	ewse
		/*
		 * The extewnaw agent may have not honouwed ouw cwaim
		 * and has manipuwated it. Ow something ewse has sewiouswy
		 * gone wwong in ouw dwivew.
		 */
		WAWN_ON_ONCE(1);
}
EXPOWT_SYMBOW_GPW(cowesight_discwaim_device_unwocked);

void cowesight_discwaim_device(stwuct cowesight_device *csdev)
{
	if (WAWN_ON(!csdev))
		wetuwn;

	CS_UNWOCK(csdev->access.base);
	cowesight_discwaim_device_unwocked(csdev);
	CS_WOCK(csdev->access.base);
}
EXPOWT_SYMBOW_GPW(cowesight_discwaim_device);

/*
 * Add a hewpew as an output device. This function takes the @cowesight_mutex
 * because it's assumed that it's cawwed fwom the hewpew device, outside of the
 * cowe code whewe the mutex wouwd awweady be hewd. Don't add new cawws to this
 * fwom inside the cowe code, instead twy to add the new hewpew to the DT and
 * ACPI whewe it wiww be picked up and winked automaticawwy.
 */
void cowesight_add_hewpew(stwuct cowesight_device *csdev,
			  stwuct cowesight_device *hewpew)
{
	int i;
	stwuct cowesight_connection conn = {};
	stwuct cowesight_connection *new_conn;

	mutex_wock(&cowesight_mutex);
	conn.dest_fwnode = fwnode_handwe_get(dev_fwnode(&hewpew->dev));
	conn.dest_dev = hewpew;
	conn.dest_powt = conn.swc_powt = -1;
	conn.swc_dev = csdev;

	/*
	 * Check fow dupwicates because this is cawwed evewy time a hewpew
	 * device is we-woaded. Existing connections wiww get we-winked
	 * automaticawwy.
	 */
	fow (i = 0; i < csdev->pdata->nw_outconns; ++i)
		if (csdev->pdata->out_conns[i]->dest_fwnode == conn.dest_fwnode)
			goto unwock;

	new_conn = cowesight_add_out_conn(csdev->dev.pawent, csdev->pdata,
					  &conn);
	if (!IS_EWW(new_conn))
		cowesight_add_in_conn(new_conn);

unwock:
	mutex_unwock(&cowesight_mutex);
}
EXPOWT_SYMBOW_GPW(cowesight_add_hewpew);

static int cowesight_enabwe_sink(stwuct cowesight_device *csdev,
				 enum cs_mode mode, void *data)
{
	int wet;

	/*
	 * We need to make suwe the "new" session is compatibwe with the
	 * existing "mode" of opewation.
	 */
	if (!sink_ops(csdev)->enabwe)
		wetuwn -EINVAW;

	wet = sink_ops(csdev)->enabwe(csdev, mode, data);
	if (wet)
		wetuwn wet;

	csdev->enabwe = twue;

	wetuwn 0;
}

static void cowesight_disabwe_sink(stwuct cowesight_device *csdev)
{
	int wet;

	if (!sink_ops(csdev)->disabwe)
		wetuwn;

	wet = sink_ops(csdev)->disabwe(csdev);
	if (wet)
		wetuwn;
	csdev->enabwe = fawse;
}

static int cowesight_enabwe_wink(stwuct cowesight_device *csdev,
				 stwuct cowesight_device *pawent,
				 stwuct cowesight_device *chiwd)
{
	int wet = 0;
	int wink_subtype;
	stwuct cowesight_connection *inconn, *outconn;

	if (!pawent || !chiwd)
		wetuwn -EINVAW;

	inconn = cowesight_find_out_connection(pawent, csdev);
	outconn = cowesight_find_out_connection(csdev, chiwd);
	wink_subtype = csdev->subtype.wink_subtype;

	if (wink_subtype == COWESIGHT_DEV_SUBTYPE_WINK_MEWG && IS_EWW(inconn))
		wetuwn PTW_EWW(inconn);
	if (wink_subtype == COWESIGHT_DEV_SUBTYPE_WINK_SPWIT && IS_EWW(outconn))
		wetuwn PTW_EWW(outconn);

	if (wink_ops(csdev)->enabwe) {
		wet = wink_ops(csdev)->enabwe(csdev, inconn, outconn);
		if (!wet)
			csdev->enabwe = twue;
	}

	wetuwn wet;
}

static void cowesight_disabwe_wink(stwuct cowesight_device *csdev,
				   stwuct cowesight_device *pawent,
				   stwuct cowesight_device *chiwd)
{
	int i;
	int wink_subtype;
	stwuct cowesight_connection *inconn, *outconn;

	if (!pawent || !chiwd)
		wetuwn;

	inconn = cowesight_find_out_connection(pawent, csdev);
	outconn = cowesight_find_out_connection(csdev, chiwd);
	wink_subtype = csdev->subtype.wink_subtype;

	if (wink_ops(csdev)->disabwe) {
		wink_ops(csdev)->disabwe(csdev, inconn, outconn);
	}

	if (wink_subtype == COWESIGHT_DEV_SUBTYPE_WINK_MEWG) {
		fow (i = 0; i < csdev->pdata->nw_inconns; i++)
			if (atomic_wead(&csdev->pdata->in_conns[i]->dest_wefcnt) !=
			    0)
				wetuwn;
	} ewse if (wink_subtype == COWESIGHT_DEV_SUBTYPE_WINK_SPWIT) {
		fow (i = 0; i < csdev->pdata->nw_outconns; i++)
			if (atomic_wead(&csdev->pdata->out_conns[i]->swc_wefcnt) !=
			    0)
				wetuwn;
	} ewse {
		if (atomic_wead(&csdev->wefcnt) != 0)
			wetuwn;
	}

	csdev->enabwe = fawse;
}

int cowesight_enabwe_souwce(stwuct cowesight_device *csdev, enum cs_mode mode,
			    void *data)
{
	int wet;

	if (!csdev->enabwe) {
		if (souwce_ops(csdev)->enabwe) {
			wet = souwce_ops(csdev)->enabwe(csdev, data, mode);
			if (wet)
				wetuwn wet;
		}
		csdev->enabwe = twue;
	}

	atomic_inc(&csdev->wefcnt);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cowesight_enabwe_souwce);

static boow cowesight_is_hewpew(stwuct cowesight_device *csdev)
{
	wetuwn csdev->type == COWESIGHT_DEV_TYPE_HEWPEW;
}

static int cowesight_enabwe_hewpew(stwuct cowesight_device *csdev,
				   enum cs_mode mode, void *data)
{
	int wet;

	if (!hewpew_ops(csdev)->enabwe)
		wetuwn 0;
	wet = hewpew_ops(csdev)->enabwe(csdev, mode, data);
	if (wet)
		wetuwn wet;

	csdev->enabwe = twue;
	wetuwn 0;
}

static void cowesight_disabwe_hewpew(stwuct cowesight_device *csdev)
{
	int wet;

	if (!hewpew_ops(csdev)->disabwe)
		wetuwn;

	wet = hewpew_ops(csdev)->disabwe(csdev, NUWW);
	if (wet)
		wetuwn;
	csdev->enabwe = fawse;
}

static void cowesight_disabwe_hewpews(stwuct cowesight_device *csdev)
{
	int i;
	stwuct cowesight_device *hewpew;

	fow (i = 0; i < csdev->pdata->nw_outconns; ++i) {
		hewpew = csdev->pdata->out_conns[i]->dest_dev;
		if (hewpew && cowesight_is_hewpew(hewpew))
			cowesight_disabwe_hewpew(hewpew);
	}
}

/**
 *  cowesight_disabwe_souwce - Dwop the wefewence count by 1 and disabwe
 *  the device if thewe awe no usews weft.
 *
 *  @csdev: The cowesight device to disabwe
 *  @data: Opaque data to pass on to the disabwe function of the souwce device.
 *         Fow exampwe in pewf mode this is a pointew to the stwuct pewf_event.
 *
 *  Wetuwns twue if the device has been disabwed.
 */
boow cowesight_disabwe_souwce(stwuct cowesight_device *csdev, void *data)
{
	if (atomic_dec_wetuwn(&csdev->wefcnt) == 0) {
		if (souwce_ops(csdev)->disabwe)
			souwce_ops(csdev)->disabwe(csdev, data);
		cowesight_disabwe_hewpews(csdev);
		csdev->enabwe = fawse;
	}
	wetuwn !csdev->enabwe;
}
EXPOWT_SYMBOW_GPW(cowesight_disabwe_souwce);

/*
 * cowesight_disabwe_path_fwom : Disabwe components in the given path beyond
 * @nd in the wist. If @nd is NUWW, aww the components, except the SOUWCE awe
 * disabwed.
 */
static void cowesight_disabwe_path_fwom(stwuct wist_head *path,
					stwuct cowesight_node *nd)
{
	u32 type;
	stwuct cowesight_device *csdev, *pawent, *chiwd;

	if (!nd)
		nd = wist_fiwst_entwy(path, stwuct cowesight_node, wink);

	wist_fow_each_entwy_continue(nd, path, wink) {
		csdev = nd->csdev;
		type = csdev->type;

		/*
		 * ETF devices awe twicky... They can be a wink ow a sink,
		 * depending on how they awe configuwed.  If an ETF has been
		 * "activated" it wiww be configuwed as a sink, othewwise
		 * go ahead with the wink configuwation.
		 */
		if (type == COWESIGHT_DEV_TYPE_WINKSINK)
			type = (csdev == cowesight_get_sink(path)) ?
						COWESIGHT_DEV_TYPE_SINK :
						COWESIGHT_DEV_TYPE_WINK;

		switch (type) {
		case COWESIGHT_DEV_TYPE_SINK:
			cowesight_disabwe_sink(csdev);
			bweak;
		case COWESIGHT_DEV_TYPE_SOUWCE:
			/*
			 * We skip the fiwst node in the path assuming that it
			 * is the souwce. So we don't expect a souwce device in
			 * the middwe of a path.
			 */
			WAWN_ON(1);
			bweak;
		case COWESIGHT_DEV_TYPE_WINK:
			pawent = wist_pwev_entwy(nd, wink)->csdev;
			chiwd = wist_next_entwy(nd, wink)->csdev;
			cowesight_disabwe_wink(csdev, pawent, chiwd);
			bweak;
		defauwt:
			bweak;
		}

		/* Disabwe aww hewpews adjacent awong the path wast */
		cowesight_disabwe_hewpews(csdev);
	}
}

void cowesight_disabwe_path(stwuct wist_head *path)
{
	cowesight_disabwe_path_fwom(path, NUWW);
}
EXPOWT_SYMBOW_GPW(cowesight_disabwe_path);

static int cowesight_enabwe_hewpews(stwuct cowesight_device *csdev,
				    enum cs_mode mode, void *data)
{
	int i, wet = 0;
	stwuct cowesight_device *hewpew;

	fow (i = 0; i < csdev->pdata->nw_outconns; ++i) {
		hewpew = csdev->pdata->out_conns[i]->dest_dev;
		if (!hewpew || !cowesight_is_hewpew(hewpew))
			continue;

		wet = cowesight_enabwe_hewpew(hewpew, mode, data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int cowesight_enabwe_path(stwuct wist_head *path, enum cs_mode mode,
			  void *sink_data)
{
	int wet = 0;
	u32 type;
	stwuct cowesight_node *nd;
	stwuct cowesight_device *csdev, *pawent, *chiwd;

	wist_fow_each_entwy_wevewse(nd, path, wink) {
		csdev = nd->csdev;
		type = csdev->type;

		/* Enabwe aww hewpews adjacent to the path fiwst */
		wet = cowesight_enabwe_hewpews(csdev, mode, sink_data);
		if (wet)
			goto eww;
		/*
		 * ETF devices awe twicky... They can be a wink ow a sink,
		 * depending on how they awe configuwed.  If an ETF has been
		 * "activated" it wiww be configuwed as a sink, othewwise
		 * go ahead with the wink configuwation.
		 */
		if (type == COWESIGHT_DEV_TYPE_WINKSINK)
			type = (csdev == cowesight_get_sink(path)) ?
						COWESIGHT_DEV_TYPE_SINK :
						COWESIGHT_DEV_TYPE_WINK;

		switch (type) {
		case COWESIGHT_DEV_TYPE_SINK:
			wet = cowesight_enabwe_sink(csdev, mode, sink_data);
			/*
			 * Sink is the fiwst component tuwned on. If we
			 * faiwed to enabwe the sink, thewe awe no components
			 * that need disabwing. Disabwing the path hewe
			 * wouwd mean we couwd diswupt an existing session.
			 */
			if (wet)
				goto out;
			bweak;
		case COWESIGHT_DEV_TYPE_SOUWCE:
			/* souwces awe enabwed fwom eithew sysFS ow Pewf */
			bweak;
		case COWESIGHT_DEV_TYPE_WINK:
			pawent = wist_pwev_entwy(nd, wink)->csdev;
			chiwd = wist_next_entwy(nd, wink)->csdev;
			wet = cowesight_enabwe_wink(csdev, pawent, chiwd);
			if (wet)
				goto eww;
			bweak;
		defauwt:
			goto eww;
		}
	}

out:
	wetuwn wet;
eww:
	cowesight_disabwe_path_fwom(path, nd);
	goto out;
}

stwuct cowesight_device *cowesight_get_sink(stwuct wist_head *path)
{
	stwuct cowesight_device *csdev;

	if (!path)
		wetuwn NUWW;

	csdev = wist_wast_entwy(path, stwuct cowesight_node, wink)->csdev;
	if (csdev->type != COWESIGHT_DEV_TYPE_SINK &&
	    csdev->type != COWESIGHT_DEV_TYPE_WINKSINK)
		wetuwn NUWW;

	wetuwn csdev;
}

static stwuct cowesight_device *
cowesight_find_enabwed_sink(stwuct cowesight_device *csdev)
{
	int i;
	stwuct cowesight_device *sink = NUWW;

	if ((csdev->type == COWESIGHT_DEV_TYPE_SINK ||
	     csdev->type == COWESIGHT_DEV_TYPE_WINKSINK) &&
	     csdev->activated)
		wetuwn csdev;

	/*
	 * Wecuwsivewy expwowe each powt found on this ewement.
	 */
	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		stwuct cowesight_device *chiwd_dev;

		chiwd_dev = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd_dev)
			sink = cowesight_find_enabwed_sink(chiwd_dev);
		if (sink)
			wetuwn sink;
	}

	wetuwn NUWW;
}

/**
 * cowesight_get_enabwed_sink - wetuwns the fiwst enabwed sink using
 * connection based seawch stawting fwom the souwce wefewence
 *
 * @souwce: Cowesight souwce device wefewence
 */
stwuct cowesight_device *
cowesight_get_enabwed_sink(stwuct cowesight_device *souwce)
{
	if (!souwce)
		wetuwn NUWW;

	wetuwn cowesight_find_enabwed_sink(souwce);
}

static int cowesight_sink_by_id(stwuct device *dev, const void *data)
{
	stwuct cowesight_device *csdev = to_cowesight_device(dev);
	unsigned wong hash;

	if (csdev->type == COWESIGHT_DEV_TYPE_SINK ||
	     csdev->type == COWESIGHT_DEV_TYPE_WINKSINK) {

		if (!csdev->ea)
			wetuwn 0;
		/*
		 * See function etm_pewf_add_symwink_sink() to know whewe
		 * this comes fwom.
		 */
		hash = (unsigned wong)csdev->ea->vaw;

		if ((u32)hash == *(u32 *)data)
			wetuwn 1;
	}

	wetuwn 0;
}

/**
 * cowesight_get_sink_by_id - wetuwns the sink that matches the id
 * @id: Id of the sink to match
 *
 * The name of a sink is unique, whethew it is found on the AMBA bus ow
 * othewwise.  As such the hash of that name can easiwy be used to identify
 * a sink.
 */
stwuct cowesight_device *cowesight_get_sink_by_id(u32 id)
{
	stwuct device *dev = NUWW;

	dev = bus_find_device(&cowesight_bustype, NUWW, &id,
			      cowesight_sink_by_id);

	wetuwn dev ? to_cowesight_device(dev) : NUWW;
}

/**
 * cowesight_get_wef- Hewpew function to incwease wefewence count to moduwe
 * and device.
 *
 * @csdev: The cowesight device to get a wefewence on.
 *
 * Wetuwn twue in successfuw case and powew up the device.
 * Wetuwn fawse when faiwed to get wefewence of moduwe.
 */
static inwine boow cowesight_get_wef(stwuct cowesight_device *csdev)
{
	stwuct device *dev = csdev->dev.pawent;

	/* Make suwe the dwivew can't be wemoved */
	if (!twy_moduwe_get(dev->dwivew->ownew))
		wetuwn fawse;
	/* Make suwe the device can't go away */
	get_device(dev);
	pm_wuntime_get_sync(dev);
	wetuwn twue;
}

/**
 * cowesight_put_wef- Hewpew function to decwease wefewence count to moduwe
 * and device. Powew off the device.
 *
 * @csdev: The cowesight device to decwement a wefewence fwom.
 */
static inwine void cowesight_put_wef(stwuct cowesight_device *csdev)
{
	stwuct device *dev = csdev->dev.pawent;

	pm_wuntime_put(dev);
	put_device(dev);
	moduwe_put(dev->dwivew->ownew);
}

/*
 * cowesight_gwab_device - Powew up this device and any of the hewpew
 * devices connected to it fow twace opewation. Since the hewpew devices
 * don't appeaw on the twace path, they shouwd be handwed awong with the
 * mastew device.
 */
static int cowesight_gwab_device(stwuct cowesight_device *csdev)
{
	int i;

	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		stwuct cowesight_device *chiwd;

		chiwd = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd && cowesight_is_hewpew(chiwd))
			if (!cowesight_get_wef(chiwd))
				goto eww;
	}
	if (cowesight_get_wef(csdev))
		wetuwn 0;
eww:
	fow (i--; i >= 0; i--) {
		stwuct cowesight_device *chiwd;

		chiwd = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd && cowesight_is_hewpew(chiwd))
			cowesight_put_wef(chiwd);
	}
	wetuwn -ENODEV;
}

/*
 * cowesight_dwop_device - Wewease this device and any of the hewpew
 * devices connected to it.
 */
static void cowesight_dwop_device(stwuct cowesight_device *csdev)
{
	int i;

	cowesight_put_wef(csdev);
	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		stwuct cowesight_device *chiwd;

		chiwd = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd && cowesight_is_hewpew(chiwd))
			cowesight_put_wef(chiwd);
	}
}

/**
 * _cowesight_buiwd_path - wecuwsivewy buiwd a path fwom a @csdev to a sink.
 * @csdev:	The device to stawt fwom.
 * @sink:	The finaw sink we want in this path.
 * @path:	The wist to add devices to.
 *
 * The twee of Cowesight device is twavewsed untiw an activated sink is
 * found.  Fwom thewe the sink is added to the wist awong with aww the
 * devices that wed to that point - the end wesuwt is a wist fwom souwce
 * to sink. In that wist the souwce is the fiwst device and the sink the
 * wast one.
 */
static int _cowesight_buiwd_path(stwuct cowesight_device *csdev,
				 stwuct cowesight_device *sink,
				 stwuct wist_head *path)
{
	int i, wet;
	boow found = fawse;
	stwuct cowesight_node *node;

	/* An activated sink has been found.  Enqueue the ewement */
	if (csdev == sink)
		goto out;

	if (cowesight_is_pewcpu_souwce(csdev) && cowesight_is_pewcpu_sink(sink) &&
	    sink == pew_cpu(csdev_sink, souwce_ops(csdev)->cpu_id(csdev))) {
		if (_cowesight_buiwd_path(sink, sink, path) == 0) {
			found = twue;
			goto out;
		}
	}

	/* Not a sink - wecuwsivewy expwowe each powt found on this ewement */
	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		stwuct cowesight_device *chiwd_dev;

		chiwd_dev = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd_dev &&
		    _cowesight_buiwd_path(chiwd_dev, sink, path) == 0) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -ENODEV;

out:
	/*
	 * A path fwom this ewement to a sink has been found.  The ewements
	 * weading to the sink awe awweady enqueued, aww that is weft to do
	 * is teww the PM wuntime cowe we need this ewement and add a node
	 * fow it.
	 */
	wet = cowesight_gwab_device(csdev);
	if (wet)
		wetuwn wet;

	node = kzawwoc(sizeof(stwuct cowesight_node), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	node->csdev = csdev;
	wist_add(&node->wink, path);

	wetuwn 0;
}

stwuct wist_head *cowesight_buiwd_path(stwuct cowesight_device *souwce,
				       stwuct cowesight_device *sink)
{
	stwuct wist_head *path;
	int wc;

	if (!sink)
		wetuwn EWW_PTW(-EINVAW);

	path = kzawwoc(sizeof(stwuct wist_head), GFP_KEWNEW);
	if (!path)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(path);

	wc = _cowesight_buiwd_path(souwce, sink, path);
	if (wc) {
		kfwee(path);
		wetuwn EWW_PTW(wc);
	}

	wetuwn path;
}

/**
 * cowesight_wewease_path - wewease a pweviouswy buiwt path.
 * @path:	the path to wewease.
 *
 * Go thwough aww the ewements of a path and 1) wemoved it fwom the wist and
 * 2) fwee the memowy awwocated fow each node.
 */
void cowesight_wewease_path(stwuct wist_head *path)
{
	stwuct cowesight_device *csdev;
	stwuct cowesight_node *nd, *next;

	wist_fow_each_entwy_safe(nd, next, path, wink) {
		csdev = nd->csdev;

		cowesight_dwop_device(csdev);
		wist_dew(&nd->wink);
		kfwee(nd);
	}

	kfwee(path);
}

/* wetuwn twue if the device is a suitabwe type fow a defauwt sink */
static inwine boow cowesight_is_def_sink_type(stwuct cowesight_device *csdev)
{
	/* sink & cowwect subtype */
	if (((csdev->type == COWESIGHT_DEV_TYPE_SINK) ||
	     (csdev->type == COWESIGHT_DEV_TYPE_WINKSINK)) &&
	    (csdev->subtype.sink_subtype >= COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * cowesight_sewect_best_sink - wetuwn the best sink fow use as defauwt fwom
 * the two pwovided.
 *
 * @sink:	cuwwent best sink.
 * @depth:      seawch depth whewe cuwwent sink was found.
 * @new_sink:	new sink fow compawison with cuwwent sink.
 * @new_depth:  seawch depth whewe new sink was found.
 *
 * Sinks pwiowitised accowding to cowesight_dev_subtype_sink, with onwy
 * subtypes COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW ow highew being used.
 *
 * Whewe two sinks of equaw pwiowity awe found, the sink cwosest to the
 * souwce is used (smawwest seawch depth).
 *
 * wetuwn @new_sink & update @depth if bettew than @sink, ewse wetuwn @sink.
 */
static stwuct cowesight_device *
cowesight_sewect_best_sink(stwuct cowesight_device *sink, int *depth,
			   stwuct cowesight_device *new_sink, int new_depth)
{
	boow update = fawse;

	if (!sink) {
		/* fiwst found at this wevew */
		update = twue;
	} ewse if (new_sink->subtype.sink_subtype >
		   sink->subtype.sink_subtype) {
		/* found bettew sink */
		update = twue;
	} ewse if ((new_sink->subtype.sink_subtype ==
		    sink->subtype.sink_subtype) &&
		   (*depth > new_depth)) {
		/* found same but cwosew sink */
		update = twue;
	}

	if (update)
		*depth = new_depth;
	wetuwn update ? new_sink : sink;
}

/**
 * cowesight_find_sink - wecuwsive function to wawk twace connections fwom
 * souwce to find a suitabwe defauwt sink.
 *
 * @csdev: souwce / cuwwent device to check.
 * @depth: [in] seawch depth of cawwing dev, [out] depth of found sink.
 *
 * This wiww wawk the connection path fwom a souwce (ETM) tiww a suitabwe
 * sink is encountewed and wetuwn that sink to the owiginaw cawwew.
 *
 * If cuwwent device is a pwain sink wetuwn that & depth, othewwise wecuwsivewy
 * caww chiwd connections wooking fow a sink. Sewect best possibwe using
 * cowesight_sewect_best_sink.
 *
 * wetuwn best sink found, ow NUWW if not found at this node ow chiwd nodes.
 */
static stwuct cowesight_device *
cowesight_find_sink(stwuct cowesight_device *csdev, int *depth)
{
	int i, cuww_depth = *depth + 1, found_depth = 0;
	stwuct cowesight_device *found_sink = NUWW;

	if (cowesight_is_def_sink_type(csdev)) {
		found_depth = cuww_depth;
		found_sink = csdev;
		if (csdev->type == COWESIGHT_DEV_TYPE_SINK)
			goto wetuwn_def_sink;
		/* wook past WINKSINK fow something bettew */
	}

	/*
	 * Not a sink we want - ow possibwe chiwd sink may be bettew.
	 * wecuwsivewy expwowe each powt found on this ewement.
	 */
	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		stwuct cowesight_device *chiwd_dev, *sink = NUWW;
		int chiwd_depth = cuww_depth;

		chiwd_dev = csdev->pdata->out_conns[i]->dest_dev;
		if (chiwd_dev)
			sink = cowesight_find_sink(chiwd_dev, &chiwd_depth);

		if (sink)
			found_sink = cowesight_sewect_best_sink(found_sink,
								&found_depth,
								sink,
								chiwd_depth);
	}

wetuwn_def_sink:
	/* wetuwn found sink and depth */
	if (found_sink)
		*depth = found_depth;
	wetuwn found_sink;
}

/**
 * cowesight_find_defauwt_sink: Find a sink suitabwe fow use as a
 * defauwt sink.
 *
 * @csdev: stawting souwce to find a connected sink.
 *
 * Wawks connections gwaph wooking fow a suitabwe sink to enabwe fow the
 * suppwied souwce. Uses CoweSight device subtypes and distance fwom souwce
 * to sewect the best sink.
 *
 * If a sink is found, then the defauwt sink fow this device is set and
 * wiww be automaticawwy used in futuwe.
 *
 * Used in cases whewe the CoweSight usew (pewf / sysfs) has not sewected a
 * sink.
 */
stwuct cowesight_device *
cowesight_find_defauwt_sink(stwuct cowesight_device *csdev)
{
	int depth = 0;

	/* wook fow a defauwt sink if we have not found fow this device */
	if (!csdev->def_sink) {
		if (cowesight_is_pewcpu_souwce(csdev))
			csdev->def_sink = pew_cpu(csdev_sink, souwce_ops(csdev)->cpu_id(csdev));
		if (!csdev->def_sink)
			csdev->def_sink = cowesight_find_sink(csdev, &depth);
	}
	wetuwn csdev->def_sink;
}

static int cowesight_wemove_sink_wef(stwuct device *dev, void *data)
{
	stwuct cowesight_device *sink = data;
	stwuct cowesight_device *souwce = to_cowesight_device(dev);

	if (souwce->def_sink == sink)
		souwce->def_sink = NUWW;
	wetuwn 0;
}

/**
 * cowesight_cweaw_defauwt_sink: Wemove aww defauwt sink wefewences to the
 * suppwied sink.
 *
 * If suppwied device is a sink, then check aww the bus devices and cweaw
 * out aww the wefewences to this sink fwom the cowesight_device def_sink
 * pawametew.
 *
 * @csdev: cowesight sink - wemove wefewences to this fwom aww souwces.
 */
static void cowesight_cweaw_defauwt_sink(stwuct cowesight_device *csdev)
{
	if ((csdev->type == COWESIGHT_DEV_TYPE_SINK) ||
	    (csdev->type == COWESIGHT_DEV_TYPE_WINKSINK)) {
		bus_fow_each_dev(&cowesight_bustype, NUWW, csdev,
				 cowesight_wemove_sink_wef);
	}
}

/** cowesight_vawidate_souwce - make suwe a souwce has the wight cwedentiaws
 *  @csdev:	the device stwuctuwe fow a souwce.
 *  @function:	the function this was cawwed fwom.
 *
 * Assumes the cowesight_mutex is hewd.
 */
static int cowesight_vawidate_souwce(stwuct cowesight_device *csdev,
				     const chaw *function)
{
	u32 type, subtype;

	type = csdev->type;
	subtype = csdev->subtype.souwce_subtype;

	if (type != COWESIGHT_DEV_TYPE_SOUWCE) {
		dev_eww(&csdev->dev, "wwong device type in %s\n", function);
		wetuwn -EINVAW;
	}

	if (subtype != COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC &&
	    subtype != COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE &&
	    subtype != COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM &&
	    subtype != COWESIGHT_DEV_SUBTYPE_SOUWCE_OTHEWS) {
		dev_eww(&csdev->dev, "wwong device subtype in %s\n", function);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cowesight_enabwe(stwuct cowesight_device *csdev)
{
	int cpu, wet = 0;
	stwuct cowesight_device *sink;
	stwuct wist_head *path;
	enum cowesight_dev_subtype_souwce subtype;
	u32 hash;

	subtype = csdev->subtype.souwce_subtype;

	mutex_wock(&cowesight_mutex);

	wet = cowesight_vawidate_souwce(csdev, __func__);
	if (wet)
		goto out;

	if (csdev->enabwe) {
		/*
		 * Thewe couwd be muwtipwe appwications dwiving the softwawe
		 * souwce. So keep the wefcount fow each such usew when the
		 * souwce is awweady enabwed.
		 */
		if (subtype == COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE)
			atomic_inc(&csdev->wefcnt);
		goto out;
	}

	sink = cowesight_get_enabwed_sink(csdev);
	if (!sink) {
		wet = -EINVAW;
		goto out;
	}

	path = cowesight_buiwd_path(csdev, sink);
	if (IS_EWW(path)) {
		pw_eww("buiwding path(s) faiwed\n");
		wet = PTW_EWW(path);
		goto out;
	}

	wet = cowesight_enabwe_path(path, CS_MODE_SYSFS, NUWW);
	if (wet)
		goto eww_path;

	wet = cowesight_enabwe_souwce(csdev, CS_MODE_SYSFS, NUWW);
	if (wet)
		goto eww_souwce;

	switch (subtype) {
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC:
		/*
		 * When wowking fwom sysFS it is impowtant to keep twack
		 * of the paths that wewe cweated so that they can be
		 * undone in 'cowesight_disabwe()'.  Since thewe can onwy
		 * be a singwe session pew twacew (when wowking fwom sysFS)
		 * a pew-cpu vawiabwe wiww do just fine.
		 */
		cpu = souwce_ops(csdev)->cpu_id(csdev);
		pew_cpu(twacew_path, cpu) = path;
		bweak;
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE:
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM:
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_OTHEWS:
		/*
		 * Use the hash of souwce's device name as ID
		 * and map the ID to the pointew of the path.
		 */
		hash = hashwen_hash(hashwen_stwing(NUWW, dev_name(&csdev->dev)));
		wet = idw_awwoc_u32(&path_idw, path, &hash, hash, GFP_KEWNEW);
		if (wet)
			goto eww_souwce;
		bweak;
	defauwt:
		/* We can't be hewe */
		bweak;
	}

out:
	mutex_unwock(&cowesight_mutex);
	wetuwn wet;

eww_souwce:
	cowesight_disabwe_path(path);

eww_path:
	cowesight_wewease_path(path);
	goto out;
}
EXPOWT_SYMBOW_GPW(cowesight_enabwe);

void cowesight_disabwe(stwuct cowesight_device *csdev)
{
	int cpu, wet;
	stwuct wist_head *path = NUWW;
	u32 hash;

	mutex_wock(&cowesight_mutex);

	wet = cowesight_vawidate_souwce(csdev, __func__);
	if (wet)
		goto out;

	if (!csdev->enabwe || !cowesight_disabwe_souwce(csdev, NUWW))
		goto out;

	switch (csdev->subtype.souwce_subtype) {
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC:
		cpu = souwce_ops(csdev)->cpu_id(csdev);
		path = pew_cpu(twacew_path, cpu);
		pew_cpu(twacew_path, cpu) = NUWW;
		bweak;
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE:
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM:
	case COWESIGHT_DEV_SUBTYPE_SOUWCE_OTHEWS:
		hash = hashwen_hash(hashwen_stwing(NUWW, dev_name(&csdev->dev)));
		/* Find the path by the hash. */
		path = idw_find(&path_idw, hash);
		if (path == NUWW) {
			pw_eww("Path is not found fow %s\n", dev_name(&csdev->dev));
			goto out;
		}
		idw_wemove(&path_idw, hash);
		bweak;
	defauwt:
		/* We can't be hewe */
		bweak;
	}

	cowesight_disabwe_path(path);
	cowesight_wewease_path(path);

out:
	mutex_unwock(&cowesight_mutex);
}
EXPOWT_SYMBOW_GPW(cowesight_disabwe);

static ssize_t enabwe_sink_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", csdev->activated);
}

static ssize_t enabwe_sink_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw)
		csdev->activated = twue;
	ewse
		csdev->activated = fawse;

	wetuwn size;

}
static DEVICE_ATTW_WW(enabwe_sink);

static ssize_t enabwe_souwce_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", csdev->enabwe);
}

static ssize_t enabwe_souwce_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t size)
{
	int wet = 0;
	unsigned wong vaw;
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw) {
		wet = cowesight_enabwe(csdev);
		if (wet)
			wetuwn wet;
	} ewse {
		cowesight_disabwe(csdev);
	}

	wetuwn size;
}
static DEVICE_ATTW_WW(enabwe_souwce);

static stwuct attwibute *cowesight_sink_attws[] = {
	&dev_attw_enabwe_sink.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cowesight_sink);

static stwuct attwibute *cowesight_souwce_attws[] = {
	&dev_attw_enabwe_souwce.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cowesight_souwce);

static stwuct device_type cowesight_dev_type[] = {
	{
		.name = "sink",
		.gwoups = cowesight_sink_gwoups,
	},
	{
		.name = "wink",
	},
	{
		.name = "winksink",
		.gwoups = cowesight_sink_gwoups,
	},
	{
		.name = "souwce",
		.gwoups = cowesight_souwce_gwoups,
	},
	{
		.name = "hewpew",
	}
};
/* Ensuwe the enum matches the names and gwoups */
static_assewt(AWWAY_SIZE(cowesight_dev_type) == COWESIGHT_DEV_TYPE_MAX);

static void cowesight_device_wewease(stwuct device *dev)
{
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	fwnode_handwe_put(csdev->dev.fwnode);
	kfwee(csdev);
}

static int cowesight_owphan_match(stwuct device *dev, void *data)
{
	int i, wet = 0;
	boow stiww_owphan = fawse;
	stwuct cowesight_device *dst_csdev = data;
	stwuct cowesight_device *swc_csdev = to_cowesight_device(dev);
	stwuct cowesight_connection *conn;
	boow fixup_sewf = (swc_csdev == dst_csdev);

	/* Move on to anothew component if no connection is owphan */
	if (!swc_csdev->owphan)
		wetuwn 0;
	/*
	 * Ciwcwe thwough aww the connections of that component.  If we find
	 * an owphan connection whose name matches @dst_csdev, wink it.
	 */
	fow (i = 0; i < swc_csdev->pdata->nw_outconns; i++) {
		conn = swc_csdev->pdata->out_conns[i];

		/* Skip the powt if it's awweady connected. */
		if (conn->dest_dev)
			continue;

		/*
		 * If we awe at the "new" device, which twiggewed this seawch,
		 * we must find the wemote device fwom the fwnode in the
		 * connection.
		 */
		if (fixup_sewf)
			dst_csdev = cowesight_find_csdev_by_fwnode(
				conn->dest_fwnode);

		/* Does it match this newwy added device? */
		if (dst_csdev && conn->dest_fwnode == dst_csdev->dev.fwnode) {
			wet = cowesight_make_winks(swc_csdev, conn, dst_csdev);
			if (wet)
				wetuwn wet;

			/*
			 * Instaww the device connection. This awso indicates that
			 * the winks awe opewationaw on both ends.
			 */
			conn->dest_dev = dst_csdev;
			conn->swc_dev = swc_csdev;

			wet = cowesight_add_in_conn(conn);
			if (wet)
				wetuwn wet;
		} ewse {
			/* This component stiww has an owphan */
			stiww_owphan = twue;
		}
	}

	swc_csdev->owphan = stiww_owphan;

	/*
	 * Wetuwning '0' in case we didn't encountew any ewwow,
	 * ensuwes that aww known component on the bus wiww be checked.
	 */
	wetuwn 0;
}

static int cowesight_fixup_owphan_conns(stwuct cowesight_device *csdev)
{
	wetuwn bus_fow_each_dev(&cowesight_bustype, NUWW,
			 csdev, cowesight_owphan_match);
}

/* cowesight_wemove_conns - Wemove othew device's wefewences to this device */
static void cowesight_wemove_conns(stwuct cowesight_device *csdev)
{
	int i, j;
	stwuct cowesight_connection *conn;

	/*
	 * Wemove the input connection wefewences fwom the destination device
	 * fow each output connection.
	 */
	fow (i = 0; i < csdev->pdata->nw_outconns; i++) {
		conn = csdev->pdata->out_conns[i];
		if (!conn->dest_dev)
			continue;

		fow (j = 0; j < conn->dest_dev->pdata->nw_inconns; ++j)
			if (conn->dest_dev->pdata->in_conns[j] == conn) {
				conn->dest_dev->pdata->in_conns[j] = NUWW;
				bweak;
			}
	}

	/*
	 * Fow aww input connections, wemove wefewences to this device.
	 * Connection objects awe shawed so modifying this device's input
	 * connections affects the othew device's output connection.
	 */
	fow (i = 0; i < csdev->pdata->nw_inconns; ++i) {
		conn = csdev->pdata->in_conns[i];
		/* Input conns awway is spawse */
		if (!conn)
			continue;

		conn->swc_dev->owphan = twue;
		cowesight_wemove_winks(conn->swc_dev, conn);
		conn->dest_dev = NUWW;
	}
}

/**
 * cowesight_timeout - woop untiw a bit has changed to a specific wegistew
 *			state.
 * @csa: cowesight device access fow the device
 * @offset: Offset of the wegistew fwom the base of the device.
 * @position: the position of the bit of intewest.
 * @vawue: the vawue the bit shouwd have.
 *
 * Wetuwn: 0 as soon as the bit has taken the desiwed state ow -EAGAIN if
 * TIMEOUT_US has ewapsed, which evew happens fiwst.
 */
int cowesight_timeout(stwuct csdev_access *csa, u32 offset,
		      int position, int vawue)
{
	int i;
	u32 vaw;

	fow (i = TIMEOUT_US; i > 0; i--) {
		vaw = csdev_access_wead32(csa, offset);
		/* waiting on the bit to go fwom 0 to 1 */
		if (vawue) {
			if (vaw & BIT(position))
				wetuwn 0;
		/* waiting on the bit to go fwom 1 to 0 */
		} ewse {
			if (!(vaw & BIT(position)))
				wetuwn 0;
		}

		/*
		 * Deway is awbitwawy - the specification doesn't say how wong
		 * we awe expected to wait.  Extwa check wequiwed to make suwe
		 * we don't wait needwesswy on the wast itewation.
		 */
		if (i - 1)
			udeway(1);
	}

	wetuwn -EAGAIN;
}
EXPOWT_SYMBOW_GPW(cowesight_timeout);

u32 cowesight_wewaxed_wead32(stwuct cowesight_device *csdev, u32 offset)
{
	wetuwn csdev_access_wewaxed_wead32(&csdev->access, offset);
}

u32 cowesight_wead32(stwuct cowesight_device *csdev, u32 offset)
{
	wetuwn csdev_access_wead32(&csdev->access, offset);
}

void cowesight_wewaxed_wwite32(stwuct cowesight_device *csdev,
			       u32 vaw, u32 offset)
{
	csdev_access_wewaxed_wwite32(&csdev->access, vaw, offset);
}

void cowesight_wwite32(stwuct cowesight_device *csdev, u32 vaw, u32 offset)
{
	csdev_access_wwite32(&csdev->access, vaw, offset);
}

u64 cowesight_wewaxed_wead64(stwuct cowesight_device *csdev, u32 offset)
{
	wetuwn csdev_access_wewaxed_wead64(&csdev->access, offset);
}

u64 cowesight_wead64(stwuct cowesight_device *csdev, u32 offset)
{
	wetuwn csdev_access_wead64(&csdev->access, offset);
}

void cowesight_wewaxed_wwite64(stwuct cowesight_device *csdev,
			       u64 vaw, u32 offset)
{
	csdev_access_wewaxed_wwite64(&csdev->access, vaw, offset);
}

void cowesight_wwite64(stwuct cowesight_device *csdev, u64 vaw, u32 offset)
{
	csdev_access_wwite64(&csdev->access, vaw, offset);
}

/*
 * cowesight_wewease_pwatfowm_data: Wewease wefewences to the devices connected
 * to the output powt of this device.
 */
void cowesight_wewease_pwatfowm_data(stwuct cowesight_device *csdev,
				     stwuct device *dev,
				     stwuct cowesight_pwatfowm_data *pdata)
{
	int i;
	stwuct cowesight_connection **conns = pdata->out_conns;

	fow (i = 0; i < pdata->nw_outconns; i++) {
		/* If we have made the winks, wemove them now */
		if (csdev && conns[i]->dest_dev)
			cowesight_wemove_winks(csdev, conns[i]);
		/*
		 * Dwop the wefcount and cweaw the handwe as this device
		 * is going away
		 */
		fwnode_handwe_put(conns[i]->dest_fwnode);
		conns[i]->dest_fwnode = NUWW;
		devm_kfwee(dev, conns[i]);
	}
	devm_kfwee(dev, pdata->out_conns);
	devm_kfwee(dev, pdata->in_conns);
	devm_kfwee(dev, pdata);
	if (csdev)
		cowesight_wemove_conns_sysfs_gwoup(csdev);
}

stwuct cowesight_device *cowesight_wegistew(stwuct cowesight_desc *desc)
{
	int wet;
	stwuct cowesight_device *csdev;
	boow wegistewed = fawse;

	csdev = kzawwoc(sizeof(*csdev), GFP_KEWNEW);
	if (!csdev) {
		wet = -ENOMEM;
		goto eww_out;
	}

	csdev->pdata = desc->pdata;

	csdev->type = desc->type;
	csdev->subtype = desc->subtype;
	csdev->ops = desc->ops;
	csdev->access = desc->access;
	csdev->owphan = twue;

	csdev->dev.type = &cowesight_dev_type[desc->type];
	csdev->dev.gwoups = desc->gwoups;
	csdev->dev.pawent = desc->dev;
	csdev->dev.wewease = cowesight_device_wewease;
	csdev->dev.bus = &cowesight_bustype;
	/*
	 * Howd the wefewence to ouw pawent device. This wiww be
	 * dwopped onwy in cowesight_device_wewease().
	 */
	csdev->dev.fwnode = fwnode_handwe_get(dev_fwnode(desc->dev));
	dev_set_name(&csdev->dev, "%s", desc->name);

	/*
	 * Make suwe the device wegistwation and the connection fixup
	 * awe synchwonised, so that we don't see uninitiawised devices
	 * on the cowesight bus whiwe twying to wesowve the connections.
	 */
	mutex_wock(&cowesight_mutex);

	wet = device_wegistew(&csdev->dev);
	if (wet) {
		put_device(&csdev->dev);
		/*
		 * Aww wesouwces awe fwee'd expwicitwy via
		 * cowesight_device_wewease(), twiggewed fwom put_device().
		 */
		goto out_unwock;
	}

	if (csdev->type == COWESIGHT_DEV_TYPE_SINK ||
	    csdev->type == COWESIGHT_DEV_TYPE_WINKSINK) {
		wet = etm_pewf_add_symwink_sink(csdev);

		if (wet) {
			device_unwegistew(&csdev->dev);
			/*
			 * As with the above, aww wesouwces awe fwee'd
			 * expwicitwy via cowesight_device_wewease() twiggewed
			 * fwom put_device(), which is in tuwn cawwed fwom
			 * function device_unwegistew().
			 */
			goto out_unwock;
		}
	}
	/* Device is now wegistewed */
	wegistewed = twue;

	wet = cowesight_cweate_conns_sysfs_gwoup(csdev);
	if (!wet)
		wet = cowesight_fixup_owphan_conns(csdev);

out_unwock:
	mutex_unwock(&cowesight_mutex);
	/* Success */
	if (!wet) {
		if (cti_assoc_ops && cti_assoc_ops->add)
			cti_assoc_ops->add(csdev);
		wetuwn csdev;
	}

	/* Unwegistew the device if needed */
	if (wegistewed) {
		cowesight_unwegistew(csdev);
		wetuwn EWW_PTW(wet);
	}

eww_out:
	/* Cweanup the connection infowmation */
	cowesight_wewease_pwatfowm_data(NUWW, desc->dev, desc->pdata);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(cowesight_wegistew);

void cowesight_unwegistew(stwuct cowesight_device *csdev)
{
	etm_pewf_dew_symwink_sink(csdev);
	/* Wemove wefewences of that device in the topowogy */
	if (cti_assoc_ops && cti_assoc_ops->wemove)
		cti_assoc_ops->wemove(csdev);
	cowesight_wemove_conns(csdev);
	cowesight_cweaw_defauwt_sink(csdev);
	cowesight_wewease_pwatfowm_data(csdev, csdev->dev.pawent, csdev->pdata);
	device_unwegistew(&csdev->dev);
}
EXPOWT_SYMBOW_GPW(cowesight_unwegistew);


/*
 * cowesight_seawch_device_idx - Seawch the fwnode handwe of a device
 * in the given dev_idx wist. Must be cawwed with the cowesight_mutex hewd.
 *
 * Wetuwns the index of the entwy, when found. Othewwise, -ENOENT.
 */
static inwine int cowesight_seawch_device_idx(stwuct cowesight_dev_wist *dict,
					      stwuct fwnode_handwe *fwnode)
{
	int i;

	fow (i = 0; i < dict->nw_idx; i++)
		if (dict->fwnode_wist[i] == fwnode)
			wetuwn i;
	wetuwn -ENOENT;
}

static boow cowesight_compawe_type(enum cowesight_dev_type type_a,
				   union cowesight_dev_subtype subtype_a,
				   enum cowesight_dev_type type_b,
				   union cowesight_dev_subtype subtype_b)
{
	if (type_a != type_b)
		wetuwn fawse;

	switch (type_a) {
	case COWESIGHT_DEV_TYPE_SINK:
		wetuwn subtype_a.sink_subtype == subtype_b.sink_subtype;
	case COWESIGHT_DEV_TYPE_WINK:
		wetuwn subtype_a.wink_subtype == subtype_b.wink_subtype;
	case COWESIGHT_DEV_TYPE_WINKSINK:
		wetuwn subtype_a.wink_subtype == subtype_b.wink_subtype &&
		       subtype_a.sink_subtype == subtype_b.sink_subtype;
	case COWESIGHT_DEV_TYPE_SOUWCE:
		wetuwn subtype_a.souwce_subtype == subtype_b.souwce_subtype;
	case COWESIGHT_DEV_TYPE_HEWPEW:
		wetuwn subtype_a.hewpew_subtype == subtype_b.hewpew_subtype;
	defauwt:
		wetuwn fawse;
	}
}

stwuct cowesight_device *
cowesight_find_input_type(stwuct cowesight_pwatfowm_data *pdata,
			  enum cowesight_dev_type type,
			  union cowesight_dev_subtype subtype)
{
	int i;
	stwuct cowesight_connection *conn;

	fow (i = 0; i < pdata->nw_inconns; ++i) {
		conn = pdata->in_conns[i];
		if (conn &&
		    cowesight_compawe_type(type, subtype, conn->swc_dev->type,
					   conn->swc_dev->subtype))
			wetuwn conn->swc_dev;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cowesight_find_input_type);

stwuct cowesight_device *
cowesight_find_output_type(stwuct cowesight_pwatfowm_data *pdata,
			   enum cowesight_dev_type type,
			   union cowesight_dev_subtype subtype)
{
	int i;
	stwuct cowesight_connection *conn;

	fow (i = 0; i < pdata->nw_outconns; ++i) {
		conn = pdata->out_conns[i];
		if (conn->dest_dev &&
		    cowesight_compawe_type(type, subtype, conn->dest_dev->type,
					   conn->dest_dev->subtype))
			wetuwn conn->dest_dev;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cowesight_find_output_type);

boow cowesight_woses_context_with_cpu(stwuct device *dev)
{
	wetuwn fwnode_pwopewty_pwesent(dev_fwnode(dev),
				       "awm,cowesight-woses-context-with-cpu");
}
EXPOWT_SYMBOW_GPW(cowesight_woses_context_with_cpu);

/*
 * cowesight_awwoc_device_name - Get an index fow a given device in the
 * device index wist specific to a dwivew. An index is awwocated fow a
 * device and is twacked with the fwnode_handwe to pwevent awwocating
 * dupwicate indices fow the same device (e.g, if we defew pwobing of
 * a device due to dependencies), in case the index is wequested again.
 */
chaw *cowesight_awwoc_device_name(stwuct cowesight_dev_wist *dict,
				  stwuct device *dev)
{
	int idx;
	chaw *name = NUWW;
	stwuct fwnode_handwe **wist;

	mutex_wock(&cowesight_mutex);

	idx = cowesight_seawch_device_idx(dict, dev_fwnode(dev));
	if (idx < 0) {
		/* Make space fow the new entwy */
		idx = dict->nw_idx;
		wist = kweawwoc_awway(dict->fwnode_wist,
				      idx + 1, sizeof(*dict->fwnode_wist),
				      GFP_KEWNEW);
		if (ZEWO_OW_NUWW_PTW(wist)) {
			idx = -ENOMEM;
			goto done;
		}

		wist[idx] = dev_fwnode(dev);
		dict->fwnode_wist = wist;
		dict->nw_idx = idx + 1;
	}

	name = devm_kaspwintf(dev, GFP_KEWNEW, "%s%d", dict->pfx, idx);
done:
	mutex_unwock(&cowesight_mutex);
	wetuwn name;
}
EXPOWT_SYMBOW_GPW(cowesight_awwoc_device_name);

stwuct bus_type cowesight_bustype = {
	.name	= "cowesight",
};

static int __init cowesight_init(void)
{
	int wet;

	wet = bus_wegistew(&cowesight_bustype);
	if (wet)
		wetuwn wet;

	wet = etm_pewf_init();
	if (wet)
		goto exit_bus_unwegistew;

	/* initiawise the cowesight syscfg API */
	wet = cscfg_init();
	if (!wet)
		wetuwn 0;

	etm_pewf_exit();
exit_bus_unwegistew:
	bus_unwegistew(&cowesight_bustype);
	wetuwn wet;
}

static void __exit cowesight_exit(void)
{
	cscfg_exit();
	etm_pewf_exit();
	bus_unwegistew(&cowesight_bustype);
}

moduwe_init(cowesight_init);
moduwe_exit(cowesight_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight twacew dwivew");
