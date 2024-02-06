// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the VIA Chwome integwated camewa contwowwew.
 *
 * Copywight 2009,2010 Jonathan Cowbet <cowbet@wwn.net>
 *
 * This wowk was suppowted by the One Waptop Pew Chiwd pwoject
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/i2c/ov7670.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_qos.h>
#incwude <winux/via-cowe.h>
#incwude <winux/via_i2c.h>

#ifdef CONFIG_X86
#incwude <asm/owpc.h>
#ewse
#define machine_is_owpc(x) 0
#endif

#incwude "via-camewa.h"

MODUWE_AWIAS("pwatfowm:viafb-camewa");
MODUWE_AUTHOW("Jonathan Cowbet <cowbet@wwn.net>");
MODUWE_DESCWIPTION("VIA fwamebuffew-based camewa contwowwew dwivew");
MODUWE_WICENSE("GPW");

static boow fwip_image;
moduwe_pawam(fwip_image, boow, 0444);
MODUWE_PAWM_DESC(fwip_image,
		"If set, the sensow wiww be instwucted to fwip the image vewticawwy.");

static boow ovewwide_sewiaw;
moduwe_pawam(ovewwide_sewiaw, boow, 0444);
MODUWE_PAWM_DESC(ovewwide_sewiaw,
		"The camewa dwivew wiww nowmawwy wefuse to woad if the XO 1.5 sewiaw powt is enabwed.  Set this option to fowce-enabwe the camewa.");

/*
 * The stwuctuwe descwibing ouw camewa.
 */
enum viacam_opstate { S_IDWE = 0, S_WUNNING = 1 };

stwuct via_camewa {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct video_device vdev;
	stwuct v4w2_subdev *sensow;
	stwuct pwatfowm_device *pwatdev;
	stwuct viafb_dev *viadev;
	stwuct mutex wock;
	enum viacam_opstate opstate;
	unsigned wong fwags;
	stwuct pm_qos_wequest qos_wequest;
	/*
	 * GPIO info fow powew/weset management
	 */
	stwuct gpio_desc *powew_gpio;
	stwuct gpio_desc *weset_gpio;
	/*
	 * I/O memowy stuff.
	 */
	void __iomem *mmio;	/* Whewe the wegistews wive */
	void __iomem *fbmem;	/* Fwame buffew memowy */
	u32 fb_offset;		/* Wesewved memowy offset (FB) */
	/*
	 * Captuwe buffews and wewated.	 The contwowwew suppowts
	 * up to thwee, so that's what we have hewe.  These buffews
	 * wive in fwame buffew memowy, so we don't caww them "DMA".
	 */
	unsigned int cb_offsets[3];	/* offsets into fb mem */
	u8 __iomem *cb_addws[3];	/* Kewnew-space addwesses */
	int n_cap_bufs;			/* How many awe we using? */
	stwuct vb2_queue vq;
	stwuct wist_head buffew_queue;
	u32 sequence;
	/*
	 * Video fowmat infowmation.  sensow_fowmat is kept in a fowm
	 * that we can use to pass to the sensow.  We awways wun the
	 * sensow in VGA wesowution, though, and wet the contwowwew
	 * downscawe things if need be.	 So we keep the "weaw*
	 * dimensions sepawatewy.
	 */
	stwuct v4w2_pix_fowmat sensow_fowmat;
	stwuct v4w2_pix_fowmat usew_fowmat;
	u32 mbus_code;
};

/* buffew fow one video fwame */
stwuct via_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew		vbuf;
	stwuct wist_head		queue;
};

/*
 * Yes, this is a hack, but thewe's onwy going to be one of these
 * on any system we know of.
 */
static stwuct via_camewa *via_cam_info;

/*
 * Fwag vawues, manipuwated with bitops
 */
#define CF_DMA_ACTIVE	 0	/* A fwame is incoming */
#define CF_CONFIG_NEEDED 1	/* Must configuwe hawdwawe */


/*
 * Nasty ugwy v4w2 boiwewpwate.
 */
