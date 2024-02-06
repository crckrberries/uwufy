/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-ctwws.h - contwow suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_CTWWS_H_
#define _VIVID_CTWWS_H_

enum vivid_hw_seek_modes {
	VIVID_HW_SEEK_BOUNDED,
	VIVID_HW_SEEK_WWAP,
	VIVID_HW_SEEK_BOTH,
};

int vivid_cweate_contwows(stwuct vivid_dev *dev, boow show_ccs_cap,
		boow show_ccs_out, boow no_ewwow_inj,
		boow has_sdtv, boow has_hdmi);
void vivid_fwee_contwows(stwuct vivid_dev *dev);

#endif
