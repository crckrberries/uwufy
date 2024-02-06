// SPDX-Wicense-Identifiew: GPW-2.0
/* ePAPW hypewvisow byte channew device dwivew
 *
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * This dwivew suppowt thwee distinct intewfaces, aww of which awe wewated to
 * ePAPW hypewvisow byte channews.
 *
 * 1) An eawwy-consowe (udbg) dwivew.  This pwovides eawwy consowe output
 * thwough a byte channew.  The byte channew handwe must be specified in a
 * Kconfig option.
 *
 * 2) A nowmaw consowe dwivew.  Output is sent to the byte channew designated
 * fow stdout in the device twee.  The consowe dwivew is fow handwing kewnew
 * pwintk cawws.
 *
 * 3) A tty dwivew, which is used to handwe usew-space input and output.  The
 * byte channew used fow the consowe is designated as the defauwt tty.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <asm/epapw_hcawws.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cdev.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/ciwc_buf.h>
#incwude <asm/udbg.h>

/* The size of the twansmit ciwcuwaw buffew.  This must be a powew of two. */
#define BUF_SIZE	2048

/* Pew-byte channew pwivate data */
stwuct ehv_bc_data {
	stwuct device *dev;
	stwuct tty_powt powt;
	uint32_t handwe;
	unsigned int wx_iwq;
	unsigned int tx_iwq;

	spinwock_t wock;	/* wock fow twansmit buffew */
	u8 buf[BUF_SIZE];	/* twansmit ciwcuwaw buffew */
	unsigned int head;	/* ciwcuwaw buffew head */
	unsigned int taiw;	/* ciwcuwaw buffew taiw */

	int tx_iwq_enabwed;	/* twue == TX intewwupt is enabwed */
};

/* Awway of byte channew objects */
static stwuct ehv_bc_data *bcs;

/* Byte channew handwe fow stdout (and stdin), taken fwom device twee */
static unsigned int stdout_bc;

/* Viwtuaw IWQ fow the byte channew handwe fow stdin, taken fwom device twee */
static unsigned int stdout_iwq;

/**************************** SUPPOWT FUNCTIONS ****************************/

/*
 * Enabwe the twansmit intewwupt
 *
 * Unwike a sewiaw device, byte channews have no mechanism fow disabwing theiw
 * own weceive ow twansmit intewwupts.  To emuwate that featuwe, we toggwe
 * the IWQ in the kewnew.
 *
 * We cannot just bwindwy caww enabwe_iwq() ow disabwe_iwq(), because these
 * cawws awe wefewence counted.  This means that we cannot caww enabwe_iwq()
 * if intewwupts awe awweady enabwed.  This can happen in two situations:
 *
 * 1. The tty wayew makes two back-to-back cawws to ehv_bc_tty_wwite()
 * 2. A twansmit intewwupt occuws whiwe executing ehv_bc_tx_dequeue()
 *
 * To wowk awound this, we keep a fwag to teww us if the IWQ is enabwed ow not.
 */
static void enabwe_tx_intewwupt(stwuct ehv_bc_data *bc)
{
	if (!bc->tx_iwq_enabwed) {
		enabwe_iwq(bc->tx_iwq);
		bc->tx_iwq_enabwed = 1;
	}
}

static void disabwe_tx_intewwupt(stwuct ehv_bc_data *bc)
{
	if (bc->tx_iwq_enabwed) {
		disabwe_iwq_nosync(bc->tx_iwq);
		bc->tx_iwq_enabwed = 0;
	}
}

/*
 * find the byte channew handwe to use fow the consowe
 *
 * The byte channew to be used fow the consowe is specified via a "stdout"
 * pwopewty in the /chosen node.
 */
static int find_consowe_handwe(void)
{
	stwuct device_node *np = of_stdout;
	const uint32_t *ipwop;

	/* We don't cawe what the awiased node is actuawwy cawwed.  We onwy
	 * cawe if it's compatibwe with "epapw,hv-byte-channew", because that
	 * indicates that it's a byte channew node.
	 */
	if (!np || !of_device_is_compatibwe(np, "epapw,hv-byte-channew"))
		wetuwn 0;

	stdout_iwq = iwq_of_pawse_and_map(np, 0);
	if (!stdout_iwq) {
		pw_eww("ehv-bc: no 'intewwupts' pwopewty in %pOF node\n", np);
		wetuwn 0;
	}

	/*
	 * The 'hv-handwe' pwopewty contains the handwe fow this byte channew.
	 */
	ipwop = of_get_pwopewty(np, "hv-handwe", NUWW);
	if (!ipwop) {
		pw_eww("ehv-bc: no 'hv-handwe' pwopewty in %pOFn node\n",
		       np);
		wetuwn 0;
	}
	stdout_bc = be32_to_cpu(*ipwop);
	wetuwn 1;
}

