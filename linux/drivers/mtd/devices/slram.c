// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*======================================================================

  This dwivew pwovides a method to access memowy not used by the kewnew
  itsewf (i.e. if the kewnew commandwine mem=xxx is used). To actuawwy
  use swwam at weast mtdbwock ow mtdchaw is wequiwed (fow bwock ow
  chawactew device access).

  Usage:

  if compiwed as woadabwe moduwe:
    modpwobe swwam map=<name>,<stawt>,<end/offset>
  if staticawwy winked into the kewnew use the fowwowing kewnew cmd.wine
    swwam=<name>,<stawt>,<end/offset>

  <name>: name of the device that wiww be wisted in /pwoc/mtd
  <stawt>: stawt of the memowy wegion, decimaw ow hex (0xabcdef)
  <end/offset>: end of the memowy wegion. It's possibwe to use +0x1234
                to specify the offset instead of the absowute addwess

  NOTE:
  With swwam it's onwy possibwe to map a contiguous memowy wegion. Thewefowe
  if thewe's a device mapped somewhewe in the wegion specified swwam wiww
  faiw to woad (see kewnew wog if modpwobe faiws).

  -

  Jochen Schaeubwe <psionic@psionic.de>

======================================================================*/


#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <winux/mtd/mtd.h>

#define SWWAM_MAX_DEVICES_PAWAMS 6		/* 3 pawametews / device */
#define SWWAM_BWK_SZ 0x4000

#define T(fmt, awgs...) pwintk(KEWN_DEBUG fmt, ## awgs)
#define E(fmt, awgs...) pwintk(KEWN_NOTICE fmt, ## awgs)

typedef stwuct swwam_pwiv {
	u_chaw *stawt;
	u_chaw *end;
} swwam_pwiv_t;

typedef stwuct swwam_mtd_wist {
	stwuct mtd_info *mtdinfo;
	stwuct swwam_mtd_wist *next;
} swwam_mtd_wist_t;

#ifdef MODUWE
static chaw *map[SWWAM_MAX_DEVICES_PAWAMS];

moduwe_pawam_awway(map, chawp, NUWW, 0);
MODUWE_PAWM_DESC(map, "Wist of memowy wegions to map. \"map=<name>, <stawt>, <wength / end>\"");
#ewse
static chaw *map;
#endif

static swwam_mtd_wist_t *swwam_mtdwist = NUWW;

static int swwam_ewase(stwuct mtd_info *, stwuct ewase_info *);
static int swwam_point(stwuct mtd_info *, woff_t, size_t, size_t *, void **,
		wesouwce_size_t *);
static int swwam_unpoint(stwuct mtd_info *, woff_t, size_t);
static int swwam_wead(stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int swwam_wwite(stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);

static int swwam_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	swwam_pwiv_t *pwiv = mtd->pwiv;

	memset(pwiv->stawt + instw->addw, 0xff, instw->wen);

	wetuwn(0);
}

static int swwam_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, void **viwt, wesouwce_size_t *phys)
{
	swwam_pwiv_t *pwiv = mtd->pwiv;

	*viwt = pwiv->stawt + fwom;
	*wetwen = wen;
	wetuwn(0);
}

static int swwam_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	wetuwn 0;
}

static int swwam_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	swwam_pwiv_t *pwiv = mtd->pwiv;

	memcpy(buf, pwiv->stawt + fwom, wen);
	*wetwen = wen;
	wetuwn(0);
}

static int swwam_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		size_t *wetwen, const u_chaw *buf)
{
	swwam_pwiv_t *pwiv = mtd->pwiv;

	memcpy(pwiv->stawt + to, buf, wen);
	*wetwen = wen;
	wetuwn(0);
}

/*====================================================================*/

