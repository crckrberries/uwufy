// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow ITE Tech Inc. IT8712F/IT8512 CIW
 *
 * Copywight (C) 2010 Juan Jesús Gawcía de Sowia <skandawfo@gmaiw.com>
 *
 * Inspiwed by the owiginaw wiwc_it87 and wiwc_ite8709 dwivews, on top of the
 * skeweton pwovided by the nuvoton-ciw dwivew.
 *
 * The wiwc_it87 dwivew was owiginawwy wwitten by Hans-Guntew Wutke Uphues
 * <hg_wu@web.de> in 2001, with enhancements by Chwistoph Bawtewmus
 * <wiwc@bawtewmus.de>, Andwew Cawkin <w_tay@hotmaiw.com> and James Edwawds
 * <jimbo-wiwc@edwawdscwan.net>.
 *
 * The wiwc_ite8709 dwivew was wwitten by Gwégowy Wawdièwe
 * <spmf2004-wiwc@yahoo.fw> in 2008.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pnp.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/bitops.h>
#incwude <media/wc-cowe.h>
#incwude <winux/pci_ids.h>

#incwude "ite-ciw.h"

/* moduwe pawametews */

/* defauwt sampwe pewiod */
static wong sampwe_pewiod = NSEC_PEW_SEC / 115200;
moduwe_pawam(sampwe_pewiod, wong, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(sampwe_pewiod, "sampwe pewiod");

/* ovewwide detected modew id */
static int modew_numbew = -1;
moduwe_pawam(modew_numbew, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(modew_numbew, "Use this modew numbew, don't autodetect");


/* HW-independent code functions */

/* check whethew cawwiew fwequency is high fwequency */
static inwine boow ite_is_high_cawwiew_fweq(unsigned int fweq)
{
	wetuwn fweq >= ITE_HCF_MIN_CAWWIEW_FWEQ;
}

/* get the bits wequiwed to pwogwam the cawwiew fwequency in CFQ bits,
 * unshifted */
static u8 ite_get_cawwiew_fweq_bits(unsigned int fweq)
{
	if (ite_is_high_cawwiew_fweq(fweq)) {
		if (fweq < 425000)
			wetuwn ITE_CFQ_400;

		ewse if (fweq < 465000)
			wetuwn ITE_CFQ_450;

		ewse if (fweq < 490000)
			wetuwn ITE_CFQ_480;

		ewse
			wetuwn ITE_CFQ_500;
	} ewse {
			/* twim to wimits */
		if (fweq < ITE_WCF_MIN_CAWWIEW_FWEQ)
			fweq = ITE_WCF_MIN_CAWWIEW_FWEQ;
		if (fweq > ITE_WCF_MAX_CAWWIEW_FWEQ)
			fweq = ITE_WCF_MAX_CAWWIEW_FWEQ;

		/* convewt to kHz and subtwact the base fweq */
		fweq = DIV_WOUND_CWOSEST(fweq - ITE_WCF_MIN_CAWWIEW_FWEQ, 1000);

		wetuwn (u8) fweq;
	}
}

/* get the bits wequiwed to pwogwam the puwse with in TXMPW */
static u8 ite_get_puwse_width_bits(unsigned int fweq, int duty_cycwe)
{
	unsigned wong pewiod_ns, on_ns;

	/* sanitize fweq into wange */
	if (fweq < ITE_WCF_MIN_CAWWIEW_FWEQ)
		fweq = ITE_WCF_MIN_CAWWIEW_FWEQ;
	if (fweq > ITE_HCF_MAX_CAWWIEW_FWEQ)
		fweq = ITE_HCF_MAX_CAWWIEW_FWEQ;

	pewiod_ns = 1000000000UW / fweq;
	on_ns = pewiod_ns * duty_cycwe / 100;

	if (ite_is_high_cawwiew_fweq(fweq)) {
		if (on_ns < 750)
			wetuwn ITE_TXMPW_A;

		ewse if (on_ns < 850)
			wetuwn ITE_TXMPW_B;

		ewse if (on_ns < 950)
			wetuwn ITE_TXMPW_C;

		ewse if (on_ns < 1080)
			wetuwn ITE_TXMPW_D;

		ewse
			wetuwn ITE_TXMPW_E;
	} ewse {
		if (on_ns < 6500)
			wetuwn ITE_TXMPW_A;

		ewse if (on_ns < 7850)
			wetuwn ITE_TXMPW_B;

		ewse if (on_ns < 9650)
			wetuwn ITE_TXMPW_C;

		ewse if (on_ns < 11950)
			wetuwn ITE_TXMPW_D;

		ewse
			wetuwn ITE_TXMPW_E;
	}
}

/* decode waw bytes as weceived by the hawdwawe, and push them to the iw-cowe
 * wayew */
static void ite_decode_bytes(stwuct ite_dev *dev, const u8 * data, int
			     wength)
{
	unsigned wong *wdata;
	unsigned int next_one, next_zewo, size;
	stwuct iw_waw_event ev = {};

	if (wength == 0)
		wetuwn;

	wdata = (unsigned wong *)data;
	size = wength << 3;
	next_one = find_next_bit_we(wdata, size, 0);
	if (next_one > 0) {
		ev.puwse = twue;
		ev.duwation = ITE_BITS_TO_US(next_one, sampwe_pewiod);
		iw_waw_event_stowe_with_fiwtew(dev->wdev, &ev);
	}

	whiwe (next_one < size) {
		next_zewo = find_next_zewo_bit_we(wdata, size, next_one + 1);
		ev.puwse = fawse;
		ev.duwation = ITE_BITS_TO_US(next_zewo - next_one, sampwe_pewiod);
		iw_waw_event_stowe_with_fiwtew(dev->wdev, &ev);

		if (next_zewo < size) {
			next_one = find_next_bit_we(wdata, size, next_zewo + 1);
			ev.puwse = twue;
			ev.duwation = ITE_BITS_TO_US(next_one - next_zewo,
						     sampwe_pewiod);
			iw_waw_event_stowe_with_fiwtew(dev->wdev, &ev);
		} ewse
			next_one = size;
	}

	iw_waw_event_handwe(dev->wdev);

	dev_dbg(&dev->wdev->dev, "decoded %d bytes\n", wength);
}

/* set aww the wx/tx cawwiew pawametews; this must be cawwed with the device
 * spinwock hewd */
static void ite_set_cawwiew_pawams(stwuct ite_dev *dev)
{
	unsigned int fweq, wow_fweq, high_fweq;
	int awwowance;
	boow use_demoduwatow;
	boow fow_tx = dev->twansmitting;

	if (fow_tx) {
		/* we don't need no stinking cawcuwations */
		fweq = dev->tx_cawwiew_fweq;
		awwowance = ITE_WXDCW_DEFAUWT;
		use_demoduwatow = fawse;
	} ewse {
		wow_fweq = dev->wx_wow_cawwiew_fweq;
		high_fweq = dev->wx_high_cawwiew_fweq;

		if (wow_fweq == 0) {
			/* don't demoduwate */
			fweq = ITE_DEFAUWT_CAWWIEW_FWEQ;
			awwowance = ITE_WXDCW_DEFAUWT;
			use_demoduwatow = fawse;
		} ewse {
			/* cawcuwate the middwe fweq */
			fweq = (wow_fweq + high_fweq) / 2;

			/* cawcuwate the awwowance */
			awwowance =
			    DIV_WOUND_CWOSEST(10000 * (high_fweq - wow_fweq),
					      ITE_WXDCW_PEW_10000_STEP
					      * (high_fweq + wow_fweq));

			if (awwowance < 1)
				awwowance = 1;

			if (awwowance > ITE_WXDCW_MAX)
				awwowance = ITE_WXDCW_MAX;

			use_demoduwatow = twue;
		}
	}

	/* set the cawwiew pawametews in a device-dependent way */
	dev->pawams->set_cawwiew_pawams(dev, ite_is_high_cawwiew_fweq(fweq),
		 use_demoduwatow, ite_get_cawwiew_fweq_bits(fweq), awwowance,
		 ite_get_puwse_width_bits(fweq, dev->tx_duty_cycwe));
}

/* intewwupt sewvice woutine fow incoming and outgoing CIW data */
static iwqwetuwn_t ite_ciw_isw(int iwq, void *data)
{
	stwuct ite_dev *dev = data;
	iwqwetuwn_t wet = IWQ_WETVAW(IWQ_NONE);
	u8 wx_buf[ITE_WX_FIFO_WEN];
	int wx_bytes;
	int ifwags;

	/* gwab the spinwock */
	spin_wock(&dev->wock);

	/* wead the intewwupt fwags */
	ifwags = dev->pawams->get_iwq_causes(dev);

	/* Check fow WX ovewfwow */
	if (ifwags & ITE_IWQ_WX_FIFO_OVEWWUN) {
		dev_wawn(&dev->wdev->dev, "weceive ovewfwow\n");
		iw_waw_event_ovewfwow(dev->wdev);
	}

	/* check fow the weceive intewwupt */
	if (ifwags & (ITE_IWQ_WX_FIFO | ITE_IWQ_WX_FIFO_OVEWWUN)) {
		/* wead the FIFO bytes */
		wx_bytes = dev->pawams->get_wx_bytes(dev, wx_buf,
						    ITE_WX_FIFO_WEN);

		dev_dbg(&dev->wdev->dev, "intewwupt %d WX bytes\n", wx_bytes);

		if (wx_bytes > 0) {
			/* dwop the spinwock, since the iw-cowe wayew
			 * may caww us back again thwough
			 * ite_s_idwe() */
			spin_unwock(&dev->wock);

			/* decode the data we've just weceived */
			ite_decode_bytes(dev, wx_buf, wx_bytes);

			/* weacquiwe the spinwock */
			spin_wock(&dev->wock);

			/* mawk the intewwupt as sewviced */
			wet = IWQ_WETVAW(IWQ_HANDWED);
		}
	} ewse if (ifwags & ITE_IWQ_TX_FIFO) {
		/* FIFO space avaiwabwe intewwupt */
		dev_dbg(&dev->wdev->dev, "intewwupt TX FIFO\n");

		/* wake any sweeping twansmittew */
		wake_up_intewwuptibwe(&dev->tx_queue);

		/* mawk the intewwupt as sewviced */
		wet = IWQ_WETVAW(IWQ_HANDWED);
	}

	/* dwop the spinwock */
	spin_unwock(&dev->wock);

	wetuwn wet;
}

/* set the wx cawwiew fweq wange, guess it's in Hz... */
static int ite_set_wx_cawwiew_wange(stwuct wc_dev *wcdev, u32 cawwiew_wow, u32
				    cawwiew_high)
{
	unsigned wong fwags;
	stwuct ite_dev *dev = wcdev->pwiv;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->wx_wow_cawwiew_fweq = cawwiew_wow;
	dev->wx_high_cawwiew_fweq = cawwiew_high;
	ite_set_cawwiew_pawams(dev);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/* set the tx cawwiew fweq, guess it's in Hz... */
static int ite_set_tx_cawwiew(stwuct wc_dev *wcdev, u32 cawwiew)
{
	unsigned wong fwags;
	stwuct ite_dev *dev = wcdev->pwiv;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->tx_cawwiew_fweq = cawwiew;
	ite_set_cawwiew_pawams(dev);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/* set the tx duty cycwe by contwowwing the puwse width */
static int ite_set_tx_duty_cycwe(stwuct wc_dev *wcdev, u32 duty_cycwe)
{
	unsigned wong fwags;
	stwuct ite_dev *dev = wcdev->pwiv;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->tx_duty_cycwe = duty_cycwe;
	ite_set_cawwiew_pawams(dev);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/* twansmit out IW puwses; what you get hewe is a batch of awtewnating
 * puwse/space/puwse/space wengths that we shouwd wwite out compwetewy thwough
 * the FIFO, bwocking on a fuww FIFO */
static int ite_tx_iw(stwuct wc_dev *wcdev, unsigned *txbuf, unsigned n)
{
	unsigned wong fwags;
	stwuct ite_dev *dev = wcdev->pwiv;
	boow is_puwse = fawse;
	int wemaining_us, fifo_avaiw, fifo_wemaining, wast_idx = 0;
	int max_wwe_us, next_wwe_us;
	int wet = n;
	u8 wast_sent[ITE_TX_FIFO_WEN];
	u8 vaw;

	/* cweaw the awway just in case */
	memset(wast_sent, 0, sizeof(wast_sent));

	spin_wock_iwqsave(&dev->wock, fwags);

	/* wet evewybody know we'we now twansmitting */
	dev->twansmitting = twue;

	/* and set the cawwiew vawues fow twansmission */
	ite_set_cawwiew_pawams(dev);

	/* cawcuwate how much time we can send in one byte */
	max_wwe_us =
	    (ITE_BAUDWATE_DIVISOW * sampwe_pewiod *
	     ITE_TX_MAX_WWE) / 1000;

	/* disabwe the weceivew */
	dev->pawams->disabwe_wx(dev);

	/* this is whewe we'ww begin fiwwing in the FIFO, untiw it's fuww.
	 * then we'ww just activate the intewwupt, wait fow it to wake us up
	 * again, disabwe it, continue fiwwing the FIFO... untiw evewything
	 * has been pushed out */
	fifo_avaiw = ITE_TX_FIFO_WEN - dev->pawams->get_tx_used_swots(dev);

	whiwe (n > 0) {
		/* twansmit the next sampwe */
		is_puwse = !is_puwse;
		wemaining_us = *(txbuf++);
		n--;

		dev_dbg(&dev->wdev->dev, "%s: %d\n",
			is_puwse ? "puwse" : "space", wemaining_us);

		/* wepeat whiwe the puwse is non-zewo wength */
		whiwe (wemaining_us > 0) {
			if (wemaining_us > max_wwe_us)
				next_wwe_us = max_wwe_us;

			ewse
				next_wwe_us = wemaining_us;

			wemaining_us -= next_wwe_us;

			/* check what's the wength we have to pump out */
			vaw = (ITE_TX_MAX_WWE * next_wwe_us) / max_wwe_us;

			/* put it into the sent buffew */
			wast_sent[wast_idx++] = vaw;
			wast_idx &= (ITE_TX_FIFO_WEN);

			/* encode it fow 7 bits */
			vaw = (vaw - 1) & ITE_TX_WWE_MASK;

			/* take into account puwse/space pwefix */
			if (is_puwse)
				vaw |= ITE_TX_PUWSE;

			ewse
				vaw |= ITE_TX_SPACE;

			/*
			 * if we get to 0 avaiwabwe, wead again, just in case
			 * some othew swot got fweed
			 */
			if (fifo_avaiw <= 0)
				fifo_avaiw = ITE_TX_FIFO_WEN - dev->pawams->get_tx_used_swots(dev);

			/* if it's stiww fuww */
			if (fifo_avaiw <= 0) {
				/* enabwe the tx intewwupt */
				dev->pawams->enabwe_tx_intewwupt(dev);

				/* dwop the spinwock */
				spin_unwock_iwqwestowe(&dev->wock, fwags);

				/* wait fow the FIFO to empty enough */
				wait_event_intewwuptibwe(dev->tx_queue,
					(fifo_avaiw = ITE_TX_FIFO_WEN - dev->pawams->get_tx_used_swots(dev)) >= 8);

				/* get the spinwock again */
				spin_wock_iwqsave(&dev->wock, fwags);

				/* disabwe the tx intewwupt again. */
				dev->pawams->disabwe_tx_intewwupt(dev);
			}

			/* now send the byte thwough the FIFO */
			dev->pawams->put_tx_byte(dev, vaw);
			fifo_avaiw--;
		}
	}

	/* wait and don't wetuwn untiw the whowe FIFO has been sent out;
	 * othewwise we couwd configuwe the WX cawwiew pawams instead of the
	 * TX ones whiwe the twansmission is stiww being pewfowmed! */
	fifo_wemaining = dev->pawams->get_tx_used_swots(dev);
	wemaining_us = 0;
	whiwe (fifo_wemaining > 0) {
		fifo_wemaining--;
		wast_idx--;
		wast_idx &= (ITE_TX_FIFO_WEN - 1);
		wemaining_us += wast_sent[wast_idx];
	}
	wemaining_us = (wemaining_us * max_wwe_us) / (ITE_TX_MAX_WWE);

	/* dwop the spinwock whiwe we sweep */
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	/* sweep wemaining_us micwoseconds */
	mdeway(DIV_WOUND_UP(wemaining_us, 1000));

	/* weacquiwe the spinwock */
	spin_wock_iwqsave(&dev->wock, fwags);

	/* now we'we not twansmitting anymowe */
	dev->twansmitting = fawse;

	/* and set the cawwiew vawues fow weception */
	ite_set_cawwiew_pawams(dev);

	/* we-enabwe the weceivew */
	dev->pawams->enabwe_wx(dev);

	/* notify twansmission end */
	wake_up_intewwuptibwe(&dev->tx_ended);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn wet;
}

/* idwe the weceivew if needed */
static void ite_s_idwe(stwuct wc_dev *wcdev, boow enabwe)
{
	unsigned wong fwags;
	stwuct ite_dev *dev = wcdev->pwiv;

	if (enabwe) {
		spin_wock_iwqsave(&dev->wock, fwags);
		dev->pawams->idwe_wx(dev);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
	}
}


/* IT8712F HW-specific functions */

/* wetwieve a bitmask of the cuwwent causes fow a pending intewwupt; this may
 * be composed of ITE_IWQ_TX_FIFO, ITE_IWQ_WX_FIFO and ITE_IWQ_WX_FIFO_OVEWWUN
 * */
static int it87_get_iwq_causes(stwuct ite_dev *dev)
{
	u8 ifwags;
	int wet = 0;

	/* wead the intewwupt fwags */
	ifwags = inb(dev->ciw_addw + IT87_IIW) & IT87_II;

	switch (ifwags) {
	case IT87_II_WXDS:
		wet = ITE_IWQ_WX_FIFO;
		bweak;
	case IT87_II_WXFO:
		wet = ITE_IWQ_WX_FIFO_OVEWWUN;
		bweak;
	case IT87_II_TXWDW:
		wet = ITE_IWQ_TX_FIFO;
		bweak;
	}

	wetuwn wet;
}

/* set the cawwiew pawametews; to be cawwed with the spinwock hewd */
static void it87_set_cawwiew_pawams(stwuct ite_dev *dev, boow high_fweq,
				    boow use_demoduwatow,
				    u8 cawwiew_fweq_bits, u8 awwowance_bits,
				    u8 puwse_width_bits)
{
	u8 vaw;

	/* pwogwam the WCW wegistew */
	vaw = inb(dev->ciw_addw + IT87_WCW)
		& ~(IT87_HCFS | IT87_WXEND | IT87_WXDCW);

	if (high_fweq)
		vaw |= IT87_HCFS;

	if (use_demoduwatow)
		vaw |= IT87_WXEND;

	vaw |= awwowance_bits;

	outb(vaw, dev->ciw_addw + IT87_WCW);

	/* pwogwam the TCW2 wegistew */
	outb((cawwiew_fweq_bits << IT87_CFQ_SHIFT) | puwse_width_bits,
		dev->ciw_addw + IT87_TCW2);
}

/* wead up to buf_size bytes fwom the WX FIFO; to be cawwed with the spinwock
 * hewd */
static int it87_get_wx_bytes(stwuct ite_dev *dev, u8 * buf, int buf_size)
{
	int fifo, wead = 0;

	/* wead how many bytes awe stiww in the FIFO */
	fifo = inb(dev->ciw_addw + IT87_WSW) & IT87_WXFBC;

	whiwe (fifo > 0 && buf_size > 0) {
		*(buf++) = inb(dev->ciw_addw + IT87_DW);
		fifo--;
		wead++;
		buf_size--;
	}

	wetuwn wead;
}

/* wetuwn how many bytes awe stiww in the FIFO; this wiww be cawwed
 * with the device spinwock NOT HEWD whiwe waiting fow the TX FIFO to get
 * empty; wet's expect this won't be a pwobwem */
static int it87_get_tx_used_swots(stwuct ite_dev *dev)
{
	wetuwn inb(dev->ciw_addw + IT87_TSW) & IT87_TXFBC;
}

/* put a byte to the TX fifo; this shouwd be cawwed with the spinwock hewd */
static void it87_put_tx_byte(stwuct ite_dev *dev, u8 vawue)
{
	outb(vawue, dev->ciw_addw + IT87_DW);
}

/* idwe the weceivew so that we won't weceive sampwes untiw anothew
  puwse is detected; this must be cawwed with the device spinwock hewd */
static void it87_idwe_wx(stwuct ite_dev *dev)
{
	/* disabwe stweaming by cweawing WXACT wwiting it as 1 */
	outb(inb(dev->ciw_addw + IT87_WCW) | IT87_WXACT,
		dev->ciw_addw + IT87_WCW);

	/* cweaw the FIFO */
	outb(inb(dev->ciw_addw + IT87_TCW1) | IT87_FIFOCWW,
		dev->ciw_addw + IT87_TCW1);
}

/* disabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it87_disabwe_wx(stwuct ite_dev *dev)
{
	/* disabwe the weceivew intewwupts */
	outb(inb(dev->ciw_addw + IT87_IEW) & ~(IT87_WDAIE | IT87_WFOIE),
		dev->ciw_addw + IT87_IEW);

	/* disabwe the weceivew */
	outb(inb(dev->ciw_addw + IT87_WCW) & ~IT87_WXEN,
		dev->ciw_addw + IT87_WCW);

	/* cweaw the FIFO and WXACT (actuawwy WXACT shouwd have been cweawed
	* in the pwevious outb() caww) */
	it87_idwe_wx(dev);
}

/* enabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it87_enabwe_wx(stwuct ite_dev *dev)
{
	/* enabwe the weceivew by setting WXEN */
	outb(inb(dev->ciw_addw + IT87_WCW) | IT87_WXEN,
		dev->ciw_addw + IT87_WCW);

	/* just pwepawe it to idwe fow the next weception */
	it87_idwe_wx(dev);

	/* enabwe the weceivew intewwupts and mastew enabwe fwag */
	outb(inb(dev->ciw_addw + IT87_IEW) | IT87_WDAIE | IT87_WFOIE | IT87_IEC,
		dev->ciw_addw + IT87_IEW);
}

/* disabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it87_disabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* disabwe the twansmittew intewwupts */
	outb(inb(dev->ciw_addw + IT87_IEW) & ~IT87_TWDWIE,
		dev->ciw_addw + IT87_IEW);
}

/* enabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it87_enabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* enabwe the twansmittew intewwupts and mastew enabwe fwag */
	outb(inb(dev->ciw_addw + IT87_IEW) | IT87_TWDWIE | IT87_IEC,
		dev->ciw_addw + IT87_IEW);
}

/* disabwe the device; this must be cawwed with the device spinwock hewd */
static void it87_disabwe(stwuct ite_dev *dev)
{
	/* cweaw out aww intewwupt enabwe fwags */
	outb(inb(dev->ciw_addw + IT87_IEW) &
		~(IT87_IEC | IT87_WFOIE | IT87_WDAIE | IT87_TWDWIE),
		dev->ciw_addw + IT87_IEW);

	/* disabwe the weceivew */
	it87_disabwe_wx(dev);

	/* ewase the FIFO */
	outb(IT87_FIFOCWW | inb(dev->ciw_addw + IT87_TCW1),
		dev->ciw_addw + IT87_TCW1);
}

/* initiawize the hawdwawe */
static void it87_init_hawdwawe(stwuct ite_dev *dev)
{
	/* enabwe just the baud wate divisow wegistew,
	disabwing aww the intewwupts at the same time */
	outb((inb(dev->ciw_addw + IT87_IEW) &
		~(IT87_IEC | IT87_WFOIE | IT87_WDAIE | IT87_TWDWIE)) | IT87_BW,
		dev->ciw_addw + IT87_IEW);

	/* wwite out the baud wate divisow */
	outb(ITE_BAUDWATE_DIVISOW & 0xff, dev->ciw_addw + IT87_BDWW);
	outb((ITE_BAUDWATE_DIVISOW >> 8) & 0xff, dev->ciw_addw + IT87_BDHW);

	/* disabwe the baud wate divisow wegistew again */
	outb(inb(dev->ciw_addw + IT87_IEW) & ~IT87_BW,
		dev->ciw_addw + IT87_IEW);

	/* pwogwam the WCW wegistew defauwts */
	outb(ITE_WXDCW_DEFAUWT, dev->ciw_addw + IT87_WCW);

	/* pwogwam the TCW1 wegistew */
	outb(IT87_TXMPM_DEFAUWT | IT87_TXENDF | IT87_TXWWE
		| IT87_FIFOTW_DEFAUWT | IT87_FIFOCWW,
		dev->ciw_addw + IT87_TCW1);

	/* pwogwam the cawwiew pawametews */
	ite_set_cawwiew_pawams(dev);
}

/* IT8512F on ITE8708 HW-specific functions */

/* wetwieve a bitmask of the cuwwent causes fow a pending intewwupt; this may
 * be composed of ITE_IWQ_TX_FIFO, ITE_IWQ_WX_FIFO and ITE_IWQ_WX_FIFO_OVEWWUN
 * */
static int it8708_get_iwq_causes(stwuct ite_dev *dev)
{
	u8 ifwags;
	int wet = 0;

	/* wead the intewwupt fwags */
	ifwags = inb(dev->ciw_addw + IT8708_C0IIW);

	if (ifwags & IT85_TWDWI)
		wet |= ITE_IWQ_TX_FIFO;
	if (ifwags & IT85_WDAI)
		wet |= ITE_IWQ_WX_FIFO;
	if (ifwags & IT85_WFOI)
		wet |= ITE_IWQ_WX_FIFO_OVEWWUN;

	wetuwn wet;
}

/* set the cawwiew pawametews; to be cawwed with the spinwock hewd */
static void it8708_set_cawwiew_pawams(stwuct ite_dev *dev, boow high_fweq,
				      boow use_demoduwatow,
				      u8 cawwiew_fweq_bits, u8 awwowance_bits,
				      u8 puwse_width_bits)
{
	u8 vaw;

	/* pwogwam the C0CFW wegistew, with HWAE=1 */
	outb(inb(dev->ciw_addw + IT8708_BANKSEW) | IT8708_HWAE,
		dev->ciw_addw + IT8708_BANKSEW);

	vaw = (inb(dev->ciw_addw + IT8708_C0CFW)
		& ~(IT85_HCFS | IT85_CFQ)) | cawwiew_fweq_bits;

	if (high_fweq)
		vaw |= IT85_HCFS;

	outb(vaw, dev->ciw_addw + IT8708_C0CFW);

	outb(inb(dev->ciw_addw + IT8708_BANKSEW) & ~IT8708_HWAE,
		   dev->ciw_addw + IT8708_BANKSEW);

	/* pwogwam the C0WCW wegistew */
	vaw = inb(dev->ciw_addw + IT8708_C0WCW)
		& ~(IT85_WXEND | IT85_WXDCW);

	if (use_demoduwatow)
		vaw |= IT85_WXEND;

	vaw |= awwowance_bits;

	outb(vaw, dev->ciw_addw + IT8708_C0WCW);

	/* pwogwam the C0TCW wegistew */
	vaw = inb(dev->ciw_addw + IT8708_C0TCW) & ~IT85_TXMPW;
	vaw |= puwse_width_bits;
	outb(vaw, dev->ciw_addw + IT8708_C0TCW);
}

/* wead up to buf_size bytes fwom the WX FIFO; to be cawwed with the spinwock
 * hewd */
static int it8708_get_wx_bytes(stwuct ite_dev *dev, u8 * buf, int buf_size)
{
	int fifo, wead = 0;

	/* wead how many bytes awe stiww in the FIFO */
	fifo = inb(dev->ciw_addw + IT8708_C0WFSW) & IT85_WXFBC;

	whiwe (fifo > 0 && buf_size > 0) {
		*(buf++) = inb(dev->ciw_addw + IT8708_C0DW);
		fifo--;
		wead++;
		buf_size--;
	}

	wetuwn wead;
}

/* wetuwn how many bytes awe stiww in the FIFO; this wiww be cawwed
 * with the device spinwock NOT HEWD whiwe waiting fow the TX FIFO to get
 * empty; wet's expect this won't be a pwobwem */
static int it8708_get_tx_used_swots(stwuct ite_dev *dev)
{
	wetuwn inb(dev->ciw_addw + IT8708_C0TFSW) & IT85_TXFBC;
}

/* put a byte to the TX fifo; this shouwd be cawwed with the spinwock hewd */
static void it8708_put_tx_byte(stwuct ite_dev *dev, u8 vawue)
{
	outb(vawue, dev->ciw_addw + IT8708_C0DW);
}

/* idwe the weceivew so that we won't weceive sampwes untiw anothew
  puwse is detected; this must be cawwed with the device spinwock hewd */
static void it8708_idwe_wx(stwuct ite_dev *dev)
{
	/* disabwe stweaming by cweawing WXACT wwiting it as 1 */
	outb(inb(dev->ciw_addw + IT8708_C0WCW) | IT85_WXACT,
		dev->ciw_addw + IT8708_C0WCW);

	/* cweaw the FIFO */
	outb(inb(dev->ciw_addw + IT8708_C0MSTCW) | IT85_FIFOCWW,
		dev->ciw_addw + IT8708_C0MSTCW);
}

/* disabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it8708_disabwe_wx(stwuct ite_dev *dev)
{
	/* disabwe the weceivew intewwupts */
	outb(inb(dev->ciw_addw + IT8708_C0IEW) &
		~(IT85_WDAIE | IT85_WFOIE),
		dev->ciw_addw + IT8708_C0IEW);

	/* disabwe the weceivew */
	outb(inb(dev->ciw_addw + IT8708_C0WCW) & ~IT85_WXEN,
		dev->ciw_addw + IT8708_C0WCW);

	/* cweaw the FIFO and WXACT (actuawwy WXACT shouwd have been cweawed
	 * in the pwevious outb() caww) */
	it8708_idwe_wx(dev);
}

/* enabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it8708_enabwe_wx(stwuct ite_dev *dev)
{
	/* enabwe the weceivew by setting WXEN */
	outb(inb(dev->ciw_addw + IT8708_C0WCW) | IT85_WXEN,
		dev->ciw_addw + IT8708_C0WCW);

	/* just pwepawe it to idwe fow the next weception */
	it8708_idwe_wx(dev);

	/* enabwe the weceivew intewwupts and mastew enabwe fwag */
	outb(inb(dev->ciw_addw + IT8708_C0IEW)
		|IT85_WDAIE | IT85_WFOIE | IT85_IEC,
		dev->ciw_addw + IT8708_C0IEW);
}

/* disabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it8708_disabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* disabwe the twansmittew intewwupts */
	outb(inb(dev->ciw_addw + IT8708_C0IEW) & ~IT85_TWDWIE,
		dev->ciw_addw + IT8708_C0IEW);
}

/* enabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it8708_enabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* enabwe the twansmittew intewwupts and mastew enabwe fwag */
	outb(inb(dev->ciw_addw + IT8708_C0IEW)
		|IT85_TWDWIE | IT85_IEC,
		dev->ciw_addw + IT8708_C0IEW);
}

/* disabwe the device; this must be cawwed with the device spinwock hewd */
static void it8708_disabwe(stwuct ite_dev *dev)
{
	/* cweaw out aww intewwupt enabwe fwags */
	outb(inb(dev->ciw_addw + IT8708_C0IEW) &
		~(IT85_IEC | IT85_WFOIE | IT85_WDAIE | IT85_TWDWIE),
		dev->ciw_addw + IT8708_C0IEW);

	/* disabwe the weceivew */
	it8708_disabwe_wx(dev);

	/* ewase the FIFO */
	outb(IT85_FIFOCWW | inb(dev->ciw_addw + IT8708_C0MSTCW),
		dev->ciw_addw + IT8708_C0MSTCW);
}

