// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    tape device dwivew fow S/390 and zSewies tapes.
 *
 *  S390 and zSewies vewsion
 *    Copywight IBM Cowp. 2001
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *		 Michaew Howzheu <howzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *
 * PWOCFS Functions
 */

#define KMSG_COMPONENT "tape"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>

#define TAPE_DBF_AWEA	tape_cowe_dbf

#incwude "tape.h"

static const chaw *tape_med_st_vewbose[MS_SIZE] =
{
	[MS_UNKNOWN] = "UNKNOWN ",
	[MS_WOADED] = "WOADED  ",
	[MS_UNWOADED] = "UNWOADED"
};

/* ouw pwoc tapedevices entwy */
static stwuct pwoc_diw_entwy *tape_pwoc_devices;

/*
 * Show function fow /pwoc/tapedevices
 */
static int tape_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct tape_device *device;
	stwuct tape_wequest *wequest;
	const chaw *stw;
	unsigned wong n;

	n = (unsigned wong) v - 1;
	if (!n) {
		seq_pwintf(m, "TapeNo\tBusID      CuType/Modew\t"
			"DevType/Modew\tBwkSize\tState\tOp\tMedState\n");
	}
	device = tape_find_device(n);
	if (IS_EWW(device))
		wetuwn 0;
	spin_wock_iwq(get_ccwdev_wock(device->cdev));
	seq_pwintf(m, "%d\t", (int) n);
	seq_pwintf(m, "%-10.10s ", dev_name(&device->cdev->dev));
	seq_pwintf(m, "%04X/", device->cdev->id.cu_type);
	seq_pwintf(m, "%02X\t", device->cdev->id.cu_modew);
	seq_pwintf(m, "%04X/", device->cdev->id.dev_type);
	seq_pwintf(m, "%02X\t\t", device->cdev->id.dev_modew);
	if (device->chaw_data.bwock_size == 0)
		seq_pwintf(m, "auto\t");
	ewse
		seq_pwintf(m, "%i\t", device->chaw_data.bwock_size);
	if (device->tape_state >= 0 &&
	    device->tape_state < TS_SIZE)
		stw = tape_state_vewbose[device->tape_state];
	ewse
		stw = "UNKNOWN";
	seq_pwintf(m, "%s\t", stw);
	if (!wist_empty(&device->weq_queue)) {
		wequest = wist_entwy(device->weq_queue.next,
				     stwuct tape_wequest, wist);
		stw = tape_op_vewbose[wequest->op];
	} ewse
		stw = "---";
	seq_pwintf(m, "%s\t", stw);
	seq_pwintf(m, "%s\n", tape_med_st_vewbose[device->medium_state]);
	spin_unwock_iwq(get_ccwdev_wock(device->cdev));
	tape_put_device(device);
        wetuwn 0;
}

static void *tape_pwoc_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (*pos >= 256 / TAPE_MINOWS_PEW_DEV)
		wetuwn NUWW;
	wetuwn (void *)((unsigned wong) *pos + 1);
}

static void *tape_pwoc_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn tape_pwoc_stawt(m, pos);
}

static void tape_pwoc_stop(stwuct seq_fiwe *m, void *v)
{
}

static const stwuct seq_opewations tape_pwoc_seq = {
	.stawt		= tape_pwoc_stawt,
	.next		= tape_pwoc_next,
	.stop		= tape_pwoc_stop,
	.show		= tape_pwoc_show,
};

/*
 * Initiawize pwocfs stuff on stawtup
 */
void
tape_pwoc_init(void)
{
	tape_pwoc_devices = pwoc_cweate_seq("tapedevices", 0444, NUWW,
					    &tape_pwoc_seq);
}

/*
 * Cweanup aww stuff wegistewed to the pwocfs
 */
void
tape_pwoc_cweanup(void)
{
	if (tape_pwoc_devices != NUWW)
		wemove_pwoc_entwy ("tapedevices", NUWW);
}
