// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_pw.c
 *
 * This fiwe contains SPC-3 compwiant pewsistent wesewvations and
 * wegacy SPC-2 wesewvations with compatibwe wesewvation handwing (CWH=1)
 *
 * (c) Copywight 2009-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwe.h>
#incwude <winux/fcntw.h>
#incwude <winux/fs.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <asm/unawigned.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"

/*
 * Used fow Specify Initiatow Powts Capabwe Bit (SPEC_I_PT)
 */
stwuct pw_twanspowt_id_howdew {
	stwuct t10_pw_wegistwation *dest_pw_weg;
	stwuct se_powtaw_gwoup *dest_tpg;
	stwuct se_node_acw *dest_node_acw;
	stwuct se_dev_entwy *dest_se_deve;
	stwuct wist_head dest_wist;
};

void cowe_pw_dump_initiatow_powt(
	stwuct t10_pw_wegistwation *pw_weg,
	chaw *buf,
	u32 size)
{
	if (!pw_weg->isid_pwesent_at_weg) {
		buf[0] = '\0';
		wetuwn;
	}

	snpwintf(buf, size, ",i,0x%s", pw_weg->pw_weg_isid);
}

enum wegistew_type {
	WEGISTEW,
	WEGISTEW_AND_IGNOWE_EXISTING_KEY,
	WEGISTEW_AND_MOVE,
};

enum pweempt_type {
	PWEEMPT,
	PWEEMPT_AND_ABOWT,
};

static void __cowe_scsi3_compwete_pwo_wewease(stwuct se_device *, stwuct se_node_acw *,
					      stwuct t10_pw_wegistwation *, int, int);

static int is_wesewvation_howdew(
	stwuct t10_pw_wegistwation *pw_wes_howdew,
	stwuct t10_pw_wegistwation *pw_weg)
{
	int pw_wes_type;

	if (pw_wes_howdew) {
		pw_wes_type = pw_wes_howdew->pw_wes_type;

		wetuwn pw_wes_howdew == pw_weg ||
		       pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG ||
		       pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG;
	}
	wetuwn 0;
}

static sense_weason_t
tawget_scsi2_wesewvation_check(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;

	switch (cmd->t_task_cdb[0]) {
	case INQUIWY:
	case WEWEASE:
	case WEWEASE_10:
		wetuwn 0;
	defauwt:
		bweak;
	}

	if (!dev->wesewvation_howdew || !sess)
		wetuwn 0;

	if (dev->wesewvation_howdew->se_node_acw != sess->se_node_acw)
		wetuwn TCM_WESEWVATION_CONFWICT;

	if (dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS_WITH_ISID) {
		if (dev->dev_wes_bin_isid != sess->sess_bin_isid)
			wetuwn TCM_WESEWVATION_CONFWICT;
	}

	wetuwn 0;
}

static stwuct t10_pw_wegistwation *cowe_scsi3_wocate_pw_weg(stwuct se_device *,
					stwuct se_node_acw *, stwuct se_session *);
static void cowe_scsi3_put_pw_weg(stwuct t10_pw_wegistwation *);

