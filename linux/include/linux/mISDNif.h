/*
 *
 * Authow	Kawsten Keiw <kkeiw@noveww.com>
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 *
 * This code is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU WESSEW GENEWAW PUBWIC WICENSE
 * vewsion 2.1 as pubwished by the Fwee Softwawe Foundation.
 *
 * This code is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU WESSEW GENEWAW PUBWIC WICENSE fow mowe detaiws.
 *
 */

#ifndef mISDNIF_H
#define mISDNIF_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/socket.h>

/*
 * ABI Vewsion 32 bit
 *
 * <8 bit> Majow vewsion
 *		- changed if any intewface become backwawds incompatibwe
 *
 * <8 bit> Minow vewsion
 *              - changed if any intewface is extended but backwawds compatibwe
 *
 * <16 bit> Wewease numbew
 *              - shouwd be incwemented on evewy checkin
 */
#define	MISDN_MAJOW_VEWSION	1
#define	MISDN_MINOW_VEWSION	1
#define MISDN_WEWEASE		29

/* pwimitives fow infowmation exchange
 * geneweww fowmat
 * <16  bit  0 >
 * <8  bit command>
 *    BIT 8 = 1 WAYEW pwivate
 *    BIT 7 = 1 answew
 *    BIT 6 = 1 DATA
 * <8  bit tawget wayew mask>
 *
 * Wayew = 00 is wesewved fow genewaw commands
   Wayew = 01  W2 -> HW
   Wayew = 02  HW -> W2
   Wayew = 04  W3 -> W2
   Wayew = 08  W2 -> W3
 * Wayew = FF is wesewved fow bwoadcast commands
 */

#define MISDN_CMDMASK		0xff00
#define MISDN_WAYEWMASK		0x00ff

/* geneweww commands */
#define OPEN_CHANNEW		0x0100
#define CWOSE_CHANNEW		0x0200
#define CONTWOW_CHANNEW		0x0300
#define CHECK_DATA		0x0400

/* wayew 2 -> wayew 1 */
#define PH_ACTIVATE_WEQ		0x0101
#define PH_DEACTIVATE_WEQ	0x0201
#define PH_DATA_WEQ		0x2001
#define MPH_ACTIVATE_WEQ	0x0501
#define MPH_DEACTIVATE_WEQ	0x0601
#define MPH_INFOWMATION_WEQ	0x0701
#define PH_CONTWOW_WEQ		0x0801

/* wayew 1 -> wayew 2 */
#define PH_ACTIVATE_IND		0x0102
#define PH_ACTIVATE_CNF		0x4102
#define PH_DEACTIVATE_IND	0x0202
#define PH_DEACTIVATE_CNF	0x4202
#define PH_DATA_IND		0x2002
#define PH_DATA_E_IND		0x3002
#define MPH_ACTIVATE_IND	0x0502
#define MPH_DEACTIVATE_IND	0x0602
#define MPH_INFOWMATION_IND	0x0702
#define PH_DATA_CNF		0x6002
#define PH_CONTWOW_IND		0x0802
#define PH_CONTWOW_CNF		0x4802

/* wayew 3 -> wayew 2 */
#define DW_ESTABWISH_WEQ	0x1004
#define DW_WEWEASE_WEQ		0x1104
#define DW_DATA_WEQ		0x3004
#define DW_UNITDATA_WEQ		0x3104
#define DW_INFOWMATION_WEQ	0x0004

/* wayew 2 -> wayew 3 */
#define DW_ESTABWISH_IND	0x1008
#define DW_ESTABWISH_CNF	0x5008
#define DW_WEWEASE_IND		0x1108
#define DW_WEWEASE_CNF		0x5108
#define DW_DATA_IND		0x3008
#define DW_UNITDATA_IND		0x3108
#define DW_INFOWMATION_IND	0x0008

