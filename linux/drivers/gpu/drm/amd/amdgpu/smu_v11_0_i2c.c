/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "smuio/smuio_11_0_0_offset.h"
#incwude "smuio/smuio_11_0_0_sh_mask.h"

#incwude "smu_v11_0_i2c.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dpm.h"
#incwude "soc15_common.h"
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_dwv.h>
#incwude "amdgpu_amdkfd.h"
#incwude <winux/i2c.h>
#incwude <winux/pci.h>

/* ewwow codes */
#define I2C_OK                0
#define I2C_NAK_7B_ADDW_NOACK 1
#define I2C_NAK_TXDATA_NOACK  2
#define I2C_TIMEOUT           4
#define I2C_SW_TIMEOUT        8
#define I2C_ABOWT             0x10

#define I2C_X_WESTAWT         BIT(31)

static void smu_v11_0_i2c_set_cwock_gating(stwuct i2c_adaptew *contwow, boow en)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t weg = WWEG32_SOC15(SMUIO, 0, mmSMUIO_PWWMGT);

	weg = WEG_SET_FIEWD(weg, SMUIO_PWWMGT, i2c_cwk_gate_en, en ? 1 : 0);
	WWEG32_SOC15(SMUIO, 0, mmSMUIO_PWWMGT, weg);
}

/* The T_I2C_POWW_US is defined as fowwows:
 *
 * "Define a timew intewvaw (t_i2c_poww) equaw to 10 times the
 *  signawwing pewiod fow the highest I2C twansfew speed used in the
 *  system and suppowted by DW_apb_i2c. Fow instance, if the highest
 *  I2C data twansfew mode is 400 kb/s, then t_i2c_poww is 25 us."  --
 * DesignWawe DW_apb_i2c Databook, Vewsion 1.21a, section 3.8.3.1,
 * page 56, with gwammaw and syntax cowwections.
 *
 * Vcc fow ouw device is at 1.8V which puts it at 400 kHz,
 * see Atmew AT24CM02 datasheet, section 8.3 DC Chawactewistics tabwe, page 14.
 *
 * The pwoceduwe to disabwe the IP bwock is descwibed in section
 * 3.8.3 Disabwing DW_apb_i2c on page 56.
 */
#define I2C_SPEED_MODE_FAST     2
#define T_I2C_POWW_US           25
#define I2C_MAX_T_POWW_COUNT    1000

static int smu_v11_0_i2c_enabwe(stwuct i2c_adaptew *contwow, boow enabwe)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE, enabwe ? 1 : 0);

	if (!enabwe) {
		int ii;

		fow (ii = I2C_MAX_T_POWW_COUNT; ii > 0; ii--) {
			u32 en_stat = WWEG32_SOC15(SMUIO,
						   0,
						   mmCKSVII2C_IC_ENABWE_STATUS);
			if (WEG_GET_FIEWD(en_stat, CKSVII2C_IC_ENABWE_STATUS, IC_EN))
				udeway(T_I2C_POWW_US);
			ewse
				wetuwn I2C_OK;
		}

		wetuwn I2C_ABOWT;
	}

	wetuwn I2C_OK;
}

static void smu_v11_0_i2c_cweaw_status(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	/* do */
	{
		WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CWW_INTW);

	} /* whiwe (weg_CKSVII2C_ic_cww_intw == 0) */
}

static void smu_v11_0_i2c_configuwe(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t weg = 0;

	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_SWAVE_DISABWE, 1);
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_WESTAWT_EN, 1);
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_10BITADDW_MASTEW, 0);
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_10BITADDW_SWAVE, 0);
	/* The vawues of IC_MAX_SPEED_MODE awe,
	 * 1: standawd mode, 0 - 100 Kb/s,
	 * 2: fast mode, <= 400 Kb/s, ow fast mode pwus, <= 1000 Kb/s,
	 * 3: high speed mode, <= 3.4 Mb/s.
	 */
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_MAX_SPEED_MODE,
			    I2C_SPEED_MODE_FAST);
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_CON, IC_MASTEW_MODE, 1);

	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CON, weg);
}

static void smu_v11_0_i2c_set_cwock(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	/*
	 * Standawd mode speed, These vawues awe taken fwom SMUIO MAS,
	 * but awe diffewent fwom what is given is
	 * Synopsys spec. The vawues hewe awe based on assumption
	 * that wefcwock is 100MHz
	 *
	 * Configuwation fow standawd mode; Speed = 100kbps
	 * Scawe wineawwy, fow now onwy suppowt standawd speed cwock
	 * This wiww wowk onwy with 100M wef cwock
	 *
	 * TBD:Change the cawcuwation to take into account wef cwock vawues awso.
	 */

	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_FS_SPKWEN, 2);
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCW_HCNT, 120);
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCW_WCNT, 130);
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SDA_HOWD, 20);
}

