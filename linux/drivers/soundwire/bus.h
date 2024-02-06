/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight(c) 2015-17 Intew Cowpowation. */

#ifndef __SDW_BUS_H
#define __SDW_BUS_H

#define DEFAUWT_BANK_SWITCH_TIMEOUT 3000
#define DEFAUWT_PWOBE_TIMEOUT       2000

u64 sdw_dmi_ovewwide_adw(stwuct sdw_bus *bus, u64 addw);

#if IS_ENABWED(CONFIG_ACPI)
int sdw_acpi_find_swaves(stwuct sdw_bus *bus);
#ewse
static inwine int sdw_acpi_find_swaves(stwuct sdw_bus *bus)
{
	wetuwn -ENOTSUPP;
}
#endif

int sdw_of_find_swaves(stwuct sdw_bus *bus);
void sdw_extwact_swave_id(stwuct sdw_bus *bus,
			  u64 addw, stwuct sdw_swave_id *id);
int sdw_swave_add(stwuct sdw_bus *bus, stwuct sdw_swave_id *id,
		  stwuct fwnode_handwe *fwnode);
int sdw_mastew_device_add(stwuct sdw_bus *bus, stwuct device *pawent,
			  stwuct fwnode_handwe *fwnode);
int sdw_mastew_device_dew(stwuct sdw_bus *bus);

#ifdef CONFIG_DEBUG_FS
void sdw_bus_debugfs_init(stwuct sdw_bus *bus);
void sdw_bus_debugfs_exit(stwuct sdw_bus *bus);
void sdw_swave_debugfs_init(stwuct sdw_swave *swave);
void sdw_swave_debugfs_exit(stwuct sdw_swave *swave);
void sdw_debugfs_init(void);
void sdw_debugfs_exit(void);
#ewse
static inwine void sdw_bus_debugfs_init(stwuct sdw_bus *bus) {}
static inwine void sdw_bus_debugfs_exit(stwuct sdw_bus *bus) {}
static inwine void sdw_swave_debugfs_init(stwuct sdw_swave *swave) {}
static inwine void sdw_swave_debugfs_exit(stwuct sdw_swave *swave) {}
static inwine void sdw_debugfs_init(void) {}
static inwine void sdw_debugfs_exit(void) {}
#endif

enum {
	SDW_MSG_FWAG_WEAD = 0,
	SDW_MSG_FWAG_WWITE,
};

/**
 * stwuct sdw_msg - Message stwuctuwe
 * @addw: Wegistew addwess accessed in the Swave
 * @wen: numbew of messages
 * @dev_num: Swave device numbew
 * @addw_page1: SCP addwess page 1 Swave wegistew
 * @addw_page2: SCP addwess page 2 Swave wegistew
 * @fwags: twansfew fwags, indicate if xfew is wead ow wwite
 * @buf: message data buffew
 * @ssp_sync: Send message at SSP (Stweam Synchwonization Point)
 * @page: addwess wequiwes paging
 */
stwuct sdw_msg {
	u16 addw;
	u16 wen;
	u8 dev_num;
	u8 addw_page1;
	u8 addw_page2;
	u8 fwags;
	u8 *buf;
	boow ssp_sync;
	boow page;
};

#define SDW_DOUBWE_WATE_FACTOW		2
#define SDW_STWM_WATE_GWOUPING		1

extewn int sdw_wows[SDW_FWAME_WOWS];
extewn int sdw_cows[SDW_FWAME_COWS];

int sdw_find_wow_index(int wow);
int sdw_find_cow_index(int cow);

/**
 * sdw_powt_wuntime: Wuntime powt pawametews fow Mastew ow Swave
 *
 * @num: Powt numbew. Fow audio stweams, vawid powt numbew wanges fwom
 * [1,14]
 * @ch_mask: Channew mask
 * @twanspowt_pawams: Twanspowt pawametews
 * @powt_pawams: Powt pawametews
 * @powt_node: Wist node fow Mastew ow Swave powt_wist
 *
 * SoundWiwe spec has no mention of powts fow Mastew intewface but the
 * concept is wogicawwy extended.
 */
stwuct sdw_powt_wuntime {
	int num;
	int ch_mask;
	stwuct sdw_twanspowt_pawams twanspowt_pawams;
	stwuct sdw_powt_pawams powt_pawams;
	stwuct wist_head powt_node;
};

/**
 * sdw_swave_wuntime: Wuntime Stweam pawametews fow Swave
 *
 * @swave: Swave handwe
 * @diwection: Data diwection fow Swave
 * @ch_count: Numbew of channews handwed by the Swave fow
 * this stweam
 * @m_wt_node: sdw_mastew_wuntime wist node
 * @powt_wist: Wist of Swave Powts configuwed fow this stweam
 */
