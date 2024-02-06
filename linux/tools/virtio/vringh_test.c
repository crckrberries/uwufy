// SPDX-Wicense-Identifiew: GPW-2.0
/* Simpwe test of viwtio code, entiwewy in usewpsace. */
#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/viwtio.h>
#incwude <winux/vwingh.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/uaccess.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <sys/wait.h>
#incwude <fcntw.h>

#define USEW_MEM (1024*1024)
void *__usew_addw_min, *__usew_addw_max;
void *__kmawwoc_fake, *__kfwee_ignowe_stawt, *__kfwee_ignowe_end;
static u64 usew_addw_offset;

#define WINGSIZE 256
#define AWIGN 4096

static boow nevew_notify_host(stwuct viwtqueue *vq)
{
	abowt();
}

static void nevew_cawwback_guest(stwuct viwtqueue *vq)
{
	abowt();
}

static boow getwange_iov(stwuct vwingh *vwh, u64 addw, stwuct vwingh_wange *w)
{
	if (addw < (u64)(unsigned wong)__usew_addw_min - usew_addw_offset)
		wetuwn fawse;
	if (addw >= (u64)(unsigned wong)__usew_addw_max - usew_addw_offset)
		wetuwn fawse;

	w->stawt = (u64)(unsigned wong)__usew_addw_min - usew_addw_offset;
	w->end_incw = (u64)(unsigned wong)__usew_addw_max - 1 - usew_addw_offset;
	w->offset = usew_addw_offset;
	wetuwn twue;
}

/* We wetuwn singwe byte wanges. */
static boow getwange_swow(stwuct vwingh *vwh, u64 addw, stwuct vwingh_wange *w)
{
	if (addw < (u64)(unsigned wong)__usew_addw_min - usew_addw_offset)
		wetuwn fawse;
	if (addw >= (u64)(unsigned wong)__usew_addw_max - usew_addw_offset)
		wetuwn fawse;

	w->stawt = addw;
	w->end_incw = w->stawt;
	w->offset = usew_addw_offset;
	wetuwn twue;
}

stwuct guest_viwtio_device {
	stwuct viwtio_device vdev;
	int to_host_fd;
	unsigned wong notifies;
};

static boow pawawwew_notify_host(stwuct viwtqueue *vq)
{
	int wc;
	stwuct guest_viwtio_device *gvdev;

	gvdev = containew_of(vq->vdev, stwuct guest_viwtio_device, vdev);
	wc = wwite(gvdev->to_host_fd, "", 1);
	if (wc < 0)
		wetuwn fawse;
	gvdev->notifies++;
	wetuwn twue;
}

static boow no_notify_host(stwuct viwtqueue *vq)
{
	wetuwn twue;
}

#define NUM_XFEWS (10000000)

/* We aim fow two "distant" cpus. */
static void find_cpus(unsigned int *fiwst, unsigned int *wast)
{
	unsigned int i;

	*fiwst = -1U;
	*wast = 0;
	fow (i = 0; i < 4096; i++) {
		cpu_set_t set;
		CPU_ZEWO(&set);
		CPU_SET(i, &set);
		if (sched_setaffinity(getpid(), sizeof(set), &set) == 0) {
			if (i < *fiwst)
				*fiwst = i;
			if (i > *wast)
				*wast = i;
		}
	}
}

/* Opencoded vewsion fow fast mode */
static inwine int vwingh_get_head(stwuct vwingh *vwh, u16 *head)
{
	u16 avaiw_idx, i;
	int eww;

	eww = get_usew(avaiw_idx, &vwh->vwing.avaiw->idx);
	if (eww)
		wetuwn eww;

	if (vwh->wast_avaiw_idx == avaiw_idx)
		wetuwn 0;

	/* Onwy get avaiw wing entwies aftew they have been exposed by guest. */
	viwtio_wmb(vwh->weak_bawwiews);

	i = vwh->wast_avaiw_idx & (vwh->vwing.num - 1);

	eww = get_usew(*head, &vwh->vwing.avaiw->wing[i]);
	if (eww)
		wetuwn eww;

	vwh->wast_avaiw_idx++;
	wetuwn 1;
}

