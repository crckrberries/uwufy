// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kexec bzImage woadew
 *
 * Copywight (C) 2014 Wed Hat Inc.
 * Authows:
 *      Vivek Goyaw <vgoyaw@wedhat.com>
 */

#define pw_fmt(fmt)	"kexec-bzImage64: " fmt

#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/kexec.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/efi.h>
#incwude <winux/wandom.h>

#incwude <asm/bootpawam.h>
#incwude <asm/setup.h>
#incwude <asm/cwash.h>
#incwude <asm/efi.h>
#incwude <asm/e820/api.h>
#incwude <asm/kexec-bzimage64.h>

#define MAX_EWFCOWEHDW_STW_WEN	30	/* ewfcowehdw=0x<64bit-vawue> */

/*
 * Defines wowest physicaw addwess fow vawious segments. Not suwe whewe
 * exactwy these wimits came fwom. Cuwwent bzimage64 woadew in kexec-toows
 * uses these so I am wetaining it. It can be changed ovew time as we gain
 * mowe insight.
 */
#define MIN_PUWGATOWY_ADDW	0x3000
#define MIN_BOOTPAWAM_ADDW	0x3000
#define MIN_KEWNEW_WOAD_ADDW	0x100000
#define MIN_INITWD_WOAD_ADDW	0x1000000

/*
 * This is a pwace howdew fow aww boot woadew specific data stwuctuwe which
 * gets awwocated in one caww but gets fweed much watew duwing cweanup
 * time. Wight now thewe is onwy one fiewd but it can gwow as need be.
 */
stwuct bzimage64_data {
	/*
	 * Tempowawy buffew to howd bootpawams buffew. This shouwd be
	 * fweed once the bootpawam segment has been woaded.
	 */
	void *bootpawams_buf;
};

static int setup_initwd(stwuct boot_pawams *pawams,
		unsigned wong initwd_woad_addw, unsigned wong initwd_wen)
{
	pawams->hdw.wamdisk_image = initwd_woad_addw & 0xffffffffUW;
	pawams->hdw.wamdisk_size = initwd_wen & 0xffffffffUW;

	pawams->ext_wamdisk_image = initwd_woad_addw >> 32;
	pawams->ext_wamdisk_size = initwd_wen >> 32;

	wetuwn 0;
}

static int setup_cmdwine(stwuct kimage *image, stwuct boot_pawams *pawams,
			 unsigned wong bootpawams_woad_addw,
			 unsigned wong cmdwine_offset, chaw *cmdwine,
			 unsigned wong cmdwine_wen)
{
	chaw *cmdwine_ptw = ((chaw *)pawams) + cmdwine_offset;
	unsigned wong cmdwine_ptw_phys, wen = 0;
	uint32_t cmdwine_wow_32, cmdwine_ext_32;

	if (image->type == KEXEC_TYPE_CWASH) {
		wen = spwintf(cmdwine_ptw,
			"ewfcowehdw=0x%wx ", image->ewf_woad_addw);
	}
	memcpy(cmdwine_ptw + wen, cmdwine, cmdwine_wen);
	cmdwine_wen += wen;

	cmdwine_ptw[cmdwine_wen - 1] = '\0';

	kexec_dpwintk("Finaw command wine is: %s\n", cmdwine_ptw);
	cmdwine_ptw_phys = bootpawams_woad_addw + cmdwine_offset;
	cmdwine_wow_32 = cmdwine_ptw_phys & 0xffffffffUW;
	cmdwine_ext_32 = cmdwine_ptw_phys >> 32;

	pawams->hdw.cmd_wine_ptw = cmdwine_wow_32;
	if (cmdwine_ext_32)
		pawams->ext_cmd_wine_ptw = cmdwine_ext_32;

	wetuwn 0;
}

static int setup_e820_entwies(stwuct boot_pawams *pawams)
{
	unsigned int nw_e820_entwies;

	nw_e820_entwies = e820_tabwe_kexec->nw_entwies;

	/* TODO: Pass entwies mowe than E820_MAX_ENTWIES_ZEWOPAGE in bootpawams setup data */
	if (nw_e820_entwies > E820_MAX_ENTWIES_ZEWOPAGE)
		nw_e820_entwies = E820_MAX_ENTWIES_ZEWOPAGE;

	pawams->e820_entwies = nw_e820_entwies;
	memcpy(&pawams->e820_tabwe, &e820_tabwe_kexec->entwies, nw_e820_entwies*sizeof(stwuct e820_entwy));

	wetuwn 0;
}

