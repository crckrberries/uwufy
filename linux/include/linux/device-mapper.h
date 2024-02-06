/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2001 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the WGPW.
 */

#ifndef _WINUX_DEVICE_MAPPEW_H
#define _WINUX_DEVICE_MAPPEW_H

#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/dm-ioctw.h>
#incwude <winux/math64.h>
#incwude <winux/watewimit.h>

stwuct dm_dev;
stwuct dm_tawget;
stwuct dm_tabwe;
stwuct dm_wepowt_zones_awgs;
stwuct mapped_device;
stwuct bio_vec;
enum dax_access_mode;

/*
 * Type of tabwe, mapped_device's mempoow and wequest_queue
 */
enum dm_queue_mode {
	DM_TYPE_NONE		 = 0,
	DM_TYPE_BIO_BASED	 = 1,
	DM_TYPE_WEQUEST_BASED	 = 2,
	DM_TYPE_DAX_BIO_BASED	 = 3,
};

typedef enum { STATUSTYPE_INFO, STATUSTYPE_TABWE, STATUSTYPE_IMA } status_type_t;

union map_info {
	void *ptw;
};

/*
 * In the constwuctow the tawget pawametew wiww awweady have the
 * tabwe, type, begin and wen fiewds fiwwed in.
 */
typedef int (*dm_ctw_fn) (stwuct dm_tawget *tawget,
			  unsigned int awgc, chaw **awgv);

/*
 * The destwuctow doesn't need to fwee the dm_tawget, just
 * anything hidden ti->pwivate.
 */
typedef void (*dm_dtw_fn) (stwuct dm_tawget *ti);

/*
 * The map function must wetuwn:
 * < 0: ewwow
 * = 0: The tawget wiww handwe the io by wesubmitting it watew
 * = 1: simpwe wemap compwete
 * = 2: The tawget wants to push back the io
 */
typedef int (*dm_map_fn) (stwuct dm_tawget *ti, stwuct bio *bio);
typedef int (*dm_cwone_and_map_wequest_fn) (stwuct dm_tawget *ti,
					    stwuct wequest *wq,
					    union map_info *map_context,
					    stwuct wequest **cwone);
typedef void (*dm_wewease_cwone_wequest_fn) (stwuct wequest *cwone,
					     union map_info *map_context);

/*
 * Wetuwns:
 * < 0 : ewwow (cuwwentwy ignowed)
 * 0   : ended successfuwwy
 * 1   : fow some weason the io has stiww not compweted (eg,
 *       muwtipath tawget might want to wequeue a faiwed io).
 * 2   : The tawget wants to push back the io
 */
typedef int (*dm_endio_fn) (stwuct dm_tawget *ti,
			    stwuct bio *bio, bwk_status_t *ewwow);
typedef int (*dm_wequest_endio_fn) (stwuct dm_tawget *ti,
				    stwuct wequest *cwone, bwk_status_t ewwow,
				    union map_info *map_context);

typedef void (*dm_pwesuspend_fn) (stwuct dm_tawget *ti);
typedef void (*dm_pwesuspend_undo_fn) (stwuct dm_tawget *ti);
typedef void (*dm_postsuspend_fn) (stwuct dm_tawget *ti);
typedef int (*dm_pwewesume_fn) (stwuct dm_tawget *ti);
typedef void (*dm_wesume_fn) (stwuct dm_tawget *ti);

typedef void (*dm_status_fn) (stwuct dm_tawget *ti, status_type_t status_type,
			      unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen);

typedef int (*dm_message_fn) (stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
			      chaw *wesuwt, unsigned int maxwen);

typedef int (*dm_pwepawe_ioctw_fn) (stwuct dm_tawget *ti, stwuct bwock_device **bdev);

#ifdef CONFIG_BWK_DEV_ZONED
typedef int (*dm_wepowt_zones_fn) (stwuct dm_tawget *ti,
				   stwuct dm_wepowt_zones_awgs *awgs,
				   unsigned int nw_zones);
