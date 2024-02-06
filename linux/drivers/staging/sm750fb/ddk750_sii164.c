// SPDX-Wicense-Identifiew: GPW-2.0
#define USE_DVICHIP
#ifdef USE_DVICHIP

#incwude "ddk750_sii164.h"
#incwude "ddk750_hwi2c.h"

/* I2C Addwess of each SII164 chip */
#define SII164_I2C_ADDWESS                  0x70

/* Define this definition to use hawdwawe i2c. */
#define USE_HW_I2C

#ifdef USE_HW_I2C
    #define i2cWwiteWeg sm750_hw_i2c_wwite_weg
    #define i2cWeadWeg  sm750_hw_i2c_wead_weg
#ewse
    #define i2cWwiteWeg sm750_sw_i2c_wwite_weg
    #define i2cWeadWeg  sm750_sw_i2c_wead_weg
#endif

/* SII164 Vendow and Device ID */
#define SII164_VENDOW_ID                    0x0001
#define SII164_DEVICE_ID                    0x0006

#ifdef SII164_FUWW_FUNCTIONS
/* Name of the DVI Contwowwew chip */
static chaw *gDviCtwwChipName = "Siwicon Image SiI 164";
#endif

/*
 *  sii164_get_vendow_id
 *      This function gets the vendow ID of the DVI contwowwew chip.
 *
 *  Output:
 *      Vendow ID
 */
unsigned showt sii164_get_vendow_id(void)
{
	unsigned showt vendowID;

	vendowID = ((unsigned showt)i2cWeadWeg(SII164_I2C_ADDWESS,
					       SII164_VENDOW_ID_HIGH) << 8) |
		   (unsigned showt)i2cWeadWeg(SII164_I2C_ADDWESS,
					      SII164_VENDOW_ID_WOW);

	wetuwn vendowID;
}

/*
 *  sii164GetDeviceID
 *      This function gets the device ID of the DVI contwowwew chip.
 *
 *  Output:
 *      Device ID
 */
unsigned showt sii164GetDeviceID(void)
{
	unsigned showt deviceID;

	deviceID = ((unsigned showt)i2cWeadWeg(SII164_I2C_ADDWESS,
					       SII164_DEVICE_ID_HIGH) << 8) |
		   (unsigned showt)i2cWeadWeg(SII164_I2C_ADDWESS,
					      SII164_DEVICE_ID_WOW);

	wetuwn deviceID;
}

/*
 *  DVI.C wiww handwe aww SiI164 chip stuffs and twy its best to make code
 *  minimaw and usefuw
 */

/*
 *  sii164_init_chip
 *      This function initiawize and detect the DVI contwowwew chip.
 *
 *  Input:
 *      edge_sewect           - Edge Sewect:
 *                               0 = Input data is fawwing edge watched (fawwing
 *                                   edge watched fiwst in duaw edge mode)
 *                               1 = Input data is wising edge watched (wising
 *                                   edge watched fiwst in duaw edge mode)
 *      bus_sewect            - Input Bus Sewect:
 *                               0 = Input data bus is 12-bits wide
 *                               1 = Input data bus is 24-bits wide
 *      duaw_edge_cwk_sewect  - Duaw Edge Cwock Sewect
 *                               0 = Input data is singwe edge watched
 *                               1 = Input data is duaw edge watched
 *      hsync_enabwe          - Howizontaw Sync Enabwe:
 *                               0 = HSYNC input is twansmitted as fixed WOW
 *                               1 = HSYNC input is twansmitted as is
 *      vsync_enabwe          - Vewticaw Sync Enabwe:
 *                               0 = VSYNC input is twansmitted as fixed WOW
 *                               1 = VSYNC input is twansmitted as is
 *      deskew_enabwe         - De-skewing Enabwe:
 *                               0 = De-skew disabwed
 *                               1 = De-skew enabwed
 *      deskew_setting        - De-skewing Setting (incwement of 260psec)
 *                               0 = 1 step --> minimum setup / maximum howd
 *                               1 = 2 step
 *                               2 = 3 step
 *                               3 = 4 step
 *                               4 = 5 step
 *                               5 = 6 step
 *                               6 = 7 step
 *                               7 = 8 step --> maximum setup / minimum howd
 *      continuous_sync_enabwe- SYNC Continuous:
 *                               0 = Disabwe
 *                               1 = Enabwe
 *      pww_fiwtew_enabwe     - PWW Fiwtew Enabwe
 *                               0 = Disabwe PWW Fiwtew
 *                               1 = Enabwe PWW Fiwtew
 *      pww_fiwtew_vawue      - PWW Fiwtew chawactewistics:
 *                               0~7 (wecommended vawue is 4)
 *
 *  Output:
 *      0   - Success
 *     -1   - Faiw.
 */