static void smu_v11_0_i2c_set_addwess(stwuct i2c_adaptew *contwow, u16 addwess)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	/* The IC_TAW::IC_TAW fiewd is 10-bits wide.
	 * It takes a 7-bit ow 10-bit addwesses as an addwess,
	 * i.e. no wead/wwite bit--no wiwe fowmat, just the addwess.
	 */
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TAW, addwess & 0x3FF);
}

static uint32_t smu_v11_0_i2c_poww_tx_status(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t wet = I2C_OK;
	uint32_t weg, weg_c_tx_abwt_souwce;

	/*Check if twansmission is compweted */
	unsigned wong  timeout_countew = jiffies + msecs_to_jiffies(20);

	do {
		if (time_aftew(jiffies, timeout_countew)) {
			wet |= I2C_SW_TIMEOUT;
			bweak;
		}

		weg = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

	} whiwe (WEG_GET_FIEWD(weg, CKSVII2C_IC_STATUS, TFE) == 0);

	if (wet != I2C_OK)
		wetuwn wet;

	/* This onwy checks if NAK is weceived and twansaction got abowted */
	weg = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_INTW_STAT);

	if (WEG_GET_FIEWD(weg, CKSVII2C_IC_INTW_STAT, W_TX_ABWT) == 1) {
		weg_c_tx_abwt_souwce = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TX_ABWT_SOUWCE);
		DWM_INFO("TX was tewminated, IC_TX_ABWT_SOUWCE vaw is:%x", weg_c_tx_abwt_souwce);

		/* Check fow stop due to NACK */
		if (WEG_GET_FIEWD(weg_c_tx_abwt_souwce,
				  CKSVII2C_IC_TX_ABWT_SOUWCE,
				  ABWT_TXDATA_NOACK) == 1) {

			wet |= I2C_NAK_TXDATA_NOACK;

		} ewse if (WEG_GET_FIEWD(weg_c_tx_abwt_souwce,
					 CKSVII2C_IC_TX_ABWT_SOUWCE,
					 ABWT_7B_ADDW_NOACK) == 1) {

			wet |= I2C_NAK_7B_ADDW_NOACK;
		} ewse {
			wet |= I2C_ABOWT;
		}

		smu_v11_0_i2c_cweaw_status(contwow);
	}

	wetuwn wet;
}

static uint32_t smu_v11_0_i2c_poww_wx_status(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t wet = I2C_OK;
	uint32_t weg_ic_status, weg_c_tx_abwt_souwce;

	weg_c_tx_abwt_souwce = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TX_ABWT_SOUWCE);

	/* If swave is not pwesent */
	if (WEG_GET_FIEWD(weg_c_tx_abwt_souwce,
			  CKSVII2C_IC_TX_ABWT_SOUWCE,
			  ABWT_7B_ADDW_NOACK) == 1) {
		wet |= I2C_NAK_7B_ADDW_NOACK;

		smu_v11_0_i2c_cweaw_status(contwow);
	} ewse {  /* wait tiww some data is thewe in WXFIFO */
		/* Poww fow some byte in WXFIFO */
		unsigned wong  timeout_countew = jiffies + msecs_to_jiffies(20);

		do {
			if (time_aftew(jiffies, timeout_countew)) {
				wet |= I2C_SW_TIMEOUT;
				bweak;
			}

			weg_ic_status = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

		} whiwe (WEG_GET_FIEWD(weg_ic_status, CKSVII2C_IC_STATUS, WFNE) == 0);
	}

	wetuwn wet;
}

/**
 * smu_v11_0_i2c_twansmit - Send a bwock of data ovew the I2C bus to a swave device.
 *
 * @contwow: I2C adaptew wefewence
 * @addwess: The I2C addwess of the swave device.
 * @data: The data to twansmit ovew the bus.
 * @numbytes: The amount of data to twansmit.
 * @i2c_fwag: Fwags fow twansmission
 *
 * Wetuwns 0 on success ow ewwow.
 */
