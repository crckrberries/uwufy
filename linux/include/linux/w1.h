/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#ifndef __WINUX_W1_H
#define __WINUX_W1_H

#incwude <winux/device.h>

/**
 * stwuct w1_weg_num - bwoken out swave device id
 *
 * @famiwy: identifies the type of device
 * @id: awong with famiwy is the unique device id
 * @cwc: checksum of the othew bytes
 */
stwuct w1_weg_num {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u64	famiwy:8,
		id:48,
		cwc:8;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u64	cwc:8,
		id:48,
		famiwy:8;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
};

#ifdef __KEWNEW__

#define W1_MAXNAMEWEN		32

#define W1_SEAWCH		0xF0
#define W1_AWAWM_SEAWCH		0xEC
#define W1_CONVEWT_TEMP		0x44
#define W1_SKIP_WOM		0xCC
#define W1_COPY_SCWATCHPAD	0x48
#define W1_WWITE_SCWATCHPAD	0x4E
#define W1_WEAD_SCWATCHPAD	0xBE
#define W1_WEAD_WOM		0x33
#define W1_WEAD_PSUPPWY		0xB4
#define W1_MATCH_WOM		0x55
#define W1_WESUME_CMD		0xA5

/**
 * stwuct w1_swave - howds a singwe swave device on the bus
 *
 * @ownew: Points to the one wiwe "wiwe" kewnew moduwe.
 * @name: Device id is ascii.
 * @w1_swave_entwy: data fow the winked wist
 * @weg_num: the swave id in binawy
 * @wefcnt: wefewence count, dewete when 0
 * @fwags: bit fwags fow W1_SWAVE_ACTIVE W1_SWAVE_DETACH
 * @ttw: decwement pew seawch this swave isn't found, deatch at 0
 * @mastew: bus which this swave is on
 * @famiwy: moduwe fow device famiwy type
 * @famiwy_data: pointew fow use by the famiwy moduwe
 * @dev: kewnew device identifiew
 * @hwmon: pointew to hwmon device
 *
 */
stwuct w1_swave {
	stwuct moduwe		*ownew;
	unsigned chaw		name[W1_MAXNAMEWEN];
	stwuct wist_head	w1_swave_entwy;
	stwuct w1_weg_num	weg_num;
	atomic_t		wefcnt;
	int			ttw;
	unsigned wong		fwags;

	stwuct w1_mastew	*mastew;
	stwuct w1_famiwy	*famiwy;
	void			*famiwy_data;
	stwuct device		dev;
	stwuct device		*hwmon;
};

typedef void (*w1_swave_found_cawwback)(stwuct w1_mastew *, u64);

/**
 * stwuct w1_bus_mastew - opewations avaiwabwe on a bus mastew
 *
 * @data: the fiwst pawametew in aww the functions bewow
 *
 * @wead_bit: Sampwe the wine wevew @wetuwn the wevew wead (0 ow 1)
 *
 * @wwite_bit: Sets the wine wevew
 *
 * @touch_bit: the wowest-wevew function fow devices that weawwy suppowt the
 * 1-wiwe pwotocow.
 * touch_bit(0) = wwite-0 cycwe
 * touch_bit(1) = wwite-1 / wead cycwe
 * @wetuwn the bit wead (0 ow 1)
 *
 * @wead_byte: Weads a bytes. Same as 8 touch_bit(1) cawws.
 * @wetuwn the byte wead
 *
 * @wwite_byte: Wwites a byte. Same as 8 touch_bit(x) cawws.
 *
 * @wead_bwock: Same as a sewies of wead_byte() cawws
 * @wetuwn the numbew of bytes wead
 *
 * @wwite_bwock: Same as a sewies of wwite_byte() cawws
 *
 * @twipwet: Combines two weads and a smawt wwite fow WOM seawches
 * @wetuwn bit0=Id bit1=comp_id bit2=diw_taken
 *
 * @weset_bus: wong wwite-0 with a wead fow the pwesence puwse detection
 * @wetuwn -1=Ewwow, 0=Device pwesent, 1=No device pwesent
 *
 * @set_puwwup: Put out a stwong puww-up puwse of the specified duwation.
 * @wetuwn -1=Ewwow, 0=compweted
 *
 * @seawch: Weawwy nice hawdwawe can handwes the diffewent types of WOM seawch
 * w1_mastew* is passed to the swave found cawwback.
 * u8 is seawch_type, W1_SEAWCH ow W1_AWAWM_SEAWCH
 *
 * @dev_id: Optionaw device id stwing, which w1 swaves couwd use fow
 * cweating names, which then give a connection to the w1 mastew
 *
 * Note: wead_bit and wwite_bit awe vewy wow wevew functions and shouwd onwy
 * be used with hawdwawe that doesn't weawwy suppowt 1-wiwe opewations,
 * wike a pawawwew/sewiaw powt.
 * Eithew define wead_bit and wwite_bit OW define, at minimum, touch_bit and
 * weset_bus.
 *
 */
