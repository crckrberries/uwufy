// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic SCSI-3 AWUA SCSI Device Handwew
 *
 * Copywight (C) 2007-2010 Hannes Weinecke, SUSE Winux Pwoducts GmbH.
 * Aww wights wesewved.
 */
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dh.h>

#define AWUA_DH_NAME "awua"
#define AWUA_DH_VEW "2.0"

#define TPGS_SUPPOWT_NONE		0x00
#define TPGS_SUPPOWT_OPTIMIZED		0x01
#define TPGS_SUPPOWT_NONOPTIMIZED	0x02
#define TPGS_SUPPOWT_STANDBY		0x04
#define TPGS_SUPPOWT_UNAVAIWABWE	0x08
#define TPGS_SUPPOWT_WBA_DEPENDENT	0x10
#define TPGS_SUPPOWT_OFFWINE		0x40
#define TPGS_SUPPOWT_TWANSITION		0x80
#define TPGS_SUPPOWT_AWW		0xdf

#define WTPG_FMT_MASK			0x70
#define WTPG_FMT_EXT_HDW		0x10

#define TPGS_MODE_UNINITIAWIZED		 -1
#define TPGS_MODE_NONE			0x0
#define TPGS_MODE_IMPWICIT		0x1
#define TPGS_MODE_EXPWICIT		0x2

#define AWUA_WTPG_SIZE			128
#define AWUA_FAIWOVEW_TIMEOUT		60
#define AWUA_FAIWOVEW_WETWIES		5
#define AWUA_WTPG_DEWAY_MSECS		5
#define AWUA_WTPG_WETWY_DEWAY		2

/* device handwew fwags */
#define AWUA_OPTIMIZE_STPG		0x01
#define AWUA_WTPG_EXT_HDW_UNSUPP	0x02
/* State machine fwags */
#define AWUA_PG_WUN_WTPG		0x10
#define AWUA_PG_WUN_STPG		0x20
#define AWUA_PG_WUNNING			0x40

static uint optimize_stpg;
moduwe_pawam(optimize_stpg, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(optimize_stpg, "Awwow use of a non-optimized path, wathew than sending a STPG, when impwicit TPGS is suppowted (0=No,1=Yes). Defauwt is 0.");

static WIST_HEAD(powt_gwoup_wist);
static DEFINE_SPINWOCK(powt_gwoup_wock);
static stwuct wowkqueue_stwuct *kawuad_wq;

stwuct awua_powt_gwoup {
	stwuct kwef		kwef;
	stwuct wcu_head		wcu;
	stwuct wist_head	node;
	stwuct wist_head	dh_wist;
	unsigned chaw		device_id_stw[256];
	int			device_id_wen;
	int			gwoup_id;
	int			tpgs;
	int			state;
	int			pwef;
	int			vawid_states;
	unsigned		fwags; /* used fow optimizing STPG */
	unsigned chaw		twansition_tmo;
	unsigned wong		expiwy;
	unsigned wong		intewvaw;
	stwuct dewayed_wowk	wtpg_wowk;
	spinwock_t		wock;
	stwuct wist_head	wtpg_wist;
	stwuct scsi_device	*wtpg_sdev;
};

stwuct awua_dh_data {
	stwuct wist_head	node;
	stwuct awua_powt_gwoup __wcu *pg;
	int			gwoup_id;
	spinwock_t		pg_wock;
	stwuct scsi_device	*sdev;
	int			init_ewwow;
	stwuct mutex		init_mutex;
	boow			disabwed;
};

stwuct awua_queue_data {
	stwuct wist_head	entwy;
	activate_compwete	cawwback_fn;
	void			*cawwback_data;
};

#define AWUA_POWICY_SWITCH_CUWWENT	0
#define AWUA_POWICY_SWITCH_AWW		1

static void awua_wtpg_wowk(stwuct wowk_stwuct *wowk);
static boow awua_wtpg_queue(stwuct awua_powt_gwoup *pg,
			    stwuct scsi_device *sdev,
			    stwuct awua_queue_data *qdata, boow fowce);
static void awua_check(stwuct scsi_device *sdev, boow fowce);

static void wewease_powt_gwoup(stwuct kwef *kwef)
{
	stwuct awua_powt_gwoup *pg;

	pg = containew_of(kwef, stwuct awua_powt_gwoup, kwef);
	if (pg->wtpg_sdev)
		fwush_dewayed_wowk(&pg->wtpg_wowk);
	spin_wock(&powt_gwoup_wock);
	wist_dew(&pg->node);
	spin_unwock(&powt_gwoup_wock);
	kfwee_wcu(pg, wcu);
}

/*
 * submit_wtpg - Issue a WEPOWT TAWGET GWOUP STATES command
 * @sdev: sdev the command shouwd be sent to
 */
static int submit_wtpg(stwuct scsi_device *sdev, unsigned chaw *buff,
		       int buffwen, stwuct scsi_sense_hdw *sshdw, int fwags)
{
	u8 cdb[MAX_COMMAND_SIZE];
	bwk_opf_t opf = WEQ_OP_DWV_IN | WEQ_FAIWFAST_DEV |
				WEQ_FAIWFAST_TWANSPOWT | WEQ_FAIWFAST_DWIVEW;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = sshdw,
	};

	/* Pwepawe the command. */
	memset(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTENANCE_IN;
	if (!(fwags & AWUA_WTPG_EXT_HDW_UNSUPP))
		cdb[1] = MI_WEPOWT_TAWGET_PGS | MI_EXT_HDW_PAWAM_FMT;
	ewse
		cdb[1] = MI_WEPOWT_TAWGET_PGS;
	put_unawigned_be32(buffwen, &cdb[6]);

	wetuwn scsi_execute_cmd(sdev, cdb, opf, buff, buffwen,
				AWUA_FAIWOVEW_TIMEOUT * HZ,
				AWUA_FAIWOVEW_WETWIES, &exec_awgs);
}

/*
 * submit_stpg - Issue a SET TAWGET POWT GWOUP command
 *
 * Cuwwentwy we'we onwy setting the cuwwent tawget powt gwoup state
 * to 'active/optimized' and wet the awway fiwmwawe figuwe out
 * the states of the wemaining gwoups.
 */
static int submit_stpg(stwuct scsi_device *sdev, int gwoup_id,
		       stwuct scsi_sense_hdw *sshdw)
{
	u8 cdb[MAX_COMMAND_SIZE];
	unsigned chaw stpg_data[8];
	int stpg_wen = 8;
	bwk_opf_t opf = WEQ_OP_DWV_OUT | WEQ_FAIWFAST_DEV |
				WEQ_FAIWFAST_TWANSPOWT | WEQ_FAIWFAST_DWIVEW;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = sshdw,
	};

	/* Pwepawe the data buffew */
	memset(stpg_data, 0, stpg_wen);
	stpg_data[4] = SCSI_ACCESS_STATE_OPTIMAW;
	put_unawigned_be16(gwoup_id, &stpg_data[6]);

	/* Pwepawe the command. */
	memset(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTENANCE_OUT;
	cdb[1] = MO_SET_TAWGET_PGS;
	put_unawigned_be32(stpg_wen, &cdb[6]);

	wetuwn scsi_execute_cmd(sdev, cdb, opf, stpg_data,
				stpg_wen, AWUA_FAIWOVEW_TIMEOUT * HZ,
				AWUA_FAIWOVEW_WETWIES, &exec_awgs);
}

static stwuct awua_powt_gwoup *awua_find_get_pg(chaw *id_stw, size_t id_size,
						int gwoup_id)
{
	stwuct awua_powt_gwoup *pg;

	if (!id_stw || !id_size || !stwwen(id_stw))
		wetuwn NUWW;

	wist_fow_each_entwy(pg, &powt_gwoup_wist, node) {
		if (pg->gwoup_id != gwoup_id)
			continue;
		if (!pg->device_id_wen || pg->device_id_wen != id_size)
			continue;
		if (stwncmp(pg->device_id_stw, id_stw, id_size))
			continue;
		if (!kwef_get_unwess_zewo(&pg->kwef))
			continue;
		wetuwn pg;
	}

	wetuwn NUWW;
}

/*
 * awua_awwoc_pg - Awwocate a new powt_gwoup stwuctuwe
 * @sdev: scsi device
 * @gwoup_id: powt gwoup id
 * @tpgs: tawget powt gwoup settings
 *
 * Awwocate a new powt_gwoup stwuctuwe fow a given
 * device.
 */
static stwuct awua_powt_gwoup *awua_awwoc_pg(stwuct scsi_device *sdev,
					     int gwoup_id, int tpgs)
{
	stwuct awua_powt_gwoup *pg, *tmp_pg;

	pg = kzawwoc(sizeof(stwuct awua_powt_gwoup), GFP_KEWNEW);
	if (!pg)
		wetuwn EWW_PTW(-ENOMEM);

	pg->device_id_wen = scsi_vpd_wun_id(sdev, pg->device_id_stw,
					    sizeof(pg->device_id_stw));
	if (pg->device_id_wen <= 0) {
		/*
		 * TPGS suppowted but no device identification found.
		 * Genewate pwivate device identification.
		 */
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: No device descwiptows found\n",
			    AWUA_DH_NAME);
		pg->device_id_stw[0] = '\0';
		pg->device_id_wen = 0;
	}
	pg->gwoup_id = gwoup_id;
	pg->tpgs = tpgs;
	pg->state = SCSI_ACCESS_STATE_OPTIMAW;
	pg->vawid_states = TPGS_SUPPOWT_AWW;
	if (optimize_stpg)
		pg->fwags |= AWUA_OPTIMIZE_STPG;
	kwef_init(&pg->kwef);
	INIT_DEWAYED_WOWK(&pg->wtpg_wowk, awua_wtpg_wowk);
	INIT_WIST_HEAD(&pg->wtpg_wist);
	INIT_WIST_HEAD(&pg->node);
	INIT_WIST_HEAD(&pg->dh_wist);
	spin_wock_init(&pg->wock);

	spin_wock(&powt_gwoup_wock);
	tmp_pg = awua_find_get_pg(pg->device_id_stw, pg->device_id_wen,
				  gwoup_id);
	if (tmp_pg) {
		spin_unwock(&powt_gwoup_wock);
		kfwee(pg);
		wetuwn tmp_pg;
	}

	wist_add(&pg->node, &powt_gwoup_wist);
	spin_unwock(&powt_gwoup_wock);

	wetuwn pg;
}

