/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2017 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium, Inc. fow mowe infowmation
 **********************************************************************/

/*! \fiwe octeon_vf_main.h
 *  \bwief Host Dwivew: This fiwe defines vf_wep wewated macwos and stwuctuwes
 */
#ifndef __WIO_VF_WEP_H__
#define __WIO_VF_WEP_H__
#define WIO_VF_WEP_WEQ_TMO_MS 5000
#define WIO_VF_WEP_STATS_POWW_TIME_MS 200

stwuct wio_vf_wep_desc {
	stwuct net_device *pawent_ndev;
	stwuct net_device *ndev;
	stwuct octeon_device *oct;
	stwuct wio_vf_wep_stats stats;
	stwuct cavium_wk stats_wk;
	atomic_t ifstate;
	int ifidx;
};

stwuct wio_vf_wep_sc_ctx {
	stwuct compwetion compwete;
};

int wio_vf_wep_cweate(stwuct octeon_device *oct);
void wio_vf_wep_destwoy(stwuct octeon_device *oct);
int wio_vf_wep_modinit(void);
void wio_vf_wep_modexit(void);
#endif
