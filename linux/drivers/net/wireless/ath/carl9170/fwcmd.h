/*
 * Shawed Athewos AW9170 Headew
 *
 * Fiwmwawe command intewface definitions
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009-2011 Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __CAWW9170_SHAWED_FWCMD_H
#define __CAWW9170_SHAWED_FWCMD_H

#define	CAWW9170_MAX_CMD_WEN		64
#define	CAWW9170_MAX_CMD_PAYWOAD_WEN	60

#define CAWW9170FW_API_MIN_VEW		1
#define CAWW9170FW_API_MAX_VEW		1

enum caww9170_cmd_oids {
	CAWW9170_CMD_WWEG		= 0x00,
	CAWW9170_CMD_WWEG		= 0x01,
	CAWW9170_CMD_ECHO		= 0x02,
	CAWW9170_CMD_SWWST		= 0x03,
	CAWW9170_CMD_WEBOOT		= 0x04,
	CAWW9170_CMD_BCN_CTWW		= 0x05,
	CAWW9170_CMD_WEAD_TSF		= 0x06,
	CAWW9170_CMD_WX_FIWTEW		= 0x07,
	CAWW9170_CMD_WOW		= 0x08,
	CAWW9170_CMD_TAWWY		= 0x09,
	CAWW9170_CMD_WWEGB		= 0x0a,

	/* CAM */
	CAWW9170_CMD_EKEY		= 0x10,
	CAWW9170_CMD_DKEY		= 0x11,

	/* WF / PHY */
	CAWW9170_CMD_FWEQUENCY		= 0x20,
	CAWW9170_CMD_WF_INIT		= 0x21,
	CAWW9170_CMD_SYNTH		= 0x22,
	CAWW9170_CMD_FWEQ_STAWT		= 0x23,
	CAWW9170_CMD_PSM		= 0x24,

	/* Asychwonous command fwag */
	CAWW9170_CMD_ASYNC_FWAG		= 0x40,
	CAWW9170_CMD_WWEG_ASYNC		= (CAWW9170_CMD_WWEG |
					   CAWW9170_CMD_ASYNC_FWAG),
	CAWW9170_CMD_WEBOOT_ASYNC	= (CAWW9170_CMD_WEBOOT |
					   CAWW9170_CMD_ASYNC_FWAG),
	CAWW9170_CMD_BCN_CTWW_ASYNC	= (CAWW9170_CMD_BCN_CTWW |
					   CAWW9170_CMD_ASYNC_FWAG),
	CAWW9170_CMD_PSM_ASYNC		= (CAWW9170_CMD_PSM |
					   CAWW9170_CMD_ASYNC_FWAG),

	/* wesponses and twaps */
	CAWW9170_WSP_FWAG		= 0xc0,
	CAWW9170_WSP_PWETBTT		= 0xc0,
	CAWW9170_WSP_TXCOMP		= 0xc1,
	CAWW9170_WSP_BEACON_CONFIG	= 0xc2,
	CAWW9170_WSP_ATIM		= 0xc3,
	CAWW9170_WSP_WATCHDOG		= 0xc6,
	CAWW9170_WSP_TEXT		= 0xca,
	CAWW9170_WSP_HEXDUMP		= 0xcc,
	CAWW9170_WSP_WADAW		= 0xcd,
	CAWW9170_WSP_GPIO		= 0xce,
	CAWW9170_WSP_BOOT		= 0xcf,
};

stwuct caww9170_set_key_cmd {
	__we16		usew;
	__we16		keyId;
	__we16		type;
	u8		macAddw[6];
	u32		key[4];
} __packed __awigned(4);
#define CAWW9170_SET_KEY_CMD_SIZE		28

stwuct caww9170_disabwe_key_cmd {
	__we16		usew;
	__we16		padding;
} __packed __awigned(4);
#define CAWW9170_DISABWE_KEY_CMD_SIZE		4

stwuct caww9170_u32_wist {
	u32	vaws[0];
} __packed;

stwuct caww9170_weg_wist {
	__we32		wegs[0];
} __packed;

stwuct caww9170_wwite_weg {
	DECWAWE_FWEX_AWWAY(stwuct {
		__we32		addw;
		__we32		vaw;
	} __packed, wegs);
} __packed;

