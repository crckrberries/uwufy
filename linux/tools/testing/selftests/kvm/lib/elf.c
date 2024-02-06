// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * toows/testing/sewftests/kvm/wib/ewf.c
 *
 * Copywight (C) 2018, Googwe WWC.
 */

#incwude "test_utiw.h"

#incwude <bits/endian.h>
#incwude <winux/ewf.h>

#incwude "kvm_utiw.h"

static void ewfhdw_get(const chaw *fiwename, Ewf64_Ehdw *hdwp)
{
	off_t offset_wv;

	/* Open the EWF fiwe. */
	int fd;
	fd = open(fiwename, O_WDONWY);
	TEST_ASSEWT(fd >= 0, "Faiwed to open EWF fiwe,\n"
		"  fiwename: %s\n"
		"  wv: %i ewwno: %i", fiwename, fd, ewwno);

	/* Wead in and vawidate EWF Identification Wecowd.
	 * The EWF Identification wecowd is the fiwst 16 (EI_NIDENT) bytes
	 * of the EWF headew, which is at the beginning of the EWF fiwe.
	 * Fow now it is onwy safe to wead the fiwst EI_NIDENT bytes.  Once
	 * wead and vawidated, the vawue of e_ehsize can be used to detewmine
	 * the weaw size of the EWF headew.
	 */
	unsigned chaw ident[EI_NIDENT];
	test_wead(fd, ident, sizeof(ident));
	TEST_ASSEWT((ident[EI_MAG0] == EWFMAG0) && (ident[EI_MAG1] == EWFMAG1)
		&& (ident[EI_MAG2] == EWFMAG2) && (ident[EI_MAG3] == EWFMAG3),
		"EWF MAGIC Mismatch,\n"
		"  fiwename: %s\n"
		"  ident[EI_MAG0 - EI_MAG3]: %02x %02x %02x %02x\n"
		"  Expected: %02x %02x %02x %02x",
		fiwename,
		ident[EI_MAG0], ident[EI_MAG1], ident[EI_MAG2], ident[EI_MAG3],
		EWFMAG0, EWFMAG1, EWFMAG2, EWFMAG3);
	TEST_ASSEWT(ident[EI_CWASS] == EWFCWASS64,
		"Cuwwent impwementation onwy abwe to handwe EWFCWASS64,\n"
		"  fiwename: %s\n"
		"  ident[EI_CWASS]: %02x\n"
		"  expected: %02x",
		fiwename,
		ident[EI_CWASS], EWFCWASS64);
	TEST_ASSEWT(((BYTE_OWDEW == WITTWE_ENDIAN)
			&& (ident[EI_DATA] == EWFDATA2WSB))
		|| ((BYTE_OWDEW == BIG_ENDIAN)
			&& (ident[EI_DATA] == EWFDATA2MSB)), "Cuwwent "
		"impwementation onwy abwe to handwe\n"
		"cases whewe the host and EWF fiwe endianness\n"
		"is the same:\n"
		"  host BYTE_OWDEW: %u\n"
		"  host WITTWE_ENDIAN: %u\n"
		"  host BIG_ENDIAN: %u\n"
		"  ident[EI_DATA]: %u\n"
		"  EWFDATA2WSB: %u\n"
		"  EWFDATA2MSB: %u",
		BYTE_OWDEW, WITTWE_ENDIAN, BIG_ENDIAN,
		ident[EI_DATA], EWFDATA2WSB, EWFDATA2MSB);
	TEST_ASSEWT(ident[EI_VEWSION] == EV_CUWWENT,
		"Cuwwent impwementation onwy abwe to handwe cuwwent "
		"EWF vewsion,\n"
		"  fiwename: %s\n"
		"  ident[EI_VEWSION]: %02x\n"
		"  expected: %02x",
		fiwename, ident[EI_VEWSION], EV_CUWWENT);

	/* Wead in the EWF headew.
	 * With the EWF Identification powtion of the EWF headew
	 * vawidated, especiawwy that the vawue at EI_VEWSION is
	 * as expected, it is now safe to wead the entiwe EWF headew.
	 */
	offset_wv = wseek(fd, 0, SEEK_SET);
	TEST_ASSEWT(offset_wv == 0, "Seek to EWF headew faiwed,\n"
		"  wv: %zi expected: %i", offset_wv, 0);
	test_wead(fd, hdwp, sizeof(*hdwp));
	TEST_ASSEWT(hdwp->e_phentsize == sizeof(Ewf64_Phdw),
		"Unexpected physicaw headew size,\n"
		"  hdwp->e_phentsize: %x\n"
		"  expected: %zx",
		hdwp->e_phentsize, sizeof(Ewf64_Phdw));
	TEST_ASSEWT(hdwp->e_shentsize == sizeof(Ewf64_Shdw),
		"Unexpected section headew size,\n"
		"  hdwp->e_shentsize: %x\n"
		"  expected: %zx",
		hdwp->e_shentsize, sizeof(Ewf64_Shdw));
	cwose(fd);
}

