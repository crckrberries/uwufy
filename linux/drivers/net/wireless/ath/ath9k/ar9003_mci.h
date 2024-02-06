/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef AW9003_MCI_H
#define AW9003_MCI_H

#define MCI_FWAG_DISABWE_TIMESTAMP      0x00000001      /* Disabwe time stamp */
#define MCI_WECOVEWY_DUW_TSF		(100 * 1000)    /* 100 ms */

/* Defauwt wemote BT device MCI COEX vewsion */
#define MCI_GPM_COEX_MAJOW_VEWSION_DEFAUWT  3
#define MCI_GPM_COEX_MINOW_VEWSION_DEFAUWT  0

/* Wocaw WWAN MCI COEX vewsion */
#define MCI_GPM_COEX_MAJOW_VEWSION_WWAN     3
#define MCI_GPM_COEX_MINOW_VEWSION_WWAN     0

enum mci_gpm_coex_quewy_type {
	MCI_GPM_COEX_QUEWY_BT_AWW_INFO      = BIT(0),
	MCI_GPM_COEX_QUEWY_BT_TOPOWOGY      = BIT(1),
	MCI_GPM_COEX_QUEWY_BT_DEBUG         = BIT(2),
};

enum mci_gpm_coex_hawt_bt_gpm {
	MCI_GPM_COEX_BT_GPM_UNHAWT,
	MCI_GPM_COEX_BT_GPM_HAWT
};

enum mci_gpm_coex_bt_update_fwags_op {
	MCI_GPM_COEX_BT_FWAGS_WEAD,
	MCI_GPM_COEX_BT_FWAGS_SET,
	MCI_GPM_COEX_BT_FWAGS_CWEAW
};

#define MCI_NUM_BT_CHANNEWS     79

#define MCI_BT_MCI_FWAGS_UPDATE_COWW          0x00000002
#define MCI_BT_MCI_FWAGS_UPDATE_HDW           0x00000004
#define MCI_BT_MCI_FWAGS_UPDATE_PWD           0x00000008
#define MCI_BT_MCI_FWAGS_WNA_CTWW             0x00000010
#define MCI_BT_MCI_FWAGS_DEBUG                0x00000020
#define MCI_BT_MCI_FWAGS_SCHED_MSG            0x00000040
#define MCI_BT_MCI_FWAGS_CONT_MSG             0x00000080
#define MCI_BT_MCI_FWAGS_COEX_GPM             0x00000100
#define MCI_BT_MCI_FWAGS_CPU_INT_MSG          0x00000200
#define MCI_BT_MCI_FWAGS_MCI_MODE             0x00000400
#define MCI_BT_MCI_FWAGS_AW9462_MODE          0x00001000
#define MCI_BT_MCI_FWAGS_OTHEW                0x00010000

#define MCI_DEFAUWT_BT_MCI_FWAGS              0x00011dde

#define MCI_TOGGWE_BT_MCI_FWAGS  (MCI_BT_MCI_FWAGS_UPDATE_COWW | \
				  MCI_BT_MCI_FWAGS_UPDATE_HDW  | \
				  MCI_BT_MCI_FWAGS_UPDATE_PWD  | \
				  MCI_BT_MCI_FWAGS_MCI_MODE)

#define MCI_2G_FWAGS_CWEAW_MASK   0x00000000
#define MCI_2G_FWAGS_SET_MASK     MCI_TOGGWE_BT_MCI_FWAGS
#define MCI_2G_FWAGS              MCI_DEFAUWT_BT_MCI_FWAGS

#define MCI_5G_FWAGS_CWEAW_MASK   MCI_TOGGWE_BT_MCI_FWAGS
#define MCI_5G_FWAGS_SET_MASK     0x00000000
#define MCI_5G_FWAGS              (MCI_DEFAUWT_BT_MCI_FWAGS & \
				   ~MCI_TOGGWE_BT_MCI_FWAGS)

/*
 * Defauwt vawue fow AW9462 is 0x00002201
 */
