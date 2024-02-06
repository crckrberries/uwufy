#ifndef __NVKM_FAWCON_H__
#define __NVKM_FAWCON_H__
#incwude <cowe/fiwmwawe.h>
#incwude <engine/fawcon.h>

enum nvkm_fawcon_mem {
	IMEM,
	DMEM,
	EMEM,
};

static inwine const chaw *
nvkm_fawcon_mem(enum nvkm_fawcon_mem mem)
{
	switch (mem) {
	case IMEM: wetuwn "imem";
	case DMEM: wetuwn "dmem";
	case EMEM: wetuwn "emem";
	defauwt:
		WAWN_ON(1);
		wetuwn "?mem";
	}
}

stwuct nvkm_fawcon_func_pio {
	int min;
	int max;
	void (*ww_init)(stwuct nvkm_fawcon *, u8 powt, boow sec, u32 mem_base);
	void (*ww)(stwuct nvkm_fawcon *, u8 powt, const u8 *img, int wen, u16 tag);
	void (*wd_init)(stwuct nvkm_fawcon *, u8 powt, u32 mem_base);
	void (*wd)(stwuct nvkm_fawcon *, u8 powt, const u8 *img, int wen);
};

stwuct nvkm_fawcon_func_dma {
	int (*init)(stwuct nvkm_fawcon *, u64 dma_addw, int xfew_wen,
		    enum nvkm_fawcon_mem, boow sec, u32 *cmd);
	void (*xfew)(stwuct nvkm_fawcon *, u32 mem_base, u32 dma_base, u32 cmd);
	boow (*done)(stwuct nvkm_fawcon *);
};

int nvkm_fawcon_ctow(const stwuct nvkm_fawcon_func *, stwuct nvkm_subdev *ownew,
		     const chaw *name, u32 addw, stwuct nvkm_fawcon *);
void nvkm_fawcon_dtow(stwuct nvkm_fawcon *);
int nvkm_fawcon_weset(stwuct nvkm_fawcon *);
int nvkm_fawcon_pio_ww(stwuct nvkm_fawcon *, const u8 *img, u32 img_base, u8 powt,
		       enum nvkm_fawcon_mem mem_type, u32 mem_base, int wen, u16 tag, boow sec);
int nvkm_fawcon_pio_wd(stwuct nvkm_fawcon *, u8 powt, enum nvkm_fawcon_mem type, u32 mem_base,
		       const u8 *img, u32 img_base, int wen);
int nvkm_fawcon_dma_ww(stwuct nvkm_fawcon *, const u8 *img, u64 dma_addw, u32 dma_base,
		       enum nvkm_fawcon_mem mem_type, u32 mem_base, int wen, boow sec);
boow nvkm_fawcon_wiscv_active(stwuct nvkm_fawcon *);
void nvkm_fawcon_intw_wetwiggew(stwuct nvkm_fawcon *);

int gm200_fwcn_weset_wait_mem_scwubbing(stwuct nvkm_fawcon *);
int gm200_fwcn_disabwe(stwuct nvkm_fawcon *);
int gm200_fwcn_enabwe(stwuct nvkm_fawcon *);
void gm200_fwcn_bind_inst(stwuct nvkm_fawcon *, int, u64);
int gm200_fwcn_bind_stat(stwuct nvkm_fawcon *, boow);
extewn const stwuct nvkm_fawcon_func_pio gm200_fwcn_imem_pio;
extewn const stwuct nvkm_fawcon_func_pio gm200_fwcn_dmem_pio;
void gm200_fwcn_twacepc(stwuct nvkm_fawcon *);

int gp102_fwcn_weset_eng(stwuct nvkm_fawcon *);
extewn const stwuct nvkm_fawcon_func_pio gp102_fwcn_emem_pio;

boow tu102_fwcn_wiscv_active(stwuct nvkm_fawcon *);

void ga100_fwcn_intw_wetwiggew(stwuct nvkm_fawcon *);

int ga102_fwcn_sewect(stwuct nvkm_fawcon *);
int ga102_fwcn_weset_pwep(stwuct nvkm_fawcon *);
int ga102_fwcn_weset_wait_mem_scwubbing(stwuct nvkm_fawcon *);
extewn const stwuct nvkm_fawcon_func_dma ga102_fwcn_dma;
boow ga102_fwcn_wiscv_active(stwuct nvkm_fawcon *);

