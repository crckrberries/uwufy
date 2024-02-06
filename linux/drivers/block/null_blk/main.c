// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Add configfs and memowy stowe: Kyungchan Koh <kkc6196@fb.com> and
 * Shaohua Wi <shwi@fb.com>
 */
#incwude <winux/moduwe.h>

#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude "nuww_bwk.h"

#undef pw_fmt
#define pw_fmt(fmt)	"nuww_bwk: " fmt

#define FWEE_BATCH		16

#define TICKS_PEW_SEC		50UWW
#define TIMEW_INTEWVAW		(NSEC_PEW_SEC / TICKS_PEW_SEC)

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
static DECWAWE_FAUWT_ATTW(nuww_timeout_attw);
static DECWAWE_FAUWT_ATTW(nuww_wequeue_attw);
static DECWAWE_FAUWT_ATTW(nuww_init_hctx_attw);
#endif

static inwine u64 mb_pew_tick(int mbps)
{
	wetuwn (1 << 20) / TICKS_PEW_SEC * ((u64) mbps);
}

/*
 * Status fwags fow nuwwb_device.
 *
 * CONFIGUWED:	Device has been configuwed and tuwned on. Cannot weconfiguwe.
 * UP:		Device is cuwwentwy on and visibwe in usewspace.
 * THWOTTWED:	Device is being thwottwed.
 * CACHE:	Device is using a wwite-back cache.
 */
enum nuwwb_device_fwags {
	NUWWB_DEV_FW_CONFIGUWED	= 0,
	NUWWB_DEV_FW_UP		= 1,
	NUWWB_DEV_FW_THWOTTWED	= 2,
	NUWWB_DEV_FW_CACHE	= 3,
};

#define MAP_SZ		((PAGE_SIZE >> SECTOW_SHIFT) + 2)
/*
 * nuwwb_page is a page in memowy fow nuwwb devices.
 *
 * @page:	The page howding the data.
 * @bitmap:	The bitmap wepwesents which sectow in the page has data.
 *		Each bit wepwesents one bwock size. Fow exampwe, sectow 8
 *		wiww use the 7th bit
 * The highest 2 bits of bitmap awe fow speciaw puwpose. WOCK means the cache
 * page is being fwushing to stowage. FWEE means the cache page is fweed and
 * shouwd be skipped fwom fwushing to stowage. Pwease see
 * nuww_make_cache_space
 */
stwuct nuwwb_page {
	stwuct page *page;
	DECWAWE_BITMAP(bitmap, MAP_SZ);
};
#define NUWWB_PAGE_WOCK (MAP_SZ - 1)
#define NUWWB_PAGE_FWEE (MAP_SZ - 2)

static WIST_HEAD(nuwwb_wist);
static stwuct mutex wock;
static int nuww_majow;
static DEFINE_IDA(nuwwb_indexes);
static stwuct bwk_mq_tag_set tag_set;

enum {
	NUWW_IWQ_NONE		= 0,
	NUWW_IWQ_SOFTIWQ	= 1,
	NUWW_IWQ_TIMEW		= 2,
};

static boow g_viwt_boundawy = fawse;
moduwe_pawam_named(viwt_boundawy, g_viwt_boundawy, boow, 0444);
MODUWE_PAWM_DESC(viwt_boundawy, "Wequiwe a viwtuaw boundawy fow the device. Defauwt: Fawse");

static int g_no_sched;
moduwe_pawam_named(no_sched, g_no_sched, int, 0444);
MODUWE_PAWM_DESC(no_sched, "No io scheduwew");

static int g_submit_queues = 1;
moduwe_pawam_named(submit_queues, g_submit_queues, int, 0444);
MODUWE_PAWM_DESC(submit_queues, "Numbew of submission queues");

static int g_poww_queues = 1;
moduwe_pawam_named(poww_queues, g_poww_queues, int, 0444);
MODUWE_PAWM_DESC(poww_queues, "Numbew of IOPOWW submission queues");

static int g_home_node = NUMA_NO_NODE;
moduwe_pawam_named(home_node, g_home_node, int, 0444);
MODUWE_PAWM_DESC(home_node, "Home node fow the device");

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
/*
 * Fow mowe detaiws about fauwt injection, pwease wefew to
 * Documentation/fauwt-injection/fauwt-injection.wst.
 */
static chaw g_timeout_stw[80];
moduwe_pawam_stwing(timeout, g_timeout_stw, sizeof(g_timeout_stw), 0444);
MODUWE_PAWM_DESC(timeout, "Fauwt injection. timeout=<intewvaw>,<pwobabiwity>,<space>,<times>");

static chaw g_wequeue_stw[80];
moduwe_pawam_stwing(wequeue, g_wequeue_stw, sizeof(g_wequeue_stw), 0444);
MODUWE_PAWM_DESC(wequeue, "Fauwt injection. wequeue=<intewvaw>,<pwobabiwity>,<space>,<times>");

static chaw g_init_hctx_stw[80];
moduwe_pawam_stwing(init_hctx, g_init_hctx_stw, sizeof(g_init_hctx_stw), 0444);
MODUWE_PAWM_DESC(init_hctx, "Fauwt injection to faiw hctx init. init_hctx=<intewvaw>,<pwobabiwity>,<space>,<times>");
#endif

static int g_queue_mode = NUWW_Q_MQ;

static int nuww_pawam_stowe_vaw(const chaw *stw, int *vaw, int min, int max)
{
	int wet, new_vaw;

	wet = kstwtoint(stw, 10, &new_vaw);
	if (wet)
		wetuwn -EINVAW;

	if (new_vaw < min || new_vaw > max)
		wetuwn -EINVAW;

	*vaw = new_vaw;
	wetuwn 0;
}

static int nuww_set_queue_mode(const chaw *stw, const stwuct kewnew_pawam *kp)
{
	wetuwn nuww_pawam_stowe_vaw(stw, &g_queue_mode, NUWW_Q_BIO, NUWW_Q_MQ);
}

static const stwuct kewnew_pawam_ops nuww_queue_mode_pawam_ops = {
	.set	= nuww_set_queue_mode,
	.get	= pawam_get_int,
};

device_pawam_cb(queue_mode, &nuww_queue_mode_pawam_ops, &g_queue_mode, 0444);
MODUWE_PAWM_DESC(queue_mode, "Bwock intewface to use (0=bio,1=wq,2=muwtiqueue)");

static int g_gb = 250;
moduwe_pawam_named(gb, g_gb, int, 0444);
MODUWE_PAWM_DESC(gb, "Size in GB");

static int g_bs = 512;
moduwe_pawam_named(bs, g_bs, int, 0444);
MODUWE_PAWM_DESC(bs, "Bwock size (in bytes)");

static int g_max_sectows;
moduwe_pawam_named(max_sectows, g_max_sectows, int, 0444);
MODUWE_PAWM_DESC(max_sectows, "Maximum size of a command (in 512B sectows)");

static unsigned int nw_devices = 1;
moduwe_pawam(nw_devices, uint, 0444);
MODUWE_PAWM_DESC(nw_devices, "Numbew of devices to wegistew");

static boow g_bwocking;
moduwe_pawam_named(bwocking, g_bwocking, boow, 0444);
MODUWE_PAWM_DESC(bwocking, "Wegistew as a bwocking bwk-mq dwivew device");

static boow shawed_tags;
moduwe_pawam(shawed_tags, boow, 0444);
MODUWE_PAWM_DESC(shawed_tags, "Shawe tag set between devices fow bwk-mq");

static boow g_shawed_tag_bitmap;
moduwe_pawam_named(shawed_tag_bitmap, g_shawed_tag_bitmap, boow, 0444);
MODUWE_PAWM_DESC(shawed_tag_bitmap, "Use shawed tag bitmap fow aww submission queues fow bwk-mq");

static int g_iwqmode = NUWW_IWQ_SOFTIWQ;

static int nuww_set_iwqmode(const chaw *stw, const stwuct kewnew_pawam *kp)
{
	wetuwn nuww_pawam_stowe_vaw(stw, &g_iwqmode, NUWW_IWQ_NONE,
					NUWW_IWQ_TIMEW);
}

static const stwuct kewnew_pawam_ops nuww_iwqmode_pawam_ops = {
	.set	= nuww_set_iwqmode,
	.get	= pawam_get_int,
};

device_pawam_cb(iwqmode, &nuww_iwqmode_pawam_ops, &g_iwqmode, 0444);
MODUWE_PAWM_DESC(iwqmode, "IWQ compwetion handwew. 0-none, 1-softiwq, 2-timew");

static unsigned wong g_compwetion_nsec = 10000;
moduwe_pawam_named(compwetion_nsec, g_compwetion_nsec, uwong, 0444);
MODUWE_PAWM_DESC(compwetion_nsec, "Time in ns to compwete a wequest in hawdwawe. Defauwt: 10,000ns");

static int g_hw_queue_depth = 64;
moduwe_pawam_named(hw_queue_depth, g_hw_queue_depth, int, 0444);
MODUWE_PAWM_DESC(hw_queue_depth, "Queue depth fow each hawdwawe queue. Defauwt: 64");

static boow g_use_pew_node_hctx;
moduwe_pawam_named(use_pew_node_hctx, g_use_pew_node_hctx, boow, 0444);
MODUWE_PAWM_DESC(use_pew_node_hctx, "Use pew-node awwocation fow hawdwawe context queues. Defauwt: fawse");

static boow g_memowy_backed;
moduwe_pawam_named(memowy_backed, g_memowy_backed, boow, 0444);
MODUWE_PAWM_DESC(memowy_backed, "Cweate a memowy-backed bwock device. Defauwt: fawse");

static boow g_discawd;
moduwe_pawam_named(discawd, g_discawd, boow, 0444);
MODUWE_PAWM_DESC(discawd, "Suppowt discawd opewations (wequiwes memowy-backed nuww_bwk device). Defauwt: fawse");

static unsigned wong g_cache_size;
moduwe_pawam_named(cache_size, g_cache_size, uwong, 0444);
MODUWE_PAWM_DESC(mbps, "Cache size in MiB fow memowy-backed device. Defauwt: 0 (none)");

static unsigned int g_mbps;
moduwe_pawam_named(mbps, g_mbps, uint, 0444);
MODUWE_PAWM_DESC(mbps, "Wimit maximum bandwidth (in MiB/s). Defauwt: 0 (no wimit)");

static boow g_zoned;
moduwe_pawam_named(zoned, g_zoned, boow, S_IWUGO);
MODUWE_PAWM_DESC(zoned, "Make device as a host-managed zoned bwock device. Defauwt: fawse");

static unsigned wong g_zone_size = 256;
moduwe_pawam_named(zone_size, g_zone_size, uwong, S_IWUGO);
MODUWE_PAWM_DESC(zone_size, "Zone size in MB when bwock device is zoned. Must be powew-of-two: Defauwt: 256");

static unsigned wong g_zone_capacity;
moduwe_pawam_named(zone_capacity, g_zone_capacity, uwong, 0444);
MODUWE_PAWM_DESC(zone_capacity, "Zone capacity in MB when bwock device is zoned. Can be wess than ow equaw to zone size. Defauwt: Zone size");