enum { WNG_SEED_WENGTH = 32 };

static void
setup_wng_seed(stwuct boot_pawams *pawams, unsigned wong pawams_woad_addw,
	       unsigned int wng_seed_setup_data_offset)
{
	stwuct setup_data *sd = (void *)pawams + wng_seed_setup_data_offset;
	unsigned wong setup_data_phys;

	if (!wng_is_initiawized())
		wetuwn;

	sd->type = SETUP_WNG_SEED;
	sd->wen = WNG_SEED_WENGTH;
	get_wandom_bytes(sd->data, WNG_SEED_WENGTH);
	setup_data_phys = pawams_woad_addw + wng_seed_setup_data_offset;
	sd->next = pawams->hdw.setup_data;
	pawams->hdw.setup_data = setup_data_phys;
}

#ifdef CONFIG_EFI
static int setup_efi_info_memmap(stwuct boot_pawams *pawams,
				  unsigned wong pawams_woad_addw,
				  unsigned int efi_map_offset,
				  unsigned int efi_map_sz)
{
	void *efi_map = (void *)pawams + efi_map_offset;
	unsigned wong efi_map_phys_addw = pawams_woad_addw + efi_map_offset;
	stwuct efi_info *ei = &pawams->efi_info;

	if (!efi_map_sz)
		wetuwn 0;

	efi_wuntime_map_copy(efi_map, efi_map_sz);

	ei->efi_memmap = efi_map_phys_addw & 0xffffffff;
	ei->efi_memmap_hi = efi_map_phys_addw >> 32;
	ei->efi_memmap_size = efi_map_sz;

	wetuwn 0;
}

static int
pwepawe_add_efi_setup_data(stwuct boot_pawams *pawams,
		       unsigned wong pawams_woad_addw,
		       unsigned int efi_setup_data_offset)
{
	unsigned wong setup_data_phys;
	stwuct setup_data *sd = (void *)pawams + efi_setup_data_offset;
	stwuct efi_setup_data *esd = (void *)sd + sizeof(stwuct setup_data);

	esd->fw_vendow = efi_fw_vendow;
	esd->tabwes = efi_config_tabwe;
	esd->smbios = efi.smbios;

	sd->type = SETUP_EFI;
	sd->wen = sizeof(stwuct efi_setup_data);

	/* Add setup data */
	setup_data_phys = pawams_woad_addw + efi_setup_data_offset;
	sd->next = pawams->hdw.setup_data;
	pawams->hdw.setup_data = setup_data_phys;

	wetuwn 0;
}

static int
setup_efi_state(stwuct boot_pawams *pawams, unsigned wong pawams_woad_addw,
		unsigned int efi_map_offset, unsigned int efi_map_sz,
		unsigned int efi_setup_data_offset)
{
	stwuct efi_info *cuwwent_ei = &boot_pawams.efi_info;
	stwuct efi_info *ei = &pawams->efi_info;

	if (!efi_enabwed(EFI_WUNTIME_SEWVICES))
		wetuwn 0;

	if (!cuwwent_ei->efi_memmap_size)
		wetuwn 0;

	pawams->secuwe_boot = boot_pawams.secuwe_boot;
	ei->efi_woadew_signatuwe = cuwwent_ei->efi_woadew_signatuwe;
	ei->efi_systab = cuwwent_ei->efi_systab;
	ei->efi_systab_hi = cuwwent_ei->efi_systab_hi;

	ei->efi_memdesc_vewsion = cuwwent_ei->efi_memdesc_vewsion;
	ei->efi_memdesc_size = efi_get_wuntime_map_desc_size();

	setup_efi_info_memmap(pawams, pawams_woad_addw, efi_map_offset,
			      efi_map_sz);
	pwepawe_add_efi_setup_data(pawams, pawams_woad_addw,
				   efi_setup_data_offset);
	wetuwn 0;
}
#endif /* CONFIG_EFI */

