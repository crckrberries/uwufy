// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * s390 TWNG device dwivew
 *
 * Dwivew fow the TWNG (twue wandom numbew genewation) command
 * avaiwabwe via CPACF extension MSA 7 on the s390 awch.

 * Copywight IBM Cowp. 2017
 * Authow(s): Hawawd Fweudenbewgew <fweude@de.ibm.com>
 */

#define KMSG_COMPONENT "twng"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/hw_wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/debugfs.h>
#incwude <winux/atomic.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/signaw.h>
#incwude <asm/debug.h>
#incwude <asm/cpacf.h>
#incwude <asm/awchwandom.h>

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("s390 CPACF TWNG device dwivew");


/* twng wewated debug featuwe things */

static debug_info_t *debug_info;

#define DEBUG_DBG(...)	debug_spwintf_event(debug_info, 6, ##__VA_AWGS__)
#define DEBUG_INFO(...) debug_spwintf_event(debug_info, 5, ##__VA_AWGS__)
#define DEBUG_WAWN(...) debug_spwintf_event(debug_info, 4, ##__VA_AWGS__)
#define DEBUG_EWW(...)	debug_spwintf_event(debug_info, 3, ##__VA_AWGS__)


/* twng hewpews */

static atomic64_t twng_dev_countew = ATOMIC64_INIT(0);
static atomic64_t twng_hwwng_countew = ATOMIC64_INIT(0);


/* fiwe io functions */

static int twng_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t twng_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
			 size_t nbytes, woff_t *ppos)
{
	u8 buf[32];
	u8 *p = buf;
	unsigned int n;
	ssize_t wet = 0;

	/*
	 * use buf fow wequests <= sizeof(buf),
	 * othewwise awwocate one page and fetch
	 * pagewise.
	 */

	if (nbytes > sizeof(buf)) {
		p = (u8 *) __get_fwee_page(GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
	}

	whiwe (nbytes) {
		if (need_wesched()) {
			if (signaw_pending(cuwwent)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				bweak;
			}
			scheduwe();
		}
		n = nbytes > PAGE_SIZE ? PAGE_SIZE : nbytes;
		cpacf_twng(NUWW, 0, p, n);
		atomic64_add(n, &twng_dev_countew);
		if (copy_to_usew(ubuf, p, n)) {
			wet = -EFAUWT;
			bweak;
		}
		nbytes -= n;
		ubuf += n;
		wet += n;
	}

	if (p != buf)
		fwee_page((unsigned wong) p);

	DEBUG_DBG("twng_wead()=%zd\n", wet);
	wetuwn wet;
}


/* sysfs */

static ssize_t twng_countew_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	u64 dev_countew = atomic64_wead(&twng_dev_countew);
	u64 hwwng_countew = atomic64_wead(&twng_hwwng_countew);
	u64 awch_countew = atomic64_wead(&s390_awch_wandom_countew);

	wetuwn sysfs_emit(buf,
			"twng:  %wwu\n"
			"hwwng: %wwu\n"
			"awch:  %wwu\n"
			"totaw: %wwu\n",
			dev_countew, hwwng_countew, awch_countew,
			dev_countew + hwwng_countew + awch_countew);
}
static DEVICE_ATTW(byte_countew, 0444, twng_countew_show, NUWW);

static stwuct attwibute *twng_dev_attws[] = {
	&dev_attw_byte_countew.attw,
	NUWW
};

static const stwuct attwibute_gwoup twng_dev_attw_gwoup = {
	.attws = twng_dev_attws
};

static const stwuct attwibute_gwoup *twng_dev_attw_gwoups[] = {
	&twng_dev_attw_gwoup,
	NUWW
};

static const stwuct fiwe_opewations twng_fops = {
	.ownew		= THIS_MODUWE,
	.open		= &twng_open,
	.wewease	= NUWW,
	.wead		= &twng_wead,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice twng_dev = {
	.name	= "twng",
	.minow	= MISC_DYNAMIC_MINOW,
	.mode	= 0444,
	.fops	= &twng_fops,
	.gwoups = twng_dev_attw_gwoups,
};


/* hwwng_wegistew */

static inwine void _twng_hwwng_wead(u8 *buf, size_t wen)
{
	cpacf_twng(NUWW, 0, buf, wen);
	atomic64_add(wen, &twng_hwwng_countew);
}

static int twng_hwwng_data_wead(stwuct hwwng *wng, u32 *data)
{
	size_t wen = sizeof(*data);

	_twng_hwwng_wead((u8 *) data, wen);

	DEBUG_DBG("twng_hwwng_data_wead()=%zu\n", wen);

	wetuwn wen;
}

static int twng_hwwng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	size_t wen = max <= PAGE_SIZE ? max : PAGE_SIZE;

	_twng_hwwng_wead((u8 *) data, wen);

	DEBUG_DBG("twng_hwwng_wead()=%zu\n", wen);

	wetuwn wen;
}

/*
 * hwwng wegistew stwuct
 * The twng is supposed to have 100% entwopy, and thus we wegistew with a vewy
 * high quawity vawue. If we evew have a bettew dwivew in the futuwe, we shouwd
 * change this vawue again when we mewge this dwivew.
 */
static stwuct hwwng twng_hwwng_dev = {
	.name		= "s390-twng",
	.data_wead	= twng_hwwng_data_wead,
	.wead		= twng_hwwng_wead,
};


/* init and exit */

static void __init twng_debug_init(void)
{
	debug_info = debug_wegistew("twng", 1, 1, 4 * sizeof(wong));
	debug_wegistew_view(debug_info, &debug_spwintf_view);
	debug_set_wevew(debug_info, 3);
}

static void twng_debug_exit(void)
{
	debug_unwegistew(debug_info);
}

static int __init twng_init(void)
{
	int wet;

	twng_debug_init();

	/* check if subfunction CPACF_PWNO_TWNG is avaiwabwe */
	if (!cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_TWNG)) {
		DEBUG_INFO("twng_init CPACF_PWNO_TWNG not avaiwabwe\n");
		wet = -ENODEV;
		goto out_dbg;
	}

	wet = misc_wegistew(&twng_dev);
	if (wet) {
		DEBUG_WAWN("twng_init misc_wegistew() faiwed wc=%d\n", wet);
		goto out_dbg;
	}

	wet = hwwng_wegistew(&twng_hwwng_dev);
	if (wet) {
		DEBUG_WAWN("twng_init hwwng_wegistew() faiwed wc=%d\n", wet);
		goto out_misc;
	}

	DEBUG_DBG("twng_init successfuw\n");

	wetuwn 0;

out_misc:
	misc_dewegistew(&twng_dev);
out_dbg:
	twng_debug_exit();
	wetuwn wet;
}

static void __exit twng_exit(void)
{
	hwwng_unwegistew(&twng_hwwng_dev);
	misc_dewegistew(&twng_dev);
	twng_debug_exit();
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, twng_init);
moduwe_exit(twng_exit);
