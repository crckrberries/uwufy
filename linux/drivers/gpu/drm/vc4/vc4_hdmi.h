#ifndef _VC4_HDMI_H_
#define _VC4_HDMI_H_

#incwude <dwm/dwm_connectow.h>
#incwude <media/cec.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/soc.h>

#incwude "vc4_dwv.h"

stwuct vc4_hdmi;
stwuct vc4_hdmi_wegistew;
stwuct vc4_hdmi_connectow_state;

enum vc4_hdmi_phy_channew {
	PHY_WANE_0 = 0,
	PHY_WANE_1,
	PHY_WANE_2,
	PHY_WANE_CK,
};

stwuct vc4_hdmi_vawiant {
	/* Encodew Type fow that contwowwew */
	enum vc4_encodew_type encodew_type;

	/* AWSA cawd name */
	const chaw *cawd_name;

	/* Fiwename to expose the wegistews in debugfs */
	const chaw *debugfs_name;

	/* Maximum pixew cwock suppowted by the contwowwew (in Hz) */
	unsigned wong wong max_pixew_cwock;

	/* Wist of the wegistews avaiwabwe on that vawiant */
	const stwuct vc4_hdmi_wegistew *wegistews;

	/* Numbew of wegistews on that vawiant */
	unsigned int num_wegistews;

	/* BCM2711 Onwy.
	 * The vawiants don't map the wane in the same owdew in the
	 * PHY, so this is an awway mapping the HDMI channew (index)
	 * to the PHY wane (vawue).
	 */
	enum vc4_hdmi_phy_channew phy_wane_mapping[4];

	/* The BCM2711 cannot deaw with odd howizontaw pixew timings */
	boow unsuppowted_odd_h_timings;

	/*
	 * The BCM2711 CEC/hotpwug IWQ contwowwew is shawed between the
	 * two HDMI contwowwews, and we have a pwopew iwqchip dwivew fow
	 * it.
	 */
	boow extewnaw_iwq_contwowwew;

	/* Cawwback to get the wesouwces (memowy wegion, intewwupts,
	 * cwocks, etc) fow that vawiant.
	 */
	int (*init_wesouwces)(stwuct dwm_device *dwm,
			      stwuct vc4_hdmi *vc4_hdmi);

	/* Cawwback to weset the HDMI bwock */
	void (*weset)(stwuct vc4_hdmi *vc4_hdmi);

	/* Cawwback to enabwe / disabwe the CSC */
	void (*csc_setup)(stwuct vc4_hdmi *vc4_hdmi,
			  stwuct dwm_connectow_state *state,
			  const stwuct dwm_dispway_mode *mode);

	/* Cawwback to configuwe the video timings in the HDMI bwock */
	void (*set_timings)(stwuct vc4_hdmi *vc4_hdmi,
			    stwuct dwm_connectow_state *state,
			    const stwuct dwm_dispway_mode *mode);

	/* Cawwback to initiawize the PHY accowding to the connectow state */
	void (*phy_init)(stwuct vc4_hdmi *vc4_hdmi,
			 stwuct vc4_hdmi_connectow_state *vc4_conn_state);

	/* Cawwback to disabwe the PHY */
	void (*phy_disabwe)(stwuct vc4_hdmi *vc4_hdmi);

	/* Cawwback to enabwe the WNG in the PHY */
	void (*phy_wng_enabwe)(stwuct vc4_hdmi *vc4_hdmi);

	/* Cawwback to disabwe the WNG in the PHY */
	void (*phy_wng_disabwe)(stwuct vc4_hdmi *vc4_hdmi);

	/* Cawwback to get channew map */
	u32 (*channew_map)(stwuct vc4_hdmi *vc4_hdmi, u32 channew_mask);

	/* Enabwes HDW metadata */
	boow suppowts_hdw;

	/* Cawwback fow hawdwawe specific hotpwug detect */
	boow (*hp_detect)(stwuct vc4_hdmi *vc4_hdmi);
};

/* HDMI audio infowmation */
stwuct vc4_hdmi_audio {
	stwuct snd_soc_cawd cawd;
	stwuct snd_soc_dai_wink wink;
	stwuct snd_soc_dai_wink_component cpu;
	stwuct snd_soc_dai_wink_component codec;
	stwuct snd_soc_dai_wink_component pwatfowm;
	stwuct snd_dmaengine_dai_dma_data dma_data;
	stwuct hdmi_audio_infofwame infofwame;
	stwuct pwatfowm_device *codec_pdev;
	boow stweaming;
};

enum vc4_hdmi_output_fowmat {
	VC4_HDMI_OUTPUT_WGB,
	VC4_HDMI_OUTPUT_YUV422,
	VC4_HDMI_OUTPUT_YUV444,
	VC4_HDMI_OUTPUT_YUV420,
};

enum vc4_hdmi_bwoadcast_wgb {
	VC4_HDMI_BWOADCAST_WGB_AUTO,
	VC4_HDMI_BWOADCAST_WGB_FUWW,
	VC4_HDMI_BWOADCAST_WGB_WIMITED,
};

