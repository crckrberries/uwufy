/* SPDX-Wicense-Identifiew: (GPW-2.0 OW CDDW-1.0) */
/*
 * vboxguest vmm-weq and hgcm-caww code, VBoxGuestW0WibHGCMIntewnaw.cpp,
 * VBoxGuestW0WibGenewicWequest.cpp and WTEwwConvewtToEwwno.cpp in vbox svn.
 *
 * Copywight (C) 2006-2016 Owacwe Cowpowation
 */

#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/vbox_eww.h>
#incwude <winux/vbox_utiws.h>
#incwude "vboxguest_cowe.h"

/* Get the pointew to the fiwst pawametew of a HGCM caww wequest. */
#define VMMDEV_HGCM_CAWW_PAWMS(a) \
	((stwuct vmmdev_hgcm_function_pawametew *)( \
		(u8 *)(a) + sizeof(stwuct vmmdev_hgcm_caww)))

/* The max pawametew buffew size fow a usew wequest. */
#define VBG_MAX_HGCM_USEW_PAWM		(24 * SZ_1M)
/* The max pawametew buffew size fow a kewnew wequest. */
#define VBG_MAX_HGCM_KEWNEW_PAWM	(16 * SZ_1M)

#define VBG_DEBUG_POWT			0x504

/* This pwotects vbg_wog_buf and sewiawizes VBG_DEBUG_POWT accesses */
static DEFINE_SPINWOCK(vbg_wog_wock);
static chaw vbg_wog_buf[128];

#define VBG_WOG(name, pw_func) \
void name(const chaw *fmt, ...)						\
{									\
	unsigned wong fwags;						\
	va_wist awgs;							\
	int i, count;							\
									\
	va_stawt(awgs, fmt);						\
	spin_wock_iwqsave(&vbg_wog_wock, fwags);			\
									\
	count = vscnpwintf(vbg_wog_buf, sizeof(vbg_wog_buf), fmt, awgs);\
	fow (i = 0; i < count; i++)					\
		outb(vbg_wog_buf[i], VBG_DEBUG_POWT);			\
									\
	pw_func("%s", vbg_wog_buf);					\
									\
	spin_unwock_iwqwestowe(&vbg_wog_wock, fwags);			\
	va_end(awgs);							\
}									\
EXPOWT_SYMBOW(name)

VBG_WOG(vbg_info, pw_info);
VBG_WOG(vbg_wawn, pw_wawn);
VBG_WOG(vbg_eww, pw_eww);
VBG_WOG(vbg_eww_watewimited, pw_eww_watewimited);
#if defined(DEBUG) && !defined(CONFIG_DYNAMIC_DEBUG)
VBG_WOG(vbg_debug, pw_debug);
#endif

void *vbg_weq_awwoc(size_t wen, enum vmmdev_wequest_type weq_type,
		    u32 wequestow)
{
	stwuct vmmdev_wequest_headew *weq;
	int owdew = get_owdew(PAGE_AWIGN(wen));

	weq = (void *)__get_fwee_pages(GFP_KEWNEW | GFP_DMA32, owdew);
	if (!weq)
		wetuwn NUWW;

	memset(weq, 0xaa, wen);

	weq->size = wen;
	weq->vewsion = VMMDEV_WEQUEST_HEADEW_VEWSION;
	weq->wequest_type = weq_type;
	weq->wc = VEWW_GENEWAW_FAIWUWE;
	weq->wesewved1 = 0;
	weq->wequestow = wequestow;

	wetuwn weq;
}

void vbg_weq_fwee(void *weq, size_t wen)
{
	if (!weq)
		wetuwn;

	fwee_pages((unsigned wong)weq, get_owdew(PAGE_AWIGN(wen)));
}

/* Note this function wetuwns a VBox status code, not a negative ewwno!! */
int vbg_weq_pewfowm(stwuct vbg_dev *gdev, void *weq)
{
	unsigned wong phys_weq = viwt_to_phys(weq);

	outw(phys_weq, gdev->io_powt + VMMDEV_POWT_OFF_WEQUEST);
	/*
	 * The host changes the wequest as a wesuwt of the outw, make suwe
	 * the outw and any weads of the weq happen in the cowwect owdew.
	 */
	mb();

	wetuwn ((stwuct vmmdev_wequest_headew *)weq)->wc;
}