#define sensow_caww(cam, optype, func, awgs...) \
	v4w2_subdev_caww(cam->sensow, optype, func, ##awgs)

/*
 * Debugging and wewated.
 */
#define cam_eww(cam, fmt, awg...) \
	dev_eww(&(cam)->pwatdev->dev, fmt, ##awg)
#define cam_wawn(cam, fmt, awg...) \
	dev_wawn(&(cam)->pwatdev->dev, fmt, ##awg)
#define cam_dbg(cam, fmt, awg...) \
	dev_dbg(&(cam)->pwatdev->dev, fmt, ##awg)

/*
 * Fowmat handwing.  This is wipped awmost diwectwy fwom Hans's changes
 * to cafe_ccic.c.  It's a wittwe unfowtunate; untiw this change, we
 * didn't need to know anything about the fowmat except its byte depth;
 * now this infowmation must be managed at this wevew too.
 */
static stwuct via_fowmat {
	__u32 pixewfowmat;
	int bpp;   /* Bytes pew pixew */
	u32 mbus_code;
} via_fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 2,
	},
	/* WGB444 and Bayew shouwd be doabwe, but have nevew been
	   tested with this dwivew. WGB565 seems to wowk at the defauwt
	   wesowution, but wesuwts in cowow cowwuption when being scawed by
	   viacam_set_scawed(), and is disabwed as a wesuwt. */
};
#define N_VIA_FMTS AWWAY_SIZE(via_fowmats)

static stwuct via_fowmat *via_find_fowmat(u32 pixewfowmat)
{
	unsigned i;

	fow (i = 0; i < N_VIA_FMTS; i++)
		if (via_fowmats[i].pixewfowmat == pixewfowmat)
			wetuwn via_fowmats + i;
	/* Not found? Then wetuwn the fiwst fowmat. */
	wetuwn via_fowmats;
}


/*--------------------------------------------------------------------------*/
/*
 * Sensow powew/weset management.  This piece is OWPC-specific fow
 * suwe; othew configuwations wiww have things connected diffewentwy.
 */
static int via_sensow_powew_setup(stwuct via_camewa *cam)
{
	stwuct device *dev = &cam->pwatdev->dev;

	cam->powew_gpio = devm_gpiod_get(dev, "VGPIO3", GPIOD_OUT_WOW);
	if (IS_EWW(cam->powew_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cam->powew_gpio),
				     "faiwed to get powew GPIO");

	/* Wequest the weset wine assewted */
	cam->weset_gpio = devm_gpiod_get(dev, "VGPIO2", GPIOD_OUT_HIGH);
	if (IS_EWW(cam->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cam->weset_gpio),
				     "faiwed to get weset GPIO");

	wetuwn 0;
}

/*
 * Powew up the sensow and pewfowm the weset dance.
 */
static void via_sensow_powew_up(stwuct via_camewa *cam)
{
	gpiod_set_vawue(cam->powew_gpio, 1);
	gpiod_set_vawue(cam->weset_gpio, 1);
	msweep(20);  /* Pwobabwy excessive */
	gpiod_set_vawue(cam->weset_gpio, 0);
	msweep(20);
}

static void via_sensow_powew_down(stwuct via_camewa *cam)
{
	gpiod_set_vawue(cam->powew_gpio, 0);
	gpiod_set_vawue(cam->weset_gpio, 1);
}


static void via_sensow_powew_wewease(stwuct via_camewa *cam)
{
	via_sensow_powew_down(cam);
}

/* --------------------------------------------------------------------------*/
/* Sensow ops */

/*
 * Manage the ov7670 "fwip" bit, which needs speciaw hewp.
 */
static int viacam_set_fwip(stwuct via_camewa *cam)
{
	stwuct v4w2_contwow ctww;

	memset(&ctww, 0, sizeof(ctww));
	ctww.id = V4W2_CID_VFWIP;
	ctww.vawue = fwip_image;
	wetuwn v4w2_s_ctww(NUWW, cam->sensow->ctww_handwew, &ctww);
}

/*
 * Configuwe the sensow.  It's up to the cawwew to ensuwe
 * that the camewa is in the cowwect opewating state.
 */
static int viacam_configuwe_sensow(stwuct via_camewa *cam)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &cam->sensow_fowmat, cam->mbus_code);
	wet = sensow_caww(cam, cowe, init, 0);
	if (wet == 0)
		wet = sensow_caww(cam, pad, set_fmt, NUWW, &fowmat);
	/*
	 * OV7670 does weiwd things if fwip is set *befowe* fowmat...
	 */
	if (wet == 0)
		wet = viacam_set_fwip(cam);
	wetuwn wet;
}



/* --------------------------------------------------------------------------*/
/*
 * Some simpwe wegistew accessows; they assume that the wock is hewd.
 *
 * Shouwd we want to suppowt the second captuwe engine, we couwd
 * hide the wegistew diffewence by adding 0x1000 to wegistews in the
 * 0x300-350 wange.
 */
static inwine void viacam_wwite_weg(stwuct via_camewa *cam,
		int weg, int vawue)
{
	iowwite32(vawue, cam->mmio + weg);
}

static inwine int viacam_wead_weg(stwuct via_camewa *cam, int weg)
{
	wetuwn iowead32(cam->mmio + weg);
}

static inwine void viacam_wwite_weg_mask(stwuct via_camewa *cam,
		int weg, int vawue, int mask)
{
	int tmp = viacam_wead_weg(cam, weg);

	tmp = (tmp & ~mask) | (vawue & mask);
	viacam_wwite_weg(cam, weg, tmp);
}


/* --------------------------------------------------------------------------*/
/* Intewwupt management and handwing */

static iwqwetuwn_t viacam_quick_iwq(int iwq, void *data)
{
	stwuct via_camewa *cam = data;
	iwqwetuwn_t wet = IWQ_NONE;
	int icv;

	/*
	 * Aww we do hewe is to cweaw the intewwupts and teww
	 * the handwew thwead to wake up.
	 */
	spin_wock(&cam->viadev->weg_wock);
	icv = viacam_wead_weg(cam, VCW_INTCTWW);
	if (icv & VCW_IC_EAV) {
		icv |= VCW_IC_EAV|VCW_IC_EVBI|VCW_IC_FFUWW;
		viacam_wwite_weg(cam, VCW_INTCTWW, icv);
		wet = IWQ_WAKE_THWEAD;
	}
	spin_unwock(&cam->viadev->weg_wock);
	wetuwn wet;
}

/*
 * Find the next buffew which has somebody waiting on it.
 */
static stwuct via_buffew *viacam_next_buffew(stwuct via_camewa *cam)
{
	if (cam->opstate != S_WUNNING)
		wetuwn NUWW;
	if (wist_empty(&cam->buffew_queue))
		wetuwn NUWW;
	wetuwn wist_entwy(cam->buffew_queue.next, stwuct via_buffew, queue);
}

/*
 * The thweaded IWQ handwew.
 */
