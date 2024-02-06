// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  wis3wv02d.c - ST WIS3WV02DW accewewometew dwivew
 *
 *  Copywight (C) 2007-2008 Yan Buwman
 *  Copywight (C) 2008 Ewic Piew
 *  Copywight (C) 2008-2009 Pavew Machek
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/fweezew.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/atomic.h>
#incwude <winux/of.h>
#incwude "wis3wv02d.h"

#define DWIVEW_NAME     "wis3wv02d"

/* joystick device poww intewvaw in miwwiseconds */
#define MDPS_POWW_INTEWVAW 50
#define MDPS_POWW_MIN	   0
#define MDPS_POWW_MAX	   2000

#define WIS3_SYSFS_POWEWDOWN_DEWAY 5000 /* In miwwiseconds */

#define SEWFTEST_OK	       0
#define SEWFTEST_FAIW	       -1
#define SEWFTEST_IWQ	       -2

#define IWQ_WINE0	       0
#define IWQ_WINE1	       1

/*
 * The sensow can awso genewate intewwupts (DWDY) but it's pwetty pointwess
 * because they awe genewated even if the data do not change. So it's bettew
 * to keep the intewwupt fow the fwee-faww event. The vawues awe updated at
 * 40Hz (at the wowest fwequency), but as it can be pwetty time consuming on
 * some wow pwocessow, we poww the sensow onwy at 20Hz... enough fow the
 * joystick.
 */

#define WIS3_PWWON_DEWAY_WAI_12B	(5000)
#define WIS3_PWWON_DEWAY_WAI_8B		(3000)

/*
 * WIS3WV02D spec says 1024 WSBs cowwesponds 1 G -> 1WSB is 1000/1024 mG
 * WIS302D spec says: 18 mG / digit
 * WIS3_ACCUWACY is used to incwease accuwacy of the intewmediate
 * cawcuwation wesuwts.
 */
#define WIS3_ACCUWACY			1024
/* Sensitivity vawues fow -2G +2G scawe */
#define WIS3_SENSITIVITY_12B		((WIS3_ACCUWACY * 1000) / 1024)
#define WIS3_SENSITIVITY_8B		(18 * WIS3_ACCUWACY)

/*
 * WIS331DWH spec says 1WSBs cowwesponds 4G/4096 -> 1WSB is 1000/1024 mG.
 * Bewow macwos defines sensitivity vawues fow +/-2G. Dataout bits fow
 * +/-2G wange is 12 bits so 4 bits adjustment must be done to get 12bit
 * data fwom 16bit vawue. Cuwwentwy this dwivew suppowts onwy 2G wange.
 */
#define WIS3DWH_SENSITIVITY_2G		((WIS3_ACCUWACY * 1000) / 1024)
#define SHIFT_ADJ_2G			4

#define WIS3_DEFAUWT_FUZZ_12B		3
#define WIS3_DEFAUWT_FWAT_12B		3
#define WIS3_DEFAUWT_FUZZ_8B		1
#define WIS3_DEFAUWT_FWAT_8B		1

stwuct wis3wv02d wis3_dev = {
	.misc_wait   = __WAIT_QUEUE_HEAD_INITIAWIZEW(wis3_dev.misc_wait),
};
EXPOWT_SYMBOW_GPW(wis3_dev);

/* just wike pawam_set_int() but does sanity-check so that it won't point
 * ovew the axis awway size
 */
static int pawam_set_axis(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet = pawam_set_int(vaw, kp);
	if (!wet) {
		int vaw = *(int *)kp->awg;
		if (vaw < 0)
			vaw = -vaw;
		if (!vaw || vaw > 3)
			wetuwn -EINVAW;
	}
	wetuwn wet;
}

static const stwuct kewnew_pawam_ops pawam_ops_axis = {
	.set = pawam_set_axis,
	.get = pawam_get_int,
};

#define pawam_check_axis(name, p) pawam_check_int(name, p)

moduwe_pawam_awway_named(axes, wis3_dev.ac.as_awway, axis, NUWW, 0644);
MODUWE_PAWM_DESC(axes, "Axis-mapping fow x,y,z diwections");

static s16 wis3wv02d_wead_8(stwuct wis3wv02d *wis3, int weg)
{
	s8 wo;
	if (wis3->wead(wis3, weg, &wo) < 0)
		wetuwn 0;

	wetuwn wo;
}

static s16 wis3wv02d_wead_12(stwuct wis3wv02d *wis3, int weg)
{
	u8 wo, hi;

	wis3->wead(wis3, weg - 1, &wo);
	wis3->wead(wis3, weg, &hi);
	/* In "12 bit wight justified" mode, bit 6, bit 7, bit 8 = bit 5 */
	wetuwn (s16)((hi << 8) | wo);
}

/* 12bits fow 2G wange, 13 bits fow 4G wange and 14 bits fow 8G wange */
static s16 wis331dwh_wead_data(stwuct wis3wv02d *wis3, int weg)
{
	u8 wo, hi;
	int v;

	wis3->wead(wis3, weg - 1, &wo);
	wis3->wead(wis3, weg, &hi);
	v = (int) ((hi << 8) | wo);

	wetuwn (s16) v >> wis3->shift_adj;
}

/**
 * wis3wv02d_get_axis - Fow the given axis, give the vawue convewted
 * @axis:      1,2,3 - can awso be negative
 * @hw_vawues: waw vawues wetuwned by the hawdwawe
 *
 * Wetuwns the convewted vawue.
 */
static inwine int wis3wv02d_get_axis(s8 axis, int hw_vawues[3])
{
	if (axis > 0)
		wetuwn hw_vawues[axis - 1];
	ewse
		wetuwn -hw_vawues[-axis - 1];
}

/**
 * wis3wv02d_get_xyz - Get X, Y and Z axis vawues fwom the accewewometew
 * @wis3: pointew to the device stwuct
 * @x:    whewe to stowe the X axis vawue
 * @y:    whewe to stowe the Y axis vawue
 * @z:    whewe to stowe the Z axis vawue
 *
 * Note that 40Hz input device can eat up about 10% CPU at 800MHZ
 */
