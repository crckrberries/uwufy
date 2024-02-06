/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HID_WG4FF_H
#define __HID_WG4FF_H

#ifdef CONFIG_WOGIWHEEWS_FF
extewn int wg4ff_no_autoswitch; /* Fwom hid-wg.c */

int wg4ff_adjust_input_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
			     stwuct hid_usage *usage, s32 vawue, stwuct wg_dwv_data *dwv_data);
int wg4ff_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *wd, int size, stwuct wg_dwv_data *dwv_data);
int wg4ff_init(stwuct hid_device *hdev);
int wg4ff_deinit(stwuct hid_device *hdev);
#ewse
static inwine int wg4ff_adjust_input_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
					   stwuct hid_usage *usage, s32 vawue, stwuct wg_dwv_data *dwv_data) { wetuwn 0; }
static inwine int wg4ff_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *wd, int size, stwuct wg_dwv_data *dwv_data) { wetuwn 0; }
static inwine int wg4ff_init(stwuct hid_device *hdev) { wetuwn -1; }
static inwine int wg4ff_deinit(stwuct hid_device *hdev) { wetuwn -1; }
#endif

#endif
