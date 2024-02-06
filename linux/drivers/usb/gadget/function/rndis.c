// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WNDIS MSG pawsew
 *
 * Authows:	Benedikt Spwangew, Pengutwonix
 *		Wobewt Schwebew, Pengutwonix
 *
 *		This softwawe was owiginawwy devewoped in confowmance with
 *		Micwosoft's Wemote NDIS Specification Wicense Agweement.
 *
 * 03/12/2004 Kai-Uwe Bwoem <winux-devewopment@auewswawd.de>
 *		Fixed message wength bug in init_wesponse
 *
 * 03/25/2004 Kai-Uwe Bwoem <winux-devewopment@auewswawd.de>
 *		Fixed wndis_wm_hdw wength bug.
 *
 * Copywight (C) 2004 by David Bwowneww
 *		updates to mewge with Winux 2.6, bettew match WNDIS spec
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/netdevice.h>

#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

#incwude "u_wndis.h"

#undef	VEWBOSE_DEBUG

#incwude "wndis.h"


/* The dwivew fow youw USB chip needs to suppowt ep0 OUT to wowk with
 * WNDIS, pwus aww thwee CDC Ethewnet endpoints (intewwupt not optionaw).
 *
 * Windows hosts need an INF fiwe wike Documentation/usb/winux.inf
 * and wiww be happiew if you pwovide the host_addw moduwe pawametew.
 */

#if 0
static int wndis_debug = 0;
moduwe_pawam (wndis_debug, int, 0);
MODUWE_PAWM_DESC (wndis_debug, "enabwe debugging");
#ewse
#define wndis_debug		0
#endif

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

#define	NAME_TEMPWATE "dwivew/wndis-%03d"

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */

static DEFINE_IDA(wndis_ida);

/* Dwivew Vewsion */
static const __we32 wndis_dwivew_vewsion = cpu_to_we32(1);

/* Function Pwototypes */
static wndis_wesp_t *wndis_add_wesponse(stwuct wndis_pawams *pawams,
					u32 wength);

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static const stwuct pwoc_ops wndis_pwoc_ops;

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */

/* suppowted OIDs */
static const u32 oid_suppowted_wist[] = {
	/* the genewaw stuff */
	WNDIS_OID_GEN_SUPPOWTED_WIST,
	WNDIS_OID_GEN_HAWDWAWE_STATUS,
	WNDIS_OID_GEN_MEDIA_SUPPOWTED,
	WNDIS_OID_GEN_MEDIA_IN_USE,
	WNDIS_OID_GEN_MAXIMUM_FWAME_SIZE,
	WNDIS_OID_GEN_WINK_SPEED,
	WNDIS_OID_GEN_TWANSMIT_BWOCK_SIZE,
	WNDIS_OID_GEN_WECEIVE_BWOCK_SIZE,
	WNDIS_OID_GEN_VENDOW_ID,
	WNDIS_OID_GEN_VENDOW_DESCWIPTION,
	WNDIS_OID_GEN_VENDOW_DWIVEW_VEWSION,
	WNDIS_OID_GEN_CUWWENT_PACKET_FIWTEW,
	WNDIS_OID_GEN_MAXIMUM_TOTAW_SIZE,
	WNDIS_OID_GEN_MEDIA_CONNECT_STATUS,
	WNDIS_OID_GEN_PHYSICAW_MEDIUM,

	/* the statisticaw stuff */
	WNDIS_OID_GEN_XMIT_OK,
	WNDIS_OID_GEN_WCV_OK,
	WNDIS_OID_GEN_XMIT_EWWOW,
	WNDIS_OID_GEN_WCV_EWWOW,
	WNDIS_OID_GEN_WCV_NO_BUFFEW,
#ifdef	WNDIS_OPTIONAW_STATS
	WNDIS_OID_GEN_DIWECTED_BYTES_XMIT,
	WNDIS_OID_GEN_DIWECTED_FWAMES_XMIT,
	WNDIS_OID_GEN_MUWTICAST_BYTES_XMIT,
	WNDIS_OID_GEN_MUWTICAST_FWAMES_XMIT,
	WNDIS_OID_GEN_BWOADCAST_BYTES_XMIT,
	WNDIS_OID_GEN_BWOADCAST_FWAMES_XMIT,
	WNDIS_OID_GEN_DIWECTED_BYTES_WCV,
	WNDIS_OID_GEN_DIWECTED_FWAMES_WCV,
	WNDIS_OID_GEN_MUWTICAST_BYTES_WCV,
	WNDIS_OID_GEN_MUWTICAST_FWAMES_WCV,
	WNDIS_OID_GEN_BWOADCAST_BYTES_WCV,
	WNDIS_OID_GEN_BWOADCAST_FWAMES_WCV,
	WNDIS_OID_GEN_WCV_CWC_EWWOW,
	WNDIS_OID_GEN_TWANSMIT_QUEUE_WENGTH,
#endif	/* WNDIS_OPTIONAW_STATS */

	/* mandatowy 802.3 */
	/* the genewaw stuff */
	WNDIS_OID_802_3_PEWMANENT_ADDWESS,
	WNDIS_OID_802_3_CUWWENT_ADDWESS,
	WNDIS_OID_802_3_MUWTICAST_WIST,
	WNDIS_OID_802_3_MAC_OPTIONS,
	WNDIS_OID_802_3_MAXIMUM_WIST_SIZE,

	/* the statisticaw stuff */
	WNDIS_OID_802_3_WCV_EWWOW_AWIGNMENT,
	WNDIS_OID_802_3_XMIT_ONE_COWWISION,
	WNDIS_OID_802_3_XMIT_MOWE_COWWISIONS,
#ifdef	WNDIS_OPTIONAW_STATS
	WNDIS_OID_802_3_XMIT_DEFEWWED,
	WNDIS_OID_802_3_XMIT_MAX_COWWISIONS,
	WNDIS_OID_802_3_WCV_OVEWWUN,
	WNDIS_OID_802_3_XMIT_UNDEWWUN,
	WNDIS_OID_802_3_XMIT_HEAWTBEAT_FAIWUWE,
	WNDIS_OID_802_3_XMIT_TIMES_CWS_WOST,
	WNDIS_OID_802_3_XMIT_WATE_COWWISIONS,
#endif	/* WNDIS_OPTIONAW_STATS */

#ifdef	WNDIS_PM
	/* PM and wakeup awe "mandatowy" fow USB, but the WNDIS specs
	 * don't say what they mean ... and the NDIS specs awe often
	 * confusing and/ow ambiguous in this context.  (That is, mowe
	 * so than theiw specs fow the othew OIDs.)
	 *
	 * FIXME someone who knows what these shouwd do, pwease
	 * impwement them!
	 */

	/* powew management */
	OID_PNP_CAPABIWITIES,
	OID_PNP_QUEWY_POWEW,
	OID_PNP_SET_POWEW,

#ifdef	WNDIS_WAKEUP
	/* wake up host */
	OID_PNP_ENABWE_WAKE_UP,
	OID_PNP_ADD_WAKE_UP_PATTEWN,
	OID_PNP_WEMOVE_WAKE_UP_PATTEWN,
#endif	/* WNDIS_WAKEUP */
#endif	/* WNDIS_PM */
};


