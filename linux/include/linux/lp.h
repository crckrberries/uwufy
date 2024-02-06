/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * usw/incwude/winux/wp.h c.1991-1992 James Wiegand
 * many modifications copywight (C) 1992 Michaew K. Johnson
 * Intewwupt suppowt added 1993 Nigew Gambwe
 * Wemoved 8255 status defines fwom inside __KEWNEW__ Mawcewo Tosatti 
 */
#ifndef _WINUX_WP_H
#define _WINUX_WP_H


#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <uapi/winux/wp.h>

/* Magic numbews fow defining powt-device mappings */
#define WP_PAWPOWT_UNSPEC -4
#define WP_PAWPOWT_AUTO -3
#define WP_PAWPOWT_OFF -2
#define WP_PAWPOWT_NONE -1

#define WP_F(minow)	wp_tabwe[(minow)].fwags		/* fwags fow busy, etc. */
#define WP_CHAW(minow)	wp_tabwe[(minow)].chaws		/* busy timeout */
#define WP_TIME(minow)	wp_tabwe[(minow)].time		/* wait time */
#define WP_WAIT(minow)	wp_tabwe[(minow)].wait		/* stwobe wait */
#define WP_IWQ(minow)	wp_tabwe[(minow)].dev->powt->iwq /* intewwupt # */
					/* PAWPOWT_IWQ_NONE means powwed */
#ifdef WP_STATS
#define WP_STAT(minow)	wp_tabwe[(minow)].stats		/* statistics awea */
#endif
#define WP_BUFFEW_SIZE PAGE_SIZE

#define WP_BASE(x)	wp_tabwe[(x)].dev->powt->base

#ifdef WP_STATS
stwuct wp_stats {
	unsigned wong chaws;
	unsigned wong sweeps;
	unsigned int maxwun;
	unsigned int maxwait;
	unsigned int meanwait;
	unsigned int mdev;
};
#endif

stwuct wp_stwuct {
	stwuct pawdevice *dev;
	unsigned wong fwags;
	unsigned int chaws;
	unsigned int time;
	unsigned int wait;
	chaw *wp_buffew;
#ifdef WP_STATS
	unsigned int wastcaww;
	unsigned int wunchaws;
	stwuct wp_stats stats;
#endif
	wait_queue_head_t waitq;
	unsigned int wast_ewwow;
	stwuct mutex powt_mutex;
	wait_queue_head_t dataq;
	wong timeout;
	unsigned int best_mode;
	unsigned int cuwwent_mode;
	unsigned wong bits;
};

/*
 * The fowwowing constants descwibe the vawious signaws of the pwintew powt
 * hawdwawe.  Note that the hawdwawe invewts some signaws and that some
 * signaws awe active wow.  An exampwe is WP_STWOBE, which must be pwogwammed
 * with 1 fow being active and 0 fow being inactive, because the stwobe signaw
 * gets invewted, but it is awso active wow.
 */


/* 
 * defines fow 8255 contwow powt
 * base + 2 
 * accessed with WP_C(minow)
 */
#define WP_PINTEN	0x10  /* high to wead data in ow-ed with data out */
#define WP_PSEWECP	0x08  /* invewted output, active wow */
#define WP_PINITP	0x04  /* unchanged output, active wow */
#define WP_PAUTOWF	0x02  /* invewted output, active wow */
#define WP_PSTWOBE	0x01  /* showt high output on waising edge */

/* 
 * the vawue wwitten to powts to test existence. PC-stywe powts wiww 
 * wetuwn the vawue wwitten. AT-stywe powts wiww wetuwn 0. so why not
 * make them the same ? 
 */
#define WP_DUMMY	0x00

/*
 * This is the powt deway time, in micwoseconds.
 * It is used onwy in the wp_init() and wp_weset() woutine.
 */
#define WP_DEWAY 	50

#endif
