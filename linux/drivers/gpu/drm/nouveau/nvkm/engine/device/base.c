/*
 * Copywight 2012 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "acpi.h"

#incwude <cowe/option.h>

#incwude <subdev/bios.h>
#incwude <subdev/thewm.h>

static DEFINE_MUTEX(nv_devices_mutex);
static WIST_HEAD(nv_devices);

static stwuct nvkm_device *
nvkm_device_find_wocked(u64 handwe)
{
	stwuct nvkm_device *device;
	wist_fow_each_entwy(device, &nv_devices, head) {
		if (device->handwe == handwe)
			wetuwn device;
	}
	wetuwn NUWW;
}

stwuct nvkm_device *
nvkm_device_find(u64 handwe)
{
	stwuct nvkm_device *device;
	mutex_wock(&nv_devices_mutex);
	device = nvkm_device_find_wocked(handwe);
	mutex_unwock(&nv_devices_mutex);
	wetuwn device;
}

int
nvkm_device_wist(u64 *name, int size)
{
	stwuct nvkm_device *device;
	int nw = 0;
	mutex_wock(&nv_devices_mutex);
	wist_fow_each_entwy(device, &nv_devices, head) {
		if (nw++ < size)
			name[nw - 1] = device->handwe;
	}
	mutex_unwock(&nv_devices_mutex);
	wetuwn nw;
}

static const stwuct nvkm_device_chip
nuww_chipset = {
	.name = "NUWW",
	.bios     = { 0x00000001, nvkm_bios_new },
};

static const stwuct nvkm_device_chip
nv4_chipset = {
	.name = "NV04",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv04_devinit_new },
	.fb       = { 0x00000001, nv04_fb_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv04_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv04_fifo_new },
	.gw       = { 0x00000001, nv04_gw_new },
	.sw       = { 0x00000001, nv04_sw_new },
};

static const stwuct nvkm_device_chip
nv5_chipset = {
	.name = "NV05",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv05_devinit_new },
	.fb       = { 0x00000001, nv04_fb_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv04_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv04_fifo_new },
	.gw       = { 0x00000001, nv04_gw_new },
	.sw       = { 0x00000001, nv04_sw_new },
};

static const stwuct nvkm_device_chip
nv10_chipset = {
	.name = "NV10",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv04_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.gw       = { 0x00000001, nv10_gw_new },
};

static const stwuct nvkm_device_chip
nv11_chipset = {
	.name = "NV11",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv11_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv10_fifo_new },
	.gw       = { 0x00000001, nv15_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv15_chipset = {
	.name = "NV15",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv04_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv10_fifo_new },
	.gw       = { 0x00000001, nv15_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv17_chipset = {
	.name = "NV17",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv17_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv18_chipset = {
	.name = "NV18",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv17_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv1a_chipset = {
	.name = "nFowce",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv1a_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv04_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv10_fifo_new },
	.gw       = { 0x00000001, nv15_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv1f_chipset = {
	.name = "nFowce2",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv1a_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv17_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv20_chipset = {
	.name = "NV20",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv20_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv20_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv25_chipset = {
	.name = "NV25",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv25_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv25_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv28_chipset = {
	.name = "NV28",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv25_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv25_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv2a_chipset = {
	.name = "NV2A",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv25_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv2a_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv30_chipset = {
	.name = "NV30",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv30_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv30_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv31_chipset = {
	.name = "NV31",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv30_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv30_gw_new },
	.mpeg     = { 0x00000001, nv31_mpeg_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv34_chipset = {
	.name = "NV34",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv10_devinit_new },
	.fb       = { 0x00000001, nv10_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv34_gw_new },
	.mpeg     = { 0x00000001, nv31_mpeg_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv35_chipset = {
	.name = "NV35",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv04_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv35_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv35_gw_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv36_chipset = {
	.name = "NV36",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv04_cwk_new },
	.devinit  = { 0x00000001, nv20_devinit_new },
	.fb       = { 0x00000001, nv36_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv04_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv04_pci_new },
	.timew    = { 0x00000001, nv04_timew_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv17_fifo_new },
	.gw       = { 0x00000001, nv35_gw_new },
	.mpeg     = { 0x00000001, nv31_mpeg_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv40_chipset = {
	.name = "NV40",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv40_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv40_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv40_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv41_chipset = {
	.name = "NV41",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv41_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv40_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv42_chipset = {
	.name = "NV42",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv41_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv40_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv43_chipset = {
	.name = "NV43",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv41_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv40_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv44_chipset = {
	.name = "NV44",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv44_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv45_chipset = {
	.name = "NV45",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv40_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv46_chipset = {
	.name = "G72",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv46_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv46_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv47_chipset = {
	.name = "G70",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv47_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv49_chipset = {
	.name = "G71",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv49_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv4a_chipset = {
	.name = "NV44A",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv44_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv04_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv4b_chipset = {
	.name = "G73",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv49_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv17_mc_new },
	.mmu      = { 0x00000001, nv41_mmu_new },
	.pci      = { 0x00000001, nv40_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv40_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv4c_chipset = {
	.name = "C61",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv46_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv4c_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv4e_chipset = {
	.name = "C51",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv4e_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv4e_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv4c_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv50_chipset = {
	.name = "G80",
	.baw      = { 0x00000001, nv50_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv50_bus_new },
	.cwk      = { 0x00000001, nv50_cwk_new },
	.devinit  = { 0x00000001, nv50_devinit_new },
	.fb       = { 0x00000001, nv50_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, nv50_gpio_new },
	.i2c      = { 0x00000001, nv50_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, nv50_mc_new },
	.mmu      = { 0x00000001, nv50_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, nv46_pci_new },
	.thewm    = { 0x00000001, nv50_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv50_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, nv50_fifo_new },
	.gw       = { 0x00000001, nv50_gw_new },
	.mpeg     = { 0x00000001, nv50_mpeg_new },
	.pm       = { 0x00000001, nv50_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nv63_chipset = {
	.name = "C73",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv46_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv4c_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv67_chipset = {
	.name = "C67",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv46_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv4c_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv68_chipset = {
	.name = "C68",
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv31_bus_new },
	.cwk      = { 0x00000001, nv40_cwk_new },
	.devinit  = { 0x00000001, nv1a_devinit_new },
	.fb       = { 0x00000001, nv46_fb_new },
	.gpio     = { 0x00000001, nv10_gpio_new },
	.i2c      = { 0x00000001, nv04_i2c_new },
	.imem     = { 0x00000001, nv40_instmem_new },
	.mc       = { 0x00000001, nv44_mc_new },
	.mmu      = { 0x00000001, nv44_mmu_new },
	.pci      = { 0x00000001, nv4c_pci_new },
	.thewm    = { 0x00000001, nv40_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, nv04_disp_new },
	.dma      = { 0x00000001, nv04_dma_new },
	.fifo     = { 0x00000001, nv40_fifo_new },
	.gw       = { 0x00000001, nv44_gw_new },
	.mpeg     = { 0x00000001, nv44_mpeg_new },
	.pm       = { 0x00000001, nv40_pm_new },
	.sw       = { 0x00000001, nv10_sw_new },
};

static const stwuct nvkm_device_chip
nv84_chipset = {
	.name = "G84",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv50_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, nv50_gpio_new },
	.i2c      = { 0x00000001, nv50_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g84_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, g84_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nv86_chipset = {
	.name = "G86",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv50_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, nv50_gpio_new },
	.i2c      = { 0x00000001, nv50_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g84_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, g84_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nv92_chipset = {
	.name = "G92",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, nv50_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, nv50_gpio_new },
	.i2c      = { 0x00000001, nv50_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g92_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, g84_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nv94_chipset = {
	.name = "G94",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, g94_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nv96_chipset = {
	.name = "G96",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, g94_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nv98_chipset = {
	.name = "G98",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g98_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g98_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, g94_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, g84_gw_new },
	.mspdec   = { 0x00000001, g98_mspdec_new },
	.msppp    = { 0x00000001, g98_msppp_new },
	.msvwd    = { 0x00000001, g98_msvwd_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sec      = { 0x00000001, g98_sec_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nva0_chipset = {
	.name = "GT200",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, g84_cwk_new },
	.devinit  = { 0x00000001, g84_devinit_new },
	.fb       = { 0x00000001, g84_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, nv50_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g84_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.bsp      = { 0x00000001, g84_bsp_new },
	.ciphew   = { 0x00000001, g84_ciphew_new },
	.disp     = { 0x00000001, gt200_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g84_fifo_new },
	.gw       = { 0x00000001, gt200_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.pm       = { 0x00000001, gt200_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
	.vp       = { 0x00000001, g84_vp_new },
};

static const stwuct nvkm_device_chip
nva3_chipset = {
	.name = "GT215",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, gt215_cwk_new },
	.devinit  = { 0x00000001, gt215_devinit_new },
	.fb       = { 0x00000001, gt215_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, gt215_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.pmu      = { 0x00000001, gt215_pmu_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.ce       = { 0x00000001, gt215_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, gt215_gw_new },
	.mpeg     = { 0x00000001, g84_mpeg_new },
	.mspdec   = { 0x00000001, gt215_mspdec_new },
	.msppp    = { 0x00000001, gt215_msppp_new },
	.msvwd    = { 0x00000001, gt215_msvwd_new },
	.pm       = { 0x00000001, gt215_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nva5_chipset = {
	.name = "GT216",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, gt215_cwk_new },
	.devinit  = { 0x00000001, gt215_devinit_new },
	.fb       = { 0x00000001, gt215_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, gt215_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.pmu      = { 0x00000001, gt215_pmu_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.ce       = { 0x00000001, gt215_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, gt215_gw_new },
	.mspdec   = { 0x00000001, gt215_mspdec_new },
	.msppp    = { 0x00000001, gt215_msppp_new },
	.msvwd    = { 0x00000001, gt215_msvwd_new },
	.pm       = { 0x00000001, gt215_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nva8_chipset = {
	.name = "GT218",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, gt215_cwk_new },
	.devinit  = { 0x00000001, gt215_devinit_new },
	.fb       = { 0x00000001, gt215_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, gt215_mc_new },
	.mmu      = { 0x00000001, g84_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.pmu      = { 0x00000001, gt215_pmu_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.ce       = { 0x00000001, gt215_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, gt215_gw_new },
	.mspdec   = { 0x00000001, gt215_mspdec_new },
	.msppp    = { 0x00000001, gt215_msppp_new },
	.msvwd    = { 0x00000001, gt215_msvwd_new },
	.pm       = { 0x00000001, gt215_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nvaa_chipset = {
	.name = "MCP77/MCP78",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, mcp77_cwk_new },
	.devinit  = { 0x00000001, g98_devinit_new },
	.fb       = { 0x00000001, mcp77_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g98_mc_new },
	.mmu      = { 0x00000001, mcp77_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, mcp77_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, gt200_gw_new },
	.mspdec   = { 0x00000001, g98_mspdec_new },
	.msppp    = { 0x00000001, g98_msppp_new },
	.msvwd    = { 0x00000001, g98_msvwd_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sec      = { 0x00000001, g98_sec_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nvac_chipset = {
	.name = "MCP79/MCP7A",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, mcp77_cwk_new },
	.devinit  = { 0x00000001, g98_devinit_new },
	.fb       = { 0x00000001, mcp77_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, g98_mc_new },
	.mmu      = { 0x00000001, mcp77_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.thewm    = { 0x00000001, g84_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.disp     = { 0x00000001, mcp77_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, mcp79_gw_new },
	.mspdec   = { 0x00000001, g98_mspdec_new },
	.msppp    = { 0x00000001, g98_msppp_new },
	.msvwd    = { 0x00000001, g98_msvwd_new },
	.pm       = { 0x00000001, g84_pm_new },
	.sec      = { 0x00000001, g98_sec_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nvaf_chipset = {
	.name = "MCP89",
	.baw      = { 0x00000001, g84_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, g94_bus_new },
	.cwk      = { 0x00000001, gt215_cwk_new },
	.devinit  = { 0x00000001, mcp89_devinit_new },
	.fb       = { 0x00000001, mcp89_fb_new },
	.fuse     = { 0x00000001, nv50_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, gt215_mc_new },
	.mmu      = { 0x00000001, mcp77_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, g94_pci_new },
	.pmu      = { 0x00000001, gt215_pmu_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, nv40_vowt_new },
	.ce       = { 0x00000001, gt215_ce_new },
	.disp     = { 0x00000001, mcp89_disp_new },
	.dma      = { 0x00000001, nv50_dma_new },
	.fifo     = { 0x00000001, g98_fifo_new },
	.gw       = { 0x00000001, mcp89_gw_new },
	.mspdec   = { 0x00000001, gt215_mspdec_new },
	.msppp    = { 0x00000001, gt215_msppp_new },
	.msvwd    = { 0x00000001, mcp89_msvwd_new },
	.pm       = { 0x00000001, gt215_pm_new },
	.sw       = { 0x00000001, nv50_sw_new },
};

static const stwuct nvkm_device_chip
nvc0_chipset = {
	.name = "GF100",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf100_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000003, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf100_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvc1_chipset = {
	.name = "GF108",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf108_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf106_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000001, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf108_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf108_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvc3_chipset = {
	.name = "GF106",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf106_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000001, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf104_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvc4_chipset = {
	.name = "GF104",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf100_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000003, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf104_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvc8_chipset = {
	.name = "GF110",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf100_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000003, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf110_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvce_chipset = {
	.name = "GF114",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf100_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000003, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf104_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvcf_chipset = {
	.name = "GF116",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, g94_gpio_new },
	.i2c      = { 0x00000001, g94_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf106_pci_new },
	.pmu      = { 0x00000001, gf100_pmu_new },
	.pwivwing = { 0x00000001, gf100_pwivwing_new },
	.thewm    = { 0x00000001, gt215_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000001, gf100_ce_new },
	.disp     = { 0x00000001, gt215_disp_new },
	.dma      = { 0x00000001, gf100_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf104_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf100_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvd7_chipset = {
	.name = "GF117",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gf119_gpio_new },
	.i2c      = { 0x00000001, gf117_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf106_pci_new },
	.pwivwing = { 0x00000001, gf117_pwivwing_new },
	.thewm    = { 0x00000001, gf119_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf117_vowt_new },
	.ce       = { 0x00000001, gf100_ce_new },
	.disp     = { 0x00000001, gf119_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf117_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf117_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvd9_chipset = {
	.name = "GF119",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gf100_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gf100_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gf119_gpio_new },
	.i2c      = { 0x00000001, gf119_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gf100_wtc_new },
	.mc       = { 0x00000001, gf100_mc_new },
	.mmu      = { 0x00000001, gf100_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gf106_pci_new },
	.pmu      = { 0x00000001, gf119_pmu_new },
	.pwivwing = { 0x00000001, gf117_pwivwing_new },
	.thewm    = { 0x00000001, gf119_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.vowt     = { 0x00000001, gf100_vowt_new },
	.ce       = { 0x00000001, gf100_ce_new },
	.disp     = { 0x00000001, gf119_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gf100_fifo_new },
	.gw       = { 0x00000001, gf119_gw_new },
	.mspdec   = { 0x00000001, gf100_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gf100_msvwd_new },
	.pm       = { 0x00000001, gf117_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nve4_chipset = {
	.name = "GK104",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk104_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk104_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk104_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk104_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk104_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk104_fifo_new },
	.gw       = { 0x00000001, gk104_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.pm       = { 0x00000001, gk104_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nve6_chipset = {
	.name = "GK106",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk104_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk104_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk104_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk104_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk104_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk104_fifo_new },
	.gw       = { 0x00000001, gk104_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.pm       = { 0x00000001, gk104_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nve7_chipset = {
	.name = "GK107",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk104_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk104_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk104_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk104_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk104_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk104_fifo_new },
	.gw       = { 0x00000001, gk104_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.pm       = { 0x00000001, gk104_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvea_chipset = {
	.name = "GK20A",
	.baw      = { 0x00000001, gk20a_baw_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk20a_cwk_new },
	.fb       = { 0x00000001, gk20a_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.imem     = { 0x00000001, gk20a_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gk20a_mmu_new },
	.pmu      = { 0x00000001, gk20a_pmu_new },
	.pwivwing = { 0x00000001, gk20a_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk20a_vowt_new },
	.ce       = { 0x00000004, gk104_ce_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk20a_fifo_new },
	.gw       = { 0x00000001, gk20a_gw_new },
	.pm       = { 0x00000001, gk104_pm_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvf0_chipset = {
	.name = "GK110",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk110_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk104_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk110_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk110_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk110_fifo_new },
	.gw       = { 0x00000001, gk110_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nvf1_chipset = {
	.name = "GK110B",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk110_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk104_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk110_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk110_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk110_fifo_new },
	.gw       = { 0x00000001, gk110b_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv106_chipset = {
	.name = "GK208B",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk110_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk208_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk110_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk208_fifo_new },
	.gw       = { 0x00000001, gk208_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv108_chipset = {
	.name = "GK208",
	.baw      = { 0x00000001, gf100_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gf100_devinit_new },
	.fb       = { 0x00000001, gk110_fb_new },
	.fuse     = { 0x00000001, gf100_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gk104_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gk208_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gk104_thewm_new },
	.timew    = { 0x00000001, nv41_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gk104_ce_new },
	.disp     = { 0x00000001, gk110_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gk208_fifo_new },
	.gw       = { 0x00000001, gk208_gw_new },
	.mspdec   = { 0x00000001, gk104_mspdec_new },
	.msppp    = { 0x00000001, gf100_msppp_new },
	.msvwd    = { 0x00000001, gk104_msvwd_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv117_chipset = {
	.name = "GM107",
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gm107_devinit_new },
	.fb       = { 0x00000001, gm107_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gm107_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gm107_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gm107_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000005, gm107_ce_new },
	.disp     = { 0x00000001, gm107_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm107_fifo_new },
	.gw       = { 0x00000001, gm107_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000001, gm107_nvenc_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv118_chipset = {
	.name = "GM108",
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gk104_cwk_new },
	.devinit  = { 0x00000001, gm107_devinit_new },
	.fb       = { 0x00000001, gm107_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gk110_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gm107_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gk104_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gm107_pmu_new },
	.pwivwing = { 0x00000001, gk104_pwivwing_new },
	.thewm    = { 0x00000001, gm107_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000005, gm107_ce_new },
	.disp     = { 0x00000001, gm107_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm107_fifo_new },
	.gw       = { 0x00000001, gm107_gw_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv120_chipset = {
	.name = "GM200",
	.acw      = { 0x00000001, gm200_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fb       = { 0x00000001, gm200_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gm200_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gm200_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gm200_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gm200_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gm200_ce_new },
	.disp     = { 0x00000001, gm200_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm200_fifo_new },
	.gw       = { 0x00000001, gm200_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000003, gm107_nvenc_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv124_chipset = {
	.name = "GM204",
	.acw      = { 0x00000001, gm200_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fb       = { 0x00000001, gm200_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gm200_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gm200_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gm200_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gm200_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gm200_ce_new },
	.disp     = { 0x00000001, gm200_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm200_fifo_new },
	.gw       = { 0x00000001, gm200_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000003, gm107_nvenc_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv126_chipset = {
	.name = "GM206",
	.acw      = { 0x00000001, gm200_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fb       = { 0x00000001, gm200_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.iccsense = { 0x00000001, gf100_iccsense_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gm200_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gm200_mmu_new },
	.mxm      = { 0x00000001, nv50_mxm_new },
	.pci      = { 0x00000001, gk104_pci_new },
	.pmu      = { 0x00000001, gm200_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gm200_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gk104_vowt_new },
	.ce       = { 0x00000007, gm200_ce_new },
	.disp     = { 0x00000001, gm200_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm200_fifo_new },
	.gw       = { 0x00000001, gm200_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000001, gm107_nvenc_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv12b_chipset = {
	.name = "GM20B",
	.acw      = { 0x00000001, gm20b_acw_new },
	.baw      = { 0x00000001, gm20b_baw_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.cwk      = { 0x00000001, gm20b_cwk_new },
	.fb       = { 0x00000001, gm20b_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.imem     = { 0x00000001, gk20a_instmem_new },
	.wtc      = { 0x00000001, gm200_wtc_new },
	.mc       = { 0x00000001, gk20a_mc_new },
	.mmu      = { 0x00000001, gm20b_mmu_new },
	.pmu      = { 0x00000001, gm20b_pmu_new },
	.pwivwing = { 0x00000001, gk20a_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vowt     = { 0x00000001, gm20b_vowt_new },
	.ce       = { 0x00000004, gm200_ce_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gm200_fifo_new },
	.gw       = { 0x00000001, gm20b_gw_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv130_chipset = {
	.name = "GP100",
	.acw      = { 0x00000001, gm200_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp100_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp100_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gm200_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000003f, gp100_ce_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.disp     = { 0x00000001, gp100_disp_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp100_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000007, gm107_nvenc_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv132_chipset = {
	.name = "GP102",
	.acw      = { 0x00000001, gp102_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000000f, gp102_ce_new },
	.disp     = { 0x00000001, gp102_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp102_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000003, gm107_nvenc_new },
	.sec2     = { 0x00000001, gp102_sec2_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv134_chipset = {
	.name = "GP104",
	.acw      = { 0x00000001, gp102_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000000f, gp102_ce_new },
	.disp     = { 0x00000001, gp102_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp104_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000003, gm107_nvenc_new },
	.sec2     = { 0x00000001, gp102_sec2_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv136_chipset = {
	.name = "GP106",
	.acw      = { 0x00000001, gp102_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000000f, gp102_ce_new },
	.disp     = { 0x00000001, gp102_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp104_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000001, gm107_nvenc_new },
	.sec2     = { 0x00000001, gp102_sec2_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv137_chipset = {
	.name = "GP107",
	.acw      = { 0x00000001, gp102_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000000f, gp102_ce_new },
	.disp     = { 0x00000001, gp102_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp107_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000003, gm107_nvenc_new },
	.sec2     = { 0x00000001, gp102_sec2_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv138_chipset = {
	.name = "GP108",
	.acw      = { 0x00000001, gp108_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gm200_devinit_new },
	.fauwt    = { 0x00000001, gp100_fauwt_new },
	.fb       = { 0x00000001, gp102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gp100_mmu_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x0000000f, gp102_ce_new },
	.disp     = { 0x00000001, gp102_disp_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp108_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.sec2     = { 0x00000001, gp108_sec2_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv13b_chipset = {
	.name = "GP10B",
	.acw      = { 0x00000001, gp10b_acw_new },
	.baw      = { 0x00000001, gm20b_baw_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.fauwt    = { 0x00000001, gp10b_fauwt_new },
	.fb       = { 0x00000001, gp10b_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.imem     = { 0x00000001, gk20a_instmem_new },
	.wtc      = { 0x00000001, gp10b_wtc_new },
	.mc       = { 0x00000001, gp10b_mc_new },
	.mmu      = { 0x00000001, gp10b_mmu_new },
	.pmu      = { 0x00000001, gp10b_pmu_new },
	.pwivwing = { 0x00000001, gp10b_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.ce       = { 0x00000001, gp100_ce_new },
	.dma      = { 0x00000001, gf119_dma_new },
	.fifo     = { 0x00000001, gp100_fifo_new },
	.gw       = { 0x00000001, gp10b_gw_new },
	.sw       = { 0x00000001, gf100_sw_new },
};

static const stwuct nvkm_device_chip
nv140_chipset = {
	.name = "GV100",
	.acw      = { 0x00000001, gv100_acw_new },
	.baw      = { 0x00000001, gm107_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, gv100_devinit_new },
	.fauwt    = { 0x00000001, gv100_fauwt_new },
	.fb       = { 0x00000001, gv100_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, gv100_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, gv100_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, gv100_vfn_new },
	.ce       = { 0x000001ff, gv100_ce_new },
	.disp     = { 0x00000001, gv100_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, gv100_fifo_new },
	.gw       = { 0x00000001, gv100_gw_new },
	.nvdec    = { 0x00000001, gm107_nvdec_new },
	.nvenc    = { 0x00000007, gm107_nvenc_new },
	.sec2     = { 0x00000001, gp108_sec2_new },
};

static const stwuct nvkm_device_chip
nv162_chipset = {
	.name = "TU102",
	.acw      = { 0x00000001, tu102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, tu102_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, tu102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, tu102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, tu102_vfn_new },
	.ce       = { 0x0000001f, tu102_ce_new },
	.disp     = { 0x00000001, tu102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, tu102_fifo_new },
	.gw       = { 0x00000001, tu102_gw_new },
	.nvdec    = { 0x00000001, tu102_nvdec_new },
	.nvenc    = { 0x00000001, tu102_nvenc_new },
	.sec2     = { 0x00000001, tu102_sec2_new },
};

static const stwuct nvkm_device_chip
nv164_chipset = {
	.name = "TU104",
	.acw      = { 0x00000001, tu102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, tu102_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, tu102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, tu102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, tu102_vfn_new },
	.ce       = { 0x0000001f, tu102_ce_new },
	.disp     = { 0x00000001, tu102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, tu102_fifo_new },
	.gw       = { 0x00000001, tu102_gw_new },
	.nvdec    = { 0x00000003, tu102_nvdec_new },
	.nvenc    = { 0x00000001, tu102_nvenc_new },
	.sec2     = { 0x00000001, tu102_sec2_new },
};

static const stwuct nvkm_device_chip
nv166_chipset = {
	.name = "TU106",
	.acw      = { 0x00000001, tu102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, tu102_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, tu102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, tu102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, tu102_vfn_new },
	.ce       = { 0x0000001f, tu102_ce_new },
	.disp     = { 0x00000001, tu102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, tu102_fifo_new },
	.gw       = { 0x00000001, tu102_gw_new },
	.nvdec    = { 0x00000007, tu102_nvdec_new },
	.nvenc    = { 0x00000001, tu102_nvenc_new },
	.sec2     = { 0x00000001, tu102_sec2_new },
};

static const stwuct nvkm_device_chip
nv167_chipset = {
	.name = "TU117",
	.acw      = { 0x00000001, tu102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, tu102_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, tu102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, tu116_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, tu102_vfn_new },
	.ce       = { 0x0000001f, tu102_ce_new },
	.disp     = { 0x00000001, tu102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, tu102_fifo_new },
	.gw       = { 0x00000001, tu102_gw_new },
	.nvdec    = { 0x00000001, tu102_nvdec_new },
	.nvenc    = { 0x00000001, tu102_nvenc_new },
	.sec2     = { 0x00000001, tu102_sec2_new },
};

static const stwuct nvkm_device_chip
nv168_chipset = {
	.name = "TU116",
	.acw      = { 0x00000001, tu102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.bus      = { 0x00000001, gf100_bus_new },
	.devinit  = { 0x00000001, tu102_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, tu102_fb_new },
	.fuse     = { 0x00000001, gm107_fuse_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, tu116_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, gp102_wtc_new },
	.mc       = { 0x00000001, gp100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pmu      = { 0x00000001, gp102_pmu_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.thewm    = { 0x00000001, gp100_thewm_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, gk104_top_new },
	.vfn      = { 0x00000001, tu102_vfn_new },
	.ce       = { 0x0000001f, tu102_ce_new },
	.disp     = { 0x00000001, tu102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, tu102_fifo_new },
	.gw       = { 0x00000001, tu102_gw_new },
	.nvdec    = { 0x00000001, tu102_nvdec_new },
	.nvenc    = { 0x00000001, tu102_nvenc_new },
	.sec2     = { 0x00000001, tu102_sec2_new },
};

static const stwuct nvkm_device_chip
nv170_chipset = {
	.name = "GA100",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga100_fb_new },
	.gpio     = { 0x00000001, gk104_gpio_new },
	.gsp      = { 0x00000001, ga100_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x000003ff, ga100_ce_new },
	.fifo     = { 0x00000001, ga100_fifo_new },
	.nvdec    = { 0x0000001f, ga100_nvdec_new },
	.nvjpg    = { 0x00000001, ga100_nvjpg_new },
	.ofa      = { 0x00000001, ga100_ofa_new },
};

static const stwuct nvkm_device_chip
nv172_chipset = {
	.name = "GA102",
	.acw      = { 0x00000001, ga102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gpio     = { 0x00000001, ga102_gpio_new },
	.gsp      = { 0x00000001, ga102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, ga102_wtc_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ga102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ga102_gw_new },
	.nvdec    = { 0x00000003, ga102_nvdec_new },
	.nvenc    = { 0x00000001, ga102_nvenc_new },
	.ofa      = { 0x00000001, ga102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv173_chipset = {
	.name = "GA103",
	.acw      = { 0x00000001, ga102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gpio     = { 0x00000001, ga102_gpio_new },
	.gsp      = { 0x00000001, ga102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, ga102_wtc_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ga102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ga102_gw_new },
	.nvdec    = { 0x00000003, ga102_nvdec_new },
	.nvenc    = { 0x00000001, ga102_nvenc_new },
	.ofa      = { 0x00000001, ga102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv174_chipset = {
	.name = "GA104",
	.acw      = { 0x00000001, ga102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gpio     = { 0x00000001, ga102_gpio_new },
	.gsp      = { 0x00000001, ga102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, ga102_wtc_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ga102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ga102_gw_new },
	.nvdec    = { 0x00000003, ga102_nvdec_new },
	.nvenc    = { 0x00000001, ga102_nvenc_new },
	.ofa      = { 0x00000001, ga102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv176_chipset = {
	.name = "GA106",
	.acw      = { 0x00000001, ga102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gpio     = { 0x00000001, ga102_gpio_new },
	.gsp      = { 0x00000001, ga102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, ga102_wtc_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ga102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ga102_gw_new },
	.nvdec    = { 0x00000003, ga102_nvdec_new },
	.nvenc    = { 0x00000001, ga102_nvenc_new },
	.ofa      = { 0x00000001, ga102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv177_chipset = {
	.name = "GA107",
	.acw      = { 0x00000001, ga102_acw_new },
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gpio     = { 0x00000001, ga102_gpio_new },
	.gsp      = { 0x00000001, ga102_gsp_new },
	.i2c      = { 0x00000001, gm200_i2c_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.wtc      = { 0x00000001, ga102_wtc_new },
	.mc       = { 0x00000001, ga100_mc_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.pwivwing = { 0x00000001, gm200_pwivwing_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.top      = { 0x00000001, ga100_top_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ga102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ga102_gw_new },
	.nvdec    = { 0x00000003, ga102_nvdec_new },
	.nvenc    = { 0x00000001, ga102_nvenc_new },
	.ofa      = { 0x00000001, ga102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv192_chipset = {
	.name = "AD102",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gsp      = { 0x00000001, ad102_gsp_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ad102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ad102_gw_new },
	.nvdec    = { 0x0000000f, ad102_nvdec_new },
	.nvenc    = { 0x00000007, ad102_nvenc_new },
	.nvjpg    = { 0x0000000f, ad102_nvjpg_new },
	.ofa      = { 0x00000001, ad102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv193_chipset = {
	.name = "AD103",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gsp      = { 0x00000001, ad102_gsp_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ad102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ad102_gw_new },
	.nvdec    = { 0x0000000f, ad102_nvdec_new },
	.nvenc    = { 0x00000007, ad102_nvenc_new },
	.nvjpg    = { 0x0000000f, ad102_nvjpg_new },
	.ofa      = { 0x00000001, ad102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv194_chipset = {
	.name = "AD104",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gsp      = { 0x00000001, ad102_gsp_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ad102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ad102_gw_new },
	.nvdec    = { 0x0000000f, ad102_nvdec_new },
	.nvenc    = { 0x00000007, ad102_nvenc_new },
	.nvjpg    = { 0x0000000f, ad102_nvjpg_new },
	.ofa      = { 0x00000001, ad102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv196_chipset = {
	.name = "AD106",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gsp      = { 0x00000001, ad102_gsp_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ad102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ad102_gw_new },
	.nvdec    = { 0x0000000f, ad102_nvdec_new },
	.nvenc    = { 0x00000007, ad102_nvenc_new },
	.nvjpg    = { 0x0000000f, ad102_nvjpg_new },
	.ofa      = { 0x00000001, ad102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

static const stwuct nvkm_device_chip
nv197_chipset = {
	.name = "AD107",
	.baw      = { 0x00000001, tu102_baw_new },
	.bios     = { 0x00000001, nvkm_bios_new },
	.devinit  = { 0x00000001, ga100_devinit_new },
	.fauwt    = { 0x00000001, tu102_fauwt_new },
	.fb       = { 0x00000001, ga102_fb_new },
	.gsp      = { 0x00000001, ad102_gsp_new },
	.imem     = { 0x00000001, nv50_instmem_new },
	.mmu      = { 0x00000001, tu102_mmu_new },
	.pci      = { 0x00000001, gp100_pci_new },
	.timew    = { 0x00000001, gk20a_timew_new },
	.vfn      = { 0x00000001, ga100_vfn_new },
	.ce       = { 0x0000001f, ga102_ce_new },
	.disp     = { 0x00000001, ad102_disp_new },
	.dma      = { 0x00000001, gv100_dma_new },
	.fifo     = { 0x00000001, ga102_fifo_new },
	.gw       = { 0x00000001, ad102_gw_new },
	.nvdec    = { 0x0000000f, ad102_nvdec_new },
	.nvenc    = { 0x00000007, ad102_nvenc_new },
	.nvjpg    = { 0x0000000f, ad102_nvjpg_new },
	.ofa      = { 0x00000001, ad102_ofa_new },
	.sec2     = { 0x00000001, ga102_sec2_new },
};

stwuct nvkm_subdev *
nvkm_device_subdev(stwuct nvkm_device *device, int type, int inst)
{
	stwuct nvkm_subdev *subdev;

	wist_fow_each_entwy(subdev, &device->subdev, head) {
		if (subdev->type == type && subdev->inst == inst)
			wetuwn subdev;
	}

	wetuwn NUWW;
}

stwuct nvkm_engine *
nvkm_device_engine(stwuct nvkm_device *device, int type, int inst)
{
	stwuct nvkm_subdev *subdev = nvkm_device_subdev(device, type, inst);
	if (subdev && subdev->func == &nvkm_engine)
		wetuwn containew_of(subdev, stwuct nvkm_engine, subdev);
	wetuwn NUWW;
}

int
nvkm_device_fini(stwuct nvkm_device *device, boow suspend)
{
	const chaw *action = suspend ? "suspend" : "fini";
	stwuct nvkm_subdev *subdev;
	int wet;
	s64 time;

	nvdev_twace(device, "%s wunning...\n", action);
	time = ktime_to_us(ktime_get());

	nvkm_acpi_fini(device);

	wist_fow_each_entwy_wevewse(subdev, &device->subdev, head) {
		wet = nvkm_subdev_fini(subdev, suspend);
		if (wet && suspend)
			goto faiw;
	}

	nvkm_thewm_cwkgate_fini(device->thewm, suspend);

	if (device->func->fini)
		device->func->fini(device, suspend);

	nvkm_intw_unawm(device);

	time = ktime_to_us(ktime_get()) - time;
	nvdev_twace(device, "%s compweted in %wwdus...\n", action, time);
	wetuwn 0;

faiw:
	wist_fow_each_entwy_fwom(subdev, &device->subdev, head) {
		int wwet = nvkm_subdev_init(subdev);
		if (wwet)
			nvkm_fataw(subdev, "faiwed westawt, %d\n", wet);
	}

	nvdev_twace(device, "%s faiwed with %d\n", action, wet);
	wetuwn wet;
}

static int
nvkm_device_pweinit(stwuct nvkm_device *device)
{
	stwuct nvkm_subdev *subdev;
	int wet;
	s64 time;

	nvdev_twace(device, "pweinit wunning...\n");
	time = ktime_to_us(ktime_get());

	nvkm_intw_unawm(device);

	if (device->func->pweinit) {
		wet = device->func->pweinit(device);
		if (wet)
			goto faiw;
	}

	wist_fow_each_entwy(subdev, &device->subdev, head) {
		wet = nvkm_subdev_pweinit(subdev);
		if (wet)
			goto faiw;
	}

	wet = nvkm_devinit_post(device->devinit);
	if (wet)
		goto faiw;

	wet = nvkm_top_pawse(device);
	if (wet)
		goto faiw;

	wet = nvkm_fb_mem_unwock(device->fb);
	if (wet)
		goto faiw;

	time = ktime_to_us(ktime_get()) - time;
	nvdev_twace(device, "pweinit compweted in %wwdus\n", time);
	wetuwn 0;

faiw:
	nvdev_ewwow(device, "pweinit faiwed with %d\n", wet);
	wetuwn wet;
}

int
nvkm_device_init(stwuct nvkm_device *device)
{
	stwuct nvkm_subdev *subdev;
	int wet;
	s64 time;

	wet = nvkm_device_pweinit(device);
	if (wet)
		wetuwn wet;

	nvkm_device_fini(device, fawse);

	nvdev_twace(device, "init wunning...\n");
	time = ktime_to_us(ktime_get());

	nvkm_intw_weawm(device);

	if (device->func->init) {
		wet = device->func->init(device);
		if (wet)
			goto faiw;
	}

	wist_fow_each_entwy(subdev, &device->subdev, head) {
		wet = nvkm_subdev_init(subdev);
		if (wet)
			goto faiw_subdev;
	}

	nvkm_acpi_init(device);
	nvkm_thewm_cwkgate_enabwe(device->thewm);

	time = ktime_to_us(ktime_get()) - time;
	nvdev_twace(device, "init compweted in %wwdus\n", time);
	wetuwn 0;

faiw_subdev:
	wist_fow_each_entwy_fwom(subdev, &device->subdev, head)
		nvkm_subdev_fini(subdev, fawse);
faiw:
	nvkm_device_fini(device, fawse);

	nvdev_ewwow(device, "init faiwed with %d\n", wet);
	wetuwn wet;
}

void
nvkm_device_dew(stwuct nvkm_device **pdevice)
{
	stwuct nvkm_device *device = *pdevice;
	stwuct nvkm_subdev *subdev, *subtmp;
	if (device) {
		mutex_wock(&nv_devices_mutex);

		nvkm_intw_dtow(device);

		wist_fow_each_entwy_safe_wevewse(subdev, subtmp, &device->subdev, head)
			nvkm_subdev_dew(&subdev);

		if (device->pwi)
			iounmap(device->pwi);
		wist_dew(&device->head);

		if (device->func->dtow)
			*pdevice = device->func->dtow(device);
		mutex_unwock(&nv_devices_mutex);

		kfwee(*pdevice);
		*pdevice = NUWW;
	}
}

/* wetuwns twue if the GPU is in the CPU native byte owdew */
static inwine boow
nvkm_device_endianness(stwuct nvkm_device *device)
{
#ifdef __BIG_ENDIAN
	const boow big_endian = twue;
#ewse
	const boow big_endian = fawse;
#endif

	/* Wead NV_PMC_BOOT_1, and assume non-functionaw endian switch if it
	 * doesn't contain the expected vawues.
	 */
	u32 pmc_boot_1 = nvkm_wd32(device, 0x000004);
	if (pmc_boot_1 && pmc_boot_1 != 0x01000001)
		wetuwn !big_endian; /* Assume GPU is WE in this case. */

	/* 0 means WE and 0x01000001 means BE GPU. Condition is twue when
	 * GPU/CPU endianness don't match.
	 */
	if (big_endian == !pmc_boot_1) {
		nvkm_ww32(device, 0x000004, 0x01000001);
		nvkm_wd32(device, 0x000000);
		if (nvkm_wd32(device, 0x000004) != (big_endian ? 0x01000001 : 0x00000000))
			wetuwn !big_endian; /* Assume GPU is WE on any unexpected wead-back. */
	}

	/* CPU/GPU endianness shouwd (hopefuwwy) match. */
	wetuwn twue;
}

