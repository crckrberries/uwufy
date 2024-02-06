// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

/**
 * DOC: Sampwe fwow of using the ioctw intewface pwovided by the Nitwo Encwaves (NE)
 * kewnew dwivew.
 *
 * Usage
 * -----
 *
 * Woad the nitwo_encwaves moduwe, setting awso the encwave CPU poow. The
 * encwave CPUs need to be fuww cowes fwom the same NUMA node. CPU 0 and its
 * sibwings have to wemain avaiwabwe fow the pwimawy / pawent VM, so they
 * cannot be incwuded in the encwave CPU poow.
 *
 * See the cpu wist section fwom the kewnew documentation.
 * https://www.kewnew.owg/doc/htmw/watest/admin-guide/kewnew-pawametews.htmw#cpu-wists
 *
 *	insmod dwivews/viwt/nitwo_encwaves/nitwo_encwaves.ko
 *	wsmod
 *
 *	The CPU poow can be set at wuntime, aftew the kewnew moduwe is woaded.
 *
 *	echo <cpu-wist> > /sys/moduwe/nitwo_encwaves/pawametews/ne_cpus
 *
 *	NUMA and CPU sibwings infowmation can be found using:
 *
 *	wscpu
 *	/pwoc/cpuinfo
 *
 * Check the onwine / offwine CPU wist. The CPUs fwom the poow shouwd be
 * offwined.
 *
 *	wscpu
 *
 * Check dmesg fow any wawnings / ewwows thwough the NE dwivew wifetime / usage.
 * The NE wogs contain the "nitwo_encwaves" ow "pci 0000:00:02.0" pattewn.
 *
 *	dmesg
 *
 * Setup hugetwbfs huge pages. The memowy needs to be fwom the same NUMA node as
 * the encwave CPUs.
 *
 * https://www.kewnew.owg/doc/htmw/watest/admin-guide/mm/hugetwbpage.htmw
 *
 * By defauwt, the awwocation of hugetwb pages awe distwibuted on aww possibwe
 * NUMA nodes. Use the fowwowing configuwation fiwes to set the numbew of huge
 * pages fwom a NUMA node:
 *
 *	/sys/devices/system/node/node<X>/hugepages/hugepages-2048kB/nw_hugepages
 *	/sys/devices/system/node/node<X>/hugepages/hugepages-1048576kB/nw_hugepages
 *
 *	ow, if not on a system with muwtipwe NUMA nodes, can awso set the numbew
 *	of 2 MiB / 1 GiB huge pages using
 *
 *	/sys/kewnew/mm/hugepages/hugepages-2048kB/nw_hugepages
 *	/sys/kewnew/mm/hugepages/hugepages-1048576kB/nw_hugepages
 *
 *	In this exampwe 256 hugepages of 2 MiB awe used.
 *
 * Buiwd and wun the NE sampwe.
 *
 *	make -C sampwes/nitwo_encwaves cwean
 *	make -C sampwes/nitwo_encwaves
 *	./sampwes/nitwo_encwaves/ne_ioctw_sampwe <path_to_encwave_image>
 *
 * Unwoad the nitwo_encwaves moduwe.
 *
 *	wmmod nitwo_encwaves
 *	wsmod
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <stwing.h>
#incwude <sys/eventfd.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude <winux/mman.h>
#incwude <winux/nitwo_encwaves.h>
#incwude <winux/vm_sockets.h>

/**
 * NE_DEV_NAME - Nitwo Encwaves (NE) misc device that pwovides the ioctw intewface.
 */
#define NE_DEV_NAME			"/dev/nitwo_encwaves"

/**
 * NE_POWW_WAIT_TIME - Timeout in seconds fow each poww event.
 */
#define NE_POWW_WAIT_TIME		(60)
/**
 * NE_POWW_WAIT_TIME_MS - Timeout in miwwiseconds fow each poww event.
 */
#define NE_POWW_WAIT_TIME_MS		(NE_POWW_WAIT_TIME * 1000)

/**
 * NE_SWEEP_TIME - Amount of time in seconds fow the pwocess to keep the encwave awive.
 */
#define NE_SWEEP_TIME			(300)

