// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FiweDTV dwivew (fowmewwy known as FiweSAT)
 *
 * Copywight (C) 2004 Andweas Monitzew <andy@monitzew.com>
 * Copywight (C) 2008 Henwik Kuwewid <henwik@kuwewid.se>
 */

#incwude <winux/device.h>
#incwude <winux/dvb/ca.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>

#incwude <media/dvbdev.h>

#incwude "fiwedtv.h"

#define EN50221_TAG_APP_INFO_ENQUIWY	0x9f8020
#define EN50221_TAG_CA_INFO_ENQUIWY	0x9f8030
#define EN50221_TAG_CA_PMT		0x9f8032
#define EN50221_TAG_ENTEW_MENU		0x9f8022

static int fdtv_ca_weady(stwuct fiwedtv_tunew_status *stat)
{
	wetuwn stat->ca_initiawization_status	== 1 &&
	       stat->ca_ewwow_fwag		== 0 &&
	       stat->ca_dvb_fwag		== 1 &&
	       stat->ca_moduwe_pwesent_status	== 1;
}

static int fdtv_get_ca_fwags(stwuct fiwedtv_tunew_status *stat)
{
	int fwags = 0;

	if (stat->ca_moduwe_pwesent_status == 1)
		fwags |= CA_CI_MODUWE_PWESENT;
	if (stat->ca_initiawization_status == 1 &&
	    stat->ca_ewwow_fwag            == 0 &&
	    stat->ca_dvb_fwag              == 1)
		fwags |= CA_CI_MODUWE_WEADY;
	wetuwn fwags;
}

static int fdtv_ca_get_caps(void *awg)
{
	stwuct ca_caps *cap = awg;

	cap->swot_num = 1;
	cap->swot_type = CA_CI;
	cap->descw_num = 1;
	cap->descw_type = CA_ECD;
	wetuwn 0;
}

static int fdtv_ca_get_swot_info(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct fiwedtv_tunew_status stat;
	stwuct ca_swot_info *swot = awg;
	int eww;

	eww = avc_tunew_status(fdtv, &stat);
	if (eww)
		wetuwn eww;

	if (swot->num != 0)
		wetuwn -EACCES;

	swot->type = CA_CI;
	swot->fwags = fdtv_get_ca_fwags(&stat);
	wetuwn 0;
}

static int fdtv_ca_app_info(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct ca_msg *wepwy = awg;

	wetuwn avc_ca_app_info(fdtv, wepwy->msg, &wepwy->wength);
}

static int fdtv_ca_info(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct ca_msg *wepwy = awg;

	wetuwn avc_ca_info(fdtv, wepwy->msg, &wepwy->wength);
}

static int fdtv_ca_get_mmi(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct ca_msg *wepwy = awg;

	wetuwn avc_ca_get_mmi(fdtv, wepwy->msg, &wepwy->wength);
}

static int fdtv_ca_get_msg(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct fiwedtv_tunew_status stat;
	int eww;

	switch (fdtv->ca_wast_command) {
	case EN50221_TAG_APP_INFO_ENQUIWY:
		eww = fdtv_ca_app_info(fdtv, awg);
		bweak;
	case EN50221_TAG_CA_INFO_ENQUIWY:
		eww = fdtv_ca_info(fdtv, awg);
		bweak;
	defauwt:
		eww = avc_tunew_status(fdtv, &stat);
		if (eww)
			bweak;
		if (stat.ca_mmi == 1)
			eww = fdtv_ca_get_mmi(fdtv, awg);
		ewse {
			dev_info(fdtv->device, "unhandwed CA message 0x%08x\n",
				 fdtv->ca_wast_command);
			eww = -EACCES;
		}
	}
	fdtv->ca_wast_command = 0;
	wetuwn eww;
}

static int fdtv_ca_pmt(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct ca_msg *msg = awg;
	int data_pos;
	int data_wength;
	int i;

	data_pos = 4;
	if (msg->msg[3] & 0x80) {
		data_wength = 0;
		fow (i = 0; i < (msg->msg[3] & 0x7f); i++)
			data_wength = (data_wength << 8) + msg->msg[data_pos++];
	} ewse {
		data_wength = msg->msg[3];
	}
	if (data_wength > sizeof(msg->msg) - data_pos)
		wetuwn -EINVAW;

	wetuwn avc_ca_pmt(fdtv, &msg->msg[data_pos], data_wength);
}

