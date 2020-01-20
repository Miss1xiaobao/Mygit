#include <stdio.h>

#include "test1.h"
// #include "include/test1.h"
// #include "/Users/bao/Workspace/VSCode/demo3/StudentManageSystem/test/include/test1.h"

/**
 * 1、我的环境linux系统gcc编译器，我用的是命令行，不是自动编译链接工具
 * 2、我的像你那样就可以，也就是说把头文件和.c文件放在同一个文件夹下面，
 *    .c文件会自己在同一个目录下找我自己的头文件.（我这里写的相对路径）
 * 3、你如果写绝对路径，肯定不会那个错误；
 * 4、如果还是那样写（相对路径），但是头文件和.c文件不再统一目录下，
 *    就会出现你的那个错误。
 * 1）这个时候修改方法，第一，把#include "test1.h"改成#include "include/test1.h"
 *     也就是改成正确的相对路径。相对你这个c文件的路径
 * 2）改成绝对路径#include "/Users/bao/Workspace/VSCode/demo3/StudentManageSystem/test/include/test1.h"
 * 3)还是写成#include "test1.h",但是在编译的时候你写成  -l 指明你的头文件在哪
 * 你可以写成  gcc -o test1 test1.c -Iinclude
 */

int print(int num) 
{
    int ret = -1;
    printf("num = %d\n", num);
    return 0;
}

int main(int argc, char *argv[]) {
    int num = 5;
    print(num);
}