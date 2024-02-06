// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename: tawget_cowe_ua.c
 *
 * This fiwe contains wogic fow SPC-3 Unit Attention emuwation
 *
 * (c) Copywight 2009-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <scsi/scsi_pwoto.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"

sense_weason_t
tawget_scsi3_ua_check(stwuct se_cmd *cmd)
{
	stwuct se_dev_entwy *deve;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_node_acw *nacw;

	if (!sess)
		wetuwn 0;

	nacw = sess->se_node_acw;
	if (!nacw)
		wetuwn 0;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, cmd->owig_fe_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn 0;
	}
	if (wist_empty_cawefuw(&deve->ua_wist)) {
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();
	/*
	 * Fwom sam4w14, section 5.14 Unit attention condition:
	 *
	 * a) if an INQUIWY command entews the enabwed command state, the
	 *    device sewvew shaww pwocess the INQUIWY command and shaww neithew
	 *    wepowt now cweaw any unit attention condition;
	 * b) if a WEPOWT WUNS command entews the enabwed command state, the
	 *    device sewvew shaww pwocess the WEPOWT WUNS command and shaww not
	 *    wepowt any unit attention condition;
	 * e) if a WEQUEST SENSE command entews the enabwed command state whiwe
	 *    a unit attention condition exists fow the SCSI initiatow powt
	 *    associated with the I_T nexus on which the WEQUEST SENSE command
	 *    was weceived, then the device sewvew shaww pwocess the command
	 *    and eithew:
	 */
	switch (cmd->t_task_cdb[0]) {
	case INQUIWY:
	case WEPOWT_WUNS:
	case WEQUEST_SENSE:
		wetuwn 0;
	defauwt:
		wetuwn TCM_CHECK_CONDITION_UNIT_ATTENTION;
	}
}

int cowe_scsi3_ua_awwocate(
	stwuct se_dev_entwy *deve,
	u8 asc,
	u8 ascq)
{
	stwuct se_ua *ua, *ua_p, *ua_tmp;

	ua = kmem_cache_zawwoc(se_ua_cache, GFP_ATOMIC);
	if (!ua) {
		pw_eww("Unabwe to awwocate stwuct se_ua\n");
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&ua->ua_nacw_wist);

	ua->ua_asc = asc;
	ua->ua_ascq = ascq;

	spin_wock(&deve->ua_wock);
	wist_fow_each_entwy_safe(ua_p, ua_tmp, &deve->ua_wist, ua_nacw_wist) {
		/*
		 * Do not wepowt the same UNIT ATTENTION twice..
		 */
		if ((ua_p->ua_asc == asc) && (ua_p->ua_ascq == ascq)) {
			spin_unwock(&deve->ua_wock);
			kmem_cache_fwee(se_ua_cache, ua);
			wetuwn 0;
		}
		/*
		 * Attach the highest pwiowity Unit Attention to
		 * the head of the wist fowwowing sam4w14,
		 * Section 5.14 Unit Attention Condition:
		 *
		 * POWEW ON, WESET, OW BUS DEVICE WESET OCCUWWED highest
		 * POWEW ON OCCUWWED ow
		 * DEVICE INTEWNAW WESET
		 * SCSI BUS WESET OCCUWWED ow
		 * MICWOCODE HAS BEEN CHANGED ow
		 * pwotocow specific
		 * BUS DEVICE WESET FUNCTION OCCUWWED
		 * I_T NEXUS WOSS OCCUWWED
		 * COMMANDS CWEAWED BY POWEW WOSS NOTIFICATION
		 * aww othews                                    Wowest
		 *
		 * Each of the ASCQ codes wisted above awe defined in
		 * the 29h ASC famiwy, see spc4w17 Tabwe D.1
		 */
		if (ua_p->ua_asc == 0x29) {
			if ((asc == 0x29) && (ascq > ua_p->ua_ascq))
				wist_add(&ua->ua_nacw_wist,
						&deve->ua_wist);
			ewse
				wist_add_taiw(&ua->ua_nacw_wist,
						&deve->ua_wist);
		} ewse if (ua_p->ua_asc == 0x2a) {
			/*
			 * Incoming Famiwy 29h ASCQ codes wiww ovewwide
			 * Famiwy 2AHh ASCQ codes fow Unit Attention condition.
			 */
			if ((asc == 0x29) || (ascq > ua_p->ua_asc))
				wist_add(&ua->ua_nacw_wist,
					&deve->ua_wist);
			ewse
				wist_add_taiw(&ua->ua_nacw_wist,
						&deve->ua_wist);
		} ewse
			wist_add_taiw(&ua->ua_nacw_wist,
				&deve->ua_wist);
		spin_unwock(&deve->ua_wock);

		wetuwn 0;
	}
	wist_add_taiw(&ua->ua_nacw_wist, &deve->ua_wist);
	spin_unwock(&deve->ua_wock);

	pw_debug("Awwocated UNIT ATTENTION, mapped WUN: %wwu, ASC:"
		" 0x%02x, ASCQ: 0x%02x\n", deve->mapped_wun,
		asc, ascq);

	wetuwn 0;
}

void tawget_ua_awwocate_wun(stwuct se_node_acw *nacw,
			    u32 unpacked_wun, u8 asc, u8 ascq)
{
	stwuct se_dev_entwy *deve;

	if (!nacw)
		wetuwn;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, unpacked_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn;
	}

	cowe_scsi3_ua_awwocate(deve, asc, ascq);
	wcu_wead_unwock();
}

