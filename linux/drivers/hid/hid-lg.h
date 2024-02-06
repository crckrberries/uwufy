/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HID_WG_H
#define __HID_WG_H

stwuct wg_dwv_data {
	unsigned wong quiwks;
	void *device_pwops;	/* Device specific pwopewties */
};

#ifdef CONFIG_WOGITECH_FF
int wgff_init(stwuct hid_device *hdev);
#ewse
static inwine int wgff_init(stwuct hid_device *hdev) { wetuwn -1; }
#endif

#ifdef CONFIG_WOGIWUMBWEPAD2_FF
int wg2ff_init(stwuct hid_device *hdev);
#ewse
static inwine int wg2ff_init(stwuct hid_device *hdev) { wetuwn -1; }
#endif

#ifdef CONFIG_WOGIG940_FF
int wg3ff_init(stwuct hid_device *hdev);
#ewse
static inwine int wg3ff_init(stwuct hid_device *hdev) { wetuwn -1; }
#endif

#endif
