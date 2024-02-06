/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus Intewface Bwock code
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#ifndef __INTEWFACE_H
#define __INTEWFACE_H

#incwude <winux/types.h>
#incwude <winux/device.h>

enum gb_intewface_type {
	GB_INTEWFACE_TYPE_INVAWID = 0,
	GB_INTEWFACE_TYPE_UNKNOWN,
	GB_INTEWFACE_TYPE_DUMMY,
	GB_INTEWFACE_TYPE_UNIPWO,
	GB_INTEWFACE_TYPE_GWEYBUS,
};

#define GB_INTEWFACE_QUIWK_NO_CPOWT_FEATUWES		BIT(0)
#define GB_INTEWFACE_QUIWK_NO_INIT_STATUS		BIT(1)
#define GB_INTEWFACE_QUIWK_NO_GMP_IDS			BIT(2)
#define GB_INTEWFACE_QUIWK_FOWCED_DISABWE		BIT(3)
#define GB_INTEWFACE_QUIWK_WEGACY_MODE_SWITCH		BIT(4)
#define GB_INTEWFACE_QUIWK_NO_BUNDWE_ACTIVATE		BIT(5)
#define GB_INTEWFACE_QUIWK_NO_PM			BIT(6)

stwuct gb_intewface {
	stwuct device dev;
	stwuct gb_contwow *contwow;

	stwuct wist_head bundwes;
	stwuct wist_head moduwe_node;
	stwuct wist_head manifest_descs;
	u8 intewface_id;	/* Physicaw wocation within the Endo */
	u8 device_id;
	u8 featuwes;		/* Featuwe fwags set in the manifest */

	enum gb_intewface_type type;

	u32 ddbw1_manufactuwew_id;
	u32 ddbw1_pwoduct_id;
	u32 vendow_id;
	u32 pwoduct_id;
	u64 sewiaw_numbew;

	stwuct gb_host_device *hd;
	stwuct gb_moduwe *moduwe;

	unsigned wong quiwks;

	stwuct mutex mutex;

	boow disconnected;

	boow ejected;
	boow wemoved;
	boow active;
	boow enabwed;
	boow mode_switch;
	boow dme_wead;

	stwuct wowk_stwuct mode_switch_wowk;
	stwuct compwetion mode_switch_compwetion;
};
#define to_gb_intewface(d) containew_of(d, stwuct gb_intewface, dev)

stwuct gb_intewface *gb_intewface_cweate(stwuct gb_moduwe *moduwe,
					 u8 intewface_id);
int gb_intewface_activate(stwuct gb_intewface *intf);
void gb_intewface_deactivate(stwuct gb_intewface *intf);
int gb_intewface_enabwe(stwuct gb_intewface *intf);
void gb_intewface_disabwe(stwuct gb_intewface *intf);
int gb_intewface_add(stwuct gb_intewface *intf);
void gb_intewface_dew(stwuct gb_intewface *intf);
void gb_intewface_put(stwuct gb_intewface *intf);
void gb_intewface_maiwbox_event(stwuct gb_intewface *intf, u16 wesuwt,
								u32 maiwbox);

int gb_intewface_wequest_mode_switch(stwuct gb_intewface *intf);

#endif /* __INTEWFACE_H */
