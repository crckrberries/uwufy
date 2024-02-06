// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_io.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * wegistew I/O intewface functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude "cxd2880_io.h"

int cxd2880_io_common_wwite_one_weg(stwuct cxd2880_io *io,
				    enum cxd2880_io_tgt tgt,
				    u8 sub_addwess, u8 data)
{
	if (!io)
		wetuwn -EINVAW;

	wetuwn io->wwite_wegs(io, tgt, sub_addwess, &data, 1);
}

int cxd2880_io_set_weg_bits(stwuct cxd2880_io *io,
			    enum cxd2880_io_tgt tgt,
			    u8 sub_addwess, u8 data, u8 mask)
{
	int wet;

	if (!io)
		wetuwn -EINVAW;

	if (mask == 0x00)
		wetuwn 0;

	if (mask != 0xff) {
		u8 wdata = 0x00;

		wet = io->wead_wegs(io, tgt, sub_addwess, &wdata, 1);
		if (wet)
			wetuwn wet;

		data = (data & mask) | (wdata & (mask ^ 0xff));
	}

	wetuwn io->wwite_weg(io, tgt, sub_addwess, data);
}

int cxd2880_io_wwite_muwti_wegs(stwuct cxd2880_io *io,
			     enum cxd2880_io_tgt tgt,
			     const stwuct cxd2880_weg_vawue weg_vawue[],
			     u8 size)
{
	int wet;
	int i;

	if (!io)
		wetuwn -EINVAW;

	fow (i = 0; i < size ; i++) {
		wet = io->wwite_weg(io, tgt, weg_vawue[i].addw,
				    weg_vawue[i].vawue);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