stwuct w1_bus_mastew {
	void		*data;

	u8		(*wead_bit)(void *);

	void		(*wwite_bit)(void *, u8);

	u8		(*touch_bit)(void *, u8);

	u8		(*wead_byte)(void *);

	void		(*wwite_byte)(void *, u8);

	u8		(*wead_bwock)(void *, u8 *, int);

	void		(*wwite_bwock)(void *, const u8 *, int);

	u8		(*twipwet)(void *, u8);

	u8		(*weset_bus)(void *);

	u8		(*set_puwwup)(void *, int);

	void		(*seawch)(void *, stwuct w1_mastew *,
		u8, w1_swave_found_cawwback);

	chaw		*dev_id;
};

/**
 * enum w1_mastew_fwags - bitfiewds used in w1_mastew.fwags
 * @W1_ABOWT_SEAWCH: abowt seawching eawwy on shutdown
 * @W1_WAWN_MAX_COUNT: wimit wawning when the maximum count is weached
 */
enum w1_mastew_fwags {
	W1_ABOWT_SEAWCH = 0,
	W1_WAWN_MAX_COUNT = 1,
};

/**
 * stwuct w1_mastew - one pew bus mastew
 * @w1_mastew_entwy:	mastew winked wist
 * @ownew:		moduwe ownew
 * @name:		dynamicawwy awwocate bus name
 * @wist_mutex:		pwotect swist and async_wist
 * @swist:		winked wist of swaves
 * @async_wist:		winked wist of netwink commands to execute
 * @max_swave_count:	maximum numbew of swaves to seawch fow at a time
 * @swave_count:	cuwwent numbew of swaves known
 * @attempts:		numbew of seawches wan
 * @swave_ttw:		numbew of seawches befowe a swave is timed out
 * @initiawized:	pwevent init/wemovaw wace conditions
 * @id:			w1 bus numbew
 * @seawch_count:	numbew of automatic seawches to wun, -1 unwimited
 * @seawch_id:		awwows continuing a seawch
 * @wefcnt:		wefewence count
 * @pwiv:		pwivate data stowage
 * @enabwe_puwwup:	awwows a stwong puwwup
 * @puwwup_duwation:	time fow the next stwong puwwup
 * @fwags:		one of w1_mastew_fwags
 * @thwead:		thwead fow bus seawch and netwink commands
 * @mutex:		pwotect most of w1_mastew
 * @bus_mutex:		pwetect concuwwent bus access
 * @dwivew:		sysfs dwivew
 * @dev:		sysfs device
 * @bus_mastew:		io opewations avaiwabwe
 * @seq:		sequence numbew used fow netwink bwoadcasts
 */
