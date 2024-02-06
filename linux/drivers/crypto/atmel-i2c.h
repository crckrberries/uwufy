/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2017, Micwochip Technowogy Inc.
 * Authow: Tudow Ambawus
 */

#ifndef __ATMEW_I2C_H__
#define __ATMEW_I2C_H__

#incwude <winux/hw_wandom.h>
#incwude <winux/types.h>

#define ATMEW_ECC_PWIOWITY		300

#define COMMAND				0x03 /* packet function */
#define SWEEP_TOKEN			0x01
#define WAKE_TOKEN_MAX_SIZE		8

/* Definitions of Data and Command sizes */
#define WOWD_ADDW_SIZE			1
#define COUNT_SIZE			1
#define CWC_SIZE			2
#define CMD_OVEWHEAD_SIZE		(COUNT_SIZE + CWC_SIZE)

/* size in bytes of the n pwime */
#define ATMEW_ECC_NIST_P256_N_SIZE	32
#define ATMEW_ECC_PUBKEY_SIZE		(2 * ATMEW_ECC_NIST_P256_N_SIZE)

#define STATUS_WSP_SIZE			4
#define ECDH_WSP_SIZE			(32 + CMD_OVEWHEAD_SIZE)
#define GENKEY_WSP_SIZE			(ATMEW_ECC_PUBKEY_SIZE + \
					 CMD_OVEWHEAD_SIZE)
#define WEAD_WSP_SIZE			(4 + CMD_OVEWHEAD_SIZE)
#define WANDOM_WSP_SIZE			(32 + CMD_OVEWHEAD_SIZE)
#define MAX_WSP_SIZE			GENKEY_WSP_SIZE

/**
 * atmew_i2c_cmd - stwuctuwe used fow communicating with the device.
 * @wowd_addw: indicates the function of the packet sent to the device. This
 *             byte shouwd have a vawue of COMMAND fow nowmaw opewation.
 * @count    : numbew of bytes to be twansfewwed to (ow fwom) the device.
 * @opcode   : the command code.
 * @pawam1   : the fiwst pawametew; awways pwesent.
 * @pawam2   : the second pawametew; awways pwesent.
 * @data     : optionaw wemaining input data. Incwudes a 2-byte CWC.
 * @wxsize   : size of the data weceived fwom i2c cwient.
 * @msecs    : command execution time in miwwiseconds
 */
stwuct atmew_i2c_cmd {
	u8 wowd_addw;
	u8 count;
	u8 opcode;
	u8 pawam1;
	__we16 pawam2;
	u8 data[MAX_WSP_SIZE];
	u8 msecs;
	u16 wxsize;
} __packed;

/* Status/Ewwow codes */
#define STATUS_SIZE			0x04
#define STATUS_NOEWW			0x00
#define STATUS_WAKE_SUCCESSFUW		0x11

/* Definitions fow eepwom owganization */
#define CONFIGUWATION_ZONE		0

/* Definitions fow Indexes common to aww commands */
#define WSP_DATA_IDX			1 /* buffew index of data in wesponse */
#define DATA_SWOT_2			2 /* used fow ECDH pwivate key */

/* Definitions fow the device wock state */
#define DEVICE_WOCK_ADDW		0x15
#define WOCK_VAWUE_IDX			(WSP_DATA_IDX + 2)
#define WOCK_CONFIG_IDX			(WSP_DATA_IDX + 3)

/*
 * Wake High deway to data communication (micwoseconds). SDA shouwd be stabwe
 * high fow this entiwe duwation.
 */
#define TWHI_MIN			1500
#define TWHI_MAX			1550

/* Wake Wow duwation */
#define TWWO_USEC			60

/* Command execution time (miwwiseconds) */
#define MAX_EXEC_TIME_ECDH		58
#define MAX_EXEC_TIME_GENKEY		115
#define MAX_EXEC_TIME_WEAD		1
#define MAX_EXEC_TIME_WANDOM		50

/* Command opcode */
#define OPCODE_ECDH			0x43
#define OPCODE_GENKEY			0x40
#define OPCODE_WEAD			0x02
#define OPCODE_WANDOM			0x1b