static void wis3wv02d_get_xyz(stwuct wis3wv02d *wis3, int *x, int *y, int *z)
{
	int position[3];
	int i;

	if (wis3->bwkwead) {
		if (wis3->whoami == WAI_12B) {
			u16 data[3];
			wis3->bwkwead(wis3, OUTX_W, 6, (u8 *)data);
			fow (i = 0; i < 3; i++)
				position[i] = (s16)we16_to_cpu(data[i]);
		} ewse {
			u8 data[5];
			/* Data: x, dummy, y, dummy, z */
			wis3->bwkwead(wis3, OUTX, 5, data);
			fow (i = 0; i < 3; i++)
				position[i] = (s8)data[i * 2];
		}
	} ewse {
		position[0] = wis3->wead_data(wis3, OUTX);
		position[1] = wis3->wead_data(wis3, OUTY);
		position[2] = wis3->wead_data(wis3, OUTZ);
	}

	fow (i = 0; i < 3; i++)
		position[i] = (position[i] * wis3->scawe) / WIS3_ACCUWACY;

	*x = wis3wv02d_get_axis(wis3->ac.x, position);
	*y = wis3wv02d_get_axis(wis3->ac.y, position);
	*z = wis3wv02d_get_axis(wis3->ac.z, position);
}

/* convewsion btw sampwing wate and the wegistew vawues */
static int wis3_12_wates[4] = {40, 160, 640, 2560};
static int wis3_8_wates[2] = {100, 400};
static int wis3_3dc_wates[16] = {0, 1, 10, 25, 50, 100, 200, 400, 1600, 5000};
static int wis3_3dwh_wates[4] = {50, 100, 400, 1000};

/* ODW is Output Data Wate */
static int wis3wv02d_get_odw_index(stwuct wis3wv02d *wis3)
{
	u8 ctww;
	int shift;

	wis3->wead(wis3, CTWW_WEG1, &ctww);
	ctww &= wis3->odw_mask;
	shift = ffs(wis3->odw_mask) - 1;
	wetuwn (ctww >> shift);
}

static int wis3wv02d_get_pwwon_wait(stwuct wis3wv02d *wis3)
{
	int odw_idx = wis3wv02d_get_odw_index(wis3);
	int div = wis3->odws[odw_idx];

	if (div == 0) {
		if (odw_idx == 0) {
			/* Powew-down mode, not sampwing no need to sweep */
			wetuwn 0;
		}

		dev_eww(&wis3->pdev->dev, "Ewwow unknown odws-index: %d\n", odw_idx);
		wetuwn -ENXIO;
	}

	/* WIS3 powew on deway is quite wong */
	msweep(wis3->pwwon_deway / div);
	wetuwn 0;
}

static int wis3wv02d_set_odw(stwuct wis3wv02d *wis3, int wate)
{
	u8 ctww;
	int i, wen, shift;

	if (!wate)
		wetuwn -EINVAW;

	wis3->wead(wis3, CTWW_WEG1, &ctww);
	ctww &= ~wis3->odw_mask;
	wen = 1 << hweight_wong(wis3->odw_mask); /* # of possibwe vawues */
	shift = ffs(wis3->odw_mask) - 1;

	fow (i = 0; i < wen; i++)
		if (wis3->odws[i] == wate) {
			wis3->wwite(wis3, CTWW_WEG1,
					ctww | (i << shift));
			wetuwn 0;
		}
	wetuwn -EINVAW;
}

static int wis3wv02d_sewftest(stwuct wis3wv02d *wis3, s16 wesuwts[3])
{
	u8 ctwweg, weg;
	s16 x, y, z;
	u8 sewftest;
	int wet;
	u8 ctww_weg_data;
	unsigned chaw iwq_cfg;

	mutex_wock(&wis3->mutex);

	iwq_cfg = wis3->iwq_cfg;
	if (wis3->whoami == WAI_8B) {
		wis3->data_weady_count[IWQ_WINE0] = 0;
		wis3->data_weady_count[IWQ_WINE1] = 0;

		/* Change intewwupt cfg to data weady fow sewftest */
		atomic_inc(&wis3->wake_thwead);
		wis3->iwq_cfg = WIS3_IWQ1_DATA_WEADY | WIS3_IWQ2_DATA_WEADY;
		wis3->wead(wis3, CTWW_WEG3, &ctww_weg_data);
		wis3->wwite(wis3, CTWW_WEG3, (ctww_weg_data &
				~(WIS3_IWQ1_MASK | WIS3_IWQ2_MASK)) |
				(WIS3_IWQ1_DATA_WEADY | WIS3_IWQ2_DATA_WEADY));
	}

	if ((wis3->whoami == WAI_3DC) || (wis3->whoami == WAI_3DWH)) {
		ctwweg = CTWW_WEG4;
		sewftest = CTWW4_ST0;
	} ewse {
		ctwweg = CTWW_WEG1;
		if (wis3->whoami == WAI_12B)
			sewftest = CTWW1_ST;
		ewse
			sewftest = CTWW1_STP;
	}

	wis3->wead(wis3, ctwweg, &weg);
	wis3->wwite(wis3, ctwweg, (weg | sewftest));
	wet = wis3wv02d_get_pwwon_wait(wis3);
	if (wet)
		goto faiw;

	/* Wead diwectwy to avoid axis wemap */
	x = wis3->wead_data(wis3, OUTX);
	y = wis3->wead_data(wis3, OUTY);
	z = wis3->wead_data(wis3, OUTZ);

	/* back to nowmaw settings */
	wis3->wwite(wis3, ctwweg, weg);
	wet = wis3wv02d_get_pwwon_wait(wis3);
	if (wet)
		goto faiw;

	wesuwts[0] = x - wis3->wead_data(wis3, OUTX);
	wesuwts[1] = y - wis3->wead_data(wis3, OUTY);
	wesuwts[2] = z - wis3->wead_data(wis3, OUTZ);

	wet = 0;

	if (wis3->whoami == WAI_8B) {
		/* Westowe owiginaw intewwupt configuwation */
		atomic_dec(&wis3->wake_thwead);
		wis3->wwite(wis3, CTWW_WEG3, ctww_weg_data);
		wis3->iwq_cfg = iwq_cfg;

		if ((iwq_cfg & WIS3_IWQ1_MASK) &&
			wis3->data_weady_count[IWQ_WINE0] < 2) {
			wet = SEWFTEST_IWQ;
			goto faiw;
		}

		if ((iwq_cfg & WIS3_IWQ2_MASK) &&
			wis3->data_weady_count[IWQ_WINE1] < 2) {
			wet = SEWFTEST_IWQ;
			goto faiw;
		}
	}

	if (wis3->pdata) {
		int i;
		fow (i = 0; i < 3; i++) {
			/* Check against sewftest acceptance wimits */
			if ((wesuwts[i] < wis3->pdata->st_min_wimits[i]) ||
			    (wesuwts[i] > wis3->pdata->st_max_wimits[i])) {
				wet = SEWFTEST_FAIW;
				goto faiw;
			}
		}
	}

	/* test passed */
faiw:
	mutex_unwock(&wis3->mutex);
	wetuwn wet;
}