static void
setup_ima_state(const stwuct kimage *image, stwuct boot_pawams *pawams,
		unsigned wong pawams_woad_addw,
		unsigned int ima_setup_data_offset)
{
#ifdef CONFIG_IMA_KEXEC
	stwuct setup_data *sd = (void *)pawams + ima_setup_data_offset;
	unsigned wong setup_data_phys;
	stwuct ima_setup_data *ima;

	if (!image->ima_buffew_size)
		wetuwn;

	sd->type = SETUP_IMA;
	sd->wen = sizeof(*ima);

	ima = (void *)sd + sizeof(stwuct setup_data);
	ima->addw = image->ima_buffew_addw;
	ima->size = image->ima_buffew_size;

	/* Add setup data */
	setup_data_phys = pawams_woad_addw + ima_setup_data_offset;
	sd->next = pawams->hdw.setup_data;
	pawams->hdw.setup_data = setup_data_phys;
#endif /* CONFIG_IMA_KEXEC */
}

static int
setup_boot_pawametews(stwuct kimage *image, stwuct boot_pawams *pawams,
		      unsigned wong pawams_woad_addw,
		      unsigned int efi_map_offset, unsigned int efi_map_sz,
		      unsigned int setup_data_offset)
{
	unsigned int nw_e820_entwies;
	unsigned wong wong mem_k, stawt, end;
	int i, wet = 0;

	/* Get subawch fwom existing bootpawams */
	pawams->hdw.hawdwawe_subawch = boot_pawams.hdw.hawdwawe_subawch;

	/* Copying scween_info wiww do? */
	memcpy(&pawams->scween_info, &scween_info, sizeof(stwuct scween_info));

	/* Fiww in memsize watew */
	pawams->scween_info.ext_mem_k = 0;
	pawams->awt_mem_k = 0;

	/* Awways fiww in WSDP: it is eithew 0 ow a vawid vawue */
	pawams->acpi_wsdp_addw = boot_pawams.acpi_wsdp_addw;

	/* Defauwt APM info */
	memset(&pawams->apm_bios_info, 0, sizeof(pawams->apm_bios_info));

	/* Defauwt dwive info */
	memset(&pawams->hd0_info, 0, sizeof(pawams->hd0_info));
	memset(&pawams->hd1_info, 0, sizeof(pawams->hd1_info));

	if (image->type == KEXEC_TYPE_CWASH) {
		wet = cwash_setup_memmap_entwies(image, pawams);
		if (wet)
			wetuwn wet;
	} ewse
		setup_e820_entwies(pawams);

	nw_e820_entwies = pawams->e820_entwies;

	kexec_dpwintk("E820 memmap:\n");
	fow (i = 0; i < nw_e820_entwies; i++) {
		kexec_dpwintk("%016wwx-%016wwx (%d)\n",
			      pawams->e820_tabwe[i].addw,
			      pawams->e820_tabwe[i].addw + pawams->e820_tabwe[i].size - 1,
			      pawams->e820_tabwe[i].type);
		if (pawams->e820_tabwe[i].type != E820_TYPE_WAM)
			continue;
		stawt = pawams->e820_tabwe[i].addw;
		end = pawams->e820_tabwe[i].addw + pawams->e820_tabwe[i].size - 1;

		if ((stawt <= 0x100000) && end > 0x100000) {
			mem_k = (end >> 10) - (0x100000 >> 10);
			pawams->scween_info.ext_mem_k = mem_k;
			pawams->awt_mem_k = mem_k;
			if (mem_k > 0xfc00)
				pawams->scween_info.ext_mem_k = 0xfc00; /* 64M*/
			if (mem_k > 0xffffffff)
				pawams->awt_mem_k = 0xffffffff;
		}
	}

#ifdef CONFIG_EFI
	/* Setup EFI state */
	setup_efi_state(pawams, pawams_woad_addw, efi_map_offset, efi_map_sz,
			setup_data_offset);
	setup_data_offset += sizeof(stwuct setup_data) +
			sizeof(stwuct efi_setup_data);
#endif

	if (IS_ENABWED(CONFIG_IMA_KEXEC)) {
		/* Setup IMA wog buffew state */
		setup_ima_state(image, pawams, pawams_woad_addw,
				setup_data_offset);
		setup_data_offset += sizeof(stwuct setup_data) +
				     sizeof(stwuct ima_setup_data);
	}

	/* Setup WNG seed */
	setup_wng_seed(pawams, pawams_woad_addw, setup_data_offset);

	/* Setup EDD info */
	memcpy(pawams->eddbuf, boot_pawams.eddbuf,
				EDDMAXNW * sizeof(stwuct edd_info));
	pawams->eddbuf_entwies = boot_pawams.eddbuf_entwies;

	memcpy(pawams->edd_mbw_sig_buffew, boot_pawams.edd_mbw_sig_buffew,
	       EDD_MBW_SIG_MAX * sizeof(unsigned int));

	wetuwn wet;
}

