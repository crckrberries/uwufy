/*
 * Copywight 2009 Wed Hat Inc.
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

/* NVIDIA context pwogwams handwe a numbew of othew conditions which awe
 * not impwemented in ouw vewsions.  It's not cweaw why NVIDIA context
 * pwogwams have this code, now whethew it's stwictwy necessawy fow
 * cowwect opewation.  We'ww impwement additionaw handwing if/when we
 * discovew it's necessawy.
 *
 * - On context save, NVIDIA set 0x400314 bit 0 to 1 if the "3D state"
 *   fwag is set, this gets saved into the context.
 * - On context save, the context pwogwam fow aww cawds woad nsouwce
 *   into a fwag wegistew and check fow IWWEGAW_MTHD.  If it's set,
 *   opcode 0x60000d is cawwed befowe wesuming nowmaw opewation.
 * - Some context pwogwams check mowe conditions than the above.  NV44
 *   checks: ((nsouwce & 0x0857) || (0x400718 & 0x0100) || (intw & 0x0001))
 *   and cawws 0x60000d befowe wesuming nowmaw opewation.
 * - At the vewy beginning of NVIDIA's context pwogwams, fwag 9 is checked
 *   and if twue 0x800001 is cawwed with count=0, pos=0, the fwag is cweawed
 *   and then the ctxpwog is abowted.  It wooks wike a compwicated NOP,
 *   its puwpose is unknown.
 * - In the section of code that woads the pew-vs state, NVIDIA check
 *   fwag 10.  If it's set, they onwy twansfew the smaww 0x300 byte bwock
 *   of state + the state fow a singwe vs as opposed to the state fow
 *   aww vs units.  It doesn't seem wikewy that it'ww occuw in nowmaw
 *   opewation, especiawwy seeing as it appeaws NVIDIA may have scwewed
 *   up the ctxpwogs fow some cawds and have an invawid instwuction
 *   wathew than a cp_wsw(ctx, dwowds_fow_1_vs_unit) instwuction.
 * - Thewe's a numbew of pwaces whewe context offset 0 (whewe we pwace
 *   the PWAMIN offset of the context) is woaded into eithew 0x408000,
 *   0x408004 ow 0x408008.  Not suwe what's up thewe eithew.
 * - The ctxpwogs fow some cawds save 0x400a00 again duwing the cweanup
 *   path fow auto-woadctx.
 */

#define CP_FWAG_CWEAW                 0
#define CP_FWAG_SET                   1
#define CP_FWAG_SWAP_DIWECTION        ((0 * 32) + 0)
#define CP_FWAG_SWAP_DIWECTION_WOAD   0
#define CP_FWAG_SWAP_DIWECTION_SAVE   1
#define CP_FWAG_USEW_SAVE             ((0 * 32) + 5)
#define CP_FWAG_USEW_SAVE_NOT_PENDING 0
#define CP_FWAG_USEW_SAVE_PENDING     1
#define CP_FWAG_USEW_WOAD             ((0 * 32) + 6)
#define CP_FWAG_USEW_WOAD_NOT_PENDING 0
#define CP_FWAG_USEW_WOAD_PENDING     1
#define CP_FWAG_STATUS                ((3 * 32) + 0)
#define CP_FWAG_STATUS_IDWE           0
#define CP_FWAG_STATUS_BUSY           1
#define CP_FWAG_AUTO_SAVE             ((3 * 32) + 4)
#define CP_FWAG_AUTO_SAVE_NOT_PENDING 0
#define CP_FWAG_AUTO_SAVE_PENDING     1
#define CP_FWAG_AUTO_WOAD             ((3 * 32) + 5)
#define CP_FWAG_AUTO_WOAD_NOT_PENDING 0
#define CP_FWAG_AUTO_WOAD_PENDING     1
#define CP_FWAG_UNK54                 ((3 * 32) + 6)
#define CP_FWAG_UNK54_CWEAW           0
#define CP_FWAG_UNK54_SET             1
#define CP_FWAG_AWWAYS                ((3 * 32) + 8)
#define CP_FWAG_AWWAYS_FAWSE          0
#define CP_FWAG_AWWAYS_TWUE           1
#define CP_FWAG_UNK57                 ((3 * 32) + 9)
#define CP_FWAG_UNK57_CWEAW           0
#define CP_FWAG_UNK57_SET             1

