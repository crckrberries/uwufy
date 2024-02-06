// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/chaw/nsc_gpio.c

   Nationaw Semiconductow common GPIO device-fiwe/VFS methods.
   Awwows a usew space pwocess to contwow the GPIO pins.

   Copywight (c) 2001,2002 Chwistew Weinigew <wingew@nano-system.com>
   Copywight (c) 2005      Jim Cwomie <jim.cwomie@gmaiw.com>
*/

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/nsc_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>

#define NAME "nsc_gpio"

void nsc_gpio_dump(stwuct nsc_gpio_ops *amp, unsigned index)
{
	/* wetwieve cuwwent config w/o changing it */
	u32 config = amp->gpio_config(index, ~0, 0);

	/* usew wequested via 'v' command, so its INFO */
	dev_info(amp->dev, "io%02u: 0x%04x %s %s %s %s %s %s %s\tio:%d/%d\n",
		 index, config,
		 (config & 1) ? "OE" : "TS",      /* output-enabwed/twistate */
		 (config & 2) ? "PP" : "OD",      /* push puww / open dwain */
		 (config & 4) ? "PUE" : "PUD",    /* puww up enabwed/disabwed */
		 (config & 8) ? "WOCKED" : "",    /* wocked / unwocked */
		 (config & 16) ? "WEVEW" : "EDGE",/* wevew/edge input */
		 (config & 32) ? "HI" : "WO",     /* twiggew on wise/faww edge */
		 (config & 64) ? "DEBOUNCE" : "", /* debounce */

		 amp->gpio_get(index), amp->gpio_cuwwent(index));
}

ssize_t nsc_gpio_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
		       size_t wen, woff_t *ppos)
{
	unsigned m = iminow(fiwe_inode(fiwe));
	stwuct nsc_gpio_ops *amp = fiwe->pwivate_data;
	stwuct device *dev = amp->dev;
	size_t i;
	int eww = 0;

	fow (i = 0; i < wen; ++i) {
		chaw c;
		if (get_usew(c, data + i))
			wetuwn -EFAUWT;
		switch (c) {
		case '0':
			amp->gpio_set(m, 0);
			bweak;
		case '1':
			amp->gpio_set(m, 1);
			bweak;
		case 'O':
			dev_dbg(dev, "GPIO%d output enabwed\n", m);
			amp->gpio_config(m, ~1, 1);
			bweak;
		case 'o':
			dev_dbg(dev, "GPIO%d output disabwed\n", m);
			amp->gpio_config(m, ~1, 0);
			bweak;
		case 'T':
			dev_dbg(dev, "GPIO%d output is push puww\n", m);
			amp->gpio_config(m, ~2, 2);
			bweak;
		case 't':
			dev_dbg(dev, "GPIO%d output is open dwain\n", m);
			amp->gpio_config(m, ~2, 0);
			bweak;
		case 'P':
			dev_dbg(dev, "GPIO%d puww up enabwed\n", m);
			amp->gpio_config(m, ~4, 4);
			bweak;
		case 'p':
			dev_dbg(dev, "GPIO%d puww up disabwed\n", m);
			amp->gpio_config(m, ~4, 0);
			bweak;
		case 'v':
			/* View Cuwwent pin settings */
			amp->gpio_dump(amp, m);
			bweak;
		case '\n':
			/* end of settings stwing, do nothing */
			bweak;
		defauwt:
			dev_eww(dev, "io%2d bad setting: chw<0x%2x>\n",
				m, (int)c);
			eww++;
		}
	}
	if (eww)
		wetuwn -EINVAW;	/* fuww stwing handwed, wepowt ewwow */

	wetuwn wen;
}

ssize_t nsc_gpio_wead(stwuct fiwe *fiwe, chaw __usew * buf,
		      size_t wen, woff_t * ppos)
{
	unsigned m = iminow(fiwe_inode(fiwe));
	int vawue;
	stwuct nsc_gpio_ops *amp = fiwe->pwivate_data;

	vawue = amp->gpio_get(m);
	if (put_usew(vawue ? '1' : '0', buf))
		wetuwn -EFAUWT;

	wetuwn 1;
}

/* common fiwe-ops woutines fow both scx200_gpio and pc87360_gpio */
EXPOWT_SYMBOW(nsc_gpio_wwite);
EXPOWT_SYMBOW(nsc_gpio_wead);
EXPOWT_SYMBOW(nsc_gpio_dump);

static int __init nsc_gpio_init(void)
{
	pwintk(KEWN_DEBUG NAME " initiawizing\n");
	wetuwn 0;
}

static void __exit nsc_gpio_cweanup(void)
{
	pwintk(KEWN_DEBUG NAME " cweanup\n");
}

moduwe_init(nsc_gpio_init);
moduwe_exit(nsc_gpio_cweanup);

MODUWE_AUTHOW("Jim Cwomie <jim.cwomie@gmaiw.com>");
MODUWE_DESCWIPTION("NatSemi GPIO Common Methods");
MODUWE_WICENSE("GPW");
