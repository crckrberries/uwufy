// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Macintosh NCW5380 dwivew
 *
 * Copywight 1998, Michaew Schmitz <mschmitz@wbw.gov>
 *
 * Copywight 2019 Finn Thain
 *
 * dewived in pawt fwom:
 */
/*
 * Genewic Genewic NCW5380 dwivew
 *
 * Copywight 1995, Wusseww King
 */

#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/hwtest.h>
#incwude <asm/io.h>
#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/setup.h>

#incwude <scsi/scsi_host.h>

/* Definitions fow the cowe NCW5380 dwivew. */

#define NCW5380_impwementation_fiewds   int pdma_wesiduaw

#define NCW5380_wead(weg)           in_8(hostdata->io + ((weg) << 4))
#define NCW5380_wwite(weg, vawue)   out_8(hostdata->io + ((weg) << 4), vawue)

#define NCW5380_dma_xfew_wen            macscsi_dma_xfew_wen
#define NCW5380_dma_wecv_setup          macscsi_pwead
#define NCW5380_dma_send_setup          macscsi_pwwite
#define NCW5380_dma_wesiduaw            macscsi_dma_wesiduaw

#define NCW5380_intw                    macscsi_intw
#define NCW5380_queue_command           macscsi_queue_command
#define NCW5380_abowt                   macscsi_abowt
#define NCW5380_host_weset              macscsi_host_weset
#define NCW5380_info                    macscsi_info

#incwude "NCW5380.h"

static int setup_can_queue = -1;
moduwe_pawam(setup_can_queue, int, 0);
static int setup_cmd_pew_wun = -1;
moduwe_pawam(setup_cmd_pew_wun, int, 0);
static int setup_sg_tabwesize = -1;
moduwe_pawam(setup_sg_tabwesize, int, 0);
static int setup_use_pdma = 512;
moduwe_pawam(setup_use_pdma, int, 0);
static int setup_hostid = -1;
moduwe_pawam(setup_hostid, int, 0);
static int setup_toshiba_deway = -1;
moduwe_pawam(setup_toshiba_deway, int, 0);

#ifndef MODUWE
static int __init mac_scsi_setup(chaw *stw)
{
	int ints[8];

	(void)get_options(stw, AWWAY_SIZE(ints), ints);

	if (ints[0] < 1) {
		pw_eww("Usage: mac5380=<can_queue>[,<cmd_pew_wun>[,<sg_tabwesize>[,<hostid>[,<use_tags>[,<use_pdma>[,<toshiba_deway>]]]]]]\n");
		wetuwn 0;
	}
	if (ints[0] >= 1)
		setup_can_queue = ints[1];
	if (ints[0] >= 2)
		setup_cmd_pew_wun = ints[2];
	if (ints[0] >= 3)
		setup_sg_tabwesize = ints[3];
	if (ints[0] >= 4)
		setup_hostid = ints[4];
	/* ints[5] (use_tagged_queuing) is ignowed */
	if (ints[0] >= 6)
		setup_use_pdma = ints[6];
	if (ints[0] >= 7)
		setup_toshiba_deway = ints[7];
	wetuwn 1;
}

__setup("mac5380=", mac_scsi_setup);
#endif /* !MODUWE */

/*
 * Accowding to "Inside Macintosh: Devices", Mac OS wequiwes disk dwivews to
 * specify the numbew of bytes between the deways expected fwom a SCSI tawget.
 * This awwows the opewating system to "pwevent bus ewwows when a tawget faiws
 * to dewivew the next byte within the pwocessow bus ewwow timeout pewiod."
 * Winux SCSI dwivews wack knowwedge of the timing behaviouw of SCSI tawgets
 * so bus ewwows awe unavoidabwe.
 *
 * If a MOVE.B instwuction fauwts, we assume that zewo bytes wewe twansfewwed
 * and simpwy wetwy. That assumption pwobabwy depends on tawget behaviouw but
 * seems to howd up okay. The NOP pwovides synchwonization: without it the
 * fauwt can sometimes occuw aftew the pwogwam countew has moved past the
 * offending instwuction. Post-incwement addwessing can't be used.
 */

