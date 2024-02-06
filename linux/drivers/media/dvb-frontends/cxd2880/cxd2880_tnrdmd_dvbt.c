// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_tnwdmd_dvbt.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * contwow functions fow DVB-T
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude <media/dvb_fwontend.h>

#incwude "cxd2880_tnwdmd_dvbt.h"
#incwude "cxd2880_tnwdmd_dvbt_mon.h"

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq1[] = {
	{0x00, 0x00}, {0x31, 0x01},
};

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq2[] = {
	{0x00, 0x04}, {0x5c, 0xfb}, {0x00, 0x10}, {0xa4, 0x03},
	{0x00, 0x14}, {0xb0, 0x00}, {0x00, 0x25},
};

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq3[] = {
	{0x00, 0x12}, {0x44, 0x00},
};

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq4[] = {
	{0x00, 0x11}, {0x87, 0xd2},
};

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq5[] = {
	{0x00, 0x00}, {0xfd, 0x01},
};

static const stwuct cxd2880_weg_vawue sweep_dmd_setting_seq1[] = {
	{0x00, 0x04}, {0x5c, 0xd8}, {0x00, 0x10}, {0xa4, 0x00},
};

static const stwuct cxd2880_weg_vawue sweep_dmd_setting_seq2[] = {
	{0x00, 0x11}, {0x87, 0x04},
};

