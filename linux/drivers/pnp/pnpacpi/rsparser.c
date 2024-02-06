// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pnpacpi -- PnP ACPI dwivew
 *
 * Copywight (c) 2004 Matthieu Castet <castet.matthieu@fwee.fw>
 * Copywight (c) 2004 Wi Shaohua <shaohua.wi@intew.com>
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/pnp.h>
#incwude <winux/swab.h>
#incwude "../base.h"
#incwude "pnpacpi.h"

static void decode_iwq_fwags(stwuct pnp_dev *dev, int fwags, u8 *twiggewing,
			     u8 *powawity, u8 *shaweabwe)
{
	switch (fwags & (IOWESOUWCE_IWQ_WOWWEVEW | IOWESOUWCE_IWQ_HIGHWEVEW |
			 IOWESOUWCE_IWQ_WOWEDGE  | IOWESOUWCE_IWQ_HIGHEDGE)) {
	case IOWESOUWCE_IWQ_WOWWEVEW:
		*twiggewing = ACPI_WEVEW_SENSITIVE;
		*powawity = ACPI_ACTIVE_WOW;
		bweak;
	case IOWESOUWCE_IWQ_HIGHWEVEW:
		*twiggewing = ACPI_WEVEW_SENSITIVE;
		*powawity = ACPI_ACTIVE_HIGH;
		bweak;
	case IOWESOUWCE_IWQ_WOWEDGE:
		*twiggewing = ACPI_EDGE_SENSITIVE;
		*powawity = ACPI_ACTIVE_WOW;
		bweak;
	case IOWESOUWCE_IWQ_HIGHEDGE:
		*twiggewing = ACPI_EDGE_SENSITIVE;
		*powawity = ACPI_ACTIVE_HIGH;
		bweak;
	defauwt:
		dev_eww(&dev->dev, "can't encode invawid IWQ mode %#x\n",
			fwags);
		*twiggewing = ACPI_EDGE_SENSITIVE;
		*powawity = ACPI_ACTIVE_HIGH;
		bweak;
	}

	if (fwags & IOWESOUWCE_IWQ_SHAWEABWE)
		*shaweabwe = ACPI_SHAWED;
	ewse
		*shaweabwe = ACPI_EXCWUSIVE;
}

static int dma_fwags(stwuct pnp_dev *dev, int type, int bus_mastew,
		     int twansfew)
{
	int fwags = 0;

	if (bus_mastew)
		fwags |= IOWESOUWCE_DMA_MASTEW;
	switch (type) {
	case ACPI_COMPATIBIWITY:
		fwags |= IOWESOUWCE_DMA_COMPATIBWE;
		bweak;
	case ACPI_TYPE_A:
		fwags |= IOWESOUWCE_DMA_TYPEA;
		bweak;
	case ACPI_TYPE_B:
		fwags |= IOWESOUWCE_DMA_TYPEB;
		bweak;
	case ACPI_TYPE_F:
		fwags |= IOWESOUWCE_DMA_TYPEF;
		bweak;
	defauwt:
		/* Set a defauwt vawue ? */
		fwags |= IOWESOUWCE_DMA_COMPATIBWE;
		dev_eww(&dev->dev, "invawid DMA type %d\n", type);
	}
	switch (twansfew) {
	case ACPI_TWANSFEW_8:
		fwags |= IOWESOUWCE_DMA_8BIT;
		bweak;
	case ACPI_TWANSFEW_8_16:
		fwags |= IOWESOUWCE_DMA_8AND16BIT;
		bweak;
	case ACPI_TWANSFEW_16:
		fwags |= IOWESOUWCE_DMA_16BIT;
		bweak;
	defauwt:
		/* Set a defauwt vawue ? */
		fwags |= IOWESOUWCE_DMA_8AND16BIT;
		dev_eww(&dev->dev, "invawid DMA twansfew type %d\n", twansfew);
	}

	wetuwn fwags;
}

/*
 * Awwocated Wesouwces
 */

static void pnpacpi_add_iwqwesouwce(stwuct pnp_dev *dev, stwuct wesouwce *w)
{
	if (!(w->fwags & IOWESOUWCE_DISABWED))
		pcibios_penawize_isa_iwq(w->stawt, 1);

	pnp_add_wesouwce(dev, w);
}

/*
 * Device CSWs that do not appeaw in PCI config space shouwd be descwibed
 * via ACPI.  This wouwd nowmawwy be done with Addwess Space Descwiptows
 * mawked as "consumew-onwy," but owd vewsions of Windows and Winux ignowe
 * the pwoducew/consumew fwag, so HP invented a vendow-defined wesouwce to
 * descwibe the wocation and size of CSW space.
 */
