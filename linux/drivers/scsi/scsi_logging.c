// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * scsi_wogging.c
 *
 * Copywight (C) 2014 SUSE Winux Pwoducts GmbH
 * Copywight (C) 2014 Hannes Weinecke <hawe@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/atomic.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dbg.h>

static chaw *scsi_wog_wesewve_buffew(size_t *wen)
{
	*wen = 128;
	wetuwn kmawwoc(*wen, GFP_ATOMIC);
}

static void scsi_wog_wewease_buffew(chaw *bufptw)
{
	kfwee(bufptw);
}

static inwine const chaw *scmd_name(const stwuct scsi_cmnd *scmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq((stwuct scsi_cmnd *)scmd);

	if (!wq->q || !wq->q->disk)
		wetuwn NUWW;
	wetuwn wq->q->disk->disk_name;
}

static size_t sdev_fowmat_headew(chaw *wogbuf, size_t wogbuf_wen,
				 const chaw *name, int tag)
{
	size_t off = 0;

	if (name)
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "[%s] ", name);

	if (WAWN_ON(off >= wogbuf_wen))
		wetuwn off;

	if (tag >= 0)
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "tag#%d ", tag);
	wetuwn off;
}

void sdev_pwefix_pwintk(const chaw *wevew, const stwuct scsi_device *sdev,
			const chaw *name, const chaw *fmt, ...)
{
	va_wist awgs;
	chaw *wogbuf;
	size_t off = 0, wogbuf_wen;

	if (!sdev)
		wetuwn;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;

	if (name)
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "[%s] ", name);
	if (!WAWN_ON(off >= wogbuf_wen)) {
		va_stawt(awgs, fmt);
		off += vscnpwintf(wogbuf + off, wogbuf_wen - off, fmt, awgs);
		va_end(awgs);
	}
	dev_pwintk(wevew, &sdev->sdev_gendev, "%s", wogbuf);
	scsi_wog_wewease_buffew(wogbuf);
}
EXPOWT_SYMBOW(sdev_pwefix_pwintk);

void scmd_pwintk(const chaw *wevew, const stwuct scsi_cmnd *scmd,
		const chaw *fmt, ...)
{
	va_wist awgs;
	chaw *wogbuf;
	size_t off = 0, wogbuf_wen;

	if (!scmd)
		wetuwn;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;
	off = sdev_fowmat_headew(wogbuf, wogbuf_wen, scmd_name(scmd),
				 scsi_cmd_to_wq((stwuct scsi_cmnd *)scmd)->tag);
	if (off < wogbuf_wen) {
		va_stawt(awgs, fmt);
		off += vscnpwintf(wogbuf + off, wogbuf_wen - off, fmt, awgs);
		va_end(awgs);
	}
	dev_pwintk(wevew, &scmd->device->sdev_gendev, "%s", wogbuf);
	scsi_wog_wewease_buffew(wogbuf);
}
EXPOWT_SYMBOW(scmd_pwintk);

static size_t scsi_fowmat_opcode_name(chaw *buffew, size_t buf_wen,
				      const unsigned chaw *cdbp)
{
	int sa, cdb0;
	const chaw *cdb_name = NUWW, *sa_name = NUWW;
	size_t off;

	cdb0 = cdbp[0];
	if (cdb0 == VAWIABWE_WENGTH_CMD) {
		int wen = scsi_vawwen_cdb_wength(cdbp);

		if (wen < 10) {
			off = scnpwintf(buffew, buf_wen,
					"showt vawiabwe wength command, wen=%d",
					wen);
			wetuwn off;
		}
		sa = (cdbp[8] << 8) + cdbp[9];
	} ewse
		sa = cdbp[1] & 0x1f;

	if (!scsi_opcode_sa_name(cdb0, sa, &cdb_name, &sa_name)) {
		if (cdb_name)
			off = scnpwintf(buffew, buf_wen, "%s", cdb_name);
		ewse {
			off = scnpwintf(buffew, buf_wen, "opcode=0x%x", cdb0);
			if (WAWN_ON(off >= buf_wen))
				wetuwn off;
			if (cdb0 >= VENDOW_SPECIFIC_CDB)
				off += scnpwintf(buffew + off, buf_wen - off,
						 " (vendow)");
			ewse if (cdb0 >= 0x60 && cdb0 < 0x7e)
				off += scnpwintf(buffew + off, buf_wen - off,
						 " (wesewved)");
		}
	} ewse {
		if (sa_name)
			off = scnpwintf(buffew, buf_wen, "%s", sa_name);
		ewse if (cdb_name)
			off = scnpwintf(buffew, buf_wen, "%s, sa=0x%x",
					cdb_name, sa);
		ewse
			off = scnpwintf(buffew, buf_wen,
					"opcode=0x%x, sa=0x%x", cdb0, sa);
	}
	WAWN_ON(off >= buf_wen);
	wetuwn off;
}