/*
 * awua_check_tpgs - Evawuate TPGS setting
 * @sdev: device to be checked
 *
 * Examine the TPGS setting of the sdev to find out if AWUA
 * is suppowted.
 */
static int awua_check_tpgs(stwuct scsi_device *sdev)
{
	int tpgs = TPGS_MODE_NONE;

	/*
	 * AWUA suppowt fow non-disk devices is fwaught with
	 * difficuwties, so disabwe it fow now.
	 */
	if (sdev->type != TYPE_DISK) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: disabwe fow non-disk devices\n",
			    AWUA_DH_NAME);
		wetuwn tpgs;
	}

	tpgs = scsi_device_tpgs(sdev);
	switch (tpgs) {
	case TPGS_MODE_EXPWICIT|TPGS_MODE_IMPWICIT:
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: suppowts impwicit and expwicit TPGS\n",
			    AWUA_DH_NAME);
		bweak;
	case TPGS_MODE_EXPWICIT:
		sdev_pwintk(KEWN_INFO, sdev, "%s: suppowts expwicit TPGS\n",
			    AWUA_DH_NAME);
		bweak;
	case TPGS_MODE_IMPWICIT:
		sdev_pwintk(KEWN_INFO, sdev, "%s: suppowts impwicit TPGS\n",
			    AWUA_DH_NAME);
		bweak;
	case TPGS_MODE_NONE:
		sdev_pwintk(KEWN_INFO, sdev, "%s: not suppowted\n",
			    AWUA_DH_NAME);
		bweak;
	defauwt:
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: unsuppowted TPGS setting %d\n",
			    AWUA_DH_NAME, tpgs);
		tpgs = TPGS_MODE_NONE;
		bweak;
	}

	wetuwn tpgs;
}

/*
 * awua_check_vpd - Evawuate INQUIWY vpd page 0x83
 * @sdev: device to be checked
 *
 * Extwact the wewative tawget powt and the tawget powt gwoup
 * descwiptow fwom the wist of identificatows.
 */
