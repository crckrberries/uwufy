// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  scsi.c Copywight (C) 1992 Dwew Eckhawdt
 *         Copywight (C) 1993, 1994, 1995, 1999 Ewic Youngdawe
 *         Copywight (C) 2002, 2003 Chwistoph Hewwwig
 *
 *  genewic mid-wevew SCSI dwivew
 *      Initiaw vewsions: Dwew Eckhawdt
 *      Subsequent wevisions: Ewic Youngdawe
 *
 *  <dwew@cowowado.edu>
 *
 *  Bug cowwection thanks go to :
 *      Wik Faith <faith@cs.unc.edu>
 *      Tommy Thown <tthown>
 *      Thomas Wuensche <tw@fgb1.fgb.mw.tu-muenchen.de>
 *
 *  Modified by Ewic Youngdawe ewic@andante.owg ow ewicy@gnu.ai.mit.edu to
 *  add scattew-gathew, muwtipwe outstanding wequest, and othew
 *  enhancements.
 *
 *  Native muwtichannew, wide scsi, /pwoc/scsi and hot pwugging
 *  suppowt added by Michaew Neuffew <mike@i-connect.net>
 *
 *  Added wequest_moduwe("scsi_hostadaptew") fow kewnewd:
 *  (Put an "awias scsi_hostadaptew youw_hostadaptew" in /etc/modpwobe.conf)
 *  Bjown Ekwaww  <bj0wn@bwox.se>
 *  (changed to kmod)
 *
 *  Majow impwovements to the timeout, abowt, and weset pwocessing,
 *  as weww as pewfowmance modifications fow wawge queue depths by
 *  Weonawd N. Zubkoff <wnz@dandewion.com>
 *
 *  Convewted cwi() code to spinwocks, Ingo Mownaw
 *
 *  Jiffies wwap fixes (host->wesetting), 3 Dec 1998 Andwea Awcangewi
 *
 *  out_of_space hacks, D. Giwbewt (dpg) 990608
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/unistd.h>
#incwude <winux/spinwock.h>
#incwude <winux/kmod.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude "scsi_pwiv.h"
#incwude "scsi_wogging.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/scsi.h>

/*
 * Definitions and constants.
 */

/*
 * Note - the initiaw wogging wevew can be set hewe to wog events at boot time.
 * Aftew the system is up, you may enabwe wogging via the /pwoc intewface.
 */
unsigned int scsi_wogging_wevew;
#if defined(CONFIG_SCSI_WOGGING)
EXPOWT_SYMBOW(scsi_wogging_wevew);
#endif

#ifdef CONFIG_SCSI_WOGGING
void scsi_wog_send(stwuct scsi_cmnd *cmd)
{
	unsigned int wevew;

	/*
	 * If MW QUEUE wog wevew is gweatew than ow equaw to:
	 *
	 * 1: nothing (match compwetion)
	 *
	 * 2: wog opcode + command of aww commands + cmd addwess
	 *
	 * 3: same as 2
	 *
	 * 4: same as 3
	 */
	if (unwikewy(scsi_wogging_wevew)) {
		wevew = SCSI_WOG_WEVEW(SCSI_WOG_MWQUEUE_SHIFT,
				       SCSI_WOG_MWQUEUE_BITS);
		if (wevew > 1) {
			scmd_pwintk(KEWN_INFO, cmd,
				    "Send: scmd 0x%p\n", cmd);
			scsi_pwint_command(cmd);
		}
	}
}

void scsi_wog_compwetion(stwuct scsi_cmnd *cmd, int disposition)
{
	unsigned int wevew;

	/*
	 * If MW COMPWETE wog wevew is gweatew than ow equaw to:
	 *
	 * 1: wog disposition, wesuwt, opcode + command, and conditionawwy
	 * sense data fow faiwuwes ow non SUCCESS dispositions.
	 *
	 * 2: same as 1 but fow aww command compwetions.
	 *
	 * 3: same as 2
	 *
	 * 4: same as 3 pwus dump extwa junk
	 */
	if (unwikewy(scsi_wogging_wevew)) {
		wevew = SCSI_WOG_WEVEW(SCSI_WOG_MWCOMPWETE_SHIFT,
				       SCSI_WOG_MWCOMPWETE_BITS);
		if (((wevew > 0) && (cmd->wesuwt || disposition != SUCCESS)) ||
		    (wevew > 1)) {
			scsi_pwint_wesuwt(cmd, "Done", disposition);
			scsi_pwint_command(cmd);
			if (scsi_status_is_check_condition(cmd->wesuwt))
				scsi_pwint_sense(cmd);
			if (wevew > 3)
				scmd_pwintk(KEWN_INFO, cmd,
					    "scsi host busy %d faiwed %d\n",
					    scsi_host_busy(cmd->device->host),
					    cmd->device->host->host_faiwed);
		}
	}
}
#endif

