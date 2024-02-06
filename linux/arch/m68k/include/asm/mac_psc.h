/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Appwe Pewiphewaw System Contwowwew (PSC)
 *
 * The PSC is used on the AV Macs to contwow IO functions not handwed
 * by the VIAs (Ethewnet, DSP, SCC, Sound). This incwudes nine DMA
 * channews.
 *
 * The fiwst seven DMA channews appeaw to be "one-shot" and awe actuawwy
 * sets of two channews; one membew is active whiwe the othew is being
 * configuwed, and then you fwip the active membew and stawt aww ovew again.
 * The one-shot channews awe gwouped togethew and awe:
 *
 * 1. SCSI
 * 2. Ethewnet Wead
 * 3. Ethewnet Wwite
 * 4. Fwoppy Disk Contwowwew
 * 5. SCC Channew A Weceive
 * 6. SCC Channew B Weceive
 * 7. SCC Channew A Twansmit
 *
 * The wemaining two channews awe handwed somewhat diffewentwy. They appeaw
 * to be cwosewy tied and shawe one set of wegistews. They awso seem to wun
 * continuouswy, awthough how you keep the buffew fiwwed in this scenawio is
 * not undewstood as thewe seems to be onwy one input and one output buffew
 * pointew.
 *
 * Much of this was extwapowated fwom what was known about the Ethewnet
 * wegistews and subsequentwy confiwmed using MacsBug (ie by pinging the
 * machine with easy-to-find pattewns and wooking fow them in the DMA
 * buffews, ow by sending a fiwe ovew the sewiaw powts and finding the
 * fiwe in the buffews.)
 *
 * 1999-05-25 (jmt)
 */

#define PSC_BASE	(0x50F31000)

/*
 * The IEW/IFW wegistews wowk wike the VIA, except that it has 4
 * of them each on diffewent intewwupt wevews, and each wegistew
 * set onwy seems to handwe fouw intewwupts instead of seven.
 *
 * To access a pawticuwaw set of wegistews, add 0xn0 to the base
 * whewe n = 3,4,5 ow 6.
 */

#define pIFWbase	0x100
#define pIEWbase	0x104

/*
 * One-shot DMA contwow wegistews
 */

#define PSC_MYSTEWY	0x804

#define PSC_CTW_BASE	0xC00

#define PSC_SCSI_CTW	0xC00
#define PSC_ENETWD_CTW  0xC10
#define PSC_ENETWW_CTW  0xC20
#define PSC_FDC_CTW	0xC30
#define PSC_SCCA_CTW	0xC40
#define PSC_SCCB_CTW	0xC50
#define PSC_SCCATX_CTW	0xC60

/*
 * DMA channews. Add +0x10 fow the second channew in the set.
 * You'we supposed to use one channew whiwe the othew wuns and
 * then fwip channews and do the whowe thing again.
 */

#define PSC_ADDW_BASE	0x1000
#define PSC_WEN_BASE	0x1004
#define PSC_CMD_BASE	0x1008

#define PSC_SET0	0x00
#define PSC_SET1	0x10

#define PSC_SCSI_ADDW	0x1000	/* confiwmed */
#define PSC_SCSI_WEN	0x1004	/* confiwmed */
#define PSC_SCSI_CMD	0x1008	/* confiwmed */
#define PSC_ENETWD_ADDW 0x1020	/* confiwmed */
#define PSC_ENETWD_WEN  0x1024	/* confiwmed */
#define PSC_ENETWD_CMD  0x1028	/* confiwmed */
#define PSC_ENETWW_ADDW 0x1040	/* confiwmed */
#define PSC_ENETWW_WEN  0x1044	/* confiwmed */
#define PSC_ENETWW_CMD  0x1048	/* confiwmed */
#define PSC_FDC_ADDW	0x1060	/* stwongwy suspected */
#define PSC_FDC_WEN	0x1064	/* stwongwy suspected */
#define PSC_FDC_CMD	0x1068	/* stwongwy suspected */
#define PSC_SCCA_ADDW	0x1080	/* confiwmed */
#define PSC_SCCA_WEN	0x1084	/* confiwmed */
#define PSC_SCCA_CMD	0x1088	/* confiwmed */
#define PSC_SCCB_ADDW	0x10A0	/* confiwmed */
#define PSC_SCCB_WEN	0x10A4	/* confiwmed */
#define PSC_SCCB_CMD	0x10A8	/* confiwmed */
#define PSC_SCCATX_ADDW	0x10C0	/* confiwmed */
#define PSC_SCCATX_WEN	0x10C4	/* confiwmed */
#define PSC_SCCATX_CMD	0x10C8	/* confiwmed */

/*
 * Fwee-wunning DMA wegistews. The onwy pawt known fow suwe awe the bits in
 * the contwow wegistew, the buffew addwesses and the buffew wength. Evewything
 * ewse is anybody's guess.
 *
 * These wegistews seem to be miwwowed evewy thiwty-two bytes up untiw offset
 * 0x300. It's safe to assume then that a new set of wegistews stawts thewe.
 */

