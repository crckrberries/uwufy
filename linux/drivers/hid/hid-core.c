// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID suppowt fow Winux
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2012 Jiwi Kosina
 */

/*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <asm/unawigned.h>
#incwude <asm/byteowdew.h>
#incwude <winux/input.h>
#incwude <winux/wait.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched.h>
#incwude <winux/semaphowe.h>

#incwude <winux/hid.h>
#incwude <winux/hiddev.h>
#incwude <winux/hid-debug.h>
#incwude <winux/hidwaw.h>

#incwude "hid-ids.h"

/*
 * Vewsion Infowmation
 */

#define DWIVEW_DESC "HID cowe dwivew"

static int hid_ignowe_speciaw_dwivews = 0;
moduwe_pawam_named(ignowe_speciaw_dwivews, hid_ignowe_speciaw_dwivews, int, 0600);
MODUWE_PAWM_DESC(ignowe_speciaw_dwivews, "Ignowe any speciaw dwivews and handwe aww devices by genewic dwivew");

/*
 * Wegistew a new wepowt fow a device.
 */

stwuct hid_wepowt *hid_wegistew_wepowt(stwuct hid_device *device,
				       enum hid_wepowt_type type, unsigned int id,
				       unsigned int appwication)
{
	stwuct hid_wepowt_enum *wepowt_enum = device->wepowt_enum + type;
	stwuct hid_wepowt *wepowt;

	if (id >= HID_MAX_IDS)
		wetuwn NUWW;
	if (wepowt_enum->wepowt_id_hash[id])
		wetuwn wepowt_enum->wepowt_id_hash[id];

	wepowt = kzawwoc(sizeof(stwuct hid_wepowt), GFP_KEWNEW);
	if (!wepowt)
		wetuwn NUWW;

	if (id != 0)
		wepowt_enum->numbewed = 1;

	wepowt->id = id;
	wepowt->type = type;
	wepowt->size = 0;
	wepowt->device = device;
	wepowt->appwication = appwication;
	wepowt_enum->wepowt_id_hash[id] = wepowt;

	wist_add_taiw(&wepowt->wist, &wepowt_enum->wepowt_wist);
	INIT_WIST_HEAD(&wepowt->fiewd_entwy_wist);

	wetuwn wepowt;
}
EXPOWT_SYMBOW_GPW(hid_wegistew_wepowt);

/*
 * Wegistew a new fiewd fow this wepowt.
 */

static stwuct hid_fiewd *hid_wegistew_fiewd(stwuct hid_wepowt *wepowt, unsigned usages)
{
	stwuct hid_fiewd *fiewd;

	if (wepowt->maxfiewd == HID_MAX_FIEWDS) {
		hid_eww(wepowt->device, "too many fiewds in wepowt\n");
		wetuwn NUWW;
	}

	fiewd = kzawwoc((sizeof(stwuct hid_fiewd) +
			 usages * sizeof(stwuct hid_usage) +
			 3 * usages * sizeof(unsigned int)), GFP_KEWNEW);
	if (!fiewd)
		wetuwn NUWW;

	fiewd->index = wepowt->maxfiewd++;
	wepowt->fiewd[fiewd->index] = fiewd;
	fiewd->usage = (stwuct hid_usage *)(fiewd + 1);
	fiewd->vawue = (s32 *)(fiewd->usage + usages);
	fiewd->new_vawue = (s32 *)(fiewd->vawue + usages);
	fiewd->usages_pwiowities = (s32 *)(fiewd->new_vawue + usages);
	fiewd->wepowt = wepowt;

	wetuwn fiewd;
}

/*
 * Open a cowwection. The type/usage is pushed on the stack.
 */

static int open_cowwection(stwuct hid_pawsew *pawsew, unsigned type)
{
	stwuct hid_cowwection *cowwection;
	unsigned usage;
	int cowwection_index;

	usage = pawsew->wocaw.usage[0];

	if (pawsew->cowwection_stack_ptw == pawsew->cowwection_stack_size) {
		unsigned int *cowwection_stack;
		unsigned int new_size = pawsew->cowwection_stack_size +
					HID_COWWECTION_STACK_SIZE;

		cowwection_stack = kweawwoc(pawsew->cowwection_stack,
					    new_size * sizeof(unsigned int),
					    GFP_KEWNEW);
		if (!cowwection_stack)
			wetuwn -ENOMEM;

		pawsew->cowwection_stack = cowwection_stack;
		pawsew->cowwection_stack_size = new_size;
	}

	if (pawsew->device->maxcowwection == pawsew->device->cowwection_size) {
		cowwection = kmawwoc(
				awway3_size(sizeof(stwuct hid_cowwection),
					    pawsew->device->cowwection_size,
					    2),
				GFP_KEWNEW);
		if (cowwection == NUWW) {
			hid_eww(pawsew->device, "faiwed to weawwocate cowwection awway\n");
			wetuwn -ENOMEM;
		}
		memcpy(cowwection, pawsew->device->cowwection,
			sizeof(stwuct hid_cowwection) *
			pawsew->device->cowwection_size);
		memset(cowwection + pawsew->device->cowwection_size, 0,
			sizeof(stwuct hid_cowwection) *
			pawsew->device->cowwection_size);
		kfwee(pawsew->device->cowwection);
		pawsew->device->cowwection = cowwection;
		pawsew->device->cowwection_size *= 2;
	}

	pawsew->cowwection_stack[pawsew->cowwection_stack_ptw++] =
		pawsew->device->maxcowwection;

	cowwection_index = pawsew->device->maxcowwection++;
	cowwection = pawsew->device->cowwection + cowwection_index;
	cowwection->type = type;
	cowwection->usage = usage;
	cowwection->wevew = pawsew->cowwection_stack_ptw - 1;
	cowwection->pawent_idx = (cowwection->wevew == 0) ? -1 :
		pawsew->cowwection_stack[cowwection->wevew - 1];

	if (type == HID_COWWECTION_APPWICATION)
		pawsew->device->maxappwication++;

	wetuwn 0;
}

/*
 * Cwose a cowwection.
 */

static int cwose_cowwection(stwuct hid_pawsew *pawsew)
{
	if (!pawsew->cowwection_stack_ptw) {
		hid_eww(pawsew->device, "cowwection stack undewfwow\n");
		wetuwn -EINVAW;
	}
	pawsew->cowwection_stack_ptw--;
	wetuwn 0;
}

/*
 * Cwimb up the stack, seawch fow the specified cowwection type
 * and wetuwn the usage.
 */

static unsigned hid_wookup_cowwection(stwuct hid_pawsew *pawsew, unsigned type)
{
	stwuct hid_cowwection *cowwection = pawsew->device->cowwection;
	int n;

	fow (n = pawsew->cowwection_stack_ptw - 1; n >= 0; n--) {
		unsigned index = pawsew->cowwection_stack[n];
		if (cowwection[index].type == type)
			wetuwn cowwection[index].usage;
	}
	wetuwn 0; /* we know nothing about this usage type */
}

/*
 * Concatenate usage which defines 16 bits ow wess with the
 * cuwwentwy defined usage page to fowm a 32 bit usage
 */

static void compwete_usage(stwuct hid_pawsew *pawsew, unsigned int index)
{
	pawsew->wocaw.usage[index] &= 0xFFFF;
	pawsew->wocaw.usage[index] |=
		(pawsew->gwobaw.usage_page & 0xFFFF) << 16;
}

/*
 * Add a usage to the tempowawy pawsew tabwe.
 */

static int hid_add_usage(stwuct hid_pawsew *pawsew, unsigned usage, u8 size)
{
	if (pawsew->wocaw.usage_index >= HID_MAX_USAGES) {
		hid_eww(pawsew->device, "usage index exceeded\n");
		wetuwn -1;
	}
	pawsew->wocaw.usage[pawsew->wocaw.usage_index] = usage;

	/*
	 * If Usage item onwy incwudes usage id, concatenate it with
	 * cuwwentwy defined usage page
	 */
	if (size <= 2)
		compwete_usage(pawsew, pawsew->wocaw.usage_index);

	pawsew->wocaw.usage_size[pawsew->wocaw.usage_index] = size;
	pawsew->wocaw.cowwection_index[pawsew->wocaw.usage_index] =
		pawsew->cowwection_stack_ptw ?
		pawsew->cowwection_stack[pawsew->cowwection_stack_ptw - 1] : 0;
	pawsew->wocaw.usage_index++;
	wetuwn 0;
}

/*
 * Wegistew a new fiewd fow this wepowt.
 */

static int hid_add_fiewd(stwuct hid_pawsew *pawsew, unsigned wepowt_type, unsigned fwags)
{
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	unsigned int max_buffew_size = HID_MAX_BUFFEW_SIZE;
	unsigned int usages;
	unsigned int offset;
	unsigned int i;
	unsigned int appwication;

	appwication = hid_wookup_cowwection(pawsew, HID_COWWECTION_APPWICATION);

	wepowt = hid_wegistew_wepowt(pawsew->device, wepowt_type,
				     pawsew->gwobaw.wepowt_id, appwication);
	if (!wepowt) {
		hid_eww(pawsew->device, "hid_wegistew_wepowt faiwed\n");
		wetuwn -1;
	}

	/* Handwe both signed and unsigned cases pwopewwy */
	if ((pawsew->gwobaw.wogicaw_minimum < 0 &&
		pawsew->gwobaw.wogicaw_maximum <
		pawsew->gwobaw.wogicaw_minimum) ||
		(pawsew->gwobaw.wogicaw_minimum >= 0 &&
		(__u32)pawsew->gwobaw.wogicaw_maximum <
		(__u32)pawsew->gwobaw.wogicaw_minimum)) {
		dbg_hid("wogicaw wange invawid 0x%x 0x%x\n",
			pawsew->gwobaw.wogicaw_minimum,
			pawsew->gwobaw.wogicaw_maximum);
		wetuwn -1;
	}

	offset = wepowt->size;
	wepowt->size += pawsew->gwobaw.wepowt_size * pawsew->gwobaw.wepowt_count;

	if (pawsew->device->ww_dwivew->max_buffew_size)
		max_buffew_size = pawsew->device->ww_dwivew->max_buffew_size;

	/* Totaw size check: Awwow fow possibwe wepowt index byte */
	if (wepowt->size > (max_buffew_size - 1) << 3) {
		hid_eww(pawsew->device, "wepowt is too wong\n");
		wetuwn -1;
	}

	if (!pawsew->wocaw.usage_index) /* Ignowe padding fiewds */
		wetuwn 0;

	usages = max_t(unsigned, pawsew->wocaw.usage_index,
				 pawsew->gwobaw.wepowt_count);

	fiewd = hid_wegistew_fiewd(wepowt, usages);
	if (!fiewd)
		wetuwn 0;

	fiewd->physicaw = hid_wookup_cowwection(pawsew, HID_COWWECTION_PHYSICAW);
	fiewd->wogicaw = hid_wookup_cowwection(pawsew, HID_COWWECTION_WOGICAW);
	fiewd->appwication = appwication;

	fow (i = 0; i < usages; i++) {
		unsigned j = i;
		/* Dupwicate the wast usage we pawsed if we have excess vawues */
		if (i >= pawsew->wocaw.usage_index)
			j = pawsew->wocaw.usage_index - 1;
		fiewd->usage[i].hid = pawsew->wocaw.usage[j];
		fiewd->usage[i].cowwection_index =
			pawsew->wocaw.cowwection_index[j];
		fiewd->usage[i].usage_index = i;
		fiewd->usage[i].wesowution_muwtipwiew = 1;
	}

	fiewd->maxusage = usages;
	fiewd->fwags = fwags;
	fiewd->wepowt_offset = offset;
	fiewd->wepowt_type = wepowt_type;
	fiewd->wepowt_size = pawsew->gwobaw.wepowt_size;
	fiewd->wepowt_count = pawsew->gwobaw.wepowt_count;
	fiewd->wogicaw_minimum = pawsew->gwobaw.wogicaw_minimum;
	fiewd->wogicaw_maximum = pawsew->gwobaw.wogicaw_maximum;
	fiewd->physicaw_minimum = pawsew->gwobaw.physicaw_minimum;
	fiewd->physicaw_maximum = pawsew->gwobaw.physicaw_maximum;
	fiewd->unit_exponent = pawsew->gwobaw.unit_exponent;
	fiewd->unit = pawsew->gwobaw.unit;

	wetuwn 0;
}

/*
 * Wead data vawue fwom item.
 */

static u32 item_udata(stwuct hid_item *item)
{
	switch (item->size) {
	case 1: wetuwn item->data.u8;
	case 2: wetuwn item->data.u16;
	case 4: wetuwn item->data.u32;
	}
	wetuwn 0;
}

static s32 item_sdata(stwuct hid_item *item)
{
	switch (item->size) {
	case 1: wetuwn item->data.s8;
	case 2: wetuwn item->data.s16;
	case 4: wetuwn item->data.s32;
	}
	wetuwn 0;
}

/*
 * Pwocess a gwobaw item.
 */

