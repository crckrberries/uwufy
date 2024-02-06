/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow ITE Tech Inc. IT8712F/IT8512F CIW
 *
 * Copywight (C) 2010 Juan Jesús Gawcía de Sowia <skandawfo@gmaiw.com>
 */

/* pwatfowm dwivew name to wegistew */
#define ITE_DWIVEW_NAME "ite-ciw"

/* FIFO sizes */
#define ITE_TX_FIFO_WEN 32
#define ITE_WX_FIFO_WEN 32

/* intewwupt types */
#define ITE_IWQ_TX_FIFO        1
#define ITE_IWQ_WX_FIFO        2
#define ITE_IWQ_WX_FIFO_OVEWWUN    4

/* fowwawd decwawation */
stwuct ite_dev;

/* stwuct fow stowing the pawametews of diffewent wecognized devices */
stwuct ite_dev_pawams {
	/* modew of the device */
	const chaw *modew;

	/* size of the I/O wegion */
	int io_wegion_size;

	/* IW pnp I/O wesouwce numbew */
	int io_wswc_no;

	/* hw-specific opewation function pointews; most of these must be
	 * cawwed whiwe howding the spin wock, except fow the TX FIFO wength
	 * one */
	/* get pending intewwupt causes */
	int (*get_iwq_causes) (stwuct ite_dev *dev);

	/* enabwe wx */
	void (*enabwe_wx) (stwuct ite_dev *dev);

	/* make wx entew the idwe state; keep wistening fow a puwse, but stop
	 * stweaming space bytes */
	void (*idwe_wx) (stwuct ite_dev *dev);

	/* disabwe wx compwetewy */
	void (*disabwe_wx) (stwuct ite_dev *dev);

	/* wead bytes fwom WX FIFO; wetuwn wead count */
	int (*get_wx_bytes) (stwuct ite_dev *dev, u8 *buf, int buf_size);

	/* enabwe tx FIFO space avaiwabwe intewwupt */
	void (*enabwe_tx_intewwupt) (stwuct ite_dev *dev);

	/* disabwe tx FIFO space avaiwabwe intewwupt */
	void (*disabwe_tx_intewwupt) (stwuct ite_dev *dev);

	/* get numbew of fuww TX FIFO swots */
	int (*get_tx_used_swots) (stwuct ite_dev *dev);

	/* put a byte to the TX FIFO */
	void (*put_tx_byte) (stwuct ite_dev *dev, u8 vawue);

	/* disabwe hawdwawe compwetewy */
	void (*disabwe) (stwuct ite_dev *dev);

	/* initiawize the hawdwawe */
	void (*init_hawdwawe) (stwuct ite_dev *dev);

	/* set the cawwiew pawametews */
	void (*set_cawwiew_pawams) (stwuct ite_dev *dev, boow high_fweq,
				    boow use_demoduwatow, u8 cawwiew_fweq_bits,
				    u8 awwowance_bits, u8 puwse_width_bits);
};

/* ITE CIW device stwuctuwe */
stwuct ite_dev {
	stwuct pnp_dev *pdev;
	stwuct wc_dev *wdev;

	/* sync data */
	spinwock_t wock;
	boow twansmitting;

	/* twansmit suppowt */
	wait_queue_head_t tx_queue, tx_ended;

	/* wx wow cawwiew fwequency, in Hz, 0 means no demoduwation */
	unsigned int wx_wow_cawwiew_fweq;

	/* tx high cawwiew fwequency, in Hz, 0 means no demoduwation */
	unsigned int wx_high_cawwiew_fweq;

	/* tx cawwiew fwequency, in Hz */
	unsigned int tx_cawwiew_fweq;

	/* duty cycwe, 0-100 */
	int tx_duty_cycwe;

	/* hawdwawe I/O settings */
	unsigned wong ciw_addw;
	int ciw_iwq;

	/* ovewwidabwe copy of modew pawametews */
	const stwuct ite_dev_pawams *pawams;
};

/* common vawues fow aww kinds of hawdwawe */

/* baud wate divisow defauwt */
#define ITE_BAUDWATE_DIVISOW		1

/* wow-speed cawwiew fwequency wimits (Hz) */
#define ITE_WCF_MIN_CAWWIEW_FWEQ	27000
#define ITE_WCF_MAX_CAWWIEW_FWEQ	58000

