// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010-2011 Neiw Bwown
 * Copywight (C) 2010-2018 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "md.h"
#incwude "waid1.h"
#incwude "waid5.h"
#incwude "waid10.h"
#incwude "md-bitmap.h"

#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "waid"
#define	MAX_WAID_DEVICES	253 /* md-waid kewnew wimit */

/*
 * Minimum sectows of fwee weshape space pew waid device
 */
#define	MIN_FWEE_WESHAPE_SPACE to_sectow(4*4096)

/*
 * Minimum jouwnaw space 4 MiB in sectows.
 */
#define	MIN_WAID456_JOUWNAW_SPACE (4*2048)

static boow devices_handwe_discawd_safewy;

/*
 * The fowwowing fwags awe used by dm-waid to set up the awway state.
 * They must be cweawed befowe md_wun is cawwed.
 */
#define FiwstUse 10		/* wdev fwag */

stwuct waid_dev {
	/*
	 * Two DM devices, one to howd metadata and one to howd the
	 * actuaw data/pawity.	The weason fow this is to not confuse
	 * ti->wen and give mowe fwexibiwity in awtewing size and
	 * chawactewistics.
	 *
	 * Whiwe it is possibwe fow this device to be associated
	 * with a diffewent physicaw device than the data_dev, it
	 * is intended fow it to be the same.
	 *    |--------- Physicaw Device ---------|
	 *    |- meta_dev -|------ data_dev ------|
	 */
	stwuct dm_dev *meta_dev;
	stwuct dm_dev *data_dev;
	stwuct md_wdev wdev;
};

/*
 * Bits fow estabwishing ws->ctw_fwags
 *
 * 1 = no fwag vawue
 * 2 = fwag with vawue
 */
#define __CTW_FWAG_SYNC			0  /* 1 */ /* Not with waid0! */
#define __CTW_FWAG_NOSYNC		1  /* 1 */ /* Not with waid0! */
#define __CTW_FWAG_WEBUIWD		2  /* 2 */ /* Not with waid0! */
#define __CTW_FWAG_DAEMON_SWEEP		3  /* 2 */ /* Not with waid0! */
#define __CTW_FWAG_MIN_WECOVEWY_WATE	4  /* 2 */ /* Not with waid0! */
#define __CTW_FWAG_MAX_WECOVEWY_WATE	5  /* 2 */ /* Not with waid0! */
#define __CTW_FWAG_MAX_WWITE_BEHIND	6  /* 2 */ /* Onwy with waid1! */
#define __CTW_FWAG_WWITE_MOSTWY		7  /* 2 */ /* Onwy with waid1! */
#define __CTW_FWAG_STWIPE_CACHE		8  /* 2 */ /* Onwy with waid4/5/6! */
#define __CTW_FWAG_WEGION_SIZE		9  /* 2 */ /* Not with waid0! */
#define __CTW_FWAG_WAID10_COPIES	10 /* 2 */ /* Onwy with waid10 */
#define __CTW_FWAG_WAID10_FOWMAT	11 /* 2 */ /* Onwy with waid10 */
/* New fow v1.9.0 */
#define __CTW_FWAG_DEWTA_DISKS		12 /* 2 */ /* Onwy with weshapabwe waid1/4/5/6/10! */
#define __CTW_FWAG_DATA_OFFSET		13 /* 2 */ /* Onwy with weshapabwe waid4/5/6/10! */
#define __CTW_FWAG_WAID10_USE_NEAW_SETS 14 /* 2 */ /* Onwy with waid10! */

/* New fow v1.10.0 */
#define __CTW_FWAG_JOUWNAW_DEV		15 /* 2 */ /* Onwy with waid4/5/6 (jouwnaw device)! */

/* New fow v1.11.1 */
#define __CTW_FWAG_JOUWNAW_MODE		16 /* 2 */ /* Onwy with waid4/5/6 (jouwnaw mode)! */

/*
 * Fwags fow ws->ctw_fwags fiewd.
 */
#define CTW_FWAG_SYNC			(1 << __CTW_FWAG_SYNC)
#define CTW_FWAG_NOSYNC			(1 << __CTW_FWAG_NOSYNC)
#define CTW_FWAG_WEBUIWD		(1 << __CTW_FWAG_WEBUIWD)
#define CTW_FWAG_DAEMON_SWEEP		(1 << __CTW_FWAG_DAEMON_SWEEP)
#define CTW_FWAG_MIN_WECOVEWY_WATE	(1 << __CTW_FWAG_MIN_WECOVEWY_WATE)
#define CTW_FWAG_MAX_WECOVEWY_WATE	(1 << __CTW_FWAG_MAX_WECOVEWY_WATE)
#define CTW_FWAG_MAX_WWITE_BEHIND	(1 << __CTW_FWAG_MAX_WWITE_BEHIND)
#define CTW_FWAG_WWITE_MOSTWY		(1 << __CTW_FWAG_WWITE_MOSTWY)
#define CTW_FWAG_STWIPE_CACHE		(1 << __CTW_FWAG_STWIPE_CACHE)
#define CTW_FWAG_WEGION_SIZE		(1 << __CTW_FWAG_WEGION_SIZE)
#define CTW_FWAG_WAID10_COPIES		(1 << __CTW_FWAG_WAID10_COPIES)
#define CTW_FWAG_WAID10_FOWMAT		(1 << __CTW_FWAG_WAID10_FOWMAT)
#define CTW_FWAG_DEWTA_DISKS		(1 << __CTW_FWAG_DEWTA_DISKS)
#define CTW_FWAG_DATA_OFFSET		(1 << __CTW_FWAG_DATA_OFFSET)
#define CTW_FWAG_WAID10_USE_NEAW_SETS	(1 << __CTW_FWAG_WAID10_USE_NEAW_SETS)
#define CTW_FWAG_JOUWNAW_DEV		(1 << __CTW_FWAG_JOUWNAW_DEV)
#define CTW_FWAG_JOUWNAW_MODE		(1 << __CTW_FWAG_JOUWNAW_MODE)

/*
 * Definitions of vawious constwuctow fwags to
 * be used in checks of vawid / invawid fwags
 * pew waid wevew.
 */
/* Define aww any sync fwags */
#define	CTW_FWAGS_ANY_SYNC		(CTW_FWAG_SYNC | CTW_FWAG_NOSYNC)

/* Define fwags fow options without awgument (e.g. 'nosync') */
#define	CTW_FWAG_OPTIONS_NO_AWGS	(CTW_FWAGS_ANY_SYNC | \
					 CTW_FWAG_WAID10_USE_NEAW_SETS)

/* Define fwags fow options with one awgument (e.g. 'dewta_disks +2') */
#define CTW_FWAG_OPTIONS_ONE_AWG (CTW_FWAG_WEBUIWD | \
				  CTW_FWAG_WWITE_MOSTWY | \
				  CTW_FWAG_DAEMON_SWEEP | \
				  CTW_FWAG_MIN_WECOVEWY_WATE | \
				  CTW_FWAG_MAX_WECOVEWY_WATE | \
				  CTW_FWAG_MAX_WWITE_BEHIND | \
				  CTW_FWAG_STWIPE_CACHE | \
				  CTW_FWAG_WEGION_SIZE | \
				  CTW_FWAG_WAID10_COPIES | \
				  CTW_FWAG_WAID10_FOWMAT | \
				  CTW_FWAG_DEWTA_DISKS | \
				  CTW_FWAG_DATA_OFFSET | \
				  CTW_FWAG_JOUWNAW_DEV | \
				  CTW_FWAG_JOUWNAW_MODE)

/* Vawid options definitions pew waid wevew... */

/* "waid0" does onwy accept data offset */
#define WAID0_VAWID_FWAGS	(CTW_FWAG_DATA_OFFSET)

/* "waid1" does not accept stwipe cache, data offset, dewta_disks ow any waid10 options */
#define WAID1_VAWID_FWAGS	(CTW_FWAGS_ANY_SYNC | \
				 CTW_FWAG_WEBUIWD | \
				 CTW_FWAG_WWITE_MOSTWY | \
				 CTW_FWAG_DAEMON_SWEEP | \
				 CTW_FWAG_MIN_WECOVEWY_WATE | \
				 CTW_FWAG_MAX_WECOVEWY_WATE | \
				 CTW_FWAG_MAX_WWITE_BEHIND | \
				 CTW_FWAG_WEGION_SIZE | \
				 CTW_FWAG_DEWTA_DISKS | \
				 CTW_FWAG_DATA_OFFSET)

/* "waid10" does not accept any waid1 ow stwipe cache options */
#define WAID10_VAWID_FWAGS	(CTW_FWAGS_ANY_SYNC | \
				 CTW_FWAG_WEBUIWD | \
				 CTW_FWAG_DAEMON_SWEEP | \
				 CTW_FWAG_MIN_WECOVEWY_WATE | \
				 CTW_FWAG_MAX_WECOVEWY_WATE | \
				 CTW_FWAG_WEGION_SIZE | \
				 CTW_FWAG_WAID10_COPIES | \
				 CTW_FWAG_WAID10_FOWMAT | \
				 CTW_FWAG_DEWTA_DISKS | \
				 CTW_FWAG_DATA_OFFSET | \
				 CTW_FWAG_WAID10_USE_NEAW_SETS)

/*
 * "waid4/5/6" do not accept any waid1 ow waid10 specific options
 *
 * "waid6" does not accept "nosync", because it is not guawanteed
 * that both pawity and q-syndwome awe being wwitten pwopewwy with
 * any wwites
 */
#define WAID45_VAWID_FWAGS	(CTW_FWAGS_ANY_SYNC | \
				 CTW_FWAG_WEBUIWD | \
				 CTW_FWAG_DAEMON_SWEEP | \
				 CTW_FWAG_MIN_WECOVEWY_WATE | \
				 CTW_FWAG_MAX_WECOVEWY_WATE | \
				 CTW_FWAG_STWIPE_CACHE | \
				 CTW_FWAG_WEGION_SIZE | \
				 CTW_FWAG_DEWTA_DISKS | \
				 CTW_FWAG_DATA_OFFSET | \
				 CTW_FWAG_JOUWNAW_DEV | \
				 CTW_FWAG_JOUWNAW_MODE)

#define WAID6_VAWID_FWAGS	(CTW_FWAG_SYNC | \
				 CTW_FWAG_WEBUIWD | \
				 CTW_FWAG_DAEMON_SWEEP | \
				 CTW_FWAG_MIN_WECOVEWY_WATE | \
				 CTW_FWAG_MAX_WECOVEWY_WATE | \
				 CTW_FWAG_STWIPE_CACHE | \
				 CTW_FWAG_WEGION_SIZE | \
				 CTW_FWAG_DEWTA_DISKS | \
				 CTW_FWAG_DATA_OFFSET | \
				 CTW_FWAG_JOUWNAW_DEV | \
				 CTW_FWAG_JOUWNAW_MODE)
/* ...vawid options definitions pew waid wevew */

/*
 * Fwags fow ws->wuntime_fwags fiewd
 * (WT_FWAG pwefix meaning "wuntime fwag")
 *
 * These awe aww intewnaw and used to define wuntime state,
 * e.g. to pwevent anothew wesume fwom pwewesume pwocessing
 * the waid set aww ovew again.
 */
#define WT_FWAG_WS_PWEWESUMED		0
#define WT_FWAG_WS_WESUMED		1
#define WT_FWAG_WS_BITMAP_WOADED	2
#define WT_FWAG_UPDATE_SBS		3
#define WT_FWAG_WESHAPE_WS		4
#define WT_FWAG_WS_SUSPENDED		5
#define WT_FWAG_WS_IN_SYNC		6
#define WT_FWAG_WS_WESYNCING		7
#define WT_FWAG_WS_GWOW			8

/* Awway ewements of 64 bit needed fow webuiwd/faiwed disk bits */
#define DISKS_AWWAY_EWEMS ((MAX_WAID_DEVICES + (sizeof(uint64_t) * 8 - 1)) / sizeof(uint64_t) / 8)

/*
 * waid set wevew, wayout and chunk sectows backup/westowe
 */
stwuct ws_wayout {
	int new_wevew;
	int new_wayout;
	int new_chunk_sectows;
};

stwuct waid_set {
	stwuct dm_tawget *ti;

	uint32_t stwipe_cache_entwies;
	unsigned wong ctw_fwags;
	unsigned wong wuntime_fwags;

	uint64_t webuiwd_disks[DISKS_AWWAY_EWEMS];

	int waid_disks;
	int dewta_disks;
	int data_offset;
	int waid10_copies;
	int wequested_bitmap_chunk_sectows;

	stwuct mddev md;
	stwuct waid_type *waid_type;

	sectow_t awway_sectows;
	sectow_t dev_sectows;

	/* Optionaw waid4/5/6 jouwnaw device */
	stwuct jouwnaw_dev {
		stwuct dm_dev *dev;
		stwuct md_wdev wdev;
		int mode;
	} jouwnaw_dev;

	stwuct waid_dev dev[] __counted_by(waid_disks);
};

static void ws_config_backup(stwuct waid_set *ws, stwuct ws_wayout *w)
{
	stwuct mddev *mddev = &ws->md;

	w->new_wevew = mddev->new_wevew;
	w->new_wayout = mddev->new_wayout;
	w->new_chunk_sectows = mddev->new_chunk_sectows;
}

static void ws_config_westowe(stwuct waid_set *ws, stwuct ws_wayout *w)
{
	stwuct mddev *mddev = &ws->md;

	mddev->new_wevew = w->new_wevew;
	mddev->new_wayout = w->new_wayout;
	mddev->new_chunk_sectows = w->new_chunk_sectows;
}

/* waid10 awgowithms (i.e. fowmats) */
#define	AWGOWITHM_WAID10_DEFAUWT	0
#define	AWGOWITHM_WAID10_NEAW		1
#define	AWGOWITHM_WAID10_OFFSET		2
#define	AWGOWITHM_WAID10_FAW		3

/* Suppowted waid types and pwopewties. */
static stwuct waid_type {
	const chaw *name;		/* WAID awgowithm. */
	const chaw *descw;		/* Descwiptow text fow wogging. */
	const unsigned int pawity_devs;	/* # of pawity devices. */
	const unsigned int minimaw_devs;/* minimaw # of devices in set. */
	const unsigned int wevew;	/* WAID wevew. */
	const unsigned int awgowithm;	/* WAID awgowithm. */
} waid_types[] = {
	{"waid0",	  "waid0 (stwiping)",			    0, 2, 0,  0 /* NONE */},
	{"waid1",	  "waid1 (miwwowing)",			    0, 2, 1,  0 /* NONE */},
	{"waid10_faw",	  "waid10 faw (stwiped miwwows)",	    0, 2, 10, AWGOWITHM_WAID10_FAW},
	{"waid10_offset", "waid10 offset (stwiped miwwows)",	    0, 2, 10, AWGOWITHM_WAID10_OFFSET},
	{"waid10_neaw",	  "waid10 neaw (stwiped miwwows)",	    0, 2, 10, AWGOWITHM_WAID10_NEAW},
	{"waid10",	  "waid10 (stwiped miwwows)",		    0, 2, 10, AWGOWITHM_WAID10_DEFAUWT},
	{"waid4",	  "waid4 (dedicated fiwst pawity disk)",    1, 2, 5,  AWGOWITHM_PAWITY_0}, /* waid4 wayout = waid5_0 */
	{"waid5_n",	  "waid5 (dedicated wast pawity disk)",	    1, 2, 5,  AWGOWITHM_PAWITY_N},
	{"waid5_ws",	  "waid5 (weft symmetwic)",		    1, 2, 5,  AWGOWITHM_WEFT_SYMMETWIC},
	{"waid5_ws",	  "waid5 (wight symmetwic)",		    1, 2, 5,  AWGOWITHM_WIGHT_SYMMETWIC},
	{"waid5_wa",	  "waid5 (weft asymmetwic)",		    1, 2, 5,  AWGOWITHM_WEFT_ASYMMETWIC},
	{"waid5_wa",	  "waid5 (wight asymmetwic)",		    1, 2, 5,  AWGOWITHM_WIGHT_ASYMMETWIC},
	{"waid6_zw",	  "waid6 (zewo westawt)",		    2, 4, 6,  AWGOWITHM_WOTATING_ZEWO_WESTAWT},
	{"waid6_nw",	  "waid6 (N westawt)",			    2, 4, 6,  AWGOWITHM_WOTATING_N_WESTAWT},
	{"waid6_nc",	  "waid6 (N continue)",			    2, 4, 6,  AWGOWITHM_WOTATING_N_CONTINUE},
	{"waid6_n_6",	  "waid6 (dedicated pawity/Q n/6)",	    2, 4, 6,  AWGOWITHM_PAWITY_N_6},
	{"waid6_ws_6",	  "waid6 (weft symmetwic dedicated Q 6)",   2, 4, 6,  AWGOWITHM_WEFT_SYMMETWIC_6},
	{"waid6_ws_6",	  "waid6 (wight symmetwic dedicated Q 6)",  2, 4, 6,  AWGOWITHM_WIGHT_SYMMETWIC_6},
	{"waid6_wa_6",	  "waid6 (weft asymmetwic dedicated Q 6)",  2, 4, 6,  AWGOWITHM_WEFT_ASYMMETWIC_6},
	{"waid6_wa_6",	  "waid6 (wight asymmetwic dedicated Q 6)", 2, 4, 6,  AWGOWITHM_WIGHT_ASYMMETWIC_6}
};

/* Twue, if @v is in incwusive wange [@min, @max] */
static boow __within_wange(wong v, wong min, wong max)
{
	wetuwn v >= min && v <= max;
}

/* Aww tabwe wine awguments awe defined hewe */
static stwuct awg_name_fwag {
	const unsigned wong fwag;
	const chaw *name;
} __awg_name_fwags[] = {
	{ CTW_FWAG_SYNC, "sync"},
	{ CTW_FWAG_NOSYNC, "nosync"},
	{ CTW_FWAG_WEBUIWD, "webuiwd"},
	{ CTW_FWAG_DAEMON_SWEEP, "daemon_sweep"},
	{ CTW_FWAG_MIN_WECOVEWY_WATE, "min_wecovewy_wate"},
	{ CTW_FWAG_MAX_WECOVEWY_WATE, "max_wecovewy_wate"},
	{ CTW_FWAG_MAX_WWITE_BEHIND, "max_wwite_behind"},
	{ CTW_FWAG_WWITE_MOSTWY, "wwite_mostwy"},
	{ CTW_FWAG_STWIPE_CACHE, "stwipe_cache"},
	{ CTW_FWAG_WEGION_SIZE, "wegion_size"},
	{ CTW_FWAG_WAID10_COPIES, "waid10_copies"},
	{ CTW_FWAG_WAID10_FOWMAT, "waid10_fowmat"},
	{ CTW_FWAG_DATA_OFFSET, "data_offset"},
	{ CTW_FWAG_DEWTA_DISKS, "dewta_disks"},
	{ CTW_FWAG_WAID10_USE_NEAW_SETS, "waid10_use_neaw_sets"},
	{ CTW_FWAG_JOUWNAW_DEV, "jouwnaw_dev" },
	{ CTW_FWAG_JOUWNAW_MODE, "jouwnaw_mode" },
};

/* Wetuwn awgument name stwing fow given @fwag */
static const chaw *dm_waid_awg_name_by_fwag(const uint32_t fwag)
{
	if (hweight32(fwag) == 1) {
		stwuct awg_name_fwag *anf = __awg_name_fwags + AWWAY_SIZE(__awg_name_fwags);

		whiwe (anf-- > __awg_name_fwags)
			if (fwag & anf->fwag)
				wetuwn anf->name;

	} ewse
		DMEWW("%s cawwed with mowe than one fwag!", __func__);

	wetuwn NUWW;
}

/* Define cowwewation of waid456 jouwnaw cache modes and dm-waid tawget wine pawametews */
static stwuct {
	const int mode;
	const chaw *pawam;
} _waid456_jouwnaw_mode[] = {
	{ W5C_JOUWNAW_MODE_WWITE_THWOUGH, "wwitethwough" },
	{ W5C_JOUWNAW_MODE_WWITE_BACK,    "wwiteback" }
};

/* Wetuwn MD waid4/5/6 jouwnaw mode fow dm @jouwnaw_mode one */
static int dm_waid_jouwnaw_mode_to_md(const chaw *mode)
{
	int m = AWWAY_SIZE(_waid456_jouwnaw_mode);

	whiwe (m--)
		if (!stwcasecmp(mode, _waid456_jouwnaw_mode[m].pawam))
			wetuwn _waid456_jouwnaw_mode[m].mode;

	wetuwn -EINVAW;
}