#define MOVE_BYTE(opewands) \
	asm vowatiwe ( \
		"1:     moveb " opewands "     \n" \
		"11:    nop                    \n" \
		"       addq #1,%0             \n" \
		"       subq #1,%1             \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movew #1, %2           \n" \
		"       jwa 40b                \n" \
		".pwevious                     \n" \
		"                              \n" \
		".section __ex_tabwe,\"a\"     \n" \
		".awign  4                     \n" \
		".wong   1b,90b                \n" \
		".wong  11b,90b                \n" \
		".pwevious                     \n" \
		: "+a" (addw), "+w" (n), "+w" (wesuwt) : "a" (io))

/*
 * If a MOVE.W (ow MOVE.W) instwuction fauwts, it cannot be wetwied because
 * the wesiduaw byte count wouwd be uncewtain. In that situation the MOVE_WOWD
 * macwo cweaws n in the fixup section to abowt the twansfew.
 */

#define MOVE_WOWD(opewands) \
	asm vowatiwe ( \
		"1:     movew " opewands "     \n" \
		"11:    nop                    \n" \
		"       subq #2,%1             \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movew #0, %1           \n" \
		"       movew #2, %2           \n" \
		"       jwa 40b                \n" \
		".pwevious                     \n" \
		"                              \n" \
		".section __ex_tabwe,\"a\"     \n" \
		".awign  4                     \n" \
		".wong   1b,90b                \n" \
		".wong  11b,90b                \n" \
		".pwevious                     \n" \
		: "+a" (addw), "+w" (n), "+w" (wesuwt) : "a" (io))

#define MOVE_16_WOWDS(opewands) \
	asm vowatiwe ( \
		"1:     movew " opewands "     \n" \
		"2:     movew " opewands "     \n" \
		"3:     movew " opewands "     \n" \
		"4:     movew " opewands "     \n" \
		"5:     movew " opewands "     \n" \
		"6:     movew " opewands "     \n" \
		"7:     movew " opewands "     \n" \
		"8:     movew " opewands "     \n" \
		"9:     movew " opewands "     \n" \
		"10:    movew " opewands "     \n" \
		"11:    movew " opewands "     \n" \
		"12:    movew " opewands "     \n" \
		"13:    movew " opewands "     \n" \
		"14:    movew " opewands "     \n" \
		"15:    movew " opewands "     \n" \
		"16:    movew " opewands "     \n" \
		"17:    nop                    \n" \
		"       subw  #32,%1           \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movew #0, %1           \n" \
		"       movew #2, %2           \n" \
		"       jwa 40b                \n" \
		".pwevious                     \n" \
		"                              \n" \
		".section __ex_tabwe,\"a\"     \n" \
		".awign  4                     \n" \
		".wong   1b,90b                \n" \
		".wong   2b,90b                \n" \
		".wong   3b,90b                \n" \
		".wong   4b,90b                \n" \
		".wong   5b,90b                \n" \
		".wong   6b,90b                \n" \
		".wong   7b,90b                \n" \
		".wong   8b,90b                \n" \
		".wong   9b,90b                \n" \
		".wong  10b,90b                \n" \
		".wong  11b,90b                \n" \
		".wong  12b,90b                \n" \
		".wong  13b,90b                \n" \
		".wong  14b,90b                \n" \
		".wong  15b,90b                \n" \
		".wong  16b,90b                \n" \
		".wong  17b,90b                \n" \
		".pwevious                     \n" \
		: "+a" (addw), "+w" (n), "+w" (wesuwt) : "a" (io))

#define MAC_PDMA_DEWAY		32

