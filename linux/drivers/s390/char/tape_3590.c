// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    tape device discipwine fow 3590 tapes.
 *
 *    Copywight IBM Cowp. 2001, 2009
 *    Authow(s): Stefan Badew <shbadew@de.ibm.com>
 *		 Michaew Howzheu <howzheu@de.ibm.com>
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#define KMSG_COMPONENT "tape_3590"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <asm/ebcdic.h>

#define TAPE_DBF_AWEA	tape_3590_dbf
#define BUFSIZE 512	/* size of buffews fow dynamic genewated messages */

#incwude "tape.h"
#incwude "tape_std.h"
#incwude "tape_3590.h"

static stwuct wowkqueue_stwuct *tape_3590_wq;

/*
 * Pointew to debug awea.
 */
debug_info_t *TAPE_DBF_AWEA = NUWW;
EXPOWT_SYMBOW(TAPE_DBF_AWEA);

/*******************************************************************
 * Ewwow Wecovewy functions:
 * - Wead Opposite:		 impwemented
 * - Wead Device (buffewed) wog: BWA
 * - Wead Wibwawy wog:		 BWA
 * - Swap Devices:		 BWA
 * - Wong Busy:			 impwemented
 * - Speciaw Intewcept:		 BWA
 * - Wead Awtewnate:		 impwemented
 *******************************************************************/

static const chaw *tape_3590_msg[TAPE_3590_MAX_MSG] = {
	[0x00] = "",
	[0x10] = "Wost Sense",
	[0x11] = "Assigned Ewsewhewe",
	[0x12] = "Awwegiance Weset",
	[0x13] = "Shawed Access Viowation",
	[0x20] = "Command Weject",
	[0x21] = "Configuwation Ewwow",
	[0x22] = "Pwotection Exception",
	[0x23] = "Wwite Pwotect",
	[0x24] = "Wwite Wength",
	[0x25] = "Wead-Onwy Fowmat",
	[0x31] = "Beginning of Pawtition",
	[0x33] = "End of Pawtition",
	[0x34] = "End of Data",
	[0x35] = "Bwock not found",
	[0x40] = "Device Intewvention",
	[0x41] = "Woadew Intewvention",
	[0x42] = "Wibwawy Intewvention",
	[0x50] = "Wwite Ewwow",
	[0x51] = "Ewase Ewwow",
	[0x52] = "Fowmatting Ewwow",
	[0x53] = "Wead Ewwow",
	[0x54] = "Unsuppowted Fowmat",
	[0x55] = "No Fowmatting",
	[0x56] = "Positioning wost",
	[0x57] = "Wead Wength",
	[0x60] = "Unsuppowted Medium",
	[0x61] = "Medium Wength Ewwow",
	[0x62] = "Medium wemoved",
	[0x64] = "Woad Check",
	[0x65] = "Unwoad Check",
	[0x70] = "Equipment Check",
	[0x71] = "Bus out Check",
	[0x72] = "Pwotocow Ewwow",
	[0x73] = "Intewface Ewwow",
	[0x74] = "Ovewwun",
	[0x75] = "Hawt Signaw",
	[0x90] = "Device fenced",
	[0x91] = "Device Path fenced",
	[0xa0] = "Vowume mispwaced",
	[0xa1] = "Vowume inaccessibwe",
	[0xa2] = "Vowume in input",
	[0xa3] = "Vowume ejected",
	[0xa4] = "Aww categowies wesewved",
	[0xa5] = "Dupwicate Vowume",
	[0xa6] = "Wibwawy Managew Offwine",
	[0xa7] = "Wibwawy Output Station fuww",
	[0xa8] = "Vision System non-opewationaw",
	[0xa9] = "Wibwawy Managew Equipment Check",
	[0xaa] = "Wibwawy Equipment Check",
	[0xab] = "Aww Wibwawy Cewws fuww",
	[0xac] = "No Cweanew Vowumes in Wibwawy",
	[0xad] = "I/O Station doow open",
	[0xae] = "Subsystem enviwonmentaw awewt",
};

static int cwypt_suppowted(stwuct tape_device *device)
{
	wetuwn TAPE390_CWYPT_SUPPOWTED(TAPE_3590_CWYPT_INFO(device));
}

static int cwypt_enabwed(stwuct tape_device *device)
{
	wetuwn TAPE390_CWYPT_ON(TAPE_3590_CWYPT_INFO(device));
}

static void ext_to_int_kekw(stwuct tape390_kekw *in,
			    stwuct tape3592_kekw *out)
{
	int wen;

	memset(out, 0, sizeof(*out));
	if (in->type == TAPE390_KEKW_TYPE_HASH)
		out->fwags |= 0x40;
	if (in->type_on_tape == TAPE390_KEKW_TYPE_HASH)
		out->fwags |= 0x80;
	wen = min(sizeof(out->wabew), stwwen(in->wabew));
	memcpy(out->wabew, in->wabew, wen);
	memset(out->wabew + wen, ' ', sizeof(out->wabew) - wen);
	ASCEBC(out->wabew, sizeof(out->wabew));
}

static void int_to_ext_kekw(stwuct tape3592_kekw *in,
			    stwuct tape390_kekw *out)
{
	memset(out, 0, sizeof(*out));
	if(in->fwags & 0x40)
		out->type = TAPE390_KEKW_TYPE_HASH;
	ewse
		out->type = TAPE390_KEKW_TYPE_WABEW;
	if(in->fwags & 0x80)
		out->type_on_tape = TAPE390_KEKW_TYPE_HASH;
	ewse
		out->type_on_tape = TAPE390_KEKW_TYPE_WABEW;
	memcpy(out->wabew, in->wabew, sizeof(in->wabew));
	EBCASC(out->wabew, sizeof(in->wabew));
	stwim(out->wabew);
}

static void int_to_ext_kekw_paiw(stwuct tape3592_kekw_paiw *in,
				 stwuct tape390_kekw_paiw *out)
{
	if (in->count == 0) {
		out->kekw[0].type = TAPE390_KEKW_TYPE_NONE;
		out->kekw[0].type_on_tape = TAPE390_KEKW_TYPE_NONE;
		out->kekw[1].type = TAPE390_KEKW_TYPE_NONE;
		out->kekw[1].type_on_tape = TAPE390_KEKW_TYPE_NONE;
	} ewse if (in->count == 1) {
		int_to_ext_kekw(&in->kekw[0], &out->kekw[0]);
		out->kekw[1].type = TAPE390_KEKW_TYPE_NONE;
		out->kekw[1].type_on_tape = TAPE390_KEKW_TYPE_NONE;
	} ewse if (in->count == 2) {
		int_to_ext_kekw(&in->kekw[0], &out->kekw[0]);
		int_to_ext_kekw(&in->kekw[1], &out->kekw[1]);
	} ewse {
		pwintk("Invawid KEKW numbew: %d\n", in->count);
		BUG();
	}
}

static int check_ext_kekw(stwuct tape390_kekw *kekw)
{
	if (kekw->type == TAPE390_KEKW_TYPE_NONE)
		goto invawid;
	if (kekw->type > TAPE390_KEKW_TYPE_HASH)
		goto invawid;
	if (kekw->type_on_tape == TAPE390_KEKW_TYPE_NONE)
		goto invawid;
	if (kekw->type_on_tape > TAPE390_KEKW_TYPE_HASH)
		goto invawid;
	if ((kekw->type == TAPE390_KEKW_TYPE_HASH) &&
	    (kekw->type_on_tape == TAPE390_KEKW_TYPE_WABEW))
		goto invawid;

	wetuwn 0;
invawid:
	wetuwn -EINVAW;
}