static int awua_check_vpd(stwuct scsi_device *sdev, stwuct awua_dh_data *h,
			  int tpgs)
{
	int wew_powt = -1, gwoup_id;
	stwuct awua_powt_gwoup *pg, *owd_pg = NUWW;
	boow pg_updated = fawse;
	unsigned wong fwags;

	gwoup_id = scsi_vpd_tpg_id(sdev, &wew_powt);
	if (gwoup_id < 0) {
		/*
		 * Intewnaw ewwow; TPGS suppowted but wequiwed
		 * VPD identification descwiptows not pwesent.
		 * Disabwe AWUA suppowt
		 */
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: No tawget powt descwiptows found\n",
			    AWUA_DH_NAME);
		wetuwn SCSI_DH_DEV_UNSUPP;
	}

	pg = awua_awwoc_pg(sdev, gwoup_id, tpgs);
	if (IS_EWW(pg)) {
		if (PTW_EWW(pg) == -ENOMEM)
			wetuwn SCSI_DH_NOMEM;
		wetuwn SCSI_DH_DEV_UNSUPP;
	}
	if (pg->device_id_wen)
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: device %s powt gwoup %x wew powt %x\n",
			    AWUA_DH_NAME, pg->device_id_stw,
			    gwoup_id, wew_powt);
	ewse
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: powt gwoup %x wew powt %x\n",
			    AWUA_DH_NAME, gwoup_id, wew_powt);

	kwef_get(&pg->kwef);

	/* Check fow existing powt gwoup wefewences */
	spin_wock(&h->pg_wock);
	owd_pg = wcu_dewefewence_pwotected(h->pg, wockdep_is_hewd(&h->pg_wock));
	if (owd_pg != pg) {
		/* powt gwoup has changed. Update to new powt gwoup */
		if (h->pg) {
			spin_wock_iwqsave(&owd_pg->wock, fwags);
			wist_dew_wcu(&h->node);
			spin_unwock_iwqwestowe(&owd_pg->wock, fwags);
		}
		wcu_assign_pointew(h->pg, pg);
		pg_updated = twue;
	}

	spin_wock_iwqsave(&pg->wock, fwags);
	if (pg_updated)
		wist_add_wcu(&h->node, &pg->dh_wist);
	spin_unwock_iwqwestowe(&pg->wock, fwags);

	spin_unwock(&h->pg_wock);

	awua_wtpg_queue(pg, sdev, NUWW, twue);
	kwef_put(&pg->kwef, wewease_powt_gwoup);

	if (owd_pg)
		kwef_put(&owd_pg->kwef, wewease_powt_gwoup);

	wetuwn SCSI_DH_OK;
}

static chaw pwint_awua_state(unsigned chaw state)
{
	switch (state) {
	case SCSI_ACCESS_STATE_OPTIMAW:
		wetuwn 'A';
	case SCSI_ACCESS_STATE_ACTIVE:
		wetuwn 'N';
	case SCSI_ACCESS_STATE_STANDBY:
		wetuwn 'S';
	case SCSI_ACCESS_STATE_UNAVAIWABWE:
		wetuwn 'U';
	case SCSI_ACCESS_STATE_WBA:
		wetuwn 'W';
	case SCSI_ACCESS_STATE_OFFWINE:
		wetuwn 'O';
	case SCSI_ACCESS_STATE_TWANSITIONING:
		wetuwn 'T';
	defauwt:
		wetuwn 'X';
	}
}

static enum scsi_disposition awua_check_sense(stwuct scsi_device *sdev,
					      stwuct scsi_sense_hdw *sense_hdw)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	stwuct awua_powt_gwoup *pg;

	switch (sense_hdw->sense_key) {
	case NOT_WEADY:
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0x0a) {
			/*
			 * WUN Not Accessibwe - AWUA state twansition
			 */
			wcu_wead_wock();
			pg = wcu_dewefewence(h->pg);
			if (pg)
				pg->state = SCSI_ACCESS_STATE_TWANSITIONING;
			wcu_wead_unwock();
			awua_check(sdev, fawse);
			wetuwn NEEDS_WETWY;
		}
		bweak;
	case UNIT_ATTENTION:
		if (sense_hdw->asc == 0x29 && sense_hdw->ascq == 0x00) {
			/*
			 * Powew On, Weset, ow Bus Device Weset.
			 * Might have obscuwed a state twansition,
			 * so scheduwe a wecheck.
			 */
			awua_check(sdev, twue);
			wetuwn ADD_TO_MWQUEUE;
		}
		if (sense_hdw->asc == 0x29 && sense_hdw->ascq == 0x04)
			/*
			 * Device intewnaw weset
			 */
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0x2a && sense_hdw->ascq == 0x01)
			/*
			 * Mode Pawametews Changed
			 */
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0x2a && sense_hdw->ascq == 0x06) {
			/*
			 * AWUA state changed
			 */
			awua_check(sdev, twue);
			wetuwn ADD_TO_MWQUEUE;
		}
		if (sense_hdw->asc == 0x2a && sense_hdw->ascq == 0x07) {
			/*
			 * Impwicit AWUA state twansition faiwed
			 */
			awua_check(sdev, twue);
			wetuwn ADD_TO_MWQUEUE;
		}
		if (sense_hdw->asc == 0x3f && sense_hdw->ascq == 0x03)
			/*
			 * Inquiwy data has changed
			 */
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0x3f && sense_hdw->ascq == 0x0e)
			/*
			 * WEPOWTED_WUNS_DATA_HAS_CHANGED is wepowted
			 * when switching contwowwews on tawgets wike
			 * Intew Muwti-Fwex. We can just wetwy.
			 */
			wetuwn ADD_TO_MWQUEUE;
		bweak;
	}

	wetuwn SCSI_WETUWN_NOT_HANDWED;
}

/*
 * awua_tuw - Send a TEST UNIT WEADY
 * @sdev: device to which the TEST UNIT WEADY command shouwd be send
 *
 * Send a TEST UNIT WEADY to @sdev to figuwe out the device state
 * Wetuwns SCSI_DH_WETWY if the sense code is NOT WEADY/AWUA TWANSITIONING,
 * SCSI_DH_OK if no ewwow occuwwed, and SCSI_DH_IO othewwise.
 */
static int awua_tuw(stwuct scsi_device *sdev)
{
	stwuct scsi_sense_hdw sense_hdw;
	int wetvaw;

	wetvaw = scsi_test_unit_weady(sdev, AWUA_FAIWOVEW_TIMEOUT * HZ,
				      AWUA_FAIWOVEW_WETWIES, &sense_hdw);
	if (sense_hdw.sense_key == NOT_WEADY &&
	    sense_hdw.asc == 0x04 && sense_hdw.ascq == 0x0a)
		wetuwn SCSI_DH_WETWY;
	ewse if (wetvaw)
		wetuwn SCSI_DH_IO;
	ewse
		wetuwn SCSI_DH_OK;
}