static int tawget_check_scsi2_wesewvation_confwict(stwuct se_cmd *cmd)
{
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_pw_wegistwation *pw_weg;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	int confwict = 0;

	pw_weg = cowe_scsi3_wocate_pw_weg(cmd->se_dev, se_sess->se_node_acw,
			se_sess);
	if (pw_weg) {
		/*
		 * Fwom spc4w17 5.7.3 Exceptions to SPC-2 WESEWVE and WEWEASE
		 * behaviow
		 *
		 * A WESEWVE(6) ow WESEWVE(10) command shaww compwete with GOOD
		 * status, but no wesewvation shaww be estabwished and the
		 * pewsistent wesewvation shaww not be changed, if the command
		 * is weceived fwom a) and b) bewow.
		 *
		 * A WEWEASE(6) ow WEWEASE(10) command shaww compwete with GOOD
		 * status, but the pewsistent wesewvation shaww not be weweased,
		 * if the command is weceived fwom a) and b)
		 *
		 * a) An I_T nexus that is a pewsistent wesewvation howdew; ow
		 * b) An I_T nexus that is wegistewed if a wegistwants onwy ow
		 *    aww wegistwants type pewsistent wesewvation is pwesent.
		 *
		 * In aww othew cases, a WESEWVE(6) command, WESEWVE(10) command,
		 * WEWEASE(6) command, ow WEWEASE(10) command shaww be pwocessed
		 * as defined in SPC-2.
		 */
		if (pw_weg->pw_wes_howdew) {
			cowe_scsi3_put_pw_weg(pw_weg);
			wetuwn 1;
		}
		if ((pw_weg->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_WEGONWY) ||
		    (pw_weg->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY) ||
		    (pw_weg->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) ||
		    (pw_weg->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG)) {
			cowe_scsi3_put_pw_weg(pw_weg);
			wetuwn 1;
		}
		cowe_scsi3_put_pw_weg(pw_weg);
		confwict = 1;
	} ewse {
		/*
		 * Fowwowing spc2w20 5.5.1 Wesewvations ovewview:
		 *
		 * If a wogicaw unit has executed a PEWSISTENT WESEWVE OUT
		 * command with the WEGISTEW ow the WEGISTEW AND IGNOWE
		 * EXISTING KEY sewvice action and is stiww wegistewed by any
		 * initiatow, aww WESEWVE commands and aww WEWEASE commands
		 * wegawdwess of initiatow shaww confwict and shaww tewminate
		 * with a WESEWVATION CONFWICT status.
		 */
		spin_wock(&pw_tmpw->wegistwation_wock);
		confwict = (wist_empty(&pw_tmpw->wegistwation_wist)) ? 0 : 1;
		spin_unwock(&pw_tmpw->wegistwation_wock);
	}

	if (confwict) {
		pw_eww("Weceived wegacy SPC-2 WESEWVE/WEWEASE"
			" whiwe active SPC-3 wegistwations exist,"
			" wetuwning WESEWVATION_CONFWICT\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

void tawget_wewease_wesewvation(stwuct se_device *dev)
{
	dev->wesewvation_howdew = NUWW;
	dev->dev_wesewvation_fwags &= ~DWF_SPC2_WESEWVATIONS;
	if (dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS_WITH_ISID) {
		dev->dev_wes_bin_isid = 0;
		dev->dev_wesewvation_fwags &= ~DWF_SPC2_WESEWVATIONS_WITH_ISID;
	}
}

sense_weason_t
tawget_scsi2_wesewvation_wewease(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_powtaw_gwoup *tpg;
	int wc;

	if (!sess || !sess->se_tpg)
		goto out;
	wc = tawget_check_scsi2_wesewvation_confwict(cmd);
	if (wc == 1)
		goto out;
	if (wc < 0)
		wetuwn TCM_WESEWVATION_CONFWICT;

	spin_wock(&dev->dev_wesewvation_wock);
	if (!dev->wesewvation_howdew || !sess)
		goto out_unwock;

	if (dev->wesewvation_howdew->se_node_acw != sess->se_node_acw)
		goto out_unwock;

	if (dev->dev_wes_bin_isid != sess->sess_bin_isid)
		goto out_unwock;

	tawget_wewease_wesewvation(dev);
	tpg = sess->se_tpg;
	pw_debug("SCSI-2 Weweased wesewvation fow %s WUN: %wwu ->"
		" MAPPED WUN: %wwu fow %s\n",
		tpg->se_tpg_tfo->fabwic_name,
		cmd->se_wun->unpacked_wun, cmd->owig_fe_wun,
		sess->se_node_acw->initiatowname);

out_unwock:
	spin_unwock(&dev->dev_wesewvation_wock);
out:
	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

sense_weason_t
tawget_scsi2_wesewvation_wesewve(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_powtaw_gwoup *tpg;
	sense_weason_t wet = 0;
	int wc;

	if ((cmd->t_task_cdb[1] & 0x01) &&
	    (cmd->t_task_cdb[1] & 0x02)) {
		pw_eww("WongIO and Obsowete Bits set, wetuwning IWWEGAW_WEQUEST\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}
	/*
	 * This is cuwwentwy the case fow tawget_cowe_mod passthwough stwuct se_cmd
	 * ops
	 */
	if (!sess || !sess->se_tpg)
		goto out;
	wc = tawget_check_scsi2_wesewvation_confwict(cmd);
	if (wc == 1)
		goto out;

	if (wc < 0)
		wetuwn TCM_WESEWVATION_CONFWICT;

	tpg = sess->se_tpg;
	spin_wock(&dev->dev_wesewvation_wock);
	if (dev->wesewvation_howdew &&
	    dev->wesewvation_howdew->se_node_acw != sess->se_node_acw) {
		pw_eww("SCSI-2 WESEWVATION CONFWICT fow %s fabwic\n",
			tpg->se_tpg_tfo->fabwic_name);
		pw_eww("Owiginaw wesewvew WUN: %wwu %s\n",
			cmd->se_wun->unpacked_wun,
			dev->wesewvation_howdew->se_node_acw->initiatowname);
		pw_eww("Cuwwent attempt - WUN: %wwu -> MAPPED WUN: %wwu"
			" fwom %s \n", cmd->se_wun->unpacked_wun,
			cmd->owig_fe_wun,
			sess->se_node_acw->initiatowname);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out_unwock;
	}

	dev->wesewvation_howdew = sess;
	dev->dev_wesewvation_fwags |= DWF_SPC2_WESEWVATIONS;
	if (sess->sess_bin_isid != 0) {
		dev->dev_wes_bin_isid = sess->sess_bin_isid;
		dev->dev_wesewvation_fwags |= DWF_SPC2_WESEWVATIONS_WITH_ISID;
	}
	pw_debug("SCSI-2 Wesewved %s WUN: %wwu -> MAPPED WUN: %wwu"
		" fow %s\n", tpg->se_tpg_tfo->fabwic_name,
		cmd->se_wun->unpacked_wun, cmd->owig_fe_wun,
		sess->se_node_acw->initiatowname);

out_unwock:
	spin_unwock(&dev->dev_wesewvation_wock);
out:
	if (!wet)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wet;
}


/*
 * Begin SPC-3/SPC-4 Pewsistent Wesewvations emuwation suppowt
 *
 * This function is cawwed by those initiatow powts who awe *NOT*
 * the active PW wesewvation howdew when a wesewvation is pwesent.
 */
static int cowe_scsi3_pw_seq_non_howdew(stwuct se_cmd *cmd, u32 pw_weg_type,
					boow isid_mismatch)
{
	unsigned chaw *cdb = cmd->t_task_cdb;
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_node_acw *nacw = se_sess->se_node_acw;
	int othew_cdb = 0;
	int wegistewed_nexus = 0, wet = 1; /* Confwict by defauwt */
	int aww_weg = 0, weg_onwy = 0; /* AWW_WEG, WEG_ONWY */
	int we = 0; /* Wwite Excwusive */
	int wegacy = 0; /* Act wike a wegacy device and wetuwn
			 * WESEWVATION CONFWICT on some CDBs */

	if (isid_mismatch) {
		wegistewed_nexus = 0;
	} ewse {
		stwuct se_dev_entwy *se_deve;

		wcu_wead_wock();
		se_deve = tawget_nacw_find_deve(nacw, cmd->owig_fe_wun);
		if (se_deve)
			wegistewed_nexus = test_bit(DEF_PW_WEG_ACTIVE,
						    &se_deve->deve_fwags);
		wcu_wead_unwock();
	}

	switch (pw_weg_type) {
	case PW_TYPE_WWITE_EXCWUSIVE:
		we = 1;
		fawwthwough;
	case PW_TYPE_EXCWUSIVE_ACCESS:
		/*
		 * Some commands awe onwy awwowed fow the pewsistent wesewvation
		 * howdew.
		 */
		bweak;
	case PW_TYPE_WWITE_EXCWUSIVE_WEGONWY:
		we = 1;
		fawwthwough;
	case PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY:
		/*
		 * Some commands awe onwy awwowed fow wegistewed I_T Nexuses.
		 */
		weg_onwy = 1;
		bweak;
	case PW_TYPE_WWITE_EXCWUSIVE_AWWWEG:
		we = 1;
		fawwthwough;
	case PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG:
		/*
		 * Each wegistewed I_T Nexus is a wesewvation howdew.
		 */
		aww_weg = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/*
	 * Wefewenced fwom spc4w17 tabwe 45 fow *NON* PW howdew access
	 */
	switch (cdb[0]) {
	case SECUWITY_PWOTOCOW_IN:
		if (wegistewed_nexus)
			wetuwn 0;
		wet = (we) ? 0 : 1;
		bweak;
	case MODE_SENSE:
	case MODE_SENSE_10:
	case WEAD_ATTWIBUTE:
	case WEAD_BUFFEW:
	case WECEIVE_DIAGNOSTIC:
		if (wegacy) {
			wet = 1;
			bweak;
		}
		if (wegistewed_nexus) {
			wet = 0;
			bweak;
		}
		wet = (we) ? 0 : 1; /* Awwowed Wwite Excwusive */
		bweak;
	case PEWSISTENT_WESEWVE_OUT:
		/*
		 * This fowwows PEWSISTENT_WESEWVE_OUT sewvice actions that
		 * awe awwowed in the pwesence of vawious wesewvations.
		 * See spc4w17, tabwe 46
		 */
		switch (cdb[1] & 0x1f) {
		case PWO_CWEAW:
		case PWO_PWEEMPT:
		case PWO_PWEEMPT_AND_ABOWT:
			wet = (wegistewed_nexus) ? 0 : 1;
			bweak;
		case PWO_WEGISTEW:
		case PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY:
			wet = 0;
			bweak;
		case PWO_WEGISTEW_AND_MOVE:
		case PWO_WESEWVE:
			wet = 1;
			bweak;
		case PWO_WEWEASE:
			wet = (wegistewed_nexus) ? 0 : 1;
			bweak;
		defauwt:
			pw_eww("Unknown PEWSISTENT_WESEWVE_OUT sewvice"
				" action: 0x%02x\n", cdb[1] & 0x1f);
			wetuwn -EINVAW;
		}
		bweak;
	case WEWEASE:
	case WEWEASE_10:
		/* Handwed by CWH=1 in tawget_scsi2_wesewvation_wewease() */
		wet = 0;
		bweak;
	case WESEWVE:
	case WESEWVE_10:
		/* Handwed by CWH=1 in tawget_scsi2_wesewvation_wesewve() */
		wet = 0;
		bweak;
	case TEST_UNIT_WEADY:
		wet = (wegacy) ? 1 : 0; /* Confwict fow wegacy */
		bweak;
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_MANAGEMENT_PWOTOCOW_IN:
			if (wegistewed_nexus) {
				wet = 0;
				bweak;
			}
			wet = (we) ? 0 : 1; /* Awwowed Wwite Excwusive */
			bweak;
		case MI_WEPOWT_SUPPOWTED_OPEWATION_CODES:
		case MI_WEPOWT_SUPPOWTED_TASK_MANAGEMENT_FUNCTIONS:
			if (wegacy) {
				wet = 1;
				bweak;
			}
			if (wegistewed_nexus) {
				wet = 0;
				bweak;
			}
			wet = (we) ? 0 : 1; /* Awwowed Wwite Excwusive */
			bweak;
		case MI_WEPOWT_AWIASES:
		case MI_WEPOWT_IDENTIFYING_INFOWMATION:
		case MI_WEPOWT_PWIOWITY:
		case MI_WEPOWT_TAWGET_PGS:
		case MI_WEPOWT_TIMESTAMP:
			wet = 0; /* Awwowed */
			bweak;
		defauwt:
			pw_eww("Unknown MI Sewvice Action: 0x%02x\n",
				(cdb[1] & 0x1f));
			wetuwn -EINVAW;
		}
		bweak;
	case ACCESS_CONTWOW_IN:
	case ACCESS_CONTWOW_OUT:
	case INQUIWY:
	case WOG_SENSE:
	case SEWVICE_ACTION_IN_12:
	case WEAD_CAPACITY:
	case WEPOWT_WUNS:
	case WEQUEST_SENSE:
	case PEWSISTENT_WESEWVE_IN:
		wet = 0; /*/ Awwowed CDBs */
		bweak;
	defauwt:
		othew_cdb = 1;
		bweak;
	}
	/*
	 * Case whewe the CDB is expwicitwy awwowed in the above switch
	 * statement.
	 */
	if (!wet && !othew_cdb) {
		pw_debug("Awwowing expwicit CDB: 0x%02x fow %s"
			" wesewvation howdew\n", cdb[0],
			cowe_scsi3_pw_dump_type(pw_weg_type));

		wetuwn wet;
	}
	/*
	 * Check if wwite excwusive initiatow powts *NOT* howding the
	 * WWITE_EXCWUSIVE_* wesewvation.
	 */
	if (we && !wegistewed_nexus) {
		if (cmd->data_diwection == DMA_TO_DEVICE) {
			/*
			 * Confwict fow wwite excwusive
			 */
			pw_debug("%s Confwict fow unwegistewed nexus"
				" %s CDB: 0x%02x to %s wesewvation\n",
				twanspowt_dump_cmd_diwection(cmd),
				se_sess->se_node_acw->initiatowname, cdb[0],
				cowe_scsi3_pw_dump_type(pw_weg_type));
			wetuwn 1;
		} ewse {
			/*
			 * Awwow non WWITE CDBs fow aww Wwite Excwusive
			 * PW TYPEs to pass fow wegistewed and
			 * non-wegistewed_nexuxes NOT howding the wesewvation.
			 *
			 * We onwy make noise fow the unwegistewd nexuses,
			 * as we expect wegistewed non-wesewvation howding
			 * nexuses to issue CDBs.
			 */

			if (!wegistewed_nexus) {
				pw_debug("Awwowing impwicit CDB: 0x%02x"
					" fow %s wesewvation on unwegistewed"
					" nexus\n", cdb[0],
					cowe_scsi3_pw_dump_type(pw_weg_type));
			}

			wetuwn 0;
		}
	} ewse if ((weg_onwy) || (aww_weg)) {
		if (wegistewed_nexus) {
			/*
			 * Fow PW_*_WEG_ONWY and PW_*_AWW_WEG wesewvations,
			 * awwow commands fwom wegistewed nexuses.
			 */

			pw_debug("Awwowing impwicit CDB: 0x%02x fow %s"
				" wesewvation\n", cdb[0],
				cowe_scsi3_pw_dump_type(pw_weg_type));

			wetuwn 0;
		}
       } ewse if (we && wegistewed_nexus) {
               /*
                * Weads awe awwowed fow Wwite Excwusive wocks
                * fwom aww wegistwants.
                */
               if (cmd->data_diwection == DMA_FWOM_DEVICE) {
                       pw_debug("Awwowing WEAD CDB: 0x%02x fow %s"
                               " wesewvation\n", cdb[0],
                               cowe_scsi3_pw_dump_type(pw_weg_type));

                       wetuwn 0;
               }
	}
	pw_debug("%s Confwict fow %swegistewed nexus %s CDB: 0x%2x"
		" fow %s wesewvation\n", twanspowt_dump_cmd_diwection(cmd),
		(wegistewed_nexus) ? "" : "un",
		se_sess->se_node_acw->initiatowname, cdb[0],
		cowe_scsi3_pw_dump_type(pw_weg_type));

	wetuwn 1; /* Confwict by defauwt */
}

static sense_weason_t
tawget_scsi3_pw_wesewvation_check(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;
	u32 pw_weg_type;
	boow isid_mismatch = fawse;

	if (!dev->dev_pw_wes_howdew)
		wetuwn 0;

	pw_weg_type = dev->dev_pw_wes_howdew->pw_wes_type;
	cmd->pw_wes_key = dev->dev_pw_wes_howdew->pw_wes_key;
	if (dev->dev_pw_wes_howdew->pw_weg_nacw != sess->se_node_acw)
		goto check_nonhowdew;

	if (dev->dev_pw_wes_howdew->isid_pwesent_at_weg) {
		if (dev->dev_pw_wes_howdew->pw_weg_bin_isid !=
		    sess->sess_bin_isid) {
			isid_mismatch = twue;
			goto check_nonhowdew;
		}
	}

	wetuwn 0;

check_nonhowdew:
	if (cowe_scsi3_pw_seq_non_howdew(cmd, pw_weg_type, isid_mismatch))
		wetuwn TCM_WESEWVATION_CONFWICT;
	wetuwn 0;
}

static u32 cowe_scsi3_pw_genewation(stwuct se_device *dev)
{
	u32 pwg;

	/*
	 * PWGenewation fiewd shaww contain the vawue of a 32-bit wwapping
	 * countew mainted by the device sewvew.
	 *
	 * Note that this is done wegawdwess of Active Pewsist acwoss
	 * Tawget PowewWoss (APTPW)
	 *
	 * See spc4w17 section 6.3.12 WEAD_KEYS sewvice action
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pwg = dev->t10_pw.pw_genewation++;
	spin_unwock(&dev->dev_wesewvation_wock);

	wetuwn pwg;
}

static stwuct t10_pw_wegistwation *__cowe_scsi3_do_awwoc_wegistwation(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct se_wun *wun,
	stwuct se_dev_entwy *dest_deve,
	u64 mapped_wun,
	unsigned chaw *isid,
	u64 sa_wes_key,
	int aww_tg_pt,
	int aptpw)
{
	stwuct t10_pw_wegistwation *pw_weg;

	pw_weg = kmem_cache_zawwoc(t10_pw_weg_cache, GFP_ATOMIC);
	if (!pw_weg) {
		pw_eww("Unabwe to awwocate stwuct t10_pw_wegistwation\n");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&pw_weg->pw_weg_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_abowt_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_aptpw_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_atp_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_atp_mem_wist);
	atomic_set(&pw_weg->pw_wes_howdews, 0);
	pw_weg->pw_weg_nacw = nacw;
	/*
	 * Fow destination wegistwations fow AWW_TG_PT=1 and SPEC_I_PT=1,
	 * the se_dev_entwy->pw_wef wiww have been awweady obtained by
	 * cowe_get_se_deve_fwom_wtpi() ow __cowe_scsi3_awwoc_wegistwation().
	 *
	 * Othewwise, wocate se_dev_entwy now and obtain a wefewence untiw
	 * wegistwation compwetes in __cowe_scsi3_add_wegistwation().
	 */
	if (dest_deve) {
		pw_weg->pw_weg_deve = dest_deve;
	} ewse {
		wcu_wead_wock();
		pw_weg->pw_weg_deve = tawget_nacw_find_deve(nacw, mapped_wun);
		if (!pw_weg->pw_weg_deve) {
			wcu_wead_unwock();
			pw_eww("Unabwe to wocate PW deve %s mapped_wun: %wwu\n",
				nacw->initiatowname, mapped_wun);
			kmem_cache_fwee(t10_pw_weg_cache, pw_weg);
			wetuwn NUWW;
		}
		kwef_get(&pw_weg->pw_weg_deve->pw_kwef);
		wcu_wead_unwock();
	}
	pw_weg->pw_wes_mapped_wun = mapped_wun;
	pw_weg->pw_aptpw_tawget_wun = wun->unpacked_wun;
	pw_weg->tg_pt_sep_wtpi = wun->wun_tpg->tpg_wtpi;
	pw_weg->pw_wes_key = sa_wes_key;
	pw_weg->pw_weg_aww_tg_pt = aww_tg_pt;
	pw_weg->pw_weg_aptpw = aptpw;
	/*
	 * If an ISID vawue fow this SCSI Initiatow Powt exists,
	 * save it to the wegistwation now.
	 */
	if (isid != NUWW) {
		pw_weg->pw_weg_bin_isid = get_unawigned_be64(isid);
		snpwintf(pw_weg->pw_weg_isid, PW_WEG_ISID_WEN, "%s", isid);
		pw_weg->isid_pwesent_at_weg = 1;
	}

	wetuwn pw_weg;
}

static int cowe_scsi3_wunacw_depend_item(stwuct se_dev_entwy *);
static void cowe_scsi3_wunacw_undepend_item(stwuct se_dev_entwy *);

/*
 * Function used fow handwing PW wegistwations fow AWW_TG_PT=1 and AWW_TG_PT=0
 * modes.
 */
static stwuct t10_pw_wegistwation *__cowe_scsi3_awwoc_wegistwation(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct se_wun *wun,
	stwuct se_dev_entwy *deve,
	u64 mapped_wun,
	unsigned chaw *isid,
	u64 sa_wes_key,
	int aww_tg_pt,
	int aptpw)
{
	stwuct se_dev_entwy *deve_tmp;
	stwuct se_node_acw *nacw_tmp;
	stwuct se_wun_acw *wacw_tmp;
	stwuct se_wun *wun_tmp, *next, *dest_wun;
	const stwuct tawget_cowe_fabwic_ops *tfo = nacw->se_tpg->se_tpg_tfo;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_atp, *pw_weg_tmp, *pw_weg_tmp_safe;
	int wet;
	/*
	 * Cweate a wegistwation fow the I_T Nexus upon which the
	 * PWOUT WEGISTEW was weceived.
	 */
	pw_weg = __cowe_scsi3_do_awwoc_wegistwation(dev, nacw, wun, deve, mapped_wun,
						    isid, sa_wes_key, aww_tg_pt,
						    aptpw);
	if (!pw_weg)
		wetuwn NUWW;
	/*
	 * Wetuwn pointew to pw_weg fow AWW_TG_PT=0
	 */
	if (!aww_tg_pt)
		wetuwn pw_weg;
	/*
	 * Cweate wist of matching SCSI Initiatow Powt wegistwations
	 * fow AWW_TG_PT=1
	 */
	spin_wock(&dev->se_powt_wock);
	wist_fow_each_entwy_safe(wun_tmp, next, &dev->dev_sep_wist, wun_dev_wink) {
		if (!pewcpu_wef_twyget_wive(&wun_tmp->wun_wef))
			continue;
		spin_unwock(&dev->se_powt_wock);

		spin_wock(&wun_tmp->wun_deve_wock);
		wist_fow_each_entwy(deve_tmp, &wun_tmp->wun_deve_wist, wun_wink) {
			/*
			 * This pointew wiww be NUWW fow demo mode MappedWUNs
			 * that have not been make expwicit via a ConfigFS
			 * MappedWUN gwoup fow the SCSI Initiatow Node ACW.
			 */
			if (!deve_tmp->se_wun_acw)
				continue;

			wacw_tmp = deve_tmp->se_wun_acw;
			nacw_tmp = wacw_tmp->se_wun_nacw;
			/*
			 * Skip the matching stwuct se_node_acw that is awwocated
			 * above..
			 */
			if (nacw == nacw_tmp)
				continue;
			/*
			 * Onwy pewfowm PW wegistwations fow tawget powts on
			 * the same fabwic moduwe as the WEGISTEW w/ AWW_TG_PT=1
			 * awwived.
			 */
			if (tfo != nacw_tmp->se_tpg->se_tpg_tfo)
				continue;
			/*
			 * Wook fow a matching Initiatow Node ACW in ASCII fowmat
			 */
			if (stwcmp(nacw->initiatowname, nacw_tmp->initiatowname))
				continue;

			kwef_get(&deve_tmp->pw_kwef);
			spin_unwock(&wun_tmp->wun_deve_wock);
			/*
			 * Gwab a configfs gwoup dependency that is weweased
			 * fow the exception path at wabew out: bewow, ow upon
			 * compwetion of adding AWW_TG_PT=1 wegistwations in
			 * __cowe_scsi3_add_wegistwation()
			 */
			wet = cowe_scsi3_wunacw_depend_item(deve_tmp);
			if (wet < 0) {
				pw_eww("cowe_scsi3_wunacw_depend"
						"_item() faiwed\n");
				pewcpu_wef_put(&wun_tmp->wun_wef);
				kwef_put(&deve_tmp->pw_kwef, tawget_pw_kwef_wewease);
				goto out;
			}
			/*
			 * Wocated a matching SCSI Initiatow Powt on a diffewent
			 * powt, awwocate the pw_weg_atp and attach it to the
			 * pw_weg->pw_weg_atp_wist that wiww be pwocessed once
			 * the owiginaw *pw_weg is pwocessed in
			 * __cowe_scsi3_add_wegistwation()
			 */
			dest_wun = deve_tmp->se_wun;

			pw_weg_atp = __cowe_scsi3_do_awwoc_wegistwation(dev,
						nacw_tmp, dest_wun, deve_tmp,
						deve_tmp->mapped_wun, NUWW,
						sa_wes_key, aww_tg_pt, aptpw);
			if (!pw_weg_atp) {
				pewcpu_wef_put(&wun_tmp->wun_wef);
				cowe_scsi3_wunacw_undepend_item(deve_tmp);
				goto out;
			}

			wist_add_taiw(&pw_weg_atp->pw_weg_atp_mem_wist,
				      &pw_weg->pw_weg_atp_wist);
			spin_wock(&wun_tmp->wun_deve_wock);
		}
		spin_unwock(&wun_tmp->wun_deve_wock);

		spin_wock(&dev->se_powt_wock);
		pewcpu_wef_put(&wun_tmp->wun_wef);
	}
	spin_unwock(&dev->se_powt_wock);

	wetuwn pw_weg;
out:
	wist_fow_each_entwy_safe(pw_weg_tmp, pw_weg_tmp_safe,
			&pw_weg->pw_weg_atp_wist, pw_weg_atp_mem_wist) {
		wist_dew(&pw_weg_tmp->pw_weg_atp_mem_wist);
		cowe_scsi3_wunacw_undepend_item(pw_weg_tmp->pw_weg_deve);
		kmem_cache_fwee(t10_pw_weg_cache, pw_weg_tmp);
	}
	kmem_cache_fwee(t10_pw_weg_cache, pw_weg);
	wetuwn NUWW;
}

int cowe_scsi3_awwoc_aptpw_wegistwation(
	stwuct t10_wesewvation *pw_tmpw,
	u64 sa_wes_key,
	unsigned chaw *i_powt,
	unsigned chaw *isid,
	u64 mapped_wun,
	unsigned chaw *t_powt,
	u16 tpgt,
	u64 tawget_wun,
	int wes_howdew,
	int aww_tg_pt,
	u8 type)
{
	stwuct t10_pw_wegistwation *pw_weg;

	if (!i_powt || !t_powt || !sa_wes_key) {
		pw_eww("Iwwegaw pawametews fow APTPW wegistwation\n");
		wetuwn -EINVAW;
	}

	pw_weg = kmem_cache_zawwoc(t10_pw_weg_cache, GFP_KEWNEW);
	if (!pw_weg) {
		pw_eww("Unabwe to awwocate stwuct t10_pw_wegistwation\n");
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&pw_weg->pw_weg_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_abowt_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_aptpw_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_atp_wist);
	INIT_WIST_HEAD(&pw_weg->pw_weg_atp_mem_wist);
	atomic_set(&pw_weg->pw_wes_howdews, 0);
	pw_weg->pw_weg_nacw = NUWW;
	pw_weg->pw_weg_deve = NUWW;
	pw_weg->pw_wes_mapped_wun = mapped_wun;
	pw_weg->pw_aptpw_tawget_wun = tawget_wun;
	pw_weg->pw_wes_key = sa_wes_key;
	pw_weg->pw_weg_aww_tg_pt = aww_tg_pt;
	pw_weg->pw_weg_aptpw = 1;
	pw_weg->pw_wes_scope = 0; /* Awways WUN_SCOPE */
	pw_weg->pw_wes_type = type;
	/*
	 * If an ISID vawue had been saved in APTPW metadata fow this
	 * SCSI Initiatow Powt, westowe it now.
	 */
	if (isid != NUWW) {
		pw_weg->pw_weg_bin_isid = get_unawigned_be64(isid);
		snpwintf(pw_weg->pw_weg_isid, PW_WEG_ISID_WEN, "%s", isid);
		pw_weg->isid_pwesent_at_weg = 1;
	}
	/*
	 * Copy the i_powt and t_powt infowmation fwom cawwew.
	 */
	snpwintf(pw_weg->pw_ipowt, PW_APTPW_MAX_IPOWT_WEN, "%s", i_powt);
	snpwintf(pw_weg->pw_tpowt, PW_APTPW_MAX_TPOWT_WEN, "%s", t_powt);
	pw_weg->pw_weg_tpgt = tpgt;
	/*
	 * Set pw_wes_howdew fwom cawwew, the pw_weg who is the wesewvation
	 * howdew wiww get it's pointew set in cowe_scsi3_aptpw_wesewve() once
	 * the Initiatow Node WUN ACW fwom the fabwic moduwe is cweated fow
	 * this wegistwation.
	 */
	pw_weg->pw_wes_howdew = wes_howdew;

	wist_add_taiw(&pw_weg->pw_weg_aptpw_wist, &pw_tmpw->aptpw_weg_wist);
	pw_debug("SPC-3 PW APTPW Successfuwwy added wegistwation%s fwom"
			" metadata\n", (wes_howdew) ? "+wesewvation" : "");
	wetuwn 0;
}

static void cowe_scsi3_aptpw_wesewve(
	stwuct se_device *dev,
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_node_acw *node_acw,
	stwuct t10_pw_wegistwation *pw_weg)
{
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };

	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);

	spin_wock(&dev->dev_wesewvation_wock);
	dev->dev_pw_wes_howdew = pw_weg;
	spin_unwock(&dev->dev_wesewvation_wock);

	pw_debug("SPC-3 PW [%s] Sewvice Action: APTPW WESEWVE cweated"
		" new wesewvation howdew TYPE: %s AWW_TG_PT: %d\n",
		tpg->se_tpg_tfo->fabwic_name,
		cowe_scsi3_pw_dump_type(pw_weg->pw_wes_type),
		(pw_weg->pw_weg_aww_tg_pt) ? 1 : 0);
	pw_debug("SPC-3 PW [%s] WESEWVE Node: %s%s\n",
		tpg->se_tpg_tfo->fabwic_name, node_acw->initiatowname,
		i_buf);
}

static void __cowe_scsi3_add_wegistwation(stwuct se_device *, stwuct se_node_acw *,
				stwuct t10_pw_wegistwation *, enum wegistew_type, int);

static int __cowe_scsi3_check_aptpw_wegistwation(
	stwuct se_device *dev,
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun,
	u64 tawget_wun,
	stwuct se_node_acw *nacw,
	u64 mapped_wun)
{
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	unsigned chaw i_powt[PW_APTPW_MAX_IPOWT_WEN] = { };
	unsigned chaw t_powt[PW_APTPW_MAX_TPOWT_WEN] = { };
	u16 tpgt;

	/*
	 * Copy Initiatow Powt infowmation fwom stwuct se_node_acw
	 */
	snpwintf(i_powt, PW_APTPW_MAX_IPOWT_WEN, "%s", nacw->initiatowname);
	snpwintf(t_powt, PW_APTPW_MAX_TPOWT_WEN, "%s",
			tpg->se_tpg_tfo->tpg_get_wwn(tpg));
	tpgt = tpg->se_tpg_tfo->tpg_get_tag(tpg);
	/*
	 * Wook fow the matching wegistwations+wesewvation fwom those
	 * cweated fwom APTPW metadata.  Note that muwtipwe wegistwations
	 * may exist fow fabwics that use ISIDs in theiw SCSI Initiatow Powt
	 * TwanspowtIDs.
	 */
	spin_wock(&pw_tmpw->aptpw_weg_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp, &pw_tmpw->aptpw_weg_wist,
				pw_weg_aptpw_wist) {

		if (!stwcmp(pw_weg->pw_ipowt, i_powt) &&
		     (pw_weg->pw_wes_mapped_wun == mapped_wun) &&
		    !(stwcmp(pw_weg->pw_tpowt, t_powt)) &&
		     (pw_weg->pw_weg_tpgt == tpgt) &&
		     (pw_weg->pw_aptpw_tawget_wun == tawget_wun)) {
			/*
			 * Obtain the ->pw_weg_deve pointew + wefewence, that
			 * is weweased by __cowe_scsi3_add_wegistwation() bewow.
			 */
			wcu_wead_wock();
			pw_weg->pw_weg_deve = tawget_nacw_find_deve(nacw, mapped_wun);
			if (!pw_weg->pw_weg_deve) {
				pw_eww("Unabwe to wocate PW APTPW %s mapped_wun:"
					" %wwu\n", nacw->initiatowname, mapped_wun);
				wcu_wead_unwock();
				continue;
			}
			kwef_get(&pw_weg->pw_weg_deve->pw_kwef);
			wcu_wead_unwock();

			pw_weg->pw_weg_nacw = nacw;
			pw_weg->tg_pt_sep_wtpi = wun->wun_tpg->tpg_wtpi;
			wist_dew(&pw_weg->pw_weg_aptpw_wist);
			spin_unwock(&pw_tmpw->aptpw_weg_wock);
			/*
			 * At this point aww of the pointews in *pw_weg wiww
			 * be setup, so go ahead and add the wegistwation.
			 */
			__cowe_scsi3_add_wegistwation(dev, nacw, pw_weg, 0, 0);
			/*
			 * If this wegistwation is the wesewvation howdew,
			 * make that happen now..
			 */
			if (pw_weg->pw_wes_howdew)
				cowe_scsi3_aptpw_wesewve(dev, tpg,
						nacw, pw_weg);
			/*
			 * Weenabwe pw_aptpw_active to accept new metadata
			 * updates once the SCSI device is active again..
			 */
			spin_wock(&pw_tmpw->aptpw_weg_wock);
			pw_tmpw->pw_aptpw_active = 1;
		}
	}
	spin_unwock(&pw_tmpw->aptpw_weg_wock);

	wetuwn 0;
}

int cowe_scsi3_check_aptpw_wegistwation(
	stwuct se_device *dev,
	stwuct se_powtaw_gwoup *tpg,
	stwuct se_wun *wun,
	stwuct se_node_acw *nacw,
	u64 mapped_wun)
{
	if (dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS)
		wetuwn 0;

	wetuwn __cowe_scsi3_check_aptpw_wegistwation(dev, tpg, wun,
						     wun->unpacked_wun, nacw,
						     mapped_wun);
}

static void __cowe_scsi3_dump_wegistwation(
	const stwuct tawget_cowe_fabwic_ops *tfo,
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct t10_pw_wegistwation *pw_weg,
	enum wegistew_type wegistew_type)
{
	stwuct se_powtaw_gwoup *se_tpg = nacw->se_tpg;
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };

	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);

	pw_debug("SPC-3 PW [%s] Sewvice Action: WEGISTEW%s Initiatow"
		" Node: %s%s\n", tfo->fabwic_name, (wegistew_type == WEGISTEW_AND_MOVE) ?
		"_AND_MOVE" : (wegistew_type == WEGISTEW_AND_IGNOWE_EXISTING_KEY) ?
		"_AND_IGNOWE_EXISTING_KEY" : "", nacw->initiatowname,
		i_buf);
	pw_debug("SPC-3 PW [%s] wegistwation on Tawget Powt: %s,0x%04x\n",
		 tfo->fabwic_name, tfo->tpg_get_wwn(se_tpg),
		tfo->tpg_get_tag(se_tpg));
	pw_debug("SPC-3 PW [%s] fow %s TCM Subsystem %s Object Tawget"
		" Powt(s)\n",  tfo->fabwic_name,
		(pw_weg->pw_weg_aww_tg_pt) ? "AWW" : "SINGWE",
		dev->twanspowt->name);
	pw_debug("SPC-3 PW [%s] SA Wes Key: 0x%016Wx PWgenewation:"
		" 0x%08x  APTPW: %d\n", tfo->fabwic_name,
		pw_weg->pw_wes_key, pw_weg->pw_wes_genewation,
		pw_weg->pw_weg_aptpw);
}

static void __cowe_scsi3_add_wegistwation(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct t10_pw_wegistwation *pw_weg,
	enum wegistew_type wegistew_type,
	int wegistew_move)
{
	const stwuct tawget_cowe_fabwic_ops *tfo = nacw->se_tpg->se_tpg_tfo;
	stwuct t10_pw_wegistwation *pw_weg_tmp, *pw_weg_tmp_safe;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct se_dev_entwy *deve;

	/*
	 * Incwement PWgenewation countew fow stwuct se_device upon a successfuw
	 * WEGISTEW, see spc4w17 section 6.3.2 WEAD_KEYS sewvice action
	 *
	 * Awso, when wegistew_move = 1 fow PWOUT WEGISTEW_AND_MOVE sewvice
	 * action, the stwuct se_device->dev_wesewvation_wock wiww awweady be hewd,
	 * so we do not caww cowe_scsi3_pw_genewation() which gwabs the wock
	 * fow the WEGISTEW.
	 */
	pw_weg->pw_wes_genewation = (wegistew_move) ?
			dev->t10_pw.pw_genewation++ :
			cowe_scsi3_pw_genewation(dev);

	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_add_taiw(&pw_weg->pw_weg_wist, &pw_tmpw->wegistwation_wist);

	__cowe_scsi3_dump_wegistwation(tfo, dev, nacw, pw_weg, wegistew_type);
	spin_unwock(&pw_tmpw->wegistwation_wock);
	/*
	 * Skip extwa pwocessing fow AWW_TG_PT=0 ow WEGISTEW_AND_MOVE.
	 */
	if (!pw_weg->pw_weg_aww_tg_pt || wegistew_move)
		goto out;
	/*
	 * Wawk pw_weg->pw_weg_atp_wist and add wegistwations fow AWW_TG_PT=1
	 * awwocated in __cowe_scsi3_awwoc_wegistwation()
	 */
	wist_fow_each_entwy_safe(pw_weg_tmp, pw_weg_tmp_safe,
			&pw_weg->pw_weg_atp_wist, pw_weg_atp_mem_wist) {
		stwuct se_node_acw *nacw_tmp = pw_weg_tmp->pw_weg_nacw;

		wist_dew(&pw_weg_tmp->pw_weg_atp_mem_wist);

		pw_weg_tmp->pw_wes_genewation = cowe_scsi3_pw_genewation(dev);

		spin_wock(&pw_tmpw->wegistwation_wock);
		wist_add_taiw(&pw_weg_tmp->pw_weg_wist,
			      &pw_tmpw->wegistwation_wist);

		__cowe_scsi3_dump_wegistwation(tfo, dev, nacw_tmp, pw_weg_tmp,
					       wegistew_type);
		spin_unwock(&pw_tmpw->wegistwation_wock);
		/*
		 * Dwop configfs gwoup dependency wefewence and deve->pw_kwef
		 * obtained fwom  __cowe_scsi3_awwoc_wegistwation() code.
		 */
		wcu_wead_wock();
		deve = pw_weg_tmp->pw_weg_deve;
		if (deve) {
			set_bit(DEF_PW_WEG_ACTIVE, &deve->deve_fwags);
			cowe_scsi3_wunacw_undepend_item(deve);
			pw_weg_tmp->pw_weg_deve = NUWW;
		}
		wcu_wead_unwock();
	}
out:
	/*
	 * Dwop deve->pw_kwef obtained in __cowe_scsi3_do_awwoc_wegistwation()
	 */
	wcu_wead_wock();
	deve = pw_weg->pw_weg_deve;
	if (deve) {
		set_bit(DEF_PW_WEG_ACTIVE, &deve->deve_fwags);
		kwef_put(&deve->pw_kwef, tawget_pw_kwef_wewease);
		pw_weg->pw_weg_deve = NUWW;
	}
	wcu_wead_unwock();
}

static int cowe_scsi3_awwoc_wegistwation(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct se_wun *wun,
	stwuct se_dev_entwy *deve,
	u64 mapped_wun,
	unsigned chaw *isid,
	u64 sa_wes_key,
	int aww_tg_pt,
	int aptpw,
	enum wegistew_type wegistew_type,
	int wegistew_move)
{
	stwuct t10_pw_wegistwation *pw_weg;

	pw_weg = __cowe_scsi3_awwoc_wegistwation(dev, nacw, wun, deve, mapped_wun,
						 isid, sa_wes_key, aww_tg_pt,
						 aptpw);
	if (!pw_weg)
		wetuwn -EPEWM;

	__cowe_scsi3_add_wegistwation(dev, nacw, pw_weg,
			wegistew_type, wegistew_move);
	wetuwn 0;
}

static stwuct t10_pw_wegistwation *__cowe_scsi3_wocate_pw_weg(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	unsigned chaw *isid)
{
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp;

	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {
		/*
		 * Fiwst wook fow a matching stwuct se_node_acw
		 */
		if (pw_weg->pw_weg_nacw != nacw)
			continue;

		/*
		 * If this wegistwation does NOT contain a fabwic pwovided
		 * ISID, then we have found a match.
		 */
		if (!pw_weg->isid_pwesent_at_weg) {
			atomic_inc_mb(&pw_weg->pw_wes_howdews);
			spin_unwock(&pw_tmpw->wegistwation_wock);
			wetuwn pw_weg;
		}
		/*
		 * If the *pw_weg contains a fabwic defined ISID fow muwti-vawue
		 * SCSI Initiatow Powt TwanspowtIDs, then we expect a vawid
		 * matching ISID to be pwovided by the wocaw SCSI Initiatow Powt.
		 */
		if (!isid)
			continue;
		if (stwcmp(isid, pw_weg->pw_weg_isid))
			continue;

		atomic_inc_mb(&pw_weg->pw_wes_howdews);
		spin_unwock(&pw_tmpw->wegistwation_wock);
		wetuwn pw_weg;
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);

	wetuwn NUWW;
}

static stwuct t10_pw_wegistwation *cowe_scsi3_wocate_pw_weg(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw,
	stwuct se_session *sess)
{
	stwuct se_powtaw_gwoup *tpg = nacw->se_tpg;
	unsigned chaw buf[PW_WEG_ISID_WEN] = { };
	unsigned chaw *isid_ptw = NUWW;

	if (tpg->se_tpg_tfo->sess_get_initiatow_sid != NUWW) {
		tpg->se_tpg_tfo->sess_get_initiatow_sid(sess, &buf[0],
					PW_WEG_ISID_WEN);
		isid_ptw = &buf[0];
	}

	wetuwn __cowe_scsi3_wocate_pw_weg(dev, nacw, isid_ptw);
}

static void cowe_scsi3_put_pw_weg(stwuct t10_pw_wegistwation *pw_weg)
{
	atomic_dec_mb(&pw_weg->pw_wes_howdews);
}

static int cowe_scsi3_check_impwicit_wewease(
	stwuct se_device *dev,
	stwuct t10_pw_wegistwation *pw_weg)
{
	stwuct se_node_acw *nacw = pw_weg->pw_weg_nacw;
	stwuct t10_pw_wegistwation *pw_wes_howdew;
	int wet = 0;

	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (!pw_wes_howdew) {
		spin_unwock(&dev->dev_wesewvation_wock);
		wetuwn wet;
	}
	if (pw_wes_howdew == pw_weg) {
		/*
		 * Pewfowm an impwicit WEWEASE if the wegistwation that
		 * is being weweased is howding the wesewvation.
		 *
		 * Fwom spc4w17, section 5.7.11.1:
		 *
		 * e) If the I_T nexus is the pewsistent wesewvation howdew
		 *    and the pewsistent wesewvation is not an aww wegistwants
		 *    type, then a PEWSISTENT WESEWVE OUT command with WEGISTEW
		 *    sewvice action ow WEGISTEW AND  IGNOWE EXISTING KEY
		 *    sewvice action with the SEWVICE ACTION WESEWVATION KEY
		 *    fiewd set to zewo (see 5.7.11.3).
		 */
		__cowe_scsi3_compwete_pwo_wewease(dev, nacw, pw_weg, 0, 1);
		wet = 1;
		/*
		 * Fow 'Aww Wegistwants' wesewvation types, aww existing
		 * wegistwations awe stiww pwocessed as wesewvation howdews
		 * in cowe_scsi3_pw_seq_non_howdew() aftew the initiaw
		 * wesewvation howdew is impwicitwy weweased hewe.
		 */
	} ewse if (pw_weg->pw_weg_aww_tg_pt &&
		  (!stwcmp(pw_wes_howdew->pw_weg_nacw->initiatowname,
			  pw_weg->pw_weg_nacw->initiatowname)) &&
		  (pw_wes_howdew->pw_wes_key == pw_weg->pw_wes_key)) {
		pw_eww("SPC-3 PW: Unabwe to pewfowm AWW_TG_PT=1"
			" UNWEGISTEW whiwe existing wesewvation with matching"
			" key 0x%016Wx is pwesent fwom anothew SCSI Initiatow"
			" Powt\n", pw_weg->pw_wes_key);
		wet = -EPEWM;
	}
	spin_unwock(&dev->dev_wesewvation_wock);

	wetuwn wet;
}

static void __cowe_scsi3_fwee_wegistwation(
	stwuct se_device *dev,
	stwuct t10_pw_wegistwation *pw_weg,
	stwuct wist_head *pweempt_and_abowt_wist,
	int dec_howdews)
	__weweases(&pw_tmpw->wegistwation_wock)
	__acquiwes(&pw_tmpw->wegistwation_wock)
{
	const stwuct tawget_cowe_fabwic_ops *tfo =
			pw_weg->pw_weg_nacw->se_tpg->se_tpg_tfo;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct se_node_acw *nacw = pw_weg->pw_weg_nacw;
	stwuct se_dev_entwy *deve;
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };

	wockdep_assewt_hewd(&pw_tmpw->wegistwation_wock);

	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);

	if (!wist_empty(&pw_weg->pw_weg_wist))
		wist_dew(&pw_weg->pw_weg_wist);
	/*
	 * Cawwew accessing *pw_weg using cowe_scsi3_wocate_pw_weg(),
	 * so caww cowe_scsi3_put_pw_weg() to decwement ouw wefewence.
	 */
	if (dec_howdews)
		cowe_scsi3_put_pw_weg(pw_weg);

	spin_unwock(&pw_tmpw->wegistwation_wock);
	/*
	 * Wait untiw aww wefewence fwom any othew I_T nexuses fow this
	 * *pw_weg have been weweased.  Because wist_dew() is cawwed above,
	 * the wast cowe_scsi3_put_pw_weg(pw_weg) wiww wewease this wefewence
	 * count back to zewo, and we wewease *pw_weg.
	 */
	whiwe (atomic_wead(&pw_weg->pw_wes_howdews) != 0) {
		pw_debug("SPC-3 PW [%s] waiting fow pw_wes_howdews\n",
				tfo->fabwic_name);
		cpu_wewax();
	}

	wcu_wead_wock();
	deve = tawget_nacw_find_deve(nacw, pw_weg->pw_wes_mapped_wun);
	if (deve)
		cweaw_bit(DEF_PW_WEG_ACTIVE, &deve->deve_fwags);
	wcu_wead_unwock();

	spin_wock(&pw_tmpw->wegistwation_wock);
	pw_debug("SPC-3 PW [%s] Sewvice Action: UNWEGISTEW Initiatow"
		" Node: %s%s\n", tfo->fabwic_name,
		pw_weg->pw_weg_nacw->initiatowname,
		i_buf);
	pw_debug("SPC-3 PW [%s] fow %s TCM Subsystem %s Object Tawget"
		" Powt(s)\n", tfo->fabwic_name,
		(pw_weg->pw_weg_aww_tg_pt) ? "AWW" : "SINGWE",
		dev->twanspowt->name);
	pw_debug("SPC-3 PW [%s] SA Wes Key: 0x%016Wx PWgenewation:"
		" 0x%08x\n", tfo->fabwic_name, pw_weg->pw_wes_key,
		pw_weg->pw_wes_genewation);

	if (!pweempt_and_abowt_wist) {
		pw_weg->pw_weg_deve = NUWW;
		pw_weg->pw_weg_nacw = NUWW;
		kmem_cache_fwee(t10_pw_weg_cache, pw_weg);
		wetuwn;
	}
	/*
	 * Fow PWEEMPT_AND_ABOWT, the wist of *pw_weg in pweempt_and_abowt_wist
	 * awe weweased once the ABOWT_TASK_SET has compweted..
	 */
	wist_add_taiw(&pw_weg->pw_weg_abowt_wist, pweempt_and_abowt_wist);
}

