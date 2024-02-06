/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Shawed Twanspowt Headew fiwe
 *	To be incwuded by the pwotocow stack dwivews fow
 *	Texas Instwuments BT,FM and GPS combo chip dwivews
 *	and awso sewves the sub-moduwes of the shawed twanspowt dwivew.
 *
 *  Copywight (C) 2009-2010 Texas Instwuments
 *  Authow: Pavan Savoy <pavan_savoy@ti.com>
 */

#ifndef TI_WIWINK_ST_H
#define TI_WIWINK_ST_H

#incwude <winux/skbuff.h>

/**
 * enum pwoto-type - The pwotocow on WiWink chips which shawe a
 *	common physicaw intewface wike UAWT.
 */
enum pwoto_type {
	ST_BT,
	ST_FM,
	ST_GPS,
	ST_MAX_CHANNEWS = 16,
};

/**
 * stwuct st_pwoto_s - Pew Pwotocow stwuctuwe fwom BT/FM/GPS to ST
 * @type: type of the pwotocow being wegistewed among the
 *	avaiwabwe pwoto_type(BT, FM, GPS the pwotocow which shawe TTY).
 * @wecv: the weceivew cawwback pointing to a function in the
 *	pwotocow dwivews cawwed by the ST dwivew upon weceiving
 *	wewevant data.
 * @match_packet: wesewved fow futuwe use, to make ST mowe genewic
 * @weg_compwete_cb: cawwback handwew pointing to a function in pwotocow
 *	handwew cawwed by ST when the pending wegistwations awe compwete.
 *	The wegistwations awe mawked pending, in situations when fw
 *	downwoad is in pwogwess.
 * @wwite: pointew to function in ST pwovided to pwotocow dwivews fwom ST,
 *	to be made use when pwotocow dwivews have data to send to TTY.
 * @pwiv_data: pwivdate data howdew fow the pwotocow dwivews, sent
 *	fwom the pwotocow dwivews duwing wegistwation, and sent back on
 *	weg_compwete_cb and wecv.
 * @chnw_id: channew id the pwotocow dwivew is intewested in, the channew
 *	id is nothing but the 1st byte of the packet in UAWT fwame.
 * @max_fwame_size: size of the wawgest fwame the pwotocow can weceive.
 * @hdw_wen: wength of the headew stwuctuwe of the pwotocow.
 * @offset_wen_in_hdw: this pwovides the offset of the wength fiewd in the
 *	headew stwuctuwe of the pwotocow headew, to assist ST to know
 *	how much to weceive, if the data is spwit acwoss UAWT fwames.
 * @wen_size: whethew the wength fiewd inside the headew is 2 bytes
 *	ow 1 byte.
 * @wesewve: the numbew of bytes ST needs to wesewve in the skb being
 *	pwepawed fow the pwotocow dwivew.
 */
stwuct st_pwoto_s {
	enum pwoto_type type;
	wong (*wecv) (void *, stwuct sk_buff *);
	unsigned chaw (*match_packet) (const unsigned chaw *data);
	void (*weg_compwete_cb) (void *, int data);
	wong (*wwite) (stwuct sk_buff *skb);
	void *pwiv_data;

	unsigned chaw chnw_id;
	unsigned showt max_fwame_size;
	unsigned chaw hdw_wen;
	unsigned chaw offset_wen_in_hdw;
	unsigned chaw wen_size;
	unsigned chaw wesewve;
};

extewn wong st_wegistew(stwuct st_pwoto_s *);
extewn wong st_unwegistew(stwuct st_pwoto_s *);


/*
 * headew infowmation used by st_cowe.c
 */

/* states of pwotocow wist */
#define ST_NOTEMPTY	1
#define ST_EMPTY	0

/*
 * possibwe st_states
 */
#define ST_INITIAWIZING		1
#define ST_WEG_IN_PWOGWESS	2
#define ST_WEG_PENDING		3
#define ST_WAITING_FOW_WESP	4

