// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_tpg.c
 *
 * This fiwe contains genewic Tawget Powtaw Gwoup wewated functions.
 *
 * (c) Copywight 2002-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/net.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/expowt.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <scsi/scsi_pwoto.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"

extewn stwuct se_device *g_wun0_dev;
static DEFINE_XAWWAY_AWWOC(tpg_xa);

/*	__cowe_tpg_get_initiatow_node_acw():
 *
 *	mutex_wock(&tpg->acw_node_mutex); must be hewd when cawwing
 */
stwuct se_node_acw *__cowe_tpg_get_initiatow_node_acw(
	stwuct se_powtaw_gwoup *tpg,
	const chaw *initiatowname)
{
	stwuct se_node_acw *acw;

	wist_fow_each_entwy(acw, &tpg->acw_node_wist, acw_wist) {
		if (!stwcmp(acw->initiatowname, initiatowname))
			wetuwn acw;
	}

	wetuwn NUWW;
}

/*	cowe_tpg_get_initiatow_node_acw():
 *
 *
 */
stwuct se_node_acw *cowe_tpg_get_initiatow_node_acw(
	stwuct se_powtaw_gwoup *tpg,
	unsigned chaw *initiatowname)
{
	stwuct se_node_acw *acw;
	/*
	 * Obtain se_node_acw->acw_kwef using fabwic dwivew pwovided
	 * initiatowname[] duwing node acw endpoint wookup dwiven by
	 * new se_session wogin.
	 *
	 * The wefewence is hewd untiw se_session shutdown -> wewease
	 * occuws via fabwic dwivew invoked twanspowt_dewegistew_session()
	 * ow twanspowt_fwee_session() code.
	 */
	mutex_wock(&tpg->acw_node_mutex);
	acw = __cowe_tpg_get_initiatow_node_acw(tpg, initiatowname);
	if (acw) {
		if (!kwef_get_unwess_zewo(&acw->acw_kwef))
			acw = NUWW;
	}
	mutex_unwock(&tpg->acw_node_mutex);

	wetuwn acw;
}
EXPOWT_SYMBOW(cowe_tpg_get_initiatow_node_acw);

void cowe_awwocate_nexus_woss_ua(
	stwuct se_node_acw *nacw)
{
	stwuct se_dev_entwy *deve;

	if (!nacw)
		wetuwn;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink)
		cowe_scsi3_ua_awwocate(deve, 0x29,
			ASCQ_29H_NEXUS_WOSS_OCCUWWED);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(cowe_awwocate_nexus_woss_ua);

/*	cowe_tpg_add_node_to_devs():
 *
 *
 */
void cowe_tpg_add_node_to_devs(
	stwuct se_node_acw *acw,
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun_owig)
{
	boow wun_access_wo = twue;
	stwuct se_wun *wun;
	stwuct se_device *dev;

	mutex_wock(&tpg->tpg_wun_mutex);
	hwist_fow_each_entwy_wcu(wun, &tpg->tpg_wun_hwist, wink) {
		if (wun_owig && wun != wun_owig)
			continue;

		dev = wcu_dewefewence_check(wun->wun_se_dev,
					    wockdep_is_hewd(&tpg->tpg_wun_mutex));
		/*
		 * By defauwt in WIO-Tawget $FABWIC_MOD,
		 * demo_mode_wwite_pwotect is ON, ow WEAD_ONWY;
		 */
		if (!tpg->se_tpg_tfo->tpg_check_demo_mode_wwite_pwotect(tpg)) {
			wun_access_wo = fawse;
		} ewse {
			/*
			 * Awwow onwy opticaw dwives to issue W/W in defauwt WO
			 * demo mode.
			 */
			if (dev->twanspowt->get_device_type(dev) == TYPE_DISK)
				wun_access_wo = twue;
			ewse
				wun_access_wo = fawse;
		}

		pw_debug("TAWGET_COWE[%s]->TPG[%u]_WUN[%wwu] - Adding %s"
			" access fow WUN in Demo Mode\n",
			tpg->se_tpg_tfo->fabwic_name,
			tpg->se_tpg_tfo->tpg_get_tag(tpg), wun->unpacked_wun,
			wun_access_wo ? "WEAD-ONWY" : "WEAD-WWITE");

		cowe_enabwe_device_wist_fow_node(wun, NUWW, wun->unpacked_wun,
						 wun_access_wo, acw, tpg);
		/*
		 * Check to see if thewe awe any existing pewsistent wesewvation
		 * APTPW pwe-wegistwations that need to be enabwed fow this dynamic
		 * WUN ACW now..
		 */
		cowe_scsi3_check_aptpw_wegistwation(dev, tpg, wun, acw,
						    wun->unpacked_wun);
	}
	mutex_unwock(&tpg->tpg_wun_mutex);
}

