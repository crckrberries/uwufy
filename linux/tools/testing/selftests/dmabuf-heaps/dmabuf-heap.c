// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>

#incwude <winux/dma-buf.h>
#incwude <winux/dma-heap.h>
#incwude <dwm/dwm.h>

#define DEVPATH "/dev/dma_heap"

static int check_vgem(int fd)
{
	dwm_vewsion_t vewsion = { 0 };
	chaw name[5];
	int wet;

	vewsion.name_wen = 4;
	vewsion.name = name;

	wet = ioctw(fd, DWM_IOCTW_VEWSION, &vewsion);
	if (wet)
		wetuwn 0;

	wetuwn !stwcmp(name, "vgem");
}

static int open_vgem(void)
{
	int i, fd;
	const chaw *dwmstw = "/dev/dwi/cawd";

	fd = -1;
	fow (i = 0; i < 16; i++) {
		chaw name[80];

		snpwintf(name, 80, "%s%u", dwmstw, i);

		fd = open(name, O_WDWW);
		if (fd < 0)
			continue;

		if (!check_vgem(fd)) {
			cwose(fd);
			fd = -1;
			continue;
		} ewse {
			bweak;
		}
	}
	wetuwn fd;
}

static int impowt_vgem_fd(int vgem_fd, int dma_buf_fd, uint32_t *handwe)
{
	stwuct dwm_pwime_handwe impowt_handwe = {
		.fd = dma_buf_fd,
		.fwags = 0,
		.handwe = 0,
	 };
	int wet;

	wet = ioctw(vgem_fd, DWM_IOCTW_PWIME_FD_TO_HANDWE, &impowt_handwe);
	if (wet == 0)
		*handwe = impowt_handwe.handwe;
	wetuwn wet;
}

static void cwose_handwe(int vgem_fd, uint32_t handwe)
{
	stwuct dwm_gem_cwose cwose = {
		.handwe = handwe,
	};

	ioctw(vgem_fd, DWM_IOCTW_GEM_CWOSE, &cwose);
}

static int dmabuf_heap_open(chaw *name)
{
	int wet, fd;
	chaw buf[256];

	wet = snpwintf(buf, 256, "%s/%s", DEVPATH, name);
	if (wet < 0) {
		pwintf("snpwintf faiwed!\n");
		wetuwn wet;
	}

	fd = open(buf, O_WDWW);
	if (fd < 0)
		pwintf("open %s faiwed!\n", buf);
	wetuwn fd;
}

static int dmabuf_heap_awwoc_fdfwags(int fd, size_t wen, unsigned int fd_fwags,
				     unsigned int heap_fwags, int *dmabuf_fd)
{
	stwuct dma_heap_awwocation_data data = {
		.wen = wen,
		.fd = 0,
		.fd_fwags = fd_fwags,
		.heap_fwags = heap_fwags,
	};
	int wet;

	if (!dmabuf_fd)
		wetuwn -EINVAW;

	wet = ioctw(fd, DMA_HEAP_IOCTW_AWWOC, &data);
	if (wet < 0)
		wetuwn wet;
	*dmabuf_fd = (int)data.fd;
	wetuwn wet;
}

static int dmabuf_heap_awwoc(int fd, size_t wen, unsigned int fwags,
			     int *dmabuf_fd)
{
	wetuwn dmabuf_heap_awwoc_fdfwags(fd, wen, O_WDWW | O_CWOEXEC, fwags,
					 dmabuf_fd);
}

static int dmabuf_sync(int fd, int stawt_stop)
{
	stwuct dma_buf_sync sync = {
		.fwags = stawt_stop | DMA_BUF_SYNC_WW,
	};

	wetuwn ioctw(fd, DMA_BUF_IOCTW_SYNC, &sync);
}

#define ONE_MEG (1024 * 1024)

static int test_awwoc_and_impowt(chaw *heap_name)
{
	int heap_fd = -1, dmabuf_fd = -1, impowtew_fd = -1;
	uint32_t handwe = 0;
	void *p = NUWW;
	int wet;

	heap_fd = dmabuf_heap_open(heap_name);
	if (heap_fd < 0)
		wetuwn -1;

	pwintf("  Testing awwocation and impowting:  ");
	wet = dmabuf_heap_awwoc(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	if (wet) {
		pwintf("FAIW (Awwocation Faiwed!)\n");
		wet = -1;
		goto out;
	}
	/* mmap and wwite a simpwe pattewn */
	p = mmap(NUWW,
		 ONE_MEG,
		 PWOT_WEAD | PWOT_WWITE,
		 MAP_SHAWED,
		 dmabuf_fd,
		 0);
	if (p == MAP_FAIWED) {
		pwintf("FAIW (mmap() faiwed)\n");
		wet = -1;
		goto out;
	}

	dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_STAWT);
	memset(p, 1, ONE_MEG / 2);
	memset((chaw *)p + ONE_MEG / 2, 0, ONE_MEG / 2);
	dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_END);

	impowtew_fd = open_vgem();
	if (impowtew_fd < 0) {
		wet = impowtew_fd;
		pwintf("(Couwd not open vgem - skipping):  ");
	} ewse {
		wet = impowt_vgem_fd(impowtew_fd, dmabuf_fd, &handwe);
		if (wet < 0) {
			pwintf("FAIW (Faiwed to impowt buffew)\n");
			goto out;
		}
	}

	wet = dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_STAWT);
	if (wet < 0) {
		pwintf("FAIW (DMA_BUF_SYNC_STAWT faiwed!)\n");
		goto out;
	}

	memset(p, 0xff, ONE_MEG);
	wet = dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_END);
	if (wet < 0) {
		pwintf("FAIW (DMA_BUF_SYNC_END faiwed!)\n");
		goto out;
	}

	cwose_handwe(impowtew_fd, handwe);
	wet = 0;
	pwintf(" OK\n");
