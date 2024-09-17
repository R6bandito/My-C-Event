#ifndef ANSI_H
#define ANSI_H

#include <iostream>

#define __ANSI_CLR_TERM()     std::cout<<"\033[2J\033[H";

#define __ANSI_MOV_CURSOR(x,y)    std::cout<<"\033["<<x<<";"<<y<<"H";

#define __ANSI_CUR_SAVE()     std::cout<<"\033[s";

#define __ANSI_CUR_GET()        std::cout<<"\033[u";

#define __ANSI_CUR_ENABLE()     std::cout<<"\033[?25h";

#define __ANSI_CUR_DISABLE()    std::cout<<"\033[?25l";

//清除该行并读取光标保存行复位
#define __ANSI_CUR_RESET()  std::cout<<"\033[2K\033[u\033[K";
                                    

#endif //ANSI_H