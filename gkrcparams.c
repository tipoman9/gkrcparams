#include "type.h"
#include <mpi_ae.h>
#include <mpi_isp.h>
#include <mpi_sys.h>
#include <mpi_venc.h>
#include <mpi_vpss.h>
#include <plugin.h>

#include <getopt.h>


const char* VENC_RC_MODE_E_to_string(VENC_RC_MODE_E mode) {
    switch (mode) {
        case VENC_RC_MODE_H264CBR: return "VENC_RC_MODE_H264CBR";
        case VENC_RC_MODE_H264VBR: return "VENC_RC_MODE_H264VBR";
        case VENC_RC_MODE_H264AVBR: return "VENC_RC_MODE_H264AVBR";
        case VENC_RC_MODE_H264QVBR: return "VENC_RC_MODE_H264QVBR";
        case VENC_RC_MODE_H264CVBR: return "VENC_RC_MODE_H264CVBR";
        case VENC_RC_MODE_H264FIXQP: return "VENC_RC_MODE_H264FIXQP";
        case VENC_RC_MODE_H264QPMAP: return "VENC_RC_MODE_H264QPMAP";
        case VENC_RC_MODE_MJPEGCBR: return "VENC_RC_MODE_MJPEGCBR";
        case VENC_RC_MODE_MJPEGVBR: return "VENC_RC_MODE_MJPEGVBR";
        case VENC_RC_MODE_MJPEGFIXQP: return "VENC_RC_MODE_MJPEGFIXQP";
        case VENC_RC_MODE_H265CBR: return "VENC_RC_MODE_H265CBR";
        case VENC_RC_MODE_H265VBR: return "VENC_RC_MODE_H265VBR";
        case VENC_RC_MODE_H265AVBR: return "VENC_RC_MODE_H265AVBR";
        case VENC_RC_MODE_H265QVBR: return "VENC_RC_MODE_H265QVBR";
        case VENC_RC_MODE_H265CVBR: return "VENC_RC_MODE_H265CVBR";
        case VENC_RC_MODE_H265FIXQP: return "VENC_RC_MODE_H265FIXQP";
        case VENC_RC_MODE_H265QPMAP: return "VENC_RC_MODE_H265QPMAP";
        case VENC_RC_MODE_BUTT: return "VENC_RC_MODE_BUTT";
        default: return "Unknown mode";
    }
}

