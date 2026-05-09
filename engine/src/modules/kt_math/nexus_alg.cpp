#include "nexus_alg.h"

vector <int> NexAlg::move0(vector<int>& nums){
    int slow = 0;
    int fast = 0;


    while(fast<nums.size()){
        if(nums[fast] != 0){
            swap(nums[slow], nums[fast]);
            slow++;
        }
        fast++;
    }
    return nums;
}

ListNode* NexAlg::rotateRight(ListNode* head, int k){



return head;
}

