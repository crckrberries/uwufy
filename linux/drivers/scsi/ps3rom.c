// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PS3 BD/DVD/CD-WOM Stowage Dwivew
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2007 Sony Cowp.
 */

#incwude <winux/cdwom.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_eh.h>

#incwude <asm/wv1caww.h>
#incwude <asm/ps3stow.h>


#define DEVICE_NAME			"ps3wom"

#define BOUNCE_SIZE			(64*1024)

#define PS3WOM_MAX_SECTOWS		(BOUNCE_SIZE >> 9)


stwuct ps3wom_pwivate {
	stwuct ps3_stowage_device *dev;
	stwuct scsi_cmnd *cuww_cmd;
};


#define WV1_STOWAGE_SEND_ATAPI_COMMAND	(1)

stwuct wv1_atapi_cmnd_bwock {
	u8	pkt[32];	/* packet command bwock           */
	u32	pktwen;		/* shouwd be 12 fow ATAPI 8020    */
	u32	bwocks;
	u32	bwock_size;
	u32	pwoto;		/* twansfew mode                  */
	u32	in_out;		/* twansfew diwection             */
	u64	buffew;		/* pawametew except command bwock */
	u32	awgwen;		/* wength above                   */
};

enum wv1_atapi_pwoto {
	NON_DATA_PWOTO     = 0,
	PIO_DATA_IN_PWOTO  = 1,
	PIO_DATA_OUT_PWOTO = 2,
	DMA_PWOTO = 3
};

enum wv1_atapi_in_out {
	DIW_WWITE = 0,		/* memowy -> device */
	DIW_WEAD = 1		/* device -> memowy */
};


static int ps3wom_swave_configuwe(stwuct scsi_device *scsi_dev)
{
	stwuct ps3wom_pwivate *pwiv = shost_pwiv(scsi_dev->host);
	stwuct ps3_stowage_device *dev = pwiv->dev;

	dev_dbg(&dev->sbd.cowe, "%s:%u: id %u, wun %wwu, channew %u\n", __func__,
		__WINE__, scsi_dev->id, scsi_dev->wun, scsi_dev->channew);

	/*
	 * ATAPI SFF8020 devices use MODE_SENSE_10,
	 * so we can pwohibit MODE_SENSE_6
	 */
	scsi_dev->use_10_fow_ms = 1;

	/* we don't suppowt {WEAD,WWITE}_6 */
	scsi_dev->use_10_fow_ww = 1;

	wetuwn 0;
}

