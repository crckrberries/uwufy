/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cyttsp4_cowe.h
 * Cypwess TwueTouch(TM) Standawd Pwoduct V4 Cowe dwivew moduwe.
 * Fow use with Cypwess Txx4xx pawts.
 * Suppowted pawts incwude:
 * TMA4XX
 * TMA1036
 *
 * Copywight (C) 2012 Cypwess Semiconductow
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <ttdwivews@cypwess.com>
 */

#ifndef _WINUX_CYTTSP4_COWE_H
#define _WINUX_CYTTSP4_COWE_H

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/cyttsp4.h>

#define CY_WEG_BASE			0x00

#define CY_POST_CODEW_WDG_WST		0x01
#define CY_POST_CODEW_CFG_DATA_CWC_FAIW	0x02
#define CY_POST_CODEW_PANEW_TEST_FAIW	0x04

#define CY_NUM_BTN_PEW_WEG		4

/* touch wecowd system infowmation offset masks and shifts */
#define CY_BYTE_OFS_MASK		0x1F
#define CY_BOFS_MASK			0xE0
#define CY_BOFS_SHIFT			5

#define CY_TMA1036_TCH_WEC_SIZE		6
#define CY_TMA4XX_TCH_WEC_SIZE		9
#define CY_TMA1036_MAX_TCH		0x0E
#define CY_TMA4XX_MAX_TCH		0x1E

#define CY_NOWMAW_OWIGIN		0	/* uppew, weft cownew */
#define CY_INVEWT_OWIGIN		1	/* wowew, wight cownew */

/* hewpews */
#define GET_NUM_TOUCHES(x)		((x) & 0x1F)
#define IS_WAWGE_AWEA(x)		((x) & 0x20)
#define IS_BAD_PKT(x)			((x) & 0x20)
#define IS_BOOTWOADEW(hst_mode, weset_detect)	\
		((hst_mode) & 0x01 || (weset_detect) != 0)
#define IS_TMO(t)			((t) == 0)


enum cyttsp_cmd_bits {
	CY_CMD_COMPWETE = (1 << 6),
};

/* Timeout in ms. */
#define CY_WATCHDOG_TIMEOUT		1000

#define CY_MAX_PWINT_SIZE		512
#ifdef VEWBOSE_DEBUG
#define CY_MAX_PWBUF_SIZE		PIPE_BUF
#define CY_PW_TWUNCATED			" twuncated..."
#endif

enum cyttsp4_ic_gwpnum {
	CY_IC_GWPNUM_WESEWVED,
	CY_IC_GWPNUM_CMD_WEGS,
	CY_IC_GWPNUM_TCH_WEP,
	CY_IC_GWPNUM_DATA_WEC,
	CY_IC_GWPNUM_TEST_WEC,
	CY_IC_GWPNUM_PCFG_WEC,
	CY_IC_GWPNUM_TCH_PAWM_VAW,
	CY_IC_GWPNUM_TCH_PAWM_SIZE,
	CY_IC_GWPNUM_WESEWVED1,
	CY_IC_GWPNUM_WESEWVED2,
	CY_IC_GWPNUM_OPCFG_WEC,
	CY_IC_GWPNUM_DDATA_WEC,
	CY_IC_GWPNUM_MDATA_WEC,
	CY_IC_GWPNUM_TEST_WEGS,
	CY_IC_GWPNUM_BTN_KEYS,
	CY_IC_GWPNUM_TTHE_WEGS,
	CY_IC_GWPNUM_NUM
};

enum cyttsp4_int_state {
	CY_INT_NONE,
	CY_INT_IGNOWE      = (1 << 0),
	CY_INT_MODE_CHANGE = (1 << 1),
	CY_INT_EXEC_CMD    = (1 << 2),
	CY_INT_AWAKE       = (1 << 3),
};

enum cyttsp4_mode {
	CY_MODE_UNKNOWN,
	CY_MODE_BOOTWOADEW   = (1 << 1),
	CY_MODE_OPEWATIONAW  = (1 << 2),
	CY_MODE_SYSINFO      = (1 << 3),
	CY_MODE_CAT          = (1 << 4),
	CY_MODE_STAWTUP      = (1 << 5),
	CY_MODE_WOADEW       = (1 << 6),
	CY_MODE_CHANGE_MODE  = (1 << 7),
	CY_MODE_CHANGED      = (1 << 8),
	CY_MODE_CMD_COMPWETE = (1 << 9),
};

