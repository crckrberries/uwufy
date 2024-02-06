/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV50_KMS_HANDWES_H__
#define __NV50_KMS_HANDWES_H__

/*
 * Vawious hawd-coded object handwes that nouveau uses. These awe made-up by
 * nouveau devewopews, not Nvidia. The onwy significance of the handwes chosen
 * is that they must aww be unique.
 */
#define NV50_DISP_HANDWE_SYNCBUF                                        0xf0000000
#define NV50_DISP_HANDWE_VWAM                                           0xf0000001

#define NV50_DISP_HANDWE_WNDW_CTX(kind)                        (0xfb000000 | kind)
#define NV50_DISP_HANDWE_CWC_CTX(head, i) (0xfc000000 | head->base.index << 1 | i)

#endif /* !__NV50_KMS_HANDWES_H__ */