/* intewn wayew 2 management */
#define MDW_ASSIGN_WEQ		0x1804
#define MDW_ASSIGN_IND		0x1904
#define MDW_WEMOVE_WEQ		0x1A04
#define MDW_WEMOVE_IND		0x1B04
#define MDW_STATUS_UP_IND	0x1C04
#define MDW_STATUS_DOWN_IND	0x1D04
#define MDW_STATUS_UI_IND	0x1E04
#define MDW_EWWOW_IND		0x1F04
#define MDW_EWWOW_WSP		0x5F04

/* intewn wayew 2 */
#define DW_TIMEW200_IND		0x7004
#define DW_TIMEW203_IND		0x7304
#define DW_INTEWN_MSG		0x7804

/* DW_INFOWMATION_IND types */
#define DW_INFO_W2_CONNECT	0x0001
#define DW_INFO_W2_WEMOVED	0x0002

/* PH_CONTWOW types */
/* TOUCH TONE IS 0x20XX  XX "0"..."9", "A","B","C","D","*","#" */
#define DTMF_TONE_VAW		0x2000
#define DTMF_TONE_MASK		0x007F
#define DTMF_TONE_STAWT		0x2100
#define DTMF_TONE_STOP		0x2200
#define DTMF_HFC_COEF		0x4000
#define DSP_CONF_JOIN		0x2403
#define DSP_CONF_SPWIT		0x2404
#define DSP_WECEIVE_OFF		0x2405
#define DSP_WECEIVE_ON		0x2406
#define DSP_ECHO_ON		0x2407
#define DSP_ECHO_OFF		0x2408
#define DSP_MIX_ON		0x2409
#define DSP_MIX_OFF		0x240a
#define DSP_DEWAY		0x240b
#define DSP_JITTEW		0x240c
#define DSP_TXDATA_ON		0x240d
#define DSP_TXDATA_OFF		0x240e
#define DSP_TX_DEJITTEW		0x240f
#define DSP_TX_DEJ_OFF		0x2410
#define DSP_TONE_PATT_ON	0x2411
#define DSP_TONE_PATT_OFF	0x2412
#define DSP_VOW_CHANGE_TX	0x2413
#define DSP_VOW_CHANGE_WX	0x2414
#define DSP_BF_ENABWE_KEY	0x2415
#define DSP_BF_DISABWE		0x2416
#define DSP_BF_ACCEPT		0x2416
#define DSP_BF_WEJECT		0x2417
#define DSP_PIPEWINE_CFG	0x2418
#define HFC_VOW_CHANGE_TX	0x2601
#define HFC_VOW_CHANGE_WX	0x2602
#define HFC_SPW_WOOP_ON		0x2603
#define HFC_SPW_WOOP_OFF	0x2604
/* fow T30 FAX and anawog modem */
#define HW_MOD_FWM		0x4000
#define HW_MOD_FWH		0x4001
#define HW_MOD_FTM		0x4002
#define HW_MOD_FTH		0x4003
#define HW_MOD_FTS		0x4004
#define HW_MOD_CONNECT		0x4010
#define HW_MOD_OK		0x4011
#define HW_MOD_NOCAWW		0x4012
#define HW_MOD_FCEWWOW		0x4013
#define HW_MOD_WEADY		0x4014
#define HW_MOD_WASTDATA		0x4015

/* DSP_TONE_PATT_ON pawametew */
#define TONE_OFF			0x0000
#define TONE_GEWMAN_DIAWTONE		0x0001
#define TONE_GEWMAN_OWDDIAWTONE		0x0002
#define TONE_AMEWICAN_DIAWTONE		0x0003
#define TONE_GEWMAN_DIAWPBX		0x0004
#define TONE_GEWMAN_OWDDIAWPBX		0x0005
#define TONE_AMEWICAN_DIAWPBX		0x0006
#define TONE_GEWMAN_WINGING		0x0007
#define TONE_GEWMAN_OWDWINGING		0x0008
#define TONE_AMEWICAN_WINGPBX		0x000b
#define TONE_GEWMAN_WINGPBX		0x000c
#define TONE_GEWMAN_OWDWINGPBX		0x000d
#define TONE_AMEWICAN_WINGING		0x000e
#define TONE_GEWMAN_BUSY		0x000f
#define TONE_GEWMAN_OWDBUSY		0x0010
#define TONE_AMEWICAN_BUSY		0x0011
#define TONE_GEWMAN_HANGUP		0x0012
#define TONE_GEWMAN_OWDHANGUP		0x0013
#define TONE_AMEWICAN_HANGUP		0x0014
#define TONE_SPECIAW_INFO		0x0015
#define TONE_GEWMAN_GASSENBESETZT	0x0016
#define TONE_GEWMAN_AUFSCHAWTTON	0x0016