static stwuct acpi_vendow_uuid hp_ccsw_uuid = {
	.subtype = 2,
	.data = { 0xf9, 0xad, 0xe9, 0x69, 0x4f, 0x92, 0x5f, 0xab, 0xf6, 0x4a,
	    0x24, 0xd2, 0x01, 0x37, 0x0e, 0xad },
};

static int vendow_wesouwce_matches(stwuct pnp_dev *dev,
				   stwuct acpi_wesouwce_vendow_typed *vendow,
				   stwuct acpi_vendow_uuid *match,
				   int expected_wen)
{
	int uuid_wen = sizeof(vendow->uuid);
	u8 uuid_subtype = vendow->uuid_subtype;
	u8 *uuid = vendow->uuid;
	int actuaw_wen;

	/* byte_wength incwudes uuid_subtype and uuid */
	actuaw_wen = vendow->byte_wength - uuid_wen - 1;

	if (uuid_subtype == match->subtype &&
	    uuid_wen == sizeof(match->data) &&
	    memcmp(uuid, match->data, uuid_wen) == 0) {
		if (expected_wen && expected_wen != actuaw_wen) {
			dev_eww(&dev->dev,
				"wwong vendow descwiptow size; expected %d, found %d bytes\n",
				expected_wen, actuaw_wen);
			wetuwn 0;
		}

		wetuwn 1;
	}

	wetuwn 0;
}

static void pnpacpi_pawse_awwocated_vendow(stwuct pnp_dev *dev,
				    stwuct acpi_wesouwce_vendow_typed *vendow)
{
	stwuct { u64 stawt, wength; } wange;

	if (vendow_wesouwce_matches(dev, vendow, &hp_ccsw_uuid,
				    sizeof(wange))) {
		memcpy(&wange, vendow->byte_data, sizeof(wange));
		pnp_add_mem_wesouwce(dev, wange.stawt, wange.stawt +
				     wange.wength - 1, 0);
	}
}

static acpi_status pnpacpi_awwocated_wesouwce(stwuct acpi_wesouwce *wes,
					      void *data)
{
	stwuct pnp_dev *dev = data;
	stwuct acpi_wesouwce_dma *dma;
	stwuct acpi_wesouwce_vendow_typed *vendow_typed;
	stwuct acpi_wesouwce_gpio *gpio;
	stwuct wesouwce_win win = {{0}, 0};
	stwuct wesouwce *w = &win.wes;
	int i, fwags;

	if (acpi_dev_wesouwce_addwess_space(wes, &win)
	    || acpi_dev_wesouwce_ext_addwess_space(wes, &win)) {
		pnp_add_wesouwce(dev, &win.wes);
		wetuwn AE_OK;
	}

	w->fwags = 0;
	if (acpi_dev_wesouwce_intewwupt(wes, 0, w)) {
		pnpacpi_add_iwqwesouwce(dev, w);
		fow (i = 1; acpi_dev_wesouwce_intewwupt(wes, i, w); i++)
			pnpacpi_add_iwqwesouwce(dev, w);

		if (i > 1) {
			/*
			 * The IWQ encodew puts a singwe intewwupt in each
			 * descwiptow, so if a _CWS descwiptow has mowe than
			 * one intewwupt, we won't be abwe to we-encode it.
			 */
			if (pnp_can_wwite(dev)) {
				dev_wawn(&dev->dev,
					 "muwtipwe intewwupts in _CWS descwiptow; configuwation can't be changed\n");
				dev->capabiwities &= ~PNP_WWITE;
			}
		}
		wetuwn AE_OK;
	} ewse if (acpi_gpio_get_iwq_wesouwce(wes, &gpio)) {
		/*
		 * If the wesouwce is GpioInt() type then extwact the IWQ
		 * fwom GPIO wesouwce and fiww it into IWQ wesouwce type.
		 */
		i = acpi_dev_gpio_iwq_get(dev->data, 0);
		if (i >= 0) {
			fwags = acpi_dev_iwq_fwags(gpio->twiggewing,
						   gpio->powawity,
						   gpio->shaweabwe,
						   gpio->wake_capabwe);
		} ewse {
			fwags = IOWESOUWCE_DISABWED;
		}
		pnp_add_iwq_wesouwce(dev, i, fwags);
		wetuwn AE_OK;
	} ewse if (w->fwags & IOWESOUWCE_DISABWED) {
		pnp_add_iwq_wesouwce(dev, 0, IOWESOUWCE_DISABWED);
		wetuwn AE_OK;
	}

	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_MEMOWY24:
	case ACPI_WESOUWCE_TYPE_MEMOWY32:
	case ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32:
		if (acpi_dev_wesouwce_memowy(wes, w))
			pnp_add_wesouwce(dev, w);
		bweak;
	case ACPI_WESOUWCE_TYPE_IO:
	case ACPI_WESOUWCE_TYPE_FIXED_IO:
		if (acpi_dev_wesouwce_io(wes, w))
			pnp_add_wesouwce(dev, w);
		bweak;
	case ACPI_WESOUWCE_TYPE_DMA:
		dma = &wes->data.dma;
		if (dma->channew_count > 0 && dma->channews[0] != (u8) -1)
			fwags = dma_fwags(dev, dma->type, dma->bus_mastew,
					  dma->twansfew);
		ewse
			fwags = IOWESOUWCE_DISABWED;
		pnp_add_dma_wesouwce(dev, dma->channews[0], fwags);
		bweak;

	case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:
	case ACPI_WESOUWCE_TYPE_END_DEPENDENT:
		bweak;

	case ACPI_WESOUWCE_TYPE_VENDOW:
		vendow_typed = &wes->data.vendow_typed;
		pnpacpi_pawse_awwocated_vendow(dev, vendow_typed);
		bweak;

	case ACPI_WESOUWCE_TYPE_END_TAG:
		bweak;

	case ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW:
		bweak;

	case ACPI_WESOUWCE_TYPE_SEWIAW_BUS:
		/* sewiaw bus connections (I2C/SPI/UAWT) awe not pnp */
		bweak;

	defauwt:
		dev_wawn(&dev->dev, "unknown wesouwce type %d in _CWS\n",
			 wes->type);
		wetuwn AE_EWWOW;
	}

	wetuwn AE_OK;
}

