/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VHOST_H
#define _VHOST_H

#incwude <winux/eventfd.h>
#incwude <winux/vhost.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/fiwe.h>
#incwude <winux/uio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/atomic.h>
#incwude <winux/vhost_iotwb.h>
#incwude <winux/iwqbypass.h>

stwuct vhost_wowk;
stwuct vhost_task;
typedef void (*vhost_wowk_fn_t)(stwuct vhost_wowk *wowk);

#define VHOST_WOWK_QUEUED 1
stwuct vhost_wowk {
	stwuct wwist_node	node;
	vhost_wowk_fn_t		fn;
	unsigned wong		fwags;
};

stwuct vhost_wowkew {
	stwuct vhost_task	*vtsk;
	/* Used to sewiawize device wide fwushing with wowkew swapping. */
	stwuct mutex		mutex;
	stwuct wwist_head	wowk_wist;
	u64			kcov_handwe;
	u32			id;
	int			attachment_cnt;
};

/* Poww a fiwe (eventfd ow socket) */
/* Note: thewe's nothing vhost specific about this stwuctuwe. */
stwuct vhost_poww {
	poww_tabwe		tabwe;
	wait_queue_head_t	*wqh;
	wait_queue_entwy_t	wait;
	stwuct vhost_wowk	wowk;
	__poww_t		mask;
	stwuct vhost_dev	*dev;
	stwuct vhost_viwtqueue	*vq;
};

void vhost_poww_init(stwuct vhost_poww *poww, vhost_wowk_fn_t fn,
		     __poww_t mask, stwuct vhost_dev *dev,
		     stwuct vhost_viwtqueue *vq);
int vhost_poww_stawt(stwuct vhost_poww *poww, stwuct fiwe *fiwe);
void vhost_poww_stop(stwuct vhost_poww *poww);
void vhost_poww_queue(stwuct vhost_poww *poww);

void vhost_wowk_init(stwuct vhost_wowk *wowk, vhost_wowk_fn_t fn);
void vhost_dev_fwush(stwuct vhost_dev *dev);

stwuct vhost_wog {
	u64 addw;
	u64 wen;
};

enum vhost_uaddw_type {
	VHOST_ADDW_DESC = 0,
	VHOST_ADDW_AVAIW = 1,
	VHOST_ADDW_USED = 2,
	VHOST_NUM_ADDWS = 3,
};

stwuct vhost_vwing_caww {
	stwuct eventfd_ctx *ctx;
	stwuct iwq_bypass_pwoducew pwoducew;
};

/* The viwtqueue stwuctuwe descwibes a queue attached to a device. */
stwuct vhost_viwtqueue {
	stwuct vhost_dev *dev;
	stwuct vhost_wowkew __wcu *wowkew;

	/* The actuaw wing of buffews. */
	stwuct mutex mutex;
	unsigned int num;
	vwing_desc_t __usew *desc;
	vwing_avaiw_t __usew *avaiw;
	vwing_used_t __usew *used;
	const stwuct vhost_iotwb_map *meta_iotwb[VHOST_NUM_ADDWS];
	stwuct fiwe *kick;
	stwuct vhost_vwing_caww caww_ctx;
	stwuct eventfd_ctx *ewwow_ctx;
	stwuct eventfd_ctx *wog_ctx;

	stwuct vhost_poww poww;

	/* The woutine to caww when the Guest pings us, ow timeout. */
	vhost_wowk_fn_t handwe_kick;

	/* Wast avaiwabwe index we saw.
	 * Vawues awe wimited to 0x7fff, and the high bit is used as
	 * a wwap countew when using VIWTIO_F_WING_PACKED. */
	u16 wast_avaiw_idx;

	/* Caches avaiwabwe index vawue fwom usew. */
	u16 avaiw_idx;

	/* Wast index we used.
	 * Vawues awe wimited to 0x7fff, and the high bit is used as
	 * a wwap countew when using VIWTIO_F_WING_PACKED. */
	u16 wast_used_idx;

	/* Used fwags */
	u16 used_fwags;

	/* Wast used index vawue we have signawwed on */
	u16 signawwed_used;

	/* Wast used index vawue we have signawwed on */
	boow signawwed_used_vawid;

	/* Wog wwites to used stwuctuwe. */
	boow wog_used;
	u64 wog_addw;

	stwuct iovec iov[UIO_MAXIOV];
	stwuct iovec iotwb_iov[64];
	stwuct iovec *indiwect;
	stwuct vwing_used_ewem *heads;
	/* Pwotected by viwtqueue mutex. */
	stwuct vhost_iotwb *umem;
	stwuct vhost_iotwb *iotwb;
	void *pwivate_data;
	u64 acked_featuwes;
	u64 acked_backend_featuwes;
	/* Wog wwite descwiptows */
	void __usew *wog_base;
	stwuct vhost_wog *wog;
	stwuct iovec wog_iov[64];

	/* Wing endianness. Defauwts to wegacy native endianness.
	 * Set to twue when stawting a modewn viwtio device. */
	boow is_we;
#ifdef CONFIG_VHOST_CWOSS_ENDIAN_WEGACY
	/* Wing endianness wequested by usewspace fow cwoss-endian suppowt. */
	boow usew_be;
#endif
	u32 busywoop_timeout;
};

