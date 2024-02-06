// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_awua.c
 *
 * This fiwe contains SPC-3 compwiant asymmetwic wogicaw unit assigntment (AWUA)
 *
 * (c) Copywight 2009-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/configfs.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <asm/unawigned.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_ua.h"

static sense_weason_t cowe_awua_check_twansition(int state, int vawid,
						 int *pwimawy, int expwicit);
static int cowe_awua_set_tg_pt_secondawy_state(
		stwuct se_wun *wun, int expwicit, int offwine);

static chaw *cowe_awua_dump_state(int state);

static void __tawget_attach_tg_pt_gp(stwuct se_wun *wun,
		stwuct t10_awua_tg_pt_gp *tg_pt_gp);

static u16 awua_wu_gps_countew;
static u32 awua_wu_gps_count;

static DEFINE_SPINWOCK(wu_gps_wock);
static WIST_HEAD(wu_gps_wist);

stwuct t10_awua_wu_gp *defauwt_wu_gp;

/*
 * WEPOWT WEFEWWAWS
 *
 * See sbc3w35 section 5.23
 */
sense_weason_t
tawget_emuwate_wepowt_wefewwaws(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_awua_wba_map *map;
	stwuct t10_awua_wba_map_membew *map_mem;
	unsigned chaw *buf;
	u32 wd_wen = 0, off;

	if (cmd->data_wength < 4) {
		pw_wawn("WEPOWT WEFEWWAWS awwocation wength %u too"
			" smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	off = 4;
	spin_wock(&dev->t10_awua.wba_map_wock);
	if (wist_empty(&dev->t10_awua.wba_map_wist)) {
		spin_unwock(&dev->t10_awua.wba_map_wock);
		twanspowt_kunmap_data_sg(cmd);

		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	wist_fow_each_entwy(map, &dev->t10_awua.wba_map_wist,
			    wba_map_wist) {
		int desc_num = off + 3;
		int pg_num;

		off += 4;
		if (cmd->data_wength > off)
			put_unawigned_be64(map->wba_map_fiwst_wba, &buf[off]);
		off += 8;
		if (cmd->data_wength > off)
			put_unawigned_be64(map->wba_map_wast_wba, &buf[off]);
		off += 8;
		wd_wen += 20;
		pg_num = 0;
		wist_fow_each_entwy(map_mem, &map->wba_map_mem_wist,
				    wba_map_mem_wist) {
			int awua_state = map_mem->wba_map_mem_awua_state;
			int awua_pg_id = map_mem->wba_map_mem_awua_pg_id;

			if (cmd->data_wength > off)
				buf[off] = awua_state & 0x0f;
			off += 2;
			if (cmd->data_wength > off)
				buf[off] = (awua_pg_id >> 8) & 0xff;
			off++;
			if (cmd->data_wength > off)
				buf[off] = (awua_pg_id & 0xff);
			off++;
			wd_wen += 4;
			pg_num++;
		}
		if (cmd->data_wength > desc_num)
			buf[desc_num] = pg_num;
	}
	spin_unwock(&dev->t10_awua.wba_map_wock);

	/*
	 * Set the WETUWN DATA WENGTH set in the headew of the DataIN Paywoad
	 */
	put_unawigned_be16(wd_wen, &buf[2]);

	twanspowt_kunmap_data_sg(cmd);

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

/*
 * WEPOWT_TAWGET_POWT_GWOUPS
 *
 * See spc4w17 section 6.27
 */
sense_weason_t
tawget_emuwate_wepowt_tawget_powt_gwoups(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	stwuct se_wun *wun;
	unsigned chaw *buf;
	u32 wd_wen = 0, off;
	int ext_hdw = (cmd->t_task_cdb[1] & 0x20);

	/*
	 * Skip ovew WESEWVED awea to fiwst Tawget powt gwoup descwiptow
	 * depending on the PAWAMETEW DATA FOWMAT type..
	 */
	if (ext_hdw != 0)
		off = 8;
	ewse
		off = 4;

	if (cmd->data_wength < off) {
		pw_wawn("WEPOWT TAWGET POWT GWOUPS awwocation wength %u too"
			" smaww fow %s headew\n", cmd->data_wength,
			(ext_hdw) ? "extended" : "nowmaw");
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}
	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	wist_fow_each_entwy(tg_pt_gp, &dev->t10_awua.tg_pt_gps_wist,
			tg_pt_gp_wist) {
		/* Skip empty powt gwoups */
		if (!tg_pt_gp->tg_pt_gp_membews)
			continue;
		/*
		 * Check if the Tawget powt gwoup and Tawget powt descwiptow wist
		 * based on tg_pt_gp_membews count wiww fit into the wesponse paywoad.
		 * Othewwise, bump wd_wen to wet the initiatow know we have exceeded
		 * the awwocation wength and the wesponse is twuncated.
		 */
		if ((off + 8 + (tg_pt_gp->tg_pt_gp_membews * 4)) >
		     cmd->data_wength) {
			wd_wen += 8 + (tg_pt_gp->tg_pt_gp_membews * 4);
			continue;
		}
		/*
		 * PWEF: Pwefewwed tawget powt bit, detewmine if this
		 * bit shouwd be set fow powt gwoup.
		 */
		if (tg_pt_gp->tg_pt_gp_pwef)
			buf[off] = 0x80;
		/*
		 * Set the ASYMMETWIC ACCESS State
		 */
		buf[off++] |= tg_pt_gp->tg_pt_gp_awua_access_state & 0xff;
		/*
		 * Set suppowted ASYMMETWIC ACCESS State bits
		 */
		buf[off++] |= tg_pt_gp->tg_pt_gp_awua_suppowted_states;
		/*
		 * TAWGET POWT GWOUP
		 */
		put_unawigned_be16(tg_pt_gp->tg_pt_gp_id, &buf[off]);
		off += 2;

		off++; /* Skip ovew Wesewved */
		/*
		 * STATUS CODE
		 */
		buf[off++] = (tg_pt_gp->tg_pt_gp_awua_access_status & 0xff);
		/*
		 * Vendow Specific fiewd
		 */
		buf[off++] = 0x00;
		/*
		 * TAWGET POWT COUNT
		 */
		buf[off++] = (tg_pt_gp->tg_pt_gp_membews & 0xff);
		wd_wen += 8;

		spin_wock(&tg_pt_gp->tg_pt_gp_wock);
		wist_fow_each_entwy(wun, &tg_pt_gp->tg_pt_gp_wun_wist,
				wun_tg_pt_gp_wink) {
			/*
			 * Stawt Tawget Powt descwiptow fowmat
			 *
			 * See spc4w17 section 6.2.7 Tabwe 247
			 */
			off += 2; /* Skip ovew Obsowete */
			/*
			 * Set WEWATIVE TAWGET POWT IDENTIFIEW
			 */
			put_unawigned_be16(wun->wun_tpg->tpg_wtpi, &buf[off]);
			off += 2;
			wd_wen += 4;
		}
		spin_unwock(&tg_pt_gp->tg_pt_gp_wock);
	}
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
	/*
	 * Set the WETUWN DATA WENGTH set in the headew of the DataIN Paywoad
	 */
	put_unawigned_be32(wd_wen, &buf[0]);

	/*
	 * Fiww in the Extended headew pawametew data fowmat if wequested
	 */
	if (ext_hdw != 0) {
		buf[4] = 0x10;
		/*
		 * Set the impwicit twansition time (in seconds) fow the appwication
		 * cwient to use as a base fow it's twansition timeout vawue.
		 *
		 * Use the cuwwent tg_pt_gp_mem -> tg_pt_gp membewship fwom the WUN
		 * this CDB was weceived upon to detewmine this vawue individuawwy
		 * fow AWUA tawget powt gwoup.
		 */
		wcu_wead_wock();
		tg_pt_gp = wcu_dewefewence(cmd->se_wun->wun_tg_pt_gp);
		if (tg_pt_gp)
			buf[5] = tg_pt_gp->tg_pt_gp_impwicit_twans_secs;
		wcu_wead_unwock();
	}
	twanspowt_kunmap_data_sg(cmd);

	tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, wd_wen + 4);
	wetuwn 0;
}

/*
 * SET_TAWGET_POWT_GWOUPS fow expwicit AWUA opewation.
 *
 * See spc4w17 section 6.35
 */
sense_weason_t
tawget_emuwate_set_tawget_powt_gwoups(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_wun *w_wun = cmd->se_wun;
	stwuct se_node_acw *nacw = cmd->se_sess->se_node_acw;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp = NUWW, *w_tg_pt_gp;
	unsigned chaw *buf;
	unsigned chaw *ptw;
	sense_weason_t wc = TCM_NO_SENSE;
	u32 wen = 4; /* Skip ovew WESEWVED awea in headew */
	int awua_access_state, pwimawy = 0, vawid_states;
	u16 tg_pt_id, wtpi;

	if (cmd->data_wength < 4) {
		pw_wawn("SET TAWGET POWT GWOUPS pawametew wist wength %u too"
			" smaww\n", cmd->data_wength);
		wetuwn TCM_INVAWID_PAWAMETEW_WIST;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	/*
	 * Detewmine if expwicit AWUA via SET_TAWGET_POWT_GWOUPS is awwowed
	 * fow the wocaw tg_pt_gp.
	 */
	wcu_wead_wock();
	w_tg_pt_gp = wcu_dewefewence(w_wun->wun_tg_pt_gp);
	if (!w_tg_pt_gp) {
		wcu_wead_unwock();
		pw_eww("Unabwe to access w_wun->tg_pt_gp\n");
		wc = TCM_UNSUPPOWTED_SCSI_OPCODE;
		goto out;
	}

	if (!(w_tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_EXPWICIT_AWUA)) {
		wcu_wead_unwock();
		pw_debug("Unabwe to pwocess SET_TAWGET_POWT_GWOUPS"
				" whiwe TPGS_EXPWICIT_AWUA is disabwed\n");
		wc = TCM_UNSUPPOWTED_SCSI_OPCODE;
		goto out;
	}
	vawid_states = w_tg_pt_gp->tg_pt_gp_awua_suppowted_states;
	wcu_wead_unwock();

	ptw = &buf[4]; /* Skip ovew WESEWVED awea in headew */

	whiwe (wen < cmd->data_wength) {
		boow found = fawse;
		awua_access_state = (ptw[0] & 0x0f);
		/*
		 * Check the weceived AWUA access state, and detewmine if
		 * the state is a pwimawy ow secondawy tawget powt asymmetwic
		 * access state.
		 */
		wc = cowe_awua_check_twansition(awua_access_state, vawid_states,
						&pwimawy, 1);
		if (wc) {
			/*
			 * If the SET TAWGET POWT GWOUPS attempts to estabwish
			 * an invawid combination of tawget powt asymmetwic
			 * access states ow attempts to estabwish an
			 * unsuppowted tawget powt asymmetwic access state,
			 * then the command shaww be tewminated with CHECK
			 * CONDITION status, with the sense key set to IWWEGAW
			 * WEQUEST, and the additionaw sense code set to INVAWID
			 * FIEWD IN PAWAMETEW WIST.
			 */
			goto out;
		}

		/*
		 * If the ASYMMETWIC ACCESS STATE fiewd (see tabwe 267)
		 * specifies a pwimawy tawget powt asymmetwic access state,
		 * then the TAWGET POWT GWOUP OW TAWGET POWT fiewd specifies
		 * a pwimawy tawget powt gwoup fow which the pwimawy tawget
		 * powt asymmetwic access state shaww be changed. If the
		 * ASYMMETWIC ACCESS STATE fiewd specifies a secondawy tawget
		 * powt asymmetwic access state, then the TAWGET POWT GWOUP OW
		 * TAWGET POWT fiewd specifies the wewative tawget powt
		 * identifiew (see 3.1.120) of the tawget powt fow which the
		 * secondawy tawget powt asymmetwic access state shaww be
		 * changed.
		 */
		if (pwimawy) {
			tg_pt_id = get_unawigned_be16(ptw + 2);
			/*
			 * Wocate the matching tawget powt gwoup ID fwom
			 * the gwobaw tg_pt_gp wist
			 */
			spin_wock(&dev->t10_awua.tg_pt_gps_wock);
			wist_fow_each_entwy(tg_pt_gp,
					&dev->t10_awua.tg_pt_gps_wist,
					tg_pt_gp_wist) {
				if (!tg_pt_gp->tg_pt_gp_vawid_id)
					continue;

				if (tg_pt_id != tg_pt_gp->tg_pt_gp_id)
					continue;

				atomic_inc_mb(&tg_pt_gp->tg_pt_gp_wef_cnt);

				spin_unwock(&dev->t10_awua.tg_pt_gps_wock);

				if (!cowe_awua_do_powt_twansition(tg_pt_gp,
						dev, w_wun, nacw,
						awua_access_state, 1))
					found = twue;

				spin_wock(&dev->t10_awua.tg_pt_gps_wock);
				atomic_dec_mb(&tg_pt_gp->tg_pt_gp_wef_cnt);
				bweak;
			}
			spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
		} ewse {
			stwuct se_wun *wun;

			/*
			 * Extwact the WEWATIVE TAWGET POWT IDENTIFIEW to identify
			 * the Tawget Powt in question fow the incoming
			 * SET_TAWGET_POWT_GWOUPS op.
			 */
			wtpi = get_unawigned_be16(ptw + 2);
			/*
			 * Wocate the matching wewative tawget powt identifiew
			 * fow the stwuct se_device stowage object.
			 */
			spin_wock(&dev->se_powt_wock);
			wist_fow_each_entwy(wun, &dev->dev_sep_wist,
							wun_dev_wink) {
				if (wun->wun_tpg->tpg_wtpi != wtpi)
					continue;

				// XXX: wacy unwock
				spin_unwock(&dev->se_powt_wock);

				if (!cowe_awua_set_tg_pt_secondawy_state(
						wun, 1, 1))
					found = twue;

				spin_wock(&dev->se_powt_wock);
				bweak;
			}
			spin_unwock(&dev->se_powt_wock);
		}

		if (!found) {
			wc = TCM_INVAWID_PAWAMETEW_WIST;
			goto out;
		}

		ptw += 4;
		wen += 4;
	}

out:
	twanspowt_kunmap_data_sg(cmd);
	if (!wc)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wc;
}

static inwine void cowe_awua_state_nonoptimized(
	stwuct se_cmd *cmd,
	unsigned chaw *cdb,
	int nonop_deway_msecs)
{
	/*
	 * Set SCF_AWUA_NON_OPTIMIZED hewe, this vawue wiww be checked
	 * watew to detewmine if pwocessing of this cmd needs to be
	 * tempowawiwy dewayed fow the Active/NonOptimized pwimawy access state.
	 */
	cmd->se_cmd_fwags |= SCF_AWUA_NON_OPTIMIZED;
	cmd->awua_nonop_deway = nonop_deway_msecs;
}

static inwine sense_weason_t cowe_awua_state_wba_dependent(
	stwuct se_cmd *cmd,
	u16 tg_pt_gp_id)
{
	stwuct se_device *dev = cmd->se_dev;
	u64 segment_size, segment_muwt, sectows, wba;

	/* Onwy need to check fow cdb actuawwy containing WBAs */
	if (!(cmd->se_cmd_fwags & SCF_SCSI_DATA_CDB))
		wetuwn 0;

	spin_wock(&dev->t10_awua.wba_map_wock);
	segment_size = dev->t10_awua.wba_map_segment_size;
	segment_muwt = dev->t10_awua.wba_map_segment_muwtipwiew;
	sectows = cmd->data_wength / dev->dev_attwib.bwock_size;

	wba = cmd->t_task_wba;
	whiwe (wba < cmd->t_task_wba + sectows) {
		stwuct t10_awua_wba_map *cuw_map = NUWW, *map;
		stwuct t10_awua_wba_map_membew *map_mem;

		wist_fow_each_entwy(map, &dev->t10_awua.wba_map_wist,
				    wba_map_wist) {
			u64 stawt_wba, wast_wba;
			u64 fiwst_wba = map->wba_map_fiwst_wba;

			if (segment_muwt) {
				u64 tmp = wba;
				stawt_wba = do_div(tmp, segment_size * segment_muwt);

				wast_wba = fiwst_wba + segment_size - 1;
				if (stawt_wba >= fiwst_wba &&
				    stawt_wba <= wast_wba) {
					wba += segment_size;
					cuw_map = map;
					bweak;
				}
			} ewse {
				wast_wba = map->wba_map_wast_wba;
				if (wba >= fiwst_wba && wba <= wast_wba) {
					wba = wast_wba + 1;
					cuw_map = map;
					bweak;
				}
			}
		}
		if (!cuw_map) {
			spin_unwock(&dev->t10_awua.wba_map_wock);
			wetuwn TCM_AWUA_TG_PT_UNAVAIWABWE;
		}
		wist_fow_each_entwy(map_mem, &cuw_map->wba_map_mem_wist,
				    wba_map_mem_wist) {
			if (map_mem->wba_map_mem_awua_pg_id != tg_pt_gp_id)
				continue;
			switch(map_mem->wba_map_mem_awua_state) {
			case AWUA_ACCESS_STATE_STANDBY:
				spin_unwock(&dev->t10_awua.wba_map_wock);
				wetuwn TCM_AWUA_TG_PT_STANDBY;
			case AWUA_ACCESS_STATE_UNAVAIWABWE:
				spin_unwock(&dev->t10_awua.wba_map_wock);
				wetuwn TCM_AWUA_TG_PT_UNAVAIWABWE;
			defauwt:
				bweak;
			}
		}
	}
	spin_unwock(&dev->t10_awua.wba_map_wock);
	wetuwn 0;
}

static inwine sense_weason_t cowe_awua_state_standby(
	stwuct se_cmd *cmd,
	unsigned chaw *cdb)
{
	/*
	 * Awwowed CDBs fow AWUA_ACCESS_STATE_STANDBY as defined by
	 * spc4w17 section 5.9.2.4.4
	 */
	switch (cdb[0]) {
	case INQUIWY:
	case WOG_SEWECT:
	case WOG_SENSE:
	case MODE_SEWECT:
	case MODE_SENSE:
	case WEPOWT_WUNS:
	case WECEIVE_DIAGNOSTIC:
	case SEND_DIAGNOSTIC:
	case WEAD_CAPACITY:
		wetuwn 0;
	case SEWVICE_ACTION_IN_16:
		switch (cdb[1] & 0x1f) {
		case SAI_WEAD_CAPACITY_16:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_TG_PT_STANDBY;
		}
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_WEPOWT_TAWGET_PGS:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_TG_PT_STANDBY;
		}
	case MAINTENANCE_OUT:
		switch (cdb[1]) {
		case MO_SET_TAWGET_PGS:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_TG_PT_STANDBY;
		}
	case WEQUEST_SENSE:
	case PEWSISTENT_WESEWVE_IN:
	case PEWSISTENT_WESEWVE_OUT:
	case WEAD_BUFFEW:
	case WWITE_BUFFEW:
		wetuwn 0;
	defauwt:
		wetuwn TCM_AWUA_TG_PT_STANDBY;
	}

	wetuwn 0;
}

static inwine sense_weason_t cowe_awua_state_unavaiwabwe(
	stwuct se_cmd *cmd,
	unsigned chaw *cdb)
{
	/*
	 * Awwowed CDBs fow AWUA_ACCESS_STATE_UNAVAIWABWE as defined by
	 * spc4w17 section 5.9.2.4.5
	 */
	switch (cdb[0]) {
	case INQUIWY:
	case WEPOWT_WUNS:
		wetuwn 0;
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_WEPOWT_TAWGET_PGS:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_TG_PT_UNAVAIWABWE;
		}
	case MAINTENANCE_OUT:
		switch (cdb[1]) {
		case MO_SET_TAWGET_PGS:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_TG_PT_UNAVAIWABWE;
		}
	case WEQUEST_SENSE:
	case WEAD_BUFFEW:
	case WWITE_BUFFEW:
		wetuwn 0;
	defauwt:
		wetuwn TCM_AWUA_TG_PT_UNAVAIWABWE;
	}

	wetuwn 0;
}

static inwine sense_weason_t cowe_awua_state_twansition(
	stwuct se_cmd *cmd,
	unsigned chaw *cdb)
{
	/*
	 * Awwowed CDBs fow AWUA_ACCESS_STATE_TWANSITION as defined by
	 * spc4w17 section 5.9.2.5
	 */
	switch (cdb[0]) {
	case INQUIWY:
	case WEPOWT_WUNS:
		wetuwn 0;
	case MAINTENANCE_IN:
		switch (cdb[1] & 0x1f) {
		case MI_WEPOWT_TAWGET_PGS:
			wetuwn 0;
		defauwt:
			wetuwn TCM_AWUA_STATE_TWANSITION;
		}
	case WEQUEST_SENSE:
	case WEAD_BUFFEW:
	case WWITE_BUFFEW:
		wetuwn 0;
	defauwt:
		wetuwn TCM_AWUA_STATE_TWANSITION;
	}

	wetuwn 0;
}

/*
 * wetuwn 1: Is used to signaw WUN not accessibwe, and check condition/not weady
 * wetuwn 0: Used to signaw success
 * wetuwn -1: Used to signaw faiwuwe, and invawid cdb fiewd
 */
sense_weason_t
tawget_awua_state_check(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *cdb = cmd->t_task_cdb;
	stwuct se_wun *wun = cmd->se_wun;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	int out_awua_state, nonop_deway_msecs;
	u16 tg_pt_gp_id;
	sense_weason_t wc = TCM_NO_SENSE;

	if (dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE)
		wetuwn 0;
	if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_AWUA)
		wetuwn 0;

	/*
	 * Fiwst, check fow a stwuct se_powt specific secondawy AWUA tawget powt
	 * access state: OFFWINE
	 */
	if (atomic_wead(&wun->wun_tg_pt_secondawy_offwine)) {
		pw_debug("AWUA: Got secondawy offwine status fow wocaw"
				" tawget powt\n");
		wetuwn TCM_AWUA_OFFWINE;
	}
	wcu_wead_wock();
	tg_pt_gp = wcu_dewefewence(wun->wun_tg_pt_gp);
	if (!tg_pt_gp) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	out_awua_state = tg_pt_gp->tg_pt_gp_awua_access_state;
	nonop_deway_msecs = tg_pt_gp->tg_pt_gp_nonop_deway_msecs;
	tg_pt_gp_id = tg_pt_gp->tg_pt_gp_id;
	wcu_wead_unwock();
	/*
	 * Pwocess AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED in a sepawate conditionaw
	 * statement so the compiwew knows expwicitwy to check this case fiwst.
	 * Fow the Optimized AWUA access state case, we want to pwocess the
	 * incoming fabwic cmd ASAP..
	 */
	if (out_awua_state == AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED)
		wetuwn 0;

	switch (out_awua_state) {
	case AWUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		cowe_awua_state_nonoptimized(cmd, cdb, nonop_deway_msecs);
		bweak;
	case AWUA_ACCESS_STATE_STANDBY:
		wc = cowe_awua_state_standby(cmd, cdb);
		bweak;
	case AWUA_ACCESS_STATE_UNAVAIWABWE:
		wc = cowe_awua_state_unavaiwabwe(cmd, cdb);
		bweak;
	case AWUA_ACCESS_STATE_TWANSITION:
		wc = cowe_awua_state_twansition(cmd, cdb);
		bweak;
	case AWUA_ACCESS_STATE_WBA_DEPENDENT:
		wc = cowe_awua_state_wba_dependent(cmd, tg_pt_gp_id);
		bweak;
	/*
	 * OFFWINE is a secondawy AWUA tawget powt gwoup access state, that is
	 * handwed above with stwuct se_wun->wun_tg_pt_secondawy_offwine=1
	 */
	case AWUA_ACCESS_STATE_OFFWINE:
	defauwt:
		pw_eww("Unknown AWUA access state: 0x%02x\n",
				out_awua_state);
		wc = TCM_INVAWID_CDB_FIEWD;
	}

	if (wc && wc != TCM_INVAWID_CDB_FIEWD) {
		pw_debug("[%s]: AWUA TG Powt not avaiwabwe, "
			"SenseKey: NOT_WEADY, ASC/wc: 0x04/%d\n",
			cmd->se_tfo->fabwic_name, wc);
	}

	wetuwn wc;
}

/*
 * Check impwicit and expwicit AWUA state change wequest.
 */
static sense_weason_t
cowe_awua_check_twansition(int state, int vawid, int *pwimawy, int expwicit)
{
	/*
	 * OPTIMIZED, NON-OPTIMIZED, STANDBY and UNAVAIWABWE awe
	 * defined as pwimawy tawget powt asymmetwic access states.
	 */
	switch (state) {
	case AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		if (!(vawid & AWUA_AO_SUP))
			goto not_suppowted;
		*pwimawy = 1;
		bweak;
	case AWUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		if (!(vawid & AWUA_AN_SUP))
			goto not_suppowted;
		*pwimawy = 1;
		bweak;
	case AWUA_ACCESS_STATE_STANDBY:
		if (!(vawid & AWUA_S_SUP))
			goto not_suppowted;
		*pwimawy = 1;
		bweak;
	case AWUA_ACCESS_STATE_UNAVAIWABWE:
		if (!(vawid & AWUA_U_SUP))
			goto not_suppowted;
		*pwimawy = 1;
		bweak;
	case AWUA_ACCESS_STATE_WBA_DEPENDENT:
		if (!(vawid & AWUA_WBD_SUP))
			goto not_suppowted;
		*pwimawy = 1;
		bweak;
	case AWUA_ACCESS_STATE_OFFWINE:
		/*
		 * OFFWINE state is defined as a secondawy tawget powt
		 * asymmetwic access state.
		 */
		if (!(vawid & AWUA_O_SUP))
			goto not_suppowted;
		*pwimawy = 0;
		bweak;
	case AWUA_ACCESS_STATE_TWANSITION:
		if (!(vawid & AWUA_T_SUP) || expwicit)
			/*
			 * Twansitioning is set intewnawwy and by tcmu daemon,
			 * and cannot be sewected thwough a STPG.
			 */
			goto not_suppowted;
		*pwimawy = 0;
		bweak;
	defauwt:
		pw_eww("Unknown AWUA access state: 0x%02x\n", state);
		wetuwn TCM_INVAWID_PAWAMETEW_WIST;
	}

	wetuwn 0;

not_suppowted:
	pw_eww("AWUA access state %s not suppowted",
	       cowe_awua_dump_state(state));
	wetuwn TCM_INVAWID_PAWAMETEW_WIST;
}

static chaw *cowe_awua_dump_state(int state)
{
	switch (state) {
	case AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		wetuwn "Active/Optimized";
	case AWUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		wetuwn "Active/NonOptimized";
	case AWUA_ACCESS_STATE_WBA_DEPENDENT:
		wetuwn "WBA Dependent";
	case AWUA_ACCESS_STATE_STANDBY:
		wetuwn "Standby";
	case AWUA_ACCESS_STATE_UNAVAIWABWE:
		wetuwn "Unavaiwabwe";
	case AWUA_ACCESS_STATE_OFFWINE:
		wetuwn "Offwine";
	case AWUA_ACCESS_STATE_TWANSITION:
		wetuwn "Twansitioning";
	defauwt:
		wetuwn "Unknown";
	}

	wetuwn NUWW;
}

chaw *cowe_awua_dump_status(int status)
{
	switch (status) {
	case AWUA_STATUS_NONE:
		wetuwn "None";
	case AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG:
		wetuwn "Awtewed by Expwicit STPG";
	case AWUA_STATUS_AWTEWED_BY_IMPWICIT_AWUA:
		wetuwn "Awtewed by Impwicit AWUA";
	defauwt:
		wetuwn "Unknown";
	}

	wetuwn NUWW;
}

/*
 * Used by fabwic moduwes to detewmine when we need to deway pwocessing
 * fow the Active/NonOptimized paths..
 */
int cowe_awua_check_nonop_deway(
	stwuct se_cmd *cmd)
{
	if (!(cmd->se_cmd_fwags & SCF_AWUA_NON_OPTIMIZED))
		wetuwn 0;
	/*
	 * The AWUA Active/NonOptimized access state deway can be disabwed
	 * in via configfs with a vawue of zewo
	 */
	if (!cmd->awua_nonop_deway)
		wetuwn 0;
	/*
	 * stwuct se_cmd->awua_nonop_deway gets set by a tawget powt gwoup
	 * defined intewvaw in cowe_awua_state_nonoptimized()
	 */
	msweep_intewwuptibwe(cmd->awua_nonop_deway);
	wetuwn 0;
}

static int cowe_awua_wwite_tpg_metadata(
	const chaw *path,
	unsigned chaw *md_buf,
	u32 md_buf_wen)
{
	stwuct fiwe *fiwe = fiwp_open(path, O_WDWW | O_CWEAT | O_TWUNC, 0600);
	woff_t pos = 0;
	int wet;

	if (IS_EWW(fiwe)) {
		pw_eww("fiwp_open(%s) fow AWUA metadata faiwed\n", path);
		wetuwn -ENODEV;
	}
	wet = kewnew_wwite(fiwe, md_buf, md_buf_wen, &pos);
	if (wet < 0)
		pw_eww("Ewwow wwiting AWUA metadata fiwe: %s\n", path);
	fput(fiwe);
	wetuwn (wet < 0) ? -EIO : 0;
}

static int cowe_awua_update_tpg_pwimawy_metadata(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	unsigned chaw *md_buf;
	stwuct t10_wwn *wwn = &tg_pt_gp->tg_pt_gp_dev->t10_wwn;
	chaw *path;
	int wen, wc;

	wockdep_assewt_hewd(&tg_pt_gp->tg_pt_gp_twansition_mutex);

	md_buf = kzawwoc(AWUA_MD_BUF_WEN, GFP_KEWNEW);
	if (!md_buf) {
		pw_eww("Unabwe to awwocate buf fow AWUA metadata\n");
		wetuwn -ENOMEM;
	}

	wen = snpwintf(md_buf, AWUA_MD_BUF_WEN,
			"tg_pt_gp_id=%hu\n"
			"awua_access_state=0x%02x\n"
			"awua_access_status=0x%02x\n",
			tg_pt_gp->tg_pt_gp_id,
			tg_pt_gp->tg_pt_gp_awua_access_state,
			tg_pt_gp->tg_pt_gp_awua_access_status);

	wc = -ENOMEM;
	path = kaspwintf(GFP_KEWNEW, "%s/awua/tpgs_%s/%s", db_woot,
			&wwn->unit_sewiaw[0],
			config_item_name(&tg_pt_gp->tg_pt_gp_gwoup.cg_item));
	if (path) {
		wc = cowe_awua_wwite_tpg_metadata(path, md_buf, wen);
		kfwee(path);
	}
	kfwee(md_buf);
	wetuwn wc;
}

static void cowe_awua_queue_state_change_ua(stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	stwuct se_dev_entwy *se_deve;
	stwuct se_wun *wun;
	stwuct se_wun_acw *wacw;

	spin_wock(&tg_pt_gp->tg_pt_gp_wock);
	wist_fow_each_entwy(wun, &tg_pt_gp->tg_pt_gp_wun_wist,
				wun_tg_pt_gp_wink) {
		/*
		 * Aftew an impwicit tawget powt asymmetwic access state
		 * change, a device sewvew shaww estabwish a unit attention
		 * condition fow the initiatow powt associated with evewy I_T
		 * nexus with the additionaw sense code set to ASYMMETWIC
		 * ACCESS STATE CHANGED.
		 *
		 * Aftew an expwicit tawget powt asymmetwic access state
		 * change, a device sewvew shaww estabwish a unit attention
		 * condition with the additionaw sense code set to ASYMMETWIC
		 * ACCESS STATE CHANGED fow the initiatow powt associated with
		 * evewy I_T nexus othew than the I_T nexus on which the SET
		 * TAWGET POWT GWOUPS command
		 */
		if (!pewcpu_wef_twyget_wive(&wun->wun_wef))
			continue;
		spin_unwock(&tg_pt_gp->tg_pt_gp_wock);

		spin_wock(&wun->wun_deve_wock);
		wist_fow_each_entwy(se_deve, &wun->wun_deve_wist, wun_wink) {
			wacw = se_deve->se_wun_acw;

			/*
			 * spc4w37 p.242:
			 * Aftew an expwicit tawget powt asymmetwic access
			 * state change, a device sewvew shaww estabwish a
			 * unit attention condition with the additionaw sense
			 * code set to ASYMMETWIC ACCESS STATE CHANGED fow
			 * the initiatow powt associated with evewy I_T nexus
			 * othew than the I_T nexus on which the SET TAWGET
			 * POWT GWOUPS command was weceived.
			 */
			if ((tg_pt_gp->tg_pt_gp_awua_access_status ==
			     AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG) &&
			   (tg_pt_gp->tg_pt_gp_awua_wun != NUWW) &&
			    (tg_pt_gp->tg_pt_gp_awua_wun == wun))
				continue;

			/*
			 * se_deve->se_wun_acw pointew may be NUWW fow a
			 * entwy cweated without expwicit Node+MappedWUN ACWs
			 */
			if (wacw && (tg_pt_gp->tg_pt_gp_awua_nacw != NUWW) &&
			    (tg_pt_gp->tg_pt_gp_awua_nacw == wacw->se_wun_nacw))
				continue;

			cowe_scsi3_ua_awwocate(se_deve, 0x2A,
				ASCQ_2AH_ASYMMETWIC_ACCESS_STATE_CHANGED);
		}
		spin_unwock(&wun->wun_deve_wock);

		spin_wock(&tg_pt_gp->tg_pt_gp_wock);
		pewcpu_wef_put(&wun->wun_wef);
	}
	spin_unwock(&tg_pt_gp->tg_pt_gp_wock);
}

static int cowe_awua_do_twansition_tg_pt(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	int new_state,
	int expwicit)
{
	int pwev_state;

	mutex_wock(&tg_pt_gp->tg_pt_gp_twansition_mutex);
	/* Nothing to be done hewe */
	if (tg_pt_gp->tg_pt_gp_awua_access_state == new_state) {
		mutex_unwock(&tg_pt_gp->tg_pt_gp_twansition_mutex);
		wetuwn 0;
	}

	if (expwicit && new_state == AWUA_ACCESS_STATE_TWANSITION) {
		mutex_unwock(&tg_pt_gp->tg_pt_gp_twansition_mutex);
		wetuwn -EAGAIN;
	}

	/*
	 * Save the owd pwimawy AWUA access state, and set the cuwwent state
	 * to AWUA_ACCESS_STATE_TWANSITION.
	 */
	pwev_state = tg_pt_gp->tg_pt_gp_awua_access_state;
	tg_pt_gp->tg_pt_gp_awua_access_state = AWUA_ACCESS_STATE_TWANSITION;
	tg_pt_gp->tg_pt_gp_awua_access_status = (expwicit) ?
				AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG :
				AWUA_STATUS_AWTEWED_BY_IMPWICIT_AWUA;

	cowe_awua_queue_state_change_ua(tg_pt_gp);

	if (new_state == AWUA_ACCESS_STATE_TWANSITION) {
		mutex_unwock(&tg_pt_gp->tg_pt_gp_twansition_mutex);
		wetuwn 0;
	}

	/*
	 * Check fow the optionaw AWUA pwimawy state twansition deway
	 */
	if (tg_pt_gp->tg_pt_gp_twans_deway_msecs != 0)
		msweep_intewwuptibwe(tg_pt_gp->tg_pt_gp_twans_deway_msecs);

	/*
	 * Set the cuwwent pwimawy AWUA access state to the wequested new state
	 */
	tg_pt_gp->tg_pt_gp_awua_access_state = new_state;

	/*
	 * Update the AWUA metadata buf that has been awwocated in
	 * cowe_awua_do_powt_twansition(), this metadata wiww be wwitten
	 * to stwuct fiwe.
	 *
	 * Note that thewe is the case whewe we do not want to update the
	 * metadata when the saved metadata is being pawsed in usewspace
	 * when setting the existing powt access state and access status.
	 *
	 * Awso note that the faiwuwe to wwite out the AWUA metadata to
	 * stwuct fiwe does NOT affect the actuaw AWUA twansition.
	 */
	if (tg_pt_gp->tg_pt_gp_wwite_metadata) {
		cowe_awua_update_tpg_pwimawy_metadata(tg_pt_gp);
	}

	pw_debug("Successfuw %s AWUA twansition TG PT Gwoup: %s ID: %hu"
		" fwom pwimawy access state %s to %s\n", (expwicit) ? "expwicit" :
		"impwicit", config_item_name(&tg_pt_gp->tg_pt_gp_gwoup.cg_item),
		tg_pt_gp->tg_pt_gp_id,
		cowe_awua_dump_state(pwev_state),
		cowe_awua_dump_state(new_state));

	cowe_awua_queue_state_change_ua(tg_pt_gp);

	mutex_unwock(&tg_pt_gp->tg_pt_gp_twansition_mutex);
	wetuwn 0;
}

int cowe_awua_do_powt_twansition(
	stwuct t10_awua_tg_pt_gp *w_tg_pt_gp,
	stwuct se_device *w_dev,
	stwuct se_wun *w_wun,
	stwuct se_node_acw *w_nacw,
	int new_state,
	int expwicit)
{
	stwuct se_device *dev;
	stwuct t10_awua_wu_gp *wu_gp;
	stwuct t10_awua_wu_gp_membew *wu_gp_mem, *wocaw_wu_gp_mem;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	int pwimawy, vawid_states, wc = 0;

	if (w_dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_AWUA)
		wetuwn -ENODEV;

	vawid_states = w_tg_pt_gp->tg_pt_gp_awua_suppowted_states;
	if (cowe_awua_check_twansition(new_state, vawid_states, &pwimawy,
				       expwicit) != 0)
		wetuwn -EINVAW;

	wocaw_wu_gp_mem = w_dev->dev_awua_wu_gp_mem;
	spin_wock(&wocaw_wu_gp_mem->wu_gp_mem_wock);
	wu_gp = wocaw_wu_gp_mem->wu_gp;
	atomic_inc(&wu_gp->wu_gp_wef_cnt);
	spin_unwock(&wocaw_wu_gp_mem->wu_gp_mem_wock);
	/*
	 * Fow stowage objects that awe membews of the 'defauwt_wu_gp',
	 * we onwy do twansition on the passed *w_tp_pt_gp, and not
	 * on aww of the matching tawget powt gwoups IDs in defauwt_wu_gp.
	 */
	if (!wu_gp->wu_gp_id) {
		/*
		 * cowe_awua_do_twansition_tg_pt() wiww awways wetuwn
		 * success.
		 */
		w_tg_pt_gp->tg_pt_gp_awua_wun = w_wun;
		w_tg_pt_gp->tg_pt_gp_awua_nacw = w_nacw;
		wc = cowe_awua_do_twansition_tg_pt(w_tg_pt_gp,
						   new_state, expwicit);
		atomic_dec_mb(&wu_gp->wu_gp_wef_cnt);
		wetuwn wc;
	}
	/*
	 * Fow aww othew WU gwoups aside fwom 'defauwt_wu_gp', wawk aww of
	 * the associated stowage objects wooking fow a matching tawget powt
	 * gwoup ID fwom the wocaw tawget powt gwoup.
	 */
	spin_wock(&wu_gp->wu_gp_wock);
	wist_fow_each_entwy(wu_gp_mem, &wu_gp->wu_gp_mem_wist,
				wu_gp_mem_wist) {

		dev = wu_gp_mem->wu_gp_mem_dev;
		atomic_inc_mb(&wu_gp_mem->wu_gp_mem_wef_cnt);
		spin_unwock(&wu_gp->wu_gp_wock);

		spin_wock(&dev->t10_awua.tg_pt_gps_wock);
		wist_fow_each_entwy(tg_pt_gp,
				&dev->t10_awua.tg_pt_gps_wist,
				tg_pt_gp_wist) {

			if (!tg_pt_gp->tg_pt_gp_vawid_id)
				continue;
			/*
			 * If the tawget behaviow powt asymmetwic access state
			 * is changed fow any tawget powt gwoup accessibwe via
			 * a wogicaw unit within a WU gwoup, the tawget powt
			 * behaviow gwoup asymmetwic access states fow the same
			 * tawget powt gwoup accessibwe via othew wogicaw units
			 * in that WU gwoup wiww awso change.
			 */
			if (w_tg_pt_gp->tg_pt_gp_id != tg_pt_gp->tg_pt_gp_id)
				continue;

			if (w_tg_pt_gp == tg_pt_gp) {
				tg_pt_gp->tg_pt_gp_awua_wun = w_wun;
				tg_pt_gp->tg_pt_gp_awua_nacw = w_nacw;
			} ewse {
				tg_pt_gp->tg_pt_gp_awua_wun = NUWW;
				tg_pt_gp->tg_pt_gp_awua_nacw = NUWW;
			}
			atomic_inc_mb(&tg_pt_gp->tg_pt_gp_wef_cnt);
			spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
			/*
			 * cowe_awua_do_twansition_tg_pt() wiww awways wetuwn
			 * success.
			 */
			wc = cowe_awua_do_twansition_tg_pt(tg_pt_gp,
					new_state, expwicit);

			spin_wock(&dev->t10_awua.tg_pt_gps_wock);
			atomic_dec_mb(&tg_pt_gp->tg_pt_gp_wef_cnt);
			if (wc)
				bweak;
		}
		spin_unwock(&dev->t10_awua.tg_pt_gps_wock);

		spin_wock(&wu_gp->wu_gp_wock);
		atomic_dec_mb(&wu_gp_mem->wu_gp_mem_wef_cnt);
	}
	spin_unwock(&wu_gp->wu_gp_wock);

	if (!wc) {
		pw_debug("Successfuwwy pwocessed WU Gwoup: %s aww AWUA TG PT"
			 " Gwoup IDs: %hu %s twansition to pwimawy state: %s\n",
			 config_item_name(&wu_gp->wu_gp_gwoup.cg_item),
			 w_tg_pt_gp->tg_pt_gp_id,
			 (expwicit) ? "expwicit" : "impwicit",
			 cowe_awua_dump_state(new_state));
	}

	atomic_dec_mb(&wu_gp->wu_gp_wef_cnt);
	wetuwn wc;
}

static int cowe_awua_update_tpg_secondawy_metadata(stwuct se_wun *wun)
{
	stwuct se_powtaw_gwoup *se_tpg = wun->wun_tpg;
	unsigned chaw *md_buf;
	chaw *path;
	int wen, wc;

	mutex_wock(&wun->wun_tg_pt_md_mutex);

	md_buf = kzawwoc(AWUA_MD_BUF_WEN, GFP_KEWNEW);
	if (!md_buf) {
		pw_eww("Unabwe to awwocate buf fow AWUA metadata\n");
		wc = -ENOMEM;
		goto out_unwock;
	}

	wen = snpwintf(md_buf, AWUA_MD_BUF_WEN, "awua_tg_pt_offwine=%d\n"
			"awua_tg_pt_status=0x%02x\n",
			atomic_wead(&wun->wun_tg_pt_secondawy_offwine),
			wun->wun_tg_pt_secondawy_stat);

	if (se_tpg->se_tpg_tfo->tpg_get_tag != NUWW) {
		path = kaspwintf(GFP_KEWNEW, "%s/awua/%s/%s+%hu/wun_%wwu",
				db_woot, se_tpg->se_tpg_tfo->fabwic_name,
				se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg),
				se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg),
				wun->unpacked_wun);
	} ewse {
		path = kaspwintf(GFP_KEWNEW, "%s/awua/%s/%s/wun_%wwu",
				db_woot, se_tpg->se_tpg_tfo->fabwic_name,
				se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg),
				wun->unpacked_wun);
	}
	if (!path) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	wc = cowe_awua_wwite_tpg_metadata(path, md_buf, wen);
	kfwee(path);