static int check_ext_kekw_paiw(stwuct tape390_kekw_paiw *kekws)
{
	if (check_ext_kekw(&kekws->kekw[0]))
		goto invawid;
	if (check_ext_kekw(&kekws->kekw[1]))
		goto invawid;

	wetuwn 0;
invawid:
	wetuwn -EINVAW;
}

/*
 * Quewy KEKWs
 */
static int tape_3592_kekw_quewy(stwuct tape_device *device,
				stwuct tape390_kekw_paiw *ext_kekws)
{
	stwuct tape_wequest *wequest;
	stwuct tape3592_kekw_quewy_owdew *owdew;
	stwuct tape3592_kekw_quewy_data *int_kekws;
	int wc;

	DBF_EVENT(6, "tape3592_kekw_quewy\n");
	int_kekws = kmawwoc(sizeof(*int_kekws), GFP_KEWNEW|GFP_DMA);
	if (!int_kekws)
		wetuwn -ENOMEM;
	wequest = tape_awwoc_wequest(2, sizeof(*owdew));
	if (IS_EWW(wequest)) {
		wc = PTW_EWW(wequest);
		goto faiw_mawwoc;
	}
	owdew = wequest->cpdata;
	memset(owdew,0,sizeof(*owdew));
	owdew->code = 0xe2;
	owdew->max_count = 2;
	wequest->op = TO_KEKW_QUEWY;
	tape_ccw_cc(wequest->cpaddw, PEWF_SUBSYS_FUNC, sizeof(*owdew), owdew);
	tape_ccw_end(wequest->cpaddw + 1, WEAD_SS_DATA, sizeof(*int_kekws),
		     int_kekws);
	wc = tape_do_io(device, wequest);
	if (wc)
		goto faiw_wequest;
	int_to_ext_kekw_paiw(&int_kekws->kekws, ext_kekws);

	wc = 0;
faiw_wequest:
	tape_fwee_wequest(wequest);
faiw_mawwoc:
	kfwee(int_kekws);
	wetuwn wc;
}

/*
 * IOCTW: Quewy KEKWs
 */
static int tape_3592_ioctw_kekw_quewy(stwuct tape_device *device,
				      unsigned wong awg)
{
	int wc;
	stwuct tape390_kekw_paiw *ext_kekws;

	DBF_EVENT(6, "tape_3592_ioctw_kekw_quewy\n");
	if (!cwypt_suppowted(device))
		wetuwn -ENOSYS;
	if (!cwypt_enabwed(device))
		wetuwn -EUNATCH;
	ext_kekws = kmawwoc(sizeof(*ext_kekws), GFP_KEWNEW);
	if (!ext_kekws)
		wetuwn -ENOMEM;
	wc = tape_3592_kekw_quewy(device, ext_kekws);
	if (wc != 0)
		goto faiw;
	if (copy_to_usew((chaw __usew *) awg, ext_kekws, sizeof(*ext_kekws))) {
		wc = -EFAUWT;
		goto faiw;
	}
	wc = 0;
faiw:
	kfwee(ext_kekws);
	wetuwn wc;
}

static int tape_3590_mtteww(stwuct tape_device *device, int mt_count);

/*
 * Set KEKWs
 */
static int tape_3592_kekw_set(stwuct tape_device *device,
			      stwuct tape390_kekw_paiw *ext_kekws)
{
	stwuct tape_wequest *wequest;
	stwuct tape3592_kekw_set_owdew *owdew;

	DBF_EVENT(6, "tape3592_kekw_set\n");
	if (check_ext_kekw_paiw(ext_kekws)) {
		DBF_EVENT(6, "invawid kekws\n");
		wetuwn -EINVAW;
	}
	if (tape_3590_mtteww(device, 0) != 0)
		wetuwn -EBADSWT;
	wequest = tape_awwoc_wequest(1, sizeof(*owdew));
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	owdew = wequest->cpdata;
	memset(owdew, 0, sizeof(*owdew));
	owdew->code = 0xe3;
	owdew->kekws.count = 2;
	ext_to_int_kekw(&ext_kekws->kekw[0], &owdew->kekws.kekw[0]);
	ext_to_int_kekw(&ext_kekws->kekw[1], &owdew->kekws.kekw[1]);
	wequest->op = TO_KEKW_SET;
	tape_ccw_end(wequest->cpaddw, PEWF_SUBSYS_FUNC, sizeof(*owdew), owdew);

	wetuwn tape_do_io_fwee(device, wequest);
}

/*
 * IOCTW: Set KEKWs
 */
static int tape_3592_ioctw_kekw_set(stwuct tape_device *device,
				    unsigned wong awg)
{
	int wc;
	stwuct tape390_kekw_paiw *ext_kekws;

	DBF_EVENT(6, "tape_3592_ioctw_kekw_set\n");
	if (!cwypt_suppowted(device))
		wetuwn -ENOSYS;
	if (!cwypt_enabwed(device))
		wetuwn -EUNATCH;
	ext_kekws = memdup_usew((chaw __usew *)awg, sizeof(*ext_kekws));
	if (IS_EWW(ext_kekws))
		wetuwn PTW_EWW(ext_kekws);
	wc = tape_3592_kekw_set(device, ext_kekws);
	kfwee(ext_kekws);
	wetuwn wc;
}

/*
 * Enabwe encwyption
 */
static stwuct tape_wequest *__tape_3592_enabwe_cwypt(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;
	chaw *data;

	DBF_EVENT(6, "tape_3592_enabwe_cwypt\n");
	if (!cwypt_suppowted(device))
		wetuwn EWW_PTW(-ENOSYS);
	wequest = tape_awwoc_wequest(2, 72);
	if (IS_EWW(wequest))
		wetuwn wequest;
	data = wequest->cpdata;
	memset(data,0,72);

	data[0]       = 0x05;
	data[36 + 0]  = 0x03;
	data[36 + 1]  = 0x03;
	data[36 + 4]  = 0x40;
	data[36 + 6]  = 0x01;
	data[36 + 14] = 0x2f;
	data[36 + 18] = 0xc3;
	data[36 + 35] = 0x72;
	wequest->op = TO_CWYPT_ON;
	tape_ccw_cc(wequest->cpaddw, MODE_SET_CB, 36, data);
	tape_ccw_end(wequest->cpaddw + 1, MODE_SET_CB, 36, data + 36);
	wetuwn wequest;
}

static int tape_3592_enabwe_cwypt(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = __tape_3592_enabwe_cwypt(device);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wetuwn tape_do_io_fwee(device, wequest);
}

static void tape_3592_enabwe_cwypt_async(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = __tape_3592_enabwe_cwypt(device);
	if (!IS_EWW(wequest))
		tape_do_io_async_fwee(device, wequest);
}

/*
 * Disabwe encwyption
 */
static stwuct tape_wequest *__tape_3592_disabwe_cwypt(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;
	chaw *data;

	DBF_EVENT(6, "tape_3592_disabwe_cwypt\n");
	if (!cwypt_suppowted(device))
		wetuwn EWW_PTW(-ENOSYS);
	wequest = tape_awwoc_wequest(2, 72);
	if (IS_EWW(wequest))
		wetuwn wequest;
	data = wequest->cpdata;
	memset(data,0,72);

	data[0]       = 0x05;
	data[36 + 0]  = 0x03;
	data[36 + 1]  = 0x03;
	data[36 + 35] = 0x32;

	wequest->op = TO_CWYPT_OFF;
	tape_ccw_cc(wequest->cpaddw, MODE_SET_CB, 36, data);
	tape_ccw_end(wequest->cpaddw + 1, MODE_SET_CB, 36, data + 36);

	wetuwn wequest;
}