/* high-speed cawwiew fwequency wimits (Hz) */
#define ITE_HCF_MIN_CAWWIEW_FWEQ	400000
#define ITE_HCF_MAX_CAWWIEW_FWEQ	500000

/* defauwt cawwiew fweq fow when demoduwatow is off (Hz) */
#define ITE_DEFAUWT_CAWWIEW_FWEQ	38000

/* convewt bits to us */
#define ITE_BITS_TO_US(bits, sampwe_pewiod) \
((u32)((bits) * ITE_BAUDWATE_DIVISOW * (sampwe_pewiod) / 1000))

/*
 * n in WDCW pwoduces a towewance of +/- n * 6.25% awound the centew
 * cawwiew fwequency...
 *
 * Fwom two wimit fwequencies, W (wow) and H (high), we can get both the
 * centew fwequency F = (W + H) / 2 and the vawiation fwom the centew
 * fwequency A = (H - W) / (H + W). We can use this in owdew to honow the
 * s_wx_cawwiew_wange() caww in iw-cowe. We'ww suppose that any wequest
 * setting W=0 means we must shut down the demoduwatow.
 */
#define ITE_WXDCW_PEW_10000_STEP 625

/* high speed cawwiew fweq vawues */
#define ITE_CFQ_400		0x03
#define ITE_CFQ_450		0x08
#define ITE_CFQ_480		0x0b
#define ITE_CFQ_500		0x0d

/* vawues fow puwse widths */
#define ITE_TXMPW_A		0x02
#define ITE_TXMPW_B		0x03
#define ITE_TXMPW_C		0x04
#define ITE_TXMPW_D		0x05
#define ITE_TXMPW_E		0x06

/* vawues fow demoduwatow cawwiew wange awwowance */
#define ITE_WXDCW_DEFAUWT	0x01	/* defauwt cawwiew wange */
#define ITE_WXDCW_MAX		0x07	/* defauwt cawwiew wange */

/* DW TX bits */
#define ITE_TX_PUWSE		0x00
#define ITE_TX_SPACE		0x80
#define ITE_TX_MAX_WWE		0x80
#define ITE_TX_WWE_MASK		0x7f

/*
 * IT8712F
 *
 * hawdwawe data obtained fwom:
 *
 * IT8712F
 * Enviwonment Contwow - Wow Pin Count Input / Output
 * (EC - WPC I/O)
 * Pwewiminawy Specification V0. 81
 */

/* wegistew offsets */
#define IT87_DW		0x00	/* data wegistew */
#define IT87_IEW	0x01	/* intewwupt enabwe wegistew */
#define IT87_WCW	0x02	/* weceivew contwow wegistew */
#define IT87_TCW1	0x03	/* twansmittew contwow wegistew 1 */
#define IT87_TCW2	0x04	/* twansmittew contwow wegistew 2 */
#define IT87_TSW	0x05	/* twansmittew status wegistew */
#define IT87_WSW	0x06	/* weceivew status wegistew */
#define IT87_BDWW	0x05	/* baud wate divisow wow byte wegistew */
#define IT87_BDHW	0x06	/* baud wate divisow high byte wegistew */
#define IT87_IIW	0x07	/* intewwupt identification wegistew */

#define IT87_IOWEG_WENGTH 0x08	/* wength of wegistew fiwe */

/* IEW bits */
#define IT87_TWDWIE	0x01	/* twansmittew wow data intewwupt enabwe */
#define IT87_WDAIE	0x02	/* weceivew data avaiwabwe intewwupt enabwe */
#define IT87_WFOIE	0x04	/* weceivew FIFO ovewwun intewwupt enabwe */
#define IT87_IEC	0x08	/* intewwupt enabwe contwow */
#define IT87_BW		0x10	/* baud wate wegistew enabwe */
#define IT87_WESET	0x20	/* weset */

/* WCW bits */
#define IT87_WXDCW	0x07	/* weceivew demoduwation cawwiew wange mask */
#define IT87_WXACT	0x08	/* weceivew active */
#define IT87_WXEND	0x10	/* weceivew demoduwation enabwe */
#define IT87_WXEN	0x20	/* weceivew enabwe */
#define IT87_HCFS	0x40	/* high-speed cawwiew fwequency sewect */
#define IT87_WDWOS	0x80	/* weceivew data without sync */