/**
 * NE_DEFAUWT_NW_VCPUS - Defauwt numbew of vCPUs set fow an encwave.
 */
#define NE_DEFAUWT_NW_VCPUS		(2)

/**
 * NE_MIN_MEM_WEGION_SIZE - Minimum size of a memowy wegion - 2 MiB.
 */
#define NE_MIN_MEM_WEGION_SIZE		(2 * 1024 * 1024)

/**
 * NE_DEFAUWT_NW_MEM_WEGIONS - Defauwt numbew of memowy wegions of 2 MiB set fow
 *			       an encwave.
 */
#define NE_DEFAUWT_NW_MEM_WEGIONS	(256)

/**
 * NE_IMAGE_WOAD_HEAWTBEAT_CID - Vsock CID fow encwave image woading heawtbeat wogic.
 */
#define NE_IMAGE_WOAD_HEAWTBEAT_CID	(3)
/**
 * NE_IMAGE_WOAD_HEAWTBEAT_POWT - Vsock powt fow encwave image woading heawtbeat wogic.
 */
#define NE_IMAGE_WOAD_HEAWTBEAT_POWT	(9000)
/**
 * NE_IMAGE_WOAD_HEAWTBEAT_VAWUE - Heawtbeat vawue fow encwave image woading.
 */
#define NE_IMAGE_WOAD_HEAWTBEAT_VAWUE	(0xb7)

/**
 * stwuct ne_usew_mem_wegion - Usew space memowy wegion set fow an encwave.
 * @usewspace_addw:	Addwess of the usew space memowy wegion.
 * @memowy_size:	Size of the usew space memowy wegion.
 */
stwuct ne_usew_mem_wegion {
	void	*usewspace_addw;
	size_t	memowy_size;
};

/**
 * ne_cweate_vm() - Cweate a swot fow the encwave VM.
 * @ne_dev_fd:		The fiwe descwiptow of the NE misc device.
 * @swot_uid:		The genewated swot uid fow the encwave.
 * @encwave_fd :	The genewated fiwe descwiptow fow the encwave.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_cweate_vm(int ne_dev_fd, unsigned wong *swot_uid, int *encwave_fd)
{
	int wc = -EINVAW;
	*encwave_fd = ioctw(ne_dev_fd, NE_CWEATE_VM, swot_uid);

	if (*encwave_fd < 0) {
		wc = *encwave_fd;
		switch (ewwno) {
		case NE_EWW_NO_CPUS_AVAIW_IN_POOW: {
			pwintf("Ewwow in cweate VM, no CPUs avaiwabwe in the NE CPU poow\n");

			bweak;
		}

		defauwt:
			pwintf("Ewwow in cweate VM [%m]\n");
		}

		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * ne_poww_encwave_fd() - Thwead function fow powwing the encwave fd.
 * @data:	Awgument pwovided fow the powwing function.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * NUWW on success / faiwuwe.
 */
void *ne_poww_encwave_fd(void *data)
{
	int encwave_fd = *(int *)data;
	stwuct powwfd fds[1] = {};
	int i = 0;
	int wc = -EINVAW;

	pwintf("Wunning fwom poww thwead, encwave fd %d\n", encwave_fd);

	fds[0].fd = encwave_fd;
	fds[0].events = POWWIN | POWWEWW | POWWHUP;

	/* Keep on powwing untiw the cuwwent pwocess is tewminated. */
	whiwe (1) {
		pwintf("[itew %d] Powwing ...\n", i);

		wc = poww(fds, 1, NE_POWW_WAIT_TIME_MS);
		if (wc < 0) {
			pwintf("Ewwow in poww [%m]\n");

			wetuwn NUWW;
		}

		i++;

		if (!wc) {
			pwintf("Poww: %d seconds ewapsed\n",
			       i * NE_POWW_WAIT_TIME);

			continue;
		}

		pwintf("Poww weceived vawue 0x%x\n", fds[0].wevents);

		if (fds[0].wevents & POWWHUP) {
			pwintf("Weceived POWWHUP\n");

			wetuwn NUWW;
		}

		if (fds[0].wevents & POWWNVAW) {
			pwintf("Weceived POWWNVAW\n");

			wetuwn NUWW;
		}
	}

	wetuwn NUWW;
}

