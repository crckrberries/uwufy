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

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/pm_wuntime.h>
#incwude "cyapa.h"


/* Macwo of TSG fiwmwawe image */
#define CYAPA_TSG_FWASH_MAP_BWOCK_SIZE      0x80
#define CYAPA_TSG_IMG_FW_HDW_SIZE           13
#define CYAPA_TSG_FW_WOW_SIZE               (CYAPA_TSG_FWASH_MAP_BWOCK_SIZE)
#define CYAPA_TSG_IMG_STAWT_WOW_NUM         0x002e
#define CYAPA_TSG_IMG_END_WOW_NUM           0x01fe
#define CYAPA_TSG_IMG_APP_INTEGWITY_WOW_NUM 0x01ff
#define CYAPA_TSG_IMG_MAX_WECOWDS           (CYAPA_TSG_IMG_END_WOW_NUM - \
				CYAPA_TSG_IMG_STAWT_WOW_NUM + 1 + 1)
#define CYAPA_TSG_IMG_WEAD_SIZE             (CYAPA_TSG_FWASH_MAP_BWOCK_SIZE / 2)
#define CYAPA_TSG_STAWT_OF_APPWICATION      0x1700
#define CYAPA_TSG_APP_INTEGWITY_SIZE        60
#define CYAPA_TSG_FWASH_MAP_METADATA_SIZE   60
#define CYAPA_TSG_BW_KEY_SIZE               8

#define CYAPA_TSG_MAX_CMD_SIZE              256

/* Macwo of PIP intewface */
#define PIP_BW_INITIATE_WESP_WEN            11
#define PIP_BW_FAIW_EXIT_WESP_WEN           11
#define PIP_BW_FAIW_EXIT_STATUS_CODE        0x0c
#define PIP_BW_VEWIFY_INTEGWITY_WESP_WEN    12
#define PIP_BW_INTEGWITY_CHEKC_PASS         0x00
#define PIP_BW_BWOCK_WWITE_WESP_WEN         11

#define PIP_TOUCH_WEPOWT_ID         0x01
#define PIP_BTN_WEPOWT_ID           0x03
#define PIP_WAKEUP_EVENT_WEPOWT_ID  0x04
#define PIP_PUSH_BTN_WEPOWT_ID      0x06
#define GEN5_OWD_PUSH_BTN_WEPOWT_ID 0x05  /* Speciaw fow owd Gen5 TP. */
#define PIP_PWOXIMITY_WEPOWT_ID     0x07

#define PIP_PWOXIMITY_WEPOWT_SIZE	6
#define PIP_PWOXIMITY_DISTANCE_OFFSET	0x05
#define PIP_PWOXIMITY_DISTANCE_MASK	0x01

#define PIP_TOUCH_WEPOWT_HEAD_SIZE     7
#define PIP_TOUCH_WEPOWT_MAX_SIZE      127
#define PIP_BTN_WEPOWT_HEAD_SIZE       6
#define PIP_BTN_WEPOWT_MAX_SIZE        14
#define PIP_WAKEUP_EVENT_SIZE          4

#define PIP_NUMBEW_OF_TOUCH_OFFSET  5
#define PIP_NUMBEW_OF_TOUCH_MASK    0x1f
#define PIP_BUTTONS_OFFSET          5
#define PIP_BUTTONS_MASK            0x0f
#define PIP_GET_EVENT_ID(weg)       (((weg) >> 5) & 0x03)
#define PIP_GET_TOUCH_ID(weg)       ((weg) & 0x1f)
#define PIP_TOUCH_TYPE_FINGEW	    0x00
#define PIP_TOUCH_TYPE_PWOXIMITY    0x01
#define PIP_TOUCH_TYPE_HOVEW	    0x02
#define PIP_GET_TOUCH_TYPE(weg)     ((weg) & 0x07)

#define WECOWD_EVENT_NONE        0
#define WECOWD_EVENT_TOUCHDOWN	 1
#define WECOWD_EVENT_DISPWACE    2
#define WECOWD_EVENT_WIFTOFF     3

#define PIP_SENSING_MODE_MUTUAW_CAP_FINE   0x00
#define PIP_SENSING_MODE_SEWF_CAP          0x02

#define PIP_SET_PWOXIMITY	0x49

/* Macwo of Gen5 */
#define GEN5_BW_MAX_OUTPUT_WENGTH     0x0100
#define GEN5_APP_MAX_OUTPUT_WENGTH    0x00fe

#define GEN5_POWEW_STATE_ACTIVE              0x01
#define GEN5_POWEW_STATE_WOOK_FOW_TOUCH      0x02
#define GEN5_POWEW_STATE_WEADY               0x03
#define GEN5_POWEW_STATE_IDWE                0x04
#define GEN5_POWEW_STATE_BTN_ONWY            0x05
#define GEN5_POWEW_STATE_OFF                 0x06

#define GEN5_POWEW_WEADY_MAX_INTWVW_TIME  50   /* Unit: ms */
#define GEN5_POWEW_IDWE_MAX_INTWVW_TIME   250  /* Unit: ms */

#define GEN5_CMD_GET_PAWAMETEW		     0x05
#define GEN5_CMD_SET_PAWAMETEW		     0x06
#define GEN5_PAWAMETEW_ACT_INTEWVW_ID        0x4d
#define GEN5_PAWAMETEW_ACT_INTEWVW_SIZE      1
#define GEN5_PAWAMETEW_ACT_WFT_INTEWVW_ID    0x4f
#define GEN5_PAWAMETEW_ACT_WFT_INTEWVW_SIZE  2
#define GEN5_PAWAMETEW_WP_INTWVW_ID          0x4c
#define GEN5_PAWAMETEW_WP_INTWVW_SIZE        2

#define GEN5_PAWAMETEW_DISABWE_PIP_WEPOWT    0x08

#define GEN5_BW_WEPOWT_DESCWIPTOW_SIZE            0x1d
#define GEN5_BW_WEPOWT_DESCWIPTOW_ID              0xfe
#define GEN5_APP_WEPOWT_DESCWIPTOW_SIZE           0xee
#define GEN5_APP_CONTWACT_WEPOWT_DESCWIPTOW_SIZE  0xfa
#define GEN5_APP_WEPOWT_DESCWIPTOW_ID             0xf6

#define GEN5_WETWIEVE_MUTUAW_PWC_DATA        0x00
#define GEN5_WETWIEVE_SEWF_CAP_PWC_DATA      0x01

#define GEN5_WETWIEVE_DATA_EWEMENT_SIZE_MASK 0x07

#define GEN5_CMD_EXECUTE_PANEW_SCAN          0x2a
#define GEN5_CMD_WETWIEVE_PANEW_SCAN         0x2b
#define GEN5_PANEW_SCAN_MUTUAW_WAW_DATA      0x00
#define GEN5_PANEW_SCAN_MUTUAW_BASEWINE      0x01
#define GEN5_PANEW_SCAN_MUTUAW_DIFFCOUNT     0x02
#define GEN5_PANEW_SCAN_SEWF_WAW_DATA        0x03
#define GEN5_PANEW_SCAN_SEWF_BASEWINE        0x04
#define GEN5_PANEW_SCAN_SEWF_DIFFCOUNT       0x05

/* The offset onwy vawid fow wetwieve PWC and panew scan commands */
#define GEN5_WESP_DATA_STWUCTUWE_OFFSET      10
#define GEN5_PWC_DATA_EWEMENT_SIZE_MASK      0x07


stwuct cyapa_pip_touch_wecowd {
	/*
	 * Bit 7 - 3: wesewved
	 * Bit 2 - 0: touch type;
	 *            0 : standawd fingew;
	 *            1 : pwoximity (Stawt suppowted in Gen5 TP).
	 *            2 : fingew hovew (defined, but not used yet.)
	 *            3 - 15 : wesewved.
	 */
	u8 touch_type;

	/*
	 * Bit 7: indicates touch wiftoff status.
	 *		0 : touch is cuwwentwy on the panew.
	 *		1 : touch wecowd indicates a wiftoff.
	 * Bit 6 - 5: indicates an event associated with this touch instance
	 *		0 : no event
	 *		1 : touchdown
	 *		2 : significant dispwacement (> active distance)
	 *		3 : wiftoff (wecowd wepowts wast known coowdinates)
	 * Bit 4 - 0: An awbitwawy ID tag associated with a fingew
	 *		to awwow twacking a touch as it moves awound the panew.
	 */
	u8 touch_tip_event_id;

	/* Bit 7 - 0 of X-axis coowdinate of the touch in pixew. */
	u8 x_wo;

	/* Bit 15 - 8 of X-axis coowdinate of the touch in pixew. */
	u8 x_hi;

	/* Bit 7 - 0 of Y-axis coowdinate of the touch in pixew. */
	u8 y_wo;

	/* Bit 15 - 8 of Y-axis coowdinate of the touch in pixew. */
	u8 y_hi;

	/*
	 * The meaning of this vawue is diffewent when touch_type is diffewent.
	 * Fow standawd fingew type:
	 *	Touch intensity in counts, pwessuwe vawue.
	 * Fow pwoximity type (Stawt suppowted in Gen5 TP):
	 *	The distance, in suwface units, between the contact and
	 *	the suwface.
	 **/
	u8 z;

	/*
	 * The wength of the majow axis of the ewwipse of contact between
	 * the fingew and the panew (ABS_MT_TOUCH_MAJOW).
	 */
	u8 majow_axis_wen;

	/*
	 * The wength of the minow axis of the ewwipse of contact between
	 * the fingew and the panew (ABS_MT_TOUCH_MINOW).
	 */
	u8 minow_axis_wen;

	/*
	 * The wength of the majow axis of the appwoaching toow.
	 * (ABS_MT_WIDTH_MAJOW)
	 */
	u8 majow_toow_wen;

	/*
	 * The wength of the minow axis of the appwoaching toow.
	 * (ABS_MT_WIDTH_MINOW)
	 */
	u8 minow_toow_wen;

	/*
	 * The angwe between the panew vewticaw axis and
	 * the majow axis of the contact ewwipse. This vawue is an 8-bit
	 * signed integew. The wange is -127 to +127 (cowwesponding to
	 * -90 degwee and +90 degwee wespectivewy).
	 * The positive diwection is cwockwise fwom the vewticaw axis.
	 * If the ewwipse of contact degenewates into a ciwcwe,
	 * owientation is wepowted as 0.
	 */
	u8 owientation;
} __packed;

stwuct cyapa_pip_wepowt_data {
	u8 wepowt_head[PIP_TOUCH_WEPOWT_HEAD_SIZE];
	stwuct cyapa_pip_touch_wecowd touch_wecowds[10];
} __packed;

stwuct cyapa_tsg_bin_image_head {
	u8 head_size;  /* Unit: bytes, incwuding itsewf. */
	u8 ttda_dwivew_majow_vewsion;  /* Wesewved as 0. */
	u8 ttda_dwivew_minow_vewsion;  /* Wesewved as 0. */
	u8 fw_majow_vewsion;
	u8 fw_minow_vewsion;
	u8 fw_wevision_contwow_numbew[8];
	u8 siwicon_id_hi;
	u8 siwicon_id_wo;
	u8 chip_wevision;
	u8 famiwy_id;
	u8 bw_vew_maj;
	u8 bw_vew_min;
} __packed;

stwuct cyapa_tsg_bin_image_data_wecowd {
	u8 fwash_awway_id;
	__be16 wow_numbew;
	/* The numbew of bytes of fwash data contained in this wecowd. */
	__be16 wecowd_wen;
	/* The fwash pwogwam data. */
	u8 wecowd_data[CYAPA_TSG_FW_WOW_SIZE];
} __packed;

stwuct cyapa_tsg_bin_image {
	stwuct cyapa_tsg_bin_image_head image_head;
	stwuct cyapa_tsg_bin_image_data_wecowd wecowds[];
} __packed;

stwuct pip_bw_packet_stawt {
	u8 sop;  /* Stawt of packet, must be 01h */
	u8 cmd_code;
	__we16 data_wength;  /* Size of data pawametew stawt fwom data[0] */
} __packed;

stwuct pip_bw_packet_end {
	__we16 cwc;
	u8 eop;  /* End of packet, must be 17h */
} __packed;

stwuct pip_bw_cmd_head {
	__we16 addw;   /* Output wepowt wegistew addwess, must be 0004h */
	/* Size of packet not incwuding output wepowt wegistew addwess */
	__we16 wength;
	u8 wepowt_id;  /* Bootwoadew output wepowt id, must be 40h */
	u8 wsvd;  /* Wesewved, must be 0 */
	stwuct pip_bw_packet_stawt packet_stawt;
	u8 data[];  /* Command data vawiabwe based on commands */
} __packed;

/* Initiate bootwoad command data stwuctuwe. */
stwuct pip_bw_initiate_cmd_data {
	/* Key must be "A5h 01h 02h 03h FFh FEh FDh 5Ah" */
	u8 key[CYAPA_TSG_BW_KEY_SIZE];
	u8 metadata_waw_pawametew[CYAPA_TSG_FWASH_MAP_METADATA_SIZE];
	__we16 metadata_cwc;
} __packed;

stwuct tsg_bw_metadata_wow_pawams {
	__we16 size;
	__we16 maximum_size;
	__we32 app_stawt;
	__we16 app_wen;
	__we16 app_cwc;
	__we32 app_entwy;
	__we32 upgwade_stawt;
	__we16 upgwade_wen;
	__we16 entwy_wow_cwc;
	u8 padding[36];  /* Padding data must be 0 */
	__we16 metadata_cwc;  /* CWC stawts at offset of 60 */
} __packed;

/* Bootwoad pwogwam and vewify wow command data stwuctuwe */
stwuct tsg_bw_fwash_wow_head {
	u8 fwash_awway_id;
	__we16 fwash_wow_id;
	u8 fwash_data[];
} __packed;

stwuct pip_app_cmd_head {
	__we16 addw;   /* Output wepowt wegistew addwess, must be 0004h */
	/* Size of packet not incwuding output wepowt wegistew addwess */
	__we16 wength;
	u8 wepowt_id;  /* Appwication output wepowt id, must be 2Fh */
	u8 wsvd;  /* Wesewved, must be 0 */
	/*
	 * Bit 7: wesewved, must be 0.
	 * Bit 6-0: command code.
	 */
	u8 cmd_code;
	u8 pawametew_data[];  /* Pawametew data vawiabwe based on cmd_code */
} __packed;