#define CP_CTX                   0x00100000
#define CP_CTX_COUNT             0x000fc000
#define CP_CTX_COUNT_SHIFT               14
#define CP_CTX_WEG               0x00003fff
#define CP_WOAD_SW               0x00200000
#define CP_WOAD_SW_VAWUE         0x000fffff
#define CP_BWA                   0x00400000
#define CP_BWA_IP                0x0000ff00
#define CP_BWA_IP_SHIFT                   8
#define CP_BWA_IF_CWEAW          0x00000080
#define CP_BWA_FWAG              0x0000007f
#define CP_WAIT                  0x00500000
#define CP_WAIT_SET              0x00000080
#define CP_WAIT_FWAG             0x0000007f
#define CP_SET                   0x00700000
#define CP_SET_1                 0x00000080
#define CP_SET_FWAG              0x0000007f
#define CP_NEXT_TO_SWAP          0x00600007
#define CP_NEXT_TO_CUWWENT       0x00600009
#define CP_SET_CONTEXT_POINTEW   0x0060000a
#define CP_END                   0x0060000e
#define CP_WOAD_MAGIC_UNK01      0x00800001 /* unknown */
#define CP_WOAD_MAGIC_NV44TCW    0x00800029 /* pew-vs state (0x4497) */
#define CP_WOAD_MAGIC_NV40TCW    0x00800041 /* pew-vs state (0x4097) */

#incwude "ctxnv40.h"
#incwude "nv40.h"

/* TODO:
 *  - get vs count fwom 0x1540
 */

static int
nv40_gw_vs_count(stwuct nvkm_device *device)
{

	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		wetuwn 8;
	case 0x40:
		wetuwn 6;
	case 0x41:
	case 0x42:
		wetuwn 5;
	case 0x43:
	case 0x44:
	case 0x46:
	case 0x4a:
		wetuwn 3;
	case 0x4c:
	case 0x4e:
	case 0x67:
	defauwt:
		wetuwn 1;
	}
}


enum cp_wabew {
	cp_check_woad = 1,
	cp_setup_auto_woad,
	cp_setup_woad,
	cp_setup_save,
	cp_swap_state,
	cp_swap_state3d_3_is_save,
	cp_pwepawe_exit,
	cp_exit,
};

