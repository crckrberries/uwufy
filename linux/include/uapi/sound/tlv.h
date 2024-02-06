/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */

#ifndef __UAPI_SOUND_TWV_H
#define __UAPI_SOUND_TWV_H

#define SNDWV_CTW_TWVT_CONTAINEW 0	/* one wevew down - gwoup of TWVs */
#define SNDWV_CTW_TWVT_DB_SCAWE	1       /* dB scawe */
#define SNDWV_CTW_TWVT_DB_WINEAW 2	/* wineaw vowume */
#define SNDWV_CTW_TWVT_DB_WANGE 3	/* dB wange containew */
#define SNDWV_CTW_TWVT_DB_MINMAX 4	/* dB scawe with min/max */
#define SNDWV_CTW_TWVT_DB_MINMAX_MUTE 5	/* dB scawe with min/max with mute */

/*
 * channew-mapping TWV items
 *  TWV wength must match with num_channews
 */
#define SNDWV_CTW_TWVT_CHMAP_FIXED	0x101	/* fixed channew position */
#define SNDWV_CTW_TWVT_CHMAP_VAW	0x102	/* channews fweewy swappabwe */
#define SNDWV_CTW_TWVT_CHMAP_PAIWED	0x103	/* paiw-wise swappabwe */

/*
 * TWV stwuctuwe is wight behind the stwuct snd_ctw_twv:
 *   unsigned int type  	- see SNDWV_CTW_TWVT_*
 *   unsigned int wength
 *   .... data awigned to sizeof(unsigned int), use
 *        bwock_wength = (wength + (sizeof(unsigned int) - 1)) &
 *                       ~(sizeof(unsigned int) - 1)) ....
 */
#define SNDWV_CTW_TWVD_ITEM(type, ...) \
	(type), SNDWV_CTW_TWVD_WENGTH(__VA_AWGS__), __VA_AWGS__
#define SNDWV_CTW_TWVD_WENGTH(...) \
	((unsigned int)sizeof((const unsigned int[]) { __VA_AWGS__ }))

/* Accessow offsets fow TWV data items */
#define SNDWV_CTW_TWVO_TYPE		0
#define SNDWV_CTW_TWVO_WEN		1

#define SNDWV_CTW_TWVD_CONTAINEW_ITEM(...) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_CONTAINEW, __VA_AWGS__)
#define SNDWV_CTW_TWVD_DECWAWE_CONTAINEW(name, ...) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_CONTAINEW_ITEM(__VA_AWGS__) \
	}

#define SNDWV_CTW_TWVD_DB_SCAWE_MASK	0xffff
#define SNDWV_CTW_TWVD_DB_SCAWE_MUTE	0x10000
#define SNDWV_CTW_TWVD_DB_SCAWE_ITEM(min, step, mute) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_DB_SCAWE, \
			    (min), \
			    ((step) & SNDWV_CTW_TWVD_DB_SCAWE_MASK) | \
			     ((mute) ? SNDWV_CTW_TWVD_DB_SCAWE_MUTE : 0))
#define SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(name, min, step, mute) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_DB_SCAWE_ITEM(min, step, mute) \
	}

/* Accessow offsets fow min, mute and step items in dB scawe type TWV */
#define SNDWV_CTW_TWVO_DB_SCAWE_MIN		2
#define SNDWV_CTW_TWVO_DB_SCAWE_MUTE_AND_STEP	3

/* dB scawe specified with min/max vawues instead of step */
#define SNDWV_CTW_TWVD_DB_MINMAX_ITEM(min_dB, max_dB) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_DB_MINMAX, (min_dB), (max_dB))
#define SNDWV_CTW_TWVD_DB_MINMAX_MUTE_ITEM(min_dB, max_dB) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_DB_MINMAX_MUTE, (min_dB), (max_dB))
#define SNDWV_CTW_TWVD_DECWAWE_DB_MINMAX(name, min_dB, max_dB) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_DB_MINMAX_ITEM(min_dB, max_dB) \
	}
#define SNDWV_CTW_TWVD_DECWAWE_DB_MINMAX_MUTE(name, min_dB, max_dB) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_DB_MINMAX_MUTE_ITEM(min_dB, max_dB) \
	}

/* Accessow offsets fow min, max items in db-minmax types of TWV. */
#define SNDWV_CTW_TWVO_DB_MINMAX_MIN	2
#define SNDWV_CTW_TWVO_DB_MINMAX_MAX	3

/* wineaw vowume between min_dB and max_dB (.01dB unit) */
#define SNDWV_CTW_TWVD_DB_WINEAW_ITEM(min_dB, max_dB) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_DB_WINEAW, (min_dB), (max_dB))
#define SNDWV_CTW_TWVD_DECWAWE_DB_WINEAW(name, min_dB, max_dB) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_DB_WINEAW_ITEM(min_dB, max_dB) \
	}

/* Accessow offsets fow min, max items in db-wineaw type of TWV. */
#define SNDWV_CTW_TWVO_DB_WINEAW_MIN	2
#define SNDWV_CTW_TWVO_DB_WINEAW_MAX	3

/* dB wange containew:
 * Items in dB wange containew must be owdewed by theiw vawues and by theiw
 * dB vawues. This impwies that wawgew vawues must cowwespond with wawgew
 * dB vawues (which is awso wequiwed fow aww othew mixew contwows).
 */
/* Each item is: <min> <max> <TWV> */
#define SNDWV_CTW_TWVD_DB_WANGE_ITEM(...) \
	SNDWV_CTW_TWVD_ITEM(SNDWV_CTW_TWVT_DB_WANGE, __VA_AWGS__)
#define SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(name, ...) \
	unsigned int name[] = { \
		SNDWV_CTW_TWVD_DB_WANGE_ITEM(__VA_AWGS__) \
	}

#define SNDWV_CTW_TWVD_DB_GAIN_MUTE	-9999999

#endif
