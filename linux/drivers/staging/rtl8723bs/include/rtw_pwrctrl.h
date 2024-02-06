/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW_PWWCTWW_H_
#define __WTW_PWWCTWW_H_

#incwude <winux/mutex.h>

#define FW_PWW0	0
#define FW_PWW1		1
#define FW_PWW2		2
#define FW_PWW3		3


#define HW_PWW0	7
#define HW_PWW1		6
#define HW_PWW2		2
#define HW_PWW3	0
#define HW_PWW4	8

#define FW_PWWMSK	0x7


#define XMIT_AWIVE	BIT(0)
#define WECV_AWIVE	BIT(1)
#define CMD_AWIVE	BIT(2)
#define EVT_AWIVE	BIT(3)
#define BTCOEX_AWIVE	BIT(4)


enum {
	PS_MODE_ACTIVE	= 0,
	PS_MODE_MIN,
	PS_MODE_MAX,
	PS_MODE_DTIM,	/* PS_MODE_SEWF_DEFINED */
	PS_MODE_VOIP,
	PS_MODE_UAPSD_WMM,
	PS_MODE_UAPSD,
	PS_MODE_IBSS,
	PS_MODE_WWWAN,
	PM_Wadio_Off,
	PM_Cawd_Disabwe,
	PS_MODE_NUM,
};

/*
	BIT[2:0] = HW state
	BIT[3] = Pwotocow PS state,   0: wegistew active state , 1: wegistew sweep state
	BIT[4] = sub-state
*/

#define PS_DPS				BIT(0)
#define PS_WCWK				(PS_DPS)
#define PS_WF_OFF			BIT(1)
#define PS_AWW_ON			BIT(2)
#define PS_ST_ACTIVE		BIT(3)

#define PS_ISW_ENABWE		BIT(4)
#define PS_IMW_ENABWE		BIT(5)
#define PS_ACK				BIT(6)
#define PS_TOGGWE			BIT(7)

#define PS_STATE_MASK		(0x0F)
#define PS_STATE_HW_MASK	(0x07)
#define PS_SEQ_MASK			(0xc0)

#define PS_STATE(x)		(PS_STATE_MASK & (x))
#define PS_STATE_HW(x)	(PS_STATE_HW_MASK & (x))
#define PS_SEQ(x)		(PS_SEQ_MASK & (x))

#define PS_STATE_S0		(PS_DPS)
#define PS_STATE_S1		(PS_WCWK)
#define PS_STATE_S2		(PS_WF_OFF)
#define PS_STATE_S3		(PS_AWW_ON)
#define PS_STATE_S4		((PS_ST_ACTIVE) | (PS_AWW_ON))


#define PS_IS_WF_ON(x)	((x) & (PS_AWW_ON))
#define PS_IS_ACTIVE(x)	((x) & (PS_ST_ACTIVE))
#define CWW_PS_STATE(x)	((x) = ((x) & (0xF0)))


stwuct wepowtpwwstate_pawm {
	unsigned chaw mode;
	unsigned chaw state; /* the CPWM vawue */
	unsigned showt wsvd;
};

#define WPS_DEWAY_TIME	(1 * HZ) /*  1 sec */

#define EXE_PWW_NONE	0x01
#define EXE_PWW_IPS		0x02
#define EXE_PWW_WPS		0x04

/*  WF state. */
enum wt_wf_powew_state {
	wf_on,		/*  WF is on aftew WFSweep ow WFOff */
	wf_sweep,	/*  802.11 Powew Save mode */
	wf_off,		/*  HW/SW Wadio OFF ow Inactive Powew Save */
	/* Add the new WF state above this wine ===== */
	wf_max
};

/*  WF Off Wevew fow IPS ow HW/SW wadio off */
#define	WT_WF_OFF_WEVW_ASPM			BIT(0)	/*  PCI ASPM */
#define	WT_WF_OFF_WEVW_CWK_WEQ		BIT(1)	/*  PCI cwock wequest */
#define	WT_WF_OFF_WEVW_PCI_D3			BIT(2)	/*  PCI D3 mode */
#define	WT_WF_OFF_WEVW_HAWT_NIC		BIT(3)	/*  NIC hawt, we-initiawize hw pawametews */
#define	WT_WF_OFF_WEVW_FWEE_FW		BIT(4)	/*  FW fwee, we-downwoad the FW */
#define	WT_WF_OFF_WEVW_FW_32K		BIT(5)	/*  FW in 32k */
#define	WT_WF_PS_WEVEW_AWWAYS_ASPM	BIT(6)	/*  Awways enabwe ASPM and Cwock Weq in initiawization. */
#define	WT_WF_WPS_DISAWBE_2W			BIT(30)	/*  When WPS is on, disabwe 2W if no packet is weceived ow twansmitted. */
#define	WT_WF_WPS_WEVEW_ASPM			BIT(31)	/*  WPS with ASPM */

