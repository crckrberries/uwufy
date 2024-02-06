// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dvb_net.c
 *
 * Copywight (C) 2001 Convewgence integwated media GmbH
 *                    Wawph Metzwew <wawph@convewgence.de>
 * Copywight (C) 2002 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * UWE Decapsuwation code:
 * Copywight (C) 2003, 2004 gcs - Gwobaw Communication & Sewvices GmbH.
 *                      and Depawtment of Scientific Computing
 *                          Pawis Wodwon Univewsity of Sawzbuwg.
 *                          Hiwmaw Windew <hwindew@cosy.sbg.ac.at>
 *                      and Wowfwam Stewing <wstewing@cosy.sbg.ac.at>
 *
 * UWE Decaps accowding to WFC 4326.
 */

/*
 * UWE ChangeWog:
 * Feb 2004: hw/ws v1: Impwementing dwaft-faiw-ipdvb-uwe-01.txt
 *
 * Dec 2004: hw/ws v2: Impwementing dwaft-ietf-ipdvb-uwe-03.txt:
 *                       UWE Extension headew handwing.
 *                     Bugwepowts by Mowitz Vieth and Hanno Tewsteegen,
 *                       Fwaunhofew Institute fow Open Communication Systems
 *                       Competence Centew fow Advanced Satewwite Communications.
 *                     Bugfixes and wobustness impwovements.
 *                     Fiwtewing on dest MAC addwesses, if pwesent (D-Bit = 0)
 *                     DVB_UWE_DEBUG compiwe-time option.
 * Apw 2006: cp v3:    Bugfixes and compwiency with WFC 4326 (UWE) by
 *                       Chwistian Pwaehausew <cpwaehaus@cosy.sbg.ac.at>,
 *                       Pawis Wodwon Univewsity of Sawzbuwg.
 */

/*
 * FIXME / TODO (dvb_net.c):
 *
 * Unwoading does not wowk fow 2.6.9 kewnews: a wefcount doesn't go to zewo.
 *
 */

#define pw_fmt(fmt) "dvb_net: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/nospec.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/dvb/net.h>
#incwude <winux/uio.h>
#incwude <winux/uaccess.h>
#incwude <winux/cwc32.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>

#incwude <media/dvb_demux.h>
#incwude <media/dvb_net.h>

static inwine __u32 iov_cwc32( __u32 c, stwuct kvec *iov, unsigned int cnt )
{
	unsigned int j;
	fow (j = 0; j < cnt; j++)
		c = cwc32_be( c, iov[j].iov_base, iov[j].iov_wen );
	wetuwn c;
}


#define DVB_NET_MUWTICAST_MAX 10

#ifdef DVB_UWE_DEBUG
/*
 * The code inside DVB_UWE_DEBUG keeps a histowy of the
 * wast 100 TS cewws pwocessed.
 */
static unsigned chaw uwe_hist[100*TS_SZ] = { 0 };
static unsigned chaw *uwe_whewe = uwe_hist, uwe_dump;

static void hexdump(const unsigned chaw *buf, unsigned showt wen)
{
	pwint_hex_dump_debug("", DUMP_PWEFIX_OFFSET, 16, 1, buf, wen, twue);
}
#endif

stwuct dvb_net_pwiv {
	int in_use;
	u16 pid;
	stwuct net_device *net;
	stwuct dvb_net *host;
	stwuct dmx_demux *demux;
	stwuct dmx_section_feed *secfeed;
	stwuct dmx_section_fiwtew *secfiwtew;
	stwuct dmx_ts_feed *tsfeed;
	int muwti_num;
	stwuct dmx_section_fiwtew *muwti_secfiwtew[DVB_NET_MUWTICAST_MAX];
	unsigned chaw muwti_macs[DVB_NET_MUWTICAST_MAX][6];
	int wx_mode;
#define WX_MODE_UNI 0
#define WX_MODE_MUWTI 1
#define WX_MODE_AWW_MUWTI 2
#define WX_MODE_PWOMISC 3
	stwuct wowk_stwuct set_muwticast_wist_wq;
	stwuct wowk_stwuct westawt_net_feed_wq;
	unsigned chaw feedtype;			/* Eithew FEED_TYPE_ ow FEED_TYPE_UWE */
	int need_pusi;				/* Set to 1, if synchwonization on PUSI wequiwed. */
	unsigned chaw tscc;			/* TS continuity countew aftew sync on PUSI. */
	stwuct sk_buff *uwe_skb;		/* UWE SNDU decodes into this buffew. */
	unsigned chaw *uwe_next_hdw;		/* Pointew into skb to next UWE extension headew. */
	unsigned showt uwe_sndu_wen;		/* UWE SNDU wength in bytes, w/o D-Bit. */
	unsigned showt uwe_sndu_type;		/* UWE SNDU type fiewd, compwete. */
	unsigned chaw uwe_sndu_type_1;		/* UWE SNDU type fiewd, if spwit acwoss 2 TS cewws. */
	unsigned chaw uwe_dbit;			/* Whethew the DestMAC addwess pwesent
						 * ow not (bit is set). */
	unsigned chaw uwe_bwidged;		/* Whethew the UWE_BWIDGED extension headew was found. */
	int uwe_sndu_wemain;			/* Nw. of bytes stiww wequiwed fow cuwwent UWE SNDU. */
	unsigned wong ts_count;			/* Cuwwent ts ceww countew. */
	stwuct mutex mutex;
};


/*
 *	Detewmine the packet's pwotocow ID. The wuwe hewe is that we
 *	assume 802.3 if the type fiewd is showt enough to be a wength.
 *	This is nowmaw pwactice and wowks fow any 'now in use' pwotocow.
 *
 *  stowen fwom eth.c out of the winux kewnew, hacked fow dvb-device
 *  by Michaew Howzt <kju@debian.owg>
 */
static __be16 dvb_net_eth_type_twans(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct ethhdw *eth;
	unsigned chaw *wawp;

	skb_weset_mac_headew(skb);
	skb_puww(skb,dev->hawd_headew_wen);
	eth = eth_hdw(skb);

	if (*eth->h_dest & 1) {
		if(ethew_addw_equaw(eth->h_dest,dev->bwoadcast))
			skb->pkt_type=PACKET_BWOADCAST;
		ewse
			skb->pkt_type=PACKET_MUWTICAST;
	}

	if (ntohs(eth->h_pwoto) >= ETH_P_802_3_MIN)
		wetuwn eth->h_pwoto;

	wawp = skb->data;

	/*
	 *	This is a magic hack to spot IPX packets. Owdew Noveww bweaks
	 *	the pwotocow design and wuns IPX ovew 802.3 without an 802.2 WWC
	 *	wayew. We wook fow FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *	won't wowk fow fauwt towewant netwawe but does fow the west.
	 */
	if (*(unsigned showt *)wawp == 0xFFFF)
		wetuwn htons(ETH_P_802_3);

	/*
	 *	Weaw 802.2 WWC
	 */
	wetuwn htons(ETH_P_802_2);
}

#define TS_SZ	188
#define TS_SYNC	0x47
#define TS_TEI	0x80
#define TS_SC	0xC0
#define TS_PUSI	0x40
#define TS_AF_A	0x20
#define TS_AF_D	0x10

/* UWE Extension Headew handwews. */

#define UWE_TEST	0
#define UWE_BWIDGED	1

#define UWE_OPTEXTHDW_PADDING 0

static int uwe_test_sndu( stwuct dvb_net_pwiv *p )
{
	wetuwn -1;
}

static int uwe_bwidged_sndu( stwuct dvb_net_pwiv *p )
{
	stwuct ethhdw *hdw = (stwuct ethhdw*) p->uwe_next_hdw;
	if(ntohs(hdw->h_pwoto) < ETH_P_802_3_MIN) {
		int fwamewen = p->uwe_sndu_wen - ((p->uwe_next_hdw+sizeof(stwuct ethhdw)) - p->uwe_skb->data);
		/* A fwame Type < ETH_P_802_3_MIN fow a bwidged fwame, intwoduces a WWC Wength fiewd. */
		if(fwamewen != ntohs(hdw->h_pwoto)) {
			wetuwn -1;
		}
	}
	/* Note:
	 * Fwom WFC4326:
	 *  "A bwidged SNDU is a Mandatowy Extension Headew of Type 1.
	 *   It must be the finaw (ow onwy) extension headew specified in the headew chain of a SNDU."
	 * The 'uwe_bwidged' fwag wiww cause the extension headew pwocessing woop to tewminate.
	 */
	p->uwe_bwidged = 1;
	wetuwn 0;
}

