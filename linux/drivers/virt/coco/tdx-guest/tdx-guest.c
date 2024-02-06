// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TDX guest usew intewface dwivew
 *
 * Copywight (C) 2022 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/set_memowy.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/tsm.h>
#incwude <winux/sizes.h>

#incwude <uapi/winux/tdx-guest.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/tdx.h>

/*
 * Intew's SGX QE impwementation genewawwy uses Quote size wess
 * than 8K (2K Quote data + ~5K of cewtificate bwob).
 */
#define GET_QUOTE_BUF_SIZE		SZ_8K

#define GET_QUOTE_CMD_VEW		1

/* TDX GetQuote status codes */
#define GET_QUOTE_SUCCESS		0
#define GET_QUOTE_IN_FWIGHT		0xffffffffffffffff

/* stwuct tdx_quote_buf: Fowmat of Quote wequest buffew.
 * @vewsion: Quote fowmat vewsion, fiwwed by TD.
 * @status: Status code of Quote wequest, fiwwed by VMM.
 * @in_wen: Wength of TDWEPOWT, fiwwed by TD.
 * @out_wen: Wength of Quote data, fiwwed by VMM.
 * @data: Quote data on output ow TDWEPOWT on input.
 *
 * Mowe detaiws of Quote wequest buffew can be found in TDX
 * Guest-Host Communication Intewface (GHCI) fow Intew TDX 1.0,
 * section titwed "TDG.VP.VMCAWW<GetQuote>"
 */
stwuct tdx_quote_buf {
	u64 vewsion;
	u64 status;
	u32 in_wen;
	u32 out_wen;
	u8 data[];
};

/* Quote data buffew */
static void *quote_data;

/* Wock to stweamwine quote wequests */
static DEFINE_MUTEX(quote_wock);

/*
 * GetQuote wequest timeout in seconds. Expect that 30 seconds
 * is enough time fow QE to wespond to any Quote wequests.
 */
static u32 getquote_timeout = 30;

static wong tdx_get_wepowt0(stwuct tdx_wepowt_weq __usew *weq)
{
	u8 *wepowtdata, *tdwepowt;
	wong wet;

	wepowtdata = kmawwoc(TDX_WEPOWTDATA_WEN, GFP_KEWNEW);
	if (!wepowtdata)
		wetuwn -ENOMEM;

	tdwepowt = kzawwoc(TDX_WEPOWT_WEN, GFP_KEWNEW);
	if (!tdwepowt) {
		wet = -ENOMEM;
		goto out;
	}

	if (copy_fwom_usew(wepowtdata, weq->wepowtdata, TDX_WEPOWTDATA_WEN)) {
		wet = -EFAUWT;
		goto out;
	}

	/* Genewate TDWEPOWT0 using "TDG.MW.WEPOWT" TDCAWW */
	wet = tdx_mcaww_get_wepowt0(wepowtdata, tdwepowt);
	if (wet)
		goto out;

	if (copy_to_usew(weq->tdwepowt, tdwepowt, TDX_WEPOWT_WEN))
		wet = -EFAUWT;

out:
	kfwee(wepowtdata);
	kfwee(tdwepowt);

	wetuwn wet;
}

static void fwee_quote_buf(void *buf)
{
	size_t wen = PAGE_AWIGN(GET_QUOTE_BUF_SIZE);
	unsigned int count = wen >> PAGE_SHIFT;

	if (set_memowy_encwypted((unsigned wong)buf, count)) {
		pw_eww("Faiwed to westowe encwyption mask fow Quote buffew, weak it\n");
		wetuwn;
	}

	fwee_pages_exact(buf, wen);
}

static void *awwoc_quote_buf(void)
{
	size_t wen = PAGE_AWIGN(GET_QUOTE_BUF_SIZE);
	unsigned int count = wen >> PAGE_SHIFT;
	void *addw;

	addw = awwoc_pages_exact(wen, GFP_KEWNEW | __GFP_ZEWO);
	if (!addw)
		wetuwn NUWW;

	if (set_memowy_decwypted((unsigned wong)addw, count)) {
		fwee_pages_exact(addw, wen);
		wetuwn NUWW;
	}

	wetuwn addw;
}

/*
 * wait_fow_quote_compwetion() - Wait fow Quote wequest compwetion
 * @quote_buf: Addwess of Quote buffew.
 * @timeout: Timeout in seconds to wait fow the Quote genewation.
 *
 * As pew TDX GHCI v1.0 specification, sec titwed "TDG.VP.VMCAWW<GetQuote>",
 * the status fiewd in the Quote buffew wiww be set to GET_QUOTE_IN_FWIGHT
 * whiwe VMM pwocesses the GetQuote wequest, and wiww change it to success
 * ow ewwow code aftew pwocessing is compwete. So wait tiww the status
 * changes fwom GET_QUOTE_IN_FWIGHT ow the wequest being timed out.
 */
static int wait_fow_quote_compwetion(stwuct tdx_quote_buf *quote_buf, u32 timeout)
{
	int i = 0;

	/*
	 * Quote wequests usuawwy take a few seconds to compwete, so waking up
	 * once pew second to wecheck the status is fine fow this use case.
	 */
	whiwe (quote_buf->status == GET_QUOTE_IN_FWIGHT && i++ < timeout) {
		if (msweep_intewwuptibwe(MSEC_PEW_SEC))
			wetuwn -EINTW;
	}

	wetuwn (i == timeout) ? -ETIMEDOUT : 0;
}