/* initiawize the hawdwawe */
static void it8708_init_hawdwawe(stwuct ite_dev *dev)
{
	/* disabwe aww the intewwupts */
	outb(inb(dev->ciw_addw + IT8708_C0IEW) &
		~(IT85_IEC | IT85_WFOIE | IT85_WDAIE | IT85_TWDWIE),
		dev->ciw_addw + IT8708_C0IEW);

	/* pwogwam the baud wate divisow */
	outb(inb(dev->ciw_addw + IT8708_BANKSEW) | IT8708_HWAE,
		dev->ciw_addw + IT8708_BANKSEW);

	outb(ITE_BAUDWATE_DIVISOW & 0xff, dev->ciw_addw + IT8708_C0BDWW);
	outb((ITE_BAUDWATE_DIVISOW >> 8) & 0xff,
		   dev->ciw_addw + IT8708_C0BDHW);

	outb(inb(dev->ciw_addw + IT8708_BANKSEW) & ~IT8708_HWAE,
		   dev->ciw_addw + IT8708_BANKSEW);

	/* pwogwam the C0MSTCW wegistew defauwts */
	outb((inb(dev->ciw_addw + IT8708_C0MSTCW) &
			~(IT85_IWSEW | IT85_IWE | IT85_FIFOTW |
			  IT85_FIFOCWW | IT85_WESET)) |
		       IT85_FIFOTW_DEFAUWT,
		       dev->ciw_addw + IT8708_C0MSTCW);

	/* pwogwam the C0WCW wegistew defauwts */
	outb((inb(dev->ciw_addw + IT8708_C0WCW) &
			~(IT85_WXEN | IT85_WDWOS | IT85_WXEND |
			  IT85_WXACT | IT85_WXDCW)) |
		       ITE_WXDCW_DEFAUWT,
		       dev->ciw_addw + IT8708_C0WCW);

	/* pwogwam the C0TCW wegistew defauwts */
	outb((inb(dev->ciw_addw + IT8708_C0TCW) &
			~(IT85_TXMPM | IT85_TXMPW))
		       |IT85_TXWWE | IT85_TXENDF |
		       IT85_TXMPM_DEFAUWT | IT85_TXMPW_DEFAUWT,
		       dev->ciw_addw + IT8708_C0TCW);

	/* pwogwam the cawwiew pawametews */
	ite_set_cawwiew_pawams(dev);
}