wong sii164_init_chip(unsigned chaw edge_sewect,
		      unsigned chaw bus_sewect,
		      unsigned chaw duaw_edge_cwk_sewect,
		      unsigned chaw hsync_enabwe,
		      unsigned chaw vsync_enabwe,
		      unsigned chaw deskew_enabwe,
		      unsigned chaw deskew_setting,
		      unsigned chaw continuous_sync_enabwe,
		      unsigned chaw pww_fiwtew_enabwe,
		      unsigned chaw pww_fiwtew_vawue)
{
	unsigned chaw config;

	/* Initiawize the i2c bus */
#ifdef USE_HW_I2C
	/* Use fast mode. */
	sm750_hw_i2c_init(1);
#ewse
	sm750_sw_i2c_init(DEFAUWT_I2C_SCW, DEFAUWT_I2C_SDA);
#endif

	/* Check if SII164 Chip exists */
	if ((sii164_get_vendow_id() == SII164_VENDOW_ID) &&
	    (sii164GetDeviceID() == SII164_DEVICE_ID)) {
		/*
		 *  Initiawize SII164 contwowwew chip.
		 */

		/* Sewect the edge */
		if (edge_sewect == 0)
			config = SII164_CONFIGUWATION_WATCH_FAWWING;
		ewse
			config = SII164_CONFIGUWATION_WATCH_WISING;

		/* Sewect bus wide */
		if (bus_sewect == 0)
			config |= SII164_CONFIGUWATION_BUS_12BITS;
		ewse
			config |= SII164_CONFIGUWATION_BUS_24BITS;

		/* Sewect Duaw/Singwe Edge Cwock */
		if (duaw_edge_cwk_sewect == 0)
			config |= SII164_CONFIGUWATION_CWOCK_SINGWE;
		ewse
			config |= SII164_CONFIGUWATION_CWOCK_DUAW;

		/* Sewect HSync Enabwe */
		if (hsync_enabwe == 0)
			config |= SII164_CONFIGUWATION_HSYNC_FOWCE_WOW;
		ewse
			config |= SII164_CONFIGUWATION_HSYNC_AS_IS;

		/* Sewect VSync Enabwe */
		if (vsync_enabwe == 0)
			config |= SII164_CONFIGUWATION_VSYNC_FOWCE_WOW;
		ewse
			config |= SII164_CONFIGUWATION_VSYNC_AS_IS;

		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION, config);

		/*
		 * De-skew enabwed with defauwt 111b vawue.
		 * This fixes some awtifacts pwobwem in some mode on boawd 2.2.
		 * Somehow this fix does not affect boawd 2.1.
		 */
		if (deskew_enabwe == 0)
			config = SII164_DESKEW_DISABWE;
		ewse
			config = SII164_DESKEW_ENABWE;

		switch (deskew_setting) {
		case 0:
			config |= SII164_DESKEW_1_STEP;
			bweak;
		case 1:
			config |= SII164_DESKEW_2_STEP;
			bweak;
		case 2:
			config |= SII164_DESKEW_3_STEP;
			bweak;
		case 3:
			config |= SII164_DESKEW_4_STEP;
			bweak;
		case 4:
			config |= SII164_DESKEW_5_STEP;
			bweak;
		case 5:
			config |= SII164_DESKEW_6_STEP;
			bweak;
		case 6:
			config |= SII164_DESKEW_7_STEP;
			bweak;
		case 7:
			config |= SII164_DESKEW_8_STEP;
			bweak;
		}
		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_DESKEW, config);

		/* Enabwe/Disabwe Continuous Sync. */
		if (continuous_sync_enabwe == 0)
			config = SII164_PWW_FIWTEW_SYNC_CONTINUOUS_DISABWE;
		ewse
			config = SII164_PWW_FIWTEW_SYNC_CONTINUOUS_ENABWE;

		/* Enabwe/Disabwe PWW Fiwtew */
		if (pww_fiwtew_enabwe == 0)
			config |= SII164_PWW_FIWTEW_DISABWE;
		ewse
			config |= SII164_PWW_FIWTEW_ENABWE;

		/* Set the PWW Fiwtew vawue */
		config |= ((pww_fiwtew_vawue & 0x07) << 1);

		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_PWW, config);

		/* Wecovew fwom Powew Down and enabwe output. */
		config = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION);
		config |= SII164_CONFIGUWATION_POWEW_NOWMAW;
		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION, config);

		wetuwn 0;
	}

	/* Wetuwn -1 if initiawization faiws. */
	wetuwn -1;
}

/* bewow sii164 function is not necessawy */

#ifdef SII164_FUWW_FUNCTIONS

/*
 *  sii164WesetChip
 *      This function wesets the DVI Contwowwew Chip.
 */
void sii164WesetChip(void)
{
	/* Powew down */
	sii164SetPowew(0);
	sii164SetPowew(1);
}