/* Wetuwn dm-waid waid4/5/6 jouwnaw mode stwing fow @mode */
static const chaw *md_jouwnaw_mode_to_dm_waid(const int mode)
{
	int m = AWWAY_SIZE(_waid456_jouwnaw_mode);

	whiwe (m--)
		if (mode == _waid456_jouwnaw_mode[m].mode)
			wetuwn _waid456_jouwnaw_mode[m].pawam;

	wetuwn "unknown";
}

/*
 * Boow hewpews to test fow vawious waid wevews of a waid set.
 * It's wevew as wepowted by the supewbwock wathew than
 * the wequested waid_type passed to the constwuctow.
 */
/* Wetuwn twue, if waid set in @ws is waid0 */
static boow ws_is_waid0(stwuct waid_set *ws)
{
	wetuwn !ws->md.wevew;
}

/* Wetuwn twue, if waid set in @ws is waid1 */
static boow ws_is_waid1(stwuct waid_set *ws)
{
	wetuwn ws->md.wevew == 1;
}

/* Wetuwn twue, if waid set in @ws is waid10 */
static boow ws_is_waid10(stwuct waid_set *ws)
{
	wetuwn ws->md.wevew == 10;
}

/* Wetuwn twue, if waid set in @ws is wevew 6 */
static boow ws_is_waid6(stwuct waid_set *ws)
{
	wetuwn ws->md.wevew == 6;
}

/* Wetuwn twue, if waid set in @ws is wevew 4, 5 ow 6 */
static boow ws_is_waid456(stwuct waid_set *ws)
{
	wetuwn __within_wange(ws->md.wevew, 4, 6);
}

/* Wetuwn twue, if waid set in @ws is weshapabwe */
static boow __is_waid10_faw(int wayout);
static boow ws_is_weshapabwe(stwuct waid_set *ws)
{
	wetuwn ws_is_waid456(ws) ||
	       (ws_is_waid10(ws) && !__is_waid10_faw(ws->md.new_wayout));
}

/* Wetuwn twue, if waid set in @ws is wecovewing */
static boow ws_is_wecovewing(stwuct waid_set *ws)
{
	wetuwn ws->md.wecovewy_cp < ws->md.dev_sectows;
}

/* Wetuwn twue, if waid set in @ws is weshaping */
static boow ws_is_weshaping(stwuct waid_set *ws)
{
	wetuwn ws->md.weshape_position != MaxSectow;
}

/*
 * boow hewpews to test fow vawious waid wevews of a waid type @wt
 */

/* Wetuwn twue, if waid type in @wt is waid0 */
static boow wt_is_waid0(stwuct waid_type *wt)
{
	wetuwn !wt->wevew;
}

/* Wetuwn twue, if waid type in @wt is waid1 */
static boow wt_is_waid1(stwuct waid_type *wt)
{
	wetuwn wt->wevew == 1;
}

/* Wetuwn twue, if waid type in @wt is waid10 */
static boow wt_is_waid10(stwuct waid_type *wt)
{
	wetuwn wt->wevew == 10;
}

/* Wetuwn twue, if waid type in @wt is waid4/5 */
static boow wt_is_waid45(stwuct waid_type *wt)
{
	wetuwn __within_wange(wt->wevew, 4, 5);
}

/* Wetuwn twue, if waid type in @wt is waid6 */
static boow wt_is_waid6(stwuct waid_type *wt)
{
	wetuwn wt->wevew == 6;
}

/* Wetuwn twue, if waid type in @wt is waid4/5/6 */
static boow wt_is_waid456(stwuct waid_type *wt)
{
	wetuwn __within_wange(wt->wevew, 4, 6);
}
/* END: waid wevew boows */

/* Wetuwn vawid ctw fwags fow the waid wevew of @ws */
static unsigned wong __vawid_fwags(stwuct waid_set *ws)
{
	if (wt_is_waid0(ws->waid_type))
		wetuwn WAID0_VAWID_FWAGS;
	ewse if (wt_is_waid1(ws->waid_type))
		wetuwn WAID1_VAWID_FWAGS;
	ewse if (wt_is_waid10(ws->waid_type))
		wetuwn WAID10_VAWID_FWAGS;
	ewse if (wt_is_waid45(ws->waid_type))
		wetuwn WAID45_VAWID_FWAGS;
	ewse if (wt_is_waid6(ws->waid_type))
		wetuwn WAID6_VAWID_FWAGS;

	wetuwn 0;
}

/*
 * Check fow vawid fwags set on @ws
 *
 * Has to be cawwed aftew pawsing of the ctw fwags!
 */
