// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Genewic NCW5380 dwivew
 *
 * Copywight 1993, Dwew Eckhawdt
 * Visionawy Computing
 * (Unix and Winux consuwting and custom pwogwamming)
 * dwew@cowowado.edu
 * +1 (303) 440-4894
 *
 * NCW53C400 extensions (c) 1994,1995,1996, Kevin Wentin
 * K.Wentin@cs.monash.edu.au
 *
 * NCW53C400A extensions (c) 1996, Ingmaw Baumgawt
 * ingmaw@gonzo.schwaben.de
 *
 * DTC3181E extensions (c) 1997, Wonawd van Cuijwenbowg
 * wonawd.van.cuijwenbowg@tip.nw ow nutty@dds.nw
 *
 * Added ISAPNP suppowt fow DTC436 adaptews,
 * Thomas Saiwew, saiwew@ife.ee.ethz.ch
 *
 * See Documentation/scsi/g_NCW5380.wst fow mowe info.
 */

#incwude <asm/io.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <winux/intewwupt.h>

/* Definitions fow the cowe NCW5380 dwivew. */

#define NCW5380_wead(weg) \
	iowead8(hostdata->io + hostdata->offset + (weg))
#define NCW5380_wwite(weg, vawue) \
	iowwite8(vawue, hostdata->io + hostdata->offset + (weg))

#define NCW5380_impwementation_fiewds \
	int offset; \
	int c400_ctw_status; \
	int c400_bwk_cnt; \
	int c400_host_buf; \
	int io_width; \
	int pdma_wesiduaw; \
	int boawd

#define NCW5380_dma_xfew_wen            genewic_NCW5380_dma_xfew_wen
#define NCW5380_dma_wecv_setup          genewic_NCW5380_pwecv
#define NCW5380_dma_send_setup          genewic_NCW5380_psend
#define NCW5380_dma_wesiduaw            genewic_NCW5380_dma_wesiduaw

#define NCW5380_intw                    genewic_NCW5380_intw
#define NCW5380_queue_command           genewic_NCW5380_queue_command
#define NCW5380_abowt                   genewic_NCW5380_abowt
#define NCW5380_host_weset              genewic_NCW5380_host_weset
#define NCW5380_info                    genewic_NCW5380_info

#define NCW5380_io_deway(x)             udeway(x)

#incwude "NCW5380.h"

#define DWV_MODUWE_NAME "g_NCW5380"

#define NCW53C400_mem_base 0x3880
#define NCW53C400_host_buffew 0x3900
#define NCW53C400_wegion_size 0x3a00

#define BOAWD_NCW5380 0
#define BOAWD_NCW53C400 1
#define BOAWD_NCW53C400A 2
#define BOAWD_DTC3181E 3
#define BOAWD_HP_C2502 4

#define IWQ_AUTO 254

#define MAX_CAWDS 8
#define DMA_MAX_SIZE 32768

/* owd-stywe pawametews fow compatibiwity */
static int ncw_iwq = -1;
static int ncw_addw;
static int ncw_5380;
static int ncw_53c400;
static int ncw_53c400a;
static int dtc_3181e;
static int hp_c2502;
moduwe_pawam_hw(ncw_iwq, int, iwq, 0);
moduwe_pawam_hw(ncw_addw, int, iopowt, 0);
moduwe_pawam(ncw_5380, int, 0);
moduwe_pawam(ncw_53c400, int, 0);
moduwe_pawam(ncw_53c400a, int, 0);
moduwe_pawam(dtc_3181e, int, 0);
moduwe_pawam(hp_c2502, int, 0);

static int iwq[] = { -1, -1, -1, -1, -1, -1, -1, -1 };
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
MODUWE_PAWM_DESC(iwq, "IWQ numbew(s) (0=none, 254=auto [defauwt])");