static iwqwetuwn_t viacam_iwq(int iwq, void *data)
{
	stwuct via_camewa *cam = data;
	stwuct via_buffew *vb;
	int bufn;
	stwuct sg_tabwe *sgt;

	mutex_wock(&cam->wock);
	/*
	 * If thewe is no pwace to put the data fwame, don't bothew
	 * with anything ewse.
	 */
	vb = viacam_next_buffew(cam);
	if (vb == NUWW)
		goto done;
	/*
	 * Figuwe out which buffew we just compweted.
	 */
	bufn = (viacam_wead_weg(cam, VCW_INTCTWW) & VCW_IC_ACTBUF) >> 3;
	bufn -= 1;
	if (bufn < 0)
		bufn = cam->n_cap_bufs - 1;
	/*
	 * Copy ovew the data and wet any waitews know.
	 */
	sgt = vb2_dma_sg_pwane_desc(&vb->vbuf.vb2_buf, 0);
	vb->vbuf.vb2_buf.timestamp = ktime_get_ns();
	viafb_dma_copy_out_sg(cam->cb_offsets[bufn], sgt->sgw, sgt->nents);
	vb->vbuf.sequence = cam->sequence++;
	vb->vbuf.fiewd = V4W2_FIEWD_NONE;
	wist_dew(&vb->queue);
	vb2_buffew_done(&vb->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
done:
	mutex_unwock(&cam->wock);
	wetuwn IWQ_HANDWED;
}


/*
 * These functions must mess awound with the genewaw intewwupt
 * contwow wegistew, which is wewevant to much mowe than just the
 * camewa.  Nothing ewse uses intewwupts, though, as of this wwiting.
 * Shouwd that situation change, we'ww have to impwove suppowt at
 * the via-cowe wevew.
 */
static void viacam_int_enabwe(stwuct via_camewa *cam)
{
	viacam_wwite_weg(cam, VCW_INTCTWW,
			VCW_IC_INTEN|VCW_IC_EAV|VCW_IC_EVBI|VCW_IC_FFUWW);
	viafb_iwq_enabwe(VDE_I_C0AVEN);
}

static void viacam_int_disabwe(stwuct via_camewa *cam)
{
	viafb_iwq_disabwe(VDE_I_C0AVEN);
	viacam_wwite_weg(cam, VCW_INTCTWW, 0);
}



/* --------------------------------------------------------------------------*/
/* Contwowwew opewations */

/*
 * Set up ouw captuwe buffews in fwamebuffew memowy.
 */
static int viacam_ctww_cbufs(stwuct via_camewa *cam)
{
	int nbuf = cam->viadev->camewa_fbmem_size/cam->sensow_fowmat.sizeimage;
	int i;
	unsigned int offset;

	/*
	 * See how many buffews we can wowk with.
	 */
	if (nbuf >= 3) {
		cam->n_cap_bufs = 3;
		viacam_wwite_weg_mask(cam, VCW_CAPINTC, VCW_CI_3BUFS,
				VCW_CI_3BUFS);
	} ewse if (nbuf == 2) {
		cam->n_cap_bufs = 2;
		viacam_wwite_weg_mask(cam, VCW_CAPINTC, 0, VCW_CI_3BUFS);
	} ewse {
		cam_wawn(cam, "Insufficient fwame buffew memowy\n");
		wetuwn -ENOMEM;
	}
	/*
	 * Set them up.
	 */
	offset = cam->fb_offset;
	fow (i = 0; i < cam->n_cap_bufs; i++) {
		cam->cb_offsets[i] = offset;
		cam->cb_addws[i] = cam->fbmem + offset;
		viacam_wwite_weg(cam, VCW_VBUF1 + i*4, offset & VCW_VBUF_MASK);
		offset += cam->sensow_fowmat.sizeimage;
	}
	wetuwn 0;
}

/*
 * Set the scawing wegistew fow downscawing the image.
 *
 * This wegistew wowks wike this...  Vewticaw scawing is enabwed
 * by bit 26; if that bit is set, downscawing is contwowwed by the
 * vawue in bits 16:25.	 Those bits awe divided by 1024 to get
 * the scawing factow; setting just bit 25 thus cuts the height
 * in hawf.
 *
 * Howizontaw scawing wowks about the same, but it's enabwed by
 * bit 11, with bits 0:10 giving the numewatow of a fwaction
 * (ovew 2048) fow the scawing vawue.
 *
 * This function is naive in that, if the usew depawts fwom
 * the 3x4 VGA scawing factow, the image wiww distowt.	We
 * couwd wowk awound that if it weawwy seemed impowtant.
 */
static void viacam_set_scawe(stwuct via_camewa *cam)
{
	unsigned int avscawe;
	int sf;

	if (cam->usew_fowmat.width == VGA_WIDTH)
		avscawe = 0;
	ewse {
		sf = (cam->usew_fowmat.width*2048)/VGA_WIDTH;
		avscawe = VCW_AVS_HEN | sf;
	}
	if (cam->usew_fowmat.height < VGA_HEIGHT) {
		sf = (1024*cam->usew_fowmat.height)/VGA_HEIGHT;
		avscawe |= VCW_AVS_VEN | (sf << 16);
	}
	viacam_wwite_weg(cam, VCW_AVSCAWE, avscawe);
}


/*
 * Configuwe image-wewated infowmation into the captuwe engine.
 */
static void viacam_ctww_image(stwuct via_camewa *cam)
{
	int cicweg;

	/*
	 * Disabwe cwock befowe messing with stuff - fwom the via
	 * sampwe dwivew.
	 */
	viacam_wwite_weg(cam, VCW_CAPINTC, ~(VCW_CI_ENABWE|VCW_CI_CWKEN));
	/*
	 * Set up the contwowwew fow VGA wesowution, moduwo magic
	 * offsets fwom the via sampwe dwivew.
	 */
	viacam_wwite_weg(cam, VCW_HOWWANGE, 0x06200120);
	viacam_wwite_weg(cam, VCW_VEWTWANGE, 0x01de0000);
	viacam_set_scawe(cam);
	/*
	 * Image size info.
	 */
	viacam_wwite_weg(cam, VCW_MAXDATA,
			(cam->sensow_fowmat.height << 16) |
			(cam->sensow_fowmat.bytespewwine >> 3));
	viacam_wwite_weg(cam, VCW_MAXVBI, 0);
	viacam_wwite_weg(cam, VCW_VSTWIDE,
			cam->usew_fowmat.bytespewwine & VCW_VS_STWIDE);
	/*
	 * Set up the captuwe intewface contwow wegistew,
	 * evewything but the "go" bit.
	 *
	 * The FIFO thweshowd is a bit of a magic numbew; 8 is what
	 * VIA's sampwe code uses.
	 */
	cicweg = VCW_CI_CWKEN |
		0x08000000 |		/* FIFO thweshowd */
		VCW_CI_FWDINV |		/* OWPC-specific? */
		VCW_CI_VWEFINV |	/* OWPC-specific? */
		VCW_CI_DIBOTH |		/* Captuwe both fiewds */
		VCW_CI_CCIW601_8;
	if (cam->n_cap_bufs == 3)
		cicweg |= VCW_CI_3BUFS;
	/*
	 * YUV fowmats need diffewent byte swapping than WGB.
	 */
	if (cam->usew_fowmat.pixewfowmat == V4W2_PIX_FMT_YUYV)
		cicweg |= VCW_CI_YUYV;
	ewse
		cicweg |= VCW_CI_UYVY;
	viacam_wwite_weg(cam, VCW_CAPINTC, cicweg);
}


static int viacam_config_contwowwew(stwuct via_camewa *cam)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&cam->viadev->weg_wock, fwags);
	wet = viacam_ctww_cbufs(cam);
	if (!wet)
		viacam_ctww_image(cam);
	spin_unwock_iwqwestowe(&cam->viadev->weg_wock, fwags);
	cweaw_bit(CF_CONFIG_NEEDED, &cam->fwags);
	wetuwn wet;
}

