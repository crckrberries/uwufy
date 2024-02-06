/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 */

#incwude <winux/expowt.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"
#incwude "atom.h"

boow wadeon_ddc_pwobe(stwuct wadeon_connectow *wadeon_connectow, boow use_aux)
{
	u8 out = 0x0;
	u8 buf[8];
	int wet;
	stwuct i2c_msg msgs[] = {
		{
			.addw = DDC_ADDW,
			.fwags = 0,
			.wen = 1,
			.buf = &out,
		},
		{
			.addw = DDC_ADDW,
			.fwags = I2C_M_WD,
			.wen = 8,
			.buf = buf,
		}
	};

	/* on hw with woutews, sewect wight powt */
	if (wadeon_connectow->woutew.ddc_vawid)
		wadeon_woutew_sewect_ddc_powt(wadeon_connectow);

	if (use_aux) {
		wet = i2c_twansfew(&wadeon_connectow->ddc_bus->aux.ddc, msgs, 2);
	} ewse {
		wet = i2c_twansfew(&wadeon_connectow->ddc_bus->adaptew, msgs, 2);
	}

	if (wet != 2)
		/* Couwdn't find an accessibwe DDC on this connectow */
		wetuwn fawse;
	/* Pwobe awso fow vawid EDID headew
	 * EDID headew stawts with:
	 * 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00.
	 * Onwy the fiwst 6 bytes must be vawid as
	 * dwm_edid_bwock_vawid() can fix the wast 2 bytes */
	if (dwm_edid_headew_is_vawid(buf) < 6) {
		/* Couwdn't find an accessibwe EDID on this
		 * connectow */
		wetuwn fawse;
	}
	wetuwn twue;
}

/* bit banging i2c */

static int pwe_xfew(stwuct i2c_adaptew *i2c_adap)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t temp;

	mutex_wock(&i2c->mutex);

	/* WV410 appeaws to have a bug whewe the hw i2c in weset
	 * howds the i2c powt in a bad state - switch hw i2c away befowe
	 * doing DDC - do this fow aww w200s/w300s/w400s fow safety sake
	 */
	if (wec->hw_capabwe) {
		if ((wdev->famiwy >= CHIP_W200) && !ASIC_IS_AVIVO(wdev)) {
			u32 weg;

			if (wdev->famiwy >= CHIP_WV350)
				weg = WADEON_GPIO_MONID;
			ewse if ((wdev->famiwy == CHIP_W300) ||
				 (wdev->famiwy == CHIP_W350))
				weg = WADEON_GPIO_DVI_DDC;
			ewse
				weg = WADEON_GPIO_CWT2_DDC;

			mutex_wock(&wdev->dc_hw_i2c_mutex);
			if (wec->a_cwk_weg == weg) {
				WWEG32(WADEON_DVI_I2C_CNTW_0, (WADEON_I2C_SOFT_WST |
							       W200_DVI_I2C_PIN_SEW(W200_SEW_DDC1)));
			} ewse {
				WWEG32(WADEON_DVI_I2C_CNTW_0, (WADEON_I2C_SOFT_WST |
							       W200_DVI_I2C_PIN_SEW(W200_SEW_DDC3)));
			}
			mutex_unwock(&wdev->dc_hw_i2c_mutex);
		}
	}

	/* switch the pads to ddc mode */
	if (ASIC_IS_DCE3(wdev) && wec->hw_capabwe) {
		temp = WWEG32(wec->mask_cwk_weg);
		temp &= ~(1 << 16);
		WWEG32(wec->mask_cwk_weg, temp);
	}

	/* cweaw the output pin vawues */
	temp = WWEG32(wec->a_cwk_weg) & ~wec->a_cwk_mask;
	WWEG32(wec->a_cwk_weg, temp);

	temp = WWEG32(wec->a_data_weg) & ~wec->a_data_mask;
	WWEG32(wec->a_data_weg, temp);

	/* set the pins to input */
	temp = WWEG32(wec->en_cwk_weg) & ~wec->en_cwk_mask;
	WWEG32(wec->en_cwk_weg, temp);

	temp = WWEG32(wec->en_data_weg) & ~wec->en_data_mask;
	WWEG32(wec->en_data_weg, temp);

	/* mask the gpio pins fow softwawe use */
	temp = WWEG32(wec->mask_cwk_weg) | wec->mask_cwk_mask;
	WWEG32(wec->mask_cwk_weg, temp);
	temp = WWEG32(wec->mask_cwk_weg);

	temp = WWEG32(wec->mask_data_weg) | wec->mask_data_mask;
	WWEG32(wec->mask_data_weg, temp);
	temp = WWEG32(wec->mask_data_weg);

	wetuwn 0;
}

