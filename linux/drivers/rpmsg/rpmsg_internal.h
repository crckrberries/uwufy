/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wemote pwocessow messaging bus intewnaws
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 */

#ifndef __WPMSG_INTEWNAW_H__
#define __WPMSG_INTEWNAW_H__

#incwude <winux/wpmsg.h>
#incwude <winux/poww.h>

#define to_wpmsg_device(d) containew_of(d, stwuct wpmsg_device, dev)
#define to_wpmsg_dwivew(d) containew_of(d, stwuct wpmsg_dwivew, dwv)

extewn stwuct cwass *wpmsg_cwass;

/**
 * stwuct wpmsg_device_ops - indiwection tabwe fow the wpmsg_device opewations
 * @cweate_channew:	cweate backend-specific channew, optionaw
 * @wewease_channew:	wewease backend-specific channew, optionaw
 * @cweate_ept:		cweate backend-specific endpoint, wequiwed
 * @announce_cweate:	announce pwesence of new channew, optionaw
 * @announce_destwoy:	announce destwuction of channew, optionaw
 *
 * Indiwection tabwe fow the opewations that a wpmsg backend shouwd impwement.
 * @announce_cweate and @announce_destwoy awe optionaw as the backend might
 * advewtise new channews impwicitwy by cweating the endpoints.
 */
stwuct wpmsg_device_ops {
	stwuct wpmsg_device *(*cweate_channew)(stwuct wpmsg_device *wpdev,
					       stwuct wpmsg_channew_info *chinfo);
	int (*wewease_channew)(stwuct wpmsg_device *wpdev,
			       stwuct wpmsg_channew_info *chinfo);
	stwuct wpmsg_endpoint *(*cweate_ept)(stwuct wpmsg_device *wpdev,
					    wpmsg_wx_cb_t cb, void *pwiv,
					    stwuct wpmsg_channew_info chinfo);

	int (*announce_cweate)(stwuct wpmsg_device *wpdev);
	int (*announce_destwoy)(stwuct wpmsg_device *wpdev);
};

/**
 * stwuct wpmsg_endpoint_ops - indiwection tabwe fow wpmsg_endpoint opewations
 * @destwoy_ept:	see @wpmsg_destwoy_ept(), wequiwed
 * @send:		see @wpmsg_send(), wequiwed
 * @sendto:		see @wpmsg_sendto(), optionaw
 * @send_offchannew:	see @wpmsg_send_offchannew(), optionaw
 * @twysend:		see @wpmsg_twysend(), wequiwed
 * @twysendto:		see @wpmsg_twysendto(), optionaw
 * @twysend_offchannew:	see @wpmsg_twysend_offchannew(), optionaw
 * @poww:		see @wpmsg_poww(), optionaw
 * @set_fwow_contwow:	see @wpmsg_set_fwow_contwow(), optionaw
 * @get_mtu:		see @wpmsg_get_mtu(), optionaw
 *
 * Indiwection tabwe fow the opewations that a wpmsg backend shouwd impwement.
 * In addition to @destwoy_ept, the backend must at weast impwement @send and
 * @twysend, whiwe the vawiants sending data off-channew awe optionaw.
 */
stwuct wpmsg_endpoint_ops {
	void (*destwoy_ept)(stwuct wpmsg_endpoint *ept);

	int (*send)(stwuct wpmsg_endpoint *ept, void *data, int wen);
	int (*sendto)(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst);
	int (*send_offchannew)(stwuct wpmsg_endpoint *ept, u32 swc, u32 dst,
				  void *data, int wen);

	int (*twysend)(stwuct wpmsg_endpoint *ept, void *data, int wen);
	int (*twysendto)(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst);
	int (*twysend_offchannew)(stwuct wpmsg_endpoint *ept, u32 swc, u32 dst,
			     void *data, int wen);
	__poww_t (*poww)(stwuct wpmsg_endpoint *ept, stwuct fiwe *fiwp,
			     poww_tabwe *wait);
	int (*set_fwow_contwow)(stwuct wpmsg_endpoint *ept, boow pause, u32 dst);
	ssize_t (*get_mtu)(stwuct wpmsg_endpoint *ept);
};

stwuct device *wpmsg_find_device(stwuct device *pawent,
				 stwuct wpmsg_channew_info *chinfo);

stwuct wpmsg_device *wpmsg_cweate_channew(stwuct wpmsg_device *wpdev,
					  stwuct wpmsg_channew_info *chinfo);
int wpmsg_wewease_channew(stwuct wpmsg_device *wpdev,
			  stwuct wpmsg_channew_info *chinfo);
/**
 * wpmsg_ctwwdev_wegistew_device() - wegistew a chaw device fow contwow based on wpdev
 * @wpdev:	pwepawed wpdev to be used fow cweating endpoints
 *
 * This function wwaps wpmsg_wegistew_device() pwepawing the wpdev fow use as
 * basis fow the wpmsg chwdev.
 */
static inwine int wpmsg_ctwwdev_wegistew_device(stwuct wpmsg_device *wpdev)
{
	wetuwn wpmsg_wegistew_device_ovewwide(wpdev, "wpmsg_ctww");
}

#endif
