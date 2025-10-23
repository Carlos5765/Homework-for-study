#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { TOKEN_VAR, TOKEN_NOT, TOKEN_AND, TOKEN_OR, TOKEN_IMPL, TOKEN_EQV, TOKEN_LPAREN, TOKEN_RPAREN } TokenType;

typedef struct {
    TokenType type;
    char var;
} Token;

typedef struct {
    Token *data;
    int size;
    int capacity;
} Vector;

typedef struct {
    int *data;
    int top;
    int capacity;
} IntStack;

typedef struct {
    TokenType *data;
    int top;
    int capacity;
} Stack;

// 向量操作函数
void vector_init(Vector *v);
void vector_push(Vector *v, Token t);
Token vector_get(Vector *v, int index);
void vector_free(Vector *v);

// 整数栈操作函数
void int_stack_init(IntStack *s);
void int_stack_push(IntStack *s, int val);
int int_stack_pop(IntStack *s);
void int_stack_free(IntStack *s);

// 符号栈操作函数
void stack_init(Stack *s);
void stack_push(Stack *s, TokenType t);
TokenType stack_pop(Stack *s);
int stack_empty(Stack *s);
TokenType stack_top(Stack *s);
void stack_free(Stack *s);

// 表达式处理函数
int tokenize(const char *input, Vector *tokens);
int infix_to_postfix(const Vector *tokens, Vector *postfix);
int get_precedence(TokenType type);
void extract_vars(const Vector *tokens, char *vars, int *count);
int evaluate_postfix(const Vector *postfix, const char *vars, const int *var_values, int var_count);

// 主功能函数
void part1();
void part2();

// 向量操作实现
void vector_init(Vector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_push(Vector *v, Token t) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity ? v->capacity * 2 : 1;
        v->data = realloc(v->data, v->capacity * sizeof(Token));
    }
    v->data[v->size++] = t;
}

Token vector_get(Vector *v, int index) {
    return v->data[index];
}

void vector_free(Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = v->capacity = 0;
}