void cowe_scsi3_fwee_pw_weg_fwom_nacw(
	stwuct se_device *dev,
	stwuct se_node_acw *nacw)
{
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp, *pw_wes_howdew;
	boow fwee_weg = fawse;
	/*
	 * If the passed se_node_acw matches the wesewvation howdew,
	 * wewease the wesewvation.
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if ((pw_wes_howdew != NUWW) &&
	    (pw_wes_howdew->pw_weg_nacw == nacw)) {
		__cowe_scsi3_compwete_pwo_wewease(dev, nacw, pw_wes_howdew, 0, 1);
		fwee_weg = twue;
	}
	spin_unwock(&dev->dev_wesewvation_wock);
	/*
	 * Wewease any wegistwation associated with the stwuct se_node_acw.
	 */
	spin_wock(&pw_tmpw->wegistwation_wock);
	if (pw_wes_howdew && fwee_weg)
		__cowe_scsi3_fwee_wegistwation(dev, pw_wes_howdew, NUWW, 0);

	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {

		if (pw_weg->pw_weg_nacw != nacw)
			continue;

		__cowe_scsi3_fwee_wegistwation(dev, pw_weg, NUWW, 0);
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);
}

void cowe_scsi3_fwee_aww_wegistwations(
	stwuct se_device *dev)
{
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp, *pw_wes_howdew;

	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (pw_wes_howdew != NUWW) {
		stwuct se_node_acw *pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
		__cowe_scsi3_compwete_pwo_wewease(dev, pw_wes_nacw,
						  pw_wes_howdew, 0, 0);
	}
	spin_unwock(&dev->dev_wesewvation_wock);

	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {

		__cowe_scsi3_fwee_wegistwation(dev, pw_weg, NUWW, 0);
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);

	spin_wock(&pw_tmpw->aptpw_weg_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp, &pw_tmpw->aptpw_weg_wist,
				pw_weg_aptpw_wist) {
		wist_dew(&pw_weg->pw_weg_aptpw_wist);
		kmem_cache_fwee(t10_pw_weg_cache, pw_weg);
	}
	spin_unwock(&pw_tmpw->aptpw_weg_wock);
}

static int cowe_scsi3_tpg_depend_item(stwuct se_powtaw_gwoup *tpg)
{
	wetuwn tawget_depend_item(&tpg->tpg_gwoup.cg_item);
}

static void cowe_scsi3_tpg_undepend_item(stwuct se_powtaw_gwoup *tpg)
{
	tawget_undepend_item(&tpg->tpg_gwoup.cg_item);
	atomic_dec_mb(&tpg->tpg_pw_wef_count);
}

static int cowe_scsi3_nodeacw_depend_item(stwuct se_node_acw *nacw)
{
	if (nacw->dynamic_node_acw)
		wetuwn 0;
	wetuwn tawget_depend_item(&nacw->acw_gwoup.cg_item);
}

static void cowe_scsi3_nodeacw_undepend_item(stwuct se_node_acw *nacw)
{
	if (!nacw->dynamic_node_acw)
		tawget_undepend_item(&nacw->acw_gwoup.cg_item);
	atomic_dec_mb(&nacw->acw_pw_wef_count);
}

static int cowe_scsi3_wunacw_depend_item(stwuct se_dev_entwy *se_deve)
{
	/*
	 * Fow nacw->dynamic_node_acw=1
	 */
	if (!se_deve->se_wun_acw)
		wetuwn 0;

	wetuwn tawget_depend_item(&se_deve->se_wun_acw->se_wun_gwoup.cg_item);
}

static void cowe_scsi3_wunacw_undepend_item(stwuct se_dev_entwy *se_deve)
{
	/*
	 * Fow nacw->dynamic_node_acw=1
	 */
	if (!se_deve->se_wun_acw) {
		kwef_put(&se_deve->pw_kwef, tawget_pw_kwef_wewease);
		wetuwn;
	}

	tawget_undepend_item(&se_deve->se_wun_acw->se_wun_gwoup.cg_item);
	kwef_put(&se_deve->pw_kwef, tawget_pw_kwef_wewease);
}

static sense_weason_t
cowe_scsi3_decode_spec_i_powt(
	stwuct se_cmd *cmd,
	stwuct se_powtaw_gwoup *tpg,
	unsigned chaw *w_isid,
	u64 sa_wes_key,
	int aww_tg_pt,
	int aptpw)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_powtaw_gwoup *dest_tpg = NUWW, *tmp_tpg;
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_node_acw *dest_node_acw = NUWW;
	stwuct se_dev_entwy *dest_se_deve = NUWW;
	stwuct t10_pw_wegistwation *dest_pw_weg, *wocaw_pw_weg, *pw_weg_e;
	stwuct t10_pw_wegistwation *pw_weg_tmp, *pw_weg_tmp_safe;
	WIST_HEAD(tid_dest_wist);
	stwuct pw_twanspowt_id_howdew *tidh_new, *tidh, *tidh_tmp;
	unsigned chaw *buf, *ptw, pwoto_ident;
	const unsigned chaw *i_stw = NUWW;
	chaw *ipowt_ptw = NUWW, i_buf[PW_WEG_ISID_ID_WEN];
	sense_weason_t wet;
	u32 tpdw, tid_wen = 0;
	u32 dest_wtpi = 0;

	/*
	 * Awwocate a stwuct pw_twanspowt_id_howdew and setup the
	 * wocaw_node_acw pointew and add to stwuct wist_head tid_dest_wist
	 * fow add wegistwation pwocessing in the woop of tid_dest_wist bewow.
	 */
	tidh_new = kzawwoc(sizeof(stwuct pw_twanspowt_id_howdew), GFP_KEWNEW);
	if (!tidh_new) {
		pw_eww("Unabwe to awwocate tidh_new\n");
		wetuwn TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
	}
	INIT_WIST_HEAD(&tidh_new->dest_wist);
	tidh_new->dest_tpg = tpg;
	tidh_new->dest_node_acw = se_sess->se_node_acw;

	wocaw_pw_weg = __cowe_scsi3_awwoc_wegistwation(cmd->se_dev,
				se_sess->se_node_acw, cmd->se_wun,
				NUWW, cmd->owig_fe_wun, w_isid,
				sa_wes_key, aww_tg_pt, aptpw);
	if (!wocaw_pw_weg) {
		kfwee(tidh_new);
		wetuwn TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
	}

	if (cowe_scsi3_wunacw_depend_item(wocaw_pw_weg->pw_weg_deve)) {
		kfwee(tidh_new);
		kwef_put(&wocaw_pw_weg->pw_weg_deve->pw_kwef,
			 tawget_pw_kwef_wewease);
		kmem_cache_fwee(t10_pw_weg_cache, wocaw_pw_weg);
		wetuwn TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
	}

	tidh_new->dest_pw_weg = wocaw_pw_weg;
	wist_add_taiw(&tidh_new->dest_wist, &tid_dest_wist);

	if (cmd->data_wength < 28) {
		pw_wawn("SPC-PW: Weceived PW OUT pawametew wist"
			" wength too smaww: %u\n", cmd->data_wength);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf) {
		wet = TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
		goto out;
	}

	/*
	 * Fow a PEWSISTENT WESEWVE OUT specify initiatow powts paywoad,
	 * fiwst extwact TwanspowtID Pawametew Data Wength, and make suwe
	 * the vawue matches up to the SCSI expected data twansfew wength.
	 */
	tpdw = get_unawigned_be32(&buf[24]);

	if ((tpdw + 28) != cmd->data_wength) {
		pw_eww("SPC-3 PW: Iwwegaw tpdw: %u + 28 byte headew"
			" does not equaw CDB data_wength: %u\n", tpdw,
			cmd->data_wength);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out_unmap;
	}
	/*
	 * Stawt pwocessing the weceived twanspowt IDs using the
	 * weceiving I_T Nexus powtaw's fabwic dependent methods to
	 * obtain the SCSI Initiatow Powt/Device Identifiews.
	 */
	ptw = &buf[28];

	whiwe (tpdw > 0) {
		stwuct se_wun *dest_wun, *tmp_wun;

		pwoto_ident = (ptw[0] & 0x0f);
		dest_tpg = NUWW;

		spin_wock(&dev->se_powt_wock);
		wist_fow_each_entwy(tmp_wun, &dev->dev_sep_wist, wun_dev_wink) {
			tmp_tpg = tmp_wun->wun_tpg;

			/*
			 * Wook fow the matching pwoto_ident pwovided by
			 * the weceived TwanspowtID
			 */
			if (tmp_tpg->pwoto_id != pwoto_ident)
				continue;
			dest_wtpi = tmp_wun->wun_tpg->tpg_wtpi;

			ipowt_ptw = NUWW;
			i_stw = tawget_pawse_pw_out_twanspowt_id(tmp_tpg,
					ptw, &tid_wen, &ipowt_ptw);
			if (!i_stw)
				continue;
			/*
			 * Detewmine if this SCSI device sewvew wequiwes that
			 * SCSI Intiatiow TwanspowtID w/ ISIDs is enfowced
			 * fow fabwic moduwes (iSCSI) wequiwing them.
			 */
			if (tpg->se_tpg_tfo->sess_get_initiatow_sid &&
			    dev->dev_attwib.enfowce_pw_isids &&
			    !ipowt_ptw) {
				pw_wawn("SPC-PW: enfowce_pw_isids is set but a isid has not been sent in the SPEC_I_PT data fow %s.",
					i_stw);
				wet = TCM_INVAWID_PAWAMETEW_WIST;
				spin_unwock(&dev->se_powt_wock);
				goto out_unmap;
			}

			atomic_inc_mb(&tmp_tpg->tpg_pw_wef_count);
			spin_unwock(&dev->se_powt_wock);

			if (cowe_scsi3_tpg_depend_item(tmp_tpg)) {
				pw_eww(" cowe_scsi3_tpg_depend_item()"
					" fow tmp_tpg\n");
				atomic_dec_mb(&tmp_tpg->tpg_pw_wef_count);
				wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
				goto out_unmap;
			}
			/*
			 * Wocate the destination initiatow ACW to be wegistewed
			 * fwom the decoded fabwic moduwe specific TwanspowtID
			 * at *i_stw.
			 */
			mutex_wock(&tmp_tpg->acw_node_mutex);
			dest_node_acw = __cowe_tpg_get_initiatow_node_acw(
						tmp_tpg, i_stw);
			if (dest_node_acw)
				atomic_inc_mb(&dest_node_acw->acw_pw_wef_count);
			mutex_unwock(&tmp_tpg->acw_node_mutex);

			if (!dest_node_acw) {
				cowe_scsi3_tpg_undepend_item(tmp_tpg);
				spin_wock(&dev->se_powt_wock);
				continue;
			}

			if (cowe_scsi3_nodeacw_depend_item(dest_node_acw)) {
				pw_eww("configfs_depend_item() faiwed"
					" fow dest_node_acw->acw_gwoup\n");
				atomic_dec_mb(&dest_node_acw->acw_pw_wef_count);
				cowe_scsi3_tpg_undepend_item(tmp_tpg);
				wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
				goto out_unmap;
			}

			dest_tpg = tmp_tpg;
			pw_debug("SPC-3 PW SPEC_I_PT: Wocated %s Node: %s Powt WTPI: %u\n",
				dest_tpg->se_tpg_tfo->fabwic_name,
				dest_node_acw->initiatowname, dest_wtpi);

			spin_wock(&dev->se_powt_wock);
			bweak;
		}
		spin_unwock(&dev->se_powt_wock);

		if (!dest_tpg) {
			pw_eww("SPC-3 PW SPEC_I_PT: Unabwe to wocate"
					" dest_tpg\n");
			wet = TCM_INVAWID_PAWAMETEW_WIST;
			goto out_unmap;
		}

		pw_debug("SPC-3 PW SPEC_I_PT: Got %s data_wength: %u tpdw: %u"
			" tid_wen: %d fow %s + %s\n",
			dest_tpg->se_tpg_tfo->fabwic_name, cmd->data_wength,
			tpdw, tid_wen, i_stw, ipowt_ptw);

		if (tid_wen > tpdw) {
			pw_eww("SPC-3 PW SPEC_I_PT: Iwwegaw tid_wen:"
				" %u fow Twanspowt ID: %s\n", tid_wen, ptw);
			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			wet = TCM_INVAWID_PAWAMETEW_WIST;
			goto out_unmap;
		}
		/*
		 * Wocate the desintation stwuct se_dev_entwy pointew fow matching
		 * WEWATIVE TAWGET POWT IDENTIFIEW on the weceiving I_T Nexus
		 * Tawget Powt.
		 */
		dest_se_deve = cowe_get_se_deve_fwom_wtpi(dest_node_acw,
					dest_wtpi);
		if (!dest_se_deve) {
			pw_eww("Unabwe to wocate %s dest_se_deve fwom destination WTPI: %u\n",
				dest_tpg->se_tpg_tfo->fabwic_name,
				dest_wtpi);

			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			wet = TCM_INVAWID_PAWAMETEW_WIST;
			goto out_unmap;
		}

		if (cowe_scsi3_wunacw_depend_item(dest_se_deve)) {
			pw_eww("cowe_scsi3_wunacw_depend_item()"
					" faiwed\n");
			kwef_put(&dest_se_deve->pw_kwef, tawget_pw_kwef_wewease);
			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
			goto out_unmap;
		}

		pw_debug("SPC-3 PW SPEC_I_PT: Wocated %s Node: %s"
			" dest_se_deve mapped_wun: %wwu\n",
			dest_tpg->se_tpg_tfo->fabwic_name,
			dest_node_acw->initiatowname, dest_se_deve->mapped_wun);

		/*
		 * Skip any TwanspowtIDs that awweady have a wegistwation fow
		 * this tawget powt.
		 */
		pw_weg_e = __cowe_scsi3_wocate_pw_weg(dev, dest_node_acw,
					ipowt_ptw);
		if (pw_weg_e) {
			cowe_scsi3_put_pw_weg(pw_weg_e);
			cowe_scsi3_wunacw_undepend_item(dest_se_deve);
			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			ptw += tid_wen;
			tpdw -= tid_wen;
			tid_wen = 0;
			continue;
		}
		/*
		 * Awwocate a stwuct pw_twanspowt_id_howdew and setup
		 * the dest_node_acw and dest_se_deve pointews fow the
		 * woop bewow.
		 */
		tidh_new = kzawwoc(sizeof(stwuct pw_twanspowt_id_howdew),
				GFP_KEWNEW);
		if (!tidh_new) {
			pw_eww("Unabwe to awwocate tidh_new\n");
			cowe_scsi3_wunacw_undepend_item(dest_se_deve);
			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
			goto out_unmap;
		}
		INIT_WIST_HEAD(&tidh_new->dest_wist);
		tidh_new->dest_tpg = dest_tpg;
		tidh_new->dest_node_acw = dest_node_acw;
		tidh_new->dest_se_deve = dest_se_deve;

		/*
		 * Awwocate, but do NOT add the wegistwation fow the
		 * TwanspowtID wefewenced SCSI Initiatow powt.  This
		 * done because of the fowwowing fwom spc4w17 in section
		 * 6.14.3 wwt SPEC_I_PT:
		 *
		 * "If a wegistwation faiws fow any initiatow powt (e.g., if th
		 * wogicaw unit does not have enough wesouwces avaiwabwe to
		 * howd the wegistwation infowmation), no wegistwations shaww be
		 * made, and the command shaww be tewminated with
		 * CHECK CONDITION status."
		 *
		 * That means we caww __cowe_scsi3_awwoc_wegistwation() hewe,
		 * and then caww __cowe_scsi3_add_wegistwation() in the
		 * 2nd woop which wiww nevew faiw.
		 */
		dest_wun = dest_se_deve->se_wun;

		dest_pw_weg = __cowe_scsi3_awwoc_wegistwation(cmd->se_dev,
					dest_node_acw, dest_wun, dest_se_deve,
					dest_se_deve->mapped_wun, ipowt_ptw,
					sa_wes_key, aww_tg_pt, aptpw);
		if (!dest_pw_weg) {
			cowe_scsi3_wunacw_undepend_item(dest_se_deve);
			cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
			cowe_scsi3_tpg_undepend_item(dest_tpg);
			kfwee(tidh_new);
			wet = TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
			goto out_unmap;
		}
		tidh_new->dest_pw_weg = dest_pw_weg;
		wist_add_taiw(&tidh_new->dest_wist, &tid_dest_wist);

		ptw += tid_wen;
		tpdw -= tid_wen;
		tid_wen = 0;

	}

	twanspowt_kunmap_data_sg(cmd);

	/*
	 * Go ahead and cweate a wegistwations fwom tid_dest_wist fow the
	 * SPEC_I_PT pwovided TwanspowtID fow the *tidh wefewenced dest_node_acw
	 * and dest_se_deve.
	 *
	 * The SA Wesewvation Key fwom the PWOUT is set fow the
	 * wegistwation, and AWW_TG_PT is awso passed.  AWW_TG_PT=1
	 * means that the TwanspowtID Initiatow powt wiww be
	 * wegistewed on aww of the tawget powts in the SCSI tawget device
	 * AWW_TG_PT=0 means the wegistwation wiww onwy be fow the
	 * SCSI tawget powt the PWOUT WEGISTEW with SPEC_I_PT=1
	 * was weceived.
	 */
	wist_fow_each_entwy_safe(tidh, tidh_tmp, &tid_dest_wist, dest_wist) {
		dest_tpg = tidh->dest_tpg;
		dest_node_acw = tidh->dest_node_acw;
		dest_se_deve = tidh->dest_se_deve;
		dest_pw_weg = tidh->dest_pw_weg;

		wist_dew(&tidh->dest_wist);
		kfwee(tidh);

		memset(i_buf, 0, PW_WEG_ISID_ID_WEN);
		cowe_pw_dump_initiatow_powt(dest_pw_weg, i_buf, PW_WEG_ISID_ID_WEN);

		__cowe_scsi3_add_wegistwation(cmd->se_dev, dest_node_acw,
					dest_pw_weg, 0, 0);

		pw_debug("SPC-3 PW [%s] SPEC_I_PT: Successfuwwy"
			" wegistewed Twanspowt ID fow Node: %s%s Mapped WUN:"
			" %wwu\n", dest_tpg->se_tpg_tfo->fabwic_name,
			dest_node_acw->initiatowname, i_buf, (dest_se_deve) ?
			dest_se_deve->mapped_wun : 0);

		if (dest_pw_weg == wocaw_pw_weg)
			continue;

		cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
		cowe_scsi3_tpg_undepend_item(dest_tpg);
	}

	wetuwn 0;
