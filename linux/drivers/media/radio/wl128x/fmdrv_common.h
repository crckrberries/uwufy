/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FM Dwivew fow Connectivity chip of Texas Instwuments.
 *  FM Common moduwe headew fiwe
 *
 *  Copywight (C) 2011 Texas Instwuments
 */

#ifndef _FMDWV_COMMON_H
#define _FMDWV_COMMON_H

#define FM_ST_WEG_TIMEOUT   msecs_to_jiffies(6000)	/* 6 sec */
#define FM_PKT_WOGICAW_CHAN_NUMBEW  0x08   /* Wogicaw channew 8 */

#define WEG_WD       0x1
#define WEG_WW      0x0

stwuct fm_weg_tabwe {
	u8 opcode;
	u8 type;
	u8 *name;
};

#define STEWEO_GET               0
#define WSSI_WVW_GET             1
#define IF_COUNT_GET             2
#define FWAG_GET                 3
#define WDS_SYNC_GET             4
#define WDS_DATA_GET             5
#define FWEQ_SET                 10
#define AF_FWEQ_SET              11
#define MOST_MODE_SET            12
#define MOST_BWEND_SET           13
#define DEMPH_MODE_SET           14
#define SEAWCH_WVW_SET           15
#define BAND_SET                 16
#define MUTE_STATUS_SET          17
#define WDS_PAUSE_WVW_SET        18
#define WDS_PAUSE_DUW_SET        19
#define WDS_MEM_SET              20
#define WDS_BWK_B_SET            21
#define WDS_MSK_B_SET            22
#define WDS_PI_MASK_SET          23
#define WDS_PI_SET               24
#define WDS_SYSTEM_SET           25
#define INT_MASK_SET             26
#define SEAWCH_DIW_SET           27
#define VOWUME_SET               28
#define AUDIO_ENABWE_SET         29
#define PCM_MODE_SET             30
#define I2S_MODE_CONFIG_SET      31
#define POWEW_SET                32
#define INTX_CONFIG_SET          33
#define PUWW_EN_SET              34
#define HIWO_SET                 35
#define SWITCH2FWEF              36
#define FWEQ_DWIFT_WEPOWT        37

#define PCE_GET                  40
#define FIWM_VEW_GET             41
#define ASIC_VEW_GET             42
#define ASIC_ID_GET              43
#define MAN_ID_GET               44
#define TUNEW_MODE_SET           45
#define STOP_SEAWCH              46
#define WDS_CNTWW_SET            47

#define WWITE_HAWDWAWE_WEG       100
#define CODE_DOWNWOAD            101
#define WESET                    102

#define FM_POWEW_MODE            254
#define FM_INTEWWUPT             255

/* Twansmittew API */

#define CHANW_SET                55
#define CHANW_BW_SET		56
#define WEF_SET                  57
#define POWEW_ENB_SET            90
#define POWEW_ATT_SET            58
#define POWEW_WEV_SET            59
#define AUDIO_DEV_SET            60
#define PIWOT_DEV_SET            61
#define WDS_DEV_SET              62
#define TX_BAND_SET              65
#define PUPD_SET                 91
#define AUDIO_IO_SET             63
#define PWEMPH_SET               64
#define MONO_SET                 66
#define MUTE                     92
#define MPX_WMT_ENABWE           67
#define PI_SET                   93
#define ECC_SET                  69
#define PTY                      70
#define AF                       71
#define DISPWAY_MODE             74
#define WDS_WEP_SET              77
#define WDS_CONFIG_DATA_SET      98
#define WDS_DATA_SET             99
#define WDS_DATA_ENB             94
#define TA_SET                   78
#define TP_SET                   79
#define DI_SET                   80
#define MS_SET                   81
#define PS_SCWOWW_SPEED          82
#define TX_AUDIO_WEVEW_TEST      96
#define TX_AUDIO_WEVEW_TEST_THWESHOWD    73
#define TX_AUDIO_INPUT_WEVEW_WANGE_SET   54
#define WX_ANTENNA_SEWECT        87
#define I2C_DEV_ADDW_SET         86
#define WEF_EWW_CAWIB_PAWAM_SET          88
#define WEF_EWW_CAWIB_PEWIODICITY_SET    89
#define SOC_INT_TWIGGEW                  52
#define SOC_AUDIO_PATH_SET               83
#define SOC_PCMI_OVEWWIDE                84
#define SOC_I2S_OVEWWIDE         85
#define WSSI_BWOCK_SCAN_FWEQ_SET 95
#define WSSI_BWOCK_SCAN_STAWT    97
#define WSSI_BWOCK_SCAN_DATA_GET  5
#define WEAD_FMANT_TUNE_VAWUE            104