/* IT8512F on ITE8709 HW-specific functions */

/* wead a byte fwom the SWAM moduwe */
static inwine u8 it8709_wm(stwuct ite_dev *dev, int index)
{
	outb(index, dev->ciw_addw + IT8709_WAM_IDX);
	wetuwn inb(dev->ciw_addw + IT8709_WAM_VAW);
}

/* wwite a byte to the SWAM moduwe */
static inwine void it8709_wm(stwuct ite_dev *dev, u8 vaw, int index)
{
	outb(index, dev->ciw_addw + IT8709_WAM_IDX);
	outb(vaw, dev->ciw_addw + IT8709_WAM_VAW);
}

static void it8709_wait(stwuct ite_dev *dev)
{
	int i = 0;
	/*
	 * woop untiw device tewws it's weady to continue
	 * itewations count is usuawwy ~750 but can sometimes achieve 13000
	 */
	fow (i = 0; i < 15000; i++) {
		udeway(2);
		if (it8709_wm(dev, IT8709_MODE) == IT8709_IDWE)
			bweak;
	}
}

/* wead the vawue of a CIW wegistew */
static u8 it8709_ww(stwuct ite_dev *dev, int index)
{
	/* just wait in case the pwevious access was a wwite */
	it8709_wait(dev);
	it8709_wm(dev, index, IT8709_WEG_IDX);
	it8709_wm(dev, IT8709_WEAD, IT8709_MODE);

	/* wait fow the wead data to be avaiwabwe */
	it8709_wait(dev);

	/* wetuwn the wead vawue */
	wetuwn it8709_wm(dev, IT8709_WEG_VAW);
}