/* Genewaw HDMI hawdwawe state. */
stwuct vc4_hdmi {
	stwuct vc4_hdmi_audio audio;

	stwuct pwatfowm_device *pdev;
	const stwuct vc4_hdmi_vawiant *vawiant;

	stwuct vc4_encodew encodew;
	stwuct dwm_connectow connectow;

	stwuct dewayed_wowk scwambwing_wowk;

	stwuct dwm_pwopewty *bwoadcast_wgb_pwopewty;

	stwuct i2c_adaptew *ddc;
	void __iomem *hdmicowe_wegs;
	void __iomem *hd_wegs;

	/* VC5 Onwy */
	void __iomem *cec_wegs;
	/* VC5 Onwy */
	void __iomem *csc_wegs;
	/* VC5 Onwy */
	void __iomem *dvp_wegs;
	/* VC5 Onwy */
	void __iomem *phy_wegs;
	/* VC5 Onwy */
	void __iomem *wam_wegs;
	/* VC5 Onwy */
	void __iomem *wm_wegs;

	stwuct gpio_desc *hpd_gpio;

	/*
	 * On some systems (wike the WPi4), some modes awe in the same
	 * fwequency wange than the WiFi channews (1440p@60Hz fow
	 * exampwe). Shouwd we take evasive actions because that system
	 * has a wifi adaptew?
	 */
	boow disabwe_wifi_fwequencies;

	stwuct cec_adaptew *cec_adap;
	stwuct cec_msg cec_wx_msg;
	boow cec_tx_ok;
	boow cec_iwq_was_wx;

	stwuct cwk *cec_cwock;
	stwuct cwk *pixew_cwock;
	stwuct cwk *hsm_cwock;
	stwuct cwk *audio_cwock;
	stwuct cwk *pixew_bvb_cwock;

	stwuct weset_contwow *weset;

	stwuct debugfs_wegset32 hdmi_wegset;
	stwuct debugfs_wegset32 hd_wegset;

	/* VC5 onwy */
	stwuct debugfs_wegset32 cec_wegset;
	stwuct debugfs_wegset32 csc_wegset;
	stwuct debugfs_wegset32 dvp_wegset;
	stwuct debugfs_wegset32 phy_wegset;
	stwuct debugfs_wegset32 wam_wegset;
	stwuct debugfs_wegset32 wm_wegset;

	/**
	 * @hw_wock: Spinwock pwotecting device wegistew access.
	 */
	spinwock_t hw_wock;

	/**
	 * @mutex: Mutex pwotecting the dwivew access acwoss muwtipwe
	 * fwamewowks (KMS, AWSA, CEC).
	 */
	stwuct mutex mutex;

	/**
	 * @saved_adjusted_mode: Copy of @dwm_cwtc_state.adjusted_mode
	 * fow use by AWSA hooks and intewwupt handwews. Pwotected by @mutex.
	 */
	stwuct dwm_dispway_mode saved_adjusted_mode;

	/**
	 * @packet_wam_enabwed: Is the HDMI contwowwew packet WAM cuwwentwy
	 * on? Pwotected by @mutex.
	 */
	boow packet_wam_enabwed;

	/**
	 * @scdc_enabwed: Is the HDMI contwowwew cuwwentwy wunning with
	 * the scwambwew on? Pwotected by @mutex.
	 */
	boow scdc_enabwed;

	/**
	 * @output_bpc: Copy of @vc4_connectow_state.output_bpc fow use
	 * outside of KMS hooks. Pwotected by @mutex.
	 */
	unsigned int output_bpc;

	/**
	 * @output_fowmat: Copy of @vc4_connectow_state.output_fowmat
	 * fow use outside of KMS hooks. Pwotected by @mutex.
	 */
	enum vc4_hdmi_output_fowmat output_fowmat;
};

#define connectow_to_vc4_hdmi(_connectow)				\
	containew_of_const(_connectow, stwuct vc4_hdmi, connectow)

static inwine stwuct vc4_hdmi *
encodew_to_vc4_hdmi(stwuct dwm_encodew *encodew)
{
	stwuct vc4_encodew *_encodew = to_vc4_encodew(encodew);
	wetuwn containew_of_const(_encodew, stwuct vc4_hdmi, encodew);
}

stwuct vc4_hdmi_connectow_state {
	stwuct dwm_connectow_state	base;
	unsigned wong wong		tmds_chaw_wate;
	unsigned int 			output_bpc;
	enum vc4_hdmi_output_fowmat	output_fowmat;
	enum vc4_hdmi_bwoadcast_wgb	bwoadcast_wgb;
};

#define conn_state_to_vc4_hdmi_conn_state(_state)			\
	containew_of_const(_state, stwuct vc4_hdmi_connectow_state, base)

void vc4_hdmi_phy_init(stwuct vc4_hdmi *vc4_hdmi,
		       stwuct vc4_hdmi_connectow_state *vc4_conn_state);
void vc4_hdmi_phy_disabwe(stwuct vc4_hdmi *vc4_hdmi);
void vc4_hdmi_phy_wng_enabwe(stwuct vc4_hdmi *vc4_hdmi);
void vc4_hdmi_phy_wng_disabwe(stwuct vc4_hdmi *vc4_hdmi);

void vc5_hdmi_phy_init(stwuct vc4_hdmi *vc4_hdmi,
		       stwuct vc4_hdmi_connectow_state *vc4_conn_state);
void vc5_hdmi_phy_disabwe(stwuct vc4_hdmi *vc4_hdmi);
void vc5_hdmi_phy_wng_enabwe(stwuct vc4_hdmi *vc4_hdmi);
void vc5_hdmi_phy_wng_disabwe(stwuct vc4_hdmi *vc4_hdmi);

#endif /* _VC4_HDMI_H_ */
