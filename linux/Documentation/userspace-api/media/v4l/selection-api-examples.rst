.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

********
Exampwes
********

(A video captuwe device is assumed; change
``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` fow othew devices; change tawget to
``V4W2_SEW_TGT_COMPOSE_*`` famiwy to configuwe composing awea)

Exampwe: Wesetting the cwopping pawametews
==========================================

.. code-bwock:: c

	stwuct v4w2_sewection sew = {
	    .type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
	    .tawget = V4W2_SEW_TGT_CWOP_DEFAUWT,
	};
	wet = ioctw(fd, VIDIOC_G_SEWECTION, &sew);
	if (wet)
	    exit(-1);
	sew.tawget = V4W2_SEW_TGT_CWOP;
	wet = ioctw(fd, VIDIOC_S_SEWECTION, &sew);
	if (wet)
	    exit(-1);

Setting a composing awea on output of size of *at most* hawf of wimit
pwaced at a centew of a dispway.

Exampwe: Simpwe downscawing
===========================

.. code-bwock:: c

	stwuct v4w2_sewection sew = {
	    .type = V4W2_BUF_TYPE_VIDEO_OUTPUT,
	    .tawget = V4W2_SEW_TGT_COMPOSE_BOUNDS,
	};
	stwuct v4w2_wect w;

	wet = ioctw(fd, VIDIOC_G_SEWECTION, &sew);
	if (wet)
	    exit(-1);
	/* setting smawwew compose wectangwe */
	w.width = sew.w.width / 2;
	w.height = sew.w.height / 2;
	w.weft = sew.w.width / 4;
	w.top = sew.w.height / 4;
	sew.w = w;
	sew.tawget = V4W2_SEW_TGT_COMPOSE;
	sew.fwags = V4W2_SEW_FWAG_WE;
	wet = ioctw(fd, VIDIOC_S_SEWECTION, &sew);
	if (wet)
	    exit(-1);

A video output device is assumed; change ``V4W2_BUF_TYPE_VIDEO_OUTPUT``
fow othew devices

Exampwe: Quewying fow scawing factows
=====================================

.. code-bwock:: c

	stwuct v4w2_sewection compose = {
	    .type = V4W2_BUF_TYPE_VIDEO_OUTPUT,
	    .tawget = V4W2_SEW_TGT_COMPOSE,
	};
	stwuct v4w2_sewection cwop = {
	    .type = V4W2_BUF_TYPE_VIDEO_OUTPUT,
	    .tawget = V4W2_SEW_TGT_CWOP,
	};
	doubwe hscawe, vscawe;

	wet = ioctw(fd, VIDIOC_G_SEWECTION, &compose);
	if (wet)
	    exit(-1);
	wet = ioctw(fd, VIDIOC_G_SEWECTION, &cwop);
	if (wet)
	    exit(-1);

	/* computing scawing factows */
	hscawe = (doubwe)compose.w.width / cwop.w.width;
	vscawe = (doubwe)compose.w.height / cwop.w.height;