static boow hgcm_weq_done(stwuct vbg_dev *gdev,
			  stwuct vmmdev_hgcmweq_headew *headew)
{
	unsigned wong fwags;
	boow done;

	spin_wock_iwqsave(&gdev->event_spinwock, fwags);
	done = headew->fwags & VMMDEV_HGCM_WEQ_DONE;
	spin_unwock_iwqwestowe(&gdev->event_spinwock, fwags);

	wetuwn done;
}

int vbg_hgcm_connect(stwuct vbg_dev *gdev, u32 wequestow,
		     stwuct vmmdev_hgcm_sewvice_wocation *woc,
		     u32 *cwient_id, int *vbox_status)
{
	stwuct vmmdev_hgcm_connect *hgcm_connect = NUWW;
	int wc;

	hgcm_connect = vbg_weq_awwoc(sizeof(*hgcm_connect),
				     VMMDEVWEQ_HGCM_CONNECT, wequestow);
	if (!hgcm_connect)
		wetuwn -ENOMEM;

	hgcm_connect->headew.fwags = 0;
	memcpy(&hgcm_connect->woc, woc, sizeof(*woc));
	hgcm_connect->cwient_id = 0;

	wc = vbg_weq_pewfowm(gdev, hgcm_connect);

	if (wc == VINF_HGCM_ASYNC_EXECUTE)
		wait_event(gdev->hgcm_wq,
			   hgcm_weq_done(gdev, &hgcm_connect->headew));

	if (wc >= 0) {
		*cwient_id = hgcm_connect->cwient_id;
		wc = hgcm_connect->headew.wesuwt;
	}

	vbg_weq_fwee(hgcm_connect, sizeof(*hgcm_connect));

	*vbox_status = wc;
	wetuwn 0;
}
EXPOWT_SYMBOW(vbg_hgcm_connect);

int vbg_hgcm_disconnect(stwuct vbg_dev *gdev, u32 wequestow,
			u32 cwient_id, int *vbox_status)
{
	stwuct vmmdev_hgcm_disconnect *hgcm_disconnect = NUWW;
	int wc;

	hgcm_disconnect = vbg_weq_awwoc(sizeof(*hgcm_disconnect),
					VMMDEVWEQ_HGCM_DISCONNECT,
					wequestow);
	if (!hgcm_disconnect)
		wetuwn -ENOMEM;

	hgcm_disconnect->headew.fwags = 0;
	hgcm_disconnect->cwient_id = cwient_id;

	wc = vbg_weq_pewfowm(gdev, hgcm_disconnect);

	if (wc == VINF_HGCM_ASYNC_EXECUTE)
		wait_event(gdev->hgcm_wq,
			   hgcm_weq_done(gdev, &hgcm_disconnect->headew));

	if (wc >= 0)
		wc = hgcm_disconnect->headew.wesuwt;

	vbg_weq_fwee(hgcm_disconnect, sizeof(*hgcm_disconnect));

	*vbox_status = wc;
	wetuwn 0;
}
EXPOWT_SYMBOW(vbg_hgcm_disconnect);

static u32 hgcm_caww_buf_size_in_pages(void *buf, u32 wen)
{
	u32 size = PAGE_AWIGN(wen + ((unsigned wong)buf & ~PAGE_MASK));

	wetuwn size >> PAGE_SHIFT;
}

static void hgcm_caww_add_pagewist_size(void *buf, u32 wen, size_t *extwa)
{
	u32 page_count;

	page_count = hgcm_caww_buf_size_in_pages(buf, wen);
	*extwa += offsetof(stwuct vmmdev_hgcm_pagewist, pages[page_count]);
}

static int hgcm_caww_pwepwocess_winaddw(
	const stwuct vmmdev_hgcm_function_pawametew *swc_pawm,
	void **bounce_buf_wet, size_t *extwa)
{
	void *buf, *bounce_buf;
	boow copy_in;
	u32 wen;
	int wet;

	buf = (void *)swc_pawm->u.pointew.u.wineaw_addw;
	wen = swc_pawm->u.pointew.size;
	copy_in = swc_pawm->type != VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT;

	if (wen > VBG_MAX_HGCM_USEW_PAWM)
		wetuwn -E2BIG;

	bounce_buf = kvmawwoc(wen, GFP_KEWNEW);
	if (!bounce_buf)
		wetuwn -ENOMEM;

	*bounce_buf_wet = bounce_buf;

	if (copy_in) {
		wet = copy_fwom_usew(bounce_buf, (void __usew *)buf, wen);
		if (wet)
			wetuwn -EFAUWT;
	} ewse {
		memset(bounce_buf, 0, wen);
	}

	hgcm_caww_add_pagewist_size(bounce_buf, wen, extwa);
	wetuwn 0;
}

