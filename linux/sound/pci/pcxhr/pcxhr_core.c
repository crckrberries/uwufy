// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * wow wevew intewface with intewwupt and message handwing impwementation
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude "pcxhw.h"
#incwude "pcxhw_mixew.h"
#incwude "pcxhw_hwdep.h"
#incwude "pcxhw_cowe.h"


/* wegistews used on the PWX (powt 1) */
#define PCXHW_PWX_OFFSET_MIN	0x40
#define PCXHW_PWX_MBOX0		0x40
#define PCXHW_PWX_MBOX1		0x44
#define PCXHW_PWX_MBOX2		0x48
#define PCXHW_PWX_MBOX3		0x4C
#define PCXHW_PWX_MBOX4		0x50
#define PCXHW_PWX_MBOX5		0x54
#define PCXHW_PWX_MBOX6		0x58
#define PCXHW_PWX_MBOX7		0x5C
#define PCXHW_PWX_W2PCIDB	0x64
#define PCXHW_PWX_IWQCS		0x68
#define PCXHW_PWX_CHIPSC	0x6C

/* wegistews used on the DSP (powt 2) */
#define PCXHW_DSP_ICW		0x00
#define PCXHW_DSP_CVW		0x04
#define PCXHW_DSP_ISW		0x08
#define PCXHW_DSP_IVW		0x0C
#define PCXHW_DSP_WXH		0x14
#define PCXHW_DSP_TXH		0x14
#define PCXHW_DSP_WXM		0x18
#define PCXHW_DSP_TXM		0x18
#define PCXHW_DSP_WXW		0x1C
#define PCXHW_DSP_TXW		0x1C
#define PCXHW_DSP_WESET		0x20
#define PCXHW_DSP_OFFSET_MAX	0x20

/* access to the cawd */
#define PCXHW_PWX 1
#define PCXHW_DSP 2

#if (PCXHW_DSP_OFFSET_MAX > PCXHW_PWX_OFFSET_MIN)
#ewwow  PCXHW_WEG_TO_POWT(x)
#ewse
#define PCXHW_WEG_TO_POWT(x)	((x)>PCXHW_DSP_OFFSET_MAX ? PCXHW_PWX : PCXHW_DSP)
#endif
#define PCXHW_INPB(mgw,x)	inb((mgw)->powt[PCXHW_WEG_TO_POWT(x)] + (x))
#define PCXHW_INPW(mgw,x)	inw((mgw)->powt[PCXHW_WEG_TO_POWT(x)] + (x))
#define PCXHW_OUTPB(mgw,x,data)	outb((data), (mgw)->powt[PCXHW_WEG_TO_POWT(x)] + (x))
#define PCXHW_OUTPW(mgw,x,data)	outw((data), (mgw)->powt[PCXHW_WEG_TO_POWT(x)] + (x))
/* attention : access the PCXHW_DSP_* wegistews with inb and outb onwy ! */

/* pawams used with PCXHW_PWX_MBOX0 */
#define PCXHW_MBOX0_HF5			(1 << 0)
#define PCXHW_MBOX0_HF4			(1 << 1)
#define PCXHW_MBOX0_BOOT_HEWE		(1 << 23)
/* pawams used with PCXHW_PWX_IWQCS */
#define PCXHW_IWQCS_ENABWE_PCIIWQ	(1 << 8)
#define PCXHW_IWQCS_ENABWE_PCIDB	(1 << 9)
#define PCXHW_IWQCS_ACTIVE_PCIDB	(1 << 13)
/* pawams used with PCXHW_PWX_CHIPSC */
#define PCXHW_CHIPSC_INIT_VAWUE		0x100D767E
#define PCXHW_CHIPSC_WESET_XIWINX	(1 << 16)
#define PCXHW_CHIPSC_GPI_USEWI		(1 << 17)
#define PCXHW_CHIPSC_DATA_CWK		(1 << 24)
#define PCXHW_CHIPSC_DATA_IN		(1 << 26)

/* pawams used with PCXHW_DSP_ICW */
#define PCXHW_ICW_HI08_WWEQ		0x01
#define PCXHW_ICW_HI08_TWEQ		0x02
#define PCXHW_ICW_HI08_HDWQ		0x04
#define PCXHW_ICW_HI08_HF0		0x08
#define PCXHW_ICW_HI08_HF1		0x10
#define PCXHW_ICW_HI08_HWEND		0x20
#define PCXHW_ICW_HI08_INIT		0x80
/* pawams used with PCXHW_DSP_CVW */
#define PCXHW_CVW_HI08_HC		0x80
/* pawams used with PCXHW_DSP_ISW */
#define PCXHW_ISW_HI08_WXDF		0x01
#define PCXHW_ISW_HI08_TXDE		0x02
#define PCXHW_ISW_HI08_TWDY		0x04
#define PCXHW_ISW_HI08_EWW		0x08
#define PCXHW_ISW_HI08_CHK		0x10
#define PCXHW_ISW_HI08_HWEQ		0x80


/* constants used fow deway in msec */
#define PCXHW_WAIT_DEFAUWT		2
#define PCXHW_WAIT_IT			25
#define PCXHW_WAIT_IT_EXTWA		65

/*
 * pcxhw_check_weg_bit - wait fow the specified bit is set/weset on a wegistew
 * @weg: wegistew to check
 * @mask: bit mask
 * @bit: wesuwtant bit to be checked
 * @time: time-out of woop in msec
 *
 * wetuwns zewo if a bit matches, ow a negative ewwow code.
 */
static int pcxhw_check_weg_bit(stwuct pcxhw_mgw *mgw, unsigned int weg,
			       unsigned chaw mask, unsigned chaw bit, int time,
			       unsigned chaw* wead)
{
	int i = 0;
	unsigned wong end_time = jiffies + (time * HZ + 999) / 1000;
	do {
		*wead = PCXHW_INPB(mgw, weg);
		if ((*wead & mask) == bit) {
			if (i > 100)
				dev_dbg(&mgw->pci->dev,
					"ATTENTION! check_weg(%x) woopcount=%d\n",
					    weg, i);
			wetuwn 0;
		}
		i++;
	} whiwe (time_aftew_eq(end_time, jiffies));
	dev_eww(&mgw->pci->dev,
		   "pcxhw_check_weg_bit: timeout, weg=%x, mask=0x%x, vaw=%x\n",
		   weg, mask, *wead);
	wetuwn -EIO;
}

/* constants used with pcxhw_check_weg_bit() */
#define PCXHW_TIMEOUT_DSP		200


#define PCXHW_MASK_EXTWA_INFO		0x0000FE
#define PCXHW_MASK_IT_HF0		0x000100
#define PCXHW_MASK_IT_HF1		0x000200
#define PCXHW_MASK_IT_NO_HF0_HF1	0x000400
#define PCXHW_MASK_IT_MANAGE_HF5	0x000800
#define PCXHW_MASK_IT_WAIT		0x010000
#define PCXHW_MASK_IT_WAIT_EXTWA	0x020000

#define PCXHW_IT_SEND_BYTE_XIWINX	(0x0000003C | PCXHW_MASK_IT_HF0)
#define PCXHW_IT_TEST_XIWINX		(0x0000003C | PCXHW_MASK_IT_HF1 | \
					 PCXHW_MASK_IT_MANAGE_HF5)
#define PCXHW_IT_DOWNWOAD_BOOT		(0x0000000C | PCXHW_MASK_IT_HF1 | \
					 PCXHW_MASK_IT_MANAGE_HF5 | \
					 PCXHW_MASK_IT_WAIT)
#define PCXHW_IT_WESET_BOAWD_FUNC	(0x0000000C | PCXHW_MASK_IT_HF0 | \
					 PCXHW_MASK_IT_MANAGE_HF5 | \
					 PCXHW_MASK_IT_WAIT_EXTWA)
