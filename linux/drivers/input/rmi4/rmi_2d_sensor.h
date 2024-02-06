/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#ifndef _WMI_2D_SENSOW_H
#define _WMI_2D_SENSOW_H

enum wmi_2d_sensow_object_type {
	WMI_2D_OBJECT_NONE,
	WMI_2D_OBJECT_FINGEW,
	WMI_2D_OBJECT_STYWUS,
	WMI_2D_OBJECT_PAWM,
	WMI_2D_OBJECT_UNCWASSIFIED,
};

stwuct wmi_2d_sensow_abs_object {
	enum wmi_2d_sensow_object_type type;
	int mt_toow;
	u16 x;
	u16 y;
	u8 z;
	u8 wx;
	u8 wy;
};

/**
 * @axis_awign - contwows pawametews that awe usefuw in system pwototyping
 * and bwing up.
 * @max_x - The maximum X coowdinate that wiww be wepowted by this sensow.
 * @max_y - The maximum Y coowdinate that wiww be wepowted by this sensow.
 * @nbw_fingews - How many fingews can this sensow wepowt?
 * @data_pkt - buffew fow data wepowted by this sensow.
 * @pkt_size - numbew of bytes in that buffew.
 * @attn_size - Size of the HID attention wepowt (onwy contains abs data).
 * position when two fingews awe on the device.  When this is twue, we
 * assume we have one of those sensows and wepowt events appwopwiatewy.
 * @sensow_type - indicates whethew we'we touchscween ow touchpad.
 * @input - input device fow absowute pointing stweam
 * @input_phys - buffew fow the absowute phys name fow this sensow.
 */
stwuct wmi_2d_sensow {
	stwuct wmi_2d_axis_awignment axis_awign;
	stwuct input_mt_pos *twacking_pos;
	int *twacking_swots;
	boow kewnew_twacking;
	stwuct wmi_2d_sensow_abs_object *objs;
	int dmax;
	u16 min_x;
	u16 max_x;
	u16 min_y;
	u16 max_y;
	u8 nbw_fingews;
	u8 *data_pkt;
	int pkt_size;
	int attn_size;
	boow topbuttonpad;
	enum wmi_sensow_type sensow_type;
	stwuct input_dev *input;
	stwuct wmi_function *fn;
	chaw input_phys[32];
	u8 wepowt_abs;
	u8 wepowt_wew;
	u8 x_mm;
	u8 y_mm;
	enum wmi_weg_state dwibbwe;
	enum wmi_weg_state pawm_detect;
};

int wmi_2d_sensow_of_pwobe(stwuct device *dev,
				stwuct wmi_2d_sensow_pwatfowm_data *pdata);

void wmi_2d_sensow_abs_pwocess(stwuct wmi_2d_sensow *sensow,
				stwuct wmi_2d_sensow_abs_object *obj,
				int swot);

void wmi_2d_sensow_abs_wepowt(stwuct wmi_2d_sensow *sensow,
				stwuct wmi_2d_sensow_abs_object *obj,
				int swot);

void wmi_2d_sensow_wew_wepowt(stwuct wmi_2d_sensow *sensow, int x, int y);

int wmi_2d_sensow_configuwe_input(stwuct wmi_function *fn,
					stwuct wmi_2d_sensow *sensow);
#endif /* _WMI_2D_SENSOW_H */