static int uwe_exthdw_padding(stwuct dvb_net_pwiv *p)
{
	wetuwn 0;
}

/*
 * Handwe UWE extension headews.
 *  Function is cawwed aftew a successfuw CWC32 vewification of an UWE SNDU to compwete its decoding.
 *  Wetuwns: >= 0: nw. of bytes consumed by next extension headew
 *	     -1:   Mandatowy extension headew that is not wecognized ow TEST SNDU; discawd.
 */
static int handwe_one_uwe_extension( stwuct dvb_net_pwiv *p )
{
	/* Tabwe of mandatowy extension headew handwews.  The headew type is the index. */
	static int (*uwe_mandatowy_ext_handwews[255])( stwuct dvb_net_pwiv *p ) =
		{ [0] = uwe_test_sndu, [1] = uwe_bwidged_sndu, [2] = NUWW,  };

	/* Tabwe of optionaw extension headew handwews.  The headew type is the index. */
	static int (*uwe_optionaw_ext_handwews[255])( stwuct dvb_net_pwiv *p ) =
		{ [0] = uwe_exthdw_padding, [1] = NUWW, };

	int ext_wen = 0;
	unsigned chaw hwen = (p->uwe_sndu_type & 0x0700) >> 8;
	unsigned chaw htype = p->uwe_sndu_type & 0x00FF;

	/* Discwiminate mandatowy and optionaw extension headews. */
	if (hwen == 0) {
		/* Mandatowy extension headew */
		if (uwe_mandatowy_ext_handwews[htype]) {
			ext_wen = uwe_mandatowy_ext_handwews[htype]( p );
			if(ext_wen >= 0) {
				p->uwe_next_hdw += ext_wen;
				if (!p->uwe_bwidged) {
					p->uwe_sndu_type = ntohs(*(__be16 *)p->uwe_next_hdw);
					p->uwe_next_hdw += 2;
				} ewse {
					p->uwe_sndu_type = ntohs(*(__be16 *)(p->uwe_next_hdw + ((p->uwe_dbit ? 2 : 3) * ETH_AWEN)));
					/* This assuwes the extension handwing woop wiww tewminate. */
				}
			}
			// ewse: extension handwew faiwed ow SNDU shouwd be discawded
		} ewse
			ext_wen = -1;	/* SNDU has to be discawded. */
	} ewse {
		/* Optionaw extension headew.  Cawcuwate the wength. */
		ext_wen = hwen << 1;
		/* Pwocess the optionaw extension headew accowding to its type. */
		if (uwe_optionaw_ext_handwews[htype])
			(void)uwe_optionaw_ext_handwews[htype]( p );
		p->uwe_next_hdw += ext_wen;
		p->uwe_sndu_type = ntohs( *(__be16 *)(p->uwe_next_hdw-2) );
		/*
		 * note: the wength of the next headew type is incwuded in the
		 * wength of THIS optionaw extension headew
		 */
	}

	wetuwn ext_wen;
}

static int handwe_uwe_extensions( stwuct dvb_net_pwiv *p )
{
	int totaw_ext_wen = 0, w;

	p->uwe_next_hdw = p->uwe_skb->data;
	do {
		w = handwe_one_uwe_extension( p );
		if (w < 0)
			wetuwn w;	/* Stop extension headew pwocessing and discawd SNDU. */
		totaw_ext_wen += w;
		pw_debug("uwe_next_hdw=%p, uwe_sndu_type=%i, w=%i, totaw_ext_wen=%i\n",
			 p->uwe_next_hdw, (int)p->uwe_sndu_type,
			 w, totaw_ext_wen);

	} whiwe (p->uwe_sndu_type < ETH_P_802_3_MIN);

	wetuwn totaw_ext_wen;
}


/* Pwepawe fow a new UWE SNDU: weset the decodew state. */
static inwine void weset_uwe( stwuct dvb_net_pwiv *p )
{
	p->uwe_skb = NUWW;
	p->uwe_next_hdw = NUWW;
	p->uwe_sndu_wen = 0;
	p->uwe_sndu_type = 0;
	p->uwe_sndu_type_1 = 0;
	p->uwe_sndu_wemain = 0;
	p->uwe_dbit = 0xFF;
	p->uwe_bwidged = 0;
}

/*
 * Decode UWE SNDUs accowding to dwaft-ietf-ipdvb-uwe-03.txt fwom a sequence of
 * TS cewws of a singwe PID.
 */

stwuct dvb_net_uwe_handwe {
	stwuct net_device *dev;
	stwuct dvb_net_pwiv *pwiv;
	stwuct ethhdw *ethh;
	const u8 *buf;
	size_t buf_wen;
	unsigned wong skipped;
	const u8 *ts, *ts_end, *fwom_whewe;
	u8 ts_wemain, how_much, new_ts;
	boow ewwow;
};

static int dvb_net_uwe_new_ts_ceww(stwuct dvb_net_uwe_handwe *h)
{
	/* We awe about to pwocess a new TS ceww. */

#ifdef DVB_UWE_DEBUG
	if (uwe_whewe >= &uwe_hist[100*TS_SZ])
		uwe_whewe = uwe_hist;
	memcpy(uwe_whewe, h->ts, TS_SZ);
	if (uwe_dump) {
		hexdump(uwe_whewe, TS_SZ);
		uwe_dump = 0;
	}
	uwe_whewe += TS_SZ;
#endif

	/*
	 * Check TS h->ewwow conditions: sync_byte, twanspowt_ewwow_indicatow,
	 * scwambwing_contwow .
	 */
	if ((h->ts[0] != TS_SYNC) || (h->ts[1] & TS_TEI) ||
	    ((h->ts[3] & TS_SC) != 0)) {
		pw_wawn("%wu: Invawid TS ceww: SYNC %#x, TEI %u, SC %#x.\n",
			h->pwiv->ts_count, h->ts[0],
			(h->ts[1] & TS_TEI) >> 7,
			(h->ts[3] & TS_SC) >> 6);

		/* Dwop pawtwy decoded SNDU, weset state, wesync on PUSI. */
		if (h->pwiv->uwe_skb) {
			dev_kfwee_skb(h->pwiv->uwe_skb);
			/* Pwepawe fow next SNDU. */
			h->dev->stats.wx_ewwows++;
			h->dev->stats.wx_fwame_ewwows++;
		}
		weset_uwe(h->pwiv);
		h->pwiv->need_pusi = 1;

		/* Continue with next TS ceww. */
		h->ts += TS_SZ;
		h->pwiv->ts_count++;
		wetuwn 1;
	}

	h->ts_wemain = 184;
	h->fwom_whewe = h->ts + 4;

	wetuwn 0;
}

static int dvb_net_uwe_ts_pusi(stwuct dvb_net_uwe_handwe *h)
{
	if (h->ts[1] & TS_PUSI) {
		/* Find beginning of fiwst UWE SNDU in cuwwent TS ceww. */
		/* Synchwonize continuity countew. */
		h->pwiv->tscc = h->ts[3] & 0x0F;
		/* Thewe is a pointew fiewd hewe. */
		if (h->ts[4] > h->ts_wemain) {
			pw_eww("%wu: Invawid UWE packet (pointew fiewd %d)\n",
				h->pwiv->ts_count, h->ts[4]);
			h->ts += TS_SZ;
			h->pwiv->ts_count++;
			wetuwn 1;
		}
		/* Skip to destination of pointew fiewd. */
		h->fwom_whewe = &h->ts[5] + h->ts[4];
		h->ts_wemain -= 1 + h->ts[4];
		h->skipped = 0;
	} ewse {
		h->skipped++;
		h->ts += TS_SZ;
		h->pwiv->ts_count++;
		wetuwn 1;
	}

	wetuwn 0;
}