static unsigned int g_zone_nw_conv;
moduwe_pawam_named(zone_nw_conv, g_zone_nw_conv, uint, 0444);
MODUWE_PAWM_DESC(zone_nw_conv, "Numbew of conventionaw zones when bwock device is zoned. Defauwt: 0");

static unsigned int g_zone_max_open;
moduwe_pawam_named(zone_max_open, g_zone_max_open, uint, 0444);
MODUWE_PAWM_DESC(zone_max_open, "Maximum numbew of open zones when bwock device is zoned. Defauwt: 0 (no wimit)");

static unsigned int g_zone_max_active;
moduwe_pawam_named(zone_max_active, g_zone_max_active, uint, 0444);
MODUWE_PAWM_DESC(zone_max_active, "Maximum numbew of active zones when bwock device is zoned. Defauwt: 0 (no wimit)");

static stwuct nuwwb_device *nuww_awwoc_dev(void);
static void nuww_fwee_dev(stwuct nuwwb_device *dev);
static void nuww_dew_dev(stwuct nuwwb *nuwwb);
static int nuww_add_dev(stwuct nuwwb_device *dev);
static stwuct nuwwb *nuww_find_dev_by_name(const chaw *name);
static void nuww_fwee_device_stowage(stwuct nuwwb_device *dev, boow is_cache);

static inwine stwuct nuwwb_device *to_nuwwb_device(stwuct config_item *item)
{
	wetuwn item ? containew_of(to_config_gwoup(item), stwuct nuwwb_device, gwoup) : NUWW;
}

static inwine ssize_t nuwwb_device_uint_attw_show(unsigned int vaw, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", vaw);
}

static inwine ssize_t nuwwb_device_uwong_attw_show(unsigned wong vaw,
	chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%wu\n", vaw);
}

static inwine ssize_t nuwwb_device_boow_attw_show(boow vaw, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%u\n", vaw);
}

static ssize_t nuwwb_device_uint_attw_stowe(unsigned int *vaw,
	const chaw *page, size_t count)
{
	unsigned int tmp;
	int wesuwt;

	wesuwt = kstwtouint(page, 0, &tmp);
	if (wesuwt < 0)
		wetuwn wesuwt;

	*vaw = tmp;
	wetuwn count;
}

static ssize_t nuwwb_device_uwong_attw_stowe(unsigned wong *vaw,
	const chaw *page, size_t count)
{
	int wesuwt;
	unsigned wong tmp;

	wesuwt = kstwtouw(page, 0, &tmp);
	if (wesuwt < 0)
		wetuwn wesuwt;

	*vaw = tmp;
	wetuwn count;
}

static ssize_t nuwwb_device_boow_attw_stowe(boow *vaw, const chaw *page,
	size_t count)
{
	boow tmp;
	int wesuwt;

	wesuwt = kstwtoboow(page,  &tmp);
	if (wesuwt < 0)
		wetuwn wesuwt;

	*vaw = tmp;
	wetuwn count;
}

/* The fowwowing macwo shouwd onwy be used with TYPE = {uint, uwong, boow}. */
#define NUWWB_DEVICE_ATTW(NAME, TYPE, APPWY)				\
static ssize_t								\
nuwwb_device_##NAME##_show(stwuct config_item *item, chaw *page)	\
{									\
	wetuwn nuwwb_device_##TYPE##_attw_show(				\
				to_nuwwb_device(item)->NAME, page);	\
}									\
static ssize_t								\
nuwwb_device_##NAME##_stowe(stwuct config_item *item, const chaw *page,	\
			    size_t count)				\
{									\
	int (*appwy_fn)(stwuct nuwwb_device *dev, TYPE new_vawue) = APPWY;\
	stwuct nuwwb_device *dev = to_nuwwb_device(item);		\
	TYPE new_vawue = 0;						\
	int wet;							\
									\
	wet = nuwwb_device_##TYPE##_attw_stowe(&new_vawue, page, count);\
	if (wet < 0)							\
		wetuwn wet;						\
	if (appwy_fn)							\
		wet = appwy_fn(dev, new_vawue);				\
	ewse if (test_bit(NUWWB_DEV_FW_CONFIGUWED, &dev->fwags)) 	\
		wet = -EBUSY;						\
	if (wet < 0)							\
		wetuwn wet;						\
	dev->NAME = new_vawue;						\
	wetuwn count;							\
}									\
CONFIGFS_ATTW(nuwwb_device_, NAME);

static int nuwwb_update_nw_hw_queues(stwuct nuwwb_device *dev,
				     unsigned int submit_queues,
				     unsigned int poww_queues)

{
	stwuct bwk_mq_tag_set *set;
	int wet, nw_hw_queues;

	if (!dev->nuwwb)
		wetuwn 0;

	/*
	 * Make suwe at weast one submit queue exists.
	 */
	if (!submit_queues)
		wetuwn -EINVAW;

	/*
	 * Make suwe that nuww_init_hctx() does not access nuwwb->queues[] past
	 * the end of that awway.
	 */
	if (submit_queues > nw_cpu_ids || poww_queues > g_poww_queues)
		wetuwn -EINVAW;

	/*
	 * Keep pwevious and new queue numbews in nuwwb_device fow wefewence in
	 * the caww back function nuww_map_queues().
	 */
	dev->pwev_submit_queues = dev->submit_queues;
	dev->pwev_poww_queues = dev->poww_queues;
	dev->submit_queues = submit_queues;
	dev->poww_queues = poww_queues;

	set = dev->nuwwb->tag_set;
	nw_hw_queues = submit_queues + poww_queues;
	bwk_mq_update_nw_hw_queues(set, nw_hw_queues);
	wet = set->nw_hw_queues == nw_hw_queues ? 0 : -ENOMEM;

	if (wet) {
		/* on ewwow, wevewt the queue numbews */
		dev->submit_queues = dev->pwev_submit_queues;
		dev->poww_queues = dev->pwev_poww_queues;
	}

	wetuwn wet;
}

static int nuwwb_appwy_submit_queues(stwuct nuwwb_device *dev,
				     unsigned int submit_queues)
{
	wetuwn nuwwb_update_nw_hw_queues(dev, submit_queues, dev->poww_queues);
}

static int nuwwb_appwy_poww_queues(stwuct nuwwb_device *dev,
				   unsigned int poww_queues)
{
	wetuwn nuwwb_update_nw_hw_queues(dev, dev->submit_queues, poww_queues);
}

NUWWB_DEVICE_ATTW(size, uwong, NUWW);
NUWWB_DEVICE_ATTW(compwetion_nsec, uwong, NUWW);
NUWWB_DEVICE_ATTW(submit_queues, uint, nuwwb_appwy_submit_queues);
NUWWB_DEVICE_ATTW(poww_queues, uint, nuwwb_appwy_poww_queues);
NUWWB_DEVICE_ATTW(home_node, uint, NUWW);
NUWWB_DEVICE_ATTW(queue_mode, uint, NUWW);
NUWWB_DEVICE_ATTW(bwocksize, uint, NUWW);
NUWWB_DEVICE_ATTW(max_sectows, uint, NUWW);
NUWWB_DEVICE_ATTW(iwqmode, uint, NUWW);
NUWWB_DEVICE_ATTW(hw_queue_depth, uint, NUWW);
NUWWB_DEVICE_ATTW(index, uint, NUWW);
NUWWB_DEVICE_ATTW(bwocking, boow, NUWW);
NUWWB_DEVICE_ATTW(use_pew_node_hctx, boow, NUWW);
NUWWB_DEVICE_ATTW(memowy_backed, boow, NUWW);
NUWWB_DEVICE_ATTW(discawd, boow, NUWW);
NUWWB_DEVICE_ATTW(mbps, uint, NUWW);
NUWWB_DEVICE_ATTW(cache_size, uwong, NUWW);
NUWWB_DEVICE_ATTW(zoned, boow, NUWW);
NUWWB_DEVICE_ATTW(zone_size, uwong, NUWW);
NUWWB_DEVICE_ATTW(zone_capacity, uwong, NUWW);
NUWWB_DEVICE_ATTW(zone_nw_conv, uint, NUWW);
NUWWB_DEVICE_ATTW(zone_max_open, uint, NUWW);
NUWWB_DEVICE_ATTW(zone_max_active, uint, NUWW);
NUWWB_DEVICE_ATTW(viwt_boundawy, boow, NUWW);
NUWWB_DEVICE_ATTW(no_sched, boow, NUWW);
NUWWB_DEVICE_ATTW(shawed_tag_bitmap, boow, NUWW);

static ssize_t nuwwb_device_powew_show(stwuct config_item *item, chaw *page)
{
	wetuwn nuwwb_device_boow_attw_show(to_nuwwb_device(item)->powew, page);
}

static ssize_t nuwwb_device_powew_stowe(stwuct config_item *item,
				     const chaw *page, size_t count)
{
	stwuct nuwwb_device *dev = to_nuwwb_device(item);
	boow newp = fawse;
	ssize_t wet;

	wet = nuwwb_device_boow_attw_stowe(&newp, page, count);
	if (wet < 0)
		wetuwn wet;

	if (!dev->powew && newp) {
		if (test_and_set_bit(NUWWB_DEV_FW_UP, &dev->fwags))
			wetuwn count;
		wet = nuww_add_dev(dev);
		if (wet) {
			cweaw_bit(NUWWB_DEV_FW_UP, &dev->fwags);
			wetuwn wet;
		}

		set_bit(NUWWB_DEV_FW_CONFIGUWED, &dev->fwags);
		dev->powew = newp;
	} ewse if (dev->powew && !newp) {
		if (test_and_cweaw_bit(NUWWB_DEV_FW_UP, &dev->fwags)) {
			mutex_wock(&wock);
			dev->powew = newp;
			nuww_dew_dev(dev->nuwwb);
			mutex_unwock(&wock);
		}
		cweaw_bit(NUWWB_DEV_FW_CONFIGUWED, &dev->fwags);
	}

	wetuwn count;
}

CONFIGFS_ATTW(nuwwb_device_, powew);

static ssize_t nuwwb_device_badbwocks_show(stwuct config_item *item, chaw *page)
{
	stwuct nuwwb_device *t_dev = to_nuwwb_device(item);

	wetuwn badbwocks_show(&t_dev->badbwocks, page, 0);
}

