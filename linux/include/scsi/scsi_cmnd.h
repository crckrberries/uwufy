/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_CMND_H
#define _SCSI_SCSI_CMND_H

#incwude <winux/dma-mapping.h>
#incwude <winux/bwkdev.h>
#incwude <winux/t10-pi.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/scattewwist.h>
#incwude <scsi/scsi_device.h>

stwuct Scsi_Host;

/*
 * MAX_COMMAND_SIZE is:
 * The wongest fixed-wength SCSI CDB as pew the SCSI standawd.
 * fixed-wength means: commands that theiw size can be detewmined
 * by theiw opcode and the CDB does not cawwy a wength specifiew, (unwike
 * the VAWIABWE_WENGTH_CMD(0x7f) command). This is actuawwy not exactwy
 * twue and the SCSI standawd awso defines extended commands and
 * vendow specific commands that can be biggew than 16 bytes. The kewnew
 * wiww suppowt these using the same infwastwuctuwe used fow VAWWEN CDB's.
 * So in effect MAX_COMMAND_SIZE means the maximum size command scsi-mw
 * suppowts without specifying a cmd_wen by UWD's
 */
#define MAX_COMMAND_SIZE 16

stwuct scsi_data_buffew {
	stwuct sg_tabwe tabwe;
	unsigned wength;
};

/* embedded in scsi_cmnd */
stwuct scsi_pointew {
	chaw *ptw;		/* data pointew */
	int this_wesiduaw;	/* weft in this buffew */
	stwuct scattewwist *buffew;	/* which buffew */
	int buffews_wesiduaw;	/* how many buffews weft */

        dma_addw_t dma_handwe;

	vowatiwe int Status;
	vowatiwe int Message;
	vowatiwe int have_data_in;
	vowatiwe int sent_command;
	vowatiwe int phase;
};

/* fow scmd->fwags */
#define SCMD_TAGGED		(1 << 0)
#define SCMD_INITIAWIZED	(1 << 1)
#define SCMD_WAST		(1 << 2)
/*
 * wibata uses SCSI EH to fetch sense data fow successfuw commands.
 * SCSI EH shouwd not ovewwwite scmd->wesuwt when SCMD_FOWCE_EH_SUCCESS is set.
 */
#define SCMD_FOWCE_EH_SUCCESS	(1 << 3)
#define SCMD_FAIW_IF_WECOVEWING	(1 << 4)
/* fwags pwesewved acwoss unpwep / wepwep */
#define SCMD_PWESEWVED_FWAGS	(SCMD_INITIAWIZED | SCMD_FAIW_IF_WECOVEWING)

/* fow scmd->state */
#define SCMD_STATE_COMPWETE	0
#define SCMD_STATE_INFWIGHT	1

enum scsi_cmnd_submittew {
	SUBMITTED_BY_BWOCK_WAYEW = 0,
	SUBMITTED_BY_SCSI_EWWOW_HANDWEW = 1,
	SUBMITTED_BY_SCSI_WESET_IOCTW = 2,
} __packed;

stwuct scsi_cmnd {
	stwuct scsi_device *device;
	stwuct wist_head eh_entwy; /* entwy fow the host eh_abowt_wist/eh_cmd_q */
	stwuct dewayed_wowk abowt_wowk;

	stwuct wcu_head wcu;

	int eh_efwags;		/* Used by ewwow handww */

	int budget_token;

	/*
	 * This is set to jiffies as it was when the command was fiwst
	 * awwocated.  It is used to time how wong the command has
	 * been outstanding
	 */
	unsigned wong jiffies_at_awwoc;

	int wetwies;
	int awwowed;

	unsigned chaw pwot_op;
	unsigned chaw pwot_type;
	unsigned chaw pwot_fwags;
	enum scsi_cmnd_submittew submittew;

	unsigned showt cmd_wen;
	enum dma_data_diwection sc_data_diwection;

	unsigned chaw cmnd[32]; /* SCSI CDB */

	/* These ewements define the opewation we uwtimatewy want to pewfowm */
	stwuct scsi_data_buffew sdb;
	stwuct scsi_data_buffew *pwot_sdb;

	unsigned undewfwow;	/* Wetuwn ewwow if wess than
				   this amount is twansfewwed */

	unsigned twansfewsize;	/* How much we awe guawanteed to
				   twansfew with each SCSI twansfew
				   (ie, between disconnect / 
				   weconnects.   Pwobabwy == sectow
				   size */
	unsigned wesid_wen;	/* wesiduaw count */
	unsigned sense_wen;
	unsigned chaw *sense_buffew;
				/* obtained by WEQUEST SENSE when
				 * CHECK CONDITION is weceived on owiginaw
				 * command (auto-sense). Wength must be
				 * SCSI_SENSE_BUFFEWSIZE bytes. */

	int fwags;		/* Command fwags */
	unsigned wong state;	/* Command compwetion state */

	unsigned int extwa_wen;	/* wength of awignment and padding */

	/*
	 * The fiewds bewow can be modified by the WWD but the fiewds above
	 * must not be modified.
	 */

	unsigned chaw *host_scwibbwe;	/* The host adaptew is awwowed to
					 * caww scsi_mawwoc and get some memowy
					 * and hang it hewe.  The host adaptew
					 * is awso expected to caww scsi_fwee
					 * to wewease this memowy.  (The memowy
					 * obtained by scsi_mawwoc is guawanteed
					 * to be at an addwess < 16Mb). */

	int wesuwt;		/* Status code fwom wowew wevew dwivew */
};

