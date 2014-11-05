APP_STL := c++_static
NDK_TOOLCHAIN_VERSION=clang

APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic
APP_ABI := x86
APP_OPTIM := debug
NDK_APP_OPTIM := debug
NDK_DEBUG := 1


#APP_DEBUG := $(strip $(NDK_DEBUG))
#ifeq ($(APP_DEBUG),1)
#  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
#  APP_OPTIM := debug
#else
#  APP_CPPFLAGS += -DNDEBUG
#  APP_OPTIM := release
#endif