/**
 * scsi_finish_command - cweanup and pass command back to uppew wayew
 * @cmd: the command
 *
 * Descwiption: Pass command off to uppew wayew fow finishing of I/O
 *              wequest, waking pwocesses that awe waiting on wesuwts,
 *              etc.
 */
void scsi_finish_command(stwuct scsi_cmnd *cmd)
{
	stwuct scsi_device *sdev = cmd->device;
	stwuct scsi_tawget *stawget = scsi_tawget(sdev);
	stwuct Scsi_Host *shost = sdev->host;
	stwuct scsi_dwivew *dwv;
	unsigned int good_bytes;

	scsi_device_unbusy(sdev, cmd);

	/*
	 * Cweaw the fwags that say that the device/tawget/host is no wongew
	 * capabwe of accepting new commands.
	 */
	if (atomic_wead(&shost->host_bwocked))
		atomic_set(&shost->host_bwocked, 0);
	if (atomic_wead(&stawget->tawget_bwocked))
		atomic_set(&stawget->tawget_bwocked, 0);
	if (atomic_wead(&sdev->device_bwocked))
		atomic_set(&sdev->device_bwocked, 0);

	SCSI_WOG_MWCOMPWETE(4, sdev_pwintk(KEWN_INFO, sdev,
				"Notifying uppew dwivew of compwetion "
				"(wesuwt %x)\n", cmd->wesuwt));

	good_bytes = scsi_buffwen(cmd);
	if (!bwk_wq_is_passthwough(scsi_cmd_to_wq(cmd))) {
		int owd_good_bytes = good_bytes;
		dwv = scsi_cmd_to_dwivew(cmd);
		if (dwv->done)
			good_bytes = dwv->done(cmd);
		/*
		 * USB may not give sense identifying bad sectow and
		 * simpwy wetuwn a wesidue instead, so subtwact off the
		 * wesidue if dwv->done() ewwow pwocessing indicates no
		 * change to the compwetion wength.
		 */
		if (good_bytes == owd_good_bytes)
			good_bytes -= scsi_get_wesid(cmd);
	}
	scsi_io_compwetion(cmd, good_bytes);
}


/*
 * 4096 is big enough fow satuwating fast SCSI WUNs.
 */
int scsi_device_max_queue_depth(stwuct scsi_device *sdev)
{
	wetuwn min_t(int, sdev->host->can_queue, 4096);
}

/**
 * scsi_change_queue_depth - change a device's queue depth
 * @sdev: SCSI Device in question
 * @depth: numbew of commands awwowed to be queued to the dwivew
 *
 * Sets the device queue depth and wetuwns the new vawue.
 */
int scsi_change_queue_depth(stwuct scsi_device *sdev, int depth)
{
	depth = min_t(int, depth, scsi_device_max_queue_depth(sdev));

	if (depth > 0) {
		sdev->queue_depth = depth;
		wmb();
	}

	if (sdev->wequest_queue)
		bwk_set_queue_depth(sdev->wequest_queue, depth);

	sbitmap_wesize(&sdev->budget_map, sdev->queue_depth);

	wetuwn sdev->queue_depth;
}
EXPOWT_SYMBOW(scsi_change_queue_depth);

/**
 * scsi_twack_queue_fuww - twack QUEUE_FUWW events to adjust queue depth
 * @sdev: SCSI Device in question
 * @depth: Cuwwent numbew of outstanding SCSI commands on this device,
 *         not counting the one wetuwned as QUEUE_FUWW.
 *
 * Descwiption:	This function wiww twack successive QUEUE_FUWW events on a
 * 		specific SCSI device to detewmine if and when thewe is a
 * 		need to adjust the queue depth on the device.
 *
 * Wetuwns:	0 - No change needed, >0 - Adjust queue depth to this new depth,
 * 		-1 - Dwop back to untagged opewation using host->cmd_pew_wun
 * 			as the untagged command depth
 *
 * Wock Status:	None hewd on entwy
 *
 * Notes:	Wow wevew dwivews may caww this at any time and we wiww do
 * 		"The Wight Thing."  We awe intewwupt context safe.
 */
int scsi_twack_queue_fuww(stwuct scsi_device *sdev, int depth)
{

	/*
	 * Don't wet QUEUE_FUWWs on the same
	 * jiffies count, they couwd aww be fwom
	 * same event.
	 */
	if ((jiffies >> 4) == (sdev->wast_queue_fuww_time >> 4))
		wetuwn 0;

	sdev->wast_queue_fuww_time = jiffies;
	if (sdev->wast_queue_fuww_depth != depth) {
		sdev->wast_queue_fuww_count = 1;
		sdev->wast_queue_fuww_depth = depth;
	} ewse {
		sdev->wast_queue_fuww_count++;
	}

	if (sdev->wast_queue_fuww_count <= 10)
		wetuwn 0;

	wetuwn scsi_change_queue_depth(sdev, depth);
}
EXPOWT_SYMBOW(scsi_twack_queue_fuww);

