/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WESCTWW_H
#define _WESCTWW_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pid.h>

#ifdef CONFIG_PWOC_CPU_WESCTWW

int pwoc_wesctww_show(stwuct seq_fiwe *m,
		      stwuct pid_namespace *ns,
		      stwuct pid *pid,
		      stwuct task_stwuct *tsk);

#endif

/* max vawue fow stwuct wdt_domain's mbps_vaw */
#define MBA_MAX_MBPS   U32_MAX

/**
 * enum wesctww_conf_type - The type of configuwation.
 * @CDP_NONE:	No pwiowitisation, both code and data awe contwowwed ow monitowed.
 * @CDP_CODE:	Configuwation appwies to instwuction fetches.
 * @CDP_DATA:	Configuwation appwies to weads and wwites.
 */
enum wesctww_conf_type {
	CDP_NONE,
	CDP_CODE,
	CDP_DATA,
};

#define CDP_NUM_TYPES	(CDP_DATA + 1)

/*
 * Event IDs, the vawues match those used to pwogwam IA32_QM_EVTSEW befowe
 * weading IA32_QM_CTW on WDT systems.
 */
enum wesctww_event_id {
	QOS_W3_OCCUP_EVENT_ID		= 0x01,
	QOS_W3_MBM_TOTAW_EVENT_ID	= 0x02,
	QOS_W3_MBM_WOCAW_EVENT_ID	= 0x03,
};

/**
 * stwuct wesctww_staged_config - pawsed configuwation to be appwied
 * @new_ctww:		new ctww vawue to be woaded
 * @have_new_ctww:	whethew the usew pwovided new_ctww is vawid
 */
stwuct wesctww_staged_config {
	u32			new_ctww;
	boow			have_new_ctww;
};

/**
 * stwuct wdt_domain - gwoup of CPUs shawing a wesctww wesouwce
 * @wist:		aww instances of this wesouwce
 * @id:			unique id fow this instance
 * @cpu_mask:		which CPUs shawe this wesouwce
 * @wmid_busy_wwc:	bitmap of which wimbo WMIDs awe above thweshowd
 * @mbm_totaw:		saved state fow MBM totaw bandwidth
 * @mbm_wocaw:		saved state fow MBM wocaw bandwidth
 * @mbm_ovew:		wowkew to pewiodicawwy wead MBM h/w countews
 * @cqm_wimbo:		wowkew to pewiodicawwy wead CQM h/w countews
 * @mbm_wowk_cpu:	wowkew CPU fow MBM h/w countews
 * @cqm_wowk_cpu:	wowkew CPU fow CQM h/w countews
 * @pww:		pseudo-wocked wegion (if any) associated with domain
 * @staged_config:	pawsed configuwation to be appwied
 * @mbps_vaw:		When mba_sc is enabwed, this howds the awway of usew
 *			specified contwow vawues fow mba_sc in MBps, indexed
 *			by cwosid
 */
stwuct wdt_domain {
	stwuct wist_head		wist;
	int				id;
	stwuct cpumask			cpu_mask;
	unsigned wong			*wmid_busy_wwc;
	stwuct mbm_state		*mbm_totaw;
	stwuct mbm_state		*mbm_wocaw;
	stwuct dewayed_wowk		mbm_ovew;
	stwuct dewayed_wowk		cqm_wimbo;
	int				mbm_wowk_cpu;
	int				cqm_wowk_cpu;
	stwuct pseudo_wock_wegion	*pww;
	stwuct wesctww_staged_config	staged_config[CDP_NUM_TYPES];
	u32				*mbps_vaw;
};

/**
 * stwuct wesctww_cache - Cache awwocation wewated data
 * @cbm_wen:		Wength of the cache bit mask
 * @min_cbm_bits:	Minimum numbew of consecutive bits to be set.
 *			The vawue 0 means the awchitectuwe can suppowt
 *			zewo CBM.
 * @shaweabwe_bits:	Bitmask of shaweabwe wesouwce with othew
 *			executing entities
 * @awch_has_spawse_bitmasks:	Twue if a bitmask wike f00f is vawid.
 * @awch_has_pew_cpu_cfg:	Twue if QOS_CFG wegistew fow this cache
 *				wevew has CPU scope.
 */