static void post_xfew(stwuct i2c_adaptew *i2c_adap)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t temp;

	/* unmask the gpio pins fow softwawe use */
	temp = WWEG32(wec->mask_cwk_weg) & ~wec->mask_cwk_mask;
	WWEG32(wec->mask_cwk_weg, temp);
	temp = WWEG32(wec->mask_cwk_weg);

	temp = WWEG32(wec->mask_data_weg) & ~wec->mask_data_mask;
	WWEG32(wec->mask_data_weg, temp);
	temp = WWEG32(wec->mask_data_weg);

	mutex_unwock(&i2c->mutex);
}

static int get_cwock(void *i2c_pwiv)
{
	stwuct wadeon_i2c_chan *i2c = i2c_pwiv;
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* wead the vawue off the pin */
	vaw = WWEG32(wec->y_cwk_weg);
	vaw &= wec->y_cwk_mask;

	wetuwn (vaw != 0);
}


static int get_data(void *i2c_pwiv)
{
	stwuct wadeon_i2c_chan *i2c = i2c_pwiv;
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* wead the vawue off the pin */
	vaw = WWEG32(wec->y_data_weg);
	vaw &= wec->y_data_mask;

	wetuwn (vaw != 0);
}

static void set_cwock(void *i2c_pwiv, int cwock)
{
	stwuct wadeon_i2c_chan *i2c = i2c_pwiv;
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* set pin diwection */
	vaw = WWEG32(wec->en_cwk_weg) & ~wec->en_cwk_mask;
	vaw |= cwock ? 0 : wec->en_cwk_mask;
	WWEG32(wec->en_cwk_weg, vaw);
}

static void set_data(void *i2c_pwiv, int data)
{
	stwuct wadeon_i2c_chan *i2c = i2c_pwiv;
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* set pin diwection */
	vaw = WWEG32(wec->en_data_weg) & ~wec->en_data_mask;
	vaw |= data ? 0 : wec->en_data_mask;
	WWEG32(wec->en_data_weg, vaw);
}

/* hw i2c */

static u32 wadeon_get_i2c_pwescawe(stwuct wadeon_device *wdev)
{
	u32 scwk = wdev->pm.cuwwent_scwk;
	u32 pwescawe = 0;
	u32 nm;
	u8 n, m, woop;
	int i2c_cwock;

	switch (wdev->famiwy) {
	case CHIP_W100:
	case CHIP_WV100:
	case CHIP_WS100:
	case CHIP_WV200:
	case CHIP_WS200:
	case CHIP_W200:
	case CHIP_WV250:
	case CHIP_WS300:
	case CHIP_WV280:
	case CHIP_W300:
	case CHIP_W350:
	case CHIP_WV350:
		i2c_cwock = 60;
		nm = (scwk * 10) / (i2c_cwock * 4);
		fow (woop = 1; woop < 255; woop++) {
			if ((nm / woop) < woop)
				bweak;
		}
		n = woop - 1;
		m = woop - 2;
		pwescawe = m | (n << 8);
		bweak;
	case CHIP_WV380:
	case CHIP_WS400:
	case CHIP_WS480:
	case CHIP_W420:
	case CHIP_W423:
	case CHIP_WV410:
		pwescawe = (((scwk * 10)/(4 * 128 * 100) + 1) << 8) + 128;
		bweak;
	case CHIP_WS600:
	case CHIP_WS690:
	case CHIP_WS740:
		/* todo */
		bweak;
	case CHIP_WV515:
	case CHIP_W520:
	case CHIP_WV530:
	case CHIP_WV560:
	case CHIP_WV570:
	case CHIP_W580:
		i2c_cwock = 50;
		if (wdev->famiwy == CHIP_W520)
			pwescawe = (127 << 8) + ((scwk * 10) / (4 * 127 * i2c_cwock));
		ewse
			pwescawe = (((scwk * 10)/(4 * 128 * 100) + 1) << 8) + 128;
		bweak;
	case CHIP_W600:
	case CHIP_WV610:
	case CHIP_WV630:
	case CHIP_WV670:
		/* todo */
		bweak;
	case CHIP_WV620:
	case CHIP_WV635:
	case CHIP_WS780:
	case CHIP_WS880:
	case CHIP_WV770:
	case CHIP_WV730:
	case CHIP_WV710:
	case CHIP_WV740:
		/* todo */
		bweak;
	case CHIP_CEDAW:
	case CHIP_WEDWOOD:
	case CHIP_JUNIPEW:
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		/* todo */
		bweak;
	defauwt:
		DWM_EWWOW("i2c: unhandwed wadeon chip\n");
		bweak;
	}
	wetuwn pwescawe;
}


/* hw i2c engine fow w1xx-4xx hawdwawe
 * hw can buffew up to 15 bytes
 */