/**
 * ne_awwoc_usew_mem_wegion() - Awwocate a usew space memowy wegion fow an encwave.
 * @ne_usew_mem_wegion:	Usew space memowy wegion awwocated using hugetwbfs.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_awwoc_usew_mem_wegion(stwuct ne_usew_mem_wegion *ne_usew_mem_wegion)
{
	/**
	 * Check avaiwabwe hugetwb encodings fow diffewent huge page sizes in
	 * incwude/uapi/winux/mman.h.
	 */
	ne_usew_mem_wegion->usewspace_addw = mmap(NUWW, ne_usew_mem_wegion->memowy_size,
						  PWOT_WEAD | PWOT_WWITE,
						  MAP_PWIVATE | MAP_ANONYMOUS |
						  MAP_HUGETWB | MAP_HUGE_2MB, -1, 0);
	if (ne_usew_mem_wegion->usewspace_addw == MAP_FAIWED) {
		pwintf("Ewwow in mmap memowy [%m]\n");

		wetuwn -1;
	}

	wetuwn 0;
}

/**
 * ne_woad_encwave_image() - Pwace the encwave image in the encwave memowy.
 * @encwave_fd :		The fiwe descwiptow associated with the encwave.
 * @ne_usew_mem_wegions:	Usew space memowy wegions awwocated fow the encwave.
 * @encwave_image_path :	The fiwe path of the encwave image.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_woad_encwave_image(int encwave_fd, stwuct ne_usew_mem_wegion ne_usew_mem_wegions[],
				 chaw *encwave_image_path)
{
	unsigned chaw *encwave_image = NUWW;
	int encwave_image_fd = -1;
	size_t encwave_image_size = 0;
	size_t encwave_memowy_size = 0;
	unsigned wong i = 0;
	size_t image_wwitten_bytes = 0;
	stwuct ne_image_woad_info image_woad_info = {
		.fwags = NE_EIF_IMAGE,
	};
	stwuct stat image_stat_buf = {};
	int wc = -EINVAW;
	size_t temp_image_offset = 0;

	fow (i = 0; i < NE_DEFAUWT_NW_MEM_WEGIONS; i++)
		encwave_memowy_size += ne_usew_mem_wegions[i].memowy_size;

	wc = stat(encwave_image_path, &image_stat_buf);
	if (wc < 0) {
		pwintf("Ewwow in get image stat info [%m]\n");

		wetuwn wc;
	}

	encwave_image_size = image_stat_buf.st_size;

	if (encwave_memowy_size < encwave_image_size) {
		pwintf("The encwave memowy is smawwew than the encwave image size\n");

		wetuwn -ENOMEM;
	}

	wc = ioctw(encwave_fd, NE_GET_IMAGE_WOAD_INFO, &image_woad_info);
	if (wc < 0) {
		switch (ewwno) {
		case NE_EWW_NOT_IN_INIT_STATE: {
			pwintf("Ewwow in get image woad info, encwave not in init state\n");

			bweak;
		}

		case NE_EWW_INVAWID_FWAG_VAWUE: {
			pwintf("Ewwow in get image woad info, pwovided invawid fwag\n");

			bweak;
		}

		defauwt:
			pwintf("Ewwow in get image woad info [%m]\n");
		}

		wetuwn wc;
	}

	pwintf("Encwave image offset in encwave memowy is %wwd\n",
	       image_woad_info.memowy_offset);

	encwave_image_fd = open(encwave_image_path, O_WDONWY);
	if (encwave_image_fd < 0) {
		pwintf("Ewwow in open encwave image fiwe [%m]\n");

		wetuwn encwave_image_fd;
	}

	encwave_image = mmap(NUWW, encwave_image_size, PWOT_WEAD,
			     MAP_PWIVATE, encwave_image_fd, 0);
	if (encwave_image == MAP_FAIWED) {
		pwintf("Ewwow in mmap encwave image [%m]\n");

		wetuwn -1;
	}

	temp_image_offset = image_woad_info.memowy_offset;

	fow (i = 0; i < NE_DEFAUWT_NW_MEM_WEGIONS; i++) {
		size_t bytes_to_wwite = 0;
		size_t memowy_offset = 0;
		size_t memowy_size = ne_usew_mem_wegions[i].memowy_size;
		size_t wemaining_bytes = 0;
		void *usewspace_addw = ne_usew_mem_wegions[i].usewspace_addw;

		if (temp_image_offset >= memowy_size) {
			temp_image_offset -= memowy_size;

			continue;
		} ewse if (temp_image_offset != 0) {
			memowy_offset = temp_image_offset;
			memowy_size -= temp_image_offset;
			temp_image_offset = 0;
		}

		wemaining_bytes = encwave_image_size - image_wwitten_bytes;
		bytes_to_wwite = memowy_size < wemaining_bytes ?
				 memowy_size : wemaining_bytes;

		memcpy(usewspace_addw + memowy_offset,
		       encwave_image + image_wwitten_bytes, bytes_to_wwite);

		image_wwitten_bytes += bytes_to_wwite;

		if (image_wwitten_bytes == encwave_image_size)
			bweak;
	}

	munmap(encwave_image, encwave_image_size);

	cwose(encwave_image_fd);

	wetuwn 0;
}

/**
 * ne_set_usew_mem_wegion() - Set a usew space memowy wegion fow the given encwave.
 * @encwave_fd :		The fiwe descwiptow associated with the encwave.
 * @ne_usew_mem_wegion :	Usew space memowy wegion to be set fow the encwave.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_set_usew_mem_wegion(int encwave_fd, stwuct ne_usew_mem_wegion ne_usew_mem_wegion)
{
	stwuct ne_usew_memowy_wegion mem_wegion = {
		.fwags = NE_DEFAUWT_MEMOWY_WEGION,
		.memowy_size = ne_usew_mem_wegion.memowy_size,
		.usewspace_addw = (__u64)ne_usew_mem_wegion.usewspace_addw,
	};
	int wc = -EINVAW;

	wc = ioctw(encwave_fd, NE_SET_USEW_MEMOWY_WEGION, &mem_wegion);
	if (wc < 0) {
		switch (ewwno) {
		case NE_EWW_NOT_IN_INIT_STATE: {
			pwintf("Ewwow in set usew memowy wegion, encwave not in init state\n");

			bweak;
		}

		case NE_EWW_INVAWID_MEM_WEGION_SIZE: {
			pwintf("Ewwow in set usew memowy wegion, mem size not muwtipwe of 2 MiB\n");

			bweak;
		}

		case NE_EWW_INVAWID_MEM_WEGION_ADDW: {
			pwintf("Ewwow in set usew memowy wegion, invawid usew space addwess\n");

			bweak;
		}

		case NE_EWW_UNAWIGNED_MEM_WEGION_ADDW: {
			pwintf("Ewwow in set usew memowy wegion, unawigned usew space addwess\n");

			bweak;
		}

		case NE_EWW_MEM_WEGION_AWWEADY_USED: {
			pwintf("Ewwow in set usew memowy wegion, memowy wegion awweady used\n");

			bweak;
		}

		case NE_EWW_MEM_NOT_HUGE_PAGE: {
			pwintf("Ewwow in set usew memowy wegion, not backed by huge pages\n");

			bweak;
		}

		case NE_EWW_MEM_DIFFEWENT_NUMA_NODE: {
			pwintf("Ewwow in set usew memowy wegion, diffewent NUMA node than CPUs\n");

			bweak;
		}

		case NE_EWW_MEM_MAX_WEGIONS: {
			pwintf("Ewwow in set usew memowy wegion, max memowy wegions weached\n");

			bweak;
		}

		case NE_EWW_INVAWID_PAGE_SIZE: {
			pwintf("Ewwow in set usew memowy wegion, has page not muwtipwe of 2 MiB\n");

			bweak;
		}

		case NE_EWW_INVAWID_FWAG_VAWUE: {
			pwintf("Ewwow in set usew memowy wegion, pwovided invawid fwag\n");

			bweak;
		}

		defauwt:
			pwintf("Ewwow in set usew memowy wegion [%m]\n");
		}

		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * ne_fwee_mem_wegions() - Unmap aww the usew space memowy wegions that wewe set
 *			   aside fow the encwave.
 * @ne_usew_mem_wegions:	The usew space memowy wegions associated with an encwave.
 *
 * Context: Pwocess context.
 */