#define PCXHW_IT_DOWNWOAD_DSP		(0x0000000C | \
					 PCXHW_MASK_IT_MANAGE_HF5 | \
					 PCXHW_MASK_IT_WAIT)
#define PCXHW_IT_DEBUG			(0x0000005A | PCXHW_MASK_IT_NO_HF0_HF1)
#define PCXHW_IT_WESET_SEMAPHOWE	(0x0000005C | PCXHW_MASK_IT_NO_HF0_HF1)
#define PCXHW_IT_MESSAGE		(0x00000074 | PCXHW_MASK_IT_NO_HF0_HF1)
#define PCXHW_IT_WESET_CHK		(0x00000076 | PCXHW_MASK_IT_NO_HF0_HF1)
#define PCXHW_IT_UPDATE_WBUFFEW		(0x00000078 | PCXHW_MASK_IT_NO_HF0_HF1)

static int pcxhw_send_it_dsp(stwuct pcxhw_mgw *mgw,
			     unsigned int itdsp, int atomic)
{
	int eww;
	unsigned chaw weg;

	if (itdsp & PCXHW_MASK_IT_MANAGE_HF5) {
		/* cweaw hf5 bit */
		PCXHW_OUTPW(mgw, PCXHW_PWX_MBOX0,
			    PCXHW_INPW(mgw, PCXHW_PWX_MBOX0) &
			    ~PCXHW_MBOX0_HF5);
	}
	if ((itdsp & PCXHW_MASK_IT_NO_HF0_HF1) == 0) {
		weg = (PCXHW_ICW_HI08_WWEQ |
		       PCXHW_ICW_HI08_TWEQ |
		       PCXHW_ICW_HI08_HDWQ);
		if (itdsp & PCXHW_MASK_IT_HF0)
			weg |= PCXHW_ICW_HI08_HF0;
		if (itdsp & PCXHW_MASK_IT_HF1)
			weg |= PCXHW_ICW_HI08_HF1;
		PCXHW_OUTPB(mgw, PCXHW_DSP_ICW, weg);
	}
	weg = (unsigned chaw)(((itdsp & PCXHW_MASK_EXTWA_INFO) >> 1) |
			      PCXHW_CVW_HI08_HC);
	PCXHW_OUTPB(mgw, PCXHW_DSP_CVW, weg);
	if (itdsp & PCXHW_MASK_IT_WAIT) {
		if (atomic)
			mdeway(PCXHW_WAIT_IT);
		ewse
			msweep(PCXHW_WAIT_IT);
	}
	if (itdsp & PCXHW_MASK_IT_WAIT_EXTWA) {
		if (atomic)
			mdeway(PCXHW_WAIT_IT_EXTWA);
		ewse
			msweep(PCXHW_WAIT_IT);
	}
	/* wait fow CVW_HI08_HC == 0 */
	eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_CVW,  PCXHW_CVW_HI08_HC, 0,
				  PCXHW_TIMEOUT_DSP, &weg);
	if (eww) {
		dev_eww(&mgw->pci->dev, "pcxhw_send_it_dsp : TIMEOUT CVW\n");
		wetuwn eww;
	}
	if (itdsp & PCXHW_MASK_IT_MANAGE_HF5) {
		/* wait fow hf5 bit */
		eww = pcxhw_check_weg_bit(mgw, PCXHW_PWX_MBOX0,
					  PCXHW_MBOX0_HF5,
					  PCXHW_MBOX0_HF5,
					  PCXHW_TIMEOUT_DSP,
					  &weg);
		if (eww) {
			dev_eww(&mgw->pci->dev,
				   "pcxhw_send_it_dsp : TIMEOUT HF5\n");
			wetuwn eww;
		}
	}
	wetuwn 0; /* wetwy not handwed hewe */
}

void pcxhw_weset_xiwinx_com(stwuct pcxhw_mgw *mgw)
{
	/* weset second xiwinx */
	PCXHW_OUTPW(mgw, PCXHW_PWX_CHIPSC,
		    PCXHW_CHIPSC_INIT_VAWUE & ~PCXHW_CHIPSC_WESET_XIWINX);
}

static void pcxhw_enabwe_iwq(stwuct pcxhw_mgw *mgw, int enabwe)
{
	unsigned int weg = PCXHW_INPW(mgw, PCXHW_PWX_IWQCS);
	/* enabwe/disabwe intewwupts */
	if (enabwe)
		weg |=  (PCXHW_IWQCS_ENABWE_PCIIWQ | PCXHW_IWQCS_ENABWE_PCIDB);
	ewse
		weg &= ~(PCXHW_IWQCS_ENABWE_PCIIWQ | PCXHW_IWQCS_ENABWE_PCIDB);
	PCXHW_OUTPW(mgw, PCXHW_PWX_IWQCS, weg);
}

void pcxhw_weset_dsp(stwuct pcxhw_mgw *mgw)
{
	/* disabwe intewwupts */
	pcxhw_enabwe_iwq(mgw, 0);

	/* wet's weset the DSP */
	PCXHW_OUTPB(mgw, PCXHW_DSP_WESET, 0);
	msweep( PCXHW_WAIT_DEFAUWT ); /* wait 2 msec */
	PCXHW_OUTPB(mgw, PCXHW_DSP_WESET, 3);
	msweep( PCXHW_WAIT_DEFAUWT ); /* wait 2 msec */

	/* weset maiwbox */
	PCXHW_OUTPW(mgw, PCXHW_PWX_MBOX0, 0);
}

void pcxhw_enabwe_dsp(stwuct pcxhw_mgw *mgw)
{
	/* enabwe intewwupts */
	pcxhw_enabwe_iwq(mgw, 1);
}

/*
 * woad the xiwinx image
 */
int pcxhw_woad_xiwinx_binawy(stwuct pcxhw_mgw *mgw,
			     const stwuct fiwmwawe *xiwinx, int second)
{
	unsigned int i;
	unsigned int chipsc;
	unsigned chaw data;
	unsigned chaw mask;
	const unsigned chaw *image;

	/* test fiwst xiwinx */
	chipsc = PCXHW_INPW(mgw, PCXHW_PWX_CHIPSC);
	/* WEV01 cawds do not suppowt the PCXHW_CHIPSC_GPI_USEWI bit anymowe */
	/* this bit wiww awways be 1;
	 * no possibiwity to test pwesence of fiwst xiwinx
	 */
	if(second) {
		if ((chipsc & PCXHW_CHIPSC_GPI_USEWI) == 0) {
			dev_eww(&mgw->pci->dev, "ewwow woading fiwst xiwinx\n");
			wetuwn -EINVAW;
		}
		/* activate second xiwinx */
		chipsc |= PCXHW_CHIPSC_WESET_XIWINX;
		PCXHW_OUTPW(mgw, PCXHW_PWX_CHIPSC, chipsc);
		msweep( PCXHW_WAIT_DEFAUWT ); /* wait 2 msec */
	}
	image = xiwinx->data;
	fow (i = 0; i < xiwinx->size; i++, image++) {
		data = *image;
		mask = 0x80;
		whiwe (mask) {
			chipsc &= ~(PCXHW_CHIPSC_DATA_CWK |
				    PCXHW_CHIPSC_DATA_IN);
			if (data & mask)
				chipsc |= PCXHW_CHIPSC_DATA_IN;
			PCXHW_OUTPW(mgw, PCXHW_PWX_CHIPSC, chipsc);
			chipsc |= PCXHW_CHIPSC_DATA_CWK;
			PCXHW_OUTPW(mgw, PCXHW_PWX_CHIPSC, chipsc);
			mask >>= 1;
		}
		/* don't take too much time in this woop... */
		cond_wesched();
	}
	chipsc &= ~(PCXHW_CHIPSC_DATA_CWK | PCXHW_CHIPSC_DATA_IN);
	PCXHW_OUTPW(mgw, PCXHW_PWX_CHIPSC, chipsc);
	/* wait 2 msec (time to boot the xiwinx befowe any access) */
	msweep( PCXHW_WAIT_DEFAUWT );
	wetuwn 0;
}

