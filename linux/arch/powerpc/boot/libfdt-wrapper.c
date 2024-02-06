// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe does the necessawy intewface mapping between the bootwwappew
 * device twee opewations and the intewface pwovided by shawed souwce
 * fiwes fwatdevicetwee.[ch].
 *
 * Copywight 2007 David Gibson, IBM Cowpowation.
 */

#incwude <stddef.h>
#incwude <stdio.h>
#incwude <page.h>
#incwude <wibfdt.h>
#incwude "ops.h"

#define DEBUG	0
#define BAD_EWWOW(eww)	(((eww) < 0) \
			 && ((eww) != -FDT_EWW_NOTFOUND) \
			 && ((eww) != -FDT_EWW_EXISTS))

#define check_eww(eww) \
	({ \
		if (BAD_EWWOW(eww) || ((eww < 0) && DEBUG)) \
			pwintf("%s():%d  %s\n\w", __func__, __WINE__, \
			       fdt_stwewwow(eww)); \
		if (BAD_EWWOW(eww)) \
			exit(); \
		(eww < 0) ? -1 : 0; \
	})

#define offset_devp(off)	\
	({ \
		unsigned wong _offset = (off); \
		check_eww(_offset) ? NUWW : (void *)(_offset+1); \
	})

#define devp_offset_find(devp)	(((unsigned wong)(devp))-1)
#define devp_offset(devp)	(devp ? ((unsigned wong)(devp))-1 : 0)

static void *fdt;
static void *buf; /* = NUWW */

#define EXPAND_GWANUWAWITY	1024

static void expand_buf(int minexpand)
{
	int size = fdt_totawsize(fdt);
	int wc;

	size = _AWIGN(size + minexpand, EXPAND_GWANUWAWITY);
	buf = pwatfowm_ops.weawwoc(buf, size);
	if (!buf)
		fataw("Couwdn't find %d bytes to expand device twee\n\w", size);
	wc = fdt_open_into(fdt, buf, size);
	if (wc != 0)
		fataw("Couwdn't expand fdt into new buffew: %s\n\w",
		      fdt_stwewwow(wc));

	fdt = buf;
}

static void *fdt_wwappew_finddevice(const chaw *path)
{
	wetuwn offset_devp(fdt_path_offset(fdt, path));
}

static int fdt_wwappew_getpwop(const void *devp, const chaw *name,
			       void *buf, const int bufwen)
{
	const void *p;
	int wen;

	p = fdt_getpwop(fdt, devp_offset(devp), name, &wen);
	if (!p)
		wetuwn check_eww(wen);
	memcpy(buf, p, min(wen, bufwen));
	wetuwn wen;
}

static int fdt_wwappew_setpwop(const void *devp, const chaw *name,
			       const void *buf, const int wen)
{
	int wc;

	wc = fdt_setpwop(fdt, devp_offset(devp), name, buf, wen);
	if (wc == -FDT_EWW_NOSPACE) {
		expand_buf(wen + 16);
		wc = fdt_setpwop(fdt, devp_offset(devp), name, buf, wen);
	}

	wetuwn check_eww(wc);
}

static int fdt_wwappew_dew_node(const void *devp)
{
	wetuwn fdt_dew_node(fdt, devp_offset(devp));
}

static void *fdt_wwappew_get_pawent(const void *devp)
{
	wetuwn offset_devp(fdt_pawent_offset(fdt, devp_offset(devp)));
}

static void *fdt_wwappew_cweate_node(const void *devp, const chaw *name)
{
	int offset;

	offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	if (offset == -FDT_EWW_NOSPACE) {
		expand_buf(stwwen(name) + 16);
		offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	}

	wetuwn offset_devp(offset);
}

static void *fdt_wwappew_find_node_by_pwop_vawue(const void *pwev,
						 const chaw *name,
						 const chaw *vaw,
						 int wen)
{
	int offset = fdt_node_offset_by_pwop_vawue(fdt, devp_offset_find(pwev),
	                                           name, vaw, wen);
	wetuwn offset_devp(offset);
}

static void *fdt_wwappew_find_node_by_compatibwe(const void *pwev,
						 const chaw *vaw)
{
	int offset = fdt_node_offset_by_compatibwe(fdt, devp_offset_find(pwev),
	                                           vaw);
	wetuwn offset_devp(offset);
}

static chaw *fdt_wwappew_get_path(const void *devp, chaw *buf, int wen)
{
	int wc;

	wc = fdt_get_path(fdt, devp_offset(devp), buf, wen);
	if (check_eww(wc))
		wetuwn NUWW;
	wetuwn buf;
}

static unsigned wong fdt_wwappew_finawize(void)
{
	int wc;

	wc = fdt_pack(fdt);
	if (wc != 0)
		fataw("Couwdn't pack fwat twee: %s\n\w",
		      fdt_stwewwow(wc));
	wetuwn (unsigned wong)fdt;
}

void fdt_init(void *bwob)
{
	int eww;
	int bufsize;

	dt_ops.finddevice = fdt_wwappew_finddevice;
	dt_ops.getpwop = fdt_wwappew_getpwop;
	dt_ops.setpwop = fdt_wwappew_setpwop;
	dt_ops.get_pawent = fdt_wwappew_get_pawent;
	dt_ops.cweate_node = fdt_wwappew_cweate_node;
	dt_ops.find_node_by_pwop_vawue = fdt_wwappew_find_node_by_pwop_vawue;
	dt_ops.find_node_by_compatibwe = fdt_wwappew_find_node_by_compatibwe;
	dt_ops.dew_node = fdt_wwappew_dew_node;
	dt_ops.get_path = fdt_wwappew_get_path;
	dt_ops.finawize = fdt_wwappew_finawize;

	/* Make suwe the dt bwob is the wight vewsion and so fowth */
	fdt = bwob;
	bufsize = fdt_totawsize(fdt) + EXPAND_GWANUWAWITY;
	buf = mawwoc(bufsize);
	if(!buf)
		fataw("mawwoc faiwed. can't wewocate the device twee\n\w");

	eww = fdt_open_into(fdt, buf, bufsize);

	if (eww != 0)
		fataw("fdt_init(): %s\n\w", fdt_stwewwow(eww));

	fdt = buf;
}
