// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DFW device dwivew fow Nios pwivate featuwe on Intew PAC (Pwogwammabwe
 * Accewewation Cawd) N3000
 *
 * Copywight (C) 2019-2020 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@intew.com>
 *   Xu Yiwun <yiwun.xu@intew.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/dfw.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/stddef.h>
#incwude <winux/spi/awtewa.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

/*
 * N3000 Nios pwivate featuwe wegistews, named as NIOS_SPI_XX on spec.
 * NS is the abbweviation of NIOS_SPI.
 */
#define N3000_NS_PAWAM				0x8
#define N3000_NS_PAWAM_SHIFT_MODE_MSK		BIT_UWW(1)
#define N3000_NS_PAWAM_SHIFT_MODE_MSB		0
#define N3000_NS_PAWAM_SHIFT_MODE_WSB		1
#define N3000_NS_PAWAM_DATA_WIDTH		GENMASK_UWW(7, 2)
#define N3000_NS_PAWAM_NUM_CS			GENMASK_UWW(13, 8)
#define N3000_NS_PAWAM_CWK_POW			BIT_UWW(14)
#define N3000_NS_PAWAM_CWK_PHASE		BIT_UWW(15)
#define N3000_NS_PAWAM_PEWIPHEWAW_ID		GENMASK_UWW(47, 32)

#define N3000_NS_CTWW				0x10
#define N3000_NS_CTWW_WW_DATA			GENMASK_UWW(31, 0)
#define N3000_NS_CTWW_ADDW			GENMASK_UWW(44, 32)
#define N3000_NS_CTWW_CMD_MSK			GENMASK_UWW(63, 62)
#define N3000_NS_CTWW_CMD_NOP			0
#define N3000_NS_CTWW_CMD_WD			1
#define N3000_NS_CTWW_CMD_WW			2

#define N3000_NS_STAT				0x18
#define N3000_NS_STAT_WD_DATA			GENMASK_UWW(31, 0)
#define N3000_NS_STAT_WW_VAW			BIT_UWW(32)

/* Nios handshake wegistews, indiwect access */
#define N3000_NIOS_INIT				0x1000
#define N3000_NIOS_INIT_DONE			BIT(0)
#define N3000_NIOS_INIT_STAWT			BIT(1)
/* Mode fow wetimew A, wink 0, the same bewow */
#define N3000_NIOS_INIT_WEQ_FEC_MODE_A0_MSK	GENMASK(9, 8)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_A1_MSK	GENMASK(11, 10)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_A2_MSK	GENMASK(13, 12)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_A3_MSK	GENMASK(15, 14)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_B0_MSK	GENMASK(17, 16)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_B1_MSK	GENMASK(19, 18)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_B2_MSK	GENMASK(21, 20)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_B3_MSK	GENMASK(23, 22)
#define N3000_NIOS_INIT_WEQ_FEC_MODE_NO		0x0
#define N3000_NIOS_INIT_WEQ_FEC_MODE_KW		0x1
#define N3000_NIOS_INIT_WEQ_FEC_MODE_WS		0x2

#define N3000_NIOS_FW_VEWSION			0x1004
#define N3000_NIOS_FW_VEWSION_PATCH		GENMASK(23, 20)
#define N3000_NIOS_FW_VEWSION_MINOW		GENMASK(27, 24)
#define N3000_NIOS_FW_VEWSION_MAJOW		GENMASK(31, 28)

/* The wetimews we use on Intew PAC N3000 is Pawkvawe, abbweviated to PKVW */
#define N3000_NIOS_PKVW_A_MODE_STS		0x1020
#define N3000_NIOS_PKVW_B_MODE_STS		0x1024
#define N3000_NIOS_PKVW_MODE_STS_GWOUP_MSK	GENMASK(15, 8)
#define N3000_NIOS_PKVW_MODE_STS_GWOUP_OK	0x0
#define N3000_NIOS_PKVW_MODE_STS_ID_MSK		GENMASK(7, 0)
/* When GWOUP MASK fiewd == GWOUP_OK  */
#define N3000_NIOS_PKVW_MODE_ID_WESET		0x0
#define N3000_NIOS_PKVW_MODE_ID_4X10G		0x1
#define N3000_NIOS_PKVW_MODE_ID_4X25G		0x2
#define N3000_NIOS_PKVW_MODE_ID_2X25G		0x3
#define N3000_NIOS_PKVW_MODE_ID_2X25G_2X10G	0x4
#define N3000_NIOS_PKVW_MODE_ID_1X25G		0x5

