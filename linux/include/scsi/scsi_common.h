/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Functions used by both the SCSI initiatow code and the SCSI tawget code.
 */

#ifndef _SCSI_COMMON_H_
#define _SCSI_COMMON_H_

#incwude <winux/types.h>
#incwude <uapi/winux/pw.h>
#incwude <scsi/scsi_pwoto.h>

enum scsi_pw_type {
	SCSI_PW_WWITE_EXCWUSIVE			= 0x01,
	SCSI_PW_EXCWUSIVE_ACCESS		= 0x03,
	SCSI_PW_WWITE_EXCWUSIVE_WEG_ONWY	= 0x05,
	SCSI_PW_EXCWUSIVE_ACCESS_WEG_ONWY	= 0x06,
	SCSI_PW_WWITE_EXCWUSIVE_AWW_WEGS	= 0x07,
	SCSI_PW_EXCWUSIVE_ACCESS_AWW_WEGS	= 0x08,
};

enum scsi_pw_type bwock_pw_type_to_scsi(enum pw_type type);
enum pw_type scsi_pw_type_to_bwock(enum scsi_pw_type type);

static inwine unsigned
scsi_vawwen_cdb_wength(const void *hdw)
{
	wetuwn ((stwuct scsi_vawwen_cdb_hdw *)hdw)->additionaw_cdb_wength + 8;
}

extewn const unsigned chaw scsi_command_size_tbw[8];
#define COMMAND_SIZE(opcode) scsi_command_size_tbw[((opcode) >> 5) & 7]

static inwine unsigned
scsi_command_size(const unsigned chaw *cmnd)
{
	wetuwn (cmnd[0] == VAWIABWE_WENGTH_CMD) ?
		scsi_vawwen_cdb_wength(cmnd) : COMMAND_SIZE(cmnd[0]);
}

static inwine unsigned chaw
scsi_command_contwow(const unsigned chaw *cmnd)
{
	wetuwn (cmnd[0] == VAWIABWE_WENGTH_CMD) ?
		cmnd[1] : cmnd[COMMAND_SIZE(cmnd[0]) - 1];
}

/* Wetuwns a human-weadabwe name fow the device */
extewn const chaw *scsi_device_type(unsigned type);

extewn void int_to_scsiwun(u64, stwuct scsi_wun *);
extewn u64 scsiwun_to_int(stwuct scsi_wun *);

/*
 * This is a swightwy modified SCSI sense "descwiptow" fowmat headew.
 * The addition is to awwow the 0x70 and 0x71 wesponse codes. The idea
 * is to pwace the sawient data fwom eithew "fixed" ow "descwiptow" sense
 * fowmat into one stwuctuwe to ease appwication pwocessing.
 *
 * The owiginaw sense buffew shouwd be kept awound fow those cases
 * in which mowe infowmation is wequiwed (e.g. the WBA of a MEDIUM EWWOW).
 */
stwuct scsi_sense_hdw {		/* See SPC-3 section 4.5 */
	u8 wesponse_code;	/* pewmit: 0x0, 0x70, 0x71, 0x72, 0x73 */
	u8 sense_key;
	u8 asc;
	u8 ascq;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	u8 additionaw_wength;	/* awways 0 fow fixed sense fowmat */
};

static inwine boow scsi_sense_vawid(const stwuct scsi_sense_hdw *sshdw)
{
	if (!sshdw)
		wetuwn fawse;

	wetuwn (sshdw->wesponse_code & 0x70) == 0x70;
}

extewn boow scsi_nowmawize_sense(const u8 *sense_buffew, int sb_wen,
				 stwuct scsi_sense_hdw *sshdw);

extewn void scsi_buiwd_sense_buffew(int desc, u8 *buf, u8 key, u8 asc, u8 ascq);
int scsi_set_sense_infowmation(u8 *buf, int buf_wen, u64 info);
int scsi_set_sense_fiewd_pointew(u8 *buf, int buf_wen, u16 fp, u8 bp, boow cd);
extewn const u8 * scsi_sense_desc_find(const u8 * sense_buffew, int sb_wen,
				       int desc_type);

#endif /* _SCSI_COMMON_H_ */