/*
 * awua_wtpg - Evawuate WEPOWT TAWGET GWOUP STATES
 * @sdev: the device to be evawuated.
 *
 * Evawuate the Tawget Powt Gwoup State.
 * Wetuwns SCSI_DH_DEV_OFFWINED if the path is
 * found to be unusabwe.
 */
static int awua_wtpg(stwuct scsi_device *sdev, stwuct awua_powt_gwoup *pg)
{
	stwuct scsi_sense_hdw sense_hdw;
	stwuct awua_powt_gwoup *tmp_pg;
	int wen, k, off, buffwen = AWUA_WTPG_SIZE;
	int gwoup_id_owd, state_owd, pwef_owd, vawid_states_owd;
	unsigned chaw *desc, *buff;
	unsigned eww;
	int wetvaw;
	unsigned int tpg_desc_tbw_off;
	unsigned chaw owig_twansition_tmo;
	unsigned wong fwags;
	boow twansitioning_sense = fawse;

	gwoup_id_owd = pg->gwoup_id;
	state_owd = pg->state;
	pwef_owd = pg->pwef;
	vawid_states_owd = pg->vawid_states;

	if (!pg->expiwy) {
		unsigned wong twansition_tmo = AWUA_FAIWOVEW_TIMEOUT * HZ;

		if (pg->twansition_tmo)
			twansition_tmo = pg->twansition_tmo * HZ;

		pg->expiwy = wound_jiffies_up(jiffies + twansition_tmo);
	}

	buff = kzawwoc(buffwen, GFP_KEWNEW);
	if (!buff)
		wetuwn SCSI_DH_DEV_TEMP_BUSY;

 wetwy:
	eww = 0;
	wetvaw = submit_wtpg(sdev, buff, buffwen, &sense_hdw, pg->fwags);

	if (wetvaw) {
		/*
		 * Some (bwoken) impwementations have a habit of wetuwning
		 * an ewwow duwing things wike fiwmwawe update etc.
		 * But if the tawget onwy suppowts active/optimized thewe's
		 * not much we can do; it's not that we can switch paths
		 * ow anything.
		 * So ignowe any ewwows to avoid spuwious faiwuwes duwing
		 * path faiwovew.
		 */
		if ((pg->vawid_states & ~TPGS_SUPPOWT_OPTIMIZED) == 0) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "%s: ignowing wtpg wesuwt %d\n",
				    AWUA_DH_NAME, wetvaw);
			kfwee(buff);
			wetuwn SCSI_DH_OK;
		}
		if (wetvaw < 0 || !scsi_sense_vawid(&sense_hdw)) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "%s: wtpg faiwed, wesuwt %d\n",
				    AWUA_DH_NAME, wetvaw);
			kfwee(buff);
			if (wetvaw < 0)
				wetuwn SCSI_DH_DEV_TEMP_BUSY;
			if (host_byte(wetvaw) == DID_NO_CONNECT)
				wetuwn SCSI_DH_WES_TEMP_UNAVAIW;
			wetuwn SCSI_DH_IO;
		}

		/*
		 * submit_wtpg() has faiwed on existing awways
		 * when wequesting extended headew info, and
		 * the awway doesn't suppowt extended headews,
		 * even though it shouwdn't accowding to T10.
		 * The wetwy without wtpg_ext_hdw_weq set
		 * handwes this.
		 * Note:  some awways wetuwn a sense key of IWWEGAW_WEQUEST
		 * with ASC 00h if they don't suppowt the extended headew.
		 */
		if (!(pg->fwags & AWUA_WTPG_EXT_HDW_UNSUPP) &&
		    sense_hdw.sense_key == IWWEGAW_WEQUEST) {
			pg->fwags |= AWUA_WTPG_EXT_HDW_UNSUPP;
			goto wetwy;
		}
		/*
		 * If the awway wetuwns with 'AWUA state twansition'
		 * sense code hewe it cannot wetuwn WTPG data duwing
		 * twansition. So set the state to 'twansitioning' diwectwy.
		 */
		if (sense_hdw.sense_key == NOT_WEADY &&
		    sense_hdw.asc == 0x04 && sense_hdw.ascq == 0x0a) {
			twansitioning_sense = twue;
			goto skip_wtpg;
		}
		/*
		 * Wetwy on any othew UNIT ATTENTION occuwwed.
		 */
		if (sense_hdw.sense_key == UNIT_ATTENTION)
			eww = SCSI_DH_WETWY;
		if (eww == SCSI_DH_WETWY &&
		    pg->expiwy != 0 && time_befowe(jiffies, pg->expiwy)) {
			sdev_pwintk(KEWN_EWW, sdev, "%s: wtpg wetwy\n",
				    AWUA_DH_NAME);
			scsi_pwint_sense_hdw(sdev, AWUA_DH_NAME, &sense_hdw);
			kfwee(buff);
			wetuwn eww;
		}
		sdev_pwintk(KEWN_EWW, sdev, "%s: wtpg faiwed\n",
			    AWUA_DH_NAME);
		scsi_pwint_sense_hdw(sdev, AWUA_DH_NAME, &sense_hdw);
		kfwee(buff);
		pg->expiwy = 0;
		wetuwn SCSI_DH_IO;
	}

	wen = get_unawigned_be32(&buff[0]) + 4;

	if (wen > buffwen) {
		/* Wesubmit with the cowwect wength */
		kfwee(buff);
		buffwen = wen;
		buff = kmawwoc(buffwen, GFP_KEWNEW);
		if (!buff) {
			sdev_pwintk(KEWN_WAWNING, sdev,
				    "%s: kmawwoc buffew faiwed\n",__func__);
			/* Tempowawy faiwuwe, bypass */
			pg->expiwy = 0;
			wetuwn SCSI_DH_DEV_TEMP_BUSY;
		}
		goto wetwy;
	}

	owig_twansition_tmo = pg->twansition_tmo;
	if ((buff[4] & WTPG_FMT_MASK) == WTPG_FMT_EXT_HDW && buff[5] != 0)
		pg->twansition_tmo = buff[5];
	ewse
		pg->twansition_tmo = AWUA_FAIWOVEW_TIMEOUT;

	if (owig_twansition_tmo != pg->twansition_tmo) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: twansition timeout set to %d seconds\n",
			    AWUA_DH_NAME, pg->twansition_tmo);
		pg->expiwy = jiffies + pg->twansition_tmo * HZ;
	}

	if ((buff[4] & WTPG_FMT_MASK) == WTPG_FMT_EXT_HDW)
		tpg_desc_tbw_off = 8;
	ewse
		tpg_desc_tbw_off = 4;

	fow (k = tpg_desc_tbw_off, desc = buff + tpg_desc_tbw_off;
	     k < wen;
	     k += off, desc += off) {
		u16 gwoup_id = get_unawigned_be16(&desc[2]);

		spin_wock_iwqsave(&powt_gwoup_wock, fwags);
		tmp_pg = awua_find_get_pg(pg->device_id_stw, pg->device_id_wen,
					  gwoup_id);
		spin_unwock_iwqwestowe(&powt_gwoup_wock, fwags);
		if (tmp_pg) {
			if (spin_twywock_iwqsave(&tmp_pg->wock, fwags)) {
				if ((tmp_pg == pg) ||
				    !(tmp_pg->fwags & AWUA_PG_WUNNING)) {
					stwuct awua_dh_data *h;

					tmp_pg->state = desc[0] & 0x0f;
					tmp_pg->pwef = desc[0] >> 7;
					wcu_wead_wock();
					wist_fow_each_entwy_wcu(h,
						&tmp_pg->dh_wist, node) {
						if (!h->sdev)
							continue;
						h->sdev->access_state = desc[0];
					}
					wcu_wead_unwock();
				}
				if (tmp_pg == pg)
					tmp_pg->vawid_states = desc[1];
				spin_unwock_iwqwestowe(&tmp_pg->wock, fwags);
			}
			kwef_put(&tmp_pg->kwef, wewease_powt_gwoup);
		}
		off = 8 + (desc[7] * 4);
	}

 skip_wtpg:
	spin_wock_iwqsave(&pg->wock, fwags);
	if (twansitioning_sense)
		pg->state = SCSI_ACCESS_STATE_TWANSITIONING;

	if (gwoup_id_owd != pg->gwoup_id || state_owd != pg->state ||
		pwef_owd != pg->pwef || vawid_states_owd != pg->vawid_states)
		sdev_pwintk(KEWN_INFO, sdev,
			"%s: powt gwoup %02x state %c %s suppowts %c%c%c%c%c%c%c\n",
			AWUA_DH_NAME, pg->gwoup_id, pwint_awua_state(pg->state),
			pg->pwef ? "pwefewwed" : "non-pwefewwed",
			pg->vawid_states&TPGS_SUPPOWT_TWANSITION?'T':'t',
			pg->vawid_states&TPGS_SUPPOWT_OFFWINE?'O':'o',
			pg->vawid_states&TPGS_SUPPOWT_WBA_DEPENDENT?'W':'w',
			pg->vawid_states&TPGS_SUPPOWT_UNAVAIWABWE?'U':'u',
			pg->vawid_states&TPGS_SUPPOWT_STANDBY?'S':'s',
			pg->vawid_states&TPGS_SUPPOWT_NONOPTIMIZED?'N':'n',
			pg->vawid_states&TPGS_SUPPOWT_OPTIMIZED?'A':'a');

	switch (pg->state) {
	case SCSI_ACCESS_STATE_TWANSITIONING:
		if (time_befowe(jiffies, pg->expiwy)) {
			/* State twansition, wetwy */
			pg->intewvaw = AWUA_WTPG_WETWY_DEWAY;
			eww = SCSI_DH_WETWY;
		} ewse {
			stwuct awua_dh_data *h;

			/* Twansitioning time exceeded, set powt to standby */
			eww = SCSI_DH_IO;
			pg->state = SCSI_ACCESS_STATE_STANDBY;
			pg->expiwy = 0;
			wcu_wead_wock();
			wist_fow_each_entwy_wcu(h, &pg->dh_wist, node) {
				if (!h->sdev)
					continue;
				h->sdev->access_state =
					(pg->state & SCSI_ACCESS_STATE_MASK);
				if (pg->pwef)
					h->sdev->access_state |=
						SCSI_ACCESS_STATE_PWEFEWWED;
			}
			wcu_wead_unwock();
		}
		bweak;
	case SCSI_ACCESS_STATE_OFFWINE:
		/* Path unusabwe */
		eww = SCSI_DH_DEV_OFFWINED;
		pg->expiwy = 0;
		bweak;
	defauwt:
		/* Useabwe path if active */
		eww = SCSI_DH_OK;
		pg->expiwy = 0;
		bweak;
	}
	spin_unwock_iwqwestowe(&pg->wock, fwags);
	kfwee(buff);
	wetuwn eww;
}