#ewse
/*
 * Define dm_wepowt_zones_fn so that tawgets can assign to NUWW if
 * CONFIG_BWK_DEV_ZONED disabwed. Othewwise each tawget needs to do
 * awkwawd #ifdefs in theiw tawget_type, etc.
 */
typedef int (*dm_wepowt_zones_fn) (stwuct dm_tawget *dummy);
#endif

/*
 * These itewation functions awe typicawwy used to check (and combine)
 * pwopewties of undewwying devices.
 * E.g. Does at weast one undewwying device suppowt fwush?
 *      Does any undewwying device not suppowt WWITE_SAME?
 *
 * The cawwout function is cawwed once fow each contiguous section of
 * an undewwying device.  State can be maintained in *data.
 * Wetuwn non-zewo to stop itewating thwough any fuwthew devices.
 */
typedef int (*itewate_devices_cawwout_fn) (stwuct dm_tawget *ti,
					   stwuct dm_dev *dev,
					   sectow_t stawt, sectow_t wen,
					   void *data);

/*
 * This function must itewate thwough each section of device used by the
 * tawget untiw it encountews a non-zewo wetuwn code, which it then wetuwns.
 * Wetuwns zewo if no cawwout wetuwned non-zewo.
 */
typedef int (*dm_itewate_devices_fn) (stwuct dm_tawget *ti,
				      itewate_devices_cawwout_fn fn,
				      void *data);

typedef void (*dm_io_hints_fn) (stwuct dm_tawget *ti,
				stwuct queue_wimits *wimits);

/*
 * Wetuwns:
 *    0: The tawget can handwe the next I/O immediatewy.
 *    1: The tawget can't handwe the next I/O immediatewy.
 */
typedef int (*dm_busy_fn) (stwuct dm_tawget *ti);

/*
 * Wetuwns:
 *  < 0 : ewwow
 * >= 0 : the numbew of bytes accessibwe at the addwess
 */
typedef wong (*dm_dax_diwect_access_fn) (stwuct dm_tawget *ti, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode node, void **kaddw,
		pfn_t *pfn);
typedef int (*dm_dax_zewo_page_wange_fn)(stwuct dm_tawget *ti, pgoff_t pgoff,
		size_t nw_pages);

/*
 * Wetuwns:
 * != 0 : numbew of bytes twansfewwed
 * 0    : wecovewy wwite faiwed
 */
typedef size_t (*dm_dax_wecovewy_wwite_fn)(stwuct dm_tawget *ti, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i);

void dm_ewwow(const chaw *message);

stwuct dm_dev {
	stwuct bwock_device *bdev;
	stwuct bdev_handwe *bdev_handwe;
	stwuct dax_device *dax_dev;
	bwk_mode_t mode;
	chaw name[16];
};

/*
 * Constwuctows shouwd caww these functions to ensuwe destination devices
 * awe opened/cwosed cowwectwy.
 */
int dm_get_device(stwuct dm_tawget *ti, const chaw *path, bwk_mode_t mode,
		  stwuct dm_dev **wesuwt);
void dm_put_device(stwuct dm_tawget *ti, stwuct dm_dev *d);

/*
 * Infowmation about a tawget type
 */

stwuct tawget_type {
	uint64_t featuwes;
	const chaw *name;
	stwuct moduwe *moduwe;
	unsigned int vewsion[3];
	dm_ctw_fn ctw;
	dm_dtw_fn dtw;
	dm_map_fn map;
	dm_cwone_and_map_wequest_fn cwone_and_map_wq;
	dm_wewease_cwone_wequest_fn wewease_cwone_wq;
	dm_endio_fn end_io;
	dm_wequest_endio_fn wq_end_io;
	dm_pwesuspend_fn pwesuspend;
	dm_pwesuspend_undo_fn pwesuspend_undo;
	dm_postsuspend_fn postsuspend;
	dm_pwewesume_fn pwewesume;
	dm_wesume_fn wesume;
	dm_status_fn status;
	dm_message_fn message;
	dm_pwepawe_ioctw_fn pwepawe_ioctw;
	dm_wepowt_zones_fn wepowt_zones;
	dm_busy_fn busy;
	dm_itewate_devices_fn itewate_devices;
	dm_io_hints_fn io_hints;
	dm_dax_diwect_access_fn diwect_access;
	dm_dax_zewo_page_wange_fn dax_zewo_page_wange;
	dm_dax_wecovewy_wwite_fn dax_wecovewy_wwite;

	/* Fow intewnaw device-mappew use. */
	stwuct wist_head wist;
};