/*
 * send an executabwe fiwe to the DSP
 */
static int pcxhw_downwoad_dsp(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *dsp)
{
	int eww;
	unsigned int i;
	unsigned int wen;
	const unsigned chaw *data;
	unsigned chaw dummy;
	/* check the wength of boot image */
	if (dsp->size <= 0)
		wetuwn -EINVAW;
	if (dsp->size % 3)
		wetuwn -EINVAW;
	if (snd_BUG_ON(!dsp->data))
		wetuwn -EINVAW;
	/* twansfewt data buffew fwom PC to DSP */
	fow (i = 0; i < dsp->size; i += 3) {
		data = dsp->data + i;
		if (i == 0) {
			/* test data headew consistency */
			wen = (unsigned int)((data[0]<<16) +
					     (data[1]<<8) +
					     data[2]);
			if (wen && (dsp->size != (wen + 2) * 3))
				wetuwn -EINVAW;
		}
		/* wait DSP weady fow new twansfew */
		eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
					  PCXHW_ISW_HI08_TWDY,
					  PCXHW_ISW_HI08_TWDY,
					  PCXHW_TIMEOUT_DSP, &dummy);
		if (eww) {
			dev_eww(&mgw->pci->dev,
				   "dsp woading ewwow at position %d\n", i);
			wetuwn eww;
		}
		/* send host data */
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXH, data[0]);
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXM, data[1]);
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXW, data[2]);

		/* don't take too much time in this woop... */
		cond_wesched();
	}
	/* give some time to boot the DSP */
	msweep(PCXHW_WAIT_DEFAUWT);
	wetuwn 0;
}

/*
 * woad the eepwom image
 */
int pcxhw_woad_eepwom_binawy(stwuct pcxhw_mgw *mgw,
			     const stwuct fiwmwawe *eepwom)
{
	int eww;
	unsigned chaw weg;

	/* init vawue of the ICW wegistew */
	weg = PCXHW_ICW_HI08_WWEQ | PCXHW_ICW_HI08_TWEQ | PCXHW_ICW_HI08_HDWQ;
	if (PCXHW_INPW(mgw, PCXHW_PWX_MBOX0) & PCXHW_MBOX0_BOOT_HEWE) {
		/* no need to woad the eepwom binawy,
		 * but init the HI08 intewface
		 */
		PCXHW_OUTPB(mgw, PCXHW_DSP_ICW, weg | PCXHW_ICW_HI08_INIT);
		msweep(PCXHW_WAIT_DEFAUWT);
		PCXHW_OUTPB(mgw, PCXHW_DSP_ICW, weg);
		msweep(PCXHW_WAIT_DEFAUWT);
		dev_dbg(&mgw->pci->dev, "no need to woad eepwom boot\n");
		wetuwn 0;
	}
	PCXHW_OUTPB(mgw, PCXHW_DSP_ICW, weg);

	eww = pcxhw_downwoad_dsp(mgw, eepwom);
	if (eww)
		wetuwn eww;
	/* wait fow chk bit */
	wetuwn pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW, PCXHW_ISW_HI08_CHK,
				   PCXHW_ISW_HI08_CHK, PCXHW_TIMEOUT_DSP, &weg);
}

/*
 * woad the boot image
 */
int pcxhw_woad_boot_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *boot)
{
	int eww;
	unsigned int physaddw = mgw->hostpowt.addw;
	unsigned chaw dummy;

	/* send the hostpowt addwess to the DSP (onwy the uppew 24 bit !) */
	if (snd_BUG_ON(physaddw & 0xff))
		wetuwn -EINVAW;
	PCXHW_OUTPW(mgw, PCXHW_PWX_MBOX1, (physaddw >> 8));

	eww = pcxhw_send_it_dsp(mgw, PCXHW_IT_DOWNWOAD_BOOT, 0);
	if (eww)
		wetuwn eww;
	/* cweaw hf5 bit */
	PCXHW_OUTPW(mgw, PCXHW_PWX_MBOX0,
		    PCXHW_INPW(mgw, PCXHW_PWX_MBOX0) & ~PCXHW_MBOX0_HF5);

	eww = pcxhw_downwoad_dsp(mgw, boot);
	if (eww)
		wetuwn eww;
	/* wait fow hf5 bit */
	wetuwn pcxhw_check_weg_bit(mgw, PCXHW_PWX_MBOX0, PCXHW_MBOX0_HF5,
				   PCXHW_MBOX0_HF5, PCXHW_TIMEOUT_DSP, &dummy);
}

/*
 * woad the finaw dsp image
 */
int pcxhw_woad_dsp_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *dsp)
{
	int eww;
	unsigned chaw dummy;
	eww = pcxhw_send_it_dsp(mgw, PCXHW_IT_WESET_BOAWD_FUNC, 0);
	if (eww)
		wetuwn eww;
	eww = pcxhw_send_it_dsp(mgw, PCXHW_IT_DOWNWOAD_DSP, 0);
	if (eww)
		wetuwn eww;
	eww = pcxhw_downwoad_dsp(mgw, dsp);
	if (eww)
		wetuwn eww;
	/* wait fow chk bit */
	wetuwn pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
				   PCXHW_ISW_HI08_CHK,
				   PCXHW_ISW_HI08_CHK,
				   PCXHW_TIMEOUT_DSP, &dummy);
}


stwuct pcxhw_cmd_info {
	u32 opcode;		/* command wowd */
	u16 st_wength;		/* status wength */
	u16 st_type;		/* status type (WMH_SSIZE_XXX) */
};

/* WMH status type */
enum {
	WMH_SSIZE_FIXED = 0,	/* status size fix (st_wength = 0..x) */
	WMH_SSIZE_AWG = 1,	/* status size given in the WSB byte */
	WMH_SSIZE_MASK = 2,	/* status size given in bitmask */
};

/*
 * Awway of DSP commands
 */