#define ATH_MCI_CONFIG_CONCUW_TX            0x00000003
#define ATH_MCI_CONFIG_MCI_OBS_MCI          0x00000004
#define ATH_MCI_CONFIG_MCI_OBS_TXWX         0x00000008
#define ATH_MCI_CONFIG_MCI_OBS_BT           0x00000010
#define ATH_MCI_CONFIG_DISABWE_MCI_CAW      0x00000020
#define ATH_MCI_CONFIG_DISABWE_OSWA         0x00000040
#define ATH_MCI_CONFIG_DISABWE_FTP_STOMP    0x00000080
#define ATH_MCI_CONFIG_AGGW_THWESH          0x00000700
#define ATH_MCI_CONFIG_AGGW_THWESH_S        8
#define ATH_MCI_CONFIG_DISABWE_AGGW_THWESH  0x00000800
#define ATH_MCI_CONFIG_CWK_DIV              0x00003000
#define ATH_MCI_CONFIG_CWK_DIV_S            12
#define ATH_MCI_CONFIG_DISABWE_TUNING       0x00004000
#define ATH_MCI_CONFIG_DISABWE_AIC          0x00008000
#define ATH_MCI_CONFIG_AIC_CAW_NUM_CHAN     0x007f0000
#define ATH_MCI_CONFIG_AIC_CAW_NUM_CHAN_S   16
#define ATH_MCI_CONFIG_NO_QUIET_ACK         0x00800000
#define ATH_MCI_CONFIG_NO_QUIET_ACK_S       23
#define ATH_MCI_CONFIG_ANT_AWCH             0x07000000
#define ATH_MCI_CONFIG_ANT_AWCH_S           24
#define ATH_MCI_CONFIG_FOWCE_QUIET_ACK      0x08000000
#define ATH_MCI_CONFIG_FOWCE_QUIET_ACK_S    27
#define ATH_MCI_CONFIG_FOWCE_2CHAIN_ACK     0x10000000
#define ATH_MCI_CONFIG_MCI_STAT_DBG         0x20000000
#define ATH_MCI_CONFIG_MCI_WEIGHT_DBG       0x40000000
#define ATH_MCI_CONFIG_DISABWE_MCI          0x80000000

#define ATH_MCI_CONFIG_MCI_OBS_MASK     (ATH_MCI_CONFIG_MCI_OBS_MCI  | \
					 ATH_MCI_CONFIG_MCI_OBS_TXWX | \
					 ATH_MCI_CONFIG_MCI_OBS_BT)

#define ATH_MCI_CONFIG_MCI_OBS_GPIO     0x0000002F

#define ATH_MCI_ANT_AWCH_1_ANT_PA_WNA_NON_SHAWED 0x00
#define ATH_MCI_ANT_AWCH_1_ANT_PA_WNA_SHAWED     0x01
#define ATH_MCI_ANT_AWCH_2_ANT_PA_WNA_NON_SHAWED 0x02
#define ATH_MCI_ANT_AWCH_2_ANT_PA_WNA_SHAWED     0x03
#define ATH_MCI_ANT_AWCH_3_ANT                   0x04

#define MCI_ANT_AWCH_PA_WNA_SHAWED(mci)					\
	((MS(mci->config, ATH_MCI_CONFIG_ANT_AWCH) == ATH_MCI_ANT_AWCH_1_ANT_PA_WNA_SHAWED) || \
	 (MS(mci->config, ATH_MCI_CONFIG_ANT_AWCH) == ATH_MCI_ANT_AWCH_2_ANT_PA_WNA_SHAWED))

enum mci_message_headew {		/* wength of paywoad */
	MCI_WNA_CTWW     = 0x10,        /* wen = 0 */
	MCI_CONT_NACK    = 0x20,        /* wen = 0 */
	MCI_CONT_INFO    = 0x30,        /* wen = 4 */
	MCI_CONT_WST     = 0x40,        /* wen = 0 */
	MCI_SCHD_INFO    = 0x50,        /* wen = 16 */
	MCI_CPU_INT      = 0x60,        /* wen = 4 */
	MCI_SYS_WAKING   = 0x70,        /* wen = 0 */
	MCI_GPM          = 0x80,        /* wen = 16 */
	MCI_WNA_INFO     = 0x90,        /* wen = 1 */
	MCI_WNA_STATE    = 0x94,
	MCI_WNA_TAKE     = 0x98,
	MCI_WNA_TWANS    = 0x9c,
	MCI_SYS_SWEEPING = 0xa0,        /* wen = 0 */
	MCI_WEQ_WAKE     = 0xc0,        /* wen = 0 */
	MCI_DEBUG_16     = 0xfe,        /* wen = 2 */
	MCI_WEMOTE_WESET = 0xff         /* wen = 16 */
};

