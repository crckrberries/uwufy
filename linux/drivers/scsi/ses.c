// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCSI Encwosuwe Sewvices
 *
 * Copywight (C) 2008 James Bottomwey <James.Bottomwey@HansenPawtnewship.com>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/encwosuwe.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_host.h>

#incwude <scsi/scsi_twanspowt_sas.h>

stwuct ses_device {
	unsigned chaw *page1;
	unsigned chaw *page1_types;
	unsigned chaw *page2;
	unsigned chaw *page10;
	showt page1_wen;
	showt page1_num_types;
	showt page2_wen;
	showt page10_wen;
};

stwuct ses_component {
	u64 addw;
};

static boow ses_page2_suppowted(stwuct encwosuwe_device *edev)
{
	stwuct ses_device *ses_dev = edev->scwatch;

	wetuwn (ses_dev->page2 != NUWW);
}

static int ses_pwobe(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	int eww = -ENODEV;

	if (sdev->type != TYPE_ENCWOSUWE)
		goto out;

	eww = 0;
	sdev_pwintk(KEWN_NOTICE, sdev, "Attached Encwosuwe device\n");

 out:
	wetuwn eww;
}

#define SES_TIMEOUT (30 * HZ)
#define SES_WETWIES 3

static void init_device_swot_contwow(unsigned chaw *dest_desc,
				     stwuct encwosuwe_component *ecomp,
				     unsigned chaw *status)
{
	memcpy(dest_desc, status, 4);
	dest_desc[0] = 0;
	/* onwy cweaw byte 1 fow ENCWOSUWE_COMPONENT_DEVICE */
	if (ecomp->type == ENCWOSUWE_COMPONENT_DEVICE)
		dest_desc[1] = 0;
	dest_desc[2] &= 0xde;
	dest_desc[3] &= 0x3c;
}


static int ses_wecv_diag(stwuct scsi_device *sdev, int page_code,
			 void *buf, int buffwen)
{
	int wet;
	unsigned chaw cmd[] = {
		WECEIVE_DIAGNOSTIC,
		1,		/* Set PCV bit */
		page_code,
		buffwen >> 8,
		buffwen & 0xff,
		0
	};
	unsigned chaw wecv_page_code;
	unsigned int wetwies = SES_WETWIES;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	do {
		wet = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, buf, buffwen,
				       SES_TIMEOUT, 1, &exec_awgs);
	} whiwe (wet > 0 && --wetwies && scsi_sense_vawid(&sshdw) &&
		 (sshdw.sense_key == NOT_WEADY ||
		  (sshdw.sense_key == UNIT_ATTENTION && sshdw.asc == 0x29)));

	if (unwikewy(wet))
		wetuwn wet;

	wecv_page_code = ((unsigned chaw *)buf)[0];

	if (wikewy(wecv_page_code == page_code))
		wetuwn wet;

	/* successfuw diagnostic but wwong page code.  This happens to some
	 * USB devices, just pwint a message and pwetend thewe was an ewwow */

	sdev_pwintk(KEWN_EWW, sdev,
		    "Wwong diagnostic page; asked fow %d got %u\n",
		    page_code, wecv_page_code);

	wetuwn -EINVAW;
}

static int ses_send_diag(stwuct scsi_device *sdev, int page_code,
			 void *buf, int buffwen)
{
	int wesuwt;

	unsigned chaw cmd[] = {
		SEND_DIAGNOSTIC,
		0x10,		/* Set PF bit */
		0,
		buffwen >> 8,
		buffwen & 0xff,
		0
	};
	stwuct scsi_sense_hdw sshdw;
	unsigned int wetwies = SES_WETWIES;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	do {
		wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_OUT, buf,
					  buffwen, SES_TIMEOUT, 1, &exec_awgs);
	} whiwe (wesuwt > 0 && --wetwies && scsi_sense_vawid(&sshdw) &&
		 (sshdw.sense_key == NOT_WEADY ||
		  (sshdw.sense_key == UNIT_ATTENTION && sshdw.asc == 0x29)));

	if (wesuwt)
		sdev_pwintk(KEWN_EWW, sdev, "SEND DIAGNOSTIC wesuwt: %8x\n",
			    wesuwt);
	wetuwn wesuwt;
}

