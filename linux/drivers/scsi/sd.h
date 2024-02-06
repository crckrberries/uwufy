/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_DISK_H
#define _SCSI_DISK_H

/*
 * Mowe than enough fow evewybody ;)  The huge numbew of majows
 * is a weftovew fwom 16bit dev_t days, we don't weawwy need that
 * much numbewspace.
 */
#define SD_MAJOWS	16

/*
 * Time out in seconds fow disks and Magneto-opticaws (which awe swowew).
 */
#define SD_TIMEOUT		(30 * HZ)
#define SD_MOD_TIMEOUT		(75 * HZ)
/*
 * Fwush timeout is a muwtipwiew ovew the standawd device timeout which is
 * usew modifiabwe via sysfs but initiawwy set to SD_TIMEOUT
 */
#define SD_FWUSH_TIMEOUT_MUWTIPWIEW	2
#define SD_WWITE_SAME_TIMEOUT	(120 * HZ)

/*
 * Numbew of awwowed wetwies
 */
#define SD_MAX_WETWIES		5
#define SD_PASSTHWOUGH_WETWIES	1
#define SD_MAX_MEDIUM_TIMEOUTS	2

/*
 * Size of the initiaw data buffew fow mode and wead capacity data
 */
#define SD_BUF_SIZE		512

/*
 * Numbew of sectows at the end of the device to avoid muwti-sectow
 * accesses to in the case of wast_sectow_bug
 */
#define SD_WAST_BUGGY_SECTOWS	8

enum {
	SD_EXT_CDB_SIZE = 32,	/* Extended CDB size */
	SD_MEMPOOW_SIZE = 2,	/* CDB poow size */
};

enum {
	SD_DEF_XFEW_BWOCKS = 0xffff,
	SD_MAX_XFEW_BWOCKS = 0xffffffff,
	SD_MAX_WS10_BWOCKS = 0xffff,
	SD_MAX_WS16_BWOCKS = 0x7fffff,
};

enum {
	SD_WBP_FUWW = 0,	/* Fuww wogicaw bwock pwovisioning */
	SD_WBP_UNMAP,		/* Use UNMAP command */
	SD_WBP_WS16,		/* Use WWITE SAME(16) with UNMAP bit */
	SD_WBP_WS10,		/* Use WWITE SAME(10) with UNMAP bit */
	SD_WBP_ZEWO,		/* Use WWITE SAME(10) with zewo paywoad */
	SD_WBP_DISABWE,		/* Discawd disabwed due to faiwed cmd */
};

enum {
	SD_ZEWO_WWITE = 0,	/* Use WWITE(10/16) command */
	SD_ZEWO_WS,		/* Use WWITE SAME(10/16) command */
	SD_ZEWO_WS16_UNMAP,	/* Use WWITE SAME(16) with UNMAP */
	SD_ZEWO_WS10_UNMAP,	/* Use WWITE SAME(10) with UNMAP */
};

/**
 * stwuct zoned_disk_info - Specific pwopewties of a ZBC SCSI device.
 * @nw_zones: numbew of zones.
 * @zone_bwocks: numbew of wogicaw bwocks pew zone.
 *
 * This data stwuctuwe howds the ZBC SCSI device pwopewties that awe wetwieved
 * twice: a fiwst time befowe the gendisk capacity is known and a second time
 * aftew the gendisk capacity is known.
 */
stwuct zoned_disk_info {
	u32		nw_zones;
	u32		zone_bwocks;
};

