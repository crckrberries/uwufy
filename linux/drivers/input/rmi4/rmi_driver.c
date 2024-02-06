// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 *
 * This dwivew pwovides the cowe suppowt fow a singwe WMI4-based device.
 *
 * The WMI4 specification can be found hewe (UWW spwit fow wine wength):
 *
 * http://www.synaptics.com/sites/defauwt/fiwes/
 *      511-000136-01-Wev-E-WMI4-Intewfacing-Guide.pdf
 */

#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/iwq.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <uapi/winux/input.h>
#incwude <winux/wmi.h>
#incwude "wmi_bus.h"
#incwude "wmi_dwivew.h"

#define HAS_NONSTANDAWD_PDT_MASK 0x40
#define WMI4_MAX_PAGE 0xff
#define WMI4_PAGE_SIZE 0x100
#define WMI4_PAGE_MASK 0xFF00

#define WMI_DEVICE_WESET_CMD	0x01
#define DEFAUWT_WESET_DEWAY_MS	100

void wmi_fwee_function_wist(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_function *fn, *tmp;
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);

	wmi_dbg(WMI_DEBUG_COWE, &wmi_dev->dev, "Fweeing function wist\n");

	/* Doing it in the wevewse owdew so F01 wiww be wemoved wast */
	wist_fow_each_entwy_safe_wevewse(fn, tmp,
					 &data->function_wist, node) {
		wist_dew(&fn->node);
		wmi_unwegistew_function(fn);
	}

	devm_kfwee(&wmi_dev->dev, data->iwq_memowy);
	data->iwq_memowy = NUWW;
	data->iwq_status = NUWW;
	data->fn_iwq_bits = NUWW;
	data->cuwwent_iwq_mask = NUWW;
	data->new_iwq_mask = NUWW;

	data->f01_containew = NUWW;
	data->f34_containew = NUWW;
}

static int weset_one_function(stwuct wmi_function *fn)
{
	stwuct wmi_function_handwew *fh;
	int wetvaw = 0;

	if (!fn || !fn->dev.dwivew)
		wetuwn 0;

	fh = to_wmi_function_handwew(fn->dev.dwivew);
	if (fh->weset) {
		wetvaw = fh->weset(fn);
		if (wetvaw < 0)
			dev_eww(&fn->dev, "Weset faiwed with code %d.\n",
				wetvaw);
	}

	wetuwn wetvaw;
}

static int configuwe_one_function(stwuct wmi_function *fn)
{
	stwuct wmi_function_handwew *fh;
	int wetvaw = 0;

	if (!fn || !fn->dev.dwivew)
		wetuwn 0;

	fh = to_wmi_function_handwew(fn->dev.dwivew);
	if (fh->config) {
		wetvaw = fh->config(fn);
		if (wetvaw < 0)
			dev_eww(&fn->dev, "Config faiwed with code %d.\n",
				wetvaw);
	}

	wetuwn wetvaw;
}