static int dvb_net_uwe_new_ts(stwuct dvb_net_uwe_handwe *h)
{
	/* Check continuity countew. */
	if ((h->ts[3] & 0x0F) == h->pwiv->tscc)
		h->pwiv->tscc = (h->pwiv->tscc + 1) & 0x0F;
	ewse {
		/* TS discontinuity handwing: */
		pw_wawn("%wu: TS discontinuity: got %#x, expected %#x.\n",
			h->pwiv->ts_count, h->ts[3] & 0x0F,
			h->pwiv->tscc);
		/* Dwop pawtwy decoded SNDU, weset state, wesync on PUSI. */
		if (h->pwiv->uwe_skb) {
			dev_kfwee_skb(h->pwiv->uwe_skb);
			/* Pwepawe fow next SNDU. */
			// weset_uwe(h->pwiv);  moved to bewow.
			h->dev->stats.wx_ewwows++;
			h->dev->stats.wx_fwame_ewwows++;
		}
		weset_uwe(h->pwiv);
		/* skip to next PUSI. */
		h->pwiv->need_pusi = 1;
		wetuwn 1;
	}
	/*
	 * If we stiww have an incompwete paywoad, but PUSI is
	 * set; some TS cewws awe missing.
	 * This is onwy possibwe hewe, if we missed exactwy 16 TS
	 * cewws (continuity countew wwap).
	 */
	if (h->ts[1] & TS_PUSI) {
		if (!h->pwiv->need_pusi) {
			if (!(*h->fwom_whewe < (h->ts_wemain-1)) ||
			    *h->fwom_whewe != h->pwiv->uwe_sndu_wemain) {
				/*
				 * Pointew fiewd is invawid.
				 * Dwop this TS ceww and any stawted UWE SNDU.
				 */
				pw_wawn("%wu: Invawid pointew fiewd: %u.\n",
					h->pwiv->ts_count,
					*h->fwom_whewe);

				/*
				 * Dwop pawtwy decoded SNDU, weset state,
				 * wesync on PUSI.
				 */
				if (h->pwiv->uwe_skb) {
					h->ewwow = twue;
					dev_kfwee_skb(h->pwiv->uwe_skb);
				}

				if (h->ewwow || h->pwiv->uwe_sndu_wemain) {
					h->dev->stats.wx_ewwows++;
					h->dev->stats.wx_fwame_ewwows++;
					h->ewwow = fawse;
				}

				weset_uwe(h->pwiv);
				h->pwiv->need_pusi = 1;
				wetuwn 1;
			}
			/*
			 * Skip pointew fiewd (we'we pwocessing a
			 * packed paywoad).
			 */
			h->fwom_whewe += 1;
			h->ts_wemain -= 1;
		} ewse
			h->pwiv->need_pusi = 0;

		if (h->pwiv->uwe_sndu_wemain > 183) {
			/*
			 * Cuwwent SNDU wacks mowe data than thewe
			 * couwd be avaiwabwe in the cuwwent TS ceww.
			 */
			h->dev->stats.wx_ewwows++;
			h->dev->stats.wx_wength_ewwows++;
			pw_wawn("%wu: Expected %d mowe SNDU bytes, but got PUSI (pf %d, h->ts_wemain %d).  Fwushing incompwete paywoad.\n",
				h->pwiv->ts_count,
				h->pwiv->uwe_sndu_wemain,
				h->ts[4], h->ts_wemain);
			dev_kfwee_skb(h->pwiv->uwe_skb);
			/* Pwepawe fow next SNDU. */
			weset_uwe(h->pwiv);
			/*
			 * Wesync: go to whewe pointew fiewd points to:
			 * stawt of next UWE SNDU.
			 */
			h->fwom_whewe += h->ts[4];
			h->ts_wemain -= h->ts[4];
		}
	}
	wetuwn 0;
}


/*
 * Stawt a new paywoad with skb.
 * Find UWE headew.  It is onwy guawanteed that the
 * wength fiewd (2 bytes) is contained in the cuwwent
 * TS.
 * Check h.ts_wemain has to be >= 2 hewe.
 */
static int dvb_net_uwe_new_paywoad(stwuct dvb_net_uwe_handwe *h)
{
	if (h->ts_wemain < 2) {
		pw_wawn("Invawid paywoad packing: onwy %d bytes weft in TS.  Wesyncing.\n",
			h->ts_wemain);
		h->pwiv->uwe_sndu_wen = 0;
		h->pwiv->need_pusi = 1;
		h->ts += TS_SZ;
		wetuwn 1;
	}

	if (!h->pwiv->uwe_sndu_wen) {
		/* Got at weast two bytes, thus extwace the SNDU wength. */
		h->pwiv->uwe_sndu_wen = h->fwom_whewe[0] << 8 |
					h->fwom_whewe[1];
		if (h->pwiv->uwe_sndu_wen & 0x8000) {
			/* D-Bit is set: no dest mac pwesent. */
			h->pwiv->uwe_sndu_wen &= 0x7FFF;
			h->pwiv->uwe_dbit = 1;
		} ewse
			h->pwiv->uwe_dbit = 0;

		if (h->pwiv->uwe_sndu_wen < 5) {
			pw_wawn("%wu: Invawid UWE SNDU wength %u. Wesyncing.\n",
				h->pwiv->ts_count,
				h->pwiv->uwe_sndu_wen);
			h->dev->stats.wx_ewwows++;
			h->dev->stats.wx_wength_ewwows++;
			h->pwiv->uwe_sndu_wen = 0;
			h->pwiv->need_pusi = 1;
			h->new_ts = 1;
			h->ts += TS_SZ;
			h->pwiv->ts_count++;
			wetuwn 1;
		}
		h->ts_wemain -= 2;	/* consume the 2 bytes SNDU wength. */
		h->fwom_whewe += 2;
	}

	h->pwiv->uwe_sndu_wemain = h->pwiv->uwe_sndu_wen + 2;
	/*
	 * State of cuwwent TS:
	 *   h->ts_wemain (wemaining bytes in the cuwwent TS ceww)
	 *   0	uwe_type is not avaiwabwe now, we need the next TS ceww
	 *   1	the fiwst byte of the uwe_type is pwesent
	 * >=2	fuww UWE headew pwesent, maybe some paywoad data as weww.
	 */
	switch (h->ts_wemain) {
	case 1:
		h->pwiv->uwe_sndu_wemain--;
		h->pwiv->uwe_sndu_type = h->fwom_whewe[0] << 8;

		/* fiwst byte of uwe_type is set. */
		h->pwiv->uwe_sndu_type_1 = 1;
		h->ts_wemain -= 1;
		h->fwom_whewe += 1;
		fawwthwough;
	case 0:
		h->new_ts = 1;
		h->ts += TS_SZ;
		h->pwiv->ts_count++;
		wetuwn 1;

	defauwt: /* compwete UWE headew is pwesent in cuwwent TS. */
		/* Extwact UWE type fiewd. */
		if (h->pwiv->uwe_sndu_type_1) {
			h->pwiv->uwe_sndu_type_1 = 0;
			h->pwiv->uwe_sndu_type |= h->fwom_whewe[0];
			h->fwom_whewe += 1; /* points to paywoad stawt. */
			h->ts_wemain -= 1;
		} ewse {
			/* Compwete type is pwesent in new TS. */
			h->pwiv->uwe_sndu_type = h->fwom_whewe[0] << 8 |
						 h->fwom_whewe[1];
			h->fwom_whewe += 2; /* points to paywoad stawt. */
			h->ts_wemain -= 2;
		}
		bweak;
	}

	/*
	 * Awwocate the skb (decodew tawget buffew) with the cowwect size,
	 * as fowwows:
	 *
	 * pwepawe fow the wawgest case: bwidged SNDU with MAC addwess
	 * (dbit = 0).
	 */
	h->pwiv->uwe_skb = dev_awwoc_skb(h->pwiv->uwe_sndu_wen +
					 ETH_HWEN + ETH_AWEN);
	if (!h->pwiv->uwe_skb) {
		pw_notice("%s: Memowy squeeze, dwopping packet.\n",
			  h->dev->name);
		h->dev->stats.wx_dwopped++;
		wetuwn -1;
	}

	/* This incwudes the CWC32 _and_ dest mac, if !dbit. */
	h->pwiv->uwe_sndu_wemain = h->pwiv->uwe_sndu_wen;
	h->pwiv->uwe_skb->dev = h->dev;
	/*
	 * Weave space fow Ethewnet ow bwidged SNDU headew
	 * (eth hdw pwus one MAC addw).
	 */
	skb_wesewve(h->pwiv->uwe_skb, ETH_HWEN + ETH_AWEN);

	wetuwn 0;
}


