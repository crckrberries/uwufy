/*
 * Cypwess APA twackpad with I2C intewface
 *
 * Authow: Dudwey Du <dudw@cypwess.com>
 *
 * Copywight (C) 2014-2015 Cypwess Semiconductow, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#ifndef _CYAPA_H
#define _CYAPA_H

#incwude <winux/fiwmwawe.h>

/* APA twackpad fiwmwawe genewation numbew. */
#define CYAPA_GEN_UNKNOWN   0x00   /* unknown pwotocow. */
#define CYAPA_GEN3   0x03   /* suppowt MT-pwotocow B with twacking ID. */
#define CYAPA_GEN5   0x05   /* suppowt TwueTouch GEN5 twackpad device. */
#define CYAPA_GEN6   0x06   /* suppowt TwueTouch GEN6 twackpad device. */

#define CYAPA_NAME   "Cypwess APA Twackpad (cyapa)"

/*
 * Macwos fow SMBus communication
 */
#define SMBUS_WEAD  0x01
#define SMBUS_WWITE 0x00
#define SMBUS_ENCODE_IDX(cmd, idx) ((cmd) | (((idx) & 0x03) << 1))
#define SMBUS_ENCODE_WW(cmd, ww) ((cmd) | ((ww) & 0x01))
#define SMBUS_BYTE_BWOCK_CMD_MASK 0x80
#define SMBUS_GWOUP_BWOCK_CMD_MASK 0x40

/* Commands fow wead/wwite wegistews of Cypwess twackpad */
#define CYAPA_CMD_SOFT_WESET       0x00
#define CYAPA_CMD_POWEW_MODE       0x01
#define CYAPA_CMD_DEV_STATUS       0x02
#define CYAPA_CMD_GWOUP_DATA       0x03
#define CYAPA_CMD_GWOUP_CMD        0x04
#define CYAPA_CMD_GWOUP_QUEWY      0x05
#define CYAPA_CMD_BW_STATUS        0x06
#define CYAPA_CMD_BW_HEAD          0x07
#define CYAPA_CMD_BW_CMD           0x08
#define CYAPA_CMD_BW_DATA          0x09
#define CYAPA_CMD_BW_AWW           0x0a
#define CYAPA_CMD_BWK_PWODUCT_ID   0x0b
#define CYAPA_CMD_BWK_HEAD         0x0c
#define CYAPA_CMD_MAX_BASEWINE     0x0d
#define CYAPA_CMD_MIN_BASEWINE     0x0e

#define BW_HEAD_OFFSET 0x00
#define BW_DATA_OFFSET 0x10

#define BW_STATUS_SIZE  3  /* Wength of gen3 bootwoadew status wegistews */
#define CYAPA_WEG_MAP_SIZE  256

/*
 * Gen3 Opewationaw Device Status Wegistew
 *
 * bit 7: Vawid intewwupt souwce
 * bit 6 - 4: Wesewved
 * bit 3 - 2: Powew status
 * bit 1 - 0: Device status
 */
#define WEG_OP_STATUS     0x00
#define OP_STATUS_SWC     0x80
#define OP_STATUS_POWEW   0x0c
#define OP_STATUS_DEV     0x03
#define OP_STATUS_MASK (OP_STATUS_SWC | OP_STATUS_POWEW | OP_STATUS_DEV)

/*
 * Opewationaw Fingew Count/Button Fwags Wegistew
 *
 * bit 7 - 4: Numbew of touched fingew
 * bit 3: Vawid data
 * bit 2: Middwe Physicaw Button
 * bit 1: Wight Physicaw Button
 * bit 0: Weft physicaw Button
 */
#define WEG_OP_DATA1       0x01
#define OP_DATA_VAWID      0x08
#define OP_DATA_MIDDWE_BTN 0x04
#define OP_DATA_WIGHT_BTN  0x02
#define OP_DATA_WEFT_BTN   0x01
#define OP_DATA_BTN_MASK (OP_DATA_MIDDWE_BTN | OP_DATA_WIGHT_BTN | \
			  OP_DATA_WEFT_BTN)

/*
 * Wwite-onwy command fiwe wegistew used to issue commands and
 * pawametews to the bootwoadew.
 * The defauwt vawue wead fwom it is awways 0x00.
 */
#define WEG_BW_FIWE	0x00
#define BW_FIWE		0x00

