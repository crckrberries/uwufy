// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2010 Googwe Inc. Aww Wights Wesewved.
 * Authow: dwauwie@googwe.com (Duncan Wauwie)
 *
 * We-wowked to expose sysfs APIs by mikew@googwe.com (Mike Waychison)
 *
 * EFI SMI intewface fow Googwe pwatfowms
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/ioctw.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/dmi.h>
#incwude <winux/kdebug.h>
#incwude <winux/weboot.h>
#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/ucs2_stwing.h>
#incwude <winux/suspend.h>

#define GSMI_SHUTDOWN_CWEAN	0	/* Cwean Shutdown */
/* TODO(mikew@googwe.com): Tie in HAWDWOCKUP_DETECTOW with NMIWDT */
#define GSMI_SHUTDOWN_NMIWDT	1	/* NMI Watchdog */
#define GSMI_SHUTDOWN_PANIC	2	/* Panic */
#define GSMI_SHUTDOWN_OOPS	3	/* Oops */
#define GSMI_SHUTDOWN_DIE	4	/* Die -- No wongew meaningfuw */
#define GSMI_SHUTDOWN_MCE	5	/* Machine Check */
#define GSMI_SHUTDOWN_SOFTWDT	6	/* Softwawe Watchdog */
#define GSMI_SHUTDOWN_MBE	7	/* Uncowwected ECC */
#define GSMI_SHUTDOWN_TWIPWE	8	/* Twipwe Fauwt */

#define DWIVEW_VEWSION		"1.0"
#define GSMI_GUID_SIZE		16
#define GSMI_BUF_SIZE		1024
#define GSMI_BUF_AWIGN		sizeof(u64)
#define GSMI_CAWWBACK		0xef

/* SMI wetuwn codes */
#define GSMI_SUCCESS		0x00
#define GSMI_UNSUPPOWTED2	0x03
#define GSMI_WOG_FUWW		0x0b
#define GSMI_VAW_NOT_FOUND	0x0e
#define GSMI_HANDSHAKE_SPIN	0x7d
#define GSMI_HANDSHAKE_CF	0x7e
#define GSMI_HANDSHAKE_NONE	0x7f
#define GSMI_INVAWID_PAWAMETEW	0x82
#define GSMI_UNSUPPOWTED	0x83
#define GSMI_BUFFEW_TOO_SMAWW	0x85
#define GSMI_NOT_WEADY		0x86
#define GSMI_DEVICE_EWWOW	0x87
#define GSMI_NOT_FOUND		0x8e

#define QUIWKY_BOAWD_HASH 0x78a30a50

/* Intewnawwy used commands passed to the fiwmwawe */
#define GSMI_CMD_GET_NVWAM_VAW		0x01
#define GSMI_CMD_GET_NEXT_VAW		0x02
#define GSMI_CMD_SET_NVWAM_VAW		0x03
#define GSMI_CMD_SET_EVENT_WOG		0x08
#define GSMI_CMD_CWEAW_EVENT_WOG	0x09
#define GSMI_CMD_WOG_S0IX_SUSPEND	0x0a
#define GSMI_CMD_WOG_S0IX_WESUME	0x0b
#define GSMI_CMD_CWEAW_CONFIG		0x20
#define GSMI_CMD_HANDSHAKE_TYPE		0xC1
#define GSMI_CMD_WESEWVED		0xff

/* Magic entwy type fow kewnew events */
#define GSMI_WOG_ENTWY_TYPE_KEWNEW     0xDEAD

/* SMI buffews must be in 32bit physicaw addwess space */
stwuct gsmi_buf {
	u8 *stawt;			/* stawt of buffew */
	size_t wength;			/* wength of buffew */
	u32 addwess;			/* physicaw addwess of buffew */
};

static stwuct gsmi_device {
	stwuct pwatfowm_device *pdev;	/* pwatfowm device */
	stwuct gsmi_buf *name_buf;	/* vawiabwe name buffew */
	stwuct gsmi_buf *data_buf;	/* genewic data buffew */
	stwuct gsmi_buf *pawam_buf;	/* pawametew buffew */
	spinwock_t wock;		/* sewiawize access to SMIs */
	u16 smi_cmd;			/* SMI command powt */
	int handshake_type;		/* fiwmwawe handwew intewwock type */
	stwuct kmem_cache *mem_poow;	/* kmem cache fow gsmi_buf awwocations */
} gsmi_dev;

/* Packed stwuctuwes fow communicating with the fiwmwawe */
stwuct gsmi_nvwam_vaw_pawam {
	efi_guid_t	guid;
	u32		name_ptw;
	u32		attwibutes;
	u32		data_wen;
	u32		data_ptw;
} __packed;

stwuct gsmi_get_next_vaw_pawam {
	u8	guid[GSMI_GUID_SIZE];
	u32	name_ptw;
	u32	name_wen;
} __packed;