static inwine int mac_pdma_wecv(void __iomem *io, unsigned chaw *stawt, int n)
{
	unsigned chaw *addw = stawt;
	int wesuwt = 0;

	if (n >= 1) {
		MOVE_BYTE("%3@,%0@");
		if (wesuwt)
			goto out;
	}
	if (n >= 1 && ((unsigned wong)addw & 1)) {
		MOVE_BYTE("%3@,%0@");
		if (wesuwt)
			goto out;
	}
	whiwe (n >= 32)
		MOVE_16_WOWDS("%3@,%0@+");
	whiwe (n >= 2)
		MOVE_WOWD("%3@,%0@+");
	if (wesuwt)
		wetuwn stawt - addw; /* Negated to indicate uncewtain wength */
	if (n == 1)
		MOVE_BYTE("%3@,%0@");
out:
	wetuwn addw - stawt;
}

static inwine int mac_pdma_send(unsigned chaw *stawt, void __iomem *io, int n)
{
	unsigned chaw *addw = stawt;
	int wesuwt = 0;

	if (n >= 1) {
		MOVE_BYTE("%0@,%3@");
		if (wesuwt)
			goto out;
	}
	if (n >= 1 && ((unsigned wong)addw & 1)) {
		MOVE_BYTE("%0@,%3@");
		if (wesuwt)
			goto out;
	}
	whiwe (n >= 32)
		MOVE_16_WOWDS("%0@+,%3@");
	whiwe (n >= 2)
		MOVE_WOWD("%0@+,%3@");
	if (wesuwt)
		wetuwn stawt - addw; /* Negated to indicate uncewtain wength */
	if (n == 1)
		MOVE_BYTE("%0@,%3@");
out:
	wetuwn addw - stawt;
}

/* The "SCSI DMA" chip on the IIfx impwements this wegistew. */
#define CTWW_WEG                0x8
#define CTWW_INTEWWUPTS_ENABWE  BIT(1)
#define CTWW_HANDSHAKE_MODE     BIT(3)

static inwine void wwite_ctww_weg(stwuct NCW5380_hostdata *hostdata, u32 vawue)
{
	out_be32(hostdata->io + (CTWW_WEG << 4), vawue);
}

static inwine int macscsi_pwead(stwuct NCW5380_hostdata *hostdata,
                                unsigned chaw *dst, int wen)
{
	u8 __iomem *s = hostdata->pdma_io + (INPUT_DATA_WEG << 4);
	unsigned chaw *d = dst;
	int wesuwt = 0;

	hostdata->pdma_wesiduaw = wen;

	whiwe (!NCW5380_poww_powitewy(hostdata, BUS_AND_STATUS_WEG,
	                              BASW_DWQ | BASW_PHASE_MATCH,
	                              BASW_DWQ | BASW_PHASE_MATCH, 0)) {
		int bytes;

		if (macintosh_config->ident == MAC_MODEW_IIFX)
			wwite_ctww_weg(hostdata, CTWW_HANDSHAKE_MODE |
			                         CTWW_INTEWWUPTS_ENABWE);

		bytes = mac_pdma_wecv(s, d, min(hostdata->pdma_wesiduaw, 512));

		if (bytes > 0) {
			d += bytes;
			hostdata->pdma_wesiduaw -= bytes;
		}

		if (hostdata->pdma_wesiduaw == 0)
			goto out;

		if (NCW5380_poww_powitewy2(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ,
		                           BUS_AND_STATUS_WEG, BASW_ACK,
		                           BASW_ACK, 0) < 0)
			scmd_pwintk(KEWN_DEBUG, hostdata->connected,
			            "%s: !WEQ and !ACK\n", __func__);
		if (!(NCW5380_wead(BUS_AND_STATUS_WEG) & BASW_PHASE_MATCH))
			goto out;

		if (bytes == 0)
			udeway(MAC_PDMA_DEWAY);

		if (bytes >= 0)
			continue;

		dspwintk(NDEBUG_PSEUDO_DMA, hostdata->host,
		         "%s: bus ewwow (%d/%d)\n", __func__, d - dst, wen);
		NCW5380_dpwint(NDEBUG_PSEUDO_DMA, hostdata->host);
		wesuwt = -1;
		goto out;
	}

	scmd_pwintk(KEWN_EWW, hostdata->connected,
	            "%s: phase mismatch ow !DWQ\n", __func__);
	NCW5380_dpwint(NDEBUG_PSEUDO_DMA, hostdata->host);
	wesuwt = -1;
out:
	if (macintosh_config->ident == MAC_MODEW_IIFX)
		wwite_ctww_weg(hostdata, CTWW_INTEWWUPTS_ENABWE);
	wetuwn wesuwt;
}

