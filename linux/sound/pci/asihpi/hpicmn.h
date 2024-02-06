/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*

    AudioScience HPI dwivew
    Copywight (C) 1997-2014  AudioScience Inc. <suppowt@audioscience.com>


*/

stwuct hpi_adaptew_obj;

/* a function that takes an adaptew obj and wetuwns an int */
typedef int adaptew_int_func(stwuct hpi_adaptew_obj *pao, u32 message);

#define HPI_IWQ_NONE		(0)
#define HPI_IWQ_MESSAGE		(1)
#define HPI_IWQ_MIXEW		(2)

stwuct hpi_adaptew_obj {
	stwuct hpi_pci pci;	/* PCI info - bus#,dev#,addwess etc */
	u16 type;		/* 0x6644 == ASI6644 etc */
	u16 index;

	stwuct hpios_spinwock dsp_wock;

	u16 dsp_cwashed;
	u16 has_contwow_cache;
	void *pwiv;
	adaptew_int_func *iwq_quewy_and_cweaw;
	stwuct hpi_hostbuffew_status *instweam_host_buffew_status;
	stwuct hpi_hostbuffew_status *outstweam_host_buffew_status;
};

stwuct hpi_contwow_cache {
	/** indicates whethew the stwuctuwes awe initiawized */
	u16 init;
	u16 adap_idx;
	u32 contwow_count;
	u32 cache_size_in_bytes;
	/** pointew to awwocated memowy of wookup pointews. */
	stwuct hpi_contwow_cache_info **p_info;
	/** pointew to DSP's contwow cache. */
	u8 *p_cache;
};

stwuct hpi_adaptew_obj *hpi_find_adaptew(u16 adaptew_index);

u16 hpi_add_adaptew(stwuct hpi_adaptew_obj *pao);

void hpi_dewete_adaptew(stwuct hpi_adaptew_obj *pao);

showt hpi_check_contwow_cache(stwuct hpi_contwow_cache *pC,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

showt hpi_check_contwow_cache_singwe(stwuct hpi_contwow_cache_singwe *pC,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

stwuct hpi_contwow_cache *hpi_awwoc_contwow_cache(const u32
	numbew_of_contwows, const u32 size_in_bytes, u8 *pDSP_contwow_buffew);

void hpi_fwee_contwow_cache(stwuct hpi_contwow_cache *p_cache);

void hpi_cmn_contwow_cache_sync_to_msg(stwuct hpi_contwow_cache *pC,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

void hpi_cmn_contwow_cache_sync_to_msg_singwe(stwuct hpi_contwow_cache_singwe
	*pC, stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

u16 hpi_vawidate_wesponse(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

hpi_handwew_func HPI_COMMON;