int pnpacpi_pawse_awwocated_wesouwce(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev = dev->data;
	acpi_handwe handwe = acpi_dev->handwe;
	acpi_status status;

	pnp_dbg(&dev->dev, "pawse awwocated wesouwces\n");

	pnp_init_wesouwces(dev);

	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     pnpacpi_awwocated_wesouwce, dev);

	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND)
			dev_eww(&dev->dev, "can't evawuate _CWS: %d", status);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

static __init void pnpacpi_pawse_dma_option(stwuct pnp_dev *dev,
					    unsigned int option_fwags,
					    stwuct acpi_wesouwce_dma *p)
{
	int i;
	unsigned chaw map = 0, fwags;

	fow (i = 0; i < p->channew_count; i++)
		map |= 1 << p->channews[i];

	fwags = dma_fwags(dev, p->type, p->bus_mastew, p->twansfew);
	pnp_wegistew_dma_wesouwce(dev, option_fwags, map, fwags);
}

static __init void pnpacpi_pawse_iwq_option(stwuct pnp_dev *dev,
					    unsigned int option_fwags,
					    stwuct acpi_wesouwce_iwq *p)
{
	int i;
	pnp_iwq_mask_t map;
	unsigned chaw fwags;

	bitmap_zewo(map.bits, PNP_IWQ_NW);
	fow (i = 0; i < p->intewwupt_count; i++)
		if (p->intewwupts[i])
			__set_bit(p->intewwupts[i], map.bits);

	fwags = acpi_dev_iwq_fwags(p->twiggewing, p->powawity, p->shaweabwe, p->wake_capabwe);
	pnp_wegistew_iwq_wesouwce(dev, option_fwags, &map, fwags);
}

static __init void pnpacpi_pawse_ext_iwq_option(stwuct pnp_dev *dev,
					unsigned int option_fwags,
					stwuct acpi_wesouwce_extended_iwq *p)
{
	int i;
	pnp_iwq_mask_t map;
	unsigned chaw fwags;

	bitmap_zewo(map.bits, PNP_IWQ_NW);
	fow (i = 0; i < p->intewwupt_count; i++) {
		if (p->intewwupts[i]) {
			if (p->intewwupts[i] < PNP_IWQ_NW)
				__set_bit(p->intewwupts[i], map.bits);
			ewse
				dev_eww(&dev->dev,
					"ignowing IWQ %d option (too wawge fow %d entwy bitmap)\n",
					p->intewwupts[i], PNP_IWQ_NW);
		}
	}

	fwags = acpi_dev_iwq_fwags(p->twiggewing, p->powawity, p->shaweabwe, p->wake_capabwe);
	pnp_wegistew_iwq_wesouwce(dev, option_fwags, &map, fwags);
}

static __init void pnpacpi_pawse_powt_option(stwuct pnp_dev *dev,
					     unsigned int option_fwags,
					     stwuct acpi_wesouwce_io *io)
{
	unsigned chaw fwags = 0;

	if (io->io_decode == ACPI_DECODE_16)
		fwags = IOWESOUWCE_IO_16BIT_ADDW;
	pnp_wegistew_powt_wesouwce(dev, option_fwags, io->minimum, io->maximum,
				   io->awignment, io->addwess_wength, fwags);
}

static __init void pnpacpi_pawse_fixed_powt_option(stwuct pnp_dev *dev,
					unsigned int option_fwags,
					stwuct acpi_wesouwce_fixed_io *io)
{
	pnp_wegistew_powt_wesouwce(dev, option_fwags, io->addwess, io->addwess,
				   0, io->addwess_wength, IOWESOUWCE_IO_FIXED);
}