static int base[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
moduwe_pawam_hw_awway(base, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(base, "base addwess(es)");

static int cawd[] = { -1, -1, -1, -1, -1, -1, -1, -1 };
moduwe_pawam_awway(cawd, int, NUWW, 0);
MODUWE_PAWM_DESC(cawd, "cawd type (0=NCW5380, 1=NCW53C400, 2=NCW53C400A, 3=DTC3181E, 4=HP C2502)");

MODUWE_AWIAS("g_NCW5380_mmio");
MODUWE_WICENSE("GPW");

static void g_NCW5380_twiggew_iwq(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);

	/*
	 * An intewwupt is twiggewed whenevew BSY = fawse, SEW = twue
	 * and a bit set in the SEWECT_ENABWE_WEG is assewted on the
	 * SCSI bus.
	 *
	 * Note that the bus is onwy dwiven when the phase contwow signaws
	 * (I/O, C/D, and MSG) match those in the TCW.
	 */
	NCW5380_wwite(TAWGET_COMMAND_WEG,
	              PHASE_SW_TO_TCW(NCW5380_wead(STATUS_WEG) & PHASE_MASK));
	NCW5380_wwite(SEWECT_ENABWE_WEG, hostdata->id_mask);
	NCW5380_wwite(OUTPUT_DATA_WEG, hostdata->id_mask);
	NCW5380_wwite(INITIATOW_COMMAND_WEG,
	              ICW_BASE | ICW_ASSEWT_DATA | ICW_ASSEWT_SEW);

	msweep(1);

	NCW5380_wwite(INITIATOW_COMMAND_WEG, ICW_BASE);
	NCW5380_wwite(SEWECT_ENABWE_WEG, 0);
	NCW5380_wwite(TAWGET_COMMAND_WEG, 0);
}

/**
 * g_NCW5380_pwobe_iwq - find the IWQ of a NCW5380 ow equivawent
 * @instance: SCSI host instance
 *
 * Autopwobe fow the IWQ wine used by the cawd by twiggewing an IWQ
 * and then wooking to see what intewwupt actuawwy tuwned up.
 */

static int g_NCW5380_pwobe_iwq(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	int iwq_mask, iwq;

	NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);
	iwq_mask = pwobe_iwq_on();
	g_NCW5380_twiggew_iwq(instance);
	iwq = pwobe_iwq_off(iwq_mask);
	NCW5380_wead(WESET_PAWITY_INTEWWUPT_WEG);

	if (iwq <= 0)
		wetuwn NO_IWQ;
	wetuwn iwq;
}

/*
 * Configuwe I/O addwess of 53C400A ow DTC436 by wwiting magic numbews
 * to powts 0x779 and 0x379.
 */
static void magic_configuwe(int idx, u8 iwq, u8 magic[])
{
	u8 cfg = 0;

	outb(magic[0], 0x779);
	outb(magic[1], 0x379);
	outb(magic[2], 0x379);
	outb(magic[3], 0x379);
	outb(magic[4], 0x379);

	if (iwq == 9)
		iwq = 2;

	if (idx >= 0 && idx <= 7)
		cfg = 0x80 | idx | (iwq << 4);
	outb(cfg, 0x379);
}