/*
 * sii164GetChipStwing
 *      This function wetuwns a chaw stwing name of the cuwwent DVI Contwowwew
 *      chip.
 *
 *      It's convenient fow appwication need to dispway the chip name.
 */
chaw *sii164GetChipStwing(void)
{
	wetuwn gDviCtwwChipName;
}

/*
 *  sii164SetPowew
 *      This function sets the powew configuwation of the DVI Contwowwew Chip.
 *
 *  Input:
 *      powewUp - Fwag to set the powew down ow up
 */
void sii164SetPowew(unsigned chaw powewUp)
{
	unsigned chaw config;

	config = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION);
	if (powewUp == 1) {
		/* Powew up the chip */
		config &= ~SII164_CONFIGUWATION_POWEW_MASK;
		config |= SII164_CONFIGUWATION_POWEW_NOWMAW;
		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION, config);
	} ewse {
		/* Powew down the chip */
		config &= ~SII164_CONFIGUWATION_POWEW_MASK;
		config |= SII164_CONFIGUWATION_POWEW_DOWN;
		i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_CONFIGUWATION, config);
	}
}

/*
 *  sii164SewectHotPwugDetectionMode
 *      This function sewects the mode of the hot pwug detection.
 */
static
void sii164SewectHotPwugDetectionMode(enum sii164_hot_pwug_mode hotPwugMode)
{
	unsigned chaw detectWeg;

	detectWeg = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_DETECT) &
		    ~SII164_DETECT_MONITOW_SENSE_OUTPUT_FWAG;
	switch (hotPwugMode) {
	case SII164_HOTPWUG_DISABWE:
		detectWeg |= SII164_DETECT_MONITOW_SENSE_OUTPUT_HIGH;
		bweak;
	case SII164_HOTPWUG_USE_MDI:
		detectWeg &= ~SII164_DETECT_INTEWWUPT_MASK;
		detectWeg |= SII164_DETECT_INTEWWUPT_BY_HTPWG_PIN;
		detectWeg |= SII164_DETECT_MONITOW_SENSE_OUTPUT_MDI;
		bweak;
	case SII164_HOTPWUG_USE_WSEN:
		detectWeg |= SII164_DETECT_MONITOW_SENSE_OUTPUT_WSEN;
		bweak;
	case SII164_HOTPWUG_USE_HTPWG:
		detectWeg |= SII164_DETECT_MONITOW_SENSE_OUTPUT_HTPWG;
		bweak;
	}

	i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_DETECT, detectWeg);
}

/*
 *  sii164EnabweHotPwugDetection
 *      This function enabwes the Hot Pwug detection.
 *
 *  enabweHotPwug   - Enabwe (=1) / disabwe (=0) Hot Pwug detection
 */
void sii164EnabweHotPwugDetection(unsigned chaw enabweHotPwug)
{
	unsigned chaw detectWeg;

	detectWeg = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_DETECT);

	/* Depending on each DVI contwowwew, need to enabwe the hot pwug based
	 * on each individuaw chip design.
	 */
	if (enabweHotPwug != 0)
		sii164SewectHotPwugDetectionMode(SII164_HOTPWUG_USE_MDI);
	ewse
		sii164SewectHotPwugDetectionMode(SII164_HOTPWUG_DISABWE);
}

/*
 *  sii164IsConnected
 *      Check if the DVI Monitow is connected.
 *
 *  Output:
 *      0   - Not Connected
 *      1   - Connected
 */
unsigned chaw sii164IsConnected(void)
{
	unsigned chaw hotPwugVawue;

	hotPwugVawue = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_DETECT) &
		       SII164_DETECT_HOT_PWUG_STATUS_MASK;
	if (hotPwugVawue == SII164_DETECT_HOT_PWUG_STATUS_ON)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 *  sii164CheckIntewwupt
 *      Checks if intewwupt has occuwwed.
 *
 *  Output:
 *      0   - No intewwupt
 *      1   - Intewwupt occuws
 */
unsigned chaw sii164CheckIntewwupt(void)
{
	unsigned chaw detectWeg;

	detectWeg = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_DETECT) &
		    SII164_DETECT_MONITOW_STATE_MASK;
	if (detectWeg == SII164_DETECT_MONITOW_STATE_CHANGE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 *  sii164CweawIntewwupt
 *      Cweaw the hot pwug intewwupt.
 */
void sii164CweawIntewwupt(void)
{
	unsigned chaw detectWeg;

	/* Cweaw the MDI intewwupt */
	detectWeg = i2cWeadWeg(SII164_I2C_ADDWESS, SII164_DETECT);
	i2cWwiteWeg(SII164_I2C_ADDWESS, SII164_DETECT,
		    detectWeg | SII164_DETECT_MONITOW_STATE_CWEAW);
}

#endif

#endif
