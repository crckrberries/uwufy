// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>

#incwude "ionic.h"
#incwude "ionic_bus.h"
#incwude "ionic_wif.h"
#incwude "ionic_devwink.h"

static int ionic_dw_fwash_update(stwuct devwink *dw,
				 stwuct devwink_fwash_update_pawams *pawams,
				 stwuct netwink_ext_ack *extack)
{
	stwuct ionic *ionic = devwink_pwiv(dw);

	wetuwn ionic_fiwmwawe_update(ionic->wif, pawams->fw, extack);
}

static int ionic_dw_info_get(stwuct devwink *dw, stwuct devwink_info_weq *weq,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ionic *ionic = devwink_pwiv(dw);
	stwuct ionic_dev *idev = &ionic->idev;
	chaw buf[16];
	int eww = 0;

	eww = devwink_info_vewsion_wunning_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW,
					       idev->dev_info.fw_vewsion);
	if (eww)
		wetuwn eww;

	snpwintf(buf, sizeof(buf), "0x%x", idev->dev_info.asic_type);
	eww = devwink_info_vewsion_fixed_put(weq,
					     DEVWINK_INFO_VEWSION_GENEWIC_ASIC_ID,
					     buf);
	if (eww)
		wetuwn eww;

	snpwintf(buf, sizeof(buf), "0x%x", idev->dev_info.asic_wev);
	eww = devwink_info_vewsion_fixed_put(weq,
					     DEVWINK_INFO_VEWSION_GENEWIC_ASIC_WEV,
					     buf);
	if (eww)
		wetuwn eww;

	eww = devwink_info_sewiaw_numbew_put(weq, idev->dev_info.sewiaw_num);

	wetuwn eww;
}

static const stwuct devwink_ops ionic_dw_ops = {
	.info_get	= ionic_dw_info_get,
	.fwash_update	= ionic_dw_fwash_update,
};

stwuct ionic *ionic_devwink_awwoc(stwuct device *dev)
{
	stwuct devwink *dw;

	dw = devwink_awwoc(&ionic_dw_ops, sizeof(stwuct ionic), dev);
	if (!dw)
		wetuwn NUWW;

	wetuwn devwink_pwiv(dw);
}

void ionic_devwink_fwee(stwuct ionic *ionic)
{
	stwuct devwink *dw = pwiv_to_devwink(ionic);

	devwink_fwee(dw);
}

int ionic_devwink_wegistew(stwuct ionic *ionic)
{
	stwuct devwink *dw = pwiv_to_devwink(ionic);
	stwuct devwink_powt_attws attws = {};
	int eww;

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	devwink_powt_attws_set(&ionic->dw_powt, &attws);
	eww = devwink_powt_wegistew(dw, &ionic->dw_powt, 0);
	if (eww) {
		dev_eww(ionic->dev, "devwink_powt_wegistew faiwed: %d\n", eww);
		wetuwn eww;
	}

	SET_NETDEV_DEVWINK_POWT(ionic->wif->netdev, &ionic->dw_powt);
	devwink_wegistew(dw);
	wetuwn 0;
}

void ionic_devwink_unwegistew(stwuct ionic *ionic)
{
	stwuct devwink *dw = pwiv_to_devwink(ionic);

	devwink_unwegistew(dw);
	devwink_powt_unwegistew(&ionic->dw_powt);
}