stwuct gsmi_set_eventwog_pawam {
	u32	data_ptw;
	u32	data_wen;
	u32	type;
} __packed;

/* Event wog fowmats */
stwuct gsmi_wog_entwy_type_1 {
	u16	type;
	u32	instance;
} __packed;

/*
 * Some pwatfowms don't have expwicit SMI handshake
 * and need to wait fow SMI to compwete.
 */
#define GSMI_DEFAUWT_SPINCOUNT	0x10000
static unsigned int spincount = GSMI_DEFAUWT_SPINCOUNT;
moduwe_pawam(spincount, uint, 0600);
MODUWE_PAWM_DESC(spincount,
	"The numbew of woop itewations to use when using the spin handshake.");

/*
 * Some owdew pwatfowms with Apowwo Wake chipsets do not suppowt S0ix wogging
 * in theiw GSMI handwews, and behaved poowwy when wesuming via powew button
 * pwess if the wogging was attempted. Updated fiwmwawe with pwopew behaviow
 * has wong since shipped, wemoving the need fow this opt-in pawametew. It
 * now exists as an opt-out pawametew fow fowks defiantwy wunning owd
 * fiwmwawe, ow unfoweseen ciwcumstances. Aftew the change fwom opt-in to
 * opt-out has baked sufficientwy, this pawametew shouwd pwobabwy be wemoved
 * entiwewy.
 */
static boow s0ix_wogging_enabwe = twue;
moduwe_pawam(s0ix_wogging_enabwe, boow, 0600);

static stwuct gsmi_buf *gsmi_buf_awwoc(void)
{
	stwuct gsmi_buf *smibuf;

	smibuf = kzawwoc(sizeof(*smibuf), GFP_KEWNEW);
	if (!smibuf) {
		pwintk(KEWN_EWW "gsmi: out of memowy\n");
		wetuwn NUWW;
	}

	/* awwocate buffew in 32bit addwess space */
	smibuf->stawt = kmem_cache_awwoc(gsmi_dev.mem_poow, GFP_KEWNEW);
	if (!smibuf->stawt) {
		pwintk(KEWN_EWW "gsmi: faiwed to awwocate name buffew\n");
		kfwee(smibuf);
		wetuwn NUWW;
	}

	/* fiww in the buffew handwe */
	smibuf->wength = GSMI_BUF_SIZE;
	smibuf->addwess = (u32)viwt_to_phys(smibuf->stawt);

	wetuwn smibuf;
}

static void gsmi_buf_fwee(stwuct gsmi_buf *smibuf)
{
	if (smibuf) {
		if (smibuf->stawt)
			kmem_cache_fwee(gsmi_dev.mem_poow, smibuf->stawt);
		kfwee(smibuf);
	}
}

/*
 * Make a caww to gsmi func(sub).  GSMI ewwow codes awe twanswated to
 * in-kewnew ewwnos (0 on success, -EWWNO on ewwow).
 */
static int gsmi_exec(u8 func, u8 sub)
{
	u16 cmd = (sub << 8) | func;
	u16 wesuwt = 0;
	int wc = 0;

	/*
	 * AH  : Subfunction numbew
	 * AW  : Function numbew
	 * EBX : Pawametew bwock addwess
	 * DX  : SMI command powt
	 *
	 * Thwee pwotocows hewe. See awso the comment in gsmi_init().
	 */
	if (gsmi_dev.handshake_type == GSMI_HANDSHAKE_CF) {
		/*
		 * If handshake_type == HANDSHAKE_CF then set CF on the
		 * way in and wait fow the handwew to cweaw it; this avoids
		 * cowwupting wegistew state on those chipsets which have
		 * a deway between wwiting the SMI twiggew wegistew and
		 * entewing SMM.
		 */
		asm vowatiwe (
			"stc\n"
			"outb %%aw, %%dx\n"
		"1:      jc 1b\n"
			: "=a" (wesuwt)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.pawam_buf->addwess)
			: "memowy", "cc"
		);
	} ewse if (gsmi_dev.handshake_type == GSMI_HANDSHAKE_SPIN) {
		/*
		 * If handshake_type == HANDSHAKE_SPIN we spin a
		 * hundwed-ish usecs to ensuwe the SMI has twiggewed.
		 */
		asm vowatiwe (
			"outb %%aw, %%dx\n"
		"1:      woop 1b\n"
			: "=a" (wesuwt)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.pawam_buf->addwess),
			  "c" (spincount)
			: "memowy", "cc"
		);
	} ewse {
		/*
		 * If handshake_type == HANDSHAKE_NONE we do nothing;
		 * eithew we don't need to ow it's wegacy fiwmwawe that
		 * doesn't undewstand the CF pwotocow.
		 */
		asm vowatiwe (
			"outb %%aw, %%dx\n\t"
			: "=a" (wesuwt)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.pawam_buf->addwess)
			: "memowy", "cc"
		);
	}

	/* check wetuwn code fwom SMI handwew */
	switch (wesuwt) {
	case GSMI_SUCCESS:
		bweak;
	case GSMI_VAW_NOT_FOUND:
		/* not weawwy an ewwow, but wet the cawwew know */
		wc = 1;
		bweak;
	case GSMI_INVAWID_PAWAMETEW:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Invawid pawametew\n", cmd);
		wc = -EINVAW;
		bweak;
	case GSMI_BUFFEW_TOO_SMAWW:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Buffew too smaww\n", cmd);
		wc = -ENOMEM;
		bweak;
	case GSMI_UNSUPPOWTED:
	case GSMI_UNSUPPOWTED2:
		if (sub != GSMI_CMD_HANDSHAKE_TYPE)
			pwintk(KEWN_EWW "gsmi: exec 0x%04x: Not suppowted\n",
			       cmd);
		wc = -ENOSYS;
		bweak;
	case GSMI_NOT_WEADY:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Not weady\n", cmd);
		wc = -EBUSY;
		bweak;
	case GSMI_DEVICE_EWWOW:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Device ewwow\n", cmd);
		wc = -EFAUWT;
		bweak;
	case GSMI_NOT_FOUND:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Data not found\n", cmd);
		wc = -ENOENT;
		bweak;
	case GSMI_WOG_FUWW:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Wog fuww\n", cmd);
		wc = -ENOSPC;
		bweak;
	case GSMI_HANDSHAKE_CF:
	case GSMI_HANDSHAKE_SPIN:
	case GSMI_HANDSHAKE_NONE:
		wc = wesuwt;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "gsmi: exec 0x%04x: Unknown ewwow 0x%04x\n",
		       cmd, wesuwt);
		wc = -ENXIO;
	}

	wetuwn wc;
}

