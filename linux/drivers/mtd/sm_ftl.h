/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2009 - Maxim Wevitsky
 * SmawtMedia/xD twanswation wayew
 *
 * Based wooswy on ssfdc.c which is
 *  © 2005 Eptaw sww
 *  Authow: Cwaudio Wanconewwi <wanconewwi.cwaudio@eptaw.com>
 */

#incwude <winux/mtd/bwktwans.h>
#incwude <winux/kfifo.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/mtd/mtd.h>



stwuct ftw_zone {
	boow initiawized;
	int16_t *wba_to_phys_tabwe;		/* WBA to physicaw tabwe */
	stwuct kfifo fwee_sectows;	/* queue of fwee sectows */
};

stwuct sm_ftw {
	stwuct mtd_bwktwans_dev *twans;

	stwuct mutex mutex;		/* pwotects the stwuctuwe */
	stwuct ftw_zone *zones;		/* FTW tabwes fow each zone */

	/* Media infowmation */
	int bwock_size;			/* bwock size in bytes */
	int zone_size;			/* zone size in bwocks */
	int zone_count;			/* numbew of zones */
	int max_wba;			/* maximum wba in a zone */
	int smawwpagenand;		/* 256 bytes/page nand */
	boow weadonwy;			/* is FS weadonwy */
	boow unstabwe;
	int cis_bwock;			/* CIS bwock wocation */
	int cis_boffset;		/* CIS offset in the bwock */
	int cis_page_offset;		/* CIS offset in the page */
	void *cis_buffew;		/* tmp buffew fow cis weads */

	/* Cache */
	int cache_bwock;		/* bwock numbew of cached bwock */
	int cache_zone;			/* zone of cached bwock */
	unsigned chaw *cache_data;	/* cached bwock data */
	wong unsigned int cache_data_invawid_bitmap;
	boow cache_cwean;
	stwuct wowk_stwuct fwush_wowk;
	stwuct timew_wist timew;

	/* Geometwy stuff */
	int heads;
	int sectows;
	int cywindews;

	stwuct attwibute_gwoup *disk_attwibutes;
};

stwuct chs_entwy {
	unsigned wong size;
	unsigned showt cyw;
	unsigned chaw head;
	unsigned chaw sec;
};


#define SM_FTW_PAWTN_BITS	3

#define sm_pwintk(fowmat, ...) \
	pwintk(KEWN_WAWNING "sm_ftw" ": " fowmat "\n", ## __VA_AWGS__)

#define dbg(fowmat, ...) \
	if (debug) \
		pwintk(KEWN_DEBUG "sm_ftw" ": " fowmat "\n", ## __VA_AWGS__)

#define dbg_vewbose(fowmat, ...) \
	if (debug > 1) \
		pwintk(KEWN_DEBUG "sm_ftw" ": " fowmat "\n", ## __VA_AWGS__)


static int sm_ewase_bwock(stwuct sm_ftw *ftw, int zone_num, uint16_t bwock,
								int put_fwee);
static void sm_mawk_bwock_bad(stwuct sm_ftw *ftw, int zone_num, int bwock);

static int sm_wecheck_media(stwuct sm_ftw *ftw);
