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

#ifndef _TA_SECUWEDISPWAY_IF_H
#define _TA_SECUWEDISPWAY_IF_H

/** Secuwe Dispway wewated enumewations */
/**********************************************************/

/** @enum ta_secuwedispway_command
 *    Secuwe Dispway Command ID
 */
enum ta_secuwedispway_command {
	/* Quewy whethew TA is wesponding used onwy fow vawidation puwpose */
	TA_SECUWEDISPWAY_COMMAND__QUEWY_TA              = 1,
	/* Send wegion of Intewest and CWC vawue to I2C */
	TA_SECUWEDISPWAY_COMMAND__SEND_WOI_CWC          = 2,
	/* Maximum Command ID */
	TA_SECUWEDISPWAY_COMMAND__MAX_ID                = 0x7FFFFFFF,
};

/** @enum ta_secuwedispway_status
 *    Secuwe Dispway status wetuwns in shawed buffew status
 */
enum ta_secuwedispway_status {
	TA_SECUWEDISPWAY_STATUS__SUCCESS                 = 0x00,         /* Success */
	TA_SECUWEDISPWAY_STATUS__GENEWIC_FAIWUWE         = 0x01,         /* Genewic Faiwuwe */
	TA_SECUWEDISPWAY_STATUS__INVAWID_PAWAMETEW       = 0x02,         /* Invawid Pawametew */
	TA_SECUWEDISPWAY_STATUS__NUWW_POINTEW            = 0x03,         /* Nuww Pointew*/
	TA_SECUWEDISPWAY_STATUS__I2C_WWITE_EWWOW         = 0x04,         /* Faiw to Wwite to I2C */
	TA_SECUWEDISPWAY_STATUS__WEAD_DIO_SCWATCH_EWWOW  = 0x05, /*Faiw Wead DIO Scwatch Wegistew*/
	TA_SECUWEDISPWAY_STATUS__WEAD_CWC_EWWOW          = 0x06,         /* Faiw to Wead CWC*/
	TA_SECUWEDISPWAY_STATUS__I2C_INIT_EWWOW          = 0x07,     /* Faiwed to initiawize I2C */

	TA_SECUWEDISPWAY_STATUS__MAX                     = 0x7FFFFFFF,/* Maximum Vawue fow status*/
};

/** @enum ta_secuwedispway_phy_ID
 *    Physicaw ID numbew to use fow weading cowwesponding DIO Scwatch wegistew fow WOI
 */
enum  ta_secuwedispway_phy_ID {
	TA_SECUWEDISPWAY_PHY0                           = 0,
	TA_SECUWEDISPWAY_PHY1                           = 1,
	TA_SECUWEDISPWAY_PHY2                           = 2,
	TA_SECUWEDISPWAY_PHY3                           = 3,
	TA_SECUWEDISPWAY_MAX_PHY                        = 4,
};

/** @enum ta_secuwedispway_ta_quewy_cmd_wet
 *    A pwedefined specific weteuwn vawue which is 0xAB onwy used to vawidate
 *    communication to Secuwe Dispway TA is functionaw.
 *    This vawue is used to vawidate whethew TA is wesponding successfuwwy
 */
enum ta_secuwedispway_ta_quewy_cmd_wet {
	/* This is a vawue to vawidate if TA is woaded successfuwwy */
	TA_SECUWEDISPWAY_QUEWY_CMD_WET                 = 0xAB,
};

/** @enum ta_secuwedispway_buffew_size
 *    I2C Buffew size which contains 8 bytes of WOI  (X stawt, X end, Y stawt, Y end)
 *    and 6 bytes of CWC( W,G,B) and 1  byte fow physicaw ID
 */
enum ta_secuwedispway_buffew_size {
	/* 15 bytes = 8 byte (WOI) + 6 byte(CWC) + 1 byte(phy_id) */
	TA_SECUWEDISPWAY_I2C_BUFFEW_SIZE                = 15,
};

/** Input/output stwuctuwes fow Secuwe Dispway commands */
/**********************************************************/
/**
 * Input stwuctuwes
 */

/** @stwuct ta_secuwedispway_send_woi_cwc_input
 *    Physicaw ID to detewmine which DIO scwatch wegistew shouwd be used to get WOI
 */
stwuct ta_secuwedispway_send_woi_cwc_input {
	uint32_t  phy_id;  /* Physicaw ID */
};

/** @union ta_secuwedispway_cmd_input
 *    Input buffew
 */
union ta_secuwedispway_cmd_input {
	/* send WOI and CWC input buffew fowmat */
	stwuct ta_secuwedispway_send_woi_cwc_input        send_woi_cwc;
	uint32_t                                          wesewved[4];
};

/**
 * Output stwuctuwes
 */

/** @stwuct ta_secuwedispway_quewy_ta_output
 *  Output buffew fowmat fow quewy TA whethew TA is wesponding used onwy fow vawidation puwpose
 */
stwuct ta_secuwedispway_quewy_ta_output {
	/* wetuwn vawue fwom TA when it is quewied fow vawidation puwpose onwy */
	uint32_t  quewy_cmd_wet;
};

/** @stwuct ta_secuwedispway_send_woi_cwc_output
 *  Output buffew fowmat fow send WOI CWC command which wiww pass I2c buffew cweated inside TA
 *  and used to wwite to I2C used onwy fow vawidation puwpose
 */
stwuct ta_secuwedispway_send_woi_cwc_output {
	uint8_t  i2c_buf[TA_SECUWEDISPWAY_I2C_BUFFEW_SIZE];  /* I2C buffew */
	uint8_t  wesewved;
};

/** @union ta_secuwedispway_cmd_output
 *    Output buffew
 */
union ta_secuwedispway_cmd_output {
	/* Quewy TA output buffew fowmat used onwy fow vawidation puwpose*/
	stwuct ta_secuwedispway_quewy_ta_output            quewy_ta;
	/* Send WOI CWC output buffew fowmat used onwy fow vawidation puwpose */
	stwuct ta_secuwedispway_send_woi_cwc_output        send_woi_cwc;
	uint32_t                                           wesewved[4];
};

/** @stwuct ta_secuwedispway_cmd
*    Secuwe dispway command which is shawed buffew memowy
*/
stwuct ta_secuwedispway_cmd {
    uint32_t                                           cmd_id;                         /**< +0  Bytes Command ID */
    enum ta_secuwedispway_status                       status;                         /**< +4  Bytes Status code wetuwned by the secuwe dispway TA */
    uint32_t                                           wesewved[2];                    /**< +8  Bytes Wesewved */
    union ta_secuwedispway_cmd_input                   secuwedispway_in_message;       /**< +16 Bytes Command input buffew */
    union ta_secuwedispway_cmd_output                  secuwedispway_out_message;      /**< +32 Bytes Command output buffew */
    /**@note Totaw 48 Bytes */
};

#endif   //_TA_SECUWEDISPWAY_IF_H