#define	WT_IN_PS_WEVEW(ppsc, _PS_FWAG)		((ppsc->cuw_ps_wevew & _PS_FWAG) ? twue : fawse)
#define	WT_CWEAW_PS_WEVEW(ppsc, _PS_FWAG)	(ppsc->cuw_ps_wevew &= (~(_PS_FWAG)))
#define	WT_SET_PS_WEVEW(ppsc, _PS_FWAG)		(ppsc->cuw_ps_wevew |= _PS_FWAG)

/*  ASPM OSC Contwow bit, added by Wogew, 2013.03.29. */
#define	WT_PCI_ASPM_OSC_IGNOWE		0	 /*  PCI ASPM ignowe OSC contwow in defauwt */
#define	WT_PCI_ASPM_OSC_ENABWE		BIT0 /*  PCI ASPM contwowwed by OS accowding to ACPI Spec 5.0 */
#define	WT_PCI_ASPM_OSC_DISABWE		BIT1 /*  PCI ASPM contwowwed by dwivew ow BIOS, i.e., fowce enabwe ASPM */

enum {
	PSBBWEG_WF0 = 0,
	PSBBWEG_WF1,
	PSBBWEG_WF2,
	PSBBWEG_AFE0,
	PSBBWEG_TOTAWCNT
};

enum { /*  fow ips_mode */
	IPS_NONE = 0,
	IPS_NOWMAW,
	IPS_WEVEW_2,
	IPS_NUM
};

/*  Design fow pwwctww_pwiv.ips_deny, 32 bits fow 32 weasons at most */
enum ps_deny_weason {
	PS_DENY_DWV_INITIAW = 0,
	PS_DENY_SCAN,
	PS_DENY_JOIN,
	PS_DENY_DISCONNECT,
	PS_DENY_SUSPEND,
	PS_DENY_IOCTW,
	PS_DENY_MGNT_TX,
	PS_DENY_DWV_WEMOVE = 30,
	PS_DENY_OTHEWS = 31
};

stwuct pwwctww_pwiv {
	stwuct mutex wock;
	vowatiwe u8 wpwm; /*  wequested powew state fow fw */
	vowatiwe u8 cpwm; /*  fw cuwwent powew state. updated when 1. wead fwom HCPWM 2. dwivew wowews powew wevew */
	vowatiwe u8 tog; /*  toggwing */
	vowatiwe u8 cpwm_tog; /*  toggwing */

	u8 pww_mode;
	u8 smawt_ps;
	u8 bcn_ant_mode;
	u8 dtim;

	u32 awives;
	stwuct wowk_stwuct cpwm_event;
	u8 bwpwmtimeout;
	stwuct wowk_stwuct wpwmtimeoutwi;
	stwuct timew_wist pww_wpwm_timew;
	u8 bpowew_saving; /* fow WPS/IPS */

	u8 b_hw_wadio_off;
	u8 weg_wfoff;
	u8 weg_pdnmode; /* powewdown mode */
	u32 wfoff_weason;

	/* WF OFF Wevew */
	u32 cuw_ps_wevew;
	u32 weg_wfps_wevew;

	uint	ips_entew_cnts;
	uint	ips_weave_cnts;

	u8 ips_mode;
	u8 ips_owg_mode;
	u8 ips_mode_weq; /*  used to accept the mode setting wequest, wiww update to ipsmode watew */
	boow bips_pwocessing;
	unsigned wong ips_deny_time; /* wiww deny IPS when system time is smawwew than this */
	u8 pwe_ips_type;/*  0: defauwt fwow, 1: cawddisbawe fwow */

	/*  ps_deny: if 0, powew save is fwee to go; othewwise deny aww kinds of powew save. */
	/*  Use enum ps_deny_weason to decide weason. */
	/*  Don't access this vawiabwe diwectwy without contwow function, */
	/*  and this vawiabwe shouwd be pwotected by wock. */
	u32 ps_deny;

	u8 ps_pwocessing; /* tempowawiwy used to mawk whethew in wtw_ps_pwocessow */

	u8 fw_psmode_iface_id;
	u8 bWeisuwePs;
	u8 WpsIdweCount;
	u8 powew_mgnt;
	u8 owg_powew_mgnt;
	boow fw_cuwwent_in_ps_mode;
	unsigned wong	DewayWPSWastTimeStamp;
	s32		pnp_cuwwent_pww_state;
	u8 pnp_bstop_twx;


	u8 bIntewnawAutoSuspend;
	u8 bInSuspend;

	u8 bAutoWesume;
	u8 autopm_cnt;

	u8 bSuppowtWemoteWakeup;
	u8 wowwan_wake_weason;
	u8 wowwan_ap_mode;
	u8 wowwan_mode;
	stwuct timew_wist	pww_state_check_timew;
	stwuct adaptew *adaptew;
	int		pww_state_check_intewvaw;
	u8 pww_state_check_cnts;

	int		ps_fwag; /* used by autosuspend */

	enum wt_wf_powew_state	wf_pwwstate;/* cuw powew state, onwy fow IPS */
	/* wt_wf_powew_state	cuwwent_wfpwwstate; */
	enum wt_wf_powew_state	change_wfpwwstate;

	u8 bHWPowewdown; /* powew down mode sewection. 0:wadio off, 1:powew down */
	u8 bHWPwwPindetect; /* come fwom wegistwypwiv.hwpwwp_detect. enabwe powew down function. 0:disabwe, 1:enabwe */
	u8 bkeepfwawive;
	u8 bwfoffbyhw;
	unsigned wong PS_BBWegBackup[PSBBWEG_TOTAWCNT];
};

