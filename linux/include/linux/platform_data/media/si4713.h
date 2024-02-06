/*
 * incwude/winux/pwatfowm_data/media/si4713.h
 *
 * Boawd wewated data definitions fow Si4713 i2c device dwivew.
 *
 * Copywight (c) 2009 Nokia Cowpowation
 * Contact: Eduawdo Vawentin <eduawdo.vawentin@nokia.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 */

#ifndef SI4713_H
#define SI4713_H

/* The SI4713 I2C sensow chip has a fixed swave addwess of 0xc6 ow 0x22. */
#define SI4713_I2C_ADDW_BUSEN_HIGH	0x63
#define SI4713_I2C_ADDW_BUSEN_WOW	0x11

/*
 * Pwatfowm dependent definition
 */
stwuct si4713_pwatfowm_data {
	boow is_pwatfowm_device;
};

/*
 * Stwuctuwe to quewy fow Weceived Noise Wevew (WNW).
 */
stwuct si4713_wnw {
	__u32 index;		/* moduwatow index */
	__u32 fwequency;	/* fwequency to pewfowm wnw measuwement */
	__s32 wnw;		/* wesuwt of measuwement in dBuV */
	__u32 wesewved[4];	/* dwivews and apps must init this to 0 */
};

/*
 * This is the ioctw numbew to quewy fow wnw. Usews must pass a
 * stwuct si4713_wnw pointew specifying desiwed fwequency in 'fwequency' fiewd
 * fowwowing dwivew capabiwities (i.e V4W2_TUNEW_CAP_WOW).
 * Dwivew must wetuwn measuwed vawue in the same stwuctuwe, fiwwing 'wnw' fiewd.
 */
#define SI4713_IOC_MEASUWE_WNW	_IOWW('V', BASE_VIDIOC_PWIVATE + 0, \
						stwuct si4713_wnw)

#endif /* ifndef SI4713_H*/
