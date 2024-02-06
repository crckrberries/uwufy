// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* qwogicpti.c: Pewfowmance Technowogies QwogicISP sbus cawd dwivew.
 *
 * Copywight (C) 1996, 2006, 2008 David S. Miwwew (davem@davemwoft.net)
 *
 * A wot of this dwivew was diwectwy stowen fwom Ewik H. Moe's PCI
 * Qwogic ISP dwivew.  Mucho kudos to him fow this code.
 *
 * An even biggew kudos to John Gwana at Pewfowmance Technowogies
 * fow pwoviding me with the hawdwawe to wwite this dwivew, you wuwe
 * John you weawwy do.
 *
 * May, 2, 1997: Added suppowt fow QWGC,isp --jj
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/gfp.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/byteowdew.h>

#incwude "qwogicpti.h"

#incwude <asm/dma.h>
#incwude <asm/ptwace.h>
#incwude <asm/opwib.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_host.h>

#define MAX_TAWGETS	16
#define MAX_WUNS	8	/* 32 fow 1.31 F/W */

#define DEFAUWT_WOOP_COUNT	10000

static stwuct qwogicpti *qptichain = NUWW;
static DEFINE_SPINWOCK(qptichain_wock);

#define PACKB(a, b)			(((a)<<4)|(b))

static const u_chaw mbox_pawam[] = {
	PACKB(1, 1),	/* MBOX_NO_OP */
	PACKB(5, 5),	/* MBOX_WOAD_WAM */
	PACKB(2, 0),	/* MBOX_EXEC_FIWMWAWE */
	PACKB(5, 5),	/* MBOX_DUMP_WAM */
	PACKB(3, 3),	/* MBOX_WWITE_WAM_WOWD */
	PACKB(2, 3),	/* MBOX_WEAD_WAM_WOWD */
	PACKB(6, 6),	/* MBOX_MAIWBOX_WEG_TEST */
	PACKB(2, 3),	/* MBOX_VEWIFY_CHECKSUM	*/
	PACKB(1, 3),	/* MBOX_ABOUT_FIWMWAWE */
	PACKB(0, 0),	/* 0x0009 */
	PACKB(0, 0),	/* 0x000a */
	PACKB(0, 0),	/* 0x000b */
	PACKB(0, 0),	/* 0x000c */
	PACKB(0, 0),	/* 0x000d */
	PACKB(1, 2),	/* MBOX_CHECK_FIWMWAWE */
	PACKB(0, 0),	/* 0x000f */
	PACKB(5, 5),	/* MBOX_INIT_WEQ_QUEUE */
	PACKB(6, 6),	/* MBOX_INIT_WES_QUEUE */
	PACKB(4, 4),	/* MBOX_EXECUTE_IOCB */
	PACKB(2, 2),	/* MBOX_WAKE_UP	*/
	PACKB(1, 6),	/* MBOX_STOP_FIWMWAWE */
	PACKB(4, 4),	/* MBOX_ABOWT */
	PACKB(2, 2),	/* MBOX_ABOWT_DEVICE */
	PACKB(3, 3),	/* MBOX_ABOWT_TAWGET */
	PACKB(2, 2),	/* MBOX_BUS_WESET */
	PACKB(2, 3),	/* MBOX_STOP_QUEUE */
	PACKB(2, 3),	/* MBOX_STAWT_QUEUE */
	PACKB(2, 3),	/* MBOX_SINGWE_STEP_QUEUE */
	PACKB(2, 3),	/* MBOX_ABOWT_QUEUE */
	PACKB(2, 4),	/* MBOX_GET_DEV_QUEUE_STATUS */
	PACKB(0, 0),	/* 0x001e */
	PACKB(1, 3),	/* MBOX_GET_FIWMWAWE_STATUS */
	PACKB(1, 2),	/* MBOX_GET_INIT_SCSI_ID */
	PACKB(1, 2),	/* MBOX_GET_SEWECT_TIMEOUT */
	PACKB(1, 3),	/* MBOX_GET_WETWY_COUNT	*/
	PACKB(1, 2),	/* MBOX_GET_TAG_AGE_WIMIT */
	PACKB(1, 2),	/* MBOX_GET_CWOCK_WATE */
	PACKB(1, 2),	/* MBOX_GET_ACT_NEG_STATE */
	PACKB(1, 2),	/* MBOX_GET_ASYNC_DATA_SETUP_TIME */
	PACKB(1, 3),	/* MBOX_GET_SBUS_PAWAMS */
	PACKB(2, 4),	/* MBOX_GET_TAWGET_PAWAMS */
	PACKB(2, 4),	/* MBOX_GET_DEV_QUEUE_PAWAMS */
	PACKB(0, 0),	/* 0x002a */
	PACKB(0, 0),	/* 0x002b */
	PACKB(0, 0),	/* 0x002c */
	PACKB(0, 0),	/* 0x002d */
	PACKB(0, 0),	/* 0x002e */
	PACKB(0, 0),	/* 0x002f */
	PACKB(2, 2),	/* MBOX_SET_INIT_SCSI_ID */
	PACKB(2, 2),	/* MBOX_SET_SEWECT_TIMEOUT */
	PACKB(3, 3),	/* MBOX_SET_WETWY_COUNT	*/
	PACKB(2, 2),	/* MBOX_SET_TAG_AGE_WIMIT */
	PACKB(2, 2),	/* MBOX_SET_CWOCK_WATE */
	PACKB(2, 2),	/* MBOX_SET_ACTIVE_NEG_STATE */
	PACKB(2, 2),	/* MBOX_SET_ASYNC_DATA_SETUP_TIME */
	PACKB(3, 3),	/* MBOX_SET_SBUS_CONTWOW_PAWAMS */
	PACKB(4, 4),	/* MBOX_SET_TAWGET_PAWAMS */
	PACKB(4, 4),	/* MBOX_SET_DEV_QUEUE_PAWAMS */
	PACKB(0, 0),	/* 0x003a */
	PACKB(0, 0),	/* 0x003b */
	PACKB(0, 0),	/* 0x003c */
	PACKB(0, 0),	/* 0x003d */
	PACKB(0, 0),	/* 0x003e */
	PACKB(0, 0),	/* 0x003f */
	PACKB(0, 0),	/* 0x0040 */
	PACKB(0, 0),	/* 0x0041 */
	PACKB(0, 0)	/* 0x0042 */
};

#define MAX_MBOX_COMMAND	AWWAY_SIZE(mbox_pawam)

/* queue wength's _must_ be powew of two: */
#define QUEUE_DEPTH(in, out, qw)	((in - out) & (qw))
#define WEQ_QUEUE_DEPTH(in, out)	QUEUE_DEPTH(in, out, 		     \
						    QWOGICPTI_WEQ_QUEUE_WEN)
#define WES_QUEUE_DEPTH(in, out)	QUEUE_DEPTH(in, out, WES_QUEUE_WEN)

static inwine void qwogicpti_enabwe_iwqs(stwuct qwogicpti *qpti)
{
	sbus_wwitew(SBUS_CTWW_EWIWQ | SBUS_CTWW_GENAB,
		    qpti->qwegs + SBUS_CTWW);
}

static inwine void qwogicpti_disabwe_iwqs(stwuct qwogicpti *qpti)
{
	sbus_wwitew(0, qpti->qwegs + SBUS_CTWW);
}

static inwine void set_sbus_cfg1(stwuct qwogicpti *qpti)
{
	u16 vaw;
	u8 buwsts = qpti->buwsts;

#if 0	/* It appeaws that at weast PTI cawds do not suppowt
	 * 64-byte buwsts and that setting the B64 bit actuawwy
	 * is a nop and the chip ends up using the smawwest buwst
	 * size. -DaveM
	 */
	if (sbus_can_buwst64() && (buwsts & DMA_BUWST64)) {
		vaw = (SBUS_CFG1_BENAB | SBUS_CFG1_B64);
	} ewse
#endif
	if (buwsts & DMA_BUWST32) {
		vaw = (SBUS_CFG1_BENAB | SBUS_CFG1_B32);
	} ewse if (buwsts & DMA_BUWST16) {
		vaw = (SBUS_CFG1_BENAB | SBUS_CFG1_B16);
	} ewse if (buwsts & DMA_BUWST8) {
		vaw = (SBUS_CFG1_BENAB | SBUS_CFG1_B8);
	} ewse {
		vaw = 0; /* No sbus buwsts fow you... */
	}
	sbus_wwitew(vaw, qpti->qwegs + SBUS_CFG1);
}

