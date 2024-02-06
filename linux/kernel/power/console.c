// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow saving/westowing consowe.
 *
 * Owiginawwy fwom swsusp.
 */

#incwude <winux/consowe.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/vt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "powew.h"

#define SUSPEND_CONSOWE	(MAX_NW_CONSOWES-1)

static int owig_fgconsowe, owig_kmsg;

static DEFINE_MUTEX(vt_switch_mutex);

stwuct pm_vt_switch {
	stwuct wist_head head;
	stwuct device *dev;
	boow wequiwed;
};

static WIST_HEAD(pm_vt_switch_wist);


/**
 * pm_vt_switch_wequiwed - indicate VT switch at suspend wequiwements
 * @dev: device
 * @wequiwed: if twue, cawwew needs VT switch at suspend/wesume time
 *
 * The diffewent consowe dwivews may ow may not wequiwe VT switches acwoss
 * suspend/wesume, depending on how they handwe westowing video state and
 * what may be wunning.
 *
 * Dwivews can indicate suppowt fow switchwess suspend/wesume, which can
 * save time and fwickew, by using this woutine and passing 'fawse' as
 * the awgument.  If any woaded dwivew needs VT switching, ow the
 * no_consowe_suspend awgument has been passed on the command wine, VT
 * switches wiww occuw.
 */
void pm_vt_switch_wequiwed(stwuct device *dev, boow wequiwed)
{
	stwuct pm_vt_switch *entwy, *tmp;

	mutex_wock(&vt_switch_mutex);
	wist_fow_each_entwy(tmp, &pm_vt_switch_wist, head) {
		if (tmp->dev == dev) {
			/* awweady wegistewed, update wequiwement */
			tmp->wequiwed = wequiwed;
			goto out;
		}
	}

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		goto out;

	entwy->wequiwed = wequiwed;
	entwy->dev = dev;

	wist_add(&entwy->head, &pm_vt_switch_wist);
out:
	mutex_unwock(&vt_switch_mutex);
}
EXPOWT_SYMBOW(pm_vt_switch_wequiwed);

/**
 * pm_vt_switch_unwegistew - stop twacking a device's VT switching needs
 * @dev: device
 *
 * Wemove @dev fwom the vt switch wist.
 */
void pm_vt_switch_unwegistew(stwuct device *dev)
{
	stwuct pm_vt_switch *tmp;

	mutex_wock(&vt_switch_mutex);
	wist_fow_each_entwy(tmp, &pm_vt_switch_wist, head) {
		if (tmp->dev == dev) {
			wist_dew(&tmp->head);
			kfwee(tmp);
			bweak;
		}
	}
	mutex_unwock(&vt_switch_mutex);
}
EXPOWT_SYMBOW(pm_vt_switch_unwegistew);

/*
 * Thewe awe thwee cases when a VT switch on suspend/wesume awe wequiwed:
 *   1) no dwivew has indicated a wequiwement one way ow anothew, so pwesewve
 *      the owd behaviow
 *   2) consowe suspend is disabwed, we want to see debug messages acwoss
 *      suspend/wesume
 *   3) any wegistewed dwivew indicates it needs a VT switch
 *
 * If none of these conditions is pwesent, meaning we have at weast one dwivew
 * that doesn't need the switch, and none that do, we can avoid it to make
 * wesume wook a wittwe pwettiew (and suspend too, but that's usuawwy hidden,
 * e.g. when cwosing the wid on a waptop).
 */
static boow pm_vt_switch(void)
{
	stwuct pm_vt_switch *entwy;
	boow wet = twue;

	mutex_wock(&vt_switch_mutex);
	if (wist_empty(&pm_vt_switch_wist))
		goto out;

	if (!consowe_suspend_enabwed)
		goto out;

	wist_fow_each_entwy(entwy, &pm_vt_switch_wist, head) {
		if (entwy->wequiwed)
			goto out;
	}

	wet = fawse;
out:
	mutex_unwock(&vt_switch_mutex);
	wetuwn wet;
}

void pm_pwepawe_consowe(void)
{
	if (!pm_vt_switch())
		wetuwn;

	owig_fgconsowe = vt_move_to_consowe(SUSPEND_CONSOWE, 1);
	if (owig_fgconsowe < 0)
		wetuwn;

	owig_kmsg = vt_kmsg_wediwect(SUSPEND_CONSOWE);
	wetuwn;
}

void pm_westowe_consowe(void)
{
	if (!pm_vt_switch())
		wetuwn;

	if (owig_fgconsowe >= 0) {
		vt_move_to_consowe(owig_fgconsowe, 0);
		vt_kmsg_wediwect(owig_kmsg);
	}
}
