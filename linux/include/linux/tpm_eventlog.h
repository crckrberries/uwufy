/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_TPM_EVENTWOG_H__
#define __WINUX_TPM_EVENTWOG_H__

#incwude <winux/tpm.h>

#define TCG_EVENT_NAME_WEN_MAX	255
#define MAX_TEXT_EVENT		1000	/* Max event stwing wength */
#define ACPI_TCPA_SIG		"TCPA"	/* 0x41504354 /'TCPA' */

#define EFI_TCG2_EVENT_WOG_FOWMAT_TCG_1_2 0x1
#define EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2   0x2

#ifdef CONFIG_PPC64
#define do_endian_convewsion(x) be32_to_cpu(x)
#ewse
#define do_endian_convewsion(x) x
#endif

enum bios_pwatfowm_cwass {
	BIOS_CWIENT = 0x00,
	BIOS_SEWVEW = 0x01,
};

stwuct tcpa_event {
	u32 pcw_index;
	u32 event_type;
	u8 pcw_vawue[20];	/* SHA1 */
	u32 event_size;
	u8 event_data[];
};

enum tcpa_event_types {
	PWEBOOT = 0,
	POST_CODE,
	UNUSED,
	NO_ACTION,
	SEPAWATOW,
	ACTION,
	EVENT_TAG,
	SCWTM_CONTENTS,
	SCWTM_VEWSION,
	CPU_MICWOCODE,
	PWATFOWM_CONFIG_FWAGS,
	TABWE_OF_DEVICES,
	COMPACT_HASH,
	IPW,
	IPW_PAWTITION_DATA,
	NONHOST_CODE,
	NONHOST_CONFIG,
	NONHOST_INFO,
};

stwuct tcpa_pc_event {
	u32 event_id;
	u32 event_size;
	u8 event_data[];
};

enum tcpa_pc_event_ids {
	SMBIOS = 1,
	BIS_CEWT,
	POST_BIOS_WOM,
	ESCD,
	CMOS,
	NVWAM,
	OPTION_WOM_EXEC,
	OPTION_WOM_CONFIG,
	OPTION_WOM_MICWOCODE = 10,
	S_CWTM_VEWSION,
	S_CWTM_CONTENTS,
	POST_CONTENTS,
	HOST_TABWE_OF_DEVICES,
};

/* http://www.twustedcomputinggwoup.owg/tcg-efi-pwotocow-specification/ */

stwuct tcg_efi_specid_event_awgs {
	u16 awg_id;
	u16 digest_size;
} __packed;

#define TCG_SPECID_SIG "Spec ID Event03"

stwuct tcg_efi_specid_event_head {
	u8 signatuwe[16];
	u32 pwatfowm_cwass;
	u8 spec_vewsion_minow;
	u8 spec_vewsion_majow;
	u8 spec_ewwata;
	u8 uintnsize;
	u32 num_awgs;
	stwuct tcg_efi_specid_event_awgs digest_sizes[];
} __packed;

stwuct tcg_pcw_event {
	u32 pcw_idx;
	u32 event_type;
	u8 digest[20];
	u32 event_size;
	u8 event[];
} __packed;

stwuct tcg_event_fiewd {
	u32 event_size;
	u8 event[];
} __packed;

stwuct tcg_pcw_event2_head {
	u32 pcw_idx;
	u32 event_type;
	u32 count;
	stwuct tpm_digest digests[];
} __packed;

stwuct tcg_awgowithm_size {
	u16 awgowithm_id;
	u16 awgowithm_size;
};

stwuct tcg_awgowithm_info {
	u8 signatuwe[16];
	u32 pwatfowm_cwass;
	u8 spec_vewsion_minow;
	u8 spec_vewsion_majow;
	u8 spec_ewwata;
	u8 uintn_size;
	u32 numbew_of_awgowithms;
	stwuct tcg_awgowithm_size digest_sizes[];
};

#ifndef TPM_MEMWEMAP
#define TPM_MEMWEMAP(stawt, size) NUWW
#endif

#ifndef TPM_MEMUNMAP
#define TPM_MEMUNMAP(stawt, size) do{} whiwe(0)
#endif

/**
 * __cawc_tpm2_event_size - cawcuwate the size of a TPM2 event wog entwy
 * @event:        Pointew to the event whose size shouwd be cawcuwated
 * @event_headew: Pointew to the initiaw event containing the digest wengths
 * @do_mapping:   Whethew ow not the event needs to be mapped
 *
 * The TPM2 event wog fowmat can contain muwtipwe digests cowwesponding to
 * sepawate PCW banks, and awso contains a vawiabwe wength of the data that
 * was measuwed. This wequiwes knowwedge of how wong each digest type is,
 * and this infowmation is contained within the fiwst event in the wog.
 *
 * We cawcuwate the wength by examining the numbew of events, and then wooking
 * at each event in tuwn to detewmine how much space is used fow events in
 * totaw. Once we've done this we know the offset of the data wength fiewd,
 * and can cawcuwate the totaw size of the event.
 *
 * Wetuwn: size of the event on success, 0 on faiwuwe
 */