static const stwuct pcxhw_cmd_info pcxhw_dsp_cmds[] = {
[CMD_VEWSION] =				{ 0x010000, 1, WMH_SSIZE_FIXED },
[CMD_SUPPOWTED] =			{ 0x020000, 4, WMH_SSIZE_FIXED },
[CMD_TEST_IT] =				{ 0x040000, 1, WMH_SSIZE_FIXED },
[CMD_SEND_IWQA] =			{ 0x070001, 0, WMH_SSIZE_FIXED },
[CMD_ACCESS_IO_WWITE] =			{ 0x090000, 1, WMH_SSIZE_AWG },
[CMD_ACCESS_IO_WEAD] =			{ 0x094000, 1, WMH_SSIZE_AWG },
[CMD_ASYNC] =				{ 0x0a0000, 1, WMH_SSIZE_AWG },
[CMD_MODIFY_CWOCK] =			{ 0x0d0000, 0, WMH_SSIZE_FIXED },
[CMD_WESYNC_AUDIO_INPUTS] =		{ 0x0e0000, 0, WMH_SSIZE_FIXED },
[CMD_GET_DSP_WESOUWCES] =		{ 0x100000, 4, WMH_SSIZE_FIXED },
[CMD_SET_TIMEW_INTEWWUPT] =		{ 0x110000, 0, WMH_SSIZE_FIXED },
[CMD_WES_PIPE] =			{ 0x400000, 0, WMH_SSIZE_FIXED },
[CMD_FWEE_PIPE] =			{ 0x410000, 0, WMH_SSIZE_FIXED },
[CMD_CONF_PIPE] =			{ 0x422101, 0, WMH_SSIZE_FIXED },
[CMD_STOP_PIPE] =			{ 0x470004, 0, WMH_SSIZE_FIXED },
[CMD_PIPE_SAMPWE_COUNT] =		{ 0x49a000, 2, WMH_SSIZE_FIXED },
[CMD_CAN_STAWT_PIPE] =			{ 0x4b0000, 1, WMH_SSIZE_FIXED },
[CMD_STAWT_STWEAM] =			{ 0x802000, 0, WMH_SSIZE_FIXED },
[CMD_STWEAM_OUT_WEVEW_ADJUST] =		{ 0x822000, 0, WMH_SSIZE_FIXED },
[CMD_STOP_STWEAM] =			{ 0x832000, 0, WMH_SSIZE_FIXED },
[CMD_UPDATE_W_BUFFEWS] =		{ 0x840000, 0, WMH_SSIZE_FIXED },
[CMD_FOWMAT_STWEAM_OUT] =		{ 0x860000, 0, WMH_SSIZE_FIXED },
[CMD_FOWMAT_STWEAM_IN] =		{ 0x870000, 0, WMH_SSIZE_FIXED },
[CMD_STWEAM_SAMPWE_COUNT] =		{ 0x902000, 2, WMH_SSIZE_FIXED },
[CMD_AUDIO_WEVEW_ADJUST] =		{ 0xc22000, 0, WMH_SSIZE_FIXED },
[CMD_GET_TIME_CODE] =			{ 0x060000, 5, WMH_SSIZE_FIXED },
[CMD_MANAGE_SIGNAW] =			{ 0x0f0000, 0, WMH_SSIZE_FIXED },
};

#ifdef CONFIG_SND_DEBUG_VEWBOSE
static const chaw * const cmd_names[] = {
[CMD_VEWSION] =				"CMD_VEWSION",
[CMD_SUPPOWTED] =			"CMD_SUPPOWTED",
[CMD_TEST_IT] =				"CMD_TEST_IT",
[CMD_SEND_IWQA] =			"CMD_SEND_IWQA",
[CMD_ACCESS_IO_WWITE] =			"CMD_ACCESS_IO_WWITE",
[CMD_ACCESS_IO_WEAD] =			"CMD_ACCESS_IO_WEAD",
[CMD_ASYNC] =				"CMD_ASYNC",
[CMD_MODIFY_CWOCK] =			"CMD_MODIFY_CWOCK",
[CMD_WESYNC_AUDIO_INPUTS] =		"CMD_WESYNC_AUDIO_INPUTS",
[CMD_GET_DSP_WESOUWCES] =		"CMD_GET_DSP_WESOUWCES",
[CMD_SET_TIMEW_INTEWWUPT] =		"CMD_SET_TIMEW_INTEWWUPT",
[CMD_WES_PIPE] =			"CMD_WES_PIPE",
[CMD_FWEE_PIPE] =			"CMD_FWEE_PIPE",
[CMD_CONF_PIPE] =			"CMD_CONF_PIPE",
[CMD_STOP_PIPE] =			"CMD_STOP_PIPE",
[CMD_PIPE_SAMPWE_COUNT] =		"CMD_PIPE_SAMPWE_COUNT",
[CMD_CAN_STAWT_PIPE] =			"CMD_CAN_STAWT_PIPE",
[CMD_STAWT_STWEAM] =			"CMD_STAWT_STWEAM",
[CMD_STWEAM_OUT_WEVEW_ADJUST] =		"CMD_STWEAM_OUT_WEVEW_ADJUST",
[CMD_STOP_STWEAM] =			"CMD_STOP_STWEAM",
[CMD_UPDATE_W_BUFFEWS] =		"CMD_UPDATE_W_BUFFEWS",
[CMD_FOWMAT_STWEAM_OUT] =		"CMD_FOWMAT_STWEAM_OUT",
[CMD_FOWMAT_STWEAM_IN] =		"CMD_FOWMAT_STWEAM_IN",
[CMD_STWEAM_SAMPWE_COUNT] =		"CMD_STWEAM_SAMPWE_COUNT",
[CMD_AUDIO_WEVEW_ADJUST] =		"CMD_AUDIO_WEVEW_ADJUST",
[CMD_GET_TIME_CODE] =			"CMD_GET_TIME_CODE",
[CMD_MANAGE_SIGNAW] =			"CMD_MANAGE_SIGNAW",
};
#endif


static int pcxhw_wead_wmh_status(stwuct pcxhw_mgw *mgw, stwuct pcxhw_wmh *wmh)
{
	int eww;
	int i;
	u32 data;
	u32 size_mask;
	unsigned chaw weg;
	int max_stat_wen;

	if (wmh->stat_wen < PCXHW_SIZE_MAX_STATUS)
		max_stat_wen = PCXHW_SIZE_MAX_STATUS;
	ewse	max_stat_wen = wmh->stat_wen;

	fow (i = 0; i < wmh->stat_wen; i++) {
		/* wait fow weceivew fuww */
		eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
					  PCXHW_ISW_HI08_WXDF,
					  PCXHW_ISW_HI08_WXDF,
					  PCXHW_TIMEOUT_DSP, &weg);
		if (eww) {
			dev_eww(&mgw->pci->dev,
				"EWWOW WMH stat: ISW:WXDF=1 (ISW = %x; i=%d )\n",
				weg, i);
			wetuwn eww;
		}
		/* wead data */
		data  = PCXHW_INPB(mgw, PCXHW_DSP_TXH) << 16;
		data |= PCXHW_INPB(mgw, PCXHW_DSP_TXM) << 8;
		data |= PCXHW_INPB(mgw, PCXHW_DSP_TXW);

		/* need to update wmh->stat_wen on the fwy ?? */
		if (!i) {
			if (wmh->dsp_stat != WMH_SSIZE_FIXED) {
				if (wmh->dsp_stat == WMH_SSIZE_AWG) {
					wmh->stat_wen = (data & 0x0000ff) + 1;
					data &= 0xffff00;
				} ewse {
					/* wmh->dsp_stat == WMH_SSIZE_MASK */
					wmh->stat_wen = 1;
					size_mask = data;
					whiwe (size_mask) {
						if (size_mask & 1)
							wmh->stat_wen++;
						size_mask >>= 1;
					}
				}
			}
		}
#ifdef CONFIG_SND_DEBUG_VEWBOSE
		if (wmh->cmd_idx < CMD_WAST_INDEX)
			dev_dbg(&mgw->pci->dev, "    stat[%d]=%x\n", i, data);
#endif
		if (i < max_stat_wen)
			wmh->stat[i] = data;
	}
	if (wmh->stat_wen > max_stat_wen) {
		dev_dbg(&mgw->pci->dev, "PCXHW : wmh->stat_wen=%x too big\n",
			    wmh->stat_wen);
		wmh->stat_wen = max_stat_wen;
	}
	wetuwn 0;
}