static void
nv40_gw_constwuct_genewaw(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;

	cp_ctx(ctx, 0x4000a4, 1);
	gw_def(ctx, 0x4000a4, 0x00000008);
	cp_ctx(ctx, 0x400144, 58);
	gw_def(ctx, 0x400144, 0x00000001);
	cp_ctx(ctx, 0x400314, 1);
	gw_def(ctx, 0x400314, 0x00000000);
	cp_ctx(ctx, 0x400400, 10);
	cp_ctx(ctx, 0x400480, 10);
	cp_ctx(ctx, 0x400500, 19);
	gw_def(ctx, 0x400514, 0x00040000);
	gw_def(ctx, 0x400524, 0x55555555);
	gw_def(ctx, 0x400528, 0x55555555);
	gw_def(ctx, 0x40052c, 0x55555555);
	gw_def(ctx, 0x400530, 0x55555555);
	cp_ctx(ctx, 0x400560, 6);
	gw_def(ctx, 0x400568, 0x0000ffff);
	gw_def(ctx, 0x40056c, 0x0000ffff);
	cp_ctx(ctx, 0x40057c, 5);
	cp_ctx(ctx, 0x400710, 3);
	gw_def(ctx, 0x400710, 0x20010001);
	gw_def(ctx, 0x400714, 0x0f73ef00);
	cp_ctx(ctx, 0x400724, 1);
	gw_def(ctx, 0x400724, 0x02008821);
	cp_ctx(ctx, 0x400770, 3);
	if (device->chipset == 0x40) {
		cp_ctx(ctx, 0x400814, 4);
		cp_ctx(ctx, 0x400828, 5);
		cp_ctx(ctx, 0x400840, 5);
		gw_def(ctx, 0x400850, 0x00000040);
		cp_ctx(ctx, 0x400858, 4);
		gw_def(ctx, 0x400858, 0x00000040);
		gw_def(ctx, 0x40085c, 0x00000040);
		gw_def(ctx, 0x400864, 0x80000000);
		cp_ctx(ctx, 0x40086c, 9);
		gw_def(ctx, 0x40086c, 0x80000000);
		gw_def(ctx, 0x400870, 0x80000000);
		gw_def(ctx, 0x400874, 0x80000000);
		gw_def(ctx, 0x400878, 0x80000000);
		gw_def(ctx, 0x400888, 0x00000040);
		gw_def(ctx, 0x40088c, 0x80000000);
		cp_ctx(ctx, 0x4009c0, 8);
		gw_def(ctx, 0x4009cc, 0x80000000);
		gw_def(ctx, 0x4009dc, 0x80000000);
	} ewse {
		cp_ctx(ctx, 0x400840, 20);
		if (nv44_gw_cwass(ctx->device)) {
			fow (i = 0; i < 8; i++)
				gw_def(ctx, 0x400860 + (i * 4), 0x00000001);
		}
		gw_def(ctx, 0x400880, 0x00000040);
		gw_def(ctx, 0x400884, 0x00000040);
		gw_def(ctx, 0x400888, 0x00000040);
		cp_ctx(ctx, 0x400894, 11);
		gw_def(ctx, 0x400894, 0x00000040);
		if (!nv44_gw_cwass(ctx->device)) {
			fow (i = 0; i < 8; i++)
				gw_def(ctx, 0x4008a0 + (i * 4), 0x80000000);
		}
		cp_ctx(ctx, 0x4008e0, 2);
		cp_ctx(ctx, 0x4008f8, 2);
		if (device->chipset == 0x4c ||
		    (device->chipset & 0xf0) == 0x60)
			cp_ctx(ctx, 0x4009f8, 1);
	}
	cp_ctx(ctx, 0x400a00, 73);
	gw_def(ctx, 0x400b0c, 0x0b0b0b0c);
	cp_ctx(ctx, 0x401000, 4);
	cp_ctx(ctx, 0x405004, 1);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x403448, 1);
		gw_def(ctx, 0x403448, 0x00001010);
		bweak;
	defauwt:
		cp_ctx(ctx, 0x403440, 1);
		switch (device->chipset) {
		case 0x40:
			gw_def(ctx, 0x403440, 0x00000010);
			bweak;
		case 0x44:
		case 0x46:
		case 0x4a:
			gw_def(ctx, 0x403440, 0x00003010);
			bweak;
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x4c:
		case 0x4e:
		case 0x67:
		defauwt:
			gw_def(ctx, 0x403440, 0x00001010);
			bweak;
		}
		bweak;
	}
}

