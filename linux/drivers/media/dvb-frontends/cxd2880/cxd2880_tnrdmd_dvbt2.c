// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_tnwdmd_dvbt2.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * contwow functions fow DVB-T2
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude <media/dvb_fwontend.h>

#incwude "cxd2880_tnwdmd_dvbt2.h"
#incwude "cxd2880_tnwdmd_dvbt2_mon.h"

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq1[] = {
	{0x00, 0x00}, {0x31, 0x02},
};

static const stwuct cxd2880_weg_vawue tune_dmd_setting_seq2[] = {
	{0x00, 0x04}, {0x5d, 0x0b},
};

static int x_tune_dvbt2_demod_setting(stwuct cxd2880_tnwdmd
				      *tnw_dmd,
				      enum cxd2880_dtv_bandwidth
				      bandwidth,
				      enum cxd2880_tnwdmd_cwockmode
				      cwk_mode)
{
	static const u8 tsif_settings[2] = { 0x01, 0x01 };
	static const u8 init_settings[14] = {
		0x07, 0x06, 0x01, 0xf0,	0x00, 0x00, 0x04, 0xb0, 0x00, 0x00,
		0x09, 0x9c, 0x0e, 0x4c
	};
	static const u8 cwk_mode_settings_a1[9] = {
		0x52, 0x49, 0x2c, 0x51,	0x51, 0x3d, 0x15, 0x29, 0x0c
	};

	static const u8 cwk_mode_settings_b1[9] = {
		0x5d, 0x55, 0x32, 0x5c,	0x5c, 0x45, 0x17, 0x2e, 0x0d
	};

	static const u8 cwk_mode_settings_c1[9] = {
		0x60, 0x00, 0x34, 0x5e,	0x5e, 0x47, 0x18, 0x2f, 0x0e
	};

	static const u8 cwk_mode_settings_a2[13] = {
		0x04, 0xe7, 0x94, 0x92,	0x09, 0xcf, 0x7e, 0xd0, 0x49,
		0xcd, 0xcd, 0x1f, 0x5b
	};

	static const u8 cwk_mode_settings_b2[13] = {
		0x05, 0x90, 0x27, 0x55,	0x0b, 0x20, 0x8f, 0xd6, 0xea,
		0xc8, 0xc8, 0x23, 0x91
	};

	static const u8 cwk_mode_settings_c2[13] = {
		0x05, 0xb8, 0xd8, 0x00,	0x0b, 0x72, 0x93, 0xf3, 0x00,
		0xcd, 0xcd, 0x24, 0x95
	};

	static const u8 cwk_mode_settings_a3[5] = {
		0x0b, 0x6a, 0xc9, 0x03, 0x33
	};
	static const u8 cwk_mode_settings_b3[5] = {
		0x01, 0x02, 0xe4, 0x03, 0x39
	};
	static const u8 cwk_mode_settings_c3[5] = {
		0x01, 0x02, 0xeb, 0x03, 0x3b
	};

	static const u8 gtdofst[2] = { 0x3f, 0xff };

	static const u8 bw8_gtdofst_a[2] = { 0x19, 0xd2 };
	static const u8 bw8_nomi_ac[6] = { 0x15, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static const u8 bw8_nomi_b[6] = { 0x14, 0x6a, 0xaa, 0xaa, 0xab, 0x00 };
	static const u8 bw8_sst_a[2] = { 0x06, 0x2a };
	static const u8 bw8_sst_b[2] = { 0x06, 0x29 };
	static const u8 bw8_sst_c[2] = { 0x06, 0x28 };
	static const u8 bw8_mwc_a[9] = {
		0x28, 0x00, 0x50, 0x00, 0x60, 0x00, 0x00, 0x90, 0x00
	};
	static const u8 bw8_mwc_b[9] = {
		0x2d, 0x5e, 0x5a, 0xbd, 0x6c, 0xe3, 0x00, 0xa3, 0x55
	};
	static const u8 bw8_mwc_c[9] = {
		0x2e, 0xaa, 0x5d, 0x55, 0x70, 0x00, 0x00, 0xa8, 0x00
	};

	static const u8 bw7_nomi_ac[6] = { 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static const u8 bw7_nomi_b[6] = { 0x17, 0x55, 0x55, 0x55, 0x55, 0x00 };
	static const u8 bw7_sst_a[2] = { 0x06, 0x23 };
	static const u8 bw7_sst_b[2] = { 0x06, 0x22 };
	static const u8 bw7_sst_c[2] = { 0x06, 0x21 };
	static const u8 bw7_mwc_a[9] = {
		0x2d, 0xb6, 0x5b, 0x6d,	0x6d, 0xb6, 0x00, 0xa4, 0x92
	};
	static const u8 bw7_mwc_b[9] = {
		0x33, 0xda, 0x67, 0xb4,	0x7c, 0x71, 0x00, 0xba, 0xaa
	};
	static const u8 bw7_mwc_c[9] = {
		0x35, 0x55, 0x6a, 0xaa,	0x80, 0x00, 0x00, 0xc0, 0x00
	};

	static const u8 bw6_nomi_ac[6] = { 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static const u8 bw6_nomi_b[6] = { 0x1b, 0x38, 0xe3, 0x8e, 0x39, 0x00 };
	static const u8 bw6_sst_a[2] = { 0x06, 0x1c };
	static const u8 bw6_sst_b[2] = { 0x06, 0x1b };
	static const u8 bw6_sst_c[2] = { 0x06, 0x1a };
	static const u8 bw6_mwc_a[9] = {
		0x35, 0x55, 0x6a, 0xaa, 0x80, 0x00, 0x00, 0xc0, 0x00
	};
	static const u8 bw6_mwc_b[9] = {
		0x3c, 0x7e, 0x78, 0xfc,	0x91, 0x2f, 0x00, 0xd9, 0xc7
	};
	static const u8 bw6_mwc_c[9] = {
		0x3e, 0x38, 0x7c, 0x71,	0x95, 0x55, 0x00, 0xdf, 0xff
	};

	static const u8 bw5_nomi_ac[6] = { 0x21, 0x99, 0x99, 0x99, 0x9a, 0x00 };
	static const u8 bw5_nomi_b[6] = { 0x20, 0xaa, 0xaa, 0xaa, 0xab, 0x00 };
	static const u8 bw5_sst_a[2] = { 0x06, 0x15 };
	static const u8 bw5_sst_b[2] = { 0x06, 0x15 };
	static const u8 bw5_sst_c[2] = { 0x06, 0x14 };
	static const u8 bw5_mwc_a[9] = {
		0x40, 0x00, 0x6a, 0xaa, 0x80, 0x00, 0x00, 0xe6, 0x66
	};
	static const u8 bw5_mwc_b[9] = {
		0x48, 0x97, 0x78, 0xfc, 0x91, 0x2f, 0x01, 0x05, 0x55
	};
	static const u8 bw5_mwc_c[9] = {
		0x4a, 0xaa, 0x7c, 0x71, 0x95, 0x55, 0x01, 0x0c, 0xcc
	};

	static const u8 bw1_7_nomi_a[6] = {
		0x68, 0x0f, 0xa2, 0x32, 0xcf, 0x03
	};
	static const u8 bw1_7_nomi_c[6] = {
		0x68, 0x0f, 0xa2, 0x32, 0xcf, 0x03
	};
	static const u8 bw1_7_nomi_b[6] = {
		0x65, 0x2b, 0xa4, 0xcd, 0xd8, 0x03
	};
	static const u8 bw1_7_sst_a[2] = { 0x06, 0x0c };
	static const u8 bw1_7_sst_b[2] = { 0x06, 0x0c };
	static const u8 bw1_7_sst_c[2] = { 0x06, 0x0b };
	static const u8 bw1_7_mwc_a[9] = {
		0x40, 0x00, 0x6a, 0xaa,	0x80, 0x00, 0x02, 0xc9, 0x8f
	};
	static const u8 bw1_7_mwc_b[9] = {
		0x48, 0x97, 0x78, 0xfc, 0x91, 0x2f, 0x03, 0x29, 0x5d
	};
	static const u8 bw1_7_mwc_c[9] = {
		0x4a, 0xaa, 0x7c, 0x71,	0x95, 0x55, 0x03, 0x40, 0x7d
	};

	const u8 *data = NUWW;
	const u8 *data2 = NUWW;
	const u8 *data3 = NUWW;
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					  CXD2880_IO_TGT_SYS,
					  tune_dmd_setting_seq1,
					  AWWAY_SIZE(tune_dmd_setting_seq1));
	if (wet)
		wetuwn wet;

	wet = cxd2880_io_wwite_muwti_wegs(tnw_dmd->io,
					  CXD2880_IO_TGT_DMD,
					  tune_dmd_setting_seq2,
					  AWWAY_SIZE(tune_dmd_setting_seq2));
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_SUB) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x00);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0xce, tsif_settings, 2);
		if (wet)
			wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x20);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x8a, init_settings[0]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x90, init_settings[1]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x25);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xf0, &init_settings[2], 2);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2a);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xdc, init_settings[4]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xde, init_settings[5]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2d);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x73, &init_settings[6], 4);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x8f, &init_settings[10], 4);
	if (wet)
		wetuwn wet;

	switch (cwk_mode) {
	case CXD2880_TNWDMD_CWOCKMODE_A:
		data = cwk_mode_settings_a1;
		data2 = cwk_mode_settings_a2;
		data3 = cwk_mode_settings_a3;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_B:
		data = cwk_mode_settings_b1;
		data2 = cwk_mode_settings_b2;
		data3 = cwk_mode_settings_b3;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_C:
		data = cwk_mode_settings_c1;
		data2 = cwk_mode_settings_c2;
		data3 = cwk_mode_settings_c3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x1d, &data[0], 3);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x22, data[3]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x24, data[4]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x26, data[5]);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x29, &data[6], 2);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x2d, data[8]);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_SUB) {
		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x2e, &data2[0], 6);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x35, &data2[6], 7);
		if (wet)
			wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x3c, &data3[0], 2);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x56, &data3[2], 3);
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
					      0x10, data, 6);
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
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = gtdofst;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, data, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw8_sst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw8_sst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw8_sst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			if (wet)
				wetuwn wet;
		}
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
					      0x10, data, 6);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x02);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtdofst, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw7_sst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw7_sst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw7_sst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			if (wet)
				wetuwn wet;
		}
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
					      0x10, data, 6);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x04);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtdofst, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw6_sst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw6_sst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw6_sst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			if (wet)
				wetuwn wet;
		}
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
					      0x10, data, 6);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x06);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtdofst, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw5_sst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw5_sst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw5_sst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
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
						      0x4b, data, 9);
			if (wet)
				wetuwn wet;
		}
		bweak;

	case CXD2880_DTV_BW_1_7_MHZ:

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw1_7_nomi_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw1_7_nomi_c;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw1_7_nomi_b;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x10, data, 6);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x4a, 0x03);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x19, gtdofst, 2);
		if (wet)
			wetuwn wet;

		switch (cwk_mode) {
		case CXD2880_TNWDMD_CWOCKMODE_A:
			data = bw1_7_sst_a;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_B:
			data = bw1_7_sst_b;
			bweak;
		case CXD2880_TNWDMD_CWOCKMODE_C:
			data = bw1_7_sst_c;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x1b, data, 2);
		if (wet)
			wetuwn wet;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			switch (cwk_mode) {
			case CXD2880_TNWDMD_CWOCKMODE_A:
				data = bw1_7_mwc_a;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_B:
				data = bw1_7_mwc_b;
				bweak;
			case CXD2880_TNWDMD_CWOCKMODE_C:
				data = bw1_7_mwc_c;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
						      CXD2880_IO_TGT_DMD,
						      0x4b, data, 9);
			if (wet)
				wetuwn wet;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x00);
	if (wet)
		wetuwn wet;

	wetuwn tnw_dmd->io->wwite_weg(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xfd, 0x01);
}