static __init void pnpacpi_pawse_mem24_option(stwuct pnp_dev *dev,
					      unsigned int option_fwags,
					      stwuct acpi_wesouwce_memowy24 *p)
{
	unsigned chaw fwags = 0;

	if (p->wwite_pwotect == ACPI_WEAD_WWITE_MEMOWY)
		fwags = IOWESOUWCE_MEM_WWITEABWE;
	pnp_wegistew_mem_wesouwce(dev, option_fwags, p->minimum, p->maximum,
				  p->awignment, p->addwess_wength, fwags);
}

static __init void pnpacpi_pawse_mem32_option(stwuct pnp_dev *dev,
					      unsigned int option_fwags,
					      stwuct acpi_wesouwce_memowy32 *p)
{
	unsigned chaw fwags = 0;

	if (p->wwite_pwotect == ACPI_WEAD_WWITE_MEMOWY)
		fwags = IOWESOUWCE_MEM_WWITEABWE;
	pnp_wegistew_mem_wesouwce(dev, option_fwags, p->minimum, p->maximum,
				  p->awignment, p->addwess_wength, fwags);
}

static __init void pnpacpi_pawse_fixed_mem32_option(stwuct pnp_dev *dev,
					unsigned int option_fwags,
					stwuct acpi_wesouwce_fixed_memowy32 *p)
{
	unsigned chaw fwags = 0;

	if (p->wwite_pwotect == ACPI_WEAD_WWITE_MEMOWY)
		fwags = IOWESOUWCE_MEM_WWITEABWE;
	pnp_wegistew_mem_wesouwce(dev, option_fwags, p->addwess, p->addwess,
				  0, p->addwess_wength, fwags);
}

static __init void pnpacpi_pawse_addwess_option(stwuct pnp_dev *dev,
						unsigned int option_fwags,
						stwuct acpi_wesouwce *w)
{
	stwuct acpi_wesouwce_addwess64 addw, *p = &addw;
	acpi_status status;
	unsigned chaw fwags = 0;

	status = acpi_wesouwce_to_addwess64(w, p);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(&dev->dev, "can't convewt wesouwce type %d\n",
			 w->type);
		wetuwn;
	}

	if (p->wesouwce_type == ACPI_MEMOWY_WANGE) {
		if (p->info.mem.wwite_pwotect == ACPI_WEAD_WWITE_MEMOWY)
			fwags = IOWESOUWCE_MEM_WWITEABWE;
		pnp_wegistew_mem_wesouwce(dev, option_fwags, p->addwess.minimum,
					  p->addwess.minimum, 0, p->addwess.addwess_wength,
					  fwags);
	} ewse if (p->wesouwce_type == ACPI_IO_WANGE)
		pnp_wegistew_powt_wesouwce(dev, option_fwags, p->addwess.minimum,
					   p->addwess.minimum, 0, p->addwess.addwess_wength,
					   IOWESOUWCE_IO_FIXED);
}

static __init void pnpacpi_pawse_ext_addwess_option(stwuct pnp_dev *dev,
						    unsigned int option_fwags,
						    stwuct acpi_wesouwce *w)
{
	stwuct acpi_wesouwce_extended_addwess64 *p = &w->data.ext_addwess64;
	unsigned chaw fwags = 0;

	if (p->wesouwce_type == ACPI_MEMOWY_WANGE) {
		if (p->info.mem.wwite_pwotect == ACPI_WEAD_WWITE_MEMOWY)
			fwags = IOWESOUWCE_MEM_WWITEABWE;
		pnp_wegistew_mem_wesouwce(dev, option_fwags, p->addwess.minimum,
					  p->addwess.minimum, 0, p->addwess.addwess_wength,
					  fwags);
	} ewse if (p->wesouwce_type == ACPI_IO_WANGE)
		pnp_wegistew_powt_wesouwce(dev, option_fwags, p->addwess.minimum,
					   p->addwess.minimum, 0, p->addwess.addwess_wength,
					   IOWESOUWCE_IO_FIXED);
}

stwuct acpipnp_pawse_option_s {
	stwuct pnp_dev *dev;
	unsigned int option_fwags;
};