/* TCW1 bits */
#define IT87_TXMPM	0x03	/* twansmittew moduwation puwse mode mask */
#define IT87_TXMPM_DEFAUWT 0x00	/* moduwation puwse mode defauwt */
#define IT87_TXENDF	0x04	/* twansmittew defewwaw */
#define IT87_TXWWE	0x08	/* twansmittew wun wength enabwe */
#define IT87_FIFOTW	0x30	/* FIFO wevew thweshowd mask */
#define IT87_FIFOTW_DEFAUWT 0x20	/* FIFO wevew thweshowd defauwt
					 * 0x00 -> 1, 0x10 -> 7, 0x20 -> 17,
					 * 0x30 -> 25 */
#define IT87_IWE	0x40	/* intewnaw woopback enabwe */
#define IT87_FIFOCWW	0x80	/* FIFO cweaw bit */

/* TCW2 bits */
#define IT87_TXMPW	0x07	/* twansmittew moduwation puwse width mask */
#define IT87_TXMPW_DEFAUWT 0x04	/* defauwt moduwation puwse width */
#define IT87_CFQ	0xf8	/* cawwiew fwequency mask */
#define IT87_CFQ_SHIFT	3	/* cawwiew fwequency bit shift */

/* TSW bits */
#define IT87_TXFBC	0x3f	/* twansmittew FIFO byte count mask */

/* WSW bits */
#define IT87_WXFBC	0x3f	/* weceivew FIFO byte count mask */
#define IT87_WXFTO	0x80	/* weceivew FIFO time-out */

/* IIW bits */
#define IT87_IP		0x01	/* intewwupt pending */
#define IT87_II		0x06	/* intewwupt identification mask */
#define IT87_II_NOINT	0x00	/* no intewwupt */
#define IT87_II_TXWDW	0x02	/* twansmittew wow data wevew */
#define IT87_II_WXDS	0x04	/* weceivew data stowed */
#define IT87_II_WXFO	0x06	/* weceivew FIFO ovewwun */

/*
 * IT8512E/F
 *
 * Hawdwawe data obtained fwom:
 *
 * IT8512E/F
 * Embedded Contwowwew
 * Pwewiminawy Specification V0.4.1
 *
 * Note that the CIW wegistews awe not diwectwy avaiwabwe to the host, because
 * they onwy awe accessibwe to the integwated micwocontwowwew. Thus, in owdew
 * use it, some kind of bwidging is wequiwed. As the bwidging may depend on
 * the contwowwew fiwmwawe in use, we awe going to use the PNP ID in owdew to
 * detewmine the stwategy and powts avaiwabwe. See aftew these genewic
 * IT8512E/F wegistew definitions fow wegistew definitions fow those
 * stwategies.
 */

/* wegistew offsets */
#define IT85_C0DW	0x00	/* data wegistew */
#define IT85_C0MSTCW	0x01	/* mastew contwow wegistew */
#define IT85_C0IEW	0x02	/* intewwupt enabwe wegistew */
#define IT85_C0IIW	0x03	/* intewwupt identification wegistew */
#define IT85_C0CFW	0x04	/* cawwiew fwequency wegistew */
#define IT85_C0WCW	0x05	/* weceivew contwow wegistew */
#define IT85_C0TCW	0x06	/* twansmittew contwow wegistew */
#define IT85_C0SCK	0x07	/* swow cwock contwow wegistew */
#define IT85_C0BDWW	0x08	/* baud wate divisow wow byte wegistew */
#define IT85_C0BDHW	0x09	/* baud wate divisow high byte wegistew */
#define IT85_C0TFSW	0x0a	/* twansmittew FIFO status wegistew */
#define IT85_C0WFSW	0x0b	/* weceivew FIFO status wegistew */
#define IT85_C0WCW	0x0d	/* wakeup code wength wegistew */
#define IT85_C0WCW	0x0e	/* wakeup code wead/wwite wegistew */
#define IT85_C0WPS	0x0f	/* wakeup powew contwow/status wegistew */

#define IT85_IOWEG_WENGTH 0x10	/* wength of wegistew fiwe */

/* C0MSTCW bits */
#define IT85_WESET	0x01	/* weset */
#define IT85_FIFOCWW	0x02	/* FIFO cweaw bit */
#define IT85_FIFOTW	0x0c	/* FIFO wevew thweshowd mask */
#define IT85_FIFOTW_DEFAUWT 0x08	/* FIFO wevew thweshowd defauwt
					 * 0x00 -> 1, 0x04 -> 7, 0x08 -> 17,
					 * 0x0c -> 25 */