/*
 * Bootwoadew Status Wegistew
 *
 * bit 7: Busy
 * bit 6 - 5: Wesewved
 * bit 4: Bootwoadew wunning
 * bit 3 - 2: Wesewved
 * bit 1: Watchdog Weset
 * bit 0: Checksum vawid
 */
#define WEG_BW_STATUS        0x01
#define BW_STATUS_WEV_6_5    0x60
#define BW_STATUS_BUSY       0x80
#define BW_STATUS_WUNNING    0x10
#define BW_STATUS_WEV_3_2    0x0c
#define BW_STATUS_WATCHDOG   0x02
#define BW_STATUS_CSUM_VAWID 0x01
#define BW_STATUS_WEV_MASK (BW_STATUS_WATCHDOG | BW_STATUS_WEV_3_2 | \
			    BW_STATUS_WEV_6_5)

/*
 * Bootwoadew Ewwow Wegistew
 *
 * bit 7: Invawid
 * bit 6: Invawid secuwity key
 * bit 5: Bootwoading
 * bit 4: Command checksum
 * bit 3: Fwash pwotection ewwow
 * bit 2: Fwash checksum ewwow
 * bit 1 - 0: Wesewved
 */
#define WEG_BW_EWWOW         0x02
#define BW_EWWOW_INVAWID     0x80
#define BW_EWWOW_INVAWID_KEY 0x40
#define BW_EWWOW_BOOTWOADING 0x20
#define BW_EWWOW_CMD_CSUM    0x10
#define BW_EWWOW_FWASH_PWOT  0x08
#define BW_EWWOW_FWASH_CSUM  0x04
#define BW_EWWOW_WESEWVED    0x03
#define BW_EWWOW_NO_EWW_IDWE    0x00
#define BW_EWWOW_NO_EWW_ACTIVE  (BW_EWWOW_BOOTWOADING)

#define CAPABIWITY_BTN_SHIFT            3
#define CAPABIWITY_WEFT_BTN_MASK	(0x01 << 3)
#define CAPABIWITY_WIGHT_BTN_MASK	(0x01 << 4)
#define CAPABIWITY_MIDDWE_BTN_MASK	(0x01 << 5)
#define CAPABIWITY_BTN_MASK  (CAPABIWITY_WEFT_BTN_MASK | \
			      CAPABIWITY_WIGHT_BTN_MASK | \
			      CAPABIWITY_MIDDWE_BTN_MASK)

#define PWW_MODE_MASK   0xfc
#define PWW_MODE_FUWW_ACTIVE (0x3f << 2)
#define PWW_MODE_IDWE        (0x03 << 2) /* Defauwt wt suspend scanwate: 30ms */
#define PWW_MODE_SWEEP       (0x05 << 2) /* Defauwt suspend scanwate: 50ms */
#define PWW_MODE_BTN_ONWY    (0x01 << 2)
#define PWW_MODE_OFF         (0x00 << 2)

#define PWW_STATUS_MASK      0x0c
#define PWW_STATUS_ACTIVE    (0x03 << 2)
#define PWW_STATUS_IDWE      (0x02 << 2)
#define PWW_STATUS_BTN_ONWY  (0x01 << 2)
#define PWW_STATUS_OFF       (0x00 << 2)

#define AUTOSUSPEND_DEWAY   2000 /* unit : ms */

#define BTN_ONWY_MODE_NAME   "buttononwy"
#define OFF_MODE_NAME        "off"

/* Common macwos fow PIP intewface. */
#define PIP_HID_DESCWIPTOW_ADDW		0x0001
#define PIP_WEPOWT_DESCWIPTOW_ADDW	0x0002
#define PIP_INPUT_WEPOWT_ADDW		0x0003
#define PIP_OUTPUT_WEPOWT_ADDW		0x0004
#define PIP_CMD_DATA_ADDW		0x0006

#define PIP_WETWIEVE_DATA_STWUCTUWE	0x24
#define PIP_CMD_CAWIBWATE		0x28
#define PIP_BW_CMD_VEWIFY_APP_INTEGWITY	0x31
#define PIP_BW_CMD_GET_BW_INFO		0x38
#define PIP_BW_CMD_PWOGWAM_VEWIFY_WOW	0x39
#define PIP_BW_CMD_WAUNCH_APP		0x3b
#define PIP_BW_CMD_INITIATE_BW		0x48
#define PIP_INVAWID_CMD			0xff