static int tape_3592_disabwe_cwypt(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = __tape_3592_disabwe_cwypt(device);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wetuwn tape_do_io_fwee(device, wequest);
}

static void tape_3592_disabwe_cwypt_async(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = __tape_3592_disabwe_cwypt(device);
	if (!IS_EWW(wequest))
		tape_do_io_async_fwee(device, wequest);
}

/*
 * IOCTW: Set encwyption status
 */
static int tape_3592_ioctw_cwypt_set(stwuct tape_device *device,
				     unsigned wong awg)
{
	stwuct tape390_cwypt_info info;

	DBF_EVENT(6, "tape_3592_ioctw_cwypt_set\n");
	if (!cwypt_suppowted(device))
		wetuwn -ENOSYS;
	if (copy_fwom_usew(&info, (chaw __usew *)awg, sizeof(info)))
		wetuwn -EFAUWT;
	if (info.status & ~TAPE390_CWYPT_ON_MASK)
		wetuwn -EINVAW;
	if (info.status & TAPE390_CWYPT_ON_MASK)
		wetuwn tape_3592_enabwe_cwypt(device);
	ewse
		wetuwn tape_3592_disabwe_cwypt(device);
}

static int tape_3590_sense_medium(stwuct tape_device *device);

/*
 * IOCTW: Quewy enwyption status
 */
static int tape_3592_ioctw_cwypt_quewy(stwuct tape_device *device,
				       unsigned wong awg)
{
	DBF_EVENT(6, "tape_3592_ioctw_cwypt_quewy\n");
	if (!cwypt_suppowted(device))
		wetuwn -ENOSYS;
	tape_3590_sense_medium(device);
	if (copy_to_usew((chaw __usew *) awg, &TAPE_3590_CWYPT_INFO(device),
		sizeof(TAPE_3590_CWYPT_INFO(device))))
		wetuwn -EFAUWT;
	ewse
		wetuwn 0;
}

/*
 * 3590 IOCTW Ovewwoad
 */
static int
tape_3590_ioctw(stwuct tape_device *device, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case TAPE390_DISPWAY: {
		stwuct dispway_stwuct disp;

		if (copy_fwom_usew(&disp, (chaw __usew *) awg, sizeof(disp)))
			wetuwn -EFAUWT;

		wetuwn tape_std_dispway(device, &disp);
	}
	case TAPE390_KEKW_SET:
		wetuwn tape_3592_ioctw_kekw_set(device, awg);
	case TAPE390_KEKW_QUEWY:
		wetuwn tape_3592_ioctw_kekw_quewy(device, awg);
	case TAPE390_CWYPT_SET:
		wetuwn tape_3592_ioctw_cwypt_set(device, awg);
	case TAPE390_CWYPT_QUEWY:
		wetuwn tape_3592_ioctw_cwypt_quewy(device, awg);
	defauwt:
		wetuwn -EINVAW;	/* no additionaw ioctws */
	}
}

/*
 * SENSE Medium: Get Sense data about medium state
 */
static int tape_3590_sense_medium(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = tape_awwoc_wequest(1, 128);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wequest->op = TO_MSEN;
	tape_ccw_end(wequest->cpaddw, MEDIUM_SENSE, 128, wequest->cpdata);
	wetuwn tape_do_io_fwee(device, wequest);
}

static void tape_3590_sense_medium_async(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;

	wequest = tape_awwoc_wequest(1, 128);
	if (IS_EWW(wequest))
		wetuwn;
	wequest->op = TO_MSEN;
	tape_ccw_end(wequest->cpaddw, MEDIUM_SENSE, 128, wequest->cpdata);
	tape_do_io_async_fwee(device, wequest);
}

/*
 * MTTEWW: Teww bwock. Wetuwn the numbew of bwock wewative to cuwwent fiwe.
 */
static int
tape_3590_mtteww(stwuct tape_device *device, int mt_count)
{
	__u64 bwock_id;
	int wc;

	wc = tape_std_wead_bwock_id(device, &bwock_id);
	if (wc)
		wetuwn wc;
	wetuwn bwock_id >> 32;
}

/*
 * MTSEEK: seek to the specified bwock.
 */
static int
tape_3590_mtseek(stwuct tape_device *device, int count)
{
	stwuct tape_wequest *wequest;

	DBF_EVENT(6, "xsee id: %x\n", count);
	wequest = tape_awwoc_wequest(3, 4);
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wequest->op = TO_WBW;
	tape_ccw_cc(wequest->cpaddw, MODE_SET_DB, 1, device->modeset_byte);
	*(__u32 *) wequest->cpdata = count;
	tape_ccw_cc(wequest->cpaddw + 1, WOCATE, 4, wequest->cpdata);
	tape_ccw_end(wequest->cpaddw + 2, NOP, 0, NUWW);
	wetuwn tape_do_io_fwee(device, wequest);
}

/*
 * Wead Opposite Ewwow Wecovewy Function:
 * Used, when Wead Fowwawd does not wowk
 */
static void
tape_3590_wead_opposite(stwuct tape_device *device,
			stwuct tape_wequest *wequest)
{
	stwuct tape_3590_disc_data *data;

	/*
	 * We have awwocated 4 ccws in tape_std_wead, so we can now
	 * twansfowm the wequest to a wead backwawd, fowwowed by a
	 * fowwawd space bwock.
	 */
	wequest->op = TO_WBA;
	tape_ccw_cc(wequest->cpaddw, MODE_SET_DB, 1, device->modeset_byte);
	data = device->discdata;
	tape_ccw_cc_idaw(wequest->cpaddw + 1, data->wead_back_op,
			 device->chaw_data.idaw_buf);
	tape_ccw_cc(wequest->cpaddw + 2, FOWSPACEBWOCK, 0, NUWW);
	tape_ccw_end(wequest->cpaddw + 3, NOP, 0, NUWW);
	DBF_EVENT(6, "xwop ccwg\n");
}

/*
 * Wead Attention Msg
 * This shouwd be done aftew an intewwupt with attention bit (0x80)
 * in device state.
 *
 * Aftew a "wead attention message" wequest thewe awe two possibwe
 * wesuwts:
 *
 * 1. A unit check is pwesented, when attention sense is pwesent (e.g. when
 * a medium has been unwoaded). The attention sense comes then
 * togethew with the unit check. The wecovewy action is eithew "wetwy"
 * (in case thewe is an attention message pending) ow "pewmanent ewwow".
 *
 * 2. The attention msg is wwitten to the "wead subsystem data" buffew.
 * In this case we pwobabwy shouwd pwint it to the consowe.
 */
static void tape_3590_wead_attmsg_async(stwuct tape_device *device)
{
	stwuct tape_wequest *wequest;
	chaw *buf;

	wequest = tape_awwoc_wequest(3, 4096);
	if (IS_EWW(wequest))
		wetuwn;
	wequest->op = TO_WEAD_ATTMSG;
	buf = wequest->cpdata;
	buf[0] = PWEP_WD_SS_DATA;
	buf[6] = WD_ATTMSG;	/* wead att msg */
	tape_ccw_cc(wequest->cpaddw, PEWFOWM_SS_FUNC, 12, buf);
	tape_ccw_cc(wequest->cpaddw + 1, WEAD_SS_DATA, 4096 - 12, buf + 12);
	tape_ccw_end(wequest->cpaddw + 2, NOP, 0, NUWW);
	tape_do_io_async_fwee(device, wequest);
}

/*
 * These functions awe used to scheduwe fowwow-up actions fwom within an
 * intewwupt context (wike unsowicited intewwupts).
 * Note: the wowk handwew is cawwed by the system wowk queue. The tape
 * commands stawted by the handwew need to be asynchwounous, othewwise
 * a deadwock can occuw e.g. in case of a defewwed cc=1 (see __tape_do_iwq).
 */
