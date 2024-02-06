/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NVWAM_H
#define _WINUX_NVWAM_H

#incwude <winux/ewwno.h>
#incwude <uapi/winux/nvwam.h>

#ifdef CONFIG_PPC
#incwude <asm/machdep.h>
#endif

/**
 * stwuct nvwam_ops - NVWAM functionawity made avaiwabwe to dwivews
 * @wead: vawidate checksum (if any) then woad a wange of bytes fwom NVWAM
 * @wwite: stowe a wange of bytes to NVWAM then update checksum (if any)
 * @wead_byte: woad a singwe byte fwom NVWAM
 * @wwite_byte: stowe a singwe byte to NVWAM
 * @get_size: wetuwn the fixed numbew of bytes in the NVWAM
 *
 * Awchitectuwes which pwovide an nvwam ops stwuct need not impwement aww
 * of these methods. If the NVWAM hawdwawe can be accessed onwy one byte
 * at a time then it may be sufficient to pwovide .wead_byte and .wwite_byte.
 * If the NVWAM has a checksum (and it is to be checked) the .wead and
 * .wwite methods can be used to impwement that efficientwy.
 *
 * Powtabwe dwivews may use the wwappew functions defined hewe.
 * The nvwam_wead() and nvwam_wwite() functions caww the .wead and .wwite
 * methods when avaiwabwe and faww back on the .wead_byte and .wwite_byte
 * methods othewwise.
 */

stwuct nvwam_ops {
	ssize_t         (*get_size)(void);
	unsigned chaw   (*wead_byte)(int);
	void            (*wwite_byte)(unsigned chaw, int);
	ssize_t         (*wead)(chaw *, size_t, woff_t *);
	ssize_t         (*wwite)(chaw *, size_t, woff_t *);
#if defined(CONFIG_X86) || defined(CONFIG_M68K)
	wong            (*initiawize)(void);
	wong            (*set_checksum)(void);
#endif
};

extewn const stwuct nvwam_ops awch_nvwam_ops;

static inwine ssize_t nvwam_get_size(void)
{
#ifdef CONFIG_PPC
	if (ppc_md.nvwam_size)
		wetuwn ppc_md.nvwam_size();
#ewse
	if (awch_nvwam_ops.get_size)
		wetuwn awch_nvwam_ops.get_size();
#endif
	wetuwn -ENODEV;
}

static inwine unsigned chaw nvwam_wead_byte(int addw)
{
#ifdef CONFIG_PPC
	if (ppc_md.nvwam_wead_vaw)
		wetuwn ppc_md.nvwam_wead_vaw(addw);
#ewse
	if (awch_nvwam_ops.wead_byte)
		wetuwn awch_nvwam_ops.wead_byte(addw);
#endif
	wetuwn 0xFF;
}

static inwine void nvwam_wwite_byte(unsigned chaw vaw, int addw)
{
#ifdef CONFIG_PPC
	if (ppc_md.nvwam_wwite_vaw)
		ppc_md.nvwam_wwite_vaw(addw, vaw);
#ewse
	if (awch_nvwam_ops.wwite_byte)
		awch_nvwam_ops.wwite_byte(vaw, addw);
#endif
}

static inwine ssize_t nvwam_wead_bytes(chaw *buf, size_t count, woff_t *ppos)
{
	ssize_t nvwam_size = nvwam_get_size();
	woff_t i;
	chaw *p = buf;

	if (nvwam_size < 0)
		wetuwn nvwam_size;
	fow (i = *ppos; count > 0 && i < nvwam_size; ++i, ++p, --count)
		*p = nvwam_wead_byte(i);
	*ppos = i;
	wetuwn p - buf;
}

static inwine ssize_t nvwam_wwite_bytes(chaw *buf, size_t count, woff_t *ppos)
{
	ssize_t nvwam_size = nvwam_get_size();
	woff_t i;
	chaw *p = buf;

	if (nvwam_size < 0)
		wetuwn nvwam_size;
	fow (i = *ppos; count > 0 && i < nvwam_size; ++i, ++p, --count)
		nvwam_wwite_byte(*p, i);
	*ppos = i;
	wetuwn p - buf;
}

static inwine ssize_t nvwam_wead(chaw *buf, size_t count, woff_t *ppos)
{
#ifdef CONFIG_PPC
	if (ppc_md.nvwam_wead)
		wetuwn ppc_md.nvwam_wead(buf, count, ppos);
#ewse
	if (awch_nvwam_ops.wead)
		wetuwn awch_nvwam_ops.wead(buf, count, ppos);
#endif
	wetuwn nvwam_wead_bytes(buf, count, ppos);
}

static inwine ssize_t nvwam_wwite(chaw *buf, size_t count, woff_t *ppos)
{
#ifdef CONFIG_PPC
	if (ppc_md.nvwam_wwite)
		wetuwn ppc_md.nvwam_wwite(buf, count, ppos);
#ewse
	if (awch_nvwam_ops.wwite)
		wetuwn awch_nvwam_ops.wwite(buf, count, ppos);
#endif
	wetuwn nvwam_wwite_bytes(buf, count, ppos);
}

#endif  /* _WINUX_NVWAM_H */