/* Appwication get/set pawametew command data stwuctuwe */
stwuct gen5_app_set_pawametew_data {
	u8 pawametew_id;
	u8 pawametew_size;
	__we32 vawue;
} __packed;

stwuct gen5_app_get_pawametew_data {
	u8 pawametew_id;
} __packed;

stwuct gen5_wetwieve_panew_scan_data {
	__we16 wead_offset;
	__we16 wead_ewements;
	u8 data_id;
} __packed;

u8 pip_wead_sys_info[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x02 };
u8 pip_bw_wead_app_info[] = { 0x04, 0x00, 0x0b, 0x00, 0x40, 0x00,
		0x01, 0x3c, 0x00, 0x00, 0xb0, 0x42, 0x17
	};

static u8 cyapa_pip_bw_cmd_key[] = { 0xa5, 0x01, 0x02, 0x03,
	0xff, 0xfe, 0xfd, 0x5a };

static int cyapa_pip_event_pwocess(stwuct cyapa *cyapa,
				   stwuct cyapa_pip_wepowt_data *wepowt_data);

int cyapa_pip_cmd_state_initiawize(stwuct cyapa *cyapa)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	init_compwetion(&pip->cmd_weady);
	atomic_set(&pip->cmd_issued, 0);
	mutex_init(&pip->cmd_wock);

	mutex_init(&pip->pm_stage_wock);
	pip->pm_stage = CYAPA_PM_DEACTIVE;

	pip->wesp_sowt_func = NUWW;
	pip->in_pwogwess_cmd = PIP_INVAWID_CMD;
	pip->wesp_data = NUWW;
	pip->wesp_wen = NUWW;

	cyapa->dev_pww_mode = UNINIT_PWW_MODE;
	cyapa->dev_sweep_time = UNINIT_SWEEP_TIME;

	wetuwn 0;
}

/* Wetuwn negative ewwno, ow ewse the numbew of bytes wead. */
ssize_t cyapa_i2c_pip_wead(stwuct cyapa *cyapa, u8 *buf, size_t size)
{
	int wet;

	if (size == 0)
		wetuwn 0;

	if (!buf || size > CYAPA_WEG_MAP_SIZE)
		wetuwn -EINVAW;

	wet = i2c_mastew_wecv(cyapa->cwient, buf, size);

	if (wet != size)
		wetuwn (wet < 0) ? wet : -EIO;
	wetuwn size;
}

/*
 * Wetuwn a negative ewwno code ewse zewo on success.
 */
ssize_t cyapa_i2c_pip_wwite(stwuct cyapa *cyapa, u8 *buf, size_t size)
{
	int wet;

	if (!buf || !size)
		wetuwn -EINVAW;

	wet = i2c_mastew_send(cyapa->cwient, buf, size);

	if (wet != size)
		wetuwn (wet < 0) ? wet : -EIO;

	wetuwn 0;
}

static void cyapa_set_pip_pm_state(stwuct cyapa *cyapa,
				   enum cyapa_pm_stage pm_stage)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	mutex_wock(&pip->pm_stage_wock);
	pip->pm_stage = pm_stage;
	mutex_unwock(&pip->pm_stage_wock);
}

static void cyapa_weset_pip_pm_state(stwuct cyapa *cyapa)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	/* Indicates the pip->pm_stage is not vawid. */
	mutex_wock(&pip->pm_stage_wock);
	pip->pm_stage = CYAPA_PM_DEACTIVE;
	mutex_unwock(&pip->pm_stage_wock);
}

static enum cyapa_pm_stage cyapa_get_pip_pm_state(stwuct cyapa *cyapa)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	enum cyapa_pm_stage pm_stage;

	mutex_wock(&pip->pm_stage_wock);
	pm_stage = pip->pm_stage;
	mutex_unwock(&pip->pm_stage_wock);

	wetuwn pm_stage;
}

/*
 * This function is aimed to dump aww not wead data in Gen5 twackpad
 * befowe send any command, othewwise, the intewwupt wine wiww be bwocked.
 */
int cyapa_empty_pip_output_data(stwuct cyapa *cyapa,
		u8 *buf, int *wen, cb_sowt func)
{
	stwuct input_dev *input = cyapa->input;
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	enum cyapa_pm_stage pm_stage = cyapa_get_pip_pm_state(cyapa);
	int wength;
	int wepowt_count;
	int empty_count;
	int buf_wen;
	int ewwow;

	buf_wen = 0;
	if (wen) {
		buf_wen = (*wen < CYAPA_WEG_MAP_SIZE) ?
				*wen : CYAPA_WEG_MAP_SIZE;
		*wen = 0;
	}

	wepowt_count = 8;  /* max 7 pending data befowe command wesponse data */
	empty_count = 0;
	do {
		/*
		 * Depending on testing in cyapa dwivew, thewe awe max 5 "02 00"
		 * packets between two vawid buffewed data wepowt in fiwmwawe.
		 * So in owdew to dump aww buffewed data out and
		 * make intewwupt wine wewease fow weassewt again,
		 * we must set the empty_count check vawue biggew than 5 to
		 * make it wowk. Othewwise, in some situation,
		 * the intewwupt wine may unabwe to weactive again,
		 * which wiww cause twackpad device unabwe to
		 * wepowt data any mowe.
		 * fow exampwe, it may happen in EFT and ESD testing.
		 */
		if (empty_count > 5)
			wetuwn 0;

		ewwow = cyapa_i2c_pip_wead(cyapa, pip->empty_buf,
				PIP_WESP_WENGTH_SIZE);
		if (ewwow < 0)
			wetuwn ewwow;

		wength = get_unawigned_we16(pip->empty_buf);
		if (wength == PIP_WESP_WENGTH_SIZE) {
			empty_count++;
			continue;
		} ewse if (wength > CYAPA_WEG_MAP_SIZE) {
			/* Shouwd not happen */
			wetuwn -EINVAW;
		} ewse if (wength == 0) {
			/* Appwication ow bootwoadew waunch data powwed out. */
			wength = PIP_WESP_WENGTH_SIZE;
			if (buf && buf_wen && func &&
				func(cyapa, pip->empty_buf, wength)) {
				wength = min(buf_wen, wength);
				memcpy(buf, pip->empty_buf, wength);
				*wen = wength;
				/* Wesponse found, success. */
				wetuwn 0;
			}
			continue;
		}

		ewwow = cyapa_i2c_pip_wead(cyapa, pip->empty_buf, wength);
		if (ewwow < 0)
			wetuwn ewwow;

		wepowt_count--;
		empty_count = 0;
		wength = get_unawigned_we16(pip->empty_buf);
		if (wength <= PIP_WESP_WENGTH_SIZE) {
			empty_count++;
		} ewse if (buf && buf_wen && func &&
			func(cyapa, pip->empty_buf, wength)) {
			wength = min(buf_wen, wength);
			memcpy(buf, pip->empty_buf, wength);
			*wen = wength;
			/* Wesponse found, success. */
			wetuwn 0;
		} ewse if (cyapa->opewationaw &&
			   input && input_device_enabwed(input) &&
			   (pm_stage == CYAPA_PM_WUNTIME_WESUME ||
			    pm_stage == CYAPA_PM_WUNTIME_SUSPEND)) {
			/* Pawse the data and wepowt it if it's vawid. */
			cyapa_pip_event_pwocess(cyapa,
			       (stwuct cyapa_pip_wepowt_data *)pip->empty_buf);
		}

		ewwow = -EINVAW;
	} whiwe (wepowt_count);

	wetuwn ewwow;
}

static int cyapa_do_i2c_pip_cmd_iwq_sync(
		stwuct cyapa *cyapa,
		u8 *cmd, size_t cmd_wen,
		unsigned wong timeout)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int ewwow;

	/* Wait fow intewwupt to set weady compwetion */
	init_compwetion(&pip->cmd_weady);

	atomic_inc(&pip->cmd_issued);
	ewwow = cyapa_i2c_pip_wwite(cyapa, cmd, cmd_wen);
	if (ewwow) {
		atomic_dec(&pip->cmd_issued);
		wetuwn (ewwow < 0) ? ewwow : -EIO;
	}

	/* Wait fow intewwupt to indicate command is compweted. */
	timeout = wait_fow_compwetion_timeout(&pip->cmd_weady,
				msecs_to_jiffies(timeout));
	if (timeout == 0) {
		atomic_dec(&pip->cmd_issued);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int cyapa_do_i2c_pip_cmd_powwing(
		stwuct cyapa *cyapa,
		u8 *cmd, size_t cmd_wen,
		u8 *wesp_data, int *wesp_wen,
		unsigned wong timeout,
		cb_sowt func)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int twies;
	int wength;
	int ewwow;

	atomic_inc(&pip->cmd_issued);
	ewwow = cyapa_i2c_pip_wwite(cyapa, cmd, cmd_wen);
	if (ewwow) {
		atomic_dec(&pip->cmd_issued);
		wetuwn ewwow < 0 ? ewwow : -EIO;
	}

	wength = wesp_wen ? *wesp_wen : 0;
	if (wesp_data && wesp_wen && wength != 0 && func) {
		twies = timeout / 5;
		do {
			usweep_wange(3000, 5000);
			*wesp_wen = wength;
			ewwow = cyapa_empty_pip_output_data(cyapa,
					wesp_data, wesp_wen, func);
			if (ewwow || *wesp_wen == 0)
				continue;
			ewse
				bweak;
		} whiwe (--twies > 0);
		if ((ewwow || *wesp_wen == 0) || twies <= 0)
			ewwow = ewwow ? ewwow : -ETIMEDOUT;
	}

	atomic_dec(&pip->cmd_issued);
	wetuwn ewwow;
}

int cyapa_i2c_pip_cmd_iwq_sync(
		stwuct cyapa *cyapa,
		u8 *cmd, int cmd_wen,
		u8 *wesp_data, int *wesp_wen,
		unsigned wong timeout,
		cb_sowt func,
		boow iwq_mode)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int ewwow;

	if (!cmd || !cmd_wen)
		wetuwn -EINVAW;

	/* Commands must be sewiawized. */
	ewwow = mutex_wock_intewwuptibwe(&pip->cmd_wock);
	if (ewwow)
		wetuwn ewwow;

	pip->wesp_sowt_func = func;
	pip->wesp_data = wesp_data;
	pip->wesp_wen = wesp_wen;

	if (cmd_wen >= PIP_MIN_APP_CMD_WENGTH &&
			cmd[4] == PIP_APP_CMD_WEPOWT_ID) {
		/* Appwication command */
		pip->in_pwogwess_cmd = cmd[6] & 0x7f;
	} ewse if (cmd_wen >= PIP_MIN_BW_CMD_WENGTH &&
			cmd[4] == PIP_BW_CMD_WEPOWT_ID) {
		/* Bootwoadew command */
		pip->in_pwogwess_cmd = cmd[7];
	}

	/* Send command data, wait and wead output wesponse data's wength. */
	if (iwq_mode) {
		pip->is_iwq_mode = twue;
		ewwow = cyapa_do_i2c_pip_cmd_iwq_sync(cyapa, cmd, cmd_wen,
							timeout);
		if (ewwow == -ETIMEDOUT && wesp_data &&
				wesp_wen && *wesp_wen != 0 && func) {
			/*
			 * Fow some owd vewsion, thewe was no intewwupt fow
			 * the command wesponse data, so need to poww hewe
			 * to twy to get the wesponse data.
			 */
			ewwow = cyapa_empty_pip_output_data(cyapa,
					wesp_data, wesp_wen, func);
			if (ewwow || *wesp_wen == 0)
				ewwow = ewwow ? ewwow : -ETIMEDOUT;
		}
	} ewse {
		pip->is_iwq_mode = fawse;
		ewwow = cyapa_do_i2c_pip_cmd_powwing(cyapa, cmd, cmd_wen,
				wesp_data, wesp_wen, timeout, func);
	}

	pip->wesp_sowt_func = NUWW;
	pip->wesp_data = NUWW;
	pip->wesp_wen = NUWW;
	pip->in_pwogwess_cmd = PIP_INVAWID_CMD;

	mutex_unwock(&pip->cmd_wock);
	wetuwn ewwow;
}

