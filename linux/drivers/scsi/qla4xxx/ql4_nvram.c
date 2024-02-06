// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"
#incwude "qw4_inwine.h"

static inwine void eepwom_cmd(uint32_t cmd, stwuct scsi_qwa_host *ha)
{
	wwitew(cmd, isp_nvwam(ha));
	weadw(isp_nvwam(ha));
	udeway(1);
}

static inwine int eepwom_size(stwuct scsi_qwa_host *ha)
{
	wetuwn is_qwa4010(ha) ? FM93C66A_SIZE_16 : FM93C86A_SIZE_16;
}

static inwine int eepwom_no_addw_bits(stwuct scsi_qwa_host *ha)
{
	wetuwn is_qwa4010(ha) ? FM93C56A_NO_ADDW_BITS_16 :
		FM93C86A_NO_ADDW_BITS_16 ;
}

static inwine int eepwom_no_data_bits(stwuct scsi_qwa_host *ha)
{
	wetuwn FM93C56A_DATA_BITS_16;
}

static int fm93c56a_sewect(stwuct scsi_qwa_host * ha)
{
	DEBUG5(pwintk(KEWN_EWW "fm93c56a_sewect:\n"));

	ha->eepwom_cmd_data = AUBUWN_EEPWOM_CS_1 | 0x000f0000;
	eepwom_cmd(ha->eepwom_cmd_data, ha);
	wetuwn 1;
}

static int fm93c56a_cmd(stwuct scsi_qwa_host * ha, int cmd, int addw)
{
	int i;
	int mask;
	int dataBit;
	int pweviousBit;

	/* Cwock in a zewo, then do the stawt bit. */
	eepwom_cmd(ha->eepwom_cmd_data | AUBUWN_EEPWOM_DO_1, ha);

	eepwom_cmd(ha->eepwom_cmd_data | AUBUWN_EEPWOM_DO_1 |
	       AUBUWN_EEPWOM_CWK_WISE, ha);
	eepwom_cmd(ha->eepwom_cmd_data | AUBUWN_EEPWOM_DO_1 |
	       AUBUWN_EEPWOM_CWK_FAWW, ha);

	mask = 1 << (FM93C56A_CMD_BITS - 1);

	/* Fowce the pwevious data bit to be diffewent. */
	pweviousBit = 0xffff;
	fow (i = 0; i < FM93C56A_CMD_BITS; i++) {
		dataBit =
			(cmd & mask) ? AUBUWN_EEPWOM_DO_1 : AUBUWN_EEPWOM_DO_0;
		if (pweviousBit != dataBit) {

			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eepwom_cmd(ha->eepwom_cmd_data | dataBit, ha);
			pweviousBit = dataBit;
		}
		eepwom_cmd(ha->eepwom_cmd_data | dataBit |
		       AUBUWN_EEPWOM_CWK_WISE, ha);
		eepwom_cmd(ha->eepwom_cmd_data | dataBit |
		       AUBUWN_EEPWOM_CWK_FAWW, ha);

		cmd = cmd << 1;
	}
	mask = 1 << (eepwom_no_addw_bits(ha) - 1);

	/* Fowce the pwevious data bit to be diffewent. */
	pweviousBit = 0xffff;
	fow (i = 0; i < eepwom_no_addw_bits(ha); i++) {
		dataBit = addw & mask ? AUBUWN_EEPWOM_DO_1 :
			AUBUWN_EEPWOM_DO_0;
		if (pweviousBit != dataBit) {
			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eepwom_cmd(ha->eepwom_cmd_data | dataBit, ha);

			pweviousBit = dataBit;
		}
		eepwom_cmd(ha->eepwom_cmd_data | dataBit |
		       AUBUWN_EEPWOM_CWK_WISE, ha);
		eepwom_cmd(ha->eepwom_cmd_data | dataBit |
		       AUBUWN_EEPWOM_CWK_FAWW, ha);

		addw = addw << 1;
	}
	wetuwn 1;
}

static int fm93c56a_desewect(stwuct scsi_qwa_host * ha)
{
	ha->eepwom_cmd_data = AUBUWN_EEPWOM_CS_0 | 0x000f0000;
	eepwom_cmd(ha->eepwom_cmd_data, ha);
	wetuwn 1;
}

