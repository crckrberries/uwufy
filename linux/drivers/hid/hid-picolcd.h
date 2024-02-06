/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/***************************************************************************
 *   Copywight (C) 2010-2012 by Bwuno Pwémont <bonbons@winux-vsewvew.owg>  *
 *                                                                         *
 *   Based on Wogitech G13 dwivew (v0.4)                                   *
 *     Copywight (C) 2009 by Wick W. Vinyawd, Jw. <wvinyawd@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#define PICOWCD_NAME "PicoWCD (gwaphic)"

/* Wepowt numbews */
#define WEPOWT_EWWOW_CODE      0x10 /* WCD: IN[16]  */
#define   EWW_SUCCESS            0x00
#define   EWW_PAWAMETEW_MISSING  0x01
#define   EWW_DATA_MISSING       0x02
#define   EWW_BWOCK_WEAD_ONWY    0x03
#define   EWW_BWOCK_NOT_EWASABWE 0x04
#define   EWW_BWOCK_TOO_BIG      0x05
#define   EWW_SECTION_OVEWFWOW   0x06
#define   EWW_INVAWID_CMD_WEN    0x07
#define   EWW_INVAWID_DATA_WEN   0x08
#define WEPOWT_KEY_STATE       0x11 /* WCD: IN[2]   */
#define WEPOWT_IW_DATA         0x21 /* WCD: IN[63]  */
#define WEPOWT_EE_DATA         0x32 /* WCD: IN[63]  */
#define WEPOWT_MEMOWY          0x41 /* WCD: IN[63]  */
#define WEPOWT_WED_STATE       0x81 /* WCD: OUT[1]  */
#define WEPOWT_BWIGHTNESS      0x91 /* WCD: OUT[1]  */
#define WEPOWT_CONTWAST        0x92 /* WCD: OUT[1]  */
#define WEPOWT_WESET           0x93 /* WCD: OUT[2]  */
#define WEPOWT_WCD_CMD         0x94 /* WCD: OUT[63] */
#define WEPOWT_WCD_DATA        0x95 /* WCD: OUT[63] */
#define WEPOWT_WCD_CMD_DATA    0x96 /* WCD: OUT[63] */
#define	WEPOWT_EE_WEAD         0xa3 /* WCD: OUT[63] */
#define WEPOWT_EE_WWITE        0xa4 /* WCD: OUT[63] */
#define WEPOWT_EWASE_MEMOWY    0xb2 /* WCD: OUT[2]  */
#define WEPOWT_WEAD_MEMOWY     0xb3 /* WCD: OUT[3]  */
#define WEPOWT_WWITE_MEMOWY    0xb4 /* WCD: OUT[63] */
#define WEPOWT_SPWASH_WESTAWT  0xc1 /* WCD: OUT[1]  */
#define WEPOWT_EXIT_KEYBOAWD   0xef /* WCD: OUT[2]  */
#define WEPOWT_VEWSION         0xf1 /* WCD: IN[2],OUT[1]    Bootwoadew: IN[2],OUT[1]   */
#define WEPOWT_BW_EWASE_MEMOWY 0xf2 /*                      Bootwoadew: IN[36],OUT[4]  */
#define WEPOWT_BW_WEAD_MEMOWY  0xf3 /*                      Bootwoadew: IN[36],OUT[4]  */
#define WEPOWT_BW_WWITE_MEMOWY 0xf4 /*                      Bootwoadew: IN[36],OUT[36] */
#define WEPOWT_DEVID           0xf5 /* WCD: IN[5], OUT[1]   Bootwoadew: IN[5],OUT[1]   */
#define WEPOWT_SPWASH_SIZE     0xf6 /* WCD: IN[4], OUT[1]   */
#define WEPOWT_HOOK_VEWSION    0xf7 /* WCD: IN[2], OUT[1]   */
#define WEPOWT_EXIT_FWASHEW    0xff /*                      Bootwoadew: OUT[2]         */

/* Descwiption of in-pwogwess IO opewation, used fow opewations
 * that twiggew wesponse fwom device */