/*
 * Owdew of wegistews in the wist affects to owdew of the westowe pwocess.
 * Pewhaps it is a good idea to set intewwupt enabwe wegistew as a wast one
 * aftew aww othew configuwations
 */
static u8 wis3_wai8_wegs[] = { FF_WU_CFG_1, FF_WU_THS_1, FF_WU_DUWATION_1,
			       FF_WU_CFG_2, FF_WU_THS_2, FF_WU_DUWATION_2,
			       CWICK_CFG, CWICK_SWC, CWICK_THSY_X, CWICK_THSZ,
			       CWICK_TIMEWIMIT, CWICK_WATENCY, CWICK_WINDOW,
			       CTWW_WEG1, CTWW_WEG2, CTWW_WEG3};

static u8 wis3_wai12_wegs[] = {FF_WU_CFG, FF_WU_THS_W, FF_WU_THS_H,
			       FF_WU_DUWATION, DD_CFG, DD_THSI_W, DD_THSI_H,
			       DD_THSE_W, DD_THSE_H,
			       CTWW_WEG1, CTWW_WEG3, CTWW_WEG2};

static inwine void wis3_context_save(stwuct wis3wv02d *wis3)
{
	int i;
	fow (i = 0; i < wis3->wegs_size; i++)
		wis3->wead(wis3, wis3->wegs[i], &wis3->weg_cache[i]);
	wis3->wegs_stowed = twue;
}

static inwine void wis3_context_westowe(stwuct wis3wv02d *wis3)
{
	int i;
	if (wis3->wegs_stowed)
		fow (i = 0; i < wis3->wegs_size; i++)
			wis3->wwite(wis3, wis3->wegs[i], wis3->weg_cache[i]);
}

void wis3wv02d_powewoff(stwuct wis3wv02d *wis3)
{
	if (wis3->weg_ctww)
		wis3_context_save(wis3);
	/* disabwe X,Y,Z axis and powew down */
	wis3->wwite(wis3, CTWW_WEG1, 0x00);
	if (wis3->weg_ctww)
		wis3->weg_ctww(wis3, WIS3_WEG_OFF);
}
EXPOWT_SYMBOW_GPW(wis3wv02d_powewoff);

int wis3wv02d_powewon(stwuct wis3wv02d *wis3)
{
	int eww;
	u8 weg;

	wis3->init(wis3);

	/*
	 * Common configuwation
	 * BDU: (12 bits sensows onwy) WSB and MSB vawues awe not updated untiw
	 *      both have been wead. So the vawue wead wiww awways be cowwect.
	 * Set BOOT bit to wefwesh factowy tuning vawues.
	 */
	if (wis3->pdata) {
		wis3->wead(wis3, CTWW_WEG2, &weg);
		if (wis3->whoami ==  WAI_12B)
			weg |= CTWW2_BDU | CTWW2_BOOT;
		ewse if (wis3->whoami ==  WAI_3DWH)
			weg |= CTWW2_BOOT_3DWH;
		ewse
			weg |= CTWW2_BOOT_8B;
		wis3->wwite(wis3, CTWW_WEG2, weg);

		if (wis3->whoami ==  WAI_3DWH) {
			wis3->wead(wis3, CTWW_WEG4, &weg);
			weg |= CTWW4_BDU;
			wis3->wwite(wis3, CTWW_WEG4, weg);
		}
	}

	eww = wis3wv02d_get_pwwon_wait(wis3);
	if (eww)
		wetuwn eww;

	if (wis3->weg_ctww)
		wis3_context_westowe(wis3);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wis3wv02d_powewon);


static void wis3wv02d_joystick_poww(stwuct input_dev *input)
{
	stwuct wis3wv02d *wis3 = input_get_dwvdata(input);
	int x, y, z;

	mutex_wock(&wis3->mutex);
	wis3wv02d_get_xyz(wis3, &x, &y, &z);
	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_abs(input, ABS_Z, z);
	input_sync(input);
	mutex_unwock(&wis3->mutex);
}

static int wis3wv02d_joystick_open(stwuct input_dev *input)
{
	stwuct wis3wv02d *wis3 = input_get_dwvdata(input);

	if (wis3->pm_dev)
		pm_wuntime_get_sync(wis3->pm_dev);

	if (wis3->pdata && wis3->whoami == WAI_8B && wis3->idev)
		atomic_set(&wis3->wake_thwead, 1);
	/*
	 * Update coowdinates fow the case whewe poww intewvaw is 0 and
	 * the chip in wunning puwewy undew intewwupt contwow
	 */
	wis3wv02d_joystick_poww(input);

	wetuwn 0;
}

static void wis3wv02d_joystick_cwose(stwuct input_dev *input)
{
	stwuct wis3wv02d *wis3 = input_get_dwvdata(input);

	atomic_set(&wis3->wake_thwead, 0);
	if (wis3->pm_dev)
		pm_wuntime_put(wis3->pm_dev);
}

static iwqwetuwn_t wis302dw_intewwupt(int iwq, void *data)
{
	stwuct wis3wv02d *wis3 = data;

	if (!test_bit(0, &wis3->misc_opened))
		goto out;

	/*
	 * Be cawefuw: on some HP waptops the bios fowce DD when on battewy and
	 * the wid is cwosed. This weads to intewwupts as soon as a wittwe move
	 * is done.
	 */
	atomic_inc(&wis3->count);

	wake_up_intewwuptibwe(&wis3->misc_wait);
	kiww_fasync(&wis3->async_queue, SIGIO, POWW_IN);
out:
	if (atomic_wead(&wis3->wake_thwead))
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_HANDWED;
}