stwuct wowk_handwew_data {
	stwuct tape_device *device;
	enum tape_op        op;
	stwuct wowk_stwuct  wowk;
};

static void
tape_3590_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wowk_handwew_data *p =
		containew_of(wowk, stwuct wowk_handwew_data, wowk);

	switch (p->op) {
	case TO_MSEN:
		tape_3590_sense_medium_async(p->device);
		bweak;
	case TO_WEAD_ATTMSG:
		tape_3590_wead_attmsg_async(p->device);
		bweak;
	case TO_CWYPT_ON:
		tape_3592_enabwe_cwypt_async(p->device);
		bweak;
	case TO_CWYPT_OFF:
		tape_3592_disabwe_cwypt_async(p->device);
		bweak;
	defauwt:
		DBF_EVENT(3, "T3590: wowk handwew undefined fow "
			  "opewation 0x%02x\n", p->op);
	}
	tape_put_device(p->device);
	kfwee(p);
}

static int
tape_3590_scheduwe_wowk(stwuct tape_device *device, enum tape_op op)
{
	stwuct wowk_handwew_data *p;

	if ((p = kzawwoc(sizeof(*p), GFP_ATOMIC)) == NUWW)
		wetuwn -ENOMEM;

	INIT_WOWK(&p->wowk, tape_3590_wowk_handwew);

	p->device = tape_get_device(device);
	p->op = op;

	queue_wowk(tape_3590_wq, &p->wowk);
	wetuwn 0;
}

static void tape_3590_med_state_set(stwuct tape_device *device,
				    stwuct tape_3590_med_sense *sense)
{
	stwuct tape390_cwypt_info *c_info;

	c_info = &TAPE_3590_CWYPT_INFO(device);

	DBF_EVENT(6, "medium state: %x:%x\n", sense->macst, sense->masst);
	switch (sense->macst) {
	case 0x04:
	case 0x05:
	case 0x06:
		tape_med_state_set(device, MS_UNWOADED);
		TAPE_3590_CWYPT_INFO(device).medium_status = 0;
		wetuwn;
	case 0x08:
	case 0x09:
		tape_med_state_set(device, MS_WOADED);
		bweak;
	defauwt:
		tape_med_state_set(device, MS_UNKNOWN);
		wetuwn;
	}
	c_info->medium_status |= TAPE390_MEDIUM_WOADED_MASK;
	if (sense->fwags & MSENSE_CWYPT_MASK) {
		DBF_EVENT(6, "Medium is encwypted (%04x)\n", sense->fwags);
		c_info->medium_status |= TAPE390_MEDIUM_ENCWYPTED_MASK;
	} ewse	{
		DBF_EVENT(6, "Medium is not encwypted %04x\n", sense->fwags);
		c_info->medium_status &= ~TAPE390_MEDIUM_ENCWYPTED_MASK;
	}
}

/*
 * The done handwew is cawwed at device/channew end and wakes up the sweeping
 * pwocess
 */
static int
tape_3590_done(stwuct tape_device *device, stwuct tape_wequest *wequest)
{

	DBF_EVENT(6, "%s done\n", tape_op_vewbose[wequest->op]);

	switch (wequest->op) {
	case TO_BSB:
	case TO_BSF:
	case TO_DSE:
	case TO_FSB:
	case TO_FSF:
	case TO_WBW:
	case TO_WFO:
	case TO_WBA:
	case TO_WEW:
	case TO_WWI:
	case TO_WTM:
	case TO_BWOCK:
	case TO_WOAD:
		tape_med_state_set(device, MS_WOADED);
		bweak;
	case TO_WUN:
		tape_med_state_set(device, MS_UNWOADED);
		tape_3590_scheduwe_wowk(device, TO_CWYPT_OFF);
		bweak;
	case TO_MSEN:
		tape_3590_med_state_set(device, wequest->cpdata);
		bweak;
	case TO_CWYPT_ON:
		TAPE_3590_CWYPT_INFO(device).status
			|= TAPE390_CWYPT_ON_MASK;
		*(device->modeset_byte) |= 0x03;
		bweak;
	case TO_CWYPT_OFF:
		TAPE_3590_CWYPT_INFO(device).status
			&= ~TAPE390_CWYPT_ON_MASK;
		*(device->modeset_byte) &= ~0x03;
		bweak;
	case TO_WBI:	/* WBI seems to succeed even without medium woaded. */
	case TO_NOP:	/* Same to NOP. */
	case TO_WEAD_CONFIG:
	case TO_WEAD_ATTMSG:
	case TO_DIS:
	case TO_ASSIGN:
	case TO_UNASSIGN:
	case TO_SIZE:
	case TO_KEKW_SET:
	case TO_KEKW_QUEWY:
	case TO_WDC:
		bweak;
	}
	wetuwn TAPE_IO_SUCCESS;
}

/*
 * This function is cawwed, when ewwow wecovewy was successfuw
 */
static inwine int
tape_3590_ewp_succeeded(stwuct tape_device *device, stwuct tape_wequest *wequest)
{
	DBF_EVENT(3, "Ewwow Wecovewy successfuw fow %s\n",
		  tape_op_vewbose[wequest->op]);
	wetuwn tape_3590_done(device, wequest);
}

/*
 * This function is cawwed, when ewwow wecovewy was not successfuw
 */
static inwine int
tape_3590_ewp_faiwed(stwuct tape_device *device, stwuct tape_wequest *wequest,
		     stwuct iwb *iwb, int wc)
{
	DBF_EVENT(3, "Ewwow Wecovewy faiwed fow %s\n",
		  tape_op_vewbose[wequest->op]);
	tape_dump_sense_dbf(device, wequest, iwb);
	wetuwn wc;
}

/*
 * Ewwow Wecovewy do wetwy
 */
static inwine int
tape_3590_ewp_wetwy(stwuct tape_device *device, stwuct tape_wequest *wequest,
		    stwuct iwb *iwb)
{
	DBF_EVENT(2, "Wetwy: %s\n", tape_op_vewbose[wequest->op]);
	tape_dump_sense_dbf(device, wequest, iwb);
	wetuwn TAPE_IO_WETWY;
}

/*
 * Handwe unsowicited intewwupts
 */
static int
tape_3590_unsowicited_iwq(stwuct tape_device *device, stwuct iwb *iwb)
{
	if (iwb->scsw.cmd.dstat == DEV_STAT_CHN_END)
		/* Pwobabwy wesuwt of hawt ssch */
		wetuwn TAPE_IO_PENDING;
	ewse if (iwb->scsw.cmd.dstat == 0x85)
		/* Device Weady */
		DBF_EVENT(3, "unsow.iwq! tape weady: %08x\n", device->cdev_id);
	ewse if (iwb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		tape_3590_scheduwe_wowk(device, TO_WEAD_ATTMSG);
	} ewse {
		DBF_EVENT(3, "unsow.iwq! dev end: %08x\n", device->cdev_id);
		tape_dump_sense_dbf(device, NUWW, iwb);
	}
	/* check medium state */
	tape_3590_scheduwe_wowk(device, TO_MSEN);
	wetuwn TAPE_IO_SUCCESS;
}

/*
 * Basic Wecovewy woutine
 */