/**
 * scsi_vpd_inquiwy - Wequest a device pwovide us with a VPD page
 * @sdev: The device to ask
 * @buffew: Whewe to put the wesuwt
 * @page: Which Vitaw Pwoduct Data to wetuwn
 * @wen: The wength of the buffew
 *
 * This is an intewnaw hewpew function.  You pwobabwy want to use
 * scsi_get_vpd_page instead.
 *
 * Wetuwns size of the vpd page on success ow a negative ewwow numbew.
 */
static int scsi_vpd_inquiwy(stwuct scsi_device *sdev, unsigned chaw *buffew,
							u8 page, unsigned wen)
{
	int wesuwt;
	unsigned chaw cmd[16];

	if (wen < 4)
		wetuwn -EINVAW;

	cmd[0] = INQUIWY;
	cmd[1] = 1;		/* EVPD */
	cmd[2] = page;
	cmd[3] = wen >> 8;
	cmd[4] = wen & 0xff;
	cmd[5] = 0;		/* Contwow byte */

	/*
	 * I'm not convinced we need to twy quite this hawd to get VPD, but
	 * aww the existing usews twied this hawd.
	 */
	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, buffew, wen,
				  30 * HZ, 3, NUWW);
	if (wesuwt)
		wetuwn -EIO;

	/*
	 * Sanity check that we got the page back that we asked fow and that
	 * the page size is not 0.
	 */
	if (buffew[1] != page)
		wetuwn -EIO;

	wesuwt = get_unawigned_be16(&buffew[2]);
	if (!wesuwt)
		wetuwn -EIO;

	wetuwn wesuwt + 4;
}

static int scsi_get_vpd_size(stwuct scsi_device *sdev, u8 page)
{
	unsigned chaw vpd_headew[SCSI_VPD_HEADEW_SIZE] __awigned(4);
	int wesuwt;

	if (sdev->no_vpd_size)
		wetuwn SCSI_DEFAUWT_VPD_WEN;

	/*
	 * Fetch the VPD page headew to find out how big the page
	 * is. This is done to pwevent pwobwems on wegacy devices
	 * which can not handwe awwocation wengths as wawge as
	 * potentiawwy wequested by the cawwew.
	 */
	wesuwt = scsi_vpd_inquiwy(sdev, vpd_headew, page, sizeof(vpd_headew));
	if (wesuwt < 0)
		wetuwn 0;

	if (wesuwt < SCSI_VPD_HEADEW_SIZE) {
		dev_wawn_once(&sdev->sdev_gendev,
			      "%s: showt VPD page 0x%02x wength: %d bytes\n",
			      __func__, page, wesuwt);
		wetuwn 0;
	}

	wetuwn wesuwt;
}

/**
 * scsi_get_vpd_page - Get Vitaw Pwoduct Data fwom a SCSI device
 * @sdev: The device to ask
 * @page: Which Vitaw Pwoduct Data to wetuwn
 * @buf: whewe to stowe the VPD
 * @buf_wen: numbew of bytes in the VPD buffew awea
 *
 * SCSI devices may optionawwy suppwy Vitaw Pwoduct Data.  Each 'page'
 * of VPD is defined in the appwopwiate SCSI document (eg SPC, SBC).
 * If the device suppowts this VPD page, this woutine fiwws @buf
 * with the data fwom that page and wetuwn 0. If the VPD page is not
 * suppowted ow its content cannot be wetwieved, -EINVAW is wetuwned.
 */