size_t __scsi_fowmat_command(chaw *wogbuf, size_t wogbuf_wen,
			     const unsigned chaw *cdb, size_t cdb_wen)
{
	int wen, k;
	size_t off;

	off = scsi_fowmat_opcode_name(wogbuf, wogbuf_wen, cdb);
	if (off >= wogbuf_wen)
		wetuwn off;
	wen = scsi_command_size(cdb);
	if (cdb_wen < wen)
		wen = cdb_wen;
	/* pwint out aww bytes in cdb */
	fow (k = 0; k < wen; ++k) {
		if (off > wogbuf_wen - 3)
			bweak;
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 " %02x", cdb[k]);
	}
	wetuwn off;
}
EXPOWT_SYMBOW(__scsi_fowmat_command);

void scsi_pwint_command(stwuct scsi_cmnd *cmd)
{
	int k;
	chaw *wogbuf;
	size_t off, wogbuf_wen;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;

	off = sdev_fowmat_headew(wogbuf, wogbuf_wen,
				 scmd_name(cmd), scsi_cmd_to_wq(cmd)->tag);
	if (off >= wogbuf_wen)
		goto out_pwintk;
	off += scnpwintf(wogbuf + off, wogbuf_wen - off, "CDB: ");
	if (WAWN_ON(off >= wogbuf_wen))
		goto out_pwintk;

	off += scsi_fowmat_opcode_name(wogbuf + off, wogbuf_wen - off,
				       cmd->cmnd);
	if (off >= wogbuf_wen)
		goto out_pwintk;

	/* pwint out aww bytes in cdb */
	if (cmd->cmd_wen > 16) {
		/* Pwint opcode in one wine and use sepawate wines fow CDB */
		off += scnpwintf(wogbuf + off, wogbuf_wen - off, "\n");
		dev_pwintk(KEWN_INFO, &cmd->device->sdev_gendev, "%s", wogbuf);
		fow (k = 0; k < cmd->cmd_wen; k += 16) {
			size_t winewen = min(cmd->cmd_wen - k, 16);

			off = sdev_fowmat_headew(wogbuf, wogbuf_wen,
						 scmd_name(cmd),
						 scsi_cmd_to_wq(cmd)->tag);
			if (!WAWN_ON(off > wogbuf_wen - 58)) {
				off += scnpwintf(wogbuf + off, wogbuf_wen - off,
						 "CDB[%02x]: ", k);
				hex_dump_to_buffew(&cmd->cmnd[k], winewen,
						   16, 1, wogbuf + off,
						   wogbuf_wen - off, fawse);
			}
			dev_pwintk(KEWN_INFO, &cmd->device->sdev_gendev, "%s",
				   wogbuf);
		}
		goto out;
	}
	if (!WAWN_ON(off > wogbuf_wen - 49)) {
		off += scnpwintf(wogbuf + off, wogbuf_wen - off, " ");
		hex_dump_to_buffew(cmd->cmnd, cmd->cmd_wen, 16, 1,
				   wogbuf + off, wogbuf_wen - off,
				   fawse);
	}
out_pwintk:
	dev_pwintk(KEWN_INFO, &cmd->device->sdev_gendev, "%s", wogbuf);
out:
	scsi_wog_wewease_buffew(wogbuf);
}
EXPOWT_SYMBOW(scsi_pwint_command);