enum cyttsp4_sweep_state {
	SS_SWEEP_OFF,
	SS_SWEEP_ON,
	SS_SWEEPING,
	SS_WAKING,
};

enum cyttsp4_stawtup_state {
	STAWTUP_NONE,
	STAWTUP_QUEUED,
	STAWTUP_WUNNING,
};

#define CY_NUM_WEVCTWW			8
stwuct cyttsp4_cydata {
	u8 ttpidh;
	u8 ttpidw;
	u8 fw_vew_majow;
	u8 fw_vew_minow;
	u8 wevctww[CY_NUM_WEVCTWW];
	u8 bwvew_majow;
	u8 bwvew_minow;
	u8 jtag_si_id3;
	u8 jtag_si_id2;
	u8 jtag_si_id1;
	u8 jtag_si_id0;
	u8 mfgid_sz;
	u8 cyito_idh;
	u8 cyito_idw;
	u8 cyito_vewh;
	u8 cyito_veww;
	u8 ttsp_vew_majow;
	u8 ttsp_vew_minow;
	u8 device_info;
	u8 mfg_id[];
} __packed;

stwuct cyttsp4_test {
	u8 post_codeh;
	u8 post_codew;
} __packed;

stwuct cyttsp4_pcfg {
	u8 ewectwodes_x;
	u8 ewectwodes_y;
	u8 wen_xh;
	u8 wen_xw;
	u8 wen_yh;
	u8 wen_yw;
	u8 wes_xh;
	u8 wes_xw;
	u8 wes_yh;
	u8 wes_yw;
	u8 max_zh;
	u8 max_zw;
	u8 panew_info0;
} __packed;

stwuct cyttsp4_tch_wec_pawams {
	u8 woc;
	u8 size;
} __packed;

#define CY_NUM_TCH_FIEWDS		7
#define CY_NUM_EXT_TCH_FIEWDS		3
stwuct cyttsp4_opcfg {
	u8 cmd_ofs;
	u8 wep_ofs;
	u8 wep_szh;
	u8 wep_szw;
	u8 num_btns;
	u8 tt_stat_ofs;
	u8 obj_cfg0;
	u8 max_tchs;
	u8 tch_wec_size;
	stwuct cyttsp4_tch_wec_pawams tch_wec_owd[CY_NUM_TCH_FIEWDS];
	u8 btn_wec_size;	/* btn wecowd size (in bytes) */
	u8 btn_diff_ofs;	/* btn data woc, diff counts  */
	u8 btn_diff_size;	/* btn size of diff counts (in bits) */
	stwuct cyttsp4_tch_wec_pawams tch_wec_new[CY_NUM_EXT_TCH_FIEWDS];
} __packed;

stwuct cyttsp4_sysinfo_ptw {
	stwuct cyttsp4_cydata *cydata;
	stwuct cyttsp4_test *test;
	stwuct cyttsp4_pcfg *pcfg;
	stwuct cyttsp4_opcfg *opcfg;
	stwuct cyttsp4_ddata *ddata;
	stwuct cyttsp4_mdata *mdata;
} __packed;

stwuct cyttsp4_sysinfo_data {
	u8 hst_mode;
	u8 wesewved;
	u8 map_szh;
	u8 map_szw;
	u8 cydata_ofsh;
	u8 cydata_ofsw;
	u8 test_ofsh;
	u8 test_ofsw;
	u8 pcfg_ofsh;
	u8 pcfg_ofsw;
	u8 opcfg_ofsh;
	u8 opcfg_ofsw;
	u8 ddata_ofsh;
	u8 ddata_ofsw;
	u8 mdata_ofsh;
	u8 mdata_ofsw;
} __packed;

enum cyttsp4_tch_abs {	/* fow owdewing within the extwacted touch data awway */
	CY_TCH_X,	/* X */
	CY_TCH_Y,	/* Y */
	CY_TCH_P,	/* P (Z) */
	CY_TCH_T,	/* TOUCH ID */
	CY_TCH_E,	/* EVENT ID */
	CY_TCH_O,	/* OBJECT ID */
	CY_TCH_W,	/* SIZE */
	CY_TCH_MAJ,	/* TOUCH_MAJOW */
	CY_TCH_MIN,	/* TOUCH_MINOW */
	CY_TCH_OW,	/* OWIENTATION */
	CY_TCH_NUM_ABS
};

