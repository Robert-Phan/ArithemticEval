#include "eval.h"
#include <math.h>

double eval_expr(Expr *expr);

double eval(char *source) {
    TokenList *list = scan(source);
    Expr *tree = parse(list);
    double eval = eval_expr(tree);

    free_list(list);
    free_expr(tree);

    return eval;
}

double eval_expr(Expr *expr) {
    // atof(expr->token.value);
    switch (expr->token.type)
    {
    case NUM:
        /* code */
        return atof(expr->token.value);
        break;
    
    case PLUS:
        return eval_expr(expr->left) + eval_expr(expr->right); break;
    case MINUS:
        return eval_expr(expr->left) - eval_expr(expr->right); break;
    case MULT:
        return eval_expr(expr->left) * eval_expr(expr->right); break;
    case DIV:
        return eval_expr(expr->left) / eval_expr(expr->right); break;
    case POW:
        return pow(eval_expr(expr->left), eval_expr(expr->right)); break;
    
    default:
        
        break;
    }

    return 0.0;
}