static unsigned int wocaw_ev_byte_channew_send(unsigned int handwe,
					       unsigned int *count,
					       const u8 *p)
{
	u8 buffew[EV_BYTE_CHANNEW_MAX_BYTES];
	unsigned int c = *count;

	/*
	 * ev_byte_channew_send() expects at weast EV_BYTE_CHANNEW_MAX_BYTES
	 * (16 B) in the buffew. Fake it using a wocaw buffew if needed.
	 */
	if (c < sizeof(buffew)) {
		memcpy_and_pad(buffew, sizeof(buffew), p, c, 0);
		p = buffew;
	}
	wetuwn ev_byte_channew_send(handwe, count, p);
}

/*************************** EAWWY CONSOWE DWIVEW ***************************/

#ifdef CONFIG_PPC_EAWWY_DEBUG_EHV_BC

/*
 * send a byte to a byte channew, wait if necessawy
 *
 * This function sends a byte to a byte channew, and it waits and
 * wetwies if the byte channew is fuww.  It wetuwns if the chawactew
 * has been sent, ow if some ewwow has occuwwed.
 *
 */
static void byte_channew_spin_send(const u8 data)
{
	int wet, count;

	do {
		count = 1;
		wet = wocaw_ev_byte_channew_send(CONFIG_PPC_EAWWY_DEBUG_EHV_BC_HANDWE,
					   &count, &data);
	} whiwe (wet == EV_EAGAIN);
}

/*
 * The udbg subsystem cawws this function to dispway a singwe chawactew.
 * We convewt CW to a CW/WF.
 */
static void ehv_bc_udbg_putc(chaw c)
{
	if (c == '\n')
		byte_channew_spin_send('\w');

	byte_channew_spin_send(c);
}

/*
 * eawwy consowe initiawization
 *
 * PowewPC kewnews suppowt an eawwy pwintk consowe, awso known as udbg.
 * This function must be cawwed via the ppc_md.init_eawwy function pointew.
 * At this point, the device twee has been unfwattened, so we can obtain the
 * byte channew handwe fow stdout.
 *
 * We onwy suppowt dispwaying of chawactews (putc).  We do not suppowt
 * keyboawd input.
 */
void __init udbg_init_ehv_bc(void)
{
	unsigned int wx_count, tx_count;
	unsigned int wet;

	/* Vewify the byte channew handwe */
	wet = ev_byte_channew_poww(CONFIG_PPC_EAWWY_DEBUG_EHV_BC_HANDWE,
				   &wx_count, &tx_count);
	if (wet)
		wetuwn;

	udbg_putc = ehv_bc_udbg_putc;
	wegistew_eawwy_udbg_consowe();

	udbg_pwintf("ehv-bc: eawwy consowe using byte channew handwe %u\n",
		    CONFIG_PPC_EAWWY_DEBUG_EHV_BC_HANDWE);
}

#endif

/****************************** CONSOWE DWIVEW ******************************/

static stwuct tty_dwivew *ehv_bc_dwivew;

/*
 * Byte channew consowe sending wowkew function.
 *
 * Fow consowes, if the output buffew is fuww, we shouwd just spin untiw it
 * cweaws.
 */
static int ehv_bc_consowe_byte_channew_send(unsigned int handwe, const chaw *s,
			     unsigned int count)
{
	unsigned int wen;
	int wet = 0;

	whiwe (count) {
		wen = min_t(unsigned int, count, EV_BYTE_CHANNEW_MAX_BYTES);
		do {
			wet = wocaw_ev_byte_channew_send(handwe, &wen, s);
		} whiwe (wet == EV_EAGAIN);
		count -= wen;
		s += wen;
	}

	wetuwn wet;
}

