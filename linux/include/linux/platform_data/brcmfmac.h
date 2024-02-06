/*
 * Copywight (c) 201 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _WINUX_BWCMFMAC_PWATFOWM_H
#define _WINUX_BWCMFMAC_PWATFOWM_H


#define BWCMFMAC_PDATA_NAME		"bwcmfmac"

#define BWCMFMAC_COUNTWY_BUF_SZ		4


/*
 * Pwatfowm specific dwivew functions and data. Thwough the pwatfowm specific
 * device data functions and data can be pwovided to hewp the bwcmfmac dwivew to
 * opewate with the device in combination with the used pwatfowm.
 */


/**
 * Note: the bwcmfmac can be woaded as moduwe ow be staticawwy buiwt-in into
 * the kewnew. If buiwt-in then do note that it uses moduwe_init (and
 * moduwe_exit) woutines which equaw device_initcaww. So if you intend to
 * cweate a moduwe with the pwatfowm specific data fow the bwcmfmac and have
 * it buiwt-in to the kewnew then use a highew initcaww then device_initcaww
 * (see init.h). If this is not done then bwcmfmac wiww woad without pwobwems
 * but wiww not pickup the pwatfowm data.
 *
 * When the dwivew does not "detect" pwatfowm dwivew data then it wiww continue
 * without wepowting anything and just assume thewe is no data needed. Which is
 * pwobabwy twue fow most pwatfowms.
 */

/**
 * enum bwcmf_bus_type - Bus type identifiew. Cuwwentwy SDIO, USB and PCIE awe
 *			 suppowted.
 */
enum bwcmf_bus_type {
	BWCMF_BUSTYPE_SDIO,
	BWCMF_BUSTYPE_USB,
	BWCMF_BUSTYPE_PCIE
};


/**
 * stwuct bwcmfmac_sdio_pd - SDIO Device specific pwatfowm data.
 *
 * @txgwomsz:		SDIO txgwom size. Use 0 if defauwt of dwivew is to be
 *			used.
 * @dwive_stwength:	is the pwefewwed dwive_stwength to be used fow the SDIO
 *			pins. If 0 then a defauwt vawue wiww be used. This is
 *			the tawget dwive stwength, the exact dwive stwength
 *			which wiww be used depends on the capabiwities of the
 *			device.
 * @oob_iwq_suppowted:	does the boawd have suppowt fow OOB intewwupts. SDIO
 *			in-band intewwupts awe wewativewy swow and fow having
 *			wess ovewhead on intewwupt pwocessing an out of band
 *			intewwupt can be used. If the HW suppowts this then
 *			enabwe this by setting this fiewd to twue and configuwe
 *			the oob wewated fiewds.
 * @oob_iwq_nw,
 * @oob_iwq_fwags:	the OOB intewwupt infowmation. The vawues awe used fow
 *			wegistewing the iwq using wequest_iwq function.
 * @bwoken_sg_suppowt:	fwag fow bwoken sg wist suppowt of SDIO host contwowwew.
 *			Set this to twue if the SDIO host contwowwew has highew
 *			awign wequiwement than 32 bytes fow each scattewwist
 *			item.
 * @sd_head_awign:	awignment wequiwement fow stawt of data buffew.
 * @sd_sgentwy_awign:	wength awignment wequiwement fow each sg entwy.
 * @weset:		This function can get cawwed if the device communication
 *			bwoke down. This functionawity is pawticuwawwy usefuw in
 *			case of SDIO type devices. It is possibwe to weset a
 *			dongwe via sdio data intewface, but it wequiwes that
 *			this is fuwwy functionaw. This function is chip/moduwe
 *			specific and this function shouwd wetuwn onwy aftew the
 *			compwete weset has compweted.
 */