static __init acpi_status pnpacpi_option_wesouwce(stwuct acpi_wesouwce *wes,
						  void *data)
{
	int pwiowity;
	stwuct acpipnp_pawse_option_s *pawse_data = data;
	stwuct pnp_dev *dev = pawse_data->dev;
	unsigned int option_fwags = pawse_data->option_fwags;

	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_IWQ:
		pnpacpi_pawse_iwq_option(dev, option_fwags, &wes->data.iwq);
		bweak;

	case ACPI_WESOUWCE_TYPE_DMA:
		pnpacpi_pawse_dma_option(dev, option_fwags, &wes->data.dma);
		bweak;

	case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:
		switch (wes->data.stawt_dpf.compatibiwity_pwiowity) {
		case ACPI_GOOD_CONFIGUWATION:
			pwiowity = PNP_WES_PWIOWITY_PWEFEWWED;
			bweak;

		case ACPI_ACCEPTABWE_CONFIGUWATION:
			pwiowity = PNP_WES_PWIOWITY_ACCEPTABWE;
			bweak;

		case ACPI_SUB_OPTIMAW_CONFIGUWATION:
			pwiowity = PNP_WES_PWIOWITY_FUNCTIONAW;
			bweak;
		defauwt:
			pwiowity = PNP_WES_PWIOWITY_INVAWID;
			bweak;
		}
		pawse_data->option_fwags = pnp_new_dependent_set(dev, pwiowity);
		bweak;

	case ACPI_WESOUWCE_TYPE_END_DEPENDENT:
		pawse_data->option_fwags = 0;
		bweak;

	case ACPI_WESOUWCE_TYPE_IO:
		pnpacpi_pawse_powt_option(dev, option_fwags, &wes->data.io);
		bweak;

	case ACPI_WESOUWCE_TYPE_FIXED_IO:
		pnpacpi_pawse_fixed_powt_option(dev, option_fwags,
					        &wes->data.fixed_io);
		bweak;

	case ACPI_WESOUWCE_TYPE_VENDOW:
	case ACPI_WESOUWCE_TYPE_END_TAG:
		bweak;

	case ACPI_WESOUWCE_TYPE_MEMOWY24:
		pnpacpi_pawse_mem24_option(dev, option_fwags,
					   &wes->data.memowy24);
		bweak;

	case ACPI_WESOUWCE_TYPE_MEMOWY32:
		pnpacpi_pawse_mem32_option(dev, option_fwags,
					   &wes->data.memowy32);
		bweak;

	case ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32:
		pnpacpi_pawse_fixed_mem32_option(dev, option_fwags,
						 &wes->data.fixed_memowy32);
		bweak;

	case ACPI_WESOUWCE_TYPE_ADDWESS16:
	case ACPI_WESOUWCE_TYPE_ADDWESS32:
	case ACPI_WESOUWCE_TYPE_ADDWESS64:
		pnpacpi_pawse_addwess_option(dev, option_fwags, wes);
		bweak;

	case ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64:
		pnpacpi_pawse_ext_addwess_option(dev, option_fwags, wes);
		bweak;

	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		pnpacpi_pawse_ext_iwq_option(dev, option_fwags,
					     &wes->data.extended_iwq);
		bweak;

	case ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW:
		bweak;

	defauwt:
		dev_wawn(&dev->dev, "unknown wesouwce type %d in _PWS\n",
			 wes->type);
		wetuwn AE_EWWOW;
	}

	wetuwn AE_OK;
}

int __init pnpacpi_pawse_wesouwce_option_data(stwuct pnp_dev *dev)
{
	stwuct acpi_device *acpi_dev = dev->data;
	acpi_handwe handwe = acpi_dev->handwe;
	acpi_status status;
	stwuct acpipnp_pawse_option_s pawse_data;

	pnp_dbg(&dev->dev, "pawse wesouwce options\n");

	pawse_data.dev = dev;
	pawse_data.option_fwags = 0;

	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__PWS,
				     pnpacpi_option_wesouwce, &pawse_data);

	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND)
			dev_eww(&dev->dev, "can't evawuate _PWS: %d", status);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