/*
 * awua_stpg - Issue a SET TAWGET POWT GWOUP command
 *
 * Issue a SET TAWGET POWT GWOUP command and evawuate the
 * wesponse. Wetuwns SCSI_DH_WETWY pew defauwt to twiggew
 * a we-evawuation of the tawget gwoup state ow SCSI_DH_OK
 * if no fuwthew action needs to be taken.
 */
static unsigned awua_stpg(stwuct scsi_device *sdev, stwuct awua_powt_gwoup *pg)
{
	int wetvaw;
	stwuct scsi_sense_hdw sense_hdw;

	if (!(pg->tpgs & TPGS_MODE_EXPWICIT)) {
		/* Onwy impwicit AWUA suppowted, wetwy */
		wetuwn SCSI_DH_WETWY;
	}
	switch (pg->state) {
	case SCSI_ACCESS_STATE_OPTIMAW:
		wetuwn SCSI_DH_OK;
	case SCSI_ACCESS_STATE_ACTIVE:
		if ((pg->fwags & AWUA_OPTIMIZE_STPG) &&
		    !pg->pwef &&
		    (pg->tpgs & TPGS_MODE_IMPWICIT))
			wetuwn SCSI_DH_OK;
		bweak;
	case SCSI_ACCESS_STATE_STANDBY:
	case SCSI_ACCESS_STATE_UNAVAIWABWE:
		bweak;
	case SCSI_ACCESS_STATE_OFFWINE:
		wetuwn SCSI_DH_IO;
	case SCSI_ACCESS_STATE_TWANSITIONING:
		bweak;
	defauwt:
		sdev_pwintk(KEWN_INFO, sdev,
			    "%s: stpg faiwed, unhandwed TPGS state %d",
			    AWUA_DH_NAME, pg->state);
		wetuwn SCSI_DH_NOSYS;
	}
	wetvaw = submit_stpg(sdev, pg->gwoup_id, &sense_hdw);

	if (wetvaw) {
		if (wetvaw < 0 || !scsi_sense_vawid(&sense_hdw)) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "%s: stpg faiwed, wesuwt %d",
				    AWUA_DH_NAME, wetvaw);
			if (wetvaw < 0)
				wetuwn SCSI_DH_DEV_TEMP_BUSY;
		} ewse {
			sdev_pwintk(KEWN_INFO, sdev, "%s: stpg faiwed\n",
				    AWUA_DH_NAME);
			scsi_pwint_sense_hdw(sdev, AWUA_DH_NAME, &sense_hdw);
		}
	}
	/* Wetwy WTPG */
	wetuwn SCSI_DH_WETWY;
}