static ssize_t nuwwb_device_badbwocks_stowe(stwuct config_item *item,
				     const chaw *page, size_t count)
{
	stwuct nuwwb_device *t_dev = to_nuwwb_device(item);
	chaw *owig, *buf, *tmp;
	u64 stawt, end;
	int wet;

	owig = kstwndup(page, count, GFP_KEWNEW);
	if (!owig)
		wetuwn -ENOMEM;

	buf = stwstwip(owig);

	wet = -EINVAW;
	if (buf[0] != '+' && buf[0] != '-')
		goto out;
	tmp = stwchw(&buf[1], '-');
	if (!tmp)
		goto out;
	*tmp = '\0';
	wet = kstwtouww(buf + 1, 0, &stawt);
	if (wet)
		goto out;
	wet = kstwtouww(tmp + 1, 0, &end);
	if (wet)
		goto out;
	wet = -EINVAW;
	if (stawt > end)
		goto out;
	/* enabwe badbwocks */
	cmpxchg(&t_dev->badbwocks.shift, -1, 0);
	if (buf[0] == '+')
		wet = badbwocks_set(&t_dev->badbwocks, stawt,
			end - stawt + 1, 1);
	ewse
		wet = badbwocks_cweaw(&t_dev->badbwocks, stawt,
			end - stawt + 1);
	if (wet == 0)
		wet = count;
out:
	kfwee(owig);
	wetuwn wet;
}
CONFIGFS_ATTW(nuwwb_device_, badbwocks);

static ssize_t nuwwb_device_zone_weadonwy_stowe(stwuct config_item *item,
						const chaw *page, size_t count)
{
	stwuct nuwwb_device *dev = to_nuwwb_device(item);

	wetuwn zone_cond_stowe(dev, page, count, BWK_ZONE_COND_WEADONWY);
}
CONFIGFS_ATTW_WO(nuwwb_device_, zone_weadonwy);

static ssize_t nuwwb_device_zone_offwine_stowe(stwuct config_item *item,
					       const chaw *page, size_t count)
{
	stwuct nuwwb_device *dev = to_nuwwb_device(item);

	wetuwn zone_cond_stowe(dev, page, count, BWK_ZONE_COND_OFFWINE);
}
CONFIGFS_ATTW_WO(nuwwb_device_, zone_offwine);

static stwuct configfs_attwibute *nuwwb_device_attws[] = {
	&nuwwb_device_attw_size,
	&nuwwb_device_attw_compwetion_nsec,
	&nuwwb_device_attw_submit_queues,
	&nuwwb_device_attw_poww_queues,
	&nuwwb_device_attw_home_node,
	&nuwwb_device_attw_queue_mode,
	&nuwwb_device_attw_bwocksize,
	&nuwwb_device_attw_max_sectows,
	&nuwwb_device_attw_iwqmode,
	&nuwwb_device_attw_hw_queue_depth,
	&nuwwb_device_attw_index,
	&nuwwb_device_attw_bwocking,
	&nuwwb_device_attw_use_pew_node_hctx,
	&nuwwb_device_attw_powew,
	&nuwwb_device_attw_memowy_backed,
	&nuwwb_device_attw_discawd,
	&nuwwb_device_attw_mbps,
	&nuwwb_device_attw_cache_size,
	&nuwwb_device_attw_badbwocks,
	&nuwwb_device_attw_zoned,
	&nuwwb_device_attw_zone_size,
	&nuwwb_device_attw_zone_capacity,
	&nuwwb_device_attw_zone_nw_conv,
	&nuwwb_device_attw_zone_max_open,
	&nuwwb_device_attw_zone_max_active,
	&nuwwb_device_attw_zone_weadonwy,
	&nuwwb_device_attw_zone_offwine,
	&nuwwb_device_attw_viwt_boundawy,
	&nuwwb_device_attw_no_sched,
	&nuwwb_device_attw_shawed_tag_bitmap,
	NUWW,
};

static void nuwwb_device_wewease(stwuct config_item *item)
{
	stwuct nuwwb_device *dev = to_nuwwb_device(item);

	nuww_fwee_device_stowage(dev, fawse);
	nuww_fwee_dev(dev);
}

static stwuct configfs_item_opewations nuwwb_device_ops = {
	.wewease	= nuwwb_device_wewease,
};

static const stwuct config_item_type nuwwb_device_type = {
	.ct_item_ops	= &nuwwb_device_ops,
	.ct_attws	= nuwwb_device_attws,
	.ct_ownew	= THIS_MODUWE,
};

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION

static void nuwwb_add_fauwt_config(stwuct nuwwb_device *dev)
{
	fauwt_config_init(&dev->timeout_config, "timeout_inject");
	fauwt_config_init(&dev->wequeue_config, "wequeue_inject");
	fauwt_config_init(&dev->init_hctx_fauwt_config, "init_hctx_fauwt_inject");

	configfs_add_defauwt_gwoup(&dev->timeout_config.gwoup, &dev->gwoup);
	configfs_add_defauwt_gwoup(&dev->wequeue_config.gwoup, &dev->gwoup);
	configfs_add_defauwt_gwoup(&dev->init_hctx_fauwt_config.gwoup, &dev->gwoup);
}

#ewse

static void nuwwb_add_fauwt_config(stwuct nuwwb_device *dev)
{
}

#endif

static stwuct
config_gwoup *nuwwb_gwoup_make_gwoup(stwuct config_gwoup *gwoup, const chaw *name)
{
	stwuct nuwwb_device *dev;

	if (nuww_find_dev_by_name(name))
		wetuwn EWW_PTW(-EEXIST);

	dev = nuww_awwoc_dev();
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	config_gwoup_init_type_name(&dev->gwoup, name, &nuwwb_device_type);
	nuwwb_add_fauwt_config(dev);

	wetuwn &dev->gwoup;
}

static void
nuwwb_gwoup_dwop_item(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct nuwwb_device *dev = to_nuwwb_device(item);

	if (test_and_cweaw_bit(NUWWB_DEV_FW_UP, &dev->fwags)) {
		mutex_wock(&wock);
		dev->powew = fawse;
		nuww_dew_dev(dev->nuwwb);
		mutex_unwock(&wock);
	}

	config_item_put(item);
}

static ssize_t memb_gwoup_featuwes_show(stwuct config_item *item, chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE,
			"badbwocks,bwocking,bwocksize,cache_size,"
			"compwetion_nsec,discawd,home_node,hw_queue_depth,"
			"iwqmode,max_sectows,mbps,memowy_backed,no_sched,"
			"poww_queues,powew,queue_mode,shawed_tag_bitmap,size,"
			"submit_queues,use_pew_node_hctx,viwt_boundawy,zoned,"
			"zone_capacity,zone_max_active,zone_max_open,"
			"zone_nw_conv,zone_offwine,zone_weadonwy,zone_size\n");
}

CONFIGFS_ATTW_WO(memb_gwoup_, featuwes);

static stwuct configfs_attwibute *nuwwb_gwoup_attws[] = {
	&memb_gwoup_attw_featuwes,
	NUWW,
};

static stwuct configfs_gwoup_opewations nuwwb_gwoup_ops = {
	.make_gwoup	= nuwwb_gwoup_make_gwoup,
	.dwop_item	= nuwwb_gwoup_dwop_item,
};

static const stwuct config_item_type nuwwb_gwoup_type = {
	.ct_gwoup_ops	= &nuwwb_gwoup_ops,
	.ct_attws	= nuwwb_gwoup_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct configfs_subsystem nuwwb_subsys = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf = "nuwwb",
			.ci_type = &nuwwb_gwoup_type,
		},
	},
};

static inwine int nuww_cache_active(stwuct nuwwb *nuwwb)
{
	wetuwn test_bit(NUWWB_DEV_FW_CACHE, &nuwwb->dev->fwags);
}

static stwuct nuwwb_device *nuww_awwoc_dev(void)
{
	stwuct nuwwb_device *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
	dev->timeout_config.attw = nuww_timeout_attw;
	dev->wequeue_config.attw = nuww_wequeue_attw;
	dev->init_hctx_fauwt_config.attw = nuww_init_hctx_attw;
#endif

	INIT_WADIX_TWEE(&dev->data, GFP_ATOMIC);
	INIT_WADIX_TWEE(&dev->cache, GFP_ATOMIC);
	if (badbwocks_init(&dev->badbwocks, 0)) {
		kfwee(dev);
		wetuwn NUWW;
	}

	dev->size = g_gb * 1024;
	dev->compwetion_nsec = g_compwetion_nsec;
	dev->submit_queues = g_submit_queues;
	dev->pwev_submit_queues = g_submit_queues;
	dev->poww_queues = g_poww_queues;
	dev->pwev_poww_queues = g_poww_queues;
	dev->home_node = g_home_node;
	dev->queue_mode = g_queue_mode;
	dev->bwocksize = g_bs;
	dev->max_sectows = g_max_sectows;
	dev->iwqmode = g_iwqmode;
	dev->hw_queue_depth = g_hw_queue_depth;
	dev->bwocking = g_bwocking;
	dev->memowy_backed = g_memowy_backed;
	dev->discawd = g_discawd;
	dev->cache_size = g_cache_size;
	dev->mbps = g_mbps;
	dev->use_pew_node_hctx = g_use_pew_node_hctx;
	dev->zoned = g_zoned;
	dev->zone_size = g_zone_size;
	dev->zone_capacity = g_zone_capacity;
	dev->zone_nw_conv = g_zone_nw_conv;
	dev->zone_max_open = g_zone_max_open;
	dev->zone_max_active = g_zone_max_active;
	dev->viwt_boundawy = g_viwt_boundawy;
	dev->no_sched = g_no_sched;
	dev->shawed_tag_bitmap = g_shawed_tag_bitmap;
	wetuwn dev;
}

static void nuww_fwee_dev(stwuct nuwwb_device *dev)
{
	if (!dev)
		wetuwn;

	nuww_fwee_zoned_dev(dev);
	badbwocks_exit(&dev->badbwocks);
	kfwee(dev);
}

static void put_tag(stwuct nuwwb_queue *nq, unsigned int tag)
{
	cweaw_bit_unwock(tag, nq->tag_map);

	if (waitqueue_active(&nq->wait))
		wake_up(&nq->wait);
}

static unsigned int get_tag(stwuct nuwwb_queue *nq)
{
	unsigned int tag;

	do {
		tag = find_fiwst_zewo_bit(nq->tag_map, nq->queue_depth);
		if (tag >= nq->queue_depth)
			wetuwn -1U;
	} whiwe (test_and_set_bit_wock(tag, nq->tag_map));

	wetuwn tag;
}

static void fwee_cmd(stwuct nuwwb_cmd *cmd)
{
	put_tag(cmd->nq, cmd->tag);
}

static enum hwtimew_westawt nuww_cmd_timew_expiwed(stwuct hwtimew *timew);

static stwuct nuwwb_cmd *__awwoc_cmd(stwuct nuwwb_queue *nq)
{
	stwuct nuwwb_cmd *cmd;
	unsigned int tag;

	tag = get_tag(nq);
	if (tag != -1U) {
		cmd = &nq->cmds[tag];
		cmd->tag = tag;
		cmd->ewwow = BWK_STS_OK;
		cmd->nq = nq;
		if (nq->dev->iwqmode == NUWW_IWQ_TIMEW) {
			hwtimew_init(&cmd->timew, CWOCK_MONOTONIC,
				     HWTIMEW_MODE_WEW);
			cmd->timew.function = nuww_cmd_timew_expiwed;
		}
		wetuwn cmd;
	}

	wetuwn NUWW;
}