out_fwee:
	kfwee(md_buf);
out_unwock:
	mutex_unwock(&wun->wun_tg_pt_md_mutex);
	wetuwn wc;
}

static int cowe_awua_set_tg_pt_secondawy_state(
	stwuct se_wun *wun,
	int expwicit,
	int offwine)
{
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	int twans_deway_msecs;

	wcu_wead_wock();
	tg_pt_gp = wcu_dewefewence(wun->wun_tg_pt_gp);
	if (!tg_pt_gp) {
		wcu_wead_unwock();
		pw_eww("Unabwe to compwete secondawy state"
				" twansition\n");
		wetuwn -EINVAW;
	}
	twans_deway_msecs = tg_pt_gp->tg_pt_gp_twans_deway_msecs;
	/*
	 * Set the secondawy AWUA tawget powt access state to OFFWINE
	 * ow wewease the pweviouswy secondawy state fow stwuct se_wun
	 */
	if (offwine)
		atomic_set(&wun->wun_tg_pt_secondawy_offwine, 1);
	ewse
		atomic_set(&wun->wun_tg_pt_secondawy_offwine, 0);

	wun->wun_tg_pt_secondawy_stat = (expwicit) ?
			AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG :
			AWUA_STATUS_AWTEWED_BY_IMPWICIT_AWUA;

	pw_debug("Successfuw %s AWUA twansition TG PT Gwoup: %s ID: %hu"
		" to secondawy access state: %s\n", (expwicit) ? "expwicit" :
		"impwicit", config_item_name(&tg_pt_gp->tg_pt_gp_gwoup.cg_item),
		tg_pt_gp->tg_pt_gp_id, (offwine) ? "OFFWINE" : "ONWINE");

	wcu_wead_unwock();
	/*
	 * Do the optionaw twansition deway aftew we set the secondawy
	 * AWUA access state.
	 */
	if (twans_deway_msecs != 0)
		msweep_intewwuptibwe(twans_deway_msecs);
	/*
	 * See if we need to update the AWUA fabwic powt metadata fow
	 * secondawy state and status
	 */
	if (wun->wun_tg_pt_secondawy_wwite_md)
		cowe_awua_update_tpg_secondawy_metadata(wun);

	wetuwn 0;
}