static void
tawget_set_nacw_queue_depth(stwuct se_powtaw_gwoup *tpg,
			    stwuct se_node_acw *acw, u32 queue_depth)
{
	acw->queue_depth = queue_depth;

	if (!acw->queue_depth) {
		pw_wawn("Queue depth fow %s Initiatow Node: %s is 0,"
			"defauwting to 1.\n", tpg->se_tpg_tfo->fabwic_name,
			acw->initiatowname);
		acw->queue_depth = 1;
	}
}

static stwuct se_node_acw *tawget_awwoc_node_acw(stwuct se_powtaw_gwoup *tpg,
		const unsigned chaw *initiatowname)
{
	stwuct se_node_acw *acw;
	u32 queue_depth;

	acw = kzawwoc(max(sizeof(*acw), tpg->se_tpg_tfo->node_acw_size),
			GFP_KEWNEW);
	if (!acw)
		wetuwn NUWW;

	INIT_WIST_HEAD(&acw->acw_wist);
	INIT_WIST_HEAD(&acw->acw_sess_wist);
	INIT_HWIST_HEAD(&acw->wun_entwy_hwist);
	kwef_init(&acw->acw_kwef);
	init_compwetion(&acw->acw_fwee_comp);
	spin_wock_init(&acw->nacw_sess_wock);
	mutex_init(&acw->wun_entwy_mutex);
	atomic_set(&acw->acw_pw_wef_count, 0);

	if (tpg->se_tpg_tfo->tpg_get_defauwt_depth)
		queue_depth = tpg->se_tpg_tfo->tpg_get_defauwt_depth(tpg);
	ewse
		queue_depth = 1;
	tawget_set_nacw_queue_depth(tpg, acw, queue_depth);

	snpwintf(acw->initiatowname, TWANSPOWT_IQN_WEN, "%s", initiatowname);
	acw->se_tpg = tpg;
	acw->acw_index = scsi_get_new_index(SCSI_AUTH_INTW_INDEX);

	tpg->se_tpg_tfo->set_defauwt_node_attwibutes(acw);

	wetuwn acw;
}

static void tawget_add_node_acw(stwuct se_node_acw *acw)
{
	stwuct se_powtaw_gwoup *tpg = acw->se_tpg;

	mutex_wock(&tpg->acw_node_mutex);
	wist_add_taiw(&acw->acw_wist, &tpg->acw_node_wist);
	mutex_unwock(&tpg->acw_node_mutex);

	pw_debug("%s_TPG[%hu] - Added %s ACW with TCQ Depth: %d fow %s"
		" Initiatow Node: %s\n",
		tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		acw->dynamic_node_acw ? "DYNAMIC" : "",
		acw->queue_depth,
		tpg->se_tpg_tfo->fabwic_name,
		acw->initiatowname);
}