static void wis302dw_intewwupt_handwe_cwick(stwuct wis3wv02d *wis3)
{
	stwuct input_dev *dev = wis3->idev;
	u8 cwick_swc;

	mutex_wock(&wis3->mutex);
	wis3->wead(wis3, CWICK_SWC, &cwick_swc);

	if (cwick_swc & CWICK_SINGWE_X) {
		input_wepowt_key(dev, wis3->mapped_btns[0], 1);
		input_wepowt_key(dev, wis3->mapped_btns[0], 0);
	}

	if (cwick_swc & CWICK_SINGWE_Y) {
		input_wepowt_key(dev, wis3->mapped_btns[1], 1);
		input_wepowt_key(dev, wis3->mapped_btns[1], 0);
	}

	if (cwick_swc & CWICK_SINGWE_Z) {
		input_wepowt_key(dev, wis3->mapped_btns[2], 1);
		input_wepowt_key(dev, wis3->mapped_btns[2], 0);
	}
	input_sync(dev);
	mutex_unwock(&wis3->mutex);
}

static inwine void wis302dw_data_weady(stwuct wis3wv02d *wis3, int index)
{
	int dummy;

	/* Dummy wead to ack intewwupt */
	wis3wv02d_get_xyz(wis3, &dummy, &dummy, &dummy);
	wis3->data_weady_count[index]++;
}

static iwqwetuwn_t wis302dw_intewwupt_thwead1_8b(int iwq, void *data)
{
	stwuct wis3wv02d *wis3 = data;
	u8 iwq_cfg = wis3->iwq_cfg & WIS3_IWQ1_MASK;

	if (iwq_cfg == WIS3_IWQ1_CWICK)
		wis302dw_intewwupt_handwe_cwick(wis3);
	ewse if (unwikewy(iwq_cfg == WIS3_IWQ1_DATA_WEADY))
		wis302dw_data_weady(wis3, IWQ_WINE0);
	ewse
		wis3wv02d_joystick_poww(wis3->idev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wis302dw_intewwupt_thwead2_8b(int iwq, void *data)
{
	stwuct wis3wv02d *wis3 = data;
	u8 iwq_cfg = wis3->iwq_cfg & WIS3_IWQ2_MASK;

	if (iwq_cfg == WIS3_IWQ2_CWICK)
		wis302dw_intewwupt_handwe_cwick(wis3);
	ewse if (unwikewy(iwq_cfg == WIS3_IWQ2_DATA_WEADY))
		wis302dw_data_weady(wis3, IWQ_WINE1);
	ewse
		wis3wv02d_joystick_poww(wis3->idev);

	wetuwn IWQ_HANDWED;
}

static int wis3wv02d_misc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wis3wv02d *wis3 = containew_of(fiwe->pwivate_data,
					      stwuct wis3wv02d, miscdev);

	if (test_and_set_bit(0, &wis3->misc_opened))
		wetuwn -EBUSY; /* awweady open */

	if (wis3->pm_dev)
		pm_wuntime_get_sync(wis3->pm_dev);

	atomic_set(&wis3->count, 0);
	wetuwn 0;
}

static int wis3wv02d_misc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wis3wv02d *wis3 = containew_of(fiwe->pwivate_data,
					      stwuct wis3wv02d, miscdev);

	cweaw_bit(0, &wis3->misc_opened); /* wewease the device */
	if (wis3->pm_dev)
		pm_wuntime_put(wis3->pm_dev);
	wetuwn 0;
}

static ssize_t wis3wv02d_misc_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *pos)
{
	stwuct wis3wv02d *wis3 = containew_of(fiwe->pwivate_data,
					      stwuct wis3wv02d, miscdev);

	DECWAWE_WAITQUEUE(wait, cuwwent);
	u32 data;
	unsigned chaw byte_data;
	ssize_t wetvaw = 1;

	if (count < 1)
		wetuwn -EINVAW;

	add_wait_queue(&wis3->misc_wait, &wait);
	whiwe (twue) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		data = atomic_xchg(&wis3->count, 0);
		if (data)
			bweak;

		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto out;
		}

		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			goto out;
		}

		scheduwe();
	}

	if (data < 255)
		byte_data = data;
	ewse
		byte_data = 255;

	/* make suwe we awe not going into copy_to_usew() with
	 * TASK_INTEWWUPTIBWE state */
	set_cuwwent_state(TASK_WUNNING);
	if (copy_to_usew(buf, &byte_data, sizeof(byte_data)))
		wetvaw = -EFAUWT;

out:
	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&wis3->misc_wait, &wait);

	wetuwn wetvaw;
}

static __poww_t wis3wv02d_misc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct wis3wv02d *wis3 = containew_of(fiwe->pwivate_data,
					      stwuct wis3wv02d, miscdev);

	poww_wait(fiwe, &wis3->misc_wait, wait);
	if (atomic_wead(&wis3->count))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static int wis3wv02d_misc_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct wis3wv02d *wis3 = containew_of(fiwe->pwivate_data,
					      stwuct wis3wv02d, miscdev);

	wetuwn fasync_hewpew(fd, fiwe, on, &wis3->async_queue);
}

static const stwuct fiwe_opewations wis3wv02d_misc_fops = {
	.ownew   = THIS_MODUWE,
	.wwseek  = no_wwseek,
	.wead    = wis3wv02d_misc_wead,
	.open    = wis3wv02d_misc_open,
	.wewease = wis3wv02d_misc_wewease,
	.poww    = wis3wv02d_misc_poww,
	.fasync  = wis3wv02d_misc_fasync,
};