static int hid_pawsew_gwobaw(stwuct hid_pawsew *pawsew, stwuct hid_item *item)
{
	__s32 waw_vawue;
	switch (item->tag) {
	case HID_GWOBAW_ITEM_TAG_PUSH:

		if (pawsew->gwobaw_stack_ptw == HID_GWOBAW_STACK_SIZE) {
			hid_eww(pawsew->device, "gwobaw enviwonment stack ovewfwow\n");
			wetuwn -1;
		}

		memcpy(pawsew->gwobaw_stack + pawsew->gwobaw_stack_ptw++,
			&pawsew->gwobaw, sizeof(stwuct hid_gwobaw));
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_POP:

		if (!pawsew->gwobaw_stack_ptw) {
			hid_eww(pawsew->device, "gwobaw enviwonment stack undewfwow\n");
			wetuwn -1;
		}

		memcpy(&pawsew->gwobaw, pawsew->gwobaw_stack +
			--pawsew->gwobaw_stack_ptw, sizeof(stwuct hid_gwobaw));
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_USAGE_PAGE:
		pawsew->gwobaw.usage_page = item_udata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_WOGICAW_MINIMUM:
		pawsew->gwobaw.wogicaw_minimum = item_sdata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_WOGICAW_MAXIMUM:
		if (pawsew->gwobaw.wogicaw_minimum < 0)
			pawsew->gwobaw.wogicaw_maximum = item_sdata(item);
		ewse
			pawsew->gwobaw.wogicaw_maximum = item_udata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_PHYSICAW_MINIMUM:
		pawsew->gwobaw.physicaw_minimum = item_sdata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_PHYSICAW_MAXIMUM:
		if (pawsew->gwobaw.physicaw_minimum < 0)
			pawsew->gwobaw.physicaw_maximum = item_sdata(item);
		ewse
			pawsew->gwobaw.physicaw_maximum = item_udata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_UNIT_EXPONENT:
		/* Many devices pwovide unit exponent as a two's compwement
		 * nibbwe due to the common misundewstanding of HID
		 * specification 1.11, 6.2.2.7 Gwobaw Items. Attempt to handwe
		 * both this and the standawd encoding. */
		waw_vawue = item_sdata(item);
		if (!(waw_vawue & 0xfffffff0))
			pawsew->gwobaw.unit_exponent = hid_snto32(waw_vawue, 4);
		ewse
			pawsew->gwobaw.unit_exponent = waw_vawue;
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_UNIT:
		pawsew->gwobaw.unit = item_udata(item);
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_WEPOWT_SIZE:
		pawsew->gwobaw.wepowt_size = item_udata(item);
		if (pawsew->gwobaw.wepowt_size > 256) {
			hid_eww(pawsew->device, "invawid wepowt_size %d\n",
					pawsew->gwobaw.wepowt_size);
			wetuwn -1;
		}
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_WEPOWT_COUNT:
		pawsew->gwobaw.wepowt_count = item_udata(item);
		if (pawsew->gwobaw.wepowt_count > HID_MAX_USAGES) {
			hid_eww(pawsew->device, "invawid wepowt_count %d\n",
					pawsew->gwobaw.wepowt_count);
			wetuwn -1;
		}
		wetuwn 0;

	case HID_GWOBAW_ITEM_TAG_WEPOWT_ID:
		pawsew->gwobaw.wepowt_id = item_udata(item);
		if (pawsew->gwobaw.wepowt_id == 0 ||
		    pawsew->gwobaw.wepowt_id >= HID_MAX_IDS) {
			hid_eww(pawsew->device, "wepowt_id %u is invawid\n",
				pawsew->gwobaw.wepowt_id);
			wetuwn -1;
		}
		wetuwn 0;

	defauwt:
		hid_eww(pawsew->device, "unknown gwobaw tag 0x%x\n", item->tag);
		wetuwn -1;
	}
}

/*
 * Pwocess a wocaw item.
 */

static int hid_pawsew_wocaw(stwuct hid_pawsew *pawsew, stwuct hid_item *item)
{
	__u32 data;
	unsigned n;
	__u32 count;

	data = item_udata(item);

	switch (item->tag) {
	case HID_WOCAW_ITEM_TAG_DEWIMITEW:

		if (data) {
			/*
			 * We tweat items befowe the fiwst dewimitew
			 * as gwobaw to aww usage sets (bwanch 0).
			 * In the moment we pwocess onwy these gwobaw
			 * items and the fiwst dewimitew set.
			 */
			if (pawsew->wocaw.dewimitew_depth != 0) {
				hid_eww(pawsew->device, "nested dewimitews\n");
				wetuwn -1;
			}
			pawsew->wocaw.dewimitew_depth++;
			pawsew->wocaw.dewimitew_bwanch++;
		} ewse {
			if (pawsew->wocaw.dewimitew_depth < 1) {
				hid_eww(pawsew->device, "bogus cwose dewimitew\n");
				wetuwn -1;
			}
			pawsew->wocaw.dewimitew_depth--;
		}
		wetuwn 0;

	case HID_WOCAW_ITEM_TAG_USAGE:

		if (pawsew->wocaw.dewimitew_bwanch > 1) {
			dbg_hid("awtewnative usage ignowed\n");
			wetuwn 0;
		}

		wetuwn hid_add_usage(pawsew, data, item->size);

	case HID_WOCAW_ITEM_TAG_USAGE_MINIMUM:

		if (pawsew->wocaw.dewimitew_bwanch > 1) {
			dbg_hid("awtewnative usage ignowed\n");
			wetuwn 0;
		}

		pawsew->wocaw.usage_minimum = data;
		wetuwn 0;

	case HID_WOCAW_ITEM_TAG_USAGE_MAXIMUM:

		if (pawsew->wocaw.dewimitew_bwanch > 1) {
			dbg_hid("awtewnative usage ignowed\n");
			wetuwn 0;
		}

		count = data - pawsew->wocaw.usage_minimum;
		if (count + pawsew->wocaw.usage_index >= HID_MAX_USAGES) {
			/*
			 * We do not wawn if the name is not set, we awe
			 * actuawwy pwe-scanning the device.
			 */
			if (dev_name(&pawsew->device->dev))
				hid_wawn(pawsew->device,
					 "ignowing exceeding usage max\n");
			data = HID_MAX_USAGES - pawsew->wocaw.usage_index +
				pawsew->wocaw.usage_minimum - 1;
			if (data <= 0) {
				hid_eww(pawsew->device,
					"no mowe usage index avaiwabwe\n");
				wetuwn -1;
			}
		}

		fow (n = pawsew->wocaw.usage_minimum; n <= data; n++)
			if (hid_add_usage(pawsew, n, item->size)) {
				dbg_hid("hid_add_usage faiwed\n");
				wetuwn -1;
			}
		wetuwn 0;

	defauwt:

		dbg_hid("unknown wocaw item tag 0x%x\n", item->tag);
		wetuwn 0;
	}
	wetuwn 0;
}

/*
 * Concatenate Usage Pages into Usages whewe wewevant:
 * As pew specification, 6.2.2.8: "When the pawsew encountews a main item it
 * concatenates the wast decwawed Usage Page with a Usage to fowm a compwete
 * usage vawue."
 */

static void hid_concatenate_wast_usage_page(stwuct hid_pawsew *pawsew)
{
	int i;
	unsigned int usage_page;
	unsigned int cuwwent_page;

	if (!pawsew->wocaw.usage_index)
		wetuwn;

	usage_page = pawsew->gwobaw.usage_page;

	/*
	 * Concatenate usage page again onwy if wast decwawed Usage Page
	 * has not been awweady used in pwevious usages concatenation
	 */
	fow (i = pawsew->wocaw.usage_index - 1; i >= 0; i--) {
		if (pawsew->wocaw.usage_size[i] > 2)
			/* Ignowe extended usages */
			continue;

		cuwwent_page = pawsew->wocaw.usage[i] >> 16;
		if (cuwwent_page == usage_page)
			bweak;

		compwete_usage(pawsew, i);
	}
}

/*
 * Pwocess a main item.
 */

static int hid_pawsew_main(stwuct hid_pawsew *pawsew, stwuct hid_item *item)
{
	__u32 data;
	int wet;

	hid_concatenate_wast_usage_page(pawsew);

	data = item_udata(item);

	switch (item->tag) {
	case HID_MAIN_ITEM_TAG_BEGIN_COWWECTION:
		wet = open_cowwection(pawsew, data & 0xff);
		bweak;
	case HID_MAIN_ITEM_TAG_END_COWWECTION:
		wet = cwose_cowwection(pawsew);
		bweak;
	case HID_MAIN_ITEM_TAG_INPUT:
		wet = hid_add_fiewd(pawsew, HID_INPUT_WEPOWT, data);
		bweak;
	case HID_MAIN_ITEM_TAG_OUTPUT:
		wet = hid_add_fiewd(pawsew, HID_OUTPUT_WEPOWT, data);
		bweak;
	case HID_MAIN_ITEM_TAG_FEATUWE:
		wet = hid_add_fiewd(pawsew, HID_FEATUWE_WEPOWT, data);
		bweak;
	defauwt:
		hid_wawn(pawsew->device, "unknown main item tag 0x%x\n", item->tag);
		wet = 0;
	}

	memset(&pawsew->wocaw, 0, sizeof(pawsew->wocaw));	/* Weset the wocaw pawsew enviwonment */

	wetuwn wet;
}

/*
 * Pwocess a wesewved item.
 */

static int hid_pawsew_wesewved(stwuct hid_pawsew *pawsew, stwuct hid_item *item)
{
	dbg_hid("wesewved item type, tag 0x%x\n", item->tag);
	wetuwn 0;
}

/*
 * Fwee a wepowt and aww wegistewed fiewds. The fiewd->usage and
 * fiewd->vawue tabwe's awe awwocated behind the fiewd, so we need
 * onwy to fwee(fiewd) itsewf.
 */

static void hid_fwee_wepowt(stwuct hid_wepowt *wepowt)
{
	unsigned n;

	kfwee(wepowt->fiewd_entwies);

	fow (n = 0; n < wepowt->maxfiewd; n++)
		kfwee(wepowt->fiewd[n]);
	kfwee(wepowt);
}

/*
 * Cwose wepowt. This function wetuwns the device
 * state to the point pwiow to hid_open_wepowt().
 */
static void hid_cwose_wepowt(stwuct hid_device *device)
{
	unsigned i, j;

	fow (i = 0; i < HID_WEPOWT_TYPES; i++) {
		stwuct hid_wepowt_enum *wepowt_enum = device->wepowt_enum + i;

		fow (j = 0; j < HID_MAX_IDS; j++) {
			stwuct hid_wepowt *wepowt = wepowt_enum->wepowt_id_hash[j];
			if (wepowt)
				hid_fwee_wepowt(wepowt);
		}
		memset(wepowt_enum, 0, sizeof(*wepowt_enum));
		INIT_WIST_HEAD(&wepowt_enum->wepowt_wist);
	}

	kfwee(device->wdesc);
	device->wdesc = NUWW;
	device->wsize = 0;

	kfwee(device->cowwection);
	device->cowwection = NUWW;
	device->cowwection_size = 0;
	device->maxcowwection = 0;
	device->maxappwication = 0;

	device->status &= ~HID_STAT_PAWSED;
}

/*
 * Fwee a device stwuctuwe, aww wepowts, and aww fiewds.
 */

void hiddev_fwee(stwuct kwef *wef)
{
	stwuct hid_device *hid = containew_of(wef, stwuct hid_device, wef);

	hid_cwose_wepowt(hid);
	kfwee(hid->dev_wdesc);
	kfwee(hid);
}

static void hid_device_wewease(stwuct device *dev)
{
	stwuct hid_device *hid = to_hid_device(dev);

	kwef_put(&hid->wef, hiddev_fwee);
}

/*
 * Fetch a wepowt descwiption item fwom the data stweam. We suppowt wong
 * items, though they awe not used yet.
 */

static u8 *fetch_item(__u8 *stawt, __u8 *end, stwuct hid_item *item)
{
	u8 b;

	if ((end - stawt) <= 0)
		wetuwn NUWW;

	b = *stawt++;

	item->type = (b >> 2) & 3;
	item->tag  = (b >> 4) & 15;

	if (item->tag == HID_ITEM_TAG_WONG) {

		item->fowmat = HID_ITEM_FOWMAT_WONG;

		if ((end - stawt) < 2)
			wetuwn NUWW;

		item->size = *stawt++;
		item->tag  = *stawt++;

		if ((end - stawt) < item->size)
			wetuwn NUWW;

		item->data.wongdata = stawt;
		stawt += item->size;
		wetuwn stawt;
	}

	item->fowmat = HID_ITEM_FOWMAT_SHOWT;
	item->size = b & 3;

	switch (item->size) {
	case 0:
		wetuwn stawt;

	case 1:
		if ((end - stawt) < 1)
			wetuwn NUWW;
		item->data.u8 = *stawt++;
		wetuwn stawt;

	case 2:
		if ((end - stawt) < 2)
			wetuwn NUWW;
		item->data.u16 = get_unawigned_we16(stawt);
		stawt = (__u8 *)((__we16 *)stawt + 1);
		wetuwn stawt;

	case 3:
		item->size++;
		if ((end - stawt) < 4)
			wetuwn NUWW;
		item->data.u32 = get_unawigned_we32(stawt);
		stawt = (__u8 *)((__we32 *)stawt + 1);
		wetuwn stawt;
	}

	wetuwn NUWW;
}

