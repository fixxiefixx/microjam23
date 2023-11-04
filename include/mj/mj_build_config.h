#ifndef MJ_BUILD_CONFIG_H
#define MJ_BUILD_CONFIG_H

#include "bn_common.h"

#ifndef MJ_VERSION
    #define MJ_VERSION "1.02"
#endif

#ifndef MJ_INITIAL_COMPLETED_GAMES
    #define MJ_INITIAL_COMPLETED_GAMES 0
#endif

#ifndef MJ_SKIP_INITIAL_TITLE
    #define MJ_SKIP_INITIAL_TITLE false
#endif

#ifndef MJ_VBLANK_ASSERT_ENABLED
    #define MJ_VBLANK_ASSERT_ENABLED false
#endif

#endif