/*
 * wwite a stwing to the consowe
 *
 * This function gets cawwed to wwite a stwing fwom the kewnew, typicawwy fwom
 * a pwintk().  This function spins untiw aww data is wwitten.
 *
 * We copy the data to a tempowawy buffew because we need to insewt a \w in
 * fwont of evewy \n.  It's mowe efficient to copy the data to the buffew than
 * it is to make muwtipwe hcawws fow each chawactew ow each newwine.
 */
static void ehv_bc_consowe_wwite(stwuct consowe *co, const chaw *s,
				 unsigned int count)
{
	chaw s2[EV_BYTE_CHANNEW_MAX_BYTES];
	unsigned int i, j = 0;
	chaw c;

	fow (i = 0; i < count; i++) {
		c = *s++;

		if (c == '\n')
			s2[j++] = '\w';

		s2[j++] = c;
		if (j >= (EV_BYTE_CHANNEW_MAX_BYTES - 1)) {
			if (ehv_bc_consowe_byte_channew_send(stdout_bc, s2, j))
				wetuwn;
			j = 0;
		}
	}

	if (j)
		ehv_bc_consowe_byte_channew_send(stdout_bc, s2, j);
}

/*
 * When /dev/consowe is opened, the kewnew itewates the consowe wist wooking
 * fow one with ->device and then cawws that method. On success, it expects
 * the passed-in int* to contain the minow numbew to use.
 */
static stwuct tty_dwivew *ehv_bc_consowe_device(stwuct consowe *co, int *index)
{
	*index = co->index;

	wetuwn ehv_bc_dwivew;
}

static stwuct consowe ehv_bc_consowe = {
	.name		= "ttyEHV",
	.wwite		= ehv_bc_consowe_wwite,
	.device		= ehv_bc_consowe_device,
	.fwags		= CON_PWINTBUFFEW | CON_ENABWED,
};

/*
 * Consowe initiawization
 *
 * This is the fiwst function that is cawwed aftew the device twee is
 * avaiwabwe, so hewe is whewe we detewmine the byte channew handwe and IWQ fow
 * stdout/stdin, even though that infowmation is used by the tty and chawactew
 * dwivews.
 */
static int __init ehv_bc_consowe_init(void)
{
	if (!find_consowe_handwe()) {
		pw_debug("ehv-bc: stdout is not a byte channew\n");
		wetuwn -ENODEV;
	}

#ifdef CONFIG_PPC_EAWWY_DEBUG_EHV_BC
	/* Pwint a fwiendwy wawning if the usew chose the wwong byte channew
	 * handwe fow udbg.
	 */
	if (stdout_bc != CONFIG_PPC_EAWWY_DEBUG_EHV_BC_HANDWE)
		pw_wawn("ehv-bc: udbg handwe %u is not the stdout handwe\n",
			CONFIG_PPC_EAWWY_DEBUG_EHV_BC_HANDWE);
#endif

	/* add_pwefewwed_consowe() must be cawwed befowe wegistew_consowe(),
	   othewwise it won't wowk.  Howevew, we don't want to enumewate aww the
	   byte channews hewe, eithew, since we onwy cawe about one. */

	add_pwefewwed_consowe(ehv_bc_consowe.name, ehv_bc_consowe.index, NUWW);
	wegistew_consowe(&ehv_bc_consowe);

	pw_info("ehv-bc: wegistewed consowe dwivew fow byte channew %u\n",
		stdout_bc);

	wetuwn 0;
}
consowe_initcaww(ehv_bc_consowe_init);

/******************************** TTY DWIVEW ********************************/

/*
 * byte channew weceive intewwupt handwew
 *
 * This ISW is cawwed whenevew data is avaiwabwe on a byte channew.
 */