static int x_sweep_dvbt2_demod_setting(stwuct cxd2880_tnwdmd
				       *tnw_dmd)
{
	static const u8 difint_cwip[] = {
		0, 1, 0, 2, 0, 4, 0, 8, 0, 16, 0, 32
	};
	int wet = 0;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x1d);
		if (wet)
			wetuwn wet;

		wet = tnw_dmd->io->wwite_wegs(tnw_dmd->io,
					      CXD2880_IO_TGT_DMD,
					      0x47, difint_cwip, 12);
	}

	wetuwn wet;
}

static int dvbt2_set_pwofiwe(stwuct cxd2880_tnwdmd *tnw_dmd,
			     enum cxd2880_dvbt2_pwofiwe pwofiwe)
{
	u8 t2_mode_tune_mode = 0;
	u8 seq_not2_dtime = 0;
	u8 dtime1 = 0;
	u8 dtime2 = 0;
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	switch (tnw_dmd->cwk_mode) {
	case CXD2880_TNWDMD_CWOCKMODE_A:
		dtime1 = 0x27;
		dtime2 = 0x0c;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_B:
		dtime1 = 0x2c;
		dtime2 = 0x0d;
		bweak;
	case CXD2880_TNWDMD_CWOCKMODE_C:
		dtime1 = 0x2e;
		dtime2 = 0x0e;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (pwofiwe) {
	case CXD2880_DVBT2_PWOFIWE_BASE:
		t2_mode_tune_mode = 0x01;
		seq_not2_dtime = dtime2;
		bweak;

	case CXD2880_DVBT2_PWOFIWE_WITE:
		t2_mode_tune_mode = 0x05;
		seq_not2_dtime = dtime1;
		bweak;

	case CXD2880_DVBT2_PWOFIWE_ANY:
		t2_mode_tune_mode = 0x00;
		seq_not2_dtime = dtime1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x2e);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, t2_mode_tune_mode);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (wet)
		wetuwn wet;