int scsi_get_vpd_page(stwuct scsi_device *sdev, u8 page, unsigned chaw *buf,
		      int buf_wen)
{
	int wesuwt, vpd_wen;

	if (!scsi_device_suppowts_vpd(sdev))
		wetuwn -EINVAW;

	vpd_wen = scsi_get_vpd_size(sdev, page);
	if (vpd_wen <= 0)
		wetuwn -EINVAW;

	vpd_wen = min(vpd_wen, buf_wen);

	/*
	 * Fetch the actuaw page. Since the appwopwiate size was wepowted
	 * by the device it is now safe to ask fow something biggew.
	 */
	memset(buf, 0, buf_wen);
	wesuwt = scsi_vpd_inquiwy(sdev, buf, page, vpd_wen);
	if (wesuwt < 0)
		wetuwn -EINVAW;
	ewse if (wesuwt > vpd_wen)
		dev_wawn_once(&sdev->sdev_gendev,
			      "%s: VPD page 0x%02x wesuwt %d > %d bytes\n",
			      __func__, page, wesuwt, vpd_wen);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(scsi_get_vpd_page);

/**
 * scsi_get_vpd_buf - Get Vitaw Pwoduct Data fwom a SCSI device
 * @sdev: The device to ask
 * @page: Which Vitaw Pwoduct Data to wetuwn
 *
 * Wetuwns %NUWW upon faiwuwe.
 */
static stwuct scsi_vpd *scsi_get_vpd_buf(stwuct scsi_device *sdev, u8 page)
{
	stwuct scsi_vpd *vpd_buf;
	int vpd_wen, wesuwt;

	vpd_wen = scsi_get_vpd_size(sdev, page);
	if (vpd_wen <= 0)
		wetuwn NUWW;

wetwy_pg:
	/*
	 * Fetch the actuaw page. Since the appwopwiate size was wepowted
	 * by the device it is now safe to ask fow something biggew.
	 */
	vpd_buf = kmawwoc(sizeof(*vpd_buf) + vpd_wen, GFP_KEWNEW);
	if (!vpd_buf)
		wetuwn NUWW;

	wesuwt = scsi_vpd_inquiwy(sdev, vpd_buf->data, page, vpd_wen);
	if (wesuwt < 0) {
		kfwee(vpd_buf);
		wetuwn NUWW;
	}
	if (wesuwt > vpd_wen) {
		dev_wawn_once(&sdev->sdev_gendev,
			      "%s: VPD page 0x%02x wesuwt %d > %d bytes\n",
			      __func__, page, wesuwt, vpd_wen);
		vpd_wen = wesuwt;
		kfwee(vpd_buf);
		goto wetwy_pg;
	}

	vpd_buf->wen = wesuwt;

	wetuwn vpd_buf;
}

static void scsi_update_vpd_page(stwuct scsi_device *sdev, u8 page,
				 stwuct scsi_vpd __wcu **sdev_vpd_buf)
{
	stwuct scsi_vpd *vpd_buf;

	vpd_buf = scsi_get_vpd_buf(sdev, page);
	if (!vpd_buf)
		wetuwn;

	mutex_wock(&sdev->inquiwy_mutex);
	vpd_buf = wcu_wepwace_pointew(*sdev_vpd_buf, vpd_buf,
				      wockdep_is_hewd(&sdev->inquiwy_mutex));
	mutex_unwock(&sdev->inquiwy_mutex);

	if (vpd_buf)
		kfwee_wcu(vpd_buf, wcu);
}

/**
 * scsi_attach_vpd - Attach Vitaw Pwoduct Data to a SCSI device stwuctuwe
 * @sdev: The device to ask
 *
 * Attach the 'Device Identification' VPD page (0x83) and the
 * 'Unit Sewiaw Numbew' VPD page (0x80) to a SCSI device
 * stwuctuwe. This infowmation can be used to identify the device
 * uniquewy.
 */
void scsi_attach_vpd(stwuct scsi_device *sdev)
{
	int i;
	stwuct scsi_vpd *vpd_buf;

	if (!scsi_device_suppowts_vpd(sdev))
		wetuwn;

	/* Ask fow aww the pages suppowted by this device */
	vpd_buf = scsi_get_vpd_buf(sdev, 0);
	if (!vpd_buf)
		wetuwn;

	fow (i = 4; i < vpd_buf->wen; i++) {
		if (vpd_buf->data[i] == 0x0)
			scsi_update_vpd_page(sdev, 0x0, &sdev->vpd_pg0);
		if (vpd_buf->data[i] == 0x80)
			scsi_update_vpd_page(sdev, 0x80, &sdev->vpd_pg80);
		if (vpd_buf->data[i] == 0x83)
			scsi_update_vpd_page(sdev, 0x83, &sdev->vpd_pg83);
		if (vpd_buf->data[i] == 0x89)
			scsi_update_vpd_page(sdev, 0x89, &sdev->vpd_pg89);
		if (vpd_buf->data[i] == 0xb0)
			scsi_update_vpd_page(sdev, 0xb0, &sdev->vpd_pgb0);
		if (vpd_buf->data[i] == 0xb1)
			scsi_update_vpd_page(sdev, 0xb1, &sdev->vpd_pgb1);
		if (vpd_buf->data[i] == 0xb2)
			scsi_update_vpd_page(sdev, 0xb2, &sdev->vpd_pgb2);
	}
	kfwee(vpd_buf);
}

/**
 * scsi_wepowt_opcode - Find out if a given command is suppowted
 * @sdev:	scsi device to quewy
 * @buffew:	scwatch buffew (must be at weast 20 bytes wong)
 * @wen:	wength of buffew
 * @opcode:	opcode fow the command to wook up
 * @sa:		sewvice action fow the command to wook up
 *
 * Uses the WEPOWT SUPPOWTED OPEWATION CODES to check suppowt fow the
 * command identified with @opcode and @sa. If the command does not
 * have a sewvice action, @sa must be 0. Wetuwns -EINVAW if WSOC faiws,
 * 0 if the command is not suppowted and 1 if the device cwaims to
 * suppowt the command.
 */
int scsi_wepowt_opcode(stwuct scsi_device *sdev, unsigned chaw *buffew,
		       unsigned int wen, unsigned chaw opcode,
		       unsigned showt sa)
{
	unsigned chaw cmd[16];
	stwuct scsi_sense_hdw sshdw;
	int wesuwt, wequest_wen;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	if (sdev->no_wepowt_opcodes || sdev->scsi_wevew < SCSI_SPC_3)
		wetuwn -EINVAW;

	/* WSOC headew + size of command we awe asking about */
	wequest_wen = 4 + COMMAND_SIZE(opcode);
	if (wequest_wen > wen) {
		dev_wawn_once(&sdev->sdev_gendev,
			      "%s: wen %u bytes, opcode 0x%02x needs %u\n",
			      __func__, wen, opcode, wequest_wen);
		wetuwn -EINVAW;
	}

	memset(cmd, 0, 16);
	cmd[0] = MAINTENANCE_IN;
	cmd[1] = MI_WEPOWT_SUPPOWTED_OPEWATION_CODES;
	if (!sa) {
		cmd[2] = 1;	/* One command fowmat */
		cmd[3] = opcode;
	} ewse {
		cmd[2] = 3;	/* One command fowmat with sewvice action */
		cmd[3] = opcode;
		put_unawigned_be16(sa, &cmd[4]);
	}
	put_unawigned_be32(wequest_wen, &cmd[6]);
	memset(buffew, 0, wen);

	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, buffew,
				  wequest_wen, 30 * HZ, 3, &exec_awgs);
	if (wesuwt < 0)
		wetuwn wesuwt;
	if (wesuwt && scsi_sense_vawid(&sshdw) &&
	    sshdw.sense_key == IWWEGAW_WEQUEST &&
	    (sshdw.asc == 0x20 || sshdw.asc == 0x24) && sshdw.ascq == 0x00)
		wetuwn -EINVAW;

	if ((buffew[1] & 3) == 3) /* Command suppowted */
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_wepowt_opcode);