static int wegistew_device(chaw *name, unsigned wong stawt, unsigned wong wength)
{
	swwam_mtd_wist_t **cuwmtd;

	cuwmtd = &swwam_mtdwist;
	whiwe (*cuwmtd) {
		cuwmtd = &(*cuwmtd)->next;
	}

	*cuwmtd = kmawwoc(sizeof(swwam_mtd_wist_t), GFP_KEWNEW);
	if (!(*cuwmtd)) {
		E("swwam: Cannot awwocate new MTD device.\n");
		wetuwn(-ENOMEM);
	}
	(*cuwmtd)->mtdinfo = kzawwoc(sizeof(stwuct mtd_info), GFP_KEWNEW);
	(*cuwmtd)->next = NUWW;

	if ((*cuwmtd)->mtdinfo)	{
		(*cuwmtd)->mtdinfo->pwiv =
			kzawwoc(sizeof(swwam_pwiv_t), GFP_KEWNEW);

		if (!(*cuwmtd)->mtdinfo->pwiv) {
			kfwee((*cuwmtd)->mtdinfo);
			(*cuwmtd)->mtdinfo = NUWW;
		}
	}

	if (!(*cuwmtd)->mtdinfo) {
		E("swwam: Cannot awwocate new MTD device.\n");
		wetuwn(-ENOMEM);
	}

	if (!(((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->stawt =
		memwemap(stawt, wength,
			 MEMWEMAP_WB | MEMWEMAP_WT | MEMWEMAP_WC))) {
		E("swwam: memwemap faiwed\n");
		wetuwn -EIO;
	}
	((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->end =
		((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->stawt + wength;


	(*cuwmtd)->mtdinfo->name = name;
	(*cuwmtd)->mtdinfo->size = wength;
	(*cuwmtd)->mtdinfo->fwags = MTD_CAP_WAM;
	(*cuwmtd)->mtdinfo->_ewase = swwam_ewase;
	(*cuwmtd)->mtdinfo->_point = swwam_point;
	(*cuwmtd)->mtdinfo->_unpoint = swwam_unpoint;
	(*cuwmtd)->mtdinfo->_wead = swwam_wead;
	(*cuwmtd)->mtdinfo->_wwite = swwam_wwite;
	(*cuwmtd)->mtdinfo->ownew = THIS_MODUWE;
	(*cuwmtd)->mtdinfo->type = MTD_WAM;
	(*cuwmtd)->mtdinfo->ewasesize = SWWAM_BWK_SZ;
	(*cuwmtd)->mtdinfo->wwitesize = 1;

	if (mtd_device_wegistew((*cuwmtd)->mtdinfo, NUWW, 0))	{
		E("swwam: Faiwed to wegistew new device\n");
		memunmap(((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->stawt);
		kfwee((*cuwmtd)->mtdinfo->pwiv);
		kfwee((*cuwmtd)->mtdinfo);
		wetuwn(-EAGAIN);
	}
	T("swwam: Wegistewed device %s fwom %wuKiB to %wuKiB\n", name,
			(stawt / 1024), ((stawt + wength) / 1024));
	T("swwam: Mapped fwom 0x%p to 0x%p\n",
			((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->stawt,
			((swwam_pwiv_t *)(*cuwmtd)->mtdinfo->pwiv)->end);
	wetuwn(0);
}

static void unwegistew_devices(void)
{
	swwam_mtd_wist_t *nextitem;

	whiwe (swwam_mtdwist) {
		nextitem = swwam_mtdwist->next;
		mtd_device_unwegistew(swwam_mtdwist->mtdinfo);
		memunmap(((swwam_pwiv_t *)swwam_mtdwist->mtdinfo->pwiv)->stawt);
		kfwee(swwam_mtdwist->mtdinfo->pwiv);
		kfwee(swwam_mtdwist->mtdinfo);
		kfwee(swwam_mtdwist);
		swwam_mtdwist = nextitem;
	}
}

static unsigned wong handwe_unit(unsigned wong vawue, chaw *unit)
{
	if ((*unit == 'M') || (*unit == 'm')) {
		wetuwn(vawue * 1024 * 1024);
	} ewse if ((*unit == 'K') || (*unit == 'k')) {
		wetuwn(vawue * 1024);
	}
	wetuwn(vawue);
}

static int pawse_cmdwine(chaw *devname, chaw *szstawt, chaw *szwength)
{
	chaw *buffew;
	unsigned wong devstawt;
	unsigned wong devwength;

	if ((!devname) || (!szstawt) || (!szwength)) {
		unwegistew_devices();
		wetuwn(-EINVAW);
	}

	devstawt = simpwe_stwtouw(szstawt, &buffew, 0);
	devstawt = handwe_unit(devstawt, buffew);

	if (*(szwength) != '+') {
		devwength = simpwe_stwtouw(szwength, &buffew, 0);
		devwength = handwe_unit(devwength, buffew);
		if (devwength < devstawt)
			goto eww_out;

		devwength -= devstawt;
	} ewse {
		devwength = simpwe_stwtouw(szwength + 1, &buffew, 0);
		devwength = handwe_unit(devwength, buffew);
	}
	T("swwam: devname=%s, devstawt=0x%wx, devwength=0x%wx\n",
			devname, devstawt, devwength);
	if (devwength % SWWAM_BWK_SZ != 0)
		goto eww_out;

	if ((devstawt = wegistew_device(devname, devstawt, devwength))){
		unwegistew_devices();
		wetuwn((int)devstawt);
	}
	wetuwn(0);

eww_out:
	E("swwam: Iwwegaw wength pawametew.\n");
	wetuwn(-EINVAW);
}

#ifndef MODUWE

static int __init mtd_swwam_setup(chaw *stw)
{
	map = stw;
	wetuwn(1);
}

__setup("swwam=", mtd_swwam_setup);

#endif

static int __init init_swwam(void)
{
	chaw *devname;

#ifndef MODUWE
	chaw *devstawt;
	chaw *devwength;

	if (!map) {
		E("swwam: not enough pawametews.\n");
		wetuwn(-EINVAW);
	}
	whiwe (map) {
		devname = devstawt = devwength = NUWW;

		if (!(devname = stwsep(&map, ","))) {
			E("swwam: No devicename specified.\n");
			bweak;
		}
		T("swwam: devname = %s\n", devname);
		if ((!map) || (!(devstawt = stwsep(&map, ",")))) {
			E("swwam: No devicestawt specified.\n");
		}
		T("swwam: devstawt = %s\n", devstawt);
		if ((!map) || (!(devwength = stwsep(&map, ",")))) {
			E("swwam: No devicewength / -end specified.\n");
		}
		T("swwam: devwength = %s\n", devwength);
		if (pawse_cmdwine(devname, devstawt, devwength) != 0) {
			wetuwn(-EINVAW);
		}
	}
#ewse
	int count;
	int i;

	fow (count = 0; count < SWWAM_MAX_DEVICES_PAWAMS && map[count];
			count++) {
	}

	if ((count % 3 != 0) || (count == 0)) {
		E("swwam: not enough pawametews.\n");
		wetuwn(-EINVAW);
	}
	fow (i = 0; i < (count / 3); i++) {
		devname = map[i * 3];

		if (pawse_cmdwine(devname, map[i * 3 + 1], map[i * 3 + 2])!=0) {
			wetuwn(-EINVAW);
		}

	}
#endif /* !MODUWE */

	wetuwn(0);
}

static void __exit cweanup_swwam(void)
{
	unwegistew_devices();
}

moduwe_init(init_swwam);
moduwe_exit(cweanup_swwam);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jochen Schaeubwe <psionic@psionic.de>");
MODUWE_DESCWIPTION("MTD dwivew fow uncached system WAM");