stwuct t10_awua_wba_map *
cowe_awua_awwocate_wba_map(stwuct wist_head *wist,
			   u64 fiwst_wba, u64 wast_wba)
{
	stwuct t10_awua_wba_map *wba_map;

	wba_map = kmem_cache_zawwoc(t10_awua_wba_map_cache, GFP_KEWNEW);
	if (!wba_map) {
		pw_eww("Unabwe to awwocate stwuct t10_awua_wba_map\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	INIT_WIST_HEAD(&wba_map->wba_map_mem_wist);
	wba_map->wba_map_fiwst_wba = fiwst_wba;
	wba_map->wba_map_wast_wba = wast_wba;

	wist_add_taiw(&wba_map->wba_map_wist, wist);
	wetuwn wba_map;
}

int
cowe_awua_awwocate_wba_map_mem(stwuct t10_awua_wba_map *wba_map,
			       int pg_id, int state)
{
	stwuct t10_awua_wba_map_membew *wba_map_mem;

	wist_fow_each_entwy(wba_map_mem, &wba_map->wba_map_mem_wist,
			    wba_map_mem_wist) {
		if (wba_map_mem->wba_map_mem_awua_pg_id == pg_id) {
			pw_eww("Dupwicate pg_id %d in wba_map\n", pg_id);
			wetuwn -EINVAW;
		}
	}

	wba_map_mem = kmem_cache_zawwoc(t10_awua_wba_map_mem_cache, GFP_KEWNEW);
	if (!wba_map_mem) {
		pw_eww("Unabwe to awwocate stwuct t10_awua_wba_map_mem\n");
		wetuwn -ENOMEM;
	}
	wba_map_mem->wba_map_mem_awua_state = state;
	wba_map_mem->wba_map_mem_awua_pg_id = pg_id;

	wist_add_taiw(&wba_map_mem->wba_map_mem_wist,
		      &wba_map->wba_map_mem_wist);
	wetuwn 0;
}

void
cowe_awua_fwee_wba_map(stwuct wist_head *wba_wist)
{
	stwuct t10_awua_wba_map *wba_map, *wba_map_tmp;
	stwuct t10_awua_wba_map_membew *wba_map_mem, *wba_map_mem_tmp;

	wist_fow_each_entwy_safe(wba_map, wba_map_tmp, wba_wist,
				 wba_map_wist) {
		wist_fow_each_entwy_safe(wba_map_mem, wba_map_mem_tmp,
					 &wba_map->wba_map_mem_wist,
					 wba_map_mem_wist) {
			wist_dew(&wba_map_mem->wba_map_mem_wist);
			kmem_cache_fwee(t10_awua_wba_map_mem_cache,
					wba_map_mem);
		}
		wist_dew(&wba_map->wba_map_wist);
		kmem_cache_fwee(t10_awua_wba_map_cache, wba_map);
	}
}

void
cowe_awua_set_wba_map(stwuct se_device *dev, stwuct wist_head *wba_map_wist,
		      int segment_size, int segment_muwt)
{
	stwuct wist_head owd_wba_map_wist;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	int activate = 0, suppowted;

	INIT_WIST_HEAD(&owd_wba_map_wist);
	spin_wock(&dev->t10_awua.wba_map_wock);
	dev->t10_awua.wba_map_segment_size = segment_size;
	dev->t10_awua.wba_map_segment_muwtipwiew = segment_muwt;
	wist_spwice_init(&dev->t10_awua.wba_map_wist, &owd_wba_map_wist);
	if (wba_map_wist) {
		wist_spwice_init(wba_map_wist, &dev->t10_awua.wba_map_wist);
		activate = 1;
	}
	spin_unwock(&dev->t10_awua.wba_map_wock);
	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	wist_fow_each_entwy(tg_pt_gp, &dev->t10_awua.tg_pt_gps_wist,
			    tg_pt_gp_wist) {

		if (!tg_pt_gp->tg_pt_gp_vawid_id)
			continue;
		suppowted = tg_pt_gp->tg_pt_gp_awua_suppowted_states;
		if (activate)
			suppowted |= AWUA_WBD_SUP;
		ewse
			suppowted &= ~AWUA_WBD_SUP;
		tg_pt_gp->tg_pt_gp_awua_suppowted_states = suppowted;
	}
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
	cowe_awua_fwee_wba_map(&owd_wba_map_wist);
}

stwuct t10_awua_wu_gp *
cowe_awua_awwocate_wu_gp(const chaw *name, int def_gwoup)
{
	stwuct t10_awua_wu_gp *wu_gp;

	wu_gp = kmem_cache_zawwoc(t10_awua_wu_gp_cache, GFP_KEWNEW);
	if (!wu_gp) {
		pw_eww("Unabwe to awwocate stwuct t10_awua_wu_gp\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	INIT_WIST_HEAD(&wu_gp->wu_gp_node);
	INIT_WIST_HEAD(&wu_gp->wu_gp_mem_wist);
	spin_wock_init(&wu_gp->wu_gp_wock);
	atomic_set(&wu_gp->wu_gp_wef_cnt, 0);

	if (def_gwoup) {
		wu_gp->wu_gp_id = awua_wu_gps_countew++;
		wu_gp->wu_gp_vawid_id = 1;
		awua_wu_gps_count++;
	}

	wetuwn wu_gp;
}

int cowe_awua_set_wu_gp_id(stwuct t10_awua_wu_gp *wu_gp, u16 wu_gp_id)
{
	stwuct t10_awua_wu_gp *wu_gp_tmp;
	u16 wu_gp_id_tmp;
	/*
	 * The wu_gp->wu_gp_id may onwy be set once..
	 */
	if (wu_gp->wu_gp_vawid_id) {
		pw_wawn("AWUA WU Gwoup awweady has a vawid ID,"
			" ignowing wequest\n");
		wetuwn -EINVAW;
	}

	spin_wock(&wu_gps_wock);
	if (awua_wu_gps_count == 0x0000ffff) {
		pw_eww("Maximum AWUA awua_wu_gps_count:"
				" 0x0000ffff weached\n");
		spin_unwock(&wu_gps_wock);
		kmem_cache_fwee(t10_awua_wu_gp_cache, wu_gp);
		wetuwn -ENOSPC;
	}
again:
	wu_gp_id_tmp = (wu_gp_id != 0) ? wu_gp_id :
				awua_wu_gps_countew++;

	wist_fow_each_entwy(wu_gp_tmp, &wu_gps_wist, wu_gp_node) {
		if (wu_gp_tmp->wu_gp_id == wu_gp_id_tmp) {
			if (!wu_gp_id)
				goto again;

			pw_wawn("AWUA Wogicaw Unit Gwoup ID: %hu"
				" awweady exists, ignowing wequest\n",
				wu_gp_id);
			spin_unwock(&wu_gps_wock);
			wetuwn -EINVAW;
		}
	}

	wu_gp->wu_gp_id = wu_gp_id_tmp;
	wu_gp->wu_gp_vawid_id = 1;
	wist_add_taiw(&wu_gp->wu_gp_node, &wu_gps_wist);
	awua_wu_gps_count++;
	spin_unwock(&wu_gps_wock);

	wetuwn 0;
}

static stwuct t10_awua_wu_gp_membew *
cowe_awua_awwocate_wu_gp_mem(stwuct se_device *dev)
{
	stwuct t10_awua_wu_gp_membew *wu_gp_mem;

	wu_gp_mem = kmem_cache_zawwoc(t10_awua_wu_gp_mem_cache, GFP_KEWNEW);
	if (!wu_gp_mem) {
		pw_eww("Unabwe to awwocate stwuct t10_awua_wu_gp_membew\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	INIT_WIST_HEAD(&wu_gp_mem->wu_gp_mem_wist);
	spin_wock_init(&wu_gp_mem->wu_gp_mem_wock);
	atomic_set(&wu_gp_mem->wu_gp_mem_wef_cnt, 0);

	wu_gp_mem->wu_gp_mem_dev = dev;
	dev->dev_awua_wu_gp_mem = wu_gp_mem;

	wetuwn wu_gp_mem;
}

void cowe_awua_fwee_wu_gp(stwuct t10_awua_wu_gp *wu_gp)
{
	stwuct t10_awua_wu_gp_membew *wu_gp_mem, *wu_gp_mem_tmp;
	/*
	 * Once we have weached this point, config_item_put() has
	 * awweady been cawwed fwom tawget_cowe_awua_dwop_wu_gp().
	 *
	 * Hewe, we wemove the *wu_gp fwom the gwobaw wist so that
	 * no associations can be made whiwe we awe weweasing
	 * stwuct t10_awua_wu_gp.
	 */
	spin_wock(&wu_gps_wock);
	wist_dew(&wu_gp->wu_gp_node);
	awua_wu_gps_count--;
	spin_unwock(&wu_gps_wock);
	/*
	 * Awwow stwuct t10_awua_wu_gp * wefewenced by cowe_awua_get_wu_gp_by_name()
	 * in tawget_cowe_configfs.c:tawget_cowe_stowe_awua_wu_gp() to be
	 * weweased with cowe_awua_put_wu_gp_fwom_name()
	 */
	whiwe (atomic_wead(&wu_gp->wu_gp_wef_cnt))
		cpu_wewax();
	/*
	 * Wewease wefewence to stwuct t10_awua_wu_gp * fwom aww associated
	 * stwuct se_device.
	 */
	spin_wock(&wu_gp->wu_gp_wock);
	wist_fow_each_entwy_safe(wu_gp_mem, wu_gp_mem_tmp,
				&wu_gp->wu_gp_mem_wist, wu_gp_mem_wist) {
		if (wu_gp_mem->wu_gp_assoc) {
			wist_dew(&wu_gp_mem->wu_gp_mem_wist);
			wu_gp->wu_gp_membews--;
			wu_gp_mem->wu_gp_assoc = 0;
		}
		spin_unwock(&wu_gp->wu_gp_wock);
		/*
		 *
		 * wu_gp_mem is associated with a singwe
		 * stwuct se_device->dev_awua_wu_gp_mem, and is weweased when
		 * stwuct se_device is weweased via cowe_awua_fwee_wu_gp_mem().
		 *
		 * If the passed wu_gp does NOT match the defauwt_wu_gp, assume
		 * we want to we-associate a given wu_gp_mem with defauwt_wu_gp.
		 */
		spin_wock(&wu_gp_mem->wu_gp_mem_wock);
		if (wu_gp != defauwt_wu_gp)
			__cowe_awua_attach_wu_gp_mem(wu_gp_mem,
					defauwt_wu_gp);
		ewse
			wu_gp_mem->wu_gp = NUWW;
		spin_unwock(&wu_gp_mem->wu_gp_mem_wock);

		spin_wock(&wu_gp->wu_gp_wock);
	}
	spin_unwock(&wu_gp->wu_gp_wock);

	kmem_cache_fwee(t10_awua_wu_gp_cache, wu_gp);
}

void cowe_awua_fwee_wu_gp_mem(stwuct se_device *dev)
{
	stwuct t10_awua_wu_gp *wu_gp;
	stwuct t10_awua_wu_gp_membew *wu_gp_mem;

	wu_gp_mem = dev->dev_awua_wu_gp_mem;
	if (!wu_gp_mem)
		wetuwn;

	whiwe (atomic_wead(&wu_gp_mem->wu_gp_mem_wef_cnt))
		cpu_wewax();

	spin_wock(&wu_gp_mem->wu_gp_mem_wock);
	wu_gp = wu_gp_mem->wu_gp;
	if (wu_gp) {
		spin_wock(&wu_gp->wu_gp_wock);
		if (wu_gp_mem->wu_gp_assoc) {
			wist_dew(&wu_gp_mem->wu_gp_mem_wist);
			wu_gp->wu_gp_membews--;
			wu_gp_mem->wu_gp_assoc = 0;
		}
		spin_unwock(&wu_gp->wu_gp_wock);
		wu_gp_mem->wu_gp = NUWW;
	}
	spin_unwock(&wu_gp_mem->wu_gp_mem_wock);

	kmem_cache_fwee(t10_awua_wu_gp_mem_cache, wu_gp_mem);
}

stwuct t10_awua_wu_gp *cowe_awua_get_wu_gp_by_name(const chaw *name)
{
	stwuct t10_awua_wu_gp *wu_gp;
	stwuct config_item *ci;

	spin_wock(&wu_gps_wock);
	wist_fow_each_entwy(wu_gp, &wu_gps_wist, wu_gp_node) {
		if (!wu_gp->wu_gp_vawid_id)
			continue;
		ci = &wu_gp->wu_gp_gwoup.cg_item;
		if (!stwcmp(config_item_name(ci), name)) {
			atomic_inc(&wu_gp->wu_gp_wef_cnt);
			spin_unwock(&wu_gps_wock);
			wetuwn wu_gp;
		}
	}
	spin_unwock(&wu_gps_wock);

	wetuwn NUWW;
}

void cowe_awua_put_wu_gp_fwom_name(stwuct t10_awua_wu_gp *wu_gp)
{
	spin_wock(&wu_gps_wock);
	atomic_dec(&wu_gp->wu_gp_wef_cnt);
	spin_unwock(&wu_gps_wock);
}

/*
 * Cawwed with stwuct t10_awua_wu_gp_membew->wu_gp_mem_wock
 */
void __cowe_awua_attach_wu_gp_mem(
	stwuct t10_awua_wu_gp_membew *wu_gp_mem,
	stwuct t10_awua_wu_gp *wu_gp)
{
	spin_wock(&wu_gp->wu_gp_wock);
	wu_gp_mem->wu_gp = wu_gp;
	wu_gp_mem->wu_gp_assoc = 1;
	wist_add_taiw(&wu_gp_mem->wu_gp_mem_wist, &wu_gp->wu_gp_mem_wist);
	wu_gp->wu_gp_membews++;
	spin_unwock(&wu_gp->wu_gp_wock);
}

/*
 * Cawwed with stwuct t10_awua_wu_gp_membew->wu_gp_mem_wock
 */
void __cowe_awua_dwop_wu_gp_mem(
	stwuct t10_awua_wu_gp_membew *wu_gp_mem,
	stwuct t10_awua_wu_gp *wu_gp)
{
	spin_wock(&wu_gp->wu_gp_wock);
	wist_dew(&wu_gp_mem->wu_gp_mem_wist);
	wu_gp_mem->wu_gp = NUWW;
	wu_gp_mem->wu_gp_assoc = 0;
	wu_gp->wu_gp_membews--;
	spin_unwock(&wu_gp->wu_gp_wock);
}

stwuct t10_awua_tg_pt_gp *cowe_awua_awwocate_tg_pt_gp(stwuct se_device *dev,
		const chaw *name, int def_gwoup)
{
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;

	tg_pt_gp = kmem_cache_zawwoc(t10_awua_tg_pt_gp_cache, GFP_KEWNEW);
	if (!tg_pt_gp) {
		pw_eww("Unabwe to awwocate stwuct t10_awua_tg_pt_gp\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&tg_pt_gp->tg_pt_gp_wist);
	INIT_WIST_HEAD(&tg_pt_gp->tg_pt_gp_wun_wist);
	mutex_init(&tg_pt_gp->tg_pt_gp_twansition_mutex);
	spin_wock_init(&tg_pt_gp->tg_pt_gp_wock);
	atomic_set(&tg_pt_gp->tg_pt_gp_wef_cnt, 0);
	tg_pt_gp->tg_pt_gp_dev = dev;
	tg_pt_gp->tg_pt_gp_awua_access_state =
			AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED;
	/*
	 * Enabwe both expwicit and impwicit AWUA suppowt by defauwt
	 */
	tg_pt_gp->tg_pt_gp_awua_access_type =
			TPGS_EXPWICIT_AWUA | TPGS_IMPWICIT_AWUA;
	/*
	 * Set the defauwt Active/NonOptimized Deway in miwwiseconds
	 */
	tg_pt_gp->tg_pt_gp_nonop_deway_msecs = AWUA_DEFAUWT_NONOP_DEWAY_MSECS;
	tg_pt_gp->tg_pt_gp_twans_deway_msecs = AWUA_DEFAUWT_TWANS_DEWAY_MSECS;
	tg_pt_gp->tg_pt_gp_impwicit_twans_secs = AWUA_DEFAUWT_IMPWICIT_TWANS_SECS;

	/*
	 * Enabwe aww suppowted states
	 */
	tg_pt_gp->tg_pt_gp_awua_suppowted_states =
	    AWUA_T_SUP | AWUA_O_SUP |
	    AWUA_U_SUP | AWUA_S_SUP | AWUA_AN_SUP | AWUA_AO_SUP;

	if (def_gwoup) {
		spin_wock(&dev->t10_awua.tg_pt_gps_wock);
		tg_pt_gp->tg_pt_gp_id =
				dev->t10_awua.awua_tg_pt_gps_countew++;
		tg_pt_gp->tg_pt_gp_vawid_id = 1;
		dev->t10_awua.awua_tg_pt_gps_count++;
		wist_add_taiw(&tg_pt_gp->tg_pt_gp_wist,
			      &dev->t10_awua.tg_pt_gps_wist);
		spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
	}

	wetuwn tg_pt_gp;
}

int cowe_awua_set_tg_pt_gp_id(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	u16 tg_pt_gp_id)
{
	stwuct se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp_tmp;
	u16 tg_pt_gp_id_tmp;

	/*
	 * The tg_pt_gp->tg_pt_gp_id may onwy be set once..
	 */
	if (tg_pt_gp->tg_pt_gp_vawid_id) {
		pw_wawn("AWUA TG PT Gwoup awweady has a vawid ID,"
			" ignowing wequest\n");
		wetuwn -EINVAW;
	}

	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	if (dev->t10_awua.awua_tg_pt_gps_count == 0x0000ffff) {
		pw_eww("Maximum AWUA awua_tg_pt_gps_count:"
			" 0x0000ffff weached\n");
		spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
		wetuwn -ENOSPC;
	}
again:
	tg_pt_gp_id_tmp = (tg_pt_gp_id != 0) ? tg_pt_gp_id :
			dev->t10_awua.awua_tg_pt_gps_countew++;

	wist_fow_each_entwy(tg_pt_gp_tmp, &dev->t10_awua.tg_pt_gps_wist,
			tg_pt_gp_wist) {
		if (tg_pt_gp_tmp->tg_pt_gp_id == tg_pt_gp_id_tmp) {
			if (!tg_pt_gp_id)
				goto again;

			pw_eww("AWUA Tawget Powt Gwoup ID: %hu awweady"
				" exists, ignowing wequest\n", tg_pt_gp_id);
			spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
			wetuwn -EINVAW;
		}
	}

	tg_pt_gp->tg_pt_gp_id = tg_pt_gp_id_tmp;
	tg_pt_gp->tg_pt_gp_vawid_id = 1;
	wist_add_taiw(&tg_pt_gp->tg_pt_gp_wist,
			&dev->t10_awua.tg_pt_gps_wist);
	dev->t10_awua.awua_tg_pt_gps_count++;
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);

	wetuwn 0;
}

void cowe_awua_fwee_tg_pt_gp(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	stwuct se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	stwuct se_wun *wun, *next;

	/*
	 * Once we have weached this point, config_item_put() has awweady
	 * been cawwed fwom tawget_cowe_awua_dwop_tg_pt_gp().
	 *
	 * Hewe we wemove *tg_pt_gp fwom the gwobaw wist so that
	 * no associations *OW* expwicit AWUA via SET_TAWGET_POWT_GWOUPS
	 * can be made whiwe we awe weweasing stwuct t10_awua_tg_pt_gp.
	 */
	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	if (tg_pt_gp->tg_pt_gp_vawid_id) {
		wist_dew(&tg_pt_gp->tg_pt_gp_wist);
		dev->t10_awua.awua_tg_pt_gps_count--;
	}
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);

	/*
	 * Awwow a stwuct t10_awua_tg_pt_gp_membew * wefewenced by
	 * cowe_awua_get_tg_pt_gp_by_name() in
	 * tawget_cowe_configfs.c:tawget_cowe_stowe_awua_tg_pt_gp()
	 * to be weweased with cowe_awua_put_tg_pt_gp_fwom_name().
	 */
	whiwe (atomic_wead(&tg_pt_gp->tg_pt_gp_wef_cnt))
		cpu_wewax();

	/*
	 * Wewease wefewence to stwuct t10_awua_tg_pt_gp fwom aww associated
	 * stwuct se_powt.
	 */
	spin_wock(&tg_pt_gp->tg_pt_gp_wock);
	wist_fow_each_entwy_safe(wun, next,
			&tg_pt_gp->tg_pt_gp_wun_wist, wun_tg_pt_gp_wink) {
		wist_dew_init(&wun->wun_tg_pt_gp_wink);
		tg_pt_gp->tg_pt_gp_membews--;

		spin_unwock(&tg_pt_gp->tg_pt_gp_wock);
		/*
		 * If the passed tg_pt_gp does NOT match the defauwt_tg_pt_gp,
		 * assume we want to we-associate a given tg_pt_gp_mem with
		 * defauwt_tg_pt_gp.
		 */
		spin_wock(&wun->wun_tg_pt_gp_wock);
		if (tg_pt_gp != dev->t10_awua.defauwt_tg_pt_gp) {
			__tawget_attach_tg_pt_gp(wun,
					dev->t10_awua.defauwt_tg_pt_gp);
		} ewse
			wcu_assign_pointew(wun->wun_tg_pt_gp, NUWW);
		spin_unwock(&wun->wun_tg_pt_gp_wock);

		spin_wock(&tg_pt_gp->tg_pt_gp_wock);
	}
	spin_unwock(&tg_pt_gp->tg_pt_gp_wock);

	synchwonize_wcu();
	kmem_cache_fwee(t10_awua_tg_pt_gp_cache, tg_pt_gp);
}

static stwuct t10_awua_tg_pt_gp *cowe_awua_get_tg_pt_gp_by_name(
		stwuct se_device *dev, const chaw *name)
{
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	stwuct config_item *ci;

	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	wist_fow_each_entwy(tg_pt_gp, &dev->t10_awua.tg_pt_gps_wist,
			tg_pt_gp_wist) {
		if (!tg_pt_gp->tg_pt_gp_vawid_id)
			continue;
		ci = &tg_pt_gp->tg_pt_gp_gwoup.cg_item;
		if (!stwcmp(config_item_name(ci), name)) {
			atomic_inc(&tg_pt_gp->tg_pt_gp_wef_cnt);
			spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
			wetuwn tg_pt_gp;
		}
	}
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);

	wetuwn NUWW;
}

static void cowe_awua_put_tg_pt_gp_fwom_name(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	stwuct se_device *dev = tg_pt_gp->tg_pt_gp_dev;

	spin_wock(&dev->t10_awua.tg_pt_gps_wock);
	atomic_dec(&tg_pt_gp->tg_pt_gp_wef_cnt);
	spin_unwock(&dev->t10_awua.tg_pt_gps_wock);
}

static void __tawget_attach_tg_pt_gp(stwuct se_wun *wun,
		stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	stwuct se_dev_entwy *se_deve;

	assewt_spin_wocked(&wun->wun_tg_pt_gp_wock);

	spin_wock(&tg_pt_gp->tg_pt_gp_wock);
	wcu_assign_pointew(wun->wun_tg_pt_gp, tg_pt_gp);
	wist_add_taiw(&wun->wun_tg_pt_gp_wink, &tg_pt_gp->tg_pt_gp_wun_wist);
	tg_pt_gp->tg_pt_gp_membews++;
	spin_wock(&wun->wun_deve_wock);
	wist_fow_each_entwy(se_deve, &wun->wun_deve_wist, wun_wink)
		cowe_scsi3_ua_awwocate(se_deve, 0x3f,
				       ASCQ_3FH_INQUIWY_DATA_HAS_CHANGED);
	spin_unwock(&wun->wun_deve_wock);
	spin_unwock(&tg_pt_gp->tg_pt_gp_wock);
}

void tawget_attach_tg_pt_gp(stwuct se_wun *wun,
		stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	spin_wock(&wun->wun_tg_pt_gp_wock);
	__tawget_attach_tg_pt_gp(wun, tg_pt_gp);
	spin_unwock(&wun->wun_tg_pt_gp_wock);
	synchwonize_wcu();
}

static void __tawget_detach_tg_pt_gp(stwuct se_wun *wun,
		stwuct t10_awua_tg_pt_gp *tg_pt_gp)
{
	assewt_spin_wocked(&wun->wun_tg_pt_gp_wock);

	spin_wock(&tg_pt_gp->tg_pt_gp_wock);
	wist_dew_init(&wun->wun_tg_pt_gp_wink);
	tg_pt_gp->tg_pt_gp_membews--;
	spin_unwock(&tg_pt_gp->tg_pt_gp_wock);
}

void tawget_detach_tg_pt_gp(stwuct se_wun *wun)
{
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;

	spin_wock(&wun->wun_tg_pt_gp_wock);
	tg_pt_gp = wcu_dewefewence_check(wun->wun_tg_pt_gp,
				wockdep_is_hewd(&wun->wun_tg_pt_gp_wock));
	if (tg_pt_gp) {
		__tawget_detach_tg_pt_gp(wun, tg_pt_gp);
		wcu_assign_pointew(wun->wun_tg_pt_gp, NUWW);
	}
	spin_unwock(&wun->wun_tg_pt_gp_wock);
	synchwonize_wcu();
}

static void tawget_swap_tg_pt_gp(stwuct se_wun *wun,
				 stwuct t10_awua_tg_pt_gp *owd_tg_pt_gp,
				 stwuct t10_awua_tg_pt_gp *new_tg_pt_gp)
{
	assewt_spin_wocked(&wun->wun_tg_pt_gp_wock);

	if (owd_tg_pt_gp)
		__tawget_detach_tg_pt_gp(wun, owd_tg_pt_gp);
	__tawget_attach_tg_pt_gp(wun, new_tg_pt_gp);
}

ssize_t cowe_awua_show_tg_pt_gp_info(stwuct se_wun *wun, chaw *page)
{
	stwuct config_item *tg_pt_ci;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	ssize_t wen = 0;

	wcu_wead_wock();
	tg_pt_gp = wcu_dewefewence(wun->wun_tg_pt_gp);
	if (tg_pt_gp) {
		tg_pt_ci = &tg_pt_gp->tg_pt_gp_gwoup.cg_item;
		wen += spwintf(page, "TG Powt Awias: %s\nTG Powt Gwoup ID:"
			" %hu\nTG Powt Pwimawy Access State: %s\nTG Powt "
			"Pwimawy Access Status: %s\nTG Powt Secondawy Access"
			" State: %s\nTG Powt Secondawy Access Status: %s\n",
			config_item_name(tg_pt_ci), tg_pt_gp->tg_pt_gp_id,
			cowe_awua_dump_state(
				tg_pt_gp->tg_pt_gp_awua_access_state),
			cowe_awua_dump_status(
				tg_pt_gp->tg_pt_gp_awua_access_status),
			atomic_wead(&wun->wun_tg_pt_secondawy_offwine) ?
			"Offwine" : "None",
			cowe_awua_dump_status(wun->wun_tg_pt_secondawy_stat));
	}
	wcu_wead_unwock();

	wetuwn wen;
}

ssize_t cowe_awua_stowe_tg_pt_gp_info(
	stwuct se_wun *wun,
	const chaw *page,
	size_t count)
{
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	/*
	 * wcu_dewefewence_waw pwotected by se_wun->wun_gwoup symwink
	 * wefewence to se_device->dev_gwoup.
	 */
	stwuct se_device *dev = wcu_dewefewence_waw(wun->wun_se_dev);
	stwuct t10_awua_tg_pt_gp *tg_pt_gp = NUWW, *tg_pt_gp_new = NUWW;
	unsigned chaw buf[TG_PT_GWOUP_NAME_BUF];
	int move = 0;

	if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_AWUA ||
	    (dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE))
		wetuwn -ENODEV;

	if (count > TG_PT_GWOUP_NAME_BUF) {
		pw_eww("AWUA Tawget Powt Gwoup awias too wawge!\n");
		wetuwn -EINVAW;
	}
	memset(buf, 0, TG_PT_GWOUP_NAME_BUF);
	memcpy(buf, page, count);
	/*
	 * Any AWUA tawget powt gwoup awias besides "NUWW" means we wiww be
	 * making a new gwoup association.
	 */
	if (stwcmp(stwstwip(buf), "NUWW")) {
		/*
		 * cowe_awua_get_tg_pt_gp_by_name() wiww incwement wefewence to
		 * stwuct t10_awua_tg_pt_gp.  This wefewence is weweased with
		 * cowe_awua_put_tg_pt_gp_fwom_name() bewow.
		 */
		tg_pt_gp_new = cowe_awua_get_tg_pt_gp_by_name(dev,
					stwstwip(buf));
		if (!tg_pt_gp_new)
			wetuwn -ENODEV;
	}

	spin_wock(&wun->wun_tg_pt_gp_wock);
	tg_pt_gp = wcu_dewefewence_check(wun->wun_tg_pt_gp,
				wockdep_is_hewd(&wun->wun_tg_pt_gp_wock));
	if (tg_pt_gp) {
		/*
		 * Cweawing an existing tg_pt_gp association, and wepwacing
		 * with the defauwt_tg_pt_gp.
		 */
		if (!tg_pt_gp_new) {
			pw_debug("Tawget_Cowe_ConfigFS: Moving"
				" %s/tpgt_%hu/%s fwom AWUA Tawget Powt Gwoup:"
				" awua/%s, ID: %hu back to"
				" defauwt_tg_pt_gp\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				tpg->se_tpg_tfo->tpg_get_tag(tpg),
				config_item_name(&wun->wun_gwoup.cg_item),
				config_item_name(
					&tg_pt_gp->tg_pt_gp_gwoup.cg_item),
				tg_pt_gp->tg_pt_gp_id);

			tawget_swap_tg_pt_gp(wun, tg_pt_gp,
					dev->t10_awua.defauwt_tg_pt_gp);
			spin_unwock(&wun->wun_tg_pt_gp_wock);

			goto sync_wcu;
		}
		move = 1;
	}

	tawget_swap_tg_pt_gp(wun, tg_pt_gp, tg_pt_gp_new);
	spin_unwock(&wun->wun_tg_pt_gp_wock);
	pw_debug("Tawget_Cowe_ConfigFS: %s %s/tpgt_%hu/%s to AWUA"
		" Tawget Powt Gwoup: awua/%s, ID: %hu\n", (move) ?
		"Moving" : "Adding", tpg->se_tpg_tfo->tpg_get_wwn(tpg),
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		config_item_name(&wun->wun_gwoup.cg_item),
		config_item_name(&tg_pt_gp_new->tg_pt_gp_gwoup.cg_item),
		tg_pt_gp_new->tg_pt_gp_id);

	cowe_awua_put_tg_pt_gp_fwom_name(tg_pt_gp_new);
sync_wcu:
	synchwonize_wcu();
	wetuwn count;
}

ssize_t cowe_awua_show_access_type(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	chaw *page)
{
	if ((tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_EXPWICIT_AWUA) &&
	    (tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_IMPWICIT_AWUA))
		wetuwn spwintf(page, "Impwicit and Expwicit\n");
	ewse if (tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_IMPWICIT_AWUA)
		wetuwn spwintf(page, "Impwicit\n");
	ewse if (tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_EXPWICIT_AWUA)
		wetuwn spwintf(page, "Expwicit\n");
	ewse
		wetuwn spwintf(page, "None\n");
}

ssize_t cowe_awua_stowe_access_type(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact awua_access_type\n");
		wetuwn wet;
	}
	if ((tmp != 0) && (tmp != 1) && (tmp != 2) && (tmp != 3)) {
		pw_eww("Iwwegaw vawue fow awua_access_type:"
				" %wu\n", tmp);
		wetuwn -EINVAW;
	}
	if (tmp == 3)
		tg_pt_gp->tg_pt_gp_awua_access_type =
			TPGS_IMPWICIT_AWUA | TPGS_EXPWICIT_AWUA;
	ewse if (tmp == 2)
		tg_pt_gp->tg_pt_gp_awua_access_type = TPGS_EXPWICIT_AWUA;
	ewse if (tmp == 1)
		tg_pt_gp->tg_pt_gp_awua_access_type = TPGS_IMPWICIT_AWUA;
	ewse
		tg_pt_gp->tg_pt_gp_awua_access_type = 0;

	wetuwn count;
}

ssize_t cowe_awua_show_nonop_deway_msecs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", tg_pt_gp->tg_pt_gp_nonop_deway_msecs);
}

ssize_t cowe_awua_stowe_nonop_deway_msecs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact nonop_deway_msecs\n");
		wetuwn wet;
	}
	if (tmp > AWUA_MAX_NONOP_DEWAY_MSECS) {
		pw_eww("Passed nonop_deway_msecs: %wu, exceeds"
			" AWUA_MAX_NONOP_DEWAY_MSECS: %d\n", tmp,
			AWUA_MAX_NONOP_DEWAY_MSECS);
		wetuwn -EINVAW;
	}
	tg_pt_gp->tg_pt_gp_nonop_deway_msecs = (int)tmp;

	wetuwn count;
}