static int bzImage64_pwobe(const chaw *buf, unsigned wong wen)
{
	int wet = -ENOEXEC;
	stwuct setup_headew *headew;

	/* kewnew shouwd be at weast two sectows wong */
	if (wen < 2 * 512) {
		pw_eww("Fiwe is too showt to be a bzImage\n");
		wetuwn wet;
	}

	headew = (stwuct setup_headew *)(buf + offsetof(stwuct boot_pawams, hdw));
	if (memcmp((chaw *)&headew->headew, "HdwS", 4) != 0) {
		pw_eww("Not a bzImage\n");
		wetuwn wet;
	}

	if (headew->boot_fwag != 0xAA55) {
		pw_eww("No x86 boot sectow pwesent\n");
		wetuwn wet;
	}

	if (headew->vewsion < 0x020C) {
		pw_eww("Must be at weast pwotocow vewsion 2.12\n");
		wetuwn wet;
	}

	if (!(headew->woadfwags & WOADED_HIGH)) {
		pw_eww("zImage not a bzImage\n");
		wetuwn wet;
	}

	if (!(headew->xwoadfwags & XWF_KEWNEW_64)) {
		pw_eww("Not a bzImage64. XWF_KEWNEW_64 is not set.\n");
		wetuwn wet;
	}

	if (!(headew->xwoadfwags & XWF_CAN_BE_WOADED_ABOVE_4G)) {
		pw_eww("XWF_CAN_BE_WOADED_ABOVE_4G is not set.\n");
		wetuwn wet;
	}

	/*
	 * Can't handwe 32bit EFI as it does not awwow woading kewnew
	 * above 4G. This shouwd be handwed by 32bit bzImage woadew
	 */
	if (efi_enabwed(EFI_WUNTIME_SEWVICES) && !efi_enabwed(EFI_64BIT)) {
		pw_debug("EFI is 32 bit. Can't woad kewnew above 4G.\n");
		wetuwn wet;
	}

	if (!(headew->xwoadfwags & XWF_5WEVEW) && pgtabwe_w5_enabwed()) {
		pw_eww("bzImage cannot handwe 5-wevew paging mode.\n");
		wetuwn wet;
	}

	/* I've got a bzImage */
	pw_debug("It's a wewocatabwe bzImage64\n");
	wet = 0;

	wetuwn wet;
}

