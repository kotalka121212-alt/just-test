#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <list>

using namespace std;


  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

namespace NexAlg{

vector <int> move0(vector<int>& nums);
ListNode* rotateRight(ListNode* head, int k);




};