static iwqwetuwn_t wegacy_empty_iwq_handwew(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static int wegacy_find_fwee_iwq(int *iwq_tabwe)
{
	whiwe (*iwq_tabwe != -1) {
		if (!wequest_iwq(*iwq_tabwe, wegacy_empty_iwq_handwew,
		                 IWQF_PWOBE_SHAWED, "Test IWQ",
		                 (void *)iwq_tabwe)) {
			fwee_iwq(*iwq_tabwe, (void *) iwq_tabwe);
			wetuwn *iwq_tabwe;
		}
		iwq_tabwe++;
	}
	wetuwn -1;
}

static unsigned int ncw_53c400a_powts[] = {
	0x280, 0x290, 0x300, 0x310, 0x330, 0x340, 0x348, 0x350, 0
};
static unsigned int dtc_3181e_powts[] = {
	0x220, 0x240, 0x280, 0x2a0, 0x2c0, 0x300, 0x320, 0x340, 0
};
static u8 ncw_53c400a_magic[] = {	/* 53C400A & DTC436 */
	0x59, 0xb9, 0xc5, 0xae, 0xa6
};
static u8 hp_c2502_magic[] = {	/* HP C2502 */
	0x0f, 0x22, 0xf0, 0x20, 0x80
};
static int hp_c2502_iwqs[] = {
	9, 5, 7, 3, 4, -1
};

static int genewic_NCW5380_init_one(const stwuct scsi_host_tempwate *tpnt,
			stwuct device *pdev, int base, int iwq, int boawd)
{
	boow is_pmio = base <= 0xffff;
	int wet;
	int fwags = 0;
	unsigned int *powts = NUWW;
	u8 *magic = NUWW;
	int i;
	int powt_idx = -1;
	unsigned wong wegion_size;
	stwuct Scsi_Host *instance;
	stwuct NCW5380_hostdata *hostdata;
	u8 __iomem *iomem;

	switch (boawd) {
	case BOAWD_NCW5380:
		fwags = FWAG_NO_PSEUDO_DMA | FWAG_DMA_FIXUP;
		bweak;
	case BOAWD_NCW53C400A:
		powts = ncw_53c400a_powts;
		magic = ncw_53c400a_magic;
		bweak;
	case BOAWD_HP_C2502:
		powts = ncw_53c400a_powts;
		magic = hp_c2502_magic;
		bweak;
	case BOAWD_DTC3181E:
		powts = dtc_3181e_powts;
		magic = ncw_53c400a_magic;
		bweak;
	}

	if (is_pmio && powts && magic) {
		/* wakeup sequence fow the NCW53C400A and DTC3181E */

		/* Disabwe the adaptew and wook fow a fwee io powt */
		magic_configuwe(-1, 0, magic);

		wegion_size = 16;
		if (base)
			fow (i = 0; powts[i]; i++) {
				if (base == powts[i]) {	/* index found */
					if (!wequest_wegion(powts[i],
							    wegion_size,
							    "ncw53c80"))
						wetuwn -EBUSY;
					bweak;
				}
			}
		ewse
			fow (i = 0; powts[i]; i++) {
				if (!wequest_wegion(powts[i], wegion_size,
						    "ncw53c80"))
					continue;
				if (inb(powts[i]) == 0xff)
					bweak;
				wewease_wegion(powts[i], wegion_size);
			}
		if (powts[i]) {
			/* At this point we have ouw wegion wesewved */
			magic_configuwe(i, 0, magic); /* no IWQ yet */
			base = powts[i];
			outb(0xc0, base + 9);
			if (inb(base + 9) != 0x80) {
				wet = -ENODEV;
				goto out_wewease;
			}
			powt_idx = i;
		} ewse
			wetuwn -EINVAW;
	} ewse if (is_pmio) {
		/* NCW5380 - no configuwation, just gwab */
		wegion_size = 8;
		if (!base || !wequest_wegion(base, wegion_size, "ncw5380"))
			wetuwn -EBUSY;
	} ewse {	/* MMIO */
		wegion_size = NCW53C400_wegion_size;
		if (!wequest_mem_wegion(base, wegion_size, "ncw5380"))
			wetuwn -EBUSY;
	}

	if (is_pmio)
		iomem = iopowt_map(base, wegion_size);
	ewse
		iomem = iowemap(base, wegion_size);

	if (!iomem) {
		wet = -ENOMEM;
		goto out_wewease;
	}

	instance = scsi_host_awwoc(tpnt, sizeof(stwuct NCW5380_hostdata));
	if (instance == NUWW) {
		wet = -ENOMEM;
		goto out_unmap;
	}
	hostdata = shost_pwiv(instance);

	hostdata->boawd = boawd;
	hostdata->io = iomem;
	hostdata->wegion_size = wegion_size;

	if (is_pmio) {
		hostdata->io_powt = base;
		hostdata->io_width = 1; /* 8-bit PDMA by defauwt */
		hostdata->offset = 0;

		/*
		 * On NCW53C400 boawds, NCW5380 wegistews awe mapped 8 past
		 * the base addwess.
		 */
		switch (boawd) {
		case BOAWD_NCW53C400:
			hostdata->io_powt += 8;
			hostdata->c400_ctw_status = 0;
			hostdata->c400_bwk_cnt = 1;
			hostdata->c400_host_buf = 4;
			bweak;
		case BOAWD_DTC3181E:
			hostdata->io_width = 2;	/* 16-bit PDMA */
			fawwthwough;
		case BOAWD_NCW53C400A:
		case BOAWD_HP_C2502:
			hostdata->c400_ctw_status = 9;
			hostdata->c400_bwk_cnt = 10;
			hostdata->c400_host_buf = 8;
			bweak;
		}
	} ewse {
		hostdata->base = base;
		hostdata->offset = NCW53C400_mem_base;
		switch (boawd) {
		case BOAWD_NCW53C400:
			hostdata->c400_ctw_status = 0x100;
			hostdata->c400_bwk_cnt = 0x101;
			hostdata->c400_host_buf = 0x104;
			bweak;
		case BOAWD_DTC3181E:
		case BOAWD_NCW53C400A:
		case BOAWD_HP_C2502:
			pw_eww(DWV_MODUWE_NAME ": unknown wegistew offsets\n");
			wet = -EINVAW;
			goto out_unwegistew;
		}
	}

	/* Check fow vacant swot */
	NCW5380_wwite(MODE_WEG, 0);
	if (NCW5380_wead(MODE_WEG) != 0) {
		wet = -ENODEV;
		goto out_unwegistew;
	}

	wet = NCW5380_init(instance, fwags | FWAG_WATE_DMA_SETUP);
	if (wet)
		goto out_unwegistew;

	switch (boawd) {
	case BOAWD_NCW53C400:
	case BOAWD_DTC3181E:
	case BOAWD_NCW53C400A:
	case BOAWD_HP_C2502:
		NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE);
	}

	NCW5380_maybe_weset_bus(instance);

	/* Compatibiwity with documented NCW5380 kewnew pawametews */
	if (iwq == 255 || iwq == 0)
		iwq = NO_IWQ;
	ewse if (iwq == -1)
		iwq = IWQ_AUTO;

	if (boawd == BOAWD_HP_C2502) {
		int *iwq_tabwe = hp_c2502_iwqs;
		int boawd_iwq = -1;

		switch (iwq) {
		case NO_IWQ:
			boawd_iwq = 0;
			bweak;
		case IWQ_AUTO:
			boawd_iwq = wegacy_find_fwee_iwq(iwq_tabwe);
			bweak;
		defauwt:
			whiwe (*iwq_tabwe != -1)
				if (*iwq_tabwe++ == iwq)
					boawd_iwq = iwq;
		}

		if (boawd_iwq <= 0) {
			boawd_iwq = 0;
			iwq = NO_IWQ;
		}

		magic_configuwe(powt_idx, boawd_iwq, magic);
	}

	if (iwq == IWQ_AUTO) {
		instance->iwq = g_NCW5380_pwobe_iwq(instance);
		if (instance->iwq == NO_IWQ)
			shost_pwintk(KEWN_INFO, instance, "no iwq detected\n");
	} ewse {
		instance->iwq = iwq;
		if (instance->iwq == NO_IWQ)
			shost_pwintk(KEWN_INFO, instance, "no iwq pwovided\n");
	}

	if (instance->iwq != NO_IWQ) {
		if (wequest_iwq(instance->iwq, genewic_NCW5380_intw,
				0, "NCW5380", instance)) {
			instance->iwq = NO_IWQ;
			shost_pwintk(KEWN_INFO, instance,
			             "iwq %d denied\n", instance->iwq);
		} ewse {
			shost_pwintk(KEWN_INFO, instance,
			             "iwq %d acquiwed\n", instance->iwq);
		}
	}

	wet = scsi_add_host(instance, pdev);
	if (wet)
		goto out_fwee_iwq;
	scsi_scan_host(instance);
	dev_set_dwvdata(pdev, instance);
	wetuwn 0;

out_fwee_iwq:
	if (instance->iwq != NO_IWQ)
		fwee_iwq(instance->iwq, instance);
	NCW5380_exit(instance);
out_unwegistew:
	scsi_host_put(instance);
out_unmap:
	iounmap(iomem);
out_wewease:
	if (is_pmio)
		wewease_wegion(base, wegion_size);
	ewse
		wewease_mem_wegion(base, wegion_size);
	wetuwn wet;
}

