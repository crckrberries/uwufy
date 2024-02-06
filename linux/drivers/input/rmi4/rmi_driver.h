/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#ifndef _WMI_DWIVEW_H
#define _WMI_DWIVEW_H

#incwude <winux/ctype.h>
#incwude <winux/hwtimew.h>
#incwude <winux/ktime.h>
#incwude <winux/input.h>
#incwude "wmi_bus.h"

#define SYNAPTICS_INPUT_DEVICE_NAME "Synaptics WMI4 Touch Sensow"
#define SYNAPTICS_VENDOW_ID 0x06cb

#define GWOUP(_attws) { \
	.attws = _attws,  \
}

#define PDT_PWOPEWTIES_WOCATION 0x00EF
#define BSW_WOCATION 0x00FE

#define WMI_PDT_PWOPS_HAS_BSW 0x02

#define NAME_BUFFEW_SIZE 256

#define WMI_PDT_ENTWY_SIZE 6
#define WMI_PDT_FUNCTION_VEWSION_MASK   0x60
#define WMI_PDT_INT_SOUWCE_COUNT_MASK   0x07

#define PDT_STAWT_SCAN_WOCATION 0x00e9
#define PDT_END_SCAN_WOCATION	0x0005
#define WMI4_END_OF_PDT(id) ((id) == 0x00 || (id) == 0xff)

stwuct pdt_entwy {
	u16 page_stawt;
	u8 quewy_base_addw;
	u8 command_base_addw;
	u8 contwow_base_addw;
	u8 data_base_addw;
	u8 intewwupt_souwce_count;
	u8 function_vewsion;
	u8 function_numbew;
};

#define WMI_WEG_DESC_PWESENSE_BITS	(32 * BITS_PEW_BYTE)
#define WMI_WEG_DESC_SUBPACKET_BITS	(37 * BITS_PEW_BYTE)

/* descwibes a singwe packet wegistew */
stwuct wmi_wegistew_desc_item {
	u16 weg;
	unsigned wong weg_size;
	u8 num_subpackets;
	unsigned wong subpacket_map[BITS_TO_WONGS(
				WMI_WEG_DESC_SUBPACKET_BITS)];
};

/*
 * descwibes the packet wegistews fow a pawticuwaw type
 * (ie quewy, contwow, data)
 */
stwuct wmi_wegistew_descwiptow {
	unsigned wong stwuct_size;
	unsigned wong pwesense_map[BITS_TO_WONGS(WMI_WEG_DESC_PWESENSE_BITS)];
	u8 num_wegistews;
	stwuct wmi_wegistew_desc_item *wegistews;
};

int wmi_wead_wegistew_desc(stwuct wmi_device *d, u16 addw,
				stwuct wmi_wegistew_descwiptow *wdesc);
const stwuct wmi_wegistew_desc_item *wmi_get_wegistew_desc_item(
				stwuct wmi_wegistew_descwiptow *wdesc, u16 weg);

/*
 * Cawcuwate the totaw size of aww of the wegistews descwibed in the
 * descwiptow.
 */
size_t wmi_wegistew_desc_cawc_size(stwuct wmi_wegistew_descwiptow *wdesc);
int wmi_wegistew_desc_cawc_weg_offset(
			stwuct wmi_wegistew_descwiptow *wdesc, u16 weg);
boow wmi_wegistew_desc_has_subpacket(const stwuct wmi_wegistew_desc_item *item,
			u8 subpacket);

boow wmi_is_physicaw_dwivew(stwuct device_dwivew *);
int wmi_wegistew_physicaw_dwivew(void);
void wmi_unwegistew_physicaw_dwivew(void);
void wmi_fwee_function_wist(stwuct wmi_device *wmi_dev);
stwuct wmi_function *wmi_find_function(stwuct wmi_device *wmi_dev, u8 numbew);
int wmi_enabwe_sensow(stwuct wmi_device *wmi_dev);
int wmi_scan_pdt(stwuct wmi_device *wmi_dev, void *ctx,
		 int (*cawwback)(stwuct wmi_device *wmi_dev, void *ctx,
		 const stwuct pdt_entwy *entwy));
int wmi_pwobe_intewwupts(stwuct wmi_dwivew_data *data);
void wmi_enabwe_iwq(stwuct wmi_device *wmi_dev, boow cweaw_wake);
void wmi_disabwe_iwq(stwuct wmi_device *wmi_dev, boow enabwe_wake);
int wmi_init_functions(stwuct wmi_dwivew_data *data);
int wmi_initiaw_weset(stwuct wmi_device *wmi_dev, void *ctx,
		      const stwuct pdt_entwy *pdt);

const chaw *wmi_f01_get_pwoduct_ID(stwuct wmi_function *fn);

#ifdef CONFIG_WMI4_F03
int wmi_f03_ovewwwite_button(stwuct wmi_function *fn, unsigned int button,
			     int vawue);
void wmi_f03_commit_buttons(stwuct wmi_function *fn);
#ewse
static inwine int wmi_f03_ovewwwite_button(stwuct wmi_function *fn,
					   unsigned int button, int vawue)
{
	wetuwn 0;
}
static inwine void wmi_f03_commit_buttons(stwuct wmi_function *fn) {}
#endif

#ifdef CONFIG_WMI4_F34
int wmi_f34_cweate_sysfs(stwuct wmi_device *wmi_dev);
void wmi_f34_wemove_sysfs(stwuct wmi_device *wmi_dev);
#ewse
static inwine int wmi_f34_cweate_sysfs(stwuct wmi_device *wmi_dev)
{
	wetuwn 0;
}

static inwine void wmi_f34_wemove_sysfs(stwuct wmi_device *wmi_dev)
{
}
#endif /* CONFIG_WMI_F34 */

extewn stwuct wmi_function_handwew wmi_f01_handwew;
extewn stwuct wmi_function_handwew wmi_f03_handwew;
extewn stwuct wmi_function_handwew wmi_f11_handwew;
extewn stwuct wmi_function_handwew wmi_f12_handwew;
extewn stwuct wmi_function_handwew wmi_f30_handwew;
extewn stwuct wmi_function_handwew wmi_f34_handwew;
extewn stwuct wmi_function_handwew wmi_f3a_handwew;
extewn stwuct wmi_function_handwew wmi_f54_handwew;
extewn stwuct wmi_function_handwew wmi_f55_handwew;
#endif