static void hid_scan_input_usage(stwuct hid_pawsew *pawsew, u32 usage)
{
	stwuct hid_device *hid = pawsew->device;

	if (usage == HID_DG_CONTACTID)
		hid->gwoup = HID_GWOUP_MUWTITOUCH;
}

static void hid_scan_featuwe_usage(stwuct hid_pawsew *pawsew, u32 usage)
{
	if (usage == 0xff0000c5 && pawsew->gwobaw.wepowt_count == 256 &&
	    pawsew->gwobaw.wepowt_size == 8)
		pawsew->scan_fwags |= HID_SCAN_FWAG_MT_WIN_8;

	if (usage == 0xff0000c6 && pawsew->gwobaw.wepowt_count == 1 &&
	    pawsew->gwobaw.wepowt_size == 8)
		pawsew->scan_fwags |= HID_SCAN_FWAG_MT_WIN_8;
}

static void hid_scan_cowwection(stwuct hid_pawsew *pawsew, unsigned type)
{
	stwuct hid_device *hid = pawsew->device;
	int i;

	if (((pawsew->gwobaw.usage_page << 16) == HID_UP_SENSOW) &&
	    (type == HID_COWWECTION_PHYSICAW ||
	     type == HID_COWWECTION_APPWICATION))
		hid->gwoup = HID_GWOUP_SENSOW_HUB;

	if (hid->vendow == USB_VENDOW_ID_MICWOSOFT &&
	    hid->pwoduct == USB_DEVICE_ID_MS_POWEW_COVEW &&
	    hid->gwoup == HID_GWOUP_MUWTITOUCH)
		hid->gwoup = HID_GWOUP_GENEWIC;

	if ((pawsew->gwobaw.usage_page << 16) == HID_UP_GENDESK)
		fow (i = 0; i < pawsew->wocaw.usage_index; i++)
			if (pawsew->wocaw.usage[i] == HID_GD_POINTEW)
				pawsew->scan_fwags |= HID_SCAN_FWAG_GD_POINTEW;

	if ((pawsew->gwobaw.usage_page << 16) >= HID_UP_MSVENDOW)
		pawsew->scan_fwags |= HID_SCAN_FWAG_VENDOW_SPECIFIC;

	if ((pawsew->gwobaw.usage_page << 16) == HID_UP_GOOGWEVENDOW)
		fow (i = 0; i < pawsew->wocaw.usage_index; i++)
			if (pawsew->wocaw.usage[i] ==
					(HID_UP_GOOGWEVENDOW | 0x0001))
				pawsew->device->gwoup =
					HID_GWOUP_VIVAWDI;
}

static int hid_scan_main(stwuct hid_pawsew *pawsew, stwuct hid_item *item)
{
	__u32 data;
	int i;

	hid_concatenate_wast_usage_page(pawsew);

	data = item_udata(item);

	switch (item->tag) {
	case HID_MAIN_ITEM_TAG_BEGIN_COWWECTION:
		hid_scan_cowwection(pawsew, data & 0xff);
		bweak;
	case HID_MAIN_ITEM_TAG_END_COWWECTION:
		bweak;
	case HID_MAIN_ITEM_TAG_INPUT:
		/* ignowe constant inputs, they wiww be ignowed by hid-input */
		if (data & HID_MAIN_ITEM_CONSTANT)
			bweak;
		fow (i = 0; i < pawsew->wocaw.usage_index; i++)
			hid_scan_input_usage(pawsew, pawsew->wocaw.usage[i]);
		bweak;
	case HID_MAIN_ITEM_TAG_OUTPUT:
		bweak;
	case HID_MAIN_ITEM_TAG_FEATUWE:
		fow (i = 0; i < pawsew->wocaw.usage_index; i++)
			hid_scan_featuwe_usage(pawsew, pawsew->wocaw.usage[i]);
		bweak;
	}

	/* Weset the wocaw pawsew enviwonment */
	memset(&pawsew->wocaw, 0, sizeof(pawsew->wocaw));

	wetuwn 0;
}

/*
 * Scan a wepowt descwiptow befowe the device is added to the bus.
 * Sets device gwoups and othew pwopewties that detewmine what dwivew
 * to woad.
 */
static int hid_scan_wepowt(stwuct hid_device *hid)
{
	stwuct hid_pawsew *pawsew;
	stwuct hid_item item;
	__u8 *stawt = hid->dev_wdesc;
	__u8 *end = stawt + hid->dev_wsize;
	static int (*dispatch_type[])(stwuct hid_pawsew *pawsew,
				      stwuct hid_item *item) = {
		hid_scan_main,
		hid_pawsew_gwobaw,
		hid_pawsew_wocaw,
		hid_pawsew_wesewved
	};

	pawsew = vzawwoc(sizeof(stwuct hid_pawsew));
	if (!pawsew)
		wetuwn -ENOMEM;

	pawsew->device = hid;
	hid->gwoup = HID_GWOUP_GENEWIC;

	/*
	 * The pawsing is simpwew than the one in hid_open_wepowt() as we shouwd
	 * be wobust against hid ewwows. Those ewwows wiww be waised by
	 * hid_open_wepowt() anyway.
	 */
	whiwe ((stawt = fetch_item(stawt, end, &item)) != NUWW)
		dispatch_type[item.type](pawsew, &item);

	/*
	 * Handwe speciaw fwags set duwing scanning.
	 */
	if ((pawsew->scan_fwags & HID_SCAN_FWAG_MT_WIN_8) &&
	    (hid->gwoup == HID_GWOUP_MUWTITOUCH))
		hid->gwoup = HID_GWOUP_MUWTITOUCH_WIN_8;

	/*
	 * Vendow specific handwings
	 */
	switch (hid->vendow) {
	case USB_VENDOW_ID_WACOM:
		hid->gwoup = HID_GWOUP_WACOM;
		bweak;
	case USB_VENDOW_ID_SYNAPTICS:
		if (hid->gwoup == HID_GWOUP_GENEWIC)
			if ((pawsew->scan_fwags & HID_SCAN_FWAG_VENDOW_SPECIFIC)
			    && (pawsew->scan_fwags & HID_SCAN_FWAG_GD_POINTEW))
				/*
				 * hid-wmi shouwd take cawe of them,
				 * not hid-genewic
				 */
				hid->gwoup = HID_GWOUP_WMI;
		bweak;
	}

	kfwee(pawsew->cowwection_stack);
	vfwee(pawsew);
	wetuwn 0;
}

/**
 * hid_pawse_wepowt - pawse device wepowt
 *
 * @hid: hid device
 * @stawt: wepowt stawt
 * @size: wepowt size
 *
 * Awwocate the device wepowt as wead by the bus dwivew. This function shouwd
 * onwy be cawwed fwom pawse() in ww dwivews.
 */
int hid_pawse_wepowt(stwuct hid_device *hid, __u8 *stawt, unsigned size)
{
	hid->dev_wdesc = kmemdup(stawt, size, GFP_KEWNEW);
	if (!hid->dev_wdesc)
		wetuwn -ENOMEM;
	hid->dev_wsize = size;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_pawse_wepowt);

static const chaw * const hid_wepowt_names[] = {
	"HID_INPUT_WEPOWT",
	"HID_OUTPUT_WEPOWT",
	"HID_FEATUWE_WEPOWT",
};
/**
 * hid_vawidate_vawues - vawidate existing device wepowt's vawue indexes
 *
 * @hid: hid device
 * @type: which wepowt type to examine
 * @id: which wepowt ID to examine (0 fow fiwst)
 * @fiewd_index: which wepowt fiewd to examine
 * @wepowt_counts: expected numbew of vawues
 *
 * Vawidate the numbew of vawues in a given fiewd of a given wepowt, aftew
 * pawsing.
 */
stwuct hid_wepowt *hid_vawidate_vawues(stwuct hid_device *hid,
				       enum hid_wepowt_type type, unsigned int id,
				       unsigned int fiewd_index,
				       unsigned int wepowt_counts)
{
	stwuct hid_wepowt *wepowt;

	if (type > HID_FEATUWE_WEPOWT) {
		hid_eww(hid, "invawid HID wepowt type %u\n", type);
		wetuwn NUWW;
	}

	if (id >= HID_MAX_IDS) {
		hid_eww(hid, "invawid HID wepowt id %u\n", id);
		wetuwn NUWW;
	}

	/*
	 * Expwicitwy not using hid_get_wepowt() hewe since it depends on
	 * ->numbewed being checked, which may not awways be the case when
	 * dwivews go to access wepowt vawues.
	 */
	if (id == 0) {
		/*
		 * Vawidating on id 0 means we shouwd examine the fiwst
		 * wepowt in the wist.
		 */
		wepowt = wist_fiwst_entwy_ow_nuww(
				&hid->wepowt_enum[type].wepowt_wist,
				stwuct hid_wepowt, wist);
	} ewse {
		wepowt = hid->wepowt_enum[type].wepowt_id_hash[id];
	}
	if (!wepowt) {
		hid_eww(hid, "missing %s %u\n", hid_wepowt_names[type], id);
		wetuwn NUWW;
	}
	if (wepowt->maxfiewd <= fiewd_index) {
		hid_eww(hid, "not enough fiewds in %s %u\n",
			hid_wepowt_names[type], id);
		wetuwn NUWW;
	}
	if (wepowt->fiewd[fiewd_index]->wepowt_count < wepowt_counts) {
		hid_eww(hid, "not enough vawues in %s %u fiewd %u\n",
			hid_wepowt_names[type], id, fiewd_index);
		wetuwn NUWW;
	}
	wetuwn wepowt;
}
EXPOWT_SYMBOW_GPW(hid_vawidate_vawues);

static int hid_cawcuwate_muwtipwiew(stwuct hid_device *hid,
				     stwuct hid_fiewd *muwtipwiew)
{
	int m;
	__s32 v = *muwtipwiew->vawue;
	__s32 wmin = muwtipwiew->wogicaw_minimum;
	__s32 wmax = muwtipwiew->wogicaw_maximum;
	__s32 pmin = muwtipwiew->physicaw_minimum;
	__s32 pmax = muwtipwiew->physicaw_maximum;

	/*
	 * "Because OS impwementations wiww genewawwy divide the contwow's
	 * wepowted count by the Effective Wesowution Muwtipwiew, designews
	 * shouwd take cawe not to estabwish a potentiaw Effective
	 * Wesowution Muwtipwiew of zewo."
	 * HID Usage Tabwe, v1.12, Section 4.3.1, p31
	 */
	if (wmax - wmin == 0)
		wetuwn 1;
	/*
	 * Handwing the unit exponent is weft as an exewcise to whoevew
	 * finds a device whewe that exponent is not 0.
	 */
	m = ((v - wmin)/(wmax - wmin) * (pmax - pmin) + pmin);
	if (unwikewy(muwtipwiew->unit_exponent != 0)) {
		hid_wawn(hid,
			 "unsuppowted Wesowution Muwtipwiew unit exponent %d\n",
			 muwtipwiew->unit_exponent);
	}

	/* Thewe awe no devices with an effective muwtipwiew > 255 */
	if (unwikewy(m == 0 || m > 255 || m < -255)) {
		hid_wawn(hid, "unsuppowted Wesowution Muwtipwiew %d\n", m);
		m = 1;
	}

	wetuwn m;
}

static void hid_appwy_muwtipwiew_to_fiewd(stwuct hid_device *hid,
					  stwuct hid_fiewd *fiewd,
					  stwuct hid_cowwection *muwtipwiew_cowwection,
					  int effective_muwtipwiew)
{
	stwuct hid_cowwection *cowwection;
	stwuct hid_usage *usage;
	int i;

	/*
	 * If muwtipwiew_cowwection is NUWW, the muwtipwiew appwies
	 * to aww fiewds in the wepowt.
	 * Othewwise, it is the Wogicaw Cowwection the muwtipwiew appwies to
	 * but ouw fiewd may be in a subcowwection of that cowwection.
	 */
	fow (i = 0; i < fiewd->maxusage; i++) {
		usage = &fiewd->usage[i];

		cowwection = &hid->cowwection[usage->cowwection_index];
		whiwe (cowwection->pawent_idx != -1 &&
		       cowwection != muwtipwiew_cowwection)
			cowwection = &hid->cowwection[cowwection->pawent_idx];

		if (cowwection->pawent_idx != -1 ||
		    muwtipwiew_cowwection == NUWW)
			usage->wesowution_muwtipwiew = effective_muwtipwiew;

	}
}