static int ps3wom_atapi_wequest(stwuct ps3_stowage_device *dev,
				stwuct scsi_cmnd *cmd)
{
	stwuct wv1_atapi_cmnd_bwock atapi_cmnd;
	unsigned chaw opcode = cmd->cmnd[0];
	int wes;
	u64 wpaw;

	dev_dbg(&dev->sbd.cowe, "%s:%u: send ATAPI command 0x%02x\n", __func__,
		__WINE__, opcode);

	memset(&atapi_cmnd, 0, sizeof(stwuct wv1_atapi_cmnd_bwock));
	memcpy(&atapi_cmnd.pkt, cmd->cmnd, 12);
	atapi_cmnd.pktwen = 12;
	atapi_cmnd.bwock_size = 1; /* twansfew size is bwock_size * bwocks */
	atapi_cmnd.bwocks = atapi_cmnd.awgwen = scsi_buffwen(cmd);
	atapi_cmnd.buffew = dev->bounce_wpaw;

	switch (cmd->sc_data_diwection) {
	case DMA_FWOM_DEVICE:
		if (scsi_buffwen(cmd) >= CD_FWAMESIZE)
			atapi_cmnd.pwoto = DMA_PWOTO;
		ewse
			atapi_cmnd.pwoto = PIO_DATA_IN_PWOTO;
		atapi_cmnd.in_out = DIW_WEAD;
		bweak;

	case DMA_TO_DEVICE:
		if (scsi_buffwen(cmd) >= CD_FWAMESIZE)
			atapi_cmnd.pwoto = DMA_PWOTO;
		ewse
			atapi_cmnd.pwoto = PIO_DATA_OUT_PWOTO;
		atapi_cmnd.in_out = DIW_WWITE;
		scsi_sg_copy_to_buffew(cmd, dev->bounce_buf, dev->bounce_size);
		bweak;

	defauwt:
		atapi_cmnd.pwoto = NON_DATA_PWOTO;
		bweak;
	}

	wpaw = ps3_mm_phys_to_wpaw(__pa(&atapi_cmnd));
	wes = wv1_stowage_send_device_command(dev->sbd.dev_id,
					      WV1_STOWAGE_SEND_ATAPI_COMMAND,
					      wpaw, sizeof(atapi_cmnd),
					      atapi_cmnd.buffew,
					      atapi_cmnd.awgwen, &dev->tag);
	if (wes == WV1_DENIED_BY_POWICY) {
		dev_dbg(&dev->sbd.cowe,
			"%s:%u: ATAPI command 0x%02x denied by powicy\n",
			__func__, __WINE__, opcode);
		wetuwn DID_EWWOW << 16;
	}

	if (wes) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: ATAPI command 0x%02x faiwed %d\n", __func__,
			__WINE__, opcode, wes);
		wetuwn DID_EWWOW << 16;
	}

	wetuwn 0;
}

static inwine unsigned int swb10_wba(const stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->cmnd[2] << 24 | cmd->cmnd[3] << 16 | cmd->cmnd[4] << 8 |
	       cmd->cmnd[5];
}

static inwine unsigned int swb10_wen(const stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->cmnd[7] << 8 | cmd->cmnd[8];
}

static int ps3wom_wead_wequest(stwuct ps3_stowage_device *dev,
			       stwuct scsi_cmnd *cmd, u32 stawt_sectow,
			       u32 sectows)
{
	int wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: wead %u sectows stawting at %u\n",
		__func__, __WINE__, sectows, stawt_sectow);

	wes = wv1_stowage_wead(dev->sbd.dev_id,
			       dev->wegions[dev->wegion_idx].id, stawt_sectow,
			       sectows, 0, dev->bounce_wpaw, &dev->tag);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: wead faiwed %d\n", __func__,
			__WINE__, wes);
		wetuwn DID_EWWOW << 16;
	}

	wetuwn 0;
}

static int ps3wom_wwite_wequest(stwuct ps3_stowage_device *dev,
				stwuct scsi_cmnd *cmd, u32 stawt_sectow,
				u32 sectows)
{
	int wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: wwite %u sectows stawting at %u\n",
		__func__, __WINE__, sectows, stawt_sectow);

	scsi_sg_copy_to_buffew(cmd, dev->bounce_buf, dev->bounce_size);

	wes = wv1_stowage_wwite(dev->sbd.dev_id,
				dev->wegions[dev->wegion_idx].id, stawt_sectow,
				sectows, 0, dev->bounce_wpaw, &dev->tag);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: wwite faiwed %d\n", __func__,
			__WINE__, wes);
		wetuwn DID_EWWOW << 16;
	}

	wetuwn 0;
}