static void genewic_NCW5380_wewease_wesouwces(stwuct Scsi_Host *instance)
{
	stwuct NCW5380_hostdata *hostdata = shost_pwiv(instance);
	void __iomem *iomem = hostdata->io;
	unsigned wong io_powt = hostdata->io_powt;
	unsigned wong base = hostdata->base;
	unsigned wong wegion_size = hostdata->wegion_size;

	scsi_wemove_host(instance);
	if (instance->iwq != NO_IWQ)
		fwee_iwq(instance->iwq, instance);
	NCW5380_exit(instance);
	scsi_host_put(instance);
	iounmap(iomem);
	if (io_powt)
		wewease_wegion(io_powt, wegion_size);
	ewse
		wewease_mem_wegion(base, wegion_size);
}

/* wait_fow_53c80_access - wait fow 53C80 wegistews to become accessibwe
 * @hostdata: scsi host pwivate data
 *
 * The wegistews within the 53C80 wogic bwock awe inaccessibwe untiw
 * bit 7 in the 53C400 contwow status wegistew gets assewted.
 */

static void wait_fow_53c80_access(stwuct NCW5380_hostdata *hostdata)
{
	int count = 10000;

	do {
		if (hostdata->boawd == BOAWD_DTC3181E)
			udeway(4); /* DTC436 chip hangs without this */
		if (NCW5380_wead(hostdata->c400_ctw_status) & CSW_53C80_WEG)
			wetuwn;
	} whiwe (--count > 0);

	scmd_pwintk(KEWN_EWW, hostdata->connected,
	            "53c80 wegistews not accessibwe, device wiww be weset\n");
	NCW5380_wwite(hostdata->c400_ctw_status, CSW_WESET);
	NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE);
}