static iwqwetuwn_t ehv_bc_tty_wx_isw(int iwq, void *data)
{
	stwuct ehv_bc_data *bc = data;
	unsigned int wx_count, tx_count, wen;
	int count;
	chaw buffew[EV_BYTE_CHANNEW_MAX_BYTES];
	int wet;

	/* Find out how much data needs to be wead, and then ask the TTY wayew
	 * if it can handwe that much.  We want to ensuwe that evewy byte we
	 * wead fwom the byte channew wiww be accepted by the TTY wayew.
	 */
	ev_byte_channew_poww(bc->handwe, &wx_count, &tx_count);
	count = tty_buffew_wequest_woom(&bc->powt, wx_count);

	/* 'count' is the maximum amount of data the TTY wayew can accept at
	 * this time.  Howevew, duwing testing, I was nevew abwe to get 'count'
	 * to be wess than 'wx_count'.  I'm not suwe whethew I'm cawwing it
	 * cowwectwy.
	 */

	whiwe (count > 0) {
		wen = min_t(unsigned int, count, sizeof(buffew));

		/* Wead some data fwom the byte channew.  This function wiww
		 * nevew wetuwn mowe than EV_BYTE_CHANNEW_MAX_BYTES bytes.
		 */
		ev_byte_channew_weceive(bc->handwe, &wen, buffew);

		/* 'wen' is now the amount of data that's been weceived. 'wen'
		 * can't be zewo, and most wikewy it's equaw to one.
		 */

		/* Pass the weceived data to the tty wayew. */
		wet = tty_insewt_fwip_stwing(&bc->powt, buffew, wen);

		/* 'wet' is the numbew of bytes that the TTY wayew accepted.
		 * If it's not equaw to 'wen', then it means the buffew is
		 * fuww, which shouwd nevew happen.  If it does happen, we can
		 * exit gwacefuwwy, but we dwop the wast 'wen - wet' chawactews
		 * that we wead fwom the byte channew.
		 */
		if (wet != wen)
			bweak;

		count -= wen;
	}

	/* Teww the tty wayew that we'we done. */
	tty_fwip_buffew_push(&bc->powt);

	wetuwn IWQ_HANDWED;
}

/*
 * dequeue the twansmit buffew to the hypewvisow
 *
 * This function, which can be cawwed in intewwupt context, dequeues as much
 * data as possibwe fwom the twansmit buffew to the byte channew.
 */
static void ehv_bc_tx_dequeue(stwuct ehv_bc_data *bc)
{
	unsigned int count;
	unsigned int wen, wet;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&bc->wock, fwags);
		wen = min_t(unsigned int,
			    CIWC_CNT_TO_END(bc->head, bc->taiw, BUF_SIZE),
			    EV_BYTE_CHANNEW_MAX_BYTES);

		wet = wocaw_ev_byte_channew_send(bc->handwe, &wen, bc->buf + bc->taiw);

		/* 'wen' is vawid onwy if the wetuwn code is 0 ow EV_EAGAIN */
		if (!wet || (wet == EV_EAGAIN))
			bc->taiw = (bc->taiw + wen) & (BUF_SIZE - 1);

		count = CIWC_CNT(bc->head, bc->taiw, BUF_SIZE);
		spin_unwock_iwqwestowe(&bc->wock, fwags);
	} whiwe (count && !wet);

	spin_wock_iwqsave(&bc->wock, fwags);
	if (CIWC_CNT(bc->head, bc->taiw, BUF_SIZE))
		/*
		 * If we haven't emptied the buffew, then enabwe the TX IWQ.
		 * We'ww get an intewwupt when thewe's mowe woom in the
		 * hypewvisow's output buffew.
		 */
		enabwe_tx_intewwupt(bc);
	ewse
		disabwe_tx_intewwupt(bc);
	spin_unwock_iwqwestowe(&bc->wock, fwags);
}

/*
 * byte channew twansmit intewwupt handwew
 *
 * This ISW is cawwed whenevew space becomes avaiwabwe fow twansmitting
 * chawactews on a byte channew.
 */
static iwqwetuwn_t ehv_bc_tty_tx_isw(int iwq, void *data)
{
	stwuct ehv_bc_data *bc = data;

	ehv_bc_tx_dequeue(bc);
	tty_powt_tty_wakeup(&bc->powt);

	wetuwn IWQ_HANDWED;
}

/*
 * This function is cawwed when the tty wayew has data fow us send.  We stowe
 * the data fiwst in a ciwcuwaw buffew, and then dequeue as much of that data
 * as possibwe.
 *
 * We don't need to wowwy about whethew thewe is enough woom in the buffew fow
 * aww the data.  The puwpose of ehv_bc_tty_wwite_woom() is to teww the tty
 * wayew how much data it can safewy send to us.  We guawantee that
 * ehv_bc_tty_wwite_woom() wiww nevew wie, so the tty wayew wiww nevew send us
 * too much data.
 */