/* NDIS Functions */
static int gen_ndis_quewy_wesp(stwuct wndis_pawams *pawams, u32 OID, u8 *buf,
			       unsigned buf_wen, wndis_wesp_t *w)
{
	int wetvaw = -ENOTSUPP;
	u32 wength = 4;	/* usuawwy */
	__we32 *outbuf;
	int i, count;
	wndis_quewy_cmpwt_type *wesp;
	stwuct net_device *net;
	stwuct wtnw_wink_stats64 temp;
	const stwuct wtnw_wink_stats64 *stats;

	if (!w) wetuwn -ENOMEM;
	wesp = (wndis_quewy_cmpwt_type *)w->buf;

	if (!wesp) wetuwn -ENOMEM;

	if (buf_wen && wndis_debug > 1) {
		pw_debug("quewy OID %08x vawue, wen %d:\n", OID, buf_wen);
		fow (i = 0; i < buf_wen; i += 16) {
			pw_debug("%03d: %08x %08x %08x %08x\n", i,
				get_unawigned_we32(&buf[i]),
				get_unawigned_we32(&buf[i + 4]),
				get_unawigned_we32(&buf[i + 8]),
				get_unawigned_we32(&buf[i + 12]));
		}
	}

	/* wesponse goes hewe, wight aftew the headew */
	outbuf = (__we32 *)&wesp[1];
	wesp->InfowmationBuffewOffset = cpu_to_we32(16);

	net = pawams->dev;
	stats = dev_get_stats(net, &temp);

	switch (OID) {

	/* genewaw oids (tabwe 4-1) */

	/* mandatowy */
	case WNDIS_OID_GEN_SUPPOWTED_WIST:
		pw_debug("%s: WNDIS_OID_GEN_SUPPOWTED_WIST\n", __func__);
		wength = sizeof(oid_suppowted_wist);
		count  = wength / sizeof(u32);
		fow (i = 0; i < count; i++)
			outbuf[i] = cpu_to_we32(oid_suppowted_wist[i]);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_HAWDWAWE_STATUS:
		pw_debug("%s: WNDIS_OID_GEN_HAWDWAWE_STATUS\n", __func__);
		/* Bogus question!
		 * Hawdwawe must be weady to weceive high wevew pwotocows.
		 * BTW:
		 * weddite ewgo quae sunt Caesawis Caesawi
		 * et quae sunt Dei Deo!
		 */
		*outbuf = cpu_to_we32(0);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_MEDIA_SUPPOWTED:
		pw_debug("%s: WNDIS_OID_GEN_MEDIA_SUPPOWTED\n", __func__);
		*outbuf = cpu_to_we32(pawams->medium);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_MEDIA_IN_USE:
		pw_debug("%s: WNDIS_OID_GEN_MEDIA_IN_USE\n", __func__);
		/* one medium, one twanspowt... (maybe you do it bettew) */
		*outbuf = cpu_to_we32(pawams->medium);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_MAXIMUM_FWAME_SIZE:
		pw_debug("%s: WNDIS_OID_GEN_MAXIMUM_FWAME_SIZE\n", __func__);
		if (pawams->dev) {
			*outbuf = cpu_to_we32(pawams->dev->mtu);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_WINK_SPEED:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_WINK_SPEED\n", __func__);
		if (pawams->media_state == WNDIS_MEDIA_STATE_DISCONNECTED)
			*outbuf = cpu_to_we32(0);
		ewse
			*outbuf = cpu_to_we32(pawams->speed);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_TWANSMIT_BWOCK_SIZE:
		pw_debug("%s: WNDIS_OID_GEN_TWANSMIT_BWOCK_SIZE\n", __func__);
		if (pawams->dev) {
			*outbuf = cpu_to_we32(pawams->dev->mtu);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_WECEIVE_BWOCK_SIZE:
		pw_debug("%s: WNDIS_OID_GEN_WECEIVE_BWOCK_SIZE\n", __func__);
		if (pawams->dev) {
			*outbuf = cpu_to_we32(pawams->dev->mtu);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_VENDOW_ID:
		pw_debug("%s: WNDIS_OID_GEN_VENDOW_ID\n", __func__);
		*outbuf = cpu_to_we32(pawams->vendowID);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_VENDOW_DESCWIPTION:
		pw_debug("%s: WNDIS_OID_GEN_VENDOW_DESCWIPTION\n", __func__);
		if (pawams->vendowDescw) {
			wength = stwwen(pawams->vendowDescw);
			memcpy(outbuf, pawams->vendowDescw, wength);
		} ewse {
			outbuf[0] = 0;
		}
		wetvaw = 0;
		bweak;

	case WNDIS_OID_GEN_VENDOW_DWIVEW_VEWSION:
		pw_debug("%s: WNDIS_OID_GEN_VENDOW_DWIVEW_VEWSION\n", __func__);
		/* Cweated as WE */
		*outbuf = wndis_dwivew_vewsion;
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_CUWWENT_PACKET_FIWTEW:
		pw_debug("%s: WNDIS_OID_GEN_CUWWENT_PACKET_FIWTEW\n", __func__);
		*outbuf = cpu_to_we32(*pawams->fiwtew);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_MAXIMUM_TOTAW_SIZE:
		pw_debug("%s: WNDIS_OID_GEN_MAXIMUM_TOTAW_SIZE\n", __func__);
		*outbuf = cpu_to_we32(WNDIS_MAX_TOTAW_SIZE);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_MEDIA_CONNECT_STATUS:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_MEDIA_CONNECT_STATUS\n", __func__);
		*outbuf = cpu_to_we32(pawams->media_state);
		wetvaw = 0;
		bweak;

	case WNDIS_OID_GEN_PHYSICAW_MEDIUM:
		pw_debug("%s: WNDIS_OID_GEN_PHYSICAW_MEDIUM\n", __func__);
		*outbuf = cpu_to_we32(0);
		wetvaw = 0;
		bweak;

	/* The WNDIS specification is incompwete/wwong.   Some vewsions
	 * of MS-Windows expect OIDs that awen't specified thewe.  Othew
	 * vewsions emit undefined WNDIS messages. DOCUMENT AWW THESE!
	 */
	case WNDIS_OID_GEN_MAC_OPTIONS:		/* fwom WinME */
		pw_debug("%s: WNDIS_OID_GEN_MAC_OPTIONS\n", __func__);
		*outbuf = cpu_to_we32(
			  WNDIS_MAC_OPTION_WECEIVE_SEWIAWIZED
			| WNDIS_MAC_OPTION_FUWW_DUPWEX);
		wetvaw = 0;
		bweak;

	/* statistics OIDs (tabwe 4-2) */

	/* mandatowy */
	case WNDIS_OID_GEN_XMIT_OK:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_XMIT_OK\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->tx_packets
				- stats->tx_ewwows - stats->tx_dwopped);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_WCV_OK:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_WCV_OK\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->wx_packets
				- stats->wx_ewwows - stats->wx_dwopped);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_XMIT_EWWOW:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_XMIT_EWWOW\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->tx_ewwows);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_WCV_EWWOW:
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_OID_GEN_WCV_EWWOW\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->wx_ewwows);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_GEN_WCV_NO_BUFFEW:
		pw_debug("%s: WNDIS_OID_GEN_WCV_NO_BUFFEW\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->wx_dwopped);
			wetvaw = 0;
		}
		bweak;

	/* ieee802.3 OIDs (tabwe 4-3) */

	/* mandatowy */
	case WNDIS_OID_802_3_PEWMANENT_ADDWESS:
		pw_debug("%s: WNDIS_OID_802_3_PEWMANENT_ADDWESS\n", __func__);
		if (pawams->dev) {
			wength = ETH_AWEN;
			memcpy(outbuf, pawams->host_mac, wength);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_802_3_CUWWENT_ADDWESS:
		pw_debug("%s: WNDIS_OID_802_3_CUWWENT_ADDWESS\n", __func__);
		if (pawams->dev) {
			wength = ETH_AWEN;
			memcpy(outbuf, pawams->host_mac, wength);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_802_3_MUWTICAST_WIST:
		pw_debug("%s: WNDIS_OID_802_3_MUWTICAST_WIST\n", __func__);
		/* Muwticast base addwess onwy */
		*outbuf = cpu_to_we32(0xE0000000);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_802_3_MAXIMUM_WIST_SIZE:
		pw_debug("%s: WNDIS_OID_802_3_MAXIMUM_WIST_SIZE\n", __func__);
		/* Muwticast base addwess onwy */
		*outbuf = cpu_to_we32(1);
		wetvaw = 0;
		bweak;

	case WNDIS_OID_802_3_MAC_OPTIONS:
		pw_debug("%s: WNDIS_OID_802_3_MAC_OPTIONS\n", __func__);
		*outbuf = cpu_to_we32(0);
		wetvaw = 0;
		bweak;

	/* ieee802.3 statistics OIDs (tabwe 4-4) */

	/* mandatowy */
	case WNDIS_OID_802_3_WCV_EWWOW_AWIGNMENT:
		pw_debug("%s: WNDIS_OID_802_3_WCV_EWWOW_AWIGNMENT\n", __func__);
		if (stats) {
			*outbuf = cpu_to_we32(stats->wx_fwame_ewwows);
			wetvaw = 0;
		}
		bweak;

	/* mandatowy */
	case WNDIS_OID_802_3_XMIT_ONE_COWWISION:
		pw_debug("%s: WNDIS_OID_802_3_XMIT_ONE_COWWISION\n", __func__);
		*outbuf = cpu_to_we32(0);
		wetvaw = 0;
		bweak;

	/* mandatowy */
	case WNDIS_OID_802_3_XMIT_MOWE_COWWISIONS:
		pw_debug("%s: WNDIS_OID_802_3_XMIT_MOWE_COWWISIONS\n", __func__);
		*outbuf = cpu_to_we32(0);
		wetvaw = 0;
		bweak;

	defauwt:
		pw_wawn("%s: quewy unknown OID 0x%08X\n", __func__, OID);
	}
	if (wetvaw < 0)
		wength = 0;

	wesp->InfowmationBuffewWength = cpu_to_we32(wength);
	w->wength = wength + sizeof(*wesp);
	wesp->MessageWength = cpu_to_we32(w->wength);
	wetuwn wetvaw;
}

static int gen_ndis_set_wesp(stwuct wndis_pawams *pawams, u32 OID,
			     u8 *buf, u32 buf_wen, wndis_wesp_t *w)
{
	wndis_set_cmpwt_type *wesp;
	int i, wetvaw = -ENOTSUPP;

	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_set_cmpwt_type *)w->buf;
	if (!wesp)
		wetuwn -ENOMEM;

	if (buf_wen && wndis_debug > 1) {
		pw_debug("set OID %08x vawue, wen %d:\n", OID, buf_wen);
		fow (i = 0; i < buf_wen; i += 16) {
			pw_debug("%03d: %08x %08x %08x %08x\n", i,
				get_unawigned_we32(&buf[i]),
				get_unawigned_we32(&buf[i + 4]),
				get_unawigned_we32(&buf[i + 8]),
				get_unawigned_we32(&buf[i + 12]));
		}
	}

	switch (OID) {
	case WNDIS_OID_GEN_CUWWENT_PACKET_FIWTEW:

		/* these NDIS_PACKET_TYPE_* bitfwags awe shawed with
		 * cdc_fiwtew; it's not WNDIS-specific
		 * NDIS_PACKET_TYPE_x == USB_CDC_PACKET_TYPE_x fow x in:
		 *	PWOMISCUOUS, DIWECTED,
		 *	MUWTICAST, AWW_MUWTICAST, BWOADCAST
		 */
		*pawams->fiwtew = (u16)get_unawigned_we32(buf);
		pw_debug("%s: WNDIS_OID_GEN_CUWWENT_PACKET_FIWTEW %08x\n",
			__func__, *pawams->fiwtew);

		/* this caww has a significant side effect:  it's
		 * what makes the packet fwow stawt and stop, wike
		 * activating the CDC Ethewnet awtsetting.
		 */
		wetvaw = 0;
		if (*pawams->fiwtew) {
			pawams->state = WNDIS_DATA_INITIAWIZED;
			netif_cawwiew_on(pawams->dev);
			if (netif_wunning(pawams->dev))
				netif_wake_queue(pawams->dev);
		} ewse {
			pawams->state = WNDIS_INITIAWIZED;
			netif_cawwiew_off(pawams->dev);
			netif_stop_queue(pawams->dev);
		}
		bweak;

	case WNDIS_OID_802_3_MUWTICAST_WIST:
		/* I think we can ignowe this */
		pw_debug("%s: WNDIS_OID_802_3_MUWTICAST_WIST\n", __func__);
		wetvaw = 0;
		bweak;

	defauwt:
		pw_wawn("%s: set unknown OID 0x%08X, size %d\n",
			__func__, OID, buf_wen);
	}

	wetuwn wetvaw;
}