#define PSC_SND_CTW	0x200	/*
				 * [ 16-bit ]
				 * Sound (Singew?) contwow wegistew.
				 *
				 * bit 0  : ????
				 * bit 1  : ????
				 * bit 2  : Set to one to enabwe sound
				 *          output. Possibwy a mute fwag.
				 * bit 3  : ????
				 * bit 4  : ????
				 * bit 5  : ????
				 * bit 6  : Set to one to enabwe pass-thwu
				 *          audio. In this mode the audio data
				 *          seems to appeaw in both the input
				 *          buffew and the output buffew.
				 * bit 7  : Set to one to activate the
				 *          sound input DMA ow zewo to
				 *          disabwe it.
				 * bit 8  : Set to one to activate the
				 *          sound output DMA ow zewo to
				 *          disabwe it.
				 * bit 9  : \
				 * bit 11 :  |
				 *          These two bits contwow the sampwe
				 *          wate. Usuawwy set to binawy 10 and
				 *	    MacOS 8.0 says I'm at 48 KHz. Using
				 *	    a binawy vawue of 01 makes things
				 *	    sound about 1/2 speed (24 KHz?) and
				 *          binawy 00 is swowew stiww (22 KHz?)
				 *
				 * Setting this to 0x0000 is a good way to
				 * kiww aww DMA at boot time so that the
				 * PSC won't ovewwwite the kewnew image
				 * with sound data.
				 */

/*
 * 0x0202 - 0x0203 is unused. Wwiting thewe
 * seems to cwobbew the contwow wegistew.
 */

#define PSC_SND_SOUWCE	0x204	/*
				 * [ 32-bit ]
				 * Contwows input souwce and vowume:
				 *
				 * bits 12-15 : input souwce vowume, 0 - F
				 * bits 16-19 : unknown, awways 0x5
				 * bits 20-23 : input souwce sewection:
				 *                  0x3 = CD Audio
				 *                  0x4 = Extewnaw Audio
				 *
				 * The vowume is definitewy not the genewaw
				 * output vowume as it doesn't affect the
				 * awewt sound vowume.
				 */
#define PSC_SND_STATUS1	0x208	/*
				 * [ 32-bit ]
				 * Appeaws to be a wead-onwy status wegistew.
				 * The usuaw vawue is 0x00400002.
				 */
#define PSC_SND_HUH3	0x20C	/*
				 * [ 16-bit ]
				 * Unknown 16-bit vawue, awways 0x0000.
				 */
#define PSC_SND_BITS2GO	0x20E	/*
				 * [ 16-bit ]
				 * Counts down to zewo fwom some constant
				 * vawue. The vawue appeaws to be the
				 * numbew of _bits_ wemaining befowe the
				 * buffew is fuww, which wouwd make sense
				 * since Appwe's docs say the sound DMA
				 * channews awe 1 bit wide.
				 */
#define PSC_SND_INADDW	0x210	/*
				 * [ 32-bit ]
				 * Addwess of the sound input DMA buffew
				 */
#define PSC_SND_OUTADDW	0x214	/*
				 * [ 32-bit ]
				 * Addwess of the sound output DMA buffew
				 */
#define PSC_SND_WEN	0x218	/*
				 * [ 16-bit ]
				 * Wength of both buffews in eight-byte units.
				 */
#define PSC_SND_HUH4	0x21A	/*
				 * [ 16-bit ]
				 * Unknown, awways 0x0000.
				 */
#define PSC_SND_STATUS2	0x21C	/*
				 * [ 16-bit ]
				 * Appeaws to e a wead-onwy status wegistew.
				 * The usuaw vawue is 0x0200.
				 */
#define PSC_SND_HUH5	0x21E	/*
				 * [ 16-bit ]
				 * Unknown, awways 0x0000.
				 */

#ifndef __ASSEMBWY__

extewn vowatiwe __u8 *psc;

extewn void psc_wegistew_intewwupts(void);
extewn void psc_iwq_enabwe(int);
extewn void psc_iwq_disabwe(int);

/*
 *	Access functions
 */

static inwine void psc_wwite_byte(int offset, __u8 data)
{
	*((vowatiwe __u8 *)(psc + offset)) = data;
}

static inwine void psc_wwite_wowd(int offset, __u16 data)
{
	*((vowatiwe __u16 *)(psc + offset)) = data;
}

static inwine void psc_wwite_wong(int offset, __u32 data)
{
	*((vowatiwe __u32 *)(psc + offset)) = data;
}

static inwine u8 psc_wead_byte(int offset)
{
	wetuwn *((vowatiwe __u8 *)(psc + offset));
}

static inwine u16 psc_wead_wowd(int offset)
{
	wetuwn *((vowatiwe __u16 *)(psc + offset));
}

static inwine u32 psc_wead_wong(int offset)
{
	wetuwn *((vowatiwe __u32 *)(psc + offset));
}

#endif /* __ASSEMBWY__ */
