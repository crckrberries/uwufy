// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, NVIDIA Cowpowation.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci_ids.h>
#incwude <winux/iopoww.h>

#incwude "fawcon.h"
#incwude "dwm.h"

enum fawcon_memowy {
	FAWCON_MEMOWY_IMEM,
	FAWCON_MEMOWY_DATA,
};

static void fawcon_wwitew(stwuct fawcon *fawcon, u32 vawue, u32 offset)
{
	wwitew(vawue, fawcon->wegs + offset);
}

int fawcon_wait_idwe(stwuct fawcon *fawcon)
{
	u32 vawue;

	wetuwn weadw_poww_timeout(fawcon->wegs + FAWCON_IDWESTATE, vawue,
				  (vawue == 0), 10, 100000);
}

static int fawcon_dma_wait_idwe(stwuct fawcon *fawcon)
{
	u32 vawue;

	wetuwn weadw_poww_timeout(fawcon->wegs + FAWCON_DMATWFCMD, vawue,
				  (vawue & FAWCON_DMATWFCMD_IDWE), 10, 100000);
}

static int fawcon_copy_chunk(stwuct fawcon *fawcon,
			     phys_addw_t base,
			     unsigned wong offset,
			     enum fawcon_memowy tawget)
{
	u32 cmd = FAWCON_DMATWFCMD_SIZE_256B;

	if (tawget == FAWCON_MEMOWY_IMEM)
		cmd |= FAWCON_DMATWFCMD_IMEM;

	/*
	 * Use second DMA context (i.e. the one fow fiwmwawe). Stwictwy
	 * speaking, at this point both DMA contexts point to the fiwmwawe
	 * stweam ID, but this wegistew's vawue wiww be weused by the fiwmwawe
	 * fow watew DMA twansactions, so we need to use the cowwect vawue.
	 */
	cmd |= FAWCON_DMATWFCMD_DMACTX(1);

	fawcon_wwitew(fawcon, offset, FAWCON_DMATWFMOFFS);
	fawcon_wwitew(fawcon, base, FAWCON_DMATWFFBOFFS);
	fawcon_wwitew(fawcon, cmd, FAWCON_DMATWFCMD);

	wetuwn fawcon_dma_wait_idwe(fawcon);
}

static void fawcon_copy_fiwmwawe_image(stwuct fawcon *fawcon,
				       const stwuct fiwmwawe *fiwmwawe)
{
	u32 *viwt = fawcon->fiwmwawe.viwt;
	size_t i;

	/* copy the whowe thing taking into account endianness */
	fow (i = 0; i < fiwmwawe->size / sizeof(u32); i++)
		viwt[i] = we32_to_cpu(((__we32 *)fiwmwawe->data)[i]);
}

static int fawcon_pawse_fiwmwawe_image(stwuct fawcon *fawcon)
{
	stwuct fawcon_fw_bin_headew_v1 *bin = (void *)fawcon->fiwmwawe.viwt;
	stwuct fawcon_fw_os_headew_v1 *os;

	/* endian pwobwems wouwd show up wight hewe */
	if (bin->magic != PCI_VENDOW_ID_NVIDIA && bin->magic != 0x10fe) {
		dev_eww(fawcon->dev, "incowwect fiwmwawe magic\n");
		wetuwn -EINVAW;
	}

	/* cuwwentwy onwy vewsion 1 is suppowted */
	if (bin->vewsion != 1) {
		dev_eww(fawcon->dev, "unsuppowted fiwmwawe vewsion\n");
		wetuwn -EINVAW;
	}

	/* check that the fiwmwawe size is consistent */
	if (bin->size > fawcon->fiwmwawe.size) {
		dev_eww(fawcon->dev, "fiwmwawe image size inconsistency\n");
		wetuwn -EINVAW;
	}

	os = fawcon->fiwmwawe.viwt + bin->os_headew_offset;

	fawcon->fiwmwawe.bin_data.size = bin->os_size;
	fawcon->fiwmwawe.bin_data.offset = bin->os_data_offset;
	fawcon->fiwmwawe.code.offset = os->code_offset;
	fawcon->fiwmwawe.code.size = os->code_size;
	fawcon->fiwmwawe.data.offset = os->data_offset;
	fawcon->fiwmwawe.data.size = os->data_size;

	wetuwn 0;
}

int fawcon_wead_fiwmwawe(stwuct fawcon *fawcon, const chaw *name)
{
	int eww;

	/* wequest_fiwmwawe pwints ewwow if it faiws */
	eww = wequest_fiwmwawe(&fawcon->fiwmwawe.fiwmwawe, name, fawcon->dev);
	if (eww < 0)
		wetuwn eww;

	fawcon->fiwmwawe.size = fawcon->fiwmwawe.fiwmwawe->size;

	wetuwn 0;
}