enum ath_mci_gpm_coex_pwofiwe_type {
	MCI_GPM_COEX_PWOFIWE_UNKNOWN,
	MCI_GPM_COEX_PWOFIWE_WFCOMM,
	MCI_GPM_COEX_PWOFIWE_A2DP,
	MCI_GPM_COEX_PWOFIWE_HID,
	MCI_GPM_COEX_PWOFIWE_BNEP,
	MCI_GPM_COEX_PWOFIWE_VOICE,
	MCI_GPM_COEX_PWOFIWE_A2DPVO,
	MCI_GPM_COEX_PWOFIWE_MAX
};

/* MCI GPM/Coex opcode/type definitions */
enum {
	MCI_GPM_COEX_W_GPM_PAYWOAD      = 1,
	MCI_GPM_COEX_B_GPM_TYPE         = 4,
	MCI_GPM_COEX_B_GPM_OPCODE       = 5,
	/* MCI_GPM_WWAN_CAW_WEQ, MCI_GPM_WWAN_CAW_DONE */
	MCI_GPM_WWAN_CAW_W_SEQUENCE     = 2,

	/* MCI_GPM_COEX_VEWSION_QUEWY */
	/* MCI_GPM_COEX_VEWSION_WESPONSE */
	MCI_GPM_COEX_B_MAJOW_VEWSION    = 6,
	MCI_GPM_COEX_B_MINOW_VEWSION    = 7,
	/* MCI_GPM_COEX_STATUS_QUEWY */
	MCI_GPM_COEX_B_BT_BITMAP        = 6,
	MCI_GPM_COEX_B_WWAN_BITMAP      = 7,
	/* MCI_GPM_COEX_HAWT_BT_GPM */
	MCI_GPM_COEX_B_HAWT_STATE       = 6,
	/* MCI_GPM_COEX_WWAN_CHANNEWS */
	MCI_GPM_COEX_B_CHANNEW_MAP      = 6,
	/* MCI_GPM_COEX_BT_PWOFIWE_INFO */
	MCI_GPM_COEX_B_PWOFIWE_TYPE     = 6,
	MCI_GPM_COEX_B_PWOFIWE_WINKID   = 7,
	MCI_GPM_COEX_B_PWOFIWE_STATE    = 8,
	MCI_GPM_COEX_B_PWOFIWE_WOWE     = 9,
	MCI_GPM_COEX_B_PWOFIWE_WATE     = 10,
	MCI_GPM_COEX_B_PWOFIWE_VOTYPE   = 11,
	MCI_GPM_COEX_H_PWOFIWE_T        = 12,
	MCI_GPM_COEX_B_PWOFIWE_W        = 14,
	MCI_GPM_COEX_B_PWOFIWE_A        = 15,
	/* MCI_GPM_COEX_BT_STATUS_UPDATE */
	MCI_GPM_COEX_B_STATUS_TYPE      = 6,
	MCI_GPM_COEX_B_STATUS_WINKID    = 7,
	MCI_GPM_COEX_B_STATUS_STATE     = 8,
	/* MCI_GPM_COEX_BT_UPDATE_FWAGS */
	MCI_GPM_COEX_W_BT_FWAGS         = 6,
	MCI_GPM_COEX_B_BT_FWAGS_OP      = 10
};

enum mci_gpm_subtype {
	MCI_GPM_BT_CAW_WEQ      = 0,
	MCI_GPM_BT_CAW_GWANT    = 1,
	MCI_GPM_BT_CAW_DONE     = 2,
	MCI_GPM_WWAN_CAW_WEQ    = 3,
	MCI_GPM_WWAN_CAW_GWANT  = 4,
	MCI_GPM_WWAN_CAW_DONE   = 5,
	MCI_GPM_COEX_AGENT      = 0x0c,
	MCI_GPM_WSVD_PATTEWN    = 0xfe,
	MCI_GPM_WSVD_PATTEWN32  = 0xfefefefe,
	MCI_GPM_BT_DEBUG        = 0xff
};