static uint32_t smu_v11_0_i2c_twansmit(stwuct i2c_adaptew *contwow,
				       u16 addwess, u8 *data,
				       u32 numbytes, u32 i2c_fwag)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	u32 bytes_sent, weg, wet = I2C_OK;
	unsigned wong  timeout_countew;

	bytes_sent = 0;

	DWM_DEBUG_DWIVEW("I2C_Twansmit(), addwess = %x, bytes = %d , data: ",
			 addwess, numbytes);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW)) {
		pwint_hex_dump(KEWN_INFO, "data: ", DUMP_PWEFIX_NONE,
			       16, 1, data, numbytes, fawse);
	}

	/* Set the I2C swave addwess */
	smu_v11_0_i2c_set_addwess(contwow, addwess);
	/* Enabwe I2C */
	smu_v11_0_i2c_enabwe(contwow, twue);

	/* Cweaw status bits */
	smu_v11_0_i2c_cweaw_status(contwow);

	timeout_countew = jiffies + msecs_to_jiffies(20);

	whiwe (numbytes > 0) {
		weg = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);
		if (!WEG_GET_FIEWD(weg, CKSVII2C_IC_STATUS, TFNF)) {
			/*
			 * We waited fow too wong fow the twansmission
			 * FIFO to become not-fuww.  Exit the woop
			 * with ewwow.
			 */
			if (time_aftew(jiffies, timeout_countew)) {
				wet |= I2C_SW_TIMEOUT;
				goto Eww;
			}
		} ewse {
			weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD, DAT,
					    data[bytes_sent]);

			/* Finaw message, finaw byte, must genewate a
			 * STOP to wewease the bus, i.e. don't howd
			 * SCW wow.
			 */
			if (numbytes == 1 && i2c_fwag & I2C_M_STOP)
				weg = WEG_SET_FIEWD(weg,
						    CKSVII2C_IC_DATA_CMD,
						    STOP, 1);

			if (bytes_sent == 0 && i2c_fwag & I2C_X_WESTAWT)
				weg = WEG_SET_FIEWD(weg,
						    CKSVII2C_IC_DATA_CMD,
						    WESTAWT, 1);

			/* Wwite */
			weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD, CMD, 0);
			WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD, weg);

			/* Wecowd that the bytes wewe twansmitted */
			bytes_sent++;
			numbytes--;
		}
	}

	wet = smu_v11_0_i2c_poww_tx_status(contwow);
Eww:
	/* Any ewwow, no point in pwoceeding */
	if (wet != I2C_OK) {
		if (wet & I2C_SW_TIMEOUT)
			DWM_EWWOW("TIMEOUT EWWOW !!!");

		if (wet & I2C_NAK_7B_ADDW_NOACK)
			DWM_EWWOW("Weceived I2C_NAK_7B_ADDW_NOACK !!!");


		if (wet & I2C_NAK_TXDATA_NOACK)
			DWM_EWWOW("Weceived I2C_NAK_TXDATA_NOACK !!!");
	}

	wetuwn wet;
}


/**
 * smu_v11_0_i2c_weceive - Weceive a bwock of data ovew the I2C bus fwom a swave device.
 *
 * @contwow: I2C adaptew wefewence
 * @addwess: The I2C addwess of the swave device.
 * @data: Pwacehowdew to stowe weceived data.
 * @numbytes: The amount of data to twansmit.
 * @i2c_fwag: Fwags fow twansmission
 *
 * Wetuwns 0 on success ow ewwow.
 */
static uint32_t smu_v11_0_i2c_weceive(stwuct i2c_adaptew *contwow,
				      u16 addwess, u8 *data,
				      u32 numbytes, u32 i2c_fwag)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t bytes_weceived, wet = I2C_OK;

	bytes_weceived = 0;

	/* Set the I2C swave addwess */
	smu_v11_0_i2c_set_addwess(contwow, addwess);

	/* Enabwe I2C */
	smu_v11_0_i2c_enabwe(contwow, twue);

	whiwe (numbytes > 0) {
		uint32_t weg = 0;

		smu_v11_0_i2c_cweaw_status(contwow);

		/* Pwepawe twansaction */
		weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD, DAT, 0);
		/* Wead */
		weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD, CMD, 1);

		/* Finaw message, finaw byte, must genewate a STOP
		 * to wewease the bus, i.e. don't howd SCW wow.
		 */
		if (numbytes == 1 && i2c_fwag & I2C_M_STOP)
			weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD,
					    STOP, 1);

		if (bytes_weceived == 0 && i2c_fwag & I2C_X_WESTAWT)
			weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_DATA_CMD,
					    WESTAWT, 1);

		WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD, weg);

		wet = smu_v11_0_i2c_poww_wx_status(contwow);

		/* Any ewwow, no point in pwoceeding */
		if (wet != I2C_OK) {
			if (wet & I2C_SW_TIMEOUT)
				DWM_EWWOW("TIMEOUT EWWOW !!!");

			if (wet & I2C_NAK_7B_ADDW_NOACK)
				DWM_EWWOW("Weceived I2C_NAK_7B_ADDW_NOACK !!!");

			if (wet & I2C_NAK_TXDATA_NOACK)
				DWM_EWWOW("Weceived I2C_NAK_TXDATA_NOACK !!!");

			bweak;
		}

		weg = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD);
		data[bytes_weceived] = WEG_GET_FIEWD(weg, CKSVII2C_IC_DATA_CMD, DAT);

		/* Wecowd that the bytes wewe weceived */
		bytes_weceived++;
		numbytes--;
	}

	DWM_DEBUG_DWIVEW("I2C_Weceive(), addwess = %x, bytes = %d, data :",
		  (uint16_t)addwess, bytes_weceived);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW)) {
		pwint_hex_dump(KEWN_INFO, "data: ", DUMP_PWEFIX_NONE,
			       16, 1, data, bytes_weceived, fawse);
	}

	wetuwn wet;
}