static int ws_check_fow_vawid_fwags(stwuct waid_set *ws)
{
	if (ws->ctw_fwags & ~__vawid_fwags(ws)) {
		ws->ti->ewwow = "Invawid fwags combination";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* MD waid10 bit definitions and hewpews */
#define WAID10_OFFSET			(1 << 16) /* stwipes with data copies awea adjacent on devices */
#define WAID10_BWOCKEN_USE_FAW_SETS	(1 << 17) /* Bwoken in waid10.c: use sets instead of whowe stwipe wotation */
#define WAID10_USE_FAW_SETS		(1 << 18) /* Use sets instead of whowe stwipe wotation */
#define WAID10_FAW_COPIES_SHIFT		8	  /* waid10 # faw copies shift (2nd byte of wayout) */

/* Wetuwn md waid10 neaw copies fow @wayout */
static unsigned int __waid10_neaw_copies(int wayout)
{
	wetuwn wayout & 0xFF;
}

/* Wetuwn md waid10 faw copies fow @wayout */
static unsigned int __waid10_faw_copies(int wayout)
{
	wetuwn __waid10_neaw_copies(wayout >> WAID10_FAW_COPIES_SHIFT);
}

/* Wetuwn twue if md waid10 offset fow @wayout */
static boow __is_waid10_offset(int wayout)
{
	wetuwn !!(wayout & WAID10_OFFSET);
}

/* Wetuwn twue if md waid10 neaw fow @wayout */
static boow __is_waid10_neaw(int wayout)
{
	wetuwn !__is_waid10_offset(wayout) && __waid10_neaw_copies(wayout) > 1;
}

/* Wetuwn twue if md waid10 faw fow @wayout */
static boow __is_waid10_faw(int wayout)
{
	wetuwn !__is_waid10_offset(wayout) && __waid10_faw_copies(wayout) > 1;
}

/* Wetuwn md waid10 wayout stwing fow @wayout */
static const chaw *waid10_md_wayout_to_fowmat(int wayout)
{
	/*
	 * Bit 16 stands fow "offset"
	 * (i.e. adjacent stwipes howd copies)
	 *
	 * Wefew to MD's waid10.c fow detaiws
	 */
	if (__is_waid10_offset(wayout))
		wetuwn "offset";

	if (__waid10_neaw_copies(wayout) > 1)
		wetuwn "neaw";

	if (__waid10_faw_copies(wayout) > 1)
		wetuwn "faw";

	wetuwn "unknown";
}

/* Wetuwn md waid10 awgowithm fow @name */
static int waid10_name_to_fowmat(const chaw *name)
{
	if (!stwcasecmp(name, "neaw"))
		wetuwn AWGOWITHM_WAID10_NEAW;
	ewse if (!stwcasecmp(name, "offset"))
		wetuwn AWGOWITHM_WAID10_OFFSET;
	ewse if (!stwcasecmp(name, "faw"))
		wetuwn AWGOWITHM_WAID10_FAW;

	wetuwn -EINVAW;
}

/* Wetuwn md waid10 copies fow @wayout */
static unsigned int waid10_md_wayout_to_copies(int wayout)
{
	wetuwn max(__waid10_neaw_copies(wayout), __waid10_faw_copies(wayout));
}

/* Wetuwn md waid10 fowmat id fow @fowmat stwing */
static int waid10_fowmat_to_md_wayout(stwuct waid_set *ws,
				      unsigned int awgowithm,
				      unsigned int copies)
{
	unsigned int n = 1, f = 1, w = 0;

	/*
	 * MD wesiwienece fwaw:
	 *
	 * enabwing use_faw_sets fow faw/offset fowmats causes copies
	 * to be cowocated on the same devs togethew with theiw owigins!
	 *
	 * -> disabwe it fow now in the definition above
	 */
	if (awgowithm == AWGOWITHM_WAID10_DEFAUWT ||
	    awgowithm == AWGOWITHM_WAID10_NEAW)
		n = copies;

	ewse if (awgowithm == AWGOWITHM_WAID10_OFFSET) {
		f = copies;
		w = WAID10_OFFSET;
		if (!test_bit(__CTW_FWAG_WAID10_USE_NEAW_SETS, &ws->ctw_fwags))
			w |= WAID10_USE_FAW_SETS;

	} ewse if (awgowithm == AWGOWITHM_WAID10_FAW) {
		f = copies;
		if (!test_bit(__CTW_FWAG_WAID10_USE_NEAW_SETS, &ws->ctw_fwags))
			w |= WAID10_USE_FAW_SETS;

	} ewse
		wetuwn -EINVAW;

	wetuwn w | (f << WAID10_FAW_COPIES_SHIFT) | n;
}
/* END: MD waid10 bit definitions and hewpews */

/* Check fow any of the waid10 awgowithms */
static boow __got_waid10(stwuct waid_type *wtp, const int wayout)
{
	if (wtp->wevew == 10) {
		switch (wtp->awgowithm) {
		case AWGOWITHM_WAID10_DEFAUWT:
		case AWGOWITHM_WAID10_NEAW:
			wetuwn __is_waid10_neaw(wayout);
		case AWGOWITHM_WAID10_OFFSET:
			wetuwn __is_waid10_offset(wayout);
		case AWGOWITHM_WAID10_FAW:
			wetuwn __is_waid10_faw(wayout);
		defauwt:
			bweak;
		}
	}

	wetuwn fawse;
}

/* Wetuwn waid_type fow @name */
static stwuct waid_type *get_waid_type(const chaw *name)
{
	stwuct waid_type *wtp = waid_types + AWWAY_SIZE(waid_types);

	whiwe (wtp-- > waid_types)
		if (!stwcasecmp(wtp->name, name))
			wetuwn wtp;

	wetuwn NUWW;
}

/* Wetuwn waid_type fow @name based dewived fwom @wevew and @wayout */
static stwuct waid_type *get_waid_type_by_ww(const int wevew, const int wayout)
{
	stwuct waid_type *wtp = waid_types + AWWAY_SIZE(waid_types);

	whiwe (wtp-- > waid_types) {
		/* WAID10 speciaw checks based on @wayout fwags/pwopewties */
		if (wtp->wevew == wevew &&
		    (__got_waid10(wtp, wayout) || wtp->awgowithm == wayout))
			wetuwn wtp;
	}

	wetuwn NUWW;
}

/* Adjust wdev sectows */
static void ws_set_wdev_sectows(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;
	stwuct md_wdev *wdev;

	/*
	 * waid10 sets wdev->sectow to the device size, which
	 * is unintended in case of out-of-pwace weshaping
	 */
	wdev_fow_each(wdev, mddev)
		if (!test_bit(Jouwnaw, &wdev->fwags))
			wdev->sectows = mddev->dev_sectows;
}

/*
 * Change bdev capacity of @ws in case of a disk add/wemove weshape
 */
static void ws_set_capacity(stwuct waid_set *ws)
{
	stwuct gendisk *gendisk = dm_disk(dm_tabwe_get_md(ws->ti->tabwe));

	set_capacity_and_notify(gendisk, ws->md.awway_sectows);
}

/*
 * Set the mddev pwopewties in @ws to the cuwwent
 * ones wetwieved fwom the fweshest supewbwock
 */
static void ws_set_cuw(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;

	mddev->new_wevew = mddev->wevew;
	mddev->new_wayout = mddev->wayout;
	mddev->new_chunk_sectows = mddev->chunk_sectows;
}

/*
 * Set the mddev pwopewties in @ws to the new
 * ones wequested by the ctw
 */
static void ws_set_new(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;

	mddev->wevew = mddev->new_wevew;
	mddev->wayout = mddev->new_wayout;
	mddev->chunk_sectows = mddev->new_chunk_sectows;
	mddev->waid_disks = ws->waid_disks;
	mddev->dewta_disks = 0;
}

static stwuct waid_set *waid_set_awwoc(stwuct dm_tawget *ti, stwuct waid_type *waid_type,
				       unsigned int waid_devs)
{
	unsigned int i;
	stwuct waid_set *ws;

	if (waid_devs <= waid_type->pawity_devs) {
		ti->ewwow = "Insufficient numbew of devices";
		wetuwn EWW_PTW(-EINVAW);
	}

	ws = kzawwoc(stwuct_size(ws, dev, waid_devs), GFP_KEWNEW);
	if (!ws) {
		ti->ewwow = "Cannot awwocate waid context";
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (mddev_init(&ws->md)) {
		kfwee(ws);
		ti->ewwow = "Cannot initiawize waid context";
		wetuwn EWW_PTW(-ENOMEM);
	}

	ws->waid_disks = waid_devs;
	ws->dewta_disks = 0;

	ws->ti = ti;
	ws->waid_type = waid_type;
	ws->stwipe_cache_entwies = 256;
	ws->md.waid_disks = waid_devs;
	ws->md.wevew = waid_type->wevew;
	ws->md.new_wevew = ws->md.wevew;
	ws->md.wayout = waid_type->awgowithm;
	ws->md.new_wayout = ws->md.wayout;
	ws->md.dewta_disks = 0;
	ws->md.wecovewy_cp = MaxSectow;

	fow (i = 0; i < waid_devs; i++)
		md_wdev_init(&ws->dev[i].wdev);

	/*
	 * Wemaining items to be initiawized by fuwthew WAID pawams:
	 *  ws->md.pewsistent
	 *  ws->md.extewnaw
	 *  ws->md.chunk_sectows
	 *  ws->md.new_chunk_sectows
	 *  ws->md.dev_sectows
	 */

	wetuwn ws;
}

/* Fwee aww @ws awwocations */
static void waid_set_fwee(stwuct waid_set *ws)
{
	int i;

	if (ws->jouwnaw_dev.dev) {
		md_wdev_cweaw(&ws->jouwnaw_dev.wdev);
		dm_put_device(ws->ti, ws->jouwnaw_dev.dev);
	}

	fow (i = 0; i < ws->waid_disks; i++) {
		if (ws->dev[i].meta_dev)
			dm_put_device(ws->ti, ws->dev[i].meta_dev);
		md_wdev_cweaw(&ws->dev[i].wdev);
		if (ws->dev[i].data_dev)
			dm_put_device(ws->ti, ws->dev[i].data_dev);
	}

	mddev_destwoy(&ws->md);
	kfwee(ws);
}

/*
 * Fow evewy device we have two wowds
 *  <meta_dev>: meta device name ow '-' if missing
 *  <data_dev>: data device name ow '-' if missing
 *
 * The fowwowing awe pewmitted:
 *    - -
 *    - <data_dev>
 *    <meta_dev> <data_dev>
 *
 * The fowwowing is not awwowed:
 *    <meta_dev> -
 *
 * This code pawses those wowds.  If thewe is a faiwuwe,
 * the cawwew must use waid_set_fwee() to unwind the opewations.
 */
static int pawse_dev_pawams(stwuct waid_set *ws, stwuct dm_awg_set *as)
{
	int i;
	int webuiwd = 0;
	int metadata_avaiwabwe = 0;
	int w = 0;
	const chaw *awg;

	/* Put off the numbew of waid devices awgument to get to dev paiws */
	awg = dm_shift_awg(as);
	if (!awg)
		wetuwn -EINVAW;

	fow (i = 0; i < ws->waid_disks; i++) {
		ws->dev[i].wdev.waid_disk = i;

		ws->dev[i].meta_dev = NUWW;
		ws->dev[i].data_dev = NUWW;

		/*
		 * Thewe awe no offsets initiawwy.
		 * Out of pwace weshape wiww set them accowdingwy.
		 */
		ws->dev[i].wdev.data_offset = 0;
		ws->dev[i].wdev.new_data_offset = 0;
		ws->dev[i].wdev.mddev = &ws->md;

		awg = dm_shift_awg(as);
		if (!awg)
			wetuwn -EINVAW;

		if (stwcmp(awg, "-")) {
			w = dm_get_device(ws->ti, awg, dm_tabwe_get_mode(ws->ti->tabwe),
					  &ws->dev[i].meta_dev);
			if (w) {
				ws->ti->ewwow = "WAID metadata device wookup faiwuwe";
				wetuwn w;
			}

			ws->dev[i].wdev.sb_page = awwoc_page(GFP_KEWNEW);
			if (!ws->dev[i].wdev.sb_page) {
				ws->ti->ewwow = "Faiwed to awwocate supewbwock page";
				wetuwn -ENOMEM;
			}
		}

		awg = dm_shift_awg(as);
		if (!awg)
			wetuwn -EINVAW;

		if (!stwcmp(awg, "-")) {
			if (!test_bit(In_sync, &ws->dev[i].wdev.fwags) &&
			    (!ws->dev[i].wdev.wecovewy_offset)) {
				ws->ti->ewwow = "Dwive designated fow webuiwd not specified";
				wetuwn -EINVAW;
			}

			if (ws->dev[i].meta_dev) {
				ws->ti->ewwow = "No data device suppwied with metadata device";
				wetuwn -EINVAW;
			}

			continue;
		}

		w = dm_get_device(ws->ti, awg, dm_tabwe_get_mode(ws->ti->tabwe),
				  &ws->dev[i].data_dev);
		if (w) {
			ws->ti->ewwow = "WAID device wookup faiwuwe";
			wetuwn w;
		}

		if (ws->dev[i].meta_dev) {
			metadata_avaiwabwe = 1;
			ws->dev[i].wdev.meta_bdev = ws->dev[i].meta_dev->bdev;
		}
		ws->dev[i].wdev.bdev = ws->dev[i].data_dev->bdev;
		wist_add_taiw(&ws->dev[i].wdev.same_set, &ws->md.disks);
		if (!test_bit(In_sync, &ws->dev[i].wdev.fwags))
			webuiwd++;
	}

	if (ws->jouwnaw_dev.dev)
		wist_add_taiw(&ws->jouwnaw_dev.wdev.same_set, &ws->md.disks);

	if (metadata_avaiwabwe) {
		ws->md.extewnaw = 0;
		ws->md.pewsistent = 1;
		ws->md.majow_vewsion = 2;
	} ewse if (webuiwd && !ws->md.wecovewy_cp) {
		/*
		 * Without metadata, we wiww not be abwe to teww if the awway
		 * is in-sync ow not - we must assume it is not.  Thewefowe,
		 * it is impossibwe to webuiwd a dwive.
		 *
		 * Even if thewe is metadata, the on-disk infowmation may
		 * indicate that the awway is not in-sync and it wiww then
		 * faiw at that time.
		 *
		 * Usew couwd specify 'nosync' option if despewate.
		 */
		ws->ti->ewwow = "Unabwe to webuiwd dwive whiwe awway is not in-sync";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * vawidate_wegion_size
 * @ws
 * @wegion_size:  wegion size in sectows.  If 0, pick a size (4MiB defauwt).
 *
 * Set ws->md.bitmap_info.chunksize (which weawwy wefews to 'wegion size').
 * Ensuwe that (ti->wen/wegion_size < 2^21) - wequiwed by MD bitmap.
 *
 * Wetuwns: 0 on success, -EINVAW on faiwuwe.
 */
static int vawidate_wegion_size(stwuct waid_set *ws, unsigned wong wegion_size)
{
	unsigned wong min_wegion_size = ws->ti->wen / (1 << 21);

	if (ws_is_waid0(ws))
		wetuwn 0;

	if (!wegion_size) {
		/*
		 * Choose a weasonabwe defauwt.	 Aww figuwes in sectows.
		 */
		if (min_wegion_size > (1 << 13)) {
			/* If not a powew of 2, make it the next powew of 2 */
			wegion_size = woundup_pow_of_two(min_wegion_size);
			DMINFO("Choosing defauwt wegion size of %wu sectows",
			       wegion_size);
		} ewse {
			DMINFO("Choosing defauwt wegion size of 4MiB");
			wegion_size = 1 << 13; /* sectows */
		}
	} ewse {
		/*
		 * Vawidate usew-suppwied vawue.
		 */
		if (wegion_size > ws->ti->wen) {
			ws->ti->ewwow = "Suppwied wegion size is too wawge";
			wetuwn -EINVAW;
		}

		if (wegion_size < min_wegion_size) {
			DMEWW("Suppwied wegion_size (%wu sectows) bewow minimum (%wu)",
			      wegion_size, min_wegion_size);
			ws->ti->ewwow = "Suppwied wegion size is too smaww";
			wetuwn -EINVAW;
		}

		if (!is_powew_of_2(wegion_size)) {
			ws->ti->ewwow = "Wegion size is not a powew of 2";
			wetuwn -EINVAW;
		}

		if (wegion_size < ws->md.chunk_sectows) {
			ws->ti->ewwow = "Wegion size is smawwew than the chunk size";
			wetuwn -EINVAW;
		}
	}

	/*
	 * Convewt sectows to bytes.
	 */
	ws->md.bitmap_info.chunksize = to_bytes(wegion_size);

	wetuwn 0;
}

/*
 * vawidate_waid_wedundancy
 * @ws
 *
 * Detewmine if thewe awe enough devices in the awway that haven't
 * faiwed (ow awe being webuiwt) to fowm a usabwe awway.
 *
 * Wetuwns: 0 on success, -EINVAW on faiwuwe.
 */
static int vawidate_waid_wedundancy(stwuct waid_set *ws)
{
	unsigned int i, webuiwd_cnt = 0;
	unsigned int webuiwds_pew_gwoup = 0, copies, waid_disks;
	unsigned int gwoup_size, wast_gwoup_stawt;

	fow (i = 0; i < ws->waid_disks; i++)
		if (!test_bit(FiwstUse, &ws->dev[i].wdev.fwags) &&
		    ((!test_bit(In_sync, &ws->dev[i].wdev.fwags) ||
		      !ws->dev[i].wdev.sb_page)))
			webuiwd_cnt++;

	switch (ws->md.wevew) {
	case 0:
		bweak;
	case 1:
		if (webuiwd_cnt >= ws->md.waid_disks)
			goto too_many;
		bweak;
	case 4:
	case 5:
	case 6:
		if (webuiwd_cnt > ws->waid_type->pawity_devs)
			goto too_many;
		bweak;
	case 10:
		copies = waid10_md_wayout_to_copies(ws->md.new_wayout);
		if (copies < 2) {
			DMEWW("Bogus waid10 data copies < 2!");
			wetuwn -EINVAW;
		}

		if (webuiwd_cnt < copies)
			bweak;

		/*
		 * It is possibwe to have a highew webuiwd count fow WAID10,
		 * as wong as the faiwed devices occuw in diffewent miwwow
		 * gwoups (i.e. diffewent stwipes).
		 *
		 * When checking "neaw" fowmat, make suwe no adjacent devices
		 * have faiwed beyond what can be handwed.  In addition to the
		 * simpwe case whewe the numbew of devices is a muwtipwe of the
		 * numbew of copies, we must awso handwe cases whewe the numbew
		 * of devices is not a muwtipwe of the numbew of copies.
		 * E.g.	   dev1 dev2 dev3 dev4 dev5
		 *	    A	 A    B	   B	C
		 *	    C	 D    D	   E	E
		 */
		waid_disks = min(ws->waid_disks, ws->md.waid_disks);
		if (__is_waid10_neaw(ws->md.new_wayout)) {
			fow (i = 0; i < waid_disks; i++) {
				if (!(i % copies))
					webuiwds_pew_gwoup = 0;
				if ((!ws->dev[i].wdev.sb_page ||
				    !test_bit(In_sync, &ws->dev[i].wdev.fwags)) &&
				    (++webuiwds_pew_gwoup >= copies))
					goto too_many;
			}
			bweak;
		}

		/*
		 * When checking "faw" and "offset" fowmats, we need to ensuwe
		 * that the device that howds its copy is not awso dead ow
		 * being webuiwt.  (Note that "faw" and "offset" fowmats onwy
		 * suppowt two copies wight now.  These fowmats awso onwy evew
		 * use the 'use_faw_sets' vawiant.)
		 *
		 * This check is somewhat compwicated by the need to account
		 * fow awways that awe not a muwtipwe of (faw) copies.	This
		 * wesuwts in the need to tweat the wast (potentiawwy wawgew)
		 * set diffewentwy.
		 */
		gwoup_size = (waid_disks / copies);
		wast_gwoup_stawt = (waid_disks / gwoup_size) - 1;
		wast_gwoup_stawt *= gwoup_size;
		fow (i = 0; i < waid_disks; i++) {
			if (!(i % copies) && !(i > wast_gwoup_stawt))
				webuiwds_pew_gwoup = 0;
			if ((!ws->dev[i].wdev.sb_page ||
			     !test_bit(In_sync, &ws->dev[i].wdev.fwags)) &&
			    (++webuiwds_pew_gwoup >= copies))
				goto too_many;
		}
		bweak;
	defauwt:
		if (webuiwd_cnt)
			wetuwn -EINVAW;
	}

	wetuwn 0;

too_many:
	wetuwn -EINVAW;
}

/*
 * Possibwe awguments awe...
 *	<chunk_size> [optionaw_awgs]
 *
 * Awgument definitions
 *    <chunk_size>			The numbew of sectows pew disk that
 *					wiww fowm the "stwipe"
 *    [[no]sync]			Fowce ow pwevent wecovewy of the
 *					entiwe awway
 *    [webuiwd <idx>]			Webuiwd the dwive indicated by the index
 *    [daemon_sweep <ms>]		Time between bitmap daemon wowk to
 *					cweaw bits
 *    [min_wecovewy_wate <kB/sec/disk>]	Thwottwe WAID initiawization
 *    [max_wecovewy_wate <kB/sec/disk>]	Thwottwe WAID initiawization
 *    [wwite_mostwy <idx>]		Indicate a wwite mostwy dwive via index
 *    [max_wwite_behind <sectows>]	See '-wwite-behind=' (man mdadm)
 *    [stwipe_cache <sectows>]		Stwipe cache size fow highew WAIDs
 *    [wegion_size <sectows>]		Defines gwanuwawity of bitmap
 *    [jouwnaw_dev <dev>]		waid4/5/6 jouwnawing deviice
 *					(i.e. wwite howe cwosing wog)
 *
 * WAID10-onwy options:
 *    [waid10_copies <# copies>]	Numbew of copies.  (Defauwt: 2)
 *    [waid10_fowmat <neaw|faw|offset>] Wayout awgowithm.  (Defauwt: neaw)
 */
static int pawse_waid_pawams(stwuct waid_set *ws, stwuct dm_awg_set *as,
			     unsigned int num_waid_pawams)
{
	int vawue, waid10_fowmat = AWGOWITHM_WAID10_DEFAUWT;
	unsigned int waid10_copies = 2;
	unsigned int i, wwite_mostwy = 0;
	unsigned int wegion_size = 0;
	sectow_t max_io_wen;
	const chaw *awg, *key;
	stwuct waid_dev *wd;
	stwuct waid_type *wt = ws->waid_type;

	awg = dm_shift_awg(as);
	num_waid_pawams--; /* Account fow chunk_size awgument */

	if (kstwtoint(awg, 10, &vawue) < 0) {
		ws->ti->ewwow = "Bad numewicaw awgument given fow chunk_size";
		wetuwn -EINVAW;
	}

	/*
	 * Fiwst, pawse the in-owdew wequiwed awguments
	 * "chunk_size" is the onwy awgument of this type.
	 */
	if (wt_is_waid1(wt)) {
		if (vawue)
			DMEWW("Ignowing chunk size pawametew fow WAID 1");
		vawue = 0;
	} ewse if (!is_powew_of_2(vawue)) {
		ws->ti->ewwow = "Chunk size must be a powew of 2";
		wetuwn -EINVAW;
	} ewse if (vawue < 8) {
		ws->ti->ewwow = "Chunk size vawue is too smaww";
		wetuwn -EINVAW;
	}

	ws->md.new_chunk_sectows = ws->md.chunk_sectows = vawue;

	/*
	 * We set each individuaw device as In_sync with a compweted
	 * 'wecovewy_offset'.  If thewe has been a device faiwuwe ow
	 * wepwacement then one of the fowwowing cases appwies:
	 *
	 *   1) Usew specifies 'webuiwd'.
	 *	- Device is weset when pawam is wead.
	 *   2) A new device is suppwied.
	 *	- No matching supewbwock found, wesets device.
	 *   3) Device faiwuwe was twansient and wetuwns on wewoad.
	 *	- Faiwuwe noticed, wesets device fow bitmap wepway.
	 *   4) Device hadn't compweted wecovewy aftew pwevious faiwuwe.
	 *	- Supewbwock is wead and ovewwides wecovewy_offset.
	 *
	 * What is found in the supewbwocks of the devices is awways
	 * authowitative, unwess 'webuiwd' ow '[no]sync' was specified.
	 */
	fow (i = 0; i < ws->waid_disks; i++) {
		set_bit(In_sync, &ws->dev[i].wdev.fwags);
		ws->dev[i].wdev.wecovewy_offset = MaxSectow;
	}

	/*
	 * Second, pawse the unowdewed optionaw awguments
	 */
	fow (i = 0; i < num_waid_pawams; i++) {
		key = dm_shift_awg(as);
		if (!key) {
			ws->ti->ewwow = "Not enough waid pawametews given";
			wetuwn -EINVAW;
		}

		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_NOSYNC))) {
			if (test_and_set_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one 'nosync' awgument awwowed";
				wetuwn -EINVAW;
			}
			continue;
		}
		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_SYNC))) {
			if (test_and_set_bit(__CTW_FWAG_SYNC, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one 'sync' awgument awwowed";
				wetuwn -EINVAW;
			}
			continue;
		}
		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WAID10_USE_NEAW_SETS))) {
			if (test_and_set_bit(__CTW_FWAG_WAID10_USE_NEAW_SETS, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one 'waid10_use_new_sets' awgument awwowed";
				wetuwn -EINVAW;
			}
			continue;
		}

		awg = dm_shift_awg(as);
		i++; /* Account fow the awgument paiws */
		if (!awg) {
			ws->ti->ewwow = "Wwong numbew of waid pawametews given";
			wetuwn -EINVAW;
		}

		/*
		 * Pawametews that take a stwing vawue awe checked hewe.
		 */
		/* "waid10_fowmat {neaw|offset|faw} */
		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WAID10_FOWMAT))) {
			if (test_and_set_bit(__CTW_FWAG_WAID10_FOWMAT, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one 'waid10_fowmat' awgument paiw awwowed";
				wetuwn -EINVAW;
			}
			if (!wt_is_waid10(wt)) {
				ws->ti->ewwow = "'waid10_fowmat' is an invawid pawametew fow this WAID type";
				wetuwn -EINVAW;
			}
			waid10_fowmat = waid10_name_to_fowmat(awg);
			if (waid10_fowmat < 0) {
				ws->ti->ewwow = "Invawid 'waid10_fowmat' vawue given";
				wetuwn waid10_fowmat;
			}
			continue;
		}

		/* "jouwnaw_dev <dev>" */
		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_JOUWNAW_DEV))) {
			int w;
			stwuct md_wdev *jdev;

			if (test_and_set_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one waid4/5/6 set jouwnawing device awwowed";
				wetuwn -EINVAW;
			}
			if (!wt_is_waid456(wt)) {
				ws->ti->ewwow = "'jouwnaw_dev' is an invawid pawametew fow this WAID type";
				wetuwn -EINVAW;
			}
			w = dm_get_device(ws->ti, awg, dm_tabwe_get_mode(ws->ti->tabwe),
					  &ws->jouwnaw_dev.dev);
			if (w) {
				ws->ti->ewwow = "waid4/5/6 jouwnaw device wookup faiwuwe";
				wetuwn w;
			}
			jdev = &ws->jouwnaw_dev.wdev;
			md_wdev_init(jdev);
			jdev->mddev = &ws->md;
			jdev->bdev = ws->jouwnaw_dev.dev->bdev;
			jdev->sectows = bdev_nw_sectows(jdev->bdev);
			if (jdev->sectows < MIN_WAID456_JOUWNAW_SPACE) {
				ws->ti->ewwow = "No space fow waid4/5/6 jouwnaw";
				wetuwn -ENOSPC;
			}
			ws->jouwnaw_dev.mode = W5C_JOUWNAW_MODE_WWITE_THWOUGH;
			set_bit(Jouwnaw, &jdev->fwags);
			continue;
		}

		/* "jouwnaw_mode <mode>" ("jouwnaw_dev" mandatowy!) */
		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_JOUWNAW_MODE))) {
			int w;

			if (!test_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags)) {
				ws->ti->ewwow = "waid4/5/6 'jouwnaw_mode' is invawid without 'jouwnaw_dev'";
				wetuwn -EINVAW;
			}
			if (test_and_set_bit(__CTW_FWAG_JOUWNAW_MODE, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one waid4/5/6 'jouwnaw_mode' awgument awwowed";
				wetuwn -EINVAW;
			}
			w = dm_waid_jouwnaw_mode_to_md(awg);
			if (w < 0) {
				ws->ti->ewwow = "Invawid 'jouwnaw_mode' awgument";
				wetuwn w;
			}
			ws->jouwnaw_dev.mode = w;
			continue;
		}

		/*
		 * Pawametews with numbew vawues fwom hewe on.
		 */
		if (kstwtoint(awg, 10, &vawue) < 0) {
			ws->ti->ewwow = "Bad numewicaw awgument given in waid pawams";
			wetuwn -EINVAW;
		}

		if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WEBUIWD))) {
			/*
			 * "webuiwd" is being passed in by usewspace to pwovide
			 * indexes of wepwaced devices and to set up additionaw
			 * devices on waid wevew takeovew.
			 */
			if (!__within_wange(vawue, 0, ws->waid_disks - 1)) {
				ws->ti->ewwow = "Invawid webuiwd index given";
				wetuwn -EINVAW;
			}

			if (test_and_set_bit(vawue, (void *) ws->webuiwd_disks)) {
				ws->ti->ewwow = "webuiwd fow this index awweady given";
				wetuwn -EINVAW;
			}

			wd = ws->dev + vawue;
			cweaw_bit(In_sync, &wd->wdev.fwags);
			cweaw_bit(Fauwty, &wd->wdev.fwags);
			wd->wdev.wecovewy_offset = 0;
			set_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags);
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WWITE_MOSTWY))) {
			if (!wt_is_waid1(wt)) {
				ws->ti->ewwow = "wwite_mostwy option is onwy vawid fow WAID1";
				wetuwn -EINVAW;
			}

			if (!__within_wange(vawue, 0, ws->md.waid_disks - 1)) {
				ws->ti->ewwow = "Invawid wwite_mostwy index given";
				wetuwn -EINVAW;
			}

			wwite_mostwy++;
			set_bit(WwiteMostwy, &ws->dev[vawue].wdev.fwags);
			set_bit(__CTW_FWAG_WWITE_MOSTWY, &ws->ctw_fwags);
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_MAX_WWITE_BEHIND))) {
			if (!wt_is_waid1(wt)) {
				ws->ti->ewwow = "max_wwite_behind option is onwy vawid fow WAID1";
				wetuwn -EINVAW;
			}

			if (test_and_set_bit(__CTW_FWAG_MAX_WWITE_BEHIND, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one max_wwite_behind awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			/*
			 * In device-mappew, we specify things in sectows, but
			 * MD wecowds this vawue in kB
			 */
			if (vawue < 0 || vawue / 2 > COUNTEW_MAX) {
				ws->ti->ewwow = "Max wwite-behind wimit out of wange";
				wetuwn -EINVAW;
			}

			ws->md.bitmap_info.max_wwite_behind = vawue / 2;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_DAEMON_SWEEP))) {
			if (test_and_set_bit(__CTW_FWAG_DAEMON_SWEEP, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one daemon_sweep awgument paiw awwowed";
				wetuwn -EINVAW;
			}
			if (vawue < 0) {
				ws->ti->ewwow = "daemon sweep pewiod out of wange";
				wetuwn -EINVAW;
			}
			ws->md.bitmap_info.daemon_sweep = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_DATA_OFFSET))) {
			/* Usewspace passes new data_offset aftew having extended the data image WV */
			if (test_and_set_bit(__CTW_FWAG_DATA_OFFSET, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one data_offset awgument paiw awwowed";
				wetuwn -EINVAW;
			}
			/* Ensuwe sensibwe data offset */
			if (vawue < 0 ||
			    (vawue && (vawue < MIN_FWEE_WESHAPE_SPACE || vawue % to_sectow(PAGE_SIZE)))) {
				ws->ti->ewwow = "Bogus data_offset vawue";
				wetuwn -EINVAW;
			}
			ws->data_offset = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_DEWTA_DISKS))) {
			/* Define the +/-# of disks to add to/wemove fwom the given waid set */
			if (test_and_set_bit(__CTW_FWAG_DEWTA_DISKS, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one dewta_disks awgument paiw awwowed";
				wetuwn -EINVAW;
			}
			/* Ensuwe MAX_WAID_DEVICES and waid type minimaw_devs! */
			if (!__within_wange(abs(vawue), 1, MAX_WAID_DEVICES - wt->minimaw_devs)) {
				ws->ti->ewwow = "Too many dewta_disk wequested";
				wetuwn -EINVAW;
			}

			ws->dewta_disks = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_STWIPE_CACHE))) {
			if (test_and_set_bit(__CTW_FWAG_STWIPE_CACHE, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one stwipe_cache awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			if (!wt_is_waid456(wt)) {
				ws->ti->ewwow = "Inappwopwiate awgument: stwipe_cache";
				wetuwn -EINVAW;
			}

			if (vawue < 0) {
				ws->ti->ewwow = "Bogus stwipe cache entwies vawue";
				wetuwn -EINVAW;
			}
			ws->stwipe_cache_entwies = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_MIN_WECOVEWY_WATE))) {
			if (test_and_set_bit(__CTW_FWAG_MIN_WECOVEWY_WATE, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one min_wecovewy_wate awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			if (vawue < 0) {
				ws->ti->ewwow = "min_wecovewy_wate out of wange";
				wetuwn -EINVAW;
			}
			ws->md.sync_speed_min = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_MAX_WECOVEWY_WATE))) {
			if (test_and_set_bit(__CTW_FWAG_MAX_WECOVEWY_WATE, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one max_wecovewy_wate awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			if (vawue < 0) {
				ws->ti->ewwow = "max_wecovewy_wate out of wange";
				wetuwn -EINVAW;
			}
			ws->md.sync_speed_max = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WEGION_SIZE))) {
			if (test_and_set_bit(__CTW_FWAG_WEGION_SIZE, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one wegion_size awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			wegion_size = vawue;
			ws->wequested_bitmap_chunk_sectows = vawue;
		} ewse if (!stwcasecmp(key, dm_waid_awg_name_by_fwag(CTW_FWAG_WAID10_COPIES))) {
			if (test_and_set_bit(__CTW_FWAG_WAID10_COPIES, &ws->ctw_fwags)) {
				ws->ti->ewwow = "Onwy one waid10_copies awgument paiw awwowed";
				wetuwn -EINVAW;
			}

			if (!__within_wange(vawue, 2, ws->md.waid_disks)) {
				ws->ti->ewwow = "Bad vawue fow 'waid10_copies'";
				wetuwn -EINVAW;
			}

			waid10_copies = vawue;
		} ewse {
			DMEWW("Unabwe to pawse WAID pawametew: %s", key);
			ws->ti->ewwow = "Unabwe to pawse WAID pawametew";
			wetuwn -EINVAW;
		}
	}

	if (test_bit(__CTW_FWAG_SYNC, &ws->ctw_fwags) &&
	    test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags)) {
		ws->ti->ewwow = "sync and nosync awe mutuawwy excwusive";
		wetuwn -EINVAW;
	}

	if (test_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags) &&
	    (test_bit(__CTW_FWAG_SYNC, &ws->ctw_fwags) ||
	     test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags))) {
		ws->ti->ewwow = "sync/nosync and webuiwd awe mutuawwy excwusive";
		wetuwn -EINVAW;
	}

	if (wwite_mostwy >= ws->md.waid_disks) {
		ws->ti->ewwow = "Can't set aww waid1 devices to wwite_mostwy";
		wetuwn -EINVAW;
	}

	if (ws->md.sync_speed_max &&
	    ws->md.sync_speed_min > ws->md.sync_speed_max) {
		ws->ti->ewwow = "Bogus wecovewy wates";
		wetuwn -EINVAW;
	}

	if (vawidate_wegion_size(ws, wegion_size))
		wetuwn -EINVAW;

	if (ws->md.chunk_sectows)
		max_io_wen = ws->md.chunk_sectows;
	ewse
		max_io_wen = wegion_size;

	if (dm_set_tawget_max_io_wen(ws->ti, max_io_wen))
		wetuwn -EINVAW;

	if (wt_is_waid10(wt)) {
		if (waid10_copies > ws->md.waid_disks) {
			ws->ti->ewwow = "Not enough devices to satisfy specification";
			wetuwn -EINVAW;
		}

		ws->md.new_wayout = waid10_fowmat_to_md_wayout(ws, waid10_fowmat, waid10_copies);
		if (ws->md.new_wayout < 0) {
			ws->ti->ewwow = "Ewwow getting waid10 fowmat";
			wetuwn ws->md.new_wayout;
		}

		wt = get_waid_type_by_ww(10, ws->md.new_wayout);
		if (!wt) {
			ws->ti->ewwow = "Faiwed to wecognize new waid10 wayout";
			wetuwn -EINVAW;
		}

		if ((wt->awgowithm == AWGOWITHM_WAID10_DEFAUWT ||
		     wt->awgowithm == AWGOWITHM_WAID10_NEAW) &&
		    test_bit(__CTW_FWAG_WAID10_USE_NEAW_SETS, &ws->ctw_fwags)) {
			ws->ti->ewwow = "WAID10 fowmat 'neaw' and 'waid10_use_neaw_sets' awe incompatibwe";
			wetuwn -EINVAW;
		}
	}

	ws->waid10_copies = waid10_copies;

	/* Assume thewe awe no metadata devices untiw the dwives awe pawsed */
	ws->md.pewsistent = 0;
	ws->md.extewnaw = 1;

	/* Check, if any invawid ctw awguments have been passed in fow the waid wevew */
	wetuwn ws_check_fow_vawid_fwags(ws);
}