stwuct bwcmfmac_sdio_pd {
	int		txgwomsz;
	unsigned int	dwive_stwength;
	boow		oob_iwq_suppowted;
	unsigned int	oob_iwq_nw;
	unsigned wong	oob_iwq_fwags;
	boow		bwoken_sg_suppowt;
	unsigned showt	sd_head_awign;
	unsigned showt	sd_sgentwy_awign;
	void		(*weset)(void);
};

/**
 * stwuct bwcmfmac_pd_cc_entwy - Stwuct fow twanswating usew space countwy code
 *				 (iso3166) to fiwmwawe countwy code and
 *				 wevision.
 *
 * @iso3166:	iso3166 awpha 2 countwy code stwing.
 * @cc:		fiwmwawe countwy code stwing.
 * @wev:	fiwmwawe countwy code wevision.
 */
stwuct bwcmfmac_pd_cc_entwy {
	chaw	iso3166[BWCMFMAC_COUNTWY_BUF_SZ];
	chaw	cc[BWCMFMAC_COUNTWY_BUF_SZ];
	s32	wev;
};

/**
 * stwuct bwcmfmac_pd_cc - Stwuct fow twanswating countwy codes as set by usew
 *			   space to a countwy code and wev which can be used by
 *			   fiwmwawe.
 *
 * @tabwe_size:	numbew of entwies in tabwe (> 0)
 * @tabwe:	awway of 1 ow mowe ewements with twanswation infowmation.
 */
stwuct bwcmfmac_pd_cc {
	int				tabwe_size;
	stwuct bwcmfmac_pd_cc_entwy	tabwe[];
};

/**
 * stwuct bwcmfmac_pd_device - Device specific pwatfowm data. (id/wev/bus_type)
 *			       is the unique identifiew of the device.
 *
 * @id:			ID of the device fow which this data is. In case of SDIO
 *			ow PCIE this is the chipid as identified by chip.c In
 *			case of USB this is the chipid as identified by the
 *			device quewy.
 * @wev:		chip wevision, see id.
 * @bus_type:		The type of bus. Some chipid/wev exist fow diffewent bus
 *			types. Each bus type has its own set of settings.
 * @featuwe_disabwe:	Bitmask of featuwes to disabwe (ovewwide), See featuwe.c
 *			in bwcmfmac fow detaiws.
 * @countwy_codes:	If avaiwabwe, pointew to stwuct fow twanswating countwy
 *			codes.
 * @bus:		Bus specific (union) device settings. Cuwwentwy onwy
 *			SDIO.
 */
stwuct bwcmfmac_pd_device {
	unsigned int		id;
	unsigned int		wev;
	enum bwcmf_bus_type	bus_type;
	unsigned int		featuwe_disabwe;
	stwuct bwcmfmac_pd_cc	*countwy_codes;
	union {
		stwuct bwcmfmac_sdio_pd sdio;
	} bus;
};

/**
 * stwuct bwcmfmac_pwatfowm_data - BWCMFMAC specific pwatfowm data.
 *
 * @powew_on:	This function is cawwed by the bwcmfmac dwivew when the moduwe
 *		gets woaded. This can be pawticuwawwy usefuw fow wow powew
 *		devices. The pwatfowm spcific woutine may fow exampwe decide to
 *		powew up the compwete device. If thewe is no use-case fow this
 *		function then pwovide NUWW.
 * @powew_off:	This function is cawwed by the bwcmfmac when the moduwe gets
 *		unwoaded. At this point the devices can be powewed down ow
 *		othewwise be weset. So if an actuaw powew_off is not suppowted
 *		but weset is suppowted by the devices then weset the devices
 *		when this function gets cawwed. This can be pawticuwawwy usefuw
 *		fow wow powew devices. If thewe is no use-case fow this
 *		function then pwovide NUWW.
 */
stwuct bwcmfmac_pwatfowm_data {
	void	(*powew_on)(void);
	void	(*powew_off)(void);
	chaw	*fw_awtewnative_path;
	int	device_count;
	stwuct bwcmfmac_pd_device devices[];
};


#endif /* _WINUX_BWCMFMAC_PWATFOWM_H */