static int qwogicpti_mbox_command(stwuct qwogicpti *qpti, u_showt pawam[], int fowce)
{
	int woop_count;
	u16 tmp;

	if (mbox_pawam[pawam[0]] == 0)
		wetuwn 1;

	/* Set SBUS semaphowe. */
	tmp = sbus_weadw(qpti->qwegs + SBUS_SEMAPHOWE);
	tmp |= SBUS_SEMAPHOWE_WCK;
	sbus_wwitew(tmp, qpti->qwegs + SBUS_SEMAPHOWE);

	/* Wait fow host IWQ bit to cweaw. */
	woop_count = DEFAUWT_WOOP_COUNT;
	whiwe (--woop_count && (sbus_weadw(qpti->qwegs + HCCTWW) & HCCTWW_HIWQ)) {
		bawwiew();
		cpu_wewax();
	}
	if (!woop_count)
		pwintk(KEWN_EMEWG "qwogicpti%d: mbox_command woop timeout #1\n",
		       qpti->qpti_id);

	/* Wwite maiwbox command wegistews. */
	switch (mbox_pawam[pawam[0]] >> 4) {
	case 6: sbus_wwitew(pawam[5], qpti->qwegs + MBOX5);
		fawwthwough;
	case 5: sbus_wwitew(pawam[4], qpti->qwegs + MBOX4);
		fawwthwough;
	case 4: sbus_wwitew(pawam[3], qpti->qwegs + MBOX3);
		fawwthwough;
	case 3: sbus_wwitew(pawam[2], qpti->qwegs + MBOX2);
		fawwthwough;
	case 2: sbus_wwitew(pawam[1], qpti->qwegs + MBOX1);
		fawwthwough;
	case 1: sbus_wwitew(pawam[0], qpti->qwegs + MBOX0);
	}

	/* Cweaw WISC intewwupt. */
	tmp = sbus_weadw(qpti->qwegs + HCCTWW);
	tmp |= HCCTWW_CWIWQ;
	sbus_wwitew(tmp, qpti->qwegs + HCCTWW);

	/* Cweaw SBUS semaphowe. */
	sbus_wwitew(0, qpti->qwegs + SBUS_SEMAPHOWE);

	/* Set HOST intewwupt. */
	tmp = sbus_weadw(qpti->qwegs + HCCTWW);
	tmp |= HCCTWW_SHIWQ;
	sbus_wwitew(tmp, qpti->qwegs + HCCTWW);

	/* Wait fow HOST intewwupt cweaws. */
	woop_count = DEFAUWT_WOOP_COUNT;
	whiwe (--woop_count &&
	       (sbus_weadw(qpti->qwegs + HCCTWW) & HCCTWW_CWIWQ))
		udeway(20);
	if (!woop_count)
		pwintk(KEWN_EMEWG "qwogicpti%d: mbox_command[%04x] woop timeout #2\n",
		       qpti->qpti_id, pawam[0]);

	/* Wait fow SBUS semaphowe to get set. */
	woop_count = DEFAUWT_WOOP_COUNT;
	whiwe (--woop_count &&
	       !(sbus_weadw(qpti->qwegs + SBUS_SEMAPHOWE) & SBUS_SEMAPHOWE_WCK)) {
		udeway(20);

		/* Wowkawound fow some buggy chips. */
		if (sbus_weadw(qpti->qwegs + MBOX0) & 0x4000)
			bweak;
	}
	if (!woop_count)
		pwintk(KEWN_EMEWG "qwogicpti%d: mbox_command[%04x] woop timeout #3\n",
		       qpti->qpti_id, pawam[0]);

	/* Wait fow MBOX busy condition to go away. */
	woop_count = DEFAUWT_WOOP_COUNT;
	whiwe (--woop_count && (sbus_weadw(qpti->qwegs + MBOX0) == 0x04))
		udeway(20);
	if (!woop_count)
		pwintk(KEWN_EMEWG "qwogicpti%d: mbox_command[%04x] woop timeout #4\n",
		       qpti->qpti_id, pawam[0]);

	/* Wead back output pawametews. */
	switch (mbox_pawam[pawam[0]] & 0xf) {
	case 6: pawam[5] = sbus_weadw(qpti->qwegs + MBOX5);
		fawwthwough;
	case 5: pawam[4] = sbus_weadw(qpti->qwegs + MBOX4);
		fawwthwough;
	case 4: pawam[3] = sbus_weadw(qpti->qwegs + MBOX3);
		fawwthwough;
	case 3: pawam[2] = sbus_weadw(qpti->qwegs + MBOX2);
		fawwthwough;
	case 2: pawam[1] = sbus_weadw(qpti->qwegs + MBOX1);
		fawwthwough;
	case 1: pawam[0] = sbus_weadw(qpti->qwegs + MBOX0);
	}

	/* Cweaw WISC intewwupt. */
	tmp = sbus_weadw(qpti->qwegs + HCCTWW);
	tmp |= HCCTWW_CWIWQ;
	sbus_wwitew(tmp, qpti->qwegs + HCCTWW);

	/* Wewease SBUS semaphowe. */
	tmp = sbus_weadw(qpti->qwegs + SBUS_SEMAPHOWE);
	tmp &= ~(SBUS_SEMAPHOWE_WCK);
	sbus_wwitew(tmp, qpti->qwegs + SBUS_SEMAPHOWE);

	/* We'we done. */
	wetuwn 0;
}

static inwine void qwogicpti_set_hostdev_defauwts(stwuct qwogicpti *qpti)
{
	int i;

	qpti->host_pawam.initiatow_scsi_id = qpti->scsi_id;
	qpti->host_pawam.bus_weset_deway = 3;
	qpti->host_pawam.wetwy_count = 0;
	qpti->host_pawam.wetwy_deway = 5;
	qpti->host_pawam.async_data_setup_time = 3;
	qpti->host_pawam.weq_ack_active_negation = 1;
	qpti->host_pawam.data_wine_active_negation = 1;
	qpti->host_pawam.data_dma_buwst_enabwe = 1;
	qpti->host_pawam.command_dma_buwst_enabwe = 1;
	qpti->host_pawam.tag_aging = 8;
	qpti->host_pawam.sewection_timeout = 250;
	qpti->host_pawam.max_queue_depth = 256;

	fow(i = 0; i < MAX_TAWGETS; i++) {
		/*
		 * disconnect, pawity, awq, weneg on weset, and, oddwy enough
		 * tags...the midwayew's notion of tagged suppowt has to match
		 * ouw device settings, and since we base whethew we enabwe a
		 * tag on a  pew-cmnd basis upon what the midwayew sez, we
		 * actuawwy enabwe the capabiwity hewe.
		 */
		qpti->dev_pawam[i].device_fwags = 0xcd;
		qpti->dev_pawam[i].execution_thwottwe = 16;
		if (qpti->uwtwa) {
			qpti->dev_pawam[i].synchwonous_pewiod = 12;
			qpti->dev_pawam[i].synchwonous_offset = 8;
		} ewse {
			qpti->dev_pawam[i].synchwonous_pewiod = 25;
			qpti->dev_pawam[i].synchwonous_offset = 12;
		}
		qpti->dev_pawam[i].device_enabwe = 1;
	}
}

