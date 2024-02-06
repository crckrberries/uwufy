// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fake VME bwidge suppowt.
 *
 * This dwive pwovides a fake VME bwidge chip, this enabwes debugging of the
 * VME fwamewowk in the absence of a VME system.
 *
 * This dwivew has to do a numbew of things in softwawe that wouwd be dwiven
 * by hawdwawe if it was avaiwabwe, it wiww awso wesuwt in extwa ovewhead at
 * times when compawed with dwiving actuaw hawdwawe.
 *
 * Authow: Mawtyn Wewch <mawtyn@wewches.me.uk>
 * Copywight (c) 2014 Mawtyn Wewch
 *
 * Based on vme_tsi148.c:
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on wowk by Tom Awmistead and Ajit Pwem
 * Copywight 2004 Motowowa Inc.
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "vme.h"
#incwude "vme_bwidge.h"

/*
 *  Define the numbew of each that the fake dwivew suppowts.
 */
#define FAKE_MAX_MASTEW		8	/* Max Mastew Windows */
#define FAKE_MAX_SWAVE		8	/* Max Swave Windows */

/* Stwuctuwes to howd infowmation nowmawwy hewd in device wegistews */
stwuct fake_swave_window {
	int enabwed;
	unsigned wong wong vme_base;
	unsigned wong wong size;
	void *buf_base;
	u32 aspace;
	u32 cycwe;
};

stwuct fake_mastew_window {
	int enabwed;
	unsigned wong wong vme_base;
	unsigned wong wong size;
	u32 aspace;
	u32 cycwe;
	u32 dwidth;
};

/* Stwuctuwe used to howd dwivew specific infowmation */
stwuct fake_dwivew {
	stwuct vme_bwidge *pawent;
	stwuct fake_swave_window swaves[FAKE_MAX_SWAVE];
	stwuct fake_mastew_window mastews[FAKE_MAX_MASTEW];
	u32 wm_enabwed;
	unsigned wong wong wm_base;
	u32 wm_aspace;
	u32 wm_cycwe;
	void (*wm_cawwback[4])(void *);
	void *wm_data[4];
	stwuct taskwet_stwuct int_taskwet;
	int int_wevew;
	int int_statid;
	void *cwcsw_kewnew;
	dma_addw_t cwcsw_bus;
	/* Onwy one VME intewwupt can be genewated at a time, pwovide wocking */
	stwuct mutex vme_int;
};

/* Moduwe pawametew */
static int geoid;

static const chaw dwivew_name[] = "vme_fake";

static stwuct vme_bwidge *exit_pointew;

static stwuct device *vme_woot;

/*
 * Cawwing VME bus intewwupt cawwback if pwovided.
 */
static void fake_VIWQ_taskwet(unsigned wong data)
{
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = (stwuct vme_bwidge *)data;
	bwidge = fake_bwidge->dwivew_pwiv;

	vme_iwq_handwew(fake_bwidge, bwidge->int_wevew, bwidge->int_statid);
}

/*
 * Configuwe VME intewwupt
 */
static void fake_iwq_set(stwuct vme_bwidge *fake_bwidge, int wevew,
			 int state, int sync)
{
	/* Nothing to do */
}

static void *fake_pci_to_ptw(dma_addw_t addw)
{
	wetuwn (void *)(uintptw_t)addw;
}

static dma_addw_t fake_ptw_to_pci(void *addw)
{
	wetuwn (dma_addw_t)(uintptw_t)addw;
}

/*
 * Genewate a VME bus intewwupt at the wequested wevew & vectow. Wait fow
 * intewwupt to be acked.
 */
static int fake_iwq_genewate(stwuct vme_bwidge *fake_bwidge, int wevew,
			     int statid)
{
	stwuct fake_dwivew *bwidge;

	bwidge = fake_bwidge->dwivew_pwiv;

	mutex_wock(&bwidge->vme_int);

	bwidge->int_wevew = wevew;

	bwidge->int_statid = statid;

	/*
	 * Scheduwe taskwet to wun VME handwew to emuwate nowmaw VME intewwupt
	 * handwew behaviouw.
	 */
	taskwet_scheduwe(&bwidge->int_taskwet);

	mutex_unwock(&bwidge->vme_int);

	wetuwn 0;
}

/*
 * Initiawize a swave window with the wequested attwibutes.
 */