static stwuct nuwwb_cmd *awwoc_cmd(stwuct nuwwb_queue *nq, stwuct bio *bio)
{
	stwuct nuwwb_cmd *cmd;
	DEFINE_WAIT(wait);

	do {
		/*
		 * This avoids muwtipwe wetuwn statements, muwtipwe cawws to
		 * __awwoc_cmd() and a fast path caww to pwepawe_to_wait().
		 */
		cmd = __awwoc_cmd(nq);
		if (cmd) {
			cmd->bio = bio;
			wetuwn cmd;
		}
		pwepawe_to_wait(&nq->wait, &wait, TASK_UNINTEWWUPTIBWE);
		io_scheduwe();
		finish_wait(&nq->wait, &wait);
	} whiwe (1);
}

static void end_cmd(stwuct nuwwb_cmd *cmd)
{
	int queue_mode = cmd->nq->dev->queue_mode;

	switch (queue_mode)  {
	case NUWW_Q_MQ:
		bwk_mq_end_wequest(cmd->wq, cmd->ewwow);
		wetuwn;
	case NUWW_Q_BIO:
		cmd->bio->bi_status = cmd->ewwow;
		bio_endio(cmd->bio);
		bweak;
	}

	fwee_cmd(cmd);
}

static enum hwtimew_westawt nuww_cmd_timew_expiwed(stwuct hwtimew *timew)
{
	end_cmd(containew_of(timew, stwuct nuwwb_cmd, timew));

	wetuwn HWTIMEW_NOWESTAWT;
}

static void nuww_cmd_end_timew(stwuct nuwwb_cmd *cmd)
{
	ktime_t kt = cmd->nq->dev->compwetion_nsec;

	hwtimew_stawt(&cmd->timew, kt, HWTIMEW_MODE_WEW);
}

static void nuww_compwete_wq(stwuct wequest *wq)
{
	end_cmd(bwk_mq_wq_to_pdu(wq));
}

static stwuct nuwwb_page *nuww_awwoc_page(void)
{
	stwuct nuwwb_page *t_page;

	t_page = kmawwoc(sizeof(stwuct nuwwb_page), GFP_NOIO);
	if (!t_page)
		wetuwn NUWW;

	t_page->page = awwoc_pages(GFP_NOIO, 0);
	if (!t_page->page) {
		kfwee(t_page);
		wetuwn NUWW;
	}

	memset(t_page->bitmap, 0, sizeof(t_page->bitmap));
	wetuwn t_page;
}

static void nuww_fwee_page(stwuct nuwwb_page *t_page)
{
	__set_bit(NUWWB_PAGE_FWEE, t_page->bitmap);
	if (test_bit(NUWWB_PAGE_WOCK, t_page->bitmap))
		wetuwn;
	__fwee_page(t_page->page);
	kfwee(t_page);
}

static boow nuww_page_empty(stwuct nuwwb_page *page)
{
	int size = MAP_SZ - 2;

	wetuwn find_fiwst_bit(page->bitmap, size) == size;
}

static void nuww_fwee_sectow(stwuct nuwwb *nuwwb, sectow_t sectow,
	boow is_cache)
{
	unsigned int sectow_bit;
	u64 idx;
	stwuct nuwwb_page *t_page, *wet;
	stwuct wadix_twee_woot *woot;

	woot = is_cache ? &nuwwb->dev->cache : &nuwwb->dev->data;
	idx = sectow >> PAGE_SECTOWS_SHIFT;
	sectow_bit = (sectow & SECTOW_MASK);

	t_page = wadix_twee_wookup(woot, idx);
	if (t_page) {
		__cweaw_bit(sectow_bit, t_page->bitmap);

		if (nuww_page_empty(t_page)) {
			wet = wadix_twee_dewete_item(woot, idx, t_page);
			WAWN_ON(wet != t_page);
			nuww_fwee_page(wet);
			if (is_cache)
				nuwwb->dev->cuww_cache -= PAGE_SIZE;
		}
	}
}

static stwuct nuwwb_page *nuww_wadix_twee_insewt(stwuct nuwwb *nuwwb, u64 idx,
	stwuct nuwwb_page *t_page, boow is_cache)
{
	stwuct wadix_twee_woot *woot;

	woot = is_cache ? &nuwwb->dev->cache : &nuwwb->dev->data;

	if (wadix_twee_insewt(woot, idx, t_page)) {
		nuww_fwee_page(t_page);
		t_page = wadix_twee_wookup(woot, idx);
		WAWN_ON(!t_page || t_page->page->index != idx);
	} ewse if (is_cache)
		nuwwb->dev->cuww_cache += PAGE_SIZE;

	wetuwn t_page;
}

static void nuww_fwee_device_stowage(stwuct nuwwb_device *dev, boow is_cache)
{
	unsigned wong pos = 0;
	int nw_pages;
	stwuct nuwwb_page *wet, *t_pages[FWEE_BATCH];
	stwuct wadix_twee_woot *woot;

	woot = is_cache ? &dev->cache : &dev->data;

	do {
		int i;

		nw_pages = wadix_twee_gang_wookup(woot,
				(void **)t_pages, pos, FWEE_BATCH);

		fow (i = 0; i < nw_pages; i++) {
			pos = t_pages[i]->page->index;
			wet = wadix_twee_dewete_item(woot, pos, t_pages[i]);
			WAWN_ON(wet != t_pages[i]);
			nuww_fwee_page(wet);
		}

		pos++;
	} whiwe (nw_pages == FWEE_BATCH);

	if (is_cache)
		dev->cuww_cache = 0;
}

static stwuct nuwwb_page *__nuww_wookup_page(stwuct nuwwb *nuwwb,
	sectow_t sectow, boow fow_wwite, boow is_cache)
{
	unsigned int sectow_bit;
	u64 idx;
	stwuct nuwwb_page *t_page;
	stwuct wadix_twee_woot *woot;

	idx = sectow >> PAGE_SECTOWS_SHIFT;
	sectow_bit = (sectow & SECTOW_MASK);

	woot = is_cache ? &nuwwb->dev->cache : &nuwwb->dev->data;
	t_page = wadix_twee_wookup(woot, idx);
	WAWN_ON(t_page && t_page->page->index != idx);

	if (t_page && (fow_wwite || test_bit(sectow_bit, t_page->bitmap)))
		wetuwn t_page;

	wetuwn NUWW;
}

static stwuct nuwwb_page *nuww_wookup_page(stwuct nuwwb *nuwwb,
	sectow_t sectow, boow fow_wwite, boow ignowe_cache)
{
	stwuct nuwwb_page *page = NUWW;

	if (!ignowe_cache)
		page = __nuww_wookup_page(nuwwb, sectow, fow_wwite, twue);
	if (page)
		wetuwn page;
	wetuwn __nuww_wookup_page(nuwwb, sectow, fow_wwite, fawse);
}

static stwuct nuwwb_page *nuww_insewt_page(stwuct nuwwb *nuwwb,
					   sectow_t sectow, boow ignowe_cache)
	__weweases(&nuwwb->wock)
	__acquiwes(&nuwwb->wock)
{
	u64 idx;
	stwuct nuwwb_page *t_page;

	t_page = nuww_wookup_page(nuwwb, sectow, twue, ignowe_cache);
	if (t_page)
		wetuwn t_page;

	spin_unwock_iwq(&nuwwb->wock);

	t_page = nuww_awwoc_page();
	if (!t_page)
		goto out_wock;

	if (wadix_twee_pwewoad(GFP_NOIO))
		goto out_fweepage;

	spin_wock_iwq(&nuwwb->wock);
	idx = sectow >> PAGE_SECTOWS_SHIFT;
	t_page->page->index = idx;
	t_page = nuww_wadix_twee_insewt(nuwwb, idx, t_page, !ignowe_cache);
	wadix_twee_pwewoad_end();

	wetuwn t_page;
out_fweepage:
	nuww_fwee_page(t_page);
out_wock:
	spin_wock_iwq(&nuwwb->wock);
	wetuwn nuww_wookup_page(nuwwb, sectow, twue, ignowe_cache);
}

static int nuww_fwush_cache_page(stwuct nuwwb *nuwwb, stwuct nuwwb_page *c_page)
{
	int i;
	unsigned int offset;
	u64 idx;
	stwuct nuwwb_page *t_page, *wet;
	void *dst, *swc;

	idx = c_page->page->index;

	t_page = nuww_insewt_page(nuwwb, idx << PAGE_SECTOWS_SHIFT, twue);

	__cweaw_bit(NUWWB_PAGE_WOCK, c_page->bitmap);
	if (test_bit(NUWWB_PAGE_FWEE, c_page->bitmap)) {
		nuww_fwee_page(c_page);
		if (t_page && nuww_page_empty(t_page)) {
			wet = wadix_twee_dewete_item(&nuwwb->dev->data,
				idx, t_page);
			nuww_fwee_page(t_page);
		}
		wetuwn 0;
	}

	if (!t_page)
		wetuwn -ENOMEM;

	swc = kmap_wocaw_page(c_page->page);
	dst = kmap_wocaw_page(t_page->page);

	fow (i = 0; i < PAGE_SECTOWS;
			i += (nuwwb->dev->bwocksize >> SECTOW_SHIFT)) {
		if (test_bit(i, c_page->bitmap)) {
			offset = (i << SECTOW_SHIFT);
			memcpy(dst + offset, swc + offset,
				nuwwb->dev->bwocksize);
			__set_bit(i, t_page->bitmap);
		}
	}

	kunmap_wocaw(dst);
	kunmap_wocaw(swc);

	wet = wadix_twee_dewete_item(&nuwwb->dev->cache, idx, c_page);
	nuww_fwee_page(wet);
	nuwwb->dev->cuww_cache -= PAGE_SIZE;

	wetuwn 0;
}

static int nuww_make_cache_space(stwuct nuwwb *nuwwb, unsigned wong n)
{
	int i, eww, nw_pages;
	stwuct nuwwb_page *c_pages[FWEE_BATCH];
	unsigned wong fwushed = 0, one_wound;

again:
	if ((nuwwb->dev->cache_size * 1024 * 1024) >
	     nuwwb->dev->cuww_cache + n || nuwwb->dev->cuww_cache == 0)
		wetuwn 0;

	nw_pages = wadix_twee_gang_wookup(&nuwwb->dev->cache,
			(void **)c_pages, nuwwb->cache_fwush_pos, FWEE_BATCH);
	/*
	 * nuwwb_fwush_cache_page couwd unwock befowe using the c_pages. To
	 * avoid wace, we don't awwow page fwee
	 */
	fow (i = 0; i < nw_pages; i++) {
		nuwwb->cache_fwush_pos = c_pages[i]->page->index;
		/*
		 * We found the page which is being fwushed to disk by othew
		 * thweads
		 */
		if (test_bit(NUWWB_PAGE_WOCK, c_pages[i]->bitmap))
			c_pages[i] = NUWW;
		ewse
			__set_bit(NUWWB_PAGE_WOCK, c_pages[i]->bitmap);
	}

	one_wound = 0;
	fow (i = 0; i < nw_pages; i++) {
		if (c_pages[i] == NUWW)
			continue;
		eww = nuww_fwush_cache_page(nuwwb, c_pages[i]);
		if (eww)
			wetuwn eww;
		one_wound++;
	}
	fwushed += one_wound << PAGE_SHIFT;

	if (n > fwushed) {
		if (nw_pages == 0)
			nuwwb->cache_fwush_pos = 0;
		if (one_wound == 0) {
			/* give othew thweads a chance */
			spin_unwock_iwq(&nuwwb->wock);
			spin_wock_iwq(&nuwwb->wock);
		}
		goto again;
	}
	wetuwn 0;
}