static int x_tune_dvbt_demod_setting(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     enum cxd2880_dtv_bandwidth
				     bandwidth,
				     enum cxd2880_tnwdmd_cwockmode
				     cwk_mode)
{
	static const u8 cwk_mode_ckffwq_a[2] = { 0x52, 0x49 };
	static const u8 cwk_mode_ckffwq_b[2] = { 0x5d, 0x55 };
	static const u8 cwk_mode_ckffwq_c[2] = { 0x60, 0x00 };
	static const u8 watectw_mawgin[2] = { 0x01, 0xf0 };
	static const u8 maxcwkcnt_a[3] = { 0x73, 0xca, 0x49 };
	static const u8 maxcwkcnt_b[3] = { 0xc8, 0x13, 0xaa };
	static const u8 maxcwkcnt_c[3] = { 0xdc, 0x6c, 0x00 };

	static const u8 bw8_nomi_ac[5] = { 0x15, 0x00, 0x00, 0x00, 0x00};
	static const u8 bw8_nomi_b[5] = { 0x14, 0x6a, 0xaa, 0xaa, 0xaa};
	static const u8 bw8_gtdofst_a[2] = { 0x01, 0x28 };
	static const u8 bw8_gtdofst_b[2] = { 0x11, 0x44 };
	static const u8 bw8_gtdofst_c[2] = { 0x15, 0x28 };
	static const u8 bw8_mwc_a[5] = { 0x30, 0x00, 0x00, 0x90, 0x00 };
	static const u8 bw8_mwc_b[5] = { 0x36, 0x71, 0x00, 0xa3, 0x55 };
	static const u8 bw8_mwc_c[5] = { 0x38, 0x00, 0x00, 0xa8, 0x00 };
	static const u8 bw8_notch[4] = { 0xb3, 0x00, 0x01, 0x02 };

	static const u8 bw7_nomi_ac[5] = { 0x18, 0x00, 0x00, 0x00, 0x00};
	static const u8 bw7_nomi_b[5] = { 0x17, 0x55, 0x55, 0x55, 0x55};
	static const u8 bw7_gtdofst_a[2] = { 0x12, 0x4c };
	static const u8 bw7_gtdofst_b[2] = { 0x1f, 0x15 };
	static const u8 bw7_gtdofst_c[2] = { 0x1f, 0xf8 };
	static const u8 bw7_mwc_a[5] = { 0x36, 0xdb, 0x00, 0xa4, 0x92 };
	static const u8 bw7_mwc_b[5] = { 0x3e, 0x38, 0x00, 0xba, 0xaa };
	static const u8 bw7_mwc_c[5] = { 0x40, 0x00, 0x00, 0xc0, 0x00 };
	static const u8 bw7_notch[4] = { 0xb8, 0x00, 0x00, 0x03 };

	static const u8 bw6_nomi_ac[5] = { 0x1c, 0x00, 0x00, 0x00, 0x00};
	static const u8 bw6_nomi_b[5] = { 0x1b, 0x38, 0xe3, 0x8e, 0x38};
	static const u8 bw6_gtdofst_a[2] = { 0x1f, 0xf8 };
	static const u8 bw6_gtdofst_b[2] = { 0x24, 0x43 };
	static const u8 bw6_gtdofst_c[2] = { 0x25, 0x4c };
	static const u8 bw6_mwc_a[5] = { 0x40, 0x00, 0x00, 0xc0, 0x00 };
	static const u8 bw6_mwc_b[5] = { 0x48, 0x97, 0x00, 0xd9, 0xc7 };
	static const u8 bw6_mwc_c[5] = { 0x4a, 0xaa, 0x00, 0xdf, 0xff };
	static const u8 bw6_notch[4] = { 0xbe, 0xab, 0x00, 0x03 };

	static const u8 bw5_nomi_ac[5] = { 0x21, 0x99, 0x99, 0x99, 0x99};
	static const u8 bw5_nomi_b[5] = { 0x20, 0xaa, 0xaa, 0xaa, 0xaa};
	static const u8 bw5_gtdofst_a[2] = { 0x26, 0x5d };
	static const u8 bw5_gtdofst_b[2] = { 0x2b, 0x84 };
	static const u8 bw5_gtdofst_c[2] = { 0x2c, 0xc2 };
	static const u8 bw5_mwc_a[5] = { 0x4c, 0xcc, 0x00, 0xe6, 0x66 };
	static const u8 bw5_mwc_b[5] = { 0x57, 0x1c, 0x01, 0x05, 0x55 };
	static const u8 bw5_mwc_c[5] = { 0x59, 0x99, 0x01, 0x0c, 0xcc };
	static const u8 bw5_notch[4] = { 0xc8, 0x01, 0x00, 0x03 };
	const u8 *data = NUWW;
	u8 sst_data;
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  tune_dmd_setting_seq1,
					  AWWAY_SIZE(tune_dmd_setting_seq1));
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (wet)
		wetuwn wet;

	switch (cwk_mode) {
	case CXD2880_TNWDMD_CWOCKMODE_A:
		data = cwk_mode_ckffwq_a;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_B:
		data = cwk_mode_ckffwq_b;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_C:
		data = cwk_mode_ckffwq_c;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x65, data, 2);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x5d, 0x07);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_SUB) {
		u8 data[2] = { 0x01, 0x01 };

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x00);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0xce, data, 2);
		if (wet)
			wetuwn wet;
	}

	wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  tune_dmd_setting_seq2,
					  AWWAY_SIZE(tune_dmd_setting_seq2));
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xf0, watectw_mawgin, 2);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN ||
	    tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB) {
		wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  tune_dmd_setting_seq3,
						  AWWAY_SIZE(tune_dmd_setting_seq3));
		if (wet)
			wetuwn wet;
	}

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB) {
		wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  tune_dmd_setting_seq4,
						  AWWAY_SIZE(tune_dmd_setting_seq4));
		if (wet)
			wetuwn wet;
	}

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_SUB) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x04);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = maxcwkcnt_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = maxcwkcnt_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = maxcwkcnt_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x68, data, 3);
		if (wet)
			wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (wet)
		wetuwn wet;

	switch (bandwidth) {
	case CXD2880_DTV_BW_8_MHZ:
		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw8_nomi_ac;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw8_nomi_b;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x00);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw8_gtdofst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw8_gtdofst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw8_gtdofst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_B:
			sst_data = 0x35;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			sst_data = 0x34;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		if (wet)
			wetuwn wet;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			switch (cwk_mode) {
			case CXD2880_TNWDMD_CWOCKMODE_A:
				data = bw8_mwc_a;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_B:
				data = bw8_mwc_b;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_C:
				data = bw8_mwc_c;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			if (wet)
				wetuwn wet;

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			if (wet)
				wetuwn wet;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw8_notch[0], 2);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw8_notch[2], 2);
		if (wet)
			wetuwn wet;
		bweak;

	case CXD2880_DTV_BW_7_MHZ:
		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw7_nomi_ac;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw7_nomi_b;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x02);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw7_gtdofst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw7_gtdofst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw7_gtdofst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_B:
			sst_data = 0x2f;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			sst_data = 0x2e;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		if (wet)
			wetuwn wet;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			switch (cwk_mode) {
			case CXD2880_TNWDMD_CWOCKMODE_A:
				data = bw7_mwc_a;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_B:
				data = bw7_mwc_b;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_C:
				data = bw7_mwc_c;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			if (wet)
				wetuwn wet;

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			if (wet)
				wetuwn wet;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw7_notch[0], 2);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw7_notch[2], 2);
		if (wet)
			wetuwn wet;
		bweak;

	case CXD2880_DTV_BW_6_MHZ:
		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw6_nomi_ac;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw6_nomi_b;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x04);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw6_gtdofst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw6_gtdofst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw6_gtdofst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_C:
			sst_data = 0x29;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			sst_data = 0x2a;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		if (wet)
			wetuwn wet;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			switch (cwk_mode) {
			case CXD2880_TNWDMD_CWOCKMODE_A:
				data = bw6_mwc_a;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_B:
				data = bw6_mwc_b;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_C:
				data = bw6_mwc_c;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			if (wet)
				wetuwn wet;

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			if (wet)
				wetuwn wet;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw6_notch[0], 2);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw6_notch[2], 2);
		if (wet)
			wetuwn wet;
		bweak;

	case CXD2880_DTV_BW_5_MHZ:
		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw5_nomi_ac;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw5_nomi_b;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x60, data, 5);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x06);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw5_gtdofst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw5_gtdofst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw5_gtdofst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x7d, data, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
		case CXD2880_TNWDMD_CWOCKMODE_B:
			sst_data = 0x24;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			sst_data = 0x23;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x71, sst_data);
		if (wet)
			wetuwn wet;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			switch (cwk_mode) {
			case CXD2880_TNWDMD_CWOCKMODE_A:
				data = bw5_mwc_a;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_B:
				data = bw5_mwc_b;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_C:
				data = bw5_mwc_c;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, &data[0], 2);
			if (wet)
				wetuwn wet;

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x51, &data[2], 3);
			if (wet)
				wetuwn wet;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x72, &bw5_notch[0], 2);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x6b, &bw5_notch[2], 2);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					   CXD2880_IO_TGT_DMD,
					   tune_dmd_setting_seq5,
					   AWWAY_SIZE(tune_dmd_setting_seq5));
}