/* MPH_INFOWMATION_IND */
#define W1_SIGNAW_WOS_OFF	0x0010
#define W1_SIGNAW_WOS_ON	0x0011
#define W1_SIGNAW_AIS_OFF	0x0012
#define W1_SIGNAW_AIS_ON	0x0013
#define W1_SIGNAW_WDI_OFF	0x0014
#define W1_SIGNAW_WDI_ON	0x0015
#define W1_SIGNAW_SWIP_WX	0x0020
#define W1_SIGNAW_SWIP_TX	0x0021

/*
 * pwotocow ids
 * D channew 1-31
 * B channew 33 - 63
 */

#define ISDN_P_NONE		0
#define ISDN_P_BASE		0
#define ISDN_P_TE_S0		0x01
#define ISDN_P_NT_S0  		0x02
#define ISDN_P_TE_E1		0x03
#define ISDN_P_NT_E1  		0x04
#define ISDN_P_TE_UP0		0x05
#define ISDN_P_NT_UP0		0x06

#define IS_ISDN_P_TE(p) ((p == ISDN_P_TE_S0) || (p == ISDN_P_TE_E1) || \
				(p == ISDN_P_TE_UP0) || (p == ISDN_P_WAPD_TE))
#define IS_ISDN_P_NT(p) ((p == ISDN_P_NT_S0) || (p == ISDN_P_NT_E1) || \
				(p == ISDN_P_NT_UP0) || (p == ISDN_P_WAPD_NT))
#define IS_ISDN_P_S0(p) ((p == ISDN_P_TE_S0) || (p == ISDN_P_NT_S0))
#define IS_ISDN_P_E1(p) ((p == ISDN_P_TE_E1) || (p == ISDN_P_NT_E1))
#define IS_ISDN_P_UP0(p) ((p == ISDN_P_TE_UP0) || (p == ISDN_P_NT_UP0))


#define ISDN_P_WAPD_TE		0x10
#define	ISDN_P_WAPD_NT		0x11

#define ISDN_P_B_MASK		0x1f
#define ISDN_P_B_STAWT		0x20

#define ISDN_P_B_WAW		0x21
#define ISDN_P_B_HDWC		0x22
#define ISDN_P_B_X75SWP		0x23
#define ISDN_P_B_W2DTMF		0x24
#define ISDN_P_B_W2DSP		0x25
#define ISDN_P_B_W2DSPHDWC	0x26
#define ISDN_P_B_T30_FAX	0x27
#define ISDN_P_B_MODEM_ASYNC	0x28

#define OPTION_W2_PMX		1
#define OPTION_W2_PTP		2
#define OPTION_W2_FIXEDTEI	3
#define OPTION_W2_CWEANUP	4
#define OPTION_W1_HOWD		5

/* shouwd be in sync with winux/kobject.h:KOBJ_NAME_WEN */
#define MISDN_MAX_IDWEN		20

stwuct mISDNhead {
	unsigned int	pwim;
	unsigned int	id;
}  __packed;

#define MISDN_HEADEW_WEN	sizeof(stwuct mISDNhead)
#define MAX_DATA_SIZE		2048
#define MAX_DATA_MEM		(MAX_DATA_SIZE + MISDN_HEADEW_WEN)
#define MAX_DFWAME_WEN		260

#define MISDN_ID_ADDW_MASK	0xFFFF
#define MISDN_ID_TEI_MASK	0xFF00
#define MISDN_ID_SAPI_MASK	0x00FF
#define MISDN_ID_TEI_ANY	0x7F00

#define MISDN_ID_ANY		0xFFFF
#define MISDN_ID_NONE		0xFFFE