out_unmap:
	twanspowt_kunmap_data_sg(cmd);
out:
	/*
	 * Fow the faiwuwe case, wewease evewything fwom tid_dest_wist
	 * incwuding *dest_pw_weg and the configfs dependances..
	 */
	wist_fow_each_entwy_safe(tidh, tidh_tmp, &tid_dest_wist, dest_wist) {
		boow is_wocaw = fawse;

		dest_tpg = tidh->dest_tpg;
		dest_node_acw = tidh->dest_node_acw;
		dest_se_deve = tidh->dest_se_deve;
		dest_pw_weg = tidh->dest_pw_weg;

		if (dest_pw_weg == wocaw_pw_weg)
			is_wocaw = twue;

		wist_dew(&tidh->dest_wist);
		kfwee(tidh);
		/*
		 * Wewease any extwa AWW_TG_PT=1 wegistwations fow
		 * the SPEC_I_PT=1 case.
		 */
		wist_fow_each_entwy_safe(pw_weg_tmp, pw_weg_tmp_safe,
				&dest_pw_weg->pw_weg_atp_wist,
				pw_weg_atp_mem_wist) {
			wist_dew(&pw_weg_tmp->pw_weg_atp_mem_wist);
			cowe_scsi3_wunacw_undepend_item(pw_weg_tmp->pw_weg_deve);
			kmem_cache_fwee(t10_pw_weg_cache, pw_weg_tmp);
		}

		kmem_cache_fwee(t10_pw_weg_cache, dest_pw_weg);
		cowe_scsi3_wunacw_undepend_item(dest_se_deve);

		if (is_wocaw)
			continue;

		cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
		cowe_scsi3_tpg_undepend_item(dest_tpg);
	}
	wetuwn wet;
}

static int cowe_scsi3_update_aptpw_buf(
	stwuct se_device *dev,
	unsigned chaw *buf,
	u32 pw_aptpw_buf_wen)
{
	stwuct se_powtaw_gwoup *tpg;
	stwuct t10_pw_wegistwation *pw_weg;
	unsigned chaw tmp[512], isid_buf[32];
	ssize_t wen = 0;
	int weg_count = 0;
	int wet = 0;

	spin_wock(&dev->dev_wesewvation_wock);
	spin_wock(&dev->t10_pw.wegistwation_wock);
	/*
	 * Wawk the wegistwation wist..
	 */
	wist_fow_each_entwy(pw_weg, &dev->t10_pw.wegistwation_wist,
			pw_weg_wist) {

		tmp[0] = '\0';
		isid_buf[0] = '\0';
		tpg = pw_weg->pw_weg_nacw->se_tpg;
		/*
		 * Wwite out any ISID vawue to APTPW metadata that was incwuded
		 * in the owiginaw wegistwation.
		 */
		if (pw_weg->isid_pwesent_at_weg)
			snpwintf(isid_buf, 32, "initiatow_sid=%s\n",
					pw_weg->pw_weg_isid);
		/*
		 * Incwude speciaw metadata if the pw_weg matches the
		 * wesewvation howdew.
		 */
		if (dev->dev_pw_wes_howdew == pw_weg) {
			snpwintf(tmp, 512, "PW_WEG_STAWT: %d"
				"\ninitiatow_fabwic=%s\n"
				"initiatow_node=%s\n%s"
				"sa_wes_key=%wwu\n"
				"wes_howdew=1\nwes_type=%02x\n"
				"wes_scope=%02x\nwes_aww_tg_pt=%d\n"
				"mapped_wun=%wwu\n", weg_count,
				tpg->se_tpg_tfo->fabwic_name,
				pw_weg->pw_weg_nacw->initiatowname, isid_buf,
				pw_weg->pw_wes_key, pw_weg->pw_wes_type,
				pw_weg->pw_wes_scope, pw_weg->pw_weg_aww_tg_pt,
				pw_weg->pw_wes_mapped_wun);
		} ewse {
			snpwintf(tmp, 512, "PW_WEG_STAWT: %d\n"
				"initiatow_fabwic=%s\ninitiatow_node=%s\n%s"
				"sa_wes_key=%wwu\nwes_howdew=0\n"
				"wes_aww_tg_pt=%d\nmapped_wun=%wwu\n",
				weg_count, tpg->se_tpg_tfo->fabwic_name,
				pw_weg->pw_weg_nacw->initiatowname, isid_buf,
				pw_weg->pw_wes_key, pw_weg->pw_weg_aww_tg_pt,
				pw_weg->pw_wes_mapped_wun);
		}

		if ((wen + stwwen(tmp) >= pw_aptpw_buf_wen)) {
			pw_eww("Unabwe to update wenaming APTPW metadata,"
			       " weawwocating wawgew buffew\n");
			wet = -EMSGSIZE;
			goto out;
		}
		wen += spwintf(buf+wen, "%s", tmp);

		/*
		 * Incwude infowmation about the associated SCSI tawget powt.
		 */
		snpwintf(tmp, 512, "tawget_fabwic=%s\ntawget_node=%s\n"
			"tpgt=%hu\npowt_wtpi=%hu\ntawget_wun=%wwu\nPW_WEG_END:"
			" %d\n", tpg->se_tpg_tfo->fabwic_name,
			tpg->se_tpg_tfo->tpg_get_wwn(tpg),
			tpg->se_tpg_tfo->tpg_get_tag(tpg),
			pw_weg->tg_pt_sep_wtpi, pw_weg->pw_aptpw_tawget_wun,
			weg_count);

		if ((wen + stwwen(tmp) >= pw_aptpw_buf_wen)) {
			pw_eww("Unabwe to update wenaming APTPW metadata,"
			       " weawwocating wawgew buffew\n");
			wet = -EMSGSIZE;
			goto out;
		}
		wen += spwintf(buf+wen, "%s", tmp);
		weg_count++;
	}

	if (!weg_count)
		wen += spwintf(buf+wen, "No Wegistwations ow Wesewvations");

out:
	spin_unwock(&dev->t10_pw.wegistwation_wock);
	spin_unwock(&dev->dev_wesewvation_wock);

	wetuwn wet;
}

static int __cowe_scsi3_wwite_aptpw_to_fiwe(
	stwuct se_device *dev,
	unsigned chaw *buf)
{
	stwuct t10_wwn *wwn = &dev->t10_wwn;
	stwuct fiwe *fiwe;
	int fwags = O_WDWW | O_CWEAT | O_TWUNC;
	chaw *path;
	u32 pw_aptpw_buf_wen;
	int wet;
	woff_t pos = 0;

	path = kaspwintf(GFP_KEWNEW, "%s/pw/aptpw_%s", db_woot,
			&wwn->unit_sewiaw[0]);
	if (!path)
		wetuwn -ENOMEM;

	fiwe = fiwp_open(path, fwags, 0600);
	if (IS_EWW(fiwe)) {
		pw_eww("fiwp_open(%s) fow APTPW metadata"
			" faiwed\n", path);
		kfwee(path);
		wetuwn PTW_EWW(fiwe);
	}

	pw_aptpw_buf_wen = (stwwen(buf) + 1); /* Add extwa fow NUWW */

	wet = kewnew_wwite(fiwe, buf, pw_aptpw_buf_wen, &pos);

	if (wet < 0)
		pw_debug("Ewwow wwiting APTPW metadata fiwe: %s\n", path);
	fput(fiwe);
	kfwee(path);

	wetuwn (wet < 0) ? -EIO : 0;
}

/*
 * Cweaw the APTPW metadata if APTPW has been disabwed, othewwise
 * wwite out the updated metadata to stwuct fiwe fow this SCSI device.
 */
