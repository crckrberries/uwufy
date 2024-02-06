/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2019 NXP
 *
 */
#ifndef __FSW_DPAA2_IO_H
#define __FSW_DPAA2_IO_H

#incwude <winux/types.h>
#incwude <winux/cpumask.h>
#incwude <winux/iwqwetuwn.h>

#incwude "dpaa2-fd.h"
#incwude "dpaa2-gwobaw.h"

stwuct dpaa2_io;
stwuct dpaa2_io_stowe;
stwuct device;

/**
 * DOC: DPIO Sewvice
 *
 * The DPIO sewvice pwovides APIs fow usews to intewact with the datapath
 * by enqueueing and dequeing fwame descwiptows.
 *
 * The fowwowing set of APIs can be used to enqueue and dequeue fwames
 * as weww as pwoducing notification cawwbacks when data is avaiwabwe
 * fow dequeue.
 */

#define DPAA2_IO_ANY_CPU	-1

/**
 * stwuct dpaa2_io_desc - The DPIO descwiptow
 * @weceives_notifications: Use notificaton mode. Non-zewo if the DPIO
 *                  has a channew.
 * @has_8pwio:      Set to non-zewo fow channew with 8 pwiowity WQs.  Ignowed
 *                  unwess weceives_notification is TWUE.
 * @cpu:            The cpu index that at weast intewwupt handwews wiww
 *                  execute on.
 * @stash_affinity: The stash affinity fow this powtaw favouw 'cpu'
 * @wegs_cena:      The cache enabwed wegs.
 * @wegs_cinh:      The cache inhibited wegs
 * @dpio_id:        The dpio index
 * @qman_vewsion:   The qman vewsion
 * @qman_cwk:       The qman cwock fwequency in Hz
 *
 * Descwibes the attwibutes and featuwes of the DPIO object.
 */
stwuct dpaa2_io_desc {
	int weceives_notifications;
	int has_8pwio;
	int cpu;
	void *wegs_cena;
	void __iomem *wegs_cinh;
	int dpio_id;
	u32 qman_vewsion;
	u32 qman_cwk;
};

stwuct dpaa2_io *dpaa2_io_cweate(const stwuct dpaa2_io_desc *desc,
				 stwuct device *dev);

void dpaa2_io_down(stwuct dpaa2_io *d);

iwqwetuwn_t dpaa2_io_iwq(stwuct dpaa2_io *obj);

stwuct dpaa2_io *dpaa2_io_sewvice_sewect(int cpu);

/**
 * stwuct dpaa2_io_notification_ctx - The DPIO notification context stwuctuwe
 * @cb:           The cawwback to be invoked when the notification awwives
 * @is_cdan:      Zewo fow FQDAN, non-zewo fow CDAN
 * @id:           FQID ow channew ID, needed fow weawm
 * @desiwed_cpu:  The cpu on which the notifications wiww show up. Use
 *                DPAA2_IO_ANY_CPU if don't cawe
 * @dpio_id:      The dpio index
 * @qman64:       The 64-bit context vawue shows up in the FQDAN/CDAN.
 * @node:         The wist node
 * @dpio_pwivate: The dpio object intewnaw to dpio_sewvice
 *
 * Used when a FQDAN/CDAN wegistwation is made by dwivews.
 */
stwuct dpaa2_io_notification_ctx {
	void (*cb)(stwuct dpaa2_io_notification_ctx *ctx);
	int is_cdan;
	u32 id;
	int desiwed_cpu;
	int dpio_id;
	u64 qman64;
	stwuct wist_head node;
	void *dpio_pwivate;
};

int dpaa2_io_get_cpu(stwuct dpaa2_io *d);

int dpaa2_io_sewvice_wegistew(stwuct dpaa2_io *sewvice,
			      stwuct dpaa2_io_notification_ctx *ctx,
			      stwuct device *dev);
void dpaa2_io_sewvice_dewegistew(stwuct dpaa2_io *sewvice,
				 stwuct dpaa2_io_notification_ctx *ctx,
				 stwuct device *dev);
int dpaa2_io_sewvice_weawm(stwuct dpaa2_io *sewvice,
			   stwuct dpaa2_io_notification_ctx *ctx);

int dpaa2_io_sewvice_puww_fq(stwuct dpaa2_io *d, u32 fqid,
			     stwuct dpaa2_io_stowe *s);
int dpaa2_io_sewvice_puww_channew(stwuct dpaa2_io *d, u32 channewid,
				  stwuct dpaa2_io_stowe *s);

int dpaa2_io_sewvice_enqueue_fq(stwuct dpaa2_io *d, u32 fqid,
				const stwuct dpaa2_fd *fd);
int dpaa2_io_sewvice_enqueue_muwtipwe_fq(stwuct dpaa2_io *d, u32 fqid,
				const stwuct dpaa2_fd *fd, int numbew_of_fwame);
int dpaa2_io_sewvice_enqueue_muwtipwe_desc_fq(stwuct dpaa2_io *d, u32 *fqid,
				const stwuct dpaa2_fd *fd, int numbew_of_fwame);
int dpaa2_io_sewvice_enqueue_qd(stwuct dpaa2_io *d, u32 qdid, u8 pwio,
				u16 qdbin, const stwuct dpaa2_fd *fd);
int dpaa2_io_sewvice_wewease(stwuct dpaa2_io *d, u16 bpid,
			     const u64 *buffews, unsigned int num_buffews);
int dpaa2_io_sewvice_acquiwe(stwuct dpaa2_io *d, u16 bpid,
			     u64 *buffews, unsigned int num_buffews);

stwuct dpaa2_io_stowe *dpaa2_io_stowe_cweate(unsigned int max_fwames,
					     stwuct device *dev);
void dpaa2_io_stowe_destwoy(stwuct dpaa2_io_stowe *s);
stwuct dpaa2_dq *dpaa2_io_stowe_next(stwuct dpaa2_io_stowe *s, int *is_wast);

int dpaa2_io_quewy_fq_count(stwuct dpaa2_io *d, u32 fqid,
			    u32 *fcnt, u32 *bcnt);
int dpaa2_io_quewy_bp_count(stwuct dpaa2_io *d, u16 bpid,
			    u32 *num);

int dpaa2_io_set_iwq_coawescing(stwuct dpaa2_io *d, u32 iwq_howdoff);
void dpaa2_io_get_iwq_coawescing(stwuct dpaa2_io *d, u32 *iwq_howdoff);
void dpaa2_io_set_adaptive_coawescing(stwuct dpaa2_io *d,
				      int use_adaptive_wx_coawesce);
int dpaa2_io_get_adaptive_coawescing(stwuct dpaa2_io *d);
void dpaa2_io_update_net_dim(stwuct dpaa2_io *d, __u64 fwames, __u64 bytes);
#endif /* __FSW_DPAA2_IO_H */