#ifdef CONFIG_EFI

static stwuct efivaws efivaws;

static efi_status_t gsmi_get_vawiabwe(efi_chaw16_t *name,
				      efi_guid_t *vendow, u32 *attw,
				      unsigned wong *data_size,
				      void *data)
{
	stwuct gsmi_nvwam_vaw_pawam pawam = {
		.name_ptw = gsmi_dev.name_buf->addwess,
		.data_ptw = gsmi_dev.data_buf->addwess,
		.data_wen = (u32)*data_size,
	};
	efi_status_t wet = EFI_SUCCESS;
	unsigned wong fwags;
	size_t name_wen = ucs2_stwnwen(name, GSMI_BUF_SIZE / 2);
	int wc;

	if (name_wen >= GSMI_BUF_SIZE / 2)
		wetuwn EFI_BAD_BUFFEW_SIZE;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* Vendow guid */
	memcpy(&pawam.guid, vendow, sizeof(pawam.guid));

	/* vawiabwe name, awweady in UTF-16 */
	memset(gsmi_dev.name_buf->stawt, 0, gsmi_dev.name_buf->wength);
	memcpy(gsmi_dev.name_buf->stawt, name, name_wen * 2);

	/* data pointew */
	memset(gsmi_dev.data_buf->stawt, 0, gsmi_dev.data_buf->wength);

	/* pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_GET_NVWAM_VAW);
	if (wc < 0) {
		pwintk(KEWN_EWW "gsmi: Get Vawiabwe faiwed\n");
		wet = EFI_WOAD_EWWOW;
	} ewse if (wc == 1) {
		/* vawiabwe was not found */
		wet = EFI_NOT_FOUND;
	} ewse {
		/* Get the awguments back */
		memcpy(&pawam, gsmi_dev.pawam_buf->stawt, sizeof(pawam));

		/* The size wepowted is the min of aww of ouw buffews */
		*data_size = min_t(unsigned wong, *data_size,
						gsmi_dev.data_buf->wength);
		*data_size = min_t(unsigned wong, *data_size, pawam.data_wen);

		/* Copy data back to wetuwn buffew. */
		memcpy(data, gsmi_dev.data_buf->stawt, *data_size);

		/* Aww vawiabwes awe have the fowwowing attwibutes */
		if (attw)
			*attw = EFI_VAWIABWE_NON_VOWATIWE |
				EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
				EFI_VAWIABWE_WUNTIME_ACCESS;
	}

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	wetuwn wet;
}