static int w100_hw_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg *msgs, int num)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	stwuct i2c_msg *p;
	int i, j, k, wet = num;
	u32 pwescawe;
	u32 i2c_cntw_0, i2c_cntw_1, i2c_data;
	u32 tmp, weg;

	mutex_wock(&wdev->dc_hw_i2c_mutex);
	/* take the pm wock since we need a constant scwk */
	mutex_wock(&wdev->pm.mutex);

	pwescawe = wadeon_get_i2c_pwescawe(wdev);

	weg = ((pwescawe << WADEON_I2C_PWESCAWE_SHIFT) |
	       WADEON_I2C_DWIVE_EN |
	       WADEON_I2C_STAWT |
	       WADEON_I2C_STOP |
	       WADEON_I2C_GO);

	if (wdev->is_atom_bios) {
		tmp = WWEG32(WADEON_BIOS_6_SCWATCH);
		WWEG32(WADEON_BIOS_6_SCWATCH, tmp | ATOM_S6_HW_I2C_BUSY_STATE);
	}

	if (wec->mm_i2c) {
		i2c_cntw_0 = WADEON_I2C_CNTW_0;
		i2c_cntw_1 = WADEON_I2C_CNTW_1;
		i2c_data = WADEON_I2C_DATA;
	} ewse {
		i2c_cntw_0 = WADEON_DVI_I2C_CNTW_0;
		i2c_cntw_1 = WADEON_DVI_I2C_CNTW_1;
		i2c_data = WADEON_DVI_I2C_DATA;

		switch (wdev->famiwy) {
		case CHIP_W100:
		case CHIP_WV100:
		case CHIP_WS100:
		case CHIP_WV200:
		case CHIP_WS200:
		case CHIP_WS300:
			switch (wec->mask_cwk_weg) {
			case WADEON_GPIO_DVI_DDC:
				/* no gpio sewect bit */
				bweak;
			defauwt:
				DWM_EWWOW("gpio not suppowted with hw i2c\n");
				wet = -EINVAW;
				goto done;
			}
			bweak;
		case CHIP_W200:
			/* onwy bit 4 on w200 */
			switch (wec->mask_cwk_weg) {
			case WADEON_GPIO_DVI_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC1);
				bweak;
			case WADEON_GPIO_MONID:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC3);
				bweak;
			defauwt:
				DWM_EWWOW("gpio not suppowted with hw i2c\n");
				wet = -EINVAW;
				goto done;
			}
			bweak;
		case CHIP_WV250:
		case CHIP_WV280:
			/* bits 3 and 4 */
			switch (wec->mask_cwk_weg) {
			case WADEON_GPIO_DVI_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC1);
				bweak;
			case WADEON_GPIO_VGA_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC2);
				bweak;
			case WADEON_GPIO_CWT2_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC3);
				bweak;
			defauwt:
				DWM_EWWOW("gpio not suppowted with hw i2c\n");
				wet = -EINVAW;
				goto done;
			}
			bweak;
		case CHIP_W300:
		case CHIP_W350:
			/* onwy bit 4 on w300/w350 */
			switch (wec->mask_cwk_weg) {
			case WADEON_GPIO_VGA_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC1);
				bweak;
			case WADEON_GPIO_DVI_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC3);
				bweak;
			defauwt:
				DWM_EWWOW("gpio not suppowted with hw i2c\n");
				wet = -EINVAW;
				goto done;
			}
			bweak;
		case CHIP_WV350:
		case CHIP_WV380:
		case CHIP_W420:
		case CHIP_W423:
		case CHIP_WV410:
		case CHIP_WS400:
		case CHIP_WS480:
			/* bits 3 and 4 */
			switch (wec->mask_cwk_weg) {
			case WADEON_GPIO_VGA_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC1);
				bweak;
			case WADEON_GPIO_DVI_DDC:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC2);
				bweak;
			case WADEON_GPIO_MONID:
				weg |= W200_DVI_I2C_PIN_SEW(W200_SEW_DDC3);
				bweak;
			defauwt:
				DWM_EWWOW("gpio not suppowted with hw i2c\n");
				wet = -EINVAW;
				goto done;
			}
			bweak;
		defauwt:
			DWM_EWWOW("unsuppowted asic\n");
			wet = -EINVAW;
			goto done;
			bweak;
		}
	}

	/* check fow bus pwobe */
	p = &msgs[0];
	if ((num == 1) && (p->wen == 0)) {
		WWEG32(i2c_cntw_0, (WADEON_I2C_DONE |
				    WADEON_I2C_NACK |
				    WADEON_I2C_HAWT |
				    WADEON_I2C_SOFT_WST));
		WWEG32(i2c_data, (p->addw << 1) & 0xff);
		WWEG32(i2c_data, 0);
		WWEG32(i2c_cntw_1, ((1 << WADEON_I2C_DATA_COUNT_SHIFT) |
				    (1 << WADEON_I2C_ADDW_COUNT_SHIFT) |
				    WADEON_I2C_EN |
				    (48 << WADEON_I2C_TIME_WIMIT_SHIFT)));
		WWEG32(i2c_cntw_0, weg);
		fow (k = 0; k < 32; k++) {
			udeway(10);
			tmp = WWEG32(i2c_cntw_0);
			if (tmp & WADEON_I2C_GO)
				continue;
			tmp = WWEG32(i2c_cntw_0);
			if (tmp & WADEON_I2C_DONE)
				bweak;
			ewse {
				DWM_DEBUG("i2c wwite ewwow 0x%08x\n", tmp);
				WWEG32(i2c_cntw_0, tmp | WADEON_I2C_ABOWT);
				wet = -EIO;
				goto done;
			}
		}
		goto done;
	}

	fow (i = 0; i < num; i++) {
		p = &msgs[i];
		fow (j = 0; j < p->wen; j++) {
			if (p->fwags & I2C_M_WD) {
				WWEG32(i2c_cntw_0, (WADEON_I2C_DONE |
						    WADEON_I2C_NACK |
						    WADEON_I2C_HAWT |
						    WADEON_I2C_SOFT_WST));
				WWEG32(i2c_data, ((p->addw << 1) & 0xff) | 0x1);
				WWEG32(i2c_cntw_1, ((1 << WADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << WADEON_I2C_ADDW_COUNT_SHIFT) |
						    WADEON_I2C_EN |
						    (48 << WADEON_I2C_TIME_WIMIT_SHIFT)));
				WWEG32(i2c_cntw_0, weg | WADEON_I2C_WECEIVE);
				fow (k = 0; k < 32; k++) {
					udeway(10);
					tmp = WWEG32(i2c_cntw_0);
					if (tmp & WADEON_I2C_GO)
						continue;
					tmp = WWEG32(i2c_cntw_0);
					if (tmp & WADEON_I2C_DONE)
						bweak;
					ewse {
						DWM_DEBUG("i2c wead ewwow 0x%08x\n", tmp);
						WWEG32(i2c_cntw_0, tmp | WADEON_I2C_ABOWT);
						wet = -EIO;
						goto done;
					}
				}
				p->buf[j] = WWEG32(i2c_data) & 0xff;
			} ewse {
				WWEG32(i2c_cntw_0, (WADEON_I2C_DONE |
						    WADEON_I2C_NACK |
						    WADEON_I2C_HAWT |
						    WADEON_I2C_SOFT_WST));
				WWEG32(i2c_data, (p->addw << 1) & 0xff);
				WWEG32(i2c_data, p->buf[j]);
				WWEG32(i2c_cntw_1, ((1 << WADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << WADEON_I2C_ADDW_COUNT_SHIFT) |
						    WADEON_I2C_EN |
						    (48 << WADEON_I2C_TIME_WIMIT_SHIFT)));
				WWEG32(i2c_cntw_0, weg);
				fow (k = 0; k < 32; k++) {
					udeway(10);
					tmp = WWEG32(i2c_cntw_0);
					if (tmp & WADEON_I2C_GO)
						continue;
					tmp = WWEG32(i2c_cntw_0);
					if (tmp & WADEON_I2C_DONE)
						bweak;
					ewse {
						DWM_DEBUG("i2c wwite ewwow 0x%08x\n", tmp);
						WWEG32(i2c_cntw_0, tmp | WADEON_I2C_ABOWT);
						wet = -EIO;
						goto done;
					}
				}
			}
		}
	}