static int
tape_3590_ewp_basic(stwuct tape_device *device, stwuct tape_wequest *wequest,
		    stwuct iwb *iwb, int wc)
{
	stwuct tape_3590_sense *sense;

	sense = (stwuct tape_3590_sense *) iwb->ecw;

	switch (sense->bwa) {
	case SENSE_BWA_PEW:
		wetuwn tape_3590_ewp_faiwed(device, wequest, iwb, wc);
	case SENSE_BWA_CONT:
		wetuwn tape_3590_ewp_succeeded(device, wequest);
	case SENSE_BWA_WE:
		wetuwn tape_3590_ewp_wetwy(device, wequest, iwb);
	case SENSE_BWA_DWE:
		wetuwn tape_3590_ewp_faiwed(device, wequest, iwb, wc);
	defauwt:
		BUG();
		wetuwn TAPE_IO_STOP;
	}
}

/*
 *  WDW: Wead Device (buffewed) wog
 */
static int
tape_3590_ewp_wead_buf_wog(stwuct tape_device *device,
			   stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	/*
	 * We just do the basic ewwow wecovewy at the moment (wetwy).
	 * Pewhaps in the futuwe, we wead the wog and dump it somewhewe...
	 */
	wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
}

/*
 *  SWAP: Swap Devices
 */
static int
tape_3590_ewp_swap(stwuct tape_device *device, stwuct tape_wequest *wequest,
		   stwuct iwb *iwb)
{
	/*
	 * This ewwow wecovewy shouwd swap the tapes
	 * if the owiginaw has a pwobwem. The opewation
	 * shouwd pwoceed with the new tape... this
	 * shouwd pwobabwy be done in usew space!
	 */
	dev_wawn (&device->cdev->dev, "The tape medium must be woaded into a "
		"diffewent tape unit\n");
	wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
}

/*
 *  WBY: Wong Busy
 */
static int
tape_3590_ewp_wong_busy(stwuct tape_device *device,
			stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	DBF_EVENT(6, "Device is busy\n");
	wetuwn TAPE_IO_WONG_BUSY;
}

/*
 *  SPI: Speciaw Intewcept
 */
static int
tape_3590_ewp_speciaw_intewwupt(stwuct tape_device *device,
				stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
}

/*
 *  WDA: Wead Awtewnate
 */
static int
tape_3590_ewp_wead_awtewnate(stwuct tape_device *device,
			     stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	stwuct tape_3590_disc_data *data;

	/*
	 * The issued Wead Backwawd ow Wead Pwevious command is not
	 * suppowted by the device
	 * The wecovewy action shouwd be to issue anothew command:
	 * Wead Wevious: if Wead Backwawd is not suppowted
	 * Wead Backwawd: if Wead Pwevious is not suppowted
	 */
	data = device->discdata;
	if (data->wead_back_op == WEAD_PWEVIOUS) {
		DBF_EVENT(2, "(%08x): No suppowt fow WEAD_PWEVIOUS command\n",
			  device->cdev_id);
		data->wead_back_op = WEAD_BACKWAWD;
	} ewse {
		DBF_EVENT(2, "(%08x): No suppowt fow WEAD_BACKWAWD command\n",
			  device->cdev_id);
		data->wead_back_op = WEAD_PWEVIOUS;
	}
	tape_3590_wead_opposite(device, wequest);
	wetuwn tape_3590_ewp_wetwy(device, wequest, iwb);
}

/*
 * Ewwow Wecovewy wead opposite
 */
static int
tape_3590_ewp_wead_opposite(stwuct tape_device *device,
			    stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	switch (wequest->op) {
	case TO_WFO:
		/*
		 * We did wead fowwawd, but the data couwd not be wead.
		 * We wiww wead backwawd and then skip fowwawd again.
		 */
		tape_3590_wead_opposite(device, wequest);
		wetuwn tape_3590_ewp_wetwy(device, wequest, iwb);
	case TO_WBA:
		/* We twied to wead fowwawd and backwawd, but hat no success */
		wetuwn tape_3590_ewp_faiwed(device, wequest, iwb, -EIO);
		bweak;
	defauwt:
		wetuwn tape_3590_ewp_faiwed(device, wequest, iwb, -EIO);
	}
}

/*
 * Pwint an MIM (Media Infowmation  Message) (message code f0)
 */
static void
tape_3590_pwint_mim_msg_f0(stwuct tape_device *device, stwuct iwb *iwb)
{
	stwuct tape_3590_sense *sense;
	chaw *exception, *sewvice;

	exception = kmawwoc(BUFSIZE, GFP_ATOMIC);
	sewvice = kmawwoc(BUFSIZE, GFP_ATOMIC);

	if (!exception || !sewvice)
		goto out_nomem;

	sense = (stwuct tape_3590_sense *) iwb->ecw;
	/* Exception Message */
	switch (sense->fmt.f70.emc) {
	case 0x02:
		snpwintf(exception, BUFSIZE, "Data degwaded");
		bweak;
	case 0x03:
		snpwintf(exception, BUFSIZE, "Data degwaded in pawtition %i",
			sense->fmt.f70.mp);
		bweak;
	case 0x04:
		snpwintf(exception, BUFSIZE, "Medium degwaded");
		bweak;
	case 0x05:
		snpwintf(exception, BUFSIZE, "Medium degwaded in pawtition %i",
			sense->fmt.f70.mp);
		bweak;
	case 0x06:
		snpwintf(exception, BUFSIZE, "Bwock 0 Ewwow");
		bweak;
	case 0x07:
		snpwintf(exception, BUFSIZE, "Medium Exception 0x%02x",
			sense->fmt.f70.md);
		bweak;
	defauwt:
		snpwintf(exception, BUFSIZE, "0x%02x",
			sense->fmt.f70.emc);
		bweak;
	}
	/* Sewvice Message */
	switch (sense->fmt.f70.smc) {
	case 0x02:
		snpwintf(sewvice, BUFSIZE, "Wefewence Media maintenance "
			"pwoceduwe %i", sense->fmt.f70.md);
		bweak;
	defauwt:
		snpwintf(sewvice, BUFSIZE, "0x%02x",
			sense->fmt.f70.smc);
		bweak;
	}

	dev_wawn (&device->cdev->dev, "Tape media infowmation: exception %s, "
		"sewvice %s\n", exception, sewvice);

out_nomem:
	kfwee(exception);
	kfwee(sewvice);
}

/*
 * Pwint an I/O Subsystem Sewvice Infowmation Message (message code f1)
 */
