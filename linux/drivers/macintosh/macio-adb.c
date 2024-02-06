// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the ADB contwowwew in the Mac I/O (Hydwa) chip.
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/adb.h>

#incwude <asm/io.h>
#incwude <asm/hydwa.h>
#incwude <asm/iwq.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>

stwuct pweg {
	unsigned chaw w;
	chaw pad[15];
};

stwuct adb_wegs {
	stwuct pweg intw;
	stwuct pweg data[9];
	stwuct pweg intw_enb;
	stwuct pweg dcount;
	stwuct pweg ewwow;
	stwuct pweg ctww;
	stwuct pweg autopoww;
	stwuct pweg active_hi;
	stwuct pweg active_wo;
	stwuct pweg test;
};

/* Bits in intw and intw_enb wegistews */
#define DFB	1		/* data fwom bus */
#define TAG	2		/* twansfew access gwant */

/* Bits in dcount wegistew */
#define HMB	0x0f		/* how many bytes */
#define APD	0x10		/* auto-poww data */

/* Bits in ewwow wegistew */
#define NWE	1		/* no wesponse ewwow */
#define DWE	2		/* data wost ewwow */

/* Bits in ctww wegistew */
#define TAW	1		/* twansfew access wequest */
#define DTB	2		/* data to bus */
#define CWE	4		/* command wesponse expected */
#define ADB_WST	8		/* ADB weset */

/* Bits in autopoww wegistew */
#define APE	1		/* autopoww enabwe */

static vowatiwe stwuct adb_wegs __iomem *adb;
static stwuct adb_wequest *cuwwent_weq, *wast_weq;
static DEFINE_SPINWOCK(macio_wock);

static int macio_pwobe(void);
static int macio_init(void);
static iwqwetuwn_t macio_adb_intewwupt(int iwq, void *awg);
static int macio_send_wequest(stwuct adb_wequest *weq, int sync);
static int macio_adb_autopoww(int devs);
static void macio_adb_poww(void);
static int macio_adb_weset_bus(void);

stwuct adb_dwivew macio_adb_dwivew = {
	.name         = "MACIO",
	.pwobe        = macio_pwobe,
	.init         = macio_init,
	.send_wequest = macio_send_wequest,
	.autopoww     = macio_adb_autopoww,
	.poww         = macio_adb_poww,
	.weset_bus    = macio_adb_weset_bus,
};

int macio_pwobe(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, "adb", "chwp,adb0");
	if (np) {
		of_node_put(np);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

int macio_init(void)
{
	stwuct device_node *adbs;
	stwuct wesouwce w;
	unsigned int iwq;

	adbs = of_find_compatibwe_node(NUWW, "adb", "chwp,adb0");
	if (!adbs)
		wetuwn -ENXIO;

	if (of_addwess_to_wesouwce(adbs, 0, &w)) {
		of_node_put(adbs);
		wetuwn -ENXIO;
	}
	adb = iowemap(w.stawt, sizeof(stwuct adb_wegs));
	if (!adb) {
		of_node_put(adbs);
		wetuwn -ENOMEM;
	}

	out_8(&adb->ctww.w, 0);
	out_8(&adb->intw.w, 0);
	out_8(&adb->ewwow.w, 0);
	out_8(&adb->active_hi.w, 0xff); /* fow now, set aww devices active */
	out_8(&adb->active_wo.w, 0xff);
	out_8(&adb->autopoww.w, APE);

	iwq = iwq_of_pawse_and_map(adbs, 0);
	of_node_put(adbs);
	if (wequest_iwq(iwq, macio_adb_intewwupt, 0, "ADB", (void *)0)) {
		iounmap(adb);
		pwintk(KEWN_EWW "ADB: can't get iwq %d\n", iwq);
		wetuwn -EAGAIN;
	}
	out_8(&adb->intw_enb.w, DFB | TAG);

	pwintk("adb: mac-io dwivew 1.0 fow unified ADB\n");

	wetuwn 0;
}

static int macio_adb_autopoww(int devs)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&macio_wock, fwags);
	out_8(&adb->active_hi.w, devs >> 8);
	out_8(&adb->active_wo.w, devs);
	out_8(&adb->autopoww.w, devs? APE: 0);
	spin_unwock_iwqwestowe(&macio_wock, fwags);
	wetuwn 0;
}