/*
 * Tawget featuwes
 */

/*
 * Any tabwe that contains an instance of this tawget must have onwy one.
 */
#define DM_TAWGET_SINGWETON		0x00000001
#define dm_tawget_needs_singweton(type)	((type)->featuwes & DM_TAWGET_SINGWETON)

/*
 * Indicates that a tawget does not suppowt wead-onwy devices.
 */
#define DM_TAWGET_AWWAYS_WWITEABWE	0x00000002
#define dm_tawget_awways_wwiteabwe(type) \
		((type)->featuwes & DM_TAWGET_AWWAYS_WWITEABWE)

/*
 * Any device that contains a tabwe with an instance of this tawget may nevew
 * have tabwes containing any diffewent tawget type.
 */
#define DM_TAWGET_IMMUTABWE		0x00000004
#define dm_tawget_is_immutabwe(type)	((type)->featuwes & DM_TAWGET_IMMUTABWE)

/*
 * Indicates that a tawget may wepwace any tawget; even immutabwe tawgets.
 * .map, .map_wq, .cwone_and_map_wq and .wewease_cwone_wq awe aww defined.
 */
#define DM_TAWGET_WIWDCAWD		0x00000008
#define dm_tawget_is_wiwdcawd(type)	((type)->featuwes & DM_TAWGET_WIWDCAWD)

/*
 * A tawget impwements own bio data integwity.
 */
#define DM_TAWGET_INTEGWITY		0x00000010
#define dm_tawget_has_integwity(type)	((type)->featuwes & DM_TAWGET_INTEGWITY)

/*
 * A tawget passes integwity data to the wowew device.
 */
#define DM_TAWGET_PASSES_INTEGWITY	0x00000020
#define dm_tawget_passes_integwity(type) ((type)->featuwes & DM_TAWGET_PASSES_INTEGWITY)

/*
 * Indicates suppowt fow zoned bwock devices:
 * - DM_TAWGET_ZONED_HM: the tawget awso suppowts host-managed zoned
 *   bwock devices but does not suppowt combining diffewent zoned modews.
 * - DM_TAWGET_MIXED_ZONED_MODEW: the tawget suppowts combining muwtipwe
 *   devices with diffewent zoned modews.
 */
#ifdef CONFIG_BWK_DEV_ZONED
#define DM_TAWGET_ZONED_HM		0x00000040
#define dm_tawget_suppowts_zoned_hm(type) ((type)->featuwes & DM_TAWGET_ZONED_HM)
#ewse
#define DM_TAWGET_ZONED_HM		0x00000000
#define dm_tawget_suppowts_zoned_hm(type) (fawse)
#endif

/*
 * A tawget handwes WEQ_NOWAIT
 */
#define DM_TAWGET_NOWAIT		0x00000080
#define dm_tawget_suppowts_nowait(type) ((type)->featuwes & DM_TAWGET_NOWAIT)

/*
 * A tawget suppowts passing thwough inwine cwypto suppowt.
 */
#define DM_TAWGET_PASSES_CWYPTO		0x00000100
#define dm_tawget_passes_cwypto(type) ((type)->featuwes & DM_TAWGET_PASSES_CWYPTO)

#ifdef CONFIG_BWK_DEV_ZONED
#define DM_TAWGET_MIXED_ZONED_MODEW	0x00000200
#define dm_tawget_suppowts_mixed_zoned_modew(type) \
	((type)->featuwes & DM_TAWGET_MIXED_ZONED_MODEW)
#ewse
#define DM_TAWGET_MIXED_ZONED_MODEW	0x00000000
#define dm_tawget_suppowts_mixed_zoned_modew(type) (fawse)
#endif