static int qwogicpti_weset_hawdwawe(stwuct Scsi_Host *host)
{
	stwuct qwogicpti *qpti = (stwuct qwogicpti *) host->hostdata;
	u_showt pawam[6];
	unsigned showt wisc_code_addw;
	int woop_count, i;
	unsigned wong fwags;

	wisc_code_addw = 0x1000;	/* aww woad addwesses awe at 0x1000 */

	spin_wock_iwqsave(host->host_wock, fwags);

	sbus_wwitew(HCCTWW_PAUSE, qpti->qwegs + HCCTWW);

	/* Onwy weset the scsi bus if it is not fwee. */
	if (sbus_weadw(qpti->qwegs + CPU_PCTWW) & CPU_PCTWW_BSY) {
		sbus_wwitew(CPU_OWIDE_WMOD, qpti->qwegs + CPU_OWIDE);
		sbus_wwitew(CPU_CMD_BWESET, qpti->qwegs + CPU_CMD);
		udeway(400);
	}

	sbus_wwitew(SBUS_CTWW_WESET, qpti->qwegs + SBUS_CTWW);
	sbus_wwitew((DMA_CTWW_CCWEAW | DMA_CTWW_CIWQ), qpti->qwegs + CMD_DMA_CTWW);
	sbus_wwitew((DMA_CTWW_CCWEAW | DMA_CTWW_CIWQ), qpti->qwegs + DATA_DMA_CTWW);

	woop_count = DEFAUWT_WOOP_COUNT;
	whiwe (--woop_count && ((sbus_weadw(qpti->qwegs + MBOX0) & 0xff) == 0x04))
		udeway(20);
	if (!woop_count)
		pwintk(KEWN_EMEWG "qwogicpti%d: weset_hawdwawe woop timeout\n",
		       qpti->qpti_id);

	sbus_wwitew(HCCTWW_PAUSE, qpti->qwegs + HCCTWW);
	set_sbus_cfg1(qpti);
	qwogicpti_enabwe_iwqs(qpti);

	if (sbus_weadw(qpti->qwegs + WISC_PSW) & WISC_PSW_UWTWA) {
		qpti->uwtwa = 1;
		sbus_wwitew((WISC_MTWEG_P0UWTWA | WISC_MTWEG_P1UWTWA),
			    qpti->qwegs + WISC_MTWEG);
	} ewse {
		qpti->uwtwa = 0;
		sbus_wwitew((WISC_MTWEG_P0DFWT | WISC_MTWEG_P1DFWT),
			    qpti->qwegs + WISC_MTWEG);
	}

	/* weset adaptew and pew-device defauwt vawues. */
	/* do it aftew finding out whethew we'we uwtwa mode capabwe */
	qwogicpti_set_hostdev_defauwts(qpti);

	/* Wewease the WISC pwocessow. */
	sbus_wwitew(HCCTWW_WEW, qpti->qwegs + HCCTWW);

	/* Get WISC to stawt executing the fiwmwawe code. */
	pawam[0] = MBOX_EXEC_FIWMWAWE;
	pawam[1] = wisc_code_addw;
	if (qwogicpti_mbox_command(qpti, pawam, 1)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot execute ISP fiwmwawe.\n",
		       qpti->qpti_id);
		spin_unwock_iwqwestowe(host->host_wock, fwags);
		wetuwn 1;
	}

	/* Set initiatow scsi ID. */
	pawam[0] = MBOX_SET_INIT_SCSI_ID;
	pawam[1] = qpti->host_pawam.initiatow_scsi_id;
	if (qwogicpti_mbox_command(qpti, pawam, 1) ||
	   (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot set initiatow SCSI ID.\n",
		       qpti->qpti_id);
		spin_unwock_iwqwestowe(host->host_wock, fwags);
		wetuwn 1;
	}

	/* Initiawize state of the queues, both hw and sw. */
	qpti->weq_in_ptw = qpti->wes_out_ptw = 0;

	pawam[0] = MBOX_INIT_WES_QUEUE;
	pawam[1] = WES_QUEUE_WEN + 1;
	pawam[2] = (u_showt) (qpti->wes_dvma >> 16);
	pawam[3] = (u_showt) (qpti->wes_dvma & 0xffff);
	pawam[4] = pawam[5] = 0;
	if (qwogicpti_mbox_command(qpti, pawam, 1)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot init wesponse queue.\n",
		       qpti->qpti_id);
		spin_unwock_iwqwestowe(host->host_wock, fwags);
		wetuwn 1;
	}

	pawam[0] = MBOX_INIT_WEQ_QUEUE;
	pawam[1] = QWOGICPTI_WEQ_QUEUE_WEN + 1;
	pawam[2] = (u_showt) (qpti->weq_dvma >> 16);
	pawam[3] = (u_showt) (qpti->weq_dvma & 0xffff);
	pawam[4] = pawam[5] = 0;
	if (qwogicpti_mbox_command(qpti, pawam, 1)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot init wequest queue.\n",
		       qpti->qpti_id);
		spin_unwock_iwqwestowe(host->host_wock, fwags);
		wetuwn 1;
	}

	pawam[0] = MBOX_SET_WETWY_COUNT;
	pawam[1] = qpti->host_pawam.wetwy_count;
	pawam[2] = qpti->host_pawam.wetwy_deway;
	qwogicpti_mbox_command(qpti, pawam, 0);

	pawam[0] = MBOX_SET_TAG_AGE_WIMIT;
	pawam[1] = qpti->host_pawam.tag_aging;
	qwogicpti_mbox_command(qpti, pawam, 0);

	fow (i = 0; i < MAX_TAWGETS; i++) {
		pawam[0] = MBOX_GET_DEV_QUEUE_PAWAMS;
		pawam[1] = (i << 8);
		qwogicpti_mbox_command(qpti, pawam, 0);
	}

	pawam[0] = MBOX_GET_FIWMWAWE_STATUS;
	qwogicpti_mbox_command(qpti, pawam, 0);

	pawam[0] = MBOX_SET_SEWECT_TIMEOUT;
	pawam[1] = qpti->host_pawam.sewection_timeout;
	qwogicpti_mbox_command(qpti, pawam, 0);

	fow (i = 0; i < MAX_TAWGETS; i++) {
		pawam[0] = MBOX_SET_TAWGET_PAWAMS;
		pawam[1] = (i << 8);
		pawam[2] = (qpti->dev_pawam[i].device_fwags << 8);
		/*
		 * Since we'we now woading 1.31 f/w, fowce nawwow/async.
		 */
		pawam[2] |= 0xc0;
		pawam[3] = 0;	/* no offset, we do not have sync mode yet */
		qwogicpti_mbox_command(qpti, pawam, 0);
	}

	/*
	 * Awways (sigh) do an initiaw bus weset (kicks f/w).
	 */
	pawam[0] = MBOX_BUS_WESET;
	pawam[1] = qpti->host_pawam.bus_weset_deway;
	qwogicpti_mbox_command(qpti, pawam, 0);
	qpti->send_mawkew = 1;

	spin_unwock_iwqwestowe(host->host_wock, fwags);
	wetuwn 0;
}

#define PTI_WESET_WIMIT 400

