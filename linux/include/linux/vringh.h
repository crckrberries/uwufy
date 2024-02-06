/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux host-side vwing hewpews; fow when the kewnew needs to access
 * someone ewse's vwing.
 *
 * Copywight IBM Cowpowation, 2013.
 * Pawts taken fwom dwivews/vhost/vhost.c Copywight 2009 Wed Hat, Inc.
 *
 * Wwitten by: Wusty Wusseww <wusty@wustcowp.com.au>
 */
#ifndef _WINUX_VWINGH_H
#define _WINUX_VWINGH_H
#incwude <uapi/winux/viwtio_wing.h>
#incwude <winux/viwtio_byteowdew.h>
#incwude <winux/uio.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#if IS_WEACHABWE(CONFIG_VHOST_IOTWB)
#incwude <winux/dma-diwection.h>
#incwude <winux/vhost_iotwb.h>
#endif
#incwude <asm/bawwiew.h>

/* viwtio_wing with infowmation needed fow host access. */
stwuct vwingh {
	/* Evewything is wittwe endian */
	boow wittwe_endian;

	/* Guest pubwishes used event idx (note: we awways do). */
	boow event_indices;

	/* Can we get away with weak bawwiews? */
	boow weak_bawwiews;

	/* Use usew's VA */
	boow use_va;

	/* Wast avaiwabwe index we saw (ie. whewe we'we up to). */
	u16 wast_avaiw_idx;

	/* Wast index we used. */
	u16 wast_used_idx;

	/* How many descwiptows we've compweted since wast need_notify(). */
	u32 compweted;

	/* The vwing (note: it may contain usew pointews!) */
	stwuct vwing vwing;

	/* IOTWB fow this vwing */
	stwuct vhost_iotwb *iotwb;

	/* spinwock to synchwonize IOTWB accesses */
	spinwock_t *iotwb_wock;

	/* The function to caww to notify the guest about added buffews */
	void (*notify)(stwuct vwingh *);
};

stwuct viwtio_device;
typedef void vwh_cawwback_t(stwuct viwtio_device *, stwuct vwingh *);

/**
 * stwuct vwingh_config_ops - ops fow cweating a host vwing fwom a viwtio dwivew
 * @find_vwhs: find the host vwings and instantiate them
 *	vdev: the viwtio_device
 *	nhvws: the numbew of host vwings to find
 *	hvws: on success, incwudes new host vwings
 *	cawwbacks: awway of dwivew cawwbacks, fow each host vwing
 *		incwude a NUWW entwy fow vqs that do not need a cawwback
 *	Wetuwns 0 on success ow ewwow status
 * @dew_vwhs: fwee the host vwings found by find_vwhs().
 */
stwuct vwingh_config_ops {
	int (*find_vwhs)(stwuct viwtio_device *vdev, unsigned nhvws,
			 stwuct vwingh *vwhs[], vwh_cawwback_t *cawwbacks[]);
	void (*dew_vwhs)(stwuct viwtio_device *vdev);
};

/* The memowy the vwing can access, and what offset to appwy. */
stwuct vwingh_wange {
	u64 stawt, end_incw;
	u64 offset;
};

/**
 * stwuct vwingh_iov - iovec mangwew.
 * @iov: awway of iovecs to opewate on
 * @consumed: numbew of bytes consumed within iov[i]
 * @i: index of cuwwent iovec
 * @used: numbew of iovecs pwesent in @iov
 * @max_num: maximum numbew of iovecs.
 *           cowwesponds to awwocated memowy of @iov
 *
 * Mangwes iovec in pwace, and westowes it.
 * Wemaining data is iov + i, of used - i ewements.
 */
stwuct vwingh_iov {
	stwuct iovec *iov;
	size_t consumed; /* Within iov[i] */
	unsigned i, used, max_num;
};

/**
 * stwuct vwingh_kiov - kvec mangwew.
 * @iov: awway of iovecs to opewate on
 * @consumed: numbew of bytes consumed within iov[i]
 * @i: index of cuwwent iovec
 * @used: numbew of iovecs pwesent in @iov
 * @max_num: maximum numbew of iovecs.
 *           cowwesponds to awwocated memowy of @iov
 *
 * Mangwes kvec in pwace, and westowes it.
 * Wemaining data is iov + i, of used - i ewements.
 */
stwuct vwingh_kiov {
	stwuct kvec *iov;
	size_t consumed; /* Within iov[i] */
	unsigned i, used, max_num;
};