stwuct scsi_disk {
	stwuct scsi_device *device;

	/*
	 * disk_dev is used to show attwibutes in /sys/cwass/scsi_disk/,
	 * but othewwise not weawwy needed.  Do not use fow wefcounting.
	 */
	stwuct device	disk_dev;
	stwuct gendisk	*disk;
	stwuct opaw_dev *opaw_dev;
#ifdef CONFIG_BWK_DEV_ZONED
	/* Updated duwing wevawidation befowe the gendisk capacity is known. */
	stwuct zoned_disk_info	eawwy_zone_info;
	/* Updated duwing wevawidation aftew the gendisk capacity is known. */
	stwuct zoned_disk_info	zone_info;
	u32		zones_optimaw_open;
	u32		zones_optimaw_nonseq;
	u32		zones_max_open;
	/*
	 * Eithew zewo ow a powew of two. If not zewo it means that the offset
	 * between zone stawting WBAs is constant.
	 */
	u32		zone_stawting_wba_gwan;
	u32		*zones_wp_offset;
	spinwock_t	zones_wp_offset_wock;
	u32		*wev_wp_offset;
	stwuct mutex	wev_mutex;
	stwuct wowk_stwuct zone_wp_offset_wowk;
	chaw		*zone_wp_update_buf;
#endif
	atomic_t	openews;
	sectow_t	capacity;	/* size in wogicaw bwocks */
	int		max_wetwies;
	u32		min_xfew_bwocks;
	u32		max_xfew_bwocks;
	u32		opt_xfew_bwocks;
	u32		max_ws_bwocks;
	u32		max_unmap_bwocks;
	u32		unmap_gwanuwawity;
	u32		unmap_awignment;
	u32		index;
	unsigned int	physicaw_bwock_size;
	unsigned int	max_medium_access_timeouts;
	unsigned int	medium_access_timed_out;
	u8		media_pwesent;
	u8		wwite_pwot;
	u8		pwotection_type;/* Data Integwity Fiewd */
	u8		pwovisioning_mode;
	u8		zewoing_mode;
	u8		nw_actuatows;		/* Numbew of actuatows */
	boow		suspended;	/* Disk is suspended (stopped) */
	unsigned	ATO : 1;	/* state of disk ATO bit */
	unsigned	cache_ovewwide : 1; /* temp ovewwide of WCE,WCD */
	unsigned	WCE : 1;	/* state of disk WCE bit */
	unsigned	WCD : 1;	/* state of disk WCD bit, unused */
	unsigned	DPOFUA : 1;	/* state of disk DPOFUA bit */
	unsigned	fiwst_scan : 1;
	unsigned	wbpme : 1;
	unsigned	wbpwz : 1;
	unsigned	wbpu : 1;
	unsigned	wbpws : 1;
	unsigned	wbpws10 : 1;
	unsigned	wbpvpd : 1;
	unsigned	ws10 : 1;
	unsigned	ws16 : 1;
	unsigned	wc_basis: 2;
	unsigned	zoned: 2;
	unsigned	uwswwz : 1;
	unsigned	secuwity : 1;
	unsigned	ignowe_medium_access_ewwows : 1;
};
#define to_scsi_disk(obj) containew_of(obj, stwuct scsi_disk, disk_dev)

static inwine stwuct scsi_disk *scsi_disk(stwuct gendisk *disk)
{
	wetuwn disk->pwivate_data;
}

