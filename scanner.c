#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "scanner.h"

static bool is_at_end(Scanner *sc) {
    return sc->current >= strlen(sc->source);
}

static char advance(Scanner *sc) {
    return *(sc->source + sc->current++);
}

static char peek(Scanner *sc) {
    if (is_at_end(sc))
        return '\0';

    return *(sc->source + sc->current);
}

static char peek_next(Scanner *sc) {
    int next = sc->current + 1;

    if (next >= strlen(sc->source)) 
        return '\0';

    return *(sc->source + next);
}

static bool match(Scanner *sc, char c) {
    if (is_at_end(sc))
        return false;
    
    if (*(sc->source + sc->current) != c) 
        return false;

    sc->current++;
    return true;
}

static bool is_digit(char c) {
    return c >= '0' && c <= '9';
} 

static char *get_value(Scanner *sc) {
    int len = sc->current - sc->start;
    char *suf = sc->source + sc->start;

    char *value = malloc(len + 1);
    memcpy(value, suf, len);
    value[len] = '\0';

    return value;
}

static void add_token(Scanner *sc, TokenType type) {
    char *value = get_value(sc);
    Token token = new_token(type, value);
    list_add(sc->list, token);
}

static void scan_number(Scanner *sc) {
    while (is_digit(peek(sc))) 
        advance(sc);

    if (peek(sc) == '.' && is_digit(peek_next(sc))) {
        advance(sc);

        while (is_digit(peek(sc))) 
            advance(sc);
    }

    add_token(sc, NUM);
}

static void scan_token(Scanner *sc) {
    char c = advance(sc);
    switch (c)
    {
    case '(':
        add_token(sc, LEFT_PAREN); break;
    case ')':
        add_token(sc, RIGHT_PAREN); break;
    case '+':
        add_token(sc, PLUS); break;
    case '-':
        add_token(sc, MINUS); break;
    case '*':
        add_token(sc, match(sc, '*') ? POW : MULT); break;
    case '/':
        add_token(sc, DIV); break;
    case '^':
        add_token(sc, POW); break;
    
    default:
        if (is_digit(c))
            scan_number(sc);
        
        break;
    }
}

TokenList *scan(char *source) {
    TokenList *list = new_list();
    Scanner scanner = {0, 0, source, list};

    while (!is_at_end(&scanner)) {
        scanner.start = scanner.current;
        scan_token(&scanner);
    }

    return list;
}