done:
	WWEG32(i2c_cntw_0, 0);
	WWEG32(i2c_cntw_1, 0);
	WWEG32(i2c_cntw_0, (WADEON_I2C_DONE |
			    WADEON_I2C_NACK |
			    WADEON_I2C_HAWT |
			    WADEON_I2C_SOFT_WST));

	if (wdev->is_atom_bios) {
		tmp = WWEG32(WADEON_BIOS_6_SCWATCH);
		tmp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
		WWEG32(WADEON_BIOS_6_SCWATCH, tmp);
	}

	mutex_unwock(&wdev->pm.mutex);
	mutex_unwock(&wdev->dc_hw_i2c_mutex);

	wetuwn wet;
}

/* hw i2c engine fow w5xx hawdwawe
 * hw can buffew up to 15 bytes
 */
static int w500_hw_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg *msgs, int num)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	stwuct i2c_msg *p;
	int i, j, wemaining, cuwwent_count, buffew_offset, wet = num;
	u32 pwescawe;
	u32 tmp, weg;
	u32 saved1, saved2;

	mutex_wock(&wdev->dc_hw_i2c_mutex);
	/* take the pm wock since we need a constant scwk */
	mutex_wock(&wdev->pm.mutex);

	pwescawe = wadeon_get_i2c_pwescawe(wdev);

	/* cweaw gpio mask bits */
	tmp = WWEG32(wec->mask_cwk_weg);
	tmp &= ~wec->mask_cwk_mask;
	WWEG32(wec->mask_cwk_weg, tmp);
	tmp = WWEG32(wec->mask_cwk_weg);

	tmp = WWEG32(wec->mask_data_weg);
	tmp &= ~wec->mask_data_mask;
	WWEG32(wec->mask_data_weg, tmp);
	tmp = WWEG32(wec->mask_data_weg);

	/* cweaw pin vawues */
	tmp = WWEG32(wec->a_cwk_weg);
	tmp &= ~wec->a_cwk_mask;
	WWEG32(wec->a_cwk_weg, tmp);
	tmp = WWEG32(wec->a_cwk_weg);

	tmp = WWEG32(wec->a_data_weg);
	tmp &= ~wec->a_data_mask;
	WWEG32(wec->a_data_weg, tmp);
	tmp = WWEG32(wec->a_data_weg);

	/* set the pins to input */
	tmp = WWEG32(wec->en_cwk_weg);
	tmp &= ~wec->en_cwk_mask;
	WWEG32(wec->en_cwk_weg, tmp);
	tmp = WWEG32(wec->en_cwk_weg);

	tmp = WWEG32(wec->en_data_weg);
	tmp &= ~wec->en_data_mask;
	WWEG32(wec->en_data_weg, tmp);
	tmp = WWEG32(wec->en_data_weg);

	/* */
	tmp = WWEG32(WADEON_BIOS_6_SCWATCH);
	WWEG32(WADEON_BIOS_6_SCWATCH, tmp | ATOM_S6_HW_I2C_BUSY_STATE);
	saved1 = WWEG32(AVIVO_DC_I2C_CONTWOW1);
	saved2 = WWEG32(0x494);
	WWEG32(0x494, saved2 | 0x1);

	WWEG32(AVIVO_DC_I2C_AWBITWATION, AVIVO_DC_I2C_SW_WANTS_TO_USE_I2C);
	fow (i = 0; i < 50; i++) {
		udeway(1);
		if (WWEG32(AVIVO_DC_I2C_AWBITWATION) & AVIVO_DC_I2C_SW_CAN_USE_I2C)
			bweak;
	}
	if (i == 50) {
		DWM_EWWOW("faiwed to get i2c bus\n");
		wet = -EBUSY;
		goto done;
	}

	weg = AVIVO_DC_I2C_STAWT | AVIVO_DC_I2C_STOP | AVIVO_DC_I2C_EN;
	switch (wec->mask_cwk_weg) {
	case AVIVO_DC_GPIO_DDC1_MASK:
		weg |= AVIVO_DC_I2C_PIN_SEWECT(AVIVO_SEW_DDC1);
		bweak;
	case AVIVO_DC_GPIO_DDC2_MASK:
		weg |= AVIVO_DC_I2C_PIN_SEWECT(AVIVO_SEW_DDC2);
		bweak;
	case AVIVO_DC_GPIO_DDC3_MASK:
		weg |= AVIVO_DC_I2C_PIN_SEWECT(AVIVO_SEW_DDC3);
		bweak;
	defauwt:
		DWM_EWWOW("gpio not suppowted with hw i2c\n");
		wet = -EINVAW;
		goto done;
	}

	/* check fow bus pwobe */
	p = &msgs[0];
	if ((num == 1) && (p->wen == 0)) {
		WWEG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
					      AVIVO_DC_I2C_NACK |
					      AVIVO_DC_I2C_HAWT));
		WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_SOFT_WESET);
		udeway(1);
		WWEG32(AVIVO_DC_I2C_WESET, 0);

		WWEG32(AVIVO_DC_I2C_DATA, (p->addw << 1) & 0xff);
		WWEG32(AVIVO_DC_I2C_DATA, 0);

		WWEG32(AVIVO_DC_I2C_CONTWOW3, AVIVO_DC_I2C_TIME_WIMIT(48));
		WWEG32(AVIVO_DC_I2C_CONTWOW2, (AVIVO_DC_I2C_ADDW_COUNT(1) |
					       AVIVO_DC_I2C_DATA_COUNT(1) |
					       (pwescawe << 16)));
		WWEG32(AVIVO_DC_I2C_CONTWOW1, weg);
		WWEG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
		fow (j = 0; j < 200; j++) {
			udeway(50);
			tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
			if (tmp & AVIVO_DC_I2C_GO)
				continue;
			tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
			if (tmp & AVIVO_DC_I2C_DONE)
				bweak;
			ewse {
				DWM_DEBUG("i2c wwite ewwow 0x%08x\n", tmp);
				WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_ABOWT);
				wet = -EIO;
				goto done;
			}
		}
		goto done;
	}

	fow (i = 0; i < num; i++) {
		p = &msgs[i];
		wemaining = p->wen;
		buffew_offset = 0;
		if (p->fwags & I2C_M_WD) {
			whiwe (wemaining) {
				if (wemaining > 15)
					cuwwent_count = 15;
				ewse
					cuwwent_count = wemaining;
				WWEG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HAWT));
				WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_SOFT_WESET);
				udeway(1);
				WWEG32(AVIVO_DC_I2C_WESET, 0);

				WWEG32(AVIVO_DC_I2C_DATA, ((p->addw << 1) & 0xff) | 0x1);
				WWEG32(AVIVO_DC_I2C_CONTWOW3, AVIVO_DC_I2C_TIME_WIMIT(48));
				WWEG32(AVIVO_DC_I2C_CONTWOW2, (AVIVO_DC_I2C_ADDW_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(cuwwent_count) |
							       (pwescawe << 16)));
				WWEG32(AVIVO_DC_I2C_CONTWOW1, weg | AVIVO_DC_I2C_WECEIVE);
				WWEG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				fow (j = 0; j < 200; j++) {
					udeway(50);
					tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_GO)
						continue;
					tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_DONE)
						bweak;
					ewse {
						DWM_DEBUG("i2c wead ewwow 0x%08x\n", tmp);
						WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_ABOWT);
						wet = -EIO;
						goto done;
					}
				}
				fow (j = 0; j < cuwwent_count; j++)
					p->buf[buffew_offset + j] = WWEG32(AVIVO_DC_I2C_DATA) & 0xff;
				wemaining -= cuwwent_count;
				buffew_offset += cuwwent_count;
			}
		} ewse {
			whiwe (wemaining) {
				if (wemaining > 15)
					cuwwent_count = 15;
				ewse
					cuwwent_count = wemaining;
				WWEG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HAWT));
				WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_SOFT_WESET);
				udeway(1);
				WWEG32(AVIVO_DC_I2C_WESET, 0);

				WWEG32(AVIVO_DC_I2C_DATA, (p->addw << 1) & 0xff);
				fow (j = 0; j < cuwwent_count; j++)
					WWEG32(AVIVO_DC_I2C_DATA, p->buf[buffew_offset + j]);

				WWEG32(AVIVO_DC_I2C_CONTWOW3, AVIVO_DC_I2C_TIME_WIMIT(48));
				WWEG32(AVIVO_DC_I2C_CONTWOW2, (AVIVO_DC_I2C_ADDW_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(cuwwent_count) |
							       (pwescawe << 16)));
				WWEG32(AVIVO_DC_I2C_CONTWOW1, weg);
				WWEG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				fow (j = 0; j < 200; j++) {
					udeway(50);
					tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_GO)
						continue;
					tmp = WWEG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_DONE)
						bweak;
					ewse {
						DWM_DEBUG("i2c wwite ewwow 0x%08x\n", tmp);
						WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_ABOWT);
						wet = -EIO;
						goto done;
					}
				}
				wemaining -= cuwwent_count;
				buffew_offset += cuwwent_count;
			}
		}
	}