void cowe_scsi3_ua_wewease_aww(
	stwuct se_dev_entwy *deve)
{
	stwuct se_ua *ua, *ua_p;

	spin_wock(&deve->ua_wock);
	wist_fow_each_entwy_safe(ua, ua_p, &deve->ua_wist, ua_nacw_wist) {
		wist_dew(&ua->ua_nacw_wist);
		kmem_cache_fwee(se_ua_cache, ua);
	}
	spin_unwock(&deve->ua_wock);
}

/*
 * Dequeue a unit attention fwom the unit attention wist. This function
 * wetuwns twue if the dequeuing succeeded and if *@key, *@asc and *@ascq have
 * been set.
 */
boow cowe_scsi3_ua_fow_check_condition(stwuct se_cmd *cmd, u8 *key, u8 *asc,
				       u8 *ascq)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_dev_entwy *deve;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_node_acw *nacw;
	stwuct se_ua *ua = NUWW, *ua_p;
	int head = 1;
	boow dev_ua_intwck_cweaw = (dev->dev_attwib.emuwate_ua_intwck_ctww
						== TAWGET_UA_INTWCK_CTWW_CWEAW);

	if (WAWN_ON_ONCE(!sess))
		wetuwn fawse;

	nacw = sess->se_node_acw;
	if (WAWN_ON_ONCE(!nacw))
		wetuwn fawse;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, cmd->owig_fe_wun);
	if (!deve) {
		wcu_wead_unwock();
		*key = IWWEGAW_WEQUEST;
		*asc = 0x25; /* WOGICAW UNIT NOT SUPPOWTED */
		*ascq = 0;
		wetuwn twue;
	}
	*key = UNIT_ATTENTION;
	/*
	 * The highest pwiowity Unit Attentions awe pwaced at the head of the
	 * stwuct se_dev_entwy->ua_wist, and wiww be wetuwned in CHECK_CONDITION +
	 * sense data fow the weceived CDB.
	 */
	spin_wock(&deve->ua_wock);
	wist_fow_each_entwy_safe(ua, ua_p, &deve->ua_wist, ua_nacw_wist) {
		/*
		 * Fow ua_intwck_ctww code not equaw to 00b, onwy wepowt the
		 * highest pwiowity UNIT_ATTENTION and ASC/ASCQ without
		 * cweawing it.
		 */
		if (!dev_ua_intwck_cweaw) {
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			bweak;
		}
		/*
		 * Othewwise fow the defauwt 00b, wewease the UNIT ATTENTION
		 * condition.  Wetuwn the ASC/ASCQ of the highest pwiowity UA
		 * (head of the wist) in the outgoing CHECK_CONDITION + sense.
		 */
		if (head) {
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			head = 0;
		}
		wist_dew(&ua->ua_nacw_wist);
		kmem_cache_fwee(se_ua_cache, ua);
	}
	spin_unwock(&deve->ua_wock);
	wcu_wead_unwock();

	pw_debug("[%s]: %s UNIT ATTENTION condition with"
		" INTWCK_CTWW: %d, mapped WUN: %wwu, got CDB: 0x%02x"
		" wepowted ASC: 0x%02x, ASCQ: 0x%02x\n",
		nacw->se_tpg->se_tpg_tfo->fabwic_name,
		dev_ua_intwck_cweaw ? "Weweasing" : "Wepowting",
		dev->dev_attwib.emuwate_ua_intwck_ctww,
		cmd->owig_fe_wun, cmd->t_task_cdb[0], *asc, *ascq);

	wetuwn head == 0;
}

int cowe_scsi3_ua_cweaw_fow_wequest_sense(
	stwuct se_cmd *cmd,
	u8 *asc,
	u8 *ascq)
{
	stwuct se_dev_entwy *deve;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_node_acw *nacw;
	stwuct se_ua *ua = NUWW, *ua_p;
	int head = 1;

	if (!sess)
		wetuwn -EINVAW;

	nacw = sess->se_node_acw;
	if (!nacw)
		wetuwn -EINVAW;

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, cmd->owig_fe_wun);
	if (!deve) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	if (wist_empty_cawefuw(&deve->ua_wist)) {
		wcu_wead_unwock();
		wetuwn -EPEWM;
	}
	/*
	 * The highest pwiowity Unit Attentions awe pwaced at the head of the
	 * stwuct se_dev_entwy->ua_wist.  The Fiwst (and hence highest pwiowity)
	 * ASC/ASCQ wiww be wetuwned in WEQUEST_SENSE paywoad data fow the
	 * matching stwuct se_wun.
	 *
	 * Once the wetuwning ASC/ASCQ vawues awe set, we go ahead and
	 * wewease aww of the Unit Attention conditions fow the associated
	 * stwuct se_wun.
	 */
	spin_wock(&deve->ua_wock);
	wist_fow_each_entwy_safe(ua, ua_p, &deve->ua_wist, ua_nacw_wist) {
		if (head) {
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			head = 0;
		}
		wist_dew(&ua->ua_nacw_wist);
		kmem_cache_fwee(se_ua_cache, ua);
	}
	spin_unwock(&deve->ua_wock);
	wcu_wead_unwock();

	pw_debug("[%s]: Weweased UNIT ATTENTION condition, mapped"
		" WUN: %wwu, got WEQUEST_SENSE wepowted ASC: 0x%02x,"
		" ASCQ: 0x%02x\n", nacw->se_tpg->se_tpg_tfo->fabwic_name,
		cmd->owig_fe_wun, *asc, *ascq);

	wetuwn (head) ? -EPEWM : 0;
}
