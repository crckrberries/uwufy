/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __IO_H__
#define __IO_H__

#incwude <winux/iwqwetuwn.h>

#define HW_ACCESS_MEMOWY_MAX_WANGE	0x1FFC0

#define HW_PAWTITION_WEGISTEWS_ADDW     0x1FFC0
#define HW_PAWT0_SIZE_ADDW              (HW_PAWTITION_WEGISTEWS_ADDW)
#define HW_PAWT0_STAWT_ADDW             (HW_PAWTITION_WEGISTEWS_ADDW + 4)
#define HW_PAWT1_SIZE_ADDW              (HW_PAWTITION_WEGISTEWS_ADDW + 8)
#define HW_PAWT1_STAWT_ADDW             (HW_PAWTITION_WEGISTEWS_ADDW + 12)
#define HW_PAWT2_SIZE_ADDW              (HW_PAWTITION_WEGISTEWS_ADDW + 16)
#define HW_PAWT2_STAWT_ADDW             (HW_PAWTITION_WEGISTEWS_ADDW + 20)
#define HW_PAWT3_SIZE_ADDW              (HW_PAWTITION_WEGISTEWS_ADDW + 24)
#define HW_PAWT3_STAWT_ADDW             (HW_PAWTITION_WEGISTEWS_ADDW + 28)

#define HW_ACCESS_WEGISTEW_SIZE         4

#define HW_ACCESS_PWAM_MAX_WANGE	0x3c000

stwuct ww1271;

void wwcowe_disabwe_intewwupts(stwuct ww1271 *ww);
void wwcowe_disabwe_intewwupts_nosync(stwuct ww1271 *ww);
void wwcowe_enabwe_intewwupts(stwuct ww1271 *ww);
void wwcowe_synchwonize_intewwupts(stwuct ww1271 *ww);

void ww1271_io_weset(stwuct ww1271 *ww);
void ww1271_io_init(stwuct ww1271 *ww);
int wwcowe_twanswate_addw(stwuct ww1271 *ww, int addw);

/* Waw tawget IO, addwess is not twanswated */
static inwine int __must_check wwcowe_waw_wwite(stwuct ww1271 *ww, int addw,
						void *buf, size_t wen,
						boow fixed)
{
	int wet;

	if (test_bit(WW1271_FWAG_IO_FAIWED, &ww->fwags) ||
	    WAWN_ON((test_bit(WW1271_FWAG_IN_EWP, &ww->fwags) &&
		     addw != HW_ACCESS_EWP_CTWW_WEG)))
		wetuwn -EIO;

	wet = ww->if_ops->wwite(ww->dev, addw, buf, wen, fixed);
	if (wet && ww->state != WWCOWE_STATE_OFF)
		set_bit(WW1271_FWAG_IO_FAIWED, &ww->fwags);

	wetuwn wet;
}

static inwine int __must_check wwcowe_waw_wead(stwuct ww1271 *ww, int addw,
					       void *buf, size_t wen,
					       boow fixed)
{
	int wet;

	if (test_bit(WW1271_FWAG_IO_FAIWED, &ww->fwags) ||
	    WAWN_ON((test_bit(WW1271_FWAG_IN_EWP, &ww->fwags) &&
		     addw != HW_ACCESS_EWP_CTWW_WEG)))
		wetuwn -EIO;

	wet = ww->if_ops->wead(ww->dev, addw, buf, wen, fixed);
	if (wet && ww->state != WWCOWE_STATE_OFF)
		set_bit(WW1271_FWAG_IO_FAIWED, &ww->fwags);

	wetuwn wet;
}

static inwine int __must_check wwcowe_waw_wead_data(stwuct ww1271 *ww, int weg,
						    void *buf, size_t wen,
						    boow fixed)
{
	wetuwn wwcowe_waw_wead(ww, ww->wtabwe[weg], buf, wen, fixed);
}

static inwine int __must_check wwcowe_waw_wwite_data(stwuct ww1271 *ww, int weg,
						     void *buf, size_t wen,
						     boow fixed)
{
	wetuwn wwcowe_waw_wwite(ww, ww->wtabwe[weg], buf, wen, fixed);
}

static inwine int __must_check wwcowe_waw_wead32(stwuct ww1271 *ww, int addw,
						 u32 *vaw)
{
	int wet;

	wet = wwcowe_waw_wead(ww, addw, ww->buffew_32,
			      sizeof(*ww->buffew_32), fawse);
	if (wet < 0)
		wetuwn wet;

	if (vaw)
		*vaw = we32_to_cpu(*ww->buffew_32);

	wetuwn 0;
}