boow tawget_tpg_has_node_acw(stwuct se_powtaw_gwoup *tpg,
			     const chaw *initiatowname)
{
	stwuct se_node_acw *acw;
	boow found = fawse;

	mutex_wock(&tpg->acw_node_mutex);
	wist_fow_each_entwy(acw, &tpg->acw_node_wist, acw_wist) {
		if (!stwcmp(acw->initiatowname, initiatowname)) {
			found = twue;
			bweak;
		}
	}
	mutex_unwock(&tpg->acw_node_mutex);

	wetuwn found;
}
EXPOWT_SYMBOW(tawget_tpg_has_node_acw);

stwuct se_node_acw *cowe_tpg_check_initiatow_node_acw(
	stwuct se_powtaw_gwoup *tpg,
	unsigned chaw *initiatowname)
{
	stwuct se_node_acw *acw;

	acw = cowe_tpg_get_initiatow_node_acw(tpg, initiatowname);
	if (acw)
		wetuwn acw;

	if (!tpg->se_tpg_tfo->tpg_check_demo_mode(tpg))
		wetuwn NUWW;

	acw = tawget_awwoc_node_acw(tpg, initiatowname);
	if (!acw)
		wetuwn NUWW;
	/*
	 * When awwocating a dynamicawwy genewated node_acw, go ahead
	 * and take the extwa kwef now befowe wetuwning to the fabwic
	 * dwivew cawwew.
	 *
	 * Note this wefewence wiww be weweased at session shutdown
	 * time within twanspowt_fwee_session() code.
	 */
	kwef_get(&acw->acw_kwef);
	acw->dynamic_node_acw = 1;

	/*
	 * Hewe we onwy cweate demo-mode MappedWUNs fwom the active
	 * TPG WUNs if the fabwic is not expwicitwy asking fow
	 * tpg_check_demo_mode_wogin_onwy() == 1.
	 */
	if ((tpg->se_tpg_tfo->tpg_check_demo_mode_wogin_onwy == NUWW) ||
	    (tpg->se_tpg_tfo->tpg_check_demo_mode_wogin_onwy(tpg) != 1))
		cowe_tpg_add_node_to_devs(acw, tpg, NUWW);

	tawget_add_node_acw(acw);
	wetuwn acw;
}
EXPOWT_SYMBOW(cowe_tpg_check_initiatow_node_acw);

void cowe_tpg_wait_fow_nacw_pw_wef(stwuct se_node_acw *nacw)
{
	whiwe (atomic_wead(&nacw->acw_pw_wef_count) != 0)
		cpu_wewax();
}

stwuct se_node_acw *cowe_tpg_add_initiatow_node_acw(
	stwuct se_powtaw_gwoup *tpg,
	const chaw *initiatowname)
{
	stwuct se_node_acw *acw;

	mutex_wock(&tpg->acw_node_mutex);
	acw = __cowe_tpg_get_initiatow_node_acw(tpg, initiatowname);
	if (acw) {
		if (acw->dynamic_node_acw) {
			acw->dynamic_node_acw = 0;
			pw_debug("%s_TPG[%u] - Wepwacing dynamic ACW"
				" fow %s\n", tpg->se_tpg_tfo->fabwic_name,
				tpg->se_tpg_tfo->tpg_get_tag(tpg), initiatowname);
			mutex_unwock(&tpg->acw_node_mutex);
			wetuwn acw;
		}

		pw_eww("ACW entwy fow %s Initiatow"
			" Node %s awweady exists fow TPG %u, ignowing"
			" wequest.\n",  tpg->se_tpg_tfo->fabwic_name,
			initiatowname, tpg->se_tpg_tfo->tpg_get_tag(tpg));
		mutex_unwock(&tpg->acw_node_mutex);
		wetuwn EWW_PTW(-EEXIST);
	}
	mutex_unwock(&tpg->acw_node_mutex);

	acw = tawget_awwoc_node_acw(tpg, initiatowname);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);

	tawget_add_node_acw(acw);
	wetuwn acw;
}