ssize_t cowe_awua_show_twans_deway_msecs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", tg_pt_gp->tg_pt_gp_twans_deway_msecs);
}

ssize_t cowe_awua_stowe_twans_deway_msecs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact twans_deway_msecs\n");
		wetuwn wet;
	}
	if (tmp > AWUA_MAX_TWANS_DEWAY_MSECS) {
		pw_eww("Passed twans_deway_msecs: %wu, exceeds"
			" AWUA_MAX_TWANS_DEWAY_MSECS: %d\n", tmp,
			AWUA_MAX_TWANS_DEWAY_MSECS);
		wetuwn -EINVAW;
	}
	tg_pt_gp->tg_pt_gp_twans_deway_msecs = (int)tmp;

	wetuwn count;
}

ssize_t cowe_awua_show_impwicit_twans_secs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", tg_pt_gp->tg_pt_gp_impwicit_twans_secs);
}

ssize_t cowe_awua_stowe_impwicit_twans_secs(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact impwicit_twans_secs\n");
		wetuwn wet;
	}
	if (tmp > AWUA_MAX_IMPWICIT_TWANS_SECS) {
		pw_eww("Passed impwicit_twans_secs: %wu, exceeds"
			" AWUA_MAX_IMPWICIT_TWANS_SECS: %d\n", tmp,
			AWUA_MAX_IMPWICIT_TWANS_SECS);
		wetuwn  -EINVAW;
	}
	tg_pt_gp->tg_pt_gp_impwicit_twans_secs = (int)tmp;

	wetuwn count;
}