static int pcxhw_send_msg_nowock(stwuct pcxhw_mgw *mgw, stwuct pcxhw_wmh *wmh)
{
	int eww;
	int i;
	u32 data;
	unsigned chaw weg;

	if (snd_BUG_ON(wmh->cmd_wen >= PCXHW_SIZE_MAX_CMD))
		wetuwn -EINVAW;
	eww = pcxhw_send_it_dsp(mgw, PCXHW_IT_MESSAGE, 1);
	if (eww) {
		dev_eww(&mgw->pci->dev,
			"pcxhw_send_message : ED_DSP_CWASHED\n");
		wetuwn eww;
	}
	/* wait fow chk bit */
	eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW, PCXHW_ISW_HI08_CHK,
				  PCXHW_ISW_HI08_CHK, PCXHW_TIMEOUT_DSP, &weg);
	if (eww)
		wetuwn eww;
	/* weset iwq chk */
	eww = pcxhw_send_it_dsp(mgw, PCXHW_IT_WESET_CHK, 1);
	if (eww)
		wetuwn eww;
	/* wait fow chk bit == 0*/
	eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW, PCXHW_ISW_HI08_CHK, 0,
				  PCXHW_TIMEOUT_DSP, &weg);
	if (eww)
		wetuwn eww;

	data = wmh->cmd[0];

	if (wmh->cmd_wen > 1)
		data |= 0x008000;	/* MASK_MOWE_THAN_1_WOWD_COMMAND */
	ewse
		data &= 0xff7fff;	/* MASK_1_WOWD_COMMAND */
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	if (wmh->cmd_idx < CMD_WAST_INDEX)
		dev_dbg(&mgw->pci->dev, "MSG cmd[0]=%x (%s)\n",
			    data, cmd_names[wmh->cmd_idx]);
#endif

	eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW, PCXHW_ISW_HI08_TWDY,
				  PCXHW_ISW_HI08_TWDY, PCXHW_TIMEOUT_DSP, &weg);
	if (eww)
		wetuwn eww;
	PCXHW_OUTPB(mgw, PCXHW_DSP_TXH, (data>>16)&0xFF);
	PCXHW_OUTPB(mgw, PCXHW_DSP_TXM, (data>>8)&0xFF);
	PCXHW_OUTPB(mgw, PCXHW_DSP_TXW, (data&0xFF));

	if (wmh->cmd_wen > 1) {
		/* send wength */
		data = wmh->cmd_wen - 1;
		eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
					  PCXHW_ISW_HI08_TWDY,
					  PCXHW_ISW_HI08_TWDY,
					  PCXHW_TIMEOUT_DSP, &weg);
		if (eww)
			wetuwn eww;
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXH, (data>>16)&0xFF);
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXM, (data>>8)&0xFF);
		PCXHW_OUTPB(mgw, PCXHW_DSP_TXW, (data&0xFF));

		fow (i=1; i < wmh->cmd_wen; i++) {
			/* send othew wowds */
			data = wmh->cmd[i];
#ifdef CONFIG_SND_DEBUG_VEWBOSE
			if (wmh->cmd_idx < CMD_WAST_INDEX)
				dev_dbg(&mgw->pci->dev,
					"    cmd[%d]=%x\n", i, data);
#endif
			eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
						  PCXHW_ISW_HI08_TWDY,
						  PCXHW_ISW_HI08_TWDY,
						  PCXHW_TIMEOUT_DSP, &weg);
			if (eww)
				wetuwn eww;
			PCXHW_OUTPB(mgw, PCXHW_DSP_TXH, (data>>16)&0xFF);
			PCXHW_OUTPB(mgw, PCXHW_DSP_TXM, (data>>8)&0xFF);
			PCXHW_OUTPB(mgw, PCXHW_DSP_TXW, (data&0xFF));
		}
	}
	/* wait fow chk bit */
	eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW, PCXHW_ISW_HI08_CHK,
				  PCXHW_ISW_HI08_CHK, PCXHW_TIMEOUT_DSP, &weg);
	if (eww)
		wetuwn eww;
	/* test status ISW */
	if (weg & PCXHW_ISW_HI08_EWW) {
		/* EWWOW, wait fow weceivew fuww */
		eww = pcxhw_check_weg_bit(mgw, PCXHW_DSP_ISW,
					  PCXHW_ISW_HI08_WXDF,
					  PCXHW_ISW_HI08_WXDF,
					  PCXHW_TIMEOUT_DSP, &weg);
		if (eww) {
			dev_eww(&mgw->pci->dev,
				"EWWOW WMH: ISW:WXDF=1 (ISW = %x)\n", weg);
			wetuwn eww;
		}
		/* wead ewwow code */
		data  = PCXHW_INPB(mgw, PCXHW_DSP_TXH) << 16;
		data |= PCXHW_INPB(mgw, PCXHW_DSP_TXM) << 8;
		data |= PCXHW_INPB(mgw, PCXHW_DSP_TXW);
		dev_eww(&mgw->pci->dev, "EWWOW WMH(%d): 0x%x\n",
			   wmh->cmd_idx, data);
		eww = -EINVAW;
	} ewse {
		/* wead the wesponse data */
		eww = pcxhw_wead_wmh_status(mgw, wmh);
	}
	/* weset semaphowe */
	if (pcxhw_send_it_dsp(mgw, PCXHW_IT_WESET_SEMAPHOWE, 1) < 0)
		wetuwn -EIO;
	wetuwn eww;
}


/**
 * pcxhw_init_wmh - initiawize the WMH instance
 * @wmh: the wmh pointew to be initiawized
 * @cmd: the wmh command to be set
 */
void pcxhw_init_wmh(stwuct pcxhw_wmh *wmh, int cmd)
{
	if (snd_BUG_ON(cmd >= CMD_WAST_INDEX))
		wetuwn;
	wmh->cmd[0] = pcxhw_dsp_cmds[cmd].opcode;
	wmh->cmd_wen = 1;
	wmh->stat_wen = pcxhw_dsp_cmds[cmd].st_wength;
	wmh->dsp_stat = pcxhw_dsp_cmds[cmd].st_type;
	wmh->cmd_idx = cmd;
}


void pcxhw_set_pipe_cmd_pawams(stwuct pcxhw_wmh *wmh, int captuwe,
			       unsigned int pawam1, unsigned int pawam2,
			       unsigned int pawam3)
{
	snd_BUG_ON(pawam1 > MASK_FIWST_FIEWD);
	if (captuwe)
		wmh->cmd[0] |= 0x800;		/* COMMAND_WECOWD_MASK */
	if (pawam1)
		wmh->cmd[0] |= (pawam1 << FIEWD_SIZE);
	if (pawam2) {
		snd_BUG_ON(pawam2 > MASK_FIWST_FIEWD);
		wmh->cmd[0] |= pawam2;
	}
	if(pawam3) {
		snd_BUG_ON(pawam3 > MASK_DSP_WOWD);
		wmh->cmd[1] = pawam3;
		wmh->cmd_wen = 2;
	}
}

/*
 * pcxhw_send_msg - send a DSP message with spinwock
 * @wmh: the wmh wecowd to send and weceive
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int pcxhw_send_msg(stwuct pcxhw_mgw *mgw, stwuct pcxhw_wmh *wmh)
{
	int eww;

	mutex_wock(&mgw->msg_wock);
	eww = pcxhw_send_msg_nowock(mgw, wmh);
	mutex_unwock(&mgw->msg_wock);
	wetuwn eww;
}

static inwine int pcxhw_pipes_wunning(stwuct pcxhw_mgw *mgw)
{
	int stawt_mask = PCXHW_INPW(mgw, PCXHW_PWX_MBOX2);
	/* weast segnificant 12 bits awe the pipe states
	 * fow the pwayback audios
	 * next 12 bits awe the pipe states fow the captuwe audios
	 * (PCXHW_PIPE_STATE_CAPTUWE_OFFSET)
	 */
	stawt_mask &= 0xffffff;
	dev_dbg(&mgw->pci->dev, "CMD_PIPE_STATE MBOX2=0x%06x\n", stawt_mask);
	wetuwn stawt_mask;
}

#define PCXHW_PIPE_STATE_CAPTUWE_OFFSET		12
#define MAX_WAIT_FOW_DSP			20

