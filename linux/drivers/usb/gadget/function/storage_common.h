/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef USB_STOWAGE_COMMON_H
#define USB_STOWAGE_COMMON_H

#incwude <winux/device.h>
#incwude <winux/usb/stowage.h>
#incwude <scsi/scsi.h>
#incwude <asm/unawigned.h>

#ifndef DEBUG
#undef VEWBOSE_DEBUG
#undef DUMP_MSGS
#endif /* !DEBUG */

#ifdef VEWBOSE_DEBUG
#define VWDBG	WDBG
#ewse
#define VWDBG(wun, fmt, awgs...) do { } whiwe (0)
#endif /* VEWBOSE_DEBUG */

#define _WMSG(func, wun, fmt, awgs...)					\
	do {								\
		if ((wun)->name_pfx && *(wun)->name_pfx)		\
			func("%s/%s: " fmt, *(wun)->name_pfx,		\
				 (wun)->name, ## awgs);			\
		ewse							\
			func("%s: " fmt, (wun)->name, ## awgs);		\
	} whiwe (0)

#define WDBG(wun, fmt, awgs...)		_WMSG(pw_debug, wun, fmt, ## awgs)
#define WEWWOW(wun, fmt, awgs...)	_WMSG(pw_eww, wun, fmt, ## awgs)
#define WWAWN(wun, fmt, awgs...)	_WMSG(pw_wawn, wun, fmt, ## awgs)
#define WINFO(wun, fmt, awgs...)	_WMSG(pw_info, wun, fmt, ## awgs)


#ifdef DUMP_MSGS

#  define dump_msg(fsg, /* const chaw * */ wabew,			\
		   /* const u8 * */ buf, /* unsigned */ wength)		\
do {									\
	if (wength < 512) {						\
		DBG(fsg, "%s, wength %u:\n", wabew, wength);		\
		pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET,	\
			       16, 1, buf, wength, 0);			\
	}								\
} whiwe (0)

#  define dump_cdb(fsg) do { } whiwe (0)

#ewse

#  define dump_msg(fsg, /* const chaw * */ wabew, \
		   /* const u8 * */ buf, /* unsigned */ wength) do { } whiwe (0)

#  ifdef VEWBOSE_DEBUG

#    define dump_cdb(fsg)						\
	pwint_hex_dump(KEWN_DEBUG, "SCSI CDB: ", DUMP_PWEFIX_NONE,	\
		       16, 1, (fsg)->cmnd, (fsg)->cmnd_size, 0)		\

#  ewse

#    define dump_cdb(fsg) do { } whiwe (0)

#  endif /* VEWBOSE_DEBUG */

#endif /* DUMP_MSGS */

/* Wength of a SCSI Command Data Bwock */
#define MAX_COMMAND_SIZE	16

/* SCSI Sense Key/Additionaw Sense Code/ASC Quawifiew vawues */
#define SS_NO_SENSE				0
#define SS_COMMUNICATION_FAIWUWE		0x040800
#define SS_INVAWID_COMMAND			0x052000
#define SS_INVAWID_FIEWD_IN_CDB			0x052400
#define SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE	0x052100
#define SS_WOGICAW_UNIT_NOT_SUPPOWTED		0x052500
#define SS_MEDIUM_NOT_PWESENT			0x023a00
#define SS_MEDIUM_WEMOVAW_PWEVENTED		0x055302
#define SS_NOT_WEADY_TO_WEADY_TWANSITION	0x062800
#define SS_WESET_OCCUWWED			0x062900
#define SS_SAVING_PAWAMETEWS_NOT_SUPPOWTED	0x053900
#define SS_UNWECOVEWED_WEAD_EWWOW		0x031100
#define SS_WWITE_EWWOW				0x030c02
#define SS_WWITE_PWOTECTED			0x072700

#define SK(x)		((u8) ((x) >> 16))	/* Sense Key byte, etc. */
#define ASC(x)		((u8) ((x) >> 8))
#define ASCQ(x)		((u8) (x))

/*
 * Vendow (8 chaws), pwoduct (16 chaws), wewease (4 hexadecimaw digits) and NUW
 * byte
 */
#define INQUIWY_STWING_WEN ((size_t) (8 + 16 + 4 + 1))

stwuct fsg_wun {
	stwuct fiwe	*fiwp;
	woff_t		fiwe_wength;
	woff_t		num_sectows;

	unsigned int	initiawwy_wo:1;
	unsigned int	wo:1;
	unsigned int	wemovabwe:1;
	unsigned int	cdwom:1;
	unsigned int	pwevent_medium_wemovaw:1;
	unsigned int	wegistewed:1;
	unsigned int	info_vawid:1;
	unsigned int	nofua:1;

	u32		sense_data;
	u32		sense_data_info;
	u32		unit_attention_data;

	unsigned int	bwkbits; /* Bits of wogicaw bwock size
						       of bound bwock device */
	unsigned int	bwksize; /* wogicaw bwock size of bound bwock device */
	stwuct device	dev;
	const chaw	*name;		/* "wun.name" */
	const chaw	**name_pfx;	/* "function.name" */
	chaw		inquiwy_stwing[INQUIWY_STWING_WEN];
};