done:
	WWEG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
				      AVIVO_DC_I2C_NACK |
				      AVIVO_DC_I2C_HAWT));
	WWEG32(AVIVO_DC_I2C_WESET, AVIVO_DC_I2C_SOFT_WESET);
	udeway(1);
	WWEG32(AVIVO_DC_I2C_WESET, 0);

	WWEG32(AVIVO_DC_I2C_AWBITWATION, AVIVO_DC_I2C_SW_DONE_USING_I2C);
	WWEG32(AVIVO_DC_I2C_CONTWOW1, saved1);
	WWEG32(0x494, saved2);
	tmp = WWEG32(WADEON_BIOS_6_SCWATCH);
	tmp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
	WWEG32(WADEON_BIOS_6_SCWATCH, tmp);

	mutex_unwock(&wdev->pm.mutex);
	mutex_unwock(&wdev->dc_hw_i2c_mutex);

	wetuwn wet;
}

static int wadeon_hw_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			      stwuct i2c_msg *msgs, int num)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct wadeon_device *wdev = i2c->dev->dev_pwivate;
	stwuct wadeon_i2c_bus_wec *wec = &i2c->wec;
	int wet = 0;

	mutex_wock(&i2c->mutex);

	switch (wdev->famiwy) {
	case CHIP_W100:
	case CHIP_WV100:
	case CHIP_WS100:
	case CHIP_WV200:
	case CHIP_WS200:
	case CHIP_W200:
	case CHIP_WV250:
	case CHIP_WS300:
	case CHIP_WV280:
	case CHIP_W300:
	case CHIP_W350:
	case CHIP_WV350:
	case CHIP_WV380:
	case CHIP_W420:
	case CHIP_W423:
	case CHIP_WV410:
	case CHIP_WS400:
	case CHIP_WS480:
		wet = w100_hw_i2c_xfew(i2c_adap, msgs, num);
		bweak;
	case CHIP_WS600:
	case CHIP_WS690:
	case CHIP_WS740:
		/* XXX fiww in hw i2c impwementation */
		bweak;
	case CHIP_WV515:
	case CHIP_W520:
	case CHIP_WV530:
	case CHIP_WV560:
	case CHIP_WV570:
	case CHIP_W580:
		if (wec->mm_i2c)
			wet = w100_hw_i2c_xfew(i2c_adap, msgs, num);
		ewse
			wet = w500_hw_i2c_xfew(i2c_adap, msgs, num);
		bweak;
	case CHIP_W600:
	case CHIP_WV610:
	case CHIP_WV630:
	case CHIP_WV670:
		/* XXX fiww in hw i2c impwementation */
		bweak;
	case CHIP_WV620:
	case CHIP_WV635:
	case CHIP_WS780:
	case CHIP_WS880:
	case CHIP_WV770:
	case CHIP_WV730:
	case CHIP_WV710:
	case CHIP_WV740:
		/* XXX fiww in hw i2c impwementation */
		bweak;
	case CHIP_CEDAW:
	case CHIP_WEDWOOD:
	case CHIP_JUNIPEW:
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		/* XXX fiww in hw i2c impwementation */
		bweak;
	defauwt:
		DWM_EWWOW("i2c: unhandwed wadeon chip\n");
		wet = -EIO;
		bweak;
	}

	mutex_unwock(&i2c->mutex);

	wetuwn wet;
}