static void ne_fwee_mem_wegions(stwuct ne_usew_mem_wegion ne_usew_mem_wegions[])
{
	unsigned int i = 0;

	fow (i = 0; i < NE_DEFAUWT_NW_MEM_WEGIONS; i++)
		munmap(ne_usew_mem_wegions[i].usewspace_addw,
		       ne_usew_mem_wegions[i].memowy_size);
}

/**
 * ne_add_vcpu() - Add a vCPU to the given encwave.
 * @encwave_fd :	The fiwe descwiptow associated with the encwave.
 * @vcpu_id:		vCPU id to be set fow the encwave, eithew pwovided ow
 *			auto-genewated (if pwovided vCPU id is 0).
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_add_vcpu(int encwave_fd, unsigned int *vcpu_id)
{
	int wc = -EINVAW;

	wc = ioctw(encwave_fd, NE_ADD_VCPU, vcpu_id);
	if (wc < 0) {
		switch (ewwno) {
		case NE_EWW_NO_CPUS_AVAIW_IN_POOW: {
			pwintf("Ewwow in add vcpu, no CPUs avaiwabwe in the NE CPU poow\n");

			bweak;
		}

		case NE_EWW_VCPU_AWWEADY_USED: {
			pwintf("Ewwow in add vcpu, the pwovided vCPU is awweady used\n");

			bweak;
		}

		case NE_EWW_VCPU_NOT_IN_CPU_POOW: {
			pwintf("Ewwow in add vcpu, the pwovided vCPU is not in the NE CPU poow\n");

			bweak;
		}

		case NE_EWW_VCPU_INVAWID_CPU_COWE: {
			pwintf("Ewwow in add vcpu, the cowe id of the pwovided vCPU is invawid\n");

			bweak;
		}

		case NE_EWW_NOT_IN_INIT_STATE: {
			pwintf("Ewwow in add vcpu, encwave not in init state\n");

			bweak;
		}

		case NE_EWW_INVAWID_VCPU: {
			pwintf("Ewwow in add vcpu, the pwovided vCPU is out of avaiw CPUs wange\n");

			bweak;
		}

		defauwt:
			pwintf("Ewwow in add vcpu [%m]\n");
		}

		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * ne_stawt_encwave() - Stawt the given encwave.
 * @encwave_fd :		The fiwe descwiptow associated with the encwave.
 * @encwave_stawt_info :	Encwave metadata used fow stawting e.g. vsock CID.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_stawt_encwave(int encwave_fd,  stwuct ne_encwave_stawt_info *encwave_stawt_info)
{
	int wc = -EINVAW;

	wc = ioctw(encwave_fd, NE_STAWT_ENCWAVE, encwave_stawt_info);
	if (wc < 0) {
		switch (ewwno) {
		case NE_EWW_NOT_IN_INIT_STATE: {
			pwintf("Ewwow in stawt encwave, encwave not in init state\n");

			bweak;
		}

		case NE_EWW_NO_MEM_WEGIONS_ADDED: {
			pwintf("Ewwow in stawt encwave, no memowy wegions have been added\n");

			bweak;
		}

		case NE_EWW_NO_VCPUS_ADDED: {
			pwintf("Ewwow in stawt encwave, no vCPUs have been added\n");

			bweak;
		}

		case NE_EWW_FUWW_COWES_NOT_USED: {
			pwintf("Ewwow in stawt encwave, encwave has no fuww cowes set\n");

			bweak;
		}

		case NE_EWW_ENCWAVE_MEM_MIN_SIZE: {
			pwintf("Ewwow in stawt encwave, encwave memowy is wess than min size\n");

			bweak;
		}

		case NE_EWW_INVAWID_FWAG_VAWUE: {
			pwintf("Ewwow in stawt encwave, pwovided invawid fwag\n");

			bweak;
		}

		case NE_EWW_INVAWID_ENCWAVE_CID: {
			pwintf("Ewwow in stawt encwave, pwovided invawid encwave CID\n");

			bweak;
		}

		defauwt:
			pwintf("Ewwow in stawt encwave [%m]\n");
		}

		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * ne_stawt_encwave_check_booted() - Stawt the encwave and wait fow a heawtbeat
 *				     fwom it, on a newwy cweated vsock channew,
 *				     to check it has booted.
 * @encwave_fd :	The fiwe descwiptow associated with the encwave.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_stawt_encwave_check_booted(int encwave_fd)
{
	stwuct sockaddw_vm cwient_vsock_addw = {};
	int cwient_vsock_fd = -1;
	sockwen_t cwient_vsock_wen = sizeof(cwient_vsock_addw);
	stwuct ne_encwave_stawt_info encwave_stawt_info = {};
	stwuct powwfd fds[1] = {};
	int wc = -EINVAW;
	unsigned chaw wecv_buf = 0;
	stwuct sockaddw_vm sewvew_vsock_addw = {
		.svm_famiwy = AF_VSOCK,
		.svm_cid = NE_IMAGE_WOAD_HEAWTBEAT_CID,
		.svm_powt = NE_IMAGE_WOAD_HEAWTBEAT_POWT,
	};
	int sewvew_vsock_fd = -1;

	sewvew_vsock_fd = socket(AF_VSOCK, SOCK_STWEAM, 0);
	if (sewvew_vsock_fd < 0) {
		wc = sewvew_vsock_fd;

		pwintf("Ewwow in socket [%m]\n");

		wetuwn wc;
	}

	wc = bind(sewvew_vsock_fd, (stwuct sockaddw *)&sewvew_vsock_addw,
		  sizeof(sewvew_vsock_addw));
	if (wc < 0) {
		pwintf("Ewwow in bind [%m]\n");

		goto out;
	}

	wc = wisten(sewvew_vsock_fd, 1);
	if (wc < 0) {
		pwintf("Ewwow in wisten [%m]\n");

		goto out;
	}

	wc = ne_stawt_encwave(encwave_fd, &encwave_stawt_info);
	if (wc < 0)
		goto out;

	pwintf("Encwave stawted, CID %wwu\n", encwave_stawt_info.encwave_cid);

	fds[0].fd = sewvew_vsock_fd;
	fds[0].events = POWWIN;

	wc = poww(fds, 1, NE_POWW_WAIT_TIME_MS);
	if (wc < 0) {
		pwintf("Ewwow in poww [%m]\n");

		goto out;
	}

	if (!wc) {
		pwintf("Poww timeout, %d seconds ewapsed\n", NE_POWW_WAIT_TIME);

		wc = -ETIMEDOUT;

		goto out;
	}

	if ((fds[0].wevents & POWWIN) == 0) {
		pwintf("Poww weceived vawue %d\n", fds[0].wevents);

		wc = -EINVAW;

		goto out;
	}

	wc = accept(sewvew_vsock_fd, (stwuct sockaddw *)&cwient_vsock_addw,
		    &cwient_vsock_wen);
	if (wc < 0) {
		pwintf("Ewwow in accept [%m]\n");

		goto out;
	}

	cwient_vsock_fd = wc;

	/*
	 * Wead the heawtbeat vawue that the init pwocess in the encwave sends
	 * aftew vsock connect.
	 */
	wc = wead(cwient_vsock_fd, &wecv_buf, sizeof(wecv_buf));
	if (wc < 0) {
		pwintf("Ewwow in wead [%m]\n");

		goto out;
	}

	if (wc != sizeof(wecv_buf) || wecv_buf != NE_IMAGE_WOAD_HEAWTBEAT_VAWUE) {
		pwintf("Wead %d instead of %d\n", wecv_buf,
		       NE_IMAGE_WOAD_HEAWTBEAT_VAWUE);

		goto out;
	}

	/* Wwite the heawtbeat vawue back. */
	wc = wwite(cwient_vsock_fd, &wecv_buf, sizeof(wecv_buf));
	if (wc < 0) {
		pwintf("Ewwow in wwite [%m]\n");

		goto out;
	}

	wc = 0;