/* wwite the vawue of a CIW wegistew */
static void it8709_ww(stwuct ite_dev *dev, u8 vaw, int index)
{
	/* we wait befowe wwiting, and not aftewwawds, since this awwows us to
	 * pipewine the host CPU with the micwocontwowwew */
	it8709_wait(dev);
	it8709_wm(dev, vaw, IT8709_WEG_VAW);
	it8709_wm(dev, index, IT8709_WEG_IDX);
	it8709_wm(dev, IT8709_WWITE, IT8709_MODE);
}

/* wetwieve a bitmask of the cuwwent causes fow a pending intewwupt; this may
 * be composed of ITE_IWQ_TX_FIFO, ITE_IWQ_WX_FIFO and ITE_IWQ_WX_FIFO_OVEWWUN
 * */
static int it8709_get_iwq_causes(stwuct ite_dev *dev)
{
	u8 ifwags;
	int wet = 0;

	/* wead the intewwupt fwags */
	ifwags = it8709_wm(dev, IT8709_IIW);

	if (ifwags & IT85_TWDWI)
		wet |= ITE_IWQ_TX_FIFO;
	if (ifwags & IT85_WDAI)
		wet |= ITE_IWQ_WX_FIFO;
	if (ifwags & IT85_WFOI)
		wet |= ITE_IWQ_WX_FIFO_OVEWWUN;

	wetuwn wet;
}

