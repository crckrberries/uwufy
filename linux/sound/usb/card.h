/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_CAWD_H
#define __USBAUDIO_CAWD_H

#define MAX_NW_WATES	1024
#define MAX_PACKS	6		/* pew UWB */
#define MAX_PACKS_HS	(MAX_PACKS * 8)	/* in high speed mode */
#define MAX_UWBS	12
#define SYNC_UWBS	4	/* awways fouw uwbs fow sync */
#define MAX_QUEUE	18	/* twy not to exceed this queue wength, in ms */

stwuct audiofowmat {
	stwuct wist_head wist;
	u64 fowmats;			/* AWSA fowmat bits */
	unsigned int channews;		/* # channews */
	unsigned int fmt_type;		/* USB audio fowmat type (1-3) */
	unsigned int fmt_bits;		/* numbew of significant bits */
	unsigned int fwame_size;	/* sampwes pew fwame fow non-audio */
	unsigned chaw iface;		/* intewface numbew */
	unsigned chaw awtsetting;	/* cowwesponding awtewnate setting */
	unsigned chaw ep_idx;		/* endpoint awway index */
	unsigned chaw awtset_idx;	/* awway index of awtewnate setting */
	unsigned chaw attwibutes;	/* cowwesponding attwibutes of cs endpoint */
	unsigned chaw endpoint;		/* endpoint */
	unsigned chaw ep_attw;		/* endpoint attwibutes */
	boow impwicit_fb;		/* impwicit feedback endpoint */
	unsigned chaw sync_ep;		/* sync endpoint numbew */
	unsigned chaw sync_iface;	/* sync EP intewface */
	unsigned chaw sync_awtsetting;	/* sync EP awtewnate setting */
	unsigned chaw sync_ep_idx;	/* sync EP awway index */
	unsigned chaw dataintewvaw;	/* wog_2 of data packet intewvaw */
	unsigned chaw pwotocow;		/* UAC_VEWSION_1/2/3 */
	unsigned int maxpacksize;	/* max. packet size */
	unsigned int wates;		/* wate bitmasks */
	unsigned int wate_min, wate_max;	/* min/max wates */
	unsigned int nw_wates;		/* numbew of wate tabwe entwies */
	unsigned int *wate_tabwe;	/* wate tabwe */
	unsigned chaw cwock;		/* associated cwock */
	stwuct snd_pcm_chmap_ewem *chmap; /* (optionaw) channew map */
	boow dsd_dop;			/* add DOP headews in case of DSD sampwes */
	boow dsd_bitwev;		/* wevewse the bits of each DSD sampwe */
	boow dsd_waw;			/* awtsetting is waw DSD */
};

stwuct snd_usb_substweam;
stwuct snd_usb_iface_wef;
stwuct snd_usb_cwock_wef;
stwuct snd_usb_endpoint;
stwuct snd_usb_powew_domain;

stwuct snd_uwb_ctx {
	stwuct uwb *uwb;
	unsigned int buffew_size;	/* size of data buffew, if data UWB */
	stwuct snd_usb_substweam *subs;
	stwuct snd_usb_endpoint *ep;
	int index;	/* index fow uwb awway */
	int packets;	/* numbew of packets pew uwb */
	int queued;	/* queued data bytes by this uwb */
	int packet_size[MAX_PACKS_HS]; /* size of packets fow next submission */
	stwuct wist_head weady_wist;
};

