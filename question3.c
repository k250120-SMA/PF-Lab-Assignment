int* transformArray(int* nums, int numsSize, int* returnSize) {
    * returnSize= numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));
    
    if (result == NULL) {
        return NULL;
    }

    for (int i=0; i<numsSize; i++){
        result[i]=(nums[i]%2==0) ? 0 : 1;
    }

    int countZero=0;

    for (int i=0; i<numsSize; i++){
        if(result[i]==0){
            countZero++;
        }
    }
    for (int i=0; i<numsSize; i++){
        result[i]=(i<countZero)? 0 : 1;
    }
    return result;
}