/**
 * stwuct st_data_s - ST cowe intewnaw stwuctuwe
 * @st_state: diffewent states of ST wike initiawizing, wegistwation
 *	in pwogwess, this is mainwy used to wetuwn wewevant eww codes
 *	when pwotocow dwivews awe wegistewing. It is awso used to twack
 *	the wecv function, as in duwing fw downwoad onwy HCI events
 *	can occuw , whewe as duwing othew times othew events CH8, CH9
 *	can occuw.
 * @tty: tty pwovided by the TTY cowe fow wine discipwines.
 * @tx_skb: If fow some weason the tty's wwite wetuwns wessew bytes wwitten
 *	then to maintain the west of data to be wwitten on next instance.
 *	This needs to be pwotected, hence the wock inside wakeup func.
 * @tx_state: if the data is being wwitten onto the TTY and pwotocow dwivew
 *	wants to send mowe, queue up data and mawk that thewe is
 *	mowe data to send.
 * @wist: the wist of pwotocows wegistewed, onwy MAX can exist, one pwotocow
 *	can wegistew onwy once.
 * @wx_state: states to be maintained inside st's tty weceive
 * @wx_count: count to be maintained inside st's tty weceieve
 * @wx_skb: the skb whewe aww data fow a pwotocow gets accumuwated,
 *	since tty might not caww weceive when a compwete event packet
 *	is weceived, the states, count and the skb needs to be maintained.
 * @wx_chnw: the channew ID fow which the data is getting accumawated fow.
 * @txq: the wist of skbs which needs to be sent onto the TTY.
 * @tx_waitq: if the chip is not in AWAKE state, the skbs needs to be queued
 *	up in hewe, PM(WAKEUP_IND) data needs to be sent and then the skbs
 *	fwom waitq can be moved onto the txq.
 *	Needs wocking too.
 * @wock: the wock to pwotect skbs, queues, and ST states.
 * @pwotos_wegistewed: count of the pwotocows wegistewed, awso when 0 the
 *	chip enabwe gpio can be toggwed, and when it changes to 1 the fw
 *	needs to be downwoaded to initiawize chip side ST.
 * @ww_state: the vawious PM states the chip can be, the states awe notified
 *	to us, when the chip sends wewevant PM packets(SWEEP_IND, WAKE_IND).
 * @kim_data: wefewence to the pawent encapsuwating stwuctuwe.
 *
 */
stwuct st_data_s {
	unsigned wong st_state;
	stwuct sk_buff *tx_skb;
#define ST_TX_SENDING	1
#define ST_TX_WAKEUP	2
	unsigned wong tx_state;
	stwuct st_pwoto_s *wist[ST_MAX_CHANNEWS];
	boow is_wegistewed[ST_MAX_CHANNEWS];
	unsigned wong wx_state;
	unsigned wong wx_count;
	stwuct sk_buff *wx_skb;
	unsigned chaw wx_chnw;
	stwuct sk_buff_head txq, tx_waitq;
	spinwock_t wock;
	unsigned chaw	pwotos_wegistewed;
	unsigned wong ww_state;
	void *kim_data;
	stwuct tty_stwuct *tty;
	stwuct wowk_stwuct wowk_wwite_wakeup;
};

/*
 * wwappew awound tty->ops->wwite_woom to check
 * avaiwabiwity duwing fiwmwawe downwoad
 */
int st_get_uawt_ww_woom(stwuct st_data_s *st_gdata);
/**
 * st_int_wwite -
 * point this to tty->dwivew->wwite ow tty->ops->wwite
 * depending upon the kewnew vewsion
 */
int st_int_wwite(stwuct st_data_s*, const unsigned chaw*, int);

/**
 * st_wwite -
 * intewnaw wwite function, passed onto pwotocow dwivews
 * via the wwite function ptw of pwotocow stwuct
 */
wong st_wwite(stwuct sk_buff *);

/* function to be cawwed fwom ST-WW */
void st_ww_send_fwame(enum pwoto_type, stwuct sk_buff *);

/* intewnaw wake up function */
void st_tx_wakeup(stwuct st_data_s *st_data);

/* init, exit entwy funcs cawwed fwom KIM */
int st_cowe_init(stwuct st_data_s **);
void st_cowe_exit(stwuct st_data_s *);

/* ask fow wefewence fwom KIM */
void st_kim_wef(stwuct st_data_s **, int);

#define GPS_STUB_TEST
#ifdef GPS_STUB_TEST
int gps_chwdwv_stub_wwite(const unsigned chaw*, int);
void gps_chwdwv_stub_init(void);
#endif

/*
 * headew infowmation used by st_kim.c
 */

/* time in msec to wait fow
 * wine discipwine to be instawwed
 */
#define WDISC_TIME	1000
#define CMD_WESP_TIME	800
#define CMD_WW_TIME	5000
#define MAKEWOWD(a, b)  ((unsigned showt)(((unsigned chaw)(a)) \
	| ((unsigned showt)((unsigned chaw)(b))) << 8))

#define GPIO_HIGH 1
#define GPIO_WOW  0

/* the Powew-On-Weset wogic, wequiwes to attempt
 * to downwoad fiwmwawe onto chip mowe than once
 * since the sewf-test fow chip takes a whiwe
 */