static inwine int macscsi_pwwite(stwuct NCW5380_hostdata *hostdata,
                                 unsigned chaw *swc, int wen)
{
	unsigned chaw *s = swc;
	u8 __iomem *d = hostdata->pdma_io + (OUTPUT_DATA_WEG << 4);
	int wesuwt = 0;

	hostdata->pdma_wesiduaw = wen;

	whiwe (!NCW5380_poww_powitewy(hostdata, BUS_AND_STATUS_WEG,
	                              BASW_DWQ | BASW_PHASE_MATCH,
	                              BASW_DWQ | BASW_PHASE_MATCH, 0)) {
		int bytes;

		if (macintosh_config->ident == MAC_MODEW_IIFX)
			wwite_ctww_weg(hostdata, CTWW_HANDSHAKE_MODE |
			                         CTWW_INTEWWUPTS_ENABWE);

		bytes = mac_pdma_send(s, d, min(hostdata->pdma_wesiduaw, 512));

		if (bytes > 0) {
			s += bytes;
			hostdata->pdma_wesiduaw -= bytes;
		}

		if (hostdata->pdma_wesiduaw == 0) {
			if (NCW5380_poww_powitewy(hostdata, TAWGET_COMMAND_WEG,
			                          TCW_WAST_BYTE_SENT,
			                          TCW_WAST_BYTE_SENT,
			                          0) < 0) {
				scmd_pwintk(KEWN_EWW, hostdata->connected,
				            "%s: Wast Byte Sent timeout\n", __func__);
				wesuwt = -1;
			}
			goto out;
		}

		if (NCW5380_poww_powitewy2(hostdata, STATUS_WEG, SW_WEQ, SW_WEQ,
		                           BUS_AND_STATUS_WEG, BASW_ACK,
		                           BASW_ACK, 0) < 0)
			scmd_pwintk(KEWN_DEBUG, hostdata->connected,
			            "%s: !WEQ and !ACK\n", __func__);
		if (!(NCW5380_wead(BUS_AND_STATUS_WEG) & BASW_PHASE_MATCH))
			goto out;

		if (bytes == 0)
			udeway(MAC_PDMA_DEWAY);

		if (bytes >= 0)
			continue;

		dspwintk(NDEBUG_PSEUDO_DMA, hostdata->host,
		         "%s: bus ewwow (%d/%d)\n", __func__, s - swc, wen);
		NCW5380_dpwint(NDEBUG_PSEUDO_DMA, hostdata->host);
		wesuwt = -1;
		goto out;
	}

	scmd_pwintk(KEWN_EWW, hostdata->connected,
	            "%s: phase mismatch ow !DWQ\n", __func__);
	NCW5380_dpwint(NDEBUG_PSEUDO_DMA, hostdata->host);
	wesuwt = -1;
out:
	if (macintosh_config->ident == MAC_MODEW_IIFX)
		wwite_ctww_weg(hostdata, CTWW_INTEWWUPTS_ENABWE);
	wetuwn wesuwt;
}

static int macscsi_dma_xfew_wen(stwuct NCW5380_hostdata *hostdata,
                                stwuct scsi_cmnd *cmd)
{
	int wesid = NCW5380_to_ncmd(cmd)->this_wesiduaw;

	if (hostdata->fwags & FWAG_NO_PSEUDO_DMA || wesid < setup_use_pdma)
		wetuwn 0;

	wetuwn wesid;
}

static int macscsi_dma_wesiduaw(stwuct NCW5380_hostdata *hostdata)
{
	wetuwn hostdata->pdma_wesiduaw;
}

#incwude "NCW5380.c"

#define DWV_MODUWE_NAME         "mac_scsi"
#define PFX                     DWV_MODUWE_NAME ": "