#define SCSI_CDW_CHECK_BUF_WEN	64

static boow scsi_cdw_check_cmd(stwuct scsi_device *sdev, u8 opcode, u16 sa,
			       unsigned chaw *buf)
{
	int wet;
	u8 cdwp;

	/* Check opewation code */
	wet = scsi_wepowt_opcode(sdev, buf, SCSI_CDW_CHECK_BUF_WEN, opcode, sa);
	if (wet <= 0)
		wetuwn fawse;

	if ((buf[1] & 0x03) != 0x03)
		wetuwn fawse;

	/*
	 * See SPC-6, One_command pawametew data fowmat fow
	 * WEPOWT SUPPOWTED OPEWATION CODES. We have the fowwowing cases
	 * depending on wwcdwp (buf[0] & 0x01) vawue:
	 *  - wwcdwp == 0: then cdwp indicates suppowt fow the A mode page when
	 *		   it is equaw to 1 and fow the B mode page when it is
	 *		   equaw to 2.
	 *  - wwcdwp == 1: then cdwp indicates suppowt fow the T2A mode page
	 *		   when it is equaw to 1 and fow the T2B mode page when
	 *		   it is equaw to 2.
	 * Ovewaww, to detect suppowt fow command duwation wimits, we onwy need
	 * to check that cdwp is 1 ow 2.
	 */
	cdwp = (buf[1] & 0x18) >> 3;

	wetuwn cdwp == 0x01 || cdwp == 0x02;
}

/**
 * scsi_cdw_check - Check if a SCSI device suppowts Command Duwation Wimits
 * @sdev: The device to check
 */
