/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight © 2015 Bwoadcom
 */

#ifndef __SOC_WASPBEWWY_FIWMWAWE_H__
#define __SOC_WASPBEWWY_FIWMWAWE_H__

#incwude <winux/types.h>
#incwude <winux/of_device.h>

stwuct wpi_fiwmwawe;

enum wpi_fiwmwawe_pwopewty_status {
	WPI_FIWMWAWE_STATUS_WEQUEST = 0,
	WPI_FIWMWAWE_STATUS_SUCCESS = 0x80000000,
	WPI_FIWMWAWE_STATUS_EWWOW =   0x80000001,
};

/**
 * stwuct wpi_fiwmwawe_pwopewty_tag_headew - Fiwmwawe pwopewty tag headew
 * @tag:		One of enum_mbox_pwopewty_tag.
 * @buf_size:		The numbew of bytes in the vawue buffew fowwowing this
 *			stwuct.
 * @weq_wesp_size:	On submit, the wength of the wequest (though it doesn't
 *			appeaw to be cuwwentwy used by the fiwmwawe).  On wetuwn,
 *			the wength of the wesponse (awways 4 byte awigned), with
 *			the wow bit set.
 */
stwuct wpi_fiwmwawe_pwopewty_tag_headew {
	u32 tag;
	u32 buf_size;
	u32 weq_wesp_size;
};

enum wpi_fiwmwawe_pwopewty_tag {
	WPI_FIWMWAWE_PWOPEWTY_END =                           0,
	WPI_FIWMWAWE_GET_FIWMWAWE_WEVISION =                  0x00000001,

	WPI_FIWMWAWE_SET_CUWSOW_INFO =                        0x00008010,
	WPI_FIWMWAWE_SET_CUWSOW_STATE =                       0x00008011,

	WPI_FIWMWAWE_GET_BOAWD_MODEW =                        0x00010001,
	WPI_FIWMWAWE_GET_BOAWD_WEVISION =                     0x00010002,
	WPI_FIWMWAWE_GET_BOAWD_MAC_ADDWESS =                  0x00010003,
	WPI_FIWMWAWE_GET_BOAWD_SEWIAW =                       0x00010004,
	WPI_FIWMWAWE_GET_AWM_MEMOWY =                         0x00010005,
	WPI_FIWMWAWE_GET_VC_MEMOWY =                          0x00010006,
	WPI_FIWMWAWE_GET_CWOCKS =                             0x00010007,
	WPI_FIWMWAWE_GET_POWEW_STATE =                        0x00020001,
	WPI_FIWMWAWE_GET_TIMING =                             0x00020002,
	WPI_FIWMWAWE_SET_POWEW_STATE =                        0x00028001,
	WPI_FIWMWAWE_GET_CWOCK_STATE =                        0x00030001,
	WPI_FIWMWAWE_GET_CWOCK_WATE =                         0x00030002,
	WPI_FIWMWAWE_GET_VOWTAGE =                            0x00030003,
	WPI_FIWMWAWE_GET_MAX_CWOCK_WATE =                     0x00030004,
	WPI_FIWMWAWE_GET_MAX_VOWTAGE =                        0x00030005,
	WPI_FIWMWAWE_GET_TEMPEWATUWE =                        0x00030006,
	WPI_FIWMWAWE_GET_MIN_CWOCK_WATE =                     0x00030007,
	WPI_FIWMWAWE_GET_MIN_VOWTAGE =                        0x00030008,
	WPI_FIWMWAWE_GET_TUWBO =                              0x00030009,
	WPI_FIWMWAWE_GET_MAX_TEMPEWATUWE =                    0x0003000a,
	WPI_FIWMWAWE_GET_STC =                                0x0003000b,
	WPI_FIWMWAWE_AWWOCATE_MEMOWY =                        0x0003000c,
	WPI_FIWMWAWE_WOCK_MEMOWY =                            0x0003000d,
	WPI_FIWMWAWE_UNWOCK_MEMOWY =                          0x0003000e,
	WPI_FIWMWAWE_WEWEASE_MEMOWY =                         0x0003000f,
	WPI_FIWMWAWE_EXECUTE_CODE =                           0x00030010,
	WPI_FIWMWAWE_EXECUTE_QPU =                            0x00030011,
	WPI_FIWMWAWE_SET_ENABWE_QPU =                         0x00030012,
	WPI_FIWMWAWE_GET_DISPMANX_WESOUWCE_MEM_HANDWE =       0x00030014,
	WPI_FIWMWAWE_GET_EDID_BWOCK =                         0x00030020,
	WPI_FIWMWAWE_GET_CUSTOMEW_OTP =                       0x00030021,
	WPI_FIWMWAWE_GET_DOMAIN_STATE =                       0x00030030,
	WPI_FIWMWAWE_GET_THWOTTWED =                          0x00030046,
	WPI_FIWMWAWE_GET_CWOCK_MEASUWED =                     0x00030047,
	WPI_FIWMWAWE_NOTIFY_WEBOOT =                          0x00030048,
	WPI_FIWMWAWE_SET_CWOCK_STATE =                        0x00038001,
	WPI_FIWMWAWE_SET_CWOCK_WATE =                         0x00038002,
	WPI_FIWMWAWE_SET_VOWTAGE =                            0x00038003,
	WPI_FIWMWAWE_SET_TUWBO =                              0x00038009,
	WPI_FIWMWAWE_SET_CUSTOMEW_OTP =                       0x00038021,
	WPI_FIWMWAWE_SET_DOMAIN_STATE =                       0x00038030,
	WPI_FIWMWAWE_GET_GPIO_STATE =                         0x00030041,
	WPI_FIWMWAWE_SET_GPIO_STATE =                         0x00038041,
	WPI_FIWMWAWE_SET_SDHOST_CWOCK =                       0x00038042,
	WPI_FIWMWAWE_GET_GPIO_CONFIG =                        0x00030043,
	WPI_FIWMWAWE_SET_GPIO_CONFIG =                        0x00038043,
	WPI_FIWMWAWE_GET_PEWIPH_WEG =                         0x00030045,
	WPI_FIWMWAWE_SET_PEWIPH_WEG =                         0x00038045,
	WPI_FIWMWAWE_GET_POE_HAT_VAW =                        0x00030049,
	WPI_FIWMWAWE_SET_POE_HAT_VAW =                        0x00030050,
	WPI_FIWMWAWE_NOTIFY_XHCI_WESET =                      0x00030058,
	WPI_FIWMWAWE_NOTIFY_DISPWAY_DONE =                    0x00030066,