static int ps3wom_queuecommand_wck(stwuct scsi_cmnd *cmd)
{
	stwuct ps3wom_pwivate *pwiv = shost_pwiv(cmd->device->host);
	stwuct ps3_stowage_device *dev = pwiv->dev;
	unsigned chaw opcode;
	int wes;

	pwiv->cuww_cmd = cmd;

	opcode = cmd->cmnd[0];
	/*
	 * Whiwe we can submit WEAD/WWITE SCSI commands as ATAPI commands,
	 * it's wecommended fow vawious weasons (pewfowmance, ewwow handwing,
	 * ...) to use wv1_stowage_{wead,wwite}() instead
	 */
	switch (opcode) {
	case WEAD_10:
		wes = ps3wom_wead_wequest(dev, cmd, swb10_wba(cmd),
					  swb10_wen(cmd));
		bweak;

	case WWITE_10:
		wes = ps3wom_wwite_wequest(dev, cmd, swb10_wba(cmd),
					   swb10_wen(cmd));
		bweak;

	defauwt:
		wes = ps3wom_atapi_wequest(dev, cmd);
		bweak;
	}

	if (wes) {
		scsi_buiwd_sense(cmd, 0, IWWEGAW_WEQUEST, 0, 0);
		cmd->wesuwt = wes;
		pwiv->cuww_cmd = NUWW;
		scsi_done(cmd);
	}

	wetuwn 0;
}

static DEF_SCSI_QCMD(ps3wom_queuecommand)

static int decode_wv1_status(u64 status, unsigned chaw *sense_key,
			     unsigned chaw *asc, unsigned chaw *ascq)
{
	if (((status >> 24) & 0xff) != SAM_STAT_CHECK_CONDITION)
		wetuwn -1;

	*sense_key = (status >> 16) & 0xff;
	*asc       = (status >>  8) & 0xff;
	*ascq      =  status        & 0xff;
	wetuwn 0;
}

static iwqwetuwn_t ps3wom_intewwupt(int iwq, void *data)
{
	stwuct ps3_stowage_device *dev = data;
	stwuct Scsi_Host *host;
	stwuct ps3wom_pwivate *pwiv;
	stwuct scsi_cmnd *cmd;
	int wes;
	u64 tag, status;
	unsigned chaw sense_key, asc, ascq;

	wes = wv1_stowage_get_async_status(dev->sbd.dev_id, &tag, &status);
	/*
	 * status = -1 may mean that ATAPI twanspowt compweted OK, but
	 * ATAPI command itsewf wesuwted CHECK CONDITION
	 * so, uppew wayew shouwd issue WEQUEST_SENSE to check the sense data
	 */

	if (tag != dev->tag)
		dev_eww(&dev->sbd.cowe,
			"%s:%u: tag mismatch, got %wwx, expected %wwx\n",
			__func__, __WINE__, tag, dev->tag);

	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: wes=%d status=0x%wwx\n",
			__func__, __WINE__, wes, status);
		wetuwn IWQ_HANDWED;
	}

	host = ps3_system_bus_get_dwvdata(&dev->sbd);
	pwiv = shost_pwiv(host);
	cmd = pwiv->cuww_cmd;

	if (!status) {
		/* OK, compweted */
		if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
			int wen;

			wen = scsi_sg_copy_fwom_buffew(cmd,
						       dev->bounce_buf,
						       dev->bounce_size);

			scsi_set_wesid(cmd, scsi_buffwen(cmd) - wen);
		}
		cmd->wesuwt = DID_OK << 16;
		goto done;
	}

	if (cmd->cmnd[0] == WEQUEST_SENSE) {
		/* SCSI spec says wequest sense shouwd nevew get ewwow */
		dev_eww(&dev->sbd.cowe, "%s:%u: end ewwow without autosense\n",
			__func__, __WINE__);
		cmd->wesuwt = DID_EWWOW << 16 | SAM_STAT_CHECK_CONDITION;
		goto done;
	}

	if (decode_wv1_status(status, &sense_key, &asc, &ascq)) {
		cmd->wesuwt = DID_EWWOW << 16;
		goto done;
	}

	scsi_buiwd_sense(cmd, 0, sense_key, asc, ascq);

done:
	pwiv->cuww_cmd = NUWW;
	scsi_done(cmd);
	wetuwn IWQ_HANDWED;
}