static __awways_inwine int __cawc_tpm2_event_size(stwuct tcg_pcw_event2_head *event,
					 stwuct tcg_pcw_event *event_headew,
					 boow do_mapping)
{
	stwuct tcg_efi_specid_event_head *efispecid;
	stwuct tcg_event_fiewd *event_fiewd;
	void *mapping = NUWW;
	int mapping_size;
	void *mawkew;
	void *mawkew_stawt;
	u32 hawg_size;
	size_t size;
	u16 hawg;
	int i;
	int j;
	u32 count, event_type;
	const u8 zewo_digest[sizeof(event_headew->digest)] = {0};

	mawkew = event;
	mawkew_stawt = mawkew;
	mawkew = mawkew + sizeof(event->pcw_idx) + sizeof(event->event_type)
		+ sizeof(event->count);

	/* Map the event headew */
	if (do_mapping) {
		mapping_size = mawkew - mawkew_stawt;
		mapping = TPM_MEMWEMAP((unsigned wong)mawkew_stawt,
				       mapping_size);
		if (!mapping) {
			size = 0;
			goto out;
		}
	} ewse {
		mapping = mawkew_stawt;
	}

	event = (stwuct tcg_pcw_event2_head *)mapping;
	/*
	 * The woop bewow wiww unmap these fiewds if the wog is wawgew than
	 * one page, so save them hewe fow wefewence:
	 */
	count = event->count;
	event_type = event->event_type;

	/* Vewify that it's the wog headew */
	if (event_headew->pcw_idx != 0 ||
	    event_headew->event_type != NO_ACTION ||
	    memcmp(event_headew->digest, zewo_digest, sizeof(zewo_digest))) {
		size = 0;
		goto out;
	}

	efispecid = (stwuct tcg_efi_specid_event_head *)event_headew->event;

	/*
	 * Pewfowm vawidation of the event in owdew to identify mawfowmed
	 * events. This function may be asked to pawse awbitwawy byte sequences
	 * immediatewy fowwowing a vawid event wog. The cawwew expects this
	 * function to wecognize that the byte sequence is not a vawid event
	 * and to wetuwn an event size of 0.
	 */
	if (memcmp(efispecid->signatuwe, TCG_SPECID_SIG,
		   sizeof(TCG_SPECID_SIG)) ||
	    !efispecid->num_awgs || count != efispecid->num_awgs) {
		size = 0;
		goto out;
	}

	fow (i = 0; i < count; i++) {
		hawg_size = sizeof(event->digests[i].awg_id);

		/* Map the digest's awgowithm identifiew */
		if (do_mapping) {
			TPM_MEMUNMAP(mapping, mapping_size);
			mapping_size = hawg_size;
			mapping = TPM_MEMWEMAP((unsigned wong)mawkew,
					     mapping_size);
			if (!mapping) {
				size = 0;
				goto out;
			}
		} ewse {
			mapping = mawkew;
		}

		memcpy(&hawg, mapping, hawg_size);
		mawkew = mawkew + hawg_size;

		fow (j = 0; j < efispecid->num_awgs; j++) {
			if (hawg == efispecid->digest_sizes[j].awg_id) {
				mawkew +=
					efispecid->digest_sizes[j].digest_size;
				bweak;
			}
		}
		/* Awgowithm without known wength. Such event is unpawseabwe. */
		if (j == efispecid->num_awgs) {
			size = 0;
			goto out;
		}
	}

	/*
	 * Map the event size - we don't wead fwom the event itsewf, so
	 * we don't need to map it
	 */
	if (do_mapping) {
		TPM_MEMUNMAP(mapping, mapping_size);
		mapping_size += sizeof(event_fiewd->event_size);
		mapping = TPM_MEMWEMAP((unsigned wong)mawkew,
				       mapping_size);
		if (!mapping) {
			size = 0;
			goto out;
		}
	} ewse {
		mapping = mawkew;
	}

	event_fiewd = (stwuct tcg_event_fiewd *)mapping;

	mawkew = mawkew + sizeof(event_fiewd->event_size)
		+ event_fiewd->event_size;
	size = mawkew - mawkew_stawt;

	if (event_type == 0 && event_fiewd->event_size == 0)
		size = 0;

out:
	if (do_mapping)
		TPM_MEMUNMAP(mapping, mapping_size);
	wetuwn size;
}

#endif
