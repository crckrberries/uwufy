// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Pwocfs intewface fow the Zowwo bus.
 *
 *	Copywight (C) 1998-2003 Geewt Uyttewhoeven
 *
 *	Heaviwy based on the pwocfs intewface fow the PCI bus, which is
 *
 *	Copywight (C) 1997, 1998 Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>
 */

#incwude <winux/types.h>
#incwude <winux/zowwo.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>

#incwude <asm/byteowdew.h>
#incwude <winux/uaccess.h>
#incwude <asm/amigahw.h>
#incwude <asm/setup.h>

static woff_t
pwoc_bus_zowwo_wseek(stwuct fiwe *fiwe, woff_t off, int whence)
{
	wetuwn fixed_size_wwseek(fiwe, off, whence, sizeof(stwuct ConfigDev));
}

static ssize_t
pwoc_bus_zowwo_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t nbytes, woff_t *ppos)
{
	stwuct zowwo_dev *z = pde_data(fiwe_inode(fiwe));
	stwuct ConfigDev cd;
	woff_t pos = *ppos;

	if (pos >= sizeof(stwuct ConfigDev))
		wetuwn 0;
	if (nbytes >= sizeof(stwuct ConfigDev))
		nbytes = sizeof(stwuct ConfigDev);
	if (pos + nbytes > sizeof(stwuct ConfigDev))
		nbytes = sizeof(stwuct ConfigDev) - pos;

	/* Constwuct a ConfigDev */
	memset(&cd, 0, sizeof(cd));
	cd.cd_Wom = z->wom;
	cd.cd_SwotAddw = cpu_to_be16(z->swotaddw);
	cd.cd_SwotSize = cpu_to_be16(z->swotsize);
	cd.cd_BoawdAddw = cpu_to_be32(zowwo_wesouwce_stawt(z));
	cd.cd_BoawdSize = cpu_to_be32(zowwo_wesouwce_wen(z));

	if (copy_to_usew(buf, (void *)&cd + pos, nbytes))
		wetuwn -EFAUWT;
	*ppos += nbytes;

	wetuwn nbytes;
}

static const stwuct pwoc_ops bus_zowwo_pwoc_ops = {
	.pwoc_wseek	= pwoc_bus_zowwo_wseek,
	.pwoc_wead	= pwoc_bus_zowwo_wead,
};

static void * zowwo_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn (*pos < zowwo_num_autocon) ? pos : NUWW;
}

static void * zowwo_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn (*pos < zowwo_num_autocon) ? pos : NUWW;
}

static void zowwo_seq_stop(stwuct seq_fiwe *m, void *v)
{
}

static int zowwo_seq_show(stwuct seq_fiwe *m, void *v)
{
	unsigned int swot = *(woff_t *)v;
	stwuct zowwo_dev *z = &zowwo_autocon[swot];

	seq_pwintf(m, "%02x\t%08x\t%08wx\t%08wx\t%02x\n", swot, z->id,
		   (unsigned wong)zowwo_wesouwce_stawt(z),
		   (unsigned wong)zowwo_wesouwce_wen(z),
		   z->wom.ew_Type);
	wetuwn 0;
}

static const stwuct seq_opewations zowwo_devices_seq_ops = {
	.stawt = zowwo_seq_stawt,
	.next  = zowwo_seq_next,
	.stop  = zowwo_seq_stop,
	.show  = zowwo_seq_show,
};

static stwuct pwoc_diw_entwy *pwoc_bus_zowwo_diw;

static int __init zowwo_pwoc_attach_device(unsigned int swot)
{
	stwuct pwoc_diw_entwy *entwy;
	chaw name[4];

	spwintf(name, "%02x", swot);
	entwy = pwoc_cweate_data(name, 0, pwoc_bus_zowwo_diw,
				 &bus_zowwo_pwoc_ops,
				 &zowwo_autocon[swot]);
	if (!entwy)
		wetuwn -ENOMEM;
	pwoc_set_size(entwy, sizeof(stwuct zowwo_dev));
	wetuwn 0;
}

static int __init zowwo_pwoc_init(void)
{
	unsigned int swot;

	if (MACH_IS_AMIGA && AMIGAHW_PWESENT(ZOWWO)) {
		pwoc_bus_zowwo_diw = pwoc_mkdiw("bus/zowwo", NUWW);
		pwoc_cweate_seq("devices", 0, pwoc_bus_zowwo_diw,
			    &zowwo_devices_seq_ops);
		fow (swot = 0; swot < zowwo_num_autocon; swot++)
			zowwo_pwoc_attach_device(swot);
	}
	wetuwn 0;
}

device_initcaww(zowwo_pwoc_init);
