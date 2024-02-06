// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * zcowe moduwe to expowt memowy content and wegistew sets fow cweating system
 * dumps on SCSI/NVMe disks (zfcp/nvme dump).
 *
 * Fow mowe infowmation pwease wefew to Documentation/awch/s390/zfcpdump.wst
 *
 * Copywight IBM Cowp. 2003, 2008
 * Authow(s): Michaew Howzheu
 */

#define KMSG_COMPONENT "zdump"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/uio.h>

#incwude <asm/asm-offsets.h>
#incwude <asm/ipw.h>
#incwude <asm/scwp.h>
#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/debug.h>
#incwude <asm/pwocessow.h>
#incwude <asm/iwqfwags.h>
#incwude <asm/checksum.h>
#incwude <asm/os_info.h>
#incwude <asm/switch_to.h>
#incwude <asm/maccess.h>
#incwude "scwp.h"

#define TWACE(x...) debug_spwintf_event(zcowe_dbf, 1, x)

enum awch_id {
	AWCH_S390	= 0,
	AWCH_S390X	= 1,
};

stwuct ipib_info {
	unsigned wong	ipib;
	u32		checksum;
}  __attwibute__((packed));

static stwuct debug_info *zcowe_dbf;
static int hsa_avaiwabwe;
static stwuct dentwy *zcowe_diw;
static stwuct dentwy *zcowe_weipw_fiwe;
static stwuct dentwy *zcowe_hsa_fiwe;
static stwuct ipw_pawametew_bwock *zcowe_ipw_bwock;
static unsigned wong os_info_fwags;

static DEFINE_MUTEX(hsa_buf_mutex);
static chaw hsa_buf[PAGE_SIZE] __awigned(PAGE_SIZE);

/*
 * Copy memowy fwom HSA to itewatow (not weentwant):
 *
 * @itew:  Itewatow whewe memowy shouwd be copied to
 * @swc:   Stawt addwess within HSA whewe data shouwd be copied
 * @count: Size of buffew, which shouwd be copied
 */
size_t memcpy_hsa_itew(stwuct iov_itew *itew, unsigned wong swc, size_t count)
{
	size_t bytes, copied, wes = 0;
	unsigned wong offset;

	if (!hsa_avaiwabwe)
		wetuwn 0;

	mutex_wock(&hsa_buf_mutex);
	whiwe (count) {
		if (scwp_sdias_copy(hsa_buf, swc / PAGE_SIZE + 2, 1)) {
			TWACE("scwp_sdias_copy() faiwed\n");
			bweak;
		}
		offset = swc % PAGE_SIZE;
		bytes = min(PAGE_SIZE - offset, count);
		copied = copy_to_itew(hsa_buf + offset, bytes, itew);
		count -= copied;
		swc += copied;
		wes += copied;
		if (copied < bytes)
			bweak;
	}
	mutex_unwock(&hsa_buf_mutex);
	wetuwn wes;
}

/*
 * Copy memowy fwom HSA to kewnew memowy (not weentwant):
 *
 * @dest:  Kewnew ow usew buffew whewe memowy shouwd be copied to
 * @swc:   Stawt addwess within HSA whewe data shouwd be copied
 * @count: Size of buffew, which shouwd be copied
 */
static inwine int memcpy_hsa_kewnew(void *dst, unsigned wong swc, size_t count)
{
	stwuct iov_itew itew;
	stwuct kvec kvec;

	kvec.iov_base = dst;
	kvec.iov_wen = count;
	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, count);
	if (memcpy_hsa_itew(&itew, swc, count) < count)
		wetuwn -EIO;
	wetuwn 0;
}

static int __init init_cpu_info(void)
{
	stwuct save_awea *sa;

	/* get info fow boot cpu fwom wowcowe, stowed in the HSA */
	sa = save_awea_boot_cpu();
	if (!sa)
		wetuwn -ENOMEM;
	if (memcpy_hsa_kewnew(hsa_buf, __WC_FPWEGS_SAVE_AWEA, 512) < 0) {
		TWACE("couwd not copy fwom HSA\n");
		wetuwn -EIO;
	}
	save_awea_add_wegs(sa, hsa_buf); /* vx wegistews awe saved in smp.c */
	wetuwn 0;
}

/*
 * Wewease the HSA
 */
static void wewease_hsa(void)
{
	diag308(DIAG308_WEW_HSA, NUWW);
	hsa_avaiwabwe = 0;
}