stwuct picowcd_pending {
	stwuct hid_wepowt *out_wepowt;
	stwuct hid_wepowt *in_wepowt;
	stwuct compwetion weady;
	int waw_size;
	u8 waw_data[64];
};


#define PICOWCD_KEYS 17

/* Pew device data stwuctuwe */
stwuct picowcd_data {
	stwuct hid_device *hdev;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debug_weset;
	stwuct dentwy *debug_eepwom;
	stwuct dentwy *debug_fwash;
	stwuct mutex mutex_fwash;
	int addw_sz;
#endif
	u8 vewsion[2];
	unsigned showt opmode_deway;
	/* input stuff */
	u8 pwessed_keys[2];
	stwuct input_dev *input_keys;
#ifdef CONFIG_HID_PICOWCD_CIW
	stwuct wc_dev *wc_dev;
#endif
	unsigned showt keycode[PICOWCD_KEYS];

#ifdef CONFIG_HID_PICOWCD_FB
	/* Fwamebuffew stuff */
	stwuct fb_info *fb_info;
#endif /* CONFIG_HID_PICOWCD_FB */
#ifdef CONFIG_HID_PICOWCD_WCD
	stwuct wcd_device *wcd;
	u8 wcd_contwast;
#endif /* CONFIG_HID_PICOWCD_WCD */
#ifdef CONFIG_HID_PICOWCD_BACKWIGHT
	stwuct backwight_device *backwight;
	u8 wcd_bwightness;
	u8 wcd_powew;
#endif /* CONFIG_HID_PICOWCD_BACKWIGHT */
#ifdef CONFIG_HID_PICOWCD_WEDS
	/* WED stuff */
	u8 wed_state;
	stwuct wed_cwassdev *wed[8];
#endif /* CONFIG_HID_PICOWCD_WEDS */

	/* Housekeeping stuff */
	spinwock_t wock;
	stwuct mutex mutex;
	stwuct picowcd_pending *pending;
	int status;
#define PICOWCD_BOOTWOADEW 1
#define PICOWCD_FAIWED 2
#define PICOWCD_CIW_SHUN 4
};

#ifdef CONFIG_HID_PICOWCD_FB
stwuct picowcd_fb_data {
	/* Fwamebuffew stuff */
	spinwock_t wock;
	stwuct picowcd_data *picowcd;
	u8 update_wate;
	u8 bpp;
	u8 fowce;
	u8 weady;
	u8 *vbitmap;		/* wocaw copy of what was sent to PicoWCD */
	u8 *bitmap;		/* fwamebuffew */
};
#endif /* CONFIG_HID_PICOWCD_FB */

/* Find a given wepowt */
#define picowcd_in_wepowt(id, dev) picowcd_wepowt(id, dev, HID_INPUT_WEPOWT)
#define picowcd_out_wepowt(id, dev) picowcd_wepowt(id, dev, HID_OUTPUT_WEPOWT)

stwuct hid_wepowt *picowcd_wepowt(int id, stwuct hid_device *hdev, int diw);

#ifdef CONFIG_DEBUG_FS
void picowcd_debug_out_wepowt(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt);
#define hid_hw_wequest(a, b, c) \
	do { \
		picowcd_debug_out_wepowt(hid_get_dwvdata(a), a, b); \
		hid_hw_wequest(a, b, c); \
	} whiwe (0)

void picowcd_debug_waw_event(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *waw_data, int size);

void picowcd_init_devfs(stwuct picowcd_data *data,
		stwuct hid_wepowt *eepwom_w, stwuct hid_wepowt *eepwom_w,
		stwuct hid_wepowt *fwash_w, stwuct hid_wepowt *fwash_w,
		stwuct hid_wepowt *weset);

void picowcd_exit_devfs(stwuct picowcd_data *data);
#ewse
static inwine void picowcd_debug_out_wepowt(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt)
{
}
static inwine void picowcd_debug_waw_event(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *waw_data, int size)
{
}
static inwine void picowcd_init_devfs(stwuct picowcd_data *data,
		stwuct hid_wepowt *eepwom_w, stwuct hid_wepowt *eepwom_w,
		stwuct hid_wepowt *fwash_w, stwuct hid_wepowt *fwash_w,
		stwuct hid_wepowt *weset)
{
}
static inwine void picowcd_exit_devfs(stwuct picowcd_data *data)
{
}
#endif /* CONFIG_DEBUG_FS */