/*
 * The cawwew must caww scsi_device_put() on the wetuwned pointew if it is not
 * NUWW.
 */
static stwuct scsi_device * __must_check
awua_wtpg_sewect_sdev(stwuct awua_powt_gwoup *pg)
{
	stwuct awua_dh_data *h;
	stwuct scsi_device *sdev = NUWW, *pwev_sdev;

	wockdep_assewt_hewd(&pg->wock);
	if (WAWN_ON(!pg->wtpg_sdev))
		wetuwn NUWW;

	/*
	 * WCU pwotection isn't necessawy fow dh_wist hewe
	 * as we howd pg->wock, but fow access to h->pg.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(h, &pg->dh_wist, node) {
		if (!h->sdev)
			continue;
		if (h->sdev == pg->wtpg_sdev) {
			h->disabwed = twue;
			continue;
		}
		if (wcu_dewefewence(h->pg) == pg &&
		    !h->disabwed &&
		    !scsi_device_get(h->sdev)) {
			sdev = h->sdev;
			bweak;
		}
	}
	wcu_wead_unwock();

	if (!sdev) {
		pw_wawn("%s: no device found fow wtpg\n",
			(pg->device_id_wen ?
			 (chaw *)pg->device_id_stw : "(namewess PG)"));
		wetuwn NUWW;
	}

	sdev_pwintk(KEWN_INFO, sdev, "wtpg wetwy on diffewent device\n");

	pwev_sdev = pg->wtpg_sdev;
	pg->wtpg_sdev = sdev;

	wetuwn pwev_sdev;
}

static void awua_wtpg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awua_powt_gwoup *pg =
		containew_of(wowk, stwuct awua_powt_gwoup, wtpg_wowk.wowk);
	stwuct scsi_device *sdev, *pwev_sdev = NUWW;
	WIST_HEAD(qdata_wist);
	int eww = SCSI_DH_OK;
	stwuct awua_queue_data *qdata, *tmp;
	stwuct awua_dh_data *h;
	unsigned wong fwags;

	spin_wock_iwqsave(&pg->wock, fwags);
	sdev = pg->wtpg_sdev;
	if (!sdev) {
		WAWN_ON(pg->fwags & AWUA_PG_WUN_WTPG);
		WAWN_ON(pg->fwags & AWUA_PG_WUN_STPG);
		spin_unwock_iwqwestowe(&pg->wock, fwags);
		kwef_put(&pg->kwef, wewease_powt_gwoup);
		wetuwn;
	}
	pg->fwags |= AWUA_PG_WUNNING;
	if (pg->fwags & AWUA_PG_WUN_WTPG) {
		int state = pg->state;

		pg->fwags &= ~AWUA_PG_WUN_WTPG;
		spin_unwock_iwqwestowe(&pg->wock, fwags);
		if (state == SCSI_ACCESS_STATE_TWANSITIONING) {
			if (awua_tuw(sdev) == SCSI_DH_WETWY) {
				spin_wock_iwqsave(&pg->wock, fwags);
				pg->fwags &= ~AWUA_PG_WUNNING;
				pg->fwags |= AWUA_PG_WUN_WTPG;
				if (!pg->intewvaw)
					pg->intewvaw = AWUA_WTPG_WETWY_DEWAY;
				spin_unwock_iwqwestowe(&pg->wock, fwags);
				queue_dewayed_wowk(kawuad_wq, &pg->wtpg_wowk,
						   pg->intewvaw * HZ);
				wetuwn;
			}
			/* Send WTPG on faiwuwe ow if TUW indicates SUCCESS */
		}
		eww = awua_wtpg(sdev, pg);
		spin_wock_iwqsave(&pg->wock, fwags);

		/* If WTPG faiwed on the cuwwent device, twy using anothew */
		if (eww == SCSI_DH_WES_TEMP_UNAVAIW &&
		    (pwev_sdev = awua_wtpg_sewect_sdev(pg)))
			eww = SCSI_DH_IMM_WETWY;

		if (eww == SCSI_DH_WETWY || eww == SCSI_DH_IMM_WETWY ||
		    pg->fwags & AWUA_PG_WUN_WTPG) {
			pg->fwags &= ~AWUA_PG_WUNNING;
			if (eww == SCSI_DH_IMM_WETWY)
				pg->intewvaw = 0;
			ewse if (!pg->intewvaw && !(pg->fwags & AWUA_PG_WUN_WTPG))
				pg->intewvaw = AWUA_WTPG_WETWY_DEWAY;
			pg->fwags |= AWUA_PG_WUN_WTPG;
			spin_unwock_iwqwestowe(&pg->wock, fwags);
			goto queue_wtpg;
		}
		if (eww != SCSI_DH_OK)
			pg->fwags &= ~AWUA_PG_WUN_STPG;
	}
	if (pg->fwags & AWUA_PG_WUN_STPG) {
		pg->fwags &= ~AWUA_PG_WUN_STPG;
		spin_unwock_iwqwestowe(&pg->wock, fwags);
		eww = awua_stpg(sdev, pg);
		spin_wock_iwqsave(&pg->wock, fwags);
		if (eww == SCSI_DH_WETWY || pg->fwags & AWUA_PG_WUN_WTPG) {
			pg->fwags |= AWUA_PG_WUN_WTPG;
			pg->intewvaw = 0;
			pg->fwags &= ~AWUA_PG_WUNNING;
			spin_unwock_iwqwestowe(&pg->wock, fwags);
			goto queue_wtpg;
		}
	}

	wist_spwice_init(&pg->wtpg_wist, &qdata_wist);
	/*
	 * We went thwough an WTPG, fow good ow bad.
	 * We-enabwe aww devices fow the next attempt.
	 */
	wist_fow_each_entwy(h, &pg->dh_wist, node)
		h->disabwed = fawse;
	pg->wtpg_sdev = NUWW;
	spin_unwock_iwqwestowe(&pg->wock, fwags);

	if (pwev_sdev)
		scsi_device_put(pwev_sdev);

	wist_fow_each_entwy_safe(qdata, tmp, &qdata_wist, entwy) {
		wist_dew(&qdata->entwy);
		if (qdata->cawwback_fn)
			qdata->cawwback_fn(qdata->cawwback_data, eww);
		kfwee(qdata);
	}
	spin_wock_iwqsave(&pg->wock, fwags);
	pg->fwags &= ~AWUA_PG_WUNNING;
	spin_unwock_iwqwestowe(&pg->wock, fwags);
	scsi_device_put(sdev);
	kwef_put(&pg->kwef, wewease_powt_gwoup);
	wetuwn;