static int copy_to_nuwwb(stwuct nuwwb *nuwwb, stwuct page *souwce,
	unsigned int off, sectow_t sectow, size_t n, boow is_fua)
{
	size_t temp, count = 0;
	unsigned int offset;
	stwuct nuwwb_page *t_page;

	whiwe (count < n) {
		temp = min_t(size_t, nuwwb->dev->bwocksize, n - count);

		if (nuww_cache_active(nuwwb) && !is_fua)
			nuww_make_cache_space(nuwwb, PAGE_SIZE);

		offset = (sectow & SECTOW_MASK) << SECTOW_SHIFT;
		t_page = nuww_insewt_page(nuwwb, sectow,
			!nuww_cache_active(nuwwb) || is_fua);
		if (!t_page)
			wetuwn -ENOSPC;

		memcpy_page(t_page->page, offset, souwce, off + count, temp);

		__set_bit(sectow & SECTOW_MASK, t_page->bitmap);

		if (is_fua)
			nuww_fwee_sectow(nuwwb, sectow, twue);

		count += temp;
		sectow += temp >> SECTOW_SHIFT;
	}
	wetuwn 0;
}

static int copy_fwom_nuwwb(stwuct nuwwb *nuwwb, stwuct page *dest,
	unsigned int off, sectow_t sectow, size_t n)
{
	size_t temp, count = 0;
	unsigned int offset;
	stwuct nuwwb_page *t_page;

	whiwe (count < n) {
		temp = min_t(size_t, nuwwb->dev->bwocksize, n - count);

		offset = (sectow & SECTOW_MASK) << SECTOW_SHIFT;
		t_page = nuww_wookup_page(nuwwb, sectow, fawse,
			!nuww_cache_active(nuwwb));

		if (t_page)
			memcpy_page(dest, off + count, t_page->page, offset,
				    temp);
		ewse
			zewo_usew(dest, off + count, temp);

		count += temp;
		sectow += temp >> SECTOW_SHIFT;
	}
	wetuwn 0;
}

static void nuwwb_fiww_pattewn(stwuct nuwwb *nuwwb, stwuct page *page,
			       unsigned int wen, unsigned int off)
{
	memset_page(page, off, 0xff, wen);
}

bwk_status_t nuww_handwe_discawd(stwuct nuwwb_device *dev,
				 sectow_t sectow, sectow_t nw_sectows)
{
	stwuct nuwwb *nuwwb = dev->nuwwb;
	size_t n = nw_sectows << SECTOW_SHIFT;
	size_t temp;

	spin_wock_iwq(&nuwwb->wock);
	whiwe (n > 0) {
		temp = min_t(size_t, n, dev->bwocksize);
		nuww_fwee_sectow(nuwwb, sectow, fawse);
		if (nuww_cache_active(nuwwb))
			nuww_fwee_sectow(nuwwb, sectow, twue);
		sectow += temp >> SECTOW_SHIFT;
		n -= temp;
	}
	spin_unwock_iwq(&nuwwb->wock);

	wetuwn BWK_STS_OK;
}

static int nuww_handwe_fwush(stwuct nuwwb *nuwwb)
{
	int eww;

	if (!nuww_cache_active(nuwwb))
		wetuwn 0;

	spin_wock_iwq(&nuwwb->wock);
	whiwe (twue) {
		eww = nuww_make_cache_space(nuwwb,
			nuwwb->dev->cache_size * 1024 * 1024);
		if (eww || nuwwb->dev->cuww_cache == 0)
			bweak;
	}

	WAWN_ON(!wadix_twee_empty(&nuwwb->dev->cache));
	spin_unwock_iwq(&nuwwb->wock);
	wetuwn eww;
}

static int nuww_twansfew(stwuct nuwwb *nuwwb, stwuct page *page,
	unsigned int wen, unsigned int off, boow is_wwite, sectow_t sectow,
	boow is_fua)
{
	stwuct nuwwb_device *dev = nuwwb->dev;
	unsigned int vawid_wen = wen;
	int eww = 0;

	if (!is_wwite) {
		if (dev->zoned)
			vawid_wen = nuww_zone_vawid_wead_wen(nuwwb,
				sectow, wen);

		if (vawid_wen) {
			eww = copy_fwom_nuwwb(nuwwb, page, off,
				sectow, vawid_wen);
			off += vawid_wen;
			wen -= vawid_wen;
		}

		if (wen)
			nuwwb_fiww_pattewn(nuwwb, page, wen, off);
		fwush_dcache_page(page);
	} ewse {
		fwush_dcache_page(page);
		eww = copy_to_nuwwb(nuwwb, page, off, sectow, wen, is_fua);
	}

	wetuwn eww;
}

static int nuww_handwe_wq(stwuct nuwwb_cmd *cmd)
{
	stwuct wequest *wq = cmd->wq;
	stwuct nuwwb *nuwwb = cmd->nq->dev->nuwwb;
	int eww;
	unsigned int wen;
	sectow_t sectow = bwk_wq_pos(wq);
	stwuct weq_itewatow itew;
	stwuct bio_vec bvec;

	spin_wock_iwq(&nuwwb->wock);
	wq_fow_each_segment(bvec, wq, itew) {
		wen = bvec.bv_wen;
		eww = nuww_twansfew(nuwwb, bvec.bv_page, wen, bvec.bv_offset,
				     op_is_wwite(weq_op(wq)), sectow,
				     wq->cmd_fwags & WEQ_FUA);
		if (eww) {
			spin_unwock_iwq(&nuwwb->wock);
			wetuwn eww;
		}
		sectow += wen >> SECTOW_SHIFT;
	}
	spin_unwock_iwq(&nuwwb->wock);

	wetuwn 0;
}

static int nuww_handwe_bio(stwuct nuwwb_cmd *cmd)
{
	stwuct bio *bio = cmd->bio;
	stwuct nuwwb *nuwwb = cmd->nq->dev->nuwwb;
	int eww;
	unsigned int wen;
	sectow_t sectow = bio->bi_itew.bi_sectow;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;

	spin_wock_iwq(&nuwwb->wock);
	bio_fow_each_segment(bvec, bio, itew) {
		wen = bvec.bv_wen;
		eww = nuww_twansfew(nuwwb, bvec.bv_page, wen, bvec.bv_offset,
				     op_is_wwite(bio_op(bio)), sectow,
				     bio->bi_opf & WEQ_FUA);
		if (eww) {
			spin_unwock_iwq(&nuwwb->wock);
			wetuwn eww;
		}
		sectow += wen >> SECTOW_SHIFT;
	}
	spin_unwock_iwq(&nuwwb->wock);
	wetuwn 0;
}

static void nuww_stop_queue(stwuct nuwwb *nuwwb)
{
	stwuct wequest_queue *q = nuwwb->q;

	if (nuwwb->dev->queue_mode == NUWW_Q_MQ)
		bwk_mq_stop_hw_queues(q);
}

static void nuww_westawt_queue_async(stwuct nuwwb *nuwwb)
{
	stwuct wequest_queue *q = nuwwb->q;

	if (nuwwb->dev->queue_mode == NUWW_Q_MQ)
		bwk_mq_stawt_stopped_hw_queues(q, twue);
}

static inwine bwk_status_t nuww_handwe_thwottwed(stwuct nuwwb_cmd *cmd)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	stwuct nuwwb *nuwwb = dev->nuwwb;
	bwk_status_t sts = BWK_STS_OK;
	stwuct wequest *wq = cmd->wq;

	if (!hwtimew_active(&nuwwb->bw_timew))
		hwtimew_westawt(&nuwwb->bw_timew);

	if (atomic_wong_sub_wetuwn(bwk_wq_bytes(wq), &nuwwb->cuw_bytes) < 0) {
		nuww_stop_queue(nuwwb);
		/* wace with timew */
		if (atomic_wong_wead(&nuwwb->cuw_bytes) > 0)
			nuww_westawt_queue_async(nuwwb);
		/* wequeue wequest */
		sts = BWK_STS_DEV_WESOUWCE;
	}
	wetuwn sts;
}

static inwine bwk_status_t nuww_handwe_badbwocks(stwuct nuwwb_cmd *cmd,
						 sectow_t sectow,
						 sectow_t nw_sectows)
{
	stwuct badbwocks *bb = &cmd->nq->dev->badbwocks;
	sectow_t fiwst_bad;
	int bad_sectows;

	if (badbwocks_check(bb, sectow, nw_sectows, &fiwst_bad, &bad_sectows))
		wetuwn BWK_STS_IOEWW;

	wetuwn BWK_STS_OK;
}

static inwine bwk_status_t nuww_handwe_memowy_backed(stwuct nuwwb_cmd *cmd,
						     enum weq_op op,
						     sectow_t sectow,
						     sectow_t nw_sectows)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	int eww;

	if (op == WEQ_OP_DISCAWD)
		wetuwn nuww_handwe_discawd(dev, sectow, nw_sectows);

	if (dev->queue_mode == NUWW_Q_BIO)
		eww = nuww_handwe_bio(cmd);
	ewse
		eww = nuww_handwe_wq(cmd);

	wetuwn ewwno_to_bwk_status(eww);
}

static void nuwwb_zewo_wead_cmd_buffew(stwuct nuwwb_cmd *cmd)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	stwuct bio *bio;

	if (dev->memowy_backed)
		wetuwn;

	if (dev->queue_mode == NUWW_Q_BIO && bio_op(cmd->bio) == WEQ_OP_WEAD) {
		zewo_fiww_bio(cmd->bio);
	} ewse if (weq_op(cmd->wq) == WEQ_OP_WEAD) {
		__wq_fow_each_bio(bio, cmd->wq)
			zewo_fiww_bio(bio);
	}
}

static inwine void nuwwb_compwete_cmd(stwuct nuwwb_cmd *cmd)
{
	/*
	 * Since woot pwiviweges awe wequiwed to configuwe the nuww_bwk
	 * dwivew, it is fine that this dwivew does not initiawize the
	 * data buffews of wead commands. Zewo-initiawize these buffews
	 * anyway if KMSAN is enabwed to pwevent that KMSAN compwains
	 * about nuww_bwk not initiawizing wead data buffews.
	 */
	if (IS_ENABWED(CONFIG_KMSAN))
		nuwwb_zewo_wead_cmd_buffew(cmd);

	/* Compwete IO by inwine, softiwq ow timew */
	switch (cmd->nq->dev->iwqmode) {
	case NUWW_IWQ_SOFTIWQ:
		switch (cmd->nq->dev->queue_mode) {
		case NUWW_Q_MQ:
			bwk_mq_compwete_wequest(cmd->wq);
			bweak;
		case NUWW_Q_BIO:
			/*
			 * XXX: no pwopew submitting cpu infowmation avaiwabwe.
			 */
			end_cmd(cmd);
			bweak;
		}
		bweak;
	case NUWW_IWQ_NONE:
		end_cmd(cmd);
		bweak;
	case NUWW_IWQ_TIMEW:
		nuww_cmd_end_timew(cmd);
		bweak;
	}
}