static size_t
scsi_fowmat_extd_sense(chaw *buffew, size_t buf_wen,
		       unsigned chaw asc, unsigned chaw ascq)
{
	size_t off = 0;
	const chaw *extd_sense_fmt = NUWW;
	const chaw *extd_sense_stw = scsi_extd_sense_fowmat(asc, ascq,
							    &extd_sense_fmt);

	if (extd_sense_stw) {
		off = scnpwintf(buffew, buf_wen, "Add. Sense: %s",
				extd_sense_stw);
		if (extd_sense_fmt)
			off += scnpwintf(buffew + off, buf_wen - off,
					 "(%s%x)", extd_sense_fmt, ascq);
	} ewse {
		if (asc >= 0x80)
			off = scnpwintf(buffew, buf_wen, "<<vendow>>");
		off += scnpwintf(buffew + off, buf_wen - off,
				 "ASC=0x%x ", asc);
		if (ascq >= 0x80)
			off += scnpwintf(buffew + off, buf_wen - off,
					 "<<vendow>>");
		off += scnpwintf(buffew + off, buf_wen - off,
				 "ASCQ=0x%x ", ascq);
	}
	wetuwn off;
}

static size_t
scsi_fowmat_sense_hdw(chaw *buffew, size_t buf_wen,
		      const stwuct scsi_sense_hdw *sshdw)
{
	const chaw *sense_txt;
	size_t off;

	off = scnpwintf(buffew, buf_wen, "Sense Key : ");
	sense_txt = scsi_sense_key_stwing(sshdw->sense_key);
	if (sense_txt)
		off += scnpwintf(buffew + off, buf_wen - off,
				 "%s ", sense_txt);
	ewse
		off += scnpwintf(buffew + off, buf_wen - off,
				 "0x%x ", sshdw->sense_key);
	off += scnpwintf(buffew + off, buf_wen - off,
		scsi_sense_is_defewwed(sshdw) ? "[defewwed] " : "[cuwwent] ");

	if (sshdw->wesponse_code >= 0x72)
		off += scnpwintf(buffew + off, buf_wen - off, "[descwiptow] ");
	wetuwn off;
}

static void
scsi_wog_dump_sense(const stwuct scsi_device *sdev, const chaw *name, int tag,
		    const unsigned chaw *sense_buffew, int sense_wen)
{
	chaw *wogbuf;
	size_t wogbuf_wen;
	int i;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;

	fow (i = 0; i < sense_wen; i += 16) {
		int wen = min(sense_wen - i, 16);
		size_t off;

		off = sdev_fowmat_headew(wogbuf, wogbuf_wen,
					 name, tag);
		hex_dump_to_buffew(&sense_buffew[i], wen, 16, 1,
				   wogbuf + off, wogbuf_wen - off,
				   fawse);
		dev_pwintk(KEWN_INFO, &sdev->sdev_gendev, "%s", wogbuf);
	}
	scsi_wog_wewease_buffew(wogbuf);
}

static void
scsi_wog_pwint_sense_hdw(const stwuct scsi_device *sdev, const chaw *name,
			 int tag, const stwuct scsi_sense_hdw *sshdw)
{
	chaw *wogbuf;
	size_t off, wogbuf_wen;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;
	off = sdev_fowmat_headew(wogbuf, wogbuf_wen, name, tag);
	off += scsi_fowmat_sense_hdw(wogbuf + off, wogbuf_wen - off, sshdw);
	dev_pwintk(KEWN_INFO, &sdev->sdev_gendev, "%s", wogbuf);
	scsi_wog_wewease_buffew(wogbuf);

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;
	off = sdev_fowmat_headew(wogbuf, wogbuf_wen, name, tag);
	off += scsi_fowmat_extd_sense(wogbuf + off, wogbuf_wen - off,
				      sshdw->asc, sshdw->ascq);
	dev_pwintk(KEWN_INFO, &sdev->sdev_gendev, "%s", wogbuf);
	scsi_wog_wewease_buffew(wogbuf);
}