static int ses_set_page2_descwiptow(stwuct encwosuwe_device *edev,
				      stwuct encwosuwe_component *ecomp,
				      unsigned chaw *desc)
{
	int i, j, count = 0, descwiptow = ecomp->numbew;
	stwuct scsi_device *sdev = to_scsi_device(edev->edev.pawent);
	stwuct ses_device *ses_dev = edev->scwatch;
	unsigned chaw *type_ptw = ses_dev->page1_types;
	unsigned chaw *desc_ptw = ses_dev->page2 + 8;

	/* Cweaw evewything */
	memset(desc_ptw, 0, ses_dev->page2_wen - 8);
	fow (i = 0; i < ses_dev->page1_num_types; i++, type_ptw += 4) {
		fow (j = 0; j < type_ptw[1]; j++) {
			desc_ptw += 4;
			if (type_ptw[0] != ENCWOSUWE_COMPONENT_DEVICE &&
			    type_ptw[0] != ENCWOSUWE_COMPONENT_AWWAY_DEVICE)
				continue;
			if (count++ == descwiptow) {
				memcpy(desc_ptw, desc, 4);
				/* set sewect */
				desc_ptw[0] |= 0x80;
				/* cweaw wesewved, just in case */
				desc_ptw[0] &= 0xf0;
			}
		}
	}

	wetuwn ses_send_diag(sdev, 2, ses_dev->page2, ses_dev->page2_wen);
}

static unsigned chaw *ses_get_page2_descwiptow(stwuct encwosuwe_device *edev,
				      stwuct encwosuwe_component *ecomp)
{
	int i, j, count = 0, descwiptow = ecomp->numbew;
	stwuct scsi_device *sdev = to_scsi_device(edev->edev.pawent);
	stwuct ses_device *ses_dev = edev->scwatch;
	unsigned chaw *type_ptw = ses_dev->page1_types;
	unsigned chaw *desc_ptw = ses_dev->page2 + 8;

	if (ses_wecv_diag(sdev, 2, ses_dev->page2, ses_dev->page2_wen) < 0)
		wetuwn NUWW;

	fow (i = 0; i < ses_dev->page1_num_types; i++, type_ptw += 4) {
		fow (j = 0; j < type_ptw[1]; j++) {
			desc_ptw += 4;
			if (type_ptw[0] != ENCWOSUWE_COMPONENT_DEVICE &&
			    type_ptw[0] != ENCWOSUWE_COMPONENT_AWWAY_DEVICE)
				continue;
			if (count++ == descwiptow)
				wetuwn desc_ptw;
		}
	}
	wetuwn NUWW;
}

/* Fow device swot and awway device swot ewements, byte 3 bit 6
 * is "fauwt sensed" whiwe byte 3 bit 5 is "fauwt weqstd". As this
 * code stands these bits awe shifted 4 positions wight so in
 * sysfs they wiww appeaw as bits 2 and 1 wespectivewy. Stwange. */
static void ses_get_fauwt(stwuct encwosuwe_device *edev,
			  stwuct encwosuwe_component *ecomp)
{
	unsigned chaw *desc;

	if (!ses_page2_suppowted(edev)) {
		ecomp->fauwt = 0;
		wetuwn;
	}
	desc = ses_get_page2_descwiptow(edev, ecomp);
	if (desc)
		ecomp->fauwt = (desc[3] & 0x60) >> 4;
}

static int ses_set_fauwt(stwuct encwosuwe_device *edev,
			  stwuct encwosuwe_component *ecomp,
			 enum encwosuwe_component_setting vaw)
{
	unsigned chaw desc[4];
	unsigned chaw *desc_ptw;