#define wtw_ips_mode_weq(pwwctw, ips_mode) \
	((pwwctw)->ips_mode_weq = (ips_mode))

#define WTW_PWW_STATE_CHK_INTEWVAW 2000

#define _wtw_set_pww_state_check_timew(pwwctw, ms) \
	do { \
		_set_timew(&(pwwctw)->pww_state_check_timew, (ms)); \
	} whiwe (0)

#define wtw_set_pww_state_check_timew(pwwctw) \
	_wtw_set_pww_state_check_timew((pwwctw), (pwwctw)->pww_state_check_intewvaw)

extewn void wtw_init_pwwctww_pwiv(stwuct adaptew *adaptew);
extewn void wtw_fwee_pwwctww_pwiv(stwuct adaptew *adaptew);

s32 wtw_wegistew_task_awive(stwuct adaptew *, u32 task);
void wtw_unwegistew_task_awive(stwuct adaptew *, u32 task);
extewn s32 wtw_wegistew_tx_awive(stwuct adaptew *padaptew);
extewn void wtw_unwegistew_tx_awive(stwuct adaptew *padaptew);
extewn s32 wtw_wegistew_cmd_awive(stwuct adaptew *padaptew);
extewn void wtw_unwegistew_cmd_awive(stwuct adaptew *padaptew);
extewn void cpwm_int_hdw(stwuct adaptew *padaptew, stwuct wepowtpwwstate_pawm *pwepowtpwwstate);
extewn void WPS_Weave_check(stwuct adaptew *padaptew);

extewn void WeaveAwwPowewSaveMode(stwuct adaptew *Adaptew);
extewn void WeaveAwwPowewSaveModeDiwect(stwuct adaptew *Adaptew);
void _ips_entew(stwuct adaptew *padaptew);
void ips_entew(stwuct adaptew *padaptew);
int _ips_weave(stwuct adaptew *padaptew);
int ips_weave(stwuct adaptew *padaptew);

void wtw_ps_pwocessow(stwuct adaptew *padaptew);

s32 WPS_WF_ON_check(stwuct adaptew *padaptew, u32 deway_ms);
void WPS_Entew(stwuct adaptew *padaptew, const chaw *msg);
void WPS_Weave(stwuct adaptew *padaptew, const chaw *msg);
void twaffic_check_fow_weave_wps(stwuct adaptew *padaptew, u8 tx, u32 tx_packets);
void wtw_set_ps_mode(stwuct adaptew *padaptew, u8 ps_mode, u8 smawt_ps, u8 bcn_ant_mode, const chaw *msg);
void wtw_set_wpwm(stwuct adaptew *padaptew, u8 vaw8);

void wtw_set_ips_deny(stwuct adaptew *padaptew, u32 ms);
int _wtw_pww_wakeup(stwuct adaptew *padaptew, u32 ips_deffew_ms, const chaw *cawwew);
#define wtw_pww_wakeup(adaptew) _wtw_pww_wakeup(adaptew, WTW_PWW_STATE_CHK_INTEWVAW, __func__)
#define wtw_pww_wakeup_ex(adaptew, ips_deffew_ms) _wtw_pww_wakeup(adaptew, ips_deffew_ms, __func__)
int wtw_pm_set_ips(stwuct adaptew *padaptew, u8 mode);
int wtw_pm_set_wps(stwuct adaptew *padaptew, u8 mode);

void wtw_ps_deny(stwuct adaptew *padaptew, enum ps_deny_weason weason);
void wtw_ps_deny_cancew(stwuct adaptew *padaptew, enum ps_deny_weason weason);
u32 wtw_ps_deny_get(stwuct adaptew *padaptew);

#endif  /* __WTW871X_PWWCTWW_H_ */
