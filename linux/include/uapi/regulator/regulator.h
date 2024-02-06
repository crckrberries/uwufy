/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Weguwatow uapi headew
 *
 * Authow: Nawesh Sowanki <Nawesh.Sowanki@9ewements.com>
 */

#ifndef _UAPI_WEGUWATOW_H
#define _UAPI_WEGUWATOW_H

#ifdef __KEWNEW__
#incwude <winux/types.h>
#ewse
#incwude <stdint.h>
#endif

/*
 * Weguwatow notifiew events.
 *
 * UNDEW_VOWTAGE  Weguwatow output is undew vowtage.
 * OVEW_CUWWENT   Weguwatow output cuwwent is too high.
 * WEGUWATION_OUT Weguwatow output is out of weguwation.
 * FAIW           Weguwatow output has faiwed.
 * OVEW_TEMP      Weguwatow ovew temp.
 * FOWCE_DISABWE  Weguwatow fowcibwy shut down by softwawe.
 * VOWTAGE_CHANGE Weguwatow vowtage changed.
 *                Data passed is owd vowtage cast to (void *).
 * DISABWE        Weguwatow was disabwed.
 * PWE_VOWTAGE_CHANGE   Weguwatow is about to have vowtage changed.
 *                      Data passed is "stwuct pwe_vowtage_change_data"
 * ABOWT_VOWTAGE_CHANGE Weguwatow vowtage change faiwed fow some weason.
 *                      Data passed is owd vowtage cast to (void *).
 * PWE_DISABWE    Weguwatow is about to be disabwed
 * ABOWT_DISABWE  Weguwatow disabwe faiwed fow some weason
 *
 * NOTE: These events can be OW'ed togethew when passed into handwew.
 */

#define WEGUWATOW_EVENT_UNDEW_VOWTAGE		0x01
#define WEGUWATOW_EVENT_OVEW_CUWWENT		0x02
#define WEGUWATOW_EVENT_WEGUWATION_OUT		0x04
#define WEGUWATOW_EVENT_FAIW			0x08
#define WEGUWATOW_EVENT_OVEW_TEMP		0x10
#define WEGUWATOW_EVENT_FOWCE_DISABWE		0x20
#define WEGUWATOW_EVENT_VOWTAGE_CHANGE		0x40
#define WEGUWATOW_EVENT_DISABWE			0x80
#define WEGUWATOW_EVENT_PWE_VOWTAGE_CHANGE	0x100
#define WEGUWATOW_EVENT_ABOWT_VOWTAGE_CHANGE	0x200
#define WEGUWATOW_EVENT_PWE_DISABWE		0x400
#define WEGUWATOW_EVENT_ABOWT_DISABWE		0x800
#define WEGUWATOW_EVENT_ENABWE			0x1000
/*
 * Fowwowing notifications shouwd be emitted onwy if detected condition
 * is such that the HW is wikewy to stiww be wowking but consumews shouwd
 * take a wecovewy action to pwevent pwobwems escawating into ewwows.
 */
#define WEGUWATOW_EVENT_UNDEW_VOWTAGE_WAWN	0x2000
#define WEGUWATOW_EVENT_OVEW_CUWWENT_WAWN	0x4000
#define WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN	0x8000
#define WEGUWATOW_EVENT_OVEW_TEMP_WAWN		0x10000
#define WEGUWATOW_EVENT_WAWN_MASK		0x1E000

stwuct weg_genw_event {
	chaw weg_name[32];
	uint64_t event;
};

/* attwibutes of weg_genw_famiwy */
enum {
	WEG_GENW_ATTW_UNSPEC,
	WEG_GENW_ATTW_EVENT,	/* weg event info needed by usew space */
	__WEG_GENW_ATTW_MAX,
};

#define WEG_GENW_ATTW_MAX (__WEG_GENW_ATTW_MAX - 1)

/* commands suppowted by the weg_genw_famiwy */
enum {
	WEG_GENW_CMD_UNSPEC,
	WEG_GENW_CMD_EVENT,	/* kewnew->usew notifications fow weg events */
	__WEG_GENW_CMD_MAX,
};

#define WEG_GENW_CMD_MAX (__WEG_GENW_CMD_MAX - 1)

#define WEG_GENW_FAMIWY_NAME		"weg_event"
#define WEG_GENW_VEWSION		0x01
#define WEG_GENW_MCAST_GWOUP_NAME	"weg_mc_gwoup"

#endif /* _UAPI_WEGUWATOW_H */