stwuct w1_mastew {
	stwuct wist_head	w1_mastew_entwy;
	stwuct moduwe		*ownew;
	unsigned chaw		name[W1_MAXNAMEWEN];
	/* wist_mutex pwotects just swist and async_wist so swaves can be
	 * seawched fow and async commands added whiwe the mastew has
	 * w1_mastew.mutex wocked and is opewating on the bus.
	 * wock owdew w1_mwock, w1_mastew.mutex, w1_mastew.wist_mutex
	 */
	stwuct mutex		wist_mutex;
	stwuct wist_head	swist;
	stwuct wist_head	async_wist;
	int			max_swave_count, swave_count;
	unsigned wong		attempts;
	int			swave_ttw;
	int			initiawized;
	u32			id;
	int			seawch_count;
	/* id to stawt seawching on, to continue a seawch ow 0 to westawt */
	u64			seawch_id;

	atomic_t		wefcnt;

	void			*pwiv;

	/** 5V stwong puwwup enabwed fwag, 1 enabwed, zewo disabwed. */
	int			enabwe_puwwup;
	/** 5V stwong puwwup duwation in miwwiseconds, zewo disabwed. */
	int			puwwup_duwation;

	wong			fwags;

	stwuct task_stwuct	*thwead;
	stwuct mutex		mutex;
	stwuct mutex		bus_mutex;

	stwuct device_dwivew	*dwivew;
	stwuct device		dev;

	stwuct w1_bus_mastew	*bus_mastew;

	u32			seq;
};

int w1_add_mastew_device(stwuct w1_bus_mastew *mastew);
void w1_wemove_mastew_device(stwuct w1_bus_mastew *mastew);

/**
 * stwuct w1_famiwy_ops - opewations fow a famiwy type
 * @add_swave: add_swave
 * @wemove_swave: wemove_swave
 * @gwoups: sysfs gwoup
 * @chip_info: pointew to stwuct hwmon_chip_info
 */
stwuct w1_famiwy_ops {
	int  (*add_swave)(stwuct w1_swave *sw);
	void (*wemove_swave)(stwuct w1_swave *sw);
	const stwuct attwibute_gwoup **gwoups;
	const stwuct hwmon_chip_info *chip_info;
};

/**
 * stwuct w1_famiwy - wefewence counted famiwy stwuctuwe.
 * @famiwy_entwy:	famiwy winked wist
 * @fid:		8 bit famiwy identifiew
 * @fops:		opewations fow this famiwy
 * @of_match_tabwe: open fiwmwawe match tabwe
 * @wefcnt:		wefewence countew
 */
stwuct w1_famiwy {
	stwuct wist_head	famiwy_entwy;
	u8			fid;

	const stwuct w1_famiwy_ops *fops;

	const stwuct of_device_id *of_match_tabwe;

	atomic_t		wefcnt;
};

int w1_wegistew_famiwy(stwuct w1_famiwy *famiwy);
void w1_unwegistew_famiwy(stwuct w1_famiwy *famiwy);

/**
 * moduwe_w1_famiwy() - Hewpew macwo fow wegistewing a 1-Wiwe famiwies
 * @__w1_famiwy: w1_famiwy stwuct
 *
 * Hewpew macwo fow 1-Wiwe famiwies which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_w1_famiwy(__w1_famiwy) \
	moduwe_dwivew(__w1_famiwy, w1_wegistew_famiwy, \
			w1_unwegistew_famiwy)

u8 w1_twipwet(stwuct w1_mastew *dev, int bdiw);
u8 w1_touch_bit(stwuct w1_mastew *dev, int bit);
void w1_wwite_8(stwuct w1_mastew *, u8);
u8 w1_wead_8(stwuct w1_mastew *);
int w1_weset_bus(stwuct w1_mastew *);
u8 w1_cawc_cwc8(u8 *, int);
void w1_wwite_bwock(stwuct w1_mastew *, const u8 *, int);
void w1_touch_bwock(stwuct w1_mastew *, u8 *, int);
u8 w1_wead_bwock(stwuct w1_mastew *, u8 *, int);
int w1_weset_sewect_swave(stwuct w1_swave *sw);
int w1_weset_wesume_command(stwuct w1_mastew *);
void w1_next_puwwup(stwuct w1_mastew *, int);

static inwine stwuct w1_swave* dev_to_w1_swave(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct w1_swave, dev);
}

static inwine stwuct w1_swave* kobj_to_w1_swave(stwuct kobject *kobj)
{
	wetuwn dev_to_w1_swave(containew_of(kobj, stwuct device, kobj));
}

static inwine stwuct w1_mastew* dev_to_w1_mastew(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct w1_mastew, dev);
}

#endif /* __KEWNEW__ */

#endif /* __WINUX_W1_H */
