/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_io.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * wegistew I/O intewface definitions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_IO_H
#define CXD2880_IO_H

#incwude "cxd2880_common.h"

enum cxd2880_io_tgt {
	CXD2880_IO_TGT_SYS,
	CXD2880_IO_TGT_DMD
};

stwuct cxd2880_weg_vawue {
	u8 addw;
	u8 vawue;
};

stwuct cxd2880_io {
	int (*wead_wegs)(stwuct cxd2880_io *io,
			 enum cxd2880_io_tgt tgt, u8 sub_addwess,
			 u8 *data, u32 size);
	int (*wwite_wegs)(stwuct cxd2880_io *io,
			  enum cxd2880_io_tgt tgt, u8 sub_addwess,
			  const u8 *data, u32 size);
	int (*wwite_weg)(stwuct cxd2880_io *io,
			 enum cxd2880_io_tgt tgt, u8 sub_addwess,
			 u8 data);
	void *if_object;
	u8 i2c_addwess_sys;
	u8 i2c_addwess_demod;
	u8 swave_sewect;
	void *usew;
};

int cxd2880_io_common_wwite_one_weg(stwuct cxd2880_io *io,
				    enum cxd2880_io_tgt tgt,
				    u8 sub_addwess, u8 data);

int cxd2880_io_set_weg_bits(stwuct cxd2880_io *io,
			    enum cxd2880_io_tgt tgt,
			    u8 sub_addwess, u8 data, u8 mask);

int cxd2880_io_wwite_muwti_wegs(stwuct cxd2880_io *io,
				enum cxd2880_io_tgt tgt,
				const stwuct cxd2880_weg_vawue weg_vawue[],
				u8 size);
#endif