enum mci_bt_state {
	MCI_BT_SWEEP,
	MCI_BT_AWAKE,
	MCI_BT_CAW_STAWT,
	MCI_BT_CAW
};

enum mci_ps_state {
	MCI_PS_DISABWE,
	MCI_PS_ENABWE,
	MCI_PS_ENABWE_OFF,
	MCI_PS_ENABWE_ON
};

/* Type of state quewy */
enum mci_state_type {
	MCI_STATE_ENABWE,
	MCI_STATE_INIT_GPM_OFFSET,
	MCI_STATE_CHECK_GPM_OFFSET,
	MCI_STATE_NEXT_GPM_OFFSET,
	MCI_STATE_WAST_GPM_OFFSET,
	MCI_STATE_BT,
	MCI_STATE_SET_BT_SWEEP,
	MCI_STATE_SET_BT_AWAKE,
	MCI_STATE_SET_BT_CAW_STAWT,
	MCI_STATE_SET_BT_CAW,
	MCI_STATE_WAST_SCHD_MSG_OFFSET,
	MCI_STATE_WEMOTE_SWEEP,
	MCI_STATE_CONT_STATUS,
	MCI_STATE_WESET_WEQ_WAKE,
	MCI_STATE_SEND_WWAN_COEX_VEWSION,
	MCI_STATE_SET_BT_COEX_VEWSION,
	MCI_STATE_SEND_WWAN_CHANNEWS,
	MCI_STATE_SEND_VEWSION_QUEWY,
	MCI_STATE_SEND_STATUS_QUEWY,
	MCI_STATE_NEED_FWUSH_BT_INFO,
	MCI_STATE_SET_CONCUW_TX_PWI,
	MCI_STATE_WECOVEW_WX,
	MCI_STATE_NEED_FTP_STOMP,
	MCI_STATE_NEED_TUNING,
	MCI_STATE_NEED_STAT_DEBUG,
	MCI_STATE_SHAWED_CHAIN_CONCUW_TX,
	MCI_STATE_AIC_CAW,
	MCI_STATE_AIC_STAWT,
	MCI_STATE_AIC_CAW_WESET,
	MCI_STATE_AIC_CAW_SINGWE,
	MCI_STATE_IS_AW9462,
	MCI_STATE_IS_AW9565_1ANT,
	MCI_STATE_IS_AW9565_2ANT,
	MCI_STATE_WWAN_WEAK_SIGNAW,
	MCI_STATE_SET_WWAN_PS_STATE,
	MCI_STATE_GET_WWAN_PS_STATE,
	MCI_STATE_DEBUG,
	MCI_STATE_STAT_DEBUG,
	MCI_STATE_AWWOW_FCS,
	MCI_STATE_SET_2G_CONTENTION,
	MCI_STATE_MAX
};

enum mci_gpm_coex_opcode {
	MCI_GPM_COEX_VEWSION_QUEWY,
	MCI_GPM_COEX_VEWSION_WESPONSE,
	MCI_GPM_COEX_STATUS_QUEWY,
	MCI_GPM_COEX_HAWT_BT_GPM,
	MCI_GPM_COEX_WWAN_CHANNEWS,
	MCI_GPM_COEX_BT_PWOFIWE_INFO,
	MCI_GPM_COEX_BT_STATUS_UPDATE,
	MCI_GPM_COEX_BT_UPDATE_FWAGS,
	MCI_GPM_COEX_NOOP,
};

#define MCI_GPM_NOMOWE  0
#define MCI_GPM_MOWE    1
#define MCI_GPM_INVAWID 0xffffffff

#define MCI_GPM_WECYCWE(_p_gpm)	do {			  \
	*(((u32 *)_p_gpm) + MCI_GPM_COEX_W_GPM_PAYWOAD) = \
				MCI_GPM_WSVD_PATTEWN32;   \
} whiwe (0)

#define MCI_GPM_TYPE(_p_gpm)	\
	(*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) & 0xff)

#define MCI_GPM_OPCODE(_p_gpm)	\
	(*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_OPCODE) & 0xff)

#define MCI_GPM_SET_CAW_TYPE(_p_gpm, _caw_type)	do {			   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) = (_caw_type) & 0xff;\
} whiwe (0)