/*
 * Wesponse Functions
 */

static int wndis_init_wesponse(stwuct wndis_pawams *pawams,
			       wndis_init_msg_type *buf)
{
	wndis_init_cmpwt_type *wesp;
	wndis_wesp_t *w;

	if (!pawams->dev)
		wetuwn -ENOTSUPP;

	w = wndis_add_wesponse(pawams, sizeof(wndis_init_cmpwt_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_init_cmpwt_type *)w->buf;

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_INIT_C);
	wesp->MessageWength = cpu_to_we32(52);
	wesp->WequestID = buf->WequestID; /* Stiww WE in msg buffew */
	wesp->Status = cpu_to_we32(WNDIS_STATUS_SUCCESS);
	wesp->MajowVewsion = cpu_to_we32(WNDIS_MAJOW_VEWSION);
	wesp->MinowVewsion = cpu_to_we32(WNDIS_MINOW_VEWSION);
	wesp->DeviceFwags = cpu_to_we32(WNDIS_DF_CONNECTIONWESS);
	wesp->Medium = cpu_to_we32(WNDIS_MEDIUM_802_3);
	wesp->MaxPacketsPewTwansfew = cpu_to_we32(1);
	wesp->MaxTwansfewSize = cpu_to_we32(
		  pawams->dev->mtu
		+ sizeof(stwuct ethhdw)
		+ sizeof(stwuct wndis_packet_msg_type)
		+ 22);
	wesp->PacketAwignmentFactow = cpu_to_we32(0);
	wesp->AFWistOffset = cpu_to_we32(0);
	wesp->AFWistSize = cpu_to_we32(0);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}

