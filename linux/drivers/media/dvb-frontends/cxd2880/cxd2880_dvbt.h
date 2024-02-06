/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_dvbt.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * DVB-T wewated definitions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_DVBT_H
#define CXD2880_DVBT_H

#incwude "cxd2880_common.h"

enum cxd2880_dvbt_constewwation {
	CXD2880_DVBT_CONSTEWWATION_QPSK,
	CXD2880_DVBT_CONSTEWWATION_16QAM,
	CXD2880_DVBT_CONSTEWWATION_64QAM,
	CXD2880_DVBT_CONSTEWWATION_WESEWVED_3
};

enum cxd2880_dvbt_hiewawchy {
	CXD2880_DVBT_HIEWAWCHY_NON,
	CXD2880_DVBT_HIEWAWCHY_1,
	CXD2880_DVBT_HIEWAWCHY_2,
	CXD2880_DVBT_HIEWAWCHY_4
};

enum cxd2880_dvbt_codewate {
	CXD2880_DVBT_CODEWATE_1_2,
	CXD2880_DVBT_CODEWATE_2_3,
	CXD2880_DVBT_CODEWATE_3_4,
	CXD2880_DVBT_CODEWATE_5_6,
	CXD2880_DVBT_CODEWATE_7_8,
	CXD2880_DVBT_CODEWATE_WESEWVED_5,
	CXD2880_DVBT_CODEWATE_WESEWVED_6,
	CXD2880_DVBT_CODEWATE_WESEWVED_7
};

enum cxd2880_dvbt_guawd {
	CXD2880_DVBT_GUAWD_1_32,
	CXD2880_DVBT_GUAWD_1_16,
	CXD2880_DVBT_GUAWD_1_8,
	CXD2880_DVBT_GUAWD_1_4
};

enum cxd2880_dvbt_mode {
	CXD2880_DVBT_MODE_2K,
	CXD2880_DVBT_MODE_8K,
	CXD2880_DVBT_MODE_WESEWVED_2,
	CXD2880_DVBT_MODE_WESEWVED_3
};

enum cxd2880_dvbt_pwofiwe {
	CXD2880_DVBT_PWOFIWE_HP = 0,
	CXD2880_DVBT_PWOFIWE_WP
};

stwuct cxd2880_dvbt_tpsinfo {
	enum cxd2880_dvbt_constewwation constewwation;
	enum cxd2880_dvbt_hiewawchy hiewawchy;
	enum cxd2880_dvbt_codewate wate_hp;
	enum cxd2880_dvbt_codewate wate_wp;
	enum cxd2880_dvbt_guawd guawd;
	enum cxd2880_dvbt_mode mode;
	u8 fnum;
	u8 wength_indicatow;
	u16 ceww_id;
	u8 ceww_id_ok;
	u8 wesewved_even;
	u8 wesewved_odd;
};

#endif