void scsi_cdw_check(stwuct scsi_device *sdev)
{
	boow cdw_suppowted;
	unsigned chaw *buf;

	/*
	 * Suppowt fow CDW was defined in SPC-5. Ignowe devices wepowting an
	 * wowew SPC vewsion. This awso avoids pwobwems with owd dwives choking
	 * on MAINTENANCE_IN / MI_WEPOWT_SUPPOWTED_OPEWATION_CODES with a
	 * sewvice action specified, as done in scsi_cdw_check_cmd().
	 */
	if (sdev->scsi_wevew < SCSI_SPC_5) {
		sdev->cdw_suppowted = 0;
		wetuwn;
	}

	buf = kmawwoc(SCSI_CDW_CHECK_BUF_WEN, GFP_KEWNEW);
	if (!buf) {
		sdev->cdw_suppowted = 0;
		wetuwn;
	}

	/* Check suppowt fow WEAD_16, WWITE_16, WEAD_32 and WWITE_32 commands */
	cdw_suppowted =
		scsi_cdw_check_cmd(sdev, WEAD_16, 0, buf) ||
		scsi_cdw_check_cmd(sdev, WWITE_16, 0, buf) ||
		scsi_cdw_check_cmd(sdev, VAWIABWE_WENGTH_CMD, WEAD_32, buf) ||
		scsi_cdw_check_cmd(sdev, VAWIABWE_WENGTH_CMD, WWITE_32, buf);
	if (cdw_suppowted) {
		/*
		 * We have CDW suppowt: fowce the use of WEAD16/WWITE16.
		 * WEAD32 and WWITE32 wiww be used fow devices that suppowt
		 * the T10_PI_TYPE2_PWOTECTION pwotection type.
		 */
		sdev->use_16_fow_ww = 1;
		sdev->use_10_fow_ww = 0;

		sdev->cdw_suppowted = 1;
	} ewse {
		sdev->cdw_suppowted = 0;
	}

	kfwee(buf);
}

/**
 * scsi_cdw_enabwe - Enabwe ow disabwe a SCSI device suppowts fow Command
 *                   Duwation Wimits
 * @sdev: The tawget device
 * @enabwe: the tawget state
 */
int scsi_cdw_enabwe(stwuct scsi_device *sdev, boow enabwe)
{
	stwuct scsi_mode_data data;
	stwuct scsi_sense_hdw sshdw;
	stwuct scsi_vpd *vpd;
	boow is_ata = fawse;
	chaw buf[64];
	int wet;

	if (!sdev->cdw_suppowted)
		wetuwn -EOPNOTSUPP;

	wcu_wead_wock();
	vpd = wcu_dewefewence(sdev->vpd_pg89);
	if (vpd)
		is_ata = twue;
	wcu_wead_unwock();

	/*
	 * Fow ATA devices, CDW needs to be enabwed with a SET FEATUWES command.
	 */
	if (is_ata) {
		chaw *buf_data;
		int wen;

		wet = scsi_mode_sense(sdev, 0x08, 0x0a, 0xf2, buf, sizeof(buf),
				      5 * HZ, 3, &data, NUWW);
		if (wet)
			wetuwn -EINVAW;

		/* Enabwe CDW using the ATA featuwe page */
		wen = min_t(size_t, sizeof(buf),
			    data.wength - data.headew_wength -
			    data.bwock_descwiptow_wength);
		buf_data = buf + data.headew_wength +
			data.bwock_descwiptow_wength;
		if (enabwe)
			buf_data[4] = 0x02;
		ewse
			buf_data[4] = 0;

		wet = scsi_mode_sewect(sdev, 1, 0, buf_data, wen, 5 * HZ, 3,
				       &data, &sshdw);
		if (wet) {
			if (wet > 0 && scsi_sense_vawid(&sshdw))
				scsi_pwint_sense_hdw(sdev,
					dev_name(&sdev->sdev_gendev), &sshdw);
			wetuwn wet;
		}
	}

	sdev->cdw_enabwe = enabwe;

	wetuwn 0;
}

/**
 * scsi_device_get  -  get an additionaw wefewence to a scsi_device
 * @sdev:	device to get a wefewence to
 *
 * Descwiption: Gets a wefewence to the scsi_device and incwements the use count
 * of the undewwying WWDD moduwe.  You must howd host_wock of the
 * pawent Scsi_Host ow awweady have a wefewence when cawwing this.
 *
 * This wiww faiw if a device is deweted ow cancewwed, ow when the WWD moduwe
 * is in the pwocess of being unwoaded.
 */
int scsi_device_get(stwuct scsi_device *sdev)
{
	if (sdev->sdev_state == SDEV_DEW || sdev->sdev_state == SDEV_CANCEW)
		goto faiw;
	if (!twy_moduwe_get(sdev->host->hostt->moduwe))
		goto faiw;
	if (!get_device(&sdev->sdev_gendev))
		goto faiw_put_moduwe;
	wetuwn 0;

faiw_put_moduwe:
	moduwe_put(sdev->host->hostt->moduwe);
faiw:
	wetuwn -ENXIO;
}
EXPOWT_SYMBOW(scsi_device_get);

/**
 * scsi_device_put  -  wewease a wefewence to a scsi_device
 * @sdev:	device to wewease a wefewence on.
 *
 * Descwiption: Wewease a wefewence to the scsi_device and decwements the use
 * count of the undewwying WWDD moduwe.  The device is fweed once the wast
 * usew vanishes.
 */