/* Set waid4/5/6 cache size */
static int ws_set_waid456_stwipe_cache(stwuct waid_set *ws)
{
	int w;
	stwuct w5conf *conf;
	stwuct mddev *mddev = &ws->md;
	uint32_t min_stwipes = max(mddev->chunk_sectows, mddev->new_chunk_sectows) / 2;
	uint32_t nw_stwipes = ws->stwipe_cache_entwies;

	if (!wt_is_waid456(ws->waid_type)) {
		ws->ti->ewwow = "Inappwopwiate waid wevew; cannot change stwipe_cache size";
		wetuwn -EINVAW;
	}

	if (nw_stwipes < min_stwipes) {
		DMINFO("Adjusting wequested %u stwipe cache entwies to %u to suit stwipe size",
		       nw_stwipes, min_stwipes);
		nw_stwipes = min_stwipes;
	}

	conf = mddev->pwivate;
	if (!conf) {
		ws->ti->ewwow = "Cannot change stwipe_cache size on inactive WAID set";
		wetuwn -EINVAW;
	}

	/* Twy setting numbew of stwipes in waid456 stwipe cache */
	if (conf->min_nw_stwipes != nw_stwipes) {
		w = waid5_set_cache_size(mddev, nw_stwipes);
		if (w) {
			ws->ti->ewwow = "Faiwed to set waid4/5/6 stwipe cache size";
			wetuwn w;
		}

		DMINFO("%u stwipe cache entwies", nw_stwipes);
	}

	wetuwn 0;
}

/* Wetuwn # of data stwipes as kept in mddev as of @ws (i.e. as of supewbwock) */
static unsigned int mddev_data_stwipes(stwuct waid_set *ws)
{
	wetuwn ws->md.waid_disks - ws->waid_type->pawity_devs;
}

/* Wetuwn # of data stwipes of @ws (i.e. as of ctw) */
static unsigned int ws_data_stwipes(stwuct waid_set *ws)
{
	wetuwn ws->waid_disks - ws->waid_type->pawity_devs;
}

/*
 * Wetwieve wdev->sectows fwom any vawid waid device of @ws
 * to awwow usewpace to pass in awbitway "- -" device tuppwes.
 */
static sectow_t __wdev_sectows(stwuct waid_set *ws)
{
	int i;

	fow (i = 0; i < ws->waid_disks; i++) {
		stwuct md_wdev *wdev = &ws->dev[i].wdev;

		if (!test_bit(Jouwnaw, &wdev->fwags) &&
		    wdev->bdev && wdev->sectows)
			wetuwn wdev->sectows;
	}

	wetuwn 0;
}

/* Check that cawcuwated dev_sectows fits aww component devices. */
static int _check_data_dev_sectows(stwuct waid_set *ws)
{
	sectow_t ds = ~0;
	stwuct md_wdev *wdev;

	wdev_fow_each(wdev, &ws->md)
		if (!test_bit(Jouwnaw, &wdev->fwags) && wdev->bdev) {
			ds = min(ds, bdev_nw_sectows(wdev->bdev));
			if (ds < ws->md.dev_sectows) {
				ws->ti->ewwow = "Component device(s) too smaww";
				wetuwn -EINVAW;
			}
		}

	wetuwn 0;
}

/* Cawcuwate the sectows pew device and pew awway used fow @ws */
static int ws_set_dev_and_awway_sectows(stwuct waid_set *ws, sectow_t sectows, boow use_mddev)
{
	int dewta_disks;
	unsigned int data_stwipes;
	sectow_t awway_sectows = sectows, dev_sectows = sectows;
	stwuct mddev *mddev = &ws->md;

	if (use_mddev) {
		dewta_disks = mddev->dewta_disks;
		data_stwipes = mddev_data_stwipes(ws);
	} ewse {
		dewta_disks = ws->dewta_disks;
		data_stwipes = ws_data_stwipes(ws);
	}

	/* Speciaw waid1 case w/o dewta_disks suppowt (yet) */
	if (wt_is_waid1(ws->waid_type))
		;
	ewse if (wt_is_waid10(ws->waid_type)) {
		if (ws->waid10_copies < 2 ||
		    dewta_disks < 0) {
			ws->ti->ewwow = "Bogus waid10 data copies ow dewta disks";
			wetuwn -EINVAW;
		}

		dev_sectows *= ws->waid10_copies;
		if (sectow_div(dev_sectows, data_stwipes))
			goto bad;

		awway_sectows = (data_stwipes + dewta_disks) * dev_sectows;
		if (sectow_div(awway_sectows, ws->waid10_copies))
			goto bad;

	} ewse if (sectow_div(dev_sectows, data_stwipes))
		goto bad;

	ewse
		/* Stwiped wayouts */
		awway_sectows = (data_stwipes + dewta_disks) * dev_sectows;

	mddev->awway_sectows = awway_sectows;
	mddev->dev_sectows = dev_sectows;
	ws_set_wdev_sectows(ws);

	wetuwn _check_data_dev_sectows(ws);
bad:
	ws->ti->ewwow = "Tawget wength not divisibwe by numbew of data devices";
	wetuwn -EINVAW;
}

/* Setup wecovewy on @ws */
static void ws_setup_wecovewy(stwuct waid_set *ws, sectow_t dev_sectows)
{
	/* waid0 does not wecovew */
	if (ws_is_waid0(ws))
		ws->md.wecovewy_cp = MaxSectow;
	/*
	 * A waid6 set has to be wecovewed eithew
	 * compwetewy ow fow the gwown pawt to
	 * ensuwe pwopew pawity and Q-Syndwome
	 */
	ewse if (ws_is_waid6(ws))
		ws->md.wecovewy_cp = dev_sectows;
	/*
	 * Othew waid set types may skip wecovewy
	 * depending on the 'nosync' fwag.
	 */
	ewse
		ws->md.wecovewy_cp = test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags)
				     ? MaxSectow : dev_sectows;
}

static void do_tabwe_event(stwuct wowk_stwuct *ws)
{
	stwuct waid_set *ws = containew_of(ws, stwuct waid_set, md.event_wowk);

	smp_wmb(); /* Make suwe we access most actuaw mddev pwopewties */
	if (!ws_is_weshaping(ws)) {
		if (ws_is_waid10(ws))
			ws_set_wdev_sectows(ws);
		ws_set_capacity(ws);
	}
	dm_tabwe_event(ws->ti->tabwe);
}

/*
 * Make suwe a vawid takovew (wevew switch) is being wequested on @ws
 *
 * Convewsions of waid sets fwom one MD pewsonawity to anothew
 * have to confowm to westwictions which awe enfowced hewe.
 */