int main(int argc, char **argv)
{

  const struct option long_options[] = {
      {"MaxI", required_argument, NULL, 'm'},
      {"MinI", required_argument, NULL, 'n'},
      {"MaxQp", required_argument, NULL, 'a'},
      {"MinQp", required_argument, NULL, 'b'},
      {"MaxIQp", required_argument, NULL, 'k'},
      {"MinIQp", required_argument, NULL, 'l'},
      {"MaxReEnc", required_argument, NULL, 'c'},
      {"MaxQpD", required_argument, NULL, 'd'},
      {"MinQpD", required_argument, NULL, 'e'},
      {"ExtraBitPct", required_argument, NULL, 'p'},
      {"RefreshNum", required_argument, NULL, 'r'},
      {"QpMapEn", required_argument, NULL, 'q'},
      {"help", no_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}};

  int MaxIprop = -1, MinIprop = -1;
  int MaxQp = -1, MinQp = -1, MaxReEnc = -1, MaxQpD = -1,  MinQpD = -1,  RefreshNum=-1, MaxIQp = -1, MinIQp = -1, ExtraBitPct=-1, QpMapEn=-1;

  int opt;
  int long_index = 0;
  while ((opt = getopt_long_only(argc, argv, "", long_options, &long_index)) != -1)
  {
    switch (opt)
    {
    case 'm': MaxIprop = atoi(optarg); break;
    case 'n': MinIprop = atoi(optarg); break;
    case 'a': MaxQp = atoi(optarg); break;
    case 'b': MinQp = atoi(optarg); break;
    case 'k': MaxIQp = atoi(optarg); break;
    case 'l': MinIQp = atoi(optarg); break;
    case 'c': MaxReEnc = atoi(optarg); break;
    case 'd': MaxQpD = atoi(optarg); break;
    case 'e': MinQpD = atoi(optarg); break;
    case 'p': ExtraBitPct = atoi(optarg); break;
    case 'q': QpMapEn = atoi(optarg); break;

    case 'r': RefreshNum = atoi(optarg); break;     

    case 'h':
    default:
      printf("Usage: rcparams [OPTIONS][value]\n"
             "Where [OPTIONS]:\n"
             "  --MaxI     u32MaxIprop[u32MinIprop,100]    \n"
             "  --MinI     u32MinIprop[1,u32MaxIprop]   \n"
             "  --MaxQp    u32MaxQp[MinQp, 51]  \n"
             "  --MinQp    u32MinQp[0, 51]   \n"
             "  --MaxIQp    u32MaxIQp, default 45  \n"
             "  --MinIQp    u32MinIQp, default 10   \n"
             "  --MaxReEnc s32MaxReEncodeTimes[0, 3]     \n"
             "  --MaxQpD   u32MaxQpDelta[0, 4]   \n"
             "  --MinQpD   u32MinQpDelta[0, 4]   \n"
             "  --RefreshNum u32RefreshNum (enables IntraRefresh) \n"
             "  --ExtraBitPct u32ExtraBitPct (0-100) \n"                 
             "  --QpMapEn  QpMapEnable [0,1] \n"                              
             "  --help      Display this help\n"
             "sample:  \n"
             "rcparams --MaxI 10 --MinI 1 \n"
             "Specs:\n"
            "u32MinIprop\n"
                          "\tMinimum ratio of I-frames to P-frames\n"
                          "\tValue range: [1, 100]\n"
                          "u32MaxIprop\n"
                          "\tMaximum ratio of I-frames to P-frames\n"
                          "\tValue range: [u32MinIprop, 100]\n"
                          "u32MaxQp\n"
                          "\tMaximum frame QP value for controlling the image quality\n"
                          "\tValue range: [0, 51]\n"
                          "u32MinQp\n"
                          "\tMinimum frame QP value for controlling bit rate fluctuation\n"
                          "\tValue range: [0, u32MaxQp]\n"
                          "u32MaxIQp\n"
                          "\tMaximum QP of an I-frame for controlling the minimum\n"
                          "\tnumber of bits of an I-frame\n"
                          "\tValue range: [0, 51]\n"
                          "u32MinIQp\n"
                          "\tMinimum QP of an I-frame for controlling the maximum\n"
                          "\tnumber of bits of an I-frame\n"
                          "\tValue range: [0, u32MaxIQp]\n"
                          "s32MaxReEncodeTimes\n"
                          "\tNumber of times that each frame is re-encoded. The value 0\n"
                          "\tindicates that the frame is not re-encoded.\n"
                          "\tValue range: [0, 3]\n"
                          "bQpMapEn\n"
                          "\tWhether to enable or disable the QpMap function in CBR\n"
                          "\tmode\n"
                          "\tValue range: HI_TRUE or HI_FALSE\n"
                          "enQpMapMode\n"
                          "\tMethod of assigning the QP values for CU32 and CU64 when\n"
                          "\tthe QpMap table is enabled\n"

             );
      exit(1);
    }
  }

  
  VENC_CHN_ATTR_S chn_attr;
  VENC_RC_PARAM_S params = {0};

  int ret = HI_MPI_VENC_GetRcParam(0, &params);
  if (ret != GK_SUCCESS){
    fprintf(stderr, "GK_API_VENC_GetRcParam error %d\n", ret);
    exit(1);
  }

  ret = HI_MPI_VENC_GetChnAttr(0,  &chn_attr);
  fprintf(stderr, "Encoder mode = %d   %s\n", chn_attr.stRcAttr.enRcMode, VENC_RC_MODE_E_to_string(chn_attr.stRcAttr.enRcMode));

  MaxIprop = (MaxIprop > -1) ? MaxIprop : params.stParamH265Cbr.u32MaxIprop;
  MinIprop = (MinIprop > -1) ? MinIprop : params.stParamH265Cbr.u32MinIprop;
  fprintf(stderr, "stParamH265Cbr.u32MaxIprop = %d , was %d\n", MaxIprop, params.stParamH265Cbr.u32MaxIprop);
  params.stParamH265Cbr.u32MaxIprop = MaxIprop;

  fprintf(stderr, "stParamH265Cbr.u32MinIprop = %d , was %d\n", MinIprop, params.stParamH265Cbr.u32MinIprop);
  params.stParamH265Cbr.u32MinIprop = MinIprop;

  MaxQp = (MaxQp > -1) ? MaxQp : params.stParamH265Cbr.u32MaxQp;
  MinQp = (MinQp > -1) ? MinQp : params.stParamH265Cbr.u32MinQp;

  fprintf(stderr, "stParamH265Cbr.u32MaxQp = %d , was %d\n", MaxQp, params.stParamH265Cbr.u32MaxQp);
  fprintf(stderr, "stParamH265Cbr.u32MinQp = %d , was %d\n", MinQp, params.stParamH265Cbr.u32MinQp);
  params.stParamH265Cbr.u32MaxQp = MaxQp;
  params.stParamH265Cbr.u32MinQp = MinQp;

  MaxIQp = (MaxIQp > -1) ? MaxIQp : params.stParamH265Cbr.u32MaxIQp;
  MinIQp = (MinIQp > -1) ? MinIQp : params.stParamH265Cbr.u32MinIQp;

  fprintf(stderr, "stParamH265Cbr.u32MaxIQp = %d , was %d\n", MaxIQp, params.stParamH265Cbr.u32MaxIQp);
  fprintf(stderr, "stParamH265Cbr.u32MinIQp = %d , was %d\n", MinIQp, params.stParamH265Cbr.u32MinIQp);
  params.stParamH265Cbr.u32MaxIQp = MaxIQp;
  params.stParamH265Cbr.u32MinIQp = MinIQp;


  MaxReEnc = (MaxReEnc > -1) ? MaxReEnc : params.stParamH265Cbr.s32MaxReEncodeTimes;
  fprintf(stderr, "stParamH265Cbr.s32MaxReEncodeTimes = %d, was %d \n", MaxReEnc, params.stParamH265Cbr.s32MaxReEncodeTimes);
  params.stParamH265Cbr.s32MaxReEncodeTimes = MaxReEnc;

  QpMapEn = (QpMapEn > -1) ? QpMapEn : params.stParamH265Cbr.bQpMapEn;
  fprintf(stderr, "stParamH265Cbr.bQpMapEn = %d, was %d \n", QpMapEn, params.stParamH265Cbr.bQpMapEn);
  params.stParamH265Cbr.bQpMapEn = QpMapEn;

/* for CVbr only
  MaxQpD = (MaxQpD > -1) ? MaxQpD : params.stParamH265Cbr.u32MaxQpDelta;
  fprintf(stderr, "stParamH265Cbr.u32MaxQpDelta   = %d, was %d  \n", MaxQpD, params.stParamH265Cbr.u32MaxQpDelta);
  params.stParamH265Cbr.u32MaxQpDelta = MaxQpD;

  MinQpD = (MinQpD > -1) ? MinQpD : params.stParamH265Cbr.u32MinQpDelta;
  fprintf(stderr, "stParamH265Cbr.u32MinQpDelta   = %d, was %d  \n", MinQpD, params.stParamH265Cbr.u32MinQpDelta);
  params.stParamH265Cbr.u32MinQpDelta = MinQpD;


  ExtraBitPct = (ExtraBitPct > -1) ? ExtraBitPct : params.stParamH265Cbr.u32ExtraBitPercent;
  fprintf(stderr, "stParamH265Cbr.u32ExtraBitPercent   = %d, was %d  \n", ExtraBitPct, params.stParamH265Cbr.u32ExtraBitPercent);
  params.stParamH265Cbr.u32ExtraBitPercent = ExtraBitPct;
*/
  fprintf(stderr, "stParamH265Cbr.enQpMapMode = %d \n", params.stParamH265Cbr.enQpMapMode);
//  fprintf(stderr, "stParamH265Cbr.u32ExtraBitPercent = %d \n", params.stParamH265Cbr.u32ExtraBitPercent);
//  fprintf(stderr, "stParamH265Cbr.u32LongTermStatTimeUnit = %d \n", params.stParamH265Cbr.u32LongTermStatTimeUnit);
  

  // params.stParamH265Cbr.u32MinQp   = 1;

  ret = HI_MPI_VENC_SetRcParam(0, &params);
  if (ret != GK_SUCCESS){
    fprintf(stderr, "GK_API_VENC_SetRcParam error %d\n", ret);
    exit(1);
  }

  
  VENC_INTRA_REFRESH_S stIntraRefresh;
	if ((ret = HI_MPI_VENC_GetIntraRefresh( 0, &stIntraRefresh)) != GK_SUCCESS) {			
     fprintf(stderr, "Failed GetIntraRefresh %d\n", ret);
     exit(1);
		
   }

  //RefreshNum = (RefreshNum > -1) ? RefreshNum : stIntraRefresh.u32RefreshNum;

  fprintf(stderr, "enIntraRefreshMode = %d , bRefreshEnable = %d, u32ReqIQp= %d\n", 
  stIntraRefresh.enIntraRefreshMode,stIntraRefresh.bRefreshEnable,stIntraRefresh.u32ReqIQp);

  fprintf(stderr, "stIntraRefresh.u32RefreshNum = %d , was %d\n", (RefreshNum > -1) ? RefreshNum : stIntraRefresh.u32RefreshNum, stIntraRefresh.u32RefreshNum);
  
  if (RefreshNum>-1){
    stIntraRefresh.u32RefreshNum=RefreshNum;
    stIntraRefresh.enIntraRefreshMode=INTRA_REFRESH_ROW;
    stIntraRefresh.bRefreshEnable = GK_TRUE;
    stIntraRefresh.u32ReqIQp=GK_FALSE;
  }

  ret=HI_MPI_VENC_SetIntraRefresh(0, &stIntraRefresh);
  if (ret != GK_SUCCESS) {
    fprintf(stderr, "GK_API_VENC_SetIntraRefresh error %d\n", ret);
    exit(1);
  }

/*
  VENC_INTRA_REFRESH_S stIntraRefresh2 = {
            .enIntraRefreshMode = INTRA_REFRESH_ROW,
            .u32RefreshNum =  32//chn->size.height / chn->framesInGop,
            .bRefreshEnable = GK_TRUE,
            .u32ReqIQp = GK_FALSE,
        };
        ret = HI_MPI_VENC_SetIntraRefresh(  chn->venc_chn, &stIntraRefresh);
*/

/*
GK_S32 GK_API_VENC_SetIntraRefresh(VENC_CHN VeChn,
				   const VENC_INTRA_REFRESH_S *pstIntraRefresh);
GK_S32 GK_API_VENC_GetIntraRefresh(VENC_CHN VeChn,
				   VENC_INTRA_REFRESH_S *pstIntraRefresh);
*/



}

/*
 For __ctype_b*, the decision to replace it by __ctype_b_loc etc.
and disallow any new links against the old type were made because
__ctype_b* does not work together with uselocale(3).
These days, uselocale(3) is used quite often e.g. in libstdc++,
so it is very bad idea to keep using __ctype_b etc.
*/

__attribute__((visibility("default"))) const unsigned short int *__ctype_b;

__attribute__((visibility("default"))) int __fgetc_unlocked(FILE *stream)
{
  return fgetc(stream);
}

__attribute__((visibility("default"))) size_t _stdlib_mb_cur_max(void)
{
  return 0;
}
