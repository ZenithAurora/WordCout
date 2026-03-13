#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 函数声明（集中管理，提升可读性）
static long count_chars(FILE *file);
static long count_words(FILE *file);

int main(int argc, char *argv[]) {
    // 1. 参数合法性校验（精简提示信息）
    if (argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0)) {
        fprintf(stderr, "用法: %s [-c|-w] 文件名\n示例: %s -c input.txt\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // 2. 打开文件（使用标准错误流输出错误）
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("文件打开失败"); // 自动拼接系统错误信息，更友好
        return EXIT_FAILURE;
    }

    // 3. 执行统计逻辑（精简分支）
    long result = (strcmp(argv[1], "-c") == 0) ? count_chars(file) : count_words(file);
    printf("%s：%ld\n", (strcmp(argv[1], "-c") == 0) ? "字符数" : "单词数", result);

    // 4. 关闭文件
    fclose(file);
    return EXIT_SUCCESS;
}

// 统计字符数（精简循环逻辑）
static long count_chars(FILE *file) {
    fseek(file, 0, SEEK_SET);
    long count = 0;
    while (fgetc(file) != EOF) count++;
    return count;
}

// 统计单词数（优化单词判断逻辑，使用标准库函数）
static long count_words(FILE *file) {
    fseek(file, 0, SEEK_SET);
    long count = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        // 使用isspace判断空白字符，覆盖所有空白类型（更通用）
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}