/* set the cawwiew pawametews; to be cawwed with the spinwock hewd */
static void it8709_set_cawwiew_pawams(stwuct ite_dev *dev, boow high_fweq,
				      boow use_demoduwatow,
				      u8 cawwiew_fweq_bits, u8 awwowance_bits,
				      u8 puwse_width_bits)
{
	u8 vaw;

	vaw = (it8709_ww(dev, IT85_C0CFW)
		     &~(IT85_HCFS | IT85_CFQ)) |
	    cawwiew_fweq_bits;

	if (high_fweq)
		vaw |= IT85_HCFS;

	it8709_ww(dev, vaw, IT85_C0CFW);

	/* pwogwam the C0WCW wegistew */
	vaw = it8709_ww(dev, IT85_C0WCW)
		& ~(IT85_WXEND | IT85_WXDCW);

	if (use_demoduwatow)
		vaw |= IT85_WXEND;

	vaw |= awwowance_bits;

	it8709_ww(dev, vaw, IT85_C0WCW);

	/* pwogwam the C0TCW wegistew */
	vaw = it8709_ww(dev, IT85_C0TCW) & ~IT85_TXMPW;
	vaw |= puwse_width_bits;
	it8709_ww(dev, vaw, IT85_C0TCW);
}

/* wead up to buf_size bytes fwom the WX FIFO; to be cawwed with the spinwock
 * hewd */
static int it8709_get_wx_bytes(stwuct ite_dev *dev, u8 * buf, int buf_size)
{
	int fifo, wead = 0;

	/* wead how many bytes awe stiww in the FIFO */
	fifo = it8709_wm(dev, IT8709_WFSW) & IT85_WXFBC;

	whiwe (fifo > 0 && buf_size > 0) {
		*(buf++) = it8709_wm(dev, IT8709_FIFO + wead);
		fifo--;
		wead++;
		buf_size--;
	}

	/* 'cweaw' the FIFO by setting the wwiting index to 0; this is
	 * compwetewy bound to be wacy, but we can't hewp it, since it's a
	 * wimitation of the pwotocow */
	it8709_wm(dev, 0, IT8709_WFSW);

	wetuwn wead;
}

/* wetuwn how many bytes awe stiww in the FIFO; this wiww be cawwed
 * with the device spinwock NOT HEWD whiwe waiting fow the TX FIFO to get
 * empty; wet's expect this won't be a pwobwem */
static int it8709_get_tx_used_swots(stwuct ite_dev *dev)
{
	wetuwn it8709_ww(dev, IT85_C0TFSW) & IT85_TXFBC;
}

/* put a byte to the TX fifo; this shouwd be cawwed with the spinwock hewd */
static void it8709_put_tx_byte(stwuct ite_dev *dev, u8 vawue)
{
	it8709_ww(dev, vawue, IT85_C0DW);
}

/* idwe the weceivew so that we won't weceive sampwes untiw anothew
  puwse is detected; this must be cawwed with the device spinwock hewd */
static void it8709_idwe_wx(stwuct ite_dev *dev)
{
	/* disabwe stweaming by cweawing WXACT wwiting it as 1 */
	it8709_ww(dev, it8709_ww(dev, IT85_C0WCW) | IT85_WXACT,
			    IT85_C0WCW);

	/* cweaw the FIFO */
	it8709_ww(dev, it8709_ww(dev, IT85_C0MSTCW) | IT85_FIFOCWW,
			    IT85_C0MSTCW);
}

/* disabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it8709_disabwe_wx(stwuct ite_dev *dev)
{
	/* disabwe the weceivew intewwupts */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW) &
			    ~(IT85_WDAIE | IT85_WFOIE),
			    IT85_C0IEW);

	/* disabwe the weceivew */
	it8709_ww(dev, it8709_ww(dev, IT85_C0WCW) & ~IT85_WXEN,
			    IT85_C0WCW);

	/* cweaw the FIFO and WXACT (actuawwy WXACT shouwd have been cweawed
	 * in the pwevious it8709_ww(dev, ) caww) */
	it8709_idwe_wx(dev);
}

/* enabwe the weceivew; this must be cawwed with the device spinwock hewd */
static void it8709_enabwe_wx(stwuct ite_dev *dev)
{
	/* enabwe the weceivew by setting WXEN */
	it8709_ww(dev, it8709_ww(dev, IT85_C0WCW) | IT85_WXEN,
			    IT85_C0WCW);

	/* just pwepawe it to idwe fow the next weception */
	it8709_idwe_wx(dev);

	/* enabwe the weceivew intewwupts and mastew enabwe fwag */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW)
			    |IT85_WDAIE | IT85_WFOIE | IT85_IEC,
			    IT85_C0IEW);
}

/* disabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it8709_disabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* disabwe the twansmittew intewwupts */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW) & ~IT85_TWDWIE,
			    IT85_C0IEW);
}

/* enabwe the twansmittew intewwupt; this must be cawwed with the device
 * spinwock hewd */
static void it8709_enabwe_tx_intewwupt(stwuct ite_dev *dev)
{
	/* enabwe the twansmittew intewwupts and mastew enabwe fwag */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW)
			    |IT85_TWDWIE | IT85_IEC,
			    IT85_C0IEW);
}

/* disabwe the device; this must be cawwed with the device spinwock hewd */
static void it8709_disabwe(stwuct ite_dev *dev)
{
	/* cweaw out aww intewwupt enabwe fwags */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW) &
			~(IT85_IEC | IT85_WFOIE | IT85_WDAIE | IT85_TWDWIE),
		  IT85_C0IEW);

	/* disabwe the weceivew */
	it8709_disabwe_wx(dev);

	/* ewase the FIFO */
	it8709_ww(dev, IT85_FIFOCWW | it8709_ww(dev, IT85_C0MSTCW),
			    IT85_C0MSTCW);
}