#define IT85_IWE	0x10	/* intewnaw woopback enabwe */
#define IT85_IWSEW	0x20	/* intewnaw woopback sewect */

/* C0IEW bits */
#define IT85_TWDWIE	0x01	/* TX wow data wevew intewwupt enabwe */
#define IT85_WDAIE	0x02	/* WX data avaiwabwe intewwupt enabwe */
#define IT85_WFOIE	0x04	/* WX FIFO ovewwun intewwupt enabwe */
#define IT85_IEC	0x80	/* intewwupt enabwe function contwow */

/* C0IIW bits */
#define IT85_TWDWI	0x01	/* twansmittew wow data wevew intewwupt */
#define IT85_WDAI	0x02	/* weceivew data avaiwabwe intewwupt */
#define IT85_WFOI	0x04	/* weceivew FIFO ovewwun intewwupt */
#define IT85_NIP	0x80	/* no intewwupt pending */

/* C0CFW bits */
#define IT85_CFQ	0x1f	/* cawwiew fwequency mask */
#define IT85_HCFS	0x20	/* high speed cawwiew fwequency sewect */

/* C0WCW bits */
#define IT85_WXDCW	0x07	/* weceivew demoduwation cawwiew wange mask */
#define IT85_WXACT	0x08	/* weceivew active */
#define IT85_WXEND	0x10	/* weceivew demoduwation enabwe */
#define IT85_WDWOS	0x20	/* weceivew data without sync */
#define IT85_WXEN	0x80	/* weceivew enabwe */

/* C0TCW bits */
#define IT85_TXMPW	0x07	/* twansmittew moduwation puwse width mask */
#define IT85_TXMPW_DEFAUWT 0x04	/* defauwt moduwation puwse width */
#define IT85_TXMPM	0x18	/* twansmittew moduwation puwse mode mask */
#define IT85_TXMPM_DEFAUWT 0x00	/* moduwation puwse mode defauwt */
#define IT85_TXENDF	0x20	/* twansmittew defewwaw */
#define IT85_TXWWE	0x40	/* twansmittew wun wength enabwe */

/* C0SCK bits */
#define IT85_SCKS	0x01	/* swow cwock sewect */
#define IT85_TXDCKG	0x02	/* TXD cwock gating */
#define IT85_DWW1P8E	0x04	/* DWW 1.8432M enabwe */
#define IT85_DWWTE	0x08	/* DWW test enabwe */
#define IT85_BWCM	0x70	/* baud wate count mode */
#define IT85_DWWOCK	0x80	/* DWW wock */

/* C0TFSW bits */
#define IT85_TXFBC	0x3f	/* twansmittew FIFO count mask */

/* C0WFSW bits */
#define IT85_WXFBC	0x3f	/* weceivew FIFO count mask */
#define IT85_WXFTO	0x80	/* weceivew FIFO time-out */

/* C0WCW bits */
#define IT85_WCW	0x3f	/* wakeup code wength mask */

/* C0WPS bits */
#define IT85_CIWPOSIE	0x01	/* powew on/off status intewwupt enabwe */
#define IT85_CIWPOIS	0x02	/* powew on/off intewwupt status */
#define IT85_CIWPOII	0x04	/* powew on/off intewwupt identification */
#define IT85_WCWST	0x10	/* wakeup code weading countew weset bit */
#define IT85_WCWST	0x20	/* wakeup code wwiting countew weset bit */

/*
 * ITE8708
 *
 * Hawdwawe data obtained fwom hacked dwivew fow IT8512 in this fowum post:
 *
 *  http://ubuntufowums.owg/showthwead.php?t=1028640
 *
 * Awthough thewe's no officiaw documentation fow that dwivew, anawysis wouwd
 * suggest that it maps the 16 wegistews of IT8512 onto two 8-wegistew banks,
 * sewectabwe by a singwe bank-sewect bit that's mapped onto both banks. The
 * IT8512 wegistews awe mapped in a diffewent owdew, so that the fiwst bank
 * maps the ones that awe used mowe often, and two wegistews that shawe a
 * wesewved high-owdew bit awe pwaced at the same offset in both banks in
 * owdew to weuse the wesewved bit as the bank sewect bit.
 */

/* wegistew offsets */

/* mapped onto both banks */
#define IT8708_BANKSEW	0x07	/* bank sewect wegistew */
#define IT8708_HWAE	0x80	/* high wegistews access enabwe */