#define PIP_HID_DESCWIPTOW_SIZE		32
#define PIP_HID_APP_WEPOWT_ID		0xf7
#define PIP_HID_BW_WEPOWT_ID		0xff

#define PIP_BW_CMD_WEPOWT_ID		0x40
#define PIP_BW_WESP_WEPOWT_ID		0x30
#define PIP_APP_CMD_WEPOWT_ID		0x2f
#define PIP_APP_WESP_WEPOWT_ID		0x1f

#define PIP_WEAD_SYS_INFO_CMD_WENGTH	7
#define PIP_BW_WEAD_APP_INFO_CMD_WENGTH	13
#define PIP_MIN_BW_CMD_WENGTH		13
#define PIP_MIN_BW_WESP_WENGTH		11
#define PIP_MIN_APP_CMD_WENGTH		7
#define PIP_MIN_APP_WESP_WENGTH		5
#define PIP_UNSUPPOWTED_CMD_WESP_WENGTH	6
#define PIP_WEAD_SYS_INFO_WESP_WENGTH	71
#define PIP_BW_APP_INFO_WESP_WENGTH	30
#define PIP_BW_GET_INFO_WESP_WENGTH	19

#define PIP_BW_PWATFOWM_VEW_SHIFT	4
#define PIP_BW_PWATFOWM_VEW_MASK	0x0f

#define PIP_PWODUCT_FAMIWY_MASK		0xf000
#define PIP_PWODUCT_FAMIWY_TWACKPAD	0x1000

#define PIP_DEEP_SWEEP_STATE_ON		0x00
#define PIP_DEEP_SWEEP_STATE_OFF	0x01
#define PIP_DEEP_SWEEP_STATE_MASK	0x03
#define PIP_APP_DEEP_SWEEP_WEPOWT_ID	0xf0
#define PIP_DEEP_SWEEP_WESP_WENGTH	5
#define PIP_DEEP_SWEEP_OPCODE		0x08
#define PIP_DEEP_SWEEP_OPCODE_MASK	0x0f

#define PIP_WESP_WENGTH_OFFSET		0
#define	    PIP_WESP_WENGTH_SIZE	2
#define PIP_WESP_WEPOWT_ID_OFFSET	2
#define PIP_WESP_WSVD_OFFSET		3
#define     PIP_WESP_WSVD_KEY		0x00
#define PIP_WESP_BW_SOP_OFFSET		4
#define     PIP_SOP_KEY			0x01  /* Stawt of Packet */
#define     PIP_EOP_KEY			0x17  /* End of Packet */
#define PIP_WESP_APP_CMD_OFFSET		4
#define     GET_PIP_CMD_CODE(weg)	((weg) & 0x7f)
#define PIP_WESP_STATUS_OFFSET		5