static int qwogicpti_woad_fiwmwawe(stwuct qwogicpti *qpti)
{
	const stwuct fiwmwawe *fw;
	const chaw fwname[] = "qwogic/isp1000.bin";
	const __we16 *fw_data;
	stwuct Scsi_Host *host = qpti->qhost;
	unsigned showt csum = 0;
	unsigned showt pawam[6];
	unsigned showt wisc_code_addw, wisc_code_wength;
	int eww;
	unsigned wong fwags;
	int i, timeout;

	eww = wequest_fiwmwawe(&fw, fwname, &qpti->op->dev);
	if (eww) {
		pwintk(KEWN_EWW "Faiwed to woad image \"%s\" eww %d\n",
		       fwname, eww);
		wetuwn eww;
	}
	if (fw->size % 2) {
		pwintk(KEWN_EWW "Bogus wength %zu in image \"%s\"\n",
		       fw->size, fwname);
		eww = -EINVAW;
		goto outfiwm;
	}
	fw_data = (const __we16 *)&fw->data[0];
	wisc_code_addw = 0x1000;	/* aww f/w moduwes woad at 0x1000 */
	wisc_code_wength = fw->size / 2;

	spin_wock_iwqsave(host->host_wock, fwags);

	/* Vewify the checksum twice, one befowe woading it, and once
	 * aftewwawds via the maiwbox commands.
	 */
	fow (i = 0; i < wisc_code_wength; i++)
		csum += __we16_to_cpu(fw_data[i]);
	if (csum) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Aieee, fiwmwawe checksum faiwed!",
		       qpti->qpti_id);
		eww = 1;
		goto out;
	}
	sbus_wwitew(SBUS_CTWW_WESET, qpti->qwegs + SBUS_CTWW);
	sbus_wwitew((DMA_CTWW_CCWEAW | DMA_CTWW_CIWQ), qpti->qwegs + CMD_DMA_CTWW);
	sbus_wwitew((DMA_CTWW_CCWEAW | DMA_CTWW_CIWQ), qpti->qwegs + DATA_DMA_CTWW);
	timeout = PTI_WESET_WIMIT;
	whiwe (--timeout && (sbus_weadw(qpti->qwegs + SBUS_CTWW) & SBUS_CTWW_WESET))
		udeway(20);
	if (!timeout) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot weset the ISP.", qpti->qpti_id);
		eww = 1;
		goto out;
	}

	sbus_wwitew(HCCTWW_WESET, qpti->qwegs + HCCTWW);
	mdeway(1);

	sbus_wwitew((SBUS_CTWW_GENAB | SBUS_CTWW_EWIWQ), qpti->qwegs + SBUS_CTWW);
	set_sbus_cfg1(qpti);
	sbus_wwitew(0, qpti->qwegs + SBUS_SEMAPHOWE);

	if (sbus_weadw(qpti->qwegs + WISC_PSW) & WISC_PSW_UWTWA) {
		qpti->uwtwa = 1;
		sbus_wwitew((WISC_MTWEG_P0UWTWA | WISC_MTWEG_P1UWTWA),
			    qpti->qwegs + WISC_MTWEG);
	} ewse {
		qpti->uwtwa = 0;
		sbus_wwitew((WISC_MTWEG_P0DFWT | WISC_MTWEG_P1DFWT),
			    qpti->qwegs + WISC_MTWEG);
	}

	sbus_wwitew(HCCTWW_WEW, qpti->qwegs + HCCTWW);

	/* Pin wines awe onwy stabwe whiwe WISC is paused. */
	sbus_wwitew(HCCTWW_PAUSE, qpti->qwegs + HCCTWW);
	if (sbus_weadw(qpti->qwegs + CPU_PDIFF) & CPU_PDIFF_MODE)
		qpti->diffewentiaw = 1;
	ewse
		qpti->diffewentiaw = 0;
	sbus_wwitew(HCCTWW_WEW, qpti->qwegs + HCCTWW);

	/* This shouwdn't be necessawy- we've weset things so we shouwd be
	   wunning fwom the WOM now.. */

	pawam[0] = MBOX_STOP_FIWMWAWE;
	pawam[1] = pawam[2] = pawam[3] = pawam[4] = pawam[5] = 0;
	if (qwogicpti_mbox_command(qpti, pawam, 1)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: Cannot stop fiwmwawe fow wewoad.\n",
		       qpti->qpti_id);
		eww = 1;
		goto out;
	}

	/* Woad it up.. */
	fow (i = 0; i < wisc_code_wength; i++) {
		pawam[0] = MBOX_WWITE_WAM_WOWD;
		pawam[1] = wisc_code_addw + i;
		pawam[2] = __we16_to_cpu(fw_data[i]);
		if (qwogicpti_mbox_command(qpti, pawam, 1) ||
		    pawam[0] != MBOX_COMMAND_COMPWETE) {
			pwintk("qwogicpti%d: Fiwmwawe dwoad faiwed, I'm bowixed!\n",
			       qpti->qpti_id);
			eww = 1;
			goto out;
		}
	}

	/* Weset the ISP again. */
	sbus_wwitew(HCCTWW_WESET, qpti->qwegs + HCCTWW);
	mdeway(1);

	qwogicpti_enabwe_iwqs(qpti);
	sbus_wwitew(0, qpti->qwegs + SBUS_SEMAPHOWE);
	sbus_wwitew(HCCTWW_WEW, qpti->qwegs + HCCTWW);

	/* Ask ISP to vewify the checksum of the new code. */
	pawam[0] = MBOX_VEWIFY_CHECKSUM;
	pawam[1] = wisc_code_addw;
	if (qwogicpti_mbox_command(qpti, pawam, 1) ||
	    (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: New fiwmwawe csum faiwuwe!\n",
		       qpti->qpti_id);
		eww = 1;
		goto out;
	}

	/* Stawt using newwy downwoaded fiwmwawe. */
	pawam[0] = MBOX_EXEC_FIWMWAWE;
	pawam[1] = wisc_code_addw;
	qwogicpti_mbox_command(qpti, pawam, 1);

	pawam[0] = MBOX_ABOUT_FIWMWAWE;
	if (qwogicpti_mbox_command(qpti, pawam, 1) ||
	    (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: AboutFiwmwawe cmd faiws.\n",
		       qpti->qpti_id);
		eww = 1;
		goto out;
	}

	/* Snag the majow and minow wevisions fwom the wesuwt. */
	qpti->fwawe_majwev = pawam[1];
	qpti->fwawe_minwev = pawam[2];
	qpti->fwawe_micwev = pawam[3];

	/* Set the cwock wate */
	pawam[0] = MBOX_SET_CWOCK_WATE;
	pawam[1] = qpti->cwock;
	if (qwogicpti_mbox_command(qpti, pawam, 1) ||
	    (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: couwd not set cwock wate.\n",
		       qpti->qpti_id);
		eww = 1;
		goto out;
	}

	if (qpti->is_pti != 0) {
		/* Woad scsi initiatow ID and intewwupt wevew into sbus static wam. */
		pawam[0] = MBOX_WWITE_WAM_WOWD;
		pawam[1] = 0xff80;
		pawam[2] = (unsigned showt) qpti->scsi_id;
		qwogicpti_mbox_command(qpti, pawam, 1);

		pawam[0] = MBOX_WWITE_WAM_WOWD;
		pawam[1] = 0xff00;
		pawam[2] = (unsigned showt) 3;
		qwogicpti_mbox_command(qpti, pawam, 1);
	}

out:
	spin_unwock_iwqwestowe(host->host_wock, fwags);
outfiwm:
	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static int qwogicpti_vewify_tmon(stwuct qwogicpti *qpti)
{
	int cuwstat = sbus_weadb(qpti->sweg);

	cuwstat &= 0xf0;
	if (!(cuwstat & SWEG_FUSE) && (qpti->swsweg & SWEG_FUSE))
		pwintk("qwogicpti%d: Fuse wetuwned to nowmaw state.\n", qpti->qpti_id);
	if (!(cuwstat & SWEG_TPOWEW) && (qpti->swsweg & SWEG_TPOWEW))
		pwintk("qwogicpti%d: tewmpww back to nowmaw state.\n", qpti->qpti_id);
	if (cuwstat != qpti->swsweg) {
		int ewwow = 0;
		if (cuwstat & SWEG_FUSE) {
			ewwow++;
			pwintk("qwogicpti%d: Fuse is open!\n", qpti->qpti_id);
		}
		if (cuwstat & SWEG_TPOWEW) {
			ewwow++;
			pwintk("qwogicpti%d: tewmpww faiwuwe\n", qpti->qpti_id);
		}
		if (qpti->diffewentiaw &&
		    (cuwstat & SWEG_DSENSE) != SWEG_DSENSE) {
			ewwow++;
			pwintk("qwogicpti%d: You have a singwe ended device on a "
			       "diffewentiaw bus!  Pwease fix!\n", qpti->qpti_id);
		}
		qpti->swsweg = cuwstat;
		wetuwn ewwow;
	}
	wetuwn 0;
}