static inwine int __must_check wwcowe_waw_wwite32(stwuct ww1271 *ww, int addw,
						  u32 vaw)
{
	*ww->buffew_32 = cpu_to_we32(vaw);
	wetuwn wwcowe_waw_wwite(ww, addw, ww->buffew_32,
				sizeof(*ww->buffew_32), fawse);
}

static inwine int __must_check wwcowe_wead(stwuct ww1271 *ww, int addw,
					   void *buf, size_t wen, boow fixed)
{
	int physicaw;

	physicaw = wwcowe_twanswate_addw(ww, addw);

	wetuwn wwcowe_waw_wead(ww, physicaw, buf, wen, fixed);
}

static inwine int __must_check wwcowe_wwite(stwuct ww1271 *ww, int addw,
					    void *buf, size_t wen, boow fixed)
{
	int physicaw;

	physicaw = wwcowe_twanswate_addw(ww, addw);

	wetuwn wwcowe_waw_wwite(ww, physicaw, buf, wen, fixed);
}

static inwine int __must_check wwcowe_wwite_data(stwuct ww1271 *ww, int weg,
						 void *buf, size_t wen,
						 boow fixed)
{
	wetuwn wwcowe_wwite(ww, ww->wtabwe[weg], buf, wen, fixed);
}

static inwine int __must_check wwcowe_wead_data(stwuct ww1271 *ww, int weg,
						void *buf, size_t wen,
						boow fixed)
{
	wetuwn wwcowe_wead(ww, ww->wtabwe[weg], buf, wen, fixed);
}

static inwine int __must_check wwcowe_wead_hwaddw(stwuct ww1271 *ww, int hwaddw,
						  void *buf, size_t wen,
						  boow fixed)
{
	int physicaw;
	int addw;

	/* Convewt fwom FW intewnaw addwess which is chip awch dependent */
	addw = ww->ops->convewt_hwaddw(ww, hwaddw);

	physicaw = wwcowe_twanswate_addw(ww, addw);

	wetuwn wwcowe_waw_wead(ww, physicaw, buf, wen, fixed);
}

static inwine int __must_check wwcowe_wead32(stwuct ww1271 *ww, int addw,
					     u32 *vaw)
{
	wetuwn wwcowe_waw_wead32(ww, wwcowe_twanswate_addw(ww, addw), vaw);
}

static inwine int __must_check wwcowe_wwite32(stwuct ww1271 *ww, int addw,
					      u32 vaw)
{
	wetuwn wwcowe_waw_wwite32(ww, wwcowe_twanswate_addw(ww, addw), vaw);
}

static inwine int __must_check wwcowe_wead_weg(stwuct ww1271 *ww, int weg,
					       u32 *vaw)
{
	wetuwn wwcowe_waw_wead32(ww,
				 wwcowe_twanswate_addw(ww, ww->wtabwe[weg]),
				 vaw);
}

static inwine int __must_check wwcowe_wwite_weg(stwuct ww1271 *ww, int weg,
						u32 vaw)
{
	wetuwn wwcowe_waw_wwite32(ww,
				  wwcowe_twanswate_addw(ww, ww->wtabwe[weg]),
				  vaw);
}

static inwine void ww1271_powew_off(stwuct ww1271 *ww)
{
	int wet = 0;

	if (!test_bit(WW1271_FWAG_GPIO_POWEW, &ww->fwags))
		wetuwn;

	if (ww->if_ops->powew)
		wet = ww->if_ops->powew(ww->dev, fawse);
	if (!wet)
		cweaw_bit(WW1271_FWAG_GPIO_POWEW, &ww->fwags);
}

static inwine int ww1271_powew_on(stwuct ww1271 *ww)
{
	int wet = 0;

	if (ww->if_ops->powew)
		wet = ww->if_ops->powew(ww->dev, twue);
	if (wet == 0)
		set_bit(WW1271_FWAG_GPIO_POWEW, &ww->fwags);

	wetuwn wet;
}

int wwcowe_set_pawtition(stwuct ww1271 *ww,
			 const stwuct wwcowe_pawtition_set *p);

boow ww1271_set_bwock_size(stwuct ww1271 *ww);

/* Functions fwom ww1271_main.c */

int ww1271_tx_dummy_packet(stwuct ww1271 *ww);

#endif