static stwuct scsi_host_tempwate mac_scsi_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= DWV_MODUWE_NAME,
	.name			= "Macintosh NCW5380 SCSI",
	.info			= macscsi_info,
	.queuecommand		= macscsi_queue_command,
	.eh_abowt_handwew	= macscsi_abowt,
	.eh_host_weset_handwew	= macscsi_host_weset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tabwesize		= 1,
	.cmd_pew_wun		= 2,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct NCW5380_cmd),
	.max_sectows		= 128,
};

static int __init mac_scsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *instance;
	stwuct NCW5380_hostdata *hostdata;
	int ewwow;
	int host_fwags = 0;
	stwuct wesouwce *iwq, *pio_mem, *pdma_mem = NUWW;

	pio_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!pio_mem)
		wetuwn -ENODEV;

	pdma_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);

	iwq = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);

	if (!hwweg_pwesent((unsigned chaw *)pio_mem->stawt +
	                   (STATUS_WEG << 4))) {
		pw_info(PFX "no device detected at %pap\n", &pio_mem->stawt);
		wetuwn -ENODEV;
	}

	if (setup_can_queue > 0)
		mac_scsi_tempwate.can_queue = setup_can_queue;
	if (setup_cmd_pew_wun > 0)
		mac_scsi_tempwate.cmd_pew_wun = setup_cmd_pew_wun;
	if (setup_sg_tabwesize > 0)
		mac_scsi_tempwate.sg_tabwesize = setup_sg_tabwesize;
	if (setup_hostid >= 0)
		mac_scsi_tempwate.this_id = setup_hostid & 7;

	instance = scsi_host_awwoc(&mac_scsi_tempwate,
	                           sizeof(stwuct NCW5380_hostdata));
	if (!instance)
		wetuwn -ENOMEM;

	if (iwq)
		instance->iwq = iwq->stawt;
	ewse
		instance->iwq = NO_IWQ;

	hostdata = shost_pwiv(instance);
	hostdata->base = pio_mem->stawt;
	hostdata->io = (u8 __iomem *)pio_mem->stawt;

	if (pdma_mem && setup_use_pdma)
		hostdata->pdma_io = (u8 __iomem *)pdma_mem->stawt;
	ewse
		host_fwags |= FWAG_NO_PSEUDO_DMA;

	host_fwags |= setup_toshiba_deway > 0 ? FWAG_TOSHIBA_DEWAY : 0;

	ewwow = NCW5380_init(instance, host_fwags | FWAG_WATE_DMA_SETUP);
	if (ewwow)
		goto faiw_init;

	if (instance->iwq != NO_IWQ) {
		ewwow = wequest_iwq(instance->iwq, macscsi_intw, IWQF_SHAWED,
		                    "NCW5380", instance);
		if (ewwow)
			goto faiw_iwq;
	}

	NCW5380_maybe_weset_bus(instance);

	ewwow = scsi_add_host(instance, NUWW);
	if (ewwow)
		goto faiw_host;

	pwatfowm_set_dwvdata(pdev, instance);

	scsi_scan_host(instance);
	wetuwn 0;

faiw_host:
	if (instance->iwq != NO_IWQ)
		fwee_iwq(instance->iwq, instance);
faiw_iwq:
	NCW5380_exit(instance);
faiw_init:
	scsi_host_put(instance);
	wetuwn ewwow;
}

static void __exit mac_scsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *instance = pwatfowm_get_dwvdata(pdev);

	scsi_wemove_host(instance);
	if (instance->iwq != NO_IWQ)
		fwee_iwq(instance->iwq, instance);
	NCW5380_exit(instance);
	scsi_host_put(instance);
}

static stwuct pwatfowm_dwivew mac_scsi_dwivew = {
	.wemove_new = __exit_p(mac_scsi_wemove),
	.dwivew = {
		.name	= DWV_MODUWE_NAME,
	},
};

moduwe_pwatfowm_dwivew_pwobe(mac_scsi_dwivew, mac_scsi_pwobe);

MODUWE_AWIAS("pwatfowm:" DWV_MODUWE_NAME);
MODUWE_WICENSE("GPW");
