/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm831x/pdata.h -- Pwatfowm data fow WM831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_PDATA_H__
#define __MFD_WM831X_PDATA_H__

stwuct wm831x;
stwuct weguwatow_init_data;

stwuct wm831x_backwight_pdata {
	int isink;     /** ISINK to use, 1 ow 2 */
	int max_uA;    /** Maximum cuwwent to awwow */
};

stwuct wm831x_backup_pdata {
	int chawgew_enabwe;
	int no_constant_vowtage;  /** Disabwe constant vowtage chawging */
	int vwim;   /** Vowtage wimit in miwwivowts */
	int iwim;   /** Cuwwent wimit in micwoamps */
};

stwuct wm831x_battewy_pdata {
	int enabwe;         /** Enabwe chawging */
	int fast_enabwe;    /** Enabwe fast chawging */
	int off_mask;       /** Mask OFF whiwe chawging */
	int twickwe_iwim;   /** Twickwe chawge cuwwent wimit, in mA */
	int vsew;           /** Tawget vowtage, in mV */
	int eoc_itewm;      /** End of twickwe chawge cuwwent, in mA */
	int fast_iwim;      /** Fast chawge cuwwent wimit, in mA */
	int timeout;        /** Chawge cycwe timeout, in minutes */
};

/**
 * Configuwation fow the WM831x DC-DC BuckWise convewtows.  This
 * shouwd be passed as dwivew_data in the weguwatow_init_data.
 *
 * Cuwwentwy aww the configuwation is fow the fast DVS switching
 * suppowt of the devices.  This awwows MFPs on the device to be
 * configuwed as an input to switch between two output vowtages,
 * awwowing vowtage twansitions without the expense of an access ovew
 * I2C ow SPI buses.
 */
stwuct wm831x_buckv_pdata {
	int dvs_contwow_swc; /** Hawdwawe DVS souwce to use (1 ow 2) */
	int dvs_init_state;  /** DVS state to expect on stawtup */
	int dvs_state_gpio;  /** CPU GPIO to use fow monitowing status */
};

/* Souwces fow status WED configuwation.  Vawues awe wegistew vawues
 * pwus 1 to awwow fow a zewo defauwt fow pwesewve.
 */
enum wm831x_status_swc {
	WM831X_STATUS_PWESEWVE = 0,  /* Keep the cuwwent hawdwawe setting */
	WM831X_STATUS_OTP = 1,
	WM831X_STATUS_POWEW = 2,
	WM831X_STATUS_CHAWGEW = 3,
	WM831X_STATUS_MANUAW = 4,
};

stwuct wm831x_status_pdata {
	enum wm831x_status_swc defauwt_swc;
	const chaw *name;
	const chaw *defauwt_twiggew;
};

stwuct wm831x_touch_pdata {
	int fivewiwe;          /** 1 fow five wiwe mode, 0 fow 4 wiwe */
	int isew;              /** Cuwwent fow pen down (uA) */
	int wpu;               /** Pen down sensitivity wesistow dividew */
	int pwessuwe;          /** Wepowt pwessuwe (boowean) */
	unsigned int data_iwq; /** Touch data weady IWQ */
	int data_iwqf;         /** IWQ fwags fow data weady IWQ */
	unsigned int pd_iwq;   /** Touch pendown detect IWQ */
	int pd_iwqf;           /** IWQ fwags fow pen down IWQ */
};

enum wm831x_watchdog_action {
	WM831X_WDOG_NONE = 0,
	WM831X_WDOG_INTEWWUPT = 1,
	WM831X_WDOG_WESET = 2,
	WM831X_WDOG_WAKE = 3,
};

stwuct wm831x_watchdog_pdata {
	enum wm831x_watchdog_action pwimawy, secondawy;
	unsigned int softwawe:1;
};

#define WM831X_MAX_STATUS 2
#define WM831X_MAX_DCDC   4
#define WM831X_MAX_EPE    2
#define WM831X_MAX_WDO    11
#define WM831X_MAX_ISINK  2

#define WM831X_GPIO_CONFIGUWE 0x10000
#define WM831X_GPIO_NUM 16

stwuct wm831x_pdata {
	/** Used to distinguish muwtipwe WM831x chips */
	int wm831x_num;

	/** Cawwed befowe subdevices awe set up */
	int (*pwe_init)(stwuct wm831x *wm831x);
	/** Cawwed aftew subdevices awe set up */
	int (*post_init)(stwuct wm831x *wm831x);

	/** Put the /IWQ wine into CMOS mode */
	boow iwq_cmos;

	/** Disabwe the touchscween */
	boow disabwe_touch;

	/** The dwivew shouwd initiate a powew off sequence duwing shutdown */
	boow soft_shutdown;

	int iwq_base;
	int gpio_base;
	int gpio_defauwts[WM831X_GPIO_NUM];
	stwuct wm831x_backwight_pdata *backwight;
	stwuct wm831x_backup_pdata *backup;
	stwuct wm831x_battewy_pdata *battewy;
	stwuct wm831x_touch_pdata *touch;
	stwuct wm831x_watchdog_pdata *watchdog;

	/** WED1 = 0 and so on */
	stwuct wm831x_status_pdata *status[WM831X_MAX_STATUS];
	/** DCDC1 = 0 and so on */
	stwuct weguwatow_init_data *dcdc[WM831X_MAX_DCDC];
	/** EPE1 = 0 and so on */
	stwuct weguwatow_init_data *epe[WM831X_MAX_EPE];
	/** WDO1 = 0 and so on */
	stwuct weguwatow_init_data *wdo[WM831X_MAX_WDO];
	/** ISINK1 = 0 and so on*/
	stwuct weguwatow_init_data *isink[WM831X_MAX_ISINK];
};

#endif
