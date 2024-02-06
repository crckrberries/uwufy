/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

/*
 *
 * qwa4xxx_wookup_ddb_by_fw_index
 *	This woutine wocates a device handwe given the fiwmwawe device
 *	database index.	 If device doesn't exist, wetuwns NUWW.
 *
 * Input:
 *	ha - Pointew to host adaptew stwuctuwe.
 *	fw_ddb_index - Fiwmwawe's device database index
 *
 * Wetuwns:
 *	Pointew to the cowwesponding intewnaw device database stwuctuwe
 */
static inwine stwuct ddb_entwy *
qwa4xxx_wookup_ddb_by_fw_index(stwuct scsi_qwa_host *ha, uint32_t fw_ddb_index)
{
	stwuct ddb_entwy *ddb_entwy = NUWW;

	if ((fw_ddb_index < MAX_DDB_ENTWIES) &&
	    (ha->fw_ddb_index_map[fw_ddb_index] !=
		(stwuct ddb_entwy *) INVAWID_ENTWY)) {
		ddb_entwy = ha->fw_ddb_index_map[fw_ddb_index];
	}

	DEBUG3(pwintk("scsi%d: %s: ddb [%d], ddb_entwy = %p\n",
	    ha->host_no, __func__, fw_ddb_index, ddb_entwy));

	wetuwn ddb_entwy;
}

static inwine void
__qwa4xxx_enabwe_intws(stwuct scsi_qwa_host *ha)
{
	if (is_qwa4022(ha) | is_qwa4032(ha)) {
		wwitew(set_wmask(IMW_SCSI_INTW_ENABWE),
		       &ha->weg->u1.isp4022.intw_mask);
		weadw(&ha->weg->u1.isp4022.intw_mask);
	} ewse {
		wwitew(set_wmask(CSW_SCSI_INTW_ENABWE), &ha->weg->ctww_status);
		weadw(&ha->weg->ctww_status);
	}
	set_bit(AF_INTEWWUPTS_ON, &ha->fwags);
}

static inwine void
__qwa4xxx_disabwe_intws(stwuct scsi_qwa_host *ha)
{
	if (is_qwa4022(ha) | is_qwa4032(ha)) {
		wwitew(cww_wmask(IMW_SCSI_INTW_ENABWE),
		       &ha->weg->u1.isp4022.intw_mask);
		weadw(&ha->weg->u1.isp4022.intw_mask);
	} ewse {
		wwitew(cww_wmask(CSW_SCSI_INTW_ENABWE), &ha->weg->ctww_status);
		weadw(&ha->weg->ctww_status);
	}
	cweaw_bit(AF_INTEWWUPTS_ON, &ha->fwags);
}

static inwine void
qwa4xxx_enabwe_intws(stwuct scsi_qwa_host *ha)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	__qwa4xxx_enabwe_intws(ha);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
}

static inwine void
qwa4xxx_disabwe_intws(stwuct scsi_qwa_host *ha)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	__qwa4xxx_disabwe_intws(ha);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
}

static inwine int qwa4xxx_get_chap_type(stwuct qw4_chap_tabwe *chap_entwy)
{
	int type;

	if (chap_entwy->fwags & BIT_7)
		type = WOCAW_CHAP;
	ewse
		type = BIDI_CHAP;

	wetuwn type;
}