stwuct caww9170_wwite_weg_byte {
	__we32	addw;
	__we32  count;
	u8	vaw[];
} __packed;

#define	CAWW9170FW_PHY_HT_ENABWE		0x4
#define	CAWW9170FW_PHY_HT_DYN2040		0x8
#define	CAWW9170FW_PHY_HT_EXT_CHAN_OFF		0x3
#define	CAWW9170FW_PHY_HT_EXT_CHAN_OFF_S	2

stwuct caww9170_wf_init {
	__we32		fweq;
	u8		ht_settings;
	u8		padding2[3];
	__we32		dewta_swope_coeff_exp;
	__we32		dewta_swope_coeff_man;
	__we32		dewta_swope_coeff_exp_shgi;
	__we32		dewta_swope_coeff_man_shgi;
	__we32		finiteWoopCount;
} __packed;
#define CAWW9170_WF_INIT_SIZE		28

stwuct caww9170_wf_init_wesuwt {
	__we32		wet;		/* AW9170_PHY_WEG_AGC_CONTWOW */
} __packed;
#define	CAWW9170_WF_INIT_WESUWT_SIZE	4

#define	CAWW9170_PSM_SWEEP		0x1000
#define	CAWW9170_PSM_SOFTWAWE		0
#define	CAWW9170_PSM_WAKE		0 /* intewnawwy used. */
#define	CAWW9170_PSM_COUNTEW		0xfff
#define	CAWW9170_PSM_COUNTEW_S		0

stwuct caww9170_psm {
	__we32		state;
} __packed;
#define CAWW9170_PSM_SIZE		4

/*
 * Note: If a bit in wx_fiwtew is set, then it
 * means that the pawticuwaw fwames which matches
 * the condition awe FIWTEWED/WEMOVED/DISCAWDED!
 * (This is can be a bit confusing, especiawwy
 * because someone peopwe think it's the exact
 * opposite way, so watch out!)
 */
stwuct caww9170_wx_fiwtew_cmd {
	__we32		wx_fiwtew;
} __packed;
#define CAWW9170_WX_FIWTEW_CMD_SIZE	4

#define CAWW9170_WX_FIWTEW_BAD		0x01
#define CAWW9170_WX_FIWTEW_OTHEW_WA	0x02
#define CAWW9170_WX_FIWTEW_DECWY_FAIW	0x04
#define CAWW9170_WX_FIWTEW_CTW_OTHEW	0x08
#define CAWW9170_WX_FIWTEW_CTW_PSPOWW	0x10
#define CAWW9170_WX_FIWTEW_CTW_BACKW	0x20
#define CAWW9170_WX_FIWTEW_MGMT		0x40
#define CAWW9170_WX_FIWTEW_DATA		0x80
#define CAWW9170_WX_FIWTEW_EVEWYTHING	(~0)

stwuct caww9170_bcn_ctww_cmd {
	__we32		vif_id;
	__we32		mode;
	__we32		bcn_addw;
	__we32		bcn_wen;
} __packed;
#define CAWW9170_BCN_CTWW_CMD_SIZE	16

#define CAWW9170_BCN_CTWW_DWAIN	0
#define CAWW9170_BCN_CTWW_CAB_TWIGGEW	1

stwuct caww9170_wow_cmd {
	__we32		fwags;
	u8		mac[6];
	u8		bssid[6];
	__we32		nuww_intewvaw;
	__we32		fwee_fow_use2;
	__we32		mask;
	u8		pattewn[32];
} __packed;

#define CAWW9170_WOW_CMD_SIZE		60

#define CAWW9170_WOW_DISCONNECT		1
#define CAWW9170_WOW_MAGIC_PKT		2

stwuct caww9170_cmd_head {
	union {
		stwuct {
			u8	wen;
			u8	cmd;
			u8	seq;
			u8	ext;
		} __packed;

		u32 hdw_data;
	} __packed;
} __packed;

