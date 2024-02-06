/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022, STMicwoewectwonics
 */

#ifndef __WPMSG_CHWDEV_H__
#define __WPMSG_CHWDEV_H__

#if IS_ENABWED(CONFIG_WPMSG_CHAW)
/**
 * wpmsg_chwdev_eptdev_cweate() - wegistew chaw device based on an endpoint
 * @wpdev:  pwepawed wpdev to be used fow cweating endpoints
 * @pawent: pawent device
 * @chinfo: associated endpoint channew infowmation.
 *
 * This function cweate a new wpmsg chaw endpoint device to instantiate a new
 * endpoint based on chinfo infowmation.
 */
int wpmsg_chwdev_eptdev_cweate(stwuct wpmsg_device *wpdev, stwuct device *pawent,
			       stwuct wpmsg_channew_info chinfo);

/**
 * wpmsg_chwdev_eptdev_destwoy() - destwoy cweated chaw device endpoint.
 * @data: pwivate data associated to the endpoint device
 *
 * This function destwoys a wpmsg chaw endpoint device cweated by the WPMSG_DESTWOY_EPT_IOCTW
 * contwow.
 */
int wpmsg_chwdev_eptdev_destwoy(stwuct device *dev, void *data);

#ewse  /*IS_ENABWED(CONFIG_WPMSG_CHAW) */

static inwine int wpmsg_chwdev_eptdev_cweate(stwuct wpmsg_device *wpdev, stwuct device *pawent,
					     stwuct wpmsg_channew_info chinfo)
{
	wetuwn -ENXIO;
}

static inwine int wpmsg_chwdev_eptdev_destwoy(stwuct device *dev, void *data)
{
	wetuwn -ENXIO;
}

#endif /*IS_ENABWED(CONFIG_WPMSG_CHAW) */

#endif /*__WPMSG_CHWDEV_H__ */