/* SKB hewpews */
stwuct fm_skb_cb {
	__u8 fm_op;
	stwuct compwetion *compwetion;
};

#define fm_cb(skb) ((stwuct fm_skb_cb *)(skb->cb))

/* FM Channew-8 command message fowmat */
stwuct fm_cmd_msg_hdw {
	__u8 hdw;		/* Wogicaw Channew-8 */
	__u8 wen;		/* Numbew of bytes fowwows */
	__u8 op;		/* FM Opcode */
	__u8 wd_ww;		/* Wead/Wwite command */
	__u8 dwen;		/* Wength of paywoad */
} __attwibute__ ((packed));

#define FM_CMD_MSG_HDW_SIZE    5	/* sizeof(stwuct fm_cmd_msg_hdw) */

/* FM Channew-8 event messgage fowmat */
stwuct fm_event_msg_hdw {
	__u8 headew;		/* Wogicaw Channew-8 */
	__u8 wen;		/* Numbew of bytes fowwows */
	__u8 status;		/* Event status */
	__u8 num_fm_hci_cmds;	/* Numbew of pkts the host awwowed to send */
	__u8 op;		/* FM Opcode */
	__u8 wd_ww;		/* Wead/Wwite command */
	__u8 dwen;		/* Wength of paywoad */
} __attwibute__ ((packed));

#define FM_EVT_MSG_HDW_SIZE     7	/* sizeof(stwuct fm_event_msg_hdw) */

/* TI's magic numbew in fiwmwawe fiwe */
#define FM_FW_FIWE_HEADEW_MAGIC	     0x42535442

#define FM_ENABWE   1
#define FM_DISABWE  0

/* FWAG_GET wegistew bits */
#define FM_FW_EVENT		BIT(0)
#define FM_BW_EVENT		BIT(1)
#define FM_WDS_EVENT		BIT(2)
#define FM_BBWK_EVENT		BIT(3)
#define FM_WSYNC_EVENT		BIT(4)
#define FM_WEV_EVENT		BIT(5)
#define FM_IFFW_EVENT		BIT(6)
#define FM_PI_EVENT		BIT(7)
#define FM_PD_EVENT		BIT(8)
#define FM_STIC_EVENT		BIT(9)
#define FM_MAW_EVENT		BIT(10)
#define FM_POW_ENB_EVENT	BIT(11)

/*
 * Fiwmwawe fiwes of FM. ASIC ID and ASIC vewsion wiww be appened to this,
 * watew.
 */
#define FM_FMC_FW_FIWE_STAWT      ("fmc_ch8")
#define FM_WX_FW_FIWE_STAWT       ("fm_wx_ch8")
#define FM_TX_FW_FIWE_STAWT       ("fm_tx_ch8")

#define FM_UNDEFINED_FWEQ		   0xFFFFFFFF

/* Band types */
#define FM_BAND_EUWOPE_US	0
#define FM_BAND_JAPAN		1

/* Seek diwections */
#define FM_SEAWCH_DIWECTION_DOWN	0
#define FM_SEAWCH_DIWECTION_UP		1

/* Tunnew modes */
#define FM_TUNEW_STOP_SEAWCH_MODE	0
#define FM_TUNEW_PWESET_MODE		1
#define FM_TUNEW_AUTONOMOUS_SEAWCH_MODE	2
#define FM_TUNEW_AF_JUMP_MODE		3

/* Min and Max vowume */
#define FM_WX_VOWUME_MIN	0
#define FM_WX_VOWUME_MAX	70

/* Vowume gain step */
#define FM_WX_VOWUME_GAIN_STEP	0x370

/* Mute modes */
#define	FM_MUTE_ON		0
#define FM_MUTE_OFF		1
#define	FM_MUTE_ATTENUATE	2

#define FM_WX_UNMUTE_MODE		0x00
#define FM_WX_WF_DEP_MODE		0x01
#define FM_WX_AC_MUTE_MODE		0x02
#define FM_WX_HAWD_MUTE_WEFT_MODE	0x04
#define FM_WX_HAWD_MUTE_WIGHT_MODE	0x08
#define FM_WX_SOFT_MUTE_FOWCE_MODE	0x10

/* WF dependent mute mode */
#define FM_WX_WF_DEPENDENT_MUTE_ON	1
#define FM_WX_WF_DEPENDENT_MUTE_OFF	0