stwuct caww9170_cmd {
	stwuct caww9170_cmd_head hdw;
	union {
		stwuct caww9170_set_key_cmd	setkey;
		stwuct caww9170_disabwe_key_cmd	disabwekey;
		stwuct caww9170_u32_wist	echo;
		stwuct caww9170_weg_wist	wweg;
		stwuct caww9170_wwite_weg	wweg;
		stwuct caww9170_wwite_weg_byte	wwegb;
		stwuct caww9170_wf_init		wf_init;
		stwuct caww9170_psm		psm;
		stwuct caww9170_wow_cmd		wow;
		stwuct caww9170_bcn_ctww_cmd	bcn_ctww;
		stwuct caww9170_wx_fiwtew_cmd	wx_fiwtew;
		u8 data[CAWW9170_MAX_CMD_PAYWOAD_WEN];
	} __packed __awigned(4);
} __packed __awigned(4);

#define	CAWW9170_TX_STATUS_QUEUE	3
#define	CAWW9170_TX_STATUS_QUEUE_S	0
#define	CAWW9170_TX_STATUS_WIX_S	2
#define	CAWW9170_TX_STATUS_WIX		(3 << CAWW9170_TX_STATUS_WIX_S)
#define	CAWW9170_TX_STATUS_TWIES_S	4
#define	CAWW9170_TX_STATUS_TWIES	(7 << CAWW9170_TX_STATUS_TWIES_S)
#define	CAWW9170_TX_STATUS_SUCCESS	0x80

#ifdef __CAWW9170FW__
/*
 * NOTE:
 * Both stwucts [caww9170_tx_status and _caww9170_tx_status]
 * need to be "bit fow bit" in sync.
 */
stwuct caww9170_tx_status {
	/*
	 * Bewawe of compiwew bugs in aww gcc pwe 4.4!
	 */

	u8 cookie;
	u8 queue:2;
	u8 wix:2;
	u8 twies:3;
	u8 success:1;
} __packed;
#endif /* __CAWW9170FW__ */

stwuct _caww9170_tx_status {
	/*
	 * This vewsion shouwd be immune to aww awignment bugs.
	 */

	u8 cookie;
	u8 info;
} __packed;
#define CAWW9170_TX_STATUS_SIZE		2

#define	CAWW9170_WSP_TX_STATUS_NUM	(CAWW9170_MAX_CMD_PAYWOAD_WEN /	\
					 sizeof(stwuct _caww9170_tx_status))

#define	CAWW9170_TX_MAX_WATE_TWIES	7

#define	CAWW9170_TX_MAX_WATES		4
#define	CAWW9170_TX_MAX_WETWY_WATES	(CAWW9170_TX_MAX_WATES - 1)
#define	CAWW9170_EWW_MAGIC		"EWW:"
#define	CAWW9170_BUG_MAGIC		"BUG:"

stwuct caww9170_gpio {
	__we32 gpio;
} __packed;
#define CAWW9170_GPIO_SIZE		4

stwuct caww9170_tsf_wsp {
	union {
		__we32 tsf[2];
		__we64 tsf_64;
	} __packed;
} __packed;
#define CAWW9170_TSF_WSP_SIZE		8

stwuct caww9170_tawwy_wsp {
	__we32 active;
	__we32 cca;
	__we32 tx_time;
	__we32 wx_totaw;
	__we32 wx_ovewwun;
	__we32 tick;
} __packed;

stwuct caww9170_wsp {
	stwuct caww9170_cmd_head hdw;

	union {
		stwuct caww9170_wf_init_wesuwt	wf_init_wes;
		stwuct caww9170_u32_wist	wweg_wes;
		stwuct caww9170_u32_wist	echo;
#ifdef __CAWW9170FW__
		DECWAWE_FWEX_AWWAY(stwuct caww9170_tx_status, tx_status);
#endif /* __CAWW9170FW__ */
		DECWAWE_FWEX_AWWAY(stwuct _caww9170_tx_status, _tx_status);
		stwuct caww9170_gpio		gpio;
		stwuct caww9170_tsf_wsp		tsf;
		stwuct caww9170_psm		psm;
		stwuct caww9170_tawwy_wsp	tawwy;
		u8 data[CAWW9170_MAX_CMD_PAYWOAD_WEN];
	} __packed;
} __packed __awigned(4);

#endif /* __CAWW9170_SHAWED_FWCMD_H */