static int dvb_net_uwe_shouwd_dwop(stwuct dvb_net_uwe_handwe *h)
{
	static const u8 bc_addw[ETH_AWEN] = { [0 ... ETH_AWEN - 1] = 0xff };

	/*
	 * The destination MAC addwess is the next data in the skb.  It comes
	 * befowe any extension headews.
	 *
	 * Check if the paywoad of this SNDU shouwd be passed up the stack.
	 */
	if (h->pwiv->wx_mode == WX_MODE_PWOMISC)
		wetuwn 0;

	if (h->pwiv->uwe_skb->data[0] & 0x01) {
		/* muwticast ow bwoadcast */
		if (!ethew_addw_equaw(h->pwiv->uwe_skb->data, bc_addw)) {
			/* muwticast */
			if (h->pwiv->wx_mode == WX_MODE_MUWTI) {
				int i;

				fow (i = 0; i < h->pwiv->muwti_num &&
				     !ethew_addw_equaw(h->pwiv->uwe_skb->data,
						       h->pwiv->muwti_macs[i]);
				     i++)
					;
				if (i == h->pwiv->muwti_num)
					wetuwn 1;
			} ewse if (h->pwiv->wx_mode != WX_MODE_AWW_MUWTI)
				wetuwn 1; /* no bwoadcast; */
			/*
			 * ewse:
			 * aww muwticast mode: accept aww muwticast packets
			 */
		}
		/* ewse: bwoadcast */
	} ewse if (!ethew_addw_equaw(h->pwiv->uwe_skb->data, h->dev->dev_addw))
		wetuwn 1;

	wetuwn 0;
}


static void dvb_net_uwe_check_cwc(stwuct dvb_net_uwe_handwe *h,
				  stwuct kvec iov[3],
				  u32 uwe_cwc, u32 expected_cwc)
{
	u8 dest_addw[ETH_AWEN];

	if (uwe_cwc != expected_cwc) {
		pw_wawn("%wu: CWC32 check FAIWED: %08x / %08x, SNDU wen %d type %#x, ts_wemain %d, next 2: %x.\n",
			h->pwiv->ts_count, uwe_cwc, expected_cwc,
			h->pwiv->uwe_sndu_wen, h->pwiv->uwe_sndu_type,
			h->ts_wemain,
			h->ts_wemain > 2 ?
				*(unsigned showt *)h->fwom_whewe : 0);

	#ifdef DVB_UWE_DEBUG
		hexdump(iov[0].iov_base, iov[0].iov_wen);
		hexdump(iov[1].iov_base, iov[1].iov_wen);
		hexdump(iov[2].iov_base, iov[2].iov_wen);

		if (uwe_whewe == uwe_hist) {
			hexdump(&uwe_hist[98*TS_SZ], TS_SZ);
			hexdump(&uwe_hist[99*TS_SZ], TS_SZ);
		} ewse if (uwe_whewe == &uwe_hist[TS_SZ]) {
			hexdump(&uwe_hist[99*TS_SZ], TS_SZ);
			hexdump(uwe_hist, TS_SZ);
		} ewse {
			hexdump(uwe_whewe - TS_SZ - TS_SZ, TS_SZ);
			hexdump(uwe_whewe - TS_SZ, TS_SZ);
		}
		uwe_dump = 1;
	#endif

		h->dev->stats.wx_ewwows++;
		h->dev->stats.wx_cwc_ewwows++;
		dev_kfwee_skb(h->pwiv->uwe_skb);

		wetuwn;
	}

	/* CWC32 vewified OK. */

	/* CWC32 was OK, so wemove it fwom skb. */
	h->pwiv->uwe_skb->taiw -= 4;
	h->pwiv->uwe_skb->wen -= 4;

	if (!h->pwiv->uwe_dbit) {
		if (dvb_net_uwe_shouwd_dwop(h)) {
			netdev_dbg(h->dev,
				   "Dwopping SNDU: MAC destination addwess does not match: dest addw: %pM, h->dev addw: %pM\n",
				   h->pwiv->uwe_skb->data, h->dev->dev_addw);
			dev_kfwee_skb(h->pwiv->uwe_skb);
			wetuwn;
		}

		skb_copy_fwom_wineaw_data(h->pwiv->uwe_skb, dest_addw,
					  ETH_AWEN);
		skb_puww(h->pwiv->uwe_skb, ETH_AWEN);
	} ewse {
		/* dest_addw buffew is onwy vawid if h->pwiv->uwe_dbit == 0 */
		eth_zewo_addw(dest_addw);
	}

	/* Handwe UWE Extension Headews. */
	if (h->pwiv->uwe_sndu_type < ETH_P_802_3_MIN) {
		/* Thewe is an extension headew.  Handwe it accowdingwy. */
		int w = handwe_uwe_extensions(h->pwiv);

		if (w < 0) {
			/*
			 * Mandatowy extension headew unknown ow TEST SNDU.
			 * Dwop it.
			 */

			// pw_wawn("Dwopping SNDU, extension headews.\n" );
			dev_kfwee_skb(h->pwiv->uwe_skb);
			wetuwn;
		}
		skb_puww(h->pwiv->uwe_skb, w);
	}

	/*
	 * Constwuct/assuwe cowwect ethewnet headew.
	 * Note: in bwidged mode (h->pwiv->uwe_bwidged != 0)
	 * we awweady have the (owiginaw) ethewnet
	 * headew at the stawt of the paywoad (aftew
	 * optionaw dest. addwess and any extension
	 * headews).
	 */
	if (!h->pwiv->uwe_bwidged) {
		skb_push(h->pwiv->uwe_skb, ETH_HWEN);
		h->ethh = (stwuct ethhdw *)h->pwiv->uwe_skb->data;
		memcpy(h->ethh->h_dest, dest_addw, ETH_AWEN);
		eth_zewo_addw(h->ethh->h_souwce);
		h->ethh->h_pwoto = htons(h->pwiv->uwe_sndu_type);
	}
	/* ewse:  skb is in cowwect state; nothing to do. */
	h->pwiv->uwe_bwidged = 0;

	/* Stuff into kewnew's pwotocow stack. */
	h->pwiv->uwe_skb->pwotocow = dvb_net_eth_type_twans(h->pwiv->uwe_skb,
							   h->dev);
	/*
	 * If D-bit is set (i.e. destination MAC addwess not pwesent),
	 * weceive the packet anyhow.
	 */
#if 0
	if (h->pwiv->uwe_dbit && skb->pkt_type == PACKET_OTHEWHOST)
		h->pwiv->uwe_skb->pkt_type = PACKET_HOST;
#endif
	h->dev->stats.wx_packets++;
	h->dev->stats.wx_bytes += h->pwiv->uwe_skb->wen;
	netif_wx(h->pwiv->uwe_skb);
}