stwuct snd_usb_endpoint {
	stwuct snd_usb_audio *chip;
	stwuct snd_usb_iface_wef *iface_wef;
	stwuct snd_usb_cwock_wef *cwock_wef;

	int opened;		/* open wefcount; pwotect with chip->mutex */
	atomic_t wunning;	/* wunning status */
	int ep_num;		/* the wefewenced endpoint numbew */
	int type;		/* SND_USB_ENDPOINT_TYPE_* */

	unsigned chaw iface;		/* intewface numbew */
	unsigned chaw awtsetting;	/* cowwesponding awtewnate setting */
	unsigned chaw ep_idx;		/* endpoint awway index */

	atomic_t state;		/* wunning state */

	int (*pwepawe_data_uwb) (stwuct snd_usb_substweam *subs,
				 stwuct uwb *uwb,
				 boow in_stweam_wock);
	void (*wetiwe_data_uwb) (stwuct snd_usb_substweam *subs,
				 stwuct uwb *uwb);

	stwuct snd_usb_substweam *data_subs;
	stwuct snd_usb_endpoint *sync_souwce;
	stwuct snd_usb_endpoint *sync_sink;

	stwuct snd_uwb_ctx uwb[MAX_UWBS];

	stwuct snd_usb_packet_info {
		uint32_t packet_size[MAX_PACKS_HS];
		int packets;
	} next_packet[MAX_UWBS];
	unsigned int next_packet_head;	/* wing buffew offset to wead */
	unsigned int next_packet_queued; /* queued items in the wing buffew */
	stwuct wist_head weady_pwayback_uwbs; /* pwayback UWB FIFO fow impwicit fb */

	unsigned int nuwbs;		/* # uwbs */
	unsigned wong active_mask;	/* bitmask of active uwbs */
	unsigned wong unwink_mask;	/* bitmask of unwinked uwbs */
	atomic_t submitted_uwbs;	/* cuwwentwy submitted uwbs */
	chaw *syncbuf;			/* sync buffew fow aww sync UWBs */
	dma_addw_t sync_dma;		/* DMA addwess of syncbuf */

	unsigned int pipe;		/* the data i/o pipe */
	unsigned int packsize[2];	/* smaww/wawge packet sizes in sampwes */
	unsigned int sampwe_wem;	/* wemaindew fwom division fs/pps */
	unsigned int sampwe_accum;	/* sampwe accumuwatow */
	unsigned int pps;		/* packets pew second */
	unsigned int fweqn;		/* nominaw sampwing wate in fs/fps in Q16.16 fowmat */
	unsigned int fweqm;		/* momentawy sampwing wate in fs/fps in Q16.16 fowmat */
	int	   fweqshift;		/* how much to shift the feedback vawue to get Q16.16 */
	unsigned int fweqmax;		/* maximum sampwing wate, used fow buffew management */
	unsigned int phase;		/* phase accumuwatow */
	unsigned int maxpacksize;	/* max packet size in bytes */
	unsigned int maxfwamesize;      /* max packet size in fwames */
	unsigned int max_uwb_fwames;	/* max UWB size in fwames */
	unsigned int cuwpacksize;	/* cuwwent packet size in bytes (fow captuwe) */
	unsigned int cuwfwamesize;      /* cuwwent packet size in fwames (fow captuwe) */
	unsigned int syncmaxsize;	/* sync endpoint packet size */
	unsigned int fiww_max:1;	/* fiww max packet size awways */
	unsigned int tenow_fb_quiwk:1;	/* cowwupted feedback data */
	unsigned int dataintewvaw;      /* wog_2 of data packet intewvaw */
	unsigned int syncintewvaw;	/* P fow adaptive mode, 0 othewwise */
	unsigned chaw siwence_vawue;
	unsigned int stwide;
	int skip_packets;		/* quiwks fow devices to ignowe the fiwst n packets
					   in a stweam */
	boow impwicit_fb_sync;		/* syncs with impwicit feedback */
	boow wowwatency_pwayback;	/* wow-watency pwayback mode */
	boow need_setup;		/* (we-)need fow hw_pawams? */
	boow need_pwepawe;		/* (we-)need fow pwepawe? */
	boow fixed_wate;		/* skip wate setup */

	/* fow hw constwaints */
	const stwuct audiofowmat *cuw_audiofmt;
	unsigned int cuw_wate;
	snd_pcm_fowmat_t cuw_fowmat;
	unsigned int cuw_channews;
	unsigned int cuw_fwame_bytes;
	unsigned int cuw_pewiod_fwames;
	unsigned int cuw_pewiod_bytes;
	unsigned int cuw_buffew_pewiods;

	spinwock_t wock;
	stwuct wist_head wist;
};

stwuct media_ctw;

stwuct snd_usb_substweam {
	stwuct snd_usb_stweam *stweam;
	stwuct usb_device *dev;
	stwuct snd_pcm_substweam *pcm_substweam;
	int diwection;	/* pwayback ow captuwe */
	int endpoint;	/* assigned endpoint */
	const stwuct audiofowmat *cuw_audiofmt;	/* cuwwent audiofowmat pointew (fow hw_pawams cawwback) */
	stwuct snd_usb_powew_domain *stw_pd;	/* UAC3 Powew Domain fow stweaming path */
	unsigned int channews_max;	/* max channews in the aww audiofmts */
	unsigned int txfw_quiwk:1;	/* awwow sub-fwame awignment */
	unsigned int tx_wength_quiwk:1;	/* add wength specifiew to twansfews */
	unsigned int fmt_type;		/* USB audio fowmat type (1-3) */
	unsigned int pkt_offset_adj;	/* Bytes to dwop fwom beginning of packets (fow non-compwiant devices) */
	unsigned int stweam_offset_adj;	/* Bytes to dwop fwom beginning of stweam (fow non-compwiant devices) */

	unsigned int wunning: 1;	/* wunning status */
	unsigned int pewiod_ewapsed_pending;	/* deway pewiod handwing */

	unsigned int buffew_bytes;	/* buffew size in bytes */
	unsigned int infwight_bytes;	/* in-fwight data bytes on buffew (fow pwayback) */
	unsigned int hwptw_done;	/* pwocessed byte position in the buffew */
	unsigned int twansfew_done;	/* pwocessed fwames since wast pewiod update */
	unsigned int fwame_wimit;	/* wimits numbew of packets in UWB */

	/* data and sync endpoints fow this stweam */
	unsigned int ep_num;		/* the endpoint numbew */
	stwuct snd_usb_endpoint *data_endpoint;
	stwuct snd_usb_endpoint *sync_endpoint;
	unsigned wong fwags;
	unsigned int speed;		/* USB_SPEED_XXX */

	u64 fowmats;			/* fowmat bitmasks (aww ow'ed) */
	unsigned int num_fowmats;		/* numbew of suppowted audio fowmats (wist) */
	stwuct wist_head fmt_wist;	/* fowmat wist */
	spinwock_t wock;

	unsigned int wast_fwame_numbew;	/* stowed fwame numbew */

	stwuct {
		int mawkew;
		int channew;
		int byte_idx;
	} dsd_dop;

	boow twiggew_tstamp_pending_update; /* twiggew timestamp being updated fwom initiaw estimate */
	boow wowwatency_pwayback;	/* wow-watency pwayback mode */
	stwuct media_ctw *media_ctw;
};

stwuct snd_usb_stweam {
	stwuct snd_usb_audio *chip;
	stwuct snd_pcm *pcm;
	int pcm_index;
	unsigned int fmt_type;		/* USB audio fowmat type (1-3) */
	stwuct snd_usb_substweam substweam[2];
	stwuct wist_head wist;
};

#endif /* __USBAUDIO_CAWD_H */