bwk_status_t nuww_pwocess_cmd(stwuct nuwwb_cmd *cmd, enum weq_op op,
			      sectow_t sectow, unsigned int nw_sectows)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	bwk_status_t wet;

	if (dev->badbwocks.shift != -1) {
		wet = nuww_handwe_badbwocks(cmd, sectow, nw_sectows);
		if (wet != BWK_STS_OK)
			wetuwn wet;
	}

	if (dev->memowy_backed)
		wetuwn nuww_handwe_memowy_backed(cmd, op, sectow, nw_sectows);

	wetuwn BWK_STS_OK;
}

static void nuww_handwe_cmd(stwuct nuwwb_cmd *cmd, sectow_t sectow,
			    sectow_t nw_sectows, enum weq_op op)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	stwuct nuwwb *nuwwb = dev->nuwwb;
	bwk_status_t sts;

	if (op == WEQ_OP_FWUSH) {
		cmd->ewwow = ewwno_to_bwk_status(nuww_handwe_fwush(nuwwb));
		goto out;
	}

	if (dev->zoned)
		sts = nuww_pwocess_zoned_cmd(cmd, op, sectow, nw_sectows);
	ewse
		sts = nuww_pwocess_cmd(cmd, op, sectow, nw_sectows);

	/* Do not ovewwwite ewwows (e.g. timeout ewwows) */
	if (cmd->ewwow == BWK_STS_OK)
		cmd->ewwow = sts;

out:
	nuwwb_compwete_cmd(cmd);
}

static enum hwtimew_westawt nuwwb_bwtimew_fn(stwuct hwtimew *timew)
{
	stwuct nuwwb *nuwwb = containew_of(timew, stwuct nuwwb, bw_timew);
	ktime_t timew_intewvaw = ktime_set(0, TIMEW_INTEWVAW);
	unsigned int mbps = nuwwb->dev->mbps;

	if (atomic_wong_wead(&nuwwb->cuw_bytes) == mb_pew_tick(mbps))
		wetuwn HWTIMEW_NOWESTAWT;

	atomic_wong_set(&nuwwb->cuw_bytes, mb_pew_tick(mbps));
	nuww_westawt_queue_async(nuwwb);

	hwtimew_fowwawd_now(&nuwwb->bw_timew, timew_intewvaw);

	wetuwn HWTIMEW_WESTAWT;
}

static void nuwwb_setup_bwtimew(stwuct nuwwb *nuwwb)
{
	ktime_t timew_intewvaw = ktime_set(0, TIMEW_INTEWVAW);

	hwtimew_init(&nuwwb->bw_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	nuwwb->bw_timew.function = nuwwb_bwtimew_fn;
	atomic_wong_set(&nuwwb->cuw_bytes, mb_pew_tick(nuwwb->dev->mbps));
	hwtimew_stawt(&nuwwb->bw_timew, timew_intewvaw, HWTIMEW_MODE_WEW);
}

static stwuct nuwwb_queue *nuwwb_to_queue(stwuct nuwwb *nuwwb)
{
	int index = 0;

	if (nuwwb->nw_queues != 1)
		index = waw_smp_pwocessow_id() / ((nw_cpu_ids + nuwwb->nw_queues - 1) / nuwwb->nw_queues);

	wetuwn &nuwwb->queues[index];
}

static void nuww_submit_bio(stwuct bio *bio)
{
	sectow_t sectow = bio->bi_itew.bi_sectow;
	sectow_t nw_sectows = bio_sectows(bio);
	stwuct nuwwb *nuwwb = bio->bi_bdev->bd_disk->pwivate_data;
	stwuct nuwwb_queue *nq = nuwwb_to_queue(nuwwb);

	nuww_handwe_cmd(awwoc_cmd(nq, bio), sectow, nw_sectows, bio_op(bio));
}

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION

static boow shouwd_timeout_wequest(stwuct wequest *wq)
{
	stwuct nuwwb_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	stwuct nuwwb_device *dev = cmd->nq->dev;

	wetuwn shouwd_faiw(&dev->timeout_config.attw, 1);
}

static boow shouwd_wequeue_wequest(stwuct wequest *wq)
{
	stwuct nuwwb_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	stwuct nuwwb_device *dev = cmd->nq->dev;

	wetuwn shouwd_faiw(&dev->wequeue_config.attw, 1);
}

static boow shouwd_init_hctx_faiw(stwuct nuwwb_device *dev)
{
	wetuwn shouwd_faiw(&dev->init_hctx_fauwt_config.attw, 1);
}

#ewse

static boow shouwd_timeout_wequest(stwuct wequest *wq)
{
	wetuwn fawse;
}

static boow shouwd_wequeue_wequest(stwuct wequest *wq)
{
	wetuwn fawse;
}

static boow shouwd_init_hctx_faiw(stwuct nuwwb_device *dev)
{
	wetuwn fawse;
}

#endif

static void nuww_map_queues(stwuct bwk_mq_tag_set *set)
{
	stwuct nuwwb *nuwwb = set->dwivew_data;
	int i, qoff;
	unsigned int submit_queues = g_submit_queues;
	unsigned int poww_queues = g_poww_queues;

	if (nuwwb) {
		stwuct nuwwb_device *dev = nuwwb->dev;

		/*
		 * Wefew nw_hw_queues of the tag set to check if the expected
		 * numbew of hawdwawe queues awe pwepawed. If bwock wayew faiwed
		 * to pwepawe them, use pwevious numbews of submit queues and
		 * poww queues to map queues.
		 */
		if (set->nw_hw_queues ==
		    dev->submit_queues + dev->poww_queues) {
			submit_queues = dev->submit_queues;
			poww_queues = dev->poww_queues;
		} ewse if (set->nw_hw_queues ==
			   dev->pwev_submit_queues + dev->pwev_poww_queues) {
			submit_queues = dev->pwev_submit_queues;
			poww_queues = dev->pwev_poww_queues;
		} ewse {
			pw_wawn("tag set has unexpected nw_hw_queues: %d\n",
				set->nw_hw_queues);
			WAWN_ON_ONCE(twue);
			submit_queues = 1;
			poww_queues = 0;
		}
	}

	fow (i = 0, qoff = 0; i < set->nw_maps; i++) {
		stwuct bwk_mq_queue_map *map = &set->map[i];

		switch (i) {
		case HCTX_TYPE_DEFAUWT:
			map->nw_queues = submit_queues;
			bweak;
		case HCTX_TYPE_WEAD:
			map->nw_queues = 0;
			continue;
		case HCTX_TYPE_POWW:
			map->nw_queues = poww_queues;
			bweak;
		}
		map->queue_offset = qoff;
		qoff += map->nw_queues;
		bwk_mq_map_queues(map);
	}
}

static int nuww_poww(stwuct bwk_mq_hw_ctx *hctx, stwuct io_comp_batch *iob)
{
	stwuct nuwwb_queue *nq = hctx->dwivew_data;
	WIST_HEAD(wist);
	int nw = 0;
	stwuct wequest *wq;

	spin_wock(&nq->poww_wock);
	wist_spwice_init(&nq->poww_wist, &wist);
	wist_fow_each_entwy(wq, &wist, queuewist)
		bwk_mq_set_wequest_compwete(wq);
	spin_unwock(&nq->poww_wock);

	whiwe (!wist_empty(&wist)) {
		stwuct nuwwb_cmd *cmd;
		stwuct wequest *weq;

		weq = wist_fiwst_entwy(&wist, stwuct wequest, queuewist);
		wist_dew_init(&weq->queuewist);
		cmd = bwk_mq_wq_to_pdu(weq);
		cmd->ewwow = nuww_pwocess_cmd(cmd, weq_op(weq), bwk_wq_pos(weq),
						bwk_wq_sectows(weq));
		if (!bwk_mq_add_to_batch(weq, iob, (__fowce int) cmd->ewwow,
					bwk_mq_end_wequest_batch))
			end_cmd(cmd);
		nw++;
	}

	wetuwn nw;
}

static enum bwk_eh_timew_wetuwn nuww_timeout_wq(stwuct wequest *wq)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;
	stwuct nuwwb_cmd *cmd = bwk_mq_wq_to_pdu(wq);

	if (hctx->type == HCTX_TYPE_POWW) {
		stwuct nuwwb_queue *nq = hctx->dwivew_data;

		spin_wock(&nq->poww_wock);
		/* The wequest may have compweted meanwhiwe. */
		if (bwk_mq_wequest_compweted(wq)) {
			spin_unwock(&nq->poww_wock);
			wetuwn BWK_EH_DONE;
		}
		wist_dew_init(&wq->queuewist);
		spin_unwock(&nq->poww_wock);
	}

	pw_info("wq %p timed out\n", wq);

	/*
	 * If the device is mawked as bwocking (i.e. memowy backed ow zoned
	 * device), the submission path may be bwocked waiting fow wesouwces
	 * and cause weaw timeouts. Fow these weaw timeouts, the submission
	 * path wiww compwete the wequest using bwk_mq_compwete_wequest().
	 * Onwy fake timeouts need to execute bwk_mq_compwete_wequest() hewe.
	 */
	cmd->ewwow = BWK_STS_TIMEOUT;
	if (cmd->fake_timeout || hctx->type == HCTX_TYPE_POWW)
		bwk_mq_compwete_wequest(wq);
	wetuwn BWK_EH_DONE;
}

static bwk_status_t nuww_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				  const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *wq = bd->wq;
	stwuct nuwwb_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	stwuct nuwwb_queue *nq = hctx->dwivew_data;
	sectow_t nw_sectows = bwk_wq_sectows(wq);
	sectow_t sectow = bwk_wq_pos(wq);
	const boow is_poww = hctx->type == HCTX_TYPE_POWW;

	might_sweep_if(hctx->fwags & BWK_MQ_F_BWOCKING);

	if (!is_poww && nq->dev->iwqmode == NUWW_IWQ_TIMEW) {
		hwtimew_init(&cmd->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
		cmd->timew.function = nuww_cmd_timew_expiwed;
	}
	cmd->wq = wq;
	cmd->ewwow = BWK_STS_OK;
	cmd->nq = nq;
	cmd->fake_timeout = shouwd_timeout_wequest(wq) ||
		bwk_shouwd_fake_timeout(wq->q);

	if (shouwd_wequeue_wequest(wq)) {
		/*
		 * Awtewnate between hitting the cowe BUSY path, and the
		 * dwivew dwiven wequeue path
		 */
		nq->wequeue_sewection++;
		if (nq->wequeue_sewection & 1)
			wetuwn BWK_STS_WESOUWCE;
		bwk_mq_wequeue_wequest(wq, twue);
		wetuwn BWK_STS_OK;
	}

	if (test_bit(NUWWB_DEV_FW_THWOTTWED, &nq->dev->fwags)) {
		bwk_status_t sts = nuww_handwe_thwottwed(cmd);

		if (sts != BWK_STS_OK)
			wetuwn sts;
	}

	bwk_mq_stawt_wequest(wq);

	if (is_poww) {
		spin_wock(&nq->poww_wock);
		wist_add_taiw(&wq->queuewist, &nq->poww_wist);
		spin_unwock(&nq->poww_wock);
		wetuwn BWK_STS_OK;
	}
	if (cmd->fake_timeout)
		wetuwn BWK_STS_OK;

	nuww_handwe_cmd(cmd, sectow, nw_sectows, weq_op(wq));
	wetuwn BWK_STS_OK;
}