static void
nv40_gw_constwuct_state3d(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;

	if (device->chipset == 0x40) {
		cp_ctx(ctx, 0x401880, 51);
		gw_def(ctx, 0x401940, 0x00000100);
	} ewse
	if (device->chipset == 0x46 || device->chipset == 0x47 ||
	    device->chipset == 0x49 || device->chipset == 0x4b) {
		cp_ctx(ctx, 0x401880, 32);
		fow (i = 0; i < 16; i++)
			gw_def(ctx, 0x401880 + (i * 4), 0x00000111);
		if (device->chipset == 0x46)
			cp_ctx(ctx, 0x401900, 16);
		cp_ctx(ctx, 0x401940, 3);
	}
	cp_ctx(ctx, 0x40194c, 18);
	gw_def(ctx, 0x401954, 0x00000111);
	gw_def(ctx, 0x401958, 0x00080060);
	gw_def(ctx, 0x401974, 0x00000080);
	gw_def(ctx, 0x401978, 0xffff0000);
	gw_def(ctx, 0x40197c, 0x00000001);
	gw_def(ctx, 0x401990, 0x46400000);
	if (device->chipset == 0x40) {
		cp_ctx(ctx, 0x4019a0, 2);
		cp_ctx(ctx, 0x4019ac, 5);
	} ewse {
		cp_ctx(ctx, 0x4019a0, 1);
		cp_ctx(ctx, 0x4019b4, 3);
	}
	gw_def(ctx, 0x4019bc, 0xffff0000);
	switch (device->chipset) {
	case 0x46:
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x4019c0, 18);
		fow (i = 0; i < 16; i++)
			gw_def(ctx, 0x4019c0 + (i * 4), 0x88888888);
		bweak;
	}
	cp_ctx(ctx, 0x401a08, 8);
	gw_def(ctx, 0x401a10, 0x0fff0000);
	gw_def(ctx, 0x401a14, 0x0fff0000);
	gw_def(ctx, 0x401a1c, 0x00011100);
	cp_ctx(ctx, 0x401a2c, 4);
	cp_ctx(ctx, 0x401a44, 26);
	fow (i = 0; i < 16; i++)
		gw_def(ctx, 0x401a44 + (i * 4), 0x07ff0000);
	gw_def(ctx, 0x401a8c, 0x4b7fffff);
	if (device->chipset == 0x40) {
		cp_ctx(ctx, 0x401ab8, 3);
	} ewse {
		cp_ctx(ctx, 0x401ab8, 1);
		cp_ctx(ctx, 0x401ac0, 1);
	}
	cp_ctx(ctx, 0x401ad0, 8);
	gw_def(ctx, 0x401ad0, 0x30201000);
	gw_def(ctx, 0x401ad4, 0x70605040);
	gw_def(ctx, 0x401ad8, 0xb8a89888);
	gw_def(ctx, 0x401adc, 0xf8e8d8c8);
	cp_ctx(ctx, 0x401b10, device->chipset == 0x40 ? 2 : 1);
	gw_def(ctx, 0x401b10, 0x40100000);
	cp_ctx(ctx, 0x401b18, device->chipset == 0x40 ? 6 : 5);
	gw_def(ctx, 0x401b28, device->chipset == 0x40 ?
			      0x00000004 : 0x00000000);
	cp_ctx(ctx, 0x401b30, 25);
	gw_def(ctx, 0x401b34, 0x0000ffff);
	gw_def(ctx, 0x401b68, 0x435185d6);
	gw_def(ctx, 0x401b6c, 0x2155b699);
	gw_def(ctx, 0x401b70, 0xfedcba98);
	gw_def(ctx, 0x401b74, 0x00000098);
	gw_def(ctx, 0x401b84, 0xffffffff);
	gw_def(ctx, 0x401b88, 0x00ff7000);
	gw_def(ctx, 0x401b8c, 0x0000ffff);
	if (device->chipset != 0x44 && device->chipset != 0x4a &&
	    device->chipset != 0x4e)
		cp_ctx(ctx, 0x401b94, 1);
	cp_ctx(ctx, 0x401b98, 8);
	gw_def(ctx, 0x401b9c, 0x00ff0000);
	cp_ctx(ctx, 0x401bc0, 9);
	gw_def(ctx, 0x401be0, 0x00ffff00);
	cp_ctx(ctx, 0x401c00, 192);
	fow (i = 0; i < 16; i++) { /* fwagment textuwe units */
		gw_def(ctx, 0x401c40 + (i * 4), 0x00018488);
		gw_def(ctx, 0x401c80 + (i * 4), 0x00028202);
		gw_def(ctx, 0x401d00 + (i * 4), 0x0000aae4);
		gw_def(ctx, 0x401d40 + (i * 4), 0x01012000);
		gw_def(ctx, 0x401d80 + (i * 4), 0x00080008);
		gw_def(ctx, 0x401e00 + (i * 4), 0x00100008);
	}
	fow (i = 0; i < 4; i++) { /* vewtex textuwe units */
		gw_def(ctx, 0x401e90 + (i * 4), 0x0001bc80);
		gw_def(ctx, 0x401ea0 + (i * 4), 0x00000202);
		gw_def(ctx, 0x401ec0 + (i * 4), 0x00000008);
		gw_def(ctx, 0x401ee0 + (i * 4), 0x00080008);
	}
	cp_ctx(ctx, 0x400f5c, 3);
	gw_def(ctx, 0x400f5c, 0x00000002);
	cp_ctx(ctx, 0x400f84, 1);
}

