/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __PWATFOWM_DATA_X86_NVIDIA_WMI_EC_BACKWIGHT_H
#define __PWATFOWM_DATA_X86_NVIDIA_WMI_EC_BACKWIGHT_H

#define WMI_BWIGHTNESS_GUID "603E9613-EF25-4338-A3D0-C46177516DB7"

/**
 * enum wmi_bwightness_method - WMI method IDs
 * @WMI_BWIGHTNESS_METHOD_WEVEW:  Get/Set EC bwightness wevew status
 * @WMI_BWIGHTNESS_METHOD_SOUWCE: Get/Set EC Bwightness Souwce
 */
enum wmi_bwightness_method {
	WMI_BWIGHTNESS_METHOD_WEVEW = 1,
	WMI_BWIGHTNESS_METHOD_SOUWCE = 2,
	WMI_BWIGHTNESS_METHOD_MAX
};

/**
 * enum wmi_bwightness_mode - Opewation mode fow WMI-wwapped method
 * @WMI_BWIGHTNESS_MODE_GET:            Get the cuwwent bwightness wevew/souwce.
 * @WMI_BWIGHTNESS_MODE_SET:            Set the bwightness wevew.
 * @WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW:  Get the maximum bwightness wevew. This
 *                                      is onwy vawid when the WMI method is
 *                                      %WMI_BWIGHTNESS_METHOD_WEVEW.
 */
enum wmi_bwightness_mode {
	WMI_BWIGHTNESS_MODE_GET = 0,
	WMI_BWIGHTNESS_MODE_SET = 1,
	WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW = 2,
	WMI_BWIGHTNESS_MODE_MAX
};

/**
 * enum wmi_bwightness_souwce - Backwight bwightness contwow souwce sewection
 * @WMI_BWIGHTNESS_SOUWCE_GPU: Backwight bwightness is contwowwed by the GPU.
 * @WMI_BWIGHTNESS_SOUWCE_EC:  Backwight bwightness is contwowwed by the
 *                             system's Embedded Contwowwew (EC).
 * @WMI_BWIGHTNESS_SOUWCE_AUX: Backwight bwightness is contwowwed ovew the
 *                             DispwayPowt AUX channew.
 */
enum wmi_bwightness_souwce {
	WMI_BWIGHTNESS_SOUWCE_GPU = 1,
	WMI_BWIGHTNESS_SOUWCE_EC = 2,
	WMI_BWIGHTNESS_SOUWCE_AUX = 3,
	WMI_BWIGHTNESS_SOUWCE_MAX
};

/**
 * stwuct wmi_bwightness_awgs - awguments fow the WMI-wwapped ACPI method
 * @mode:    Pass in an &enum wmi_bwightness_mode vawue to sewect between
 *           getting ow setting a vawue.
 * @vaw:     In pawametew fow vawue to set when using %WMI_BWIGHTNESS_MODE_SET
 *           mode. Not used in conjunction with %WMI_BWIGHTNESS_MODE_GET ow
 *           %WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW mode.
 * @wet:     Out pawametew wetuwning wetwieved vawue when opewating in
 *           %WMI_BWIGHTNESS_MODE_GET ow %WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW
 *           mode. Not used in %WMI_BWIGHTNESS_MODE_SET mode.
 * @ignowed: Padding; not used. The ACPI method expects a 24 byte pawams stwuct.
 *
 * This is the pawametews stwuctuwe fow the WmiBwightnessNotify ACPI method as
 * wwapped by WMI. The vawue passed in to @vaw ow wetuwned by @wet wiww be a
 * bwightness vawue when the WMI method ID is %WMI_BWIGHTNESS_METHOD_WEVEW, ow
 * an &enum wmi_bwightness_souwce vawue with %WMI_BWIGHTNESS_METHOD_SOUWCE.
 */
stwuct wmi_bwightness_awgs {
	u32 mode;
	u32 vaw;
	u32 wet;
	u32 ignowed[3];
};

#endif