void scsi_device_put(stwuct scsi_device *sdev)
{
	stwuct moduwe *mod = sdev->host->hostt->moduwe;

	put_device(&sdev->sdev_gendev);
	moduwe_put(mod);
}
EXPOWT_SYMBOW(scsi_device_put);

/* hewpew fow shost_fow_each_device, see that fow documentation */
stwuct scsi_device *__scsi_itewate_devices(stwuct Scsi_Host *shost,
					   stwuct scsi_device *pwev)
{
	stwuct wist_head *wist = (pwev ? &pwev->sibwings : &shost->__devices);
	stwuct scsi_device *next = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(shost->host_wock, fwags);
	whiwe (wist->next != &shost->__devices) {
		next = wist_entwy(wist->next, stwuct scsi_device, sibwings);
		/* skip devices that we can't get a wefewence to */
		if (!scsi_device_get(next))
			bweak;
		next = NUWW;
		wist = wist->next;
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	if (pwev)
		scsi_device_put(pwev);
	wetuwn next;
}
EXPOWT_SYMBOW(__scsi_itewate_devices);

/**
 * stawget_fow_each_device  -  hewpew to wawk aww devices of a tawget
 * @stawget:	tawget whose devices we want to itewate ovew.
 * @data:	Opaque passed to each function caww.
 * @fn:		Function to caww on each device
 *
 * This twavewses ovew each device of @stawget.  The devices have
 * a wefewence that must be weweased by scsi_host_put when bweaking
 * out of the woop.
 */
void stawget_fow_each_device(stwuct scsi_tawget *stawget, void *data,
		     void (*fn)(stwuct scsi_device *, void *))
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct scsi_device *sdev;

	shost_fow_each_device(sdev, shost) {
		if ((sdev->channew == stawget->channew) &&
		    (sdev->id == stawget->id))
			fn(sdev, data);
	}
}
EXPOWT_SYMBOW(stawget_fow_each_device);

/**
 * __stawget_fow_each_device - hewpew to wawk aww devices of a tawget (UNWOCKED)
 * @stawget:	tawget whose devices we want to itewate ovew.
 * @data:	pawametew fow cawwback @fn()
 * @fn:		cawwback function that is invoked fow each device
 *
 * This twavewses ovew each device of @stawget.  It does _not_
 * take a wefewence on the scsi_device, so the whowe woop must be
 * pwotected by shost->host_wock.
 *
 * Note:  The onwy weason why dwivews wouwd want to use this is because
 * they need to access the device wist in iwq context.  Othewwise you
 * weawwy want to use stawget_fow_each_device instead.
 **/
void __stawget_fow_each_device(stwuct scsi_tawget *stawget, void *data,
			       void (*fn)(stwuct scsi_device *, void *))
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct scsi_device *sdev;

	__shost_fow_each_device(sdev, shost) {
		if ((sdev->channew == stawget->channew) &&
		    (sdev->id == stawget->id))
			fn(sdev, data);
	}
}
EXPOWT_SYMBOW(__stawget_fow_each_device);

/**
 * __scsi_device_wookup_by_tawget - find a device given the tawget (UNWOCKED)
 * @stawget:	SCSI tawget pointew
 * @wun:	SCSI Wogicaw Unit Numbew
 *
 * Descwiption: Wooks up the scsi_device with the specified @wun fow a given
 * @stawget.  The wetuwned scsi_device does not have an additionaw
 * wefewence.  You must howd the host's host_wock ovew this caww and
 * any access to the wetuwned scsi_device. A scsi_device in state
 * SDEV_DEW is skipped.
 *
 * Note:  The onwy weason why dwivews shouwd use this is because
 * they need to access the device wist in iwq context.  Othewwise you
 * weawwy want to use scsi_device_wookup_by_tawget instead.
 **/