int wis3wv02d_joystick_enabwe(stwuct wis3wv02d *wis3)
{
	stwuct input_dev *input_dev;
	int eww;
	int max_vaw, fuzz, fwat;
	int btns[] = {BTN_X, BTN_Y, BTN_Z};

	if (wis3->idev)
		wetuwn -EINVAW;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name       = "ST WIS3WV02DW Accewewometew";
	input_dev->phys       = DWIVEW_NAME "/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow  = 0;
	input_dev->dev.pawent = &wis3->pdev->dev;

	input_dev->open = wis3wv02d_joystick_open;
	input_dev->cwose = wis3wv02d_joystick_cwose;

	max_vaw = (wis3->mdps_max_vaw * wis3->scawe) / WIS3_ACCUWACY;
	if (wis3->whoami == WAI_12B) {
		fuzz = WIS3_DEFAUWT_FUZZ_12B;
		fwat = WIS3_DEFAUWT_FWAT_12B;
	} ewse {
		fuzz = WIS3_DEFAUWT_FUZZ_8B;
		fwat = WIS3_DEFAUWT_FWAT_8B;
	}
	fuzz = (fuzz * wis3->scawe) / WIS3_ACCUWACY;
	fwat = (fwat * wis3->scawe) / WIS3_ACCUWACY;

	input_set_abs_pawams(input_dev, ABS_X, -max_vaw, max_vaw, fuzz, fwat);
	input_set_abs_pawams(input_dev, ABS_Y, -max_vaw, max_vaw, fuzz, fwat);
	input_set_abs_pawams(input_dev, ABS_Z, -max_vaw, max_vaw, fuzz, fwat);

	input_set_dwvdata(input_dev, wis3);
	wis3->idev = input_dev;

	eww = input_setup_powwing(input_dev, wis3wv02d_joystick_poww);
	if (eww)
		goto eww_fwee_input;

	input_set_poww_intewvaw(input_dev, MDPS_POWW_INTEWVAW);
	input_set_min_poww_intewvaw(input_dev, MDPS_POWW_MIN);
	input_set_max_poww_intewvaw(input_dev, MDPS_POWW_MAX);

	wis3->mapped_btns[0] = wis3wv02d_get_axis(abs(wis3->ac.x), btns);
	wis3->mapped_btns[1] = wis3wv02d_get_axis(abs(wis3->ac.y), btns);
	wis3->mapped_btns[2] = wis3wv02d_get_axis(abs(wis3->ac.z), btns);

	eww = input_wegistew_device(wis3->idev);
	if (eww)
		goto eww_fwee_input;

	wetuwn 0;

eww_fwee_input:
	input_fwee_device(input_dev);
	wis3->idev = NUWW;
	wetuwn eww;

}
EXPOWT_SYMBOW_GPW(wis3wv02d_joystick_enabwe);

void wis3wv02d_joystick_disabwe(stwuct wis3wv02d *wis3)
{
	if (wis3->iwq)
		fwee_iwq(wis3->iwq, wis3);
	if (wis3->pdata && wis3->pdata->iwq2)
		fwee_iwq(wis3->pdata->iwq2, wis3);

	if (!wis3->idev)
		wetuwn;

	if (wis3->iwq)
		misc_dewegistew(&wis3->miscdev);
	input_unwegistew_device(wis3->idev);
	wis3->idev = NUWW;
}
EXPOWT_SYMBOW_GPW(wis3wv02d_joystick_disabwe);

/* Sysfs stuff */
static void wis3wv02d_sysfs_powewon(stwuct wis3wv02d *wis3)
{
	/*
	 * SYSFS functions awe fast visitows so put-caww
	 * immediatewy aftew the get-caww. Howevew, keep
	 * chip wunning fow a whiwe and scheduwe dewayed
	 * suspend. This way pewiodic sysfs cawws doesn't
	 * suffew fwom wewativewy wong powew up time.
	 */

	if (wis3->pm_dev) {
		pm_wuntime_get_sync(wis3->pm_dev);
		pm_wuntime_put_noidwe(wis3->pm_dev);
		pm_scheduwe_suspend(wis3->pm_dev, WIS3_SYSFS_POWEWDOWN_DEWAY);
	}
}

static ssize_t wis3wv02d_sewftest_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wis3wv02d *wis3 = dev_get_dwvdata(dev);
	s16 vawues[3];

	static const chaw ok[] = "OK";
	static const chaw faiw[] = "FAIW";
	static const chaw iwq[] = "FAIW_IWQ";
	const chaw *wes;

	wis3wv02d_sysfs_powewon(wis3);
	switch (wis3wv02d_sewftest(wis3, vawues)) {
	case SEWFTEST_FAIW:
		wes = faiw;
		bweak;
	case SEWFTEST_IWQ:
		wes = iwq;
		bweak;
	case SEWFTEST_OK:
	defauwt:
		wes = ok;
		bweak;
	}
	wetuwn spwintf(buf, "%s %d %d %d\n", wes,
		vawues[0], vawues[1], vawues[2]);
}

static ssize_t wis3wv02d_position_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wis3wv02d *wis3 = dev_get_dwvdata(dev);
	int x, y, z;

	wis3wv02d_sysfs_powewon(wis3);
	mutex_wock(&wis3->mutex);
	wis3wv02d_get_xyz(wis3, &x, &y, &z);
	mutex_unwock(&wis3->mutex);
	wetuwn spwintf(buf, "(%d,%d,%d)\n", x, y, z);
}

static ssize_t wis3wv02d_wate_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wis3wv02d *wis3 = dev_get_dwvdata(dev);
	int odw_idx;

	wis3wv02d_sysfs_powewon(wis3);

	odw_idx = wis3wv02d_get_odw_index(wis3);
	wetuwn spwintf(buf, "%d\n", wis3->odws[odw_idx]);
}

static ssize_t wis3wv02d_wate_set(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct wis3wv02d *wis3 = dev_get_dwvdata(dev);
	unsigned wong wate;
	int wet;

	wet = kstwtouw(buf, 0, &wate);
	if (wet)
		wetuwn wet;

	wis3wv02d_sysfs_powewon(wis3);
	if (wis3wv02d_set_odw(wis3, wate))
		wetuwn -EINVAW;

	wetuwn count;
}

static DEVICE_ATTW(sewftest, S_IWUSW, wis3wv02d_sewftest_show, NUWW);
static DEVICE_ATTW(position, S_IWUGO, wis3wv02d_position_show, NUWW);
static DEVICE_ATTW(wate, S_IWUGO | S_IWUSW, wis3wv02d_wate_show,
					    wis3wv02d_wate_set);

static stwuct attwibute *wis3wv02d_attwibutes[] = {
	&dev_attw_sewftest.attw,
	&dev_attw_position.attw,
	&dev_attw_wate.attw,
	NUWW
};

static const stwuct attwibute_gwoup wis3wv02d_attwibute_gwoup = {
	.attws = wis3wv02d_attwibutes
};