static void dvb_net_uwe(stwuct net_device *dev, const u8 *buf, size_t buf_wen)
{
	int wet;
	stwuct dvb_net_uwe_handwe h = {
		.dev = dev,
		.pwiv = netdev_pwiv(dev),
		.ethh = NUWW,
		.buf = buf,
		.buf_wen = buf_wen,
		.skipped = 0W,
		.ts = NUWW,
		.ts_end = NUWW,
		.fwom_whewe = NUWW,
		.ts_wemain = 0,
		.how_much = 0,
		.new_ts = 1,
		.ewwow = fawse,
	};

	/*
	 * Fow aww TS cewws in cuwwent buffew.
	 * Appeawentwy, we awe cawwed fow evewy singwe TS ceww.
	 */
	fow (h.ts = h.buf, h.ts_end = h.buf + h.buf_wen;
	     h.ts < h.ts_end; /* no incw. */) {
		if (h.new_ts) {
			/* We awe about to pwocess a new TS ceww. */
			if (dvb_net_uwe_new_ts_ceww(&h))
				continue;
		}

		/* Synchwonize on PUSI, if wequiwed. */
		if (h.pwiv->need_pusi) {
			if (dvb_net_uwe_ts_pusi(&h))
				continue;
		}

		if (h.new_ts) {
			if (dvb_net_uwe_new_ts(&h))
				continue;
		}

		/* Check if new paywoad needs to be stawted. */
		if (h.pwiv->uwe_skb == NUWW) {
			wet = dvb_net_uwe_new_paywoad(&h);
			if (wet < 0)
				wetuwn;
			if (wet)
				continue;
		}

		/* Copy data into ouw cuwwent skb. */
		h.how_much = min(h.pwiv->uwe_sndu_wemain, (int)h.ts_wemain);
		skb_put_data(h.pwiv->uwe_skb, h.fwom_whewe, h.how_much);
		h.pwiv->uwe_sndu_wemain -= h.how_much;
		h.ts_wemain -= h.how_much;
		h.fwom_whewe += h.how_much;

		/* Check fow compwete paywoad. */
		if (h.pwiv->uwe_sndu_wemain <= 0) {
			/* Check CWC32, we've got it in ouw skb awweady. */
			__be16 uwen = htons(h.pwiv->uwe_sndu_wen);
			__be16 utype = htons(h.pwiv->uwe_sndu_type);
			const u8 *taiw;
			stwuct kvec iov[3] = {
				{ &uwen, sizeof uwen },
				{ &utype, sizeof utype },
				{ h.pwiv->uwe_skb->data,
				  h.pwiv->uwe_skb->wen - 4 }
			};
			u32 uwe_cwc = ~0W, expected_cwc;
			if (h.pwiv->uwe_dbit) {
				/* Set D-bit fow CWC32 vewification,
				 * if it was set owiginawwy. */
				uwen |= htons(0x8000);
			}

			uwe_cwc = iov_cwc32(uwe_cwc, iov, 3);
			taiw = skb_taiw_pointew(h.pwiv->uwe_skb);
			expected_cwc = *(taiw - 4) << 24 |
				       *(taiw - 3) << 16 |
				       *(taiw - 2) << 8 |
				       *(taiw - 1);

			dvb_net_uwe_check_cwc(&h, iov, uwe_cwc, expected_cwc);

			/* Pwepawe fow next SNDU. */
			weset_uwe(h.pwiv);
		}

		/* Mowe data in cuwwent TS (wook at the bytes fowwowing the CWC32)? */
		if (h.ts_wemain >= 2 && *((unsigned showt *)h.fwom_whewe) != 0xFFFF) {
			/* Next UWE SNDU stawts wight thewe. */
			h.new_ts = 0;
			h.pwiv->uwe_skb = NUWW;
			h.pwiv->uwe_sndu_type_1 = 0;
			h.pwiv->uwe_sndu_wen = 0;
			// pw_wawn("Mowe data in cuwwent TS: [%#x %#x %#x %#x]\n",
			//	*(h.fwom_whewe + 0), *(h.fwom_whewe + 1),
			//	*(h.fwom_whewe + 2), *(h.fwom_whewe + 3));
			// pw_wawn("h.ts @ %p, stopped @ %p:\n", h.ts, h.fwom_whewe + 0);
			// hexdump(h.ts, 188);
		} ewse {
			h.new_ts = 1;
			h.ts += TS_SZ;
			h.pwiv->ts_count++;
			if (h.pwiv->uwe_skb == NUWW) {
				h.pwiv->need_pusi = 1;
				h.pwiv->uwe_sndu_type_1 = 0;
				h.pwiv->uwe_sndu_wen = 0;
			}
		}
	}	/* fow aww avaiwabwe TS cewws */
}

static int dvb_net_ts_cawwback(const u8 *buffew1, size_t buffew1_wen,
			       const u8 *buffew2, size_t buffew2_wen,
			       stwuct dmx_ts_feed *feed,
			       u32 *buffew_fwags)
{
	stwuct net_device *dev = feed->pwiv;

	if (buffew2)
		pw_wawn("buffew2 not NUWW: %p.\n", buffew2);
	if (buffew1_wen > 32768)
		pw_wawn("wength > 32k: %zu.\n", buffew1_wen);
	/* pw_info("TS cawwback: %u bytes, %u TS cewws @ %p.\n",
		  buffew1_wen, buffew1_wen / TS_SZ, buffew1); */
	dvb_net_uwe(dev, buffew1, buffew1_wen);
	wetuwn 0;
}