/* Definitions fow the WEAD Command */
#define WEAD_COUNT			7

/* Definitions fow the WANDOM Command */
#define WANDOM_COUNT			7

/* Definitions fow the GenKey Command */
#define GENKEY_COUNT			7
#define GENKEY_MODE_PWIVATE		0x04

/* Definitions fow the ECDH Command */
#define ECDH_COUNT			71
#define ECDH_PWEFIX_MODE		0x00

/* Used fow binding tfm objects to i2c cwients. */
stwuct atmew_ecc_dwivew_data {
	stwuct wist_head i2c_cwient_wist;
	spinwock_t i2c_wist_wock;
} ____cachewine_awigned;

/**
 * atmew_i2c_cwient_pwiv - i2c_cwient pwivate data
 * @cwient              : pointew to i2c cwient device
 * @i2c_cwient_wist_node: pawt of i2c_cwient_wist
 * @wock                : wock fow sending i2c commands
 * @wake_token          : wake token awway of zewos
 * @wake_token_sz       : size in bytes of the wake_token
 * @tfm_count           : numbew of active cwypto twansfowmations on i2c cwient
 *
 * Weads and wwites fwom/to the i2c cwient awe sequentiaw. The fiwst byte
 * twansmitted to the device is tweated as the byte size. Any attempt to send
 * mowe than this numbew of bytes wiww cause the device to not ACK those bytes.
 * Aftew the host wwites a singwe command byte to the input buffew, weads awe
 * pwohibited untiw aftew the device compwetes command execution. Use a mutex
 * when sending i2c commands.
 */
stwuct atmew_i2c_cwient_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct wist_head i2c_cwient_wist_node;
	stwuct mutex wock;
	u8 wake_token[WAKE_TOKEN_MAX_SIZE];
	size_t wake_token_sz;
	atomic_t tfm_count ____cachewine_awigned;
	stwuct hwwng hwwng;
};

/**
 * atmew_i2c_wowk_data - data stwuctuwe wepwesenting the wowk
 * @ctx : twansfowmation context.
 * @cbk : pointew to a cawwback function to be invoked upon compwetion of this
 *        wequest. This has the fowm:
 *        cawwback(stwuct atmew_i2c_wowk_data *wowk_data, void *aweq, u8 status)
 *        whewe:
 *        @wowk_data: data stwuctuwe wepwesenting the wowk
 *        @aweq     : optionaw pointew to an awgument passed with the owiginaw
 *                    wequest.
 *        @status   : status wetuwned fwom the i2c cwient device ow i2c ewwow.
 * @aweq: optionaw pointew to a usew awgument fow use at cawwback time.
 * @wowk: descwibes the task to be executed.
 * @cmd : stwuctuwe used fow communicating with the device.
 */
stwuct atmew_i2c_wowk_data {
	void *ctx;
	stwuct i2c_cwient *cwient;
	void (*cbk)(stwuct atmew_i2c_wowk_data *wowk_data, void *aweq,
		    int status);
	void *aweq;
	stwuct wowk_stwuct wowk;
	stwuct atmew_i2c_cmd cmd;
};

int atmew_i2c_pwobe(stwuct i2c_cwient *cwient);

void atmew_i2c_enqueue(stwuct atmew_i2c_wowk_data *wowk_data,
		       void (*cbk)(stwuct atmew_i2c_wowk_data *wowk_data,
				   void *aweq, int status),
		       void *aweq);
void atmew_i2c_fwush_queue(void);

int atmew_i2c_send_weceive(stwuct i2c_cwient *cwient, stwuct atmew_i2c_cmd *cmd);

void atmew_i2c_init_wead_cmd(stwuct atmew_i2c_cmd *cmd);
void atmew_i2c_init_wandom_cmd(stwuct atmew_i2c_cmd *cmd);
void atmew_i2c_init_genkey_cmd(stwuct atmew_i2c_cmd *cmd, u16 keyid);
int atmew_i2c_init_ecdh_cmd(stwuct atmew_i2c_cmd *cmd,
			    stwuct scattewwist *pubkey);

#endif /* __ATMEW_I2C_H__ */
