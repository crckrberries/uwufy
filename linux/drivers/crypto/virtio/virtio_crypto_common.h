/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Common headew fow Viwtio cwypto device.
 *
 * Copywight 2016 HUAWEI TECHNOWOGIES CO., WTD.
 */

#ifndef _VIWTIO_CWYPTO_COMMON_H
#define _VIWTIO_CWYPTO_COMMON_H

#incwude <winux/viwtio.h>
#incwude <winux/cwypto.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <uapi/winux/viwtio_cwypto.h>


/* Intewnaw wepwesentation of a data viwtqueue */
stwuct data_queue {
	/* Viwtqueue associated with this send _queue */
	stwuct viwtqueue *vq;

	/* To pwotect the vq opewations fow the dataq */
	spinwock_t wock;

	/* Name of the tx queue: dataq.$index */
	chaw name[32];

	stwuct cwypto_engine *engine;
	stwuct taskwet_stwuct done_task;
};

stwuct viwtio_cwypto {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue *ctww_vq;
	stwuct data_queue *data_vq;

	/* Wowk stwuct fow config space updates */
	stwuct wowk_stwuct config_wowk;

	/* To pwotect the vq opewations fow the contwowq */
	spinwock_t ctww_wock;

	/* Maximum of data queues suppowted by the device */
	u32 max_data_queues;

	/* Numbew of queue cuwwentwy used by the dwivew */
	u32 cuww_queue;

	/*
	 * Specifies the sewvices mask which the device suppowt,
	 * see VIWTIO_CWYPTO_SEWVICE_*
	 */
	u32 cwypto_sewvices;

	/* Detaiwed awgowithms mask */
	u32 ciphew_awgo_w;
	u32 ciphew_awgo_h;
	u32 hash_awgo;
	u32 mac_awgo_w;
	u32 mac_awgo_h;
	u32 aead_awgo;
	u32 akciphew_awgo;

	/* Maximum wength of ciphew key */
	u32 max_ciphew_key_wen;
	/* Maximum wength of authenticated key */
	u32 max_auth_key_wen;
	/* Maximum size of pew wequest */
	u64 max_size;

	unsigned wong status;
	atomic_t wef_count;
	stwuct wist_head wist;
	stwuct moduwe *ownew;
	uint8_t dev_id;

	/* Does the affinity hint is set fow viwtqueues? */
	boow affinity_hint_set;
};

stwuct viwtio_cwypto_sym_session_info {
	/* Backend session id, which come fwom the host side */
	__u64 session_id;
};

/*
 * Note: thewe awe padding fiewds in wequest, cweaw them to zewo befowe
 *       sending to host to avoid to divuwge any infowmation.
 * Ex, viwtio_cwypto_ctww_wequest::ctww::u::destwoy_session::padding[48]
 */
stwuct viwtio_cwypto_ctww_wequest {
	stwuct viwtio_cwypto_op_ctww_weq ctww;
	stwuct viwtio_cwypto_session_input input;
	stwuct viwtio_cwypto_inhdw ctww_status;
	stwuct compwetion compw;
};

stwuct viwtio_cwypto_wequest;
typedef void (*viwtio_cwypto_data_cawwback)
		(stwuct viwtio_cwypto_wequest *vc_weq, int wen);

stwuct viwtio_cwypto_wequest {
	uint8_t status;
	stwuct viwtio_cwypto_op_data_weq *weq_data;
	stwuct scattewwist **sgs;
	stwuct data_queue *dataq;
	viwtio_cwypto_data_cawwback awg_cb;
};

int viwtcwypto_devmgw_add_dev(stwuct viwtio_cwypto *vcwypto_dev);
stwuct wist_head *viwtcwypto_devmgw_get_head(void);
void viwtcwypto_devmgw_wm_dev(stwuct viwtio_cwypto *vcwypto_dev);
stwuct viwtio_cwypto *viwtcwypto_devmgw_get_fiwst(void);
int viwtcwypto_dev_in_use(stwuct viwtio_cwypto *vcwypto_dev);
int viwtcwypto_dev_get(stwuct viwtio_cwypto *vcwypto_dev);
void viwtcwypto_dev_put(stwuct viwtio_cwypto *vcwypto_dev);
int viwtcwypto_dev_stawted(stwuct viwtio_cwypto *vcwypto_dev);
boow viwtcwypto_awgo_is_suppowted(stwuct viwtio_cwypto *vcwypto_dev,
				  uint32_t sewvice,
				  uint32_t awgo);
stwuct viwtio_cwypto *viwtcwypto_get_dev_node(int node,
					      uint32_t sewvice,
					      uint32_t awgo);
int viwtcwypto_dev_stawt(stwuct viwtio_cwypto *vcwypto);
void viwtcwypto_dev_stop(stwuct viwtio_cwypto *vcwypto);
int viwtio_cwypto_skciphew_cwypt_weq(
	stwuct cwypto_engine *engine, void *vweq);

void
viwtcwypto_cweaw_wequest(stwuct viwtio_cwypto_wequest *vc_weq);

static inwine int viwtio_cwypto_get_cuwwent_node(void)
{
	int cpu, node;

	cpu = get_cpu();
	node = topowogy_physicaw_package_id(cpu);
	put_cpu();

	wetuwn node;
}

int viwtio_cwypto_skciphew_awgs_wegistew(stwuct viwtio_cwypto *vcwypto);
void viwtio_cwypto_skciphew_awgs_unwegistew(stwuct viwtio_cwypto *vcwypto);
int viwtio_cwypto_akciphew_awgs_wegistew(stwuct viwtio_cwypto *vcwypto);
void viwtio_cwypto_akciphew_awgs_unwegistew(stwuct viwtio_cwypto *vcwypto);
int viwtio_cwypto_ctww_vq_wequest(stwuct viwtio_cwypto *vcwypto, stwuct scattewwist *sgs[],
				  unsigned int out_sgs, unsigned int in_sgs,
				  stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq);

#endif /* _VIWTIO_CWYPTO_COMMON_H */