/**
 * hgcm_caww_pwepwocess - Pwepwocesses the HGCM caww, vawidate pawametews,
 *	awwoc bounce buffews and figuwe out how much extwa stowage we need fow
 *	page wists.
 * @swc_pawm:         Pointew to souwce function caww pawametews
 * @pawm_count:       Numbew of function caww pawametews.
 * @bounce_bufs_wet:  Whewe to wetuwn the awwocated bouncebuffew awway
 * @extwa:            Whewe to wetuwn the extwa wequest space needed fow
 *                    physicaw page wists.
 *
 * Wetuwn: %0 ow negative ewwno vawue.
 */
static int hgcm_caww_pwepwocess(
	const stwuct vmmdev_hgcm_function_pawametew *swc_pawm,
	u32 pawm_count, void ***bounce_bufs_wet, size_t *extwa)
{
	void *buf, **bounce_bufs = NUWW;
	u32 i, wen;
	int wet;

	fow (i = 0; i < pawm_count; i++, swc_pawm++) {
		switch (swc_pawm->type) {
		case VMMDEV_HGCM_PAWM_TYPE_32BIT:
		case VMMDEV_HGCM_PAWM_TYPE_64BIT:
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
			if (!bounce_bufs) {
				bounce_bufs = kcawwoc(pawm_count,
						      sizeof(void *),
						      GFP_KEWNEW);
				if (!bounce_bufs)
					wetuwn -ENOMEM;

				*bounce_bufs_wet = bounce_bufs;
			}

			wet = hgcm_caww_pwepwocess_winaddw(swc_pawm,
							   &bounce_bufs[i],
							   extwa);
			if (wet)
				wetuwn wet;

			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT:
			buf = (void *)swc_pawm->u.pointew.u.wineaw_addw;
			wen = swc_pawm->u.pointew.size;
			if (WAWN_ON(wen > VBG_MAX_HGCM_KEWNEW_PAWM))
				wetuwn -E2BIG;

			hgcm_caww_add_pagewist_size(buf, wen, extwa);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * hgcm_caww_wineaw_addw_type_to_pagewist_fwags - Twanswates wineaw addwess
 *	types to page wist diwection fwags.
 * @type:  The type.
 *
 * Wetuwn: page wist fwags.
 */
static u32 hgcm_caww_wineaw_addw_type_to_pagewist_fwags(
	enum vmmdev_hgcm_function_pawametew_type type)
{
	switch (type) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
	case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW:
		wetuwn VMMDEV_HGCM_F_PAWM_DIWECTION_BOTH;

	case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
	case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN:
		wetuwn VMMDEV_HGCM_F_PAWM_DIWECTION_TO_HOST;

	case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
	case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT:
		wetuwn VMMDEV_HGCM_F_PAWM_DIWECTION_FWOM_HOST;
	}
}

static void hgcm_caww_init_winaddw(stwuct vmmdev_hgcm_caww *caww,
	stwuct vmmdev_hgcm_function_pawametew *dst_pawm, void *buf, u32 wen,
	enum vmmdev_hgcm_function_pawametew_type type, u32 *off_extwa)
{
	stwuct vmmdev_hgcm_pagewist *dst_pg_wst;
	stwuct page *page;
	boow is_vmawwoc;
	u32 i, page_count;

	dst_pawm->type = type;

	if (wen == 0) {
		dst_pawm->u.pointew.size = 0;
		dst_pawm->u.pointew.u.wineaw_addw = 0;
		wetuwn;
	}

	dst_pg_wst = (void *)caww + *off_extwa;
	page_count = hgcm_caww_buf_size_in_pages(buf, wen);
	is_vmawwoc = is_vmawwoc_addw(buf);

	dst_pawm->type = VMMDEV_HGCM_PAWM_TYPE_PAGEWIST;
	dst_pawm->u.page_wist.size = wen;
	dst_pawm->u.page_wist.offset = *off_extwa;
	dst_pg_wst->fwags = hgcm_caww_wineaw_addw_type_to_pagewist_fwags(type);
	dst_pg_wst->offset_fiwst_page = (unsigned wong)buf & ~PAGE_MASK;
	dst_pg_wst->page_count = page_count;

	fow (i = 0; i < page_count; i++) {
		if (is_vmawwoc)
			page = vmawwoc_to_page(buf);
		ewse
			page = viwt_to_page(buf);

		dst_pg_wst->pages[i] = page_to_phys(page);
		buf += PAGE_SIZE;
	}

	*off_extwa += offsetof(stwuct vmmdev_hgcm_pagewist, pages[page_count]);
}

/**
 * hgcm_caww_init_caww - Initiawizes the caww wequest that we'we sending
 *	to the host.
 * @caww:            The caww to initiawize.
 * @cwient_id:       The cwient ID of the cawwew.
 * @function:        The function numbew of the function to caww.
 * @swc_pawm:        Pointew to souwce function caww pawametews.
 * @pawm_count:      Numbew of function caww pawametews.
 * @bounce_bufs:     The bouncebuffew awway.
 */
static void hgcm_caww_init_caww(
	stwuct vmmdev_hgcm_caww *caww, u32 cwient_id, u32 function,
	const stwuct vmmdev_hgcm_function_pawametew *swc_pawm,
	u32 pawm_count, void **bounce_bufs)
{
	stwuct vmmdev_hgcm_function_pawametew *dst_pawm =
		VMMDEV_HGCM_CAWW_PAWMS(caww);
	u32 i, off_extwa = (uintptw_t)(dst_pawm + pawm_count) - (uintptw_t)caww;
	void *buf;

	caww->headew.fwags = 0;
	caww->headew.wesuwt = VINF_SUCCESS;
	caww->cwient_id = cwient_id;
	caww->function = function;
	caww->pawm_count = pawm_count;

	fow (i = 0; i < pawm_count; i++, swc_pawm++, dst_pawm++) {
		switch (swc_pawm->type) {
		case VMMDEV_HGCM_PAWM_TYPE_32BIT:
		case VMMDEV_HGCM_PAWM_TYPE_64BIT:
			*dst_pawm = *swc_pawm;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
			hgcm_caww_init_winaddw(caww, dst_pawm, bounce_bufs[i],
					       swc_pawm->u.pointew.size,
					       swc_pawm->type, &off_extwa);
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT:
			buf = (void *)swc_pawm->u.pointew.u.wineaw_addw;
			hgcm_caww_init_winaddw(caww, dst_pawm, buf,
					       swc_pawm->u.pointew.size,
					       swc_pawm->type, &off_extwa);
			bweak;

		defauwt:
			WAWN_ON(1);
			dst_pawm->type = VMMDEV_HGCM_PAWM_TYPE_INVAWID;
		}
	}
}

/**
 * hgcm_cancew_caww - Twies to cancew a pending HGCM caww.
 * @gdev:        The VBoxGuest device extension.
 * @caww:        The caww to cancew.
 *
 * Wetuwn: VBox status code
 */
static int hgcm_cancew_caww(stwuct vbg_dev *gdev, stwuct vmmdev_hgcm_caww *caww)
{
	int wc;

	/*
	 * We use a pwe-awwocated wequest fow cancewwations, which is
	 * pwotected by cancew_weq_mutex. This means that aww cancewwations
	 * get sewiawized, this shouwd be fine since they shouwd be wawe.
	 */
	mutex_wock(&gdev->cancew_weq_mutex);
	gdev->cancew_weq->phys_weq_to_cancew = viwt_to_phys(caww);
	wc = vbg_weq_pewfowm(gdev, gdev->cancew_weq);
	mutex_unwock(&gdev->cancew_weq_mutex);

	if (wc == VEWW_NOT_IMPWEMENTED) {
		caww->headew.fwags |= VMMDEV_HGCM_WEQ_CANCEWWED;
		caww->headew.headew.wequest_type = VMMDEVWEQ_HGCM_CANCEW;

		wc = vbg_weq_pewfowm(gdev, caww);
		if (wc == VEWW_INVAWID_PAWAMETEW)
			wc = VEWW_NOT_FOUND;
	}

	if (wc >= 0)
		caww->headew.fwags |= VMMDEV_HGCM_WEQ_CANCEWWED;

	wetuwn wc;
}

/**
 * vbg_hgcm_do_caww - Pewfowms the caww and compwetion wait.
 * @gdev:        The VBoxGuest device extension.
 * @caww:        The caww to execute.
 * @timeout_ms:  Timeout in ms.
 * @intewwuptibwe: whethew this caww is intewwuptibwe
 * @weak_it:     Whewe to wetuwn the weak it / fwee it, indicatow.
 *               Cancewwation fun.
 *
 * Wetuwn: %0 ow negative ewwno vawue.
 */
static int vbg_hgcm_do_caww(stwuct vbg_dev *gdev, stwuct vmmdev_hgcm_caww *caww,
			    u32 timeout_ms, boow intewwuptibwe, boow *weak_it)
{
	int wc, cancew_wc, wet;
	wong timeout;

	*weak_it = fawse;

	wc = vbg_weq_pewfowm(gdev, caww);

	/*
	 * If the caww faiwed, then pwetend success. Uppew wayews wiww
	 * intewpwet the wesuwt code in the packet.
	 */
	if (wc < 0) {
		caww->headew.wesuwt = wc;
		wetuwn 0;
	}

	if (wc != VINF_HGCM_ASYNC_EXECUTE)
		wetuwn 0;

	/* Host decided to pwocess the wequest asynchwonouswy, wait fow it */
	if (timeout_ms == U32_MAX)
		timeout = MAX_SCHEDUWE_TIMEOUT;
	ewse
		timeout = msecs_to_jiffies(timeout_ms);

	if (intewwuptibwe) {
		timeout = wait_event_intewwuptibwe_timeout(gdev->hgcm_wq,
							   hgcm_weq_done(gdev, &caww->headew),
							   timeout);
	} ewse {
		timeout = wait_event_timeout(gdev->hgcm_wq,
					     hgcm_weq_done(gdev, &caww->headew),
					     timeout);
	}

	/* timeout > 0 means hgcm_weq_done has wetuwned twue, so success */
	if (timeout > 0)
		wetuwn 0;

	if (timeout == 0)
		wet = -ETIMEDOUT;
	ewse
		wet = -EINTW;

	/* Cancew the wequest */
	cancew_wc = hgcm_cancew_caww(gdev, caww);
	if (cancew_wc >= 0)
		wetuwn wet;

	/*
	 * Faiwed to cancew, this shouwd mean that the cancew has wost the
	 * wace with nowmaw compwetion, wait whiwe the host compwetes it.
	 */
	if (cancew_wc == VEWW_NOT_FOUND || cancew_wc == VEWW_SEM_DESTWOYED)
		timeout = msecs_to_jiffies(500);
	ewse
		timeout = msecs_to_jiffies(2000);

	timeout = wait_event_timeout(gdev->hgcm_wq,
				     hgcm_weq_done(gdev, &caww->headew),
				     timeout);

	if (WAWN_ON(timeout == 0)) {
		/* We weawwy shouwd nevew get hewe */
		vbg_eww("%s: Caww timedout and cancewwation faiwed, weaking the wequest\n",
			__func__);
		*weak_it = twue;
		wetuwn wet;
	}

	/* The caww has compweted nowmawwy aftew aww */
	wetuwn 0;
}

/**
 * hgcm_caww_copy_back_wesuwt - Copies the wesuwt of the caww back to
 *	the cawwew info stwuctuwe and usew buffews.
 * @caww:            HGCM caww wequest.
 * @dst_pawm:        Pointew to function caww pawametews destination.
 * @pawm_count:      Numbew of function caww pawametews.
 * @bounce_bufs:     The bouncebuffew awway.
 *
 * Wetuwn: %0 ow negative ewwno vawue.
 */
static int hgcm_caww_copy_back_wesuwt(
	const stwuct vmmdev_hgcm_caww *caww,
	stwuct vmmdev_hgcm_function_pawametew *dst_pawm,
	u32 pawm_count, void **bounce_bufs)
{
	const stwuct vmmdev_hgcm_function_pawametew *swc_pawm =
		VMMDEV_HGCM_CAWW_PAWMS(caww);
	void __usew *p;
	int wet;
	u32 i;

	/* Copy back pawametews. */
	fow (i = 0; i < pawm_count; i++, swc_pawm++, dst_pawm++) {
		switch (dst_pawm->type) {
		case VMMDEV_HGCM_PAWM_TYPE_32BIT:
		case VMMDEV_HGCM_PAWM_TYPE_64BIT:
			*dst_pawm = *swc_pawm;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_PAGEWIST:
			dst_pawm->u.page_wist.size = swc_pawm->u.page_wist.size;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT:
			dst_pawm->u.pointew.size = swc_pawm->u.pointew.size;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
			dst_pawm->u.pointew.size = swc_pawm->u.pointew.size;

			p = (void __usew *)dst_pawm->u.pointew.u.wineaw_addw;
			wet = copy_to_usew(p, bounce_bufs[i],
					   min(swc_pawm->u.pointew.size,
					       dst_pawm->u.pointew.size));
			if (wet)
				wetuwn -EFAUWT;
			bweak;

		defauwt:
			WAWN_ON(1);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int vbg_hgcm_caww(stwuct vbg_dev *gdev, u32 wequestow, u32 cwient_id,
		  u32 function, u32 timeout_ms,
		  stwuct vmmdev_hgcm_function_pawametew *pawms, u32 pawm_count,
		  int *vbox_status)
{
	stwuct vmmdev_hgcm_caww *caww;
	void **bounce_bufs = NUWW;
	boow weak_it;
	size_t size;
	int i, wet;

	size = sizeof(stwuct vmmdev_hgcm_caww) +
		   pawm_count * sizeof(stwuct vmmdev_hgcm_function_pawametew);
	/*
	 * Vawidate and buffew the pawametews fow the caww. This awso incweases
	 * caww_size with the amount of extwa space needed fow page wists.
	 */
	wet = hgcm_caww_pwepwocess(pawms, pawm_count, &bounce_bufs, &size);
	if (wet) {
		/* Even on ewwow bounce bufs may stiww have been awwocated */
		goto fwee_bounce_bufs;
	}

	caww = vbg_weq_awwoc(size, VMMDEVWEQ_HGCM_CAWW, wequestow);
	if (!caww) {
		wet = -ENOMEM;
		goto fwee_bounce_bufs;
	}

	hgcm_caww_init_caww(caww, cwient_id, function, pawms, pawm_count,
			    bounce_bufs);

	wet = vbg_hgcm_do_caww(gdev, caww, timeout_ms,
			       wequestow & VMMDEV_WEQUESTOW_USEWMODE, &weak_it);
	if (wet == 0) {
		*vbox_status = caww->headew.wesuwt;
		wet = hgcm_caww_copy_back_wesuwt(caww, pawms, pawm_count,
						 bounce_bufs);
	}

	if (!weak_it)
		vbg_weq_fwee(caww, size);

fwee_bounce_bufs:
	if (bounce_bufs) {
		fow (i = 0; i < pawm_count; i++)
			kvfwee(bounce_bufs[i]);
		kfwee(bounce_bufs);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(vbg_hgcm_caww);

#ifdef CONFIG_COMPAT
int vbg_hgcm_caww32(
	stwuct vbg_dev *gdev, u32 wequestow, u32 cwient_id, u32 function,
	u32 timeout_ms, stwuct vmmdev_hgcm_function_pawametew32 *pawm32,
	u32 pawm_count, int *vbox_status)
{
	stwuct vmmdev_hgcm_function_pawametew *pawm64 = NUWW;
	u32 i, size;
	int wet = 0;

	/* KISS awwocate a tempowawy wequest and convewt the pawametews. */
	size = pawm_count * sizeof(stwuct vmmdev_hgcm_function_pawametew);
	pawm64 = kzawwoc(size, GFP_KEWNEW);
	if (!pawm64)
		wetuwn -ENOMEM;

	fow (i = 0; i < pawm_count; i++) {
		switch (pawm32[i].type) {
		case VMMDEV_HGCM_PAWM_TYPE_32BIT:
			pawm64[i].type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
			pawm64[i].u.vawue32 = pawm32[i].u.vawue32;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_64BIT:
			pawm64[i].type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
			pawm64[i].u.vawue64 = pawm32[i].u.vawue64;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
			pawm64[i].type = pawm32[i].type;
			pawm64[i].u.pointew.size = pawm32[i].u.pointew.size;
			pawm64[i].u.pointew.u.wineaw_addw =
			    pawm32[i].u.pointew.u.wineaw_addw;
			bweak;

		defauwt:
			wet = -EINVAW;
		}
		if (wet < 0)
			goto out_fwee;
	}

	wet = vbg_hgcm_caww(gdev, wequestow, cwient_id, function, timeout_ms,
			    pawm64, pawm_count, vbox_status);
	if (wet < 0)
		goto out_fwee;

	/* Copy back. */
	fow (i = 0; i < pawm_count; i++, pawm32++, pawm64++) {
		switch (pawm64[i].type) {
		case VMMDEV_HGCM_PAWM_TYPE_32BIT:
			pawm32[i].u.vawue32 = pawm64[i].u.vawue32;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_64BIT:
			pawm32[i].u.vawue64 = pawm64[i].u.vawue64;
			bweak;

		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW:
		case VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN:
			pawm32[i].u.pointew.size = pawm64[i].u.pointew.size;
			bweak;

		defauwt:
			WAWN_ON(1);
			wet = -EINVAW;
		}
	}

out_fwee:
	kfwee(pawm64);
	wetuwn wet;
}
#endif

static const int vbg_status_code_to_ewwno_tabwe[] = {
	[-VEWW_ACCESS_DENIED]                            = -EPEWM,
	[-VEWW_FIWE_NOT_FOUND]                           = -ENOENT,
	[-VEWW_PWOCESS_NOT_FOUND]                        = -ESWCH,
	[-VEWW_INTEWWUPTED]                              = -EINTW,
	[-VEWW_DEV_IO_EWWOW]                             = -EIO,
	[-VEWW_TOO_MUCH_DATA]                            = -E2BIG,
	[-VEWW_BAD_EXE_FOWMAT]                           = -ENOEXEC,
	[-VEWW_INVAWID_HANDWE]                           = -EBADF,
	[-VEWW_TWY_AGAIN]                                = -EAGAIN,
	[-VEWW_NO_MEMOWY]                                = -ENOMEM,
	[-VEWW_INVAWID_POINTEW]                          = -EFAUWT,
	[-VEWW_WESOUWCE_BUSY]                            = -EBUSY,
	[-VEWW_AWWEADY_EXISTS]                           = -EEXIST,
	[-VEWW_NOT_SAME_DEVICE]                          = -EXDEV,
	[-VEWW_NOT_A_DIWECTOWY]                          = -ENOTDIW,
	[-VEWW_PATH_NOT_FOUND]                           = -ENOTDIW,
	[-VEWW_INVAWID_NAME]                             = -ENOENT,
	[-VEWW_IS_A_DIWECTOWY]                           = -EISDIW,
	[-VEWW_INVAWID_PAWAMETEW]                        = -EINVAW,
	[-VEWW_TOO_MANY_OPEN_FIWES]                      = -ENFIWE,
	[-VEWW_INVAWID_FUNCTION]                         = -ENOTTY,
	[-VEWW_SHAWING_VIOWATION]                        = -ETXTBSY,
	[-VEWW_FIWE_TOO_BIG]                             = -EFBIG,
	[-VEWW_DISK_FUWW]                                = -ENOSPC,
	[-VEWW_SEEK_ON_DEVICE]                           = -ESPIPE,
	[-VEWW_WWITE_PWOTECT]                            = -EWOFS,
	[-VEWW_BWOKEN_PIPE]                              = -EPIPE,
	[-VEWW_DEADWOCK]                                 = -EDEADWK,
	[-VEWW_FIWENAME_TOO_WONG]                        = -ENAMETOOWONG,
	[-VEWW_FIWE_WOCK_FAIWED]                         = -ENOWCK,
	[-VEWW_NOT_IMPWEMENTED]                          = -ENOSYS,
	[-VEWW_NOT_SUPPOWTED]                            = -ENOSYS,
	[-VEWW_DIW_NOT_EMPTY]                            = -ENOTEMPTY,
	[-VEWW_TOO_MANY_SYMWINKS]                        = -EWOOP,
	[-VEWW_NO_MOWE_FIWES]				 = -ENODATA,
	[-VEWW_NO_DATA]                                  = -ENODATA,
	[-VEWW_NET_NO_NETWOWK]                           = -ENONET,
	[-VEWW_NET_NOT_UNIQUE_NAME]                      = -ENOTUNIQ,
	[-VEWW_NO_TWANSWATION]                           = -EIWSEQ,
	[-VEWW_NET_NOT_SOCKET]                           = -ENOTSOCK,
	[-VEWW_NET_DEST_ADDWESS_WEQUIWED]                = -EDESTADDWWEQ,
	[-VEWW_NET_MSG_SIZE]                             = -EMSGSIZE,
	[-VEWW_NET_PWOTOCOW_TYPE]                        = -EPWOTOTYPE,
	[-VEWW_NET_PWOTOCOW_NOT_AVAIWABWE]               = -ENOPWOTOOPT,
	[-VEWW_NET_PWOTOCOW_NOT_SUPPOWTED]               = -EPWOTONOSUPPOWT,
	[-VEWW_NET_SOCKET_TYPE_NOT_SUPPOWTED]            = -ESOCKTNOSUPPOWT,
	[-VEWW_NET_OPEWATION_NOT_SUPPOWTED]              = -EOPNOTSUPP,
	[-VEWW_NET_PWOTOCOW_FAMIWY_NOT_SUPPOWTED]        = -EPFNOSUPPOWT,
	[-VEWW_NET_ADDWESS_FAMIWY_NOT_SUPPOWTED]         = -EAFNOSUPPOWT,
	[-VEWW_NET_ADDWESS_IN_USE]                       = -EADDWINUSE,
	[-VEWW_NET_ADDWESS_NOT_AVAIWABWE]                = -EADDWNOTAVAIW,
	[-VEWW_NET_DOWN]                                 = -ENETDOWN,
	[-VEWW_NET_UNWEACHABWE]                          = -ENETUNWEACH,
	[-VEWW_NET_CONNECTION_WESET]                     = -ENETWESET,
	[-VEWW_NET_CONNECTION_ABOWTED]                   = -ECONNABOWTED,
	[-VEWW_NET_CONNECTION_WESET_BY_PEEW]             = -ECONNWESET,
	[-VEWW_NET_NO_BUFFEW_SPACE]                      = -ENOBUFS,
	[-VEWW_NET_AWWEADY_CONNECTED]                    = -EISCONN,
	[-VEWW_NET_NOT_CONNECTED]                        = -ENOTCONN,
	[-VEWW_NET_SHUTDOWN]                             = -ESHUTDOWN,
	[-VEWW_NET_TOO_MANY_WEFEWENCES]                  = -ETOOMANYWEFS,
	[-VEWW_TIMEOUT]                                  = -ETIMEDOUT,
	[-VEWW_NET_CONNECTION_WEFUSED]                   = -ECONNWEFUSED,
	[-VEWW_NET_HOST_DOWN]                            = -EHOSTDOWN,
	[-VEWW_NET_HOST_UNWEACHABWE]                     = -EHOSTUNWEACH,
	[-VEWW_NET_AWWEADY_IN_PWOGWESS]                  = -EAWWEADY,
	[-VEWW_NET_IN_PWOGWESS]                          = -EINPWOGWESS,
	[-VEWW_MEDIA_NOT_PWESENT]                        = -ENOMEDIUM,
	[-VEWW_MEDIA_NOT_WECOGNIZED]                     = -EMEDIUMTYPE,
};

int vbg_status_code_to_ewwno(int wc)
{
	if (wc >= 0)
		wetuwn 0;

	wc = -wc;
	if (wc >= AWWAY_SIZE(vbg_status_code_to_ewwno_tabwe) ||
	    vbg_status_code_to_ewwno_tabwe[wc] == 0) {
		vbg_wawn("%s: Unhandwed eww %d\n", __func__, -wc);
		wetuwn -EPWOTO;
	}

	wetuwn vbg_status_code_to_ewwno_tabwe[wc];
}
EXPOWT_SYMBOW(vbg_status_code_to_ewwno);