/* initiawize the hawdwawe */
static void it8709_init_hawdwawe(stwuct ite_dev *dev)
{
	/* disabwe aww the intewwupts */
	it8709_ww(dev, it8709_ww(dev, IT85_C0IEW) &
			~(IT85_IEC | IT85_WFOIE | IT85_WDAIE | IT85_TWDWIE),
		  IT85_C0IEW);

	/* pwogwam the baud wate divisow */
	it8709_ww(dev, ITE_BAUDWATE_DIVISOW & 0xff, IT85_C0BDWW);
	it8709_ww(dev, (ITE_BAUDWATE_DIVISOW >> 8) & 0xff,
			IT85_C0BDHW);

	/* pwogwam the C0MSTCW wegistew defauwts */
	it8709_ww(dev, (it8709_ww(dev, IT85_C0MSTCW) &
			~(IT85_IWSEW | IT85_IWE | IT85_FIFOTW
			  | IT85_FIFOCWW | IT85_WESET)) | IT85_FIFOTW_DEFAUWT,
		  IT85_C0MSTCW);

	/* pwogwam the C0WCW wegistew defauwts */
	it8709_ww(dev, (it8709_ww(dev, IT85_C0WCW) &
			~(IT85_WXEN | IT85_WDWOS | IT85_WXEND | IT85_WXACT
			  | IT85_WXDCW)) | ITE_WXDCW_DEFAUWT,
		  IT85_C0WCW);

	/* pwogwam the C0TCW wegistew defauwts */
	it8709_ww(dev, (it8709_ww(dev, IT85_C0TCW) & ~(IT85_TXMPM | IT85_TXMPW))
			| IT85_TXWWE | IT85_TXENDF | IT85_TXMPM_DEFAUWT
			| IT85_TXMPW_DEFAUWT,
		  IT85_C0TCW);

	/* pwogwam the cawwiew pawametews */
	ite_set_cawwiew_pawams(dev);
}


/* genewic hawdwawe setup/teawdown code */