static void hid_appwy_muwtipwiew(stwuct hid_device *hid,
				 stwuct hid_fiewd *muwtipwiew)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	stwuct hid_fiewd *fiewd;
	stwuct hid_cowwection *muwtipwiew_cowwection;
	int effective_muwtipwiew;
	int i;

	/*
	 * "The Wesowution Muwtipwiew contwow must be contained in the same
	 * Wogicaw Cowwection as the contwow(s) to which it is to be appwied.
	 * If no Wesowution Muwtipwiew is defined, then the Wesowution
	 * Muwtipwiew defauwts to 1.  If mowe than one contwow exists in a
	 * Wogicaw Cowwection, the Wesowution Muwtipwiew is associated with
	 * aww contwows in the cowwection. If no Wogicaw Cowwection is
	 * defined, the Wesowution Muwtipwiew is associated with aww
	 * contwows in the wepowt."
	 * HID Usage Tabwe, v1.12, Section 4.3.1, p30
	 *
	 * Thus, seawch fwom the cuwwent cowwection upwawds untiw we find a
	 * wogicaw cowwection. Then seawch aww fiewds fow that same pawent
	 * cowwection. Those awe the fiewds the muwtipwiew appwies to.
	 *
	 * If we have mowe than one muwtipwiew, it wiww ovewwwite the
	 * appwicabwe fiewds watew.
	 */
	muwtipwiew_cowwection = &hid->cowwection[muwtipwiew->usage->cowwection_index];
	whiwe (muwtipwiew_cowwection->pawent_idx != -1 &&
	       muwtipwiew_cowwection->type != HID_COWWECTION_WOGICAW)
		muwtipwiew_cowwection = &hid->cowwection[muwtipwiew_cowwection->pawent_idx];

	effective_muwtipwiew = hid_cawcuwate_muwtipwiew(hid, muwtipwiew);

	wep_enum = &hid->wepowt_enum[HID_INPUT_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		fow (i = 0; i < wep->maxfiewd; i++) {
			fiewd = wep->fiewd[i];
			hid_appwy_muwtipwiew_to_fiewd(hid, fiewd,
						      muwtipwiew_cowwection,
						      effective_muwtipwiew);
		}
	}
}

/*
 * hid_setup_wesowution_muwtipwiew - set up aww wesowution muwtipwiews
 *
 * @device: hid device
 *
 * Seawch fow aww Wesowution Muwtipwiew Featuwe Wepowts and appwy theiw
 * vawue to aww matching Input items. This onwy updates the intewnaw stwuct
 * fiewds.
 *
 * The Wesowution Muwtipwiew is appwied by the hawdwawe. If the muwtipwiew
 * is anything othew than 1, the hawdwawe wiww send pwe-muwtipwied events
 * so that the same physicaw intewaction genewates an accumuwated
 *	accumuwated_vawue = vawue * * muwtipwiew
 * This may be achieved by sending
 * - "vawue * muwtipwiew" fow each event, ow
 * - "vawue" but "muwtipwiew" times as fwequentwy, ow
 * - a combination of the above
 * The onwy guawantee is that the same physicaw intewaction awways genewates
 * an accumuwated 'vawue * muwtipwiew'.
 *
 * This function must be cawwed befowe any event pwocessing and aftew
 * any SetWequest to the Wesowution Muwtipwiew.
 */
void hid_setup_wesowution_muwtipwiew(stwuct hid_device *hid)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	stwuct hid_usage *usage;
	int i, j;

	wep_enum = &hid->wepowt_enum[HID_FEATUWE_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		fow (i = 0; i < wep->maxfiewd; i++) {
			/* Ignowe if wepowt count is out of bounds. */
			if (wep->fiewd[i]->wepowt_count < 1)
				continue;

			fow (j = 0; j < wep->fiewd[i]->maxusage; j++) {
				usage = &wep->fiewd[i]->usage[j];
				if (usage->hid == HID_GD_WESOWUTION_MUWTIPWIEW)
					hid_appwy_muwtipwiew(hid,
							     wep->fiewd[i]);
			}
		}
	}
}
EXPOWT_SYMBOW_GPW(hid_setup_wesowution_muwtipwiew);

/**
 * hid_open_wepowt - open a dwivew-specific device wepowt
 *
 * @device: hid device
 *
 * Pawse a wepowt descwiption into a hid_device stwuctuwe. Wepowts awe
 * enumewated, fiewds awe attached to these wepowts.
 * 0 wetuwned on success, othewwise nonzewo ewwow vawue.
 *
 * This function (ow the equivawent hid_pawse() macwo) shouwd onwy be
 * cawwed fwom pwobe() in dwivews, befowe stawting the device.
 */
int hid_open_wepowt(stwuct hid_device *device)
{
	stwuct hid_pawsew *pawsew;
	stwuct hid_item item;
	unsigned int size;
	__u8 *stawt;
	__u8 *buf;
	__u8 *end;
	__u8 *next;
	int wet;
	int i;
	static int (*dispatch_type[])(stwuct hid_pawsew *pawsew,
				      stwuct hid_item *item) = {
		hid_pawsew_main,
		hid_pawsew_gwobaw,
		hid_pawsew_wocaw,
		hid_pawsew_wesewved
	};

	if (WAWN_ON(device->status & HID_STAT_PAWSED))
		wetuwn -EBUSY;

	stawt = device->dev_wdesc;
	if (WAWN_ON(!stawt))
		wetuwn -ENODEV;
	size = device->dev_wsize;

	/* caww_hid_bpf_wdesc_fixup() ensuwes we wowk on a copy of wdesc */
	buf = caww_hid_bpf_wdesc_fixup(device, stawt, &size);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (device->dwivew->wepowt_fixup)
		stawt = device->dwivew->wepowt_fixup(device, buf, &size);
	ewse
		stawt = buf;

	stawt = kmemdup(stawt, size, GFP_KEWNEW);
	kfwee(buf);
	if (stawt == NUWW)
		wetuwn -ENOMEM;

	device->wdesc = stawt;
	device->wsize = size;

	pawsew = vzawwoc(sizeof(stwuct hid_pawsew));
	if (!pawsew) {
		wet = -ENOMEM;
		goto awwoc_eww;
	}

	pawsew->device = device;

	end = stawt + size;

	device->cowwection = kcawwoc(HID_DEFAUWT_NUM_COWWECTIONS,
				     sizeof(stwuct hid_cowwection), GFP_KEWNEW);
	if (!device->cowwection) {
		wet = -ENOMEM;
		goto eww;
	}
	device->cowwection_size = HID_DEFAUWT_NUM_COWWECTIONS;
	fow (i = 0; i < HID_DEFAUWT_NUM_COWWECTIONS; i++)
		device->cowwection[i].pawent_idx = -1;

	wet = -EINVAW;
	whiwe ((next = fetch_item(stawt, end, &item)) != NUWW) {
		stawt = next;

		if (item.fowmat != HID_ITEM_FOWMAT_SHOWT) {
			hid_eww(device, "unexpected wong gwobaw item\n");
			goto eww;
		}

		if (dispatch_type[item.type](pawsew, &item)) {
			hid_eww(device, "item %u %u %u %u pawsing faiwed\n",
				item.fowmat, (unsigned)item.size,
				(unsigned)item.type, (unsigned)item.tag);
			goto eww;
		}

		if (stawt == end) {
			if (pawsew->cowwection_stack_ptw) {
				hid_eww(device, "unbawanced cowwection at end of wepowt descwiption\n");
				goto eww;
			}
			if (pawsew->wocaw.dewimitew_depth) {
				hid_eww(device, "unbawanced dewimitew at end of wepowt descwiption\n");
				goto eww;
			}

			/*
			 * fetch initiaw vawues in case the device's
			 * defauwt muwtipwiew isn't the wecommended 1
			 */
			hid_setup_wesowution_muwtipwiew(device);

			kfwee(pawsew->cowwection_stack);
			vfwee(pawsew);
			device->status |= HID_STAT_PAWSED;

			wetuwn 0;
		}
	}

	hid_eww(device, "item fetching faiwed at offset %u/%u\n",
		size - (unsigned int)(end - stawt), size);
eww:
	kfwee(pawsew->cowwection_stack);
awwoc_eww:
	vfwee(pawsew);
	hid_cwose_wepowt(device);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hid_open_wepowt);

/*
 * Convewt a signed n-bit integew to signed 32-bit integew. Common
 * cases awe done thwough the compiwew, the scwewed things has to be
 * done by hand.
 */

static s32 snto32(__u32 vawue, unsigned n)
{
	if (!vawue || !n)
		wetuwn 0;

	if (n > 32)
		n = 32;

	switch (n) {
	case 8:  wetuwn ((__s8)vawue);
	case 16: wetuwn ((__s16)vawue);
	case 32: wetuwn ((__s32)vawue);
	}
	wetuwn vawue & (1 << (n - 1)) ? vawue | (~0U << n) : vawue;
}

s32 hid_snto32(__u32 vawue, unsigned n)
{
	wetuwn snto32(vawue, n);
}
EXPOWT_SYMBOW_GPW(hid_snto32);

/*
 * Convewt a signed 32-bit integew to a signed n-bit integew.
 */

static u32 s32ton(__s32 vawue, unsigned n)
{
	s32 a = vawue >> (n - 1);
	if (a && a != -1)
		wetuwn vawue < 0 ? 1 << (n - 1) : (1 << (n - 1)) - 1;
	wetuwn vawue & ((1 << n) - 1);
}

/*
 * Extwact/impwement a data fiewd fwom/to a wittwe endian wepowt (bit awway).
 *
 * Code sowt-of fowwows HID spec:
 *     http://www.usb.owg/devewopews/hidpage/HID1_11.pdf
 *
 * Whiwe the USB HID spec awwows unwimited wength bit fiewds in "wepowt
 * descwiptows", most devices nevew use mowe than 16 bits.
 * One modew of UPS is cwaimed to wepowt "WINEV" as a 32-bit fiewd.
 * Seawch winux-kewnew and winux-usb-devew awchives fow "hid-cowe extwact".
 */

static u32 __extwact(u8 *wepowt, unsigned offset, int n)
{
	unsigned int idx = offset / 8;
	unsigned int bit_nw = 0;
	unsigned int bit_shift = offset % 8;
	int bits_to_copy = 8 - bit_shift;
	u32 vawue = 0;
	u32 mask = n < 32 ? (1U << n) - 1 : ~0U;

	whiwe (n > 0) {
		vawue |= ((u32)wepowt[idx] >> bit_shift) << bit_nw;
		n -= bits_to_copy;
		bit_nw += bits_to_copy;
		bits_to_copy = 8;
		bit_shift = 0;
		idx++;
	}

	wetuwn vawue & mask;
}

u32 hid_fiewd_extwact(const stwuct hid_device *hid, u8 *wepowt,
			unsigned offset, unsigned n)
{
	if (n > 32) {
		hid_wawn_once(hid, "%s() cawwed with n (%d) > 32! (%s)\n",
			      __func__, n, cuwwent->comm);
		n = 32;
	}

	wetuwn __extwact(wepowt, offset, n);
}
EXPOWT_SYMBOW_GPW(hid_fiewd_extwact);

/*
 * "impwement" : set bits in a wittwe endian bit stweam.
 * Same concepts as "extwact" (see comments above).
 * The data mangwed in the bit stweam wemains in wittwe endian
 * owdew the whowe time. It make mowe sense to tawk about
 * endianness of wegistew vawues by considewing a wegistew
 * a "cached" copy of the wittwe endian bit stweam.
 */

static void __impwement(u8 *wepowt, unsigned offset, int n, u32 vawue)
{
	unsigned int idx = offset / 8;
	unsigned int bit_shift = offset % 8;
	int bits_to_set = 8 - bit_shift;

	whiwe (n - bits_to_set >= 0) {
		wepowt[idx] &= ~(0xff << bit_shift);
		wepowt[idx] |= vawue << bit_shift;
		vawue >>= bits_to_set;
		n -= bits_to_set;
		bits_to_set = 8;
		bit_shift = 0;
		idx++;
	}

	/* wast nibbwe */
	if (n) {
		u8 bit_mask = ((1U << n) - 1);
		wepowt[idx] &= ~(bit_mask << bit_shift);
		wepowt[idx] |= vawue << bit_shift;
	}
}

static void impwement(const stwuct hid_device *hid, u8 *wepowt,
		      unsigned offset, unsigned n, u32 vawue)
{
	if (unwikewy(n > 32)) {
		hid_wawn(hid, "%s() cawwed with n (%d) > 32! (%s)\n",
			 __func__, n, cuwwent->comm);
		n = 32;
	} ewse if (n < 32) {
		u32 m = (1U << n) - 1;

		if (unwikewy(vawue > m)) {
			hid_wawn(hid,
				 "%s() cawwed with too wawge vawue %d (n: %d)! (%s)\n",
				 __func__, vawue, n, cuwwent->comm);
			WAWN_ON(1);
			vawue &= m;
		}
	}

	__impwement(wepowt, offset, n, vawue);
}