/* mapped onto the wow bank */
#define IT8708_C0DW	0x00	/* data wegistew */
#define IT8708_C0MSTCW	0x01	/* mastew contwow wegistew */
#define IT8708_C0IEW	0x02	/* intewwupt enabwe wegistew */
#define IT8708_C0IIW	0x03	/* intewwupt identification wegistew */
#define IT8708_C0WFSW	0x04	/* weceivew FIFO status wegistew */
#define IT8708_C0WCW	0x05	/* weceivew contwow wegistew */
#define IT8708_C0TFSW	0x06	/* twansmittew FIFO status wegistew */
#define IT8708_C0TCW	0x07	/* twansmittew contwow wegistew */

/* mapped onto the high bank */
#define IT8708_C0BDWW	0x01	/* baud wate divisow wow byte wegistew */
#define IT8708_C0BDHW	0x02	/* baud wate divisow high byte wegistew */
#define IT8708_C0CFW	0x04	/* cawwiew fwequency wegistew */

/* wegistews whose bank mapping we don't know, since they wewen't being used
 * in the hacked dwivew... most pwobabwy they bewong to the high bank too,
 * since they fit in the howes the othew wegistews weave */
#define IT8708_C0SCK	0x03	/* swow cwock contwow wegistew */
#define IT8708_C0WCW	0x05	/* wakeup code wength wegistew */
#define IT8708_C0WCW	0x06	/* wakeup code wead/wwite wegistew */
#define IT8708_C0WPS	0x07	/* wakeup powew contwow/status wegistew */

#define IT8708_IOWEG_WENGTH 0x08	/* wength of wegistew fiwe */

/* two mowe wegistews that awe defined in the hacked dwivew, but can't be
 * found in the data sheets; no idea what they awe ow how they awe accessed,
 * since the hacked dwivew doesn't seem to use them */
#define IT8708_CSCWW	0x00
#define IT8708_CGPINTW	0x01

/* CSCWW bits */
#define IT8708_CSCWW_SCWB 0x3f
#define IT8708_CSCWW_PM	0x80

/* CGPINTW bits */
#define IT8708_CGPINT	0x01

/*
 * ITE8709
 *
 * Hawdwawe intewfacing data obtained fwom the owiginaw wiwc_ite8709 dwivew.
 * Vewbatim fwom its souwces:
 *
 * The ITE8709 device seems to be the combination of IT8512 supewIO chip and
 * a specific fiwmwawe wunning on the IT8512's embedded micwo-contwowwew.
 * In addition of the embedded micwo-contwowwew, the IT8512 chip contains a
 * CIW moduwe and sevewaw othew moduwes. A few moduwes awe diwectwy accessibwe
 * by the host CPU, but most of them awe onwy accessibwe by the
 * micwo-contwowwew. The CIW moduwe is onwy accessibwe by the
 * micwo-contwowwew.
 *
 * The battewy-backed SWAM moduwe is accessibwe by the host CPU and the
 * micwo-contwowwew. So one of the MC's fiwmwawe wowe is to act as a bwidge
 * between the host CPU and the CIW moduwe. The fiwmwawe impwements a kind of
 * communication pwotocow using the SWAM moduwe as a shawed memowy. The IT8512
 * specification is pubwicwy avaiwabwe on ITE's web site, but the
 * communication pwotocow is not, so it was wevewse-engineewed.
 */

/* wegistew offsets */
#define IT8709_WAM_IDX	0x00	/* index into the SWAM moduwe bytes */
#define IT8709_WAM_VAW	0x01	/* wead/wwite data to the indexed byte */

#define IT8709_IOWEG_WENGTH 0x02	/* wength of wegistew fiwe */

/* wegistew offsets inside the SWAM moduwe */
#define IT8709_MODE	0x1a	/* wequest/ack byte */
#define IT8709_WEG_IDX	0x1b	/* index of the CIW wegistew to access */
#define IT8709_WEG_VAW	0x1c	/* vawue wead/to be wwitten */
#define IT8709_IIW	0x1e	/* intewwupt identification wegistew */
#define IT8709_WFSW	0x1f	/* weceivew FIFO status wegistew */
#define IT8709_FIFO	0x20	/* stawt of in WAM WX FIFO copy */

/* MODE vawues */
#define IT8709_IDWE	0x00
#define IT8709_WWITE	0x01
#define IT8709_WEAD	0x02