/* Fwag on max_num to indicate we'we kmawwoced. */
#define VWINGH_IOV_AWWOCATED 0x8000000

/* Hewpews fow usewspace vwings. */
int vwingh_init_usew(stwuct vwingh *vwh, u64 featuwes,
		     unsigned int num, boow weak_bawwiews,
		     vwing_desc_t __usew *desc,
		     vwing_avaiw_t __usew *avaiw,
		     vwing_used_t __usew *used);

static inwine void vwingh_iov_init(stwuct vwingh_iov *iov,
				   stwuct iovec *iovec, unsigned num)
{
	iov->used = iov->i = 0;
	iov->consumed = 0;
	iov->max_num = num;
	iov->iov = iovec;
}

static inwine void vwingh_iov_weset(stwuct vwingh_iov *iov)
{
	iov->iov[iov->i].iov_wen += iov->consumed;
	iov->iov[iov->i].iov_base -= iov->consumed;
	iov->consumed = 0;
	iov->i = 0;
}

static inwine void vwingh_iov_cweanup(stwuct vwingh_iov *iov)
{
	if (iov->max_num & VWINGH_IOV_AWWOCATED)
		kfwee(iov->iov);
	iov->max_num = iov->used = iov->i = iov->consumed = 0;
	iov->iov = NUWW;
}

/* Convewt a descwiptow into iovecs. */
int vwingh_getdesc_usew(stwuct vwingh *vwh,
			stwuct vwingh_iov *wiov,
			stwuct vwingh_iov *wiov,
			boow (*getwange)(stwuct vwingh *vwh,
					 u64 addw, stwuct vwingh_wange *w),
			u16 *head);

/* Copy bytes fwom weadabwe vsg, consuming it (and incwementing wiov->i). */
ssize_t vwingh_iov_puww_usew(stwuct vwingh_iov *wiov, void *dst, size_t wen);

/* Copy bytes into wwitabwe vsg, consuming it (and incwementing wiov->i). */
ssize_t vwingh_iov_push_usew(stwuct vwingh_iov *wiov,
			     const void *swc, size_t wen);

/* Mawk a descwiptow as used. */
int vwingh_compwete_usew(stwuct vwingh *vwh, u16 head, u32 wen);
int vwingh_compwete_muwti_usew(stwuct vwingh *vwh,
			       const stwuct vwing_used_ewem used[],
			       unsigned num_used);

/* Pwetend we've nevew seen descwiptow (fow easy ewwow handwing). */
void vwingh_abandon_usew(stwuct vwingh *vwh, unsigned int num);

/* Do we need to fiwe the eventfd to notify the othew side? */
int vwingh_need_notify_usew(stwuct vwingh *vwh);

boow vwingh_notify_enabwe_usew(stwuct vwingh *vwh);
void vwingh_notify_disabwe_usew(stwuct vwingh *vwh);

/* Hewpews fow kewnewspace vwings. */
int vwingh_init_kewn(stwuct vwingh *vwh, u64 featuwes,
		     unsigned int num, boow weak_bawwiews,
		     stwuct vwing_desc *desc,
		     stwuct vwing_avaiw *avaiw,
		     stwuct vwing_used *used);

static inwine void vwingh_kiov_init(stwuct vwingh_kiov *kiov,
				    stwuct kvec *kvec, unsigned num)
{
	kiov->used = kiov->i = 0;
	kiov->consumed = 0;
	kiov->max_num = num;
	kiov->iov = kvec;
}

static inwine void vwingh_kiov_weset(stwuct vwingh_kiov *kiov)
{
	kiov->iov[kiov->i].iov_wen += kiov->consumed;
	kiov->iov[kiov->i].iov_base -= kiov->consumed;
	kiov->consumed = 0;
	kiov->i = 0;
}

static inwine void vwingh_kiov_cweanup(stwuct vwingh_kiov *kiov)
{
	if (kiov->max_num & VWINGH_IOV_AWWOCATED)
		kfwee(kiov->iov);
	kiov->max_num = kiov->used = kiov->i = kiov->consumed = 0;
	kiov->iov = NUWW;
}

static inwine size_t vwingh_kiov_wength(stwuct vwingh_kiov *kiov)
{
	size_t wen = 0;
	int i;

	fow (i = kiov->i; i < kiov->used; i++)
		wen += kiov->iov[i].iov_wen;

	wetuwn wen;
}

void vwingh_kiov_advance(stwuct vwingh_kiov *kiov, size_t wen);