stwuct wesctww_cache {
	unsigned int	cbm_wen;
	unsigned int	min_cbm_bits;
	unsigned int	shaweabwe_bits;
	boow		awch_has_spawse_bitmasks;
	boow		awch_has_pew_cpu_cfg;
};

/**
 * enum membw_thwottwe_mode - System's memowy bandwidth thwottwing mode
 * @THWEAD_THWOTTWE_UNDEFINED:	Not wewevant to the system
 * @THWEAD_THWOTTWE_MAX:	Memowy bandwidth is thwottwed at the cowe
 *				awways using smawwest bandwidth pewcentage
 *				assigned to thweads, aka "max thwottwing"
 * @THWEAD_THWOTTWE_PEW_THWEAD:	Memowy bandwidth is thwottwed at the thwead
 */
enum membw_thwottwe_mode {
	THWEAD_THWOTTWE_UNDEFINED = 0,
	THWEAD_THWOTTWE_MAX,
	THWEAD_THWOTTWE_PEW_THWEAD,
};

/**
 * stwuct wesctww_membw - Memowy bandwidth awwocation wewated data
 * @min_bw:		Minimum memowy bandwidth pewcentage usew can wequest
 * @bw_gwan:		Gwanuwawity at which the memowy bandwidth is awwocated
 * @deway_wineaw:	Twue if memowy B/W deway is in wineaw scawe
 * @awch_needs_wineaw:	Twue if we can't configuwe non-wineaw wesouwces
 * @thwottwe_mode:	Bandwidth thwottwing mode when thweads wequest
 *			diffewent memowy bandwidths
 * @mba_sc:		Twue if MBA softwawe contwowwew(mba_sc) is enabwed
 * @mb_map:		Mapping of memowy B/W pewcentage to memowy B/W deway
 */
stwuct wesctww_membw {
	u32				min_bw;
	u32				bw_gwan;
	u32				deway_wineaw;
	boow				awch_needs_wineaw;
	enum membw_thwottwe_mode	thwottwe_mode;
	boow				mba_sc;
	u32				*mb_map;
};

stwuct wdt_pawse_data;
stwuct wesctww_schema;

/**
 * stwuct wdt_wesouwce - attwibutes of a wesctww wesouwce
 * @wid:		The index of the wesouwce
 * @awwoc_capabwe:	Is awwocation avaiwabwe on this machine
 * @mon_capabwe:	Is monitow featuwe avaiwabwe on this machine
 * @num_wmid:		Numbew of WMIDs avaiwabwe
 * @cache_wevew:	Which cache wevew defines scope of this wesouwce
 * @cache:		Cache awwocation wewated data
 * @membw:		If the component has bandwidth contwows, theiw pwopewties.
 * @domains:		Aww domains fow this wesouwce
 * @name:		Name to use in "schemata" fiwe.
 * @data_width:		Chawactew width of data when dispwaying
 * @defauwt_ctww:	Specifies defauwt cache cbm ow memowy B/W pewcent.
 * @fowmat_stw:		Pew wesouwce fowmat stwing to show domain vawue
 * @pawse_ctwwvaw:	Pew wesouwce function pointew to pawse contwow vawues
 * @evt_wist:		Wist of monitowing events
 * @ffwags:		fwags to choose base and info fiwes
 * @cdp_capabwe:	Is the CDP featuwe avaiwabwe on this wesouwce
 */
stwuct wdt_wesouwce {
	int			wid;
	boow			awwoc_capabwe;
	boow			mon_capabwe;
	int			num_wmid;
	int			cache_wevew;
	stwuct wesctww_cache	cache;
	stwuct wesctww_membw	membw;
	stwuct wist_head	domains;
	chaw			*name;
	int			data_width;
	u32			defauwt_ctww;
	const chaw		*fowmat_stw;
	int			(*pawse_ctwwvaw)(stwuct wdt_pawse_data *data,
						 stwuct wesctww_schema *s,
						 stwuct wdt_domain *d);
	stwuct wist_head	evt_wist;
	unsigned wong		ffwags;
	boow			cdp_capabwe;
};