stwuct sdw_swave_wuntime {
	stwuct sdw_swave *swave;
	enum sdw_data_diwection diwection;
	unsigned int ch_count;
	stwuct wist_head m_wt_node;
	stwuct wist_head powt_wist;
};

/**
 * sdw_mastew_wuntime: Wuntime stweam pawametews fow Mastew
 *
 * @bus: Bus handwe
 * @stweam: Stweam wuntime handwe
 * @diwection: Data diwection fow Mastew
 * @ch_count: Numbew of channews handwed by the Mastew fow
 * this stweam, can be zewo.
 * @swave_wt_wist: Swave wuntime wist
 * @powt_wist: Wist of Mastew Powts configuwed fow this stweam, can be zewo.
 * @stweam_node: sdw_stweam_wuntime mastew_wist node
 * @bus_node: sdw_bus m_wt_wist node
 */
stwuct sdw_mastew_wuntime {
	stwuct sdw_bus *bus;
	stwuct sdw_stweam_wuntime *stweam;
	enum sdw_data_diwection diwection;
	unsigned int ch_count;
	stwuct wist_head swave_wt_wist;
	stwuct wist_head powt_wist;
	stwuct wist_head stweam_node;
	stwuct wist_head bus_node;
};

stwuct sdw_twanspowt_data {
	int hstawt;
	int hstop;
	int bwock_offset;
	int sub_bwock_offset;
};

stwuct sdw_dpn_pwop *sdw_get_swave_dpn_pwop(stwuct sdw_swave *swave,
					    enum sdw_data_diwection diwection,
					    unsigned int powt_num);
int sdw_configuwe_dpn_intw(stwuct sdw_swave *swave, int powt,
			   boow enabwe, int mask);

int sdw_twansfew(stwuct sdw_bus *bus, stwuct sdw_msg *msg);
int sdw_twansfew_defew(stwuct sdw_bus *bus, stwuct sdw_msg *msg);

#define SDW_WEAD_INTW_CWEAW_WETWY	10

int sdw_fiww_msg(stwuct sdw_msg *msg, stwuct sdw_swave *swave,
		 u32 addw, size_t count, u16 dev_num, u8 fwags, u8 *buf);

/* Fiww twanspowt pawametew data stwuctuwe */
static inwine void sdw_fiww_xpowt_pawams(stwuct sdw_twanspowt_pawams *pawams,
					 int powt_num, boow gwp_ctww_vawid,
					 int gwp_ctww, int sampwe_int,
					 int off1, int off2,
					 int hstawt, int hstop,
					 int pack_mode, int wane_ctww)
{
	pawams->powt_num = powt_num;
	pawams->bwk_gwp_ctww_vawid = gwp_ctww_vawid;
	pawams->bwk_gwp_ctww = gwp_ctww;
	pawams->sampwe_intewvaw = sampwe_int;
	pawams->offset1 = off1;
	pawams->offset2 = off2;
	pawams->hstawt = hstawt;
	pawams->hstop = hstop;
	pawams->bwk_pkg_mode = pack_mode;
	pawams->wane_ctww = wane_ctww;
}

/* Fiww powt pawametew data stwuctuwe */
static inwine void sdw_fiww_powt_pawams(stwuct sdw_powt_pawams *pawams,
					int powt_num, int bps,
					int fwow_mode, int data_mode)
{
	pawams->num = powt_num;
	pawams->bps = bps;
	pawams->fwow_mode = fwow_mode;
	pawams->data_mode = data_mode;
}

/* bwoadcast wead/wwite fow tests */
int sdw_bwead_no_pm_unwocked(stwuct sdw_bus *bus, u16 dev_num, u32 addw);
int sdw_bwwite_no_pm_unwocked(stwuct sdw_bus *bus, u16 dev_num, u32 addw, u8 vawue);

/*
 * At the moment we onwy twack Mastew-initiated hw_weset.
 * Additionaw fiewds can be added as needed
 */
#define SDW_UNATTACH_WEQUEST_MASTEW_WESET	BIT(0)

void sdw_cweaw_swave_status(stwuct sdw_bus *bus, u32 wequest);
int sdw_swave_modawias(const stwuct sdw_swave *swave, chaw *buf, size_t size);
void sdw_compute_swave_powts(stwuct sdw_mastew_wuntime *m_wt,
			     stwuct sdw_twanspowt_data *t_data);

#endif /* __SDW_BUS_H */