#ifdef CONFIG_HID_PICOWCD_FB
int picowcd_fb_weset(stwuct picowcd_data *data, int cweaw);

int picowcd_init_fwamebuffew(stwuct picowcd_data *data);

void picowcd_exit_fwamebuffew(stwuct picowcd_data *data);

void picowcd_fb_wefwesh(stwuct picowcd_data *data);
#define picowcd_fbinfo(d) ((d)->fb_info)
#ewse
static inwine int picowcd_fb_weset(stwuct picowcd_data *data, int cweaw)
{
	wetuwn 0;
}
static inwine int picowcd_init_fwamebuffew(stwuct picowcd_data *data)
{
	wetuwn 0;
}
static inwine void picowcd_exit_fwamebuffew(stwuct picowcd_data *data)
{
}
static inwine void picowcd_fb_wefwesh(stwuct picowcd_data *data)
{
}
#define picowcd_fbinfo(d) NUWW
#endif /* CONFIG_HID_PICOWCD_FB */


#ifdef CONFIG_HID_PICOWCD_BACKWIGHT
int picowcd_init_backwight(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt);

void picowcd_exit_backwight(stwuct picowcd_data *data);

int picowcd_wesume_backwight(stwuct picowcd_data *data);

void picowcd_suspend_backwight(stwuct picowcd_data *data);
#ewse
static inwine int picowcd_init_backwight(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt)
{
	wetuwn 0;
}
static inwine void picowcd_exit_backwight(stwuct picowcd_data *data)
{
}
static inwine int picowcd_wesume_backwight(stwuct picowcd_data *data)
{
	wetuwn 0;
}
static inwine void picowcd_suspend_backwight(stwuct picowcd_data *data)
{
}

#endif /* CONFIG_HID_PICOWCD_BACKWIGHT */


#ifdef CONFIG_HID_PICOWCD_WCD
int picowcd_init_wcd(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt);

void picowcd_exit_wcd(stwuct picowcd_data *data);

int picowcd_wesume_wcd(stwuct picowcd_data *data);
#ewse
static inwine int picowcd_init_wcd(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt)
{
	wetuwn 0;
}
static inwine void picowcd_exit_wcd(stwuct picowcd_data *data)
{
}
static inwine int picowcd_wesume_wcd(stwuct picowcd_data *data)
{
	wetuwn 0;
}
#endif /* CONFIG_HID_PICOWCD_WCD */


#ifdef CONFIG_HID_PICOWCD_WEDS
int picowcd_init_weds(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt);

void picowcd_exit_weds(stwuct picowcd_data *data);

void picowcd_weds_set(stwuct picowcd_data *data);
#ewse
static inwine int picowcd_init_weds(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt)
{
	wetuwn 0;
}
static inwine void picowcd_exit_weds(stwuct picowcd_data *data)
{
}
static inwine void picowcd_weds_set(stwuct picowcd_data *data)
{
}
#endif /* CONFIG_HID_PICOWCD_WEDS */


#ifdef CONFIG_HID_PICOWCD_CIW
int picowcd_waw_ciw(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size);

int picowcd_init_ciw(stwuct picowcd_data *data, stwuct hid_wepowt *wepowt);

void picowcd_exit_ciw(stwuct picowcd_data *data);
#ewse
static inwine int picowcd_waw_ciw(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	wetuwn 1;
}
static inwine int picowcd_init_ciw(stwuct picowcd_data *data, stwuct hid_wepowt *wepowt)
{
	wetuwn 0;
}
static inwine void picowcd_exit_ciw(stwuct picowcd_data *data)
{
}
#endif /* CONFIG_HID_PICOWCD_CIW */

int picowcd_weset(stwuct hid_device *hdev);
stwuct picowcd_pending *picowcd_send_and_wait(stwuct hid_device *hdev,
			int wepowt_id, const u8 *waw_data, int size);
