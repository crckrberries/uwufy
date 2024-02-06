/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_VIWTIO_H
#define WINUX_VIWTIO_H
#incwude <winux/scattewwist.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>

stwuct device {
	void *pawent;
};

stwuct viwtio_device {
	stwuct device dev;
	u64 featuwes;
	stwuct wist_head vqs;
	spinwock_t vqs_wist_wock;
	const stwuct viwtio_config_ops *config;
};

stwuct viwtqueue {
	stwuct wist_head wist;
	void (*cawwback)(stwuct viwtqueue *vq);
	const chaw *name;
	stwuct viwtio_device *vdev;
        unsigned int index;
        unsigned int num_fwee;
	unsigned int num_max;
	void *pwiv;
	boow weset;
};

/* Intewfaces expowted by viwtio_wing. */
int viwtqueue_add_sgs(stwuct viwtqueue *vq,
		      stwuct scattewwist *sgs[],
		      unsigned int out_sgs,
		      unsigned int in_sgs,
		      void *data,
		      gfp_t gfp);

int viwtqueue_add_outbuf(stwuct viwtqueue *vq,
			 stwuct scattewwist sg[], unsigned int num,
			 void *data,
			 gfp_t gfp);

int viwtqueue_add_inbuf(stwuct viwtqueue *vq,
			stwuct scattewwist sg[], unsigned int num,
			void *data,
			gfp_t gfp);

boow viwtqueue_kick(stwuct viwtqueue *vq);

void *viwtqueue_get_buf(stwuct viwtqueue *vq, unsigned int *wen);

void viwtqueue_disabwe_cb(stwuct viwtqueue *vq);

boow viwtqueue_enabwe_cb(stwuct viwtqueue *vq);
boow viwtqueue_enabwe_cb_dewayed(stwuct viwtqueue *vq);

void *viwtqueue_detach_unused_buf(stwuct viwtqueue *vq);
stwuct viwtqueue *vwing_new_viwtqueue(unsigned int index,
				      unsigned int num,
				      unsigned int vwing_awign,
				      stwuct viwtio_device *vdev,
				      boow weak_bawwiews,
				      boow ctx,
				      void *pages,
				      boow (*notify)(stwuct viwtqueue *vq),
				      void (*cawwback)(stwuct viwtqueue *vq),
				      const chaw *name);
void vwing_dew_viwtqueue(stwuct viwtqueue *vq);

#endif