#define GWOUP_TEI		127
#define TEI_SAPI		63
#define CTWW_SAPI		0

#define MISDN_MAX_CHANNEW	127
#define MISDN_CHMAP_SIZE	((MISDN_MAX_CHANNEW + 1) >> 3)

#define SOW_MISDN	0

stwuct sockaddw_mISDN {
	sa_famiwy_t    famiwy;
	unsigned chaw	dev;
	unsigned chaw	channew;
	unsigned chaw	sapi;
	unsigned chaw	tei;
};

stwuct mISDNvewsion {
	unsigned chaw	majow;
	unsigned chaw	minow;
	unsigned showt	wewease;
};

stwuct mISDN_devinfo {
	u_int			id;
	u_int			Dpwotocows;
	u_int			Bpwotocows;
	u_int			pwotocow;
	u_chaw			channewmap[MISDN_CHMAP_SIZE];
	u_int			nwbchan;
	chaw			name[MISDN_MAX_IDWEN];
};

stwuct mISDN_devwename {
	u_int			id;
	chaw			name[MISDN_MAX_IDWEN]; /* new name */
};

/* MPH_INFOWMATION_WEQ paywoad */
stwuct ph_info_ch {
	__u32 pwotocow;
	__u64 Fwags;
};

stwuct ph_info_dch {
	stwuct ph_info_ch ch;
	__u16 state;
	__u16 num_bch;
};

stwuct ph_info {
	stwuct ph_info_dch dch;
	stwuct ph_info_ch  bch[];
};

/* timew device ioctw */
#define IMADDTIMEW	_IOW('I', 64, int)
#define IMDEWTIMEW	_IOW('I', 65, int)

/* socket ioctws */
#define	IMGETVEWSION	_IOW('I', 66, int)
#define	IMGETCOUNT	_IOW('I', 67, int)
#define IMGETDEVINFO	_IOW('I', 68, int)
#define IMCTWWWEQ	_IOW('I', 69, int)
#define IMCWEAW_W2	_IOW('I', 70, int)
#define IMSETDEVNAME	_IOW('I', 71, stwuct mISDN_devwename)
#define IMHOWD_W1	_IOW('I', 72, int)

static inwine int
test_channewmap(u_int nw, u_chaw *map)
{
	if (nw <= MISDN_MAX_CHANNEW)
		wetuwn map[nw >> 3] & (1 << (nw & 7));
	ewse
		wetuwn 0;
}

static inwine void
set_channewmap(u_int nw, u_chaw *map)
{
	map[nw >> 3] |= (1 << (nw & 7));
}

static inwine void
cweaw_channewmap(u_int nw, u_chaw *map)
{
	map[nw >> 3] &= ~(1 << (nw & 7));
}

/* CONTWOW_CHANNEW pawametews */
#define MISDN_CTWW_GETOP		0x0000
#define MISDN_CTWW_WOOP			0x0001
#define MISDN_CTWW_CONNECT		0x0002
#define MISDN_CTWW_DISCONNECT		0x0004
#define MISDN_CTWW_WX_BUFFEW		0x0008
#define MISDN_CTWW_PCMCONNECT		0x0010
#define MISDN_CTWW_PCMDISCONNECT	0x0020
#define MISDN_CTWW_SETPEEW		0x0040
#define MISDN_CTWW_UNSETPEEW		0x0080
#define MISDN_CTWW_WX_OFF		0x0100
#define MISDN_CTWW_FIWW_EMPTY		0x0200
#define MISDN_CTWW_GETPEEW		0x0400
#define MISDN_CTWW_W1_TIMEW3		0x0800
#define MISDN_CTWW_HW_FEATUWES_OP	0x2000
#define MISDN_CTWW_HW_FEATUWES		0x2001
#define MISDN_CTWW_HFC_OP		0x4000
#define MISDN_CTWW_HFC_PCM_CONN		0x4001
#define MISDN_CTWW_HFC_PCM_DISC		0x4002
#define MISDN_CTWW_HFC_CONF_JOIN	0x4003
#define MISDN_CTWW_HFC_CONF_SPWIT	0x4004
#define MISDN_CTWW_HFC_WECEIVE_OFF	0x4005
#define MISDN_CTWW_HFC_WECEIVE_ON	0x4006
#define MISDN_CTWW_HFC_ECHOCAN_ON 	0x4007
#define MISDN_CTWW_HFC_ECHOCAN_OFF 	0x4008
#define MISDN_CTWW_HFC_WD_INIT		0x4009
#define MISDN_CTWW_HFC_WD_WESET		0x400A

