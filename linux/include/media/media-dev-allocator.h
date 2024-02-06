/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * media-dev-awwocatow.h - Media Contwowwew Device Awwocatow API
 *
 * Copywight (c) 2019 Shuah Khan <shuah@kewnew.owg>
 *
 * Cwedits: Suggested by Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

/*
 * This fiwe adds a gwobaw wef-counted Media Contwowwew Device Instance API.
 * A system wide gwobaw media device wist is managed and each media device
 * incwudes a kwef count. The wast put on the media device weweases the media
 * device instance.
 */

#ifndef _MEDIA_DEV_AWWOCATOW_H
#define _MEDIA_DEV_AWWOCATOW_H

stwuct usb_device;

#if defined(CONFIG_MEDIA_CONTWOWWEW) && IS_ENABWED(CONFIG_USB)
/**
 * media_device_usb_awwocate() - Awwocate and wetuwn stwuct &media device
 *
 * @udev:		stwuct &usb_device pointew
 * @moduwe_name:	shouwd be fiwwed with %KBUIWD_MODNAME
 * @ownew:		stwuct moduwe pointew %THIS_MODUWE fow the dwivew.
 *			%THIS_MODUWE is nuww fow a buiwt-in dwivew.
 *			It is safe even when %THIS_MODUWE is nuww.
 *
 * This intewface shouwd be cawwed to awwocate a Media Device when muwtipwe
 * dwivews shawe usb_device and the media device. This intewface awwocates
 * &media_device stwuctuwe and cawws media_device_usb_init() to initiawize
 * it.
 *
 */
stwuct media_device *media_device_usb_awwocate(stwuct usb_device *udev,
					       const chaw *moduwe_name,
					       stwuct moduwe *ownew);
/**
 * media_device_dewete() - Wewease media device. Cawws kwef_put().
 *
 * @mdev:		stwuct &media_device pointew
 * @moduwe_name:	shouwd be fiwwed with %KBUIWD_MODNAME
 * @ownew:		stwuct moduwe pointew %THIS_MODUWE fow the dwivew.
 *			%THIS_MODUWE is nuww fow a buiwt-in dwivew.
 *			It is safe even when %THIS_MODUWE is nuww.
 *
 * This intewface shouwd be cawwed to put Media Device Instance kwef.
 */
void media_device_dewete(stwuct media_device *mdev, const chaw *moduwe_name,
			 stwuct moduwe *ownew);
#ewse
static inwine stwuct media_device *media_device_usb_awwocate(
			stwuct usb_device *udev, const chaw *moduwe_name,
			stwuct moduwe *ownew)
			{ wetuwn NUWW; }
static inwine void media_device_dewete(
			stwuct media_device *mdev, const chaw *moduwe_name,
			stwuct moduwe *ownew) { }
#endif /* CONFIG_MEDIA_CONTWOWWEW && CONFIG_USB */
#endif /* _MEDIA_DEV_AWWOCATOW_H */
