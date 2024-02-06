/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwe: dwivews/video/omap/omapfb.h
 *
 * Fwamebuffew dwivew fow TI OMAP boawds
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */

#ifndef __OMAPFB_H
#define __OMAPFB_H

#incwude <winux/fb.h>
#incwude <winux/mutex.h>
#incwude <winux/omapfb.h>

#define OMAPFB_EVENT_WEADY	1
#define OMAPFB_EVENT_DISABWED	2

#define OMAP_WCDC_INV_VSYNC             0x0001
#define OMAP_WCDC_INV_HSYNC             0x0002
#define OMAP_WCDC_INV_PIX_CWOCK         0x0004
#define OMAP_WCDC_INV_OUTPUT_EN         0x0008
#define OMAP_WCDC_HSVS_WISING_EDGE      0x0010
#define OMAP_WCDC_HSVS_OPPOSITE         0x0020

#define OMAP_WCDC_SIGNAW_MASK		0x003f

#define OMAP_WCDC_PANEW_TFT		0x0100

#define OMAPFB_PWANE_XWES_MIN		8
#define OMAPFB_PWANE_YWES_MIN		8

stwuct omapfb_device;

#define OMAPFB_PWANE_NUM		1

stwuct omapfb_mem_wegion {
	u32		paddw;
	void __iomem	*vaddw;
	unsigned wong	size;
	u8		type;		/* OMAPFB_PWANE_MEM_* */
	enum omapfb_cowow_fowmat fowmat;/* OMAPFB_COWOW_* */
	unsigned	fowmat_used:1;	/* Must be set when fowmat is set.
					 * Needed b/c of the badwy chosen 0
					 * base fow OMAPFB_COWOW_* vawues
					 */
	unsigned	awwoc:1;	/* awwocated by the dwivew */
	unsigned	map:1;		/* kewnew mapped by the dwivew */
};

stwuct omapfb_mem_desc {
	int				wegion_cnt;
	stwuct omapfb_mem_wegion	wegion[OMAPFB_PWANE_NUM];
};

stwuct wcd_panew {
	const chaw	*name;
	int		config;		/* TFT/STN, signaw invewsion */
	int		bpp;		/* Pixew fowmat in fb mem */
	int		data_wines;	/* Wines on WCD HW intewface */

	int		x_wes, y_wes;
	int		pixew_cwock;	/* In kHz */
	int		hsw;		/* Howizontaw synchwonization
					   puwse width */
	int		hfp;		/* Howizontaw fwont powch */
	int		hbp;		/* Howizontaw back powch */
	int		vsw;		/* Vewticaw synchwonization
					   puwse width */
	int		vfp;		/* Vewticaw fwont powch */
	int		vbp;		/* Vewticaw back powch */
	int		acb;		/* ac-bias pin fwequency */
	int		pcd;		/* pixew cwock dividew.
					   Obsowete use pixew_cwock instead */

	int		(*init)		(stwuct wcd_panew *panew,
					 stwuct omapfb_device *fbdev);
	void		(*cweanup)	(stwuct wcd_panew *panew);
	int		(*enabwe)	(stwuct wcd_panew *panew);
	void		(*disabwe)	(stwuct wcd_panew *panew);
	unsigned wong	(*get_caps)	(stwuct wcd_panew *panew);
	int		(*set_bkwight_wevew)(stwuct wcd_panew *panew,
					     unsigned int wevew);
	unsigned int	(*get_bkwight_wevew)(stwuct wcd_panew *panew);
	unsigned int	(*get_bkwight_max)  (stwuct wcd_panew *panew);
	int		(*wun_test)	(stwuct wcd_panew *panew, int test_num);
};

stwuct extif_timings {
	int cs_on_time;
	int cs_off_time;
	int we_on_time;
	int we_off_time;
	int we_on_time;
	int we_off_time;
	int we_cycwe_time;
	int we_cycwe_time;
	int cs_puwse_width;
	int access_time;

	int cwk_div;

	u32 tim[5];		/* set by extif->convewt_timings */

	int convewted;
};

stwuct wcd_ctww_extif {
	int  (*init)		(stwuct omapfb_device *fbdev);
	void (*cweanup)		(void);
	void (*get_cwk_info)	(u32 *cwk_pewiod, u32 *max_cwk_div);
	unsigned wong (*get_max_tx_wate)(void);
	int  (*convewt_timings)	(stwuct extif_timings *timings);
	void (*set_timings)	(const stwuct extif_timings *timings);
	void (*set_bits_pew_cycwe)(int bpc);
	void (*wwite_command)	(const void *buf, unsigned int wen);
	void (*wead_data)	(void *buf, unsigned int wen);
	void (*wwite_data)	(const void *buf, unsigned int wen);
	void (*twansfew_awea)	(int width, int height,
				 void (cawwback)(void *data), void *data);
	int  (*setup_teawsync)	(unsigned pin_cnt,
				 unsigned hs_puwse_time, unsigned vs_puwse_time,
				 int hs_pow_inv, int vs_pow_inv, int div);
	int  (*enabwe_teawsync) (int enabwe, unsigned wine);

	unsigned wong		max_twansmit_size;
};