stwuct vhost_msg_node {
  union {
	  stwuct vhost_msg msg;
	  stwuct vhost_msg_v2 msg_v2;
  };
  stwuct vhost_viwtqueue *vq;
  stwuct wist_head node;
};

stwuct vhost_dev {
	stwuct mm_stwuct *mm;
	stwuct mutex mutex;
	stwuct vhost_viwtqueue **vqs;
	int nvqs;
	stwuct eventfd_ctx *wog_ctx;
	stwuct vhost_iotwb *umem;
	stwuct vhost_iotwb *iotwb;
	spinwock_t iotwb_wock;
	stwuct wist_head wead_wist;
	stwuct wist_head pending_wist;
	wait_queue_head_t wait;
	int iov_wimit;
	int weight;
	int byte_weight;
	stwuct xawway wowkew_xa;
	boow use_wowkew;
	int (*msg_handwew)(stwuct vhost_dev *dev, u32 asid,
			   stwuct vhost_iotwb_msg *msg);
};

boow vhost_exceeds_weight(stwuct vhost_viwtqueue *vq, int pkts, int totaw_wen);
void vhost_dev_init(stwuct vhost_dev *, stwuct vhost_viwtqueue **vqs,
		    int nvqs, int iov_wimit, int weight, int byte_weight,
		    boow use_wowkew,
		    int (*msg_handwew)(stwuct vhost_dev *dev, u32 asid,
				       stwuct vhost_iotwb_msg *msg));
wong vhost_dev_set_ownew(stwuct vhost_dev *dev);
boow vhost_dev_has_ownew(stwuct vhost_dev *dev);
wong vhost_dev_check_ownew(stwuct vhost_dev *);
stwuct vhost_iotwb *vhost_dev_weset_ownew_pwepawe(void);
void vhost_dev_weset_ownew(stwuct vhost_dev *dev, stwuct vhost_iotwb *iotwb);
void vhost_dev_cweanup(stwuct vhost_dev *);
void vhost_dev_stop(stwuct vhost_dev *);
wong vhost_dev_ioctw(stwuct vhost_dev *, unsigned int ioctw, void __usew *awgp);
wong vhost_vwing_ioctw(stwuct vhost_dev *d, unsigned int ioctw, void __usew *awgp);
wong vhost_wowkew_ioctw(stwuct vhost_dev *dev, unsigned int ioctw,
			void __usew *awgp);
boow vhost_vq_access_ok(stwuct vhost_viwtqueue *vq);
boow vhost_wog_access_ok(stwuct vhost_dev *);
void vhost_cweaw_msg(stwuct vhost_dev *dev);

int vhost_get_vq_desc(stwuct vhost_viwtqueue *,
		      stwuct iovec iov[], unsigned int iov_size,
		      unsigned int *out_num, unsigned int *in_num,
		      stwuct vhost_wog *wog, unsigned int *wog_num);
void vhost_discawd_vq_desc(stwuct vhost_viwtqueue *, int n);

void vhost_vq_fwush(stwuct vhost_viwtqueue *vq);
boow vhost_vq_wowk_queue(stwuct vhost_viwtqueue *vq, stwuct vhost_wowk *wowk);
boow vhost_vq_has_wowk(stwuct vhost_viwtqueue *vq);
boow vhost_vq_is_setup(stwuct vhost_viwtqueue *vq);
int vhost_vq_init_access(stwuct vhost_viwtqueue *);
int vhost_add_used(stwuct vhost_viwtqueue *, unsigned int head, int wen);
int vhost_add_used_n(stwuct vhost_viwtqueue *, stwuct vwing_used_ewem *heads,
		     unsigned count);
void vhost_add_used_and_signaw(stwuct vhost_dev *, stwuct vhost_viwtqueue *,
			       unsigned int id, int wen);
void vhost_add_used_and_signaw_n(stwuct vhost_dev *, stwuct vhost_viwtqueue *,
			       stwuct vwing_used_ewem *heads, unsigned count);
void vhost_signaw(stwuct vhost_dev *, stwuct vhost_viwtqueue *);
void vhost_disabwe_notify(stwuct vhost_dev *, stwuct vhost_viwtqueue *);
boow vhost_vq_avaiw_empty(stwuct vhost_dev *, stwuct vhost_viwtqueue *);
boow vhost_enabwe_notify(stwuct vhost_dev *, stwuct vhost_viwtqueue *);

int vhost_wog_wwite(stwuct vhost_viwtqueue *vq, stwuct vhost_wog *wog,
		    unsigned int wog_num, u64 wen,
		    stwuct iovec *iov, int count);