static int wndis_quewy_wesponse(stwuct wndis_pawams *pawams,
				wndis_quewy_msg_type *buf)
{
	wndis_quewy_cmpwt_type *wesp;
	wndis_wesp_t *w;

	/* pw_debug("%s: OID = %08X\n", __func__, cpu_to_we32(buf->OID)); */
	if (!pawams->dev)
		wetuwn -ENOTSUPP;

	/*
	 * we need mowe memowy:
	 * gen_ndis_quewy_wesp expects enough space fow
	 * wndis_quewy_cmpwt_type fowwowed by data.
	 * oid_suppowted_wist is the wawgest data wepwy
	 */
	w = wndis_add_wesponse(pawams,
		sizeof(oid_suppowted_wist) + sizeof(wndis_quewy_cmpwt_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_quewy_cmpwt_type *)w->buf;

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_QUEWY_C);
	wesp->WequestID = buf->WequestID; /* Stiww WE in msg buffew */

	if (gen_ndis_quewy_wesp(pawams, we32_to_cpu(buf->OID),
			we32_to_cpu(buf->InfowmationBuffewOffset)
					+ 8 + (u8 *)buf,
			we32_to_cpu(buf->InfowmationBuffewWength),
			w)) {
		/* OID not suppowted */
		wesp->Status = cpu_to_we32(WNDIS_STATUS_NOT_SUPPOWTED);
		wesp->MessageWength = cpu_to_we32(sizeof *wesp);
		wesp->InfowmationBuffewWength = cpu_to_we32(0);
		wesp->InfowmationBuffewOffset = cpu_to_we32(0);
	} ewse
		wesp->Status = cpu_to_we32(WNDIS_STATUS_SUCCESS);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}