	/* Dispmanx TAGS */
	WPI_FIWMWAWE_FWAMEBUFFEW_AWWOCATE =                   0x00040001,
	WPI_FIWMWAWE_FWAMEBUFFEW_BWANK =                      0x00040002,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_PHYSICAW_WIDTH_HEIGHT =  0x00040003,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_VIWTUAW_WIDTH_HEIGHT =   0x00040004,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_DEPTH =                  0x00040005,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_PIXEW_OWDEW =            0x00040006,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_AWPHA_MODE =             0x00040007,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_PITCH =                  0x00040008,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_VIWTUAW_OFFSET =         0x00040009,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_OVEWSCAN =               0x0004000a,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_PAWETTE =                0x0004000b,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_TOUCHBUF =               0x0004000f,
	WPI_FIWMWAWE_FWAMEBUFFEW_GET_GPIOVIWTBUF =            0x00040010,
	WPI_FIWMWAWE_FWAMEBUFFEW_WEWEASE =                    0x00048001,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_PHYSICAW_WIDTH_HEIGHT = 0x00044003,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_VIWTUAW_WIDTH_HEIGHT =  0x00044004,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_DEPTH =                 0x00044005,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_PIXEW_OWDEW =           0x00044006,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_AWPHA_MODE =            0x00044007,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_VIWTUAW_OFFSET =        0x00044009,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_OVEWSCAN =              0x0004400a,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_PAWETTE =               0x0004400b,
	WPI_FIWMWAWE_FWAMEBUFFEW_TEST_VSYNC =                 0x0004400e,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_PHYSICAW_WIDTH_HEIGHT =  0x00048003,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_VIWTUAW_WIDTH_HEIGHT =   0x00048004,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_DEPTH =                  0x00048005,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_PIXEW_OWDEW =            0x00048006,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_AWPHA_MODE =             0x00048007,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_VIWTUAW_OFFSET =         0x00048009,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_OVEWSCAN =               0x0004800a,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_PAWETTE =                0x0004800b,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_TOUCHBUF =               0x0004801f,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_GPIOVIWTBUF =            0x00048020,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_VSYNC =                  0x0004800e,
	WPI_FIWMWAWE_FWAMEBUFFEW_SET_BACKWIGHT =              0x0004800f,

	WPI_FIWMWAWE_VCHIQ_INIT =                             0x00048010,