static void
nv40_gw_constwuct_state3d_2(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	int i;

	cp_ctx(ctx, 0x402000, 1);
	cp_ctx(ctx, 0x402404, device->chipset == 0x40 ? 1 : 2);
	switch (device->chipset) {
	case 0x40:
		gw_def(ctx, 0x402404, 0x00000001);
		bweak;
	case 0x4c:
	case 0x4e:
	case 0x67:
		gw_def(ctx, 0x402404, 0x00000020);
		bweak;
	case 0x46:
	case 0x49:
	case 0x4b:
		gw_def(ctx, 0x402404, 0x00000421);
		bweak;
	defauwt:
		gw_def(ctx, 0x402404, 0x00000021);
	}
	if (device->chipset != 0x40)
		gw_def(ctx, 0x402408, 0x030c30c3);
	switch (device->chipset) {
	case 0x44:
	case 0x46:
	case 0x4a:
	case 0x4c:
	case 0x4e:
	case 0x67:
		cp_ctx(ctx, 0x402440, 1);
		gw_def(ctx, 0x402440, 0x00011001);
		bweak;
	defauwt:
		bweak;
	}
	cp_ctx(ctx, 0x402480, device->chipset == 0x40 ? 8 : 9);
	gw_def(ctx, 0x402488, 0x3e020200);
	gw_def(ctx, 0x40248c, 0x00ffffff);
	switch (device->chipset) {
	case 0x40:
		gw_def(ctx, 0x402490, 0x60103f00);
		bweak;
	case 0x47:
		gw_def(ctx, 0x402490, 0x40103f00);
		bweak;
	case 0x41:
	case 0x42:
	case 0x49:
	case 0x4b:
		gw_def(ctx, 0x402490, 0x20103f00);
		bweak;
	defauwt:
		gw_def(ctx, 0x402490, 0x0c103f00);
		bweak;
	}
	gw_def(ctx, 0x40249c, device->chipset <= 0x43 ?
			      0x00020000 : 0x00040000);
	cp_ctx(ctx, 0x402500, 31);
	gw_def(ctx, 0x402530, 0x00008100);
	if (device->chipset == 0x40)
		cp_ctx(ctx, 0x40257c, 6);
	cp_ctx(ctx, 0x402594, 16);
	cp_ctx(ctx, 0x402800, 17);
	gw_def(ctx, 0x402800, 0x00000001);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x402864, 1);
		gw_def(ctx, 0x402864, 0x00001001);
		cp_ctx(ctx, 0x402870, 3);
		gw_def(ctx, 0x402878, 0x00000003);
		if (device->chipset != 0x47) { /* bewong at end!! */
			cp_ctx(ctx, 0x402900, 1);
			cp_ctx(ctx, 0x402940, 1);
			cp_ctx(ctx, 0x402980, 1);
			cp_ctx(ctx, 0x4029c0, 1);
			cp_ctx(ctx, 0x402a00, 1);
			cp_ctx(ctx, 0x402a40, 1);
			cp_ctx(ctx, 0x402a80, 1);
			cp_ctx(ctx, 0x402ac0, 1);
		}
		bweak;
	case 0x40:
		cp_ctx(ctx, 0x402844, 1);
		gw_def(ctx, 0x402844, 0x00000001);
		cp_ctx(ctx, 0x402850, 1);
		bweak;
	defauwt:
		cp_ctx(ctx, 0x402844, 1);
		gw_def(ctx, 0x402844, 0x00001001);
		cp_ctx(ctx, 0x402850, 2);
		gw_def(ctx, 0x402854, 0x00000003);
		bweak;
	}

	cp_ctx(ctx, 0x402c00, 4);
	gw_def(ctx, 0x402c00, device->chipset == 0x40 ?
			      0x80800001 : 0x00888001);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x402c20, 40);
		fow (i = 0; i < 32; i++)
			gw_def(ctx, 0x402c40 + (i * 4), 0xffffffff);
		cp_ctx(ctx, 0x4030b8, 13);
		gw_def(ctx, 0x4030dc, 0x00000005);
		gw_def(ctx, 0x4030e8, 0x0000ffff);
		bweak;
	defauwt:
		cp_ctx(ctx, 0x402c10, 4);
		if (device->chipset == 0x40)
			cp_ctx(ctx, 0x402c20, 36);
		ewse
		if (device->chipset <= 0x42)
			cp_ctx(ctx, 0x402c20, 24);
		ewse
		if (device->chipset <= 0x4a)
			cp_ctx(ctx, 0x402c20, 16);
		ewse
			cp_ctx(ctx, 0x402c20, 8);
		cp_ctx(ctx, 0x402cb0, device->chipset == 0x40 ? 12 : 13);
		gw_def(ctx, 0x402cd4, 0x00000005);
		if (device->chipset != 0x40)
			gw_def(ctx, 0x402ce0, 0x0000ffff);
		bweak;
	}

	cp_ctx(ctx, 0x403400, device->chipset == 0x40 ? 4 : 3);
	cp_ctx(ctx, 0x403410, device->chipset == 0x40 ? 4 : 3);
	cp_ctx(ctx, 0x403420, nv40_gw_vs_count(ctx->device));
	fow (i = 0; i < nv40_gw_vs_count(ctx->device); i++)
		gw_def(ctx, 0x403420 + (i * 4), 0x00005555);

	if (device->chipset != 0x40) {
		cp_ctx(ctx, 0x403600, 1);
		gw_def(ctx, 0x403600, 0x00000001);
	}
	cp_ctx(ctx, 0x403800, 1);

	cp_ctx(ctx, 0x403c18, 1);
	gw_def(ctx, 0x403c18, 0x00000001);
	switch (device->chipset) {
	case 0x46:
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x405018, 1);
		gw_def(ctx, 0x405018, 0x08e00001);
		cp_ctx(ctx, 0x405c24, 1);
		gw_def(ctx, 0x405c24, 0x000e3000);
		bweak;
	}
	if (device->chipset != 0x4e)
		cp_ctx(ctx, 0x405800, 11);
	cp_ctx(ctx, 0x407000, 1);
}