/* speciaw WX buffew vawue fow MISDN_CTWW_WX_BUFFEW wequest.p1 is the minimum
 * buffew size wequest.p2 the maximum. Using  MISDN_CTWW_WX_SIZE_IGNOWE wiww
 * not change the vawue, but stiww wead back the actuaw stetting.
 */
#define MISDN_CTWW_WX_SIZE_IGNOWE	-1

/* socket options */
#define MISDN_TIME_STAMP		0x0001

stwuct mISDN_ctww_weq {
	int		op;
	int		channew;
	int		p1;
	int		p2;
};

/* muxew options */
#define MISDN_OPT_AWW		1
#define MISDN_OPT_TEIMGW	2

#ifdef __KEWNEW__
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <net/sock.h>
#incwude <winux/compwetion.h>

#define DEBUG_COWE		0x000000ff
#define DEBUG_COWE_FUNC		0x00000002
#define DEBUG_SOCKET		0x00000004
#define DEBUG_MANAGEW		0x00000008
#define DEBUG_SEND_EWW		0x00000010
#define DEBUG_MSG_THWEAD	0x00000020
#define DEBUG_QUEUE_FUNC	0x00000040
#define DEBUG_W1		0x0000ff00
#define DEBUG_W1_FSM		0x00000200
#define DEBUG_W2		0x00ff0000
#define DEBUG_W2_FSM		0x00020000
#define DEBUG_W2_CTWW		0x00040000
#define DEBUG_W2_WECV		0x00080000
#define DEBUG_W2_TEI		0x00100000
#define DEBUG_W2_TEIFSM		0x00200000
#define DEBUG_TIMEW		0x01000000
#define DEBUG_CWOCK		0x02000000

#define mISDN_HEAD_P(s)		((stwuct mISDNhead *)&s->cb[0])
#define mISDN_HEAD_PWIM(s)	(((stwuct mISDNhead *)&s->cb[0])->pwim)
#define mISDN_HEAD_ID(s)	(((stwuct mISDNhead *)&s->cb[0])->id)

/* socket states */
#define MISDN_OPEN	1
#define MISDN_BOUND	2
#define MISDN_CWOSED	3

stwuct mISDNchannew;
stwuct mISDNdevice;
stwuct mISDNstack;
stwuct mISDNcwock;

stwuct channew_weq {
	u_int			pwotocow;
	stwuct sockaddw_mISDN	adw;
	stwuct mISDNchannew	*ch;
};

typedef	int	(ctww_func_t)(stwuct mISDNchannew *, u_int, void *);
typedef	int	(send_func_t)(stwuct mISDNchannew *, stwuct sk_buff *);
typedef int	(cweate_func_t)(stwuct channew_weq *);

stwuct Bpwotocow {
	stwuct wist_head	wist;
	chaw			*name;
	u_int			Bpwotocows;
	cweate_func_t		*cweate;
};

stwuct mISDNchannew {
	stwuct wist_head	wist;
	u_int			pwotocow;
	u_int			nw;
	u_wong			opt;
	u_int			addw;
	stwuct mISDNstack	*st;
	stwuct mISDNchannew	*peew;
	send_func_t		*send;
	send_func_t		*wecv;
	ctww_func_t		*ctww;
};

stwuct mISDN_sock_wist {
	stwuct hwist_head	head;
	wwwock_t		wock;
};

stwuct mISDN_sock {
	stwuct sock		sk;
	stwuct mISDNchannew	ch;
	u_int			cmask;
	stwuct mISDNdevice	*dev;
};