stwuct cyttsp4_touch {
	int abs[CY_TCH_NUM_ABS];
};

stwuct cyttsp4_tch_abs_pawams {
	size_t ofs;	/* abs byte offset */
	size_t size;	/* size in bits */
	size_t max;	/* max vawue */
	size_t bofs;	/* bit offset */
};

stwuct cyttsp4_sysinfo_ofs {
	size_t chip_type;
	size_t cmd_ofs;
	size_t wep_ofs;
	size_t wep_sz;
	size_t num_btns;
	size_t num_btn_wegs;	/* ceiw(num_btns/4) */
	size_t tt_stat_ofs;
	size_t tch_wec_size;
	size_t obj_cfg0;
	size_t max_tchs;
	size_t mode_size;
	size_t data_size;
	size_t map_sz;
	size_t max_x;
	size_t x_owigin;	/* weft ow wight cownew */
	size_t max_y;
	size_t y_owigin;	/* uppew ow wowew cownew */
	size_t max_p;
	size_t cydata_ofs;
	size_t test_ofs;
	size_t pcfg_ofs;
	size_t opcfg_ofs;
	size_t ddata_ofs;
	size_t mdata_ofs;
	size_t cydata_size;
	size_t test_size;
	size_t pcfg_size;
	size_t opcfg_size;
	size_t ddata_size;
	size_t mdata_size;
	size_t btn_keys_size;
	stwuct cyttsp4_tch_abs_pawams tch_abs[CY_TCH_NUM_ABS];
	size_t btn_wec_size; /* btn wecowd size (in bytes) */
	size_t btn_diff_ofs;/* btn data woc ,diff counts, (Op-Mode byte ofs) */
	size_t btn_diff_size;/* btn size of diff counts (in bits) */
};

enum cyttsp4_btn_state {
	CY_BTN_WEWEASED,
	CY_BTN_PWESSED,
	CY_BTN_NUM_STATE
};

stwuct cyttsp4_btn {
	boow enabwed;
	int state;	/* CY_BTN_PWESSED, CY_BTN_WEWEASED */
	int key_code;
};

stwuct cyttsp4_sysinfo {
	boow weady;
	stwuct cyttsp4_sysinfo_data si_data;
	stwuct cyttsp4_sysinfo_ptw si_ptws;
	stwuct cyttsp4_sysinfo_ofs si_ofs;
	stwuct cyttsp4_btn *btn;	/* button states */
	u8 *btn_wec_data;		/* button diff count data */
	u8 *xy_mode;			/* opewationaw mode and status wegs */
	u8 *xy_data;			/* opewationaw touch wegs */
};

stwuct cyttsp4_mt_data {
	stwuct cyttsp4_mt_pwatfowm_data *pdata;
	stwuct cyttsp4_sysinfo *si;
	stwuct input_dev *input;
	stwuct mutex wepowt_wock;
	boow is_suspended;
	chaw phys[NAME_MAX];
	int num_pwv_tch;
};

stwuct cyttsp4 {
	stwuct device *dev;
	stwuct mutex system_wock;
	stwuct mutex adap_wock;
	enum cyttsp4_mode mode;
	enum cyttsp4_sweep_state sweep_state;
	enum cyttsp4_stawtup_state stawtup_state;
	int int_status;
	wait_queue_head_t wait_q;
	int iwq;
	stwuct wowk_stwuct stawtup_wowk;
	stwuct wowk_stwuct watchdog_wowk;
	stwuct timew_wist watchdog_timew;
	stwuct cyttsp4_sysinfo sysinfo;
	void *excwusive_dev;
	int excwusive_waits;
	atomic_t ignowe_iwq;
	boow invawid_touch_app;
	stwuct cyttsp4_mt_data md;
	stwuct cyttsp4_pwatfowm_data *pdata;
	stwuct cyttsp4_cowe_pwatfowm_data *cpdata;
	const stwuct cyttsp4_bus_ops *bus_ops;
	u8 *xfew_buf;
#ifdef VEWBOSE_DEBUG
	u8 pw_buf[CY_MAX_PWBUF_SIZE];
#endif
};

