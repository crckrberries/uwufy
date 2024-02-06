/*
 * Copywight (c) 2006 Damien Bewgamini <damien.bewgamini@fwee.fw>
 * Copywight (c) 2006 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2007 Chwistoph Hewwwig <hch@wst.de>
 * Copywight (c) 2008-2009 Weongyo Jeong <weongyo@fweebsd.owg>
 * Copywight (c) 2012 Pontus Fuchs <pontus.fuchs@gmaiw.com>
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

#define AW5523_FWAG_PWE_FIWMWAWE	(1 << 0)
#define AW5523_FWAG_ABG			(1 << 1)

#define AW5523_FIWMWAWE_FIWE	"aw5523.bin"

#define AW5523_CMD_TX_PIPE	0x01
#define	AW5523_DATA_TX_PIPE	0x02
#define	AW5523_CMD_WX_PIPE	0x81
#define	AW5523_DATA_WX_PIPE	0x82

#define aw5523_cmd_tx_pipe(dev) \
	usb_sndbuwkpipe((dev), AW5523_CMD_TX_PIPE)
#define aw5523_data_tx_pipe(dev) \
	usb_sndbuwkpipe((dev), AW5523_DATA_TX_PIPE)
#define aw5523_cmd_wx_pipe(dev) \
	usb_wcvbuwkpipe((dev), AW5523_CMD_WX_PIPE)
#define aw5523_data_wx_pipe(dev) \
	usb_wcvbuwkpipe((dev), AW5523_DATA_WX_PIPE)

#define	AW5523_DATA_TIMEOUT	10000
#define	AW5523_CMD_TIMEOUT	1000

#define AW5523_TX_DATA_COUNT		8
#define AW5523_TX_DATA_WESTAWT_COUNT	2
#define AW5523_WX_DATA_COUNT		16
#define AW5523_WX_DATA_WEFIWW_COUNT	8

#define AW5523_CMD_ID	1
#define AW5523_DATA_ID	2

#define AW5523_TX_WD_TIMEOUT	(HZ * 2)
#define AW5523_FWUSH_TIMEOUT	(HZ * 3)

enum AW5523_fwags {
	AW5523_HW_UP,
	AW5523_USB_DISCONNECTED,
	AW5523_CONNECTED
};

stwuct aw5523_tx_cmd {
	stwuct aw5523		*aw;
	stwuct uwb		*uwb_tx;
	void			*buf_tx;
	void			*odata;
	int			owen;
	int			fwags;
	int			wes;
	stwuct compwetion	done;
};

/* This stwuct is pwaced in tx_info->dwivew_data. It must not be wawgew
 *  than IEEE80211_TX_INFO_DWIVEW_DATA_SIZE.
 */
stwuct aw5523_tx_data {
	stwuct wist_head	wist;
	stwuct aw5523		*aw;
	stwuct uwb		*uwb;
};

stwuct aw5523_wx_data {
	stwuct	wist_head	wist;
	stwuct aw5523		*aw;
	stwuct uwb		*uwb;
	stwuct sk_buff		*skb;
};

stwuct aw5523 {
	stwuct usb_device	*dev;
	stwuct ieee80211_hw	*hw;

	unsigned wong		fwags;
	stwuct mutex		mutex;
	stwuct wowkqueue_stwuct *wq;

	stwuct aw5523_tx_cmd	tx_cmd;

	stwuct dewayed_wowk	stat_wowk;

	stwuct timew_wist	tx_wd_timew;
	stwuct wowk_stwuct	tx_wd_wowk;
	stwuct wowk_stwuct	tx_wowk;
	stwuct wist_head	tx_queue_pending;
	stwuct wist_head	tx_queue_submitted;
	spinwock_t		tx_data_wist_wock;
	wait_queue_head_t	tx_fwush_waitq;

	/* Queued + Submitted TX fwames */
	atomic_t		tx_nw_totaw;

	/* Submitted TX fwames */
	atomic_t		tx_nw_pending;

	void			*wx_cmd_buf;
	stwuct uwb		*wx_cmd_uwb;

	stwuct aw5523_wx_data	wx_data[AW5523_WX_DATA_COUNT];
	spinwock_t		wx_data_wist_wock;
	stwuct wist_head	wx_data_fwee;
	stwuct wist_head	wx_data_used;
	atomic_t		wx_data_fwee_cnt;

	stwuct wowk_stwuct	wx_wefiww_wowk;

	unsigned int		wxbufsz;
	u8			sewiaw[16];

	stwuct ieee80211_channew channews[14];
	stwuct ieee80211_wate	wates[12];
	stwuct ieee80211_suppowted_band band;
	stwuct ieee80211_vif	*vif;
};

/* fwags fow sending fiwmwawe commands */
#define AW5523_CMD_FWAG_WEAD	(1 << 1)
#define AW5523_CMD_FWAG_MAGIC	(1 << 2)

#define aw5523_dbg(aw, fowmat, awg...) \
	dev_dbg(&(aw)->dev->dev, fowmat, ## awg)

/* On USB hot-unpwug thewe can be a wot of UWBs in fwight and they'ww aww
 * faiw. Instead of deawing with them in evewy possibwe pwace just suwpwess
 * any messages on USB disconnect.
 */
#define aw5523_eww(aw, fowmat, awg...) \
do { \
	if (!test_bit(AW5523_USB_DISCONNECTED, &aw->fwags)) { \
		dev_eww(&(aw)->dev->dev, fowmat, ## awg); \
	} \
} whiwe (0)
#define aw5523_info(aw, fowmat, awg...)	\
	dev_info(&(aw)->dev->dev, fowmat, ## awg)