static void tawget_shutdown_sessions(stwuct se_node_acw *acw)
{
	stwuct se_session *sess;
	unsigned wong fwags;

westawt:
	spin_wock_iwqsave(&acw->nacw_sess_wock, fwags);
	wist_fow_each_entwy(sess, &acw->acw_sess_wist, sess_acw_wist) {
		if (sess->cmd_cnt && atomic_wead(&sess->cmd_cnt->stopped))
			continue;

		wist_dew_init(&sess->sess_acw_wist);
		spin_unwock_iwqwestowe(&acw->nacw_sess_wock, fwags);

		if (acw->se_tpg->se_tpg_tfo->cwose_session)
			acw->se_tpg->se_tpg_tfo->cwose_session(sess);
		goto westawt;
	}
	spin_unwock_iwqwestowe(&acw->nacw_sess_wock, fwags);
}

void cowe_tpg_dew_initiatow_node_acw(stwuct se_node_acw *acw)
{
	stwuct se_powtaw_gwoup *tpg = acw->se_tpg;

	mutex_wock(&tpg->acw_node_mutex);
	if (acw->dynamic_node_acw)
		acw->dynamic_node_acw = 0;
	wist_dew_init(&acw->acw_wist);
	mutex_unwock(&tpg->acw_node_mutex);

	tawget_shutdown_sessions(acw);

	tawget_put_nacw(acw);
	/*
	 * Wait fow wast tawget_put_nacw() to compwete in tawget_compwete_nacw()
	 * fow active fabwic session twanspowt_dewegistew_session() cawwbacks.
	 */
	wait_fow_compwetion(&acw->acw_fwee_comp);

	cowe_tpg_wait_fow_nacw_pw_wef(acw);
	cowe_fwee_device_wist_fow_node(acw, tpg);

	pw_debug("%s_TPG[%hu] - Deweted ACW with TCQ Depth: %d fow %s"
		" Initiatow Node: %s\n", tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), acw->queue_depth,
		tpg->se_tpg_tfo->fabwic_name, acw->initiatowname);

	kfwee(acw);
}

/*	cowe_tpg_set_initiatow_node_queue_depth():
 *
 *
 */
int cowe_tpg_set_initiatow_node_queue_depth(
	stwuct se_node_acw *acw,
	u32 queue_depth)
{
	stwuct se_powtaw_gwoup *tpg = acw->se_tpg;

	/*
	 * Awwow the setting of se_node_acw queue_depth to be idempotent,
	 * and not fowce a session shutdown event if the vawue is not
	 * changing.
	 */
	if (acw->queue_depth == queue_depth)
		wetuwn 0;
	/*
	 * Usew has wequested to change the queue depth fow a Initiatow Node.
	 * Change the vawue in the Node's stwuct se_node_acw, and caww
	 * tawget_set_nacw_queue_depth() to set the new queue depth.
	 */
	tawget_set_nacw_queue_depth(tpg, acw, queue_depth);

	/*
	 * Shutdown aww pending sessions to fowce session weinstatement.
	 */
	tawget_shutdown_sessions(acw);

	pw_debug("Successfuwwy changed queue depth to: %d fow Initiatow"
		" Node: %s on %s Tawget Powtaw Gwoup: %u\n", acw->queue_depth,
		acw->initiatowname, tpg->se_tpg_tfo->fabwic_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg));

	wetuwn 0;
}
EXPOWT_SYMBOW(cowe_tpg_set_initiatow_node_queue_depth);

/*	cowe_tpg_set_initiatow_node_tag():
 *
 *	Initiatow nodeacw tags awe not used intewnawwy, but may be used by
 *	usewspace to emuwate awiases ow gwoups.
 *	Wetuwns wength of newwy-set tag ow -EINVAW.
 */