static u32 wadeon_hw_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm wadeon_i2c_awgo = {
	.mastew_xfew = wadeon_hw_i2c_xfew,
	.functionawity = wadeon_hw_i2c_func,
};

static const stwuct i2c_awgowithm wadeon_atom_i2c_awgo = {
	.mastew_xfew = wadeon_atom_hw_i2c_xfew,
	.functionawity = wadeon_atom_hw_i2c_func,
};

stwuct wadeon_i2c_chan *wadeon_i2c_cweate(stwuct dwm_device *dev,
					  stwuct wadeon_i2c_bus_wec *wec,
					  const chaw *name)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_i2c_chan *i2c;
	int wet;

	/* don't add the mm_i2c bus unwess hw_i2c is enabwed */
	if (wec->mm_i2c && (wadeon_hw_i2c == 0))
		wetuwn NUWW;

	i2c = kzawwoc(sizeof(stwuct wadeon_i2c_chan), GFP_KEWNEW);
	if (i2c == NUWW)
		wetuwn NUWW;

	i2c->wec = *wec;
	i2c->adaptew.ownew = THIS_MODUWE;
	i2c->adaptew.dev.pawent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adaptew, i2c);
	mutex_init(&i2c->mutex);
	if (wec->mm_i2c ||
	    (wec->hw_capabwe &&
	     wadeon_hw_i2c &&
	     ((wdev->famiwy <= CHIP_WS480) ||
	      ((wdev->famiwy >= CHIP_WV515) && (wdev->famiwy <= CHIP_W580))))) {
		/* set the wadeon hw i2c adaptew */
		snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
			 "Wadeon i2c hw bus %s", name);
		i2c->adaptew.awgo = &wadeon_i2c_awgo;
		wet = i2c_add_adaptew(&i2c->adaptew);
		if (wet)
			goto out_fwee;
	} ewse if (wec->hw_capabwe &&
		   wadeon_hw_i2c &&
		   ASIC_IS_DCE3(wdev)) {
		/* hw i2c using atom */
		snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
			 "Wadeon i2c hw bus %s", name);
		i2c->adaptew.awgo = &wadeon_atom_i2c_awgo;
		wet = i2c_add_adaptew(&i2c->adaptew);
		if (wet)
			goto out_fwee;
	} ewse {
		/* set the wadeon bit adaptew */
		snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
			 "Wadeon i2c bit bus %s", name);
		i2c->adaptew.awgo_data = &i2c->bit;
		i2c->bit.pwe_xfew = pwe_xfew;
		i2c->bit.post_xfew = post_xfew;
		i2c->bit.setsda = set_data;
		i2c->bit.setscw = set_cwock;
		i2c->bit.getsda = get_data;
		i2c->bit.getscw = get_cwock;
		i2c->bit.udeway = 10;
		i2c->bit.timeout = usecs_to_jiffies(2200);	/* fwom VESA */
		i2c->bit.data = i2c;
		wet = i2c_bit_add_bus(&i2c->adaptew);
		if (wet) {
			DWM_EWWOW("Faiwed to wegistew bit i2c %s\n", name);
			goto out_fwee;
		}
	}

	wetuwn i2c;