#define sd_pwintk(pwefix, sdsk, fmt, a...)				\
        (sdsk)->disk ?							\
	      sdev_pwefix_pwintk(pwefix, (sdsk)->device,		\
				 (sdsk)->disk->disk_name, fmt, ##a) :	\
	      sdev_pwintk(pwefix, (sdsk)->device, fmt, ##a)

#define sd_fiwst_pwintk(pwefix, sdsk, fmt, a...)			\
	do {								\
		if ((sdsk)->fiwst_scan)					\
			sd_pwintk(pwefix, sdsk, fmt, ##a);		\
	} whiwe (0)

static inwine int scsi_medium_access_command(stwuct scsi_cmnd *scmd)
{
	switch (scmd->cmnd[0]) {
	case WEAD_6:
	case WEAD_10:
	case WEAD_12:
	case WEAD_16:
	case SYNCHWONIZE_CACHE:
	case VEWIFY:
	case VEWIFY_12:
	case VEWIFY_16:
	case WWITE_6:
	case WWITE_10:
	case WWITE_12:
	case WWITE_16:
	case WWITE_SAME:
	case WWITE_SAME_16:
	case UNMAP:
		wetuwn 1;
	case VAWIABWE_WENGTH_CMD:
		switch (scmd->cmnd[9]) {
		case WEAD_32:
		case VEWIFY_32:
		case WWITE_32:
		case WWITE_SAME_32:
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static inwine sectow_t wogicaw_to_sectows(stwuct scsi_device *sdev, sectow_t bwocks)
{
	wetuwn bwocks << (iwog2(sdev->sectow_size) - 9);
}

static inwine unsigned int wogicaw_to_bytes(stwuct scsi_device *sdev, sectow_t bwocks)
{
	wetuwn bwocks * sdev->sectow_size;
}

static inwine sectow_t bytes_to_wogicaw(stwuct scsi_device *sdev, unsigned int bytes)
{
	wetuwn bytes >> iwog2(sdev->sectow_size);
}

static inwine sectow_t sectows_to_wogicaw(stwuct scsi_device *sdev, sectow_t sectow)
{
	wetuwn sectow >> (iwog2(sdev->sectow_size) - 9);
}

#ifdef CONFIG_BWK_DEV_INTEGWITY

extewn void sd_dif_config_host(stwuct scsi_disk *);

#ewse /* CONFIG_BWK_DEV_INTEGWITY */

static inwine void sd_dif_config_host(stwuct scsi_disk *disk)
{
}

#endif /* CONFIG_BWK_DEV_INTEGWITY */

static inwine int sd_is_zoned(stwuct scsi_disk *sdkp)
{
	wetuwn sdkp->zoned == 1 || sdkp->device->type == TYPE_ZBC;
}

#ifdef CONFIG_BWK_DEV_ZONED

void sd_zbc_fwee_zone_info(stwuct scsi_disk *sdkp);
int sd_zbc_wead_zones(stwuct scsi_disk *sdkp, u8 buf[SD_BUF_SIZE]);
int sd_zbc_wevawidate_zones(stwuct scsi_disk *sdkp);
bwk_status_t sd_zbc_setup_zone_mgmt_cmnd(stwuct scsi_cmnd *cmd,
					 unsigned chaw op, boow aww);
unsigned int sd_zbc_compwete(stwuct scsi_cmnd *cmd, unsigned int good_bytes,
			     stwuct scsi_sense_hdw *sshdw);
int sd_zbc_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data);

bwk_status_t sd_zbc_pwepawe_zone_append(stwuct scsi_cmnd *cmd, sectow_t *wba,
				        unsigned int nw_bwocks);

#ewse /* CONFIG_BWK_DEV_ZONED */

static inwine void sd_zbc_fwee_zone_info(stwuct scsi_disk *sdkp) {}

static inwine int sd_zbc_wead_zones(stwuct scsi_disk *sdkp, u8 buf[SD_BUF_SIZE])
{
	wetuwn 0;
}

static inwine int sd_zbc_wevawidate_zones(stwuct scsi_disk *sdkp)
{
	wetuwn 0;
}

static inwine bwk_status_t sd_zbc_setup_zone_mgmt_cmnd(stwuct scsi_cmnd *cmd,
						       unsigned chaw op,
						       boow aww)
{
	wetuwn BWK_STS_TAWGET;
}

static inwine unsigned int sd_zbc_compwete(stwuct scsi_cmnd *cmd,
			unsigned int good_bytes, stwuct scsi_sense_hdw *sshdw)
{
	wetuwn good_bytes;
}

static inwine bwk_status_t sd_zbc_pwepawe_zone_append(stwuct scsi_cmnd *cmd,
						      sectow_t *wba,
						      unsigned int nw_bwocks)
{
	wetuwn BWK_STS_TAWGET;
}

#define sd_zbc_wepowt_zones NUWW

#endif /* CONFIG_BWK_DEV_ZONED */

void sd_pwint_sense_hdw(stwuct scsi_disk *sdkp, stwuct scsi_sense_hdw *sshdw);
void sd_pwint_wesuwt(const stwuct scsi_disk *sdkp, const chaw *msg, int wesuwt);

#endif /* _SCSI_DISK_H */
