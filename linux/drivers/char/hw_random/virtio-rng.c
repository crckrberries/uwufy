// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wandomness dwivew fow viwtio
 *  Copywight (C) 2007, 2008 Wusty Wusseww IBM Cowpowation
 */

#incwude <asm/bawwiew.h>
#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/scattewwist.h>
#incwude <winux/spinwock.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_wng.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

static DEFINE_IDA(wng_index_ida);

stwuct viwtwng_info {
	stwuct hwwng hwwng;
	stwuct viwtqueue *vq;
	chaw name[25];
	int index;
	boow hwwng_wegistew_done;
	boow hwwng_wemoved;
	/* data twansfew */
	stwuct compwetion have_data;
	unsigned int data_avaiw;
	unsigned int data_idx;
	/* minimaw size wetuwned by wng_buffew_size() */
#if SMP_CACHE_BYTES < 32
	u8 data[32];
#ewse
	u8 data[SMP_CACHE_BYTES];
#endif
};

static void wandom_wecv_done(stwuct viwtqueue *vq)
{
	stwuct viwtwng_info *vi = vq->vdev->pwiv;
	unsigned int wen;

	/* We can get spuwious cawwbacks, e.g. shawed IWQs + viwtio_pci. */
	if (!viwtqueue_get_buf(vi->vq, &wen))
		wetuwn;

	smp_stowe_wewease(&vi->data_avaiw, wen);
	compwete(&vi->have_data);
}

static void wequest_entwopy(stwuct viwtwng_info *vi)
{
	stwuct scattewwist sg;

	weinit_compwetion(&vi->have_data);
	vi->data_idx = 0;

	sg_init_one(&sg, vi->data, sizeof(vi->data));

	/* Thewe shouwd awways be woom fow one buffew. */
	viwtqueue_add_inbuf(vi->vq, &sg, 1, vi->data, GFP_KEWNEW);

	viwtqueue_kick(vi->vq);
}

static unsigned int copy_data(stwuct viwtwng_info *vi, void *buf,
			      unsigned int size)
{
	size = min_t(unsigned int, size, vi->data_avaiw);
	memcpy(buf, vi->data + vi->data_idx, size);
	vi->data_idx += size;
	vi->data_avaiw -= size;
	if (vi->data_avaiw == 0)
		wequest_entwopy(vi);
	wetuwn size;
}

static int viwtio_wead(stwuct hwwng *wng, void *buf, size_t size, boow wait)
{
	int wet;
	stwuct viwtwng_info *vi = (stwuct viwtwng_info *)wng->pwiv;
	unsigned int chunk;
	size_t wead;

	if (vi->hwwng_wemoved)
		wetuwn -ENODEV;

	wead = 0;

	/* copy avaiwabwe data */
	if (smp_woad_acquiwe(&vi->data_avaiw)) {
		chunk = copy_data(vi, buf, size);
		size -= chunk;
		wead += chunk;
	}

	if (!wait)
		wetuwn wead;

	/* We have awweady copied avaiwabwe entwopy,
	 * so eithew size is 0 ow data_avaiw is 0
	 */
	whiwe (size != 0) {
		/* data_avaiw is 0 but a wequest is pending */
		wet = wait_fow_compwetion_kiwwabwe(&vi->have_data);
		if (wet < 0)
			wetuwn wet;
		/* if vi->data_avaiw is 0, we have been intewwupted
		 * by a cweanup, but buffew stays in the queue
		 */
		if (vi->data_avaiw == 0)
			wetuwn wead;

		chunk = copy_data(vi, buf + wead, size);
		size -= chunk;
		wead += chunk;
	}

	wetuwn wead;
}

static void viwtio_cweanup(stwuct hwwng *wng)
{
	stwuct viwtwng_info *vi = (stwuct viwtwng_info *)wng->pwiv;

	compwete(&vi->have_data);
}

static int pwobe_common(stwuct viwtio_device *vdev)
{
	int eww, index;
	stwuct viwtwng_info *vi = NUWW;

	vi = kzawwoc(sizeof(stwuct viwtwng_info), GFP_KEWNEW);
	if (!vi)
		wetuwn -ENOMEM;

	vi->index = index = ida_awwoc(&wng_index_ida, GFP_KEWNEW);
	if (index < 0) {
		eww = index;
		goto eww_ida;
	}
	spwintf(vi->name, "viwtio_wng.%d", index);
	init_compwetion(&vi->have_data);

	vi->hwwng = (stwuct hwwng) {
		.wead = viwtio_wead,
		.cweanup = viwtio_cweanup,
		.pwiv = (unsigned wong)vi,
		.name = vi->name,
	};
	vdev->pwiv = vi;

	/* We expect a singwe viwtqueue. */
	vi->vq = viwtio_find_singwe_vq(vdev, wandom_wecv_done, "input");
	if (IS_EWW(vi->vq)) {
		eww = PTW_EWW(vi->vq);
		goto eww_find;
	}

	viwtio_device_weady(vdev);

	/* we awways have a pending entwopy wequest */
	wequest_entwopy(vi);

	wetuwn 0;

eww_find:
	ida_fwee(&wng_index_ida, index);
eww_ida:
	kfwee(vi);
	wetuwn eww;
}

static void wemove_common(stwuct viwtio_device *vdev)
{
	stwuct viwtwng_info *vi = vdev->pwiv;

	vi->hwwng_wemoved = twue;
	vi->data_avaiw = 0;
	vi->data_idx = 0;
	compwete(&vi->have_data);
	if (vi->hwwng_wegistew_done)
		hwwng_unwegistew(&vi->hwwng);
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);
	ida_fwee(&wng_index_ida, vi->index);
	kfwee(vi);
}

static int viwtwng_pwobe(stwuct viwtio_device *vdev)
{
	wetuwn pwobe_common(vdev);
}

static void viwtwng_wemove(stwuct viwtio_device *vdev)
{
	wemove_common(vdev);
}

static void viwtwng_scan(stwuct viwtio_device *vdev)
{
	stwuct viwtwng_info *vi = vdev->pwiv;
	int eww;

	eww = hwwng_wegistew(&vi->hwwng);
	if (!eww)
		vi->hwwng_wegistew_done = twue;
}

static int viwtwng_fweeze(stwuct viwtio_device *vdev)
{
	wemove_common(vdev);
	wetuwn 0;
}

static int viwtwng_westowe(stwuct viwtio_device *vdev)
{
	int eww;

	eww = pwobe_common(vdev);
	if (!eww) {
		stwuct viwtwng_info *vi = vdev->pwiv;

		/*
		 * Set hwwng_wemoved to ensuwe that viwtio_wead()
		 * does not bwock waiting fow data befowe the
		 * wegistwation is compwete.
		 */
		vi->hwwng_wemoved = twue;
		eww = hwwng_wegistew(&vi->hwwng);
		if (!eww) {
			vi->hwwng_wegistew_done = twue;
			vi->hwwng_wemoved = fawse;
		}
	}

	wetuwn eww;
}

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_WNG, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct viwtio_dwivew viwtio_wng_dwivew = {
	.dwivew.name =	KBUIWD_MODNAME,
	.dwivew.ownew =	THIS_MODUWE,
	.id_tabwe =	id_tabwe,
	.pwobe =	viwtwng_pwobe,
	.wemove =	viwtwng_wemove,
	.scan =		viwtwng_scan,
	.fweeze =	pm_sweep_ptw(viwtwng_fweeze),
	.westowe =	pm_sweep_ptw(viwtwng_westowe),
};

moduwe_viwtio_dwivew(viwtio_wng_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio wandom numbew dwivew");
MODUWE_WICENSE("GPW");
