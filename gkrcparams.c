#include "type.h"
#include <gk_api_venc.h>
#include <getopt.h>

int main(int argc, char **argv)
{

  const struct option long_options[] = {
      {"MaxI", required_argument, NULL, 'm'},
      {"MinI", required_argument, NULL, 'n'},
      {"MaxQp", required_argument, NULL, 'a'},
      {"MinQp", required_argument, NULL, 'b'},
      {"MaxReEnc", required_argument, NULL, 'c'},
      {"MaxQpD", required_argument, NULL, 'd'},
      {"help", no_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}};

  int MaxIprop = -1, MinIprop = -1;
  int MaxQp = -1, MinQp = -1, MaxReEnc = -1, MaxQpD = -1;

  int opt;
  int long_index = 0;
  while ((opt = getopt_long_only(argc, argv, "", long_options,
                                 &long_index)) != -1)
  {
    switch (opt)
    {
    case 'm':
      MaxIprop = atoi(optarg);
      break;
    case 'n':
      MinIprop = atoi(optarg);
      break;
    case 'a':
      MaxQp = atoi(optarg);
      break;
    case 'b':
      MinQp = atoi(optarg);
      break;
    case 'c':
      MaxReEnc = atoi(optarg);
      break;

    case 'd':
      MaxQpD = atoi(optarg);
      break;

    case 'h':
    default:
      printf("Usage: rcparams [OPTIONS]\n"
             "Where:\n"
             "  --MaxI      \n"
             "  --MinI      \n"
             "  --MaxQp      \n"
             "  --MinQp     \n"
             "  --MaxReEnc     \n"
             "  --MaxQpD     \n"
             "  --help          Display this help\n"
             "sample:  \n"
             "rcparams --MaxI 10 --MinI 1 \n");
      exit(1);
    }
  }

  VENC_RC_PARAM_S params = {0};

  int ret = GK_API_VENC_GetRcParam(0, &params);
  if (ret != GK_SUCCESS)
  {
    fprintf(stderr, "GK_API_VENC_GetRcParam error %d\n", ret);
    exit(1);
  }

  MaxIprop = (MaxIprop > -1) ? MaxIprop : params.stParamH265CVbr.u32MaxIprop;
  MinIprop = (MinIprop > -1) ? MinIprop : params.stParamH265CVbr.u32MinIprop;
  fprintf(stderr, "stParamH265CVbr.u32MaxIprop = %d , was %d\n", MaxIprop, params.stParamH265CVbr.u32MaxIprop);
  params.stParamH265CVbr.u32MaxIprop = MaxIprop;

  fprintf(stderr, "stParamH265CVbr.u32MinIprop = %d , was %d\n", MinIprop, params.stParamH265CVbr.u32MinIprop);
  params.stParamH265CVbr.u32MinIprop = MinIprop;

  MaxQp = (MaxQp > -1) ? MaxQp : params.stParamH265CVbr.u32MaxQp;
  MinQp = (MinQp > -1) ? MinQp : params.stParamH265CVbr.u32MinQp;

  fprintf(stderr, "stParamH265CVbr.u32MaxQp = %d , was %d\n", MaxQp, params.stParamH265CVbr.u32MaxQp);
  fprintf(stderr, "stParamH265CVbr.u32MinQp = %d , was %d\n", MinQp, params.stParamH265CVbr.u32MinQp);
  params.stParamH265CVbr.u32MaxQp = MaxQp;
  params.stParamH265CVbr.u32MinQp = MinQp;

  fprintf(stderr, "stParamH265CVbr.bQpMapEn = %d \n", params.stParamH265CVbr.bQpMapEn);

  MaxReEnc = (MaxReEnc > -1) ? MaxReEnc : params.stParamH265CVbr.s32MaxReEncodeTimes;
  fprintf(stderr, "stParamH265CVbr.s32MaxReEncodeTimes = %d, was %d \n", MaxReEnc, params.stParamH265CVbr.s32MaxReEncodeTimes);
  params.stParamH265CVbr.s32MaxReEncodeTimes = MaxReEnc;

  MaxQpD = (MaxQpD > -1) ? MaxQpD : params.stParamH265CVbr.u32MaxQpDelta;
  fprintf(stderr, "stParamH265CVbr.u32MaxQpDelta   = %d, was %d  \n", MaxQpD, params.stParamH265CVbr.u32MaxQpDelta);
  params.stParamH265CVbr.u32MaxQpDelta = MaxQpD;

  fprintf(stderr, "stParamH265CVbr.enQpMapMode = %d \n", params.stParamH265CVbr.enQpMapMode);
  fprintf(stderr, "stParamH265CVbr.u32ExtraBitPercent = %d \n", params.stParamH265CVbr.u32ExtraBitPercent);
  fprintf(stderr, "stParamH265CVbr.u32LongTermStatTimeUnit = %d \n", params.stParamH265CVbr.u32LongTermStatTimeUnit);
  fprintf(stderr, "stParamH265AVbr.u32MaxIprop = %d \n", params.stParamH265AVbr.u32MaxIprop);

  // params.stParamH265CVbr.u32MinQp   = 1;

  ret = GK_API_VENC_SetRcParam(0, &params);
  if (ret != GK_SUCCESS)
  {
    fprintf(stderr, "GK_API_VENC_SetRcParam error %d\n", ret);
    exit(1);
  }
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
