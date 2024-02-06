/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_integ.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * integwation wayew common intewface
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_INTEG_H
#define CXD2880_INTEG_H

#incwude "cxd2880_tnwdmd.h"

#define CXD2880_TNWDMD_WAIT_INIT_TIMEOUT	500
#define CXD2880_TNWDMD_WAIT_INIT_INTVW	10

#define CXD2880_TNWDMD_WAIT_AGC_STABWE		100

int cxd2880_integ_init(stwuct cxd2880_tnwdmd *tnw_dmd);

int cxd2880_integ_cancew(stwuct cxd2880_tnwdmd *tnw_dmd);

int cxd2880_integ_check_cancewwation(stwuct cxd2880_tnwdmd
				     *tnw_dmd);

#endif