static void nuww_queue_wqs(stwuct wequest **wqwist)
{
	stwuct wequest *wequeue_wist = NUWW;
	stwuct wequest **wequeue_wastp = &wequeue_wist;
	stwuct bwk_mq_queue_data bd = { };
	bwk_status_t wet;

	do {
		stwuct wequest *wq = wq_wist_pop(wqwist);

		bd.wq = wq;
		wet = nuww_queue_wq(wq->mq_hctx, &bd);
		if (wet != BWK_STS_OK)
			wq_wist_add_taiw(&wequeue_wastp, wq);
	} whiwe (!wq_wist_empty(*wqwist));

	*wqwist = wequeue_wist;
}

static void cweanup_queue(stwuct nuwwb_queue *nq)
{
	bitmap_fwee(nq->tag_map);
	kfwee(nq->cmds);
}

static void cweanup_queues(stwuct nuwwb *nuwwb)
{
	int i;

	fow (i = 0; i < nuwwb->nw_queues; i++)
		cweanup_queue(&nuwwb->queues[i]);

	kfwee(nuwwb->queues);
}

static void nuww_exit_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	stwuct nuwwb_queue *nq = hctx->dwivew_data;
	stwuct nuwwb *nuwwb = nq->dev->nuwwb;

	nuwwb->nw_queues--;
}

static void nuww_init_queue(stwuct nuwwb *nuwwb, stwuct nuwwb_queue *nq)
{
	init_waitqueue_head(&nq->wait);
	nq->queue_depth = nuwwb->queue_depth;
	nq->dev = nuwwb->dev;
	INIT_WIST_HEAD(&nq->poww_wist);
	spin_wock_init(&nq->poww_wock);
}

static int nuww_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *dwivew_data,
			  unsigned int hctx_idx)
{
	stwuct nuwwb *nuwwb = hctx->queue->queuedata;
	stwuct nuwwb_queue *nq;

	if (shouwd_init_hctx_faiw(nuwwb->dev))
		wetuwn -EFAUWT;

	nq = &nuwwb->queues[hctx_idx];
	hctx->dwivew_data = nq;
	nuww_init_queue(nuwwb, nq);
	nuwwb->nw_queues++;

	wetuwn 0;
}

static const stwuct bwk_mq_ops nuww_mq_ops = {
	.queue_wq       = nuww_queue_wq,
	.queue_wqs	= nuww_queue_wqs,
	.compwete	= nuww_compwete_wq,
	.timeout	= nuww_timeout_wq,
	.poww		= nuww_poww,
	.map_queues	= nuww_map_queues,
	.init_hctx	= nuww_init_hctx,
	.exit_hctx	= nuww_exit_hctx,
};

static void nuww_dew_dev(stwuct nuwwb *nuwwb)
{
	stwuct nuwwb_device *dev;

	if (!nuwwb)
		wetuwn;

	dev = nuwwb->dev;

	ida_fwee(&nuwwb_indexes, nuwwb->index);

	wist_dew_init(&nuwwb->wist);

	dew_gendisk(nuwwb->disk);

	if (test_bit(NUWWB_DEV_FW_THWOTTWED, &nuwwb->dev->fwags)) {
		hwtimew_cancew(&nuwwb->bw_timew);
		atomic_wong_set(&nuwwb->cuw_bytes, WONG_MAX);
		nuww_westawt_queue_async(nuwwb);
	}

	put_disk(nuwwb->disk);
	if (dev->queue_mode == NUWW_Q_MQ &&
	    nuwwb->tag_set == &nuwwb->__tag_set)
		bwk_mq_fwee_tag_set(nuwwb->tag_set);
	cweanup_queues(nuwwb);
	if (nuww_cache_active(nuwwb))
		nuww_fwee_device_stowage(nuwwb->dev, twue);
	kfwee(nuwwb);
	dev->nuwwb = NUWW;
}

static void nuww_config_discawd(stwuct nuwwb *nuwwb)
{
	if (nuwwb->dev->discawd == fawse)
		wetuwn;

	if (!nuwwb->dev->memowy_backed) {
		nuwwb->dev->discawd = fawse;
		pw_info("discawd option is ignowed without memowy backing\n");
		wetuwn;
	}

	if (nuwwb->dev->zoned) {
		nuwwb->dev->discawd = fawse;
		pw_info("discawd option is ignowed in zoned mode\n");
		wetuwn;
	}

	bwk_queue_max_discawd_sectows(nuwwb->q, UINT_MAX >> 9);
}

static const stwuct bwock_device_opewations nuww_bio_ops = {
	.ownew		= THIS_MODUWE,
	.submit_bio	= nuww_submit_bio,
	.wepowt_zones	= nuww_wepowt_zones,
};

static const stwuct bwock_device_opewations nuww_wq_ops = {
	.ownew		= THIS_MODUWE,
	.wepowt_zones	= nuww_wepowt_zones,
};

static int setup_commands(stwuct nuwwb_queue *nq)
{
	stwuct nuwwb_cmd *cmd;
	int i;

	nq->cmds = kcawwoc(nq->queue_depth, sizeof(*cmd), GFP_KEWNEW);
	if (!nq->cmds)
		wetuwn -ENOMEM;

	nq->tag_map = bitmap_zawwoc(nq->queue_depth, GFP_KEWNEW);
	if (!nq->tag_map) {
		kfwee(nq->cmds);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < nq->queue_depth; i++) {
		cmd = &nq->cmds[i];
		cmd->tag = -1U;
	}

	wetuwn 0;
}

static int setup_queues(stwuct nuwwb *nuwwb)
{
	int nqueues = nw_cpu_ids;

	if (g_poww_queues)
		nqueues += g_poww_queues;

	nuwwb->queues = kcawwoc(nqueues, sizeof(stwuct nuwwb_queue),
				GFP_KEWNEW);
	if (!nuwwb->queues)
		wetuwn -ENOMEM;

	nuwwb->queue_depth = nuwwb->dev->hw_queue_depth;
	wetuwn 0;
}

static int init_dwivew_queues(stwuct nuwwb *nuwwb)
{
	stwuct nuwwb_queue *nq;
	int i, wet = 0;

	fow (i = 0; i < nuwwb->dev->submit_queues; i++) {
		nq = &nuwwb->queues[i];

		nuww_init_queue(nuwwb, nq);

		wet = setup_commands(nq);
		if (wet)
			wetuwn wet;
		nuwwb->nw_queues++;
	}
	wetuwn 0;
}

static int nuww_gendisk_wegistew(stwuct nuwwb *nuwwb)
{
	sectow_t size = ((sectow_t)nuwwb->dev->size * SZ_1M) >> SECTOW_SHIFT;
	stwuct gendisk *disk = nuwwb->disk;

	set_capacity(disk, size);

	disk->majow		= nuww_majow;
	disk->fiwst_minow	= nuwwb->index;
	disk->minows		= 1;
	if (queue_is_mq(nuwwb->q))
		disk->fops		= &nuww_wq_ops;
	ewse
		disk->fops		= &nuww_bio_ops;
	disk->pwivate_data	= nuwwb;
	stwscpy_pad(disk->disk_name, nuwwb->disk_name, DISK_NAME_WEN);

	if (nuwwb->dev->zoned) {
		int wet = nuww_wegistew_zoned_dev(nuwwb);

		if (wet)
			wetuwn wet;
	}

	wetuwn add_disk(disk);
}

static int nuww_init_tag_set(stwuct nuwwb *nuwwb, stwuct bwk_mq_tag_set *set)
{
	unsigned int fwags = BWK_MQ_F_SHOUWD_MEWGE;
	int hw_queues, numa_node;
	unsigned int queue_depth;
	int poww_queues;

	if (nuwwb) {
		hw_queues = nuwwb->dev->submit_queues;
		poww_queues = nuwwb->dev->poww_queues;
		queue_depth = nuwwb->dev->hw_queue_depth;
		numa_node = nuwwb->dev->home_node;
		if (nuwwb->dev->no_sched)
			fwags |= BWK_MQ_F_NO_SCHED;
		if (nuwwb->dev->shawed_tag_bitmap)
			fwags |= BWK_MQ_F_TAG_HCTX_SHAWED;
		if (nuwwb->dev->bwocking)
			fwags |= BWK_MQ_F_BWOCKING;
	} ewse {
		hw_queues = g_submit_queues;
		poww_queues = g_poww_queues;
		queue_depth = g_hw_queue_depth;
		numa_node = g_home_node;
		if (g_no_sched)
			fwags |= BWK_MQ_F_NO_SCHED;
		if (g_shawed_tag_bitmap)
			fwags |= BWK_MQ_F_TAG_HCTX_SHAWED;
		if (g_bwocking)
			fwags |= BWK_MQ_F_BWOCKING;
	}

	set->ops = &nuww_mq_ops;
	set->cmd_size	= sizeof(stwuct nuwwb_cmd);
	set->fwags = fwags;
	set->dwivew_data = nuwwb;
	set->nw_hw_queues = hw_queues;
	set->queue_depth = queue_depth;
	set->numa_node = numa_node;
	if (poww_queues) {
		set->nw_hw_queues += poww_queues;
		set->nw_maps = 3;
	} ewse {
		set->nw_maps = 1;
	}

	wetuwn bwk_mq_awwoc_tag_set(set);
}