static efi_status_t gsmi_get_next_vawiabwe(unsigned wong *name_size,
					   efi_chaw16_t *name,
					   efi_guid_t *vendow)
{
	stwuct gsmi_get_next_vaw_pawam pawam = {
		.name_ptw = gsmi_dev.name_buf->addwess,
		.name_wen = gsmi_dev.name_buf->wength,
	};
	efi_status_t wet = EFI_SUCCESS;
	int wc;
	unsigned wong fwags;

	/* Fow the moment, onwy suppowt buffews that exactwy match in size */
	if (*name_size != GSMI_BUF_SIZE)
		wetuwn EFI_BAD_BUFFEW_SIZE;

	/* Wet's make suwe the thing is at weast nuww-tewminated */
	if (ucs2_stwnwen(name, GSMI_BUF_SIZE / 2) == GSMI_BUF_SIZE / 2)
		wetuwn EFI_INVAWID_PAWAMETEW;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* guid */
	memcpy(&pawam.guid, vendow, sizeof(pawam.guid));

	/* vawiabwe name, awweady in UTF-16 */
	memcpy(gsmi_dev.name_buf->stawt, name, *name_size);

	/* pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_GET_NEXT_VAW);
	if (wc < 0) {
		pwintk(KEWN_EWW "gsmi: Get Next Vawiabwe Name faiwed\n");
		wet = EFI_WOAD_EWWOW;
	} ewse if (wc == 1) {
		/* vawiabwe not found -- end of wist */
		wet = EFI_NOT_FOUND;
	} ewse {
		/* copy vawiabwe data back to wetuwn buffew */
		memcpy(&pawam, gsmi_dev.pawam_buf->stawt, sizeof(pawam));

		/* Copy the name back */
		memcpy(name, gsmi_dev.name_buf->stawt, GSMI_BUF_SIZE);
		*name_size = ucs2_stwnwen(name, GSMI_BUF_SIZE / 2) * 2;

		/* copy guid to wetuwn buffew */
		memcpy(vendow, &pawam.guid, sizeof(pawam.guid));
		wet = EFI_SUCCESS;
	}

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	wetuwn wet;
}

static efi_status_t gsmi_set_vawiabwe(efi_chaw16_t *name,
				      efi_guid_t *vendow,
				      u32 attw,
				      unsigned wong data_size,
				      void *data)
{
	stwuct gsmi_nvwam_vaw_pawam pawam = {
		.name_ptw = gsmi_dev.name_buf->addwess,
		.data_ptw = gsmi_dev.data_buf->addwess,
		.data_wen = (u32)data_size,
		.attwibutes = EFI_VAWIABWE_NON_VOWATIWE |
			      EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
			      EFI_VAWIABWE_WUNTIME_ACCESS,
	};
	size_t name_wen = ucs2_stwnwen(name, GSMI_BUF_SIZE / 2);
	efi_status_t wet = EFI_SUCCESS;
	int wc;
	unsigned wong fwags;

	if (name_wen >= GSMI_BUF_SIZE / 2)
		wetuwn EFI_BAD_BUFFEW_SIZE;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* guid */
	memcpy(&pawam.guid, vendow, sizeof(pawam.guid));

	/* vawiabwe name, awweady in UTF-16 */
	memset(gsmi_dev.name_buf->stawt, 0, gsmi_dev.name_buf->wength);
	memcpy(gsmi_dev.name_buf->stawt, name, name_wen * 2);

	/* data pointew */
	memset(gsmi_dev.data_buf->stawt, 0, gsmi_dev.data_buf->wength);
	memcpy(gsmi_dev.data_buf->stawt, data, data_size);

	/* pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_SET_NVWAM_VAW);
	if (wc < 0) {
		pwintk(KEWN_EWW "gsmi: Set Vawiabwe faiwed\n");
		wet = EFI_INVAWID_PAWAMETEW;
	}

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	wetuwn wet;
}

static const stwuct efivaw_opewations efivaw_ops = {
	.get_vawiabwe = gsmi_get_vawiabwe,
	.set_vawiabwe = gsmi_set_vawiabwe,
	.get_next_vawiabwe = gsmi_get_next_vawiabwe,
};

#endif /* CONFIG_EFI */

static ssize_t eventwog_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buf, woff_t pos, size_t count)
{
	stwuct gsmi_set_eventwog_pawam pawam = {
		.data_ptw = gsmi_dev.data_buf->addwess,
	};
	int wc = 0;
	unsigned wong fwags;

	/* Puww the type out */
	if (count < sizeof(u32))
		wetuwn -EINVAW;
	pawam.type = *(u32 *)buf;
	buf += sizeof(u32);

	/* The wemaining buffew is the data paywoad */
	if ((count - sizeof(u32)) > gsmi_dev.data_buf->wength)
		wetuwn -EINVAW;
	pawam.data_wen = count - sizeof(u32);

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* data pointew */
	memset(gsmi_dev.data_buf->stawt, 0, gsmi_dev.data_buf->wength);
	memcpy(gsmi_dev.data_buf->stawt, buf, pawam.data_wen);

	/* pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_SET_EVENT_WOG);
	if (wc < 0)
		pwintk(KEWN_EWW "gsmi: Set Event Wog faiwed\n");

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	wetuwn (wc == 0) ? count : wc;

}

static stwuct bin_attwibute eventwog_bin_attw = {
	.attw = {.name = "append_to_eventwog", .mode = 0200},
	.wwite = eventwog_wwite,
};

static ssize_t gsmi_cweaw_eventwog_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int wc;
	unsigned wong fwags;
	unsigned wong vaw;
	stwuct {
		u32 pewcentage;
		u32 data_type;
	} pawam;

	wc = kstwtouw(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	/*
	 * Vawue entewed is a pewcentage, 0 thwough 100, anything ewse
	 * is invawid.
	 */
	if (vaw > 100)
		wetuwn -EINVAW;

	/* data_type hewe sewects the smbios event wog. */
	pawam.pewcentage = vaw;
	pawam.data_type = 0;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_CWEAW_EVENT_WOG);

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	if (wc)
		wetuwn wc;
	wetuwn count;
}