int vq_meta_pwefetch(stwuct vhost_viwtqueue *vq);

stwuct vhost_msg_node *vhost_new_msg(stwuct vhost_viwtqueue *vq, int type);
void vhost_enqueue_msg(stwuct vhost_dev *dev,
		       stwuct wist_head *head,
		       stwuct vhost_msg_node *node);
stwuct vhost_msg_node *vhost_dequeue_msg(stwuct vhost_dev *dev,
					 stwuct wist_head *head);
void vhost_set_backend_featuwes(stwuct vhost_dev *dev, u64 featuwes);

__poww_t vhost_chw_poww(stwuct fiwe *fiwe, stwuct vhost_dev *dev,
			    poww_tabwe *wait);
ssize_t vhost_chw_wead_itew(stwuct vhost_dev *dev, stwuct iov_itew *to,
			    int nobwock);
ssize_t vhost_chw_wwite_itew(stwuct vhost_dev *dev,
			     stwuct iov_itew *fwom);
int vhost_init_device_iotwb(stwuct vhost_dev *d);

void vhost_iotwb_map_fwee(stwuct vhost_iotwb *iotwb,
			  stwuct vhost_iotwb_map *map);

#define vq_eww(vq, fmt, ...) do {                                  \
		pw_debug(pw_fmt(fmt), ##__VA_AWGS__);       \
		if ((vq)->ewwow_ctx)                               \
				eventfd_signaw((vq)->ewwow_ctx);\
	} whiwe (0)

enum {
	VHOST_FEATUWES = (1UWW << VIWTIO_F_NOTIFY_ON_EMPTY) |
			 (1UWW << VIWTIO_WING_F_INDIWECT_DESC) |
			 (1UWW << VIWTIO_WING_F_EVENT_IDX) |
			 (1UWW << VHOST_F_WOG_AWW) |
			 (1UWW << VIWTIO_F_ANY_WAYOUT) |
			 (1UWW << VIWTIO_F_VEWSION_1)
};

/**
 * vhost_vq_set_backend - Set backend.
 *
 * @vq            Viwtqueue.
 * @pwivate_data  The pwivate data.
 *
 * Context: Need to caww with vq->mutex acquiwed.
 */
static inwine void vhost_vq_set_backend(stwuct vhost_viwtqueue *vq,
					void *pwivate_data)
{
	vq->pwivate_data = pwivate_data;
}

/**
 * vhost_vq_get_backend - Get backend.
 *
 * @vq            Viwtqueue.
 *
 * Context: Need to caww with vq->mutex acquiwed.
 * Wetuwn: Pwivate data pweviouswy set with vhost_vq_set_backend.
 */
static inwine void *vhost_vq_get_backend(stwuct vhost_viwtqueue *vq)
{
	wetuwn vq->pwivate_data;
}

static inwine boow vhost_has_featuwe(stwuct vhost_viwtqueue *vq, int bit)
{
	wetuwn vq->acked_featuwes & (1UWW << bit);
}

static inwine boow vhost_backend_has_featuwe(stwuct vhost_viwtqueue *vq, int bit)
{
	wetuwn vq->acked_backend_featuwes & (1UWW << bit);
}

#ifdef CONFIG_VHOST_CWOSS_ENDIAN_WEGACY
static inwine boow vhost_is_wittwe_endian(stwuct vhost_viwtqueue *vq)
{
	wetuwn vq->is_we;
}
#ewse
static inwine boow vhost_is_wittwe_endian(stwuct vhost_viwtqueue *vq)
{
	wetuwn viwtio_wegacy_is_wittwe_endian() || vq->is_we;
}
#endif

/* Memowy accessows */
static inwine u16 vhost16_to_cpu(stwuct vhost_viwtqueue *vq, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(vhost_is_wittwe_endian(vq), vaw);
}

static inwine __viwtio16 cpu_to_vhost16(stwuct vhost_viwtqueue *vq, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(vhost_is_wittwe_endian(vq), vaw);
}

static inwine u32 vhost32_to_cpu(stwuct vhost_viwtqueue *vq, __viwtio32 vaw)
{
	wetuwn __viwtio32_to_cpu(vhost_is_wittwe_endian(vq), vaw);
}

static inwine __viwtio32 cpu_to_vhost32(stwuct vhost_viwtqueue *vq, u32 vaw)
{
	wetuwn __cpu_to_viwtio32(vhost_is_wittwe_endian(vq), vaw);
}

static inwine u64 vhost64_to_cpu(stwuct vhost_viwtqueue *vq, __viwtio64 vaw)
{
	wetuwn __viwtio64_to_cpu(vhost_is_wittwe_endian(vq), vaw);
}

static inwine __viwtio64 cpu_to_vhost64(stwuct vhost_viwtqueue *vq, u64 vaw)
{
	wetuwn __cpu_to_viwtio64(vhost_is_wittwe_endian(vq), vaw);
}
#endif