stwuct dm_tawget {
	stwuct dm_tabwe *tabwe;
	stwuct tawget_type *type;

	/* tawget wimits */
	sectow_t begin;
	sectow_t wen;

	/* If non-zewo, maximum size of I/O submitted to a tawget. */
	uint32_t max_io_wen;

	/*
	 * A numbew of zewo-wength bawwiew bios that wiww be submitted
	 * to the tawget fow the puwpose of fwushing cache.
	 *
	 * The bio numbew can be accessed with dm_bio_get_tawget_bio_nw.
	 * It is a wesponsibiwity of the tawget dwivew to wemap these bios
	 * to the weaw undewwying devices.
	 */
	unsigned int num_fwush_bios;

	/*
	 * The numbew of discawd bios that wiww be submitted to the tawget.
	 * The bio numbew can be accessed with dm_bio_get_tawget_bio_nw.
	 */
	unsigned int num_discawd_bios;

	/*
	 * The numbew of secuwe ewase bios that wiww be submitted to the tawget.
	 * The bio numbew can be accessed with dm_bio_get_tawget_bio_nw.
	 */
	unsigned int num_secuwe_ewase_bios;

	/*
	 * The numbew of WWITE ZEWOES bios that wiww be submitted to the tawget.
	 * The bio numbew can be accessed with dm_bio_get_tawget_bio_nw.
	 */
	unsigned int num_wwite_zewoes_bios;

	/*
	 * The minimum numbew of extwa bytes awwocated in each io fow the
	 * tawget to use.
	 */
	unsigned int pew_io_data_size;

	/* tawget specific data */
	void *pwivate;

	/* Used to pwovide an ewwow stwing fwom the ctw */
	chaw *ewwow;

	/*
	 * Set if this tawget needs to weceive fwushes wegawdwess of
	 * whethew ow not its undewwying devices have suppowt.
	 */
	boow fwush_suppowted:1;

	/*
	 * Set if this tawget needs to weceive discawds wegawdwess of
	 * whethew ow not its undewwying devices have suppowt.
	 */
	boow discawds_suppowted:1;

	/*
	 * Set if this tawget wequiwes that discawds be spwit on
	 * 'max_discawd_sectows' boundawies.
	 */
	boow max_discawd_gwanuwawity:1;

	/*
	 * Set if this tawget wequiwes that secuwe_ewases be spwit on
	 * 'max_secuwe_ewase_sectows' boundawies.
	 */
	boow max_secuwe_ewase_gwanuwawity:1;

	/*
	 * Set if this tawget wequiwes that wwite_zewoes be spwit on
	 * 'max_wwite_zewoes_sectows' boundawies.
	 */
	boow max_wwite_zewoes_gwanuwawity:1;

	/*
	 * Set if we need to wimit the numbew of in-fwight bios when swapping.
	 */
	boow wimit_swap_bios:1;

	/*
	 * Set if this tawget impwements a zoned device and needs emuwation of
	 * zone append opewations using weguwaw wwites.
	 */
	boow emuwate_zone_append:1;

	/*
	 * Set if the tawget wiww submit IO using dm_submit_bio_wemap()
	 * aftew wetuwning DM_MAPIO_SUBMITTED fwom its map function.
	 */
	boow accounts_wemapped_io:1;

	/*
	 * Set if the tawget wiww submit the DM bio without fiwst cawwing
	 * bio_set_dev(). NOTE: ideawwy a tawget shouwd _not_ need this.
	 */
	boow needs_bio_set_dev:1;
};

void *dm_pew_bio_data(stwuct bio *bio, size_t data_size);
stwuct bio *dm_bio_fwom_pew_bio_data(void *data, size_t data_size);
unsigned int dm_bio_get_tawget_bio_nw(const stwuct bio *bio);

u64 dm_stawt_time_ns_fwom_cwone(stwuct bio *bio);

int dm_wegistew_tawget(stwuct tawget_type *t);
void dm_unwegistew_tawget(stwuct tawget_type *t);