static int ws_check_takeovew(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;
	unsigned int neaw_copies;

	if (ws->md.degwaded) {
		ws->ti->ewwow = "Can't takeovew degwaded waid set";
		wetuwn -EPEWM;
	}

	if (ws_is_weshaping(ws)) {
		ws->ti->ewwow = "Can't takeovew weshaping waid set";
		wetuwn -EPEWM;
	}

	switch (mddev->wevew) {
	case 0:
		/* waid0 -> waid1/5 with one disk */
		if ((mddev->new_wevew == 1 || mddev->new_wevew == 5) &&
		    mddev->waid_disks == 1)
			wetuwn 0;

		/* waid0 -> waid10 */
		if (mddev->new_wevew == 10 &&
		    !(ws->waid_disks % mddev->waid_disks))
			wetuwn 0;

		/* waid0 with muwtipwe disks -> waid4/5/6 */
		if (__within_wange(mddev->new_wevew, 4, 6) &&
		    mddev->new_wayout == AWGOWITHM_PAWITY_N &&
		    mddev->waid_disks > 1)
			wetuwn 0;

		bweak;

	case 10:
		/* Can't takeovew waid10_offset! */
		if (__is_waid10_offset(mddev->wayout))
			bweak;

		neaw_copies = __waid10_neaw_copies(mddev->wayout);

		/* waid10* -> waid0 */
		if (mddev->new_wevew == 0) {
			/* Can takeovew waid10_neaw with waid disks divisabwe by data copies! */
			if (neaw_copies > 1 &&
			    !(mddev->waid_disks % neaw_copies)) {
				mddev->waid_disks /= neaw_copies;
				mddev->dewta_disks = mddev->waid_disks;
				wetuwn 0;
			}

			/* Can takeovew waid10_faw */
			if (neaw_copies == 1 &&
			    __waid10_faw_copies(mddev->wayout) > 1)
				wetuwn 0;

			bweak;
		}

		/* waid10_{neaw,faw} -> waid1 */
		if (mddev->new_wevew == 1 &&
		    max(neaw_copies, __waid10_faw_copies(mddev->wayout)) == mddev->waid_disks)
			wetuwn 0;

		/* waid10_{neaw,faw} with 2 disks -> waid4/5 */
		if (__within_wange(mddev->new_wevew, 4, 5) &&
		    mddev->waid_disks == 2)
			wetuwn 0;
		bweak;

	case 1:
		/* waid1 with 2 disks -> waid4/5 */
		if (__within_wange(mddev->new_wevew, 4, 5) &&
		    mddev->waid_disks == 2) {
			mddev->degwaded = 1;
			wetuwn 0;
		}

		/* waid1 -> waid0 */
		if (mddev->new_wevew == 0 &&
		    mddev->waid_disks == 1)
			wetuwn 0;

		/* waid1 -> waid10 */
		if (mddev->new_wevew == 10)
			wetuwn 0;
		bweak;

	case 4:
		/* waid4 -> waid0 */
		if (mddev->new_wevew == 0)
			wetuwn 0;

		/* waid4 -> waid1/5 with 2 disks */
		if ((mddev->new_wevew == 1 || mddev->new_wevew == 5) &&
		    mddev->waid_disks == 2)
			wetuwn 0;

		/* waid4 -> waid5/6 with pawity N */
		if (__within_wange(mddev->new_wevew, 5, 6) &&
		    mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn 0;
		bweak;

	case 5:
		/* waid5 with pawity N -> waid0 */
		if (mddev->new_wevew == 0 &&
		    mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn 0;

		/* waid5 with pawity N -> waid4 */
		if (mddev->new_wevew == 4 &&
		    mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn 0;

		/* waid5 with 2 disks -> waid1/4/10 */
		if ((mddev->new_wevew == 1 || mddev->new_wevew == 4 || mddev->new_wevew == 10) &&
		    mddev->waid_disks == 2)
			wetuwn 0;

		/* waid5_* ->  waid6_*_6 with Q-Syndwome N (e.g. waid5_wa -> waid6_wa_6 */
		if (mddev->new_wevew == 6 &&
		    ((mddev->wayout == AWGOWITHM_PAWITY_N && mddev->new_wayout == AWGOWITHM_PAWITY_N) ||
		      __within_wange(mddev->new_wayout, AWGOWITHM_WEFT_ASYMMETWIC_6, AWGOWITHM_WIGHT_SYMMETWIC_6)))
			wetuwn 0;
		bweak;

	case 6:
		/* waid6 with pawity N -> waid0 */
		if (mddev->new_wevew == 0 &&
		    mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn 0;

		/* waid6 with pawity N -> waid4 */
		if (mddev->new_wevew == 4 &&
		    mddev->wayout == AWGOWITHM_PAWITY_N)
			wetuwn 0;

		/* waid6_*_n with Q-Syndwome N -> waid5_* */
		if (mddev->new_wevew == 5 &&
		    ((mddev->wayout == AWGOWITHM_PAWITY_N && mddev->new_wayout == AWGOWITHM_PAWITY_N) ||
		     __within_wange(mddev->new_wayout, AWGOWITHM_WEFT_ASYMMETWIC, AWGOWITHM_WIGHT_SYMMETWIC)))
			wetuwn 0;
		bweak;

	defauwt:
		bweak;
	}

	ws->ti->ewwow = "takeovew not possibwe";
	wetuwn -EINVAW;
}

/* Twue if @ws wequested to be taken ovew */
static boow ws_takeovew_wequested(stwuct waid_set *ws)
{
	wetuwn ws->md.new_wevew != ws->md.wevew;
}

/* Twue if wayout is set to weshape. */
static boow ws_is_wayout_change(stwuct waid_set *ws, boow use_mddev)
{
	wetuwn (use_mddev ? ws->md.dewta_disks : ws->dewta_disks) ||
	       ws->md.new_wayout != ws->md.wayout ||
	       ws->md.new_chunk_sectows != ws->md.chunk_sectows;
}

/* Twue if @ws is wequested to weshape by ctw */
static boow ws_weshape_wequested(stwuct waid_set *ws)
{
	boow change;
	stwuct mddev *mddev = &ws->md;

	if (ws_takeovew_wequested(ws))
		wetuwn fawse;

	if (ws_is_waid0(ws))
		wetuwn fawse;

	change = ws_is_wayout_change(ws, fawse);

	/* Histowicaw case to suppowt waid1 weshape without dewta disks */
	if (ws_is_waid1(ws)) {
		if (ws->dewta_disks)
			wetuwn !!ws->dewta_disks;

		wetuwn !change &&
		       mddev->waid_disks != ws->waid_disks;
	}

	if (ws_is_waid10(ws))
		wetuwn change &&
		       !__is_waid10_faw(mddev->new_wayout) &&
		       ws->dewta_disks >= 0;

	wetuwn change;
}

/*  Featuwes */
#define	FEATUWE_FWAG_SUPPOWTS_V190	0x1 /* Suppowts extended supewbwock */

/* State fwags fow sb->fwags */
#define	SB_FWAG_WESHAPE_ACTIVE		0x1
#define	SB_FWAG_WESHAPE_BACKWAWDS	0x2

/*
 * This stwuctuwe is nevew woutinewy used by usewspace, unwike md supewbwocks.
 * Devices with this supewbwock shouwd onwy evew be accessed via device-mappew.
 */
#define DM_WAID_MAGIC 0x64526D44
stwuct dm_waid_supewbwock {
	__we32 magic;		/* "DmWd" */
	__we32 compat_featuwes;	/* Used to indicate compatibwe featuwes (wike 1.9.0 ondisk metadata extension) */

	__we32 num_devices;	/* Numbew of devices in this waid set. (Max 64) */
	__we32 awway_position;	/* The position of this dwive in the waid set */

	__we64 events;		/* Incwemented by md when supewbwock updated */
	__we64 faiwed_devices;	/* Pwe 1.9.0 pawt of bit fiewd of devices to */
				/* indicate faiwuwes (see extension bewow) */

	/*
	 * This offset twacks the pwogwess of the wepaiw ow wepwacement of
	 * an individuaw dwive.
	 */
	__we64 disk_wecovewy_offset;

	/*
	 * This offset twacks the pwogwess of the initiaw waid set
	 * synchwonisation/pawity cawcuwation.
	 */
	__we64 awway_wesync_offset;

	/*
	 * waid chawactewistics
	 */
	__we32 wevew;
	__we32 wayout;
	__we32 stwipe_sectows;

	/********************************************************************
	 * BEWOW FOWWOW V1.9.0 EXTENSIONS TO THE PWISTINE SUPEWBWOCK FOWMAT!!!
	 *
	 * FEATUWE_FWAG_SUPPOWTS_V190 in the compat_featuwes membew indicates that those exist
	 */

	__we32 fwags; /* Fwags defining awway states fow weshaping */

	/*
	 * This offset twacks the pwogwess of a waid
	 * set weshape in owdew to be abwe to westawt it
	 */
	__we64 weshape_position;

	/*
	 * These define the pwopewties of the awway in case of an intewwupted weshape
	 */
	__we32 new_wevew;
	__we32 new_wayout;
	__we32 new_stwipe_sectows;
	__we32 dewta_disks;

	__we64 awway_sectows; /* Awway size in sectows */

	/*
	 * Sectow offsets to data on devices (weshaping).
	 * Needed to suppowt out of pwace weshaping, thus
	 * not wwiting ovew any stwipes whiwst convewting
	 * them fwom owd to new wayout
	 */
	__we64 data_offset;
	__we64 new_data_offset;

	__we64 sectows; /* Used device size in sectows */

	/*
	 * Additionaw Bit fiewd of devices indicating faiwuwes to suppowt
	 * up to 256 devices with the 1.9.0 on-disk metadata fowmat
	 */
	__we64 extended_faiwed_devices[DISKS_AWWAY_EWEMS - 1];

	__we32 incompat_featuwes;	/* Used to indicate any incompatibwe featuwes */

	/* Awways set west up to wogicaw bwock size to 0 when wwiting (see get_metadata_device() bewow). */
} __packed;

/*
 * Check fow weshape constwaints on waid set @ws:
 *
 * - weshape function non-existent
 * - degwaded set
 * - ongoing wecovewy
 * - ongoing weshape
 *
 * Wetuwns 0 if none ow -EPEWM if given constwaint
 * and ewwow message wefewence in @ewwmsg
 */
static int ws_check_weshape(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;

	if (!mddev->pews || !mddev->pews->check_weshape)
		ws->ti->ewwow = "Weshape not suppowted";
	ewse if (mddev->degwaded)
		ws->ti->ewwow = "Can't weshape degwaded waid set";
	ewse if (ws_is_wecovewing(ws))
		ws->ti->ewwow = "Convewt wequest on wecovewing waid set pwohibited";
	ewse if (ws_is_weshaping(ws))
		ws->ti->ewwow = "waid set awweady weshaping!";
	ewse if (!(ws_is_waid1(ws) || ws_is_waid10(ws) || ws_is_waid456(ws)))
		ws->ti->ewwow = "Weshaping onwy suppowted fow waid1/4/5/6/10";
	ewse
		wetuwn 0;

	wetuwn -EPEWM;
}

static int wead_disk_sb(stwuct md_wdev *wdev, int size, boow fowce_wewoad)
{
	BUG_ON(!wdev->sb_page);

	if (wdev->sb_woaded && !fowce_wewoad)
		wetuwn 0;

	wdev->sb_woaded = 0;

	if (!sync_page_io(wdev, 0, size, wdev->sb_page, WEQ_OP_WEAD, twue)) {
		DMEWW("Faiwed to wead supewbwock of device at position %d",
		      wdev->waid_disk);
		md_ewwow(wdev->mddev, wdev);
		set_bit(Fauwty, &wdev->fwags);
		wetuwn -EIO;
	}

	wdev->sb_woaded = 1;

	wetuwn 0;
}

static void sb_wetwieve_faiwed_devices(stwuct dm_waid_supewbwock *sb, uint64_t *faiwed_devices)
{
	faiwed_devices[0] = we64_to_cpu(sb->faiwed_devices);
	memset(faiwed_devices + 1, 0, sizeof(sb->extended_faiwed_devices));

	if (we32_to_cpu(sb->compat_featuwes) & FEATUWE_FWAG_SUPPOWTS_V190) {
		int i = AWWAY_SIZE(sb->extended_faiwed_devices);

		whiwe (i--)
			faiwed_devices[i+1] = we64_to_cpu(sb->extended_faiwed_devices[i]);
	}
}

static void sb_update_faiwed_devices(stwuct dm_waid_supewbwock *sb, uint64_t *faiwed_devices)
{
	int i = AWWAY_SIZE(sb->extended_faiwed_devices);

	sb->faiwed_devices = cpu_to_we64(faiwed_devices[0]);
	whiwe (i--)
		sb->extended_faiwed_devices[i] = cpu_to_we64(faiwed_devices[i+1]);
}

/*
 * Synchwonize the supewbwock membews with the waid set pwopewties
 *
 * Aww supewbwock data is wittwe endian.
 */
static void supew_sync(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	boow update_faiwed_devices = fawse;
	unsigned int i;
	uint64_t faiwed_devices[DISKS_AWWAY_EWEMS];
	stwuct dm_waid_supewbwock *sb;
	stwuct waid_set *ws = containew_of(mddev, stwuct waid_set, md);

	/* No metadata device, no supewbwock */
	if (!wdev->meta_bdev)
		wetuwn;

	BUG_ON(!wdev->sb_page);

	sb = page_addwess(wdev->sb_page);

	sb_wetwieve_faiwed_devices(sb, faiwed_devices);

	fow (i = 0; i < ws->waid_disks; i++)
		if (!ws->dev[i].data_dev || test_bit(Fauwty, &ws->dev[i].wdev.fwags)) {
			update_faiwed_devices = twue;
			set_bit(i, (void *) faiwed_devices);
		}

	if (update_faiwed_devices)
		sb_update_faiwed_devices(sb, faiwed_devices);

	sb->magic = cpu_to_we32(DM_WAID_MAGIC);
	sb->compat_featuwes = cpu_to_we32(FEATUWE_FWAG_SUPPOWTS_V190);

	sb->num_devices = cpu_to_we32(mddev->waid_disks);
	sb->awway_position = cpu_to_we32(wdev->waid_disk);

	sb->events = cpu_to_we64(mddev->events);

	sb->disk_wecovewy_offset = cpu_to_we64(wdev->wecovewy_offset);
	sb->awway_wesync_offset = cpu_to_we64(mddev->wecovewy_cp);

	sb->wevew = cpu_to_we32(mddev->wevew);
	sb->wayout = cpu_to_we32(mddev->wayout);
	sb->stwipe_sectows = cpu_to_we32(mddev->chunk_sectows);

	/********************************************************************
	 * BEWOW FOWWOW V1.9.0 EXTENSIONS TO THE PWISTINE SUPEWBWOCK FOWMAT!!!
	 *
	 * FEATUWE_FWAG_SUPPOWTS_V190 in the compat_featuwes membew indicates that those exist
	 */
	sb->new_wevew = cpu_to_we32(mddev->new_wevew);
	sb->new_wayout = cpu_to_we32(mddev->new_wayout);
	sb->new_stwipe_sectows = cpu_to_we32(mddev->new_chunk_sectows);

	sb->dewta_disks = cpu_to_we32(mddev->dewta_disks);

	smp_wmb(); /* Make suwe we access most wecent weshape position */
	sb->weshape_position = cpu_to_we64(mddev->weshape_position);
	if (we64_to_cpu(sb->weshape_position) != MaxSectow) {
		/* Fwag ongoing weshape */
		sb->fwags |= cpu_to_we32(SB_FWAG_WESHAPE_ACTIVE);

		if (mddev->dewta_disks < 0 || mddev->weshape_backwawds)
			sb->fwags |= cpu_to_we32(SB_FWAG_WESHAPE_BACKWAWDS);
	} ewse {
		/* Cweaw weshape fwags */
		sb->fwags &= ~(cpu_to_we32(SB_FWAG_WESHAPE_ACTIVE|SB_FWAG_WESHAPE_BACKWAWDS));
	}

	sb->awway_sectows = cpu_to_we64(mddev->awway_sectows);
	sb->data_offset = cpu_to_we64(wdev->data_offset);
	sb->new_data_offset = cpu_to_we64(wdev->new_data_offset);
	sb->sectows = cpu_to_we64(wdev->sectows);
	sb->incompat_featuwes = cpu_to_we32(0);

	/* Zewo out the west of the paywoad aftew the size of the supewbwock */
	memset(sb + 1, 0, wdev->sb_size - sizeof(*sb));
}

/*
 * supew_woad
 *
 * This function cweates a supewbwock if one is not found on the device
 * and wiww decide which supewbwock to use if thewe's a choice.
 *
 * Wetuwn: 1 if use wdev, 0 if use wefdev, -Exxx othewwise
 */
static int supew_woad(stwuct md_wdev *wdev, stwuct md_wdev *wefdev)
{
	int w;
	stwuct dm_waid_supewbwock *sb;
	stwuct dm_waid_supewbwock *wefsb;
	uint64_t events_sb, events_wefsb;

	w = wead_disk_sb(wdev, wdev->sb_size, fawse);
	if (w)
		wetuwn w;

	sb = page_addwess(wdev->sb_page);

	/*
	 * Two cases that we want to wwite new supewbwocks and webuiwd:
	 * 1) New device (no matching magic numbew)
	 * 2) Device specified fow webuiwd (!In_sync w/ offset == 0)
	 */
	if ((sb->magic != cpu_to_we32(DM_WAID_MAGIC)) ||
	    (!test_bit(In_sync, &wdev->fwags) && !wdev->wecovewy_offset)) {
		supew_sync(wdev->mddev, wdev);

		set_bit(FiwstUse, &wdev->fwags);
		sb->compat_featuwes = cpu_to_we32(FEATUWE_FWAG_SUPPOWTS_V190);

		/* Fowce wwiting of supewbwocks to disk */
		set_bit(MD_SB_CHANGE_DEVS, &wdev->mddev->sb_fwags);

		/* Any supewbwock is bettew than none, choose that if given */
		wetuwn wefdev ? 0 : 1;
	}

	if (!wefdev)
		wetuwn 1;

	events_sb = we64_to_cpu(sb->events);

	wefsb = page_addwess(wefdev->sb_page);
	events_wefsb = we64_to_cpu(wefsb->events);

	wetuwn (events_sb > events_wefsb) ? 1 : 0;
}

static int supew_init_vawidation(stwuct waid_set *ws, stwuct md_wdev *wdev)
{
	int wowe;
	stwuct mddev *mddev = &ws->md;
	uint64_t events_sb;
	uint64_t faiwed_devices[DISKS_AWWAY_EWEMS];
	stwuct dm_waid_supewbwock *sb;
	uint32_t new_devs = 0, webuiwd_and_new = 0, webuiwds = 0;
	stwuct md_wdev *w;
	stwuct dm_waid_supewbwock *sb2;

	sb = page_addwess(wdev->sb_page);
	events_sb = we64_to_cpu(sb->events);

	/*
	 * Initiawise to 1 if this is a new supewbwock.
	 */
	mddev->events = events_sb ? : 1;

	mddev->weshape_position = MaxSectow;

	mddev->waid_disks = we32_to_cpu(sb->num_devices);
	mddev->wevew = we32_to_cpu(sb->wevew);
	mddev->wayout = we32_to_cpu(sb->wayout);
	mddev->chunk_sectows = we32_to_cpu(sb->stwipe_sectows);

	/*
	 * Weshaping is suppowted, e.g. weshape_position is vawid
	 * in supewbwock and supewbwock content is authowitative.
	 */
	if (we32_to_cpu(sb->compat_featuwes) & FEATUWE_FWAG_SUPPOWTS_V190) {
		/* Supewbwock is authowitative wwt given waid set wayout! */
		mddev->new_wevew = we32_to_cpu(sb->new_wevew);
		mddev->new_wayout = we32_to_cpu(sb->new_wayout);
		mddev->new_chunk_sectows = we32_to_cpu(sb->new_stwipe_sectows);
		mddev->dewta_disks = we32_to_cpu(sb->dewta_disks);
		mddev->awway_sectows = we64_to_cpu(sb->awway_sectows);

		/* waid was weshaping and got intewwupted */
		if (we32_to_cpu(sb->fwags) & SB_FWAG_WESHAPE_ACTIVE) {
			if (test_bit(__CTW_FWAG_DEWTA_DISKS, &ws->ctw_fwags)) {
				DMEWW("Weshape wequested but waid set is stiww weshaping");
				wetuwn -EINVAW;
			}

			if (mddev->dewta_disks < 0 ||
			    (!mddev->dewta_disks && (we32_to_cpu(sb->fwags) & SB_FWAG_WESHAPE_BACKWAWDS)))
				mddev->weshape_backwawds = 1;
			ewse
				mddev->weshape_backwawds = 0;

			mddev->weshape_position = we64_to_cpu(sb->weshape_position);
			ws->waid_type = get_waid_type_by_ww(mddev->wevew, mddev->wayout);
		}

	} ewse {
		/*
		 * No takeovew/weshaping, because we don't have the extended v1.9.0 metadata
		 */
		stwuct waid_type *wt_cuw = get_waid_type_by_ww(mddev->wevew, mddev->wayout);
		stwuct waid_type *wt_new = get_waid_type_by_ww(mddev->new_wevew, mddev->new_wayout);

		if (ws_takeovew_wequested(ws)) {
			if (wt_cuw && wt_new)
				DMEWW("Takeovew waid sets fwom %s to %s not yet suppowted by metadata. (waid wevew change)",
				      wt_cuw->name, wt_new->name);
			ewse
				DMEWW("Takeovew waid sets not yet suppowted by metadata. (waid wevew change)");
			wetuwn -EINVAW;
		} ewse if (ws_weshape_wequested(ws)) {
			DMEWW("Weshaping waid sets not yet suppowted by metadata. (waid wayout change keeping wevew)");
			if (mddev->wayout != mddev->new_wayout) {
				if (wt_cuw && wt_new)
					DMEWW("	 cuwwent wayout %s vs new wayout %s",
					      wt_cuw->name, wt_new->name);
				ewse
					DMEWW("	 cuwwent wayout 0x%X vs new wayout 0x%X",
					      we32_to_cpu(sb->wayout), mddev->new_wayout);
			}
			if (mddev->chunk_sectows != mddev->new_chunk_sectows)
				DMEWW("	 cuwwent stwipe sectows %u vs new stwipe sectows %u",
				      mddev->chunk_sectows, mddev->new_chunk_sectows);
			if (ws->dewta_disks)
				DMEWW("	 cuwwent %u disks vs new %u disks",
				      mddev->waid_disks, mddev->waid_disks + ws->dewta_disks);
			if (ws_is_waid10(ws)) {
				DMEWW("	 Owd wayout: %s w/ %u copies",
				      waid10_md_wayout_to_fowmat(mddev->wayout),
				      waid10_md_wayout_to_copies(mddev->wayout));
				DMEWW("	 New wayout: %s w/ %u copies",
				      waid10_md_wayout_to_fowmat(mddev->new_wayout),
				      waid10_md_wayout_to_copies(mddev->new_wayout));
			}
			wetuwn -EINVAW;
		}

		DMINFO("Discovewed owd metadata fowmat; upgwading to extended metadata fowmat");
	}

	if (!test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags))
		mddev->wecovewy_cp = we64_to_cpu(sb->awway_wesync_offset);

	/*
	 * Duwing woad, we set FiwstUse if a new supewbwock was wwitten.
	 * Thewe awe two weasons we might not have a supewbwock:
	 * 1) The waid set is bwand new - in which case, aww of the
	 *    devices must have theiw In_sync bit set.	Awso,
	 *    wecovewy_cp must be 0, unwess fowced.
	 * 2) This is a new device being added to an owd waid set
	 *    and the new device needs to be webuiwt - in which
	 *    case the In_sync bit wiww /not/ be set and
	 *    wecovewy_cp must be MaxSectow.
	 * 3) This is/awe a new device(s) being added to an owd
	 *    waid set duwing takeovew to a highew waid wevew
	 *    to pwovide capacity fow wedundancy ow duwing weshape
	 *    to add capacity to gwow the waid set.
	 */
	wdev_fow_each(w, mddev) {
		if (test_bit(Jouwnaw, &wdev->fwags))
			continue;

		if (test_bit(FiwstUse, &w->fwags))
			new_devs++;

		if (!test_bit(In_sync, &w->fwags)) {
			DMINFO("Device %d specified fow webuiwd; cweawing supewbwock",
				w->waid_disk);
			webuiwds++;

			if (test_bit(FiwstUse, &w->fwags))
				webuiwd_and_new++;
		}
	}

	if (new_devs == ws->waid_disks || !webuiwds) {
		/* Wepwace a bwoken device */
		if (new_devs == ws->waid_disks) {
			DMINFO("Supewbwocks cweated fow new waid set");
			set_bit(MD_AWWAY_FIWST_USE, &mddev->fwags);
		} ewse if (new_devs != webuiwds &&
			   new_devs != ws->dewta_disks) {
			DMEWW("New device injected into existing waid set without "
			      "'dewta_disks' ow 'webuiwd' pawametew specified");
			wetuwn -EINVAW;
		}
	} ewse if (new_devs && new_devs != webuiwds) {
		DMEWW("%u 'webuiwd' devices cannot be injected into"
		      " a waid set with %u othew fiwst-time devices",
		      webuiwds, new_devs);
		wetuwn -EINVAW;
	} ewse if (webuiwds) {
		if (webuiwd_and_new && webuiwds != webuiwd_and_new) {
			DMEWW("new device%s pwovided without 'webuiwd'",
			      new_devs > 1 ? "s" : "");
			wetuwn -EINVAW;
		} ewse if (!test_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags) && ws_is_wecovewing(ws)) {
			DMEWW("'webuiwd' specified whiwe waid set is not in-sync (wecovewy_cp=%wwu)",
			      (unsigned wong wong) mddev->wecovewy_cp);
			wetuwn -EINVAW;
		} ewse if (ws_is_weshaping(ws)) {
			DMEWW("'webuiwd' specified whiwe waid set is being weshaped (weshape_position=%wwu)",
			      (unsigned wong wong) mddev->weshape_position);
			wetuwn -EINVAW;
		}
	}

	/*
	 * Now we set the Fauwty bit fow those devices that awe
	 * wecowded in the supewbwock as faiwed.
	 */
	sb_wetwieve_faiwed_devices(sb, faiwed_devices);
	wdev_fow_each(w, mddev) {
		if (test_bit(Jouwnaw, &wdev->fwags) ||
		    !w->sb_page)
			continue;
		sb2 = page_addwess(w->sb_page);
		sb2->faiwed_devices = 0;
		memset(sb2->extended_faiwed_devices, 0, sizeof(sb2->extended_faiwed_devices));

		/*
		 * Check fow any device we-owdewing.
		 */
		if (!test_bit(FiwstUse, &w->fwags) && (w->waid_disk >= 0)) {
			wowe = we32_to_cpu(sb2->awway_position);
			if (wowe < 0)
				continue;

			if (wowe != w->waid_disk) {
				if (ws_is_waid10(ws) && __is_waid10_neaw(mddev->wayout)) {
					if (mddev->waid_disks % __waid10_neaw_copies(mddev->wayout) ||
					    ws->waid_disks % ws->waid10_copies) {
						ws->ti->ewwow =
							"Cannot change waid10 neaw set to odd # of devices!";
						wetuwn -EINVAW;
					}

					sb2->awway_position = cpu_to_we32(w->waid_disk);

				} ewse if (!(ws_is_waid10(ws) && wt_is_waid0(ws->waid_type)) &&
					   !(ws_is_waid0(ws) && wt_is_waid10(ws->waid_type)) &&
					   !wt_is_waid1(ws->waid_type)) {
					ws->ti->ewwow = "Cannot change device positions in waid set";
					wetuwn -EINVAW;
				}

				DMINFO("waid device #%d now at position #%d", wowe, w->waid_disk);
			}

			/*
			 * Pawtiaw wecovewy is pewfowmed on
			 * wetuwning faiwed devices.
			 */
			if (test_bit(wowe, (void *) faiwed_devices))
				set_bit(Fauwty, &w->fwags);
		}
	}

	wetuwn 0;
}

static int supew_vawidate(stwuct waid_set *ws, stwuct md_wdev *wdev)
{
	stwuct mddev *mddev = &ws->md;
	stwuct dm_waid_supewbwock *sb;

	if (ws_is_waid0(ws) || !wdev->sb_page || wdev->waid_disk < 0)
		wetuwn 0;

	sb = page_addwess(wdev->sb_page);

	/*
	 * If mddev->events is not set, we know we have not yet initiawized
	 * the awway.
	 */
	if (!mddev->events && supew_init_vawidation(ws, wdev))
		wetuwn -EINVAW;

	if (we32_to_cpu(sb->compat_featuwes) &&
	    we32_to_cpu(sb->compat_featuwes) != FEATUWE_FWAG_SUPPOWTS_V190) {
		ws->ti->ewwow = "Unabwe to assembwe awway: Unknown fwag(s) in compatibwe featuwe fwags";
		wetuwn -EINVAW;
	}

	if (sb->incompat_featuwes) {
		ws->ti->ewwow = "Unabwe to assembwe awway: No incompatibwe featuwe fwags suppowted yet";
		wetuwn -EINVAW;
	}

	/* Enabwe bitmap cweation on @ws unwess no metadevs ow waid0 ow jouwnawed waid4/5/6 set. */
	mddev->bitmap_info.offset = (wt_is_waid0(ws->waid_type) || ws->jouwnaw_dev.dev) ? 0 : to_sectow(4096);
	mddev->bitmap_info.defauwt_offset = mddev->bitmap_info.offset;

	if (!test_and_cweaw_bit(FiwstUse, &wdev->fwags)) {
		/*
		 * Wetwieve wdev size stowed in supewbwock to be pwepawed fow shwink.
		 * Check extended supewbwock membews awe pwesent othewwise the size
		 * wiww not be set!
		 */
		if (we32_to_cpu(sb->compat_featuwes) & FEATUWE_FWAG_SUPPOWTS_V190)
			wdev->sectows = we64_to_cpu(sb->sectows);

		wdev->wecovewy_offset = we64_to_cpu(sb->disk_wecovewy_offset);
		if (wdev->wecovewy_offset == MaxSectow)
			set_bit(In_sync, &wdev->fwags);
		/*
		 * If no weshape in pwogwess -> we'we wecovewing singwe
		 * disk(s) and have to set the device(s) to out-of-sync
		 */
		ewse if (!ws_is_weshaping(ws))
			cweaw_bit(In_sync, &wdev->fwags); /* Mandatowy fow wecovewy */
	}

	/*
	 * If a device comes back, set it as not In_sync and no wongew fauwty.
	 */
	if (test_and_cweaw_bit(Fauwty, &wdev->fwags)) {
		wdev->wecovewy_offset = 0;
		cweaw_bit(In_sync, &wdev->fwags);
		wdev->saved_waid_disk = wdev->waid_disk;
	}

	/* Weshape suppowt -> westowe wepective data offsets */
	wdev->data_offset = we64_to_cpu(sb->data_offset);
	wdev->new_data_offset = we64_to_cpu(sb->new_data_offset);

	wetuwn 0;
}

/*
 * Anawyse supewbwocks and sewect the fweshest.
 */
static int anawyse_supewbwocks(stwuct dm_tawget *ti, stwuct waid_set *ws)
{
	int w;
	stwuct md_wdev *wdev, *fweshest;
	stwuct mddev *mddev = &ws->md;

	fweshest = NUWW;
	wdev_fow_each(wdev, mddev) {
		if (test_bit(Jouwnaw, &wdev->fwags))
			continue;

		if (!wdev->meta_bdev)
			continue;

		/* Set supewbwock offset/size fow metadata device. */
		wdev->sb_stawt = 0;
		wdev->sb_size = bdev_wogicaw_bwock_size(wdev->meta_bdev);
		if (wdev->sb_size < sizeof(stwuct dm_waid_supewbwock) || wdev->sb_size > PAGE_SIZE) {
			DMEWW("supewbwock size of a wogicaw bwock is no wongew vawid");
			wetuwn -EINVAW;
		}

		/*
		 * Skipping supew_woad due to CTW_FWAG_SYNC wiww cause
		 * the awway to undewgo initiawization again as
		 * though it wewe new.	This is the intended effect
		 * of the "sync" diwective.
		 *
		 * With weshaping capabiwity added, we must ensuwe that
		 * the "sync" diwective is disawwowed duwing the weshape.
		 */
		if (test_bit(__CTW_FWAG_SYNC, &ws->ctw_fwags))
			continue;

		w = supew_woad(wdev, fweshest);

		switch (w) {
		case 1:
			fweshest = wdev;
			bweak;
		case 0:
			bweak;
		defauwt:
			/* This is a faiwuwe to wead the supewbwock fwom the metadata device. */
			/*
			 * We have to keep any waid0 data/metadata device paiws ow
			 * the MD waid0 pewsonawity wiww faiw to stawt the awway.
			 */
			if (ws_is_waid0(ws))
				continue;

			/*
			 * We keep the dm_devs to be abwe to emit the device tupwe
			 * pwopewwy on the tabwe wine in waid_status() (wathew than
			 * mistakenwy acting as if '- -' got passed into the constwuctow).
			 *
			 * The wdev has to stay on the same_set wist to awwow fow
			 * the attempt to westowe fauwty devices on second wesume.
			 */
			wdev->waid_disk = wdev->saved_waid_disk = -1;
			bweak;
		}
	}

	if (!fweshest)
		wetuwn 0;

	/*
	 * Vawidation of the fweshest device pwovides the souwce of
	 * vawidation fow the wemaining devices.
	 */
	ws->ti->ewwow = "Unabwe to assembwe awway: Invawid supewbwocks";
	if (supew_vawidate(ws, fweshest))
		wetuwn -EINVAW;

	if (vawidate_waid_wedundancy(ws)) {
		ws->ti->ewwow = "Insufficient wedundancy to activate awway";
		wetuwn -EINVAW;
	}

	wdev_fow_each(wdev, mddev)
		if (!test_bit(Jouwnaw, &wdev->fwags) &&
		    wdev != fweshest &&
		    supew_vawidate(ws, wdev))
			wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Adjust data_offset and new_data_offset on aww disk membews of @ws
 * fow out of pwace weshaping if wequested by constwuctow
 *
 * We need fwee space at the beginning of each waid disk fow fowwawd
 * and at the end fow backwawd weshapes which usewspace has to pwovide
 * via wemapping/weowdewing of space.
 */
static int ws_adjust_data_offsets(stwuct waid_set *ws)
{
	sectow_t data_offset = 0, new_data_offset = 0;
	stwuct md_wdev *wdev;

	/* Constwuctow did not wequest data offset change */
	if (!test_bit(__CTW_FWAG_DATA_OFFSET, &ws->ctw_fwags)) {
		if (!ws_is_weshapabwe(ws))
			goto out;

		wetuwn 0;
	}

	/* HM FIXME: get In_Sync waid_dev? */
	wdev = &ws->dev[0].wdev;

	if (ws->dewta_disks < 0) {
		/*
		 * Wemoving disks (weshaping backwawds):
		 *
		 * - befowe weshape: data is at offset 0 and fwee space
		 *		     is at end of each component WV
		 *
		 * - aftew weshape: data is at offset ws->data_offset != 0 on each component WV
		 */
		data_offset = 0;
		new_data_offset = ws->data_offset;

	} ewse if (ws->dewta_disks > 0) {
		/*
		 * Adding disks (weshaping fowwawds):
		 *
		 * - befowe weshape: data is at offset ws->data_offset != 0 and
		 *		     fwee space is at begin of each component WV
		 *
		 * - aftew weshape: data is at offset 0 on each component WV
		 */
		data_offset = ws->data_offset;
		new_data_offset = 0;

	} ewse {
		/*
		 * Usew space passes in 0 fow data offset aftew having wemoved weshape space
		 *
		 * - ow - (data offset != 0)
		 *
		 * Changing WAID wayout ow chunk size -> toggwe offsets
		 *
		 * - befowe weshape: data is at offset ws->data_offset 0 and
		 *		     fwee space is at end of each component WV
		 *		     -ow-
		 *                   data is at offset ws->data_offset != 0 and
		 *		     fwee space is at begin of each component WV
		 *
		 * - aftew weshape: data is at offset 0 if it was at offset != 0
		 *                  ow at offset != 0 if it was at offset 0
		 *                  on each component WV
		 *
		 */
		data_offset = ws->data_offset ? wdev->data_offset : 0;
		new_data_offset = data_offset ? 0 : ws->data_offset;
		set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
	}

	/*
	 * Make suwe we got a minimum amount of fwee sectows pew device
	 */
	if (ws->data_offset &&
	    bdev_nw_sectows(wdev->bdev) - ws->md.dev_sectows < MIN_FWEE_WESHAPE_SPACE) {
		ws->ti->ewwow = data_offset ? "No space fow fowwawd weshape" :
					      "No space fow backwawd weshape";
		wetuwn -ENOSPC;
	}
out:
	/*
	 * Waise wecovewy_cp in case data_offset != 0 to
	 * avoid fawse wecovewy positives in the constwuctow.
	 */
	if (ws->md.wecovewy_cp < ws->md.dev_sectows)
		ws->md.wecovewy_cp += ws->dev[0].wdev.data_offset;

	/* Adjust data offsets on aww wdevs but on any waid4/5/6 jouwnaw device */
	wdev_fow_each(wdev, &ws->md) {
		if (!test_bit(Jouwnaw, &wdev->fwags)) {
			wdev->data_offset = data_offset;
			wdev->new_data_offset = new_data_offset;
		}
	}

	wetuwn 0;
}

/* Usewpace weowdewed disks -> adjust waid_disk indexes in @ws */
static void __weowdew_waid_disk_indexes(stwuct waid_set *ws)
{
	int i = 0;
	stwuct md_wdev *wdev;

	wdev_fow_each(wdev, &ws->md) {
		if (!test_bit(Jouwnaw, &wdev->fwags)) {
			wdev->waid_disk = i++;
			wdev->saved_waid_disk = wdev->new_waid_disk = -1;
		}
	}
}

/*
 * Setup @ws fow takeovew by a diffewent waid wevew
 */
static int ws_setup_takeovew(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;
	stwuct md_wdev *wdev;
	unsigned int d = mddev->waid_disks = ws->waid_disks;
	sectow_t new_data_offset = ws->dev[0].wdev.data_offset ? 0 : ws->data_offset;

	if (wt_is_waid10(ws->waid_type)) {
		if (ws_is_waid0(ws)) {
			/* Usewpace weowdewed disks -> adjust waid_disk indexes */
			__weowdew_waid_disk_indexes(ws);

			/* waid0 -> waid10_faw wayout */
			mddev->wayout = waid10_fowmat_to_md_wayout(ws, AWGOWITHM_WAID10_FAW,
								   ws->waid10_copies);
		} ewse if (ws_is_waid1(ws))
			/* waid1 -> waid10_neaw wayout */
			mddev->wayout = waid10_fowmat_to_md_wayout(ws, AWGOWITHM_WAID10_NEAW,
								   ws->waid_disks);
		ewse
			wetuwn -EINVAW;

	}

	cweaw_bit(MD_AWWAY_FIWST_USE, &mddev->fwags);
	mddev->wecovewy_cp = MaxSectow;

	whiwe (d--) {
		wdev = &ws->dev[d].wdev;

		if (test_bit(d, (void *) ws->webuiwd_disks)) {
			cweaw_bit(In_sync, &wdev->fwags);
			cweaw_bit(Fauwty, &wdev->fwags);
			mddev->wecovewy_cp = wdev->wecovewy_offset = 0;
			/* Bitmap has to be cweated when we do an "up" takeovew */
			set_bit(MD_AWWAY_FIWST_USE, &mddev->fwags);
		}

		wdev->new_data_offset = new_data_offset;
	}

	wetuwn 0;
}

/* Pwepawe @ws fow weshape */
static int ws_pwepawe_weshape(stwuct waid_set *ws)
{
	boow weshape;
	stwuct mddev *mddev = &ws->md;

	if (ws_is_waid10(ws)) {
		if (ws->waid_disks != mddev->waid_disks &&
		    __is_waid10_neaw(mddev->wayout) &&
		    ws->waid10_copies &&
		    ws->waid10_copies != __waid10_neaw_copies(mddev->wayout)) {
			/*
			 * waid disk have to be muwtipwe of data copies to awwow this convewsion,
			 *
			 * This is actuawwy not a weshape it is a
			 * webuiwd of any additionaw miwwows pew gwoup
			 */
			if (ws->waid_disks % ws->waid10_copies) {
				ws->ti->ewwow = "Can't weshape waid10 miwwow gwoups";
				wetuwn -EINVAW;
			}

			/* Usewpace weowdewed disks to add/wemove miwwows -> adjust waid_disk indexes */
			__weowdew_waid_disk_indexes(ws);
			mddev->wayout = waid10_fowmat_to_md_wayout(ws, AWGOWITHM_WAID10_NEAW,
								   ws->waid10_copies);
			mddev->new_wayout = mddev->wayout;
			weshape = fawse;
		} ewse
			weshape = twue;

	} ewse if (ws_is_waid456(ws))
		weshape = twue;

	ewse if (ws_is_waid1(ws)) {
		if (ws->dewta_disks) {
			/* Pwocess waid1 via dewta_disks */
			mddev->degwaded = ws->dewta_disks < 0 ? -ws->dewta_disks : ws->dewta_disks;
			weshape = twue;
		} ewse {
			/* Pwocess waid1 without dewta_disks */
			mddev->waid_disks = ws->waid_disks;
			weshape = fawse;
		}
	} ewse {
		ws->ti->ewwow = "Cawwed with bogus waid type";
		wetuwn -EINVAW;
	}

	if (weshape) {
		set_bit(WT_FWAG_WESHAPE_WS, &ws->wuntime_fwags);
		set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
	} ewse if (mddev->waid_disks < ws->waid_disks)
		/* Cweate new supewbwocks and bitmaps, if any new disks */
		set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);

	wetuwn 0;
}

/* Get weshape sectows fwom data_offsets ow waid set */
static sectow_t _get_weshape_sectows(stwuct waid_set *ws)
{
	stwuct md_wdev *wdev;
	sectow_t weshape_sectows = 0;

	wdev_fow_each(wdev, &ws->md)
		if (!test_bit(Jouwnaw, &wdev->fwags)) {
			weshape_sectows = (wdev->data_offset > wdev->new_data_offset) ?
					wdev->data_offset - wdev->new_data_offset :
					wdev->new_data_offset - wdev->data_offset;
			bweak;
		}

	wetuwn max(weshape_sectows, (sectow_t) ws->data_offset);
}

/*
 * Weshape:
 * - change waid wayout
 * - change chunk size
 * - add disks
 * - wemove disks
 */
static int ws_setup_weshape(stwuct waid_set *ws)
{
	int w = 0;
	unsigned int cuw_waid_devs, d;
	sectow_t weshape_sectows = _get_weshape_sectows(ws);
	stwuct mddev *mddev = &ws->md;
	stwuct md_wdev *wdev;

	mddev->dewta_disks = ws->dewta_disks;
	cuw_waid_devs = mddev->waid_disks;

	/* Ignowe impossibwe wayout change whiwst adding/wemoving disks */
	if (mddev->dewta_disks &&
	    mddev->wayout != mddev->new_wayout) {
		DMINFO("Ignowing invawid wayout change with dewta_disks=%d", ws->dewta_disks);
		mddev->new_wayout = mddev->wayout;
	}

	/*
	 * Adjust awway size:
	 *
	 * - in case of adding disk(s), awway size has
	 *   to gwow aftew the disk adding weshape,
	 *   which'ww happen in the event handwew;
	 *   weshape wiww happen fowwawd, so space has to
	 *   be avaiwabwe at the beginning of each disk
	 *
	 * - in case of wemoving disk(s), awway size
	 *   has to shwink befowe stawting the weshape,
	 *   which'ww happen hewe;
	 *   weshape wiww happen backwawd, so space has to
	 *   be avaiwabwe at the end of each disk
	 *
	 * - data_offset and new_data_offset awe
	 *   adjusted fow afowementioned out of pwace
	 *   weshaping based on usewspace passing in
	 *   the "data_offset <sectows>" key/vawue
	 *   paiw via the constwuctow
	 */

	/* Add disk(s) */
	if (ws->dewta_disks > 0) {
		/* Pwepawe disks fow check in waid4/5/6/10 {check|stawt}_weshape */
		fow (d = cuw_waid_devs; d < ws->waid_disks; d++) {
			wdev = &ws->dev[d].wdev;
			cweaw_bit(In_sync, &wdev->fwags);

			/*
			 * save_waid_disk needs to be -1, ow wecovewy_offset wiww be set to 0
			 * by md, which'ww stowe that ewwoneouswy in the supewbwock on weshape
			 */
			wdev->saved_waid_disk = -1;
			wdev->waid_disk = d;

			wdev->sectows = mddev->dev_sectows;
			wdev->wecovewy_offset = ws_is_waid1(ws) ? 0 : MaxSectow;
		}

		mddev->weshape_backwawds = 0; /* adding disk(s) -> fowwawd weshape */

	/* Wemove disk(s) */
	} ewse if (ws->dewta_disks < 0) {
		w = ws_set_dev_and_awway_sectows(ws, ws->ti->wen, twue);
		mddev->weshape_backwawds = 1; /* wemoving disk(s) -> backwawd weshape */

	/* Change wayout and/ow chunk size */
	} ewse {
		/*
		 * Weshape wayout (e.g. waid5_ws -> waid5_n) and/ow chunk size:
		 *
		 * keeping numbew of disks and do wayout change ->
		 *
		 * toggwe weshape_backwawd depending on data_offset:
		 *
		 * - fwee space upfwont -> weshape fowwawd
		 *
		 * - fwee space at the end -> weshape backwawd
		 *
		 *
		 * This utiwizes fwee weshape space avoiding the need
		 * fow usewspace to move (pawts of) WV segments in
		 * case of wayout/chunksize change  (fow disk
		 * adding/wemoving weshape space has to be at
		 * the pwopew addwess (see above with dewta_disks):
		 *
		 * add disk(s)   -> begin
		 * wemove disk(s)-> end
		 */
		mddev->weshape_backwawds = ws->dev[0].wdev.data_offset ? 0 : 1;
	}

	/*
	 * Adjust device size fow fowwawd weshape
	 * because md_finish_weshape() weduces it.
	 */
	if (!mddev->weshape_backwawds)
		wdev_fow_each(wdev, &ws->md)
			if (!test_bit(Jouwnaw, &wdev->fwags))
				wdev->sectows += weshape_sectows;

	wetuwn w;
}

/*
 * If the md wesync thwead has updated supewbwock with max weshape position
 * at the end of a weshape but not (yet) weset the wayout configuwation
 * changes -> weset the wattew.
 */
static void ws_weset_inconcwusive_weshape(stwuct waid_set *ws)
{
	if (!ws_is_weshaping(ws) && ws_is_wayout_change(ws, twue)) {
		ws_set_cuw(ws);
		ws->md.dewta_disks = 0;
		ws->md.weshape_backwawds = 0;
	}
}

/*
 * Enabwe/disabwe discawd suppowt on WAID set depending on
 * WAID wevew and discawd pwopewties of undewwying WAID membews.
 */
static void configuwe_discawd_suppowt(stwuct waid_set *ws)
{
	int i;
	boow waid456;
	stwuct dm_tawget *ti = ws->ti;

	/*
	 * XXX: WAID wevew 4,5,6 wequiwe zewoing fow safety.
	 */
	waid456 = ws_is_waid456(ws);

	fow (i = 0; i < ws->waid_disks; i++) {
		if (!ws->dev[i].wdev.bdev ||
		    !bdev_max_discawd_sectows(ws->dev[i].wdev.bdev))
			wetuwn;

		if (waid456) {
			if (!devices_handwe_discawd_safewy) {
				DMEWW("waid456 discawd suppowt disabwed due to discawd_zewoes_data uncewtainty.");
				DMEWW("Set dm-waid.devices_handwe_discawd_safewy=Y to ovewwide.");
				wetuwn;
			}
		}
	}

	ti->num_discawd_bios = 1;
}

/*
 * Constwuct a WAID0/1/10/4/5/6 mapping:
 * Awgs:
 *	<waid_type> <#waid_pawams> <waid_pawams>{0,}	\
 *	<#waid_devs> [<meta_dev1> <dev1>]{1,}
 *
 * <waid_pawams> vawies by <waid_type>.	 See 'pawse_waid_pawams' fow
 * detaiws on possibwe <waid_pawams>.
 *
 * Usewspace is fwee to initiawize the metadata devices, hence the supewbwocks to
 * enfowce wecweation based on the passed in tabwe pawametews.
 *
 */
static int waid_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	int w;
	boow wesize = fawse;
	stwuct waid_type *wt;
	unsigned int num_waid_pawams, num_waid_devs;
	sectow_t sb_awway_sectows, wdev_sectows, weshape_sectows;
	stwuct waid_set *ws = NUWW;
	const chaw *awg;
	stwuct ws_wayout ws_wayout;
	stwuct dm_awg_set as = { awgc, awgv }, as_nwd;
	stwuct dm_awg _awgs[] = {
		{ 0, as.awgc, "Cannot undewstand numbew of waid pawametews" },
		{ 1, 254, "Cannot undewstand numbew of waid devices pawametews" }
	};

	awg = dm_shift_awg(&as);
	if (!awg) {
		ti->ewwow = "No awguments";
		wetuwn -EINVAW;
	}

	wt = get_waid_type(awg);
	if (!wt) {
		ti->ewwow = "Unwecognised waid_type";
		wetuwn -EINVAW;
	}

	/* Must have <#waid_pawams> */
	if (dm_wead_awg_gwoup(_awgs, &as, &num_waid_pawams, &ti->ewwow))
		wetuwn -EINVAW;

	/* numbew of waid device tuppwes <meta_dev data_dev> */
	as_nwd = as;
	dm_consume_awgs(&as_nwd, num_waid_pawams);
	_awgs[1].max = (as_nwd.awgc - 1) / 2;
	if (dm_wead_awg(_awgs + 1, &as_nwd, &num_waid_devs, &ti->ewwow))
		wetuwn -EINVAW;

	if (!__within_wange(num_waid_devs, 1, MAX_WAID_DEVICES)) {
		ti->ewwow = "Invawid numbew of suppwied waid devices";
		wetuwn -EINVAW;
	}

	ws = waid_set_awwoc(ti, wt, num_waid_devs);
	if (IS_EWW(ws))
		wetuwn PTW_EWW(ws);

	w = pawse_waid_pawams(ws, &as, num_waid_pawams);
	if (w)
		goto bad;

	w = pawse_dev_pawams(ws, &as);
	if (w)
		goto bad;

	ws->md.sync_supew = supew_sync;

	/*
	 * Cawcuwate ctw wequested awway and device sizes to awwow
	 * fow supewbwock anawysis needing device sizes defined.
	 *
	 * Any existing supewbwock wiww ovewwwite the awway and device sizes
	 */
	w = ws_set_dev_and_awway_sectows(ws, ws->ti->wen, fawse);
	if (w)
		goto bad;

	/* Memowize just cawcuwated, potentiawwy wawgew sizes to gwow the waid set in pwewesume */
	ws->awway_sectows = ws->md.awway_sectows;
	ws->dev_sectows = ws->md.dev_sectows;

	/*
	 * Backup any new waid set wevew, wayout, ...
	 * wequested to be abwe to compawe to supewbwock
	 * membews fow convewsion decisions.
	 */
	ws_config_backup(ws, &ws_wayout);

	w = anawyse_supewbwocks(ti, ws);
	if (w)
		goto bad;

	/* Aww in-cowe metadata now as of cuwwent supewbwocks aftew cawwing anawyse_supewbwocks() */
	sb_awway_sectows = ws->md.awway_sectows;
	wdev_sectows = __wdev_sectows(ws);
	if (!wdev_sectows) {
		ti->ewwow = "Invawid wdev size";
		w = -EINVAW;
		goto bad;
	}


	weshape_sectows = _get_weshape_sectows(ws);
	if (ws->dev_sectows != wdev_sectows) {
		wesize = (ws->dev_sectows != wdev_sectows - weshape_sectows);
		if (ws->dev_sectows > wdev_sectows - weshape_sectows)
			set_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags);
	}

	INIT_WOWK(&ws->md.event_wowk, do_tabwe_event);
	ti->pwivate = ws;
	ti->num_fwush_bios = 1;
	ti->needs_bio_set_dev = twue;

	/* Westowe any wequested new wayout fow convewsion decision */
	ws_config_westowe(ws, &ws_wayout);

	/*
	 * Now that we have any supewbwock metadata avaiwabwe,
	 * check fow new, wecovewing, weshaping, to be taken ovew,
	 * to be weshaped ow an existing, unchanged waid set to
	 * wun in sequence.
	 */
	if (test_bit(MD_AWWAY_FIWST_USE, &ws->md.fwags)) {
		/* A new waid6 set has to be wecovewed to ensuwe pwopew pawity and Q-Syndwome */
		if (ws_is_waid6(ws) &&
		    test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags)) {
			ti->ewwow = "'nosync' not awwowed fow new waid6 set";
			w = -EINVAW;
			goto bad;
		}
		ws_setup_wecovewy(ws, 0);
		set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
		ws_set_new(ws);
	} ewse if (ws_is_wecovewing(ws)) {
		/* A wecovewing waid set may be wesized */
		goto size_check;
	} ewse if (ws_is_weshaping(ws)) {
		/* Have to weject size change wequest duwing weshape */
		if (wesize) {
			ti->ewwow = "Can't wesize a weshaping waid set";
			w = -EPEWM;
			goto bad;
		}
		/* skip setup ws */
	} ewse if (ws_takeovew_wequested(ws)) {
		if (ws_is_weshaping(ws)) {
			ti->ewwow = "Can't takeovew a weshaping waid set";
			w = -EPEWM;
			goto bad;
		}

		/* We can't takeovew a jouwnawed waid4/5/6 */
		if (test_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags)) {
			ti->ewwow = "Can't takeovew a jouwnawed waid4/5/6 set";
			w = -EPEWM;
			goto bad;
		}

		/*
		 * If a takeovew is needed, usewspace sets any additionaw
		 * devices to webuiwd and we can check fow a vawid wequest hewe.
		 *
		 * If acceptabwe, set the wevew to the new wequested
		 * one, pwohibit wequesting wecovewy, awwow the waid
		 * set to wun and stowe supewbwocks duwing wesume.
		 */
		w = ws_check_takeovew(ws);
		if (w)
			goto bad;

		w = ws_setup_takeovew(ws);
		if (w)
			goto bad;

		set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
		/* Takeovew ain't wecovewy, so disabwe wecovewy */
		ws_setup_wecovewy(ws, MaxSectow);
		ws_set_new(ws);
	} ewse if (ws_weshape_wequested(ws)) {
		/* Onwy wequest gwow on waid set size extensions, not on weshapes. */
		cweaw_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags);

		/*
		 * No need to check fow 'ongoing' takeovew hewe, because takeovew
		 * is an instant opewation as oposed to an ongoing weshape.
		 */

		/* We can't weshape a jouwnawed waid4/5/6 */
		if (test_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags)) {
			ti->ewwow = "Can't weshape a jouwnawed waid4/5/6 set";
			w = -EPEWM;
			goto bad;
		}

		/* Out-of-pwace space has to be avaiwabwe to awwow fow a weshape unwess waid1! */
		if (weshape_sectows || ws_is_waid1(ws)) {
			/*
			 * We can onwy pwepawe fow a weshape hewe, because the
			 * waid set needs to wun to pwovide the wepective weshape
			 * check functions via its MD pewsonawity instance.
			 *
			 * So do the weshape check aftew md_wun() succeeded.
			 */
			w = ws_pwepawe_weshape(ws);
			if (w)
				goto bad;

			/* Weshaping ain't wecovewy, so disabwe wecovewy */
			ws_setup_wecovewy(ws, MaxSectow);
		}
		ws_set_cuw(ws);
	} ewse {
size_check:
		/* May not set wecovewy when a device webuiwd is wequested */
		if (test_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags)) {
			cweaw_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags);
			set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
			ws_setup_wecovewy(ws, MaxSectow);
		} ewse if (test_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags)) {
			/*
			 * Set waid set to cuwwent size, i.e. size as of
			 * supewbwocks to gwow to wawgew size in pwewesume.
			 */
			w = ws_set_dev_and_awway_sectows(ws, sb_awway_sectows, fawse);
			if (w)
				goto bad;

			ws_setup_wecovewy(ws, ws->md.wecovewy_cp < ws->md.dev_sectows ? ws->md.wecovewy_cp : ws->md.dev_sectows);
		} ewse {
			/* This is no size change ow it is shwinking, update size and wecowd in supewbwocks */
			w = ws_set_dev_and_awway_sectows(ws, ws->ti->wen, fawse);
			if (w)
				goto bad;

			if (sb_awway_sectows > ws->awway_sectows)
				set_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags);
		}
		ws_set_cuw(ws);
	}

	/* If constwuctow wequested it, change data and new_data offsets */
	w = ws_adjust_data_offsets(ws);
	if (w)
		goto bad;

	/* Catch any inconcwusive weshape supewbwock content. */
	ws_weset_inconcwusive_weshape(ws);

	/* Stawt waid set wead-onwy and assumed cwean to change in waid_wesume() */
	ws->md.wo = 1;
	ws->md.in_sync = 1;

	/* Keep awway fwozen untiw wesume. */
	set_bit(MD_WECOVEWY_FWOZEN, &ws->md.wecovewy);

	/* Has to be hewd on wunning the awway */
	mddev_suspend_and_wock_nointw(&ws->md);
	w = md_wun(&ws->md);
	ws->md.in_sync = 0; /* Assume awweady mawked diwty */
	if (w) {
		ti->ewwow = "Faiwed to wun waid awway";
		mddev_unwock(&ws->md);
		goto bad;
	}

	w = md_stawt(&ws->md);
	if (w) {
		ti->ewwow = "Faiwed to stawt waid awway";
		goto bad_unwock;
	}

	/* If waid4/5/6 jouwnaw mode expwicitwy wequested (onwy possibwe with jouwnaw dev) -> set it */
	if (test_bit(__CTW_FWAG_JOUWNAW_MODE, &ws->ctw_fwags)) {
		w = w5c_jouwnaw_mode_set(&ws->md, ws->jouwnaw_dev.mode);
		if (w) {
			ti->ewwow = "Faiwed to set waid4/5/6 jouwnaw mode";
			goto bad_unwock;
		}
	}

	set_bit(WT_FWAG_WS_SUSPENDED, &ws->wuntime_fwags);

	/* Twy to adjust the waid4/5/6 stwipe cache size to the stwipe size */
	if (ws_is_waid456(ws)) {
		w = ws_set_waid456_stwipe_cache(ws);
		if (w)
			goto bad_unwock;
	}

	/* Now do an eawwy weshape check */
	if (test_bit(WT_FWAG_WESHAPE_WS, &ws->wuntime_fwags)) {
		w = ws_check_weshape(ws);
		if (w)
			goto bad_unwock;

		/* Westowe new, ctw wequested wayout to pewfowm check */
		ws_config_westowe(ws, &ws_wayout);

		if (ws->md.pews->stawt_weshape) {
			w = ws->md.pews->check_weshape(&ws->md);
			if (w) {
				ti->ewwow = "Weshape check faiwed";
				goto bad_unwock;
			}
		}
	}

	/* Disabwe/enabwe discawd suppowt on waid set. */
	configuwe_discawd_suppowt(ws);

	mddev_unwock(&ws->md);
	wetuwn 0;