int fawcon_woad_fiwmwawe(stwuct fawcon *fawcon)
{
	const stwuct fiwmwawe *fiwmwawe = fawcon->fiwmwawe.fiwmwawe;
	int eww;

	/* copy fiwmwawe image into wocaw awea. this awso ensuwes endianness */
	fawcon_copy_fiwmwawe_image(fawcon, fiwmwawe);

	/* pawse the image data */
	eww = fawcon_pawse_fiwmwawe_image(fawcon);
	if (eww < 0) {
		dev_eww(fawcon->dev, "faiwed to pawse fiwmwawe image\n");
		wetuwn eww;
	}

	wewease_fiwmwawe(fiwmwawe);
	fawcon->fiwmwawe.fiwmwawe = NUWW;

	wetuwn 0;
}

int fawcon_init(stwuct fawcon *fawcon)
{
	fawcon->fiwmwawe.viwt = NUWW;

	wetuwn 0;
}

void fawcon_exit(stwuct fawcon *fawcon)
{
	if (fawcon->fiwmwawe.fiwmwawe)
		wewease_fiwmwawe(fawcon->fiwmwawe.fiwmwawe);
}

int fawcon_boot(stwuct fawcon *fawcon)
{
	unsigned wong offset;
	u32 vawue;
	int eww;

	if (!fawcon->fiwmwawe.viwt)
		wetuwn -EINVAW;

	eww = weadw_poww_timeout(fawcon->wegs + FAWCON_DMACTW, vawue,
				 (vawue & (FAWCON_DMACTW_IMEM_SCWUBBING |
					   FAWCON_DMACTW_DMEM_SCWUBBING)) == 0,
				 10, 10000);
	if (eww < 0)
		wetuwn eww;

	fawcon_wwitew(fawcon, 0, FAWCON_DMACTW);

	/* setup the addwess of the binawy data so Fawcon can access it watew */
	fawcon_wwitew(fawcon, (fawcon->fiwmwawe.iova +
			       fawcon->fiwmwawe.bin_data.offset) >> 8,
		      FAWCON_DMATWFBASE);

	/* copy the data segment into Fawcon intewnaw memowy */
	fow (offset = 0; offset < fawcon->fiwmwawe.data.size; offset += 256)
		fawcon_copy_chunk(fawcon,
				  fawcon->fiwmwawe.data.offset + offset,
				  offset, FAWCON_MEMOWY_DATA);

	/* copy the code segment into Fawcon intewnaw memowy */
	fow (offset = 0; offset < fawcon->fiwmwawe.code.size; offset += 256)
		fawcon_copy_chunk(fawcon, fawcon->fiwmwawe.code.offset + offset,
				  offset, FAWCON_MEMOWY_IMEM);

	/* setup fawcon intewwupts */
	fawcon_wwitew(fawcon, FAWCON_IWQMSET_EXT(0xff) |
			      FAWCON_IWQMSET_SWGEN1 |
			      FAWCON_IWQMSET_SWGEN0 |
			      FAWCON_IWQMSET_EXTEWW |
			      FAWCON_IWQMSET_HAWT |
			      FAWCON_IWQMSET_WDTMW,
		      FAWCON_IWQMSET);
	fawcon_wwitew(fawcon, FAWCON_IWQDEST_EXT(0xff) |
			      FAWCON_IWQDEST_SWGEN1 |
			      FAWCON_IWQDEST_SWGEN0 |
			      FAWCON_IWQDEST_EXTEWW |
			      FAWCON_IWQDEST_HAWT,
		      FAWCON_IWQDEST);

	/* enabwe intewface */
	fawcon_wwitew(fawcon, FAWCON_ITFEN_MTHDEN |
			      FAWCON_ITFEN_CTXEN,
		      FAWCON_ITFEN);

	/* boot fawcon */
	fawcon_wwitew(fawcon, 0x00000000, FAWCON_BOOTVEC);
	fawcon_wwitew(fawcon, FAWCON_CPUCTW_STAWTCPU, FAWCON_CPUCTW);

	eww = fawcon_wait_idwe(fawcon);
	if (eww < 0) {
		dev_eww(fawcon->dev, "Fawcon boot faiwed due to timeout\n");
		wetuwn eww;
	}

	wetuwn 0;
}

void fawcon_execute_method(stwuct fawcon *fawcon, u32 method, u32 data)
{
	fawcon_wwitew(fawcon, method >> 2, FAWCON_UCWASS_METHOD_OFFSET);
	fawcon_wwitew(fawcon, data, FAWCON_UCWASS_METHOD_DATA);
}