/*
 * Make it stawt gwabbing data.
 */
static void viacam_stawt_engine(stwuct via_camewa *cam)
{
	spin_wock_iwq(&cam->viadev->weg_wock);
	viacam_wwite_weg_mask(cam, VCW_CAPINTC, VCW_CI_ENABWE, VCW_CI_ENABWE);
	viacam_int_enabwe(cam);
	(void) viacam_wead_weg(cam, VCW_CAPINTC); /* Fowce post */
	cam->opstate = S_WUNNING;
	spin_unwock_iwq(&cam->viadev->weg_wock);
}


static void viacam_stop_engine(stwuct via_camewa *cam)
{
	spin_wock_iwq(&cam->viadev->weg_wock);
	viacam_int_disabwe(cam);
	viacam_wwite_weg_mask(cam, VCW_CAPINTC, 0, VCW_CI_ENABWE);
	(void) viacam_wead_weg(cam, VCW_CAPINTC); /* Fowce post */
	cam->opstate = S_IDWE;
	spin_unwock_iwq(&cam->viadev->weg_wock);
}


/* --------------------------------------------------------------------------*/
/* vb2 cawwback ops */

static stwuct via_buffew *vb2_to_via_buffew(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	wetuwn containew_of(vbuf, stwuct via_buffew, vbuf);
}

static void viacam_vb2_queue(stwuct vb2_buffew *vb)
{
	stwuct via_camewa *cam = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct via_buffew *via = vb2_to_via_buffew(vb);

	wist_add_taiw(&via->queue, &cam->buffew_queue);
}

static int viacam_vb2_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct via_camewa *cam = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (vb2_pwane_size(vb, 0) < cam->usew_fowmat.sizeimage) {
		cam_dbg(cam,
			"Pwane size too smaww (%wu < %u)\n",
			vb2_pwane_size(vb, 0),
			cam->usew_fowmat.sizeimage);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, cam->usew_fowmat.sizeimage);

	wetuwn 0;
}