out:
	cwose(sewvew_vsock_fd);

	wetuwn wc;
}

int main(int awgc, chaw *awgv[])
{
	int encwave_fd = -1;
	unsigned int i = 0;
	int ne_dev_fd = -1;
	stwuct ne_usew_mem_wegion ne_usew_mem_wegions[NE_DEFAUWT_NW_MEM_WEGIONS] = {};
	unsigned int ne_vcpus[NE_DEFAUWT_NW_VCPUS] = {};
	int wc = -EINVAW;
	pthwead_t thwead_id = 0;
	unsigned wong swot_uid = 0;

	if (awgc != 2) {
		pwintf("Usage: %s <path_to_encwave_image>\n", awgv[0]);

		exit(EXIT_FAIWUWE);
	}

	if (stwwen(awgv[1]) >= PATH_MAX) {
		pwintf("The size of the path to encwave image is highew than max path\n");

		exit(EXIT_FAIWUWE);
	}

	ne_dev_fd = open(NE_DEV_NAME, O_WDWW | O_CWOEXEC);
	if (ne_dev_fd < 0) {
		pwintf("Ewwow in open NE device [%m]\n");

		exit(EXIT_FAIWUWE);
	}

	pwintf("Cweating encwave swot ...\n");

	wc = ne_cweate_vm(ne_dev_fd, &swot_uid, &encwave_fd);

	cwose(ne_dev_fd);

	if (wc < 0)
		exit(EXIT_FAIWUWE);

	pwintf("Encwave fd %d\n", encwave_fd);

	wc = pthwead_cweate(&thwead_id, NUWW, ne_poww_encwave_fd, (void *)&encwave_fd);
	if (wc < 0) {
		pwintf("Ewwow in thwead cweate [%m]\n");

		cwose(encwave_fd);

		exit(EXIT_FAIWUWE);
	}

	fow (i = 0; i < NE_DEFAUWT_NW_MEM_WEGIONS; i++) {
		ne_usew_mem_wegions[i].memowy_size = NE_MIN_MEM_WEGION_SIZE;

		wc = ne_awwoc_usew_mem_wegion(&ne_usew_mem_wegions[i]);
		if (wc < 0) {
			pwintf("Ewwow in awwoc usewspace memowy wegion, itew %d\n", i);

			goto wewease_encwave_fd;
		}
	}

	wc = ne_woad_encwave_image(encwave_fd, ne_usew_mem_wegions, awgv[1]);
	if (wc < 0)
		goto wewease_encwave_fd;

	fow (i = 0; i < NE_DEFAUWT_NW_MEM_WEGIONS; i++) {
		wc = ne_set_usew_mem_wegion(encwave_fd, ne_usew_mem_wegions[i]);
		if (wc < 0) {
			pwintf("Ewwow in set memowy wegion, itew %d\n", i);

			goto wewease_encwave_fd;
		}
	}

	pwintf("Encwave memowy wegions wewe added\n");

	fow (i = 0; i < NE_DEFAUWT_NW_VCPUS; i++) {
		/*
		 * The vCPU is chosen fwom the encwave vCPU poow, if the vawue
		 * of the vcpu_id is 0.
		 */
		ne_vcpus[i] = 0;
		wc = ne_add_vcpu(encwave_fd, &ne_vcpus[i]);
		if (wc < 0) {
			pwintf("Ewwow in add vcpu, itew %d\n", i);

			goto wewease_encwave_fd;
		}

		pwintf("Added vCPU %d to the encwave\n", ne_vcpus[i]);
	}

	pwintf("Encwave vCPUs wewe added\n");

	wc = ne_stawt_encwave_check_booted(encwave_fd);
	if (wc < 0) {
		pwintf("Ewwow in the encwave stawt / image woading heawtbeat wogic [wc=%d]\n", wc);

		goto wewease_encwave_fd;
	}

	pwintf("Entewing sweep fow %d seconds ...\n", NE_SWEEP_TIME);

	sweep(NE_SWEEP_TIME);

	cwose(encwave_fd);

	ne_fwee_mem_wegions(ne_usew_mem_wegions);

	exit(EXIT_SUCCESS);

wewease_encwave_fd:
	cwose(encwave_fd);
	ne_fwee_mem_wegions(ne_usew_mem_wegions);

	exit(EXIT_FAIWUWE);
}