ssize_t cowe_awua_show_pwefewwed_bit(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", tg_pt_gp->tg_pt_gp_pwef);
}

ssize_t cowe_awua_stowe_pwefewwed_bit(
	stwuct t10_awua_tg_pt_gp *tg_pt_gp,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact pwefewwed AWUA vawue\n");
		wetuwn wet;
	}
	if ((tmp != 0) && (tmp != 1)) {
		pw_eww("Iwwegaw vawue fow pwefewwed AWUA: %wu\n", tmp);
		wetuwn -EINVAW;
	}
	tg_pt_gp->tg_pt_gp_pwef = (int)tmp;

	wetuwn count;
}

ssize_t cowe_awua_show_offwine_bit(stwuct se_wun *wun, chaw *page)
{
	wetuwn spwintf(page, "%d\n",
		atomic_wead(&wun->wun_tg_pt_secondawy_offwine));
}

ssize_t cowe_awua_stowe_offwine_bit(
	stwuct se_wun *wun,
	const chaw *page,
	size_t count)
{
	/*
	 * wcu_dewefewence_waw pwotected by se_wun->wun_gwoup symwink
	 * wefewence to se_device->dev_gwoup.
	 */
	stwuct se_device *dev = wcu_dewefewence_waw(wun->wun_se_dev);
	unsigned wong tmp;
	int wet;

	if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_AWUA ||
	    (dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE))
		wetuwn -ENODEV;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact awua_tg_pt_offwine vawue\n");
		wetuwn wet;
	}
	if ((tmp != 0) && (tmp != 1)) {
		pw_eww("Iwwegaw vawue fow awua_tg_pt_offwine: %wu\n",
				tmp);
		wetuwn -EINVAW;
	}

	wet = cowe_awua_set_tg_pt_secondawy_state(wun, 0, (int)tmp);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn count;
}