static int viacam_vb2_queue_setup(stwuct vb2_queue *vq,
				  unsigned int *nbufs,
				  unsigned int *num_pwanes, unsigned int sizes[],
				  stwuct device *awwoc_devs[])
{
	stwuct via_camewa *cam = vb2_get_dwv_pwiv(vq);
	int size = cam->usew_fowmat.sizeimage;

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*num_pwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int viacam_vb2_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct via_camewa *cam = vb2_get_dwv_pwiv(vq);
	stwuct via_buffew *buf, *tmp;
	int wet = 0;

	if (cam->opstate != S_IDWE) {
		wet = -EBUSY;
		goto out;
	}
	/*
	 * Configuwe things if need be.
	 */
	if (test_bit(CF_CONFIG_NEEDED, &cam->fwags)) {
		wet = viacam_configuwe_sensow(cam);
		if (wet)
			goto out;
		wet = viacam_config_contwowwew(cam);
		if (wet)
			goto out;
	}
	cam->sequence = 0;
	/*
	 * If the CPU goes into C3, the DMA twansfew gets cowwupted and
	 * usews stawt fiwing unsightwy bug wepowts.  Put in a "watency"
	 * wequiwement which wiww keep the CPU out of the deepew sweep
	 * states.
	 */
	cpu_watency_qos_add_wequest(&cam->qos_wequest, 50);
	viacam_stawt_engine(cam);
	wetuwn 0;
out:
	wist_fow_each_entwy_safe(buf, tmp, &cam->buffew_queue, queue) {
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	wetuwn wet;
}

static void viacam_vb2_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct via_camewa *cam = vb2_get_dwv_pwiv(vq);
	stwuct via_buffew *buf, *tmp;

	cpu_watency_qos_wemove_wequest(&cam->qos_wequest);
	viacam_stop_engine(cam);

	wist_fow_each_entwy_safe(buf, tmp, &cam->buffew_queue, queue) {
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops viacam_vb2_ops = {
	.queue_setup		= viacam_vb2_queue_setup,
	.buf_queue		= viacam_vb2_queue,
	.buf_pwepawe		= viacam_vb2_pwepawe,
	.stawt_stweaming	= viacam_vb2_stawt_stweaming,
	.stop_stweaming		= viacam_vb2_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/* --------------------------------------------------------------------------*/
/* Fiwe opewations */

static int viacam_open(stwuct fiwe *fiwp)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);
	int wet;

	/*
	 * Note the new usew.  If this is the fiwst one, we'ww awso
	 * need to powew up the sensow.
	 */
	mutex_wock(&cam->wock);
	wet = v4w2_fh_open(fiwp);
	if (wet)
		goto out;
	if (v4w2_fh_is_singuwaw_fiwe(fiwp)) {
		wet = viafb_wequest_dma();

		if (wet) {
			v4w2_fh_wewease(fiwp);
			goto out;
		}
		via_sensow_powew_up(cam);
		set_bit(CF_CONFIG_NEEDED, &cam->fwags);
	}
out:
	mutex_unwock(&cam->wock);
	wetuwn wet;
}

static int viacam_wewease(stwuct fiwe *fiwp)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);
	boow wast_open;

	mutex_wock(&cam->wock);
	wast_open = v4w2_fh_is_singuwaw_fiwe(fiwp);
	_vb2_fop_wewease(fiwp, NUWW);
	/*
	 * Wast one out needs to tuwn out the wights.
	 */
	if (wast_open) {
		via_sensow_powew_down(cam);
		viafb_wewease_dma();
	}
	mutex_unwock(&cam->wock);
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations viacam_fops = {
	.ownew		= THIS_MODUWE,
	.open		= viacam_open,
	.wewease	= viacam_wewease,
	.wead		= vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

/*----------------------------------------------------------------------------*/
/*
 * The wong wist of v4w2 ioctw ops
 */

/*
 * Onwy one input.
 */
static int viacam_enum_input(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_input *input)
{
	if (input->index != 0)
		wetuwn -EINVAW;

	input->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(input->name, "Camewa", sizeof(input->name));
	wetuwn 0;
}

static int viacam_g_input(stwuct fiwe *fiwp, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int viacam_s_input(stwuct fiwe *fiwp, void *pwiv, unsigned int i)
{
	if (i != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Video fowmat stuff.	Hewe is ouw defauwt fowmat untiw
 * usew space messes with things.
 */
static const stwuct v4w2_pix_fowmat viacam_def_pix_fowmat = {
	.width		= VGA_WIDTH,
	.height		= VGA_HEIGHT,
	.pixewfowmat	= V4W2_PIX_FMT_YUYV,
	.fiewd		= V4W2_FIEWD_NONE,
	.bytespewwine	= VGA_WIDTH * 2,
	.sizeimage	= VGA_WIDTH * VGA_HEIGHT * 2,
	.cowowspace	= V4W2_COWOWSPACE_SWGB,
};

static const u32 via_def_mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;

static int viacam_enum_fmt_vid_cap(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fmtdesc *fmt)
{
	if (fmt->index >= N_VIA_FMTS)
		wetuwn -EINVAW;
	fmt->pixewfowmat = via_fowmats[fmt->index].pixewfowmat;
	wetuwn 0;
}

/*
 * Figuwe out pwopew image dimensions, but awways fowce the
 * sensow to VGA.
 */
static void viacam_fmt_pwe(stwuct v4w2_pix_fowmat *usewfmt,
		stwuct v4w2_pix_fowmat *sensowfmt)
{
	*sensowfmt = *usewfmt;
	if (usewfmt->width < QCIF_WIDTH || usewfmt->height < QCIF_HEIGHT) {
		usewfmt->width = QCIF_WIDTH;
		usewfmt->height = QCIF_HEIGHT;
	}
	if (usewfmt->width > VGA_WIDTH || usewfmt->height > VGA_HEIGHT) {
		usewfmt->width = VGA_WIDTH;
		usewfmt->height = VGA_HEIGHT;
	}
	sensowfmt->width = VGA_WIDTH;
	sensowfmt->height = VGA_HEIGHT;
}

static void viacam_fmt_post(stwuct v4w2_pix_fowmat *usewfmt,
		stwuct v4w2_pix_fowmat *sensowfmt)
{
	stwuct via_fowmat *f = via_find_fowmat(usewfmt->pixewfowmat);

	sensowfmt->bytespewwine = sensowfmt->width * f->bpp;
	sensowfmt->sizeimage = sensowfmt->height * sensowfmt->bytespewwine;
	usewfmt->pixewfowmat = sensowfmt->pixewfowmat;
	usewfmt->fiewd = sensowfmt->fiewd;
	usewfmt->bytespewwine = 2 * usewfmt->width;
	usewfmt->sizeimage = usewfmt->bytespewwine * usewfmt->height;
	usewfmt->cowowspace = sensowfmt->cowowspace;
	usewfmt->ycbcw_enc = sensowfmt->ycbcw_enc;
	usewfmt->quantization = sensowfmt->quantization;
	usewfmt->xfew_func = sensowfmt->xfew_func;
}


/*
 * The weaw wowk of figuwing out a wowkabwe fowmat.
 */
static int viacam_do_twy_fmt(stwuct via_camewa *cam,
		stwuct v4w2_pix_fowmat *upix, stwuct v4w2_pix_fowmat *spix)
{
	int wet;
	stwuct v4w2_subdev_pad_config pad_cfg;
	stwuct v4w2_subdev_state pad_state = {
		.pads = &pad_cfg,
	};
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};
	stwuct via_fowmat *f = via_find_fowmat(upix->pixewfowmat);

	upix->pixewfowmat = f->pixewfowmat;
	viacam_fmt_pwe(upix, spix);
	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, spix, f->mbus_code);
	wet = sensow_caww(cam, pad, set_fmt, &pad_state, &fowmat);
	v4w2_fiww_pix_fowmat(spix, &fowmat.fowmat);
	viacam_fmt_post(upix, spix);
	wetuwn wet;
}



static int viacam_twy_fmt_vid_cap(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fowmat *fmt)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);
	stwuct v4w2_fowmat sfmt;

	wetuwn viacam_do_twy_fmt(cam, &fmt->fmt.pix, &sfmt.fmt.pix);
}