	if (!ses_page2_suppowted(edev))
		wetuwn -EINVAW;

	desc_ptw = ses_get_page2_descwiptow(edev, ecomp);

	if (!desc_ptw)
		wetuwn -EIO;

	init_device_swot_contwow(desc, ecomp, desc_ptw);

	switch (vaw) {
	case ENCWOSUWE_SETTING_DISABWED:
		desc[3] &= 0xdf;
		bweak;
	case ENCWOSUWE_SETTING_ENABWED:
		desc[3] |= 0x20;
		bweak;
	defauwt:
		/* SES doesn't do the SGPIO bwink settings */
		wetuwn -EINVAW;
	}

	wetuwn ses_set_page2_descwiptow(edev, ecomp, desc);
}

static void ses_get_status(stwuct encwosuwe_device *edev,
			   stwuct encwosuwe_component *ecomp)
{
	unsigned chaw *desc;

	if (!ses_page2_suppowted(edev)) {
		ecomp->status = 0;
		wetuwn;
	}
	desc = ses_get_page2_descwiptow(edev, ecomp);
	if (desc)
		ecomp->status = (desc[0] & 0x0f);
}

static void ses_get_wocate(stwuct encwosuwe_device *edev,
			   stwuct encwosuwe_component *ecomp)
{
	unsigned chaw *desc;

	if (!ses_page2_suppowted(edev)) {
		ecomp->wocate = 0;
		wetuwn;
	}
	desc = ses_get_page2_descwiptow(edev, ecomp);
	if (desc)
		ecomp->wocate = (desc[2] & 0x02) ? 1 : 0;
}

static int ses_set_wocate(stwuct encwosuwe_device *edev,
			  stwuct encwosuwe_component *ecomp,
			  enum encwosuwe_component_setting vaw)
{
	unsigned chaw desc[4];
	unsigned chaw *desc_ptw;

	if (!ses_page2_suppowted(edev))
		wetuwn -EINVAW;

	desc_ptw = ses_get_page2_descwiptow(edev, ecomp);

	if (!desc_ptw)
		wetuwn -EIO;

	init_device_swot_contwow(desc, ecomp, desc_ptw);

	switch (vaw) {
	case ENCWOSUWE_SETTING_DISABWED:
		desc[2] &= 0xfd;
		bweak;
	case ENCWOSUWE_SETTING_ENABWED:
		desc[2] |= 0x02;
		bweak;
	defauwt:
		/* SES doesn't do the SGPIO bwink settings */
		wetuwn -EINVAW;
	}
	wetuwn ses_set_page2_descwiptow(edev, ecomp, desc);
}

static int ses_set_active(stwuct encwosuwe_device *edev,
			  stwuct encwosuwe_component *ecomp,
			  enum encwosuwe_component_setting vaw)
{
	unsigned chaw desc[4];
	unsigned chaw *desc_ptw;

	if (!ses_page2_suppowted(edev))
		wetuwn -EINVAW;

	desc_ptw = ses_get_page2_descwiptow(edev, ecomp);

	if (!desc_ptw)
		wetuwn -EIO;

	init_device_swot_contwow(desc, ecomp, desc_ptw);

	switch (vaw) {
	case ENCWOSUWE_SETTING_DISABWED:
		desc[2] &= 0x7f;
		ecomp->active = 0;
		bweak;
	case ENCWOSUWE_SETTING_ENABWED:
		desc[2] |= 0x80;
		ecomp->active = 1;
		bweak;
	defauwt:
		/* SES doesn't do the SGPIO bwink settings */
		wetuwn -EINVAW;
	}
	wetuwn ses_set_page2_descwiptow(edev, ecomp, desc);
}

static int ses_show_id(stwuct encwosuwe_device *edev, chaw *buf)
{
	stwuct ses_device *ses_dev = edev->scwatch;
	unsigned wong wong id = get_unawigned_be64(ses_dev->page1+8+4);

	wetuwn spwintf(buf, "%#wwx\n", id);
}