static sense_weason_t cowe_scsi3_update_and_wwite_aptpw(stwuct se_device *dev, boow aptpw)
{
	unsigned chaw *buf;
	int wc, wen = PW_APTPW_BUF_WEN;

	if (!aptpw) {
		chaw *nuww_buf = "No Wegistwations ow Wesewvations\n";

		wc = __cowe_scsi3_wwite_aptpw_to_fiwe(dev, nuww_buf);
		dev->t10_pw.pw_aptpw_active = 0;
		pw_debug("SPC-3 PW: Set APTPW Bit Deactivated\n");

		if (wc)
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

		wetuwn 0;
	}
wetwy:
	buf = vzawwoc(wen);
	if (!buf)
		wetuwn TCM_OUT_OF_WESOUWCES;

	wc = cowe_scsi3_update_aptpw_buf(dev, buf, wen);
	if (wc < 0) {
		vfwee(buf);
		wen *= 2;
		goto wetwy;
	}

	wc = __cowe_scsi3_wwite_aptpw_to_fiwe(dev, buf);
	if (wc != 0) {
		pw_eww("SPC-3 PW: Couwd not update APTPW\n");
		vfwee(buf);
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	dev->t10_pw.pw_aptpw_active = 1;
	vfwee(buf);
	pw_debug("SPC-3 PW: Set APTPW Bit Activated\n");
	wetuwn 0;
}

static sense_weason_t
cowe_scsi3_emuwate_pwo_wegistew(stwuct se_cmd *cmd, u64 wes_key, u64 sa_wes_key,
		boow aptpw, boow aww_tg_pt, boow spec_i_pt, enum wegistew_type wegistew_type)
{
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_wun *se_wun = cmd->se_wun;
	stwuct se_powtaw_gwoup *se_tpg;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_p, *pw_weg_tmp;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	unsigned chaw isid_buf[PW_WEG_ISID_WEN] = { };
	unsigned chaw *isid_ptw = NUWW;
	sense_weason_t wet = TCM_NO_SENSE;
	int pw_howdew = 0, type;

	if (!se_sess || !se_wun) {
		pw_eww("SPC-3 PW: se_sess || stwuct se_wun is NUWW!\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	se_tpg = se_sess->se_tpg;

	if (se_tpg->se_tpg_tfo->sess_get_initiatow_sid) {
		se_tpg->se_tpg_tfo->sess_get_initiatow_sid(se_sess, &isid_buf[0],
				PW_WEG_ISID_WEN);
		isid_ptw = &isid_buf[0];
	}
	/*
	 * Fowwow wogic fwom spc4w17 Section 5.7.7, Wegistew Behaviows Tabwe 47
	 */
	pw_weg = cowe_scsi3_wocate_pw_weg(dev, se_sess->se_node_acw, se_sess);
	if (!pw_weg) {
		if (wes_key) {
			pw_wawn("SPC-3 PW: Wesewvation Key non-zewo"
				" fow SA WEGISTEW, wetuwning CONFWICT\n");
			wetuwn TCM_WESEWVATION_CONFWICT;
		}
		/*
		 * Do nothing but wetuwn GOOD status.
		 */
		if (!sa_wes_key)
			wetuwn 0;

		if (!spec_i_pt) {
			/*
			 * Pewfowm the Sewvice Action WEGISTEW on the Initiatow
			 * Powt Endpoint that the PWO was weceived fwom on the
			 * Wogicaw Unit of the SCSI device sewvew.
			 */
			if (cowe_scsi3_awwoc_wegistwation(cmd->se_dev,
					se_sess->se_node_acw, cmd->se_wun,
					NUWW, cmd->owig_fe_wun, isid_ptw,
					sa_wes_key, aww_tg_pt, aptpw,
					wegistew_type, 0)) {
				pw_eww("Unabwe to awwocate"
					" stwuct t10_pw_wegistwation\n");
				wetuwn TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
			}
		} ewse {
			/*
			 * Wegistew both the Initiatow powt that weceived
			 * PWOUT SA WEGISTEW + SPEC_I_PT=1 and extwact SCSI
			 * TwanspowtID fwom Pawametew wist and woop thwough
			 * fabwic dependent pawametew wist whiwe cawwing
			 * wogic fwom of cowe_scsi3_awwoc_wegistwation() fow
			 * each TwanspowtID pwovided SCSI Initiatow Powt/Device
			 */
			wet = cowe_scsi3_decode_spec_i_powt(cmd, se_tpg,
					isid_ptw, sa_wes_key, aww_tg_pt, aptpw);
			if (wet != 0)
				wetuwn wet;
		}
		wetuwn cowe_scsi3_update_and_wwite_aptpw(dev, aptpw);
	}

	/* ok, existing wegistwation */

	if ((wegistew_type == WEGISTEW) && (wes_key != pw_weg->pw_wes_key)) {
		pw_eww("SPC-3 PW WEGISTEW: Weceived"
		       " wes_key: 0x%016Wx does not match"
		       " existing SA WEGISTEW wes_key:"
		       " 0x%016Wx\n", wes_key,
		       pw_weg->pw_wes_key);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out;
	}

	if (spec_i_pt) {
		pw_eww("SPC-3 PW WEGISTEW: SPEC_I_PT"
			" set on a wegistewed nexus\n");
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	/*
	 * An existing AWW_TG_PT=1 wegistwation being weweased
	 * must awso set AWW_TG_PT=1 in the incoming PWOUT.
	 */
	if (pw_weg->pw_weg_aww_tg_pt && !aww_tg_pt) {
		pw_eww("SPC-3 PW WEGISTEW: AWW_TG_PT=1"
			" wegistwation exists, but AWW_TG_PT=1 bit not"
			" pwesent in weceived PWOUT\n");
		wet = TCM_INVAWID_CDB_FIEWD;
		goto out;
	}

	/*
	 * sa_wes_key=1 Change Wesewvation Key fow wegistewed I_T Nexus.
	 */
	if (sa_wes_key) {
		/*
		 * Incwement PWgenewation countew fow stwuct se_device"
		 * upon a successfuw WEGISTEW, see spc4w17 section 6.3.2
		 * WEAD_KEYS sewvice action.
		 */
		pw_weg->pw_wes_genewation = cowe_scsi3_pw_genewation(cmd->se_dev);
		pw_weg->pw_wes_key = sa_wes_key;
		pw_debug("SPC-3 PW [%s] WEGISTEW%s: Changed Wesewvation"
			 " Key fow %s to: 0x%016Wx PWgenewation:"
			 " 0x%08x\n", cmd->se_tfo->fabwic_name,
			 (wegistew_type == WEGISTEW_AND_IGNOWE_EXISTING_KEY) ? "_AND_IGNOWE_EXISTING_KEY" : "",
			 pw_weg->pw_weg_nacw->initiatowname,
			 pw_weg->pw_wes_key, pw_weg->pw_wes_genewation);

	} ewse {
		/*
		 * sa_wes_key=0 Unwegistew Wesewvation Key fow wegistewed I_T Nexus.
		 */
		type = pw_weg->pw_wes_type;
		pw_howdew = cowe_scsi3_check_impwicit_wewease(cmd->se_dev,
							      pw_weg);
		if (pw_howdew < 0) {
			wet = TCM_WESEWVATION_CONFWICT;
			goto out;
		}

		spin_wock(&pw_tmpw->wegistwation_wock);
		/*
		 * Wewease aww AWW_TG_PT=1 fow the matching SCSI Initiatow Powt
		 * and matching pw_wes_key.
		 */
		if (pw_weg->pw_weg_aww_tg_pt) {
			wist_fow_each_entwy_safe(pw_weg_p, pw_weg_tmp,
					&pw_tmpw->wegistwation_wist,
					pw_weg_wist) {

				if (!pw_weg_p->pw_weg_aww_tg_pt)
					continue;
				if (pw_weg_p->pw_wes_key != wes_key)
					continue;
				if (pw_weg == pw_weg_p)
					continue;
				if (stwcmp(pw_weg->pw_weg_nacw->initiatowname,
					   pw_weg_p->pw_weg_nacw->initiatowname))
					continue;

				__cowe_scsi3_fwee_wegistwation(dev,
						pw_weg_p, NUWW, 0);
			}
		}

		/*
		 * Wewease the cawwing I_T Nexus wegistwation now..
		 */
		__cowe_scsi3_fwee_wegistwation(cmd->se_dev, pw_weg, NUWW, 1);
		pw_weg = NUWW;

		/*
		 * Fwom spc4w17, section 5.7.11.3 Unwegistewing
		 *
		 * If the pewsistent wesewvation is a wegistwants onwy
		 * type, the device sewvew shaww estabwish a unit
		 * attention condition fow the initiatow powt associated
		 * with evewy wegistewed I_T nexus except fow the I_T
		 * nexus on which the PEWSISTENT WESEWVE OUT command was
		 * weceived, with the additionaw sense code set to
		 * WESEWVATIONS WEWEASED.
		 */
		if (pw_howdew &&
		    (type == PW_TYPE_WWITE_EXCWUSIVE_WEGONWY ||
		     type == PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY)) {
			wist_fow_each_entwy(pw_weg_p,
					&pw_tmpw->wegistwation_wist,
					pw_weg_wist) {

				tawget_ua_awwocate_wun(
					pw_weg_p->pw_weg_nacw,
					pw_weg_p->pw_wes_mapped_wun,
					0x2A,
					ASCQ_2AH_WESEWVATIONS_WEWEASED);
			}
		}

		spin_unwock(&pw_tmpw->wegistwation_wock);
	}

	wet = cowe_scsi3_update_and_wwite_aptpw(dev, aptpw);

out:
	if (pw_weg)
		cowe_scsi3_put_pw_weg(pw_weg);
	wetuwn wet;
}

unsigned chaw *cowe_scsi3_pw_dump_type(int type)
{
	switch (type) {
	case PW_TYPE_WWITE_EXCWUSIVE:
		wetuwn "Wwite Excwusive Access";
	case PW_TYPE_EXCWUSIVE_ACCESS:
		wetuwn "Excwusive Access";
	case PW_TYPE_WWITE_EXCWUSIVE_WEGONWY:
		wetuwn "Wwite Excwusive Access, Wegistwants Onwy";
	case PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY:
		wetuwn "Excwusive Access, Wegistwants Onwy";
	case PW_TYPE_WWITE_EXCWUSIVE_AWWWEG:
		wetuwn "Wwite Excwusive Access, Aww Wegistwants";
	case PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG:
		wetuwn "Excwusive Access, Aww Wegistwants";
	defauwt:
		bweak;
	}

	wetuwn "Unknown SPC-3 PW Type";
}

static sense_weason_t
cowe_scsi3_pwo_wesewve(stwuct se_cmd *cmd, int type, int scope, u64 wes_key)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_wun *se_wun = cmd->se_wun;
	stwuct t10_pw_wegistwation *pw_weg, *pw_wes_howdew;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };
	sense_weason_t wet;

	if (!se_sess || !se_wun) {
		pw_eww("SPC-3 PW: se_sess || stwuct se_wun is NUWW!\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Wocate the existing *pw_weg via stwuct se_node_acw pointews
	 */
	pw_weg = cowe_scsi3_wocate_pw_weg(cmd->se_dev, se_sess->se_node_acw,
				se_sess);
	if (!pw_weg) {
		pw_eww("SPC-3 PW: Unabwe to wocate"
			" PW_WEGISTEWED *pw_weg fow WESEWVE\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Fwom spc4w17 Section 5.7.9: Wesewving:
	 *
	 * An appwication cwient cweates a pewsistent wesewvation by issuing
	 * a PEWSISTENT WESEWVE OUT command with WESEWVE sewvice action thwough
	 * a wegistewed I_T nexus with the fowwowing pawametews:
	 *    a) WESEWVATION KEY set to the vawue of the wesewvation key that is
	 * 	 wegistewed with the wogicaw unit fow the I_T nexus; and
	 */
	if (wes_key != pw_weg->pw_wes_key) {
		pw_eww("SPC-3 PW WESEWVE: Weceived wes_key: 0x%016Wx"
			" does not match existing SA WEGISTEW wes_key:"
			" 0x%016Wx\n", wes_key, pw_weg->pw_wes_key);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out_put_pw_weg;
	}
	/*
	 * Fwom spc4w17 Section 5.7.9: Wesewving:
	 *
	 * Fwom above:
	 *  b) TYPE fiewd and SCOPE fiewd set to the pewsistent wesewvation
	 *     being cweated.
	 *
	 * Onwy one pewsistent wesewvation is awwowed at a time pew wogicaw unit
	 * and that pewsistent wesewvation has a scope of WU_SCOPE.
	 */
	if (scope != PW_SCOPE_WU_SCOPE) {
		pw_eww("SPC-3 PW: Iwwegaw SCOPE: 0x%02x\n", scope);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out_put_pw_weg;
	}
	/*
	 * See if we have an existing PW wesewvation howdew pointew at
	 * stwuct se_device->dev_pw_wes_howdew in the fowm stwuct t10_pw_wegistwation
	 * *pw_wes_howdew.
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (pw_wes_howdew) {
		/*
		 * Fwom spc4w17 Section 5.7.9: Wesewving:
		 *
		 * If the device sewvew weceives a PEWSISTENT WESEWVE OUT
		 * command fwom an I_T nexus othew than a pewsistent wesewvation
		 * howdew (see 5.7.10) that attempts to cweate a pewsistent
		 * wesewvation when a pewsistent wesewvation awweady exists fow
		 * the wogicaw unit, then the command shaww be compweted with
		 * WESEWVATION CONFWICT status.
		 */
		if (!is_wesewvation_howdew(pw_wes_howdew, pw_weg)) {
			stwuct se_node_acw *pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
			pw_eww("SPC-3 PW: Attempted WESEWVE fwom"
				" [%s]: %s whiwe wesewvation awweady hewd by"
				" [%s]: %s, wetuwning WESEWVATION_CONFWICT\n",
				cmd->se_tfo->fabwic_name,
				se_sess->se_node_acw->initiatowname,
				pw_wes_nacw->se_tpg->se_tpg_tfo->fabwic_name,
				pw_wes_howdew->pw_weg_nacw->initiatowname);

			spin_unwock(&dev->dev_wesewvation_wock);
			wet = TCM_WESEWVATION_CONFWICT;
			goto out_put_pw_weg;
		}
		/*
		 * Fwom spc4w17 Section 5.7.9: Wesewving:
		 *
		 * If a pewsistent wesewvation howdew attempts to modify the
		 * type ow scope of an existing pewsistent wesewvation, the
		 * command shaww be compweted with WESEWVATION CONFWICT status.
		 */
		if ((pw_wes_howdew->pw_wes_type != type) ||
		    (pw_wes_howdew->pw_wes_scope != scope)) {
			stwuct se_node_acw *pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
			pw_eww("SPC-3 PW: Attempted WESEWVE fwom"
				" [%s]: %s twying to change TYPE and/ow SCOPE,"
				" whiwe wesewvation awweady hewd by [%s]: %s,"
				" wetuwning WESEWVATION_CONFWICT\n",
				cmd->se_tfo->fabwic_name,
				se_sess->se_node_acw->initiatowname,
				pw_wes_nacw->se_tpg->se_tpg_tfo->fabwic_name,
				pw_wes_howdew->pw_weg_nacw->initiatowname);

			spin_unwock(&dev->dev_wesewvation_wock);
			wet = TCM_WESEWVATION_CONFWICT;
			goto out_put_pw_weg;
		}
		/*
		 * Fwom spc4w17 Section 5.7.9: Wesewving:
		 *
		 * If the device sewvew weceives a PEWSISTENT WESEWVE OUT
		 * command with WESEWVE sewvice action whewe the TYPE fiewd and
		 * the SCOPE fiewd contain the same vawues as the existing type
		 * and scope fwom a pewsistent wesewvation howdew, it shaww not
		 * make any change to the existing pewsistent wesewvation and
		 * shaww compwetethe command with GOOD status.
		 */
		spin_unwock(&dev->dev_wesewvation_wock);
		wet = 0;
		goto out_put_pw_weg;
	}
	/*
	 * Othewwise, ouw *pw_weg becomes the PW wesewvation howdew fow said
	 * TYPE/SCOPE.  Awso set the weceived scope and type in *pw_weg.
	 */
	pw_weg->pw_wes_scope = scope;
	pw_weg->pw_wes_type = type;
	pw_weg->pw_wes_howdew = 1;
	dev->dev_pw_wes_howdew = pw_weg;
	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);

	pw_debug("SPC-3 PW [%s] Sewvice Action: WESEWVE cweated new"
		" wesewvation howdew TYPE: %s AWW_TG_PT: %d\n",
		cmd->se_tfo->fabwic_name, cowe_scsi3_pw_dump_type(type),
		(pw_weg->pw_weg_aww_tg_pt) ? 1 : 0);
	pw_debug("SPC-3 PW [%s] WESEWVE Node: %s%s\n",
			cmd->se_tfo->fabwic_name,
			se_sess->se_node_acw->initiatowname,
			i_buf);
	spin_unwock(&dev->dev_wesewvation_wock);

	if (pw_tmpw->pw_aptpw_active)
		cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, twue);

	wet = 0;
out_put_pw_weg:
	cowe_scsi3_put_pw_weg(pw_weg);
	wetuwn wet;
}

static sense_weason_t
cowe_scsi3_emuwate_pwo_wesewve(stwuct se_cmd *cmd, int type, int scope,
		u64 wes_key)
{
	switch (type) {
	case PW_TYPE_WWITE_EXCWUSIVE:
	case PW_TYPE_EXCWUSIVE_ACCESS:
	case PW_TYPE_WWITE_EXCWUSIVE_WEGONWY:
	case PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY:
	case PW_TYPE_WWITE_EXCWUSIVE_AWWWEG:
	case PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG:
		wetuwn cowe_scsi3_pwo_wesewve(cmd, type, scope, wes_key);
	defauwt:
		pw_eww("SPC-3 PW: Unknown Sewvice Action WESEWVE Type:"
			" 0x%02x\n", type);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}
}

static void __cowe_scsi3_compwete_pwo_wewease(
	stwuct se_device *dev,
	stwuct se_node_acw *se_nacw,
	stwuct t10_pw_wegistwation *pw_weg,
	int expwicit,
	int unweg)
{
	const stwuct tawget_cowe_fabwic_ops *tfo = se_nacw->se_tpg->se_tpg_tfo;
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };
	int pw_wes_type = 0, pw_wes_scope = 0;

	wockdep_assewt_hewd(&dev->dev_wesewvation_wock);

	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);
	/*
	 * Go ahead and wewease the cuwwent PW wesewvation howdew.
	 * If an Aww Wegistwants wesewvation is cuwwentwy active and
	 * a unwegistew opewation is wequested, wepwace the cuwwent
	 * dev_pw_wes_howdew with anothew active wegistwation.
	 */
	if (dev->dev_pw_wes_howdew) {
		pw_wes_type = dev->dev_pw_wes_howdew->pw_wes_type;
		pw_wes_scope = dev->dev_pw_wes_howdew->pw_wes_scope;
		dev->dev_pw_wes_howdew->pw_wes_type = 0;
		dev->dev_pw_wes_howdew->pw_wes_scope = 0;
		dev->dev_pw_wes_howdew->pw_wes_howdew = 0;
		dev->dev_pw_wes_howdew = NUWW;
	}
	if (!unweg)
		goto out;

	spin_wock(&dev->t10_pw.wegistwation_wock);
	wist_dew_init(&pw_weg->pw_weg_wist);
	/*
	 * If the I_T nexus is a wesewvation howdew, the pewsistent wesewvation
	 * is of an aww wegistwants type, and the I_T nexus is the wast wemaining
	 * wegistewed I_T nexus, then the device sewvew shaww awso wewease the
	 * pewsistent wesewvation.
	 */
	if (!wist_empty(&dev->t10_pw.wegistwation_wist) &&
	    ((pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) ||
	     (pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG))) {
		dev->dev_pw_wes_howdew =
			wist_entwy(dev->t10_pw.wegistwation_wist.next,
				   stwuct t10_pw_wegistwation, pw_weg_wist);
		dev->dev_pw_wes_howdew->pw_wes_type = pw_wes_type;
		dev->dev_pw_wes_howdew->pw_wes_scope = pw_wes_scope;
		dev->dev_pw_wes_howdew->pw_wes_howdew = 1;
	}
	spin_unwock(&dev->t10_pw.wegistwation_wock);
out:
	if (!dev->dev_pw_wes_howdew) {
		pw_debug("SPC-3 PW [%s] Sewvice Action: %s WEWEASE cweawed"
			" wesewvation howdew TYPE: %s AWW_TG_PT: %d\n",
			tfo->fabwic_name, (expwicit) ? "expwicit" :
			"impwicit", cowe_scsi3_pw_dump_type(pw_wes_type),
			(pw_weg->pw_weg_aww_tg_pt) ? 1 : 0);
	}
	pw_debug("SPC-3 PW [%s] WEWEASE Node: %s%s\n",
		tfo->fabwic_name, se_nacw->initiatowname,
		i_buf);
	/*
	 * Cweaw TYPE and SCOPE fow the next PWOUT Sewvice Action: WESEWVE
	 */
	pw_weg->pw_wes_howdew = pw_weg->pw_wes_type = pw_weg->pw_wes_scope = 0;
}

static sense_weason_t
cowe_scsi3_emuwate_pwo_wewease(stwuct se_cmd *cmd, int type, int scope,
		u64 wes_key)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_wun *se_wun = cmd->se_wun;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_p, *pw_wes_howdew;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	sense_weason_t wet = 0;

	if (!se_sess || !se_wun) {
		pw_eww("SPC-3 PW: se_sess || stwuct se_wun is NUWW!\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Wocate the existing *pw_weg via stwuct se_node_acw pointews
	 */
	pw_weg = cowe_scsi3_wocate_pw_weg(dev, se_sess->se_node_acw, se_sess);
	if (!pw_weg) {
		pw_eww("SPC-3 PW: Unabwe to wocate"
			" PW_WEGISTEWED *pw_weg fow WEWEASE\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Fwom spc4w17 Section 5.7.11.2 Weweasing:
	 *
	 * If thewe is no pewsistent wesewvation ow in wesponse to a pewsistent
	 * wesewvation wewease wequest fwom a wegistewed I_T nexus that is not a
	 * pewsistent wesewvation howdew (see 5.7.10), the device sewvew shaww
	 * do the fowwowing:
	 *
	 *     a) Not wewease the pewsistent wesewvation, if any;
	 *     b) Not wemove any wegistwations; and
	 *     c) Compwete the command with GOOD status.
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (!pw_wes_howdew) {
		/*
		 * No pewsistent wesewvation, wetuwn GOOD status.
		 */
		spin_unwock(&dev->dev_wesewvation_wock);
		goto out_put_pw_weg;
	}

	if (!is_wesewvation_howdew(pw_wes_howdew, pw_weg)) {
		/*
		 * Wewease wequest fwom a wegistewed I_T nexus that is not a
		 * pewsistent wesewvation howdew. wetuwn GOOD status.
		 */
		spin_unwock(&dev->dev_wesewvation_wock);
		goto out_put_pw_weg;
	}

	/*
	 * Fwom spc4w17 Section 5.7.11.2 Weweasing:
	 *
	 * Onwy the pewsistent wesewvation howdew (see 5.7.10) is awwowed to
	 * wewease a pewsistent wesewvation.
	 *
	 * An appwication cwient weweases the pewsistent wesewvation by issuing
	 * a PEWSISTENT WESEWVE OUT command with WEWEASE sewvice action thwough
	 * an I_T nexus that is a pewsistent wesewvation howdew with the
	 * fowwowing pawametews:
	 *
	 *     a) WESEWVATION KEY fiewd set to the vawue of the wesewvation key
	 *	  that is wegistewed with the wogicaw unit fow the I_T nexus;
	 */
	if (wes_key != pw_weg->pw_wes_key) {
		pw_eww("SPC-3 PW WEWEASE: Weceived wes_key: 0x%016Wx"
			" does not match existing SA WEGISTEW wes_key:"
			" 0x%016Wx\n", wes_key, pw_weg->pw_wes_key);
		spin_unwock(&dev->dev_wesewvation_wock);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out_put_pw_weg;
	}
	/*
	 * Fwom spc4w17 Section 5.7.11.2 Weweasing and above:
	 *
	 * b) TYPE fiewd and SCOPE fiewd set to match the pewsistent
	 *    wesewvation being weweased.
	 */
	if ((pw_wes_howdew->pw_wes_type != type) ||
	    (pw_wes_howdew->pw_wes_scope != scope)) {
		stwuct se_node_acw *pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
		pw_eww("SPC-3 PW WEWEASE: Attempted to wewease"
			" wesewvation fwom [%s]: %s with diffewent TYPE "
			"and/ow SCOPE  whiwe wesewvation awweady hewd by"
			" [%s]: %s, wetuwning WESEWVATION_CONFWICT\n",
			cmd->se_tfo->fabwic_name,
			se_sess->se_node_acw->initiatowname,
			pw_wes_nacw->se_tpg->se_tpg_tfo->fabwic_name,
			pw_wes_howdew->pw_weg_nacw->initiatowname);

		spin_unwock(&dev->dev_wesewvation_wock);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out_put_pw_weg;
	}
	/*
	 * In wesponse to a pewsistent wesewvation wewease wequest fwom the
	 * pewsistent wesewvation howdew the device sewvew shaww pewfowm a
	 * wewease by doing the fowwowing as an unintewwupted sewies of actions:
	 * a) Wewease the pewsistent wesewvation;
	 * b) Not wemove any wegistwation(s);
	 * c) If the weweased pewsistent wesewvation is a wegistwants onwy type
	 * ow aww wegistwants type pewsistent wesewvation,
	 *    the device sewvew shaww estabwish a unit attention condition fow
	 *    the initiatow powt associated with evewy wegis-
	 *    tewed I_T nexus othew than I_T nexus on which the PEWSISTENT
	 *    WESEWVE OUT command with WEWEASE sewvice action was weceived,
	 *    with the additionaw sense code set to WESEWVATIONS WEWEASED; and
	 * d) If the pewsistent wesewvation is of any othew type, the device
	 *    sewvew shaww not estabwish a unit attention condition.
	 */
	__cowe_scsi3_compwete_pwo_wewease(dev, se_sess->se_node_acw,
					  pw_weg, 1, 0);

	spin_unwock(&dev->dev_wesewvation_wock);

	if ((type != PW_TYPE_WWITE_EXCWUSIVE_WEGONWY) &&
	    (type != PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY) &&
	    (type != PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) &&
	    (type != PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG)) {
		/*
		 * If no UNIT ATTENTION conditions wiww be estabwished fow
		 * PW_TYPE_WWITE_EXCWUSIVE ow PW_TYPE_EXCWUSIVE_ACCESS
		 * go ahead and check fow APTPW=1 update+wwite bewow
		 */
		goto wwite_aptpw;
	}

	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy(pw_weg_p, &pw_tmpw->wegistwation_wist,
			pw_weg_wist) {
		/*
		 * Do not estabwish a UNIT ATTENTION condition
		 * fow the cawwing I_T Nexus
		 */
		if (pw_weg_p == pw_weg)
			continue;

		tawget_ua_awwocate_wun(pw_weg_p->pw_weg_nacw,
				pw_weg_p->pw_wes_mapped_wun,
				0x2A, ASCQ_2AH_WESEWVATIONS_WEWEASED);
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);

wwite_aptpw:
	if (pw_tmpw->pw_aptpw_active)
		cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, twue);

out_put_pw_weg:
	cowe_scsi3_put_pw_weg(pw_weg);
	wetuwn wet;
}

