#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 统计字符数函数
long count_chars(FILE *file) {
    long count = 0;
    int ch;
    
    // 重置文件指针到开头
    fseek(file, 0, SEEK_SET);
    
    // 逐个读取字符，直到文件结束
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    
    return count;
}

// 统计单词数函数
long count_words(FILE *file) {
    long count = 0;
    int ch;
    int in_word = 0;  // 标记是否在单词中，0表示不在，1表示在
    
    // 重置文件指针到开头
    fseek(file, 0, SEEK_SET);
    
    // 逐个读取字符
    while ((ch = fgetc(file)) != EOF) {
        // 如果是分隔符（空格、逗号、制表符、换行符）
        if (ch == ' ' || ch == ',' || ch == '\t' || ch == '\n') {
            in_word = 0;
        } 
        // 如果不是分隔符且不在单词中，说明新单词开始
        else if (!in_word) {
            in_word = 1;
            count++;
        }
        // 其他情况（在单词中），不做处理
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    // 检查命令行参数数量
    if (argc != 3) {
        printf("用法: %s [-c|-w] 文件名\n", argv[0]);
        printf("示例: %s -c input.txt\n", argv[0]);
        return 1;
    }
    
    // 检查参数是否合法
    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0) {
        printf("错误：参数必须是 -c 或 -w\n");
        return 1;
    }
    
    // 打开文件
    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("错误：无法打开文件 %s\n", argv[2]);
        return 1;
    }
    
    long result = 0;
    // 根据参数执行不同的统计逻辑
    if (strcmp(argv[1], "-c") == 0) {
        result = count_chars(file);
        printf("字符数：%ld\n", result);
    } else {
        result = count_words(file);
        printf("单词数：%ld\n", result);
    }
    
    // 关闭文件
    fclose(file);
    
    return 0;
}