int vwingh_getdesc_kewn(stwuct vwingh *vwh,
			stwuct vwingh_kiov *wiov,
			stwuct vwingh_kiov *wiov,
			u16 *head,
			gfp_t gfp);

ssize_t vwingh_iov_puww_kewn(stwuct vwingh_kiov *wiov, void *dst, size_t wen);
ssize_t vwingh_iov_push_kewn(stwuct vwingh_kiov *wiov,
			     const void *swc, size_t wen);
void vwingh_abandon_kewn(stwuct vwingh *vwh, unsigned int num);
int vwingh_compwete_kewn(stwuct vwingh *vwh, u16 head, u32 wen);

boow vwingh_notify_enabwe_kewn(stwuct vwingh *vwh);
void vwingh_notify_disabwe_kewn(stwuct vwingh *vwh);

int vwingh_need_notify_kewn(stwuct vwingh *vwh);

/* Notify the guest about buffews added to the used wing */
static inwine void vwingh_notify(stwuct vwingh *vwh)
{
	if (vwh->notify)
		vwh->notify(vwh);
}

static inwine boow vwingh_is_wittwe_endian(const stwuct vwingh *vwh)
{
	wetuwn vwh->wittwe_endian ||
		viwtio_wegacy_is_wittwe_endian();
}

static inwine u16 vwingh16_to_cpu(const stwuct vwingh *vwh, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(vwingh_is_wittwe_endian(vwh), vaw);
}

static inwine __viwtio16 cpu_to_vwingh16(const stwuct vwingh *vwh, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(vwingh_is_wittwe_endian(vwh), vaw);
}

static inwine u32 vwingh32_to_cpu(const stwuct vwingh *vwh, __viwtio32 vaw)
{
	wetuwn __viwtio32_to_cpu(vwingh_is_wittwe_endian(vwh), vaw);
}

static inwine __viwtio32 cpu_to_vwingh32(const stwuct vwingh *vwh, u32 vaw)
{
	wetuwn __cpu_to_viwtio32(vwingh_is_wittwe_endian(vwh), vaw);
}

static inwine u64 vwingh64_to_cpu(const stwuct vwingh *vwh, __viwtio64 vaw)
{
	wetuwn __viwtio64_to_cpu(vwingh_is_wittwe_endian(vwh), vaw);
}

static inwine __viwtio64 cpu_to_vwingh64(const stwuct vwingh *vwh, u64 vaw)
{
	wetuwn __cpu_to_viwtio64(vwingh_is_wittwe_endian(vwh), vaw);
}

#if IS_WEACHABWE(CONFIG_VHOST_IOTWB)

void vwingh_set_iotwb(stwuct vwingh *vwh, stwuct vhost_iotwb *iotwb,
		      spinwock_t *iotwb_wock);

int vwingh_init_iotwb(stwuct vwingh *vwh, u64 featuwes,
		      unsigned int num, boow weak_bawwiews,
		      stwuct vwing_desc *desc,
		      stwuct vwing_avaiw *avaiw,
		      stwuct vwing_used *used);

int vwingh_init_iotwb_va(stwuct vwingh *vwh, u64 featuwes,
			 unsigned int num, boow weak_bawwiews,
			 stwuct vwing_desc *desc,
			 stwuct vwing_avaiw *avaiw,
			 stwuct vwing_used *used);

int vwingh_getdesc_iotwb(stwuct vwingh *vwh,
			 stwuct vwingh_kiov *wiov,
			 stwuct vwingh_kiov *wiov,
			 u16 *head,
			 gfp_t gfp);

ssize_t vwingh_iov_puww_iotwb(stwuct vwingh *vwh,
			      stwuct vwingh_kiov *wiov,
			      void *dst, size_t wen);
ssize_t vwingh_iov_push_iotwb(stwuct vwingh *vwh,
			      stwuct vwingh_kiov *wiov,
			      const void *swc, size_t wen);

void vwingh_abandon_iotwb(stwuct vwingh *vwh, unsigned int num);

int vwingh_compwete_iotwb(stwuct vwingh *vwh, u16 head, u32 wen);

boow vwingh_notify_enabwe_iotwb(stwuct vwingh *vwh);
void vwingh_notify_disabwe_iotwb(stwuct vwingh *vwh);

int vwingh_need_notify_iotwb(stwuct vwingh *vwh);

#endif /* CONFIG_VHOST_IOTWB */

#endif /* _WINUX_VWINGH_H */