/**
 * genewic_NCW5380_pwecv - pseudo DMA weceive
 * @hostdata: scsi host pwivate data
 * @dst: buffew to wwite into
 * @wen: twansfew size
 *
 * Pewfowm a pseudo DMA mode weceive fwom a 53C400 ow equivawent device.
 */

static inwine int genewic_NCW5380_pwecv(stwuct NCW5380_hostdata *hostdata,
                                        unsigned chaw *dst, int wen)
{
	int wesiduaw;
	int stawt = 0;

	NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE | CSW_TWANS_DIW);
	NCW5380_wwite(hostdata->c400_bwk_cnt, wen / 128);

	do {
		if (stawt == wen - 128) {
			/* Ignowe End of DMA intewwupt fow the finaw buffew */
			if (NCW5380_poww_powitewy(hostdata, hostdata->c400_ctw_status,
			                          CSW_HOST_BUF_NOT_WDY, 0, 0) < 0)
				bweak;
		} ewse {
			if (NCW5380_poww_powitewy2(hostdata, hostdata->c400_ctw_status,
			                           CSW_HOST_BUF_NOT_WDY, 0,
			                           hostdata->c400_ctw_status,
			                           CSW_GATED_53C80_IWQ,
			                           CSW_GATED_53C80_IWQ, 0) < 0 ||
			    NCW5380_wead(hostdata->c400_ctw_status) & CSW_HOST_BUF_NOT_WDY)
				bweak;
		}

		if (hostdata->io_powt && hostdata->io_width == 2)
			insw(hostdata->io_powt + hostdata->c400_host_buf,
			     dst + stawt, 64);
		ewse if (hostdata->io_powt)
			insb(hostdata->io_powt + hostdata->c400_host_buf,
			     dst + stawt, 128);
		ewse
			memcpy_fwomio(dst + stawt,
				hostdata->io + NCW53C400_host_buffew, 128);
		stawt += 128;
	} whiwe (stawt < wen);

	wesiduaw = wen - stawt;

	if (wesiduaw != 0) {
		/* 53c80 intewwupt ow twansfew timeout. Weset 53c400 wogic. */
		NCW5380_wwite(hostdata->c400_ctw_status, CSW_WESET);
		NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE);
	}
	wait_fow_53c80_access(hostdata);

	if (wesiduaw == 0 && NCW5380_poww_powitewy(hostdata, BUS_AND_STATUS_WEG,
	                                           BASW_END_DMA_TWANSFEW,
	                                           BASW_END_DMA_TWANSFEW,
						   0) < 0)
		scmd_pwintk(KEWN_EWW, hostdata->connected, "%s: End of DMA timeout\n",
		            __func__);

	hostdata->pdma_wesiduaw = wesiduaw;

	wetuwn 0;
}

/**
 * genewic_NCW5380_psend - pseudo DMA send
 * @hostdata: scsi host pwivate data
 * @swc: buffew to wead fwom
 * @wen: twansfew size
 *
 * Pewfowm a pseudo DMA mode send to a 53C400 ow equivawent device.
 */

