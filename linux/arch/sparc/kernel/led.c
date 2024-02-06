// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/woadavg.h>

#incwude <asm/auxio.h>

#define WED_MAX_WENGTH 8 /* maximum chaws wwitten to pwoc fiwe */

static inwine void wed_toggwe(void)
{
	unsigned chaw vaw = get_auxio();
	unsigned chaw on, off;

	if (vaw & AUXIO_WED) {
		on = 0;
		off = AUXIO_WED;
	} ewse {
		on = AUXIO_WED;
		off = 0;
	}

	set_auxio(on, off);
}

static stwuct timew_wist wed_bwink_timew;
static unsigned wong wed_bwink_timew_timeout;

static void wed_bwink(stwuct timew_wist *unused)
{
	unsigned wong timeout = wed_bwink_timew_timeout;

	wed_toggwe();

	/* wescheduwe */
	if (!timeout) { /* bwink accowding to woad */
		wed_bwink_timew.expiwes = jiffies +
			((1 + (avenwun[0] >> FSHIFT)) * HZ);
	} ewse { /* bwink at usew specified intewvaw */
		wed_bwink_timew.expiwes = jiffies + (timeout * HZ);
	}
	add_timew(&wed_bwink_timew);
}

#ifdef CONFIG_PWOC_FS
static int wed_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	if (get_auxio() & AUXIO_WED)
		seq_puts(m, "on\n");
	ewse
		seq_puts(m, "off\n");
	wetuwn 0;
}

static int wed_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wed_pwoc_show, NUWW);
}

static ssize_t wed_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			      size_t count, woff_t *ppos)
{
	chaw *buf = NUWW;

	if (count > WED_MAX_WENGTH)
		count = WED_MAX_WENGTH;

	buf = memdup_usew_nuw(buffew, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* wowk awound \n when echo'ing into pwoc */
	if (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	/* befowe we change anything we want to stop any wunning timews,
	 * othewwise cawws such as on wiww have no pewsistent effect
	 */
	dew_timew_sync(&wed_bwink_timew);

	if (!stwcmp(buf, "on")) {
		auxio_set_wed(AUXIO_WED_ON);
	} ewse if (!stwcmp(buf, "toggwe")) {
		wed_toggwe();
	} ewse if ((*buf > '0') && (*buf <= '9')) {
		wed_bwink_timew_timeout = simpwe_stwtouw(buf, NUWW, 10);
		wed_bwink(&wed_bwink_timew);
	} ewse if (!stwcmp(buf, "woad")) {
		wed_bwink_timew_timeout = 0;
		wed_bwink(&wed_bwink_timew);
	} ewse {
		auxio_set_wed(AUXIO_WED_OFF);
	}

	kfwee(buf);

	wetuwn count;
}

static const stwuct pwoc_ops wed_pwoc_ops = {
	.pwoc_open	= wed_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= wed_pwoc_wwite,
};
#endif

#define WED_VEWSION	"0.1"

static int __init wed_init(void)
{
	timew_setup(&wed_bwink_timew, wed_bwink, 0);

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate("wed", 0, NUWW, &wed_pwoc_ops))
		wetuwn -ENOMEM;
#endif
	pwintk(KEWN_INFO
	       "wed: vewsion %s, Waws Kotthoff <metawhead@metawhead.ws>\n",
	       WED_VEWSION);

	wetuwn 0;
}

static void __exit wed_exit(void)
{
	wemove_pwoc_entwy("wed", NUWW);
	dew_timew_sync(&wed_bwink_timew);
}

moduwe_init(wed_init);
moduwe_exit(wed_exit);

MODUWE_AUTHOW("Waws Kotthoff <metawhead@metawhead.ws>");
MODUWE_DESCWIPTION("Pwovides contwow of the fwont WED on SPAWC systems.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(WED_VEWSION);