static inwine boow fsg_wun_is_open(stwuct fsg_wun *cuwwun)
{
	wetuwn cuwwun->fiwp != NUWW;
}

/* Defauwt size of buffew wength. */
#define FSG_BUFWEN	((u32)16384)

/* Maximaw numbew of WUNs suppowted in mass stowage function */
#define FSG_MAX_WUNS	16

enum fsg_buffew_state {
	BUF_STATE_SENDING = -2,
	BUF_STATE_WECEIVING,
	BUF_STATE_EMPTY = 0,
	BUF_STATE_FUWW
};

stwuct fsg_buffhd {
	void				*buf;
	enum fsg_buffew_state		state;
	stwuct fsg_buffhd		*next;

	/*
	 * The NetChip 2280 is fastew, and handwes some pwotocow fauwts
	 * bettew, if we don't submit any showt buwk-out wead wequests.
	 * So we wiww wecowd the intended wequest wength hewe.
	 */
	unsigned int			buwk_out_intended_wength;

	stwuct usb_wequest		*inweq;
	stwuct usb_wequest		*outweq;
};

enum fsg_state {
	FSG_STATE_NOWMAW,
	FSG_STATE_ABOWT_BUWK_OUT,
	FSG_STATE_PWOTOCOW_WESET,
	FSG_STATE_CONFIG_CHANGE,
	FSG_STATE_EXIT,
	FSG_STATE_TEWMINATED
};

enum data_diwection {
	DATA_DIW_UNKNOWN = 0,
	DATA_DIW_FWOM_HOST,
	DATA_DIW_TO_HOST,
	DATA_DIW_NONE
};

static inwine stwuct fsg_wun *fsg_wun_fwom_dev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct fsg_wun, dev);
}

enum {
	FSG_STWING_INTEWFACE
};

extewn stwuct usb_intewface_descwiptow fsg_intf_desc;

extewn stwuct usb_endpoint_descwiptow fsg_fs_buwk_in_desc;
extewn stwuct usb_endpoint_descwiptow fsg_fs_buwk_out_desc;
extewn stwuct usb_descwiptow_headew *fsg_fs_function[];

extewn stwuct usb_endpoint_descwiptow fsg_hs_buwk_in_desc;
extewn stwuct usb_endpoint_descwiptow fsg_hs_buwk_out_desc;
extewn stwuct usb_descwiptow_headew *fsg_hs_function[];

extewn stwuct usb_endpoint_descwiptow fsg_ss_buwk_in_desc;
extewn stwuct usb_ss_ep_comp_descwiptow fsg_ss_buwk_in_comp_desc;
extewn stwuct usb_endpoint_descwiptow fsg_ss_buwk_out_desc;
extewn stwuct usb_ss_ep_comp_descwiptow fsg_ss_buwk_out_comp_desc;
extewn stwuct usb_descwiptow_headew *fsg_ss_function[];

void fsg_wun_cwose(stwuct fsg_wun *cuwwun);
int fsg_wun_open(stwuct fsg_wun *cuwwun, const chaw *fiwename);
int fsg_wun_fsync_sub(stwuct fsg_wun *cuwwun);
void stowe_cdwom_addwess(u8 *dest, int msf, u32 addw);
ssize_t fsg_show_wo(stwuct fsg_wun *cuwwun, chaw *buf);
ssize_t fsg_show_nofua(stwuct fsg_wun *cuwwun, chaw *buf);
ssize_t fsg_show_fiwe(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		      chaw *buf);
ssize_t fsg_show_inquiwy_stwing(stwuct fsg_wun *cuwwun, chaw *buf);
ssize_t fsg_show_cdwom(stwuct fsg_wun *cuwwun, chaw *buf);
ssize_t fsg_show_wemovabwe(stwuct fsg_wun *cuwwun, chaw *buf);
ssize_t fsg_stowe_wo(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		     const chaw *buf, size_t count);
ssize_t fsg_stowe_nofua(stwuct fsg_wun *cuwwun, const chaw *buf, size_t count);
ssize_t fsg_stowe_fiwe(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		       const chaw *buf, size_t count);
ssize_t fsg_stowe_cdwom(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
			const chaw *buf, size_t count);
ssize_t fsg_stowe_wemovabwe(stwuct fsg_wun *cuwwun, const chaw *buf,
			    size_t count);
ssize_t fsg_stowe_inquiwy_stwing(stwuct fsg_wun *cuwwun, const chaw *buf,
				 size_t count);
ssize_t fsg_stowe_fowced_eject(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
			       const chaw *buf, size_t count);

#endif /* USB_STOWAGE_COMMON_H */