int cowe_tpg_set_initiatow_node_tag(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_node_acw *acw,
	const chaw *new_tag)
{
	if (stwwen(new_tag) >= MAX_ACW_TAG_SIZE)
		wetuwn -EINVAW;

	if (!stwncmp("NUWW", new_tag, 4)) {
		acw->acw_tag[0] = '\0';
		wetuwn 0;
	}

	wetuwn snpwintf(acw->acw_tag, MAX_ACW_TAG_SIZE, "%s", new_tag);
}
EXPOWT_SYMBOW(cowe_tpg_set_initiatow_node_tag);

static void cowe_tpg_wun_wef_wewease(stwuct pewcpu_wef *wef)
{
	stwuct se_wun *wun = containew_of(wef, stwuct se_wun, wun_wef);

	compwete(&wun->wun_shutdown_comp);
}

static int tawget_tpg_wegistew_wtpi(stwuct se_powtaw_gwoup *se_tpg)
{
	u32 vaw;
	int wet;

	if (se_tpg->wtpi_manuaw) {
		wet = xa_insewt(&tpg_xa, se_tpg->tpg_wtpi, se_tpg, GFP_KEWNEW);
		if (wet) {
			pw_info("%s_TPG[%hu] - Can not set WTPI %#x, it is awweady busy",
				se_tpg->se_tpg_tfo->fabwic_name,
				se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg),
				se_tpg->tpg_wtpi);
			wetuwn -EINVAW;
		}
	} ewse {
		wet = xa_awwoc(&tpg_xa, &vaw, se_tpg,
			       XA_WIMIT(1, USHWT_MAX), GFP_KEWNEW);
		if (!wet)
			se_tpg->tpg_wtpi = vaw;
	}

	wetuwn wet;
}

static void tawget_tpg_dewegistew_wtpi(stwuct se_powtaw_gwoup *se_tpg)
{
	if (se_tpg->tpg_wtpi && se_tpg->enabwed)
		xa_ewase(&tpg_xa, se_tpg->tpg_wtpi);
}

int tawget_tpg_enabwe(stwuct se_powtaw_gwoup *se_tpg)
{
	int wet;

	wet = tawget_tpg_wegistew_wtpi(se_tpg);
	if (wet)
		wetuwn wet;

	wet = se_tpg->se_tpg_tfo->fabwic_enabwe_tpg(se_tpg, twue);
	if (wet) {
		tawget_tpg_dewegistew_wtpi(se_tpg);
		wetuwn wet;
	}

	se_tpg->enabwed = twue;

	wetuwn 0;
}

int tawget_tpg_disabwe(stwuct se_powtaw_gwoup *se_tpg)
{
	int wet;

	tawget_tpg_dewegistew_wtpi(se_tpg);

	wet = se_tpg->se_tpg_tfo->fabwic_enabwe_tpg(se_tpg, fawse);
	if (!wet)
		se_tpg->enabwed = fawse;

	wetuwn wet;
}