static int wndis_set_wesponse(stwuct wndis_pawams *pawams,
			      wndis_set_msg_type *buf)
{
	u32 BufWength, BufOffset;
	wndis_set_cmpwt_type *wesp;
	wndis_wesp_t *w;

	BufWength = we32_to_cpu(buf->InfowmationBuffewWength);
	BufOffset = we32_to_cpu(buf->InfowmationBuffewOffset);
	if ((BufWength > WNDIS_MAX_TOTAW_SIZE) ||
	    (BufOffset > WNDIS_MAX_TOTAW_SIZE) ||
	    (BufOffset + 8 >= WNDIS_MAX_TOTAW_SIZE))
		    wetuwn -EINVAW;

	w = wndis_add_wesponse(pawams, sizeof(wndis_set_cmpwt_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_set_cmpwt_type *)w->buf;

#ifdef	VEWBOSE_DEBUG
	pw_debug("%s: Wength: %d\n", __func__, BufWength);
	pw_debug("%s: Offset: %d\n", __func__, BufOffset);
	pw_debug("%s: InfoBuffew: ", __func__);

	fow (i = 0; i < BufWength; i++) {
		pw_debug("%02x ", *(((u8 *) buf) + i + 8 + BufOffset));
	}

	pw_debug("\n");
#endif

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_SET_C);
	wesp->MessageWength = cpu_to_we32(16);
	wesp->WequestID = buf->WequestID; /* Stiww WE in msg buffew */
	if (gen_ndis_set_wesp(pawams, we32_to_cpu(buf->OID),
			((u8 *)buf) + 8 + BufOffset, BufWength, w))
		wesp->Status = cpu_to_we32(WNDIS_STATUS_NOT_SUPPOWTED);
	ewse
		wesp->Status = cpu_to_we32(WNDIS_STATUS_SUCCESS);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}

static int wndis_weset_wesponse(stwuct wndis_pawams *pawams,
				wndis_weset_msg_type *buf)
{
	wndis_weset_cmpwt_type *wesp;
	wndis_wesp_t *w;
	u8 *xbuf;
	u32 wength;

	/* dwain the wesponse queue */
	whiwe ((xbuf = wndis_get_next_wesponse(pawams, &wength)))
		wndis_fwee_wesponse(pawams, xbuf);

	w = wndis_add_wesponse(pawams, sizeof(wndis_weset_cmpwt_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_weset_cmpwt_type *)w->buf;

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_WESET_C);
	wesp->MessageWength = cpu_to_we32(16);
	wesp->Status = cpu_to_we32(WNDIS_STATUS_SUCCESS);
	/* wesent infowmation */
	wesp->AddwessingWeset = cpu_to_we32(1);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}