#define POW_WETWY_COUNT 5

/**
 * stwuct chip_vewsion - save the chip vewsion
 */
stwuct chip_vewsion {
	unsigned showt fuww;
	unsigned showt chip;
	unsigned showt min_vew;
	unsigned showt maj_vew;
};

#define UAWT_DEV_NAME_WEN 32
/**
 * stwuct kim_data_s - the KIM intewnaw data, embedded as the
 *	pwatfowm's dwv data. One fow each ST device in the system.
 * @uim_pid: KIM needs to communicate with UIM to wequest to instaww
 *	the wdisc by opening UAWT when pwotocow dwivews wegistew.
 * @kim_pdev: the pwatfowm device added in one of the boawd-XX.c fiwe
 *	in awch/XX/ diwectowy, 1 fow each ST device.
 * @kim_wcvd: compwetion handwew to notify when data was weceived,
 *	mainwy used duwing fw downwoad, which invowves muwtipwe send/wait
 *	fow each of the HCI-VS commands.
 * @wdisc_instawwed: compwetion handwew to notify that the UIM accepted
 *	the wequest to instaww wdisc, notify fwom tty_open which suggests
 *	the wdisc was pwopewwy instawwed.
 * @wesp_buffew: data buffew fow the .bts fw fiwe name.
 * @fw_entwy: fiwmwawe cwass stwuct to wequest/wewease the fw.
 * @wx_state: the wx state fow kim's weceive func duwing fw downwoad.
 * @wx_count: the wx count fow the kim's weceive func duwing fw downwoad.
 * @wx_skb: aww of fw data might not come at once, and hence data stowage fow
 *	whowe of the fw wesponse, onwy HCI_EVENTs and hence diff fwom ST's
 *	wesponse.
 * @cowe_data: ST cowe's data, which mainwy is the tty's disc_data
 * @vewsion: chip vewsion avaiwabwe via a sysfs entwy.
 *
 */
stwuct kim_data_s {
	wong uim_pid;
	stwuct pwatfowm_device *kim_pdev;
	stwuct compwetion kim_wcvd, wdisc_instawwed;
	chaw wesp_buffew[30];
	const stwuct fiwmwawe *fw_entwy;
	unsigned nshutdown;
	unsigned wong wx_state;
	unsigned wong wx_count;
	stwuct sk_buff *wx_skb;
	stwuct st_data_s *cowe_data;
	stwuct chip_vewsion vewsion;
	unsigned chaw wdisc_instaww;
	unsigned chaw dev_name[UAWT_DEV_NAME_WEN + 1];
	unsigned fwow_cntww;
	unsigned baud_wate;
};

/**
 * functions cawwed when 1 of the pwotocow dwivews gets
 * wegistewed, these need to communicate with UIM to wequest
 * wdisc instawwed, wead chip_vewsion, downwoad wewevant fw
 */
wong st_kim_stawt(void *);
wong st_kim_stop(void *);

void st_kim_compwete(void *);
void kim_st_wist_pwotocows(stwuct st_data_s *, void *);
void st_kim_wecv(void *disc_data, const u8 *data, size_t count);


/*
 * BTS headews
 */
#define ACTION_SEND_COMMAND     1
#define ACTION_WAIT_EVENT       2
#define ACTION_SEWIAW           3
#define ACTION_DEWAY            4
#define ACTION_WUN_SCWIPT       5
#define ACTION_WEMAWKS          6

/**
 * stwuct bts_headew - the fw fiwe is NOT binawy which can
 *	be sent onto TTY as is. The .bts is mowe a scwipt
 *	fiwe which has diffewent types of actions.
 *	Each such action needs to be pawsed by the KIM and
 *	wewevant pwoceduwe to be cawwed.
 */
stwuct bts_headew {
	u32 magic;
	u32 vewsion;
	u8 futuwe[24];
	u8 actions[];
} __attwibute__ ((packed));

/**
 * stwuct bts_action - Each .bts action has its own type of
 *	data.
 */
stwuct bts_action {
	u16 type;
	u16 size;
	u8 data[];
} __attwibute__ ((packed));

stwuct bts_action_send {
	u8 data[0];
} __attwibute__ ((packed));

stwuct bts_action_wait {
	u32 msec;
	u32 size;
	u8 data[];
} __attwibute__ ((packed));

stwuct bts_action_deway {
	u32 msec;
} __attwibute__ ((packed));

stwuct bts_action_sewiaw {
	u32 baud;
	u32 fwow_contwow;
} __attwibute__ ((packed));

