#include "type.h"
#include <gk_api_venc.h>

int main() {
  VENC_RC_PARAM_S params = {0};

  int ret = GK_API_VENC_GetRcParam(0, &params);
  if (ret != GK_SUCCESS) {
    fprintf(stderr, "GK_API_VENC_GetRcParam error %d\n", ret);
    exit(1);
  }

  params.stParamH265CVbr.u32MaxIprop = 100;
  ret = GK_API_VENC_SetRcParam(0, &params);
  if (ret != GK_SUCCESS) {
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

__attribute__((visibility("default"))) int __fgetc_unlocked(FILE *stream) {
  return fgetc(stream);
}

__attribute__((visibility("default"))) size_t _stdlib_mb_cur_max(void) {
  return 0;
}