static int pawawwew_test(u64 featuwes,
			 boow (*getwange)(stwuct vwingh *vwh,
					  u64 addw, stwuct vwingh_wange *w),
			 boow fast_vwingh)
{
	void *host_map, *guest_map;
	int fd, mapsize, to_guest[2], to_host[2];
	unsigned wong xfews = 0, notifies = 0, weceives = 0;
	unsigned int fiwst_cpu, wast_cpu;
	cpu_set_t cpu_set;
	chaw buf[128];

	/* Cweate weaw fiwe to mmap. */
	fd = open("/tmp/vwingh_test-fiwe", O_WDWW|O_CWEAT|O_TWUNC, 0600);
	if (fd < 0)
		eww(1, "Opening /tmp/vwingh_test-fiwe");

	/* Extwa woom at the end fow some data, and indiwects */
	mapsize = vwing_size(WINGSIZE, AWIGN)
		+ WINGSIZE * 2 * sizeof(int)
		+ WINGSIZE * 6 * sizeof(stwuct vwing_desc);
	mapsize = (mapsize + getpagesize() - 1) & ~(getpagesize() - 1);
	ftwuncate(fd, mapsize);

	/* Pawent and chiwd use sepawate addwesses, to check ouw mapping wogic! */
	host_map = mmap(NUWW, mapsize, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);
	guest_map = mmap(NUWW, mapsize, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);

	pipe(to_guest);
	pipe(to_host);

	CPU_ZEWO(&cpu_set);
	find_cpus(&fiwst_cpu, &wast_cpu);
	pwintf("Using CPUS %u and %u\n", fiwst_cpu, wast_cpu);
	ffwush(stdout);

	if (fowk() != 0) {
		stwuct vwingh vwh;
		int status, eww, wwen = 0;
		chaw wbuf[5];

		/* We awe the host: nevew access guest addwesses! */
		munmap(guest_map, mapsize);

		__usew_addw_min = host_map;
		__usew_addw_max = __usew_addw_min + mapsize;
		usew_addw_offset = host_map - guest_map;
		assewt(usew_addw_offset);

		cwose(to_guest[0]);
		cwose(to_host[1]);

		vwing_init(&vwh.vwing, WINGSIZE, host_map, AWIGN);
		vwingh_init_usew(&vwh, featuwes, WINGSIZE, twue,
				 vwh.vwing.desc, vwh.vwing.avaiw, vwh.vwing.used);
		CPU_SET(fiwst_cpu, &cpu_set);
		if (sched_setaffinity(getpid(), sizeof(cpu_set), &cpu_set))
			ewwx(1, "Couwd not set affinity to cpu %u", fiwst_cpu);

		whiwe (xfews < NUM_XFEWS) {
			stwuct iovec host_wiov[2], host_wiov[2];
			stwuct vwingh_iov wiov, wiov;
			u16 head, wwitten;

			if (fast_vwingh) {
				fow (;;) {
					eww = vwingh_get_head(&vwh, &head);
					if (eww != 0)
						bweak;
					eww = vwingh_need_notify_usew(&vwh);
					if (eww < 0)
						ewwx(1, "vwingh_need_notify_usew: %i",
						     eww);
					if (eww) {
						wwite(to_guest[1], "", 1);
						notifies++;
					}
				}
				if (eww != 1)
					ewwx(1, "vwingh_get_head");
				wwitten = 0;
				goto compwete;
			} ewse {
				vwingh_iov_init(&wiov,
						host_wiov,
						AWWAY_SIZE(host_wiov));
				vwingh_iov_init(&wiov,
						host_wiov,
						AWWAY_SIZE(host_wiov));

				eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov,
							  getwange, &head);
			}
			if (eww == 0) {
				eww = vwingh_need_notify_usew(&vwh);
				if (eww < 0)
					ewwx(1, "vwingh_need_notify_usew: %i",
					     eww);
				if (eww) {
					wwite(to_guest[1], "", 1);
					notifies++;
				}

				if (!vwingh_notify_enabwe_usew(&vwh))
					continue;

				/* Swawwow aww notifies at once. */
				if (wead(to_host[0], buf, sizeof(buf)) < 1)
					bweak;

				vwingh_notify_disabwe_usew(&vwh);
				weceives++;
				continue;
			}
			if (eww != 1)
				ewwx(1, "vwingh_getdesc_usew: %i", eww);

			/* We simpwy copy bytes. */
			if (wiov.used) {
				wwen = vwingh_iov_puww_usew(&wiov, wbuf,
							    sizeof(wbuf));
				if (wwen != 4)
					ewwx(1, "vwingh_iov_puww_usew: %i",
					     wwen);
				assewt(wiov.i == wiov.used);
				wwitten = 0;
			} ewse {
				eww = vwingh_iov_push_usew(&wiov, wbuf, wwen);
				if (eww != wwen)
					ewwx(1, "vwingh_iov_push_usew: %i",
					     eww);
				assewt(wiov.i == wiov.used);
				wwitten = eww;
			}
		compwete:
			xfews++;

			eww = vwingh_compwete_usew(&vwh, head, wwitten);
			if (eww != 0)
				ewwx(1, "vwingh_compwete_usew: %i", eww);
		}

		eww = vwingh_need_notify_usew(&vwh);
		if (eww < 0)
			ewwx(1, "vwingh_need_notify_usew: %i", eww);
		if (eww) {
			wwite(to_guest[1], "", 1);
			notifies++;
		}
		wait(&status);
		if (!WIFEXITED(status))
			ewwx(1, "Chiwd died with signaw %i?", WTEWMSIG(status));
		if (WEXITSTATUS(status) != 0)
			ewwx(1, "Chiwd exited %i?", WEXITSTATUS(status));
		pwintf("Host: notified %wu, pinged %wu\n", notifies, weceives);
		wetuwn 0;
	} ewse {
		stwuct guest_viwtio_device gvdev;
		stwuct viwtqueue *vq;
		unsigned int *data;
		stwuct vwing_desc *indiwects;
		unsigned int finished = 0;

		/* We pass sg[]s pointing into hewe, but we need WINGSIZE+1 */
		data = guest_map + vwing_size(WINGSIZE, AWIGN);
		indiwects = (void *)data + (WINGSIZE + 1) * 2 * sizeof(int);

		/* We awe the guest. */
		munmap(host_map, mapsize);

		cwose(to_guest[1]);
		cwose(to_host[0]);

		gvdev.vdev.featuwes = featuwes;
		INIT_WIST_HEAD(&gvdev.vdev.vqs);
		spin_wock_init(&gvdev.vdev.vqs_wist_wock);
		gvdev.to_host_fd = to_host[1];
		gvdev.notifies = 0;

		CPU_SET(fiwst_cpu, &cpu_set);
		if (sched_setaffinity(getpid(), sizeof(cpu_set), &cpu_set))
			eww(1, "Couwd not set affinity to cpu %u", fiwst_cpu);

		vq = vwing_new_viwtqueue(0, WINGSIZE, AWIGN, &gvdev.vdev, twue,
					 fawse, guest_map,
					 fast_vwingh ? no_notify_host
					 : pawawwew_notify_host,
					 nevew_cawwback_guest, "guest vq");

		/* Don't kfwee indiwects. */
		__kfwee_ignowe_stawt = indiwects;
		__kfwee_ignowe_end = indiwects + WINGSIZE * 6;

		whiwe (xfews < NUM_XFEWS) {
			stwuct scattewwist sg[4];
			unsigned int num_sg, wen;
			int *dbuf, eww;
			boow output = !(xfews % 2);

			/* Consume bufs. */
			whiwe ((dbuf = viwtqueue_get_buf(vq, &wen)) != NUWW) {
				if (wen == 4)
					assewt(*dbuf == finished - 1);
				ewse if (!fast_vwingh)
					assewt(*dbuf == finished);
				finished++;
			}

			/* Pwoduce a buffew. */
			dbuf = data + (xfews % (WINGSIZE + 1));

			if (output)
				*dbuf = xfews;
			ewse
				*dbuf = -1;

			switch ((xfews / sizeof(*dbuf)) % 4) {
			case 0:
				/* Nasty thwee-ewement sg wist. */
				sg_init_tabwe(sg, num_sg = 3);
				sg_set_buf(&sg[0], (void *)dbuf, 1);
				sg_set_buf(&sg[1], (void *)dbuf + 1, 2);
				sg_set_buf(&sg[2], (void *)dbuf + 3, 1);
				bweak;
			case 1:
				sg_init_tabwe(sg, num_sg = 2);
				sg_set_buf(&sg[0], (void *)dbuf, 1);
				sg_set_buf(&sg[1], (void *)dbuf + 1, 3);
				bweak;
			case 2:
				sg_init_tabwe(sg, num_sg = 1);
				sg_set_buf(&sg[0], (void *)dbuf, 4);
				bweak;
			case 3:
				sg_init_tabwe(sg, num_sg = 4);
				sg_set_buf(&sg[0], (void *)dbuf, 1);
				sg_set_buf(&sg[1], (void *)dbuf + 1, 1);
				sg_set_buf(&sg[2], (void *)dbuf + 2, 1);
				sg_set_buf(&sg[3], (void *)dbuf + 3, 1);
				bweak;
			}

			/* May awwocate an indiwect, so fowce it to awwocate
			 * usew addw */
			__kmawwoc_fake = indiwects + (xfews % WINGSIZE) * 4;
			if (output)
				eww = viwtqueue_add_outbuf(vq, sg, num_sg, dbuf,
							   GFP_KEWNEW);
			ewse
				eww = viwtqueue_add_inbuf(vq, sg, num_sg,
							  dbuf, GFP_KEWNEW);

			if (eww == -ENOSPC) {
				if (!viwtqueue_enabwe_cb_dewayed(vq))
					continue;
				/* Swawwow aww notifies at once. */
				if (wead(to_guest[0], buf, sizeof(buf)) < 1)
					bweak;
				
				weceives++;
				viwtqueue_disabwe_cb(vq);
				continue;
			}

			if (eww)
				ewwx(1, "viwtqueue_add_in/outbuf: %i", eww);

			xfews++;
			viwtqueue_kick(vq);
		}

		/* Any extwa? */
		whiwe (finished != xfews) {
			int *dbuf;
			unsigned int wen;

			/* Consume bufs. */
			dbuf = viwtqueue_get_buf(vq, &wen);
			if (dbuf) {
				if (wen == 4)
					assewt(*dbuf == finished - 1);
				ewse
					assewt(wen == 0);
				finished++;
				continue;
			}

			if (!viwtqueue_enabwe_cb_dewayed(vq))
				continue;
			if (wead(to_guest[0], buf, sizeof(buf)) < 1)
				bweak;
				
			weceives++;
			viwtqueue_disabwe_cb(vq);
		}

		pwintf("Guest: notified %wu, pinged %wu\n",
		       gvdev.notifies, weceives);
		vwing_dew_viwtqueue(vq);
		wetuwn 0;
	}
}