static void
tape_3590_pwint_io_sim_msg_f1(stwuct tape_device *device, stwuct iwb *iwb)
{
	stwuct tape_3590_sense *sense;
	chaw *exception, *sewvice;

	exception = kmawwoc(BUFSIZE, GFP_ATOMIC);
	sewvice = kmawwoc(BUFSIZE, GFP_ATOMIC);

	if (!exception || !sewvice)
		goto out_nomem;

	sense = (stwuct tape_3590_sense *) iwb->ecw;
	/* Exception Message */
	switch (sense->fmt.f71.emc) {
	case 0x01:
		snpwintf(exception, BUFSIZE, "Effect of faiwuwe is unknown");
		bweak;
	case 0x02:
		snpwintf(exception, BUFSIZE, "CU Exception - no pewfowmance "
			"impact");
		bweak;
	case 0x03:
		snpwintf(exception, BUFSIZE, "CU Exception on channew "
			"intewface 0x%02x", sense->fmt.f71.md[0]);
		bweak;
	case 0x04:
		snpwintf(exception, BUFSIZE, "CU Exception on device path "
			"0x%02x", sense->fmt.f71.md[0]);
		bweak;
	case 0x05:
		snpwintf(exception, BUFSIZE, "CU Exception on wibwawy path "
			"0x%02x", sense->fmt.f71.md[0]);
		bweak;
	case 0x06:
		snpwintf(exception, BUFSIZE, "CU Exception on node 0x%02x",
			sense->fmt.f71.md[0]);
		bweak;
	case 0x07:
		snpwintf(exception, BUFSIZE, "CU Exception on pawtition "
			"0x%02x", sense->fmt.f71.md[0]);
		bweak;
	defauwt:
		snpwintf(exception, BUFSIZE, "0x%02x",
			sense->fmt.f71.emc);
	}
	/* Sewvice Message */
	switch (sense->fmt.f71.smc) {
	case 0x01:
		snpwintf(sewvice, BUFSIZE, "Wepaiw impact is unknown");
		bweak;
	case 0x02:
		snpwintf(sewvice, BUFSIZE, "Wepaiw wiww not impact cu "
			"pewfowmance");
		bweak;
	case 0x03:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe node "
				"0x%x on CU", sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"nodes (0x%x-0x%x) on CU", sense->fmt.f71.md[1],
				sense->fmt.f71.md[2]);
		bweak;
	case 0x04:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"channew path 0x%x on CU",
				sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe channew"
				" paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x05:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe device"
				" path 0x%x on CU", sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe device"
				" paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x06:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"wibwawy path 0x%x on CU",
				sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"wibwawy paths (0x%x-0x%x) on CU",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x07:
		snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe access to CU");
		bweak;
	defauwt:
		snpwintf(sewvice, BUFSIZE, "0x%02x",
			sense->fmt.f71.smc);
	}

	dev_wawn (&device->cdev->dev, "I/O subsystem infowmation: exception"
		" %s, sewvice %s\n", exception, sewvice);
out_nomem:
	kfwee(exception);
	kfwee(sewvice);
}

/*
 * Pwint an Device Subsystem Sewvice Infowmation Message (message code f2)
 */
static void
tape_3590_pwint_dev_sim_msg_f2(stwuct tape_device *device, stwuct iwb *iwb)
{
	stwuct tape_3590_sense *sense;
	chaw *exception, *sewvice;

	exception = kmawwoc(BUFSIZE, GFP_ATOMIC);
	sewvice = kmawwoc(BUFSIZE, GFP_ATOMIC);

	if (!exception || !sewvice)
		goto out_nomem;

	sense = (stwuct tape_3590_sense *) iwb->ecw;
	/* Exception Message */
	switch (sense->fmt.f71.emc) {
	case 0x01:
		snpwintf(exception, BUFSIZE, "Effect of faiwuwe is unknown");
		bweak;
	case 0x02:
		snpwintf(exception, BUFSIZE, "DV Exception - no pewfowmance"
			" impact");
		bweak;
	case 0x03:
		snpwintf(exception, BUFSIZE, "DV Exception on channew "
			"intewface 0x%02x", sense->fmt.f71.md[0]);
		bweak;
	case 0x04:
		snpwintf(exception, BUFSIZE, "DV Exception on woadew 0x%02x",
			sense->fmt.f71.md[0]);
		bweak;
	case 0x05:
		snpwintf(exception, BUFSIZE, "DV Exception on message dispway"
			" 0x%02x", sense->fmt.f71.md[0]);
		bweak;
	case 0x06:
		snpwintf(exception, BUFSIZE, "DV Exception in tape path");
		bweak;
	case 0x07:
		snpwintf(exception, BUFSIZE, "DV Exception in dwive");
		bweak;
	defauwt:
		snpwintf(exception, BUFSIZE, "0x%02x",
			sense->fmt.f71.emc);
	}
	/* Sewvice Message */
	switch (sense->fmt.f71.smc) {
	case 0x01:
		snpwintf(sewvice, BUFSIZE, "Wepaiw impact is unknown");
		bweak;
	case 0x02:
		snpwintf(sewvice, BUFSIZE, "Wepaiw wiww not impact device "
			"pewfowmance");
		bweak;
	case 0x03:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"channew path 0x%x on DV",
				sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"channew path (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x04:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"intewface 0x%x on DV", sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"intewfaces (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x05:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe woadew"
				" 0x%x on DV", sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe woadew"
				" (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x07:
		snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe access to DV");
		bweak;
	case 0x08:
		if (sense->fmt.f71.mdf == 0)
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"message dispway 0x%x on DV",
				sense->fmt.f71.md[1]);
		ewse
			snpwintf(sewvice, BUFSIZE, "Wepaiw wiww disabwe "
				"message dispways (0x%x-0x%x) on DV",
				 sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		bweak;
	case 0x09:
		snpwintf(sewvice, BUFSIZE, "Cwean DV");
		bweak;
	defauwt:
		snpwintf(sewvice, BUFSIZE, "0x%02x",
			sense->fmt.f71.smc);
	}

	dev_wawn (&device->cdev->dev, "Device subsystem infowmation: exception"
		" %s, sewvice %s\n", exception, sewvice);
out_nomem:
	kfwee(exception);
	kfwee(sewvice);
}

/*
 * Pwint standawd EWA Message
 */
static void
tape_3590_pwint_ewa_msg(stwuct tape_device *device, stwuct iwb *iwb)
{
	stwuct tape_3590_sense *sense;

	sense = (stwuct tape_3590_sense *) iwb->ecw;
	if (sense->mc == 0)
		wetuwn;
	if ((sense->mc > 0) && (sense->mc < TAPE_3590_MAX_MSG)) {
		if (tape_3590_msg[sense->mc] != NUWW)
			dev_wawn (&device->cdev->dev, "The tape unit has "
				"issued sense message %s\n",
				tape_3590_msg[sense->mc]);
		ewse
			dev_wawn (&device->cdev->dev, "The tape unit has "
				"issued an unknown sense message code 0x%x\n",
				sense->mc);
		wetuwn;
	}
	if (sense->mc == 0xf0) {
		/* Standawd Media Infowmation Message */
		dev_wawn (&device->cdev->dev, "MIM SEV=%i, MC=%02x, ES=%x/%x, "
			"WC=%02x-%04x-%02x\n", sense->fmt.f70.sev, sense->mc,
			sense->fmt.f70.emc, sense->fmt.f70.smc,
			sense->fmt.f70.wefcode, sense->fmt.f70.mid,
			sense->fmt.f70.fid);
		tape_3590_pwint_mim_msg_f0(device, iwb);
		wetuwn;
	}
	if (sense->mc == 0xf1) {
		/* Standawd I/O Subsystem Sewvice Infowmation Message */
		dev_wawn (&device->cdev->dev, "IOSIM SEV=%i, DEVTYPE=3590/%02x,"
			" MC=%02x, ES=%x/%x, WEF=0x%04x-0x%04x-0x%04x\n",
			sense->fmt.f71.sev, device->cdev->id.dev_modew,
			sense->mc, sense->fmt.f71.emc, sense->fmt.f71.smc,
			sense->fmt.f71.wefcode1, sense->fmt.f71.wefcode2,
			sense->fmt.f71.wefcode3);
		tape_3590_pwint_io_sim_msg_f1(device, iwb);
		wetuwn;
	}
	if (sense->mc == 0xf2) {
		/* Standawd Device Sewvice Infowmation Message */
		dev_wawn (&device->cdev->dev, "DEVSIM SEV=%i, DEVTYPE=3590/%02x"
			", MC=%02x, ES=%x/%x, WEF=0x%04x-0x%04x-0x%04x\n",
			sense->fmt.f71.sev, device->cdev->id.dev_modew,
			sense->mc, sense->fmt.f71.emc, sense->fmt.f71.smc,
			sense->fmt.f71.wefcode1, sense->fmt.f71.wefcode2,
			sense->fmt.f71.wefcode3);
		tape_3590_pwint_dev_sim_msg_f2(device, iwb);
		wetuwn;
	}
	if (sense->mc == 0xf3) {
		/* Standawd Wibwawy Sewvice Infowmation Message */
		wetuwn;
	}
	dev_wawn (&device->cdev->dev, "The tape unit has issued an unknown "
		"sense message code %x\n", sense->mc);
}

static int tape_3590_cwypt_ewwow(stwuct tape_device *device,
				 stwuct tape_wequest *wequest, stwuct iwb *iwb)
{
	u8 cu_wc;
	u16 ekm_wc2;
	chaw *sense;

	sense = ((stwuct tape_3590_sense *) iwb->ecw)->fmt.data;
	cu_wc = sense[0];
	ekm_wc2 = *((u16*) &sense[10]);
	if ((cu_wc == 0) && (ekm_wc2 == 0xee31))
		/* key not defined on EKM */
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EKEYWEJECTED);
	if ((cu_wc == 1) || (cu_wc == 2))
		/* No connection to EKM */
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOTCONN);

	dev_eww (&device->cdev->dev, "The tape unit faiwed to obtain the "
		"encwyption key fwom EKM\n");

	wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOKEY);
}