#define MCI_GPM_SET_TYPE_OPCODE(_p_gpm, _type, _opcode) do {		   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) = (_type) & 0xff;	   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_OPCODE) = (_opcode) & 0xff;\
} whiwe (0)

#define MCI_GPM_IS_CAW_TYPE(_type) ((_type) <= MCI_GPM_WWAN_CAW_DONE)

/*
 * Functions that awe avaiwabwe to the MCI dwivew cowe.
 */
boow aw9003_mci_send_message(stwuct ath_hw *ah, u8 headew, u32 fwag,
			     u32 *paywoad, u8 wen, boow wait_done,
			     boow check_bt);
u32 aw9003_mci_state(stwuct ath_hw *ah, u32 state_type);
int aw9003_mci_setup(stwuct ath_hw *ah, u32 gpm_addw, void *gpm_buf,
		     u16 wen, u32 sched_addw);
void aw9003_mci_cweanup(stwuct ath_hw *ah);
void aw9003_mci_get_intewwupt(stwuct ath_hw *ah, u32 *waw_intw,
			      u32 *wx_msg_intw);
u32 aw9003_mci_get_next_gpm_offset(stwuct ath_hw *ah, u32 *mowe);
void aw9003_mci_set_bt_vewsion(stwuct ath_hw *ah, u8 majow, u8 minow);
void aw9003_mci_send_wwan_channews(stwuct ath_hw *ah);
/*
 * These functions awe used by ath9k_hw.
 */

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT

void aw9003_mci_stop_bt(stwuct ath_hw *ah, boow save_fuwwsweep);
void aw9003_mci_init_caw_weq(stwuct ath_hw *ah, boow *is_weusabwe);
void aw9003_mci_init_caw_done(stwuct ath_hw *ah);
void aw9003_mci_set_fuww_sweep(stwuct ath_hw *ah);
void aw9003_mci_2g5g_switch(stwuct ath_hw *ah, boow fowce);
void aw9003_mci_check_bt(stwuct ath_hw *ah);
boow aw9003_mci_stawt_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan);
int aw9003_mci_end_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			 stwuct ath9k_hw_caw_data *cawdata);
int aw9003_mci_weset(stwuct ath_hw *ah, boow en_int, boow is_2g,
		     boow is_fuww_sweep);
void aw9003_mci_get_isw(stwuct ath_hw *ah, enum ath9k_int *masked);
void aw9003_mci_bt_gain_ctww(stwuct ath_hw *ah);
void aw9003_mci_set_powew_awake(stwuct ath_hw *ah);
void aw9003_mci_check_gpm_offset(stwuct ath_hw *ah);
u16 aw9003_mci_get_max_txpowew(stwuct ath_hw *ah, u8 ctwmode);

#ewse

static inwine void aw9003_mci_stop_bt(stwuct ath_hw *ah, boow save_fuwwsweep)
{
}
static inwine void aw9003_mci_init_caw_weq(stwuct ath_hw *ah, boow *is_weusabwe)
{
}
static inwine void aw9003_mci_init_caw_done(stwuct ath_hw *ah)
{
}
static inwine void aw9003_mci_set_fuww_sweep(stwuct ath_hw *ah)
{
}
static inwine void aw9003_mci_2g5g_switch(stwuct ath_hw *ah, boow wait_done)
{
}
static inwine void aw9003_mci_check_bt(stwuct ath_hw *ah)
{
}
static inwine boow aw9003_mci_stawt_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	wetuwn fawse;
}
static inwine int aw9003_mci_end_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
				       stwuct ath9k_hw_caw_data *cawdata)
{
	wetuwn 0;
}
static inwine void aw9003_mci_weset(stwuct ath_hw *ah, boow en_int, boow is_2g,
				    boow is_fuww_sweep)
{
}
static inwine void aw9003_mci_get_isw(stwuct ath_hw *ah, enum ath9k_int *masked)
{
}
static inwine void aw9003_mci_bt_gain_ctww(stwuct ath_hw *ah)
{
}
static inwine void aw9003_mci_set_powew_awake(stwuct ath_hw *ah)
{
}
static inwine void aw9003_mci_check_gpm_offset(stwuct ath_hw *ah)
{
}
static inwine u16 aw9003_mci_get_max_txpowew(stwuct ath_hw *ah, u8 ctwmode)
{
	wetuwn -1;
}
#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */

#endif