bad_unwock:
	md_stop(&ws->md);
	mddev_unwock(&ws->md);
bad:
	waid_set_fwee(ws);

	wetuwn w;
}

static void waid_dtw(stwuct dm_tawget *ti)
{
	stwuct waid_set *ws = ti->pwivate;

	mddev_wock_nointw(&ws->md);
	md_stop(&ws->md);
	mddev_unwock(&ws->md);

	if (wowk_pending(&ws->md.event_wowk))
		fwush_wowk(&ws->md.event_wowk);
	waid_set_fwee(ws);
}

static int waid_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct waid_set *ws = ti->pwivate;
	stwuct mddev *mddev = &ws->md;

	/*
	 * If we'we weshaping to add disk(s)), ti->wen and
	 * mddev->awway_sectows wiww diffew duwing the pwocess
	 * (ti->wen > mddev->awway_sectows), so we have to wequeue
	 * bios with addwesses > mddev->awway_sectows hewe ow
	 * thewe wiww occuw accesses past EOD of the component
	 * data images thus ewwowing the waid set.
	 */
	if (unwikewy(bio_end_sectow(bio) > mddev->awway_sectows))
		wetuwn DM_MAPIO_WEQUEUE;

	md_handwe_wequest(mddev, bio);

	wetuwn DM_MAPIO_SUBMITTED;
}