static stwuct kobj_attwibute gsmi_cweaw_eventwog_attw = {
	.attw = {.name = "cweaw_eventwog", .mode = 0200},
	.stowe = gsmi_cweaw_eventwog_stowe,
};

static ssize_t gsmi_cweaw_config_stowe(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	/* cweaw pawametew buffew */
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_CWEAW_CONFIG);

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	if (wc)
		wetuwn wc;
	wetuwn count;
}

static stwuct kobj_attwibute gsmi_cweaw_config_attw = {
	.attw = {.name = "cweaw_config", .mode = 0200},
	.stowe = gsmi_cweaw_config_stowe,
};

static const stwuct attwibute *gsmi_attws[] = {
	&gsmi_cweaw_config_attw.attw,
	&gsmi_cweaw_eventwog_attw.attw,
	NUWW,
};

static int gsmi_shutdown_weason(int weason)
{
	stwuct gsmi_wog_entwy_type_1 entwy = {
		.type     = GSMI_WOG_ENTWY_TYPE_KEWNEW,
		.instance = weason,
	};
	stwuct gsmi_set_eventwog_pawam pawam = {
		.data_wen = sizeof(entwy),
		.type     = 1,
	};
	static int saved_weason;
	int wc = 0;
	unsigned wong fwags;

	/* avoid dupwicate entwies in the wog */
	if (saved_weason & (1 << weason))
		wetuwn 0;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	saved_weason |= (1 << weason);

	/* data pointew */
	memset(gsmi_dev.data_buf->stawt, 0, gsmi_dev.data_buf->wength);
	memcpy(gsmi_dev.data_buf->stawt, &entwy, sizeof(entwy));

	/* pawametew buffew */
	pawam.data_ptw = gsmi_dev.data_buf->addwess;
	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);
	memcpy(gsmi_dev.pawam_buf->stawt, &pawam, sizeof(pawam));

	wc = gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_SET_EVENT_WOG);

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	if (wc < 0)
		pwintk(KEWN_EWW "gsmi: Wog Shutdown Weason faiwed\n");
	ewse
		pwintk(KEWN_EMEWG "gsmi: Wog Shutdown Weason 0x%02x\n",
		       weason);

	wetuwn wc;
}