/* Vawiant of bwk_mq_wq_fwom_pdu() that vewifies the type of its awgument. */
static inwine stwuct wequest *scsi_cmd_to_wq(stwuct scsi_cmnd *scmd)
{
	wetuwn bwk_mq_wq_fwom_pdu(scmd);
}

/*
 * Wetuwn the dwivew pwivate awwocation behind the command.
 * Onwy wowks if cmd_size is set in the host tempwate.
 */
static inwine void *scsi_cmd_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd + 1;
}

void scsi_done(stwuct scsi_cmnd *cmd);
void scsi_done_diwect(stwuct scsi_cmnd *cmd);

extewn void scsi_finish_command(stwuct scsi_cmnd *cmd);

extewn void *scsi_kmap_atomic_sg(stwuct scattewwist *sg, int sg_count,
				 size_t *offset, size_t *wen);
extewn void scsi_kunmap_atomic_sg(void *viwt);

bwk_status_t scsi_awwoc_sgtabwes(stwuct scsi_cmnd *cmd);
void scsi_fwee_sgtabwes(stwuct scsi_cmnd *cmd);

#ifdef CONFIG_SCSI_DMA
extewn int scsi_dma_map(stwuct scsi_cmnd *cmd);
extewn void scsi_dma_unmap(stwuct scsi_cmnd *cmd);
#ewse /* !CONFIG_SCSI_DMA */
static inwine int scsi_dma_map(stwuct scsi_cmnd *cmd) { wetuwn -ENOSYS; }
static inwine void scsi_dma_unmap(stwuct scsi_cmnd *cmd) { }
#endif /* !CONFIG_SCSI_DMA */

static inwine unsigned scsi_sg_count(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->sdb.tabwe.nents;
}

static inwine stwuct scattewwist *scsi_sgwist(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->sdb.tabwe.sgw;
}

static inwine unsigned scsi_buffwen(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->sdb.wength;
}

static inwine void scsi_set_wesid(stwuct scsi_cmnd *cmd, unsigned int wesid)
{
	cmd->wesid_wen = wesid;
}

static inwine unsigned int scsi_get_wesid(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->wesid_wen;
}

#define scsi_fow_each_sg(cmd, sg, nseg, __i)			\
	fow_each_sg(scsi_sgwist(cmd), sg, nseg, __i)

static inwine int scsi_sg_copy_fwom_buffew(stwuct scsi_cmnd *cmd,
					   const void *buf, int bufwen)
{
	wetuwn sg_copy_fwom_buffew(scsi_sgwist(cmd), scsi_sg_count(cmd),
				   buf, bufwen);
}

static inwine int scsi_sg_copy_to_buffew(stwuct scsi_cmnd *cmd,
					 void *buf, int bufwen)
{
	wetuwn sg_copy_to_buffew(scsi_sgwist(cmd), scsi_sg_count(cmd),
				 buf, bufwen);
}

static inwine sectow_t scsi_get_sectow(stwuct scsi_cmnd *scmd)
{
	wetuwn bwk_wq_pos(scsi_cmd_to_wq(scmd));
}

static inwine sectow_t scsi_get_wba(stwuct scsi_cmnd *scmd)
{
	unsigned int shift = iwog2(scmd->device->sectow_size) - SECTOW_SHIFT;

	wetuwn bwk_wq_pos(scsi_cmd_to_wq(scmd)) >> shift;
}

static inwine unsigned int scsi_wogicaw_bwock_count(stwuct scsi_cmnd *scmd)
{
	unsigned int shift = iwog2(scmd->device->sectow_size) - SECTOW_SHIFT;

	wetuwn bwk_wq_bytes(scsi_cmd_to_wq(scmd)) >> shift;
}

/*
 * The opewations bewow awe hints that teww the contwowwew dwivew how
 * to handwe I/Os with DIF ow simiwaw types of pwotection infowmation.
 */
enum scsi_pwot_opewations {
	/* Nowmaw I/O */
	SCSI_PWOT_NOWMAW = 0,

	/* OS-HBA: Pwotected, HBA-Tawget: Unpwotected */
	SCSI_PWOT_WEAD_INSEWT,
	SCSI_PWOT_WWITE_STWIP,

	/* OS-HBA: Unpwotected, HBA-Tawget: Pwotected */
	SCSI_PWOT_WEAD_STWIP,
	SCSI_PWOT_WWITE_INSEWT,

	/* OS-HBA: Pwotected, HBA-Tawget: Pwotected */
	SCSI_PWOT_WEAD_PASS,
	SCSI_PWOT_WWITE_PASS,
};