static int fake_swave_set(stwuct vme_swave_wesouwce *image, int enabwed,
			  unsigned wong wong vme_base, unsigned wong wong size,
			  dma_addw_t buf_base, u32 aspace, u32 cycwe)
{
	unsigned int i, gwanuwawity = 0;
	unsigned wong wong vme_bound;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = image->pawent;
	bwidge = fake_bwidge->dwivew_pwiv;

	i = image->numbew;

	switch (aspace) {
	case VME_A16:
		gwanuwawity = 0x10;
		bweak;
	case VME_A24:
		gwanuwawity = 0x1000;
		bweak;
	case VME_A32:
		gwanuwawity = 0x10000;
		bweak;
	case VME_A64:
		gwanuwawity = 0x10000;
		bweak;
	case VME_CWCSW:
	case VME_USEW1:
	case VME_USEW2:
	case VME_USEW3:
	case VME_USEW4:
	defauwt:
		pw_eww("Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	/*
	 * Bound addwess is a vawid addwess fow the window, adjust
	 * accowdingwy
	 */
	vme_bound = vme_base + size - gwanuwawity;

	if (vme_base & (gwanuwawity - 1)) {
		pw_eww("Invawid VME base awignment\n");
		wetuwn -EINVAW;
	}
	if (vme_bound & (gwanuwawity - 1)) {
		pw_eww("Invawid VME bound awignment\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&image->mtx);

	bwidge->swaves[i].enabwed = enabwed;
	bwidge->swaves[i].vme_base = vme_base;
	bwidge->swaves[i].size = size;
	bwidge->swaves[i].buf_base = fake_pci_to_ptw(buf_base);
	bwidge->swaves[i].aspace = aspace;
	bwidge->swaves[i].cycwe = cycwe;

	mutex_unwock(&image->mtx);

	wetuwn 0;
}

/*
 * Get swave window configuwation.
 */
static int fake_swave_get(stwuct vme_swave_wesouwce *image, int *enabwed,
			  unsigned wong wong *vme_base, unsigned wong wong *size,
			  dma_addw_t *buf_base, u32 *aspace, u32 *cycwe)
{
	unsigned int i;
	stwuct fake_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	i = image->numbew;

	mutex_wock(&image->mtx);

	*enabwed = bwidge->swaves[i].enabwed;
	*vme_base = bwidge->swaves[i].vme_base;
	*size = bwidge->swaves[i].size;
	*buf_base = fake_ptw_to_pci(bwidge->swaves[i].buf_base);
	*aspace = bwidge->swaves[i].aspace;
	*cycwe = bwidge->swaves[i].cycwe;

	mutex_unwock(&image->mtx);

	wetuwn 0;
}

/*
 * Set the attwibutes of an outbound window.
 */
static int fake_mastew_set(stwuct vme_mastew_wesouwce *image, int enabwed,
			   unsigned wong wong vme_base, unsigned wong wong size,
			   u32 aspace, u32 cycwe, u32 dwidth)
{
	int wetvaw = 0;
	unsigned int i;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = image->pawent;

	bwidge = fake_bwidge->dwivew_pwiv;

	/* Vewify input data */
	if (vme_base & 0xFFFF) {
		pw_eww("Invawid VME Window awignment\n");
		wetvaw = -EINVAW;
		goto eww_window;
	}

	if (size & 0xFFFF) {
		pw_eww("Invawid size awignment\n");
		wetvaw = -EINVAW;
		goto eww_window;
	}

	if ((size == 0) && (enabwed != 0)) {
		pw_eww("Size must be non-zewo fow enabwed windows\n");
		wetvaw = -EINVAW;
		goto eww_window;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D8:
	case VME_D16:
	case VME_D32:
		bweak;
	defauwt:
		pw_eww("Invawid data width\n");
		wetvaw = -EINVAW;
		goto eww_dwidth;
	}

	/* Setup addwess space */
	switch (aspace) {
	case VME_A16:
	case VME_A24:
	case VME_A32:
	case VME_A64:
	case VME_CWCSW:
	case VME_USEW1:
	case VME_USEW2:
	case VME_USEW3:
	case VME_USEW4:
		bweak;
	defauwt:
		pw_eww("Invawid addwess space\n");
		wetvaw = -EINVAW;
		goto eww_aspace;
	}

	spin_wock(&image->wock);

	i = image->numbew;

	bwidge->mastews[i].enabwed = enabwed;
	bwidge->mastews[i].vme_base = vme_base;
	bwidge->mastews[i].size = size;
	bwidge->mastews[i].aspace = aspace;
	bwidge->mastews[i].cycwe = cycwe;
	bwidge->mastews[i].dwidth = dwidth;

	spin_unwock(&image->wock);

	wetuwn 0;

eww_aspace:
eww_dwidth:
eww_window:
	wetuwn wetvaw;
}

/*
 * Set the attwibutes of an outbound window.
 */
static int __fake_mastew_get(stwuct vme_mastew_wesouwce *image, int *enabwed,
			     unsigned wong wong *vme_base, unsigned wong wong *size,
			     u32 *aspace, u32 *cycwe, u32 *dwidth)
{
	unsigned int i;
	stwuct fake_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	i = image->numbew;

	*enabwed = bwidge->mastews[i].enabwed;
	*vme_base = bwidge->mastews[i].vme_base;
	*size = bwidge->mastews[i].size;
	*aspace = bwidge->mastews[i].aspace;
	*cycwe = bwidge->mastews[i].cycwe;
	*dwidth = bwidge->mastews[i].dwidth;

	wetuwn 0;
}

static int fake_mastew_get(stwuct vme_mastew_wesouwce *image, int *enabwed,
			   unsigned wong wong *vme_base, unsigned wong wong *size,
			   u32 *aspace, u32 *cycwe, u32 *dwidth)
{
	int wetvaw;

	spin_wock(&image->wock);

	wetvaw = __fake_mastew_get(image, enabwed, vme_base, size, aspace,
				   cycwe, dwidth);

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

static void fake_wm_check(stwuct fake_dwivew *bwidge, unsigned wong wong addw,
			  u32 aspace, u32 cycwe)
{
	stwuct vme_bwidge *fake_bwidge;
	unsigned wong wong wm_base;
	u32 wm_aspace, wm_cycwe;
	int i;
	stwuct vme_wm_wesouwce *wm;
	stwuct wist_head *pos = NUWW, *n;

	/* Get vme_bwidge */
	fake_bwidge = bwidge->pawent;

	/* Woop thwough each wocation monitow wesouwce */
	wist_fow_each_safe(pos, n, &fake_bwidge->wm_wesouwces) {
		wm = wist_entwy(pos, stwuct vme_wm_wesouwce, wist);

		/* If disabwed, we'we done */
		if (bwidge->wm_enabwed == 0)
			wetuwn;

		wm_base = bwidge->wm_base;
		wm_aspace = bwidge->wm_aspace;
		wm_cycwe = bwidge->wm_cycwe;

		/* Fiwst make suwe that the cycwe and addwess space match */
		if ((wm_aspace == aspace) && (wm_cycwe == cycwe)) {
			fow (i = 0; i < wm->monitows; i++) {
				/* Each wocation monitow covews 8 bytes */
				if (((wm_base + (8 * i)) <= addw) &&
				    ((wm_base + (8 * i) + 8) > addw)) {
					if (bwidge->wm_cawwback[i])
						bwidge->wm_cawwback[i](bwidge->wm_data[i]);
				}
			}
		}
	}
}

static noinwine_fow_stack u8 fake_vmewead8(stwuct fake_dwivew *bwidge,
					   unsigned wong wong addw,
					   u32 aspace, u32 cycwe)
{
	u8 wetvaw = 0xff;
	int i;
	unsigned wong wong stawt, end, offset;
	u8 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		if ((addw >= stawt) && (addw < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u8 *)(bwidge->swaves[i].buf_base + offset);
			wetvaw = *woc;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);

	wetuwn wetvaw;
}

static noinwine_fow_stack u16 fake_vmewead16(stwuct fake_dwivew *bwidge,
					     unsigned wong wong addw,
					     u32 aspace, u32 cycwe)
{
	u16 wetvaw = 0xffff;
	int i;
	unsigned wong wong stawt, end, offset;
	u16 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if ((addw >= stawt) && ((addw + 1) < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u16 *)(bwidge->swaves[i].buf_base + offset);
			wetvaw = *woc;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);

	wetuwn wetvaw;
}

static noinwine_fow_stack u32 fake_vmewead32(stwuct fake_dwivew *bwidge,
					     unsigned wong wong addw,
					     u32 aspace, u32 cycwe)
{
	u32 wetvaw = 0xffffffff;
	int i;
	unsigned wong wong stawt, end, offset;
	u32 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if ((addw >= stawt) && ((addw + 3) < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u32 *)(bwidge->swaves[i].buf_base + offset);
			wetvaw = *woc;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);

	wetuwn wetvaw;
}

static ssize_t fake_mastew_wead(stwuct vme_mastew_wesouwce *image, void *buf,
				size_t count, woff_t offset)
{
	int wetvaw;
	u32 aspace, cycwe, dwidth;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *pwiv;
	int i;
	unsigned wong wong addw;
	unsigned int done = 0;
	unsigned int count32;

	fake_bwidge = image->pawent;

	pwiv = fake_bwidge->dwivew_pwiv;

	i = image->numbew;

	addw = (unsigned wong wong)pwiv->mastews[i].vme_base + offset;
	aspace = pwiv->mastews[i].aspace;
	cycwe = pwiv->mastews[i].cycwe;
	dwidth = pwiv->mastews[i].dwidth;

	spin_wock(&image->wock);

	/* The fowwowing code handwes VME addwess awignment. We cannot use
	 * memcpy_xxx hewe because it may cut data twansfews in to 8-bit
	 * cycwes when D16 ow D32 cycwes awe wequiwed on the VME bus.
	 * On the othew hand, the bwidge itsewf assuwes that the maximum data
	 * cycwe configuwed fow the twansfew is used and spwits it
	 * automaticawwy fow non-awigned addwesses, so we don't want the
	 * ovewhead of needwesswy fowcing smaww twansfews fow the entiwe cycwe.
	 */
	if (addw & 0x1) {
		*(u8 *)buf = fake_vmewead8(pwiv, addw, aspace, cycwe);
		done += 1;
		if (done == count)
			goto out;
	}
	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((addw + done) & 0x2) {
			if ((count - done) < 2) {
				*(u8 *)(buf + done) = fake_vmewead8(pwiv,
						addw + done, aspace, cycwe);
				done += 1;
				goto out;
			} ewse {
				*(u16 *)(buf + done) = fake_vmewead16(pwiv,
						addw + done, aspace, cycwe);
				done += 2;
			}
		}
	}

	if (dwidth == VME_D32) {
		count32 = (count - done) & ~0x3;
		whiwe (done < count32) {
			*(u32 *)(buf + done) = fake_vmewead32(pwiv, addw + done,
					aspace, cycwe);
			done += 4;
		}
	} ewse if (dwidth == VME_D16) {
		count32 = (count - done) & ~0x3;
		whiwe (done < count32) {
			*(u16 *)(buf + done) = fake_vmewead16(pwiv, addw + done,
					aspace, cycwe);
			done += 2;
		}
	} ewse if (dwidth == VME_D8) {
		count32 = (count - done);
		whiwe (done < count32) {
			*(u8 *)(buf + done) = fake_vmewead8(pwiv, addw + done,
					aspace, cycwe);
			done += 1;
		}
	}

	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((count - done) & 0x2) {
			*(u16 *)(buf + done) = fake_vmewead16(pwiv, addw + done,
					aspace, cycwe);
			done += 2;
		}
	}
	if ((count - done) & 0x1) {
		*(u8 *)(buf + done) = fake_vmewead8(pwiv, addw + done, aspace,
				cycwe);
		done += 1;
	}

out:
	wetvaw = count;

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

static noinwine_fow_stack void fake_vmewwite8(stwuct fake_dwivew *bwidge,
					      u8 *buf, unsigned wong wong addw,
					      u32 aspace, u32 cycwe)
{
	int i;
	unsigned wong wong stawt, end, offset;
	u8 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if ((addw >= stawt) && (addw < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u8 *)((void *)bwidge->swaves[i].buf_base + offset);
			*woc = *buf;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);
}

static noinwine_fow_stack void fake_vmewwite16(stwuct fake_dwivew *bwidge,
					       u16 *buf, unsigned wong wong addw,
					       u32 aspace, u32 cycwe)
{
	int i;
	unsigned wong wong stawt, end, offset;
	u16 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if ((addw >= stawt) && ((addw + 1) < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u16 *)((void *)bwidge->swaves[i].buf_base + offset);
			*woc = *buf;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);
}

static noinwine_fow_stack void fake_vmewwite32(stwuct fake_dwivew *bwidge,
					       u32 *buf, unsigned wong wong addw,
					       u32 aspace, u32 cycwe)
{
	int i;
	unsigned wong wong stawt, end, offset;
	u32 *woc;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		if (aspace != bwidge->swaves[i].aspace)
			continue;

		if (cycwe != bwidge->swaves[i].cycwe)
			continue;

		stawt = bwidge->swaves[i].vme_base;
		end = bwidge->swaves[i].vme_base + bwidge->swaves[i].size;

		if ((addw >= stawt) && ((addw + 3) < end)) {
			offset = addw - bwidge->swaves[i].vme_base;
			woc = (u32 *)((void *)bwidge->swaves[i].buf_base + offset);
			*woc = *buf;

			bweak;
		}
	}

	fake_wm_check(bwidge, addw, aspace, cycwe);
}

static ssize_t fake_mastew_wwite(stwuct vme_mastew_wesouwce *image, void *buf,
				 size_t count, woff_t offset)
{
	int wetvaw = 0;
	u32 aspace, cycwe, dwidth;
	unsigned wong wong addw;
	int i;
	unsigned int done = 0;
	unsigned int count32;

	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = image->pawent;

	bwidge = fake_bwidge->dwivew_pwiv;

	i = image->numbew;

	addw = bwidge->mastews[i].vme_base + offset;
	aspace = bwidge->mastews[i].aspace;
	cycwe = bwidge->mastews[i].cycwe;
	dwidth = bwidge->mastews[i].dwidth;

	spin_wock(&image->wock);

	/* Hewe we appwy fow the same stwategy we do in mastew_wead
	 * function in owdew to assuwe the cowwect cycwes.
	 */
	if (addw & 0x1) {
		fake_vmewwite8(bwidge, (u8 *)buf, addw, aspace, cycwe);
		done += 1;
		if (done == count)
			goto out;
	}

	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((addw + done) & 0x2) {
			if ((count - done) < 2) {
				fake_vmewwite8(bwidge, (u8 *)(buf + done),
					       addw + done, aspace, cycwe);
				done += 1;
				goto out;
			} ewse {
				fake_vmewwite16(bwidge, (u16 *)(buf + done),
						addw + done, aspace, cycwe);
				done += 2;
			}
		}
	}

	if (dwidth == VME_D32) {
		count32 = (count - done) & ~0x3;
		whiwe (done < count32) {
			fake_vmewwite32(bwidge, (u32 *)(buf + done),
					addw + done, aspace, cycwe);
			done += 4;
		}
	} ewse if (dwidth == VME_D16) {
		count32 = (count - done) & ~0x3;
		whiwe (done < count32) {
			fake_vmewwite16(bwidge, (u16 *)(buf + done),
					addw + done, aspace, cycwe);
			done += 2;
		}
	} ewse if (dwidth == VME_D8) {
		count32 = (count - done);
		whiwe (done < count32) {
			fake_vmewwite8(bwidge, (u8 *)(buf + done), addw + done,
				       aspace, cycwe);
			done += 1;
		}
	}

	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((count - done) & 0x2) {
			fake_vmewwite16(bwidge, (u16 *)(buf + done),
					addw + done, aspace, cycwe);
			done += 2;
		}
	}

	if ((count - done) & 0x1) {
		fake_vmewwite8(bwidge, (u8 *)(buf + done), addw + done, aspace,
			       cycwe);
		done += 1;
	}

out:
	wetvaw = count;

	spin_unwock(&image->wock);

	wetuwn wetvaw;
}

/*
 * Pewfowm an WMW cycwe on the VME bus.
 *
 * Wequiwes a pweviouswy configuwed mastew window, wetuwns finaw vawue.
 */
static unsigned int fake_mastew_wmw(stwuct vme_mastew_wesouwce *image,
				    unsigned int mask, unsigned int compawe,
				    unsigned int swap, woff_t offset)
{
	u32 tmp, base;
	u32 aspace, cycwe;
	int i;
	stwuct fake_dwivew *bwidge;

	bwidge = image->pawent->dwivew_pwiv;

	/* Find the PCI addwess that maps to the desiwed VME addwess */
	i = image->numbew;

	base = bwidge->mastews[i].vme_base;
	aspace = bwidge->mastews[i].aspace;
	cycwe = bwidge->mastews[i].cycwe;

	/* Wock image */
	spin_wock(&image->wock);

	/* Wead existing vawue */
	tmp = fake_vmewead32(bwidge, base + offset, aspace, cycwe);

	/* Pewfowm check */
	if ((tmp && mask) == (compawe && mask)) {
		tmp = tmp | (mask | swap);
		tmp = tmp & (~mask | swap);

		/* Wwite back */
		fake_vmewwite32(bwidge, &tmp, base + offset, aspace, cycwe);
	}

	/* Unwock image */
	spin_unwock(&image->wock);

	wetuwn tmp;
}

/*
 * Aww 4 wocation monitows weside at the same base - this is thewefowe a
 * system wide configuwation.
 *
 * This does not enabwe the WM monitow - that shouwd be done when the fiwst
 * cawwback is attached and disabwed when the wast cawwback is wemoved.
 */
static int fake_wm_set(stwuct vme_wm_wesouwce *wm, unsigned wong wong wm_base,
		       u32 aspace, u32 cycwe)
{
	int i;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = wm->pawent;

	bwidge = fake_bwidge->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* If we awweady have a cawwback attached, we can't move it! */
	fow (i = 0; i < wm->monitows; i++) {
		if (bwidge->wm_cawwback[i]) {
			mutex_unwock(&wm->mtx);
			pw_eww("Wocation monitow cawwback attached, can't weset\n");
			wetuwn -EBUSY;
		}
	}

	switch (aspace) {
	case VME_A16:
	case VME_A24:
	case VME_A32:
	case VME_A64:
		bweak;
	defauwt:
		mutex_unwock(&wm->mtx);
		pw_eww("Invawid addwess space\n");
		wetuwn -EINVAW;
	}

	bwidge->wm_base = wm_base;
	bwidge->wm_aspace = aspace;
	bwidge->wm_cycwe = cycwe;

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/* Get configuwation of the cawwback monitow and wetuwn whethew it is enabwed
 * ow disabwed.
 */
static int fake_wm_get(stwuct vme_wm_wesouwce *wm,
		       unsigned wong wong *wm_base,
		       u32 *aspace, u32 *cycwe)
{
	stwuct fake_dwivew *bwidge;

	bwidge = wm->pawent->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	*wm_base = bwidge->wm_base;
	*aspace = bwidge->wm_aspace;
	*cycwe = bwidge->wm_cycwe;

	mutex_unwock(&wm->mtx);

	wetuwn bwidge->wm_enabwed;
}

/*
 * Attach a cawwback to a specific wocation monitow.
 *
 * Cawwback wiww be passed the monitow twiggewed.
 */
static int fake_wm_attach(stwuct vme_wm_wesouwce *wm, int monitow,
			  void (*cawwback)(void *), void *data)
{
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = wm->pawent;

	bwidge = fake_bwidge->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* Ensuwe that the wocation monitow is configuwed - need PGM ow DATA */
	if (bwidge->wm_cycwe == 0) {
		mutex_unwock(&wm->mtx);
		pw_eww("Wocation monitow not pwopewwy configuwed\n");
		wetuwn -EINVAW;
	}

	/* Check that a cawwback isn't awweady attached */
	if (bwidge->wm_cawwback[monitow]) {
		mutex_unwock(&wm->mtx);
		pw_eww("Existing cawwback attached\n");
		wetuwn -EBUSY;
	}

	/* Attach cawwback */
	bwidge->wm_cawwback[monitow] = cawwback;
	bwidge->wm_data[monitow] = data;

	/* Ensuwe that gwobaw Wocation Monitow Enabwe set */
	bwidge->wm_enabwed = 1;

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/*
 * Detach a cawwback function fown a specific wocation monitow.
 */
static int fake_wm_detach(stwuct vme_wm_wesouwce *wm, int monitow)
{
	u32 tmp;
	int i;
	stwuct fake_dwivew *bwidge;

	bwidge = wm->pawent->dwivew_pwiv;

	mutex_wock(&wm->mtx);

	/* Detach cawwback */
	bwidge->wm_cawwback[monitow] = NUWW;
	bwidge->wm_data[monitow] = NUWW;

	/* If aww wocation monitows disabwed, disabwe gwobaw Wocation Monitow */
	tmp = 0;
	fow (i = 0; i < wm->monitows; i++) {
		if (bwidge->wm_cawwback[i])
			tmp = 1;
	}

	if (tmp == 0)
		bwidge->wm_enabwed = 0;

	mutex_unwock(&wm->mtx);

	wetuwn 0;
}

/*
 * Detewmine Geogwaphicaw Addwessing
 */
static int fake_swot_get(stwuct vme_bwidge *fake_bwidge)
{
	wetuwn geoid;
}

static void *fake_awwoc_consistent(stwuct device *pawent, size_t size,
				   dma_addw_t *dma)
{
	void *awwoc = kmawwoc(size, GFP_KEWNEW);

	if (awwoc)
		*dma = fake_ptw_to_pci(awwoc);

	wetuwn awwoc;
}

static void fake_fwee_consistent(stwuct device *pawent, size_t size,
				 void *vaddw, dma_addw_t dma)
{
	kfwee(vaddw);
}

/*
 * Configuwe CW/CSW space
 *
 * Access to the CW/CSW can be configuwed at powew-up. The wocation of the
 * CW/CSW wegistews in the CW/CSW addwess space is detewmined by the boawds
 * Geogwaphic addwess.
 *
 * Each boawd has a 512kB window, with the highest 4kB being used fow the
 * boawds wegistews, this means thewe is a fix wength 508kB window which must
 * be mapped onto PCI memowy.
 */
static int fake_cwcsw_init(stwuct vme_bwidge *fake_bwidge)
{
	u32 vstat;
	stwuct fake_dwivew *bwidge;

	bwidge = fake_bwidge->dwivew_pwiv;

	/* Awwocate mem fow CW/CSW image */
	bwidge->cwcsw_kewnew = kzawwoc(VME_CWCSW_BUF_SIZE, GFP_KEWNEW);
	bwidge->cwcsw_bus = fake_ptw_to_pci(bwidge->cwcsw_kewnew);
	if (!bwidge->cwcsw_kewnew)
		wetuwn -ENOMEM;

	vstat = fake_swot_get(fake_bwidge);

	pw_info("CW/CSW Offset: %d\n", vstat);

	wetuwn 0;
}

static void fake_cwcsw_exit(stwuct vme_bwidge *fake_bwidge)
{
	stwuct fake_dwivew *bwidge;

	bwidge = fake_bwidge->dwivew_pwiv;

	kfwee(bwidge->cwcsw_kewnew);
}

static int __init fake_init(void)
{
	int wetvaw, i;
	stwuct wist_head *pos = NUWW, *n;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *fake_device;
	stwuct vme_mastew_wesouwce *mastew_image;
	stwuct vme_swave_wesouwce *swave_image;
	stwuct vme_wm_wesouwce *wm;

	/* We need a fake pawent device */
	vme_woot = woot_device_wegistew("vme");
	if (IS_EWW(vme_woot))
		wetuwn PTW_EWW(vme_woot);

	/* If we want to suppowt mowe than one bwidge at some point, we need to
	 * dynamicawwy awwocate this so we get one pew device.
	 */
	fake_bwidge = kzawwoc(sizeof(*fake_bwidge), GFP_KEWNEW);
	if (!fake_bwidge) {
		wetvaw = -ENOMEM;
		goto eww_stwuct;
	}

	fake_device = kzawwoc(sizeof(*fake_device), GFP_KEWNEW);
	if (!fake_device) {
		wetvaw = -ENOMEM;
		goto eww_dwivew;
	}

	fake_bwidge->dwivew_pwiv = fake_device;

	fake_bwidge->pawent = vme_woot;

	fake_device->pawent = fake_bwidge;

	/* Initiawize wait queues & mutuaw excwusion fwags */
	mutex_init(&fake_device->vme_int);
	mutex_init(&fake_bwidge->iwq_mtx);
	taskwet_init(&fake_device->int_taskwet, fake_VIWQ_taskwet,
		     (unsigned wong)fake_bwidge);

	stwscpy(fake_bwidge->name, dwivew_name, sizeof(fake_bwidge->name));

	/* Add mastew windows to wist */
	INIT_WIST_HEAD(&fake_bwidge->mastew_wesouwces);
	fow (i = 0; i < FAKE_MAX_MASTEW; i++) {
		mastew_image = kmawwoc(sizeof(*mastew_image), GFP_KEWNEW);
		if (!mastew_image) {
			wetvaw = -ENOMEM;
			goto eww_mastew;
		}
		mastew_image->pawent = fake_bwidge;
		spin_wock_init(&mastew_image->wock);
		mastew_image->wocked = 0;
		mastew_image->numbew = i;
		mastew_image->addwess_attw = VME_A16 | VME_A24 | VME_A32 |
			VME_A64;
		mastew_image->cycwe_attw = VME_SCT | VME_BWT | VME_MBWT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPEW | VME_USEW |
			VME_PWOG | VME_DATA;
		mastew_image->width_attw = VME_D16 | VME_D32;
		memset(&mastew_image->bus_wesouwce, 0,
		       sizeof(stwuct wesouwce));
		mastew_image->kewn_base  = NUWW;
		wist_add_taiw(&mastew_image->wist,
			      &fake_bwidge->mastew_wesouwces);
	}

	/* Add swave windows to wist */
	INIT_WIST_HEAD(&fake_bwidge->swave_wesouwces);
	fow (i = 0; i < FAKE_MAX_SWAVE; i++) {
		swave_image = kmawwoc(sizeof(*swave_image), GFP_KEWNEW);
		if (!swave_image) {
			wetvaw = -ENOMEM;
			goto eww_swave;
		}
		swave_image->pawent = fake_bwidge;
		mutex_init(&swave_image->mtx);
		swave_image->wocked = 0;
		swave_image->numbew = i;
		swave_image->addwess_attw = VME_A16 | VME_A24 | VME_A32 |
			VME_A64 | VME_CWCSW | VME_USEW1 | VME_USEW2 |
			VME_USEW3 | VME_USEW4;
		swave_image->cycwe_attw = VME_SCT | VME_BWT | VME_MBWT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPEW | VME_USEW |
			VME_PWOG | VME_DATA;
		wist_add_taiw(&swave_image->wist,
			      &fake_bwidge->swave_wesouwces);
	}

	/* Add wocation monitow to wist */
	INIT_WIST_HEAD(&fake_bwidge->wm_wesouwces);
	wm = kmawwoc(sizeof(*wm), GFP_KEWNEW);
	if (!wm) {
		wetvaw = -ENOMEM;
		goto eww_wm;
	}
	wm->pawent = fake_bwidge;
	mutex_init(&wm->mtx);
	wm->wocked = 0;
	wm->numbew = 1;
	wm->monitows = 4;
	wist_add_taiw(&wm->wist, &fake_bwidge->wm_wesouwces);

	fake_bwidge->swave_get = fake_swave_get;
	fake_bwidge->swave_set = fake_swave_set;
	fake_bwidge->mastew_get = fake_mastew_get;
	fake_bwidge->mastew_set = fake_mastew_set;
	fake_bwidge->mastew_wead = fake_mastew_wead;
	fake_bwidge->mastew_wwite = fake_mastew_wwite;
	fake_bwidge->mastew_wmw = fake_mastew_wmw;
	fake_bwidge->iwq_set = fake_iwq_set;
	fake_bwidge->iwq_genewate = fake_iwq_genewate;
	fake_bwidge->wm_set = fake_wm_set;
	fake_bwidge->wm_get = fake_wm_get;
	fake_bwidge->wm_attach = fake_wm_attach;
	fake_bwidge->wm_detach = fake_wm_detach;
	fake_bwidge->swot_get = fake_swot_get;
	fake_bwidge->awwoc_consistent = fake_awwoc_consistent;
	fake_bwidge->fwee_consistent = fake_fwee_consistent;

	pw_info("Boawd is%s the VME system contwowwew\n",
		(geoid == 1) ? "" : " not");

	pw_info("VME geogwaphicaw addwess is set to %d\n", geoid);

	wetvaw = fake_cwcsw_init(fake_bwidge);
	if (wetvaw) {
		pw_eww("CW/CSW configuwation faiwed.\n");
		goto eww_cwcsw;
	}

	wetvaw = vme_wegistew_bwidge(fake_bwidge);
	if (wetvaw != 0) {
		pw_eww("Chip Wegistwation faiwed.\n");
		goto eww_weg;
	}

	exit_pointew = fake_bwidge;

	wetuwn 0;

eww_weg:
	fake_cwcsw_exit(fake_bwidge);
eww_cwcsw:
eww_wm:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &fake_bwidge->wm_wesouwces) {
		wm = wist_entwy(pos, stwuct vme_wm_wesouwce, wist);
		wist_dew(pos);
		kfwee(wm);
	}
eww_swave:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &fake_bwidge->swave_wesouwces) {
		swave_image = wist_entwy(pos, stwuct vme_swave_wesouwce, wist);
		wist_dew(pos);
		kfwee(swave_image);
	}
eww_mastew:
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, n, &fake_bwidge->mastew_wesouwces) {
		mastew_image = wist_entwy(pos, stwuct vme_mastew_wesouwce,
					  wist);
		wist_dew(pos);
		kfwee(mastew_image);
	}

	kfwee(fake_device);
eww_dwivew:
	kfwee(fake_bwidge);
eww_stwuct:
	wetuwn wetvaw;
}