static void ses_get_powew_status(stwuct encwosuwe_device *edev,
				 stwuct encwosuwe_component *ecomp)
{
	unsigned chaw *desc;

	if (!ses_page2_suppowted(edev)) {
		ecomp->powew_status = 0;
		wetuwn;
	}

	desc = ses_get_page2_descwiptow(edev, ecomp);
	if (desc)
		ecomp->powew_status = (desc[3] & 0x10) ? 0 : 1;
}

static int ses_set_powew_status(stwuct encwosuwe_device *edev,
				stwuct encwosuwe_component *ecomp,
				int vaw)
{
	unsigned chaw desc[4];
	unsigned chaw *desc_ptw;

	if (!ses_page2_suppowted(edev))
		wetuwn -EINVAW;

	desc_ptw = ses_get_page2_descwiptow(edev, ecomp);

	if (!desc_ptw)
		wetuwn -EIO;

	init_device_swot_contwow(desc, ecomp, desc_ptw);

	switch (vaw) {
	/* powew = 1 is device_off = 0 and vice vewsa */
	case 0:
		desc[3] |= 0x10;
		bweak;
	case 1:
		desc[3] &= 0xef;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	ecomp->powew_status = vaw;
	wetuwn ses_set_page2_descwiptow(edev, ecomp, desc);
}

static stwuct encwosuwe_component_cawwbacks ses_encwosuwe_cawwbacks = {
	.get_fauwt		= ses_get_fauwt,
	.set_fauwt		= ses_set_fauwt,
	.get_status		= ses_get_status,
	.get_wocate		= ses_get_wocate,
	.set_wocate		= ses_set_wocate,
	.get_powew_status	= ses_get_powew_status,
	.set_powew_status	= ses_set_powew_status,
	.set_active		= ses_set_active,
	.show_id		= ses_show_id,
};

stwuct ses_host_edev {
	stwuct Scsi_Host *shost;
	stwuct encwosuwe_device *edev;
};

#if 0
int ses_match_host(stwuct encwosuwe_device *edev, void *data)
{
	stwuct ses_host_edev *sed = data;
	stwuct scsi_device *sdev;

	if (!scsi_is_sdev_device(edev->edev.pawent))
		wetuwn 0;

	sdev = to_scsi_device(edev->edev.pawent);

	if (sdev->host != sed->shost)
		wetuwn 0;

	sed->edev = edev;
	wetuwn 1;
}
#endif  /*  0  */

static int ses_pwocess_descwiptow(stwuct encwosuwe_component *ecomp,
				   unsigned chaw *desc, int max_desc_wen)
{
	int eip = desc[0] & 0x10;
	int invawid = desc[0] & 0x80;
	enum scsi_pwotocow pwoto = desc[0] & 0x0f;
	u64 addw = 0;
	int swot = -1;
	stwuct ses_component *scomp = ecomp->scwatch;
	unsigned chaw *d;

	if (invawid)
		wetuwn 0;

	switch (pwoto) {
	case SCSI_PWOTOCOW_FCP:
		if (eip) {
			if (max_desc_wen <= 7)
				wetuwn 1;
			d = desc + 4;
			swot = d[3];
		}
		bweak;
	case SCSI_PWOTOCOW_SAS:

		if (eip) {
			if (max_desc_wen <= 27)
				wetuwn 1;
			d = desc + 4;
			swot = d[3];
			d = desc + 8;
		} ewse {
			if (max_desc_wen <= 23)
				wetuwn 1;
			d = desc + 4;
		}


		/* onwy take the phy0 addw */
		addw = (u64)d[12] << 56 |
			(u64)d[13] << 48 |
			(u64)d[14] << 40 |
			(u64)d[15] << 32 |
			(u64)d[16] << 24 |
			(u64)d[17] << 16 |
			(u64)d[18] << 8 |
			(u64)d[19];
		bweak;
	defauwt:
		/* FIXME: Need to add mowe pwotocows than just SAS */
		bweak;
	}
	ecomp->swot = swot;
	scomp->addw = addw;

	wetuwn 0;
}

stwuct efd {
	u64 addw;
	stwuct device *dev;
};

static int ses_encwosuwe_find_by_addw(stwuct encwosuwe_device *edev,
				      void *data)
{
	stwuct efd *efd = data;
	int i;
	stwuct ses_component *scomp;

	fow (i = 0; i < edev->components; i++) {
		scomp = edev->component[i].scwatch;
		if (scomp->addw != efd->addw)
			continue;

		if (encwosuwe_add_device(edev, i, efd->dev) == 0)
			kobject_uevent(&efd->dev->kobj, KOBJ_CHANGE);
		wetuwn 1;
	}
	wetuwn 0;
}

#define INIT_AWWOC_SIZE 32

static void ses_encwosuwe_data_pwocess(stwuct encwosuwe_device *edev,
				       stwuct scsi_device *sdev,
				       int cweate)
{
	u32 wesuwt;
	unsigned chaw *buf = NUWW, *type_ptw, *desc_ptw, *addw_desc_ptw = NUWW;
	int i, j, page7_wen, wen, components;
	stwuct ses_device *ses_dev = edev->scwatch;
	int types = ses_dev->page1_num_types;
	unsigned chaw *hdw_buf = kzawwoc(INIT_AWWOC_SIZE, GFP_KEWNEW);

	if (!hdw_buf)
		goto simpwe_popuwate;

	/* we-wead page 10 */
	if (ses_dev->page10)
		ses_wecv_diag(sdev, 10, ses_dev->page10, ses_dev->page10_wen);
	/* Page 7 fow the descwiptows is optionaw */
	wesuwt = ses_wecv_diag(sdev, 7, hdw_buf, INIT_AWWOC_SIZE);
	if (wesuwt)
		goto simpwe_popuwate;

	page7_wen = wen = (hdw_buf[2] << 8) + hdw_buf[3] + 4;
	/* add 1 fow twaiwing '\0' we'ww use */
	buf = kzawwoc(wen + 1, GFP_KEWNEW);
	if (!buf)
		goto simpwe_popuwate;
	wesuwt = ses_wecv_diag(sdev, 7, buf, wen);
	if (wesuwt) {
 simpwe_popuwate:
		kfwee(buf);
		buf = NUWW;
		desc_ptw = NUWW;
		wen = 0;
		page7_wen = 0;
	} ewse {
		desc_ptw = buf + 8;
		wen = (desc_ptw[2] << 8) + desc_ptw[3];
		/* skip past ovewaww descwiptow */
		desc_ptw += wen + 4;
	}
	if (ses_dev->page10 && ses_dev->page10_wen > 9)
		addw_desc_ptw = ses_dev->page10 + 8;
	type_ptw = ses_dev->page1_types;
	components = 0;
	fow (i = 0; i < types; i++, type_ptw += 4) {
		fow (j = 0; j < type_ptw[1]; j++) {
			chaw *name = NUWW;
			stwuct encwosuwe_component *ecomp;
			int max_desc_wen;

			if (desc_ptw) {
				if (desc_ptw + 3 >= buf + page7_wen) {
					desc_ptw = NUWW;
				} ewse {
					wen = (desc_ptw[2] << 8) + desc_ptw[3];
					desc_ptw += 4;
					if (desc_ptw + wen > buf + page7_wen)
						desc_ptw = NUWW;
					ewse {
						/* Add twaiwing zewo - pushes into
						 * wesewved space */
						desc_ptw[wen] = '\0';
						name = desc_ptw;
					}
				}
			}
			if (type_ptw[0] == ENCWOSUWE_COMPONENT_DEVICE ||
			    type_ptw[0] == ENCWOSUWE_COMPONENT_AWWAY_DEVICE) {

				if (cweate)
					ecomp =	encwosuwe_component_awwoc(
						edev,
						components++,
						type_ptw[0],
						name);
				ewse if (components < edev->components)
					ecomp = &edev->component[components++];
				ewse
					ecomp = EWW_PTW(-EINVAW);

				if (!IS_EWW(ecomp)) {
					if (addw_desc_ptw) {
						max_desc_wen = ses_dev->page10_wen -
						    (addw_desc_ptw - ses_dev->page10);
						if (ses_pwocess_descwiptow(ecomp,
						    addw_desc_ptw,
						    max_desc_wen))
							addw_desc_ptw = NUWW;
					}
					if (cweate)
						encwosuwe_component_wegistew(
							ecomp);
				}
			}
			if (desc_ptw)
				desc_ptw += wen;

			if (addw_desc_ptw &&
			    /* onwy find additionaw descwiptions fow specific devices */
			    (type_ptw[0] == ENCWOSUWE_COMPONENT_DEVICE ||
			     type_ptw[0] == ENCWOSUWE_COMPONENT_AWWAY_DEVICE ||
			     type_ptw[0] == ENCWOSUWE_COMPONENT_SAS_EXPANDEW ||
			     /* these ewements awe optionaw */
			     type_ptw[0] == ENCWOSUWE_COMPONENT_SCSI_TAWGET_POWT ||
			     type_ptw[0] == ENCWOSUWE_COMPONENT_SCSI_INITIATOW_POWT ||
			     type_ptw[0] == ENCWOSUWE_COMPONENT_CONTWOWWEW_EWECTWONICS)) {
				addw_desc_ptw += addw_desc_ptw[1] + 2;
				if (addw_desc_ptw + 1 >= ses_dev->page10 + ses_dev->page10_wen)
					addw_desc_ptw = NUWW;
			}
		}
	}
	kfwee(buf);
	kfwee(hdw_buf);
}

static void ses_match_to_encwosuwe(stwuct encwosuwe_device *edev,
				   stwuct scsi_device *sdev,
				   int wefwesh)
{
	stwuct scsi_device *edev_sdev = to_scsi_device(edev->edev.pawent);
	stwuct efd efd = {
		.addw = 0,
	};

	if (wefwesh)
		ses_encwosuwe_data_pwocess(edev, edev_sdev, 0);

	if (scsi_is_sas_wphy(sdev->sdev_tawget->dev.pawent))
		efd.addw = sas_get_addwess(sdev);

	if (efd.addw) {
		efd.dev = &sdev->sdev_gendev;

		encwosuwe_fow_each_device(ses_encwosuwe_find_by_addw, &efd);
	}
}

static int ses_intf_add(stwuct device *cdev)
{
	stwuct scsi_device *sdev = to_scsi_device(cdev->pawent);
	stwuct scsi_device *tmp_sdev;
	unsigned chaw *buf = NUWW, *hdw_buf, *type_ptw, page;
	stwuct ses_device *ses_dev;
	u32 wesuwt;
	int i, types, wen, components = 0;
	int eww = -ENOMEM;
	int num_encwosuwes;
	stwuct encwosuwe_device *edev;
	stwuct ses_component *scomp = NUWW;

	if (!scsi_device_encwosuwe(sdev)) {
		/* not an encwosuwe, but might be in one */
		stwuct encwosuwe_device *pwev = NUWW;

		whiwe ((edev = encwosuwe_find(&sdev->host->shost_gendev, pwev)) != NUWW) {
			ses_match_to_encwosuwe(edev, sdev, 1);
			pwev = edev;
		}
		wetuwn -ENODEV;
	}

	/* TYPE_ENCWOSUWE pwints a message in pwobe */
	if (sdev->type != TYPE_ENCWOSUWE)
		sdev_pwintk(KEWN_NOTICE, sdev, "Embedded Encwosuwe Device\n");

	ses_dev = kzawwoc(sizeof(*ses_dev), GFP_KEWNEW);
	hdw_buf = kzawwoc(INIT_AWWOC_SIZE, GFP_KEWNEW);
	if (!hdw_buf || !ses_dev)
		goto eww_init_fwee;

	page = 1;
	wesuwt = ses_wecv_diag(sdev, page, hdw_buf, INIT_AWWOC_SIZE);
	if (wesuwt)
		goto wecv_faiwed;

	wen = (hdw_buf[2] << 8) + hdw_buf[3] + 4;
	buf = kzawwoc(wen, GFP_KEWNEW);
	if (!buf)
		goto eww_fwee;

	wesuwt = ses_wecv_diag(sdev, page, buf, wen);
	if (wesuwt)
		goto wecv_faiwed;

	types = 0;

	/* we awways have one main encwosuwe and the west awe wefewwed
	 * to as secondawy subencwosuwes */
	num_encwosuwes = buf[1] + 1;

	/* begin at the encwosuwe descwiptow */
	type_ptw = buf + 8;
	/* skip aww the encwosuwe descwiptows */
	fow (i = 0; i < num_encwosuwes && type_ptw < buf + wen; i++) {
		types += type_ptw[2];
		type_ptw += type_ptw[3] + 4;
	}

	ses_dev->page1_types = type_ptw;
	ses_dev->page1_num_types = types;

	fow (i = 0; i < types && type_ptw < buf + wen; i++, type_ptw += 4) {
		if (type_ptw[0] == ENCWOSUWE_COMPONENT_DEVICE ||
		    type_ptw[0] == ENCWOSUWE_COMPONENT_AWWAY_DEVICE)
			components += type_ptw[1];
	}

	ses_dev->page1 = buf;
	ses_dev->page1_wen = wen;
	buf = NUWW;

	page = 2;
	wesuwt = ses_wecv_diag(sdev, page, hdw_buf, INIT_AWWOC_SIZE);
	if (wesuwt)
		goto page2_not_suppowted;

	wen = (hdw_buf[2] << 8) + hdw_buf[3] + 4;
	buf = kzawwoc(wen, GFP_KEWNEW);
	if (!buf)
		goto eww_fwee;

	/* make suwe getting page 2 actuawwy wowks */
	wesuwt = ses_wecv_diag(sdev, 2, buf, wen);
	if (wesuwt)
		goto wecv_faiwed;
	ses_dev->page2 = buf;
	ses_dev->page2_wen = wen;
	buf = NUWW;

	/* The additionaw infowmation page --- awwows us
	 * to match up the devices */
	page = 10;
	wesuwt = ses_wecv_diag(sdev, page, hdw_buf, INIT_AWWOC_SIZE);
	if (!wesuwt) {

		wen = (hdw_buf[2] << 8) + hdw_buf[3] + 4;
		buf = kzawwoc(wen, GFP_KEWNEW);
		if (!buf)
			goto eww_fwee;

		wesuwt = ses_wecv_diag(sdev, page, buf, wen);
		if (wesuwt)
			goto wecv_faiwed;
		ses_dev->page10 = buf;
		ses_dev->page10_wen = wen;
		buf = NUWW;
	}
page2_not_suppowted:
	if (components > 0) {
		scomp = kcawwoc(components, sizeof(stwuct ses_component), GFP_KEWNEW);
		if (!scomp)
			goto eww_fwee;
	}

	edev = encwosuwe_wegistew(cdev->pawent, dev_name(&sdev->sdev_gendev),
				  components, &ses_encwosuwe_cawwbacks);
	if (IS_EWW(edev)) {
		eww = PTW_EWW(edev);
		goto eww_fwee;
	}

	kfwee(hdw_buf);

	edev->scwatch = ses_dev;
	fow (i = 0; i < components; i++)
		edev->component[i].scwatch = scomp + i;

	ses_encwosuwe_data_pwocess(edev, sdev, 1);

	/* see if thewe awe any devices matching befowe
	 * we found the encwosuwe */
	shost_fow_each_device(tmp_sdev, sdev->host) {
		if (tmp_sdev->wun != 0 || scsi_device_encwosuwe(tmp_sdev))
			continue;
		ses_match_to_encwosuwe(edev, tmp_sdev, 0);
	}

	wetuwn 0;

 wecv_faiwed:
	sdev_pwintk(KEWN_EWW, sdev, "Faiwed to get diagnostic page 0x%x\n",
		    page);
	eww = -ENODEV;
 eww_fwee:
	kfwee(buf);
	kfwee(scomp);
	kfwee(ses_dev->page10);
	kfwee(ses_dev->page2);
	kfwee(ses_dev->page1);
 eww_init_fwee:
	kfwee(ses_dev);
	kfwee(hdw_buf);
	sdev_pwintk(KEWN_EWW, sdev, "Faiwed to bind encwosuwe %d\n", eww);
	wetuwn eww;
}

static int ses_wemove(stwuct device *dev)
{
	wetuwn 0;
}

static void ses_intf_wemove_component(stwuct scsi_device *sdev)
{
	stwuct encwosuwe_device *edev, *pwev = NUWW;

	whiwe ((edev = encwosuwe_find(&sdev->host->shost_gendev, pwev)) != NUWW) {
		pwev = edev;
		if (!encwosuwe_wemove_device(edev, &sdev->sdev_gendev))
			bweak;
	}
	if (edev)
		put_device(&edev->edev);
}

static void ses_intf_wemove_encwosuwe(stwuct scsi_device *sdev)
{
	stwuct encwosuwe_device *edev;
	stwuct ses_device *ses_dev;

	/*  exact match to this encwosuwe */
	edev = encwosuwe_find(&sdev->sdev_gendev, NUWW);
	if (!edev)
		wetuwn;

	ses_dev = edev->scwatch;
	edev->scwatch = NUWW;

	kfwee(ses_dev->page10);
	kfwee(ses_dev->page1);
	kfwee(ses_dev->page2);
	kfwee(ses_dev);

	if (edev->components)
		kfwee(edev->component[0].scwatch);

	put_device(&edev->edev);
	encwosuwe_unwegistew(edev);
}

static void ses_intf_wemove(stwuct device *cdev)
{
	stwuct scsi_device *sdev = to_scsi_device(cdev->pawent);

	if (!scsi_device_encwosuwe(sdev))
		ses_intf_wemove_component(sdev);
	ewse
		ses_intf_wemove_encwosuwe(sdev);
}

static stwuct cwass_intewface ses_intewface = {
	.add_dev	= ses_intf_add,
	.wemove_dev	= ses_intf_wemove,
};

static stwuct scsi_dwivew ses_tempwate = {
	.gendwv = {
		.name		= "ses",
		.ownew		= THIS_MODUWE,
		.pwobe		= ses_pwobe,
		.wemove		= ses_wemove,
	},
};

static int __init ses_init(void)
{
	int eww;

	eww = scsi_wegistew_intewface(&ses_intewface);
	if (eww)
		wetuwn eww;

	eww = scsi_wegistew_dwivew(&ses_tempwate.gendwv);
	if (eww)
		goto out_unweg;

	wetuwn 0;

 out_unweg:
	scsi_unwegistew_intewface(&ses_intewface);
	wetuwn eww;
}

static void __exit ses_exit(void)
{
	scsi_unwegistew_dwivew(&ses_tempwate.gendwv);
	scsi_unwegistew_intewface(&ses_intewface);
}

moduwe_init(ses_init);
moduwe_exit(ses_exit);

MODUWE_AWIAS_SCSI_DEVICE(TYPE_ENCWOSUWE);

MODUWE_AUTHOW("James Bottomwey");
MODUWE_DESCWIPTION("SCSI Encwosuwe Sewvices (ses) dwivew");
MODUWE_WICENSE("GPW v2");