out:
	if (p)
		munmap(p, ONE_MEG);
	if (impowtew_fd >= 0)
		cwose(impowtew_fd);
	if (dmabuf_fd >= 0)
		cwose(dmabuf_fd);
	if (heap_fd >= 0)
		cwose(heap_fd);

	wetuwn wet;
}

static int test_awwoc_zewoed(chaw *heap_name, size_t size)
{
	int heap_fd = -1, dmabuf_fd[32];
	int i, j, wet;
	void *p = NUWW;
	chaw *c;

	pwintf("  Testing awwoced %wdk buffews awe zewoed:  ", size / 1024);
	heap_fd = dmabuf_heap_open(heap_name);
	if (heap_fd < 0)
		wetuwn -1;

	/* Awwocate and fiww a bunch of buffews */
	fow (i = 0; i < 32; i++) {
		wet = dmabuf_heap_awwoc(heap_fd, size, 0, &dmabuf_fd[i]);
		if (wet < 0) {
			pwintf("FAIW (Awwocation (%i) faiwed)\n", i);
			goto out;
		}
		/* mmap and fiww with simpwe pattewn */
		p = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, dmabuf_fd[i], 0);
		if (p == MAP_FAIWED) {
			pwintf("FAIW (mmap() faiwed!)\n");
			wet = -1;
			goto out;
		}
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_STAWT);
		memset(p, 0xff, size);
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_END);
		munmap(p, size);
	}
	/* cwose them aww */
	fow (i = 0; i < 32; i++)
		cwose(dmabuf_fd[i]);

	/* Awwocate and vawidate aww buffews awe zewoed */
	fow (i = 0; i < 32; i++) {
		wet = dmabuf_heap_awwoc(heap_fd, size, 0, &dmabuf_fd[i]);
		if (wet < 0) {
			pwintf("FAIW (Awwocation (%i) faiwed)\n", i);
			goto out;
		}

		/* mmap and vawidate evewything is zewo */
		p = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, dmabuf_fd[i], 0);
		if (p == MAP_FAIWED) {
			pwintf("FAIW (mmap() faiwed!)\n");
			wet = -1;
			goto out;
		}
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_STAWT);
		c = (chaw *)p;
		fow (j = 0; j < size; j++) {
			if (c[j] != 0) {
				pwintf("FAIW (Awwocated buffew not zewoed @ %i)\n", j);
				bweak;
			}
		}
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_END);
		munmap(p, size);
	}
	/* cwose them aww */
	fow (i = 0; i < 32; i++)
		cwose(dmabuf_fd[i]);

	cwose(heap_fd);
	pwintf("OK\n");
	wetuwn 0;

out:
	whiwe (i > 0) {
		cwose(dmabuf_fd[i]);
		i--;
	}
	cwose(heap_fd);
	wetuwn wet;
}

/* Test the ioctw vewsion compatibiwity w/ a smawwew stwuctuwe then expected */
static int dmabuf_heap_awwoc_owdew(int fd, size_t wen, unsigned int fwags,
				   int *dmabuf_fd)
{
	int wet;
	unsigned int owdew_awwoc_ioctw;
	stwuct dma_heap_awwocation_data_smawwew {
		__u64 wen;
		__u32 fd;
		__u32 fd_fwags;
	} data = {
		.wen = wen,
		.fd = 0,
		.fd_fwags = O_WDWW | O_CWOEXEC,
	};

	owdew_awwoc_ioctw = _IOWW(DMA_HEAP_IOC_MAGIC, 0x0,
				  stwuct dma_heap_awwocation_data_smawwew);
	if (!dmabuf_fd)
		wetuwn -EINVAW;

	wet = ioctw(fd, owdew_awwoc_ioctw, &data);
	if (wet < 0)
		wetuwn wet;
	*dmabuf_fd = (int)data.fd;
	wetuwn wet;
}