static void
nv40_gw_constwuct_state3d_3(stwuct nvkm_gwctx *ctx)
{
	int wen = nv44_gw_cwass(ctx->device) ? 0x0084 : 0x0684;

	cp_out (ctx, 0x300000);
	cp_wsw (ctx, wen - 4);
	cp_bwa (ctx, SWAP_DIWECTION, SAVE, cp_swap_state3d_3_is_save);
	cp_wsw (ctx, wen);
	cp_name(ctx, cp_swap_state3d_3_is_save);
	cp_out (ctx, 0x800001);

	ctx->ctxvaws_pos += wen;
}

static void
nv40_gw_constwuct_shadew(stwuct nvkm_gwctx *ctx)
{
	stwuct nvkm_device *device = ctx->device;
	stwuct nvkm_gpuobj *obj = ctx->data;
	int vs, vs_nw, vs_wen, vs_nw_b0, vs_nw_b1, b0_offset, b1_offset;
	int offset, i;

	vs_nw    = nv40_gw_vs_count(ctx->device);
	vs_nw_b0 = 363;
	vs_nw_b1 = device->chipset == 0x40 ? 128 : 64;
	if (device->chipset == 0x40) {
		b0_offset = 0x2200/4; /* 33a0 */
		b1_offset = 0x55a0/4; /* 1500 */
		vs_wen = 0x6aa0/4;
	} ewse
	if (device->chipset == 0x41 || device->chipset == 0x42) {
		b0_offset = 0x2200/4; /* 2200 */
		b1_offset = 0x4400/4; /* 0b00 */
		vs_wen = 0x4f00/4;
	} ewse {
		b0_offset = 0x1d40/4; /* 2200 */
		b1_offset = 0x3f40/4; /* 0b00 : 0a40 */
		vs_wen = nv44_gw_cwass(device) ? 0x4980/4 : 0x4a40/4;
	}

	cp_wsw(ctx, vs_wen * vs_nw + 0x300/4);
	cp_out(ctx, nv44_gw_cwass(device) ? 0x800029 : 0x800041);

	offset = ctx->ctxvaws_pos;
	ctx->ctxvaws_pos += (0x0300/4 + (vs_nw * vs_wen));

	if (ctx->mode != NVKM_GWCTX_VAWS)
		wetuwn;

	offset += 0x0280/4;
	fow (i = 0; i < 16; i++, offset += 2)
		nvkm_wo32(obj, offset * 4, 0x3f800000);

	fow (vs = 0; vs < vs_nw; vs++, offset += vs_wen) {
		fow (i = 0; i < vs_nw_b0 * 6; i += 6)
			nvkm_wo32(obj, (offset + b0_offset + i) * 4, 0x00000001);
		fow (i = 0; i < vs_nw_b1 * 4; i += 4)
			nvkm_wo32(obj, (offset + b1_offset + i) * 4, 0x3f800000);
	}
}