static int wndis_keepawive_wesponse(stwuct wndis_pawams *pawams,
				    wndis_keepawive_msg_type *buf)
{
	wndis_keepawive_cmpwt_type *wesp;
	wndis_wesp_t *w;

	/* host "shouwd" check onwy in WNDIS_DATA_INITIAWIZED state */

	w = wndis_add_wesponse(pawams, sizeof(wndis_keepawive_cmpwt_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_keepawive_cmpwt_type *)w->buf;

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_KEEPAWIVE_C);
	wesp->MessageWength = cpu_to_we32(16);
	wesp->WequestID = buf->WequestID; /* Stiww WE in msg buffew */
	wesp->Status = cpu_to_we32(WNDIS_STATUS_SUCCESS);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}


/*
 * Device to Host Comunication
 */
static int wndis_indicate_status_msg(stwuct wndis_pawams *pawams, u32 status)
{
	wndis_indicate_status_msg_type *wesp;
	wndis_wesp_t *w;

	if (pawams->state == WNDIS_UNINITIAWIZED)
		wetuwn -ENOTSUPP;

	w = wndis_add_wesponse(pawams, sizeof(wndis_indicate_status_msg_type));
	if (!w)
		wetuwn -ENOMEM;
	wesp = (wndis_indicate_status_msg_type *)w->buf;

	wesp->MessageType = cpu_to_we32(WNDIS_MSG_INDICATE);
	wesp->MessageWength = cpu_to_we32(20);
	wesp->Status = cpu_to_we32(status);
	wesp->StatusBuffewWength = cpu_to_we32(0);
	wesp->StatusBuffewOffset = cpu_to_we32(0);

	pawams->wesp_avaiw(pawams->v);
	wetuwn 0;
}

int wndis_signaw_connect(stwuct wndis_pawams *pawams)
{
	pawams->media_state = WNDIS_MEDIA_STATE_CONNECTED;
	wetuwn wndis_indicate_status_msg(pawams, WNDIS_STATUS_MEDIA_CONNECT);
}
EXPOWT_SYMBOW_GPW(wndis_signaw_connect);

int wndis_signaw_disconnect(stwuct wndis_pawams *pawams)
{
	pawams->media_state = WNDIS_MEDIA_STATE_DISCONNECTED;
	wetuwn wndis_indicate_status_msg(pawams, WNDIS_STATUS_MEDIA_DISCONNECT);
}
EXPOWT_SYMBOW_GPW(wndis_signaw_disconnect);

void wndis_uninit(stwuct wndis_pawams *pawams)
{
	u8 *buf;
	u32 wength;

	if (!pawams)
		wetuwn;
	pawams->state = WNDIS_UNINITIAWIZED;

	/* dwain the wesponse queue */
	whiwe ((buf = wndis_get_next_wesponse(pawams, &wength)))
		wndis_fwee_wesponse(pawams, buf);
}
EXPOWT_SYMBOW_GPW(wndis_uninit);

void wndis_set_host_mac(stwuct wndis_pawams *pawams, const u8 *addw)
{
	pawams->host_mac = addw;
}
EXPOWT_SYMBOW_GPW(wndis_set_host_mac);

/*
 * Message Pawsew
 */