// 整数栈操作实现
void int_stack_init(IntStack *s) {
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

void int_stack_push(IntStack *s, int val) {
    if (s->top == s->capacity - 1) {
        s->capacity = s->capacity ? s->capacity * 2 : 1;
        s->data = realloc(s->data, s->capacity * sizeof(int));
    }
    s->data[++s->top] = val;
}

int int_stack_pop(IntStack *s) {
    if (s->top == -1) {
        printf("栈下溢错误\n");
        exit(1);
    }
    return s->data[s->top--];
}

void int_stack_free(IntStack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

// 符号栈操作实现
void stack_init(Stack *s) {
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

void stack_push(Stack *s, TokenType t) {
    if (s->top == s->capacity - 1) {
        s->capacity = s->capacity ? s->capacity * 2 : 1;
        s->data = realloc(s->data, s->capacity * sizeof(TokenType));
    }
    s->data[++s->top] = t;
}

TokenType stack_pop(Stack *s) {
    if (s->top == -1) {
        printf("栈下溢错误\n");
        exit(1);
    }
    return s->data[s->top--];
}

int stack_empty(Stack *s) {
    return s->top == -1;
}

TokenType stack_top(Stack *s) {
    if (s->top == -1) {
        printf("栈下溢错误\n");
        exit(1);
    }
    return s->data[s->top];
}

void stack_free(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->top = s->capacity = 0;
}

// 表达式处理实现
int get_precedence(TokenType type) {
    switch (type) {
        case TOKEN_NOT: return 10;
        case TOKEN_AND: return 8;
        case TOKEN_OR: return 6;
        case TOKEN_IMPL: return 4;
        case TOKEN_EQV: return 2;
        case TOKEN_LPAREN: return 1;
        case TOKEN_RPAREN: return 0;
        default: return -1;
    }
}

int tokenize(const char *input, Vector *tokens) {
    int i = 0;
    int len = strlen(input);
    vector_init(tokens);
    while (i < len) {
        if (isspace(input[i])) {
            i++;
            continue;
        }
        switch (input[i]) {
            case '!':
                vector_push(tokens, (Token){TOKEN_NOT, 0});
                i++;
                break;
            case '&':
                vector_push(tokens, (Token){TOKEN_AND, 0});
                i++;
                break;
            case '|':
                vector_push(tokens, (Token){TOKEN_OR, 0});
                i++;
                break;
            case '(':
                vector_push(tokens, (Token){TOKEN_LPAREN, 0});
                i++;
                break;
            case ')':
                vector_push(tokens, (Token){TOKEN_RPAREN, 0});
                i++;
                break;
            case '-':
                if (i+1 < len && input[i+1] == '>') {
                    vector_push(tokens, (Token){TOKEN_IMPL, 0});
                    i += 2;
                } else {
                    printf("无效字符 '-'\n");
                    vector_free(tokens);
                    return 0;
                }
                break;
            case '<':
                if (i+2 < len && input[i+1] == '-' && input[i+2] == '>') {
                    vector_push(tokens, (Token){TOKEN_EQV, 0});
                    i += 3;
                } else {
                    printf("无效字符 '<'\n");
                    vector_free(tokens);
                    return 0;
                }
                break;
            default:
                if (isalpha(input[i]) && isupper(input[i])) {
                    vector_push(tokens, (Token){TOKEN_VAR, input[i]});
                    i++;
                } else {
                    printf("无效字符 '%c'\n", input[i]);
                    vector_free(tokens);
                    return 0;
                }
                break;
        }
    }
    return 1;
}

int infix_to_postfix(const Vector *tokens, Vector *postfix) {
    Stack op_stack;
    stack_init(&op_stack);
    vector_init(postfix);
    
    for (int i = 0; i < tokens->size; i++) {
        Token token = tokens->data[i];
        if (token.type == TOKEN_VAR) {
            vector_push(postfix, token);
        } else if (token.type == TOKEN_LPAREN) {
            stack_push(&op_stack, token.type);
        } else if (token.type == TOKEN_RPAREN) {
            while (!stack_empty(&op_stack) && stack_top(&op_stack) != TOKEN_LPAREN) {
                Token t = {stack_pop(&op_stack), 0};
                vector_push(postfix, t);
            }
            if (stack_empty(&op_stack)) {
                printf("括号不匹配\n");
                vector_free(postfix);
                stack_free(&op_stack);
                return 0;
            }
            stack_pop(&op_stack);
        } else {
            int prec = get_precedence(token.type);
            while (!stack_empty(&op_stack)) {
                TokenType top_type = stack_top(&op_stack);
                int top_prec = get_precedence(top_type);
                if (top_prec > prec || (top_prec == prec && token.type != TOKEN_NOT)) {
                    Token t = {top_type, 0};
                    vector_push(postfix, t);
                    stack_pop(&op_stack);
                } else {
                    break;
                }
            }
            stack_push(&op_stack, token.type);
        }
    }
    
    while (!stack_empty(&op_stack)) {
        TokenType top_type = stack_top(&op_stack);
        if (top_type == TOKEN_LPAREN) {
            printf("括号不匹配\n");
            vector_free(postfix);
            stack_free(&op_stack);
            return 0;
        }
        Token t = {top_type, 0};
        vector_push(postfix, t);
        stack_pop(&op_stack);
    }
    
    stack_free(&op_stack);
    return 1;
}

void extract_vars(const Vector *tokens, char *vars, int *count) {
    *count = 0;
    for (int i = 0; i < tokens->size; i++) {
        Token token = tokens->data[i];
        if (token.type == TOKEN_VAR) {
            int found = 0;
            for (int j = 0; j < *count; j++) {
                if (vars[j] == token.var) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                vars[(*count)++] = token.var;
            }
        }
    }
    for (int i = 0; i < *count - 1; i++) {
        for (int j = i+1; j < *count; j++) {
            if (vars[i] > vars[j]) {
                char temp = vars[i];
                vars[i] = vars[j];
                vars[j] = temp;
            }
        }
    }
}

int evaluate_postfix(const Vector *postfix, const char *vars, const int *var_values, int var_count) {
    IntStack val_stack;
    int_stack_init(&val_stack);
    
    for (int i = 0; i < postfix->size; i++) {
        Token token = postfix->data[i];
        switch (token.type) {
            case TOKEN_VAR: {
                char var = token.var;
                int idx = -1;
                for (int j = 0; j < var_count; j++) {
                    if (vars[j] == var) {
                        idx = j;
                        break;
                    }
                }
                if (idx == -1) {
                    printf("未定义的变量 %c\n", var);
                    int_stack_free(&val_stack);
                    return -1;
                }
                int_stack_push(&val_stack, var_values[idx]);
                break;
            }
            case TOKEN_NOT: {
                if (val_stack.top < 0) {
                    printf("NOT运算时栈下溢\n");
                    int_stack_free(&val_stack);
                    return -1;
                }
                int val = int_stack_pop(&val_stack);
                int_stack_push(&val_stack, val ? 0 : 1);
                break;
            }
            case TOKEN_AND: {
                if (val_stack.top < 1) {
                    printf("AND运算时栈下溢\n");
                    int_stack_free(&val_stack);
                    return -1;
                }
                int right = int_stack_pop(&val_stack);
                int left = int_stack_pop(&val_stack);
                int_stack_push(&val_stack, (left && right) ? 1 : 0);
                break;
            }
            case TOKEN_OR: {
                if (val_stack.top < 1) {
                    printf("OR运算时栈下溢\n");
                    int_stack_free(&val_stack);
                    return -1;
                }
                int right = int_stack_pop(&val_stack);
                int left = int_stack_pop(&val_stack);
                int_stack_push(&val_stack, (left || right) ? 1 : 0);
                break;
            }
            case TOKEN_IMPL: {
                if (val_stack.top < 1) {
                    printf("IMPL运算时栈下溢\n");
                    int_stack_free(&val_stack);
                    return -1;
                }
                int right = int_stack_pop(&val_stack);
                int left = int_stack_pop(&val_stack);
                int res = (!left) || right;
                int_stack_push(&val_stack, res ? 1 : 0);
                break;
            }
            case TOKEN_EQV: {
                if (val_stack.top < 1) {
                    printf("EQV运算时栈下溢\n");
                    int_stack_free(&val_stack);
                    return -1;
                }
                int right = int_stack_pop(&val_stack);
                int left = int_stack_pop(&val_stack);
                int_stack_push(&val_stack, (left == right) ? 1 : 0);
                break;
            }
            default:
                break;
        }
    }
    
    if (val_stack.top != 0) {
        printf("无效的后缀表达式\n");
        int_stack_free(&val_stack);
        return -1;
    }
    int result = int_stack_pop(&val_stack);
    int_stack_free(&val_stack);
    return result;
}

void part1() {
    int p, q;
    printf("请输入命题P的真值 (0 或 1): ");
    scanf("%d", &p);
    printf("请输入命题Q的真值 (0 或 1): ");
    scanf("%d", &q);
    
    int not_p = !p;
    int and_pq = p && q;
    int or_pq = p || q;
    int impl_pq = !p || q;
    int eqv_pq = (p == q);
    
    printf("?P: %d\n", not_p);
    printf("P∧Q: %d\n", and_pq);
    printf("P∨Q: %d\n", or_pq);
    printf("P→Q: %d\n", impl_pq);
    printf("P?Q: %d\n", eqv_pq);
}

void part2() {
    char formula[100];
    printf("请输入命题公式 (使用 ! 表示 ?, & 表示 ∧, | 表示 ∨, -> 表示 →, <-> 表示 ?): ");
    fflush(stdin);
    fgets(formula, sizeof(formula), stdin);
    formula[strcspn(formula, "\n")] = '\0';
    
    Vector tokens;
    if (!tokenize(formula, &tokens)) {
        return;
    }
    
    Vector postfix;
    if (!infix_to_postfix(&tokens, &postfix)) {
        vector_free(&tokens);
        return;
    }
    vector_free(&tokens);
    
    char vars[26] = {0};
    int var_count = 0;
    extract_vars(&postfix, vars, &var_count);
    if (var_count == 0) {
        printf("公式中不包含变量\n");
        vector_free(&postfix);
        return;
    }
    
    int num_combinations = 1 << var_count;
    printf("公式 %s 的真值表:\n", formula);
    for (int i = 0; i < var_count; i++) {
        printf("%c ", vars[i]);
    }
    printf("| 结果\n");
    for (int i = 0; i < var_count + 7; i++) {
        printf("-");
    }
    printf("\n");
    
    for (int k = 0; k < num_combinations; k++) {
        int var_values[26];
        for (int i = 0; i < var_count; i++) {
            var_values[i] = (k >> i) & 1;
            printf("%d ", var_values[i]);
        }
        int result = evaluate_postfix(&postfix, vars, var_values, var_count);
        if (result == -1) {
            vector_free(&postfix);
            return;
        }
        printf("| %d\n", result);
    }
    
    vector_free(&postfix);
}

int main() {
    int choice;
    printf("实验1: 命题逻辑真值计算与真值表生成\n");
    printf("1. 计算P和Q的基本逻辑运算\n");
    printf("2. 生成命题公式的真值表\n");
    printf("请输入你的选择: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        part1();
    } else if (choice == 2) {
        part2();
    } else {
        printf("无效的选择\n");
    }
    
    return 0;
}