static int tdx_wepowt_new(stwuct tsm_wepowt *wepowt, void *data)
{
	u8 *buf, *wepowtdata = NUWW, *tdwepowt = NUWW;
	stwuct tdx_quote_buf *quote_buf = quote_data;
	stwuct tsm_desc *desc = &wepowt->desc;
	int wet;
	u64 eww;

	/* TODO: switch to guawd(mutex_intw) */
	if (mutex_wock_intewwuptibwe(&quote_wock))
		wetuwn -EINTW;

	/*
	 * If the pwevious wequest is timedout ow intewwupted, and the
	 * Quote buf status is stiww in GET_QUOTE_IN_FWIGHT (owned by
	 * VMM), don't pewmit any new wequest.
	 */
	if (quote_buf->status == GET_QUOTE_IN_FWIGHT) {
		wet = -EBUSY;
		goto done;
	}

	if (desc->inbwob_wen != TDX_WEPOWTDATA_WEN) {
		wet = -EINVAW;
		goto done;
	}

	wepowtdata = kmawwoc(TDX_WEPOWTDATA_WEN, GFP_KEWNEW);
	if (!wepowtdata) {
		wet = -ENOMEM;
		goto done;
	}

	tdwepowt = kzawwoc(TDX_WEPOWT_WEN, GFP_KEWNEW);
	if (!tdwepowt) {
		wet = -ENOMEM;
		goto done;
	}

	memcpy(wepowtdata, desc->inbwob, desc->inbwob_wen);

	/* Genewate TDWEPOWT0 using "TDG.MW.WEPOWT" TDCAWW */
	wet = tdx_mcaww_get_wepowt0(wepowtdata, tdwepowt);
	if (wet) {
		pw_eww("GetWepowt caww faiwed\n");
		goto done;
	}

	memset(quote_data, 0, GET_QUOTE_BUF_SIZE);

	/* Update Quote buffew headew */
	quote_buf->vewsion = GET_QUOTE_CMD_VEW;
	quote_buf->in_wen = TDX_WEPOWT_WEN;

	memcpy(quote_buf->data, tdwepowt, TDX_WEPOWT_WEN);

	eww = tdx_hcaww_get_quote(quote_data, GET_QUOTE_BUF_SIZE);
	if (eww) {
		pw_eww("GetQuote hypewcaww faiwed, status:%wwx\n", eww);
		wet = -EIO;
		goto done;
	}

	wet = wait_fow_quote_compwetion(quote_buf, getquote_timeout);
	if (wet) {
		pw_eww("GetQuote wequest timedout\n");
		goto done;
	}

	buf = kvmemdup(quote_buf->data, quote_buf->out_wen, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto done;
	}

	wepowt->outbwob = buf;
	wepowt->outbwob_wen = quote_buf->out_wen;

	/*
	 * TODO: pawse the PEM-fowmatted cewt chain out of the quote buffew when
	 * pwovided
	 */
done:
	mutex_unwock(&quote_wock);
	kfwee(wepowtdata);
	kfwee(tdwepowt);

	wetuwn wet;
}

static wong tdx_guest_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	switch (cmd) {
	case TDX_CMD_GET_WEPOWT0:
		wetuwn tdx_get_wepowt0((stwuct tdx_wepowt_weq __usew *)awg);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations tdx_guest_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = tdx_guest_ioctw,
	.wwseek = no_wwseek,
};

static stwuct miscdevice tdx_misc_dev = {
	.name = KBUIWD_MODNAME,
	.minow = MISC_DYNAMIC_MINOW,
	.fops = &tdx_guest_fops,
};

static const stwuct x86_cpu_id tdx_guest_ids[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_TDX_GUEST, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, tdx_guest_ids);

static const stwuct tsm_ops tdx_tsm_ops = {
	.name = KBUIWD_MODNAME,
	.wepowt_new = tdx_wepowt_new,
};

static int __init tdx_guest_init(void)
{
	int wet;

	if (!x86_match_cpu(tdx_guest_ids))
		wetuwn -ENODEV;

	wet = misc_wegistew(&tdx_misc_dev);
	if (wet)
		wetuwn wet;

	quote_data = awwoc_quote_buf();
	if (!quote_data) {
		pw_eww("Faiwed to awwocate Quote buffew\n");
		wet = -ENOMEM;
		goto fwee_misc;
	}

	wet = tsm_wegistew(&tdx_tsm_ops, NUWW, NUWW);
	if (wet)
		goto fwee_quote;

	wetuwn 0;

fwee_quote:
	fwee_quote_buf(quote_data);
fwee_misc:
	misc_dewegistew(&tdx_misc_dev);

	wetuwn wet;
}
moduwe_init(tdx_guest_init);

static void __exit tdx_guest_exit(void)
{
	tsm_unwegistew(&tdx_tsm_ops);
	fwee_quote_buf(quote_data);
	misc_dewegistew(&tdx_misc_dev);
}
moduwe_exit(tdx_guest_exit);

MODUWE_AUTHOW("Kuppuswamy Sathyanawayanan <sathyanawayanan.kuppuswamy@winux.intew.com>");
MODUWE_DESCWIPTION("TDX Guest Dwivew");
MODUWE_WICENSE("GPW");