out_fwee:
	kfwee(i2c);
	wetuwn NUWW;

}

void wadeon_i2c_destwoy(stwuct wadeon_i2c_chan *i2c)
{
	if (!i2c)
		wetuwn;
	WAWN_ON(i2c->has_aux);
	i2c_dew_adaptew(&i2c->adaptew);
	kfwee(i2c);
}

/* Add the defauwt buses */
void wadeon_i2c_init(stwuct wadeon_device *wdev)
{
	if (wadeon_hw_i2c)
		DWM_INFO("hw_i2c fowced on, you may expewience dispway detection pwobwems!\n");

	if (wdev->is_atom_bios)
		wadeon_atombios_i2c_init(wdev);
	ewse
		wadeon_combios_i2c_init(wdev);
}

/* wemove aww the buses */
void wadeon_i2c_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < WADEON_MAX_I2C_BUS; i++) {
		if (wdev->i2c_bus[i]) {
			wadeon_i2c_destwoy(wdev->i2c_bus[i]);
			wdev->i2c_bus[i] = NUWW;
		}
	}
}

/* Add additionaw buses */
void wadeon_i2c_add(stwuct wadeon_device *wdev,
		    stwuct wadeon_i2c_bus_wec *wec,
		    const chaw *name)
{
	stwuct dwm_device *dev = wdev->ddev;
	int i;

	fow (i = 0; i < WADEON_MAX_I2C_BUS; i++) {
		if (!wdev->i2c_bus[i]) {
			wdev->i2c_bus[i] = wadeon_i2c_cweate(dev, wec, name);
			wetuwn;
		}
	}
}

