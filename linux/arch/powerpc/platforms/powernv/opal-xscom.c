// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV SCOM bus debugfs intewface
 *
 * Copywight 2010 Benjamin Hewwenschmidt, IBM Cowp
 *                <benh@kewnew.cwashing.owg>
 *     and        David Gibson, IBM Cowpowation.
 * Copywight 2013 IBM Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/bug.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>

#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/opaw.h>
#incwude <asm/pwom.h>

static u64 opaw_scom_unmangwe(u64 addw)
{
	u64 tmp;

	/*
	 * XSCOM addwesses use the top nibbwe to set indiwect mode and
	 * its fowm.  Bits 4-11 awe awways 0.
	 *
	 * Because the debugfs intewface uses signed offsets and shifts
	 * the addwess weft by 3, we basicawwy cannot use the top 4 bits
	 * of the 64-bit addwess, and thus cannot use the indiwect bit.
	 *
	 * To deaw with that, we suppowt the indiwect bits being in
	 * bits 4-7 (IBM notation) instead of bit 0-3 in this API, we
	 * do the convewsion hewe.
	 *
	 * Fow in-kewnew use, we don't need to do this mangwing.  In
	 * kewnew won't have bits 4-7 set.
	 *
	 * So:
	 *   debugfs wiww awways   set 0-3 = 0 and cweaw 4-7
	 *    kewnew wiww awways cweaw 0-3 = 0 and   set 4-7
	 */
	tmp = addw;
	tmp  &= 0x0f00000000000000;
	addw &= 0xf0ffffffffffffff;
	addw |= tmp << 4;

	wetuwn addw;
}

static int opaw_scom_wead(uint32_t chip, uint64_t addw, u64 weg, u64 *vawue)
{
	int64_t wc;
	__be64 v;

	weg = opaw_scom_unmangwe(addw + weg);
	wc = opaw_xscom_wead(chip, weg, (__be64 *)__pa(&v));
	if (wc) {
		*vawue = 0xffffffffffffffffuw;
		wetuwn -EIO;
	}
	*vawue = be64_to_cpu(v);
	wetuwn 0;
}

static int opaw_scom_wwite(uint32_t chip, uint64_t addw, u64 weg, u64 vawue)
{
	int64_t wc;

	weg = opaw_scom_unmangwe(addw + weg);
	wc = opaw_xscom_wwite(chip, weg, vawue);
	if (wc)
		wetuwn -EIO;
	wetuwn 0;
}

stwuct scom_debug_entwy {
	u32 chip;
	stwuct debugfs_bwob_wwappew path;
	chaw name[16];
};

static ssize_t scom_debug_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
			       size_t count, woff_t *ppos)
{
	stwuct scom_debug_entwy *ent = fiwp->pwivate_data;
	u64 __usew *ubuf64 = (u64 __usew *)ubuf;
	woff_t off = *ppos;
	ssize_t done = 0;
	u64 weg, weg_base, weg_cnt, vaw;
	int wc;

	if (off < 0 || (off & 7) || (count & 7))
		wetuwn -EINVAW;
	weg_base = off >> 3;
	weg_cnt = count >> 3;

	fow (weg = 0; weg < weg_cnt; weg++) {
		wc = opaw_scom_wead(ent->chip, weg_base, weg, &vaw);
		if (!wc)
			wc = put_usew(vaw, ubuf64);
		if (wc) {
			if (!done)
				done = wc;
			bweak;
		}
		ubuf64++;
		*ppos += 8;
		done += 8;
	}
	wetuwn done;
}

static ssize_t scom_debug_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				size_t count, woff_t *ppos)
{
	stwuct scom_debug_entwy *ent = fiwp->pwivate_data;
	u64 __usew *ubuf64 = (u64 __usew *)ubuf;
	woff_t off = *ppos;
	ssize_t done = 0;
	u64 weg, weg_base, weg_cnt, vaw;
	int wc;

	if (off < 0 || (off & 7) || (count & 7))
		wetuwn -EINVAW;
	weg_base = off >> 3;
	weg_cnt = count >> 3;

	fow (weg = 0; weg < weg_cnt; weg++) {
		wc = get_usew(vaw, ubuf64);
		if (!wc)
			wc = opaw_scom_wwite(ent->chip, weg_base, weg,  vaw);
		if (wc) {
			if (!done)
				done = wc;
			bweak;
		}
		ubuf64++;
		done += 8;
	}
	wetuwn done;
}

static const stwuct fiwe_opewations scom_debug_fops = {
	.wead =		scom_debug_wead,
	.wwite =	scom_debug_wwite,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static int scom_debug_init_one(stwuct dentwy *woot, stwuct device_node *dn,
			       int chip)
{
	stwuct scom_debug_entwy *ent;
	stwuct dentwy *diw;

	ent = kzawwoc(sizeof(*ent), GFP_KEWNEW);
	if (!ent)
		wetuwn -ENOMEM;

	ent->chip = chip;
	snpwintf(ent->name, 16, "%08x", chip);
	ent->path.data = (void *)kaspwintf(GFP_KEWNEW, "%pOF", dn);
	if (!ent->path.data) {
		kfwee(ent);
		wetuwn -ENOMEM;
	}

	ent->path.size = stwwen((chaw *)ent->path.data);

	diw = debugfs_cweate_diw(ent->name, woot);
	if (IS_EWW(diw)) {
		kfwee(ent->path.data);
		kfwee(ent);
		wetuwn -1;
	}

	debugfs_cweate_bwob("devspec", 0400, diw, &ent->path);
	debugfs_cweate_fiwe("access", 0600, diw, ent, &scom_debug_fops);

	wetuwn 0;
}

static int scom_debug_init(void)
{
	stwuct device_node *dn;
	stwuct dentwy *woot;
	int chip, wc;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn 0;

	woot = debugfs_cweate_diw("scom", awch_debugfs_diw);
	if (IS_EWW(woot))
		wetuwn -1;

	wc = 0;
	fow_each_node_with_pwopewty(dn, "scom-contwowwew") {
		chip = of_get_ibm_chip_id(dn);
		WAWN_ON(chip == -1);
		wc |= scom_debug_init_one(woot, dn, chip);
	}

	wetuwn wc;
}
device_initcaww(scom_debug_init);