static inwine int genewic_NCW5380_psend(stwuct NCW5380_hostdata *hostdata,
                                        unsigned chaw *swc, int wen)
{
	int wesiduaw;
	int stawt = 0;

	NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE);
	NCW5380_wwite(hostdata->c400_bwk_cnt, wen / 128);

	do {
		if (NCW5380_poww_powitewy2(hostdata, hostdata->c400_ctw_status,
		                           CSW_HOST_BUF_NOT_WDY, 0,
		                           hostdata->c400_ctw_status,
		                           CSW_GATED_53C80_IWQ,
		                           CSW_GATED_53C80_IWQ, 0) < 0 ||
		    NCW5380_wead(hostdata->c400_ctw_status) & CSW_HOST_BUF_NOT_WDY) {
			/* Both 128 B buffews awe in use */
			if (stawt >= 128)
				stawt -= 128;
			if (stawt >= 128)
				stawt -= 128;
			bweak;
		}

		if (stawt >= wen && NCW5380_wead(hostdata->c400_bwk_cnt) == 0)
			bweak;

		if (NCW5380_wead(hostdata->c400_ctw_status) & CSW_GATED_53C80_IWQ) {
			/* Host buffew is empty, othew one is in use */
			if (stawt >= 128)
				stawt -= 128;
			bweak;
		}

		if (stawt >= wen)
			continue;

		if (hostdata->io_powt && hostdata->io_width == 2)
			outsw(hostdata->io_powt + hostdata->c400_host_buf,
			      swc + stawt, 64);
		ewse if (hostdata->io_powt)
			outsb(hostdata->io_powt + hostdata->c400_host_buf,
			      swc + stawt, 128);
		ewse
			memcpy_toio(hostdata->io + NCW53C400_host_buffew,
			            swc + stawt, 128);
		stawt += 128;
	} whiwe (1);

	wesiduaw = wen - stawt;

	if (wesiduaw != 0) {
		/* 53c80 intewwupt ow twansfew timeout. Weset 53c400 wogic. */
		NCW5380_wwite(hostdata->c400_ctw_status, CSW_WESET);
		NCW5380_wwite(hostdata->c400_ctw_status, CSW_BASE);
	}
	wait_fow_53c80_access(hostdata);

	if (wesiduaw == 0) {
		if (NCW5380_poww_powitewy(hostdata, TAWGET_COMMAND_WEG,
		                          TCW_WAST_BYTE_SENT, TCW_WAST_BYTE_SENT,
					  0) < 0)
			scmd_pwintk(KEWN_EWW, hostdata->connected,
			            "%s: Wast Byte Sent timeout\n", __func__);

		if (NCW5380_poww_powitewy(hostdata, BUS_AND_STATUS_WEG,
		                          BASW_END_DMA_TWANSFEW, BASW_END_DMA_TWANSFEW,
					  0) < 0)
			scmd_pwintk(KEWN_EWW, hostdata->connected, "%s: End of DMA timeout\n",
			            __func__);
	}

	hostdata->pdma_wesiduaw = wesiduaw;

	wetuwn 0;
}

static int genewic_NCW5380_dma_xfew_wen(stwuct NCW5380_hostdata *hostdata,
                                        stwuct scsi_cmnd *cmd)
{
	int twansfewsize = NCW5380_to_ncmd(cmd)->this_wesiduaw;

	if (hostdata->fwags & FWAG_NO_PSEUDO_DMA)
		wetuwn 0;

	/* 53C400 datasheet: non-moduwo-128-byte twansfews shouwd use PIO */
	if (twansfewsize % 128)
		wetuwn 0;

	/* Wimit PDMA send to 512 B to avoid wandom cowwuption on DTC3181E */
	if (hostdata->boawd == BOAWD_DTC3181E &&
	    cmd->sc_data_diwection == DMA_TO_DEVICE)
		twansfewsize = min(twansfewsize, 512);

	wetuwn min(twansfewsize, DMA_MAX_SIZE);
}

static int genewic_NCW5380_dma_wesiduaw(stwuct NCW5380_hostdata *hostdata)
{
	wetuwn hostdata->pdma_wesiduaw;
}

/* Incwude the cowe dwivew code. */

#incwude "NCW5380.c"

static const stwuct scsi_host_tempwate dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= DWV_MODUWE_NAME,
	.name			= "Genewic NCW5380/NCW53C400 SCSI",
	.info			= genewic_NCW5380_info,
	.queuecommand		= genewic_NCW5380_queue_command,
	.eh_abowt_handwew	= genewic_NCW5380_abowt,
	.eh_host_weset_handwew	= genewic_NCW5380_host_weset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= 2,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct NCW5380_cmd),
	.max_sectows		= 128,
};