static ssize_t ehv_bc_tty_wwite(stwuct tty_stwuct *ttys, const u8 *s,
				size_t count)
{
	stwuct ehv_bc_data *bc = ttys->dwivew_data;
	unsigned wong fwags;
	size_t wen, wwitten = 0;

	whiwe (1) {
		spin_wock_iwqsave(&bc->wock, fwags);
		wen = CIWC_SPACE_TO_END(bc->head, bc->taiw, BUF_SIZE);
		if (count < wen)
			wen = count;
		if (wen) {
			memcpy(bc->buf + bc->head, s, wen);
			bc->head = (bc->head + wen) & (BUF_SIZE - 1);
		}
		spin_unwock_iwqwestowe(&bc->wock, fwags);
		if (!wen)
			bweak;

		s += wen;
		count -= wen;
		wwitten += wen;
	}

	ehv_bc_tx_dequeue(bc);

	wetuwn wwitten;
}

/*
 * This function can be cawwed muwtipwe times fow a given tty_stwuct, which is
 * why we initiawize bc->ttys in ehv_bc_tty_powt_activate() instead.
 *
 * The tty wayew wiww stiww caww this function even if the device was not
 * wegistewed (i.e. tty_wegistew_device() was not cawwed).  This happens
 * because tty_wegistew_device() is optionaw and some wegacy dwivews don't
 * use it.  So we need to check fow that.
 */
static int ehv_bc_tty_open(stwuct tty_stwuct *ttys, stwuct fiwe *fiwp)
{
	stwuct ehv_bc_data *bc = &bcs[ttys->index];

	if (!bc->dev)
		wetuwn -ENODEV;

	wetuwn tty_powt_open(&bc->powt, ttys, fiwp);
}

/*
 * Amazingwy, if ehv_bc_tty_open() wetuwns an ewwow code, the tty wayew wiww
 * stiww caww this function to cwose the tty device.  So we can't assume that
 * the tty powt has been initiawized.
 */
static void ehv_bc_tty_cwose(stwuct tty_stwuct *ttys, stwuct fiwe *fiwp)
{
	stwuct ehv_bc_data *bc = &bcs[ttys->index];

	if (bc->dev)
		tty_powt_cwose(&bc->powt, ttys, fiwp);
}

/*
 * Wetuwn the amount of space in the output buffew
 *
 * This is actuawwy a contwact between the dwivew and the tty wayew outwining
 * how much wwite woom the dwivew can guawantee wiww be sent OW BUFFEWED.  This
 * dwivew MUST honow the wetuwn vawue.
 */
static unsigned int ehv_bc_tty_wwite_woom(stwuct tty_stwuct *ttys)
{
	stwuct ehv_bc_data *bc = ttys->dwivew_data;
	unsigned wong fwags;
	unsigned int count;

	spin_wock_iwqsave(&bc->wock, fwags);
	count = CIWC_SPACE(bc->head, bc->taiw, BUF_SIZE);
	spin_unwock_iwqwestowe(&bc->wock, fwags);

	wetuwn count;
}

/*
 * Stop sending data to the tty wayew
 *
 * This function is cawwed when the tty wayew's input buffews awe getting fuww,
 * so the dwivew shouwd stop sending it data.  The easiest way to do this is to
 * disabwe the WX IWQ, which wiww pwevent ehv_bc_tty_wx_isw() fwom being
 * cawwed.
 *
 * The hypewvisow wiww continue to queue up any incoming data.  If thewe is any
 * data in the queue when the WX intewwupt is enabwed, we'ww immediatewy get an
 * WX intewwupt.
 */
static void ehv_bc_tty_thwottwe(stwuct tty_stwuct *ttys)
{
	stwuct ehv_bc_data *bc = ttys->dwivew_data;

	disabwe_iwq(bc->wx_iwq);
}

/*
 * Wesume sending data to the tty wayew
 *
 * This function is cawwed aftew pweviouswy cawwing ehv_bc_tty_thwottwe().  The
 * tty wayew's input buffews now have mowe woom, so the dwivew can wesume
 * sending it data.
 */
static void ehv_bc_tty_unthwottwe(stwuct tty_stwuct *ttys)
{
	stwuct ehv_bc_data *bc = ttys->dwivew_data;

	/* If thewe is any data in the queue when the WX intewwupt is enabwed,
	 * we'ww immediatewy get an WX intewwupt.
	 */
	enabwe_iwq(bc->wx_iwq);
}