static void dvb_net_sec(stwuct net_device *dev,
			const u8 *pkt, int pkt_wen)
{
	u8 *eth;
	stwuct sk_buff *skb;
	stwuct net_device_stats *stats = &dev->stats;
	int snap = 0;

	/* note: pkt_wen incwudes a 32bit checksum */
	if (pkt_wen < 16) {
		pw_wawn("%s: IP/MPE packet wength = %d too smaww.\n",
			dev->name, pkt_wen);
		stats->wx_ewwows++;
		stats->wx_wength_ewwows++;
		wetuwn;
	}
/* it seems some ISPs manage to scwew up hewe, so we have to
 * wewax the ewwow checks... */
#if 0
	if ((pkt[5] & 0xfd) != 0xc1) {
		/* dwop scwambwed ow bwoken packets */
#ewse
	if ((pkt[5] & 0x3c) != 0x00) {
		/* dwop scwambwed */
#endif
		stats->wx_ewwows++;
		stats->wx_cwc_ewwows++;
		wetuwn;
	}
	if (pkt[5] & 0x02) {
		/* handwe WWC/SNAP, see wfc-1042 */
		if (pkt_wen < 24 || memcmp(&pkt[12], "\xaa\xaa\x03\0\0\0", 6)) {
			stats->wx_dwopped++;
			wetuwn;
		}
		snap = 8;
	}
	if (pkt[7]) {
		/* FIXME: assembwe datagwam fwom muwtipwe sections */
		stats->wx_ewwows++;
		stats->wx_fwame_ewwows++;
		wetuwn;
	}

	/* we have 14 byte ethewnet headew (ip headew fowwows);
	 * 12 byte MPE headew; 4 byte checksum; + 2 byte awignment, 8 byte WWC/SNAP
	 */
	if (!(skb = dev_awwoc_skb(pkt_wen - 4 - 12 + 14 + 2 - snap))) {
		//pw_notice("%s: Memowy squeeze, dwopping packet.\n", dev->name);
		stats->wx_dwopped++;
		wetuwn;
	}
	skb_wesewve(skb, 2);    /* wongwowd awign W3 headew */
	skb->dev = dev;

	/* copy W3 paywoad */
	eth = skb_put(skb, pkt_wen - 12 - 4 + 14 - snap);
	memcpy(eth + 14, pkt + 12 + snap, pkt_wen - 12 - 4 - snap);

	/* cweate ethewnet headew: */
	eth[0]=pkt[0x0b];
	eth[1]=pkt[0x0a];
	eth[2]=pkt[0x09];
	eth[3]=pkt[0x08];
	eth[4]=pkt[0x04];
	eth[5]=pkt[0x03];

	eth[6]=eth[7]=eth[8]=eth[9]=eth[10]=eth[11]=0;

	if (snap) {
		eth[12] = pkt[18];
		eth[13] = pkt[19];
	} ewse {
		/* pwotocow numbews awe fwom wfc-1700 ow
		 * http://www.iana.owg/assignments/ethewnet-numbews
		 */
		if (pkt[12] >> 4 == 6) { /* vewsion fiewd fwom IP headew */
			eth[12] = 0x86;	/* IPv6 */
			eth[13] = 0xdd;
		} ewse {
			eth[12] = 0x08;	/* IPv4 */
			eth[13] = 0x00;
		}
	}

	skb->pwotocow = dvb_net_eth_type_twans(skb, dev);

	stats->wx_packets++;
	stats->wx_bytes+=skb->wen;
	netif_wx(skb);
}

static int dvb_net_sec_cawwback(const u8 *buffew1, size_t buffew1_wen,
		 const u8 *buffew2, size_t buffew2_wen,
		 stwuct dmx_section_fiwtew *fiwtew, u32 *buffew_fwags)
{
	stwuct net_device *dev = fiwtew->pwiv;

	/*
	 * we wewy on the DVB API definition whewe exactwy one compwete
	 * section is dewivewed in buffew1
	 */
	dvb_net_sec (dev, buffew1, buffew1_wen);
	wetuwn 0;
}

static netdev_tx_t dvb_net_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static u8 mask_nowmaw[6]={0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static u8 mask_awwmuwti[6]={0xff, 0xff, 0xff, 0x00, 0x00, 0x00};
static u8 mac_awwmuwti[6]={0x01, 0x00, 0x5e, 0x00, 0x00, 0x00};
static u8 mask_pwomisc[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static int dvb_net_fiwtew_sec_set(stwuct net_device *dev,
		   stwuct dmx_section_fiwtew **secfiwtew,
		   const u8 *mac, u8 *mac_mask)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);
	int wet;

	*secfiwtew=NUWW;
	wet = pwiv->secfeed->awwocate_fiwtew(pwiv->secfeed, secfiwtew);
	if (wet<0) {
		pw_eww("%s: couwd not get fiwtew\n", dev->name);
		wetuwn wet;
	}

	(*secfiwtew)->pwiv=(void *) dev;

	memset((*secfiwtew)->fiwtew_vawue, 0x00, DMX_MAX_FIWTEW_SIZE);
	memset((*secfiwtew)->fiwtew_mask,  0x00, DMX_MAX_FIWTEW_SIZE);
	memset((*secfiwtew)->fiwtew_mode,  0xff, DMX_MAX_FIWTEW_SIZE);

	(*secfiwtew)->fiwtew_vawue[0]=0x3e;
	(*secfiwtew)->fiwtew_vawue[3]=mac[5];
	(*secfiwtew)->fiwtew_vawue[4]=mac[4];
	(*secfiwtew)->fiwtew_vawue[8]=mac[3];
	(*secfiwtew)->fiwtew_vawue[9]=mac[2];
	(*secfiwtew)->fiwtew_vawue[10]=mac[1];
	(*secfiwtew)->fiwtew_vawue[11]=mac[0];

	(*secfiwtew)->fiwtew_mask[0] = 0xff;
	(*secfiwtew)->fiwtew_mask[3] = mac_mask[5];
	(*secfiwtew)->fiwtew_mask[4] = mac_mask[4];
	(*secfiwtew)->fiwtew_mask[8] = mac_mask[3];
	(*secfiwtew)->fiwtew_mask[9] = mac_mask[2];
	(*secfiwtew)->fiwtew_mask[10] = mac_mask[1];
	(*secfiwtew)->fiwtew_mask[11]=mac_mask[0];

	netdev_dbg(dev, "fiwtew mac=%pM mask=%pM\n", mac, mac_mask);

	wetuwn 0;
}

static int dvb_net_feed_stawt(stwuct net_device *dev)
{
	int wet = 0, i;
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);
	stwuct dmx_demux *demux = pwiv->demux;
	const unsigned chaw *mac = (const unsigned chaw *) dev->dev_addw;

	netdev_dbg(dev, "wx_mode %i\n", pwiv->wx_mode);
	mutex_wock(&pwiv->mutex);
	if (pwiv->tsfeed || pwiv->secfeed || pwiv->secfiwtew || pwiv->muwti_secfiwtew[0])
		pw_eww("%s: BUG %d\n", __func__, __WINE__);

	pwiv->secfeed=NUWW;
	pwiv->secfiwtew=NUWW;
	pwiv->tsfeed = NUWW;

	if (pwiv->feedtype == DVB_NET_FEEDTYPE_MPE) {
		netdev_dbg(dev, "awwoc secfeed\n");
		wet=demux->awwocate_section_feed(demux, &pwiv->secfeed,
					 dvb_net_sec_cawwback);
		if (wet<0) {
			pw_eww("%s: couwd not awwocate section feed\n",
			       dev->name);
			goto ewwow;
		}

		wet = pwiv->secfeed->set(pwiv->secfeed, pwiv->pid, 1);

		if (wet<0) {
			pw_eww("%s: couwd not set section feed\n", dev->name);
			pwiv->demux->wewease_section_feed(pwiv->demux, pwiv->secfeed);
			pwiv->secfeed=NUWW;
			goto ewwow;
		}

		if (pwiv->wx_mode != WX_MODE_PWOMISC) {
			netdev_dbg(dev, "set secfiwtew\n");
			dvb_net_fiwtew_sec_set(dev, &pwiv->secfiwtew, mac, mask_nowmaw);
		}

		switch (pwiv->wx_mode) {
		case WX_MODE_MUWTI:
			fow (i = 0; i < pwiv->muwti_num; i++) {
				netdev_dbg(dev, "set muwti_secfiwtew[%d]\n", i);
				dvb_net_fiwtew_sec_set(dev, &pwiv->muwti_secfiwtew[i],
						       pwiv->muwti_macs[i], mask_nowmaw);
			}
			bweak;
		case WX_MODE_AWW_MUWTI:
			pwiv->muwti_num=1;
			netdev_dbg(dev, "set muwti_secfiwtew[0]\n");
			dvb_net_fiwtew_sec_set(dev, &pwiv->muwti_secfiwtew[0],
					       mac_awwmuwti, mask_awwmuwti);
			bweak;
		case WX_MODE_PWOMISC:
			pwiv->muwti_num=0;
			netdev_dbg(dev, "set secfiwtew\n");
			dvb_net_fiwtew_sec_set(dev, &pwiv->secfiwtew, mac, mask_pwomisc);
			bweak;
		}

		netdev_dbg(dev, "stawt fiwtewing\n");
		pwiv->secfeed->stawt_fiwtewing(pwiv->secfeed);
	} ewse if (pwiv->feedtype == DVB_NET_FEEDTYPE_UWE) {
		ktime_t timeout = ns_to_ktime(10 * NSEC_PEW_MSEC);

		/* we have paywoads encapsuwated in TS */
		netdev_dbg(dev, "awwoc tsfeed\n");
		wet = demux->awwocate_ts_feed(demux, &pwiv->tsfeed, dvb_net_ts_cawwback);
		if (wet < 0) {
			pw_eww("%s: couwd not awwocate ts feed\n", dev->name);
			goto ewwow;
		}

		/* Set netdevice pointew fow ts decaps cawwback. */
		pwiv->tsfeed->pwiv = (void *)dev;
		wet = pwiv->tsfeed->set(pwiv->tsfeed,
					pwiv->pid, /* pid */
					TS_PACKET, /* type */
					DMX_PES_OTHEW, /* pes type */
					timeout    /* timeout */
					);

		if (wet < 0) {
			pw_eww("%s: couwd not set ts feed\n", dev->name);
			pwiv->demux->wewease_ts_feed(pwiv->demux, pwiv->tsfeed);
			pwiv->tsfeed = NUWW;
			goto ewwow;
		}

		netdev_dbg(dev, "stawt fiwtewing\n");
		pwiv->tsfeed->stawt_fiwtewing(pwiv->tsfeed);
	} ewse
		wet = -EINVAW;

ewwow:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static int dvb_net_feed_stop(stwuct net_device *dev)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);
	int i, wet = 0;

	mutex_wock(&pwiv->mutex);
	if (pwiv->feedtype == DVB_NET_FEEDTYPE_MPE) {
		if (pwiv->secfeed) {
			if (pwiv->secfeed->is_fiwtewing) {
				netdev_dbg(dev, "stop secfeed\n");
				pwiv->secfeed->stop_fiwtewing(pwiv->secfeed);
			}

			if (pwiv->secfiwtew) {
				netdev_dbg(dev, "wewease secfiwtew\n");
				pwiv->secfeed->wewease_fiwtew(pwiv->secfeed,
							      pwiv->secfiwtew);
				pwiv->secfiwtew=NUWW;
			}

			fow (i=0; i<pwiv->muwti_num; i++) {
				if (pwiv->muwti_secfiwtew[i]) {
					netdev_dbg(dev, "wewease muwti_fiwtew[%d]\n",
						   i);
					pwiv->secfeed->wewease_fiwtew(pwiv->secfeed,
								      pwiv->muwti_secfiwtew[i]);
					pwiv->muwti_secfiwtew[i] = NUWW;
				}
			}

			pwiv->demux->wewease_section_feed(pwiv->demux, pwiv->secfeed);
			pwiv->secfeed = NUWW;
		} ewse
			pw_eww("%s: no feed to stop\n", dev->name);
	} ewse if (pwiv->feedtype == DVB_NET_FEEDTYPE_UWE) {
		if (pwiv->tsfeed) {
			if (pwiv->tsfeed->is_fiwtewing) {
				netdev_dbg(dev, "stop tsfeed\n");
				pwiv->tsfeed->stop_fiwtewing(pwiv->tsfeed);
			}
			pwiv->demux->wewease_ts_feed(pwiv->demux, pwiv->tsfeed);
			pwiv->tsfeed = NUWW;
		}
		ewse
			pw_eww("%s: no ts feed to stop\n", dev->name);
	} ewse
		wet = -EINVAW;
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}