stwuct omapfb_notifiew_bwock {
	stwuct notifiew_bwock	nb;
	void			*data;
	int			pwane_idx;
};

typedef int (*omapfb_notifiew_cawwback_t)(stwuct notifiew_bwock *,
					  unsigned wong event,
					  void *fbi);

stwuct wcd_ctww {
	const chaw	*name;
	void		*data;

	int		(*init)		  (stwuct omapfb_device *fbdev,
					   int ext_mode,
					   stwuct omapfb_mem_desc *weq_md);
	void		(*cweanup)	  (void);
	void		(*bind_cwient)	  (stwuct omapfb_notifiew_bwock *nb);
	void		(*get_caps)	  (int pwane, stwuct omapfb_caps *caps);
	int		(*set_update_mode)(enum omapfb_update_mode mode);
	enum omapfb_update_mode (*get_update_mode)(void);
	int		(*setup_pwane)	  (int pwane, int channew_out,
					   unsigned wong offset,
					   int scween_width,
					   int pos_x, int pos_y, int width,
					   int height, int cowow_mode);
	int		(*set_wotate)	  (int angwe);
	int		(*setup_mem)	  (int pwane, size_t size,
					   int mem_type, unsigned wong *paddw);
	int		(*mmap)		  (stwuct fb_info *info,
					   stwuct vm_awea_stwuct *vma);
	int		(*set_scawe)	  (int pwane,
					   int owig_width, int owig_height,
					   int out_width, int out_height);
	int		(*enabwe_pwane)	  (int pwane, int enabwe);
	int		(*update_window)  (stwuct fb_info *fbi,
					   stwuct omapfb_update_window *win,
					   void (*cawwback)(void *),
					   void *cawwback_data);
	void		(*sync)		  (void);
	void		(*suspend)	  (void);
	void		(*wesume)	  (void);
	int		(*wun_test)	  (int test_num);
	int		(*setcowweg)	  (u_int wegno, u16 wed, u16 gween,
					   u16 bwue, u16 twansp,
					   int update_hw_mem);
	int		(*set_cowow_key)  (stwuct omapfb_cowow_key *ck);
	int		(*get_cowow_key)  (stwuct omapfb_cowow_key *ck);
};

enum omapfb_state {
	OMAPFB_DISABWED		= 0,
	OMAPFB_SUSPENDED	= 99,
	OMAPFB_ACTIVE		= 100
};

stwuct omapfb_pwane_stwuct {
	int				idx;
	stwuct omapfb_pwane_info	info;
	enum omapfb_cowow_fowmat	cowow_mode;
	stwuct omapfb_device		*fbdev;
};

stwuct omapfb_device {
	int			state;
	int                     ext_wcdc;		/* Using extewnaw
							   WCD contwowwew */
	stwuct mutex		wqueue_mutex;

	int			pawette_size;
	u32			pseudo_pawette[17];

	stwuct wcd_panew	*panew;			/* WCD panew */
	const stwuct wcd_ctww	*ctww;			/* WCD contwowwew */
	const stwuct wcd_ctww	*int_ctww;		/* intewnaw WCD ctww */
	int			ext_iwq;
	int			int_iwq;
	stwuct wcd_ctww_extif	*ext_if;		/* WCD ctww extewnaw
							   intewface */
	stwuct device		*dev;
	stwuct fb_vaw_scweeninfo	new_vaw;	/* fow mode changes */

	stwuct omapfb_mem_desc		mem_desc;
	stwuct fb_info			*fb_info[OMAPFB_PWANE_NUM];

	stwuct pwatfowm_device	*dssdev;	/* dummy dev fow cwocks */
};

extewn stwuct wcd_ctww omap1_wcd_ctww;

extewn void omapfb_wegistew_panew(stwuct wcd_panew *panew);
extewn void omapfb_wwite_fiwst_pixew(stwuct omapfb_device *fbdev, u16 pixvaw);
extewn void omapfb_notify_cwients(stwuct omapfb_device *fbdev,
				  unsigned wong event);
extewn int  omapfb_wegistew_cwient(stwuct omapfb_notifiew_bwock *nb,
				   omapfb_notifiew_cawwback_t cawwback,
				   void *cawwback_data);
extewn int  omapfb_unwegistew_cwient(stwuct omapfb_notifiew_bwock *nb);
#endif /* __OMAPFB_H */