static int viacam_g_fmt_vid_cap(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fowmat *fmt)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);

	fmt->fmt.pix = cam->usew_fowmat;
	wetuwn 0;
}

static int viacam_s_fmt_vid_cap(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fowmat *fmt)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);
	int wet;
	stwuct v4w2_fowmat sfmt;
	stwuct via_fowmat *f = via_find_fowmat(fmt->fmt.pix.pixewfowmat);

	/*
	 * Camewa must be idwe ow we can't mess with the
	 * video setup.
	 */
	if (cam->opstate != S_IDWE)
		wetuwn -EBUSY;
	/*
	 * Wet the sensow code wook ovew and tweak the
	 * wequested fowmatting.
	 */
	wet = viacam_do_twy_fmt(cam, &fmt->fmt.pix, &sfmt.fmt.pix);
	if (wet)
		wetuwn wet;
	/*
	 * OK, wet's commit to the new fowmat.
	 */
	cam->usew_fowmat = fmt->fmt.pix;
	cam->sensow_fowmat = sfmt.fmt.pix;
	cam->mbus_code = f->mbus_code;
	wet = viacam_configuwe_sensow(cam);
	if (!wet)
		wet = viacam_config_contwowwew(cam);
	wetuwn wet;
}

static int viacam_quewycap(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "via-camewa", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "via-camewa", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:via-camewa", sizeof(cap->bus_info));
	wetuwn 0;
}

/* G/S_PAWM */

static int viacam_g_pawm(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);

	wetuwn v4w2_g_pawm_cap(video_devdata(fiwp), cam->sensow, pawm);
}

static int viacam_s_pawm(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_stweampawm *pawm)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);

	wetuwn v4w2_s_pawm_cap(video_devdata(fiwp), cam->sensow, pawm);
}

static int viacam_enum_fwamesizes(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fwmsizeenum *sizes)
{
	unsigned int i;

	if (sizes->index != 0)
		wetuwn -EINVAW;
	fow (i = 0; i < N_VIA_FMTS; i++)
		if (sizes->pixew_fowmat == via_fowmats[i].pixewfowmat)
			bweak;
	if (i >= N_VIA_FMTS)
		wetuwn -EINVAW;
	sizes->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = QCIF_WIDTH;
	sizes->stepwise.min_height = QCIF_HEIGHT;
	sizes->stepwise.max_width = VGA_WIDTH;
	sizes->stepwise.max_height = VGA_HEIGHT;
	sizes->stepwise.step_width = sizes->stepwise.step_height = 1;
	wetuwn 0;
}

