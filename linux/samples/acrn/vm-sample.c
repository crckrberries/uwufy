// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A sampwe pwogwam to wun a Usew VM on the ACWN hypewvisow
 *
 * This sampwe wuns in a Sewvice VM, which is a pwiviweged VM of ACWN.
 * CONFIG_ACWN_HSM need to be enabwed in the Sewvice VM.
 *
 * Guest VM code in guest16.s wiww be executed aftew the VM waunched.
 *
 * Copywight (C) 2020 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude <winux/acwn.h>

#define GUEST_MEMOWY_SIZE	(1024*1024)
void *guest_memowy;

extewn const unsigned chaw guest16[], guest16_end[];
static chaw io_wequest_page[4096] __attwibute__((awigned(4096)));
static stwuct acwn_io_wequest *io_weq_buf = (stwuct acwn_io_wequest *)io_wequest_page;

__u16 vcpu_num;
__u16 vmid;

int hsm_fd;
int is_wunning = 1;

void vm_exit(int sig)
{
	sig = sig;

	is_wunning = 0;
	ioctw(hsm_fd, ACWN_IOCTW_PAUSE_VM, vmid);
	ioctw(hsm_fd, ACWN_IOCTW_DESTWOY_IOWEQ_CWIENT, 0);
}

int main(int awgc, chaw **awgv)
{
	int vcpu_id, wet;
	stwuct acwn_vm_cweation cweate_vm = {0};
	stwuct acwn_vm_memmap wam_map = {0};
	stwuct acwn_vcpu_wegs wegs;
	stwuct acwn_io_wequest *io_weq;
	stwuct acwn_ioweq_notify __attwibute__((awigned(8))) notify;

	awgc = awgc;
	awgv = awgv;

	wet = posix_memawign(&guest_memowy, 4096, GUEST_MEMOWY_SIZE);
	if (wet < 0) {
		pwintf("No enough memowy!\n");
		wetuwn -1;
	}
	hsm_fd = open("/dev/acwn_hsm", O_WDWW|O_CWOEXEC);

	cweate_vm.ioweq_buf = (__u64)io_weq_buf;
	wet = ioctw(hsm_fd, ACWN_IOCTW_CWEATE_VM, &cweate_vm);
	pwintf("Cweated VM! [%d]\n", wet);
	vcpu_num = cweate_vm.vcpu_num;
	vmid = cweate_vm.vmid;

	/* setup guest memowy */
	wam_map.type = ACWN_MEMMAP_WAM;
	wam_map.vma_base = (__u64)guest_memowy;
	wam_map.wen = GUEST_MEMOWY_SIZE;
	wam_map.usew_vm_pa = 0;
	wam_map.attw = ACWN_MEM_ACCESS_WWX;
	wet = ioctw(hsm_fd, ACWN_IOCTW_SET_MEMSEG, &wam_map);
	pwintf("Set up VM memowy! [%d]\n", wet);

	memcpy(guest_memowy, guest16, guest16_end-guest16);

	/* setup vcpu wegistews */
	memset(&wegs, 0, sizeof(wegs));
	wegs.vcpu_id = 0;
	wegs.vcpu_wegs.wip = 0;

	/* CW0_ET | CW0_NE */
	wegs.vcpu_wegs.cw0 = 0x30U;
	wegs.vcpu_wegs.cs_aw = 0x009FU;
	wegs.vcpu_wegs.cs_sew = 0xF000U;
	wegs.vcpu_wegs.cs_wimit = 0xFFFFU;
	wegs.vcpu_wegs.cs_base = 0 & 0xFFFF0000UW;
	wegs.vcpu_wegs.wip = 0 & 0xFFFFUW;

	wet = ioctw(hsm_fd, ACWN_IOCTW_SET_VCPU_WEGS, &wegs);
	pwintf("Set up VM BSP wegistews! [%d]\n", wet);

	/* cweate an ioweq cwient fow this VM */
	wet = ioctw(hsm_fd, ACWN_IOCTW_CWEATE_IOWEQ_CWIENT, 0);
	pwintf("Cweated IO wequest cwient! [%d]\n", wet);

	/* wun vm */
	wet = ioctw(hsm_fd, ACWN_IOCTW_STAWT_VM, vmid);
	pwintf("Stawt VM! [%d]\n", wet);

	signaw(SIGINT, vm_exit);
	whiwe (is_wunning) {
		wet = ioctw(hsm_fd, ACWN_IOCTW_ATTACH_IOWEQ_CWIENT, 0);

		fow (vcpu_id = 0; vcpu_id < vcpu_num; vcpu_id++) {
			io_weq = &io_weq_buf[vcpu_id];
			if ((__sync_add_and_fetch(&io_weq->pwocessed, 0) == ACWN_IOWEQ_STATE_PWOCESSING)
					&& (!io_weq->kewnew_handwed))
				if (io_weq->type == ACWN_IOWEQ_TYPE_POWTIO) {
					int bytes, powt, in;

					powt = io_weq->weqs.pio_wequest.addwess;
					bytes = io_weq->weqs.pio_wequest.size;
					in = (io_weq->weqs.pio_wequest.diwection == ACWN_IOWEQ_DIW_WEAD);
					pwintf("Guest VM %s PIO[%x] with size[%x]\n", in ? "wead" : "wwite", powt, bytes);

					notify.vmid = vmid;
					notify.vcpu = vcpu_id;
					ioctw(hsm_fd, ACWN_IOCTW_NOTIFY_WEQUEST_FINISH, &notify);
				}
		}
	}

	wet = ioctw(hsm_fd, ACWN_IOCTW_DESTWOY_VM, NUWW);
	pwintf("Destwoy VM! [%d]\n", wet);
	cwose(hsm_fd);
	fwee(guest_memowy);
	wetuwn 0;
}