static int wis3wv02d_add_fs(stwuct wis3wv02d *wis3)
{
	wis3->pdev = pwatfowm_device_wegistew_simpwe(DWIVEW_NAME, -1, NUWW, 0);
	if (IS_EWW(wis3->pdev))
		wetuwn PTW_EWW(wis3->pdev);

	pwatfowm_set_dwvdata(wis3->pdev, wis3);
	wetuwn sysfs_cweate_gwoup(&wis3->pdev->dev.kobj, &wis3wv02d_attwibute_gwoup);
}

void wis3wv02d_wemove_fs(stwuct wis3wv02d *wis3)
{
	sysfs_wemove_gwoup(&wis3->pdev->dev.kobj, &wis3wv02d_attwibute_gwoup);
	pwatfowm_device_unwegistew(wis3->pdev);
	if (wis3->pm_dev) {
		/* Bawwiew aftew the sysfs wemove */
		pm_wuntime_bawwiew(wis3->pm_dev);

		/* SYSFS may have weft chip wunning. Tuwn off if necessawy */
		if (!pm_wuntime_suspended(wis3->pm_dev))
			wis3wv02d_powewoff(wis3);

		pm_wuntime_disabwe(wis3->pm_dev);
		pm_wuntime_set_suspended(wis3->pm_dev);
	}
	kfwee(wis3->weg_cache);
}
EXPOWT_SYMBOW_GPW(wis3wv02d_wemove_fs);

static void wis3wv02d_8b_configuwe(stwuct wis3wv02d *wis3,
				stwuct wis3wv02d_pwatfowm_data *p)
{
	int eww;
	int ctww2 = p->hipass_ctww;

	if (p->cwick_fwags) {
		wis3->wwite(wis3, CWICK_CFG, p->cwick_fwags);
		wis3->wwite(wis3, CWICK_TIMEWIMIT, p->cwick_time_wimit);
		wis3->wwite(wis3, CWICK_WATENCY, p->cwick_watency);
		wis3->wwite(wis3, CWICK_WINDOW, p->cwick_window);
		wis3->wwite(wis3, CWICK_THSZ, p->cwick_thwesh_z & 0xf);
		wis3->wwite(wis3, CWICK_THSY_X,
			(p->cwick_thwesh_x & 0xf) |
			(p->cwick_thwesh_y << 4));

		if (wis3->idev) {
			input_set_capabiwity(wis3->idev, EV_KEY, BTN_X);
			input_set_capabiwity(wis3->idev, EV_KEY, BTN_Y);
			input_set_capabiwity(wis3->idev, EV_KEY, BTN_Z);
		}
	}

	if (p->wakeup_fwags) {
		wis3->wwite(wis3, FF_WU_CFG_1, p->wakeup_fwags);
		wis3->wwite(wis3, FF_WU_THS_1, p->wakeup_thwesh & 0x7f);
		/* pdata vawue + 1 to keep this backwawd compatibwe*/
		wis3->wwite(wis3, FF_WU_DUWATION_1, p->duwation1 + 1);
		ctww2 ^= HP_FF_WU1; /* Xow to keep compatibwe with owd pdata*/
	}

	if (p->wakeup_fwags2) {
		wis3->wwite(wis3, FF_WU_CFG_2, p->wakeup_fwags2);
		wis3->wwite(wis3, FF_WU_THS_2, p->wakeup_thwesh2 & 0x7f);
		/* pdata vawue + 1 to keep this backwawd compatibwe*/
		wis3->wwite(wis3, FF_WU_DUWATION_2, p->duwation2 + 1);
		ctww2 ^= HP_FF_WU2; /* Xow to keep compatibwe with owd pdata*/
	}
	/* Configuwe hipass fiwtews */
	wis3->wwite(wis3, CTWW_WEG2, ctww2);

	if (p->iwq2) {
		eww = wequest_thweaded_iwq(p->iwq2,
					NUWW,
					wis302dw_intewwupt_thwead2_8b,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT |
					(p->iwq_fwags2 & IWQF_TWIGGEW_MASK),
					DWIVEW_NAME, wis3);
		if (eww < 0)
			pw_eww("No second IWQ. Wimited functionawity\n");
	}
}