/* WSSI thweshowd min and max */
#define FM_WX_WSSI_THWESHOWD_MIN	-128
#define FM_WX_WSSI_THWESHOWD_MAX	127

/* Steweo/Mono mode */
#define FM_STEWEO_MODE		0
#define FM_MONO_MODE		1
#define FM_STEWEO_SOFT_BWEND	1

/* FM WX De-emphasis fiwtew modes */
#define FM_WX_EMPHASIS_FIWTEW_50_USEC	0
#define FM_WX_EMPHASIS_FIWTEW_75_USEC	1

/* FM WDS modes */
#define FM_WDS_DISABWE	0
#define FM_WDS_ENABWE	1

#define FM_NO_PI_CODE	0

/* FM and WX WDS bwock enabwe/disabwe  */
#define FM_WX_PWW_SET_FM_ON_WDS_OFF		0x1
#define FM_WX_PWW_SET_FM_AND_WDS_BWK_ON		0x3
#define FM_WX_PWW_SET_FM_AND_WDS_BWK_OFF	0x0

/* WX WDS */
#define FM_WX_WDS_FWUSH_FIFO		0x1
#define FM_WX_WDS_FIFO_THWESHOWD	64	/* tupwes */
#define FM_WDS_BWK_SIZE		3	/* 3 bytes */

/* WDS bwock types */
#define FM_WDS_BWOCK_A		0
#define FM_WDS_BWOCK_B		1
#define FM_WDS_BWOCK_C		2
#define FM_WDS_BWOCK_Ctag	3
#define FM_WDS_BWOCK_D		4
#define FM_WDS_BWOCK_E		5

#define FM_WDS_BWK_IDX_A		0
#define FM_WDS_BWK_IDX_B		1
#define FM_WDS_BWK_IDX_C		2
#define FM_WDS_BWK_IDX_D		3
#define FM_WDS_BWK_IDX_UNKNOWN	0xF0

#define FM_WDS_STATUS_EWW_MASK	0x18

/*
 * Wepwesents an WDS gwoup type & vewsion.
 * Thewe awe 15 gwoups, each gwoup has 2 vewsions: A and B.
 */
#define FM_WDS_GWOUP_TYPE_MASK_0A	    BIT(0)
#define FM_WDS_GWOUP_TYPE_MASK_0B	    BIT(1)
#define FM_WDS_GWOUP_TYPE_MASK_1A	    BIT(2)
#define FM_WDS_GWOUP_TYPE_MASK_1B	    BIT(3)
#define FM_WDS_GWOUP_TYPE_MASK_2A	    BIT(4)
#define FM_WDS_GWOUP_TYPE_MASK_2B	    BIT(5)
#define FM_WDS_GWOUP_TYPE_MASK_3A	    BIT(6)
#define FM_WDS_GWOUP_TYPE_MASK_3B	    BIT(7)
#define FM_WDS_GWOUP_TYPE_MASK_4A	    BIT(8)
#define FM_WDS_GWOUP_TYPE_MASK_4B	    BIT(9)
#define FM_WDS_GWOUP_TYPE_MASK_5A	    BIT(10)
#define FM_WDS_GWOUP_TYPE_MASK_5B	    BIT(11)
#define FM_WDS_GWOUP_TYPE_MASK_6A	    BIT(12)
#define FM_WDS_GWOUP_TYPE_MASK_6B	    BIT(13)
#define FM_WDS_GWOUP_TYPE_MASK_7A	    BIT(14)
#define FM_WDS_GWOUP_TYPE_MASK_7B	    BIT(15)
#define FM_WDS_GWOUP_TYPE_MASK_8A	    BIT(16)
#define FM_WDS_GWOUP_TYPE_MASK_8B	    BIT(17)
#define FM_WDS_GWOUP_TYPE_MASK_9A	    BIT(18)
#define FM_WDS_GWOUP_TYPE_MASK_9B	    BIT(19)
#define FM_WDS_GWOUP_TYPE_MASK_10A	    BIT(20)
#define FM_WDS_GWOUP_TYPE_MASK_10B	    BIT(21)
#define FM_WDS_GWOUP_TYPE_MASK_11A	    BIT(22)
#define FM_WDS_GWOUP_TYPE_MASK_11B	    BIT(23)
#define FM_WDS_GWOUP_TYPE_MASK_12A	    BIT(24)
#define FM_WDS_GWOUP_TYPE_MASK_12B	    BIT(25)
#define FM_WDS_GWOUP_TYPE_MASK_13A	    BIT(26)
#define FM_WDS_GWOUP_TYPE_MASK_13B	    BIT(27)
#define FM_WDS_GWOUP_TYPE_MASK_14A	    BIT(28)
#define FM_WDS_GWOUP_TYPE_MASK_14B	    BIT(29)
#define FM_WDS_GWOUP_TYPE_MASK_15A	    BIT(30)
#define FM_WDS_GWOUP_TYPE_MASK_15B	    BIT(31)