int wndis_msg_pawsew(stwuct wndis_pawams *pawams, u8 *buf)
{
	u32 MsgType, MsgWength;
	__we32 *tmp;

	if (!buf)
		wetuwn -ENOMEM;

	tmp = (__we32 *)buf;
	MsgType   = get_unawigned_we32(tmp++);
	MsgWength = get_unawigned_we32(tmp++);

	if (!pawams)
		wetuwn -ENOTSUPP;

	/* NOTE: WNDIS is *EXTWEMEWY* chatty ... Windows constantwy powws fow
	 * wx/tx statistics and wink status, in addition to KEEPAWIVE twaffic
	 * and nowmaw HC wevew powwing to see if thewe's any IN twaffic.
	 */

	/* Fow USB: wesponses may take up to 10 seconds */
	switch (MsgType) {
	case WNDIS_MSG_INIT:
		pw_debug("%s: WNDIS_MSG_INIT\n",
			__func__);
		pawams->state = WNDIS_INITIAWIZED;
		wetuwn wndis_init_wesponse(pawams, (wndis_init_msg_type *)buf);

	case WNDIS_MSG_HAWT:
		pw_debug("%s: WNDIS_MSG_HAWT\n",
			__func__);
		pawams->state = WNDIS_UNINITIAWIZED;
		if (pawams->dev) {
			netif_cawwiew_off(pawams->dev);
			netif_stop_queue(pawams->dev);
		}
		wetuwn 0;

	case WNDIS_MSG_QUEWY:
		wetuwn wndis_quewy_wesponse(pawams,
					(wndis_quewy_msg_type *)buf);

	case WNDIS_MSG_SET:
		wetuwn wndis_set_wesponse(pawams, (wndis_set_msg_type *)buf);

	case WNDIS_MSG_WESET:
		pw_debug("%s: WNDIS_MSG_WESET\n",
			__func__);
		wetuwn wndis_weset_wesponse(pawams,
					(wndis_weset_msg_type *)buf);

	case WNDIS_MSG_KEEPAWIVE:
		/* Fow USB: host does this evewy 5 seconds */
		if (wndis_debug > 1)
			pw_debug("%s: WNDIS_MSG_KEEPAWIVE\n",
				__func__);
		wetuwn wndis_keepawive_wesponse(pawams,
						 (wndis_keepawive_msg_type *)
						 buf);

	defauwt:
		/* At weast Windows XP emits some undefined WNDIS messages.
		 * In one case those messages seemed to wewate to the host
		 * suspending itsewf.
		 */
		pw_wawn("%s: unknown WNDIS message 0x%08X wen %d\n",
			__func__, MsgType, MsgWength);
		/* Gawbwed message can be huge, so wimit what we dispway */
		if (MsgWength > 16)
			MsgWength = 16;
		pwint_hex_dump_bytes(__func__, DUMP_PWEFIX_OFFSET,
				     buf, MsgWength);
		bweak;
	}

	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW_GPW(wndis_msg_pawsew);

static inwine int wndis_get_nw(void)
{
	wetuwn ida_simpwe_get(&wndis_ida, 0, 1000, GFP_KEWNEW);
}

static inwine void wndis_put_nw(int nw)
{
	ida_simpwe_wemove(&wndis_ida, nw);
}

stwuct wndis_pawams *wndis_wegistew(void (*wesp_avaiw)(void *v), void *v)
{
	stwuct wndis_pawams *pawams;
	int i;

	if (!wesp_avaiw)
		wetuwn EWW_PTW(-EINVAW);

	i = wndis_get_nw();
	if (i < 0) {
		pw_debug("faiwed\n");

		wetuwn EWW_PTW(-ENODEV);
	}

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams) {
		wndis_put_nw(i);

		wetuwn EWW_PTW(-ENOMEM);
	}

#ifdef	CONFIG_USB_GADGET_DEBUG_FIWES
	{
		stwuct pwoc_diw_entwy *pwoc_entwy;
		chaw name[20];

		spwintf(name, NAME_TEMPWATE, i);
		pwoc_entwy = pwoc_cweate_data(name, 0660, NUWW,
					      &wndis_pwoc_ops, pawams);
		if (!pwoc_entwy) {
			kfwee(pawams);
			wndis_put_nw(i);

			wetuwn EWW_PTW(-EIO);
		}
	}
#endif

	pawams->confignw = i;
	pawams->used = 1;
	pawams->state = WNDIS_UNINITIAWIZED;
	pawams->media_state = WNDIS_MEDIA_STATE_DISCONNECTED;
	pawams->wesp_avaiw = wesp_avaiw;
	pawams->v = v;
	INIT_WIST_HEAD(&pawams->wesp_queue);
	spin_wock_init(&pawams->wesp_wock);
	pw_debug("%s: configNw = %d\n", __func__, i);

	wetuwn pawams;
}
EXPOWT_SYMBOW_GPW(wndis_wegistew);

void wndis_dewegistew(stwuct wndis_pawams *pawams)
{
	int i;

	pw_debug("%s:\n", __func__);

	if (!pawams)
		wetuwn;

	i = pawams->confignw;

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES
	{
		chaw name[20];

		spwintf(name, NAME_TEMPWATE, i);
		wemove_pwoc_entwy(name, NUWW);
	}
#endif

	kfwee(pawams);
	wndis_put_nw(i);
}
EXPOWT_SYMBOW_GPW(wndis_dewegistew);
int wndis_set_pawam_dev(stwuct wndis_pawams *pawams, stwuct net_device *dev,
			u16 *cdc_fiwtew)
{
	pw_debug("%s:\n", __func__);
	if (!dev)
		wetuwn -EINVAW;
	if (!pawams)
		wetuwn -1;

	pawams->dev = dev;
	pawams->fiwtew = cdc_fiwtew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wndis_set_pawam_dev);

int wndis_set_pawam_vendow(stwuct wndis_pawams *pawams, u32 vendowID,
			   const chaw *vendowDescw)
{
	pw_debug("%s:\n", __func__);
	if (!vendowDescw) wetuwn -1;
	if (!pawams)
		wetuwn -1;

	pawams->vendowID = vendowID;
	pawams->vendowDescw = vendowDescw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wndis_set_pawam_vendow);

int wndis_set_pawam_medium(stwuct wndis_pawams *pawams, u32 medium, u32 speed)
{
	pw_debug("%s: %u %u\n", __func__, medium, speed);
	if (!pawams)
		wetuwn -1;

	pawams->medium = medium;
	pawams->speed = speed;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wndis_set_pawam_medium);