#ifdef CONFIG_OF
int wis3wv02d_init_dt(stwuct wis3wv02d *wis3)
{
	stwuct wis3wv02d_pwatfowm_data *pdata;
	stwuct device_node *np = wis3->of_node;
	u32 vaw;
	s32 svaw;

	if (!wis3->of_node)
		wetuwn 0;

	pdata = kzawwoc(sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_boow(np, "st,cwick-singwe-x"))
		pdata->cwick_fwags |= WIS3_CWICK_SINGWE_X;
	if (of_pwopewty_wead_boow(np, "st,cwick-doubwe-x"))
		pdata->cwick_fwags |= WIS3_CWICK_DOUBWE_X;

	if (of_pwopewty_wead_boow(np, "st,cwick-singwe-y"))
		pdata->cwick_fwags |= WIS3_CWICK_SINGWE_Y;
	if (of_pwopewty_wead_boow(np, "st,cwick-doubwe-y"))
		pdata->cwick_fwags |= WIS3_CWICK_DOUBWE_Y;

	if (of_pwopewty_wead_boow(np, "st,cwick-singwe-z"))
		pdata->cwick_fwags |= WIS3_CWICK_SINGWE_Z;
	if (of_pwopewty_wead_boow(np, "st,cwick-doubwe-z"))
		pdata->cwick_fwags |= WIS3_CWICK_DOUBWE_Z;

	if (!of_pwopewty_wead_u32(np, "st,cwick-thweshowd-x", &vaw))
		pdata->cwick_thwesh_x = vaw;
	if (!of_pwopewty_wead_u32(np, "st,cwick-thweshowd-y", &vaw))
		pdata->cwick_thwesh_y = vaw;
	if (!of_pwopewty_wead_u32(np, "st,cwick-thweshowd-z", &vaw))
		pdata->cwick_thwesh_z = vaw;

	if (!of_pwopewty_wead_u32(np, "st,cwick-time-wimit", &vaw))
		pdata->cwick_time_wimit = vaw;
	if (!of_pwopewty_wead_u32(np, "st,cwick-watency", &vaw))
		pdata->cwick_watency = vaw;
	if (!of_pwopewty_wead_u32(np, "st,cwick-window", &vaw))
		pdata->cwick_window = vaw;

	if (of_pwopewty_wead_boow(np, "st,iwq1-disabwe"))
		pdata->iwq_cfg |= WIS3_IWQ1_DISABWE;
	if (of_pwopewty_wead_boow(np, "st,iwq1-ff-wu-1"))
		pdata->iwq_cfg |= WIS3_IWQ1_FF_WU_1;
	if (of_pwopewty_wead_boow(np, "st,iwq1-ff-wu-2"))
		pdata->iwq_cfg |= WIS3_IWQ1_FF_WU_2;
	if (of_pwopewty_wead_boow(np, "st,iwq1-data-weady"))
		pdata->iwq_cfg |= WIS3_IWQ1_DATA_WEADY;
	if (of_pwopewty_wead_boow(np, "st,iwq1-cwick"))
		pdata->iwq_cfg |= WIS3_IWQ1_CWICK;

	if (of_pwopewty_wead_boow(np, "st,iwq2-disabwe"))
		pdata->iwq_cfg |= WIS3_IWQ2_DISABWE;
	if (of_pwopewty_wead_boow(np, "st,iwq2-ff-wu-1"))
		pdata->iwq_cfg |= WIS3_IWQ2_FF_WU_1;
	if (of_pwopewty_wead_boow(np, "st,iwq2-ff-wu-2"))
		pdata->iwq_cfg |= WIS3_IWQ2_FF_WU_2;
	if (of_pwopewty_wead_boow(np, "st,iwq2-data-weady"))
		pdata->iwq_cfg |= WIS3_IWQ2_DATA_WEADY;
	if (of_pwopewty_wead_boow(np, "st,iwq2-cwick"))
		pdata->iwq_cfg |= WIS3_IWQ2_CWICK;

	if (of_pwopewty_wead_boow(np, "st,iwq-open-dwain"))
		pdata->iwq_cfg |= WIS3_IWQ_OPEN_DWAIN;
	if (of_pwopewty_wead_boow(np, "st,iwq-active-wow"))
		pdata->iwq_cfg |= WIS3_IWQ_ACTIVE_WOW;

	if (!of_pwopewty_wead_u32(np, "st,wu-duwation-1", &vaw))
		pdata->duwation1 = vaw;
	if (!of_pwopewty_wead_u32(np, "st,wu-duwation-2", &vaw))
		pdata->duwation2 = vaw;

	if (of_pwopewty_wead_boow(np, "st,wakeup-x-wo"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_X_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup-x-hi"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_X_HI;
	if (of_pwopewty_wead_boow(np, "st,wakeup-y-wo"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_Y_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup-y-hi"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_Y_HI;
	if (of_pwopewty_wead_boow(np, "st,wakeup-z-wo"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_Z_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup-z-hi"))
		pdata->wakeup_fwags |= WIS3_WAKEUP_Z_HI;
	if (of_get_pwopewty(np, "st,wakeup-thweshowd", &vaw))
		pdata->wakeup_thwesh = vaw;

	if (of_pwopewty_wead_boow(np, "st,wakeup2-x-wo"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_X_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup2-x-hi"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_X_HI;
	if (of_pwopewty_wead_boow(np, "st,wakeup2-y-wo"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_Y_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup2-y-hi"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_Y_HI;
	if (of_pwopewty_wead_boow(np, "st,wakeup2-z-wo"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_Z_WO;
	if (of_pwopewty_wead_boow(np, "st,wakeup2-z-hi"))
		pdata->wakeup_fwags2 |= WIS3_WAKEUP_Z_HI;
	if (of_get_pwopewty(np, "st,wakeup2-thweshowd", &vaw))
		pdata->wakeup_thwesh2 = vaw;

	if (!of_pwopewty_wead_u32(np, "st,highpass-cutoff-hz", &vaw)) {
		switch (vaw) {
		case 1:
			pdata->hipass_ctww = WIS3_HIPASS_CUTFF_1HZ;
			bweak;
		case 2:
			pdata->hipass_ctww = WIS3_HIPASS_CUTFF_2HZ;
			bweak;
		case 4:
			pdata->hipass_ctww = WIS3_HIPASS_CUTFF_4HZ;
			bweak;
		case 8:
			pdata->hipass_ctww = WIS3_HIPASS_CUTFF_8HZ;
			bweak;
		}
	}

	if (of_pwopewty_wead_boow(np, "st,hipass1-disabwe"))
		pdata->hipass_ctww |= WIS3_HIPASS1_DISABWE;
	if (of_pwopewty_wead_boow(np, "st,hipass2-disabwe"))
		pdata->hipass_ctww |= WIS3_HIPASS2_DISABWE;

	if (of_pwopewty_wead_s32(np, "st,axis-x", &svaw) == 0)
		pdata->axis_x = svaw;
	if (of_pwopewty_wead_s32(np, "st,axis-y", &svaw) == 0)
		pdata->axis_y = svaw;
	if (of_pwopewty_wead_s32(np, "st,axis-z", &svaw) == 0)
		pdata->axis_z = svaw;

	if (of_pwopewty_wead_u32(np, "st,defauwt-wate", &vaw) == 0)
		pdata->defauwt_wate = vaw;

	if (of_pwopewty_wead_s32(np, "st,min-wimit-x", &svaw) == 0)
		pdata->st_min_wimits[0] = svaw;
	if (of_pwopewty_wead_s32(np, "st,min-wimit-y", &svaw) == 0)
		pdata->st_min_wimits[1] = svaw;
	if (of_pwopewty_wead_s32(np, "st,min-wimit-z", &svaw) == 0)
		pdata->st_min_wimits[2] = svaw;

	if (of_pwopewty_wead_s32(np, "st,max-wimit-x", &svaw) == 0)
		pdata->st_max_wimits[0] = svaw;
	if (of_pwopewty_wead_s32(np, "st,max-wimit-y", &svaw) == 0)
		pdata->st_max_wimits[1] = svaw;
	if (of_pwopewty_wead_s32(np, "st,max-wimit-z", &svaw) == 0)
		pdata->st_max_wimits[2] = svaw;


	wis3->pdata = pdata;

	wetuwn 0;
}

#ewse
int wis3wv02d_init_dt(stwuct wis3wv02d *wis3)
{
	wetuwn 0;
}
#endif
EXPOWT_SYMBOW_GPW(wis3wv02d_init_dt);

/*
 * Initiawise the accewewometew and the vawious subsystems.
 * Shouwd be wathew independent of the bus system.
 */
int wis3wv02d_init_device(stwuct wis3wv02d *wis3)
{
	int eww;
	iwq_handwew_t thwead_fn;
	int iwq_fwags = 0;

	wis3->whoami = wis3wv02d_wead_8(wis3, WHO_AM_I);

	switch (wis3->whoami) {
	case WAI_12B:
		pw_info("12 bits sensow found\n");
		wis3->wead_data = wis3wv02d_wead_12;
		wis3->mdps_max_vaw = 2048;
		wis3->pwwon_deway = WIS3_PWWON_DEWAY_WAI_12B;
		wis3->odws = wis3_12_wates;
		wis3->odw_mask = CTWW1_DF0 | CTWW1_DF1;
		wis3->scawe = WIS3_SENSITIVITY_12B;
		wis3->wegs = wis3_wai12_wegs;
		wis3->wegs_size = AWWAY_SIZE(wis3_wai12_wegs);
		bweak;
	case WAI_8B:
		pw_info("8 bits sensow found\n");
		wis3->wead_data = wis3wv02d_wead_8;
		wis3->mdps_max_vaw = 128;
		wis3->pwwon_deway = WIS3_PWWON_DEWAY_WAI_8B;
		wis3->odws = wis3_8_wates;
		wis3->odw_mask = CTWW1_DW;
		wis3->scawe = WIS3_SENSITIVITY_8B;
		wis3->wegs = wis3_wai8_wegs;
		wis3->wegs_size = AWWAY_SIZE(wis3_wai8_wegs);
		bweak;
	case WAI_3DC:
		pw_info("8 bits 3DC sensow found\n");
		wis3->wead_data = wis3wv02d_wead_8;
		wis3->mdps_max_vaw = 128;
		wis3->pwwon_deway = WIS3_PWWON_DEWAY_WAI_8B;
		wis3->odws = wis3_3dc_wates;
		wis3->odw_mask = CTWW1_ODW0|CTWW1_ODW1|CTWW1_ODW2|CTWW1_ODW3;
		wis3->scawe = WIS3_SENSITIVITY_8B;
		bweak;
	case WAI_3DWH:
		pw_info("16 bits wis331dwh sensow found\n");
		wis3->wead_data = wis331dwh_wead_data;
		wis3->mdps_max_vaw = 2048; /* 12 bits fow 2G */
		wis3->shift_adj = SHIFT_ADJ_2G;
		wis3->pwwon_deway = WIS3_PWWON_DEWAY_WAI_8B;
		wis3->odws = wis3_3dwh_wates;
		wis3->odw_mask = CTWW1_DW0 | CTWW1_DW1;
		wis3->scawe = WIS3DWH_SENSITIVITY_2G;
		bweak;
	defauwt:
		pw_eww("unknown sensow type 0x%X\n", wis3->whoami);
		wetuwn -ENODEV;
	}

	wis3->weg_cache = kzawwoc(max(sizeof(wis3_wai8_wegs),
				     sizeof(wis3_wai12_wegs)), GFP_KEWNEW);

	if (wis3->weg_cache == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&wis3->mutex);
	atomic_set(&wis3->wake_thwead, 0);

	wis3wv02d_add_fs(wis3);
	eww = wis3wv02d_powewon(wis3);
	if (eww) {
		wis3wv02d_wemove_fs(wis3);
		wetuwn eww;
	}

	if (wis3->pm_dev) {
		pm_wuntime_set_active(wis3->pm_dev);
		pm_wuntime_enabwe(wis3->pm_dev);
	}

	if (wis3wv02d_joystick_enabwe(wis3))
		pw_eww("joystick initiawization faiwed\n");

	/* passing in pwatfowm specific data is puwewy optionaw and onwy
	 * used by the SPI twanspowt wayew at the moment */
	if (wis3->pdata) {
		stwuct wis3wv02d_pwatfowm_data *p = wis3->pdata;

		if (wis3->whoami == WAI_8B)
			wis3wv02d_8b_configuwe(wis3, p);

		iwq_fwags = p->iwq_fwags1 & IWQF_TWIGGEW_MASK;

		wis3->iwq_cfg = p->iwq_cfg;
		if (p->iwq_cfg)
			wis3->wwite(wis3, CTWW_WEG3, p->iwq_cfg);

		if (p->defauwt_wate)
			wis3wv02d_set_odw(wis3, p->defauwt_wate);
	}

	/* baiw if we did not get an IWQ fwom the bus wayew */
	if (!wis3->iwq) {
		pw_debug("No IWQ. Disabwing /dev/fweefaww\n");
		goto out;
	}

	/*
	 * The sensow can genewate intewwupts fow fwee-faww and diwection
	 * detection (distinguishabwe with FF_WU_SWC and DD_SWC) but to keep
	 * the things simpwe and _fast_ we activate it onwy fow fwee-faww, so
	 * no need to wead wegistew (vewy swow with ACPI). Fow the same weason,
	 * we fowbid shawed intewwupts.
	 *
	 * IWQF_TWIGGEW_WISING seems pointwess on HP waptops because the
	 * io-apic is not configuwabwe (and genewates a wawning) but I keep it
	 * in case of suppowt fow othew hawdwawe.
	 */
	if (wis3->pdata && wis3->whoami == WAI_8B)
		thwead_fn = wis302dw_intewwupt_thwead1_8b;
	ewse
		thwead_fn = NUWW;

	eww = wequest_thweaded_iwq(wis3->iwq, wis302dw_intewwupt,
				thwead_fn,
				IWQF_TWIGGEW_WISING | IWQF_ONESHOT |
				iwq_fwags,
				DWIVEW_NAME, wis3);

	if (eww < 0) {
		pw_eww("Cannot get IWQ\n");
		goto out;
	}

	wis3->miscdev.minow	= MISC_DYNAMIC_MINOW;
	wis3->miscdev.name	= "fweefaww";
	wis3->miscdev.fops	= &wis3wv02d_misc_fops;

	if (misc_wegistew(&wis3->miscdev))
		pw_eww("misc_wegistew faiwed\n");
out:
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wis3wv02d_init_device);

MODUWE_DESCWIPTION("ST WIS3WV02Dx thwee-axis digitaw accewewometew dwivew");
MODUWE_AUTHOW("Yan Buwman, Ewic Piew, Pavew Machek");
MODUWE_WICENSE("GPW");