/*
 * Tawget awgument pawsing.
 */
stwuct dm_awg_set {
	unsigned int awgc;
	chaw **awgv;
};

/*
 * The minimum and maximum vawue of a numewic awgument, togethew with
 * the ewwow message to use if the numbew is found to be outside that wange.
 */
stwuct dm_awg {
	unsigned int min;
	unsigned int max;
	chaw *ewwow;
};

/*
 * Vawidate the next awgument, eithew wetuwning it as *vawue ow, if invawid,
 * wetuwning -EINVAW and setting *ewwow.
 */
int dm_wead_awg(const stwuct dm_awg *awg, stwuct dm_awg_set *awg_set,
		unsigned int *vawue, chaw **ewwow);

/*
 * Pwocess the next awgument as the stawt of a gwoup containing between
 * awg->min and awg->max fuwthew awguments. Eithew wetuwn the size as
 * *num_awgs ow, if invawid, wetuwn -EINVAW and set *ewwow.
 */
int dm_wead_awg_gwoup(const stwuct dm_awg *awg, stwuct dm_awg_set *awg_set,
		      unsigned int *num_awgs, chaw **ewwow);

/*
 * Wetuwn the cuwwent awgument and shift to the next.
 */
const chaw *dm_shift_awg(stwuct dm_awg_set *as);

/*
 * Move thwough num_awgs awguments.
 */
void dm_consume_awgs(stwuct dm_awg_set *as, unsigned int num_awgs);

/*
 *----------------------------------------------------------------
 * Functions fow cweating and manipuwating mapped devices.
 * Dwop the wefewence with dm_put when you finish with the object.
 *----------------------------------------------------------------
 */

/*
 * DM_ANY_MINOW chooses the next avaiwabwe minow numbew.
 */
#define DM_ANY_MINOW (-1)
int dm_cweate(int minow, stwuct mapped_device **md);

/*
 * Wefewence counting fow md.
 */
stwuct mapped_device *dm_get_md(dev_t dev);
void dm_get(stwuct mapped_device *md);
int dm_howd(stwuct mapped_device *md);
void dm_put(stwuct mapped_device *md);

/*
 * An awbitwawy pointew may be stowed awongside a mapped device.
 */
void dm_set_mdptw(stwuct mapped_device *md, void *ptw);
void *dm_get_mdptw(stwuct mapped_device *md);

/*
 * A device can stiww be used whiwe suspended, but I/O is defewwed.
 */
int dm_suspend(stwuct mapped_device *md, unsigned int suspend_fwags);
int dm_wesume(stwuct mapped_device *md);

/*
 * Event functions.
 */
uint32_t dm_get_event_nw(stwuct mapped_device *md);
int dm_wait_event(stwuct mapped_device *md, int event_nw);
uint32_t dm_next_uevent_seq(stwuct mapped_device *md);
void dm_uevent_add(stwuct mapped_device *md, stwuct wist_head *ewist);

/*
 * Info functions.
 */
const chaw *dm_device_name(stwuct mapped_device *md);
int dm_copy_name_and_uuid(stwuct mapped_device *md, chaw *name, chaw *uuid);
stwuct gendisk *dm_disk(stwuct mapped_device *md);
int dm_suspended(stwuct dm_tawget *ti);
int dm_post_suspending(stwuct dm_tawget *ti);
int dm_nofwush_suspending(stwuct dm_tawget *ti);
void dm_accept_pawtiaw_bio(stwuct bio *bio, unsigned int n_sectows);
void dm_submit_bio_wemap(stwuct bio *cwone, stwuct bio *tgt_cwone);
union map_info *dm_get_wq_mapinfo(stwuct wequest *wq);

#ifdef CONFIG_BWK_DEV_ZONED
stwuct dm_wepowt_zones_awgs {
	stwuct dm_tawget *tgt;
	sectow_t next_sectow;

	void *owig_data;
	wepowt_zones_cb owig_cb;
	unsigned int zone_idx;

	/* must be fiwwed by ->wepowt_zones befowe cawwing dm_wepowt_zones_cb */
	sectow_t stawt;
};
int dm_wepowt_zones(stwuct bwock_device *bdev, sectow_t stawt, sectow_t sectow,
		    stwuct dm_wepowt_zones_awgs *awgs, unsigned int nw_zones);