	wetuwn tnw_dmd->io->wwite_weg(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0x2c, seq_not2_dtime);
}

int cxd2880_tnwdmd_dvbt2_tune1(stwuct cxd2880_tnwdmd *tnw_dmd,
			       stwuct cxd2880_dvbt2_tune_pawam
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

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN &&
	    tune_pawam->pwofiwe == CXD2880_DVBT2_PWOFIWE_ANY)
		wetuwn -ENOTTY;

	wet =
	    cxd2880_tnwdmd_common_tune_setting1(tnw_dmd, CXD2880_DTV_SYS_DVBT2,
						tune_pawam->centew_fweq_khz,
						tune_pawam->bandwidth, 0, 0);
	if (wet)
		wetuwn wet;

	wet =
	    x_tune_dvbt2_demod_setting(tnw_dmd, tune_pawam->bandwidth,
				       tnw_dmd->cwk_mode);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		wet =
		    x_tune_dvbt2_demod_setting(tnw_dmd->divew_sub,
					       tune_pawam->bandwidth,
					       tnw_dmd->divew_sub->cwk_mode);
		if (wet)
			wetuwn wet;
	}

	wet = dvbt2_set_pwofiwe(tnw_dmd, tune_pawam->pwofiwe);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		wet =
		    dvbt2_set_pwofiwe(tnw_dmd->divew_sub, tune_pawam->pwofiwe);
		if (wet)
			wetuwn wet;
	}

	if (tune_pawam->data_pwp_id == CXD2880_DVBT2_TUNE_PAWAM_PWPID_AUTO)
		wet = cxd2880_tnwdmd_dvbt2_set_pwp_cfg(tnw_dmd, 1, 0);
	ewse
		wet =
		    cxd2880_tnwdmd_dvbt2_set_pwp_cfg(tnw_dmd, 0,
					     (u8)(tune_pawam->data_pwp_id));

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_tune2(stwuct cxd2880_tnwdmd *tnw_dmd,
			       stwuct cxd2880_dvbt2_tune_pawam
			       *tune_pawam)
{
	u8 en_fef_intmtnt_ctww = 1;
	int wet;

	if (!tnw_dmd || !tune_pawam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	switch (tune_pawam->pwofiwe) {
	case CXD2880_DVBT2_PWOFIWE_BASE:
		en_fef_intmtnt_ctww = tnw_dmd->en_fef_intmtnt_base;
		bweak;
	case CXD2880_DVBT2_PWOFIWE_WITE:
		en_fef_intmtnt_ctww = tnw_dmd->en_fef_intmtnt_wite;
		bweak;
	case CXD2880_DVBT2_PWOFIWE_ANY:
		if (tnw_dmd->en_fef_intmtnt_base &&
		    tnw_dmd->en_fef_intmtnt_wite)
			en_fef_intmtnt_ctww = 1;
		ewse
			en_fef_intmtnt_ctww = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet =
	    cxd2880_tnwdmd_common_tune_setting2(tnw_dmd,
						CXD2880_DTV_SYS_DVBT2,
						en_fef_intmtnt_ctww);
	if (wet)
		wetuwn wet;

	tnw_dmd->state = CXD2880_TNWDMD_STATE_ACTIVE;
	tnw_dmd->fwequency_khz = tune_pawam->centew_fweq_khz;
	tnw_dmd->sys = CXD2880_DTV_SYS_DVBT2;
	tnw_dmd->bandwidth = tune_pawam->bandwidth;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN) {
		tnw_dmd->divew_sub->state = CXD2880_TNWDMD_STATE_ACTIVE;
		tnw_dmd->divew_sub->fwequency_khz = tune_pawam->centew_fweq_khz;
		tnw_dmd->divew_sub->sys = CXD2880_DTV_SYS_DVBT2;
		tnw_dmd->divew_sub->bandwidth = tune_pawam->bandwidth;
	}

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_sweep_setting(stwuct cxd2880_tnwdmd
				       *tnw_dmd)
{
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet = x_sweep_dvbt2_demod_setting(tnw_dmd);
	if (wet)
		wetuwn wet;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wet = x_sweep_dvbt2_demod_setting(tnw_dmd->divew_sub);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_check_demod_wock(stwuct cxd2880_tnwdmd
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
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_stat, &ts_wock,
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
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub(tnw_dmd, &sync_stat,
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

int cxd2880_tnwdmd_dvbt2_check_ts_wock(stwuct cxd2880_tnwdmd
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
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_stat, &ts_wock,
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
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub(tnw_dmd, &sync_stat,
						   &unwock_detected_sub);
	if (wet)
		wetuwn wet;

	if (unwock_detected && unwock_detected_sub)
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_UNWOCKED;
	ewse
		*wock = CXD2880_TNWDMD_WOCK_WESUWT_NOTDETECT;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_set_pwp_cfg(stwuct cxd2880_tnwdmd
				     *tnw_dmd, u8 auto_pwp,
				     u8 pwp_id)
{
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x23);
	if (wet)
		wetuwn wet;

	if (!auto_pwp) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xaf, pwp_id);
		if (wet)
			wetuwn wet;
	}

	wetuwn tnw_dmd->io->wwite_weg(tnw_dmd->io,
				      CXD2880_IO_TGT_DMD,
				      0xad, auto_pwp ? 0x00 : 0x01);
}

int cxd2880_tnwdmd_dvbt2_divew_fef_setting(stwuct cxd2880_tnwdmd
					   *tnw_dmd)
{
	stwuct cxd2880_dvbt2_ofdm ofdm;
	static const u8 data[] = { 0, 8, 0, 16, 0, 32, 0, 64, 0, 128, 1, 0};
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SINGWE)
		wetuwn 0;

	wet = cxd2880_tnwdmd_dvbt2_mon_ofdm(tnw_dmd, &ofdm);
	if (wet)
		wetuwn wet;

	if (!ofdm.mixed)
		wetuwn 0;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x1d);
	if (wet)
		wetuwn wet;

	wetuwn tnw_dmd->io->wwite_wegs(tnw_dmd->io,
				       CXD2880_IO_TGT_DMD,
				       0x47, data, 12);
}

int cxd2880_tnwdmd_dvbt2_check_w1post_vawid(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    u8 *w1_post_vawid)
{
	int wet;

	u8 data;

	if (!tnw_dmd || !w1_post_vawid)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &data, 1);
	if (wet)
		wetuwn wet;

	*w1_post_vawid = data & 0x01;

	wetuwn wet;
}
