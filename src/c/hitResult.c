#include "hitResult.h"

// literally taken from osus HitResultExtensions.IsHit(result)

int hitResultIsHit(int result){
    if(result <= HIT_RESULT_SMALL_TICK_MISS){
        if(result > HIT_RESULT_MISS && result != HIT_RESULT_SMALL_TICK_MISS){
            return 1;
        }
    } else if(result != HIT_RESULT_LARGE_TICK_MISS && result != HIT_RESULT_IGNORE_MISS && result != HIT_RESULT_COMBO_BREAK){
        return 1;
    }
    return 0;
}