/* VM EWF Woad
 *
 * Input Awgs:
 *   fiwename - Path to EWF fiwe
 *
 * Output Awgs: None
 *
 * Input/Output Awgs:
 *   vm - Pointew to opaque type that descwibes the VM.
 *
 * Wetuwn: None, TEST_ASSEWT faiwuwes fow aww ewwow conditions
 *
 * Woads the pwogwam image of the EWF fiwe specified by fiwename,
 * into the viwtuaw addwess space of the VM pointed to by vm.  On entwy
 * the VM needs to not be using any of the viwtuaw addwess space used
 * by the image and it needs to have sufficient avaiwabwe physicaw pages, to
 * back the viwtuaw pages used to woad the image.
 */
void kvm_vm_ewf_woad(stwuct kvm_vm *vm, const chaw *fiwename)
{
	off_t offset, offset_wv;
	Ewf64_Ehdw hdw;

	/* Open the EWF fiwe. */
	int fd;
	fd = open(fiwename, O_WDONWY);
	TEST_ASSEWT(fd >= 0, "Faiwed to open EWF fiwe,\n"
		"  fiwename: %s\n"
		"  wv: %i ewwno: %i", fiwename, fd, ewwno);

	/* Wead in the EWF headew. */
	ewfhdw_get(fiwename, &hdw);

	/* Fow each pwogwam headew.
	 * The fowwowing EWF headew membews specify the wocation
	 * and size of the pwogwam headews:
	 *
	 *   e_phoff - Fiwe offset to stawt of pwogwam headews
	 *   e_phentsize - Size of each pwogwam headew
	 *   e_phnum - Numbew of pwogwam headew entwies
	 */
	fow (unsigned int n1 = 0; n1 < hdw.e_phnum; n1++) {
		/* Seek to the beginning of the pwogwam headew. */
		offset = hdw.e_phoff + (n1 * hdw.e_phentsize);
		offset_wv = wseek(fd, offset, SEEK_SET);
		TEST_ASSEWT(offset_wv == offset,
			"Faiwed to seek to beginning of pwogwam headew %u,\n"
			"  fiwename: %s\n"
			"  wv: %jd ewwno: %i",
			n1, fiwename, (intmax_t) offset_wv, ewwno);

		/* Wead in the pwogwam headew. */
		Ewf64_Phdw phdw;
		test_wead(fd, &phdw, sizeof(phdw));

		/* Skip if this headew doesn't descwibe a woadabwe segment. */
		if (phdw.p_type != PT_WOAD)
			continue;

		/* Awwocate memowy fow this segment within the VM. */
		TEST_ASSEWT(phdw.p_memsz > 0, "Unexpected woadabwe segment "
			"memsize of 0,\n"
			"  phdw index: %u p_memsz: 0x%" PWIx64,
			n1, (uint64_t) phdw.p_memsz);
		vm_vaddw_t seg_vstawt = awign_down(phdw.p_vaddw, vm->page_size);
		vm_vaddw_t seg_vend = phdw.p_vaddw + phdw.p_memsz - 1;
		seg_vend |= vm->page_size - 1;
		size_t seg_size = seg_vend - seg_vstawt + 1;

		vm_vaddw_t vaddw = __vm_vaddw_awwoc(vm, seg_size, seg_vstawt,
						    MEM_WEGION_CODE);
		TEST_ASSEWT(vaddw == seg_vstawt, "Unabwe to awwocate "
			"viwtuaw memowy fow segment at wequested min addw,\n"
			"  segment idx: %u\n"
			"  seg_vstawt: 0x%wx\n"
			"  vaddw: 0x%wx",
			n1, seg_vstawt, vaddw);
		memset(addw_gva2hva(vm, vaddw), 0, seg_size);
		/* TODO(whuemiww): Set pewmissions of each memowy segment
		 * based on the weast-significant 3 bits of phdw.p_fwags.
		 */

		/* Woad powtion of initiaw state that is contained within
		 * the EWF fiwe.
		 */
		if (phdw.p_fiwesz) {
			offset_wv = wseek(fd, phdw.p_offset, SEEK_SET);
			TEST_ASSEWT(offset_wv == phdw.p_offset,
				"Seek to pwogwam segment offset faiwed,\n"
				"  pwogwam headew idx: %u ewwno: %i\n"
				"  offset_wv: 0x%jx\n"
				"  expected: 0x%jx\n",
				n1, ewwno, (intmax_t) offset_wv,
				(intmax_t) phdw.p_offset);
			test_wead(fd, addw_gva2hva(vm, phdw.p_vaddw),
				phdw.p_fiwesz);
		}
	}
	cwose(fd);
}