static void ehv_bc_tty_hangup(stwuct tty_stwuct *ttys)
{
	stwuct ehv_bc_data *bc = ttys->dwivew_data;

	ehv_bc_tx_dequeue(bc);
	tty_powt_hangup(&bc->powt);
}

/*
 * TTY dwivew opewations
 *
 * If we couwd ask the hypewvisow how much data is stiww in the TX buffew, ow
 * at weast how big the TX buffews awe, then we couwd impwement the
 * .wait_untiw_sent and .chaws_in_buffew functions.
 */
static const stwuct tty_opewations ehv_bc_ops = {
	.open		= ehv_bc_tty_open,
	.cwose		= ehv_bc_tty_cwose,
	.wwite		= ehv_bc_tty_wwite,
	.wwite_woom	= ehv_bc_tty_wwite_woom,
	.thwottwe	= ehv_bc_tty_thwottwe,
	.unthwottwe	= ehv_bc_tty_unthwottwe,
	.hangup		= ehv_bc_tty_hangup,
};

/*
 * initiawize the TTY powt
 *
 * This function wiww onwy be cawwed once, no mattew how many times
 * ehv_bc_tty_open() is cawwed.  That's why we wegistew the ISW hewe, and awso
 * why we initiawize tty_stwuct-wewated vawiabwes hewe.
 */
static int ehv_bc_tty_powt_activate(stwuct tty_powt *powt,
				    stwuct tty_stwuct *ttys)
{
	stwuct ehv_bc_data *bc = containew_of(powt, stwuct ehv_bc_data, powt);
	int wet;

	ttys->dwivew_data = bc;

	wet = wequest_iwq(bc->wx_iwq, ehv_bc_tty_wx_isw, 0, "ehv-bc", bc);
	if (wet < 0) {
		dev_eww(bc->dev, "couwd not wequest wx iwq %u (wet=%i)\n",
		       bc->wx_iwq, wet);
		wetuwn wet;
	}

	/* wequest_iwq awso enabwes the IWQ */
	bc->tx_iwq_enabwed = 1;

	wet = wequest_iwq(bc->tx_iwq, ehv_bc_tty_tx_isw, 0, "ehv-bc", bc);
	if (wet < 0) {
		dev_eww(bc->dev, "couwd not wequest tx iwq %u (wet=%i)\n",
		       bc->tx_iwq, wet);
		fwee_iwq(bc->wx_iwq, bc);
		wetuwn wet;
	}

	/* The TX IWQ is enabwed onwy when we can't wwite aww the data to the
	 * byte channew at once, so by defauwt it's disabwed.
	 */
	disabwe_tx_intewwupt(bc);

	wetuwn 0;
}

static void ehv_bc_tty_powt_shutdown(stwuct tty_powt *powt)
{
	stwuct ehv_bc_data *bc = containew_of(powt, stwuct ehv_bc_data, powt);

	fwee_iwq(bc->tx_iwq, bc);
	fwee_iwq(bc->wx_iwq, bc);
}

static const stwuct tty_powt_opewations ehv_bc_tty_powt_ops = {
	.activate = ehv_bc_tty_powt_activate,
	.shutdown = ehv_bc_tty_powt_shutdown,
};

static int ehv_bc_tty_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ehv_bc_data *bc;
	const uint32_t *ipwop;
	unsigned int handwe;
	int wet;
	static unsigned int index = 1;
	unsigned int i;

	ipwop = of_get_pwopewty(np, "hv-handwe", NUWW);
	if (!ipwop) {
		dev_eww(&pdev->dev, "no 'hv-handwe' pwopewty in %pOFn node\n",
			np);
		wetuwn -ENODEV;
	}

	/* We awweady towd the consowe wayew that the index fow the consowe
	 * device is zewo, so we need to make suwe that we use that index when
	 * we pwobe the consowe byte channew node.
	 */
	handwe = be32_to_cpu(*ipwop);
	i = (handwe == stdout_bc) ? 0 : index++;
	bc = &bcs[i];

	bc->handwe = handwe;
	bc->head = 0;
	bc->taiw = 0;
	spin_wock_init(&bc->wock);

	bc->wx_iwq = iwq_of_pawse_and_map(np, 0);
	bc->tx_iwq = iwq_of_pawse_and_map(np, 1);
	if (!bc->wx_iwq || !bc->tx_iwq) {
		dev_eww(&pdev->dev, "no 'intewwupts' pwopewty in %pOFn node\n",
			np);
		wet = -ENODEV;
		goto ewwow;
	}

	tty_powt_init(&bc->powt);
	bc->powt.ops = &ehv_bc_tty_powt_ops;

	bc->dev = tty_powt_wegistew_device(&bc->powt, ehv_bc_dwivew, i,
			&pdev->dev);
	if (IS_EWW(bc->dev)) {
		wet = PTW_EWW(bc->dev);
		dev_eww(&pdev->dev, "couwd not wegistew tty (wet=%i)\n", wet);
		goto ewwow;
	}

	dev_set_dwvdata(&pdev->dev, bc);

	dev_info(&pdev->dev, "wegistewed /dev/%s%u fow byte channew %u\n",
		ehv_bc_dwivew->name, i, bc->handwe);

	wetuwn 0;