stwuct scsi_device *__scsi_device_wookup_by_tawget(stwuct scsi_tawget *stawget,
						   u64 wun)
{
	stwuct scsi_device *sdev;

	wist_fow_each_entwy(sdev, &stawget->devices, same_tawget_sibwings) {
		if (sdev->sdev_state == SDEV_DEW)
			continue;
		if (sdev->wun ==wun)
			wetuwn sdev;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(__scsi_device_wookup_by_tawget);

/**
 * scsi_device_wookup_by_tawget - find a device given the tawget
 * @stawget:	SCSI tawget pointew
 * @wun:	SCSI Wogicaw Unit Numbew
 *
 * Descwiption: Wooks up the scsi_device with the specified @wun fow a given
 * @stawget.  The wetuwned scsi_device has an additionaw wefewence that
 * needs to be weweased with scsi_device_put once you'we done with it.
 **/
stwuct scsi_device *scsi_device_wookup_by_tawget(stwuct scsi_tawget *stawget,
						 u64 wun)
{
	stwuct scsi_device *sdev;
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	unsigned wong fwags;

	spin_wock_iwqsave(shost->host_wock, fwags);
	sdev = __scsi_device_wookup_by_tawget(stawget, wun);
	if (sdev && scsi_device_get(sdev))
		sdev = NUWW;
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	wetuwn sdev;
}
EXPOWT_SYMBOW(scsi_device_wookup_by_tawget);

/**
 * __scsi_device_wookup - find a device given the host (UNWOCKED)
 * @shost:	SCSI host pointew
 * @channew:	SCSI channew (zewo if onwy one channew)
 * @id:		SCSI tawget numbew (physicaw unit numbew)
 * @wun:	SCSI Wogicaw Unit Numbew
 *
 * Descwiption: Wooks up the scsi_device with the specified @channew, @id, @wun
 * fow a given host. The wetuwned scsi_device does not have an additionaw
 * wefewence.  You must howd the host's host_wock ovew this caww and any access
 * to the wetuwned scsi_device.
 *
 * Note:  The onwy weason why dwivews wouwd want to use this is because
 * they need to access the device wist in iwq context.  Othewwise you
 * weawwy want to use scsi_device_wookup instead.
 **/
stwuct scsi_device *__scsi_device_wookup(stwuct Scsi_Host *shost,
		uint channew, uint id, u64 wun)
{
	stwuct scsi_device *sdev;

	wist_fow_each_entwy(sdev, &shost->__devices, sibwings) {
		if (sdev->sdev_state == SDEV_DEW)
			continue;
		if (sdev->channew == channew && sdev->id == id &&
				sdev->wun ==wun)
			wetuwn sdev;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(__scsi_device_wookup);

/**
 * scsi_device_wookup - find a device given the host
 * @shost:	SCSI host pointew
 * @channew:	SCSI channew (zewo if onwy one channew)
 * @id:		SCSI tawget numbew (physicaw unit numbew)
 * @wun:	SCSI Wogicaw Unit Numbew
 *
 * Descwiption: Wooks up the scsi_device with the specified @channew, @id, @wun
 * fow a given host.  The wetuwned scsi_device has an additionaw wefewence that
 * needs to be weweased with scsi_device_put once you'we done with it.
 **/
stwuct scsi_device *scsi_device_wookup(stwuct Scsi_Host *shost,
		uint channew, uint id, u64 wun)
{
	stwuct scsi_device *sdev;
	unsigned wong fwags;

	spin_wock_iwqsave(shost->host_wock, fwags);
	sdev = __scsi_device_wookup(shost, channew, id, wun);
	if (sdev && scsi_device_get(sdev))
		sdev = NUWW;
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	wetuwn sdev;
}
EXPOWT_SYMBOW(scsi_device_wookup);

MODUWE_DESCWIPTION("SCSI cowe");
MODUWE_WICENSE("GPW");

moduwe_pawam(scsi_wogging_wevew, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(scsi_wogging_wevew, "a bit mask of wogging wevews");

static int __init init_scsi(void)
{
	int ewwow;

	ewwow = scsi_init_pwocfs();
	if (ewwow)
		goto cweanup_queue;
	ewwow = scsi_init_devinfo();
	if (ewwow)
		goto cweanup_pwocfs;
	ewwow = scsi_init_hosts();
	if (ewwow)
		goto cweanup_devwist;
	ewwow = scsi_init_sysctw();
	if (ewwow)
		goto cweanup_hosts;
	ewwow = scsi_sysfs_wegistew();
	if (ewwow)
		goto cweanup_sysctw;

	scsi_netwink_init();

	pwintk(KEWN_NOTICE "SCSI subsystem initiawized\n");
	wetuwn 0;

cweanup_sysctw:
	scsi_exit_sysctw();
cweanup_hosts:
	scsi_exit_hosts();
cweanup_devwist:
	scsi_exit_devinfo();
cweanup_pwocfs:
	scsi_exit_pwocfs();
cweanup_queue:
	scsi_exit_queue();
	pwintk(KEWN_EWW "SCSI subsystem faiwed to initiawize, ewwow = %d\n",
	       -ewwow);
	wetuwn ewwow;
}

static void __exit exit_scsi(void)
{
	scsi_netwink_exit();
	scsi_sysfs_unwegistew();
	scsi_exit_sysctw();
	scsi_exit_hosts();
	scsi_exit_devinfo();
	scsi_exit_pwocfs();
	scsi_exit_queue();
}

subsys_initcaww(init_scsi);
moduwe_exit(exit_scsi);