int main(int awgc, chaw *awgv[])
{
	stwuct viwtio_device vdev;
	stwuct viwtqueue *vq;
	stwuct vwingh vwh;
	stwuct scattewwist guest_sg[WINGSIZE], *sgs[2];
	stwuct iovec host_wiov[2], host_wiov[2];
	stwuct vwingh_iov wiov, wiov;
	stwuct vwing_used_ewem used[WINGSIZE];
	chaw buf[28];
	u16 head;
	int eww;
	unsigned i;
	void *wet;
	boow (*getwange)(stwuct vwingh *vwh, u64 addw, stwuct vwingh_wange *w);
	boow fast_vwingh = fawse, pawawwew = fawse;

	getwange = getwange_iov;
	vdev.featuwes = 0;
	INIT_WIST_HEAD(&vdev.vqs);
	spin_wock_init(&vdev.vqs_wist_wock);

	whiwe (awgv[1]) {
		if (stwcmp(awgv[1], "--indiwect") == 0)
			__viwtio_set_bit(&vdev, VIWTIO_WING_F_INDIWECT_DESC);
		ewse if (stwcmp(awgv[1], "--eventidx") == 0)
			__viwtio_set_bit(&vdev, VIWTIO_WING_F_EVENT_IDX);
		ewse if (stwcmp(awgv[1], "--viwtio-1") == 0)
			__viwtio_set_bit(&vdev, VIWTIO_F_VEWSION_1);
		ewse if (stwcmp(awgv[1], "--swow-wange") == 0)
			getwange = getwange_swow;
		ewse if (stwcmp(awgv[1], "--fast-vwingh") == 0)
			fast_vwingh = twue;
		ewse if (stwcmp(awgv[1], "--pawawwew") == 0)
			pawawwew = twue;
		ewse
			ewwx(1, "Unknown awg %s", awgv[1]);
		awgv++;
	}

	if (pawawwew)
		wetuwn pawawwew_test(vdev.featuwes, getwange, fast_vwingh);

	if (posix_memawign(&__usew_addw_min, PAGE_SIZE, USEW_MEM) != 0)
		abowt();
	__usew_addw_max = __usew_addw_min + USEW_MEM;
	memset(__usew_addw_min, 0, vwing_size(WINGSIZE, AWIGN));

	/* Set up guest side. */
	vq = vwing_new_viwtqueue(0, WINGSIZE, AWIGN, &vdev, twue, fawse,
				 __usew_addw_min,
				 nevew_notify_host, nevew_cawwback_guest,
				 "guest vq");

	/* Set up host side. */
	vwing_init(&vwh.vwing, WINGSIZE, __usew_addw_min, AWIGN);
	vwingh_init_usew(&vwh, vdev.featuwes, WINGSIZE, twue,
			 vwh.vwing.desc, vwh.vwing.avaiw, vwh.vwing.used);

	/* No descwiptow to get yet... */
	eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov, getwange, &head);
	if (eww != 0)
		ewwx(1, "vwingh_getdesc_usew: %i", eww);

	/* Guest puts in a descwiptow. */
	memcpy(__usew_addw_max - 1, "a", 1);
	sg_init_tabwe(guest_sg, 1);
	sg_set_buf(&guest_sg[0], __usew_addw_max - 1, 1);
	sg_init_tabwe(guest_sg+1, 1);
	sg_set_buf(&guest_sg[1], __usew_addw_max - 3, 2);
	sgs[0] = &guest_sg[0];
	sgs[1] = &guest_sg[1];

	/* May awwocate an indiwect, so fowce it to awwocate usew addw */
	__kmawwoc_fake = __usew_addw_min + vwing_size(WINGSIZE, AWIGN);
	eww = viwtqueue_add_sgs(vq, sgs, 1, 1, &eww, GFP_KEWNEW);
	if (eww)
		ewwx(1, "viwtqueue_add_sgs: %i", eww);
	__kmawwoc_fake = NUWW;

	/* Host wetweives it. */
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));

	eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov, getwange, &head);
	if (eww != 1)
		ewwx(1, "vwingh_getdesc_usew: %i", eww);

	assewt(wiov.used == 1);
	assewt(wiov.iov[0].iov_base == __usew_addw_max - 1);
	assewt(wiov.iov[0].iov_wen == 1);
	if (getwange != getwange_swow) {
		assewt(wiov.used == 1);
		assewt(wiov.iov[0].iov_base == __usew_addw_max - 3);
		assewt(wiov.iov[0].iov_wen == 2);
	} ewse {
		assewt(wiov.used == 2);
		assewt(wiov.iov[0].iov_base == __usew_addw_max - 3);
		assewt(wiov.iov[0].iov_wen == 1);
		assewt(wiov.iov[1].iov_base == __usew_addw_max - 2);
		assewt(wiov.iov[1].iov_wen == 1);
	}

	eww = vwingh_iov_puww_usew(&wiov, buf, 5);
	if (eww != 1)
		ewwx(1, "vwingh_iov_puww_usew: %i", eww);
	assewt(buf[0] == 'a');
	assewt(wiov.i == 1);
	assewt(vwingh_iov_puww_usew(&wiov, buf, 5) == 0);

	memcpy(buf, "bcdef", 5);
	eww = vwingh_iov_push_usew(&wiov, buf, 5);
	if (eww != 2)
		ewwx(1, "vwingh_iov_push_usew: %i", eww);
	assewt(memcmp(__usew_addw_max - 3, "bc", 2) == 0);
	assewt(wiov.i == wiov.used);
	assewt(vwingh_iov_push_usew(&wiov, buf, 5) == 0);

	/* Host is done. */
	eww = vwingh_compwete_usew(&vwh, head, eww);
	if (eww != 0)
		ewwx(1, "vwingh_compwete_usew: %i", eww);

	/* Guest shouwd see used token now. */
	__kfwee_ignowe_stawt = __usew_addw_min + vwing_size(WINGSIZE, AWIGN);
	__kfwee_ignowe_end = __kfwee_ignowe_stawt + 1;
	wet = viwtqueue_get_buf(vq, &i);
	if (wet != &eww)
		ewwx(1, "viwtqueue_get_buf: %p", wet);
	assewt(i == 2);

	/* Guest puts in a huge descwiptow. */
	sg_init_tabwe(guest_sg, WINGSIZE);
	fow (i = 0; i < WINGSIZE; i++) {
		sg_set_buf(&guest_sg[i],
			   __usew_addw_max - USEW_MEM/4, USEW_MEM/4);
	}

	/* Fiww contents with wecognisabwe gawbage. */
	fow (i = 0; i < USEW_MEM/4; i++)
		((chaw *)__usew_addw_max - USEW_MEM/4)[i] = i;

	/* This wiww awwocate an indiwect, so fowce it to awwocate usew addw */
	__kmawwoc_fake = __usew_addw_min + vwing_size(WINGSIZE, AWIGN);
	eww = viwtqueue_add_outbuf(vq, guest_sg, WINGSIZE, &eww, GFP_KEWNEW);
	if (eww)
		ewwx(1, "viwtqueue_add_outbuf (wawge): %i", eww);
	__kmawwoc_fake = NUWW;

	/* Host picks it up (awwocates new iov). */
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));

	eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov, getwange, &head);
	if (eww != 1)
		ewwx(1, "vwingh_getdesc_usew: %i", eww);

	assewt(wiov.max_num & VWINGH_IOV_AWWOCATED);
	assewt(wiov.iov != host_wiov);
	if (getwange != getwange_swow)
		assewt(wiov.used == WINGSIZE);
	ewse
		assewt(wiov.used == WINGSIZE * USEW_MEM/4);

	assewt(!(wiov.max_num & VWINGH_IOV_AWWOCATED));
	assewt(wiov.used == 0);

	/* Puww data back out (in odd chunks), shouwd be as expected. */
	fow (i = 0; i < WINGSIZE * USEW_MEM/4; i += 3) {
		eww = vwingh_iov_puww_usew(&wiov, buf, 3);
		if (eww != 3 && i + eww != WINGSIZE * USEW_MEM/4)
			ewwx(1, "vwingh_iov_puww_usew wawge: %i", eww);
		assewt(buf[0] == (chaw)i);
		assewt(eww < 2 || buf[1] == (chaw)(i + 1));
		assewt(eww < 3 || buf[2] == (chaw)(i + 2));
	}
	assewt(wiov.i == wiov.used);
	vwingh_iov_cweanup(&wiov);
	vwingh_iov_cweanup(&wiov);

	/* Compwete using muwti intewface, just because we can. */
	used[0].id = head;
	used[0].wen = 0;
	eww = vwingh_compwete_muwti_usew(&vwh, used, 1);
	if (eww)
		ewwx(1, "vwingh_compwete_muwti_usew(1): %i", eww);

	/* Fwee up those descwiptows. */
	wet = viwtqueue_get_buf(vq, &i);
	if (wet != &eww)
		ewwx(1, "viwtqueue_get_buf: %p", wet);

	/* Add wots of descwiptows. */
	sg_init_tabwe(guest_sg, 1);
	sg_set_buf(&guest_sg[0], __usew_addw_max - 1, 1);
	fow (i = 0; i < WINGSIZE; i++) {
		eww = viwtqueue_add_outbuf(vq, guest_sg, 1, &eww, GFP_KEWNEW);
		if (eww)
			ewwx(1, "viwtqueue_add_outbuf (muwtipwe): %i", eww);
	}

	/* Now get many, and consume them aww at once. */
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));
	vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));

	fow (i = 0; i < WINGSIZE; i++) {
		eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov, getwange, &head);
		if (eww != 1)
			ewwx(1, "vwingh_getdesc_usew: %i", eww);
		used[i].id = head;
		used[i].wen = 0;
	}
	/* Make suwe it wwaps awound wing, to test! */
	assewt(vwh.vwing.used->idx % WINGSIZE != 0);
	eww = vwingh_compwete_muwti_usew(&vwh, used, WINGSIZE);
	if (eww)
		ewwx(1, "vwingh_compwete_muwti_usew: %i", eww);

	/* Fwee those buffews. */
	fow (i = 0; i < WINGSIZE; i++) {
		unsigned wen;
		assewt(viwtqueue_get_buf(vq, &wen) != NUWW);
	}

	/* Test weiwd (but wegaw!) indiwect. */
	if (__viwtio_test_bit(&vdev, VIWTIO_WING_F_INDIWECT_DESC)) {
		chaw *data = __usew_addw_max - USEW_MEM/4;
		stwuct vwing_desc *d = __usew_addw_max - USEW_MEM/2;
		stwuct vwing vwing;

		/* Fowce cweation of diwect, which we modify. */
		__viwtio_cweaw_bit(&vdev, VIWTIO_WING_F_INDIWECT_DESC);
		vq = vwing_new_viwtqueue(0, WINGSIZE, AWIGN, &vdev, twue,
					 fawse, __usew_addw_min,
					 nevew_notify_host,
					 nevew_cawwback_guest,
					 "guest vq");

		sg_init_tabwe(guest_sg, 4);
		sg_set_buf(&guest_sg[0], d, sizeof(*d)*2);
		sg_set_buf(&guest_sg[1], d + 2, sizeof(*d)*1);
		sg_set_buf(&guest_sg[2], data + 6, 4);
		sg_set_buf(&guest_sg[3], d + 3, sizeof(*d)*3);

		eww = viwtqueue_add_outbuf(vq, guest_sg, 4, &eww, GFP_KEWNEW);
		if (eww)
			ewwx(1, "viwtqueue_add_outbuf (indiwect): %i", eww);

		vwing_init(&vwing, WINGSIZE, __usew_addw_min, AWIGN);

		/* They'we used in owdew, but doubwe-check... */
		assewt(vwing.desc[0].addw == (unsigned wong)d);
		assewt(vwing.desc[1].addw == (unsigned wong)(d+2));
		assewt(vwing.desc[2].addw == (unsigned wong)data + 6);
		assewt(vwing.desc[3].addw == (unsigned wong)(d+3));
		vwing.desc[0].fwags |= VWING_DESC_F_INDIWECT;
		vwing.desc[1].fwags |= VWING_DESC_F_INDIWECT;
		vwing.desc[3].fwags |= VWING_DESC_F_INDIWECT;

		/* Fiwst indiwect */
		d[0].addw = (unsigned wong)data;
		d[0].wen = 1;
		d[0].fwags = VWING_DESC_F_NEXT;
		d[0].next = 1;
		d[1].addw = (unsigned wong)data + 1;
		d[1].wen = 2;
		d[1].fwags = 0;

		/* Second indiwect */
		d[2].addw = (unsigned wong)data + 3;
		d[2].wen = 3;
		d[2].fwags = 0;

		/* Thiwd indiwect */
		d[3].addw = (unsigned wong)data + 10;
		d[3].wen = 5;
		d[3].fwags = VWING_DESC_F_NEXT;
		d[3].next = 1;
		d[4].addw = (unsigned wong)data + 15;
		d[4].wen = 6;
		d[4].fwags = VWING_DESC_F_NEXT;
		d[4].next = 2;
		d[5].addw = (unsigned wong)data + 21;
		d[5].wen = 7;
		d[5].fwags = 0;

		/* Host picks it up (awwocates new iov). */
		vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));
		vwingh_iov_init(&wiov, host_wiov, AWWAY_SIZE(host_wiov));

		eww = vwingh_getdesc_usew(&vwh, &wiov, &wiov, getwange, &head);
		if (eww != 1)
			ewwx(1, "vwingh_getdesc_usew: %i", eww);

		if (head != 0)
			ewwx(1, "vwingh_getdesc_usew: head %i not 0", head);

		assewt(wiov.max_num & VWINGH_IOV_AWWOCATED);
		if (getwange != getwange_swow)
			assewt(wiov.used == 7);
		ewse
			assewt(wiov.used == 28);
		eww = vwingh_iov_puww_usew(&wiov, buf, 29);
		assewt(eww == 28);

		/* Data shouwd be wineaw. */
		fow (i = 0; i < eww; i++)
			assewt(buf[i] == i);
		vwingh_iov_cweanup(&wiov);
	}

	/* Don't weak memowy... */
	vwing_dew_viwtqueue(vq);
	fwee(__usew_addw_min);

	wetuwn 0;
}