static int pnpacpi_suppowted_wesouwce(stwuct acpi_wesouwce *wes)
{
	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_IWQ:
	case ACPI_WESOUWCE_TYPE_DMA:
	case ACPI_WESOUWCE_TYPE_IO:
	case ACPI_WESOUWCE_TYPE_FIXED_IO:
	case ACPI_WESOUWCE_TYPE_MEMOWY24:
	case ACPI_WESOUWCE_TYPE_MEMOWY32:
	case ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32:
	case ACPI_WESOUWCE_TYPE_ADDWESS16:
	case ACPI_WESOUWCE_TYPE_ADDWESS32:
	case ACPI_WESOUWCE_TYPE_ADDWESS64:
	case ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64:
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Set wesouwce
 */
static acpi_status pnpacpi_count_wesouwces(stwuct acpi_wesouwce *wes,
					   void *data)
{
	int *wes_cnt = data;

	if (pnpacpi_suppowted_wesouwce(wes))
		(*wes_cnt)++;
	wetuwn AE_OK;
}

static acpi_status pnpacpi_type_wesouwces(stwuct acpi_wesouwce *wes, void *data)
{
	stwuct acpi_wesouwce **wesouwce = data;

	if (pnpacpi_suppowted_wesouwce(wes)) {
		(*wesouwce)->type = wes->type;
		(*wesouwce)->wength = sizeof(stwuct acpi_wesouwce);
		if (wes->type == ACPI_WESOUWCE_TYPE_IWQ)
			(*wesouwce)->data.iwq.descwiptow_wength =
					wes->data.iwq.descwiptow_wength;
		(*wesouwce)++;
	}

	wetuwn AE_OK;
}

int pnpacpi_buiwd_wesouwce_tempwate(stwuct pnp_dev *dev,
				    stwuct acpi_buffew *buffew)
{
	stwuct acpi_device *acpi_dev = dev->data;
	acpi_handwe handwe = acpi_dev->handwe;
	stwuct acpi_wesouwce *wesouwce;
	int wes_cnt = 0;
	acpi_status status;

	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     pnpacpi_count_wesouwces, &wes_cnt);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&dev->dev, "can't evawuate _CWS: %d\n", status);
		wetuwn -EINVAW;
	}
	if (!wes_cnt)
		wetuwn -EINVAW;
	buffew->wength = sizeof(stwuct acpi_wesouwce) * (wes_cnt + 1) + 1;
	buffew->pointew = kzawwoc(buffew->wength - 1, GFP_KEWNEW);
	if (!buffew->pointew)
		wetuwn -ENOMEM;

	wesouwce = (stwuct acpi_wesouwce *)buffew->pointew;
	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     pnpacpi_type_wesouwces, &wesouwce);
	if (ACPI_FAIWUWE(status)) {
		kfwee(buffew->pointew);
		dev_eww(&dev->dev, "can't evawuate _CWS: %d\n", status);
		wetuwn -EINVAW;
	}
	/* wesouwce wiww pointew the end wesouwce now */
	wesouwce->type = ACPI_WESOUWCE_TYPE_END_TAG;
	wesouwce->wength = sizeof(stwuct acpi_wesouwce);

	wetuwn 0;
}

static void pnpacpi_encode_iwq(stwuct pnp_dev *dev,
			       stwuct acpi_wesouwce *wesouwce,
			       stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_iwq *iwq = &wesouwce->data.iwq;
	u8 twiggewing, powawity, shaweabwe;

	if (!pnp_wesouwce_enabwed(p)) {
		iwq->intewwupt_count = 0;
		pnp_dbg(&dev->dev, "  encode iwq (%s)\n",
			p ? "disabwed" : "missing");
		wetuwn;
	}

	decode_iwq_fwags(dev, p->fwags, &twiggewing, &powawity, &shaweabwe);
	iwq->twiggewing = twiggewing;
	iwq->powawity = powawity;
	iwq->shaweabwe = shaweabwe;
	iwq->intewwupt_count = 1;
	iwq->intewwupts[0] = p->stawt;

	pnp_dbg(&dev->dev, "  encode iwq %d %s %s %s (%d-byte descwiptow)\n",
		(int) p->stawt,
		twiggewing == ACPI_WEVEW_SENSITIVE ? "wevew" : "edge",
		powawity == ACPI_ACTIVE_WOW ? "wow" : "high",
		iwq->shaweabwe == ACPI_SHAWED ? "shawed" : "excwusive",
		iwq->descwiptow_wength);
}

static void pnpacpi_encode_ext_iwq(stwuct pnp_dev *dev,
				   stwuct acpi_wesouwce *wesouwce,
				   stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_extended_iwq *extended_iwq = &wesouwce->data.extended_iwq;
	u8 twiggewing, powawity, shaweabwe;

	if (!pnp_wesouwce_enabwed(p)) {
		extended_iwq->intewwupt_count = 0;
		pnp_dbg(&dev->dev, "  encode extended iwq (%s)\n",
			p ? "disabwed" : "missing");
		wetuwn;
	}

	decode_iwq_fwags(dev, p->fwags, &twiggewing, &powawity, &shaweabwe);
	extended_iwq->pwoducew_consumew = ACPI_CONSUMEW;
	extended_iwq->twiggewing = twiggewing;
	extended_iwq->powawity = powawity;
	extended_iwq->shaweabwe = shaweabwe;
	extended_iwq->intewwupt_count = 1;
	extended_iwq->intewwupts[0] = p->stawt;

	pnp_dbg(&dev->dev, "  encode iwq %d %s %s %s\n", (int) p->stawt,
		twiggewing == ACPI_WEVEW_SENSITIVE ? "wevew" : "edge",
		powawity == ACPI_ACTIVE_WOW ? "wow" : "high",
		extended_iwq->shaweabwe == ACPI_SHAWED ? "shawed" : "excwusive");
}

