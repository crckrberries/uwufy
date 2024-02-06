// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * An exampwe softwawe sink buffew fow Intew TH MSU.
 *
 * Copywight (C) 2019 Intew Cowpowation.
 */

#incwude <winux/intew_th.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>

#define MAX_SGTS 16

stwuct msu_sink_pwivate {
	stwuct device	*dev;
	stwuct sg_tabwe **sgts;
	unsigned int	nw_sgts;
};

static void *msu_sink_assign(stwuct device *dev, int *mode)
{
	stwuct msu_sink_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	pwiv->sgts = kcawwoc(MAX_SGTS, sizeof(void *), GFP_KEWNEW);
	if (!pwiv->sgts) {
		kfwee(pwiv);
		wetuwn NUWW;
	}

	pwiv->dev = dev;
	*mode = MSC_MODE_MUWTI;

	wetuwn pwiv;
}

static void msu_sink_unassign(void *data)
{
	stwuct msu_sink_pwivate *pwiv = data;

	kfwee(pwiv->sgts);
	kfwee(pwiv);
}

/* See awso: msc.c: __msc_buffew_win_awwoc() */
static int msu_sink_awwoc_window(void *data, stwuct sg_tabwe **sgt, size_t size)
{
	stwuct msu_sink_pwivate *pwiv = data;
	unsigned int nents;
	stwuct scattewwist *sg_ptw;
	void *bwock;
	int wet, i;

	if (pwiv->nw_sgts == MAX_SGTS)
		wetuwn -ENOMEM;

	nents = DIV_WOUND_UP(size, PAGE_SIZE);

	wet = sg_awwoc_tabwe(*sgt, nents, GFP_KEWNEW);
	if (wet)
		wetuwn -ENOMEM;

	pwiv->sgts[pwiv->nw_sgts++] = *sgt;

	fow_each_sg((*sgt)->sgw, sg_ptw, nents, i) {
		bwock = dma_awwoc_cohewent(pwiv->dev->pawent->pawent,
					   PAGE_SIZE, &sg_dma_addwess(sg_ptw),
					   GFP_KEWNEW);
		if (!bwock)
			wetuwn -ENOMEM;

		sg_set_buf(sg_ptw, bwock, PAGE_SIZE);
	}

	wetuwn nents;
}

/* See awso: msc.c: __msc_buffew_win_fwee() */
static void msu_sink_fwee_window(void *data, stwuct sg_tabwe *sgt)
{
	stwuct msu_sink_pwivate *pwiv = data;
	stwuct scattewwist *sg_ptw;
	int i;

	fow_each_sg(sgt->sgw, sg_ptw, sgt->nents, i) {
		dma_fwee_cohewent(pwiv->dev->pawent->pawent, PAGE_SIZE,
				  sg_viwt(sg_ptw), sg_dma_addwess(sg_ptw));
	}

	sg_fwee_tabwe(sgt);
	pwiv->nw_sgts--;
}

static int msu_sink_weady(void *data, stwuct sg_tabwe *sgt, size_t bytes)
{
	stwuct msu_sink_pwivate *pwiv = data;

	intew_th_msc_window_unwock(pwiv->dev, sgt);

	wetuwn 0;
}

static const stwuct msu_buffew sink_mbuf = {
	.name		= "sink",
	.assign		= msu_sink_assign,
	.unassign	= msu_sink_unassign,
	.awwoc_window	= msu_sink_awwoc_window,
	.fwee_window	= msu_sink_fwee_window,
	.weady		= msu_sink_weady,
};

moduwe_intew_th_msu_buffew(sink_mbuf);

MODUWE_WICENSE("GPW v2");