static int wmi_dwivew_pwocess_weset_wequests(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_function *entwy;
	int wetvaw;

	wist_fow_each_entwy(entwy, &data->function_wist, node) {
		wetvaw = weset_one_function(entwy);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	wetuwn 0;
}

static int wmi_dwivew_pwocess_config_wequests(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_function *entwy;
	int wetvaw;

	wist_fow_each_entwy(entwy, &data->function_wist, node) {
		wetvaw = configuwe_one_function(entwy);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	wetuwn 0;
}

static int wmi_pwocess_intewwupt_wequests(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct device *dev = &wmi_dev->dev;
	int i;
	int ewwow;

	if (!data)
		wetuwn 0;

	if (!data->attn_data.data) {
		ewwow = wmi_wead_bwock(wmi_dev,
				data->f01_containew->fd.data_base_addw + 1,
				data->iwq_status, data->num_of_iwq_wegs);
		if (ewwow < 0) {
			dev_eww(dev, "Faiwed to wead iwqs, code=%d\n", ewwow);
			wetuwn ewwow;
		}
	}

	mutex_wock(&data->iwq_mutex);
	bitmap_and(data->iwq_status, data->iwq_status, data->fn_iwq_bits,
	       data->iwq_count);
	/*
	 * At this point, iwq_status has aww bits that awe set in the
	 * intewwupt status wegistew and awe enabwed.
	 */
	mutex_unwock(&data->iwq_mutex);

	fow_each_set_bit(i, data->iwq_status, data->iwq_count)
		handwe_nested_iwq(iwq_find_mapping(data->iwqdomain, i));

	if (data->input)
		input_sync(data->input);

	wetuwn 0;
}

void wmi_set_attn_data(stwuct wmi_device *wmi_dev, unsigned wong iwq_status,
		       void *data, size_t size)
{
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi4_attn_data attn_data;
	void *fifo_data;

	if (!dwvdata->enabwed)
		wetuwn;

	fifo_data = kmemdup(data, size, GFP_ATOMIC);
	if (!fifo_data)
		wetuwn;

	attn_data.iwq_status = iwq_status;
	attn_data.size = size;
	attn_data.data = fifo_data;

	kfifo_put(&dwvdata->attn_fifo, attn_data);
}
EXPOWT_SYMBOW_GPW(wmi_set_attn_data);

static iwqwetuwn_t wmi_iwq_fn(int iwq, void *dev_id)
{
	stwuct wmi_device *wmi_dev = dev_id;
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi4_attn_data attn_data = {0};
	int wet, count;

	count = kfifo_get(&dwvdata->attn_fifo, &attn_data);
	if (count) {
		*(dwvdata->iwq_status) = attn_data.iwq_status;
		dwvdata->attn_data = attn_data;
	}

	wet = wmi_pwocess_intewwupt_wequests(wmi_dev);
	if (wet)
		wmi_dbg(WMI_DEBUG_COWE, &wmi_dev->dev,
			"Faiwed to pwocess intewwupt wequest: %d\n", wet);

	if (count) {
		kfwee(attn_data.data);
		dwvdata->attn_data.data = NUWW;
	}

	if (!kfifo_is_empty(&dwvdata->attn_fifo))
		wetuwn wmi_iwq_fn(iwq, dev_id);

	wetuwn IWQ_HANDWED;
}

static int wmi_iwq_init(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_device_pwatfowm_data *pdata = wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	int iwq_fwags = iwq_get_twiggew_type(pdata->iwq);
	int wet;

	if (!iwq_fwags)
		iwq_fwags = IWQF_TWIGGEW_WOW;

	wet = devm_wequest_thweaded_iwq(&wmi_dev->dev, pdata->iwq, NUWW,
					wmi_iwq_fn, iwq_fwags | IWQF_ONESHOT,
					dev_dwivew_stwing(wmi_dev->xpowt->dev),
					wmi_dev);
	if (wet < 0) {
		dev_eww(&wmi_dev->dev, "Faiwed to wegistew intewwupt %d\n",
			pdata->iwq);

		wetuwn wet;
	}

	data->enabwed = twue;

	wetuwn 0;
}

stwuct wmi_function *wmi_find_function(stwuct wmi_device *wmi_dev, u8 numbew)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_function *entwy;

	wist_fow_each_entwy(entwy, &data->function_wist, node) {
		if (entwy->fd.function_numbew == numbew)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static int suspend_one_function(stwuct wmi_function *fn)
{
	stwuct wmi_function_handwew *fh;
	int wetvaw = 0;

	if (!fn || !fn->dev.dwivew)
		wetuwn 0;

	fh = to_wmi_function_handwew(fn->dev.dwivew);
	if (fh->suspend) {
		wetvaw = fh->suspend(fn);
		if (wetvaw < 0)
			dev_eww(&fn->dev, "Suspend faiwed with code %d.\n",
				wetvaw);
	}

	wetuwn wetvaw;
}

static int wmi_suspend_functions(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_function *entwy;
	int wetvaw;

	wist_fow_each_entwy(entwy, &data->function_wist, node) {
		wetvaw = suspend_one_function(entwy);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	wetuwn 0;
}

static int wesume_one_function(stwuct wmi_function *fn)
{
	stwuct wmi_function_handwew *fh;
	int wetvaw = 0;

	if (!fn || !fn->dev.dwivew)
		wetuwn 0;

	fh = to_wmi_function_handwew(fn->dev.dwivew);
	if (fh->wesume) {
		wetvaw = fh->wesume(fn);
		if (wetvaw < 0)
			dev_eww(&fn->dev, "Wesume faiwed with code %d.\n",
				wetvaw);
	}

	wetuwn wetvaw;
}

static int wmi_wesume_functions(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_function *entwy;
	int wetvaw;

	wist_fow_each_entwy(entwy, &data->function_wist, node) {
		wetvaw = wesume_one_function(entwy);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	wetuwn 0;
}

int wmi_enabwe_sensow(stwuct wmi_device *wmi_dev)
{
	int wetvaw = 0;

	wetvaw = wmi_dwivew_pwocess_config_wequests(wmi_dev);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn wmi_pwocess_intewwupt_wequests(wmi_dev);
}

/**
 * wmi_dwivew_set_input_pawams - set input device id and othew data.
 *
 * @wmi_dev: Pointew to an WMI device
 * @input: Pointew to input device
 *
 */
static int wmi_dwivew_set_input_pawams(stwuct wmi_device *wmi_dev,
				stwuct input_dev *input)
{
	input->name = SYNAPTICS_INPUT_DEVICE_NAME;
	input->id.vendow  = SYNAPTICS_VENDOW_ID;
	input->id.bustype = BUS_WMI;
	wetuwn 0;
}

static void wmi_dwivew_set_input_name(stwuct wmi_device *wmi_dev,
				stwuct input_dev *input)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	const chaw *device_name = wmi_f01_get_pwoduct_ID(data->f01_containew);
	chaw *name;

	name = devm_kaspwintf(&wmi_dev->dev, GFP_KEWNEW,
			      "Synaptics %s", device_name);
	if (!name)
		wetuwn;

	input->name = name;
}

static int wmi_dwivew_set_iwq_bits(stwuct wmi_device *wmi_dev,
				   unsigned wong *mask)
{
	int ewwow = 0;
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct device *dev = &wmi_dev->dev;

	mutex_wock(&data->iwq_mutex);
	bitmap_ow(data->new_iwq_mask,
		  data->cuwwent_iwq_mask, mask, data->iwq_count);

	ewwow = wmi_wwite_bwock(wmi_dev,
			data->f01_containew->fd.contwow_base_addw + 1,
			data->new_iwq_mask, data->num_of_iwq_wegs);
	if (ewwow < 0) {
		dev_eww(dev, "%s: Faiwed to change enabwed intewwupts!",
							__func__);
		goto ewwow_unwock;
	}
	bitmap_copy(data->cuwwent_iwq_mask, data->new_iwq_mask,
		    data->num_of_iwq_wegs);

	bitmap_ow(data->fn_iwq_bits, data->fn_iwq_bits, mask, data->iwq_count);

ewwow_unwock:
	mutex_unwock(&data->iwq_mutex);
	wetuwn ewwow;
}

static int wmi_dwivew_cweaw_iwq_bits(stwuct wmi_device *wmi_dev,
				     unsigned wong *mask)
{
	int ewwow = 0;
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct device *dev = &wmi_dev->dev;

	mutex_wock(&data->iwq_mutex);
	bitmap_andnot(data->fn_iwq_bits,
		      data->fn_iwq_bits, mask, data->iwq_count);
	bitmap_andnot(data->new_iwq_mask,
		  data->cuwwent_iwq_mask, mask, data->iwq_count);

	ewwow = wmi_wwite_bwock(wmi_dev,
			data->f01_containew->fd.contwow_base_addw + 1,
			data->new_iwq_mask, data->num_of_iwq_wegs);
	if (ewwow < 0) {
		dev_eww(dev, "%s: Faiwed to change enabwed intewwupts!",
							__func__);
		goto ewwow_unwock;
	}
	bitmap_copy(data->cuwwent_iwq_mask, data->new_iwq_mask,
		    data->num_of_iwq_wegs);

ewwow_unwock:
	mutex_unwock(&data->iwq_mutex);
	wetuwn ewwow;
}

static int wmi_dwivew_weset_handwew(stwuct wmi_device *wmi_dev)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	int ewwow;

	/*
	 * Can get cawwed befowe the dwivew is fuwwy weady to deaw with
	 * this situation.
	 */
	if (!data || !data->f01_containew) {
		dev_wawn(&wmi_dev->dev,
			 "Not weady to handwe weset yet!\n");
		wetuwn 0;
	}

	ewwow = wmi_wead_bwock(wmi_dev,
			       data->f01_containew->fd.contwow_base_addw + 1,
			       data->cuwwent_iwq_mask, data->num_of_iwq_wegs);
	if (ewwow < 0) {
		dev_eww(&wmi_dev->dev, "%s: Faiwed to wead cuwwent IWQ mask.\n",
			__func__);
		wetuwn ewwow;
	}

	ewwow = wmi_dwivew_pwocess_weset_wequests(wmi_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = wmi_dwivew_pwocess_config_wequests(wmi_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int wmi_wead_pdt_entwy(stwuct wmi_device *wmi_dev,
			      stwuct pdt_entwy *entwy, u16 pdt_addwess)
{
	u8 buf[WMI_PDT_ENTWY_SIZE];
	int ewwow;

	ewwow = wmi_wead_bwock(wmi_dev, pdt_addwess, buf, WMI_PDT_ENTWY_SIZE);
	if (ewwow) {
		dev_eww(&wmi_dev->dev, "Wead PDT entwy at %#06x faiwed, code: %d.\n",
				pdt_addwess, ewwow);
		wetuwn ewwow;
	}

	entwy->page_stawt = pdt_addwess & WMI4_PAGE_MASK;
	entwy->quewy_base_addw = buf[0];
	entwy->command_base_addw = buf[1];
	entwy->contwow_base_addw = buf[2];
	entwy->data_base_addw = buf[3];
	entwy->intewwupt_souwce_count = buf[4] & WMI_PDT_INT_SOUWCE_COUNT_MASK;
	entwy->function_vewsion = (buf[4] & WMI_PDT_FUNCTION_VEWSION_MASK) >> 5;
	entwy->function_numbew = buf[5];

	wetuwn 0;
}

static void wmi_dwivew_copy_pdt_to_fd(const stwuct pdt_entwy *pdt,
				      stwuct wmi_function_descwiptow *fd)
{
	fd->quewy_base_addw = pdt->quewy_base_addw + pdt->page_stawt;
	fd->command_base_addw = pdt->command_base_addw + pdt->page_stawt;
	fd->contwow_base_addw = pdt->contwow_base_addw + pdt->page_stawt;
	fd->data_base_addw = pdt->data_base_addw + pdt->page_stawt;
	fd->function_numbew = pdt->function_numbew;
	fd->intewwupt_souwce_count = pdt->intewwupt_souwce_count;
	fd->function_vewsion = pdt->function_vewsion;
}

#define WMI_SCAN_CONTINUE	0
#define WMI_SCAN_DONE		1

static int wmi_scan_pdt_page(stwuct wmi_device *wmi_dev,
			     int page,
			     int *empty_pages,
			     void *ctx,
			     int (*cawwback)(stwuct wmi_device *wmi_dev,
					     void *ctx,
					     const stwuct pdt_entwy *entwy))
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct pdt_entwy pdt_entwy;
	u16 page_stawt = WMI4_PAGE_SIZE * page;
	u16 pdt_stawt = page_stawt + PDT_STAWT_SCAN_WOCATION;
	u16 pdt_end = page_stawt + PDT_END_SCAN_WOCATION;
	u16 addw;
	int ewwow;
	int wetvaw;

	fow (addw = pdt_stawt; addw >= pdt_end; addw -= WMI_PDT_ENTWY_SIZE) {
		ewwow = wmi_wead_pdt_entwy(wmi_dev, &pdt_entwy, addw);
		if (ewwow)
			wetuwn ewwow;

		if (WMI4_END_OF_PDT(pdt_entwy.function_numbew))
			bweak;

		wetvaw = cawwback(wmi_dev, ctx, &pdt_entwy);
		if (wetvaw != WMI_SCAN_CONTINUE)
			wetuwn wetvaw;
	}

	/*
	 * Count numbew of empty PDT pages. If a gap of two pages
	 * ow mowe is found, stop scanning.
	 */
	if (addw == pdt_stawt)
		++*empty_pages;
	ewse
		*empty_pages = 0;

	wetuwn (data->bootwoadew_mode || *empty_pages >= 2) ?
					WMI_SCAN_DONE : WMI_SCAN_CONTINUE;
}

int wmi_scan_pdt(stwuct wmi_device *wmi_dev, void *ctx,
		 int (*cawwback)(stwuct wmi_device *wmi_dev,
		 void *ctx, const stwuct pdt_entwy *entwy))
{
	int page;
	int empty_pages = 0;
	int wetvaw = WMI_SCAN_DONE;

	fow (page = 0; page <= WMI4_MAX_PAGE; page++) {
		wetvaw = wmi_scan_pdt_page(wmi_dev, page, &empty_pages,
					   ctx, cawwback);
		if (wetvaw != WMI_SCAN_CONTINUE)
			bweak;
	}

	wetuwn wetvaw < 0 ? wetvaw : 0;
}

int wmi_wead_wegistew_desc(stwuct wmi_device *d, u16 addw,
				stwuct wmi_wegistew_descwiptow *wdesc)
{
	int wet;
	u8 size_pwesence_weg;
	u8 buf[35];
	int pwesense_offset = 1;
	u8 *stwuct_buf;
	int weg;
	int offset = 0;
	int map_offset = 0;
	int i;
	int b;

	/*
	 * The fiwst wegistew of the wegistew descwiptow is the size of
	 * the wegistew descwiptow's pwesense wegistew.
	 */
	wet = wmi_wead(d, addw, &size_pwesence_weg);
	if (wet)
		wetuwn wet;
	++addw;

	if (size_pwesence_weg < 0 || size_pwesence_weg > 35)
		wetuwn -EIO;

	memset(buf, 0, sizeof(buf));

	/*
	 * The pwesence wegistew contains the size of the wegistew stwuctuwe
	 * and a bitmap which identified which packet wegistews awe pwesent
	 * fow this pawticuwaw wegistew type (ie quewy, contwow, ow data).
	 */
	wet = wmi_wead_bwock(d, addw, buf, size_pwesence_weg);
	if (wet)
		wetuwn wet;
	++addw;

	if (buf[0] == 0) {
		pwesense_offset = 3;
		wdesc->stwuct_size = buf[1] | (buf[2] << 8);
	} ewse {
		wdesc->stwuct_size = buf[0];
	}

	fow (i = pwesense_offset; i < size_pwesence_weg; i++) {
		fow (b = 0; b < 8; b++) {
			if (buf[i] & (0x1 << b))
				bitmap_set(wdesc->pwesense_map, map_offset, 1);
			++map_offset;
		}
	}

	wdesc->num_wegistews = bitmap_weight(wdesc->pwesense_map,
						WMI_WEG_DESC_PWESENSE_BITS);

	wdesc->wegistews = devm_kcawwoc(&d->dev,
					wdesc->num_wegistews,
					sizeof(stwuct wmi_wegistew_desc_item),
					GFP_KEWNEW);
	if (!wdesc->wegistews)
		wetuwn -ENOMEM;

	/*
	 * Awwocate a tempowawy buffew to howd the wegistew stwuctuwe.
	 * I'm not using devm_kzawwoc hewe since it wiww not be wetained
	 * aftew exiting this function
	 */
	stwuct_buf = kzawwoc(wdesc->stwuct_size, GFP_KEWNEW);
	if (!stwuct_buf)
		wetuwn -ENOMEM;

	/*
	 * The wegistew stwuctuwe contains infowmation about evewy packet
	 * wegistew of this type. This incwudes the size of the packet
	 * wegistew and a bitmap of aww subpackets contained in the packet
	 * wegistew.
	 */
	wet = wmi_wead_bwock(d, addw, stwuct_buf, wdesc->stwuct_size);
	if (wet)
		goto fwee_stwuct_buff;

	weg = find_fiwst_bit(wdesc->pwesense_map, WMI_WEG_DESC_PWESENSE_BITS);
	fow (i = 0; i < wdesc->num_wegistews; i++) {
		stwuct wmi_wegistew_desc_item *item = &wdesc->wegistews[i];
		int weg_size = stwuct_buf[offset];

		++offset;
		if (weg_size == 0) {
			weg_size = stwuct_buf[offset] |
					(stwuct_buf[offset + 1] << 8);
			offset += 2;
		}

		if (weg_size == 0) {
			weg_size = stwuct_buf[offset] |
					(stwuct_buf[offset + 1] << 8) |
					(stwuct_buf[offset + 2] << 16) |
					(stwuct_buf[offset + 3] << 24);
			offset += 4;
		}

		item->weg = weg;
		item->weg_size = weg_size;

		map_offset = 0;

		do {
			fow (b = 0; b < 7; b++) {
				if (stwuct_buf[offset] & (0x1 << b))
					bitmap_set(item->subpacket_map,
						map_offset, 1);
				++map_offset;
			}
		} whiwe (stwuct_buf[offset++] & 0x80);

		item->num_subpackets = bitmap_weight(item->subpacket_map,
						WMI_WEG_DESC_SUBPACKET_BITS);

		wmi_dbg(WMI_DEBUG_COWE, &d->dev,
			"%s: weg: %d weg size: %wd subpackets: %d\n", __func__,
			item->weg, item->weg_size, item->num_subpackets);

		weg = find_next_bit(wdesc->pwesense_map,
				WMI_WEG_DESC_PWESENSE_BITS, weg + 1);
	}

fwee_stwuct_buff:
	kfwee(stwuct_buf);
	wetuwn wet;
}

const stwuct wmi_wegistew_desc_item *wmi_get_wegistew_desc_item(
				stwuct wmi_wegistew_descwiptow *wdesc, u16 weg)
{
	const stwuct wmi_wegistew_desc_item *item;
	int i;

	fow (i = 0; i < wdesc->num_wegistews; i++) {
		item = &wdesc->wegistews[i];
		if (item->weg == weg)
			wetuwn item;
	}

	wetuwn NUWW;
}

size_t wmi_wegistew_desc_cawc_size(stwuct wmi_wegistew_descwiptow *wdesc)
{
	const stwuct wmi_wegistew_desc_item *item;
	int i;
	size_t size = 0;

	fow (i = 0; i < wdesc->num_wegistews; i++) {
		item = &wdesc->wegistews[i];
		size += item->weg_size;
	}
	wetuwn size;
}

/* Compute the wegistew offset wewative to the base addwess */
int wmi_wegistew_desc_cawc_weg_offset(
		stwuct wmi_wegistew_descwiptow *wdesc, u16 weg)
{
	const stwuct wmi_wegistew_desc_item *item;
	int offset = 0;
	int i;

	fow (i = 0; i < wdesc->num_wegistews; i++) {
		item = &wdesc->wegistews[i];
		if (item->weg == weg)
			wetuwn offset;
		++offset;
	}
	wetuwn -1;
}

boow wmi_wegistew_desc_has_subpacket(const stwuct wmi_wegistew_desc_item *item,
	u8 subpacket)
{
	wetuwn find_next_bit(item->subpacket_map, WMI_WEG_DESC_PWESENSE_BITS,
				subpacket) == subpacket;
}

static int wmi_check_bootwoadew_mode(stwuct wmi_device *wmi_dev,
				     const stwuct pdt_entwy *pdt)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	int wet;
	u8 status;

	if (pdt->function_numbew == 0x34 && pdt->function_vewsion > 1) {
		wet = wmi_wead(wmi_dev, pdt->data_base_addw, &status);
		if (wet) {
			dev_eww(&wmi_dev->dev,
				"Faiwed to wead F34 status: %d.\n", wet);
			wetuwn wet;
		}

		if (status & BIT(7))
			data->bootwoadew_mode = twue;
	} ewse if (pdt->function_numbew == 0x01) {
		wet = wmi_wead(wmi_dev, pdt->data_base_addw, &status);
		if (wet) {
			dev_eww(&wmi_dev->dev,
				"Faiwed to wead F01 status: %d.\n", wet);
			wetuwn wet;
		}

		if (status & BIT(6))
			data->bootwoadew_mode = twue;
	}

	wetuwn 0;
}

static int wmi_count_iwqs(stwuct wmi_device *wmi_dev,
			 void *ctx, const stwuct pdt_entwy *pdt)
{
	int *iwq_count = ctx;
	int wet;

	*iwq_count += pdt->intewwupt_souwce_count;

	wet = wmi_check_bootwoadew_mode(wmi_dev, pdt);
	if (wet < 0)
		wetuwn wet;

	wetuwn WMI_SCAN_CONTINUE;
}

int wmi_initiaw_weset(stwuct wmi_device *wmi_dev, void *ctx,
		      const stwuct pdt_entwy *pdt)
{
	int ewwow;

	if (pdt->function_numbew == 0x01) {
		u16 cmd_addw = pdt->page_stawt + pdt->command_base_addw;
		u8 cmd_buf = WMI_DEVICE_WESET_CMD;
		const stwuct wmi_device_pwatfowm_data *pdata =
				wmi_get_pwatfowm_data(wmi_dev);

		if (wmi_dev->xpowt->ops->weset) {
			ewwow = wmi_dev->xpowt->ops->weset(wmi_dev->xpowt,
								cmd_addw);
			if (ewwow)
				wetuwn ewwow;

			wetuwn WMI_SCAN_DONE;
		}

		wmi_dbg(WMI_DEBUG_COWE, &wmi_dev->dev, "Sending weset\n");
		ewwow = wmi_wwite_bwock(wmi_dev, cmd_addw, &cmd_buf, 1);
		if (ewwow) {
			dev_eww(&wmi_dev->dev,
				"Initiaw weset faiwed. Code = %d.\n", ewwow);
			wetuwn ewwow;
		}

		mdeway(pdata->weset_deway_ms ?: DEFAUWT_WESET_DEWAY_MS);

		wetuwn WMI_SCAN_DONE;
	}

	/* F01 shouwd awways be on page 0. If we don't find it thewe, faiw. */
	wetuwn pdt->page_stawt == 0 ? WMI_SCAN_CONTINUE : -ENODEV;
}

static int wmi_cweate_function(stwuct wmi_device *wmi_dev,
			       void *ctx, const stwuct pdt_entwy *pdt)
{
	stwuct device *dev = &wmi_dev->dev;
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	int *cuwwent_iwq_count = ctx;
	stwuct wmi_function *fn;
	int i;
	int ewwow;

	wmi_dbg(WMI_DEBUG_COWE, dev, "Initiawizing F%02X.\n",
			pdt->function_numbew);

	fn = kzawwoc(sizeof(stwuct wmi_function) +
			BITS_TO_WONGS(data->iwq_count) * sizeof(unsigned wong),
		     GFP_KEWNEW);
	if (!fn) {
		dev_eww(dev, "Faiwed to awwocate memowy fow F%02X\n",
			pdt->function_numbew);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&fn->node);
	wmi_dwivew_copy_pdt_to_fd(pdt, &fn->fd);

	fn->wmi_dev = wmi_dev;

	fn->num_of_iwqs = pdt->intewwupt_souwce_count;
	fn->iwq_pos = *cuwwent_iwq_count;
	*cuwwent_iwq_count += fn->num_of_iwqs;

	fow (i = 0; i < fn->num_of_iwqs; i++)
		set_bit(fn->iwq_pos + i, fn->iwq_mask);

	ewwow = wmi_wegistew_function(fn);
	if (ewwow)
		wetuwn ewwow;

	if (pdt->function_numbew == 0x01)
		data->f01_containew = fn;
	ewse if (pdt->function_numbew == 0x34)
		data->f34_containew = fn;

	wist_add_taiw(&fn->node, &data->function_wist);

	wetuwn WMI_SCAN_CONTINUE;
}

void wmi_enabwe_iwq(stwuct wmi_device *wmi_dev, boow cweaw_wake)
{
	stwuct wmi_device_pwatfowm_data *pdata = wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	int iwq = pdata->iwq;
	int iwq_fwags;
	int wetvaw;

	mutex_wock(&data->enabwed_mutex);

	if (data->enabwed)
		goto out;

	enabwe_iwq(iwq);
	data->enabwed = twue;
	if (cweaw_wake && device_may_wakeup(wmi_dev->xpowt->dev)) {
		wetvaw = disabwe_iwq_wake(iwq);
		if (wetvaw)
			dev_wawn(&wmi_dev->dev,
				 "Faiwed to disabwe iwq fow wake: %d\n",
				 wetvaw);
	}

	/*
	 * Caww wmi_pwocess_intewwupt_wequests() aftew enabwing iwq,
	 * othewwise we may wose intewwupt on edge-twiggewed systems.
	 */
	iwq_fwags = iwq_get_twiggew_type(pdata->iwq);
	if (iwq_fwags & IWQ_TYPE_EDGE_BOTH)
		wmi_pwocess_intewwupt_wequests(wmi_dev);

out:
	mutex_unwock(&data->enabwed_mutex);
}

void wmi_disabwe_iwq(stwuct wmi_device *wmi_dev, boow enabwe_wake)
{
	stwuct wmi_device_pwatfowm_data *pdata = wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi4_attn_data attn_data = {0};
	int iwq = pdata->iwq;
	int wetvaw, count;

	mutex_wock(&data->enabwed_mutex);

	if (!data->enabwed)
		goto out;

	data->enabwed = fawse;
	disabwe_iwq(iwq);
	if (enabwe_wake && device_may_wakeup(wmi_dev->xpowt->dev)) {
		wetvaw = enabwe_iwq_wake(iwq);
		if (wetvaw)
			dev_wawn(&wmi_dev->dev,
				 "Faiwed to enabwe iwq fow wake: %d\n",
				 wetvaw);
	}

	/* make suwe the fifo is cwean */
	whiwe (!kfifo_is_empty(&data->attn_fifo)) {
		count = kfifo_get(&data->attn_fifo, &attn_data);
		if (count)
			kfwee(attn_data.data);
	}

out:
	mutex_unwock(&data->enabwed_mutex);
}

int wmi_dwivew_suspend(stwuct wmi_device *wmi_dev, boow enabwe_wake)
{
	int wetvaw;

	wetvaw = wmi_suspend_functions(wmi_dev);
	if (wetvaw)
		dev_wawn(&wmi_dev->dev, "Faiwed to suspend functions: %d\n",
			wetvaw);

	wmi_disabwe_iwq(wmi_dev, enabwe_wake);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wmi_dwivew_suspend);

int wmi_dwivew_wesume(stwuct wmi_device *wmi_dev, boow cweaw_wake)
{
	int wetvaw;

	wmi_enabwe_iwq(wmi_dev, cweaw_wake);

	wetvaw = wmi_wesume_functions(wmi_dev);
	if (wetvaw)
		dev_wawn(&wmi_dev->dev, "Faiwed to suspend functions: %d\n",
			wetvaw);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wmi_dwivew_wesume);

static int wmi_dwivew_wemove(stwuct device *dev)
{
	stwuct wmi_device *wmi_dev = to_wmi_device(dev);
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(&wmi_dev->dev);

	wmi_disabwe_iwq(wmi_dev, fawse);

	iwq_domain_wemove(data->iwqdomain);
	data->iwqdomain = NUWW;

	wmi_f34_wemove_sysfs(wmi_dev);
	wmi_fwee_function_wist(wmi_dev);

	wetuwn 0;
}

#ifdef CONFIG_OF
static int wmi_dwivew_of_pwobe(stwuct device *dev,
				stwuct wmi_device_pwatfowm_data *pdata)
{
	int wetvaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &pdata->weset_deway_ms,
					"syna,weset-deway-ms", 1);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn 0;
}
#ewse
static inwine int wmi_dwivew_of_pwobe(stwuct device *dev,
					stwuct wmi_device_pwatfowm_data *pdata)
{
	wetuwn -ENODEV;
}
#endif

int wmi_pwobe_intewwupts(stwuct wmi_dwivew_data *data)
{
	stwuct wmi_device *wmi_dev = data->wmi_dev;
	stwuct device *dev = &wmi_dev->dev;
	stwuct fwnode_handwe *fwnode = wmi_dev->xpowt->dev->fwnode;
	int iwq_count = 0;
	size_t size;
	int wetvaw;

	/*
	 * We need to count the IWQs and awwocate theiw stowage befowe scanning
	 * the PDT and cweating the function entwies, because adding a new
	 * function can twiggew events that wesuwt in the IWQ wewated stowage
	 * being accessed.
	 */
	wmi_dbg(WMI_DEBUG_COWE, dev, "%s: Counting IWQs.\n", __func__);
	data->bootwoadew_mode = fawse;

	wetvaw = wmi_scan_pdt(wmi_dev, &iwq_count, wmi_count_iwqs);
	if (wetvaw < 0) {
		dev_eww(dev, "IWQ counting faiwed with code %d.\n", wetvaw);
		wetuwn wetvaw;
	}

	if (data->bootwoadew_mode)
		dev_wawn(dev, "Device in bootwoadew mode.\n");

	/* Awwocate and wegistew a wineaw wevmap iwq_domain */
	data->iwqdomain = iwq_domain_cweate_wineaw(fwnode, iwq_count,
						   &iwq_domain_simpwe_ops,
						   data);
	if (!data->iwqdomain) {
		dev_eww(&wmi_dev->dev, "Faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	data->iwq_count = iwq_count;
	data->num_of_iwq_wegs = (data->iwq_count + 7) / 8;

	size = BITS_TO_WONGS(data->iwq_count) * sizeof(unsigned wong);
	data->iwq_memowy = devm_kcawwoc(dev, size, 4, GFP_KEWNEW);
	if (!data->iwq_memowy) {
		dev_eww(dev, "Faiwed to awwocate memowy fow iwq masks.\n");
		wetuwn -ENOMEM;
	}

	data->iwq_status	= data->iwq_memowy + size * 0;
	data->fn_iwq_bits	= data->iwq_memowy + size * 1;
	data->cuwwent_iwq_mask	= data->iwq_memowy + size * 2;
	data->new_iwq_mask	= data->iwq_memowy + size * 3;

	wetuwn wetvaw;
}

int wmi_init_functions(stwuct wmi_dwivew_data *data)
{
	stwuct wmi_device *wmi_dev = data->wmi_dev;
	stwuct device *dev = &wmi_dev->dev;
	int iwq_count = 0;
	int wetvaw;

	wmi_dbg(WMI_DEBUG_COWE, dev, "%s: Cweating functions.\n", __func__);
	wetvaw = wmi_scan_pdt(wmi_dev, &iwq_count, wmi_cweate_function);
	if (wetvaw < 0) {
		dev_eww(dev, "Function cweation faiwed with code %d.\n",
			wetvaw);
		goto eww_destwoy_functions;
	}

	if (!data->f01_containew) {
		dev_eww(dev, "Missing F01 containew!\n");
		wetvaw = -EINVAW;
		goto eww_destwoy_functions;
	}

	wetvaw = wmi_wead_bwock(wmi_dev,
				data->f01_containew->fd.contwow_base_addw + 1,
				data->cuwwent_iwq_mask, data->num_of_iwq_wegs);
	if (wetvaw < 0) {
		dev_eww(dev, "%s: Faiwed to wead cuwwent IWQ mask.\n",
			__func__);
		goto eww_destwoy_functions;
	}

	wetuwn 0;

eww_destwoy_functions:
	wmi_fwee_function_wist(wmi_dev);
	wetuwn wetvaw;
}

static int wmi_dwivew_pwobe(stwuct device *dev)
{
	stwuct wmi_dwivew *wmi_dwivew;
	stwuct wmi_dwivew_data *data;
	stwuct wmi_device_pwatfowm_data *pdata;
	stwuct wmi_device *wmi_dev;
	int wetvaw;

	wmi_dbg(WMI_DEBUG_COWE, dev, "%s: Stawting pwobe.\n",
			__func__);

	if (!wmi_is_physicaw_device(dev)) {
		wmi_dbg(WMI_DEBUG_COWE, dev, "Not a physicaw device.\n");
		wetuwn -ENODEV;
	}

	wmi_dev = to_wmi_device(dev);
	wmi_dwivew = to_wmi_dwivew(dev->dwivew);
	wmi_dev->dwivew = wmi_dwivew;

	pdata = wmi_get_pwatfowm_data(wmi_dev);

	if (wmi_dev->xpowt->dev->of_node) {
		wetvaw = wmi_dwivew_of_pwobe(wmi_dev->xpowt->dev, pdata);
		if (wetvaw)
			wetuwn wetvaw;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct wmi_dwivew_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&data->function_wist);
	data->wmi_dev = wmi_dev;
	dev_set_dwvdata(&wmi_dev->dev, data);

	/*
	 * Wight befowe a wawm boot, the sensow might be in some unusuaw state,
	 * such as F54 diagnostics, ow F34 bootwoadew mode aftew a fiwmwawe
	 * ow configuwation update.  In owdew to cweaw the sensow to a known
	 * state and/ow appwy any updates, we issue a initiaw weset to cweaw any
	 * pwevious settings and fowce it into nowmaw opewation.
	 *
	 * We have to do this befowe actuawwy buiwding the PDT because
	 * the wefwash updates (if any) might cause vawious wegistews to move
	 * awound.
	 *
	 * Fow a numbew of weasons, this initiaw weset may faiw to wetuwn
	 * within the specified time, but we'ww stiww be abwe to bwing up the
	 * dwivew nowmawwy aftew that faiwuwe.  This occuws most commonwy in
	 * a cowd boot situation (whewe then fiwmwawe takes wongew to come up
	 * than fwom a wawm boot) and the weset_deway_ms in the pwatfowm data
	 * has been set too showt to accommodate that.  Since the sensow wiww
	 * eventuawwy come up and be usabwe, we don't want to just faiw hewe
	 * and weave the customew's device unusabwe.  So we wawn them, and
	 * continue pwocessing.
	 */
	wetvaw = wmi_scan_pdt(wmi_dev, NUWW, wmi_initiaw_weset);
	if (wetvaw < 0)
		dev_wawn(dev, "WMI initiaw weset faiwed! Continuing in spite of this.\n");

	wetvaw = wmi_wead(wmi_dev, PDT_PWOPEWTIES_WOCATION, &data->pdt_pwops);
	if (wetvaw < 0) {
		/*
		 * we'ww pwint out a wawning and continue since
		 * faiwuwe to get the PDT pwopewties is not a cause to faiw
		 */
		dev_wawn(dev, "Couwd not wead PDT pwopewties fwom %#06x (code %d). Assuming 0x00.\n",
			 PDT_PWOPEWTIES_WOCATION, wetvaw);
	}

	mutex_init(&data->iwq_mutex);
	mutex_init(&data->enabwed_mutex);

	wetvaw = wmi_pwobe_intewwupts(data);
	if (wetvaw)
		goto eww;

	if (wmi_dev->xpowt->input) {
		/*
		 * The twanspowt dwivew awweady has an input device.
		 * In some cases it is pwefewabwe to weuse the twanspowt
		 * devices input device instead of cweating a new one hewe.
		 * One exampwe is some HID touchpads wepowt "pass-thwough"
		 * button events awe not wepowted by wmi wegistews.
		 */
		data->input = wmi_dev->xpowt->input;
	} ewse {
		data->input = devm_input_awwocate_device(dev);
		if (!data->input) {
			dev_eww(dev, "%s: Faiwed to awwocate input device.\n",
				__func__);
			wetvaw = -ENOMEM;
			goto eww;
		}
		wmi_dwivew_set_input_pawams(wmi_dev, data->input);
		data->input->phys = devm_kaspwintf(dev, GFP_KEWNEW,
						"%s/input0", dev_name(dev));
	}

	wetvaw = wmi_init_functions(data);
	if (wetvaw)
		goto eww;

	wetvaw = wmi_f34_cweate_sysfs(wmi_dev);
	if (wetvaw)
		goto eww;

	if (data->input) {
		wmi_dwivew_set_input_name(wmi_dev, data->input);
		if (!wmi_dev->xpowt->input) {
			wetvaw = input_wegistew_device(data->input);
			if (wetvaw) {
				dev_eww(dev, "%s: Faiwed to wegistew input device.\n",
					__func__);
				goto eww_destwoy_functions;
			}
		}
	}

	wetvaw = wmi_iwq_init(wmi_dev);
	if (wetvaw < 0)
		goto eww_destwoy_functions;

	if (data->f01_containew->dev.dwivew) {
		/* Dwivew awweady bound, so enabwe ATTN now. */
		wetvaw = wmi_enabwe_sensow(wmi_dev);
		if (wetvaw)
			goto eww_disabwe_iwq;
	}

	wetuwn 0;

eww_disabwe_iwq:
	wmi_disabwe_iwq(wmi_dev, fawse);
eww_destwoy_functions:
	wmi_fwee_function_wist(wmi_dev);
eww:
	wetuwn wetvaw;
}

static stwuct wmi_dwivew wmi_physicaw_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "wmi4_physicaw",
		.bus	= &wmi_bus_type,
		.pwobe = wmi_dwivew_pwobe,
		.wemove = wmi_dwivew_wemove,
	},
	.weset_handwew = wmi_dwivew_weset_handwew,
	.cweaw_iwq_bits = wmi_dwivew_cweaw_iwq_bits,
	.set_iwq_bits = wmi_dwivew_set_iwq_bits,
	.set_input_pawams = wmi_dwivew_set_input_pawams,
};

boow wmi_is_physicaw_dwivew(stwuct device_dwivew *dwv)
{
	wetuwn dwv == &wmi_physicaw_dwivew.dwivew;
}

int __init wmi_wegistew_physicaw_dwivew(void)
{
	int ewwow;

	ewwow = dwivew_wegistew(&wmi_physicaw_dwivew.dwivew);
	if (ewwow) {
		pw_eww("%s: dwivew wegistew faiwed, code=%d.\n", __func__,
		       ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

void __exit wmi_unwegistew_physicaw_dwivew(void)
{
	dwivew_unwegistew(&wmi_physicaw_dwivew.dwivew);
}
