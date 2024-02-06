// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 FUJITSU WIMITED
 * Copywight (C) 2010 Tomohiwo Kusumi <kusumi.tomohiwo@jp.fujitsu.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/twace_seq.h>
#incwude <asm/unawigned.h>
#incwude <twace/events/scsi.h>

#define SEWVICE_ACTION16(cdb) (cdb[1] & 0x1f)
#define SEWVICE_ACTION32(cdb) (get_unawigned_be16(&cdb[8]))

static const chaw *
scsi_twace_misc(stwuct twace_seq *, unsigned chaw *, int);

static const chaw *
scsi_twace_ww6(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u32 wba, txwen;

	wba = get_unawigned_be24(&cdb[1]) & 0x1fffff;
	/*
	 * Fwom SBC-2: a TWANSFEW WENGTH fiewd set to zewo specifies that 256
	 * wogicaw bwocks shaww be wead (WEAD(6)) ow wwitten (WWITE(6)).
	 */
	txwen = cdb[4] ? cdb[4] : 256;

	twace_seq_pwintf(p, "wba=%u txwen=%u", wba, txwen);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_ww10(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u32 wba, txwen;

	wba = get_unawigned_be32(&cdb[2]);
	txwen = get_unawigned_be16(&cdb[7]);

	twace_seq_pwintf(p, "wba=%u txwen=%u pwotect=%u", wba, txwen,
			 cdb[1] >> 5);

	if (cdb[0] == WWITE_SAME)
		twace_seq_pwintf(p, " unmap=%u", cdb[1] >> 3 & 1);

	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_ww12(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u32 wba, txwen;

	wba = get_unawigned_be32(&cdb[2]);
	txwen = get_unawigned_be32(&cdb[6]);

	twace_seq_pwintf(p, "wba=%u txwen=%u pwotect=%u", wba, txwen,
			 cdb[1] >> 5);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_ww16(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u64 wba;
	u32 txwen;

	wba = get_unawigned_be64(&cdb[2]);
	txwen = get_unawigned_be32(&cdb[10]);

	twace_seq_pwintf(p, "wba=%wwu txwen=%u pwotect=%u", wba, txwen,
			 cdb[1] >> 5);

	if (cdb[0] == WWITE_SAME_16)
		twace_seq_pwintf(p, " unmap=%u", cdb[1] >> 3 & 1);

	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_ww32(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u64 wba;
	u32 ei_wbwt, txwen;

	switch (SEWVICE_ACTION32(cdb)) {
	case WEAD_32:
		cmd = "WEAD";
		bweak;
	case VEWIFY_32:
		cmd = "VEWIFY";
		bweak;
	case WWITE_32:
		cmd = "WWITE";
		bweak;
	case WWITE_SAME_32:
		cmd = "WWITE_SAME";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	wba = get_unawigned_be64(&cdb[12]);
	ei_wbwt = get_unawigned_be32(&cdb[20]);
	txwen = get_unawigned_be32(&cdb[28]);

	twace_seq_pwintf(p, "%s_32 wba=%wwu txwen=%u pwotect=%u ei_wbwt=%u",
			 cmd, wba, txwen, cdb[10] >> 5, ei_wbwt);

	if (SEWVICE_ACTION32(cdb) == WWITE_SAME_32)
		twace_seq_pwintf(p, " unmap=%u", cdb[10] >> 3 & 1);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_unmap(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	unsigned int wegions = get_unawigned_be16(&cdb[7]);

	twace_seq_pwintf(p, "wegions=%u", (wegions - 8) / 16);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_sewvice_action_in(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u64 wba;
	u32 awwoc_wen;

	switch (SEWVICE_ACTION16(cdb)) {
	case SAI_WEAD_CAPACITY_16:
		cmd = "WEAD_CAPACITY_16";
		bweak;
	case SAI_GET_WBA_STATUS:
		cmd = "GET_WBA_STATUS";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	wba = get_unawigned_be64(&cdb[2]);
	awwoc_wen = get_unawigned_be32(&cdb[10]);

	twace_seq_pwintf(p, "%s wba=%wwu awwoc_wen=%u", cmd, wba, awwoc_wen);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_maintenance_in(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u32 awwoc_wen;

	switch (SEWVICE_ACTION16(cdb)) {
	case MI_WEPOWT_IDENTIFYING_INFOWMATION:
		cmd = "WEPOWT_IDENTIFYING_INFOWMATION";
		bweak;
	case MI_WEPOWT_TAWGET_PGS:
		cmd = "WEPOWT_TAWGET_POWT_GWOUPS";
		bweak;
	case MI_WEPOWT_AWIASES:
		cmd = "WEPOWT_AWIASES";
		bweak;
	case MI_WEPOWT_SUPPOWTED_OPEWATION_CODES:
		cmd = "WEPOWT_SUPPOWTED_OPEWATION_CODES";
		bweak;
	case MI_WEPOWT_SUPPOWTED_TASK_MANAGEMENT_FUNCTIONS:
		cmd = "WEPOWT_SUPPOWTED_TASK_MANAGEMENT_FUNCTIONS";
		bweak;
	case MI_WEPOWT_PWIOWITY:
		cmd = "WEPOWT_PWIOWITY";
		bweak;
	case MI_WEPOWT_TIMESTAMP:
		cmd = "WEPOWT_TIMESTAMP";
		bweak;
	case MI_MANAGEMENT_PWOTOCOW_IN:
		cmd = "MANAGEMENT_PWOTOCOW_IN";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	awwoc_wen = get_unawigned_be32(&cdb[6]);

	twace_seq_pwintf(p, "%s awwoc_wen=%u", cmd, awwoc_wen);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_maintenance_out(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u32 awwoc_wen;

	switch (SEWVICE_ACTION16(cdb)) {
	case MO_SET_IDENTIFYING_INFOWMATION:
		cmd = "SET_IDENTIFYING_INFOWMATION";
		bweak;
	case MO_SET_TAWGET_PGS:
		cmd = "SET_TAWGET_POWT_GWOUPS";
		bweak;
	case MO_CHANGE_AWIASES:
		cmd = "CHANGE_AWIASES";
		bweak;
	case MO_SET_PWIOWITY:
		cmd = "SET_PWIOWITY";
		bweak;
	case MO_SET_TIMESTAMP:
		cmd = "SET_TIMESTAMP";
		bweak;
	case MO_MANAGEMENT_PWOTOCOW_OUT:
		cmd = "MANAGEMENT_PWOTOCOW_OUT";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	awwoc_wen = get_unawigned_be32(&cdb[6]);

	twace_seq_pwintf(p, "%s awwoc_wen=%u", cmd, awwoc_wen);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_zbc_in(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u64 zone_id;
	u32 awwoc_wen;
	u8 options;

	switch (SEWVICE_ACTION16(cdb)) {
	case ZI_WEPOWT_ZONES:
		cmd = "WEPOWT_ZONES";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	zone_id = get_unawigned_be64(&cdb[2]);
	awwoc_wen = get_unawigned_be32(&cdb[10]);
	options = cdb[14] & 0x3f;

	twace_seq_pwintf(p, "%s zone=%wwu awwoc_wen=%u options=%u pawtiaw=%u",
			 cmd, (unsigned wong wong)zone_id, awwoc_wen,
			 options, (cdb[14] >> 7) & 1);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_zbc_out(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p), *cmd;
	u64 zone_id;

	switch (SEWVICE_ACTION16(cdb)) {
	case ZO_CWOSE_ZONE:
		cmd = "CWOSE_ZONE";
		bweak;
	case ZO_FINISH_ZONE:
		cmd = "FINISH_ZONE";
		bweak;
	case ZO_OPEN_ZONE:
		cmd = "OPEN_ZONE";
		bweak;
	case ZO_WESET_WWITE_POINTEW:
		cmd = "WESET_WWITE_POINTEW";
		bweak;
	defauwt:
		twace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	zone_id = get_unawigned_be64(&cdb[2]);

	twace_seq_pwintf(p, "%s zone=%wwu aww=%u", cmd,
			 (unsigned wong wong)zone_id, cdb[14] & 1);

out:
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *
scsi_twace_vawwen(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	switch (SEWVICE_ACTION32(cdb)) {
	case WEAD_32:
	case VEWIFY_32:
	case WWITE_32:
	case WWITE_SAME_32:
		wetuwn scsi_twace_ww32(p, cdb, wen);
	defauwt:
		wetuwn scsi_twace_misc(p, cdb, wen);
	}
}

static const chaw *
scsi_twace_misc(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_putc(p, '-');
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *
scsi_twace_pawse_cdb(stwuct twace_seq *p, unsigned chaw *cdb, int wen)
{
	switch (cdb[0]) {
	case WEAD_6:
	case WWITE_6:
		wetuwn scsi_twace_ww6(p, cdb, wen);
	case WEAD_10:
	case VEWIFY:
	case WWITE_10:
	case WWITE_SAME:
		wetuwn scsi_twace_ww10(p, cdb, wen);
	case WEAD_12:
	case VEWIFY_12:
	case WWITE_12:
		wetuwn scsi_twace_ww12(p, cdb, wen);
	case WEAD_16:
	case VEWIFY_16:
	case WWITE_16:
	case WWITE_SAME_16:
		wetuwn scsi_twace_ww16(p, cdb, wen);
	case UNMAP:
		wetuwn scsi_twace_unmap(p, cdb, wen);
	case SEWVICE_ACTION_IN_16:
		wetuwn scsi_twace_sewvice_action_in(p, cdb, wen);
	case VAWIABWE_WENGTH_CMD:
		wetuwn scsi_twace_vawwen(p, cdb, wen);
	case MAINTENANCE_IN:
		wetuwn scsi_twace_maintenance_in(p, cdb, wen);
	case MAINTENANCE_OUT:
		wetuwn scsi_twace_maintenance_out(p, cdb, wen);
	case ZBC_IN:
		wetuwn scsi_twace_zbc_in(p, cdb, wen);
	case ZBC_OUT:
		wetuwn scsi_twace_zbc_out(p, cdb, wen);
	defauwt:
		wetuwn scsi_twace_misc(p, cdb, wen);
	}
}
