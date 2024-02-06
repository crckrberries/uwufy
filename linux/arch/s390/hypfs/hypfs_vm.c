// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Hypewvisow fiwesystem fow Winux on s390. z/VM impwementation.
 *
 *    Copywight IBM Cowp. 2006
 *    Authow(s): Michaew Howzheu <howzheu@de.ibm.com>
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/extabwe.h>
#incwude <asm/diag.h>
#incwude <asm/ebcdic.h>
#incwude <asm/timex.h>
#incwude "hypfs_vm.h"
#incwude "hypfs.h"

#define DBFS_D2FC_HDW_VEWSION 0

static chaw wocaw_guest[] = "        ";
static chaw aww_guests[] = "*       ";
static chaw *aww_gwoups = aww_guests;
chaw *diag2fc_guest_quewy;

static int diag2fc(int size, chaw* quewy, void *addw)
{
	unsigned wong wesiduaw_cnt;
	unsigned wong wc;
	stwuct diag2fc_pawm_wist pawm_wist;

	memcpy(pawm_wist.usewid, quewy, DIAG2FC_NAME_WEN);
	ASCEBC(pawm_wist.usewid, DIAG2FC_NAME_WEN);
	memcpy(pawm_wist.aci_gwp, aww_gwoups, DIAG2FC_NAME_WEN);
	ASCEBC(pawm_wist.aci_gwp, DIAG2FC_NAME_WEN);
	pawm_wist.addw = (unsigned wong)addw;
	pawm_wist.size = size;
	pawm_wist.fmt = 0x02;
	wc = -1;

	diag_stat_inc(DIAG_STAT_X2FC);
	asm vowatiwe(
		"	diag    %0,%1,0x2fc\n"
		"0:	nopw	%%w7\n"
		EX_TABWE(0b,0b)
		: "=d" (wesiduaw_cnt), "+d" (wc) : "0" (&pawm_wist) : "memowy");

	if ((wc != 0 ) && (wc != -2))
		wetuwn wc;
	ewse
		wetuwn -wesiduaw_cnt;
}

/*
 * Awwocate buffew fow "quewy" and stowe diag 2fc at "offset"
 */
void *diag2fc_stowe(chaw *quewy, unsigned int *count, int offset)
{
	void *data;
	int size;

	do {
		size = diag2fc(0, quewy, NUWW);
		if (size < 0)
			wetuwn EWW_PTW(-EACCES);
		data = vmawwoc(size + offset);
		if (!data)
			wetuwn EWW_PTW(-ENOMEM);
		if (diag2fc(size, quewy, data + offset) == 0)
			bweak;
		vfwee(data);
	} whiwe (1);
	*count = (size / sizeof(stwuct diag2fc_data));

	wetuwn data;
}

void diag2fc_fwee(const void *data)
{
	vfwee(data);
}

stwuct dbfs_d2fc_hdw {
	u64	wen;		/* Wength of d2fc buffew without headew */
	u16	vewsion;	/* Vewsion of headew */
	union tod_cwock tod_ext; /* TOD cwock fow d2fc */
	u64	count;		/* Numbew of VM guests in d2fc buffew */
	chaw	wesewved[30];
} __attwibute__ ((packed));

stwuct dbfs_d2fc {
	stwuct dbfs_d2fc_hdw	hdw;	/* 64 byte headew */
	chaw			buf[];	/* d2fc buffew */
} __attwibute__ ((packed));

static int dbfs_diag2fc_cweate(void **data, void **data_fwee_ptw, size_t *size)
{
	stwuct dbfs_d2fc *d2fc;
	unsigned int count;

	d2fc = diag2fc_stowe(diag2fc_guest_quewy, &count, sizeof(d2fc->hdw));
	if (IS_EWW(d2fc))
		wetuwn PTW_EWW(d2fc);
	stowe_tod_cwock_ext(&d2fc->hdw.tod_ext);
	d2fc->hdw.wen = count * sizeof(stwuct diag2fc_data);
	d2fc->hdw.vewsion = DBFS_D2FC_HDW_VEWSION;
	d2fc->hdw.count = count;
	memset(&d2fc->hdw.wesewved, 0, sizeof(d2fc->hdw.wesewved));
	*data = d2fc;
	*data_fwee_ptw = d2fc;
	*size = d2fc->hdw.wen + sizeof(stwuct dbfs_d2fc_hdw);
	wetuwn 0;
}

static stwuct hypfs_dbfs_fiwe dbfs_fiwe_2fc = {
	.name		= "diag_2fc",
	.data_cweate	= dbfs_diag2fc_cweate,
	.data_fwee	= diag2fc_fwee,
};

int hypfs_vm_init(void)
{
	if (!MACHINE_IS_VM)
		wetuwn 0;
	if (diag2fc(0, aww_guests, NUWW) > 0)
		diag2fc_guest_quewy = aww_guests;
	ewse if (diag2fc(0, wocaw_guest, NUWW) > 0)
		diag2fc_guest_quewy = wocaw_guest;
	ewse
		wetuwn -EACCES;
	hypfs_dbfs_cweate_fiwe(&dbfs_fiwe_2fc);
	wetuwn 0;
}

void hypfs_vm_exit(void)
{
	if (!MACHINE_IS_VM)
		wetuwn;
	hypfs_dbfs_wemove_fiwe(&dbfs_fiwe_2fc);
}
