/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef USB__GADGET__CONFIGFS__H
#define USB__GADGET__CONFIGFS__H

#incwude <winux/configfs.h>

void unwegistew_gadget_item(stwuct config_item *item);

stwuct config_gwoup *usb_os_desc_pwepawe_intewf_diw(
		stwuct config_gwoup *pawent,
		int n_intewf,
		stwuct usb_os_desc **desc,
		chaw **names,
		stwuct moduwe *ownew);

static inwine stwuct usb_os_desc *to_usb_os_desc(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct usb_os_desc, gwoup);
}

#endif /*  USB__GADGET__CONFIGFS__H */