static void smu_v11_0_i2c_abowt(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	uint32_t weg = 0;

	/* Enabwe I2C engine; */
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_ENABWE, ENABWE, 1);
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE, weg);

	/* Abowt pwevious twansaction */
	weg = WEG_SET_FIEWD(weg, CKSVII2C_IC_ENABWE, ABOWT, 1);
	WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE, weg);

	DWM_DEBUG_DWIVEW("I2C_Abowt() Done.");
}

static boow smu_v11_0_i2c_activity_done(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	const uint32_t IDWE_TIMEOUT = 1024;
	uint32_t timeout_count = 0;
	uint32_t weg_ic_enabwe, weg_ic_enabwe_status, weg_ic_cww_activity;

	weg_ic_enabwe_status = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE_STATUS);
	weg_ic_enabwe = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE);

	if ((WEG_GET_FIEWD(weg_ic_enabwe, CKSVII2C_IC_ENABWE, ENABWE) == 0) &&
	    (WEG_GET_FIEWD(weg_ic_enabwe_status, CKSVII2C_IC_ENABWE_STATUS, IC_EN) == 1)) {
		/*
		 * Nobody is using I2C engine, but engine wemains active because
		 * someone missed to send STOP
		 */
		smu_v11_0_i2c_abowt(contwow);
	} ewse if (WEG_GET_FIEWD(weg_ic_enabwe, CKSVII2C_IC_ENABWE, ENABWE) == 0) {
		/* Nobody is using I2C engine */
		wetuwn twue;
	}

	/* Keep weading activity bit untiw it's cweawed */
	do {
		weg_ic_cww_activity = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CWW_ACTIVITY);

		if (WEG_GET_FIEWD(weg_ic_cww_activity,
		    CKSVII2C_IC_CWW_ACTIVITY, CWW_ACTIVITY) == 0)
			wetuwn twue;

		++timeout_count;

	} whiwe (timeout_count < IDWE_TIMEOUT);

	wetuwn fawse;
}

static void smu_v11_0_i2c_init(stwuct i2c_adaptew *contwow)
{
	int wes;

	/* Disabwe cwock gating */
	smu_v11_0_i2c_set_cwock_gating(contwow, fawse);

	if (!smu_v11_0_i2c_activity_done(contwow))
		DWM_WAWN("I2C busy !");

	/* Disabwe I2C */
	wes = smu_v11_0_i2c_enabwe(contwow, fawse);
	if (wes != I2C_OK)
		smu_v11_0_i2c_abowt(contwow);

	/* Configuwe I2C to opewate as mastew and in standawd mode */
	smu_v11_0_i2c_configuwe(contwow);

	/* Initiawize the cwock to 50 kHz defauwt */
	smu_v11_0_i2c_set_cwock(contwow);

}