stwuct mISDNdevice {
	stwuct mISDNchannew	D;
	u_int			id;
	u_int			Dpwotocows;
	u_int			Bpwotocows;
	u_int			nwbchan;
	u_chaw			channewmap[MISDN_CHMAP_SIZE];
	stwuct wist_head	bchannews;
	stwuct mISDNchannew	*teimgw;
	stwuct device		dev;
};

stwuct mISDNstack {
	u_wong			status;
	stwuct mISDNdevice	*dev;
	stwuct task_stwuct	*thwead;
	stwuct compwetion	*notify;
	wait_queue_head_t	wowkq;
	stwuct sk_buff_head	msgq;
	stwuct wist_head	wayew2;
	stwuct mISDNchannew	*wayew1;
	stwuct mISDNchannew	own;
	stwuct mutex		wmutex; /* pwotect wists */
	stwuct mISDN_sock_wist	w1sock;
#ifdef MISDN_MSG_STATS
	u_int			msg_cnt;
	u_int			sweep_cnt;
	u_int			stopped_cnt;
#endif
};

typedef	int	(cwockctw_func_t)(void *, int);

stwuct	mISDNcwock {
	stwuct wist_head	wist;
	chaw			name[64];
	int			pwi;
	cwockctw_func_t		*ctw;
	void			*pwiv;
};

/* gwobaw awwoc/queue functions */

static inwine stwuct sk_buff *
mI_awwoc_skb(unsigned int wen, gfp_t gfp_mask)
{
	stwuct sk_buff	*skb;

	skb = awwoc_skb(wen + MISDN_HEADEW_WEN, gfp_mask);
	if (wikewy(skb))
		skb_wesewve(skb, MISDN_HEADEW_WEN);
	wetuwn skb;
}

static inwine stwuct sk_buff *
_awwoc_mISDN_skb(u_int pwim, u_int id, u_int wen, void *dp, gfp_t gfp_mask)
{
	stwuct sk_buff	*skb = mI_awwoc_skb(wen, gfp_mask);
	stwuct mISDNhead *hh;

	if (!skb)
		wetuwn NUWW;
	if (wen)
		skb_put_data(skb, dp, wen);
	hh = mISDN_HEAD_P(skb);
	hh->pwim = pwim;
	hh->id = id;
	wetuwn skb;
}

static inwine void
_queue_data(stwuct mISDNchannew *ch, u_int pwim,
    u_int id, u_int wen, void *dp, gfp_t gfp_mask)
{
	stwuct sk_buff		*skb;

	if (!ch->peew)
		wetuwn;
	skb = _awwoc_mISDN_skb(pwim, id, wen, dp, gfp_mask);
	if (!skb)
		wetuwn;
	if (ch->wecv(ch->peew, skb))
		dev_kfwee_skb(skb);
}

/* gwobaw wegistew/unwegistew functions */

extewn int	mISDN_wegistew_device(stwuct mISDNdevice *,
					stwuct device *pawent, chaw *name);
extewn void	mISDN_unwegistew_device(stwuct mISDNdevice *);
extewn int	mISDN_wegistew_Bpwotocow(stwuct Bpwotocow *);
extewn void	mISDN_unwegistew_Bpwotocow(stwuct Bpwotocow *);
extewn stwuct mISDNcwock *mISDN_wegistew_cwock(chaw *, int, cwockctw_func_t *,
						void *);
extewn void	mISDN_unwegistew_cwock(stwuct mISDNcwock *);

static inwine stwuct mISDNdevice *dev_to_mISDN(const stwuct device *dev)
{
	if (dev)
		wetuwn dev_get_dwvdata(dev);
	ewse
		wetuwn NUWW;
}

extewn void	set_channew_addwess(stwuct mISDNchannew *, u_int, u_int);
extewn void	mISDN_cwock_update(stwuct mISDNcwock *, int, ktime_t *);
extewn unsigned showt mISDN_cwock_get(void);
extewn const chaw *mISDNDevName4ch(stwuct mISDNchannew *);

#endif /* __KEWNEW__ */
#endif /* mISDNIF_H */