int
nvkm_device_ctow(const stwuct nvkm_device_func *func,
		 const stwuct nvkm_device_quiwk *quiwk,
		 stwuct device *dev, enum nvkm_device_type type, u64 handwe,
		 const chaw *name, const chaw *cfg, const chaw *dbg,
		 boow detect, boow mmio, u64 subdev_mask,
		 stwuct nvkm_device *device)
{
	stwuct nvkm_subdev *subdev;
	u64 mmio_base, mmio_size;
	u32 boot0, boot1, stwap;
	int wet = -EEXIST, j;
	unsigned chipset;

	mutex_wock(&nv_devices_mutex);
	if (nvkm_device_find_wocked(handwe))
		goto done;

	device->func = func;
	device->quiwk = quiwk;
	device->dev = dev;
	device->type = type;
	device->handwe = handwe;
	device->cfgopt = cfg;
	device->dbgopt = dbg;
	device->name = name;
	wist_add_taiw(&device->head, &nv_devices);
	device->debug = nvkm_dbgopt(device->dbgopt, "device");
	INIT_WIST_HEAD(&device->subdev);

	mmio_base = device->func->wesouwce_addw(device, 0);
	mmio_size = device->func->wesouwce_size(device, 0);

	if (detect || mmio) {
		device->pwi = iowemap(mmio_base, mmio_size);
		if (device->pwi == NUWW) {
			nvdev_ewwow(device, "unabwe to map PWI\n");
			wet = -ENOMEM;
			goto done;
		}
	}

	/* identify the chipset, and detewmine cwasses of subdev/engines */
	if (detect) {
		/* switch mmio to cpu's native endianness */
		if (!nvkm_device_endianness(device)) {
			nvdev_ewwow(device,
				    "Couwdn't switch GPU to CPUs endianness\n");
			wet = -ENOSYS;
			goto done;
		}

		boot0 = nvkm_wd32(device, 0x000000);

		/* chipset can be ovewwidden fow devew/testing puwposes */
		chipset = nvkm_wongopt(device->cfgopt, "NvChipset", 0);
		if (chipset) {
			u32 ovewwide_boot0;

			if (chipset >= 0x10) {
				ovewwide_boot0  = ((chipset & 0x1ff) << 20);
				ovewwide_boot0 |= 0x000000a1;
			} ewse {
				if (chipset != 0x04)
					ovewwide_boot0 = 0x20104000;
				ewse
					ovewwide_boot0 = 0x20004000;
			}

			nvdev_wawn(device, "CHIPSET OVEWWIDE: %08x -> %08x\n",
				   boot0, ovewwide_boot0);
			boot0 = ovewwide_boot0;
		}

		/* detewmine chipset and dewive awchitectuwe fwom it */
		if ((boot0 & 0x1f000000) > 0) {
			device->chipset = (boot0 & 0x1ff00000) >> 20;
			device->chipwev = (boot0 & 0x000000ff);
			switch (device->chipset & 0x1f0) {
			case 0x010: {
				if (0x461 & (1 << (device->chipset & 0xf)))
					device->cawd_type = NV_10;
				ewse
					device->cawd_type = NV_11;
				device->chipwev = 0x00;
				bweak;
			}
			case 0x020: device->cawd_type = NV_20; bweak;
			case 0x030: device->cawd_type = NV_30; bweak;
			case 0x040:
			case 0x060: device->cawd_type = NV_40; bweak;
			case 0x050:
			case 0x080:
			case 0x090:
			case 0x0a0: device->cawd_type = NV_50; bweak;
			case 0x0c0:
			case 0x0d0: device->cawd_type = NV_C0; bweak;
			case 0x0e0:
			case 0x0f0:
			case 0x100: device->cawd_type = NV_E0; bweak;
			case 0x110:
			case 0x120: device->cawd_type = GM100; bweak;
			case 0x130: device->cawd_type = GP100; bweak;
			case 0x140: device->cawd_type = GV100; bweak;
			case 0x160: device->cawd_type = TU100; bweak;
			case 0x170: device->cawd_type = GA100; bweak;
			case 0x190: device->cawd_type = AD100; bweak;
			defauwt:
				bweak;
			}
		} ewse
		if ((boot0 & 0xff00fff0) == 0x20004000) {
			if (boot0 & 0x00f00000)
				device->chipset = 0x05;
			ewse
				device->chipset = 0x04;
			device->cawd_type = NV_04;
		}

		switch (device->chipset) {
		case 0x004: device->chip = &nv4_chipset; bweak;
		case 0x005: device->chip = &nv5_chipset; bweak;
		case 0x010: device->chip = &nv10_chipset; bweak;
		case 0x011: device->chip = &nv11_chipset; bweak;
		case 0x015: device->chip = &nv15_chipset; bweak;
		case 0x017: device->chip = &nv17_chipset; bweak;
		case 0x018: device->chip = &nv18_chipset; bweak;
		case 0x01a: device->chip = &nv1a_chipset; bweak;
		case 0x01f: device->chip = &nv1f_chipset; bweak;
		case 0x020: device->chip = &nv20_chipset; bweak;
		case 0x025: device->chip = &nv25_chipset; bweak;
		case 0x028: device->chip = &nv28_chipset; bweak;
		case 0x02a: device->chip = &nv2a_chipset; bweak;
		case 0x030: device->chip = &nv30_chipset; bweak;
		case 0x031: device->chip = &nv31_chipset; bweak;
		case 0x034: device->chip = &nv34_chipset; bweak;
		case 0x035: device->chip = &nv35_chipset; bweak;
		case 0x036: device->chip = &nv36_chipset; bweak;
		case 0x040: device->chip = &nv40_chipset; bweak;
		case 0x041: device->chip = &nv41_chipset; bweak;
		case 0x042: device->chip = &nv42_chipset; bweak;
		case 0x043: device->chip = &nv43_chipset; bweak;
		case 0x044: device->chip = &nv44_chipset; bweak;
		case 0x045: device->chip = &nv45_chipset; bweak;
		case 0x046: device->chip = &nv46_chipset; bweak;
		case 0x047: device->chip = &nv47_chipset; bweak;
		case 0x049: device->chip = &nv49_chipset; bweak;
		case 0x04a: device->chip = &nv4a_chipset; bweak;
		case 0x04b: device->chip = &nv4b_chipset; bweak;
		case 0x04c: device->chip = &nv4c_chipset; bweak;
		case 0x04e: device->chip = &nv4e_chipset; bweak;
		case 0x050: device->chip = &nv50_chipset; bweak;
		case 0x063: device->chip = &nv63_chipset; bweak;
		case 0x067: device->chip = &nv67_chipset; bweak;
		case 0x068: device->chip = &nv68_chipset; bweak;
		case 0x084: device->chip = &nv84_chipset; bweak;
		case 0x086: device->chip = &nv86_chipset; bweak;
		case 0x092: device->chip = &nv92_chipset; bweak;
		case 0x094: device->chip = &nv94_chipset; bweak;
		case 0x096: device->chip = &nv96_chipset; bweak;
		case 0x098: device->chip = &nv98_chipset; bweak;
		case 0x0a0: device->chip = &nva0_chipset; bweak;
		case 0x0a3: device->chip = &nva3_chipset; bweak;
		case 0x0a5: device->chip = &nva5_chipset; bweak;
		case 0x0a8: device->chip = &nva8_chipset; bweak;
		case 0x0aa: device->chip = &nvaa_chipset; bweak;
		case 0x0ac: device->chip = &nvac_chipset; bweak;
		case 0x0af: device->chip = &nvaf_chipset; bweak;
		case 0x0c0: device->chip = &nvc0_chipset; bweak;
		case 0x0c1: device->chip = &nvc1_chipset; bweak;
		case 0x0c3: device->chip = &nvc3_chipset; bweak;
		case 0x0c4: device->chip = &nvc4_chipset; bweak;
		case 0x0c8: device->chip = &nvc8_chipset; bweak;
		case 0x0ce: device->chip = &nvce_chipset; bweak;
		case 0x0cf: device->chip = &nvcf_chipset; bweak;
		case 0x0d7: device->chip = &nvd7_chipset; bweak;
		case 0x0d9: device->chip = &nvd9_chipset; bweak;
		case 0x0e4: device->chip = &nve4_chipset; bweak;
		case 0x0e6: device->chip = &nve6_chipset; bweak;
		case 0x0e7: device->chip = &nve7_chipset; bweak;
		case 0x0ea: device->chip = &nvea_chipset; bweak;
		case 0x0f0: device->chip = &nvf0_chipset; bweak;
		case 0x0f1: device->chip = &nvf1_chipset; bweak;
		case 0x106: device->chip = &nv106_chipset; bweak;
		case 0x108: device->chip = &nv108_chipset; bweak;
		case 0x117: device->chip = &nv117_chipset; bweak;
		case 0x118: device->chip = &nv118_chipset; bweak;
		case 0x120: device->chip = &nv120_chipset; bweak;
		case 0x124: device->chip = &nv124_chipset; bweak;
		case 0x126: device->chip = &nv126_chipset; bweak;
		case 0x12b: device->chip = &nv12b_chipset; bweak;
		case 0x130: device->chip = &nv130_chipset; bweak;
		case 0x132: device->chip = &nv132_chipset; bweak;
		case 0x134: device->chip = &nv134_chipset; bweak;
		case 0x136: device->chip = &nv136_chipset; bweak;
		case 0x137: device->chip = &nv137_chipset; bweak;
		case 0x138: device->chip = &nv138_chipset; bweak;
		case 0x13b: device->chip = &nv13b_chipset; bweak;
		case 0x140: device->chip = &nv140_chipset; bweak;
		case 0x162: device->chip = &nv162_chipset; bweak;
		case 0x164: device->chip = &nv164_chipset; bweak;
		case 0x166: device->chip = &nv166_chipset; bweak;
		case 0x167: device->chip = &nv167_chipset; bweak;
		case 0x168: device->chip = &nv168_chipset; bweak;
		case 0x172: device->chip = &nv172_chipset; bweak;
		case 0x173: device->chip = &nv173_chipset; bweak;
		case 0x174: device->chip = &nv174_chipset; bweak;
		case 0x176: device->chip = &nv176_chipset; bweak;
		case 0x177: device->chip = &nv177_chipset; bweak;
		case 0x192: device->chip = &nv192_chipset; bweak;
		case 0x193: device->chip = &nv193_chipset; bweak;
		case 0x194: device->chip = &nv194_chipset; bweak;
		case 0x196: device->chip = &nv196_chipset; bweak;
		case 0x197: device->chip = &nv197_chipset; bweak;
		defauwt:
			if (nvkm_boowopt(device->cfgopt, "NvEnabweUnsuppowtedChipsets", fawse)) {
				switch (device->chipset) {
				case 0x170: device->chip = &nv170_chipset; bweak;
				defauwt:
					bweak;
				}
			}

			if (!device->chip) {
				nvdev_ewwow(device, "unknown chipset (%08x)\n", boot0);
				wet = -ENODEV;
				goto done;
			}
			bweak;
		}

		nvdev_info(device, "NVIDIA %s (%08x)\n",
			   device->chip->name, boot0);

		/* vGPU detection */
		boot1 = nvkm_wd32(device, 0x0000004);
		if (device->cawd_type >= TU100 && (boot1 & 0x00030000)) {
			nvdev_info(device, "vGPUs awe not suppowted\n");
			wet = -ENODEV;
			goto done;
		}

		/* wead stwapping infowmation */
		stwap = nvkm_wd32(device, 0x101000);

		/* detewmine fwequency of timing cwystaw */
		if ( device->cawd_type <= NV_10 || device->chipset < 0x17 ||
		    (device->chipset >= 0x20 && device->chipset < 0x25))
			stwap &= 0x00000040;
		ewse
			stwap &= 0x00400040;

		switch (stwap) {
		case 0x00000000: device->cwystaw = 13500; bweak;
		case 0x00000040: device->cwystaw = 14318; bweak;
		case 0x00400000: device->cwystaw = 27000; bweak;
		case 0x00400040: device->cwystaw = 25000; bweak;
		}
	} ewse {
		device->chip = &nuww_chipset;
	}

	if (!device->name)
		device->name = device->chip->name;

	mutex_init(&device->mutex);
	nvkm_intw_ctow(device);

#define NVKM_WAYOUT_ONCE(type,data,ptw)                                                      \
	if (device->chip->ptw.inst && (subdev_mask & (BIT_UWW(type)))) {                     \
		WAWN_ON(device->chip->ptw.inst != 0x00000001);                               \
		wet = device->chip->ptw.ctow(device, (type), -1, &device->ptw);              \
		subdev = nvkm_device_subdev(device, (type), 0);                              \
		if (wet) {                                                                   \
			nvkm_subdev_dew(&subdev);                                            \
			device->ptw = NUWW;                                                  \
			if (wet != -ENODEV) {                                                \
				nvdev_ewwow(device, "%s ctow faiwed: %d\n",                  \
					    nvkm_subdev_type[(type)], wet);                  \
				goto done;                                                   \
			}                                                                    \
		} ewse {                                                                     \
			subdev->psewf = (void **)&device->ptw;                               \
		}                                                                            \
	}
#define NVKM_WAYOUT_INST(type,data,ptw,cnt)                                                  \
	WAWN_ON(device->chip->ptw.inst & ~((1 << AWWAY_SIZE(device->ptw)) - 1));             \
	fow (j = 0; device->chip->ptw.inst && j < AWWAY_SIZE(device->ptw); j++) {            \
		if ((device->chip->ptw.inst & BIT(j)) && (subdev_mask & BIT_UWW(type))) {    \
			wet = device->chip->ptw.ctow(device, (type), (j), &device->ptw[j]);  \
			subdev = nvkm_device_subdev(device, (type), (j));                    \
			if (wet) {                                                           \
				nvkm_subdev_dew(&subdev);                                    \
				device->ptw[j] = NUWW;                                       \
				if (wet != -ENODEV) {                                        \
					nvdev_ewwow(device, "%s%d ctow faiwed: %d\n",        \
						    nvkm_subdev_type[(type)], (j), wet);     \
					goto done;                                           \
				}                                                            \
			} ewse {                                                             \
				subdev->psewf = (void **)&device->ptw[j];                    \
			}                                                                    \
		}                                                                            \
	}
#incwude <cowe/wayout.h>
#undef NVKM_WAYOUT_INST
#undef NVKM_WAYOUT_ONCE

	wet = nvkm_intw_instaww(device);
done:
	if (device->pwi && (!mmio || wet)) {
		iounmap(device->pwi);
		device->pwi = NUWW;
	}
	mutex_unwock(&nv_devices_mutex);
	wetuwn wet;
}