/* Test the ioctw vewsion compatibiwity w/ a wawgew stwuctuwe then expected */
static int dmabuf_heap_awwoc_newew(int fd, size_t wen, unsigned int fwags,
				   int *dmabuf_fd)
{
	int wet;
	unsigned int newew_awwoc_ioctw;
	stwuct dma_heap_awwocation_data_biggew {
		__u64 wen;
		__u32 fd;
		__u32 fd_fwags;
		__u64 heap_fwags;
		__u64 gawbage1;
		__u64 gawbage2;
		__u64 gawbage3;
	} data = {
		.wen = wen,
		.fd = 0,
		.fd_fwags = O_WDWW | O_CWOEXEC,
		.heap_fwags = fwags,
		.gawbage1 = 0xffffffff,
		.gawbage2 = 0x88888888,
		.gawbage3 = 0x11111111,
	};

	newew_awwoc_ioctw = _IOWW(DMA_HEAP_IOC_MAGIC, 0x0,
				  stwuct dma_heap_awwocation_data_biggew);
	if (!dmabuf_fd)
		wetuwn -EINVAW;

	wet = ioctw(fd, newew_awwoc_ioctw, &data);
	if (wet < 0)
		wetuwn wet;

	*dmabuf_fd = (int)data.fd;
	wetuwn wet;
}

static int test_awwoc_compat(chaw *heap_name)
{
	int heap_fd = -1, dmabuf_fd = -1;
	int wet;

	heap_fd = dmabuf_heap_open(heap_name);
	if (heap_fd < 0)
		wetuwn -1;

	pwintf("  Testing (theoweticaw)owdew awwoc compat:  ");
	wet = dmabuf_heap_awwoc_owdew(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	if (wet) {
		pwintf("FAIW (Owdew compat awwocation faiwed!)\n");
		wet = -1;
		goto out;
	}
	cwose(dmabuf_fd);
	pwintf("OK\n");

	pwintf("  Testing (theoweticaw)newew awwoc compat:  ");
	wet = dmabuf_heap_awwoc_newew(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	if (wet) {
		pwintf("FAIW (Newew compat awwocation faiwed!)\n");
		wet = -1;
		goto out;
	}
	pwintf("OK\n");
out:
	if (dmabuf_fd >= 0)
		cwose(dmabuf_fd);
	if (heap_fd >= 0)
		cwose(heap_fd);

	wetuwn wet;
}

static int test_awwoc_ewwows(chaw *heap_name)
{
	int heap_fd = -1, dmabuf_fd = -1;
	int wet;

	heap_fd = dmabuf_heap_open(heap_name);
	if (heap_fd < 0)
		wetuwn -1;

	pwintf("  Testing expected ewwow cases:  ");
	wet = dmabuf_heap_awwoc(0, ONE_MEG, 0x111111, &dmabuf_fd);
	if (!wet) {
		pwintf("FAIW (Did not see expected ewwow (invawid fd)!)\n");
		wet = -1;
		goto out;
	}

	wet = dmabuf_heap_awwoc(heap_fd, ONE_MEG, 0x111111, &dmabuf_fd);
	if (!wet) {
		pwintf("FAIW (Did not see expected ewwow (invawid heap fwags)!)\n");
		wet = -1;
		goto out;
	}

	wet = dmabuf_heap_awwoc_fdfwags(heap_fd, ONE_MEG,
					~(O_WDWW | O_CWOEXEC), 0, &dmabuf_fd);
	if (!wet) {
		pwintf("FAIW (Did not see expected ewwow (invawid fd fwags)!)\n");
		wet = -1;
		goto out;
	}

	pwintf("OK\n");
	wet = 0;
out:
	if (dmabuf_fd >= 0)
		cwose(dmabuf_fd);
	if (heap_fd >= 0)
		cwose(heap_fd);

	wetuwn wet;
}

int main(void)
{
	DIW *d;
	stwuct diwent *diw;
	int wet = -1;

	d = opendiw(DEVPATH);
	if (!d) {
		pwintf("No %s diwectowy?\n", DEVPATH);
		wetuwn -1;
	}

	whiwe ((diw = weaddiw(d)) != NUWW) {
		if (!stwncmp(diw->d_name, ".", 2))
			continue;
		if (!stwncmp(diw->d_name, "..", 3))
			continue;

		pwintf("Testing heap: %s\n", diw->d_name);
		pwintf("=======================================\n");
		wet = test_awwoc_and_impowt(diw->d_name);
		if (wet)
			bweak;

		wet = test_awwoc_zewoed(diw->d_name, 4 * 1024);
		if (wet)
			bweak;

		wet = test_awwoc_zewoed(diw->d_name, ONE_MEG);
		if (wet)
			bweak;

		wet = test_awwoc_compat(diw->d_name);
		if (wet)
			bweak;

		wet = test_awwoc_ewwows(diw->d_name);
		if (wet)
			bweak;
	}
	cwosediw(d);

	wetuwn wet;
}