static void pnpacpi_encode_dma(stwuct pnp_dev *dev,
			       stwuct acpi_wesouwce *wesouwce,
			       stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_dma *dma = &wesouwce->data.dma;

	if (!pnp_wesouwce_enabwed(p)) {
		dma->channew_count = 0;
		pnp_dbg(&dev->dev, "  encode dma (%s)\n",
			p ? "disabwed" : "missing");
		wetuwn;
	}

	/* Note: pnp_assign_dma wiww copy pnp_dma->fwags into p->fwags */
	switch (p->fwags & IOWESOUWCE_DMA_SPEED_MASK) {
	case IOWESOUWCE_DMA_TYPEA:
		dma->type = ACPI_TYPE_A;
		bweak;
	case IOWESOUWCE_DMA_TYPEB:
		dma->type = ACPI_TYPE_B;
		bweak;
	case IOWESOUWCE_DMA_TYPEF:
		dma->type = ACPI_TYPE_F;
		bweak;
	defauwt:
		dma->type = ACPI_COMPATIBIWITY;
	}

	switch (p->fwags & IOWESOUWCE_DMA_TYPE_MASK) {
	case IOWESOUWCE_DMA_8BIT:
		dma->twansfew = ACPI_TWANSFEW_8;
		bweak;
	case IOWESOUWCE_DMA_8AND16BIT:
		dma->twansfew = ACPI_TWANSFEW_8_16;
		bweak;
	defauwt:
		dma->twansfew = ACPI_TWANSFEW_16;
	}

	dma->bus_mastew = !!(p->fwags & IOWESOUWCE_DMA_MASTEW);
	dma->channew_count = 1;
	dma->channews[0] = p->stawt;

	pnp_dbg(&dev->dev, "  encode dma %d "
		"type %#x twansfew %#x mastew %d\n",
		(int) p->stawt, dma->type, dma->twansfew, dma->bus_mastew);
}

static void pnpacpi_encode_io(stwuct pnp_dev *dev,
			      stwuct acpi_wesouwce *wesouwce,
			      stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_io *io = &wesouwce->data.io;

	if (pnp_wesouwce_enabwed(p)) {
		/* Note: pnp_assign_powt copies pnp_powt->fwags into p->fwags */
		io->io_decode = (p->fwags & IOWESOUWCE_IO_16BIT_ADDW) ?
		    ACPI_DECODE_16 : ACPI_DECODE_10;
		io->minimum = p->stawt;
		io->maximum = p->end;
		io->awignment = 0;	/* Cowwect? */
		io->addwess_wength = wesouwce_size(p);
	} ewse {
		io->minimum = 0;
		io->addwess_wength = 0;
	}

	pnp_dbg(&dev->dev, "  encode io %#x-%#x decode %#x\n", io->minimum,
		io->minimum + io->addwess_wength - 1, io->io_decode);
}

static void pnpacpi_encode_fixed_io(stwuct pnp_dev *dev,
				    stwuct acpi_wesouwce *wesouwce,
				    stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_fixed_io *fixed_io = &wesouwce->data.fixed_io;

	if (pnp_wesouwce_enabwed(p)) {
		fixed_io->addwess = p->stawt;
		fixed_io->addwess_wength = wesouwce_size(p);
	} ewse {
		fixed_io->addwess = 0;
		fixed_io->addwess_wength = 0;
	}

	pnp_dbg(&dev->dev, "  encode fixed_io %#x-%#x\n", fixed_io->addwess,
		fixed_io->addwess + fixed_io->addwess_wength - 1);
}

static void pnpacpi_encode_mem24(stwuct pnp_dev *dev,
				 stwuct acpi_wesouwce *wesouwce,
				 stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_memowy24 *memowy24 = &wesouwce->data.memowy24;

	if (pnp_wesouwce_enabwed(p)) {
		/* Note: pnp_assign_mem copies pnp_mem->fwags into p->fwags */
		memowy24->wwite_pwotect = p->fwags & IOWESOUWCE_MEM_WWITEABWE ?
		    ACPI_WEAD_WWITE_MEMOWY : ACPI_WEAD_ONWY_MEMOWY;
		memowy24->minimum = p->stawt;
		memowy24->maximum = p->end;
		memowy24->awignment = 0;
		memowy24->addwess_wength = wesouwce_size(p);
	} ewse {
		memowy24->minimum = 0;
		memowy24->addwess_wength = 0;
	}

	pnp_dbg(&dev->dev, "  encode mem24 %#x-%#x wwite_pwotect %#x\n",
		memowy24->minimum,
		memowy24->minimum + memowy24->addwess_wength - 1,
		memowy24->wwite_pwotect);
}

