
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (l1 == NULL)
        {
            return l2;
        }
        if (l2 == NULL)
        {
            return l1;
        }

        int plus = 0;
        int sum = 0;
        ListNode *pHead = NULL;
        ListNode *pCur = NULL;
        while (l1 != NULL && l2 !=NULL) //位数从个位开始相加，过10进1
        {
            sum = l1->val + l2->val + plus;
            plus = sum / 10;//超过10就进位
            ListNode *pNode = new ListNode(sum % 10);//sum % 10为当前位数的数值，独立为一个新节点
            if (pHead == NULL)//个位第一个节点赋值
            {
                pHead = pCur = pNode;
            }
            else
            {
                pCur->next = pNode;//上一位数的节点位置链接到当前位数节点位置
                pCur = pNode;//更新当前节点位置
            }
            l1 = l1->next;//更新L1和L2
            l2 = l2->next;
        }
        //一个数的位数比另一个数位数多，位数多的为li
        ListNode *li = (l1 != NULL ? l1 : l2);

        while (li != NULL)
        {
            sum = li->val + plus;//如果上一位有进位，plus=1
            plus = sum / 10;//如果还是有进位，继续进位
            ListNode *pNode = new ListNode(sum % 10);//当前位置的值
            pCur->next = pNode;//上一次位置的下一个连接到当前位置
            pCur = pNode;//更新当前位置
            li = li->next;//更新Li
        }
        //最后l1,l2位数都到头了还有进位的话，再加一个链接
        if (plus)
        {
            pCur->next = new ListNode(plus);
        }
        return pHead;
        //        ListNode preHead(0), *p = &preHead;
        //        int extra = 0;
        //        while (l1 || l2 || extra)
        //        {
        //           int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
        //           extra = sum / 10;
        //           p->next = new ListNode(sum % 10);
        //           p = p->next;
        //           l1 = l1 ? l1->next : l1;
        //           l2 = l2 ? l2->next : l2;
        //        }

        //        return preHead.next;
    }
};
