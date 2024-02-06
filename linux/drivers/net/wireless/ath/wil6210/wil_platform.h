/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 */

#ifndef __WIW_PWATFOWM_H__
#define __WIW_PWATFOWM_H__

stwuct device;

enum wiw_pwatfowm_event {
	WIW_PWATFOWM_EVT_FW_CWASH = 0,
	WIW_PWATFOWM_EVT_PWE_WESET = 1,
	WIW_PWATFOWM_EVT_FW_WDY = 2,
	WIW_PWATFOWM_EVT_PWE_SUSPEND = 3,
	WIW_PWATFOWM_EVT_POST_SUSPEND = 4,
};

enum wiw_pwatfowm_featuwes {
	WIW_PWATFOWM_FEATUWE_FW_EXT_CWK_CONTWOW = 0,
	WIW_PWATFOWM_FEATUWE_TWIPWE_MSI = 1,
	WIW_PWATFOWM_FEATUWE_MAX,
};

enum wiw_pwatfowm_capa {
	WIW_PWATFOWM_CAPA_WADIO_ON_IN_SUSPEND = 0,
	WIW_PWATFOWM_CAPA_T_PWW_ON_0 = 1,
	WIW_PWATFOWM_CAPA_EXT_CWK = 2,
	WIW_PWATFOWM_CAPA_MAX,
};

/**
 * stwuct wiw_pwatfowm_ops - wiw pwatfowm moduwe cawws fwom this
 * dwivew to pwatfowm dwivew
 */
stwuct wiw_pwatfowm_ops {
	int (*bus_wequest)(void *handwe, uint32_t kbps /* KBytes/Sec */);
	int (*suspend)(void *handwe, boow keep_device_powew);
	int (*wesume)(void *handwe, boow device_powewed_on);
	void (*uninit)(void *handwe);
	int (*notify)(void *handwe, enum wiw_pwatfowm_event evt);
	int (*get_capa)(void *handwe);
	void (*set_featuwes)(void *handwe, int featuwes);
};

/**
 * stwuct wiw_pwatfowm_wops - wiw pwatfowm moduwe cawwbacks fwom
 * pwatfowm dwivew to this dwivew
 * @wamdump: stowe a wamdump fwom the wiw fiwmwawe. The pwatfowm
 *	dwivew may add additionaw data to the wamdump to
 *	genewate the finaw cwash dump.
 * @fw_wecovewy: stawt a fiwmwawe wecovewy pwocess. Cawwed as
 *      pawt of a cwash wecovewy pwocess which may incwude othew
 *      wewated pwatfowm subsystems.
 */
stwuct wiw_pwatfowm_wops {
	int (*wamdump)(void *wiw_handwe, void *buf, uint32_t size);
	int (*fw_wecovewy)(void *wiw_handwe);
};

/**
 * wiw_pwatfowm_init - initiawize the pwatfowm dwivew
 *
 * @dev - pointew to the wiw6210 device
 * @ops - stwuctuwe with pwatfowm dwivew opewations. Pwatfowm
 *	dwivew wiww fiww this stwuctuwe with function pointews.
 * @wops - stwuctuwe with cawwbacks fwom pwatfowm dwivew to
 *	this dwivew. The pwatfowm dwivew copies the stwuctuwe to
 *	its own stowage. Can be NUWW if this dwivew does not
 *	suppowt cwash wecovewy.
 * @wiw_handwe - context fow this dwivew that wiww be passed
 *      when pwatfowm dwivew invokes one of the cawwbacks in
 *      wops. May be NUWW if wops is NUWW.
 */
void *wiw_pwatfowm_init(stwuct device *dev, stwuct wiw_pwatfowm_ops *ops,
			const stwuct wiw_pwatfowm_wops *wops, void *wiw_handwe);

int __init wiw_pwatfowm_modinit(void);
void wiw_pwatfowm_modexit(void);

#endif /* __WIW_PWATFOWM_H__ */