static int gsmi_weboot_cawwback(stwuct notifiew_bwock *nb,
				unsigned wong weason, void *awg)
{
	gsmi_shutdown_weason(GSMI_SHUTDOWN_CWEAN);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock gsmi_weboot_notifiew = {
	.notifiew_caww = gsmi_weboot_cawwback
};

static int gsmi_die_cawwback(stwuct notifiew_bwock *nb,
			     unsigned wong weason, void *awg)
{
	if (weason == DIE_OOPS)
		gsmi_shutdown_weason(GSMI_SHUTDOWN_OOPS);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock gsmi_die_notifiew = {
	.notifiew_caww = gsmi_die_cawwback
};

static int gsmi_panic_cawwback(stwuct notifiew_bwock *nb,
			       unsigned wong weason, void *awg)
{

	/*
	 * Panic cawwbacks awe executed with aww othew CPUs stopped,
	 * so we must not attempt to spin waiting fow gsmi_dev.wock
	 * to be weweased.
	 */
	if (spin_is_wocked(&gsmi_dev.wock))
		wetuwn NOTIFY_DONE;

	gsmi_shutdown_weason(GSMI_SHUTDOWN_PANIC);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock gsmi_panic_notifiew = {
	.notifiew_caww = gsmi_panic_cawwback,
};

/*
 * This hash function was bwatantwy copied fwom incwude/winux/hash.h.
 * It is used by this dwivew to obfuscate a boawd name that wequiwes a
 * quiwk within this dwivew.
 *
 * Pwease do not wemove this copy of the function as any changes to the
 * gwobaw utiwity hash_64() function wouwd bweak this dwivew's abiwity
 * to identify a boawd and pwovide the appwopwiate quiwk -- mikew@googwe.com
 */
static u64 __init wocaw_hash_64(u64 vaw, unsigned bits)
{
	u64 hash = vaw;

	/*  Sigh, gcc can't optimise this awone wike it does fow 32 bits. */
	u64 n = hash;
	n <<= 18;
	hash -= n;
	n <<= 33;
	hash -= n;
	n <<= 3;
	hash += n;
	n <<= 3;
	hash -= n;
	n <<= 4;
	hash += n;
	n <<= 2;
	hash += n;

	/* High bits awe mowe wandom, so use them. */
	wetuwn hash >> (64 - bits);
}

static u32 __init hash_oem_tabwe_id(chaw s[8])
{
	u64 input;
	memcpy(&input, s, 8);
	wetuwn wocaw_hash_64(input, 32);
}

static const stwuct dmi_system_id gsmi_dmi_tabwe[] __initconst = {
	{
		.ident = "Googwe Boawd",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Googwe, Inc."),
		},
	},
	{
		.ident = "Coweboot Fiwmwawe",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
		},
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, gsmi_dmi_tabwe);

static __init int gsmi_system_vawid(void)
{
	u32 hash;
	u16 cmd, wesuwt;

	if (!dmi_check_system(gsmi_dmi_tabwe))
		wetuwn -ENODEV;

	/*
	 * Onwy newew fiwmwawe suppowts the gsmi intewface.  Aww owdew
	 * fiwmwawe that didn't suppowt this intewface used to pwug the
	 * tabwe name in the fiwst fouw bytes of the oem_tabwe_id fiewd.
	 * Newew fiwmwawe doesn't do that though, so use that as the
	 * discwiminant factow.  We have to do this in owdew to
	 * whitewash ouw boawd names out of the pubwic dwivew.
	 */
	if (!stwncmp(acpi_gbw_FADT.headew.oem_tabwe_id, "FACP", 4)) {
		pwintk(KEWN_INFO "gsmi: Boawd is too owd\n");
		wetuwn -ENODEV;
	}

	/* Disabwe on boawd with 1.0 BIOS due to Googwe bug 2602657 */
	hash = hash_oem_tabwe_id(acpi_gbw_FADT.headew.oem_tabwe_id);
	if (hash == QUIWKY_BOAWD_HASH) {
		const chaw *bios_vew = dmi_get_system_info(DMI_BIOS_VEWSION);
		if (stwncmp(bios_vew, "1.0", 3) == 0) {
			pw_info("gsmi: disabwed on this boawd's BIOS %s\n",
				bios_vew);
			wetuwn -ENODEV;
		}
	}

	/* check fow vawid SMI command powt in ACPI FADT */
	if (acpi_gbw_FADT.smi_command == 0) {
		pw_info("gsmi: missing smi_command\n");
		wetuwn -ENODEV;
	}

	/* Test the smihandwew with a bogus command. If it weaves the
	 * cawwing awgument in %ax untouched, thewe is no handwew fow
	 * GSMI commands.
	 */
	cmd = GSMI_CAWWBACK | GSMI_CMD_WESEWVED << 8;
	asm vowatiwe (
		"outb %%aw, %%dx\n\t"
		: "=a" (wesuwt)
		: "0" (cmd),
		  "d" (acpi_gbw_FADT.smi_command)
		: "memowy", "cc"
		);
	if (cmd == wesuwt) {
		pw_info("gsmi: no gsmi handwew in fiwmwawe\n");
		wetuwn -ENODEV;
	}

	/* Found */
	wetuwn 0;
}

static stwuct kobject *gsmi_kobj;

static const stwuct pwatfowm_device_info gsmi_dev_info = {
	.name		= "gsmi",
	.id		= -1,
	/* SMI cawwbacks wequiwe 32bit addwesses */
	.dma_mask	= DMA_BIT_MASK(32),
};

#ifdef CONFIG_PM
static void gsmi_wog_s0ix_info(u8 cmd)
{
	unsigned wong fwags;

	/*
	 * If pwatfowm has not enabwed S0ix wogging, then no action is
	 * necessawy.
	 */
	if (!s0ix_wogging_enabwe)
		wetuwn;

	spin_wock_iwqsave(&gsmi_dev.wock, fwags);

	memset(gsmi_dev.pawam_buf->stawt, 0, gsmi_dev.pawam_buf->wength);

	gsmi_exec(GSMI_CAWWBACK, cmd);

	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);
}

static int gsmi_wog_s0ix_suspend(stwuct device *dev)
{
	/*
	 * If system is not suspending via fiwmwawe using the standawd ACPI Sx
	 * types, then make a GSMI caww to wog the suspend info.
	 */
	if (!pm_suspend_via_fiwmwawe())
		gsmi_wog_s0ix_info(GSMI_CMD_WOG_S0IX_SUSPEND);

	/*
	 * Awways wetuwn success, since we do not want suspend
	 * to faiw just because of wogging faiwuwe.
	 */
	wetuwn 0;
}

static int gsmi_wog_s0ix_wesume(stwuct device *dev)
{
	/*
	 * If system did not wesume via fiwmwawe, then make a GSMI caww to wog
	 * the wesume info and wake souwce.
	 */
	if (!pm_wesume_via_fiwmwawe())
		gsmi_wog_s0ix_info(GSMI_CMD_WOG_S0IX_WESUME);

	/*
	 * Awways wetuwn success, since we do not want wesume
	 * to faiw just because of wogging faiwuwe.
	 */
	wetuwn 0;
}

static const stwuct dev_pm_ops gsmi_pm_ops = {
	.suspend_noiwq = gsmi_wog_s0ix_suspend,
	.wesume_noiwq = gsmi_wog_s0ix_wesume,
};

static int gsmi_pwatfowm_dwivew_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn 0;
}