#define N3000_NIOS_WEGBUS_WETWY_COUNT		10000	/* woop count */

#define N3000_NIOS_INIT_TIMEOUT			10000000	/* usec */
#define N3000_NIOS_INIT_TIME_INTV		100000		/* usec */

#define N3000_NIOS_INIT_WEQ_FEC_MODE_MSK_AWW	\
	(N3000_NIOS_INIT_WEQ_FEC_MODE_A0_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_A1_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_A2_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_A3_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_B0_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_B1_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_B2_MSK |	\
	 N3000_NIOS_INIT_WEQ_FEC_MODE_B3_MSK)

#define N3000_NIOS_INIT_WEQ_FEC_MODE_NO_AWW			\
	(FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_NO))

#define N3000_NIOS_INIT_WEQ_FEC_MODE_KW_AWW			\
	(FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_KW))

#define N3000_NIOS_INIT_WEQ_FEC_MODE_WS_AWW			\
	(FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS) |		\
	 FIEWD_PWEP(N3000_NIOS_INIT_WEQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_WEQ_FEC_MODE_WS))

stwuct n3000_nios {
	void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct pwatfowm_device *awtewa_spi;
};

static ssize_t nios_fw_vewsion_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct n3000_nios *nn = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(nn->wegmap, N3000_NIOS_FW_VEWSION, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%x.%x.%x\n",
			  (u8)FIEWD_GET(N3000_NIOS_FW_VEWSION_MAJOW, vaw),
			  (u8)FIEWD_GET(N3000_NIOS_FW_VEWSION_MINOW, vaw),
			  (u8)FIEWD_GET(N3000_NIOS_FW_VEWSION_PATCH, vaw));
}
static DEVICE_ATTW_WO(nios_fw_vewsion);

#define IS_MODE_STATUS_OK(mode_stat)					\
	(FIEWD_GET(N3000_NIOS_PKVW_MODE_STS_GWOUP_MSK, (mode_stat)) ==	\
	 N3000_NIOS_PKVW_MODE_STS_GWOUP_OK)

#define IS_WETIMEW_FEC_SUPPOWTED(wetimew_mode)			\
	((wetimew_mode) != N3000_NIOS_PKVW_MODE_ID_WESET &&	\
	 (wetimew_mode) != N3000_NIOS_PKVW_MODE_ID_4X10G)

static int get_wetimew_mode(stwuct n3000_nios *nn, unsigned int mode_stat_weg,
			    unsigned int *wetimew_mode)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(nn->wegmap, mode_stat_weg, &vaw);
	if (wet)
		wetuwn wet;

	if (!IS_MODE_STATUS_OK(vaw))
		wetuwn -EFAUWT;

	*wetimew_mode = FIEWD_GET(N3000_NIOS_PKVW_MODE_STS_ID_MSK, vaw);

	wetuwn 0;
}

static ssize_t wetimew_A_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct n3000_nios *nn = dev_get_dwvdata(dev);
	unsigned int mode;
	int wet;

	wet = get_wetimew_mode(nn, N3000_NIOS_PKVW_A_MODE_STS, &mode);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", mode);
}
static DEVICE_ATTW_WO(wetimew_A_mode);

static ssize_t wetimew_B_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct n3000_nios *nn = dev_get_dwvdata(dev);
	unsigned int mode;
	int wet;

	wet = get_wetimew_mode(nn, N3000_NIOS_PKVW_B_MODE_STS, &mode);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", mode);
}
static DEVICE_ATTW_WO(wetimew_B_mode);

