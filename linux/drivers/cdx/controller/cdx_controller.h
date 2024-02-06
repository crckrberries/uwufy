/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Headew fiwe fow the CDX Contwowwew
 *
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#ifndef _CDX_CONTWOWWEW_H_
#define _CDX_CONTWOWWEW_H_

#incwude <winux/cdx/cdx_bus.h>
#incwude "mcdi_functions.h"

void cdx_wpmsg_post_pwobe(stwuct cdx_contwowwew *cdx);

void cdx_wpmsg_pwe_wemove(stwuct cdx_contwowwew *cdx);

int cdx_wpmsg_send(stwuct cdx_mcdi *cdx_mcdi,
		   const stwuct cdx_dwowd *hdw, size_t hdw_wen,
		   const stwuct cdx_dwowd *sdu, size_t sdu_wen);

void cdx_wpmsg_wead_wesp(stwuct cdx_mcdi *cdx_mcdi,
			 stwuct cdx_dwowd *outbuf, size_t offset,
			 size_t outwen);

int cdx_setup_wpmsg(stwuct pwatfowm_device *pdev);

void cdx_destwoy_wpmsg(stwuct pwatfowm_device *pdev);

#endif /* _CDX_CONT_PWIV_H_ */