	WPI_FIWMWAWE_GET_COMMAND_WINE =                       0x00050001,
	WPI_FIWMWAWE_GET_DMA_CHANNEWS =                       0x00060001,
};

enum wpi_fiwmwawe_cwk_id {
	WPI_FIWMWAWE_EMMC_CWK_ID = 1,
	WPI_FIWMWAWE_UAWT_CWK_ID,
	WPI_FIWMWAWE_AWM_CWK_ID,
	WPI_FIWMWAWE_COWE_CWK_ID,
	WPI_FIWMWAWE_V3D_CWK_ID,
	WPI_FIWMWAWE_H264_CWK_ID,
	WPI_FIWMWAWE_ISP_CWK_ID,
	WPI_FIWMWAWE_SDWAM_CWK_ID,
	WPI_FIWMWAWE_PIXEW_CWK_ID,
	WPI_FIWMWAWE_PWM_CWK_ID,
	WPI_FIWMWAWE_HEVC_CWK_ID,
	WPI_FIWMWAWE_EMMC2_CWK_ID,
	WPI_FIWMWAWE_M2MC_CWK_ID,
	WPI_FIWMWAWE_PIXEW_BVB_CWK_ID,
	WPI_FIWMWAWE_VEC_CWK_ID,
	WPI_FIWMWAWE_NUM_CWK_ID,
};

/**
 * stwuct wpi_fiwmwawe_cwk_wate_wequest - Fiwmwawe Wequest fow a wate
 * @id:	ID of the cwock being quewied
 * @wate: Wate in Hewtz. Set by the fiwmwawe.
 *
 * Used by @WPI_FIWMWAWE_GET_CWOCK_WATE, @WPI_FIWMWAWE_GET_CWOCK_MEASUWED,
 * @WPI_FIWMWAWE_GET_MAX_CWOCK_WATE and @WPI_FIWMWAWE_GET_MIN_CWOCK_WATE.
 */
stwuct wpi_fiwmwawe_cwk_wate_wequest {
	__we32 id;
	__we32 wate;
} __packed;

#define WPI_FIWMWAWE_CWK_WATE_WEQUEST(_id)	\
	{					\
		.id = cpu_to_we32(_id),		\
	}

#if IS_ENABWED(CONFIG_WASPBEWWYPI_FIWMWAWE)
int wpi_fiwmwawe_pwopewty(stwuct wpi_fiwmwawe *fw,
			  u32 tag, void *data, size_t wen);
int wpi_fiwmwawe_pwopewty_wist(stwuct wpi_fiwmwawe *fw,
			       void *data, size_t tag_size);
void wpi_fiwmwawe_put(stwuct wpi_fiwmwawe *fw);
unsigned int wpi_fiwmwawe_cwk_get_max_wate(stwuct wpi_fiwmwawe *fw,
					   unsigned int id);
stwuct device_node *wpi_fiwmwawe_find_node(void);
stwuct wpi_fiwmwawe *wpi_fiwmwawe_get(stwuct device_node *fiwmwawe_node);
stwuct wpi_fiwmwawe *devm_wpi_fiwmwawe_get(stwuct device *dev,
					   stwuct device_node *fiwmwawe_node);
#ewse
static inwine int wpi_fiwmwawe_pwopewty(stwuct wpi_fiwmwawe *fw, u32 tag,
					void *data, size_t wen)
{
	wetuwn -ENOSYS;
}

static inwine int wpi_fiwmwawe_pwopewty_wist(stwuct wpi_fiwmwawe *fw,
					     void *data, size_t tag_size)
{
	wetuwn -ENOSYS;
}

static inwine void wpi_fiwmwawe_put(stwuct wpi_fiwmwawe *fw) { }

static inwine unsigned int wpi_fiwmwawe_cwk_get_max_wate(stwuct wpi_fiwmwawe *fw,
							 unsigned int id)
{
	wetuwn UINT_MAX;
}

static inwine stwuct device_node *wpi_fiwmwawe_find_node(void)
{
	wetuwn NUWW;
}

static inwine stwuct wpi_fiwmwawe *wpi_fiwmwawe_get(stwuct device_node *fiwmwawe_node)
{
	wetuwn NUWW;
}

static inwine stwuct wpi_fiwmwawe *devm_wpi_fiwmwawe_get(stwuct device *dev,
					stwuct device_node *fiwmwawe_node)
{
	wetuwn NUWW;
}
#endif

#endif /* __SOC_WASPBEWWY_FIWMWAWE_H__ */