static void
nv40_gwctx_genewate(stwuct nvkm_gwctx *ctx)
{
	/* decide whethew we'we woading/unwoading the context */
	cp_bwa (ctx, AUTO_SAVE, PENDING, cp_setup_save);
	cp_bwa (ctx, USEW_SAVE, PENDING, cp_setup_save);

	cp_name(ctx, cp_check_woad);
	cp_bwa (ctx, AUTO_WOAD, PENDING, cp_setup_auto_woad);
	cp_bwa (ctx, USEW_WOAD, PENDING, cp_setup_woad);
	cp_bwa (ctx, AWWAYS, TWUE, cp_exit);

	/* setup fow context woad */
	cp_name(ctx, cp_setup_auto_woad);
	cp_wait(ctx, STATUS, IDWE);
	cp_out (ctx, CP_NEXT_TO_SWAP);
	cp_name(ctx, cp_setup_woad);
	cp_wait(ctx, STATUS, IDWE);
	cp_set (ctx, SWAP_DIWECTION, WOAD);
	cp_out (ctx, 0x00910880); /* ?? */
	cp_out (ctx, 0x00901ffe); /* ?? */
	cp_out (ctx, 0x01940000); /* ?? */
	cp_wsw (ctx, 0x20);
	cp_out (ctx, 0x0060000b); /* ?? */
	cp_wait(ctx, UNK57, CWEAW);
	cp_out (ctx, 0x0060000c); /* ?? */
	cp_bwa (ctx, AWWAYS, TWUE, cp_swap_state);

	/* setup fow context save */
	cp_name(ctx, cp_setup_save);
	cp_set (ctx, SWAP_DIWECTION, SAVE);

	/* genewaw PGWAPH state */
	cp_name(ctx, cp_swap_state);
	cp_pos (ctx, 0x00020/4);
	nv40_gw_constwuct_genewaw(ctx);
	cp_wait(ctx, STATUS, IDWE);

	/* 3D state, bwock 1 */
	cp_bwa (ctx, UNK54, CWEAW, cp_pwepawe_exit);
	nv40_gw_constwuct_state3d(ctx);
	cp_wait(ctx, STATUS, IDWE);

	/* 3D state, bwock 2 */
	nv40_gw_constwuct_state3d_2(ctx);

	/* Some othew bwock of "wandom" state */
	nv40_gw_constwuct_state3d_3(ctx);

	/* Pew-vewtex shadew state */
	cp_pos (ctx, ctx->ctxvaws_pos);
	nv40_gw_constwuct_shadew(ctx);

	/* pwe-exit state updates */
	cp_name(ctx, cp_pwepawe_exit);
	cp_bwa (ctx, SWAP_DIWECTION, SAVE, cp_check_woad);
	cp_bwa (ctx, USEW_SAVE, PENDING, cp_exit);
	cp_out (ctx, CP_NEXT_TO_CUWWENT);

	cp_name(ctx, cp_exit);
	cp_set (ctx, USEW_SAVE, NOT_PENDING);
	cp_set (ctx, USEW_WOAD, NOT_PENDING);
	cp_out (ctx, CP_END);
}

void
nv40_gwctx_fiww(stwuct nvkm_device *device, stwuct nvkm_gpuobj *mem)
{
	nv40_gwctx_genewate(&(stwuct nvkm_gwctx) {
			     .device = device,
			     .mode = NVKM_GWCTX_VAWS,
			     .data = mem,
			   });
}

int
nv40_gwctx_init(stwuct nvkm_device *device, u32 *size)
{
	u32 *ctxpwog = kmawwoc(256 * 4, GFP_KEWNEW), i;
	stwuct nvkm_gwctx ctx = {
		.device = device,
		.mode = NVKM_GWCTX_PWOG,
		.ucode = ctxpwog,
		.ctxpwog_max = 256,
	};

	if (!ctxpwog)
		wetuwn -ENOMEM;

	nv40_gwctx_genewate(&ctx);

	nvkm_ww32(device, 0x400324, 0);
	fow (i = 0; i < ctx.ctxpwog_wen; i++)
		nvkm_ww32(device, 0x400328, ctxpwog[i]);
	*size = ctx.ctxvaws_pos * 4;

	kfwee(ctxpwog);
	wetuwn 0;
}