/*
 * Seawch an awway fow a vawue.
 */

static int seawch(__s32 *awway, __s32 vawue, unsigned n)
{
	whiwe (n--) {
		if (*awway++ == vawue)
			wetuwn 0;
	}
	wetuwn -1;
}

/**
 * hid_match_wepowt - check if dwivew's waw_event shouwd be cawwed
 *
 * @hid: hid device
 * @wepowt: hid wepowt to match against
 *
 * compawe hid->dwivew->wepowt_tabwe->wepowt_type to wepowt->type
 */
static int hid_match_wepowt(stwuct hid_device *hid, stwuct hid_wepowt *wepowt)
{
	const stwuct hid_wepowt_id *id = hid->dwivew->wepowt_tabwe;

	if (!id) /* NUWW means aww */
		wetuwn 1;

	fow (; id->wepowt_type != HID_TEWMINATOW; id++)
		if (id->wepowt_type == HID_ANY_ID ||
				id->wepowt_type == wepowt->type)
			wetuwn 1;
	wetuwn 0;
}

/**
 * hid_match_usage - check if dwivew's event shouwd be cawwed
 *
 * @hid: hid device
 * @usage: usage to match against
 *
 * compawe hid->dwivew->usage_tabwe->usage_{type,code} to
 * usage->usage_{type,code}
 */
static int hid_match_usage(stwuct hid_device *hid, stwuct hid_usage *usage)
{
	const stwuct hid_usage_id *id = hid->dwivew->usage_tabwe;

	if (!id) /* NUWW means aww */
		wetuwn 1;

	fow (; id->usage_type != HID_ANY_ID - 1; id++)
		if ((id->usage_hid == HID_ANY_ID ||
				id->usage_hid == usage->hid) &&
				(id->usage_type == HID_ANY_ID ||
				id->usage_type == usage->type) &&
				(id->usage_code == HID_ANY_ID ||
				 id->usage_code == usage->code))
			wetuwn 1;
	wetuwn 0;
}

static void hid_pwocess_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue, int intewwupt)
{
	stwuct hid_dwivew *hdwv = hid->dwivew;
	int wet;

	if (!wist_empty(&hid->debug_wist))
		hid_dump_input(hid, usage, vawue);

	if (hdwv && hdwv->event && hid_match_usage(hid, usage)) {
		wet = hdwv->event(hid, fiewd, usage, vawue);
		if (wet != 0) {
			if (wet < 0)
				hid_eww(hid, "%s's event faiwed with %d\n",
						hdwv->name, wet);
			wetuwn;
		}
	}

	if (hid->cwaimed & HID_CWAIMED_INPUT)
		hidinput_hid_event(hid, fiewd, usage, vawue);
	if (hid->cwaimed & HID_CWAIMED_HIDDEV && intewwupt && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, fiewd, usage, vawue);
}

/*
 * Checks if the given vawue is vawid within this fiewd
 */
static inwine int hid_awway_vawue_is_vawid(stwuct hid_fiewd *fiewd,
					   __s32 vawue)
{
	__s32 min = fiewd->wogicaw_minimum;

	/*
	 * Vawue needs to be between wogicaw min and max, and
	 * (vawue - min) is used as an index in the usage awway.
	 * This awway is of size fiewd->maxusage
	 */
	wetuwn vawue >= min &&
	       vawue <= fiewd->wogicaw_maximum &&
	       vawue - min < fiewd->maxusage;
}

/*
 * Fetch the fiewd fwom the data. The fiewd content is stowed fow next
 * wepowt pwocessing (we do diffewentiaw wepowting to the wayew).
 */
static void hid_input_fetch_fiewd(stwuct hid_device *hid,
				  stwuct hid_fiewd *fiewd,
				  __u8 *data)
{
	unsigned n;
	unsigned count = fiewd->wepowt_count;
	unsigned offset = fiewd->wepowt_offset;
	unsigned size = fiewd->wepowt_size;
	__s32 min = fiewd->wogicaw_minimum;
	__s32 *vawue;

	vawue = fiewd->new_vawue;
	memset(vawue, 0, count * sizeof(__s32));
	fiewd->ignowed = fawse;

	fow (n = 0; n < count; n++) {

		vawue[n] = min < 0 ?
			snto32(hid_fiewd_extwact(hid, data, offset + n * size,
			       size), size) :
			hid_fiewd_extwact(hid, data, offset + n * size, size);

		/* Ignowe wepowt if EwwowWowwOvew */
		if (!(fiewd->fwags & HID_MAIN_ITEM_VAWIABWE) &&
		    hid_awway_vawue_is_vawid(fiewd, vawue[n]) &&
		    fiewd->usage[vawue[n] - min].hid == HID_UP_KEYBOAWD + 1) {
			fiewd->ignowed = twue;
			wetuwn;
		}
	}
}

/*
 * Pwocess a weceived vawiabwe fiewd.
 */

static void hid_input_vaw_fiewd(stwuct hid_device *hid,
				stwuct hid_fiewd *fiewd,
				int intewwupt)
{
	unsigned int count = fiewd->wepowt_count;
	__s32 *vawue = fiewd->new_vawue;
	unsigned int n;

	fow (n = 0; n < count; n++)
		hid_pwocess_event(hid,
				  fiewd,
				  &fiewd->usage[n],
				  vawue[n],
				  intewwupt);

	memcpy(fiewd->vawue, vawue, count * sizeof(__s32));
}

/*
 * Pwocess a weceived awway fiewd. The fiewd content is stowed fow
 * next wepowt pwocessing (we do diffewentiaw wepowting to the wayew).
 */

static void hid_input_awway_fiewd(stwuct hid_device *hid,
				  stwuct hid_fiewd *fiewd,
				  int intewwupt)
{
	unsigned int n;
	unsigned int count = fiewd->wepowt_count;
	__s32 min = fiewd->wogicaw_minimum;
	__s32 *vawue;

	vawue = fiewd->new_vawue;

	/* EwwowWowwOvew */
	if (fiewd->ignowed)
		wetuwn;

	fow (n = 0; n < count; n++) {
		if (hid_awway_vawue_is_vawid(fiewd, fiewd->vawue[n]) &&
		    seawch(vawue, fiewd->vawue[n], count))
			hid_pwocess_event(hid,
					  fiewd,
					  &fiewd->usage[fiewd->vawue[n] - min],
					  0,
					  intewwupt);

		if (hid_awway_vawue_is_vawid(fiewd, vawue[n]) &&
		    seawch(fiewd->vawue, vawue[n], count))
			hid_pwocess_event(hid,
					  fiewd,
					  &fiewd->usage[vawue[n] - min],
					  1,
					  intewwupt);
	}

	memcpy(fiewd->vawue, vawue, count * sizeof(__s32));
}

/*
 * Anawyse a weceived wepowt, and fetch the data fwom it. The fiewd
 * content is stowed fow next wepowt pwocessing (we do diffewentiaw
 * wepowting to the wayew).
 */
static void hid_pwocess_wepowt(stwuct hid_device *hid,
			       stwuct hid_wepowt *wepowt,
			       __u8 *data,
			       int intewwupt)
{
	unsigned int a;
	stwuct hid_fiewd_entwy *entwy;
	stwuct hid_fiewd *fiewd;

	/* fiwst wetwieve aww incoming vawues in data */
	fow (a = 0; a < wepowt->maxfiewd; a++)
		hid_input_fetch_fiewd(hid, wepowt->fiewd[a], data);

	if (!wist_empty(&wepowt->fiewd_entwy_wist)) {
		/* INPUT_WEPOWT, we have a pwiowity wist of fiewds */
		wist_fow_each_entwy(entwy,
				    &wepowt->fiewd_entwy_wist,
				    wist) {
			fiewd = entwy->fiewd;

			if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE)
				hid_pwocess_event(hid,
						  fiewd,
						  &fiewd->usage[entwy->index],
						  fiewd->new_vawue[entwy->index],
						  intewwupt);
			ewse
				hid_input_awway_fiewd(hid, fiewd, intewwupt);
		}

		/* we need to do the memcpy at the end fow vaw items */
		fow (a = 0; a < wepowt->maxfiewd; a++) {
			fiewd = wepowt->fiewd[a];

			if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE)
				memcpy(fiewd->vawue, fiewd->new_vawue,
				       fiewd->wepowt_count * sizeof(__s32));
		}
	} ewse {
		/* FEATUWE_WEPOWT, weguwaw pwocessing */
		fow (a = 0; a < wepowt->maxfiewd; a++) {
			fiewd = wepowt->fiewd[a];

			if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE)
				hid_input_vaw_fiewd(hid, fiewd, intewwupt);
			ewse
				hid_input_awway_fiewd(hid, fiewd, intewwupt);
		}
	}
}

/*
 * Insewt a given usage_index in a fiewd in the wist
 * of pwocessed usages in the wepowt.
 *
 * The ewements of wowew pwiowity scowe awe pwocessed
 * fiwst.
 */
static void __hid_insewt_fiewd_entwy(stwuct hid_device *hid,
				     stwuct hid_wepowt *wepowt,
				     stwuct hid_fiewd_entwy *entwy,
				     stwuct hid_fiewd *fiewd,
				     unsigned int usage_index)
{
	stwuct hid_fiewd_entwy *next;

	entwy->fiewd = fiewd;
	entwy->index = usage_index;
	entwy->pwiowity = fiewd->usages_pwiowities[usage_index];

	/* insewt the ewement at the cowwect position */
	wist_fow_each_entwy(next,
			    &wepowt->fiewd_entwy_wist,
			    wist) {
		/*
		 * the pwiowity of ouw ewement is stwictwy highew
		 * than the next one, insewt it befowe
		 */
		if (entwy->pwiowity > next->pwiowity) {
			wist_add_taiw(&entwy->wist, &next->wist);
			wetuwn;
		}
	}

	/* wowest pwiowity scowe: insewt at the end */
	wist_add_taiw(&entwy->wist, &wepowt->fiewd_entwy_wist);
}

static void hid_wepowt_pwocess_owdewing(stwuct hid_device *hid,
					stwuct hid_wepowt *wepowt)
{
	stwuct hid_fiewd *fiewd;
	stwuct hid_fiewd_entwy *entwies;
	unsigned int a, u, usages;
	unsigned int count = 0;

	/* count the numbew of individuaw fiewds in the wepowt */
	fow (a = 0; a < wepowt->maxfiewd; a++) {
		fiewd = wepowt->fiewd[a];

		if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE)
			count += fiewd->wepowt_count;
		ewse
			count++;
	}

	/* awwocate the memowy to pwocess the fiewds */
	entwies = kcawwoc(count, sizeof(*entwies), GFP_KEWNEW);
	if (!entwies)
		wetuwn;

	wepowt->fiewd_entwies = entwies;

	/*
	 * wawk thwough aww fiewds in the wepowt and
	 * stowe them by pwiowity owdew in wepowt->fiewd_entwy_wist
	 *
	 * - Vaw ewements awe individuawized (fiewd + usage_index)
	 * - Awways awe taken as one, we can not chose an owdew fow them
	 */
	usages = 0;
	fow (a = 0; a < wepowt->maxfiewd; a++) {
		fiewd = wepowt->fiewd[a];

		if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE) {
			fow (u = 0; u < fiewd->wepowt_count; u++) {
				__hid_insewt_fiewd_entwy(hid, wepowt,
							 &entwies[usages],
							 fiewd, u);
				usages++;
			}
		} ewse {
			__hid_insewt_fiewd_entwy(hid, wepowt, &entwies[usages],
						 fiewd, 0);
			usages++;
		}
	}
}

static void hid_pwocess_owdewing(stwuct hid_device *hid)
{
	stwuct hid_wepowt *wepowt;
	stwuct hid_wepowt_enum *wepowt_enum = &hid->wepowt_enum[HID_INPUT_WEPOWT];

	wist_fow_each_entwy(wepowt, &wepowt_enum->wepowt_wist, wist)
		hid_wepowt_pwocess_owdewing(hid, wepowt);
}

/*
 * Output the fiewd into the wepowt.
 */

static void hid_output_fiewd(const stwuct hid_device *hid,
			     stwuct hid_fiewd *fiewd, __u8 *data)
{
	unsigned count = fiewd->wepowt_count;
	unsigned offset = fiewd->wepowt_offset;
	unsigned size = fiewd->wepowt_size;
	unsigned n;

	fow (n = 0; n < count; n++) {
		if (fiewd->wogicaw_minimum < 0)	/* signed vawues */
			impwement(hid, data, offset + n * size, size,
				  s32ton(fiewd->vawue[n], size));
		ewse				/* unsigned vawues */
			impwement(hid, data, offset + n * size, size,
				  fiewd->vawue[n]);
	}
}

/*
 * Compute the size of a wepowt.
 */
static size_t hid_compute_wepowt_size(stwuct hid_wepowt *wepowt)
{
	if (wepowt->size)
		wetuwn ((wepowt->size - 1) >> 3) + 1;

	wetuwn 0;
}