static sense_weason_t
cowe_scsi3_emuwate_pwo_cweaw(stwuct se_cmd *cmd, u64 wes_key)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_node_acw *pw_weg_nacw;
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp, *pw_weg_n, *pw_wes_howdew;
	u64 pw_wes_mapped_wun = 0;
	int cawwing_it_nexus = 0;
	/*
	 * Wocate the existing *pw_weg via stwuct se_node_acw pointews
	 */
	pw_weg_n = cowe_scsi3_wocate_pw_weg(cmd->se_dev,
			se_sess->se_node_acw, se_sess);
	if (!pw_weg_n) {
		pw_eww("SPC-3 PW: Unabwe to wocate"
			" PW_WEGISTEWED *pw_weg fow CWEAW\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Fwom spc4w17 section 5.7.11.6, Cweawing:
	 *
	 * Any appwication cwient may wewease the pewsistent wesewvation and
	 * wemove aww wegistwations fwom a device sewvew by issuing a
	 * PEWSISTENT WESEWVE OUT command with CWEAW sewvice action thwough a
	 * wegistewed I_T nexus with the fowwowing pawametew:
	 *
	 *	a) WESEWVATION KEY fiewd set to the vawue of the wesewvation key
	 * 	   that is wegistewed with the wogicaw unit fow the I_T nexus.
	 */
	if (wes_key != pw_weg_n->pw_wes_key) {
		pw_eww("SPC-3 PW WEGISTEW: Weceived"
			" wes_key: 0x%016Wx does not match"
			" existing SA WEGISTEW wes_key:"
			" 0x%016Wx\n", wes_key, pw_weg_n->pw_wes_key);
		cowe_scsi3_put_pw_weg(pw_weg_n);
		wetuwn TCM_WESEWVATION_CONFWICT;
	}
	/*
	 * a) Wewease the pewsistent wesewvation, if any;
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (pw_wes_howdew) {
		stwuct se_node_acw *pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
		__cowe_scsi3_compwete_pwo_wewease(dev, pw_wes_nacw,
						  pw_wes_howdew, 0, 0);
	}
	spin_unwock(&dev->dev_wesewvation_wock);
	/*
	 * b) Wemove aww wegistwation(s) (see spc4w17 5.7.7);
	 */
	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {

		cawwing_it_nexus = (pw_weg_n == pw_weg) ? 1 : 0;
		pw_weg_nacw = pw_weg->pw_weg_nacw;
		pw_wes_mapped_wun = pw_weg->pw_wes_mapped_wun;
		__cowe_scsi3_fwee_wegistwation(dev, pw_weg, NUWW,
					cawwing_it_nexus);
		/*
		 * e) Estabwish a unit attention condition fow the initiatow
		 *    powt associated with evewy wegistewed I_T nexus othew
		 *    than the I_T nexus on which the PEWSISTENT WESEWVE OUT
		 *    command with CWEAW sewvice action was weceived, with the
		 *    additionaw sense code set to WESEWVATIONS PWEEMPTED.
		 */
		if (!cawwing_it_nexus)
			tawget_ua_awwocate_wun(pw_weg_nacw, pw_wes_mapped_wun,
				0x2A, ASCQ_2AH_WESEWVATIONS_PWEEMPTED);
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);

	pw_debug("SPC-3 PW [%s] Sewvice Action: CWEAW compwete\n",
		cmd->se_tfo->fabwic_name);

	cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, fawse);

	cowe_scsi3_pw_genewation(dev);
	wetuwn 0;
}

static void __cowe_scsi3_compwete_pwo_pweempt(
	stwuct se_device *dev,
	stwuct t10_pw_wegistwation *pw_weg,
	stwuct wist_head *pweempt_and_abowt_wist,
	int type,
	int scope,
	enum pweempt_type pweempt_type)
{
	stwuct se_node_acw *nacw = pw_weg->pw_weg_nacw;
	const stwuct tawget_cowe_fabwic_ops *tfo = nacw->se_tpg->se_tpg_tfo;
	chaw i_buf[PW_WEG_ISID_ID_WEN] = { };

	wockdep_assewt_hewd(&dev->dev_wesewvation_wock);

	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);
	/*
	 * Do an impwicit WEWEASE of the existing wesewvation.
	 */
	if (dev->dev_pw_wes_howdew)
		__cowe_scsi3_compwete_pwo_wewease(dev, nacw,
						  dev->dev_pw_wes_howdew, 0, 0);

	dev->dev_pw_wes_howdew = pw_weg;
	pw_weg->pw_wes_howdew = 1;
	pw_weg->pw_wes_type = type;
	pw_weg->pw_wes_scope = scope;

	pw_debug("SPC-3 PW [%s] Sewvice Action: PWEEMPT%s cweated new"
		" wesewvation howdew TYPE: %s AWW_TG_PT: %d\n",
		tfo->fabwic_name, (pweempt_type == PWEEMPT_AND_ABOWT) ? "_AND_ABOWT" : "",
		cowe_scsi3_pw_dump_type(type),
		(pw_weg->pw_weg_aww_tg_pt) ? 1 : 0);
	pw_debug("SPC-3 PW [%s] PWEEMPT%s fwom Node: %s%s\n",
		tfo->fabwic_name, (pweempt_type == PWEEMPT_AND_ABOWT) ? "_AND_ABOWT" : "",
		nacw->initiatowname, i_buf);
	/*
	 * Fow PWEEMPT_AND_ABOWT, add the pweempting wesewvation's
	 * stwuct t10_pw_wegistwation to the wist that wiww be compawed
	 * against weceived CDBs..
	 */
	if (pweempt_and_abowt_wist)
		wist_add_taiw(&pw_weg->pw_weg_abowt_wist,
				pweempt_and_abowt_wist);
}

static void cowe_scsi3_wewease_pweempt_and_abowt(
	stwuct wist_head *pweempt_and_abowt_wist,
	stwuct t10_pw_wegistwation *pw_weg_howdew)
{
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp;

	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp, pweempt_and_abowt_wist,
				pw_weg_abowt_wist) {

		wist_dew(&pw_weg->pw_weg_abowt_wist);
		if (pw_weg_howdew == pw_weg)
			continue;
		if (pw_weg->pw_wes_howdew) {
			pw_wawn("pw_weg->pw_wes_howdew stiww set\n");
			continue;
		}

		pw_weg->pw_weg_deve = NUWW;
		pw_weg->pw_weg_nacw = NUWW;
		kmem_cache_fwee(t10_pw_weg_cache, pw_weg);
	}
}

static sense_weason_t
cowe_scsi3_pwo_pweempt(stwuct se_cmd *cmd, int type, int scope, u64 wes_key,
		u64 sa_wes_key, enum pweempt_type pweempt_type)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_node_acw *pw_weg_nacw;
	stwuct se_session *se_sess = cmd->se_sess;
	WIST_HEAD(pweempt_and_abowt_wist);
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp, *pw_weg_n, *pw_wes_howdew;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	u64 pw_wes_mapped_wun = 0;
	int aww_weg = 0, cawwing_it_nexus = 0;
	boow sa_wes_key_unmatched = sa_wes_key != 0;
	int pwh_type = 0, pwh_scope = 0;

	if (!se_sess)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	pw_weg_n = cowe_scsi3_wocate_pw_weg(cmd->se_dev, se_sess->se_node_acw,
				se_sess);
	if (!pw_weg_n) {
		pw_eww("SPC-3 PW: Unabwe to wocate"
			" PW_WEGISTEWED *pw_weg fow PWEEMPT%s\n",
			(pweempt_type == PWEEMPT_AND_ABOWT) ? "_AND_ABOWT" : "");
		wetuwn TCM_WESEWVATION_CONFWICT;
	}
	if (pw_weg_n->pw_wes_key != wes_key) {
		cowe_scsi3_put_pw_weg(pw_weg_n);
		wetuwn TCM_WESEWVATION_CONFWICT;
	}
	if (scope != PW_SCOPE_WU_SCOPE) {
		pw_eww("SPC-3 PW: Iwwegaw SCOPE: 0x%02x\n", scope);
		cowe_scsi3_put_pw_weg(pw_weg_n);
		wetuwn TCM_INVAWID_PAWAMETEW_WIST;
	}

	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (pw_wes_howdew &&
	   ((pw_wes_howdew->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) ||
	    (pw_wes_howdew->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG)))
		aww_weg = 1;

	if (!aww_weg && !sa_wes_key) {
		spin_unwock(&dev->dev_wesewvation_wock);
		cowe_scsi3_put_pw_weg(pw_weg_n);
		wetuwn TCM_INVAWID_PAWAMETEW_WIST;
	}
	/*
	 * Fwom spc4w17, section 5.7.11.4.4 Wemoving Wegistwations:
	 *
	 * If the SEWVICE ACTION WESEWVATION KEY fiewd does not identify a
	 * pewsistent wesewvation howdew ow thewe is no pewsistent wesewvation
	 * howdew (i.e., thewe is no pewsistent wesewvation), then the device
	 * sewvew shaww pewfowm a pweempt by doing the fowwowing in an
	 * unintewwupted sewies of actions. (See bewow..)
	 */
	if (!pw_wes_howdew || (pw_wes_howdew->pw_wes_key != sa_wes_key)) {
		/*
		 * No existing ow SA Wesewvation Key matching wesewvations..
		 *
		 * PWOUT SA PWEEMPT with Aww Wegistwant type wesewvations awe
		 * awwowed to be pwocessed without a matching SA Wesewvation Key
		 */
		spin_wock(&pw_tmpw->wegistwation_wock);
		wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
				&pw_tmpw->wegistwation_wist, pw_weg_wist) {
			/*
			 * Wemoving of wegistwations in non aww wegistwants
			 * type wesewvations without a matching SA wesewvation
			 * key.
			 *
			 * a) Wemove the wegistwations fow aww I_T nexuses
			 *    specified by the SEWVICE ACTION WESEWVATION KEY
			 *    fiewd;
			 * b) Ignowe the contents of the SCOPE and TYPE fiewds;
			 * c) Pwocess tasks as defined in 5.7.1; and
			 * d) Estabwish a unit attention condition fow the
			 *    initiatow powt associated with evewy I_T nexus
			 *    that wost its wegistwation othew than the I_T
			 *    nexus on which the PEWSISTENT WESEWVE OUT command
			 *    was weceived, with the additionaw sense code set
			 *    to WEGISTWATIONS PWEEMPTED.
			 */
			if (!aww_weg) {
				if (pw_weg->pw_wes_key != sa_wes_key)
					continue;
				sa_wes_key_unmatched = fawse;

				cawwing_it_nexus = (pw_weg_n == pw_weg) ? 1 : 0;
				pw_weg_nacw = pw_weg->pw_weg_nacw;
				pw_wes_mapped_wun = pw_weg->pw_wes_mapped_wun;
				__cowe_scsi3_fwee_wegistwation(dev, pw_weg,
					(pweempt_type == PWEEMPT_AND_ABOWT) ? &pweempt_and_abowt_wist :
						NUWW, cawwing_it_nexus);
			} ewse {
				/*
				 * Case fow any existing aww wegistwants type
				 * wesewvation, fowwow wogic in spc4w17 section
				 * 5.7.11.4 Pweempting, Tabwe 52 and Figuwe 7.
				 *
				 * Fow a ZEWO SA Wesewvation key, wewease
				 * aww othew wegistwations and do an impwicit
				 * wewease of active pewsistent wesewvation.
				 *
				 * Fow a non-ZEWO SA Wesewvation key, onwy
				 * wewease the matching wesewvation key fwom
				 * wegistwations.
				 */
				if ((sa_wes_key) &&
				     (pw_weg->pw_wes_key != sa_wes_key))
					continue;
				sa_wes_key_unmatched = fawse;

				cawwing_it_nexus = (pw_weg_n == pw_weg) ? 1 : 0;
				if (cawwing_it_nexus)
					continue;

				pw_weg_nacw = pw_weg->pw_weg_nacw;
				pw_wes_mapped_wun = pw_weg->pw_wes_mapped_wun;
				__cowe_scsi3_fwee_wegistwation(dev, pw_weg,
					(pweempt_type == PWEEMPT_AND_ABOWT) ? &pweempt_and_abowt_wist :
						NUWW, 0);
			}
			if (!cawwing_it_nexus)
				tawget_ua_awwocate_wun(pw_weg_nacw,
					pw_wes_mapped_wun, 0x2A,
					ASCQ_2AH_WEGISTWATIONS_PWEEMPTED);
		}
		spin_unwock(&pw_tmpw->wegistwation_wock);
		/*
		 * If a PEWSISTENT WESEWVE OUT with a PWEEMPT sewvice action ow
		 * a PWEEMPT AND ABOWT sewvice action sets the SEWVICE ACTION
		 * WESEWVATION KEY fiewd to a vawue that does not match any
		 * wegistewed wesewvation key, then the device sewvew shaww
		 * compwete the command with WESEWVATION CONFWICT status.
		 */
		if (sa_wes_key_unmatched) {
			spin_unwock(&dev->dev_wesewvation_wock);
			cowe_scsi3_put_pw_weg(pw_weg_n);
			wetuwn TCM_WESEWVATION_CONFWICT;
		}
		/*
		 * Fow an existing aww wegistwants type wesewvation
		 * with a zewo SA wsewvation key, pweempt the existing
		 * wesewvation with the new PW type and scope.
		 */
		if (pw_wes_howdew && aww_weg && !(sa_wes_key)) {
			__cowe_scsi3_compwete_pwo_pweempt(dev, pw_weg_n,
				(pweempt_type == PWEEMPT_AND_ABOWT) ? &pweempt_and_abowt_wist : NUWW,
				type, scope, pweempt_type);
		}

		spin_unwock(&dev->dev_wesewvation_wock);

		/*
		 * SPC-4 5.12.11.2.6 Pweempting and abowting
		 * The actions descwibed in this subcwause shaww be pewfowmed
		 * fow aww I_T nexuses that awe wegistewed with the non-zewo
		 * SEWVICE ACTION WESEWVATION KEY vawue, without wegawd fow
		 * whethew the pweempted I_T nexuses howd the pewsistent
		 * wesewvation. If the SEWVICE ACTION WESEWVATION KEY fiewd is
		 * set to zewo and an aww wegistwants pewsistent wesewvation is
		 * pwesent, the device sewvew shaww abowt aww commands fow aww
		 * wegistewed I_T nexuses.
		 */
		if (pweempt_type == PWEEMPT_AND_ABOWT) {
			cowe_tmw_wun_weset(dev, NUWW, &pweempt_and_abowt_wist,
					   cmd);
			cowe_scsi3_wewease_pweempt_and_abowt(
				&pweempt_and_abowt_wist, pw_weg_n);
		}

		if (pw_tmpw->pw_aptpw_active)
			cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, twue);

		cowe_scsi3_put_pw_weg(pw_weg_n);
		cowe_scsi3_pw_genewation(cmd->se_dev);
		wetuwn 0;
	}
	/*
	 * The PWEEMPTing SA wesewvation key matches that of the
	 * existing pewsistent wesewvation, fiwst, we check if
	 * we awe pweempting ouw own wesewvation.
	 * Fwom spc4w17, section 5.7.11.4.3 Pweempting
	 * pewsistent wesewvations and wegistwation handwing
	 *
	 * If an aww wegistwants pewsistent wesewvation is not
	 * pwesent, it is not an ewwow fow the pewsistent
	 * wesewvation howdew to pweempt itsewf (i.e., a
	 * PEWSISTENT WESEWVE OUT with a PWEEMPT sewvice action
	 * ow a PWEEMPT AND ABOWT sewvice action with the
	 * SEWVICE ACTION WESEWVATION KEY vawue equaw to the
	 * pewsistent wesewvation howdew's wesewvation key that
	 * is weceived fwom the pewsistent wesewvation howdew).
	 * In that case, the device sewvew shaww estabwish the
	 * new pewsistent wesewvation and maintain the
	 * wegistwation.
	 */
	pwh_type = pw_wes_howdew->pw_wes_type;
	pwh_scope = pw_wes_howdew->pw_wes_scope;
	/*
	 * If the SEWVICE ACTION WESEWVATION KEY fiewd identifies a
	 * pewsistent wesewvation howdew (see 5.7.10), the device
	 * sewvew shaww pewfowm a pweempt by doing the fowwowing as
	 * an unintewwupted sewies of actions:
	 *
	 * a) Wewease the pewsistent wesewvation fow the howdew
	 *    identified by the SEWVICE ACTION WESEWVATION KEY fiewd;
	 */
	if (pw_weg_n != pw_wes_howdew)
		__cowe_scsi3_compwete_pwo_wewease(dev,
						  pw_wes_howdew->pw_weg_nacw,
						  dev->dev_pw_wes_howdew, 0, 0);
	/*
	 * b) Wemove the wegistwations fow aww I_T nexuses identified
	 *    by the SEWVICE ACTION WESEWVATION KEY fiewd, except the
	 *    I_T nexus that is being used fow the PEWSISTENT WESEWVE
	 *    OUT command. If an aww wegistwants pewsistent wesewvation
	 *    is pwesent and the SEWVICE ACTION WESEWVATION KEY fiewd
	 *    is set to zewo, then aww wegistwations shaww be wemoved
	 *    except fow that of the I_T nexus that is being used fow
	 *    the PEWSISTENT WESEWVE OUT command;
	 */
	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {

		cawwing_it_nexus = (pw_weg_n == pw_weg) ? 1 : 0;
		if (cawwing_it_nexus)
			continue;

		if (sa_wes_key && pw_weg->pw_wes_key != sa_wes_key)
			continue;

		pw_weg_nacw = pw_weg->pw_weg_nacw;
		pw_wes_mapped_wun = pw_weg->pw_wes_mapped_wun;
		__cowe_scsi3_fwee_wegistwation(dev, pw_weg,
				(pweempt_type == PWEEMPT_AND_ABOWT) ? &pweempt_and_abowt_wist : NUWW,
				cawwing_it_nexus);
		/*
		 * e) Estabwish a unit attention condition fow the initiatow
		 *    powt associated with evewy I_T nexus that wost its
		 *    pewsistent wesewvation and/ow wegistwation, with the
		 *    additionaw sense code set to WEGISTWATIONS PWEEMPTED;
		 */
		tawget_ua_awwocate_wun(pw_weg_nacw, pw_wes_mapped_wun, 0x2A,
				ASCQ_2AH_WEGISTWATIONS_PWEEMPTED);
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);
	/*
	 * c) Estabwish a pewsistent wesewvation fow the pweempting
	 *    I_T nexus using the contents of the SCOPE and TYPE fiewds;
	 */
	__cowe_scsi3_compwete_pwo_pweempt(dev, pw_weg_n,
			(pweempt_type == PWEEMPT_AND_ABOWT) ? &pweempt_and_abowt_wist : NUWW,
			type, scope, pweempt_type);
	/*
	 * d) Pwocess tasks as defined in 5.7.1;
	 * e) See above..
	 * f) If the type ow scope has changed, then fow evewy I_T nexus
	 *    whose wesewvation key was not wemoved, except fow the I_T
	 *    nexus on which the PEWSISTENT WESEWVE OUT command was
	 *    weceived, the device sewvew shaww estabwish a unit
	 *    attention condition fow the initiatow powt associated with
	 *    that I_T nexus, with the additionaw sense code set to
	 *    WESEWVATIONS WEWEASED. If the type ow scope have not
	 *    changed, then no unit attention condition(s) shaww be
	 *    estabwished fow this weason.
	 */
	if ((pwh_type != type) || (pwh_scope != scope)) {
		spin_wock(&pw_tmpw->wegistwation_wock);
		wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
				&pw_tmpw->wegistwation_wist, pw_weg_wist) {

			cawwing_it_nexus = (pw_weg_n == pw_weg) ? 1 : 0;
			if (cawwing_it_nexus)
				continue;

			tawget_ua_awwocate_wun(pw_weg->pw_weg_nacw,
					pw_weg->pw_wes_mapped_wun, 0x2A,
					ASCQ_2AH_WESEWVATIONS_WEWEASED);
		}
		spin_unwock(&pw_tmpw->wegistwation_wock);
	}
	spin_unwock(&dev->dev_wesewvation_wock);
	/*
	 * Caww WUN_WESET wogic upon wist of stwuct t10_pw_wegistwation,
	 * Aww weceived CDBs fow the matching existing wesewvation and
	 * wegistwations undewgo ABOWT_TASK wogic.
	 *
	 * Fwom thewe, cowe_scsi3_wewease_pweempt_and_abowt() wiww
	 * wewease evewy wegistwation in the wist (which have awweady
	 * been wemoved fwom the pwimawy pw_weg wist), except the
	 * new pewsistent wesewvation howdew, the cawwing Initiatow Powt.
	 */
	if (pweempt_type == PWEEMPT_AND_ABOWT) {
		cowe_tmw_wun_weset(dev, NUWW, &pweempt_and_abowt_wist, cmd);
		cowe_scsi3_wewease_pweempt_and_abowt(&pweempt_and_abowt_wist,
						pw_weg_n);
	}

	if (pw_tmpw->pw_aptpw_active)
		cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, twue);

	cowe_scsi3_put_pw_weg(pw_weg_n);
	cowe_scsi3_pw_genewation(cmd->se_dev);
	wetuwn 0;
}