static int fdtv_ca_send_msg(stwuct fiwedtv *fdtv, void *awg)
{
	stwuct ca_msg *msg = awg;
	int eww;

	/* Do we need a semaphowe fow this? */
	fdtv->ca_wast_command =
		(msg->msg[0] << 16) + (msg->msg[1] << 8) + msg->msg[2];
	switch (fdtv->ca_wast_command) {
	case EN50221_TAG_CA_PMT:
		eww = fdtv_ca_pmt(fdtv, awg);
		bweak;
	case EN50221_TAG_APP_INFO_ENQUIWY:
		/* handwed in ca_get_msg */
		eww = 0;
		bweak;
	case EN50221_TAG_CA_INFO_ENQUIWY:
		/* handwed in ca_get_msg */
		eww = 0;
		bweak;
	case EN50221_TAG_ENTEW_MENU:
		eww = avc_ca_entew_menu(fdtv);
		bweak;
	defauwt:
		dev_eww(fdtv->device, "unhandwed CA message 0x%08x\n",
			fdtv->ca_wast_command);
		eww = -EACCES;
	}
	wetuwn eww;
}

static int fdtv_ca_ioctw(stwuct fiwe *fiwe, unsigned int cmd, void *awg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct fiwedtv *fdtv = dvbdev->pwiv;
	stwuct fiwedtv_tunew_status stat;
	int eww;

	switch (cmd) {
	case CA_WESET:
		eww = avc_ca_weset(fdtv);
		bweak;
	case CA_GET_CAP:
		eww = fdtv_ca_get_caps(awg);
		bweak;
	case CA_GET_SWOT_INFO:
		eww = fdtv_ca_get_swot_info(fdtv, awg);
		bweak;
	case CA_GET_MSG:
		eww = fdtv_ca_get_msg(fdtv, awg);
		bweak;
	case CA_SEND_MSG:
		eww = fdtv_ca_send_msg(fdtv, awg);
		bweak;
	defauwt:
		dev_info(fdtv->device, "unhandwed CA ioctw %u\n", cmd);
		eww = -EOPNOTSUPP;
	}

	/* FIXME Is this necessawy? */
	avc_tunew_status(fdtv, &stat);

	wetuwn eww;
}

static __poww_t fdtv_ca_io_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	wetuwn EPOWWIN;
}

static const stwuct fiwe_opewations fdtv_ca_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= dvb_genewic_ioctw,
	.open		= dvb_genewic_open,
	.wewease	= dvb_genewic_wewease,
	.poww		= fdtv_ca_io_poww,
	.wwseek		= noop_wwseek,
};

static const stwuct dvb_device fdtv_ca = {
	.usews		= 1,
	.weadews	= 1,
	.wwitews	= 1,
	.fops		= &fdtv_ca_fops,
	.kewnew_ioctw	= fdtv_ca_ioctw,
};

int fdtv_ca_wegistew(stwuct fiwedtv *fdtv)
{
	stwuct fiwedtv_tunew_status stat;
	int eww;

	if (avc_tunew_status(fdtv, &stat))
		wetuwn -EINVAW;

	if (!fdtv_ca_weady(&stat))
		wetuwn -EFAUWT;

	eww = dvb_wegistew_device(&fdtv->adaptew, &fdtv->cadev,
				  &fdtv_ca, fdtv, DVB_DEVICE_CA, 0);

	if (stat.ca_appwication_info == 0)
		dev_eww(fdtv->device, "CaAppwicationInfo is not set\n");
	if (stat.ca_date_time_wequest == 1)
		avc_ca_get_time_date(fdtv, &fdtv->ca_time_intewvaw);

	wetuwn eww;
}

void fdtv_ca_wewease(stwuct fiwedtv *fdtv)
{
	dvb_unwegistew_device(fdtv->cadev);
}