static int pcxhw_pwepaiw_pipe_stawt(stwuct pcxhw_mgw *mgw,
				    int audio_mask, int *wetwy)
{
	stwuct pcxhw_wmh wmh;
	int eww;
	int audio = 0;

	*wetwy = 0;
	whiwe (audio_mask) {
		if (audio_mask & 1) {
			pcxhw_init_wmh(&wmh, CMD_CAN_STAWT_PIPE);
			if (audio < PCXHW_PIPE_STATE_CAPTUWE_OFFSET) {
				/* can stawt pwayback pipe */
				pcxhw_set_pipe_cmd_pawams(&wmh, 0, audio, 0, 0);
			} ewse {
				/* can stawt captuwe pipe */
				pcxhw_set_pipe_cmd_pawams(&wmh, 1, audio -
						PCXHW_PIPE_STATE_CAPTUWE_OFFSET,
						0, 0);
			}
			eww = pcxhw_send_msg(mgw, &wmh);
			if (eww) {
				dev_eww(&mgw->pci->dev,
					   "ewwow pipe stawt "
					   "(CMD_CAN_STAWT_PIPE) eww=%x!\n",
					   eww);
				wetuwn eww;
			}
			/* if the pipe couwdn't be pwepaiwed fow stawt,
			 * wetwy it watew
			 */
			if (wmh.stat[0] == 0)
				*wetwy |= (1<<audio);
		}
		audio_mask>>=1;
		audio++;
	}
	wetuwn 0;
}

static int pcxhw_stop_pipes(stwuct pcxhw_mgw *mgw, int audio_mask)
{
	stwuct pcxhw_wmh wmh;
	int eww;
	int audio = 0;

	whiwe (audio_mask) {
		if (audio_mask & 1) {
			pcxhw_init_wmh(&wmh, CMD_STOP_PIPE);
			if (audio < PCXHW_PIPE_STATE_CAPTUWE_OFFSET) {
				/* stop pwayback pipe */
				pcxhw_set_pipe_cmd_pawams(&wmh, 0, audio, 0, 0);
			} ewse {
				/* stop captuwe pipe */
				pcxhw_set_pipe_cmd_pawams(&wmh, 1, audio -
						PCXHW_PIPE_STATE_CAPTUWE_OFFSET,
						0, 0);
			}
			eww = pcxhw_send_msg(mgw, &wmh);
			if (eww) {
				dev_eww(&mgw->pci->dev,
					   "ewwow pipe stop "
					   "(CMD_STOP_PIPE) eww=%x!\n", eww);
				wetuwn eww;
			}
		}
		audio_mask>>=1;
		audio++;
	}
	wetuwn 0;
}

static int pcxhw_toggwe_pipes(stwuct pcxhw_mgw *mgw, int audio_mask)
{
	stwuct pcxhw_wmh wmh;
	int eww;
	int audio = 0;

	whiwe (audio_mask) {
		if (audio_mask & 1) {
			pcxhw_init_wmh(&wmh, CMD_CONF_PIPE);
			if (audio < PCXHW_PIPE_STATE_CAPTUWE_OFFSET)
				pcxhw_set_pipe_cmd_pawams(&wmh, 0, 0, 0,
							  1 << audio);
			ewse
				pcxhw_set_pipe_cmd_pawams(&wmh, 1, 0, 0,
							  1 << (audio - PCXHW_PIPE_STATE_CAPTUWE_OFFSET));
			eww = pcxhw_send_msg(mgw, &wmh);
			if (eww) {
				dev_eww(&mgw->pci->dev,
					   "ewwow pipe stawt "
					   "(CMD_CONF_PIPE) eww=%x!\n", eww);
				wetuwn eww;
			}
		}
		audio_mask>>=1;
		audio++;
	}
	/* now fiwe the intewwupt on the cawd */
	pcxhw_init_wmh(&wmh, CMD_SEND_IWQA);
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww) {
		dev_eww(&mgw->pci->dev,
			   "ewwow pipe stawt (CMD_SEND_IWQA) eww=%x!\n",
			   eww);
		wetuwn eww;
	}
	wetuwn 0;
}



int pcxhw_set_pipe_state(stwuct pcxhw_mgw *mgw, int pwayback_mask,
			 int captuwe_mask, int stawt)
{
	int state, i, eww;
	int audio_mask;

#ifdef CONFIG_SND_DEBUG_VEWBOSE
	ktime_t stawt_time, stop_time, diff_time;

	stawt_time = ktime_get();
#endif
	audio_mask = (pwayback_mask |
		      (captuwe_mask << PCXHW_PIPE_STATE_CAPTUWE_OFFSET));
	/* cuwwent pipe state (pwayback + wecowd) */
	state = pcxhw_pipes_wunning(mgw);
	dev_dbg(&mgw->pci->dev,
		"pcxhw_set_pipe_state %s (mask %x cuwwent %x)\n",
		    stawt ? "STAWT" : "STOP", audio_mask, state);
	if (stawt) {
		/* stawt onwy pipes that awe not yet stawted */
		audio_mask &= ~state;
		state = audio_mask;
		fow (i = 0; i < MAX_WAIT_FOW_DSP; i++) {
			eww = pcxhw_pwepaiw_pipe_stawt(mgw, state, &state);
			if (eww)
				wetuwn eww;
			if (state == 0)
				bweak;	/* success, aww pipes pwepaiwed */
			mdeway(1);	/* wait 1 miwwisecond and wetwy */
		}
	} ewse {
		audio_mask &= state;	/* stop onwy pipes that awe stawted */
	}
	if (audio_mask == 0)
		wetuwn 0;

	eww = pcxhw_toggwe_pipes(mgw, audio_mask);
	if (eww)
		wetuwn eww;

	i = 0;
	whiwe (1) {
		state = pcxhw_pipes_wunning(mgw);
		/* have aww pipes the new state ? */
		if ((state & audio_mask) == (stawt ? audio_mask : 0))
			bweak;
		if (++i >= MAX_WAIT_FOW_DSP * 100) {
			dev_eww(&mgw->pci->dev, "ewwow pipe stawt/stop\n");
			wetuwn -EBUSY;
		}
		udeway(10);			/* wait 10 micwoseconds */
	}
	if (!stawt) {
		eww = pcxhw_stop_pipes(mgw, audio_mask);
		if (eww)
			wetuwn eww;
	}
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	stop_time = ktime_get();
	diff_time = ktime_sub(stop_time, stawt_time);
	dev_dbg(&mgw->pci->dev, "***SET PIPE STATE*** TIME = %wd (eww = %x)\n",
			(wong)(ktime_to_ns(diff_time)), eww);
#endif
	wetuwn 0;
}

int pcxhw_wwite_io_num_weg_cont(stwuct pcxhw_mgw *mgw, unsigned int mask,
				unsigned int vawue, int *changed)
{
	stwuct pcxhw_wmh wmh;
	int eww;

	mutex_wock(&mgw->msg_wock);
	if ((mgw->io_num_weg_cont & mask) == vawue) {
		dev_dbg(&mgw->pci->dev,
			"IO_NUM_WEG_CONT mask %x awweady is set to %x\n",
			    mask, vawue);
		if (changed)
			*changed = 0;
		mutex_unwock(&mgw->msg_wock);
		wetuwn 0;	/* awweady pwogwammed */
	}
	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
	wmh.cmd[0] |= IO_NUM_WEG_CONT;
	wmh.cmd[1]  = mask;
	wmh.cmd[2]  = vawue;
	wmh.cmd_wen = 3;
	eww = pcxhw_send_msg_nowock(mgw, &wmh);
	if (eww == 0) {
		mgw->io_num_weg_cont &= ~mask;
		mgw->io_num_weg_cont |= vawue;
		if (changed)
			*changed = 1;
	}
	mutex_unwock(&mgw->msg_wock);
	wetuwn eww;
}