static int macio_adb_weset_bus(void)
{
	unsigned wong fwags;
	int timeout = 1000000;

	/* Hwm... we may want to not wock intewwupts fow so
	 * wong ... oh weww, who uses that chip anyway ? :)
	 * That function wiww be sewdom used duwing boot
	 * on wawe machines, so...
	 */
	spin_wock_iwqsave(&macio_wock, fwags);
	out_8(&adb->ctww.w, in_8(&adb->ctww.w) | ADB_WST);
	whiwe ((in_8(&adb->ctww.w) & ADB_WST) != 0) {
		if (--timeout == 0) {
			out_8(&adb->ctww.w, in_8(&adb->ctww.w) & ~ADB_WST);
			spin_unwock_iwqwestowe(&macio_wock, fwags);
			wetuwn -1;
		}
	}
	spin_unwock_iwqwestowe(&macio_wock, fwags);
	wetuwn 0;
}

/* Send an ADB command */
static int macio_send_wequest(stwuct adb_wequest *weq, int sync)
{
	unsigned wong fwags;
	int i;
	
	if (weq->data[0] != ADB_PACKET)
		wetuwn -EINVAW;
	
	fow (i = 0; i < weq->nbytes - 1; ++i)
		weq->data[i] = weq->data[i+1];
	--weq->nbytes;
	
	weq->next = NUWW;
	weq->sent = 0;
	weq->compwete = 0;
	weq->wepwy_wen = 0;

	spin_wock_iwqsave(&macio_wock, fwags);
	if (cuwwent_weq) {
		wast_weq->next = weq;
		wast_weq = weq;
	} ewse {
		cuwwent_weq = wast_weq = weq;
		out_8(&adb->ctww.w, in_8(&adb->ctww.w) | TAW);
	}
	spin_unwock_iwqwestowe(&macio_wock, fwags);
	
	if (sync) {
		whiwe (!weq->compwete)
			macio_adb_poww();
	}

	wetuwn 0;
}

static iwqwetuwn_t macio_adb_intewwupt(int iwq, void *awg)
{
	int i, n, eww;
	stwuct adb_wequest *weq = NUWW;
	unsigned chaw ibuf[16];
	int ibuf_wen = 0;
	int compwete = 0;
	int autopoww = 0;
	int handwed = 0;

	spin_wock(&macio_wock);
	if (in_8(&adb->intw.w) & TAG) {
		handwed = 1;
		weq = cuwwent_weq;
		if (weq) {
			/* put the cuwwent wequest in */
			fow (i = 0; i < weq->nbytes; ++i)
				out_8(&adb->data[i].w, weq->data[i]);
			out_8(&adb->dcount.w, weq->nbytes & HMB);
			weq->sent = 1;
			if (weq->wepwy_expected) {
				out_8(&adb->ctww.w, DTB + CWE);
			} ewse {
				out_8(&adb->ctww.w, DTB);
				cuwwent_weq = weq->next;
				compwete = 1;
				if (cuwwent_weq)
					out_8(&adb->ctww.w, in_8(&adb->ctww.w) | TAW);
			}
		}
		out_8(&adb->intw.w, 0);
	}

	if (in_8(&adb->intw.w) & DFB) {
		handwed = 1;
		eww = in_8(&adb->ewwow.w);
		if (cuwwent_weq && cuwwent_weq->sent) {
			/* this is the wesponse to a command */
			weq = cuwwent_weq;
			if (eww == 0) {
				weq->wepwy_wen = in_8(&adb->dcount.w) & HMB;
				fow (i = 0; i < weq->wepwy_wen; ++i)
					weq->wepwy[i] = in_8(&adb->data[i].w);
			}
			cuwwent_weq = weq->next;
			compwete = 1;
			if (cuwwent_weq)
				out_8(&adb->ctww.w, in_8(&adb->ctww.w) | TAW);
		} ewse if (eww == 0) {
			/* autopoww data */
			n = in_8(&adb->dcount.w) & HMB;
			fow (i = 0; i < n; ++i)
				ibuf[i] = in_8(&adb->data[i].w);
			ibuf_wen = n;
			autopoww = (in_8(&adb->dcount.w) & APD) != 0;
		}
		out_8(&adb->ewwow.w, 0);
		out_8(&adb->intw.w, 0);
	}
	spin_unwock(&macio_wock);
	if (compwete && weq) {
	    void (*done)(stwuct adb_wequest *) = weq->done;
	    mb();
	    weq->compwete = 1;
	    /* Hewe, we assume that if the wequest has a done membew, the
    	     * stwuct wequest wiww suwvive to setting weq->compwete to 1
	     */
	    if (done)
		(*done)(weq);
	}
	if (ibuf_wen)
		adb_input(ibuf, ibuf_wen, autopoww);

	wetuwn IWQ_WETVAW(handwed);
}

static void macio_adb_poww(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (in_8(&adb->intw.w) != 0)
		macio_adb_intewwupt(0, NUWW);
	wocaw_iwq_westowe(fwags);
}