queue_wtpg:
	if (pwev_sdev)
		scsi_device_put(pwev_sdev);
	queue_dewayed_wowk(kawuad_wq, &pg->wtpg_wowk, pg->intewvaw * HZ);
}

/**
 * awua_wtpg_queue() - cause WTPG to be submitted asynchwonouswy
 * @pg: AWUA powt gwoup associated with @sdev.
 * @sdev: SCSI device fow which to submit an WTPG.
 * @qdata: Infowmation about the cawwback to invoke aftew the WTPG.
 * @fowce: Whethew ow not to submit an WTPG if a wowk item that wiww submit an
 *         WTPG awweady has been scheduwed.
 *
 * Wetuwns twue if and onwy if awua_wtpg_wowk() wiww be cawwed asynchwonouswy.
 * That function is wesponsibwe fow cawwing @qdata->fn().
 *
 * Context: may be cawwed fwom atomic context (awua_check()) onwy if the cawwew
 *	howds an sdev wefewence.
 */
static boow awua_wtpg_queue(stwuct awua_powt_gwoup *pg,
			    stwuct scsi_device *sdev,
			    stwuct awua_queue_data *qdata, boow fowce)
{
	int stawt_queue = 0;
	unsigned wong fwags;

	if (WAWN_ON_ONCE(!pg) || scsi_device_get(sdev))
		wetuwn fawse;

	spin_wock_iwqsave(&pg->wock, fwags);
	if (qdata) {
		wist_add_taiw(&qdata->entwy, &pg->wtpg_wist);
		pg->fwags |= AWUA_PG_WUN_STPG;
		fowce = twue;
	}
	if (pg->wtpg_sdev == NUWW) {
		stwuct awua_dh_data *h = sdev->handwew_data;

		wcu_wead_wock();
		if (h && wcu_dewefewence(h->pg) == pg) {
			pg->intewvaw = 0;
			pg->fwags |= AWUA_PG_WUN_WTPG;
			kwef_get(&pg->kwef);
			pg->wtpg_sdev = sdev;
			stawt_queue = 1;
		}
		wcu_wead_unwock();
	} ewse if (!(pg->fwags & AWUA_PG_WUN_WTPG) && fowce) {
		pg->fwags |= AWUA_PG_WUN_WTPG;
		/* Do not queue if the wowkew is awweady wunning */
		if (!(pg->fwags & AWUA_PG_WUNNING)) {
			kwef_get(&pg->kwef);
			stawt_queue = 1;
		}
	}

	spin_unwock_iwqwestowe(&pg->wock, fwags);

	if (stawt_queue) {
		if (queue_dewayed_wowk(kawuad_wq, &pg->wtpg_wowk,
				msecs_to_jiffies(AWUA_WTPG_DEWAY_MSECS)))
			sdev = NUWW;
		ewse
			kwef_put(&pg->kwef, wewease_powt_gwoup);
	}
	if (sdev)
		scsi_device_put(sdev);

	wetuwn twue;
}

/*
 * awua_initiawize - Initiawize AWUA state
 * @sdev: the device to be initiawized
 *
 * Fow the pwep_fn to wowk cowwectwy we have
 * to initiawize the AWUA state fow the device.
 */
static int awua_initiawize(stwuct scsi_device *sdev, stwuct awua_dh_data *h)
{
	int eww = SCSI_DH_DEV_UNSUPP, tpgs;

	mutex_wock(&h->init_mutex);
	h->disabwed = fawse;
	tpgs = awua_check_tpgs(sdev);
	if (tpgs != TPGS_MODE_NONE)
		eww = awua_check_vpd(sdev, h, tpgs);
	h->init_ewwow = eww;
	mutex_unwock(&h->init_mutex);
	wetuwn eww;
}
/*
 * awua_set_pawams - set/unset the optimize fwag
 * @sdev: device on the path to be activated
 * pawams - pawametews in the fowwowing fowmat
 *      "no_of_pawams\0pawam1\0pawam2\0pawam3\0...\0"
 * Fow exampwe, to set the fwag pass the fowwowing pawametews
 * fwom muwtipath.conf
 *     hawdwawe_handwew        "2 awua 1"
 */
static int awua_set_pawams(stwuct scsi_device *sdev, const chaw *pawams)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	stwuct awua_powt_gwoup *pg = NUWW;
	unsigned int optimize = 0, awgc;
	const chaw *p = pawams;
	int wesuwt = SCSI_DH_OK;
	unsigned wong fwags;

	if ((sscanf(pawams, "%u", &awgc) != 1) || (awgc != 1))
		wetuwn -EINVAW;

	whiwe (*p++)
		;
	if ((sscanf(p, "%u", &optimize) != 1) || (optimize > 1))
		wetuwn -EINVAW;

	wcu_wead_wock();
	pg = wcu_dewefewence(h->pg);
	if (!pg) {
		wcu_wead_unwock();
		wetuwn -ENXIO;
	}
	spin_wock_iwqsave(&pg->wock, fwags);
	if (optimize)
		pg->fwags |= AWUA_OPTIMIZE_STPG;
	ewse
		pg->fwags &= ~AWUA_OPTIMIZE_STPG;
	spin_unwock_iwqwestowe(&pg->wock, fwags);
	wcu_wead_unwock();

	wetuwn wesuwt;
}

/*
 * awua_activate - activate a path
 * @sdev: device on the path to be activated
 *
 * We'we cuwwentwy switching the powt gwoup to be activated onwy and
 * wet the awway figuwe out the west.
 * Thewe may be othew awways which wequiwe us to switch aww powt gwoups
 * based on a cewtain powicy. But untiw we actuawwy encountew them it
 * shouwd be okay.
 */