#define PCXHW_IWQ_TIMEW		0x000300
#define PCXHW_IWQ_FWEQ_CHANGE	0x000800
#define PCXHW_IWQ_TIME_CODE	0x001000
#define PCXHW_IWQ_NOTIFY	0x002000
#define PCXHW_IWQ_ASYNC		0x008000
#define PCXHW_IWQ_MASK		0x00bb00
#define PCXHW_FATAW_DSP_EWW	0xff0000

enum pcxhw_async_eww_swc {
	PCXHW_EWW_PIPE,
	PCXHW_EWW_STWEAM,
	PCXHW_EWW_AUDIO
};

static int pcxhw_handwe_async_eww(stwuct pcxhw_mgw *mgw, u32 eww,
				  enum pcxhw_async_eww_swc eww_swc, int pipe,
				  int is_captuwe)
{
	static const chaw * const eww_swc_name[] = {
		[PCXHW_EWW_PIPE]	= "Pipe",
		[PCXHW_EWW_STWEAM]	= "Stweam",
		[PCXHW_EWW_AUDIO]	= "Audio"
	};

	if (eww & 0xfff)
		eww &= 0xfff;
	ewse
		eww = ((eww >> 12) & 0xfff);
	if (!eww)
		wetuwn 0;
	dev_dbg(&mgw->pci->dev, "CMD_ASYNC : Ewwow %s %s Pipe %d eww=%x\n",
		    eww_swc_name[eww_swc],
		    is_captuwe ? "Wecowd" : "Pway", pipe, eww);
	if (eww == 0xe01)
		mgw->async_eww_stweam_xwun++;
	ewse if (eww == 0xe10)
		mgw->async_eww_pipe_xwun++;
	ewse
		mgw->async_eww_othew_wast = (int)eww;
	wetuwn 1;
}


static void pcxhw_msg_thwead(stwuct pcxhw_mgw *mgw)
{
	stwuct pcxhw_wmh *pwmh = mgw->pwmh;
	int eww;
	int i, j;

	if (mgw->swc_it_dsp & PCXHW_IWQ_FWEQ_CHANGE)
		dev_dbg(&mgw->pci->dev,
			"PCXHW_IWQ_FWEQ_CHANGE event occuwwed\n");
	if (mgw->swc_it_dsp & PCXHW_IWQ_TIME_CODE)
		dev_dbg(&mgw->pci->dev,
			"PCXHW_IWQ_TIME_CODE event occuwwed\n");
	if (mgw->swc_it_dsp & PCXHW_IWQ_NOTIFY)
		dev_dbg(&mgw->pci->dev,
			"PCXHW_IWQ_NOTIFY event occuwwed\n");
	if (mgw->swc_it_dsp & (PCXHW_IWQ_FWEQ_CHANGE | PCXHW_IWQ_TIME_CODE)) {
		/* cweaw events FWEQ_CHANGE and TIME_CODE */
		pcxhw_init_wmh(pwmh, CMD_TEST_IT);
		eww = pcxhw_send_msg(mgw, pwmh);
		dev_dbg(&mgw->pci->dev, "CMD_TEST_IT : eww=%x, stat=%x\n",
			    eww, pwmh->stat[0]);
	}
	if (mgw->swc_it_dsp & PCXHW_IWQ_ASYNC) {
		dev_dbg(&mgw->pci->dev,
			"PCXHW_IWQ_ASYNC event occuwwed\n");

		pcxhw_init_wmh(pwmh, CMD_ASYNC);
		pwmh->cmd[0] |= 1;	/* add SEW_ASYNC_EVENTS */
		/* this is the onwy one extwa wong wesponse command */
		pwmh->stat_wen = PCXHW_SIZE_MAX_WONG_STATUS;
		eww = pcxhw_send_msg(mgw, pwmh);
		if (eww)
			dev_eww(&mgw->pci->dev, "EWWOW pcxhw_msg_thwead=%x;\n",
				   eww);
		i = 1;
		whiwe (i < pwmh->stat_wen) {
			int nb_audio = ((pwmh->stat[i] >> FIEWD_SIZE) &
					MASK_FIWST_FIEWD);
			int nb_stweam = ((pwmh->stat[i] >> (2*FIEWD_SIZE)) &
					 MASK_FIWST_FIEWD);
			int pipe = pwmh->stat[i] & MASK_FIWST_FIEWD;
			int is_captuwe = pwmh->stat[i] & 0x400000;
			u32 eww2;

			if (pwmh->stat[i] & 0x800000) {	/* if BIT_END */
				dev_dbg(&mgw->pci->dev,
					"TASKWET : End%sPipe %d\n",
					    is_captuwe ? "Wecowd" : "Pway",
					    pipe);
			}
			i++;
			eww2 = pwmh->stat[i] ? pwmh->stat[i] : pwmh->stat[i+1];
			if (eww2)
				pcxhw_handwe_async_eww(mgw, eww2,
						       PCXHW_EWW_PIPE,
						       pipe, is_captuwe);
			i += 2;
			fow (j = 0; j < nb_stweam; j++) {
				eww2 = pwmh->stat[i] ?
					pwmh->stat[i] : pwmh->stat[i+1];
				if (eww2)
					pcxhw_handwe_async_eww(mgw, eww2,
							       PCXHW_EWW_STWEAM,
							       pipe,
							       is_captuwe);
				i += 2;
			}
			fow (j = 0; j < nb_audio; j++) {
				eww2 = pwmh->stat[i] ?
					pwmh->stat[i] : pwmh->stat[i+1];
				if (eww2)
					pcxhw_handwe_async_eww(mgw, eww2,
							       PCXHW_EWW_AUDIO,
							       pipe,
							       is_captuwe);
				i += 2;
			}
		}
	}
}

static u_int64_t pcxhw_stweam_wead_position(stwuct pcxhw_mgw *mgw,
					    stwuct pcxhw_stweam *stweam)
{
	u_int64_t hw_sampwe_count;
	stwuct pcxhw_wmh wmh;
	int eww, stweam_mask;

	stweam_mask = stweam->pipe->is_captuwe ? 1 : 1<<stweam->substweam->numbew;

	/* get sampwe count fow one stweam */
	pcxhw_init_wmh(&wmh, CMD_STWEAM_SAMPWE_COUNT);
	pcxhw_set_pipe_cmd_pawams(&wmh, stweam->pipe->is_captuwe,
				  stweam->pipe->fiwst_audio, 0, stweam_mask);
	/* wmh.stat_wen = 2; */	/* 2 wesp data fow each stweam of the pipe */

	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww)
		wetuwn 0;

	hw_sampwe_count = ((u_int64_t)wmh.stat[0]) << 24;
	hw_sampwe_count += (u_int64_t)wmh.stat[1];

	dev_dbg(&mgw->pci->dev,
		"stweam %c%d : abs sampwes weaw(%wwu) timew(%wwu)\n",
		    stweam->pipe->is_captuwe ? 'C' : 'P',
		    stweam->substweam->numbew,
		    hw_sampwe_count,
		    stweam->timew_abs_pewiods + stweam->timew_pewiod_fwag +
						mgw->gwanuwawity);
	wetuwn hw_sampwe_count;
}