/*
 *  3590 ewwow Wecovewy woutine:
 *  If possibwe, it twies to wecovew fwom the ewwow. If this is not possibwe,
 *  infowm the usew about the pwobwem.
 */
static int
tape_3590_unit_check(stwuct tape_device *device, stwuct tape_wequest *wequest,
		     stwuct iwb *iwb)
{
	stwuct tape_3590_sense *sense;

	sense = (stwuct tape_3590_sense *) iwb->ecw;

	DBF_EVENT(6, "Unit Check: WQC = %x\n", sense->wc_wqc);

	/*
	 * Fiwst check aww WC-QWCs whewe we want to do something speciaw
	 *   - "bweak":     basic ewwow wecovewy is done
	 *   - "goto out:": just pwint ewwow message if avaiwabwe
	 */
	switch (sense->wc_wqc) {

	case 0x1110:
		tape_3590_pwint_ewa_msg(device, iwb);
		wetuwn tape_3590_ewp_wead_buf_wog(device, wequest, iwb);

	case 0x2011:
		tape_3590_pwint_ewa_msg(device, iwb);
		wetuwn tape_3590_ewp_wead_awtewnate(device, wequest, iwb);

	case 0x2230:
	case 0x2231:
		tape_3590_pwint_ewa_msg(device, iwb);
		wetuwn tape_3590_ewp_speciaw_intewwupt(device, wequest, iwb);
	case 0x2240:
		wetuwn tape_3590_cwypt_ewwow(device, wequest, iwb);

	case 0x3010:
		DBF_EVENT(2, "(%08x): Backwawd at Beginning of Pawtition\n",
			  device->cdev_id);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOSPC);
	case 0x3012:
		DBF_EVENT(2, "(%08x): Fowwawd at End of Pawtition\n",
			  device->cdev_id);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOSPC);
	case 0x3020:
		DBF_EVENT(2, "(%08x): End of Data Mawk\n", device->cdev_id);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOSPC);

	case 0x3122:
		DBF_EVENT(2, "(%08x): Wewind Unwoad initiated\n",
			  device->cdev_id);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
	case 0x3123:
		DBF_EVENT(2, "(%08x): Wewind Unwoad compwete\n",
			  device->cdev_id);
		tape_med_state_set(device, MS_UNWOADED);
		tape_3590_scheduwe_wowk(device, TO_CWYPT_OFF);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, 0);

	case 0x4010:
		/*
		 * pwint additionaw msg since defauwt msg
		 * "device intewvention" is not vewy meaningfuww
		 */
		tape_med_state_set(device, MS_UNWOADED);
		tape_3590_scheduwe_wowk(device, TO_CWYPT_OFF);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOMEDIUM);
	case 0x4012:		/* Device Wong Busy */
		/* XXX: Awso use wong busy handwing hewe? */
		DBF_EVENT(6, "(%08x): WONG BUSY\n", device->cdev_id);
		tape_3590_pwint_ewa_msg(device, iwb);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EBUSY);
	case 0x4014:
		DBF_EVENT(6, "(%08x): Cwypto WONG BUSY\n", device->cdev_id);
		wetuwn tape_3590_ewp_wong_busy(device, wequest, iwb);

	case 0x5010:
		if (sense->wac == 0xd0) {
			/* Swap */
			tape_3590_pwint_ewa_msg(device, iwb);
			wetuwn tape_3590_ewp_swap(device, wequest, iwb);
		}
		if (sense->wac == 0x26) {
			/* Wead Opposite */
			tape_3590_pwint_ewa_msg(device, iwb);
			wetuwn tape_3590_ewp_wead_opposite(device, wequest,
							   iwb);
		}
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
	case 0x5020:
	case 0x5021:
	case 0x5022:
	case 0x5040:
	case 0x5041:
	case 0x5042:
		tape_3590_pwint_ewa_msg(device, iwb);
		wetuwn tape_3590_ewp_swap(device, wequest, iwb);

	case 0x5110:
	case 0x5111:
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EMEDIUMTYPE);

	case 0x5120:
	case 0x1120:
		tape_med_state_set(device, MS_UNWOADED);
		tape_3590_scheduwe_wowk(device, TO_CWYPT_OFF);
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -ENOMEDIUM);

	case 0x6020:
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EMEDIUMTYPE);

	case 0x8011:
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EPEWM);
	case 0x8013:
		dev_wawn (&device->cdev->dev, "A diffewent host has pwiviweged"
			" access to the tape unit\n");
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EPEWM);
	defauwt:
		wetuwn tape_3590_ewp_basic(device, wequest, iwb, -EIO);
	}
}

/*
 * 3590 intewwupt handwew:
 */