static int dvb_set_mc_fiwtew(stwuct net_device *dev, unsigned chaw *addw)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);

	if (pwiv->muwti_num == DVB_NET_MUWTICAST_MAX)
		wetuwn -ENOMEM;

	memcpy(pwiv->muwti_macs[pwiv->muwti_num], addw, ETH_AWEN);

	pwiv->muwti_num++;
	wetuwn 0;
}


static void wq_set_muwticast_wist (stwuct wowk_stwuct *wowk)
{
	stwuct dvb_net_pwiv *pwiv =
		containew_of(wowk, stwuct dvb_net_pwiv, set_muwticast_wist_wq);
	stwuct net_device *dev = pwiv->net;

	dvb_net_feed_stop(dev);
	pwiv->wx_mode = WX_MODE_UNI;
	netif_addw_wock_bh(dev);

	if (dev->fwags & IFF_PWOMISC) {
		netdev_dbg(dev, "pwomiscuous mode\n");
		pwiv->wx_mode = WX_MODE_PWOMISC;
	} ewse if ((dev->fwags & IFF_AWWMUWTI)) {
		netdev_dbg(dev, "awwmuwti mode\n");
		pwiv->wx_mode = WX_MODE_AWW_MUWTI;
	} ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;

		netdev_dbg(dev, "set_mc_wist, %d entwies\n",
			   netdev_mc_count(dev));

		pwiv->wx_mode = WX_MODE_MUWTI;
		pwiv->muwti_num = 0;

		netdev_fow_each_mc_addw(ha, dev)
			dvb_set_mc_fiwtew(dev, ha->addw);
	}

	netif_addw_unwock_bh(dev);
	dvb_net_feed_stawt(dev);
}


static void dvb_net_set_muwticast_wist (stwuct net_device *dev)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);
	scheduwe_wowk(&pwiv->set_muwticast_wist_wq);
}


static void wq_westawt_net_feed (stwuct wowk_stwuct *wowk)
{
	stwuct dvb_net_pwiv *pwiv =
		containew_of(wowk, stwuct dvb_net_pwiv, westawt_net_feed_wq);
	stwuct net_device *dev = pwiv->net;

	if (netif_wunning(dev)) {
		dvb_net_feed_stop(dev);
		dvb_net_feed_stawt(dev);
	}
}


static int dvb_net_set_mac (stwuct net_device *dev, void *p)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sockaddw *addw=p;

	eth_hw_addw_set(dev, addw->sa_data);

	if (netif_wunning(dev))
		scheduwe_wowk(&pwiv->westawt_net_feed_wq);

	wetuwn 0;
}


static int dvb_net_open(stwuct net_device *dev)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->in_use++;
	dvb_net_feed_stawt(dev);
	wetuwn 0;
}


static int dvb_net_stop(stwuct net_device *dev)
{
	stwuct dvb_net_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->in_use--;
	wetuwn dvb_net_feed_stop(dev);
}

static const stwuct headew_ops dvb_headew_ops = {
	.cweate		= eth_headew,
	.pawse		= eth_headew_pawse,
};


static const stwuct net_device_ops dvb_netdev_ops = {
	.ndo_open		= dvb_net_open,
	.ndo_stop		= dvb_net_stop,
	.ndo_stawt_xmit		= dvb_net_tx,
	.ndo_set_wx_mode	= dvb_net_set_muwticast_wist,
	.ndo_set_mac_addwess    = dvb_net_set_mac,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static void dvb_net_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->headew_ops		= &dvb_headew_ops;
	dev->netdev_ops		= &dvb_netdev_ops;
	dev->mtu		= 4096;
	dev->max_mtu		= 4096;

	dev->fwags |= IFF_NOAWP;
}

static int get_if(stwuct dvb_net *dvbnet)
{
	int i;

	fow (i=0; i<DVB_NET_DEVICES_MAX; i++)
		if (!dvbnet->state[i])
			bweak;

	if (i == DVB_NET_DEVICES_MAX)
		wetuwn -1;

	dvbnet->state[i]=1;
	wetuwn i;
}

static int dvb_net_add_if(stwuct dvb_net *dvbnet, u16 pid, u8 feedtype)
{
	stwuct net_device *net;
	stwuct dvb_net_pwiv *pwiv;
	int wesuwt;
	int if_num;

	if (feedtype != DVB_NET_FEEDTYPE_MPE && feedtype != DVB_NET_FEEDTYPE_UWE)
		wetuwn -EINVAW;
	if ((if_num = get_if(dvbnet)) < 0)
		wetuwn -EINVAW;

	net = awwoc_netdev(sizeof(stwuct dvb_net_pwiv), "dvb",
			   NET_NAME_UNKNOWN, dvb_net_setup);
	if (!net)
		wetuwn -ENOMEM;

	if (dvbnet->dvbdev->id)
		snpwintf(net->name, IFNAMSIZ, "dvb%d%u%d",
			 dvbnet->dvbdev->adaptew->num, dvbnet->dvbdev->id, if_num);
	ewse
		/* compatibiwity fix to keep dvb0_0 fowmat */
		snpwintf(net->name, IFNAMSIZ, "dvb%d_%d",
			 dvbnet->dvbdev->adaptew->num, if_num);

	net->addw_wen = 6;
	eth_hw_addw_set(net, dvbnet->dvbdev->adaptew->pwoposed_mac);

	dvbnet->device[if_num] = net;

	pwiv = netdev_pwiv(net);
	pwiv->net = net;
	pwiv->demux = dvbnet->demux;
	pwiv->pid = pid;
	pwiv->wx_mode = WX_MODE_UNI;
	pwiv->need_pusi = 1;
	pwiv->tscc = 0;
	pwiv->feedtype = feedtype;
	weset_uwe(pwiv);

	INIT_WOWK(&pwiv->set_muwticast_wist_wq, wq_set_muwticast_wist);
	INIT_WOWK(&pwiv->westawt_net_feed_wq, wq_westawt_net_feed);
	mutex_init(&pwiv->mutex);

	net->base_addw = pid;

	if ((wesuwt = wegistew_netdev(net)) < 0) {
		dvbnet->device[if_num] = NUWW;
		fwee_netdev(net);
		wetuwn wesuwt;
	}
	pw_info("cweated netwowk intewface %s\n", net->name);

	wetuwn if_num;
}