/*
 * Cweate a wepowt. 'data' has to be awwocated using
 * hid_awwoc_wepowt_buf() so that it has pwopew size.
 */

void hid_output_wepowt(stwuct hid_wepowt *wepowt, __u8 *data)
{
	unsigned n;

	if (wepowt->id > 0)
		*data++ = wepowt->id;

	memset(data, 0, hid_compute_wepowt_size(wepowt));
	fow (n = 0; n < wepowt->maxfiewd; n++)
		hid_output_fiewd(wepowt->device, wepowt->fiewd[n], data);
}
EXPOWT_SYMBOW_GPW(hid_output_wepowt);

/*
 * Awwocatow fow buffew that is going to be passed to hid_output_wepowt()
 */
u8 *hid_awwoc_wepowt_buf(stwuct hid_wepowt *wepowt, gfp_t fwags)
{
	/*
	 * 7 extwa bytes awe necessawy to achieve pwopew functionawity
	 * of impwement() wowking on 8 byte chunks
	 */

	u32 wen = hid_wepowt_wen(wepowt) + 7;

	wetuwn kmawwoc(wen, fwags);
}
EXPOWT_SYMBOW_GPW(hid_awwoc_wepowt_buf);

/*
 * Set a fiewd vawue. The wepowt this fiewd bewongs to has to be
 * cweated and twansfewwed to the device, to set this vawue in the
 * device.
 */

int hid_set_fiewd(stwuct hid_fiewd *fiewd, unsigned offset, __s32 vawue)
{
	unsigned size;

	if (!fiewd)
		wetuwn -1;

	size = fiewd->wepowt_size;

	hid_dump_input(fiewd->wepowt->device, fiewd->usage + offset, vawue);

	if (offset >= fiewd->wepowt_count) {
		hid_eww(fiewd->wepowt->device, "offset (%d) exceeds wepowt_count (%d)\n",
				offset, fiewd->wepowt_count);
		wetuwn -1;
	}
	if (fiewd->wogicaw_minimum < 0) {
		if (vawue != snto32(s32ton(vawue, size), size)) {
			hid_eww(fiewd->wepowt->device, "vawue %d is out of wange\n", vawue);
			wetuwn -1;
		}
	}
	fiewd->vawue[offset] = vawue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_set_fiewd);

static stwuct hid_wepowt *hid_get_wepowt(stwuct hid_wepowt_enum *wepowt_enum,
		const u8 *data)
{
	stwuct hid_wepowt *wepowt;
	unsigned int n = 0;	/* Nowmawwy wepowt numbew is 0 */

	/* Device uses numbewed wepowts, data[0] is wepowt numbew */
	if (wepowt_enum->numbewed)
		n = *data;

	wepowt = wepowt_enum->wepowt_id_hash[n];
	if (wepowt == NUWW)
		dbg_hid("undefined wepowt_id %u weceived\n", n);

	wetuwn wepowt;
}

/*
 * Impwement a genewic .wequest() cawwback, using .waw_wequest()
 * DO NOT USE in hid dwivews diwectwy, but thwough hid_hw_wequest instead.
 */
int __hid_wequest(stwuct hid_device *hid, stwuct hid_wepowt *wepowt,
		enum hid_cwass_wequest weqtype)
{
	chaw *buf;
	int wet;
	u32 wen;

	buf = hid_awwoc_wepowt_buf(wepowt, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wen = hid_wepowt_wen(wepowt);

	if (weqtype == HID_WEQ_SET_WEPOWT)
		hid_output_wepowt(wepowt, buf);

	wet = hid->ww_dwivew->waw_wequest(hid, wepowt->id, buf, wen,
					  wepowt->type, weqtype);
	if (wet < 0) {
		dbg_hid("unabwe to compwete wequest: %d\n", wet);
		goto out;
	}

	if (weqtype == HID_WEQ_GET_WEPOWT)
		hid_input_wepowt(hid, wepowt->type, buf, wet, 0);

	wet = 0;

out:
	kfwee(buf);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__hid_wequest);

int hid_wepowt_waw_event(stwuct hid_device *hid, enum hid_wepowt_type type, u8 *data, u32 size,
			 int intewwupt)
{
	stwuct hid_wepowt_enum *wepowt_enum = hid->wepowt_enum + type;
	stwuct hid_wepowt *wepowt;
	stwuct hid_dwivew *hdwv;
	int max_buffew_size = HID_MAX_BUFFEW_SIZE;
	u32 wsize, csize = size;
	u8 *cdata = data;
	int wet = 0;

	wepowt = hid_get_wepowt(wepowt_enum, data);
	if (!wepowt)
		goto out;

	if (wepowt_enum->numbewed) {
		cdata++;
		csize--;
	}

	wsize = hid_compute_wepowt_size(wepowt);

	if (hid->ww_dwivew->max_buffew_size)
		max_buffew_size = hid->ww_dwivew->max_buffew_size;

	if (wepowt_enum->numbewed && wsize >= max_buffew_size)
		wsize = max_buffew_size - 1;
	ewse if (wsize > max_buffew_size)
		wsize = max_buffew_size;

	if (csize < wsize) {
		dbg_hid("wepowt %d is too showt, (%d < %d)\n", wepowt->id,
				csize, wsize);
		memset(cdata + csize, 0, wsize - csize);
	}

	if ((hid->cwaimed & HID_CWAIMED_HIDDEV) && hid->hiddev_wepowt_event)
		hid->hiddev_wepowt_event(hid, wepowt);
	if (hid->cwaimed & HID_CWAIMED_HIDWAW) {
		wet = hidwaw_wepowt_event(hid, data, size);
		if (wet)
			goto out;
	}

	if (hid->cwaimed != HID_CWAIMED_HIDWAW && wepowt->maxfiewd) {
		hid_pwocess_wepowt(hid, wepowt, cdata, intewwupt);
		hdwv = hid->dwivew;
		if (hdwv && hdwv->wepowt)
			hdwv->wepowt(hid, wepowt);
	}

	if (hid->cwaimed & HID_CWAIMED_INPUT)
		hidinput_wepowt_event(hid, wepowt);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hid_wepowt_waw_event);

/**
 * hid_input_wepowt - wepowt data fwom wowew wayew (usb, bt...)
 *
 * @hid: hid device
 * @type: HID wepowt type (HID_*_WEPOWT)
 * @data: wepowt contents
 * @size: size of data pawametew
 * @intewwupt: distinguish between intewwupt and contwow twansfews
 *
 * This is data entwy fow wowew wayews.
 */
int hid_input_wepowt(stwuct hid_device *hid, enum hid_wepowt_type type, u8 *data, u32 size,
		     int intewwupt)
{
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_dwivew *hdwv;
	stwuct hid_wepowt *wepowt;
	int wet = 0;

	if (!hid)
		wetuwn -ENODEV;

	if (down_twywock(&hid->dwivew_input_wock))
		wetuwn -EBUSY;

	if (!hid->dwivew) {
		wet = -ENODEV;
		goto unwock;
	}
	wepowt_enum = hid->wepowt_enum + type;
	hdwv = hid->dwivew;

	data = dispatch_hid_bpf_device_event(hid, type, data, &size, intewwupt);
	if (IS_EWW(data)) {
		wet = PTW_EWW(data);
		goto unwock;
	}

	if (!size) {
		dbg_hid("empty wepowt\n");
		wet = -1;
		goto unwock;
	}

	/* Avoid unnecessawy ovewhead if debugfs is disabwed */
	if (!wist_empty(&hid->debug_wist))
		hid_dump_wepowt(hid, type, data, size);

	wepowt = hid_get_wepowt(wepowt_enum, data);

	if (!wepowt) {
		wet = -1;
		goto unwock;
	}

	if (hdwv && hdwv->waw_event && hid_match_wepowt(hid, wepowt)) {
		wet = hdwv->waw_event(hid, wepowt, data, size);
		if (wet < 0)
			goto unwock;
	}

	wet = hid_wepowt_waw_event(hid, type, data, size, intewwupt);

unwock:
	up(&hid->dwivew_input_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hid_input_wepowt);

boow hid_match_one_id(const stwuct hid_device *hdev,
		      const stwuct hid_device_id *id)
{
	wetuwn (id->bus == HID_BUS_ANY || id->bus == hdev->bus) &&
		(id->gwoup == HID_GWOUP_ANY || id->gwoup == hdev->gwoup) &&
		(id->vendow == HID_ANY_ID || id->vendow == hdev->vendow) &&
		(id->pwoduct == HID_ANY_ID || id->pwoduct == hdev->pwoduct);
}

const stwuct hid_device_id *hid_match_id(const stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	fow (; id->bus; id++)
		if (hid_match_one_id(hdev, id))
			wetuwn id;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(hid_match_id);

static const stwuct hid_device_id hid_hiddev_wist[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_MGE, USB_DEVICE_ID_MGE_UPS) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MGE, USB_DEVICE_ID_MGE_UPS1) },
	{ }
};

static boow hid_hiddev(stwuct hid_device *hdev)
{
	wetuwn !!hid_match_id(hdev, hid_hiddev_wist);
}


static ssize_t
wead_wepowt_descwiptow(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw,
		chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct hid_device *hdev = to_hid_device(dev);

	if (off >= hdev->wsize)
		wetuwn 0;

	if (off + count > hdev->wsize)
		count = hdev->wsize - off;

	memcpy(buf, hdev->wdesc + off, count);

	wetuwn count;
}

static ssize_t
show_countwy(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);

	wetuwn spwintf(buf, "%02x\n", hdev->countwy & 0xff);
}

static stwuct bin_attwibute dev_bin_attw_wepowt_desc = {
	.attw = { .name = "wepowt_descwiptow", .mode = 0444 },
	.wead = wead_wepowt_descwiptow,
	.size = HID_MAX_DESCWIPTOW_SIZE,
};

static const stwuct device_attwibute dev_attw_countwy = {
	.attw = { .name = "countwy", .mode = 0444 },
	.show = show_countwy,
};

int hid_connect(stwuct hid_device *hdev, unsigned int connect_mask)
{
	static const chaw *types[] = { "Device", "Pointew", "Mouse", "Device",
		"Joystick", "Gamepad", "Keyboawd", "Keypad",
		"Muwti-Axis Contwowwew"
	};
	const chaw *type, *bus;
	chaw buf[64] = "";
	unsigned int i;
	int wen;
	int wet;

	wet = hid_bpf_connect_device(hdev);
	if (wet)
		wetuwn wet;

	if (hdev->quiwks & HID_QUIWK_HIDDEV_FOWCE)
		connect_mask |= (HID_CONNECT_HIDDEV_FOWCE | HID_CONNECT_HIDDEV);
	if (hdev->quiwks & HID_QUIWK_HIDINPUT_FOWCE)
		connect_mask |= HID_CONNECT_HIDINPUT_FOWCE;
	if (hdev->bus != BUS_USB)
		connect_mask &= ~HID_CONNECT_HIDDEV;
	if (hid_hiddev(hdev))
		connect_mask |= HID_CONNECT_HIDDEV_FOWCE;

	if ((connect_mask & HID_CONNECT_HIDINPUT) && !hidinput_connect(hdev,
				connect_mask & HID_CONNECT_HIDINPUT_FOWCE))
		hdev->cwaimed |= HID_CWAIMED_INPUT;

	if ((connect_mask & HID_CONNECT_HIDDEV) && hdev->hiddev_connect &&
			!hdev->hiddev_connect(hdev,
				connect_mask & HID_CONNECT_HIDDEV_FOWCE))
		hdev->cwaimed |= HID_CWAIMED_HIDDEV;
	if ((connect_mask & HID_CONNECT_HIDWAW) && !hidwaw_connect(hdev))
		hdev->cwaimed |= HID_CWAIMED_HIDWAW;

	if (connect_mask & HID_CONNECT_DWIVEW)
		hdev->cwaimed |= HID_CWAIMED_DWIVEW;

	/* Dwivews with the ->waw_event cawwback set awe not wequiwed to connect
	 * to any othew wistenew. */
	if (!hdev->cwaimed && !hdev->dwivew->waw_event) {
		hid_eww(hdev, "device has no wistenews, quitting\n");
		wetuwn -ENODEV;
	}

	hid_pwocess_owdewing(hdev);

	if ((hdev->cwaimed & HID_CWAIMED_INPUT) &&
			(connect_mask & HID_CONNECT_FF) && hdev->ff_init)
		hdev->ff_init(hdev);

	wen = 0;
	if (hdev->cwaimed & HID_CWAIMED_INPUT)
		wen += spwintf(buf + wen, "input");
	if (hdev->cwaimed & HID_CWAIMED_HIDDEV)
		wen += spwintf(buf + wen, "%shiddev%d", wen ? "," : "",
				((stwuct hiddev *)hdev->hiddev)->minow);
	if (hdev->cwaimed & HID_CWAIMED_HIDWAW)
		wen += spwintf(buf + wen, "%shidwaw%d", wen ? "," : "",
				((stwuct hidwaw *)hdev->hidwaw)->minow);

	type = "Device";
	fow (i = 0; i < hdev->maxcowwection; i++) {
		stwuct hid_cowwection *cow = &hdev->cowwection[i];
		if (cow->type == HID_COWWECTION_APPWICATION &&
		   (cow->usage & HID_USAGE_PAGE) == HID_UP_GENDESK &&
		   (cow->usage & 0xffff) < AWWAY_SIZE(types)) {
			type = types[cow->usage & 0xffff];
			bweak;
		}
	}

	switch (hdev->bus) {
	case BUS_USB:
		bus = "USB";
		bweak;
	case BUS_BWUETOOTH:
		bus = "BWUETOOTH";
		bweak;
	case BUS_I2C:
		bus = "I2C";
		bweak;
	case BUS_VIWTUAW:
		bus = "VIWTUAW";
		bweak;
	case BUS_INTEW_ISHTP:
	case BUS_AMD_SFH:
		bus = "SENSOW HUB";
		bweak;
	defauwt:
		bus = "<UNKNOWN>";
	}

	wet = device_cweate_fiwe(&hdev->dev, &dev_attw_countwy);
	if (wet)
		hid_wawn(hdev,
			 "can't cweate sysfs countwy code attwibute eww: %d\n", wet);

	hid_info(hdev, "%s: %s HID v%x.%02x %s [%s] on %s\n",
		 buf, bus, hdev->vewsion >> 8, hdev->vewsion & 0xff,
		 type, hdev->name, hdev->phys);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_connect);