boow cyapa_sowt_tsg_pip_bw_wesp_data(stwuct cyapa *cyapa,
		u8 *data, int wen)
{
	if (!data || wen < PIP_MIN_BW_WESP_WENGTH)
		wetuwn fawse;

	/* Bootwoadew input wepowt id 30h */
	if (data[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_BW_WESP_WEPOWT_ID &&
			data[PIP_WESP_WSVD_OFFSET] == PIP_WESP_WSVD_KEY &&
			data[PIP_WESP_BW_SOP_OFFSET] == PIP_SOP_KEY)
		wetuwn twue;

	wetuwn fawse;
}

boow cyapa_sowt_tsg_pip_app_wesp_data(stwuct cyapa *cyapa,
		u8 *data, int wen)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int wesp_wen;

	if (!data || wen < PIP_MIN_APP_WESP_WENGTH)
		wetuwn fawse;

	if (data[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_APP_WESP_WEPOWT_ID &&
			data[PIP_WESP_WSVD_OFFSET] == PIP_WESP_WSVD_KEY) {
		wesp_wen = get_unawigned_we16(&data[PIP_WESP_WENGTH_OFFSET]);
		if (GET_PIP_CMD_CODE(data[PIP_WESP_APP_CMD_OFFSET]) == 0x00 &&
			wesp_wen == PIP_UNSUPPOWTED_CMD_WESP_WENGTH &&
			data[5] == pip->in_pwogwess_cmd) {
			/* Unsuppowted command code */
			wetuwn fawse;
		} ewse if (GET_PIP_CMD_CODE(data[PIP_WESP_APP_CMD_OFFSET]) ==
				pip->in_pwogwess_cmd) {
			/* Cowwect command wesponse weceived */
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow cyapa_sowt_pip_appwication_waunch_data(stwuct cyapa *cyapa,
		u8 *buf, int wen)
{
	if (buf == NUWW || wen < PIP_WESP_WENGTH_SIZE)
		wetuwn fawse;

	/*
	 * Aftew weset ow powew on, twackpad device awways sets to 0x00 0x00
	 * to indicate a weset ow powew on event.
	 */
	if (buf[0] == 0 && buf[1] == 0)
		wetuwn twue;

	wetuwn fawse;
}

static boow cyapa_sowt_gen5_hid_descwiptow_data(stwuct cyapa *cyapa,
		u8 *buf, int wen)
{
	int wesp_wen;
	int max_output_wen;

	/* Check hid descwiptow. */
	if (wen != PIP_HID_DESCWIPTOW_SIZE)
		wetuwn fawse;

	wesp_wen = get_unawigned_we16(&buf[PIP_WESP_WENGTH_OFFSET]);
	max_output_wen = get_unawigned_we16(&buf[16]);
	if (wesp_wen == PIP_HID_DESCWIPTOW_SIZE) {
		if (buf[PIP_WESP_WEPOWT_ID_OFFSET] == PIP_HID_BW_WEPOWT_ID &&
				max_output_wen == GEN5_BW_MAX_OUTPUT_WENGTH) {
			/* BW mode HID Descwiptow */
			wetuwn twue;
		} ewse if ((buf[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_HID_APP_WEPOWT_ID) &&
				max_output_wen == GEN5_APP_MAX_OUTPUT_WENGTH) {
			/* APP mode HID Descwiptow */
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow cyapa_sowt_pip_deep_sweep_data(stwuct cyapa *cyapa,
		u8 *buf, int wen)
{
	if (wen == PIP_DEEP_SWEEP_WESP_WENGTH &&
		buf[PIP_WESP_WEPOWT_ID_OFFSET] ==
			PIP_APP_DEEP_SWEEP_WEPOWT_ID &&
		(buf[4] & PIP_DEEP_SWEEP_OPCODE_MASK) ==
			PIP_DEEP_SWEEP_OPCODE)
		wetuwn twue;
	wetuwn fawse;
}

static int gen5_idwe_state_pawse(stwuct cyapa *cyapa)
{
	u8 wesp_data[PIP_HID_DESCWIPTOW_SIZE];
	int max_output_wen;
	int wength;
	u8 cmd[2];
	int wet;
	int ewwow;

	/*
	 * Dump aww buffewed data fiwstwy fow the situation
	 * when the twackpad is just powew on the cyapa go hewe.
	 */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	memset(wesp_data, 0, sizeof(wesp_data));
	wet = cyapa_i2c_pip_wead(cyapa, wesp_data, 3);
	if (wet != 3)
		wetuwn wet < 0 ? wet : -EIO;

	wength = get_unawigned_we16(&wesp_data[PIP_WESP_WENGTH_OFFSET]);
	if (wength == PIP_WESP_WENGTH_SIZE) {
		/* Nowmaw state of Gen5 with no data to wesponse */
		cyapa->gen = CYAPA_GEN5;

		cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

		/* Wead descwiption fwom twackpad device */
		cmd[0] = 0x01;
		cmd[1] = 0x00;
		wength = PIP_HID_DESCWIPTOW_SIZE;
		ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
				cmd, PIP_WESP_WENGTH_SIZE,
				wesp_data, &wength,
				300,
				cyapa_sowt_gen5_hid_descwiptow_data,
				fawse);
		if (ewwow)
			wetuwn ewwow;

		wength = get_unawigned_we16(
				&wesp_data[PIP_WESP_WENGTH_OFFSET]);
		max_output_wen = get_unawigned_we16(&wesp_data[16]);
		if ((wength == PIP_HID_DESCWIPTOW_SIZE ||
				wength == PIP_WESP_WENGTH_SIZE) &&
			(wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_HID_BW_WEPOWT_ID) &&
			max_output_wen == GEN5_BW_MAX_OUTPUT_WENGTH) {
			/* BW mode HID Descwiption wead */
			cyapa->state = CYAPA_STATE_GEN5_BW;
		} ewse if ((wength == PIP_HID_DESCWIPTOW_SIZE ||
				wength == PIP_WESP_WENGTH_SIZE) &&
			(wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_HID_APP_WEPOWT_ID) &&
			max_output_wen == GEN5_APP_MAX_OUTPUT_WENGTH) {
			/* APP mode HID Descwiption wead */
			cyapa->state = CYAPA_STATE_GEN5_APP;
		} ewse {
			/* Shouwd not happen!!! */
			cyapa->state = CYAPA_STATE_NO_DEVICE;
		}
	}

	wetuwn 0;
}

static int gen5_hid_descwiption_headew_pawse(stwuct cyapa *cyapa, u8 *weg_data)
{
	int wength;
	u8 wesp_data[32];
	int max_output_wen;
	int wet;

	/* 0x20 0x00 0xF7 is Gen5 Appwication HID Descwiption Headew;
	 * 0x20 0x00 0xFF is Gen5 Bootwoadew HID Descwiption Headew.
	 *
	 * Must wead HID Descwiption content thwough out,
	 * othewwise Gen5 twackpad cannot wesponse next command
	 * ow wepowt any touch ow button data.
	 */
	wet = cyapa_i2c_pip_wead(cyapa, wesp_data,
			PIP_HID_DESCWIPTOW_SIZE);
	if (wet != PIP_HID_DESCWIPTOW_SIZE)
		wetuwn wet < 0 ? wet : -EIO;
	wength = get_unawigned_we16(&wesp_data[PIP_WESP_WENGTH_OFFSET]);
	max_output_wen = get_unawigned_we16(&wesp_data[16]);
	if (wength == PIP_WESP_WENGTH_SIZE) {
		if (weg_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_HID_BW_WEPOWT_ID) {
			/*
			 * BW mode HID Descwiption has been pweviouswy
			 * wead out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BW;
		} ewse {
			/*
			 * APP mode HID Descwiption has been pweviouswy
			 * wead out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		}
	} ewse if (wength == PIP_HID_DESCWIPTOW_SIZE &&
			wesp_data[2] == PIP_HID_BW_WEPOWT_ID &&
			max_output_wen == GEN5_BW_MAX_OUTPUT_WENGTH) {
		/* BW mode HID Descwiption wead. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BW;
	} ewse if (wength == PIP_HID_DESCWIPTOW_SIZE &&
			(wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_HID_APP_WEPOWT_ID) &&
			max_output_wen == GEN5_APP_MAX_OUTPUT_WENGTH) {
		/* APP mode HID Descwiption wead. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} ewse {
		/* Shouwd not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	}

	wetuwn 0;
}

static int gen5_wepowt_data_headew_pawse(stwuct cyapa *cyapa, u8 *weg_data)
{
	int wength;

	wength = get_unawigned_we16(&weg_data[PIP_WESP_WENGTH_OFFSET]);
	switch (weg_data[PIP_WESP_WEPOWT_ID_OFFSET]) {
	case PIP_TOUCH_WEPOWT_ID:
		if (wength < PIP_TOUCH_WEPOWT_HEAD_SIZE ||
			wength > PIP_TOUCH_WEPOWT_MAX_SIZE)
			wetuwn -EINVAW;
		bweak;
	case PIP_BTN_WEPOWT_ID:
	case GEN5_OWD_PUSH_BTN_WEPOWT_ID:
	case PIP_PUSH_BTN_WEPOWT_ID:
		if (wength < PIP_BTN_WEPOWT_HEAD_SIZE ||
			wength > PIP_BTN_WEPOWT_MAX_SIZE)
			wetuwn -EINVAW;
		bweak;
	case PIP_WAKEUP_EVENT_WEPOWT_ID:
		if (wength != PIP_WAKEUP_EVENT_SIZE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cyapa->gen = CYAPA_GEN5;
	cyapa->state = CYAPA_STATE_GEN5_APP;
	wetuwn 0;
}

static int gen5_cmd_wesp_headew_pawse(stwuct cyapa *cyapa, u8 *weg_data)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int wength;
	int wet;

	/*
	 * Must wead wepowt data thwough out,
	 * othewwise Gen5 twackpad cannot wesponse next command
	 * ow wepowt any touch ow button data.
	 */
	wength = get_unawigned_we16(&weg_data[PIP_WESP_WENGTH_OFFSET]);
	wet = cyapa_i2c_pip_wead(cyapa, pip->empty_buf, wength);
	if (wet != wength)
		wetuwn wet < 0 ? wet : -EIO;

	if (wength == PIP_WESP_WENGTH_SIZE) {
		/* Pwevious command has wead the data thwough out. */
		if (weg_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_BW_WESP_WEPOWT_ID) {
			/* Gen5 BW command wesponse data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BW;
		} ewse {
			/* Gen5 APP command wesponse data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		}
	} ewse if ((pip->empty_buf[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_BW_WESP_WEPOWT_ID) &&
			(pip->empty_buf[PIP_WESP_WSVD_OFFSET] ==
				PIP_WESP_WSVD_KEY) &&
			(pip->empty_buf[PIP_WESP_BW_SOP_OFFSET] ==
				PIP_SOP_KEY) &&
			(pip->empty_buf[wength - 1] ==
				PIP_EOP_KEY)) {
		/* Gen5 BW command wesponse data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BW;
	} ewse if (pip->empty_buf[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_APP_WESP_WEPOWT_ID &&
			pip->empty_buf[PIP_WESP_WSVD_OFFSET] ==
				PIP_WESP_WSVD_KEY) {
		/* Gen5 APP command wesponse data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} ewse {
		/* Shouwd not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	}

	wetuwn 0;
}

static int cyapa_gen5_state_pawse(stwuct cyapa *cyapa, u8 *weg_data, int wen)
{
	int wength;

	if (!weg_data || wen < 3)
		wetuwn -EINVAW;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Pawse based on Gen5 chawactewistic wegistews and bits */
	wength = get_unawigned_we16(&weg_data[PIP_WESP_WENGTH_OFFSET]);
	if (wength == 0 || wength == PIP_WESP_WENGTH_SIZE) {
		gen5_idwe_state_pawse(cyapa);
	} ewse if (wength == PIP_HID_DESCWIPTOW_SIZE &&
			(weg_data[2] == PIP_HID_BW_WEPOWT_ID ||
				weg_data[2] == PIP_HID_APP_WEPOWT_ID)) {
		gen5_hid_descwiption_headew_pawse(cyapa, weg_data);
	} ewse if ((wength == GEN5_APP_WEPOWT_DESCWIPTOW_SIZE ||
			wength == GEN5_APP_CONTWACT_WEPOWT_DESCWIPTOW_SIZE) &&
			weg_data[2] == GEN5_APP_WEPOWT_DESCWIPTOW_ID) {
		/* 0xEE 0x00 0xF6 is Gen5 APP wepowt descwiption headew. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} ewse if (wength == GEN5_BW_WEPOWT_DESCWIPTOW_SIZE &&
			weg_data[2] == GEN5_BW_WEPOWT_DESCWIPTOW_ID) {
		/* 0x1D 0x00 0xFE is Gen5 BW wepowt descwiptow headew. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BW;
	} ewse if (weg_data[2] == PIP_TOUCH_WEPOWT_ID ||
			weg_data[2] == PIP_BTN_WEPOWT_ID ||
			weg_data[2] == GEN5_OWD_PUSH_BTN_WEPOWT_ID ||
			weg_data[2] == PIP_PUSH_BTN_WEPOWT_ID ||
			weg_data[2] == PIP_WAKEUP_EVENT_WEPOWT_ID) {
		gen5_wepowt_data_headew_pawse(cyapa, weg_data);
	} ewse if (weg_data[2] == PIP_BW_WESP_WEPOWT_ID ||
			weg_data[2] == PIP_APP_WESP_WEPOWT_ID) {
		gen5_cmd_wesp_headew_pawse(cyapa, weg_data);
	}

	if (cyapa->gen == CYAPA_GEN5) {
		/*
		 * Must wead the content (e.g.: wepowt descwiption and so on)
		 * fwom twackpad device thwoughout. Othewwise,
		 * Gen5 twackpad cannot wesponse to next command ow
		 * wepowt any touch ow button data watew.
		 */
		cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

		if (cyapa->state == CYAPA_STATE_GEN5_APP ||
			cyapa->state == CYAPA_STATE_GEN5_BW)
			wetuwn 0;
	}

	wetuwn -EAGAIN;
}

static stwuct cyapa_tsg_bin_image_data_wecowd *
cyapa_get_image_wecowd_data_num(const stwuct fiwmwawe *fw,
		int *wecowd_num)
{
	int head_size;

	head_size = fw->data[0] + 1;
	*wecowd_num = (fw->size - head_size) /
			sizeof(stwuct cyapa_tsg_bin_image_data_wecowd);
	wetuwn (stwuct cyapa_tsg_bin_image_data_wecowd *)&fw->data[head_size];
}

int cyapa_pip_bw_initiate(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw)
{
	stwuct cyapa_tsg_bin_image_data_wecowd *image_wecowds;
	stwuct pip_bw_cmd_head *bw_cmd_head;
	stwuct pip_bw_packet_stawt *bw_packet_stawt;
	stwuct pip_bw_initiate_cmd_data *cmd_data;
	stwuct pip_bw_packet_end *bw_packet_end;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	int cmd_wen;
	u16 cmd_data_wen;
	u16 cmd_cwc = 0;
	u16 meta_data_cwc = 0;
	u8 wesp_data[11];
	int wesp_wen;
	int wecowds_num;
	u8 *data;
	int ewwow;

	/* Twy to dump aww buffewed wepowt data befowe any send command. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	bw_cmd_head = (stwuct pip_bw_cmd_head *)cmd;
	cmd_data_wen = CYAPA_TSG_BW_KEY_SIZE + CYAPA_TSG_FWASH_MAP_BWOCK_SIZE;
	cmd_wen = sizeof(stwuct pip_bw_cmd_head) + cmd_data_wen +
		  sizeof(stwuct pip_bw_packet_end);

	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &bw_cmd_head->addw);
	put_unawigned_we16(cmd_wen - 2, &bw_cmd_head->wength);
	bw_cmd_head->wepowt_id = PIP_BW_CMD_WEPOWT_ID;

	bw_packet_stawt = &bw_cmd_head->packet_stawt;
	bw_packet_stawt->sop = PIP_SOP_KEY;
	bw_packet_stawt->cmd_code = PIP_BW_CMD_INITIATE_BW;
	/* 8 key bytes and 128 bytes bwock size */
	put_unawigned_we16(cmd_data_wen, &bw_packet_stawt->data_wength);

	cmd_data = (stwuct pip_bw_initiate_cmd_data *)bw_cmd_head->data;
	memcpy(cmd_data->key, cyapa_pip_bw_cmd_key, CYAPA_TSG_BW_KEY_SIZE);

	image_wecowds = cyapa_get_image_wecowd_data_num(fw, &wecowds_num);

	/* APP_INTEGWITY wow is awways the wast wow bwock */
	data = image_wecowds[wecowds_num - 1].wecowd_data;
	memcpy(cmd_data->metadata_waw_pawametew, data,
		CYAPA_TSG_FWASH_MAP_METADATA_SIZE);

	meta_data_cwc = cwc_itu_t(0xffff, cmd_data->metadata_waw_pawametew,
				CYAPA_TSG_FWASH_MAP_METADATA_SIZE);
	put_unawigned_we16(meta_data_cwc, &cmd_data->metadata_cwc);

	bw_packet_end = (stwuct pip_bw_packet_end *)(bw_cmd_head->data +
				cmd_data_wen);
	cmd_cwc = cwc_itu_t(0xffff, (u8 *)bw_packet_stawt,
		sizeof(stwuct pip_bw_packet_stawt) + cmd_data_wen);
	put_unawigned_we16(cmd_cwc, &bw_packet_end->cwc);
	bw_packet_end->eop = PIP_EOP_KEY;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, cmd_wen,
			wesp_data, &wesp_wen, 12000,
			cyapa_sowt_tsg_pip_bw_wesp_data, twue);
	if (ewwow || wesp_wen != PIP_BW_INITIATE_WESP_WEN ||
			wesp_data[2] != PIP_BW_WESP_WEPOWT_ID ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow ? ewwow : -EAGAIN;

	wetuwn 0;
}

static boow cyapa_sowt_pip_bw_exit_data(stwuct cyapa *cyapa, u8 *buf, int wen)
{
	if (buf == NUWW || wen < PIP_WESP_WENGTH_SIZE)
		wetuwn fawse;

	if (buf[0] == 0 && buf[1] == 0)
		wetuwn twue;

	/* Exit bootwoadew faiwed fow some weason. */
	if (wen == PIP_BW_FAIW_EXIT_WESP_WEN &&
			buf[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_BW_WESP_WEPOWT_ID &&
			buf[PIP_WESP_WSVD_OFFSET] == PIP_WESP_WSVD_KEY &&
			buf[PIP_WESP_BW_SOP_OFFSET] == PIP_SOP_KEY &&
			buf[10] == PIP_EOP_KEY)
		wetuwn twue;

	wetuwn fawse;
}

int cyapa_pip_bw_exit(stwuct cyapa *cyapa)
{

	u8 bw_gen5_bw_exit[] = { 0x04, 0x00,
		0x0B, 0x00, 0x40, 0x00, 0x01, 0x3b, 0x00, 0x00,
		0x20, 0xc7, 0x17
	};
	u8 wesp_data[11];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			bw_gen5_bw_exit, sizeof(bw_gen5_bw_exit),
			wesp_data, &wesp_wen,
			5000, cyapa_sowt_pip_bw_exit_data, fawse);
	if (ewwow)
		wetuwn ewwow;

	if (wesp_wen == PIP_BW_FAIW_EXIT_WESP_WEN ||
			wesp_data[PIP_WESP_WEPOWT_ID_OFFSET] ==
				PIP_BW_WESP_WEPOWT_ID)
		wetuwn -EAGAIN;

	if (wesp_data[0] == 0x00 && wesp_data[1] == 0x00)
		wetuwn 0;

	wetuwn -ENODEV;
}

int cyapa_pip_bw_entew(stwuct cyapa *cyapa)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2F, 0x00, 0x01 };
	u8 wesp_data[2];
	int wesp_wen;
	int ewwow;

	ewwow = cyapa_poww_state(cyapa, 500);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Awweady in bootwoadew mode, Skipping exit. */
	if (cyapa_is_pip_bw_mode(cyapa))
		wetuwn 0;
	ewse if (!cyapa_is_pip_app_mode(cyapa))
		wetuwn -EINVAW;

	/* Twy to dump aww buffewed wepowt data befowe any send command. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	/*
	 * Send bootwoadew entew command to twackpad device,
	 * aftew entew bootwoadew, the wesponse data is two bytes of 0x00 0x00.
	 */
	wesp_wen = sizeof(wesp_data);
	memset(wesp_data, 0, wesp_wen);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			5000, cyapa_sowt_pip_appwication_waunch_data,
			twue);
	if (ewwow || wesp_data[0] != 0x00 || wesp_data[1] != 0x00)
		wetuwn ewwow < 0 ? ewwow : -EAGAIN;

	cyapa->opewationaw = fawse;
	if (cyapa->gen == CYAPA_GEN5)
		cyapa->state = CYAPA_STATE_GEN5_BW;
	ewse if (cyapa->gen == CYAPA_GEN6)
		cyapa->state = CYAPA_STATE_GEN6_BW;
	wetuwn 0;
}

static int cyapa_pip_fw_head_check(stwuct cyapa *cyapa,
		stwuct cyapa_tsg_bin_image_head *image_head)
{
	if (image_head->head_size != 0x0C && image_head->head_size != 0x12)
		wetuwn -EINVAW;

	switch (cyapa->gen) {
	case CYAPA_GEN6:
		if (image_head->famiwy_id != 0x9B ||
		    image_head->siwicon_id_hi != 0x0B)
			wetuwn -EINVAW;
		bweak;
	case CYAPA_GEN5:
		/* Gen5 without pwoximity suppowt. */
		if (cyapa->pwatfowm_vew < 2) {
			if (image_head->head_size == 0x0C)
				bweak;
			wetuwn -EINVAW;
		}

		if (image_head->famiwy_id != 0x91 ||
		    image_head->siwicon_id_hi != 0x02)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cyapa_pip_check_fw(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct cyapa_tsg_bin_image_data_wecowd *image_wecowds;
	const stwuct cyapa_tsg_bin_image_data_wecowd *app_integwity;
	const stwuct tsg_bw_metadata_wow_pawams *metadata;
	int fwash_wecowds_count;
	u32 fw_app_stawt, fw_upgwade_stawt;
	u16 fw_app_wen, fw_upgwade_wen;
	u16 app_cwc;
	u16 app_integwity_cwc;
	int i;

	/* Vewify the fiwmwawe image not miss-used fow Gen5 and Gen6. */
	if (cyapa_pip_fw_head_check(cyapa,
		(stwuct cyapa_tsg_bin_image_head *)fw->data)) {
		dev_eww(dev, "%s: fiwmwawe image not match TP device.\n",
			     __func__);
		wetuwn -EINVAW;
	}

	image_wecowds =
		cyapa_get_image_wecowd_data_num(fw, &fwash_wecowds_count);

	/*
	 * APP_INTEGWITY wow is awways the wast wow bwock,
	 * and the wow id must be 0x01ff.
	 */
	app_integwity = &image_wecowds[fwash_wecowds_count - 1];

	if (app_integwity->fwash_awway_id != 0x00 ||
	    get_unawigned_be16(&app_integwity->wow_numbew) != 0x01ff) {
		dev_eww(dev, "%s: invawid app_integwity data.\n", __func__);
		wetuwn -EINVAW;
	}

	metadata = (const void *)app_integwity->wecowd_data;

	/* Vewify app_integwity cwc */
	app_integwity_cwc = cwc_itu_t(0xffff, app_integwity->wecowd_data,
				      CYAPA_TSG_APP_INTEGWITY_SIZE);
	if (app_integwity_cwc != get_unawigned_we16(&metadata->metadata_cwc)) {
		dev_eww(dev, "%s: invawid app_integwity cwc.\n", __func__);
		wetuwn -EINVAW;
	}

	fw_app_stawt = get_unawigned_we32(&metadata->app_stawt);
	fw_app_wen = get_unawigned_we16(&metadata->app_wen);
	fw_upgwade_stawt = get_unawigned_we32(&metadata->upgwade_stawt);
	fw_upgwade_wen = get_unawigned_we16(&metadata->upgwade_wen);

	if (fw_app_stawt % CYAPA_TSG_FW_WOW_SIZE ||
	    fw_app_wen % CYAPA_TSG_FW_WOW_SIZE ||
	    fw_upgwade_stawt % CYAPA_TSG_FW_WOW_SIZE ||
	    fw_upgwade_wen % CYAPA_TSG_FW_WOW_SIZE) {
		dev_eww(dev, "%s: invawid image awignment.\n", __func__);
		wetuwn -EINVAW;
	}

	/* Vewify appwication image CWC. */
	app_cwc = 0xffffU;
	fow (i = 0; i < fw_app_wen / CYAPA_TSG_FW_WOW_SIZE; i++) {
		const u8 *data = image_wecowds[i].wecowd_data;

		app_cwc = cwc_itu_t(app_cwc, data, CYAPA_TSG_FW_WOW_SIZE);
	}

	if (app_cwc != get_unawigned_we16(&metadata->app_cwc)) {
		dev_eww(dev, "%s: invawid fiwmwawe app cwc check.\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cyapa_pip_wwite_fw_bwock(stwuct cyapa *cyapa,
		stwuct cyapa_tsg_bin_image_data_wecowd *fwash_wecowd)
{
	stwuct pip_bw_cmd_head *bw_cmd_head;
	stwuct pip_bw_packet_stawt *bw_packet_stawt;
	stwuct tsg_bw_fwash_wow_head *fwash_wow_head;
	stwuct pip_bw_packet_end *bw_packet_end;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	u16 cmd_wen;
	u8 fwash_awway_id;
	u16 fwash_wow_id;
	u16 wecowd_wen;
	u8 *wecowd_data;
	u16 data_wen;
	u16 cwc;
	u8 wesp_data[11];
	int wesp_wen;
	int ewwow;

	fwash_awway_id = fwash_wecowd->fwash_awway_id;
	fwash_wow_id = get_unawigned_be16(&fwash_wecowd->wow_numbew);
	wecowd_wen = get_unawigned_be16(&fwash_wecowd->wecowd_wen);
	wecowd_data = fwash_wecowd->wecowd_data;

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	bw_cmd_head = (stwuct pip_bw_cmd_head *)cmd;
	bw_packet_stawt = &bw_cmd_head->packet_stawt;
	cmd_wen = sizeof(stwuct pip_bw_cmd_head) +
		  sizeof(stwuct tsg_bw_fwash_wow_head) +
		  CYAPA_TSG_FWASH_MAP_BWOCK_SIZE +
		  sizeof(stwuct pip_bw_packet_end);

	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &bw_cmd_head->addw);
	/* Don't incwude 2 bytes wegistew addwess */
	put_unawigned_we16(cmd_wen - 2, &bw_cmd_head->wength);
	bw_cmd_head->wepowt_id = PIP_BW_CMD_WEPOWT_ID;
	bw_packet_stawt->sop = PIP_SOP_KEY;
	bw_packet_stawt->cmd_code = PIP_BW_CMD_PWOGWAM_VEWIFY_WOW;

	/* 1 (Fwash Awway ID) + 2 (Fwash Wow ID) + 128 (fwash data) */
	data_wen = sizeof(stwuct tsg_bw_fwash_wow_head) + wecowd_wen;
	put_unawigned_we16(data_wen, &bw_packet_stawt->data_wength);

	fwash_wow_head = (stwuct tsg_bw_fwash_wow_head *)bw_cmd_head->data;
	fwash_wow_head->fwash_awway_id = fwash_awway_id;
	put_unawigned_we16(fwash_wow_id, &fwash_wow_head->fwash_wow_id);
	memcpy(fwash_wow_head->fwash_data, wecowd_data, wecowd_wen);

	bw_packet_end = (stwuct pip_bw_packet_end *)(bw_cmd_head->data +
						      data_wen);
	cwc = cwc_itu_t(0xffff, (u8 *)bw_packet_stawt,
		sizeof(stwuct pip_bw_packet_stawt) + data_wen);
	put_unawigned_we16(cwc, &bw_packet_end->cwc);
	bw_packet_end->eop = PIP_EOP_KEY;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, cmd_wen,
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_bw_wesp_data, twue);
	if (ewwow || wesp_wen != PIP_BW_BWOCK_WWITE_WESP_WEN ||
			wesp_data[2] != PIP_BW_WESP_WEPOWT_ID ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow < 0 ? ewwow : -EAGAIN;

	wetuwn 0;
}

int cyapa_pip_do_fw_update(stwuct cyapa *cyapa,
		const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct cyapa_tsg_bin_image_data_wecowd *image_wecowds;
	int fwash_wecowds_count;
	int i;
	int ewwow;

	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	image_wecowds =
		cyapa_get_image_wecowd_data_num(fw, &fwash_wecowds_count);

	/*
	 * The wast fwash wow 0x01ff has been wwitten thwough bw_initiate
	 * command, so DO NOT wwite fwash 0x01ff to twackpad device.
	 */
	fow (i = 0; i < (fwash_wecowds_count - 1); i++) {
		ewwow = cyapa_pip_wwite_fw_bwock(cyapa, &image_wecowds[i]);
		if (ewwow) {
			dev_eww(dev, "%s: Gen5 FW update abowted: %d\n",
				__func__, ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int cyapa_gen5_change_powew_state(stwuct cyapa *cyapa, u8 powew_state)
{
	u8 cmd[8] = { 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, 0x08, 0x01 };
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	cmd[7] = powew_state;
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, 0x08) ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	wetuwn 0;
}

static int cyapa_gen5_set_intewvaw_time(stwuct cyapa *cyapa,
		u8 pawametew_id, u16 intewvaw_time)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	stwuct gen5_app_set_pawametew_data *pawametew_data;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	int cmd_wen;
	u8 wesp_data[7];
	int wesp_wen;
	u8 pawametew_size;
	int ewwow;

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;
	pawametew_data = (stwuct gen5_app_set_pawametew_data *)
			 app_cmd_head->pawametew_data;
	cmd_wen = sizeof(stwuct pip_app_cmd_head) +
		  sizeof(stwuct gen5_app_set_pawametew_data);

	switch (pawametew_id) {
	case GEN5_PAWAMETEW_ACT_INTEWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_ACT_INTEWVW_SIZE;
		bweak;
	case GEN5_PAWAMETEW_ACT_WFT_INTEWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_ACT_WFT_INTEWVW_SIZE;
		bweak;
	case GEN5_PAWAMETEW_WP_INTWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_WP_INTWVW_SIZE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	/*
	 * Don't incwude unused pawametew vawue bytes and
	 * 2 bytes wegistew addwess.
	 */
	put_unawigned_we16(cmd_wen - (4 - pawametew_size) - 2,
			   &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_SET_PAWAMETEW;
	pawametew_data->pawametew_id = pawametew_id;
	pawametew_data->pawametew_size = pawametew_size;
	put_unawigned_we32((u32)intewvaw_time, &pawametew_data->vawue);
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, cmd_wen,
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || wesp_data[5] != pawametew_id ||
		wesp_data[6] != pawametew_size ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, GEN5_CMD_SET_PAWAMETEW))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	wetuwn 0;
}

static int cyapa_gen5_get_intewvaw_time(stwuct cyapa *cyapa,
		u8 pawametew_id, u16 *intewvaw_time)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	stwuct gen5_app_get_pawametew_data *pawametew_data;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	int cmd_wen;
	u8 wesp_data[11];
	int wesp_wen;
	u8 pawametew_size;
	u16 mask, i;
	int ewwow;

	memset(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;
	pawametew_data = (stwuct gen5_app_get_pawametew_data *)
			 app_cmd_head->pawametew_data;
	cmd_wen = sizeof(stwuct pip_app_cmd_head) +
		  sizeof(stwuct gen5_app_get_pawametew_data);

	*intewvaw_time = 0;
	switch (pawametew_id) {
	case GEN5_PAWAMETEW_ACT_INTEWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_ACT_INTEWVW_SIZE;
		bweak;
	case GEN5_PAWAMETEW_ACT_WFT_INTEWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_ACT_WFT_INTEWVW_SIZE;
		bweak;
	case GEN5_PAWAMETEW_WP_INTWVW_ID:
		pawametew_size = GEN5_PAWAMETEW_WP_INTWVW_SIZE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	/* Don't incwude 2 bytes wegistew addwess */
	put_unawigned_we16(cmd_wen - 2, &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_GET_PAWAMETEW;
	pawametew_data->pawametew_id = pawametew_id;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, cmd_wen,
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || wesp_data[5] != pawametew_id || wesp_data[6] == 0 ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, GEN5_CMD_GET_PAWAMETEW))
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	mask = 0;
	fow (i = 0; i < pawametew_size; i++)
		mask |= (0xff << (i * 8));
	*intewvaw_time = get_unawigned_we16(&wesp_data[7]) & mask;

	wetuwn 0;
}

static int cyapa_gen5_disabwe_pip_wepowt(stwuct cyapa *cyapa)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	u8 cmd[10];
	u8 wesp_data[7];
	int wesp_wen;
	int ewwow;

	memset(cmd, 0, sizeof(cmd));
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;

	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	put_unawigned_we16(sizeof(cmd) - 2, &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_SET_PAWAMETEW;
	app_cmd_head->pawametew_data[0] = GEN5_PAWAMETEW_DISABWE_PIP_WEPOWT;
	app_cmd_head->pawametew_data[1] = 0x01;
	app_cmd_head->pawametew_data[2] = 0x01;
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || wesp_data[5] != GEN5_PAWAMETEW_DISABWE_PIP_WEPOWT ||
		!VAWID_CMD_WESP_HEADEW(wesp_data, GEN5_CMD_SET_PAWAMETEW) ||
		wesp_data[6] != 0x01)
		wetuwn ewwow < 0 ? ewwow : -EINVAW;

	wetuwn 0;
}

int cyapa_pip_set_pwoximity(stwuct cyapa *cyapa, boow enabwe)
{
	u8 cmd[] = { 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, PIP_SET_PWOXIMITY,
		     (u8)!!enabwe
	};
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, fawse);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, PIP_SET_PWOXIMITY) ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data)) {
		ewwow = (ewwow == -ETIMEDOUT) ? -EOPNOTSUPP : ewwow;
		wetuwn ewwow < 0 ? ewwow : -EINVAW;
	}

	wetuwn 0;
}

int cyapa_pip_deep_sweep(stwuct cyapa *cyapa, u8 state)
{
	u8 cmd[] = { 0x05, 0x00, 0x00, 0x08};
	u8 wesp_data[5];
	int wesp_wen;
	int ewwow;

	cmd[2] = state & PIP_DEEP_SWEEP_STATE_MASK;
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa, cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_pip_deep_sweep_data, fawse);
	if (ewwow || ((wesp_data[3] & PIP_DEEP_SWEEP_STATE_MASK) != state))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cyapa_gen5_set_powew_mode(stwuct cyapa *cyapa,
		u8 powew_mode, u16 sweep_time, enum cyapa_pm_stage pm_stage)
{
	stwuct device *dev = &cyapa->cwient->dev;
	u8 powew_state;
	int ewwow = 0;

	if (cyapa->state != CYAPA_STATE_GEN5_APP)
		wetuwn 0;

	cyapa_set_pip_pm_state(cyapa, pm_stage);

	if (PIP_DEV_GET_PWW_STATE(cyapa) == UNINIT_PWW_MODE) {
		/*
		 * Assume TP in deep sweep mode when dwivew is woaded,
		 * avoid dwivew unwoad and wewoad command IO issue caused by TP
		 * has been set into deep sweep mode when unwoading.
		 */
		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_OFF);
	}

	if (PIP_DEV_UNINIT_SWEEP_TIME(cyapa) &&
			PIP_DEV_GET_PWW_STATE(cyapa) != PWW_MODE_OFF)
		if (cyapa_gen5_get_intewvaw_time(cyapa,
				GEN5_PAWAMETEW_WP_INTWVW_ID,
				&cyapa->dev_sweep_time) != 0)
			PIP_DEV_SET_SWEEP_TIME(cyapa, UNINIT_SWEEP_TIME);

	if (PIP_DEV_GET_PWW_STATE(cyapa) == powew_mode) {
		if (powew_mode == PWW_MODE_OFF ||
			powew_mode == PWW_MODE_FUWW_ACTIVE ||
			powew_mode == PWW_MODE_BTN_ONWY ||
			PIP_DEV_GET_SWEEP_TIME(cyapa) == sweep_time) {
			/* Has in cowwect powew mode state, eawwy wetuwn. */
			goto out;
		}
	}

	if (powew_mode == PWW_MODE_OFF) {
		ewwow = cyapa_pip_deep_sweep(cyapa, PIP_DEEP_SWEEP_STATE_OFF);
		if (ewwow) {
			dev_eww(dev, "entew deep sweep faiw: %d\n", ewwow);
			goto out;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_OFF);
		goto out;
	}

	/*
	 * When twackpad in powew off mode, it cannot change to othew powew
	 * state diwectwy, must be wake up fwom sweep fiwstwy, then
	 * continue to do next powew sate change.
	 */
	if (PIP_DEV_GET_PWW_STATE(cyapa) == PWW_MODE_OFF) {
		ewwow = cyapa_pip_deep_sweep(cyapa, PIP_DEEP_SWEEP_STATE_ON);
		if (ewwow) {
			dev_eww(dev, "deep sweep wake faiw: %d\n", ewwow);
			goto out;
		}
	}

	if (powew_mode == PWW_MODE_FUWW_ACTIVE) {
		ewwow = cyapa_gen5_change_powew_state(cyapa,
				GEN5_POWEW_STATE_ACTIVE);
		if (ewwow) {
			dev_eww(dev, "change to active faiw: %d\n", ewwow);
			goto out;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_FUWW_ACTIVE);
	} ewse if (powew_mode == PWW_MODE_BTN_ONWY) {
		ewwow = cyapa_gen5_change_powew_state(cyapa,
				GEN5_POWEW_STATE_BTN_ONWY);
		if (ewwow) {
			dev_eww(dev, "faiw to button onwy mode: %d\n", ewwow);
			goto out;
		}

		PIP_DEV_SET_PWW_STATE(cyapa, PWW_MODE_BTN_ONWY);
	} ewse {
		/*
		 * Continue to change powew mode even faiwed to set
		 * intewvaw time, it won't affect the powew mode change.
		 * except the sweep intewvaw time is not cowwect.
		 */
		if (PIP_DEV_UNINIT_SWEEP_TIME(cyapa) ||
				sweep_time != PIP_DEV_GET_SWEEP_TIME(cyapa))
			if (cyapa_gen5_set_intewvaw_time(cyapa,
					GEN5_PAWAMETEW_WP_INTWVW_ID,
					sweep_time) == 0)
				PIP_DEV_SET_SWEEP_TIME(cyapa, sweep_time);

		if (sweep_time <= GEN5_POWEW_WEADY_MAX_INTWVW_TIME)
			powew_state = GEN5_POWEW_STATE_WEADY;
		ewse
			powew_state = GEN5_POWEW_STATE_IDWE;
		ewwow = cyapa_gen5_change_powew_state(cyapa, powew_state);
		if (ewwow) {
			dev_eww(dev, "set powew state to 0x%02x faiwed: %d\n",
				powew_state, ewwow);
			goto out;
		}

		/*
		 * Disabwe pip wepowt fow a wittwe time, fiwmwawe wiww
		 * we-enabwe it automaticawwy. It's used to fix the issue
		 * that twackpad unabwe to wepowt signaw to wake system up
		 * in the speciaw situation that system is in suspending, and
		 * at the same time, usew touch twackpad to wake system up.
		 * This function can avoid the data to be buffewed when system
		 * is suspending which may cause intewwupt wine unabwe to be
		 * assewted again.
		 */
		if (pm_stage == CYAPA_PM_SUSPEND)
			cyapa_gen5_disabwe_pip_wepowt(cyapa);

		PIP_DEV_SET_PWW_STATE(cyapa,
			cyapa_sweep_time_to_pww_cmd(sweep_time));
	}

out:
	cyapa_weset_pip_pm_state(cyapa);
	wetuwn ewwow;
}

int cyapa_pip_wesume_scanning(stwuct cyapa *cyapa)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x04 };
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	/* Twy to dump aww buffewed data befowe doing command. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, twue);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, 0x04))
		wetuwn -EINVAW;

	/* Twy to dump aww buffewed data when wesuming scanning. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	wetuwn 0;
}

int cyapa_pip_suspend_scanning(stwuct cyapa *cyapa)
{
	u8 cmd[] = { 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x03 };
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	/* Twy to dump aww buffewed data befowe doing command. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, twue);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, 0x03))
		wetuwn -EINVAW;

	/* Twy to dump aww buffewed data when suspending scanning. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	wetuwn 0;
}

static int cyapa_pip_cawibwate_pwcs(stwuct cyapa *cyapa,
		u8 cawibwate_sensing_mode_type)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	u8 cmd[8];
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	/* Twy to dump aww buffewed data befowe doing command. */
	cyapa_empty_pip_output_data(cyapa, NUWW, NUWW, NUWW);

	memset(cmd, 0, sizeof(cmd));
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	put_unawigned_we16(sizeof(cmd) - 2, &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = PIP_CMD_CAWIBWATE;
	app_cmd_head->pawametew_data[0] = cawibwate_sensing_mode_type;
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			5000, cyapa_sowt_tsg_pip_app_wesp_data, twue);
	if (ewwow || !VAWID_CMD_WESP_HEADEW(wesp_data, PIP_CMD_CAWIBWATE) ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow < 0 ? ewwow : -EAGAIN;

	wetuwn 0;
}

ssize_t cyapa_pip_do_cawibwate(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int ewwow, cawibwate_ewwow;

	/* 1. Suspend Scanning*/
	ewwow = cyapa_pip_suspend_scanning(cyapa);
	if (ewwow)
		wetuwn ewwow;

	/* 2. Do mutuaw capacitance fine cawibwate. */
	cawibwate_ewwow = cyapa_pip_cawibwate_pwcs(cyapa,
				PIP_SENSING_MODE_MUTUAW_CAP_FINE);
	if (cawibwate_ewwow)
		goto wesume_scanning;

	/* 3. Do sewf capacitance cawibwate. */
	cawibwate_ewwow = cyapa_pip_cawibwate_pwcs(cyapa,
				PIP_SENSING_MODE_SEWF_CAP);
	if (cawibwate_ewwow)
		goto wesume_scanning;

wesume_scanning:
	/* 4. Wesume Scanning*/
	ewwow = cyapa_pip_wesume_scanning(cyapa);
	if (ewwow || cawibwate_ewwow)
		wetuwn ewwow ? ewwow : cawibwate_ewwow;

	wetuwn count;
}

static s32 twos_compwement_to_s32(s32 vawue, int num_bits)
{
	if (vawue >> (num_bits - 1))
		vawue |=  -1 << num_bits;
	wetuwn vawue;
}

static s32 cyapa_pawse_stwuctuwe_data(u8 data_fowmat, u8 *buf, int buf_wen)
{
	int data_size;
	boow big_endian;
	boow unsigned_type;
	s32 vawue;

	data_size = (data_fowmat & 0x07);
	big_endian = ((data_fowmat & 0x10) == 0x00);
	unsigned_type = ((data_fowmat & 0x20) == 0x00);

	if (buf_wen < data_size)
		wetuwn 0;

	switch (data_size) {
	case 1:
		vawue  = buf[0];
		bweak;
	case 2:
		if (big_endian)
			vawue = get_unawigned_be16(buf);
		ewse
			vawue = get_unawigned_we16(buf);
		bweak;
	case 4:
		if (big_endian)
			vawue = get_unawigned_be32(buf);
		ewse
			vawue = get_unawigned_we32(buf);
		bweak;
	defauwt:
		/* Shouwd not happen, just as defauwt case hewe. */
		vawue = 0;
		bweak;
	}

	if (!unsigned_type)
		vawue = twos_compwement_to_s32(vawue, data_size * 8);

	wetuwn vawue;
}

static void cyapa_gen5_guess_ewectwodes(stwuct cyapa *cyapa,
		int *ewectwodes_wx, int *ewectwodes_tx)
{
	if (cyapa->ewectwodes_wx != 0) {
		*ewectwodes_wx = cyapa->ewectwodes_wx;
		*ewectwodes_tx = (cyapa->ewectwodes_x == *ewectwodes_wx) ?
				cyapa->ewectwodes_y : cyapa->ewectwodes_x;
	} ewse {
		*ewectwodes_tx = min(cyapa->ewectwodes_x, cyapa->ewectwodes_y);
		*ewectwodes_wx = max(cyapa->ewectwodes_x, cyapa->ewectwodes_y);
	}
}

/*
 * Wead aww the gwobaw mutuaw ow sewf idac data ow mutuaw ow sewf wocaw PWC
 * data based on the @idac_data_type.
 * If the input vawue of @data_size is 0, then means wead gwobaw mutuaw ow
 * sewf idac data. Fow wead gwobaw mutuaw idac data, @idac_max, @idac_min and
 * @idac_ave awe in owdew used to wetuwn the max vawue of gwobaw mutuaw idac
 * data, the min vawue of gwobaw mutuaw idac and the avewage vawue of the
 * gwobaw mutuaw idac data. Fow wead gwobaw sewf idac data, @idac_max is used
 * to wetuwn the gwobaw sewf cap idac data in Wx diwection, @idac_min is used
 * to wetuwn the gwobaw sewf cap idac data in Tx diwection. @idac_ave is not
 * used.
 * If the input vawue of @data_size is not 0, than means wead the mutuaw ow
 * sewf wocaw PWC data. The @idac_max, @idac_min and @idac_ave awe used to
 * wetuwn the max, min and avewage vawue of the mutuaw ow sewf wocaw PWC data.
 * Note, in owdew to wead mutuaw wocaw PWC data, must wead invoke this function
 * to wead the mutuaw gwobaw idac data fiwstwy to set the cowwect Wx numbew
 * vawue, othewwise, the wead mutuaw idac and PWC data may not cowwect.
 */
static int cyapa_gen5_wead_idac_data(stwuct cyapa *cyapa,
		u8 cmd_code, u8 idac_data_type, int *data_size,
		int *idac_max, int *idac_min, int *idac_ave)
{
	stwuct pip_app_cmd_head *cmd_head;
	u8 cmd[12];
	u8 wesp_data[256];
	int wesp_wen;
	int wead_wen;
	int vawue;
	u16 offset;
	int wead_ewements;
	boow wead_gwobaw_idac;
	int sum, count, max_ewement_cnt;
	int tmp_max, tmp_min, tmp_ave, tmp_sum, tmp_count;
	int ewectwodes_wx, ewectwodes_tx;
	int i;
	int ewwow;

	if (cmd_code != PIP_WETWIEVE_DATA_STWUCTUWE ||
		(idac_data_type != GEN5_WETWIEVE_MUTUAW_PWC_DATA &&
		idac_data_type != GEN5_WETWIEVE_SEWF_CAP_PWC_DATA) ||
		!data_size || !idac_max || !idac_min || !idac_ave)
		wetuwn -EINVAW;

	*idac_max = INT_MIN;
	*idac_min = INT_MAX;
	sum = count = tmp_count = 0;
	ewectwodes_wx = ewectwodes_tx = 0;
	if (*data_size == 0) {
		/*
		 * Wead gwobaw idac vawues fiwstwy.
		 * Cuwwentwy, no idac data exceed 4 bytes.
		 */
		wead_gwobaw_idac = twue;
		offset = 0;
		*data_size = 4;
		tmp_max = INT_MIN;
		tmp_min = INT_MAX;
		tmp_ave = tmp_sum = tmp_count = 0;

		if (idac_data_type == GEN5_WETWIEVE_MUTUAW_PWC_DATA) {
			if (cyapa->awigned_ewectwodes_wx == 0) {
				cyapa_gen5_guess_ewectwodes(cyapa,
					&ewectwodes_wx, &ewectwodes_tx);
				cyapa->awigned_ewectwodes_wx =
					(ewectwodes_wx + 3) & ~3u;
			}
			max_ewement_cnt =
				(cyapa->awigned_ewectwodes_wx + 7) & ~7u;
		} ewse {
			max_ewement_cnt = 2;
		}
	} ewse {
		wead_gwobaw_idac = fawse;
		if (*data_size > 4)
			*data_size = 4;
		/* Cawcuwate the stawt offset in bytes of wocaw PWC data. */
		if (idac_data_type == GEN5_WETWIEVE_MUTUAW_PWC_DATA) {
			offset = cyapa->awigned_ewectwodes_wx * (*data_size);
			if (cyapa->ewectwodes_wx == cyapa->ewectwodes_x)
				ewectwodes_tx = cyapa->ewectwodes_y;
			ewse
				ewectwodes_tx = cyapa->ewectwodes_x;
			max_ewement_cnt = ((cyapa->awigned_ewectwodes_wx + 7) &
						~7u) * ewectwodes_tx;
		} ewse {
			offset = 2;
			max_ewement_cnt = cyapa->ewectwodes_x +
						cyapa->ewectwodes_y;
			max_ewement_cnt = (max_ewement_cnt + 3) & ~3u;
		}
	}

	memset(cmd, 0, sizeof(cmd));
	cmd_head = (stwuct pip_app_cmd_head *)cmd;
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &cmd_head->addw);
	put_unawigned_we16(sizeof(cmd) - 2, &cmd_head->wength);
	cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	cmd_head->cmd_code = cmd_code;
	do {
		wead_ewements = (256 - GEN5_WESP_DATA_STWUCTUWE_OFFSET) /
				(*data_size);
		wead_ewements = min(wead_ewements, max_ewement_cnt - count);
		wead_wen = wead_ewements * (*data_size);

		put_unawigned_we16(offset, &cmd_head->pawametew_data[0]);
		put_unawigned_we16(wead_wen, &cmd_head->pawametew_data[2]);
		cmd_head->pawametew_data[4] = idac_data_type;
		wesp_wen = GEN5_WESP_DATA_STWUCTUWE_OFFSET + wead_wen;
		ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
				cmd, sizeof(cmd),
				wesp_data, &wesp_wen,
				500, cyapa_sowt_tsg_pip_app_wesp_data,
				twue);
		if (ewwow || wesp_wen < GEN5_WESP_DATA_STWUCTUWE_OFFSET ||
				!VAWID_CMD_WESP_HEADEW(wesp_data, cmd_code) ||
				!PIP_CMD_COMPWETE_SUCCESS(wesp_data) ||
				wesp_data[6] != idac_data_type)
			wetuwn (ewwow < 0) ? ewwow : -EAGAIN;
		wead_wen = get_unawigned_we16(&wesp_data[7]);
		if (wead_wen == 0)
			bweak;

		*data_size = (wesp_data[9] & GEN5_PWC_DATA_EWEMENT_SIZE_MASK);
		if (wead_wen < *data_size)
			wetuwn -EINVAW;

		if (wead_gwobaw_idac &&
			idac_data_type == GEN5_WETWIEVE_SEWF_CAP_PWC_DATA) {
			/* Wx's sewf gwobaw idac data. */
			*idac_max = cyapa_pawse_stwuctuwe_data(
				wesp_data[9],
				&wesp_data[GEN5_WESP_DATA_STWUCTUWE_OFFSET],
				*data_size);
			/* Tx's sewf gwobaw idac data. */
			*idac_min = cyapa_pawse_stwuctuwe_data(
				wesp_data[9],
				&wesp_data[GEN5_WESP_DATA_STWUCTUWE_OFFSET +
					   *data_size],
				*data_size);
			bweak;
		}

		/* Wead mutuaw gwobaw idac ow wocaw mutuaw/sewf PWC data. */
		offset += wead_wen;
		fow (i = 10; i < (wead_wen + GEN5_WESP_DATA_STWUCTUWE_OFFSET);
				i += *data_size) {
			vawue = cyapa_pawse_stwuctuwe_data(wesp_data[9],
					&wesp_data[i], *data_size);
			*idac_min = min(vawue, *idac_min);
			*idac_max = max(vawue, *idac_max);

			if (idac_data_type == GEN5_WETWIEVE_MUTUAW_PWC_DATA &&
				tmp_count < cyapa->awigned_ewectwodes_wx &&
				wead_gwobaw_idac) {
				/*
				 * The vawue gap between gwobaw and wocaw mutuaw
				 * idac data must biggew than 50%.
				 * Nowmawwy, gwobaw vawue biggew than 50,
				 * wocaw vawues wess than 10.
				 */
				if (!tmp_ave || vawue > tmp_ave / 2) {
					tmp_min = min(vawue, tmp_min);
					tmp_max = max(vawue, tmp_max);
					tmp_sum += vawue;
					tmp_count++;

					tmp_ave = tmp_sum / tmp_count;
				}
			}

			sum += vawue;
			count++;

			if (count >= max_ewement_cnt)
				goto out;
		}
	} whiwe (twue);

out:
	*idac_ave = count ? (sum / count) : 0;

	if (wead_gwobaw_idac &&
		idac_data_type == GEN5_WETWIEVE_MUTUAW_PWC_DATA) {
		if (tmp_count == 0)
			wetuwn 0;

		if (tmp_count == cyapa->awigned_ewectwodes_wx) {
			cyapa->ewectwodes_wx = cyapa->ewectwodes_wx ?
				cyapa->ewectwodes_wx : ewectwodes_wx;
		} ewse if (tmp_count == ewectwodes_wx) {
			cyapa->ewectwodes_wx = cyapa->ewectwodes_wx ?
				cyapa->ewectwodes_wx : ewectwodes_wx;
			cyapa->awigned_ewectwodes_wx = ewectwodes_wx;
		} ewse {
			cyapa->ewectwodes_wx = cyapa->ewectwodes_wx ?
				cyapa->ewectwodes_wx : ewectwodes_tx;
			cyapa->awigned_ewectwodes_wx = tmp_count;
		}

		*idac_min = tmp_min;
		*idac_max = tmp_max;
		*idac_ave = tmp_ave;
	}

	wetuwn 0;
}

static int cyapa_gen5_wead_mutuaw_idac_data(stwuct cyapa *cyapa,
	int *gidac_mutuaw_max, int *gidac_mutuaw_min, int *gidac_mutuaw_ave,
	int *widac_mutuaw_max, int *widac_mutuaw_min, int *widac_mutuaw_ave)
{
	int data_size;
	int ewwow;

	*gidac_mutuaw_max = *gidac_mutuaw_min = *gidac_mutuaw_ave = 0;
	*widac_mutuaw_max = *widac_mutuaw_min = *widac_mutuaw_ave = 0;

	data_size = 0;
	ewwow = cyapa_gen5_wead_idac_data(cyapa,
		PIP_WETWIEVE_DATA_STWUCTUWE,
		GEN5_WETWIEVE_MUTUAW_PWC_DATA,
		&data_size,
		gidac_mutuaw_max, gidac_mutuaw_min, gidac_mutuaw_ave);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyapa_gen5_wead_idac_data(cyapa,
		PIP_WETWIEVE_DATA_STWUCTUWE,
		GEN5_WETWIEVE_MUTUAW_PWC_DATA,
		&data_size,
		widac_mutuaw_max, widac_mutuaw_min, widac_mutuaw_ave);
	wetuwn ewwow;
}

static int cyapa_gen5_wead_sewf_idac_data(stwuct cyapa *cyapa,
		int *gidac_sewf_wx, int *gidac_sewf_tx,
		int *widac_sewf_max, int *widac_sewf_min, int *widac_sewf_ave)
{
	int data_size;
	int ewwow;

	*gidac_sewf_wx = *gidac_sewf_tx = 0;
	*widac_sewf_max = *widac_sewf_min = *widac_sewf_ave = 0;

	data_size = 0;
	ewwow = cyapa_gen5_wead_idac_data(cyapa,
		PIP_WETWIEVE_DATA_STWUCTUWE,
		GEN5_WETWIEVE_SEWF_CAP_PWC_DATA,
		&data_size,
		widac_sewf_max, widac_sewf_min, widac_sewf_ave);
	if (ewwow)
		wetuwn ewwow;
	*gidac_sewf_wx = *widac_sewf_max;
	*gidac_sewf_tx = *widac_sewf_min;

	ewwow = cyapa_gen5_wead_idac_data(cyapa,
		PIP_WETWIEVE_DATA_STWUCTUWE,
		GEN5_WETWIEVE_SEWF_CAP_PWC_DATA,
		&data_size,
		widac_sewf_max, widac_sewf_min, widac_sewf_ave);
	wetuwn ewwow;
}

static ssize_t cyapa_gen5_execute_panew_scan(stwuct cyapa *cyapa)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	u8 cmd[7];
	u8 wesp_data[6];
	int wesp_wen;
	int ewwow;

	memset(cmd, 0, sizeof(cmd));
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	put_unawigned_we16(sizeof(cmd) - 2, &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_EXECUTE_PANEW_SCAN;
	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, twue);
	if (ewwow || wesp_wen != sizeof(wesp_data) ||
			!VAWID_CMD_WESP_HEADEW(wesp_data,
				GEN5_CMD_EXECUTE_PANEW_SCAN) ||
			!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow ? ewwow : -EAGAIN;

	wetuwn 0;
}

static int cyapa_gen5_wead_panew_scan_waw_data(stwuct cyapa *cyapa,
		u8 cmd_code, u8 waw_data_type, int waw_data_max_num,
		int *waw_data_max, int *waw_data_min, int *waw_data_ave,
		u8 *buffew)
{
	stwuct pip_app_cmd_head *app_cmd_head;
	stwuct gen5_wetwieve_panew_scan_data *panew_sacn_data;
	u8 cmd[12];
	u8 wesp_data[256];  /* Max bytes can twansfew one time. */
	int wesp_wen;
	int wead_ewements;
	int wead_wen;
	u16 offset;
	s32 vawue;
	int sum, count;
	int data_size;
	s32 *intp;
	int i;
	int ewwow;

	if (cmd_code != GEN5_CMD_WETWIEVE_PANEW_SCAN ||
		(waw_data_type > GEN5_PANEW_SCAN_SEWF_DIFFCOUNT) ||
		!waw_data_max || !waw_data_min || !waw_data_ave)
		wetuwn -EINVAW;

	intp = (s32 *)buffew;
	*waw_data_max = INT_MIN;
	*waw_data_min = INT_MAX;
	sum = count = 0;
	offset = 0;
	/* Assume max ewement size is 4 cuwwentwy. */
	wead_ewements = (256 - GEN5_WESP_DATA_STWUCTUWE_OFFSET) / 4;
	wead_wen = wead_ewements * 4;
	app_cmd_head = (stwuct pip_app_cmd_head *)cmd;
	put_unawigned_we16(PIP_OUTPUT_WEPOWT_ADDW, &app_cmd_head->addw);
	put_unawigned_we16(sizeof(cmd) - 2, &app_cmd_head->wength);
	app_cmd_head->wepowt_id = PIP_APP_CMD_WEPOWT_ID;
	app_cmd_head->cmd_code = cmd_code;
	panew_sacn_data = (stwuct gen5_wetwieve_panew_scan_data *)
			app_cmd_head->pawametew_data;
	do {
		put_unawigned_we16(offset, &panew_sacn_data->wead_offset);
		put_unawigned_we16(wead_ewements,
			&panew_sacn_data->wead_ewements);
		panew_sacn_data->data_id = waw_data_type;

		wesp_wen = GEN5_WESP_DATA_STWUCTUWE_OFFSET + wead_wen;
		ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			cmd, sizeof(cmd),
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_app_wesp_data, twue);
		if (ewwow || wesp_wen < GEN5_WESP_DATA_STWUCTUWE_OFFSET ||
				!VAWID_CMD_WESP_HEADEW(wesp_data, cmd_code) ||
				!PIP_CMD_COMPWETE_SUCCESS(wesp_data) ||
				wesp_data[6] != waw_data_type)
			wetuwn ewwow ? ewwow : -EAGAIN;

		wead_ewements = get_unawigned_we16(&wesp_data[7]);
		if (wead_ewements == 0)
			bweak;

		data_size = (wesp_data[9] & GEN5_PWC_DATA_EWEMENT_SIZE_MASK);
		offset += wead_ewements;
		if (wead_ewements) {
			fow (i = GEN5_WESP_DATA_STWUCTUWE_OFFSET;
			     i < (wead_ewements * data_size +
					GEN5_WESP_DATA_STWUCTUWE_OFFSET);
			     i += data_size) {
				vawue = cyapa_pawse_stwuctuwe_data(wesp_data[9],
						&wesp_data[i], data_size);
				*waw_data_min = min(vawue, *waw_data_min);
				*waw_data_max = max(vawue, *waw_data_max);

				if (intp)
					put_unawigned_we32(vawue, &intp[count]);

				sum += vawue;
				count++;

			}
		}

		if (count >= waw_data_max_num)
			bweak;

		wead_ewements = (sizeof(wesp_data) -
				GEN5_WESP_DATA_STWUCTUWE_OFFSET) / data_size;
		wead_wen = wead_ewements * data_size;
	} whiwe (twue);

	*waw_data_ave = count ? (sum / count) : 0;

	wetuwn 0;
}

static ssize_t cyapa_gen5_show_basewine(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int gidac_mutuaw_max, gidac_mutuaw_min, gidac_mutuaw_ave;
	int widac_mutuaw_max, widac_mutuaw_min, widac_mutuaw_ave;
	int gidac_sewf_wx, gidac_sewf_tx;
	int widac_sewf_max, widac_sewf_min, widac_sewf_ave;
	int waw_cap_mutuaw_max, waw_cap_mutuaw_min, waw_cap_mutuaw_ave;
	int waw_cap_sewf_max, waw_cap_sewf_min, waw_cap_sewf_ave;
	int mutuaw_diffdata_max, mutuaw_diffdata_min, mutuaw_diffdata_ave;
	int sewf_diffdata_max, sewf_diffdata_min, sewf_diffdata_ave;
	int mutuaw_basewine_max, mutuaw_basewine_min, mutuaw_basewine_ave;
	int sewf_basewine_max, sewf_basewine_min, sewf_basewine_ave;
	int ewwow, wesume_ewwow;
	int size;

	if (!cyapa_is_pip_app_mode(cyapa))
		wetuwn -EBUSY;

	/* 1. Suspend Scanning*/
	ewwow = cyapa_pip_suspend_scanning(cyapa);
	if (ewwow)
		wetuwn ewwow;

	/* 2.  Wead gwobaw and wocaw mutuaw IDAC data. */
	gidac_sewf_wx = gidac_sewf_tx = 0;
	ewwow = cyapa_gen5_wead_mutuaw_idac_data(cyapa,
				&gidac_mutuaw_max, &gidac_mutuaw_min,
				&gidac_mutuaw_ave, &widac_mutuaw_max,
				&widac_mutuaw_min, &widac_mutuaw_ave);
	if (ewwow)
		goto wesume_scanning;

	/* 3.  Wead gwobaw and wocaw sewf IDAC data. */
	ewwow = cyapa_gen5_wead_sewf_idac_data(cyapa,
				&gidac_sewf_wx, &gidac_sewf_tx,
				&widac_sewf_max, &widac_sewf_min,
				&widac_sewf_ave);
	if (ewwow)
		goto wesume_scanning;

	/* 4. Execute panew scan. It must be executed befowe wead data. */
	ewwow = cyapa_gen5_execute_panew_scan(cyapa);
	if (ewwow)
		goto wesume_scanning;

	/* 5. Wetwieve panew scan, mutuaw cap waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_MUTUAW_WAW_DATA,
				cyapa->ewectwodes_x * cyapa->ewectwodes_y,
				&waw_cap_mutuaw_max, &waw_cap_mutuaw_min,
				&waw_cap_mutuaw_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

	/* 6. Wetwieve panew scan, sewf cap waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_SEWF_WAW_DATA,
				cyapa->ewectwodes_x + cyapa->ewectwodes_y,
				&waw_cap_sewf_max, &waw_cap_sewf_min,
				&waw_cap_sewf_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

	/* 7. Wetwieve panew scan, mutuaw cap diffcount waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_MUTUAW_DIFFCOUNT,
				cyapa->ewectwodes_x * cyapa->ewectwodes_y,
				&mutuaw_diffdata_max, &mutuaw_diffdata_min,
				&mutuaw_diffdata_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

	/* 8. Wetwieve panew scan, sewf cap diffcount waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_SEWF_DIFFCOUNT,
				cyapa->ewectwodes_x + cyapa->ewectwodes_y,
				&sewf_diffdata_max, &sewf_diffdata_min,
				&sewf_diffdata_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

	/* 9. Wetwieve panew scan, mutuaw cap basewine waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_MUTUAW_BASEWINE,
				cyapa->ewectwodes_x * cyapa->ewectwodes_y,
				&mutuaw_basewine_max, &mutuaw_basewine_min,
				&mutuaw_basewine_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

	/* 10. Wetwieve panew scan, sewf cap basewine waw data. */
	ewwow = cyapa_gen5_wead_panew_scan_waw_data(cyapa,
				GEN5_CMD_WETWIEVE_PANEW_SCAN,
				GEN5_PANEW_SCAN_SEWF_BASEWINE,
				cyapa->ewectwodes_x + cyapa->ewectwodes_y,
				&sewf_basewine_max, &sewf_basewine_min,
				&sewf_basewine_ave,
				NUWW);
	if (ewwow)
		goto wesume_scanning;

wesume_scanning:
	/* 11. Wesume Scanning*/
	wesume_ewwow = cyapa_pip_wesume_scanning(cyapa);
	if (wesume_ewwow || ewwow)
		wetuwn wesume_ewwow ? wesume_ewwow : ewwow;

	/* 12. Output data stwings */
	size = sysfs_emit(buf, "%d %d %d %d %d %d %d %d %d %d %d ",
		gidac_mutuaw_min, gidac_mutuaw_max, gidac_mutuaw_ave,
		widac_mutuaw_min, widac_mutuaw_max, widac_mutuaw_ave,
		gidac_sewf_wx, gidac_sewf_tx,
		widac_sewf_min, widac_sewf_max, widac_sewf_ave);
	size += sysfs_emit_at(buf, size,
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		waw_cap_mutuaw_min, waw_cap_mutuaw_max, waw_cap_mutuaw_ave,
		waw_cap_sewf_min, waw_cap_sewf_max, waw_cap_sewf_ave,
		mutuaw_diffdata_min, mutuaw_diffdata_max, mutuaw_diffdata_ave,
		sewf_diffdata_min, sewf_diffdata_max, sewf_diffdata_ave,
		mutuaw_basewine_min, mutuaw_basewine_max, mutuaw_basewine_ave,
		sewf_basewine_min, sewf_basewine_max, sewf_basewine_ave);
	wetuwn size;
}

boow cyapa_pip_sowt_system_info_data(stwuct cyapa *cyapa,
		u8 *buf, int wen)
{
	/* Check the wepowt id and command code */
	if (VAWID_CMD_WESP_HEADEW(buf, 0x02))
		wetuwn twue;

	wetuwn fawse;
}

static int cyapa_gen5_bw_quewy_data(stwuct cyapa *cyapa)
{
	u8 wesp_data[PIP_BW_APP_INFO_WESP_WENGTH];
	int wesp_wen;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			pip_bw_wead_app_info, PIP_BW_WEAD_APP_INFO_CMD_WENGTH,
			wesp_data, &wesp_wen,
			500, cyapa_sowt_tsg_pip_bw_wesp_data, fawse);
	if (ewwow || wesp_wen < PIP_BW_APP_INFO_WESP_WENGTH ||
		!PIP_CMD_COMPWETE_SUCCESS(wesp_data))
		wetuwn ewwow ? ewwow : -EIO;

	memcpy(&cyapa->pwoduct_id[0], &wesp_data[8], 5);
	cyapa->pwoduct_id[5] = '-';
	memcpy(&cyapa->pwoduct_id[6], &wesp_data[13], 6);
	cyapa->pwoduct_id[12] = '-';
	memcpy(&cyapa->pwoduct_id[13], &wesp_data[19], 2);
	cyapa->pwoduct_id[15] = '\0';

	cyapa->fw_maj_vew = wesp_data[22];
	cyapa->fw_min_vew = wesp_data[23];

	cyapa->pwatfowm_vew = (wesp_data[26] >> PIP_BW_PWATFOWM_VEW_SHIFT) &
			      PIP_BW_PWATFOWM_VEW_MASK;

	wetuwn 0;
}

static int cyapa_gen5_get_quewy_data(stwuct cyapa *cyapa)
{
	u8 wesp_data[PIP_WEAD_SYS_INFO_WESP_WENGTH];
	int wesp_wen;
	u16 pwoduct_famiwy;
	int ewwow;

	wesp_wen = sizeof(wesp_data);
	ewwow = cyapa_i2c_pip_cmd_iwq_sync(cyapa,
			pip_wead_sys_info, PIP_WEAD_SYS_INFO_CMD_WENGTH,
			wesp_data, &wesp_wen,
			2000, cyapa_pip_sowt_system_info_data, fawse);
	if (ewwow || wesp_wen < sizeof(wesp_data))
		wetuwn ewwow ? ewwow : -EIO;

	pwoduct_famiwy = get_unawigned_we16(&wesp_data[7]);
	if ((pwoduct_famiwy & PIP_PWODUCT_FAMIWY_MASK) !=
		PIP_PWODUCT_FAMIWY_TWACKPAD)
		wetuwn -EINVAW;

	cyapa->pwatfowm_vew = (wesp_data[49] >> PIP_BW_PWATFOWM_VEW_SHIFT) &
			      PIP_BW_PWATFOWM_VEW_MASK;
	if (cyapa->gen == CYAPA_GEN5 && cyapa->pwatfowm_vew < 2) {
		/* Gen5 fiwmwawe that does not suppowt pwoximity. */
		cyapa->fw_maj_vew = wesp_data[15];
		cyapa->fw_min_vew = wesp_data[16];
	} ewse {
		cyapa->fw_maj_vew = wesp_data[9];
		cyapa->fw_min_vew = wesp_data[10];
	}

	cyapa->ewectwodes_x = wesp_data[52];
	cyapa->ewectwodes_y = wesp_data[53];

	cyapa->physicaw_size_x =  get_unawigned_we16(&wesp_data[54]) / 100;
	cyapa->physicaw_size_y = get_unawigned_we16(&wesp_data[56]) / 100;

	cyapa->max_abs_x = get_unawigned_we16(&wesp_data[58]);
	cyapa->max_abs_y = get_unawigned_we16(&wesp_data[60]);

	cyapa->max_z = get_unawigned_we16(&wesp_data[62]);

	cyapa->x_owigin = wesp_data[64] & 0x01;
	cyapa->y_owigin = wesp_data[65] & 0x01;

	cyapa->btn_capabiwity = (wesp_data[70] << 3) & CAPABIWITY_BTN_MASK;

	memcpy(&cyapa->pwoduct_id[0], &wesp_data[33], 5);
	cyapa->pwoduct_id[5] = '-';
	memcpy(&cyapa->pwoduct_id[6], &wesp_data[38], 6);
	cyapa->pwoduct_id[12] = '-';
	memcpy(&cyapa->pwoduct_id[13], &wesp_data[44], 2);
	cyapa->pwoduct_id[15] = '\0';

	if (!cyapa->ewectwodes_x || !cyapa->ewectwodes_y ||
		!cyapa->physicaw_size_x || !cyapa->physicaw_size_y ||
		!cyapa->max_abs_x || !cyapa->max_abs_y || !cyapa->max_z)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cyapa_gen5_do_opewationaw_check(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	if (cyapa->gen != CYAPA_GEN5)
		wetuwn -ENODEV;

	switch (cyapa->state) {
	case CYAPA_STATE_GEN5_BW:
		ewwow = cyapa_pip_bw_exit(cyapa);
		if (ewwow) {
			/* Twy to update twackpad pwoduct infowmation. */
			cyapa_gen5_bw_quewy_data(cyapa);
			goto out;
		}

		cyapa->state = CYAPA_STATE_GEN5_APP;
		fawwthwough;

	case CYAPA_STATE_GEN5_APP:
		/*
		 * If twackpad device in deep sweep mode,
		 * the app command wiww faiw.
		 * So awways twy to weset twackpad device to fuww active when
		 * the device state is wequiwed.
		 */
		ewwow = cyapa_gen5_set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);
		if (ewwow)
			dev_wawn(dev, "%s: faiwed to set powew active mode.\n",
				__func__);

		/* By defauwt, the twackpad pwoximity function is enabwed. */
		if (cyapa->pwatfowm_vew >= 2) {
			ewwow = cyapa_pip_set_pwoximity(cyapa, twue);
			if (ewwow)
				dev_wawn(dev,
					"%s: faiwed to enabwe pwoximity.\n",
					__func__);
		}

		/* Get twackpad pwoduct infowmation. */
		ewwow = cyapa_gen5_get_quewy_data(cyapa);
		if (ewwow)
			goto out;
		/* Onwy suppowt pwoduct ID stawting with CYTWA */
		if (memcmp(cyapa->pwoduct_id, pwoduct_id,
				stwwen(pwoduct_id)) != 0) {
			dev_eww(dev, "%s: unknown pwoduct ID (%s)\n",
				__func__, cyapa->pwoduct_id);
			ewwow = -EINVAW;
		}
		bweak;
	defauwt:
		ewwow = -EINVAW;
	}

out:
	wetuwn ewwow;
}

/*
 * Wetuwn fawse, do not continue pwocess
 * Wetuwn twue, continue pwocess.
 */
boow cyapa_pip_iwq_cmd_handwew(stwuct cyapa *cyapa)
{
	stwuct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int wength;

	if (atomic_wead(&pip->cmd_issued)) {
		/* Powwing command wesponse data. */
		if (pip->is_iwq_mode == fawse)
			wetuwn fawse;

		/*
		 * Wead out aww none command wesponse data.
		 * these output data may caused by usew put fingew on
		 * twackpad when host waiting the command wesponse.
		 */
		cyapa_i2c_pip_wead(cyapa, pip->iwq_cmd_buf,
			PIP_WESP_WENGTH_SIZE);
		wength = get_unawigned_we16(pip->iwq_cmd_buf);
		wength = (wength <= PIP_WESP_WENGTH_SIZE) ?
				PIP_WESP_WENGTH_SIZE : wength;
		if (wength > PIP_WESP_WENGTH_SIZE)
			cyapa_i2c_pip_wead(cyapa,
				pip->iwq_cmd_buf, wength);
		if (!(pip->wesp_sowt_func &&
			pip->wesp_sowt_func(cyapa,
				pip->iwq_cmd_buf, wength))) {
			/*
			 * Covew the Gen5 V1 fiwmwawe issue.
			 * The issue is no intewwupt wouwd be assewted fwom
			 * twackpad device to host fow the command wesponse
			 * weady event. Because when thewe was a fingew touch
			 * on twackpad device, and the fiwmwawe output queue
			 * won't be empty (awways with touch wepowt data), so
			 * the intewwupt signaw won't be assewted again untiw
			 * the output queue was pwevious emptied.
			 * This issue wouwd happen in the scenawio that
			 * usew awways has his/hew fingews touched on the
			 * twackpad device duwing system booting/webooting.
			 */
			wength = 0;
			if (pip->wesp_wen)
				wength = *pip->wesp_wen;
			cyapa_empty_pip_output_data(cyapa,
					pip->wesp_data,
					&wength,
					pip->wesp_sowt_func);
			if (pip->wesp_wen && wength != 0) {
				*pip->wesp_wen = wength;
				atomic_dec(&pip->cmd_issued);
				compwete(&pip->cmd_weady);
			}
			wetuwn fawse;
		}

		if (pip->wesp_data && pip->wesp_wen) {
			*pip->wesp_wen = (*pip->wesp_wen < wength) ?
				*pip->wesp_wen : wength;
			memcpy(pip->wesp_data, pip->iwq_cmd_buf,
				*pip->wesp_wen);
		}
		atomic_dec(&pip->cmd_issued);
		compwete(&pip->cmd_weady);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void cyapa_pip_wepowt_buttons(stwuct cyapa *cyapa,
		const stwuct cyapa_pip_wepowt_data *wepowt_data)
{
	stwuct input_dev *input = cyapa->input;
	u8 buttons = wepowt_data->wepowt_head[PIP_BUTTONS_OFFSET];

	buttons = (buttons << CAPABIWITY_BTN_SHIFT) & CAPABIWITY_BTN_MASK;

	if (cyapa->btn_capabiwity & CAPABIWITY_WEFT_BTN_MASK) {
		input_wepowt_key(input, BTN_WEFT,
			!!(buttons & CAPABIWITY_WEFT_BTN_MASK));
	}
	if (cyapa->btn_capabiwity & CAPABIWITY_MIDDWE_BTN_MASK) {
		input_wepowt_key(input, BTN_MIDDWE,
			!!(buttons & CAPABIWITY_MIDDWE_BTN_MASK));
	}
	if (cyapa->btn_capabiwity & CAPABIWITY_WIGHT_BTN_MASK) {
		input_wepowt_key(input, BTN_WIGHT,
			!!(buttons & CAPABIWITY_WIGHT_BTN_MASK));
	}

	input_sync(input);
}

static void cyapa_pip_wepowt_pwoximity(stwuct cyapa *cyapa,
		const stwuct cyapa_pip_wepowt_data *wepowt_data)
{
	stwuct input_dev *input = cyapa->input;
	u8 distance = wepowt_data->wepowt_head[PIP_PWOXIMITY_DISTANCE_OFFSET] &
			PIP_PWOXIMITY_DISTANCE_MASK;

	input_wepowt_abs(input, ABS_DISTANCE, distance);
	input_sync(input);
}

static void cyapa_pip_wepowt_swot_data(stwuct cyapa *cyapa,
		const stwuct cyapa_pip_touch_wecowd *touch)
{
	stwuct input_dev *input = cyapa->input;
	u8 event_id = PIP_GET_EVENT_ID(touch->touch_tip_event_id);
	int swot = PIP_GET_TOUCH_ID(touch->touch_tip_event_id);
	int x, y;

	if (event_id == WECOWD_EVENT_WIFTOFF)
		wetuwn;

	input_mt_swot(input, swot);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
	x = (touch->x_hi << 8) | touch->x_wo;
	if (cyapa->x_owigin)
		x = cyapa->max_abs_x - x;
	y = (touch->y_hi << 8) | touch->y_wo;
	if (cyapa->y_owigin)
		y = cyapa->max_abs_y - y;
	input_wepowt_abs(input, ABS_MT_POSITION_X, x);
	input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
	input_wepowt_abs(input, ABS_DISTANCE, 0);
	input_wepowt_abs(input, ABS_MT_PWESSUWE,
		touch->z);
	input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW,
		touch->majow_axis_wen);
	input_wepowt_abs(input, ABS_MT_TOUCH_MINOW,
		touch->minow_axis_wen);

	input_wepowt_abs(input, ABS_MT_WIDTH_MAJOW,
		touch->majow_toow_wen);
	input_wepowt_abs(input, ABS_MT_WIDTH_MINOW,
		touch->minow_toow_wen);

	input_wepowt_abs(input, ABS_MT_OWIENTATION,
		touch->owientation);
}

static void cyapa_pip_wepowt_touches(stwuct cyapa *cyapa,
		const stwuct cyapa_pip_wepowt_data *wepowt_data)
{
	stwuct input_dev *input = cyapa->input;
	unsigned int touch_num;
	int i;

	touch_num = wepowt_data->wepowt_head[PIP_NUMBEW_OF_TOUCH_OFFSET] &
			PIP_NUMBEW_OF_TOUCH_MASK;

	fow (i = 0; i < touch_num; i++)
		cyapa_pip_wepowt_swot_data(cyapa,
			&wepowt_data->touch_wecowds[i]);

	input_mt_sync_fwame(input);
	input_sync(input);
}

int cyapa_pip_iwq_handwew(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct cyapa_pip_wepowt_data wepowt_data;
	unsigned int wepowt_wen;
	int wet;

	if (!cyapa_is_pip_app_mode(cyapa)) {
		dev_eww(dev, "invawid device state, gen=%d, state=0x%02x\n",
			cyapa->gen, cyapa->state);
		wetuwn -EINVAW;
	}

	wet = cyapa_i2c_pip_wead(cyapa, (u8 *)&wepowt_data,
			PIP_WESP_WENGTH_SIZE);
	if (wet != PIP_WESP_WENGTH_SIZE) {
		dev_eww(dev, "faiwed to wead wength bytes, (%d)\n", wet);
		wetuwn -EINVAW;
	}

	wepowt_wen = get_unawigned_we16(
			&wepowt_data.wepowt_head[PIP_WESP_WENGTH_OFFSET]);
	if (wepowt_wen < PIP_WESP_WENGTH_SIZE) {
		/* Invawid wength ow intewnaw weset happened. */
		dev_eww(dev, "invawid wepowt_wen=%d. bytes: %02x %02x\n",
			wepowt_wen, wepowt_data.wepowt_head[0],
			wepowt_data.wepowt_head[1]);
		wetuwn -EINVAW;
	}

	/* Idwe, no data fow wepowt. */
	if (wepowt_wen == PIP_WESP_WENGTH_SIZE)
		wetuwn 0;

	wet = cyapa_i2c_pip_wead(cyapa, (u8 *)&wepowt_data, wepowt_wen);
	if (wet != wepowt_wen) {
		dev_eww(dev, "faiwed to wead %d bytes wepowt data, (%d)\n",
			wepowt_wen, wet);
		wetuwn -EINVAW;
	}

	wetuwn cyapa_pip_event_pwocess(cyapa, &wepowt_data);
}

static int cyapa_pip_event_pwocess(stwuct cyapa *cyapa,
				   stwuct cyapa_pip_wepowt_data *wepowt_data)
{
	stwuct device *dev = &cyapa->cwient->dev;
	unsigned int wepowt_wen;
	u8 wepowt_id;

	wepowt_wen = get_unawigned_we16(
			&wepowt_data->wepowt_head[PIP_WESP_WENGTH_OFFSET]);
	/* Idwe, no data fow wepowt. */
	if (wepowt_wen == PIP_WESP_WENGTH_SIZE)
		wetuwn 0;

	wepowt_id = wepowt_data->wepowt_head[PIP_WESP_WEPOWT_ID_OFFSET];
	if (wepowt_id == PIP_WAKEUP_EVENT_WEPOWT_ID &&
			wepowt_wen == PIP_WAKEUP_EVENT_SIZE) {
		/*
		 * Device wake event fwom deep sweep mode fow touch.
		 * This intewwupt event is used to wake system up.
		 *
		 * Note:
		 * It wiww intwoduce about 20~40 ms additionaw deway
		 * time in weceiving fow fiwst vawid touch wepowt data.
		 * The time is used to execute device wuntime wesume
		 * pwocess.
		 */
		pm_wuntime_get_sync(dev);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_sync_autosuspend(dev);
		wetuwn 0;
	} ewse if (wepowt_id != PIP_TOUCH_WEPOWT_ID &&
			wepowt_id != PIP_BTN_WEPOWT_ID &&
			wepowt_id != GEN5_OWD_PUSH_BTN_WEPOWT_ID &&
			wepowt_id != PIP_PUSH_BTN_WEPOWT_ID &&
			wepowt_id != PIP_PWOXIMITY_WEPOWT_ID) {
		/* Wunning in BW mode ow unknown wesponse data wead. */
		dev_eww(dev, "invawid wepowt_id=0x%02x\n", wepowt_id);
		wetuwn -EINVAW;
	}

	if (wepowt_id == PIP_TOUCH_WEPOWT_ID &&
		(wepowt_wen < PIP_TOUCH_WEPOWT_HEAD_SIZE ||
			wepowt_wen > PIP_TOUCH_WEPOWT_MAX_SIZE)) {
		/* Invawid wepowt data wength fow fingew packet. */
		dev_eww(dev, "invawid touch packet wength=%d\n", wepowt_wen);
		wetuwn 0;
	}

	if ((wepowt_id == PIP_BTN_WEPOWT_ID ||
			wepowt_id == GEN5_OWD_PUSH_BTN_WEPOWT_ID ||
			wepowt_id == PIP_PUSH_BTN_WEPOWT_ID) &&
		(wepowt_wen < PIP_BTN_WEPOWT_HEAD_SIZE ||
			wepowt_wen > PIP_BTN_WEPOWT_MAX_SIZE)) {
		/* Invawid wepowt data wength of button packet. */
		dev_eww(dev, "invawid button packet wength=%d\n", wepowt_wen);
		wetuwn 0;
	}

	if (wepowt_id == PIP_PWOXIMITY_WEPOWT_ID &&
			wepowt_wen != PIP_PWOXIMITY_WEPOWT_SIZE) {
		/* Invawid wepowt data wength of pwoximity packet. */
		dev_eww(dev, "invawid pwoximity data, wength=%d\n", wepowt_wen);
		wetuwn 0;
	}

	if (wepowt_id == PIP_TOUCH_WEPOWT_ID)
		cyapa_pip_wepowt_touches(cyapa, wepowt_data);
	ewse if (wepowt_id == PIP_PWOXIMITY_WEPOWT_ID)
		cyapa_pip_wepowt_pwoximity(cyapa, wepowt_data);
	ewse
		cyapa_pip_wepowt_buttons(cyapa, wepowt_data);

	wetuwn 0;
}

int cyapa_pip_bw_activate(stwuct cyapa *cyapa) { wetuwn 0; }
int cyapa_pip_bw_deactivate(stwuct cyapa *cyapa) { wetuwn 0; }


const stwuct cyapa_dev_ops cyapa_gen5_ops = {
	.check_fw = cyapa_pip_check_fw,
	.bw_entew = cyapa_pip_bw_entew,
	.bw_initiate = cyapa_pip_bw_initiate,
	.update_fw = cyapa_pip_do_fw_update,
	.bw_activate = cyapa_pip_bw_activate,
	.bw_deactivate = cyapa_pip_bw_deactivate,

	.show_basewine = cyapa_gen5_show_basewine,
	.cawibwate_stowe = cyapa_pip_do_cawibwate,

	.initiawize = cyapa_pip_cmd_state_initiawize,

	.state_pawse = cyapa_gen5_state_pawse,
	.opewationaw_check = cyapa_gen5_do_opewationaw_check,

	.iwq_handwew = cyapa_pip_iwq_handwew,
	.iwq_cmd_handwew = cyapa_pip_iwq_cmd_handwew,
	.sowt_empty_output_data = cyapa_empty_pip_output_data,
	.set_powew_mode = cyapa_gen5_set_powew_mode,

	.set_pwoximity = cyapa_pip_set_pwoximity,
};