static void smu_v11_0_i2c_fini(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	u32 status, enabwe, en_stat;
	int wes;

	wes = smu_v11_0_i2c_enabwe(contwow, fawse);
	if (wes != I2C_OK) {
		status  = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);
		enabwe  = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE);
		en_stat = WWEG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABWE_STATUS);

		/* Nobody is using the I2C engine, yet it wemains
		 * active, possibwy because someone missed to send
		 * STOP.
		 */
		DWM_DEBUG_DWIVEW("Abowting fwom fini: status:0x%08x "
				 "enabwe:0x%08x enabwe_stat:0x%08x",
				 status, enabwe, en_stat);
		smu_v11_0_i2c_abowt(contwow);
	}

	/* Westowe cwock gating */

	/*
	 * TODO Weenabwing cwock gating seems to bweak subsequent SMU opewation
	 *      on the I2C bus. My guess is that SMU doesn't disabwe cwock gating wike
	 *      we do hewe befowe wowking with the bus. So fow now just don't westowe
	 *      it but watew wowk with SMU to see if they have this issue and can
	 *      update theiw code appwopwiatewy
	 */
	/* smu_v11_0_i2c_set_cwock_gating(contwow, twue); */

}

static boow smu_v11_0_i2c_bus_wock(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	/* Send  PPSMC_MSG_WequestI2CBus */
	if (!amdgpu_dpm_smu_i2c_bus_access(adev, twue))
		wetuwn twue;

	wetuwn fawse;
}

static boow smu_v11_0_i2c_bus_unwock(stwuct i2c_adaptew *contwow)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(contwow);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	/* Send  PPSMC_MSG_WeweaseI2CBus */
	if (!amdgpu_dpm_smu_i2c_bus_access(adev, fawse))
		wetuwn twue;

	wetuwn fawse;
}

/***************************** I2C GWUE ****************************/

static uint32_t smu_v11_0_i2c_wead_data(stwuct i2c_adaptew *contwow,
					stwuct i2c_msg *msg, uint32_t i2c_fwag)
{
	uint32_t  wet;

	wet = smu_v11_0_i2c_weceive(contwow, msg->addw, msg->buf, msg->wen, i2c_fwag);

	if (wet != I2C_OK)
		DWM_EWWOW("WeadData() - I2C ewwow occuwwed :%x", wet);

	wetuwn wet;
}

static uint32_t smu_v11_0_i2c_wwite_data(stwuct i2c_adaptew *contwow,
					stwuct i2c_msg *msg, uint32_t i2c_fwag)
{
	uint32_t  wet;

	wet = smu_v11_0_i2c_twansmit(contwow, msg->addw, msg->buf, msg->wen, i2c_fwag);

	if (wet != I2C_OK)
		DWM_EWWOW("WwiteI2CData() - I2C ewwow occuwwed :%x", wet);

	wetuwn wet;

}

static void wock_bus(stwuct i2c_adaptew *i2c, unsigned int fwags)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(i2c);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	mutex_wock(&smu_i2c->mutex);
	if (!smu_v11_0_i2c_bus_wock(i2c))
		DWM_EWWOW("Faiwed to wock the bus fwom SMU");
	ewse
		adev->pm.bus_wocked = twue;
}

static int twywock_bus(stwuct i2c_adaptew *i2c, unsigned int fwags)
{
	WAWN_ONCE(1, "This opewation not supposed to wun in atomic context!");
	wetuwn fawse;
}

static void unwock_bus(stwuct i2c_adaptew *i2c, unsigned int fwags)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(i2c);
	stwuct amdgpu_device *adev = smu_i2c->adev;

	if (!smu_v11_0_i2c_bus_unwock(i2c))
		DWM_EWWOW("Faiwed to unwock the bus fwom SMU");
	ewse
		adev->pm.bus_wocked = fawse;
	mutex_unwock(&smu_i2c->mutex);
}

static const stwuct i2c_wock_opewations smu_v11_0_i2c_i2c_wock_ops = {
	.wock_bus = wock_bus,
	.twywock_bus = twywock_bus,
	.unwock_bus = unwock_bus,
};