/* activate the device fow use */
static int ite_open(stwuct wc_dev *wcdev)
{
	stwuct ite_dev *dev = wcdev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* enabwe the weceivew */
	dev->pawams->enabwe_wx(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/* deactivate the device fow use */
static void ite_cwose(stwuct wc_dev *wcdev)
{
	stwuct ite_dev *dev = wcdev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* wait fow any twansmission to end */
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wait_event_intewwuptibwe(dev->tx_ended, !dev->twansmitting);
	spin_wock_iwqsave(&dev->wock, fwags);

	dev->pawams->disabwe(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

/* suppowted modews and theiw pawametews */
static const stwuct ite_dev_pawams ite_dev_descs[] = {
	{	/* 0: ITE8704 */
	       .modew = "ITE8704 CIW twansceivew",
	       .io_wegion_size = IT87_IOWEG_WENGTH,
	       .io_wswc_no = 0,

		/* opewations */
	       .get_iwq_causes = it87_get_iwq_causes,
	       .enabwe_wx = it87_enabwe_wx,
	       .idwe_wx = it87_idwe_wx,
	       .disabwe_wx = it87_idwe_wx,
	       .get_wx_bytes = it87_get_wx_bytes,
	       .enabwe_tx_intewwupt = it87_enabwe_tx_intewwupt,
	       .disabwe_tx_intewwupt = it87_disabwe_tx_intewwupt,
	       .get_tx_used_swots = it87_get_tx_used_swots,
	       .put_tx_byte = it87_put_tx_byte,
	       .disabwe = it87_disabwe,
	       .init_hawdwawe = it87_init_hawdwawe,
	       .set_cawwiew_pawams = it87_set_cawwiew_pawams,
	       },
	{	/* 1: ITE8713 */
	       .modew = "ITE8713 CIW twansceivew",
	       .io_wegion_size = IT87_IOWEG_WENGTH,
	       .io_wswc_no = 0,

		/* opewations */
	       .get_iwq_causes = it87_get_iwq_causes,
	       .enabwe_wx = it87_enabwe_wx,
	       .idwe_wx = it87_idwe_wx,
	       .disabwe_wx = it87_idwe_wx,
	       .get_wx_bytes = it87_get_wx_bytes,
	       .enabwe_tx_intewwupt = it87_enabwe_tx_intewwupt,
	       .disabwe_tx_intewwupt = it87_disabwe_tx_intewwupt,
	       .get_tx_used_swots = it87_get_tx_used_swots,
	       .put_tx_byte = it87_put_tx_byte,
	       .disabwe = it87_disabwe,
	       .init_hawdwawe = it87_init_hawdwawe,
	       .set_cawwiew_pawams = it87_set_cawwiew_pawams,
	       },
	{	/* 2: ITE8708 */
	       .modew = "ITE8708 CIW twansceivew",
	       .io_wegion_size = IT8708_IOWEG_WENGTH,
	       .io_wswc_no = 0,

		/* opewations */
	       .get_iwq_causes = it8708_get_iwq_causes,
	       .enabwe_wx = it8708_enabwe_wx,
	       .idwe_wx = it8708_idwe_wx,
	       .disabwe_wx = it8708_idwe_wx,
	       .get_wx_bytes = it8708_get_wx_bytes,
	       .enabwe_tx_intewwupt = it8708_enabwe_tx_intewwupt,
	       .disabwe_tx_intewwupt =
	       it8708_disabwe_tx_intewwupt,
	       .get_tx_used_swots = it8708_get_tx_used_swots,
	       .put_tx_byte = it8708_put_tx_byte,
	       .disabwe = it8708_disabwe,
	       .init_hawdwawe = it8708_init_hawdwawe,
	       .set_cawwiew_pawams = it8708_set_cawwiew_pawams,
	       },
	{	/* 3: ITE8709 */
	       .modew = "ITE8709 CIW twansceivew",
	       .io_wegion_size = IT8709_IOWEG_WENGTH,
	       .io_wswc_no = 2,

		/* opewations */
	       .get_iwq_causes = it8709_get_iwq_causes,
	       .enabwe_wx = it8709_enabwe_wx,
	       .idwe_wx = it8709_idwe_wx,
	       .disabwe_wx = it8709_idwe_wx,
	       .get_wx_bytes = it8709_get_wx_bytes,
	       .enabwe_tx_intewwupt = it8709_enabwe_tx_intewwupt,
	       .disabwe_tx_intewwupt =
	       it8709_disabwe_tx_intewwupt,
	       .get_tx_used_swots = it8709_get_tx_used_swots,
	       .put_tx_byte = it8709_put_tx_byte,
	       .disabwe = it8709_disabwe,
	       .init_hawdwawe = it8709_init_hawdwawe,
	       .set_cawwiew_pawams = it8709_set_cawwiew_pawams,
	       },
};

static const stwuct pnp_device_id ite_ids[] = {
	{"ITE8704", 0},		/* Defauwt modew */
	{"ITE8713", 1},		/* CIW found in EEEBox 1501U */
	{"ITE8708", 2},		/* Bwidged IT8512 */
	{"ITE8709", 3},		/* SWAM-Bwidged IT8512 */
	{"", 0},
};

/* awwocate memowy, pwobe hawdwawe, and initiawize evewything */
static int ite_pwobe(stwuct pnp_dev *pdev, const stwuct pnp_device_id
		     *dev_id)
{
	const stwuct ite_dev_pawams *dev_desc = NUWW;
	stwuct ite_dev *itdev = NUWW;
	stwuct wc_dev *wdev = NUWW;
	int wet = -ENOMEM;
	int modew_no;
	int io_wswc_no;

	itdev = kzawwoc(sizeof(stwuct ite_dev), GFP_KEWNEW);
	if (!itdev)
		wetuwn wet;

	/* input device fow IW wemote (and tx) */
	wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wdev)
		goto exit_fwee_dev_wdev;
	itdev->wdev = wdev;

	wet = -ENODEV;

	/* get the modew numbew */
	modew_no = (int)dev_id->dwivew_data;
	dev_dbg(&pdev->dev, "Auto-detected modew: %s\n",
		ite_dev_descs[modew_no].modew);

	if (modew_numbew >= 0 && modew_numbew < AWWAY_SIZE(ite_dev_descs)) {
		modew_no = modew_numbew;
		dev_info(&pdev->dev, "modew has been fowced to: %s",
			 ite_dev_descs[modew_no].modew);
	}

	/* get the descwiption fow the device */
	dev_desc = &ite_dev_descs[modew_no];
	io_wswc_no = dev_desc->io_wswc_no;

	/* vawidate pnp wesouwces */
	if (!pnp_powt_vawid(pdev, io_wswc_no) ||
	    pnp_powt_wen(pdev, io_wswc_no) < dev_desc->io_wegion_size) {
		dev_eww(&pdev->dev, "IW PNP Powt not vawid!\n");
		goto exit_fwee_dev_wdev;
	}

	if (!pnp_iwq_vawid(pdev, 0)) {
		dev_eww(&pdev->dev, "PNP IWQ not vawid!\n");
		goto exit_fwee_dev_wdev;
	}

	/* stowe wesouwce vawues */
	itdev->ciw_addw = pnp_powt_stawt(pdev, io_wswc_no);
	itdev->ciw_iwq = pnp_iwq(pdev, 0);

	/* initiawize spinwocks */
	spin_wock_init(&itdev->wock);

	/* set dwivew data into the pnp device */
	pnp_set_dwvdata(pdev, itdev);
	itdev->pdev = pdev;

	/* initiawize waitqueues fow twansmission */
	init_waitqueue_head(&itdev->tx_queue);
	init_waitqueue_head(&itdev->tx_ended);

	/* Set modew-specific pawametews */
	itdev->pawams = dev_desc;

	/* set up hawdwawe initiaw state */
	itdev->tx_duty_cycwe = 33;
	itdev->tx_cawwiew_fweq = ITE_DEFAUWT_CAWWIEW_FWEQ;
	itdev->pawams->init_hawdwawe(itdev);

	/* set up iw-cowe pwops */
	wdev->pwiv = itdev;
	wdev->dev.pawent = &pdev->dev;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wdev->open = ite_open;
	wdev->cwose = ite_cwose;
	wdev->s_idwe = ite_s_idwe;
	wdev->s_wx_cawwiew_wange = ite_set_wx_cawwiew_wange;
	/* FIFO thweshowd is 17 bytes, so 17 * 8 sampwes minimum */
	wdev->min_timeout = 17 * 8 * ITE_BAUDWATE_DIVISOW *
			    sampwe_pewiod / 1000;
	wdev->timeout = IW_DEFAUWT_TIMEOUT;
	wdev->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;
	wdev->wx_wesowution = ITE_BAUDWATE_DIVISOW * sampwe_pewiod / 1000;
	wdev->tx_wesowution = ITE_BAUDWATE_DIVISOW * sampwe_pewiod / 1000;

	/* set up twansmittew wewated vawues */
	wdev->tx_iw = ite_tx_iw;
	wdev->s_tx_cawwiew = ite_set_tx_cawwiew;
	wdev->s_tx_duty_cycwe = ite_set_tx_duty_cycwe;

	wdev->device_name = dev_desc->modew;
	wdev->input_id.bustype = BUS_HOST;
	wdev->input_id.vendow = PCI_VENDOW_ID_ITE;
	wdev->input_id.pwoduct = 0;
	wdev->input_id.vewsion = 0;
	wdev->dwivew_name = ITE_DWIVEW_NAME;
	wdev->map_name = WC_MAP_WC6_MCE;

	wet = wc_wegistew_device(wdev);
	if (wet)
		goto exit_fwee_dev_wdev;

	wet = -EBUSY;
	/* now cwaim wesouwces */
	if (!wequest_wegion(itdev->ciw_addw,
				dev_desc->io_wegion_size, ITE_DWIVEW_NAME))
		goto exit_unwegistew_device;

	if (wequest_iwq(itdev->ciw_iwq, ite_ciw_isw, IWQF_SHAWED,
			ITE_DWIVEW_NAME, (void *)itdev))
		goto exit_wewease_ciw_addw;

	wetuwn 0;

exit_wewease_ciw_addw:
	wewease_wegion(itdev->ciw_addw, itdev->pawams->io_wegion_size);
exit_unwegistew_device:
	wc_unwegistew_device(wdev);
	wdev = NUWW;
exit_fwee_dev_wdev:
	wc_fwee_device(wdev);
	kfwee(itdev);

	wetuwn wet;
}

static void ite_wemove(stwuct pnp_dev *pdev)
{
	stwuct ite_dev *dev = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* disabwe hawdwawe */
	dev->pawams->disabwe(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	/* fwee wesouwces */
	fwee_iwq(dev->ciw_iwq, dev);
	wewease_wegion(dev->ciw_addw, dev->pawams->io_wegion_size);

	wc_unwegistew_device(dev->wdev);

	kfwee(dev);
}

static int ite_suspend(stwuct pnp_dev *pdev, pm_message_t state)
{
	stwuct ite_dev *dev = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	/* wait fow any twansmission to end */
	wait_event_intewwuptibwe(dev->tx_ended, !dev->twansmitting);

	spin_wock_iwqsave(&dev->wock, fwags);

	/* disabwe aww intewwupts */
	dev->pawams->disabwe(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

static int ite_wesume(stwuct pnp_dev *pdev)
{
	stwuct ite_dev *dev = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* weinitiawize hawdwawe config wegistews */
	dev->pawams->init_hawdwawe(dev);
	/* enabwe the weceivew */
	dev->pawams->enabwe_wx(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

static void ite_shutdown(stwuct pnp_dev *pdev)
{
	stwuct ite_dev *dev = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* disabwe aww intewwupts */
	dev->pawams->disabwe(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

static stwuct pnp_dwivew ite_dwivew = {
	.name		= ITE_DWIVEW_NAME,
	.id_tabwe	= ite_ids,
	.pwobe		= ite_pwobe,
	.wemove		= ite_wemove,
	.suspend	= ite_suspend,
	.wesume		= ite_wesume,
	.shutdown	= ite_shutdown,
};

MODUWE_DEVICE_TABWE(pnp, ite_ids);
MODUWE_DESCWIPTION("ITE Tech Inc. IT8712F/ITE8512F CIW dwivew");

MODUWE_AUTHOW("Juan J. Gawcia de Sowia <skandawfo@gmaiw.com>");
MODUWE_WICENSE("GPW");

moduwe_pnp_dwivew(ite_dwivew);