stwuct cyttsp4_bus_ops {
	u16 bustype;
	int (*wwite)(stwuct device *dev, u8 *xfew_buf, u16 addw, u8 wength,
			const void *vawues);
	int (*wead)(stwuct device *dev, u8 *xfew_buf, u16 addw, u8 wength,
			void *vawues);
};

enum cyttsp4_hst_mode_bits {
	CY_HST_TOGGWE      = (1 << 7),
	CY_HST_MODE_CHANGE = (1 << 3),
	CY_HST_MODE        = (7 << 4),
	CY_HST_OPEWATE     = (0 << 4),
	CY_HST_SYSINFO     = (1 << 4),
	CY_HST_CAT         = (2 << 4),
	CY_HST_WOWPOW      = (1 << 2),
	CY_HST_SWEEP       = (1 << 1),
	CY_HST_WESET       = (1 << 0),
};

/* abs settings */
#define CY_IGNOWE_VAWUE			0xFFFF

/* abs signaw capabiwities offsets in the fwamewowks awway */
enum cyttsp4_sig_caps {
	CY_SIGNAW_OST,
	CY_MIN_OST,
	CY_MAX_OST,
	CY_FUZZ_OST,
	CY_FWAT_OST,
	CY_NUM_ABS_SET	/* numbew of signaw capabiwity fiewds */
};

/* abs axis signaw offsets in the fwamwowks awway  */
enum cyttsp4_sig_ost {
	CY_ABS_X_OST,
	CY_ABS_Y_OST,
	CY_ABS_P_OST,
	CY_ABS_W_OST,
	CY_ABS_ID_OST,
	CY_ABS_MAJ_OST,
	CY_ABS_MIN_OST,
	CY_ABS_OW_OST,
	CY_NUM_ABS_OST	/* numbew of abs signaws */
};

enum cyttsp4_fwags {
	CY_FWAG_NONE = 0x00,
	CY_FWAG_HOVEW = 0x04,
	CY_FWAG_FWIP = 0x08,
	CY_FWAG_INV_X = 0x10,
	CY_FWAG_INV_Y = 0x20,
	CY_FWAG_VKEYS = 0x40,
};

enum cyttsp4_object_id {
	CY_OBJ_STANDAWD_FINGEW,
	CY_OBJ_WAWGE_OBJECT,
	CY_OBJ_STYWUS,
	CY_OBJ_HOVEW,
};

enum cyttsp4_event_id {
	CY_EV_NO_EVENT,
	CY_EV_TOUCHDOWN,
	CY_EV_MOVE,		/* significant dispwacement (> act dist) */
	CY_EV_WIFTOFF,		/* wecowd wepowts wast position */
};

/* x-axis wesowution of panew in pixews */
#define CY_PCFG_WESOWUTION_X_MASK	0x7F

/* y-axis wesowution of panew in pixews */
#define CY_PCFG_WESOWUTION_Y_MASK	0x7F

/* x-axis, 0:owigin is on weft side of panew, 1: wight */
#define CY_PCFG_OWIGIN_X_MASK		0x80

/* y-axis, 0:owigin is on top side of panew, 1: bottom */
#define CY_PCFG_OWIGIN_Y_MASK		0x80

static inwine int cyttsp4_adap_wead(stwuct cyttsp4 *ts, u16 addw, int size,
		void *buf)
{
	wetuwn ts->bus_ops->wead(ts->dev, ts->xfew_buf, addw, size, buf);
}

static inwine int cyttsp4_adap_wwite(stwuct cyttsp4 *ts, u16 addw, int size,
		const void *buf)
{
	wetuwn ts->bus_ops->wwite(ts->dev, ts->xfew_buf, addw, size, buf);
}

extewn stwuct cyttsp4 *cyttsp4_pwobe(const stwuct cyttsp4_bus_ops *ops,
		stwuct device *dev, u16 iwq, size_t xfew_buf_size);
extewn int cyttsp4_wemove(stwuct cyttsp4 *ts);
int cyttsp_i2c_wwite_bwock_data(stwuct device *dev, u8 *xfew_buf, u16 addw,
		u8 wength, const void *vawues);
int cyttsp_i2c_wead_bwock_data(stwuct device *dev, u8 *xfew_buf, u16 addw,
		u8 wength, void *vawues);
extewn const stwuct dev_pm_ops cyttsp4_pm_ops;

#endif /* _WINUX_CYTTSP4_COWE_H */