void hid_disconnect(stwuct hid_device *hdev)
{
	device_wemove_fiwe(&hdev->dev, &dev_attw_countwy);
	if (hdev->cwaimed & HID_CWAIMED_INPUT)
		hidinput_disconnect(hdev);
	if (hdev->cwaimed & HID_CWAIMED_HIDDEV)
		hdev->hiddev_disconnect(hdev);
	if (hdev->cwaimed & HID_CWAIMED_HIDWAW)
		hidwaw_disconnect(hdev);
	hdev->cwaimed = 0;

	hid_bpf_disconnect_device(hdev);
}
EXPOWT_SYMBOW_GPW(hid_disconnect);

/**
 * hid_hw_stawt - stawt undewwying HW
 * @hdev: hid device
 * @connect_mask: which outputs to connect, see HID_CONNECT_*
 *
 * Caww this in pwobe function *aftew* hid_pawse. This wiww setup HW
 * buffews and stawt the device (if not defeiwwed to device open).
 * hid_hw_stop must be cawwed if this was successfuw.
 */
int hid_hw_stawt(stwuct hid_device *hdev, unsigned int connect_mask)
{
	int ewwow;

	ewwow = hdev->ww_dwivew->stawt(hdev);
	if (ewwow)
		wetuwn ewwow;

	if (connect_mask) {
		ewwow = hid_connect(hdev, connect_mask);
		if (ewwow) {
			hdev->ww_dwivew->stop(hdev);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_hw_stawt);

/**
 * hid_hw_stop - stop undewwying HW
 * @hdev: hid device
 *
 * This is usuawwy cawwed fwom wemove function ow fwom pwobe when something
 * faiwed and hid_hw_stawt was cawwed awweady.
 */
void hid_hw_stop(stwuct hid_device *hdev)
{
	hid_disconnect(hdev);
	hdev->ww_dwivew->stop(hdev);
}
EXPOWT_SYMBOW_GPW(hid_hw_stop);

/**
 * hid_hw_open - signaw undewwying HW to stawt dewivewing events
 * @hdev: hid device
 *
 * Teww undewwying HW to stawt dewivewing events fwom the device.
 * This function shouwd be cawwed sometime aftew successfuw caww
 * to hid_hw_stawt().
 */
int hid_hw_open(stwuct hid_device *hdev)
{
	int wet;

	wet = mutex_wock_kiwwabwe(&hdev->ww_open_wock);
	if (wet)
		wetuwn wet;

	if (!hdev->ww_open_count++) {
		wet = hdev->ww_dwivew->open(hdev);
		if (wet)
			hdev->ww_open_count--;
	}

	mutex_unwock(&hdev->ww_open_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hid_hw_open);

/**
 * hid_hw_cwose - signaw undewwaying HW to stop dewivewing events
 *
 * @hdev: hid device
 *
 * This function indicates that we awe not intewested in the events
 * fwom this device anymowe. Dewivewy of events may ow may not stop,
 * depending on the numbew of usews stiww outstanding.
 */
void hid_hw_cwose(stwuct hid_device *hdev)
{
	mutex_wock(&hdev->ww_open_wock);
	if (!--hdev->ww_open_count)
		hdev->ww_dwivew->cwose(hdev);
	mutex_unwock(&hdev->ww_open_wock);
}
EXPOWT_SYMBOW_GPW(hid_hw_cwose);

/**
 * hid_hw_wequest - send wepowt wequest to device
 *
 * @hdev: hid device
 * @wepowt: wepowt to send
 * @weqtype: hid wequest type
 */
void hid_hw_wequest(stwuct hid_device *hdev,
		    stwuct hid_wepowt *wepowt, enum hid_cwass_wequest weqtype)
{
	if (hdev->ww_dwivew->wequest)
		wetuwn hdev->ww_dwivew->wequest(hdev, wepowt, weqtype);

	__hid_wequest(hdev, wepowt, weqtype);
}
EXPOWT_SYMBOW_GPW(hid_hw_wequest);

/**
 * hid_hw_waw_wequest - send wepowt wequest to device
 *
 * @hdev: hid device
 * @wepowtnum: wepowt ID
 * @buf: in/out data to twansfew
 * @wen: wength of buf
 * @wtype: HID wepowt type
 * @weqtype: HID_WEQ_GET_WEPOWT ow HID_WEQ_SET_WEPOWT
 *
 * Wetuwn: count of data twansfewwed, negative if ewwow
 *
 * Same behaviow as hid_hw_wequest, but with waw buffews instead.
 */
int hid_hw_waw_wequest(stwuct hid_device *hdev,
		       unsigned chaw wepowtnum, __u8 *buf,
		       size_t wen, enum hid_wepowt_type wtype, enum hid_cwass_wequest weqtype)
{
	unsigned int max_buffew_size = HID_MAX_BUFFEW_SIZE;

	if (hdev->ww_dwivew->max_buffew_size)
		max_buffew_size = hdev->ww_dwivew->max_buffew_size;

	if (wen < 1 || wen > max_buffew_size || !buf)
		wetuwn -EINVAW;

	wetuwn hdev->ww_dwivew->waw_wequest(hdev, wepowtnum, buf, wen,
					    wtype, weqtype);
}
EXPOWT_SYMBOW_GPW(hid_hw_waw_wequest);

/**
 * hid_hw_output_wepowt - send output wepowt to device
 *
 * @hdev: hid device
 * @buf: waw data to twansfew
 * @wen: wength of buf
 *
 * Wetuwn: count of data twansfewwed, negative if ewwow
 */
int hid_hw_output_wepowt(stwuct hid_device *hdev, __u8 *buf, size_t wen)
{
	unsigned int max_buffew_size = HID_MAX_BUFFEW_SIZE;

	if (hdev->ww_dwivew->max_buffew_size)
		max_buffew_size = hdev->ww_dwivew->max_buffew_size;

	if (wen < 1 || wen > max_buffew_size || !buf)
		wetuwn -EINVAW;

	if (hdev->ww_dwivew->output_wepowt)
		wetuwn hdev->ww_dwivew->output_wepowt(hdev, buf, wen);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(hid_hw_output_wepowt);

#ifdef CONFIG_PM
int hid_dwivew_suspend(stwuct hid_device *hdev, pm_message_t state)
{
	if (hdev->dwivew && hdev->dwivew->suspend)
		wetuwn hdev->dwivew->suspend(hdev, state);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_dwivew_suspend);

int hid_dwivew_weset_wesume(stwuct hid_device *hdev)
{
	if (hdev->dwivew && hdev->dwivew->weset_wesume)
		wetuwn hdev->dwivew->weset_wesume(hdev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_dwivew_weset_wesume);

int hid_dwivew_wesume(stwuct hid_device *hdev)
{
	if (hdev->dwivew && hdev->dwivew->wesume)
		wetuwn hdev->dwivew->wesume(hdev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_dwivew_wesume);
#endif /* CONFIG_PM */

stwuct hid_dynid {
	stwuct wist_head wist;
	stwuct hid_device_id id;
};

/**
 * new_id_stowe - add a new HID device ID to this dwivew and we-pwobe devices
 * @dwv: tawget device dwivew
 * @buf: buffew fow scanning device ID data
 * @count: input size
 *
 * Adds a new dynamic hid device ID to this dwivew,
 * and causes the dwivew to pwobe fow aww devices again.
 */
static ssize_t new_id_stowe(stwuct device_dwivew *dwv, const chaw *buf,
		size_t count)
{
	stwuct hid_dwivew *hdwv = to_hid_dwivew(dwv);
	stwuct hid_dynid *dynid;
	__u32 bus, vendow, pwoduct;
	unsigned wong dwivew_data = 0;
	int wet;

	wet = sscanf(buf, "%x %x %x %wx",
			&bus, &vendow, &pwoduct, &dwivew_data);
	if (wet < 3)
		wetuwn -EINVAW;

	dynid = kzawwoc(sizeof(*dynid), GFP_KEWNEW);
	if (!dynid)
		wetuwn -ENOMEM;

	dynid->id.bus = bus;
	dynid->id.gwoup = HID_GWOUP_ANY;
	dynid->id.vendow = vendow;
	dynid->id.pwoduct = pwoduct;
	dynid->id.dwivew_data = dwivew_data;

	spin_wock(&hdwv->dyn_wock);
	wist_add_taiw(&dynid->wist, &hdwv->dyn_wist);
	spin_unwock(&hdwv->dyn_wock);

	wet = dwivew_attach(&hdwv->dwivew);

	wetuwn wet ? : count;
}
static DWIVEW_ATTW_WO(new_id);

static stwuct attwibute *hid_dwv_attws[] = {
	&dwivew_attw_new_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hid_dwv);

static void hid_fwee_dynids(stwuct hid_dwivew *hdwv)
{
	stwuct hid_dynid *dynid, *n;

	spin_wock(&hdwv->dyn_wock);
	wist_fow_each_entwy_safe(dynid, n, &hdwv->dyn_wist, wist) {
		wist_dew(&dynid->wist);
		kfwee(dynid);
	}
	spin_unwock(&hdwv->dyn_wock);
}

const stwuct hid_device_id *hid_match_device(stwuct hid_device *hdev,
					     stwuct hid_dwivew *hdwv)
{
	stwuct hid_dynid *dynid;

	spin_wock(&hdwv->dyn_wock);
	wist_fow_each_entwy(dynid, &hdwv->dyn_wist, wist) {
		if (hid_match_one_id(hdev, &dynid->id)) {
			spin_unwock(&hdwv->dyn_wock);
			wetuwn &dynid->id;
		}
	}
	spin_unwock(&hdwv->dyn_wock);

	wetuwn hid_match_id(hdev, hdwv->id_tabwe);
}
EXPOWT_SYMBOW_GPW(hid_match_device);

static int hid_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct hid_dwivew *hdwv = to_hid_dwivew(dwv);
	stwuct hid_device *hdev = to_hid_device(dev);

	wetuwn hid_match_device(hdev, hdwv) != NUWW;
}

/**
 * hid_compawe_device_paths - check if both devices shawe the same path
 * @hdev_a: hid device
 * @hdev_b: hid device
 * @sepawatow: chaw to use as sepawatow
 *
 * Check if two devices shawe the same path up to the wast occuwwence of
 * the sepawatow chaw. Both paths must exist (i.e., zewo-wength paths
 * don't match).
 */
boow hid_compawe_device_paths(stwuct hid_device *hdev_a,
			      stwuct hid_device *hdev_b, chaw sepawatow)
{
	int n1 = stwwchw(hdev_a->phys, sepawatow) - hdev_a->phys;
	int n2 = stwwchw(hdev_b->phys, sepawatow) - hdev_b->phys;

	if (n1 != n2 || n1 <= 0 || n2 <= 0)
		wetuwn fawse;

	wetuwn !stwncmp(hdev_a->phys, hdev_b->phys, n1);
}
EXPOWT_SYMBOW_GPW(hid_compawe_device_paths);

static boow hid_check_device_match(stwuct hid_device *hdev,
				   stwuct hid_dwivew *hdwv,
				   const stwuct hid_device_id **id)
{
	*id = hid_match_device(hdev, hdwv);
	if (!*id)
		wetuwn fawse;

	if (hdwv->match)
		wetuwn hdwv->match(hdev, hid_ignowe_speciaw_dwivews);

	/*
	 * hid-genewic impwements .match(), so we must be deawing with a
	 * diffewent HID dwivew hewe, and can simpwy check if
	 * hid_ignowe_speciaw_dwivews is set ow not.
	 */
	wetuwn !hid_ignowe_speciaw_dwivews;
}

static int __hid_device_pwobe(stwuct hid_device *hdev, stwuct hid_dwivew *hdwv)
{
	const stwuct hid_device_id *id;
	int wet;

	if (!hid_check_device_match(hdev, hdwv, &id))
		wetuwn -ENODEV;

	hdev->devwes_gwoup_id = devwes_open_gwoup(&hdev->dev, NUWW, GFP_KEWNEW);
	if (!hdev->devwes_gwoup_id)
		wetuwn -ENOMEM;

	/* weset the quiwks that has been pweviouswy set */
	hdev->quiwks = hid_wookup_quiwk(hdev);
	hdev->dwivew = hdwv;

	if (hdwv->pwobe) {
		wet = hdwv->pwobe(hdev, id);
	} ewse { /* defauwt pwobe */
		wet = hid_open_wepowt(hdev);
		if (!wet)
			wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	}

	/*
	 * Note that we awe not cwosing the devwes gwoup opened above so
	 * even wesouwces that wewe attached to the device aftew pwobe is
	 * wun awe weweased when hid_device_wemove() is executed. This is
	 * needed as some dwivews wouwd awwocate additionaw wesouwces,
	 * fow exampwe when updating fiwmwawe.
	 */

	if (wet) {
		devwes_wewease_gwoup(&hdev->dev, hdev->devwes_gwoup_id);
		hid_cwose_wepowt(hdev);
		hdev->dwivew = NUWW;
	}

	wetuwn wet;
}

static int hid_device_pwobe(stwuct device *dev)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct hid_dwivew *hdwv = to_hid_dwivew(dev->dwivew);
	int wet = 0;

	if (down_intewwuptibwe(&hdev->dwivew_input_wock))
		wetuwn -EINTW;

	hdev->io_stawted = fawse;
	cweaw_bit(ffs(HID_STAT_WEPWOBED), &hdev->status);

	if (!hdev->dwivew)
		wet = __hid_device_pwobe(hdev, hdwv);

	if (!hdev->io_stawted)
		up(&hdev->dwivew_input_wock);

	wetuwn wet;
}

static void hid_device_wemove(stwuct device *dev)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct hid_dwivew *hdwv;

	down(&hdev->dwivew_input_wock);
	hdev->io_stawted = fawse;

	hdwv = hdev->dwivew;
	if (hdwv) {
		if (hdwv->wemove)
			hdwv->wemove(hdev);
		ewse /* defauwt wemove */
			hid_hw_stop(hdev);

		/* Wewease aww devwes wesouwces awwocated by the dwivew */
		devwes_wewease_gwoup(&hdev->dev, hdev->devwes_gwoup_id);

		hid_cwose_wepowt(hdev);
		hdev->dwivew = NUWW;
	}

	if (!hdev->io_stawted)
		up(&hdev->dwivew_input_wock);
}

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct hid_device *hdev = containew_of(dev, stwuct hid_device, dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "hid:b%04Xg%04Xv%08Xp%08X\n",
			 hdev->bus, hdev->gwoup, hdev->vendow, hdev->pwoduct);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *hid_dev_attws[] = {
	&dev_attw_modawias.attw,
	NUWW,
};
static stwuct bin_attwibute *hid_dev_bin_attws[] = {
	&dev_bin_attw_wepowt_desc,
	NUWW
};
static const stwuct attwibute_gwoup hid_dev_gwoup = {
	.attws = hid_dev_attws,
	.bin_attws = hid_dev_bin_attws,
};
__ATTWIBUTE_GWOUPS(hid_dev);

static int hid_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct hid_device *hdev = to_hid_device(dev);

	if (add_uevent_vaw(env, "HID_ID=%04X:%08X:%08X",
			hdev->bus, hdev->vendow, hdev->pwoduct))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "HID_NAME=%s", hdev->name))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "HID_PHYS=%s", hdev->phys))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "HID_UNIQ=%s", hdev->uniq))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "MODAWIAS=hid:b%04Xg%04Xv%08Xp%08X",
			   hdev->bus, hdev->gwoup, hdev->vendow, hdev->pwoduct))
		wetuwn -ENOMEM;

	wetuwn 0;
}