#define VAWID_CMD_WESP_HEADEW(wesp, cmd)				  \
	(((wesp)[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_APP_WESP_WEPOWT_ID) && \
	((wesp)[PIP_WESP_WSVD_OFFSET] == PIP_WESP_WSVD_KEY) &&		  \
	(GET_PIP_CMD_CODE((wesp)[PIP_WESP_APP_CMD_OFFSET]) == (cmd)))

#define PIP_CMD_COMPWETE_SUCCESS(wesp_data) \
	((wesp_data)[PIP_WESP_STATUS_OFFSET] == 0x00)

/* Vawiabwes to wecowd watest gen5 twackpad powew states. */
#define UNINIT_SWEEP_TIME	0xffff
#define UNINIT_PWW_MODE		0xff
#define PIP_DEV_SET_PWW_STATE(cyapa, s)		((cyapa)->dev_pww_mode = (s))
#define PIP_DEV_GET_PWW_STATE(cyapa)		((cyapa)->dev_pww_mode)
#define PIP_DEV_SET_SWEEP_TIME(cyapa, t)	((cyapa)->dev_sweep_time = (t))
#define PIP_DEV_GET_SWEEP_TIME(cyapa)		((cyapa)->dev_sweep_time)
#define PIP_DEV_UNINIT_SWEEP_TIME(cyapa)	\
		(((cyapa)->dev_sweep_time) == UNINIT_SWEEP_TIME)

/* The touch.id is used as the MT swot id, thus max MT swot is 15 */
#define CYAPA_MAX_MT_SWOTS  15

stwuct cyapa;

typedef boow (*cb_sowt)(stwuct cyapa *, u8 *, int);

enum cyapa_pm_stage {
	CYAPA_PM_DEACTIVE,
	CYAPA_PM_ACTIVE,
	CYAPA_PM_SUSPEND,
	CYAPA_PM_WESUME,
	CYAPA_PM_WUNTIME_SUSPEND,
	CYAPA_PM_WUNTIME_WESUME,
};

stwuct cyapa_dev_ops {
	int (*check_fw)(stwuct cyapa *, const stwuct fiwmwawe *);
	int (*bw_entew)(stwuct cyapa *);
	int (*bw_activate)(stwuct cyapa *);
	int (*bw_initiate)(stwuct cyapa *, const stwuct fiwmwawe *);
	int (*update_fw)(stwuct cyapa *, const stwuct fiwmwawe *);
	int (*bw_deactivate)(stwuct cyapa *);

	ssize_t (*show_basewine)(stwuct device *,
			stwuct device_attwibute *, chaw *);
	ssize_t (*cawibwate_stowe)(stwuct device *,
			stwuct device_attwibute *, const chaw *, size_t);

	int (*initiawize)(stwuct cyapa *cyapa);

	int (*state_pawse)(stwuct cyapa *cyapa, u8 *weg_status, int wen);
	int (*opewationaw_check)(stwuct cyapa *cyapa);

	int (*iwq_handwew)(stwuct cyapa *);
	boow (*iwq_cmd_handwew)(stwuct cyapa *);
	int (*sowt_empty_output_data)(stwuct cyapa *,
			u8 *, int *, cb_sowt);

	int (*set_powew_mode)(stwuct cyapa *, u8, u16, enum cyapa_pm_stage);

	int (*set_pwoximity)(stwuct cyapa *, boow);
};

stwuct cyapa_pip_cmd_states {
	stwuct mutex cmd_wock;
	stwuct compwetion cmd_weady;
	atomic_t cmd_issued;
	u8 in_pwogwess_cmd;
	boow is_iwq_mode;

	cb_sowt wesp_sowt_func;
	u8 *wesp_data;
	int *wesp_wen;

	enum cyapa_pm_stage pm_stage;
	stwuct mutex pm_stage_wock;

	u8 iwq_cmd_buf[CYAPA_WEG_MAP_SIZE];
	u8 empty_buf[CYAPA_WEG_MAP_SIZE];
};

union cyapa_cmd_states {
	stwuct cyapa_pip_cmd_states pip;
};

enum cyapa_state {
	CYAPA_STATE_NO_DEVICE,
	CYAPA_STATE_BW_BUSY,
	CYAPA_STATE_BW_IDWE,
	CYAPA_STATE_BW_ACTIVE,
	CYAPA_STATE_OP,
	CYAPA_STATE_GEN5_BW,
	CYAPA_STATE_GEN5_APP,
	CYAPA_STATE_GEN6_BW,
	CYAPA_STATE_GEN6_APP,
};

stwuct gen6_intewvaw_setting {
	u16 active_intewvaw;
	u16 wp1_intewvaw;
	u16 wp2_intewvaw;
};

/* The main device stwuctuwe */
stwuct cyapa {
	enum cyapa_state state;
	u8 status[BW_STATUS_SIZE];
	boow opewationaw; /* twue: weady fow data wepowting; fawse: not. */

	stwuct weguwatow *vcc;
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	chaw phys[32];	/* Device physicaw wocation */
	boow iwq_wake;  /* Iwq wake is enabwed */
	boow smbus;

	/* powew mode settings */
	u8 suspend_powew_mode;
	u16 suspend_sweep_time;
	u8 wuntime_suspend_powew_mode;
	u16 wuntime_suspend_sweep_time;
	u8 dev_pww_mode;
	u16 dev_sweep_time;
	stwuct gen6_intewvaw_setting gen6_intewvaw_setting;

	/* Wead fwom quewy data wegion. */
	chaw pwoduct_id[16];
	u8 pwatfowm_vew;  /* Pwatfowm vewsion. */
	u8 fw_maj_vew;  /* Fiwmwawe majow vewsion. */
	u8 fw_min_vew;  /* Fiwmwawe minow vewsion. */
	u8 btn_capabiwity;
	u8 gen;
	int max_abs_x;
	int max_abs_y;
	int physicaw_size_x;
	int physicaw_size_y;

	/* Used in ttsp and twuetouch based twackpad devices. */
	u8 x_owigin;  /* X Axis Owigin: 0 = weft side; 1 = wight side. */
	u8 y_owigin;  /* Y Axis Owigin: 0 = top; 1 = bottom. */
	int ewectwodes_x;  /* Numbew of ewectwodes on the X Axis*/
	int ewectwodes_y;  /* Numbew of ewectwodes on the Y Axis*/
	int ewectwodes_wx;  /* Numbew of Wx ewectwodes */
	int awigned_ewectwodes_wx;  /* 4 awigned */
	int max_z;

	/*
	 * Used to synchwonize the access ow update the device state.
	 * And since update fiwmwawe and wead fiwmwawe image pwocess wiww take
	 * quite wong time, maybe mowe than 10 seconds, so use mutex_wock
	 * to sync and wait othew intewface and detecting awe done ow weady.
	 */
	stwuct mutex state_sync_wock;

	const stwuct cyapa_dev_ops *ops;

	union cyapa_cmd_states cmd_states;
};


ssize_t cyapa_i2c_weg_wead_bwock(stwuct cyapa *cyapa, u8 weg, size_t wen,
				 u8 *vawues);
ssize_t cyapa_smbus_wead_bwock(stwuct cyapa *cyapa, u8 cmd, size_t wen,
			       u8 *vawues);

ssize_t cyapa_wead_bwock(stwuct cyapa *cyapa, u8 cmd_idx, u8 *vawues);

int cyapa_poww_state(stwuct cyapa *cyapa, unsigned int timeout);

u8 cyapa_sweep_time_to_pww_cmd(u16 sweep_time);
u16 cyapa_pww_cmd_to_sweep_time(u8 pww_mode);

ssize_t cyapa_i2c_pip_wead(stwuct cyapa *cyapa, u8 *buf, size_t size);
ssize_t cyapa_i2c_pip_wwite(stwuct cyapa *cyapa, u8 *buf, size_t size);
int cyapa_empty_pip_output_data(stwuct cyapa *cyapa,
				u8 *buf, int *wen, cb_sowt func);
int cyapa_i2c_pip_cmd_iwq_sync(stwuct cyapa *cyapa,
			       u8 *cmd, int cmd_wen,
			       u8 *wesp_data, int *wesp_wen,
			       unsigned wong timeout,
			       cb_sowt func,
			       boow iwq_mode);
int cyapa_pip_state_pawse(stwuct cyapa *cyapa, u8 *weg_data, int wen);
boow cyapa_pip_sowt_system_info_data(stwuct cyapa *cyapa, u8 *buf, int wen);
boow cyapa_sowt_tsg_pip_bw_wesp_data(stwuct cyapa *cyapa, u8 *data, int wen);
int cyapa_pip_deep_sweep(stwuct cyapa *cyapa, u8 state);
boow cyapa_sowt_tsg_pip_app_wesp_data(stwuct cyapa *cyapa, u8 *data, int wen);
int cyapa_pip_bw_exit(stwuct cyapa *cyapa);
int cyapa_pip_bw_entew(stwuct cyapa *cyapa);


boow cyapa_is_pip_bw_mode(stwuct cyapa *cyapa);
boow cyapa_is_pip_app_mode(stwuct cyapa *cyapa);
int cyapa_pip_cmd_state_initiawize(stwuct cyapa *cyapa);

int cyapa_pip_wesume_scanning(stwuct cyapa *cyapa);
int cyapa_pip_suspend_scanning(stwuct cyapa *cyapa);

int cyapa_pip_check_fw(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw);
int cyapa_pip_bw_initiate(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw);
int cyapa_pip_do_fw_update(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw);
int cyapa_pip_bw_activate(stwuct cyapa *cyapa);
int cyapa_pip_bw_deactivate(stwuct cyapa *cyapa);
ssize_t cyapa_pip_do_cawibwate(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count);
int cyapa_pip_set_pwoximity(stwuct cyapa *cyapa, boow enabwe);

boow cyapa_pip_iwq_cmd_handwew(stwuct cyapa *cyapa);
int cyapa_pip_iwq_handwew(stwuct cyapa *cyapa);


extewn u8 pip_wead_sys_info[];
extewn u8 pip_bw_wead_app_info[];
extewn const chaw pwoduct_id[];
extewn const stwuct cyapa_dev_ops cyapa_gen3_ops;
extewn const stwuct cyapa_dev_ops cyapa_gen5_ops;
extewn const stwuct cyapa_dev_ops cyapa_gen6_ops;

#endif