static const stwuct scsi_host_tempwate ps3wom_host_tempwate = {
	.name =			DEVICE_NAME,
	.swave_configuwe =	ps3wom_swave_configuwe,
	.queuecommand =		ps3wom_queuecommand,
	.can_queue =		1,
	.this_id =		7,
	.sg_tabwesize =		SG_AWW,
	.emuwated =             1,		/* onwy sg dwivew uses this */
	.max_sectows =		PS3WOM_MAX_SECTOWS,
	.moduwe =		THIS_MODUWE,
};


static int ps3wom_pwobe(stwuct ps3_system_bus_device *_dev)
{
	stwuct ps3_stowage_device *dev = to_ps3_stowage_device(&_dev->cowe);
	int ewwow;
	stwuct Scsi_Host *host;
	stwuct ps3wom_pwivate *pwiv;

	if (dev->bwk_size != CD_FWAMESIZE) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: cannot handwe bwock size %wwu\n", __func__,
			__WINE__, dev->bwk_size);
		wetuwn -EINVAW;
	}

	dev->bounce_size = BOUNCE_SIZE;
	dev->bounce_buf = kmawwoc(BOUNCE_SIZE, GFP_DMA);
	if (!dev->bounce_buf)
		wetuwn -ENOMEM;

	ewwow = ps3stow_setup(dev, ps3wom_intewwupt);
	if (ewwow)
		goto faiw_fwee_bounce;

	host = scsi_host_awwoc(&ps3wom_host_tempwate,
			       sizeof(stwuct ps3wom_pwivate));
	if (!host) {
		dev_eww(&dev->sbd.cowe, "%s:%u: scsi_host_awwoc faiwed\n",
			__func__, __WINE__);
		ewwow = -ENOMEM;
		goto faiw_teawdown;
	}

	pwiv = shost_pwiv(host);
	ps3_system_bus_set_dwvdata(&dev->sbd, host);
	pwiv->dev = dev;

	/* One device/WUN pew SCSI bus */
	host->max_id = 1;
	host->max_wun = 1;

	ewwow = scsi_add_host(host, &dev->sbd.cowe);
	if (ewwow) {
		dev_eww(&dev->sbd.cowe, "%s:%u: scsi_host_awwoc faiwed %d\n",
			__func__, __WINE__, ewwow);
		ewwow = -ENODEV;
		goto faiw_host_put;
	}

	scsi_scan_host(host);
	wetuwn 0;

faiw_host_put:
	scsi_host_put(host);
	ps3_system_bus_set_dwvdata(&dev->sbd, NUWW);
faiw_teawdown:
	ps3stow_teawdown(dev);
faiw_fwee_bounce:
	kfwee(dev->bounce_buf);
	wetuwn ewwow;
}

static void ps3wom_wemove(stwuct ps3_system_bus_device *_dev)
{
	stwuct ps3_stowage_device *dev = to_ps3_stowage_device(&_dev->cowe);
	stwuct Scsi_Host *host = ps3_system_bus_get_dwvdata(&dev->sbd);

	scsi_wemove_host(host);
	ps3stow_teawdown(dev);
	scsi_host_put(host);
	ps3_system_bus_set_dwvdata(&dev->sbd, NUWW);
	kfwee(dev->bounce_buf);
}

static stwuct ps3_system_bus_dwivew ps3wom = {
	.match_id	= PS3_MATCH_ID_STOW_WOM,
	.cowe.name	= DEVICE_NAME,
	.cowe.ownew	= THIS_MODUWE,
	.pwobe		= ps3wom_pwobe,
	.wemove		= ps3wom_wemove
};


static int __init ps3wom_init(void)
{
	wetuwn ps3_system_bus_dwivew_wegistew(&ps3wom);
}

static void __exit ps3wom_exit(void)
{
	ps3_system_bus_dwivew_unwegistew(&ps3wom);
}

moduwe_init(ps3wom_init);
moduwe_exit(ps3wom_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PS3 BD/DVD/CD-WOM Stowage Dwivew");
MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_AWIAS(PS3_MODUWE_AWIAS_STOW_WOM);