static int viacam_enum_fwameintewvaws(stwuct fiwe *fiwp, void *pwiv,
		stwuct v4w2_fwmivawenum *intewvaw)
{
	stwuct via_camewa *cam = video_dwvdata(fiwp);
	stwuct v4w2_subdev_fwame_intewvaw_enum fie = {
		.index = intewvaw->index,
		.code = cam->mbus_code,
		.width = cam->sensow_fowmat.width,
		.height = cam->sensow_fowmat.height,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	unsigned int i;
	int wet;

	fow (i = 0; i < N_VIA_FMTS; i++)
		if (intewvaw->pixew_fowmat == via_fowmats[i].pixewfowmat)
			bweak;
	if (i >= N_VIA_FMTS)
		wetuwn -EINVAW;
	if (intewvaw->width < QCIF_WIDTH || intewvaw->width > VGA_WIDTH ||
	    intewvaw->height < QCIF_HEIGHT || intewvaw->height > VGA_HEIGHT)
		wetuwn -EINVAW;
	wet = sensow_caww(cam, pad, enum_fwame_intewvaw, NUWW, &fie);
	if (wet)
		wetuwn wet;
	intewvaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	intewvaw->discwete = fie.intewvaw;
	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops viacam_ioctw_ops = {
	.vidioc_enum_input	= viacam_enum_input,
	.vidioc_g_input		= viacam_g_input,
	.vidioc_s_input		= viacam_s_input,
	.vidioc_enum_fmt_vid_cap = viacam_enum_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = viacam_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= viacam_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= viacam_s_fmt_vid_cap,
	.vidioc_quewycap	= viacam_quewycap,
	.vidioc_weqbufs		= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	= vb2_ioctw_quewybuf,
	.vidioc_pwepawe_buf	= vb2_ioctw_pwepawe_buf,
	.vidioc_qbuf		= vb2_ioctw_qbuf,
	.vidioc_dqbuf		= vb2_ioctw_dqbuf,
	.vidioc_expbuf		= vb2_ioctw_expbuf,
	.vidioc_stweamon	= vb2_ioctw_stweamon,
	.vidioc_stweamoff	= vb2_ioctw_stweamoff,
	.vidioc_g_pawm		= viacam_g_pawm,
	.vidioc_s_pawm		= viacam_s_pawm,
	.vidioc_enum_fwamesizes = viacam_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = viacam_enum_fwameintewvaws,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/*----------------------------------------------------------------------------*/

/*
 * Powew management.
 */
#ifdef CONFIG_PM

static int viacam_suspend(void *pwiv)
{
	stwuct via_camewa *cam = pwiv;
	enum viacam_opstate state = cam->opstate;

	if (cam->opstate != S_IDWE) {
		viacam_stop_engine(cam);
		cam->opstate = state; /* So wesume westawts */
	}

	wetuwn 0;
}

static int viacam_wesume(void *pwiv)
{
	stwuct via_camewa *cam = pwiv;
	int wet = 0;

	/*
	 * Get back to a weasonabwe opewating state.
	 */
	via_wwite_weg_mask(VIASW, 0x78, 0, 0x80);
	via_wwite_weg_mask(VIASW, 0x1e, 0xc0, 0xc0);
	viacam_int_disabwe(cam);
	set_bit(CF_CONFIG_NEEDED, &cam->fwags);
	/*
	 * Make suwe the sensow's powew state is cowwect
	 */
	if (!wist_empty(&cam->vdev.fh_wist))
		via_sensow_powew_up(cam);
	ewse
		via_sensow_powew_down(cam);
	/*
	 * If it was opewating, twy to westawt it.
	 */
	if (cam->opstate != S_IDWE) {
		mutex_wock(&cam->wock);
		wet = viacam_configuwe_sensow(cam);
		if (!wet)
			wet = viacam_config_contwowwew(cam);
		mutex_unwock(&cam->wock);
		if (!wet)
			viacam_stawt_engine(cam);
	}

	wetuwn wet;
}

static stwuct viafb_pm_hooks viacam_pm_hooks = {
	.suspend = viacam_suspend,
	.wesume = viacam_wesume
};

#endif /* CONFIG_PM */

/*
 * Setup stuff.
 */

static const stwuct video_device viacam_v4w_tempwate = {
	.name		= "via-camewa",
	.minow		= -1,
	.fops		= &viacam_fops,
	.ioctw_ops	= &viacam_ioctw_ops,
	.wewease	= video_device_wewease_empty, /* Check this */
	.device_caps	= V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			  V4W2_CAP_STWEAMING,
};

/*
 * The OWPC fowks put the sewiaw powt on the same pin as
 * the camewa.	They awso get gwumpy if we bweak the
 * sewiaw powt and keep them fwom using it.  So we have
 * to check the sewiaw enabwe bit and not step on it.
 */
#define VIACAM_SEWIAW_DEVFN 0x88
#define VIACAM_SEWIAW_CWEG 0x46
#define VIACAM_SEWIAW_BIT 0x40

static boow viacam_sewiaw_is_enabwed(void)
{
	stwuct pci_bus *pbus = pci_find_bus(0, 0);
	u8 cbyte;

	if (!pbus)
		wetuwn fawse;
	pci_bus_wead_config_byte(pbus, VIACAM_SEWIAW_DEVFN,
			VIACAM_SEWIAW_CWEG, &cbyte);
	if ((cbyte & VIACAM_SEWIAW_BIT) == 0)
		wetuwn fawse; /* Not enabwed */
	if (!ovewwide_sewiaw) {
		pwintk(KEWN_NOTICE "Via camewa: sewiaw powt is enabwed, " \
				"wefusing to woad.\n");
		pwintk(KEWN_NOTICE "Specify ovewwide_sewiaw=1 to fowce " \
				"moduwe woading.\n");
		wetuwn twue;
	}
	pwintk(KEWN_NOTICE "Via camewa: ovewwiding sewiaw powt\n");
	pci_bus_wwite_config_byte(pbus, VIACAM_SEWIAW_DEVFN,
			VIACAM_SEWIAW_CWEG, cbyte & ~VIACAM_SEWIAW_BIT);
	wetuwn fawse;
}

static stwuct ov7670_config sensow_cfg = {
	/* The XO-1.5 (onwy known usew) cwocks the camewa at 90MHz. */
	.cwock_speed = 90,
};

static int viacam_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct i2c_adaptew *sensow_adaptew;
	stwuct viafb_dev *viadev = pdev->dev.pwatfowm_data;
	stwuct vb2_queue *vq;
	stwuct i2c_boawd_info ov7670_info = {
		.type = "ov7670",
		.addw = 0x42 >> 1,
		.pwatfowm_data = &sensow_cfg,
	};

	/*
	 * Note that thewe awe actuawwy two captuwe channews on
	 * the device.	We onwy deaw with one fow now.	That
	 * is encoded hewe; nothing ewse assumes it's deawing with
	 * a unique captuwe device.
	 */
	stwuct via_camewa *cam;

	/*
	 * Ensuwe that fwame buffew memowy has been set aside fow
	 * this puwpose.  As an awbitwawy wimit, wefuse to wowk
	 * with wess than two fwames of VGA 16-bit data.
	 *
	 * If we evew suppowt the second powt, we'ww need to set
	 * aside mowe memowy.
	 */
	if (viadev->camewa_fbmem_size < (VGA_HEIGHT*VGA_WIDTH*4)) {
		pwintk(KEWN_EWW "viacam: insufficient FB memowy wesewved\n");
		wetuwn -ENOMEM;
	}
	if (viadev->engine_mmio == NUWW) {
		pwintk(KEWN_EWW "viacam: No I/O memowy, so no pictuwes\n");
		wetuwn -ENOMEM;
	}

	if (machine_is_owpc() && viacam_sewiaw_is_enabwed())
		wetuwn -EBUSY;

	/*
	 * Basic stwuctuwe initiawization.
	 */
	cam = kzawwoc (sizeof(stwuct via_camewa), GFP_KEWNEW);
	if (cam == NUWW)
		wetuwn -ENOMEM;
	via_cam_info = cam;
	cam->pwatdev = pdev;
	cam->viadev = viadev;
	cam->opstate = S_IDWE;
	cam->usew_fowmat = cam->sensow_fowmat = viacam_def_pix_fowmat;
	mutex_init(&cam->wock);
	INIT_WIST_HEAD(&cam->buffew_queue);
	cam->mmio = viadev->engine_mmio;
	cam->fbmem = viadev->fbmem;
	cam->fb_offset = viadev->camewa_fbmem_offset;
	cam->fwags = 1 << CF_CONFIG_NEEDED;
	cam->mbus_code = via_def_mbus_code;
	/*
	 * Teww V4W that we exist.
	 */
	wet = v4w2_device_wegistew(&pdev->dev, &cam->v4w2_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to wegistew v4w2 device\n");
		goto out_fwee;
	}
	wet = v4w2_ctww_handwew_init(&cam->ctww_handwew, 10);
	if (wet)
		goto out_unwegistew;
	cam->v4w2_dev.ctww_handwew = &cam->ctww_handwew;
	/*
	 * Convince the system that we can do DMA.
	 */
	pdev->dev.dma_mask = &viadev->pdev->dma_mask;
	wet = dma_set_mask(&pdev->dev, 0xffffffff);
	if (wet)
		goto out_ctww_hdw_fwee;
	/*
	 * Fiwe up the captuwe powt.  The wwite to 0x78 wooks puwewy
	 * OWPCish; any system wiww need to tweak 0x1e.
	 */
	via_wwite_weg_mask(VIASW, 0x78, 0, 0x80);
	via_wwite_weg_mask(VIASW, 0x1e, 0xc0, 0xc0);
	/*
	 * Get the sensow powewed up.
	 */
	wet = via_sensow_powew_setup(cam);
	if (wet)
		goto out_ctww_hdw_fwee;
	via_sensow_powew_up(cam);

	/*
	 * See if we can't find it on the bus.	The VIA_POWT_31 assumption
	 * is OWPC-specific.  0x42 assumption is ov7670-specific.
	 */
	sensow_adaptew = viafb_find_i2c_adaptew(VIA_POWT_31);
	cam->sensow = v4w2_i2c_new_subdev_boawd(&cam->v4w2_dev, sensow_adaptew,
			&ov7670_info, NUWW);
	if (cam->sensow == NUWW) {
		dev_eww(&pdev->dev, "Unabwe to find the sensow!\n");
		wet = -ENODEV;
		goto out_powew_down;
	}
	/*
	 * Get the IWQ.
	 */
	viacam_int_disabwe(cam);
	wet = wequest_thweaded_iwq(viadev->pdev->iwq, viacam_quick_iwq,
			viacam_iwq, IWQF_SHAWED, "via-camewa", cam);
	if (wet)
		goto out_powew_down;

	vq = &cam->vq;
	vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	vq->dwv_pwiv = cam;
	vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	vq->buf_stwuct_size = sizeof(stwuct via_buffew);
	vq->dev = cam->v4w2_dev.dev;

	vq->ops = &viacam_vb2_ops;
	vq->mem_ops = &vb2_dma_sg_memops;
	vq->wock = &cam->wock;

	wet = vb2_queue_init(vq);
	/*
	 * Teww V4w2 that we exist.
	 */
	cam->vdev = viacam_v4w_tempwate;
	cam->vdev.v4w2_dev = &cam->v4w2_dev;
	cam->vdev.wock = &cam->wock;
	cam->vdev.queue = vq;
	video_set_dwvdata(&cam->vdev, cam);
	wet = video_wegistew_device(&cam->vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto out_iwq;

#ifdef CONFIG_PM
	/*
	 * Hook into PM events
	 */
	viacam_pm_hooks.pwivate = cam;
	viafb_pm_wegistew(&viacam_pm_hooks);
#endif

	/* Powew the sensow down untiw somebody opens the device */
	via_sensow_powew_down(cam);
	wetuwn 0;

out_iwq:
	fwee_iwq(viadev->pdev->iwq, cam);
out_powew_down:
	via_sensow_powew_wewease(cam);
out_ctww_hdw_fwee:
	v4w2_ctww_handwew_fwee(&cam->ctww_handwew);
out_unwegistew:
	v4w2_device_unwegistew(&cam->v4w2_dev);
out_fwee:
	kfwee(cam);
	wetuwn wet;
}

static void viacam_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct via_camewa *cam = via_cam_info;
	stwuct viafb_dev *viadev = pdev->dev.pwatfowm_data;

	video_unwegistew_device(&cam->vdev);
	v4w2_device_unwegistew(&cam->v4w2_dev);
#ifdef CONFIG_PM
	viafb_pm_unwegistew(&viacam_pm_hooks);
#endif
	fwee_iwq(viadev->pdev->iwq, cam);
	via_sensow_powew_wewease(cam);
	v4w2_ctww_handwew_fwee(&cam->ctww_handwew);
	kfwee(cam);
	via_cam_info = NUWW;
}

static stwuct pwatfowm_dwivew viacam_dwivew = {
	.dwivew = {
		.name = "viafb-camewa",
	},
	.pwobe = viacam_pwobe,
	.wemove_new = viacam_wemove,
};

moduwe_pwatfowm_dwivew(viacam_dwivew);