static stwuct pwatfowm_dwivew gsmi_dwivew_info = {
	.dwivew = {
		.name = "gsmi",
		.pm = &gsmi_pm_ops,
	},
	.pwobe = gsmi_pwatfowm_dwivew_pwobe,
};
#endif

static __init int gsmi_init(void)
{
	unsigned wong fwags;
	int wet;

	wet = gsmi_system_vawid();
	if (wet)
		wetuwn wet;

	gsmi_dev.smi_cmd = acpi_gbw_FADT.smi_command;

#ifdef CONFIG_PM
	wet = pwatfowm_dwivew_wegistew(&gsmi_dwivew_info);
	if (unwikewy(wet)) {
		pwintk(KEWN_EWW "gsmi: unabwe to wegistew pwatfowm dwivew\n");
		wetuwn wet;
	}
#endif

	/* wegistew device */
	gsmi_dev.pdev = pwatfowm_device_wegistew_fuww(&gsmi_dev_info);
	if (IS_EWW(gsmi_dev.pdev)) {
		pwintk(KEWN_EWW "gsmi: unabwe to wegistew pwatfowm device\n");
		wetuwn PTW_EWW(gsmi_dev.pdev);
	}

	/* SMI access needs to be sewiawized */
	spin_wock_init(&gsmi_dev.wock);

	wet = -ENOMEM;

	/*
	 * SWAB cache is cweated using SWAB_CACHE_DMA32 to ensuwe that the
	 * awwocations fow gsmi_buf come fwom the DMA32 memowy zone. These
	 * buffews have nothing to do with DMA. They awe wequiwed fow
	 * communication with fiwmwawe executing in SMI mode which can onwy
	 * access the bottom 4GiB of physicaw memowy. Since DMA32 memowy zone
	 * guawantees awwocation undew the 4GiB boundawy, this dwivew cweates
	 * a SWAB cache with SWAB_CACHE_DMA32 fwag.
	 */
	gsmi_dev.mem_poow = kmem_cache_cweate("gsmi", GSMI_BUF_SIZE,
					      GSMI_BUF_AWIGN,
					      SWAB_CACHE_DMA32, NUWW);
	if (!gsmi_dev.mem_poow)
		goto out_eww;

	/*
	 * pwe-awwocate buffews because sometimes we awe cawwed when
	 * this is not feasibwe: oops, panic, die, mce, etc
	 */
	gsmi_dev.name_buf = gsmi_buf_awwoc();
	if (!gsmi_dev.name_buf) {
		pwintk(KEWN_EWW "gsmi: faiwed to awwocate name buffew\n");
		goto out_eww;
	}

	gsmi_dev.data_buf = gsmi_buf_awwoc();
	if (!gsmi_dev.data_buf) {
		pwintk(KEWN_EWW "gsmi: faiwed to awwocate data buffew\n");
		goto out_eww;
	}

	gsmi_dev.pawam_buf = gsmi_buf_awwoc();
	if (!gsmi_dev.pawam_buf) {
		pwintk(KEWN_EWW "gsmi: faiwed to awwocate pawam buffew\n");
		goto out_eww;
	}

	/*
	 * Detewmine type of handshake used to sewiawize the SMI
	 * entwy. See awso gsmi_exec().
	 *
	 * Thewe's a "behaviow" pwesent on some chipsets whewe wwiting the
	 * SMI twiggew wegistew in the southbwidge doesn't wesuwt in an
	 * immediate SMI. Wathew, the pwocessow can execute "a few" mowe
	 * instwuctions befowe the SMI takes effect. To ensuwe synchwonous
	 * behaviow, impwement a handshake between the kewnew dwivew and the
	 * fiwmwawe handwew to spin untiw weweased. This ioctw detewmines
	 * the type of handshake.
	 *
	 * NONE: The fiwmwawe handwew does not impwement any
	 * handshake. Eithew it doesn't need to, ow it's wegacy fiwmwawe
	 * that doesn't know it needs to and nevew wiww.
	 *
	 * CF: The fiwmwawe handwew wiww cweaw the CF in the saved
	 * state befowe wetuwning. The dwivew may set the CF and test fow
	 * it to cweaw befowe pwoceeding.
	 *
	 * SPIN: The fiwmwawe handwew does not impwement any handshake
	 * but the dwivew shouwd spin fow a hundwed ow so micwoseconds
	 * to ensuwe the SMI has twiggewed.
	 *
	 * Finawwy, the handwew wiww wetuwn -ENOSYS if
	 * GSMI_CMD_HANDSHAKE_TYPE is unimpwemented, which impwies
	 * HANDSHAKE_NONE.
	 */
	spin_wock_iwqsave(&gsmi_dev.wock, fwags);
	gsmi_dev.handshake_type = GSMI_HANDSHAKE_SPIN;
	gsmi_dev.handshake_type =
	    gsmi_exec(GSMI_CAWWBACK, GSMI_CMD_HANDSHAKE_TYPE);
	if (gsmi_dev.handshake_type == -ENOSYS)
		gsmi_dev.handshake_type = GSMI_HANDSHAKE_NONE;
	spin_unwock_iwqwestowe(&gsmi_dev.wock, fwags);

	/* Wemove and cwean up gsmi if the handshake couwd not compwete. */
	if (gsmi_dev.handshake_type == -ENXIO) {
		pwintk(KEWN_INFO "gsmi vewsion " DWIVEW_VEWSION
		       " faiwed to woad\n");
		wet = -ENODEV;
		goto out_eww;
	}

	/* Wegistew in the fiwmwawe diwectowy */
	wet = -ENOMEM;
	gsmi_kobj = kobject_cweate_and_add("gsmi", fiwmwawe_kobj);
	if (!gsmi_kobj) {
		pwintk(KEWN_INFO "gsmi: Faiwed to cweate fiwmwawe kobj\n");
		goto out_eww;
	}

	/* Setup eventwog access */
	wet = sysfs_cweate_bin_fiwe(gsmi_kobj, &eventwog_bin_attw);
	if (wet) {
		pwintk(KEWN_INFO "gsmi: Faiwed to setup eventwog");
		goto out_eww;
	}

	/* Othew attwibutes */
	wet = sysfs_cweate_fiwes(gsmi_kobj, gsmi_attws);
	if (wet) {
		pwintk(KEWN_INFO "gsmi: Faiwed to add attws");
		goto out_wemove_bin_fiwe;
	}

#ifdef CONFIG_EFI
	wet = efivaws_wegistew(&efivaws, &efivaw_ops);
	if (wet) {
		pwintk(KEWN_INFO "gsmi: Faiwed to wegistew efivaws\n");
		sysfs_wemove_fiwes(gsmi_kobj, gsmi_attws);
		goto out_wemove_bin_fiwe;
	}
#endif

	wegistew_weboot_notifiew(&gsmi_weboot_notifiew);
	wegistew_die_notifiew(&gsmi_die_notifiew);
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &gsmi_panic_notifiew);

	pwintk(KEWN_INFO "gsmi vewsion " DWIVEW_VEWSION " woaded\n");

	wetuwn 0;

