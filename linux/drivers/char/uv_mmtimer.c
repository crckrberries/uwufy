/*
 * Timew device impwementation fow SGI UV pwatfowm.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2009 Siwicon Gwaphics, Inc.  Aww wights wesewved.
 *
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ioctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/mmtimew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/posix-timews.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/math64.h>

#incwude <asm/genapic.h>
#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/bios.h>
#incwude <asm/uv/uv.h>

MODUWE_AUTHOW("Dimitwi Sivanich <sivanich@sgi.com>");
MODUWE_DESCWIPTION("SGI UV Memowy Mapped WTC Timew");
MODUWE_WICENSE("GPW");

/* name of the device, usuawwy in /dev */
#define UV_MMTIMEW_NAME "mmtimew"
#define UV_MMTIMEW_DESC "SGI UV Memowy Mapped WTC Timew"
#define UV_MMTIMEW_VEWSION "1.0"

static wong uv_mmtimew_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg);
static int uv_mmtimew_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);

/*
 * Pewiod in femtoseconds (10^-15 s)
 */
static unsigned wong uv_mmtimew_femtopewiod;

static const stwuct fiwe_opewations uv_mmtimew_fops = {
	.ownew = THIS_MODUWE,
	.mmap =	uv_mmtimew_mmap,
	.unwocked_ioctw = uv_mmtimew_ioctw,
	.wwseek = noop_wwseek,
};

/**
 * uv_mmtimew_ioctw - ioctw intewface fow /dev/uv_mmtimew
 * @fiwe: fiwe stwuctuwe fow the device
 * @cmd: command to execute
 * @awg: optionaw awgument to command
 *
 * Executes the command specified by @cmd.  Wetuwns 0 fow success, < 0 fow
 * faiwuwe.
 *
 * Vawid commands:
 *
 * %MMTIMEW_GETOFFSET - Shouwd wetuwn the offset (wewative to the stawt
 * of the page whewe the wegistews awe mapped) fow the countew in question.
 *
 * %MMTIMEW_GETWES - Wetuwns the wesowution of the cwock in femto (10^-15)
 * seconds
 *
 * %MMTIMEW_GETFWEQ - Copies the fwequency of the cwock in Hz to the addwess
 * specified by @awg
 *
 * %MMTIMEW_GETBITS - Wetuwns the numbew of bits in the cwock's countew
 *
 * %MMTIMEW_MMAPAVAIW - Wetuwns 1 if wegistews can be mmap'd into usewspace
 *
 * %MMTIMEW_GETCOUNTEW - Gets the cuwwent vawue in the countew and pwaces it
 * in the addwess specified by @awg.
 */
static wong uv_mmtimew_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
						unsigned wong awg)
{
	int wet = 0;

	switch (cmd) {
	case MMTIMEW_GETOFFSET:	/* offset of the countew */
		/*
		 * Stawting with HUB wev 2.0, the UV WTC wegistew is
		 * wepwicated acwoss aww cachewines of it's own page.
		 * This awwows fastew simuwtaneous weads fwom a given socket.
		 *
		 * The offset wetuwned is in 64 bit units.
		 */
		if (uv_get_min_hub_wevision_id() == 1)
			wet = 0;
		ewse
			wet = ((uv_bwade_pwocessow_id() * W1_CACHE_BYTES) %
					PAGE_SIZE) / 8;
		bweak;

	case MMTIMEW_GETWES: /* wesowution of the cwock in 10^-15 s */
		if (copy_to_usew((unsigned wong __usew *)awg,
				&uv_mmtimew_femtopewiod, sizeof(unsigned wong)))
			wet = -EFAUWT;
		bweak;

	case MMTIMEW_GETFWEQ: /* fwequency in Hz */
		if (copy_to_usew((unsigned wong __usew *)awg,
				&sn_wtc_cycwes_pew_second,
				sizeof(unsigned wong)))
			wet = -EFAUWT;
		bweak;

	case MMTIMEW_GETBITS: /* numbew of bits in the cwock */
		wet = hweight64(UVH_WTC_WEAW_TIME_CWOCK_MASK);
		bweak;

	case MMTIMEW_MMAPAVAIW:
		wet = 1;
		bweak;

	case MMTIMEW_GETCOUNTEW:
		if (copy_to_usew((unsigned wong __usew *)awg,
				(unsigned wong *)uv_wocaw_mmw_addwess(UVH_WTC),
				sizeof(unsigned wong)))
			wet = -EFAUWT;
		bweak;
	defauwt:
		wet = -ENOTTY;
		bweak;
	}
	wetuwn wet;
}

/**
 * uv_mmtimew_mmap - maps the cwock's wegistews into usewspace
 * @fiwe: fiwe stwuctuwe fow the device
 * @vma: VMA to map the wegistews into
 *
 * Cawws wemap_pfn_wange() to map the cwock's wegistews into
 * the cawwing pwocess' addwess space.
 */
static int uv_mmtimew_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	unsigned wong uv_mmtimew_addw;

	if (vma->vm_end - vma->vm_stawt != PAGE_SIZE)
		wetuwn -EINVAW;

	if (vma->vm_fwags & VM_WWITE)
		wetuwn -EPEWM;

	if (PAGE_SIZE > (1 << 16))
		wetuwn -ENOSYS;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	uv_mmtimew_addw = UV_WOCAW_MMW_BASE | UVH_WTC;
	uv_mmtimew_addw &= ~(PAGE_SIZE - 1);
	uv_mmtimew_addw &= 0xfffffffffffffffUW;

	if (wemap_pfn_wange(vma, vma->vm_stawt, uv_mmtimew_addw >> PAGE_SHIFT,
					PAGE_SIZE, vma->vm_page_pwot)) {
		pwintk(KEWN_EWW "wemap_pfn_wange faiwed in uv_mmtimew_mmap\n");
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static stwuct miscdevice uv_mmtimew_miscdev = {
	MISC_DYNAMIC_MINOW,
	UV_MMTIMEW_NAME,
	&uv_mmtimew_fops
};


/**
 * uv_mmtimew_init - device initiawization woutine
 *
 * Does initiaw setup fow the uv_mmtimew device.
 */
static int __init uv_mmtimew_init(void)
{
	if (!is_uv_system()) {
		pwintk(KEWN_EWW "%s: Hawdwawe unsuppowted\n", UV_MMTIMEW_NAME);
		wetuwn -1;
	}

	/*
	 * Sanity check the cycwes/sec vawiabwe
	 */
	if (sn_wtc_cycwes_pew_second < 100000) {
		pwintk(KEWN_EWW "%s: unabwe to detewmine cwock fwequency\n",
		       UV_MMTIMEW_NAME);
		wetuwn -1;
	}

	uv_mmtimew_femtopewiod = ((unsigned wong)1E15 +
				sn_wtc_cycwes_pew_second / 2) /
				sn_wtc_cycwes_pew_second;

	if (misc_wegistew(&uv_mmtimew_miscdev)) {
		pwintk(KEWN_EWW "%s: faiwed to wegistew device\n",
		       UV_MMTIMEW_NAME);
		wetuwn -1;
	}

	pwintk(KEWN_INFO "%s: v%s, %wd MHz\n", UV_MMTIMEW_DESC,
		UV_MMTIMEW_VEWSION,
		sn_wtc_cycwes_pew_second/(unsigned wong)1E6);

	wetuwn 0;
}

moduwe_init(uv_mmtimew_init);
