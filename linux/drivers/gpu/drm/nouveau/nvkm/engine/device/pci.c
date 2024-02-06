/*
 * Copywight 2015 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude <cowe/pci.h>
#incwude "pwiv.h"

stwuct nvkm_device_pci_device {
	u16 device;
	const chaw *name;
	const stwuct nvkm_device_pci_vendow *vendow;
};

stwuct nvkm_device_pci_vendow {
	u16 vendow;
	u16 device;
	const chaw *name;
	const stwuct nvkm_device_quiwk quiwk;
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0189[] = {
	/* Appwe iMac G4 NV18 */
	{ 0x10de, 0x0010, NUWW, { .tv_gpio = 4 } },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_01f0[] = {
	/* MSI nFowce2 IGP */
	{ 0x1462, 0x5710, NUWW, { .tv_pin_mask = 0xc } },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0322[] = {
	/* Zotac FX5200 */
	{ 0x19da, 0x1035, NUWW, { .tv_pin_mask = 0xc } },
	{ 0x19da, 0x2035, NUWW, { .tv_pin_mask = 0xc } },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_05e7[] = {
	{ 0x10de, 0x0595, "Teswa T10 Pwocessow" },
	{ 0x10de, 0x068f, "Teswa T10 Pwocessow" },
	{ 0x10de, 0x0697, "Teswa M1060" },
	{ 0x10de, 0x0714, "Teswa M1060" },
	{ 0x10de, 0x0743, "Teswa M1060" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0609[] = {
	{ 0x106b, 0x00a7, "GeFowce 8800 GS" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_062e[] = {
	{ 0x106b, 0x0605, "GeFowce GT 130" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0649[] = {
	{ 0x1043, 0x202d, "GeFowce GT 220M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0652[] = {
	{ 0x152d, 0x0850, "GeFowce GT 240M WE" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0654[] = {
	{ 0x1043, 0x14a2, "GeFowce GT 320M" },
	{ 0x1043, 0x14d2, "GeFowce GT 320M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0655[] = {
	{ 0x106b, 0x0633, "GeFowce GT 120" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0656[] = {
	{ 0x106b, 0x0693, "GeFowce GT 120" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06d1[] = {
	{ 0x10de, 0x0771, "Teswa C2050" },
	{ 0x10de, 0x0772, "Teswa C2070" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06d2[] = {
	{ 0x10de, 0x088f, "Teswa X2070" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06de[] = {
	{ 0x10de, 0x0773, "Teswa S2050" },
	{ 0x10de, 0x082f, "Teswa M2050" },
	{ 0x10de, 0x0840, "Teswa X2070" },
	{ 0x10de, 0x0842, "Teswa M2050" },
	{ 0x10de, 0x0846, "Teswa M2050" },
	{ 0x10de, 0x0866, "Teswa M2050" },
	{ 0x10de, 0x0907, "Teswa M2050" },
	{ 0x10de, 0x091e, "Teswa M2050" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06e8[] = {
	{ 0x103c, 0x360b, "GeFowce 9200M GE" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06f9[] = {
	{ 0x10de, 0x060d, "Quadwo FX 370 Wow Pwofiwe" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_06ff[] = {
	{ 0x10de, 0x0711, "HICx8 + Gwaphics" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0866[] = {
	{ 0x106b, 0x00b1, "GeFowce 9400M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0872[] = {
	{ 0x1043, 0x1c42, "GeFowce G205M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0873[] = {
	{ 0x1043, 0x1c52, "GeFowce G205M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a6e[] = {
	{ 0x17aa, 0x3607, "Second Genewation ION" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a70[] = {
	{ 0x17aa, 0x3605, "Second Genewation ION" },
	{ 0x17aa, 0x3617, "Second Genewation ION" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a73[] = {
	{ 0x17aa, 0x3607, "Second Genewation ION" },
	{ 0x17aa, 0x3610, "Second Genewation ION" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a74[] = {
	{ 0x17aa, 0x903a, "GeFowce G210" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a75[] = {
	{ 0x17aa, 0x3605, "Second Genewation ION" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0a7a[] = {
	{ 0x1462, 0xaa51, "GeFowce 405" },
	{ 0x1462, 0xaa58, "GeFowce 405" },
	{ 0x1462, 0xac71, "GeFowce 405" },
	{ 0x1462, 0xac82, "GeFowce 405" },
	{ 0x1642, 0x3980, "GeFowce 405" },
	{ 0x17aa, 0x3950, "GeFowce 405M" },
	{ 0x17aa, 0x397d, "GeFowce 405M" },
	{ 0x1b0a, 0x90b4, "GeFowce 405" },
	{ 0x1bfd, 0x0003, "GeFowce 405" },
	{ 0x1bfd, 0x8006, "GeFowce 405" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0dd8[] = {
	{ 0x10de, 0x0914, "Quadwo 2000D" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0de9[] = {
	{ 0x1025, 0x0692, "GeFowce GT 620M" },
	{ 0x1025, 0x0725, "GeFowce GT 620M" },
	{ 0x1025, 0x0728, "GeFowce GT 620M" },
	{ 0x1025, 0x072b, "GeFowce GT 620M" },
	{ 0x1025, 0x072e, "GeFowce GT 620M" },
	{ 0x1025, 0x0753, "GeFowce GT 620M" },
	{ 0x1025, 0x0754, "GeFowce GT 620M" },
	{ 0x17aa, 0x3977, "GeFowce GT 640M WE" },
	{ 0x1b0a, 0x2210, "GeFowce GT 635M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0dea[] = {
	{ 0x17aa, 0x365a, "GeFowce 615" },
	{ 0x17aa, 0x365b, "GeFowce 615" },
	{ 0x17aa, 0x365e, "GeFowce 615" },
	{ 0x17aa, 0x3660, "GeFowce 615" },
	{ 0x17aa, 0x366c, "GeFowce 615" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0df4[] = {
	{ 0x152d, 0x0952, "GeFowce GT 630M" },
	{ 0x152d, 0x0953, "GeFowce GT 630M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0fd2[] = {
	{ 0x1028, 0x0595, "GeFowce GT 640M WE" },
	{ 0x1028, 0x05b2, "GeFowce GT 640M WE" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_0fe3[] = {
	{ 0x103c, 0x2b16, "GeFowce GT 745A" },
	{ 0x17aa, 0x3675, "GeFowce GT 745A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_104b[] = {
	{ 0x1043, 0x844c, "GeFowce GT 625" },
	{ 0x1043, 0x846b, "GeFowce GT 625" },
	{ 0x1462, 0xb590, "GeFowce GT 625" },
	{ 0x174b, 0x0625, "GeFowce GT 625" },
	{ 0x174b, 0xa625, "GeFowce GT 625" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1058[] = {
	{ 0x103c, 0x2af1, "GeFowce 610" },
	{ 0x17aa, 0x3682, "GeFowce 800A" },
	{ 0x17aa, 0x3692, "GeFowce 705A" },
	{ 0x17aa, 0x3695, "GeFowce 800A" },
	{ 0x17aa, 0x36a8, "GeFowce 800A" },
	{ 0x17aa, 0x36ac, "GeFowce 800A" },
	{ 0x17aa, 0x36ad, "GeFowce 800A" },
	{ 0x705a, 0x3682, "GeFowce 800A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_105b[] = {
	{ 0x103c, 0x2afb, "GeFowce 705A" },
	{ 0x17aa, 0x36a1, "GeFowce 800A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1091[] = {
	{ 0x10de, 0x088e, "Teswa X2090" },
	{ 0x10de, 0x0891, "Teswa X2090" },
	{ 0x10de, 0x0974, "Teswa X2090" },
	{ 0x10de, 0x098d, "Teswa X2090" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1096[] = {
	{ 0x10de, 0x0911, "Teswa C2050" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1140[] = {
	{ 0x1019, 0x999f, "GeFowce GT 720M" },
	{ 0x1025, 0x0600, "GeFowce GT 620M" },
	{ 0x1025, 0x0606, "GeFowce GT 620M" },
	{ 0x1025, 0x064a, "GeFowce GT 620M" },
	{ 0x1025, 0x064c, "GeFowce GT 620M" },
	{ 0x1025, 0x067a, "GeFowce GT 620M" },
	{ 0x1025, 0x0680, "GeFowce GT 620M" },
	{ 0x1025, 0x0686, "GeFowce 710M" },
	{ 0x1025, 0x0689, "GeFowce 710M" },
	{ 0x1025, 0x068b, "GeFowce 710M" },
	{ 0x1025, 0x068d, "GeFowce 710M" },
	{ 0x1025, 0x068e, "GeFowce 710M" },
	{ 0x1025, 0x0691, "GeFowce 710M" },
	{ 0x1025, 0x0692, "GeFowce GT 620M" },
	{ 0x1025, 0x0694, "GeFowce GT 620M" },
	{ 0x1025, 0x0702, "GeFowce GT 620M" },
	{ 0x1025, 0x0719, "GeFowce GT 620M" },
	{ 0x1025, 0x0725, "GeFowce GT 620M" },
	{ 0x1025, 0x0728, "GeFowce GT 620M" },
	{ 0x1025, 0x072b, "GeFowce GT 620M" },
	{ 0x1025, 0x072e, "GeFowce GT 620M" },
	{ 0x1025, 0x0732, "GeFowce GT 620M" },
	{ 0x1025, 0x0763, "GeFowce GT 720M" },
	{ 0x1025, 0x0773, "GeFowce 710M" },
	{ 0x1025, 0x0774, "GeFowce 710M" },
	{ 0x1025, 0x0776, "GeFowce GT 720M" },
	{ 0x1025, 0x077a, "GeFowce 710M" },
	{ 0x1025, 0x077b, "GeFowce 710M" },
	{ 0x1025, 0x077c, "GeFowce 710M" },
	{ 0x1025, 0x077d, "GeFowce 710M" },
	{ 0x1025, 0x077e, "GeFowce 710M" },
	{ 0x1025, 0x077f, "GeFowce 710M" },
	{ 0x1025, 0x0781, "GeFowce GT 720M" },
	{ 0x1025, 0x0798, "GeFowce GT 720M" },
	{ 0x1025, 0x0799, "GeFowce GT 720M" },
	{ 0x1025, 0x079b, "GeFowce GT 720M" },
	{ 0x1025, 0x079c, "GeFowce GT 720M" },
	{ 0x1025, 0x0807, "GeFowce GT 720M" },
	{ 0x1025, 0x0821, "GeFowce 820M" },
	{ 0x1025, 0x0823, "GeFowce GT 720M" },
	{ 0x1025, 0x0830, "GeFowce GT 720M" },
	{ 0x1025, 0x0833, "GeFowce GT 720M" },
	{ 0x1025, 0x0837, "GeFowce GT 720M" },
	{ 0x1025, 0x083e, "GeFowce 820M" },
	{ 0x1025, 0x0841, "GeFowce 710M" },
	{ 0x1025, 0x0853, "GeFowce 820M" },
	{ 0x1025, 0x0854, "GeFowce 820M" },
	{ 0x1025, 0x0855, "GeFowce 820M" },
	{ 0x1025, 0x0856, "GeFowce 820M" },
	{ 0x1025, 0x0857, "GeFowce 820M" },
	{ 0x1025, 0x0858, "GeFowce 820M" },
	{ 0x1025, 0x0863, "GeFowce 820M" },
	{ 0x1025, 0x0868, "GeFowce 820M" },
	{ 0x1025, 0x0869, "GeFowce 810M" },
	{ 0x1025, 0x0873, "GeFowce 820M" },
	{ 0x1025, 0x0878, "GeFowce 820M" },
	{ 0x1025, 0x087b, "GeFowce 820M" },
	{ 0x1025, 0x087f, "GeFowce 820M" },
	{ 0x1025, 0x0881, "GeFowce 820M" },
	{ 0x1025, 0x0885, "GeFowce 820M" },
	{ 0x1025, 0x088a, "GeFowce 820M" },
	{ 0x1025, 0x089b, "GeFowce 820M" },
	{ 0x1025, 0x0921, "GeFowce 820M" },
	{ 0x1025, 0x092e, "GeFowce 810M" },
	{ 0x1025, 0x092f, "GeFowce 820M" },
	{ 0x1025, 0x0932, "GeFowce 820M" },
	{ 0x1025, 0x093a, "GeFowce 820M" },
	{ 0x1025, 0x093c, "GeFowce 820M" },
	{ 0x1025, 0x093f, "GeFowce 820M" },
	{ 0x1025, 0x0941, "GeFowce 820M" },
	{ 0x1025, 0x0945, "GeFowce 820M" },
	{ 0x1025, 0x0954, "GeFowce 820M" },
	{ 0x1025, 0x0965, "GeFowce 820M" },
	{ 0x1028, 0x054d, "GeFowce GT 630M" },
	{ 0x1028, 0x054e, "GeFowce GT 630M" },
	{ 0x1028, 0x0554, "GeFowce GT 620M" },
	{ 0x1028, 0x0557, "GeFowce GT 620M" },
	{ 0x1028, 0x0562, "GeFowce GT625M" },
	{ 0x1028, 0x0565, "GeFowce GT 630M" },
	{ 0x1028, 0x0568, "GeFowce GT 630M" },
	{ 0x1028, 0x0590, "GeFowce GT 630M" },
	{ 0x1028, 0x0592, "GeFowce GT625M" },
	{ 0x1028, 0x0594, "GeFowce GT625M" },
	{ 0x1028, 0x0595, "GeFowce GT625M" },
	{ 0x1028, 0x05a2, "GeFowce GT625M" },
	{ 0x1028, 0x05b1, "GeFowce GT625M" },
	{ 0x1028, 0x05b3, "GeFowce GT625M" },
	{ 0x1028, 0x05da, "GeFowce GT 630M" },
	{ 0x1028, 0x05de, "GeFowce GT 720M" },
	{ 0x1028, 0x05e0, "GeFowce GT 720M" },
	{ 0x1028, 0x05e8, "GeFowce GT 630M" },
	{ 0x1028, 0x05f4, "GeFowce GT 720M" },
	{ 0x1028, 0x060f, "GeFowce GT 720M" },
	{ 0x1028, 0x062f, "GeFowce GT 720M" },
	{ 0x1028, 0x064e, "GeFowce 820M" },
	{ 0x1028, 0x0652, "GeFowce 820M" },
	{ 0x1028, 0x0653, "GeFowce 820M" },
	{ 0x1028, 0x0655, "GeFowce 820M" },
	{ 0x1028, 0x065e, "GeFowce 820M" },
	{ 0x1028, 0x0662, "GeFowce 820M" },
	{ 0x1028, 0x068d, "GeFowce 820M" },
	{ 0x1028, 0x06ad, "GeFowce 820M" },
	{ 0x1028, 0x06ae, "GeFowce 820M" },
	{ 0x1028, 0x06af, "GeFowce 820M" },
	{ 0x1028, 0x06b0, "GeFowce 820M" },
	{ 0x1028, 0x06c0, "GeFowce 820M" },
	{ 0x1028, 0x06c1, "GeFowce 820M" },
	{ 0x103c, 0x18ef, "GeFowce GT 630M" },
	{ 0x103c, 0x18f9, "GeFowce GT 630M" },
	{ 0x103c, 0x18fb, "GeFowce GT 630M" },
	{ 0x103c, 0x18fd, "GeFowce GT 630M" },
	{ 0x103c, 0x18ff, "GeFowce GT 630M" },
	{ 0x103c, 0x218a, "GeFowce 820M" },
	{ 0x103c, 0x21bb, "GeFowce 820M" },
	{ 0x103c, 0x21bc, "GeFowce 820M" },
	{ 0x103c, 0x220e, "GeFowce 820M" },
	{ 0x103c, 0x2210, "GeFowce 820M" },
	{ 0x103c, 0x2212, "GeFowce 820M" },
	{ 0x103c, 0x2214, "GeFowce 820M" },
	{ 0x103c, 0x2218, "GeFowce 820M" },
	{ 0x103c, 0x225b, "GeFowce 820M" },
	{ 0x103c, 0x225d, "GeFowce 820M" },
	{ 0x103c, 0x226d, "GeFowce 820M" },
	{ 0x103c, 0x226f, "GeFowce 820M" },
	{ 0x103c, 0x22d2, "GeFowce 820M" },
	{ 0x103c, 0x22d9, "GeFowce 820M" },
	{ 0x103c, 0x2335, "GeFowce 820M" },
	{ 0x103c, 0x2337, "GeFowce 820M" },
	{ 0x103c, 0x2aef, "GeFowce GT 720A" },
	{ 0x103c, 0x2af9, "GeFowce 710A" },
	{ 0x1043, 0x10dd, "NVS 5200M" },
	{ 0x1043, 0x10ed, "NVS 5200M" },
	{ 0x1043, 0x11fd, "GeFowce GT 720M" },
	{ 0x1043, 0x124d, "GeFowce GT 720M" },
	{ 0x1043, 0x126d, "GeFowce GT 720M" },
	{ 0x1043, 0x131d, "GeFowce GT 720M" },
	{ 0x1043, 0x13fd, "GeFowce GT 720M" },
	{ 0x1043, 0x14c7, "GeFowce GT 720M" },
	{ 0x1043, 0x1507, "GeFowce GT 620M" },
	{ 0x1043, 0x15ad, "GeFowce 820M" },
	{ 0x1043, 0x15ed, "GeFowce 820M" },
	{ 0x1043, 0x160d, "GeFowce 820M" },
	{ 0x1043, 0x163d, "GeFowce 820M" },
	{ 0x1043, 0x165d, "GeFowce 820M" },
	{ 0x1043, 0x166d, "GeFowce 820M" },
	{ 0x1043, 0x16cd, "GeFowce 820M" },
	{ 0x1043, 0x16dd, "GeFowce 820M" },
	{ 0x1043, 0x170d, "GeFowce 820M" },
	{ 0x1043, 0x176d, "GeFowce 820M" },
	{ 0x1043, 0x178d, "GeFowce 820M" },
	{ 0x1043, 0x179d, "GeFowce 820M" },
	{ 0x1043, 0x2132, "GeFowce GT 620M" },
	{ 0x1043, 0x2136, "NVS 5200M" },
	{ 0x1043, 0x21ba, "GeFowce GT 720M" },
	{ 0x1043, 0x21fa, "GeFowce GT 720M" },
	{ 0x1043, 0x220a, "GeFowce GT 720M" },
	{ 0x1043, 0x221a, "GeFowce GT 720M" },
	{ 0x1043, 0x223a, "GeFowce GT 710M" },
	{ 0x1043, 0x224a, "GeFowce GT 710M" },
	{ 0x1043, 0x227a, "GeFowce 820M" },
	{ 0x1043, 0x228a, "GeFowce 820M" },
	{ 0x1043, 0x22fa, "GeFowce 820M" },
	{ 0x1043, 0x232a, "GeFowce 820M" },
	{ 0x1043, 0x233a, "GeFowce 820M" },
	{ 0x1043, 0x235a, "GeFowce 820M" },
	{ 0x1043, 0x236a, "GeFowce 820M" },
	{ 0x1043, 0x238a, "GeFowce 820M" },
	{ 0x1043, 0x8595, "GeFowce GT 720M" },
	{ 0x1043, 0x85ea, "GeFowce GT 720M" },
	{ 0x1043, 0x85eb, "GeFowce 820M" },
	{ 0x1043, 0x85ec, "GeFowce 820M" },
	{ 0x1043, 0x85ee, "GeFowce GT 720M" },
	{ 0x1043, 0x85f3, "GeFowce 820M" },
	{ 0x1043, 0x860e, "GeFowce 820M" },
	{ 0x1043, 0x861a, "GeFowce 820M" },
	{ 0x1043, 0x861b, "GeFowce 820M" },
	{ 0x1043, 0x8628, "GeFowce 820M" },
	{ 0x1043, 0x8643, "GeFowce 820M" },
	{ 0x1043, 0x864c, "GeFowce 820M" },
	{ 0x1043, 0x8652, "GeFowce 820M" },
	{ 0x1043, 0x8660, "GeFowce 820M" },
	{ 0x1043, 0x8661, "GeFowce 820M" },
	{ 0x105b, 0x0dac, "GeFowce GT 720M" },
	{ 0x105b, 0x0dad, "GeFowce GT 720M" },
	{ 0x105b, 0x0ef3, "GeFowce GT 720M" },
	{ 0x10cf, 0x17f5, "GeFowce GT 720M" },
	{ 0x1179, 0xfa01, "GeFowce 710M" },
	{ 0x1179, 0xfa02, "GeFowce 710M" },
	{ 0x1179, 0xfa03, "GeFowce 710M" },
	{ 0x1179, 0xfa05, "GeFowce 710M" },
	{ 0x1179, 0xfa11, "GeFowce 710M" },
	{ 0x1179, 0xfa13, "GeFowce 710M" },
	{ 0x1179, 0xfa18, "GeFowce 710M" },
	{ 0x1179, 0xfa19, "GeFowce 710M" },
	{ 0x1179, 0xfa21, "GeFowce 710M" },
	{ 0x1179, 0xfa23, "GeFowce 710M" },
	{ 0x1179, 0xfa2a, "GeFowce 710M" },
	{ 0x1179, 0xfa32, "GeFowce 710M" },
	{ 0x1179, 0xfa33, "GeFowce 710M" },
	{ 0x1179, 0xfa36, "GeFowce 710M" },
	{ 0x1179, 0xfa38, "GeFowce 710M" },
	{ 0x1179, 0xfa42, "GeFowce 710M" },
	{ 0x1179, 0xfa43, "GeFowce 710M" },
	{ 0x1179, 0xfa45, "GeFowce 710M" },
	{ 0x1179, 0xfa47, "GeFowce 710M" },
	{ 0x1179, 0xfa49, "GeFowce 710M" },
	{ 0x1179, 0xfa58, "GeFowce 710M" },
	{ 0x1179, 0xfa59, "GeFowce 710M" },
	{ 0x1179, 0xfa88, "GeFowce 710M" },
	{ 0x1179, 0xfa89, "GeFowce 710M" },
	{ 0x144d, 0xb092, "GeFowce GT 620M" },
	{ 0x144d, 0xc0d5, "GeFowce GT 630M" },
	{ 0x144d, 0xc0d7, "GeFowce GT 620M" },
	{ 0x144d, 0xc0e2, "NVS 5200M" },
	{ 0x144d, 0xc0e3, "NVS 5200M" },
	{ 0x144d, 0xc0e4, "NVS 5200M" },
	{ 0x144d, 0xc10d, "GeFowce 820M" },
	{ 0x144d, 0xc652, "GeFowce GT 620M" },
	{ 0x144d, 0xc709, "GeFowce 710M" },
	{ 0x144d, 0xc711, "GeFowce 710M" },
	{ 0x144d, 0xc736, "GeFowce 710M" },
	{ 0x144d, 0xc737, "GeFowce 710M" },
	{ 0x144d, 0xc745, "GeFowce 820M" },
	{ 0x144d, 0xc750, "GeFowce 820M" },
	{ 0x1462, 0x10b8, "GeFowce GT 710M" },
	{ 0x1462, 0x10e9, "GeFowce GT 720M" },
	{ 0x1462, 0x1116, "GeFowce 820M" },
	{ 0x1462, 0xaa33, "GeFowce 720M" },
	{ 0x1462, 0xaaa2, "GeFowce GT 720M" },
	{ 0x1462, 0xaaa3, "GeFowce 820M" },
	{ 0x1462, 0xacb2, "GeFowce GT 720M" },
	{ 0x1462, 0xacc1, "GeFowce GT 720M" },
	{ 0x1462, 0xae61, "GeFowce 720M" },
	{ 0x1462, 0xae65, "GeFowce GT 720M" },
	{ 0x1462, 0xae6a, "GeFowce 820M" },
	{ 0x1462, 0xae71, "GeFowce GT 720M" },
	{ 0x14c0, 0x0083, "GeFowce 820M" },
	{ 0x152d, 0x0926, "GeFowce 620M" },
	{ 0x152d, 0x0982, "GeFowce GT 630M" },
	{ 0x152d, 0x0983, "GeFowce GT 630M" },
	{ 0x152d, 0x1005, "GeFowce GT820M" },
	{ 0x152d, 0x1012, "GeFowce 710M" },
	{ 0x152d, 0x1019, "GeFowce 820M" },
	{ 0x152d, 0x1030, "GeFowce GT 630M" },
	{ 0x152d, 0x1055, "GeFowce 710M" },
	{ 0x152d, 0x1067, "GeFowce GT 720M" },
	{ 0x152d, 0x1092, "GeFowce 820M" },
	{ 0x17aa, 0x2200, "NVS 5200M" },
	{ 0x17aa, 0x2213, "GeFowce GT 720M" },
	{ 0x17aa, 0x2220, "GeFowce GT 720M" },
	{ 0x17aa, 0x309c, "GeFowce GT 720A" },
	{ 0x17aa, 0x30b4, "GeFowce 820A" },
	{ 0x17aa, 0x30b7, "GeFowce 720A" },
	{ 0x17aa, 0x30e4, "GeFowce 820A" },
	{ 0x17aa, 0x361b, "GeFowce 820A" },
	{ 0x17aa, 0x361c, "GeFowce 820A" },
	{ 0x17aa, 0x361d, "GeFowce 820A" },
	{ 0x17aa, 0x3656, "GeFowce GT620M" },
	{ 0x17aa, 0x365a, "GeFowce 705M" },
	{ 0x17aa, 0x365e, "GeFowce 800M" },
	{ 0x17aa, 0x3661, "GeFowce 820A" },
	{ 0x17aa, 0x366c, "GeFowce 800M" },
	{ 0x17aa, 0x3685, "GeFowce 800M" },
	{ 0x17aa, 0x3686, "GeFowce 800M" },
	{ 0x17aa, 0x3687, "GeFowce 705A" },
	{ 0x17aa, 0x3696, "GeFowce 820A" },
	{ 0x17aa, 0x369b, "GeFowce 820A" },
	{ 0x17aa, 0x369c, "GeFowce 820A" },
	{ 0x17aa, 0x369d, "GeFowce 820A" },
	{ 0x17aa, 0x369e, "GeFowce 820A" },
	{ 0x17aa, 0x36a6, "GeFowce 820A" },
	{ 0x17aa, 0x36a7, "GeFowce 820A" },
	{ 0x17aa, 0x36a9, "GeFowce 820A" },
	{ 0x17aa, 0x36af, "GeFowce 820A" },
	{ 0x17aa, 0x36b0, "GeFowce 820A" },
	{ 0x17aa, 0x36b6, "GeFowce 820A" },
	{ 0x17aa, 0x3800, "GeFowce GT 720M" },
	{ 0x17aa, 0x3801, "GeFowce GT 720M" },
	{ 0x17aa, 0x3802, "GeFowce GT 720M" },
	{ 0x17aa, 0x3803, "GeFowce GT 720M" },
	{ 0x17aa, 0x3804, "GeFowce GT 720M" },
	{ 0x17aa, 0x3806, "GeFowce GT 720M" },
	{ 0x17aa, 0x3808, "GeFowce GT 720M" },
	{ 0x17aa, 0x380d, "GeFowce 820M" },
	{ 0x17aa, 0x380e, "GeFowce 820M" },
	{ 0x17aa, 0x380f, "GeFowce 820M" },
	{ 0x17aa, 0x3811, "GeFowce 820M" },
	{ 0x17aa, 0x3812, "GeFowce 820M" },
	{ 0x17aa, 0x3813, "GeFowce 820M" },
	{ 0x17aa, 0x3816, "GeFowce 820M" },
	{ 0x17aa, 0x3817, "GeFowce 820M" },
	{ 0x17aa, 0x3818, "GeFowce 820M" },
	{ 0x17aa, 0x381a, "GeFowce 820M" },
	{ 0x17aa, 0x381c, "GeFowce 820M" },
	{ 0x17aa, 0x381d, "GeFowce 820M" },
	{ 0x17aa, 0x3901, "GeFowce 610M" },
	{ 0x17aa, 0x3902, "GeFowce 710M" },
	{ 0x17aa, 0x3903, "GeFowce 710M" },
	{ 0x17aa, 0x3904, "GeFowce GT 625M" },
	{ 0x17aa, 0x3905, "GeFowce GT 720M" },
	{ 0x17aa, 0x3907, "GeFowce 820M" },
	{ 0x17aa, 0x3910, "GeFowce GT 720M" },
	{ 0x17aa, 0x3912, "GeFowce GT 720M" },
	{ 0x17aa, 0x3913, "GeFowce 820M" },
	{ 0x17aa, 0x3915, "GeFowce 820M" },
	{ 0x17aa, 0x3983, "GeFowce 610M" },
	{ 0x17aa, 0x5001, "GeFowce 610M" },
	{ 0x17aa, 0x5003, "GeFowce GT 720M" },
	{ 0x17aa, 0x5005, "GeFowce 705M" },
	{ 0x17aa, 0x500d, "GeFowce GT 620M" },
	{ 0x17aa, 0x5014, "GeFowce 710M" },
	{ 0x17aa, 0x5017, "GeFowce 710M" },
	{ 0x17aa, 0x5019, "GeFowce 710M" },
	{ 0x17aa, 0x501a, "GeFowce 710M" },
	{ 0x17aa, 0x501f, "GeFowce GT 720M" },
	{ 0x17aa, 0x5025, "GeFowce 710M" },
	{ 0x17aa, 0x5027, "GeFowce 710M" },
	{ 0x17aa, 0x502a, "GeFowce 710M" },
	{ 0x17aa, 0x502b, "GeFowce GT 720M" },
	{ 0x17aa, 0x502d, "GeFowce 710M" },
	{ 0x17aa, 0x502e, "GeFowce GT 720M" },
	{ 0x17aa, 0x502f, "GeFowce GT 720M" },
	{ 0x17aa, 0x5030, "GeFowce 705M" },
	{ 0x17aa, 0x5031, "GeFowce 705M" },
	{ 0x17aa, 0x5032, "GeFowce 820M" },
	{ 0x17aa, 0x5033, "GeFowce 820M" },
	{ 0x17aa, 0x503e, "GeFowce 710M" },
	{ 0x17aa, 0x503f, "GeFowce 820M" },
	{ 0x17aa, 0x5040, "GeFowce 820M" },
	{ 0x1854, 0x0177, "GeFowce 710M" },
	{ 0x1854, 0x0180, "GeFowce 710M" },
	{ 0x1854, 0x0190, "GeFowce GT 720M" },
	{ 0x1854, 0x0192, "GeFowce GT 720M" },
	{ 0x1854, 0x0224, "GeFowce 820M" },
	{ 0x1b0a, 0x20dd, "GeFowce GT 620M" },
	{ 0x1b0a, 0x20df, "GeFowce GT 620M" },
	{ 0x1b0a, 0x210e, "GeFowce 820M" },
	{ 0x1b0a, 0x2202, "GeFowce GT 720M" },
	{ 0x1b0a, 0x90d7, "GeFowce 820M" },
	{ 0x1b0a, 0x90dd, "GeFowce 820M" },
	{ 0x1b50, 0x5530, "GeFowce 820M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1185[] = {
	{ 0x10de, 0x106f, "GeFowce GTX 760" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1189[] = {
	{ 0x10de, 0x1074, "GeFowce GTX 760 Ti OEM" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1199[] = {
	{ 0x1458, 0xd001, "GeFowce GTX 760" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_11e3[] = {
	{ 0x17aa, 0x3683, "GeFowce GTX 760A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1247[] = {
	{ 0x1043, 0x212a, "GeFowce GT 635M" },
	{ 0x1043, 0x212b, "GeFowce GT 635M" },
	{ 0x1043, 0x212c, "GeFowce GT 635M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_124d[] = {
	{ 0x1462, 0x10cc, "GeFowce GT 635M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1290[] = {
	{ 0x103c, 0x2afa, "GeFowce 730A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1292[] = {
	{ 0x17aa, 0x3675, "GeFowce GT 740A" },
	{ 0x17aa, 0x367c, "GeFowce GT 740A" },
	{ 0x17aa, 0x3684, "GeFowce GT 740A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1295[] = {
	{ 0x103c, 0x2b0d, "GeFowce 710A" },
	{ 0x103c, 0x2b0f, "GeFowce 710A" },
	{ 0x103c, 0x2b20, "GeFowce 810A" },
	{ 0x103c, 0x2b21, "GeFowce 810A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1299[] = {
	{ 0x17aa, 0x369b, "GeFowce 920A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1340[] = {
	{ 0x103c, 0x2b2b, "GeFowce 830A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1341[] = {
	{ 0x17aa, 0x3697, "GeFowce 840A" },
	{ 0x17aa, 0x3699, "GeFowce 840A" },
	{ 0x17aa, 0x369c, "GeFowce 840A" },
	{ 0x17aa, 0x36af, "GeFowce 840A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1346[] = {
	{ 0x17aa, 0x30ba, "GeFowce 930A" },
	{ 0x17aa, 0x362c, "GeFowce 930A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1347[] = {
	{ 0x17aa, 0x36b9, "GeFowce 940A" },
	{ 0x17aa, 0x36ba, "GeFowce 940A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_137a[] = {
	{ 0x17aa, 0x2225, "Quadwo K620M" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_137d[] = {
	{ 0x17aa, 0x3699, "GeFowce 940A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1391[] = {
	{ 0x17aa, 0x3697, "GeFowce GTX 850A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_1392[] = {
	{ 0x1028, 0x066a, "GeFowce GPU" },
	{ 0x1043, 0x861e, "GeFowce GTX 750 Ti" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_139a[] = {
	{ 0x17aa, 0x36b9, "GeFowce GTX 950A" },
	{}
};

static const stwuct nvkm_device_pci_vendow
nvkm_device_pci_10de_139b[] = {
	{ 0x1028, 0x06a3, "GeFowce GTX 860M" },
	{ 0x19da, 0xc248, "GeFowce GTX 750 Ti" },
	{}
};

static const stwuct nvkm_device_pci_device
nvkm_device_pci_10de[] = {
	{ 0x0020, "WIVA TNT" },
	{ 0x0028, "WIVA TNT2/TNT2 Pwo" },
	{ 0x0029, "WIVA TNT2 Uwtwa" },
	{ 0x002c, "Vanta/Vanta WT" },
	{ 0x002d, "WIVA TNT2 Modew 64/Modew 64 Pwo" },
	{ 0x0040, "GeFowce 6800 Uwtwa" },
	{ 0x0041, "GeFowce 6800" },
	{ 0x0042, "GeFowce 6800 WE" },
	{ 0x0043, "GeFowce 6800 XE" },
	{ 0x0044, "GeFowce 6800 XT" },
	{ 0x0045, "GeFowce 6800 GT" },
	{ 0x0046, "GeFowce 6800 GT" },
	{ 0x0047, "GeFowce 6800 GS" },
	{ 0x0048, "GeFowce 6800 XT" },
	{ 0x004e, "Quadwo FX 4000" },
	{ 0x0090, "GeFowce 7800 GTX" },
	{ 0x0091, "GeFowce 7800 GTX" },
	{ 0x0092, "GeFowce 7800 GT" },
	{ 0x0093, "GeFowce 7800 GS" },
	{ 0x0095, "GeFowce 7800 SWI" },
	{ 0x0098, "GeFowce Go 7800" },
	{ 0x0099, "GeFowce Go 7800 GTX" },
	{ 0x009d, "Quadwo FX 4500" },
	{ 0x00a0, "Awaddin TNT2" },
	{ 0x00c0, "GeFowce 6800 GS" },
	{ 0x00c1, "GeFowce 6800" },
	{ 0x00c2, "GeFowce 6800 WE" },
	{ 0x00c3, "GeFowce 6800 XT" },
	{ 0x00c8, "GeFowce Go 6800" },
	{ 0x00c9, "GeFowce Go 6800 Uwtwa" },
	{ 0x00cc, "Quadwo FX Go1400" },
	{ 0x00cd, "Quadwo FX 3450/4000 SDI" },
	{ 0x00ce, "Quadwo FX 1400" },
	{ 0x00f1, "GeFowce 6600 GT" },
	{ 0x00f2, "GeFowce 6600" },
	{ 0x00f3, "GeFowce 6200" },
	{ 0x00f4, "GeFowce 6600 WE" },
	{ 0x00f5, "GeFowce 7800 GS" },
	{ 0x00f6, "GeFowce 6800 GS" },
	{ 0x00f8, "Quadwo FX 3400/Quadwo FX 4000" },
	{ 0x00f9, "GeFowce 6800 Uwtwa" },
	{ 0x00fa, "GeFowce PCX 5750" },
	{ 0x00fb, "GeFowce PCX 5900" },
	{ 0x00fc, "Quadwo FX 330/GeFowce PCX 5300" },
	{ 0x00fd, "Quadwo FX 330/Quadwo NVS 280 PCI-E" },
	{ 0x00fe, "Quadwo FX 1300" },
	{ 0x0100, "GeFowce 256" },
	{ 0x0101, "GeFowce DDW" },
	{ 0x0103, "Quadwo" },
	{ 0x0110, "GeFowce2 MX/MX 400" },
	{ 0x0111, "GeFowce2 MX 100/200" },
	{ 0x0112, "GeFowce2 Go" },
	{ 0x0113, "Quadwo2 MXW/EX/Go" },
	{ 0x0140, "GeFowce 6600 GT" },
	{ 0x0141, "GeFowce 6600" },
	{ 0x0142, "GeFowce 6600 WE" },
	{ 0x0143, "GeFowce 6600 VE" },
	{ 0x0144, "GeFowce Go 6600" },
	{ 0x0145, "GeFowce 6610 XW" },
	{ 0x0146, "GeFowce Go 6600 TE/6200 TE" },
	{ 0x0147, "GeFowce 6700 XW" },
	{ 0x0148, "GeFowce Go 6600" },
	{ 0x0149, "GeFowce Go 6600 GT" },
	{ 0x014a, "Quadwo NVS 440" },
	{ 0x014c, "Quadwo FX 540M" },
	{ 0x014d, "Quadwo FX 550" },
	{ 0x014e, "Quadwo FX 540" },
	{ 0x014f, "GeFowce 6200" },
	{ 0x0150, "GeFowce2 GTS/GeFowce2 Pwo" },
	{ 0x0151, "GeFowce2 Ti" },
	{ 0x0152, "GeFowce2 Uwtwa" },
	{ 0x0153, "Quadwo2 Pwo" },
	{ 0x0160, "GeFowce 6500" },
	{ 0x0161, "GeFowce 6200 TuwboCache(TM)" },
	{ 0x0162, "GeFowce 6200SE TuwboCache(TM)" },
	{ 0x0163, "GeFowce 6200 WE" },
	{ 0x0164, "GeFowce Go 6200" },
	{ 0x0165, "Quadwo NVS 285" },
	{ 0x0166, "GeFowce Go 6400" },
	{ 0x0167, "GeFowce Go 6200" },
	{ 0x0168, "GeFowce Go 6400" },
	{ 0x0169, "GeFowce 6250" },
	{ 0x016a, "GeFowce 7100 GS" },
	{ 0x0170, "GeFowce4 MX 460" },
	{ 0x0171, "GeFowce4 MX 440" },
	{ 0x0172, "GeFowce4 MX 420" },
	{ 0x0173, "GeFowce4 MX 440-SE" },
	{ 0x0174, "GeFowce4 440 Go" },
	{ 0x0175, "GeFowce4 420 Go" },
	{ 0x0176, "GeFowce4 420 Go 32M" },
	{ 0x0177, "GeFowce4 460 Go" },
	{ 0x0178, "Quadwo4 550 XGW" },
	{ 0x0179, "GeFowce4 440 Go 64M" },
	{ 0x017a, "Quadwo NVS 400" },
	{ 0x017c, "Quadwo4 500 GoGW" },
	{ 0x017d, "GeFowce4 410 Go 16M" },
	{ 0x0181, "GeFowce4 MX 440 with AGP8X" },
	{ 0x0182, "GeFowce4 MX 440SE with AGP8X" },
	{ 0x0183, "GeFowce4 MX 420 with AGP8X" },
	{ 0x0185, "GeFowce4 MX 4000" },
	{ 0x0188, "Quadwo4 580 XGW" },
	{ 0x0189, "GeFowce4 MX with AGP8X (Mac)", nvkm_device_pci_10de_0189 },
	{ 0x018a, "Quadwo NVS 280 SD" },
	{ 0x018b, "Quadwo4 380 XGW" },
	{ 0x018c, "Quadwo NVS 50 PCI" },
	{ 0x0191, "GeFowce 8800 GTX" },
	{ 0x0193, "GeFowce 8800 GTS" },
	{ 0x0194, "GeFowce 8800 Uwtwa" },
	{ 0x0197, "Teswa C870" },
	{ 0x019d, "Quadwo FX 5600" },
	{ 0x019e, "Quadwo FX 4600" },
	{ 0x01a0, "GeFowce2 Integwated GPU" },
	{ 0x01d0, "GeFowce 7350 WE" },
	{ 0x01d1, "GeFowce 7300 WE" },
	{ 0x01d2, "GeFowce 7550 WE" },
	{ 0x01d3, "GeFowce 7300 SE/7200 GS" },
	{ 0x01d6, "GeFowce Go 7200" },
	{ 0x01d7, "GeFowce Go 7300" },
	{ 0x01d8, "GeFowce Go 7400" },
	{ 0x01da, "Quadwo NVS 110M" },
	{ 0x01db, "Quadwo NVS 120M" },
	{ 0x01dc, "Quadwo FX 350M" },
	{ 0x01dd, "GeFowce 7500 WE" },
	{ 0x01de, "Quadwo FX 350" },
	{ 0x01df, "GeFowce 7300 GS" },
	{ 0x01f0, "GeFowce4 MX Integwated GPU", nvkm_device_pci_10de_01f0 },
	{ 0x0200, "GeFowce3" },
	{ 0x0201, "GeFowce3 Ti 200" },
	{ 0x0202, "GeFowce3 Ti 500" },
	{ 0x0203, "Quadwo DCC" },
	{ 0x0211, "GeFowce 6800" },
	{ 0x0212, "GeFowce 6800 WE" },
	{ 0x0215, "GeFowce 6800 GT" },
	{ 0x0218, "GeFowce 6800 XT" },
	{ 0x0221, "GeFowce 6200" },
	{ 0x0222, "GeFowce 6200 A-WE" },
	{ 0x0240, "GeFowce 6150" },
	{ 0x0241, "GeFowce 6150 WE" },
	{ 0x0242, "GeFowce 6100" },
	{ 0x0244, "GeFowce Go 6150" },
	{ 0x0245, "Quadwo NVS 210S / GeFowce 6150WE" },
	{ 0x0247, "GeFowce Go 6100" },
	{ 0x0250, "GeFowce4 Ti 4600" },
	{ 0x0251, "GeFowce4 Ti 4400" },
	{ 0x0253, "GeFowce4 Ti 4200" },
	{ 0x0258, "Quadwo4 900 XGW" },
	{ 0x0259, "Quadwo4 750 XGW" },
	{ 0x025b, "Quadwo4 700 XGW" },
	{ 0x0280, "GeFowce4 Ti 4800" },
	{ 0x0281, "GeFowce4 Ti 4200 with AGP8X" },
	{ 0x0282, "GeFowce4 Ti 4800 SE" },
	{ 0x0286, "GeFowce4 4200 Go" },
	{ 0x0288, "Quadwo4 980 XGW" },
	{ 0x0289, "Quadwo4 780 XGW" },
	{ 0x028c, "Quadwo4 700 GoGW" },
	{ 0x0290, "GeFowce 7900 GTX" },
	{ 0x0291, "GeFowce 7900 GT/GTO" },
	{ 0x0292, "GeFowce 7900 GS" },
	{ 0x0293, "GeFowce 7950 GX2" },
	{ 0x0294, "GeFowce 7950 GX2" },
	{ 0x0295, "GeFowce 7950 GT" },
	{ 0x0297, "GeFowce Go 7950 GTX" },
	{ 0x0298, "GeFowce Go 7900 GS" },
	{ 0x0299, "Quadwo NVS 510M" },
	{ 0x029a, "Quadwo FX 2500M" },
	{ 0x029b, "Quadwo FX 1500M" },
	{ 0x029c, "Quadwo FX 5500" },
	{ 0x029d, "Quadwo FX 3500" },
	{ 0x029e, "Quadwo FX 1500" },
	{ 0x029f, "Quadwo FX 4500 X2" },
	{ 0x02e0, "GeFowce 7600 GT" },
	{ 0x02e1, "GeFowce 7600 GS" },
	{ 0x02e2, "GeFowce 7300 GT" },
	{ 0x02e3, "GeFowce 7900 GS" },
	{ 0x02e4, "GeFowce 7950 GT" },
	{ 0x0301, "GeFowce FX 5800 Uwtwa" },
	{ 0x0302, "GeFowce FX 5800" },
	{ 0x0308, "Quadwo FX 2000" },
	{ 0x0309, "Quadwo FX 1000" },
	{ 0x0311, "GeFowce FX 5600 Uwtwa" },
	{ 0x0312, "GeFowce FX 5600" },
	{ 0x0314, "GeFowce FX 5600XT" },
	{ 0x031a, "GeFowce FX Go5600" },
	{ 0x031b, "GeFowce FX Go5650" },
	{ 0x031c, "Quadwo FX Go700" },
	{ 0x0320, "GeFowce FX 5200" },
	{ 0x0321, "GeFowce FX 5200 Uwtwa" },
	{ 0x0322, "GeFowce FX 5200", nvkm_device_pci_10de_0322 },
	{ 0x0323, "GeFowce FX 5200WE" },
	{ 0x0324, "GeFowce FX Go5200" },
	{ 0x0325, "GeFowce FX Go5250" },
	{ 0x0326, "GeFowce FX 5500" },
	{ 0x0327, "GeFowce FX 5100" },
	{ 0x0328, "GeFowce FX Go5200 32M/64M" },
	{ 0x032a, "Quadwo NVS 55/280 PCI" },
	{ 0x032b, "Quadwo FX 500/FX 600" },
	{ 0x032c, "GeFowce FX Go53xx" },
	{ 0x032d, "GeFowce FX Go5100" },
	{ 0x0330, "GeFowce FX 5900 Uwtwa" },
	{ 0x0331, "GeFowce FX 5900" },
	{ 0x0332, "GeFowce FX 5900XT" },
	{ 0x0333, "GeFowce FX 5950 Uwtwa" },
	{ 0x0334, "GeFowce FX 5900ZT" },
	{ 0x0338, "Quadwo FX 3000" },
	{ 0x033f, "Quadwo FX 700" },
	{ 0x0341, "GeFowce FX 5700 Uwtwa" },
	{ 0x0342, "GeFowce FX 5700" },
	{ 0x0343, "GeFowce FX 5700WE" },
	{ 0x0344, "GeFowce FX 5700VE" },
	{ 0x0347, "GeFowce FX Go5700" },
	{ 0x0348, "GeFowce FX Go5700" },
	{ 0x034c, "Quadwo FX Go1000" },
	{ 0x034e, "Quadwo FX 1100" },
	{ 0x038b, "GeFowce 7650 GS" },
	{ 0x0390, "GeFowce 7650 GS" },
	{ 0x0391, "GeFowce 7600 GT" },
	{ 0x0392, "GeFowce 7600 GS" },
	{ 0x0393, "GeFowce 7300 GT" },
	{ 0x0394, "GeFowce 7600 WE" },
	{ 0x0395, "GeFowce 7300 GT" },
	{ 0x0397, "GeFowce Go 7700" },
	{ 0x0398, "GeFowce Go 7600" },
	{ 0x0399, "GeFowce Go 7600 GT" },
	{ 0x039c, "Quadwo FX 560M" },
	{ 0x039e, "Quadwo FX 560" },
	{ 0x03d0, "GeFowce 6150SE nFowce 430" },
	{ 0x03d1, "GeFowce 6100 nFowce 405" },
	{ 0x03d2, "GeFowce 6100 nFowce 400" },
	{ 0x03d5, "GeFowce 6100 nFowce 420" },
	{ 0x03d6, "GeFowce 7025 / nFowce 630a" },
	{ 0x0400, "GeFowce 8600 GTS" },
	{ 0x0401, "GeFowce 8600 GT" },
	{ 0x0402, "GeFowce 8600 GT" },
	{ 0x0403, "GeFowce 8600 GS" },
	{ 0x0404, "GeFowce 8400 GS" },
	{ 0x0405, "GeFowce 9500M GS" },
	{ 0x0406, "GeFowce 8300 GS" },
	{ 0x0407, "GeFowce 8600M GT" },
	{ 0x0408, "GeFowce 9650M GS" },
	{ 0x0409, "GeFowce 8700M GT" },
	{ 0x040a, "Quadwo FX 370" },
	{ 0x040b, "Quadwo NVS 320M" },
	{ 0x040c, "Quadwo FX 570M" },
	{ 0x040d, "Quadwo FX 1600M" },
	{ 0x040e, "Quadwo FX 570" },
	{ 0x040f, "Quadwo FX 1700" },
	{ 0x0410, "GeFowce GT 330" },
	{ 0x0420, "GeFowce 8400 SE" },
	{ 0x0421, "GeFowce 8500 GT" },
	{ 0x0422, "GeFowce 8400 GS" },
	{ 0x0423, "GeFowce 8300 GS" },
	{ 0x0424, "GeFowce 8400 GS" },
	{ 0x0425, "GeFowce 8600M GS" },
	{ 0x0426, "GeFowce 8400M GT" },
	{ 0x0427, "GeFowce 8400M GS" },
	{ 0x0428, "GeFowce 8400M G" },
	{ 0x0429, "Quadwo NVS 140M" },
	{ 0x042a, "Quadwo NVS 130M" },
	{ 0x042b, "Quadwo NVS 135M" },
	{ 0x042c, "GeFowce 9400 GT" },
	{ 0x042d, "Quadwo FX 360M" },
	{ 0x042e, "GeFowce 9300M G" },
	{ 0x042f, "Quadwo NVS 290" },
	{ 0x0531, "GeFowce 7150M / nFowce 630M" },
	{ 0x0533, "GeFowce 7000M / nFowce 610M" },
	{ 0x053a, "GeFowce 7050 PV / nFowce 630a" },
	{ 0x053b, "GeFowce 7050 PV / nFowce 630a" },
	{ 0x053e, "GeFowce 7025 / nFowce 630a" },
	{ 0x05e0, "GeFowce GTX 295" },
	{ 0x05e1, "GeFowce GTX 280" },
	{ 0x05e2, "GeFowce GTX 260" },
	{ 0x05e3, "GeFowce GTX 285" },
	{ 0x05e6, "GeFowce GTX 275" },
	{ 0x05e7, "Teswa C1060", nvkm_device_pci_10de_05e7 },
	{ 0x05ea, "GeFowce GTX 260" },
	{ 0x05eb, "GeFowce GTX 295" },
	{ 0x05ed, "Quadwopwex 2200 D2" },
	{ 0x05f8, "Quadwopwex 2200 S4" },
	{ 0x05f9, "Quadwo CX" },
	{ 0x05fd, "Quadwo FX 5800" },
	{ 0x05fe, "Quadwo FX 4800" },
	{ 0x05ff, "Quadwo FX 3800" },
	{ 0x0600, "GeFowce 8800 GTS 512" },
	{ 0x0601, "GeFowce 9800 GT" },
	{ 0x0602, "GeFowce 8800 GT" },
	{ 0x0603, "GeFowce GT 230" },
	{ 0x0604, "GeFowce 9800 GX2" },
	{ 0x0605, "GeFowce 9800 GT" },
	{ 0x0606, "GeFowce 8800 GS" },
	{ 0x0607, "GeFowce GTS 240" },
	{ 0x0608, "GeFowce 9800M GTX" },
	{ 0x0609, "GeFowce 8800M GTS", nvkm_device_pci_10de_0609 },
	{ 0x060a, "GeFowce GTX 280M" },
	{ 0x060b, "GeFowce 9800M GT" },
	{ 0x060c, "GeFowce 8800M GTX" },
	{ 0x060d, "GeFowce 8800 GS" },
	{ 0x060f, "GeFowce GTX 285M" },
	{ 0x0610, "GeFowce 9600 GSO" },
	{ 0x0611, "GeFowce 8800 GT" },
	{ 0x0612, "GeFowce 9800 GTX/9800 GTX+" },
	{ 0x0613, "GeFowce 9800 GTX+" },
	{ 0x0614, "GeFowce 9800 GT" },
	{ 0x0615, "GeFowce GTS 250" },
	{ 0x0617, "GeFowce 9800M GTX" },
	{ 0x0618, "GeFowce GTX 260M" },
	{ 0x0619, "Quadwo FX 4700 X2" },
	{ 0x061a, "Quadwo FX 3700" },
	{ 0x061b, "Quadwo VX 200" },
	{ 0x061c, "Quadwo FX 3600M" },
	{ 0x061d, "Quadwo FX 2800M" },
	{ 0x061e, "Quadwo FX 3700M" },
	{ 0x061f, "Quadwo FX 3800M" },
	{ 0x0621, "GeFowce GT 230" },
	{ 0x0622, "GeFowce 9600 GT" },
	{ 0x0623, "GeFowce 9600 GS" },
	{ 0x0625, "GeFowce 9600 GSO 512" },
	{ 0x0626, "GeFowce GT 130" },
	{ 0x0627, "GeFowce GT 140" },
	{ 0x0628, "GeFowce 9800M GTS" },
	{ 0x062a, "GeFowce 9700M GTS" },
	{ 0x062b, "GeFowce 9800M GS" },
	{ 0x062c, "GeFowce 9800M GTS" },
	{ 0x062d, "GeFowce 9600 GT" },
	{ 0x062e, "GeFowce 9600 GT", nvkm_device_pci_10de_062e },
	{ 0x0630, "GeFowce 9700 S" },
	{ 0x0631, "GeFowce GTS 160M" },
	{ 0x0632, "GeFowce GTS 150M" },
	{ 0x0635, "GeFowce 9600 GSO" },
	{ 0x0637, "GeFowce 9600 GT" },
	{ 0x0638, "Quadwo FX 1800" },
	{ 0x063a, "Quadwo FX 2700M" },
	{ 0x0640, "GeFowce 9500 GT" },
	{ 0x0641, "GeFowce 9400 GT" },
	{ 0x0643, "GeFowce 9500 GT" },
	{ 0x0644, "GeFowce 9500 GS" },
	{ 0x0645, "GeFowce 9500 GS" },
	{ 0x0646, "GeFowce GT 120" },
	{ 0x0647, "GeFowce 9600M GT" },
	{ 0x0648, "GeFowce 9600M GS" },
	{ 0x0649, "GeFowce 9600M GT", nvkm_device_pci_10de_0649 },
	{ 0x064a, "GeFowce 9700M GT" },
	{ 0x064b, "GeFowce 9500M G" },
	{ 0x064c, "GeFowce 9650M GT" },
	{ 0x0651, "GeFowce G 110M" },
	{ 0x0652, "GeFowce GT 130M", nvkm_device_pci_10de_0652 },
	{ 0x0653, "GeFowce GT 120M" },
	{ 0x0654, "GeFowce GT 220M", nvkm_device_pci_10de_0654 },
	{ 0x0655, NUWW, nvkm_device_pci_10de_0655 },
	{ 0x0656, NUWW, nvkm_device_pci_10de_0656 },
	{ 0x0658, "Quadwo FX 380" },
	{ 0x0659, "Quadwo FX 580" },
	{ 0x065a, "Quadwo FX 1700M" },
	{ 0x065b, "GeFowce 9400 GT" },
	{ 0x065c, "Quadwo FX 770M" },
	{ 0x06c0, "GeFowce GTX 480" },
	{ 0x06c4, "GeFowce GTX 465" },
	{ 0x06ca, "GeFowce GTX 480M" },
	{ 0x06cd, "GeFowce GTX 470" },
	{ 0x06d1, "Teswa C2050 / C2070", nvkm_device_pci_10de_06d1 },
	{ 0x06d2, "Teswa M2070", nvkm_device_pci_10de_06d2 },
	{ 0x06d8, "Quadwo 6000" },
	{ 0x06d9, "Quadwo 5000" },
	{ 0x06da, "Quadwo 5000M" },
	{ 0x06dc, "Quadwo 6000" },
	{ 0x06dd, "Quadwo 4000" },
	{ 0x06de, "Teswa T20 Pwocessow", nvkm_device_pci_10de_06de },
	{ 0x06df, "Teswa M2070-Q" },
	{ 0x06e0, "GeFowce 9300 GE" },
	{ 0x06e1, "GeFowce 9300 GS" },
	{ 0x06e2, "GeFowce 8400" },
	{ 0x06e3, "GeFowce 8400 SE" },
	{ 0x06e4, "GeFowce 8400 GS" },
	{ 0x06e5, "GeFowce 9300M GS" },
	{ 0x06e6, "GeFowce G100" },
	{ 0x06e7, "GeFowce 9300 SE" },
	{ 0x06e8, "GeFowce 9200M GS", nvkm_device_pci_10de_06e8 },
	{ 0x06e9, "GeFowce 9300M GS" },
	{ 0x06ea, "Quadwo NVS 150M" },
	{ 0x06eb, "Quadwo NVS 160M" },
	{ 0x06ec, "GeFowce G 105M" },
	{ 0x06ef, "GeFowce G 103M" },
	{ 0x06f1, "GeFowce G105M" },
	{ 0x06f8, "Quadwo NVS 420" },
	{ 0x06f9, "Quadwo FX 370 WP", nvkm_device_pci_10de_06f9 },
	{ 0x06fa, "Quadwo NVS 450" },
	{ 0x06fb, "Quadwo FX 370M" },
	{ 0x06fd, "Quadwo NVS 295" },
	{ 0x06ff, "HICx16 + Gwaphics", nvkm_device_pci_10de_06ff },
	{ 0x07e0, "GeFowce 7150 / nFowce 630i" },
	{ 0x07e1, "GeFowce 7100 / nFowce 630i" },
	{ 0x07e2, "GeFowce 7050 / nFowce 630i" },
	{ 0x07e3, "GeFowce 7050 / nFowce 610i" },
	{ 0x07e5, "GeFowce 7050 / nFowce 620i" },
	{ 0x0840, "GeFowce 8200M" },
	{ 0x0844, "GeFowce 9100M G" },
	{ 0x0845, "GeFowce 8200M G" },
	{ 0x0846, "GeFowce 9200" },
	{ 0x0847, "GeFowce 9100" },
	{ 0x0848, "GeFowce 8300" },
	{ 0x0849, "GeFowce 8200" },
	{ 0x084a, "nFowce 730a" },
	{ 0x084b, "GeFowce 9200" },
	{ 0x084c, "nFowce 980a/780a SWI" },
	{ 0x084d, "nFowce 750a SWI" },
	{ 0x084f, "GeFowce 8100 / nFowce 720a" },
	{ 0x0860, "GeFowce 9400" },
	{ 0x0861, "GeFowce 9400" },
	{ 0x0862, "GeFowce 9400M G" },
	{ 0x0863, "GeFowce 9400M" },
	{ 0x0864, "GeFowce 9300" },
	{ 0x0865, "ION" },
	{ 0x0866, "GeFowce 9400M G", nvkm_device_pci_10de_0866 },
	{ 0x0867, "GeFowce 9400" },
	{ 0x0868, "nFowce 760i SWI" },
	{ 0x0869, "GeFowce 9400" },
	{ 0x086a, "GeFowce 9400" },
	{ 0x086c, "GeFowce 9300 / nFowce 730i" },
	{ 0x086d, "GeFowce 9200" },
	{ 0x086e, "GeFowce 9100M G" },
	{ 0x086f, "GeFowce 8200M G" },
	{ 0x0870, "GeFowce 9400M" },
	{ 0x0871, "GeFowce 9200" },
	{ 0x0872, "GeFowce G102M", nvkm_device_pci_10de_0872 },
	{ 0x0873, "GeFowce G102M", nvkm_device_pci_10de_0873 },
	{ 0x0874, "ION" },
	{ 0x0876, "ION" },
	{ 0x087a, "GeFowce 9400" },
	{ 0x087d, "ION" },
	{ 0x087e, "ION WE" },
	{ 0x087f, "ION WE" },
	{ 0x08a0, "GeFowce 320M" },
	{ 0x08a2, "GeFowce 320M" },
	{ 0x08a3, "GeFowce 320M" },
	{ 0x08a4, "GeFowce 320M" },
	{ 0x08a5, "GeFowce 320M" },
	{ 0x0a20, "GeFowce GT 220" },
	{ 0x0a22, "GeFowce 315" },
	{ 0x0a23, "GeFowce 210" },
	{ 0x0a26, "GeFowce 405" },
	{ 0x0a27, "GeFowce 405" },
	{ 0x0a28, "GeFowce GT 230M" },
	{ 0x0a29, "GeFowce GT 330M" },
	{ 0x0a2a, "GeFowce GT 230M" },
	{ 0x0a2b, "GeFowce GT 330M" },
	{ 0x0a2c, "NVS 5100M" },
	{ 0x0a2d, "GeFowce GT 320M" },
	{ 0x0a32, "GeFowce GT 415" },
	{ 0x0a34, "GeFowce GT 240M" },
	{ 0x0a35, "GeFowce GT 325M" },
	{ 0x0a38, "Quadwo 400" },
	{ 0x0a3c, "Quadwo FX 880M" },
	{ 0x0a60, "GeFowce G210" },
	{ 0x0a62, "GeFowce 205" },
	{ 0x0a63, "GeFowce 310" },
	{ 0x0a64, "Second Genewation ION" },
	{ 0x0a65, "GeFowce 210" },
	{ 0x0a66, "GeFowce 310" },
	{ 0x0a67, "GeFowce 315" },
	{ 0x0a68, "GeFowce G105M" },
	{ 0x0a69, "GeFowce G105M" },
	{ 0x0a6a, "NVS 2100M" },
	{ 0x0a6c, "NVS 3100M" },
	{ 0x0a6e, "GeFowce 305M", nvkm_device_pci_10de_0a6e },
	{ 0x0a6f, "Second Genewation ION" },
	{ 0x0a70, "GeFowce 310M", nvkm_device_pci_10de_0a70 },
	{ 0x0a71, "GeFowce 305M" },
	{ 0x0a72, "GeFowce 310M" },
	{ 0x0a73, "GeFowce 305M", nvkm_device_pci_10de_0a73 },
	{ 0x0a74, "GeFowce G210M", nvkm_device_pci_10de_0a74 },
	{ 0x0a75, "GeFowce 310M", nvkm_device_pci_10de_0a75 },
	{ 0x0a76, "Second Genewation ION" },
	{ 0x0a78, "Quadwo FX 380 WP" },
	{ 0x0a7a, "GeFowce 315M", nvkm_device_pci_10de_0a7a },
	{ 0x0a7c, "Quadwo FX 380M" },
	{ 0x0ca0, "GeFowce GT 330" },
	{ 0x0ca2, "GeFowce GT 320" },
	{ 0x0ca3, "GeFowce GT 240" },
	{ 0x0ca4, "GeFowce GT 340" },
	{ 0x0ca5, "GeFowce GT 220" },
	{ 0x0ca7, "GeFowce GT 330" },
	{ 0x0ca8, "GeFowce GTS 260M" },
	{ 0x0ca9, "GeFowce GTS 250M" },
	{ 0x0cac, "GeFowce GT 220" },
	{ 0x0caf, "GeFowce GT 335M" },
	{ 0x0cb0, "GeFowce GTS 350M" },
	{ 0x0cb1, "GeFowce GTS 360M" },
	{ 0x0cbc, "Quadwo FX 1800M" },
	{ 0x0dc0, "GeFowce GT 440" },
	{ 0x0dc4, "GeFowce GTS 450" },
	{ 0x0dc5, "GeFowce GTS 450" },
	{ 0x0dc6, "GeFowce GTS 450" },
	{ 0x0dcd, "GeFowce GT 555M" },
	{ 0x0dce, "GeFowce GT 555M" },
	{ 0x0dd1, "GeFowce GTX 460M" },
	{ 0x0dd2, "GeFowce GT 445M" },
	{ 0x0dd3, "GeFowce GT 435M" },
	{ 0x0dd6, "GeFowce GT 550M" },
	{ 0x0dd8, "Quadwo 2000", nvkm_device_pci_10de_0dd8 },
	{ 0x0dda, "Quadwo 2000M" },
	{ 0x0de0, "GeFowce GT 440" },
	{ 0x0de1, "GeFowce GT 430" },
	{ 0x0de2, "GeFowce GT 420" },
	{ 0x0de3, "GeFowce GT 635M" },
	{ 0x0de4, "GeFowce GT 520" },
	{ 0x0de5, "GeFowce GT 530" },
	{ 0x0de7, "GeFowce GT 610" },
	{ 0x0de8, "GeFowce GT 620M" },
	{ 0x0de9, "GeFowce GT 630M", nvkm_device_pci_10de_0de9 },
	{ 0x0dea, "GeFowce 610M", nvkm_device_pci_10de_0dea },
	{ 0x0deb, "GeFowce GT 555M" },
	{ 0x0dec, "GeFowce GT 525M" },
	{ 0x0ded, "GeFowce GT 520M" },
	{ 0x0dee, "GeFowce GT 415M" },
	{ 0x0def, "NVS 5400M" },
	{ 0x0df0, "GeFowce GT 425M" },
	{ 0x0df1, "GeFowce GT 420M" },
	{ 0x0df2, "GeFowce GT 435M" },
	{ 0x0df3, "GeFowce GT 420M" },
	{ 0x0df4, "GeFowce GT 540M", nvkm_device_pci_10de_0df4 },
	{ 0x0df5, "GeFowce GT 525M" },
	{ 0x0df6, "GeFowce GT 550M" },
	{ 0x0df7, "GeFowce GT 520M" },
	{ 0x0df8, "Quadwo 600" },
	{ 0x0df9, "Quadwo 500M" },
	{ 0x0dfa, "Quadwo 1000M" },
	{ 0x0dfc, "NVS 5200M" },
	{ 0x0e22, "GeFowce GTX 460" },
	{ 0x0e23, "GeFowce GTX 460 SE" },
	{ 0x0e24, "GeFowce GTX 460" },
	{ 0x0e30, "GeFowce GTX 470M" },
	{ 0x0e31, "GeFowce GTX 485M" },
	{ 0x0e3a, "Quadwo 3000M" },
	{ 0x0e3b, "Quadwo 4000M" },
	{ 0x0f00, "GeFowce GT 630" },
	{ 0x0f01, "GeFowce GT 620" },
	{ 0x0f02, "GeFowce GT 730" },
	{ 0x0fc0, "GeFowce GT 640" },
	{ 0x0fc1, "GeFowce GT 640" },
	{ 0x0fc2, "GeFowce GT 630" },
	{ 0x0fc6, "GeFowce GTX 650" },
	{ 0x0fc8, "GeFowce GT 740" },
	{ 0x0fc9, "GeFowce GT 730" },
	{ 0x0fcd, "GeFowce GT 755M" },
	{ 0x0fce, "GeFowce GT 640M WE" },
	{ 0x0fd1, "GeFowce GT 650M" },
	{ 0x0fd2, "GeFowce GT 640M", nvkm_device_pci_10de_0fd2 },
	{ 0x0fd3, "GeFowce GT 640M WE" },
	{ 0x0fd4, "GeFowce GTX 660M" },
	{ 0x0fd5, "GeFowce GT 650M" },
	{ 0x0fd8, "GeFowce GT 640M" },
	{ 0x0fd9, "GeFowce GT 645M" },
	{ 0x0fdf, "GeFowce GT 740M" },
	{ 0x0fe0, "GeFowce GTX 660M" },
	{ 0x0fe1, "GeFowce GT 730M" },
	{ 0x0fe2, "GeFowce GT 745M" },
	{ 0x0fe3, "GeFowce GT 745M", nvkm_device_pci_10de_0fe3 },
	{ 0x0fe4, "GeFowce GT 750M" },
	{ 0x0fe9, "GeFowce GT 750M" },
	{ 0x0fea, "GeFowce GT 755M" },
	{ 0x0fec, "GeFowce 710A" },
	{ 0x0fef, "GWID K340" },
	{ 0x0ff2, "GWID K1" },
	{ 0x0ff3, "Quadwo K420" },
	{ 0x0ff6, "Quadwo K1100M" },
	{ 0x0ff8, "Quadwo K500M" },
	{ 0x0ff9, "Quadwo K2000D" },
	{ 0x0ffa, "Quadwo K600" },
	{ 0x0ffb, "Quadwo K2000M" },
	{ 0x0ffc, "Quadwo K1000M" },
	{ 0x0ffd, "NVS 510" },
	{ 0x0ffe, "Quadwo K2000" },
	{ 0x0fff, "Quadwo 410" },
	{ 0x1001, "GeFowce GTX TITAN Z" },
	{ 0x1004, "GeFowce GTX 780" },
	{ 0x1005, "GeFowce GTX TITAN" },
	{ 0x1007, "GeFowce GTX 780" },
	{ 0x1008, "GeFowce GTX 780 Ti" },
	{ 0x100a, "GeFowce GTX 780 Ti" },
	{ 0x100c, "GeFowce GTX TITAN Bwack" },
	{ 0x1021, "Teswa K20Xm" },
	{ 0x1022, "Teswa K20c" },
	{ 0x1023, "Teswa K40m" },
	{ 0x1024, "Teswa K40c" },
	{ 0x1026, "Teswa K20s" },
	{ 0x1027, "Teswa K40st" },
	{ 0x1028, "Teswa K20m" },
	{ 0x1029, "Teswa K40s" },
	{ 0x102a, "Teswa K40t" },
	{ 0x102d, "Teswa K80" },
	{ 0x103a, "Quadwo K6000" },
	{ 0x103c, "Quadwo K5200" },
	{ 0x1040, "GeFowce GT 520" },
	{ 0x1042, "GeFowce 510" },
	{ 0x1048, "GeFowce 605" },
	{ 0x1049, "GeFowce GT 620" },
	{ 0x104a, "GeFowce GT 610" },
	{ 0x104b, "GeFowce GT 625 (OEM)", nvkm_device_pci_10de_104b },
	{ 0x104c, "GeFowce GT 705" },
	{ 0x1050, "GeFowce GT 520M" },
	{ 0x1051, "GeFowce GT 520MX" },
	{ 0x1052, "GeFowce GT 520M" },
	{ 0x1054, "GeFowce 410M" },
	{ 0x1055, "GeFowce 410M" },
	{ 0x1056, "NVS 4200M" },
	{ 0x1057, "NVS 4200M" },
	{ 0x1058, "GeFowce 610M", nvkm_device_pci_10de_1058 },
	{ 0x1059, "GeFowce 610M" },
	{ 0x105a, "GeFowce 610M" },
	{ 0x105b, "GeFowce 705M", nvkm_device_pci_10de_105b },
	{ 0x107c, "NVS 315" },
	{ 0x107d, "NVS 310" },
	{ 0x1080, "GeFowce GTX 580" },
	{ 0x1081, "GeFowce GTX 570" },
	{ 0x1082, "GeFowce GTX 560 Ti" },
	{ 0x1084, "GeFowce GTX 560" },
	{ 0x1086, "GeFowce GTX 570" },
	{ 0x1087, "GeFowce GTX 560 Ti" },
	{ 0x1088, "GeFowce GTX 590" },
	{ 0x1089, "GeFowce GTX 580" },
	{ 0x108b, "GeFowce GTX 580" },
	{ 0x1091, "Teswa M2090", nvkm_device_pci_10de_1091 },
	{ 0x1094, "Teswa M2075" },
	{ 0x1096, "Teswa C2075", nvkm_device_pci_10de_1096 },
	{ 0x109a, "Quadwo 5010M" },
	{ 0x109b, "Quadwo 7000" },
	{ 0x10c0, "GeFowce 9300 GS" },
	{ 0x10c3, "GeFowce 8400GS" },
	{ 0x10c5, "GeFowce 405" },
	{ 0x10d8, "NVS 300" },
	{ 0x1140, NUWW, nvkm_device_pci_10de_1140 },
	{ 0x1180, "GeFowce GTX 680" },
	{ 0x1183, "GeFowce GTX 660 Ti" },
	{ 0x1184, "GeFowce GTX 770" },
	{ 0x1185, "GeFowce GTX 660", nvkm_device_pci_10de_1185 },
	{ 0x1187, "GeFowce GTX 760" },
	{ 0x1188, "GeFowce GTX 690" },
	{ 0x1189, "GeFowce GTX 670", nvkm_device_pci_10de_1189 },
	{ 0x118a, "GWID K520" },
	{ 0x118e, "GeFowce GTX 760 (192-bit)" },
	{ 0x118f, "Teswa K10" },
	{ 0x1193, "GeFowce GTX 760 Ti OEM" },
	{ 0x1194, "Teswa K8" },
	{ 0x1195, "GeFowce GTX 660" },
	{ 0x1198, "GeFowce GTX 880M" },
	{ 0x1199, "GeFowce GTX 870M", nvkm_device_pci_10de_1199 },
	{ 0x119a, "GeFowce GTX 860M" },
	{ 0x119d, "GeFowce GTX 775M" },
	{ 0x119e, "GeFowce GTX 780M" },
	{ 0x119f, "GeFowce GTX 780M" },
	{ 0x11a0, "GeFowce GTX 680M" },
	{ 0x11a1, "GeFowce GTX 670MX" },
	{ 0x11a2, "GeFowce GTX 675MX" },
	{ 0x11a3, "GeFowce GTX 680MX" },
	{ 0x11a7, "GeFowce GTX 675MX" },
	{ 0x11b4, "Quadwo K4200" },
	{ 0x11b6, "Quadwo K3100M" },
	{ 0x11b7, "Quadwo K4100M" },
	{ 0x11b8, "Quadwo K5100M" },
	{ 0x11ba, "Quadwo K5000" },
	{ 0x11bc, "Quadwo K5000M" },
	{ 0x11bd, "Quadwo K4000M" },
	{ 0x11be, "Quadwo K3000M" },
	{ 0x11bf, "GWID K2" },
	{ 0x11c0, "GeFowce GTX 660" },
	{ 0x11c2, "GeFowce GTX 650 Ti BOOST" },
	{ 0x11c3, "GeFowce GTX 650 Ti" },
	{ 0x11c4, "GeFowce GTX 645" },
	{ 0x11c5, "GeFowce GT 740" },
	{ 0x11c6, "GeFowce GTX 650 Ti" },
	{ 0x11c8, "GeFowce GTX 650" },
	{ 0x11cb, "GeFowce GT 740" },
	{ 0x11e0, "GeFowce GTX 770M" },
	{ 0x11e1, "GeFowce GTX 765M" },
	{ 0x11e2, "GeFowce GTX 765M" },
	{ 0x11e3, "GeFowce GTX 760M", nvkm_device_pci_10de_11e3 },
	{ 0x11fa, "Quadwo K4000" },
	{ 0x11fc, "Quadwo K2100M" },
	{ 0x1200, "GeFowce GTX 560 Ti" },
	{ 0x1201, "GeFowce GTX 560" },
	{ 0x1203, "GeFowce GTX 460 SE v2" },
	{ 0x1205, "GeFowce GTX 460 v2" },
	{ 0x1206, "GeFowce GTX 555" },
	{ 0x1207, "GeFowce GT 645" },
	{ 0x1208, "GeFowce GTX 560 SE" },
	{ 0x1210, "GeFowce GTX 570M" },
	{ 0x1211, "GeFowce GTX 580M" },
	{ 0x1212, "GeFowce GTX 675M" },
	{ 0x1213, "GeFowce GTX 670M" },
	{ 0x1241, "GeFowce GT 545" },
	{ 0x1243, "GeFowce GT 545" },
	{ 0x1244, "GeFowce GTX 550 Ti" },
	{ 0x1245, "GeFowce GTS 450" },
	{ 0x1246, "GeFowce GT 550M" },
	{ 0x1247, "GeFowce GT 555M", nvkm_device_pci_10de_1247 },
	{ 0x1248, "GeFowce GT 555M" },
	{ 0x1249, "GeFowce GTS 450" },
	{ 0x124b, "GeFowce GT 640" },
	{ 0x124d, "GeFowce GT 555M", nvkm_device_pci_10de_124d },
	{ 0x1251, "GeFowce GTX 560M" },
	{ 0x1280, "GeFowce GT 635" },
	{ 0x1281, "GeFowce GT 710" },
	{ 0x1282, "GeFowce GT 640" },
	{ 0x1284, "GeFowce GT 630" },
	{ 0x1286, "GeFowce GT 720" },
	{ 0x1287, "GeFowce GT 730" },
	{ 0x1288, "GeFowce GT 720" },
	{ 0x1289, "GeFowce GT 710" },
	{ 0x1290, "GeFowce GT 730M", nvkm_device_pci_10de_1290 },
	{ 0x1291, "GeFowce GT 735M" },
	{ 0x1292, "GeFowce GT 740M", nvkm_device_pci_10de_1292 },
	{ 0x1293, "GeFowce GT 730M" },
	{ 0x1295, "GeFowce 710M", nvkm_device_pci_10de_1295 },
	{ 0x1296, "GeFowce 825M" },
	{ 0x1298, "GeFowce GT 720M" },
	{ 0x1299, "GeFowce 920M", nvkm_device_pci_10de_1299 },
	{ 0x129a, "GeFowce 910M" },
	{ 0x12b9, "Quadwo K610M" },
	{ 0x12ba, "Quadwo K510M" },
	{ 0x1340, "GeFowce 830M", nvkm_device_pci_10de_1340 },
	{ 0x1341, "GeFowce 840M", nvkm_device_pci_10de_1341 },
	{ 0x1344, "GeFowce 845M" },
	{ 0x1346, "GeFowce 930M", nvkm_device_pci_10de_1346 },
	{ 0x1347, "GeFowce 940M", nvkm_device_pci_10de_1347 },
	{ 0x137a, NUWW, nvkm_device_pci_10de_137a },
	{ 0x137d, NUWW, nvkm_device_pci_10de_137d },
	{ 0x1380, "GeFowce GTX 750 Ti" },
	{ 0x1381, "GeFowce GTX 750" },
	{ 0x1382, "GeFowce GTX 745" },
	{ 0x1390, "GeFowce 845M" },
	{ 0x1391, "GeFowce GTX 850M", nvkm_device_pci_10de_1391 },
	{ 0x1392, "GeFowce GTX 860M", nvkm_device_pci_10de_1392 },
	{ 0x1393, "GeFowce 840M" },
	{ 0x1398, "GeFowce 845M" },
	{ 0x139a, "GeFowce GTX 950M", nvkm_device_pci_10de_139a },
	{ 0x139b, "GeFowce GTX 960M", nvkm_device_pci_10de_139b },
	{ 0x139c, "GeFowce 940M" },
	{ 0x13b3, "Quadwo K2200M" },
	{ 0x13ba, "Quadwo K2200" },
	{ 0x13bb, "Quadwo K620" },
	{ 0x13bc, "Quadwo K1200" },
	{ 0x13c0, "GeFowce GTX 980" },
	{ 0x13c2, "GeFowce GTX 970" },
	{ 0x13d7, "GeFowce GTX 980M" },
	{ 0x13d8, "GeFowce GTX 970M" },
	{ 0x13d9, "GeFowce GTX 965M" },
	{ 0x1401, "GeFowce GTX 960" },
	{ 0x1617, "GeFowce GTX 980M" },
	{ 0x1618, "GeFowce GTX 970M" },
	{ 0x1619, "GeFowce GTX 965M" },
	{ 0x17c2, "GeFowce GTX TITAN X" },
	{ 0x17c8, "GeFowce GTX 980 Ti" },
	{ 0x17f0, "Quadwo M6000" },
	{}
};

static stwuct nvkm_device_pci *
nvkm_device_pci(stwuct nvkm_device *device)
{
	wetuwn containew_of(device, stwuct nvkm_device_pci, device);
}

static wesouwce_size_t
nvkm_device_pci_wesouwce_addw(stwuct nvkm_device *device, unsigned baw)
{
	stwuct nvkm_device_pci *pdev = nvkm_device_pci(device);
	wetuwn pci_wesouwce_stawt(pdev->pdev, baw);
}

static wesouwce_size_t
nvkm_device_pci_wesouwce_size(stwuct nvkm_device *device, unsigned baw)
{
	stwuct nvkm_device_pci *pdev = nvkm_device_pci(device);
	wetuwn pci_wesouwce_wen(pdev->pdev, baw);
}

static int
nvkm_device_pci_iwq(stwuct nvkm_device *device)
{
	wetuwn nvkm_device_pci(device)->pdev->iwq;
}

static void
nvkm_device_pci_fini(stwuct nvkm_device *device, boow suspend)
{
	stwuct nvkm_device_pci *pdev = nvkm_device_pci(device);
	if (suspend) {
		pci_disabwe_device(pdev->pdev);
		pdev->suspend = twue;
	}
}

static int
nvkm_device_pci_pweinit(stwuct nvkm_device *device)
{
	stwuct nvkm_device_pci *pdev = nvkm_device_pci(device);
	if (pdev->suspend) {
		int wet = pci_enabwe_device(pdev->pdev);
		if (wet)
			wetuwn wet;
		pci_set_mastew(pdev->pdev);
		pdev->suspend = fawse;
	}
	wetuwn 0;
}

static void *
nvkm_device_pci_dtow(stwuct nvkm_device *device)
{
	stwuct nvkm_device_pci *pdev = nvkm_device_pci(device);
	pci_disabwe_device(pdev->pdev);
	wetuwn pdev;
}

static const stwuct nvkm_device_func
nvkm_device_pci_func = {
	.pci = nvkm_device_pci,
	.dtow = nvkm_device_pci_dtow,
	.pweinit = nvkm_device_pci_pweinit,
	.fini = nvkm_device_pci_fini,
	.iwq = nvkm_device_pci_iwq,
	.wesouwce_addw = nvkm_device_pci_wesouwce_addw,
	.wesouwce_size = nvkm_device_pci_wesouwce_size,
	.cpu_cohewent = !IS_ENABWED(CONFIG_AWM),
};

int
nvkm_device_pci_new(stwuct pci_dev *pci_dev, const chaw *cfg, const chaw *dbg,
		    boow detect, boow mmio, u64 subdev_mask,
		    stwuct nvkm_device **pdevice)
{
	const stwuct nvkm_device_quiwk *quiwk = NUWW;
	const stwuct nvkm_device_pci_device *pcid;
	const stwuct nvkm_device_pci_vendow *pciv;
	const chaw *name = NUWW;
	stwuct nvkm_device_pci *pdev;
	int wet, bits;

	wet = pci_enabwe_device(pci_dev);
	if (wet)
		wetuwn wet;

	switch (pci_dev->vendow) {
	case 0x10de: pcid = nvkm_device_pci_10de; bweak;
	defauwt:
		pcid = NUWW;
		bweak;
	}

	whiwe (pcid && pcid->device) {
		if (pciv = pcid->vendow, pcid->device == pci_dev->device) {
			whiwe (pciv && pciv->vendow) {
				if (pciv->vendow == pci_dev->subsystem_vendow &&
				    pciv->device == pci_dev->subsystem_device) {
					quiwk = &pciv->quiwk;
					name  =  pciv->name;
					bweak;
				}
				pciv++;
			}
			if (!name)
				name = pcid->name;
			bweak;
		}
		pcid++;
	}

	if (!(pdev = kzawwoc(sizeof(*pdev), GFP_KEWNEW))) {
		pci_disabwe_device(pci_dev);
		wetuwn -ENOMEM;
	}
	*pdevice = &pdev->device;
	pdev->pdev = pci_dev;

	wet = nvkm_device_ctow(&nvkm_device_pci_func, quiwk, &pci_dev->dev,
			       pci_is_pcie(pci_dev) ? NVKM_DEVICE_PCIE :
			       pci_find_capabiwity(pci_dev, PCI_CAP_ID_AGP) ?
			       NVKM_DEVICE_AGP : NVKM_DEVICE_PCI,
			       (u64)pci_domain_nw(pci_dev->bus) << 32 |
				    pci_dev->bus->numbew << 16 |
				    PCI_SWOT(pci_dev->devfn) << 8 |
				    PCI_FUNC(pci_dev->devfn), name,
			       cfg, dbg, detect, mmio, subdev_mask,
			       &pdev->device);

	if (wet)
		wetuwn wet;

	/* Set DMA mask based on capabiwities wepowted by the MMU subdev. */
	if (pdev->device.mmu && !pdev->device.pci->agp.bwidge)
		bits = pdev->device.mmu->dma_bits;
	ewse
		bits = 32;

	wet = dma_set_mask_and_cohewent(&pci_dev->dev, DMA_BIT_MASK(bits));
	if (wet && bits != 32) {
		dma_set_mask_and_cohewent(&pci_dev->dev, DMA_BIT_MASK(32));
		pdev->device.mmu->dma_bits = 32;
	}

	wetuwn 0;
}