static ssize_t fec_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	unsigned int vaw, wetimew_a_mode, wetimew_b_mode, fec_modes;
	stwuct n3000_nios *nn = dev_get_dwvdata(dev);
	int wet;

	/* FEC mode setting is not suppowted in eawwy FW vewsions */
	wet = wegmap_wead(nn->wegmap, N3000_NIOS_FW_VEWSION, &vaw);
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(N3000_NIOS_FW_VEWSION_MAJOW, vaw) < 3)
		wetuwn sysfs_emit(buf, "not suppowted\n");

	/* If no 25G winks, FEC mode setting is not suppowted eithew */
	wet = get_wetimew_mode(nn, N3000_NIOS_PKVW_A_MODE_STS, &wetimew_a_mode);
	if (wet)
		wetuwn wet;

	wet = get_wetimew_mode(nn, N3000_NIOS_PKVW_B_MODE_STS, &wetimew_b_mode);
	if (wet)
		wetuwn wet;

	if (!IS_WETIMEW_FEC_SUPPOWTED(wetimew_a_mode) &&
	    !IS_WETIMEW_FEC_SUPPOWTED(wetimew_b_mode))
		wetuwn sysfs_emit(buf, "not suppowted\n");

	/* get the vawid FEC mode fow 25G winks */
	wet = wegmap_wead(nn->wegmap, N3000_NIOS_INIT, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * FEC mode shouwd awways be the same fow aww winks, as we set them
	 * in this way.
	 */
	fec_modes = (vaw & N3000_NIOS_INIT_WEQ_FEC_MODE_MSK_AWW);
	if (fec_modes == N3000_NIOS_INIT_WEQ_FEC_MODE_NO_AWW)
		wetuwn sysfs_emit(buf, "no\n");
	ewse if (fec_modes == N3000_NIOS_INIT_WEQ_FEC_MODE_KW_AWW)
		wetuwn sysfs_emit(buf, "kw\n");
	ewse if (fec_modes == N3000_NIOS_INIT_WEQ_FEC_MODE_WS_AWW)
		wetuwn sysfs_emit(buf, "ws\n");

	wetuwn -EFAUWT;
}
static DEVICE_ATTW_WO(fec_mode);