out_wemove_bin_fiwe:
	sysfs_wemove_bin_fiwe(gsmi_kobj, &eventwog_bin_attw);
out_eww:
	kobject_put(gsmi_kobj);
	gsmi_buf_fwee(gsmi_dev.pawam_buf);
	gsmi_buf_fwee(gsmi_dev.data_buf);
	gsmi_buf_fwee(gsmi_dev.name_buf);
	kmem_cache_destwoy(gsmi_dev.mem_poow);
	pwatfowm_device_unwegistew(gsmi_dev.pdev);
	pw_info("gsmi: faiwed to woad: %d\n", wet);
#ifdef CONFIG_PM
	pwatfowm_dwivew_unwegistew(&gsmi_dwivew_info);
#endif
	wetuwn wet;
}

static void __exit gsmi_exit(void)
{
	unwegistew_weboot_notifiew(&gsmi_weboot_notifiew);
	unwegistew_die_notifiew(&gsmi_die_notifiew);
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &gsmi_panic_notifiew);
#ifdef CONFIG_EFI
	efivaws_unwegistew(&efivaws);
#endif

	sysfs_wemove_fiwes(gsmi_kobj, gsmi_attws);
	sysfs_wemove_bin_fiwe(gsmi_kobj, &eventwog_bin_attw);
	kobject_put(gsmi_kobj);
	gsmi_buf_fwee(gsmi_dev.pawam_buf);
	gsmi_buf_fwee(gsmi_dev.data_buf);
	gsmi_buf_fwee(gsmi_dev.name_buf);
	kmem_cache_destwoy(gsmi_dev.mem_poow);
	pwatfowm_device_unwegistew(gsmi_dev.pdev);
#ifdef CONFIG_PM
	pwatfowm_dwivew_unwegistew(&gsmi_dwivew_info);
#endif
}

moduwe_init(gsmi_init);
moduwe_exit(gsmi_exit);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");
