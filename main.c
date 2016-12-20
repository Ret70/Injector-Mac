//****************************************************
// 1.将loader改为app主程序名称，然后将主程序改名 例如：test－－>test_
// 2.将inject.dylib放到目录
//****************************************************

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>


#define BUF_LENGTH 1024
#define DYLIB_NAME "inject.dylib"



int main(int argc, const char * argv[])

{
    
    char szFullPath[BUF_LENGTH] = {0};  // 路径
    
    char szSelfName[50] = {0};          // 应用程序名称
    
    char szFilePath[BUF_LENGTH] = {0};
    
    char szInject[BUF_LENGTH] = {0};
    
    
    // 得到完整路径
    
    char *c = dirname((char *)argv[0]);
    
    strcpy(szFullPath, c);
    
    // 得到应用程序名
    
    c = basename((char *)argv[0]);
    
    strcpy(szSelfName, c);
    
    //printf("szFullPath==%s, szSelfName==%s\n\n\n\n", szFullPath, szSelfName);
    
    
    // 组装原始文件路径（原始文件被加了_）
    
    sprintf(szFilePath, "%s/%s_", szFullPath, szSelfName);
    
    //printf("------szFilePath = %s========\n\n\n\n", szFilePath);
    
    
    sprintf(szInject, "DYLD_INSERT_LIBRARIES=%s/%s", szFullPath, DYLIB_NAME);
    
    
    // 插入环境变量，为了使dylib自动注入
    
    char const * envp[] = {
        
        "export", "DYLD_FORCE_FLAT_NAMESPACE=1",
        
        "export", szInject,
        
        NULL
        
    };
    
    
    // 加载原始程序，此时dylib被注入
    
    execle(szFilePath, szSelfName, NULL, envp);
    
    return 0;
    
}