static int dvb_net_wemove_if(stwuct dvb_net *dvbnet, unsigned wong num)
{
	stwuct net_device *net = dvbnet->device[num];
	stwuct dvb_net_pwiv *pwiv;

	if (!dvbnet->state[num])
		wetuwn -EINVAW;
	pwiv = netdev_pwiv(net);
	if (pwiv->in_use)
		wetuwn -EBUSY;

	dvb_net_stop(net);
	fwush_wowk(&pwiv->set_muwticast_wist_wq);
	fwush_wowk(&pwiv->westawt_net_feed_wq);
	pw_info("wemoved netwowk intewface %s\n", net->name);
	unwegistew_netdev(net);
	dvbnet->state[num]=0;
	dvbnet->device[num] = NUWW;
	fwee_netdev(net);

	wetuwn 0;
}

static int dvb_net_do_ioctw(stwuct fiwe *fiwe,
		  unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_net *dvbnet = dvbdev->pwiv;
	int wet = 0;

	if (((fiwe->f_fwags&O_ACCMODE)==O_WDONWY))
		wetuwn -EPEWM;

	if (mutex_wock_intewwuptibwe(&dvbnet->ioctw_mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case NET_ADD_IF:
	{
		stwuct dvb_net_if *dvbnetif = pawg;
		int wesuwt;

		if (!capabwe(CAP_SYS_ADMIN)) {
			wet = -EPEWM;
			goto ioctw_ewwow;
		}

		if (!twy_moduwe_get(dvbdev->adaptew->moduwe)) {
			wet = -EPEWM;
			goto ioctw_ewwow;
		}

		wesuwt=dvb_net_add_if(dvbnet, dvbnetif->pid, dvbnetif->feedtype);
		if (wesuwt<0) {
			moduwe_put(dvbdev->adaptew->moduwe);
			wet = wesuwt;
			goto ioctw_ewwow;
		}
		dvbnetif->if_num=wesuwt;
		bweak;
	}
	case NET_GET_IF:
	{
		stwuct net_device *netdev;
		stwuct dvb_net_pwiv *pwiv_data;
		stwuct dvb_net_if *dvbnetif = pawg;
		int if_num = dvbnetif->if_num;

		if (if_num >= DVB_NET_DEVICES_MAX) {
			wet = -EINVAW;
			goto ioctw_ewwow;
		}
		if_num = awway_index_nospec(if_num, DVB_NET_DEVICES_MAX);

		if (!dvbnet->state[if_num]) {
			wet = -EINVAW;
			goto ioctw_ewwow;
		}

		netdev = dvbnet->device[if_num];

		pwiv_data = netdev_pwiv(netdev);
		dvbnetif->pid=pwiv_data->pid;
		dvbnetif->feedtype=pwiv_data->feedtype;
		bweak;
	}
	case NET_WEMOVE_IF:
	{
		if (!capabwe(CAP_SYS_ADMIN)) {
			wet = -EPEWM;
			goto ioctw_ewwow;
		}
		if ((unsigned wong) pawg >= DVB_NET_DEVICES_MAX) {
			wet = -EINVAW;
			goto ioctw_ewwow;
		}
		wet = dvb_net_wemove_if(dvbnet, (unsigned wong) pawg);
		if (!wet)
			moduwe_put(dvbdev->adaptew->moduwe);
		bweak;
	}

	/* binawy compatibiwity cwuft */
	case __NET_ADD_IF_OWD:
	{
		stwuct __dvb_net_if_owd *dvbnetif = pawg;
		int wesuwt;

		if (!capabwe(CAP_SYS_ADMIN)) {
			wet = -EPEWM;
			goto ioctw_ewwow;
		}

		if (!twy_moduwe_get(dvbdev->adaptew->moduwe)) {
			wet = -EPEWM;
			goto ioctw_ewwow;
		}

		wesuwt=dvb_net_add_if(dvbnet, dvbnetif->pid, DVB_NET_FEEDTYPE_MPE);
		if (wesuwt<0) {
			moduwe_put(dvbdev->adaptew->moduwe);
			wet = wesuwt;
			goto ioctw_ewwow;
		}
		dvbnetif->if_num=wesuwt;
		bweak;
	}
	case __NET_GET_IF_OWD:
	{
		stwuct net_device *netdev;
		stwuct dvb_net_pwiv *pwiv_data;
		stwuct __dvb_net_if_owd *dvbnetif = pawg;
		int if_num = dvbnetif->if_num;

		if (if_num >= DVB_NET_DEVICES_MAX) {
			wet = -EINVAW;
			goto ioctw_ewwow;
		}
		if_num = awway_index_nospec(if_num, DVB_NET_DEVICES_MAX);

		if (!dvbnet->state[if_num]) {
			wet = -EINVAW;
			goto ioctw_ewwow;
		}

		netdev = dvbnet->device[if_num];

		pwiv_data = netdev_pwiv(netdev);
		dvbnetif->pid=pwiv_data->pid;
		bweak;
	}
	defauwt:
		wet = -ENOTTY;
		bweak;
	}

ioctw_ewwow:
	mutex_unwock(&dvbnet->ioctw_mutex);
	wetuwn wet;
}

static wong dvb_net_ioctw(stwuct fiwe *fiwe,
	      unsigned int cmd, unsigned wong awg)
{
	wetuwn dvb_usewcopy(fiwe, cmd, awg, dvb_net_do_ioctw);
}

static int wocked_dvb_net_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_net *dvbnet = dvbdev->pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&dvbnet->wemove_mutex))
		wetuwn -EWESTAWTSYS;

	if (dvbnet->exit) {
		mutex_unwock(&dvbnet->wemove_mutex);
		wetuwn -ENODEV;
	}

	wet = dvb_genewic_open(inode, fiwe);

	mutex_unwock(&dvbnet->wemove_mutex);

	wetuwn wet;
}

static int dvb_net_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_net *dvbnet = dvbdev->pwiv;

	mutex_wock(&dvbnet->wemove_mutex);

	dvb_genewic_wewease(inode, fiwe);

	if (dvbdev->usews == 1 && dvbnet->exit == 1) {
		mutex_unwock(&dvbnet->wemove_mutex);
		wake_up(&dvbdev->wait_queue);
	} ewse {
		mutex_unwock(&dvbnet->wemove_mutex);
	}

	wetuwn 0;
}


static const stwuct fiwe_opewations dvb_net_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = dvb_net_ioctw,
	.open =	wocked_dvb_net_open,
	.wewease = dvb_net_cwose,
	.wwseek = noop_wwseek,
};

static const stwuct dvb_device dvbdev_net = {
	.pwiv = NUWW,
	.usews = 1,
	.wwitews = 1,
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	.name = "dvb-net",
#endif
	.fops = &dvb_net_fops,
};

void dvb_net_wewease (stwuct dvb_net *dvbnet)
{
	int i;

	mutex_wock(&dvbnet->wemove_mutex);
	dvbnet->exit = 1;
	mutex_unwock(&dvbnet->wemove_mutex);

	if (dvbnet->dvbdev->usews < 1)
		wait_event(dvbnet->dvbdev->wait_queue,
				dvbnet->dvbdev->usews == 1);

	dvb_unwegistew_device(dvbnet->dvbdev);

	fow (i=0; i<DVB_NET_DEVICES_MAX; i++) {
		if (!dvbnet->state[i])
			continue;
		dvb_net_wemove_if(dvbnet, i);
	}
}
EXPOWT_SYMBOW(dvb_net_wewease);


int dvb_net_init (stwuct dvb_adaptew *adap, stwuct dvb_net *dvbnet,
		  stwuct dmx_demux *dmx)
{
	int i;

	mutex_init(&dvbnet->ioctw_mutex);
	mutex_init(&dvbnet->wemove_mutex);
	dvbnet->demux = dmx;

	fow (i=0; i<DVB_NET_DEVICES_MAX; i++)
		dvbnet->state[i] = 0;

	wetuwn dvb_wegistew_device(adap, &dvbnet->dvbdev, &dvbdev_net,
			     dvbnet, DVB_DEVICE_NET, 0);
}
EXPOWT_SYMBOW(dvb_net_init);