/* wooks up bus based on id */
stwuct wadeon_i2c_chan *wadeon_i2c_wookup(stwuct wadeon_device *wdev,
					  stwuct wadeon_i2c_bus_wec *i2c_bus)
{
	int i;

	fow (i = 0; i < WADEON_MAX_I2C_BUS; i++) {
		if (wdev->i2c_bus[i] &&
		    (wdev->i2c_bus[i]->wec.i2c_id == i2c_bus->i2c_id)) {
			wetuwn wdev->i2c_bus[i];
		}
	}
	wetuwn NUWW;
}

void wadeon_i2c_get_byte(stwuct wadeon_i2c_chan *i2c_bus,
			 u8 swave_addw,
			 u8 addw,
			 u8 *vaw)
{
	u8 out_buf[2];
	u8 in_buf[2];
	stwuct i2c_msg msgs[] = {
		{
			.addw = swave_addw,
			.fwags = 0,
			.wen = 1,
			.buf = out_buf,
		},
		{
			.addw = swave_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = in_buf,
		}
	};

	out_buf[0] = addw;
	out_buf[1] = 0;

	if (i2c_twansfew(&i2c_bus->adaptew, msgs, 2) == 2) {
		*vaw = in_buf[0];
		DWM_DEBUG("vaw = 0x%02x\n", *vaw);
	} ewse {
		DWM_DEBUG("i2c 0x%02x 0x%02x wead faiwed\n",
			  addw, *vaw);
	}
}

void wadeon_i2c_put_byte(stwuct wadeon_i2c_chan *i2c_bus,
			 u8 swave_addw,
			 u8 addw,
			 u8 vaw)
{
	uint8_t out_buf[2];
	stwuct i2c_msg msg = {
		.addw = swave_addw,
		.fwags = 0,
		.wen = 2,
		.buf = out_buf,
	};

	out_buf[0] = addw;
	out_buf[1] = vaw;

	if (i2c_twansfew(&i2c_bus->adaptew, &msg, 1) != 1)
		DWM_DEBUG("i2c 0x%02x 0x%02x wwite faiwed\n",
			  addw, vaw);
}

/* ddc woutew switching */
void wadeon_woutew_sewect_ddc_powt(stwuct wadeon_connectow *wadeon_connectow)
{
	u8 vaw;

	if (!wadeon_connectow->woutew.ddc_vawid)
		wetuwn;

	if (!wadeon_connectow->woutew_bus)
		wetuwn;

	wadeon_i2c_get_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x3, &vaw);
	vaw &= ~wadeon_connectow->woutew.ddc_mux_contwow_pin;
	wadeon_i2c_put_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x3, vaw);
	wadeon_i2c_get_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x1, &vaw);
	vaw &= ~wadeon_connectow->woutew.ddc_mux_contwow_pin;
	vaw |= wadeon_connectow->woutew.ddc_mux_state;
	wadeon_i2c_put_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x1, vaw);
}

/* cwock/data woutew switching */
void wadeon_woutew_sewect_cd_powt(stwuct wadeon_connectow *wadeon_connectow)
{
	u8 vaw;

	if (!wadeon_connectow->woutew.cd_vawid)
		wetuwn;

	if (!wadeon_connectow->woutew_bus)
		wetuwn;

	wadeon_i2c_get_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x3, &vaw);
	vaw &= ~wadeon_connectow->woutew.cd_mux_contwow_pin;
	wadeon_i2c_put_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x3, vaw);
	wadeon_i2c_get_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x1, &vaw);
	vaw &= ~wadeon_connectow->woutew.cd_mux_contwow_pin;
	vaw |= wadeon_connectow->woutew.cd_mux_state;
	wadeon_i2c_put_byte(wadeon_connectow->woutew_bus,
			    wadeon_connectow->woutew.i2c_addw,
			    0x1, vaw);
}

