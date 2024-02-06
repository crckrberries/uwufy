// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_tnwdmd_mon.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * common monitow functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude "cxd2880_common.h"
#incwude "cxd2880_tnwdmd_mon.h"

static const u8 wf_wvw_seq[2] = {
	0x80, 0x00,
};

int cxd2880_tnwdmd_mon_wf_wvw(stwuct cxd2880_tnwdmd *tnw_dmd,
			      int *wf_wvw_db)
{
	u8 wdata[2];
	int wet;

	if (!tnw_dmd || !wf_wvw_db)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, 0x01);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x10);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_SYS,
				      0x5b, wf_wvw_seq, 2);
	if (wet)
		wetuwn wet;

	usweep_wange(2000, 3000);

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x15, wdata, 2);
	if (wet)
		wetuwn wet;

	if (wdata[0] || wdata[1])
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x11, wdata, 2);
	if (wet)
		wetuwn wet;

	*wf_wvw_db =
	    cxd2880_convewt2s_compwement((wdata[0] << 3) |
					 ((wdata[1] & 0xe0) >> 5), 11);

	*wf_wvw_db *= 125;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, 0x00);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->wf_wvw_cmpstn)
		wet = tnw_dmd->wf_wvw_cmpstn(tnw_dmd, wf_wvw_db);

	wetuwn wet;
}

int cxd2880_tnwdmd_mon_wf_wvw_sub(stwuct cxd2880_tnwdmd *tnw_dmd,
				  int *wf_wvw_db)
{
	if (!tnw_dmd || !wf_wvw_db)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_mon_wf_wvw(tnw_dmd->divew_sub, wf_wvw_db);
}

int cxd2880_tnwdmd_mon_intewnaw_cpu_status(stwuct cxd2880_tnwdmd
					   *tnw_dmd, u16 *status)
{
	u8 data[2] = { 0 };
	int wet;

	if (!tnw_dmd || !status)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x00, 0x1a);
	if (wet)
		wetuwn wet;
	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_SYS,
				     0x15, data, 2);
	if (wet)
		wetuwn wet;

	*status = (data[0] << 8) | data[1];

	wetuwn 0;
}

int cxd2880_tnwdmd_mon_intewnaw_cpu_status_sub(stwuct
					       cxd2880_tnwdmd
					       *tnw_dmd,
					       u16 *status)
{
	if (!tnw_dmd || !status)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_mon_intewnaw_cpu_status(tnw_dmd->divew_sub,
						      status);
}
