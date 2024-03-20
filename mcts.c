#include <stdio.h>
#include <float.h>
#include <math.h>

#include "mcts.h"
#include "fpmath.h"

static inline void uct_score_test(int n_total, int n_visits, double score)
{
    if (n_visits == 0)
        return;

    fx16_t fx16_n_total = to_fx16_int(n_total);
    fx16_t fx16_n_visits = to_fx16_int(n_visits);
    fx16_t fx16_score = to_fx16_double(score);

    printf("n_total: %d, n_visits: %d, score: %.15f\n", n_total, n_visits, score);
    printf("fx n_total: %d, fx n_visits: %d, fx score: %d\n", fx16_n_total, fx16_n_visits, fx16_score);
    printf("\n");

    // score / n_visits
    printf("score / n_visits\n");
    printf("\tFloat: \t\t%.15f\n", score / n_visits);
    printf("\tFixed Point: \t%.15f\n", to_Float(fx_div(fx16_score, fx16_n_visits)));
    printf("\n");

    // log(n_total)
    printf("log(n_total)\n");
    printf("\tFloat: \t\t%1.5f\n", log(n_total));
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_log(fx16_n_total)));
    printf("\n");

    // log(n_total) / n_visits
    printf("log(n_total) / n_visits\n");
    printf("\tFloat: \t\t%1.5f\n", log(n_total) / n_visits);
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_div(fx_log(fx16_n_total), fx16_n_visits)));
    printf("\n");

    // sqrt(log(n_total) / n_visits)
    printf("sqrt(log(n_total) / n_visits)\n");
    printf("\tFloat: \t\t%1.5f\n", sqrt(log(n_total) / n_visits));
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_sqrt(fx_div(fx_log(fx16_n_total), fx16_n_visits))));

    // EXPLORATION_FACTOR
    printf("EXPLORATION_FACTOR\n");
    printf("\tFloat: \t\t%1.5f\n", EXPLORATION_FACTOR);
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_sqrt(to_fx16_int(2))));
    printf("\n");

    // EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits)
    printf("EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits)\n");
    printf("\tFloat: \t\t%1.5f\n", EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits));
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_mul(fx_sqrt(to_fx16_int(2)), fx_sqrt(fx_div(fx_log(fx16_n_total), fx16_n_visits)))));
    printf("\n");

    // score / n_visits + EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits)
    printf("score / n_visits + EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits)\n");
    printf("\tFloat: \t\t%1.5f\n", score / n_visits + EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits));
    printf("\tFixed Point: \t%1.5f\n", to_Float(fx_div(fx16_score, fx16_n_visits) + fx_mul(fx_sqrt(to_fx16_int(2)), fx_sqrt(fx_div(fx_log(fx16_n_total), fx16_n_visits)))));
    printf("\n");
}

static inline double uct_score(int n_total, int n_visits, double score)
{
    if (n_visits == 0)
        return DBL_MAX;
    return score / n_visits +
           EXPLORATION_FACTOR * sqrt(log(n_total) / n_visits);
}

static inline double fx_uct_score(int n_total, int n_visits, double score)
{
    if (n_visits == 0)
        return DBL_MAX;
    
    fx16_t fx16_n_total = to_fx16_int(n_total);
    fx16_t fx16_n_visits = to_fx16_int(n_visits);
    fx16_t fx16_score = to_fx16_double(score);
    return to_Float(fx_div(fx16_score, fx16_n_visits) + fx_mul(fx_sqrt(to_fx16_int(2)), fx_sqrt(fx_div(fx_log(fx16_n_total), fx16_n_visits))));
}

int run()
{
    FILE *file;
    int n_total, n_visits;
    double score;
    char buffer[256]; // 用於讀取檔案每行的緩衝區

    file = fopen("uct_scores.log", "r");
    if (file == NULL) {
        perror("檔案打開失敗");
        return -1;
    }

    // 直接從檔案開頭開始解析並處理500行
    for (int i = 0; i < 500 && fgets(buffer, sizeof(buffer), file) != NULL; ++i) {
        // 根據檔案格式解析每行的n_total, n_visits, score
        if (sscanf(buffer, "n_total: %d, n_visits: %d, score: %lf", &n_total, &n_visits, &score) == 3) {
            uct_score_test(n_total, n_visits, score);
        } else {
            // 如果解析失敗，輸出錯誤信息
            printf("解析錯誤: %s", buffer);
        }
    }

    fclose(file);

    return 0;
}

int main(){
    run();
    return 0;
}