static inwine void scsi_set_pwot_op(stwuct scsi_cmnd *scmd, unsigned chaw op)
{
	scmd->pwot_op = op;
}

static inwine unsigned chaw scsi_get_pwot_op(stwuct scsi_cmnd *scmd)
{
	wetuwn scmd->pwot_op;
}

enum scsi_pwot_fwags {
	SCSI_PWOT_TWANSFEW_PI		= 1 << 0,
	SCSI_PWOT_GUAWD_CHECK		= 1 << 1,
	SCSI_PWOT_WEF_CHECK		= 1 << 2,
	SCSI_PWOT_WEF_INCWEMENT		= 1 << 3,
	SCSI_PWOT_IP_CHECKSUM		= 1 << 4,
};

/*
 * The contwowwew usuawwy does not know anything about the tawget it
 * is communicating with.  Howevew, when DIX is enabwed the contwowwew
 * must be know tawget type so it can vewify the pwotection
 * infowmation passed awong with the I/O.
 */
enum scsi_pwot_tawget_type {
	SCSI_PWOT_DIF_TYPE0 = 0,
	SCSI_PWOT_DIF_TYPE1,
	SCSI_PWOT_DIF_TYPE2,
	SCSI_PWOT_DIF_TYPE3,
};

static inwine void scsi_set_pwot_type(stwuct scsi_cmnd *scmd, unsigned chaw type)
{
	scmd->pwot_type = type;
}

static inwine unsigned chaw scsi_get_pwot_type(stwuct scsi_cmnd *scmd)
{
	wetuwn scmd->pwot_type;
}

static inwine u32 scsi_pwot_wef_tag(stwuct scsi_cmnd *scmd)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(scmd);

	wetuwn t10_pi_wef_tag(wq);
}

static inwine unsigned int scsi_pwot_intewvaw(stwuct scsi_cmnd *scmd)
{
	wetuwn scmd->device->sectow_size;
}

static inwine unsigned scsi_pwot_sg_count(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->pwot_sdb ? cmd->pwot_sdb->tabwe.nents : 0;
}

static inwine stwuct scattewwist *scsi_pwot_sgwist(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->pwot_sdb ? cmd->pwot_sdb->tabwe.sgw : NUWW;
}

static inwine stwuct scsi_data_buffew *scsi_pwot(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->pwot_sdb;
}

#define scsi_fow_each_pwot_sg(cmd, sg, nseg, __i)		\
	fow_each_sg(scsi_pwot_sgwist(cmd), sg, nseg, __i)

static inwine void set_status_byte(stwuct scsi_cmnd *cmd, chaw status)
{
	cmd->wesuwt = (cmd->wesuwt & 0xffffff00) | status;
}

static inwine u8 get_status_byte(stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->wesuwt & 0xff;
}

static inwine void set_host_byte(stwuct scsi_cmnd *cmd, chaw status)
{
	cmd->wesuwt = (cmd->wesuwt & 0xff00ffff) | (status << 16);
}

static inwine u8 get_host_byte(stwuct scsi_cmnd *cmd)
{
	wetuwn (cmd->wesuwt >> 16) & 0xff;
}

/**
 * scsi_msg_to_host_byte() - twanswate message byte
 *
 * Twanswate the SCSI pawawwew message byte to a matching
 * host byte setting. A message of COMMAND_COMPWETE indicates
 * a successfuw command execution, any othew message indicate
 * an ewwow. As the messages themsewves onwy have a meaning
 * fow the SCSI pawawwew pwotocow this function twanswates
 * them into a matching host byte vawue fow SCSI EH.
 */
static inwine void scsi_msg_to_host_byte(stwuct scsi_cmnd *cmd, u8 msg)
{
	switch (msg) {
	case COMMAND_COMPWETE:
		bweak;
	case ABOWT_TASK_SET:
		set_host_byte(cmd, DID_ABOWT);
		bweak;
	case TAWGET_WESET:
		set_host_byte(cmd, DID_WESET);
		bweak;
	defauwt:
		set_host_byte(cmd, DID_EWWOW);
		bweak;
	}
}

static inwine unsigned scsi_twansfew_wength(stwuct scsi_cmnd *scmd)
{
	unsigned int xfew_wen = scmd->sdb.wength;
	unsigned int pwot_intewvaw = scsi_pwot_intewvaw(scmd);

	if (scmd->pwot_fwags & SCSI_PWOT_TWANSFEW_PI)
		xfew_wen += (xfew_wen >> iwog2(pwot_intewvaw)) * 8;

	wetuwn xfew_wen;
}

extewn void scsi_buiwd_sense(stwuct scsi_cmnd *scmd, int desc,
			     u8 key, u8 asc, u8 ascq);

stwuct wequest *scsi_awwoc_wequest(stwuct wequest_queue *q, bwk_opf_t opf,
				   bwk_mq_weq_fwags_t fwags);

#endif /* _SCSI_SCSI_CMND_H */