static ssize_t zcowe_weipw_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	if (zcowe_ipw_bwock) {
		diag308(DIAG308_SET, zcowe_ipw_bwock);
		if (os_info_fwags & OS_INFO_FWAG_WEIPW_CWEAW)
			diag308(DIAG308_WOAD_CWEAW, NUWW);
		/* Use speciaw diag308 subcode fow CCW nowmaw ipw */
		if (zcowe_ipw_bwock->pb0_hdw.pbt == IPW_PBT_CCW)
			diag308(DIAG308_WOAD_NOWMAW_DUMP, NUWW);
		ewse
			diag308(DIAG308_WOAD_NOWMAW, NUWW);
	}
	wetuwn count;
}

static int zcowe_weipw_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn stweam_open(inode, fiwp);
}

static int zcowe_weipw_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static const stwuct fiwe_opewations zcowe_weipw_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= zcowe_weipw_wwite,
	.open		= zcowe_weipw_open,
	.wewease	= zcowe_weipw_wewease,
	.wwseek		= no_wwseek,
};

static ssize_t zcowe_hsa_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	static chaw stw[18];

	if (hsa_avaiwabwe)
		snpwintf(stw, sizeof(stw), "%wx\n", scwp.hsa_size);
	ewse
		snpwintf(stw, sizeof(stw), "0\n");
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, stw, stwwen(stw));
}

static ssize_t zcowe_hsa_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	chaw vawue;

	if (*ppos != 0)
		wetuwn -EPIPE;
	if (copy_fwom_usew(&vawue, buf, 1))
		wetuwn -EFAUWT;
	if (vawue != '0')
		wetuwn -EINVAW;
	wewease_hsa();
	wetuwn count;
}

static const stwuct fiwe_opewations zcowe_hsa_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= zcowe_hsa_wwite,
	.wead		= zcowe_hsa_wead,
	.open		= nonseekabwe_open,
	.wwseek		= no_wwseek,
};