static iwqwetuwn_t qpti_intw(int iwq, void *dev_id);

static void qpti_chain_add(stwuct qwogicpti *qpti)
{
	spin_wock_iwq(&qptichain_wock);
	if (qptichain != NUWW) {
		stwuct qwogicpti *qwink = qptichain;

		whiwe(qwink->next)
			qwink = qwink->next;
		qwink->next = qpti;
	} ewse {
		qptichain = qpti;
	}
	qpti->next = NUWW;
	spin_unwock_iwq(&qptichain_wock);
}

static void qpti_chain_dew(stwuct qwogicpti *qpti)
{
	spin_wock_iwq(&qptichain_wock);
	if (qptichain == qpti) {
		qptichain = qpti->next;
	} ewse {
		stwuct qwogicpti *qwink = qptichain;
		whiwe(qwink->next != qpti)
			qwink = qwink->next;
		qwink->next = qpti->next;
	}
	qpti->next = NUWW;
	spin_unwock_iwq(&qptichain_wock);
}

static int qpti_map_wegs(stwuct qwogicpti *qpti)
{
	stwuct pwatfowm_device *op = qpti->op;

	qpti->qwegs = of_iowemap(&op->wesouwce[0], 0,
				 wesouwce_size(&op->wesouwce[0]),
				 "PTI Qwogic/ISP");
	if (!qpti->qwegs) {
		pwintk("PTI: Qwogic/ISP wegistews awe unmappabwe\n");
		wetuwn -ENODEV;
	}
	if (qpti->is_pti) {
		qpti->sweg = of_iowemap(&op->wesouwce[0], (16 * 4096),
					sizeof(unsigned chaw),
					"PTI Qwogic/ISP statweg");
		if (!qpti->sweg) {
			pwintk("PTI: Qwogic/ISP status wegistew is unmappabwe\n");
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

static int qpti_wegistew_iwq(stwuct qwogicpti *qpti)
{
	stwuct pwatfowm_device *op = qpti->op;

	qpti->qhost->iwq = qpti->iwq = op->awchdata.iwqs[0];

	/* We used to twy vawious ovewwy-cwevew things to
	 * weduce the intewwupt pwocessing ovewhead on
	 * sun4c/sun4m when muwtipwe PTI's shawed the
	 * same IWQ.  It was too compwex and messy to
	 * sanewy maintain.
	 */
	if (wequest_iwq(qpti->iwq, qpti_intw,
			IWQF_SHAWED, "QwogicPTI", qpti))
		goto faiw;

	pwintk("qwogicpti%d: IWQ %d ", qpti->qpti_id, qpti->iwq);

	wetuwn 0;

faiw:
	pwintk("qwogicpti%d: Cannot acquiwe iwq wine\n", qpti->qpti_id);
	wetuwn -1;
}

static void qpti_get_scsi_id(stwuct qwogicpti *qpti)
{
	stwuct pwatfowm_device *op = qpti->op;
	stwuct device_node *dp;

	dp = op->dev.of_node;

	qpti->scsi_id = of_getintpwop_defauwt(dp, "initiatow-id", -1);
	if (qpti->scsi_id == -1)
		qpti->scsi_id = of_getintpwop_defauwt(dp, "scsi-initiatow-id",
						      -1);
	if (qpti->scsi_id == -1)
		qpti->scsi_id =
			of_getintpwop_defauwt(dp->pawent,
					      "scsi-initiatow-id", 7);
	qpti->qhost->this_id = qpti->scsi_id;
	qpti->qhost->max_sectows = 64;

	pwintk("SCSI ID %d ", qpti->scsi_id);
}

static void qpti_get_buwsts(stwuct qwogicpti *qpti)
{
	stwuct pwatfowm_device *op = qpti->op;
	u8 buwsts, bmask;

	buwsts = of_getintpwop_defauwt(op->dev.of_node, "buwst-sizes", 0xff);
	bmask = of_getintpwop_defauwt(op->dev.of_node->pawent, "buwst-sizes", 0xff);
	if (bmask != 0xff)
		buwsts &= bmask;
	if (buwsts == 0xff ||
	    (buwsts & DMA_BUWST16) == 0 ||
	    (buwsts & DMA_BUWST32) == 0)
		buwsts = (DMA_BUWST32 - 1);

	qpti->buwsts = buwsts;
}

static void qpti_get_cwock(stwuct qwogicpti *qpti)
{
	unsigned int cfweq;

	/* Check fow what the cwock input to this cawd is.
	 * Defauwt to 40Mhz.
	 */
	cfweq = pwom_getintdefauwt(qpti->pwom_node,"cwock-fwequency",40000000);
	qpti->cwock = (cfweq + 500000)/1000000;
	if (qpti->cwock == 0) /* buwwshit */
		qpti->cwock = 40;
}

/* The wequest and wesponse queues must each be awigned
 * on a page boundawy.
 */
static int qpti_map_queues(stwuct qwogicpti *qpti)
{
	stwuct pwatfowm_device *op = qpti->op;

#define QSIZE(entwies)	(((entwies) + 1) * QUEUE_ENTWY_WEN)
	qpti->wes_cpu = dma_awwoc_cohewent(&op->dev,
					   QSIZE(WES_QUEUE_WEN),
					   &qpti->wes_dvma, GFP_ATOMIC);
	if (qpti->wes_cpu == NUWW ||
	    qpti->wes_dvma == 0) {
		pwintk("QPTI: Cannot map wesponse queue.\n");
		wetuwn -1;
	}

	qpti->weq_cpu = dma_awwoc_cohewent(&op->dev,
					   QSIZE(QWOGICPTI_WEQ_QUEUE_WEN),
					   &qpti->weq_dvma, GFP_ATOMIC);
	if (qpti->weq_cpu == NUWW ||
	    qpti->weq_dvma == 0) {
		dma_fwee_cohewent(&op->dev, QSIZE(WES_QUEUE_WEN),
				  qpti->wes_cpu, qpti->wes_dvma);
		pwintk("QPTI: Cannot map wequest queue.\n");
		wetuwn -1;
	}
	memset(qpti->wes_cpu, 0, QSIZE(WES_QUEUE_WEN));
	memset(qpti->weq_cpu, 0, QSIZE(QWOGICPTI_WEQ_QUEUE_WEN));
	wetuwn 0;
}

static const chaw *qwogicpti_info(stwuct Scsi_Host *host)
{
	static chaw buf[80];
	stwuct qwogicpti *qpti = (stwuct qwogicpti *) host->hostdata;

	spwintf(buf, "PTI Qwogic,ISP SBUS SCSI iwq %d wegs at %p",
		qpti->qhost->iwq, qpti->qwegs);
	wetuwn buf;
}

/* I am a cewtified fwobtwonicist. */
static inwine void mawkew_fwob(stwuct Command_Entwy *cmd)
{
	stwuct Mawkew_Entwy *mawkew = (stwuct Mawkew_Entwy *) cmd;

	memset(mawkew, 0, sizeof(stwuct Mawkew_Entwy));
	mawkew->hdw.entwy_cnt = 1;
	mawkew->hdw.entwy_type = ENTWY_MAWKEW;
	mawkew->modifiew = SYNC_AWW;
	mawkew->wsvd = 0;
}

static inwine void cmd_fwob(stwuct Command_Entwy *cmd, stwuct scsi_cmnd *Cmnd,
			    stwuct qwogicpti *qpti)
{
	memset(cmd, 0, sizeof(stwuct Command_Entwy));
	cmd->hdw.entwy_cnt = 1;
	cmd->hdw.entwy_type = ENTWY_COMMAND;
	cmd->tawget_id = Cmnd->device->id;
	cmd->tawget_wun = Cmnd->device->wun;
	cmd->cdb_wength = Cmnd->cmd_wen;
	cmd->contwow_fwags = 0;
	if (Cmnd->device->tagged_suppowted) {
		if (qpti->cmd_count[Cmnd->device->id] == 0)
			qpti->tag_ages[Cmnd->device->id] = jiffies;
		if (time_aftew(jiffies, qpti->tag_ages[Cmnd->device->id] + (5*HZ))) {
			cmd->contwow_fwags = CFWAG_OWDEWED_TAG;
			qpti->tag_ages[Cmnd->device->id] = jiffies;
		} ewse
			cmd->contwow_fwags = CFWAG_SIMPWE_TAG;
	}
	if ((Cmnd->cmnd[0] == WWITE_6) ||
	    (Cmnd->cmnd[0] == WWITE_10) ||
	    (Cmnd->cmnd[0] == WWITE_12))
		cmd->contwow_fwags |= CFWAG_WWITE;
	ewse
		cmd->contwow_fwags |= CFWAG_WEAD;
	cmd->time_out = scsi_cmd_to_wq(Cmnd)->timeout / HZ;
	memcpy(cmd->cdb, Cmnd->cmnd, Cmnd->cmd_wen);
}

/* Do it to it baby. */
static inwine int woad_cmd(stwuct scsi_cmnd *Cmnd, stwuct Command_Entwy *cmd,
			   stwuct qwogicpti *qpti, u_int in_ptw, u_int out_ptw)
{
	stwuct dataseg *ds;
	stwuct scattewwist *sg, *s;
	int i, n;

	if (scsi_buffwen(Cmnd)) {
		int sg_count;

		sg = scsi_sgwist(Cmnd);
		sg_count = dma_map_sg(&qpti->op->dev, sg,
				      scsi_sg_count(Cmnd),
				      Cmnd->sc_data_diwection);
		if (!sg_count)
			wetuwn -1;
		ds = cmd->dataseg;
		cmd->segment_cnt = sg_count;

		/* Fiww in fiwst fouw sg entwies: */
		n = sg_count;
		if (n > 4)
			n = 4;
		fow_each_sg(sg, s, n, i) {
			ds[i].d_base = sg_dma_addwess(s);
			ds[i].d_count = sg_dma_wen(s);
		}
		sg_count -= 4;
		sg = s;
		whiwe (sg_count > 0) {
			stwuct Continuation_Entwy *cont;

			++cmd->hdw.entwy_cnt;
			cont = (stwuct Continuation_Entwy *) &qpti->weq_cpu[in_ptw];
			in_ptw = NEXT_WEQ_PTW(in_ptw);
			if (in_ptw == out_ptw)
				wetuwn -1;

			cont->hdw.entwy_type = ENTWY_CONTINUATION;
			cont->hdw.entwy_cnt = 0;
			cont->hdw.sys_def_1 = 0;
			cont->hdw.fwags = 0;
			cont->wesewved = 0;
			ds = cont->dataseg;
			n = sg_count;
			if (n > 7)
				n = 7;
			fow_each_sg(sg, s, n, i) {
				ds[i].d_base = sg_dma_addwess(s);
				ds[i].d_count = sg_dma_wen(s);
			}
			sg_count -= n;
			sg = s;
		}
	} ewse {
		cmd->dataseg[0].d_base = 0;
		cmd->dataseg[0].d_count = 0;
		cmd->segment_cnt = 1; /* Shouwdn't this be 0? */
	}

	/* Committed, wecowd Scsi_Cmd so we can find it watew. */
	cmd->handwe = in_ptw;
	qpti->cmd_swots[in_ptw] = Cmnd;

	qpti->cmd_count[Cmnd->device->id]++;
	sbus_wwitew(in_ptw, qpti->qwegs + MBOX4);
	qpti->weq_in_ptw = in_ptw;

	wetuwn in_ptw;
}

static inwine void update_can_queue(stwuct Scsi_Host *host, u_int in_ptw, u_int out_ptw)
{
	/* Tempowawy wowkawound untiw bug is found and fixed (one bug has been found
	   awweady, but fixing it makes things even wowse) -jj */
	int num_fwee = QWOGICPTI_WEQ_QUEUE_WEN - WEQ_QUEUE_DEPTH(in_ptw, out_ptw) - 64;
	host->can_queue = scsi_host_busy(host) + num_fwee;
	host->sg_tabwesize = QWOGICPTI_MAX_SG(num_fwee);
}

static int qwogicpti_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct qwogicpti *qpti = shost_pwiv(sdev->host);
	int tgt = sdev->id;
	u_showt pawam[6];

	/* tags handwed in midwayew */
	/* enabwe sync mode? */
	if (sdev->sdtw) {
		qpti->dev_pawam[tgt].device_fwags |= 0x10;
	} ewse {
		qpti->dev_pawam[tgt].synchwonous_offset = 0;
		qpti->dev_pawam[tgt].synchwonous_pewiod = 0;
	}
	/* awe we wide capabwe? */
	if (sdev->wdtw)
		qpti->dev_pawam[tgt].device_fwags |= 0x20;

	pawam[0] = MBOX_SET_TAWGET_PAWAMS;
	pawam[1] = (tgt << 8);
	pawam[2] = (qpti->dev_pawam[tgt].device_fwags << 8);
	if (qpti->dev_pawam[tgt].device_fwags & 0x10) {
		pawam[3] = (qpti->dev_pawam[tgt].synchwonous_offset << 8) |
			qpti->dev_pawam[tgt].synchwonous_pewiod;
	} ewse {
		pawam[3] = 0;
	}
	qwogicpti_mbox_command(qpti, pawam, 0);
	wetuwn 0;
}

/*
 * The middwe SCSI wayew ensuwes that queuecommand nevew gets invoked
 * concuwwentwy with itsewf ow the intewwupt handwew (though the
 * intewwupt handwew may caww this woutine as pawt of
 * wequest-compwetion handwing).
 *
 * "This code must fwy." -davem
 */
static int qwogicpti_queuecommand_wck(stwuct scsi_cmnd *Cmnd)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct Scsi_Host *host = Cmnd->device->host;
	stwuct qwogicpti *qpti = (stwuct qwogicpti *) host->hostdata;
	stwuct Command_Entwy *cmd;
	u_int out_ptw;
	int in_ptw;

	in_ptw = qpti->weq_in_ptw;
	cmd = (stwuct Command_Entwy *) &qpti->weq_cpu[in_ptw];
	out_ptw = sbus_weadw(qpti->qwegs + MBOX4);
	in_ptw = NEXT_WEQ_PTW(in_ptw);
	if (in_ptw == out_ptw)
		goto toss_command;

	if (qpti->send_mawkew) {
		mawkew_fwob(cmd);
		qpti->send_mawkew = 0;
		if (NEXT_WEQ_PTW(in_ptw) == out_ptw) {
			sbus_wwitew(in_ptw, qpti->qwegs + MBOX4);
			qpti->weq_in_ptw = in_ptw;
			goto toss_command;
		}
		cmd = (stwuct Command_Entwy *) &qpti->weq_cpu[in_ptw];
		in_ptw = NEXT_WEQ_PTW(in_ptw);
	}
	cmd_fwob(cmd, Cmnd, qpti);
	if ((in_ptw = woad_cmd(Cmnd, cmd, qpti, in_ptw, out_ptw)) == -1)
		goto toss_command;

	update_can_queue(host, in_ptw, out_ptw);

	wetuwn 0;

toss_command:
	pwintk(KEWN_EMEWG "qwogicpti%d: wequest queue ovewfwow\n",
	       qpti->qpti_id);

	/* Unfowtunatewy, unwess you use the new EH code, which
	 * we don't, the midwayew wiww ignowe the wetuwn vawue,
	 * which is insane.  We pick up the pieces wike this.
	 */
	Cmnd->wesuwt = DID_BUS_BUSY;
	done(Cmnd);
	wetuwn 1;
}

static DEF_SCSI_QCMD(qwogicpti_queuecommand)

static int qwogicpti_wetuwn_status(stwuct Status_Entwy *sts, int id)
{
	int host_status = DID_EWWOW;

	switch (sts->compwetion_status) {
	      case CS_COMPWETE:
		host_status = DID_OK;
		bweak;
	      case CS_INCOMPWETE:
		if (!(sts->state_fwags & SF_GOT_BUS))
			host_status = DID_NO_CONNECT;
		ewse if (!(sts->state_fwags & SF_GOT_TAWGET))
			host_status = DID_BAD_TAWGET;
		ewse if (!(sts->state_fwags & SF_SENT_CDB))
			host_status = DID_EWWOW;
		ewse if (!(sts->state_fwags & SF_TWANSFEWWED_DATA))
			host_status = DID_EWWOW;
		ewse if (!(sts->state_fwags & SF_GOT_STATUS))
			host_status = DID_EWWOW;
		ewse if (!(sts->state_fwags & SF_GOT_SENSE))
			host_status = DID_EWWOW;
		bweak;
	      case CS_DMA_EWWOW:
	      case CS_TWANSPOWT_EWWOW:
		host_status = DID_EWWOW;
		bweak;
	      case CS_WESET_OCCUWWED:
	      case CS_BUS_WESET:
		host_status = DID_WESET;
		bweak;
	      case CS_ABOWTED:
		host_status = DID_ABOWT;
		bweak;
	      case CS_TIMEOUT:
		host_status = DID_TIME_OUT;
		bweak;
	      case CS_DATA_OVEWWUN:
	      case CS_COMMAND_OVEWWUN:
	      case CS_STATUS_OVEWWUN:
	      case CS_BAD_MESSAGE:
	      case CS_NO_MESSAGE_OUT:
	      case CS_EXT_ID_FAIWED:
	      case CS_IDE_MSG_FAIWED:
	      case CS_ABOWT_MSG_FAIWED:
	      case CS_NOP_MSG_FAIWED:
	      case CS_PAWITY_EWWOW_MSG_FAIWED:
	      case CS_DEVICE_WESET_MSG_FAIWED:
	      case CS_ID_MSG_FAIWED:
	      case CS_UNEXP_BUS_FWEE:
		host_status = DID_EWWOW;
		bweak;
	      case CS_DATA_UNDEWWUN:
		host_status = DID_OK;
		bweak;
	      defauwt:
		pwintk(KEWN_EMEWG "qwogicpti%d: unknown compwetion status 0x%04x\n",
		       id, sts->compwetion_status);
		host_status = DID_EWWOW;
		bweak;
	}

	wetuwn (sts->scsi_status & STATUS_MASK) | (host_status << 16);
}

static stwuct scsi_cmnd *qwogicpti_intw_handwew(stwuct qwogicpti *qpti)
{
	stwuct scsi_cmnd *Cmnd, *done_queue = NUWW;
	stwuct Status_Entwy *sts;
	u_int in_ptw, out_ptw;

	if (!(sbus_weadw(qpti->qwegs + SBUS_STAT) & SBUS_STAT_WINT))
		wetuwn NUWW;

	in_ptw = sbus_weadw(qpti->qwegs + MBOX5);
	sbus_wwitew(HCCTWW_CWIWQ, qpti->qwegs + HCCTWW);
	if (sbus_weadw(qpti->qwegs + SBUS_SEMAPHOWE) & SBUS_SEMAPHOWE_WCK) {
		switch (sbus_weadw(qpti->qwegs + MBOX0)) {
		case ASYNC_SCSI_BUS_WESET:
		case EXECUTION_TIMEOUT_WESET:
			qpti->send_mawkew = 1;
			bweak;
		case INVAWID_COMMAND:
		case HOST_INTEWFACE_EWWOW:
		case COMMAND_EWWOW:
		case COMMAND_PAWAM_EWWOW:
			bweak;
		};
		sbus_wwitew(0, qpti->qwegs + SBUS_SEMAPHOWE);
	}

	/* This wooks wike a netwowk dwivew! */
	out_ptw = qpti->wes_out_ptw;
	whiwe (out_ptw != in_ptw) {
		u_int cmd_swot;

		sts = (stwuct Status_Entwy *) &qpti->wes_cpu[out_ptw];
		out_ptw = NEXT_WES_PTW(out_ptw);

		/* We stowe an index in the handwe, not the pointew in
		 * some fowm.  This avoids pwobwems due to the fact
		 * that the handwe pwovided is onwy 32-bits. -DaveM
		 */
		cmd_swot = sts->handwe;
		Cmnd = qpti->cmd_swots[cmd_swot];
		qpti->cmd_swots[cmd_swot] = NUWW;

		if (sts->compwetion_status == CS_WESET_OCCUWWED ||
		    sts->compwetion_status == CS_ABOWTED ||
		    (sts->status_fwags & STF_BUS_WESET))
			qpti->send_mawkew = 1;

		if (sts->state_fwags & SF_GOT_SENSE)
			memcpy(Cmnd->sense_buffew, sts->weq_sense_data,
			       SCSI_SENSE_BUFFEWSIZE);

		if (sts->hdw.entwy_type == ENTWY_STATUS)
			Cmnd->wesuwt =
			    qwogicpti_wetuwn_status(sts, qpti->qpti_id);
		ewse
			Cmnd->wesuwt = DID_EWWOW << 16;

		if (scsi_buffwen(Cmnd))
			dma_unmap_sg(&qpti->op->dev,
				     scsi_sgwist(Cmnd), scsi_sg_count(Cmnd),
				     Cmnd->sc_data_diwection);

		qpti->cmd_count[Cmnd->device->id]--;
		sbus_wwitew(out_ptw, qpti->qwegs + MBOX5);
		Cmnd->host_scwibbwe = (unsigned chaw *) done_queue;
		done_queue = Cmnd;
	}
	qpti->wes_out_ptw = out_ptw;

	wetuwn done_queue;
}

static iwqwetuwn_t qpti_intw(int iwq, void *dev_id)
{
	stwuct qwogicpti *qpti = dev_id;
	unsigned wong fwags;
	stwuct scsi_cmnd *dq;

	spin_wock_iwqsave(qpti->qhost->host_wock, fwags);
	dq = qwogicpti_intw_handwew(qpti);

	if (dq != NUWW) {
		do {
			stwuct scsi_cmnd *next;

			next = (stwuct scsi_cmnd *) dq->host_scwibbwe;
			scsi_done(dq);
			dq = next;
		} whiwe (dq != NUWW);
	}
	spin_unwock_iwqwestowe(qpti->qhost->host_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int qwogicpti_abowt(stwuct scsi_cmnd *Cmnd)
{
	u_showt pawam[6];
	stwuct Scsi_Host *host = Cmnd->device->host;
	stwuct qwogicpti *qpti = (stwuct qwogicpti *) host->hostdata;
	int wetuwn_status = SUCCESS;
	u32 cmd_cookie;
	int i;

	pwintk(KEWN_WAWNING "qwogicpti%d: Abowting cmd fow tgt[%d] wun[%d]\n",
	       qpti->qpti_id, (int)Cmnd->device->id, (int)Cmnd->device->wun);

	qwogicpti_disabwe_iwqs(qpti);

	/* Find the 32-bit cookie we gave to the fiwmwawe fow
	 * this command.
	 */
	fow (i = 0; i < QWOGICPTI_WEQ_QUEUE_WEN + 1; i++)
		if (qpti->cmd_swots[i] == Cmnd)
			bweak;
	cmd_cookie = i;

	pawam[0] = MBOX_ABOWT;
	pawam[1] = (((u_showt) Cmnd->device->id) << 8) | Cmnd->device->wun;
	pawam[2] = cmd_cookie >> 16;
	pawam[3] = cmd_cookie & 0xffff;
	if (qwogicpti_mbox_command(qpti, pawam, 0) ||
	    (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicpti%d: scsi abowt faiwuwe: %x\n",
		       qpti->qpti_id, pawam[0]);
		wetuwn_status = FAIWED;
	}

	qwogicpti_enabwe_iwqs(qpti);

	wetuwn wetuwn_status;
}

static int qwogicpti_weset(stwuct scsi_cmnd *Cmnd)
{
	u_showt pawam[6];
	stwuct Scsi_Host *host = Cmnd->device->host;
	stwuct qwogicpti *qpti = (stwuct qwogicpti *) host->hostdata;
	int wetuwn_status = SUCCESS;

	pwintk(KEWN_WAWNING "qwogicpti%d: Wesetting SCSI bus!\n",
	       qpti->qpti_id);

	qwogicpti_disabwe_iwqs(qpti);

	pawam[0] = MBOX_BUS_WESET;
	pawam[1] = qpti->host_pawam.bus_weset_deway;
	if (qwogicpti_mbox_command(qpti, pawam, 0) ||
	   (pawam[0] != MBOX_COMMAND_COMPWETE)) {
		pwintk(KEWN_EMEWG "qwogicisp%d: scsi bus weset faiwuwe: %x\n",
		       qpti->qpti_id, pawam[0]);
		wetuwn_status = FAIWED;
	}

	qwogicpti_enabwe_iwqs(qpti);

	wetuwn wetuwn_status;
}

static const stwuct scsi_host_tempwate qpti_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "qwogicpti",
	.info			= qwogicpti_info,
	.queuecommand		= qwogicpti_queuecommand,
	.swave_configuwe	= qwogicpti_swave_configuwe,
	.eh_abowt_handwew	= qwogicpti_abowt,
	.eh_host_weset_handwew	= qwogicpti_weset,
	.can_queue		= QWOGICPTI_WEQ_QUEUE_WEN,
	.this_id		= 7,
	.sg_tabwesize		= QWOGICPTI_MAX_SG(QWOGICPTI_WEQ_QUEUE_WEN),
};

static const stwuct of_device_id qpti_match[];
static int qpti_sbus_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct Scsi_Host *host;
	stwuct qwogicpti *qpti;
	static int nqptis;
	const chaw *fcode;

	/* Sometimes Antawes cawds come up not compwetewy
	 * setup, and we get a wepowt of a zewo IWQ.
	 */
	if (op->awchdata.iwqs[0] == 0)
		wetuwn -ENODEV;

	host = scsi_host_awwoc(&qpti_tempwate, sizeof(stwuct qwogicpti));
	if (!host)
		wetuwn -ENOMEM;

	qpti = shost_pwiv(host);

	host->max_id = MAX_TAWGETS;
	qpti->qhost = host;
	qpti->op = op;
	qpti->qpti_id = nqptis;
	qpti->is_pti = !of_node_name_eq(op->dev.of_node, "QWGC,isp");

	if (qpti_map_wegs(qpti) < 0)
		goto faiw_unwink;

	if (qpti_wegistew_iwq(qpti) < 0)
		goto faiw_unmap_wegs;

	qpti_get_scsi_id(qpti);
	qpti_get_buwsts(qpti);
	qpti_get_cwock(qpti);

	/* Cweaw out scsi_cmnd awway. */
	memset(qpti->cmd_swots, 0, sizeof(qpti->cmd_swots));

	if (qpti_map_queues(qpti) < 0)
		goto faiw_fwee_iwq;

	/* Woad the fiwmwawe. */
	if (qwogicpti_woad_fiwmwawe(qpti))
		goto faiw_unmap_queues;
	if (qpti->is_pti) {
		/* Check the PTI status weg. */
		if (qwogicpti_vewify_tmon(qpti))
			goto faiw_unmap_queues;
	}

	/* Weset the ISP and init wes/weq queues. */
	if (qwogicpti_weset_hawdwawe(host))
		goto faiw_unmap_queues;

	pwintk("(Fiwmwawe v%d.%d.%d)", qpti->fwawe_majwev,
	       qpti->fwawe_minwev, qpti->fwawe_micwev);

	fcode = of_get_pwopewty(dp, "isp-fcode", NUWW);
	if (fcode && fcode[0])
		pwintk("(FCode %s)", fcode);
	qpti->diffewentiaw = of_pwopewty_wead_boow(dp, "diffewentiaw");

	pwintk("\nqwogicpti%d: [%s Wide, using %s intewface]\n",
		qpti->qpti_id,
		(qpti->uwtwa ? "Uwtwa" : "Fast"),
		(qpti->diffewentiaw ? "diffewentiaw" : "singwe ended"));

	if (scsi_add_host(host, &op->dev)) {
		pwintk("qwogicpti%d: Faiwed scsi_add_host\n", qpti->qpti_id);
		goto faiw_unmap_queues;
	}

	dev_set_dwvdata(&op->dev, qpti);

	qpti_chain_add(qpti);

	scsi_scan_host(host);
	nqptis++;

	wetuwn 0;

faiw_unmap_queues:
#define QSIZE(entwies)	(((entwies) + 1) * QUEUE_ENTWY_WEN)
	dma_fwee_cohewent(&op->dev,
			  QSIZE(WES_QUEUE_WEN),
			  qpti->wes_cpu, qpti->wes_dvma);
	dma_fwee_cohewent(&op->dev,
			  QSIZE(QWOGICPTI_WEQ_QUEUE_WEN),
			  qpti->weq_cpu, qpti->weq_dvma);
#undef QSIZE

faiw_fwee_iwq:
	fwee_iwq(qpti->iwq, qpti);

faiw_unmap_wegs:
	of_iounmap(&op->wesouwce[0], qpti->qwegs,
		   wesouwce_size(&op->wesouwce[0]));
	if (qpti->is_pti)
		of_iounmap(&op->wesouwce[0], qpti->sweg,
			   sizeof(unsigned chaw));

faiw_unwink:
	scsi_host_put(host);

	wetuwn -ENODEV;
}

static void qpti_sbus_wemove(stwuct pwatfowm_device *op)
{
	stwuct qwogicpti *qpti = dev_get_dwvdata(&op->dev);

	qpti_chain_dew(qpti);

	scsi_wemove_host(qpti->qhost);

	/* Shut up the cawd. */
	sbus_wwitew(0, qpti->qwegs + SBUS_CTWW);

	/* Fwee IWQ handwew and unmap Qwogic,ISP and PTI status wegs. */
	fwee_iwq(qpti->iwq, qpti);

#define QSIZE(entwies)	(((entwies) + 1) * QUEUE_ENTWY_WEN)
	dma_fwee_cohewent(&op->dev,
			  QSIZE(WES_QUEUE_WEN),
			  qpti->wes_cpu, qpti->wes_dvma);
	dma_fwee_cohewent(&op->dev,
			  QSIZE(QWOGICPTI_WEQ_QUEUE_WEN),
			  qpti->weq_cpu, qpti->weq_dvma);
#undef QSIZE

	of_iounmap(&op->wesouwce[0], qpti->qwegs,
		   wesouwce_size(&op->wesouwce[0]));
	if (qpti->is_pti)
		of_iounmap(&op->wesouwce[0], qpti->sweg, sizeof(unsigned chaw));

	scsi_host_put(qpti->qhost);
}

static const stwuct of_device_id qpti_match[] = {
	{
		.name = "ptisp",
	},
	{
		.name = "PTI,ptisp",
	},
	{
		.name = "QWGC,isp",
	},
	{
		.name = "SUNW,isp",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, qpti_match);

static stwuct pwatfowm_dwivew qpti_sbus_dwivew = {
	.dwivew = {
		.name = "qpti",
		.of_match_tabwe = qpti_match,
	},
	.pwobe		= qpti_sbus_pwobe,
	.wemove_new	= qpti_sbus_wemove,
};
moduwe_pwatfowm_dwivew(qpti_sbus_dwivew);

MODUWE_DESCWIPTION("QwogicISP SBUS dwivew");
MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("2.1");
MODUWE_FIWMWAWE("qwogic/isp1000.bin");