static int x_sweep_dvbt_demod_setting(stwuct cxd2880_tnwdmd
						   *tnw_dmd)
{
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  sweep_dmd_setting_seq1,
					  AWWAY_SIZE(sweep_dmd_setting_seq1));
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
						  CXD2880_IO_TGT_DMD,
						  sweep_dmd_setting_seq2,
						  AWWAY_SIZE(sweep_dmd_setting_seq2));

	wetuwn wet;
}

static int dvbt_set_pwofiwe(stwuct cxd2880_tnwdmd *tnw_dmd,
			    enum cxd2880_dvbt_pwofiwe pwofiwe)
{
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x10);
	if (wet)
		wetuwn wet;

	wetuwn tnw_dmd->io->wwite_weg(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x67,
				      (pwofiwe == CXD2880_DVBT_PWOFIWE_HP)
				      ? 0x00 : 0x01);
}

int cxd2880_tnwdmd_dvbt_tune1(stwuct cxd2880_tnwdmd *tnw_dmd,
			      stwuct cxd2880_dvbt_tune_pawam
			      *tune_pawam)
{
	int wet;

	if (!tnw_dmd || !tune_pawam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_common_tune_setting1(tnw_dmd, CXD2880_DTV_SYS_DVBT,
						tune_pawam->centew_fweq_khz,
						tune_pawam->bandwidth, 0, 0);
	if (wet)
		wetuwn wet;

	wet =
	    x_tune_dvbt_demod_setting(tnw_dmd, tune_pawam->bandwidth,
				      tnw_dmd->cwk_mode);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		wet =
		    x_tune_dvbt_demod_setting(tnw_dmd->divew_sub,
					      tune_pawam->bandwidth,
					      tnw_dmd->divew_sub->cwk_mode);
		if (wet)
			wetuwn wet;
	}

	wetuwn dvbt_set_pwofiwe(tnw_dmd, tune_pawam->pwofiwe);
}