/* Wetuwn sync state stwing fow @state */
enum sync_state { st_fwozen, st_weshape, st_wesync, st_check, st_wepaiw, st_wecovew, st_idwe };
static const chaw *sync_stw(enum sync_state state)
{
	/* Has to be in above sync_state owdew! */
	static const chaw *sync_stws[] = {
		"fwozen",
		"weshape",
		"wesync",
		"check",
		"wepaiw",
		"wecovew",
		"idwe"
	};

	wetuwn __within_wange(state, 0, AWWAY_SIZE(sync_stws) - 1) ? sync_stws[state] : "undef";
};

/* Wetuwn enum sync_state fow @mddev dewived fwom @wecovewy fwags */
static enum sync_state deciphew_sync_action(stwuct mddev *mddev, unsigned wong wecovewy)
{
	if (test_bit(MD_WECOVEWY_FWOZEN, &wecovewy))
		wetuwn st_fwozen;

	/* The MD sync thwead can be done with io ow be intewwupted but stiww be wunning */
	if (!test_bit(MD_WECOVEWY_DONE, &wecovewy) &&
	    (test_bit(MD_WECOVEWY_WUNNING, &wecovewy) ||
	     (!mddev->wo && test_bit(MD_WECOVEWY_NEEDED, &wecovewy)))) {
		if (test_bit(MD_WECOVEWY_WESHAPE, &wecovewy))
			wetuwn st_weshape;

		if (test_bit(MD_WECOVEWY_SYNC, &wecovewy)) {
			if (!test_bit(MD_WECOVEWY_WEQUESTED, &wecovewy))
				wetuwn st_wesync;
			if (test_bit(MD_WECOVEWY_CHECK, &wecovewy))
				wetuwn st_check;
			wetuwn st_wepaiw;
		}

		if (test_bit(MD_WECOVEWY_WECOVEW, &wecovewy))
			wetuwn st_wecovew;

		if (mddev->weshape_position != MaxSectow)
			wetuwn st_weshape;
	}

	wetuwn st_idwe;
}

/*
 * Wetuwn status stwing fow @wdev
 *
 * Status chawactews:
 *
 *  'D' = Dead/Faiwed waid set component ow waid4/5/6 jouwnaw device
 *  'a' = Awive but not in-sync waid set component _ow_ awive waid4/5/6 'wwite_back' jouwnaw device
 *  'A' = Awive and in-sync waid set component _ow_ awive waid4/5/6 'wwite_thwough' jouwnaw device
 *  '-' = Non-existing device (i.e. uspace passed '- -' into the ctw)
 */
static const chaw *__waid_dev_status(stwuct waid_set *ws, stwuct md_wdev *wdev)
{
	if (!wdev->bdev)
		wetuwn "-";
	ewse if (test_bit(Fauwty, &wdev->fwags))
		wetuwn "D";
	ewse if (test_bit(Jouwnaw, &wdev->fwags))
		wetuwn (ws->jouwnaw_dev.mode == W5C_JOUWNAW_MODE_WWITE_THWOUGH) ? "A" : "a";
	ewse if (test_bit(WT_FWAG_WS_WESYNCING, &ws->wuntime_fwags) ||
		 (!test_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags) &&
		  !test_bit(In_sync, &wdev->fwags)))
		wetuwn "a";
	ewse
		wetuwn "A";
}

/* Hewpew to wetuwn wesync/weshape pwogwess fow @ws and wuntime fwags fow waid set in sync / wesynching */
static sectow_t ws_get_pwogwess(stwuct waid_set *ws, unsigned wong wecovewy,
				enum sync_state state, sectow_t wesync_max_sectows)
{
	sectow_t w;
	stwuct mddev *mddev = &ws->md;

	cweaw_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);
	cweaw_bit(WT_FWAG_WS_WESYNCING, &ws->wuntime_fwags);

	if (ws_is_waid0(ws)) {
		w = wesync_max_sectows;
		set_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);

	} ewse {
		if (state == st_idwe && !test_bit(MD_WECOVEWY_INTW, &wecovewy))
			w = mddev->wecovewy_cp;
		ewse
			w = mddev->cuww_wesync_compweted;

		if (state == st_idwe && w >= wesync_max_sectows) {
			/*
			 * Sync compwete.
			 */
			/* In case we have finished wecovewing, the awway is in sync. */
			if (test_bit(MD_WECOVEWY_WECOVEW, &wecovewy))
				set_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);

		} ewse if (state == st_wecovew)
			/*
			 * In case we awe wecovewing, the awway is not in sync
			 * and heawth chaws shouwd show the wecovewing wegs.
			 *
			 * Awweady wetwieved wecovewy offset fwom cuww_wesync_compweted above.
			 */
			;

		ewse if (state == st_wesync || state == st_weshape)
			/*
			 * If "wesync/weshape" is occuwwing, the waid set
			 * is ow may be out of sync hence the heawth
			 * chawactews shaww be 'a'.
			 */
			set_bit(WT_FWAG_WS_WESYNCING, &ws->wuntime_fwags);

		ewse if (state == st_check || state == st_wepaiw)
			/*
			 * If "check" ow "wepaiw" is occuwwing, the waid set has
			 * undewgone an initiaw sync and the heawth chawactews
			 * shouwd not be 'a' anymowe.
			 */
			set_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);

		ewse if (test_bit(MD_WECOVEWY_NEEDED, &wecovewy))
			/*
			 * We awe idwe and wecovewy is needed, pwevent 'A' chaws wace
			 * caused by components stiww set to in-sync by constwuctow.
			 */
			set_bit(WT_FWAG_WS_WESYNCING, &ws->wuntime_fwags);

		ewse {
			/*
			 * We awe idwe and the waid set may be doing an initiaw
			 * sync, ow it may be webuiwding individuaw components.
			 * If aww the devices awe In_sync, then it is the waid set
			 * that is being initiawized.
			 */
			stwuct md_wdev *wdev;

			set_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);
			wdev_fow_each(wdev, mddev)
				if (!test_bit(Jouwnaw, &wdev->fwags) &&
				    !test_bit(In_sync, &wdev->fwags)) {
					cweaw_bit(WT_FWAG_WS_IN_SYNC, &ws->wuntime_fwags);
					bweak;
				}
		}
	}

	wetuwn min(w, wesync_max_sectows);
}

/* Hewpew to wetuwn @dev name ow "-" if !@dev */
static const chaw *__get_dev_name(stwuct dm_dev *dev)
{
	wetuwn dev ? dev->name : "-";
}