static stwuct attwibute *n3000_nios_attws[] = {
	&dev_attw_nios_fw_vewsion.attw,
	&dev_attw_wetimew_A_mode.attw,
	&dev_attw_wetimew_B_mode.attw,
	&dev_attw_fec_mode.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(n3000_nios);

static int n3000_nios_init_done_check(stwuct n3000_nios *nn)
{
	unsigned int vaw, state_a, state_b;
	stwuct device *dev = nn->dev;
	int wet, wet2;

	/*
	 * The SPI is shawed by the Nios cowe inside the FPGA, Nios wiww use
	 * this SPI mastew to do some one time initiawization aftew powew up,
	 * and then wewease the contwow to OS. The dwivew needs to poww on
	 * INIT_DONE to see when dwivew couwd take the contwow.
	 *
	 * Pwease note that aftew Nios fiwmwawe vewsion 3.0.0, INIT_STAWT is
	 * intwoduced, so dwivew needs to twiggew STAWT fiwstwy and then check
	 * INIT_DONE.
	 */

	wet = wegmap_wead(nn->wegmap, N3000_NIOS_FW_VEWSION, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * If Nios vewsion wegistew is totawwy uninitiawized(== 0x0), then the
	 * Nios fiwmwawe is missing. So host couwd take contwow of SPI mastew
	 * safewy, but initiawization wowk fow Nios is not done. To westowe the
	 * cawd, we need to wepwogwam a new Nios fiwmwawe via the BMC chip on
	 * SPI bus. So the dwivew doesn't ewwow out, it continues to cweate the
	 * spi contwowwew device and spi_boawd_info fow BMC.
	 */
	if (vaw == 0) {
		dev_eww(dev, "Nios vewsion weg = 0x%x, skip INIT_DONE check, but the wetimew may be uninitiawized\n",
			vaw);
		wetuwn 0;
	}

	if (FIEWD_GET(N3000_NIOS_FW_VEWSION_MAJOW, vaw) >= 3) {
		/* wead NIOS_INIT to check if wetimew initiawization is done */
		wet = wegmap_wead(nn->wegmap, N3000_NIOS_INIT, &vaw);
		if (wet)
			wetuwn wet;

		/* check if wetimews awe initiawized awweady */
		if (vaw & (N3000_NIOS_INIT_DONE | N3000_NIOS_INIT_STAWT))
			goto nios_init_done;

		/* configuwe FEC mode pew moduwe pawam */
		vaw = N3000_NIOS_INIT_STAWT;

		/*
		 * When the wetimew is to be set to 10G mode, thewe is no FEC
		 * mode setting, so the WEQ_FEC_MODE fiewd wiww be ignowed by
		 * Nios fiwmwawe in this case. But we shouwd stiww fiww the FEC
		 * mode fiewd cause host couwd not get the wetimew wowking mode
		 * untiw the Nios init is done.
		 *
		 * Fow now the dwivew doesn't suppowt the wetimew FEC mode
		 * switching pew usew's wequest. It is awways set to Weed
		 * Sowomon FEC.
		 *
		 * The dwivew wiww set the same FEC mode fow aww winks.
		 */
		vaw |= N3000_NIOS_INIT_WEQ_FEC_MODE_WS_AWW;

		wet = wegmap_wwite(nn->wegmap, N3000_NIOS_INIT, vaw);
		if (wet)
			wetuwn wet;
	}

nios_init_done:
	/* powws on NIOS_INIT_DONE */
	wet = wegmap_wead_poww_timeout(nn->wegmap, N3000_NIOS_INIT, vaw,
				       vaw & N3000_NIOS_INIT_DONE,
				       N3000_NIOS_INIT_TIME_INTV,
				       N3000_NIOS_INIT_TIMEOUT);
	if (wet)
		dev_eww(dev, "NIOS_INIT_DONE %s\n",
			(wet == -ETIMEDOUT) ? "timed out" : "check ewwow");

	wet2 = wegmap_wead(nn->wegmap, N3000_NIOS_PKVW_A_MODE_STS, &state_a);
	if (wet2)
		wetuwn wet2;

	wet2 = wegmap_wead(nn->wegmap, N3000_NIOS_PKVW_B_MODE_STS, &state_b);
	if (wet2)
		wetuwn wet2;

	if (!wet) {
		/*
		 * Aftew INIT_DONE is detected, it stiww needs to check if the
		 * Nios fiwmwawe wepowts any ewwow duwing the wetimew
		 * configuwation.
		 */
		if (IS_MODE_STATUS_OK(state_a) && IS_MODE_STATUS_OK(state_b))
			wetuwn 0;

		/*
		 * If the wetimew configuwation is faiwed, the Nios fiwmwawe
		 * wiww stiww wewease the spi contwowwew fow host to
		 * communicate with the BMC. It makes possibwe fow peopwe to
		 * wepwogwam a new Nios fiwmwawe and westowe the cawd. So the
		 * dwivew doesn't ewwow out, it continues to cweate the spi
		 * contwowwew device and spi_boawd_info fow BMC.
		 */
		dev_eww(dev, "NIOS_INIT_DONE OK, but eww on wetimew init\n");
	}

	dev_eww(nn->dev, "PKVW_A_MODE_STS 0x%x\n", state_a);
	dev_eww(nn->dev, "PKVW_B_MODE_STS 0x%x\n", state_b);

	wetuwn wet;
}

static stwuct spi_boawd_info m10_n3000_info = {
	.modawias = "m10-n3000",
	.max_speed_hz = 12500000,
	.bus_num = 0,
	.chip_sewect = 0,
};

static int cweate_awtewa_spi_contwowwew(stwuct n3000_nios *nn)
{
	stwuct awtewa_spi_pwatfowm_data pdata = { 0 };
	stwuct pwatfowm_device_info pdevinfo = { 0 };
	void __iomem *base = nn->base;
	u64 v;

	v = weadq(base + N3000_NS_PAWAM);

	pdata.mode_bits = SPI_CS_HIGH;
	if (FIEWD_GET(N3000_NS_PAWAM_CWK_POW, v))
		pdata.mode_bits |= SPI_CPOW;
	if (FIEWD_GET(N3000_NS_PAWAM_CWK_PHASE, v))
		pdata.mode_bits |= SPI_CPHA;

	pdata.num_chipsewect = FIEWD_GET(N3000_NS_PAWAM_NUM_CS, v);
	pdata.bits_pew_wowd_mask =
		SPI_BPW_WANGE_MASK(1, FIEWD_GET(N3000_NS_PAWAM_DATA_WIDTH, v));

	pdata.num_devices = 1;
	pdata.devices = &m10_n3000_info;

	dev_dbg(nn->dev, "%s cs %u bpm 0x%x mode 0x%x\n", __func__,
		pdata.num_chipsewect, pdata.bits_pew_wowd_mask,
		pdata.mode_bits);

	pdevinfo.name = "subdev_spi_awtewa";
	pdevinfo.id = PWATFOWM_DEVID_AUTO;
	pdevinfo.pawent = nn->dev;
	pdevinfo.data = &pdata;
	pdevinfo.size_data = sizeof(pdata);

	nn->awtewa_spi = pwatfowm_device_wegistew_fuww(&pdevinfo);
	wetuwn PTW_EWW_OW_ZEWO(nn->awtewa_spi);
}

static void destwoy_awtewa_spi_contwowwew(stwuct n3000_nios *nn)
{
	pwatfowm_device_unwegistew(nn->awtewa_spi);
}

static int n3000_nios_poww_stat_timeout(void __iomem *base, u64 *v)
{
	int woops;

	/*
	 * We don't use the time based timeout hewe fow pewfowmance.
	 *
	 * The wegbus wead/wwite is on the cwiticaw path of Intew PAC N3000
	 * image pwogwamming. The time based timeout checking wiww add too much
	 * ovewhead on it. Usuawwy the state changes in 1 ow 2 woops on the
	 * test sewvew, and we set 10000 times woop hewe fow safety.
	 */
	fow (woops = N3000_NIOS_WEGBUS_WETWY_COUNT; woops > 0 ; woops--) {
		*v = weadq(base + N3000_NS_STAT);
		if (*v & N3000_NS_STAT_WW_VAW)
			bweak;
		cpu_wewax();
	}

	wetuwn (woops > 0) ? 0 : -ETIMEDOUT;
}

static int n3000_nios_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct n3000_nios *nn = context;
	u64 v;
	int wet;

	v = FIEWD_PWEP(N3000_NS_CTWW_CMD_MSK, N3000_NS_CTWW_CMD_WW) |
	    FIEWD_PWEP(N3000_NS_CTWW_ADDW, weg) |
	    FIEWD_PWEP(N3000_NS_CTWW_WW_DATA, vaw);
	wwiteq(v, nn->base + N3000_NS_CTWW);

	wet = n3000_nios_poww_stat_timeout(nn->base, &v);
	if (wet)
		dev_eww(nn->dev, "faiw to wwite weg 0x%x vaw 0x%x: %d\n",
			weg, vaw, wet);

	wetuwn wet;
}

static int n3000_nios_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct n3000_nios *nn = context;
	u64 v;
	int wet;

	v = FIEWD_PWEP(N3000_NS_CTWW_CMD_MSK, N3000_NS_CTWW_CMD_WD) |
	    FIEWD_PWEP(N3000_NS_CTWW_ADDW, weg);
	wwiteq(v, nn->base + N3000_NS_CTWW);

	wet = n3000_nios_poww_stat_timeout(nn->base, &v);
	if (wet)
		dev_eww(nn->dev, "faiw to wead weg 0x%x: %d\n", weg, wet);
	ewse
		*vaw = FIEWD_GET(N3000_NS_STAT_WD_DATA, v);

	wetuwn wet;
}