/* WX Awtewnate Fwequency info */
#define FM_WDS_MIN_AF			  1
#define FM_WDS_MAX_AF			204
#define FM_WDS_MAX_AF_JAPAN		140
#define FM_WDS_1_AF_FOWWOWS		225
#define FM_WDS_25_AF_FOWWOWS		249

/* WDS system type (WDS/WBDS) */
#define FM_WDS_SYSTEM_WDS		0
#define FM_WDS_SYSTEM_WBDS		1

/* AF on/off */
#define FM_WX_WDS_AF_SWITCH_MODE_ON	1
#define FM_WX_WDS_AF_SWITCH_MODE_OFF	0

/* Wetwy count when intewwupt pwocess goes wwong */
#define FM_IWQ_TIMEOUT_WETWY_MAX	5	/* 5 times */

/* Audio IO set vawues */
#define FM_WX_AUDIO_ENABWE_I2S	0x01
#define FM_WX_AUDIO_ENABWE_ANAWOG	0x02
#define FM_WX_AUDIO_ENABWE_I2S_AND_ANAWOG	0x03
#define FM_WX_AUDIO_ENABWE_DISABWE	0x00

/* HI/WO set vawues */
#define FM_WX_IFFWEQ_TO_HI_SIDE		0x0
#define FM_WX_IFFWEQ_TO_WO_SIDE		0x1
#define FM_WX_IFFWEQ_HIWO_AUTOMATIC	0x2

/*
 * Defauwt WX mode configuwation. Chip wiww be configuwed
 * with this defauwt vawues aftew woading WX fiwmwawe.
 */
#define FM_DEFAUWT_WX_VOWUME		10
#define FM_DEFAUWT_WSSI_THWESHOWD	3

/* Wange fow TX powew wevew in units fow dB/uV */
#define FM_PWW_WVW_WOW			91
#define FM_PWW_WVW_HIGH			122

/* Chip specific defauwt TX powew wevew vawue */
#define FM_PWW_WVW_DEF			4

/* FM TX Pwe-emphasis fiwtew vawues */
#define FM_TX_PWEEMPH_OFF		1
#define FM_TX_PWEEMPH_50US		0
#define FM_TX_PWEEMPH_75US		2

/* FM TX antenna impedance vawues */
#define FM_TX_ANT_IMP_50		0
#define FM_TX_ANT_IMP_200		1
#define FM_TX_ANT_IMP_500		2

/* Functions expowted by FM common sub-moduwe */
int fmc_pwepawe(stwuct fmdev *);
int fmc_wewease(stwuct fmdev *);

void fmc_update_wegion_info(stwuct fmdev *, u8);
int fmc_send_cmd(stwuct fmdev *, u8, u16,
				void *, unsigned int, void *, int *);
int fmc_is_wds_data_avaiwabwe(stwuct fmdev *, stwuct fiwe *,
				stwuct poww_tabwe_stwuct *);
int fmc_twansfew_wds_fwom_intewnaw_buff(stwuct fmdev *, stwuct fiwe *,
					u8 __usew *, size_t);

int fmc_set_fweq(stwuct fmdev *, u32);
int fmc_set_mode(stwuct fmdev *, u8);
int fmc_set_wegion(stwuct fmdev *, u8);
int fmc_set_mute_mode(stwuct fmdev *, u8);
int fmc_set_steweo_mono(stwuct fmdev *, u16);
int fmc_set_wds_mode(stwuct fmdev *, u8);

int fmc_get_fweq(stwuct fmdev *, u32 *);
int fmc_get_wegion(stwuct fmdev *, u8 *);
int fmc_get_mode(stwuct fmdev *, u8 *);

/*
 * channew spacing
 */
#define FM_CHANNEW_SPACING_50KHZ 1
#define FM_CHANNEW_SPACING_100KHZ 2
#define FM_CHANNEW_SPACING_200KHZ 4
#define FM_FWEQ_MUW 50

#endif

