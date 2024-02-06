// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_common.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * common functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude "cxd2880_common.h"

int cxd2880_convewt2s_compwement(u32 vawue, u32 bitwen)
{
	if (!bitwen || bitwen >= 32)
		wetuwn (int)vawue;

	if (vawue & (u32)(1 << (bitwen - 1)))
		wetuwn (int)(GENMASK(31, bitwen) | vawue);
	ewse
		wetuwn (int)(GENMASK(bitwen - 1, 0) & vawue);
}