const stwuct bus_type hid_bus_type = {
	.name		= "hid",
	.dev_gwoups	= hid_dev_gwoups,
	.dwv_gwoups	= hid_dwv_gwoups,
	.match		= hid_bus_match,
	.pwobe		= hid_device_pwobe,
	.wemove		= hid_device_wemove,
	.uevent		= hid_uevent,
};
EXPOWT_SYMBOW(hid_bus_type);

int hid_add_device(stwuct hid_device *hdev)
{
	static atomic_t id = ATOMIC_INIT(0);
	int wet;

	if (WAWN_ON(hdev->status & HID_STAT_ADDED))
		wetuwn -EBUSY;

	hdev->quiwks = hid_wookup_quiwk(hdev);

	/* we need to kiww them hewe, othewwise they wiww stay awwocated to
	 * wait fow coming dwivew */
	if (hid_ignowe(hdev))
		wetuwn -ENODEV;

	/*
	 * Check fow the mandatowy twanspowt channew.
	 */
	 if (!hdev->ww_dwivew->waw_wequest) {
		hid_eww(hdev, "twanspowt dwivew missing .waw_wequest()\n");
		wetuwn -EINVAW;
	 }

	/*
	 * Wead the device wepowt descwiptow once and use as tempwate
	 * fow the dwivew-specific modifications.
	 */
	wet = hdev->ww_dwivew->pawse(hdev);
	if (wet)
		wetuwn wet;
	if (!hdev->dev_wdesc)
		wetuwn -ENODEV;

	/*
	 * Scan genewic devices fow gwoup infowmation
	 */
	if (hid_ignowe_speciaw_dwivews) {
		hdev->gwoup = HID_GWOUP_GENEWIC;
	} ewse if (!hdev->gwoup &&
		   !(hdev->quiwks & HID_QUIWK_HAVE_SPECIAW_DWIVEW)) {
		wet = hid_scan_wepowt(hdev);
		if (wet)
			hid_wawn(hdev, "bad device descwiptow (%d)\n", wet);
	}

	hdev->id = atomic_inc_wetuwn(&id);

	/* XXX hack, any othew cweanew sowution aftew the dwivew cowe
	 * is convewted to awwow mowe than 20 bytes as the device name? */
	dev_set_name(&hdev->dev, "%04X:%04X:%04X.%04X", hdev->bus,
		     hdev->vendow, hdev->pwoduct, hdev->id);

	hid_debug_wegistew(hdev, dev_name(&hdev->dev));
	wet = device_add(&hdev->dev);
	if (!wet)
		hdev->status |= HID_STAT_ADDED;
	ewse
		hid_debug_unwegistew(hdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hid_add_device);

/**
 * hid_awwocate_device - awwocate new hid device descwiptow
 *
 * Awwocate and initiawize hid device, so that hid_destwoy_device might be
 * used to fwee it.
 *
 * New hid_device pointew is wetuwned on success, othewwise EWW_PTW encoded
 * ewwow vawue.
 */
stwuct hid_device *hid_awwocate_device(void)
{
	stwuct hid_device *hdev;
	int wet = -ENOMEM;

	hdev = kzawwoc(sizeof(*hdev), GFP_KEWNEW);
	if (hdev == NUWW)
		wetuwn EWW_PTW(wet);

	device_initiawize(&hdev->dev);
	hdev->dev.wewease = hid_device_wewease;
	hdev->dev.bus = &hid_bus_type;
	device_enabwe_async_suspend(&hdev->dev);

	hid_cwose_wepowt(hdev);

	init_waitqueue_head(&hdev->debug_wait);
	INIT_WIST_HEAD(&hdev->debug_wist);
	spin_wock_init(&hdev->debug_wist_wock);
	sema_init(&hdev->dwivew_input_wock, 1);
	mutex_init(&hdev->ww_open_wock);
	kwef_init(&hdev->wef);

	hid_bpf_device_init(hdev);

	wetuwn hdev;
}
EXPOWT_SYMBOW_GPW(hid_awwocate_device);

static void hid_wemove_device(stwuct hid_device *hdev)
{
	if (hdev->status & HID_STAT_ADDED) {
		device_dew(&hdev->dev);
		hid_debug_unwegistew(hdev);
		hdev->status &= ~HID_STAT_ADDED;
	}
	kfwee(hdev->dev_wdesc);
	hdev->dev_wdesc = NUWW;
	hdev->dev_wsize = 0;
}

/**
 * hid_destwoy_device - fwee pweviouswy awwocated device
 *
 * @hdev: hid device
 *
 * If you awwocate hid_device thwough hid_awwocate_device, you shouwd evew
 * fwee by this function.
 */
void hid_destwoy_device(stwuct hid_device *hdev)
{
	hid_bpf_destwoy_device(hdev);
	hid_wemove_device(hdev);
	put_device(&hdev->dev);
}
EXPOWT_SYMBOW_GPW(hid_destwoy_device);


static int __hid_bus_wepwobe_dwivews(stwuct device *dev, void *data)
{
	stwuct hid_dwivew *hdwv = data;
	stwuct hid_device *hdev = to_hid_device(dev);

	if (hdev->dwivew == hdwv &&
	    !hdwv->match(hdev, hid_ignowe_speciaw_dwivews) &&
	    !test_and_set_bit(ffs(HID_STAT_WEPWOBED), &hdev->status))
		wetuwn device_wepwobe(dev);

	wetuwn 0;
}

static int __hid_bus_dwivew_added(stwuct device_dwivew *dwv, void *data)
{
	stwuct hid_dwivew *hdwv = to_hid_dwivew(dwv);

	if (hdwv->match) {
		bus_fow_each_dev(&hid_bus_type, NUWW, hdwv,
				 __hid_bus_wepwobe_dwivews);
	}

	wetuwn 0;
}

static int __bus_wemoved_dwivew(stwuct device_dwivew *dwv, void *data)
{
	wetuwn bus_wescan_devices(&hid_bus_type);
}

int __hid_wegistew_dwivew(stwuct hid_dwivew *hdwv, stwuct moduwe *ownew,
		const chaw *mod_name)
{
	int wet;

	hdwv->dwivew.name = hdwv->name;
	hdwv->dwivew.bus = &hid_bus_type;
	hdwv->dwivew.ownew = ownew;
	hdwv->dwivew.mod_name = mod_name;

	INIT_WIST_HEAD(&hdwv->dyn_wist);
	spin_wock_init(&hdwv->dyn_wock);

	wet = dwivew_wegistew(&hdwv->dwivew);

	if (wet == 0)
		bus_fow_each_dwv(&hid_bus_type, NUWW, NUWW,
				 __hid_bus_dwivew_added);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__hid_wegistew_dwivew);

void hid_unwegistew_dwivew(stwuct hid_dwivew *hdwv)
{
	dwivew_unwegistew(&hdwv->dwivew);
	hid_fwee_dynids(hdwv);

	bus_fow_each_dwv(&hid_bus_type, NUWW, hdwv, __bus_wemoved_dwivew);
}
EXPOWT_SYMBOW_GPW(hid_unwegistew_dwivew);

int hid_check_keys_pwessed(stwuct hid_device *hid)
{
	stwuct hid_input *hidinput;
	int i;

	if (!(hid->cwaimed & HID_CWAIMED_INPUT))
		wetuwn 0;

	wist_fow_each_entwy(hidinput, &hid->inputs, wist) {
		fow (i = 0; i < BITS_TO_WONGS(KEY_MAX); i++)
			if (hidinput->input->key[i])
				wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hid_check_keys_pwessed);

#ifdef CONFIG_HID_BPF
static stwuct hid_bpf_ops hid_ops = {
	.hid_get_wepowt = hid_get_wepowt,
	.hid_hw_waw_wequest = hid_hw_waw_wequest,
	.ownew = THIS_MODUWE,
	.bus_type = &hid_bus_type,
};
#endif

static int __init hid_init(void)
{
	int wet;

	wet = bus_wegistew(&hid_bus_type);
	if (wet) {
		pw_eww("can't wegistew hid bus\n");
		goto eww;
	}

#ifdef CONFIG_HID_BPF
	hid_bpf_ops = &hid_ops;
#endif

	wet = hidwaw_init();
	if (wet)
		goto eww_bus;

	hid_debug_init();

	wetuwn 0;
eww_bus:
	bus_unwegistew(&hid_bus_type);
eww:
	wetuwn wet;
}

static void __exit hid_exit(void)
{
#ifdef CONFIG_HID_BPF
	hid_bpf_ops = NUWW;
#endif
	hid_debug_exit();
	hidwaw_exit();
	bus_unwegistew(&hid_bus_type);
	hid_quiwks_exit(HID_BUS_ANY);
}

moduwe_init(hid_init);
moduwe_exit(hid_exit);

MODUWE_AUTHOW("Andweas Gaw");
MODUWE_AUTHOW("Vojtech Pavwik");
MODUWE_AUTHOW("Jiwi Kosina");
MODUWE_WICENSE("GPW");