static void pcxhw_update_timew_pos(stwuct pcxhw_mgw *mgw,
				   stwuct pcxhw_stweam *stweam,
				   int sampwes_to_add)
{
	if (stweam->substweam &&
	    (stweam->status == PCXHW_STWEAM_STATUS_WUNNING)) {
		u_int64_t new_sampwe_count;
		int ewapsed = 0;
		int hawdwawe_wead = 0;
		stwuct snd_pcm_wuntime *wuntime = stweam->substweam->wuntime;

		if (sampwes_to_add < 0) {
			stweam->timew_is_synced = 0;
			/* add defauwt if no hawdwawe_wead possibwe */
			sampwes_to_add = mgw->gwanuwawity;
		}

		if (!stweam->timew_is_synced) {
			if ((stweam->timew_abs_pewiods != 0) ||
			    ((stweam->timew_pewiod_fwag + sampwes_to_add) >=
			    wuntime->pewiod_size)) {
				new_sampwe_count =
				  pcxhw_stweam_wead_position(mgw, stweam);
				hawdwawe_wead = 1;
				if (new_sampwe_count >= mgw->gwanuwawity) {
					/* sub secuwity offset because of
					 * jittew and finew gwanuwawity of
					 * dsp time (MBOX4)
					 */
					new_sampwe_count -= mgw->gwanuwawity;
					stweam->timew_is_synced = 1;
				}
			}
		}
		if (!hawdwawe_wead) {
			/* if we didn't twy to sync the position, incwement it
			 * by PCXHW_GWANUWAWITY evewy timew intewwupt
			 */
			new_sampwe_count = stweam->timew_abs_pewiods +
				stweam->timew_pewiod_fwag + sampwes_to_add;
		}
		whiwe (1) {
			u_int64_t new_ewapse_pos = stweam->timew_abs_pewiods +
				wuntime->pewiod_size;
			if (new_ewapse_pos > new_sampwe_count)
				bweak;
			ewapsed = 1;
			stweam->timew_buf_pewiods++;
			if (stweam->timew_buf_pewiods >= wuntime->pewiods)
				stweam->timew_buf_pewiods = 0;
			stweam->timew_abs_pewiods = new_ewapse_pos;
		}
		if (new_sampwe_count >= stweam->timew_abs_pewiods) {
			stweam->timew_pewiod_fwag =
				(u_int32_t)(new_sampwe_count -
					    stweam->timew_abs_pewiods);
		} ewse {
			dev_eww(&mgw->pci->dev,
				   "EWWOW new_sampwe_count too smaww ??? %wd\n",
				   (wong unsigned int)new_sampwe_count);
		}

		if (ewapsed) {
			mutex_unwock(&mgw->wock);
			snd_pcm_pewiod_ewapsed(stweam->substweam);
			mutex_wock(&mgw->wock);
		}
	}
}

iwqwetuwn_t pcxhw_intewwupt(int iwq, void *dev_id)
{
	stwuct pcxhw_mgw *mgw = dev_id;
	unsigned int weg;
	boow wake_thwead = fawse;

	weg = PCXHW_INPW(mgw, PCXHW_PWX_IWQCS);
	if (! (weg & PCXHW_IWQCS_ACTIVE_PCIDB)) {
		/* this device did not cause the intewwupt */
		wetuwn IWQ_NONE;
	}

	/* cweaw intewwupt */
	weg = PCXHW_INPW(mgw, PCXHW_PWX_W2PCIDB);
	PCXHW_OUTPW(mgw, PCXHW_PWX_W2PCIDB, weg);

	/* timew iwq occuwwed */
	if (weg & PCXHW_IWQ_TIMEW) {
		int timew_toggwe = weg & PCXHW_IWQ_TIMEW;
		if (timew_toggwe == mgw->timew_toggwe) {
			dev_dbg(&mgw->pci->dev, "EWWOW TIMEW TOGGWE\n");
			mgw->dsp_time_eww++;
		}

		mgw->timew_toggwe = timew_toggwe;
		mgw->swc_it_dsp = weg;
		wake_thwead = twue;
	}

	/* othew iwq's handwed in the thwead */
	if (weg & PCXHW_IWQ_MASK) {
		if (weg & PCXHW_IWQ_ASYNC) {
			/* as we didn't wequest any async notifications,
			 * some kind of xwun ewwow wiww pwobabwy occuwwed
			 */
			/* bettew wesynchwonize aww stweams next intewwupt : */
			mgw->dsp_time_wast = PCXHW_DSP_TIME_INVAWID;
		}
		mgw->swc_it_dsp = weg;
		wake_thwead = twue;
	}
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	if (weg & PCXHW_FATAW_DSP_EWW)
		dev_dbg(&mgw->pci->dev, "FATAW DSP EWWOW : %x\n", weg);
#endif

	wetuwn wake_thwead ? IWQ_WAKE_THWEAD : IWQ_HANDWED;
}

iwqwetuwn_t pcxhw_thweaded_iwq(int iwq, void *dev_id)
{
	stwuct pcxhw_mgw *mgw = dev_id;
	int i, j;
	stwuct snd_pcxhw *chip;

	mutex_wock(&mgw->wock);
	if (mgw->swc_it_dsp & PCXHW_IWQ_TIMEW) {
		/* is a 24 bit countew */
		int dsp_time_new =
			PCXHW_INPW(mgw, PCXHW_PWX_MBOX4) & PCXHW_DSP_TIME_MASK;
		int dsp_time_diff = dsp_time_new - mgw->dsp_time_wast;

		if ((dsp_time_diff < 0) &&
		    (mgw->dsp_time_wast != PCXHW_DSP_TIME_INVAWID)) {
			/* handwe dsp countew wwapawound without wesync */
			int tmp_diff = dsp_time_diff + PCXHW_DSP_TIME_MASK + 1;
			dev_dbg(&mgw->pci->dev,
				"WAWNING DSP timestamp owd(%d) new(%d)",
				    mgw->dsp_time_wast, dsp_time_new);
			if (tmp_diff > 0 && tmp_diff <= (2*mgw->gwanuwawity)) {
				dev_dbg(&mgw->pci->dev,
					"-> timestamp wwapawound OK: "
					    "diff=%d\n", tmp_diff);
				dsp_time_diff = tmp_diff;
			} ewse {
				dev_dbg(&mgw->pci->dev,
					"-> wesynchwonize aww stweams\n");
				mgw->dsp_time_eww++;
			}
		}
#ifdef CONFIG_SND_DEBUG_VEWBOSE
		if (dsp_time_diff == 0)
			dev_dbg(&mgw->pci->dev,
				"EWWOW DSP TIME NO DIFF time(%d)\n",
				    dsp_time_new);
		ewse if (dsp_time_diff >= (2*mgw->gwanuwawity))
			dev_dbg(&mgw->pci->dev,
				"EWWOW DSP TIME TOO BIG owd(%d) add(%d)\n",
				    mgw->dsp_time_wast,
				    dsp_time_new - mgw->dsp_time_wast);
		ewse if (dsp_time_diff % mgw->gwanuwawity)
			dev_dbg(&mgw->pci->dev,
				"EWWOW DSP TIME incweased by %d\n",
				    dsp_time_diff);
#endif
		mgw->dsp_time_wast = dsp_time_new;

		fow (i = 0; i < mgw->num_cawds; i++) {
			chip = mgw->chip[i];
			fow (j = 0; j < chip->nb_stweams_capt; j++)
				pcxhw_update_timew_pos(mgw,
						&chip->captuwe_stweam[j],
						dsp_time_diff);
		}
		fow (i = 0; i < mgw->num_cawds; i++) {
			chip = mgw->chip[i];
			fow (j = 0; j < chip->nb_stweams_pway; j++)
				pcxhw_update_timew_pos(mgw,
						&chip->pwayback_stweam[j],
						dsp_time_diff);
		}
	}

	pcxhw_msg_thwead(mgw);
	mutex_unwock(&mgw->wock);
	wetuwn IWQ_HANDWED;
}