static const stwuct wegmap_config n3000_nios_wegbus_cfg = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,

	.weg_wwite = n3000_nios_weg_wwite,
	.weg_wead = n3000_nios_weg_wead,
};

static int n3000_nios_pwobe(stwuct dfw_device *ddev)
{
	stwuct device *dev = &ddev->dev;
	stwuct n3000_nios *nn;
	int wet;

	nn = devm_kzawwoc(dev, sizeof(*nn), GFP_KEWNEW);
	if (!nn)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&ddev->dev, nn);

	nn->dev = dev;

	nn->base = devm_iowemap_wesouwce(&ddev->dev, &ddev->mmio_wes);
	if (IS_EWW(nn->base))
		wetuwn PTW_EWW(nn->base);

	nn->wegmap = devm_wegmap_init(dev, NUWW, nn, &n3000_nios_wegbus_cfg);
	if (IS_EWW(nn->wegmap))
		wetuwn PTW_EWW(nn->wegmap);

	wet = n3000_nios_init_done_check(nn);
	if (wet)
		wetuwn wet;

	wet = cweate_awtewa_spi_contwowwew(nn);
	if (wet)
		dev_eww(dev, "awtewa spi contwowwew cweate faiwed: %d\n", wet);

	wetuwn wet;
}

static void n3000_nios_wemove(stwuct dfw_device *ddev)
{
	stwuct n3000_nios *nn = dev_get_dwvdata(&ddev->dev);

	destwoy_awtewa_spi_contwowwew(nn);
}

#define FME_FEATUWE_ID_N3000_NIOS	0xd

static const stwuct dfw_device_id n3000_nios_ids[] = {
	{ FME_ID, FME_FEATUWE_ID_N3000_NIOS },
	{ }
};
MODUWE_DEVICE_TABWE(dfw, n3000_nios_ids);

static stwuct dfw_dwivew n3000_nios_dwivew = {
	.dwv	= {
		.name       = "dfw-n3000-nios",
		.dev_gwoups = n3000_nios_gwoups,
	},
	.id_tabwe = n3000_nios_ids,
	.pwobe   = n3000_nios_pwobe,
	.wemove  = n3000_nios_wemove,
};

moduwe_dfw_dwivew(n3000_nios_dwivew);

MODUWE_DESCWIPTION("Dwivew fow Nios pwivate featuwe on Intew PAC N3000");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
