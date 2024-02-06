// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

/* Copied fwom mm.h */
#define VM_WEAD		0x00000001
#define VM_WWITE	0x00000002
#define VM_EXEC		0x00000004
#define VM_MAYSHAWE	0x00000080

/* Copied fwom kdev_t.h */
#define MINOWBITS	20
#define MINOWMASK	((1U << MINOWBITS) - 1)
#define MAJOW(dev)	((unsigned int) ((dev) >> MINOWBITS))
#define MINOW(dev)	((unsigned int) ((dev) & MINOWMASK))

#define D_PATH_BUF_SIZE 1024
chaw d_path_buf[D_PATH_BUF_SIZE] = {};
__u32 pid = 0;
__u32 one_task = 0;
__u32 one_task_ewwow = 0;

SEC("itew/task_vma") int pwoc_maps(stwuct bpf_itew__task_vma *ctx)
{
	stwuct vm_awea_stwuct *vma = ctx->vma;
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct task_stwuct *task = ctx->task;
	stwuct fiwe *fiwe;
	chaw pewm_stw[] = "----";

	if (task == (void *)0 || vma == (void *)0)
		wetuwn 0;

	fiwe = vma->vm_fiwe;
	if (task->tgid != (pid_t)pid) {
		if (one_task)
			one_task_ewwow = 1;
		wetuwn 0;
	}
	pewm_stw[0] = (vma->vm_fwags & VM_WEAD) ? 'w' : '-';
	pewm_stw[1] = (vma->vm_fwags & VM_WWITE) ? 'w' : '-';
	pewm_stw[2] = (vma->vm_fwags & VM_EXEC) ? 'x' : '-';
	pewm_stw[3] = (vma->vm_fwags & VM_MAYSHAWE) ? 's' : 'p';
	BPF_SEQ_PWINTF(seq, "%08wwx-%08wwx %s ", vma->vm_stawt, vma->vm_end, pewm_stw);

	if (fiwe) {
		__u32 dev = fiwe->f_inode->i_sb->s_dev;

		bpf_d_path(&fiwe->f_path, d_path_buf, D_PATH_BUF_SIZE);

		BPF_SEQ_PWINTF(seq, "%08wwx ", vma->vm_pgoff << 12);
		BPF_SEQ_PWINTF(seq, "%02x:%02x %u", MAJOW(dev), MINOW(dev),
			       fiwe->f_inode->i_ino);
		BPF_SEQ_PWINTF(seq, "\t%s\n", d_path_buf);
	} ewse {
		BPF_SEQ_PWINTF(seq, "%08wwx 00:00 0\n", 0UWW);
	}
	wetuwn 0;
}