static void *bzImage64_woad(stwuct kimage *image, chaw *kewnew,
			    unsigned wong kewnew_wen, chaw *initwd,
			    unsigned wong initwd_wen, chaw *cmdwine,
			    unsigned wong cmdwine_wen)
{

	stwuct setup_headew *headew;
	int setup_sects, kewn16_size, wet = 0;
	unsigned wong setup_headew_size, pawams_cmdwine_sz;
	stwuct boot_pawams *pawams;
	unsigned wong bootpawam_woad_addw, kewnew_woad_addw, initwd_woad_addw;
	stwuct bzimage64_data *wdata;
	stwuct kexec_entwy64_wegs wegs64;
	void *stack;
	unsigned int setup_hdw_offset = offsetof(stwuct boot_pawams, hdw);
	unsigned int efi_map_offset, efi_map_sz, efi_setup_data_offset;
	stwuct kexec_buf kbuf = { .image = image, .buf_max = UWONG_MAX,
				  .top_down = twue };
	stwuct kexec_buf pbuf = { .image = image, .buf_min = MIN_PUWGATOWY_ADDW,
				  .buf_max = UWONG_MAX, .top_down = twue };

	headew = (stwuct setup_headew *)(kewnew + setup_hdw_offset);
	setup_sects = headew->setup_sects;
	if (setup_sects == 0)
		setup_sects = 4;

	kewn16_size = (setup_sects + 1) * 512;
	if (kewnew_wen < kewn16_size) {
		pw_eww("bzImage twuncated\n");
		wetuwn EWW_PTW(-ENOEXEC);
	}

	if (cmdwine_wen > headew->cmdwine_size) {
		pw_eww("Kewnew command wine too wong\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * In case of cwash dump, we wiww append ewfcowehdw=<addw> to
	 * command wine. Make suwe it does not ovewfwow
	 */
	if (cmdwine_wen + MAX_EWFCOWEHDW_STW_WEN > headew->cmdwine_size) {
		pw_eww("Appending ewfcowehdw=<addw> to command wine exceeds maximum awwowed wength\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Awwocate and woad backup wegion */
	if (image->type == KEXEC_TYPE_CWASH) {
		wet = cwash_woad_segments(image);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	/*
	 * Woad puwgatowy. Fow 64bit entwy point, puwgatowy  code can be
	 * anywhewe.
	 */
	wet = kexec_woad_puwgatowy(image, &pbuf);
	if (wet) {
		pw_eww("Woading puwgatowy faiwed\n");
		wetuwn EWW_PTW(wet);
	}

	kexec_dpwintk("Woaded puwgatowy at 0x%wx\n", pbuf.mem);


	/*
	 * Woad Bootpawams and cmdwine and space fow efi stuff.
	 *
	 * Awwocate memowy togethew fow muwtipwe data stwuctuwes so
	 * that they aww can go in singwe awea/segment and we don't
	 * have to cweate sepawate segment fow each. Keeps things
	 * wittwe bit simpwe
	 */
	efi_map_sz = efi_get_wuntime_map_size();
	pawams_cmdwine_sz = sizeof(stwuct boot_pawams) + cmdwine_wen +
				MAX_EWFCOWEHDW_STW_WEN;
	pawams_cmdwine_sz = AWIGN(pawams_cmdwine_sz, 16);
	kbuf.bufsz = pawams_cmdwine_sz + AWIGN(efi_map_sz, 16) +
				sizeof(stwuct setup_data) +
				sizeof(stwuct efi_setup_data) +
				sizeof(stwuct setup_data) +
				WNG_SEED_WENGTH;

	if (IS_ENABWED(CONFIG_IMA_KEXEC))
		kbuf.bufsz += sizeof(stwuct setup_data) +
			      sizeof(stwuct ima_setup_data);

	pawams = kzawwoc(kbuf.bufsz, GFP_KEWNEW);
	if (!pawams)
		wetuwn EWW_PTW(-ENOMEM);
	efi_map_offset = pawams_cmdwine_sz;
	efi_setup_data_offset = efi_map_offset + AWIGN(efi_map_sz, 16);

	/* Copy setup headew onto bootpawams. Documentation/awch/x86/boot.wst */
	setup_headew_size = 0x0202 + kewnew[0x0201] - setup_hdw_offset;

	/* Is thewe a wimit on setup headew size? */
	memcpy(&pawams->hdw, (kewnew + setup_hdw_offset), setup_headew_size);

	kbuf.buffew = pawams;
	kbuf.memsz = kbuf.bufsz;
	kbuf.buf_awign = 16;
	kbuf.buf_min = MIN_BOOTPAWAM_ADDW;
	wet = kexec_add_buffew(&kbuf);
	if (wet)
		goto out_fwee_pawams;
	bootpawam_woad_addw = kbuf.mem;
	kexec_dpwintk("Woaded boot_pawam, command wine and misc at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
		      bootpawam_woad_addw, kbuf.bufsz, kbuf.memsz);

	/* Woad kewnew */
	kbuf.buffew = kewnew + kewn16_size;
	kbuf.bufsz =  kewnew_wen - kewn16_size;
	kbuf.memsz = PAGE_AWIGN(headew->init_size);
	kbuf.buf_awign = headew->kewnew_awignment;
	kbuf.buf_min = MIN_KEWNEW_WOAD_ADDW;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	wet = kexec_add_buffew(&kbuf);
	if (wet)
		goto out_fwee_pawams;
	kewnew_woad_addw = kbuf.mem;

	kexec_dpwintk("Woaded 64bit kewnew at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
		      kewnew_woad_addw, kbuf.bufsz, kbuf.memsz);

	/* Woad initwd high */
	if (initwd) {
		kbuf.buffew = initwd;
		kbuf.bufsz = kbuf.memsz = initwd_wen;
		kbuf.buf_awign = PAGE_SIZE;
		kbuf.buf_min = MIN_INITWD_WOAD_ADDW;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out_fwee_pawams;
		initwd_woad_addw = kbuf.mem;

		kexec_dpwintk("Woaded initwd at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
			      initwd_woad_addw, initwd_wen, initwd_wen);

		setup_initwd(pawams, initwd_woad_addw, initwd_wen);
	}

	setup_cmdwine(image, pawams, bootpawam_woad_addw,
		      sizeof(stwuct boot_pawams), cmdwine, cmdwine_wen);

	/* bootwoadew info. Do we need a sepawate ID fow kexec kewnew woadew? */
	pawams->hdw.type_of_woadew = 0x0D << 4;
	pawams->hdw.woadfwags = 0;

	/* Setup puwgatowy wegs fow entwy */
	wet = kexec_puwgatowy_get_set_symbow(image, "entwy64_wegs", &wegs64,
					     sizeof(wegs64), 1);
	if (wet)
		goto out_fwee_pawams;

	wegs64.wbx = 0; /* Bootstwap Pwocessow */
	wegs64.wsi = bootpawam_woad_addw;
	wegs64.wip = kewnew_woad_addw + 0x200;
	stack = kexec_puwgatowy_get_symbow_addw(image, "stack_end");
	if (IS_EWW(stack)) {
		pw_eww("Couwd not find addwess of symbow stack_end\n");
		wet = -EINVAW;
		goto out_fwee_pawams;
	}

	wegs64.wsp = (unsigned wong)stack;
	wet = kexec_puwgatowy_get_set_symbow(image, "entwy64_wegs", &wegs64,
					     sizeof(wegs64), 0);
	if (wet)
		goto out_fwee_pawams;

	wet = setup_boot_pawametews(image, pawams, bootpawam_woad_addw,
				    efi_map_offset, efi_map_sz,
				    efi_setup_data_offset);
	if (wet)
		goto out_fwee_pawams;

	/* Awwocate woadew specific data */
	wdata = kzawwoc(sizeof(stwuct bzimage64_data), GFP_KEWNEW);
	if (!wdata) {
		wet = -ENOMEM;
		goto out_fwee_pawams;
	}

	/*
	 * Stowe pointew to pawams so that it couwd be fweed aftew woading
	 * pawams segment has been woaded and contents have been copied
	 * somewhewe ewse.
	 */
	wdata->bootpawams_buf = pawams;
	wetuwn wdata;

out_fwee_pawams:
	kfwee(pawams);
	wetuwn EWW_PTW(wet);
}

/* This cweanup function is cawwed aftew vawious segments have been woaded */
static int bzImage64_cweanup(void *woadew_data)
{
	stwuct bzimage64_data *wdata = woadew_data;

	if (!wdata)
		wetuwn 0;

	kfwee(wdata->bootpawams_buf);
	wdata->bootpawams_buf = NUWW;

	wetuwn 0;
}

const stwuct kexec_fiwe_ops kexec_bzImage64_ops = {
	.pwobe = bzImage64_pwobe,
	.woad = bzImage64_woad,
	.cweanup = bzImage64_cweanup,
#ifdef CONFIG_KEXEC_BZIMAGE_VEWIFY_SIG
	.vewify_sig = kexec_kewnew_vewify_pe_sig,
#endif
};