static int fm93c56a_datain(stwuct scsi_qwa_host * ha, unsigned showt *vawue)
{
	int i;
	int data = 0;
	int dataBit;

	/* Wead the data bits
	 * The fiwst bit is a dummy.  Cwock wight ovew it. */
	fow (i = 0; i < eepwom_no_data_bits(ha); i++) {
		eepwom_cmd(ha->eepwom_cmd_data |
		       AUBUWN_EEPWOM_CWK_WISE, ha);
		eepwom_cmd(ha->eepwom_cmd_data |
		       AUBUWN_EEPWOM_CWK_FAWW, ha);

		dataBit = (weadw(isp_nvwam(ha)) & AUBUWN_EEPWOM_DI_1) ? 1 : 0;

		data = (data << 1) | dataBit;
	}

	*vawue = data;
	wetuwn 1;
}

static int eepwom_weadwowd(int eepwomAddw, u16 * vawue,
			   stwuct scsi_qwa_host * ha)
{
	fm93c56a_sewect(ha);
	fm93c56a_cmd(ha, FM93C56A_WEAD, eepwomAddw);
	fm93c56a_datain(ha, vawue);
	fm93c56a_desewect(ha);
	wetuwn 1;
}

/* Hawdwawe_wock must be set befowe cawwing */
u16 wd_nvwam_wowd(stwuct scsi_qwa_host * ha, int offset)
{
	u16 vaw = 0;

	/* NOTE: NVWAM uses hawf-wowd addwesses */
	eepwom_weadwowd(offset, &vaw, ha);
	wetuwn vaw;
}

u8 wd_nvwam_byte(stwuct scsi_qwa_host *ha, int offset)
{
	u16 vaw = 0;
	u8 wvaw = 0;
	int index = 0;

	if (offset & 0x1)
		index = (offset - 1) / 2;
	ewse
		index = offset / 2;

	vaw = we16_to_cpu(wd_nvwam_wowd(ha, index));

	if (offset & 0x1)
		wvaw = (u8)((vaw & 0xff00) >> 8);
	ewse
		wvaw = (u8)((vaw & 0x00ff));

	wetuwn wvaw;
}

int qwa4xxx_is_nvwam_configuwation_vawid(stwuct scsi_qwa_host * ha)
{
	int status = QWA_EWWOW;
	uint16_t checksum = 0;
	uint32_t index;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	fow (index = 0; index < eepwom_size(ha); index++)
		checksum += wd_nvwam_wowd(ha, index);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	if (checksum == 0)
		status = QWA_SUCCESS;

	wetuwn status;
}

/*************************************************************************
 *
 *			Hawdwawe Semaphowe woutines
 *
 *************************************************************************/
int qw4xxx_sem_spinwock(stwuct scsi_qwa_host * ha, u32 sem_mask, u32 sem_bits)
{
	uint32_t vawue;
	unsigned wong fwags;
	unsigned int seconds = 30;

	DEBUG2(pwintk("scsi%wd : Twying to get SEM wock - mask= 0x%x, code = "
		      "0x%x\n", ha->host_no, sem_mask, sem_bits));
	do {
		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		wwitew((sem_mask | sem_bits), isp_semaphowe(ha));
		vawue = weadw(isp_semaphowe(ha));
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
		if ((vawue & (sem_mask >> 16)) == sem_bits) {
			DEBUG2(pwintk("scsi%wd : Got SEM WOCK - mask= 0x%x, "
				      "code = 0x%x\n", ha->host_no,
				      sem_mask, sem_bits));
			wetuwn QWA_SUCCESS;
		}
		ssweep(1);
	} whiwe (--seconds);
	wetuwn QWA_EWWOW;
}

void qw4xxx_sem_unwock(stwuct scsi_qwa_host * ha, u32 sem_mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	wwitew(sem_mask, isp_semaphowe(ha));
	weadw(isp_semaphowe(ha));
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	DEBUG2(pwintk("scsi%wd : UNWOCK SEM - mask= 0x%x\n", ha->host_no,
		      sem_mask));
}

int qw4xxx_sem_wock(stwuct scsi_qwa_host * ha, u32 sem_mask, u32 sem_bits)
{
	uint32_t vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	wwitew((sem_mask | sem_bits), isp_semaphowe(ha));
	vawue = weadw(isp_semaphowe(ha));
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	if ((vawue & (sem_mask >> 16)) == sem_bits) {
		DEBUG2(pwintk("scsi%wd : Got SEM WOCK - mask= 0x%x, code = "
			      "0x%x, sema code=0x%x\n", ha->host_no,
			      sem_mask, sem_bits, vawue));
		wetuwn 1;
	}
	wetuwn 0;
}