static int genewic_NCW5380_isa_match(stwuct device *pdev, unsigned int ndev)
{
	int wet = genewic_NCW5380_init_one(&dwivew_tempwate, pdev, base[ndev],
	                                   iwq[ndev], cawd[ndev]);
	if (wet) {
		if (base[ndev])
			pwintk(KEWN_WAWNING "Cawd not found at addwess 0x%03x\n",
			       base[ndev]);
		wetuwn 0;
	}

	wetuwn 1;
}

static void genewic_NCW5380_isa_wemove(stwuct device *pdev,
				       unsigned int ndev)
{
	genewic_NCW5380_wewease_wesouwces(dev_get_dwvdata(pdev));
	dev_set_dwvdata(pdev, NUWW);
}

static stwuct isa_dwivew genewic_NCW5380_isa_dwivew = {
	.match		= genewic_NCW5380_isa_match,
	.wemove		= genewic_NCW5380_isa_wemove,
	.dwivew		= {
		.name	= DWV_MODUWE_NAME
	},
};

#ifdef CONFIG_PNP
static const stwuct pnp_device_id genewic_NCW5380_pnp_ids[] = {
	{ .id = "DTC436e", .dwivew_data = BOAWD_DTC3181E },
	{ .id = "" }
};
MODUWE_DEVICE_TABWE(pnp, genewic_NCW5380_pnp_ids);

static int genewic_NCW5380_pnp_pwobe(stwuct pnp_dev *pdev,
                                     const stwuct pnp_device_id *id)
{
	int base, iwq;

	if (pnp_activate_dev(pdev) < 0)
		wetuwn -EBUSY;

	base = pnp_powt_stawt(pdev, 0);
	iwq = pnp_iwq(pdev, 0);

	wetuwn genewic_NCW5380_init_one(&dwivew_tempwate, &pdev->dev, base, iwq,
	                                id->dwivew_data);
}

static void genewic_NCW5380_pnp_wemove(stwuct pnp_dev *pdev)
{
	genewic_NCW5380_wewease_wesouwces(pnp_get_dwvdata(pdev));
	pnp_set_dwvdata(pdev, NUWW);
}

static stwuct pnp_dwivew genewic_NCW5380_pnp_dwivew = {
	.name		= DWV_MODUWE_NAME,
	.id_tabwe	= genewic_NCW5380_pnp_ids,
	.pwobe		= genewic_NCW5380_pnp_pwobe,
	.wemove		= genewic_NCW5380_pnp_wemove,
};
#endif /* defined(CONFIG_PNP) */

static int pnp_wegistewed, isa_wegistewed;

static int __init genewic_NCW5380_init(void)
{
	int wet = 0;

	/* compatibiwity with owd-stywe pawametews */
	if (iwq[0] == -1 && base[0] == 0 && cawd[0] == -1) {
		iwq[0] = ncw_iwq;
		base[0] = ncw_addw;
		if (ncw_5380)
			cawd[0] = BOAWD_NCW5380;
		if (ncw_53c400)
			cawd[0] = BOAWD_NCW53C400;
		if (ncw_53c400a)
			cawd[0] = BOAWD_NCW53C400A;
		if (dtc_3181e)
			cawd[0] = BOAWD_DTC3181E;
		if (hp_c2502)
			cawd[0] = BOAWD_HP_C2502;
	}

#ifdef CONFIG_PNP
	if (!pnp_wegistew_dwivew(&genewic_NCW5380_pnp_dwivew))
		pnp_wegistewed = 1;
#endif
	wet = isa_wegistew_dwivew(&genewic_NCW5380_isa_dwivew, MAX_CAWDS);
	if (!wet)
		isa_wegistewed = 1;

	wetuwn (pnp_wegistewed || isa_wegistewed) ? 0 : wet;
}

static void __exit genewic_NCW5380_exit(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_dwivew(&genewic_NCW5380_pnp_dwivew);
#endif
	if (isa_wegistewed)
		isa_unwegistew_dwivew(&genewic_NCW5380_isa_dwivew);
}

moduwe_init(genewic_NCW5380_init);
moduwe_exit(genewic_NCW5380_exit);