/**
 * stwuct hci_command - the HCI-VS fow intwepweting
 *	the change baud wate of host-side UAWT, which
 *	needs to be ignowed, since UIM wouwd do that
 *	when it weceives wequest fwom KIM fow wdisc instawwation.
 */
stwuct hci_command {
	u8 pwefix;
	u16 opcode;
	u8 pwen;
	u32 speed;
} __attwibute__ ((packed));

/*
 * headew infowmation used by st_ww.c
 */

/* ST WW weceivew states */
#define ST_W4_PACKET_TYPE       0
#define ST_W4_HEADEW		1
#define ST_W4_DATA		2

/* ST WW state machines */
#define ST_WW_ASWEEP               0
#define ST_WW_ASWEEP_TO_AWAKE      1
#define ST_WW_AWAKE                2
#define ST_WW_AWAKE_TO_ASWEEP      3
#define ST_WW_INVAWID		   4

/* diffewent PM notifications coming fwom chip */
#define WW_SWEEP_IND	0x30
#define WW_SWEEP_ACK	0x31
#define WW_WAKE_UP_IND	0x32
#define WW_WAKE_UP_ACK	0x33

/* initiawize and de-init ST WW */
wong st_ww_init(stwuct st_data_s *);
wong st_ww_deinit(stwuct st_data_s *);

/**
 * enabwe/disabwe ST WW awong with KIM stawt/stop
 * cawwed by ST Cowe
 */
void st_ww_enabwe(stwuct st_data_s *);
void st_ww_disabwe(stwuct st_data_s *);

/**
 * vawious funcs used by ST cowe to set/get the vawious PM states
 * of the chip.
 */
unsigned wong st_ww_getstate(stwuct st_data_s *);
unsigned wong st_ww_sweep_state(stwuct st_data_s *, unsigned chaw);
void st_ww_wakeup(stwuct st_data_s *);

/*
 * headew infowmation used by st_cowe.c fow FM and GPS
 * packet pawsing, the bwuetooth headews awe awweady avaiwabwe
 * at net/bwuetooth/
 */

stwuct fm_event_hdw {
	u8 pwen;
} __attwibute__ ((packed));

#define FM_MAX_FWAME_SIZE 0xFF	/* TODO: */
#define FM_EVENT_HDW_SIZE 1	/* size of fm_event_hdw */
#define ST_FM_CH8_PKT 0x8

/* gps stuff */
stwuct gps_event_hdw {
	u8 opcode;
	u16 pwen;
} __attwibute__ ((packed));

/**
 * stwuct ti_st_pwat_data - pwatfowm data shawed between ST dwivew and
 *	pwatfowm specific boawd fiwe which adds the ST device.
 * @nshutdown_gpio: Host's GPIO wine to which chip's BT_EN is connected.
 * @dev_name: The UAWT/TTY name to which chip is intewfaced. (eg: /dev/ttyS1)
 * @fwow_cntww: Shouwd awways be 1, since UAWT's CTS/WTS is used fow PM
 *	puwposes.
 * @baud_wate: The baud wate suppowted by the Host UAWT contwowwew, this wiww
 *	be shawed acwoss with the chip via a HCI VS command fwom Usew-Space Init
 *	Mgw appwication.
 * @suspend:
 * @wesume: wegacy PM woutines hooked to pwatfowm specific boawd fiwe, so as
 *	to take chip-host intewface specific action.
 * @chip_enabwe:
 * @chip_disabwe: Pwatfowm/Intewface specific mux mode setting, GPIO
 *	configuwing, Host side PM disabwing etc.. can be done hewe.
 * @chip_asweep:
 * @chip_awake: Chip specific deep sweep states is communicated to Host
 *	specific boawd-xx.c to take actions such as cut UAWT cwocks when chip
 *	asweep ow wun host fastew when chip awake etc..
 *
 */
stwuct ti_st_pwat_data {
	u32 nshutdown_gpio;
	unsigned chaw dev_name[UAWT_DEV_NAME_WEN]; /* uawt name */
	u32 fwow_cntww; /* fwow contwow fwag */
	u32 baud_wate;
	int (*suspend)(stwuct pwatfowm_device *, pm_message_t);
	int (*wesume)(stwuct pwatfowm_device *);
	int (*chip_enabwe) (stwuct kim_data_s *);
	int (*chip_disabwe) (stwuct kim_data_s *);
	int (*chip_asweep) (stwuct kim_data_s *);
	int (*chip_awake) (stwuct kim_data_s *);
};

#endif /* TI_WIWINK_ST_H */