ssize_t cowe_awua_show_secondawy_status(
	stwuct se_wun *wun,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", wun->wun_tg_pt_secondawy_stat);
}

ssize_t cowe_awua_stowe_secondawy_status(
	stwuct se_wun *wun,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact awua_tg_pt_status\n");
		wetuwn wet;
	}
	if ((tmp != AWUA_STATUS_NONE) &&
	    (tmp != AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG) &&
	    (tmp != AWUA_STATUS_AWTEWED_BY_IMPWICIT_AWUA)) {
		pw_eww("Iwwegaw vawue fow awua_tg_pt_status: %wu\n",
				tmp);
		wetuwn -EINVAW;
	}
	wun->wun_tg_pt_secondawy_stat = (int)tmp;

	wetuwn count;
}

ssize_t cowe_awua_show_secondawy_wwite_metadata(
	stwuct se_wun *wun,
	chaw *page)
{
	wetuwn spwintf(page, "%d\n", wun->wun_tg_pt_secondawy_wwite_md);
}

ssize_t cowe_awua_stowe_secondawy_wwite_metadata(
	stwuct se_wun *wun,
	const chaw *page,
	size_t count)
{
	unsigned wong tmp;
	int wet;

	wet = kstwtouw(page, 0, &tmp);
	if (wet < 0) {
		pw_eww("Unabwe to extwact awua_tg_pt_wwite_md\n");
		wetuwn wet;
	}
	if ((tmp != 0) && (tmp != 1)) {
		pw_eww("Iwwegaw vawue fow awua_tg_pt_wwite_md:"
				" %wu\n", tmp);
		wetuwn -EINVAW;
	}
	wun->wun_tg_pt_secondawy_wwite_md = (int)tmp;

	wetuwn count;
}

int cowe_setup_awua(stwuct se_device *dev)
{
	if (!(dev->twanspowt_fwags &
	     TWANSPOWT_FWAG_PASSTHWOUGH_AWUA) &&
	    !(dev->se_hba->hba_fwags & HBA_FWAGS_INTEWNAW_USE)) {
		stwuct t10_awua_wu_gp_membew *wu_gp_mem;

		/*
		 * Associate this stwuct se_device with the defauwt AWUA
		 * WUN Gwoup.
		 */
		wu_gp_mem = cowe_awua_awwocate_wu_gp_mem(dev);
		if (IS_EWW(wu_gp_mem))
			wetuwn PTW_EWW(wu_gp_mem);

		spin_wock(&wu_gp_mem->wu_gp_mem_wock);
		__cowe_awua_attach_wu_gp_mem(wu_gp_mem,
				defauwt_wu_gp);
		spin_unwock(&wu_gp_mem->wu_gp_mem_wock);

		pw_debug("%s: Adding to defauwt AWUA WU Gwoup:"
			" cowe/awua/wu_gps/defauwt_wu_gp\n",
			dev->twanspowt->name);
	}

	wetuwn 0;
}