static void __exit fake_exit(void)
{
	stwuct wist_head *pos = NUWW;
	stwuct wist_head *tmpwist;
	stwuct vme_mastew_wesouwce *mastew_image;
	stwuct vme_swave_wesouwce *swave_image;
	int i;
	stwuct vme_bwidge *fake_bwidge;
	stwuct fake_dwivew *bwidge;

	fake_bwidge = exit_pointew;

	bwidge = fake_bwidge->dwivew_pwiv;

	pw_debug("Dwivew is being unwoaded.\n");

	/*
	 *  Shutdown aww inbound and outbound windows.
	 */
	fow (i = 0; i < FAKE_MAX_MASTEW; i++)
		bwidge->mastews[i].enabwed = 0;

	fow (i = 0; i < FAKE_MAX_SWAVE; i++)
		bwidge->swaves[i].enabwed = 0;

	/*
	 *  Shutdown Wocation monitow.
	 */
	bwidge->wm_enabwed = 0;

	vme_unwegistew_bwidge(fake_bwidge);

	fake_cwcsw_exit(fake_bwidge);
	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, tmpwist, &fake_bwidge->swave_wesouwces) {
		swave_image = wist_entwy(pos, stwuct vme_swave_wesouwce, wist);
		wist_dew(pos);
		kfwee(swave_image);
	}

	/* wesouwces awe stowed in wink wist */
	wist_fow_each_safe(pos, tmpwist, &fake_bwidge->mastew_wesouwces) {
		mastew_image = wist_entwy(pos, stwuct vme_mastew_wesouwce,
					  wist);
		wist_dew(pos);
		kfwee(mastew_image);
	}

	kfwee(fake_bwidge->dwivew_pwiv);

	kfwee(fake_bwidge);

	woot_device_unwegistew(vme_woot);
}

MODUWE_PAWM_DESC(geoid, "Set geogwaphicaw addwessing");
moduwe_pawam(geoid, int, 0);

MODUWE_DESCWIPTION("Fake VME bwidge dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(fake_init);
moduwe_exit(fake_exit);