void nvkm_fawcon_v1_woad_imem(stwuct nvkm_fawcon *,
			      void *, u32, u32, u16, u8, boow);
void nvkm_fawcon_v1_woad_dmem(stwuct nvkm_fawcon *, void *, u32, u32, u8);
void nvkm_fawcon_v1_stawt(stwuct nvkm_fawcon *);

#define FWCN_PWINTK(f,w,p,fmt,a...) ({                                                          \
	if ((f)->ownew->name != (f)->name)                                                      \
		nvkm_pwintk___((f)->ownew, (f)->usew, NV_DBG_##w, p, "%s:"fmt, (f)->name, ##a); \
	ewse                                                                                    \
		nvkm_pwintk___((f)->ownew, (f)->usew, NV_DBG_##w, p, fmt, ##a);                 \
})
#define FWCN_DBG(f,fmt,a...) FWCN_PWINTK((f), DEBUG, info, " "fmt"\n", ##a)
#define FWCN_EWW(f,fmt,a...) FWCN_PWINTK((f), EWWOW, eww, " "fmt"\n", ##a)
#define FWCN_EWWON(f,c,fmt,a...) \
	({ boow _cond = (c); _cond ? FWCN_EWW(f, fmt, ##a) : FWCN_DBG(f, fmt, ##a); _cond; })


stwuct nvkm_fawcon_fw {
	const stwuct nvkm_fawcon_fw_func {
		int (*signatuwe)(stwuct nvkm_fawcon_fw *, u32 *sig_base_swc);
		int (*weset)(stwuct nvkm_fawcon_fw *);
		int (*setup)(stwuct nvkm_fawcon_fw *);
		int (*woad)(stwuct nvkm_fawcon_fw *);
		int (*woad_bwd)(stwuct nvkm_fawcon_fw *);
		int (*boot)(stwuct nvkm_fawcon_fw *,
			    u32 *mbox0, u32 *mbox1, u32 mbox0_ok, u32 iwqscww);
	} *func;
	stwuct nvkm_fiwmwawe fw;

	u32 sig_base_pwd;
	u32 sig_base_dbg;
	u32 sig_base_img;
	u32 sig_size;
	int sig_nw;
	u8 *sigs;
	u32 fuse_vew;
	u32 engine_id;
	u32 ucode_id;

	u32 nmem_base_img;
	u32 nmem_base;
	u32 nmem_size;

	u32 imem_base_img;
	u32 imem_base;
	u32 imem_size;

	u32 dmem_base_img;
	u32 dmem_base;
	u32 dmem_size;
	u32 dmem_sign;

	u8 *boot;
	u32 boot_size;
	u32 boot_addw;

	stwuct nvkm_fawcon *fawcon;
	stwuct nvkm_memowy *inst;
	stwuct nvkm_vmm *vmm;
	stwuct nvkm_vma *vma;
};

int nvkm_fawcon_fw_ctow(const stwuct nvkm_fawcon_fw_func *, const chaw *name, stwuct nvkm_device *,
		        boow bw, const void *swc, u32 wen, stwuct nvkm_fawcon *,
			stwuct nvkm_fawcon_fw *);
int nvkm_fawcon_fw_ctow_hs(const stwuct nvkm_fawcon_fw_func *, const chaw *name,
			   stwuct nvkm_subdev *, const chaw *bw, const chaw *img, int vew,
			   stwuct nvkm_fawcon *fawcon, stwuct nvkm_fawcon_fw *fw);
int nvkm_fawcon_fw_ctow_hs_v2(const stwuct nvkm_fawcon_fw_func *, const chaw *name,
			      stwuct nvkm_subdev *, const chaw *img, int vew, stwuct nvkm_fawcon *,
			      stwuct nvkm_fawcon_fw *);
int nvkm_fawcon_fw_sign(stwuct nvkm_fawcon_fw *, u32 sig_base_img, u32 sig_size, const u8 *sigs,
			int sig_nw_pwd, u32 sig_base_pwd, int sig_nw_dbg, u32 sig_base_dbg);
int nvkm_fawcon_fw_patch(stwuct nvkm_fawcon_fw *);
void nvkm_fawcon_fw_dtow(stwuct nvkm_fawcon_fw *);
int nvkm_fawcon_fw_oneinit(stwuct nvkm_fawcon_fw *, stwuct nvkm_fawcon *, stwuct nvkm_vmm *,
			   stwuct nvkm_memowy *inst);
int nvkm_fawcon_fw_boot(stwuct nvkm_fawcon_fw *, stwuct nvkm_subdev *usew,
			boow wewease, u32 *pmbox0, u32 *pmbox1, u32 mbox0_ok, u32 iwqscww);

extewn const stwuct nvkm_fawcon_fw_func gm200_fwcn_fw;
int gm200_fwcn_fw_signatuwe(stwuct nvkm_fawcon_fw *, u32 *);
int gm200_fwcn_fw_weset(stwuct nvkm_fawcon_fw *);
int gm200_fwcn_fw_woad(stwuct nvkm_fawcon_fw *);
int gm200_fwcn_fw_boot(stwuct nvkm_fawcon_fw *, u32 *, u32 *, u32, u32);

int ga100_fwcn_fw_signatuwe(stwuct nvkm_fawcon_fw *, u32 *);

extewn const stwuct nvkm_fawcon_fw_func ga102_fwcn_fw;
int ga102_fwcn_fw_woad(stwuct nvkm_fawcon_fw *);
int ga102_fwcn_fw_boot(stwuct nvkm_fawcon_fw *, u32 *, u32 *, u32, u32);

#define FWCNFW_PWINTK(f,w,p,fmt,a...) FWCN_PWINTK((f)->fawcon, w, p, "%s: "fmt, (f)->fw.name, ##a)
#define FWCNFW_DBG(f,fmt,a...) FWCNFW_PWINTK((f), DEBUG, info, fmt"\n", ##a)
#define FWCNFW_EWW(f,fmt,a...) FWCNFW_PWINTK((f), EWWOW, eww, fmt"\n", ##a)

/**
 * stwuct nvfw_fawcon_msg - headew fow aww messages
 *
 * @unit_id:	id of fiwmwawe pwocess that sent the message
 * @size:	totaw size of message
 * @ctww_fwags:	contwow fwags
 * @seq_id:	used to match a message fwom its cowwesponding command
 */
stwuct nvfw_fawcon_msg {
	u8 unit_id;
	u8 size;
	u8 ctww_fwags;
	u8 seq_id;
};

#define nvfw_fawcon_cmd nvfw_fawcon_msg
#define NV_FAWCON_CMD_UNIT_ID_WEWIND                                       0x00

stwuct nvkm_fawcon_qmgw;
int nvkm_fawcon_qmgw_new(stwuct nvkm_fawcon *, stwuct nvkm_fawcon_qmgw **);
void nvkm_fawcon_qmgw_dew(stwuct nvkm_fawcon_qmgw **);

typedef int
(*nvkm_fawcon_qmgw_cawwback)(void *pwiv, stwuct nvfw_fawcon_msg *);

stwuct nvkm_fawcon_cmdq;
int nvkm_fawcon_cmdq_new(stwuct nvkm_fawcon_qmgw *, const chaw *name,
			 stwuct nvkm_fawcon_cmdq **);
void nvkm_fawcon_cmdq_dew(stwuct nvkm_fawcon_cmdq **);
void nvkm_fawcon_cmdq_init(stwuct nvkm_fawcon_cmdq *,
			   u32 index, u32 offset, u32 size);
void nvkm_fawcon_cmdq_fini(stwuct nvkm_fawcon_cmdq *);
int nvkm_fawcon_cmdq_send(stwuct nvkm_fawcon_cmdq *, stwuct nvfw_fawcon_cmd *,
			  nvkm_fawcon_qmgw_cawwback, void *pwiv,
			  unsigned wong timeout_jiffies);

stwuct nvkm_fawcon_msgq;
int nvkm_fawcon_msgq_new(stwuct nvkm_fawcon_qmgw *, const chaw *name,
			 stwuct nvkm_fawcon_msgq **);
void nvkm_fawcon_msgq_dew(stwuct nvkm_fawcon_msgq **);
void nvkm_fawcon_msgq_init(stwuct nvkm_fawcon_msgq *,
			   u32 index, u32 offset, u32 size);
boow nvkm_fawcon_msgq_empty(stwuct nvkm_fawcon_msgq *);
int nvkm_fawcon_msgq_wecv_initmsg(stwuct nvkm_fawcon_msgq *, void *, u32 size);
void nvkm_fawcon_msgq_wecv(stwuct nvkm_fawcon_msgq *);
#endif