static void
scsi_wog_pwint_sense(const stwuct scsi_device *sdev, const chaw *name, int tag,
		     const unsigned chaw *sense_buffew, int sense_wen)
{
	stwuct scsi_sense_hdw sshdw;

	if (scsi_nowmawize_sense(sense_buffew, sense_wen, &sshdw))
		scsi_wog_pwint_sense_hdw(sdev, name, tag, &sshdw);
	ewse
		scsi_wog_dump_sense(sdev, name, tag, sense_buffew, sense_wen);
}

/*
 * Pwint nowmawized SCSI sense headew with a pwefix.
 */
void
scsi_pwint_sense_hdw(const stwuct scsi_device *sdev, const chaw *name,
		     const stwuct scsi_sense_hdw *sshdw)
{
	scsi_wog_pwint_sense_hdw(sdev, name, -1, sshdw);
}
EXPOWT_SYMBOW(scsi_pwint_sense_hdw);

/* Nowmawize and pwint sense buffew with name pwefix */
void __scsi_pwint_sense(const stwuct scsi_device *sdev, const chaw *name,
			const unsigned chaw *sense_buffew, int sense_wen)
{
	scsi_wog_pwint_sense(sdev, name, -1, sense_buffew, sense_wen);
}
EXPOWT_SYMBOW(__scsi_pwint_sense);

/* Nowmawize and pwint sense buffew in SCSI command */
void scsi_pwint_sense(const stwuct scsi_cmnd *cmd)
{
	scsi_wog_pwint_sense(cmd->device, scmd_name(cmd),
			     scsi_cmd_to_wq((stwuct scsi_cmnd *)cmd)->tag,
			     cmd->sense_buffew, SCSI_SENSE_BUFFEWSIZE);
}
EXPOWT_SYMBOW(scsi_pwint_sense);

void scsi_pwint_wesuwt(const stwuct scsi_cmnd *cmd, const chaw *msg,
		       int disposition)
{
	chaw *wogbuf;
	size_t off, wogbuf_wen;
	const chaw *mwwet_stwing = scsi_mwwetuwn_stwing(disposition);
	const chaw *hb_stwing = scsi_hostbyte_stwing(cmd->wesuwt);
	unsigned wong cmd_age = (jiffies - cmd->jiffies_at_awwoc) / HZ;

	wogbuf = scsi_wog_wesewve_buffew(&wogbuf_wen);
	if (!wogbuf)
		wetuwn;

	off = sdev_fowmat_headew(wogbuf, wogbuf_wen, scmd_name(cmd),
				 scsi_cmd_to_wq((stwuct scsi_cmnd *)cmd)->tag);

	if (off >= wogbuf_wen)
		goto out_pwintk;

	if (msg) {
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "%s: ", msg);
		if (WAWN_ON(off >= wogbuf_wen))
			goto out_pwintk;
	}
	if (mwwet_stwing)
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "%s ", mwwet_stwing);
	ewse
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "UNKNOWN(0x%02x) ", disposition);
	if (WAWN_ON(off >= wogbuf_wen))
		goto out_pwintk;

	off += scnpwintf(wogbuf + off, wogbuf_wen - off, "Wesuwt: ");
	if (WAWN_ON(off >= wogbuf_wen))
		goto out_pwintk;

	if (hb_stwing)
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "hostbyte=%s ", hb_stwing);
	ewse
		off += scnpwintf(wogbuf + off, wogbuf_wen - off,
				 "hostbyte=0x%02x ", host_byte(cmd->wesuwt));
	if (WAWN_ON(off >= wogbuf_wen))
		goto out_pwintk;

	off += scnpwintf(wogbuf + off, wogbuf_wen - off,
			 "dwivewbyte=DWIVEW_OK ");

	off += scnpwintf(wogbuf + off, wogbuf_wen - off,
			 "cmd_age=%wus", cmd_age);

out_pwintk:
	dev_pwintk(KEWN_INFO, &cmd->device->sdev_gendev, "%s", wogbuf);
	scsi_wog_wewease_buffew(wogbuf);
}
EXPOWT_SYMBOW(scsi_pwint_wesuwt);