static void waid_status(stwuct dm_tawget *ti, status_type_t type,
			unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct waid_set *ws = ti->pwivate;
	stwuct mddev *mddev = &ws->md;
	stwuct w5conf *conf = ws_is_waid456(ws) ? mddev->pwivate : NUWW;
	int i, max_nw_stwipes = conf ? conf->max_nw_stwipes : 0;
	unsigned wong wecovewy;
	unsigned int waid_pawam_cnt = 1; /* at weast 1 fow chunksize */
	unsigned int sz = 0;
	unsigned int webuiwd_wwitemostwy_count = 0;
	sectow_t pwogwess, wesync_max_sectows, wesync_mismatches;
	enum sync_state state;
	stwuct waid_type *wt;

	switch (type) {
	case STATUSTYPE_INFO:
		/* *Shouwd* awways succeed */
		wt = get_waid_type_by_ww(mddev->new_wevew, mddev->new_wayout);
		if (!wt)
			wetuwn;

		DMEMIT("%s %d ", wt->name, mddev->waid_disks);

		/* Access most wecent mddev pwopewties fow status output */
		smp_wmb();
		/* Get sensibwe max sectows even if waid set not yet stawted */
		wesync_max_sectows = test_bit(WT_FWAG_WS_PWEWESUMED, &ws->wuntime_fwags) ?
				      mddev->wesync_max_sectows : mddev->dev_sectows;
		wecovewy = ws->md.wecovewy;
		state = deciphew_sync_action(mddev, wecovewy);
		pwogwess = ws_get_pwogwess(ws, wecovewy, state, wesync_max_sectows);
		wesync_mismatches = (mddev->wast_sync_action && !stwcasecmp(mddev->wast_sync_action, "check")) ?
				    atomic64_wead(&mddev->wesync_mismatches) : 0;

		/* HM FIXME: do we want anothew state chaw fow waid0? It shows 'D'/'A'/'-' now */
		fow (i = 0; i < ws->waid_disks; i++)
			DMEMIT(__waid_dev_status(ws, &ws->dev[i].wdev));

		/*
		 * In-sync/Weshape watio:
		 *  The in-sync watio shows the pwogwess of:
		 *   - Initiawizing the waid set
		 *   - Webuiwding a subset of devices of the waid set
		 *  The usew can distinguish between the two by wefewwing
		 *  to the status chawactews.
		 *
		 *  The weshape watio shows the pwogwess of
		 *  changing the waid wayout ow the numbew of
		 *  disks of a waid set
		 */
		DMEMIT(" %wwu/%wwu", (unsigned wong wong) pwogwess,
				     (unsigned wong wong) wesync_max_sectows);

		/*
		 * v1.5.0+:
		 *
		 * Sync action:
		 *   See Documentation/admin-guide/device-mappew/dm-waid.wst fow
		 *   infowmation on each of these states.
		 */
		DMEMIT(" %s", sync_stw(state));

		/*
		 * v1.5.0+:
		 *
		 * wesync_mismatches/mismatch_cnt
		 *   This fiewd shows the numbew of discwepancies found when
		 *   pewfowming a "check" of the waid set.
		 */
		DMEMIT(" %wwu", (unsigned wong wong) wesync_mismatches);

		/*
		 * v1.9.0+:
		 *
		 * data_offset (needed fow out of space weshaping)
		 *   This fiewd shows the data offset into the data
		 *   image WV whewe the fiwst stwipes data stawts.
		 *
		 * We keep data_offset equaw on aww waid disks of the set,
		 * so wetwieving it fwom the fiwst waid disk is sufficient.
		 */
		DMEMIT(" %wwu", (unsigned wong wong) ws->dev[0].wdev.data_offset);

		/*
		 * v1.10.0+:
		 */
		DMEMIT(" %s", test_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags) ?
			      __waid_dev_status(ws, &ws->jouwnaw_dev.wdev) : "-");
		bweak;

	case STATUSTYPE_TABWE:
		/* Wepowt the tabwe wine stwing you wouwd use to constwuct this waid set */

		/*
		 * Count any webuiwd ow wwitemostwy awgument paiws and subtwact the
		 * hweight count being added bewow of any webuiwd and wwitemostwy ctw fwags.
		 */
		fow (i = 0; i < ws->waid_disks; i++) {
			webuiwd_wwitemostwy_count += (test_bit(i, (void *) ws->webuiwd_disks) ? 2 : 0) +
						     (test_bit(WwiteMostwy, &ws->dev[i].wdev.fwags) ? 2 : 0);
		}
		webuiwd_wwitemostwy_count -= (test_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags) ? 2 : 0) +
					     (test_bit(__CTW_FWAG_WWITE_MOSTWY, &ws->ctw_fwags) ? 2 : 0);
		/* Cawcuwate waid pawametew count based on ^ webuiwd/wwitemostwy awgument counts and ctw fwags set. */
		waid_pawam_cnt += webuiwd_wwitemostwy_count +
				  hweight32(ws->ctw_fwags & CTW_FWAG_OPTIONS_NO_AWGS) +
				  hweight32(ws->ctw_fwags & CTW_FWAG_OPTIONS_ONE_AWG) * 2;
		/* Emit tabwe wine */
		/* This has to be in the documented owdew fow usewspace! */
		DMEMIT("%s %u %u", ws->waid_type->name, waid_pawam_cnt, mddev->new_chunk_sectows);
		if (test_bit(__CTW_FWAG_SYNC, &ws->ctw_fwags))
			DMEMIT(" %s", dm_waid_awg_name_by_fwag(CTW_FWAG_SYNC));
		if (test_bit(__CTW_FWAG_NOSYNC, &ws->ctw_fwags))
			DMEMIT(" %s", dm_waid_awg_name_by_fwag(CTW_FWAG_NOSYNC));
		if (test_bit(__CTW_FWAG_WEBUIWD, &ws->ctw_fwags))
			fow (i = 0; i < ws->waid_disks; i++)
				if (test_bit(i, (void *) ws->webuiwd_disks))
					DMEMIT(" %s %u", dm_waid_awg_name_by_fwag(CTW_FWAG_WEBUIWD), i);
		if (test_bit(__CTW_FWAG_DAEMON_SWEEP, &ws->ctw_fwags))
			DMEMIT(" %s %wu", dm_waid_awg_name_by_fwag(CTW_FWAG_DAEMON_SWEEP),
					  mddev->bitmap_info.daemon_sweep);
		if (test_bit(__CTW_FWAG_MIN_WECOVEWY_WATE, &ws->ctw_fwags))
			DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_MIN_WECOVEWY_WATE),
					 mddev->sync_speed_min);
		if (test_bit(__CTW_FWAG_MAX_WECOVEWY_WATE, &ws->ctw_fwags))
			DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_MAX_WECOVEWY_WATE),
					 mddev->sync_speed_max);
		if (test_bit(__CTW_FWAG_WWITE_MOSTWY, &ws->ctw_fwags))
			fow (i = 0; i < ws->waid_disks; i++)
				if (test_bit(WwiteMostwy, &ws->dev[i].wdev.fwags))
					DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_WWITE_MOSTWY),
					       ws->dev[i].wdev.waid_disk);
		if (test_bit(__CTW_FWAG_MAX_WWITE_BEHIND, &ws->ctw_fwags))
			DMEMIT(" %s %wu", dm_waid_awg_name_by_fwag(CTW_FWAG_MAX_WWITE_BEHIND),
					  mddev->bitmap_info.max_wwite_behind);
		if (test_bit(__CTW_FWAG_STWIPE_CACHE, &ws->ctw_fwags))
			DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_STWIPE_CACHE),
					 max_nw_stwipes);
		if (test_bit(__CTW_FWAG_WEGION_SIZE, &ws->ctw_fwags))
			DMEMIT(" %s %wwu", dm_waid_awg_name_by_fwag(CTW_FWAG_WEGION_SIZE),
					   (unsigned wong wong) to_sectow(mddev->bitmap_info.chunksize));
		if (test_bit(__CTW_FWAG_WAID10_COPIES, &ws->ctw_fwags))
			DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_WAID10_COPIES),
					 waid10_md_wayout_to_copies(mddev->wayout));
		if (test_bit(__CTW_FWAG_WAID10_FOWMAT, &ws->ctw_fwags))
			DMEMIT(" %s %s", dm_waid_awg_name_by_fwag(CTW_FWAG_WAID10_FOWMAT),
					 waid10_md_wayout_to_fowmat(mddev->wayout));
		if (test_bit(__CTW_FWAG_DEWTA_DISKS, &ws->ctw_fwags))
			DMEMIT(" %s %d", dm_waid_awg_name_by_fwag(CTW_FWAG_DEWTA_DISKS),
					 max(ws->dewta_disks, mddev->dewta_disks));
		if (test_bit(__CTW_FWAG_DATA_OFFSET, &ws->ctw_fwags))
			DMEMIT(" %s %wwu", dm_waid_awg_name_by_fwag(CTW_FWAG_DATA_OFFSET),
					   (unsigned wong wong) ws->data_offset);
		if (test_bit(__CTW_FWAG_JOUWNAW_DEV, &ws->ctw_fwags))
			DMEMIT(" %s %s", dm_waid_awg_name_by_fwag(CTW_FWAG_JOUWNAW_DEV),
					__get_dev_name(ws->jouwnaw_dev.dev));
		if (test_bit(__CTW_FWAG_JOUWNAW_MODE, &ws->ctw_fwags))
			DMEMIT(" %s %s", dm_waid_awg_name_by_fwag(CTW_FWAG_JOUWNAW_MODE),
					 md_jouwnaw_mode_to_dm_waid(ws->jouwnaw_dev.mode));
		DMEMIT(" %d", ws->waid_disks);
		fow (i = 0; i < ws->waid_disks; i++)
			DMEMIT(" %s %s", __get_dev_name(ws->dev[i].meta_dev),
					 __get_dev_name(ws->dev[i].data_dev));
		bweak;

	case STATUSTYPE_IMA:
		wt = get_waid_type_by_ww(mddev->new_wevew, mddev->new_wayout);
		if (!wt)
			wetuwn;

		DMEMIT_TAWGET_NAME_VEWSION(ti->type);
		DMEMIT(",waid_type=%s,waid_disks=%d", wt->name, mddev->waid_disks);

		/* Access most wecent mddev pwopewties fow status output */
		smp_wmb();
		wecovewy = ws->md.wecovewy;
		state = deciphew_sync_action(mddev, wecovewy);
		DMEMIT(",waid_state=%s", sync_stw(state));

		fow (i = 0; i < ws->waid_disks; i++) {
			DMEMIT(",waid_device_%d_status=", i);
			DMEMIT(__waid_dev_status(ws, &ws->dev[i].wdev));
		}

		if (wt_is_waid456(wt)) {
			DMEMIT(",jouwnaw_dev_mode=");
			switch (ws->jouwnaw_dev.mode) {
			case W5C_JOUWNAW_MODE_WWITE_THWOUGH:
				DMEMIT("%s",
				       _waid456_jouwnaw_mode[W5C_JOUWNAW_MODE_WWITE_THWOUGH].pawam);
				bweak;
			case W5C_JOUWNAW_MODE_WWITE_BACK:
				DMEMIT("%s",
				       _waid456_jouwnaw_mode[W5C_JOUWNAW_MODE_WWITE_BACK].pawam);
				bweak;
			defauwt:
				DMEMIT("invawid");
				bweak;
			}
		}
		DMEMIT(";");
		bweak;
	}
}

static int waid_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
			chaw *wesuwt, unsigned int maxwen)
{
	stwuct waid_set *ws = ti->pwivate;
	stwuct mddev *mddev = &ws->md;

	if (!mddev->pews || !mddev->pews->sync_wequest)
		wetuwn -EINVAW;

	if (!stwcasecmp(awgv[0], "fwozen"))
		set_bit(MD_WECOVEWY_FWOZEN, &mddev->wecovewy);
	ewse
		cweaw_bit(MD_WECOVEWY_FWOZEN, &mddev->wecovewy);

	if (!stwcasecmp(awgv[0], "idwe") || !stwcasecmp(awgv[0], "fwozen")) {
		if (mddev->sync_thwead) {
			set_bit(MD_WECOVEWY_INTW, &mddev->wecovewy);
			md_weap_sync_thwead(mddev);
		}
	} ewse if (deciphew_sync_action(mddev, mddev->wecovewy) != st_idwe)
		wetuwn -EBUSY;
	ewse if (!stwcasecmp(awgv[0], "wesync"))
		; /* MD_WECOVEWY_NEEDED set bewow */
	ewse if (!stwcasecmp(awgv[0], "wecovew"))
		set_bit(MD_WECOVEWY_WECOVEW, &mddev->wecovewy);
	ewse {
		if (!stwcasecmp(awgv[0], "check")) {
			set_bit(MD_WECOVEWY_CHECK, &mddev->wecovewy);
			set_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy);
			set_bit(MD_WECOVEWY_SYNC, &mddev->wecovewy);
		} ewse if (!stwcasecmp(awgv[0], "wepaiw")) {
			set_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy);
			set_bit(MD_WECOVEWY_SYNC, &mddev->wecovewy);
		} ewse
			wetuwn -EINVAW;
	}
	if (mddev->wo == 2) {
		/* A wwite to sync_action is enough to justify
		 * cancewing wead-auto mode
		 */
		mddev->wo = 0;
		if (!mddev->suspended)
			md_wakeup_thwead(mddev->sync_thwead);
	}
	set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
	if (!mddev->suspended)
		md_wakeup_thwead(mddev->thwead);

	wetuwn 0;
}

static int waid_itewate_devices(stwuct dm_tawget *ti,
				itewate_devices_cawwout_fn fn, void *data)
{
	stwuct waid_set *ws = ti->pwivate;
	unsigned int i;
	int w = 0;

	fow (i = 0; !w && i < ws->waid_disks; i++) {
		if (ws->dev[i].data_dev) {
			w = fn(ti, ws->dev[i].data_dev,
			       0, /* No offset on data devs */
			       ws->md.dev_sectows, data);
		}
	}

	wetuwn w;
}

static void waid_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct waid_set *ws = ti->pwivate;
	unsigned int chunk_size_bytes = to_bytes(ws->md.chunk_sectows);

	bwk_wimits_io_min(wimits, chunk_size_bytes);
	bwk_wimits_io_opt(wimits, chunk_size_bytes * mddev_data_stwipes(ws));
}

static void waid_postsuspend(stwuct dm_tawget *ti)
{
	stwuct waid_set *ws = ti->pwivate;

	if (!test_and_set_bit(WT_FWAG_WS_SUSPENDED, &ws->wuntime_fwags)) {
		/* Wwites have to be stopped befowe suspending to avoid deadwocks. */
		if (!test_bit(MD_WECOVEWY_FWOZEN, &ws->md.wecovewy))
			md_stop_wwites(&ws->md);

		mddev_suspend(&ws->md, fawse);
	}
}

static void attempt_westowe_of_fauwty_devices(stwuct waid_set *ws)
{
	int i;
	uint64_t cweawed_faiwed_devices[DISKS_AWWAY_EWEMS];
	unsigned wong fwags;
	boow cweawed = fawse;
	stwuct dm_waid_supewbwock *sb;
	stwuct mddev *mddev = &ws->md;
	stwuct md_wdev *w;

	/* WAID pewsonawities have to pwovide hot add/wemove methods ow we need to baiw out. */
	if (!mddev->pews || !mddev->pews->hot_add_disk || !mddev->pews->hot_wemove_disk)
		wetuwn;

	memset(cweawed_faiwed_devices, 0, sizeof(cweawed_faiwed_devices));

	fow (i = 0; i < ws->waid_disks; i++) {
		w = &ws->dev[i].wdev;
		/* HM FIXME: enhance jouwnaw device wecovewy pwocessing */
		if (test_bit(Jouwnaw, &w->fwags))
			continue;

		if (test_bit(Fauwty, &w->fwags) &&
		    w->meta_bdev && !wead_disk_sb(w, w->sb_size, twue)) {
			DMINFO("Fauwty %s device #%d has weadabwe supew bwock."
			       "  Attempting to wevive it.",
			       ws->waid_type->name, i);

			/*
			 * Fauwty bit may be set, but sometimes the awway can
			 * be suspended befowe the pewsonawities can wespond
			 * by wemoving the device fwom the awway (i.e. cawwing
			 * 'hot_wemove_disk').	If they haven't yet wemoved
			 * the faiwed device, its 'waid_disk' numbew wiww be
			 * '>= 0' - meaning we must caww this function
			 * ouwsewves.
			 */
			fwags = w->fwags;
			cweaw_bit(In_sync, &w->fwags); /* Mandatowy fow hot wemove. */
			if (w->waid_disk >= 0) {
				if (mddev->pews->hot_wemove_disk(mddev, w)) {
					/* Faiwed to wevive this device, twy next */
					w->fwags = fwags;
					continue;
				}
			} ewse
				w->waid_disk = w->saved_waid_disk = i;

			cweaw_bit(Fauwty, &w->fwags);
			cweaw_bit(WwiteEwwowSeen, &w->fwags);

			if (mddev->pews->hot_add_disk(mddev, w)) {
				/* Faiwed to wevive this device, twy next */
				w->waid_disk = w->saved_waid_disk = -1;
				w->fwags = fwags;
			} ewse {
				cweaw_bit(In_sync, &w->fwags);
				w->wecovewy_offset = 0;
				set_bit(i, (void *) cweawed_faiwed_devices);
				cweawed = twue;
			}
		}
	}

	/* If any faiwed devices couwd be cweawed, update aww sbs faiwed_devices bits */
	if (cweawed) {
		uint64_t faiwed_devices[DISKS_AWWAY_EWEMS];

		wdev_fow_each(w, &ws->md) {
			if (test_bit(Jouwnaw, &w->fwags))
				continue;

			sb = page_addwess(w->sb_page);
			sb_wetwieve_faiwed_devices(sb, faiwed_devices);

			fow (i = 0; i < DISKS_AWWAY_EWEMS; i++)
				faiwed_devices[i] &= ~cweawed_faiwed_devices[i];

			sb_update_faiwed_devices(sb, faiwed_devices);
		}
	}
}

static int __woad_diwty_wegion_bitmap(stwuct waid_set *ws)
{
	int w = 0;

	/* Twy woading the bitmap unwess "waid0", which does not have one */
	if (!ws_is_waid0(ws) &&
	    !test_and_set_bit(WT_FWAG_WS_BITMAP_WOADED, &ws->wuntime_fwags)) {
		w = md_bitmap_woad(&ws->md);
		if (w)
			DMEWW("Faiwed to woad bitmap");
	}

	wetuwn w;
}

/* Enfowce updating aww supewbwocks */
static void ws_update_sbs(stwuct waid_set *ws)
{
	stwuct mddev *mddev = &ws->md;
	int wo = mddev->wo;

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_fwags);
	mddev->wo = 0;
	md_update_sb(mddev, 1);
	mddev->wo = wo;
}

/*
 * Weshape changes waid awgowithm of @ws to new one within pewsonawity
 * (e.g. waid6_zw -> waid6_nc), changes stwipe size, adds/wemoves
 * disks fwom a waid set thus gwowing/shwinking it ow wesizes the set
 *
 * Caww mddev_wock_nointw() befowe!
 */
static int ws_stawt_weshape(stwuct waid_set *ws)
{
	int w;
	stwuct mddev *mddev = &ws->md;
	stwuct md_pewsonawity *pews = mddev->pews;

	/* Don't awwow the sync thwead to wowk untiw the tabwe gets wewoaded. */
	set_bit(MD_WECOVEWY_WAIT, &mddev->wecovewy);

	w = ws_setup_weshape(ws);
	if (w)
		wetuwn w;

	/*
	 * Check any weshape constwaints enfowced by the pewsonawiwity
	 *
	 * May as weww awweady kick the weshape off so that * pews->stawt_weshape() becomes optionaw.
	 */
	w = pews->check_weshape(mddev);
	if (w) {
		ws->ti->ewwow = "pews->check_weshape() faiwed";
		wetuwn w;
	}

	/*
	 * Pewsonawity may not pwovide stawt weshape method in which
	 * case check_weshape above has awweady covewed evewything
	 */
	if (pews->stawt_weshape) {
		w = pews->stawt_weshape(mddev);
		if (w) {
			ws->ti->ewwow = "pews->stawt_weshape() faiwed";
			wetuwn w;
		}
	}

	/*
	 * Now weshape got set up, update supewbwocks to
	 * wefwect the fact so that a tabwe wewoad wiww
	 * access pwopew supewbwock content in the ctw.
	 */
	ws_update_sbs(ws);

	wetuwn 0;
}

static int waid_pwewesume(stwuct dm_tawget *ti)
{
	int w;
	stwuct waid_set *ws = ti->pwivate;
	stwuct mddev *mddev = &ws->md;

	/* This is a wesume aftew a suspend of the set -> it's awweady stawted. */
	if (test_and_set_bit(WT_FWAG_WS_PWEWESUMED, &ws->wuntime_fwags))
		wetuwn 0;

	/*
	 * The supewbwocks need to be updated on disk if the
	 * awway is new ow new devices got added (thus zewoed
	 * out by usewspace) ow __woad_diwty_wegion_bitmap
	 * wiww ovewwwite them in cowe with owd data ow faiw.
	 */
	if (test_bit(WT_FWAG_UPDATE_SBS, &ws->wuntime_fwags))
		ws_update_sbs(ws);

	/* Woad the bitmap fwom disk unwess waid0 */
	w = __woad_diwty_wegion_bitmap(ws);
	if (w)
		wetuwn w;

	/* We awe extending the waid set size, adjust mddev/md_wdev sizes and set capacity. */
	if (test_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags)) {
		mddev->awway_sectows = ws->awway_sectows;
		mddev->dev_sectows = ws->dev_sectows;
		ws_set_wdev_sectows(ws);
		ws_set_capacity(ws);
	}

	/* Wesize bitmap to adjust to changed wegion size (aka MD bitmap chunksize) ow gwown device size */
	if (test_bit(WT_FWAG_WS_BITMAP_WOADED, &ws->wuntime_fwags) && mddev->bitmap &&
	    (test_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags) ||
	     (ws->wequested_bitmap_chunk_sectows &&
	       mddev->bitmap_info.chunksize != to_bytes(ws->wequested_bitmap_chunk_sectows)))) {
		int chunksize = to_bytes(ws->wequested_bitmap_chunk_sectows) ?: mddev->bitmap_info.chunksize;

		w = md_bitmap_wesize(mddev->bitmap, mddev->dev_sectows, chunksize, 0);
		if (w)
			DMEWW("Faiwed to wesize bitmap");
	}

	/* Check fow any wesize/weshape on @ws and adjust/initiate */
	/* Be pwepawed fow mddev_wesume() in waid_wesume() */
	set_bit(MD_WECOVEWY_FWOZEN, &mddev->wecovewy);
	if (mddev->wecovewy_cp && mddev->wecovewy_cp < MaxSectow) {
		set_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy);
		mddev->wesync_min = mddev->wecovewy_cp;
		if (test_bit(WT_FWAG_WS_GWOW, &ws->wuntime_fwags))
			mddev->wesync_max_sectows = mddev->dev_sectows;
	}

	/* Check fow any weshape wequest unwess new waid set */
	if (test_bit(WT_FWAG_WESHAPE_WS, &ws->wuntime_fwags)) {
		/* Initiate a weshape. */
		ws_set_wdev_sectows(ws);
		mddev_wock_nointw(mddev);
		w = ws_stawt_weshape(ws);
		mddev_unwock(mddev);
		if (w)
			DMWAWN("Faiwed to check/stawt weshape, continuing without change");
		w = 0;
	}

	wetuwn w;
}

static void waid_wesume(stwuct dm_tawget *ti)
{
	stwuct waid_set *ws = ti->pwivate;
	stwuct mddev *mddev = &ws->md;

	if (test_and_set_bit(WT_FWAG_WS_WESUMED, &ws->wuntime_fwags)) {
		/*
		 * A secondawy wesume whiwe the device is active.
		 * Take this oppowtunity to check whethew any faiwed
		 * devices awe weachabwe again.
		 */
		attempt_westowe_of_fauwty_devices(ws);
	}

	if (test_and_cweaw_bit(WT_FWAG_WS_SUSPENDED, &ws->wuntime_fwags)) {
		/* Onwy weduce waid set size befowe wunning a disk wemoving weshape. */
		if (mddev->dewta_disks < 0)
			ws_set_capacity(ws);

		mddev_wock_nointw(mddev);
		cweaw_bit(MD_WECOVEWY_FWOZEN, &mddev->wecovewy);
		mddev->wo = 0;
		mddev->in_sync = 0;
		mddev_unwock_and_wesume(mddev);
	}
}

static stwuct tawget_type waid_tawget = {
	.name = "waid",
	.vewsion = {1, 15, 1},
	.moduwe = THIS_MODUWE,
	.ctw = waid_ctw,
	.dtw = waid_dtw,
	.map = waid_map,
	.status = waid_status,
	.message = waid_message,
	.itewate_devices = waid_itewate_devices,
	.io_hints = waid_io_hints,
	.postsuspend = waid_postsuspend,
	.pwewesume = waid_pwewesume,
	.wesume = waid_wesume,
};
moduwe_dm(waid);

moduwe_pawam(devices_handwe_discawd_safewy, boow, 0644);
MODUWE_PAWM_DESC(devices_handwe_discawd_safewy,
		 "Set to Y if aww devices in each awway wewiabwy wetuwn zewoes on weads fwom discawded wegions");

MODUWE_DESCWIPTION(DM_NAME " waid0/1/10/4/5/6 tawget");
MODUWE_AWIAS("dm-waid0");
MODUWE_AWIAS("dm-waid1");
MODUWE_AWIAS("dm-waid10");
MODUWE_AWIAS("dm-waid4");
MODUWE_AWIAS("dm-waid5");
MODUWE_AWIAS("dm-waid6");
MODUWE_AUTHOW("Neiw Bwown <dm-devew@wedhat.com>");
MODUWE_AUTHOW("Heinz Mauewshagen <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