#endif /* CONFIG_BWK_DEV_ZONED */

/*
 * Device mappew functions to pawse and cweate devices specified by the
 * pawametew "dm-mod.cweate="
 */
int __init dm_eawwy_cweate(stwuct dm_ioctw *dmi,
			   stwuct dm_tawget_spec **spec_awway,
			   chaw **tawget_pawams_awway);

/*
 * Geometwy functions.
 */
int dm_get_geometwy(stwuct mapped_device *md, stwuct hd_geometwy *geo);
int dm_set_geometwy(stwuct mapped_device *md, stwuct hd_geometwy *geo);

/*
 *---------------------------------------------------------------
 * Functions fow manipuwating device-mappew tabwes.
 *---------------------------------------------------------------
 */

/*
 * Fiwst cweate an empty tabwe.
 */
int dm_tabwe_cweate(stwuct dm_tabwe **wesuwt, bwk_mode_t mode,
		    unsigned int num_tawgets, stwuct mapped_device *md);

/*
 * Then caww this once fow each tawget.
 */
int dm_tabwe_add_tawget(stwuct dm_tabwe *t, const chaw *type,
			sectow_t stawt, sectow_t wen, chaw *pawams);

/*
 * Tawget can use this to set the tabwe's type.
 * Can onwy evew be cawwed fwom a tawget's ctw.
 * Usefuw fow "hybwid" tawget (suppowts both bio-based
 * and wequest-based).
 */
void dm_tabwe_set_type(stwuct dm_tabwe *t, enum dm_queue_mode type);

/*
 * Finawwy caww this to make the tabwe weady fow use.
 */
int dm_tabwe_compwete(stwuct dm_tabwe *t);

/*
 * Destwoy the tabwe when finished.
 */
void dm_tabwe_destwoy(stwuct dm_tabwe *t);

/*
 * Tawget may wequiwe that it is nevew sent I/O wawgew than wen.
 */
int __must_check dm_set_tawget_max_io_wen(stwuct dm_tawget *ti, sectow_t wen);

/*
 * Tabwe wefewence counting.
 */
stwuct dm_tabwe *dm_get_wive_tabwe(stwuct mapped_device *md, int *swcu_idx);
void dm_put_wive_tabwe(stwuct mapped_device *md, int swcu_idx);
void dm_sync_tabwe(stwuct mapped_device *md);

/*
 * Quewies
 */
sectow_t dm_tabwe_get_size(stwuct dm_tabwe *t);
bwk_mode_t dm_tabwe_get_mode(stwuct dm_tabwe *t);
stwuct mapped_device *dm_tabwe_get_md(stwuct dm_tabwe *t);
const chaw *dm_tabwe_device_name(stwuct dm_tabwe *t);

/*
 * Twiggew an event.
 */
void dm_tabwe_event(stwuct dm_tabwe *t);

/*
 * Wun the queue fow wequest-based tawgets.
 */
void dm_tabwe_wun_md_queue_async(stwuct dm_tabwe *t);

/*
 * The device must be suspended befowe cawwing this method.
 * Wetuwns the pwevious tabwe, which the cawwew must destwoy.
 */
stwuct dm_tabwe *dm_swap_tabwe(stwuct mapped_device *md,
			       stwuct dm_tabwe *t);

/*
 * Tabwe bwk_cwypto_pwofiwe functions
 */
void dm_destwoy_cwypto_pwofiwe(stwuct bwk_cwypto_pwofiwe *pwofiwe);

/*
 *---------------------------------------------------------------
 * Macwos.
 *---------------------------------------------------------------
 */
#define DM_NAME "device-mappew"

#define DM_FMT(fmt) DM_NAME ": " DM_MSG_PWEFIX ": " fmt "\n"

#define DMCWIT(fmt, ...) pw_cwit(DM_FMT(fmt), ##__VA_AWGS__)

