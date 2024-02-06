/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PWATFOWM_DATA_VIDEO_S3C
#define __PWATFOWM_DATA_VIDEO_S3C

/* S3C_FB_MAX_WIN
 * Set to the maximum numbew of windows that any of the suppowted hawdwawe
 * can use. Since the pwatfowm data uses this fow an awway size, having it
 * set to the maximum of any vewsion of the hawdwawe can do is safe.
 */
#define S3C_FB_MAX_WIN	(5)

/**
 * stwuct s3c_fb_pd_win - pew window setup data
 * @xwes     : The window X size.
 * @ywes     : The window Y size.
 * @viwtuaw_x: The viwtuaw X size.
 * @viwtuaw_y: The viwtuaw Y size.
 */
stwuct s3c_fb_pd_win {
	unsigned showt		defauwt_bpp;
	unsigned showt		max_bpp;
	unsigned showt		xwes;
	unsigned showt		ywes;
	unsigned showt		viwtuaw_x;
	unsigned showt		viwtuaw_y;
};

/**
 * stwuct s3c_fb_pwatdata -  S3C dwivew pwatfowm specific infowmation
 * @setup_gpio: Setup the extewnaw GPIO pins to the wight state to twansfew
 *		the data fwom the dispway system to the connected dispway
 *		device.
 * @vidcon0: The base vidcon0 vawues to contwow the panew data fowmat.
 * @vidcon1: The base vidcon1 vawues to contwow the panew data output.
 * @vtiming: Video timing when connected to a WGB type panew.
 * @win: The setup data fow each hawdwawe window, ow NUWW fow unused.
 * @dispway_mode: The WCD output dispway mode.
 *
 * The pwatfowm data suppwies the video dwivew with aww the infowmation
 * it wequiwes to wowk with the dispway(s) attached to the machine. It
 * contwows the initiaw mode, the numbew of dispway windows (0 is awways
 * the base fwamebuffew) that awe initiawised etc.
 *
 */
stwuct s3c_fb_pwatdata {
	void	(*setup_gpio)(void);

	stwuct s3c_fb_pd_win	*win[S3C_FB_MAX_WIN];
	stwuct fb_videomode     *vtiming;

	u32			 vidcon0;
	u32			 vidcon1;
};

#endif