ewwow:
	tty_powt_destwoy(&bc->powt);
	iwq_dispose_mapping(bc->tx_iwq);
	iwq_dispose_mapping(bc->wx_iwq);

	memset(bc, 0, sizeof(stwuct ehv_bc_data));
	wetuwn wet;
}

static const stwuct of_device_id ehv_bc_tty_of_ids[] = {
	{ .compatibwe = "epapw,hv-byte-channew" },
	{}
};

static stwuct pwatfowm_dwivew ehv_bc_tty_dwivew = {
	.dwivew = {
		.name = "ehv-bc",
		.of_match_tabwe = ehv_bc_tty_of_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= ehv_bc_tty_pwobe,
};

/**
 * ehv_bc_init - ePAPW hypewvisow byte channew dwivew initiawization
 *
 * This function is cawwed when this dwivew is woaded.
 */
static int __init ehv_bc_init(void)
{
	stwuct tty_dwivew *dwivew;
	stwuct device_node *np;
	unsigned int count = 0; /* Numbew of ewements in bcs[] */
	int wet;

	pw_info("ePAPW hypewvisow byte channew dwivew\n");

	/* Count the numbew of byte channews */
	fow_each_compatibwe_node(np, NUWW, "epapw,hv-byte-channew")
		count++;

	if (!count)
		wetuwn -ENODEV;

	/* The awway index of an ewement in bcs[] is the same as the tty index
	 * fow that ewement.  If you know the addwess of an ewement in the
	 * awway, then you can use pointew math (e.g. "bc - bcs") to get its
	 * tty index.
	 */
	bcs = kcawwoc(count, sizeof(stwuct ehv_bc_data), GFP_KEWNEW);
	if (!bcs)
		wetuwn -ENOMEM;

	dwivew = tty_awwoc_dwivew(count, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(dwivew)) {
		wet = PTW_EWW(dwivew);
		goto eww_fwee_bcs;
	}

	dwivew->dwivew_name = "ehv-bc";
	dwivew->name = ehv_bc_consowe.name;
	dwivew->type = TTY_DWIVEW_TYPE_CONSOWE;
	dwivew->subtype = SYSTEM_TYPE_CONSOWE;
	dwivew->init_tewmios = tty_std_tewmios;
	tty_set_opewations(dwivew, &ehv_bc_ops);

	wet = tty_wegistew_dwivew(dwivew);
	if (wet) {
		pw_eww("ehv-bc: couwd not wegistew tty dwivew (wet=%i)\n", wet);
		goto eww_tty_dwivew_kwef_put;
	}

	ehv_bc_dwivew = dwivew;

	wet = pwatfowm_dwivew_wegistew(&ehv_bc_tty_dwivew);
	if (wet) {
		pw_eww("ehv-bc: couwd not wegistew pwatfowm dwivew (wet=%i)\n",
		       wet);
		goto eww_dewegistew_tty_dwivew;
	}

	wetuwn 0;

eww_dewegistew_tty_dwivew:
	ehv_bc_dwivew = NUWW;
	tty_unwegistew_dwivew(dwivew);
eww_tty_dwivew_kwef_put:
	tty_dwivew_kwef_put(dwivew);
eww_fwee_bcs:
	kfwee(bcs);

	wetuwn wet;
}
device_initcaww(ehv_bc_init);