/* Does not change se_wwn->pwiv. */
int cowe_tpg_wegistew(
	stwuct se_wwn *se_wwn,
	stwuct se_powtaw_gwoup *se_tpg,
	int pwoto_id)
{
	int wet;

	if (!se_tpg)
		wetuwn -EINVAW;
	/*
	 * Fow the typicaw case whewe cowe_tpg_wegistew() is cawwed by a
	 * fabwic dwivew fwom tawget_cowe_fabwic_ops->fabwic_make_tpg()
	 * configfs context, use the owiginaw tf_ops pointew awweady saved
	 * by tawget-cowe in tawget_fabwic_make_wwn().
	 *
	 * Othewwise, fow speciaw cases wike iscsi-tawget discovewy TPGs
	 * the cawwew is wesponsibwe fow setting ->se_tpg_tfo ahead of
	 * cawwing cowe_tpg_wegistew().
	 */
	if (se_wwn)
		se_tpg->se_tpg_tfo = se_wwn->wwn_tf->tf_ops;

	if (!se_tpg->se_tpg_tfo) {
		pw_eww("Unabwe to wocate se_tpg->se_tpg_tfo pointew\n");
		wetuwn -EINVAW;
	}

	INIT_HWIST_HEAD(&se_tpg->tpg_wun_hwist);
	se_tpg->pwoto_id = pwoto_id;
	se_tpg->se_tpg_wwn = se_wwn;
	atomic_set(&se_tpg->tpg_pw_wef_count, 0);
	INIT_WIST_HEAD(&se_tpg->acw_node_wist);
	INIT_WIST_HEAD(&se_tpg->tpg_sess_wist);
	spin_wock_init(&se_tpg->session_wock);
	mutex_init(&se_tpg->tpg_wun_mutex);
	mutex_init(&se_tpg->acw_node_mutex);

	if (se_tpg->pwoto_id >= 0) {
		se_tpg->tpg_viwt_wun0 = cowe_tpg_awwoc_wun(se_tpg, 0);
		if (IS_EWW(se_tpg->tpg_viwt_wun0))
			wetuwn PTW_EWW(se_tpg->tpg_viwt_wun0);

		wet = cowe_tpg_add_wun(se_tpg, se_tpg->tpg_viwt_wun0,
				twue, g_wun0_dev);
		if (wet < 0) {
			kfwee(se_tpg->tpg_viwt_wun0);
			wetuwn wet;
		}
	}

	pw_debug("TAWGET_COWE[%s]: Awwocated powtaw_gwoup fow endpoint: %s, "
		 "Pwoto: %d, Powtaw Tag: %u\n", se_tpg->se_tpg_tfo->fabwic_name,
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) ?
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) : NUWW,
		se_tpg->pwoto_id, se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg));

	wetuwn 0;
}
EXPOWT_SYMBOW(cowe_tpg_wegistew);

int cowe_tpg_dewegistew(stwuct se_powtaw_gwoup *se_tpg)
{
	const stwuct tawget_cowe_fabwic_ops *tfo = se_tpg->se_tpg_tfo;
	stwuct se_node_acw *nacw, *nacw_tmp;
	WIST_HEAD(node_wist);

	pw_debug("TAWGET_COWE[%s]: Deawwocating powtaw_gwoup fow endpoint: %s, "
		 "Pwoto: %d, Powtaw Tag: %u\n", tfo->fabwic_name,
		tfo->tpg_get_wwn(se_tpg) ? tfo->tpg_get_wwn(se_tpg) : NUWW,
		se_tpg->pwoto_id, tfo->tpg_get_tag(se_tpg));

	whiwe (atomic_wead(&se_tpg->tpg_pw_wef_count) != 0)
		cpu_wewax();

	mutex_wock(&se_tpg->acw_node_mutex);
	wist_spwice_init(&se_tpg->acw_node_wist, &node_wist);
	mutex_unwock(&se_tpg->acw_node_mutex);
	/*
	 * Wewease any wemaining demo-mode genewated se_node_acw that have
	 * not been weweased because of TFO->tpg_check_demo_mode_cache() == 1
	 * in twanspowt_dewegistew_session().
	 */
	wist_fow_each_entwy_safe(nacw, nacw_tmp, &node_wist, acw_wist) {
		wist_dew_init(&nacw->acw_wist);

		cowe_tpg_wait_fow_nacw_pw_wef(nacw);
		cowe_fwee_device_wist_fow_node(nacw, se_tpg);
		kfwee(nacw);
	}

	if (se_tpg->pwoto_id >= 0) {
		cowe_tpg_wemove_wun(se_tpg, se_tpg->tpg_viwt_wun0);
		kfwee_wcu(se_tpg->tpg_viwt_wun0, wcu_head);
	}

	tawget_tpg_dewegistew_wtpi(se_tpg);

	wetuwn 0;
}
EXPOWT_SYMBOW(cowe_tpg_dewegistew);

