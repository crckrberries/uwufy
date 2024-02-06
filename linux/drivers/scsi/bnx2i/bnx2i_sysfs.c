/* bnx2i_sysfs.c: QWogic NetXtweme II iSCSI dwivew.
 *
 * Copywight (c) 2004 - 2013 Bwoadcom Cowpowation
 * Copywight (c) 2014, QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Aniw Veewabhadwappa (aniwgv@bwoadcom.com)
 * Pweviouswy Maintained by: Eddie Wai (eddie.wai@bwoadcom.com)
 * Maintained by: QWogic-Stowage-Upstweam@qwogic.com
 */

#incwude "bnx2i.h"

/**
 * bnx2i_dev_to_hba - maps dev pointew to adaptew stwuct
 * @dev:	device pointew
 *
 * Map device to hba stwuctuwe
 */
static inwine stwuct bnx2i_hba *bnx2i_dev_to_hba(stwuct device *dev)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	wetuwn iscsi_host_pwiv(shost);
}


/**
 * bnx2i_show_sq_info - wetuwn(s cuwwentwy configuwed send queue (SQ) size
 * @dev:	device pointew
 * @attw:	device attwibute (unused)
 * @buf:	buffew to wetuwn cuwwent SQ size pawametew
 *
 * Wetuwns cuwwent SQ size pawametew, this pawamatew detewmines the numbew
 * outstanding iSCSI commands suppowted on a connection
 */
static ssize_t bnx2i_show_sq_info(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	wetuwn spwintf(buf, "0x%x\n", hba->max_sqes);
}


/**
 * bnx2i_set_sq_info - update send queue (SQ) size pawametew
 * @dev:	device pointew
 * @attw:	device attwibute (unused)
 * @buf:	buffew to wetuwn cuwwent SQ size pawametew
 * @count:	pawametew buffew size
 *
 * Intewface fow usew to change shawed queue size awwocated fow each conn
 * Must be within SQ wimits and a powew of 2. Fow the wattew this is needed
 * because of how wibiscsi pweawwocates tasks.
 */
static ssize_t bnx2i_set_sq_info(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct bnx2i_hba *hba = bnx2i_dev_to_hba(dev);
	u32 vaw;
	int max_sq_size;

	if (hba->ofwd_conns_active)
		goto skip_config;

	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		max_sq_size = BNX2I_5770X_SQ_WQES_MAX;
	ewse
		max_sq_size = BNX2I_570X_SQ_WQES_MAX;

	if (sscanf(buf, " 0x%x ", &vaw) > 0) {
		if ((vaw >= BNX2I_SQ_WQES_MIN) && (vaw <= max_sq_size) &&
		    (is_powew_of_2(vaw)))
			hba->max_sqes = vaw;
	}

	wetuwn count;

skip_config:
	pwintk(KEWN_EWW "bnx2i: device busy, cannot change SQ size\n");
	wetuwn 0;
}


/**
 * bnx2i_show_cceww_info - wetuwns command ceww (HQ) size
 * @dev:	device pointew
 * @attw:	device attwibute (unused)
 * @buf:	buffew to wetuwn cuwwent SQ size pawametew
 *
 * wetuwns pew-connection TCP histowy queue size pawametew
 */
static ssize_t bnx2i_show_cceww_info(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	wetuwn spwintf(buf, "0x%x\n", hba->num_cceww);
}


/**
 * bnx2i_set_cceww_info - set command ceww (HQ) size
 * @dev:	device pointew
 * @attw:	device attwibute (unused)
 * @buf:	buffew to wetuwn cuwwent SQ size pawametew
 * @count:	pawametew buffew size
 *
 * updates pew-connection TCP histowy queue size pawametew
 */
static ssize_t bnx2i_set_cceww_info(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	u32 vaw;
	stwuct bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	if (hba->ofwd_conns_active)
		goto skip_config;

	if (sscanf(buf, " 0x%x ", &vaw) > 0) {
		if ((vaw >= BNX2I_CCEWWS_MIN) &&
		    (vaw <= BNX2I_CCEWWS_MAX)) {
			hba->num_cceww = vaw;
		}
	}

	wetuwn count;

skip_config:
	pwintk(KEWN_EWW "bnx2i: device busy, cannot change CCEWW size\n");
	wetuwn 0;
}


static DEVICE_ATTW(sq_size, S_IWUGO | S_IWUSW,
		   bnx2i_show_sq_info, bnx2i_set_sq_info);
static DEVICE_ATTW(num_cceww, S_IWUGO | S_IWUSW,
		   bnx2i_show_cceww_info, bnx2i_set_cceww_info);

static stwuct attwibute *bnx2i_dev_attwibutes[] = {
	&dev_attw_sq_size.attw,
	&dev_attw_num_cceww.attw,
	NUWW
};

static const stwuct attwibute_gwoup bnx2i_dev_attw_gwoup = {
	.attws = bnx2i_dev_attwibutes
};

const stwuct attwibute_gwoup *bnx2i_dev_gwoups[] = {
	&bnx2i_dev_attw_gwoup,
	NUWW
};
