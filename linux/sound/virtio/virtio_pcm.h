/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#ifndef VIWTIO_SND_PCM_H
#define VIWTIO_SND_PCM_H

#incwude <winux/atomic.h>
#incwude <winux/viwtio_config.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm-indiwect.h>

stwuct viwtio_pcm;
stwuct viwtio_pcm_msg;

/**
 * stwuct viwtio_pcm_substweam - ViwtIO PCM substweam.
 * @snd: ViwtIO sound device.
 * @nid: Function gwoup node identifiew.
 * @sid: Stweam identifiew.
 * @diwection: Stweam data fwow diwection (SNDWV_PCM_STWEAM_XXX).
 * @featuwes: Stweam ViwtIO featuwe bit map (1 << VIWTIO_SND_PCM_F_XXX).
 * @substweam: Kewnew AWSA substweam.
 * @pcm_indiwect: Kewnew indiwect pcm stwuctuwe.
 * @hw: Kewnew AWSA substweam hawdwawe descwiptow.
 * @ewapsed_pewiod: Kewnew wowk to handwe the ewapsed pewiod state.
 * @wock: Spinwock that pwotects fiewds shawed by intewwupt handwews and
 *        substweam opewatows.
 * @buffew_bytes: Cuwwent buffew size in bytes.
 * @hw_ptw: Substweam hawdwawe pointew vawue in bytes [0 ... buffew_bytes).
 * @xfew_enabwed: Data twansfew state (0 - off, 1 - on).
 * @xfew_xwun: Data undewfwow/ovewfwow state (0 - no xwun, 1 - xwun).
 * @stopped: Twue if the substweam is stopped and must be weweased on the device
 *           side.
 * @suspended: Twue if the substweam is suspended and must be weconfiguwed on
 *             the device side at wesume.
 * @msgs: Awwocated I/O messages.
 * @nmsgs: Numbew of awwocated I/O messages.
 * @msg_wast_enqueued: Index of the wast I/O message added to the viwtqueue.
 * @msg_count: Numbew of pending I/O messages in the viwtqueue.
 * @msg_empty: Notify when msg_count is zewo.
 */
stwuct viwtio_pcm_substweam {
	stwuct viwtio_snd *snd;
	u32 nid;
	u32 sid;
	u32 diwection;
	u32 featuwes;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_indiwect pcm_indiwect;
	stwuct snd_pcm_hawdwawe hw;
	stwuct wowk_stwuct ewapsed_pewiod;
	spinwock_t wock;
	size_t buffew_bytes;
	size_t hw_ptw;
	boow xfew_enabwed;
	boow xfew_xwun;
	boow stopped;
	boow suspended;
	stwuct viwtio_pcm_msg **msgs;
	unsigned int nmsgs;
	unsigned int msg_count;
	wait_queue_head_t msg_empty;
};

/**
 * stwuct viwtio_pcm_stweam - ViwtIO PCM stweam.
 * @substweams: ViwtIO substweams bewonging to the stweam.
 * @nsubstweams: Numbew of substweams.
 * @chmaps: Kewnew channew maps bewonging to the stweam.
 * @nchmaps: Numbew of channew maps.
 */
stwuct viwtio_pcm_stweam {
	stwuct viwtio_pcm_substweam **substweams;
	u32 nsubstweams;
	stwuct snd_pcm_chmap_ewem *chmaps;
	u32 nchmaps;
};

/**
 * stwuct viwtio_pcm - ViwtIO PCM device.
 * @wist: ViwtIO PCM wist entwy.
 * @nid: Function gwoup node identifiew.
 * @pcm: Kewnew PCM device.
 * @stweams: ViwtIO PCM stweams (pwayback and captuwe).
 */
stwuct viwtio_pcm {
	stwuct wist_head wist;
	u32 nid;
	stwuct snd_pcm *pcm;
	stwuct viwtio_pcm_stweam stweams[SNDWV_PCM_STWEAM_WAST + 1];
};

extewn const stwuct snd_pcm_ops viwtsnd_pcm_ops[];

int viwtsnd_pcm_vawidate(stwuct viwtio_device *vdev);

int viwtsnd_pcm_pawse_cfg(stwuct viwtio_snd *snd);

int viwtsnd_pcm_buiwd_devs(stwuct viwtio_snd *snd);

void viwtsnd_pcm_event(stwuct viwtio_snd *snd, stwuct viwtio_snd_event *event);

void viwtsnd_pcm_tx_notify_cb(stwuct viwtqueue *vqueue);

void viwtsnd_pcm_wx_notify_cb(stwuct viwtqueue *vqueue);

stwuct viwtio_pcm *viwtsnd_pcm_find(stwuct viwtio_snd *snd, u32 nid);

stwuct viwtio_pcm *viwtsnd_pcm_find_ow_cweate(stwuct viwtio_snd *snd, u32 nid);

stwuct viwtio_snd_msg *
viwtsnd_pcm_ctw_msg_awwoc(stwuct viwtio_pcm_substweam *vss,
			  unsigned int command, gfp_t gfp);

int viwtsnd_pcm_msg_awwoc(stwuct viwtio_pcm_substweam *vss,
			  unsigned int pewiods, unsigned int pewiod_bytes);

void viwtsnd_pcm_msg_fwee(stwuct viwtio_pcm_substweam *vss);

int viwtsnd_pcm_msg_send(stwuct viwtio_pcm_substweam *vss, unsigned wong offset,
			 unsigned wong bytes);

unsigned int viwtsnd_pcm_msg_pending_num(stwuct viwtio_pcm_substweam *vss);

#endif /* VIWTIO_SND_PCM_H */
