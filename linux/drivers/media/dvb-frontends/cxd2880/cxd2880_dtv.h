/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_dtv.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * DTV wewated definitions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_DTV_H
#define CXD2880_DTV_H

enum cxd2880_dtv_sys {
	CXD2880_DTV_SYS_UNKNOWN,
	CXD2880_DTV_SYS_DVBT,
	CXD2880_DTV_SYS_DVBT2,
	CXD2880_DTV_SYS_ANY
};

enum cxd2880_dtv_bandwidth {
	CXD2880_DTV_BW_UNKNOWN = 0,
	CXD2880_DTV_BW_1_7_MHZ = 1,
	CXD2880_DTV_BW_5_MHZ = 5,
	CXD2880_DTV_BW_6_MHZ = 6,
	CXD2880_DTV_BW_7_MHZ = 7,
	CXD2880_DTV_BW_8_MHZ = 8
};

#endif