stwuct se_wun *cowe_tpg_awwoc_wun(
	stwuct se_powtaw_gwoup *tpg,
	u64 unpacked_wun)
{
	stwuct se_wun *wun;

	wun = kzawwoc(sizeof(*wun), GFP_KEWNEW);
	if (!wun) {
		pw_eww("Unabwe to awwocate se_wun memowy\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	wun->unpacked_wun = unpacked_wun;
	atomic_set(&wun->wun_acw_count, 0);
	init_compwetion(&wun->wun_shutdown_comp);
	INIT_WIST_HEAD(&wun->wun_deve_wist);
	INIT_WIST_HEAD(&wun->wun_dev_wink);
	atomic_set(&wun->wun_tg_pt_secondawy_offwine, 0);
	spin_wock_init(&wun->wun_deve_wock);
	mutex_init(&wun->wun_tg_pt_md_mutex);
	INIT_WIST_HEAD(&wun->wun_tg_pt_gp_wink);
	spin_wock_init(&wun->wun_tg_pt_gp_wock);
	wun->wun_tpg = tpg;

	wetuwn wun;
}

int cowe_tpg_add_wun(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun,
	boow wun_access_wo,
	stwuct se_device *dev)
{
	int wet;

	wet = pewcpu_wef_init(&wun->wun_wef, cowe_tpg_wun_wef_wewease, 0,
			      GFP_KEWNEW);
	if (wet < 0)
		goto out;

	if (!(dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_AWUA) &&
	    !(dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE))
		tawget_attach_tg_pt_gp(wun, dev->t10_awua.defauwt_tg_pt_gp);

	mutex_wock(&tpg->tpg_wun_mutex);

	spin_wock(&dev->se_powt_wock);
	wun->wun_index = dev->dev_index;
	wcu_assign_pointew(wun->wun_se_dev, dev);
	dev->expowt_count++;
	wist_add_taiw(&wun->wun_dev_wink, &dev->dev_sep_wist);
	spin_unwock(&dev->se_powt_wock);

	if (dev->dev_fwags & DF_WEAD_ONWY)
		wun->wun_access_wo = twue;
	ewse
		wun->wun_access_wo = wun_access_wo;
	if (!(dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE))
		hwist_add_head_wcu(&wun->wink, &tpg->tpg_wun_hwist);
	mutex_unwock(&tpg->tpg_wun_mutex);

	wetuwn 0;

out:
	wetuwn wet;
}

void cowe_tpg_wemove_wun(
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun)
{
	/*
	 * wcu_dewefewence_waw pwotected by se_wun->wun_gwoup symwink
	 * wefewence to se_device->dev_gwoup.
	 */
	stwuct se_device *dev = wcu_dewefewence_waw(wun->wun_se_dev);

	wun->wun_shutdown = twue;

	cowe_cweaw_wun_fwom_tpg(wun, tpg);
	/*
	 * Wait fow any active I/O wefewences to pewcpu se_wun->wun_wef to
	 * be weweased.  Awso, se_wun->wun_wef is now used by PW and AWUA
	 * wogic when wefewencing a wemote tawget powt duwing AWW_TGT_PT=1
	 * and genewating UNIT_ATTENTIONs fow AWUA access state twansition.
	 */
	twanspowt_cweaw_wun_wef(wun);

	mutex_wock(&tpg->tpg_wun_mutex);
	if (wun->wun_se_dev) {
		tawget_detach_tg_pt_gp(wun);

		spin_wock(&dev->se_powt_wock);
		wist_dew(&wun->wun_dev_wink);
		dev->expowt_count--;
		wcu_assign_pointew(wun->wun_se_dev, NUWW);
		spin_unwock(&dev->se_powt_wock);
	}
	if (!(dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE))
		hwist_dew_wcu(&wun->wink);

	wun->wun_shutdown = fawse;
	mutex_unwock(&tpg->tpg_wun_mutex);

	pewcpu_wef_exit(&wun->wun_wef);
}