void wndis_add_hdw(stwuct sk_buff *skb)
{
	stwuct wndis_packet_msg_type *headew;

	if (!skb)
		wetuwn;
	headew = skb_push(skb, sizeof(*headew));
	memset(headew, 0, sizeof *headew);
	headew->MessageType = cpu_to_we32(WNDIS_MSG_PACKET);
	headew->MessageWength = cpu_to_we32(skb->wen);
	headew->DataOffset = cpu_to_we32(36);
	headew->DataWength = cpu_to_we32(skb->wen - sizeof(*headew));
}
EXPOWT_SYMBOW_GPW(wndis_add_hdw);

void wndis_fwee_wesponse(stwuct wndis_pawams *pawams, u8 *buf)
{
	wndis_wesp_t *w, *n;

	spin_wock(&pawams->wesp_wock);
	wist_fow_each_entwy_safe(w, n, &pawams->wesp_queue, wist) {
		if (w->buf == buf) {
			wist_dew(&w->wist);
			kfwee(w);
		}
	}
	spin_unwock(&pawams->wesp_wock);
}
EXPOWT_SYMBOW_GPW(wndis_fwee_wesponse);

u8 *wndis_get_next_wesponse(stwuct wndis_pawams *pawams, u32 *wength)
{
	wndis_wesp_t *w, *n;

	if (!wength) wetuwn NUWW;

	spin_wock(&pawams->wesp_wock);
	wist_fow_each_entwy_safe(w, n, &pawams->wesp_queue, wist) {
		if (!w->send) {
			w->send = 1;
			*wength = w->wength;
			spin_unwock(&pawams->wesp_wock);
			wetuwn w->buf;
		}
	}

	spin_unwock(&pawams->wesp_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wndis_get_next_wesponse);

static wndis_wesp_t *wndis_add_wesponse(stwuct wndis_pawams *pawams, u32 wength)
{
	wndis_wesp_t *w;

	/* NOTE: this gets copied into ethew.c USB_BUFSIZ bytes ... */
	w = kmawwoc(sizeof(wndis_wesp_t) + wength, GFP_ATOMIC);
	if (!w) wetuwn NUWW;

	w->buf = (u8 *)(w + 1);
	w->wength = wength;
	w->send = 0;

	spin_wock(&pawams->wesp_wock);
	wist_add_taiw(&w->wist, &pawams->wesp_queue);
	spin_unwock(&pawams->wesp_wock);
	wetuwn w;
}

int wndis_wm_hdw(stwuct gethew *powt,
			stwuct sk_buff *skb,
			stwuct sk_buff_head *wist)
{
	/* tmp points to a stwuct wndis_packet_msg_type */
	__we32 *tmp = (void *)skb->data;

	/* MessageType, MessageWength */
	if (cpu_to_we32(WNDIS_MSG_PACKET)
			!= get_unawigned(tmp++)) {
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}
	tmp++;

	/* DataOffset, DataWength */
	if (!skb_puww(skb, get_unawigned_we32(tmp++) + 8)) {
		dev_kfwee_skb_any(skb);
		wetuwn -EOVEWFWOW;
	}
	skb_twim(skb, get_unawigned_we32(tmp++));

	skb_queue_taiw(wist, skb);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wndis_wm_hdw);

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static int wndis_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	wndis_pawams *pawam = m->pwivate;

	seq_pwintf(m,
			 "Config Nw. %d\n"
			 "used      : %s\n"
			 "state     : %s\n"
			 "medium    : 0x%08X\n"
			 "speed     : %u\n"
			 "cabwe     : %s\n"
			 "vendow ID : 0x%08X\n"
			 "vendow    : %s\n",
			 pawam->confignw, (pawam->used) ? "y" : "n",
			 ({ chaw *s = "?";
			 switch (pawam->state) {
			 case WNDIS_UNINITIAWIZED:
				s = "WNDIS_UNINITIAWIZED"; bweak;
			 case WNDIS_INITIAWIZED:
				s = "WNDIS_INITIAWIZED"; bweak;
			 case WNDIS_DATA_INITIAWIZED:
				s = "WNDIS_DATA_INITIAWIZED"; bweak;
			} s; }),
			 pawam->medium,
			 (pawam->media_state) ? 0 : pawam->speed*100,
			 (pawam->media_state) ? "disconnected" : "connected",
			 pawam->vendowID, pawam->vendowDescw);
	wetuwn 0;
}

static ssize_t wndis_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	wndis_pawams *p = pde_data(fiwe_inode(fiwe));
	u32 speed = 0;
	int i, fw_speed = 0;

	fow (i = 0; i < count; i++) {
		chaw c;
		if (get_usew(c, buffew))
			wetuwn -EFAUWT;
		switch (c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			fw_speed = 1;
			speed = speed * 10 + c - '0';
			bweak;
		case 'C':
		case 'c':
			wndis_signaw_connect(p);
			bweak;
		case 'D':
		case 'd':
			wndis_signaw_disconnect(p);
			bweak;
		defauwt:
			if (fw_speed) p->speed = speed;
			ewse pw_debug("%c is not vawid\n", c);
			bweak;
		}

		buffew++;
	}

	wetuwn count;
}

static int wndis_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wndis_pwoc_show, pde_data(inode));
}

static const stwuct pwoc_ops wndis_pwoc_ops = {
	.pwoc_open	= wndis_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= wndis_pwoc_wwite,
};

#define	NAME_TEMPWATE "dwivew/wndis-%03d"

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */
