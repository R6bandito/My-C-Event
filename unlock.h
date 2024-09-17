#ifndef UNLOCK_H
#define UNLOCK_H

#include <iostream>
#include "ansilib.h"
#include <mingw.thread.h>
#include <chrono>
#include "error.h"

#define PERMISSION_CONFIRM  1
#define PERMISSION_DENY 0

//客户端解锁界面
size_t display_unlock_menu();

#endif //UNLOCK_h