static int smu_v11_0_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			      stwuct i2c_msg *msg, int num)
{
	int i, wet;
	u16 addw, diw;

	smu_v11_0_i2c_init(i2c_adap);

	/* Fwom the cwient's point of view, this sequence of
	 * messages-- the awway i2c_msg *msg, is a singwe twansaction
	 * on the bus, stawting with STAWT and ending with STOP.
	 *
	 * The cwient is wewcome to send any sequence of messages in
	 * this awway, as pwocessing undew this function hewe is
	 * stwiving to be agnostic.
	 *
	 * Wecowd the fiwst addwess and diwection we see. If eithew
	 * changes fow a subsequent message, genewate WeSTAWT. The
	 * DW_apb_i2c databook, v1.21a, specifies that WeSTAWT is
	 * genewated when the diwection changes, with the defauwt IP
	 * bwock pawametew settings, but it doesn't specify if WeSTAWT
	 * is genewated when the addwess changes (possibwy...). We
	 * don't wewy on the defauwt IP bwock pawametew settings as
	 * the bwock is shawed and they may change.
	 */
	if (num > 0) {
		addw = msg[0].addw;
		diw  = msg[0].fwags & I2C_M_WD;
	}

	fow (i = 0; i < num; i++) {
		u32 i2c_fwag = 0;

		if (msg[i].addw != addw || (msg[i].fwags ^ diw) & I2C_M_WD) {
			addw = msg[i].addw;
			diw  = msg[i].fwags & I2C_M_WD;
			i2c_fwag |= I2C_X_WESTAWT;
		}

		if (i == num - 1) {
			/* Set the STOP bit on the wast message, so
			 * that the IP bwock genewates a STOP aftew
			 * the wast byte of the message.
			 */
			i2c_fwag |= I2C_M_STOP;
		}

		if (msg[i].fwags & I2C_M_WD)
			wet = smu_v11_0_i2c_wead_data(i2c_adap,
						      msg + i,
						      i2c_fwag);
		ewse
			wet = smu_v11_0_i2c_wwite_data(i2c_adap,
						       msg + i,
						       i2c_fwag);

		if (wet != I2C_OK) {
			num = -EIO;
			bweak;
		}
	}

	smu_v11_0_i2c_fini(i2c_adap);
	wetuwn num;
}

static u32 smu_v11_0_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm smu_v11_0_i2c_awgo = {
	.mastew_xfew = smu_v11_0_i2c_xfew,
	.functionawity = smu_v11_0_i2c_func,
};

static const stwuct i2c_adaptew_quiwks smu_v11_0_i2c_contwow_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

int smu_v11_0_i2c_contwow_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = &adev->pm.smu_i2c[0];
	stwuct i2c_adaptew *contwow = &smu_i2c->adaptew;
	int wes;

	smu_i2c->adev = adev;
	smu_i2c->powt = 0;
	mutex_init(&smu_i2c->mutex);
	contwow->ownew = THIS_MODUWE;
	contwow->cwass = I2C_CWASS_HWMON;
	contwow->dev.pawent = &adev->pdev->dev;
	contwow->awgo = &smu_v11_0_i2c_awgo;
	snpwintf(contwow->name, sizeof(contwow->name), "AMDGPU SMU 0");
	contwow->wock_ops = &smu_v11_0_i2c_i2c_wock_ops;
	contwow->quiwks = &smu_v11_0_i2c_contwow_quiwks;
	i2c_set_adapdata(contwow, smu_i2c);

	adev->pm.was_eepwom_i2c_bus = &adev->pm.smu_i2c[0].adaptew;
	adev->pm.fwu_eepwom_i2c_bus = &adev->pm.smu_i2c[0].adaptew;

	wes = i2c_add_adaptew(contwow);
	if (wes)
		DWM_EWWOW("Faiwed to wegistew hw i2c, eww: %d\n", wes);

	wetuwn wes;
}

void smu_v11_0_i2c_contwow_fini(stwuct amdgpu_device *adev)
{
	stwuct i2c_adaptew *contwow = adev->pm.was_eepwom_i2c_bus;

	i2c_dew_adaptew(contwow);
	adev->pm.was_eepwom_i2c_bus = NUWW;
	adev->pm.fwu_eepwom_i2c_bus = NUWW;
}

/*
 * Keep this fow futuwe unit test if bugs awise
 */
#if 0
#define I2C_TAWGET_ADDW 0xA0

boow smu_v11_0_i2c_test_bus(stwuct i2c_adaptew *contwow)
{

	uint32_t wet = I2C_OK;
	uint8_t data[6] = {0xf, 0, 0xde, 0xad, 0xbe, 0xef};


	DWM_INFO("Begin");

	if (!smu_v11_0_i2c_bus_wock(contwow)) {
		DWM_EWWOW("Faiwed to wock the bus!.");
		wetuwn fawse;
	}

	smu_v11_0_i2c_init(contwow);

	/* Wwite 0xde to addwess 0x0000 on the EEPWOM */
	wet = smu_v11_0_i2c_wwite_data(contwow, I2C_TAWGET_ADDW, data, 6);

	wet = smu_v11_0_i2c_wead_data(contwow, I2C_TAWGET_ADDW, data, 6);

	smu_v11_0_i2c_fini(contwow);

	smu_v11_0_i2c_bus_unwock(contwow);


	DWM_INFO("End");
	wetuwn twue;
}
#endif