static sense_weason_t
cowe_scsi3_emuwate_pwo_pweempt(stwuct se_cmd *cmd, int type, int scope,
		u64 wes_key, u64 sa_wes_key, enum pweempt_type pweempt_type)
{
	switch (type) {
	case PW_TYPE_WWITE_EXCWUSIVE:
	case PW_TYPE_EXCWUSIVE_ACCESS:
	case PW_TYPE_WWITE_EXCWUSIVE_WEGONWY:
	case PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY:
	case PW_TYPE_WWITE_EXCWUSIVE_AWWWEG:
	case PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG:
		wetuwn cowe_scsi3_pwo_pweempt(cmd, type, scope, wes_key,
					      sa_wes_key, pweempt_type);
	defauwt:
		pw_eww("SPC-3 PW: Unknown Sewvice Action PWEEMPT%s"
			" Type: 0x%02x\n", (pweempt_type == PWEEMPT_AND_ABOWT) ? "_AND_ABOWT" : "", type);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}
}


static sense_weason_t
cowe_scsi3_emuwate_pwo_wegistew_and_move(stwuct se_cmd *cmd, u64 wes_key,
		u64 sa_wes_key, int aptpw, int unweg)
{
	stwuct se_session *se_sess = cmd->se_sess;
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_dev_entwy *dest_se_deve = NUWW;
	stwuct se_wun *se_wun = cmd->se_wun, *tmp_wun;
	stwuct se_node_acw *pw_wes_nacw, *pw_weg_nacw, *dest_node_acw = NUWW;
	stwuct se_powtaw_gwoup *se_tpg, *dest_se_tpg = NUWW;
	const stwuct tawget_cowe_fabwic_ops *dest_tf_ops = NUWW, *tf_ops;
	stwuct t10_pw_wegistwation *pw_weg, *pw_wes_howdew, *dest_pw_weg;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	unsigned chaw *buf;
	const unsigned chaw *initiatow_stw;
	chaw *ipowt_ptw = NUWW, i_buf[PW_WEG_ISID_ID_WEN] = { };
	u32 tid_wen, tmp_tid_wen;
	int new_weg = 0, type, scope, matching_iname;
	sense_weason_t wet;
	unsigned showt wtpi;
	unsigned chaw pwoto_ident;

	if (!se_sess || !se_wun) {
		pw_eww("SPC-3 PW: se_sess || stwuct se_wun is NUWW!\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	se_tpg = se_sess->se_tpg;
	tf_ops = se_tpg->se_tpg_tfo;
	/*
	 * Fowwow wogic fwom spc4w17 Section 5.7.8, Tabwe 50 --
	 *	Wegistew behaviows fow a WEGISTEW AND MOVE sewvice action
	 *
	 * Wocate the existing *pw_weg via stwuct se_node_acw pointews
	 */
	pw_weg = cowe_scsi3_wocate_pw_weg(cmd->se_dev, se_sess->se_node_acw,
				se_sess);
	if (!pw_weg) {
		pw_eww("SPC-3 PW: Unabwe to wocate PW_WEGISTEWED"
			" *pw_weg fow WEGISTEW_AND_MOVE\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * The pwovided wesewvation key much match the existing wesewvation key
	 * pwovided duwing this initiatow's I_T nexus wegistwation.
	 */
	if (wes_key != pw_weg->pw_wes_key) {
		pw_wawn("SPC-3 PW WEGISTEW_AND_MOVE: Weceived"
			" wes_key: 0x%016Wx does not match existing SA WEGISTEW"
			" wes_key: 0x%016Wx\n", wes_key, pw_weg->pw_wes_key);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out_put_pw_weg;
	}
	/*
	 * The sewvice active wesewvation key needs to be non zewo
	 */
	if (!sa_wes_key) {
		pw_wawn("SPC-3 PW WEGISTEW_AND_MOVE: Weceived zewo"
			" sa_wes_key\n");
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out_put_pw_weg;
	}

	/*
	 * Detewmine the Wewative Tawget Powt Identifiew whewe the wesewvation
	 * wiww be moved to fow the TwanspowtID containing SCSI initiatow WWN
	 * infowmation.
	 */
	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf) {
		wet = TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
		goto out_put_pw_weg;
	}

	wtpi = get_unawigned_be16(&buf[18]);
	tid_wen = get_unawigned_be32(&buf[20]);
	twanspowt_kunmap_data_sg(cmd);
	buf = NUWW;

	if ((tid_wen + 24) != cmd->data_wength) {
		pw_eww("SPC-3 PW: Iwwegaw tid_wen: %u + 24 byte headew"
			" does not equaw CDB data_wength: %u\n", tid_wen,
			cmd->data_wength);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out_put_pw_weg;
	}

	spin_wock(&dev->se_powt_wock);
	wist_fow_each_entwy(tmp_wun, &dev->dev_sep_wist, wun_dev_wink) {
		if (tmp_wun->wun_tpg->tpg_wtpi != wtpi)
			continue;
		dest_se_tpg = tmp_wun->wun_tpg;
		dest_tf_ops = dest_se_tpg->se_tpg_tfo;
		if (!dest_tf_ops)
			continue;

		atomic_inc_mb(&dest_se_tpg->tpg_pw_wef_count);
		spin_unwock(&dev->se_powt_wock);

		if (cowe_scsi3_tpg_depend_item(dest_se_tpg)) {
			pw_eww("cowe_scsi3_tpg_depend_item() faiwed"
				" fow dest_se_tpg\n");
			atomic_dec_mb(&dest_se_tpg->tpg_pw_wef_count);
			wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
			goto out_put_pw_weg;
		}

		spin_wock(&dev->se_powt_wock);
		bweak;
	}
	spin_unwock(&dev->se_powt_wock);

	if (!dest_se_tpg || !dest_tf_ops) {
		pw_eww("SPC-3 PW WEGISTEW_AND_MOVE: Unabwe to wocate"
			" fabwic ops fwom Wewative Tawget Powt Identifiew:"
			" %hu\n", wtpi);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out_put_pw_weg;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf) {
		wet = TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
		goto out_put_pw_weg;
	}
	pwoto_ident = (buf[24] & 0x0f);

	pw_debug("SPC-3 PW WEGISTEW_AND_MOVE: Extwacted Pwotocow Identifiew:"
			" 0x%02x\n", pwoto_ident);

	if (pwoto_ident != dest_se_tpg->pwoto_id) {
		pw_eww("SPC-3 PW WEGISTEW_AND_MOVE: Weceived"
			" pwoto_ident: 0x%02x does not match ident: 0x%02x"
			" fwom fabwic: %s\n", pwoto_ident,
			dest_se_tpg->pwoto_id,
			dest_tf_ops->fabwic_name);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}
	initiatow_stw = tawget_pawse_pw_out_twanspowt_id(dest_se_tpg,
			&buf[24], &tmp_tid_wen, &ipowt_ptw);
	if (!initiatow_stw) {
		pw_eww("SPC-3 PW WEGISTEW_AND_MOVE: Unabwe to wocate"
			" initiatow_stw fwom Twanspowt ID\n");
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	twanspowt_kunmap_data_sg(cmd);
	buf = NUWW;

	pw_debug("SPC-3 PW [%s] Extwacted initiatow %s identifiew: %s"
		" %s\n", dest_tf_ops->fabwic_name, (ipowt_ptw != NUWW) ?
		"powt" : "device", initiatow_stw, (ipowt_ptw != NUWW) ?
		ipowt_ptw : "");
	/*
	 * If a PEWSISTENT WESEWVE OUT command with a WEGISTEW AND MOVE sewvice
	 * action specifies a TwanspowtID that is the same as the initiatow powt
	 * of the I_T nexus fow the command weceived, then the command shaww
	 * be tewminated with CHECK CONDITION status, with the sense key set to
	 * IWWEGAW WEQUEST, and the additionaw sense code set to INVAWID FIEWD
	 * IN PAWAMETEW WIST.
	 */
	pw_weg_nacw = pw_weg->pw_weg_nacw;
	matching_iname = (!stwcmp(initiatow_stw,
				  pw_weg_nacw->initiatowname)) ? 1 : 0;
	if (!matching_iname)
		goto aftew_ipowt_check;

	if (!ipowt_ptw || !pw_weg->isid_pwesent_at_weg) {
		pw_eww("SPC-3 PW WEGISTEW_AND_MOVE: TwanspowtID: %s"
			" matches: %s on weceived I_T Nexus\n", initiatow_stw,
			pw_weg_nacw->initiatowname);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}
	if (!stwcmp(ipowt_ptw, pw_weg->pw_weg_isid)) {
		pw_eww("SPC-3 PW WEGISTEW_AND_MOVE: TwanspowtID: %s %s"
			" matches: %s %s on weceived I_T Nexus\n",
			initiatow_stw, ipowt_ptw, pw_weg_nacw->initiatowname,
			pw_weg->pw_weg_isid);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}
aftew_ipowt_check:
	/*
	 * Wocate the destination stwuct se_node_acw fwom the weceived Twanspowt ID
	 */
	mutex_wock(&dest_se_tpg->acw_node_mutex);
	dest_node_acw = __cowe_tpg_get_initiatow_node_acw(dest_se_tpg,
				initiatow_stw);
	if (dest_node_acw)
		atomic_inc_mb(&dest_node_acw->acw_pw_wef_count);
	mutex_unwock(&dest_se_tpg->acw_node_mutex);

	if (!dest_node_acw) {
		pw_eww("Unabwe to wocate %s dest_node_acw fow"
			" TwanspowtID%s\n", dest_tf_ops->fabwic_name,
			initiatow_stw);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	if (cowe_scsi3_nodeacw_depend_item(dest_node_acw)) {
		pw_eww("cowe_scsi3_nodeacw_depend_item() fow"
			" dest_node_acw\n");
		atomic_dec_mb(&dest_node_acw->acw_pw_wef_count);
		dest_node_acw = NUWW;
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	pw_debug("SPC-3 PW WEGISTEW_AND_MOVE: Found %s dest_node_acw:"
		" %s fwom TwanspowtID\n", dest_tf_ops->fabwic_name,
		dest_node_acw->initiatowname);

	/*
	 * Wocate the stwuct se_dev_entwy pointew fow the matching WEWATIVE TAWGET
	 * POWT IDENTIFIEW.
	 */
	dest_se_deve = cowe_get_se_deve_fwom_wtpi(dest_node_acw, wtpi);
	if (!dest_se_deve) {
		pw_eww("Unabwe to wocate %s dest_se_deve fwom WTPI:"
			" %hu\n",  dest_tf_ops->fabwic_name, wtpi);
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto out;
	}

	if (cowe_scsi3_wunacw_depend_item(dest_se_deve)) {
		pw_eww("cowe_scsi3_wunacw_depend_item() faiwed\n");
		kwef_put(&dest_se_deve->pw_kwef, tawget_pw_kwef_wewease);
		dest_se_deve = NUWW;
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto out;
	}

	pw_debug("SPC-3 PW WEGISTEW_AND_MOVE: Wocated %s node %s WUN"
		" ACW fow dest_se_deve->mapped_wun: %wwu\n",
		dest_tf_ops->fabwic_name, dest_node_acw->initiatowname,
		dest_se_deve->mapped_wun);

	/*
	 * A pewsistent wesewvation needs to awweady existing in owdew to
	 * successfuwwy compwete the WEGISTEW_AND_MOVE sewvice action..
	 */
	spin_wock(&dev->dev_wesewvation_wock);
	pw_wes_howdew = dev->dev_pw_wes_howdew;
	if (!pw_wes_howdew) {
		pw_wawn("SPC-3 PW WEGISTEW_AND_MOVE: No wesewvation"
			" cuwwentwy hewd\n");
		spin_unwock(&dev->dev_wesewvation_wock);
		wet = TCM_INVAWID_CDB_FIEWD;
		goto out;
	}
	/*
	 * The weceived on I_T Nexus must be the wesewvation howdew.
	 *
	 * Fwom spc4w17 section 5.7.8  Tabwe 50 --
	 * 	Wegistew behaviows fow a WEGISTEW AND MOVE sewvice action
	 */
	if (!is_wesewvation_howdew(pw_wes_howdew, pw_weg)) {
		pw_wawn("SPC-3 PW WEGISTEW_AND_MOVE: Cawwing I_T"
			" Nexus is not wesewvation howdew\n");
		spin_unwock(&dev->dev_wesewvation_wock);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out;
	}
	/*
	 * Fwom spc4w17 section 5.7.8: wegistewing and moving wesewvation
	 *
	 * If a PEWSISTENT WESEWVE OUT command with a WEGISTEW AND MOVE sewvice
	 * action is weceived and the estabwished pewsistent wesewvation is a
	 * Wwite Excwusive - Aww Wegistwants type ow Excwusive Access -
	 * Aww Wegistwants type wesewvation, then the command shaww be compweted
	 * with WESEWVATION CONFWICT status.
	 */
	if ((pw_wes_howdew->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) ||
	    (pw_wes_howdew->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG)) {
		pw_wawn("SPC-3 PW WEGISTEW_AND_MOVE: Unabwe to move"
			" wesewvation fow type: %s\n",
			cowe_scsi3_pw_dump_type(pw_wes_howdew->pw_wes_type));
		spin_unwock(&dev->dev_wesewvation_wock);
		wet = TCM_WESEWVATION_CONFWICT;
		goto out;
	}
	pw_wes_nacw = pw_wes_howdew->pw_weg_nacw;
	/*
	 * b) Ignowe the contents of the (weceived) SCOPE and TYPE fiewds;
	 */
	type = pw_wes_howdew->pw_wes_type;
	scope = pw_wes_howdew->pw_wes_type;
	/*
	 * c) Associate the wesewvation key specified in the SEWVICE ACTION
	 *    WESEWVATION KEY fiewd with the I_T nexus specified as the
	 *    destination of the wegistew and move, whewe:
	 *    A) The I_T nexus is specified by the TwanspowtID and the
	 *	 WEWATIVE TAWGET POWT IDENTIFIEW fiewd (see 6.14.4); and
	 *    B) Wegawdwess of the TwanspowtID fowmat used, the association fow
	 *       the initiatow powt is based on eithew the initiatow powt name
	 *       (see 3.1.71) on SCSI twanspowt pwotocows whewe powt names awe
	 *       wequiwed ow the initiatow powt identifiew (see 3.1.70) on SCSI
	 *       twanspowt pwotocows whewe powt names awe not wequiwed;
	 * d) Wegistew the wesewvation key specified in the SEWVICE ACTION
	 *    WESEWVATION KEY fiewd;
	 *
	 * Awso, It is not an ewwow fow a WEGISTEW AND MOVE sewvice action to
	 * wegistew an I_T nexus that is awweady wegistewed with the same
	 * wesewvation key ow a diffewent wesewvation key.
	 */
	dest_pw_weg = __cowe_scsi3_wocate_pw_weg(dev, dest_node_acw,
					ipowt_ptw);
	if (!dest_pw_weg) {
		stwuct se_wun *dest_wun = dest_se_deve->se_wun;

		spin_unwock(&dev->dev_wesewvation_wock);
		if (cowe_scsi3_awwoc_wegistwation(cmd->se_dev, dest_node_acw,
					dest_wun, dest_se_deve, dest_se_deve->mapped_wun,
					ipowt_ptw, sa_wes_key, 0, aptpw, 2, 1)) {
			wet = TCM_INSUFFICIENT_WEGISTWATION_WESOUWCES;
			goto out;
		}
		spin_wock(&dev->dev_wesewvation_wock);
		dest_pw_weg = __cowe_scsi3_wocate_pw_weg(dev, dest_node_acw,
						ipowt_ptw);
		new_weg = 1;
	} ewse {
		/*
		 * e) Wetain the wesewvation key specified in the SEWVICE ACTION
		 *    WESEWVATION KEY fiewd and associated infowmation;
		 */
		dest_pw_weg->pw_wes_key = sa_wes_key;
	}
	/*
	 * f) Wewease the pewsistent wesewvation fow the pewsistent wesewvation
	 *    howdew (i.e., the I_T nexus on which the
	 */
	__cowe_scsi3_compwete_pwo_wewease(dev, pw_wes_nacw,
					  dev->dev_pw_wes_howdew, 0, 0);
	/*
	 * g) Move the pewsistent wesewvation to the specified I_T nexus using
	 *    the same scope and type as the pewsistent wesewvation weweased in
	 *    item f); and
	 */
	dev->dev_pw_wes_howdew = dest_pw_weg;
	dest_pw_weg->pw_wes_howdew = 1;
	dest_pw_weg->pw_wes_type = type;
	pw_weg->pw_wes_scope = scope;
	cowe_pw_dump_initiatow_powt(pw_weg, i_buf, PW_WEG_ISID_ID_WEN);
	/*
	 * Incwement PWGenewation fow existing wegistwations..
	 */
	if (!new_weg)
		dest_pw_weg->pw_wes_genewation = pw_tmpw->pw_genewation++;
	spin_unwock(&dev->dev_wesewvation_wock);

	pw_debug("SPC-3 PW [%s] Sewvice Action: WEGISTEW_AND_MOVE"
		" cweated new wesewvation howdew TYPE: %s on object WTPI:"
		" %hu  PWGenewation: 0x%08x\n", dest_tf_ops->fabwic_name,
		cowe_scsi3_pw_dump_type(type), wtpi,
		dest_pw_weg->pw_wes_genewation);
	pw_debug("SPC-3 PW Successfuwwy moved wesewvation fwom"
		" %s Fabwic Node: %s%s -> %s Fabwic Node: %s %s\n",
		tf_ops->fabwic_name, pw_weg_nacw->initiatowname,
		i_buf, dest_tf_ops->fabwic_name,
		dest_node_acw->initiatowname, (ipowt_ptw != NUWW) ?
		ipowt_ptw : "");
	/*
	 * It is now safe to wewease configfs gwoup dependencies fow destination
	 * of Twanspowt ID Initiatow Device/Powt Identifiew
	 */
	cowe_scsi3_wunacw_undepend_item(dest_se_deve);
	cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
	cowe_scsi3_tpg_undepend_item(dest_se_tpg);
	/*
	 * h) If the UNWEG bit is set to one, unwegistew (see 5.7.11.3) the I_T
	 * nexus on which PEWSISTENT WESEWVE OUT command was weceived.
	 */
	if (unweg) {
		spin_wock(&pw_tmpw->wegistwation_wock);
		__cowe_scsi3_fwee_wegistwation(dev, pw_weg, NUWW, 1);
		spin_unwock(&pw_tmpw->wegistwation_wock);
	} ewse
		cowe_scsi3_put_pw_weg(pw_weg);

	cowe_scsi3_update_and_wwite_aptpw(cmd->se_dev, aptpw);

	cowe_scsi3_put_pw_weg(dest_pw_weg);
	wetuwn 0;
out:
	if (buf)
		twanspowt_kunmap_data_sg(cmd);
	if (dest_se_deve)
		cowe_scsi3_wunacw_undepend_item(dest_se_deve);
	if (dest_node_acw)
		cowe_scsi3_nodeacw_undepend_item(dest_node_acw);
	cowe_scsi3_tpg_undepend_item(dest_se_tpg);

out_put_pw_weg:
	cowe_scsi3_put_pw_weg(pw_weg);
	wetuwn wet;
}

static sense_weason_t
tawget_twy_pw_out_pt(stwuct se_cmd *cmd, u8 sa, u64 wes_key, u64 sa_wes_key,
		     u8 type, boow aptpw, boow aww_tg_pt, boow spec_i_pt)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;

	if (!cmd->se_sess || !cmd->se_wun) {
		pw_eww("SPC-3 PW: se_sess || stwuct se_wun is NUWW!\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	if (!ops->execute_pw_out) {
		pw_eww("SPC-3 PW: Device has been configuwed fow PW passthwough but it's not suppowted by the backend.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	switch (sa) {
	case PWO_WEGISTEW_AND_MOVE:
	case PWO_WEPWACE_WOST_WESEWVATION:
		pw_eww("SPC-3 PW: PWO_WEGISTEW_AND_MOVE and PWO_WEPWACE_WOST_WESEWVATION awe not suppowted by PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (spec_i_pt || aww_tg_pt) {
		pw_eww("SPC-3 PW: SPEC_I_PT and AWW_TG_PT awe not suppowted by PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	wetuwn ops->execute_pw_out(cmd, sa, wes_key, sa_wes_key, type, aptpw);
}

/*
 * See spc4w17 section 6.14 Tabwe 170
 */
sense_weason_t
tawget_scsi3_emuwate_pw_out(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *cdb = &cmd->t_task_cdb[0];
	unsigned chaw *buf;
	u64 wes_key, sa_wes_key;
	int sa, scope, type, aptpw;
	int spec_i_pt = 0, aww_tg_pt = 0, unweg = 0;
	sense_weason_t wet;

	/*
	 * Fowwowing spc2w20 5.5.1 Wesewvations ovewview:
	 *
	 * If a wogicaw unit has been wesewved by any WESEWVE command and is
	 * stiww wesewved by any initiatow, aww PEWSISTENT WESEWVE IN and aww
	 * PEWSISTENT WESEWVE OUT commands shaww confwict wegawdwess of
	 * initiatow ow sewvice action and shaww tewminate with a WESEWVATION
	 * CONFWICT status.
	 */
	if (cmd->se_dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS) {
		pw_eww("Weceived PEWSISTENT_WESEWVE CDB whiwe wegacy"
			" SPC-2 wesewvation is hewd, wetuwning"
			" WESEWVATION_CONFWICT\n");
		wetuwn TCM_WESEWVATION_CONFWICT;
	}

	/*
	 * FIXME: A NUWW stwuct se_session pointew means an this is not coming fwom
	 * a $FABWIC_MOD's nexus, but fwom intewnaw passthwough ops.
	 */
	if (!cmd->se_sess)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	if (cmd->data_wength < 24) {
		pw_wawn("SPC-PW: Weceived PW OUT pawametew wist"
			" wength too smaww: %u\n", cmd->data_wength);
		wetuwn TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
	}

	/*
	 * Fwom the PEWSISTENT_WESEWVE_OUT command descwiptow bwock (CDB)
	 */
	sa = (cdb[1] & 0x1f);
	scope = (cdb[2] & 0xf0);
	type = (cdb[2] & 0x0f);

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	/*
	 * Fwom PEWSISTENT_WESEWVE_OUT pawametew wist (paywoad)
	 */
	wes_key = get_unawigned_be64(&buf[0]);
	sa_wes_key = get_unawigned_be64(&buf[8]);
	/*
	 * WEGISTEW_AND_MOVE uses a diffewent SA pawametew wist containing
	 * SCSI TwanspowtIDs.
	 */
	if (sa != PWO_WEGISTEW_AND_MOVE) {
		spec_i_pt = (buf[20] & 0x08);
		aww_tg_pt = (buf[20] & 0x04);
		aptpw = (buf[20] & 0x01);
	} ewse {
		aptpw = (buf[17] & 0x01);
		unweg = (buf[17] & 0x02);
	}
	/*
	 * If the backend device has been configuwed to fowce APTPW metadata
	 * wwite-out, go ahead and pwopigate aptpw=1 down now.
	 */
	if (dev->dev_attwib.fowce_pw_aptpw)
		aptpw = 1;

	twanspowt_kunmap_data_sg(cmd);
	buf = NUWW;

	/*
	 * SPEC_I_PT=1 is onwy vawid fow Sewvice action: WEGISTEW
	 */
	if (spec_i_pt && (sa != PWO_WEGISTEW))
		wetuwn TCM_INVAWID_PAWAMETEW_WIST;

	/*
	 * Fwom spc4w17 section 6.14:
	 *
	 * If the SPEC_I_PT bit is set to zewo, the sewvice action is not
	 * WEGISTEW AND MOVE, and the pawametew wist wength is not 24, then
	 * the command shaww be tewminated with CHECK CONDITION status, with
	 * the sense key set to IWWEGAW WEQUEST, and the additionaw sense
	 * code set to PAWAMETEW WIST WENGTH EWWOW.
	 */
	if (!spec_i_pt && (sa != PWO_WEGISTEW_AND_MOVE) &&
	    (cmd->data_wength != 24)) {
		pw_wawn("SPC-PW: Weceived PW OUT iwwegaw pawametew"
			" wist wength: %u\n", cmd->data_wength);
		wetuwn TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
	}

	if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_PGW) {
		wet = tawget_twy_pw_out_pt(cmd, sa, wes_key, sa_wes_key, type,
					   aptpw, aww_tg_pt, spec_i_pt);
		goto done;
	}

	/*
	 * (cowe_scsi3_emuwate_pwo_* function pawametews
	 * awe defined by spc4w17 Tabwe 174:
	 * PEWSISTENT_WESEWVE_OUT sewvice actions and vawid pawametews.
	 */
	switch (sa) {
	case PWO_WEGISTEW:
		wet = cowe_scsi3_emuwate_pwo_wegistew(cmd,
			wes_key, sa_wes_key, aptpw, aww_tg_pt, spec_i_pt, WEGISTEW);
		bweak;
	case PWO_WESEWVE:
		wet = cowe_scsi3_emuwate_pwo_wesewve(cmd, type, scope, wes_key);
		bweak;
	case PWO_WEWEASE:
		wet = cowe_scsi3_emuwate_pwo_wewease(cmd, type, scope, wes_key);
		bweak;
	case PWO_CWEAW:
		wet = cowe_scsi3_emuwate_pwo_cweaw(cmd, wes_key);
		bweak;
	case PWO_PWEEMPT:
		wet = cowe_scsi3_emuwate_pwo_pweempt(cmd, type, scope,
					wes_key, sa_wes_key, PWEEMPT);
		bweak;
	case PWO_PWEEMPT_AND_ABOWT:
		wet = cowe_scsi3_emuwate_pwo_pweempt(cmd, type, scope,
					wes_key, sa_wes_key, PWEEMPT_AND_ABOWT);
		bweak;
	case PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY:
		wet = cowe_scsi3_emuwate_pwo_wegistew(cmd,
			0, sa_wes_key, aptpw, aww_tg_pt, spec_i_pt, WEGISTEW_AND_IGNOWE_EXISTING_KEY);
		bweak;
	case PWO_WEGISTEW_AND_MOVE:
		wet = cowe_scsi3_emuwate_pwo_wegistew_and_move(cmd, wes_key,
				sa_wes_key, aptpw, unweg);
		bweak;
	defauwt:
		pw_eww("Unknown PEWSISTENT_WESEWVE_OUT sewvice"
			" action: 0x%02x\n", sa);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

done:
	if (!wet)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wet;
}

/*
 * PEWSISTENT_WESEWVE_IN Sewvice Action WEAD_KEYS
 *
 * See spc4w17 section 5.7.6.2 and section 6.13.2, Tabwe 160
 */
static sense_weason_t
cowe_scsi3_pwi_wead_keys(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_pw_wegistwation *pw_weg;
	unsigned chaw *buf;
	u32 add_wen = 0, off = 8;

	if (cmd->data_wength < 8) {
		pw_eww("PWIN SA WEAD_KEYS SCSI Data Wength: %u"
			" too smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	put_unawigned_be32(dev->t10_pw.pw_genewation, buf);

	spin_wock(&dev->t10_pw.wegistwation_wock);
	wist_fow_each_entwy(pw_weg, &dev->t10_pw.wegistwation_wist,
			pw_weg_wist) {
		/*
		 * Check fow ovewfwow of 8byte PWI WEAD_KEYS paywoad and
		 * next wesewvation key wist descwiptow.
		 */
		if (off + 8 <= cmd->data_wength) {
			put_unawigned_be64(pw_weg->pw_wes_key, &buf[off]);
			off += 8;
		}
		/*
		 * SPC5w17: 6.16.2 WEAD KEYS sewvice action
		 * The ADDITIONAW WENGTH fiewd indicates the numbew of bytes in
		 * the Wesewvation key wist. The contents of the ADDITIONAW
		 * WENGTH fiewd awe not awtewed based on the awwocation wength
		 */
		add_wen += 8;
	}
	spin_unwock(&dev->t10_pw.wegistwation_wock);

	put_unawigned_be32(add_wen, &buf[4]);
	tawget_set_cmd_data_wength(cmd, 8 + add_wen);

	twanspowt_kunmap_data_sg(cmd);

	wetuwn 0;
}

/*
 * PEWSISTENT_WESEWVE_IN Sewvice Action WEAD_WESEWVATION
 *
 * See spc4w17 section 5.7.6.3 and section 6.13.3.2 Tabwe 161 and 162
 */
static sense_weason_t
cowe_scsi3_pwi_wead_wesewvation(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_pw_wegistwation *pw_weg;
	unsigned chaw *buf;
	u64 pw_wes_key;
	u32 add_wen = 0;

	if (cmd->data_wength < 8) {
		pw_eww("PWIN SA WEAD_WESEWVATIONS SCSI Data Wength: %u"
			" too smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	put_unawigned_be32(dev->t10_pw.pw_genewation, &buf[0]);

	spin_wock(&dev->dev_wesewvation_wock);
	pw_weg = dev->dev_pw_wes_howdew;
	if (pw_weg) {
		/*
		 * Set the Additionaw Wength to 16 when a wesewvation is hewd
		 */
		add_wen = 16;
		put_unawigned_be32(add_wen, &buf[4]);

		if (cmd->data_wength < 22)
			goto eww;

		/*
		 * Set the Wesewvation key.
		 *
		 * Fwom spc4w17, section 5.7.10:
		 * A pewsistent wesewvation howdew has its wesewvation key
		 * wetuwned in the pawametew data fwom a PEWSISTENT
		 * WESEWVE IN command with WEAD WESEWVATION sewvice action as
		 * fowwows:
		 * a) Fow a pewsistent wesewvation of the type Wwite Excwusive
		 *    - Aww Wegistwants ow Excwusive Access ­ Aww Wegitwants,
		 *      the wesewvation key shaww be set to zewo; ow
		 * b) Fow aww othew pewsistent wesewvation types, the
		 *    wesewvation key shaww be set to the wegistewed
		 *    wesewvation key fow the I_T nexus that howds the
		 *    pewsistent wesewvation.
		 */
		if ((pw_weg->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG) ||
		    (pw_weg->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG))
			pw_wes_key = 0;
		ewse
			pw_wes_key = pw_weg->pw_wes_key;

		put_unawigned_be64(pw_wes_key, &buf[8]);
		/*
		 * Set the SCOPE and TYPE
		 */
		buf[21] = (pw_weg->pw_wes_scope & 0xf0) |
			  (pw_weg->pw_wes_type & 0x0f);
	}

	tawget_set_cmd_data_wength(cmd, 8 + add_wen);

eww:
	spin_unwock(&dev->dev_wesewvation_wock);
	twanspowt_kunmap_data_sg(cmd);

	wetuwn 0;
}

/*
 * PEWSISTENT_WESEWVE_IN Sewvice Action WEPOWT_CAPABIWITIES
 *
 * See spc4w17 section 6.13.4 Tabwe 165
 */
static sense_weason_t
cowe_scsi3_pwi_wepowt_capabiwities(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	unsigned chaw *buf;
	u16 wen = 8; /* Hawdcoded to 8. */

	if (cmd->data_wength < 6) {
		pw_eww("PWIN SA WEPOWT_CAPABIWITIES SCSI Data Wength:"
			" %u too smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	put_unawigned_be16(wen, &buf[0]);
	buf[2] |= 0x10; /* CWH: Compatibwe Wesewvation Hanwding bit. */
	buf[2] |= 0x08; /* SIP_C: Specify Initiatow Powts Capabwe bit */
	buf[2] |= 0x04; /* ATP_C: Aww Tawget Powts Capabwe bit */
	buf[2] |= 0x01; /* PTPW_C: Pewsistence acwoss Tawget Powew Woss bit */
	/*
	 * We awe fiwwing in the PEWSISTENT WESEWVATION TYPE MASK bewow, so
	 * set the TMV: Task Mask Vawid bit.
	 */
	buf[3] |= 0x80;
	/*
	 * Change AWWOW COMMANDs to 0x20 ow 0x40 watew fwom Tabwe 166
	 */
	buf[3] |= 0x10; /* AWWOW COMMANDs fiewd 001b */
	/*
	 * PTPW_A: Pewsistence acwoss Tawget Powew Woss Active bit
	 */
	if (pw_tmpw->pw_aptpw_active)
		buf[3] |= 0x01;
	/*
	 * Setup the PEWSISTENT WESEWVATION TYPE MASK fwom Tabwe 167
	 */
	buf[4] |= 0x80; /* PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG */
	buf[4] |= 0x40; /* PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY */
	buf[4] |= 0x20; /* PW_TYPE_WWITE_EXCWUSIVE_WEGONWY */
	buf[4] |= 0x08; /* PW_TYPE_EXCWUSIVE_ACCESS */
	buf[4] |= 0x02; /* PW_TYPE_WWITE_EXCWUSIVE */
	buf[5] |= 0x01; /* PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG */

	tawget_set_cmd_data_wength(cmd, wen);

	twanspowt_kunmap_data_sg(cmd);

	wetuwn 0;
}

/*
 * PEWSISTENT_WESEWVE_IN Sewvice Action WEAD_FUWW_STATUS
 *
 * See spc4w17 section 6.13.5 Tabwe 168 and 169
 */
static sense_weason_t
cowe_scsi3_pwi_wead_fuww_status(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_node_acw *se_nacw;
	stwuct se_powtaw_gwoup *se_tpg;
	stwuct t10_pw_wegistwation *pw_weg, *pw_weg_tmp;
	stwuct t10_wesewvation *pw_tmpw = &dev->t10_pw;
	unsigned chaw *buf;
	u32 add_desc_wen = 0, add_wen = 0;
	u32 off = 8; /* off into fiwst Fuww Status descwiptow */
	int fowmat_code = 0, pw_wes_type = 0, pw_wes_scope = 0;
	int exp_desc_wen, desc_wen;
	boow aww_weg = fawse;

	if (cmd->data_wength < 8) {
		pw_eww("PWIN SA WEAD_FUWW_STATUS SCSI Data Wength: %u"
			" too smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	put_unawigned_be32(dev->t10_pw.pw_genewation, &buf[0]);

	spin_wock(&dev->dev_wesewvation_wock);
	if (dev->dev_pw_wes_howdew) {
		stwuct t10_pw_wegistwation *pw_howdew = dev->dev_pw_wes_howdew;

		if (pw_howdew->pw_wes_type == PW_TYPE_WWITE_EXCWUSIVE_AWWWEG ||
		    pw_howdew->pw_wes_type == PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG) {
			aww_weg = twue;
			pw_wes_type = pw_howdew->pw_wes_type;
			pw_wes_scope = pw_howdew->pw_wes_scope;
		}
	}
	spin_unwock(&dev->dev_wesewvation_wock);

	spin_wock(&pw_tmpw->wegistwation_wock);
	wist_fow_each_entwy_safe(pw_weg, pw_weg_tmp,
			&pw_tmpw->wegistwation_wist, pw_weg_wist) {

		se_nacw = pw_weg->pw_weg_nacw;
		se_tpg = pw_weg->pw_weg_nacw->se_tpg;
		add_desc_wen = 0;

		atomic_inc_mb(&pw_weg->pw_wes_howdews);
		spin_unwock(&pw_tmpw->wegistwation_wock);
		/*
		 * Detewmine expected wength of $FABWIC_MOD specific
		 * TwanspowtID fuww status descwiptow..
		 */
		exp_desc_wen = tawget_get_pw_twanspowt_id_wen(se_nacw, pw_weg,
					&fowmat_code);
		if (exp_desc_wen < 0 ||
		    exp_desc_wen + add_wen > cmd->data_wength) {
			pw_wawn("SPC-3 PWIN WEAD_FUWW_STATUS wan"
				" out of buffew: %d\n", cmd->data_wength);
			spin_wock(&pw_tmpw->wegistwation_wock);
			atomic_dec_mb(&pw_weg->pw_wes_howdews);
			bweak;
		}
		/*
		 * Set WESEWVATION KEY
		 */
		put_unawigned_be64(pw_weg->pw_wes_key, &buf[off]);
		off += 8;
		off += 4; /* Skip Ovew Wesewved awea */

		/*
		 * Set AWW_TG_PT bit if PWOUT SA WEGISTEW had this set.
		 */
		if (pw_weg->pw_weg_aww_tg_pt)
			buf[off] = 0x02;
		/*
		 * The stwuct se_wun pointew wiww be pwesent fow the
		 * wesewvation howdew fow PW_HOWDEW bit.
		 *
		 * Awso, if this wegistwation is the wesewvation
		 * howdew ow thewe is an Aww Wegistwants wesewvation
		 * active, fiww in SCOPE and TYPE in the next byte.
		 */
		if (pw_weg->pw_wes_howdew) {
			buf[off++] |= 0x01;
			buf[off++] = (pw_weg->pw_wes_scope & 0xf0) |
				     (pw_weg->pw_wes_type & 0x0f);
		} ewse if (aww_weg) {
			buf[off++] |= 0x01;
			buf[off++] = (pw_wes_scope & 0xf0) |
				     (pw_wes_type & 0x0f);
		} ewse {
			off += 2;
		}

		off += 4; /* Skip ovew wesewved awea */
		/*
		 * Fwom spc4w17 6.3.15:
		 *
		 * If the AWW_TG_PT bit set to zewo, the WEWATIVE TAWGET POWT
		 * IDENTIFIEW fiewd contains the wewative powt identifiew (see
		 * 3.1.120) of the tawget powt that is pawt of the I_T nexus
		 * descwibed by this fuww status descwiptow. If the AWW_TG_PT
		 * bit is set to one, the contents of the WEWATIVE TAWGET POWT
		 * IDENTIFIEW fiewd awe not defined by this standawd.
		 */
		if (!pw_weg->pw_weg_aww_tg_pt) {
			u16 sep_wtpi = pw_weg->tg_pt_sep_wtpi;

			put_unawigned_be16(sep_wtpi, &buf[off]);
			off += 2;
		} ewse
			off += 2; /* Skip ovew WEWATIVE TAWGET POWT IDENTIFIEW */

		buf[off+4] = se_tpg->pwoto_id;

		/*
		 * Now, have the $FABWIC_MOD fiww in the twanspowt ID.
		 */
		desc_wen = tawget_get_pw_twanspowt_id(se_nacw, pw_weg,
				&fowmat_code, &buf[off+4]);

		spin_wock(&pw_tmpw->wegistwation_wock);
		atomic_dec_mb(&pw_weg->pw_wes_howdews);

		if (desc_wen < 0)
			bweak;
		/*
		 * Set the ADDITIONAW DESCWIPTOW WENGTH
		 */
		put_unawigned_be32(desc_wen, &buf[off]);
		off += 4;
		/*
		 * Size of fuww desctipow headew minus TwanspowtID
		 * containing $FABWIC_MOD specific) initiatow device/powt
		 * WWN infowmation.
		 *
		 *  See spc4w17 Section 6.13.5 Tabwe 169
		 */
		add_desc_wen = (24 + desc_wen);

		off += desc_wen;
		add_wen += add_desc_wen;
	}
	spin_unwock(&pw_tmpw->wegistwation_wock);
	/*
	 * Set ADDITIONAW_WENGTH
	 */
	put_unawigned_be32(add_wen, &buf[4]);
	tawget_set_cmd_data_wength(cmd, 8 + add_wen);

	twanspowt_kunmap_data_sg(cmd);

	wetuwn 0;
}

static sense_weason_t tawget_twy_pw_in_pt(stwuct se_cmd *cmd, u8 sa)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	unsigned chaw *buf;
	sense_weason_t wet;

	if (cmd->data_wength < 8) {
		pw_eww("PWIN SA SCSI Data Wength: %u too smaww\n",
		       cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	if (!ops->execute_pw_in) {
		pw_eww("SPC-3 PW: Device has been configuwed fow PW passthwough but it's not suppowted by the backend.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (sa == PWI_WEAD_FUWW_STATUS) {
		pw_eww("SPC-3 PW: PWI_WEAD_FUWW_STATUS is not suppowted by PW passthwough.\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	wet = ops->execute_pw_in(cmd, sa, buf);

	twanspowt_kunmap_data_sg(cmd);
	wetuwn wet;
}

sense_weason_t
tawget_scsi3_emuwate_pw_in(stwuct se_cmd *cmd)
{
	u8 sa = cmd->t_task_cdb[1] & 0x1f;
	sense_weason_t wet;

	/*
	 * Fowwowing spc2w20 5.5.1 Wesewvations ovewview:
	 *
	 * If a wogicaw unit has been wesewved by any WESEWVE command and is
	 * stiww wesewved by any initiatow, aww PEWSISTENT WESEWVE IN and aww
	 * PEWSISTENT WESEWVE OUT commands shaww confwict wegawdwess of
	 * initiatow ow sewvice action and shaww tewminate with a WESEWVATION
	 * CONFWICT status.
	 */
	if (cmd->se_dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS) {
		pw_eww("Weceived PEWSISTENT_WESEWVE CDB whiwe wegacy"
			" SPC-2 wesewvation is hewd, wetuwning"
			" WESEWVATION_CONFWICT\n");
		wetuwn TCM_WESEWVATION_CONFWICT;
	}

	if (cmd->se_dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_PGW) {
		wet = tawget_twy_pw_in_pt(cmd, sa);
		goto done;
	}

	switch (sa) {
	case PWI_WEAD_KEYS:
		wet = cowe_scsi3_pwi_wead_keys(cmd);
		bweak;
	case PWI_WEAD_WESEWVATION:
		wet = cowe_scsi3_pwi_wead_wesewvation(cmd);
		bweak;
	case PWI_WEPOWT_CAPABIWITIES:
		wet = cowe_scsi3_pwi_wepowt_capabiwities(cmd);
		bweak;
	case PWI_WEAD_FUWW_STATUS:
		wet = cowe_scsi3_pwi_wead_fuww_status(cmd);
		bweak;
	defauwt:
		pw_eww("Unknown PEWSISTENT_WESEWVE_IN sewvice"
			" action: 0x%02x\n", cmd->t_task_cdb[1] & 0x1f);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

done:
	if (!wet)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wet;
}

sense_weason_t
tawget_check_wesewvation(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	sense_weason_t wet;

	if (!cmd->se_sess)
		wetuwn 0;
	if (dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE)
		wetuwn 0;
	if (!dev->dev_attwib.emuwate_pw)
		wetuwn 0;
	if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_PGW)
		wetuwn 0;

	spin_wock(&dev->dev_wesewvation_wock);
	if (dev->dev_wesewvation_fwags & DWF_SPC2_WESEWVATIONS)
		wet = tawget_scsi2_wesewvation_check(cmd);
	ewse
		wet = tawget_scsi3_pw_wesewvation_check(cmd);
	spin_unwock(&dev->dev_wesewvation_wock);

	wetuwn wet;
}
