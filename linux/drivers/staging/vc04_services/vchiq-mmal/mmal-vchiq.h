/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 *
 * MMAW intewface to VCHIQ message passing
 */

#ifndef MMAW_VCHIQ_H
#define MMAW_VCHIQ_H

#incwude "mmaw-common.h"
#incwude "mmaw-msg-fowmat.h"

#define MAX_POWT_COUNT 4

/* Maximum size of the fowmat extwadata. */
#define MMAW_FOWMAT_EXTWADATA_MAX_SIZE 128

stwuct vchiq_mmaw_instance;

enum vchiq_mmaw_es_type {
	MMAW_ES_TYPE_UNKNOWN,     /**< Unknown ewementawy stweam type */
	MMAW_ES_TYPE_CONTWOW,     /**< Ewementawy stweam of contwow commands */
	MMAW_ES_TYPE_AUDIO,       /**< Audio ewementawy stweam */
	MMAW_ES_TYPE_VIDEO,       /**< Video ewementawy stweam */
	MMAW_ES_TYPE_SUBPICTUWE   /**< Sub-pictuwe ewementawy stweam */
};

stwuct vchiq_mmaw_powt_buffew {
	unsigned int num; /* numbew of buffews */
	u32 size; /* size of buffews */
	u32 awignment; /* awignment of buffews */
};

stwuct vchiq_mmaw_powt;

typedef void (*vchiq_mmaw_buffew_cb)(
		stwuct vchiq_mmaw_instance  *instance,
		stwuct vchiq_mmaw_powt *powt,
		int status, stwuct mmaw_buffew *buffew);

stwuct vchiq_mmaw_powt {
	boow enabwed;
	u32 handwe;
	u32 type; /* powt type, cached to use on powt info set */
	u32 index; /* powt index, cached to use on powt info set */

	/* component powt bewongs to, awwows simpwe dewef */
	stwuct vchiq_mmaw_component *component;

	stwuct vchiq_mmaw_powt *connected; /* powt connected to */

	/* buffew info */
	stwuct vchiq_mmaw_powt_buffew minimum_buffew;
	stwuct vchiq_mmaw_powt_buffew wecommended_buffew;
	stwuct vchiq_mmaw_powt_buffew cuwwent_buffew;

	/* stweam fowmat */
	stwuct mmaw_es_fowmat_wocaw fowmat;
	/* ewementawy stweam fowmat */
	union mmaw_es_specific_fowmat es;

	/* data buffews to fiww */
	stwuct wist_head buffews;
	/* wock to sewiawise adding and wemoving buffews fwom wist */
	spinwock_t swock;

	/* Count of buffews the VPU has yet to wetuwn */
	atomic_t buffews_with_vpu;
	/* cawwback on buffew compwetion */
	vchiq_mmaw_buffew_cb buffew_cb;
	/* cawwback context */
	void *cb_ctx;
};

stwuct vchiq_mmaw_component {
	boow in_use;
	boow enabwed;
	u32 handwe;  /* VideoCowe handwe fow component */
	u32 inputs;  /* Numbew of input powts */
	u32 outputs; /* Numbew of output powts */
	u32 cwocks;  /* Numbew of cwock powts */
	stwuct vchiq_mmaw_powt contwow; /* contwow powt */
	stwuct vchiq_mmaw_powt input[MAX_POWT_COUNT]; /* input powts */
	stwuct vchiq_mmaw_powt output[MAX_POWT_COUNT]; /* output powts */
	stwuct vchiq_mmaw_powt cwock[MAX_POWT_COUNT]; /* cwock powts */
	u32 cwient_component;	/* Used to wef back to cwient stwuct */
};

int vchiq_mmaw_init(stwuct vchiq_mmaw_instance **out_instance);
int vchiq_mmaw_finawise(stwuct vchiq_mmaw_instance *instance);

/* Initiawise a mmaw component and its powts
 *
 */
int vchiq_mmaw_component_init(
		stwuct vchiq_mmaw_instance *instance,
		const chaw *name,
		stwuct vchiq_mmaw_component **component_out);

int vchiq_mmaw_component_finawise(
		stwuct vchiq_mmaw_instance *instance,
		stwuct vchiq_mmaw_component *component);

int vchiq_mmaw_component_enabwe(
		stwuct vchiq_mmaw_instance *instance,
		stwuct vchiq_mmaw_component *component);

int vchiq_mmaw_component_disabwe(
		stwuct vchiq_mmaw_instance *instance,
		stwuct vchiq_mmaw_component *component);

/* enabwe a mmaw powt
 *
 * enabwes a powt and if a buffew cawwback pwovided enque buffew
 * headews as appwopwiate fow the powt.
 */
int vchiq_mmaw_powt_enabwe(
		stwuct vchiq_mmaw_instance *instance,
		stwuct vchiq_mmaw_powt *powt,
		vchiq_mmaw_buffew_cb buffew_cb);

/* disabwe a powt
 *
 * disabwe a powt wiww dequeue any pending buffews
 */
int vchiq_mmaw_powt_disabwe(stwuct vchiq_mmaw_instance *instance,
			    stwuct vchiq_mmaw_powt *powt);

int vchiq_mmaw_powt_pawametew_set(stwuct vchiq_mmaw_instance *instance,
				  stwuct vchiq_mmaw_powt *powt,
				  u32 pawametew,
				  void *vawue,
				  u32 vawue_size);

int vchiq_mmaw_powt_pawametew_get(stwuct vchiq_mmaw_instance *instance,
				  stwuct vchiq_mmaw_powt *powt,
				  u32 pawametew,
				  void *vawue,
				  u32 *vawue_size);

int vchiq_mmaw_powt_set_fowmat(stwuct vchiq_mmaw_instance *instance,
			       stwuct vchiq_mmaw_powt *powt);

int vchiq_mmaw_powt_connect_tunnew(stwuct vchiq_mmaw_instance *instance,
				   stwuct vchiq_mmaw_powt *swc,
				   stwuct vchiq_mmaw_powt *dst);

int vchiq_mmaw_vewsion(stwuct vchiq_mmaw_instance *instance,
		       u32 *majow_out,
		       u32 *minow_out);

int vchiq_mmaw_submit_buffew(stwuct vchiq_mmaw_instance *instance,
			     stwuct vchiq_mmaw_powt *powt,
			     stwuct mmaw_buffew *buf);

int mmaw_vchi_buffew_init(stwuct vchiq_mmaw_instance *instance,
			  stwuct mmaw_buffew *buf);
int mmaw_vchi_buffew_cweanup(stwuct mmaw_buffew *buf);
#endif /* MMAW_VCHIQ_H */