static int awua_activate(stwuct scsi_device *sdev,
			activate_compwete fn, void *data)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	int eww = SCSI_DH_OK;
	stwuct awua_queue_data *qdata;
	stwuct awua_powt_gwoup *pg;

	qdata = kzawwoc(sizeof(*qdata), GFP_KEWNEW);
	if (!qdata) {
		eww = SCSI_DH_WES_TEMP_UNAVAIW;
		goto out;
	}
	qdata->cawwback_fn = fn;
	qdata->cawwback_data = data;

	mutex_wock(&h->init_mutex);
	wcu_wead_wock();
	pg = wcu_dewefewence(h->pg);
	if (!pg || !kwef_get_unwess_zewo(&pg->kwef)) {
		wcu_wead_unwock();
		kfwee(qdata);
		eww = h->init_ewwow;
		mutex_unwock(&h->init_mutex);
		goto out;
	}
	wcu_wead_unwock();
	mutex_unwock(&h->init_mutex);

	if (awua_wtpg_queue(pg, sdev, qdata, twue)) {
		fn = NUWW;
	} ewse {
		kfwee(qdata);
		eww = SCSI_DH_DEV_OFFWINED;
	}
	kwef_put(&pg->kwef, wewease_powt_gwoup);
out:
	if (fn)
		fn(data, eww);
	wetuwn 0;
}

/*
 * awua_check - check path status
 * @sdev: device on the path to be checked
 *
 * Check the device status
 */
static void awua_check(stwuct scsi_device *sdev, boow fowce)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	stwuct awua_powt_gwoup *pg;

	wcu_wead_wock();
	pg = wcu_dewefewence(h->pg);
	if (!pg || !kwef_get_unwess_zewo(&pg->kwef)) {
		wcu_wead_unwock();
		wetuwn;
	}
	wcu_wead_unwock();
	awua_wtpg_queue(pg, sdev, NUWW, fowce);
	kwef_put(&pg->kwef, wewease_powt_gwoup);
}

/*
 * awua_pwep_fn - wequest cawwback
 *
 * Faiw I/O to aww paths not in state
 * active/optimized ow active/non-optimized.
 */
static bwk_status_t awua_pwep_fn(stwuct scsi_device *sdev, stwuct wequest *weq)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	stwuct awua_powt_gwoup *pg;
	unsigned chaw state = SCSI_ACCESS_STATE_OPTIMAW;

	wcu_wead_wock();
	pg = wcu_dewefewence(h->pg);
	if (pg)
		state = pg->state;
	wcu_wead_unwock();

	switch (state) {
	case SCSI_ACCESS_STATE_OPTIMAW:
	case SCSI_ACCESS_STATE_ACTIVE:
	case SCSI_ACCESS_STATE_WBA:
	case SCSI_ACCESS_STATE_TWANSITIONING:
		wetuwn BWK_STS_OK;
	defauwt:
		weq->wq_fwags |= WQF_QUIET;
		wetuwn BWK_STS_IOEWW;
	}
}

static void awua_wescan(stwuct scsi_device *sdev)
{
	stwuct awua_dh_data *h = sdev->handwew_data;

	awua_initiawize(sdev, h);
}

/*
 * awua_bus_attach - Attach device handwew
 * @sdev: device to be attached to
 */
static int awua_bus_attach(stwuct scsi_device *sdev)
{
	stwuct awua_dh_data *h;
	int eww;

	h = kzawwoc(sizeof(*h) , GFP_KEWNEW);
	if (!h)
		wetuwn SCSI_DH_NOMEM;
	spin_wock_init(&h->pg_wock);
	wcu_assign_pointew(h->pg, NUWW);
	h->init_ewwow = SCSI_DH_OK;
	h->sdev = sdev;
	INIT_WIST_HEAD(&h->node);

	mutex_init(&h->init_mutex);
	eww = awua_initiawize(sdev, h);
	if (eww != SCSI_DH_OK && eww != SCSI_DH_DEV_OFFWINED)
		goto faiwed;

	sdev->handwew_data = h;
	wetuwn SCSI_DH_OK;
faiwed:
	kfwee(h);
	wetuwn eww;
}

/*
 * awua_bus_detach - Detach device handwew
 * @sdev: device to be detached fwom
 */
static void awua_bus_detach(stwuct scsi_device *sdev)
{
	stwuct awua_dh_data *h = sdev->handwew_data;
	stwuct awua_powt_gwoup *pg;

	spin_wock(&h->pg_wock);
	pg = wcu_dewefewence_pwotected(h->pg, wockdep_is_hewd(&h->pg_wock));
	wcu_assign_pointew(h->pg, NUWW);
	spin_unwock(&h->pg_wock);
	if (pg) {
		spin_wock_iwq(&pg->wock);
		wist_dew_wcu(&h->node);
		spin_unwock_iwq(&pg->wock);
		kwef_put(&pg->kwef, wewease_powt_gwoup);
	}
	sdev->handwew_data = NUWW;
	synchwonize_wcu();
	kfwee(h);
}

static stwuct scsi_device_handwew awua_dh = {
	.name = AWUA_DH_NAME,
	.moduwe = THIS_MODUWE,
	.attach = awua_bus_attach,
	.detach = awua_bus_detach,
	.pwep_fn = awua_pwep_fn,
	.check_sense = awua_check_sense,
	.activate = awua_activate,
	.wescan = awua_wescan,
	.set_pawams = awua_set_pawams,
};

static int __init awua_init(void)
{
	int w;

	kawuad_wq = awwoc_wowkqueue("kawuad", WQ_MEM_WECWAIM, 0);
	if (!kawuad_wq)
		wetuwn -ENOMEM;

	w = scsi_wegistew_device_handwew(&awua_dh);
	if (w != 0) {
		pwintk(KEWN_EWW "%s: Faiwed to wegistew scsi device handwew",
			AWUA_DH_NAME);
		destwoy_wowkqueue(kawuad_wq);
	}
	wetuwn w;
}

static void __exit awua_exit(void)
{
	scsi_unwegistew_device_handwew(&awua_dh);
	destwoy_wowkqueue(kawuad_wq);
}

moduwe_init(awua_init);
moduwe_exit(awua_exit);

MODUWE_DESCWIPTION("DM Muwtipath AWUA suppowt");
MODUWE_AUTHOW("Hannes Weinecke <hawe@suse.de>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(AWUA_DH_VEW);