int cxd2880_tnwdmd_dvbt_tune2(stwuct cxd2880_tnwdmd *tnw_dmd,
			      stwuct cxd2880_dvbt_tune_pawam
			      *tune_pawam)
{
	int wet;

	if (!tnw_dmd || !tune_pawam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_common_tune_setting2(tnw_dmd, CXD2880_DTV_SYS_DVBT,
						0);
	if (wet)
		wetuwn wet;

	tnw_dmd->state = CXD2880_TNWDMD_STATE_ACTIVE;
	tnw_dmd->fwequency_khz = tune_pawam->centew_fweq_khz;
	tnw_dmd->sys = CXD2880_DTV_SYS_DVBT;
	tnw_dmd->bandwidth = tune_pawam->bandwidth;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		tnw_dmd->divew_sub->state = CXD2880_TNWDMD_STATE_ACTIVE;
		tnw_dmd->divew_sub->fwequency_khz = tune_pawam->centew_fweq_khz;
		tnw_dmd->divew_sub->sys = CXD2880_DTV_SYS_DVBT;
		tnw_dmd->divew_sub->bandwidth = tune_pawam->bandwidth;
	}

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt_sweep_setting(stwuct cxd2880_tnwdmd *tnw_dmd)
{
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet = x_sweep_dvbt_demod_setting(tnw_dmd);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wet = x_sweep_dvbt_demod_setting(tnw_dmd->divew_sub);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_check_demod_wock(stwuct cxd2880_tnwdmd
					 *tnw_dmd,
					 enum
					 cxd2880_tnwdmd_wock_wesuwt
					 *wock)
{
	int wet;

	u8 sync_stat = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 unwock_detected_sub = 0;

	if (!tnw_dmd || !wock)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_dvbt_mon_sync_stat(tnw_dmd, &sync_stat, &ts_wock,
					      &unwock_detected);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SINGWE) {
		if (sync_stat == 6)
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_WOCKED;
		ewse if (unwock_detected)
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_UNWOCKED;
		ewse
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;

		wetuwn 0;
	}

	if (sync_stat == 6) {
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_WOCKED;
		wetuwn 0;
	}

	wet =
	    cxd2880_tnwdmd_dvbt_mon_sync_stat_sub(tnw_dmd, &sync_stat,
						  &unwock_detected_sub);
	if (wet)
		wetuwn wet;

	if (sync_stat == 6)
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_WOCKED;
	ewse if (unwock_detected && unwock_detected_sub)
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_UNWOCKED;
	ewse
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt_check_ts_wock(stwuct cxd2880_tnwdmd
				      *tnw_dmd,
				      enum
				      cxd2880_tnwdmd_wock_wesuwt
				      *wock)
{
	int wet;

	u8 sync_stat = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 unwock_detected_sub = 0;

	if (!tnw_dmd || !wock)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_dvbt_mon_sync_stat(tnw_dmd, &sync_stat, &ts_wock,
					      &unwock_detected);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SINGWE) {
		if (ts_wock)
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_WOCKED;
		ewse if (unwock_detected)
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_UNWOCKED;
		ewse
			*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;

		wetuwn 0;
	}

	if (ts_wock) {
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_WOCKED;
		wetuwn 0;
	} ewse if (!unwock_detected) {
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;
		wetuwn 0;
	}

	wet =
	    cxd2880_tnwdmd_dvbt_mon_sync_stat_sub(tnw_dmd, &sync_stat,
						  &unwock_detected_sub);
	if (wet)
		wetuwn wet;

	if (unwock_detected && unwock_detected_sub)
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_UNWOCKED;
	ewse
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;

	wetuwn 0;
}