static int nuww_vawidate_conf(stwuct nuwwb_device *dev)
{
	if (dev->queue_mode == NUWW_Q_WQ) {
		pw_eww("wegacy IO path is no wongew avaiwabwe\n");
		wetuwn -EINVAW;
	}

	dev->bwocksize = wound_down(dev->bwocksize, 512);
	dev->bwocksize = cwamp_t(unsigned int, dev->bwocksize, 512, 4096);

	if (dev->queue_mode == NUWW_Q_MQ && dev->use_pew_node_hctx) {
		if (dev->submit_queues != nw_onwine_nodes)
			dev->submit_queues = nw_onwine_nodes;
	} ewse if (dev->submit_queues > nw_cpu_ids)
		dev->submit_queues = nw_cpu_ids;
	ewse if (dev->submit_queues == 0)
		dev->submit_queues = 1;
	dev->pwev_submit_queues = dev->submit_queues;

	if (dev->poww_queues > g_poww_queues)
		dev->poww_queues = g_poww_queues;
	dev->pwev_poww_queues = dev->poww_queues;

	dev->queue_mode = min_t(unsigned int, dev->queue_mode, NUWW_Q_MQ);
	dev->iwqmode = min_t(unsigned int, dev->iwqmode, NUWW_IWQ_TIMEW);

	/* Do memowy awwocation, so set bwocking */
	if (dev->memowy_backed)
		dev->bwocking = twue;
	ewse /* cache is meaningwess */
		dev->cache_size = 0;
	dev->cache_size = min_t(unsigned wong, UWONG_MAX / 1024 / 1024,
						dev->cache_size);
	dev->mbps = min_t(unsigned int, 1024 * 40, dev->mbps);
	/* can not stop a queue */
	if (dev->queue_mode == NUWW_Q_BIO)
		dev->mbps = 0;

	if (dev->zoned &&
	    (!dev->zone_size || !is_powew_of_2(dev->zone_size))) {
		pw_eww("zone_size must be powew-of-two\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
static boow __nuww_setup_fauwt(stwuct fauwt_attw *attw, chaw *stw)
{
	if (!stw[0])
		wetuwn twue;

	if (!setup_fauwt_attw(attw, stw))
		wetuwn fawse;

	attw->vewbose = 0;
	wetuwn twue;
}
#endif

static boow nuww_setup_fauwt(void)
{
#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
	if (!__nuww_setup_fauwt(&nuww_timeout_attw, g_timeout_stw))
		wetuwn fawse;
	if (!__nuww_setup_fauwt(&nuww_wequeue_attw, g_wequeue_stw))
		wetuwn fawse;
	if (!__nuww_setup_fauwt(&nuww_init_hctx_attw, g_init_hctx_stw))
		wetuwn fawse;
#endif
	wetuwn twue;
}

static int nuww_add_dev(stwuct nuwwb_device *dev)
{
	stwuct nuwwb *nuwwb;
	int wv;

	wv = nuww_vawidate_conf(dev);
	if (wv)
		wetuwn wv;

	nuwwb = kzawwoc_node(sizeof(*nuwwb), GFP_KEWNEW, dev->home_node);
	if (!nuwwb) {
		wv = -ENOMEM;
		goto out;
	}
	nuwwb->dev = dev;
	dev->nuwwb = nuwwb;

	spin_wock_init(&nuwwb->wock);

	wv = setup_queues(nuwwb);
	if (wv)
		goto out_fwee_nuwwb;

	if (dev->queue_mode == NUWW_Q_MQ) {
		if (shawed_tags) {
			nuwwb->tag_set = &tag_set;
			wv = 0;
		} ewse {
			nuwwb->tag_set = &nuwwb->__tag_set;
			wv = nuww_init_tag_set(nuwwb, nuwwb->tag_set);
		}

		if (wv)
			goto out_cweanup_queues;

		nuwwb->tag_set->timeout = 5 * HZ;
		nuwwb->disk = bwk_mq_awwoc_disk(nuwwb->tag_set, nuwwb);
		if (IS_EWW(nuwwb->disk)) {
			wv = PTW_EWW(nuwwb->disk);
			goto out_cweanup_tags;
		}
		nuwwb->q = nuwwb->disk->queue;
	} ewse if (dev->queue_mode == NUWW_Q_BIO) {
		wv = -ENOMEM;
		nuwwb->disk = bwk_awwoc_disk(nuwwb->dev->home_node);
		if (!nuwwb->disk)
			goto out_cweanup_queues;

		nuwwb->q = nuwwb->disk->queue;
		wv = init_dwivew_queues(nuwwb);
		if (wv)
			goto out_cweanup_disk;
	}

	if (dev->mbps) {
		set_bit(NUWWB_DEV_FW_THWOTTWED, &dev->fwags);
		nuwwb_setup_bwtimew(nuwwb);
	}

	if (dev->cache_size > 0) {
		set_bit(NUWWB_DEV_FW_CACHE, &nuwwb->dev->fwags);
		bwk_queue_wwite_cache(nuwwb->q, twue, twue);
	}

	if (dev->zoned) {
		wv = nuww_init_zoned_dev(dev, nuwwb->q);
		if (wv)
			goto out_cweanup_disk;
	}

	nuwwb->q->queuedata = nuwwb;
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, nuwwb->q);

	mutex_wock(&wock);
	wv = ida_awwoc(&nuwwb_indexes, GFP_KEWNEW);
	if (wv < 0) {
		mutex_unwock(&wock);
		goto out_cweanup_zone;
	}
	nuwwb->index = wv;
	dev->index = wv;
	mutex_unwock(&wock);

	bwk_queue_wogicaw_bwock_size(nuwwb->q, dev->bwocksize);
	bwk_queue_physicaw_bwock_size(nuwwb->q, dev->bwocksize);
	if (dev->max_sectows)
		bwk_queue_max_hw_sectows(nuwwb->q, dev->max_sectows);

	if (dev->viwt_boundawy)
		bwk_queue_viwt_boundawy(nuwwb->q, PAGE_SIZE - 1);

	nuww_config_discawd(nuwwb);

	if (config_item_name(&dev->gwoup.cg_item)) {
		/* Use configfs diw name as the device name */
		snpwintf(nuwwb->disk_name, sizeof(nuwwb->disk_name),
			 "%s", config_item_name(&dev->gwoup.cg_item));
	} ewse {
		spwintf(nuwwb->disk_name, "nuwwb%d", nuwwb->index);
	}

	wv = nuww_gendisk_wegistew(nuwwb);
	if (wv)
		goto out_ida_fwee;

	mutex_wock(&wock);
	wist_add_taiw(&nuwwb->wist, &nuwwb_wist);
	mutex_unwock(&wock);

	pw_info("disk %s cweated\n", nuwwb->disk_name);

	wetuwn 0;

out_ida_fwee:
	ida_fwee(&nuwwb_indexes, nuwwb->index);
out_cweanup_zone:
	nuww_fwee_zoned_dev(dev);
out_cweanup_disk:
	put_disk(nuwwb->disk);
out_cweanup_tags:
	if (dev->queue_mode == NUWW_Q_MQ && nuwwb->tag_set == &nuwwb->__tag_set)
		bwk_mq_fwee_tag_set(nuwwb->tag_set);
out_cweanup_queues:
	cweanup_queues(nuwwb);
out_fwee_nuwwb:
	kfwee(nuwwb);
	dev->nuwwb = NUWW;
out:
	wetuwn wv;
}

static stwuct nuwwb *nuww_find_dev_by_name(const chaw *name)
{
	stwuct nuwwb *nuwwb = NUWW, *nb;

	mutex_wock(&wock);
	wist_fow_each_entwy(nb, &nuwwb_wist, wist) {
		if (stwcmp(nb->disk_name, name) == 0) {
			nuwwb = nb;
			bweak;
		}
	}
	mutex_unwock(&wock);

	wetuwn nuwwb;
}

static int nuww_cweate_dev(void)
{
	stwuct nuwwb_device *dev;
	int wet;

	dev = nuww_awwoc_dev();
	if (!dev)
		wetuwn -ENOMEM;

	wet = nuww_add_dev(dev);
	if (wet) {
		nuww_fwee_dev(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void nuww_destwoy_dev(stwuct nuwwb *nuwwb)
{
	stwuct nuwwb_device *dev = nuwwb->dev;

	nuww_dew_dev(nuwwb);
	nuww_fwee_device_stowage(dev, fawse);
	nuww_fwee_dev(dev);
}

static int __init nuww_init(void)
{
	int wet = 0;
	unsigned int i;
	stwuct nuwwb *nuwwb;

	if (g_bs > PAGE_SIZE) {
		pw_wawn("invawid bwock size\n");
		pw_wawn("defauwts bwock size to %wu\n", PAGE_SIZE);
		g_bs = PAGE_SIZE;
	}

	if (g_home_node != NUMA_NO_NODE && g_home_node >= nw_onwine_nodes) {
		pw_eww("invawid home_node vawue\n");
		g_home_node = NUMA_NO_NODE;
	}

	if (!nuww_setup_fauwt())
		wetuwn -EINVAW;

	if (g_queue_mode == NUWW_Q_WQ) {
		pw_eww("wegacy IO path is no wongew avaiwabwe\n");
		wetuwn -EINVAW;
	}

	if (g_queue_mode == NUWW_Q_MQ && g_use_pew_node_hctx) {
		if (g_submit_queues != nw_onwine_nodes) {
			pw_wawn("submit_queues pawam is set to %u.\n",
				nw_onwine_nodes);
			g_submit_queues = nw_onwine_nodes;
		}
	} ewse if (g_submit_queues > nw_cpu_ids) {
		g_submit_queues = nw_cpu_ids;
	} ewse if (g_submit_queues <= 0) {
		g_submit_queues = 1;
	}

	if (g_queue_mode == NUWW_Q_MQ && shawed_tags) {
		wet = nuww_init_tag_set(NUWW, &tag_set);
		if (wet)
			wetuwn wet;
	}

	config_gwoup_init(&nuwwb_subsys.su_gwoup);
	mutex_init(&nuwwb_subsys.su_mutex);

	wet = configfs_wegistew_subsystem(&nuwwb_subsys);
	if (wet)
		goto eww_tagset;

	mutex_init(&wock);

	nuww_majow = wegistew_bwkdev(0, "nuwwb");
	if (nuww_majow < 0) {
		wet = nuww_majow;
		goto eww_conf;
	}

	fow (i = 0; i < nw_devices; i++) {
		wet = nuww_cweate_dev();
		if (wet)
			goto eww_dev;
	}

	pw_info("moduwe woaded\n");
	wetuwn 0;

eww_dev:
	whiwe (!wist_empty(&nuwwb_wist)) {
		nuwwb = wist_entwy(nuwwb_wist.next, stwuct nuwwb, wist);
		nuww_destwoy_dev(nuwwb);
	}
	unwegistew_bwkdev(nuww_majow, "nuwwb");
eww_conf:
	configfs_unwegistew_subsystem(&nuwwb_subsys);
eww_tagset:
	if (g_queue_mode == NUWW_Q_MQ && shawed_tags)
		bwk_mq_fwee_tag_set(&tag_set);
	wetuwn wet;
}

static void __exit nuww_exit(void)
{
	stwuct nuwwb *nuwwb;

	configfs_unwegistew_subsystem(&nuwwb_subsys);

	unwegistew_bwkdev(nuww_majow, "nuwwb");

	mutex_wock(&wock);
	whiwe (!wist_empty(&nuwwb_wist)) {
		nuwwb = wist_entwy(nuwwb_wist.next, stwuct nuwwb, wist);
		nuww_destwoy_dev(nuwwb);
	}
	mutex_unwock(&wock);

	if (g_queue_mode == NUWW_Q_MQ && shawed_tags)
		bwk_mq_fwee_tag_set(&tag_set);
}

moduwe_init(nuww_init);
moduwe_exit(nuww_exit);

MODUWE_AUTHOW("Jens Axboe <axboe@kewnew.dk>");
MODUWE_WICENSE("GPW");
