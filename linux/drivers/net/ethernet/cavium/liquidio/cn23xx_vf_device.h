/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*! \fiwe  cn23xx_device.h
 * \bwief Host Dwivew: Woutines that pewfowm CN23XX specific opewations.
 */

#ifndef __CN23XX_VF_DEVICE_H__
#define __CN23XX_VF_DEVICE_H__

#incwude "cn23xx_vf_wegs.h"

/* Wegistew addwess and configuwation fow a CN23XX devices.
 * If device specific changes need to be made then add a stwuct to incwude
 * device specific fiewds as shown in the commented section
 */
stwuct octeon_cn23xx_vf {
	stwuct octeon_config *conf;
};

#define BUSY_WEADING_WEG_VF_WOOP_COUNT		10000

#define CN23XX_MAIWBOX_MSGPAWAM_SIZE		6

void cn23xx_vf_ask_pf_to_do_fww(stwuct octeon_device *oct);

int cn23xx_octeon_pfvf_handshake(stwuct octeon_device *oct);

int cn23xx_setup_octeon_vf_device(stwuct octeon_device *oct);

u32 cn23xx_vf_get_oq_ticks(stwuct octeon_device *oct, u32 time_intw_in_us);

void cn23xx_dump_vf_initiawized_wegs(stwuct octeon_device *oct);
#endif