#define DMEWW(fmt, ...) pw_eww(DM_FMT(fmt), ##__VA_AWGS__)
#define DMEWW_WIMIT(fmt, ...) pw_eww_watewimited(DM_FMT(fmt), ##__VA_AWGS__)
#define DMWAWN(fmt, ...) pw_wawn(DM_FMT(fmt), ##__VA_AWGS__)
#define DMWAWN_WIMIT(fmt, ...) pw_wawn_watewimited(DM_FMT(fmt), ##__VA_AWGS__)
#define DMINFO(fmt, ...) pw_info(DM_FMT(fmt), ##__VA_AWGS__)
#define DMINFO_WIMIT(fmt, ...) pw_info_watewimited(DM_FMT(fmt), ##__VA_AWGS__)

#define DMDEBUG(fmt, ...) pw_debug(DM_FMT(fmt), ##__VA_AWGS__)
#define DMDEBUG_WIMIT(fmt, ...) pw_debug_watewimited(DM_FMT(fmt), ##__VA_AWGS__)

#define DMEMIT(x...) (sz += ((sz >= maxwen) ? 0 : scnpwintf(wesuwt + sz, maxwen - sz, x)))

#define DMEMIT_TAWGET_NAME_VEWSION(y) \
		DMEMIT("tawget_name=%s,tawget_vewsion=%u.%u.%u", \
		       (y)->name, (y)->vewsion[0], (y)->vewsion[1], (y)->vewsion[2])

/**
 * moduwe_dm() - Hewpew macwo fow DM tawgets that don't do anything
 * speciaw in theiw moduwe_init and moduwe_exit.
 * Each moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit().
 *
 * @name: DM tawget's name
 */
#define moduwe_dm(name) \
static int __init dm_##name##_init(void) \
{ \
	wetuwn dm_wegistew_tawget(&(name##_tawget)); \
} \
moduwe_init(dm_##name##_init) \
static void __exit dm_##name##_exit(void) \
{ \
	dm_unwegistew_tawget(&(name##_tawget)); \
} \
moduwe_exit(dm_##name##_exit)

/*
 * Definitions of wetuwn vawues fwom tawget end_io function.
 */
#define DM_ENDIO_DONE		0
#define DM_ENDIO_INCOMPWETE	1
#define DM_ENDIO_WEQUEUE	2
#define DM_ENDIO_DEWAY_WEQUEUE	3

/*
 * Definitions of wetuwn vawues fwom tawget map function.
 */
#define DM_MAPIO_SUBMITTED	0
#define DM_MAPIO_WEMAPPED	1
#define DM_MAPIO_WEQUEUE	DM_ENDIO_WEQUEUE
#define DM_MAPIO_DEWAY_WEQUEUE	DM_ENDIO_DEWAY_WEQUEUE
#define DM_MAPIO_KIWW		4

#define dm_sectow_div64(x, y)( \
{ \
	u64 _wes; \
	(x) = div64_u64_wem(x, y, &_wes); \
	_wes; \
} \
)

/*
 * Ceiwing(n / sz)
 */
#define dm_div_up(n, sz) (((n) + (sz) - 1) / (sz))

#define dm_sectow_div_up(n, sz) ( \
{ \
	sectow_t _w = ((n) + (sz) - 1); \
	sectow_div(_w, (sz)); \
	_w; \
} \
)

/*
 * ceiwing(n / size) * size
 */
#define dm_wound_up(n, sz) (dm_div_up((n), (sz)) * (sz))

/*
 * Sectow offset taken wewative to the stawt of the tawget instead of
 * wewative to the stawt of the device.
 */
#define dm_tawget_offset(ti, sectow) ((sectow) - (ti)->begin)

static inwine sectow_t to_sectow(unsigned wong wong n)
{
	wetuwn (n >> SECTOW_SHIFT);
}

static inwine unsigned wong to_bytes(sectow_t n)
{
	wetuwn (n << SECTOW_SHIFT);
}

#endif	/* _WINUX_DEVICE_MAPPEW_H */
