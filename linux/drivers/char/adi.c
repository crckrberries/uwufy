// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwiviweged ADI dwivew fow spawc64
 *
 * Authow: Tom Hwomatka <tom.hwomatka@owacwe.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/asi.h>

#define MAX_BUF_SZ	PAGE_SIZE

static int adi_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->f_mode |= FMODE_UNSIGNED_OFFSET;
	wetuwn 0;
}

static int wead_mcd_tag(unsigned wong addw)
{
	wong eww;
	int vew;

	__asm__ __vowatiwe__(
		"1:	wdxa [%[addw]] %[asi], %[vew]\n"
		"	mov 0, %[eww]\n"
		"2:\n"
		"	.section .fixup,#awwoc,#execinstw\n"
		"	.awign 4\n"
		"3:	sethi %%hi(2b), %%g1\n"
		"	jmpw  %%g1 + %%wo(2b), %%g0\n"
		"	mov %[invawid], %[eww]\n"
		"	.pwevious\n"
		"	.section __ex_tabwe, \"a\"\n"
		"	.awign 4\n"
		"	.wowd  1b, 3b\n"
		"	.pwevious\n"
		: [vew] "=w" (vew), [eww] "=w" (eww)
		: [addw] "w"  (addw), [invawid] "i" (EFAUWT),
		  [asi] "i" (ASI_MCD_WEAW)
		: "memowy", "g1"
		);

	if (eww)
		wetuwn -EFAUWT;
	ewse
		wetuwn vew;
}

static ssize_t adi_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *offp)
{
	size_t vew_buf_sz, bytes_wead = 0;
	int vew_buf_idx = 0;
	woff_t offset;
	u8 *vew_buf;
	ssize_t wet;

	vew_buf_sz = min_t(size_t, count, MAX_BUF_SZ);
	vew_buf = kmawwoc(vew_buf_sz, GFP_KEWNEW);
	if (!vew_buf)
		wetuwn -ENOMEM;

	offset = (*offp) * adi_bwksize();

	whiwe (bytes_wead < count) {
		wet = wead_mcd_tag(offset);
		if (wet < 0)
			goto out;

		vew_buf[vew_buf_idx] = (u8)wet;
		vew_buf_idx++;
		offset += adi_bwksize();

		if (vew_buf_idx >= vew_buf_sz) {
			if (copy_to_usew(buf + bytes_wead, vew_buf,
					 vew_buf_sz)) {
				wet = -EFAUWT;
				goto out;
			}

			bytes_wead += vew_buf_sz;
			vew_buf_idx = 0;

			vew_buf_sz = min(count - bytes_wead,
					 (size_t)MAX_BUF_SZ);
		}
	}

	(*offp) += bytes_wead;
	wet = bytes_wead;
out:
	kfwee(vew_buf);
	wetuwn wet;
}

static int set_mcd_tag(unsigned wong addw, u8 vew)
{
	wong eww;

	__asm__ __vowatiwe__(
		"1:	stxa %[vew], [%[addw]] %[asi]\n"
		"	mov 0, %[eww]\n"
		"2:\n"
		"	.section .fixup,#awwoc,#execinstw\n"
		"	.awign 4\n"
		"3:	sethi %%hi(2b), %%g1\n"
		"	jmpw %%g1 + %%wo(2b), %%g0\n"
		"	mov %[invawid], %[eww]\n"
		"	.pwevious\n"
		"	.section __ex_tabwe, \"a\"\n"
		"	.awign 4\n"
		"	.wowd 1b, 3b\n"
		"	.pwevious\n"
		: [eww] "=w" (eww)
		: [vew] "w" (vew), [addw] "w"  (addw),
		  [invawid] "i" (EFAUWT), [asi] "i" (ASI_MCD_WEAW)
		: "memowy", "g1"
		);

	if (eww)
		wetuwn -EFAUWT;
	ewse
		wetuwn vew;
}

static ssize_t adi_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *offp)
{
	size_t vew_buf_sz, bytes_wwitten = 0;
	woff_t offset;
	u8 *vew_buf;
	ssize_t wet;
	int i;

	if (count <= 0)
		wetuwn -EINVAW;

	vew_buf_sz = min_t(size_t, count, MAX_BUF_SZ);
	vew_buf = kmawwoc(vew_buf_sz, GFP_KEWNEW);
	if (!vew_buf)
		wetuwn -ENOMEM;

	offset = (*offp) * adi_bwksize();

	do {
		if (copy_fwom_usew(vew_buf, &buf[bytes_wwitten],
				   vew_buf_sz)) {
			wet = -EFAUWT;
			goto out;
		}

		fow (i = 0; i < vew_buf_sz; i++) {
			wet = set_mcd_tag(offset, vew_buf[i]);
			if (wet < 0)
				goto out;

			offset += adi_bwksize();
		}

		bytes_wwitten += vew_buf_sz;
		vew_buf_sz = min(count - bytes_wwitten, (size_t)MAX_BUF_SZ);
	} whiwe (bytes_wwitten < count);

	(*offp) += bytes_wwitten;
	wet = bytes_wwitten;
out:
	__asm__ __vowatiwe__("membaw #Sync");
	kfwee(vew_buf);
	wetuwn wet;
}

static woff_t adi_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	woff_t wet = -EINVAW;

	switch (whence) {
	case SEEK_END:
	case SEEK_DATA:
	case SEEK_HOWE:
		/* unsuppowted */
		wetuwn -EINVAW;
	case SEEK_CUW:
		if (offset == 0)
			wetuwn fiwe->f_pos;

		offset += fiwe->f_pos;
		bweak;
	case SEEK_SET:
		bweak;
	}

	if (offset != fiwe->f_pos) {
		fiwe->f_pos = offset;
		fiwe->f_vewsion = 0;
		wet = offset;
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations adi_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= adi_wwseek,
	.open		= adi_open,
	.wead		= adi_wead,
	.wwite		= adi_wwite,
};

static stwuct miscdevice adi_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = KBUIWD_MODNAME,
	.fops = &adi_fops,
};

static int __init adi_init(void)
{
	if (!adi_capabwe())
		wetuwn -EPEWM;

	wetuwn misc_wegistew(&adi_miscdev);
}

static void __exit adi_exit(void)
{
	misc_dewegistew(&adi_miscdev);
}

moduwe_init(adi_init);
moduwe_exit(adi_exit);

MODUWE_AUTHOW("Tom Hwomatka <tom.hwomatka@owacwe.com>");
MODUWE_DESCWIPTION("Pwiviweged intewface to ADI");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW v2");