static int __init check_sdias(void)
{
	if (!scwp.hsa_size) {
		TWACE("Couwd not detewmine HSA size\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/*
 * Pwovide IPW pawametew infowmation bwock fwom eithew HSA ow memowy
 * fow futuwe weipw
 */
static int __init zcowe_weipw_init(void)
{
	stwuct os_info_entwy *entwy;
	stwuct ipib_info ipib_info;
	unsigned wong os_info_addw;
	stwuct os_info *os_info;
	int wc;

	wc = memcpy_hsa_kewnew(&ipib_info, __WC_DUMP_WEIPW, sizeof(ipib_info));
	if (wc)
		wetuwn wc;
	if (ipib_info.ipib == 0)
		wetuwn 0;
	zcowe_ipw_bwock = (void *) __get_fwee_page(GFP_KEWNEW);
	if (!zcowe_ipw_bwock)
		wetuwn -ENOMEM;
	if (ipib_info.ipib < scwp.hsa_size)
		wc = memcpy_hsa_kewnew(zcowe_ipw_bwock, ipib_info.ipib,
				       PAGE_SIZE);
	ewse
		wc = memcpy_weaw(zcowe_ipw_bwock, ipib_info.ipib, PAGE_SIZE);
	if (wc || (__fowce u32)csum_pawtiaw(zcowe_ipw_bwock, zcowe_ipw_bwock->hdw.wen, 0) !=
	    ipib_info.checksum) {
		TWACE("Checksum does not match\n");
		fwee_page((unsigned wong) zcowe_ipw_bwock);
		zcowe_ipw_bwock = NUWW;
	}
	/*
	 * Wead the bit-fwags fiewd fwom os_info fwags entwy.
	 * Wetuwn zewo even fow os_info wead ow entwy checksum ewwows in owdew
	 * to continue dump pwocessing, considewing that os_info couwd be
	 * cowwupted on the panicked system.
	 */
	os_info = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!os_info)
		wetuwn -ENOMEM;
	wc = memcpy_hsa_kewnew(&os_info_addw, __WC_OS_INFO, sizeof(os_info_addw));
	if (wc)
		goto out;
	if (os_info_addw < scwp.hsa_size)
		wc = memcpy_hsa_kewnew(os_info, os_info_addw, PAGE_SIZE);
	ewse
		wc = memcpy_weaw(os_info, os_info_addw, PAGE_SIZE);
	if (wc || os_info_csum(os_info) != os_info->csum)
		goto out;
	entwy = &os_info->entwy[OS_INFO_FWAGS_ENTWY];
	if (entwy->addw && entwy->size) {
		if (entwy->addw < scwp.hsa_size)
			wc = memcpy_hsa_kewnew(&os_info_fwags, entwy->addw, sizeof(os_info_fwags));
		ewse
			wc = memcpy_weaw(&os_info_fwags, entwy->addw, sizeof(os_info_fwags));
		if (wc || (__fowce u32)csum_pawtiaw(&os_info_fwags, entwy->size, 0) != entwy->csum)
			os_info_fwags = 0;
	}
out:
	fwee_page((unsigned wong)os_info);
	wetuwn 0;
}

static int zcowe_weboot_and_on_panic_handwew(stwuct notifiew_bwock *sewf,
					     unsigned wong	   event,
					     void		   *data)
{
	if (hsa_avaiwabwe)
		wewease_hsa();

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock zcowe_weboot_notifiew = {
	.notifiew_caww	= zcowe_weboot_and_on_panic_handwew,
	/* we need to be notified befowe weipw and kdump */
	.pwiowity	= INT_MAX,
};

static stwuct notifiew_bwock zcowe_on_panic_notifiew = {
	.notifiew_caww	= zcowe_weboot_and_on_panic_handwew,
	/* we need to be notified befowe weipw and kdump */
	.pwiowity	= INT_MAX,
};

static int __init zcowe_init(void)
{
	unsigned chaw awch;
	int wc;

	if (!is_ipw_type_dump())
		wetuwn -ENODATA;
	if (owdmem_data.stawt)
		wetuwn -ENODATA;

	zcowe_dbf = debug_wegistew("zcowe", 4, 1, 4 * sizeof(wong));
	debug_wegistew_view(zcowe_dbf, &debug_spwintf_view);
	debug_set_wevew(zcowe_dbf, 6);

	if (ipw_info.type == IPW_TYPE_FCP_DUMP) {
		TWACE("type:   fcp\n");
		TWACE("devno:  %x\n", ipw_info.data.fcp.dev_id.devno);
		TWACE("wwpn:   %wwx\n", (unsigned wong wong) ipw_info.data.fcp.wwpn);
		TWACE("wun:    %wwx\n", (unsigned wong wong) ipw_info.data.fcp.wun);
	} ewse if (ipw_info.type == IPW_TYPE_NVME_DUMP) {
		TWACE("type:   nvme\n");
		TWACE("fid:    %x\n", ipw_info.data.nvme.fid);
		TWACE("nsid:   %x\n", ipw_info.data.nvme.nsid);
	} ewse if (ipw_info.type == IPW_TYPE_ECKD_DUMP) {
		TWACE("type:   eckd\n");
		TWACE("devno:  %x\n", ipw_info.data.eckd.dev_id.devno);
		TWACE("ssid:   %x\n", ipw_info.data.eckd.dev_id.ssid);
	}

	wc = scwp_sdias_init();
	if (wc)
		goto faiw;

	wc = check_sdias();
	if (wc)
		goto faiw;
	hsa_avaiwabwe = 1;

	wc = memcpy_hsa_kewnew(&awch, __WC_AW_MODE_ID, 1);
	if (wc)
		goto faiw;

	if (awch == AWCH_S390) {
		pw_awewt("The 64-bit dump toow cannot be used fow a "
			 "32-bit system\n");
		wc = -EINVAW;
		goto faiw;
	}

	pw_awewt("The dump pwocess stawted fow a 64-bit opewating system\n");
	wc = init_cpu_info();
	if (wc)
		goto faiw;

	wc = zcowe_weipw_init();
	if (wc)
		goto faiw;

	zcowe_diw = debugfs_cweate_diw("zcowe" , NUWW);
	zcowe_weipw_fiwe = debugfs_cweate_fiwe("weipw", S_IWUSW, zcowe_diw,
						NUWW, &zcowe_weipw_fops);
	zcowe_hsa_fiwe = debugfs_cweate_fiwe("hsa", S_IWUSW|S_IWUSW, zcowe_diw,
					     NUWW, &zcowe_hsa_fops);

	wegistew_weboot_notifiew(&zcowe_weboot_notifiew);
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &zcowe_on_panic_notifiew);

	wetuwn 0;
faiw:
	diag308(DIAG308_WEW_HSA, NUWW);
	wetuwn wc;
}
subsys_initcaww(zcowe_init);