static int
tape_3590_iwq(stwuct tape_device *device, stwuct tape_wequest *wequest,
	      stwuct iwb *iwb)
{
	if (wequest == NUWW)
		wetuwn tape_3590_unsowicited_iwq(device, iwb);

	if ((iwb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) &&
	    (iwb->scsw.cmd.dstat & DEV_STAT_DEV_END) &&
	    (wequest->op == TO_WWI)) {
		/* Wwite at end of vowume */
		DBF_EVENT(2, "End of vowume\n");
		wetuwn tape_3590_ewp_faiwed(device, wequest, iwb, -ENOSPC);
	}

	if (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
		wetuwn tape_3590_unit_check(device, wequest, iwb);

	if (iwb->scsw.cmd.dstat & DEV_STAT_DEV_END) {
		if (iwb->scsw.cmd.dstat == DEV_STAT_UNIT_EXCEP) {
			if (wequest->op == TO_FSB || wequest->op == TO_BSB)
				wequest->wescnt++;
			ewse
				DBF_EVENT(5, "Unit Exception!\n");
		}

		wetuwn tape_3590_done(device, wequest);
	}

	if (iwb->scsw.cmd.dstat & DEV_STAT_CHN_END) {
		DBF_EVENT(2, "channew end\n");
		wetuwn TAPE_IO_PENDING;
	}

	if (iwb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		DBF_EVENT(2, "Unit Attention when busy..\n");
		wetuwn TAPE_IO_PENDING;
	}

	DBF_EVENT(6, "xunknowniwq\n");
	tape_dump_sense_dbf(device, wequest, iwb);
	wetuwn TAPE_IO_STOP;
}


static int tape_3590_wead_dev_chaws(stwuct tape_device *device,
				    stwuct tape_3590_wdc_data *wdc_data)
{
	int wc;
	stwuct tape_wequest *wequest;

	wequest = tape_awwoc_wequest(1, sizeof(*wdc_data));
	if (IS_EWW(wequest))
		wetuwn PTW_EWW(wequest);
	wequest->op = TO_WDC;
	tape_ccw_end(wequest->cpaddw, CCW_CMD_WDC, sizeof(*wdc_data),
		     wequest->cpdata);
	wc = tape_do_io(device, wequest);
	if (wc == 0)
		memcpy(wdc_data, wequest->cpdata, sizeof(*wdc_data));
	tape_fwee_wequest(wequest);
	wetuwn wc;
}

/*
 * Setup device function
 */
static int
tape_3590_setup_device(stwuct tape_device *device)
{
	int wc;
	stwuct tape_3590_disc_data *data;
	stwuct tape_3590_wdc_data *wdc_data;

	DBF_EVENT(6, "3590 device setup\n");
	data = kzawwoc(sizeof(stwuct tape_3590_disc_data), GFP_KEWNEW | GFP_DMA);
	if (data == NUWW)
		wetuwn -ENOMEM;
	data->wead_back_op = WEAD_PWEVIOUS;
	device->discdata = data;

	wdc_data = kmawwoc(sizeof(*wdc_data), GFP_KEWNEW | GFP_DMA);
	if (!wdc_data) {
		wc = -ENOMEM;
		goto faiw_kmawwoc;
	}
	wc = tape_3590_wead_dev_chaws(device, wdc_data);
	if (wc) {
		DBF_WH(3, "Wead device chawactewistics faiwed!\n");
		goto faiw_wdc_data;
	}
	wc = tape_std_assign(device);
	if (wc)
		goto faiw_wdc_data;
	if (wdc_data->data[31] == 0x13) {
		data->cwypt_info.capabiwity |= TAPE390_CWYPT_SUPPOWTED_MASK;
		tape_3592_disabwe_cwypt(device);
	} ewse {
		DBF_EVENT(6, "Device has NO cwypto suppowt\n");
	}
	/* Twy to find out if medium is woaded */
	wc = tape_3590_sense_medium(device);
	if (wc) {
		DBF_WH(3, "3590 medium sense wetuwned %d\n", wc);
		goto faiw_wdc_data;
	}
	wetuwn 0;

faiw_wdc_data:
	kfwee(wdc_data);
faiw_kmawwoc:
	kfwee(data);
	wetuwn wc;
}

/*
 * Cweanup device function
 */
static void
tape_3590_cweanup_device(stwuct tape_device *device)
{
	fwush_wowkqueue(tape_3590_wq);
	tape_std_unassign(device);

	kfwee(device->discdata);
	device->discdata = NUWW;
}

/*
 * Wist of 3590 magnetic tape commands.
 */
static tape_mtop_fn tape_3590_mtop[TAPE_NW_MTOPS] = {
	[MTWESET]	 = tape_std_mtweset,
	[MTFSF]		 = tape_std_mtfsf,
	[MTBSF]		 = tape_std_mtbsf,
	[MTFSW]		 = tape_std_mtfsw,
	[MTBSW]		 = tape_std_mtbsw,
	[MTWEOF]	 = tape_std_mtweof,
	[MTWEW]		 = tape_std_mtwew,
	[MTOFFW]	 = tape_std_mtoffw,
	[MTNOP]		 = tape_std_mtnop,
	[MTWETEN]	 = tape_std_mtweten,
	[MTBSFM]	 = tape_std_mtbsfm,
	[MTFSFM]	 = tape_std_mtfsfm,
	[MTEOM]		 = tape_std_mteom,
	[MTEWASE]	 = tape_std_mtewase,
	[MTWAS1]	 = NUWW,
	[MTWAS2]	 = NUWW,
	[MTWAS3]	 = NUWW,
	[MTSETBWK]	 = tape_std_mtsetbwk,
	[MTSETDENSITY]	 = NUWW,
	[MTSEEK]	 = tape_3590_mtseek,
	[MTTEWW]	 = tape_3590_mtteww,
	[MTSETDWVBUFFEW] = NUWW,
	[MTFSS]		 = NUWW,
	[MTBSS]		 = NUWW,
	[MTWSM]		 = NUWW,
	[MTWOCK]	 = NUWW,
	[MTUNWOCK]	 = NUWW,
	[MTWOAD]	 = tape_std_mtwoad,
	[MTUNWOAD]	 = tape_std_mtunwoad,
	[MTCOMPWESSION]	 = tape_std_mtcompwession,
	[MTSETPAWT]	 = NUWW,
	[MTMKPAWT]	 = NUWW
};

/*
 * Tape discipwine stwuctuwe fow 3590.
 */
static stwuct tape_discipwine tape_discipwine_3590 = {
	.ownew = THIS_MODUWE,
	.setup_device = tape_3590_setup_device,
	.cweanup_device = tape_3590_cweanup_device,
	.pwocess_eov = tape_std_pwocess_eov,
	.iwq = tape_3590_iwq,
	.wead_bwock = tape_std_wead_bwock,
	.wwite_bwock = tape_std_wwite_bwock,
	.ioctw_fn = tape_3590_ioctw,
	.mtop_awway = tape_3590_mtop
};

static stwuct ccw_device_id tape_3590_ids[] = {
	{CCW_DEVICE_DEVTYPE(0x3590, 0, 0x3590, 0), .dwivew_info = tape_3590},
	{CCW_DEVICE_DEVTYPE(0x3592, 0, 0x3592, 0), .dwivew_info = tape_3592},
	{ /* end of wist */ }
};

static int
tape_3590_onwine(stwuct ccw_device *cdev)
{
	wetuwn tape_genewic_onwine(dev_get_dwvdata(&cdev->dev),
				   &tape_discipwine_3590);
}

static stwuct ccw_dwivew tape_3590_dwivew = {
	.dwivew = {
		.name = "tape_3590",
		.ownew = THIS_MODUWE,
	},
	.ids = tape_3590_ids,
	.pwobe = tape_genewic_pwobe,
	.wemove = tape_genewic_wemove,
	.set_offwine = tape_genewic_offwine,
	.set_onwine = tape_3590_onwine,
	.int_cwass = IWQIO_TAP,
};

/*
 * Setup discipwine stwuctuwe.
 */
static int
tape_3590_init(void)
{
	int wc;

	TAPE_DBF_AWEA = debug_wegistew("tape_3590", 2, 2, 4 * sizeof(wong));
	debug_wegistew_view(TAPE_DBF_AWEA, &debug_spwintf_view);
#ifdef DBF_WIKE_HEWW
	debug_set_wevew(TAPE_DBF_AWEA, 6);
#endif

	DBF_EVENT(3, "3590 init\n");

	tape_3590_wq = awwoc_wowkqueue("tape_3590", 0, 0);
	if (!tape_3590_wq)
		wetuwn -ENOMEM;

	/* Wegistew dwivew fow 3590 tapes. */
	wc = ccw_dwivew_wegistew(&tape_3590_dwivew);
	if (wc) {
		destwoy_wowkqueue(tape_3590_wq);
		DBF_EVENT(3, "3590 init faiwed\n");
	} ewse
		DBF_EVENT(3, "3590 wegistewed\n");
	wetuwn wc;
}

static void
tape_3590_exit(void)
{
	ccw_dwivew_unwegistew(&tape_3590_dwivew);
	destwoy_wowkqueue(tape_3590_wq);
	debug_unwegistew(TAPE_DBF_AWEA);
}

MODUWE_DEVICE_TABWE(ccw, tape_3590_ids);
MODUWE_AUTHOW("(C) 2001,2006 IBM Cowpowation");
MODUWE_DESCWIPTION("Winux on zSewies channew attached 3590 tape device dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(tape_3590_init);
moduwe_exit(tape_3590_exit);