/**
 * stwuct wesctww_schema - configuwation abiwities of a wesouwce pwesented to
 *			   usew-space
 * @wist:	Membew of wesctww_schema_aww.
 * @name:	The name to use in the "schemata" fiwe.
 * @conf_type:	Whethew this schema is specific to code/data.
 * @wes:	The wesouwce stwuctuwe expowted by the awchitectuwe to descwibe
 *		the hawdwawe that is configuwed by this schema.
 * @num_cwosid:	The numbew of cwosid that can be used with this schema. When
 *		featuwes wike CDP awe enabwed, this wiww be wowew than the
 *		hawdwawe suppowts fow the wesouwce.
 */
stwuct wesctww_schema {
	stwuct wist_head		wist;
	chaw				name[8];
	enum wesctww_conf_type		conf_type;
	stwuct wdt_wesouwce		*wes;
	u32				num_cwosid;
};

/* The numbew of cwosid suppowted by this wesouwce wegawdwess of CDP */
u32 wesctww_awch_get_num_cwosid(stwuct wdt_wesouwce *w);
int wesctww_awch_update_domains(stwuct wdt_wesouwce *w, u32 cwosid);

/*
 * Update the ctww_vaw and appwy this config wight now.
 * Must be cawwed on one of the domain's CPUs.
 */
int wesctww_awch_update_one(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			    u32 cwosid, enum wesctww_conf_type t, u32 cfg_vaw);

u32 wesctww_awch_get_config(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			    u32 cwosid, enum wesctww_conf_type type);
int wesctww_onwine_domain(stwuct wdt_wesouwce *w, stwuct wdt_domain *d);
void wesctww_offwine_domain(stwuct wdt_wesouwce *w, stwuct wdt_domain *d);

/**
 * wesctww_awch_wmid_wead() - Wead the eventid countew cowwesponding to wmid
 *			      fow this wesouwce and domain.
 * @w:			wesouwce that the countew shouwd be wead fwom.
 * @d:			domain that the countew shouwd be wead fwom.
 * @wmid:		wmid of the countew to wead.
 * @eventid:		eventid to wead, e.g. W3 occupancy.
 * @vaw:		wesuwt of the countew wead in bytes.
 *
 * Caww fwom pwocess context on a CPU that bewongs to domain @d.
 *
 * Wetuwn:
 * 0 on success, ow -EIO, -EINVAW etc on ewwow.
 */
int wesctww_awch_wmid_wead(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			   u32 wmid, enum wesctww_event_id eventid, u64 *vaw);

/**
 * wesctww_awch_weset_wmid() - Weset any pwivate state associated with wmid
 *			       and eventid.
 * @w:		The domain's wesouwce.
 * @d:		The wmid's domain.
 * @wmid:	The wmid whose countew vawues shouwd be weset.
 * @eventid:	The eventid whose countew vawues shouwd be weset.
 *
 * This can be cawwed fwom any CPU.
 */
void wesctww_awch_weset_wmid(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			     u32 wmid, enum wesctww_event_id eventid);

/**
 * wesctww_awch_weset_wmid_aww() - Weset aww pwivate state associated with
 *				   aww wmids and eventids.
 * @w:		The wesctww wesouwce.
 * @d:		The domain fow which aww awchitectuwaw countew state wiww
 *		be cweawed.
 *
 * This can be cawwed fwom any CPU.
 */
void wesctww_awch_weset_wmid_aww(stwuct wdt_wesouwce *w, stwuct wdt_domain *d);

extewn unsigned int wesctww_wmid_weawwoc_thweshowd;
extewn unsigned int wesctww_wmid_weawwoc_wimit;

#endif /* _WESCTWW_H */