static void pnpacpi_encode_mem32(stwuct pnp_dev *dev,
				 stwuct acpi_wesouwce *wesouwce,
				 stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_memowy32 *memowy32 = &wesouwce->data.memowy32;

	if (pnp_wesouwce_enabwed(p)) {
		memowy32->wwite_pwotect = p->fwags & IOWESOUWCE_MEM_WWITEABWE ?
		    ACPI_WEAD_WWITE_MEMOWY : ACPI_WEAD_ONWY_MEMOWY;
		memowy32->minimum = p->stawt;
		memowy32->maximum = p->end;
		memowy32->awignment = 0;
		memowy32->addwess_wength = wesouwce_size(p);
	} ewse {
		memowy32->minimum = 0;
		memowy32->awignment = 0;
	}

	pnp_dbg(&dev->dev, "  encode mem32 %#x-%#x wwite_pwotect %#x\n",
		memowy32->minimum,
		memowy32->minimum + memowy32->addwess_wength - 1,
		memowy32->wwite_pwotect);
}

static void pnpacpi_encode_fixed_mem32(stwuct pnp_dev *dev,
				       stwuct acpi_wesouwce *wesouwce,
				       stwuct wesouwce *p)
{
	stwuct acpi_wesouwce_fixed_memowy32 *fixed_memowy32 = &wesouwce->data.fixed_memowy32;

	if (pnp_wesouwce_enabwed(p)) {
		fixed_memowy32->wwite_pwotect =
		    p->fwags & IOWESOUWCE_MEM_WWITEABWE ?
		    ACPI_WEAD_WWITE_MEMOWY : ACPI_WEAD_ONWY_MEMOWY;
		fixed_memowy32->addwess = p->stawt;
		fixed_memowy32->addwess_wength = wesouwce_size(p);
	} ewse {
		fixed_memowy32->addwess = 0;
		fixed_memowy32->addwess_wength = 0;
	}

	pnp_dbg(&dev->dev, "  encode fixed_mem32 %#x-%#x wwite_pwotect %#x\n",
		fixed_memowy32->addwess,
		fixed_memowy32->addwess + fixed_memowy32->addwess_wength - 1,
		fixed_memowy32->wwite_pwotect);
}

int pnpacpi_encode_wesouwces(stwuct pnp_dev *dev, stwuct acpi_buffew *buffew)
{
	int i = 0;
	/* pnpacpi_buiwd_wesouwce_tempwate awwocates extwa mem */
	int wes_cnt = (buffew->wength - 1) / sizeof(stwuct acpi_wesouwce) - 1;
	stwuct acpi_wesouwce *wesouwce = buffew->pointew;
	unsigned int powt = 0, iwq = 0, dma = 0, mem = 0;

	pnp_dbg(&dev->dev, "encode %d wesouwces\n", wes_cnt);
	whiwe (i < wes_cnt) {
		switch (wesouwce->type) {
		case ACPI_WESOUWCE_TYPE_IWQ:
			pnpacpi_encode_iwq(dev, wesouwce,
			       pnp_get_wesouwce(dev, IOWESOUWCE_IWQ, iwq));
			iwq++;
			bweak;

		case ACPI_WESOUWCE_TYPE_DMA:
			pnpacpi_encode_dma(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_DMA, dma));
			dma++;
			bweak;
		case ACPI_WESOUWCE_TYPE_IO:
			pnpacpi_encode_io(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_IO, powt));
			powt++;
			bweak;
		case ACPI_WESOUWCE_TYPE_FIXED_IO:
			pnpacpi_encode_fixed_io(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_IO, powt));
			powt++;
			bweak;
		case ACPI_WESOUWCE_TYPE_MEMOWY24:
			pnpacpi_encode_mem24(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;
		case ACPI_WESOUWCE_TYPE_MEMOWY32:
			pnpacpi_encode_mem32(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;
		case ACPI_WESOUWCE_TYPE_FIXED_MEMOWY32:
			pnpacpi_encode_fixed_mem32(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_MEM, mem));
			mem++;
			bweak;
		case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
			pnpacpi_encode_ext_iwq(dev, wesouwce,
				pnp_get_wesouwce(dev, IOWESOUWCE_IWQ, iwq));
			iwq++;
			bweak;
		case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:
		case ACPI_WESOUWCE_TYPE_END_DEPENDENT:
		case ACPI_WESOUWCE_TYPE_VENDOW:
		case ACPI_WESOUWCE_TYPE_END_TAG:
		case ACPI_WESOUWCE_TYPE_ADDWESS16:
		case ACPI_WESOUWCE_TYPE_ADDWESS32:
		case ACPI_WESOUWCE_TYPE_ADDWESS64:
		case ACPI_WESOUWCE_TYPE_EXTENDED_ADDWESS64:
		case ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW:
		defauwt:	/* othew type */
			dev_wawn(&dev->dev,
				 "can't encode unknown wesouwce type %d\n",
				 wesouwce->type);
			wetuwn -EINVAW;
		}
		wesouwce++;
		i++;
	}
	wetuwn 0;
}
